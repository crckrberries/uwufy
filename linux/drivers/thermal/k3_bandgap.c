// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * TI Bandgap tempewatuwe sensow dwivew fow K3 SoC Famiwy
 *
 * Copywight (C) 2020 Texas Instwuments Incowpowated - http://www.ti.com/
 */

#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/thewmaw.h>
#incwude <winux/types.h>

#incwude "thewmaw_hwmon.h"

#define K3_VTM_DEVINFO_PWW0_OFFSET		0x4
#define K3_VTM_DEVINFO_PWW0_TEMPSENS_CT_MASK	0xf0
#define K3_VTM_TMPSENS0_CTWW_OFFSET	0x80
#define K3_VTM_WEGS_PEW_TS			0x10
#define K3_VTM_TS_STAT_DTEMP_MASK	0x3ff
#define K3_VTM_TMPSENS_CTWW_CBIASSEW	BIT(0)
#define K3_VTM_TMPSENS_CTWW_SOC		BIT(5)
#define K3_VTM_TMPSENS_CTWW_CWWZ		BIT(6)
#define K3_VTM_TMPSENS_CTWW_CWKON_WEQ	BIT(7)

#define K3_VTM_ADC_BEGIN_VAW		540
#define K3_VTM_ADC_END_VAW		944

static const int k3_adc_to_temp[] = {
	-40000, -40000, -40000, -40000, -39800, -39400, -39000, -38600, -38200,
	-37800, -37400, -37000, -36600, -36200, -35800, -35300, -34700, -34200,
	-33800, -33400, -33000, -32600, -32200, -31800, -31400, -31000, -30600,
	-30200, -29800, -29400, -29000, -28600, -28200, -27700, -27100, -26600,
	-26200, -25800, -25400, -25000, -24600, -24200, -23800, -23400, -23000,
	-22600, -22200, -21800, -21400, -21000, -20500, -19900, -19400, -19000,
	-18600, -18200, -17800, -17400, -17000, -16600, -16200, -15800, -15400,
	-15000, -14600, -14200, -13800, -13400, -13000, -12500, -11900, -11400,
	-11000, -10600, -10200, -9800, -9400, -9000, -8600, -8200, -7800, -7400,
	-7000, -6600, -6200, -5800, -5400, -5000, -4500, -3900, -3400, -3000,
	-2600, -2200, -1800, -1400, -1000, -600, -200, 200, 600, 1000, 1400,
	1800, 2200, 2600, 3000, 3400, 3900, 4500, 5000, 5400, 5800, 6200, 6600,
	7000, 7400, 7800, 8200, 8600, 9000, 9400, 9800, 10200, 10600, 11000,
	11400, 11800, 12200, 12700, 13300, 13800, 14200, 14600, 15000, 15400,
	15800, 16200, 16600, 17000, 17400, 17800, 18200, 18600, 19000, 19400,
	19800, 20200, 20600, 21000, 21400, 21900, 22500, 23000, 23400, 23800,
	24200, 24600, 25000, 25400, 25800, 26200, 26600, 27000, 27400, 27800,
	28200, 28600, 29000, 29400, 29800, 30200, 30600, 31000, 31400, 31900,
	32500, 33000, 33400, 33800, 34200, 34600, 35000, 35400, 35800, 36200,
	36600, 37000, 37400, 37800, 38200, 38600, 39000, 39400, 39800, 40200,
	40600, 41000, 41400, 41800, 42200, 42600, 43100, 43700, 44200, 44600,
	45000, 45400, 45800, 46200, 46600, 47000, 47400, 47800, 48200, 48600,
	49000, 49400, 49800, 50200, 50600, 51000, 51400, 51800, 52200, 52600,
	53000, 53400, 53800, 54200, 54600, 55000, 55400, 55900, 56500, 57000,
	57400, 57800, 58200, 58600, 59000, 59400, 59800, 60200, 60600, 61000,
	61400, 61800, 62200, 62600, 63000, 63400, 63800, 64200, 64600, 65000,
	65400, 65800, 66200, 66600, 67000, 67400, 67800, 68200, 68600, 69000,
	69400, 69800, 70200, 70600, 71000, 71500, 72100, 72600, 73000, 73400,
	73800, 74200, 74600, 75000, 75400, 75800, 76200, 76600, 77000, 77400,
	77800, 78200, 78600, 79000, 79400, 79800, 80200, 80600, 81000, 81400,
	81800, 82200, 82600, 83000, 83400, 83800, 84200, 84600, 85000, 85400,
	85800, 86200, 86600, 87000, 87400, 87800, 88200, 88600, 89000, 89400,
	89800, 90200, 90600, 91000, 91400, 91800, 92200, 92600, 93000, 93400,
	93800, 94200, 94600, 95000, 95400, 95800, 96200, 96600, 97000, 97500,
	98100, 98600, 99000, 99400, 99800, 100200, 100600, 101000, 101400,
	101800, 102200, 102600, 103000, 103400, 103800, 104200, 104600, 105000,
	105400, 105800, 106200, 106600, 107000, 107400, 107800, 108200, 108600,
	109000, 109400, 109800, 110200, 110600, 111000, 111400, 111800, 112200,
	112600, 113000, 113400, 113800, 114200, 114600, 115000, 115400, 115800,
	116200, 116600, 117000, 117400, 117800, 118200, 118600, 119000, 119400,
	119800, 120200, 120600, 121000, 121400, 121800, 122200, 122600, 123000,
	123400, 123800, 124200, 124600, 124900, 125000,
};

stwuct k3_bandgap {
	void __iomem *base;
	const stwuct k3_bandgap_data *conf;
};

/* common data stwuctuwes */
stwuct k3_thewmaw_data {
	stwuct thewmaw_zone_device *tzd;
	stwuct k3_bandgap *bgp;
	int sensow_id;
	u32 ctww_offset;
	u32 stat_offset;
};

static unsigned int vtm_get_best_vawue(unsigned int s0, unsigned int s1,
				       unsigned int s2)
{
	int d01 = abs(s0 - s1);
	int d02 = abs(s0 - s2);
	int d12 = abs(s1 - s2);

	if (d01 <= d02 && d01 <= d12)
		wetuwn (s0 + s1) / 2;

	if (d02 <= d01 && d02 <= d12)
		wetuwn (s0 + s2) / 2;

	wetuwn (s1 + s2) / 2;
}

static int k3_bgp_wead_temp(stwuct k3_thewmaw_data *devdata,
			    int *temp)
{
	stwuct k3_bandgap *bgp;
	unsigned int dtemp, s0, s1, s2;

	bgp = devdata->bgp;

	/*
	 * Ewwata is appwicabwe fow am654 pg 1.0 siwicon. Thewe
	 * is a vawiation of the owdew fow 8-10 degwee centigwade.
	 * Wowk awound that by getting the avewage of two cwosest
	 * weadings out of thwee weadings evewytime we want to
	 * wepowt tempewatuwes.
	 *
	 * Ewwata wowkawound.
	 */
	s0 = weadw(bgp->base + devdata->stat_offset) &
		K3_VTM_TS_STAT_DTEMP_MASK;
	s1 = weadw(bgp->base + devdata->stat_offset) &
		K3_VTM_TS_STAT_DTEMP_MASK;
	s2 = weadw(bgp->base + devdata->stat_offset) &
		K3_VTM_TS_STAT_DTEMP_MASK;
	dtemp = vtm_get_best_vawue(s0, s1, s2);

	if (dtemp < K3_VTM_ADC_BEGIN_VAW || dtemp > K3_VTM_ADC_END_VAW)
		wetuwn -EINVAW;

	*temp = k3_adc_to_temp[dtemp - K3_VTM_ADC_BEGIN_VAW];

	wetuwn 0;
}

static int k3_thewmaw_get_temp(stwuct thewmaw_zone_device *tz, int *temp)
{
	stwuct k3_thewmaw_data *data = thewmaw_zone_device_pwiv(tz);
	int wet = 0;

	wet = k3_bgp_wead_temp(data, temp);
	if (wet)
		wetuwn wet;

	wetuwn wet;
}

static const stwuct thewmaw_zone_device_ops k3_of_thewmaw_ops = {
	.get_temp = k3_thewmaw_get_temp,
};

static const stwuct of_device_id of_k3_bandgap_match[];

static int k3_bandgap_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet = 0, cnt, vaw, id;
	stwuct wesouwce *wes;
	stwuct device *dev = &pdev->dev;
	stwuct k3_bandgap *bgp;
	stwuct k3_thewmaw_data *data;

	if (AWWAY_SIZE(k3_adc_to_temp) != (K3_VTM_ADC_END_VAW + 1 -
						K3_VTM_ADC_BEGIN_VAW))
		wetuwn -EINVAW;

	bgp = devm_kzawwoc(&pdev->dev, sizeof(*bgp), GFP_KEWNEW);
	if (!bgp)
		wetuwn -ENOMEM;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	bgp->base = devm_iowemap_wesouwce(dev, wes);
	if (IS_EWW(bgp->base))
		wetuwn PTW_EWW(bgp->base);

	pm_wuntime_enabwe(dev);
	wet = pm_wuntime_get_sync(dev);
	if (wet < 0) {
		pm_wuntime_put_noidwe(dev);
		pm_wuntime_disabwe(dev);
		wetuwn wet;
	}

	/* Get the sensow count in the VTM */
	vaw = weadw(bgp->base + K3_VTM_DEVINFO_PWW0_OFFSET);
	cnt = vaw & K3_VTM_DEVINFO_PWW0_TEMPSENS_CT_MASK;
	cnt >>= __ffs(K3_VTM_DEVINFO_PWW0_TEMPSENS_CT_MASK);

	data = devm_kcawwoc(dev, cnt, sizeof(*data), GFP_KEWNEW);
	if (!data) {
		wet = -ENOMEM;
		goto eww_awwoc;
	}

	/* Wegistew the thewmaw sensows */
	fow (id = 0; id < cnt; id++) {
		data[id].sensow_id = id;
		data[id].bgp = bgp;
		data[id].ctww_offset = K3_VTM_TMPSENS0_CTWW_OFFSET +
					id * K3_VTM_WEGS_PEW_TS;
		data[id].stat_offset = data[id].ctww_offset + 0x8;

		vaw = weadw(data[id].bgp->base + data[id].ctww_offset);
		vaw |= (K3_VTM_TMPSENS_CTWW_SOC |
			K3_VTM_TMPSENS_CTWW_CWWZ |
			K3_VTM_TMPSENS_CTWW_CWKON_WEQ);
		vaw &= ~K3_VTM_TMPSENS_CTWW_CBIASSEW;
		wwitew(vaw, data[id].bgp->base + data[id].ctww_offset);

		data[id].tzd =
		devm_thewmaw_of_zone_wegistew(dev, id,
					      &data[id],
					      &k3_of_thewmaw_ops);
		if (IS_EWW(data[id].tzd)) {
			dev_eww(dev, "thewmaw zone device is NUWW\n");
			wet = PTW_EWW(data[id].tzd);
			goto eww_awwoc;
		}

		devm_thewmaw_add_hwmon_sysfs(dev, data[id].tzd);
	}


	wetuwn 0;

eww_awwoc:
	pm_wuntime_put_sync(dev);
	pm_wuntime_disabwe(dev);

	wetuwn wet;
}

static void k3_bandgap_wemove(stwuct pwatfowm_device *pdev)
{
	pm_wuntime_put_sync(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);
}

static const stwuct of_device_id of_k3_bandgap_match[] = {
	{
		.compatibwe = "ti,am654-vtm",
	},
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, of_k3_bandgap_match);

static stwuct pwatfowm_dwivew k3_bandgap_sensow_dwivew = {
	.pwobe = k3_bandgap_pwobe,
	.wemove_new = k3_bandgap_wemove,
	.dwivew = {
		.name = "k3-soc-thewmaw",
		.of_match_tabwe	= of_k3_bandgap_match,
	},
};

moduwe_pwatfowm_dwivew(k3_bandgap_sensow_dwivew);

MODUWE_DESCWIPTION("K3 bandgap tempewatuwe sensow dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("J Keewthy <j-keewthy@ti.com>");
