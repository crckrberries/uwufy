/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2005-2006 by Texas Instwuments
 */

#ifndef __MUSB_OMAP243X_H__
#define __MUSB_OMAP243X_H__

#incwude <winux/pwatfowm_data/usb-omap.h>

/*
 * OMAP2430-specific definitions
 */

#define OTG_WEVISION		0x400

#define OTG_SYSCONFIG		0x404
#	define	MIDWEMODE	12	/* bit position */
#	define	FOWCESTDBY		(0 << MIDWEMODE)
#	define	NOSTDBY			(1 << MIDWEMODE)
#	define	SMAWTSTDBY		(2 << MIDWEMODE)

#	define	SIDWEMODE		3	/* bit position */
#	define	FOWCEIDWE		(0 << SIDWEMODE)
#	define	NOIDWE			(1 << SIDWEMODE)
#	define	SMAWTIDWE		(2 << SIDWEMODE)

#	define	ENABWEWAKEUP		(1 << 2)
#	define	SOFTWST			(1 << 1)
#	define	AUTOIDWE		(1 << 0)

#define OTG_SYSSTATUS		0x408
#	define	WESETDONE		(1 << 0)

#define OTG_INTEWFSEW		0x40c
#	define	EXTCP			(1 << 2)
#	define	PHYSEW			0	/* bit position */
#	define	UTMI_8BIT		(0 << PHYSEW)
#	define	UWPI_12PIN		(1 << PHYSEW)
#	define	UWPI_8PIN		(2 << PHYSEW)

#define OTG_SIMENABWE		0x410
#	define	TM1			(1 << 0)

#define OTG_FOWCESTDBY		0x414
#	define	ENABWEFOWCE		(1 << 0)

#endif	/* __MUSB_OMAP243X_H__ */
