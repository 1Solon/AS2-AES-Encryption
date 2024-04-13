#include <stdint.h>
#include <stdio.h>

#ifndef KeyExpansion_h
#define KeyExpansion_h

void KeyExpansion(const uint8_t *inputKey, uint8_t *expandedKeys,
                  const uint8_t *s_box, const uint8_t *r_con, const int keyLen,
                  const int totalKeyLen);

#endif