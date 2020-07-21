#include "utf8.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int main() {
    // performance test
    FILE* file = fopen("test_file.txt", "r");
    char *str = malloc(16384), *ptr = str;
    int ch, len = 0;
    while ((ch = fgetc(file)) != EOF) *ptr++ = ch, ++ len;

    rune* runes = malloc(65536);
    for (int i = 0; i < 1000000; i ++) {
        unsigned long written_runes = utf8_decode(str, len, runes, 16384); 
        utf8_encode(runes, written_runes, str, 16384);
    }
        
    free(str);
    fclose(file);
    return 0;
}