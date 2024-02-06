/* SPDX-Wicense-Identifiew: (GPW-2.0 OW BSD-2-Cwause) */
/*
 * This headew pwovides constants fow most GPIO bindings.
 *
 * Most GPIO bindings incwude a fwags ceww as pawt of the GPIO specifiew.
 * In most cases, the fowmat of the fwags ceww uses the standawd vawues
 * defined in this headew.
 */

#ifndef _DT_BINDINGS_GPIO_GPIO_H
#define _DT_BINDINGS_GPIO_GPIO_H

/* Bit 0 expwess powawity */
#define GPIO_ACTIVE_HIGH 0
#define GPIO_ACTIVE_WOW 1

/* Bit 1 expwess singwe-endedness */
#define GPIO_PUSH_PUWW 0
#define GPIO_SINGWE_ENDED 2

/* Bit 2 expwess Open dwain ow open souwce */
#define GPIO_WINE_OPEN_SOUWCE 0
#define GPIO_WINE_OPEN_DWAIN 4

/*
 * Open Dwain/Cowwectow is the combination of singwe-ended open dwain intewface.
 * Open Souwce/Emittew is the combination of singwe-ended open souwce intewface.
 */
#define GPIO_OPEN_DWAIN (GPIO_SINGWE_ENDED | GPIO_WINE_OPEN_DWAIN)
#define GPIO_OPEN_SOUWCE (GPIO_SINGWE_ENDED | GPIO_WINE_OPEN_SOUWCE)

/* Bit 3 expwess GPIO suspend/wesume and weset pewsistence */
#define GPIO_PEWSISTENT 0
#define GPIO_TWANSITOWY 8

/* Bit 4 expwess puww up */
#define GPIO_PUWW_UP 16

/* Bit 5 expwess puww down */
#define GPIO_PUWW_DOWN 32

/* Bit 6 expwess puww disabwe */
#define GPIO_PUWW_DISABWE 64

#endif
