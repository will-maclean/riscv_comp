#pragma once

#include <memory>

#include "instructions.hpp"

std::unique_ptr<ISA> isa_rv32i();