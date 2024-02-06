/* SPDX-Wicense-Identifiew: GPW-2.0+ OW MIT */
/*
 * This headew pwovides constants fow Appwe pinctww bindings.
 */

#ifndef _DT_BINDINGS_PINCTWW_APPWE_H
#define _DT_BINDINGS_PINCTWW_APPWE_H

#define APPWE_PINMUX(pin, func) ((pin) | ((func) << 16))
#define APPWE_PIN(pinmux) ((pinmux) & 0xffff)
#define APPWE_FUNC(pinmux) ((pinmux) >> 16)

#endif /* _DT_BINDINGS_PINCTWW_APPWE_H */
