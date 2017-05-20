#include "config.hpp"
#include "typeid.hpp"

#include <bitset>
#include <cstdint>

#ifndef TYRA_COMPONENTSET_H
#define TYRA_COMPONENTSET_H

namespace tyra {

    struct Component;

    class ComponentSet {
    public:
        typedef std::bitset<MAX_COMPONENT_TYPES> container_type;
        container_type m_bits;
        ComponentSet(container_type set) : m_bits(set) {} 

        //template<typename T> static void build(container_type&); 
        //template<typename T1, typename T2, typename... Ts> static void build(container_type&);

    public:
        ComponentSet() = default;
        const container_type& bits() const;
        //template<typename T> static ComponentSet build(); 
        //template<typename T1, typename T2, typename... Ts> static ComponentSet build();

        ComponentSet& add(const TypeId&);
        ComponentSet& remove(const TypeId&);

        bool contains(const TypeId&) const;
        bool contains_all(const ComponentSet& other) const;
        bool contains_any(const ComponentSet& other) const;
        bool contains_none(const ComponentSet& other) const;

        bool empty() const;

        bool operator==(const ComponentSet& other) const;
        bool operator!=(const ComponentSet& other) const;
    };

    const ComponentSet::container_type& ComponentSet::bits() const {
        return m_bits;
    }

    /*
    template<typename T>
        ComponentSet ComponentSet::build() {
            container_type set;
            build<T>(set);
            return ComponentSet(set);
        }

    template<typename T>
        void ComponentSet::build(container_type& c) {
            TypeId id = Type<Component>::id<T>();
            c[id] = 1;
        }

    template<typename T1, typename T2, typename... Ts>
        ComponentSet ComponentSet::build() {
            container_type set;
            build<T1, T2, Ts...>(set);
            return ComponentSet(set);
        }

    template<typename T1, typename T2, typename... Ts>
        void ComponentSet::build(container_type& c) {
            TypeId id = Type<Component>::id<T1>();
            c[id] = 1;
            build<T2, Ts...>(c);
        }

    */
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

#endif
