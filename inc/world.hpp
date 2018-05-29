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

#ifndef TYRA_WORLD_H
#define TYRA_WORLD_H

#include "common.hpp"
#include "manager.hpp"
#include "typeid.hpp"

#include "componentmanager.hpp"
#include "entitymanager.hpp"
#include "systemmanager.hpp"


#include <chrono>
#include <map>
#include <memory>
#include <vector>

namespace tyra {

    class World {
    private:
        typedef std::chrono::high_resolution_clock      Time;
        typedef std::chrono::milliseconds               Ms;
        typedef std::chrono::system_clock::time_point   TimePoint;

        bool                m_processing;
        TimePoint           m_prev_update;
        int                 m_delta;

        std::vector<std::unique_ptr<Manager>> m_managers;
        std::map<std::string, EntityId> m_tags;

        void notify_systems();

    protected:
        virtual void preUpdate() { }
        virtual void postUpdate() { }

    public:
        World();
        virtual ~World() { }

        void start()            { m_processing = true; }
        void stop()             { m_processing = false; }
        bool processing() const { return m_processing; }
        void update();

        EntityManager& entity();
        ComponentManager& component();
        SystemManager& system();

        EntityId tag(const std::string&) const;
        void tag(const std::string&, EntityId);
        int delta() const;

        template<typename T, typename... Args> T& add_manager(Args&&... args);
        template<typename T> T& get_manager();
    };

    template<typename T, typename... Args> T& World::add_manager(Args&&... args) {
        static_assert(std::is_base_of<Manager, T>::value, "World::add_manager: T must be derived from Manager.");
        TypeId tid = type_id<Manager, T>::value;
        if (static_cast<size_t>(tid) <= m_managers.size()) {
            m_managers.resize(static_cast<size_t>(tid + 1));
        }
        m_managers[tid] = std::make_unique<T>(std::forward<Args>(args)...);
        m_managers[tid]->m_world = this;
        return get_manager<T>();
    }

    template<typename T> T& World::get_manager() {
        static_assert(std::is_base_of<Manager, T>::value, "World::get_manager: T must be derived from Manager");
        TypeId tid = type_id<Manager, T>::value;
        return static_cast<T&>(*m_managers[tid]);
    }

}


#endif
