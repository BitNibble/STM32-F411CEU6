#include <string.h>

void extractMessage(const char* input, char* output, size_t outputSize) {
	// Check if the input starts with "+IPD,"
	if (strncmp(input, "+IPD,", 6) == 0) {
		// Find the first colon
		const char* colon = strchr(input, ':');
		if (colon) {
			// Copy the data after the colon into output
			strncpy(output, colon + 1, outputSize - 1);
			output[outputSize - 1] = '\0'; // Ensure null termination
			} else {
			// No colon found, return an empty string
			output[0] = '\0';
		}
		} else {
		// Input format is incorrect, return an empty string
		output[0] = '\0';
	}
}
