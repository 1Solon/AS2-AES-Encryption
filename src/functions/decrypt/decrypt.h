#include "../Encrypt/Encrypt.h"
#include <stdint.h>
#include <stdio.h>

#define AES_BLOCK_SIZE 16

#ifndef Decrypt_h
#define Decrypt_h

void Decrypt(uint8_t *input, uint8_t *key, const uint8_t *inv_s_box);

#endif