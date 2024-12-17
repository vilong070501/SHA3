#pragma once

#include <array>
#include <cstdint>

#define STATE_SIZE 1600
#define LANE_SIZE 64
#define NUM_LANES 25
#define NUM_ROUNDS 24

using State = std::array<uint64_t, 25>;

class Keccak {
    public:
        Keccak();
        void process();
        void print_hash(unsigned int output_size) const;
    protected:
        State hash_buffer;

        void keccak_f();
        void theta();
        void rho();
        void pi();
        void chi();
        void iota(int round_index);
};