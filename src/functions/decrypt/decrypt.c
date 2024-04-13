#include "decrypt.h"

void InvSubBytes(uint8_t state[AES_BLOCK_SIZE], const uint8_t inv_s_box[256]) {
  for (int i = 0; i < 16; ++i) {
    state[i] = inv_s_box[state[i]];
  }
}

void InvShiftRows(uint8_t state[AES_BLOCK_SIZE]) {
  uint8_t temp;

  // Row 1, shift right by 1
  temp = state[13];
  state[13] = state[9];
  state[9] = state[5];
  state[5] = state[1];
  state[1] = temp;

  // Row 2, shift right by 2
  temp = state[14];
  state[14] = state[6];
  state[6] = temp;
  temp = state[10];
  state[10] = state[2];
  state[2] = temp;

  // Row 3, shift right by 3
  temp = state[3];
  state[3] = state[7];
  state[7] = state[11];
  state[11] = state[15];
  state[15] = temp;
}

void InvMixColumns(uint8_t state[AES_BLOCK_SIZE]) {
  uint8_t tmp[AES_BLOCK_SIZE];

  for (int i = 0; i < 4; ++i) {
    tmp[4 * i + 0] =
        (uint8_t)(gmul(0x0e, state[4 * i + 0]) ^ gmul(0x0b, state[4 * i + 1]) ^
                  gmul(0x0d, state[4 * i + 2]) ^ gmul(0x09, state[4 * i + 3]));
    tmp[4 * i + 1] =
        (uint8_t)(gmul(0x09, state[4 * i + 0]) ^ gmul(0x0e, state[4 * i + 1]) ^
                  gmul(0x0b, state[4 * i + 2]) ^ gmul(0x0d, state[4 * i + 3]));
    tmp[4 * i + 2] =
        (uint8_t)(gmul(0x0d, state[4 * i + 0]) ^ gmul(0x09, state[4 * i + 1]) ^
                  gmul(0x0e, state[4 * i + 2]) ^ gmul(0x0b, state[4 * i + 3]));
    tmp[4 * i + 3] =
        (uint8_t)(gmul(0x0b, state[4 * i + 0]) ^ gmul(0x0d, state[4 * i + 1]) ^
                  gmul(0x09, state[4 * i + 2]) ^ gmul(0x0e, state[4 * i + 3]));
  }

  for (int i = 0; i < AES_BLOCK_SIZE; ++i) {
    state[i] = tmp[i];
  }
}

void Decrypt(uint8_t *input, uint8_t *key, const uint8_t *inv_s_box) {
  AddRoundKey(input, key + 10 * AES_BLOCK_SIZE);

  for (int round = 9; round > 0; --round) {
    InvShiftRows(input);
    InvSubBytes(input, inv_s_box);
    AddRoundKey(input, key + round * AES_BLOCK_SIZE);
    InvMixColumns(input);
  }

  InvShiftRows(input);
  InvSubBytes(input, inv_s_box);
  AddRoundKey(input, key);
}
