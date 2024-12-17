#include "sha3.h"
#include <iostream>
#include <stddef.h>

SHA3::SHA3(unsigned int len)
    : Keccak()
{
    output_length = len;
    rate = STATE_SIZE - 2 * output_length;
    capacity = 2 * output_length;
    block_size = rate / 8;
}

std::vector<uint8_t> SHA3::compute(const std::vector<uint8_t> &message)
{
    auto padded_message = padding(message);
    absorb(padded_message);
    return squeeze();
}

void SHA3::print_hash()
{
    Keccak::print_hash(output_length);
}

std::vector<uint8_t> SHA3::padding(const std::vector<uint8_t> &message)
{
    size_t pad_len = block_size - (message.size() % block_size);
    std::vector<uint8_t> padded_message = message;
    padded_message.push_back(0x06);
    while (padded_message.size() < message.size() + pad_len - 1)
    {
        padded_message.push_back(0x00);
    }
    padded_message.push_back(0x80);
    return padded_message;
}

void SHA3::absorb(const std::vector<uint8_t> &padded_message)
{
    // for (size_t i = 0; i < padded_message.size(); i += block_size)
    // {
    //     size_t block_end = std::min(i + block_size, padded_message.size());
    //     for (size_t j = i; j < block_end; j++)
    //     {
    //         size_t x = (j / 8) % 5;
    //         size_t y = (j / 8) / 5;
    //         size_t shift = (j % 8) * 8;
    //         uint64_t value = static_cast<uint64_t>(padded_message[j]) << shift;
    //         hash_buffer[x][y] ^= value;
    //     }
    //     keccak_f();
    // }
    size_t num_blocks = padded_message.size() / block_size;

    for (size_t i = 0; i < num_blocks; ++i) {
        // XOR chaque octet du bloc dans l'état interne
        for (size_t j = 0; j < block_size; ++j) {
            size_t lane_index = j / 8;  // Index de la "lane"
            size_t shift = (j % 8) * 8;

            hash_buffer[lane_index] ^= 
                (uint64_t)padded_message[i * block_size + j] << shift;
        }

        // Applique Keccak-f à l'état
        keccak_f();
    }
}

std::vector<uint8_t> SHA3::squeeze()
{
    // std::vector<uint8_t> output(output_length / 8);
    // size_t i = 0;

    // //while (i < output.size())
    // //{
    //     for (size_t j = 0; j < block_size && i < output.size(); j++)
    //     {
    //         size_t x = (j / 8) % 5;
    //         size_t y = (j / 8) / 5;
    //         size_t shift = (j % 8) * 8;
    //         uint64_t value = hash_buffer[x][y];
    //         output[i++] = (value >> shift) & 0xFF;
    //     }
    //     //keccak_f();
    // //}
    // return output;
    std::vector<uint8_t> output(output_length / 8);
    size_t offset = 0;

    while (offset < output.size()) {
        size_t to_copy = std::min(block_size, output.size() - offset);

        for (size_t i = 0; i < to_copy; ++i) {
            size_t lane_index = i / 8;
            size_t shift = (i % 8) * 8;

            output[offset + i] = (hash_buffer[lane_index] >> shift) & 0xFF;
        }

        offset += to_copy;

        if (offset < output.size()) {
            keccak_f();  // Continue l'extraction avec une permutation supplémentaire
        }
    }

    return output;
}