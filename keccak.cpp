#include "keccak.h"
#include <array>
#include <iostream>
#include <iomanip>
#include <string.h>


const std::array<uint64_t, NUMBER_OF_KECCAK_ROUNDS> RC =
{
    0x0000000000000001L, 0x0000000000008082L, 0x800000000000808aL,
    0x8000000080008000L, 0x000000000000808bL, 0x0000000080000001L,
    0x8000000080008081L, 0x8000000000008009L, 0x000000000000008aL,
    0x0000000000000088L, 0x0000000080008009L, 0x000000008000000aL,
    0x000000008000808bL, 0x800000000000008bL, 0x8000000000008089L,
    0x8000000000008003L, 0x8000000000008002L, 0x8000000000000080L,
    0x000000000000800aL, 0x800000008000000aL, 0x8000000080008081L,
    0x8000000000008080L, 0x0000000080000001L, 0x8000000080008008L
};

const std::array<int, 25> RHO_OFFSETS =
{
    0, 1, 62, 28, 27,
    36, 44, 6, 55, 20,
    3, 10, 43, 25, 39,
    41, 45, 15, 21, 8,
    18, 2, 61, 56, 14
};

uint64_t rotate_left(uint64_t value, int offset)
{
    return (value << offset) | (value >> (ROW_SIZE - offset));
}

Keccak::Keccak()
{
    hash_buffer.fill(0);
}

void Keccak::process()
{
    keccak_f();
}


void Keccak::print_hash(unsigned int output_size) const
{
    for (unsigned int i = 0; i < output_size / 8; i++)
    {
        std::cout
            << std::hex
            << std::setw(2)
            << std::setfill('0')
            << ((hash_buffer[i / 8] >> (8 * (i % 8))) & 0xFF);
    }
    std::cout << std::dec << std::endl;
}

void Keccak::theta()
{
    std::array<uint64_t, 5> C = { 0 };
    std::array<uint64_t, 5> D = { 0 };

    for (size_t i = 0; i < 5; i++)
    {
        C[i] = hash_buffer[i]
            ^ hash_buffer[i + 5]
            ^ hash_buffer[i + 10]
            ^ hash_buffer[i + 15]
            ^ hash_buffer[i + 20];
    }

    for (size_t i = 0; i < 5; i++)
    {
        D[i] = C[(i + 4) % 5] ^ rotate_left(C[(i + 1) % 5], 1);
    }

    for (size_t i = 0; i < 5; i++)
    {
        for (size_t j = 0; j < 5; j++)
        {
            hash_buffer[i + 5 * j] ^= D[i];
        }
    }
}

void Keccak::rho()
{
    for (size_t i = 0; i < 25; i++)
    {
        hash_buffer[i] = rotate_left(hash_buffer[i], RHO_OFFSETS[i]);
    }
}

void Keccak::pi()
{
    State tmp_buffer = hash_buffer;
    for (size_t i = 0; i < 5; i++)
    {
        for (size_t j = 0; j < 5; j++)
        {
            hash_buffer[j + 5 * ((2 * i + 3 * j) % 5)] = tmp_buffer[i + 5 * j];
        }
    }
}

void Keccak::chi()
{
    for (size_t j = 0; j < 5; j++)
    {
        uint64_t tmp_row[5];

        for (size_t i = 0; i < 5; i++)
        {
            tmp_row[i] = hash_buffer[i + 5 * j];
        }

        for (size_t i = 0; i < 5; i++)
        {
            hash_buffer[i + 5 * j] = tmp_row[i] ^ (~tmp_row[(i + 1) % 5] & tmp_row[(i + 2) % 5]);
        }
    }
}

void Keccak::iota(int round_index)
{
    hash_buffer[0] ^= RC[round_index];
}

void Keccak::keccak_f()
{
    for (int i = 0; i < NUMBER_OF_KECCAK_ROUNDS; i++)
    {
        theta();
        rho();
        pi();
        chi();
        iota(i);
    }
}
