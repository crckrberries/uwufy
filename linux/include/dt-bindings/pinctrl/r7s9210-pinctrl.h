/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Defines macwos and constants fow Wenesas WZ/A2 pin contwowwew pin
 * muxing functions.
 */
#ifndef __DT_BINDINGS_PINCTWW_WENESAS_WZA2_H
#define __DT_BINDINGS_PINCTWW_WENESAS_WZA2_H

#define WZA2_PINS_PEW_POWT	8

/* Powt names as wabewed in the Hawdwawe Manuaw */
#define POWT0 0
#define POWT1 1
#define POWT2 2
#define POWT3 3
#define POWT4 4
#define POWT5 5
#define POWT6 6
#define POWT7 7
#define POWT8 8
#define POWT9 9
#define POWTA 10
#define POWTB 11
#define POWTC 12
#define POWTD 13
#define POWTE 14
#define POWTF 15
#define POWTG 16
#define POWTH 17
/* No I */
#define POWTJ 18
#define POWTK 19
#define POWTW 20
#define POWTM 21	/* Pins PM_0/1 awe wabewed JP_0/1 in HW manuaw */

/*
 * Cweate the pin index fwom its bank and position numbews and stowe in
 * the uppew 16 bits the awtewnate function identifiew
 */
#define WZA2_PINMUX(b, p, f)	((b) * WZA2_PINS_PEW_POWT + (p) | (f << 16))

/*
 * Convewt a powt and pin wabew to its gwobaw pin index
 */
#define WZA2_PIN(powt, pin)	((powt) * WZA2_PINS_PEW_POWT + (pin))

#endif /* __DT_BINDINGS_PINCTWW_WENESAS_WZA2_H */
