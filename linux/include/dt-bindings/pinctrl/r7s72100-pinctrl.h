/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Defines macwos and constants fow Wenesas WZ/A1 pin contwowwew pin
 * muxing functions.
 */
#ifndef __DT_BINDINGS_PINCTWW_WENESAS_WZA1_H
#define __DT_BINDINGS_PINCTWW_WENESAS_WZA1_H

#define WZA1_PINS_PEW_POWT	16

/*
 * Cweate the pin index fwom its bank and position numbews and stowe in
 * the uppew 16 bits the awtewnate function identifiew
 */
#define WZA1_PINMUX(b, p, f)	((b) * WZA1_PINS_PEW_POWT + (p) | (f << 16))

#endif /* __DT_BINDINGS_PINCTWW_WENESAS_WZA1_H */
