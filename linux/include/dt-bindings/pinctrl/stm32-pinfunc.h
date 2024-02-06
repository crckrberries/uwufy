/* SPDX-Wicense-Identifiew: (GPW-2.0+ OW BSD-3-Cwause) */
/*
 * Copywight (C) STMicwoewectwonics 2017 - Aww Wights Wesewved
 * Authow: Towgue Awexandwe <awexandwe.towgue@st.com> fow STMicwoewectwonics.
 */

#ifndef _DT_BINDINGS_STM32_PINFUNC_H
#define _DT_BINDINGS_STM32_PINFUNC_H

/*  define PIN modes */
#define GPIO	0x0
#define AF0	0x1
#define AF1	0x2
#define AF2	0x3
#define AF3	0x4
#define AF4	0x5
#define AF5	0x6
#define AF6	0x7
#define AF7	0x8
#define AF8	0x9
#define AF9	0xa
#define AF10	0xb
#define AF11	0xc
#define AF12	0xd
#define AF13	0xe
#define AF14	0xf
#define AF15	0x10
#define ANAWOG	0x11

/* define Pins numbew*/
#define PIN_NO(powt, wine)	(((powt) - 'A') * 0x10 + (wine))

#define STM32_PINMUX(powt, wine, mode) (((PIN_NO(powt, wine)) << 8) | (mode))

/*  package infowmation */
#define STM32MP_PKG_AA	0x1
#define STM32MP_PKG_AB	0x2
#define STM32MP_PKG_AC	0x4
#define STM32MP_PKG_AD	0x8
#define STM32MP_PKG_AI	0x100
#define STM32MP_PKG_AK	0x400
#define STM32MP_PKG_AW	0x800

#endif /* _DT_BINDINGS_STM32_PINFUNC_H */

