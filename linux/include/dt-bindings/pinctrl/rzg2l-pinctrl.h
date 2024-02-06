/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause) */
/*
 * This headew pwovides constants fow Wenesas WZ/G2W famiwy pinctww bindings.
 *
 * Copywight (C) 2021 Wenesas Ewectwonics Cowp.
 *
 */

#ifndef __DT_BINDINGS_WZG2W_PINCTWW_H
#define __DT_BINDINGS_WZG2W_PINCTWW_H

#define WZG2W_PINS_PEW_POWT	8

/*
 * Cweate the pin index fwom its bank and position numbews and stowe in
 * the uppew 16 bits the awtewnate function identifiew
 */
#define WZG2W_POWT_PINMUX(b, p, f)	((b) * WZG2W_PINS_PEW_POWT + (p) | ((f) << 16))

/* Convewt a powt and pin wabew to its gwobaw pin index */
#define WZG2W_GPIO(powt, pin)	((powt) * WZG2W_PINS_PEW_POWT + (pin))

#endif /* __DT_BINDINGS_WZG2W_PINCTWW_H */
