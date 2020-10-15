#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "sort.h"

extern void sort(long long *array_to_sort, long long *result, size_t array_length);

int is_prefix(char *big_string, char *small_string) {
	int small_string_length = strlen(small_string);
	int big_string_length = strlen(big_string);
	if (big_string_length < small_string_length) {
		return 0;
	}
	for (int i = 0; i < small_string_length; i++) {
		if (small_string[i] != big_string[i]) {
			return 0;
		}
	}
	return 1;
}

int parse_parameters(long long *from, long long *to, int *from_is_entered, int *to_is_entered, int argc, char *argv[]) {
	const int PARSED_SUCCESSFULLY = 0, TOO_LITTLE_PARAMETERS = -1, TOO_MANY_PARAMETERS = -2, TOO_MANY_DECLARATIONS = -3, NO_CORRECT_PARAMETERS = -4;
	if (argc < 2) {
		return TOO_LITTLE_PARAMETERS;
	}
	if (argc > 3) {
		return TOO_MANY_PARAMETERS;
	}
	for (int i = 1; i < argc; i++) {
		char *current_parameter = argv[i], *end_of_current_parameter = current_parameter + strlen(current_parameter);
		if (is_prefix(current_parameter, "--from=")) {
			if (*from_is_entered) {
				return TOO_MANY_DECLARATIONS;
			}
			*from_is_entered = 1;
			*from = strtoll(current_parameter + strlen("--from="), &end_of_current_parameter, 10);
		}
		if (is_prefix(current_parameter, "--to=")) {
			if (*to_is_entered) {
				return TOO_MANY_DECLARATIONS;
			}
			*to_is_entered = 1;
			*to = strtoll(current_parameter + strlen("--to="), &end_of_current_parameter, 10);
		}
	}
	if (!(*from_is_entered) && !(*to_is_entered)) {
		return NO_CORRECT_PARAMETERS;
	}
	return PARSED_SUCCESSFULLY;
}

int read_array(long long *arr) {
	int array_length = 0;
	const int FAIL = -5;
	long long current_element = 0;
	int reading_result = scanf("%lld", &current_element);
	while (reading_result != EOF) {
		if (reading_result == 1) {
			arr[array_length] = current_element;
			array_length++;
			reading_result = scanf("%lld", &current_element);
		}
		else {
			fprintf(stderr, "Incorrect input\n");
			return FAIL;
		}
	}
	return array_length;
}

int filter_array(long long *arr, long long *from, int from_is_entered, long long *to, int to_is_entered, size_t array_length) {
	int number_of_removed_elements = 0;
	for (size_t i = 0; i < array_length; i++) {
		if (from_is_entered && arr[i] <= *from) {
			fprintf(stdout, "%lld ", arr[i]);
			number_of_removed_elements++;
		}
		else if (to_is_entered && arr[i] >= *to) {
			fprintf(stderr, "%lld ", arr[i]);
			number_of_removed_elements++;
		}
		else {
			arr[i - number_of_removed_elements] = arr[i];
		}
	}
	return array_length - number_of_removed_elements;
}

int count_elements_that_differ(long long *arr1, long long *arr2, size_t array_length) {
	int result = 0;
	for (size_t i = 0; i < array_length; i++) {
		if (arr1[i] != arr2[i]) {
			result++;
		}
	}
	return result;
}

int main(int argc, char *argv[]) {
	long long from, to;
	int from_is_entered = 0, to_is_entered = 0;
	int parsing_parameters_result = parse_parameters(&from, &to, &from_is_entered, &to_is_entered, argc, argv);
	const int PARSED_SUCCESSFULLY = 0;
	if (parsing_parameters_result != PARSED_SUCCESSFULLY) {
		return parsing_parameters_result;
	}
	const size_t MAX_ARRAY_LENGTH = 100;
	long long array[MAX_ARRAY_LENGTH];
	int array_length = read_array(array);
	const int FAILED_TO_READ_ARRAY = -5;
	if (array_length == FAILED_TO_READ_ARRAY) {
		fprintf(stderr, "Failed to read array\n");
		return FAILED_TO_READ_ARRAY;
	}
	array_length = filter_array(array, &from, from_is_entered, &to, to_is_entered, (size_t)array_length);
	long long sorted_array[MAX_ARRAY_LENGTH];
	sort(array, sorted_array, (size_t)array_length);
	return count_elements_that_differ(array, sorted_array, (size_t)array_length);
}