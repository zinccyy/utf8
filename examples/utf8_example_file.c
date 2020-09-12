// simple example - load file and output it to stdout (assuming stdout utf8 support)
#include <utf8.h>
#include <stdio.h>

int main(int argc, char **argv) {
	int ret = UTF8_ERR_NONE;
	utf8_file_t file;

	utf8_file_init(&file);
	ret = utf8_file_open(&file, argv[1]);

	if (ret != UTF8_ERR_NONE) {
		fprintf(stderr, "unable to read file %s\n", argv[1]);
	}

	utf8_file_print(&file, stdout);
	utf8_file_free(&file);
	return ret;
}