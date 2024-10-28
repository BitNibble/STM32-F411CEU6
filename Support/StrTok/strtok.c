#include <stdio.h>
#include <string.h>

#define MAX_TOKENS 10

int main() {
	char input[] = "example,42,7:additional_data"; // Modifiable input string
	char *tokens[MAX_TOKENS]; // Array of pointers to hold token addresses
	int count = 0;

	// Tokenize the input string
	char *token = strtok(input, ",:");
	while (token != NULL && count < MAX_TOKENS) {
		tokens[count++] = token; // Store the pointer to the token
		token = strtok(NULL, ",:");
	}

	// Access and print the tokens
	for (int i = 0; i < count; i++) {
		printf("Token %d: %s at address: %p\n", i + 1, tokens[i], (void*)tokens[i]);
	}

	return 0;
}



#include <stdio.h>
#include <string.h>

#define MAX_TOKENS 10

// Function to tokenize a string
int tokenize_string(char *input, char *tokens[], int max_tokens, const char *delimiters) {
	int count = 0;

	// Get the first token
	char *token = strtok(input, delimiters);
	while (token != NULL && count < max_tokens) {
		tokens[count++] = token; // Store the pointer to the token
		token = strtok(NULL, delimiters); // Get the next token
	}

	return count; // Return the number of tokens found
}

int main() {
	char input[] = "example,42,7:additional_data"; // Modifiable input string
	char *tokens[MAX_TOKENS]; // Array of pointers to hold token addresses

	// Tokenize the string
	int num_tokens = tokenize_string(input, tokens, MAX_TOKENS, ",:");

	// Access and print the tokens
	for (int i = 0; i < num_tokens; i++) {
		printf("Token %d: %s at address: %p\n", i + 1, tokens[i], (void*)tokens[i]);
	}

	return 0;
}



//if(sscanf(oneshot, "%[^,],%d,%d:%s", parse_str0, &parse_int0, &parse_int1, parse_str1) == 4);
//else { parse_str0[0] = 0, parse_int0 = 0; parse_int1 = 0; parse_str1[0] = 0; }



