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

#include "common.hpp"
#include "typeid.hpp"

#include <bitset>
#include <iostream>

namespace tyra {

    class TypeSet {
    private:
        std::bitset<MAX_TYPES> m_bits;
        
    public:
        TypeSet& add(const TypeId&);
        TypeSet& remove(const TypeId&);

        bool contains(const TypeId&) const;
        bool contains_all(const TypeSet& other) const;
        bool contains_any(const TypeSet& other) const;
        bool contains_none(const TypeSet& other) const;

        size_t size() const;
        bool empty() const;

        bool operator==(const TypeSet& other) const;
        bool operator!=(const TypeSet& other) const;
		bool operator<(const TypeSet& other) const;
        size_t hash() const;

        friend std::ostream& operator<<(std::ostream& os, const TypeSet& cs) {
            os << cs.m_bits;
            return os;
        }
    };
}

#endif
