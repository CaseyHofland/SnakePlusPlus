#include "Snake.h"
#include "RectMath.h"

Snake::Snake() noexcept : m_position{ RectMath::RectPos(Grid::RandTile()) }
{
    for (unsigned i = 0; i < std::max(Core::startingBodyParts, minimumBodyParts); i++)
    {
        Grow();
    }
}

void Snake::Update(float deltaTime, const InputData& input) noexcept
{
    ProcessInput(input);
    m_position += speed * Grid::tileSize * deltaTime * m_moveDirection;

    UpdateBodyPosition();

    if (Grid::OutOfBounds(Head())
        || HasBodyCollision())
    {
        Die();
    }
}

void Snake::Render(const Renderer& renderer) const noexcept
{
    std::for_each(m_bodyParts.begin(), m_bodyParts.end(), [this, &renderer](const auto& bodyPart) noexcept { renderer.FillRect(bodyColor, bodyPart); });
    renderer.FillRect(headColor, Head());
}

void Snake::ProcessInput(const InputData& input) noexcept
{
    Vector2 newMoveDirection{ m_moveDirection };

    if (input.GetKeyDown(Scancode::SDL_SCANCODE_LEFT))
    {
        newMoveDirection = Vector2::left();
    }
    else if (input.GetKeyDown(Scancode::SDL_SCANCODE_RIGHT))
    {
        newMoveDirection = Vector2::right();
    }
    else if (input.GetKeyDown(Scancode::SDL_SCANCODE_UP))
    {
        newMoveDirection = Vector2::down();
    }
    else if (input.GetKeyDown(Scancode::SDL_SCANCODE_DOWN))
    {
        newMoveDirection = Vector2::up();
    }

    if (newMoveDirection == m_moveDirection
        || newMoveDirection == -m_moveDirection)
    {
        return;
    }

    m_moveDirection = newMoveDirection;

    // If the move direction changed, snap the position to the grid and pre-move it to ensure players can't turn in on themselves.
    Snap();
    m_position += Grid::tileSize * 0.5f * m_moveDirection;
}

void Snake::Snap() noexcept
{
    const auto headCenter = RectMath::RectCenter(Head());
    m_position.x = static_cast<float>(Grid::Snap(headCenter.x));
    m_position.y = static_cast<float>(Grid::Snap(headCenter.y));

    UpdateBodyPosition();
}

[[gsl::suppress(f.6, justification : "The size of m_bodyParts is kept at a minimum of 3, meaning m_bodyParts.at(1) and m_bodyParts.at(m_bodyParts.size() - 2) may never throw.")]]
void Snake::UpdateBodyPosition() noexcept
{
    // Collect body parts to perform calculations on.
    auto& head{ m_bodyParts.front() };
    const auto& neck{ m_bodyParts.at(1) };
    const auto& butt{ m_bodyParts.at(m_bodyParts.size() - 2) };
    auto& tail{ m_bodyParts.back() };

    // Place the head at the position.
    RectMath::PlaceRect(head, m_position);

    // Shift the body if the head moves too far from the neck.
    auto neckDistance{ static_cast<unsigned>(RectMath::Distance(head, neck)) };
    if (neckDistance >= Grid::tileSize)
    {
        std::shift_right(m_bodyParts.begin(), m_bodyParts.end(), 1);
        neckDistance -= Grid::tileSize;
    }

    // Smooth out the tail based on the heads distance from the neck.
    // Note to Ulf: this code is added functionality that is unnecessary, but I added it as a bonus to smooth out the tail. Removing it has no affect on the attachment of head and neck.
    const auto tailDistance{ Grid::tileSize - neckDistance };
    const auto tailDirection{ RectMath::Direction(tail, butt) };
    const auto tailDelta = static_cast<float>(tailDistance) * tailDirection;
    const auto tailPos = RectMath::RectPos(butt) + tailDelta;
    RectMath::PlaceRect(tail, tailPos);
}

bool Snake::HasBodyCollision() const noexcept
{
    if (m_bodyParts.size() <= minimumBodyParts)
    {
        return false;
    }

    const auto intersectsHeadAndNotAtTail = [this](const auto& bodyPart) noexcept
    {
        return SDL_HasIntersection(&bodyPart, &Head())
            && !(bodyPart.x == Tail().x && bodyPart.y == Tail().y);
    };

    // The size of m_bodyParts is kept at a minimum of 3, meaning m_bodyParts.begin() + 2 and m_bodyParts.end() - 1 may never throw.
    const auto bodyBegin = m_bodyParts.begin() + 2;
    const auto bodyEnd = m_bodyParts.end() - 1;
    return std::any_of(bodyBegin, bodyEnd, intersectsHeadAndNotAtTail);
}
