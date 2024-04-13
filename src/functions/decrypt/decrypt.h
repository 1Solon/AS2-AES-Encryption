#include <stdint.h>
#include <stdio.h>
#include "../encrypt/encrypt.h"

#define AES_BLOCK_SIZE 16 // AES block size in bytes

#ifndef decrypt_h
#define decrypt_h

void decrypt(uint8_t* input, uint8_t* key, const uint8_t* inv_s_box);

#endif