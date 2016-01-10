#include <stdlib.h>
#include <string.h>
#include "strings.h"

const char *TIME_PLACEHOLDER = "Time:        ";
const char *BATTERY_PLACEHOLDER = "Battery:         ";
const char *TEMP_PLACEHOLDER = "Temp:        ";
const char *CONDITIONS_PLACEHOLDER = "Cond:                          ";
const char *DATE_PLACEHOLDER = "Date:          ";

/**
 * Allocates a string with the contents of `src`.
 *
 * @param {const char*} src A string to copy from.
 * @return char*
 */
char *initString(const char *src) {
  int length = strlen(src);
  char *dest;

  dest = malloc(length);
  strcpy(dest, src);

  return dest;
};

/**
 * Allocates memory for all strings in the given `strs` struct.
 *
 * @param {Strings*} strs
 */
void createStrings(struct Strings *strs) {
  strs->time = initString(TIME_PLACEHOLDER);
  strs->battery = initString(BATTERY_PLACEHOLDER);
  strs->temp = initString(TEMP_PLACEHOLDER);
  strs->conditions = initString(CONDITIONS_PLACEHOLDER);
  strs->date = initString(DATE_PLACEHOLDER);
}

/**
 * Frees memory for all strings in the given `strs` struct.
 *
 * @param {Strings*} strs
 */
void destroyStrings(struct Strings *strs) {
  free(strs->time);
  free(strs->battery);
  free(strs->temp);
  free(strs->conditions);
  free(strs->date);
}
