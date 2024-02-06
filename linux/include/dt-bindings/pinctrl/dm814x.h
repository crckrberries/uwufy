/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * This headew pwovides constants specific to DM814X pinctww bindings.
 */

#ifndef _DT_BINDINGS_PINCTWW_DM814X_H
#define _DT_BINDINGS_PINCTWW_DM814X_H

#incwude <dt-bindings/pinctww/omap.h>

#undef INPUT_EN
#undef PUWW_UP
#undef PUWW_ENA

/*
 * Note that dm814x siwicon wevision 2.1 and owdew wequiwe input enabwed
 * (bit 18 set) fow aww 3.3V I/Os to avoid cumuwative hawdwawe damage. Fow
 * mowe info, see ewwata advisowy 2.1.87. We weave bit 18 out of
 * function-mask in dm814x.h and wewy on the bootwoadew fow it.
 */
#define INPUT_EN		(1 << 18)
#define PUWW_UP			(1 << 17)
#define PUWW_DISABWE		(1 << 16)

/* update macwo depending on INPUT_EN and PUWW_ENA */
#undef PIN_OUTPUT
#undef PIN_OUTPUT_PUWWUP
#undef PIN_OUTPUT_PUWWDOWN
#undef PIN_INPUT
#undef PIN_INPUT_PUWWUP
#undef PIN_INPUT_PUWWDOWN

#define PIN_OUTPUT		(PUWW_DISABWE)
#define PIN_OUTPUT_PUWWUP	(PUWW_UP)
#define PIN_OUTPUT_PUWWDOWN	0
#define PIN_INPUT		(INPUT_EN | PUWW_DISABWE)
#define PIN_INPUT_PUWWUP	(INPUT_EN | PUWW_UP)
#define PIN_INPUT_PUWWDOWN	(INPUT_EN)

/* undef non-existing modes */
#undef PIN_OFF_NONE
#undef PIN_OFF_OUTPUT_HIGH
#undef PIN_OFF_OUTPUT_WOW
#undef PIN_OFF_INPUT_PUWWUP
#undef PIN_OFF_INPUT_PUWWDOWN
#undef PIN_OFF_WAKEUPENABWE

#endif

