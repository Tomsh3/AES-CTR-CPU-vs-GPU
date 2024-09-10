# AES Encryption/Decryption Program

# Authors
Tom Shahar
Yinon Coscas

# General description

This project implements AES (Advanced Encryption Standard) encryption and decryption in CTR (Counter) mode. The implementation is split across three files: `aes.h`, `aes.c`, and `test.c`.

## Files

### 1. aes.h

This header file contains the declarations and definitions required for AES encryption and decryption.

- **Constants:**
  - `AES_BLOCKLEN`: Block length in bytes (16 bytes for AES).
  - `AES_KEYLEN`: Key length in bytes (16 bytes for AES-128).
  - `AES_keyExpSize`: Size of the expanded key (176 bytes for AES-128).

- **Structures:**
  - `AES_ctx`: Structure to hold the AES context, including the round keys and the initialization vector (IV).

- **Functions:**
  - `void AES_init_ctx(struct AES_ctx* ctx, const uint8_t* key)`: Initializes the AES context with a key.
  - `void AES_init_ctx_iv(struct AES_ctx* ctx, const uint8_t* key, const uint8_t* iv)`: Initializes the AES context with a key and IV.
  - `void AES_ctx_set_iv(struct AES_ctx* ctx, const uint8_t* iv)`: Sets the IV in the AES context.
  - `void AES_CTR_xcrypt_buffer(struct AES_ctx* ctx, uint8_t* buf, size_t length)`: Encrypts or decrypts a buffer in CTR mode.

### 2. aes.c

This source file contains the implementation of the AES encryption and decryption functions.

- **Private Variables:**
  - `state_t`: Array holding the intermediate results during decryption.
  - `sbox`: Lookup table for the S-box.
  - `Rcon`: Round constant word array.

- **Private Functions:**
  - `static void KeyExpansion(uint8_t* RoundKey, const uint8_t* Key)`: Produces the round keys used in each round to decrypt the states.

- **Public Functions:**
  - `void AES_init_ctx(struct AES_ctx* ctx, const uint8_t* key)`: Initializes the AES context with a key.
  - `void AES_init_ctx_iv(struct AES_ctx* ctx, const uint8_t* key, const uint8_t* iv)`: Initializes the AES context with a key and IV.

### 3. test.c

This source file contains the test functions to verify the AES-CTR encryption and decryption.

- **Functions:**
  - `static void phex(uint8_t* str)`: Prints a hexadecimal representation of a byte array.
  - `static int test_encrypt_ctr(void)`: Tests the AES-CTR encryption.
  - `static int test_decrypt_ctr(void)`: Tests the AES-CTR decryption.
  - `static int test_xcrypt_ctr(const char* xcrypt)`: Tests the AES-CTR encryption or decryption based on the input parameter.
  - `int main(void)`: Main function that runs the tests.

## Usage

1. **Compile the Program:**
   gcc -o aes_test aes.c test.c


2. **Run the Program:**
   ./aes_test


3. **Input and Output Files:**
   - The program reads data from `input.txt` and writes the encrypted data to `output.txt`.

## Notes

- The AES implementation uses a 128-bit key.
- The program measures the time and CPU cycles spent on encryption.
- Ensure that `input.txt` exists in the same directory as the executable before running the program.


