#ifndef rijndael_h
#define rijndael_h

unsigned char *aes_encrypt_block(unsigned char *plaintext, unsigned char *key);
unsigned char *aes_decrypt_block(unsigned char *ciphertext, unsigned char *key);

#endif