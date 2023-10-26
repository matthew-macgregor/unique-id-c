#include <ctype.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#if _MSC_VER && !__INTEL_COMPILER
#include <process.h>
#else
#include <unistd.h>
#endif

#define EXIT_FAILURE 1
#define ID_MAX_LEN 256
#define DEFAULT_LEN 17

#define CLAMP_MAX(x, max) (((x) <= (max)) ? (x) : (max))
#define CLAMP_MIN(x, min) (((x) >= (min)) ? (x) : (min))

void gen_random(const int len, char* buffer) {
	static const char alphanum[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghkmnopqrstuvwxyz";

	for (int i = 0; i < len; ++i) {
		buffer[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
	}
	buffer[len] = 0; // null term
}

int is_numeric_str(const char *str) {
	for (int i = 0; i < strlen(str); i++) {
	if (!isdigit(str[i])) {
		return 0;
	}
	}

	return 1;
}

int main(int argc, char *argv[]) {
	int len = DEFAULT_LEN;
	size_t option_idx;
	for (option_idx = 1; option_idx < argc; option_idx++) {
		switch (argv[option_idx][1]) {
			case 'l':
				if (option_idx + 1 >= argc) {
					printf("Missing integer argument for option -l\n");
					exit(EXIT_FAILURE);
				}

				char* maybe_len = argv[++option_idx];
				len = atoi(maybe_len);
				if (len <= 0) {
					if (is_numeric_str(maybe_len) == 0) {
						printf("%s is not a valid value\n", maybe_len);
					} else {
						printf("%d is an invalid length\n", len);
					}
					exit(EXIT_FAILURE);
				}
				len = CLAMP_MAX(len, ID_MAX_LEN);
				break;
			default:
				fprintf(stderr, "Usage: %s [-l len]\n", argv[0]);
				exit(EXIT_FAILURE);
		}
	}

	srand((unsigned)time(NULL) * getpid());
	char random[ID_MAX_LEN + 1] = {0,};
	gen_random(len, random);
	printf("%s\n", random);
	return 0;
}
