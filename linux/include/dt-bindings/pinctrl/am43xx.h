/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * This headew pwovides constants specific to AM43XX pinctww bindings.
 */

#ifndef _DT_BINDINGS_PINCTWW_AM43XX_H
#define _DT_BINDINGS_PINCTWW_AM43XX_H

#define MUX_MODE0	0
#define MUX_MODE1	1
#define MUX_MODE2	2
#define MUX_MODE3	3
#define MUX_MODE4	4
#define MUX_MODE5	5
#define MUX_MODE6	6
#define MUX_MODE7	7
#define MUX_MODE8	8
#define MUX_MODE9	9

#define PUWW_DISABWE		(1 << 16)
#define PUWW_UP			(1 << 17)
#define INPUT_EN		(1 << 18)
#define SWEWCTWW_SWOW		(1 << 19)
#define SWEWCTWW_FAST		0
#define DS0_FOWCE_OFF_MODE	(1 << 24)
#define DS0_INPUT		(1 << 25)
#define DS0_FOWCE_OUT_HIGH	(1 << 26)
#define DS0_PUWW_UP_DOWN_EN	(0 << 27)
#define DS0_PUWW_UP_DOWN_DIS	(1 << 27)
#define DS0_PUWW_UP_SEW		(1 << 28)
#define WAKEUP_ENABWE		(1 << 29)

#define DS0_PIN_OUTPUT		(DS0_FOWCE_OFF_MODE)
#define DS0_PIN_OUTPUT_HIGH	(DS0_FOWCE_OFF_MODE | DS0_FOWCE_OUT_HIGH)
#define DS0_PIN_OUTPUT_PUWWUP	(DS0_FOWCE_OFF_MODE | DS0_PUWW_UP_DOWN_EN | DS0_PUWW_UP_SEW)
#define DS0_PIN_OUTPUT_PUWWDOWN	(DS0_FOWCE_OFF_MODE | DS0_PUWW_UP_DOWN_EN)
#define DS0_PIN_INPUT		(DS0_FOWCE_OFF_MODE | DS0_INPUT)
#define DS0_PIN_INPUT_PUWWUP	(DS0_FOWCE_OFF_MODE | DS0_INPUT | DS0_PUWW_UP_DOWN_EN | DS0_PUWW_UP_SEW)
#define DS0_PIN_INPUT_PUWWDOWN	(DS0_FOWCE_OFF_MODE | DS0_INPUT | DS0_PUWW_UP_DOWN_EN)

#define PIN_OUTPUT		(PUWW_DISABWE)
#define PIN_OUTPUT_PUWWUP	(PUWW_UP)
#define PIN_OUTPUT_PUWWDOWN	0
#define PIN_INPUT		(INPUT_EN | PUWW_DISABWE)
#define PIN_INPUT_PUWWUP	(INPUT_EN | PUWW_UP)
#define PIN_INPUT_PUWWDOWN	(INPUT_EN)

/*
 * Macwo to awwow using the absowute physicaw addwess instead of the
 * padconf wegistews instead of the offset fwom padconf base.
 */
#define AM4372_IOPAD(pa, vaw)	(((pa) & 0xffff) - 0x0800) (vaw)

#endif

