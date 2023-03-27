#include "include/choice.h"

// Present the user with choices, along with a short preamble, and wait for the
// user's choice. The choice is returned via user_choice, and is the user-chosen
// index. While it does output from 1 (for user-friendliness) it in fact does
// return a valid index (from 0).
void emit_choice(const choice_t *choice, int *user_choice) {
	int needed_scrollback = 0;


	if (!choice)
		goto return_error;

	// Preamble:
	if (choice->context) {
		printf("%s\n", choice->context);
	}

	// Print the option if it is enabled.
	for (uint8_t i = 0, u = 0; i < MAX_OPTIONS; ++i) {
		switch (choice->options[i].state) {
		case STATE_HARD:
			print_option_hard(++u, &choice->options[i]);
			needed_scrollback += 1;
			break;
		case STATE_HIDDEN:
		case STATE_NORMAL:
			// Prefix it because output should start from one.
			print_option(++u, &choice->options[i]);
			needed_scrollback += 1;
		case STATE_OFF:
		default:
			continue;
		}
	}

	printf(USER_PROMPT);

	{
		int result = scanf("%d", user_choice);
		needed_scrollback += 1;
		DISCARD_STDIN
		// EOF means there was trouble getting the number.
		if (result == EOF) {
			goto return_error;
		}
	}
	// Scroll the terminal up.
	if (needed_scrollback)
		printf("\033[%dT", needed_scrollback);

	// Return from 0;
	--(*user_choice);
	return;
return_error:
	*user_choice = -1;
}

void print_option(uint8_t number, const option_t *option) {
	printf("\t%d: %s\n", number, option->text);
}

void print_option_hard(uint8_t number, const option_t *option) {
	printf("\t" TEXT_HARD "%d: %s" TEXT_NORMAL "\n", number, option->text);
}
