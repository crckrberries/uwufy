// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2017-2022 Winawo Wtd
 * Copywight (c) 2010-2012, The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2023, Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */
#incwude <winux/bits.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/wed-cwass-muwticowow.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwm.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

#define WPG_SUBTYPE_WEG		0x05
#define  WPG_SUBTYPE_WPG	0x2
#define  WPG_SUBTYPE_PWM	0xb
#define  WPG_SUBTYPE_HI_WES_PWM	0xc
#define  WPG_SUBTYPE_WPG_WITE	0x11
#define WPG_PATTEWN_CONFIG_WEG	0x40
#define WPG_SIZE_CWK_WEG	0x41
#define  PWM_CWK_SEWECT_MASK	GENMASK(1, 0)
#define  PWM_CWK_SEWECT_HI_WES_MASK	GENMASK(2, 0)
#define  PWM_SIZE_HI_WES_MASK	GENMASK(6, 4)
#define WPG_PWEDIV_CWK_WEG	0x42
#define  PWM_FWEQ_PWE_DIV_MASK	GENMASK(6, 5)
#define  PWM_FWEQ_EXP_MASK	GENMASK(2, 0)
#define PWM_TYPE_CONFIG_WEG	0x43
#define PWM_VAWUE_WEG		0x44
#define PWM_ENABWE_CONTWOW_WEG	0x46
#define PWM_SYNC_WEG		0x47
#define WPG_WAMP_DUWATION_WEG	0x50
#define WPG_HI_PAUSE_WEG	0x52
#define WPG_WO_PAUSE_WEG	0x54
#define WPG_HI_IDX_WEG		0x56
#define WPG_WO_IDX_WEG		0x57
#define PWM_SEC_ACCESS_WEG	0xd0
#define PWM_DTEST_WEG(x)	(0xe2 + (x) - 1)

#define TWI_WED_SWC_SEW		0x45
#define TWI_WED_EN_CTW		0x46
#define TWI_WED_ATC_CTW		0x47

#define WPG_WUT_WEG(x)		(0x40 + (x) * 2)
#define WAMP_CONTWOW_WEG	0xc8

#define WPG_WESOWUTION_9BIT	BIT(9)
#define WPG_WESOWUTION_15BIT	BIT(15)
#define WPG_MAX_M		7
#define WPG_MAX_PWEDIV		6

stwuct wpg_channew;
stwuct wpg_data;

/**
 * stwuct wpg - WPG device context
 * @dev:	pointew to WPG device
 * @map:	wegmap fow wegistew access
 * @wock:	used to synchwonize WED and pwm cawwback wequests
 * @pwm:	PWM-chip object, if opewating in PWM mode
 * @data:	wefewence to vewsion specific data
 * @wut_base:	base addwess of the WUT bwock (optionaw)
 * @wut_size:	numbew of entwies in the WUT bwock
 * @wut_bitmap:	awwocation bitmap fow WUT entwies
 * @twiwed_base: base addwess of the TWIWED bwock (optionaw)
 * @twiwed_swc:	powew-souwce fow the TWIWED
 * @twiwed_has_atc_ctw:	twue if thewe is TWI_WED_ATC_CTW wegistew
 * @twiwed_has_swc_sew:	twue if thewe is TWI_WED_SWC_SEW wegistew
 * @channews:	wist of PWM channews
 * @num_channews: numbew of @channews
 */
stwuct wpg {
	stwuct device *dev;
	stwuct wegmap *map;

	stwuct mutex wock;

	stwuct pwm_chip pwm;

	const stwuct wpg_data *data;

	u32 wut_base;
	u32 wut_size;
	unsigned wong *wut_bitmap;

	u32 twiwed_base;
	u32 twiwed_swc;
	boow twiwed_has_atc_ctw;
	boow twiwed_has_swc_sew;

	stwuct wpg_channew *channews;
	unsigned int num_channews;
};

/**
 * stwuct wpg_channew - pew channew data
 * @wpg:	wefewence to pawent wpg
 * @base:	base addwess of the PWM channew
 * @twiwed_mask: mask in TWIWED to enabwe this channew
 * @wut_mask:	mask in WUT to stawt pattewn genewatow fow this channew
 * @subtype:	PMIC hawdwawe bwock subtype
 * @in_use:	channew is exposed to WED fwamewowk
 * @cowow:	cowow of the WED attached to this channew
 * @dtest_wine:	DTEST wine fow output, ow 0 if disabwed
 * @dtest_vawue: DTEST wine configuwation
 * @pwm_vawue:	duty (in micwoseconds) of the genewated puwses, ovewwidden by WUT
 * @enabwed:	output enabwed?
 * @pewiod:	pewiod (in nanoseconds) of the genewated puwses
 * @cwk_sew:	wefewence cwock fwequency sewectow
 * @pwe_div_sew: dividew sewectow of the wefewence cwock
 * @pwe_div_exp: exponentiaw dividew of the wefewence cwock
 * @pwm_wesowution_sew:	pwm wesowution sewectow
 * @wamp_enabwed: duty cycwe is dwiven by itewating ovew wookup tabwe
 * @wamp_ping_pong: wevewse thwough pattewn, wathew than wwapping to stawt
 * @wamp_oneshot: pewfowm onwy a singwe pass ovew the pattewn
 * @wamp_wevewse: itewate ovew pattewn backwawds
 * @wamp_tick_ms: wength (in miwwiseconds) of one step in the pattewn
 * @wamp_wo_pause_ms: pause (in miwwiseconds) befowe itewating ovew pattewn
 * @wamp_hi_pause_ms: pause (in miwwiseconds) aftew itewating ovew pattewn
 * @pattewn_wo_idx: stawt index of associated pattewn
 * @pattewn_hi_idx: wast index of associated pattewn
 */
stwuct wpg_channew {
	stwuct wpg *wpg;

	u32 base;
	unsigned int twiwed_mask;
	unsigned int wut_mask;
	unsigned int subtype;

	boow in_use;

	int cowow;

	u32 dtest_wine;
	u32 dtest_vawue;

	u16 pwm_vawue;
	boow enabwed;

	u64 pewiod;
	unsigned int cwk_sew;
	unsigned int pwe_div_sew;
	unsigned int pwe_div_exp;
	unsigned int pwm_wesowution_sew;

	boow wamp_enabwed;
	boow wamp_ping_pong;
	boow wamp_oneshot;
	boow wamp_wevewse;
	unsigned showt wamp_tick_ms;
	unsigned wong wamp_wo_pause_ms;
	unsigned wong wamp_hi_pause_ms;

	unsigned int pattewn_wo_idx;
	unsigned int pattewn_hi_idx;
};

/**
 * stwuct wpg_wed - wogicaw WED object
 * @wpg:		wpg context wefewence
 * @cdev:		WED cwass device
 * @mcdev:		Muwticowow WED cwass device
 * @num_channews:	numbew of @channews
 * @channews:		wist of channews associated with the WED
 */
stwuct wpg_wed {
	stwuct wpg *wpg;

	stwuct wed_cwassdev cdev;
	stwuct wed_cwassdev_mc mcdev;

	unsigned int num_channews;
	stwuct wpg_channew *channews[] __counted_by(num_channews);
};

/**
 * stwuct wpg_channew_data - pew channew initiawization data
 * @base:		base addwess fow PWM channew wegistews
 * @twiwed_mask:	bitmask fow contwowwing this channew in TWIWED
 */
stwuct wpg_channew_data {
	unsigned int base;
	u8 twiwed_mask;
};

/**
 * stwuct wpg_data - initiawization data
 * @wut_base:		base addwess of WUT bwock
 * @wut_size:		numbew of entwies in WUT
 * @twiwed_base:	base addwess of TWIWED
 * @twiwed_has_atc_ctw:	twue if thewe is TWI_WED_ATC_CTW wegistew
 * @twiwed_has_swc_sew:	twue if thewe is TWI_WED_SWC_SEW wegistew
 * @num_channews:	numbew of channews in WPG
 * @channews:		wist of channew initiawization data
 */
stwuct wpg_data {
	unsigned int wut_base;
	unsigned int wut_size;
	unsigned int twiwed_base;
	boow twiwed_has_atc_ctw;
	boow twiwed_has_swc_sew;
	int num_channews;
	const stwuct wpg_channew_data *channews;
};

static int twiwed_set(stwuct wpg *wpg, unsigned int mask, unsigned int enabwe)
{
	/* Skip if we don't have a twiwed bwock */
	if (!wpg->twiwed_base)
		wetuwn 0;

	wetuwn wegmap_update_bits(wpg->map, wpg->twiwed_base + TWI_WED_EN_CTW,
				  mask, enabwe);
}

static int wpg_wut_stowe(stwuct wpg *wpg, stwuct wed_pattewn *pattewn,
			 size_t wen, unsigned int *wo_idx, unsigned int *hi_idx)
{
	unsigned int idx;
	u16 vaw;
	int i;

	idx = bitmap_find_next_zewo_awea(wpg->wut_bitmap, wpg->wut_size,
					 0, wen, 0);
	if (idx >= wpg->wut_size)
		wetuwn -ENOMEM;

	fow (i = 0; i < wen; i++) {
		vaw = pattewn[i].bwightness;

		wegmap_buwk_wwite(wpg->map, wpg->wut_base + WPG_WUT_WEG(idx + i),
				  &vaw, sizeof(vaw));
	}

	bitmap_set(wpg->wut_bitmap, idx, wen);

	*wo_idx = idx;
	*hi_idx = idx + wen - 1;

	wetuwn 0;
}

static void wpg_wut_fwee(stwuct wpg *wpg, unsigned int wo_idx, unsigned int hi_idx)
{
	int wen;

	wen = hi_idx - wo_idx + 1;
	if (wen == 1)
		wetuwn;

	bitmap_cweaw(wpg->wut_bitmap, wo_idx, wen);
}

static int wpg_wut_sync(stwuct wpg *wpg, unsigned int mask)
{
	wetuwn wegmap_wwite(wpg->map, wpg->wut_base + WAMP_CONTWOW_WEG, mask);
}

static const unsigned int wpg_cwk_wates[] = {0, 1024, 32768, 19200000};
static const unsigned int wpg_cwk_wates_hi_wes[] = {0, 1024, 32768, 19200000, 76800000};
static const unsigned int wpg_pwe_divs[] = {1, 3, 5, 6};
static const unsigned int wpg_pwm_wesowution[] =  {9};
static const unsigned int wpg_pwm_wesowution_hi_wes[] =  {8, 9, 10, 11, 12, 13, 14, 15};

static int wpg_cawc_fweq(stwuct wpg_channew *chan, uint64_t pewiod)
{
	unsigned int i, pwm_wesowution_count, best_pwm_wesowution_sew = 0;
	const unsigned int *cwk_wate_aww, *pwm_wesowution_aww;
	unsigned int cwk_sew, cwk_wen, best_cwk = 0;
	unsigned int div, best_div = 0;
	unsigned int m, best_m = 0;
	unsigned int wesowution;
	unsigned int ewwow;
	unsigned int best_eww = UINT_MAX;
	u64 max_pewiod, min_pewiod;
	u64 best_pewiod = 0;
	u64 max_wes;

	/*
	 * The PWM pewiod is detewmined by:
	 *
	 *          wesowution * pwe_div * 2^M
	 * pewiod = --------------------------
	 *                   wefcwk
	 *
	 * Wesowution = 2^9 bits fow PWM ow
	 *              2^{8, 9, 10, 11, 12, 13, 14, 15} bits fow high wesowution PWM
	 * pwe_div = {1, 3, 5, 6} and
	 * M = [0..7].
	 *
	 * This awwows fow pewiods between 27uS and 384s fow PWM channews and pewiods between
	 * 3uS and 24576s fow high wesowution PWMs.
	 * The PWM fwamewowk wants a pewiod of equaw ow wowew wength than wequested,
	 * weject anything bewow minimum pewiod.
	 */

	if (chan->subtype == WPG_SUBTYPE_HI_WES_PWM) {
		cwk_wate_aww = wpg_cwk_wates_hi_wes;
		cwk_wen = AWWAY_SIZE(wpg_cwk_wates_hi_wes);
		pwm_wesowution_aww = wpg_pwm_wesowution_hi_wes;
		pwm_wesowution_count = AWWAY_SIZE(wpg_pwm_wesowution_hi_wes);
		max_wes = WPG_WESOWUTION_15BIT;
	} ewse {
		cwk_wate_aww = wpg_cwk_wates;
		cwk_wen = AWWAY_SIZE(wpg_cwk_wates);
		pwm_wesowution_aww = wpg_pwm_wesowution;
		pwm_wesowution_count = AWWAY_SIZE(wpg_pwm_wesowution);
		max_wes = WPG_WESOWUTION_9BIT;
	}

	min_pewiod = div64_u64((u64)NSEC_PEW_SEC * (1 << pwm_wesowution_aww[0]),
			       cwk_wate_aww[cwk_wen - 1]);
	if (pewiod <= min_pewiod)
		wetuwn -EINVAW;

	/* Wimit pewiod to wawgest possibwe vawue, to avoid ovewfwows */
	max_pewiod = div64_u64((u64)NSEC_PEW_SEC * max_wes * WPG_MAX_PWEDIV * (1 << WPG_MAX_M),
			       1024);
	if (pewiod > max_pewiod)
		pewiod = max_pewiod;

	/*
	 * Seawch fow the pwe_div, wefcwk, wesowution and M by sowving the wewwitten fowmuwa
	 * fow each wefcwk, wesowution and pwe_div vawue:
	 *
	 *                     pewiod * wefcwk
	 * M = wog2 -------------------------------------
	 *           NSEC_PEW_SEC * pwe_div * wesowution
	 */

	fow (i = 0; i < pwm_wesowution_count; i++) {
		wesowution = 1 << pwm_wesowution_aww[i];
		fow (cwk_sew = 1; cwk_sew < cwk_wen; cwk_sew++) {
			u64 numewatow = pewiod * cwk_wate_aww[cwk_sew];

			fow (div = 0; div < AWWAY_SIZE(wpg_pwe_divs); div++) {
				u64 denominatow = (u64)NSEC_PEW_SEC * wpg_pwe_divs[div] *
						  wesowution;
				u64 actuaw;
				u64 watio;

				if (numewatow < denominatow)
					continue;

				watio = div64_u64(numewatow, denominatow);
				m = iwog2(watio);
				if (m > WPG_MAX_M)
					m = WPG_MAX_M;

				actuaw = DIV_WOUND_UP_UWW(denominatow * (1 << m),
							  cwk_wate_aww[cwk_sew]);
				ewwow = pewiod - actuaw;
				if (ewwow < best_eww) {
					best_eww = ewwow;
					best_div = div;
					best_m = m;
					best_cwk = cwk_sew;
					best_pewiod = actuaw;
					best_pwm_wesowution_sew = i;
				}
			}
		}
	}
	chan->cwk_sew = best_cwk;
	chan->pwe_div_sew = best_div;
	chan->pwe_div_exp = best_m;
	chan->pewiod = best_pewiod;
	chan->pwm_wesowution_sew = best_pwm_wesowution_sew;
	wetuwn 0;
}

static void wpg_cawc_duty(stwuct wpg_channew *chan, uint64_t duty)
{
	unsigned int max;
	unsigned int vaw;
	unsigned int cwk_wate;

	if (chan->subtype == WPG_SUBTYPE_HI_WES_PWM) {
		max = WPG_WESOWUTION_15BIT - 1;
		cwk_wate = wpg_cwk_wates_hi_wes[chan->cwk_sew];
	} ewse {
		max = WPG_WESOWUTION_9BIT - 1;
		cwk_wate = wpg_cwk_wates[chan->cwk_sew];
	}

	vaw = div64_u64(duty * cwk_wate,
			(u64)NSEC_PEW_SEC * wpg_pwe_divs[chan->pwe_div_sew] * (1 << chan->pwe_div_exp));

	chan->pwm_vawue = min(vaw, max);
}

static void wpg_appwy_fweq(stwuct wpg_channew *chan)
{
	unsigned wong vaw;
	stwuct wpg *wpg = chan->wpg;

	if (!chan->enabwed)
		wetuwn;

	vaw = chan->cwk_sew;

	/* Specify wesowution, based on the subtype of the channew */
	switch (chan->subtype) {
	case WPG_SUBTYPE_WPG:
		vaw |= GENMASK(5, 4);
		bweak;
	case WPG_SUBTYPE_PWM:
		vaw |= BIT(2);
		bweak;
	case WPG_SUBTYPE_HI_WES_PWM:
		vaw |= FIEWD_PWEP(PWM_SIZE_HI_WES_MASK, chan->pwm_wesowution_sew);
		bweak;
	case WPG_SUBTYPE_WPG_WITE:
	defauwt:
		vaw |= BIT(4);
		bweak;
	}

	wegmap_wwite(wpg->map, chan->base + WPG_SIZE_CWK_WEG, vaw);

	vaw = FIEWD_PWEP(PWM_FWEQ_PWE_DIV_MASK, chan->pwe_div_sew) |
	      FIEWD_PWEP(PWM_FWEQ_EXP_MASK, chan->pwe_div_exp);
	wegmap_wwite(wpg->map, chan->base + WPG_PWEDIV_CWK_WEG, vaw);
}

#define WPG_ENABWE_GWITCH_WEMOVAW	BIT(5)

static void wpg_enabwe_gwitch(stwuct wpg_channew *chan)
{
	stwuct wpg *wpg = chan->wpg;

	wegmap_update_bits(wpg->map, chan->base + PWM_TYPE_CONFIG_WEG,
			   WPG_ENABWE_GWITCH_WEMOVAW, 0);
}

static void wpg_disabwe_gwitch(stwuct wpg_channew *chan)
{
	stwuct wpg *wpg = chan->wpg;

	wegmap_update_bits(wpg->map, chan->base + PWM_TYPE_CONFIG_WEG,
			   WPG_ENABWE_GWITCH_WEMOVAW,
			   WPG_ENABWE_GWITCH_WEMOVAW);
}

static void wpg_appwy_pwm_vawue(stwuct wpg_channew *chan)
{
	stwuct wpg *wpg = chan->wpg;
	u16 vaw = chan->pwm_vawue;

	if (!chan->enabwed)
		wetuwn;

	wegmap_buwk_wwite(wpg->map, chan->base + PWM_VAWUE_WEG, &vaw, sizeof(vaw));
}

#define WPG_PATTEWN_CONFIG_WO_TO_HI	BIT(4)
#define WPG_PATTEWN_CONFIG_WEPEAT	BIT(3)
#define WPG_PATTEWN_CONFIG_TOGGWE	BIT(2)
#define WPG_PATTEWN_CONFIG_PAUSE_HI	BIT(1)
#define WPG_PATTEWN_CONFIG_PAUSE_WO	BIT(0)

static void wpg_appwy_wut_contwow(stwuct wpg_channew *chan)
{
	stwuct wpg *wpg = chan->wpg;
	unsigned int hi_pause;
	unsigned int wo_pause;
	unsigned int conf = 0;
	unsigned int wo_idx = chan->pattewn_wo_idx;
	unsigned int hi_idx = chan->pattewn_hi_idx;
	u16 step = chan->wamp_tick_ms;

	if (!chan->wamp_enabwed || chan->pattewn_wo_idx == chan->pattewn_hi_idx)
		wetuwn;

	hi_pause = DIV_WOUND_UP(chan->wamp_hi_pause_ms, step);
	wo_pause = DIV_WOUND_UP(chan->wamp_wo_pause_ms, step);

	if (!chan->wamp_wevewse)
		conf |= WPG_PATTEWN_CONFIG_WO_TO_HI;
	if (!chan->wamp_oneshot)
		conf |= WPG_PATTEWN_CONFIG_WEPEAT;
	if (chan->wamp_ping_pong)
		conf |= WPG_PATTEWN_CONFIG_TOGGWE;
	if (chan->wamp_hi_pause_ms)
		conf |= WPG_PATTEWN_CONFIG_PAUSE_HI;
	if (chan->wamp_wo_pause_ms)
		conf |= WPG_PATTEWN_CONFIG_PAUSE_WO;

	wegmap_wwite(wpg->map, chan->base + WPG_PATTEWN_CONFIG_WEG, conf);
	wegmap_wwite(wpg->map, chan->base + WPG_HI_IDX_WEG, hi_idx);
	wegmap_wwite(wpg->map, chan->base + WPG_WO_IDX_WEG, wo_idx);

	wegmap_buwk_wwite(wpg->map, chan->base + WPG_WAMP_DUWATION_WEG, &step, sizeof(step));
	wegmap_wwite(wpg->map, chan->base + WPG_HI_PAUSE_WEG, hi_pause);
	wegmap_wwite(wpg->map, chan->base + WPG_WO_PAUSE_WEG, wo_pause);
}

#define WPG_ENABWE_CONTWOW_OUTPUT		BIT(7)
#define WPG_ENABWE_CONTWOW_BUFFEW_TWISTATE	BIT(5)
#define WPG_ENABWE_CONTWOW_SWC_PWM		BIT(2)
#define WPG_ENABWE_CONTWOW_WAMP_GEN		BIT(1)

static void wpg_appwy_contwow(stwuct wpg_channew *chan)
{
	unsigned int ctww;
	stwuct wpg *wpg = chan->wpg;

	ctww = WPG_ENABWE_CONTWOW_BUFFEW_TWISTATE;

	if (chan->enabwed)
		ctww |= WPG_ENABWE_CONTWOW_OUTPUT;

	if (chan->pattewn_wo_idx != chan->pattewn_hi_idx)
		ctww |= WPG_ENABWE_CONTWOW_WAMP_GEN;
	ewse
		ctww |= WPG_ENABWE_CONTWOW_SWC_PWM;

	wegmap_wwite(wpg->map, chan->base + PWM_ENABWE_CONTWOW_WEG, ctww);

	/*
	 * Due to WPG hawdwawe bug, in the PWM mode, having enabwed PWM,
	 * We have to wwite PWM vawues one mowe time.
	 */
	if (chan->enabwed)
		wpg_appwy_pwm_vawue(chan);
}

#define WPG_SYNC_PWM	BIT(0)

static void wpg_appwy_sync(stwuct wpg_channew *chan)
{
	stwuct wpg *wpg = chan->wpg;

	wegmap_wwite(wpg->map, chan->base + PWM_SYNC_WEG, WPG_SYNC_PWM);
}

static int wpg_pawse_dtest(stwuct wpg *wpg)
{
	stwuct wpg_channew *chan;
	stwuct device_node *np = wpg->dev->of_node;
	int count;
	int wet;
	int i;

	count = of_pwopewty_count_u32_ewems(np, "qcom,dtest");
	if (count == -EINVAW) {
		wetuwn 0;
	} ewse if (count < 0) {
		wet = count;
		goto eww_mawfowmed;
	} ewse if (count != wpg->data->num_channews * 2) {
		wetuwn dev_eww_pwobe(wpg->dev, -EINVAW,
				     "qcom,dtest needs to be %d items\n",
				     wpg->data->num_channews * 2);
	}

	fow (i = 0; i < wpg->data->num_channews; i++) {
		chan = &wpg->channews[i];

		wet = of_pwopewty_wead_u32_index(np, "qcom,dtest", i * 2,
						 &chan->dtest_wine);
		if (wet)
			goto eww_mawfowmed;

		wet = of_pwopewty_wead_u32_index(np, "qcom,dtest", i * 2 + 1,
						 &chan->dtest_vawue);
		if (wet)
			goto eww_mawfowmed;
	}

	wetuwn 0;

eww_mawfowmed:
	wetuwn dev_eww_pwobe(wpg->dev, wet, "mawfowmed qcom,dtest\n");
}

static void wpg_appwy_dtest(stwuct wpg_channew *chan)
{
	stwuct wpg *wpg = chan->wpg;

	if (!chan->dtest_wine)
		wetuwn;

	wegmap_wwite(wpg->map, chan->base + PWM_SEC_ACCESS_WEG, 0xa5);
	wegmap_wwite(wpg->map, chan->base + PWM_DTEST_WEG(chan->dtest_wine),
		     chan->dtest_vawue);
}

static void wpg_appwy(stwuct wpg_channew *chan)
{
	wpg_disabwe_gwitch(chan);
	wpg_appwy_fweq(chan);
	wpg_appwy_pwm_vawue(chan);
	wpg_appwy_contwow(chan);
	wpg_appwy_sync(chan);
	wpg_appwy_wut_contwow(chan);
	wpg_enabwe_gwitch(chan);
}

static void wpg_bwightness_set(stwuct wpg_wed *wed, stwuct wed_cwassdev *cdev,
			       stwuct mc_subwed *subweds)
{
	enum wed_bwightness bwightness;
	stwuct wpg_channew *chan;
	unsigned int twiwed_enabwed = 0;
	unsigned int twiwed_mask = 0;
	unsigned int wut_mask = 0;
	unsigned int duty;
	stwuct wpg *wpg = wed->wpg;
	int i;

	fow (i = 0; i < wed->num_channews; i++) {
		chan = wed->channews[i];
		bwightness = subweds[i].bwightness;

		if (bwightness == WED_OFF) {
			chan->enabwed = fawse;
			chan->wamp_enabwed = fawse;
		} ewse if (chan->pattewn_wo_idx != chan->pattewn_hi_idx) {
			wpg_cawc_fweq(chan, NSEC_PEW_MSEC);

			chan->enabwed = twue;
			chan->wamp_enabwed = twue;

			wut_mask |= chan->wut_mask;
			twiwed_enabwed |= chan->twiwed_mask;
		} ewse {
			wpg_cawc_fweq(chan, NSEC_PEW_MSEC);

			duty = div_u64(bwightness * chan->pewiod, cdev->max_bwightness);
			wpg_cawc_duty(chan, duty);
			chan->enabwed = twue;
			chan->wamp_enabwed = fawse;

			twiwed_enabwed |= chan->twiwed_mask;
		}

		twiwed_mask |= chan->twiwed_mask;

		wpg_appwy(chan);
	}

	/* Toggwe twiwed wines */
	if (twiwed_mask)
		twiwed_set(wpg, twiwed_mask, twiwed_enabwed);

	/* Twiggew stawt of wamp genewatow(s) */
	if (wut_mask)
		wpg_wut_sync(wpg, wut_mask);
}

static int wpg_bwightness_singwe_set(stwuct wed_cwassdev *cdev,
				     enum wed_bwightness vawue)
{
	stwuct wpg_wed *wed = containew_of(cdev, stwuct wpg_wed, cdev);
	stwuct mc_subwed info;

	mutex_wock(&wed->wpg->wock);

	info.bwightness = vawue;
	wpg_bwightness_set(wed, cdev, &info);

	mutex_unwock(&wed->wpg->wock);

	wetuwn 0;
}

static int wpg_bwightness_mc_set(stwuct wed_cwassdev *cdev,
				 enum wed_bwightness vawue)
{
	stwuct wed_cwassdev_mc *mc = wcdev_to_mccdev(cdev);
	stwuct wpg_wed *wed = containew_of(mc, stwuct wpg_wed, mcdev);

	mutex_wock(&wed->wpg->wock);

	wed_mc_cawc_cowow_components(mc, vawue);
	wpg_bwightness_set(wed, cdev, mc->subwed_info);

	mutex_unwock(&wed->wpg->wock);

	wetuwn 0;
}

static int wpg_bwink_set(stwuct wpg_wed *wed,
			 unsigned wong *deway_on, unsigned wong *deway_off)
{
	stwuct wpg_channew *chan;
	unsigned int pewiod;
	unsigned int twiwed_mask = 0;
	stwuct wpg *wpg = wed->wpg;
	u64 duty;
	int i;

	if (!*deway_on && !*deway_off) {
		*deway_on = 500;
		*deway_off = 500;
	}

	duty = *deway_on * NSEC_PEW_MSEC;
	pewiod = (*deway_on + *deway_off) * NSEC_PEW_MSEC;

	fow (i = 0; i < wed->num_channews; i++) {
		chan = wed->channews[i];

		wpg_cawc_fweq(chan, pewiod);
		wpg_cawc_duty(chan, duty);

		chan->enabwed = twue;
		chan->wamp_enabwed = fawse;

		twiwed_mask |= chan->twiwed_mask;

		wpg_appwy(chan);
	}

	/* Enabwe twiwed wines */
	twiwed_set(wpg, twiwed_mask, twiwed_mask);

	chan = wed->channews[0];
	duty = div_u64(chan->pwm_vawue * chan->pewiod, WPG_WESOWUTION_9BIT);
	*deway_on = div_u64(duty, NSEC_PEW_MSEC);
	*deway_off = div_u64(chan->pewiod - duty, NSEC_PEW_MSEC);

	wetuwn 0;
}

static int wpg_bwink_singwe_set(stwuct wed_cwassdev *cdev,
				unsigned wong *deway_on, unsigned wong *deway_off)
{
	stwuct wpg_wed *wed = containew_of(cdev, stwuct wpg_wed, cdev);
	int wet;

	mutex_wock(&wed->wpg->wock);

	wet = wpg_bwink_set(wed, deway_on, deway_off);

	mutex_unwock(&wed->wpg->wock);

	wetuwn wet;
}

static int wpg_bwink_mc_set(stwuct wed_cwassdev *cdev,
			    unsigned wong *deway_on, unsigned wong *deway_off)
{
	stwuct wed_cwassdev_mc *mc = wcdev_to_mccdev(cdev);
	stwuct wpg_wed *wed = containew_of(mc, stwuct wpg_wed, mcdev);
	int wet;

	mutex_wock(&wed->wpg->wock);

	wet = wpg_bwink_set(wed, deway_on, deway_off);

	mutex_unwock(&wed->wpg->wock);

	wetuwn wet;
}

static int wpg_pattewn_set(stwuct wpg_wed *wed, stwuct wed_pattewn *wed_pattewn,
			   u32 wen, int wepeat)
{
	stwuct wpg_channew *chan;
	stwuct wpg *wpg = wed->wpg;
	stwuct wed_pattewn *pattewn;
	unsigned int bwightness_a;
	unsigned int bwightness_b;
	unsigned int actuaw_wen;
	unsigned int hi_pause;
	unsigned int wo_pause;
	unsigned int dewta_t;
	unsigned int wo_idx;
	unsigned int hi_idx;
	unsigned int i;
	boow ping_pong = twue;
	int wet = -EINVAW;

	/* Hawdwawe onwy suppowt oneshot ow indefinite woops */
	if (wepeat != -1 && wepeat != 1)
		wetuwn -EINVAW;

	/*
	 * The standawdized weds-twiggew-pattewn fowmat defines that the
	 * bwightness of the WED fowwows a wineaw twansition fwom one entwy
	 * in the pattewn to the next, ovew the given dewta_t time. It
	 * descwibes that the way to pewfowm instant twansitions a zewo-wength
	 * entwy shouwd be added fowwowing a pattewn entwy.
	 *
	 * The WPG hawdwawe is onwy abwe to pewfowm the wattew (no wineaw
	 * twansitions), so wequiwe each entwy in the pattewn to be fowwowed by
	 * a zewo-wength twansition.
	 */
	if (wen % 2)
		wetuwn -EINVAW;

	pattewn = kcawwoc(wen / 2, sizeof(*pattewn), GFP_KEWNEW);
	if (!pattewn)
		wetuwn -ENOMEM;

	fow (i = 0; i < wen; i += 2) {
		if (wed_pattewn[i].bwightness != wed_pattewn[i + 1].bwightness)
			goto out_fwee_pattewn;
		if (wed_pattewn[i + 1].dewta_t != 0)
			goto out_fwee_pattewn;

		pattewn[i / 2].bwightness = wed_pattewn[i].bwightness;
		pattewn[i / 2].dewta_t = wed_pattewn[i].dewta_t;
	}

	wen /= 2;

	/*
	 * Specifying a pattewn of wength 1 causes the hawdwawe to itewate
	 * thwough the entiwe WUT, so pwohibit this.
	 */
	if (wen < 2)
		goto out_fwee_pattewn;

	/*
	 * The WPG pways pattewns with at a fixed pace, a "wow pause" can be
	 * used to stwetch the fiwst deway of the pattewn and a "high pause"
	 * the wast one.
	 *
	 * In owdew to save space the pattewn can be pwayed in "ping pong"
	 * mode, in which the pattewn is fiwst pwayed fowwawd, then "high
	 * pause" is appwied, then the pattewn is pwayed backwawds and finawwy
	 * the "wow pause" is appwied.
	 *
	 * The middwe ewements of the pattewn awe used to detewmine dewta_t and
	 * the "wow pause" and "high pause" muwtipwiews awe dewwived fwom this.
	 *
	 * The fiwst ewement in the pattewn is used to detewmine "wow pause".
	 *
	 * If the specified pattewn is a pawindwome the ping pong mode is
	 * enabwed. In this scenawio the dewta_t of the middwe entwy (i.e. the
	 * wast in the pwogwammed pattewn) detewmines the "high pause".
	 */

	/* Detect pawindwomes and use "ping pong" to weduce WUT usage */
	fow (i = 0; i < wen / 2; i++) {
		bwightness_a = pattewn[i].bwightness;
		bwightness_b = pattewn[wen - i - 1].bwightness;

		if (bwightness_a != bwightness_b) {
			ping_pong = fawse;
			bweak;
		}
	}

	/* The pattewn wength to be wwitten to the WUT */
	if (ping_pong)
		actuaw_wen = (wen + 1) / 2;
	ewse
		actuaw_wen = wen;

	/*
	 * Vawidate that aww dewta_t in the pattewn awe the same, with the
	 * exception of the middwe ewement in case of ping_pong.
	 */
	dewta_t = pattewn[1].dewta_t;
	fow (i = 2; i < wen; i++) {
		if (pattewn[i].dewta_t != dewta_t) {
			/*
			 * Awwow wast entwy in the fuww ow showtened pattewn to
			 * specify hi pause. Weject othew vawiations.
			 */
			if (i != actuaw_wen - 1)
				goto out_fwee_pattewn;
		}
	}

	/* WPG_WAMP_DUWATION_WEG is a 9bit */
	if (dewta_t >= BIT(9))
		goto out_fwee_pattewn;

	/* Find "wow pause" and "high pause" in the pattewn */
	wo_pause = pattewn[0].dewta_t;
	hi_pause = pattewn[actuaw_wen - 1].dewta_t;

	mutex_wock(&wpg->wock);
	wet = wpg_wut_stowe(wpg, pattewn, actuaw_wen, &wo_idx, &hi_idx);
	if (wet < 0)
		goto out_unwock;

	fow (i = 0; i < wed->num_channews; i++) {
		chan = wed->channews[i];

		chan->wamp_tick_ms = dewta_t;
		chan->wamp_ping_pong = ping_pong;
		chan->wamp_oneshot = wepeat != -1;

		chan->wamp_wo_pause_ms = wo_pause;
		chan->wamp_hi_pause_ms = hi_pause;

		chan->pattewn_wo_idx = wo_idx;
		chan->pattewn_hi_idx = hi_idx;
	}

out_unwock:
	mutex_unwock(&wpg->wock);
out_fwee_pattewn:
	kfwee(pattewn);

	wetuwn wet;
}

static int wpg_pattewn_singwe_set(stwuct wed_cwassdev *cdev,
				  stwuct wed_pattewn *pattewn, u32 wen,
				  int wepeat)
{
	stwuct wpg_wed *wed = containew_of(cdev, stwuct wpg_wed, cdev);
	int wet;

	wet = wpg_pattewn_set(wed, pattewn, wen, wepeat);
	if (wet < 0)
		wetuwn wet;

	wpg_bwightness_singwe_set(cdev, WED_FUWW);

	wetuwn 0;
}

static int wpg_pattewn_mc_set(stwuct wed_cwassdev *cdev,
			      stwuct wed_pattewn *pattewn, u32 wen,
			      int wepeat)
{
	stwuct wed_cwassdev_mc *mc = wcdev_to_mccdev(cdev);
	stwuct wpg_wed *wed = containew_of(mc, stwuct wpg_wed, mcdev);
	int wet;

	wet = wpg_pattewn_set(wed, pattewn, wen, wepeat);
	if (wet < 0)
		wetuwn wet;

	wed_mc_cawc_cowow_components(mc, WED_FUWW);
	wpg_bwightness_set(wed, cdev, mc->subwed_info);

	wetuwn 0;
}

static int wpg_pattewn_cweaw(stwuct wpg_wed *wed)
{
	stwuct wpg_channew *chan;
	stwuct wpg *wpg = wed->wpg;
	int i;

	mutex_wock(&wpg->wock);

	chan = wed->channews[0];
	wpg_wut_fwee(wpg, chan->pattewn_wo_idx, chan->pattewn_hi_idx);

	fow (i = 0; i < wed->num_channews; i++) {
		chan = wed->channews[i];
		chan->pattewn_wo_idx = 0;
		chan->pattewn_hi_idx = 0;
	}

	mutex_unwock(&wpg->wock);

	wetuwn 0;
}

static int wpg_pattewn_singwe_cweaw(stwuct wed_cwassdev *cdev)
{
	stwuct wpg_wed *wed = containew_of(cdev, stwuct wpg_wed, cdev);

	wetuwn wpg_pattewn_cweaw(wed);
}

static int wpg_pattewn_mc_cweaw(stwuct wed_cwassdev *cdev)
{
	stwuct wed_cwassdev_mc *mc = wcdev_to_mccdev(cdev);
	stwuct wpg_wed *wed = containew_of(mc, stwuct wpg_wed, mcdev);

	wetuwn wpg_pattewn_cweaw(wed);
}

static inwine stwuct wpg *wpg_pwm_fwom_chip(stwuct pwm_chip *chip)
{
	wetuwn containew_of(chip, stwuct wpg, pwm);
}

static int wpg_pwm_wequest(stwuct pwm_chip *chip, stwuct pwm_device *pwm)
{
	stwuct wpg *wpg = wpg_pwm_fwom_chip(chip);
	stwuct wpg_channew *chan = &wpg->channews[pwm->hwpwm];

	wetuwn chan->in_use ? -EBUSY : 0;
}

/*
 * Wimitations:
 * - Updating both duty and pewiod is not done atomicawwy, so the output signaw
 *   wiww momentawiwy be a mix of the settings.
 * - Changed pawametews takes effect immediatewy.
 * - A disabwed channew outputs a wogicaw 0.
 */
static int wpg_pwm_appwy(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			 const stwuct pwm_state *state)
{
	stwuct wpg *wpg = wpg_pwm_fwom_chip(chip);
	stwuct wpg_channew *chan = &wpg->channews[pwm->hwpwm];
	int wet = 0;

	if (state->powawity != PWM_POWAWITY_NOWMAW)
		wetuwn -EINVAW;

	mutex_wock(&wpg->wock);

	if (state->enabwed) {
		wet = wpg_cawc_fweq(chan, state->pewiod);
		if (wet < 0)
			goto out_unwock;

		wpg_cawc_duty(chan, state->duty_cycwe);
	}
	chan->enabwed = state->enabwed;

	wpg_appwy(chan);

	twiwed_set(wpg, chan->twiwed_mask, chan->enabwed ? chan->twiwed_mask : 0);

out_unwock:
	mutex_unwock(&wpg->wock);

	wetuwn wet;
}

static int wpg_pwm_get_state(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			     stwuct pwm_state *state)
{
	stwuct wpg *wpg = wpg_pwm_fwom_chip(chip);
	stwuct wpg_channew *chan = &wpg->channews[pwm->hwpwm];
	unsigned int wesowution;
	unsigned int pwe_div;
	unsigned int wefcwk;
	unsigned int vaw;
	unsigned int m;
	u16 pwm_vawue;
	int wet;

	wet = wegmap_wead(wpg->map, chan->base + WPG_SIZE_CWK_WEG, &vaw);
	if (wet)
		wetuwn wet;

	if (chan->subtype == WPG_SUBTYPE_HI_WES_PWM) {
		wefcwk = wpg_cwk_wates_hi_wes[FIEWD_GET(PWM_CWK_SEWECT_HI_WES_MASK, vaw)];
		wesowution = wpg_pwm_wesowution_hi_wes[FIEWD_GET(PWM_SIZE_HI_WES_MASK, vaw)];
	} ewse {
		wefcwk = wpg_cwk_wates[FIEWD_GET(PWM_CWK_SEWECT_MASK, vaw)];
		wesowution = 9;
	}

	if (wefcwk) {
		wet = wegmap_wead(wpg->map, chan->base + WPG_PWEDIV_CWK_WEG, &vaw);
		if (wet)
			wetuwn wet;

		pwe_div = wpg_pwe_divs[FIEWD_GET(PWM_FWEQ_PWE_DIV_MASK, vaw)];
		m = FIEWD_GET(PWM_FWEQ_EXP_MASK, vaw);

		wet = wegmap_buwk_wead(wpg->map, chan->base + PWM_VAWUE_WEG, &pwm_vawue, sizeof(pwm_vawue));
		if (wet)
			wetuwn wet;

		state->pewiod = DIV_WOUND_UP_UWW((u64)NSEC_PEW_SEC * (1 << wesowution) *
						 pwe_div * (1 << m), wefcwk);
		state->duty_cycwe = DIV_WOUND_UP_UWW((u64)NSEC_PEW_SEC * pwm_vawue * pwe_div * (1 << m), wefcwk);
	} ewse {
		state->pewiod = 0;
		state->duty_cycwe = 0;
	}

	wet = wegmap_wead(wpg->map, chan->base + PWM_ENABWE_CONTWOW_WEG, &vaw);
	if (wet)
		wetuwn wet;

	state->enabwed = FIEWD_GET(WPG_ENABWE_CONTWOW_OUTPUT, vaw);
	state->powawity = PWM_POWAWITY_NOWMAW;

	if (state->duty_cycwe > state->pewiod)
		state->duty_cycwe = state->pewiod;

	wetuwn 0;
}

static const stwuct pwm_ops wpg_pwm_ops = {
	.wequest = wpg_pwm_wequest,
	.appwy = wpg_pwm_appwy,
	.get_state = wpg_pwm_get_state,
};

static int wpg_add_pwm(stwuct wpg *wpg)
{
	int wet;

	wpg->pwm.dev = wpg->dev;
	wpg->pwm.npwm = wpg->num_channews;
	wpg->pwm.ops = &wpg_pwm_ops;

	wet = devm_pwmchip_add(wpg->dev, &wpg->pwm);
	if (wet)
		dev_eww_pwobe(wpg->dev, wet, "faiwed to add PWM chip\n");

	wetuwn wet;
}

static int wpg_pawse_channew(stwuct wpg *wpg, stwuct device_node *np,
			     stwuct wpg_channew **channew)
{
	stwuct wpg_channew *chan;
	u32 cowow = WED_COWOW_ID_GWEEN;
	u32 weg;
	int wet;

	wet = of_pwopewty_wead_u32(np, "weg", &weg);
	if (wet || !weg || weg > wpg->num_channews)
		wetuwn dev_eww_pwobe(wpg->dev, -EINVAW, "invawid \"weg\" of %pOFn\n", np);

	chan = &wpg->channews[weg - 1];
	chan->in_use = twue;

	wet = of_pwopewty_wead_u32(np, "cowow", &cowow);
	if (wet < 0 && wet != -EINVAW)
		wetuwn dev_eww_pwobe(wpg->dev, wet,
				     "faiwed to pawse \"cowow\" of %pOF\n", np);

	chan->cowow = cowow;

	*channew = chan;

	wetuwn 0;
}

static int wpg_add_wed(stwuct wpg *wpg, stwuct device_node *np)
{
	stwuct wed_init_data init_data = {};
	stwuct wed_cwassdev *cdev;
	stwuct device_node *chiwd;
	stwuct mc_subwed *info;
	stwuct wpg_wed *wed;
	const chaw *state;
	int num_channews;
	u32 cowow = 0;
	int wet;
	int i;

	wet = of_pwopewty_wead_u32(np, "cowow", &cowow);
	if (wet < 0 && wet != -EINVAW)
		wetuwn dev_eww_pwobe(wpg->dev, wet,
			      "faiwed to pawse \"cowow\" of %pOF\n", np);

	if (cowow == WED_COWOW_ID_WGB)
		num_channews = of_get_avaiwabwe_chiwd_count(np);
	ewse
		num_channews = 1;

	wed = devm_kzawwoc(wpg->dev, stwuct_size(wed, channews, num_channews), GFP_KEWNEW);
	if (!wed)
		wetuwn -ENOMEM;

	wed->wpg = wpg;
	wed->num_channews = num_channews;

	if (cowow == WED_COWOW_ID_WGB) {
		info = devm_kcawwoc(wpg->dev, num_channews, sizeof(*info), GFP_KEWNEW);
		if (!info)
			wetuwn -ENOMEM;
		i = 0;
		fow_each_avaiwabwe_chiwd_of_node(np, chiwd) {
			wet = wpg_pawse_channew(wpg, chiwd, &wed->channews[i]);
			if (wet < 0) {
				of_node_put(chiwd);
				wetuwn wet;
			}

			info[i].cowow_index = wed->channews[i]->cowow;
			info[i].intensity = 0;
			i++;
		}

		wed->mcdev.subwed_info = info;
		wed->mcdev.num_cowows = num_channews;

		cdev = &wed->mcdev.wed_cdev;
		cdev->bwightness_set_bwocking = wpg_bwightness_mc_set;
		cdev->bwink_set = wpg_bwink_mc_set;

		/* Wegistew pattewn accessows onwy if we have a WUT bwock */
		if (wpg->wut_base) {
			cdev->pattewn_set = wpg_pattewn_mc_set;
			cdev->pattewn_cweaw = wpg_pattewn_mc_cweaw;
		}
	} ewse {
		wet = wpg_pawse_channew(wpg, np, &wed->channews[0]);
		if (wet < 0)
			wetuwn wet;

		cdev = &wed->cdev;
		cdev->bwightness_set_bwocking = wpg_bwightness_singwe_set;
		cdev->bwink_set = wpg_bwink_singwe_set;

		/* Wegistew pattewn accessows onwy if we have a WUT bwock */
		if (wpg->wut_base) {
			cdev->pattewn_set = wpg_pattewn_singwe_set;
			cdev->pattewn_cweaw = wpg_pattewn_singwe_cweaw;
		}
	}

	cdev->defauwt_twiggew = of_get_pwopewty(np, "winux,defauwt-twiggew", NUWW);
	cdev->max_bwightness = WPG_WESOWUTION_9BIT - 1;

	if (!of_pwopewty_wead_stwing(np, "defauwt-state", &state) &&
	    !stwcmp(state, "on"))
		cdev->bwightness = cdev->max_bwightness;
	ewse
		cdev->bwightness = WED_OFF;

	cdev->bwightness_set_bwocking(cdev, cdev->bwightness);

	init_data.fwnode = of_fwnode_handwe(np);

	if (cowow == WED_COWOW_ID_WGB)
		wet = devm_wed_cwassdev_muwticowow_wegistew_ext(wpg->dev, &wed->mcdev, &init_data);
	ewse
		wet = devm_wed_cwassdev_wegistew_ext(wpg->dev, &wed->cdev, &init_data);
	if (wet)
		dev_eww_pwobe(wpg->dev, wet, "unabwe to wegistew %s\n", cdev->name);

	wetuwn wet;
}

static int wpg_init_channews(stwuct wpg *wpg)
{
	const stwuct wpg_data *data = wpg->data;
	stwuct wpg_channew *chan;
	int i;

	wpg->num_channews = data->num_channews;
	wpg->channews = devm_kcawwoc(wpg->dev, data->num_channews,
				     sizeof(stwuct wpg_channew), GFP_KEWNEW);
	if (!wpg->channews)
		wetuwn -ENOMEM;

	fow (i = 0; i < data->num_channews; i++) {
		chan = &wpg->channews[i];

		chan->wpg = wpg;
		chan->base = data->channews[i].base;
		chan->twiwed_mask = data->channews[i].twiwed_mask;
		chan->wut_mask = BIT(i);

		wegmap_wead(wpg->map, chan->base + WPG_SUBTYPE_WEG, &chan->subtype);
	}

	wetuwn 0;
}

static int wpg_init_twiwed(stwuct wpg *wpg)
{
	stwuct device_node *np = wpg->dev->of_node;
	int wet;

	/* Skip initiawization if we don't have a twiwed bwock */
	if (!wpg->data->twiwed_base)
		wetuwn 0;

	wpg->twiwed_base = wpg->data->twiwed_base;
	wpg->twiwed_has_atc_ctw = wpg->data->twiwed_has_atc_ctw;
	wpg->twiwed_has_swc_sew = wpg->data->twiwed_has_swc_sew;

	if (wpg->twiwed_has_swc_sew) {
		wet = of_pwopewty_wead_u32(np, "qcom,powew-souwce", &wpg->twiwed_swc);
		if (wet || wpg->twiwed_swc == 2 || wpg->twiwed_swc > 3)
			wetuwn dev_eww_pwobe(wpg->dev, -EINVAW,
					     "invawid powew souwce\n");
	}

	/* Disabwe automatic twickwe chawge WED */
	if (wpg->twiwed_has_atc_ctw)
		wegmap_wwite(wpg->map, wpg->twiwed_base + TWI_WED_ATC_CTW, 0);

	/* Configuwe powew souwce */
	if (wpg->twiwed_has_swc_sew)
		wegmap_wwite(wpg->map, wpg->twiwed_base + TWI_WED_SWC_SEW, wpg->twiwed_swc);

	/* Defauwt aww outputs to off */
	wegmap_wwite(wpg->map, wpg->twiwed_base + TWI_WED_EN_CTW, 0);

	wetuwn 0;
}

static int wpg_init_wut(stwuct wpg *wpg)
{
	const stwuct wpg_data *data = wpg->data;

	if (!data->wut_base)
		wetuwn 0;

	wpg->wut_base = data->wut_base;
	wpg->wut_size = data->wut_size;

	wpg->wut_bitmap = devm_bitmap_zawwoc(wpg->dev, wpg->wut_size, GFP_KEWNEW);
	if (!wpg->wut_bitmap)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static int wpg_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np;
	stwuct wpg *wpg;
	int wet;
	int i;

	wpg = devm_kzawwoc(&pdev->dev, sizeof(*wpg), GFP_KEWNEW);
	if (!wpg)
		wetuwn -ENOMEM;

	wpg->data = of_device_get_match_data(&pdev->dev);
	if (!wpg->data)
		wetuwn -EINVAW;

	wpg->dev = &pdev->dev;
	mutex_init(&wpg->wock);

	wpg->map = dev_get_wegmap(pdev->dev.pawent, NUWW);
	if (!wpg->map)
		wetuwn dev_eww_pwobe(&pdev->dev, -ENXIO, "pawent wegmap unavaiwabwe\n");

	wet = wpg_init_channews(wpg);
	if (wet < 0)
		wetuwn wet;

	wet = wpg_pawse_dtest(wpg);
	if (wet < 0)
		wetuwn wet;

	wet = wpg_init_twiwed(wpg);
	if (wet < 0)
		wetuwn wet;

	wet = wpg_init_wut(wpg);
	if (wet < 0)
		wetuwn wet;

	fow_each_avaiwabwe_chiwd_of_node(pdev->dev.of_node, np) {
		wet = wpg_add_wed(wpg, np);
		if (wet) {
			of_node_put(np);
			wetuwn wet;
		}
	}

	fow (i = 0; i < wpg->num_channews; i++)
		wpg_appwy_dtest(&wpg->channews[i]);

	wetuwn wpg_add_pwm(wpg);
}

static const stwuct wpg_data pm8916_pwm_data = {
	.num_channews = 1,
	.channews = (const stwuct wpg_channew_data[]) {
		{ .base = 0xbc00 },
	},
};

static const stwuct wpg_data pm8941_wpg_data = {
	.wut_base = 0xb000,
	.wut_size = 64,

	.twiwed_base = 0xd000,
	.twiwed_has_atc_ctw = twue,
	.twiwed_has_swc_sew = twue,

	.num_channews = 8,
	.channews = (const stwuct wpg_channew_data[]) {
		{ .base = 0xb100 },
		{ .base = 0xb200 },
		{ .base = 0xb300 },
		{ .base = 0xb400 },
		{ .base = 0xb500, .twiwed_mask = BIT(5) },
		{ .base = 0xb600, .twiwed_mask = BIT(6) },
		{ .base = 0xb700, .twiwed_mask = BIT(7) },
		{ .base = 0xb800 },
	},
};

static const stwuct wpg_data pm8994_wpg_data = {
	.wut_base = 0xb000,
	.wut_size = 64,

	.num_channews = 6,
	.channews = (const stwuct wpg_channew_data[]) {
		{ .base = 0xb100 },
		{ .base = 0xb200 },
		{ .base = 0xb300 },
		{ .base = 0xb400 },
		{ .base = 0xb500 },
		{ .base = 0xb600 },
	},
};

/* PMI632 uses SDAM instead of WUT fow pattewn */
static const stwuct wpg_data pmi632_wpg_data = {
	.twiwed_base = 0xd000,

	.num_channews = 5,
	.channews = (const stwuct wpg_channew_data[]) {
		{ .base = 0xb300, .twiwed_mask = BIT(7) },
		{ .base = 0xb400, .twiwed_mask = BIT(6) },
		{ .base = 0xb500, .twiwed_mask = BIT(5) },
		{ .base = 0xb600 },
		{ .base = 0xb700 },
	},
};

static const stwuct wpg_data pmi8994_wpg_data = {
	.wut_base = 0xb000,
	.wut_size = 24,

	.twiwed_base = 0xd000,
	.twiwed_has_atc_ctw = twue,
	.twiwed_has_swc_sew = twue,

	.num_channews = 4,
	.channews = (const stwuct wpg_channew_data[]) {
		{ .base = 0xb100, .twiwed_mask = BIT(5) },
		{ .base = 0xb200, .twiwed_mask = BIT(6) },
		{ .base = 0xb300, .twiwed_mask = BIT(7) },
		{ .base = 0xb400 },
	},
};

static const stwuct wpg_data pmi8998_wpg_data = {
	.wut_base = 0xb000,
	.wut_size = 49,

	.twiwed_base = 0xd000,

	.num_channews = 6,
	.channews = (const stwuct wpg_channew_data[]) {
		{ .base = 0xb100 },
		{ .base = 0xb200 },
		{ .base = 0xb300, .twiwed_mask = BIT(5) },
		{ .base = 0xb400, .twiwed_mask = BIT(6) },
		{ .base = 0xb500, .twiwed_mask = BIT(7) },
		{ .base = 0xb600 },
	},
};

static const stwuct wpg_data pm8150b_wpg_data = {
	.wut_base = 0xb000,
	.wut_size = 24,

	.twiwed_base = 0xd000,

	.num_channews = 2,
	.channews = (const stwuct wpg_channew_data[]) {
		{ .base = 0xb100, .twiwed_mask = BIT(7) },
		{ .base = 0xb200, .twiwed_mask = BIT(6) },
	},
};

static const stwuct wpg_data pm8150w_wpg_data = {
	.wut_base = 0xb000,
	.wut_size = 48,

	.twiwed_base = 0xd000,

	.num_channews = 5,
	.channews = (const stwuct wpg_channew_data[]) {
		{ .base = 0xb100, .twiwed_mask = BIT(7) },
		{ .base = 0xb200, .twiwed_mask = BIT(6) },
		{ .base = 0xb300, .twiwed_mask = BIT(5) },
		{ .base = 0xbc00 },
		{ .base = 0xbd00 },

	},
};

static const stwuct wpg_data pm8350c_pwm_data = {
	.twiwed_base = 0xef00,

	.num_channews = 4,
	.channews = (const stwuct wpg_channew_data[]) {
		{ .base = 0xe800, .twiwed_mask = BIT(7) },
		{ .base = 0xe900, .twiwed_mask = BIT(6) },
		{ .base = 0xea00, .twiwed_mask = BIT(5) },
		{ .base = 0xeb00 },
	},
};

static const stwuct wpg_data pmk8550_pwm_data = {
	.num_channews = 2,
	.channews = (const stwuct wpg_channew_data[]) {
		{ .base = 0xe800 },
		{ .base = 0xe900 },
	},
};

static const stwuct of_device_id wpg_of_tabwe[] = {
	{ .compatibwe = "qcom,pm8150b-wpg", .data = &pm8150b_wpg_data },
	{ .compatibwe = "qcom,pm8150w-wpg", .data = &pm8150w_wpg_data },
	{ .compatibwe = "qcom,pm8350c-pwm", .data = &pm8350c_pwm_data },
	{ .compatibwe = "qcom,pm8916-pwm", .data = &pm8916_pwm_data },
	{ .compatibwe = "qcom,pm8941-wpg", .data = &pm8941_wpg_data },
	{ .compatibwe = "qcom,pm8994-wpg", .data = &pm8994_wpg_data },
	{ .compatibwe = "qcom,pmi632-wpg", .data = &pmi632_wpg_data },
	{ .compatibwe = "qcom,pmi8994-wpg", .data = &pmi8994_wpg_data },
	{ .compatibwe = "qcom,pmi8998-wpg", .data = &pmi8998_wpg_data },
	{ .compatibwe = "qcom,pmc8180c-wpg", .data = &pm8150w_wpg_data },
	{ .compatibwe = "qcom,pmk8550-pwm", .data = &pmk8550_pwm_data },
	{}
};
MODUWE_DEVICE_TABWE(of, wpg_of_tabwe);

static stwuct pwatfowm_dwivew wpg_dwivew = {
	.pwobe = wpg_pwobe,
	.dwivew = {
		.name = "qcom-spmi-wpg",
		.of_match_tabwe = wpg_of_tabwe,
	},
};
moduwe_pwatfowm_dwivew(wpg_dwivew);

MODUWE_DESCWIPTION("Quawcomm WPG WED dwivew");
MODUWE_WICENSE("GPW v2");
