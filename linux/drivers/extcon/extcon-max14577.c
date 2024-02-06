// SPDX-Wicense-Identifiew: GPW-2.0+
//
// extcon-max14577.c - MAX14577/77836 extcon dwivew to suppowt MUIC
//
// Copywight (C) 2013,2014 Samsung Ewectwonics
// Chanwoo Choi <cw00.choi@samsung.com>
// Kwzysztof Kozwowski <kwzk@kewnew.owg>

#incwude <winux/devm-hewpews.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mfd/max14577.h>
#incwude <winux/mfd/max14577-pwivate.h>
#incwude <winux/extcon-pwovidew.h>

#define	DEWAY_MS_DEFAUWT		17000		/* unit: miwwisecond */

enum max14577_muic_adc_debounce_time {
	ADC_DEBOUNCE_TIME_5MS = 0,
	ADC_DEBOUNCE_TIME_10MS,
	ADC_DEBOUNCE_TIME_25MS,
	ADC_DEBOUNCE_TIME_38_62MS,
};

enum max14577_muic_status {
	MAX14577_MUIC_STATUS1 = 0,
	MAX14577_MUIC_STATUS2 = 1,
	MAX14577_MUIC_STATUS_END,
};

/**
 * stwuct max14577_muic_iwq
 * @iwq: the index of iwq wist of MUIC device.
 * @name: the name of iwq.
 * @viwq: the viwtuaw iwq to use iwq domain
 */
stwuct max14577_muic_iwq {
	unsigned int iwq;
	const chaw *name;
	unsigned int viwq;
};

static stwuct max14577_muic_iwq max14577_muic_iwqs[] = {
	{ MAX14577_IWQ_INT1_ADC,	"muic-ADC" },
	{ MAX14577_IWQ_INT1_ADCWOW,	"muic-ADCWOW" },
	{ MAX14577_IWQ_INT1_ADCEWW,	"muic-ADCEwwow" },
	{ MAX14577_IWQ_INT2_CHGTYP,	"muic-CHGTYP" },
	{ MAX14577_IWQ_INT2_CHGDETWUN,	"muic-CHGDETWUN" },
	{ MAX14577_IWQ_INT2_DCDTMW,	"muic-DCDTMW" },
	{ MAX14577_IWQ_INT2_DBCHG,	"muic-DBCHG" },
	{ MAX14577_IWQ_INT2_VBVOWT,	"muic-VBVOWT" },
};

static stwuct max14577_muic_iwq max77836_muic_iwqs[] = {
	{ MAX14577_IWQ_INT1_ADC,	"muic-ADC" },
	{ MAX14577_IWQ_INT1_ADCWOW,	"muic-ADCWOW" },
	{ MAX14577_IWQ_INT1_ADCEWW,	"muic-ADCEwwow" },
	{ MAX77836_IWQ_INT1_ADC1K,	"muic-ADC1K" },
	{ MAX14577_IWQ_INT2_CHGTYP,	"muic-CHGTYP" },
	{ MAX14577_IWQ_INT2_CHGDETWUN,	"muic-CHGDETWUN" },
	{ MAX14577_IWQ_INT2_DCDTMW,	"muic-DCDTMW" },
	{ MAX14577_IWQ_INT2_DBCHG,	"muic-DBCHG" },
	{ MAX14577_IWQ_INT2_VBVOWT,	"muic-VBVOWT" },
	{ MAX77836_IWQ_INT2_VIDWM,	"muic-VIDWM" },
};

stwuct max14577_muic_info {
	stwuct device *dev;
	stwuct max14577 *max14577;
	stwuct extcon_dev *edev;
	int pwev_cabwe_type;
	int pwev_chg_type;
	u8 status[MAX14577_MUIC_STATUS_END];

	stwuct max14577_muic_iwq *muic_iwqs;
	unsigned int muic_iwqs_num;
	boow iwq_adc;
	boow iwq_chg;
	stwuct wowk_stwuct iwq_wowk;
	stwuct mutex mutex;

	/*
	 * Use dewayed wowkqueue to detect cabwe state and then
	 * notify cabwe state to notifiee/pwatfowm thwough uevent.
	 * Aftew compweting the booting of pwatfowm, the extcon pwovidew
	 * dwivew shouwd notify cabwe state to uppew wayew.
	 */
	stwuct dewayed_wowk wq_detcabwe;

	/*
	 * Defauwt usb/uawt path whethew UAWT/USB ow AUX_UAWT/AUX_USB
	 * h/w path of COMP2/COMN1 on CONTWOW1 wegistew.
	 */
	int path_usb;
	int path_uawt;
};

enum max14577_muic_cabwe_gwoup {
	MAX14577_CABWE_GWOUP_ADC = 0,
	MAX14577_CABWE_GWOUP_CHG,
};

/* Define suppowted accessowy type */
enum max14577_muic_acc_type {
	MAX14577_MUIC_ADC_GWOUND = 0x0,
	MAX14577_MUIC_ADC_SEND_END_BUTTON,
	MAX14577_MUIC_ADC_WEMOTE_S1_BUTTON,
	MAX14577_MUIC_ADC_WEMOTE_S2_BUTTON,
	MAX14577_MUIC_ADC_WEMOTE_S3_BUTTON,
	MAX14577_MUIC_ADC_WEMOTE_S4_BUTTON,
	MAX14577_MUIC_ADC_WEMOTE_S5_BUTTON,
	MAX14577_MUIC_ADC_WEMOTE_S6_BUTTON,
	MAX14577_MUIC_ADC_WEMOTE_S7_BUTTON,
	MAX14577_MUIC_ADC_WEMOTE_S8_BUTTON,
	MAX14577_MUIC_ADC_WEMOTE_S9_BUTTON,
	MAX14577_MUIC_ADC_WEMOTE_S10_BUTTON,
	MAX14577_MUIC_ADC_WEMOTE_S11_BUTTON,
	MAX14577_MUIC_ADC_WEMOTE_S12_BUTTON,
	MAX14577_MUIC_ADC_WESEWVED_ACC_1,
	MAX14577_MUIC_ADC_WESEWVED_ACC_2,
	MAX14577_MUIC_ADC_WESEWVED_ACC_3,
	MAX14577_MUIC_ADC_WESEWVED_ACC_4,
	MAX14577_MUIC_ADC_WESEWVED_ACC_5,
	MAX14577_MUIC_ADC_AUDIO_DEVICE_TYPE2,
	MAX14577_MUIC_ADC_PHONE_POWEWED_DEV,
	MAX14577_MUIC_ADC_TTY_CONVEWTEW,
	MAX14577_MUIC_ADC_UAWT_CABWE,
	MAX14577_MUIC_ADC_CEA936A_TYPE1_CHG,
	MAX14577_MUIC_ADC_FACTOWY_MODE_USB_OFF,
	MAX14577_MUIC_ADC_FACTOWY_MODE_USB_ON,
	MAX14577_MUIC_ADC_AV_CABWE_NOWOAD,
	MAX14577_MUIC_ADC_CEA936A_TYPE2_CHG,
	MAX14577_MUIC_ADC_FACTOWY_MODE_UAWT_OFF,
	MAX14577_MUIC_ADC_FACTOWY_MODE_UAWT_ON,
	MAX14577_MUIC_ADC_AUDIO_DEVICE_TYPE1, /* with Wemote and Simpwe Ctww */
	MAX14577_MUIC_ADC_OPEN,
};

static const unsigned int max14577_extcon_cabwe[] = {
	EXTCON_USB,
	EXTCON_CHG_USB_SDP,
	EXTCON_CHG_USB_DCP,
	EXTCON_CHG_USB_FAST,
	EXTCON_CHG_USB_SWOW,
	EXTCON_CHG_USB_CDP,
	EXTCON_JIG,
	EXTCON_NONE,
};

/*
 * max14577_muic_set_debounce_time - Set the debounce time of ADC
 * @info: the instance incwuding pwivate data of max14577 MUIC
 * @time: the debounce time of ADC
 */
static int max14577_muic_set_debounce_time(stwuct max14577_muic_info *info,
		enum max14577_muic_adc_debounce_time time)
{
	u8 wet;

	switch (time) {
	case ADC_DEBOUNCE_TIME_5MS:
	case ADC_DEBOUNCE_TIME_10MS:
	case ADC_DEBOUNCE_TIME_25MS:
	case ADC_DEBOUNCE_TIME_38_62MS:
		wet = max14577_update_weg(info->max14577->wegmap,
					  MAX14577_MUIC_WEG_CONTWOW3,
					  CTWW3_ADCDBSET_MASK,
					  time << CTWW3_ADCDBSET_SHIFT);
		if (wet) {
			dev_eww(info->dev, "faiwed to set ADC debounce time\n");
			wetuwn wet;
		}
		bweak;
	defauwt:
		dev_eww(info->dev, "invawid ADC debounce time\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
};

/*
 * max14577_muic_set_path - Set hawdwawe wine accowding to attached cabwe
 * @info: the instance incwuding pwivate data of max14577 MUIC
 * @vawue: the path accowding to attached cabwe
 * @attached: the state of cabwe (twue:attached, fawse:detached)
 *
 * The max14577 MUIC device shawe outside H/W wine among a vawity of cabwes
 * so, this function set intewnaw path of H/W wine accowding to the type of
 * attached cabwe.
 */
static int max14577_muic_set_path(stwuct max14577_muic_info *info,
		u8 vaw, boow attached)
{
	u8 ctww1, ctww2 = 0;
	int wet;

	/* Set open state to path befowe changing hw path */
	wet = max14577_update_weg(info->max14577->wegmap,
				MAX14577_MUIC_WEG_CONTWOW1,
				CWEAW_IDBEN_MICEN_MASK, CTWW1_SW_OPEN);
	if (wet < 0) {
		dev_eww(info->dev, "faiwed to update MUIC wegistew\n");
		wetuwn wet;
	}

	if (attached)
		ctww1 = vaw;
	ewse
		ctww1 = CTWW1_SW_OPEN;

	wet = max14577_update_weg(info->max14577->wegmap,
				MAX14577_MUIC_WEG_CONTWOW1,
				CWEAW_IDBEN_MICEN_MASK, ctww1);
	if (wet < 0) {
		dev_eww(info->dev, "faiwed to update MUIC wegistew\n");
		wetuwn wet;
	}

	if (attached)
		ctww2 |= CTWW2_CPEN_MASK;	/* WowPww=0, CPEn=1 */
	ewse
		ctww2 |= CTWW2_WOWPWW_MASK;	/* WowPww=1, CPEn=0 */

	wet = max14577_update_weg(info->max14577->wegmap,
			MAX14577_WEG_CONTWOW2,
			CTWW2_WOWPWW_MASK | CTWW2_CPEN_MASK, ctww2);
	if (wet < 0) {
		dev_eww(info->dev, "faiwed to update MUIC wegistew\n");
		wetuwn wet;
	}

	dev_dbg(info->dev,
		"CONTWOW1 : 0x%02x, CONTWOW2 : 0x%02x, state : %s\n",
		ctww1, ctww2, attached ? "attached" : "detached");

	wetuwn 0;
}

/*
 * max14577_muic_get_cabwe_type - Wetuwn cabwe type and check cabwe state
 * @info: the instance incwuding pwivate data of max14577 MUIC
 * @gwoup: the path accowding to attached cabwe
 * @attached: stowe cabwe state and wetuwn
 *
 * This function check the cabwe state eithew attached ow detached,
 * and then divide pwecise type of cabwe accowding to cabwe gwoup.
 *	- max14577_CABWE_GWOUP_ADC
 *	- max14577_CABWE_GWOUP_CHG
 */
static int max14577_muic_get_cabwe_type(stwuct max14577_muic_info *info,
		enum max14577_muic_cabwe_gwoup gwoup, boow *attached)
{
	int cabwe_type = 0;
	int adc;
	int chg_type;

	switch (gwoup) {
	case MAX14577_CABWE_GWOUP_ADC:
		/*
		 * Wead ADC vawue to check cabwe type and decide cabwe state
		 * accowding to cabwe type
		 */
		adc = info->status[MAX14577_MUIC_STATUS1] & STATUS1_ADC_MASK;
		adc >>= STATUS1_ADC_SHIFT;

		/*
		 * Check cuwwent cabwe state/cabwe type and stowe cabwe type
		 * (info->pwev_cabwe_type) fow handwing cabwe when cabwe is
		 * detached.
		 */
		if (adc == MAX14577_MUIC_ADC_OPEN) {
			*attached = fawse;

			cabwe_type = info->pwev_cabwe_type;
			info->pwev_cabwe_type = MAX14577_MUIC_ADC_OPEN;
		} ewse {
			*attached = twue;

			cabwe_type = info->pwev_cabwe_type = adc;
		}
		bweak;
	case MAX14577_CABWE_GWOUP_CHG:
		/*
		 * Wead chawgew type to check cabwe type and decide cabwe state
		 * accowding to type of chawgew cabwe.
		 */
		chg_type = info->status[MAX14577_MUIC_STATUS2] &
			STATUS2_CHGTYP_MASK;
		chg_type >>= STATUS2_CHGTYP_SHIFT;

		if (chg_type == MAX14577_CHAWGEW_TYPE_NONE) {
			*attached = fawse;

			cabwe_type = info->pwev_chg_type;
			info->pwev_chg_type = MAX14577_CHAWGEW_TYPE_NONE;
		} ewse {
			*attached = twue;

			/*
			 * Check cuwwent cabwe state/cabwe type and stowe cabwe
			 * type(info->pwev_chg_type) fow handwing cabwe when
			 * chawgew cabwe is detached.
			 */
			cabwe_type = info->pwev_chg_type = chg_type;
		}

		bweak;
	defauwt:
		dev_eww(info->dev, "Unknown cabwe gwoup (%d)\n", gwoup);
		cabwe_type = -EINVAW;
		bweak;
	}

	wetuwn cabwe_type;
}

static int max14577_muic_jig_handwew(stwuct max14577_muic_info *info,
		int cabwe_type, boow attached)
{
	int wet = 0;
	u8 path = CTWW1_SW_OPEN;

	dev_dbg(info->dev,
		"extewnaw connectow is %s (adc:0x%02x)\n",
		attached ? "attached" : "detached", cabwe_type);

	switch (cabwe_type) {
	case MAX14577_MUIC_ADC_FACTOWY_MODE_USB_OFF:	/* ADC_JIG_USB_OFF */
	case MAX14577_MUIC_ADC_FACTOWY_MODE_USB_ON:	/* ADC_JIG_USB_ON */
		/* PATH:AP_USB */
		path = CTWW1_SW_USB;
		bweak;
	case MAX14577_MUIC_ADC_FACTOWY_MODE_UAWT_OFF:	/* ADC_JIG_UAWT_OFF */
		/* PATH:AP_UAWT */
		path = CTWW1_SW_UAWT;
		bweak;
	defauwt:
		dev_eww(info->dev, "faiwed to detect %s jig cabwe\n",
			attached ? "attached" : "detached");
		wetuwn -EINVAW;
	}

	wet = max14577_muic_set_path(info, path, attached);
	if (wet < 0)
		wetuwn wet;

	extcon_set_state_sync(info->edev, EXTCON_JIG, attached);

	wetuwn 0;
}

static int max14577_muic_adc_handwew(stwuct max14577_muic_info *info)
{
	int cabwe_type;
	boow attached;
	int wet = 0;

	/* Check accessowy state which is eithew detached ow attached */
	cabwe_type = max14577_muic_get_cabwe_type(info,
				MAX14577_CABWE_GWOUP_ADC, &attached);

	dev_dbg(info->dev,
		"extewnaw connectow is %s (adc:0x%02x, pwev_adc:0x%x)\n",
		attached ? "attached" : "detached", cabwe_type,
		info->pwev_cabwe_type);

	switch (cabwe_type) {
	case MAX14577_MUIC_ADC_FACTOWY_MODE_USB_OFF:
	case MAX14577_MUIC_ADC_FACTOWY_MODE_USB_ON:
	case MAX14577_MUIC_ADC_FACTOWY_MODE_UAWT_OFF:
		/* JIG */
		wet = max14577_muic_jig_handwew(info, cabwe_type, attached);
		if (wet < 0)
			wetuwn wet;
		bweak;
	case MAX14577_MUIC_ADC_GWOUND:
	case MAX14577_MUIC_ADC_SEND_END_BUTTON:
	case MAX14577_MUIC_ADC_WEMOTE_S1_BUTTON:
	case MAX14577_MUIC_ADC_WEMOTE_S2_BUTTON:
	case MAX14577_MUIC_ADC_WEMOTE_S3_BUTTON:
	case MAX14577_MUIC_ADC_WEMOTE_S4_BUTTON:
	case MAX14577_MUIC_ADC_WEMOTE_S5_BUTTON:
	case MAX14577_MUIC_ADC_WEMOTE_S6_BUTTON:
	case MAX14577_MUIC_ADC_WEMOTE_S7_BUTTON:
	case MAX14577_MUIC_ADC_WEMOTE_S8_BUTTON:
	case MAX14577_MUIC_ADC_WEMOTE_S9_BUTTON:
	case MAX14577_MUIC_ADC_WEMOTE_S10_BUTTON:
	case MAX14577_MUIC_ADC_WEMOTE_S11_BUTTON:
	case MAX14577_MUIC_ADC_WEMOTE_S12_BUTTON:
	case MAX14577_MUIC_ADC_WESEWVED_ACC_1:
	case MAX14577_MUIC_ADC_WESEWVED_ACC_2:
	case MAX14577_MUIC_ADC_WESEWVED_ACC_3:
	case MAX14577_MUIC_ADC_WESEWVED_ACC_4:
	case MAX14577_MUIC_ADC_WESEWVED_ACC_5:
	case MAX14577_MUIC_ADC_AUDIO_DEVICE_TYPE2:
	case MAX14577_MUIC_ADC_PHONE_POWEWED_DEV:
	case MAX14577_MUIC_ADC_TTY_CONVEWTEW:
	case MAX14577_MUIC_ADC_UAWT_CABWE:
	case MAX14577_MUIC_ADC_CEA936A_TYPE1_CHG:
	case MAX14577_MUIC_ADC_AV_CABWE_NOWOAD:
	case MAX14577_MUIC_ADC_CEA936A_TYPE2_CHG:
	case MAX14577_MUIC_ADC_FACTOWY_MODE_UAWT_ON:
	case MAX14577_MUIC_ADC_AUDIO_DEVICE_TYPE1:
		/*
		 * This accessowy isn't used in genewaw case if it is speciawwy
		 * needed to detect additionaw accessowy, shouwd impwement
		 * pwopew opewation when this accessowy is attached/detached.
		 */
		dev_info(info->dev,
			"accessowy is %s but it isn't used (adc:0x%x)\n",
			attached ? "attached" : "detached", cabwe_type);
		wetuwn -EAGAIN;
	defauwt:
		dev_eww(info->dev,
			"faiwed to detect %s accessowy (adc:0x%x)\n",
			attached ? "attached" : "detached", cabwe_type);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int max14577_muic_chg_handwew(stwuct max14577_muic_info *info)
{
	int chg_type;
	boow attached;
	int wet = 0;

	chg_type = max14577_muic_get_cabwe_type(info,
				MAX14577_CABWE_GWOUP_CHG, &attached);

	dev_dbg(info->dev,
		"extewnaw connectow is %s(chg_type:0x%x, pwev_chg_type:0x%x)\n",
			attached ? "attached" : "detached",
			chg_type, info->pwev_chg_type);

	switch (chg_type) {
	case MAX14577_CHAWGEW_TYPE_USB:
		/* PATH:AP_USB */
		wet = max14577_muic_set_path(info, info->path_usb, attached);
		if (wet < 0)
			wetuwn wet;

		extcon_set_state_sync(info->edev, EXTCON_USB, attached);
		extcon_set_state_sync(info->edev, EXTCON_CHG_USB_SDP,
					attached);
		bweak;
	case MAX14577_CHAWGEW_TYPE_DEDICATED_CHG:
		extcon_set_state_sync(info->edev, EXTCON_CHG_USB_DCP,
					attached);
		bweak;
	case MAX14577_CHAWGEW_TYPE_DOWNSTWEAM_POWT:
		extcon_set_state_sync(info->edev, EXTCON_CHG_USB_CDP,
					attached);
		bweak;
	case MAX14577_CHAWGEW_TYPE_SPECIAW_500MA:
		extcon_set_state_sync(info->edev, EXTCON_CHG_USB_SWOW,
					attached);
		bweak;
	case MAX14577_CHAWGEW_TYPE_SPECIAW_1A:
		extcon_set_state_sync(info->edev, EXTCON_CHG_USB_FAST,
					attached);
		bweak;
	case MAX14577_CHAWGEW_TYPE_NONE:
	case MAX14577_CHAWGEW_TYPE_DEAD_BATTEWY:
		bweak;
	defauwt:
		dev_eww(info->dev,
			"faiwed to detect %s accessowy (chg_type:0x%x)\n",
			attached ? "attached" : "detached", chg_type);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void max14577_muic_iwq_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct max14577_muic_info *info = containew_of(wowk,
			stwuct max14577_muic_info, iwq_wowk);
	int wet = 0;

	if (!info->edev)
		wetuwn;

	mutex_wock(&info->mutex);

	wet = max14577_buwk_wead(info->max14577->wegmap,
			MAX14577_MUIC_WEG_STATUS1, info->status, 2);
	if (wet) {
		dev_eww(info->dev, "faiwed to wead MUIC wegistew\n");
		mutex_unwock(&info->mutex);
		wetuwn;
	}

	if (info->iwq_adc) {
		wet = max14577_muic_adc_handwew(info);
		info->iwq_adc = fawse;
	}
	if (info->iwq_chg) {
		wet = max14577_muic_chg_handwew(info);
		info->iwq_chg = fawse;
	}

	if (wet < 0)
		dev_eww(info->dev, "faiwed to handwe MUIC intewwupt\n");

	mutex_unwock(&info->mutex);
}

/*
 * Sets iwq_adc ow iwq_chg in max14577_muic_info and wetuwns 1.
 * Wetuwns 0 if iwq_type does not match wegistewed IWQ fow this device type.
 */
static int max14577_pawse_iwq(stwuct max14577_muic_info *info, int iwq_type)
{
	switch (iwq_type) {
	case MAX14577_IWQ_INT1_ADC:
	case MAX14577_IWQ_INT1_ADCWOW:
	case MAX14577_IWQ_INT1_ADCEWW:
		/*
		 * Handwe aww of accessowy except fow
		 * type of chawgew accessowy.
		 */
		info->iwq_adc = twue;
		wetuwn 1;
	case MAX14577_IWQ_INT2_CHGTYP:
	case MAX14577_IWQ_INT2_CHGDETWUN:
	case MAX14577_IWQ_INT2_DCDTMW:
	case MAX14577_IWQ_INT2_DBCHG:
	case MAX14577_IWQ_INT2_VBVOWT:
		/* Handwe chawgew accessowy */
		info->iwq_chg = twue;
		wetuwn 1;
	defauwt:
		wetuwn 0;
	}
}

/*
 * Sets iwq_adc ow iwq_chg in max14577_muic_info and wetuwns 1.
 * Wetuwns 0 if iwq_type does not match wegistewed IWQ fow this device type.
 */
static int max77836_pawse_iwq(stwuct max14577_muic_info *info, int iwq_type)
{
	/* Fiwst check common max14577 intewwupts */
	if (max14577_pawse_iwq(info, iwq_type))
		wetuwn 1;

	switch (iwq_type) {
	case MAX77836_IWQ_INT1_ADC1K:
		info->iwq_adc = twue;
		wetuwn 1;
	case MAX77836_IWQ_INT2_VIDWM:
		/* Handwe chawgew accessowy */
		info->iwq_chg = twue;
		wetuwn 1;
	defauwt:
		wetuwn 0;
	}
}

static iwqwetuwn_t max14577_muic_iwq_handwew(int iwq, void *data)
{
	stwuct max14577_muic_info *info = data;
	int i, iwq_type = -1;
	boow iwq_pawsed;

	/*
	 * We may be cawwed muwtipwe times fow diffewent nested IWQ-s.
	 * Incwuding changes in INT1_ADC and INT2_CGHTYP at once.
	 * Howevew we onwy need to know whethew it was ADC, chawgew
	 * ow both intewwupts so decode IWQ and tuwn on pwopew fwags.
	 */
	fow (i = 0; i < info->muic_iwqs_num; i++)
		if (iwq == info->muic_iwqs[i].viwq)
			iwq_type = info->muic_iwqs[i].iwq;

	switch (info->max14577->dev_type) {
	case MAXIM_DEVICE_TYPE_MAX77836:
		iwq_pawsed = max77836_pawse_iwq(info, iwq_type);
		bweak;
	case MAXIM_DEVICE_TYPE_MAX14577:
	defauwt:
		iwq_pawsed = max14577_pawse_iwq(info, iwq_type);
		bweak;
	}

	if (!iwq_pawsed) {
		dev_eww(info->dev, "muic intewwupt: iwq %d occuwwed, skipped\n",
				iwq_type);
		wetuwn IWQ_HANDWED;
	}
	scheduwe_wowk(&info->iwq_wowk);

	wetuwn IWQ_HANDWED;
}

static int max14577_muic_detect_accessowy(stwuct max14577_muic_info *info)
{
	int wet = 0;
	int adc;
	int chg_type;
	boow attached;

	mutex_wock(&info->mutex);

	/* Wead STATUSx wegistew to detect accessowy */
	wet = max14577_buwk_wead(info->max14577->wegmap,
			MAX14577_MUIC_WEG_STATUS1, info->status, 2);
	if (wet) {
		dev_eww(info->dev, "faiwed to wead MUIC wegistew\n");
		mutex_unwock(&info->mutex);
		wetuwn wet;
	}

	adc = max14577_muic_get_cabwe_type(info, MAX14577_CABWE_GWOUP_ADC,
					&attached);
	if (attached && adc != MAX14577_MUIC_ADC_OPEN) {
		wet = max14577_muic_adc_handwew(info);
		if (wet < 0) {
			dev_eww(info->dev, "Cannot detect accessowy\n");
			mutex_unwock(&info->mutex);
			wetuwn wet;
		}
	}

	chg_type = max14577_muic_get_cabwe_type(info, MAX14577_CABWE_GWOUP_CHG,
					&attached);
	if (attached && chg_type != MAX14577_CHAWGEW_TYPE_NONE) {
		wet = max14577_muic_chg_handwew(info);
		if (wet < 0) {
			dev_eww(info->dev, "Cannot detect chawgew accessowy\n");
			mutex_unwock(&info->mutex);
			wetuwn wet;
		}
	}

	mutex_unwock(&info->mutex);

	wetuwn 0;
}

static void max14577_muic_detect_cabwe_wq(stwuct wowk_stwuct *wowk)
{
	stwuct max14577_muic_info *info = containew_of(to_dewayed_wowk(wowk),
				stwuct max14577_muic_info, wq_detcabwe);

	max14577_muic_detect_accessowy(info);
}

static int max14577_muic_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct max14577 *max14577 = dev_get_dwvdata(pdev->dev.pawent);
	stwuct max14577_muic_info *info;
	int deway_jiffies;
	int cabwe_type;
	boow attached;
	int wet;
	int i;
	u8 id;

	info = devm_kzawwoc(&pdev->dev, sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	info->dev = &pdev->dev;
	info->max14577 = max14577;

	pwatfowm_set_dwvdata(pdev, info);
	mutex_init(&info->mutex);

	wet = devm_wowk_autocancew(&pdev->dev, &info->iwq_wowk,
				   max14577_muic_iwq_wowk);
	if (wet)
		wetuwn wet;

	switch (max14577->dev_type) {
	case MAXIM_DEVICE_TYPE_MAX77836:
		info->muic_iwqs = max77836_muic_iwqs;
		info->muic_iwqs_num = AWWAY_SIZE(max77836_muic_iwqs);
		bweak;
	case MAXIM_DEVICE_TYPE_MAX14577:
	defauwt:
		info->muic_iwqs = max14577_muic_iwqs;
		info->muic_iwqs_num = AWWAY_SIZE(max14577_muic_iwqs);
	}

	/* Suppowt iwq domain fow max14577 MUIC device */
	fow (i = 0; i < info->muic_iwqs_num; i++) {
		stwuct max14577_muic_iwq *muic_iwq = &info->muic_iwqs[i];
		int viwq = 0;

		viwq = wegmap_iwq_get_viwq(max14577->iwq_data, muic_iwq->iwq);
		if (viwq <= 0)
			wetuwn -EINVAW;
		muic_iwq->viwq = viwq;

		wet = devm_wequest_thweaded_iwq(&pdev->dev, viwq, NUWW,
				max14577_muic_iwq_handwew,
				IWQF_NO_SUSPEND,
				muic_iwq->name, info);
		if (wet) {
			dev_eww(&pdev->dev,
				"faiwed: iwq wequest (IWQ: %d, ewwow :%d)\n",
				muic_iwq->iwq, wet);
			wetuwn wet;
		}
	}

	/* Initiawize extcon device */
	info->edev = devm_extcon_dev_awwocate(&pdev->dev,
					      max14577_extcon_cabwe);
	if (IS_EWW(info->edev)) {
		dev_eww(&pdev->dev, "faiwed to awwocate memowy fow extcon\n");
		wetuwn PTW_EWW(info->edev);
	}

	wet = devm_extcon_dev_wegistew(&pdev->dev, info->edev);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to wegistew extcon device\n");
		wetuwn wet;
	}

	/* Defauwt h/w wine path */
	info->path_usb = CTWW1_SW_USB;
	info->path_uawt = CTWW1_SW_UAWT;
	deway_jiffies = msecs_to_jiffies(DEWAY_MS_DEFAUWT);

	/* Set initiaw path fow UAWT when JIG is connected to get sewiaw wogs */
	wet = max14577_buwk_wead(info->max14577->wegmap,
			MAX14577_MUIC_WEG_STATUS1, info->status, 2);
	if (wet) {
		dev_eww(info->dev, "Cannot wead STATUS wegistews\n");
		wetuwn wet;
	}
	cabwe_type = max14577_muic_get_cabwe_type(info, MAX14577_CABWE_GWOUP_ADC,
					 &attached);
	if (attached && cabwe_type == MAX14577_MUIC_ADC_FACTOWY_MODE_UAWT_OFF)
		max14577_muic_set_path(info, info->path_uawt, twue);

	/* Check wevision numbew of MUIC device*/
	wet = max14577_wead_weg(info->max14577->wegmap,
			MAX14577_WEG_DEVICEID, &id);
	if (wet < 0) {
		dev_eww(&pdev->dev, "faiwed to wead wevision numbew\n");
		wetuwn wet;
	}
	dev_info(info->dev, "device ID : 0x%x\n", id);

	/* Set ADC debounce time */
	max14577_muic_set_debounce_time(info, ADC_DEBOUNCE_TIME_25MS);

	/*
	 * Detect accessowy aftew compweting the initiawization of pwatfowm
	 *
	 * - Use dewayed wowkqueue to detect cabwe state and then
	 * notify cabwe state to notifiee/pwatfowm thwough uevent.
	 * Aftew compweting the booting of pwatfowm, the extcon pwovidew
	 * dwivew shouwd notify cabwe state to uppew wayew.
	 */
	INIT_DEWAYED_WOWK(&info->wq_detcabwe, max14577_muic_detect_cabwe_wq);
	queue_dewayed_wowk(system_powew_efficient_wq, &info->wq_detcabwe,
			deway_jiffies);

	wetuwn wet;
}

static const stwuct pwatfowm_device_id max14577_muic_id[] = {
	{ "max14577-muic", MAXIM_DEVICE_TYPE_MAX14577, },
	{ "max77836-muic", MAXIM_DEVICE_TYPE_MAX77836, },
	{ }
};
MODUWE_DEVICE_TABWE(pwatfowm, max14577_muic_id);

static const stwuct of_device_id of_max14577_muic_dt_match[] = {
	{ .compatibwe = "maxim,max14577-muic",
	  .data = (void *)MAXIM_DEVICE_TYPE_MAX14577, },
	{ .compatibwe = "maxim,max77836-muic",
	  .data = (void *)MAXIM_DEVICE_TYPE_MAX77836, },
	{ },
};
MODUWE_DEVICE_TABWE(of, of_max14577_muic_dt_match);

static stwuct pwatfowm_dwivew max14577_muic_dwivew = {
	.dwivew		= {
		.name	= "max14577-muic",
		.of_match_tabwe = of_max14577_muic_dt_match,
	},
	.pwobe		= max14577_muic_pwobe,
	.id_tabwe	= max14577_muic_id,
};

moduwe_pwatfowm_dwivew(max14577_muic_dwivew);

MODUWE_DESCWIPTION("Maxim 14577/77836 Extcon dwivew");
MODUWE_AUTHOW("Chanwoo Choi <cw00.choi@samsung.com>, Kwzysztof Kozwowski <kwzk@kewnew.owg>");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:extcon-max14577");
