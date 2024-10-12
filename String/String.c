// Copyright Joan Montas
// All rights reserved.
// License under GNU General Public License v3.0

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "./String.h"

String *string_init_default(void)
{
	String *str = malloc(sizeof(String));

	if (str == NULL) {
		fprintf(stderr,
			"ERROR: string_init_default error. Unable to malloc struct string\n");
		return NULL;
	};

	str->size = 0;
	str->capacity = 7;
	str->c_string = malloc(sizeof(char) * 7);
	if (str->c_string != NULL) {
		memset(str->c_string, '\0', sizeof(char) * 7);
		return str;
	};

	fprintf(stderr,
		"ERROR: string_init_default error. Unable to malloc c_string\n");
	free(str);
	return NULL;
}

String *string_init_c_string(const char *c_string)
{
	size_t i = 0u;
	String *str = NULL;

	if (c_string == NULL) {
		fprintf(stderr,
			"ERROR: string_init_c_string error. Given NULL instead of char*\n");
		return NULL;
	}

	str = (String *)malloc(sizeof(String));
	if (str == NULL) {
		fprintf(stderr,
			"ERROR: string_init_c_string error. Unable to malloc String\n");
		return NULL;
	}

	str->size = 0u;
	str->capacity = 1u;

	for (i = 0u; c_string[i] != '\0'; i++) {
		str->capacity = str->capacity + 1;
		str->size = str->size + 1;
	}

	str->c_string = (char *)malloc(sizeof(char) * (str->capacity));
	if (str->c_string == NULL) {
		free(str);
		str = NULL;
		fprintf(stderr,
			"ERROR: string_init_c_string error. Unable to malloc c_string\n");
		return NULL;
	}
	memset(str->c_string, '\0', sizeof(char) * (str->capacity));

	for (i = 0u; i < str->capacity; i++) {
		str->c_string[i] = c_string[i];
	}

	return str;
}

void string_destroy(String *str)
{
	if (str == NULL) {
		fprintf(stderr,
			"ERROR: string_destroy error. Tried destroying NULL\n");
		return;
	}

	free(str->c_string);
	free(str);
}

size_t string_compare(String *l_str, String *r_str)
{
	size_t i = 0u;

	if (l_str == NULL || r_str == NULL) {
		fprintf(stderr,
			"ERROR: string_compare error. Tried comparing NULL\n");
		return 0u;
	}

	if (l_str->size != r_str->size) {
		return 0u;
	}

	for (i = 0u; i < l_str->size; i++) {
		if (l_str->c_string[i] != r_str->c_string[i]) {
			return 0u;
		}
	}
	return 1u;
}

char string_at(String *str, size_t indx)
{
	if (str == NULL) {
		fprintf(stderr, "ERROR: string_at error. Tried at-ing NULL\n");
		return '\0';
	}

	if (indx >= str->size) {
		fprintf(stderr, "ERROR: string_at error. Index out of range\n");
		return '\0';
	}
	return str->c_string[indx];
}

char string_pop_back(String *str)
{
	char c = '\0';

	if (str == NULL) {
		fprintf(stderr,
			"ERROR: string_pop_back error. Tried pop-ing NULL\n");
		return '\0';
	}

	if (str->size == 0u) {
		fprintf(stderr, "ERROR: string_pop_back error. Out of range\n");
		return '\0';
	}

	c = str->c_string[str->size - 1u];
	str->c_string[str->size - 1u] = '\0';
	str->size--;

	return c;
}

size_t string_append_char(String *str, char c)
{
	size_t i = 0u;
	char *temp_c_string = NULL;

	if (str == NULL) {
		fprintf(stderr,
			"ERROR: string_append_char error. Tried append-ing NULL\n");
		return 0u;
	}

	str->size++;
	if (str->size < str->capacity) {
		str->c_string[str->size - 1u] = c;
		return 1u;
	}

	str->size--;
	temp_c_string = (char *)malloc(sizeof(char) * str->capacity * 2);
	if (temp_c_string == NULL) {
		fprintf(stderr,
			"ERROR: string_append_char error. Could not allocate memory for temp_c_string\n");
		return 0u;
	}
	memset(temp_c_string, '\0', sizeof(char) * str->capacity * 2);

	for (i = 0u; i < str->size; i++) {
		temp_c_string[i] = str->c_string[i];
	}
	str->capacity = str->capacity * 2;

	free(str->c_string);
	str->c_string = temp_c_string;

	str->c_string[str->size] = c;
	str->size++;

	return 1u;
}

char *string_get_c_string(String *str)
{
	if (str == NULL) {
		fprintf(stderr,
			"ERROR: string_get_c_string error. Given String is NULL\n");
		return NULL;
	}

	return str->c_string;
}

int string_concat(String *str_left, String *str_right)
{
	size_t i = 0u;
	size_t rslt = 0;

	if (str_left == NULL || str_right == NULL) {
		fprintf(stderr,
			"ERROR: string_concat error. Given String is NULL\n");
		return -1;
	}

	for (i = 0u; i < str_right->size; i++) {
		rslt = string_append_char(str_left, string_at(str_right, i));

		if (rslt == 0) {
			fprintf(stderr,
				"Error: string_concat. Error while appending char\n");
			return -1;
		}
	}

	return 1;
}