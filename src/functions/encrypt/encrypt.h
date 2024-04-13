#include <stdint.h>
#include <stdio.h>

#define AES_BLOCK_SIZE 16 // AES block size in bytes

#ifndef encrypt_h
#define encrypt_h

void encrypt(uint8_t* input, uint8_t* key, const uint8_t* s_box);

#endif
