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

#include "../inc/componentmanager.hpp"

#include "../inc/defs.hpp"
#include "../inc/entitymanager.hpp"

#include <bitset>

namespace tyra {

    ComponentManager::~ComponentManager() {
        for (size_t i = 0; i < m_components.size(); ++i) {
            for (size_t j = 0; j < m_components[i].size(); ++j) {
                delete m_components[i][j];
            }
        }
    }

    void ComponentManager::add(EntityId entity_id, TypeId type_id, Component* component_ptr) {
        if (static_cast<size_t>(type_id) <= m_num_registered_components) {
            m_num_registered_components = static_cast<size_t>(type_id) + 1;
        }

        EntityIndex entity_index = EntityManager::index(entity_id);

        if (m_components.size() < static_cast<size_t>(entity_index + 1)) {
            m_components.resize(entity_index + 100);
            m_components_bits.resize(entity_index + 100);
        }

        if (m_components[entity_index][type_id] != nullptr) {
            delete m_components[entity_index][type_id];
        }

        m_components[entity_index][type_id] = component_ptr;
        m_components_bits[entity_index][type_id] = 1;

        m_updated.insert(entity_id);
    }

    void ComponentManager::remove(EntityId entity_id, TypeId type_id) {
        if (!valid(entity_id, type_id)) return;

        EntityIndex entity_index = EntityManager::index(entity_id);

        delete m_components[entity_index][type_id];

        m_components[entity_index][type_id] = nullptr;
        m_components_bits[entity_index][type_id] = 0;

        m_updated.insert(entity_id);
    }

    void ComponentManager::removeAll(EntityId entity_id) {
        EntityIndex entity_index = EntityManager::index(entity_id);

        for (size_t i = 0; i < m_components[entity_index].size(); ++i) {
            m_components[entity_index][i] = nullptr;
        }

        m_components_bits[entity_index].reset();

        m_updated.insert(entity_id);
    }

    bool ComponentManager::valid(EntityId entity_id, TypeId type_id) const {
        EntityIndex entity_index = EntityManager::index(entity_id);

        if (m_components_bits.size() < static_cast<size_t>(entity_index + 1)) {
            return false;
        }

        return m_components_bits[entity_index][type_id];
    }

    Component* ComponentManager::get(EntityId entity_id, TypeId type_id) const {
        EntityIndex entity_index = EntityManager::index(entity_id);

        return m_components[entity_index][type_id];
    }

    std::bitset<MAX_COMPONENT_TYPES>& ComponentManager::bits(EntityId entity_id){
        return m_components_bits[EntityManager::index(entity_id)];
    } 

}
