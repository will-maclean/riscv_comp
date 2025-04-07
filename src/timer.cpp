#include "timer.hpp"

TickTimer::TickTimer()
    :total_ticks(0), 
     curr_ticks(0),
     active(false)
{}

void TickTimer::configure(uint32_t ticks, uint32_t interrupt_addr) {
    total_ticks = ticks;
    curr_ticks = 0;
    active = true;
    this->interrupt_addr = interrupt_addr;
}

void TickTimer::deconfigure() {
    total_ticks = 0;
    curr_ticks = 0;
    active = false;
}

void TickTimer::tick() {
    if (active && (curr_ticks < total_ticks)) {
        curr_ticks++;
    }
}

bool TickTimer::is_done() const {
    return curr_ticks >= total_ticks && active;
}

void TickTimer::reset() {
    curr_ticks = 0;
}

uint32_t TickTimer::get_interrupt_addr() const {
    return interrupt_addr;
}