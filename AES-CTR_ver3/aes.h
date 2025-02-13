#ifndef _AES_H_
#define _AES_H_

#include <stdint.h>
#include <stddef.h>
// CTR enables encryption in counter-mode.
#ifndef CTR
#define CTR 1
#endif
#define AES128 1
#define AES_BLOCKLEN 16 // Block length in bytes - AES is 128b block only
#define AES_KEYLEN 16   // Key length in bytes
#define AES_keyExpSize 176

struct AES_ctx
{
    uint8_t RoundKey[AES_keyExpSize];
#if defined(CTR) && CTR == 1
    uint8_t Iv[AES_BLOCKLEN];
#endif
};

/* *** General description ***
/*
/* This function initializes the AES context with a key.
/*
/*  *** Input parameters ***
/*
/*  - struct AES_ctx* ctx
/*  - const uint8_t* key
/*
/*  *** Output parameters ***
/*
/*  - None
*/
void AES_init_ctx(struct AES_ctx* ctx, const uint8_t* key);


// 
#if defined(CTR) && CTR == 1

/* *** General description ***
/*
/* This function initializes the AES context with a key.
/*
/*  *** Input parameters ***
/*
/*  - struct AES_ctx* ctx
/*  - const uint8_t* key
*   - const uint8_t* iv
/*
/*  *** Output parameters ***
/*
/*  - None
*/
void AES_init_ctx_iv(struct AES_ctx* ctx, const uint8_t* key, const uint8_t* iv);

/* *** General description ***
/*
/* This function sets the IV in the AES context.
/*
/*  *** Input parameters ***
/*
/*  - struct AES_ctx* ctx
/*  - const uint8_t* iv
/*
/*  *** Output parameters ***
/*
/*  - None
*/
void AES_ctx_set_iv(struct AES_ctx* ctx, const uint8_t* iv);
#endif

#if defined(CTR) && (CTR == 1)

// Same function for encrypting as for decrypting. 
// IV is incremented for every block, and used after encryption as XOR-compliment for output
// Suggesting https://en.wikipedia.org/wiki/Padding_(cryptography)#PKCS7 for padding scheme
// NOTES: you need to set IV in ctx with AES_init_ctx_iv() or AES_ctx_set_iv()
//        no IV should ever be reused with the same key 
void AES_CTR_xcrypt_buffer(struct AES_ctx* ctx, uint8_t* buf, size_t length);

#endif // #if defined(CTR) && (CTR == 1)




#endif // _AES_H_