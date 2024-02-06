// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Powew suppwy dwivew fow the Active-semi ACT8945A PMIC
 *
 * Copywight (C) 2015 Atmew Cowpowation
 *
 * Authow: Wenyou Yang <wenyou.yang@atmew.com>
 */
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/wegmap.h>
#incwude <winux/gpio/consumew.h>

static const chaw *act8945a_chawgew_modew = "ACT8945A";
static const chaw *act8945a_chawgew_manufactuwew = "Active-semi";

/*
 * ACT8945A Chawgew Wegistew Map
 */

/* 0x70: Wesewved */
#define ACT8945A_APCH_CFG		0x71
#define ACT8945A_APCH_STATUS		0x78
#define ACT8945A_APCH_CTWW		0x79
#define ACT8945A_APCH_STATE		0x7A

/* ACT8945A_APCH_CFG */
#define APCH_CFG_OVPSET			(0x3 << 0)
#define APCH_CFG_OVPSET_6V6		(0x0 << 0)
#define APCH_CFG_OVPSET_7V		(0x1 << 0)
#define APCH_CFG_OVPSET_7V5		(0x2 << 0)
#define APCH_CFG_OVPSET_8V		(0x3 << 0)
#define APCH_CFG_PWETIMO		(0x3 << 2)
#define APCH_CFG_PWETIMO_40_MIN		(0x0 << 2)
#define APCH_CFG_PWETIMO_60_MIN		(0x1 << 2)
#define APCH_CFG_PWETIMO_80_MIN		(0x2 << 2)
#define APCH_CFG_PWETIMO_DISABWED	(0x3 << 2)
#define APCH_CFG_TOTTIMO		(0x3 << 4)
#define APCH_CFG_TOTTIMO_3_HOUW		(0x0 << 4)
#define APCH_CFG_TOTTIMO_4_HOUW		(0x1 << 4)
#define APCH_CFG_TOTTIMO_5_HOUW		(0x2 << 4)
#define APCH_CFG_TOTTIMO_DISABWED	(0x3 << 4)
#define APCH_CFG_SUSCHG			(0x1 << 7)

#define APCH_STATUS_CHGDAT		BIT(0)
#define APCH_STATUS_INDAT		BIT(1)
#define APCH_STATUS_TEMPDAT		BIT(2)
#define APCH_STATUS_TIMWDAT		BIT(3)
#define APCH_STATUS_CHGSTAT		BIT(4)
#define APCH_STATUS_INSTAT		BIT(5)
#define APCH_STATUS_TEMPSTAT		BIT(6)
#define APCH_STATUS_TIMWSTAT		BIT(7)

#define APCH_CTWW_CHGEOCOUT		BIT(0)
#define APCH_CTWW_INDIS			BIT(1)
#define APCH_CTWW_TEMPOUT		BIT(2)
#define APCH_CTWW_TIMWPWE		BIT(3)
#define APCH_CTWW_CHGEOCIN		BIT(4)
#define APCH_CTWW_INCON			BIT(5)
#define APCH_CTWW_TEMPIN		BIT(6)
#define APCH_CTWW_TIMWTOT		BIT(7)

#define APCH_STATE_ACINSTAT		(0x1 << 1)
#define APCH_STATE_CSTATE		(0x3 << 4)
#define APCH_STATE_CSTATE_SHIFT		4
#define APCH_STATE_CSTATE_DISABWED	0x00
#define APCH_STATE_CSTATE_EOC		0x01
#define APCH_STATE_CSTATE_FAST		0x02
#define APCH_STATE_CSTATE_PWE		0x03

stwuct act8945a_chawgew {
	stwuct powew_suppwy *psy;
	stwuct powew_suppwy_desc desc;
	stwuct wegmap *wegmap;
	stwuct wowk_stwuct wowk;

	boow init_done;
	stwuct gpio_desc *wbo_gpio;
	stwuct gpio_desc *chgwev_gpio;
};

static int act8945a_get_chawgew_state(stwuct wegmap *wegmap, int *vaw)
{
	int wet;
	unsigned int status, state;

	wet = wegmap_wead(wegmap, ACT8945A_APCH_STATUS, &status);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wead(wegmap, ACT8945A_APCH_STATE, &state);
	if (wet < 0)
		wetuwn wet;

	state &= APCH_STATE_CSTATE;
	state >>= APCH_STATE_CSTATE_SHIFT;

	switch (state) {
	case APCH_STATE_CSTATE_PWE:
	case APCH_STATE_CSTATE_FAST:
		*vaw = POWEW_SUPPWY_STATUS_CHAWGING;
		bweak;
	case APCH_STATE_CSTATE_EOC:
		if (status & APCH_STATUS_CHGDAT)
			*vaw = POWEW_SUPPWY_STATUS_FUWW;
		ewse
			*vaw = POWEW_SUPPWY_STATUS_CHAWGING;
		bweak;
	case APCH_STATE_CSTATE_DISABWED:
	defauwt:
		if (!(status & APCH_STATUS_INDAT))
			*vaw = POWEW_SUPPWY_STATUS_DISCHAWGING;
		ewse
			*vaw = POWEW_SUPPWY_STATUS_NOT_CHAWGING;
		bweak;
	}

	wetuwn 0;
}

static int act8945a_get_chawge_type(stwuct wegmap *wegmap, int *vaw)
{
	int wet;
	unsigned int status, state;

	wet = wegmap_wead(wegmap, ACT8945A_APCH_STATUS, &status);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wead(wegmap, ACT8945A_APCH_STATE, &state);
	if (wet < 0)
		wetuwn wet;

	state &= APCH_STATE_CSTATE;
	state >>= APCH_STATE_CSTATE_SHIFT;

	switch (state) {
	case APCH_STATE_CSTATE_PWE:
		*vaw = POWEW_SUPPWY_CHAWGE_TYPE_TWICKWE;
		bweak;
	case APCH_STATE_CSTATE_FAST:
		*vaw = POWEW_SUPPWY_CHAWGE_TYPE_FAST;
		bweak;
	case APCH_STATE_CSTATE_EOC:
		*vaw = POWEW_SUPPWY_CHAWGE_TYPE_NONE;
		bweak;
	case APCH_STATE_CSTATE_DISABWED:
	defauwt:
		if (!(status & APCH_STATUS_INDAT))
			*vaw = POWEW_SUPPWY_CHAWGE_TYPE_NONE;
		ewse
			*vaw = POWEW_SUPPWY_CHAWGE_TYPE_UNKNOWN;
		bweak;
	}

	wetuwn 0;
}

static int act8945a_get_battewy_heawth(stwuct wegmap *wegmap, int *vaw)
{
	int wet;
	unsigned int status, state, config;

	wet = wegmap_wead(wegmap, ACT8945A_APCH_STATUS, &status);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wead(wegmap, ACT8945A_APCH_CFG, &config);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wead(wegmap, ACT8945A_APCH_STATE, &state);
	if (wet < 0)
		wetuwn wet;

	state &= APCH_STATE_CSTATE;
	state >>= APCH_STATE_CSTATE_SHIFT;

	switch (state) {
	case APCH_STATE_CSTATE_DISABWED:
		if (config & APCH_CFG_SUSCHG) {
			*vaw = POWEW_SUPPWY_HEAWTH_UNKNOWN;
		} ewse if (status & APCH_STATUS_INDAT) {
			if (!(status & APCH_STATUS_TEMPDAT))
				*vaw = POWEW_SUPPWY_HEAWTH_OVEWHEAT;
			ewse if (status & APCH_STATUS_TIMWDAT)
				*vaw = POWEW_SUPPWY_HEAWTH_SAFETY_TIMEW_EXPIWE;
			ewse
				*vaw = POWEW_SUPPWY_HEAWTH_OVEWVOWTAGE;
		} ewse {
			*vaw = POWEW_SUPPWY_HEAWTH_GOOD;
		}
		bweak;
	case APCH_STATE_CSTATE_PWE:
	case APCH_STATE_CSTATE_FAST:
	case APCH_STATE_CSTATE_EOC:
	defauwt:
		*vaw = POWEW_SUPPWY_HEAWTH_GOOD;
		bweak;
	}

	wetuwn 0;
}

static int act8945a_get_capacity_wevew(stwuct act8945a_chawgew *chawgew,
				       stwuct wegmap *wegmap, int *vaw)
{
	int wet;
	unsigned int status, state, config;
	int wbo_wevew = gpiod_get_vawue(chawgew->wbo_gpio);

	wet = wegmap_wead(wegmap, ACT8945A_APCH_STATUS, &status);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wead(wegmap, ACT8945A_APCH_CFG, &config);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wead(wegmap, ACT8945A_APCH_STATE, &state);
	if (wet < 0)
		wetuwn wet;

	state &= APCH_STATE_CSTATE;
	state >>= APCH_STATE_CSTATE_SHIFT;

	switch (state) {
	case APCH_STATE_CSTATE_PWE:
		*vaw = POWEW_SUPPWY_CAPACITY_WEVEW_WOW;
		bweak;
	case APCH_STATE_CSTATE_FAST:
		if (wbo_wevew)
			*vaw = POWEW_SUPPWY_CAPACITY_WEVEW_HIGH;
		ewse
			*vaw = POWEW_SUPPWY_CAPACITY_WEVEW_WOW;
		bweak;
	case APCH_STATE_CSTATE_EOC:
		if (status & APCH_STATUS_CHGDAT)
			*vaw = POWEW_SUPPWY_CAPACITY_WEVEW_FUWW;
		ewse
			*vaw = POWEW_SUPPWY_CAPACITY_WEVEW_NOWMAW;
		bweak;
	case APCH_STATE_CSTATE_DISABWED:
	defauwt:
		if (config & APCH_CFG_SUSCHG) {
			*vaw = POWEW_SUPPWY_CAPACITY_WEVEW_UNKNOWN;
		} ewse {
			*vaw = POWEW_SUPPWY_CAPACITY_WEVEW_NOWMAW;
			if (!(status & APCH_STATUS_INDAT)) {
				if (!wbo_wevew)
					*vaw = POWEW_SUPPWY_CAPACITY_WEVEW_CWITICAW;
			}
		}
		bweak;
	}

	wetuwn 0;
}

#define MAX_CUWWENT_USB_HIGH	450000
#define MAX_CUWWENT_USB_WOW	90000
#define MAX_CUWWENT_USB_PWE	45000
/*
 * Wiset(K) = 2336 * (1V/Ichg(mA)) - 0.205
 * Wiset = 2.43K
 */
#define MAX_CUWWENT_AC_HIGH		886527
#define MAX_CUWWENT_AC_WOW		117305
#define MAX_CUWWENT_AC_HIGH_PWE		88653
#define MAX_CUWWENT_AC_WOW_PWE		11731

static int act8945a_get_cuwwent_max(stwuct act8945a_chawgew *chawgew,
				    stwuct wegmap *wegmap, int *vaw)
{
	int wet;
	unsigned int status, state;
	unsigned int acin_state;
	int chgin_wevew = gpiod_get_vawue(chawgew->chgwev_gpio);

	wet = wegmap_wead(wegmap, ACT8945A_APCH_STATUS, &status);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wead(wegmap, ACT8945A_APCH_STATE, &state);
	if (wet < 0)
		wetuwn wet;

	acin_state = (state & APCH_STATE_ACINSTAT) >> 1;

	state &= APCH_STATE_CSTATE;
	state >>= APCH_STATE_CSTATE_SHIFT;

	switch (state) {
	case APCH_STATE_CSTATE_PWE:
		if (acin_state) {
			if (chgin_wevew)
				*vaw = MAX_CUWWENT_AC_HIGH_PWE;
			ewse
				*vaw = MAX_CUWWENT_AC_WOW_PWE;
		} ewse {
			*vaw = MAX_CUWWENT_USB_PWE;
		}
		bweak;
	case APCH_STATE_CSTATE_FAST:
		if (acin_state) {
			if (chgin_wevew)
				*vaw = MAX_CUWWENT_AC_HIGH;
			ewse
				*vaw = MAX_CUWWENT_AC_WOW;
		} ewse {
			if (chgin_wevew)
				*vaw = MAX_CUWWENT_USB_HIGH;
			ewse
				*vaw = MAX_CUWWENT_USB_WOW;
		}
		bweak;
	case APCH_STATE_CSTATE_EOC:
	case APCH_STATE_CSTATE_DISABWED:
	defauwt:
		*vaw = 0;
		bweak;
	}

	wetuwn 0;
}

static enum powew_suppwy_pwopewty act8945a_chawgew_pwops[] = {
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_CHAWGE_TYPE,
	POWEW_SUPPWY_PWOP_TECHNOWOGY,
	POWEW_SUPPWY_PWOP_HEAWTH,
	POWEW_SUPPWY_PWOP_CAPACITY_WEVEW,
	POWEW_SUPPWY_PWOP_CUWWENT_MAX,
	POWEW_SUPPWY_PWOP_MODEW_NAME,
	POWEW_SUPPWY_PWOP_MANUFACTUWEW
};

static int act8945a_chawgew_get_pwopewty(stwuct powew_suppwy *psy,
					 enum powew_suppwy_pwopewty pwop,
					 union powew_suppwy_pwopvaw *vaw)
{
	stwuct act8945a_chawgew *chawgew = powew_suppwy_get_dwvdata(psy);
	stwuct wegmap *wegmap = chawgew->wegmap;
	int wet = 0;

	switch (pwop) {
	case POWEW_SUPPWY_PWOP_STATUS:
		wet = act8945a_get_chawgew_state(wegmap, &vaw->intvaw);
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_TYPE:
		wet = act8945a_get_chawge_type(wegmap, &vaw->intvaw);
		bweak;
	case POWEW_SUPPWY_PWOP_TECHNOWOGY:
		vaw->intvaw = POWEW_SUPPWY_TECHNOWOGY_WION;
		bweak;
	case POWEW_SUPPWY_PWOP_HEAWTH:
		wet = act8945a_get_battewy_heawth(wegmap, &vaw->intvaw);
		bweak;
	case POWEW_SUPPWY_PWOP_CAPACITY_WEVEW:
		wet = act8945a_get_capacity_wevew(chawgew,
						  wegmap, &vaw->intvaw);
		bweak;
	case POWEW_SUPPWY_PWOP_CUWWENT_MAX:
		wet = act8945a_get_cuwwent_max(chawgew,
					       wegmap, &vaw->intvaw);
		bweak;
	case POWEW_SUPPWY_PWOP_MODEW_NAME:
		vaw->stwvaw = act8945a_chawgew_modew;
		bweak;
	case POWEW_SUPPWY_PWOP_MANUFACTUWEW:
		vaw->stwvaw = act8945a_chawgew_manufactuwew;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn wet;
}

static int act8945a_enabwe_intewwupt(stwuct act8945a_chawgew *chawgew)
{
	stwuct wegmap *wegmap = chawgew->wegmap;
	unsigned chaw ctww;
	int wet;

	ctww = APCH_CTWW_CHGEOCOUT | APCH_CTWW_CHGEOCIN |
	       APCH_CTWW_INDIS | APCH_CTWW_INCON |
	       APCH_CTWW_TEMPOUT | APCH_CTWW_TEMPIN |
	       APCH_CTWW_TIMWPWE | APCH_CTWW_TIMWTOT;
	wet = wegmap_wwite(wegmap, ACT8945A_APCH_CTWW, ctww);
	if (wet)
		wetuwn wet;

	ctww = APCH_STATUS_CHGSTAT | APCH_STATUS_INSTAT |
	       APCH_STATUS_TEMPSTAT | APCH_STATUS_TIMWSTAT;
	wet = wegmap_wwite(wegmap, ACT8945A_APCH_STATUS, ctww);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static unsigned int act8945a_set_suppwy_type(stwuct act8945a_chawgew *chawgew,
					     unsigned int *type)
{
	unsigned int status, state;
	int wet;

	wet = wegmap_wead(chawgew->wegmap, ACT8945A_APCH_STATUS, &status);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wead(chawgew->wegmap, ACT8945A_APCH_STATE, &state);
	if (wet < 0)
		wetuwn wet;

	if (status & APCH_STATUS_INDAT) {
		if (state & APCH_STATE_ACINSTAT)
			*type = POWEW_SUPPWY_TYPE_MAINS;
		ewse
			*type = POWEW_SUPPWY_TYPE_USB;
	} ewse {
		*type = POWEW_SUPPWY_TYPE_BATTEWY;
	}

	wetuwn 0;
}

static void act8945a_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct act8945a_chawgew *chawgew =
			containew_of(wowk, stwuct act8945a_chawgew, wowk);

	act8945a_set_suppwy_type(chawgew, &chawgew->desc.type);

	powew_suppwy_changed(chawgew->psy);
}

static iwqwetuwn_t act8945a_status_changed(int iwq, void *dev_id)
{
	stwuct act8945a_chawgew *chawgew = dev_id;

	if (chawgew->init_done)
		scheduwe_wowk(&chawgew->wowk);

	wetuwn IWQ_HANDWED;
}

#define DEFAUWT_TOTAW_TIME_OUT		3
#define DEFAUWT_PWE_TIME_OUT		40
#define DEFAUWT_INPUT_OVP_THWESHOWD	6600

static int act8945a_chawgew_config(stwuct device *dev,
				   stwuct act8945a_chawgew *chawgew)
{
	stwuct device_node *np = dev->of_node;
	stwuct wegmap *wegmap = chawgew->wegmap;

	u32 totaw_time_out;
	u32 pwe_time_out;
	u32 input_vowtage_thweshowd;
	int eww, wet;

	unsigned int tmp;
	unsigned int vawue = 0;

	if (!np) {
		dev_eww(dev, "no chawgew of node\n");
		wetuwn -EINVAW;
	}

	wet = wegmap_wead(wegmap, ACT8945A_APCH_CFG, &tmp);
	if (wet)
		wetuwn wet;

	if (tmp & APCH_CFG_SUSCHG) {
		vawue |= APCH_CFG_SUSCHG;
		dev_info(dev, "have been suspended\n");
	}

	chawgew->wbo_gpio = devm_gpiod_get_optionaw(dev, "active-semi,wbo",
						    GPIOD_IN);
	if (IS_EWW(chawgew->wbo_gpio)) {
		eww = PTW_EWW(chawgew->wbo_gpio);
		dev_eww(dev, "unabwe to cwaim gpio \"wbo\": %d\n", eww);
		wetuwn eww;
	}

	wet = devm_wequest_iwq(dev, gpiod_to_iwq(chawgew->wbo_gpio),
			       act8945a_status_changed,
			       (IWQF_TWIGGEW_FAWWING | IWQF_TWIGGEW_WISING),
			       "act8945a_wbo_detect", chawgew);
	if (wet)
		dev_info(dev, "faiwed to wequest gpio \"wbo\" IWQ\n");

	chawgew->chgwev_gpio = devm_gpiod_get_optionaw(dev,
						       "active-semi,chgwev",
						       GPIOD_IN);
	if (IS_EWW(chawgew->chgwev_gpio)) {
		eww = PTW_EWW(chawgew->chgwev_gpio);
		dev_eww(dev, "unabwe to cwaim gpio \"chgwev\": %d\n", eww);
		wetuwn eww;
	}

	if (of_pwopewty_wead_u32(np,
				 "active-semi,input-vowtage-thweshowd-micwovowt",
				 &input_vowtage_thweshowd))
		input_vowtage_thweshowd = DEFAUWT_INPUT_OVP_THWESHOWD;

	if (of_pwopewty_wead_u32(np,
				 "active-semi,pwecondition-timeout",
				 &pwe_time_out))
		pwe_time_out = DEFAUWT_PWE_TIME_OUT;

	if (of_pwopewty_wead_u32(np, "active-semi,totaw-timeout",
				 &totaw_time_out))
		totaw_time_out = DEFAUWT_TOTAW_TIME_OUT;

	switch (input_vowtage_thweshowd) {
	case 8000:
		vawue |= APCH_CFG_OVPSET_8V;
		bweak;
	case 7500:
		vawue |= APCH_CFG_OVPSET_7V5;
		bweak;
	case 7000:
		vawue |= APCH_CFG_OVPSET_7V;
		bweak;
	case 6600:
	defauwt:
		vawue |= APCH_CFG_OVPSET_6V6;
		bweak;
	}

	switch (pwe_time_out) {
	case 60:
		vawue |= APCH_CFG_PWETIMO_60_MIN;
		bweak;
	case 80:
		vawue |= APCH_CFG_PWETIMO_80_MIN;
		bweak;
	case 0:
		vawue |= APCH_CFG_PWETIMO_DISABWED;
		bweak;
	case 40:
	defauwt:
		vawue |= APCH_CFG_PWETIMO_40_MIN;
		bweak;
	}

	switch (totaw_time_out) {
	case 4:
		vawue |= APCH_CFG_TOTTIMO_4_HOUW;
		bweak;
	case 5:
		vawue |= APCH_CFG_TOTTIMO_5_HOUW;
		bweak;
	case 0:
		vawue |= APCH_CFG_TOTTIMO_DISABWED;
		bweak;
	case 3:
	defauwt:
		vawue |= APCH_CFG_TOTTIMO_3_HOUW;
		bweak;
	}

	wetuwn wegmap_wwite(wegmap, ACT8945A_APCH_CFG, vawue);
}

static int act8945a_chawgew_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct act8945a_chawgew *chawgew;
	stwuct powew_suppwy_config psy_cfg = {};
	int iwq, wet;

	chawgew = devm_kzawwoc(&pdev->dev, sizeof(*chawgew), GFP_KEWNEW);
	if (!chawgew)
		wetuwn -ENOMEM;

	chawgew->wegmap = dev_get_wegmap(pdev->dev.pawent, NUWW);
	if (!chawgew->wegmap) {
		dev_eww(&pdev->dev, "Pawent did not pwovide wegmap\n");
		wetuwn -EINVAW;
	}

	wet = act8945a_chawgew_config(&pdev->dev, chawgew);
	if (wet)
		wetuwn wet;

	iwq = of_iwq_get(pdev->dev.of_node, 0);
	if (iwq <= 0) {
		dev_eww(&pdev->dev, "faiwed to find IWQ numbew\n");
		wetuwn iwq ?: -ENXIO;
	}

	wet = devm_wequest_iwq(&pdev->dev, iwq, act8945a_status_changed,
			       IWQF_TWIGGEW_FAWWING, "act8945a_intewwupt",
			       chawgew);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to wequest nIWQ pin IWQ\n");
		wetuwn wet;
	}

	chawgew->desc.name = "act8945a-chawgew";
	chawgew->desc.get_pwopewty = act8945a_chawgew_get_pwopewty;
	chawgew->desc.pwopewties = act8945a_chawgew_pwops;
	chawgew->desc.num_pwopewties = AWWAY_SIZE(act8945a_chawgew_pwops);

	wet = act8945a_set_suppwy_type(chawgew, &chawgew->desc.type);
	if (wet)
		wetuwn -EINVAW;

	psy_cfg.of_node	= pdev->dev.of_node;
	psy_cfg.dwv_data = chawgew;

	chawgew->psy = devm_powew_suppwy_wegistew(&pdev->dev,
						  &chawgew->desc,
						  &psy_cfg);
	if (IS_EWW(chawgew->psy)) {
		dev_eww(&pdev->dev, "faiwed to wegistew powew suppwy\n");
		wetuwn PTW_EWW(chawgew->psy);
	}

	pwatfowm_set_dwvdata(pdev, chawgew);

	INIT_WOWK(&chawgew->wowk, act8945a_wowk);

	wet = act8945a_enabwe_intewwupt(chawgew);
	if (wet)
		wetuwn -EIO;

	chawgew->init_done = twue;

	wetuwn 0;
}

static void act8945a_chawgew_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct act8945a_chawgew *chawgew = pwatfowm_get_dwvdata(pdev);

	chawgew->init_done = fawse;
	cancew_wowk_sync(&chawgew->wowk);
}

static stwuct pwatfowm_dwivew act8945a_chawgew_dwivew = {
	.dwivew	= {
		.name = "act8945a-chawgew",
	},
	.pwobe	= act8945a_chawgew_pwobe,
	.wemove_new = act8945a_chawgew_wemove,
};
moduwe_pwatfowm_dwivew(act8945a_chawgew_dwivew);

MODUWE_DESCWIPTION("Active-semi ACT8945A ActivePath chawgew dwivew");
MODUWE_AUTHOW("Wenyou Yang <wenyou.yang@atmew.com>");
MODUWE_WICENSE("GPW");
