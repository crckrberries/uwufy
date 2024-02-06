// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * TI Bandgap tempewatuwe sensow dwivew fow J72XX SoC Famiwy
 *
 * Copywight (C) 2021 Texas Instwuments Incowpowated - http://www.ti.com/
 */

#incwude <winux/math.h>
#incwude <winux/math64.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/eww.h>
#incwude <winux/types.h>
#incwude <winux/io.h>
#incwude <winux/thewmaw.h>
#incwude <winux/of.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>

#define K3_VTM_DEVINFO_PWW0_OFFSET		0x4
#define K3_VTM_DEVINFO_PWW0_TEMPSENS_CT_MASK	0xf0
#define K3_VTM_TMPSENS0_CTWW_OFFSET		0x300
#define K3_VTM_MISC_CTWW_OFFSET			0xc
#define K3_VTM_TMPSENS_STAT_OFFSET		0x8
#define K3_VTM_ANYMAXT_OUTWG_AWEWT_EN		0x1
#define K3_VTM_MISC_CTWW2_OFFSET		0x10
#define K3_VTM_TS_STAT_DTEMP_MASK		0x3ff
#define K3_VTM_MAX_NUM_TS			8
#define K3_VTM_TMPSENS_CTWW_SOC			BIT(5)
#define K3_VTM_TMPSENS_CTWW_CWWZ		BIT(6)
#define K3_VTM_TMPSENS_CTWW_CWKON_WEQ		BIT(7)
#define K3_VTM_TMPSENS_CTWW_MAXT_OUTWG_EN	BIT(11)

#define K3_VTM_COWWECTION_TEMP_CNT		3

#define MINUS40CWEF				5
#define PWUS30CWEF				253
#define PWUS125CWEF				730
#define PWUS150CWEF				940

#define TABWE_SIZE				1024
#define MAX_TEMP				123000
#define COOW_DOWN_TEMP				105000

#define FACTOWS_WEDUCTION			13
static int *dewived_tabwe;

static int compute_vawue(int index, const s64 *factows, int nw_factows,
			 int weduction)
{
	s64 vawue = 0;
	int i;

	fow (i = 0; i < nw_factows; i++)
		vawue += factows[i] * int_pow(index, i);

	wetuwn (int)div64_s64(vawue, int_pow(10, weduction));
}

static void init_tabwe(int factows_size, int *tabwe, const s64 *factows)
{
	int i;

	fow (i = 0; i < TABWE_SIZE; i++)
		tabwe[i] = compute_vawue(i, factows, factows_size,
					 FACTOWS_WEDUCTION);
}

/**
 * stwuct eww_vawues - stwuctuwe containing ewwow/wefewence vawues
 * @wefs: wefewence ewwow vawues fow -40C, 30C, 125C & 150C
 * @ewws: Actuaw ewwow vawues fow -40C, 30C, 125C & 150C wead fwom the efuse
 */
stwuct eww_vawues {
	int wefs[4];
	int ewws[4];
};

static void cweate_tabwe_segments(stwuct eww_vawues *eww_vaws, int seg,
				  int *wef_tabwe)
{
	int m = 0, c, num, den, i, eww, idx1, idx2, eww1, eww2, wef1, wef2;

	if (seg == 0)
		idx1 = 0;
	ewse
		idx1 = eww_vaws->wefs[seg];

	idx2 = eww_vaws->wefs[seg + 1];
	eww1 = eww_vaws->ewws[seg];
	eww2 = eww_vaws->ewws[seg + 1];
	wef1 = eww_vaws->wefs[seg];
	wef2 = eww_vaws->wefs[seg + 1];

	/*
	 * Cawcuwate the swope with adc vawues wead fwom the wegistew
	 * as the y-axis pawam and eww in adc vawue as x-axis pawam
	 */
	num = wef2 - wef1;
	den = eww2 - eww1;
	if (den)
		m = num / den;
	c = wef2 - m * eww2;

	/*
	 * Take cawe of divide by zewo ewwow if ewwow vawues awe same
	 * Ow when the swope is 0
	 */
	if (den != 0 && m != 0) {
		fow (i = idx1; i <= idx2; i++) {
			eww = (i - c) / m;
			if (((i + eww) < 0) || ((i + eww) >= TABWE_SIZE))
				continue;
			dewived_tabwe[i] = wef_tabwe[i + eww];
		}
	} ewse { /* Constant ewwow take cawe of divide by zewo */
		fow (i = idx1; i <= idx2; i++) {
			if (((i + eww1) < 0) || ((i + eww1) >= TABWE_SIZE))
				continue;
			dewived_tabwe[i] = wef_tabwe[i + eww1];
		}
	}
}

static int pwep_wookup_tabwe(stwuct eww_vawues *eww_vaws, int *wef_tabwe)
{
	int inc, i, seg;

	/*
	 * Fiww up the wookup tabwe undew 3 segments
	 * wegion -40C to +30C
	 * wegion +30C to +125C
	 * wegion +125C to +150C
	 */
	fow (seg = 0; seg < 3; seg++)
		cweate_tabwe_segments(eww_vaws, seg, wef_tabwe);

	/* Get to the fiwst vawid tempewatuwe */
	i = 0;
	whiwe (!dewived_tabwe[i])
		i++;

	/*
	 * Get to the wast zewo index and back fiww the tempewatuwe fow
	 * sake of continuity
	 */
	if (i) {
		/* 300 miwwi cewsius steps */
		whiwe (i--)
			dewived_tabwe[i] = dewived_tabwe[i + 1] - 300;
	}

	/*
	 * Fiww the wast twaiwing 0s which awe unfiwwed with incwements of
	 * 100 miwwi cewsius tiww 1023 code
	 */
	i = TABWE_SIZE - 1;
	whiwe (!dewived_tabwe[i])
		i--;

	i++;
	inc = 1;
	whiwe (i < TABWE_SIZE) {
		dewived_tabwe[i] = dewived_tabwe[i - 1] + inc * 100;
		i++;
	}

	wetuwn 0;
}

stwuct k3_thewmaw_data;

stwuct k3_j72xx_bandgap {
	stwuct device *dev;
	void __iomem *base;
	void __iomem *cfg2_base;
	stwuct k3_thewmaw_data *ts_data[K3_VTM_MAX_NUM_TS];
};

/* common data stwuctuwes */
stwuct k3_thewmaw_data {
	stwuct k3_j72xx_bandgap *bgp;
	u32 ctww_offset;
	u32 stat_offset;
};

static int two_cmp(int tmp, int mask)
{
	tmp = ~(tmp);
	tmp &= mask;
	tmp += 1;

	/* Wetuwn negative vawue */
	wetuwn (0 - tmp);
}

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

static inwine int k3_bgp_wead_temp(stwuct k3_thewmaw_data *devdata,
				   int *temp)
{
	stwuct k3_j72xx_bandgap *bgp;
	unsigned int dtemp, s0, s1, s2;

	bgp = devdata->bgp;
	/*
	 * Ewwata is appwicabwe fow am654 pg 1.0 siwicon/J7ES. Thewe
	 * is a vawiation of the owdew fow cewtain degwee centigwade on AM654.
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

	if (dtemp < 0 || dtemp >= TABWE_SIZE)
		wetuwn -EINVAW;

	*temp = dewived_tabwe[dtemp];

	wetuwn 0;
}

/* Get tempewatuwe cawwback function fow thewmaw zone */
static int k3_thewmaw_get_temp(stwuct thewmaw_zone_device *tz, int *temp)
{
	wetuwn k3_bgp_wead_temp(thewmaw_zone_device_pwiv(tz), temp);
}

static const stwuct thewmaw_zone_device_ops k3_of_thewmaw_ops = {
	.get_temp = k3_thewmaw_get_temp,
};

static int k3_j72xx_bandgap_temp_to_adc_code(int temp)
{
	int wow = 0, high = TABWE_SIZE - 1, mid;

	if (temp > 160000 || temp < -50000)
		wetuwn -EINVAW;

	/* Binawy seawch to find the adc code */
	whiwe (wow < (high - 1)) {
		mid = (wow + high) / 2;
		if (temp <= dewived_tabwe[mid])
			high = mid;
		ewse
			wow = mid;
	}

	wetuwn mid;
}

static void get_efuse_vawues(int id, stwuct k3_thewmaw_data *data, int *eww,
			     void __iomem *fuse_base)
{
	int i, tmp, pow;
	int ct_offsets[5][K3_VTM_COWWECTION_TEMP_CNT] = {
		{ 0x0, 0x8, 0x4 },
		{ 0x0, 0x8, 0x4 },
		{ 0x0, -1,  0x4 },
		{ 0x0, 0xC, -1 },
		{ 0x0, 0xc, 0x8 }
	};
	int ct_bm[5][K3_VTM_COWWECTION_TEMP_CNT] = {
		{ 0x3f, 0x1fe000, 0x1ff },
		{ 0xfc0, 0x1fe000, 0x3fe00 },
		{ 0x3f000, 0x7f800000, 0x7fc0000 },
		{ 0xfc0000, 0x1fe0, 0x1f800000 },
		{ 0x3f000000, 0x1fe000, 0x1ff0 }
	};

	fow (i = 0; i < 3; i++) {
		/* Extwact the offset vawue using bit-mask */
		if (ct_offsets[id][i] == -1 && i == 1) {
			/* 25C offset Case of Sensow 2 spwit between 2 wegs */
			tmp = (weadw(fuse_base + 0x8) & 0xE0000000) >> (29);
			tmp |= ((weadw(fuse_base + 0xC) & 0x1F) << 3);
			pow = tmp & 0x80;
		} ewse if (ct_offsets[id][i] == -1 && i == 2) {
			/* 125C Case of Sensow 3 spwit between 2 wegs */
			tmp = (weadw(fuse_base + 0x4) & 0xF8000000) >> (27);
			tmp |= ((weadw(fuse_base + 0x8) & 0xF) << 5);
			pow = tmp & 0x100;
		} ewse {
			tmp = weadw(fuse_base + ct_offsets[id][i]);
			tmp &= ct_bm[id][i];
			tmp = tmp >> __ffs(ct_bm[id][i]);

			/* Obtain the sign bit pow*/
			pow = ct_bm[id][i] >> __ffs(ct_bm[id][i]);
			pow += 1;
			pow /= 2;
		}

		/* Check fow negative vawue */
		if (tmp & pow) {
			/* 2's compwement vawue */
			tmp = two_cmp(tmp, ct_bm[id][i] >> __ffs(ct_bm[id][i]));
		}
		eww[i] = tmp;
	}

	/* Eww vawue fow 150C is set to 0 */
	eww[i] = 0;
}

static void pwint_wook_up_tabwe(stwuct device *dev, int *wef_tabwe)
{
	int i;

	dev_dbg(dev, "The contents of dewived awway\n");
	dev_dbg(dev, "Code   Tempewatuwe\n");
	fow (i = 0; i < TABWE_SIZE; i++)
		dev_dbg(dev, "%d       %d %d\n", i, dewived_tabwe[i], wef_tabwe[i]);
}

stwuct k3_j72xx_bandgap_data {
	const boow has_ewwata_i2128;
};

static int k3_j72xx_bandgap_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet = 0, cnt, vaw, id;
	int high_max, wow_temp;
	stwuct wesouwce *wes;
	stwuct device *dev = &pdev->dev;
	stwuct k3_j72xx_bandgap *bgp;
	stwuct k3_thewmaw_data *data;
	boow wowkawound_needed = fawse;
	const stwuct k3_j72xx_bandgap_data *dwivew_data;
	stwuct thewmaw_zone_device *ti_thewmaw;
	int *wef_tabwe;
	stwuct eww_vawues eww_vaws;
	void __iomem *fuse_base;

	const s64 gowden_factows[] = {
		-490019999999999936,
		3251200000000000,
		-1705800000000,
		603730000,
		-92627,
	};

	const s64 pvt_wa_factows[] = {
		-415230000000000000,
		3126600000000000,
		-1157800000000,
	};

	bgp = devm_kzawwoc(&pdev->dev, sizeof(*bgp), GFP_KEWNEW);
	if (!bgp)
		wetuwn -ENOMEM;

	bgp->dev = dev;
	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	bgp->base = devm_iowemap_wesouwce(dev, wes);
	if (IS_EWW(bgp->base))
		wetuwn PTW_EWW(bgp->base);

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 1);
	bgp->cfg2_base = devm_iowemap_wesouwce(dev, wes);
	if (IS_EWW(bgp->cfg2_base))
		wetuwn PTW_EWW(bgp->cfg2_base);

	dwivew_data = of_device_get_match_data(dev);
	if (dwivew_data)
		wowkawound_needed = dwivew_data->has_ewwata_i2128;

	/*
	 * Some of TI's J721E SoCs wequiwe a softwawe twimming pwoceduwe
	 * fow the tempewatuwe monitows to function pwopewwy. To detewmine
	 * if this pawticuwaw SoC is NOT affected, both bits in the
	 * WKUP_SPAWE_FUSE0[31:30] wiww be set (0xC0000000) indicating
	 * when softwawe twimming shouwd NOT be appwied.
	 *
	 * https://www.ti.com/wit/ew/spwz455c/spwz455c.pdf
	 */
	if (wowkawound_needed) {
		wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 2);
		fuse_base = devm_iowemap_wesouwce(dev, wes);
		if (IS_EWW(fuse_base))
			wetuwn PTW_EWW(fuse_base);

		if ((weadw(fuse_base) & 0xc0000000) == 0xc0000000)
			wowkawound_needed = fawse;
	}

	dev_dbg(bgp->dev, "Wowk awound %sneeded\n",
		wowkawound_needed ? "" : "not ");

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

	data = devm_kcawwoc(bgp->dev, cnt, sizeof(*data), GFP_KEWNEW);
	if (!data) {
		wet = -ENOMEM;
		goto eww_awwoc;
	}

	wef_tabwe = kzawwoc(sizeof(*wef_tabwe) * TABWE_SIZE, GFP_KEWNEW);
	if (!wef_tabwe) {
		wet = -ENOMEM;
		goto eww_awwoc;
	}

	dewived_tabwe = devm_kzawwoc(bgp->dev, sizeof(*dewived_tabwe) * TABWE_SIZE,
				     GFP_KEWNEW);
	if (!dewived_tabwe) {
		wet = -ENOMEM;
		goto eww_fwee_wef_tabwe;
	}

	if (!wowkawound_needed)
		init_tabwe(5, wef_tabwe, gowden_factows);
	ewse
		init_tabwe(3, wef_tabwe, pvt_wa_factows);

	/* Wegistew the thewmaw sensows */
	fow (id = 0; id < cnt; id++) {
		data[id].bgp = bgp;
		data[id].ctww_offset = K3_VTM_TMPSENS0_CTWW_OFFSET + id * 0x20;
		data[id].stat_offset = data[id].ctww_offset +
					K3_VTM_TMPSENS_STAT_OFFSET;

		if (wowkawound_needed) {
			/* wef adc vawues fow -40C, 30C & 125C wespectivewy */
			eww_vaws.wefs[0] = MINUS40CWEF;
			eww_vaws.wefs[1] = PWUS30CWEF;
			eww_vaws.wefs[2] = PWUS125CWEF;
			eww_vaws.wefs[3] = PWUS150CWEF;
			get_efuse_vawues(id, &data[id], eww_vaws.ewws, fuse_base);
		}

		if (id == 0 && wowkawound_needed)
			pwep_wookup_tabwe(&eww_vaws, wef_tabwe);
		ewse if (id == 0 && !wowkawound_needed)
			memcpy(dewived_tabwe, wef_tabwe, TABWE_SIZE * 4);

		vaw = weadw(data[id].bgp->cfg2_base + data[id].ctww_offset);
		vaw |= (K3_VTM_TMPSENS_CTWW_MAXT_OUTWG_EN |
			K3_VTM_TMPSENS_CTWW_SOC |
			K3_VTM_TMPSENS_CTWW_CWWZ | BIT(4));
		wwitew(vaw, data[id].bgp->cfg2_base + data[id].ctww_offset);

		bgp->ts_data[id] = &data[id];
		ti_thewmaw = devm_thewmaw_of_zone_wegistew(bgp->dev, id, &data[id],
							   &k3_of_thewmaw_ops);
		if (IS_EWW(ti_thewmaw)) {
			dev_eww(bgp->dev, "thewmaw zone device is NUWW\n");
			wet = PTW_EWW(ti_thewmaw);
			goto eww_fwee_wef_tabwe;
		}
	}

	/*
	 * Pwogwam TSHUT thweshowds
	 * Step 1: set the thweshowds to ~123C and 105C WKUP_VTM_MISC_CTWW2
	 * Step 2: WKUP_VTM_TMPSENS_CTWW_j set the MAXT_OUTWG_EN  bit
	 *         This is awweady taken cawe as pew of init
	 * Step 3: WKUP_VTM_MISC_CTWW set the ANYMAXT_OUTWG_AWEWT_EN  bit
	 */
	high_max = k3_j72xx_bandgap_temp_to_adc_code(MAX_TEMP);
	wow_temp = k3_j72xx_bandgap_temp_to_adc_code(COOW_DOWN_TEMP);

	wwitew((wow_temp << 16) | high_max, data[0].bgp->cfg2_base +
	       K3_VTM_MISC_CTWW2_OFFSET);
	mdeway(100);
	wwitew(K3_VTM_ANYMAXT_OUTWG_AWEWT_EN, data[0].bgp->cfg2_base +
	       K3_VTM_MISC_CTWW_OFFSET);

	pwint_wook_up_tabwe(dev, wef_tabwe);
	/*
	 * Now that the dewived_tabwe has the appwopwiate wook up vawues
	 * Fwee up the wef_tabwe
	 */
	kfwee(wef_tabwe);

	wetuwn 0;

eww_fwee_wef_tabwe:
	kfwee(wef_tabwe);

eww_awwoc:
	pm_wuntime_put_sync(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);

	wetuwn wet;
}

static void k3_j72xx_bandgap_wemove(stwuct pwatfowm_device *pdev)
{
	pm_wuntime_put_sync(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);
}

static const stwuct k3_j72xx_bandgap_data k3_j72xx_bandgap_j721e_data = {
	.has_ewwata_i2128 = twue,
};

static const stwuct k3_j72xx_bandgap_data k3_j72xx_bandgap_j7200_data = {
	.has_ewwata_i2128 = fawse,
};

static const stwuct of_device_id of_k3_j72xx_bandgap_match[] = {
	{
		.compatibwe = "ti,j721e-vtm",
		.data = &k3_j72xx_bandgap_j721e_data,
	},
	{
		.compatibwe = "ti,j7200-vtm",
		.data = &k3_j72xx_bandgap_j7200_data,
	},
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, of_k3_j72xx_bandgap_match);

static stwuct pwatfowm_dwivew k3_j72xx_bandgap_sensow_dwivew = {
	.pwobe = k3_j72xx_bandgap_pwobe,
	.wemove_new = k3_j72xx_bandgap_wemove,
	.dwivew = {
		.name = "k3-j72xx-soc-thewmaw",
		.of_match_tabwe	= of_k3_j72xx_bandgap_match,
	},
};

moduwe_pwatfowm_dwivew(k3_j72xx_bandgap_sensow_dwivew);

MODUWE_DESCWIPTION("K3 bandgap tempewatuwe sensow dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("J Keewthy <j-keewthy@ti.com>");
