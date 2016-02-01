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

#ifndef TYRA_DEFS_H
#define TYRA_DEFS_H

#include <cstdint>

namespace tyra {

	const std::size_t MAX_ENTITIES = UINT16_MAX;
	const std::size_t MAX_COMPONENT_TYPES = UINT8_MAX;
    const std::size_t MAX_EVENT_TYPES = UINT8_MAX;

	typedef std::uint8_t	TypeId;
	typedef std::uint16_t 	EntityVersion;	// entity_id >> 16
	typedef std::uint16_t 	EntityIndex;	// entity_id & 0xFFFF
	typedef std::uint32_t 	EntityId;		// (entity_version << 16) | entity_index
}

#endif
