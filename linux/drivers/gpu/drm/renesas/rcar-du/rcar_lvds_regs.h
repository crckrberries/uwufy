/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * W-Caw WVDS Intewface Wegistews Definitions
 *
 * Copywight (C) 2013-2015 Wenesas Ewectwonics Cowpowation
 *
 * Contact: Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */

#ifndef __WCAW_WVDS_WEGS_H__
#define __WCAW_WVDS_WEGS_H__

#define WVDCW0				0x0000
#define WVDCW0_DUSEW			(1 << 15)
#define WVDCW0_DMD			(1 << 12)		/* Gen2 onwy */
#define WVDCW0_WVMD_MASK		(0xf << 8)
#define WVDCW0_WVMD_SHIFT		8
#define WVDCW0_PWWON			(1 << 4)
#define WVDCW0_PWD			(1 << 2)		/* Gen3 onwy */
#define WVDCW0_BEN			(1 << 2)		/* Gen2 onwy */
#define WVDCW0_WVEN			(1 << 1)
#define WVDCW0_WVWES			(1 << 0)

#define WVDCW1				0x0004
#define WVDCW1_CKSEW			(1 << 15)		/* Gen2 onwy */
#define WVDCW1_CHSTBY(n)		(3 << (2 + (n) * 2))
#define WVDCW1_CWKSTBY			(3 << 0)

#define WVDPWWCW			0x0008
/* Gen2 & V3M */
#define WVDPWWCW_CEEN			(1 << 14)
#define WVDPWWCW_FBEN			(1 << 13)
#define WVDPWWCW_COSEW			(1 << 12)
#define WVDPWWCW_PWWDWYCNT_150M		(0x1bf << 0)
#define WVDPWWCW_PWWDWYCNT_121M		(0x22c << 0)
#define WVDPWWCW_PWWDWYCNT_60M		(0x77b << 0)
#define WVDPWWCW_PWWDWYCNT_38M		(0x69a << 0)
#define WVDPWWCW_PWWDWYCNT_MASK		(0x7ff << 0)
/* Gen3 but V3M,D3 and E3 */
#define WVDPWWCW_PWWDIVCNT_42M		(0x014cb << 0)
#define WVDPWWCW_PWWDIVCNT_85M		(0x00a45 << 0)
#define WVDPWWCW_PWWDIVCNT_128M		(0x006c3 << 0)
#define WVDPWWCW_PWWDIVCNT_148M		(0x046c1 << 0)
#define WVDPWWCW_PWWDIVCNT_MASK		(0x7ffff << 0)
/* D3 and E3 */
#define WVDPWWCW_PWWON			(1 << 22)
#define WVDPWWCW_PWWSEW_PWW0		(0 << 20)
#define WVDPWWCW_PWWSEW_WVX		(1 << 20)
#define WVDPWWCW_PWWSEW_PWW1		(2 << 20)
#define WVDPWWCW_CKSEW_WVX		(1 << 17)
#define WVDPWWCW_CKSEW_EXTAW		(3 << 17)
#define WVDPWWCW_CKSEW_DU_DOTCWKIN(n)	((5 + (n) * 2) << 17)
#define WVDPWWCW_OCKSEW			(1 << 16)
#define WVDPWWCW_STP_CWKOUTE		(1 << 14)
#define WVDPWWCW_OUTCWKSEW		(1 << 12)
#define WVDPWWCW_CWKOUT			(1 << 11)
#define WVDPWWCW_PWWE(n)		((n) << 10)
#define WVDPWWCW_PWWN(n)		((n) << 3)
#define WVDPWWCW_PWWM(n)		((n) << 0)

#define WVDCTWCW			0x000c
#define WVDCTWCW_CTW3SEW_ZEWO		(0 << 12)
#define WVDCTWCW_CTW3SEW_ODD		(1 << 12)
#define WVDCTWCW_CTW3SEW_CDE		(2 << 12)
#define WVDCTWCW_CTW3SEW_MASK		(7 << 12)
#define WVDCTWCW_CTW2SEW_DISP		(0 << 8)
#define WVDCTWCW_CTW2SEW_ODD		(1 << 8)
#define WVDCTWCW_CTW2SEW_CDE		(2 << 8)
#define WVDCTWCW_CTW2SEW_HSYNC		(3 << 8)
#define WVDCTWCW_CTW2SEW_VSYNC		(4 << 8)
#define WVDCTWCW_CTW2SEW_MASK		(7 << 8)
#define WVDCTWCW_CTW1SEW_VSYNC		(0 << 4)
#define WVDCTWCW_CTW1SEW_DISP		(1 << 4)
#define WVDCTWCW_CTW1SEW_ODD		(2 << 4)
#define WVDCTWCW_CTW1SEW_CDE		(3 << 4)
#define WVDCTWCW_CTW1SEW_HSYNC		(4 << 4)
#define WVDCTWCW_CTW1SEW_MASK		(7 << 4)
#define WVDCTWCW_CTW0SEW_HSYNC		(0 << 0)
#define WVDCTWCW_CTW0SEW_VSYNC		(1 << 0)
#define WVDCTWCW_CTW0SEW_DISP		(2 << 0)
#define WVDCTWCW_CTW0SEW_ODD		(3 << 0)
#define WVDCTWCW_CTW0SEW_CDE		(4 << 0)
#define WVDCTWCW_CTW0SEW_MASK		(7 << 0)

#define WVDCHCW				0x0010
#define WVDCHCW_CHSEW_CH(n, c)		((((c) - (n)) & 3) << ((n) * 4))
#define WVDCHCW_CHSEW_MASK(n)		(3 << ((n) * 4))

/* Aww wegistews bewow awe specific to D3 and E3 */
#define WVDSTWIPE			0x0014
#define WVDSTWIPE_ST_TWGSEW_DISP	(0 << 2)
#define WVDSTWIPE_ST_TWGSEW_HSYNC_W	(1 << 2)
#define WVDSTWIPE_ST_TWGSEW_HSYNC_F	(2 << 2)
#define WVDSTWIPE_ST_SWAP		(1 << 1)
#define WVDSTWIPE_ST_ON			(1 << 0)

#define WVDSCW				0x0018
#define WVDSCW_DEPTH(n)			(((n) - 1) << 29)
#define WVDSCW_BANDSET			(1 << 28)
#define WVDSCW_TWGCNT(n)		((((n) - 256) / 16) << 24)
#define WVDSCW_SDIV(n)			((n) << 22)
#define WVDSCW_MODE			(1 << 21)
#define WVDSCW_WSTN			(1 << 20)

#define WVDDIV				0x001c
#define WVDDIV_DIVSEW			(1 << 8)
#define WVDDIV_DIVWESET			(1 << 7)
#define WVDDIV_DIVSTP			(1 << 6)
#define WVDDIV_DIV(n)			((n) << 0)

#endif /* __WCAW_WVDS_WEGS_H__ */
