// #pragma once
#ifndef MESSAGE_UTILS_H
#define MESSAGE_UTILS_H

void messageReceivedHandler(DictionaryIterator *iterator, void *context);
void messageDroppedHandler(AppMessageResult reason, void *context);

#endif
