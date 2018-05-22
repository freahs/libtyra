
#include "componentview.hpp"

namespace tyra {

	/*!
	\brief Method to determine whether this particular view is interested in the ComponentSet \a s
	\details A ComponentView is interested in a ComponentSet when the following conditions are met:
	  - At least one of the three categories (`require one`, `require any` and `exclude`) have at least one Component associated with it
	  - \a s is not empty
	  - \a s contain all Components present in the `require all` category (if any)
	  - \a s contains at least one of the Components present in the `require any` category
	  - \a s does not contain any Components present in the `exclude` category (if any)

	\param s The ComponentSet to offer
	\returns true if this ComponentView are interested in the ComponentSet \a s, false if not
	*/
    bool ComponentView::interested(const ComponentSet& s) {
        if(m_require_all.empty() && m_exclude.empty() && m_require_one.empty()) {
            return false;
        }
        if(!m_require_all.empty() && !s.contains_all(m_require_all)) {
            return false;
        }
        if(!m_exclude.empty() && s.contains_any(m_exclude)) {
            return false;
        }
        if(!m_require_one.empty() && !s.contains_any(m_require_one)) {
            return false;
        }
        if(s.empty()) {
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
