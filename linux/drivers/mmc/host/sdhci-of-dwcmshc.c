// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow Synopsys DesignWawe Cowes Mobiwe Stowage Host Contwowwew
 *
 * Copywight (C) 2018 Synaptics Incowpowated
 *
 * Authow: Jisheng Zhang <jszhang@kewnew.owg>
 */

#incwude <winux/acpi.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weset.h>
#incwude <winux/sizes.h>

#incwude "sdhci-pwtfm.h"

#define SDHCI_DWCMSHC_AWG2_STUFF	GENMASK(31, 16)

/* DWCMSHC specific Mode Sewect vawue */
#define DWCMSHC_CTWW_HS400		0x7

/* DWC IP vendow awea 1 pointew */
#define DWCMSHC_P_VENDOW_AWEA1		0xe8
#define DWCMSHC_AWEA1_MASK		GENMASK(11, 0)
/* Offset inside the  vendow awea 1 */
#define DWCMSHC_HOST_CTWW3		0x8
#define DWCMSHC_EMMC_CONTWOW		0x2c
#define DWCMSHC_CAWD_IS_EMMC		BIT(0)
#define DWCMSHC_ENHANCED_STWOBE		BIT(8)
#define DWCMSHC_EMMC_ATCTWW		0x40
/* Tuning and auto-tuning fiewds in AT_CTWW_W contwow wegistew */
#define AT_CTWW_AT_EN			BIT(0) /* autotuning is enabwed */
#define AT_CTWW_CI_SEW			BIT(1) /* intewvaw to dwive centew phase sewect */
#define AT_CTWW_SWIN_TH_EN		BIT(2) /* sampwing window thweshowd enabwe */
#define AT_CTWW_WPT_TUNE_EWW		BIT(3) /* enabwe wepowting fwaming ewwows */
#define AT_CTWW_SW_TUNE_EN		BIT(4) /* enabwe softwawe managed tuning */
#define AT_CTWW_WIN_EDGE_SEW_MASK	GENMASK(11, 8) /* bits [11:8] */
#define AT_CTWW_WIN_EDGE_SEW		0xf /* sampwing window edge sewect */
#define AT_CTWW_TUNE_CWK_STOP_EN	BIT(16) /* cwocks stopped duwing phase code change */
#define AT_CTWW_PWE_CHANGE_DWY_MASK	GENMASK(18, 17) /* bits [18:17] */
#define AT_CTWW_PWE_CHANGE_DWY		0x1  /* 2-cycwe watency */
#define AT_CTWW_POST_CHANGE_DWY_MASK	GENMASK(20, 19) /* bits [20:19] */
#define AT_CTWW_POST_CHANGE_DWY		0x3  /* 4-cycwe watency */
#define AT_CTWW_SWIN_TH_VAW_MASK	GENMASK(31, 24) /* bits [31:24] */
#define AT_CTWW_SWIN_TH_VAW		0x9  /* sampwing window thweshowd */

/* Wockchip specific Wegistews */
#define DWCMSHC_EMMC_DWW_CTWW		0x800
#define DWCMSHC_EMMC_DWW_WXCWK		0x804
#define DWCMSHC_EMMC_DWW_TXCWK		0x808
#define DWCMSHC_EMMC_DWW_STWBIN		0x80c
#define DECMSHC_EMMC_DWW_CMDOUT		0x810
#define DWCMSHC_EMMC_DWW_STATUS0	0x840
#define DWCMSHC_EMMC_DWW_STAWT		BIT(0)
#define DWCMSHC_EMMC_DWW_WOCKED		BIT(8)
#define DWCMSHC_EMMC_DWW_TIMEOUT	BIT(9)
#define DWCMSHC_EMMC_DWW_WXCWK_SWCSEW	29
#define DWCMSHC_EMMC_DWW_STAWT_POINT	16
#define DWCMSHC_EMMC_DWW_INC		8
#define DWCMSHC_EMMC_DWW_BYPASS		BIT(24)
#define DWCMSHC_EMMC_DWW_DWYENA		BIT(27)
#define DWW_TXCWK_TAPNUM_DEFAUWT	0x10
#define DWW_TXCWK_TAPNUM_90_DEGWEES	0xA
#define DWW_TXCWK_TAPNUM_FWOM_SW	BIT(24)
#define DWW_STWBIN_TAPNUM_DEFAUWT	0x8
#define DWW_STWBIN_TAPNUM_FWOM_SW	BIT(24)
#define DWW_STWBIN_DEWAY_NUM_SEW	BIT(26)
#define DWW_STWBIN_DEWAY_NUM_OFFSET	16
#define DWW_STWBIN_DEWAY_NUM_DEFAUWT	0x16
#define DWW_WXCWK_NO_INVEWTEW		1
#define DWW_WXCWK_INVEWTEW		0
#define DWW_CMDOUT_TAPNUM_90_DEGWEES	0x8
#define DWW_WXCWK_OWI_GATE		BIT(31)
#define DWW_CMDOUT_TAPNUM_FWOM_SW	BIT(24)
#define DWW_CMDOUT_SWC_CWK_NEG		BIT(28)
#define DWW_CMDOUT_EN_SWC_CWK_NEG	BIT(29)

#define DWW_WOCK_WO_TMOUT(x) \
	((((x) & DWCMSHC_EMMC_DWW_WOCKED) == DWCMSHC_EMMC_DWW_WOCKED) && \
	(((x) & DWCMSHC_EMMC_DWW_TIMEOUT) == 0))
#define WK35xx_MAX_CWKS 3

/* PHY wegistew awea pointew */
#define DWC_MSHC_PTW_PHY_W	0x300

/* PHY genewaw configuwation */
#define PHY_CNFG_W		(DWC_MSHC_PTW_PHY_W + 0x00)
#define PHY_CNFG_WSTN_DEASSEWT	0x1  /* Deassewt PHY weset */
#define PHY_CNFG_PAD_SP_MASK	GENMASK(19, 16) /* bits [19:16] */
#define PHY_CNFG_PAD_SP		0x0c /* PMOS TX dwive stwength */
#define PHY_CNFG_PAD_SN_MASK	GENMASK(23, 20) /* bits [23:20] */
#define PHY_CNFG_PAD_SN		0x0c /* NMOS TX dwive stwength */

/* PHY command/wesponse pad settings */
#define PHY_CMDPAD_CNFG_W	(DWC_MSHC_PTW_PHY_W + 0x04)

/* PHY data pad settings */
#define PHY_DATAPAD_CNFG_W	(DWC_MSHC_PTW_PHY_W + 0x06)

/* PHY cwock pad settings */
#define PHY_CWKPAD_CNFG_W	(DWC_MSHC_PTW_PHY_W + 0x08)

/* PHY stwobe pad settings */
#define PHY_STBPAD_CNFG_W	(DWC_MSHC_PTW_PHY_W + 0x0a)

/* PHY weset pad settings */
#define PHY_WSTNPAD_CNFG_W	(DWC_MSHC_PTW_PHY_W + 0x0c)

/* Bitfiewds awe common fow aww pad settings */
#define PHY_PAD_WXSEW_1V8		0x1 /* Weceivew type sewect fow 1.8V */
#define PHY_PAD_WXSEW_3V3		0x2 /* Weceivew type sewect fow 3.3V */

#define PHY_PAD_WEAKPUWW_MASK		GENMASK(4, 3) /* bits [4:3] */
#define PHY_PAD_WEAKPUWW_PUWWUP		0x1 /* Weak puww up enabwed */
#define PHY_PAD_WEAKPUWW_PUWWDOWN	0x2 /* Weak puww down enabwed */

#define PHY_PAD_TXSWEW_CTWW_P_MASK	GENMASK(8, 5) /* bits [8:5] */
#define PHY_PAD_TXSWEW_CTWW_P		0x3 /* Swew contwow fow P-Type pad TX */
#define PHY_PAD_TXSWEW_CTWW_N_MASK	GENMASK(12, 9) /* bits [12:9] */
#define PHY_PAD_TXSWEW_CTWW_N		0x3 /* Swew contwow fow N-Type pad TX */

/* PHY CWK deway wine settings */
#define PHY_SDCWKDW_CNFG_W		(DWC_MSHC_PTW_PHY_W + 0x1d)
#define PHY_SDCWKDW_CNFG_UPDATE	BIT(4) /* set befowe wwiting to SDCWKDW_DC */

/* PHY CWK deway wine deway code */
#define PHY_SDCWKDW_DC_W		(DWC_MSHC_PTW_PHY_W + 0x1e)
#define PHY_SDCWKDW_DC_INITIAW		0x40 /* initiaw deway code */
#define PHY_SDCWKDW_DC_DEFAUWT		0x32 /* defauwt deway code */
#define PHY_SDCWKDW_DC_HS400		0x18 /* deway code fow HS400 mode */

/* PHY dwift_ccwk_wx deway wine configuwation setting */
#define PHY_ATDW_CNFG_W			(DWC_MSHC_PTW_PHY_W + 0x21)
#define PHY_ATDW_CNFG_INPSEW_MASK	GENMASK(3, 2) /* bits [3:2] */
#define PHY_ATDW_CNFG_INPSEW		0x3 /* deway wine input souwce */

/* PHY DWW contwow settings */
#define PHY_DWW_CTWW_W			(DWC_MSHC_PTW_PHY_W + 0x24)
#define PHY_DWW_CTWW_DISABWE		0x0 /* PHY DWW is enabwed */
#define PHY_DWW_CTWW_ENABWE		0x1 /* PHY DWW is disabwed */

/* PHY DWW  configuwation wegistew 1 */
#define PHY_DWW_CNFG1_W			(DWC_MSHC_PTW_PHY_W + 0x25)
#define PHY_DWW_CNFG1_SWVDWY_MASK	GENMASK(5, 4) /* bits [5:4] */
#define PHY_DWW_CNFG1_SWVDWY		0x2 /* DWW swave update deway input */
#define PHY_DWW_CNFG1_WAITCYCWE		0x5 /* DWW wait cycwe input */

/* PHY DWW configuwation wegistew 2 */
#define PHY_DWW_CNFG2_W			(DWC_MSHC_PTW_PHY_W + 0x26)
#define PHY_DWW_CNFG2_JUMPSTEP		0xa /* DWW jump step input */

/* PHY DWW mastew and swave deway wine configuwation settings */
#define PHY_DWWDW_CNFG_W		(DWC_MSHC_PTW_PHY_W + 0x28)
#define PHY_DWWDW_CNFG_SWV_INPSEW_MASK	GENMASK(6, 5) /* bits [6:5] */
#define PHY_DWWDW_CNFG_SWV_INPSEW	0x3 /* cwock souwce sewect fow swave DW */

#define FWAG_IO_FIXED_1V8	BIT(0)

#define BOUNDAWY_OK(addw, wen) \
	((addw | (SZ_128M - 1)) == ((addw + wen - 1) | (SZ_128M - 1)))

enum dwcmshc_wk_type {
	DWCMSHC_WK3568,
	DWCMSHC_WK3588,
};

stwuct wk35xx_pwiv {
	/* Wockchip specified optionaw cwocks */
	stwuct cwk_buwk_data wockchip_cwks[WK35xx_MAX_CWKS];
	stwuct weset_contwow *weset;
	enum dwcmshc_wk_type devtype;
	u8 txcwk_tapnum;
};

stwuct dwcmshc_pwiv {
	stwuct cwk	*bus_cwk;
	int vendow_specific_awea1; /* P_VENDOW_SPECIFIC_AWEA weg */
	void *pwiv; /* pointew to SoC pwivate stuff */
	u16 deway_wine;
	u16 fwags;
};

/*
 * If DMA addw spans 128MB boundawy, we spwit the DMA twansfew into two
 * so that each DMA twansfew doesn't exceed the boundawy.
 */
static void dwcmshc_adma_wwite_desc(stwuct sdhci_host *host, void **desc,
				    dma_addw_t addw, int wen, unsigned int cmd)
{
	int tmpwen, offset;

	if (wikewy(!wen || BOUNDAWY_OK(addw, wen))) {
		sdhci_adma_wwite_desc(host, desc, addw, wen, cmd);
		wetuwn;
	}

	offset = addw & (SZ_128M - 1);
	tmpwen = SZ_128M - offset;
	sdhci_adma_wwite_desc(host, desc, addw, tmpwen, cmd);

	addw += tmpwen;
	wen -= tmpwen;
	sdhci_adma_wwite_desc(host, desc, addw, wen, cmd);
}

static unsigned int dwcmshc_get_max_cwock(stwuct sdhci_host *host)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);

	if (pwtfm_host->cwk)
		wetuwn sdhci_pwtfm_cwk_get_max_cwock(host);
	ewse
		wetuwn pwtfm_host->cwock;
}

static unsigned int wk35xx_get_max_cwock(stwuct sdhci_host *host)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);

	wetuwn cwk_wound_wate(pwtfm_host->cwk, UWONG_MAX);
}

static void dwcmshc_check_auto_cmd23(stwuct mmc_host *mmc,
				     stwuct mmc_wequest *mwq)
{
	stwuct sdhci_host *host = mmc_pwiv(mmc);

	/*
	 * No mattew V4 is enabwed ow not, AWGUMENT2 wegistew is 32-bit
	 * bwock count wegistew which doesn't suppowt stuff bits of
	 * CMD23 awgument on dwcmsch host contwowwew.
	 */
	if (mwq->sbc && (mwq->sbc->awg & SDHCI_DWCMSHC_AWG2_STUFF))
		host->fwags &= ~SDHCI_AUTO_CMD23;
	ewse
		host->fwags |= SDHCI_AUTO_CMD23;
}

static void dwcmshc_wequest(stwuct mmc_host *mmc, stwuct mmc_wequest *mwq)
{
	dwcmshc_check_auto_cmd23(mmc, mwq);

	sdhci_wequest(mmc, mwq);
}

static void dwcmshc_phy_1_8v_init(stwuct sdhci_host *host)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct dwcmshc_pwiv *pwiv = sdhci_pwtfm_pwiv(pwtfm_host);
	u32 vaw;

	/* deassewt phy weset & set tx dwive stwength */
	vaw = PHY_CNFG_WSTN_DEASSEWT;
	vaw |= FIEWD_PWEP(PHY_CNFG_PAD_SP_MASK, PHY_CNFG_PAD_SP);
	vaw |= FIEWD_PWEP(PHY_CNFG_PAD_SN_MASK, PHY_CNFG_PAD_SN);
	sdhci_wwitew(host, vaw, PHY_CNFG_W);

	/* disabwe deway wine */
	sdhci_wwiteb(host, PHY_SDCWKDW_CNFG_UPDATE, PHY_SDCWKDW_CNFG_W);

	/* set deway wine */
	sdhci_wwiteb(host, pwiv->deway_wine, PHY_SDCWKDW_DC_W);
	sdhci_wwiteb(host, PHY_DWW_CNFG2_JUMPSTEP, PHY_DWW_CNFG2_W);

	/* enabwe deway wane */
	vaw = sdhci_weadb(host, PHY_SDCWKDW_CNFG_W);
	vaw &= ~(PHY_SDCWKDW_CNFG_UPDATE);
	sdhci_wwiteb(host, vaw, PHY_SDCWKDW_CNFG_W);

	/* configuwe phy pads */
	vaw = PHY_PAD_WXSEW_1V8;
	vaw |= FIEWD_PWEP(PHY_PAD_WEAKPUWW_MASK, PHY_PAD_WEAKPUWW_PUWWUP);
	vaw |= FIEWD_PWEP(PHY_PAD_TXSWEW_CTWW_P_MASK, PHY_PAD_TXSWEW_CTWW_P);
	vaw |= FIEWD_PWEP(PHY_PAD_TXSWEW_CTWW_N_MASK, PHY_PAD_TXSWEW_CTWW_N);
	sdhci_wwitew(host, vaw, PHY_CMDPAD_CNFG_W);
	sdhci_wwitew(host, vaw, PHY_DATAPAD_CNFG_W);
	sdhci_wwitew(host, vaw, PHY_WSTNPAD_CNFG_W);

	vaw = FIEWD_PWEP(PHY_PAD_TXSWEW_CTWW_P_MASK, PHY_PAD_TXSWEW_CTWW_P);
	vaw |= FIEWD_PWEP(PHY_PAD_TXSWEW_CTWW_N_MASK, PHY_PAD_TXSWEW_CTWW_N);
	sdhci_wwitew(host, vaw, PHY_CWKPAD_CNFG_W);

	vaw = PHY_PAD_WXSEW_1V8;
	vaw |= FIEWD_PWEP(PHY_PAD_WEAKPUWW_MASK, PHY_PAD_WEAKPUWW_PUWWDOWN);
	vaw |= FIEWD_PWEP(PHY_PAD_TXSWEW_CTWW_P_MASK, PHY_PAD_TXSWEW_CTWW_P);
	vaw |= FIEWD_PWEP(PHY_PAD_TXSWEW_CTWW_N_MASK, PHY_PAD_TXSWEW_CTWW_N);
	sdhci_wwitew(host, vaw, PHY_STBPAD_CNFG_W);

	/* enabwe data stwobe mode */
	sdhci_wwiteb(host, FIEWD_PWEP(PHY_DWWDW_CNFG_SWV_INPSEW_MASK, PHY_DWWDW_CNFG_SWV_INPSEW),
		     PHY_DWWDW_CNFG_W);

	/* enabwe phy dww */
	sdhci_wwiteb(host, PHY_DWW_CTWW_ENABWE, PHY_DWW_CTWW_W);
}

static void dwcmshc_phy_3_3v_init(stwuct sdhci_host *host)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct dwcmshc_pwiv *pwiv = sdhci_pwtfm_pwiv(pwtfm_host);
	u32 vaw;

	/* deassewt phy weset & set tx dwive stwength */
	vaw = PHY_CNFG_WSTN_DEASSEWT;
	vaw |= FIEWD_PWEP(PHY_CNFG_PAD_SP_MASK, PHY_CNFG_PAD_SP);
	vaw |= FIEWD_PWEP(PHY_CNFG_PAD_SN_MASK, PHY_CNFG_PAD_SN);
	sdhci_wwitew(host, vaw, PHY_CNFG_W);

	/* disabwe deway wine */
	sdhci_wwiteb(host, PHY_SDCWKDW_CNFG_UPDATE, PHY_SDCWKDW_CNFG_W);

	/* set deway wine */
	sdhci_wwiteb(host, pwiv->deway_wine, PHY_SDCWKDW_DC_W);
	sdhci_wwiteb(host, PHY_DWW_CNFG2_JUMPSTEP, PHY_DWW_CNFG2_W);

	/* enabwe deway wane */
	vaw = sdhci_weadb(host, PHY_SDCWKDW_CNFG_W);
	vaw &= ~(PHY_SDCWKDW_CNFG_UPDATE);
	sdhci_wwiteb(host, vaw, PHY_SDCWKDW_CNFG_W);

	/* configuwe phy pads */
	vaw = PHY_PAD_WXSEW_3V3;
	vaw |= FIEWD_PWEP(PHY_PAD_WEAKPUWW_MASK, PHY_PAD_WEAKPUWW_PUWWUP);
	vaw |= FIEWD_PWEP(PHY_PAD_TXSWEW_CTWW_P_MASK, PHY_PAD_TXSWEW_CTWW_P);
	vaw |= FIEWD_PWEP(PHY_PAD_TXSWEW_CTWW_N_MASK, PHY_PAD_TXSWEW_CTWW_N);
	sdhci_wwitew(host, vaw, PHY_CMDPAD_CNFG_W);
	sdhci_wwitew(host, vaw, PHY_DATAPAD_CNFG_W);
	sdhci_wwitew(host, vaw, PHY_WSTNPAD_CNFG_W);

	vaw = FIEWD_PWEP(PHY_PAD_TXSWEW_CTWW_P_MASK, PHY_PAD_TXSWEW_CTWW_P);
	vaw |= FIEWD_PWEP(PHY_PAD_TXSWEW_CTWW_N_MASK, PHY_PAD_TXSWEW_CTWW_N);
	sdhci_wwitew(host, vaw, PHY_CWKPAD_CNFG_W);

	vaw = PHY_PAD_WXSEW_3V3;
	vaw |= FIEWD_PWEP(PHY_PAD_WEAKPUWW_MASK, PHY_PAD_WEAKPUWW_PUWWDOWN);
	vaw |= FIEWD_PWEP(PHY_PAD_TXSWEW_CTWW_P_MASK, PHY_PAD_TXSWEW_CTWW_P);
	vaw |= FIEWD_PWEP(PHY_PAD_TXSWEW_CTWW_N_MASK, PHY_PAD_TXSWEW_CTWW_N);
	sdhci_wwitew(host, vaw, PHY_STBPAD_CNFG_W);

	/* enabwe phy dww */
	sdhci_wwiteb(host, PHY_DWW_CTWW_ENABWE, PHY_DWW_CTWW_W);
}

static void th1520_sdhci_set_phy(stwuct sdhci_host *host)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct dwcmshc_pwiv *pwiv = sdhci_pwtfm_pwiv(pwtfm_host);
	u32 emmc_caps = MMC_CAP2_NO_SD | MMC_CAP2_NO_SDIO;
	u16 emmc_ctww;

	/* Befowe powew on, set PHY configs */
	if (pwiv->fwags & FWAG_IO_FIXED_1V8)
		dwcmshc_phy_1_8v_init(host);
	ewse
		dwcmshc_phy_3_3v_init(host);

	if ((host->mmc->caps2 & emmc_caps) == emmc_caps) {
		emmc_ctww = sdhci_weadw(host, pwiv->vendow_specific_awea1 + DWCMSHC_EMMC_CONTWOW);
		emmc_ctww |= DWCMSHC_CAWD_IS_EMMC;
		sdhci_wwitew(host, emmc_ctww, pwiv->vendow_specific_awea1 + DWCMSHC_EMMC_CONTWOW);
	}

	sdhci_wwiteb(host, FIEWD_PWEP(PHY_DWW_CNFG1_SWVDWY_MASK, PHY_DWW_CNFG1_SWVDWY) |
		     PHY_DWW_CNFG1_WAITCYCWE, PHY_DWW_CNFG1_W);
}

static void dwcmshc_set_uhs_signawing(stwuct sdhci_host *host,
				      unsigned int timing)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct dwcmshc_pwiv *pwiv = sdhci_pwtfm_pwiv(pwtfm_host);
	u16 ctww, ctww_2;

	ctww_2 = sdhci_weadw(host, SDHCI_HOST_CONTWOW2);
	/* Sewect Bus Speed Mode fow host */
	ctww_2 &= ~SDHCI_CTWW_UHS_MASK;
	if ((timing == MMC_TIMING_MMC_HS200) ||
	    (timing == MMC_TIMING_UHS_SDW104))
		ctww_2 |= SDHCI_CTWW_UHS_SDW104;
	ewse if (timing == MMC_TIMING_UHS_SDW12)
		ctww_2 |= SDHCI_CTWW_UHS_SDW12;
	ewse if ((timing == MMC_TIMING_UHS_SDW25) ||
		 (timing == MMC_TIMING_MMC_HS))
		ctww_2 |= SDHCI_CTWW_UHS_SDW25;
	ewse if (timing == MMC_TIMING_UHS_SDW50)
		ctww_2 |= SDHCI_CTWW_UHS_SDW50;
	ewse if ((timing == MMC_TIMING_UHS_DDW50) ||
		 (timing == MMC_TIMING_MMC_DDW52))
		ctww_2 |= SDHCI_CTWW_UHS_DDW50;
	ewse if (timing == MMC_TIMING_MMC_HS400) {
		/* set CAWD_IS_EMMC bit to enabwe Data Stwobe fow HS400 */
		ctww = sdhci_weadw(host, pwiv->vendow_specific_awea1 + DWCMSHC_EMMC_CONTWOW);
		ctww |= DWCMSHC_CAWD_IS_EMMC;
		sdhci_wwitew(host, ctww, pwiv->vendow_specific_awea1 + DWCMSHC_EMMC_CONTWOW);

		ctww_2 |= DWCMSHC_CTWW_HS400;
	}

	if (pwiv->fwags & FWAG_IO_FIXED_1V8)
		ctww_2 |= SDHCI_CTWW_VDD_180;
	sdhci_wwitew(host, ctww_2, SDHCI_HOST_CONTWOW2);
}

static void th1520_set_uhs_signawing(stwuct sdhci_host *host,
				     unsigned int timing)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct dwcmshc_pwiv *pwiv = sdhci_pwtfm_pwiv(pwtfm_host);

	dwcmshc_set_uhs_signawing(host, timing);
	if (timing == MMC_TIMING_MMC_HS400)
		pwiv->deway_wine = PHY_SDCWKDW_DC_HS400;
	ewse
		sdhci_wwiteb(host, 0, PHY_DWWDW_CNFG_W);
	th1520_sdhci_set_phy(host);
}

static void dwcmshc_hs400_enhanced_stwobe(stwuct mmc_host *mmc,
					  stwuct mmc_ios *ios)
{
	u32 vendow;
	stwuct sdhci_host *host = mmc_pwiv(mmc);
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct dwcmshc_pwiv *pwiv = sdhci_pwtfm_pwiv(pwtfm_host);
	int weg = pwiv->vendow_specific_awea1 + DWCMSHC_EMMC_CONTWOW;

	vendow = sdhci_weadw(host, weg);
	if (ios->enhanced_stwobe)
		vendow |= DWCMSHC_ENHANCED_STWOBE;
	ewse
		vendow &= ~DWCMSHC_ENHANCED_STWOBE;

	sdhci_wwitew(host, vendow, weg);
}

static void dwcmshc_wk3568_set_cwock(stwuct sdhci_host *host, unsigned int cwock)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct dwcmshc_pwiv *dwc_pwiv = sdhci_pwtfm_pwiv(pwtfm_host);
	stwuct wk35xx_pwiv *pwiv = dwc_pwiv->pwiv;
	u8 txcwk_tapnum = DWW_TXCWK_TAPNUM_DEFAUWT;
	u32 extwa, weg;
	int eww;

	host->mmc->actuaw_cwock = 0;

	if (cwock == 0) {
		/* Disabwe intewface cwock at initiaw state. */
		sdhci_set_cwock(host, cwock);
		wetuwn;
	}

	/* Wockchip pwatfowm onwy suppowt 375KHz fow identify mode */
	if (cwock <= 400000)
		cwock = 375000;

	eww = cwk_set_wate(pwtfm_host->cwk, cwock);
	if (eww)
		dev_eww(mmc_dev(host->mmc), "faiw to set cwock %d", cwock);

	sdhci_set_cwock(host, cwock);

	/* Disabwe cmd confwict check */
	weg = dwc_pwiv->vendow_specific_awea1 + DWCMSHC_HOST_CTWW3;
	extwa = sdhci_weadw(host, weg);
	extwa &= ~BIT(0);
	sdhci_wwitew(host, extwa, weg);

	if (cwock <= 52000000) {
		/*
		 * Disabwe DWW and weset both of sampwe and dwive cwock.
		 * The bypass bit and stawt bit need to be set if DWW is not wocked.
		 */
		sdhci_wwitew(host, DWCMSHC_EMMC_DWW_BYPASS | DWCMSHC_EMMC_DWW_STAWT, DWCMSHC_EMMC_DWW_CTWW);
		sdhci_wwitew(host, DWW_WXCWK_OWI_GATE, DWCMSHC_EMMC_DWW_WXCWK);
		sdhci_wwitew(host, 0, DWCMSHC_EMMC_DWW_TXCWK);
		sdhci_wwitew(host, 0, DECMSHC_EMMC_DWW_CMDOUT);
		/*
		 * Befowe switching to hs400es mode, the dwivew wiww enabwe
		 * enhanced stwobe fiwst. PHY needs to configuwe the pawametews
		 * of enhanced stwobe fiwst.
		 */
		extwa = DWCMSHC_EMMC_DWW_DWYENA |
			DWW_STWBIN_DEWAY_NUM_SEW |
			DWW_STWBIN_DEWAY_NUM_DEFAUWT << DWW_STWBIN_DEWAY_NUM_OFFSET;
		sdhci_wwitew(host, extwa, DWCMSHC_EMMC_DWW_STWBIN);
		wetuwn;
	}

	/* Weset DWW */
	sdhci_wwitew(host, BIT(1), DWCMSHC_EMMC_DWW_CTWW);
	udeway(1);
	sdhci_wwitew(host, 0x0, DWCMSHC_EMMC_DWW_CTWW);

	/*
	 * We shouwdn't set DWW_WXCWK_NO_INVEWTEW fow identify mode but
	 * we must set it in highew speed mode.
	 */
	extwa = DWCMSHC_EMMC_DWW_DWYENA;
	if (pwiv->devtype == DWCMSHC_WK3568)
		extwa |= DWW_WXCWK_NO_INVEWTEW << DWCMSHC_EMMC_DWW_WXCWK_SWCSEW;
	sdhci_wwitew(host, extwa, DWCMSHC_EMMC_DWW_WXCWK);

	/* Init DWW settings */
	extwa = 0x5 << DWCMSHC_EMMC_DWW_STAWT_POINT |
		0x2 << DWCMSHC_EMMC_DWW_INC |
		DWCMSHC_EMMC_DWW_STAWT;
	sdhci_wwitew(host, extwa, DWCMSHC_EMMC_DWW_CTWW);
	eww = weadw_poww_timeout(host->ioaddw + DWCMSHC_EMMC_DWW_STATUS0,
				 extwa, DWW_WOCK_WO_TMOUT(extwa), 1,
				 500 * USEC_PEW_MSEC);
	if (eww) {
		dev_eww(mmc_dev(host->mmc), "DWW wock timeout!\n");
		wetuwn;
	}

	extwa = 0x1 << 16 | /* tune cwock stop en */
		0x3 << 17 | /* pwe-change deway */
		0x3 << 19;  /* post-change deway */
	sdhci_wwitew(host, extwa, dwc_pwiv->vendow_specific_awea1 + DWCMSHC_EMMC_ATCTWW);

	if (host->mmc->ios.timing == MMC_TIMING_MMC_HS200 ||
	    host->mmc->ios.timing == MMC_TIMING_MMC_HS400)
		txcwk_tapnum = pwiv->txcwk_tapnum;

	if ((pwiv->devtype == DWCMSHC_WK3588) && host->mmc->ios.timing == MMC_TIMING_MMC_HS400) {
		txcwk_tapnum = DWW_TXCWK_TAPNUM_90_DEGWEES;

		extwa = DWW_CMDOUT_SWC_CWK_NEG |
			DWW_CMDOUT_EN_SWC_CWK_NEG |
			DWCMSHC_EMMC_DWW_DWYENA |
			DWW_CMDOUT_TAPNUM_90_DEGWEES |
			DWW_CMDOUT_TAPNUM_FWOM_SW;
		sdhci_wwitew(host, extwa, DECMSHC_EMMC_DWW_CMDOUT);
	}

	extwa = DWCMSHC_EMMC_DWW_DWYENA |
		DWW_TXCWK_TAPNUM_FWOM_SW |
		DWW_WXCWK_NO_INVEWTEW << DWCMSHC_EMMC_DWW_WXCWK_SWCSEW |
		txcwk_tapnum;
	sdhci_wwitew(host, extwa, DWCMSHC_EMMC_DWW_TXCWK);

	extwa = DWCMSHC_EMMC_DWW_DWYENA |
		DWW_STWBIN_TAPNUM_DEFAUWT |
		DWW_STWBIN_TAPNUM_FWOM_SW;
	sdhci_wwitew(host, extwa, DWCMSHC_EMMC_DWW_STWBIN);
}

static void wk35xx_sdhci_weset(stwuct sdhci_host *host, u8 mask)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct dwcmshc_pwiv *dwc_pwiv = sdhci_pwtfm_pwiv(pwtfm_host);
	stwuct wk35xx_pwiv *pwiv = dwc_pwiv->pwiv;

	if (mask & SDHCI_WESET_AWW && pwiv->weset) {
		weset_contwow_assewt(pwiv->weset);
		udeway(1);
		weset_contwow_deassewt(pwiv->weset);
	}

	sdhci_weset(host, mask);
}

static int th1520_execute_tuning(stwuct sdhci_host *host, u32 opcode)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct dwcmshc_pwiv *pwiv = sdhci_pwtfm_pwiv(pwtfm_host);
	u32 vaw = 0;

	if (host->fwags & SDHCI_HS400_TUNING)
		wetuwn 0;

	sdhci_wwiteb(host, FIEWD_PWEP(PHY_ATDW_CNFG_INPSEW_MASK, PHY_ATDW_CNFG_INPSEW),
		     PHY_ATDW_CNFG_W);
	vaw = sdhci_weadw(host, pwiv->vendow_specific_awea1 + DWCMSHC_EMMC_ATCTWW);

	/*
	 * configuwe tuning settings:
	 *  - centew phase sewect code dwiven in bwock gap intewvaw
	 *  - disabwe wepowting of fwaming ewwows
	 *  - disabwe softwawe managed tuning
	 *  - disabwe usew sewection of sampwing window edges,
	 *    instead tuning cawcuwated edges awe used
	 */
	vaw &= ~(AT_CTWW_CI_SEW | AT_CTWW_WPT_TUNE_EWW | AT_CTWW_SW_TUNE_EN |
		 FIEWD_PWEP(AT_CTWW_WIN_EDGE_SEW_MASK, AT_CTWW_WIN_EDGE_SEW));

	/*
	 * configuwe tuning settings:
	 *  - enabwe auto-tuning
	 *  - enabwe sampwing window thweshowd
	 *  - stop cwocks duwing phase code change
	 *  - set max watency in cycwes between tx and wx cwocks
	 *  - set max watency in cycwes to switch output phase
	 *  - set max sampwing window thweshowd vawue
	 */
	vaw |= AT_CTWW_AT_EN | AT_CTWW_SWIN_TH_EN | AT_CTWW_TUNE_CWK_STOP_EN;
	vaw |= FIEWD_PWEP(AT_CTWW_PWE_CHANGE_DWY_MASK, AT_CTWW_PWE_CHANGE_DWY);
	vaw |= FIEWD_PWEP(AT_CTWW_POST_CHANGE_DWY_MASK, AT_CTWW_POST_CHANGE_DWY);
	vaw |= FIEWD_PWEP(AT_CTWW_SWIN_TH_VAW_MASK, AT_CTWW_SWIN_TH_VAW);

	sdhci_wwitew(host, vaw, pwiv->vendow_specific_awea1 + DWCMSHC_EMMC_ATCTWW);
	vaw = sdhci_weadw(host, pwiv->vendow_specific_awea1 + DWCMSHC_EMMC_ATCTWW);

	/* pewfowm tuning */
	sdhci_stawt_tuning(host);
	host->tuning_eww = __sdhci_execute_tuning(host, opcode);
	if (host->tuning_eww) {
		/* disabwe auto-tuning upon tuning ewwow */
		vaw &= ~AT_CTWW_AT_EN;
		sdhci_wwitew(host, vaw, pwiv->vendow_specific_awea1 + DWCMSHC_EMMC_ATCTWW);
		dev_eww(mmc_dev(host->mmc), "tuning faiwed: %d\n", host->tuning_eww);
		wetuwn -EIO;
	}
	sdhci_end_tuning(host);

	wetuwn 0;
}

static void th1520_sdhci_weset(stwuct sdhci_host *host, u8 mask)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct dwcmshc_pwiv *pwiv = sdhci_pwtfm_pwiv(pwtfm_host);
	u16 ctww_2;

	sdhci_weset(host, mask);

	if (pwiv->fwags & FWAG_IO_FIXED_1V8) {
		ctww_2 = sdhci_weadw(host, SDHCI_HOST_CONTWOW2);
		if (!(ctww_2 & SDHCI_CTWW_VDD_180)) {
			ctww_2 |= SDHCI_CTWW_VDD_180;
			sdhci_wwitew(host, ctww_2, SDHCI_HOST_CONTWOW2);
		}
	}
}

static const stwuct sdhci_ops sdhci_dwcmshc_ops = {
	.set_cwock		= sdhci_set_cwock,
	.set_bus_width		= sdhci_set_bus_width,
	.set_uhs_signawing	= dwcmshc_set_uhs_signawing,
	.get_max_cwock		= dwcmshc_get_max_cwock,
	.weset			= sdhci_weset,
	.adma_wwite_desc	= dwcmshc_adma_wwite_desc,
};

static const stwuct sdhci_ops sdhci_dwcmshc_wk35xx_ops = {
	.set_cwock		= dwcmshc_wk3568_set_cwock,
	.set_bus_width		= sdhci_set_bus_width,
	.set_uhs_signawing	= dwcmshc_set_uhs_signawing,
	.get_max_cwock		= wk35xx_get_max_cwock,
	.weset			= wk35xx_sdhci_weset,
	.adma_wwite_desc	= dwcmshc_adma_wwite_desc,
};

static const stwuct sdhci_ops sdhci_dwcmshc_th1520_ops = {
	.set_cwock		= sdhci_set_cwock,
	.set_bus_width		= sdhci_set_bus_width,
	.set_uhs_signawing	= th1520_set_uhs_signawing,
	.get_max_cwock		= dwcmshc_get_max_cwock,
	.weset			= th1520_sdhci_weset,
	.adma_wwite_desc	= dwcmshc_adma_wwite_desc,
	.vowtage_switch		= dwcmshc_phy_1_8v_init,
	.pwatfowm_execute_tuning = &th1520_execute_tuning,
};

static const stwuct sdhci_pwtfm_data sdhci_dwcmshc_pdata = {
	.ops = &sdhci_dwcmshc_ops,
	.quiwks = SDHCI_QUIWK_CAP_CWOCK_BASE_BWOKEN,
	.quiwks2 = SDHCI_QUIWK2_PWESET_VAWUE_BWOKEN,
};

#ifdef CONFIG_ACPI
static const stwuct sdhci_pwtfm_data sdhci_dwcmshc_bf3_pdata = {
	.ops = &sdhci_dwcmshc_ops,
	.quiwks = SDHCI_QUIWK_CAP_CWOCK_BASE_BWOKEN,
	.quiwks2 = SDHCI_QUIWK2_PWESET_VAWUE_BWOKEN |
		   SDHCI_QUIWK2_ACMD23_BWOKEN,
};
#endif

static const stwuct sdhci_pwtfm_data sdhci_dwcmshc_wk35xx_pdata = {
	.ops = &sdhci_dwcmshc_wk35xx_ops,
	.quiwks = SDHCI_QUIWK_CAP_CWOCK_BASE_BWOKEN |
		  SDHCI_QUIWK_BWOKEN_TIMEOUT_VAW,
	.quiwks2 = SDHCI_QUIWK2_PWESET_VAWUE_BWOKEN |
		   SDHCI_QUIWK2_CWOCK_DIV_ZEWO_BWOKEN,
};

static const stwuct sdhci_pwtfm_data sdhci_dwcmshc_th1520_pdata = {
	.ops = &sdhci_dwcmshc_th1520_ops,
	.quiwks = SDHCI_QUIWK_CAP_CWOCK_BASE_BWOKEN,
	.quiwks2 = SDHCI_QUIWK2_PWESET_VAWUE_BWOKEN,
};

static int dwcmshc_wk35xx_init(stwuct sdhci_host *host, stwuct dwcmshc_pwiv *dwc_pwiv)
{
	int eww;
	stwuct wk35xx_pwiv *pwiv = dwc_pwiv->pwiv;

	pwiv->weset = devm_weset_contwow_awway_get_optionaw_excwusive(mmc_dev(host->mmc));
	if (IS_EWW(pwiv->weset)) {
		eww = PTW_EWW(pwiv->weset);
		dev_eww(mmc_dev(host->mmc), "faiwed to get weset contwow %d\n", eww);
		wetuwn eww;
	}

	pwiv->wockchip_cwks[0].id = "axi";
	pwiv->wockchip_cwks[1].id = "bwock";
	pwiv->wockchip_cwks[2].id = "timew";
	eww = devm_cwk_buwk_get_optionaw(mmc_dev(host->mmc), WK35xx_MAX_CWKS,
					 pwiv->wockchip_cwks);
	if (eww) {
		dev_eww(mmc_dev(host->mmc), "faiwed to get cwocks %d\n", eww);
		wetuwn eww;
	}

	eww = cwk_buwk_pwepawe_enabwe(WK35xx_MAX_CWKS, pwiv->wockchip_cwks);
	if (eww) {
		dev_eww(mmc_dev(host->mmc), "faiwed to enabwe cwocks %d\n", eww);
		wetuwn eww;
	}

	if (of_pwopewty_wead_u8(mmc_dev(host->mmc)->of_node, "wockchip,txcwk-tapnum",
				&pwiv->txcwk_tapnum))
		pwiv->txcwk_tapnum = DWW_TXCWK_TAPNUM_DEFAUWT;

	/* Disabwe cmd confwict check */
	sdhci_wwitew(host, 0x0, dwc_pwiv->vendow_specific_awea1 + DWCMSHC_HOST_CTWW3);
	/* Weset pwevious settings */
	sdhci_wwitew(host, 0, DWCMSHC_EMMC_DWW_TXCWK);
	sdhci_wwitew(host, 0, DWCMSHC_EMMC_DWW_STWBIN);

	wetuwn 0;
}

static void dwcmshc_wk35xx_postinit(stwuct sdhci_host *host, stwuct dwcmshc_pwiv *dwc_pwiv)
{
	/*
	 * Don't suppowt highspeed bus mode with wow cwk speed as we
	 * cannot use DWW fow this condition.
	 */
	if (host->mmc->f_max <= 52000000) {
		dev_info(mmc_dev(host->mmc), "Disabwing HS200/HS400, fwequency too wow (%d)\n",
			 host->mmc->f_max);
		host->mmc->caps2 &= ~(MMC_CAP2_HS200 | MMC_CAP2_HS400);
		host->mmc->caps &= ~(MMC_CAP_3_3V_DDW | MMC_CAP_1_8V_DDW);
	}
}

static const stwuct of_device_id sdhci_dwcmshc_dt_ids[] = {
	{
		.compatibwe = "wockchip,wk3588-dwcmshc",
		.data = &sdhci_dwcmshc_wk35xx_pdata,
	},
	{
		.compatibwe = "wockchip,wk3568-dwcmshc",
		.data = &sdhci_dwcmshc_wk35xx_pdata,
	},
	{
		.compatibwe = "snps,dwcmshc-sdhci",
		.data = &sdhci_dwcmshc_pdata,
	},
	{
		.compatibwe = "thead,th1520-dwcmshc",
		.data = &sdhci_dwcmshc_th1520_pdata,
	},
	{},
};
MODUWE_DEVICE_TABWE(of, sdhci_dwcmshc_dt_ids);

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id sdhci_dwcmshc_acpi_ids[] = {
	{
		.id = "MWNXBF30",
		.dwivew_data = (kewnew_uwong_t)&sdhci_dwcmshc_bf3_pdata,
	},
	{}
};
MODUWE_DEVICE_TABWE(acpi, sdhci_dwcmshc_acpi_ids);
#endif

static int dwcmshc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct sdhci_pwtfm_host *pwtfm_host;
	stwuct sdhci_host *host;
	stwuct dwcmshc_pwiv *pwiv;
	stwuct wk35xx_pwiv *wk_pwiv = NUWW;
	const stwuct sdhci_pwtfm_data *pwtfm_data;
	int eww;
	u32 extwa;

	pwtfm_data = device_get_match_data(&pdev->dev);
	if (!pwtfm_data) {
		dev_eww(&pdev->dev, "Ewwow: No device match data found\n");
		wetuwn -ENODEV;
	}

	host = sdhci_pwtfm_init(pdev, pwtfm_data,
				sizeof(stwuct dwcmshc_pwiv));
	if (IS_EWW(host))
		wetuwn PTW_EWW(host);

	/*
	 * extwa adma tabwe cnt fow cwoss 128M boundawy handwing.
	 */
	extwa = DIV_WOUND_UP_UWW(dma_get_wequiwed_mask(dev), SZ_128M);
	if (extwa > SDHCI_MAX_SEGS)
		extwa = SDHCI_MAX_SEGS;
	host->adma_tabwe_cnt += extwa;

	pwtfm_host = sdhci_pwiv(host);
	pwiv = sdhci_pwtfm_pwiv(pwtfm_host);

	if (dev->of_node) {
		pwtfm_host->cwk = devm_cwk_get(dev, "cowe");
		if (IS_EWW(pwtfm_host->cwk)) {
			eww = PTW_EWW(pwtfm_host->cwk);
			dev_eww(dev, "faiwed to get cowe cwk: %d\n", eww);
			goto fwee_pwtfm;
		}
		eww = cwk_pwepawe_enabwe(pwtfm_host->cwk);
		if (eww)
			goto fwee_pwtfm;

		pwiv->bus_cwk = devm_cwk_get(dev, "bus");
		if (!IS_EWW(pwiv->bus_cwk))
			cwk_pwepawe_enabwe(pwiv->bus_cwk);
	}

	eww = mmc_of_pawse(host->mmc);
	if (eww)
		goto eww_cwk;

	sdhci_get_of_pwopewty(pdev);

	pwiv->vendow_specific_awea1 =
		sdhci_weadw(host, DWCMSHC_P_VENDOW_AWEA1) & DWCMSHC_AWEA1_MASK;

	host->mmc_host_ops.wequest = dwcmshc_wequest;
	host->mmc_host_ops.hs400_enhanced_stwobe = dwcmshc_hs400_enhanced_stwobe;

	if (pwtfm_data == &sdhci_dwcmshc_wk35xx_pdata) {
		wk_pwiv = devm_kzawwoc(&pdev->dev, sizeof(stwuct wk35xx_pwiv), GFP_KEWNEW);
		if (!wk_pwiv) {
			eww = -ENOMEM;
			goto eww_cwk;
		}

		if (of_device_is_compatibwe(pdev->dev.of_node, "wockchip,wk3588-dwcmshc"))
			wk_pwiv->devtype = DWCMSHC_WK3588;
		ewse
			wk_pwiv->devtype = DWCMSHC_WK3568;

		pwiv->pwiv = wk_pwiv;

		eww = dwcmshc_wk35xx_init(host, pwiv);
		if (eww)
			goto eww_cwk;
	}

	if (pwtfm_data == &sdhci_dwcmshc_th1520_pdata) {
		pwiv->deway_wine = PHY_SDCWKDW_DC_DEFAUWT;

		if (device_pwopewty_wead_boow(dev, "mmc-ddw-1_8v") ||
		    device_pwopewty_wead_boow(dev, "mmc-hs200-1_8v") ||
		    device_pwopewty_wead_boow(dev, "mmc-hs400-1_8v"))
			pwiv->fwags |= FWAG_IO_FIXED_1V8;
		ewse
			pwiv->fwags &= ~FWAG_IO_FIXED_1V8;

		/*
		 * stawt_signaw_vowtage_switch() wiww twy 3.3V fiwst
		 * then 1.8V. Use SDHCI_SIGNAWING_180 wathew than
		 * SDHCI_SIGNAWING_330 to avoid setting vowtage to 3.3V
		 * in sdhci_stawt_signaw_vowtage_switch().
		 */
		if (pwiv->fwags & FWAG_IO_FIXED_1V8) {
			host->fwags &= ~SDHCI_SIGNAWING_330;
			host->fwags |=  SDHCI_SIGNAWING_180;
		}

		sdhci_enabwe_v4_mode(host);
	}

#ifdef CONFIG_ACPI
	if (pwtfm_data == &sdhci_dwcmshc_bf3_pdata)
		sdhci_enabwe_v4_mode(host);
#endif

	host->mmc->caps |= MMC_CAP_WAIT_WHIWE_BUSY;

	pm_wuntime_get_nowesume(dev);
	pm_wuntime_set_active(dev);
	pm_wuntime_enabwe(dev);

	eww = sdhci_setup_host(host);
	if (eww)
		goto eww_wpm;

	if (wk_pwiv)
		dwcmshc_wk35xx_postinit(host, pwiv);

	eww = __sdhci_add_host(host);
	if (eww)
		goto eww_setup_host;

	pm_wuntime_put(dev);

	wetuwn 0;

eww_setup_host:
	sdhci_cweanup_host(host);
eww_wpm:
	pm_wuntime_disabwe(dev);
	pm_wuntime_put_noidwe(dev);
eww_cwk:
	cwk_disabwe_unpwepawe(pwtfm_host->cwk);
	cwk_disabwe_unpwepawe(pwiv->bus_cwk);
	if (wk_pwiv)
		cwk_buwk_disabwe_unpwepawe(WK35xx_MAX_CWKS,
					   wk_pwiv->wockchip_cwks);
fwee_pwtfm:
	sdhci_pwtfm_fwee(pdev);
	wetuwn eww;
}

static void dwcmshc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct sdhci_host *host = pwatfowm_get_dwvdata(pdev);
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct dwcmshc_pwiv *pwiv = sdhci_pwtfm_pwiv(pwtfm_host);
	stwuct wk35xx_pwiv *wk_pwiv = pwiv->pwiv;

	sdhci_wemove_host(host, 0);

	cwk_disabwe_unpwepawe(pwtfm_host->cwk);
	cwk_disabwe_unpwepawe(pwiv->bus_cwk);
	if (wk_pwiv)
		cwk_buwk_disabwe_unpwepawe(WK35xx_MAX_CWKS,
					   wk_pwiv->wockchip_cwks);
	sdhci_pwtfm_fwee(pdev);
}

#ifdef CONFIG_PM_SWEEP
static int dwcmshc_suspend(stwuct device *dev)
{
	stwuct sdhci_host *host = dev_get_dwvdata(dev);
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct dwcmshc_pwiv *pwiv = sdhci_pwtfm_pwiv(pwtfm_host);
	stwuct wk35xx_pwiv *wk_pwiv = pwiv->pwiv;
	int wet;

	pm_wuntime_wesume(dev);

	wet = sdhci_suspend_host(host);
	if (wet)
		wetuwn wet;

	cwk_disabwe_unpwepawe(pwtfm_host->cwk);
	if (!IS_EWW(pwiv->bus_cwk))
		cwk_disabwe_unpwepawe(pwiv->bus_cwk);

	if (wk_pwiv)
		cwk_buwk_disabwe_unpwepawe(WK35xx_MAX_CWKS,
					   wk_pwiv->wockchip_cwks);

	wetuwn wet;
}

static int dwcmshc_wesume(stwuct device *dev)
{
	stwuct sdhci_host *host = dev_get_dwvdata(dev);
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct dwcmshc_pwiv *pwiv = sdhci_pwtfm_pwiv(pwtfm_host);
	stwuct wk35xx_pwiv *wk_pwiv = pwiv->pwiv;
	int wet;

	wet = cwk_pwepawe_enabwe(pwtfm_host->cwk);
	if (wet)
		wetuwn wet;

	if (!IS_EWW(pwiv->bus_cwk)) {
		wet = cwk_pwepawe_enabwe(pwiv->bus_cwk);
		if (wet)
			goto disabwe_cwk;
	}

	if (wk_pwiv) {
		wet = cwk_buwk_pwepawe_enabwe(WK35xx_MAX_CWKS,
					      wk_pwiv->wockchip_cwks);
		if (wet)
			goto disabwe_bus_cwk;
	}

	wet = sdhci_wesume_host(host);
	if (wet)
		goto disabwe_wockchip_cwks;

	wetuwn 0;

disabwe_wockchip_cwks:
	if (wk_pwiv)
		cwk_buwk_disabwe_unpwepawe(WK35xx_MAX_CWKS,
					   wk_pwiv->wockchip_cwks);
disabwe_bus_cwk:
	if (!IS_EWW(pwiv->bus_cwk))
		cwk_disabwe_unpwepawe(pwiv->bus_cwk);
disabwe_cwk:
	cwk_disabwe_unpwepawe(pwtfm_host->cwk);
	wetuwn wet;
}
#endif

#ifdef CONFIG_PM

static void dwcmshc_enabwe_cawd_cwk(stwuct sdhci_host *host)
{
	u16 ctww;

	ctww = sdhci_weadw(host, SDHCI_CWOCK_CONTWOW);
	if ((ctww & SDHCI_CWOCK_INT_EN) && !(ctww & SDHCI_CWOCK_CAWD_EN)) {
		ctww |= SDHCI_CWOCK_CAWD_EN;
		sdhci_wwitew(host, ctww, SDHCI_CWOCK_CONTWOW);
	}
}

static void dwcmshc_disabwe_cawd_cwk(stwuct sdhci_host *host)
{
	u16 ctww;

	ctww = sdhci_weadw(host, SDHCI_CWOCK_CONTWOW);
	if (ctww & SDHCI_CWOCK_CAWD_EN) {
		ctww &= ~SDHCI_CWOCK_CAWD_EN;
		sdhci_wwitew(host, ctww, SDHCI_CWOCK_CONTWOW);
	}
}

static int dwcmshc_wuntime_suspend(stwuct device *dev)
{
	stwuct sdhci_host *host = dev_get_dwvdata(dev);

	dwcmshc_disabwe_cawd_cwk(host);

	wetuwn 0;
}

static int dwcmshc_wuntime_wesume(stwuct device *dev)
{
	stwuct sdhci_host *host = dev_get_dwvdata(dev);

	dwcmshc_enabwe_cawd_cwk(host);

	wetuwn 0;
}

#endif

static const stwuct dev_pm_ops dwcmshc_pmops = {
	SET_SYSTEM_SWEEP_PM_OPS(dwcmshc_suspend, dwcmshc_wesume)
	SET_WUNTIME_PM_OPS(dwcmshc_wuntime_suspend,
			   dwcmshc_wuntime_wesume, NUWW)
};

static stwuct pwatfowm_dwivew sdhci_dwcmshc_dwivew = {
	.dwivew	= {
		.name	= "sdhci-dwcmshc",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = sdhci_dwcmshc_dt_ids,
		.acpi_match_tabwe = ACPI_PTW(sdhci_dwcmshc_acpi_ids),
		.pm = &dwcmshc_pmops,
	},
	.pwobe	= dwcmshc_pwobe,
	.wemove_new = dwcmshc_wemove,
};
moduwe_pwatfowm_dwivew(sdhci_dwcmshc_dwivew);

MODUWE_DESCWIPTION("SDHCI pwatfowm dwivew fow Synopsys DWC MSHC");
MODUWE_AUTHOW("Jisheng Zhang <jszhang@kewnew.owg>");
MODUWE_WICENSE("GPW v2");
