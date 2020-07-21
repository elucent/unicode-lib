#ifndef __ELUCENT_UTF8_H
#define __ELUCENT_UTF8_H

#include "stdint.h"

// representation of a single unicode character
typedef uint32_t rune;

typedef enum UnicodeCategory_t {
    UNICODE_INVALID = 0,
    UNICODE_CONTROL = 1,
    UNICODE_FORMAT = 2,
    UNICODE_NOT_ASSIGNED = 3,
    UNICODE_PRIVATE_USE = 4,
    UNICODE_SURROGATE = 5,
    UNICODE_CASED_LETTER = 6,
    UNICODE_LOWERCASE_LETTER = 7,
    UNICODE_LETTER_MODIFIER = 8,
    UNICODE_OTHER_LETTER = 9,
    UNICODE_TITLECASE_LETTER = 10,
    UNICODE_UPPERCASE_LETTER = 11,
    UNICODE_SPACING_COMBINING_MARK = 12,
    UNICODE_ENCLOSING_MARK = 13,
    UNICODE_NONSPACING_MARK = 14,
    UNICODE_DECIMAL_NUMBER = 15,
    UNICODE_LETTER_NUMBER = 16,
    UNICODE_OTHER_NUMBER = 17,
    UNICODE_PUNCTUATION_CONNECTOR = 18,
    UNICODE_PUNCTUATION_DASH = 19,
    UNICODE_PUNCTUATION_CLOSE = 20,
    UNICODE_PUNCTUATION_FINAL_QUOTE = 21,
    UNICODE_PUNCTUATION_INITIAL_QUOTE = 22,
    UNICODE_PUNCTUATION_OTHER = 23,
    UNICODE_PUNCTUATION_OPEN = 24,
    UNICODE_CURRENCY_SYMBOL = 25,
    UNICODE_MODIFIER_SYMBOL = 26,
    UNICODE_MATH_SYMBOL = 27,
    UNICODE_OTHER_SYMBOL = 28,
    UNICODE_LINE_SEPARATOR = 29,
    UNICODE_PARAGRAPH_SEPARATOR = 30,
    UNICODE_SPACE_SEPARATOR = 31
} UnicodeCategory;

typedef enum UnicodeError_t {
    NO_ERROR = 0,
    INCORRECT_FORMAT,
    RAN_OUT_OF_BOUNDS,
    BUFFER_TOO_SMALL,
    INVALID_RUNE
} UnicodeError;

// returns the most recent internal error, or NO_ERROR if there was none.
UnicodeError unicode_error();

// returns the length of str in runes
unsigned long int utf8_length(const char* str, unsigned long int str_length);

// decodes str_length bytes from str into runes, and writes up to out_length runes to out.
// returns the number of runes written to out.
unsigned long int utf8_decode(const char* str, unsigned long int str_length, 
                              rune* out, unsigned long int out_length);

// encodes str_length runes from str, writing up to out_length bytes to out.
// returns the number of bytes written to out.
unsigned long int utf8_encode(const rune* str, unsigned long int str_length,
                              char* out, unsigned long int out_length);

// these are todo for now. probably not too hard, right? :-)
unsigned long int utf16_length(const char* str, unsigned long int str_length);
unsigned long int utf16_decode(const char* str, unsigned long int str_length, 
                               rune* out, unsigned long int out_length);
unsigned long int utf16_encode(const rune* str, unsigned long int str_length,
                               char* out, unsigned long int out_length);

int is_other(rune r);
int is_control(rune r);
int is_format(rune r);
int is_not_assigned(rune r);
int is_private_use(rune r);
int is_surrogate(rune r);

int is_letter(rune r);
int is_cased_letter(rune r);
int is_lowercase(rune r);
int is_letter_modifier(rune r);
int is_other_letter(rune r);
int is_titlecase(rune r);
int is_uppercase(rune r);

int is_mark(rune r);
int is_spacing_combining_mark(rune r);
int is_enclosing_mark(rune r);
int is_nonspacing_mark(rune r);

int is_number(rune r);
int is_digit(rune r);
int is_letter_number(rune r);
int is_other_number(rune r);

int is_punctuation(rune r);
int is_connector(rune r);
int is_dash(rune r);
int is_punctuation_close(rune r);
int is_final_quote(rune r);
int is_initial_quote(rune r);
int is_other_punctuation(rune r);
int is_punctuation_open(rune r);

int is_symbol(rune r);
int is_currency_symbol(rune r);
int is_modifier_symbol(rune r);
int is_math_symbol(rune r);
int is_other_symbol(rune r);

int is_separator(rune r);
int is_line_separator(rune r);
int is_paragraph_separator(rune r);
int is_space_separator(rune r);

#endif