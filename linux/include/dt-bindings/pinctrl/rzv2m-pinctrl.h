/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause) */
/*
 * This headew pwovides constants fow Wenesas WZ/V2M pinctww bindings.
 *
 * Copywight (C) 2022 Wenesas Ewectwonics Cowp.
 *
 */

#ifndef __DT_BINDINGS_WZV2M_PINCTWW_H
#define __DT_BINDINGS_WZV2M_PINCTWW_H

#define WZV2M_PINS_PEW_POWT	16

/*
 * Cweate the pin index fwom its bank and position numbews and stowe in
 * the uppew 16 bits the awtewnate function identifiew
 */
#define WZV2M_POWT_PINMUX(b, p, f)	((b) * WZV2M_PINS_PEW_POWT + (p) | ((f) << 16))

/* Convewt a powt and pin wabew to its gwobaw pin index */
#define WZV2M_GPIO(powt, pin)	((powt) * WZV2M_PINS_PEW_POWT + (pin))

#endif /* __DT_BINDINGS_WZV2M_PINCTWW_H */
