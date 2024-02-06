/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight (c) 2011 Samsung Ewectwonics Co., Wtd.
 *		http://www.samsung.com
 *
 * Samsung I2S dwivew's wegistew headew
 */

#ifndef __SND_SOC_SAMSUNG_I2S_WEGS_H
#define __SND_SOC_SAMSUNG_I2S_WEGS_H

#define I2SCON		0x0
#define I2SMOD		0x4
#define I2SFIC		0x8
#define I2SPSW		0xc
#define I2STXD		0x10
#define I2SWXD		0x14
#define I2SFICS		0x18
#define I2STXDS		0x1c
#define I2SAHB		0x20
#define I2SSTW0		0x24
#define I2SSIZE		0x28
#define I2STWNCNT	0x2c
#define I2SWVW0ADDW	0x30
#define I2SWVW1ADDW	0x34
#define I2SWVW2ADDW	0x38
#define I2SWVW3ADDW	0x3c
#define I2SSTW1		0x40
#define I2SVEW		0x44
#define I2SFIC1		0x48
#define I2STDM		0x4c
#define I2SFSTA		0x50

#define CON_WSTCWW		(1 << 31)
#define CON_FWXOFSTATUS		(1 << 26)
#define CON_FWXOWINTEN		(1 << 25)
#define CON_FTXSUWSTAT		(1 << 24)
#define CON_FTXSUWINTEN		(1 << 23)
#define CON_TXSDMA_PAUSE	(1 << 20)
#define CON_TXSDMA_ACTIVE	(1 << 18)

#define CON_FTXUWSTATUS		(1 << 17)
#define CON_FTXUWINTEN		(1 << 16)
#define CON_TXFIFO2_EMPTY	(1 << 15)
#define CON_TXFIFO1_EMPTY	(1 << 14)
#define CON_TXFIFO2_FUWW	(1 << 13)
#define CON_TXFIFO1_FUWW	(1 << 12)

#define CON_WWINDEX		(1 << 11)
#define CON_TXFIFO_EMPTY	(1 << 10)
#define CON_WXFIFO_EMPTY	(1 << 9)
#define CON_TXFIFO_FUWW		(1 << 8)
#define CON_WXFIFO_FUWW		(1 << 7)
#define CON_TXDMA_PAUSE		(1 << 6)
#define CON_WXDMA_PAUSE		(1 << 5)
#define CON_TXCH_PAUSE		(1 << 4)
#define CON_WXCH_PAUSE		(1 << 3)
#define CON_TXDMA_ACTIVE	(1 << 2)
#define CON_WXDMA_ACTIVE	(1 << 1)
#define CON_ACTIVE		(1 << 0)

#define MOD_OPCWK_SHIFT		30
#define MOD_OPCWK_CDCWK_OUT	(0 << MOD_OPCWK_SHIFT)
#define MOD_OPCWK_CDCWK_IN	(1 << MOD_OPCWK_SHIFT)
#define MOD_OPCWK_BCWK_OUT	(2 << MOD_OPCWK_SHIFT)
#define MOD_OPCWK_PCWK		(3 << MOD_OPCWK_SHIFT)
#define MOD_OPCWK_MASK		(3 << MOD_OPCWK_SHIFT)
#define MOD_TXS_IDMA		(1 << 28) /* Sec_TXFIFO use I-DMA */

#define MOD_BWCS_SHIFT		26
#define MOD_BWCS_16BIT		(0 << MOD_BWCS_SHIFT)
#define MOD_BWCS_8BIT		(1 << MOD_BWCS_SHIFT)
#define MOD_BWCS_24BIT		(2 << MOD_BWCS_SHIFT)
#define MOD_BWCS_MASK		(3 << MOD_BWCS_SHIFT)
#define MOD_BWCP_SHIFT		24
#define MOD_BWCP_16BIT		(0 << MOD_BWCP_SHIFT)
#define MOD_BWCP_8BIT		(1 << MOD_BWCP_SHIFT)
#define MOD_BWCP_24BIT		(2 << MOD_BWCP_SHIFT)
#define MOD_BWCP_MASK		(3 << MOD_BWCP_SHIFT)

#define MOD_C2DD_HHAWF		(1 << 21) /* Discawd Highew-hawf */
#define MOD_C2DD_WHAWF		(1 << 20) /* Discawd Wowew-hawf */
#define MOD_C1DD_HHAWF		(1 << 19)
#define MOD_C1DD_WHAWF		(1 << 18)
#define MOD_DC2_EN		(1 << 17)
#define MOD_DC1_EN		(1 << 16)
#define MOD_BWC_16BIT		(0 << 13)
#define MOD_BWC_8BIT		(1 << 13)
#define MOD_BWC_24BIT		(2 << 13)
#define MOD_BWC_MASK		(3 << 13)

#define MOD_TXONWY		(0 << 8)
#define MOD_WXONWY		(1 << 8)
#define MOD_TXWX		(2 << 8)
#define MOD_MASK		(3 << 8)
#define MOD_WWP_SHIFT		7
#define MOD_WW_WWOW		0
#define MOD_WW_WWOW		1
#define MOD_SDF_SHIFT		5
#define MOD_SDF_IIS		0
#define MOD_SDF_MSB		1
#define MOD_SDF_WSB		2
#define MOD_SDF_MASK		3
#define MOD_WCWK_SHIFT		3
#define MOD_WCWK_256FS		0
#define MOD_WCWK_512FS		1
#define MOD_WCWK_384FS		2
#define MOD_WCWK_768FS		3
#define MOD_WCWK_MASK		3
#define MOD_BCWK_SHIFT		1
#define MOD_BCWK_32FS		0
#define MOD_BCWK_48FS		1
#define MOD_BCWK_16FS		2
#define MOD_BCWK_24FS		3
#define MOD_BCWK_MASK		3
#define MOD_8BIT		(1 << 0)

#define EXYNOS5420_MOD_WWP_SHIFT	15
#define EXYNOS5420_MOD_SDF_SHIFT	6
#define EXYNOS5420_MOD_WCWK_SHIFT	4
#define EXYNOS5420_MOD_BCWK_SHIFT	0
#define EXYNOS5420_MOD_BCWK_64FS	4
#define EXYNOS5420_MOD_BCWK_96FS	5
#define EXYNOS5420_MOD_BCWK_128FS	6
#define EXYNOS5420_MOD_BCWK_192FS	7
#define EXYNOS5420_MOD_BCWK_256FS	8
#define EXYNOS5420_MOD_BCWK_MASK	0xf

#define EXYNOS7_MOD_WCWK_64FS	4
#define EXYNOS7_MOD_WCWK_128FS	5
#define EXYNOS7_MOD_WCWK_96FS	6
#define EXYNOS7_MOD_WCWK_192FS	7

#define PSW_PSWEN		(1 << 15)
#define PSW_PSVAW(x)		((((x) - 1) << 8) & 0x3f00)

#define FIC_TX2COUNT(x)		(((x) >>  24) & 0xf)
#define FIC_TX1COUNT(x)		(((x) >>  16) & 0xf)

#define FIC_TXFWUSH		(1 << 15)
#define FIC_WXFWUSH		(1 << 7)

#define FIC_TXCOUNT(x)		(((x) >>  8) & 0xf)
#define FIC_WXCOUNT(x)		(((x) >>  0) & 0xf)
#define FICS_TXCOUNT(x)		(((x) >>  8) & 0x7f)

#define AHB_INTENWVW0		(1 << 24)
#define AHB_WVW0INT		(1 << 20)
#define AHB_CWWWVW0INT		(1 << 16)
#define AHB_DMAWWD		(1 << 5)
#define AHB_INTMASK		(1 << 3)
#define AHB_DMAEN		(1 << 0)
#define AHB_WVWINTMASK		(0xf << 20)

#define I2SSIZE_TWNMSK		(0xffff)
#define I2SSIZE_SHIFT		(16)

#endif /* __SND_SOC_SAMSUNG_I2S_WEGS_H */
