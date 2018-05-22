#include "componentset.hpp"
#include "typeid.hpp"

namespace tyra {

    const ComponentSet::container_type& ComponentSet::bits() const {
        return m_bits;
    }

	/*!
	\brief Adds the component type to the component set
	\param	type_id	The ::TypeId of the component
	\return a reference to this object for method chaining
	*/
    ComponentSet& ComponentSet::add(const TypeId& type_id) {
        m_bits[type_id] = 1;
        return *this;
    }

	/*!
	\brief Removes the component type from the component set
	\param	type_id	The ::TypeId of the component
	\return a reference to this object for method chaining
	*/
    ComponentSet& ComponentSet::remove(const TypeId& type_id) {
        m_bits[type_id] = 0;
        return *this;
    }

	/*!
	\brief Checks if this ComponentSet contains a specific component type
	\param	type_id	The ::TypeId of the component
	\return true if this ComponentSet contains the component, false if not
	*/
    bool ComponentSet::contains(const TypeId& type_id) const {
        if (static_cast<size_t>(type_id) >= m_bits.size()) {
            return false;
        }
        return m_bits[type_id];
    }

	/*!
	\brief Checks if this ComponentSet contains all of the components in another ComponentSet
	\details It differs from equality since `c1.contains_all(c2)` not necessarily is the same as `c2.contains_all(c1)`
	\param	other The ComponentSet whose member components will be compared the ones in this
	\return true if this ComponentSet contains all of the components in the ComponentSet `other`, false if not
	*/
    bool ComponentSet::contains_all(const ComponentSet& other) const {
        if(this->m_bits.any() && (this->m_bits & other.m_bits) != other.m_bits) {
            return false;
        }
        return true;
    }
	
	/*!
	\brief Checks if this ComponentSet contains any of the components in another ComponentSet
	\param	other The ComponentSet whose member components will be compared the ones in this
	\return true if this ComponentSet contains any of the components in the ComponentSet `other`, false if not
	*/
    bool ComponentSet::contains_any(const ComponentSet& other) const {
        if(this->m_bits.any() && (this->m_bits & other.m_bits).none()) {
            return false;
        }
        return true;
    }

	/*!
	\brief Checks if this ComponentSet doesn't contain any of the components in another ComponentSet
	\param	other The ComponentSet whose member components will be compared the ones in this
	\return true if this ComponentSet doesn't contain any of the components in the ComponentSet `other`, false if not
	*/
    bool ComponentSet::contains_none(const ComponentSet& other) const {
        if(this->m_bits.any() && (this->m_bits & other.m_bits).any()) {
            return false;
        }
        return true;
    }

	/*!
	\brief Checks whether this ComponentSet is empty or not
	\return true if this ComponentSet is empty, false if not
	*/
    bool ComponentSet::empty() const {
        return m_bits.none();
    }

    bool ComponentSet::operator==(const ComponentSet& other) const {
        return m_bits == other.m_bits;
    }

    bool ComponentSet::operator!=(const ComponentSet& other) const {
        return !operator==(other);
    }

}
