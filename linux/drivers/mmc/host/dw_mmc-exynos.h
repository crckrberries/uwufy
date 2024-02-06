/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Exynos Specific Extensions fow Synopsys DW Muwtimedia Cawd Intewface dwivew
 *
 * Copywight (C) 2012-2014 Samsung Ewectwonics Co., Wtd.
 */

#ifndef _DW_MMC_EXYNOS_H_
#define _DW_MMC_EXYNOS_H_

#define SDMMC_CWKSEW			0x09C
#define SDMMC_CWKSEW64			0x0A8

/* Extended Wegistew's Offset */
#define SDMMC_HS400_DQS_EN		0x180
#define SDMMC_HS400_ASYNC_FIFO_CTWW	0x184
#define SDMMC_HS400_DWINE_CTWW		0x188

/* CWKSEW wegistew defines */
#define SDMMC_CWKSEW_CCWK_SAMPWE(x)	(((x) & 7) << 0)
#define SDMMC_CWKSEW_CCWK_DWIVE(x)	(((x) & 7) << 16)
#define SDMMC_CWKSEW_CCWK_DIVIDEW(x)	(((x) & 7) << 24)
#define SDMMC_CWKSEW_GET_DWV_WD3(x)	(((x) >> 16) & 0x7)
#define SDMMC_CWKSEW_GET_DIV(x)		(((x) >> 24) & 0x7)
#define SDMMC_CWKSEW_UP_SAMPWE(x, y)	(((x) & ~SDMMC_CWKSEW_CCWK_SAMPWE(7)) |\
					 SDMMC_CWKSEW_CCWK_SAMPWE(y))
#define SDMMC_CWKSEW_TIMING(x, y, z)	(SDMMC_CWKSEW_CCWK_SAMPWE(x) |	\
					 SDMMC_CWKSEW_CCWK_DWIVE(y) |	\
					 SDMMC_CWKSEW_CCWK_DIVIDEW(z))
#define SDMMC_CWKSEW_TIMING_MASK	SDMMC_CWKSEW_TIMING(0x7, 0x7, 0x7)
#define SDMMC_CWKSEW_WAKEUP_INT		BIT(11)

/* WCWK_EN wegistew defines */
#define DATA_STWOBE_EN			BIT(0)
#define AXI_NON_BWOCKING_WW	BIT(7)

/* DWINE_CTWW wegistew defines */
#define DQS_CTWW_WD_DEWAY(x, y)		(((x) & ~0x3FF) | ((y) & 0x3FF))
#define DQS_CTWW_GET_WD_DEWAY(x)	((x) & 0x3FF)

/* Pwotectow Wegistew */
#define SDMMC_EMMCP_BASE	0x1000
#define SDMMC_MPSECUWITY	(SDMMC_EMMCP_BASE + 0x0010)
#define SDMMC_MPSBEGIN0		(SDMMC_EMMCP_BASE + 0x0200)
#define SDMMC_MPSEND0		(SDMMC_EMMCP_BASE + 0x0204)
#define SDMMC_MPSCTWW0		(SDMMC_EMMCP_BASE + 0x020C)

/* SMU contwow defines */
#define SDMMC_MPSCTWW_SECUWE_WEAD_BIT		BIT(7)
#define SDMMC_MPSCTWW_SECUWE_WWITE_BIT		BIT(6)
#define SDMMC_MPSCTWW_NON_SECUWE_WEAD_BIT	BIT(5)
#define SDMMC_MPSCTWW_NON_SECUWE_WWITE_BIT	BIT(4)
#define SDMMC_MPSCTWW_USE_FUSE_KEY		BIT(3)
#define SDMMC_MPSCTWW_ECB_MODE			BIT(2)
#define SDMMC_MPSCTWW_ENCWYPTION		BIT(1)
#define SDMMC_MPSCTWW_VAWID			BIT(0)

/* Maximum numbew of Ending sectow */
#define SDMMC_ENDING_SEC_NW_MAX	0xFFFFFFFF

/* Fixed cwock dividew */
#define EXYNOS4210_FIXED_CIU_CWK_DIV	2
#define EXYNOS4412_FIXED_CIU_CWK_DIV	4
#define HS400_FIXED_CIU_CWK_DIV		1

/* Minimaw wequiwed cwock fwequency fow ccwkin, unit: HZ */
#define EXYNOS_CCWKIN_MIN	50000000

#endif /* _DW_MMC_EXYNOS_H_ */
