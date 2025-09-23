#pragma once
#include "IComponent.h"

namespace Components {
	struct IDComponent: public IComponent
	{
	public:
		explicit IDComponent(long&& id) : m_id(id) {}
	private:
		long m_id;

	public:
		const long& getId() const{
			return m_id;
		}
	};
}