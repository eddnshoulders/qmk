#ifndef SPACEPAD_H
#define SPACEPAD_H

#include "quantum.h"

// Used to create a keymap using only KC_ prefixed keys
#define XXX KC_NO
#define ___ KC_TRNS
#define LAYOUT( \
  k00, k01, k02, \
  k10, k11, k12, \
                 k23 \
) { \
  {k00, k01, k02, XXX}, \
  {k10, k11, k12, XXX}, \
  {XXX, XXX, XXX, k23} \
}

#endif /* SPACEPAD_H */
