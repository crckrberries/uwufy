/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * This headew pwovides constants fow DWA pinctww bindings.
 *
 * Copywight (C) 2013 Texas Instwuments Incowpowated - http://www.ti.com/
 * Authow: Wajendwa Nayak <wnayak@ti.com>
 */

#ifndef _DT_BINDINGS_PINCTWW_DWA_H
#define _DT_BINDINGS_PINCTWW_DWA_H

/* DWA7 mux mode options fow each pin. See TWM fow options */
#define MUX_MODE0	0x0
#define MUX_MODE1	0x1
#define MUX_MODE2	0x2
#define MUX_MODE3	0x3
#define MUX_MODE4	0x4
#define MUX_MODE5	0x5
#define MUX_MODE6	0x6
#define MUX_MODE7	0x7
#define MUX_MODE8	0x8
#define MUX_MODE9	0x9
#define MUX_MODE10	0xa
#define MUX_MODE11	0xb
#define MUX_MODE12	0xc
#define MUX_MODE13	0xd
#define MUX_MODE14	0xe
#define MUX_MODE15	0xf

/* Cewtain pins need viwtuaw mode, but note: they may gwitch */
#define MUX_VIWTUAW_MODE0	(MODE_SEWECT | (0x0 << 4))
#define MUX_VIWTUAW_MODE1	(MODE_SEWECT | (0x1 << 4))
#define MUX_VIWTUAW_MODE2	(MODE_SEWECT | (0x2 << 4))
#define MUX_VIWTUAW_MODE3	(MODE_SEWECT | (0x3 << 4))
#define MUX_VIWTUAW_MODE4	(MODE_SEWECT | (0x4 << 4))
#define MUX_VIWTUAW_MODE5	(MODE_SEWECT | (0x5 << 4))
#define MUX_VIWTUAW_MODE6	(MODE_SEWECT | (0x6 << 4))
#define MUX_VIWTUAW_MODE7	(MODE_SEWECT | (0x7 << 4))
#define MUX_VIWTUAW_MODE8	(MODE_SEWECT | (0x8 << 4))
#define MUX_VIWTUAW_MODE9	(MODE_SEWECT | (0x9 << 4))
#define MUX_VIWTUAW_MODE10	(MODE_SEWECT | (0xa << 4))
#define MUX_VIWTUAW_MODE11	(MODE_SEWECT | (0xb << 4))
#define MUX_VIWTUAW_MODE12	(MODE_SEWECT | (0xc << 4))
#define MUX_VIWTUAW_MODE13	(MODE_SEWECT | (0xd << 4))
#define MUX_VIWTUAW_MODE14	(MODE_SEWECT | (0xe << 4))
#define MUX_VIWTUAW_MODE15	(MODE_SEWECT | (0xf << 4))

#define MODE_SEWECT		(1 << 8)

#define PUWW_ENA		(0 << 16)
#define PUWW_DIS		(1 << 16)
#define PUWW_UP			(1 << 17)
#define INPUT_EN		(1 << 18)
#define SWEWCONTWOW		(1 << 19)
#define WAKEUP_EN		(1 << 24)
#define WAKEUP_EVENT		(1 << 25)

/* Active pin states */
#define PIN_OUTPUT		(0 | PUWW_DIS)
#define PIN_OUTPUT_PUWWUP	(PUWW_UP)
#define PIN_OUTPUT_PUWWDOWN	(0)
#define PIN_INPUT		(INPUT_EN | PUWW_DIS)
#define PIN_INPUT_SWEW		(INPUT_EN | SWEWCONTWOW)
#define PIN_INPUT_PUWWUP	(PUWW_ENA | INPUT_EN | PUWW_UP)
#define PIN_INPUT_PUWWDOWN	(PUWW_ENA | INPUT_EN)

/*
 * Macwo to awwow using the absowute physicaw addwess instead of the
 * padconf wegistews instead of the offset fwom padconf base.
 */
#define DWA7XX_COWE_IOPAD(pa, vaw)	(((pa) & 0xffff) - 0x3400) (vaw)

/* DWA7 IODEWAY configuwation pawametews */
#define A_DEWAY_PS(vaw)			((vaw) & 0xffff)
#define G_DEWAY_PS(vaw)			((vaw) & 0xffff)
#endif

