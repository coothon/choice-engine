#ifndef STORY_CHOICE_H_
#define STORY_CHOICE_H_

#include <stdint.h>
#include <stdio.h>

#define USER_PROMPT "-> "

// Keeping it within single-digits.
#define MAX_OPTIONS 9

#define TEXT_HARD "\033[31m"
#define TEXT_BOLD "\033[1m"
#define TEXT_NORMAL "\033[0m"

// Needed to "flush" stdin.
#define DISCARD_STDIN                               \
	do {                                            \
		int c = 0;                                  \
		while ((c = getchar()) != '\n' && c != EOF) \
			;                                       \
	} while (0);

// Choice constructor.
#define CHOICE(choice_context, ...) \
	{                               \
		.context = choice_context,  \
		.options = {                \
			__VA_ARGS__,            \
			{0},                    \
		},                          \
	}

typedef struct option_t option_t;
typedef struct choice_t choice_t;

typedef enum option_state {
	STATE_OFF = 0,
	STATE_HIDDEN,
	STATE_NORMAL,
	STATE_HARD,
	STATE_CHANCE,
	STATE_SPECIAL,
	STATE_MAGIC,
} option_state;

struct option_t {
	const char *text;
	option_state state;
};

struct choice_t {
	const char *context;
	option_t options[MAX_OPTIONS]; // Wasteful, I know.
};

void print_option(uint8_t number, const option_t *option);
void print_option_hard(uint8_t number, const option_t *option);
void emit_choice(const choice_t *choice, int *user_choice);


#endif // STORY_CHOICE_H_
