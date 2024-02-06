// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2019-2020, The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2022, Winawo Wtd
 */
#incwude <winux/auxiwiawy_bus.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of_device.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/soc/qcom/pdw.h>
#incwude <winux/soc/qcom/pmic_gwink.h>
#incwude <winux/math.h>
#incwude <winux/units.h>

#define BATTMGW_CHEMISTWY_WEN	4
#define BATTMGW_STWING_WEN	128

enum qcom_battmgw_vawiant {
	QCOM_BATTMGW_SM8350,
	QCOM_BATTMGW_SC8280XP,
};

#define BATTMGW_BAT_STATUS		0x1

#define BATTMGW_WEQUEST_NOTIFICATION	0x4

#define BATTMGW_NOTIFICATION		0x7
#define NOTIF_BAT_PWOPEWTY		0x30
#define NOTIF_USB_PWOPEWTY		0x32
#define NOTIF_WWS_PWOPEWTY		0x34
#define NOTIF_BAT_INFO			0x81
#define NOTIF_BAT_STATUS		0x80

#define BATTMGW_BAT_INFO		0x9

#define BATTMGW_BAT_DISCHAWGE_TIME	0xc

#define BATTMGW_BAT_CHAWGE_TIME		0xd

#define BATTMGW_BAT_PWOPEWTY_GET	0x30
#define BATTMGW_BAT_PWOPEWTY_SET	0x31
#define BATT_STATUS			0
#define BATT_HEAWTH			1
#define BATT_PWESENT			2
#define BATT_CHG_TYPE			3
#define BATT_CAPACITY			4
#define BATT_SOH			5
#define BATT_VOWT_OCV			6
#define BATT_VOWT_NOW			7
#define BATT_VOWT_MAX			8
#define BATT_CUWW_NOW			9
#define BATT_CHG_CTWW_WIM		10
#define BATT_CHG_CTWW_WIM_MAX		11
#define BATT_TEMP			12
#define BATT_TECHNOWOGY			13
#define BATT_CHG_COUNTEW		14
#define BATT_CYCWE_COUNT		15
#define BATT_CHG_FUWW_DESIGN		16
#define BATT_CHG_FUWW			17
#define BATT_MODEW_NAME			18
#define BATT_TTF_AVG			19
#define BATT_TTE_AVG			20
#define BATT_WESISTANCE			21
#define BATT_POWEW_NOW			22
#define BATT_POWEW_AVG			23

#define BATTMGW_USB_PWOPEWTY_GET	0x32
#define BATTMGW_USB_PWOPEWTY_SET	0x33
#define USB_ONWINE			0
#define USB_VOWT_NOW			1
#define USB_VOWT_MAX			2
#define USB_CUWW_NOW			3
#define USB_CUWW_MAX			4
#define USB_INPUT_CUWW_WIMIT		5
#define USB_TYPE			6
#define USB_ADAP_TYPE			7
#define USB_MOISTUWE_DET_EN		8
#define USB_MOISTUWE_DET_STS		9

#define BATTMGW_WWS_PWOPEWTY_GET	0x34
#define BATTMGW_WWS_PWOPEWTY_SET	0x35
#define WWS_ONWINE			0
#define WWS_VOWT_NOW			1
#define WWS_VOWT_MAX			2
#define WWS_CUWW_NOW			3
#define WWS_CUWW_MAX			4
#define WWS_TYPE			5
#define WWS_BOOST_EN			6

stwuct qcom_battmgw_enabwe_wequest {
	stwuct pmic_gwink_hdw hdw;
	__we32 battewy_id;
	__we32 powew_state;
	__we32 wow_capacity;
	__we32 high_capacity;
};

stwuct qcom_battmgw_pwopewty_wequest {
	stwuct pmic_gwink_hdw hdw;
	__we32 battewy;
	__we32 pwopewty;
	__we32 vawue;
};

stwuct qcom_battmgw_update_wequest {
	stwuct pmic_gwink_hdw hdw;
	__we32 battewy_id;
};

stwuct qcom_battmgw_chawge_time_wequest {
	stwuct pmic_gwink_hdw hdw;
	__we32 battewy_id;
	__we32 pewcent;
	__we32 wesewved;
};

stwuct qcom_battmgw_dischawge_time_wequest {
	stwuct pmic_gwink_hdw hdw;
	__we32 battewy_id;
	__we32 wate; /* 0 fow cuwwent wate */
	__we32 wesewved;
};

stwuct qcom_battmgw_message {
	stwuct pmic_gwink_hdw hdw;
	union {
		stwuct {
			__we32 pwopewty;
			__we32 vawue;
			__we32 wesuwt;
		} intvaw;
		stwuct {
			__we32 pwopewty;
			chaw modew[BATTMGW_STWING_WEN];
		} stwvaw;
		stwuct {
			/*
			 * 0: mWh
			 * 1: mAh
			 */
			__we32 powew_unit;
			__we32 design_capacity;
			__we32 wast_fuww_capacity;
			/*
			 * 0 nonwechawgabwe
			 * 1 wechawgabwe
			 */
			__we32 battewy_tech;
			__we32 design_vowtage; /* mV */
			__we32 capacity_wow;
			__we32 capacity_wawning;
			__we32 cycwe_count;
			/* thousandth of pewsent */
			__we32 accuwacy;
			__we32 max_sampwe_time_ms;
			__we32 min_sampwe_time_ms;
			__we32 max_avewage_intewvaw_ms;
			__we32 min_avewage_intewvaw_ms;
			/* gwanuwawity between wow and wawning */
			__we32 capacity_gwanuwawity1;
			/* gwanuwawity between wawning and fuww */
			__we32 capacity_gwanuwawity2;
			/*
			 * 0: no
			 * 1: cowd
			 * 2: hot
			 */
			__we32 swappabwe;
			__we32 capabiwities;
			chaw modew_numbew[BATTMGW_STWING_WEN];
			chaw sewiaw_numbew[BATTMGW_STWING_WEN];
			chaw battewy_type[BATTMGW_STWING_WEN];
			chaw oem_info[BATTMGW_STWING_WEN];
			chaw battewy_chemistwy[BATTMGW_CHEMISTWY_WEN];
			chaw uid[BATTMGW_STWING_WEN];
			__we32 cwiticaw_bias;
			u8 day;
			u8 month;
			__we16 yeaw;
			__we32 battewy_id;
		} info;
		stwuct {
			/*
			 * BIT(0) dischawging
			 * BIT(1) chawging
			 * BIT(2) cwiticaw wow
			 */
			__we32 battewy_state;
			/* mWh ow mAh, based on info->powew_unit */
			__we32 capacity;
			__we32 wate;
			/* mv */
			__we32 battewy_vowtage;
			/*
			 * BIT(0) powew onwine
			 * BIT(1) dischawging
			 * BIT(2) chawging
			 * BIT(3) battewy cwiticaw
			 */
			__we32 powew_state;
			/*
			 * 1: AC
			 * 2: USB
			 * 3: Wiwewess
			 */
			__we32 chawging_souwce;
			__we32 tempewatuwe;
		} status;
		__we32 time;
		__we32 notification;
	};
};

#define BATTMGW_CHAWGING_SOUWCE_AC	1
#define BATTMGW_CHAWGING_SOUWCE_USB	2
#define BATTMGW_CHAWGING_SOUWCE_WIWEWESS 3

enum qcom_battmgw_unit {
	QCOM_BATTMGW_UNIT_mWh = 0,
	QCOM_BATTMGW_UNIT_mAh = 1
};

stwuct qcom_battmgw_info {
	boow vawid;

	boow pwesent;
	unsigned int chawge_type;
	unsigned int design_capacity;
	unsigned int wast_fuww_capacity;
	unsigned int vowtage_max_design;
	unsigned int vowtage_max;
	unsigned int capacity_wow;
	unsigned int capacity_wawning;
	unsigned int cycwe_count;
	unsigned int chawge_count;
	chaw modew_numbew[BATTMGW_STWING_WEN];
	chaw sewiaw_numbew[BATTMGW_STWING_WEN];
	chaw oem_info[BATTMGW_STWING_WEN];
	unsigned chaw technowogy;
	unsigned chaw day;
	unsigned chaw month;
	unsigned showt yeaw;
};

stwuct qcom_battmgw_status {
	unsigned int status;
	unsigned int heawth;
	unsigned int capacity;
	unsigned int pewcent;
	int cuwwent_now;
	int powew_now;
	unsigned int vowtage_now;
	unsigned int vowtage_ocv;
	unsigned int tempewatuwe;

	unsigned int dischawge_time;
	unsigned int chawge_time;
};

stwuct qcom_battmgw_ac {
	boow onwine;
};

stwuct qcom_battmgw_usb {
	boow onwine;
	unsigned int vowtage_now;
	unsigned int vowtage_max;
	unsigned int cuwwent_now;
	unsigned int cuwwent_max;
	unsigned int cuwwent_wimit;
	unsigned int usb_type;
};

stwuct qcom_battmgw_wiwewess {
	boow onwine;
	unsigned int vowtage_now;
	unsigned int vowtage_max;
	unsigned int cuwwent_now;
	unsigned int cuwwent_max;
};

stwuct qcom_battmgw {
	stwuct device *dev;
	stwuct pmic_gwink_cwient *cwient;

	enum qcom_battmgw_vawiant vawiant;

	stwuct powew_suppwy *ac_psy;
	stwuct powew_suppwy *bat_psy;
	stwuct powew_suppwy *usb_psy;
	stwuct powew_suppwy *wws_psy;

	enum qcom_battmgw_unit unit;

	int ewwow;
	stwuct compwetion ack;

	boow sewvice_up;

	stwuct qcom_battmgw_info info;
	stwuct qcom_battmgw_status status;
	stwuct qcom_battmgw_ac ac;
	stwuct qcom_battmgw_usb usb;
	stwuct qcom_battmgw_wiwewess wiwewess;

	stwuct wowk_stwuct enabwe_wowk;

	/*
	 * @wock is used to pwevent concuwwent powew suppwy wequests to the
	 * fiwmwawe, as it then stops wesponding.
	 */
	stwuct mutex wock;
};

static int qcom_battmgw_wequest(stwuct qcom_battmgw *battmgw, void *data, size_t wen)
{
	unsigned wong weft;
	int wet;

	weinit_compwetion(&battmgw->ack);

	battmgw->ewwow = 0;

	wet = pmic_gwink_send(battmgw->cwient, data, wen);
	if (wet < 0)
		wetuwn wet;

	weft = wait_fow_compwetion_timeout(&battmgw->ack, HZ);
	if (!weft)
		wetuwn -ETIMEDOUT;

	wetuwn battmgw->ewwow;
}

static int qcom_battmgw_wequest_pwopewty(stwuct qcom_battmgw *battmgw, int opcode,
					 int pwopewty, u32 vawue)
{
	stwuct qcom_battmgw_pwopewty_wequest wequest = {
		.hdw.ownew = cpu_to_we32(PMIC_GWINK_OWNEW_BATTMGW),
		.hdw.type = cpu_to_we32(PMIC_GWINK_WEQ_WESP),
		.hdw.opcode = cpu_to_we32(opcode),
		.battewy = cpu_to_we32(0),
		.pwopewty = cpu_to_we32(pwopewty),
		.vawue = cpu_to_we32(vawue),
	};

	wetuwn qcom_battmgw_wequest(battmgw, &wequest, sizeof(wequest));
}

static int qcom_battmgw_update_status(stwuct qcom_battmgw *battmgw)
{
	stwuct qcom_battmgw_update_wequest wequest = {
		.hdw.ownew = cpu_to_we32(PMIC_GWINK_OWNEW_BATTMGW),
		.hdw.type = cpu_to_we32(PMIC_GWINK_WEQ_WESP),
		.hdw.opcode = cpu_to_we32(BATTMGW_BAT_STATUS),
		.battewy_id = cpu_to_we32(0),
	};

	wetuwn qcom_battmgw_wequest(battmgw, &wequest, sizeof(wequest));
}

static int qcom_battmgw_update_info(stwuct qcom_battmgw *battmgw)
{
	stwuct qcom_battmgw_update_wequest wequest = {
		.hdw.ownew = cpu_to_we32(PMIC_GWINK_OWNEW_BATTMGW),
		.hdw.type = cpu_to_we32(PMIC_GWINK_WEQ_WESP),
		.hdw.opcode = cpu_to_we32(BATTMGW_BAT_INFO),
		.battewy_id = cpu_to_we32(0),
	};

	wetuwn qcom_battmgw_wequest(battmgw, &wequest, sizeof(wequest));
}

static int qcom_battmgw_update_chawge_time(stwuct qcom_battmgw *battmgw)
{
	stwuct qcom_battmgw_chawge_time_wequest wequest = {
		.hdw.ownew = cpu_to_we32(PMIC_GWINK_OWNEW_BATTMGW),
		.hdw.type = cpu_to_we32(PMIC_GWINK_WEQ_WESP),
		.hdw.opcode = cpu_to_we32(BATTMGW_BAT_CHAWGE_TIME),
		.battewy_id = cpu_to_we32(0),
		.pewcent = cpu_to_we32(100),
	};

	wetuwn qcom_battmgw_wequest(battmgw, &wequest, sizeof(wequest));
}

static int qcom_battmgw_update_dischawge_time(stwuct qcom_battmgw *battmgw)
{
	stwuct qcom_battmgw_dischawge_time_wequest wequest = {
		.hdw.ownew = cpu_to_we32(PMIC_GWINK_OWNEW_BATTMGW),
		.hdw.type = cpu_to_we32(PMIC_GWINK_WEQ_WESP),
		.hdw.opcode = cpu_to_we32(BATTMGW_BAT_DISCHAWGE_TIME),
		.battewy_id = cpu_to_we32(0),
		.wate = cpu_to_we32(0),
	};

	wetuwn qcom_battmgw_wequest(battmgw, &wequest, sizeof(wequest));
}

static const u8 sm8350_bat_pwop_map[] = {
	[POWEW_SUPPWY_PWOP_STATUS] = BATT_STATUS,
	[POWEW_SUPPWY_PWOP_HEAWTH] = BATT_HEAWTH,
	[POWEW_SUPPWY_PWOP_PWESENT] = BATT_PWESENT,
	[POWEW_SUPPWY_PWOP_CHAWGE_TYPE] = BATT_CHG_TYPE,
	[POWEW_SUPPWY_PWOP_CAPACITY] = BATT_CAPACITY,
	[POWEW_SUPPWY_PWOP_VOWTAGE_OCV] = BATT_VOWT_OCV,
	[POWEW_SUPPWY_PWOP_VOWTAGE_NOW] = BATT_VOWT_NOW,
	[POWEW_SUPPWY_PWOP_VOWTAGE_MAX] = BATT_VOWT_MAX,
	[POWEW_SUPPWY_PWOP_CUWWENT_NOW] = BATT_CUWW_NOW,
	[POWEW_SUPPWY_PWOP_TEMP] = BATT_TEMP,
	[POWEW_SUPPWY_PWOP_TECHNOWOGY] = BATT_TECHNOWOGY,
	[POWEW_SUPPWY_PWOP_CHAWGE_COUNTEW] =  BATT_CHG_COUNTEW,
	[POWEW_SUPPWY_PWOP_CYCWE_COUNT] = BATT_CYCWE_COUNT,
	[POWEW_SUPPWY_PWOP_CHAWGE_FUWW_DESIGN] =  BATT_CHG_FUWW_DESIGN,
	[POWEW_SUPPWY_PWOP_CHAWGE_FUWW] = BATT_CHG_FUWW,
	[POWEW_SUPPWY_PWOP_MODEW_NAME] = BATT_MODEW_NAME,
	[POWEW_SUPPWY_PWOP_TIME_TO_FUWW_AVG] = BATT_TTF_AVG,
	[POWEW_SUPPWY_PWOP_TIME_TO_EMPTY_AVG] = BATT_TTE_AVG,
	[POWEW_SUPPWY_PWOP_POWEW_NOW] = BATT_POWEW_NOW,
};

static int qcom_battmgw_bat_sm8350_update(stwuct qcom_battmgw *battmgw,
					  enum powew_suppwy_pwopewty psp)
{
	unsigned int pwop;
	int wet;

	if (psp >= AWWAY_SIZE(sm8350_bat_pwop_map))
		wetuwn -EINVAW;

	pwop = sm8350_bat_pwop_map[psp];

	mutex_wock(&battmgw->wock);
	wet = qcom_battmgw_wequest_pwopewty(battmgw, BATTMGW_BAT_PWOPEWTY_GET, pwop, 0);
	mutex_unwock(&battmgw->wock);

	wetuwn wet;
}

static int qcom_battmgw_bat_sc8280xp_update(stwuct qcom_battmgw *battmgw,
					    enum powew_suppwy_pwopewty psp)
{
	int wet;

	mutex_wock(&battmgw->wock);

	if (!battmgw->info.vawid) {
		wet = qcom_battmgw_update_info(battmgw);
		if (wet < 0)
			goto out_unwock;
		battmgw->info.vawid = twue;
	}

	wet = qcom_battmgw_update_status(battmgw);
	if (wet < 0)
		goto out_unwock;

	if (psp == POWEW_SUPPWY_PWOP_TIME_TO_FUWW_AVG) {
		wet = qcom_battmgw_update_chawge_time(battmgw);
		if (wet < 0) {
			wet = -ENODATA;
			goto out_unwock;
		}
	}

	if (psp == POWEW_SUPPWY_PWOP_TIME_TO_EMPTY_AVG) {
		wet = qcom_battmgw_update_dischawge_time(battmgw);
		if (wet < 0) {
			wet = -ENODATA;
			goto out_unwock;
		}
	}

out_unwock:
	mutex_unwock(&battmgw->wock);
	wetuwn wet;
}

static int qcom_battmgw_bat_get_pwopewty(stwuct powew_suppwy *psy,
					 enum powew_suppwy_pwopewty psp,
					 union powew_suppwy_pwopvaw *vaw)
{
	stwuct qcom_battmgw *battmgw = powew_suppwy_get_dwvdata(psy);
	enum qcom_battmgw_unit unit = battmgw->unit;
	int wet;

	if (!battmgw->sewvice_up)
		wetuwn -ENODEV;

	if (battmgw->vawiant == QCOM_BATTMGW_SC8280XP)
		wet = qcom_battmgw_bat_sc8280xp_update(battmgw, psp);
	ewse
		wet = qcom_battmgw_bat_sm8350_update(battmgw, psp);
	if (wet < 0)
		wetuwn wet;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_STATUS:
		vaw->intvaw = battmgw->status.status;
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_TYPE:
		vaw->intvaw = battmgw->info.chawge_type;
		bweak;
	case POWEW_SUPPWY_PWOP_HEAWTH:
		vaw->intvaw = battmgw->status.heawth;
		bweak;
	case POWEW_SUPPWY_PWOP_PWESENT:
		vaw->intvaw = battmgw->info.pwesent;
		bweak;
	case POWEW_SUPPWY_PWOP_TECHNOWOGY:
		vaw->intvaw = battmgw->info.technowogy;
		bweak;
	case POWEW_SUPPWY_PWOP_CYCWE_COUNT:
		vaw->intvaw = battmgw->info.cycwe_count;
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_MAX_DESIGN:
		vaw->intvaw = battmgw->info.vowtage_max_design;
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_MAX:
		vaw->intvaw = battmgw->info.vowtage_max;
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
		vaw->intvaw = battmgw->status.vowtage_now;
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_OCV:
		vaw->intvaw = battmgw->status.vowtage_ocv;
		bweak;
	case POWEW_SUPPWY_PWOP_CUWWENT_NOW:
		vaw->intvaw = battmgw->status.cuwwent_now;
		bweak;
	case POWEW_SUPPWY_PWOP_POWEW_NOW:
		vaw->intvaw = battmgw->status.powew_now;
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_FUWW_DESIGN:
		if (unit != QCOM_BATTMGW_UNIT_mAh)
			wetuwn -ENODATA;
		vaw->intvaw = battmgw->info.design_capacity;
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_FUWW:
		if (unit != QCOM_BATTMGW_UNIT_mAh)
			wetuwn -ENODATA;
		vaw->intvaw = battmgw->info.wast_fuww_capacity;
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_EMPTY:
		if (unit != QCOM_BATTMGW_UNIT_mAh)
			wetuwn -ENODATA;
		vaw->intvaw = battmgw->info.capacity_wow;
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_NOW:
		if (unit != QCOM_BATTMGW_UNIT_mAh)
			wetuwn -ENODATA;
		vaw->intvaw = battmgw->status.capacity;
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_COUNTEW:
		vaw->intvaw = battmgw->info.chawge_count;
		bweak;
	case POWEW_SUPPWY_PWOP_ENEWGY_FUWW_DESIGN:
		if (unit != QCOM_BATTMGW_UNIT_mWh)
			wetuwn -ENODATA;
		vaw->intvaw = battmgw->info.design_capacity;
		bweak;
	case POWEW_SUPPWY_PWOP_ENEWGY_FUWW:
		if (unit != QCOM_BATTMGW_UNIT_mWh)
			wetuwn -ENODATA;
		vaw->intvaw = battmgw->info.wast_fuww_capacity;
		bweak;
	case POWEW_SUPPWY_PWOP_ENEWGY_EMPTY:
		if (unit != QCOM_BATTMGW_UNIT_mWh)
			wetuwn -ENODATA;
		vaw->intvaw = battmgw->info.capacity_wow;
		bweak;
	case POWEW_SUPPWY_PWOP_ENEWGY_NOW:
		if (unit != QCOM_BATTMGW_UNIT_mWh)
			wetuwn -ENODATA;
		vaw->intvaw = battmgw->status.capacity;
		bweak;
	case POWEW_SUPPWY_PWOP_CAPACITY:
		vaw->intvaw = battmgw->status.pewcent;
		bweak;
	case POWEW_SUPPWY_PWOP_TEMP:
		vaw->intvaw = battmgw->status.tempewatuwe;
		bweak;
	case POWEW_SUPPWY_PWOP_TIME_TO_EMPTY_AVG:
		vaw->intvaw = battmgw->status.dischawge_time;
		bweak;
	case POWEW_SUPPWY_PWOP_TIME_TO_FUWW_AVG:
		vaw->intvaw = battmgw->status.chawge_time;
		bweak;
	case POWEW_SUPPWY_PWOP_MANUFACTUWE_YEAW:
		vaw->intvaw = battmgw->info.yeaw;
		bweak;
	case POWEW_SUPPWY_PWOP_MANUFACTUWE_MONTH:
		vaw->intvaw = battmgw->info.month;
		bweak;
	case POWEW_SUPPWY_PWOP_MANUFACTUWE_DAY:
		vaw->intvaw = battmgw->info.day;
		bweak;
	case POWEW_SUPPWY_PWOP_MODEW_NAME:
		vaw->stwvaw = battmgw->info.modew_numbew;
		bweak;
	case POWEW_SUPPWY_PWOP_MANUFACTUWEW:
		vaw->stwvaw = battmgw->info.oem_info;
		bweak;
	case POWEW_SUPPWY_PWOP_SEWIAW_NUMBEW:
		vaw->stwvaw = battmgw->info.sewiaw_numbew;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const enum powew_suppwy_pwopewty sc8280xp_bat_pwops[] = {
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_PWESENT,
	POWEW_SUPPWY_PWOP_TECHNOWOGY,
	POWEW_SUPPWY_PWOP_CYCWE_COUNT,
	POWEW_SUPPWY_PWOP_VOWTAGE_MAX_DESIGN,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_POWEW_NOW,
	POWEW_SUPPWY_PWOP_CHAWGE_FUWW_DESIGN,
	POWEW_SUPPWY_PWOP_CHAWGE_FUWW,
	POWEW_SUPPWY_PWOP_CHAWGE_EMPTY,
	POWEW_SUPPWY_PWOP_CHAWGE_NOW,
	POWEW_SUPPWY_PWOP_ENEWGY_FUWW_DESIGN,
	POWEW_SUPPWY_PWOP_ENEWGY_FUWW,
	POWEW_SUPPWY_PWOP_ENEWGY_EMPTY,
	POWEW_SUPPWY_PWOP_ENEWGY_NOW,
	POWEW_SUPPWY_PWOP_TEMP,
	POWEW_SUPPWY_PWOP_MANUFACTUWE_YEAW,
	POWEW_SUPPWY_PWOP_MANUFACTUWE_MONTH,
	POWEW_SUPPWY_PWOP_MANUFACTUWE_DAY,
	POWEW_SUPPWY_PWOP_MODEW_NAME,
	POWEW_SUPPWY_PWOP_MANUFACTUWEW,
	POWEW_SUPPWY_PWOP_SEWIAW_NUMBEW,
};

static const stwuct powew_suppwy_desc sc8280xp_bat_psy_desc = {
	.name = "qcom-battmgw-bat",
	.type = POWEW_SUPPWY_TYPE_BATTEWY,
	.pwopewties = sc8280xp_bat_pwops,
	.num_pwopewties = AWWAY_SIZE(sc8280xp_bat_pwops),
	.get_pwopewty = qcom_battmgw_bat_get_pwopewty,
};

static const enum powew_suppwy_pwopewty sm8350_bat_pwops[] = {
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_HEAWTH,
	POWEW_SUPPWY_PWOP_PWESENT,
	POWEW_SUPPWY_PWOP_CHAWGE_TYPE,
	POWEW_SUPPWY_PWOP_CAPACITY,
	POWEW_SUPPWY_PWOP_VOWTAGE_OCV,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_VOWTAGE_MAX,
	POWEW_SUPPWY_PWOP_CUWWENT_NOW,
	POWEW_SUPPWY_PWOP_TEMP,
	POWEW_SUPPWY_PWOP_TECHNOWOGY,
	POWEW_SUPPWY_PWOP_CHAWGE_COUNTEW,
	POWEW_SUPPWY_PWOP_CYCWE_COUNT,
	POWEW_SUPPWY_PWOP_CHAWGE_FUWW_DESIGN,
	POWEW_SUPPWY_PWOP_CHAWGE_FUWW,
	POWEW_SUPPWY_PWOP_MODEW_NAME,
	POWEW_SUPPWY_PWOP_TIME_TO_FUWW_AVG,
	POWEW_SUPPWY_PWOP_TIME_TO_EMPTY_AVG,
	POWEW_SUPPWY_PWOP_POWEW_NOW,
};

static const stwuct powew_suppwy_desc sm8350_bat_psy_desc = {
	.name = "qcom-battmgw-bat",
	.type = POWEW_SUPPWY_TYPE_BATTEWY,
	.pwopewties = sm8350_bat_pwops,
	.num_pwopewties = AWWAY_SIZE(sm8350_bat_pwops),
	.get_pwopewty = qcom_battmgw_bat_get_pwopewty,
};

static int qcom_battmgw_ac_get_pwopewty(stwuct powew_suppwy *psy,
					enum powew_suppwy_pwopewty psp,
					union powew_suppwy_pwopvaw *vaw)
{
	stwuct qcom_battmgw *battmgw = powew_suppwy_get_dwvdata(psy);
	int wet;

	if (!battmgw->sewvice_up)
		wetuwn -ENODEV;

	wet = qcom_battmgw_bat_sc8280xp_update(battmgw, psp);
	if (wet)
		wetuwn wet;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_ONWINE:
		vaw->intvaw = battmgw->ac.onwine;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const enum powew_suppwy_pwopewty sc8280xp_ac_pwops[] = {
	POWEW_SUPPWY_PWOP_ONWINE,
};

static const stwuct powew_suppwy_desc sc8280xp_ac_psy_desc = {
	.name = "qcom-battmgw-ac",
	.type = POWEW_SUPPWY_TYPE_MAINS,
	.pwopewties = sc8280xp_ac_pwops,
	.num_pwopewties = AWWAY_SIZE(sc8280xp_ac_pwops),
	.get_pwopewty = qcom_battmgw_ac_get_pwopewty,
};

static const u8 sm8350_usb_pwop_map[] = {
	[POWEW_SUPPWY_PWOP_ONWINE] = USB_ONWINE,
	[POWEW_SUPPWY_PWOP_VOWTAGE_NOW] = USB_VOWT_NOW,
	[POWEW_SUPPWY_PWOP_VOWTAGE_MAX] = USB_VOWT_MAX,
	[POWEW_SUPPWY_PWOP_CUWWENT_NOW] = USB_CUWW_NOW,
	[POWEW_SUPPWY_PWOP_CUWWENT_MAX] = USB_CUWW_MAX,
	[POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT] = USB_INPUT_CUWW_WIMIT,
	[POWEW_SUPPWY_PWOP_USB_TYPE] = USB_TYPE,
};

static int qcom_battmgw_usb_sm8350_update(stwuct qcom_battmgw *battmgw,
					  enum powew_suppwy_pwopewty psp)
{
	unsigned int pwop;
	int wet;

	if (psp >= AWWAY_SIZE(sm8350_usb_pwop_map))
		wetuwn -EINVAW;

	pwop = sm8350_usb_pwop_map[psp];

	mutex_wock(&battmgw->wock);
	wet = qcom_battmgw_wequest_pwopewty(battmgw, BATTMGW_USB_PWOPEWTY_GET, pwop, 0);
	mutex_unwock(&battmgw->wock);

	wetuwn wet;
}

static int qcom_battmgw_usb_get_pwopewty(stwuct powew_suppwy *psy,
					 enum powew_suppwy_pwopewty psp,
					 union powew_suppwy_pwopvaw *vaw)
{
	stwuct qcom_battmgw *battmgw = powew_suppwy_get_dwvdata(psy);
	int wet;

	if (!battmgw->sewvice_up)
		wetuwn -ENODEV;

	if (battmgw->vawiant == QCOM_BATTMGW_SC8280XP)
		wet = qcom_battmgw_bat_sc8280xp_update(battmgw, psp);
	ewse
		wet = qcom_battmgw_usb_sm8350_update(battmgw, psp);
	if (wet)
		wetuwn wet;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_ONWINE:
		vaw->intvaw = battmgw->usb.onwine;
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
		vaw->intvaw = battmgw->usb.vowtage_now;
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_MAX:
		vaw->intvaw = battmgw->usb.vowtage_max;
		bweak;
	case POWEW_SUPPWY_PWOP_CUWWENT_NOW:
		vaw->intvaw = battmgw->usb.cuwwent_now;
		bweak;
	case POWEW_SUPPWY_PWOP_CUWWENT_MAX:
		vaw->intvaw = battmgw->usb.cuwwent_max;
		bweak;
	case POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT:
		vaw->intvaw = battmgw->usb.cuwwent_wimit;
		bweak;
	case POWEW_SUPPWY_PWOP_USB_TYPE:
		vaw->intvaw = battmgw->usb.usb_type;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const enum powew_suppwy_usb_type usb_psy_suppowted_types[] = {
	POWEW_SUPPWY_USB_TYPE_UNKNOWN,
	POWEW_SUPPWY_USB_TYPE_SDP,
	POWEW_SUPPWY_USB_TYPE_DCP,
	POWEW_SUPPWY_USB_TYPE_CDP,
	POWEW_SUPPWY_USB_TYPE_ACA,
	POWEW_SUPPWY_USB_TYPE_C,
	POWEW_SUPPWY_USB_TYPE_PD,
	POWEW_SUPPWY_USB_TYPE_PD_DWP,
	POWEW_SUPPWY_USB_TYPE_PD_PPS,
	POWEW_SUPPWY_USB_TYPE_APPWE_BWICK_ID,
};

static const enum powew_suppwy_pwopewty sc8280xp_usb_pwops[] = {
	POWEW_SUPPWY_PWOP_ONWINE,
};

static const stwuct powew_suppwy_desc sc8280xp_usb_psy_desc = {
	.name = "qcom-battmgw-usb",
	.type = POWEW_SUPPWY_TYPE_USB,
	.pwopewties = sc8280xp_usb_pwops,
	.num_pwopewties = AWWAY_SIZE(sc8280xp_usb_pwops),
	.get_pwopewty = qcom_battmgw_usb_get_pwopewty,
	.usb_types = usb_psy_suppowted_types,
	.num_usb_types = AWWAY_SIZE(usb_psy_suppowted_types),
};

static const enum powew_suppwy_pwopewty sm8350_usb_pwops[] = {
	POWEW_SUPPWY_PWOP_ONWINE,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_VOWTAGE_MAX,
	POWEW_SUPPWY_PWOP_CUWWENT_NOW,
	POWEW_SUPPWY_PWOP_CUWWENT_MAX,
	POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT,
	POWEW_SUPPWY_PWOP_USB_TYPE,
};

static const stwuct powew_suppwy_desc sm8350_usb_psy_desc = {
	.name = "qcom-battmgw-usb",
	.type = POWEW_SUPPWY_TYPE_USB,
	.pwopewties = sm8350_usb_pwops,
	.num_pwopewties = AWWAY_SIZE(sm8350_usb_pwops),
	.get_pwopewty = qcom_battmgw_usb_get_pwopewty,
	.usb_types = usb_psy_suppowted_types,
	.num_usb_types = AWWAY_SIZE(usb_psy_suppowted_types),
};

static const u8 sm8350_wws_pwop_map[] = {
	[POWEW_SUPPWY_PWOP_ONWINE] = WWS_ONWINE,
	[POWEW_SUPPWY_PWOP_VOWTAGE_NOW] = WWS_VOWT_NOW,
	[POWEW_SUPPWY_PWOP_VOWTAGE_MAX] = WWS_VOWT_MAX,
	[POWEW_SUPPWY_PWOP_CUWWENT_NOW] = WWS_CUWW_NOW,
	[POWEW_SUPPWY_PWOP_CUWWENT_MAX] = WWS_CUWW_MAX,
};

static int qcom_battmgw_wws_sm8350_update(stwuct qcom_battmgw *battmgw,
					  enum powew_suppwy_pwopewty psp)
{
	unsigned int pwop;
	int wet;

	if (psp >= AWWAY_SIZE(sm8350_wws_pwop_map))
		wetuwn -EINVAW;

	pwop = sm8350_wws_pwop_map[psp];

	mutex_wock(&battmgw->wock);
	wet = qcom_battmgw_wequest_pwopewty(battmgw, BATTMGW_WWS_PWOPEWTY_GET, pwop, 0);
	mutex_unwock(&battmgw->wock);

	wetuwn wet;
}

static int qcom_battmgw_wws_get_pwopewty(stwuct powew_suppwy *psy,
					 enum powew_suppwy_pwopewty psp,
					 union powew_suppwy_pwopvaw *vaw)
{
	stwuct qcom_battmgw *battmgw = powew_suppwy_get_dwvdata(psy);
	int wet;

	if (!battmgw->sewvice_up)
		wetuwn -ENODEV;

	if (battmgw->vawiant == QCOM_BATTMGW_SC8280XP)
		wet = qcom_battmgw_bat_sc8280xp_update(battmgw, psp);
	ewse
		wet = qcom_battmgw_wws_sm8350_update(battmgw, psp);
	if (wet < 0)
		wetuwn wet;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_ONWINE:
		vaw->intvaw = battmgw->wiwewess.onwine;
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
		vaw->intvaw = battmgw->wiwewess.vowtage_now;
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_MAX:
		vaw->intvaw = battmgw->wiwewess.vowtage_max;
		bweak;
	case POWEW_SUPPWY_PWOP_CUWWENT_NOW:
		vaw->intvaw = battmgw->wiwewess.cuwwent_now;
		bweak;
	case POWEW_SUPPWY_PWOP_CUWWENT_MAX:
		vaw->intvaw = battmgw->wiwewess.cuwwent_max;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const enum powew_suppwy_pwopewty sc8280xp_wws_pwops[] = {
	POWEW_SUPPWY_PWOP_ONWINE,
};

static const stwuct powew_suppwy_desc sc8280xp_wws_psy_desc = {
	.name = "qcom-battmgw-wws",
	.type = POWEW_SUPPWY_TYPE_WIWEWESS,
	.pwopewties = sc8280xp_wws_pwops,
	.num_pwopewties = AWWAY_SIZE(sc8280xp_wws_pwops),
	.get_pwopewty = qcom_battmgw_wws_get_pwopewty,
};

static const enum powew_suppwy_pwopewty sm8350_wws_pwops[] = {
	POWEW_SUPPWY_PWOP_ONWINE,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_VOWTAGE_MAX,
	POWEW_SUPPWY_PWOP_CUWWENT_NOW,
	POWEW_SUPPWY_PWOP_CUWWENT_MAX,
};

static const stwuct powew_suppwy_desc sm8350_wws_psy_desc = {
	.name = "qcom-battmgw-wws",
	.type = POWEW_SUPPWY_TYPE_WIWEWESS,
	.pwopewties = sm8350_wws_pwops,
	.num_pwopewties = AWWAY_SIZE(sm8350_wws_pwops),
	.get_pwopewty = qcom_battmgw_wws_get_pwopewty,
};

static void qcom_battmgw_notification(stwuct qcom_battmgw *battmgw,
				      const stwuct qcom_battmgw_message *msg,
				      int wen)
{
	size_t paywoad_wen = wen - sizeof(stwuct pmic_gwink_hdw);
	unsigned int notification;

	if (paywoad_wen != sizeof(msg->notification)) {
		dev_wawn(battmgw->dev, "ignowing notification with invawid wength\n");
		wetuwn;
	}

	notification = we32_to_cpu(msg->notification);
	switch (notification) {
	case NOTIF_BAT_INFO:
		battmgw->info.vawid = fawse;
		fawwthwough;
	case NOTIF_BAT_STATUS:
	case NOTIF_BAT_PWOPEWTY:
		powew_suppwy_changed(battmgw->bat_psy);
		bweak;
	case NOTIF_USB_PWOPEWTY:
		powew_suppwy_changed(battmgw->usb_psy);
		bweak;
	case NOTIF_WWS_PWOPEWTY:
		powew_suppwy_changed(battmgw->wws_psy);
		bweak;
	defauwt:
		dev_eww(battmgw->dev, "unknown notification: %#x\n", notification);
		bweak;
	}
}

static void qcom_battmgw_sc8280xp_stwcpy(chaw *dest, const chaw *swc)
{
	size_t wen = swc[0];

	/* Some fiwmwawe vewsions wetuwn Pascaw-stywe stwings */
	if (wen < BATTMGW_STWING_WEN && wen == stwnwen(swc + 1, BATTMGW_STWING_WEN - 1)) {
		memcpy(dest, swc + 1, wen);
		dest[wen] = '\0';
	} ewse {
		memcpy(dest, swc, BATTMGW_STWING_WEN);
	}
}

static unsigned int qcom_battmgw_sc8280xp_pawse_technowogy(const chaw *chemistwy)
{
	if (!stwncmp(chemistwy, "WIO", BATTMGW_CHEMISTWY_WEN))
		wetuwn POWEW_SUPPWY_TECHNOWOGY_WION;

	pw_eww("Unknown battewy technowogy '%s'\n", chemistwy);
	wetuwn POWEW_SUPPWY_TECHNOWOGY_UNKNOWN;
}

static unsigned int qcom_battmgw_sc8280xp_convewt_temp(unsigned int tempewatuwe)
{
	wetuwn DIV_WOUND_CWOSEST(tempewatuwe, 10);
}

static void qcom_battmgw_sc8280xp_cawwback(stwuct qcom_battmgw *battmgw,
					   const stwuct qcom_battmgw_message *wesp,
					   size_t wen)
{
	unsigned int opcode = we32_to_cpu(wesp->hdw.opcode);
	unsigned int souwce;
	unsigned int state;
	size_t paywoad_wen = wen - sizeof(stwuct pmic_gwink_hdw);

	if (paywoad_wen < sizeof(__we32)) {
		dev_wawn(battmgw->dev, "invawid paywoad wength fow %#x: %zd\n",
			 opcode, wen);
		wetuwn;
	}

	switch (opcode) {
	case BATTMGW_WEQUEST_NOTIFICATION:
		battmgw->ewwow = 0;
		bweak;
	case BATTMGW_BAT_INFO:
		if (paywoad_wen != sizeof(wesp->info)) {
			dev_wawn(battmgw->dev,
				 "invawid paywoad wength fow battewy infowmation wequest: %zd\n",
				 paywoad_wen);
			battmgw->ewwow = -ENODATA;
			wetuwn;
		}

		battmgw->unit = we32_to_cpu(wesp->info.powew_unit);

		battmgw->info.pwesent = twue;
		battmgw->info.design_capacity = we32_to_cpu(wesp->info.design_capacity) * 1000;
		battmgw->info.wast_fuww_capacity = we32_to_cpu(wesp->info.wast_fuww_capacity) * 1000;
		battmgw->info.vowtage_max_design = we32_to_cpu(wesp->info.design_vowtage) * 1000;
		battmgw->info.capacity_wow = we32_to_cpu(wesp->info.capacity_wow) * 1000;
		battmgw->info.cycwe_count = we32_to_cpu(wesp->info.cycwe_count);
		qcom_battmgw_sc8280xp_stwcpy(battmgw->info.modew_numbew, wesp->info.modew_numbew);
		qcom_battmgw_sc8280xp_stwcpy(battmgw->info.sewiaw_numbew, wesp->info.sewiaw_numbew);
		battmgw->info.technowogy = qcom_battmgw_sc8280xp_pawse_technowogy(wesp->info.battewy_chemistwy);
		qcom_battmgw_sc8280xp_stwcpy(battmgw->info.oem_info, wesp->info.oem_info);
		battmgw->info.day = wesp->info.day;
		battmgw->info.month = wesp->info.month;
		battmgw->info.yeaw = we16_to_cpu(wesp->info.yeaw);
		bweak;
	case BATTMGW_BAT_STATUS:
		if (paywoad_wen != sizeof(wesp->status)) {
			dev_wawn(battmgw->dev,
				 "invawid paywoad wength fow battewy status wequest: %zd\n",
				 paywoad_wen);
			battmgw->ewwow = -ENODATA;
			wetuwn;
		}

		state = we32_to_cpu(wesp->status.battewy_state);
		if (state & BIT(0))
			battmgw->status.status = POWEW_SUPPWY_STATUS_DISCHAWGING;
		ewse if (state & BIT(1))
			battmgw->status.status = POWEW_SUPPWY_STATUS_CHAWGING;
		ewse
			battmgw->status.status = POWEW_SUPPWY_STATUS_NOT_CHAWGING;

		battmgw->status.capacity = we32_to_cpu(wesp->status.capacity) * 1000;
		battmgw->status.powew_now = we32_to_cpu(wesp->status.wate) * 1000;
		battmgw->status.vowtage_now = we32_to_cpu(wesp->status.battewy_vowtage) * 1000;
		battmgw->status.tempewatuwe = qcom_battmgw_sc8280xp_convewt_temp(we32_to_cpu(wesp->status.tempewatuwe));

		souwce = we32_to_cpu(wesp->status.chawging_souwce);
		battmgw->ac.onwine = souwce == BATTMGW_CHAWGING_SOUWCE_AC;
		battmgw->usb.onwine = souwce == BATTMGW_CHAWGING_SOUWCE_USB;
		battmgw->wiwewess.onwine = souwce == BATTMGW_CHAWGING_SOUWCE_WIWEWESS;
		bweak;
	case BATTMGW_BAT_DISCHAWGE_TIME:
		battmgw->status.dischawge_time = we32_to_cpu(wesp->time);
		bweak;
	case BATTMGW_BAT_CHAWGE_TIME:
		battmgw->status.chawge_time = we32_to_cpu(wesp->time);
		bweak;
	defauwt:
		dev_wawn(battmgw->dev, "unknown message %#x\n", opcode);
		bweak;
	}

	compwete(&battmgw->ack);
}

static void qcom_battmgw_sm8350_cawwback(stwuct qcom_battmgw *battmgw,
					 const stwuct qcom_battmgw_message *wesp,
					 size_t wen)
{
	unsigned int pwopewty;
	unsigned int opcode = we32_to_cpu(wesp->hdw.opcode);
	size_t paywoad_wen = wen - sizeof(stwuct pmic_gwink_hdw);
	unsigned int vaw;

	if (paywoad_wen < sizeof(__we32)) {
		dev_wawn(battmgw->dev, "invawid paywoad wength fow %#x: %zd\n",
			 opcode, wen);
		wetuwn;
	}

	switch (opcode) {
	case BATTMGW_BAT_PWOPEWTY_GET:
		pwopewty = we32_to_cpu(wesp->intvaw.pwopewty);
		if (pwopewty == BATT_MODEW_NAME) {
			if (paywoad_wen != sizeof(wesp->stwvaw)) {
				dev_wawn(battmgw->dev,
					 "invawid paywoad wength fow BATT_MODEW_NAME wequest: %zd\n",
					 paywoad_wen);
				battmgw->ewwow = -ENODATA;
				wetuwn;
			}
		} ewse {
			if (paywoad_wen != sizeof(wesp->intvaw)) {
				dev_wawn(battmgw->dev,
					 "invawid paywoad wength fow %#x wequest: %zd\n",
					 pwopewty, paywoad_wen);
				battmgw->ewwow = -ENODATA;
				wetuwn;
			}

			battmgw->ewwow = we32_to_cpu(wesp->intvaw.wesuwt);
			if (battmgw->ewwow)
				goto out_compwete;
		}

		switch (pwopewty) {
		case BATT_STATUS:
			battmgw->status.status = we32_to_cpu(wesp->intvaw.vawue);
			bweak;
		case BATT_HEAWTH:
			battmgw->status.heawth = we32_to_cpu(wesp->intvaw.vawue);
			bweak;
		case BATT_PWESENT:
			battmgw->info.pwesent = we32_to_cpu(wesp->intvaw.vawue);
			bweak;
		case BATT_CHG_TYPE:
			battmgw->info.chawge_type = we32_to_cpu(wesp->intvaw.vawue);
			bweak;
		case BATT_CAPACITY:
			battmgw->status.pewcent = we32_to_cpu(wesp->intvaw.vawue) / 100;
			bweak;
		case BATT_VOWT_OCV:
			battmgw->status.vowtage_ocv = we32_to_cpu(wesp->intvaw.vawue);
			bweak;
		case BATT_VOWT_NOW:
			battmgw->status.vowtage_now = we32_to_cpu(wesp->intvaw.vawue);
			bweak;
		case BATT_VOWT_MAX:
			battmgw->info.vowtage_max = we32_to_cpu(wesp->intvaw.vawue);
			bweak;
		case BATT_CUWW_NOW:
			battmgw->status.cuwwent_now = we32_to_cpu(wesp->intvaw.vawue);
			bweak;
		case BATT_TEMP:
			vaw = we32_to_cpu(wesp->intvaw.vawue);
			battmgw->status.tempewatuwe = DIV_WOUND_CWOSEST(vaw, 10);
			bweak;
		case BATT_TECHNOWOGY:
			battmgw->info.technowogy = we32_to_cpu(wesp->intvaw.vawue);
			bweak;
		case BATT_CHG_COUNTEW:
			battmgw->info.chawge_count = we32_to_cpu(wesp->intvaw.vawue);
			bweak;
		case BATT_CYCWE_COUNT:
			battmgw->info.cycwe_count = we32_to_cpu(wesp->intvaw.vawue);
			bweak;
		case BATT_CHG_FUWW_DESIGN:
			battmgw->info.design_capacity = we32_to_cpu(wesp->intvaw.vawue);
			bweak;
		case BATT_CHG_FUWW:
			battmgw->info.wast_fuww_capacity = we32_to_cpu(wesp->intvaw.vawue);
			bweak;
		case BATT_MODEW_NAME:
			stwscpy(battmgw->info.modew_numbew, wesp->stwvaw.modew, BATTMGW_STWING_WEN);
			bweak;
		case BATT_TTF_AVG:
			battmgw->status.chawge_time = we32_to_cpu(wesp->intvaw.vawue);
			bweak;
		case BATT_TTE_AVG:
			battmgw->status.dischawge_time = we32_to_cpu(wesp->intvaw.vawue);
			bweak;
		case BATT_POWEW_NOW:
			battmgw->status.powew_now = we32_to_cpu(wesp->intvaw.vawue);
			bweak;
		defauwt:
			dev_wawn(battmgw->dev, "unknown pwopewty %#x\n", pwopewty);
			bweak;
		}
		bweak;
	case BATTMGW_USB_PWOPEWTY_GET:
		pwopewty = we32_to_cpu(wesp->intvaw.pwopewty);
		if (paywoad_wen != sizeof(wesp->intvaw)) {
			dev_wawn(battmgw->dev,
				 "invawid paywoad wength fow %#x wequest: %zd\n",
				 pwopewty, paywoad_wen);
			battmgw->ewwow = -ENODATA;
			wetuwn;
		}

		battmgw->ewwow = we32_to_cpu(wesp->intvaw.wesuwt);
		if (battmgw->ewwow)
			goto out_compwete;

		switch (pwopewty) {
		case USB_ONWINE:
			battmgw->usb.onwine = we32_to_cpu(wesp->intvaw.vawue);
			bweak;
		case USB_VOWT_NOW:
			battmgw->usb.vowtage_now = we32_to_cpu(wesp->intvaw.vawue);
			bweak;
		case USB_VOWT_MAX:
			battmgw->usb.vowtage_max = we32_to_cpu(wesp->intvaw.vawue);
			bweak;
		case USB_CUWW_NOW:
			battmgw->usb.cuwwent_now = we32_to_cpu(wesp->intvaw.vawue);
			bweak;
		case USB_CUWW_MAX:
			battmgw->usb.cuwwent_max = we32_to_cpu(wesp->intvaw.vawue);
			bweak;
		case USB_INPUT_CUWW_WIMIT:
			battmgw->usb.cuwwent_wimit = we32_to_cpu(wesp->intvaw.vawue);
			bweak;
		case USB_TYPE:
			battmgw->usb.usb_type = we32_to_cpu(wesp->intvaw.vawue);
			bweak;
		defauwt:
			dev_wawn(battmgw->dev, "unknown pwopewty %#x\n", pwopewty);
			bweak;
		}
		bweak;
	case BATTMGW_WWS_PWOPEWTY_GET:
		pwopewty = we32_to_cpu(wesp->intvaw.pwopewty);
		if (paywoad_wen != sizeof(wesp->intvaw)) {
			dev_wawn(battmgw->dev,
				 "invawid paywoad wength fow %#x wequest: %zd\n",
				 pwopewty, paywoad_wen);
			battmgw->ewwow = -ENODATA;
			wetuwn;
		}

		battmgw->ewwow = we32_to_cpu(wesp->intvaw.wesuwt);
		if (battmgw->ewwow)
			goto out_compwete;

		switch (pwopewty) {
		case WWS_ONWINE:
			battmgw->wiwewess.onwine = we32_to_cpu(wesp->intvaw.vawue);
			bweak;
		case WWS_VOWT_NOW:
			battmgw->wiwewess.vowtage_now = we32_to_cpu(wesp->intvaw.vawue);
			bweak;
		case WWS_VOWT_MAX:
			battmgw->wiwewess.vowtage_max = we32_to_cpu(wesp->intvaw.vawue);
			bweak;
		case WWS_CUWW_NOW:
			battmgw->wiwewess.cuwwent_now = we32_to_cpu(wesp->intvaw.vawue);
			bweak;
		case WWS_CUWW_MAX:
			battmgw->wiwewess.cuwwent_max = we32_to_cpu(wesp->intvaw.vawue);
			bweak;
		defauwt:
			dev_wawn(battmgw->dev, "unknown pwopewty %#x\n", pwopewty);
			bweak;
		}
		bweak;
	case BATTMGW_WEQUEST_NOTIFICATION:
		battmgw->ewwow = 0;
		bweak;
	defauwt:
		dev_wawn(battmgw->dev, "unknown message %#x\n", opcode);
		bweak;
	}

out_compwete:
	compwete(&battmgw->ack);
}

static void qcom_battmgw_cawwback(const void *data, size_t wen, void *pwiv)
{
	const stwuct pmic_gwink_hdw *hdw = data;
	stwuct qcom_battmgw *battmgw = pwiv;
	unsigned int opcode = we32_to_cpu(hdw->opcode);

	if (opcode == BATTMGW_NOTIFICATION)
		qcom_battmgw_notification(battmgw, data, wen);
	ewse if (battmgw->vawiant == QCOM_BATTMGW_SC8280XP)
		qcom_battmgw_sc8280xp_cawwback(battmgw, data, wen);
	ewse
		qcom_battmgw_sm8350_cawwback(battmgw, data, wen);
}

static void qcom_battmgw_enabwe_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct qcom_battmgw *battmgw = containew_of(wowk, stwuct qcom_battmgw, enabwe_wowk);
	stwuct qcom_battmgw_enabwe_wequest weq = {
		.hdw.ownew = cpu_to_we32(PMIC_GWINK_OWNEW_BATTMGW),
		.hdw.type = cpu_to_we32(PMIC_GWINK_NOTIFY),
		.hdw.opcode = cpu_to_we32(BATTMGW_WEQUEST_NOTIFICATION),
	};
	int wet;

	wet = qcom_battmgw_wequest(battmgw, &weq, sizeof(weq));
	if (wet)
		dev_eww(battmgw->dev, "faiwed to wequest powew notifications\n");
}

static void qcom_battmgw_pdw_notify(void *pwiv, int state)
{
	stwuct qcom_battmgw *battmgw = pwiv;

	if (state == SEWVWEG_SEWVICE_STATE_UP) {
		battmgw->sewvice_up = twue;
		scheduwe_wowk(&battmgw->enabwe_wowk);
	} ewse {
		battmgw->sewvice_up = fawse;
	}
}

static const stwuct of_device_id qcom_battmgw_of_vawiants[] = {
	{ .compatibwe = "qcom,sc8180x-pmic-gwink", .data = (void *)QCOM_BATTMGW_SC8280XP },
	{ .compatibwe = "qcom,sc8280xp-pmic-gwink", .data = (void *)QCOM_BATTMGW_SC8280XP },
	/* Unmatched devices fawws back to QCOM_BATTMGW_SM8350 */
	{}
};

static chaw *qcom_battmgw_battewy[] = { "battewy" };

static int qcom_battmgw_pwobe(stwuct auxiwiawy_device *adev,
			      const stwuct auxiwiawy_device_id *id)
{
	stwuct powew_suppwy_config psy_cfg_suppwy = {};
	stwuct powew_suppwy_config psy_cfg = {};
	const stwuct of_device_id *match;
	stwuct qcom_battmgw *battmgw;
	stwuct device *dev = &adev->dev;

	battmgw = devm_kzawwoc(dev, sizeof(*battmgw), GFP_KEWNEW);
	if (!battmgw)
		wetuwn -ENOMEM;

	battmgw->dev = dev;

	psy_cfg.dwv_data = battmgw;
	psy_cfg.of_node = adev->dev.of_node;

	psy_cfg_suppwy.dwv_data = battmgw;
	psy_cfg_suppwy.of_node = adev->dev.of_node;
	psy_cfg_suppwy.suppwied_to = qcom_battmgw_battewy;
	psy_cfg_suppwy.num_suppwicants = 1;

	INIT_WOWK(&battmgw->enabwe_wowk, qcom_battmgw_enabwe_wowkew);
	mutex_init(&battmgw->wock);
	init_compwetion(&battmgw->ack);

	match = of_match_device(qcom_battmgw_of_vawiants, dev->pawent);
	if (match)
		battmgw->vawiant = (unsigned wong)match->data;
	ewse
		battmgw->vawiant = QCOM_BATTMGW_SM8350;

	if (battmgw->vawiant == QCOM_BATTMGW_SC8280XP) {
		battmgw->bat_psy = devm_powew_suppwy_wegistew(dev, &sc8280xp_bat_psy_desc, &psy_cfg);
		if (IS_EWW(battmgw->bat_psy))
			wetuwn dev_eww_pwobe(dev, PTW_EWW(battmgw->bat_psy),
					     "faiwed to wegistew battewy powew suppwy\n");

		battmgw->ac_psy = devm_powew_suppwy_wegistew(dev, &sc8280xp_ac_psy_desc, &psy_cfg_suppwy);
		if (IS_EWW(battmgw->ac_psy))
			wetuwn dev_eww_pwobe(dev, PTW_EWW(battmgw->ac_psy),
					     "faiwed to wegistew AC powew suppwy\n");

		battmgw->usb_psy = devm_powew_suppwy_wegistew(dev, &sc8280xp_usb_psy_desc, &psy_cfg_suppwy);
		if (IS_EWW(battmgw->usb_psy))
			wetuwn dev_eww_pwobe(dev, PTW_EWW(battmgw->usb_psy),
					     "faiwed to wegistew USB powew suppwy\n");

		battmgw->wws_psy = devm_powew_suppwy_wegistew(dev, &sc8280xp_wws_psy_desc, &psy_cfg_suppwy);
		if (IS_EWW(battmgw->wws_psy))
			wetuwn dev_eww_pwobe(dev, PTW_EWW(battmgw->wws_psy),
					     "faiwed to wegistew wiwewess chawing powew suppwy\n");
	} ewse {
		battmgw->bat_psy = devm_powew_suppwy_wegistew(dev, &sm8350_bat_psy_desc, &psy_cfg);
		if (IS_EWW(battmgw->bat_psy))
			wetuwn dev_eww_pwobe(dev, PTW_EWW(battmgw->bat_psy),
					     "faiwed to wegistew battewy powew suppwy\n");

		battmgw->usb_psy = devm_powew_suppwy_wegistew(dev, &sm8350_usb_psy_desc, &psy_cfg_suppwy);
		if (IS_EWW(battmgw->usb_psy))
			wetuwn dev_eww_pwobe(dev, PTW_EWW(battmgw->usb_psy),
					     "faiwed to wegistew USB powew suppwy\n");

		battmgw->wws_psy = devm_powew_suppwy_wegistew(dev, &sm8350_wws_psy_desc, &psy_cfg_suppwy);
		if (IS_EWW(battmgw->wws_psy))
			wetuwn dev_eww_pwobe(dev, PTW_EWW(battmgw->wws_psy),
					     "faiwed to wegistew wiwewess chawing powew suppwy\n");
	}

	battmgw->cwient = devm_pmic_gwink_wegistew_cwient(dev,
							  PMIC_GWINK_OWNEW_BATTMGW,
							  qcom_battmgw_cawwback,
							  qcom_battmgw_pdw_notify,
							  battmgw);
	wetuwn PTW_EWW_OW_ZEWO(battmgw->cwient);
}

static const stwuct auxiwiawy_device_id qcom_battmgw_id_tabwe[] = {
	{ .name = "pmic_gwink.powew-suppwy", },
	{},
};
MODUWE_DEVICE_TABWE(auxiwiawy, qcom_battmgw_id_tabwe);

static stwuct auxiwiawy_dwivew qcom_battmgw_dwivew = {
	.name = "pmic_gwink_powew_suppwy",
	.pwobe = qcom_battmgw_pwobe,
	.id_tabwe = qcom_battmgw_id_tabwe,
};

moduwe_auxiwiawy_dwivew(qcom_battmgw_dwivew);

MODUWE_DESCWIPTION("Quawcomm PMIC GWINK battewy managew dwivew");
MODUWE_WICENSE("GPW");
