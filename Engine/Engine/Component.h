#pragma once

#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include "Object.h"

/**
 * @class Component
 *
 * The Component class is an abstract base class for all components that can be attached to entities.
 * It provides a common interface for initializing, updating, and loading component data.
 */
class Entity;

class Component : public Object
{
    DECLARE_ABSTRACT_DERIVED_CLASS(Component, Object)

protected:
    Entity* ownerEntity = nullptr;  //< Pointer to the entity that owns this component.

public:
    /**
     * @brief Default constructor for the Component class.
    */
    Component() = default;


    /**
    *@brief Destructor for the Component class.
    */
    ~Component() override = default;

    /**
     * @brief Initializes the component.
    * This function is called during the initialization of the component.
    */
    void Initialize() override;

    /**
     * @brief Updates the component's state.
     * This pure virtual function must be implemented by derived component classes.
     */
    virtual void Update() {
#ifdef DEBUG_COMPONENT
        LOG("Component Update called on " << this->uid)
#endif
    };

    /**
    * @brief Loads component data from a JSON object.
    *
    * @param node The JSON object containing the component data.
    */
    void Load(json::JSON& node) override;

    /**
     * @brief Destroys the component.
     * This function is called when the component is being destroyed.
     * Can be overridden by derived classes to perform additional cleanup.
     */
    void Destroy() override;

    /**
    * @brief Sets the owner entity of this component.
    *
    * @param owner Pointer to the Entity that owns this component.
    */
    void SetOwner(Entity* owner);

    /**
    * @brief Gets the owner entity of this component.
    *
    * @return Pointer to the owner Entity.
    */
    Entity* GetOwner() const;

    friend class Entity; // To allow Entity to access protected/private members
};

#endif // !_COMPONENT_H_
