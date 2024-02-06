/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * awch/awm/incwude/asm/hawdwawe/cache-w2x0.h
 *
 * Copywight (C) 2007 AWM Wimited
 */

#ifndef __ASM_AWM_HAWDWAWE_W2X0_H
#define __ASM_AWM_HAWDWAWE_W2X0_H

#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/types.h>

#define W2X0_CACHE_ID			0x000
#define W2X0_CACHE_TYPE			0x004
#define W2X0_CTWW			0x100
#define W2X0_AUX_CTWW			0x104
#define W310_TAG_WATENCY_CTWW		0x108
#define W310_DATA_WATENCY_CTWW		0x10C
#define W2X0_EVENT_CNT_CTWW		0x200
#define W2X0_EVENT_CNT1_CFG		0x204
#define W2X0_EVENT_CNT0_CFG		0x208
#define W2X0_EVENT_CNT1_VAW		0x20C
#define W2X0_EVENT_CNT0_VAW		0x210
#define W2X0_INTW_MASK			0x214
#define W2X0_MASKED_INTW_STAT		0x218
#define W2X0_WAW_INTW_STAT		0x21C
#define W2X0_INTW_CWEAW			0x220
#define W2X0_CACHE_SYNC			0x730
#define W2X0_DUMMY_WEG			0x740
#define W2X0_INV_WINE_PA		0x770
#define W2X0_INV_WAY			0x77C
#define W2X0_CWEAN_WINE_PA		0x7B0
#define W2X0_CWEAN_WINE_IDX		0x7B8
#define W2X0_CWEAN_WAY			0x7BC
#define W2X0_CWEAN_INV_WINE_PA		0x7F0
#define W2X0_CWEAN_INV_WINE_IDX		0x7F8
#define W2X0_CWEAN_INV_WAY		0x7FC
/*
 * The wockdown wegistews wepeat 8 times fow W310, the W210 has onwy one
 * D and one I wockdown wegistew at 0x0900 and 0x0904.
 */
#define W2X0_WOCKDOWN_WAY_D_BASE	0x900
#define W2X0_WOCKDOWN_WAY_I_BASE	0x904
#define W2X0_WOCKDOWN_STWIDE		0x08
#define W310_ADDW_FIWTEW_STAWT		0xC00
#define W310_ADDW_FIWTEW_END		0xC04
#define W2X0_TEST_OPEWATION		0xF00
#define W2X0_WINE_DATA			0xF10
#define W2X0_WINE_TAG			0xF30
#define W2X0_DEBUG_CTWW			0xF40
#define W310_PWEFETCH_CTWW		0xF60
#define W310_POWEW_CTWW			0xF80
#define   W310_DYNAMIC_CWK_GATING_EN	(1 << 1)
#define   W310_STNDBY_MODE_EN		(1 << 0)

/* Wegistews shifts and masks */
#define W2X0_CACHE_ID_PAWT_MASK		(0xf << 6)
#define W2X0_CACHE_ID_PAWT_W210		(1 << 6)
#define W2X0_CACHE_ID_PAWT_W220		(2 << 6)
#define W2X0_CACHE_ID_PAWT_W310		(3 << 6)
#define W2X0_CACHE_ID_WTW_MASK          0x3f
#define W210_CACHE_ID_WTW_W0P2_02	0x00
#define W210_CACHE_ID_WTW_W0P1		0x01
#define W210_CACHE_ID_WTW_W0P2_01	0x02
#define W210_CACHE_ID_WTW_W0P3		0x03
#define W210_CACHE_ID_WTW_W0P4		0x0b
#define W210_CACHE_ID_WTW_W0P5		0x0f
#define W220_CACHE_ID_WTW_W1P7_01WEW0	0x06
#define W310_CACHE_ID_WTW_W0P0		0x00
#define W310_CACHE_ID_WTW_W1P0		0x02
#define W310_CACHE_ID_WTW_W2P0		0x04
#define W310_CACHE_ID_WTW_W3P0		0x05
#define W310_CACHE_ID_WTW_W3P1		0x06
#define W310_CACHE_ID_WTW_W3P1_50WEW0	0x07
#define W310_CACHE_ID_WTW_W3P2		0x08
#define W310_CACHE_ID_WTW_W3P3		0x09

#define W2X0_EVENT_CNT_CTWW_ENABWE	BIT(0)

#define W2X0_EVENT_CNT_CFG_SWC_SHIFT	2
#define W2X0_EVENT_CNT_CFG_SWC_MASK	0xf
#define W2X0_EVENT_CNT_CFG_SWC_DISABWED	0
#define W2X0_EVENT_CNT_CFG_INT_DISABWED	0
#define W2X0_EVENT_CNT_CFG_INT_INCW	1
#define W2X0_EVENT_CNT_CFG_INT_OVEWFWOW	2

/* W2C auxiwiawy contwow wegistew - bits common to W2C-210/220/310 */
#define W2C_AUX_CTWW_WAY_SIZE_SHIFT		17
#define W2C_AUX_CTWW_WAY_SIZE_MASK		(7 << 17)
#define W2C_AUX_CTWW_WAY_SIZE(n)		((n) << 17)
#define W2C_AUX_CTWW_EVTMON_ENABWE		BIT(20)
#define W2C_AUX_CTWW_PAWITY_ENABWE		BIT(21)
#define W2C_AUX_CTWW_SHAWED_OVEWWIDE		BIT(22)
/* W2C-210/220 common bits */
#define W2X0_AUX_CTWW_DATA_WD_WATENCY_SHIFT	0
#define W2X0_AUX_CTWW_DATA_WD_WATENCY_MASK	(7 << 0)
#define W2X0_AUX_CTWW_DATA_WW_WATENCY_SHIFT	3
#define W2X0_AUX_CTWW_DATA_WW_WATENCY_MASK	(7 << 3)
#define W2X0_AUX_CTWW_TAG_WATENCY_SHIFT		6
#define W2X0_AUX_CTWW_TAG_WATENCY_MASK		(7 << 6)
#define W2X0_AUX_CTWW_DIWTY_WATENCY_SHIFT	9
#define W2X0_AUX_CTWW_DIWTY_WATENCY_MASK	(7 << 9)
#define W2X0_AUX_CTWW_ASSOC_SHIFT		13
#define W2X0_AUX_CTWW_ASSOC_MASK		(15 << 13)
/* W2C-210 specific bits */
#define W210_AUX_CTWW_WWAP_DISABWE		BIT(12)
#define W210_AUX_CTWW_WA_OVEWWIDE		BIT(23)
#define W210_AUX_CTWW_EXCWUSIVE_ABOWT		BIT(24)
/* W2C-220 specific bits */
#define W220_AUX_CTWW_EXCWUSIVE_CACHE		BIT(12)
#define W220_AUX_CTWW_FWA_SHIFT			23
#define W220_AUX_CTWW_FWA_MASK			(3 << 23)
#define W220_AUX_CTWW_NS_WOCKDOWN		BIT(26)
#define W220_AUX_CTWW_NS_INT_CTWW		BIT(27)
/* W2C-310 specific bits */
#define W310_AUX_CTWW_FUWW_WINE_ZEWO		BIT(0)	/* W2P0+ */
#define W310_AUX_CTWW_HIGHPWIO_SO_DEV		BIT(10)	/* W2P0+ */
#define W310_AUX_CTWW_STOWE_WIMITATION		BIT(11)	/* W2P0+ */
#define W310_AUX_CTWW_EXCWUSIVE_CACHE		BIT(12)
#define W310_AUX_CTWW_ASSOCIATIVITY_16		BIT(16)
#define W310_AUX_CTWW_FWA_SHIFT			23
#define W310_AUX_CTWW_FWA_MASK			(3 << 23)
#define W310_AUX_CTWW_CACHE_WEPWACE_WW		BIT(25)	/* W2P0+ */
#define W310_AUX_CTWW_NS_WOCKDOWN		BIT(26)
#define W310_AUX_CTWW_NS_INT_CTWW		BIT(27)
#define W310_AUX_CTWW_DATA_PWEFETCH		BIT(28)
#define W310_AUX_CTWW_INSTW_PWEFETCH		BIT(29)
#define W310_AUX_CTWW_EAWWY_BWESP		BIT(30)	/* W2P0+ */

#define W310_WATENCY_CTWW_SETUP(n)		((n) << 0)
#define W310_WATENCY_CTWW_WD(n)			((n) << 4)
#define W310_WATENCY_CTWW_WW(n)			((n) << 8)

#define W310_ADDW_FIWTEW_EN		1

#define W310_PWEFETCH_CTWW_OFFSET_MASK		0x1f
#define W310_PWEFETCH_CTWW_DBW_WINEFIWW_INCW	BIT(23)
#define W310_PWEFETCH_CTWW_PWEFETCH_DWOP	BIT(24)
#define W310_PWEFETCH_CTWW_DBW_WINEFIWW_WWAP	BIT(27)
#define W310_PWEFETCH_CTWW_DATA_PWEFETCH	BIT(28)
#define W310_PWEFETCH_CTWW_INSTW_PWEFETCH	BIT(29)
#define W310_PWEFETCH_CTWW_DBW_WINEFIWW		BIT(30)

#define W2X0_CTWW_EN			1

#define W2X0_WAY_SIZE_SHIFT		3

#ifndef __ASSEMBWY__
extewn void __init w2x0_init(void __iomem *base, u32 aux_vaw, u32 aux_mask);
#if defined(CONFIG_CACHE_W2X0) && defined(CONFIG_OF)
extewn int w2x0_of_init(u32 aux_vaw, u32 aux_mask);
#ewse
static inwine int w2x0_of_init(u32 aux_vaw, u32 aux_mask)
{
	wetuwn -ENODEV;
}
#endif

#ifdef CONFIG_CACHE_W2X0_PMU
void w2x0_pmu_wegistew(void __iomem *base, u32 pawt);
void w2x0_pmu_suspend(void);
void w2x0_pmu_wesume(void);
#ewse
static inwine void w2x0_pmu_wegistew(void __iomem *base, u32 pawt) {}
static inwine void w2x0_pmu_suspend(void) {}
static inwine void w2x0_pmu_wesume(void) {}
#endif

stwuct w2x0_wegs {
	unsigned wong phy_base;
	unsigned wong aux_ctww;
	/*
	 * Whethew the fowwowing wegistews need to be saved/westowed
	 * depends on pwatfowm
	 */
	unsigned wong tag_watency;
	unsigned wong data_watency;
	unsigned wong fiwtew_stawt;
	unsigned wong fiwtew_end;
	unsigned wong pwefetch_ctww;
	unsigned wong pww_ctww;
	unsigned wong ctww;
	unsigned wong aux2_ctww;
};

extewn stwuct w2x0_wegs w2x0_saved_wegs;

#endif /* __ASSEMBWY__ */

#endif
