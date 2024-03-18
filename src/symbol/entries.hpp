#ifndef __ENTRIES_HPP__
#define __ENTRIES_HPP__

#include <memory>

namespace sem {

    class Entry;

    typedef std::shared_ptr<Entry> EntryPtr;
    typedef std::vector<EntryPtr> EntryList;

    class Entry {};

    class EntryFunction : public Entry {};

    class EntryVariable : public Entry {};

    class EntryParameter : public Entry {};

}


#endif // __ENTRIES_HPP__
