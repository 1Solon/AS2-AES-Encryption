#include <stdint.h>
#include <stdio.h>

#include "encrypt.h"

#define AES_BLOCK_SIZE 16 // AES block size in bytes

// I hated implementing this, this took me HOURS!
uint8_t gmul(uint8_t x, uint8_t y) {
    uint8_t p = 0;
    uint8_t carry;
    for (int i = 0; i < 8; i++) {
        if (y & 1) { // If the least significant bit of b is set
            p ^= x; // XOR the product
        }
        carry = x & 0x80; // Check if the most significant bit of a is set
        x <<= 1; // Multiply a by x to shift left
        if (carry) { // If there was a carry, perform modulo operation
            x ^= 0x1B;
        }
        y >>= 1; // Divide b by x to shift right
    }
    return p;
}

void print_state(const char* message, uint8_t* state, int len) {
    printf("%s: ", message);
    for (int i = 0; i < len; i++) {
        printf("%02x", state[i]);
    }
    printf("\n");
}

void AddRoundKey(uint8_t input[AES_BLOCK_SIZE], const uint8_t key[AES_BLOCK_SIZE]) {
    printf("Input and Key before AddRoundKey:\n");
    for (int i = 0; i < AES_BLOCK_SIZE; i++) {
        printf("%02x ", input[i]);
    }
    printf("\n");
    for (int i = 0; i < AES_BLOCK_SIZE; i++) {
        printf("%02x ", key[i]);
    }
    printf("\n");

    for (int i = 0; i < AES_BLOCK_SIZE; i++) {
        input[i] ^= key[i];
        printf("%02x ", input[i]); // Print result of XOR operation for each byte
    }
    printf("\n");
}

void SubBytes(uint8_t state[AES_BLOCK_SIZE], const uint8_t s_box[256]) {
    for (int i = 0; i < 16; ++i) {
        state[i] = s_box[state[i]];
    }
}

void ShiftRows(uint8_t state[AES_BLOCK_SIZE]) {
    uint8_t temp;

    // Row 1, shift left by 1
    temp = state[1];
    state[1] = state[5];
    state[5] = state[9];
    state[9] = state[13];
    state[13] = temp;

    // Row 2, shift left by 2
    temp = state[2];
    state[2] = state[10];
    state[10] = temp;
    temp = state[6];
    state[6] = state[14];
    state[14] = temp;

    // Row 3, shift left by 3 (or right by 1)
    temp = state[15];
    state[15] = state[11];
    state[11] = state[7];
    state[7] = state[3];
    state[3] = temp;
}

void MixColumns(uint8_t state[AES_BLOCK_SIZE]) {
    uint8_t tmp[AES_BLOCK_SIZE];

    for (int i = 0; i < 4; ++i) {
        tmp[4*i+0] = (uint8_t) (gmul(0x02, state[4*i+0]) ^ gmul(0x03, state[4*i+1]) ^ state[4*i+2] ^ state[4*i+3]);
        tmp[4*i+1] = (uint8_t) (state[4*i+0] ^ gmul(0x02, state[4*i+1]) ^ gmul(0x03, state[4*i+2]) ^ state[4*i+3]);
        tmp[4*i+2] = (uint8_t) (state[4*i+0] ^ state[4*i+1] ^ gmul(0x02, state[4*i+2]) ^ gmul(0x03, state[4*i+3]));
        tmp[4*i+3] = (uint8_t) (gmul(0x03, state[4*i+0]) ^ state[4*i+1] ^ state[4*i+2] ^ gmul(0x02, state[4*i+3]));
    }
    
    for (int i = 0; i < AES_BLOCK_SIZE; ++i) {
        state[i] = tmp[i];
    }
}


void encrypt(uint8_t* input, uint8_t* key, const uint8_t* s_box) {
    print_state("Initial state", input, AES_BLOCK_SIZE);
    AddRoundKey(input, key);
    print_state("After initial AddRoundKey", input, AES_BLOCK_SIZE);

    for (int round = 1; round < 10; ++round) {
        SubBytes(input, s_box);
        print_state("After SubBytes", input, AES_BLOCK_SIZE);
        ShiftRows(input);
        print_state("After ShiftRows", input, AES_BLOCK_SIZE);
        MixColumns(input);
        print_state("After MixColumns", input, AES_BLOCK_SIZE);
        AddRoundKey(input, key + round * AES_BLOCK_SIZE);
        print_state("After AddRoundKey", input, AES_BLOCK_SIZE);
    }

    SubBytes(input, s_box);
    ShiftRows(input);
    AddRoundKey(input, key + 10 * AES_BLOCK_SIZE);
    print_state("Final state", input, AES_BLOCK_SIZE);
}