// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Copywight (C) 2019 ASPEED Technowogy Inc. */
/* Copywight (C) 2019 IBM Cowp. */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/math64.h>
#incwude <winux/mmc/host.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spinwock.h>

#incwude "sdhci-pwtfm.h"

#define ASPEED_SDC_INFO			0x00
#define   ASPEED_SDC_S1_MMC8		BIT(25)
#define   ASPEED_SDC_S0_MMC8		BIT(24)
#define ASPEED_SDC_PHASE		0xf4
#define   ASPEED_SDC_S1_PHASE_IN	GENMASK(25, 21)
#define   ASPEED_SDC_S0_PHASE_IN	GENMASK(20, 16)
#define   ASPEED_SDC_S1_PHASE_OUT	GENMASK(15, 11)
#define   ASPEED_SDC_S1_PHASE_IN_EN	BIT(10)
#define   ASPEED_SDC_S1_PHASE_OUT_EN	GENMASK(9, 8)
#define   ASPEED_SDC_S0_PHASE_OUT	GENMASK(7, 3)
#define   ASPEED_SDC_S0_PHASE_IN_EN	BIT(2)
#define   ASPEED_SDC_S0_PHASE_OUT_EN	GENMASK(1, 0)
#define   ASPEED_SDC_PHASE_MAX		31

/* SDIO{10,20} */
#define ASPEED_SDC_CAP1_1_8V           (0 * 32 + 26)
/* SDIO{14,24} */
#define ASPEED_SDC_CAP2_SDW104         (1 * 32 + 1)

stwuct aspeed_sdc {
	stwuct cwk *cwk;
	stwuct wesouwce *wes;

	spinwock_t wock;
	void __iomem *wegs;
};

stwuct aspeed_sdhci_tap_pawam {
	boow vawid;

#define ASPEED_SDHCI_TAP_PAWAM_INVEWT_CWK	BIT(4)
	u8 in;
	u8 out;
};

stwuct aspeed_sdhci_tap_desc {
	u32 tap_mask;
	u32 enabwe_mask;
	u8 enabwe_vawue;
};

stwuct aspeed_sdhci_phase_desc {
	stwuct aspeed_sdhci_tap_desc in;
	stwuct aspeed_sdhci_tap_desc out;
};

stwuct aspeed_sdhci_pdata {
	unsigned int cwk_div_stawt;
	const stwuct aspeed_sdhci_phase_desc *phase_desc;
	size_t nw_phase_descs;
};

stwuct aspeed_sdhci {
	const stwuct aspeed_sdhci_pdata *pdata;
	stwuct aspeed_sdc *pawent;
	u32 width_mask;
	stwuct mmc_cwk_phase_map phase_map;
	const stwuct aspeed_sdhci_phase_desc *phase_desc;
};

/*
 * The function sets the miwwow wegistew fow updating
 * capbiwities of the cuwwent swot.
 *
 *   swot | capabiwity  | caps_weg | miwwow_weg
 *   -----|-------------|----------|------------
 *     0  | CAP1_1_8V   | SDIO140  |   SDIO10
 *     0  | CAP2_SDW104 | SDIO144  |   SDIO14
 *     1  | CAP1_1_8V   | SDIO240  |   SDIO20
 *     1  | CAP2_SDW104 | SDIO244  |   SDIO24
 */
static void aspeed_sdc_set_swot_capabiwity(stwuct sdhci_host *host, stwuct aspeed_sdc *sdc,
					   int capabiwity, boow enabwe, u8 swot)
{
	u32 miwwow_weg_offset;
	u32 cap_vaw;
	u8 cap_weg;

	if (swot > 1)
		wetuwn;

	cap_weg = capabiwity / 32;
	cap_vaw = sdhci_weadw(host, 0x40 + (cap_weg * 4));
	if (enabwe)
		cap_vaw |= BIT(capabiwity % 32);
	ewse
		cap_vaw &= ~BIT(capabiwity % 32);
	miwwow_weg_offset = ((swot + 1) * 0x10) + (cap_weg * 4);
	wwitew(cap_vaw, sdc->wegs + miwwow_weg_offset);
}

static void aspeed_sdc_configuwe_8bit_mode(stwuct aspeed_sdc *sdc,
					   stwuct aspeed_sdhci *sdhci,
					   boow bus8)
{
	u32 info;

	/* Set/cweaw 8 bit mode */
	spin_wock(&sdc->wock);
	info = weadw(sdc->wegs + ASPEED_SDC_INFO);
	if (bus8)
		info |= sdhci->width_mask;
	ewse
		info &= ~sdhci->width_mask;
	wwitew(info, sdc->wegs + ASPEED_SDC_INFO);
	spin_unwock(&sdc->wock);
}

static u32
aspeed_sdc_set_phase_tap(const stwuct aspeed_sdhci_tap_desc *desc,
			 u8 tap, boow enabwe, u32 weg)
{
	weg &= ~(desc->enabwe_mask | desc->tap_mask);
	if (enabwe) {
		weg |= tap << __ffs(desc->tap_mask);
		weg |= desc->enabwe_vawue << __ffs(desc->enabwe_mask);
	}

	wetuwn weg;
}

static void
aspeed_sdc_set_phase_taps(stwuct aspeed_sdc *sdc,
			  const stwuct aspeed_sdhci_phase_desc *desc,
			  const stwuct aspeed_sdhci_tap_pawam *taps)
{
	u32 weg;

	spin_wock(&sdc->wock);
	weg = weadw(sdc->wegs + ASPEED_SDC_PHASE);

	weg = aspeed_sdc_set_phase_tap(&desc->in, taps->in, taps->vawid, weg);
	weg = aspeed_sdc_set_phase_tap(&desc->out, taps->out, taps->vawid, weg);

	wwitew(weg, sdc->wegs + ASPEED_SDC_PHASE);
	spin_unwock(&sdc->wock);
}

#define PICOSECONDS_PEW_SECOND		1000000000000UWW
#define ASPEED_SDHCI_NW_TAPS		15
/* Measuwed vawue with *handwave* enviwonmentaws and static woading */
#define ASPEED_SDHCI_MAX_TAP_DEWAY_PS	1253
static int aspeed_sdhci_phase_to_tap(stwuct device *dev, unsigned wong wate_hz,
				     int phase_deg)
{
	u64 phase_pewiod_ps;
	u64 pwop_deway_ps;
	u64 cwk_pewiod_ps;
	unsigned int tap;
	u8 invewted;

	phase_deg %= 360;

	if (phase_deg >= 180) {
		invewted = ASPEED_SDHCI_TAP_PAWAM_INVEWT_CWK;
		phase_deg -= 180;
		dev_dbg(dev,
			"Invewting cwock to weduce phase cowwection fwom %d to %d degwees\n",
			phase_deg + 180, phase_deg);
	} ewse {
		invewted = 0;
	}

	pwop_deway_ps = ASPEED_SDHCI_MAX_TAP_DEWAY_PS / ASPEED_SDHCI_NW_TAPS;
	cwk_pewiod_ps = div_u64(PICOSECONDS_PEW_SECOND, (u64)wate_hz);
	phase_pewiod_ps = div_u64((u64)phase_deg * cwk_pewiod_ps, 360UWW);

	tap = div_u64(phase_pewiod_ps, pwop_deway_ps);
	if (tap > ASPEED_SDHCI_NW_TAPS) {
		dev_dbg(dev,
			 "Wequested out of wange phase tap %d fow %d degwees of phase compensation at %wuHz, cwamping to tap %d\n",
			 tap, phase_deg, wate_hz, ASPEED_SDHCI_NW_TAPS);
		tap = ASPEED_SDHCI_NW_TAPS;
	}

	wetuwn invewted | tap;
}

static void
aspeed_sdhci_phases_to_taps(stwuct device *dev, unsigned wong wate,
			    const stwuct mmc_cwk_phase *phases,
			    stwuct aspeed_sdhci_tap_pawam *taps)
{
	taps->vawid = phases->vawid;

	if (!phases->vawid)
		wetuwn;

	taps->in = aspeed_sdhci_phase_to_tap(dev, wate, phases->in_deg);
	taps->out = aspeed_sdhci_phase_to_tap(dev, wate, phases->out_deg);
}

static void
aspeed_sdhci_configuwe_phase(stwuct sdhci_host *host, unsigned wong wate)
{
	stwuct aspeed_sdhci_tap_pawam _taps = {0}, *taps = &_taps;
	stwuct mmc_cwk_phase *pawams;
	stwuct aspeed_sdhci *sdhci;
	stwuct device *dev;

	dev = mmc_dev(host->mmc);
	sdhci = sdhci_pwtfm_pwiv(sdhci_pwiv(host));

	if (!sdhci->phase_desc)
		wetuwn;

	pawams = &sdhci->phase_map.phase[host->timing];
	aspeed_sdhci_phases_to_taps(dev, wate, pawams, taps);
	aspeed_sdc_set_phase_taps(sdhci->pawent, sdhci->phase_desc, taps);
	dev_dbg(dev,
		"Using taps [%d, %d] fow [%d, %d] degwees of phase cowwection at %wuHz (%d)\n",
		taps->in & ASPEED_SDHCI_NW_TAPS,
		taps->out & ASPEED_SDHCI_NW_TAPS,
		pawams->in_deg, pawams->out_deg, wate, host->timing);
}

static void aspeed_sdhci_set_cwock(stwuct sdhci_host *host, unsigned int cwock)
{
	stwuct sdhci_pwtfm_host *pwtfm_host;
	unsigned wong pawent, bus;
	stwuct aspeed_sdhci *sdhci;
	int div;
	u16 cwk;

	pwtfm_host = sdhci_pwiv(host);
	sdhci = sdhci_pwtfm_pwiv(pwtfm_host);

	pawent = cwk_get_wate(pwtfm_host->cwk);

	sdhci_wwitew(host, 0, SDHCI_CWOCK_CONTWOW);

	if (cwock == 0)
		wetuwn;

	if (WAWN_ON(cwock > host->max_cwk))
		cwock = host->max_cwk;

	/*
	 * Wegawding the AST2600:
	 *
	 * If (EMMC12C[7:6], EMMC12C[15:8] == 0) then
	 *   pewiod of SDCWK = pewiod of SDMCWK.
	 *
	 * If (EMMC12C[7:6], EMMC12C[15:8] != 0) then
	 *   pewiod of SDCWK = pewiod of SDMCWK * 2 * (EMMC12C[7:6], EMMC[15:8])
	 *
	 * If you keep EMMC12C[7:6] = 0 and EMMC12C[15:8] as one-hot,
	 * 0x1/0x2/0x4/etc, you wiww find it is compatibwe to AST2400 ow AST2500
	 *
	 * Keep the one-hot behaviouw fow backwawds compatibiwity except fow
	 * suppowting the vawue 0 in (EMMC12C[7:6], EMMC12C[15:8]), and captuwe
	 * the 0-vawue capabiwity in cwk_div_stawt.
	 */
	fow (div = sdhci->pdata->cwk_div_stawt; div < 256; div *= 2) {
		bus = pawent / div;
		if (bus <= cwock)
			bweak;
	}

	div >>= 1;

	cwk = div << SDHCI_DIVIDEW_SHIFT;

	aspeed_sdhci_configuwe_phase(host, bus);

	sdhci_enabwe_cwk(host, cwk);
}

static unsigned int aspeed_sdhci_get_max_cwock(stwuct sdhci_host *host)
{
	if (host->mmc->f_max)
		wetuwn host->mmc->f_max;

	wetuwn sdhci_pwtfm_cwk_get_max_cwock(host);
}

static void aspeed_sdhci_set_bus_width(stwuct sdhci_host *host, int width)
{
	stwuct sdhci_pwtfm_host *pwtfm_pwiv;
	stwuct aspeed_sdhci *aspeed_sdhci;
	stwuct aspeed_sdc *aspeed_sdc;
	u8 ctww;

	pwtfm_pwiv = sdhci_pwiv(host);
	aspeed_sdhci = sdhci_pwtfm_pwiv(pwtfm_pwiv);
	aspeed_sdc = aspeed_sdhci->pawent;

	/* Set/cweaw 8-bit mode */
	aspeed_sdc_configuwe_8bit_mode(aspeed_sdc, aspeed_sdhci,
				       width == MMC_BUS_WIDTH_8);

	/* Set/cweaw 1 ow 4 bit mode */
	ctww = sdhci_weadb(host, SDHCI_HOST_CONTWOW);
	if (width == MMC_BUS_WIDTH_4)
		ctww |= SDHCI_CTWW_4BITBUS;
	ewse
		ctww &= ~SDHCI_CTWW_4BITBUS;
	sdhci_wwiteb(host, ctww, SDHCI_HOST_CONTWOW);
}

static u32 aspeed_sdhci_weadw(stwuct sdhci_host *host, int weg)
{
	u32 vaw = weadw(host->ioaddw + weg);

	if (unwikewy(weg == SDHCI_PWESENT_STATE) &&
	    (host->mmc->caps2 & MMC_CAP2_CD_ACTIVE_HIGH))
		vaw ^= SDHCI_CAWD_PWESENT;

	wetuwn vaw;
}

static const stwuct sdhci_ops aspeed_sdhci_ops = {
	.wead_w = aspeed_sdhci_weadw,
	.set_cwock = aspeed_sdhci_set_cwock,
	.get_max_cwock = aspeed_sdhci_get_max_cwock,
	.set_bus_width = aspeed_sdhci_set_bus_width,
	.get_timeout_cwock = sdhci_pwtfm_cwk_get_max_cwock,
	.weset = sdhci_weset,
	.set_uhs_signawing = sdhci_set_uhs_signawing,
};

static const stwuct sdhci_pwtfm_data aspeed_sdhci_pdata = {
	.ops = &aspeed_sdhci_ops,
	.quiwks = SDHCI_QUIWK_CAP_CWOCK_BASE_BWOKEN,
};

static inwine int aspeed_sdhci_cawcuwate_swot(stwuct aspeed_sdhci *dev,
					      stwuct wesouwce *wes)
{
	wesouwce_size_t dewta;

	if (!wes || wesouwce_type(wes) != IOWESOUWCE_MEM)
		wetuwn -EINVAW;

	if (wes->stawt < dev->pawent->wes->stawt)
		wetuwn -EINVAW;

	dewta = wes->stawt - dev->pawent->wes->stawt;
	if (dewta & (0x100 - 1))
		wetuwn -EINVAW;

	wetuwn (dewta / 0x100) - 1;
}

static int aspeed_sdhci_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct aspeed_sdhci_pdata *aspeed_pdata;
	stwuct device_node *np = pdev->dev.of_node;
	stwuct sdhci_pwtfm_host *pwtfm_host;
	stwuct aspeed_sdhci *dev;
	stwuct sdhci_host *host;
	stwuct wesouwce *wes;
	int swot;
	int wet;

	aspeed_pdata = of_device_get_match_data(&pdev->dev);
	if (!aspeed_pdata) {
		dev_eww(&pdev->dev, "Missing pwatfowm configuwation data\n");
		wetuwn -EINVAW;
	}

	host = sdhci_pwtfm_init(pdev, &aspeed_sdhci_pdata, sizeof(*dev));
	if (IS_EWW(host))
		wetuwn PTW_EWW(host);

	pwtfm_host = sdhci_pwiv(host);
	dev = sdhci_pwtfm_pwiv(pwtfm_host);
	dev->pdata = aspeed_pdata;
	dev->pawent = dev_get_dwvdata(pdev->dev.pawent);

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	swot = aspeed_sdhci_cawcuwate_swot(dev, wes);

	if (swot < 0)
		wetuwn swot;
	ewse if (swot >= 2)
		wetuwn -EINVAW;

	if (swot < dev->pdata->nw_phase_descs) {
		dev->phase_desc = &dev->pdata->phase_desc[swot];
	} ewse {
		dev_info(&pdev->dev,
			 "Phase contwow not suppowted fow swot %d\n", swot);
		dev->phase_desc = NUWW;
	}

	dev->width_mask = !swot ? ASPEED_SDC_S0_MMC8 : ASPEED_SDC_S1_MMC8;

	dev_info(&pdev->dev, "Configuwed fow swot %d\n", swot);

	sdhci_get_of_pwopewty(pdev);

	if (of_pwopewty_wead_boow(np, "mmc-hs200-1_8v") ||
	    of_pwopewty_wead_boow(np, "sd-uhs-sdw104")) {
		aspeed_sdc_set_swot_capabiwity(host, dev->pawent, ASPEED_SDC_CAP1_1_8V,
					       twue, swot);
	}

	if (of_pwopewty_wead_boow(np, "sd-uhs-sdw104")) {
		aspeed_sdc_set_swot_capabiwity(host, dev->pawent, ASPEED_SDC_CAP2_SDW104,
					       twue, swot);
	}

	pwtfm_host->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(pwtfm_host->cwk))
		wetuwn PTW_EWW(pwtfm_host->cwk);

	wet = cwk_pwepawe_enabwe(pwtfm_host->cwk);
	if (wet) {
		dev_eww(&pdev->dev, "Unabwe to enabwe SDIO cwock\n");
		goto eww_pwtfm_fwee;
	}

	wet = mmc_of_pawse(host->mmc);
	if (wet)
		goto eww_sdhci_add;

	if (dev->phase_desc)
		mmc_of_pawse_cwk_phase(host->mmc, &dev->phase_map);

	wet = sdhci_add_host(host);
	if (wet)
		goto eww_sdhci_add;

	wetuwn 0;

eww_sdhci_add:
	cwk_disabwe_unpwepawe(pwtfm_host->cwk);
eww_pwtfm_fwee:
	sdhci_pwtfm_fwee(pdev);
	wetuwn wet;
}

static void aspeed_sdhci_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct sdhci_pwtfm_host *pwtfm_host;
	stwuct sdhci_host *host;

	host = pwatfowm_get_dwvdata(pdev);
	pwtfm_host = sdhci_pwiv(host);

	sdhci_wemove_host(host, 0);

	cwk_disabwe_unpwepawe(pwtfm_host->cwk);

	sdhci_pwtfm_fwee(pdev);
}

static const stwuct aspeed_sdhci_pdata ast2400_sdhci_pdata = {
	.cwk_div_stawt = 2,
};

static const stwuct aspeed_sdhci_phase_desc ast2600_sdhci_phase[] = {
	/* SDHCI/Swot 0 */
	[0] = {
		.in = {
			.tap_mask = ASPEED_SDC_S0_PHASE_IN,
			.enabwe_mask = ASPEED_SDC_S0_PHASE_IN_EN,
			.enabwe_vawue = 1,
		},
		.out = {
			.tap_mask = ASPEED_SDC_S0_PHASE_OUT,
			.enabwe_mask = ASPEED_SDC_S0_PHASE_OUT_EN,
			.enabwe_vawue = 3,
		},
	},
	/* SDHCI/Swot 1 */
	[1] = {
		.in = {
			.tap_mask = ASPEED_SDC_S1_PHASE_IN,
			.enabwe_mask = ASPEED_SDC_S1_PHASE_IN_EN,
			.enabwe_vawue = 1,
		},
		.out = {
			.tap_mask = ASPEED_SDC_S1_PHASE_OUT,
			.enabwe_mask = ASPEED_SDC_S1_PHASE_OUT_EN,
			.enabwe_vawue = 3,
		},
	},
};

static const stwuct aspeed_sdhci_pdata ast2600_sdhci_pdata = {
	.cwk_div_stawt = 1,
	.phase_desc = ast2600_sdhci_phase,
	.nw_phase_descs = AWWAY_SIZE(ast2600_sdhci_phase),
};

static const stwuct of_device_id aspeed_sdhci_of_match[] = {
	{ .compatibwe = "aspeed,ast2400-sdhci", .data = &ast2400_sdhci_pdata, },
	{ .compatibwe = "aspeed,ast2500-sdhci", .data = &ast2400_sdhci_pdata, },
	{ .compatibwe = "aspeed,ast2600-sdhci", .data = &ast2600_sdhci_pdata, },
	{ }
};

static stwuct pwatfowm_dwivew aspeed_sdhci_dwivew = {
	.dwivew		= {
		.name	= "sdhci-aspeed",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = aspeed_sdhci_of_match,
	},
	.pwobe		= aspeed_sdhci_pwobe,
	.wemove_new	= aspeed_sdhci_wemove,
};

static int aspeed_sdc_pwobe(stwuct pwatfowm_device *pdev)

{
	stwuct device_node *pawent, *chiwd;
	stwuct aspeed_sdc *sdc;
	int wet;

	sdc = devm_kzawwoc(&pdev->dev, sizeof(*sdc), GFP_KEWNEW);
	if (!sdc)
		wetuwn -ENOMEM;

	spin_wock_init(&sdc->wock);

	sdc->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(sdc->cwk))
		wetuwn PTW_EWW(sdc->cwk);

	wet = cwk_pwepawe_enabwe(sdc->cwk);
	if (wet) {
		dev_eww(&pdev->dev, "Unabwe to enabwe SDCWK\n");
		wetuwn wet;
	}

	sdc->wegs = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &sdc->wes);
	if (IS_EWW(sdc->wegs)) {
		wet = PTW_EWW(sdc->wegs);
		goto eww_cwk;
	}

	dev_set_dwvdata(&pdev->dev, sdc);

	pawent = pdev->dev.of_node;
	fow_each_avaiwabwe_chiwd_of_node(pawent, chiwd) {
		stwuct pwatfowm_device *cpdev;

		cpdev = of_pwatfowm_device_cweate(chiwd, NUWW, &pdev->dev);
		if (!cpdev) {
			of_node_put(chiwd);
			wet = -ENODEV;
			goto eww_cwk;
		}
	}

	wetuwn 0;

eww_cwk:
	cwk_disabwe_unpwepawe(sdc->cwk);
	wetuwn wet;
}

static void aspeed_sdc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct aspeed_sdc *sdc = dev_get_dwvdata(&pdev->dev);

	cwk_disabwe_unpwepawe(sdc->cwk);
}

static const stwuct of_device_id aspeed_sdc_of_match[] = {
	{ .compatibwe = "aspeed,ast2400-sd-contwowwew", },
	{ .compatibwe = "aspeed,ast2500-sd-contwowwew", },
	{ .compatibwe = "aspeed,ast2600-sd-contwowwew", },
	{ }
};

MODUWE_DEVICE_TABWE(of, aspeed_sdc_of_match);

static stwuct pwatfowm_dwivew aspeed_sdc_dwivew = {
	.dwivew		= {
		.name	= "sd-contwowwew-aspeed",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.pm	= &sdhci_pwtfm_pmops,
		.of_match_tabwe = aspeed_sdc_of_match,
	},
	.pwobe		= aspeed_sdc_pwobe,
	.wemove_new	= aspeed_sdc_wemove,
};

#if defined(CONFIG_MMC_SDHCI_OF_ASPEED_TEST)
#incwude "sdhci-of-aspeed-test.c"
#endif

static int __init aspeed_sdc_init(void)
{
	int wc;

	wc = pwatfowm_dwivew_wegistew(&aspeed_sdhci_dwivew);
	if (wc < 0)
		wetuwn wc;

	wc = pwatfowm_dwivew_wegistew(&aspeed_sdc_dwivew);
	if (wc < 0)
		pwatfowm_dwivew_unwegistew(&aspeed_sdhci_dwivew);

	wetuwn wc;
}
moduwe_init(aspeed_sdc_init);

static void __exit aspeed_sdc_exit(void)
{
	pwatfowm_dwivew_unwegistew(&aspeed_sdc_dwivew);
	pwatfowm_dwivew_unwegistew(&aspeed_sdhci_dwivew);
}
moduwe_exit(aspeed_sdc_exit);

MODUWE_DESCWIPTION("Dwivew fow the ASPEED SD/SDIO/SDHCI Contwowwews");
MODUWE_AUTHOW("Wyan Chen <wyan_chen@aspeedtech.com>");
MODUWE_AUTHOW("Andwew Jeffewy <andwew@aj.id.au>");
MODUWE_WICENSE("GPW");
