#pragma once

/** Single header utf8 processing library, containing:
 * > functions for file reading and processing
 * > structs and functions for manipulating utf8 data
 */

#include <stdio.h>

typedef enum utf8_err_e utf8_err_t;

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

/** UTF8 block structure
 * holds only data (as much needed)
 * functions encode and decode for encoding and decoding bytes
 * size from 1 - 4 bytes
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

/** sets size to 0 */
void utf8_block_init(utf8_block_t *block);
/** allocates new array with as many needed bytes and sets size pointer param to size */
unsigned char *utf8_block_decode(utf8_block_t *block, unsigned char *nbytes);
/** encodes data into an utf8_block_t struct */
int utf8_block_encode(utf8_block_t *block, unsigned char *data, unsigned char nbytes);
/** sets size back to 0 */
void utf8_block_free(utf8_block_t *block);

/** UTF8 string structure
 * - array of utf8 blocks
 * - holds length and size values => speed
 */
struct utf8_string_s {
	// basically a string => whole file
	utf8_block_t *blocks;
	// length of the string => number of characters
	unsigned int block_count;
	// size of the string => number of bytes
	unsigned int size;
};

/** sets all data to 0 */
void utf8_string_init(utf8_string_t *str);
/** parse data into a string type*/
int utf8_string_from_bytes(utf8_string_t *str, unsigned char *data, unsigned int nbytes);
/** prints string to output FILE* */
int utf8_string_print(utf8_string_t *str, FILE *out);
/** frees blocks array and inits again 0 */
void utf8_string_free(utf8_string_t *str);

/** file contains an array of blocks and when opened reads a file into those blocks*/
struct utf8_file_s {
	// holds only string which stores data from a file
	utf8_string_t str;
};

/** init string */
void utf8_file_init(utf8_file_t *file);
/** opens a file and reads it to the string */
int utf8_file_open(utf8_file_t *file, const char *fn);
/** prints file to output FILE* */
int utf8_file_print(utf8_file_t *file, FILE *out);
/** free file string*/
void utf8_file_free(utf8_file_t *file);