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

#include "../inc/entitymanager.hpp"
#include "../inc/assert.hpp"

namespace tyra {

    /**
     * \details Validates an ::EntityId. If the entity has not been destroyed it should return true.
     * @see World::destroyEntity(EntityId)
     */
    bool EntityManager::valid(EntityId entity_id) const {
        EntityIndex entity_index = index(entity_id);
        EntityVersion entity_version = version(entity_id);
        return (entity_index < m_pool.size() && m_pool[entity_index] == entity_version);
    }

    /**
     * \details Will create a new ::EntityId or reuse one from a preveiously
     * destroyed entity.
     */
    EntityId EntityManager::create() {
        if (m_free.empty()) {
            ASSERT_ERROR(m_pool.size() < MAX_ENTITIES, "EntityManager::create: Maximum entities reached.");
            m_pool.push_back(0);
            m_free.push_back(m_pool.size() - 1);
        }
        EntityIndex entity_index = m_free.back();
        m_free.pop_back();
        return id(m_pool[entity_index], entity_index);
    }

    /**
     * \details Destroys an entity and recyclies it's ::EntityIndex. This
     * ::EntityId will become invalid and further use will trigger exceptions.
     * \exception std::runtime_error if the EntityId is invalid.
     */
    void EntityManager::destroy(EntityId entity_id) {
        ASSERT_ERROR(valid(entity_id), "EntityManager::destroy: Invalid entity.");
        EntityIndex entity_index = index(entity_id);
        ++m_pool[entity_index];
        m_free.push_back(entity_index);
        m_active.erase(entity_index);
    }

    /**
     * \details Evaluates if an ::EntityId is active. Active entities will remain
     * alive, but will not be processed by systems.
     * \exception std::runtime_error if the EntityId is invalid.
     */
    bool EntityManager::active(EntityId entity_id) const {
        ASSERT_ERROR(valid(entity_id), "EntityManager::active: Invalid entity.");
        return (m_active.find(entity_id) != m_active.end());
    }

    /**
     * \details Activates an ::EntityId. Systems will resume processing this
     * ::EntityId if there are any systems subscribing to it.
     * \exception std::runtime_error if the EntityId is invalid.
     * \todo re-insert the entity to subscribing systems.
     */
    void EntityManager::activate(EntityId entity_id) {
        ASSERT_ERROR(valid(entity_id), "EntityManager::activate: Invalid entity.");
        m_active.insert(entity_id);
    }

    /**
     * \details Deactivates an ::EntityId. Systems will cease processing this
     * ::EntityId if there are any systems subscribing to it.
     * \exception std::runtime_error if the EntityId is invalid.
     * \todo remove the entity from subscribing systems.
     */
    void EntityManager::deactivate(EntityId entity_id) {
        ASSERT_ERROR(valid(entity_id), "EntityManager::deactivate: Invalid entity.");
        m_active.erase(entity_id);
    }

}
