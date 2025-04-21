#pragma once
#include <cstdint>

class TickTimer {
public:
    TickTimer();

    void configure(uint32_t ticks, uint32_t interrupt_addr);
    void deconfigure();
    void tick();
    bool is_done() const;
    void reset();
    uint32_t get_interrupt_addr() const;

private:
    uint32_t total_ticks;
    uint32_t curr_ticks;
    uint32_t interrupt_addr;
    bool active;
};