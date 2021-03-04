
/* Copyright 2016 Fredrik Åhs
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

#ifndef TYRA_TYPE_ID_H
#define TYRA_TYPE_ID_H

#include <cstdint>
#include <type_traits>

namespace tyra {

    using TypeId = std::uint8_t;
    const std::size_t MAX_TYPES = UINT8_MAX;

    namespace __details {
        template <typename B> struct type_counter {
            static TypeId next_id;
        };
        template <typename B> TypeId type_counter<B>::next_id = 0;
    }

    template <typename B, typename T> struct type_id {
        static_assert(std::is_base_of<B, T>::value, "type_id: T must be base of B");
        static const TypeId value;
    };
    template <typename B, typename T>
    const TypeId type_id<B, T>::value = __details::type_counter<B>::next_id++;
}
#endif
