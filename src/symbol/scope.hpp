#ifndef __SCOPE_HPP__
#define __SCOPE_HPP__

#include "entries.hpp"

namespace sem {

    class Scope;

    typedef std::shared_ptr<Scope> ScopePtr;

    class Scope {
        public:
            Scope(int level, sem::EntryPtr root);
            int getLevel() const;

        private:
            int level;
            sem::EntryPtr root;
    };


}

#endif // __SCOPE_HPP__
