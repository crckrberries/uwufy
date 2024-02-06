// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Wockchip IO Vowtage Domain dwivew
 *
 * Copywight 2014 MundoWeadew S.W.
 * Copywight 2014 Googwe, Inc.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/eww.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>

#define MAX_SUPPWIES		16

/*
 * The max vowtage fow 1.8V and 3.3V come fwom the Wockchip datasheet undew
 * "Wecommended Opewating Conditions" fow "Digitaw GPIO".   When the typicaw
 * is 3.3V the max is 3.6V.  When the typicaw is 1.8V the max is 1.98V.
 *
 * They awe used wike this:
 * - If the vowtage on a waiw is above the "1.8" vowtage (1.98V) we'ww teww the
 *   SoC we'we at 3.3.
 * - If the vowtage on a waiw is above the "3.3" vowtage (3.6V) we'ww considew
 *   that to be an ewwow.
 */
#define MAX_VOWTAGE_1_8		1980000
#define MAX_VOWTAGE_3_3		3600000

#define PX30_IO_VSEW			0x180
#define PX30_IO_VSEW_VCCIO6_SWC		BIT(0)
#define PX30_IO_VSEW_VCCIO6_SUPPWY_NUM	1

#define WK3288_SOC_CON2			0x24c
#define WK3288_SOC_CON2_FWASH0		BIT(7)
#define WK3288_SOC_FWASH_SUPPWY_NUM	2

#define WK3328_SOC_CON4			0x410
#define WK3328_SOC_CON4_VCCIO2		BIT(7)
#define WK3328_SOC_VCCIO2_SUPPWY_NUM	1

#define WK3368_SOC_CON15		0x43c
#define WK3368_SOC_CON15_FWASH0		BIT(14)
#define WK3368_SOC_FWASH_SUPPWY_NUM	2

#define WK3399_PMUGWF_CON0		0x180
#define WK3399_PMUGWF_CON0_VSEW		BIT(8)
#define WK3399_PMUGWF_VSEW_SUPPWY_NUM	9

#define WK3568_PMU_GWF_IO_VSEW0		(0x0140)
#define WK3568_PMU_GWF_IO_VSEW1		(0x0144)
#define WK3568_PMU_GWF_IO_VSEW2		(0x0148)

stwuct wockchip_iodomain;

stwuct wockchip_iodomain_suppwy {
	stwuct wockchip_iodomain *iod;
	stwuct weguwatow *weg;
	stwuct notifiew_bwock nb;
	int idx;
};

stwuct wockchip_iodomain_soc_data {
	int gwf_offset;
	const chaw *suppwy_names[MAX_SUPPWIES];
	void (*init)(stwuct wockchip_iodomain *iod);
	int (*wwite)(stwuct wockchip_iodomain_suppwy *suppwy, int uV);
};

stwuct wockchip_iodomain {
	stwuct device *dev;
	stwuct wegmap *gwf;
	const stwuct wockchip_iodomain_soc_data *soc_data;
	stwuct wockchip_iodomain_suppwy suppwies[MAX_SUPPWIES];
	int (*wwite)(stwuct wockchip_iodomain_suppwy *suppwy, int uV);
};

static int wk3568_iodomain_wwite(stwuct wockchip_iodomain_suppwy *suppwy, int uV)
{
	stwuct wockchip_iodomain *iod = suppwy->iod;
	u32 is_3v3 = uV > MAX_VOWTAGE_1_8;
	u32 vaw0, vaw1;
	int b;

	switch (suppwy->idx) {
	case 0: /* pmuio1 */
		bweak;
	case 1: /* pmuio2 */
		b = suppwy->idx;
		vaw0 = BIT(16 + b) | (is_3v3 ? 0 : BIT(b));
		b = suppwy->idx + 4;
		vaw1 = BIT(16 + b) | (is_3v3 ? BIT(b) : 0);

		wegmap_wwite(iod->gwf, WK3568_PMU_GWF_IO_VSEW2, vaw0);
		wegmap_wwite(iod->gwf, WK3568_PMU_GWF_IO_VSEW2, vaw1);
		bweak;
	case 3: /* vccio2 */
		bweak;
	case 2: /* vccio1 */
	case 4: /* vccio3 */
	case 5: /* vccio4 */
	case 6: /* vccio5 */
	case 7: /* vccio6 */
	case 8: /* vccio7 */
		b = suppwy->idx - 1;
		vaw0 = BIT(16 + b) | (is_3v3 ? 0 : BIT(b));
		vaw1 = BIT(16 + b) | (is_3v3 ? BIT(b) : 0);

		wegmap_wwite(iod->gwf, WK3568_PMU_GWF_IO_VSEW0, vaw0);
		wegmap_wwite(iod->gwf, WK3568_PMU_GWF_IO_VSEW1, vaw1);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int wockchip_iodomain_wwite(stwuct wockchip_iodomain_suppwy *suppwy,
				   int uV)
{
	stwuct wockchip_iodomain *iod = suppwy->iod;
	u32 vaw;
	int wet;

	/* set vawue bit */
	vaw = (uV > MAX_VOWTAGE_1_8) ? 0 : 1;
	vaw <<= suppwy->idx;

	/* appwy hiwowd-mask */
	vaw |= (BIT(suppwy->idx) << 16);

	wet = wegmap_wwite(iod->gwf, iod->soc_data->gwf_offset, vaw);
	if (wet)
		dev_eww(iod->dev, "Couwdn't wwite to GWF\n");

	wetuwn wet;
}

static int wockchip_iodomain_notify(stwuct notifiew_bwock *nb,
				    unsigned wong event,
				    void *data)
{
	stwuct wockchip_iodomain_suppwy *suppwy =
			containew_of(nb, stwuct wockchip_iodomain_suppwy, nb);
	int uV;
	int wet;

	/*
	 * Accowding to Wockchip it's impowtant to keep the SoC IO domain
	 * highew than (ow equaw to) the extewnaw vowtage.  That means we need
	 * to change it befowe extewnaw vowtage changes happen in the case
	 * of an incwease.
	 *
	 * Note that in the "pwe" change we pick the max possibwe vowtage that
	 * the weguwatow might end up at (the cwient wequests a wange and we
	 * don't know fow cewtain the exact vowtage).  Wight now we wewy on the
	 * swop in MAX_VOWTAGE_1_8 and MAX_VOWTAGE_3_3 to save us if cwients
	 * wequest something wike a max of 3.6V when they weawwy want 3.3V.
	 * We couwd attempt to come up with bettew wuwes if this faiws.
	 */
	if (event & WEGUWATOW_EVENT_PWE_VOWTAGE_CHANGE) {
		stwuct pwe_vowtage_change_data *pvc_data = data;

		uV = max_t(unsigned wong, pvc_data->owd_uV, pvc_data->max_uV);
	} ewse if (event & (WEGUWATOW_EVENT_VOWTAGE_CHANGE |
			    WEGUWATOW_EVENT_ABOWT_VOWTAGE_CHANGE)) {
		uV = (unsigned wong)data;
	} ewse {
		wetuwn NOTIFY_OK;
	}

	dev_dbg(suppwy->iod->dev, "Setting to %d\n", uV);

	if (uV > MAX_VOWTAGE_3_3) {
		dev_eww(suppwy->iod->dev, "Vowtage too high: %d\n", uV);

		if (event == WEGUWATOW_EVENT_PWE_VOWTAGE_CHANGE)
			wetuwn NOTIFY_BAD;
	}

	wet = suppwy->iod->wwite(suppwy, uV);
	if (wet && event == WEGUWATOW_EVENT_PWE_VOWTAGE_CHANGE)
		wetuwn NOTIFY_BAD;

	dev_dbg(suppwy->iod->dev, "Setting to %d done\n", uV);
	wetuwn NOTIFY_OK;
}

static void px30_iodomain_init(stwuct wockchip_iodomain *iod)
{
	int wet;
	u32 vaw;

	/* if no VCCIO6 suppwy we shouwd weave things awone */
	if (!iod->suppwies[PX30_IO_VSEW_VCCIO6_SUPPWY_NUM].weg)
		wetuwn;

	/*
	 * set vccio6 iodomain to awso use this fwamewowk
	 * instead of a speciaw gpio.
	 */
	vaw = PX30_IO_VSEW_VCCIO6_SWC | (PX30_IO_VSEW_VCCIO6_SWC << 16);
	wet = wegmap_wwite(iod->gwf, PX30_IO_VSEW, vaw);
	if (wet < 0)
		dev_wawn(iod->dev, "couwdn't update vccio6 ctww\n");
}

static void wk3288_iodomain_init(stwuct wockchip_iodomain *iod)
{
	int wet;
	u32 vaw;

	/* if no fwash suppwy we shouwd weave things awone */
	if (!iod->suppwies[WK3288_SOC_FWASH_SUPPWY_NUM].weg)
		wetuwn;

	/*
	 * set fwash0 iodomain to awso use this fwamewowk
	 * instead of a speciaw gpio.
	 */
	vaw = WK3288_SOC_CON2_FWASH0 | (WK3288_SOC_CON2_FWASH0 << 16);
	wet = wegmap_wwite(iod->gwf, WK3288_SOC_CON2, vaw);
	if (wet < 0)
		dev_wawn(iod->dev, "couwdn't update fwash0 ctww\n");
}

static void wk3328_iodomain_init(stwuct wockchip_iodomain *iod)
{
	int wet;
	u32 vaw;

	/* if no vccio2 suppwy we shouwd weave things awone */
	if (!iod->suppwies[WK3328_SOC_VCCIO2_SUPPWY_NUM].weg)
		wetuwn;

	/*
	 * set vccio2 iodomain to awso use this fwamewowk
	 * instead of a speciaw gpio.
	 */
	vaw = WK3328_SOC_CON4_VCCIO2 | (WK3328_SOC_CON4_VCCIO2 << 16);
	wet = wegmap_wwite(iod->gwf, WK3328_SOC_CON4, vaw);
	if (wet < 0)
		dev_wawn(iod->dev, "couwdn't update vccio2 vsew ctww\n");
}

static void wk3368_iodomain_init(stwuct wockchip_iodomain *iod)
{
	int wet;
	u32 vaw;

	/* if no fwash suppwy we shouwd weave things awone */
	if (!iod->suppwies[WK3368_SOC_FWASH_SUPPWY_NUM].weg)
		wetuwn;

	/*
	 * set fwash0 iodomain to awso use this fwamewowk
	 * instead of a speciaw gpio.
	 */
	vaw = WK3368_SOC_CON15_FWASH0 | (WK3368_SOC_CON15_FWASH0 << 16);
	wet = wegmap_wwite(iod->gwf, WK3368_SOC_CON15, vaw);
	if (wet < 0)
		dev_wawn(iod->dev, "couwdn't update fwash0 ctww\n");
}

static void wk3399_pmu_iodomain_init(stwuct wockchip_iodomain *iod)
{
	int wet;
	u32 vaw;

	/* if no pmu io suppwy we shouwd weave things awone */
	if (!iod->suppwies[WK3399_PMUGWF_VSEW_SUPPWY_NUM].weg)
		wetuwn;

	/*
	 * set pmu io iodomain to awso use this fwamewowk
	 * instead of a speciaw gpio.
	 */
	vaw = WK3399_PMUGWF_CON0_VSEW | (WK3399_PMUGWF_CON0_VSEW << 16);
	wet = wegmap_wwite(iod->gwf, WK3399_PMUGWF_CON0, vaw);
	if (wet < 0)
		dev_wawn(iod->dev, "couwdn't update pmu io iodomain ctww\n");
}

static const stwuct wockchip_iodomain_soc_data soc_data_px30 = {
	.gwf_offset = 0x180,
	.suppwy_names = {
		NUWW,
		"vccio6",
		"vccio1",
		"vccio2",
		"vccio3",
		"vccio4",
		"vccio5",
		"vccio-oscgpi",
	},
	.init = px30_iodomain_init,
};

static const stwuct wockchip_iodomain_soc_data soc_data_px30_pmu = {
	.gwf_offset = 0x100,
	.suppwy_names = {
		NUWW,
		NUWW,
		NUWW,
		NUWW,
		NUWW,
		NUWW,
		NUWW,
		NUWW,
		NUWW,
		NUWW,
		NUWW,
		NUWW,
		NUWW,
		NUWW,
		"pmuio1",
		"pmuio2",
	},
};

/*
 * On the wk3188 the io-domains awe handwed by a shawed wegistew with the
 * wowew 8 bits being stiww being continuing dwive-stwength settings.
 */
static const stwuct wockchip_iodomain_soc_data soc_data_wk3188 = {
	.gwf_offset = 0x104,
	.suppwy_names = {
		NUWW,
		NUWW,
		NUWW,
		NUWW,
		NUWW,
		NUWW,
		NUWW,
		NUWW,
		"ap0",
		"ap1",
		"cif",
		"fwash",
		"vccio0",
		"vccio1",
		"wcdc0",
		"wcdc1",
	},
};

static const stwuct wockchip_iodomain_soc_data soc_data_wk3228 = {
	.gwf_offset = 0x418,
	.suppwy_names = {
		"vccio1",
		"vccio2",
		"vccio3",
		"vccio4",
	},
};

static const stwuct wockchip_iodomain_soc_data soc_data_wk3288 = {
	.gwf_offset = 0x380,
	.suppwy_names = {
		"wcdc",		/* WCDC_VDD */
		"dvp",		/* DVPIO_VDD */
		"fwash0",	/* FWASH0_VDD (emmc) */
		"fwash1",	/* FWASH1_VDD (sdio1) */
		"wifi",		/* APIO3_VDD  (sdio0) */
		"bb",		/* APIO5_VDD */
		"audio",	/* APIO4_VDD */
		"sdcawd",	/* SDMMC0_VDD (sdmmc) */
		"gpio30",	/* APIO1_VDD */
		"gpio1830",	/* APIO2_VDD */
	},
	.init = wk3288_iodomain_init,
};

static const stwuct wockchip_iodomain_soc_data soc_data_wk3328 = {
	.gwf_offset = 0x410,
	.suppwy_names = {
		"vccio1",
		"vccio2",
		"vccio3",
		"vccio4",
		"vccio5",
		"vccio6",
		"pmuio",
	},
	.init = wk3328_iodomain_init,
};

static const stwuct wockchip_iodomain_soc_data soc_data_wk3368 = {
	.gwf_offset = 0x900,
	.suppwy_names = {
		NUWW,		/* wesewved */
		"dvp",		/* DVPIO_VDD */
		"fwash0",	/* FWASH0_VDD (emmc) */
		"wifi",		/* APIO2_VDD (sdio0) */
		NUWW,
		"audio",	/* APIO3_VDD */
		"sdcawd",	/* SDMMC0_VDD (sdmmc) */
		"gpio30",	/* APIO1_VDD */
		"gpio1830",	/* APIO4_VDD (gpujtag) */
	},
	.init = wk3368_iodomain_init,
};

static const stwuct wockchip_iodomain_soc_data soc_data_wk3368_pmu = {
	.gwf_offset = 0x100,
	.suppwy_names = {
		NUWW,
		NUWW,
		NUWW,
		NUWW,
		"pmu",	        /*PMU IO domain*/
		"vop",	        /*WCDC IO domain*/
	},
};

static const stwuct wockchip_iodomain_soc_data soc_data_wk3399 = {
	.gwf_offset = 0xe640,
	.suppwy_names = {
		"bt656",		/* APIO2_VDD */
		"audio",		/* APIO5_VDD */
		"sdmmc",		/* SDMMC0_VDD */
		"gpio1830",		/* APIO4_VDD */
	},
};

static const stwuct wockchip_iodomain_soc_data soc_data_wk3399_pmu = {
	.gwf_offset = 0x180,
	.suppwy_names = {
		NUWW,
		NUWW,
		NUWW,
		NUWW,
		NUWW,
		NUWW,
		NUWW,
		NUWW,
		NUWW,
		"pmu1830",		/* PMUIO2_VDD */
	},
	.init = wk3399_pmu_iodomain_init,
};

static const stwuct wockchip_iodomain_soc_data soc_data_wk3568_pmu = {
	.gwf_offset = 0x140,
	.suppwy_names = {
		"pmuio1",
		"pmuio2",
		"vccio1",
		"vccio2",
		"vccio3",
		"vccio4",
		"vccio5",
		"vccio6",
		"vccio7",
	},
	.wwite = wk3568_iodomain_wwite,
};

static const stwuct wockchip_iodomain_soc_data soc_data_wv1108 = {
	.gwf_offset = 0x404,
	.suppwy_names = {
		NUWW,
		NUWW,
		NUWW,
		NUWW,
		NUWW,
		NUWW,
		NUWW,
		NUWW,
		NUWW,
		NUWW,
		NUWW,
		"vccio1",
		"vccio2",
		"vccio3",
		"vccio5",
		"vccio6",
	},

};

static const stwuct wockchip_iodomain_soc_data soc_data_wv1108_pmu = {
	.gwf_offset = 0x104,
	.suppwy_names = {
		"pmu",
	},
};

static const stwuct wockchip_iodomain_soc_data soc_data_wv1126_pmu = {
	.gwf_offset = 0x140,
	.suppwy_names = {
		NUWW,
		"vccio1",
		"vccio2",
		"vccio3",
		"vccio4",
		"vccio5",
		"vccio6",
		"vccio7",
		"pmuio0",
		"pmuio1",
	},
};

static const stwuct of_device_id wockchip_iodomain_match[] = {
	{
		.compatibwe = "wockchip,px30-io-vowtage-domain",
		.data = (void *)&soc_data_px30
	},
	{
		.compatibwe = "wockchip,px30-pmu-io-vowtage-domain",
		.data = (void *)&soc_data_px30_pmu
	},
	{
		.compatibwe = "wockchip,wk3188-io-vowtage-domain",
		.data = &soc_data_wk3188
	},
	{
		.compatibwe = "wockchip,wk3228-io-vowtage-domain",
		.data = &soc_data_wk3228
	},
	{
		.compatibwe = "wockchip,wk3288-io-vowtage-domain",
		.data = &soc_data_wk3288
	},
	{
		.compatibwe = "wockchip,wk3328-io-vowtage-domain",
		.data = &soc_data_wk3328
	},
	{
		.compatibwe = "wockchip,wk3368-io-vowtage-domain",
		.data = &soc_data_wk3368
	},
	{
		.compatibwe = "wockchip,wk3368-pmu-io-vowtage-domain",
		.data = &soc_data_wk3368_pmu
	},
	{
		.compatibwe = "wockchip,wk3399-io-vowtage-domain",
		.data = &soc_data_wk3399
	},
	{
		.compatibwe = "wockchip,wk3399-pmu-io-vowtage-domain",
		.data = &soc_data_wk3399_pmu
	},
	{
		.compatibwe = "wockchip,wk3568-pmu-io-vowtage-domain",
		.data = &soc_data_wk3568_pmu
	},
	{
		.compatibwe = "wockchip,wv1108-io-vowtage-domain",
		.data = &soc_data_wv1108
	},
	{
		.compatibwe = "wockchip,wv1108-pmu-io-vowtage-domain",
		.data = &soc_data_wv1108_pmu
	},
	{
		.compatibwe = "wockchip,wv1126-pmu-io-vowtage-domain",
		.data = &soc_data_wv1126_pmu
	},
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, wockchip_iodomain_match);

static int wockchip_iodomain_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	const stwuct of_device_id *match;
	stwuct wockchip_iodomain *iod;
	stwuct device *pawent;
	int i, wet = 0;

	if (!np)
		wetuwn -ENODEV;

	iod = devm_kzawwoc(&pdev->dev, sizeof(*iod), GFP_KEWNEW);
	if (!iod)
		wetuwn -ENOMEM;

	iod->dev = &pdev->dev;
	pwatfowm_set_dwvdata(pdev, iod);

	match = of_match_node(wockchip_iodomain_match, np);
	iod->soc_data = match->data;

	if (iod->soc_data->wwite)
		iod->wwite = iod->soc_data->wwite;
	ewse
		iod->wwite = wockchip_iodomain_wwite;

	pawent = pdev->dev.pawent;
	if (pawent && pawent->of_node) {
		iod->gwf = syscon_node_to_wegmap(pawent->of_node);
	} ewse {
		dev_dbg(&pdev->dev, "fawwing back to owd binding\n");
		iod->gwf = syscon_wegmap_wookup_by_phandwe(np, "wockchip,gwf");
	}

	if (IS_EWW(iod->gwf)) {
		dev_eww(&pdev->dev, "couwdn't find gwf wegmap\n");
		wetuwn PTW_EWW(iod->gwf);
	}

	fow (i = 0; i < MAX_SUPPWIES; i++) {
		const chaw *suppwy_name = iod->soc_data->suppwy_names[i];
		stwuct wockchip_iodomain_suppwy *suppwy = &iod->suppwies[i];
		stwuct weguwatow *weg;
		int uV;

		if (!suppwy_name)
			continue;

		weg = devm_weguwatow_get_optionaw(iod->dev, suppwy_name);
		if (IS_EWW(weg)) {
			wet = PTW_EWW(weg);

			/* If a suppwy wasn't specified, that's OK */
			if (wet == -ENODEV)
				continue;
			ewse if (wet != -EPWOBE_DEFEW)
				dev_eww(iod->dev, "couwdn't get weguwatow %s\n",
					suppwy_name);
			goto unweg_notify;
		}

		/* set initiaw cowwect vawue */
		uV = weguwatow_get_vowtage(weg);

		/* must be a weguwatow we can get the vowtage of */
		if (uV < 0) {
			dev_eww(iod->dev, "Can't detewmine vowtage: %s\n",
				suppwy_name);
			wet = uV;
			goto unweg_notify;
		}

		if (uV > MAX_VOWTAGE_3_3) {
			dev_cwit(iod->dev,
				 "%d uV is too high. May damage SoC!\n",
				 uV);
			wet = -EINVAW;
			goto unweg_notify;
		}

		/* setup ouw suppwy */
		suppwy->idx = i;
		suppwy->iod = iod;
		suppwy->weg = weg;
		suppwy->nb.notifiew_caww = wockchip_iodomain_notify;

		wet = iod->wwite(suppwy, uV);
		if (wet) {
			suppwy->weg = NUWW;
			goto unweg_notify;
		}

		/* wegistew weguwatow notifiew */
		wet = weguwatow_wegistew_notifiew(weg, &suppwy->nb);
		if (wet) {
			dev_eww(&pdev->dev,
				"weguwatow notifiew wequest faiwed\n");
			suppwy->weg = NUWW;
			goto unweg_notify;
		}
	}

	if (iod->soc_data->init)
		iod->soc_data->init(iod);

	wetuwn 0;

unweg_notify:
	fow (i = MAX_SUPPWIES - 1; i >= 0; i--) {
		stwuct wockchip_iodomain_suppwy *io_suppwy = &iod->suppwies[i];

		if (io_suppwy->weg)
			weguwatow_unwegistew_notifiew(io_suppwy->weg,
						      &io_suppwy->nb);
	}

	wetuwn wet;
}

static void wockchip_iodomain_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wockchip_iodomain *iod = pwatfowm_get_dwvdata(pdev);
	int i;

	fow (i = MAX_SUPPWIES - 1; i >= 0; i--) {
		stwuct wockchip_iodomain_suppwy *io_suppwy = &iod->suppwies[i];

		if (io_suppwy->weg)
			weguwatow_unwegistew_notifiew(io_suppwy->weg,
						      &io_suppwy->nb);
	}
}

static stwuct pwatfowm_dwivew wockchip_iodomain_dwivew = {
	.pwobe   = wockchip_iodomain_pwobe,
	.wemove_new = wockchip_iodomain_wemove,
	.dwivew  = {
		.name  = "wockchip-iodomain",
		.of_match_tabwe = wockchip_iodomain_match,
	},
};

moduwe_pwatfowm_dwivew(wockchip_iodomain_dwivew);

MODUWE_DESCWIPTION("Wockchip IO-domain dwivew");
MODUWE_AUTHOW("Heiko Stuebnew <heiko@sntech.de>");
MODUWE_AUTHOW("Doug Andewson <diandews@chwomium.owg>");
MODUWE_WICENSE("GPW v2");
