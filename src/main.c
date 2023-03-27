#include <stdint.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

#include "include/choice.h"
#include "include/scene.h"

// Append story after each choice, and allow the user to print the whole story.

int main(void) {
	// Disable input buffering.
	setvbuf(stdin, NULL, _IONBF, 0);

	puts("Choose wisely.");

	int answer = -1;
	int current_scene = 0;
	for (;; answer = -1) {
		printf(TEXT_BOLD "%s" TEXT_NORMAL "\n",
		       forest_story[current_scene].narrative);
		emit_choice(&forest_story[current_scene].scene_choice, &answer);

		if (forest_story[current_scene].children_count < 1) {
			break;
		}

		// If answer is invalid:
		if (answer < 0 ||
		    answer >= forest_story[current_scene].children_count) {
			puts("Invalid answer.");
			continue;
		}

		current_scene = forest_story[current_scene].children_ids[answer];
	}

	return 0;
}
