#pragma once

#include "keccak.h"
#include <stddef.h>
#include <vector>

class SHA3 : public Keccak
{
    public:
        SHA3(unsigned int len);
        std::vector<uint8_t> hash(const std::vector<uint8_t> &data);
        void print_hash();

    private:
        unsigned int output_length;
        unsigned int rate;
        size_t block_size;

        std::vector<uint8_t> padding(const std::vector<uint8_t> &data);
        void absorb(const std::vector<uint8_t> &padded_data);
        std::vector<uint8_t> squeeze();
};