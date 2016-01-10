#include <pebble.h>
#include "message_utils.h"
#include "strings.h"

extern TextLayer *tempTextLayer;
extern TextLayer *condTextLayer;

extern char *tempText;
extern struct Strings strings;

/**
 * Maps keys to values found in `appinfo.json` for AppMessage API
 */
typedef enum WeatherKey {
  TEMPERATURE = 0,
  CONDITIONS,
} WeatherKey;

/**
 * Handler for successful AppMessage receiving.
 *
 * @param {DictionaryIterator} iterator iterator that holds message info.
 * @param {void*} context
 */
void messageReceivedHandler(DictionaryIterator *iterator, void *context) {
  Tuple *tempTuple = dict_find(iterator, TEMPERATURE);
  Tuple *condTuple = dict_find(iterator, CONDITIONS);

  snprintf(strings.temp, 13, "Temp: %sF", tempTuple->value->cstring);
  text_layer_set_text(tempTextLayer, strings.temp);
  APP_LOG(APP_LOG_LEVEL_DEBUG, "AppMessage temp: %s\n", tempTuple->value->cstring);

  snprintf(strings.conditions, 31, "Cond: %s", condTuple->value->cstring);
  text_layer_set_text(condTextLayer, strings.conditions);
  APP_LOG(APP_LOG_LEVEL_DEBUG, "AppMessage cond: %s\n", condTuple->value->cstring);
}

/**
 * Handler for failed AppMessage receiving.
 *
 * @param {AppMessageResult} reason The reason the message failed.
 * @param {void*} context
 */
void messageDroppedHandler(AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "AppMessage dropped message: %d\n", reason);
}

