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
#include "typeid.hpp"
#include "world.hpp"

#include <bitset>
#include <iostream>

namespace tyra {

    void System::requireOne(TypeId id) {
        ASSERT_ERROR(!m_exclude_components[id], "System::requireComponent: component already excluded.");
        m_require_one_components[id] = 1;
    }

    void System::requireAll(TypeId id) {
        ASSERT_ERROR(!m_exclude_components[id], "System::requireComponent: component already excluded.");
        m_require_all_components[id] = 1;
    }

    void System::exclude(TypeId id) {
        ASSERT_ERROR(!m_require_one_components[id], "System::requireComponent: component already included.");
        ASSERT_ERROR(!m_require_all_components[id], "System::requireComponent: component already included.");
        m_exclude_components[id] = 1;
    }

    void System::addEntity(EntityId id) {
        m_entities.insert(id);
        entityAdded(id);
    }

    void System::removeEntity(EntityId id) {
        m_entities.erase(id);
        entityRemoved(id);
    }

    void System::entityUpdated(EntityId id, std::bitset<MAX_COMPONENT_TYPES>& entity_components) {
        bool has_all = false;
        bool has_one = false;
        bool has_excluded = false;

        if (m_require_all_components.count() == 0 && m_require_one_components.count() == 0) {
            return;
        }

        for (size_t i = 0; i < MAX_COMPONENT_TYPES; ++i) {
            if (m_exclude_components[i] && entity_components[i]) { has_excluded = true; break; }
            if (m_require_all_components[i] && !entity_components[i]) { has_all = false; break; }
            if (m_require_one_components[i] && entity_components[i]) has_one = true;
            if (m_require_all_components[i] && entity_components[i]) has_all = true;
        }

        bool is_present = m_entities.find(id) != m_entities.end();

        if (is_present){
            if (has_excluded) removeEntity(id);
            else if (!has_one && !has_all) removeEntity(id);
            else if (!has_one && m_require_one_components.any()) removeEntity(id);
            else if (!has_all && m_require_all_components.any()) removeEntity(id);
        } else if(!has_excluded && !is_present) {
            if (has_all && has_one) addEntity(id);
            else if (has_one && !has_all && m_require_all_components.none()) addEntity(id);
            else if (has_all && !has_one && m_require_one_components.none()) addEntity(id);
        }
    }

    void System::update() {
        process(m_entities);
    }

}
