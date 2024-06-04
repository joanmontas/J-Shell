// Copyright Joan Montas
// All rights reserved.
// License under GNU General Public License v3.0

#ifndef STRING_H
#define STRING_H
#include <stdio.h>
#include <stdlib.h>

typedef struct String {
	size_t size, capacity;
	char *c_string;
} String;

String *string_init_default();
String *string_init_c_string(const char *c_string);

void string_destroy(String *str);

size_t string_compare(String *l_str, String *r_str);
char string_at(String *str, size_t indx);

char string_pop_back(String *str);
size_t string_append_char(String *str, char c);

#endif
