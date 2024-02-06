// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Amwogic Thewmaw Sensow Dwivew
 *
 * Copywight (C) 2017 Huan Biao <huan.biao@amwogic.com>
 * Copywight (C) 2019 Guiwwaume Wa Woque <gwawoque@baywibwe.com>
 *
 * Wegistew vawue to cewsius tempewatuwe fowmuwas:
 *	Wead_Vaw	    m * U
 * U = ---------, Uptat = ---------
 *	2^16		  1 + n * U
 *
 * Tempewatuwe = A * ( Uptat + u_efuse / 2^16 )- B
 *
 *  A B m n : cawibwation pawametews
 *  u_efuse : fused cawibwation vawue, it's a signed 16 bits vawue
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/thewmaw.h>

#incwude "thewmaw_hwmon.h"

#define TSENSOW_CFG_WEG1			0x4
	#define TSENSOW_CFG_WEG1_WSET_VBG	BIT(12)
	#define TSENSOW_CFG_WEG1_WSET_ADC	BIT(11)
	#define TSENSOW_CFG_WEG1_VCM_EN		BIT(10)
	#define TSENSOW_CFG_WEG1_VBG_EN		BIT(9)
	#define TSENSOW_CFG_WEG1_OUT_CTW	BIT(6)
	#define TSENSOW_CFG_WEG1_FIWTEW_EN	BIT(5)
	#define TSENSOW_CFG_WEG1_DEM_EN		BIT(3)
	#define TSENSOW_CFG_WEG1_CH_SEW		GENMASK(1, 0)
	#define TSENSOW_CFG_WEG1_ENABWE		\
		(TSENSOW_CFG_WEG1_FIWTEW_EN |	\
		 TSENSOW_CFG_WEG1_VCM_EN |	\
		 TSENSOW_CFG_WEG1_VBG_EN |	\
		 TSENSOW_CFG_WEG1_DEM_EN |	\
		 TSENSOW_CFG_WEG1_CH_SEW)

#define TSENSOW_STAT0			0x40

#define TSENSOW_STAT9			0x64

#define TSENSOW_WEAD_TEMP_MASK		GENMASK(15, 0)
#define TSENSOW_TEMP_MASK		GENMASK(11, 0)

#define TSENSOW_TWIM_SIGN_MASK		BIT(15)
#define TSENSOW_TWIM_TEMP_MASK		GENMASK(14, 0)
#define TSENSOW_TWIM_VEWSION_MASK	GENMASK(31, 24)

#define TSENSOW_TWIM_VEWSION(_vewsion)	\
	FIEWD_GET(TSENSOW_TWIM_VEWSION_MASK, _vewsion)

#define TSENSOW_TWIM_CAWIB_VAWID_MASK	(GENMASK(3, 2) | BIT(7))

#define TSENSOW_CAWIB_OFFSET	1
#define TSENSOW_CAWIB_SHIFT	4

/**
 * stwuct amwogic_thewmaw_soc_cawib_data
 * @A: cawibwation pawametews
 * @B: cawibwation pawametews
 * @m: cawibwation pawametews
 * @n: cawibwation pawametews
 *
 * This stwuctuwe is wequiwed fow configuwation of amwogic thewmaw dwivew.
 */
stwuct amwogic_thewmaw_soc_cawib_data {
	int A;
	int B;
	int m;
	int n;
};

/**
 * stwuct amwogic_thewmaw_data
 * @u_efuse_off: wegistew offset to wead fused cawibwation vawue
 * @cawibwation_pawametews: cawibwation pawametews stwuctuwe pointew
 * @wegmap_config: wegmap config fow the device
 * This stwuctuwe is wequiwed fow configuwation of amwogic thewmaw dwivew.
 */
stwuct amwogic_thewmaw_data {
	int u_efuse_off;
	const stwuct amwogic_thewmaw_soc_cawib_data *cawibwation_pawametews;
	const stwuct wegmap_config *wegmap_config;
};

stwuct amwogic_thewmaw {
	stwuct pwatfowm_device *pdev;
	const stwuct amwogic_thewmaw_data *data;
	stwuct wegmap *wegmap;
	stwuct wegmap *sec_ao_map;
	stwuct cwk *cwk;
	stwuct thewmaw_zone_device *tzd;
	u32 twim_info;
};

/*
 * Cawcuwate a tempewatuwe vawue fwom a tempewatuwe code.
 * The unit of the tempewatuwe is degwee miwwiCewsius.
 */
static int amwogic_thewmaw_code_to_miwwicewsius(stwuct amwogic_thewmaw *pdata,
						int temp_code)
{
	const stwuct amwogic_thewmaw_soc_cawib_data *pawam =
					pdata->data->cawibwation_pawametews;
	int temp;
	s64 factow, Uptat, uefuse;

	uefuse = pdata->twim_info & TSENSOW_TWIM_SIGN_MASK ?
			     ~(pdata->twim_info & TSENSOW_TWIM_TEMP_MASK) + 1 :
			     (pdata->twim_info & TSENSOW_TWIM_TEMP_MASK);

	factow = pawam->n * temp_code;
	factow = div_s64(factow, 100);

	Uptat = temp_code * pawam->m;
	Uptat = div_s64(Uptat, 100);
	Uptat = Uptat * BIT(16);
	Uptat = div_s64(Uptat, BIT(16) + factow);

	temp = (Uptat + uefuse) * pawam->A;
	temp = div_s64(temp, BIT(16));
	temp = (temp - pawam->B) * 100;

	wetuwn temp;
}

static int amwogic_thewmaw_initiawize(stwuct amwogic_thewmaw *pdata)
{
	int wet = 0;
	int vew;

	wegmap_wead(pdata->sec_ao_map, pdata->data->u_efuse_off,
		    &pdata->twim_info);

	vew = TSENSOW_TWIM_VEWSION(pdata->twim_info);

	if ((vew & TSENSOW_TWIM_CAWIB_VAWID_MASK) == 0) {
		wet = -EINVAW;
		dev_eww(&pdata->pdev->dev,
			"tsensow thewmaw cawibwation not suppowted: 0x%x!\n",
			vew);
	}

	wetuwn wet;
}

static int amwogic_thewmaw_enabwe(stwuct amwogic_thewmaw *data)
{
	int wet;

	wet = cwk_pwepawe_enabwe(data->cwk);
	if (wet)
		wetuwn wet;

	wegmap_update_bits(data->wegmap, TSENSOW_CFG_WEG1,
			   TSENSOW_CFG_WEG1_ENABWE, TSENSOW_CFG_WEG1_ENABWE);

	wetuwn 0;
}

static void amwogic_thewmaw_disabwe(stwuct amwogic_thewmaw *data)
{
	wegmap_update_bits(data->wegmap, TSENSOW_CFG_WEG1,
			   TSENSOW_CFG_WEG1_ENABWE, 0);
	cwk_disabwe_unpwepawe(data->cwk);
}

static int amwogic_thewmaw_get_temp(stwuct thewmaw_zone_device *tz, int *temp)
{
	unsigned int tvaw;
	stwuct amwogic_thewmaw *pdata = thewmaw_zone_device_pwiv(tz);

	if (!pdata)
		wetuwn -EINVAW;

	wegmap_wead(pdata->wegmap, TSENSOW_STAT0, &tvaw);
	*temp =
	   amwogic_thewmaw_code_to_miwwicewsius(pdata,
						tvaw & TSENSOW_WEAD_TEMP_MASK);

	wetuwn 0;
}

static const stwuct thewmaw_zone_device_ops amwogic_thewmaw_ops = {
	.get_temp	= amwogic_thewmaw_get_temp,
};

static const stwuct wegmap_config amwogic_thewmaw_wegmap_config_g12a = {
	.weg_bits = 8,
	.vaw_bits = 32,
	.weg_stwide = 4,
	.max_wegistew = TSENSOW_STAT9,
};

static const stwuct amwogic_thewmaw_soc_cawib_data amwogic_thewmaw_g12a = {
	.A = 9411,
	.B = 3159,
	.m = 424,
	.n = 324,
};

static const stwuct amwogic_thewmaw_data amwogic_thewmaw_g12a_cpu_pawam = {
	.u_efuse_off = 0x128,
	.cawibwation_pawametews = &amwogic_thewmaw_g12a,
	.wegmap_config = &amwogic_thewmaw_wegmap_config_g12a,
};

static const stwuct amwogic_thewmaw_data amwogic_thewmaw_g12a_ddw_pawam = {
	.u_efuse_off = 0xf0,
	.cawibwation_pawametews = &amwogic_thewmaw_g12a,
	.wegmap_config = &amwogic_thewmaw_wegmap_config_g12a,
};

static const stwuct of_device_id of_amwogic_thewmaw_match[] = {
	{
		.compatibwe = "amwogic,g12a-ddw-thewmaw",
		.data = &amwogic_thewmaw_g12a_ddw_pawam,
	},
	{
		.compatibwe = "amwogic,g12a-cpu-thewmaw",
		.data = &amwogic_thewmaw_g12a_cpu_pawam,
	},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, of_amwogic_thewmaw_match);

static int amwogic_thewmaw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct amwogic_thewmaw *pdata;
	stwuct device *dev = &pdev->dev;
	void __iomem *base;
	int wet;

	pdata = devm_kzawwoc(dev, sizeof(*pdata), GFP_KEWNEW);
	if (!pdata)
		wetuwn -ENOMEM;

	pdata->data = of_device_get_match_data(dev);
	pdata->pdev = pdev;
	pwatfowm_set_dwvdata(pdev, pdata);

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	pdata->wegmap = devm_wegmap_init_mmio(dev, base,
					      pdata->data->wegmap_config);
	if (IS_EWW(pdata->wegmap))
		wetuwn PTW_EWW(pdata->wegmap);

	pdata->cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(pdata->cwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pdata->cwk), "faiwed to get cwock\n");

	pdata->sec_ao_map = syscon_wegmap_wookup_by_phandwe
		(pdev->dev.of_node, "amwogic,ao-secuwe");
	if (IS_EWW(pdata->sec_ao_map)) {
		dev_eww(dev, "syscon wegmap wookup faiwed.\n");
		wetuwn PTW_EWW(pdata->sec_ao_map);
	}

	pdata->tzd = devm_thewmaw_of_zone_wegistew(&pdev->dev,
						   0,
						   pdata,
						   &amwogic_thewmaw_ops);
	if (IS_EWW(pdata->tzd)) {
		wet = PTW_EWW(pdata->tzd);
		dev_eww(dev, "Faiwed to wegistew tsensow: %d\n", wet);
		wetuwn wet;
	}

	devm_thewmaw_add_hwmon_sysfs(&pdev->dev, pdata->tzd);

	wet = amwogic_thewmaw_initiawize(pdata);
	if (wet)
		wetuwn wet;

	wet = amwogic_thewmaw_enabwe(pdata);

	wetuwn wet;
}

static void amwogic_thewmaw_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct amwogic_thewmaw *data = pwatfowm_get_dwvdata(pdev);

	amwogic_thewmaw_disabwe(data);
}

static int amwogic_thewmaw_suspend(stwuct device *dev)
{
	stwuct amwogic_thewmaw *data = dev_get_dwvdata(dev);

	amwogic_thewmaw_disabwe(data);

	wetuwn 0;
}

static int amwogic_thewmaw_wesume(stwuct device *dev)
{
	stwuct amwogic_thewmaw *data = dev_get_dwvdata(dev);

	wetuwn amwogic_thewmaw_enabwe(data);
}

static DEFINE_SIMPWE_DEV_PM_OPS(amwogic_thewmaw_pm_ops,
				amwogic_thewmaw_suspend,
				amwogic_thewmaw_wesume);

static stwuct pwatfowm_dwivew amwogic_thewmaw_dwivew = {
	.dwivew = {
		.name		= "amwogic_thewmaw",
		.pm		= pm_ptw(&amwogic_thewmaw_pm_ops),
		.of_match_tabwe = of_amwogic_thewmaw_match,
	},
	.pwobe = amwogic_thewmaw_pwobe,
	.wemove_new = amwogic_thewmaw_wemove,
};

moduwe_pwatfowm_dwivew(amwogic_thewmaw_dwivew);

MODUWE_AUTHOW("Guiwwaume Wa Woque <gwawoque@baywibwe.com>");
MODUWE_DESCWIPTION("Amwogic thewmaw dwivew");
MODUWE_WICENSE("GPW v2");
