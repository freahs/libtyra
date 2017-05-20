#include "config.hpp"
#include "typeid.hpp"

#include <bitset>
#include <cstdint>

#ifndef TYRA_COMPONENTSET_H
#define TYRA_COMPONENTSET_H

namespace tyra {

    struct Component;

    class ComponentSet {
    private:
        typedef std::bitset<MAX_COMPONENT_TYPES> container_type;
        container_type m_bits;
        ComponentSet(container_type set) : m_bits(set) {} 

        template<typename T> static void build(container_type&); 
        template<typename T1, typename T2, typename... Ts> static void build(container_type&);

    public:
        const container_type& bits() const;
        template<typename T> static ComponentSet build(); 
        template<typename T1, typename T2, typename... Ts> static ComponentSet build();

        bool contains_all(const ComponentSet& other) const;
        bool contains_any(const ComponentSet& other) const;
        bool contains_none(const ComponentSet& other) const;
    };

    const ComponentSet::container_type& ComponentSet::bits() const {
        return m_bits;
    }

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
}

#endif
