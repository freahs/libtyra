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
