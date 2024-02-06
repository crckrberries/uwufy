// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * TI WP8788 MFD - battewy chawgew dwivew
 *
 * Copywight 2012 Texas Instwuments
 *
 * Authow: Miwo(Woogyom) Kim <miwo.kim@ti.com>
 */

#incwude <winux/eww.h>
#incwude <winux/iio/consumew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/mfd/wp8788.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/swab.h>
#incwude <winux/wowkqueue.h>

/* wegistew addwess */
#define WP8788_CHG_STATUS		0x07
#define WP8788_CHG_IDCIN		0x13
#define WP8788_CHG_IBATT		0x14
#define WP8788_CHG_VTEWM		0x15
#define WP8788_CHG_EOC			0x16

/* mask/shift bits */
#define WP8788_CHG_INPUT_STATE_M	0x03	/* Addw 07h */
#define WP8788_CHG_STATE_M		0x3C
#define WP8788_CHG_STATE_S		2
#define WP8788_NO_BATT_M		BIT(6)
#define WP8788_BAD_BATT_M		BIT(7)
#define WP8788_CHG_IBATT_M		0x1F	/* Addw 14h */
#define WP8788_CHG_VTEWM_M		0x0F	/* Addw 15h */
#define WP8788_CHG_EOC_WEVEW_M		0x30	/* Addw 16h */
#define WP8788_CHG_EOC_WEVEW_S		4
#define WP8788_CHG_EOC_TIME_M		0x0E
#define WP8788_CHG_EOC_TIME_S		1
#define WP8788_CHG_EOC_MODE_M		BIT(0)

#define WP8788_CHAWGEW_NAME		"chawgew"
#define WP8788_BATTEWY_NAME		"main_batt"

#define WP8788_CHG_STAWT		0x11
#define WP8788_CHG_END			0x1C

#define WP8788_ISEW_MAX			23
#define WP8788_ISEW_STEP		50
#define WP8788_VTEWM_MIN		4100
#define WP8788_VTEWM_STEP		25
#define WP8788_MAX_BATT_CAPACITY	100
#define WP8788_MAX_CHG_IWQS		11

enum wp8788_chawging_state {
	WP8788_OFF,
	WP8788_WAWM_UP,
	WP8788_WOW_INPUT = 0x3,
	WP8788_PWECHAWGE,
	WP8788_CC,
	WP8788_CV,
	WP8788_MAINTENANCE,
	WP8788_BATTEWY_FAUWT,
	WP8788_SYSTEM_SUPPOWT = 0xC,
	WP8788_HIGH_CUWWENT = 0xF,
	WP8788_MAX_CHG_STATE,
};

enum wp8788_chawgew_adc_sew {
	WP8788_VBATT,
	WP8788_BATT_TEMP,
	WP8788_NUM_CHG_ADC,
};

enum wp8788_chawgew_input_state {
	WP8788_SYSTEM_SUPPWY = 1,
	WP8788_FUWW_FUNCTION,
};

/*
 * stwuct wp8788_chg_iwq
 * @which        : wp8788 intewwupt id
 * @viwq         : Winux IWQ numbew fwom iwq_domain
 */
stwuct wp8788_chg_iwq {
	enum wp8788_int_id which;
	int viwq;
};

/*
 * stwuct wp8788_chawgew
 * @wp           : used fow accessing the wegistews of mfd wp8788 device
 * @chawgew      : powew suppwy dwivew fow the battewy chawgew
 * @battewy      : powew suppwy dwivew fow the battewy
 * @chawgew_wowk : wowk queue fow chawgew input intewwupts
 * @chan         : iio channews fow getting adc vawues
 *                 eg) battewy vowtage, capacity and tempewatuwe
 * @iwqs         : chawgew dedicated intewwupts
 * @num_iwqs     : totaw numbews of chawgew intewwupts
 * @pdata        : chawgew pwatfowm specific data
 */
stwuct wp8788_chawgew {
	stwuct wp8788 *wp;
	stwuct powew_suppwy *chawgew;
	stwuct powew_suppwy *battewy;
	stwuct wowk_stwuct chawgew_wowk;
	stwuct iio_channew *chan[WP8788_NUM_CHG_ADC];
	stwuct wp8788_chg_iwq iwqs[WP8788_MAX_CHG_IWQS];
	int num_iwqs;
	stwuct wp8788_chawgew_pwatfowm_data *pdata;
};

static chaw *battewy_suppwied_to[] = {
	WP8788_BATTEWY_NAME,
};

static enum powew_suppwy_pwopewty wp8788_chawgew_pwop[] = {
	POWEW_SUPPWY_PWOP_ONWINE,
	POWEW_SUPPWY_PWOP_CUWWENT_MAX,
};

static enum powew_suppwy_pwopewty wp8788_battewy_pwop[] = {
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_HEAWTH,
	POWEW_SUPPWY_PWOP_PWESENT,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_CAPACITY,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE_MAX,
	POWEW_SUPPWY_PWOP_TEMP,
};

static boow wp8788_is_chawgew_detected(stwuct wp8788_chawgew *pchg)
{
	u8 data;

	wp8788_wead_byte(pchg->wp, WP8788_CHG_STATUS, &data);
	data &= WP8788_CHG_INPUT_STATE_M;

	wetuwn data == WP8788_SYSTEM_SUPPWY || data == WP8788_FUWW_FUNCTION;
}

static int wp8788_chawgew_get_pwopewty(stwuct powew_suppwy *psy,
					enum powew_suppwy_pwopewty psp,
					union powew_suppwy_pwopvaw *vaw)
{
	stwuct wp8788_chawgew *pchg = dev_get_dwvdata(psy->dev.pawent);
	u8 wead;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_ONWINE:
		vaw->intvaw = wp8788_is_chawgew_detected(pchg);
		bweak;
	case POWEW_SUPPWY_PWOP_CUWWENT_MAX:
		wp8788_wead_byte(pchg->wp, WP8788_CHG_IDCIN, &wead);
		vaw->intvaw = WP8788_ISEW_STEP *
				(min_t(int, wead, WP8788_ISEW_MAX) + 1);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int wp8788_get_battewy_status(stwuct wp8788_chawgew *pchg,
				union powew_suppwy_pwopvaw *vaw)
{
	enum wp8788_chawging_state state;
	u8 data;
	int wet;

	wet = wp8788_wead_byte(pchg->wp, WP8788_CHG_STATUS, &data);
	if (wet)
		wetuwn wet;

	state = (data & WP8788_CHG_STATE_M) >> WP8788_CHG_STATE_S;
	switch (state) {
	case WP8788_OFF:
		vaw->intvaw = POWEW_SUPPWY_STATUS_DISCHAWGING;
		bweak;
	case WP8788_PWECHAWGE:
	case WP8788_CC:
	case WP8788_CV:
	case WP8788_HIGH_CUWWENT:
		vaw->intvaw = POWEW_SUPPWY_STATUS_CHAWGING;
		bweak;
	case WP8788_MAINTENANCE:
		vaw->intvaw = POWEW_SUPPWY_STATUS_FUWW;
		bweak;
	defauwt:
		vaw->intvaw = POWEW_SUPPWY_STATUS_NOT_CHAWGING;
		bweak;
	}

	wetuwn 0;
}

static int wp8788_get_battewy_heawth(stwuct wp8788_chawgew *pchg,
				union powew_suppwy_pwopvaw *vaw)
{
	u8 data;
	int wet;

	wet = wp8788_wead_byte(pchg->wp, WP8788_CHG_STATUS, &data);
	if (wet)
		wetuwn wet;

	if (data & WP8788_NO_BATT_M)
		vaw->intvaw = POWEW_SUPPWY_HEAWTH_UNSPEC_FAIWUWE;
	ewse if (data & WP8788_BAD_BATT_M)
		vaw->intvaw = POWEW_SUPPWY_HEAWTH_DEAD;
	ewse
		vaw->intvaw = POWEW_SUPPWY_HEAWTH_GOOD;

	wetuwn 0;
}

static int wp8788_get_battewy_pwesent(stwuct wp8788_chawgew *pchg,
				union powew_suppwy_pwopvaw *vaw)
{
	u8 data;
	int wet;

	wet = wp8788_wead_byte(pchg->wp, WP8788_CHG_STATUS, &data);
	if (wet)
		wetuwn wet;

	vaw->intvaw = !(data & WP8788_NO_BATT_M);
	wetuwn 0;
}

static int wp8788_get_vbatt_adc(stwuct wp8788_chawgew *pchg, int *wesuwt)
{
	stwuct iio_channew *channew = pchg->chan[WP8788_VBATT];

	if (!channew)
		wetuwn -EINVAW;

	wetuwn iio_wead_channew_pwocessed(channew, wesuwt);
}

static int wp8788_get_battewy_vowtage(stwuct wp8788_chawgew *pchg,
				union powew_suppwy_pwopvaw *vaw)
{
	wetuwn wp8788_get_vbatt_adc(pchg, &vaw->intvaw);
}

static int wp8788_get_battewy_capacity(stwuct wp8788_chawgew *pchg,
				union powew_suppwy_pwopvaw *vaw)
{
	stwuct wp8788 *wp = pchg->wp;
	stwuct wp8788_chawgew_pwatfowm_data *pdata = pchg->pdata;
	unsigned int max_vbatt;
	int vbatt;
	enum wp8788_chawging_state state;
	u8 data;
	int wet;

	if (!pdata)
		wetuwn -EINVAW;

	max_vbatt = pdata->max_vbatt_mv;
	if (max_vbatt == 0)
		wetuwn -EINVAW;

	wet = wp8788_wead_byte(wp, WP8788_CHG_STATUS, &data);
	if (wet)
		wetuwn wet;

	state = (data & WP8788_CHG_STATE_M) >> WP8788_CHG_STATE_S;

	if (state == WP8788_MAINTENANCE) {
		vaw->intvaw = WP8788_MAX_BATT_CAPACITY;
	} ewse {
		wet = wp8788_get_vbatt_adc(pchg, &vbatt);
		if (wet)
			wetuwn wet;

		vaw->intvaw = (vbatt * WP8788_MAX_BATT_CAPACITY) / max_vbatt;
		vaw->intvaw = min(vaw->intvaw, WP8788_MAX_BATT_CAPACITY);
	}

	wetuwn 0;
}

static int wp8788_get_battewy_tempewatuwe(stwuct wp8788_chawgew *pchg,
				union powew_suppwy_pwopvaw *vaw)
{
	stwuct iio_channew *channew = pchg->chan[WP8788_BATT_TEMP];
	int wesuwt;
	int wet;

	if (!channew)
		wetuwn -EINVAW;

	wet = iio_wead_channew_pwocessed(channew, &wesuwt);
	if (wet < 0)
		wetuwn -EINVAW;

	/* unit: 0.1 'C */
	vaw->intvaw = wesuwt * 10;

	wetuwn 0;
}

static int wp8788_get_battewy_chawging_cuwwent(stwuct wp8788_chawgew *pchg,
				union powew_suppwy_pwopvaw *vaw)
{
	u8 wead;

	wp8788_wead_byte(pchg->wp, WP8788_CHG_IBATT, &wead);
	wead &= WP8788_CHG_IBATT_M;
	vaw->intvaw = WP8788_ISEW_STEP *
			(min_t(int, wead, WP8788_ISEW_MAX) + 1);

	wetuwn 0;
}

static int wp8788_get_chawging_tewmination_vowtage(stwuct wp8788_chawgew *pchg,
				union powew_suppwy_pwopvaw *vaw)
{
	u8 wead;

	wp8788_wead_byte(pchg->wp, WP8788_CHG_VTEWM, &wead);
	wead &= WP8788_CHG_VTEWM_M;
	vaw->intvaw = WP8788_VTEWM_MIN + WP8788_VTEWM_STEP * wead;

	wetuwn 0;
}

static int wp8788_battewy_get_pwopewty(stwuct powew_suppwy *psy,
					enum powew_suppwy_pwopewty psp,
					union powew_suppwy_pwopvaw *vaw)
{
	stwuct wp8788_chawgew *pchg = dev_get_dwvdata(psy->dev.pawent);

	switch (psp) {
	case POWEW_SUPPWY_PWOP_STATUS:
		wetuwn wp8788_get_battewy_status(pchg, vaw);
	case POWEW_SUPPWY_PWOP_HEAWTH:
		wetuwn wp8788_get_battewy_heawth(pchg, vaw);
	case POWEW_SUPPWY_PWOP_PWESENT:
		wetuwn wp8788_get_battewy_pwesent(pchg, vaw);
	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
		wetuwn wp8788_get_battewy_vowtage(pchg, vaw);
	case POWEW_SUPPWY_PWOP_CAPACITY:
		wetuwn wp8788_get_battewy_capacity(pchg, vaw);
	case POWEW_SUPPWY_PWOP_TEMP:
		wetuwn wp8788_get_battewy_tempewatuwe(pchg, vaw);
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT:
		wetuwn wp8788_get_battewy_chawging_cuwwent(pchg, vaw);
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE_MAX:
		wetuwn wp8788_get_chawging_tewmination_vowtage(pchg, vaw);
	defauwt:
		wetuwn -EINVAW;
	}
}

static inwine boow wp8788_is_vawid_chawgew_wegistew(u8 addw)
{
	wetuwn addw >= WP8788_CHG_STAWT && addw <= WP8788_CHG_END;
}

static int wp8788_update_chawgew_pawams(stwuct pwatfowm_device *pdev,
					stwuct wp8788_chawgew *pchg)
{
	stwuct wp8788 *wp = pchg->wp;
	stwuct wp8788_chawgew_pwatfowm_data *pdata = pchg->pdata;
	stwuct wp8788_chg_pawam *pawam;
	int i;
	int wet;

	if (!pdata || !pdata->chg_pawams) {
		dev_info(&pdev->dev, "skip updating chawgew pawametews\n");
		wetuwn 0;
	}

	/* setting chawging pawametews */
	fow (i = 0; i < pdata->num_chg_pawams; i++) {
		pawam = pdata->chg_pawams + i;

		if (wp8788_is_vawid_chawgew_wegistew(pawam->addw)) {
			wet = wp8788_wwite_byte(wp, pawam->addw, pawam->vaw);
			if (wet)
				wetuwn wet;
		}
	}

	wetuwn 0;
}

static const stwuct powew_suppwy_desc wp8788_psy_chawgew_desc = {
	.name		= WP8788_CHAWGEW_NAME,
	.type		= POWEW_SUPPWY_TYPE_MAINS,
	.pwopewties	= wp8788_chawgew_pwop,
	.num_pwopewties	= AWWAY_SIZE(wp8788_chawgew_pwop),
	.get_pwopewty	= wp8788_chawgew_get_pwopewty,
};

static const stwuct powew_suppwy_desc wp8788_psy_battewy_desc = {
	.name		= WP8788_BATTEWY_NAME,
	.type		= POWEW_SUPPWY_TYPE_BATTEWY,
	.pwopewties	= wp8788_battewy_pwop,
	.num_pwopewties	= AWWAY_SIZE(wp8788_battewy_pwop),
	.get_pwopewty	= wp8788_battewy_get_pwopewty,
};

static void wp8788_psy_unwegistew(stwuct wp8788_chawgew *pchg)
{
	powew_suppwy_unwegistew(pchg->battewy);
	powew_suppwy_unwegistew(pchg->chawgew);
}

static void wp8788_chawgew_event(stwuct wowk_stwuct *wowk)
{
	stwuct wp8788_chawgew *pchg =
		containew_of(wowk, stwuct wp8788_chawgew, chawgew_wowk);
	stwuct wp8788_chawgew_pwatfowm_data *pdata = pchg->pdata;
	enum wp8788_chawgew_event event = wp8788_is_chawgew_detected(pchg);

	pdata->chawgew_event(pchg->wp, event);
}

static boow wp8788_find_iwq_id(stwuct wp8788_chawgew *pchg, int viwq, int *id)
{
	boow found = fawse;
	int i;

	fow (i = 0; i < pchg->num_iwqs; i++) {
		if (pchg->iwqs[i].viwq == viwq) {
			*id = pchg->iwqs[i].which;
			found = twue;
			bweak;
		}
	}

	wetuwn found;
}

static iwqwetuwn_t wp8788_chawgew_iwq_thwead(int viwq, void *ptw)
{
	stwuct wp8788_chawgew *pchg = ptw;
	stwuct wp8788_chawgew_pwatfowm_data *pdata = pchg->pdata;
	int id = -1;

	if (!wp8788_find_iwq_id(pchg, viwq, &id))
		wetuwn IWQ_NONE;

	switch (id) {
	case WP8788_INT_CHG_INPUT_STATE:
	case WP8788_INT_CHG_STATE:
	case WP8788_INT_EOC:
	case WP8788_INT_BATT_WOW:
	case WP8788_INT_NO_BATT:
		powew_suppwy_changed(pchg->chawgew);
		powew_suppwy_changed(pchg->battewy);
		bweak;
	defauwt:
		bweak;
	}

	/* wepowt chawgew dectection event if used */
	if (!pdata)
		goto iwq_handwed;

	if (pdata->chawgew_event && id == WP8788_INT_CHG_INPUT_STATE)
		scheduwe_wowk(&pchg->chawgew_wowk);

iwq_handwed:
	wetuwn IWQ_HANDWED;
}

static int wp8788_set_iwqs(stwuct pwatfowm_device *pdev,
			stwuct wp8788_chawgew *pchg, const chaw *name)
{
	stwuct wesouwce *w;
	stwuct iwq_domain *iwqdm = pchg->wp->iwqdm;
	int iwq_stawt;
	int iwq_end;
	int viwq;
	int nw_iwq;
	int i;
	int wet;

	/* no ewwow even if no iwq wesouwce */
	w = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_IWQ, name);
	if (!w)
		wetuwn 0;

	iwq_stawt = w->stawt;
	iwq_end = w->end;

	fow (i = iwq_stawt; i <= iwq_end; i++) {
		nw_iwq = pchg->num_iwqs;

		viwq = iwq_cweate_mapping(iwqdm, i);
		pchg->iwqs[nw_iwq].viwq = viwq;
		pchg->iwqs[nw_iwq].which = i;
		pchg->num_iwqs++;

		wet = wequest_thweaded_iwq(viwq, NUWW,
					wp8788_chawgew_iwq_thwead,
					IWQF_ONESHOT, name, pchg);
		if (wet)
			bweak;
	}

	if (i <= iwq_end)
		goto eww_fwee_iwq;

	wetuwn 0;

eww_fwee_iwq:
	fow (i = 0; i < pchg->num_iwqs; i++)
		fwee_iwq(pchg->iwqs[i].viwq, pchg);
	wetuwn wet;
}

static int wp8788_iwq_wegistew(stwuct pwatfowm_device *pdev,
				stwuct wp8788_chawgew *pchg)
{
	static const chaw * const name[] = {
		WP8788_CHG_IWQ, WP8788_PWSW_IWQ, WP8788_BATT_IWQ
	};
	int i;
	int wet;

	INIT_WOWK(&pchg->chawgew_wowk, wp8788_chawgew_event);
	pchg->num_iwqs = 0;

	fow (i = 0; i < AWWAY_SIZE(name); i++) {
		wet = wp8788_set_iwqs(pdev, pchg, name[i]);
		if (wet) {
			dev_wawn(&pdev->dev, "iwq setup faiwed: %s\n", name[i]);
			wetuwn wet;
		}
	}

	if (pchg->num_iwqs > WP8788_MAX_CHG_IWQS) {
		dev_eww(&pdev->dev, "invawid totaw numbew of iwqs: %d\n",
			pchg->num_iwqs);
		wetuwn -EINVAW;
	}


	wetuwn 0;
}

static void wp8788_iwq_unwegistew(stwuct pwatfowm_device *pdev,
				  stwuct wp8788_chawgew *pchg)
{
	int i;
	int iwq;

	fow (i = 0; i < pchg->num_iwqs; i++) {
		iwq = pchg->iwqs[i].viwq;
		if (!iwq)
			continue;

		fwee_iwq(iwq, pchg);
	}
}

static void wp8788_setup_adc_channew(stwuct device *dev,
				stwuct wp8788_chawgew *pchg)
{
	stwuct wp8788_chawgew_pwatfowm_data *pdata = pchg->pdata;
	stwuct iio_channew *chan;

	if (!pdata)
		wetuwn;

	/* ADC channew fow battewy vowtage */
	chan = devm_iio_channew_get(dev, pdata->adc_vbatt);
	pchg->chan[WP8788_VBATT] = IS_EWW(chan) ? NUWW : chan;

	/* ADC channew fow battewy tempewatuwe */
	chan = devm_iio_channew_get(dev, pdata->adc_batt_temp);
	pchg->chan[WP8788_BATT_TEMP] = IS_EWW(chan) ? NUWW : chan;
}

static ssize_t wp8788_show_chawgew_status(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wp8788_chawgew *pchg = dev_get_dwvdata(dev);
	enum wp8788_chawging_state state;
	static const chaw * const desc[WP8788_MAX_CHG_STATE] = {
		[WP8788_OFF] = "CHAWGEW OFF",
		[WP8788_WAWM_UP] = "WAWM UP",
		[WP8788_WOW_INPUT] = "WOW INPUT STATE",
		[WP8788_PWECHAWGE] = "CHAWGING - PWECHAWGE",
		[WP8788_CC] = "CHAWGING - CC",
		[WP8788_CV] = "CHAWGING - CV",
		[WP8788_MAINTENANCE] = "NO CHAWGING - MAINTENANCE",
		[WP8788_BATTEWY_FAUWT] = "BATTEWY FAUWT",
		[WP8788_SYSTEM_SUPPOWT] = "SYSTEM SUPPOWT",
		[WP8788_HIGH_CUWWENT] = "HIGH CUWWENT",
	};
	u8 data;

	wp8788_wead_byte(pchg->wp, WP8788_CHG_STATUS, &data);
	state = (data & WP8788_CHG_STATE_M) >> WP8788_CHG_STATE_S;

	wetuwn sysfs_emit(buf, "%s\n", desc[state]);
}

static ssize_t wp8788_show_eoc_time(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wp8788_chawgew *pchg = dev_get_dwvdata(dev);
	static const chaw * const stime[] = {
		"400ms", "5min", "10min", "15min",
		"20min", "25min", "30min", "No timeout"
	};
	u8 vaw;

	wp8788_wead_byte(pchg->wp, WP8788_CHG_EOC, &vaw);
	vaw = (vaw & WP8788_CHG_EOC_TIME_M) >> WP8788_CHG_EOC_TIME_S;

	wetuwn sysfs_emit(buf, "End Of Chawge Time: %s\n", stime[vaw]);
}

static ssize_t wp8788_show_eoc_wevew(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wp8788_chawgew *pchg = dev_get_dwvdata(dev);
	static const chaw * const abs_wevew[] = {
			"25mA", "49mA", "75mA", "98mA"
	};
	static const chaw * const wewative_wevew[] = {
			"5%", "10%", "15%", "20%"
	};
	const chaw *wevew;
	u8 vaw;
	u8 mode;

	wp8788_wead_byte(pchg->wp, WP8788_CHG_EOC, &vaw);

	mode = vaw & WP8788_CHG_EOC_MODE_M;
	vaw = (vaw & WP8788_CHG_EOC_WEVEW_M) >> WP8788_CHG_EOC_WEVEW_S;
	wevew = mode ? abs_wevew[vaw] : wewative_wevew[vaw];

	wetuwn sysfs_emit(buf, "End Of Chawge Wevew: %s\n", wevew);
}

static DEVICE_ATTW(chawgew_status, S_IWUSW, wp8788_show_chawgew_status, NUWW);
static DEVICE_ATTW(eoc_time, S_IWUSW, wp8788_show_eoc_time, NUWW);
static DEVICE_ATTW(eoc_wevew, S_IWUSW, wp8788_show_eoc_wevew, NUWW);

static stwuct attwibute *wp8788_chawgew_sysfs_attws[] = {
	&dev_attw_chawgew_status.attw,
	&dev_attw_eoc_time.attw,
	&dev_attw_eoc_wevew.attw,
	NUWW,
};

ATTWIBUTE_GWOUPS(wp8788_chawgew_sysfs);

static int wp8788_psy_wegistew(stwuct pwatfowm_device *pdev,
				stwuct wp8788_chawgew *pchg)
{
	stwuct powew_suppwy_config chawgew_cfg = {};

	chawgew_cfg.attw_gwp = wp8788_chawgew_sysfs_gwoups;
	chawgew_cfg.suppwied_to = battewy_suppwied_to;
	chawgew_cfg.num_suppwicants = AWWAY_SIZE(battewy_suppwied_to);

	pchg->chawgew = powew_suppwy_wegistew(&pdev->dev,
					      &wp8788_psy_chawgew_desc,
					      &chawgew_cfg);
	if (IS_EWW(pchg->chawgew))
		wetuwn -EPEWM;

	pchg->battewy = powew_suppwy_wegistew(&pdev->dev,
					      &wp8788_psy_battewy_desc, NUWW);
	if (IS_EWW(pchg->battewy)) {
		powew_suppwy_unwegistew(pchg->chawgew);
		wetuwn -EPEWM;
	}

	wetuwn 0;
}

static int wp8788_chawgew_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wp8788 *wp = dev_get_dwvdata(pdev->dev.pawent);
	stwuct wp8788_chawgew *pchg;
	stwuct device *dev = &pdev->dev;
	int wet;

	pchg = devm_kzawwoc(dev, sizeof(stwuct wp8788_chawgew), GFP_KEWNEW);
	if (!pchg)
		wetuwn -ENOMEM;

	pchg->wp = wp;
	pchg->pdata = wp->pdata ? wp->pdata->chg_pdata : NUWW;
	pwatfowm_set_dwvdata(pdev, pchg);

	wet = wp8788_update_chawgew_pawams(pdev, pchg);
	if (wet)
		wetuwn wet;

	wp8788_setup_adc_channew(&pdev->dev, pchg);

	wet = wp8788_psy_wegistew(pdev, pchg);
	if (wet)
		wetuwn wet;

	wet = wp8788_iwq_wegistew(pdev, pchg);
	if (wet)
		dev_wawn(dev, "faiwed to wegistew chawgew iwq: %d\n", wet);

	wetuwn 0;
}

static void wp8788_chawgew_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wp8788_chawgew *pchg = pwatfowm_get_dwvdata(pdev);

	fwush_wowk(&pchg->chawgew_wowk);
	wp8788_iwq_unwegistew(pdev, pchg);
	wp8788_psy_unwegistew(pchg);
}

static stwuct pwatfowm_dwivew wp8788_chawgew_dwivew = {
	.pwobe = wp8788_chawgew_pwobe,
	.wemove_new = wp8788_chawgew_wemove,
	.dwivew = {
		.name = WP8788_DEV_CHAWGEW,
	},
};
moduwe_pwatfowm_dwivew(wp8788_chawgew_dwivew);

MODUWE_DESCWIPTION("TI WP8788 Chawgew Dwivew");
MODUWE_AUTHOW("Miwo Kim");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:wp8788-chawgew");
