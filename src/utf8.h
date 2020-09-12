#pragma once

/**
 * @file utf8.h
 * @author Mateo Cindric
 * @date 12 Sep 2020
 * @brief Header file of the library containing all structs and manipulation functions for those structs.
 *
 * Single header utf8 processing library
 * - functions for file reading and processing
 * - structs for manipulating utf8 data (strings, blocks, files...)
 */

#include <stdio.h>

typedef enum utf8_err_e utf8_err_t;

/**
 * @brief Used in functions that may return an error - all functions which return int return some of these options.
 */
enum utf8_err_e {
	UTF8_ERR_NONE = 0,
	UTF8_ERR_FOPEN,
	UTF8_ERR_ALLOC,
	UTF8_ERR_NBYTES,
	UTF8_ERR_INTERNAL,
};

typedef struct utf8_block_s utf8_block_t;
typedef struct utf8_string_s utf8_string_t;
typedef struct utf8_file_s utf8_file_t;

/** @brief UTF-8 block of data

    1 - 4 bytes in size
    @author Mateo Cindric
    @date September 2020
*/
struct utf8_block_s {
	union {
		unsigned char b1;
		unsigned char b2[2];
		unsigned char b3[3];
		unsigned char b4[4];
	} data;
	unsigned char nbytes;
};

/** Initialize block with size 0
    @param block block to init
*/
void utf8_block_init(utf8_block_t *block);

/** Decode an UTF-8 block of data
    @param block block to decode
    @param nbytes variable to which the number of decoded bytes are stored
    @return data decoded data with nbytes
*/
unsigned char *utf8_block_decode(utf8_block_t *block, unsigned char *nbytes);

/** Encode an UTF-8 block of data
    @param block block to encode
    @param data data to encode into a block
		@param nbytes number of bytes to encode
    @return error if any occurs
*/
int utf8_block_encode(utf8_block_t *block, unsigned char *data, unsigned char nbytes);

/** Free the block - basically init again
    @param block block to free
*/
void utf8_block_free(utf8_block_t *block);

/** @brief UTF-8 string of data, basically array of blocks
    @author Mateo Cindric
    @date September 2020
*/
struct utf8_string_s {
	// array of blocks
	utf8_block_t *blocks;
	// length of the string; number of characters
	unsigned int block_count;
	// size of the string; number of bytes
	unsigned int size;
};

/** Initialize string fields with 0
    @param str string to init
*/
void utf8_string_init(utf8_string_t *str);

/** Load and initialize all blocks and create a string
    @param str string to create
    @param data C-string which gets converted to UTF-8 data
		@param nbytes number of bytes that data occupies
    @return error if any occurs
*/
int utf8_string_from_bytes(utf8_string_t *str, unsigned char *data, unsigned int nbytes);

/** Print a string to a desired output FILE*
    @param str string to print
    @param out output file
    @return error if any occurs
*/
int utf8_string_print(utf8_string_t *str, FILE *out);

/** Free blocks and init back to 0
    @param str string to free
*/
void utf8_string_free(utf8_string_t *str);

/** @brief UTF-8 file type
    @author Mateo Cindric
    @date September 2020
*/
struct utf8_file_s {
	// holds only string which stores data from a file
	utf8_string_t str;
};

/** Initialize file fields
    @param file file to init
*/
void utf8_file_init(utf8_file_t *file);

/** Open file and read it as UTF-8
    @param file UTF-8 file struct 
		@param fn filename
		@return error if any occurs
*/
int utf8_file_open(utf8_file_t *file, const char *fn);

/** Print utf8 file to a desired output
    @param file UTF-8 file struct to print
		@param out output file
		@return error if any occurs
*/
int utf8_file_print(utf8_file_t *file, FILE *out);

/** Free file fields
    @param file file to free
*/
void utf8_file_free(utf8_file_t *file);