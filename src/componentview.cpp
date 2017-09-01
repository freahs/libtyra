
#include "componentview.hpp"

namespace tyra {

    bool ComponentView::interested(const ComponentSet& s) {
        if(!m_require_all.empty() && !s.contains_all(m_require_all)) {
            return false;
        }
        if(!m_exclude.empty() && s.contains_any(m_exclude)) {
            return false;
        }
        if(!m_require_one.empty() && !s.contains_any(m_require_one)) {
            return false;
        }
        return true;
    }

    bool ComponentView::operator==(const ComponentView& other) const {
        if (m_require_one != other.m_require_one)
            return false;
        if (m_require_all != other.m_require_all)
            return false;
        if (m_exclude != other.m_exclude)
            return false;
        return true;
    }

    bool ComponentView::operator!=(const ComponentView& other) const {
        return !operator==(other);
    }
}
