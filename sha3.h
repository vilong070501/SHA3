#pragma once

#include "keccak.h"
#include <stddef.h>
#include <vector>

class SHA3 : public Keccak
{
    public:
        SHA3(unsigned int len);
        std::vector<uint8_t> compute(const std::vector<uint8_t> &message);
        void print_hash();

    private:
        unsigned int output_length;
        unsigned int rate;
        unsigned int capacity;
        size_t block_size;

        std::vector<uint8_t> padding(const std::vector<uint8_t> &message);
        void absorb(const std::vector<uint8_t> &padded_message);
        std::vector<uint8_t> squeeze();
};