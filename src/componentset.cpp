#include "componentset.hpp"
#include "typeid.hpp"

namespace tyra {

    const ComponentSet::container_type& ComponentSet::bits() const {
        return m_bits;
    }

    ComponentSet& ComponentSet::add(const TypeId& type_id) {
        m_bits[type_id] = 1;
        return *this;
    }

    ComponentSet& ComponentSet::remove(const TypeId& type_id) {
        m_bits[type_id] = 0;
        return *this;
    }

    bool ComponentSet::contains(const TypeId& type_id) const {
        if (static_cast<size_t>(type_id) >= m_bits.size()) {
            return false;
        }
        return m_bits[type_id];
    }

    bool ComponentSet::contains_all(const ComponentSet& other) const {
        if(this->m_bits.any() && (this->m_bits & other.m_bits) != other.m_bits) {
            return false;
        }
        return true;
    }

    bool ComponentSet::contains_any(const ComponentSet& other) const {
        if(this->m_bits.any() && (this->m_bits & other.m_bits).none()) {
            return false;
        }
        return true;
    }

    bool ComponentSet::contains_none(const ComponentSet& other) const {
        if(this->m_bits.any() && (this->m_bits & other.m_bits).any()) {
            return false;
        }
        return true;
    }

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
