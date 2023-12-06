//@fil// @file: Transform.cpp
//
// @brief: Implementation of the Transform class, which represents the spatial properties (position, rotation, scale) of an entity.
//
//
// 


#include "EngineCore.h"
#include "Transform.h"

IMPLEMENT_DYNAMIC_CLASS(Transform);

/**
 * @brief Default constructor for Transform. Initializes position to (0,0), rotation to 0, and scale to (1,1).
 */

Transform::Transform() : position(Vec2::Zero), rotation(0), scale(Vec2(1)) {} //constructor & initialize pos to 0, rotation to 0, scale to 1

/**
 * @brief Initializes the Transform component. This function is called during the initialization of the component.
 */
void Transform::Initialize() { // empty function but initial values are est in constructor
	//LOG(position.x << ", " << position.y << ", " << rotation)
}

/**
 * @brief Updates the Transform component's state. This function is called every frame to update the component's state.
 */
void Transform::Update() {
	Component::Update();
}

/**
 * @brief Loads Transform data from JSON.
 *
 * @param node The JSON object containing the Transform data.
 */
void Transform::Load(json::JSON& node)
{
	Component::Load(node);

	if (node.hasKey("Position")) {
		position = vec2_from_json(node["Position"]);
	}
	if (node.hasKey("Rotation"))
	{
		rotation = static_cast<float>(node["Rotation"].ToFloat());
	}
	if (node.hasKey("Scale")) {
		scale = vec2_from_json(node["Scale"]);
	}
}

/**
 * @brief Translates the entity by a given vector.
 *
 * @param delta The vector by which to translate the entity.
 */
void Transform::Translate(const Vec2& delta) { // next 3 functions for adjusting position, rotation and scale by a given vector
	position += delta;
}

/**
 * @brief Rotates the entity by a given amount.
 *
 * @param delta The amount by which to rotate the entity.
 */
void Transform::Rotate(float delta) {
	rotation += delta;
}

/**
 * @brief Scales the entity by a given vector.
 *
 * @param delta The vector by which to scale the entity.
 */
void Transform::Scale(const Vec2& delta) {
	scale *= delta;
}

