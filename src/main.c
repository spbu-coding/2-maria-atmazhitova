#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

extern void sort(long long *array, size_t array_length);

int parse_parameters(long long *from, long long *to, bool *from_is_entered, bool *to_is_entered, int argc, char *argv[]) {
	const int PARSED_SUCCESSFULLY = 0, TOO_LITTLE_PARAMETERS = -1, TOO_MANY_PARAMETERS = -2, TOO_MANY_DECLARATIONS = -3, NO_CORRECT_PARAMETERS = -4;
	const char *from_parameter = "--from=", *to_parameter = "--to=";
	const int from_parameter_length = strlen(from_parameter), to_parameter_length = strlen(to_parameter);
	if (argc < 2) {
		return TOO_LITTLE_PARAMETERS;
	}
	if (argc > 3) {
		return TOO_MANY_PARAMETERS;
	}
	for (int i = 1; i < argc; i++) {
		char *current_parameter = argv[i], *end_of_current_parameter = current_parameter + strlen(current_parameter);
		if (strncmp(current_parameter, from_parameter, from_parameter_length) == 0) {
			if (*from_is_entered) {
				return TOO_MANY_DECLARATIONS;
			}
			*from_is_entered = 1;
			*from = strtoll(current_parameter + from_parameter_length, &end_of_current_parameter, 10);
		}
		if (strncmp(current_parameter, to_parameter, to_parameter_length) == 0) {
			if (*to_is_entered) {
				return TOO_MANY_DECLARATIONS;
			}
			*to_is_entered = 1;
			*to = strtoll(current_parameter + to_parameter_length, &end_of_current_parameter, 10);
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

int filter_array(long long *arr, long long from, bool from_is_entered, long long to, bool to_is_entered, size_t array_length) {
	int number_of_removed_elements = 0;
	for (size_t i = 0; i < array_length; i++) {
		if (from_is_entered && arr[i] <= from && to_is_entered && arr[i] >= to) {
			fprintf(stderr, "%lld ", arr[i]);
			fprintf(stdout, "%lld ", arr[i]);
			number_of_removed_elements++;
		}
		else if (from_is_entered && arr[i] <= from) {
			fprintf(stdout, "%lld ", arr[i]);
			number_of_removed_elements++;
		}
		else if (to_is_entered && arr[i] >= to) {
			fprintf(stderr, "%lld ", arr[i]);
			number_of_removed_elements++;
		}
		else {
			arr[i - number_of_removed_elements] = arr[i];
		}
	}
	return array_length - number_of_removed_elements;
}

void copy_array(long long *array_from, long long *array_to, size_t array_length) {
	for (size_t i = 0; i < array_length; i++) {
		array_to[i] = array_from[i];
	}
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
	bool from_is_entered = 0, to_is_entered = 0;
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
	array_length = filter_array(array, from, from_is_entered, to, to_is_entered, (size_t)array_length);
	long long sorted_array[MAX_ARRAY_LENGTH];
	copy_array(array, sorted_array, (size_t)array_length);
	sort(sorted_array, (size_t)array_length);
	return count_elements_that_differ(array, sorted_array, (size_t)array_length);
}