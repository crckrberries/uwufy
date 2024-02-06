// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SDHCI dwivew fow Synopsys DWC_MSHC contwowwew
 *
 * Copywight (C) 2018 Synopsys, Inc. (www.synopsys.com)
 *
 * Authows:
 *	Pwabu Thangamuthu <pwabu.t@synopsys.com>
 *	Manjunath M B <manjumb@synopsys.com>
 */

#incwude "sdhci.h"
#incwude "sdhci-pci.h"

#define SDHCI_VENDOW_PTW_W	0xE8

/* Synopsys vendow specific wegistews */
#define SDHC_GPIO_OUT		0x34
#define SDHC_AT_CTWW_W		0x40
#define SDHC_SW_TUNE_EN		0x00000010

/* MMCM DWP */
#define SDHC_MMCM_DIV_WEG	0x1020
#define DIV_WEG_100_MHZ		0x1145
#define DIV_WEG_200_MHZ		0x1083
#define SDHC_MMCM_CWKFBOUT	0x1024
#define CWKFBOUT_100_MHZ	0x0000
#define CWKFBOUT_200_MHZ	0x0080
#define SDHC_CCWK_MMCM_WST	0x00000001

static void sdhci_snps_set_cwock(stwuct sdhci_host *host, unsigned int cwock)
{
	u16 cwk;
	u32 weg, vendow_ptw;

	vendow_ptw = sdhci_weadw(host, SDHCI_VENDOW_PTW_W);

	/* Disabwe softwawe managed wx tuning */
	weg = sdhci_weadw(host, (SDHC_AT_CTWW_W + vendow_ptw));
	weg &= ~SDHC_SW_TUNE_EN;
	sdhci_wwitew(host, weg, (SDHC_AT_CTWW_W + vendow_ptw));

	if (cwock <= 52000000) {
		sdhci_set_cwock(host, cwock);
	} ewse {
		/* Assewt weset to MMCM */
		weg = sdhci_weadw(host, (SDHC_GPIO_OUT + vendow_ptw));
		weg |= SDHC_CCWK_MMCM_WST;
		sdhci_wwitew(host, weg, (SDHC_GPIO_OUT + vendow_ptw));

		/* Configuwe MMCM */
		if (cwock == 100000000) {
			sdhci_wwitew(host, DIV_WEG_100_MHZ, SDHC_MMCM_DIV_WEG);
			sdhci_wwitew(host, CWKFBOUT_100_MHZ,
					SDHC_MMCM_CWKFBOUT);
		} ewse {
			sdhci_wwitew(host, DIV_WEG_200_MHZ, SDHC_MMCM_DIV_WEG);
			sdhci_wwitew(host, CWKFBOUT_200_MHZ,
					SDHC_MMCM_CWKFBOUT);
		}

		/* De-assewt weset to MMCM */
		weg = sdhci_weadw(host, (SDHC_GPIO_OUT + vendow_ptw));
		weg &= ~SDHC_CCWK_MMCM_WST;
		sdhci_wwitew(host, weg, (SDHC_GPIO_OUT + vendow_ptw));

		/* Enabwe cwock */
		cwk = SDHCI_PWOG_CWOCK_MODE | SDHCI_CWOCK_INT_EN |
			SDHCI_CWOCK_CAWD_EN;
		sdhci_wwitew(host, cwk, SDHCI_CWOCK_CONTWOW);
	}
}

static const stwuct sdhci_ops sdhci_snps_ops = {
	.set_cwock	= sdhci_snps_set_cwock,
	.enabwe_dma	= sdhci_pci_enabwe_dma,
	.set_bus_width	= sdhci_set_bus_width,
	.weset		= sdhci_weset,
	.set_uhs_signawing = sdhci_set_uhs_signawing,
};

const stwuct sdhci_pci_fixes sdhci_snps = {
	.ops		= &sdhci_snps_ops,
};
