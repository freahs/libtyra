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
#include "typeid.hpp"

#include <chrono>
#include <cstdlib>
#include <memory>

namespace tyra {

    World::World() :
        m_processing(false),
        m_prev_update(Time::now()),
        m_delta(0) {
            add_manager<ComponentManager>();
            add_manager<EntityManager>();
            add_manager<SystemManager>();
        }

    void World::notify_systems() {
        for(auto& sys : system().all()) {
            for(EntityId entity_id : component().updated()) {
                sys->updated().insert(entity_id);
            }
        }
        component().updated().clear();
    }

    void World::update() {

        TimePoint time_now = Time::now();
        m_delta = std::chrono::duration_cast<Ms>(time_now - m_prev_update).count();
        m_prev_update = time_now;

        if (processing()) {
            preUpdate();


            notify_systems();
            for(auto& sys : system().all()) {
                for (EntityId entity_id : sys->updated()) {
                    sys->entityUpdated(entity_id, component().bits(entity_id));
                }
                sys->updated().clear();
                sys->update();
                notify_systems();
            }

            postUpdate();
        }
    }

    EntityManager& World::entity()         { return get_manager<EntityManager>(); }
    ComponentManager& World::component()   { return get_manager<ComponentManager>(); }
    SystemManager& World::system()         { return get_manager<SystemManager>(); }

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
