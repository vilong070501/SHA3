#include "sha3.h"
#include <iostream>
#include <stddef.h>

SHA3::SHA3(unsigned int len)
    : Keccak()
{
    output_length = len;
    rate = STATE_SIZE - 2 * output_length;
    block_size = rate / 8;
}

std::vector<uint8_t> SHA3::hash(const std::vector<uint8_t> &data)
{
    std::vector<uint8_t> padded_data = padding(data);
    absorb(padded_data);
    return squeeze();
}

void SHA3::print_hash()
{
    Keccak::print_hash(output_length);
}

std::vector<uint8_t> SHA3::padding(const std::vector<uint8_t> &data)
{
    size_t pad_len = block_size - (data.size() % block_size);

    std::vector<uint8_t> padded_data = data;

    padded_data.push_back(0x06);

    while (padded_data.size() < data.size() + pad_len - 1)
    {
        padded_data.push_back(0x00);
    }

    padded_data.push_back(0x80);

    return padded_data;
}

void SHA3::absorb(const std::vector<uint8_t> &padded_data)
{
    size_t num_blocks = padded_data.size() / block_size;

    for (size_t i = 0; i < num_blocks; ++i)
    {
        for (size_t j = 0; j < block_size; ++j)
        {
            size_t row_index = j / 8;
            size_t shift = (j % 8) * 8;

            hash_buffer[row_index] ^= 
                static_cast<uint64_t> (padded_data[i * block_size + j]) << shift;
        }

        keccak_f();
    }
}

std::vector<uint8_t> SHA3::squeeze()
{
    std::vector<uint8_t> output(output_length / 8);
    size_t offset = 0;

    while (offset < output.size())
    {
        size_t left_to_hash = std::min(block_size, output.size() - offset);

        for (size_t i = 0; i < left_to_hash; i++)
        {
            size_t row_index = i / 8;
            size_t shift = (i % 8) * 8;

            output[offset + i] = (hash_buffer[row_index] >> shift) & 0xFF;
        }

        offset += left_to_hash;

        if (offset < output.size())
        {
            keccak_f();
        }
    }

    return output;
}