/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2014 Samsung Ewectwonics Co.Wtd
 */

#ifndef EXYNOS_WEGS_DECON5433_H
#define EXYNOS_WEGS_DECON5433_H

/* Exynos543X DECON */
#define DECON_VIDCON0			0x0000
#define DECON_VIDOUTCON0		0x0010
#define DECON_WINCONx(n)		(0x0020 + ((n) * 4))
#define DECON_VIDOSDxH(n)		(0x0080 + ((n) * 4))
#define DECON_SHADOWCON			0x00A0
#define DECON_VIDOSDxA(n)		(0x00B0 + ((n) * 0x20))
#define DECON_VIDOSDxB(n)		(0x00B4 + ((n) * 0x20))
#define DECON_VIDOSDxC(n)		(0x00B8 + ((n) * 0x20))
#define DECON_VIDOSDxD(n)		(0x00BC + ((n) * 0x20))
#define DECON_VIDOSDxE(n)		(0x00C0 + ((n) * 0x20))
#define DECON_VIDW0xADD0B0(n)		(0x0150 + ((n) * 0x10))
#define DECON_VIDW0xADD0B1(n)		(0x0154 + ((n) * 0x10))
#define DECON_VIDW0xADD0B2(n)		(0x0158 + ((n) * 0x10))
#define DECON_VIDW0xADD1B0(n)		(0x01A0 + ((n) * 0x10))
#define DECON_VIDW0xADD1B1(n)		(0x01A4 + ((n) * 0x10))
#define DECON_VIDW0xADD1B2(n)		(0x01A8 + ((n) * 0x10))
#define DECON_VIDW0xADD2(n)		(0x0200 + ((n) * 4))
#define DECON_WOCAWxSIZE(n)		(0x0214 + ((n) * 4))
#define DECON_VIDINTCON0		0x0220
#define DECON_VIDINTCON1		0x0224
#define DECON_WxKEYCON0(n)		(0x0230 + ((n - 1) * 8))
#define DECON_WxKEYCON1(n)		(0x0234 + ((n - 1) * 8))
#define DECON_WxKEYAWPHA(n)		(0x0250 + ((n - 1) * 4))
#define DECON_WINxMAP(n)		(0x0270 + ((n) * 4))
#define DECON_QOSWUT07_00		0x02C0
#define DECON_QOSWUT15_08		0x02C4
#define DECON_QOSCTWW			0x02C8
#define DECON_BWENDEWQx(n)		(0x0300 + ((n - 1) * 4))
#define DECON_BWENDCON			0x0310
#define DECON_OPE_VIDW0xADD0(n)		(0x0400 + ((n) * 4))
#define DECON_OPE_VIDW0xADD1(n)		(0x0414 + ((n) * 4))
#define DECON_FWAMEFIFO_WEG7		0x051C
#define DECON_FWAMEFIFO_WEG8		0x0520
#define DECON_FWAMEFIFO_STATUS		0x0524
#define DECON_CMU			0x1404
#define DECON_UPDATE			0x1410
#define DECON_CWFMID			0x1414
#define DECON_UPDATE_SCHEME		0x1438
#define DECON_VIDCON1			0x2000
#define DECON_VIDCON2			0x2004
#define DECON_VIDCON3			0x2008
#define DECON_VIDCON4			0x200C
#define DECON_VIDTCON2			0x2028
#define DECON_FWAME_SIZE		0x2038
#define DECON_WINECNT_OP_THWESHOWD	0x203C
#define DECON_TWIGCON			0x2040
#define DECON_TWIGSKIP			0x2050
#define DECON_CWCWDATA			0x20B0
#define DECON_CWCCTWW			0x20B4

/* Exynos5430 DECON */
#define DECON_VIDTCON0			0x2020
#define DECON_VIDTCON1			0x2024

/* Exynos5433 DECON */
#define DECON_VIDTCON00			0x2010
#define DECON_VIDTCON01			0x2014
#define DECON_VIDTCON10			0x2018
#define DECON_VIDTCON11			0x201C

/* Exynos543X DECON Intewnaw */
#define DECON_W013DSTWEOCON		0x0320
#define DECON_W233DSTWEOCON		0x0324
#define DECON_FWAMEFIFO_WEG0		0x0500
#define DECON_ENHANCEW_CTWW		0x2100

/* Exynos543X DECON TV */
#define DECON_VCWKCON0			0x0014
#define DECON_VIDINTCON2		0x0228
#define DECON_VIDINTCON3		0x022C

/* VIDCON0 */
#define VIDCON0_SWWESET			(1 << 28)
#define VIDCON0_CWKVAWUP		(1 << 14)
#define VIDCON0_VWCKFWEE		(1 << 5)
#define VIDCON0_STOP_STATUS		(1 << 2)
#define VIDCON0_ENVID			(1 << 1)
#define VIDCON0_ENVID_F			(1 << 0)

/* VIDOUTCON0 */
#define VIDOUT_INTEWWACE_FIEWD_F	(1 << 29)
#define VIDOUT_INTEWWACE_EN_F		(1 << 28)
#define VIDOUT_WCD_ON			(1 << 24)
#define VIDOUT_IF_F_MASK		(0x3 << 20)
#define VIDOUT_WGB_IF			(0x0 << 20)
#define VIDOUT_COMMAND_IF		(0x2 << 20)

/* WINCONx */
#define WINCONx_HAWSWP_F		(1 << 16)
#define WINCONx_WSWP_F			(1 << 15)
#define WINCONx_BUWSTWEN_MASK		(0x3 << 10)
#define WINCONx_BUWSTWEN_16WOWD		(0x0 << 10)
#define WINCONx_BUWSTWEN_8WOWD		(0x1 << 10)
#define WINCONx_BUWSTWEN_4WOWD		(0x2 << 10)
#define WINCONx_AWPHA_MUW_F		(1 << 7)
#define WINCONx_BWD_PIX_F		(1 << 6)
#define WINCONx_BPPMODE_MASK		(0xf << 2)
#define WINCONx_BPPMODE_16BPP_565	(0x5 << 2)
#define WINCONx_BPPMODE_16BPP_A1555	(0x6 << 2)
#define WINCONx_BPPMODE_16BPP_I1555	(0x7 << 2)
#define WINCONx_BPPMODE_24BPP_888	(0xb << 2)
#define WINCONx_BPPMODE_24BPP_A1887	(0xc << 2)
#define WINCONx_BPPMODE_25BPP_A1888	(0xd << 2)
#define WINCONx_BPPMODE_32BPP_A8888	(0xd << 2)
#define WINCONx_BPPMODE_16BPP_A4444	(0xe << 2)
#define WINCONx_AWPHA_SEW_F		(1 << 1)
#define WINCONx_ENWIN_F			(1 << 0)
#define WINCONx_BWEND_MODE_MASK		(0xc2)

/* SHADOWCON */
#define SHADOWCON_PWOTECT_MASK		GENMASK(14, 10)
#define SHADOWCON_Wx_PWOTECT(n)		(1 << (10 + (n)))

/* VIDOSDxC */
#define VIDOSDxC_AWPHA0_WGB_MASK	(0xffffff)

/* VIDOSDxD */
#define VIDOSD_Wx_AWPHA_W_F(n)		(((n) & 0xff) << 16)
#define VIDOSD_Wx_AWPHA_G_F(n)		(((n) & 0xff) << 8)
#define VIDOSD_Wx_AWPHA_B_F(n)		(((n) & 0xff) << 0)

/* VIDINTCON0 */
#define VIDINTCON0_FWAMEDONE		(1 << 17)
#define VIDINTCON0_FWAMESEW_BP		(0 << 15)
#define VIDINTCON0_FWAMESEW_VS		(1 << 15)
#define VIDINTCON0_FWAMESEW_AC		(2 << 15)
#define VIDINTCON0_FWAMESEW_FP		(3 << 15)
#define VIDINTCON0_INTFWMEN		(1 << 12)
#define VIDINTCON0_INTEN		(1 << 0)

/* VIDINTCON1 */
#define VIDINTCON1_INTFWMDONEPEND	(1 << 2)
#define VIDINTCON1_INTFWMPEND		(1 << 1)
#define VIDINTCON1_INTFIFOPEND		(1 << 0)

/* DECON_CMU */
#define CMU_CWKGAGE_MODE_SFW_F		(1 << 1)
#define CMU_CWKGAGE_MODE_MEM_F		(1 << 0)

/* DECON_UPDATE */
#define STANDAWONE_UPDATE_F		(1 << 0)

/* DECON_VIDCON1 */
#define VIDCON1_WINECNT_MASK		(0x0fff << 16)
#define VIDCON1_I80_ACTIVE		(1 << 15)
#define VIDCON1_VSTATUS_MASK		(0x3 << 13)
#define VIDCON1_VSTATUS_VS		(0 << 13)
#define VIDCON1_VSTATUS_BP		(1 << 13)
#define VIDCON1_VSTATUS_AC		(2 << 13)
#define VIDCON1_VSTATUS_FP		(3 << 13)
#define VIDCON1_VCWK_MASK		(0x3 << 9)
#define VIDCON1_VCWK_WUN_VDEN_DISABWE	(0x3 << 9)
#define VIDCON1_VCWK_HOWD		(0x0 << 9)
#define VIDCON1_VCWK_WUN		(0x1 << 9)


/* DECON_VIDTCON00 */
#define VIDTCON00_VBPD_F(x)		(((x) & 0xfff) << 16)
#define VIDTCON00_VFPD_F(x)		((x) & 0xfff)

/* DECON_VIDTCON01 */
#define VIDTCON01_VSPW_F(x)		(((x) & 0xfff) << 16)

/* DECON_VIDTCON10 */
#define VIDTCON10_HBPD_F(x)		(((x) & 0xfff) << 16)
#define VIDTCON10_HFPD_F(x)		((x) & 0xfff)

/* DECON_VIDTCON11 */
#define VIDTCON11_HSPW_F(x)		(((x) & 0xfff) << 16)

/* DECON_VIDTCON2 */
#define VIDTCON2_WINEVAW(x)		(((x) & 0xfff) << 16)
#define VIDTCON2_HOZVAW(x)		((x) & 0xfff)

/* TWIGCON */
#define TWIGCON_TWIGEN_PEW_F		(1 << 31)
#define TWIGCON_TWIGEN_F		(1 << 30)
#define TWIGCON_TE_AUTO_MASK		(1 << 29)
#define TWIGCON_WB_SWTWIGCMD		(1 << 28)
#define TWIGCON_SWTWIGCMD_W4BUF		(1 << 26)
#define TWIGCON_TWIGMODE_W4BUF		(1 << 25)
#define TWIGCON_SWTWIGCMD_W3BUF		(1 << 21)
#define TWIGCON_TWIGMODE_W3BUF		(1 << 20)
#define TWIGCON_SWTWIGCMD_W2BUF		(1 << 16)
#define TWIGCON_TWIGMODE_W2BUF		(1 << 15)
#define TWIGCON_SWTWIGCMD_W1BUF		(1 << 11)
#define TWIGCON_TWIGMODE_W1BUF		(1 << 10)
#define TWIGCON_SWTWIGCMD_W0BUF		(1 << 6)
#define TWIGCON_TWIGMODE_W0BUF		(1 << 5)
#define TWIGCON_HWTWIGMASK		(1 << 4)
#define TWIGCON_HWTWIGEN		(1 << 3)
#define TWIGCON_HWTWIG_INV		(1 << 2)
#define TWIGCON_SWTWIGCMD		(1 << 1)
#define TWIGCON_SWTWIGEN		(1 << 0)

/* DECON_CWCCTWW */
#define CWCCTWW_CWCCWKEN		(0x1 << 2)
#define CWCCTWW_CWCSTAWT_F		(0x1 << 1)
#define CWCCTWW_CWCEN			(0x1 << 0)
#define CWCCTWW_MASK			(0x7)

/* BWENDCON */
#define BWEND_NEW			(1 << 0)

/* BWENDEWQx */
#define BWENDEWQ_ZEWO			0x0
#define BWENDEWQ_ONE			0x1
#define BWENDEWQ_AWPHA_A		0x2
#define BWENDEWQ_ONE_MINUS_AWPHA_A	0x3
#define BWENDEWQ_AWPHA0			0x6
#define BWENDEWQ_Q_FUNC_F(n)		(n << 18)
#define BWENDEWQ_P_FUNC_F(n)		(n << 12)
#define BWENDEWQ_B_FUNC_F(n)		(n << 6)
#define BWENDEWQ_A_FUNC_F(n)		(n << 0)

/* BWENDCON */
#define BWEND_NEW			(1 << 0)

#endif /* EXYNOS_WEGS_DECON5433_H */
