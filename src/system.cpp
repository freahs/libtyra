/**
 * Copyright 2016 Fredrik Åhs
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

#include "system.hpp"

#include "assert.hpp"
#include "componentmanager.hpp"
#include "entitymanager.hpp"
#include "typeid.hpp"
#include "world.hpp"

#include <bitset>
#include <iostream>

#include <sstream>

namespace tyra {

    void System::entityUpdated(EntityId id, const TypeSet& entity_components) {
        bool p = m_entities.find(id) != m_entities.end();
        bool i = interested(entity_components);
        if (i && !p) {
            m_entities.insert(id);
            entityAdded(id);
        } else if (!i && p) {
            m_entities.erase(id);
            entityRemoved(id);
        }
    }

    void System::update() {
        process(m_entities);
    }

}
