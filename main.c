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
    buffer[len-1] = 0; // null term
}

int main(int argc, char *argv[]) {
    int len = DEFAULT_LEN;
    size_t option_idx;
    for (option_idx = 1; option_idx < argc && argv[option_idx][0] == '-'; option_idx++) {
        switch (argv[option_idx][1]) {
            case 'l':
                len = atoi(argv[++option_idx]) + 1;
                if (len <= 0) {
                    printf("%d is an invalid length\n", len);
                    exit(EXIT_FAILURE);
                }
                len = CLAMP_MAX(len, ID_MAX_LEN);
            break;
            default:
                fprintf(stderr, "Usage: %s [-i len]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    srand((unsigned)time(NULL) * getpid());
    char random[ID_MAX_LEN + 1] = {0,};
    gen_random(len, random);
    printf("%s\n", random);
    return 0;
}