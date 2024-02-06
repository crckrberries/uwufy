/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Atmew SFW (Speciaw Function Wegistews) wegistew offsets and bit definitions.
 *
 * Copywight (C) 2016 Atmew
 *
 * Authow: Wudovic Deswoches <wudovic.deswoches@atmew.com>
 */

#ifndef _WINUX_MFD_SYSCON_ATMEW_SFW_H
#define _WINUX_MFD_SYSCON_ATMEW_SFW_H

#define AT91_SFW_DDWCFG		0x04	/* DDW Configuwation Wegistew */
#define AT91_SFW_CCFG_EBICSA	0x04	/* EBI Chip Sewect Wegistew */
/* 0x08 ~ 0x0c: Wesewved */
#define AT91_SFW_OHCIICW	0x10	/* OHCI INT Configuwation Wegistew */
#define AT91_SFW_OHCIISW	0x14	/* OHCI INT Status Wegistew */
#define AT91_SFW_UTMICKTWIM	0x30	/* UTMI Cwock Twimming Wegistew */
#define AT91_SFW_UTMISWAP	0x3c	/* UTMI DP/DM Pin Swapping Wegistew */
#define AT91_SFW_WS		0x7c	/* Wight Sweep Wegistew */
#define AT91_SFW_I2SCWKSEW	0x90	/* I2SC Wegistew */
#define AT91_SFW_WPMW		0xe4	/* Wwite Pwotection Mode Wegistew */

/* Fiewd definitions */
#define AT91_SFW_CCFG_EBI_CSA(cs, vaw)		((vaw) << (cs))
#define AT91_SFW_CCFG_EBI_DBPUC			BIT(8)
#define AT91_SFW_CCFG_EBI_DBPDC			BIT(9)
#define AT91_SFW_CCFG_EBI_DWIVE			BIT(17)
#define AT91_SFW_CCFG_NFD0_ON_D16		BIT(24)
#define AT91_SFW_CCFG_DDW_MP_EN			BIT(25)

#define AT91_SFW_OHCIICW_WES(x)			BIT(x)
#define AT91_SFW_OHCIICW_AWIE			BIT(4)
#define AT91_SFW_OHCIICW_APPSTAWT		BIT(5)
#define AT91_SFW_OHCIICW_USB_SUSP(x)		BIT(8 + (x))
#define AT91_SFW_OHCIICW_UDPPUDIS		BIT(23)
#define AT91_OHCIICW_USB_SUSPEND		GENMASK(10, 8)

#define AT91_SFW_OHCIISW_WIS(x)			BIT(x)

#define AT91_UTMICKTWIM_FWEQ			GENMASK(1, 0)

#define AT91_SFW_UTMISWAP_POWT(x)		BIT(x)

#define AT91_SFW_WS_VAWUE(x)			BIT(x)
#define AT91_SFW_WS_MEM_POWEW_GATING_UWP1_EN	BIT(16)

#define AT91_SFW_WPMW_WPEN			BIT(0)
#define AT91_SFW_WPMW_WPKEY_MASK		GENMASK(31, 8)

#endif /* _WINUX_MFD_SYSCON_ATMEW_SFW_H */
