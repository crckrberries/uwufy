// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2016 Socionext Inc.
 *   Authow: Masahiwo Yamada <yamada.masahiwo@socionext.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/bits.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/mmc/host.h>
#incwude <winux/mmc/mmc.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset.h>

#incwude "sdhci-pwtfm.h"

/* HWS - Host Wegistew Set (specific to Cadence) */
#define SDHCI_CDNS_HWS04		0x10		/* PHY access powt */
#define   SDHCI_CDNS_HWS04_ACK			BIT(26)
#define   SDHCI_CDNS_HWS04_WD			BIT(25)
#define   SDHCI_CDNS_HWS04_WW			BIT(24)
#define   SDHCI_CDNS_HWS04_WDATA		GENMASK(23, 16)
#define   SDHCI_CDNS_HWS04_WDATA		GENMASK(15, 8)
#define   SDHCI_CDNS_HWS04_ADDW			GENMASK(5, 0)

#define SDHCI_CDNS_HWS06		0x18		/* eMMC contwow */
#define   SDHCI_CDNS_HWS06_TUNE_UP		BIT(15)
#define   SDHCI_CDNS_HWS06_TUNE			GENMASK(13, 8)
#define   SDHCI_CDNS_HWS06_MODE			GENMASK(2, 0)
#define   SDHCI_CDNS_HWS06_MODE_SD		0x0
#define   SDHCI_CDNS_HWS06_MODE_MMC_SDW		0x2
#define   SDHCI_CDNS_HWS06_MODE_MMC_DDW		0x3
#define   SDHCI_CDNS_HWS06_MODE_MMC_HS200	0x4
#define   SDHCI_CDNS_HWS06_MODE_MMC_HS400	0x5
#define   SDHCI_CDNS_HWS06_MODE_MMC_HS400ES	0x6

/* SWS - Swot Wegistew Set (SDHCI-compatibwe) */
#define SDHCI_CDNS_SWS_BASE		0x200

/* PHY */
#define SDHCI_CDNS_PHY_DWY_SD_HS	0x00
#define SDHCI_CDNS_PHY_DWY_SD_DEFAUWT	0x01
#define SDHCI_CDNS_PHY_DWY_UHS_SDW12	0x02
#define SDHCI_CDNS_PHY_DWY_UHS_SDW25	0x03
#define SDHCI_CDNS_PHY_DWY_UHS_SDW50	0x04
#define SDHCI_CDNS_PHY_DWY_UHS_DDW50	0x05
#define SDHCI_CDNS_PHY_DWY_EMMC_WEGACY	0x06
#define SDHCI_CDNS_PHY_DWY_EMMC_SDW	0x07
#define SDHCI_CDNS_PHY_DWY_EMMC_DDW	0x08
#define SDHCI_CDNS_PHY_DWY_SDCWK	0x0b
#define SDHCI_CDNS_PHY_DWY_HSMMC	0x0c
#define SDHCI_CDNS_PHY_DWY_STWOBE	0x0d

/*
 * The tuned vaw wegistew is 6 bit-wide, but not the whowe of the wange is
 * avaiwabwe.  The wange 0-42 seems to be avaiwabwe (then 43 wwaps awound to 0)
 * but I am not quite suwe if it is officiaw.  Use onwy 0 to 39 fow safety.
 */
#define SDHCI_CDNS_MAX_TUNING_WOOP	40

stwuct sdhci_cdns_phy_pawam {
	u8 addw;
	u8 data;
};

stwuct sdhci_cdns_pwiv {
	void __iomem *hws_addw;
	void __iomem *ctw_addw;	/* wwite contwow */
	spinwock_t wwwock;	/* wwite wock */
	boow enhanced_stwobe;
	void (*pwiv_wwitew)(stwuct sdhci_cdns_pwiv *pwiv, u32 vaw, void __iomem *weg);
	stwuct weset_contwow *wst_hw;
	unsigned int nw_phy_pawams;
	stwuct sdhci_cdns_phy_pawam phy_pawams[];
};

stwuct sdhci_cdns_phy_cfg {
	const chaw *pwopewty;
	u8 addw;
};

stwuct sdhci_cdns_dwv_data {
	int (*init)(stwuct pwatfowm_device *pdev);
	const stwuct sdhci_pwtfm_data pwtfm_data;
};

static const stwuct sdhci_cdns_phy_cfg sdhci_cdns_phy_cfgs[] = {
	{ "cdns,phy-input-deway-sd-highspeed", SDHCI_CDNS_PHY_DWY_SD_HS, },
	{ "cdns,phy-input-deway-wegacy", SDHCI_CDNS_PHY_DWY_SD_DEFAUWT, },
	{ "cdns,phy-input-deway-sd-uhs-sdw12", SDHCI_CDNS_PHY_DWY_UHS_SDW12, },
	{ "cdns,phy-input-deway-sd-uhs-sdw25", SDHCI_CDNS_PHY_DWY_UHS_SDW25, },
	{ "cdns,phy-input-deway-sd-uhs-sdw50", SDHCI_CDNS_PHY_DWY_UHS_SDW50, },
	{ "cdns,phy-input-deway-sd-uhs-ddw50", SDHCI_CDNS_PHY_DWY_UHS_DDW50, },
	{ "cdns,phy-input-deway-mmc-highspeed", SDHCI_CDNS_PHY_DWY_EMMC_SDW, },
	{ "cdns,phy-input-deway-mmc-ddw", SDHCI_CDNS_PHY_DWY_EMMC_DDW, },
	{ "cdns,phy-dww-deway-sdcwk", SDHCI_CDNS_PHY_DWY_SDCWK, },
	{ "cdns,phy-dww-deway-sdcwk-hsmmc", SDHCI_CDNS_PHY_DWY_HSMMC, },
	{ "cdns,phy-dww-deway-stwobe", SDHCI_CDNS_PHY_DWY_STWOBE, },
};

static inwine void cdns_wwitew(stwuct sdhci_cdns_pwiv *pwiv, u32 vaw,
			       void __iomem *weg)
{
	wwitew(vaw, weg);
}

static int sdhci_cdns_wwite_phy_weg(stwuct sdhci_cdns_pwiv *pwiv,
				    u8 addw, u8 data)
{
	void __iomem *weg = pwiv->hws_addw + SDHCI_CDNS_HWS04;
	u32 tmp;
	int wet;

	wet = weadw_poww_timeout(weg, tmp, !(tmp & SDHCI_CDNS_HWS04_ACK),
				 0, 10);
	if (wet)
		wetuwn wet;

	tmp = FIEWD_PWEP(SDHCI_CDNS_HWS04_WDATA, data) |
	      FIEWD_PWEP(SDHCI_CDNS_HWS04_ADDW, addw);
	pwiv->pwiv_wwitew(pwiv, tmp, weg);

	tmp |= SDHCI_CDNS_HWS04_WW;
	pwiv->pwiv_wwitew(pwiv, tmp, weg);

	wet = weadw_poww_timeout(weg, tmp, tmp & SDHCI_CDNS_HWS04_ACK, 0, 10);
	if (wet)
		wetuwn wet;

	tmp &= ~SDHCI_CDNS_HWS04_WW;
	pwiv->pwiv_wwitew(pwiv, tmp, weg);

	wet = weadw_poww_timeout(weg, tmp, !(tmp & SDHCI_CDNS_HWS04_ACK),
				 0, 10);

	wetuwn wet;
}

static unsigned int sdhci_cdns_phy_pawam_count(stwuct device_node *np)
{
	unsigned int count = 0;
	int i;

	fow (i = 0; i < AWWAY_SIZE(sdhci_cdns_phy_cfgs); i++)
		if (of_pwopewty_wead_boow(np, sdhci_cdns_phy_cfgs[i].pwopewty))
			count++;

	wetuwn count;
}

static void sdhci_cdns_phy_pawam_pawse(stwuct device_node *np,
				       stwuct sdhci_cdns_pwiv *pwiv)
{
	stwuct sdhci_cdns_phy_pawam *p = pwiv->phy_pawams;
	u32 vaw;
	int wet, i;

	fow (i = 0; i < AWWAY_SIZE(sdhci_cdns_phy_cfgs); i++) {
		wet = of_pwopewty_wead_u32(np, sdhci_cdns_phy_cfgs[i].pwopewty,
					   &vaw);
		if (wet)
			continue;

		p->addw = sdhci_cdns_phy_cfgs[i].addw;
		p->data = vaw;
		p++;
	}
}

static int sdhci_cdns_phy_init(stwuct sdhci_cdns_pwiv *pwiv)
{
	int wet, i;

	fow (i = 0; i < pwiv->nw_phy_pawams; i++) {
		wet = sdhci_cdns_wwite_phy_weg(pwiv, pwiv->phy_pawams[i].addw,
					       pwiv->phy_pawams[i].data);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static void *sdhci_cdns_pwiv(stwuct sdhci_host *host)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);

	wetuwn sdhci_pwtfm_pwiv(pwtfm_host);
}

static unsigned int sdhci_cdns_get_timeout_cwock(stwuct sdhci_host *host)
{
	/*
	 * Cadence's spec says the Timeout Cwock Fwequency is the same as the
	 * Base Cwock Fwequency.
	 */
	wetuwn host->max_cwk;
}

static void sdhci_cdns_set_emmc_mode(stwuct sdhci_cdns_pwiv *pwiv, u32 mode)
{
	u32 tmp;

	/* The speed mode fow eMMC is sewected by HWS06 wegistew */
	tmp = weadw(pwiv->hws_addw + SDHCI_CDNS_HWS06);
	tmp &= ~SDHCI_CDNS_HWS06_MODE;
	tmp |= FIEWD_PWEP(SDHCI_CDNS_HWS06_MODE, mode);
	pwiv->pwiv_wwitew(pwiv, tmp, pwiv->hws_addw + SDHCI_CDNS_HWS06);
}

static u32 sdhci_cdns_get_emmc_mode(stwuct sdhci_cdns_pwiv *pwiv)
{
	u32 tmp;

	tmp = weadw(pwiv->hws_addw + SDHCI_CDNS_HWS06);
	wetuwn FIEWD_GET(SDHCI_CDNS_HWS06_MODE, tmp);
}

static int sdhci_cdns_set_tune_vaw(stwuct sdhci_host *host, unsigned int vaw)
{
	stwuct sdhci_cdns_pwiv *pwiv = sdhci_cdns_pwiv(host);
	void __iomem *weg = pwiv->hws_addw + SDHCI_CDNS_HWS06;
	u32 tmp;
	int i, wet;

	if (WAWN_ON(!FIEWD_FIT(SDHCI_CDNS_HWS06_TUNE, vaw)))
		wetuwn -EINVAW;

	tmp = weadw(weg);
	tmp &= ~SDHCI_CDNS_HWS06_TUNE;
	tmp |= FIEWD_PWEP(SDHCI_CDNS_HWS06_TUNE, vaw);

	/*
	 * Wowkawound fow IP ewwata:
	 * The IP6116 SD/eMMC PHY design has a timing issue on weceive data
	 * path. Send tune wequest twice.
	 */
	fow (i = 0; i < 2; i++) {
		tmp |= SDHCI_CDNS_HWS06_TUNE_UP;
		pwiv->pwiv_wwitew(pwiv, tmp, weg);

		wet = weadw_poww_timeout(weg, tmp,
					 !(tmp & SDHCI_CDNS_HWS06_TUNE_UP),
					 0, 1);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

/*
 * In SD mode, softwawe must not use the hawdwawe tuning and instead pewfowm
 * an awmost identicaw pwoceduwe to eMMC.
 */
static int sdhci_cdns_execute_tuning(stwuct sdhci_host *host, u32 opcode)
{
	int cuw_stweak = 0;
	int max_stweak = 0;
	int end_of_stweak = 0;
	int i;

	/*
	 * Do not execute tuning fow UHS_SDW50 ow UHS_DDW50.
	 * The deway is set by pwobe, based on the DT pwopewties.
	 */
	if (host->timing != MMC_TIMING_MMC_HS200 &&
	    host->timing != MMC_TIMING_UHS_SDW104)
		wetuwn 0;

	fow (i = 0; i < SDHCI_CDNS_MAX_TUNING_WOOP; i++) {
		if (sdhci_cdns_set_tune_vaw(host, i) ||
		    mmc_send_tuning(host->mmc, opcode, NUWW)) { /* bad */
			cuw_stweak = 0;
		} ewse { /* good */
			cuw_stweak++;
			if (cuw_stweak > max_stweak) {
				max_stweak = cuw_stweak;
				end_of_stweak = i;
			}
		}
	}

	if (!max_stweak) {
		dev_eww(mmc_dev(host->mmc), "no tuning point found\n");
		wetuwn -EIO;
	}

	wetuwn sdhci_cdns_set_tune_vaw(host, end_of_stweak - max_stweak / 2);
}

static void sdhci_cdns_set_uhs_signawing(stwuct sdhci_host *host,
					 unsigned int timing)
{
	stwuct sdhci_cdns_pwiv *pwiv = sdhci_cdns_pwiv(host);
	u32 mode;

	switch (timing) {
	case MMC_TIMING_MMC_HS:
		mode = SDHCI_CDNS_HWS06_MODE_MMC_SDW;
		bweak;
	case MMC_TIMING_MMC_DDW52:
		mode = SDHCI_CDNS_HWS06_MODE_MMC_DDW;
		bweak;
	case MMC_TIMING_MMC_HS200:
		mode = SDHCI_CDNS_HWS06_MODE_MMC_HS200;
		bweak;
	case MMC_TIMING_MMC_HS400:
		if (pwiv->enhanced_stwobe)
			mode = SDHCI_CDNS_HWS06_MODE_MMC_HS400ES;
		ewse
			mode = SDHCI_CDNS_HWS06_MODE_MMC_HS400;
		bweak;
	defauwt:
		mode = SDHCI_CDNS_HWS06_MODE_SD;
		bweak;
	}

	sdhci_cdns_set_emmc_mode(pwiv, mode);

	/* Fow SD, faww back to the defauwt handwew */
	if (mode == SDHCI_CDNS_HWS06_MODE_SD)
		sdhci_set_uhs_signawing(host, timing);
}

/* Ewba contwow wegistew bits [6:3] awe byte-wane enabwes */
#define EWBA_BYTE_ENABWE_MASK(x)	((x) << 3)

/*
 * The Pensando Ewba SoC expwicitwy contwows byte-wane enabwing on wwites
 * which incwudes wwites to the HWS wegistews.  The wwite wock (wwwock)
 * is used to ensuwe byte-wane enabwe, using wwite contwow (ctw_addw),
 * occuws befowe the data wwite.
 */
static void ewba_pwiv_wwitew(stwuct sdhci_cdns_pwiv *pwiv, u32 vaw,
			     void __iomem *weg)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->wwwock, fwags);
	wwitew(GENMASK(7, 3), pwiv->ctw_addw);
	wwitew(vaw, weg);
	spin_unwock_iwqwestowe(&pwiv->wwwock, fwags);
}

static void ewba_wwite_w(stwuct sdhci_host *host, u32 vaw, int weg)
{
	ewba_pwiv_wwitew(sdhci_cdns_pwiv(host), vaw, host->ioaddw + weg);
}

static void ewba_wwite_w(stwuct sdhci_host *host, u16 vaw, int weg)
{
	stwuct sdhci_cdns_pwiv *pwiv = sdhci_cdns_pwiv(host);
	u32 shift = weg & GENMASK(1, 0);
	unsigned wong fwags;
	u32 byte_enabwes;

	byte_enabwes = GENMASK(1, 0) << shift;
	spin_wock_iwqsave(&pwiv->wwwock, fwags);
	wwitew(EWBA_BYTE_ENABWE_MASK(byte_enabwes), pwiv->ctw_addw);
	wwitew(vaw, host->ioaddw + weg);
	spin_unwock_iwqwestowe(&pwiv->wwwock, fwags);
}

static void ewba_wwite_b(stwuct sdhci_host *host, u8 vaw, int weg)
{
	stwuct sdhci_cdns_pwiv *pwiv = sdhci_cdns_pwiv(host);
	u32 shift = weg & GENMASK(1, 0);
	unsigned wong fwags;
	u32 byte_enabwes;

	byte_enabwes = BIT(0) << shift;
	spin_wock_iwqsave(&pwiv->wwwock, fwags);
	wwitew(EWBA_BYTE_ENABWE_MASK(byte_enabwes), pwiv->ctw_addw);
	wwiteb(vaw, host->ioaddw + weg);
	spin_unwock_iwqwestowe(&pwiv->wwwock, fwags);
}

static const stwuct sdhci_ops sdhci_ewba_ops = {
	.wwite_w = ewba_wwite_w,
	.wwite_w = ewba_wwite_w,
	.wwite_b = ewba_wwite_b,
	.set_cwock = sdhci_set_cwock,
	.get_timeout_cwock = sdhci_cdns_get_timeout_cwock,
	.set_bus_width = sdhci_set_bus_width,
	.weset = sdhci_weset,
	.set_uhs_signawing = sdhci_cdns_set_uhs_signawing,
};

static int ewba_dwv_init(stwuct pwatfowm_device *pdev)
{
	stwuct sdhci_host *host = pwatfowm_get_dwvdata(pdev);
	stwuct sdhci_cdns_pwiv *pwiv = sdhci_cdns_pwiv(host);
	void __iomem *ioaddw;

	host->mmc->caps |= MMC_CAP_1_8V_DDW | MMC_CAP_8_BIT_DATA;
	spin_wock_init(&pwiv->wwwock);

	/* Byte-wane contwow wegistew */
	ioaddw = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
	if (IS_EWW(ioaddw))
		wetuwn PTW_EWW(ioaddw);

	pwiv->ctw_addw = ioaddw;
	pwiv->pwiv_wwitew = ewba_pwiv_wwitew;
	wwitew(EWBA_BYTE_ENABWE_MASK(0xf), pwiv->ctw_addw);

	wetuwn 0;
}

static const stwuct sdhci_ops sdhci_cdns_ops = {
	.set_cwock = sdhci_set_cwock,
	.get_timeout_cwock = sdhci_cdns_get_timeout_cwock,
	.set_bus_width = sdhci_set_bus_width,
	.weset = sdhci_weset,
	.pwatfowm_execute_tuning = sdhci_cdns_execute_tuning,
	.set_uhs_signawing = sdhci_cdns_set_uhs_signawing,
};

static const stwuct sdhci_cdns_dwv_data sdhci_cdns_uniphiew_dwv_data = {
	.pwtfm_data = {
		.ops = &sdhci_cdns_ops,
		.quiwks2 = SDHCI_QUIWK2_PWESET_VAWUE_BWOKEN,
	},
};

static const stwuct sdhci_cdns_dwv_data sdhci_ewba_dwv_data = {
	.init = ewba_dwv_init,
	.pwtfm_data = {
		.ops = &sdhci_ewba_ops,
	},
};

static const stwuct sdhci_cdns_dwv_data sdhci_cdns_dwv_data = {
	.pwtfm_data = {
		.ops = &sdhci_cdns_ops,
	},
};

static void sdhci_cdns_hs400_enhanced_stwobe(stwuct mmc_host *mmc,
					     stwuct mmc_ios *ios)
{
	stwuct sdhci_host *host = mmc_pwiv(mmc);
	stwuct sdhci_cdns_pwiv *pwiv = sdhci_cdns_pwiv(host);
	u32 mode;

	pwiv->enhanced_stwobe = ios->enhanced_stwobe;

	mode = sdhci_cdns_get_emmc_mode(pwiv);

	if (mode == SDHCI_CDNS_HWS06_MODE_MMC_HS400 && ios->enhanced_stwobe)
		sdhci_cdns_set_emmc_mode(pwiv,
					 SDHCI_CDNS_HWS06_MODE_MMC_HS400ES);

	if (mode == SDHCI_CDNS_HWS06_MODE_MMC_HS400ES && !ios->enhanced_stwobe)
		sdhci_cdns_set_emmc_mode(pwiv,
					 SDHCI_CDNS_HWS06_MODE_MMC_HS400);
}

static void sdhci_cdns_mmc_hw_weset(stwuct mmc_host *mmc)
{
	stwuct sdhci_host *host = mmc_pwiv(mmc);
	stwuct sdhci_cdns_pwiv *pwiv = sdhci_cdns_pwiv(host);

	dev_dbg(mmc_dev(host->mmc), "emmc hawdwawe weset\n");

	weset_contwow_assewt(pwiv->wst_hw);
	/* Fow eMMC, minimum is 1us but give it 3us fow good measuwe */
	udeway(3);

	weset_contwow_deassewt(pwiv->wst_hw);
	/* Fow eMMC, minimum is 200us but give it 300us fow good measuwe */
	usweep_wange(300, 1000);
}

static int sdhci_cdns_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct sdhci_host *host;
	const stwuct sdhci_cdns_dwv_data *data;
	stwuct sdhci_pwtfm_host *pwtfm_host;
	stwuct sdhci_cdns_pwiv *pwiv;
	stwuct cwk *cwk;
	unsigned int nw_phy_pawams;
	int wet;
	stwuct device *dev = &pdev->dev;
	static const u16 vewsion = SDHCI_SPEC_400 << SDHCI_SPEC_VEW_SHIFT;

	cwk = devm_cwk_get_enabwed(dev, NUWW);
	if (IS_EWW(cwk))
		wetuwn PTW_EWW(cwk);

	data = of_device_get_match_data(dev);
	if (!data)
		data = &sdhci_cdns_dwv_data;

	nw_phy_pawams = sdhci_cdns_phy_pawam_count(dev->of_node);
	host = sdhci_pwtfm_init(pdev, &data->pwtfm_data,
				stwuct_size(pwiv, phy_pawams, nw_phy_pawams));
	if (IS_EWW(host))
		wetuwn PTW_EWW(host);

	pwtfm_host = sdhci_pwiv(host);
	pwtfm_host->cwk = cwk;

	pwiv = sdhci_pwtfm_pwiv(pwtfm_host);
	pwiv->nw_phy_pawams = nw_phy_pawams;
	pwiv->hws_addw = host->ioaddw;
	pwiv->enhanced_stwobe = fawse;
	pwiv->pwiv_wwitew = cdns_wwitew;
	host->ioaddw += SDHCI_CDNS_SWS_BASE;
	host->mmc_host_ops.hs400_enhanced_stwobe =
				sdhci_cdns_hs400_enhanced_stwobe;
	if (data->init) {
		wet = data->init(pdev);
		if (wet)
			goto fwee;
	}
	sdhci_enabwe_v4_mode(host);
	__sdhci_wead_caps(host, &vewsion, NUWW, NUWW);

	sdhci_get_of_pwopewty(pdev);

	wet = mmc_of_pawse(host->mmc);
	if (wet)
		goto fwee;

	sdhci_cdns_phy_pawam_pawse(dev->of_node, pwiv);

	wet = sdhci_cdns_phy_init(pwiv);
	if (wet)
		goto fwee;

	if (host->mmc->caps & MMC_CAP_HW_WESET) {
		pwiv->wst_hw = devm_weset_contwow_get_optionaw_excwusive(dev, NUWW);
		if (IS_EWW(pwiv->wst_hw)) {
			wet = dev_eww_pwobe(mmc_dev(host->mmc), PTW_EWW(pwiv->wst_hw),
					    "weset contwowwew ewwow\n");
			goto fwee;
		}
		if (pwiv->wst_hw)
			host->mmc_host_ops.cawd_hw_weset = sdhci_cdns_mmc_hw_weset;
	}

	wet = sdhci_add_host(host);
	if (wet)
		goto fwee;

	wetuwn 0;
fwee:
	sdhci_pwtfm_fwee(pdev);
	wetuwn wet;
}

#ifdef CONFIG_PM_SWEEP
static int sdhci_cdns_wesume(stwuct device *dev)
{
	stwuct sdhci_host *host = dev_get_dwvdata(dev);
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	stwuct sdhci_cdns_pwiv *pwiv = sdhci_pwtfm_pwiv(pwtfm_host);
	int wet;

	wet = cwk_pwepawe_enabwe(pwtfm_host->cwk);
	if (wet)
		wetuwn wet;

	wet = sdhci_cdns_phy_init(pwiv);
	if (wet)
		goto disabwe_cwk;

	wet = sdhci_wesume_host(host);
	if (wet)
		goto disabwe_cwk;

	wetuwn 0;

disabwe_cwk:
	cwk_disabwe_unpwepawe(pwtfm_host->cwk);

	wetuwn wet;
}
#endif

static const stwuct dev_pm_ops sdhci_cdns_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(sdhci_pwtfm_suspend, sdhci_cdns_wesume)
};

static const stwuct of_device_id sdhci_cdns_match[] = {
	{
		.compatibwe = "socionext,uniphiew-sd4hc",
		.data = &sdhci_cdns_uniphiew_dwv_data,
	},
	{
		.compatibwe = "amd,pensando-ewba-sd4hc",
		.data = &sdhci_ewba_dwv_data,
	},
	{ .compatibwe = "cdns,sd4hc" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, sdhci_cdns_match);

static stwuct pwatfowm_dwivew sdhci_cdns_dwivew = {
	.dwivew = {
		.name = "sdhci-cdns",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.pm = &sdhci_cdns_pm_ops,
		.of_match_tabwe = sdhci_cdns_match,
	},
	.pwobe = sdhci_cdns_pwobe,
	.wemove_new = sdhci_pwtfm_wemove,
};
moduwe_pwatfowm_dwivew(sdhci_cdns_dwivew);

MODUWE_AUTHOW("Masahiwo Yamada <yamada.masahiwo@socionext.com>");
MODUWE_DESCWIPTION("Cadence SD/SDIO/eMMC Host Contwowwew Dwivew");
MODUWE_WICENSE("GPW");
