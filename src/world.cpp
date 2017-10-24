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

#include "world.hpp"

#include "componentmanager.hpp"
#include "entitymanager.hpp"
#include "system.hpp"
#include "systemmanager.hpp"

#include "logger.hpp"

#include <chrono>
#include <cstdlib>

namespace tyra {

    World::World() :
        m_component_manager(new ComponentManager()),
        m_entity_manager(new EntityManager()),
        m_system_manager(new SystemManager()),
        m_processing(false),
        m_prev_update(Time::now()),
        m_delta(0) {
            m_component_manager->world(*this);
            m_entity_manager->world(*this);
            m_system_manager->world(*this);
        }

    World::~World() {
        delete m_component_manager;
        delete m_entity_manager;
        delete m_system_manager;
    }

    void World::update() {
        init_loggers();
        auto logg = spdlog::get("world");
        logg->set_level(spdlog::level::debug);

        TimePoint time_now = Time::now();
        m_delta = std::chrono::duration_cast<Ms>(time_now - m_prev_update).count();
        m_prev_update = time_now;

        if (processing()) {
            preUpdate();

            for(System* sys : system().all()) {
                for(EntityId entity_id : component().updated()) {
                    sys->entityUpdated(entity_id, component().bits(entity_id));
                }
            }

            component().updated().clear();

            for(System* sys : system().all()) {
                sys->update();
            }

            postUpdate();
        }
    }

    EntityManager& World::entity()         { return *m_entity_manager; }
    ComponentManager& World::component()   { return *m_component_manager; }
    SystemManager& World::system()         { return *m_system_manager; }

    EntityId World::tag(const std::string& tag) const {
        auto res = m_tags.find(tag);
        if (res == m_tags.end()) {
            return -1;
        }
        return res->second;
    }

    void World::tag(const std::string& tag, EntityId entity_id) {
        m_tags[tag] = entity_id;
    }

    int World::delta() const {
        return m_delta;
    }

}
