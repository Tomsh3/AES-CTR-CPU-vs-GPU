#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <intrin.h>

#define CTR 1
#define CHUNCK_SIZE 4096

#include "aes.h"

/* *** General description ***
/*
/* This function prints a hexadecimal representation of a byte array.
/*
/*  *** Input parameters ***
/*
/*  - uint8_t* str
/*
/*  *** Output parameters ***
/*
/*  - None
*/

static void phex(uint8_t* str);

/* *** General description ***
/*
/* This function tests the AES-CTR encryption.
/*
/*  *** Input parameters ***
/*
/*  - None
/*
/*  *** Output parameters ***
/*
/*  - int
*/
static int test_encrypt_ctr(void);

/* *** General description ***
/*
/* This function tests the AES-CTR decryption.
/*
/*  *** Input parameters ***
/*
/*  - None
/*
/*  *** Output parameters ***
/*
/*  - int
*/
static int test_decrypt_ctr(void);

/* *** General description ***
/*
/* This is the main function that runs the tests.
/*
/*  *** Input parameters ***
/*
/*  - None
/*
/*  *** Output parameters ***
/*
/*  - int
*/
int main(void)
{
    int exit;

#if defined(AES128)
    printf("\nTesting AES128\n\n");
#endif
    exit = test_encrypt_ctr(); //+ test_decrypt_ctr();
    return exit;
}

/* *** General description ***
/*
/* This function prints a hexadecimal representation of a byte array.
/*
/*  *** Input parameters ***
/*
/*  - uint8_t* str
/*
/*  *** Output parameters ***
/*
/*  - None
*/
static void phex(uint8_t* str)
{
    uint8_t len = 16;
    unsigned char i;
    for (i = 0; i < len; ++i)
        printf("%.2x", str[i]);
    printf("\n");
}

/* *** General description ***
/*
/* This function tests the AES-CTR encryption or decryption based on the input parameter.
/*
/*  *** Input parameters ***
/*
/*  - const char* xcrypt
/*
/*  *** Output parameters ***
/*
/*  - int
*/
static int test_xcrypt_ctr(const char* xcrypt);


static int test_encrypt_ctr(void)
{
    return test_xcrypt_ctr("encrypt");
}

static int test_decrypt_ctr(void)
{
    return test_xcrypt_ctr("decrypt");
}

/* *** General description ***
/*
/* This function tests the AES-CTR encryption or decryption based on the input parameter.
/*
/*  *** Input parameters ***
/*
/*  - const char* xcrypt
/*
/*  *** Output parameters ***
/*
/*  - int
*/
static int test_xcrypt_ctr(const char* xcrypt)
{
#if defined(AES128)
    uint8_t key[16] = { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c };
    
#endif
    uint8_t iv[16] = { 0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xff };

    // Open the file for reading
    FILE *infile = fopen("input8.txt", "rb");
    if (infile == NULL) {
		printf("Error: Could not open file\n");
		return 1;
	}

    // Get the size of the file
    fseek(infile, 0, SEEK_END);
    long filesize = ftell(infile);
    fseek(infile, 0, SEEK_SET);
    printf("Size of the data to be encrypted: %ld bytes\n", filesize);

    // Create a new file for writing
    FILE *outfile = fopen("output.txt", "wb");
    if (outfile == NULL) {
    printf("Error: Could not open file\n");
		return 1;
    }

    //Create buffer to hold the data
    uint8_t in[CHUNCK_SIZE];

    struct AES_ctx ctx;

    // This function initializes the AES context ctx with the 128-bit key key
    AES_init_ctx_iv(&ctx, key, iv);

    // Get the starting cycle count
    unsigned __int64 start = __rdtsc();
    double start_time = clock();



    // Read and encrypt the file in chunks
    size_t bytes_read;
    while((bytes_read = fread(in, 1, CHUNCK_SIZE, infile)) > 0) {
		AES_CTR_xcrypt_buffer(&ctx, in, bytes_read);
		fwrite(in, 1, bytes_read, outfile);
	}

    double end_time = clock();
    // Total time spent to encrypt the data in milliseconds
    double time_spent = (end_time - start_time) / CLOCKS_PER_SEC * 1000;
    // Get the ending cycle count
    unsigned __int64 end = __rdtsc();
    // Compute the difference in cycle counts
    unsigned __int64 cycles_spent = end - start;

    printf("Time spent to encrypt the data: %f milliseconds\n", time_spent);
    printf("Cycles spent to encrypt the data: %llu\n", cycles_spent);
    printf("The AES-CTR 128-bit encryption is done\n");
    fclose(infile);
    fclose(outfile);
    return 0;
}