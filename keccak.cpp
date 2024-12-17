#include "keccak.h"
#include <array>
#include <iostream>
#include <iomanip>
#include <string.h>


const std::array<uint64_t, NUM_ROUNDS> RC = {
    0x0000000000000001L, 0x0000000000008082L, 0x800000000000808aL,
    0x8000000080008000L, 0x000000000000808bL, 0x0000000080000001L,
    0x8000000080008081L, 0x8000000000008009L, 0x000000000000008aL,
    0x0000000000000088L, 0x0000000080008009L, 0x000000008000000aL,
    0x000000008000808bL, 0x800000000000008bL, 0x8000000000008089L,
    0x8000000000008003L, 0x8000000000008002L, 0x8000000000000080L,
    0x000000000000800aL, 0x800000008000000aL, 0x8000000080008081L,
    0x8000000000008080L, 0x0000000080000001L, 0x8000000080008008L
};

const std::array<int, 25> RHO_OFFSETS = {
    0, 1, 62, 28, 27,
    36, 44, 6, 55, 20,
    3, 10, 43, 25, 39,
    41, 45, 15, 21, 8,
    18, 2, 61, 56, 14
};

uint64_t rotate_left(uint64_t value, int offset)
{
    return (value << offset) | (value >> (LANE_SIZE - offset));
}

Keccak::Keccak()
{
    hash_buffer.fill(0);
}

void Keccak::process() {
    keccak_f();
}

// void Keccak::print_hash(unsigned int output_size) const {
//     size_t bytes_printed = 0;

//     for (const auto &row : hash_buffer) {
//         for (const uint64_t lane : row) {
//             for (int i = 0; i < 8 && bytes_printed < output_size; i++) {
//                 uint8_t byte = (lane >> (i * 8)) & 0xFF;
//                 std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)byte;
//                 bytes_printed++;
//             }
//         }
//     }
//     std::cout << std::endl;
// }

void Keccak::print_hash(unsigned int output_size) const {
    for (unsigned int i = 0; i < output_size / 8; ++i) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << ((hash_buffer[i / 8] >> (8 * (i % 8))) & 0xFF);
    }
    std::cout << std::dec << std::endl;
}

void Keccak::theta()
{
    std::array<uint64_t, 5> C = { 0 };
    std::array<uint64_t, 5> D = { 0 };

    for (size_t x = 0; x < 5; ++x) {
        C[x] = hash_buffer[x] ^ hash_buffer[x + 5] ^ hash_buffer[x + 10] ^ hash_buffer[x + 15] ^ hash_buffer[x + 20];
    }

    for (size_t x = 0; x < 5; ++x) {
        D[x] = C[(x + 4) % 5] ^ rotate_left(C[(x + 1) % 5], 1);
    }

    for (size_t x = 0; x < 5; ++x) {
        for (size_t y = 0; y < 5; ++y) {
            hash_buffer[x + 5 * y] ^= D[x];
        }
    }
}

void Keccak::rho()
{
    for (size_t i = 0; i < 25; ++i) {
        hash_buffer[i] = rotate_left(hash_buffer[i], RHO_OFFSETS[i]);
    }
}

void Keccak::pi()
{
    // State tmp_buffer;
    // for (int j = 0; j < 5; j++)
    // {
    //     for (int i = 0; i < 5; i++)
    //     {
    //         tmp_buffer[i + j * 5] = hash_buffer[i + j * 5];
    //     }
    // }

    // int u, v;
    // for (int j = 0; j < 5; j++)
    // {
    //     for (int i = 0; i < 5; i++)
    //     {
    //         u = (0 * i + 1 * j) % 5;
    //         v = (2 * i + 3 * j) % 5;
    //         hash_buffer[u + v * 5] = tmp_buffer[i + 5 * j];
    //     }
    // }
    State tmp_buffer = hash_buffer;
    for (size_t x = 0; x < 5; ++x) {
        for (size_t y = 0; y < 5; ++y) {
            hash_buffer[y + 5 * ((2 * x + 3 * y) % 5)] = tmp_buffer[x + 5 * y];
        }
    }
}

void Keccak::chi()
{
    // for (int j = 0; j < 5; j++)
    // {
    //     for (int i = 0; i < 5; i++)
    //     {
    //         tmp_row[i] = hash_buffer[i + j * 5]
    //                     ^ ((~hash_buffer[j * 5 + ((i + 1) % 5)]) & hash_buffer[j * 5 + ((i + 2) % 5)]);
    //     }
        
    //     for (int i = 0; i < 5; i++)
    //     {
    //         hash_buffer[i + j * 5] = tmp_row[i];
    //     }
    // }
    for (size_t y = 0; y < 5; ++y) {
        uint64_t temp[5];
        for (size_t x = 0; x < 5; ++x) {
            temp[x] = hash_buffer[x + 5 * y];
        }
        for (size_t x = 0; x < 5; ++x) {
            hash_buffer[x + 5 * y] = temp[x] ^ (~temp[(x + 1) % 5] & temp[(x + 2) % 5]);
        }
    }
}

void Keccak::iota(int round_index)
{
    hash_buffer[0] ^= RC[round_index];
}

void Keccak::keccak_f()
{
    for (int i = 0; i < NUM_ROUNDS; i++)
    {
        theta();
        rho();
        pi();
        chi();
        iota(i);
    }
}
