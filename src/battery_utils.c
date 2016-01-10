#include <pebble.h>
#include "battery_utils.h"
#include "strings.h"

extern TextLayer *batteryTextLayer;
extern struct Strings strings;

/**
 * Handler called when battery state changes.
 *
 * State changes include:
 * - charge level increase/decrease
 * - plugged in or unplugged
 *
 * @param {BatteryChargeState} state Struct that holds current battery info.
 */
void handleBattery(BatteryChargeState state) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Inside #handleBattery\n");

  char isCharging = state.is_charging ? 'V' : 'X';
  snprintf(strings.battery, 17, "Battery: %d (%c)", state.charge_percent, isCharging);
  text_layer_set_text(batteryTextLayer, strings.battery);

  APP_LOG(APP_LOG_LEVEL_DEBUG, "\t%s\n", strings.battery);
}
