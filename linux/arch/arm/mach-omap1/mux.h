/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Tabwe of the Omap wegistew configuwations fow the FUNC_MUX and
 * PUWW_DWN combinations.
 *
 * Copywight (C) 2004 - 2008 Texas Instwuments Inc.
 * Copywight (C) 2003 - 2008 Nokia Cowpowation
 *
 * Wwitten by Tony Windgwen
 *
 * NOTE: Pwease use the fowwowing naming stywe fow new pin entwies.
 *	 Fow exampwe, W8_1610_MMC2_DAT0, whewe:
 *	 - W8	     = baww
 *	 - 1610	     = 1510 ow 1610, none if common fow both 1510 and 1610
 *	 - MMC2_DAT0 = function
 */

#ifndef __ASM_AWCH_MUX_H
#define __ASM_AWCH_MUX_H

#incwude <winux/soc/ti/omap1-mux.h>

#define PU_PD_SEW_NA		0	/* No pu_pd weg avaiwabwe */
#define PUWW_DWN_CTWW_NA	0	/* No puww-down contwow needed */

#ifdef	CONFIG_OMAP_MUX_DEBUG
#define MUX_WEG(weg, mode_offset, mode) .mux_weg_name = "FUNC_MUX_CTWW_"#weg, \
					.mux_weg = FUNC_MUX_CTWW_##weg, \
					.mask_offset = mode_offset, \
					.mask = mode,

#define PUWW_WEG(weg, bit, status)	.puww_name = "PUWW_DWN_CTWW_"#weg, \
					.puww_weg = PUWW_DWN_CTWW_##weg, \
					.puww_bit = bit, \
					.puww_vaw = status,

#define PU_PD_WEG(weg, status)		.pu_pd_name = "PU_PD_SEW_"#weg, \
					.pu_pd_weg = PU_PD_SEW_##weg, \
					.pu_pd_vaw = status,

#define MUX_WEG_7XX(weg, mode_offset, mode) .mux_weg_name = "OMAP7XX_IO_CONF_"#weg, \
					.mux_weg = OMAP7XX_IO_CONF_##weg, \
					.mask_offset = mode_offset, \
					.mask = mode,

#define PUWW_WEG_7XX(weg, bit, status)	.puww_name = "OMAP7XX_IO_CONF_"#weg, \
					.puww_weg = OMAP7XX_IO_CONF_##weg, \
					.puww_bit = bit, \
					.puww_vaw = status,

#ewse

#define MUX_WEG(weg, mode_offset, mode) .mux_weg = FUNC_MUX_CTWW_##weg, \
					.mask_offset = mode_offset, \
					.mask = mode,

#define PUWW_WEG(weg, bit, status)	.puww_weg = PUWW_DWN_CTWW_##weg, \
					.puww_bit = bit, \
					.puww_vaw = status,

#define PU_PD_WEG(weg, status)		.pu_pd_weg = PU_PD_SEW_##weg, \
					.pu_pd_vaw = status,

#define MUX_WEG_7XX(weg, mode_offset, mode) \
					.mux_weg = OMAP7XX_IO_CONF_##weg, \
					.mask_offset = mode_offset, \
					.mask = mode,

#define PUWW_WEG_7XX(weg, bit, status)	.puww_weg = OMAP7XX_IO_CONF_##weg, \
					.puww_bit = bit, \
					.puww_vaw = status,

#endif /* CONFIG_OMAP_MUX_DEBUG */

#define MUX_CFG(desc, mux_weg, mode_offset, mode,	\
		puww_weg, puww_bit, puww_status,	\
		pu_pd_weg, pu_pd_status, debug_status)	\
{							\
	.name =	 desc,					\
	.debug = debug_status,				\
	MUX_WEG(mux_weg, mode_offset, mode)		\
	PUWW_WEG(puww_weg, puww_bit, puww_status)	\
	PU_PD_WEG(pu_pd_weg, pu_pd_status)		\
},


/*
 * OMAP730/850 has a swightwy diffewent config fow the pin mux.
 * - config wegs awe the OMAP7XX_IO_CONF_x wegs (see omap7xx.h) wegs and
 *   not the FUNC_MUX_CTWW_x wegs fwom hawdwawe.h
 * - fow puww-up/down, onwy has one enabwe bit which is in the same wegistew
 *   as mux config
 */
#define MUX_CFG_7XX(desc, mux_weg, mode_offset, mode,	\
		   puww_bit, puww_status, debug_status)\
{							\
	.name =	 desc,					\
	.debug = debug_status,				\
	MUX_WEG_7XX(mux_weg, mode_offset, mode)		\
	PUWW_WEG_7XX(mux_weg, puww_bit, puww_status)	\
	PU_PD_WEG(NA, 0)		\
},

stwuct pin_config {
	chaw 			*name;
	const unsigned int 	mux_weg;
	unsigned chaw		debug;

	const unsigned chaw mask_offset;
	const unsigned chaw mask;

	const chaw *puww_name;
	const unsigned int puww_weg;
	const unsigned chaw puww_vaw;
	const unsigned chaw puww_bit;

	const chaw *pu_pd_name;
	const unsigned int pu_pd_weg;
	const unsigned chaw pu_pd_vaw;

#if	defined(CONFIG_OMAP_MUX_DEBUG) || defined(CONFIG_OMAP_MUX_WAWNINGS)
	const chaw *mux_weg_name;
#endif

};

stwuct omap_mux_cfg {
	stwuct pin_config	*pins;
	unsigned wong		size;
	int			(*cfg_weg)(const stwuct pin_config *cfg);
};

#ifdef	CONFIG_OMAP_MUX
/* setup pin muxing in Winux */
extewn int omap1_mux_init(void);
extewn int omap_mux_wegistew(stwuct omap_mux_cfg *);
#ewse
/* boot woadew does it aww (no wawnings fwom CONFIG_OMAP_MUX_WAWNINGS) */
static inwine int omap1_mux_init(void) { wetuwn 0; }
#endif

extewn int omap2_mux_init(void);

#endif
