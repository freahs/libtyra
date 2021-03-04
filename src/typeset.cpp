#include "typeset.hpp"
#include "typeid.hpp"

namespace tyra {

    /*!
	\brief Adds the type to the TypeSet
	\param	type_id	The ::TypeId of the type
	\return a reference to this object for method chaining
	*/
    TypeSet& TypeSet::add(const TypeId& type_id) {
        m_bits[type_id] = 1;
        return *this;
    }

	/*!
	\brief Removes the type from the TypeSet
	\param	type_id	The ::TypeId of the component
	\return a reference to this object for method chaining
	*/
    TypeSet& TypeSet::remove(const TypeId& type_id) {
        m_bits[type_id] = 0;
        return *this;
    }

	/*!
	\brief Checks if this TypeSet contains a specific type
	\param	type_id	The ::TypeId of the component
	\return true if this TypeSet contains the type, false if not
	*/
    bool TypeSet::contains(const TypeId& type_id) const {
        if (static_cast<size_t>(type_id) >= m_bits.size()) {
            return false;
        }
        return m_bits[type_id];
    }

	/*!
	\brief Checks if this TypeSet contains all of the types in another TypeSet
	\details It differs from equality since `s1.contains_all(s2)` not necessarily is the same as `s2.contains_all(s1)`
	\param	other The TypeSet whose member types will be compared the ones in this
	\return true if this TypeSet contains all of the types in the TypeSet \a other, false if not
	*/
    bool TypeSet::contains_all(const TypeSet& other) const {
        if(this->m_bits.any() && (this->m_bits & other.m_bits) != other.m_bits) {
            return false;
        }
        return true;
    }
	
	/*!
	\brief Checks if this TypeSet contains any of the types in another TypeSet
	\param	other The TypeSet whose member types will be compared the ones in this
	\return true if this TypeSet contains any of the types in the TypeSet \a other, false if not
	*/
    bool TypeSet::contains_any(const TypeSet& other) const {
        if(this->m_bits.any() && (this->m_bits & other.m_bits).none()) {
            return false;
        }
        return true;
    }

	/*!
	\brief Checks if this TypeSet doesn't contain any of the types in another TypeSet
	\param	other The TypeSet whose member types will be compared to the ones in this
	\return true if this TypeSet doesn't contain any of the types in the TypeSet \a other, false if not
	*/
    bool TypeSet::contains_none(const TypeSet& other) const {
        if(this->m_bits.any() && (this->m_bits & other.m_bits).any()) {
            return false;
        }
        return true;
    }

    /*!
    \return Returns the number of member types in this TypeSet
    */
    size_t TypeSet::size() const {
        return m_bits.count();
    }

	/*!
	\brief Checks whether this TypeSet is empty or not
	\return true if this TypeSet is empty, false if not
	*/
    bool TypeSet::empty() const {
        return m_bits.none();
    }

    bool TypeSet::operator==(const TypeSet& other) const {
        return m_bits == other.m_bits;
    }

    bool TypeSet::operator!=(const TypeSet& other) const {
        return !operator==(other);
    }

	bool TypeSet::operator<(const TypeSet& other) const {
		return m_bits.to_ullong() < other.m_bits.to_ullong();
	}

    size_t TypeSet::hash() const {
        static const std::hash<std::bitset<MAX_TYPES>> hash_fn{};
        return hash_fn(m_bits);
    }

}
