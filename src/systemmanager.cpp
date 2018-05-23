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

#include "systemmanager.hpp"

#include "system.hpp"
#include "typeid.hpp"

#include <cstdlib>
#include <memory>

namespace tyra {

    void SystemManager::add(TypeId type_id, std::unique_ptr<System> system_ptr) {
        system_ptr->world(world());
        size_t system_index = static_cast<size_t>(type_id);
        if (m_systems.size() < system_index + 1) {
            m_systems.resize(system_index + 1);
        }
        m_systems[system_index] = std::move(system_ptr);
		m_systems[system_index]->init();
    }

    System& SystemManager::get(TypeId type_id) {
        return *m_systems[static_cast<size_t>(type_id)];
    }

    std::vector<std::unique_ptr<System>>& SystemManager::all() {
        return m_systems;
    }
}
