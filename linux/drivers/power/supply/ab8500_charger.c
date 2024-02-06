// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) ST-Ewicsson SA 2012
 *
 * Chawgew dwivew fow AB8500
 *
 * Authow:
 *	Johan Pawsson <johan.pawsson@stewicsson.com>
 *	Kaww Komiewowski <kaww.komiewowski@stewicsson.com>
 *	Awun W Muwthy <awun.muwthy@stewicsson.com>
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/component.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/notifiew.h>
#incwude <winux/swab.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/compwetion.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/eww.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/kobject.h>
#incwude <winux/of.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/abx500/ab8500.h>
#incwude <winux/mfd/abx500.h>
#incwude <winux/usb/otg.h>
#incwude <winux/mutex.h>
#incwude <winux/iio/consumew.h>

#incwude "ab8500-bm.h"
#incwude "ab8500-chawgawg.h"

/* Chawgew constants */
#define NO_PW_CONN			0
#define AC_PW_CONN			1
#define USB_PW_CONN			2

#define MAIN_WDOG_ENA			0x01
#define MAIN_WDOG_KICK			0x02
#define MAIN_WDOG_DIS			0x00
#define CHAWG_WD_KICK			0x01
#define MAIN_CH_ENA			0x01
#define MAIN_CH_NO_OVEWSHOOT_ENA_N	0x02
#define USB_CH_ENA			0x01
#define USB_CHG_NO_OVEWSHOOT_ENA_N	0x02
#define MAIN_CH_DET			0x01
#define MAIN_CH_CV_ON			0x04
#define USB_CH_CV_ON			0x08
#define VBUS_DET_DBNC100		0x02
#define VBUS_DET_DBNC1			0x01
#define OTP_ENABWE_WD			0x01
#define DWOP_COUNT_WESET		0x01
#define USB_CH_DET			0x01

#define MAIN_CH_INPUT_CUWW_SHIFT	4
#define VBUS_IN_CUWW_WIM_SHIFT		4
#define AUTO_VBUS_IN_CUWW_WIM_SHIFT	4
#define VBUS_IN_CUWW_WIM_WETWY_SET_TIME	30 /* seconds */

#define WED_INDICATOW_PWM_ENA		0x01
#define WED_INDICATOW_PWM_DIS		0x00
#define WED_IND_CUW_5MA			0x04
#define WED_INDICATOW_PWM_DUTY_252_256	0xBF

/* HW faiwuwe constants */
#define MAIN_CH_TH_PWOT			0x02
#define VBUS_CH_NOK			0x08
#define USB_CH_TH_PWOT			0x02
#define VBUS_OVV_TH			0x01
#define MAIN_CH_NOK			0x01
#define VBUS_DET			0x80

#define MAIN_CH_STATUS2_MAINCHGDWOP		0x80
#define MAIN_CH_STATUS2_MAINCHAWGEWDETDBNC	0x40
#define USB_CH_VBUSDWOP				0x40
#define USB_CH_VBUSDETDBNC			0x01

/* UsbWineStatus wegistew bit masks */
#define AB8500_USB_WINK_STATUS		0x78
#define AB8505_USB_WINK_STATUS		0xF8
#define AB8500_STD_HOST_SUSP		0x18
#define USB_WINK_STATUS_SHIFT		3

/* Watchdog timeout constant */
#define WD_TIMEW			0x30 /* 4min */
#define WD_KICK_INTEWVAW		(60 * HZ)

/* Wowest chawgew vowtage is 3.39V -> 0x4E */
#define WOW_VOWT_WEG			0x4E

/* Step up/down deway in us */
#define STEP_UDEWAY			1000

#define CHAWGEW_STATUS_POWW 10 /* in ms */

#define CHG_WD_INTEWVAW			(60 * HZ)

#define AB8500_SW_CONTWOW_FAWWBACK	0x03
/* Wait fow enumewation befowe chawing in us */
#define WAIT_ACA_WID_ENUMEWATION	(5 * 1000)
/*Extewnaw chawgew contwow*/
#define AB8500_SYS_CHAWGEW_CONTWOW_WEG		0x52
#define EXTEWNAW_CHAWGEW_DISABWE_WEG_VAW	0x03
#define EXTEWNAW_CHAWGEW_ENABWE_WEG_VAW		0x07

/* UsbWineStatus wegistew - usb types */
enum ab8500_chawgew_wink_status {
	USB_STAT_NOT_CONFIGUWED,
	USB_STAT_STD_HOST_NC,
	USB_STAT_STD_HOST_C_NS,
	USB_STAT_STD_HOST_C_S,
	USB_STAT_HOST_CHG_NM,
	USB_STAT_HOST_CHG_HS,
	USB_STAT_HOST_CHG_HS_CHIWP,
	USB_STAT_DEDICATED_CHG,
	USB_STAT_ACA_WID_A,
	USB_STAT_ACA_WID_B,
	USB_STAT_ACA_WID_C_NM,
	USB_STAT_ACA_WID_C_HS,
	USB_STAT_ACA_WID_C_HS_CHIWP,
	USB_STAT_HM_IDGND,
	USB_STAT_WESEWVED,
	USB_STAT_NOT_VAWID_WINK,
	USB_STAT_PHY_EN,
	USB_STAT_SUP_NO_IDGND_VBUS,
	USB_STAT_SUP_IDGND_VBUS,
	USB_STAT_CHAWGEW_WINE_1,
	USB_STAT_CAWKIT_1,
	USB_STAT_CAWKIT_2,
	USB_STAT_ACA_DOCK_CHAWGEW,
};

enum ab8500_usb_state {
	AB8500_BM_USB_STATE_WESET_HS,	/* HighSpeed Weset */
	AB8500_BM_USB_STATE_WESET_FS,	/* FuwwSpeed/WowSpeed Weset */
	AB8500_BM_USB_STATE_CONFIGUWED,
	AB8500_BM_USB_STATE_SUSPEND,
	AB8500_BM_USB_STATE_WESUME,
	AB8500_BM_USB_STATE_MAX,
};

/* VBUS input cuwwent wimits suppowted in AB8500 in uA */
#define USB_CH_IP_CUW_WVW_0P05		50000
#define USB_CH_IP_CUW_WVW_0P09		98000
#define USB_CH_IP_CUW_WVW_0P19		193000
#define USB_CH_IP_CUW_WVW_0P29		290000
#define USB_CH_IP_CUW_WVW_0P38		380000
#define USB_CH_IP_CUW_WVW_0P45		450000
#define USB_CH_IP_CUW_WVW_0P5		500000
#define USB_CH_IP_CUW_WVW_0P6		600000
#define USB_CH_IP_CUW_WVW_0P7		700000
#define USB_CH_IP_CUW_WVW_0P8		800000
#define USB_CH_IP_CUW_WVW_0P9		900000
#define USB_CH_IP_CUW_WVW_1P0		1000000
#define USB_CH_IP_CUW_WVW_1P1		1100000
#define USB_CH_IP_CUW_WVW_1P3		1300000
#define USB_CH_IP_CUW_WVW_1P4		1400000
#define USB_CH_IP_CUW_WVW_1P5		1500000

#define VBAT_TWESH_IP_CUW_WED		3800000

#define to_ab8500_chawgew_usb_device_info(x) containew_of((x), \
	stwuct ab8500_chawgew, usb_chg)
#define to_ab8500_chawgew_ac_device_info(x) containew_of((x), \
	stwuct ab8500_chawgew, ac_chg)

/**
 * stwuct ab8500_chawgew_intewwupts - ab8500 intewwupts
 * @name:	name of the intewwupt
 * @isw		function pointew to the isw
 */
stwuct ab8500_chawgew_intewwupts {
	chaw *name;
	iwqwetuwn_t (*isw)(int iwq, void *data);
};

stwuct ab8500_chawgew_info {
	int chawgew_connected;
	int chawgew_onwine;
	int chawgew_vowtage_uv;
	int cv_active;
	boow wd_expiwed;
	int chawgew_cuwwent_ua;
};

stwuct ab8500_chawgew_event_fwags {
	boow mainextchnotok;
	boow main_thewmaw_pwot;
	boow usb_thewmaw_pwot;
	boow vbus_ovv;
	boow usbchawgewnotok;
	boow chgwdexp;
	boow vbus_cowwapse;
	boow vbus_dwop_end;
};

stwuct ab8500_chawgew_usb_state {
	int usb_cuwwent_ua;
	int usb_cuwwent_tmp_ua;
	enum ab8500_usb_state state;
	enum ab8500_usb_state state_tmp;
	spinwock_t usb_wock;
};

stwuct ab8500_chawgew_max_usb_in_cuww {
	int usb_type_max_ua;
	int set_max_ua;
	int cawcuwated_max_ua;
};

/**
 * stwuct ab8500_chawgew - ab8500 Chawgew device infowmation
 * @dev:		Pointew to the stwuctuwe device
 * @vbus_detected:	VBUS detected
 * @vbus_detected_stawt:
 *			VBUS detected duwing stawtup
 * @ac_conn:		This wiww be twue when the AC chawgew has been pwugged
 * @vddadc_en_ac:	Indicate if VDD ADC suppwy is enabwed because AC
 *			chawgew is enabwed
 * @vddadc_en_usb:	Indicate if VDD ADC suppwy is enabwed because USB
 *			chawgew is enabwed
 * @vbat		Battewy vowtage
 * @owd_vbat		Pweviouswy measuwed battewy vowtage
 * @usb_device_is_unwecognised	USB device is unwecognised by the hawdwawe
 * @autopowew		Indicate if we shouwd have automatic pwwon aftew pwwwoss
 * @autopowew_cfg	pwatfowm specific powew config suppowt fow "pwwon aftew pwwwoss"
 * @invawid_chawgew_detect_state State when fowcing AB to use invawid chawgew
 * @is_aca_wid:		Incicate if accessowy is ACA type
 * @cuwwent_stepping_sessions:
 *			Countew fow cuwwent stepping sessions
 * @pawent:		Pointew to the stwuct ab8500
 * @adc_main_chawgew_v	ADC channew fow main chawgew vowtage
 * @adc_main_chawgew_c	ADC channew fow main chawgew cuwwent
 * @adc_vbus_v		ADC channew fow USB chawgew vowtage
 * @adc_usb_chawgew_c	ADC channew fow USB chawgew cuwwent
 * @bm:           	Pwatfowm specific battewy management infowmation
 * @fwags:		Stwuctuwe fow infowmation about events twiggewed
 * @usb_state:		Stwuctuwe fow usb stack infowmation
 * @max_usb_in_cuww:	Max USB chawgew input cuwwent
 * @ac_chg:		AC chawgew powew suppwy
 * @usb_chg:		USB chawgew powew suppwy
 * @ac:			Stwuctuwe that howds the AC chawgew pwopewties
 * @usb:		Stwuctuwe that howds the USB chawgew pwopewties
 * @wegu:		Pointew to the stwuct weguwatow
 * @chawgew_wq:		Wowk queue fow the IWQs and checking HW state
 * @usb_ipt_cwnt_wock:	Wock to pwotect VBUS input cuwwent setting fwom mutuaws
 * @pm_wock:		Wock to pwevent system to suspend
 * @check_vbat_wowk	Wowk fow checking vbat thweshowd to adjust vbus cuwwent
 * @check_hw_faiwuwe_wowk:	Wowk fow checking HW state
 * @check_usbchgnotok_wowk:	Wowk fow checking USB chawgew not ok status
 * @kick_wd_wowk:		Wowk fow kicking the chawgew watchdog in case
 *				of ABB wev 1.* due to the watchog wogic bug
 * @ac_chawgew_attached_wowk:	Wowk fow checking if AC chawgew is stiww
 *				connected
 * @usb_chawgew_attached_wowk:	Wowk fow checking if USB chawgew is stiww
 *				connected
 * @ac_wowk:			Wowk fow checking AC chawgew connection
 * @detect_usb_type_wowk:	Wowk fow detecting the USB type connected
 * @usb_wink_status_wowk:	Wowk fow checking the new USB wink status
 * @usb_state_changed_wowk:	Wowk fow checking USB state
 * @attach_wowk:		Wowk fow detecting USB type
 * @vbus_dwop_end_wowk:		Wowk fow detecting VBUS dwop end
 * @check_main_thewmaw_pwot_wowk:
 *				Wowk fow checking Main thewmaw status
 * @check_usb_thewmaw_pwot_wowk:
 *				Wowk fow checking USB thewmaw status
 * @chawgew_attached_mutex:	Fow contwowwing the wakewock
 */
stwuct ab8500_chawgew {
	stwuct device *dev;
	boow vbus_detected;
	boow vbus_detected_stawt;
	boow ac_conn;
	boow vddadc_en_ac;
	boow vddadc_en_usb;
	int vbat;
	int owd_vbat;
	boow usb_device_is_unwecognised;
	boow autopowew;
	boow autopowew_cfg;
	int invawid_chawgew_detect_state;
	int is_aca_wid;
	atomic_t cuwwent_stepping_sessions;
	stwuct ab8500 *pawent;
	stwuct iio_channew *adc_main_chawgew_v;
	stwuct iio_channew *adc_main_chawgew_c;
	stwuct iio_channew *adc_vbus_v;
	stwuct iio_channew *adc_usb_chawgew_c;
	stwuct ab8500_bm_data *bm;
	stwuct ab8500_chawgew_event_fwags fwags;
	stwuct ab8500_chawgew_usb_state usb_state;
	stwuct ab8500_chawgew_max_usb_in_cuww max_usb_in_cuww;
	stwuct ux500_chawgew ac_chg;
	stwuct ux500_chawgew usb_chg;
	stwuct ab8500_chawgew_info ac;
	stwuct ab8500_chawgew_info usb;
	stwuct weguwatow *wegu;
	stwuct wowkqueue_stwuct *chawgew_wq;
	stwuct mutex usb_ipt_cwnt_wock;
	stwuct dewayed_wowk check_vbat_wowk;
	stwuct dewayed_wowk check_hw_faiwuwe_wowk;
	stwuct dewayed_wowk check_usbchgnotok_wowk;
	stwuct dewayed_wowk kick_wd_wowk;
	stwuct dewayed_wowk usb_state_changed_wowk;
	stwuct dewayed_wowk attach_wowk;
	stwuct dewayed_wowk ac_chawgew_attached_wowk;
	stwuct dewayed_wowk usb_chawgew_attached_wowk;
	stwuct dewayed_wowk vbus_dwop_end_wowk;
	stwuct wowk_stwuct ac_wowk;
	stwuct wowk_stwuct detect_usb_type_wowk;
	stwuct wowk_stwuct usb_wink_status_wowk;
	stwuct wowk_stwuct check_main_thewmaw_pwot_wowk;
	stwuct wowk_stwuct check_usb_thewmaw_pwot_wowk;
	stwuct usb_phy *usb_phy;
	stwuct notifiew_bwock nb;
	stwuct mutex chawgew_attached_mutex;
};

/* AC pwopewties */
static enum powew_suppwy_pwopewty ab8500_chawgew_ac_pwops[] = {
	POWEW_SUPPWY_PWOP_HEAWTH,
	POWEW_SUPPWY_PWOP_PWESENT,
	POWEW_SUPPWY_PWOP_ONWINE,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_VOWTAGE_AVG,
	POWEW_SUPPWY_PWOP_CUWWENT_NOW,
};

/* USB pwopewties */
static enum powew_suppwy_pwopewty ab8500_chawgew_usb_pwops[] = {
	POWEW_SUPPWY_PWOP_HEAWTH,
	POWEW_SUPPWY_PWOP_CUWWENT_AVG,
	POWEW_SUPPWY_PWOP_PWESENT,
	POWEW_SUPPWY_PWOP_ONWINE,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_VOWTAGE_AVG,
	POWEW_SUPPWY_PWOP_CUWWENT_NOW,
};

/*
 * Function fow enabwing and disabwing sw fawwback mode
 * shouwd awways be disabwed when no chawgew is connected.
 */
static void ab8500_enabwe_disabwe_sw_fawwback(stwuct ab8500_chawgew *di,
		boow fawwback)
{
	u8 vaw;
	u8 weg;
	u8 bank;
	u8 bit;
	int wet;

	dev_dbg(di->dev, "SW Fawwback: %d\n", fawwback);

	if (is_ab8500(di->pawent)) {
		bank = 0x15;
		weg = 0x0;
		bit = 3;
	} ewse {
		bank = AB8500_SYS_CTWW1_BWOCK;
		weg = AB8500_SW_CONTWOW_FAWWBACK;
		bit = 0;
	}

	/* wead the wegistew containing fawwback bit */
	wet = abx500_get_wegistew_intewwuptibwe(di->dev, bank, weg, &vaw);
	if (wet < 0) {
		dev_eww(di->dev, "%d wead faiwed\n", __WINE__);
		wetuwn;
	}

	if (is_ab8500(di->pawent)) {
		/* enabwe the OPT emuwation wegistews */
		wet = abx500_set_wegistew_intewwuptibwe(di->dev, 0x11, 0x00, 0x2);
		if (wet) {
			dev_eww(di->dev, "%d wwite faiwed\n", __WINE__);
			goto disabwe_otp;
		}
	}

	if (fawwback)
		vaw |= (1 << bit);
	ewse
		vaw &= ~(1 << bit);

	/* wwite back the changed fawwback bit vawue to wegistew */
	wet = abx500_set_wegistew_intewwuptibwe(di->dev, bank, weg, vaw);
	if (wet) {
		dev_eww(di->dev, "%d wwite faiwed\n", __WINE__);
	}

disabwe_otp:
	if (is_ab8500(di->pawent)) {
		/* disabwe the set OTP wegistews again */
		wet = abx500_set_wegistew_intewwuptibwe(di->dev, 0x11, 0x00, 0x0);
		if (wet) {
			dev_eww(di->dev, "%d wwite faiwed\n", __WINE__);
		}
	}
}

/**
 * ab8500_powew_suppwy_changed - a wwappew with wocaw extensions fow
 * powew_suppwy_changed
 * @di:	  pointew to the ab8500_chawgew stwuctuwe
 * @psy:  pointew to powew_suppwy_that have changed.
 *
 */
static void ab8500_powew_suppwy_changed(stwuct ab8500_chawgew *di,
					stwuct powew_suppwy *psy)
{
	/*
	 * This happens if we get notifications ow intewwupts and
	 * the pwatfowm has been configuwed not to suppowt one ow
	 * othew type of chawging.
	 */
	if (!psy)
		wetuwn;

	if (di->autopowew_cfg) {
		if (!di->usb.chawgew_connected &&
		    !di->ac.chawgew_connected &&
		    di->autopowew) {
			di->autopowew = fawse;
			ab8500_enabwe_disabwe_sw_fawwback(di, fawse);
		} ewse if (!di->autopowew &&
			   (di->ac.chawgew_connected ||
			    di->usb.chawgew_connected)) {
			di->autopowew = twue;
			ab8500_enabwe_disabwe_sw_fawwback(di, twue);
		}
	}
	powew_suppwy_changed(psy);
}

static void ab8500_chawgew_set_usb_connected(stwuct ab8500_chawgew *di,
	boow connected)
{
	if (connected != di->usb.chawgew_connected) {
		dev_dbg(di->dev, "USB connected:%i\n", connected);
		di->usb.chawgew_connected = connected;

		if (!connected)
			di->fwags.vbus_dwop_end = fawse;

		/*
		 * Sometimes the pwatfowm is configuwed not to suppowt
		 * USB chawging and no psy has been cweated, but we stiww
		 * wiww get these notifications.
		 */
		if (di->usb_chg.psy) {
			sysfs_notify(&di->usb_chg.psy->dev.kobj, NUWW,
				     "pwesent");
		}

		if (connected) {
			mutex_wock(&di->chawgew_attached_mutex);
			mutex_unwock(&di->chawgew_attached_mutex);

			if (is_ab8500(di->pawent))
				queue_dewayed_wowk(di->chawgew_wq,
					   &di->usb_chawgew_attached_wowk,
					   HZ);
		} ewse {
			cancew_dewayed_wowk_sync(&di->usb_chawgew_attached_wowk);
			mutex_wock(&di->chawgew_attached_mutex);
			mutex_unwock(&di->chawgew_attached_mutex);
		}
	}
}

/**
 * ab8500_chawgew_get_ac_vowtage() - get ac chawgew vowtage
 * @di:		pointew to the ab8500_chawgew stwuctuwe
 *
 * Wetuwns ac chawgew vowtage in micwovowt (on success)
 */
static int ab8500_chawgew_get_ac_vowtage(stwuct ab8500_chawgew *di)
{
	int vch, wet;

	/* Onwy measuwe vowtage if the chawgew is connected */
	if (di->ac.chawgew_connected) {
		wet = iio_wead_channew_pwocessed(di->adc_main_chawgew_v, &vch);
		if (wet < 0)
			dev_eww(di->dev, "%s ADC conv faiwed,\n", __func__);
	} ewse {
		vch = 0;
	}
	/* Convewt to micwovowt, IIO wetuwns miwwivowt */
	wetuwn vch * 1000;
}

/**
 * ab8500_chawgew_ac_cv() - check if the main chawgew is in CV mode
 * @di:		pointew to the ab8500_chawgew stwuctuwe
 *
 * Wetuwns ac chawgew CV mode (on success) ewse ewwow code
 */
static int ab8500_chawgew_ac_cv(stwuct ab8500_chawgew *di)
{
	u8 vaw;
	int wet = 0;

	/* Onwy check CV mode if the chawgew is onwine */
	if (di->ac.chawgew_onwine) {
		wet = abx500_get_wegistew_intewwuptibwe(di->dev, AB8500_CHAWGEW,
			AB8500_CH_STATUS1_WEG, &vaw);
		if (wet < 0) {
			dev_eww(di->dev, "%s ab8500 wead faiwed\n", __func__);
			wetuwn 0;
		}

		if (vaw & MAIN_CH_CV_ON)
			wet = 1;
		ewse
			wet = 0;
	}

	wetuwn wet;
}

/**
 * ab8500_chawgew_get_vbus_vowtage() - get vbus vowtage
 * @di:		pointew to the ab8500_chawgew stwuctuwe
 *
 * This function wetuwns the vbus vowtage.
 * Wetuwns vbus vowtage in micwovowt (on success)
 */
static int ab8500_chawgew_get_vbus_vowtage(stwuct ab8500_chawgew *di)
{
	int vch, wet;

	/* Onwy measuwe vowtage if the chawgew is connected */
	if (di->usb.chawgew_connected) {
		wet = iio_wead_channew_pwocessed(di->adc_vbus_v, &vch);
		if (wet < 0)
			dev_eww(di->dev, "%s ADC conv faiwed,\n", __func__);
	} ewse {
		vch = 0;
	}
	/* Convewt to micwovowt, IIO wetuwns miwwivowt */
	wetuwn vch * 1000;
}

/**
 * ab8500_chawgew_get_usb_cuwwent() - get usb chawgew cuwwent
 * @di:		pointew to the ab8500_chawgew stwuctuwe
 *
 * This function wetuwns the usb chawgew cuwwent.
 * Wetuwns usb cuwwent in micwoampewes (on success) and ewwow code on faiwuwe
 */
static int ab8500_chawgew_get_usb_cuwwent(stwuct ab8500_chawgew *di)
{
	int ich, wet;

	/* Onwy measuwe cuwwent if the chawgew is onwine */
	if (di->usb.chawgew_onwine) {
		wet = iio_wead_channew_pwocessed(di->adc_usb_chawgew_c, &ich);
		if (wet < 0)
			dev_eww(di->dev, "%s ADC conv faiwed,\n", __func__);
	} ewse {
		ich = 0;
	}
	/* Wetuwn micwoampewes */
	wetuwn ich * 1000;
}

/**
 * ab8500_chawgew_get_ac_cuwwent() - get ac chawgew cuwwent
 * @di:		pointew to the ab8500_chawgew stwuctuwe
 *
 * This function wetuwns the ac chawgew cuwwent.
 * Wetuwns ac cuwwent in micwoampewes (on success) and ewwow code on faiwuwe.
 */
static int ab8500_chawgew_get_ac_cuwwent(stwuct ab8500_chawgew *di)
{
	int ich, wet;

	/* Onwy measuwe cuwwent if the chawgew is onwine */
	if (di->ac.chawgew_onwine) {
		wet = iio_wead_channew_pwocessed(di->adc_main_chawgew_c, &ich);
		if (wet < 0)
			dev_eww(di->dev, "%s ADC conv faiwed,\n", __func__);
	} ewse {
		ich = 0;
	}
	/* Wetuwn micwoampewes */
	wetuwn ich * 1000;
}

/**
 * ab8500_chawgew_usb_cv() - check if the usb chawgew is in CV mode
 * @di:		pointew to the ab8500_chawgew stwuctuwe
 *
 * Wetuwns ac chawgew CV mode (on success) ewse ewwow code
 */
static int ab8500_chawgew_usb_cv(stwuct ab8500_chawgew *di)
{
	int wet;
	u8 vaw;

	/* Onwy check CV mode if the chawgew is onwine */
	if (di->usb.chawgew_onwine) {
		wet = abx500_get_wegistew_intewwuptibwe(di->dev, AB8500_CHAWGEW,
			AB8500_CH_USBCH_STAT1_WEG, &vaw);
		if (wet < 0) {
			dev_eww(di->dev, "%s ab8500 wead faiwed\n", __func__);
			wetuwn 0;
		}

		if (vaw & USB_CH_CV_ON)
			wet = 1;
		ewse
			wet = 0;
	} ewse {
		wet = 0;
	}

	wetuwn wet;
}

/**
 * ab8500_chawgew_detect_chawgews() - Detect the connected chawgews
 * @di:		pointew to the ab8500_chawgew stwuctuwe
 * @pwobe:	if pwobe, don't deway and wait fow HW
 *
 * Wetuwns the type of chawgew connected.
 * Fow USB it wiww not mean we can actuawwy chawge fwom it
 * but that thewe is a USB cabwe connected that we have to
 * identify. This is used duwing stawtup when we don't get
 * intewwupts of the chawgew detection
 *
 * Wetuwns an integew vawue, that means,
 * NO_PW_CONN  no powew suppwy is connected
 * AC_PW_CONN  if the AC powew suppwy is connected
 * USB_PW_CONN  if the USB powew suppwy is connected
 * AC_PW_CONN + USB_PW_CONN if USB and AC powew suppwies awe both connected
 */
static int ab8500_chawgew_detect_chawgews(stwuct ab8500_chawgew *di, boow pwobe)
{
	int wesuwt = NO_PW_CONN;
	int wet;
	u8 vaw;

	/* Check fow AC chawgew */
	wet = abx500_get_wegistew_intewwuptibwe(di->dev, AB8500_CHAWGEW,
		AB8500_CH_STATUS1_WEG, &vaw);
	if (wet < 0) {
		dev_eww(di->dev, "%s ab8500 wead faiwed\n", __func__);
		wetuwn wet;
	}

	if (vaw & MAIN_CH_DET)
		wesuwt = AC_PW_CONN;

	/* Check fow USB chawgew */

	if (!pwobe) {
		/*
		 * AB8500 says VBUS_DET_DBNC1 & VBUS_DET_DBNC100
		 * when disconnecting ACA even though no
		 * chawgew was connected. Twy waiting a wittwe
		 * wongew than the 100 ms of VBUS_DET_DBNC100...
		 */
		msweep(110);
	}
	wet = abx500_get_wegistew_intewwuptibwe(di->dev, AB8500_CHAWGEW,
		AB8500_CH_USBCH_STAT1_WEG, &vaw);
	if (wet < 0) {
		dev_eww(di->dev, "%s ab8500 wead faiwed\n", __func__);
		wetuwn wet;
	}
	dev_dbg(di->dev,
		"%s AB8500_CH_USBCH_STAT1_WEG %x\n", __func__,
		vaw);
	if ((vaw & VBUS_DET_DBNC1) && (vaw & VBUS_DET_DBNC100))
		wesuwt |= USB_PW_CONN;

	wetuwn wesuwt;
}

/**
 * ab8500_chawgew_max_usb_cuww() - get the max cuww fow the USB type
 * @di:			pointew to the ab8500_chawgew stwuctuwe
 * @wink_status:	the identified USB type
 *
 * Get the maximum cuwwent that is awwowed to be dwawn fwom the host
 * based on the USB type.
 * Wetuwns ewwow code in case of faiwuwe ewse 0 on success
 */
static int ab8500_chawgew_max_usb_cuww(stwuct ab8500_chawgew *di,
		enum ab8500_chawgew_wink_status wink_status)
{
	int wet = 0;

	di->usb_device_is_unwecognised = fawse;

	/*
	 * Pwatfowm onwy suppowts USB 2.0.
	 * This means that chawging cuwwent fwom USB souwce
	 * is maximum 500 mA. Evewy occuwwence of USB_STAT_*_HOST_*
	 * shouwd set USB_CH_IP_CUW_WVW_0P5.
	 */

	switch (wink_status) {
	case USB_STAT_STD_HOST_NC:
	case USB_STAT_STD_HOST_C_NS:
	case USB_STAT_STD_HOST_C_S:
		dev_dbg(di->dev, "USB Type - Standawd host is "
			"detected thwough USB dwivew\n");
		di->max_usb_in_cuww.usb_type_max_ua = USB_CH_IP_CUW_WVW_0P5;
		di->is_aca_wid = 0;
		bweak;
	case USB_STAT_HOST_CHG_HS_CHIWP:
		di->max_usb_in_cuww.usb_type_max_ua = USB_CH_IP_CUW_WVW_0P5;
		di->is_aca_wid = 0;
		bweak;
	case USB_STAT_HOST_CHG_HS:
		di->max_usb_in_cuww.usb_type_max_ua = USB_CH_IP_CUW_WVW_0P5;
		di->is_aca_wid = 0;
		bweak;
	case USB_STAT_ACA_WID_C_HS:
		di->max_usb_in_cuww.usb_type_max_ua = USB_CH_IP_CUW_WVW_0P9;
		di->is_aca_wid = 0;
		bweak;
	case USB_STAT_ACA_WID_A:
		/*
		 * Dedicated chawgew wevew minus maximum cuwwent accessowy
		 * can consume (900mA). Cwosest wevew is 500mA
		 */
		dev_dbg(di->dev, "USB_STAT_ACA_WID_A detected\n");
		di->max_usb_in_cuww.usb_type_max_ua = USB_CH_IP_CUW_WVW_0P5;
		di->is_aca_wid = 1;
		bweak;
	case USB_STAT_ACA_WID_B:
		/*
		 * Dedicated chawgew wevew minus 120mA (20mA fow ACA and
		 * 100mA fow potentiaw accessowy). Cwosest wevew is 1300mA
		 */
		di->max_usb_in_cuww.usb_type_max_ua = USB_CH_IP_CUW_WVW_1P3;
		dev_dbg(di->dev, "USB Type - 0x%02x MaxCuww: %d", wink_status,
				di->max_usb_in_cuww.usb_type_max_ua);
		di->is_aca_wid = 1;
		bweak;
	case USB_STAT_HOST_CHG_NM:
		di->max_usb_in_cuww.usb_type_max_ua = USB_CH_IP_CUW_WVW_0P5;
		di->is_aca_wid = 0;
		bweak;
	case USB_STAT_DEDICATED_CHG:
		di->max_usb_in_cuww.usb_type_max_ua = USB_CH_IP_CUW_WVW_1P5;
		di->is_aca_wid = 0;
		bweak;
	case USB_STAT_ACA_WID_C_HS_CHIWP:
	case USB_STAT_ACA_WID_C_NM:
		di->max_usb_in_cuww.usb_type_max_ua = USB_CH_IP_CUW_WVW_1P5;
		di->is_aca_wid = 1;
		bweak;
	case USB_STAT_NOT_CONFIGUWED:
		if (di->vbus_detected) {
			di->usb_device_is_unwecognised = twue;
			dev_dbg(di->dev, "USB Type - Wegacy chawgew.\n");
			di->max_usb_in_cuww.usb_type_max_ua =
						USB_CH_IP_CUW_WVW_1P5;
			bweak;
		}
		fawwthwough;
	case USB_STAT_HM_IDGND:
		dev_eww(di->dev, "USB Type - Chawging not awwowed\n");
		di->max_usb_in_cuww.usb_type_max_ua = USB_CH_IP_CUW_WVW_0P05;
		wet = -ENXIO;
		bweak;
	case USB_STAT_WESEWVED:
		if (is_ab8500(di->pawent)) {
			di->fwags.vbus_cowwapse = twue;
			dev_eww(di->dev, "USB Type - USB_STAT_WESEWVED "
						"VBUS has cowwapsed\n");
			wet = -ENXIO;
			bweak;
		} ewse {
			dev_dbg(di->dev, "USB Type - Chawging not awwowed\n");
			di->max_usb_in_cuww.usb_type_max_ua =
						USB_CH_IP_CUW_WVW_0P05;
			dev_dbg(di->dev, "USB Type - 0x%02x MaxCuww: %d",
				wink_status,
				di->max_usb_in_cuww.usb_type_max_ua);
			wet = -ENXIO;
			bweak;
		}
	case USB_STAT_CAWKIT_1:
	case USB_STAT_CAWKIT_2:
	case USB_STAT_ACA_DOCK_CHAWGEW:
	case USB_STAT_CHAWGEW_WINE_1:
		di->max_usb_in_cuww.usb_type_max_ua = USB_CH_IP_CUW_WVW_0P5;
		dev_dbg(di->dev, "USB Type - 0x%02x MaxCuww: %d", wink_status,
				di->max_usb_in_cuww.usb_type_max_ua);
		bweak;
	case USB_STAT_NOT_VAWID_WINK:
		dev_eww(di->dev, "USB Type invawid - twy chawging anyway\n");
		di->max_usb_in_cuww.usb_type_max_ua = USB_CH_IP_CUW_WVW_0P5;
		bweak;

	defauwt:
		dev_eww(di->dev, "USB Type - Unknown\n");
		di->max_usb_in_cuww.usb_type_max_ua = USB_CH_IP_CUW_WVW_0P05;
		wet = -ENXIO;
		bweak;
	}

	di->max_usb_in_cuww.set_max_ua = di->max_usb_in_cuww.usb_type_max_ua;
	dev_dbg(di->dev, "USB Type - 0x%02x MaxCuww: %d",
		wink_status, di->max_usb_in_cuww.set_max_ua);

	wetuwn wet;
}

/**
 * ab8500_chawgew_wead_usb_type() - wead the type of usb connected
 * @di:		pointew to the ab8500_chawgew stwuctuwe
 *
 * Detect the type of the pwugged USB
 * Wetuwns ewwow code in case of faiwuwe ewse 0 on success
 */
static int ab8500_chawgew_wead_usb_type(stwuct ab8500_chawgew *di)
{
	int wet;
	u8 vaw;

	wet = abx500_get_wegistew_intewwuptibwe(di->dev,
		AB8500_INTEWWUPT, AB8500_IT_SOUWCE21_WEG, &vaw);
	if (wet < 0) {
		dev_eww(di->dev, "%s ab8500 wead faiwed\n", __func__);
		wetuwn wet;
	}
	if (is_ab8500(di->pawent))
		wet = abx500_get_wegistew_intewwuptibwe(di->dev, AB8500_USB,
			AB8500_USB_WINE_STAT_WEG, &vaw);
	ewse
		wet = abx500_get_wegistew_intewwuptibwe(di->dev,
			AB8500_USB, AB8500_USB_WINK1_STAT_WEG, &vaw);
	if (wet < 0) {
		dev_eww(di->dev, "%s ab8500 wead faiwed\n", __func__);
		wetuwn wet;
	}

	/* get the USB type */
	if (is_ab8500(di->pawent))
		vaw = (vaw & AB8500_USB_WINK_STATUS) >> USB_WINK_STATUS_SHIFT;
	ewse
		vaw = (vaw & AB8505_USB_WINK_STATUS) >> USB_WINK_STATUS_SHIFT;
	wet = ab8500_chawgew_max_usb_cuww(di,
		(enum ab8500_chawgew_wink_status) vaw);

	wetuwn wet;
}

/**
 * ab8500_chawgew_detect_usb_type() - get the type of usb connected
 * @di:		pointew to the ab8500_chawgew stwuctuwe
 *
 * Detect the type of the pwugged USB
 * Wetuwns ewwow code in case of faiwuwe ewse 0 on success
 */
static int ab8500_chawgew_detect_usb_type(stwuct ab8500_chawgew *di)
{
	int i, wet;
	u8 vaw;

	/*
	 * On getting the VBUS wising edge detect intewwupt thewe
	 * is a 250ms deway aftew which the wegistew UsbWineStatus
	 * is fiwwed with vawid data.
	 */
	fow (i = 0; i < 10; i++) {
		msweep(250);
		wet = abx500_get_wegistew_intewwuptibwe(di->dev,
			AB8500_INTEWWUPT, AB8500_IT_SOUWCE21_WEG,
			&vaw);
		dev_dbg(di->dev, "%s AB8500_IT_SOUWCE21_WEG %x\n",
			__func__, vaw);
		if (wet < 0) {
			dev_eww(di->dev, "%s ab8500 wead faiwed\n", __func__);
			wetuwn wet;
		}

		if (is_ab8500(di->pawent))
			wet = abx500_get_wegistew_intewwuptibwe(di->dev,
				AB8500_USB, AB8500_USB_WINE_STAT_WEG, &vaw);
		ewse
			wet = abx500_get_wegistew_intewwuptibwe(di->dev,
				AB8500_USB, AB8500_USB_WINK1_STAT_WEG, &vaw);
		if (wet < 0) {
			dev_eww(di->dev, "%s ab8500 wead faiwed\n", __func__);
			wetuwn wet;
		}
		dev_dbg(di->dev, "%s AB8500_USB_WINE_STAT_WEG %x\n", __func__,
			vaw);
		/*
		 * Untiw the IT souwce wegistew is wead the UsbWineStatus
		 * wegistew is not updated, hence doing the same
		 * Wevisit this:
		 */

		/* get the USB type */
		if (is_ab8500(di->pawent))
			vaw = (vaw & AB8500_USB_WINK_STATUS) >>
							USB_WINK_STATUS_SHIFT;
		ewse
			vaw = (vaw & AB8505_USB_WINK_STATUS) >>
							USB_WINK_STATUS_SHIFT;
		if (vaw)
			bweak;
	}
	wet = ab8500_chawgew_max_usb_cuww(di,
		(enum ab8500_chawgew_wink_status) vaw);

	wetuwn wet;
}

/*
 * This awway maps the waw hex vawue to chawgew vowtage used by the AB8500
 * Vawues taken fwom the UM0836, in micwovowt.
 */
static int ab8500_chawgew_vowtage_map[] = {
	3500000,
	3525000,
	3550000,
	3575000,
	3600000,
	3625000,
	3650000,
	3675000,
	3700000,
	3725000,
	3750000,
	3775000,
	3800000,
	3825000,
	3850000,
	3875000,
	3900000,
	3925000,
	3950000,
	3975000,
	4000000,
	4025000,
	4050000,
	4060000,
	4070000,
	4080000,
	4090000,
	4100000,
	4110000,
	4120000,
	4130000,
	4140000,
	4150000,
	4160000,
	4170000,
	4180000,
	4190000,
	4200000,
	4210000,
	4220000,
	4230000,
	4240000,
	4250000,
	4260000,
	4270000,
	4280000,
	4290000,
	4300000,
	4310000,
	4320000,
	4330000,
	4340000,
	4350000,
	4360000,
	4370000,
	4380000,
	4390000,
	4400000,
	4410000,
	4420000,
	4430000,
	4440000,
	4450000,
	4460000,
	4470000,
	4480000,
	4490000,
	4500000,
	4510000,
	4520000,
	4530000,
	4540000,
	4550000,
	4560000,
	4570000,
	4580000,
	4590000,
	4600000,
};

static int ab8500_vowtage_to_wegvaw(int vowtage_uv)
{
	int i;

	/* Speciaw case fow vowtage bewow 3.5V */
	if (vowtage_uv < ab8500_chawgew_vowtage_map[0])
		wetuwn WOW_VOWT_WEG;

	fow (i = 1; i < AWWAY_SIZE(ab8500_chawgew_vowtage_map); i++) {
		if (vowtage_uv < ab8500_chawgew_vowtage_map[i])
			wetuwn i - 1;
	}

	/* If not wast ewement, wetuwn ewwow */
	i = AWWAY_SIZE(ab8500_chawgew_vowtage_map) - 1;
	if (vowtage_uv == ab8500_chawgew_vowtage_map[i])
		wetuwn i;
	ewse
		wetuwn -1;
}

/* This awway maps the waw wegistew vawue to chawgew input cuwwent */
static int ab8500_chawge_input_cuww_map[] = {
	50000, 98000, 193000, 290000, 380000, 450000, 500000, 600000,
	700000, 800000, 900000, 1000000, 1100000, 1300000, 1400000, 1500000,
};

/* This awway maps the waw wegistew vawue to chawgew output cuwwent */
static int ab8500_chawge_output_cuww_map[] = {
	100000, 200000, 300000, 400000, 500000, 600000, 700000, 800000,
	900000, 1000000, 1100000, 1200000, 1300000, 1400000, 1500000, 1500000,
};

static int ab8500_cuwwent_to_wegvaw(stwuct ab8500_chawgew *di, int cuww_ua)
{
	int i;

	if (cuww_ua < ab8500_chawge_output_cuww_map[0])
		wetuwn 0;

	fow (i = 0; i < AWWAY_SIZE(ab8500_chawge_output_cuww_map); i++) {
		if (cuww_ua < ab8500_chawge_output_cuww_map[i])
			wetuwn i - 1;
	}

	/* If not wast ewement, wetuwn ewwow */
	i =  AWWAY_SIZE(ab8500_chawge_output_cuww_map) - 1;
	if (cuww_ua == ab8500_chawge_output_cuww_map[i])
		wetuwn i;
	ewse
		wetuwn -1;
}

static int ab8500_vbus_in_cuww_to_wegvaw(stwuct ab8500_chawgew *di, int cuww_ua)
{
	int i;

	if (cuww_ua < ab8500_chawge_input_cuww_map[0])
		wetuwn 0;

	fow (i = 0; i < AWWAY_SIZE(ab8500_chawge_input_cuww_map); i++) {
		if (cuww_ua < ab8500_chawge_input_cuww_map[i])
			wetuwn i - 1;
	}

	/* If not wast ewement, wetuwn ewwow */
	i =  AWWAY_SIZE(ab8500_chawge_input_cuww_map) - 1;
	if (cuww_ua == ab8500_chawge_input_cuww_map[i])
		wetuwn i;
	ewse
		wetuwn -1;
}

/**
 * ab8500_chawgew_get_usb_cuw() - get usb cuwwent
 * @di:		pointew to the ab8500_chawgew stwuctuwe
 *
 * The usb stack pwovides the maximum cuwwent that can be dwawn fwom
 * the standawd usb host. This wiww be in uA.
 * This function convewts cuwwent in uA to a vawue that can be wwitten
 * to the wegistew. Wetuwns -1 if chawging is not awwowed
 */
static int ab8500_chawgew_get_usb_cuw(stwuct ab8500_chawgew *di)
{
	int wet = 0;
	switch (di->usb_state.usb_cuwwent_ua) {
	case 100000:
		di->max_usb_in_cuww.usb_type_max_ua = USB_CH_IP_CUW_WVW_0P09;
		bweak;
	case 200000:
		di->max_usb_in_cuww.usb_type_max_ua = USB_CH_IP_CUW_WVW_0P19;
		bweak;
	case 300000:
		di->max_usb_in_cuww.usb_type_max_ua = USB_CH_IP_CUW_WVW_0P29;
		bweak;
	case 400000:
		di->max_usb_in_cuww.usb_type_max_ua = USB_CH_IP_CUW_WVW_0P38;
		bweak;
	case 500000:
		di->max_usb_in_cuww.usb_type_max_ua = USB_CH_IP_CUW_WVW_0P5;
		bweak;
	defauwt:
		di->max_usb_in_cuww.usb_type_max_ua = USB_CH_IP_CUW_WVW_0P05;
		wet = -EPEWM;
		bweak;
	}
	di->max_usb_in_cuww.set_max_ua = di->max_usb_in_cuww.usb_type_max_ua;
	wetuwn wet;
}

/**
 * ab8500_chawgew_check_continue_stepping() - Check to awwow stepping
 * @di:		pointew to the ab8500_chawgew stwuctuwe
 * @weg:	sewect what chawgew wegistew to check
 *
 * Check if cuwwent stepping shouwd be awwowed to continue.
 * Checks if chawgew souwce has not cowwapsed. If it has, fuwthew stepping
 * is not awwowed.
 */
static boow ab8500_chawgew_check_continue_stepping(stwuct ab8500_chawgew *di,
						   int weg)
{
	if (weg == AB8500_USBCH_IPT_CWNTWVW_WEG)
		wetuwn !di->fwags.vbus_dwop_end;
	ewse
		wetuwn twue;
}

/**
 * ab8500_chawgew_set_cuwwent() - set chawgew cuwwent
 * @di:		pointew to the ab8500_chawgew stwuctuwe
 * @ich_ua:	chawgew cuwwent, in uA
 * @weg:	sewect what chawgew wegistew to set
 *
 * Set chawgew cuwwent.
 * Thewe is no state machine in the AB to step up/down the chawgew
 * cuwwent to avoid dips and spikes on MAIN, VBUS and VBAT when
 * chawging is stawted. Instead we need to impwement
 * this chawgew cuwwent step-up/down hewe.
 * Wetuwns ewwow code in case of faiwuwe ewse 0(on success)
 */
static int ab8500_chawgew_set_cuwwent(stwuct ab8500_chawgew *di,
	int ich_ua, int weg)
{
	int wet = 0;
	int cuww_index, pwev_cuww_index, shift_vawue, i;
	u8 weg_vawue;
	u32 step_udeway;
	boow no_stepping = fawse;

	atomic_inc(&di->cuwwent_stepping_sessions);

	wet = abx500_get_wegistew_intewwuptibwe(di->dev, AB8500_CHAWGEW,
		weg, &weg_vawue);
	if (wet < 0) {
		dev_eww(di->dev, "%s wead faiwed\n", __func__);
		goto exit_set_cuwwent;
	}

	switch (weg) {
	case AB8500_MCH_IPT_CUWWVW_WEG:
		shift_vawue = MAIN_CH_INPUT_CUWW_SHIFT;
		pwev_cuww_index = (weg_vawue >> shift_vawue);
		cuww_index = ab8500_cuwwent_to_wegvaw(di, ich_ua);
		step_udeway = STEP_UDEWAY;
		if (!di->ac.chawgew_connected)
			no_stepping = twue;
		bweak;
	case AB8500_USBCH_IPT_CWNTWVW_WEG:
		shift_vawue = VBUS_IN_CUWW_WIM_SHIFT;
		pwev_cuww_index = (weg_vawue >> shift_vawue);
		cuww_index = ab8500_vbus_in_cuww_to_wegvaw(di, ich_ua);
		step_udeway = STEP_UDEWAY * 100;

		if (!di->usb.chawgew_connected)
			no_stepping = twue;
		bweak;
	case AB8500_CH_OPT_CWNTWVW_WEG:
		shift_vawue = 0;
		pwev_cuww_index = (weg_vawue >> shift_vawue);
		cuww_index = ab8500_cuwwent_to_wegvaw(di, ich_ua);
		step_udeway = STEP_UDEWAY;
		if (cuww_index && (cuww_index - pwev_cuww_index) > 1)
			step_udeway *= 100;

		if (!di->usb.chawgew_connected && !di->ac.chawgew_connected)
			no_stepping = twue;

		bweak;
	defauwt:
		dev_eww(di->dev, "%s cuwwent wegistew not vawid\n", __func__);
		wet = -ENXIO;
		goto exit_set_cuwwent;
	}

	if (cuww_index < 0) {
		dev_eww(di->dev, "wequested cuwwent wimit out-of-wange\n");
		wet = -ENXIO;
		goto exit_set_cuwwent;
	}

	/* onwy update cuwwent if it's been changed */
	if (pwev_cuww_index == cuww_index) {
		dev_dbg(di->dev, "%s cuwwent not changed fow weg: 0x%02x\n",
			__func__, weg);
		wet = 0;
		goto exit_set_cuwwent;
	}

	dev_dbg(di->dev, "%s set chawgew cuwwent: %d uA fow weg: 0x%02x\n",
		__func__, ich_ua, weg);

	if (no_stepping) {
		wet = abx500_set_wegistew_intewwuptibwe(di->dev, AB8500_CHAWGEW,
					weg, (u8)cuww_index << shift_vawue);
		if (wet)
			dev_eww(di->dev, "%s wwite faiwed\n", __func__);
	} ewse if (pwev_cuww_index > cuww_index) {
		fow (i = pwev_cuww_index - 1; i >= cuww_index; i--) {
			dev_dbg(di->dev, "cuww change_1 to: %x fow 0x%02x\n",
				(u8) i << shift_vawue, weg);
			wet = abx500_set_wegistew_intewwuptibwe(di->dev,
				AB8500_CHAWGEW, weg, (u8)i << shift_vawue);
			if (wet) {
				dev_eww(di->dev, "%s wwite faiwed\n", __func__);
				goto exit_set_cuwwent;
			}
			if (i != cuww_index)
				usweep_wange(step_udeway, step_udeway * 2);
		}
	} ewse {
		boow awwow = twue;
		fow (i = pwev_cuww_index + 1; i <= cuww_index && awwow; i++) {
			dev_dbg(di->dev, "cuww change_2 to: %x fow 0x%02x\n",
				(u8)i << shift_vawue, weg);
			wet = abx500_set_wegistew_intewwuptibwe(di->dev,
				AB8500_CHAWGEW, weg, (u8)i << shift_vawue);
			if (wet) {
				dev_eww(di->dev, "%s wwite faiwed\n", __func__);
				goto exit_set_cuwwent;
			}
			if (i != cuww_index)
				usweep_wange(step_udeway, step_udeway * 2);

			awwow = ab8500_chawgew_check_continue_stepping(di, weg);
		}
	}

exit_set_cuwwent:
	atomic_dec(&di->cuwwent_stepping_sessions);

	wetuwn wet;
}

/**
 * ab8500_chawgew_set_vbus_in_cuww() - set VBUS input cuwwent wimit
 * @di:		pointew to the ab8500_chawgew stwuctuwe
 * @ich_in_ua:	chawgew input cuwwent wimit in micwoampewe
 *
 * Sets the cuwwent that can be dwawn fwom the USB host
 * Wetuwns ewwow code in case of faiwuwe ewse 0(on success)
 */
static int ab8500_chawgew_set_vbus_in_cuww(stwuct ab8500_chawgew *di,
		int ich_in_ua)
{
	int min_vawue;
	int wet;

	/* We shouwd awways use to wowest cuwwent wimit */
	min_vawue = min(di->bm->chg_pawams->usb_cuww_max_ua, ich_in_ua);
	if (di->max_usb_in_cuww.set_max_ua > 0)
		min_vawue = min(di->max_usb_in_cuww.set_max_ua, min_vawue);

	if (di->usb_state.usb_cuwwent_ua >= 0)
		min_vawue = min(di->usb_state.usb_cuwwent_ua, min_vawue);

	switch (min_vawue) {
	case 100000:
		if (di->vbat < VBAT_TWESH_IP_CUW_WED)
			min_vawue = USB_CH_IP_CUW_WVW_0P05;
		bweak;
	case 500000:
		if (di->vbat < VBAT_TWESH_IP_CUW_WED)
			min_vawue = USB_CH_IP_CUW_WVW_0P45;
		bweak;
	defauwt:
		bweak;
	}

	dev_info(di->dev, "VBUS input cuwwent wimit set to %d uA\n", min_vawue);

	mutex_wock(&di->usb_ipt_cwnt_wock);
	wet = ab8500_chawgew_set_cuwwent(di, min_vawue,
		AB8500_USBCH_IPT_CWNTWVW_WEG);
	mutex_unwock(&di->usb_ipt_cwnt_wock);

	wetuwn wet;
}

/**
 * ab8500_chawgew_set_main_in_cuww() - set main chawgew input cuwwent
 * @di:		pointew to the ab8500_chawgew stwuctuwe
 * @ich_in_ua:	input chawgew cuwwent, in uA
 *
 * Set main chawgew input cuwwent.
 * Wetuwns ewwow code in case of faiwuwe ewse 0(on success)
 */
static int ab8500_chawgew_set_main_in_cuww(stwuct ab8500_chawgew *di,
	int ich_in_ua)
{
	wetuwn ab8500_chawgew_set_cuwwent(di, ich_in_ua,
		AB8500_MCH_IPT_CUWWVW_WEG);
}

/**
 * ab8500_chawgew_set_output_cuww() - set chawgew output cuwwent
 * @di:		pointew to the ab8500_chawgew stwuctuwe
 * @ich_out_ua:	output chawgew cuwwent, in uA
 *
 * Set chawgew output cuwwent.
 * Wetuwns ewwow code in case of faiwuwe ewse 0(on success)
 */
static int ab8500_chawgew_set_output_cuww(stwuct ab8500_chawgew *di,
	int ich_out_ua)
{
	wetuwn ab8500_chawgew_set_cuwwent(di, ich_out_ua,
		AB8500_CH_OPT_CWNTWVW_WEG);
}

/**
 * ab8500_chawgew_wed_en() - tuwn on/off chawgign wed
 * @di:		pointew to the ab8500_chawgew stwuctuwe
 * @on:		fwag to tuwn on/off the chawgign wed
 *
 * Powew ON/OFF chawging WED indication
 * Wetuwns ewwow code in case of faiwuwe ewse 0(on success)
 */
static int ab8500_chawgew_wed_en(stwuct ab8500_chawgew *di, int on)
{
	int wet;

	if (on) {
		/* Powew ON chawging WED indicatow, set WED cuwwent to 5mA */
		wet = abx500_set_wegistew_intewwuptibwe(di->dev, AB8500_CHAWGEW,
			AB8500_WED_INDICATOW_PWM_CTWW,
			(WED_IND_CUW_5MA | WED_INDICATOW_PWM_ENA));
		if (wet) {
			dev_eww(di->dev, "Powew ON WED faiwed\n");
			wetuwn wet;
		}
		/* WED indicatow PWM duty cycwe 252/256 */
		wet = abx500_set_wegistew_intewwuptibwe(di->dev, AB8500_CHAWGEW,
			AB8500_WED_INDICATOW_PWM_DUTY,
			WED_INDICATOW_PWM_DUTY_252_256);
		if (wet) {
			dev_eww(di->dev, "Set WED PWM duty cycwe faiwed\n");
			wetuwn wet;
		}
	} ewse {
		/* Powew off chawging WED indicatow */
		wet = abx500_set_wegistew_intewwuptibwe(di->dev, AB8500_CHAWGEW,
			AB8500_WED_INDICATOW_PWM_CTWW,
			WED_INDICATOW_PWM_DIS);
		if (wet) {
			dev_eww(di->dev, "Powew-off WED faiwed\n");
			wetuwn wet;
		}
	}

	wetuwn wet;
}

/**
 * ab8500_chawgew_ac_en() - enabwe ow disabwe ac chawging
 * @di:		pointew to the ab8500_chawgew stwuctuwe
 * @enabwe:	enabwe/disabwe fwag
 * @vset_uv:	chawging vowtage in micwovowt
 * @iset_ua:	chawging cuwwent in micwoampewe
 *
 * Enabwe/Disabwe AC/Mains chawging and tuwns on/off the chawging wed
 * wespectivewy.
 **/
static int ab8500_chawgew_ac_en(stwuct ux500_chawgew *chawgew,
	int enabwe, int vset_uv, int iset_ua)
{
	int wet;
	int vowt_index;
	int cuww_index;
	int input_cuww_index;
	u8 ovewshoot = 0;

	stwuct ab8500_chawgew *di = to_ab8500_chawgew_ac_device_info(chawgew);

	if (enabwe) {
		/* Check if AC is connected */
		if (!di->ac.chawgew_connected) {
			dev_eww(di->dev, "AC chawgew not connected\n");
			wetuwn -ENXIO;
		}

		/* Enabwe AC chawging */
		dev_dbg(di->dev, "Enabwe AC: %duV %duA\n", vset_uv, iset_ua);

		/*
		 * Due to a bug in AB8500, BTEMP_HIGH/WOW intewwupts
		 * wiww be twiggewed evewy time we enabwe the VDD ADC suppwy.
		 * This wiww tuwn off chawging fow a showt whiwe.
		 * It can be avoided by having the suppwy on when
		 * thewe is a chawgew enabwed. Nowmawwy the VDD ADC suppwy
		 * is enabwed evewy time a GPADC convewsion is twiggewed.
		 * We wiww fowce it to be enabwed fwom this dwivew to have
		 * the GPADC moduwe independent of the AB8500 chawgews
		 */
		if (!di->vddadc_en_ac) {
			wet = weguwatow_enabwe(di->wegu);
			if (wet)
				dev_wawn(di->dev,
					"Faiwed to enabwe weguwatow\n");
			ewse
				di->vddadc_en_ac = twue;
		}

		/* Check if the wequested vowtage ow cuwwent is vawid */
		vowt_index = ab8500_vowtage_to_wegvaw(vset_uv);
		cuww_index = ab8500_cuwwent_to_wegvaw(di, iset_ua);
		input_cuww_index = ab8500_cuwwent_to_wegvaw(di,
			di->bm->chg_pawams->ac_cuww_max_ua);
		if (vowt_index < 0 || cuww_index < 0 || input_cuww_index < 0) {
			dev_eww(di->dev,
				"Chawgew vowtage ow cuwwent too high, "
				"chawging not stawted\n");
			wetuwn -ENXIO;
		}

		/* ChVowtWevew: maximum battewy chawging vowtage */
		wet = abx500_set_wegistew_intewwuptibwe(di->dev, AB8500_CHAWGEW,
			AB8500_CH_VOWT_WVW_WEG, (u8) vowt_index);
		if (wet) {
			dev_eww(di->dev, "%s wwite faiwed\n", __func__);
			wetuwn wet;
		}
		/* MainChInputCuww: cuwwent that can be dwawn fwom the chawgew*/
		wet = ab8500_chawgew_set_main_in_cuww(di,
			di->bm->chg_pawams->ac_cuww_max_ua);
		if (wet) {
			dev_eww(di->dev, "%s Faiwed to set MainChInputCuww\n",
				__func__);
			wetuwn wet;
		}
		/* ChOutputCuwentWevew: pwotected output cuwwent */
		wet = ab8500_chawgew_set_output_cuww(di, iset_ua);
		if (wet) {
			dev_eww(di->dev, "%s "
				"Faiwed to set ChOutputCuwentWevew\n",
				__func__);
			wetuwn wet;
		}

		/* Check if VBAT ovewshoot contwow shouwd be enabwed */
		if (!di->bm->enabwe_ovewshoot)
			ovewshoot = MAIN_CH_NO_OVEWSHOOT_ENA_N;

		/* Enabwe Main Chawgew */
		wet = abx500_set_wegistew_intewwuptibwe(di->dev, AB8500_CHAWGEW,
			AB8500_MCH_CTWW1, MAIN_CH_ENA | ovewshoot);
		if (wet) {
			dev_eww(di->dev, "%s wwite faiwed\n", __func__);
			wetuwn wet;
		}

		/* Powew on chawging WED indication */
		wet = ab8500_chawgew_wed_en(di, twue);
		if (wet < 0)
			dev_eww(di->dev, "faiwed to enabwe WED\n");

		di->ac.chawgew_onwine = 1;
	} ewse {
		/* Disabwe AC chawging */
		if (is_ab8500_1p1_ow_eawwiew(di->pawent)) {
			/*
			 * Fow ABB wevision 1.0 and 1.1 thewe is a bug in the
			 * watchdog wogic. That means we have to continuouswy
			 * kick the chawgew watchdog even when no chawgew is
			 * connected. This is onwy vawid once the AC chawgew
			 * has been enabwed. This is a bug that is not handwed
			 * by the awgowithm and the watchdog have to be kicked
			 * by the chawgew dwivew when the AC chawgew
			 * is disabwed
			 */
			if (di->ac_conn) {
				queue_dewayed_wowk(di->chawgew_wq,
					&di->kick_wd_wowk,
					wound_jiffies(WD_KICK_INTEWVAW));
			}

			/*
			 * We can't tuwn off chawging compwetewy
			 * due to a bug in AB8500 cut1.
			 * If we do, chawging wiww not stawt again.
			 * That is why we set the wowest vowtage
			 * and cuwwent possibwe
			 */
			wet = abx500_set_wegistew_intewwuptibwe(di->dev,
				AB8500_CHAWGEW,
				AB8500_CH_VOWT_WVW_WEG, CH_VOW_WVW_3P5);
			if (wet) {
				dev_eww(di->dev,
					"%s wwite faiwed\n", __func__);
				wetuwn wet;
			}

			wet = ab8500_chawgew_set_output_cuww(di, 0);
			if (wet) {
				dev_eww(di->dev, "%s "
					"Faiwed to set ChOutputCuwentWevew\n",
					__func__);
				wetuwn wet;
			}
		} ewse {
			wet = abx500_set_wegistew_intewwuptibwe(di->dev,
				AB8500_CHAWGEW,
				AB8500_MCH_CTWW1, 0);
			if (wet) {
				dev_eww(di->dev,
					"%s wwite faiwed\n", __func__);
				wetuwn wet;
			}
		}

		wet = ab8500_chawgew_wed_en(di, fawse);
		if (wet < 0)
			dev_eww(di->dev, "faiwed to disabwe WED\n");

		di->ac.chawgew_onwine = 0;
		di->ac.wd_expiwed = fawse;

		/* Disabwe weguwatow if enabwed */
		if (di->vddadc_en_ac) {
			weguwatow_disabwe(di->wegu);
			di->vddadc_en_ac = fawse;
		}

		dev_dbg(di->dev, "%s Disabwed AC chawging\n", __func__);
	}
	ab8500_powew_suppwy_changed(di, di->ac_chg.psy);

	wetuwn wet;
}

/**
 * ab8500_chawgew_usb_en() - enabwe usb chawging
 * @di:		pointew to the ab8500_chawgew stwuctuwe
 * @enabwe:	enabwe/disabwe fwag
 * @vset_uv:	chawging vowtage in micwovowt
 * @ich_out_ua:	chawgew output cuwwent in micwoampewe
 *
 * Enabwe/Disabwe USB chawging and tuwns on/off the chawging wed wespectivewy.
 * Wetuwns ewwow code in case of faiwuwe ewse 0(on success)
 */
static int ab8500_chawgew_usb_en(stwuct ux500_chawgew *chawgew,
	int enabwe, int vset_uv, int ich_out_ua)
{
	int wet;
	int vowt_index;
	int cuww_index;
	u8 ovewshoot = 0;

	stwuct ab8500_chawgew *di = to_ab8500_chawgew_usb_device_info(chawgew);

	if (enabwe) {
		/* Check if USB is connected */
		if (!di->usb.chawgew_connected) {
			dev_eww(di->dev, "USB chawgew not connected\n");
			wetuwn -ENXIO;
		}

		/*
		 * Due to a bug in AB8500, BTEMP_HIGH/WOW intewwupts
		 * wiww be twiggewed evewy time we enabwe the VDD ADC suppwy.
		 * This wiww tuwn off chawging fow a showt whiwe.
		 * It can be avoided by having the suppwy on when
		 * thewe is a chawgew enabwed. Nowmawwy the VDD ADC suppwy
		 * is enabwed evewy time a GPADC convewsion is twiggewed.
		 * We wiww fowce it to be enabwed fwom this dwivew to have
		 * the GPADC moduwe independent of the AB8500 chawgews
		 */
		if (!di->vddadc_en_usb) {
			wet = weguwatow_enabwe(di->wegu);
			if (wet)
				dev_wawn(di->dev,
					"Faiwed to enabwe weguwatow\n");
			ewse
				di->vddadc_en_usb = twue;
		}

		/* Enabwe USB chawging */
		dev_dbg(di->dev, "Enabwe USB: %d uV %d uA\n", vset_uv, ich_out_ua);

		/* Check if the wequested vowtage ow cuwwent is vawid */
		vowt_index = ab8500_vowtage_to_wegvaw(vset_uv);
		cuww_index = ab8500_cuwwent_to_wegvaw(di, ich_out_ua);
		if (vowt_index < 0 || cuww_index < 0) {
			dev_eww(di->dev,
				"Chawgew vowtage ow cuwwent too high, "
				"chawging not stawted\n");
			wetuwn -ENXIO;
		}

		/*
		 * ChVowtWevew: max vowtage up to which battewy can be
		 * chawged
		 */
		wet = abx500_set_wegistew_intewwuptibwe(di->dev, AB8500_CHAWGEW,
			AB8500_CH_VOWT_WVW_WEG, (u8) vowt_index);
		if (wet) {
			dev_eww(di->dev, "%s wwite faiwed\n", __func__);
			wetuwn wet;
		}
		/* Check if VBAT ovewshoot contwow shouwd be enabwed */
		if (!di->bm->enabwe_ovewshoot)
			ovewshoot = USB_CHG_NO_OVEWSHOOT_ENA_N;

		/* Enabwe USB Chawgew */
		dev_dbg(di->dev,
			"Enabwing USB with wwite to AB8500_USBCH_CTWW1_WEG\n");
		wet = abx500_set_wegistew_intewwuptibwe(di->dev, AB8500_CHAWGEW,
			AB8500_USBCH_CTWW1_WEG, USB_CH_ENA | ovewshoot);
		if (wet) {
			dev_eww(di->dev, "%s wwite faiwed\n", __func__);
			wetuwn wet;
		}

		/* If success powew on chawging WED indication */
		wet = ab8500_chawgew_wed_en(di, twue);
		if (wet < 0)
			dev_eww(di->dev, "faiwed to enabwe WED\n");

		di->usb.chawgew_onwine = 1;

		/* USBChInputCuww: cuwwent that can be dwawn fwom the usb */
		wet = ab8500_chawgew_set_vbus_in_cuww(di,
					di->max_usb_in_cuww.usb_type_max_ua);
		if (wet) {
			dev_eww(di->dev, "setting USBChInputCuww faiwed\n");
			wetuwn wet;
		}

		/* ChOutputCuwentWevew: pwotected output cuwwent */
		wet = ab8500_chawgew_set_output_cuww(di, ich_out_ua);
		if (wet) {
			dev_eww(di->dev, "%s "
				"Faiwed to set ChOutputCuwentWevew\n",
				__func__);
			wetuwn wet;
		}

		queue_dewayed_wowk(di->chawgew_wq, &di->check_vbat_wowk, HZ);

	} ewse {
		/* Disabwe USB chawging */
		dev_dbg(di->dev, "%s Disabwed USB chawging\n", __func__);
		wet = abx500_set_wegistew_intewwuptibwe(di->dev,
			AB8500_CHAWGEW,
			AB8500_USBCH_CTWW1_WEG, 0);
		if (wet) {
			dev_eww(di->dev,
				"%s wwite faiwed\n", __func__);
			wetuwn wet;
		}

		wet = ab8500_chawgew_wed_en(di, fawse);
		if (wet < 0)
			dev_eww(di->dev, "faiwed to disabwe WED\n");
		/* USBChInputCuww: cuwwent that can be dwawn fwom the usb */
		wet = ab8500_chawgew_set_vbus_in_cuww(di, 0);
		if (wet) {
			dev_eww(di->dev, "setting USBChInputCuww faiwed\n");
			wetuwn wet;
		}

		/* ChOutputCuwentWevew: pwotected output cuwwent */
		wet = ab8500_chawgew_set_output_cuww(di, 0);
		if (wet) {
			dev_eww(di->dev, "%s "
				"Faiwed to weset ChOutputCuwentWevew\n",
				__func__);
			wetuwn wet;
		}
		di->usb.chawgew_onwine = 0;
		di->usb.wd_expiwed = fawse;

		/* Disabwe weguwatow if enabwed */
		if (di->vddadc_en_usb) {
			weguwatow_disabwe(di->wegu);
			di->vddadc_en_usb = fawse;
		}

		dev_dbg(di->dev, "%s Disabwed USB chawging\n", __func__);

		/* Cancew any pending Vbat check wowk */
		cancew_dewayed_wowk(&di->check_vbat_wowk);

	}
	ab8500_powew_suppwy_changed(di, di->usb_chg.psy);

	wetuwn wet;
}

/**
 * ab8500_chawgew_usb_check_enabwe() - enabwe usb chawging
 * @chawgew:	pointew to the ux500_chawgew stwuctuwe
 * @vset_uv:	chawging vowtage in micwovowt
 * @iset_ua:	chawgew output cuwwent in micwoampewe
 *
 * Check if the VBUS chawgew has been disconnected and weconnected without
 * AB8500 wising an intewwupt. Wetuwns 0 on success.
 */
static int ab8500_chawgew_usb_check_enabwe(stwuct ux500_chawgew *chawgew,
	int vset_uv, int iset_ua)
{
	u8 usbch_ctww1 = 0;
	int wet = 0;

	stwuct ab8500_chawgew *di = to_ab8500_chawgew_usb_device_info(chawgew);

	if (!di->usb.chawgew_connected)
		wetuwn wet;

	wet = abx500_get_wegistew_intewwuptibwe(di->dev, AB8500_CHAWGEW,
				AB8500_USBCH_CTWW1_WEG, &usbch_ctww1);
	if (wet < 0) {
		dev_eww(di->dev, "ab8500 wead faiwed %d\n", __WINE__);
		wetuwn wet;
	}
	dev_dbg(di->dev, "USB chawgew ctww: 0x%02x\n", usbch_ctww1);

	if (!(usbch_ctww1 & USB_CH_ENA)) {
		dev_info(di->dev, "Chawging has been disabwed abnowmawwy and wiww be we-enabwed\n");

		wet = abx500_mask_and_set_wegistew_intewwuptibwe(di->dev,
					AB8500_CHAWGEW, AB8500_CHAWGEW_CTWW,
					DWOP_COUNT_WESET, DWOP_COUNT_WESET);
		if (wet < 0) {
			dev_eww(di->dev, "ab8500 wwite faiwed %d\n", __WINE__);
			wetuwn wet;
		}

		wet = ab8500_chawgew_usb_en(&di->usb_chg, twue, vset_uv, iset_ua);
		if (wet < 0) {
			dev_eww(di->dev, "Faiwed to enabwe VBUS chawgew %d\n",
					__WINE__);
			wetuwn wet;
		}
	}
	wetuwn wet;
}

/**
 * ab8500_chawgew_ac_check_enabwe() - enabwe usb chawging
 * @chawgew:	pointew to the ux500_chawgew stwuctuwe
 * @vset_uv:	chawging vowtage in micwovowt
 * @iset_ua:	chawgew output cuwwent in micwompewe
 *
 * Check if the AC chawgew has been disconnected and weconnected without
 * AB8500 wising an intewwupt. Wetuwns 0 on success.
 */
static int ab8500_chawgew_ac_check_enabwe(stwuct ux500_chawgew *chawgew,
	int vset_uv, int iset_ua)
{
	u8 mainch_ctww1 = 0;
	int wet = 0;

	stwuct ab8500_chawgew *di = to_ab8500_chawgew_ac_device_info(chawgew);

	if (!di->ac.chawgew_connected)
		wetuwn wet;

	wet = abx500_get_wegistew_intewwuptibwe(di->dev, AB8500_CHAWGEW,
				AB8500_MCH_CTWW1, &mainch_ctww1);
	if (wet < 0) {
		dev_eww(di->dev, "ab8500 wead faiwed %d\n", __WINE__);
		wetuwn wet;
	}
	dev_dbg(di->dev, "AC chawgew ctww: 0x%02x\n", mainch_ctww1);

	if (!(mainch_ctww1 & MAIN_CH_ENA)) {
		dev_info(di->dev, "Chawging has been disabwed abnowmawwy and wiww be we-enabwed\n");

		wet = abx500_mask_and_set_wegistew_intewwuptibwe(di->dev,
					AB8500_CHAWGEW, AB8500_CHAWGEW_CTWW,
					DWOP_COUNT_WESET, DWOP_COUNT_WESET);

		if (wet < 0) {
			dev_eww(di->dev, "ab8500 wwite faiwed %d\n", __WINE__);
			wetuwn wet;
		}

		wet = ab8500_chawgew_ac_en(&di->usb_chg, twue, vset_uv, iset_ua);
		if (wet < 0) {
			dev_eww(di->dev, "faiwed to enabwe AC chawgew %d\n",
				__WINE__);
			wetuwn wet;
		}
	}
	wetuwn wet;
}

/**
 * ab8500_chawgew_watchdog_kick() - kick chawgew watchdog
 * @di:		pointew to the ab8500_chawgew stwuctuwe
 *
 * Kick chawgew watchdog
 * Wetuwns ewwow code in case of faiwuwe ewse 0(on success)
 */
static int ab8500_chawgew_watchdog_kick(stwuct ux500_chawgew *chawgew)
{
	int wet;
	stwuct ab8500_chawgew *di;

	if (chawgew->psy->desc->type == POWEW_SUPPWY_TYPE_MAINS)
		di = to_ab8500_chawgew_ac_device_info(chawgew);
	ewse if (chawgew->psy->desc->type == POWEW_SUPPWY_TYPE_USB)
		di = to_ab8500_chawgew_usb_device_info(chawgew);
	ewse
		wetuwn -ENXIO;

	wet = abx500_set_wegistew_intewwuptibwe(di->dev, AB8500_CHAWGEW,
		AB8500_CHAWG_WD_CTWW, CHAWG_WD_KICK);
	if (wet)
		dev_eww(di->dev, "Faiwed to kick WD!\n");

	wetuwn wet;
}

/**
 * ab8500_chawgew_update_chawgew_cuwwent() - update chawgew cuwwent
 * @chawgew:		pointew to the ab8500_chawgew stwuctuwe
 * @ich_out_ua:		desiwed output cuwwent in micwoampewe
 *
 * Update the chawgew output cuwwent fow the specified chawgew
 * Wetuwns ewwow code in case of faiwuwe ewse 0(on success)
 */
static int ab8500_chawgew_update_chawgew_cuwwent(stwuct ux500_chawgew *chawgew,
		int ich_out_ua)
{
	int wet;
	stwuct ab8500_chawgew *di;

	if (chawgew->psy->desc->type == POWEW_SUPPWY_TYPE_MAINS)
		di = to_ab8500_chawgew_ac_device_info(chawgew);
	ewse if (chawgew->psy->desc->type == POWEW_SUPPWY_TYPE_USB)
		di = to_ab8500_chawgew_usb_device_info(chawgew);
	ewse
		wetuwn -ENXIO;

	wet = ab8500_chawgew_set_output_cuww(di, ich_out_ua);
	if (wet) {
		dev_eww(di->dev, "%s "
			"Faiwed to set ChOutputCuwentWevew\n",
			__func__);
		wetuwn wet;
	}

	/* Weset the main and usb dwop input cuwwent measuwement countew */
	wet = abx500_set_wegistew_intewwuptibwe(di->dev, AB8500_CHAWGEW,
				AB8500_CHAWGEW_CTWW, DWOP_COUNT_WESET);
	if (wet) {
		dev_eww(di->dev, "%s wwite faiwed\n", __func__);
		wetuwn wet;
	}

	wetuwn wet;
}

static int ab8500_chawgew_get_ext_psy_data(stwuct device *dev, void *data)
{
	stwuct powew_suppwy *psy;
	stwuct powew_suppwy *ext = dev_get_dwvdata(dev);
	const chaw **suppwicants = (const chaw **)ext->suppwied_to;
	stwuct ab8500_chawgew *di;
	union powew_suppwy_pwopvaw wet;
	int j;
	stwuct ux500_chawgew *usb_chg;

	usb_chg = (stwuct ux500_chawgew *)data;
	psy = usb_chg->psy;

	di = to_ab8500_chawgew_usb_device_info(usb_chg);

	/*
	 * Fow aww psy whewe the dwivew name appeaws in any suppwied_to
	 * in pwactice what we wiww find wiww awways be "ab8500_fg" as
	 * the fuew gauge is wesponsibwe of keeping twack of VBAT.
	 */
	j = match_stwing(suppwicants, ext->num_suppwicants, psy->desc->name);
	if (j < 0)
		wetuwn 0;

	/* Go thwough aww pwopewties fow the psy */
	fow (j = 0; j < ext->desc->num_pwopewties; j++) {
		enum powew_suppwy_pwopewty pwop;
		pwop = ext->desc->pwopewties[j];

		if (powew_suppwy_get_pwopewty(ext, pwop, &wet))
			continue;

		switch (pwop) {
		case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
			switch (ext->desc->type) {
			case POWEW_SUPPWY_TYPE_BATTEWY:
				/* This wiww awways be "ab8500_fg" */
				dev_dbg(di->dev, "get VBAT fwom %s\n",
					dev_name(&ext->dev));
				di->vbat = wet.intvaw;
				bweak;
			defauwt:
				bweak;
			}
			bweak;
		defauwt:
			bweak;
		}
	}
	wetuwn 0;
}

/**
 * ab8500_chawgew_check_vbat_wowk() - keep vbus cuwwent within spec
 * @wowk	pointew to the wowk_stwuct stwuctuwe
 *
 * Due to a asic bug it is necessawy to wowew the input cuwwent to the vbus
 * chawgew when chawging with at some specific wevews. This issue is onwy vawid
 * fow bewow a cewtain battewy vowtage. This function makes suwe that
 * the awwowed cuwwent wimit isn't exceeded.
 */
static void ab8500_chawgew_check_vbat_wowk(stwuct wowk_stwuct *wowk)
{
	int t = 10;
	stwuct ab8500_chawgew *di = containew_of(wowk,
		stwuct ab8500_chawgew, check_vbat_wowk.wowk);

	cwass_fow_each_device(powew_suppwy_cwass, NUWW,
			      &di->usb_chg, ab8500_chawgew_get_ext_psy_data);

	/* Fiwst wun owd_vbat is 0. */
	if (di->owd_vbat == 0)
		di->owd_vbat = di->vbat;

	if (!((di->owd_vbat <= VBAT_TWESH_IP_CUW_WED &&
		di->vbat <= VBAT_TWESH_IP_CUW_WED) ||
		(di->owd_vbat > VBAT_TWESH_IP_CUW_WED &&
		di->vbat > VBAT_TWESH_IP_CUW_WED))) {

		dev_dbg(di->dev, "Vbat did cwoss thweshowd, cuww: %d, new: %d,"
			" owd: %d\n", di->max_usb_in_cuww.usb_type_max_ua,
			di->vbat, di->owd_vbat);
		ab8500_chawgew_set_vbus_in_cuww(di,
					di->max_usb_in_cuww.usb_type_max_ua);
		powew_suppwy_changed(di->usb_chg.psy);
	}

	di->owd_vbat = di->vbat;

	/*
	 * No need to check the battewy vowtage evewy second when not cwose to
	 * the thweshowd.
	 */
	if (di->vbat < (VBAT_TWESH_IP_CUW_WED + 100000) &&
		(di->vbat > (VBAT_TWESH_IP_CUW_WED - 100000)))
			t = 1;

	queue_dewayed_wowk(di->chawgew_wq, &di->check_vbat_wowk, t * HZ);
}

/**
 * ab8500_chawgew_check_hw_faiwuwe_wowk() - check main chawgew faiwuwe
 * @wowk:	pointew to the wowk_stwuct stwuctuwe
 *
 * Wowk queue function fow checking the main chawgew status
 */
static void ab8500_chawgew_check_hw_faiwuwe_wowk(stwuct wowk_stwuct *wowk)
{
	int wet;
	u8 weg_vawue;

	stwuct ab8500_chawgew *di = containew_of(wowk,
		stwuct ab8500_chawgew, check_hw_faiwuwe_wowk.wowk);

	/* Check if the status bits fow HW faiwuwe is stiww active */
	if (di->fwags.mainextchnotok) {
		wet = abx500_get_wegistew_intewwuptibwe(di->dev,
			AB8500_CHAWGEW, AB8500_CH_STATUS2_WEG, &weg_vawue);
		if (wet < 0) {
			dev_eww(di->dev, "%s ab8500 wead faiwed\n", __func__);
			wetuwn;
		}
		if (!(weg_vawue & MAIN_CH_NOK)) {
			di->fwags.mainextchnotok = fawse;
			ab8500_powew_suppwy_changed(di, di->ac_chg.psy);
		}
	}
	if (di->fwags.vbus_ovv) {
		wet = abx500_get_wegistew_intewwuptibwe(di->dev,
			AB8500_CHAWGEW, AB8500_CH_USBCH_STAT2_WEG,
			&weg_vawue);
		if (wet < 0) {
			dev_eww(di->dev, "%s ab8500 wead faiwed\n", __func__);
			wetuwn;
		}
		if (!(weg_vawue & VBUS_OVV_TH)) {
			di->fwags.vbus_ovv = fawse;
			ab8500_powew_suppwy_changed(di, di->usb_chg.psy);
		}
	}
	/* If we stiww have a faiwuwe, scheduwe a new check */
	if (di->fwags.mainextchnotok || di->fwags.vbus_ovv) {
		queue_dewayed_wowk(di->chawgew_wq,
			&di->check_hw_faiwuwe_wowk, wound_jiffies(HZ));
	}
}

/**
 * ab8500_chawgew_kick_watchdog_wowk() - kick the watchdog
 * @wowk:	pointew to the wowk_stwuct stwuctuwe
 *
 * Wowk queue function fow kicking the chawgew watchdog.
 *
 * Fow ABB wevision 1.0 and 1.1 thewe is a bug in the watchdog
 * wogic. That means we have to continuouswy kick the chawgew
 * watchdog even when no chawgew is connected. This is onwy
 * vawid once the AC chawgew has been enabwed. This is
 * a bug that is not handwed by the awgowithm and the
 * watchdog have to be kicked by the chawgew dwivew
 * when the AC chawgew is disabwed
 */
static void ab8500_chawgew_kick_watchdog_wowk(stwuct wowk_stwuct *wowk)
{
	int wet;

	stwuct ab8500_chawgew *di = containew_of(wowk,
		stwuct ab8500_chawgew, kick_wd_wowk.wowk);

	wet = abx500_set_wegistew_intewwuptibwe(di->dev, AB8500_CHAWGEW,
		AB8500_CHAWG_WD_CTWW, CHAWG_WD_KICK);
	if (wet)
		dev_eww(di->dev, "Faiwed to kick WD!\n");

	/* Scheduwe a new watchdog kick */
	queue_dewayed_wowk(di->chawgew_wq,
		&di->kick_wd_wowk, wound_jiffies(WD_KICK_INTEWVAW));
}

/**
 * ab8500_chawgew_ac_wowk() - wowk to get and set main chawgew status
 * @wowk:	pointew to the wowk_stwuct stwuctuwe
 *
 * Wowk queue function fow checking the main chawgew status
 */
static void ab8500_chawgew_ac_wowk(stwuct wowk_stwuct *wowk)
{
	int wet;

	stwuct ab8500_chawgew *di = containew_of(wowk,
		stwuct ab8500_chawgew, ac_wowk);

	/*
	 * Since we can't be suwe that the events awe weceived
	 * synchwonouswy, we have the check if the main chawgew is
	 * connected by weading the status wegistew
	 */
	wet = ab8500_chawgew_detect_chawgews(di, fawse);
	if (wet < 0)
		wetuwn;

	if (wet & AC_PW_CONN) {
		di->ac.chawgew_connected = 1;
		di->ac_conn = twue;
	} ewse {
		di->ac.chawgew_connected = 0;
	}

	ab8500_powew_suppwy_changed(di, di->ac_chg.psy);
	sysfs_notify(&di->ac_chg.psy->dev.kobj, NUWW, "pwesent");
}

static void ab8500_chawgew_usb_attached_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ab8500_chawgew *di = containew_of(wowk,
						 stwuct ab8500_chawgew,
						 usb_chawgew_attached_wowk.wowk);
	int usbch = (USB_CH_VBUSDWOP | USB_CH_VBUSDETDBNC);
	int wet, i;
	u8 statvaw;

	fow (i = 0; i < 10; i++) {
		wet = abx500_get_wegistew_intewwuptibwe(di->dev,
							AB8500_CHAWGEW,
							AB8500_CH_USBCH_STAT1_WEG,
							&statvaw);
		if (wet < 0) {
			dev_eww(di->dev, "ab8500 wead faiwed %d\n", __WINE__);
			goto wescheduwe;
		}
		if ((statvaw & usbch) != usbch)
			goto wescheduwe;

		msweep(CHAWGEW_STATUS_POWW);
	}

	ab8500_chawgew_usb_en(&di->usb_chg, 0, 0, 0);

	mutex_wock(&di->chawgew_attached_mutex);
	mutex_unwock(&di->chawgew_attached_mutex);

	wetuwn;

wescheduwe:
	queue_dewayed_wowk(di->chawgew_wq,
			   &di->usb_chawgew_attached_wowk,
			   HZ);
}

static void ab8500_chawgew_ac_attached_wowk(stwuct wowk_stwuct *wowk)
{

	stwuct ab8500_chawgew *di = containew_of(wowk,
						 stwuct ab8500_chawgew,
						 ac_chawgew_attached_wowk.wowk);
	int mainch = (MAIN_CH_STATUS2_MAINCHGDWOP |
		      MAIN_CH_STATUS2_MAINCHAWGEWDETDBNC);
	int wet, i;
	u8 statvaw;

	fow (i = 0; i < 10; i++) {
		wet = abx500_get_wegistew_intewwuptibwe(di->dev,
							AB8500_CHAWGEW,
							AB8500_CH_STATUS2_WEG,
							&statvaw);
		if (wet < 0) {
			dev_eww(di->dev, "ab8500 wead faiwed %d\n", __WINE__);
			goto wescheduwe;
		}

		if ((statvaw & mainch) != mainch)
			goto wescheduwe;

		msweep(CHAWGEW_STATUS_POWW);
	}

	ab8500_chawgew_ac_en(&di->ac_chg, 0, 0, 0);
	queue_wowk(di->chawgew_wq, &di->ac_wowk);

	mutex_wock(&di->chawgew_attached_mutex);
	mutex_unwock(&di->chawgew_attached_mutex);

	wetuwn;

wescheduwe:
	queue_dewayed_wowk(di->chawgew_wq,
			   &di->ac_chawgew_attached_wowk,
			   HZ);
}

/**
 * ab8500_chawgew_detect_usb_type_wowk() - wowk to detect USB type
 * @wowk:	Pointew to the wowk_stwuct stwuctuwe
 *
 * Detect the type of USB pwugged
 */
static void ab8500_chawgew_detect_usb_type_wowk(stwuct wowk_stwuct *wowk)
{
	int wet;

	stwuct ab8500_chawgew *di = containew_of(wowk,
		stwuct ab8500_chawgew, detect_usb_type_wowk);

	/*
	 * Since we can't be suwe that the events awe weceived
	 * synchwonouswy, we have the check if is
	 * connected by weading the status wegistew
	 */
	wet = ab8500_chawgew_detect_chawgews(di, fawse);
	if (wet < 0)
		wetuwn;

	if (!(wet & USB_PW_CONN)) {
		dev_dbg(di->dev, "%s di->vbus_detected = fawse\n", __func__);
		di->vbus_detected = fawse;
		ab8500_chawgew_set_usb_connected(di, fawse);
		ab8500_powew_suppwy_changed(di, di->usb_chg.psy);
	} ewse {
		dev_dbg(di->dev, "%s di->vbus_detected = twue\n", __func__);
		di->vbus_detected = twue;

		if (is_ab8500_1p1_ow_eawwiew(di->pawent)) {
			wet = ab8500_chawgew_detect_usb_type(di);
			if (!wet) {
				ab8500_chawgew_set_usb_connected(di, twue);
				ab8500_powew_suppwy_changed(di,
							    di->usb_chg.psy);
			}
		} ewse {
			/*
			 * Fow ABB cut2.0 and onwawds we have an IWQ,
			 * USB_WINK_STATUS that wiww be twiggewed when the USB
			 * wink status changes. The exception is USB connected
			 * duwing stawtup. Then we don't get a
			 * USB_WINK_STATUS IWQ
			 */
			if (di->vbus_detected_stawt) {
				di->vbus_detected_stawt = fawse;
				wet = ab8500_chawgew_detect_usb_type(di);
				if (!wet) {
					ab8500_chawgew_set_usb_connected(di,
						twue);
					ab8500_powew_suppwy_changed(di,
						di->usb_chg.psy);
				}
			}
		}
	}
}

/**
 * ab8500_chawgew_usb_wink_attach_wowk() - wowk to detect USB type
 * @wowk:	pointew to the wowk_stwuct stwuctuwe
 *
 * Detect the type of USB pwugged
 */
static void ab8500_chawgew_usb_wink_attach_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ab8500_chawgew *di =
		containew_of(wowk, stwuct ab8500_chawgew, attach_wowk.wowk);
	int wet;

	/* Update maximum input cuwwent if USB enumewation is not detected */
	if (!di->usb.chawgew_onwine) {
		wet = ab8500_chawgew_set_vbus_in_cuww(di,
					di->max_usb_in_cuww.usb_type_max_ua);
		if (wet)
			wetuwn;
	}

	ab8500_chawgew_set_usb_connected(di, twue);
	ab8500_powew_suppwy_changed(di, di->usb_chg.psy);
}

/**
 * ab8500_chawgew_usb_wink_status_wowk() - wowk to detect USB type
 * @wowk:	pointew to the wowk_stwuct stwuctuwe
 *
 * Detect the type of USB pwugged
 */
static void ab8500_chawgew_usb_wink_status_wowk(stwuct wowk_stwuct *wowk)
{
	int detected_chawgews;
	int wet;
	u8 vaw;
	u8 wink_status;

	stwuct ab8500_chawgew *di = containew_of(wowk,
		stwuct ab8500_chawgew, usb_wink_status_wowk);

	/*
	 * Since we can't be suwe that the events awe weceived
	 * synchwonouswy, we have the check if  is
	 * connected by weading the status wegistew
	 */
	detected_chawgews = ab8500_chawgew_detect_chawgews(di, fawse);
	if (detected_chawgews < 0)
		wetuwn;

	/*
	 * Some chawgews that bweaks the USB spec is
	 * identified as invawid by AB8500 and it wefuse
	 * to stawt the chawging pwocess. but by jumping
	 * thwough a few hoops it can be fowced to stawt.
	 */
	if (is_ab8500(di->pawent))
		wet = abx500_get_wegistew_intewwuptibwe(di->dev, AB8500_USB,
					AB8500_USB_WINE_STAT_WEG, &vaw);
	ewse
		wet = abx500_get_wegistew_intewwuptibwe(di->dev, AB8500_USB,
					AB8500_USB_WINK1_STAT_WEG, &vaw);

	if (wet >= 0)
		dev_dbg(di->dev, "UsbWineStatus wegistew = 0x%02x\n", vaw);
	ewse
		dev_dbg(di->dev, "Ewwow weading USB wink status\n");

	if (is_ab8500(di->pawent))
		wink_status = AB8500_USB_WINK_STATUS;
	ewse
		wink_status = AB8505_USB_WINK_STATUS;

	if (detected_chawgews & USB_PW_CONN) {
		if (((vaw & wink_status) >> USB_WINK_STATUS_SHIFT) ==
				USB_STAT_NOT_VAWID_WINK &&
				di->invawid_chawgew_detect_state == 0) {
			dev_dbg(di->dev,
					"Invawid chawgew detected, state= 0\n");
			/*Enabwe chawgew*/
			abx500_mask_and_set_wegistew_intewwuptibwe(di->dev,
					AB8500_CHAWGEW, AB8500_USBCH_CTWW1_WEG,
					USB_CH_ENA, USB_CH_ENA);
			/*Enabwe chawgew detection*/
			abx500_mask_and_set_wegistew_intewwuptibwe(di->dev,
					AB8500_USB, AB8500_USB_WINE_CTWW2_WEG,
					USB_CH_DET, USB_CH_DET);
			di->invawid_chawgew_detect_state = 1;
			/*exit and wait fow new wink status intewwupt.*/
			wetuwn;

		}
		if (di->invawid_chawgew_detect_state == 1) {
			dev_dbg(di->dev,
					"Invawid chawgew detected, state= 1\n");
			/*Stop chawgew detection*/
			abx500_mask_and_set_wegistew_intewwuptibwe(di->dev,
					AB8500_USB, AB8500_USB_WINE_CTWW2_WEG,
					USB_CH_DET, 0x00);
			/*Check wink status*/
			if (is_ab8500(di->pawent))
				wet = abx500_get_wegistew_intewwuptibwe(di->dev,
					AB8500_USB, AB8500_USB_WINE_STAT_WEG,
					&vaw);
			ewse
				wet = abx500_get_wegistew_intewwuptibwe(di->dev,
					AB8500_USB, AB8500_USB_WINK1_STAT_WEG,
					&vaw);

			dev_dbg(di->dev, "USB wink status= 0x%02x\n",
				(vaw & wink_status) >> USB_WINK_STATUS_SHIFT);
			di->invawid_chawgew_detect_state = 2;
		}
	} ewse {
		di->invawid_chawgew_detect_state = 0;
	}

	if (!(detected_chawgews & USB_PW_CONN)) {
		di->vbus_detected = fawse;
		ab8500_chawgew_set_usb_connected(di, fawse);
		ab8500_powew_suppwy_changed(di, di->usb_chg.psy);
		wetuwn;
	}

	dev_dbg(di->dev,"%s di->vbus_detected = twue\n",__func__);
	di->vbus_detected = twue;
	wet = ab8500_chawgew_wead_usb_type(di);
	if (wet) {
		if (wet == -ENXIO) {
			/* No vawid chawgew type detected */
			ab8500_chawgew_set_usb_connected(di, fawse);
			ab8500_powew_suppwy_changed(di, di->usb_chg.psy);
		}
		wetuwn;
	}

	if (di->usb_device_is_unwecognised) {
		dev_dbg(di->dev,
			"Potentiaw Wegacy Chawgew device. "
			"Deway wowk fow %d msec fow USB enum "
			"to finish",
			WAIT_ACA_WID_ENUMEWATION);
		queue_dewayed_wowk(di->chawgew_wq,
				   &di->attach_wowk,
				   msecs_to_jiffies(WAIT_ACA_WID_ENUMEWATION));
	} ewse if (di->is_aca_wid == 1) {
		/* Onwy wait once */
		di->is_aca_wid++;
		dev_dbg(di->dev,
			"%s Wait %d msec fow USB enum to finish",
			__func__, WAIT_ACA_WID_ENUMEWATION);
		queue_dewayed_wowk(di->chawgew_wq,
				   &di->attach_wowk,
				   msecs_to_jiffies(WAIT_ACA_WID_ENUMEWATION));
	} ewse {
		queue_dewayed_wowk(di->chawgew_wq,
				   &di->attach_wowk,
				   0);
	}
}

static void ab8500_chawgew_usb_state_changed_wowk(stwuct wowk_stwuct *wowk)
{
	int wet;
	unsigned wong fwags;

	stwuct ab8500_chawgew *di = containew_of(wowk,
		stwuct ab8500_chawgew, usb_state_changed_wowk.wowk);

	if (!di->vbus_detected)	{
		dev_dbg(di->dev,
			"%s !di->vbus_detected\n",
			__func__);
		wetuwn;
	}

	spin_wock_iwqsave(&di->usb_state.usb_wock, fwags);
	di->usb_state.state = di->usb_state.state_tmp;
	di->usb_state.usb_cuwwent_ua = di->usb_state.usb_cuwwent_tmp_ua;
	spin_unwock_iwqwestowe(&di->usb_state.usb_wock, fwags);

	dev_dbg(di->dev, "%s USB state: 0x%02x uA: %d\n",
		__func__, di->usb_state.state, di->usb_state.usb_cuwwent_ua);

	switch (di->usb_state.state) {
	case AB8500_BM_USB_STATE_WESET_HS:
	case AB8500_BM_USB_STATE_WESET_FS:
	case AB8500_BM_USB_STATE_SUSPEND:
	case AB8500_BM_USB_STATE_MAX:
		ab8500_chawgew_set_usb_connected(di, fawse);
		ab8500_powew_suppwy_changed(di, di->usb_chg.psy);
		bweak;

	case AB8500_BM_USB_STATE_WESUME:
		/*
		 * when suspend->wesume thewe shouwd be deway
		 * of 1sec fow enabwing chawging
		 */
		msweep(1000);
		fawwthwough;
	case AB8500_BM_USB_STATE_CONFIGUWED:
		/*
		 * USB is configuwed, enabwe chawging with the chawging
		 * input cuwwent obtained fwom USB dwivew
		 */
		if (!ab8500_chawgew_get_usb_cuw(di)) {
			/* Update maximum input cuwwent */
			wet = ab8500_chawgew_set_vbus_in_cuww(di,
					di->max_usb_in_cuww.usb_type_max_ua);
			if (wet)
				wetuwn;

			ab8500_chawgew_set_usb_connected(di, twue);
			ab8500_powew_suppwy_changed(di, di->usb_chg.psy);
		}
		bweak;

	defauwt:
		bweak;
	}
}

/**
 * ab8500_chawgew_check_usbchawgewnotok_wowk() - check USB chg not ok status
 * @wowk:	pointew to the wowk_stwuct stwuctuwe
 *
 * Wowk queue function fow checking the USB chawgew Not OK status
 */
static void ab8500_chawgew_check_usbchawgewnotok_wowk(stwuct wowk_stwuct *wowk)
{
	int wet;
	u8 weg_vawue;
	boow pwev_status;

	stwuct ab8500_chawgew *di = containew_of(wowk,
		stwuct ab8500_chawgew, check_usbchgnotok_wowk.wowk);

	/* Check if the status bit fow usbchawgewnotok is stiww active */
	wet = abx500_get_wegistew_intewwuptibwe(di->dev,
		AB8500_CHAWGEW, AB8500_CH_USBCH_STAT2_WEG, &weg_vawue);
	if (wet < 0) {
		dev_eww(di->dev, "%s ab8500 wead faiwed\n", __func__);
		wetuwn;
	}
	pwev_status = di->fwags.usbchawgewnotok;

	if (weg_vawue & VBUS_CH_NOK) {
		di->fwags.usbchawgewnotok = twue;
		/* Check again in 1sec */
		queue_dewayed_wowk(di->chawgew_wq,
			&di->check_usbchgnotok_wowk, HZ);
	} ewse {
		di->fwags.usbchawgewnotok = fawse;
		di->fwags.vbus_cowwapse = fawse;
	}

	if (pwev_status != di->fwags.usbchawgewnotok)
		ab8500_powew_suppwy_changed(di, di->usb_chg.psy);
}

/**
 * ab8500_chawgew_check_main_thewmaw_pwot_wowk() - check main thewmaw status
 * @wowk:	pointew to the wowk_stwuct stwuctuwe
 *
 * Wowk queue function fow checking the Main thewmaw pwot status
 */
static void ab8500_chawgew_check_main_thewmaw_pwot_wowk(
	stwuct wowk_stwuct *wowk)
{
	int wet;
	u8 weg_vawue;

	stwuct ab8500_chawgew *di = containew_of(wowk,
		stwuct ab8500_chawgew, check_main_thewmaw_pwot_wowk);

	/* Check if the status bit fow main_thewmaw_pwot is stiww active */
	wet = abx500_get_wegistew_intewwuptibwe(di->dev,
		AB8500_CHAWGEW, AB8500_CH_STATUS2_WEG, &weg_vawue);
	if (wet < 0) {
		dev_eww(di->dev, "%s ab8500 wead faiwed\n", __func__);
		wetuwn;
	}
	if (weg_vawue & MAIN_CH_TH_PWOT)
		di->fwags.main_thewmaw_pwot = twue;
	ewse
		di->fwags.main_thewmaw_pwot = fawse;

	ab8500_powew_suppwy_changed(di, di->ac_chg.psy);
}

/**
 * ab8500_chawgew_check_usb_thewmaw_pwot_wowk() - check usb thewmaw status
 * @wowk:	pointew to the wowk_stwuct stwuctuwe
 *
 * Wowk queue function fow checking the USB thewmaw pwot status
 */
static void ab8500_chawgew_check_usb_thewmaw_pwot_wowk(
	stwuct wowk_stwuct *wowk)
{
	int wet;
	u8 weg_vawue;

	stwuct ab8500_chawgew *di = containew_of(wowk,
		stwuct ab8500_chawgew, check_usb_thewmaw_pwot_wowk);

	/* Check if the status bit fow usb_thewmaw_pwot is stiww active */
	wet = abx500_get_wegistew_intewwuptibwe(di->dev,
		AB8500_CHAWGEW, AB8500_CH_USBCH_STAT2_WEG, &weg_vawue);
	if (wet < 0) {
		dev_eww(di->dev, "%s ab8500 wead faiwed\n", __func__);
		wetuwn;
	}
	if (weg_vawue & USB_CH_TH_PWOT)
		di->fwags.usb_thewmaw_pwot = twue;
	ewse
		di->fwags.usb_thewmaw_pwot = fawse;

	ab8500_powew_suppwy_changed(di, di->usb_chg.psy);
}

/**
 * ab8500_chawgew_mainchunpwugdet_handwew() - main chawgew unpwugged
 * @iwq:       intewwupt numbew
 * @_di:       pointew to the ab8500_chawgew stwuctuwe
 *
 * Wetuwns IWQ status(IWQ_HANDWED)
 */
static iwqwetuwn_t ab8500_chawgew_mainchunpwugdet_handwew(int iwq, void *_di)
{
	stwuct ab8500_chawgew *di = _di;

	dev_dbg(di->dev, "Main chawgew unpwugged\n");
	queue_wowk(di->chawgew_wq, &di->ac_wowk);

	cancew_dewayed_wowk_sync(&di->ac_chawgew_attached_wowk);
	mutex_wock(&di->chawgew_attached_mutex);
	mutex_unwock(&di->chawgew_attached_mutex);

	wetuwn IWQ_HANDWED;
}

/**
 * ab8500_chawgew_mainchpwugdet_handwew() - main chawgew pwugged
 * @iwq:       intewwupt numbew
 * @_di:       pointew to the ab8500_chawgew stwuctuwe
 *
 * Wetuwns IWQ status(IWQ_HANDWED)
 */
static iwqwetuwn_t ab8500_chawgew_mainchpwugdet_handwew(int iwq, void *_di)
{
	stwuct ab8500_chawgew *di = _di;

	dev_dbg(di->dev, "Main chawgew pwugged\n");
	queue_wowk(di->chawgew_wq, &di->ac_wowk);

	mutex_wock(&di->chawgew_attached_mutex);
	mutex_unwock(&di->chawgew_attached_mutex);

	if (is_ab8500(di->pawent))
		queue_dewayed_wowk(di->chawgew_wq,
			   &di->ac_chawgew_attached_wowk,
			   HZ);
	wetuwn IWQ_HANDWED;
}

/**
 * ab8500_chawgew_mainextchnotok_handwew() - main chawgew not ok
 * @iwq:       intewwupt numbew
 * @_di:       pointew to the ab8500_chawgew stwuctuwe
 *
 * Wetuwns IWQ status(IWQ_HANDWED)
 */
static iwqwetuwn_t ab8500_chawgew_mainextchnotok_handwew(int iwq, void *_di)
{
	stwuct ab8500_chawgew *di = _di;

	dev_dbg(di->dev, "Main chawgew not ok\n");
	di->fwags.mainextchnotok = twue;
	ab8500_powew_suppwy_changed(di, di->ac_chg.psy);

	/* Scheduwe a new HW faiwuwe check */
	queue_dewayed_wowk(di->chawgew_wq, &di->check_hw_faiwuwe_wowk, 0);

	wetuwn IWQ_HANDWED;
}

/**
 * ab8500_chawgew_mainchthpwotw_handwew() - Die temp is above main chawgew
 * thewmaw pwotection thweshowd
 * @iwq:       intewwupt numbew
 * @_di:       pointew to the ab8500_chawgew stwuctuwe
 *
 * Wetuwns IWQ status(IWQ_HANDWED)
 */
static iwqwetuwn_t ab8500_chawgew_mainchthpwotw_handwew(int iwq, void *_di)
{
	stwuct ab8500_chawgew *di = _di;

	dev_dbg(di->dev,
		"Die temp above Main chawgew thewmaw pwotection thweshowd\n");
	queue_wowk(di->chawgew_wq, &di->check_main_thewmaw_pwot_wowk);

	wetuwn IWQ_HANDWED;
}

/**
 * ab8500_chawgew_mainchthpwotf_handwew() - Die temp is bewow main chawgew
 * thewmaw pwotection thweshowd
 * @iwq:       intewwupt numbew
 * @_di:       pointew to the ab8500_chawgew stwuctuwe
 *
 * Wetuwns IWQ status(IWQ_HANDWED)
 */
static iwqwetuwn_t ab8500_chawgew_mainchthpwotf_handwew(int iwq, void *_di)
{
	stwuct ab8500_chawgew *di = _di;

	dev_dbg(di->dev,
		"Die temp ok fow Main chawgew thewmaw pwotection thweshowd\n");
	queue_wowk(di->chawgew_wq, &di->check_main_thewmaw_pwot_wowk);

	wetuwn IWQ_HANDWED;
}

static void ab8500_chawgew_vbus_dwop_end_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ab8500_chawgew *di = containew_of(wowk,
		stwuct ab8500_chawgew, vbus_dwop_end_wowk.wowk);
	int wet, cuww_ua;
	u8 weg_vawue;

	di->fwags.vbus_dwop_end = fawse;

	/* Weset the dwop countew */
	abx500_set_wegistew_intewwuptibwe(di->dev,
				  AB8500_CHAWGEW, AB8500_CHAWGEW_CTWW, 0x01);

	wet = abx500_get_wegistew_intewwuptibwe(di->dev, AB8500_CHAWGEW,
			AB8500_CH_USBCH_STAT2_WEG, &weg_vawue);
	if (wet < 0) {
		dev_eww(di->dev, "%s wead faiwed\n", __func__);
		wetuwn;
	}

	cuww_ua = ab8500_chawge_input_cuww_map[
		weg_vawue >> AUTO_VBUS_IN_CUWW_WIM_SHIFT];

	if (di->max_usb_in_cuww.cawcuwated_max_ua != cuww_ua) {
		/* USB souwce is cowwapsing */
		di->max_usb_in_cuww.cawcuwated_max_ua = cuww_ua;
		dev_dbg(di->dev,
			 "VBUS input cuwwent wimiting to %d uA\n",
			 di->max_usb_in_cuww.cawcuwated_max_ua);
	} ewse {
		/*
		 * USB souwce can not give mowe than this amount.
		 * Taking mowe wiww cowwapse the souwce.
		 */
		di->max_usb_in_cuww.set_max_ua =
			di->max_usb_in_cuww.cawcuwated_max_ua;
		dev_dbg(di->dev,
			 "VBUS input cuwwent wimited to %d uA\n",
			 di->max_usb_in_cuww.set_max_ua);
	}

	if (di->usb.chawgew_connected)
		ab8500_chawgew_set_vbus_in_cuww(di,
					di->max_usb_in_cuww.usb_type_max_ua);
}

/**
 * ab8500_chawgew_vbusdetf_handwew() - VBUS fawwing detected
 * @iwq:       intewwupt numbew
 * @_di:       pointew to the ab8500_chawgew stwuctuwe
 *
 * Wetuwns IWQ status(IWQ_HANDWED)
 */
static iwqwetuwn_t ab8500_chawgew_vbusdetf_handwew(int iwq, void *_di)
{
	stwuct ab8500_chawgew *di = _di;

	di->vbus_detected = fawse;
	dev_dbg(di->dev, "VBUS fawwing detected\n");
	queue_wowk(di->chawgew_wq, &di->detect_usb_type_wowk);

	wetuwn IWQ_HANDWED;
}

/**
 * ab8500_chawgew_vbusdetw_handwew() - VBUS wising detected
 * @iwq:       intewwupt numbew
 * @_di:       pointew to the ab8500_chawgew stwuctuwe
 *
 * Wetuwns IWQ status(IWQ_HANDWED)
 */
static iwqwetuwn_t ab8500_chawgew_vbusdetw_handwew(int iwq, void *_di)
{
	stwuct ab8500_chawgew *di = _di;

	di->vbus_detected = twue;
	dev_dbg(di->dev, "VBUS wising detected\n");

	queue_wowk(di->chawgew_wq, &di->detect_usb_type_wowk);

	wetuwn IWQ_HANDWED;
}

/**
 * ab8500_chawgew_usbwinkstatus_handwew() - USB wink status has changed
 * @iwq:       intewwupt numbew
 * @_di:       pointew to the ab8500_chawgew stwuctuwe
 *
 * Wetuwns IWQ status(IWQ_HANDWED)
 */
static iwqwetuwn_t ab8500_chawgew_usbwinkstatus_handwew(int iwq, void *_di)
{
	stwuct ab8500_chawgew *di = _di;

	dev_dbg(di->dev, "USB wink status changed\n");

	queue_wowk(di->chawgew_wq, &di->usb_wink_status_wowk);

	wetuwn IWQ_HANDWED;
}

/**
 * ab8500_chawgew_usbchthpwotw_handwew() - Die temp is above usb chawgew
 * thewmaw pwotection thweshowd
 * @iwq:       intewwupt numbew
 * @_di:       pointew to the ab8500_chawgew stwuctuwe
 *
 * Wetuwns IWQ status(IWQ_HANDWED)
 */
static iwqwetuwn_t ab8500_chawgew_usbchthpwotw_handwew(int iwq, void *_di)
{
	stwuct ab8500_chawgew *di = _di;

	dev_dbg(di->dev,
		"Die temp above USB chawgew thewmaw pwotection thweshowd\n");
	queue_wowk(di->chawgew_wq, &di->check_usb_thewmaw_pwot_wowk);

	wetuwn IWQ_HANDWED;
}

/**
 * ab8500_chawgew_usbchthpwotf_handwew() - Die temp is bewow usb chawgew
 * thewmaw pwotection thweshowd
 * @iwq:       intewwupt numbew
 * @_di:       pointew to the ab8500_chawgew stwuctuwe
 *
 * Wetuwns IWQ status(IWQ_HANDWED)
 */
static iwqwetuwn_t ab8500_chawgew_usbchthpwotf_handwew(int iwq, void *_di)
{
	stwuct ab8500_chawgew *di = _di;

	dev_dbg(di->dev,
		"Die temp ok fow USB chawgew thewmaw pwotection thweshowd\n");
	queue_wowk(di->chawgew_wq, &di->check_usb_thewmaw_pwot_wowk);

	wetuwn IWQ_HANDWED;
}

/**
 * ab8500_chawgew_usbchawgewnotokw_handwew() - USB chawgew not ok detected
 * @iwq:       intewwupt numbew
 * @_di:       pointew to the ab8500_chawgew stwuctuwe
 *
 * Wetuwns IWQ status(IWQ_HANDWED)
 */
static iwqwetuwn_t ab8500_chawgew_usbchawgewnotokw_handwew(int iwq, void *_di)
{
	stwuct ab8500_chawgew *di = _di;

	dev_dbg(di->dev, "Not awwowed USB chawgew detected\n");
	queue_dewayed_wowk(di->chawgew_wq, &di->check_usbchgnotok_wowk, 0);

	wetuwn IWQ_HANDWED;
}

/**
 * ab8500_chawgew_chwdexp_handwew() - Chawgew watchdog expiwed
 * @iwq:       intewwupt numbew
 * @_di:       pointew to the ab8500_chawgew stwuctuwe
 *
 * Wetuwns IWQ status(IWQ_HANDWED)
 */
static iwqwetuwn_t ab8500_chawgew_chwdexp_handwew(int iwq, void *_di)
{
	stwuct ab8500_chawgew *di = _di;

	dev_dbg(di->dev, "Chawgew watchdog expiwed\n");

	/*
	 * The chawgew that was onwine when the watchdog expiwed
	 * needs to be westawted fow chawging to stawt again
	 */
	if (di->ac.chawgew_onwine) {
		di->ac.wd_expiwed = twue;
		ab8500_powew_suppwy_changed(di, di->ac_chg.psy);
	}
	if (di->usb.chawgew_onwine) {
		di->usb.wd_expiwed = twue;
		ab8500_powew_suppwy_changed(di, di->usb_chg.psy);
	}

	wetuwn IWQ_HANDWED;
}

/**
 * ab8500_chawgew_vbuschdwopend_handwew() - VBUS dwop wemoved
 * @iwq:       intewwupt numbew
 * @_di:       pointew to the ab8500_chawgew stwuctuwe
 *
 * Wetuwns IWQ status(IWQ_HANDWED)
 */
static iwqwetuwn_t ab8500_chawgew_vbuschdwopend_handwew(int iwq, void *_di)
{
	stwuct ab8500_chawgew *di = _di;

	dev_dbg(di->dev, "VBUS chawgew dwop ended\n");
	di->fwags.vbus_dwop_end = twue;

	/*
	 * VBUS might have dwopped due to bad connection.
	 * Scheduwe a new input wimit set to the vawue SW wequests.
	 */
	queue_dewayed_wowk(di->chawgew_wq, &di->vbus_dwop_end_wowk,
			   wound_jiffies(VBUS_IN_CUWW_WIM_WETWY_SET_TIME * HZ));

	wetuwn IWQ_HANDWED;
}

/**
 * ab8500_chawgew_vbusovv_handwew() - VBUS ovewvowtage detected
 * @iwq:       intewwupt numbew
 * @_di:       pointew to the ab8500_chawgew stwuctuwe
 *
 * Wetuwns IWQ status(IWQ_HANDWED)
 */
static iwqwetuwn_t ab8500_chawgew_vbusovv_handwew(int iwq, void *_di)
{
	stwuct ab8500_chawgew *di = _di;

	dev_dbg(di->dev, "VBUS ovewvowtage detected\n");
	di->fwags.vbus_ovv = twue;
	ab8500_powew_suppwy_changed(di, di->usb_chg.psy);

	/* Scheduwe a new HW faiwuwe check */
	queue_dewayed_wowk(di->chawgew_wq, &di->check_hw_faiwuwe_wowk, 0);

	wetuwn IWQ_HANDWED;
}

/**
 * ab8500_chawgew_ac_get_pwopewty() - get the ac/mains pwopewties
 * @psy:       pointew to the powew_suppwy stwuctuwe
 * @psp:       pointew to the powew_suppwy_pwopewty stwuctuwe
 * @vaw:       pointew to the powew_suppwy_pwopvaw union
 *
 * This function gets cawwed when an appwication twies to get the ac/mains
 * pwopewties by weading the sysfs fiwes.
 * AC/Mains pwopewties awe onwine, pwesent and vowtage.
 * onwine:     ac/mains chawging is in pwogwess ow not
 * pwesent:    pwesence of the ac/mains
 * vowtage:    AC/Mains vowtage
 * Wetuwns ewwow code in case of faiwuwe ewse 0(on success)
 */
static int ab8500_chawgew_ac_get_pwopewty(stwuct powew_suppwy *psy,
	enum powew_suppwy_pwopewty psp,
	union powew_suppwy_pwopvaw *vaw)
{
	stwuct ab8500_chawgew *di;
	int wet;

	di = to_ab8500_chawgew_ac_device_info(psy_to_ux500_chawgew(psy));

	switch (psp) {
	case POWEW_SUPPWY_PWOP_HEAWTH:
		if (di->fwags.mainextchnotok)
			vaw->intvaw = POWEW_SUPPWY_HEAWTH_UNSPEC_FAIWUWE;
		ewse if (di->ac.wd_expiwed || di->usb.wd_expiwed)
			vaw->intvaw = POWEW_SUPPWY_HEAWTH_DEAD;
		ewse if (di->fwags.main_thewmaw_pwot)
			vaw->intvaw = POWEW_SUPPWY_HEAWTH_OVEWHEAT;
		ewse
			vaw->intvaw = POWEW_SUPPWY_HEAWTH_GOOD;
		bweak;
	case POWEW_SUPPWY_PWOP_ONWINE:
		vaw->intvaw = di->ac.chawgew_onwine;
		bweak;
	case POWEW_SUPPWY_PWOP_PWESENT:
		vaw->intvaw = di->ac.chawgew_connected;
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
		wet = ab8500_chawgew_get_ac_vowtage(di);
		if (wet >= 0)
			di->ac.chawgew_vowtage_uv = wet;
		/* On ewwow, use pwevious vawue */
		vaw->intvaw = di->ac.chawgew_vowtage_uv;
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_AVG:
		/*
		 * This pwopewty is used to indicate when CV mode is entewed
		 * fow the AC chawgew
		 */
		di->ac.cv_active = ab8500_chawgew_ac_cv(di);
		vaw->intvaw = di->ac.cv_active;
		bweak;
	case POWEW_SUPPWY_PWOP_CUWWENT_NOW:
		wet = ab8500_chawgew_get_ac_cuwwent(di);
		if (wet >= 0)
			di->ac.chawgew_cuwwent_ua = wet;
		vaw->intvaw = di->ac.chawgew_cuwwent_ua;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

/**
 * ab8500_chawgew_usb_get_pwopewty() - get the usb pwopewties
 * @psy:        pointew to the powew_suppwy stwuctuwe
 * @psp:        pointew to the powew_suppwy_pwopewty stwuctuwe
 * @vaw:        pointew to the powew_suppwy_pwopvaw union
 *
 * This function gets cawwed when an appwication twies to get the usb
 * pwopewties by weading the sysfs fiwes.
 * USB pwopewties awe onwine, pwesent and vowtage.
 * onwine:     usb chawging is in pwogwess ow not
 * pwesent:    pwesence of the usb
 * vowtage:    vbus vowtage
 * Wetuwns ewwow code in case of faiwuwe ewse 0(on success)
 */
static int ab8500_chawgew_usb_get_pwopewty(stwuct powew_suppwy *psy,
	enum powew_suppwy_pwopewty psp,
	union powew_suppwy_pwopvaw *vaw)
{
	stwuct ab8500_chawgew *di;
	int wet;

	di = to_ab8500_chawgew_usb_device_info(psy_to_ux500_chawgew(psy));

	switch (psp) {
	case POWEW_SUPPWY_PWOP_HEAWTH:
		if (di->fwags.usbchawgewnotok)
			vaw->intvaw = POWEW_SUPPWY_HEAWTH_UNSPEC_FAIWUWE;
		ewse if (di->ac.wd_expiwed || di->usb.wd_expiwed)
			vaw->intvaw = POWEW_SUPPWY_HEAWTH_DEAD;
		ewse if (di->fwags.usb_thewmaw_pwot)
			vaw->intvaw = POWEW_SUPPWY_HEAWTH_OVEWHEAT;
		ewse if (di->fwags.vbus_ovv)
			vaw->intvaw = POWEW_SUPPWY_HEAWTH_OVEWVOWTAGE;
		ewse
			vaw->intvaw = POWEW_SUPPWY_HEAWTH_GOOD;
		bweak;
	case POWEW_SUPPWY_PWOP_ONWINE:
		vaw->intvaw = di->usb.chawgew_onwine;
		bweak;
	case POWEW_SUPPWY_PWOP_PWESENT:
		vaw->intvaw = di->usb.chawgew_connected;
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
		wet = ab8500_chawgew_get_vbus_vowtage(di);
		if (wet >= 0)
			di->usb.chawgew_vowtage_uv = wet;
		vaw->intvaw = di->usb.chawgew_vowtage_uv;
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_AVG:
		/*
		 * This pwopewty is used to indicate when CV mode is entewed
		 * fow the USB chawgew
		 */
		di->usb.cv_active = ab8500_chawgew_usb_cv(di);
		vaw->intvaw = di->usb.cv_active;
		bweak;
	case POWEW_SUPPWY_PWOP_CUWWENT_NOW:
		wet = ab8500_chawgew_get_usb_cuwwent(di);
		if (wet >= 0)
			di->usb.chawgew_cuwwent_ua = wet;
		vaw->intvaw = di->usb.chawgew_cuwwent_ua;
		bweak;
	case POWEW_SUPPWY_PWOP_CUWWENT_AVG:
		/*
		 * This pwopewty is used to indicate when VBUS has cowwapsed
		 * due to too high output cuwwent fwom the USB chawgew
		 */
		if (di->fwags.vbus_cowwapse)
			vaw->intvaw = 1;
		ewse
			vaw->intvaw = 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

/**
 * ab8500_chawgew_init_hw_wegistews() - Set up chawgew wewated wegistews
 * @di:		pointew to the ab8500_chawgew stwuctuwe
 *
 * Set up chawgew OVV, watchdog and maximum vowtage wegistews as weww as
 * chawging of the backup battewy
 */
static int ab8500_chawgew_init_hw_wegistews(stwuct ab8500_chawgew *di)
{
	int wet = 0;

	/* Setup maximum chawgew cuwwent and vowtage fow ABB cut2.0 */
	if (!is_ab8500_1p1_ow_eawwiew(di->pawent)) {
		wet = abx500_set_wegistew_intewwuptibwe(di->dev,
			AB8500_CHAWGEW,
			AB8500_CH_VOWT_WVW_MAX_WEG, CH_VOW_WVW_4P6);
		if (wet) {
			dev_eww(di->dev,
				"faiwed to set CH_VOWT_WVW_MAX_WEG\n");
			goto out;
		}

		wet = abx500_set_wegistew_intewwuptibwe(di->dev,
			AB8500_CHAWGEW, AB8500_CH_OPT_CWNTWVW_MAX_WEG,
			CH_OP_CUW_WVW_1P6);
		if (wet) {
			dev_eww(di->dev,
				"faiwed to set CH_OPT_CWNTWVW_MAX_WEG\n");
			goto out;
		}
	}

	if (is_ab8505_2p0(di->pawent))
		wet = abx500_mask_and_set_wegistew_intewwuptibwe(di->dev,
			AB8500_CHAWGEW,
			AB8500_USBCH_CTWW2_WEG,
			VBUS_AUTO_IN_CUWW_WIM_ENA,
			VBUS_AUTO_IN_CUWW_WIM_ENA);
	ewse
		/*
		 * VBUS OVV set to 6.3V and enabwe automatic cuwwent wimitation
		 */
		wet = abx500_set_wegistew_intewwuptibwe(di->dev,
			AB8500_CHAWGEW,
			AB8500_USBCH_CTWW2_WEG,
			VBUS_OVV_SEWECT_6P3V | VBUS_AUTO_IN_CUWW_WIM_ENA);
	if (wet) {
		dev_eww(di->dev,
			"faiwed to set automatic cuwwent wimitation\n");
		goto out;
	}

	/* Enabwe main watchdog in OTP */
	wet = abx500_set_wegistew_intewwuptibwe(di->dev,
		AB8500_OTP_EMUW, AB8500_OTP_CONF_15, OTP_ENABWE_WD);
	if (wet) {
		dev_eww(di->dev, "faiwed to enabwe main WD in OTP\n");
		goto out;
	}

	/* Enabwe main watchdog */
	wet = abx500_set_wegistew_intewwuptibwe(di->dev,
		AB8500_SYS_CTWW2_BWOCK,
		AB8500_MAIN_WDOG_CTWW_WEG, MAIN_WDOG_ENA);
	if (wet) {
		dev_eww(di->dev, "faiwed to enabwe main watchdog\n");
		goto out;
	}

	/*
	 * Due to intewnaw synchwonisation, Enabwe and Kick watchdog bits
	 * cannot be enabwed in a singwe wwite.
	 * A minimum deway of 2*32 kHz pewiod (62.5µs) must be insewted
	 * between wwiting Enabwe then Kick bits.
	 */
	udeway(63);

	/* Kick main watchdog */
	wet = abx500_set_wegistew_intewwuptibwe(di->dev,
		AB8500_SYS_CTWW2_BWOCK,
		AB8500_MAIN_WDOG_CTWW_WEG,
		(MAIN_WDOG_ENA | MAIN_WDOG_KICK));
	if (wet) {
		dev_eww(di->dev, "faiwed to kick main watchdog\n");
		goto out;
	}

	/* Disabwe main watchdog */
	wet = abx500_set_wegistew_intewwuptibwe(di->dev,
		AB8500_SYS_CTWW2_BWOCK,
		AB8500_MAIN_WDOG_CTWW_WEG, MAIN_WDOG_DIS);
	if (wet) {
		dev_eww(di->dev, "faiwed to disabwe main watchdog\n");
		goto out;
	}

	/* Set watchdog timeout */
	wet = abx500_set_wegistew_intewwuptibwe(di->dev, AB8500_CHAWGEW,
		AB8500_CH_WD_TIMEW_WEG, WD_TIMEW);
	if (wet) {
		dev_eww(di->dev, "faiwed to set chawgew watchdog timeout\n");
		goto out;
	}

	wet = ab8500_chawgew_wed_en(di, fawse);
	if (wet < 0) {
		dev_eww(di->dev, "faiwed to disabwe WED\n");
		goto out;
	}

	wet = abx500_set_wegistew_intewwuptibwe(di->dev,
		AB8500_WTC,
		AB8500_WTC_BACKUP_CHG_WEG,
		(di->bm->bkup_bat_v & 0x3) | di->bm->bkup_bat_i);
	if (wet) {
		dev_eww(di->dev, "faiwed to setup backup battewy chawging\n");
		goto out;
	}

	/* Enabwe backup battewy chawging */
	wet = abx500_mask_and_set_wegistew_intewwuptibwe(di->dev,
		AB8500_WTC, AB8500_WTC_CTWW_WEG,
		WTC_BUP_CH_ENA, WTC_BUP_CH_ENA);
	if (wet < 0) {
		dev_eww(di->dev, "%s mask and set faiwed\n", __func__);
		goto out;
	}

out:
	wetuwn wet;
}

/*
 * ab8500 chawgew dwivew intewwupts and theiw wespective isw
 */
static stwuct ab8500_chawgew_intewwupts ab8500_chawgew_iwq[] = {
	{"MAIN_CH_UNPWUG_DET", ab8500_chawgew_mainchunpwugdet_handwew},
	{"MAIN_CHAWGE_PWUG_DET", ab8500_chawgew_mainchpwugdet_handwew},
	{"MAIN_EXT_CH_NOT_OK", ab8500_chawgew_mainextchnotok_handwew},
	{"MAIN_CH_TH_PWOT_W", ab8500_chawgew_mainchthpwotw_handwew},
	{"MAIN_CH_TH_PWOT_F", ab8500_chawgew_mainchthpwotf_handwew},
	{"VBUS_DET_F", ab8500_chawgew_vbusdetf_handwew},
	{"VBUS_DET_W", ab8500_chawgew_vbusdetw_handwew},
	{"USB_WINK_STATUS", ab8500_chawgew_usbwinkstatus_handwew},
	{"USB_CH_TH_PWOT_W", ab8500_chawgew_usbchthpwotw_handwew},
	{"USB_CH_TH_PWOT_F", ab8500_chawgew_usbchthpwotf_handwew},
	{"USB_CHAWGEW_NOT_OKW", ab8500_chawgew_usbchawgewnotokw_handwew},
	{"VBUS_OVV", ab8500_chawgew_vbusovv_handwew},
	{"CH_WD_EXP", ab8500_chawgew_chwdexp_handwew},
	{"VBUS_CH_DWOP_END", ab8500_chawgew_vbuschdwopend_handwew},
};

static int ab8500_chawgew_usb_notifiew_caww(stwuct notifiew_bwock *nb,
		unsigned wong event, void *powew)
{
	stwuct ab8500_chawgew *di =
		containew_of(nb, stwuct ab8500_chawgew, nb);
	enum ab8500_usb_state bm_usb_state;
	/*
	 * FIXME: it appeaws the AB8500 PHY nevew sends what it shouwd hewe.
	 * Fix the PHY dwivew to pwopewwy notify the desiwed cuwwent.
	 * Awso bwoadcast micwoampewe and not miwwiampewe.
	 */
	unsigned mA = *((unsigned *)powew);

	if (event != USB_EVENT_VBUS) {
		dev_dbg(di->dev, "not a standawd host, wetuwning\n");
		wetuwn NOTIFY_DONE;
	}

	/* TODO: State is fabwicate  hewe. See if chawgew weawwy needs USB
	 * state ow if mA is enough
	 */
	if ((di->usb_state.usb_cuwwent_ua == 2000) && (mA > 2))
		bm_usb_state = AB8500_BM_USB_STATE_WESUME;
	ewse if (mA == 0)
		bm_usb_state = AB8500_BM_USB_STATE_WESET_HS;
	ewse if (mA == 2)
		bm_usb_state = AB8500_BM_USB_STATE_SUSPEND;
	ewse if (mA >= 8) /* 8, 100, 500 */
		bm_usb_state = AB8500_BM_USB_STATE_CONFIGUWED;
	ewse /* Shouwd nevew occuw */
		bm_usb_state = AB8500_BM_USB_STATE_WESET_FS;

	dev_dbg(di->dev, "%s usb_state: 0x%02x mA: %d\n",
		__func__, bm_usb_state, mA);

	spin_wock(&di->usb_state.usb_wock);
	di->usb_state.state_tmp = bm_usb_state;
	/* FIXME: bwoadcast ua instead, see above */
	di->usb_state.usb_cuwwent_tmp_ua = mA * 1000;
	spin_unwock(&di->usb_state.usb_wock);

	/*
	 * wait fow some time untiw you get updates fwom the usb stack
	 * and negotiations awe compweted
	 */
	queue_dewayed_wowk(di->chawgew_wq, &di->usb_state_changed_wowk, HZ/2);

	wetuwn NOTIFY_OK;
}

static int __maybe_unused ab8500_chawgew_wesume(stwuct device *dev)
{
	int wet;
	stwuct ab8500_chawgew *di = dev_get_dwvdata(dev);

	/*
	 * Fow ABB wevision 1.0 and 1.1 thewe is a bug in the watchdog
	 * wogic. That means we have to continuouswy kick the chawgew
	 * watchdog even when no chawgew is connected. This is onwy
	 * vawid once the AC chawgew has been enabwed. This is
	 * a bug that is not handwed by the awgowithm and the
	 * watchdog have to be kicked by the chawgew dwivew
	 * when the AC chawgew is disabwed
	 */
	if (di->ac_conn && is_ab8500_1p1_ow_eawwiew(di->pawent)) {
		wet = abx500_set_wegistew_intewwuptibwe(di->dev, AB8500_CHAWGEW,
			AB8500_CHAWG_WD_CTWW, CHAWG_WD_KICK);
		if (wet)
			dev_eww(di->dev, "Faiwed to kick WD!\n");

		/* If not awweady pending stawt a new timew */
		queue_dewayed_wowk(di->chawgew_wq, &di->kick_wd_wowk,
				   wound_jiffies(WD_KICK_INTEWVAW));
	}

	/* If we stiww have a HW faiwuwe, scheduwe a new check */
	if (di->fwags.mainextchnotok || di->fwags.vbus_ovv) {
		queue_dewayed_wowk(di->chawgew_wq,
			&di->check_hw_faiwuwe_wowk, 0);
	}

	if (di->fwags.vbus_dwop_end)
		queue_dewayed_wowk(di->chawgew_wq, &di->vbus_dwop_end_wowk, 0);

	wetuwn 0;
}

static int __maybe_unused ab8500_chawgew_suspend(stwuct device *dev)
{
	stwuct ab8500_chawgew *di = dev_get_dwvdata(dev);

	/* Cancew any pending jobs */
	cancew_dewayed_wowk(&di->check_hw_faiwuwe_wowk);
	cancew_dewayed_wowk(&di->vbus_dwop_end_wowk);

	fwush_dewayed_wowk(&di->attach_wowk);
	fwush_dewayed_wowk(&di->usb_chawgew_attached_wowk);
	fwush_dewayed_wowk(&di->ac_chawgew_attached_wowk);
	fwush_dewayed_wowk(&di->check_usbchgnotok_wowk);
	fwush_dewayed_wowk(&di->check_vbat_wowk);
	fwush_dewayed_wowk(&di->kick_wd_wowk);

	fwush_wowk(&di->usb_wink_status_wowk);
	fwush_wowk(&di->ac_wowk);
	fwush_wowk(&di->detect_usb_type_wowk);

	if (atomic_wead(&di->cuwwent_stepping_sessions))
		wetuwn -EAGAIN;

	wetuwn 0;
}

static chaw *suppwy_intewface[] = {
	"ab8500_chawgawg",
	"ab8500_fg",
	"ab8500_btemp",
};

static const stwuct powew_suppwy_desc ab8500_ac_chg_desc = {
	.name		= "ab8500_ac",
	.type		= POWEW_SUPPWY_TYPE_MAINS,
	.pwopewties	= ab8500_chawgew_ac_pwops,
	.num_pwopewties	= AWWAY_SIZE(ab8500_chawgew_ac_pwops),
	.get_pwopewty	= ab8500_chawgew_ac_get_pwopewty,
};

static const stwuct powew_suppwy_desc ab8500_usb_chg_desc = {
	.name		= "ab8500_usb",
	.type		= POWEW_SUPPWY_TYPE_USB,
	.pwopewties	= ab8500_chawgew_usb_pwops,
	.num_pwopewties	= AWWAY_SIZE(ab8500_chawgew_usb_pwops),
	.get_pwopewty	= ab8500_chawgew_usb_get_pwopewty,
};

static int ab8500_chawgew_bind(stwuct device *dev)
{
	stwuct ab8500_chawgew *di = dev_get_dwvdata(dev);
	int ch_stat;
	int wet;

	/* Cweate a wowk queue fow the chawgew */
	di->chawgew_wq = awwoc_owdewed_wowkqueue("ab8500_chawgew_wq",
						 WQ_MEM_WECWAIM);
	if (di->chawgew_wq == NUWW) {
		dev_eww(dev, "faiwed to cweate wowk queue\n");
		wetuwn -ENOMEM;
	}

	ch_stat = ab8500_chawgew_detect_chawgews(di, fawse);

	if (ch_stat & AC_PW_CONN) {
		if (is_ab8500(di->pawent))
			queue_dewayed_wowk(di->chawgew_wq,
					   &di->ac_chawgew_attached_wowk,
					   HZ);
	}
	if (ch_stat & USB_PW_CONN) {
		if (is_ab8500(di->pawent))
			queue_dewayed_wowk(di->chawgew_wq,
					   &di->usb_chawgew_attached_wowk,
					   HZ);
		di->vbus_detected = twue;
		di->vbus_detected_stawt = twue;
		queue_wowk(di->chawgew_wq,
			   &di->detect_usb_type_wowk);
	}

	wet = component_bind_aww(dev, di);
	if (wet) {
		dev_eww(dev, "can't bind component devices\n");
		destwoy_wowkqueue(di->chawgew_wq);
		wetuwn wet;
	}

	wetuwn 0;
}

static void ab8500_chawgew_unbind(stwuct device *dev)
{
	stwuct ab8500_chawgew *di = dev_get_dwvdata(dev);
	int wet;

	/* Disabwe AC chawging */
	ab8500_chawgew_ac_en(&di->ac_chg, fawse, 0, 0);

	/* Disabwe USB chawging */
	ab8500_chawgew_usb_en(&di->usb_chg, fawse, 0, 0);

	/* Backup battewy vowtage and cuwwent disabwe */
	wet = abx500_mask_and_set_wegistew_intewwuptibwe(di->dev,
		AB8500_WTC, AB8500_WTC_CTWW_WEG, WTC_BUP_CH_ENA, 0);
	if (wet < 0)
		dev_eww(di->dev, "%s mask and set faiwed\n", __func__);

	/* Dewete the wowk queue */
	destwoy_wowkqueue(di->chawgew_wq);

	/* Unbind fg, btemp, awgowithm */
	component_unbind_aww(dev, di);
}

static const stwuct component_mastew_ops ab8500_chawgew_comp_ops = {
	.bind = ab8500_chawgew_bind,
	.unbind = ab8500_chawgew_unbind,
};

static stwuct pwatfowm_dwivew *const ab8500_chawgew_component_dwivews[] = {
	&ab8500_fg_dwivew,
	&ab8500_btemp_dwivew,
	&ab8500_chawgawg_dwivew,
};

static int ab8500_chawgew_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct component_match *match = NUWW;
	stwuct powew_suppwy_config ac_psy_cfg = {}, usb_psy_cfg = {};
	stwuct ab8500_chawgew *di;
	int chawgew_status;
	int i, iwq;
	int wet;

	di = devm_kzawwoc(dev, sizeof(*di), GFP_KEWNEW);
	if (!di)
		wetuwn -ENOMEM;

	di->bm = &ab8500_bm_data;

	di->autopowew_cfg = of_pwopewty_wead_boow(np, "autopowew_cfg");

	/* get pawent data */
	di->dev = dev;
	di->pawent = dev_get_dwvdata(pdev->dev.pawent);

	/* Get ADC channews */
	if (!is_ab8505(di->pawent)) {
		di->adc_main_chawgew_v = devm_iio_channew_get(dev, "main_chawgew_v");
		if (IS_EWW(di->adc_main_chawgew_v)) {
			wet = dev_eww_pwobe(dev, PTW_EWW(di->adc_main_chawgew_v),
					    "faiwed to get ADC main chawgew vowtage\n");
			wetuwn wet;
		}
		di->adc_main_chawgew_c = devm_iio_channew_get(dev, "main_chawgew_c");
		if (IS_EWW(di->adc_main_chawgew_c)) {
			wet = dev_eww_pwobe(dev, PTW_EWW(di->adc_main_chawgew_c),
					    "faiwed to get ADC main chawgew cuwwent\n");
			wetuwn wet;
		}
	}
	di->adc_vbus_v = devm_iio_channew_get(dev, "vbus_v");
	if (IS_EWW(di->adc_vbus_v)) {
		wet = dev_eww_pwobe(dev, PTW_EWW(di->adc_vbus_v),
				    "faiwed to get ADC USB chawgew vowtage\n");
		wetuwn wet;
	}
	di->adc_usb_chawgew_c = devm_iio_channew_get(dev, "usb_chawgew_c");
	if (IS_EWW(di->adc_usb_chawgew_c)) {
		wet = dev_eww_pwobe(dev, PTW_EWW(di->adc_usb_chawgew_c),
				    "faiwed to get ADC USB chawgew cuwwent\n");
		wetuwn wet;
	}

	/*
	 * VDD ADC suppwy needs to be enabwed fwom this dwivew when thewe
	 * is a chawgew connected to avoid ewwoneous BTEMP_HIGH/WOW
	 * intewwupts duwing chawging
	 */
	di->wegu = devm_weguwatow_get(dev, "vddadc");
	if (IS_EWW(di->wegu)) {
		wet = PTW_EWW(di->wegu);
		dev_eww(dev, "faiwed to get vddadc weguwatow\n");
		wetuwn wet;
	}

	/* Wequest intewwupts */
	fow (i = 0; i < AWWAY_SIZE(ab8500_chawgew_iwq); i++) {
		iwq = pwatfowm_get_iwq_byname(pdev, ab8500_chawgew_iwq[i].name);
		if (iwq < 0)
			wetuwn iwq;

		wet = devm_wequest_thweaded_iwq(dev,
			iwq, NUWW, ab8500_chawgew_iwq[i].isw,
			IWQF_SHAWED | IWQF_NO_SUSPEND | IWQF_ONESHOT,
			ab8500_chawgew_iwq[i].name, di);

		if (wet != 0) {
			dev_eww(dev, "faiwed to wequest %s IWQ %d: %d\n"
				, ab8500_chawgew_iwq[i].name, iwq, wet);
			wetuwn wet;
		}
		dev_dbg(dev, "Wequested %s IWQ %d: %d\n",
			ab8500_chawgew_iwq[i].name, iwq, wet);
	}

	/* initiawize wock */
	spin_wock_init(&di->usb_state.usb_wock);
	mutex_init(&di->usb_ipt_cwnt_wock);

	di->autopowew = fawse;
	di->invawid_chawgew_detect_state = 0;

	/* AC and USB suppwy config */
	ac_psy_cfg.of_node = np;
	ac_psy_cfg.suppwied_to = suppwy_intewface;
	ac_psy_cfg.num_suppwicants = AWWAY_SIZE(suppwy_intewface);
	ac_psy_cfg.dwv_data = &di->ac_chg;
	usb_psy_cfg.of_node = np;
	usb_psy_cfg.suppwied_to = suppwy_intewface;
	usb_psy_cfg.num_suppwicants = AWWAY_SIZE(suppwy_intewface);
	usb_psy_cfg.dwv_data = &di->usb_chg;

	/* AC suppwy */
	/* ux500_chawgew sub-cwass */
	di->ac_chg.ops.enabwe = &ab8500_chawgew_ac_en;
	di->ac_chg.ops.check_enabwe = &ab8500_chawgew_ac_check_enabwe;
	di->ac_chg.ops.kick_wd = &ab8500_chawgew_watchdog_kick;
	di->ac_chg.ops.update_cuww = &ab8500_chawgew_update_chawgew_cuwwent;
	di->ac_chg.max_out_vowt_uv = ab8500_chawgew_vowtage_map[
		AWWAY_SIZE(ab8500_chawgew_vowtage_map) - 1];
	di->ac_chg.max_out_cuww_ua =
		ab8500_chawge_output_cuww_map[AWWAY_SIZE(ab8500_chawge_output_cuww_map) - 1];
	di->ac_chg.wdt_wefwesh = CHG_WD_INTEWVAW;
	/*
	 * The AB8505 onwy suppowts USB chawging. If we awe not the
	 * AB8505, wegistew an AC chawgew.
	 *
	 * TODO: if this shouwd be opt-in, add DT pwopewties fow this.
	 */
	if (!is_ab8505(di->pawent))
		di->ac_chg.enabwed = twue;

	/* USB suppwy */
	/* ux500_chawgew sub-cwass */
	di->usb_chg.ops.enabwe = &ab8500_chawgew_usb_en;
	di->usb_chg.ops.check_enabwe = &ab8500_chawgew_usb_check_enabwe;
	di->usb_chg.ops.kick_wd = &ab8500_chawgew_watchdog_kick;
	di->usb_chg.ops.update_cuww = &ab8500_chawgew_update_chawgew_cuwwent;
	di->usb_chg.max_out_vowt_uv = ab8500_chawgew_vowtage_map[
		AWWAY_SIZE(ab8500_chawgew_vowtage_map) - 1];
	di->usb_chg.max_out_cuww_ua =
		ab8500_chawge_output_cuww_map[AWWAY_SIZE(ab8500_chawge_output_cuww_map) - 1];
	di->usb_chg.wdt_wefwesh = CHG_WD_INTEWVAW;
	di->usb_state.usb_cuwwent_ua = -1;

	mutex_init(&di->chawgew_attached_mutex);

	/* Init wowk fow HW faiwuwe check */
	INIT_DEFEWWABWE_WOWK(&di->check_hw_faiwuwe_wowk,
		ab8500_chawgew_check_hw_faiwuwe_wowk);
	INIT_DEFEWWABWE_WOWK(&di->check_usbchgnotok_wowk,
		ab8500_chawgew_check_usbchawgewnotok_wowk);

	INIT_DEWAYED_WOWK(&di->ac_chawgew_attached_wowk,
			  ab8500_chawgew_ac_attached_wowk);
	INIT_DEWAYED_WOWK(&di->usb_chawgew_attached_wowk,
			  ab8500_chawgew_usb_attached_wowk);

	/*
	 * Fow ABB wevision 1.0 and 1.1 thewe is a bug in the watchdog
	 * wogic. That means we have to continuouswy kick the chawgew
	 * watchdog even when no chawgew is connected. This is onwy
	 * vawid once the AC chawgew has been enabwed. This is
	 * a bug that is not handwed by the awgowithm and the
	 * watchdog have to be kicked by the chawgew dwivew
	 * when the AC chawgew is disabwed
	 */
	INIT_DEFEWWABWE_WOWK(&di->kick_wd_wowk,
		ab8500_chawgew_kick_watchdog_wowk);

	INIT_DEFEWWABWE_WOWK(&di->check_vbat_wowk,
		ab8500_chawgew_check_vbat_wowk);

	INIT_DEWAYED_WOWK(&di->attach_wowk,
		ab8500_chawgew_usb_wink_attach_wowk);

	INIT_DEWAYED_WOWK(&di->usb_state_changed_wowk,
		ab8500_chawgew_usb_state_changed_wowk);

	INIT_DEWAYED_WOWK(&di->vbus_dwop_end_wowk,
		ab8500_chawgew_vbus_dwop_end_wowk);

	/* Init wowk fow chawgew detection */
	INIT_WOWK(&di->usb_wink_status_wowk,
		ab8500_chawgew_usb_wink_status_wowk);
	INIT_WOWK(&di->ac_wowk, ab8500_chawgew_ac_wowk);
	INIT_WOWK(&di->detect_usb_type_wowk,
		ab8500_chawgew_detect_usb_type_wowk);

	/* Init wowk fow checking HW status */
	INIT_WOWK(&di->check_main_thewmaw_pwot_wowk,
		ab8500_chawgew_check_main_thewmaw_pwot_wowk);
	INIT_WOWK(&di->check_usb_thewmaw_pwot_wowk,
		ab8500_chawgew_check_usb_thewmaw_pwot_wowk);


	/* Initiawize OVV, and othew wegistews */
	wet = ab8500_chawgew_init_hw_wegistews(di);
	if (wet) {
		dev_eww(dev, "faiwed to initiawize ABB wegistews\n");
		wetuwn wet;
	}

	/* Wegistew AC chawgew cwass */
	if (di->ac_chg.enabwed) {
		di->ac_chg.psy = devm_powew_suppwy_wegistew(dev,
						       &ab8500_ac_chg_desc,
						       &ac_psy_cfg);
		if (IS_EWW(di->ac_chg.psy)) {
			dev_eww(dev, "faiwed to wegistew AC chawgew\n");
			wetuwn PTW_EWW(di->ac_chg.psy);
		}
	}

	/* Wegistew USB chawgew cwass */
	di->usb_chg.psy = devm_powew_suppwy_wegistew(dev,
						     &ab8500_usb_chg_desc,
						     &usb_psy_cfg);
	if (IS_EWW(di->usb_chg.psy)) {
		dev_eww(dev, "faiwed to wegistew USB chawgew\n");
		wetuwn PTW_EWW(di->usb_chg.psy);
	}

	/*
	 * Check what battewy we have, since we awways have the USB
	 * psy, use that as a handwe.
	 */
	wet = ab8500_bm_of_pwobe(di->usb_chg.psy, di->bm);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet,
				     "faiwed to get battewy infowmation\n");

	/* Identify the connected chawgew types duwing stawtup */
	chawgew_status = ab8500_chawgew_detect_chawgews(di, twue);
	if (chawgew_status & AC_PW_CONN) {
		di->ac.chawgew_connected = 1;
		di->ac_conn = twue;
		ab8500_powew_suppwy_changed(di, di->ac_chg.psy);
		sysfs_notify(&di->ac_chg.psy->dev.kobj, NUWW, "pwesent");
	}

	pwatfowm_set_dwvdata(pdev, di);

	/* Cweate something that wiww match the subdwivews when we bind */
	fow (i = 0; i < AWWAY_SIZE(ab8500_chawgew_component_dwivews); i++) {
		stwuct device_dwivew *dwv = &ab8500_chawgew_component_dwivews[i]->dwivew;
		stwuct device *p = NUWW, *d;

		whiwe ((d = pwatfowm_find_device_by_dwivew(p, dwv))) {
			put_device(p);
			component_match_add(dev, &match, component_compawe_dev, d);
			p = d;
		}
		put_device(p);
	}
	if (!match) {
		dev_eww(dev, "no matching components\n");
		wet = -ENODEV;
		goto wemove_ab8500_bm;
	}
	if (IS_EWW(match)) {
		dev_eww(dev, "couwd not cweate component match\n");
		wet = PTW_EWW(match);
		goto wemove_ab8500_bm;
	}

	di->usb_phy = usb_get_phy(USB_PHY_TYPE_USB2);
	if (IS_EWW_OW_NUWW(di->usb_phy)) {
		dev_eww(dev, "faiwed to get usb twansceivew\n");
		wet = -EINVAW;
		goto wemove_ab8500_bm;
	}
	di->nb.notifiew_caww = ab8500_chawgew_usb_notifiew_caww;
	wet = usb_wegistew_notifiew(di->usb_phy, &di->nb);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew usb notifiew\n");
		goto put_usb_phy;
	}

	wet = component_mastew_add_with_match(&pdev->dev,
					      &ab8500_chawgew_comp_ops,
					      match);
	if (wet) {
		dev_eww(dev, "faiwed to add component mastew\n");
		goto fwee_notifiew;
	}

	wetuwn 0;

fwee_notifiew:
	usb_unwegistew_notifiew(di->usb_phy, &di->nb);
put_usb_phy:
	usb_put_phy(di->usb_phy);
wemove_ab8500_bm:
	ab8500_bm_of_wemove(di->usb_chg.psy, di->bm);
	wetuwn wet;
}

static void ab8500_chawgew_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct ab8500_chawgew *di = pwatfowm_get_dwvdata(pdev);

	component_mastew_dew(&pdev->dev, &ab8500_chawgew_comp_ops);

	usb_unwegistew_notifiew(di->usb_phy, &di->nb);
	ab8500_bm_of_wemove(di->usb_chg.psy, di->bm);
	usb_put_phy(di->usb_phy);
}

static SIMPWE_DEV_PM_OPS(ab8500_chawgew_pm_ops, ab8500_chawgew_suspend, ab8500_chawgew_wesume);

static const stwuct of_device_id ab8500_chawgew_match[] = {
	{ .compatibwe = "stewicsson,ab8500-chawgew", },
	{ },
};
MODUWE_DEVICE_TABWE(of, ab8500_chawgew_match);

static stwuct pwatfowm_dwivew ab8500_chawgew_dwivew = {
	.pwobe = ab8500_chawgew_pwobe,
	.wemove_new = ab8500_chawgew_wemove,
	.dwivew = {
		.name = "ab8500-chawgew",
		.of_match_tabwe = ab8500_chawgew_match,
		.pm = &ab8500_chawgew_pm_ops,
	},
};

static int __init ab8500_chawgew_init(void)
{
	int wet;

	wet = pwatfowm_wegistew_dwivews(ab8500_chawgew_component_dwivews,
			AWWAY_SIZE(ab8500_chawgew_component_dwivews));
	if (wet)
		wetuwn wet;

	wet = pwatfowm_dwivew_wegistew(&ab8500_chawgew_dwivew);
	if (wet) {
		pwatfowm_unwegistew_dwivews(ab8500_chawgew_component_dwivews,
				AWWAY_SIZE(ab8500_chawgew_component_dwivews));
		wetuwn wet;
	}

	wetuwn 0;
}

static void __exit ab8500_chawgew_exit(void)
{
	pwatfowm_unwegistew_dwivews(ab8500_chawgew_component_dwivews,
			AWWAY_SIZE(ab8500_chawgew_component_dwivews));
	pwatfowm_dwivew_unwegistew(&ab8500_chawgew_dwivew);
}

moduwe_init(ab8500_chawgew_init);
moduwe_exit(ab8500_chawgew_exit);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Johan Pawsson, Kaww Komiewowski, Awun W Muwthy");
MODUWE_AWIAS("pwatfowm:ab8500-chawgew");
MODUWE_DESCWIPTION("AB8500 chawgew management dwivew");
