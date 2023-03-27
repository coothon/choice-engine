#ifndef STORY_SCENE_H_
#define STORY_SCENE_H_

#include <stdint.h>
#include <stdio.h>

#include "choice.h"

// A list of all the scenes, in any order. Used for unique scene IDs.
enum scenes {
	SCENE_NULL = -1,
	SCENE_START = 0,
	SCENE_START_LEFT,
	SCENE_LEFT_DIE,
	SCENE_START_RIGHT,
	SCENE_RIGHT_DIE,

	SCENE_COUNT,
};

// All the information a scene needs.
typedef struct scene {
	int32_t parent_id;
	int32_t *children_ids;
	int32_t children_count;
	const char *narrative;
	choice_t scene_choice;
} scene;

static const scene forest_story[] = {
	[SCENE_START] =
		{
			SCENE_NULL,
			(int[]){
				SCENE_START_LEFT,
				SCENE_START_RIGHT,
			},
			2,
			"You walk through the forest. The trail splits, forking left and right.",
			CHOICE("Which way do you go?", {"Go left.", STATE_NORMAL},
                   {"Go right.", STATE_NORMAL}),
		},
	[SCENE_START_LEFT] =
		{
			SCENE_START,
			(int[]){
				SCENE_LEFT_DIE,
			},
			1,
			"You decide to head left.",
			CHOICE("Your stomach rumbles.", {"Shit your pants.", STATE_HARD}),
		},
	[SCENE_LEFT_DIE] =
		{
			SCENE_START_LEFT,
			(int[]){SCENE_NULL},
			0,
			"You shit your pants uncontrollably. You shit so hard your bowels fly out.",
			CHOICE("You have died.", {"THE END.", STATE_HARD}),
		},
	[SCENE_START_RIGHT] =
		{
			SCENE_START,
			(int[]){
				SCENE_RIGHT_DIE,
			},
			1,
			"Heading right, your foot hits a rock and you slip.",
			CHOICE("The world lurches.",
                   {"Try to catch yourself on the ground.", STATE_HARD}),
		},
	[SCENE_RIGHT_DIE] =
		{
			SCENE_START_RIGHT,
			(int[]){SCENE_NULL},
			0,
			"Your hands also slip (the ground here is really slippy), and your head hits the floor with a sickening crunch. It is the last thing you hear.",
			CHOICE("You have died.", {"THE END.", STATE_HARD}),
		},
};

#endif // STORY_SCENE_H_
