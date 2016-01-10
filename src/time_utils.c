#include <pebble.h>
#include "strings.h"
#include "time_utils.h"

extern TextLayer *timeTextLayer;
extern TextLayer *dateTextLayer;
extern struct Strings strings;

void tickHandler(struct tm *tickTime, TimeUnits unitsChanged) {
  // set time text layer
  strftime(strings.time, 13, "Time: %H:%M", tickTime);
  text_layer_set_text(timeTextLayer, strings.time);

  // set date text layer
  strftime(strings.date, 15, "Date: %d/%m/%y", tickTime);
  text_layer_set_text(dateTextLayer, strings.date);
}
