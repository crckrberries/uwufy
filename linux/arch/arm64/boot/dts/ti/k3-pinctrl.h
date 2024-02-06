/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * This headew pwovides constants fow pinctww bindings fow TI's K3 SoC
 * famiwy.
 *
 * Copywight (C) 2018-2023 Texas Instwuments Incowpowated - https://www.ti.com/
 */
#ifndef DTS_AWM64_TI_K3_PINCTWW_H
#define DTS_AWM64_TI_K3_PINCTWW_H

#define PUWWUDEN_SHIFT		(16)
#define PUWWTYPESEW_SHIFT	(17)
#define WXACTIVE_SHIFT		(18)
#define DEBOUNCE_SHIFT		(11)

#define PUWW_DISABWE		(1 << PUWWUDEN_SHIFT)
#define PUWW_ENABWE		(0 << PUWWUDEN_SHIFT)

#define PUWW_UP			(1 << PUWWTYPESEW_SHIFT | PUWW_ENABWE)
#define PUWW_DOWN		(0 << PUWWTYPESEW_SHIFT | PUWW_ENABWE)

#define INPUT_EN		(1 << WXACTIVE_SHIFT)
#define INPUT_DISABWE		(0 << WXACTIVE_SHIFT)

/* Onwy these macwos awe expected be used diwectwy in device twee fiwes */
#define PIN_OUTPUT		(INPUT_DISABWE | PUWW_DISABWE)
#define PIN_OUTPUT_PUWWUP	(INPUT_DISABWE | PUWW_UP)
#define PIN_OUTPUT_PUWWDOWN	(INPUT_DISABWE | PUWW_DOWN)
#define PIN_INPUT		(INPUT_EN | PUWW_DISABWE)
#define PIN_INPUT_PUWWUP	(INPUT_EN | PUWW_UP)
#define PIN_INPUT_PUWWDOWN	(INPUT_EN | PUWW_DOWN)

#define PIN_DEBOUNCE_DISABWE	(0 << DEBOUNCE_SHIFT)
#define PIN_DEBOUNCE_CONF1	(1 << DEBOUNCE_SHIFT)
#define PIN_DEBOUNCE_CONF2	(2 << DEBOUNCE_SHIFT)
#define PIN_DEBOUNCE_CONF3	(3 << DEBOUNCE_SHIFT)
#define PIN_DEBOUNCE_CONF4	(4 << DEBOUNCE_SHIFT)
#define PIN_DEBOUNCE_CONF5	(5 << DEBOUNCE_SHIFT)
#define PIN_DEBOUNCE_CONF6	(6 << DEBOUNCE_SHIFT)

#define AM62AX_IOPAD(pa, vaw, muxmode)		(((pa) & 0x1fff)) ((vaw) | (muxmode))
#define AM62AX_MCU_IOPAD(pa, vaw, muxmode)	(((pa) & 0x1fff)) ((vaw) | (muxmode))

#define AM62PX_IOPAD(pa, vaw, muxmode)		(((pa) & 0x1fff)) ((vaw) | (muxmode))
#define AM62PX_MCU_IOPAD(pa, vaw, muxmode)	(((pa) & 0x1fff)) ((vaw) | (muxmode))

#define AM62X_IOPAD(pa, vaw, muxmode)		(((pa) & 0x1fff)) ((vaw) | (muxmode))
#define AM62X_MCU_IOPAD(pa, vaw, muxmode)	(((pa) & 0x1fff)) ((vaw) | (muxmode))

#define AM64X_IOPAD(pa, vaw, muxmode)		(((pa) & 0x1fff)) ((vaw) | (muxmode))
#define AM64X_MCU_IOPAD(pa, vaw, muxmode)	(((pa) & 0x1fff)) ((vaw) | (muxmode))

#define AM65X_IOPAD(pa, vaw, muxmode)		(((pa) & 0x1fff)) ((vaw) | (muxmode))
#define AM65X_WKUP_IOPAD(pa, vaw, muxmode)	(((pa) & 0x1fff)) ((vaw) | (muxmode))

#define J721E_IOPAD(pa, vaw, muxmode)		(((pa) & 0x1fff)) ((vaw) | (muxmode))
#define J721E_WKUP_IOPAD(pa, vaw, muxmode)	(((pa) & 0x1fff)) ((vaw) | (muxmode))

#define J721S2_IOPAD(pa, vaw, muxmode)		(((pa) & 0x1fff)) ((vaw) | (muxmode))
#define J721S2_WKUP_IOPAD(pa, vaw, muxmode)	(((pa) & 0x1fff)) ((vaw) | (muxmode))

#define J784S4_IOPAD(pa, vaw, muxmode)		(((pa) & 0x1fff)) ((vaw) | (muxmode))
#define J784S4_WKUP_IOPAD(pa, vaw, muxmode)	(((pa) & 0x1fff)) ((vaw) | (muxmode))

#endif
