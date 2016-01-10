#include <pebble.h>
#include <stdlib.h>

#include "battery_utils.h"
#include "message_utils.h"
#include "strings.h"
#include "time_utils.h"

struct Strings strings;

// main window data
Window *mainWindow;
Layer *mainLayer;
GRect mainBounds;

// text layers
TextLayer *timeTextLayer;
TextLayer *batteryTextLayer;
TextLayer *tempTextLayer;
TextLayer *condTextLayer;
TextLayer *dateTextLayer;
TextLayer *testTextLayer;

/**
 * Appends `textLayer` with `text` to `parentLayer`.
 *
 * @param {Layer*} parentLayer The layer to append a TextLayer to.
 * @param {TextLayer*} textLayer The TextLayer to append to `parentLayer`.
 * @param {const char*} text The optional text which to set on `textLayer`
 */
void appendTextLayer(Layer *parentLayer, TextLayer *textLayer, const char *text) {
  if (text) {
    text_layer_set_text(textLayer, text);
  }

  layer_add_child(parentLayer, text_layer_get_layer(textLayer));
}

/**
 * Handler for the main window.
 *
 * @param {Window*} window
 */
void mainWindowLoad(Window *window) {
  // allocate memory for display strings
  createStrings(&strings);

  timeTextLayer = text_layer_create(GRect(0, 0, 200, 20));
  batteryTextLayer = text_layer_create(GRect(0, 20, 200, 20));
  tempTextLayer = text_layer_create(GRect(0, 40, 200, 20));
  condTextLayer = text_layer_create(GRect(0, 60, 200, 20));
  dateTextLayer = text_layer_create(GRect(0, 80, 200, 20));
  testTextLayer = text_layer_create(GRect(0, 100, 200, 20));

  mainLayer = window_get_root_layer(mainWindow);
  mainBounds = layer_get_bounds(mainLayer);

  // create text layers
  appendTextLayer(mainLayer, timeTextLayer, "Time:");
  appendTextLayer(mainLayer, batteryTextLayer, "Battery:");
  appendTextLayer(mainLayer, tempTextLayer, "Temp:");
  appendTextLayer(mainLayer, condTextLayer, "Cond:");
  appendTextLayer(mainLayer, dateTextLayer, "Date:");

  // subscribe to battery state service
  battery_state_service_subscribe(handleBattery);

  // peek at battery value to fill text layer until the battery event is fired next
  handleBattery(battery_state_service_peek());

  // subscribe to time service
  tick_timer_service_subscribe(MINUTE_UNIT, tickHandler);

  // subscribe to app message service
  app_message_register_inbox_received(messageReceivedHandler);
  app_message_register_inbox_dropped(messageDroppedHandler);
  app_message_open(64, 0);
}

/**
 * Handler for the main window.
 *
 * @param {Window*} window
 */
void mainWindowUnload(Window *window) {
  destroyStrings(&strings);

  // unsubscribe/deregister to all services
  battery_state_service_unsubscribe();
  tick_timer_service_unsubscribe();
  app_message_deregister_callbacks();
}

/**
 * Handler that is called when app get initialized.
 */
void handle_init(void) {
  mainWindow = window_create();

  // set handlers on main window
  window_set_window_handlers(mainWindow, (WindowHandlers) {
    .load = mainWindowLoad,
    .unload = mainWindowUnload
  });

  window_stack_push(mainWindow, true);
}

/**
 * Handler that is called when app get deinitialized.
 */
void handle_deinit(void) {
  text_layer_destroy(timeTextLayer);
  text_layer_destroy(batteryTextLayer);
  text_layer_destroy(tempTextLayer);
  text_layer_destroy(condTextLayer);
  text_layer_destroy(dateTextLayer);
  text_layer_destroy(testTextLayer);

  window_destroy(mainWindow);
}

/**
 * App's main entry point.
 */
int main(void) {
  handle_init();
  app_event_loop();
  handle_deinit();
}
