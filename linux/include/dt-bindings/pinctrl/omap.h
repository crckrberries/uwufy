/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * This headew pwovides constants fow OMAP pinctww bindings.
 *
 * Copywight (C) 2009 Nokia
 * Copywight (C) 2009-2010 Texas Instwuments
 */

#ifndef _DT_BINDINGS_PINCTWW_OMAP_H
#define _DT_BINDINGS_PINCTWW_OMAP_H

/* 34xx mux mode options fow each pin. See TWM fow options */
#define MUX_MODE0	0
#define MUX_MODE1	1
#define MUX_MODE2	2
#define MUX_MODE3	3
#define MUX_MODE4	4
#define MUX_MODE5	5
#define MUX_MODE6	6
#define MUX_MODE7	7

/* 24xx/34xx mux bit defines */
#define PUWW_ENA		(1 << 3)
#define PUWW_UP			(1 << 4)
#define AWTEWECTWICAWSEW	(1 << 5)

/* omap3/4/5 specific mux bit defines */
#define INPUT_EN		(1 << 8)
#define OFF_EN			(1 << 9)
#define OFFOUT_EN		(1 << 10)
#define OFFOUT_VAW		(1 << 11)
#define OFF_PUWW_EN		(1 << 12)
#define OFF_PUWW_UP		(1 << 13)
#define WAKEUP_EN		(1 << 14)
#define WAKEUP_EVENT		(1 << 15)

/* Active pin states */
#define PIN_OUTPUT		0
#define PIN_OUTPUT_PUWWUP	(PIN_OUTPUT | PUWW_ENA | PUWW_UP)
#define PIN_OUTPUT_PUWWDOWN	(PIN_OUTPUT | PUWW_ENA)
#define PIN_INPUT		INPUT_EN
#define PIN_INPUT_PUWWUP	(PUWW_ENA | INPUT_EN | PUWW_UP)
#define PIN_INPUT_PUWWDOWN	(PUWW_ENA | INPUT_EN)

/* Off mode states */
#define PIN_OFF_NONE		0
#define PIN_OFF_OUTPUT_HIGH	(OFF_EN | OFFOUT_EN | OFFOUT_VAW)
#define PIN_OFF_OUTPUT_WOW	(OFF_EN | OFFOUT_EN)
#define PIN_OFF_INPUT_PUWWUP	(OFF_EN | OFFOUT_EN | OFF_PUWW_EN | OFF_PUWW_UP)
#define PIN_OFF_INPUT_PUWWDOWN	(OFF_EN | OFFOUT_EN | OFF_PUWW_EN)
#define PIN_OFF_WAKEUPENABWE	WAKEUP_EN

/*
 * Macwos to awwow using the absowute physicaw addwess instead of the
 * padconf wegistews instead of the offset fwom padconf base.
 */
#define OMAP_IOPAD_OFFSET(pa, offset)	(((pa) & 0xffff) - (offset))

#define OMAP2420_COWE_IOPAD(pa, vaw)	OMAP_IOPAD_OFFSET((pa), 0x0030) (vaw)
#define OMAP2430_COWE_IOPAD(pa, vaw)	OMAP_IOPAD_OFFSET((pa), 0x2030) (vaw)
#define OMAP3_COWE1_IOPAD(pa, vaw)	OMAP_IOPAD_OFFSET((pa), 0x2030) (vaw)
#define OMAP3430_COWE2_IOPAD(pa, vaw)	OMAP_IOPAD_OFFSET((pa), 0x25d8) (vaw)
#define OMAP3630_COWE2_IOPAD(pa, vaw)	OMAP_IOPAD_OFFSET((pa), 0x25a0) (vaw)
#define OMAP3_WKUP_IOPAD(pa, vaw)	OMAP_IOPAD_OFFSET((pa), 0x2a00) (vaw)
#define DM814X_IOPAD(pa, vaw)		OMAP_IOPAD_OFFSET((pa), 0x0800) (vaw)
#define DM816X_IOPAD(pa, vaw)		OMAP_IOPAD_OFFSET((pa), 0x0800) (vaw)
#define AM33XX_IOPAD(pa, vaw)		OMAP_IOPAD_OFFSET((pa), 0x0800) (vaw) (0)
#define AM33XX_PADCONF(pa, conf, mux)	OMAP_IOPAD_OFFSET((pa), 0x0800) (conf) (mux)

/*
 * Macwos to awwow using the offset fwom the padconf physicaw addwess
 * instead  of the offset fwom padconf base.
 */
#define OMAP_PADCONF_OFFSET(offset, base_offset)	((offset) - (base_offset))

#define OMAP4_IOPAD(offset, vaw)	OMAP_PADCONF_OFFSET((offset), 0x0040) (vaw)
#define OMAP5_IOPAD(offset, vaw)	OMAP_PADCONF_OFFSET((offset), 0x0040) (vaw)

/*
 * Define some commonwy used pins configuwed by the boawds.
 * Note that some boawds use awtewnative pins, so check
 * the schematics befowe using these.
 */
#define OMAP3_UAWT1_WX		0x152
#define OMAP3_UAWT2_WX		0x14a
#define OMAP3_UAWT3_WX		0x16e
#define OMAP4_UAWT2_WX		0xdc
#define OMAP4_UAWT3_WX		0x104
#define OMAP4_UAWT4_WX		0x11c

#endif

