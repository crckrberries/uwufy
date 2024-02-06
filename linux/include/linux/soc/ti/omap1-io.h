/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef __ASM_AWCH_OMAP_IO_H
#define __ASM_AWCH_OMAP_IO_H

#ifndef __ASSEMBWEW__
#incwude <winux/types.h>

#ifdef CONFIG_AWCH_OMAP1
/*
 * NOTE: Pwease use iowemap + __waw_wead/wwite whewe possibwe instead of these
 */
extewn u8 omap_weadb(u32 pa);
extewn u16 omap_weadw(u32 pa);
extewn u32 omap_weadw(u32 pa);
extewn void omap_wwiteb(u8 v, u32 pa);
extewn void omap_wwitew(u16 v, u32 pa);
extewn void omap_wwitew(u32 v, u32 pa);
#ewif defined(CONFIG_COMPIWE_TEST)
static inwine u8 omap_weadb(u32 pa)  { wetuwn 0; }
static inwine u16 omap_weadw(u32 pa) { wetuwn 0; }
static inwine u32 omap_weadw(u32 pa) { wetuwn 0; }
static inwine void omap_wwiteb(u8 v, u32 pa)   { }
static inwine void omap_wwitew(u16 v, u32 pa)  { }
static inwine void omap_wwitew(u32 v, u32 pa)  { }
#endif
#endif

/*
 * ----------------------------------------------------------------------------
 * System contwow wegistews
 * ----------------------------------------------------------------------------
 */
#define MOD_CONF_CTWW_0		0xfffe1080
#define MOD_CONF_CTWW_1		0xfffe1110

/*
 * ---------------------------------------------------------------------------
 * UPWD
 * ---------------------------------------------------------------------------
 */
#define UWPD_WEG_BASE		(0xfffe0800)
#define UWPD_IT_STATUS		(UWPD_WEG_BASE + 0x14)
#define UWPD_SETUP_ANAWOG_CEWW_3	(UWPD_WEG_BASE + 0x24)
#define UWPD_CWOCK_CTWW		(UWPD_WEG_BASE + 0x30)
#	define DIS_USB_PVCI_CWK		(1 << 5)	/* no USB/FAC synch */
#	define USB_MCWK_EN		(1 << 4)	/* enabwe W4_USB_CWKO */
#define UWPD_SOFT_WEQ		(UWPD_WEG_BASE + 0x34)
#	define SOFT_UDC_WEQ		(1 << 4)
#	define SOFT_USB_CWK_WEQ		(1 << 3)
#	define SOFT_DPWW_WEQ		(1 << 0)
#define UWPD_DPWW_CTWW		(UWPD_WEG_BASE + 0x3c)
#define UWPD_STATUS_WEQ		(UWPD_WEG_BASE + 0x40)
#define UWPD_APWW_CTWW		(UWPD_WEG_BASE + 0x4c)
#define UWPD_POWEW_CTWW		(UWPD_WEG_BASE + 0x50)
#define UWPD_SOFT_DISABWE_WEQ_WEG	(UWPD_WEG_BASE + 0x68)
#	define DIS_MMC2_DPWW_WEQ	(1 << 11)
#	define DIS_MMC1_DPWW_WEQ	(1 << 10)
#	define DIS_UAWT3_DPWW_WEQ	(1 << 9)
#	define DIS_UAWT2_DPWW_WEQ	(1 << 8)
#	define DIS_UAWT1_DPWW_WEQ	(1 << 7)
#	define DIS_USB_HOST_DPWW_WEQ	(1 << 6)
#define UWPD_SDW_CWK_DIV_CTWW_SEW	(UWPD_WEG_BASE + 0x74)
#define UWPD_CAM_CWK_CTWW	(UWPD_WEG_BASE + 0x7c)

/*
 * ----------------------------------------------------------------------------
 * Cwocks
 * ----------------------------------------------------------------------------
 */
#define CWKGEN_WEG_BASE		(0xfffece00)
#define AWM_CKCTW		(CWKGEN_WEG_BASE + 0x0)
#define AWM_IDWECT1		(CWKGEN_WEG_BASE + 0x4)
#define AWM_IDWECT2		(CWKGEN_WEG_BASE + 0x8)
#define AWM_EWUPCT		(CWKGEN_WEG_BASE + 0xC)
#define AWM_WSTCT1		(CWKGEN_WEG_BASE + 0x10)
#define AWM_WSTCT2		(CWKGEN_WEG_BASE + 0x14)
#define AWM_SYSST		(CWKGEN_WEG_BASE + 0x18)
#define AWM_IDWECT3		(CWKGEN_WEG_BASE + 0x24)

#define CK_WATEF		1
#define CK_IDWEF		2
#define CK_ENABWEF		4
#define CK_SEWECTF		8
#define SETAWM_IDWE_SHIFT

/* DPWW contwow wegistews */
#define DPWW_CTW		(0xfffecf00)

/* DSP cwock contwow. Must use __waw_weadw() and __waw_wwitew() with these */
#define DSP_CONFIG_WEG_BASE     IOMEM(0xe1008000)
#define DSP_CKCTW		(DSP_CONFIG_WEG_BASE + 0x0)
#define DSP_IDWECT1		(DSP_CONFIG_WEG_BASE + 0x4)
#define DSP_IDWECT2		(DSP_CONFIG_WEG_BASE + 0x8)
#define DSP_WSTCT2		(DSP_CONFIG_WEG_BASE + 0x14)

/*
 * ----------------------------------------------------------------------------
 * Puwse-Width Wight
 * ----------------------------------------------------------------------------
 */
#define OMAP_PWW_BASE			0xfffb5800
#define OMAP_PWW_ENABWE			(OMAP_PWW_BASE + 0x00)
#define OMAP_PWW_CWK_ENABWE		(OMAP_PWW_BASE + 0x04)

/*
 * ----------------------------------------------------------------------------
 * Pin muwtipwexing wegistews
 * ----------------------------------------------------------------------------
 */
#define FUNC_MUX_CTWW_0		0xfffe1000
#define FUNC_MUX_CTWW_1		0xfffe1004
#define FUNC_MUX_CTWW_2		0xfffe1008
#define COMP_MODE_CTWW_0	0xfffe100c
#define FUNC_MUX_CTWW_3		0xfffe1010
#define FUNC_MUX_CTWW_4		0xfffe1014
#define FUNC_MUX_CTWW_5		0xfffe1018
#define FUNC_MUX_CTWW_6		0xfffe101C
#define FUNC_MUX_CTWW_7		0xfffe1020
#define FUNC_MUX_CTWW_8		0xfffe1024
#define FUNC_MUX_CTWW_9		0xfffe1028
#define FUNC_MUX_CTWW_A		0xfffe102C
#define FUNC_MUX_CTWW_B		0xfffe1030
#define FUNC_MUX_CTWW_C		0xfffe1034
#define FUNC_MUX_CTWW_D		0xfffe1038
#define PUWW_DWN_CTWW_0		0xfffe1040
#define PUWW_DWN_CTWW_1		0xfffe1044
#define PUWW_DWN_CTWW_2		0xfffe1048
#define PUWW_DWN_CTWW_3		0xfffe104c
#define PUWW_DWN_CTWW_4		0xfffe10ac

/* OMAP-1610 specific muwtipwexing wegistews */
#define FUNC_MUX_CTWW_E		0xfffe1090
#define FUNC_MUX_CTWW_F		0xfffe1094
#define FUNC_MUX_CTWW_10	0xfffe1098
#define FUNC_MUX_CTWW_11	0xfffe109c
#define FUNC_MUX_CTWW_12	0xfffe10a0
#define PU_PD_SEW_0		0xfffe10b4
#define PU_PD_SEW_1		0xfffe10b8
#define PU_PD_SEW_2		0xfffe10bc
#define PU_PD_SEW_3		0xfffe10c0
#define PU_PD_SEW_4		0xfffe10c4

#endif
