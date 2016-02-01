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

#include "../inc/world.hpp"

#include "../inc/componentmanager.hpp"
#include "../inc/entitymanager.hpp"
#include "../inc/system.hpp"
#include "../inc/systemmanager.hpp"

#include <cstdlib>

namespace tyra {

    World::World() :
    m_component_manager(new ComponentManager()),
    m_entity_manager(new EntityManager()),
    m_system_manager(new SystemManager()) {
        m_component_manager->world(*this);
        m_entity_manager->world(*this);
        m_system_manager->world(*this);
    }

    void World::update() {
        if (processing()) {
            preUpdate();
            for(System* sys : system().all()) {
                for(EntityId entity_id : component().updated()) {
                    sys->entityUpdated(entity_id, component().bits(entity_id));
                }
                sys->update();
            }
            postUpdate();
            component().updated().clear();
        }
    }

    EntityManager& World::entity()         { return *m_entity_manager; }
    ComponentManager& World::component()   { return *m_component_manager; }
    SystemManager& World::system()         { return *m_system_manager; }

}
