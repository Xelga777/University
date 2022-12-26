#ifndef _S21_STRING_H_
#define _S21_STRING_H_

#include <stddef.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <math.h>
// #include <locale.h>

typedef int bool;
#define TRUE 1
#define FALSE 0

// struct that saves flags from format during sprintf working
typedef struct flags {
    bool minus;
    bool plus;
    bool space;
    bool grid;
    bool zero;
} flags;


// main string funcs 
size_t s21_strlen(const char *str);
char *s21_strcat(char *dest, const char *src);
char *s21_strcpy(char *dest, const char *src);

// func to implement sprintf
int s21_sprintf(char **str, const char *format, ...);

// it parses the format str and gets flags, width and etc
int working_with_specifier(char **str, char **ch, va_list specifier, char *begin);

// it is called if the letter is met here
int handling_letters(char **str, char *ch, va_list specifier,
                      int *opt_len, int width, flags flags, int accurancy, char *begin);

// it makes str of the requested length based on accurancy
void handling_accurancy(char **str, int *len, int accurancy, char spec);

// it makes str of the requested length based on width
void handling_width(char **str, char *num, int len, int width, flags flags);

// it gets length from % to the last letter
int specif_len(char *sp);

// these funcs handles separate groups of specificators
// for example integer_specif handles d, i, u, etc
void integer_specif(char **str, int width, flags flags, int accurancy, long int value);
void float_specif(char **str, int width, flags flags, int accurancy, long double value);
void o_specif(char **str, int width, flags flags, int accurancy, long int value);
void x_specif(char **str, int width, flags flags, int accurancy, long int value, char whoami);

// addition needed funcs
int itoa(long int n, char *s, flags flags);
int ftoa(long double num, char *s, int accurancy, flags flags);
void reverse_str(char *s);

#endif  // _S21_STRING_H_