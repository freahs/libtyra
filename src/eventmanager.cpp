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

#include "../inc/eventmanager.hpp"

#include "../inc/entitymanager.hpp"
#include "../inc/defs.hpp"

namespace tyra {

    void EventManager::add(EntityId entity_id, TypeId type_id) {
        m_events[type_id].insert(entity_id);
    }

    void EventManager::remove(EntityId entity_id, TypeId type_id) {
        m_events[type_id].erase(entity_id);
    }

    void EventManager::create(TypeId type_id, Event& event) {
        for (EntityId entity_id : m_events[type_id]) {
            event.run(entity_id);
        }
    }
}
