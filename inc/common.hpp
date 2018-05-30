#ifndef TYRA_CONFIG_H
#define TYRA_CONFIG_H

#include <cstdint>

namespace tyra {

    const std::size_t MAX_COMPONENT_TYPES = UINT8_MAX;
    const std::size_t MAX_EVENT_TYPES = UINT8_MAX;

#ifndef TYRA_X64
    const std::size_t MAX_ENTITIES = UINT16_MAX;
    typedef std::uint16_t   EntityVersion;  // entity_id >> 16
    typedef std::uint16_t   EntityIndex;    // entity_id & 0xFFFF
    typedef std::uint32_t   EntityId;       // (entity_version << 16) | entity_index
#else
    const std::size_t MAX_ENTITIES = UINT32_MAX;
    typedef std::uint32_t   EntityVersion;  // entity_id >> 32
    typedef std::uint32_t   EntityIndex;    // entity_id & 0xFFFFFFFF
    typedef std::uint64_t   EntityId;       // (entity_version << 32) | entity_index
#endif

    EntityIndex inline eid_to_idx(EntityId id) { return id & MAX_ENTITIES; }
    EntityVersion inline eid_to_ver(EntityId id) { return id >> sizeof(EntityIndex) * 8; }
    EntityId inline eid_from_ver_idx(EntityVersion ver, EntityIndex idx) { return static_cast<EntityId>(ver) << sizeof(EntityIndex) * 8 | idx; }
}

#endif
