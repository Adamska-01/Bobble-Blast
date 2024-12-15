#pragma once
#include "../Constants/ComponentBucketConstants.h"
#include "../Components/GameComponent.h"
#include <array>
#include <bitset>
#include <vector>
#include <memory>


class GameObject;


class ComponentBucket
{
	friend class GameObject;


private:
	std::vector<std::unique_ptr<GameComponent>> components;

	std::bitset<ComponentConstants::MAX_COMPONENTS> componentBitSet;

	std::array<GameComponent*, ComponentConstants::MAX_COMPONENTS> componentArray;


	size_t GetComponentID();


	template <typename T>
	size_t GetComponentTypeID();

	template <typename T>
	bool ContainsComponent() const;

	template <typename T>
	T& GetComponent() const;

	template<typename T, typename... TArgs>
	T& AddComponent(GameObject* owner, TArgs&& ...args);
};


template <typename T>
size_t ComponentBucket::GetComponentTypeID()
{
	static size_t typeID = GetComponentID();

	return typeID;
}

template<typename T>
bool ComponentBucket::ContainsComponent() const
{
	return componentBitSet[GetComponentTypeID<T>()];
}

template<typename T>
T& ComponentBucket::GetComponent() const
{
	return *static_cast<T*>(componentArray[GetComponentTypeID<T>()]);
}

template<typename T, typename ...TArgs>
T& ComponentBucket::AddComponent(GameObject* owner, TArgs&& ...args)
{
	T* component = new T(std::forward<TArgs>(args)...);

	component->OwningObject = owner;

	std::unique_ptr<GameComponent> uniquePtr(component);

	static_assert(std::is_base_of<GameComponent, T>::value, "child must inherit from GameComponent");
	static_assert(std::is_same<std::unique_ptr<GameComponent>, decltype(uniquePtr)>::value, "uniquePtr must be of the correct type");

	components.emplace_back(std::move(uniquePtr));

	auto typeID = GetComponentTypeID<T>();

	componentArray[typeID] = component;
	componentBitSet[typeID] = true;

	// TODO: Add init function to GameComponent class
	//component->Initialize();

	return *component;
}