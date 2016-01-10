// #pragma once
#ifndef STRINGS_UTILS_H
#define STRINGS_UTILS_H

/**
 * A better way to manage strings.
 *
 * Provides a struct for storing all strings that will be needed for this pebble
 * app/watchface. Also provides convenience functions for allocating/freeing
 * memory.
 */
typedef struct Strings {
  char *time;
  char *battery;
  char *temp;
  char *conditions;
  char *date;
} Strings;

void createStrings(struct Strings *strs);
void destroyStrings(struct Strings *strs);

#endif
