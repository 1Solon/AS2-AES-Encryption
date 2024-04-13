<div align="center">

## AS2-AES-Encryption

_Assignment to build a Rijndael-AES implementation in c_

</div>

<div align="center">

![GitHub Repo stars](https://img.shields.io/github/stars/1Solon/AS2-AES-Encryption?style=for-the-badge)
![GitHub forks](https://img.shields.io/github/forks/1Solon/AS2-AES-Encryption?style=for-the-badge)
![GitHub Workflow Status (with event)](https://img.shields.io/github/actions/workflow/status/1Solon/AS2-AES-Encryption/release.yaml?style=for-the-badge&label=Scheduled%20Release)

</div>

This is a simple implementation of the Rijndael-AES encryption algorithm in C. The library exposes two functions:
```c
unsigned char *aes_encrypt_block(unsigned char *plaintext, unsigned char *key);
unsigned char *aes_decrypt_block(unsigned char *ciphertext, unsigned char *key);
```
The `aes_encrypt_block` function takes a 16-byte plaintext block and a 16-byte key, and returns a 16-byte ciphertext block. The `aes_decrypt_block` function takes a 16-byte ciphertext block and a 16-byte key, and returns a 16-byte plaintext block.

## Usage
To use the library, simply include the `libRijndael_lib.so` or `rijndael.h`  header file in your project and link against the `rijndael` library.

## Building
To build the library, simply run the following commands:
```bash
cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=1 && make
```
This will generate the `libRijndael_lib.so` shared library in the `build` directory.

## Testing
To run the tests, simply run the following command:
```bash
pytest
```
If you do not have `pytest` installed, you can install it by running:
```bash
pip install pytest
```

## DevContainer
This project includes a `devcontainer.json` file for use with Visual Studio Code's Remote - Containers extension. To use the devcontainer, simply open the project in Visual Studio Code and click the "Reopen in Container" button that appears in the bottom right corner of the window.

## Acknowledgements
This project makes heavy use of examples from these links, which were invaluable in understanding the Rijndael-AES algorithm:

* [Wikipedia](https://en.wikipedia.org/wiki/Advanced_Encryption_Standard)
* [GeeksForGeeks](https://www.geeksforgeeks.org/advanced-encryption-standard-aes/)
* [Sam Trenholme's C implementation](http://www.samiam.org/key-schedule.html)
* [m3y54m](https://github.com/m3y54m/aes-in-c/blob/main/src/main.c)

For testing, I used the test vectors from the [NIST Cryptographic Algorithm Validation Program](https://csrc.nist.gov/projects/cryptographic-algorithm-validation-program/block-ciphers#AES).

I also used [ircmaxell](https://github.com/ircmaxell/quality-checker/blob/master/tmp/gh_18/PHP-PasswordLib-master/test/Data/Vectors/aes-ecb.test-vectors)'s tests

