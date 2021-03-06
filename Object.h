#pragma once

#include "stdafx.h"
#include <list>
#include <memory>
#include "IComponent.h"
#include "Transform.h"
#include "Vector2.h"

class Object {
private:
	using ComponentList = std::list<std::shared_ptr<IComponent>>;

	std::tstring m_name;
	std::unique_ptr<Transform> m_transform;
	ComponentList m_components;

public:
	Object(std::tstring, const Utility::Vector2 = Utility::Vector2(), const Utility::Vector2 = Utility::Vector2(1, 1), const float = 0);
	Object(const Object& object);
	virtual ~Object() = default;

public:
	void Init();
	void Update();
	void Clear();

public:
	const std::tstring& GetName() const noexcept;

	template <class ComponentType>
	ComponentType& GetComponent() const {
		static_assert(std::is_base_of<IComponent, ComponentType>::value, "ComponentType is not Component");

		for (auto& iter : m_components)
			if (dynamic_cast<ComponentType*>(iter.get()))
				return *(static_cast<ComponentType*>(iter.get()));

		throw;
	}

	template <>
	Transform& GetComponent<Transform>() const {
		return *m_transform;
	}

	template <class ComponentType, class... Args>
	ComponentType& AddComponent(Args&&... args) {
		static_assert(std::is_base_of<IComponent, ComponentType>::value, "ComponentType is not Component");

		m_components.emplace_back(std::unique_ptr<ComponentType>(new ComponentType(this, std::forward<Args>(args)...)));
		return *(static_cast<ComponentType*>(m_components.back().get()));
	}
};