#include "keyExpansion.h"

void KeyExpansion(const uint8_t *inputKey, uint8_t *expandedKeys,
                  const uint8_t *s_box, const uint8_t *r_con, const int keyLen,
                  const int totalKeyLen) {
  int i = 0;
  uint8_t temp[4];

  for (i = 0; i < keyLen; i++) {
    expandedKeys[i] = inputKey[i];
  }

  for (; i < totalKeyLen; i += 4) {
    for (int j = 0; j < 4; j++) {
      temp[j] = expandedKeys[(i - 4) + j];
    }

    if (i % keyLen == 0) {
      // Rotate the 4-byte word
      uint8_t k = temp[0];
      temp[0] = temp[1];
      temp[1] = temp[2];
      temp[2] = temp[3];
      temp[3] = k;

      // Apply S-box substitution
      for (int j = 0; j < 4; j++) {
        temp[j] = s_box[temp[j]];
      }

      // XOR with Rcon
      temp[0] = temp[0] ^
                r_con[i / keyLen - 1];
    }

    for (int j = 0; j < 4; j++) {
      expandedKeys[i + j] = expandedKeys[i - keyLen + j] ^ temp[j];
    }
  }
}