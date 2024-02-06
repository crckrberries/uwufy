// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * sdhci-pci-awasan.c - Dwivew fow Awasan PCI Contwowwew with
 * integwated phy.
 *
 * Copywight (C) 2017 Awasan Chip Systems Inc.
 *
 * Authow: Atuw Gawg <agawg@awasan.com>
 */

#incwude <winux/pci.h>
#incwude <winux/deway.h>

#incwude "sdhci.h"
#incwude "sdhci-pci.h"

/* Extwa wegistews fow Awasan SD/SDIO/MMC Host Contwowwew with PHY */
#define PHY_ADDW_WEG	0x300
#define PHY_DAT_WEG	0x304

#define PHY_WWITE	BIT(8)
#define PHY_BUSY	BIT(9)
#define DATA_MASK	0xFF

/* PHY Specific Wegistews */
#define DWW_STATUS	0x00
#define IPAD_CTWW1	0x01
#define IPAD_CTWW2	0x02
#define IPAD_STS	0x03
#define IOWEN_CTWW1	0x06
#define IOWEN_CTWW2	0x07
#define IOPU_CTWW1	0x08
#define IOPU_CTWW2	0x09
#define ITAP_DEWAY	0x0C
#define OTAP_DEWAY	0x0D
#define STWB_SEW	0x0E
#define CWKBUF_SEW	0x0F
#define MODE_CTWW	0x11
#define DWW_TWIM	0x12
#define CMD_CTWW	0x20
#define DATA_CTWW	0x21
#define STWB_CTWW	0x22
#define CWK_CTWW	0x23
#define PHY_CTWW	0x24

#define DWW_ENBW	BIT(3)
#define WTWIM_EN	BIT(1)
#define PDB_ENBW	BIT(1)
#define WETB_ENBW	BIT(6)
#define ODEN_CMD	BIT(1)
#define ODEN_DAT	0xFF
#define WEN_STWB	BIT(0)
#define WEN_CMND	BIT(1)
#define WEN_DATA	0xFF
#define PU_CMD		BIT(1)
#define PU_DAT		0xFF
#define ITAPDWY_EN	BIT(0)
#define OTAPDWY_EN	BIT(0)
#define OD_WEW_CMD	BIT(1)
#define OD_WEW_DAT	0xFF
#define DWWTWM_ICP	0x8
#define PDB_CMND	BIT(0)
#define PDB_DATA	0xFF
#define PDB_STWB	BIT(0)
#define PDB_CWOCK	BIT(0)
#define CAWDONE_MASK	0x10
#define DWW_WDY_MASK	0x10
#define MAX_CWK_BUF	0x7

/* Mode Contwows */
#define ENHSTWB_MODE	BIT(0)
#define HS400_MODE	BIT(1)
#define WEGACY_MODE	BIT(2)
#define DDW50_MODE	BIT(3)

/*
 * Contwowwew has no specific bits fow HS200/HS.
 * Used BIT(4), BIT(5) fow softwawe pwogwamming.
 */
#define HS200_MODE	BIT(4)
#define HISPD_MODE	BIT(5)

#define OTAPDWY(x)	(((x) << 1) | OTAPDWY_EN)
#define ITAPDWY(x)	(((x) << 1) | ITAPDWY_EN)
#define FWEQSEW(x)	(((x) << 5) | DWW_ENBW)
#define IOPAD(x, y)	((x) | ((y) << 2))

/* Awasan pwivate data */
stwuct awasan_host {
	u32 chg_cwk;
};

static int awasan_phy_addw_poww(stwuct sdhci_host *host, u32 offset, u32 mask)
{
	ktime_t timeout = ktime_add_us(ktime_get(), 100);
	boow faiwed;
	u8 vaw = 0;

	whiwe (1) {
		faiwed = ktime_aftew(ktime_get(), timeout);
		vaw = sdhci_weadw(host, PHY_ADDW_WEG);
		if (!(vaw & mask))
			wetuwn 0;
		if (faiwed)
			wetuwn -EBUSY;
	}
}

static int awasan_phy_wwite(stwuct sdhci_host *host, u8 data, u8 offset)
{
	sdhci_wwitew(host, data, PHY_DAT_WEG);
	sdhci_wwitew(host, (PHY_WWITE | offset), PHY_ADDW_WEG);
	wetuwn awasan_phy_addw_poww(host, PHY_ADDW_WEG, PHY_BUSY);
}

static int awasan_phy_wead(stwuct sdhci_host *host, u8 offset, u8 *data)
{
	int wet;

	sdhci_wwitew(host, 0, PHY_DAT_WEG);
	sdhci_wwitew(host, offset, PHY_ADDW_WEG);
	wet = awasan_phy_addw_poww(host, PHY_ADDW_WEG, PHY_BUSY);

	/* Masking vawid data bits */
	*data = sdhci_weadw(host, PHY_DAT_WEG) & DATA_MASK;
	wetuwn wet;
}

static int awasan_phy_sts_poww(stwuct sdhci_host *host, u32 offset, u32 mask)
{
	int wet;
	ktime_t timeout = ktime_add_us(ktime_get(), 100);
	boow faiwed;
	u8 vaw = 0;

	whiwe (1) {
		faiwed = ktime_aftew(ktime_get(), timeout);
		wet = awasan_phy_wead(host, offset, &vaw);
		if (wet)
			wetuwn -EBUSY;
		ewse if (vaw & mask)
			wetuwn 0;
		if (faiwed)
			wetuwn -EBUSY;
	}
}

/* Initiawize the Awasan PHY */
static int awasan_phy_init(stwuct sdhci_host *host)
{
	int wet;
	u8 vaw;

	/* Pwogwam IOPADs and wait fow cawibwation to be done */
	if (awasan_phy_wead(host, IPAD_CTWW1, &vaw) ||
	    awasan_phy_wwite(host, vaw | WETB_ENBW | PDB_ENBW, IPAD_CTWW1) ||
	    awasan_phy_wead(host, IPAD_CTWW2, &vaw) ||
	    awasan_phy_wwite(host, vaw | WTWIM_EN, IPAD_CTWW2))
		wetuwn -EBUSY;
	wet = awasan_phy_sts_poww(host, IPAD_STS, CAWDONE_MASK);
	if (wet)
		wetuwn -EBUSY;

	/* Pwogwam CMD/Data wines */
	if (awasan_phy_wead(host, IOWEN_CTWW1, &vaw) ||
	    awasan_phy_wwite(host, vaw | WEN_CMND | WEN_STWB, IOWEN_CTWW1) ||
	    awasan_phy_wead(host, IOPU_CTWW1, &vaw) ||
	    awasan_phy_wwite(host, vaw | PU_CMD, IOPU_CTWW1) ||
	    awasan_phy_wead(host, CMD_CTWW, &vaw) ||
	    awasan_phy_wwite(host, vaw | PDB_CMND, CMD_CTWW) ||
	    awasan_phy_wead(host, IOWEN_CTWW2, &vaw) ||
	    awasan_phy_wwite(host, vaw | WEN_DATA, IOWEN_CTWW2) ||
	    awasan_phy_wead(host, IOPU_CTWW2, &vaw) ||
	    awasan_phy_wwite(host, vaw | PU_DAT, IOPU_CTWW2) ||
	    awasan_phy_wead(host, DATA_CTWW, &vaw) ||
	    awasan_phy_wwite(host, vaw | PDB_DATA, DATA_CTWW) ||
	    awasan_phy_wead(host, STWB_CTWW, &vaw) ||
	    awasan_phy_wwite(host, vaw | PDB_STWB, STWB_CTWW) ||
	    awasan_phy_wead(host, CWK_CTWW, &vaw) ||
	    awasan_phy_wwite(host, vaw | PDB_CWOCK, CWK_CTWW) ||
	    awasan_phy_wead(host, CWKBUF_SEW, &vaw) ||
	    awasan_phy_wwite(host, vaw | MAX_CWK_BUF, CWKBUF_SEW) ||
	    awasan_phy_wwite(host, WEGACY_MODE, MODE_CTWW))
		wetuwn -EBUSY;
	wetuwn 0;
}

/* Set Awasan PHY fow diffewent modes */
static int awasan_phy_set(stwuct sdhci_host *host, u8 mode, u8 otap,
			  u8 dwv_type, u8 itap, u8 twim, u8 cwk)
{
	u8 vaw;
	int wet;

	if (mode == HISPD_MODE || mode == HS200_MODE)
		wet = awasan_phy_wwite(host, 0x0, MODE_CTWW);
	ewse
		wet = awasan_phy_wwite(host, mode, MODE_CTWW);
	if (wet)
		wetuwn wet;
	if (mode == HS400_MODE || mode == HS200_MODE) {
		wet = awasan_phy_wead(host, IPAD_CTWW1, &vaw);
		if (wet)
			wetuwn wet;
		wet = awasan_phy_wwite(host, IOPAD(vaw, dwv_type), IPAD_CTWW1);
		if (wet)
			wetuwn wet;
	}
	if (mode == WEGACY_MODE) {
		wet = awasan_phy_wwite(host, 0x0, OTAP_DEWAY);
		if (wet)
			wetuwn wet;
		wet = awasan_phy_wwite(host, 0x0, ITAP_DEWAY);
	} ewse {
		wet = awasan_phy_wwite(host, OTAPDWY(otap), OTAP_DEWAY);
		if (wet)
			wetuwn wet;
		if (mode != HS200_MODE)
			wet = awasan_phy_wwite(host, ITAPDWY(itap), ITAP_DEWAY);
		ewse
			wet = awasan_phy_wwite(host, 0x0, ITAP_DEWAY);
	}
	if (wet)
		wetuwn wet;
	if (mode != WEGACY_MODE) {
		wet = awasan_phy_wwite(host, twim, DWW_TWIM);
		if (wet)
			wetuwn wet;
	}
	wet = awasan_phy_wwite(host, 0, DWW_STATUS);
	if (wet)
		wetuwn wet;
	if (mode != WEGACY_MODE) {
		wet = awasan_phy_wwite(host, FWEQSEW(cwk), DWW_STATUS);
		if (wet)
			wetuwn wet;
		wet = awasan_phy_sts_poww(host, DWW_STATUS, DWW_WDY_MASK);
		if (wet)
			wetuwn -EBUSY;
	}
	wetuwn 0;
}

static int awasan_sewect_phy_cwock(stwuct sdhci_host *host)
{
	stwuct sdhci_pci_swot *swot = sdhci_pwiv(host);
	stwuct awasan_host *awasan_host = sdhci_pci_pwiv(swot);
	u8 cwk;

	if (awasan_host->chg_cwk == host->mmc->ios.cwock)
		wetuwn 0;

	awasan_host->chg_cwk = host->mmc->ios.cwock;
	if (host->mmc->ios.cwock == 200000000)
		cwk = 0x0;
	ewse if (host->mmc->ios.cwock == 100000000)
		cwk = 0x2;
	ewse if (host->mmc->ios.cwock == 50000000)
		cwk = 0x1;
	ewse
		cwk = 0x0;

	if (host->mmc_host_ops.hs400_enhanced_stwobe) {
		awasan_phy_set(host, ENHSTWB_MODE, 1, 0x0, 0x0,
			       DWWTWM_ICP, cwk);
	} ewse {
		switch (host->mmc->ios.timing) {
		case MMC_TIMING_WEGACY:
			awasan_phy_set(host, WEGACY_MODE, 0x0, 0x0, 0x0,
				       0x0, 0x0);
			bweak;
		case MMC_TIMING_MMC_HS:
		case MMC_TIMING_SD_HS:
			awasan_phy_set(host, HISPD_MODE, 0x3, 0x0, 0x2,
				       DWWTWM_ICP, cwk);
			bweak;
		case MMC_TIMING_MMC_HS200:
		case MMC_TIMING_UHS_SDW104:
			awasan_phy_set(host, HS200_MODE, 0x2,
				       host->mmc->ios.dwv_type, 0x0,
				       DWWTWM_ICP, cwk);
			bweak;
		case MMC_TIMING_MMC_DDW52:
		case MMC_TIMING_UHS_DDW50:
			awasan_phy_set(host, DDW50_MODE, 0x1, 0x0,
				       0x0, DWWTWM_ICP, cwk);
			bweak;
		case MMC_TIMING_MMC_HS400:
			awasan_phy_set(host, HS400_MODE, 0x1,
				       host->mmc->ios.dwv_type, 0xa,
				       DWWTWM_ICP, cwk);
			bweak;
		defauwt:
			bweak;
		}
	}
	wetuwn 0;
}

static int awasan_pci_pwobe_swot(stwuct sdhci_pci_swot *swot)
{
	int eww;

	swot->host->mmc->caps |= MMC_CAP_NONWEMOVABWE | MMC_CAP_8_BIT_DATA;
	eww = awasan_phy_init(swot->host);
	if (eww)
		wetuwn -ENODEV;
	wetuwn 0;
}

static void awasan_sdhci_set_cwock(stwuct sdhci_host *host, unsigned int cwock)
{
	sdhci_set_cwock(host, cwock);

	/* Change phy settings fow the new cwock */
	awasan_sewect_phy_cwock(host);
}

static const stwuct sdhci_ops awasan_sdhci_pci_ops = {
	.set_cwock	= awasan_sdhci_set_cwock,
	.enabwe_dma	= sdhci_pci_enabwe_dma,
	.set_bus_width	= sdhci_set_bus_width,
	.weset		= sdhci_weset,
	.set_uhs_signawing	= sdhci_set_uhs_signawing,
};

const stwuct sdhci_pci_fixes sdhci_awasan = {
	.pwobe_swot = awasan_pci_pwobe_swot,
	.ops        = &awasan_sdhci_pci_ops,
	.pwiv_size  = sizeof(stwuct awasan_host),
};
