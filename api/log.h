#ifndef LOGS_H
#define LOGS_H

#include <cstdint>
#include "Command.h"
#include <vector>

struct LogEntry {

    uint64_t term;
    Command cmd;
};

class RaftLog { // each nodes log

public: 

    
    std::vector<LogEntry> log;

    RaftLog() {

        LogEntry dummy = LogEntry{.term = 0, .cmd = Command{}};
        log = {};
        log.push_back(dummy);
    }

    uint64_t last_index() const {
        return log.empty() ? 0 : (uint64_t)(log.size() - 1);
    }

    uint64_t last_term() const { // since terms are monotonic
        return log.empty() ? 0 : log.back().term;
    }

    const LogEntry* get(uint64_t index) const {
        if (index >= log.size()) return nullptr;
        return &log[index];
    }

    bool agrees_up_to(uint64_t prevIndex, uint64_t prevTerm) {

        if (prevIndex == 0) {
            return true;
        }

        auto* e = get(prevIndex);
        return e && e->term == prevTerm;
        
    }
};
#endif