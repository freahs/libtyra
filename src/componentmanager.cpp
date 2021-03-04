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

#include "componentmanager.hpp"

#include "entitymanager.hpp"

#include <bitset>
#include <memory>

namespace tyra {

    void ComponentManager::add(EntityId entity_id, TypeId type_id, std::unique_ptr<Component> component_ptr) {
        if (valid(entity_id, type_id)) {
            throw error::ComponentError("ComponentManager::add: Component already present (1)", entity_id, type_id);
        }

        // TODO: fix types
        if (static_cast<size_t>(type_id) <= m_num_registered_components) {
            m_num_registered_components = static_cast<size_t>(type_id + 1);
        }

        EntityIndex entity_index = EntityManager::index(entity_id);

        // TODO: fix resize method
        if (m_component_arrays.size() < static_cast<size_t>(entity_index + 1)) {
            m_component_arrays.resize(entity_index + 100);
            m_component_sets.resize(entity_index + 100);
        }

        m_component_arrays[entity_index][type_id] = std::move(component_ptr);
        m_component_sets[entity_index].add(type_id);

        m_updated.insert(entity_id);
    }

    void ComponentManager::remove(EntityId entity_id, TypeId type_id) {
        if (!valid(entity_id, type_id)) {
            throw error::ComponentError("ComponentManager::remove: Component not present", entity_id, type_id);
        }

        EntityIndex entity_index = EntityManager::index(entity_id);

        m_component_arrays[entity_index][type_id].release();
        m_component_sets[entity_index].remove(type_id);

        m_updated.insert(entity_id);
    }


    bool ComponentManager::valid(EntityId entity_id, TypeId type_id) const {
        EntityIndex entity_index = EntityManager::index(entity_id);

        if (m_component_sets.size() < static_cast<size_t>(entity_index + 1)) {
            return false;
        }

        return m_component_sets[entity_index].contains(type_id);
    }

    Component& ComponentManager::get(EntityId entity_id, TypeId type_id) const {
        if (!valid(entity_id, type_id)) {
            throw error::ComponentError("ComponentManager::get: Component not present", entity_id, type_id);
        }
        EntityIndex entity_index = EntityManager::index(entity_id);
        return *m_component_arrays[entity_index][type_id];
    }

    const TypeSet& ComponentManager::bits(EntityId entity_id) const {
        EntityIndex entity_index = EntityManager::index(entity_id);
        return m_component_sets[entity_index];
    } 

}
