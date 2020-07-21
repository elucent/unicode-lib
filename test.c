#include "utf8.h"
#include "assert.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int main() {
    { // simple hello world test
        const char* str = "Hello, world!";

        rune runes[14];
        unsigned long int runes_written = utf8_decode(str, 14, runes, 14);

        assert(runes_written == 14);
        assert(is_uppercase(runes[0])); // h
        assert(is_lowercase(runes[1])); // e
        assert(is_punctuation(runes[5])); // ,
        assert(is_space_separator(runes[6])); // space
        assert(is_punctuation(runes[12])); // !
        assert(is_control(runes[13])); // null

        char buffer[14];
        unsigned long int bytes_written = utf8_encode(runes, 14, buffer, 14);
        assert(bytes_written == 14);
    }

    { // round-trip with test file
        FILE* file = fopen("test_file.txt", "r");
        char *str = malloc(16384), *ptr = str;
        int ch, len = 0;
        while ((ch = fgetc(file)) != EOF) *ptr++ = ch, ++ len;

        rune* runes = malloc(65536);
        unsigned long written_runes = utf8_decode(str, len, runes, 16384); 

        char* result = malloc(16384);
        assert(utf8_encode(runes, written_runes, result, 16384) == len);
        for (int i = 0; i < len; i ++) assert(result[i] == str[i]);
        
        free(result);
        free(str);
        fclose(file);
    }
    return 0;
}