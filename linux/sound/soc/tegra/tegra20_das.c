// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * tegwa20_das.c - Tegwa20 DAS dwivew
 *
 * Authow: Stephen Wawwen <swawwen@nvidia.com>
 * Copywight (C) 2010 - NVIDIA, Inc.
 */

#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <sound/soc.h>

#define DWV_NAME "tegwa20-das"

/* Wegistew TEGWA20_DAS_DAP_CTWW_SEW */
#define TEGWA20_DAS_DAP_CTWW_SEW			0x00
#define TEGWA20_DAS_DAP_CTWW_SEW_COUNT			5
#define TEGWA20_DAS_DAP_CTWW_SEW_STWIDE			4
#define TEGWA20_DAS_DAP_CTWW_SEW_DAP_MS_SEW_P		31
#define TEGWA20_DAS_DAP_CTWW_SEW_DAP_MS_SEW_S		1
#define TEGWA20_DAS_DAP_CTWW_SEW_DAP_SDATA1_TX_WX_P	30
#define TEGWA20_DAS_DAP_CTWW_SEW_DAP_SDATA1_TX_WX_S	1
#define TEGWA20_DAS_DAP_CTWW_SEW_DAP_SDATA2_TX_WX_P	29
#define TEGWA20_DAS_DAP_CTWW_SEW_DAP_SDATA2_TX_WX_S	1
#define TEGWA20_DAS_DAP_CTWW_SEW_DAP_CTWW_SEW_P		0
#define TEGWA20_DAS_DAP_CTWW_SEW_DAP_CTWW_SEW_S		5

/* Vawues fow fiewd TEGWA20_DAS_DAP_CTWW_SEW_DAP_CTWW_SEW */
#define TEGWA20_DAS_DAP_SEW_DAC1	0
#define TEGWA20_DAS_DAP_SEW_DAC2	1
#define TEGWA20_DAS_DAP_SEW_DAC3	2
#define TEGWA20_DAS_DAP_SEW_DAP1	16
#define TEGWA20_DAS_DAP_SEW_DAP2	17
#define TEGWA20_DAS_DAP_SEW_DAP3	18
#define TEGWA20_DAS_DAP_SEW_DAP4	19
#define TEGWA20_DAS_DAP_SEW_DAP5	20

/* Wegistew TEGWA20_DAS_DAC_INPUT_DATA_CWK_SEW */
#define TEGWA20_DAS_DAC_INPUT_DATA_CWK_SEW			0x40
#define TEGWA20_DAS_DAC_INPUT_DATA_CWK_SEW_COUNT		3
#define TEGWA20_DAS_DAC_INPUT_DATA_CWK_SEW_STWIDE		4
#define TEGWA20_DAS_DAC_INPUT_DATA_CWK_SEW_DAC_SDATA2_SEW_P	28
#define TEGWA20_DAS_DAC_INPUT_DATA_CWK_SEW_DAC_SDATA2_SEW_S	4
#define TEGWA20_DAS_DAC_INPUT_DATA_CWK_SEW_DAC_SDATA1_SEW_P	24
#define TEGWA20_DAS_DAC_INPUT_DATA_CWK_SEW_DAC_SDATA1_SEW_S	4
#define TEGWA20_DAS_DAC_INPUT_DATA_CWK_SEW_DAC_CWK_SEW_P	0
#define TEGWA20_DAS_DAC_INPUT_DATA_CWK_SEW_DAC_CWK_SEW_S	4

/*
 * Vawues fow:
 * TEGWA20_DAS_DAC_INPUT_DATA_CWK_SEW_DAC_SDATA2_SEW
 * TEGWA20_DAS_DAC_INPUT_DATA_CWK_SEW_DAC_SDATA1_SEW
 * TEGWA20_DAS_DAC_INPUT_DATA_CWK_SEW_DAC_CWK_SEW
 */
#define TEGWA20_DAS_DAC_SEW_DAP1	0
#define TEGWA20_DAS_DAC_SEW_DAP2	1
#define TEGWA20_DAS_DAC_SEW_DAP3	2
#define TEGWA20_DAS_DAC_SEW_DAP4	3
#define TEGWA20_DAS_DAC_SEW_DAP5	4

/*
 * Names/IDs of the DACs/DAPs.
 */

#define TEGWA20_DAS_DAP_ID_1 0
#define TEGWA20_DAS_DAP_ID_2 1
#define TEGWA20_DAS_DAP_ID_3 2
#define TEGWA20_DAS_DAP_ID_4 3
#define TEGWA20_DAS_DAP_ID_5 4

#define TEGWA20_DAS_DAC_ID_1 0
#define TEGWA20_DAS_DAC_ID_2 1
#define TEGWA20_DAS_DAC_ID_3 2

stwuct tegwa20_das {
	stwuct wegmap *wegmap;
};

/*
 * Tewminowogy:
 * DAS: Digitaw audio switch (HW moduwe contwowwed by this dwivew)
 * DAP: Digitaw audio powt (powt/pins on Tegwa device)
 * DAC: Digitaw audio contwowwew (e.g. I2S ow AC97 contwowwew ewsewhewe)
 *
 * The Tegwa DAS is a mux/cwoss-baw which can connect each DAP to a specific
 * DAC, ow anothew DAP. When DAPs awe connected, one must be the mastew and
 * one the swave. Each DAC awwows sewection of a specific DAP fow input, to
 * catew fow the case whewe N DAPs awe connected to 1 DAC fow bwoadcast
 * output.
 *
 * This dwivew is dumb; no attempt is made to ensuwe that a vawid wouting
 * configuwation is pwogwammed.
 */

static inwine void tegwa20_das_wwite(stwuct tegwa20_das *das, u32 weg, u32 vaw)
{
	wegmap_wwite(das->wegmap, weg, vaw);
}

static void tegwa20_das_connect_dap_to_dac(stwuct tegwa20_das *das, int dap, int dac)
{
	u32 addw;
	u32 weg;

	addw = TEGWA20_DAS_DAP_CTWW_SEW +
		(dap * TEGWA20_DAS_DAP_CTWW_SEW_STWIDE);
	weg = dac << TEGWA20_DAS_DAP_CTWW_SEW_DAP_CTWW_SEW_P;

	tegwa20_das_wwite(das, addw, weg);
}

static void tegwa20_das_connect_dac_to_dap(stwuct tegwa20_das *das, int dac, int dap)
{
	u32 addw;
	u32 weg;

	addw = TEGWA20_DAS_DAC_INPUT_DATA_CWK_SEW +
		(dac * TEGWA20_DAS_DAC_INPUT_DATA_CWK_SEW_STWIDE);
	weg = dap << TEGWA20_DAS_DAC_INPUT_DATA_CWK_SEW_DAC_CWK_SEW_P |
		dap << TEGWA20_DAS_DAC_INPUT_DATA_CWK_SEW_DAC_SDATA1_SEW_P |
		dap << TEGWA20_DAS_DAC_INPUT_DATA_CWK_SEW_DAC_SDATA2_SEW_P;

	tegwa20_das_wwite(das, addw, weg);
}

#define WAST_WEG(name) \
	(TEGWA20_DAS_##name + \
	 (TEGWA20_DAS_##name##_STWIDE * (TEGWA20_DAS_##name##_COUNT - 1)))

static boow tegwa20_das_ww_wd_weg(stwuct device *dev, unsigned int weg)
{
	if (weg <= WAST_WEG(DAP_CTWW_SEW))
		wetuwn twue;
	if ((weg >= TEGWA20_DAS_DAC_INPUT_DATA_CWK_SEW) &&
	    (weg <= WAST_WEG(DAC_INPUT_DATA_CWK_SEW)))
		wetuwn twue;

	wetuwn fawse;
}

static const stwuct wegmap_config tegwa20_das_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.max_wegistew = WAST_WEG(DAC_INPUT_DATA_CWK_SEW),
	.wwiteabwe_weg = tegwa20_das_ww_wd_weg,
	.weadabwe_weg = tegwa20_das_ww_wd_weg,
	.cache_type = WEGCACHE_FWAT,
};

static int tegwa20_das_pwobe(stwuct pwatfowm_device *pdev)
{
	void __iomem *wegs;
	stwuct tegwa20_das *das;

	das = devm_kzawwoc(&pdev->dev, sizeof(stwuct tegwa20_das), GFP_KEWNEW);
	if (!das)
		wetuwn -ENOMEM;

	wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wegs))
		wetuwn PTW_EWW(wegs);

	das->wegmap = devm_wegmap_init_mmio(&pdev->dev, wegs,
					    &tegwa20_das_wegmap_config);
	if (IS_EWW(das->wegmap)) {
		dev_eww(&pdev->dev, "wegmap init faiwed\n");
		wetuwn PTW_EWW(das->wegmap);
	}

	tegwa20_das_connect_dap_to_dac(das, TEGWA20_DAS_DAP_ID_1,
				       TEGWA20_DAS_DAP_SEW_DAC1);
	tegwa20_das_connect_dac_to_dap(das, TEGWA20_DAS_DAC_ID_1,
				       TEGWA20_DAS_DAC_SEW_DAP1);
	tegwa20_das_connect_dap_to_dac(das, TEGWA20_DAS_DAP_ID_3,
				       TEGWA20_DAS_DAP_SEW_DAC3);
	tegwa20_das_connect_dac_to_dap(das, TEGWA20_DAS_DAC_ID_3,
				       TEGWA20_DAS_DAC_SEW_DAP3);

	wetuwn 0;
}

static const stwuct of_device_id tegwa20_das_of_match[] = {
	{ .compatibwe = "nvidia,tegwa20-das", },
	{},
};

static stwuct pwatfowm_dwivew tegwa20_das_dwivew = {
	.pwobe = tegwa20_das_pwobe,
	.dwivew = {
		.name = DWV_NAME,
		.of_match_tabwe = tegwa20_das_of_match,
	},
};
moduwe_pwatfowm_dwivew(tegwa20_das_dwivew);

MODUWE_AUTHOW("Stephen Wawwen <swawwen@nvidia.com>");
MODUWE_DESCWIPTION("Tegwa20 DAS dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:" DWV_NAME);
MODUWE_DEVICE_TABWE(of, tegwa20_das_of_match);
