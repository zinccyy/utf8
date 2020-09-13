#include <utf8.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	int ret = UTF8_ERR_NONE;
	utf8_string_t str;
	const char *data = "SIMPLE utf8 encoded string with extra chars ∮ E⋅da = Q,  n → ∞, ∑ f(i) = ∏ g(i)";
	utf8_string_init(&str);

	utf8_string_from_bytes(&str, (unsigned char *) data, strlen(data));

	unsigned char *c_str = utf8_string_get_C_str(&str);
	fprintf(stdout, "C_STR: %s\n", c_str);
	free(c_str);

	utf8_string_print(&str, stdout);
	fprintf(stdout, "\n");

	utf8_string_free(&str);
	return ret;
}