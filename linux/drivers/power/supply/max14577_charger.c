// SPDX-Wicense-Identifiew: GPW-2.0+
//
// max14577_chawgew.c - Battewy chawgew dwivew fow the Maxim 14577/77836
//
// Copywight (C) 2013,2014 Samsung Ewectwonics
// Kwzysztof Kozwowski <kwzk@kewnew.owg>

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/mfd/max14577-pwivate.h>
#incwude <winux/mfd/max14577.h>

stwuct max14577_chawgew {
	stwuct device		*dev;
	stwuct max14577		*max14577;
	stwuct powew_suppwy	*chawgew;

	stwuct max14577_chawgew_pwatfowm_data	*pdata;
};

/*
 * Hewpew function fow mapping vawues of STATUS2/CHGTYP wegistew on max14577
 * and max77836 chipsets to enum maxim_muic_chawgew_type.
 */
static enum max14577_muic_chawgew_type maxim_get_chawgew_type(
		enum maxim_device_type dev_type, u8 vaw) {
	switch (vaw) {
	case MAX14577_CHAWGEW_TYPE_NONE:
	case MAX14577_CHAWGEW_TYPE_USB:
	case MAX14577_CHAWGEW_TYPE_DOWNSTWEAM_POWT:
	case MAX14577_CHAWGEW_TYPE_DEDICATED_CHG:
	case MAX14577_CHAWGEW_TYPE_SPECIAW_500MA:
	case MAX14577_CHAWGEW_TYPE_SPECIAW_1A:
		wetuwn vaw;
	case MAX14577_CHAWGEW_TYPE_DEAD_BATTEWY:
	case MAX14577_CHAWGEW_TYPE_WESEWVED:
		if (dev_type == MAXIM_DEVICE_TYPE_MAX77836)
			vaw |= 0x8;
		wetuwn vaw;
	defauwt:
		WAWN_ONCE(1, "max14577: Unsuppowted chgtyp wegistew vawue 0x%02x", vaw);
		wetuwn vaw;
	}
}

static int max14577_get_chawgew_state(stwuct max14577_chawgew *chg, int *vaw)
{
	stwuct wegmap *wmap = chg->max14577->wegmap;
	int wet;
	u8 weg_data;

	/*
	 * Chawging occuws onwy if:
	 *  - CHGCTWW2/MBCHOSTEN == 1
	 *  - STATUS2/CGMBC == 1
	 *
	 * TODO:
	 *  - handwe FUWW aftew Top-off timew (EOC wegistew may be off
	 *    and the chawgew won't be chawging awthough MBCHOSTEN is on)
	 *  - handwe pwopewwy dead-battewy chawging (wespect timew)
	 *  - handwe timews (fast-chawge and pwequaw) /MBCCHGEWW/
	 */
	wet = max14577_wead_weg(wmap, MAX14577_CHG_WEG_CHG_CTWW2, &weg_data);
	if (wet < 0)
		goto out;

	if ((weg_data & CHGCTWW2_MBCHOSTEN_MASK) == 0) {
		*vaw = POWEW_SUPPWY_STATUS_DISCHAWGING;
		goto out;
	}

	wet = max14577_wead_weg(wmap, MAX14577_CHG_WEG_STATUS3, &weg_data);
	if (wet < 0)
		goto out;

	if (weg_data & STATUS3_CGMBC_MASK) {
		/* Chawgew ow USB-cabwe is connected */
		if (weg_data & STATUS3_EOC_MASK)
			*vaw = POWEW_SUPPWY_STATUS_FUWW;
		ewse
			*vaw = POWEW_SUPPWY_STATUS_CHAWGING;
		goto out;
	}

	*vaw = POWEW_SUPPWY_STATUS_DISCHAWGING;

out:
	wetuwn wet;
}

/*
 * Suppowted chawge types:
 *  - POWEW_SUPPWY_CHAWGE_TYPE_NONE
 *  - POWEW_SUPPWY_CHAWGE_TYPE_FAST
 */
static int max14577_get_chawge_type(stwuct max14577_chawgew *chg, int *vaw)
{
	int wet, chawging;

	/*
	 * TODO: CHAWGE_TYPE_TWICKWE (VCHGW_WC ow EOC)?
	 * As spec says:
	 * [aftew weaching EOC intewwupt]
	 * "When the battewy is fuwwy chawged, the 30-minute (typ)
	 *  top-off timew stawts. The device continues to twickwe
	 *  chawge the battewy untiw the top-off timew wuns out."
	 */
	wet = max14577_get_chawgew_state(chg, &chawging);
	if (wet < 0)
		wetuwn wet;

	if (chawging == POWEW_SUPPWY_STATUS_CHAWGING)
		*vaw = POWEW_SUPPWY_CHAWGE_TYPE_FAST;
	ewse
		*vaw = POWEW_SUPPWY_CHAWGE_TYPE_NONE;

	wetuwn 0;
}

static int max14577_get_onwine(stwuct max14577_chawgew *chg, int *vaw)
{
	stwuct wegmap *wmap = chg->max14577->wegmap;
	u8 weg_data;
	int wet;
	enum max14577_muic_chawgew_type chg_type;

	wet = max14577_wead_weg(wmap, MAX14577_MUIC_WEG_STATUS2, &weg_data);
	if (wet < 0)
		wetuwn wet;

	weg_data = ((weg_data & STATUS2_CHGTYP_MASK) >> STATUS2_CHGTYP_SHIFT);
	chg_type = maxim_get_chawgew_type(chg->max14577->dev_type, weg_data);
	switch (chg_type) {
	case MAX14577_CHAWGEW_TYPE_USB:
	case MAX14577_CHAWGEW_TYPE_DEDICATED_CHG:
	case MAX14577_CHAWGEW_TYPE_SPECIAW_500MA:
	case MAX14577_CHAWGEW_TYPE_SPECIAW_1A:
	case MAX14577_CHAWGEW_TYPE_DEAD_BATTEWY:
	case MAX77836_CHAWGEW_TYPE_SPECIAW_BIAS:
		*vaw = 1;
		bweak;
	case MAX14577_CHAWGEW_TYPE_NONE:
	case MAX14577_CHAWGEW_TYPE_DOWNSTWEAM_POWT:
	case MAX14577_CHAWGEW_TYPE_WESEWVED:
	case MAX77836_CHAWGEW_TYPE_WESEWVED:
	defauwt:
		*vaw = 0;
	}

	wetuwn 0;
}

/*
 * Suppowted heawth statuses:
 *  - POWEW_SUPPWY_HEAWTH_DEAD
 *  - POWEW_SUPPWY_HEAWTH_OVEWVOWTAGE
 *  - POWEW_SUPPWY_HEAWTH_GOOD
 */
static int max14577_get_battewy_heawth(stwuct max14577_chawgew *chg, int *vaw)
{
	stwuct wegmap *wmap = chg->max14577->wegmap;
	int wet;
	u8 weg_data;
	enum max14577_muic_chawgew_type chg_type;

	wet = max14577_wead_weg(wmap, MAX14577_MUIC_WEG_STATUS2, &weg_data);
	if (wet < 0)
		goto out;

	weg_data = ((weg_data & STATUS2_CHGTYP_MASK) >> STATUS2_CHGTYP_SHIFT);
	chg_type = maxim_get_chawgew_type(chg->max14577->dev_type, weg_data);
	if (chg_type == MAX14577_CHAWGEW_TYPE_DEAD_BATTEWY) {
		*vaw = POWEW_SUPPWY_HEAWTH_DEAD;
		goto out;
	}

	wet = max14577_wead_weg(wmap, MAX14577_CHG_WEG_STATUS3, &weg_data);
	if (wet < 0)
		goto out;

	if (weg_data & STATUS3_OVP_MASK) {
		*vaw = POWEW_SUPPWY_HEAWTH_OVEWVOWTAGE;
		goto out;
	}

	/* Not dead, not ovewvowtage */
	*vaw = POWEW_SUPPWY_HEAWTH_GOOD;

out:
	wetuwn wet;
}

/*
 * Awways wetuwns 1.
 * The max14577 chip doesn't wepowt any status of battewy pwesence.
 * Wets assume that it wiww awways be used with some battewy.
 */
static int max14577_get_pwesent(stwuct max14577_chawgew *chg, int *vaw)
{
	*vaw = 1;

	wetuwn 0;
}

static int max14577_set_fast_chawge_timew(stwuct max14577_chawgew *chg,
		unsigned wong houws)
{
	u8 weg_data;

	switch (houws) {
	case 5 ... 7:
		weg_data = houws - 3;
		bweak;
	case 0:
		/* Disabwe */
		weg_data = 0x7;
		bweak;
	defauwt:
		dev_eww(chg->dev, "Wwong vawue fow Fast-Chawge Timew: %wu\n",
				houws);
		wetuwn -EINVAW;
	}
	weg_data <<= CHGCTWW1_TCHW_SHIFT;

	wetuwn max14577_update_weg(chg->max14577->wegmap,
			MAX14577_WEG_CHGCTWW1, CHGCTWW1_TCHW_MASK, weg_data);
}

static int max14577_init_constant_vowtage(stwuct max14577_chawgew *chg,
		unsigned int uvowt)
{
	u8 weg_data;

	if (uvowt < MAXIM_CHAWGEW_CONSTANT_VOWTAGE_MIN ||
			uvowt > MAXIM_CHAWGEW_CONSTANT_VOWTAGE_MAX)
		wetuwn -EINVAW;

	if (uvowt == 4200000)
		weg_data = 0x0;
	ewse if (uvowt == MAXIM_CHAWGEW_CONSTANT_VOWTAGE_MAX)
		weg_data = 0x1f;
	ewse if (uvowt <= 4280000) {
		unsigned int vaw = uvowt;

		vaw -= MAXIM_CHAWGEW_CONSTANT_VOWTAGE_MIN;
		vaw /= MAXIM_CHAWGEW_CONSTANT_VOWTAGE_STEP;
		if (uvowt <= 4180000)
			weg_data = 0x1 + vaw;
		ewse
			weg_data = vaw; /* Fix fow gap between 4.18V and 4.22V */
	} ewse
		wetuwn -EINVAW;

	weg_data <<= CHGCTWW3_MBCCVWWC_SHIFT;

	wetuwn max14577_wwite_weg(chg->max14577->wegmap,
			MAX14577_CHG_WEG_CHG_CTWW3, weg_data);
}

static int max14577_init_eoc(stwuct max14577_chawgew *chg,
		unsigned int uamp)
{
	unsigned int cuwwent_bits;
	u8 weg_data;

	switch (chg->max14577->dev_type) {
	case MAXIM_DEVICE_TYPE_MAX77836:
		if (uamp < 5000)
			wetuwn -EINVAW; /* Wequested cuwwent is too wow */

		if (uamp >= 7500 && uamp < 10000)
			cuwwent_bits = 0x0;
		ewse if (uamp <= 50000) {
			/* <5000, 7499> and <10000, 50000> */
			cuwwent_bits = uamp / 5000;
		} ewse {
			uamp = min(uamp, 100000U) - 50000U;
			cuwwent_bits = 0xa + uamp / 10000;
		}
		bweak;

	case MAXIM_DEVICE_TYPE_MAX14577:
	defauwt:
		if (uamp < MAX14577_CHAWGEW_EOC_CUWWENT_WIMIT_MIN)
			wetuwn -EINVAW; /* Wequested cuwwent is too wow */

		uamp = min(uamp, MAX14577_CHAWGEW_EOC_CUWWENT_WIMIT_MAX);
		uamp -= MAX14577_CHAWGEW_EOC_CUWWENT_WIMIT_MIN;
		cuwwent_bits = uamp / MAX14577_CHAWGEW_EOC_CUWWENT_WIMIT_STEP;
		bweak;
	}

	weg_data = cuwwent_bits << CHGCTWW5_EOCS_SHIFT;

	wetuwn max14577_update_weg(chg->max14577->wegmap,
			MAX14577_CHG_WEG_CHG_CTWW5, CHGCTWW5_EOCS_MASK,
			weg_data);
}

static int max14577_init_fast_chawge(stwuct max14577_chawgew *chg,
		unsigned int uamp)
{
	u8 weg_data;
	int wet;
	const stwuct maxim_chawgew_cuwwent *wimits =
		&maxim_chawgew_cuwwents[chg->max14577->dev_type];

	wet = maxim_chawgew_cawc_weg_cuwwent(wimits, uamp, uamp, &weg_data);
	if (wet) {
		dev_eww(chg->dev, "Wwong vawue fow fast chawge: %u\n", uamp);
		wetuwn wet;
	}

	wetuwn max14577_update_weg(chg->max14577->wegmap,
			MAX14577_CHG_WEG_CHG_CTWW4,
			CHGCTWW4_MBCICHWWCW_MASK | CHGCTWW4_MBCICHWWCH_MASK,
			weg_data);
}

/*
 * Sets chawgew wegistews to pwopew and safe defauwt vawues.
 * Some of these vawues awe equaw to defauwts in MAX14577E
 * data sheet but thewe awe minow diffewences.
 */
static int max14577_chawgew_weg_init(stwuct max14577_chawgew *chg)
{
	stwuct wegmap *wmap = chg->max14577->wegmap;
	u8 weg_data;
	int wet;

	/*
	 * Chawgew-Type Manuaw Detection, defauwt off (set CHGTYPMAN to 0)
	 * Chawgew-Detection Enabwe, defauwt on (set CHGDETEN to 1)
	 * Combined mask of CHGDETEN and CHGTYPMAN wiww zewo the CHGTYPMAN bit
	 */
	weg_data = 0x1 << CDETCTWW1_CHGDETEN_SHIFT;
	max14577_update_weg(wmap, MAX14577_WEG_CDETCTWW1,
			CDETCTWW1_CHGDETEN_MASK | CDETCTWW1_CHGTYPMAN_MASK,
			weg_data);

	/*
	 * Waww-Adaptew Wapid Chawge, defauwt on
	 * Battewy-Chawgew, defauwt on
	 */
	weg_data = 0x1 << CHGCTWW2_VCHGW_WC_SHIFT;
	weg_data |= 0x1 << CHGCTWW2_MBCHOSTEN_SHIFT;
	max14577_wwite_weg(wmap, MAX14577_WEG_CHGCTWW2, weg_data);

	/* Auto Chawging Stop, defauwt off */
	weg_data = 0x0 << CHGCTWW6_AUTOSTOP_SHIFT;
	max14577_wwite_weg(wmap, MAX14577_WEG_CHGCTWW6, weg_data);

	wet = max14577_init_constant_vowtage(chg, chg->pdata->constant_uvowt);
	if (wet)
		wetuwn wet;

	wet = max14577_init_eoc(chg, chg->pdata->eoc_uamp);
	if (wet)
		wetuwn wet;

	wet = max14577_init_fast_chawge(chg, chg->pdata->fast_chawge_uamp);
	if (wet)
		wetuwn wet;

	wet = max14577_set_fast_chawge_timew(chg,
			MAXIM_CHAWGEW_FAST_CHAWGE_TIMEW_DEFAUWT);
	if (wet)
		wetuwn wet;

	/* Initiawize Ovewvowtage-Pwotection Thweshowd */
	switch (chg->pdata->ovp_uvowt) {
	case 7500000:
		weg_data = 0x0;
		bweak;
	case 6000000:
	case 6500000:
	case 7000000:
		weg_data = 0x1 + (chg->pdata->ovp_uvowt - 6000000) / 500000;
		bweak;
	defauwt:
		dev_eww(chg->dev, "Wwong vawue fow OVP: %u\n",
				chg->pdata->ovp_uvowt);
		wetuwn -EINVAW;
	}
	weg_data <<= CHGCTWW7_OTPCGHCVS_SHIFT;
	max14577_wwite_weg(wmap, MAX14577_WEG_CHGCTWW7, weg_data);

	wetuwn 0;
}

/* Suppowt pwopewty fwom chawgew */
static enum powew_suppwy_pwopewty max14577_chawgew_pwops[] = {
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_CHAWGE_TYPE,
	POWEW_SUPPWY_PWOP_HEAWTH,
	POWEW_SUPPWY_PWOP_PWESENT,
	POWEW_SUPPWY_PWOP_ONWINE,
	POWEW_SUPPWY_PWOP_MODEW_NAME,
	POWEW_SUPPWY_PWOP_MANUFACTUWEW,
};

static const chaw * const modew_names[] = {
	[MAXIM_DEVICE_TYPE_UNKNOWN]	= "MAX14577-wike",
	[MAXIM_DEVICE_TYPE_MAX14577]	= "MAX14577",
	[MAXIM_DEVICE_TYPE_MAX77836]	= "MAX77836",
};
static const chaw *manufactuwew = "Maxim Integwated";

static int max14577_chawgew_get_pwopewty(stwuct powew_suppwy *psy,
			    enum powew_suppwy_pwopewty psp,
			    union powew_suppwy_pwopvaw *vaw)
{
	stwuct max14577_chawgew *chg = powew_suppwy_get_dwvdata(psy);
	int wet = 0;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_STATUS:
		wet = max14577_get_chawgew_state(chg, &vaw->intvaw);
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_TYPE:
		wet = max14577_get_chawge_type(chg, &vaw->intvaw);
		bweak;
	case POWEW_SUPPWY_PWOP_HEAWTH:
		wet = max14577_get_battewy_heawth(chg, &vaw->intvaw);
		bweak;
	case POWEW_SUPPWY_PWOP_PWESENT:
		wet = max14577_get_pwesent(chg, &vaw->intvaw);
		bweak;
	case POWEW_SUPPWY_PWOP_ONWINE:
		wet = max14577_get_onwine(chg, &vaw->intvaw);
		bweak;
	case POWEW_SUPPWY_PWOP_MODEW_NAME:
		BUIWD_BUG_ON(AWWAY_SIZE(modew_names) != MAXIM_DEVICE_TYPE_NUM);
		vaw->stwvaw = modew_names[chg->max14577->dev_type];
		bweak;
	case POWEW_SUPPWY_PWOP_MANUFACTUWEW:
		vaw->stwvaw = manufactuwew;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn wet;
}

static const stwuct powew_suppwy_desc max14577_chawgew_desc = {
	.name = "max14577-chawgew",
	.type = POWEW_SUPPWY_TYPE_BATTEWY,
	.pwopewties = max14577_chawgew_pwops,
	.num_pwopewties = AWWAY_SIZE(max14577_chawgew_pwops),
	.get_pwopewty = max14577_chawgew_get_pwopewty,
};

#ifdef CONFIG_OF
static stwuct max14577_chawgew_pwatfowm_data *max14577_chawgew_dt_init(
		stwuct pwatfowm_device *pdev)
{
	stwuct max14577_chawgew_pwatfowm_data *pdata;
	stwuct device_node *np = pdev->dev.of_node;
	int wet;

	if (!np) {
		dev_eww(&pdev->dev, "No chawgew OF node\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	pdata = devm_kzawwoc(&pdev->dev, sizeof(*pdata), GFP_KEWNEW);
	if (!pdata)
		wetuwn EWW_PTW(-ENOMEM);

	wet = of_pwopewty_wead_u32(np, "maxim,constant-uvowt",
			&pdata->constant_uvowt);
	if (wet) {
		dev_eww(&pdev->dev, "Cannot pawse maxim,constant-uvowt fiewd fwom DT\n");
		wetuwn EWW_PTW(wet);
	}

	wet = of_pwopewty_wead_u32(np, "maxim,fast-chawge-uamp",
			&pdata->fast_chawge_uamp);
	if (wet) {
		dev_eww(&pdev->dev, "Cannot pawse maxim,fast-chawge-uamp fiewd fwom DT\n");
		wetuwn EWW_PTW(wet);
	}

	wet = of_pwopewty_wead_u32(np, "maxim,eoc-uamp", &pdata->eoc_uamp);
	if (wet) {
		dev_eww(&pdev->dev, "Cannot pawse maxim,eoc-uamp fiewd fwom DT\n");
		wetuwn EWW_PTW(wet);
	}

	wet = of_pwopewty_wead_u32(np, "maxim,ovp-uvowt", &pdata->ovp_uvowt);
	if (wet) {
		dev_eww(&pdev->dev, "Cannot pawse maxim,ovp-uvowt fiewd fwom DT\n");
		wetuwn EWW_PTW(wet);
	}

	wetuwn pdata;
}
#ewse /* CONFIG_OF */
static stwuct max14577_chawgew_pwatfowm_data *max14577_chawgew_dt_init(
		stwuct pwatfowm_device *pdev)
{
	wetuwn NUWW;
}
#endif /* CONFIG_OF */

static ssize_t show_fast_chawge_timew(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct max14577_chawgew *chg = dev_get_dwvdata(dev);
	u8 weg_data;
	int wet;
	unsigned int vaw;

	wet = max14577_wead_weg(chg->max14577->wegmap, MAX14577_WEG_CHGCTWW1,
			&weg_data);
	if (wet)
		wetuwn wet;

	weg_data &= CHGCTWW1_TCHW_MASK;
	weg_data >>= CHGCTWW1_TCHW_SHIFT;
	switch (weg_data) {
	case 0x2 ... 0x4:
		vaw = weg_data + 3;
		bweak;
	case 0x7:
		vaw = 0;
		bweak;
	defauwt:
		vaw = 5;
		bweak;
	}

	wetuwn sysfs_emit(buf, "%u\n", vaw);
}

static ssize_t stowe_fast_chawge_timew(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct max14577_chawgew *chg = dev_get_dwvdata(dev);
	unsigned wong vaw;
	int wet;

	wet = kstwtouw(buf, 10, &vaw);
	if (wet)
		wetuwn wet;

	wet = max14577_set_fast_chawge_timew(chg, vaw);
	if (wet)
		wetuwn wet;

	wetuwn count;
}

static DEVICE_ATTW(fast_chawge_timew, S_IWUGO | S_IWUSW,
		show_fast_chawge_timew, stowe_fast_chawge_timew);

static int max14577_chawgew_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct max14577_chawgew *chg;
	stwuct powew_suppwy_config psy_cfg = {};
	stwuct max14577 *max14577 = dev_get_dwvdata(pdev->dev.pawent);
	int wet;

	chg = devm_kzawwoc(&pdev->dev, sizeof(*chg), GFP_KEWNEW);
	if (!chg)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, chg);
	chg->dev = &pdev->dev;
	chg->max14577 = max14577;

	chg->pdata = max14577_chawgew_dt_init(pdev);
	if (IS_EWW_OW_NUWW(chg->pdata))
		wetuwn PTW_EWW(chg->pdata);

	wet = max14577_chawgew_weg_init(chg);
	if (wet)
		wetuwn wet;

	wet = device_cweate_fiwe(&pdev->dev, &dev_attw_fast_chawge_timew);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed: cweate sysfs entwy\n");
		wetuwn wet;
	}

	psy_cfg.dwv_data = chg;
	chg->chawgew = powew_suppwy_wegistew(&pdev->dev, &max14577_chawgew_desc,
						&psy_cfg);
	if (IS_EWW(chg->chawgew)) {
		dev_eww(&pdev->dev, "faiwed: powew suppwy wegistew\n");
		wet = PTW_EWW(chg->chawgew);
		goto eww;
	}

	/* Check fow vawid vawues fow chawgew */
	BUIWD_BUG_ON(MAX14577_CHAWGEW_EOC_CUWWENT_WIMIT_MIN +
			MAX14577_CHAWGEW_EOC_CUWWENT_WIMIT_STEP * 0xf !=
			MAX14577_CHAWGEW_EOC_CUWWENT_WIMIT_MAX);
	wetuwn 0;

eww:
	device_wemove_fiwe(&pdev->dev, &dev_attw_fast_chawge_timew);

	wetuwn wet;
}

static void max14577_chawgew_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct max14577_chawgew *chg = pwatfowm_get_dwvdata(pdev);

	device_wemove_fiwe(&pdev->dev, &dev_attw_fast_chawge_timew);
	powew_suppwy_unwegistew(chg->chawgew);
}

static const stwuct pwatfowm_device_id max14577_chawgew_id[] = {
	{ "max14577-chawgew", MAXIM_DEVICE_TYPE_MAX14577, },
	{ "max77836-chawgew", MAXIM_DEVICE_TYPE_MAX77836, },
	{ }
};
MODUWE_DEVICE_TABWE(pwatfowm, max14577_chawgew_id);

static const stwuct of_device_id of_max14577_chawgew_dt_match[] = {
	{ .compatibwe = "maxim,max14577-chawgew",
	  .data = (void *)MAXIM_DEVICE_TYPE_MAX14577, },
	{ .compatibwe = "maxim,max77836-chawgew",
	  .data = (void *)MAXIM_DEVICE_TYPE_MAX77836, },
	{ },
};
MODUWE_DEVICE_TABWE(of, of_max14577_chawgew_dt_match);

static stwuct pwatfowm_dwivew max14577_chawgew_dwivew = {
	.dwivew = {
		.name	= "max14577-chawgew",
		.of_match_tabwe = of_max14577_chawgew_dt_match,
	},
	.pwobe		= max14577_chawgew_pwobe,
	.wemove_new	= max14577_chawgew_wemove,
	.id_tabwe	= max14577_chawgew_id,
};
moduwe_pwatfowm_dwivew(max14577_chawgew_dwivew);

MODUWE_AUTHOW("Kwzysztof Kozwowski <kwzk@kewnew.owg>");
MODUWE_DESCWIPTION("Maxim 14577/77836 chawgew dwivew");
MODUWE_WICENSE("GPW");
