/**
 * Copyright 2017 Fredrik Åhs
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef TYRA_COMPONENTSET_H
#define TYRA_COMPONENTSET_H

#include "config.hpp"
#include "typeid.hpp"

#include <bitset>
#include <cstdint>
#include <iostream>

namespace tyra {

    struct Component;

	/*!
	\brief Basically a bitset with some convenience methods to group component types
	\details Component often appear in specific configurations and such configurations might appear in many locations. The ComponentSet makes it easy to reuse such configurations.
	*/
    class ComponentSet {
    private:
        typedef std::bitset<MAX_COMPONENT_TYPES> container_type;
        container_type m_bits;
        
    public:
        ComponentSet& add(const TypeId&);
        ComponentSet& remove(const TypeId&);

        bool contains(const TypeId&) const;
        bool contains_all(const ComponentSet& other) const;
        bool contains_any(const ComponentSet& other) const;
        bool contains_none(const ComponentSet& other) const;

        bool empty() const;

        bool operator==(const ComponentSet& other) const;
        bool operator!=(const ComponentSet& other) const;
        friend std::ostream& operator<<(std::ostream& os, const ComponentSet& cs) {
            os << cs.m_bits;
            return os;
        }
    };



}

#endif
