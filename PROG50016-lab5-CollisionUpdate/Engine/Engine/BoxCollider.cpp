#include "EngineCore.h"
#include "BoxCollider.h"

IMPLEMENT_DYNAMIC_CLASS(BoxCollider);

void BoxCollider::Load(json::JSON& node)
{
	if (node.hasKey("Width")) {
		width = node[0].ToInt();
	}
	if (node.hasKey("Height")) {
		height = node[1].ToInt();
	}
	if (node.hasKey("Position")) {
		Vec2 pos = vec2_from_json(node["Position"]);
		*m_rect = { static_cast<int>(pos.x), static_cast<int>(pos.y), width, height };
	}
}

bool BoxCollider::HandleCollision(ICollider* other) {
	return false;
}

/**
* * @brief Sets the size of the BoxCollider.
* *
* * @param width The new width for the collider.
* * @param height The new height for the collider.
* */
void BoxCollider::SetSize(int width, int height) const
{
	if (m_rect == nullptr) {
		return;
	}
	*m_rect = { static_cast<int>(ownerEntity->GetTransform().position.x), static_cast<int>(ownerEntity->GetTransform().position.y), width, height };
}
/**
* * @brief Gets the size of the BoxCollider.
* *
* * @return The size of the collider.
* */
SDL_Rect BoxCollider::GetBounds() const
{
	if (m_rect == nullptr) {
		return { 0, 0, 0, 0 };
	}
	//rectangle != transform
	SDL_Rect result = *m_rect;
	result.x = ownerEntity->GetTransform().position.x;
	result.y = ownerEntity->GetTransform().position.y;
	return *m_rect;
}
/**
* * @brief Calculates the broad phase radius of the BoxCollider.
* *
* * @return The radius of the collider.
* */


float BoxCollider::GetBroadPhaseRadius() const {
	if (m_rect == nullptr) {
		return 0.0f;
	}
	return Vec2(static_cast<float>(m_rect->w), static_cast<float>(m_rect->h)).Magnitude();
}

/**
*
* * @brief Gets the type of the collider.
* *
* * @return The type of the collider, in this case Box.
* */
ColliderType BoxCollider::GetType() const {
	return ColliderType::Box;
}
