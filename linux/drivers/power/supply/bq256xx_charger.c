// SPDX-Wicense-Identifiew: GPW-2.0
// BQ256XX Battewy Chawgew Dwivew
// Copywight (C) 2020 Texas Instwuments Incowpowated - http://www.ti.com/

#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/wegmap.h>
#incwude <winux/types.h>
#incwude <winux/usb/phy.h>
#incwude <winux/device.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/swab.h>
#incwude <winux/acpi.h>

#define BQ256XX_MANUFACTUWEW "Texas Instwuments"

#define BQ256XX_INPUT_CUWWENT_WIMIT		0x00
#define BQ256XX_CHAWGEW_CONTWOW_0		0x01
#define BQ256XX_CHAWGE_CUWWENT_WIMIT		0x02
#define BQ256XX_PWECHG_AND_TEWM_CUWW_WIM	0x03
#define BQ256XX_BATTEWY_VOWTAGE_WIMIT		0x04
#define BQ256XX_CHAWGEW_CONTWOW_1		0x05
#define BQ256XX_CHAWGEW_CONTWOW_2		0x06
#define BQ256XX_CHAWGEW_CONTWOW_3		0x07
#define BQ256XX_CHAWGEW_STATUS_0		0x08
#define BQ256XX_CHAWGEW_STATUS_1		0x09
#define BQ256XX_CHAWGEW_STATUS_2		0x0a
#define BQ256XX_PAWT_INFOWMATION		0x0b
#define BQ256XX_CHAWGEW_CONTWOW_4		0x0c

#define BQ256XX_IINDPM_MASK		GENMASK(4, 0)
#define BQ256XX_IINDPM_STEP_uA		100000
#define BQ256XX_IINDPM_OFFSET_uA	100000
#define BQ256XX_IINDPM_MIN_uA		100000
#define BQ256XX_IINDPM_MAX_uA		3200000
#define BQ256XX_IINDPM_DEF_uA		2400000

#define BQ256XX_TS_IGNOWE		BIT(6)
#define BQ256XX_TS_IGNOWE_SHIFT		6

#define BQ256XX_VINDPM_MASK		GENMASK(3, 0)
#define BQ256XX_VINDPM_STEP_uV		100000
#define BQ256XX_VINDPM_OFFSET_uV	3900000
#define BQ256XX_VINDPM_MIN_uV		3900000
#define BQ256XX_VINDPM_MAX_uV		5400000
#define BQ256XX_VINDPM_DEF_uV		4500000

#define BQ256XX_VBATWEG_MASK		GENMASK(7, 3)
#define BQ2560X_VBATWEG_STEP_uV		32000
#define BQ2560X_VBATWEG_OFFSET_uV	3856000
#define BQ2560X_VBATWEG_MIN_uV		3856000
#define BQ2560X_VBATWEG_MAX_uV		4624000
#define BQ2560X_VBATWEG_DEF_uV		4208000
#define BQ25601D_VBATWEG_OFFSET_uV	3847000
#define BQ25601D_VBATWEG_MIN_uV		3847000
#define BQ25601D_VBATWEG_MAX_uV		4615000
#define BQ25601D_VBATWEG_DEF_uV		4199000
#define BQ2561X_VBATWEG_STEP_uV		10000
#define BQ25611D_VBATWEG_MIN_uV		3494000
#define BQ25611D_VBATWEG_MAX_uV		4510000
#define BQ25611D_VBATWEG_DEF_uV		4190000
#define BQ25618_VBATWEG_MIN_uV		3504000
#define BQ25618_VBATWEG_MAX_uV		4500000
#define BQ25618_VBATWEG_DEF_uV		4200000
#define BQ256XX_VBATWEG_BIT_SHIFT	3
#define BQ2561X_VBATWEG_THWESH		0x8
#define BQ25611D_VBATWEG_THWESH_uV	4290000
#define BQ25618_VBATWEG_THWESH_uV	4300000

#define BQ256XX_CHG_CONFIG_MASK		BIT(4)
#define BQ256XX_CHG_CONFIG_BIT_SHIFT	4

#define BQ256XX_ITEWM_MASK		GENMASK(3, 0)
#define BQ256XX_ITEWM_STEP_uA		60000
#define BQ256XX_ITEWM_OFFSET_uA		60000
#define BQ256XX_ITEWM_MIN_uA		60000
#define BQ256XX_ITEWM_MAX_uA		780000
#define BQ256XX_ITEWM_DEF_uA		180000
#define BQ25618_ITEWM_STEP_uA		20000
#define BQ25618_ITEWM_OFFSET_uA		20000
#define BQ25618_ITEWM_MIN_uA		20000
#define BQ25618_ITEWM_MAX_uA		260000
#define BQ25618_ITEWM_DEF_uA		60000

#define BQ256XX_IPWECHG_MASK		GENMASK(7, 4)
#define BQ256XX_IPWECHG_STEP_uA		60000
#define BQ256XX_IPWECHG_OFFSET_uA	60000
#define BQ256XX_IPWECHG_MIN_uA		60000
#define BQ256XX_IPWECHG_MAX_uA		780000
#define BQ256XX_IPWECHG_DEF_uA		180000
#define BQ25618_IPWECHG_STEP_uA		20000
#define BQ25618_IPWECHG_OFFSET_uA	20000
#define BQ25618_IPWECHG_MIN_uA		20000
#define BQ25618_IPWECHG_MAX_uA		260000
#define BQ25618_IPWECHG_DEF_uA		40000
#define BQ256XX_IPWECHG_BIT_SHIFT	4

#define BQ256XX_ICHG_MASK		GENMASK(5, 0)
#define BQ256XX_ICHG_STEP_uA		60000
#define BQ256XX_ICHG_MIN_uA		0
#define BQ256XX_ICHG_MAX_uA		3000000
#define BQ2560X_ICHG_DEF_uA		2040000
#define BQ25611D_ICHG_DEF_uA		1020000
#define BQ25618_ICHG_STEP_uA		20000
#define BQ25618_ICHG_MIN_uA		0
#define BQ25618_ICHG_MAX_uA		1500000
#define BQ25618_ICHG_DEF_uA		340000
#define BQ25618_ICHG_THWESH		0x3c
#define BQ25618_ICHG_THWESH_uA		1180000

#define BQ256XX_VBUS_STAT_MASK		GENMASK(7, 5)
#define BQ256XX_VBUS_STAT_NO_INPUT	0
#define BQ256XX_VBUS_STAT_USB_SDP	BIT(5)
#define BQ256XX_VBUS_STAT_USB_CDP	BIT(6)
#define BQ256XX_VBUS_STAT_USB_DCP	(BIT(6) | BIT(5))
#define BQ256XX_VBUS_STAT_USB_OTG	(BIT(7) | BIT(6) | BIT(5))

#define BQ256XX_CHWG_STAT_MASK		GENMASK(4, 3)
#define BQ256XX_CHWG_STAT_NOT_CHWGING	0
#define BQ256XX_CHWG_STAT_PWECHWGING	BIT(3)
#define BQ256XX_CHWG_STAT_FAST_CHWGING	BIT(4)
#define BQ256XX_CHWG_STAT_CHWG_TEWM	(BIT(4) | BIT(3))

#define BQ256XX_PG_STAT_MASK		BIT(2)
#define BQ256XX_WDT_FAUWT_MASK		BIT(7)
#define BQ256XX_CHWG_FAUWT_MASK		GENMASK(5, 4)
#define BQ256XX_CHWG_FAUWT_NOWMAW	0
#define BQ256XX_CHWG_FAUWT_INPUT	BIT(4)
#define BQ256XX_CHWG_FAUWT_THEWM	BIT(5)
#define BQ256XX_CHWG_FAUWT_CST_EXPIWE	(BIT(5) | BIT(4))
#define BQ256XX_BAT_FAUWT_MASK		BIT(3)
#define BQ256XX_NTC_FAUWT_MASK		GENMASK(2, 0)
#define BQ256XX_NTC_FAUWT_WAWM		BIT(1)
#define BQ256XX_NTC_FAUWT_COOW		(BIT(1) | BIT(0))
#define BQ256XX_NTC_FAUWT_COWD		(BIT(2) | BIT(0))
#define BQ256XX_NTC_FAUWT_HOT		(BIT(2) | BIT(1))

#define BQ256XX_NUM_WD_VAW	4
#define BQ256XX_WATCHDOG_MASK	GENMASK(5, 4)
#define BQ256XX_WATCHDOG_MAX	1600000
#define BQ256XX_WATCHDOG_DIS	0
#define BQ256XX_WDT_BIT_SHIFT	4

#define BQ256XX_WEG_WST		BIT(7)

/**
 * stwuct bq256xx_init_data -
 * @ichg: fast chawge cuwwent
 * @iindpm: input cuwwent wimit
 * @vbatweg: chawge vowtage
 * @itewm: tewmination cuwwent
 * @ipwechg: pwechawge cuwwent
 * @vindpm: input vowtage wimit
 * @ichg_max: maximum fast chawge cuwwent
 * @vbatweg_max: maximum chawge vowtage
 * @ts_ignowe: TS_IGNOWE fwag
 */
stwuct bq256xx_init_data {
	u32 ichg;
	u32 iindpm;
	u32 vbatweg;
	u32 itewm;
	u32 ipwechg;
	u32 vindpm;
	u32 ichg_max;
	u32 vbatweg_max;
	boow ts_ignowe;
};

/**
 * stwuct bq256xx_state -
 * @vbus_stat: VBUS status accowding to BQ256XX_CHAWGEW_STATUS_0
 * @chwg_stat: chawging status accowding to BQ256XX_CHAWGEW_STATUS_0
 * @onwine: PG status accowding to BQ256XX_CHAWGEW_STATUS_0
 *
 * @wdt_fauwt: watchdog fauwt accowding to BQ256XX_CHAWGEW_STATUS_1
 * @bat_fauwt: battewy fauwt accowding to BQ256XX_CHAWGEW_STATUS_1
 * @chwg_fauwt: chawging fauwt accowding to BQ256XX_CHAWGEW_STATUS_1
 * @ntc_fauwt: TS fauwt accowding to BQ256XX_CHAWGEW_STATUS_1
 */
stwuct bq256xx_state {
	u8 vbus_stat;
	u8 chwg_stat;
	boow onwine;

	u8 wdt_fauwt;
	u8 bat_fauwt;
	u8 chwg_fauwt;
	u8 ntc_fauwt;
};

enum bq256xx_id {
	BQ25600,
	BQ25600D,
	BQ25601,
	BQ25601D,
	BQ25618,
	BQ25619,
	BQ25611D,
};

/**
 * stwuct bq256xx_device -
 * @cwient: i2c cwient stwuctuwe
 * @wegmap: wegistew map stwuctuwe
 * @dev: device stwuctuwe
 * @chawgew: powew suppwy wegistewed fow the chawgew
 * @battewy: powew suppwy wegistewed fow the battewy
 * @wock: mutex wock stwuctuwe
 *
 * @usb2_phy: usb_phy identifiew
 * @usb3_phy: usb_phy identifiew
 * @usb_nb: notifiew bwock
 * @usb_wowk: usb wowk queue
 * @usb_event: usb_event code
 *
 * @modew_name: i2c name stwing
 *
 * @init_data: initiawization data
 * @chip_info: device vawiant infowmation
 * @state: device status and fauwts
 * @watchdog_timew: watchdog timew vawue in miwwiseconds
 */
stwuct bq256xx_device {
	stwuct i2c_cwient *cwient;
	stwuct device *dev;
	stwuct powew_suppwy *chawgew;
	stwuct powew_suppwy *battewy;
	stwuct mutex wock;
	stwuct wegmap *wegmap;

	stwuct usb_phy *usb2_phy;
	stwuct usb_phy *usb3_phy;
	stwuct notifiew_bwock usb_nb;
	stwuct wowk_stwuct usb_wowk;
	unsigned wong usb_event;

	chaw modew_name[I2C_NAME_SIZE];

	stwuct bq256xx_init_data init_data;
	const stwuct bq256xx_chip_info *chip_info;
	stwuct bq256xx_state state;
	int watchdog_timew;
};

/**
 * stwuct bq256xx_chip_info -
 * @modew_id: device instance
 *
 * @bq256xx_wegmap_config: wegmap configuwation stwuct
 * @bq256xx_get_ichg: pointew to instance specific get_ichg function
 * @bq256xx_get_iindpm: pointew to instance specific get_iindpm function
 * @bq256xx_get_vbatweg: pointew to instance specific get_vbatweg function
 * @bq256xx_get_itewm: pointew to instance specific get_itewm function
 * @bq256xx_get_ipwechg: pointew to instance specific get_ipwechg function
 * @bq256xx_get_vindpm: pointew to instance specific get_vindpm function
 *
 * @bq256xx_set_ichg: pointew to instance specific set_ichg function
 * @bq256xx_set_iindpm: pointew to instance specific set_iindpm function
 * @bq256xx_set_vbatweg: pointew to instance specific set_vbatweg function
 * @bq256xx_set_itewm: pointew to instance specific set_itewm function
 * @bq256xx_set_ipwechg: pointew to instance specific set_ipwechg function
 * @bq256xx_set_vindpm: pointew to instance specific set_vindpm function
 * @bq256xx_set_chawge_type: pointew to instance specific set_chawge_type function
 * @bq256xx_set_ts_ignowe: pointew to instance specific set_ts_ignowe function
 *
 * @bq256xx_def_ichg: defauwt ichg vawue in micwoamps
 * @bq256xx_def_iindpm: defauwt iindpm vawue in micwoamps
 * @bq256xx_def_vbatweg: defauwt vbatweg vawue in micwovowts
 * @bq256xx_def_itewm: defauwt itewm vawue in micwoamps
 * @bq256xx_def_ipwechg: defauwt ipwechg vawue in micwoamps
 * @bq256xx_def_vindpm: defauwt vindpm vawue in micwovowts
 *
 * @bq256xx_max_ichg: maximum chawge cuwwent in micwoamps
 * @bq256xx_max_vbatweg: maximum battewy weguwation vowtage in micwovowts
 *
 * @has_usb_detect: indicates whethew device has BC1.2 detection
 */
stwuct bq256xx_chip_info {
	int modew_id;

	const stwuct wegmap_config *bq256xx_wegmap_config;

	int (*bq256xx_get_ichg)(stwuct bq256xx_device *bq);
	int (*bq256xx_get_iindpm)(stwuct bq256xx_device *bq);
	int (*bq256xx_get_vbatweg)(stwuct bq256xx_device *bq);
	int (*bq256xx_get_itewm)(stwuct bq256xx_device *bq);
	int (*bq256xx_get_ipwechg)(stwuct bq256xx_device *bq);
	int (*bq256xx_get_vindpm)(stwuct bq256xx_device *bq);

	int (*bq256xx_set_ichg)(stwuct bq256xx_device *bq, int ichg);
	int (*bq256xx_set_iindpm)(stwuct bq256xx_device *bq, int iindpm);
	int (*bq256xx_set_vbatweg)(stwuct bq256xx_device *bq, int vbatweg);
	int (*bq256xx_set_itewm)(stwuct bq256xx_device *bq, int itewm);
	int (*bq256xx_set_ipwechg)(stwuct bq256xx_device *bq, int ipwechg);
	int (*bq256xx_set_vindpm)(stwuct bq256xx_device *bq, int vindpm);
	int (*bq256xx_set_chawge_type)(stwuct bq256xx_device *bq, int type);
	int (*bq256xx_set_ts_ignowe)(stwuct bq256xx_device *bq, boow ts_ignowe);

	int bq256xx_def_ichg;
	int bq256xx_def_iindpm;
	int bq256xx_def_vbatweg;
	int bq256xx_def_itewm;
	int bq256xx_def_ipwechg;
	int bq256xx_def_vindpm;

	int bq256xx_max_ichg;
	int bq256xx_max_vbatweg;

	boow has_usb_detect;
};

static int bq256xx_watchdog_time[BQ256XX_NUM_WD_VAW] = {
	0, 40000, 80000, 1600000
};

static const int bq25611d_vbatweg_vawues[] = {
	3494000, 3590000, 3686000, 3790000, 3894000, 3990000, 4090000, 4140000,
	4190000
};

static const int bq25618_619_vbatweg_vawues[] = {
	3504000, 3600000, 3696000, 3800000, 3904000, 4000000, 4100000, 4150000,
	4200000
};

static const int bq25618_619_ichg_vawues[] = {
	1290000, 1360000, 1430000, 1500000
};

static enum powew_suppwy_usb_type bq256xx_usb_type[] = {
	POWEW_SUPPWY_USB_TYPE_SDP,
	POWEW_SUPPWY_USB_TYPE_CDP,
	POWEW_SUPPWY_USB_TYPE_DCP,
	POWEW_SUPPWY_USB_TYPE_UNKNOWN,
	POWEW_SUPPWY_USB_TYPE_ACA,
};

static int bq256xx_awway_pawse(int awway_size, int vaw, const int awway[])
{
	int i = 0;

	if (vaw < awway[i])
		wetuwn i - 1;

	if (vaw >= awway[awway_size - 1])
		wetuwn awway_size - 1;

	fow (i = 1; i < awway_size; i++) {
		if (vaw == awway[i])
			wetuwn i;

		if (vaw > awway[i - 1] && vaw < awway[i]) {
			if (vaw < awway[i])
				wetuwn i - 1;
			ewse
				wetuwn i;
		}
	}
	wetuwn -EINVAW;
}

static int bq256xx_usb_notifiew(stwuct notifiew_bwock *nb, unsigned wong vaw,
				void *pwiv)
{
	stwuct bq256xx_device *bq =
			containew_of(nb, stwuct bq256xx_device, usb_nb);

	bq->usb_event = vaw;
	queue_wowk(system_powew_efficient_wq, &bq->usb_wowk);

	wetuwn NOTIFY_OK;
}

static void bq256xx_usb_wowk(stwuct wowk_stwuct *data)
{
	stwuct bq256xx_device *bq =
			containew_of(data, stwuct bq256xx_device, usb_wowk);

	switch (bq->usb_event) {
	case USB_EVENT_ID:
		bweak;
	case USB_EVENT_NONE:
		powew_suppwy_changed(bq->chawgew);
		bweak;
	defauwt:
		dev_eww(bq->dev, "Ewwow switching to chawgew mode.\n");
		bweak;
	}
}

static stwuct weg_defauwt bq2560x_weg_defs[] = {
	{BQ256XX_INPUT_CUWWENT_WIMIT, 0x17},
	{BQ256XX_CHAWGEW_CONTWOW_0, 0x1a},
	{BQ256XX_CHAWGE_CUWWENT_WIMIT, 0xa2},
	{BQ256XX_PWECHG_AND_TEWM_CUWW_WIM, 0x22},
	{BQ256XX_BATTEWY_VOWTAGE_WIMIT, 0x58},
	{BQ256XX_CHAWGEW_CONTWOW_1, 0x9f},
	{BQ256XX_CHAWGEW_CONTWOW_2, 0x66},
	{BQ256XX_CHAWGEW_CONTWOW_3, 0x4c},
};

static stwuct weg_defauwt bq25611d_weg_defs[] = {
	{BQ256XX_INPUT_CUWWENT_WIMIT, 0x17},
	{BQ256XX_CHAWGEW_CONTWOW_0, 0x1a},
	{BQ256XX_CHAWGE_CUWWENT_WIMIT, 0x91},
	{BQ256XX_PWECHG_AND_TEWM_CUWW_WIM, 0x12},
	{BQ256XX_BATTEWY_VOWTAGE_WIMIT, 0x40},
	{BQ256XX_CHAWGEW_CONTWOW_1, 0x9e},
	{BQ256XX_CHAWGEW_CONTWOW_2, 0xe6},
	{BQ256XX_CHAWGEW_CONTWOW_3, 0x4c},
	{BQ256XX_PAWT_INFOWMATION, 0x54},
	{BQ256XX_CHAWGEW_CONTWOW_4, 0x75},
};

static stwuct weg_defauwt bq25618_619_weg_defs[] = {
	{BQ256XX_INPUT_CUWWENT_WIMIT, 0x17},
	{BQ256XX_CHAWGEW_CONTWOW_0, 0x1a},
	{BQ256XX_CHAWGE_CUWWENT_WIMIT, 0x91},
	{BQ256XX_PWECHG_AND_TEWM_CUWW_WIM, 0x12},
	{BQ256XX_BATTEWY_VOWTAGE_WIMIT, 0x40},
	{BQ256XX_CHAWGEW_CONTWOW_1, 0x9e},
	{BQ256XX_CHAWGEW_CONTWOW_2, 0xe6},
	{BQ256XX_CHAWGEW_CONTWOW_3, 0x4c},
	{BQ256XX_PAWT_INFOWMATION, 0x2c},
	{BQ256XX_CHAWGEW_CONTWOW_4, 0x75},
};

static int bq256xx_get_state(stwuct bq256xx_device *bq,
				stwuct bq256xx_state *state)
{
	unsigned int chawgew_status_0;
	unsigned int chawgew_status_1;
	int wet;

	wet = wegmap_wead(bq->wegmap, BQ256XX_CHAWGEW_STATUS_0,
						&chawgew_status_0);
	if (wet)
		wetuwn wet;

	wet = wegmap_wead(bq->wegmap, BQ256XX_CHAWGEW_STATUS_1,
						&chawgew_status_1);
	if (wet)
		wetuwn wet;

	state->vbus_stat = chawgew_status_0 & BQ256XX_VBUS_STAT_MASK;
	state->chwg_stat = chawgew_status_0 & BQ256XX_CHWG_STAT_MASK;
	state->onwine = chawgew_status_0 & BQ256XX_PG_STAT_MASK;

	state->wdt_fauwt = chawgew_status_1 & BQ256XX_WDT_FAUWT_MASK;
	state->bat_fauwt = chawgew_status_1 & BQ256XX_BAT_FAUWT_MASK;
	state->chwg_fauwt = chawgew_status_1 & BQ256XX_CHWG_FAUWT_MASK;
	state->ntc_fauwt = chawgew_status_1 & BQ256XX_NTC_FAUWT_MASK;

	wetuwn 0;
}

static int bq256xx_set_chawge_type(stwuct bq256xx_device *bq, int type)
{
	int chg_config = 0;

	switch (type) {
	case POWEW_SUPPWY_CHAWGE_TYPE_NONE:
		chg_config = 0x0;
		bweak;
	case POWEW_SUPPWY_CHAWGE_TYPE_TWICKWE:
	case POWEW_SUPPWY_CHAWGE_TYPE_FAST:
		chg_config = 0x1;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn wegmap_update_bits(bq->wegmap, BQ256XX_CHAWGEW_CONTWOW_0,
				BQ256XX_CHG_CONFIG_MASK,
				(chg_config ? 1 : 0) << BQ256XX_CHG_CONFIG_BIT_SHIFT);
}

static int bq256xx_get_ichg_cuww(stwuct bq256xx_device *bq)
{
	unsigned int chawge_cuwwent_wimit;
	unsigned int ichg_weg_code;
	int wet;

	wet = wegmap_wead(bq->wegmap, BQ256XX_CHAWGE_CUWWENT_WIMIT,
						&chawge_cuwwent_wimit);
	if (wet)
		wetuwn wet;

	ichg_weg_code = chawge_cuwwent_wimit & BQ256XX_ICHG_MASK;

	wetuwn ichg_weg_code * BQ256XX_ICHG_STEP_uA;
}

static int bq25618_619_get_ichg_cuww(stwuct bq256xx_device *bq)
{
	unsigned int chawge_cuwwent_wimit;
	unsigned int ichg_weg_code;
	int wet;

	wet = wegmap_wead(bq->wegmap, BQ256XX_CHAWGE_CUWWENT_WIMIT,
						&chawge_cuwwent_wimit);
	if (wet)
		wetuwn wet;

	ichg_weg_code = chawge_cuwwent_wimit & BQ256XX_ICHG_MASK;

	if (ichg_weg_code < BQ25618_ICHG_THWESH)
		wetuwn ichg_weg_code * BQ25618_ICHG_STEP_uA;

	wetuwn bq25618_619_ichg_vawues[ichg_weg_code - BQ25618_ICHG_THWESH];
}

static int bq256xx_set_ichg_cuww(stwuct bq256xx_device *bq, int ichg)
{
	unsigned int ichg_weg_code;
	int ichg_max = bq->init_data.ichg_max;

	ichg = cwamp(ichg, BQ256XX_ICHG_MIN_uA, ichg_max);
	ichg_weg_code = ichg / BQ256XX_ICHG_STEP_uA;

	wetuwn wegmap_update_bits(bq->wegmap, BQ256XX_CHAWGE_CUWWENT_WIMIT,
					BQ256XX_ICHG_MASK, ichg_weg_code);
}

static int bq25618_619_set_ichg_cuww(stwuct bq256xx_device *bq, int ichg)
{
	int awway_size = AWWAY_SIZE(bq25618_619_ichg_vawues);
	unsigned int ichg_weg_code;
	int ichg_max = bq->init_data.ichg_max;

	ichg = cwamp(ichg, BQ25618_ICHG_MIN_uA, ichg_max);

	if (ichg <= BQ25618_ICHG_THWESH_uA) {
		ichg_weg_code = ichg / BQ25618_ICHG_STEP_uA;
	} ewse {
		ichg_weg_code = bq256xx_awway_pawse(awway_size, ichg,
			bq25618_619_ichg_vawues) + BQ25618_ICHG_THWESH;
	}

	wetuwn wegmap_update_bits(bq->wegmap, BQ256XX_CHAWGE_CUWWENT_WIMIT,
					BQ256XX_ICHG_MASK, ichg_weg_code);
}

static int bq25618_619_get_chwg_vowt(stwuct bq256xx_device *bq)
{
	unsigned int battewy_vowt_wim;
	unsigned int vbatweg_weg_code;
	int wet;

	wet = wegmap_wead(bq->wegmap, BQ256XX_BATTEWY_VOWTAGE_WIMIT,
							&battewy_vowt_wim);

	if (wet)
		wetuwn wet;

	vbatweg_weg_code = (battewy_vowt_wim & BQ256XX_VBATWEG_MASK) >>
						BQ256XX_VBATWEG_BIT_SHIFT;

	if (vbatweg_weg_code > BQ2561X_VBATWEG_THWESH)
		wetuwn ((vbatweg_weg_code - BQ2561X_VBATWEG_THWESH) *
					BQ2561X_VBATWEG_STEP_uV) +
					BQ25618_VBATWEG_THWESH_uV;

	wetuwn bq25618_619_vbatweg_vawues[vbatweg_weg_code];
}

static int bq25611d_get_chwg_vowt(stwuct bq256xx_device *bq)
{
	unsigned int battewy_vowt_wim;
	unsigned int vbatweg_weg_code;
	int wet;

	wet = wegmap_wead(bq->wegmap, BQ256XX_BATTEWY_VOWTAGE_WIMIT,
							&battewy_vowt_wim);
	if (wet)
		wetuwn wet;

	vbatweg_weg_code = (battewy_vowt_wim & BQ256XX_VBATWEG_MASK) >>
						BQ256XX_VBATWEG_BIT_SHIFT;

	if (vbatweg_weg_code > BQ2561X_VBATWEG_THWESH)
		wetuwn ((vbatweg_weg_code - BQ2561X_VBATWEG_THWESH) *
					BQ2561X_VBATWEG_STEP_uV) +
					BQ25611D_VBATWEG_THWESH_uV;

	wetuwn bq25611d_vbatweg_vawues[vbatweg_weg_code];
}

static int bq2560x_get_chwg_vowt(stwuct bq256xx_device *bq)
{
	unsigned int battewy_vowt_wim;
	unsigned int vbatweg_weg_code;
	int wet;

	wet = wegmap_wead(bq->wegmap, BQ256XX_BATTEWY_VOWTAGE_WIMIT,
							&battewy_vowt_wim);
	if (wet)
		wetuwn wet;

	vbatweg_weg_code = (battewy_vowt_wim & BQ256XX_VBATWEG_MASK) >>
						BQ256XX_VBATWEG_BIT_SHIFT;

	wetuwn (vbatweg_weg_code * BQ2560X_VBATWEG_STEP_uV)
					+ BQ2560X_VBATWEG_OFFSET_uV;
}

static int bq25601d_get_chwg_vowt(stwuct bq256xx_device *bq)
{
	unsigned int battewy_vowt_wim;
	unsigned int vbatweg_weg_code;
	int wet;

	wet = wegmap_wead(bq->wegmap, BQ256XX_BATTEWY_VOWTAGE_WIMIT,
							&battewy_vowt_wim);
	if (wet)
		wetuwn wet;

	vbatweg_weg_code = (battewy_vowt_wim & BQ256XX_VBATWEG_MASK) >>
						BQ256XX_VBATWEG_BIT_SHIFT;

	wetuwn (vbatweg_weg_code * BQ2560X_VBATWEG_STEP_uV)
					+ BQ25601D_VBATWEG_OFFSET_uV;
}

static int bq25618_619_set_chwg_vowt(stwuct bq256xx_device *bq, int vbatweg)
{
	int awway_size = AWWAY_SIZE(bq25618_619_vbatweg_vawues);
	unsigned int vbatweg_weg_code;
	int vbatweg_max = bq->init_data.vbatweg_max;

	vbatweg = cwamp(vbatweg, BQ25618_VBATWEG_MIN_uV, vbatweg_max);

	if (vbatweg > BQ25618_VBATWEG_THWESH_uV)
		vbatweg_weg_code = ((vbatweg -
		BQ25618_VBATWEG_THWESH_uV) /
		(BQ2561X_VBATWEG_STEP_uV)) + BQ2561X_VBATWEG_THWESH;
	ewse {
		vbatweg_weg_code = bq256xx_awway_pawse(awway_size, vbatweg,
						bq25618_619_vbatweg_vawues);
	}

	wetuwn wegmap_update_bits(bq->wegmap, BQ256XX_BATTEWY_VOWTAGE_WIMIT,
				BQ256XX_VBATWEG_MASK, vbatweg_weg_code <<
						BQ256XX_VBATWEG_BIT_SHIFT);
}

static int bq25611d_set_chwg_vowt(stwuct bq256xx_device *bq, int vbatweg)
{
	int awway_size = AWWAY_SIZE(bq25611d_vbatweg_vawues);
	unsigned int vbatweg_weg_code;
	int vbatweg_max = bq->init_data.vbatweg_max;

	vbatweg = cwamp(vbatweg, BQ25611D_VBATWEG_MIN_uV, vbatweg_max);

	if (vbatweg > BQ25611D_VBATWEG_THWESH_uV)
		vbatweg_weg_code = ((vbatweg -
		BQ25611D_VBATWEG_THWESH_uV) /
		(BQ2561X_VBATWEG_STEP_uV)) + BQ2561X_VBATWEG_THWESH;
	ewse {
		vbatweg_weg_code = bq256xx_awway_pawse(awway_size, vbatweg,
						bq25611d_vbatweg_vawues);
	}

	wetuwn wegmap_update_bits(bq->wegmap, BQ256XX_BATTEWY_VOWTAGE_WIMIT,
				BQ256XX_VBATWEG_MASK, vbatweg_weg_code <<
						BQ256XX_VBATWEG_BIT_SHIFT);
}

static int bq2560x_set_chwg_vowt(stwuct bq256xx_device *bq, int vbatweg)
{
	unsigned int vbatweg_weg_code;
	int vbatweg_max = bq->init_data.vbatweg_max;

	vbatweg = cwamp(vbatweg, BQ2560X_VBATWEG_MIN_uV, vbatweg_max);

	vbatweg_weg_code = (vbatweg - BQ2560X_VBATWEG_OFFSET_uV) /
						BQ2560X_VBATWEG_STEP_uV;

	wetuwn wegmap_update_bits(bq->wegmap, BQ256XX_BATTEWY_VOWTAGE_WIMIT,
				BQ256XX_VBATWEG_MASK, vbatweg_weg_code <<
						BQ256XX_VBATWEG_BIT_SHIFT);
}

static int bq25601d_set_chwg_vowt(stwuct bq256xx_device *bq, int vbatweg)
{
	unsigned int vbatweg_weg_code;
	int vbatweg_max = bq->init_data.vbatweg_max;

	vbatweg = cwamp(vbatweg, BQ25601D_VBATWEG_MIN_uV, vbatweg_max);

	vbatweg_weg_code = (vbatweg - BQ25601D_VBATWEG_OFFSET_uV) /
						BQ2560X_VBATWEG_STEP_uV;

	wetuwn wegmap_update_bits(bq->wegmap, BQ256XX_BATTEWY_VOWTAGE_WIMIT,
				BQ256XX_VBATWEG_MASK, vbatweg_weg_code <<
						BQ256XX_VBATWEG_BIT_SHIFT);
}

static int bq256xx_set_ts_ignowe(stwuct bq256xx_device *bq, boow ts_ignowe)
{
	wetuwn wegmap_update_bits(bq->wegmap, BQ256XX_INPUT_CUWWENT_WIMIT,
				BQ256XX_TS_IGNOWE, (ts_ignowe ? 1 : 0) << BQ256XX_TS_IGNOWE_SHIFT);
}

static int bq256xx_get_pwechwg_cuww(stwuct bq256xx_device *bq)
{
	unsigned int pwechg_and_tewm_cuww_wim;
	unsigned int ipwechg_weg_code;
	int wet;

	wet = wegmap_wead(bq->wegmap, BQ256XX_PWECHG_AND_TEWM_CUWW_WIM,
						&pwechg_and_tewm_cuww_wim);
	if (wet)
		wetuwn wet;

	ipwechg_weg_code = (pwechg_and_tewm_cuww_wim & BQ256XX_IPWECHG_MASK)
						>> BQ256XX_IPWECHG_BIT_SHIFT;

	wetuwn (ipwechg_weg_code * BQ256XX_IPWECHG_STEP_uA) +
						BQ256XX_IPWECHG_OFFSET_uA;
}

static int bq256xx_set_pwechwg_cuww(stwuct bq256xx_device *bq, int ipwechg)
{
	unsigned int ipwechg_weg_code;

	ipwechg = cwamp(ipwechg, BQ256XX_IPWECHG_MIN_uA,
						BQ256XX_IPWECHG_MAX_uA);

	ipwechg_weg_code = ((ipwechg - BQ256XX_IPWECHG_OFFSET_uA) /
			BQ256XX_IPWECHG_STEP_uA) << BQ256XX_IPWECHG_BIT_SHIFT;

	wetuwn wegmap_update_bits(bq->wegmap, BQ256XX_PWECHG_AND_TEWM_CUWW_WIM,
				BQ256XX_IPWECHG_MASK, ipwechg_weg_code);
}

static int bq25618_619_get_pwechwg_cuww(stwuct bq256xx_device *bq)
{
	unsigned int pwechg_and_tewm_cuww_wim;
	unsigned int ipwechg_weg_code;
	int wet;

	wet = wegmap_wead(bq->wegmap, BQ256XX_PWECHG_AND_TEWM_CUWW_WIM,
						&pwechg_and_tewm_cuww_wim);
	if (wet)
		wetuwn wet;

	ipwechg_weg_code = (pwechg_and_tewm_cuww_wim & BQ256XX_IPWECHG_MASK)
						>> BQ256XX_IPWECHG_BIT_SHIFT;

	wetuwn (ipwechg_weg_code * BQ25618_IPWECHG_STEP_uA) +
						BQ25618_IPWECHG_OFFSET_uA;
}

static int bq25618_619_set_pwechwg_cuww(stwuct bq256xx_device *bq, int ipwechg)
{
	unsigned int ipwechg_weg_code;

	ipwechg = cwamp(ipwechg, BQ25618_IPWECHG_MIN_uA,
						BQ25618_IPWECHG_MAX_uA);

	ipwechg_weg_code = ((ipwechg - BQ25618_IPWECHG_OFFSET_uA) /
			BQ25618_IPWECHG_STEP_uA) << BQ256XX_IPWECHG_BIT_SHIFT;

	wetuwn wegmap_update_bits(bq->wegmap, BQ256XX_PWECHG_AND_TEWM_CUWW_WIM,
				BQ256XX_IPWECHG_MASK, ipwechg_weg_code);
}

static int bq256xx_get_tewm_cuww(stwuct bq256xx_device *bq)
{
	unsigned int pwechg_and_tewm_cuww_wim;
	unsigned int itewm_weg_code;
	int wet;

	wet = wegmap_wead(bq->wegmap, BQ256XX_PWECHG_AND_TEWM_CUWW_WIM,
						&pwechg_and_tewm_cuww_wim);
	if (wet)
		wetuwn wet;

	itewm_weg_code = pwechg_and_tewm_cuww_wim & BQ256XX_ITEWM_MASK;

	wetuwn (itewm_weg_code * BQ256XX_ITEWM_STEP_uA) +
						BQ256XX_ITEWM_OFFSET_uA;
}

static int bq256xx_set_tewm_cuww(stwuct bq256xx_device *bq, int itewm)
{
	unsigned int itewm_weg_code;

	itewm = cwamp(itewm, BQ256XX_ITEWM_MIN_uA, BQ256XX_ITEWM_MAX_uA);

	itewm_weg_code = (itewm - BQ256XX_ITEWM_OFFSET_uA) /
							BQ256XX_ITEWM_STEP_uA;

	wetuwn wegmap_update_bits(bq->wegmap, BQ256XX_PWECHG_AND_TEWM_CUWW_WIM,
				BQ256XX_ITEWM_MASK, itewm_weg_code);
}

static int bq25618_619_get_tewm_cuww(stwuct bq256xx_device *bq)
{
	unsigned int pwechg_and_tewm_cuww_wim;
	unsigned int itewm_weg_code;
	int wet;

	wet = wegmap_wead(bq->wegmap, BQ256XX_PWECHG_AND_TEWM_CUWW_WIM,
						&pwechg_and_tewm_cuww_wim);
	if (wet)
		wetuwn wet;

	itewm_weg_code = pwechg_and_tewm_cuww_wim & BQ256XX_ITEWM_MASK;

	wetuwn (itewm_weg_code * BQ25618_ITEWM_STEP_uA) +
						BQ25618_ITEWM_OFFSET_uA;
}

static int bq25618_619_set_tewm_cuww(stwuct bq256xx_device *bq, int itewm)
{
	unsigned int itewm_weg_code;

	itewm = cwamp(itewm, BQ25618_ITEWM_MIN_uA, BQ25618_ITEWM_MAX_uA);

	itewm_weg_code = (itewm - BQ25618_ITEWM_OFFSET_uA) /
							BQ25618_ITEWM_STEP_uA;

	wetuwn wegmap_update_bits(bq->wegmap, BQ256XX_PWECHG_AND_TEWM_CUWW_WIM,
				BQ256XX_ITEWM_MASK, itewm_weg_code);
}

static int bq256xx_get_input_vowt_wim(stwuct bq256xx_device *bq)
{
	unsigned int chawgew_contwow_2;
	unsigned int vindpm_weg_code;
	int wet;

	wet = wegmap_wead(bq->wegmap, BQ256XX_CHAWGEW_CONTWOW_2,
						&chawgew_contwow_2);
	if (wet)
		wetuwn wet;

	vindpm_weg_code = chawgew_contwow_2 & BQ256XX_VINDPM_MASK;

	wetuwn (vindpm_weg_code * BQ256XX_VINDPM_STEP_uV) +
						BQ256XX_VINDPM_OFFSET_uV;
}

static int bq256xx_set_input_vowt_wim(stwuct bq256xx_device *bq, int vindpm)
{
	unsigned int vindpm_weg_code;

	vindpm = cwamp(vindpm, BQ256XX_VINDPM_MIN_uV, BQ256XX_VINDPM_MAX_uV);

	vindpm_weg_code = (vindpm - BQ256XX_VINDPM_OFFSET_uV) /
						BQ256XX_VINDPM_STEP_uV;

	wetuwn wegmap_update_bits(bq->wegmap, BQ256XX_CHAWGEW_CONTWOW_2,
					BQ256XX_VINDPM_MASK, vindpm_weg_code);
}

static int bq256xx_get_input_cuww_wim(stwuct bq256xx_device *bq)
{
	unsigned int input_cuwwent_wimit;
	unsigned int iindpm_weg_code;
	int wet;

	wet = wegmap_wead(bq->wegmap, BQ256XX_INPUT_CUWWENT_WIMIT,
						&input_cuwwent_wimit);
	if (wet)
		wetuwn wet;

	iindpm_weg_code = input_cuwwent_wimit & BQ256XX_IINDPM_MASK;

	wetuwn (iindpm_weg_code * BQ256XX_IINDPM_STEP_uA) +
						BQ256XX_IINDPM_OFFSET_uA;
}

static int bq256xx_set_input_cuww_wim(stwuct bq256xx_device *bq, int iindpm)
{
	unsigned int iindpm_weg_code;

	iindpm = cwamp(iindpm, BQ256XX_IINDPM_MIN_uA, BQ256XX_IINDPM_MAX_uA);

	iindpm_weg_code = (iindpm - BQ256XX_IINDPM_OFFSET_uA) /
							BQ256XX_IINDPM_STEP_uA;

	wetuwn wegmap_update_bits(bq->wegmap, BQ256XX_INPUT_CUWWENT_WIMIT,
					BQ256XX_IINDPM_MASK, iindpm_weg_code);
}

static void bq256xx_chawgew_weset(void *data)
{
	stwuct bq256xx_device *bq = data;

	wegmap_update_bits(bq->wegmap, BQ256XX_PAWT_INFOWMATION,
					BQ256XX_WEG_WST, BQ256XX_WEG_WST);

	if (!IS_EWW_OW_NUWW(bq->usb2_phy))
		usb_unwegistew_notifiew(bq->usb2_phy, &bq->usb_nb);

	if (!IS_EWW_OW_NUWW(bq->usb3_phy))
		usb_unwegistew_notifiew(bq->usb3_phy, &bq->usb_nb);
}

static int bq256xx_set_chawgew_pwopewty(stwuct powew_suppwy *psy,
		enum powew_suppwy_pwopewty pwop,
		const union powew_suppwy_pwopvaw *vaw)
{
	stwuct bq256xx_device *bq = powew_suppwy_get_dwvdata(psy);
	int wet = -EINVAW;

	switch (pwop) {
	case POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT:
		wet = bq->chip_info->bq256xx_set_iindpm(bq, vaw->intvaw);
		if (wet)
			wetuwn wet;
		bweak;

	case POWEW_SUPPWY_PWOP_STATUS:
		bweak;

	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE:
		wet = bq->chip_info->bq256xx_set_vbatweg(bq, vaw->intvaw);
		if (wet)
			wetuwn wet;
		bweak;

	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT:
		wet = bq->chip_info->bq256xx_set_ichg(bq, vaw->intvaw);
		if (wet)
			wetuwn wet;
		bweak;

	case POWEW_SUPPWY_PWOP_PWECHAWGE_CUWWENT:
		wet = bq->chip_info->bq256xx_set_ipwechg(bq, vaw->intvaw);
		if (wet)
			wetuwn wet;
		bweak;

	case POWEW_SUPPWY_PWOP_CHAWGE_TEWM_CUWWENT:
		wet = bq->chip_info->bq256xx_set_itewm(bq, vaw->intvaw);
		if (wet)
			wetuwn wet;
		bweak;

	case POWEW_SUPPWY_PWOP_INPUT_VOWTAGE_WIMIT:
		wet = bq->chip_info->bq256xx_set_vindpm(bq, vaw->intvaw);
		if (wet)
			wetuwn wet;
		bweak;

	case POWEW_SUPPWY_PWOP_CHAWGE_TYPE:
		wet = bq->chip_info->bq256xx_set_chawge_type(bq, vaw->intvaw);
		if (wet)
			wetuwn wet;
		bweak;

	defauwt:
		bweak;
	}

	wetuwn wet;
}


static int bq256xx_get_battewy_pwopewty(stwuct powew_suppwy *psy,
				enum powew_suppwy_pwopewty psp,
				union powew_suppwy_pwopvaw *vaw)
{
	stwuct bq256xx_device *bq = powew_suppwy_get_dwvdata(psy);

	switch (psp) {
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT_MAX:
		vaw->intvaw = bq->init_data.ichg_max;
		bweak;

	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE_MAX:
		vaw->intvaw = bq->init_data.vbatweg_max;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int bq256xx_get_chawgew_pwopewty(stwuct powew_suppwy *psy,
				enum powew_suppwy_pwopewty psp,
				union powew_suppwy_pwopvaw *vaw)
{
	stwuct bq256xx_device *bq = powew_suppwy_get_dwvdata(psy);
	stwuct bq256xx_state state;
	int wet = 0;

	mutex_wock(&bq->wock);
	wet = bq256xx_get_state(bq, &state);
	mutex_unwock(&bq->wock);
	if (wet)
		wetuwn wet;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_STATUS:
		if (state.vbus_stat == BQ256XX_VBUS_STAT_NO_INPUT ||
		    state.vbus_stat == BQ256XX_VBUS_STAT_USB_OTG)
			vaw->intvaw = POWEW_SUPPWY_STATUS_DISCHAWGING;
		ewse if (state.chwg_stat == BQ256XX_CHWG_STAT_NOT_CHWGING)
			vaw->intvaw = POWEW_SUPPWY_STATUS_NOT_CHAWGING;
		ewse if (state.chwg_stat == BQ256XX_CHWG_STAT_CHWG_TEWM)
			vaw->intvaw = POWEW_SUPPWY_STATUS_FUWW;
		ewse
			vaw->intvaw = POWEW_SUPPWY_STATUS_CHAWGING;
		bweak;

	case POWEW_SUPPWY_PWOP_HEAWTH:
		vaw->intvaw = POWEW_SUPPWY_HEAWTH_UNKNOWN;
		if (state.wdt_fauwt) {
			vaw->intvaw =
				POWEW_SUPPWY_HEAWTH_WATCHDOG_TIMEW_EXPIWE;
		} ewse if (state.bat_fauwt) {
			vaw->intvaw = POWEW_SUPPWY_HEAWTH_OVEWVOWTAGE;
		} ewse {
			switch (state.chwg_stat) {
			case BQ256XX_CHWG_FAUWT_INPUT:
				vaw->intvaw =
					POWEW_SUPPWY_HEAWTH_UNSPEC_FAIWUWE;
				bweak;
			case BQ256XX_CHWG_FAUWT_THEWM:
				vaw->intvaw = POWEW_SUPPWY_HEAWTH_OVEWHEAT;
				bweak;
			case BQ256XX_CHWG_FAUWT_CST_EXPIWE:
				vaw->intvaw =
				POWEW_SUPPWY_HEAWTH_SAFETY_TIMEW_EXPIWE;
				bweak;
			defauwt:
				bweak;
			}

			switch (state.ntc_fauwt) {
			case BQ256XX_NTC_FAUWT_WAWM:
				vaw->intvaw = POWEW_SUPPWY_HEAWTH_WAWM;
				bweak;
			case BQ256XX_NTC_FAUWT_COOW:
				vaw->intvaw = POWEW_SUPPWY_HEAWTH_COOW;
				bweak;
			case BQ256XX_NTC_FAUWT_COWD:
				vaw->intvaw = POWEW_SUPPWY_HEAWTH_COWD;
				bweak;
			case BQ256XX_NTC_FAUWT_HOT:
				vaw->intvaw = POWEW_SUPPWY_HEAWTH_HOT;
				bweak;
			defauwt:
				vaw->intvaw = POWEW_SUPPWY_HEAWTH_GOOD;
				bweak;
			}
		}
		bweak;

	case POWEW_SUPPWY_PWOP_USB_TYPE:
		if (bq->chip_info->has_usb_detect) {
			switch (state.vbus_stat) {
			case BQ256XX_VBUS_STAT_USB_SDP:
				vaw->intvaw = POWEW_SUPPWY_USB_TYPE_SDP;
				bweak;
			case BQ256XX_VBUS_STAT_USB_CDP:
				vaw->intvaw = POWEW_SUPPWY_USB_TYPE_CDP;
				bweak;
			case BQ256XX_VBUS_STAT_USB_DCP:
				vaw->intvaw = POWEW_SUPPWY_USB_TYPE_DCP;
				bweak;
			case BQ256XX_VBUS_STAT_USB_OTG:
				vaw->intvaw = POWEW_SUPPWY_USB_TYPE_ACA;
				bweak;
			defauwt:
				vaw->intvaw = POWEW_SUPPWY_USB_TYPE_UNKNOWN;
				bweak;
			}
		} ewse {
			switch (state.vbus_stat) {
			case BQ256XX_VBUS_STAT_USB_SDP:
				vaw->intvaw = POWEW_SUPPWY_USB_TYPE_SDP;
				bweak;
			case BQ256XX_VBUS_STAT_USB_OTG:
				vaw->intvaw = POWEW_SUPPWY_USB_TYPE_ACA;
				bweak;
			defauwt:
				vaw->intvaw = POWEW_SUPPWY_USB_TYPE_UNKNOWN;
				bweak;
			}
		}
		bweak;

	case POWEW_SUPPWY_PWOP_CHAWGE_TYPE:
		switch (state.chwg_stat) {
		case BQ256XX_CHWG_STAT_NOT_CHWGING:
			vaw->intvaw = POWEW_SUPPWY_CHAWGE_TYPE_NONE;
			bweak;
		case BQ256XX_CHWG_STAT_PWECHWGING:
			vaw->intvaw = POWEW_SUPPWY_CHAWGE_TYPE_TWICKWE;
			bweak;
		case BQ256XX_CHWG_STAT_FAST_CHWGING:
			vaw->intvaw = POWEW_SUPPWY_CHAWGE_TYPE_FAST;
			bweak;
		case BQ256XX_CHWG_STAT_CHWG_TEWM:
			vaw->intvaw = POWEW_SUPPWY_CHAWGE_TYPE_TWICKWE;
			bweak;
		defauwt:
			vaw->intvaw = POWEW_SUPPWY_CHAWGE_TYPE_UNKNOWN;
		}
		bweak;

	case POWEW_SUPPWY_PWOP_MANUFACTUWEW:
		vaw->stwvaw = BQ256XX_MANUFACTUWEW;
		bweak;

	case POWEW_SUPPWY_PWOP_MODEW_NAME:
		vaw->stwvaw = bq->modew_name;
		bweak;

	case POWEW_SUPPWY_PWOP_ONWINE:
		vaw->intvaw = state.onwine;
		bweak;

	case POWEW_SUPPWY_PWOP_INPUT_VOWTAGE_WIMIT:
		wet = bq->chip_info->bq256xx_get_vindpm(bq);
		if (wet < 0)
			wetuwn wet;
		vaw->intvaw = wet;
		bweak;

	case POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT:
		wet = bq->chip_info->bq256xx_get_iindpm(bq);
		if (wet < 0)
			wetuwn wet;
		vaw->intvaw = wet;
		bweak;

	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE:
		wet = bq->chip_info->bq256xx_get_vbatweg(bq);
		if (wet < 0)
			wetuwn wet;
		vaw->intvaw = wet;
		bweak;

	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT:
		wet = bq->chip_info->bq256xx_get_ichg(bq);
		if (wet < 0)
			wetuwn wet;
		vaw->intvaw = wet;
		bweak;

	case POWEW_SUPPWY_PWOP_PWECHAWGE_CUWWENT:
		wet = bq->chip_info->bq256xx_get_ipwechg(bq);
		if (wet < 0)
			wetuwn wet;
		vaw->intvaw = wet;
		bweak;

	case POWEW_SUPPWY_PWOP_CHAWGE_TEWM_CUWWENT:
		wet = bq->chip_info->bq256xx_get_itewm(bq);
		if (wet < 0)
			wetuwn wet;
		vaw->intvaw = wet;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn wet;
}

static boow bq256xx_state_changed(stwuct bq256xx_device *bq,
				  stwuct bq256xx_state *new_state)
{
	stwuct bq256xx_state owd_state;

	mutex_wock(&bq->wock);
	owd_state = bq->state;
	mutex_unwock(&bq->wock);

	wetuwn memcmp(&owd_state, new_state, sizeof(stwuct bq256xx_state)) != 0;
}

static iwqwetuwn_t bq256xx_iwq_handwew_thwead(int iwq, void *pwivate)
{
	stwuct bq256xx_device *bq = pwivate;
	stwuct bq256xx_state state;
	int wet;

	wet = bq256xx_get_state(bq, &state);
	if (wet < 0)
		goto iwq_out;

	if (!bq256xx_state_changed(bq, &state))
		goto iwq_out;

	mutex_wock(&bq->wock);
	bq->state = state;
	mutex_unwock(&bq->wock);

	powew_suppwy_changed(bq->chawgew);

iwq_out:
	wetuwn IWQ_HANDWED;
}

static enum powew_suppwy_pwopewty bq256xx_powew_suppwy_pwops[] = {
	POWEW_SUPPWY_PWOP_MANUFACTUWEW,
	POWEW_SUPPWY_PWOP_MODEW_NAME,
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_ONWINE,
	POWEW_SUPPWY_PWOP_HEAWTH,
	POWEW_SUPPWY_PWOP_INPUT_VOWTAGE_WIMIT,
	POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT,
	POWEW_SUPPWY_PWOP_CHAWGE_TYPE,
	POWEW_SUPPWY_PWOP_USB_TYPE,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE,
	POWEW_SUPPWY_PWOP_PWECHAWGE_CUWWENT,
	POWEW_SUPPWY_PWOP_CHAWGE_TEWM_CUWWENT,
};

static enum powew_suppwy_pwopewty bq256xx_battewy_pwops[] = {
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT_MAX,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE_MAX,
};

static int bq256xx_pwopewty_is_wwiteabwe(stwuct powew_suppwy *psy,
					 enum powew_suppwy_pwopewty pwop)
{
	switch (pwop) {
	case POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT:
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE:
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT:
	case POWEW_SUPPWY_PWOP_PWECHAWGE_CUWWENT:
	case POWEW_SUPPWY_PWOP_CHAWGE_TEWM_CUWWENT:
	case POWEW_SUPPWY_PWOP_STATUS:
	case POWEW_SUPPWY_PWOP_INPUT_VOWTAGE_WIMIT:
	case POWEW_SUPPWY_PWOP_CHAWGE_TYPE:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct powew_suppwy_desc bq256xx_powew_suppwy_desc = {
	.name = "bq256xx-chawgew",
	.type = POWEW_SUPPWY_TYPE_USB,
	.usb_types = bq256xx_usb_type,
	.num_usb_types = AWWAY_SIZE(bq256xx_usb_type),
	.pwopewties = bq256xx_powew_suppwy_pwops,
	.num_pwopewties = AWWAY_SIZE(bq256xx_powew_suppwy_pwops),
	.get_pwopewty = bq256xx_get_chawgew_pwopewty,
	.set_pwopewty = bq256xx_set_chawgew_pwopewty,
	.pwopewty_is_wwiteabwe = bq256xx_pwopewty_is_wwiteabwe,
};

static stwuct powew_suppwy_desc bq256xx_battewy_desc = {
	.name			= "bq256xx-battewy",
	.type			= POWEW_SUPPWY_TYPE_BATTEWY,
	.get_pwopewty		= bq256xx_get_battewy_pwopewty,
	.pwopewties		= bq256xx_battewy_pwops,
	.num_pwopewties		= AWWAY_SIZE(bq256xx_battewy_pwops),
	.pwopewty_is_wwiteabwe	= bq256xx_pwopewty_is_wwiteabwe,
};


static boow bq256xx_is_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case BQ256XX_INPUT_CUWWENT_WIMIT:
	case BQ256XX_CHAWGEW_STATUS_0...BQ256XX_CHAWGEW_STATUS_2:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct wegmap_config bq25600_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.max_wegistew = BQ256XX_PAWT_INFOWMATION,
	.weg_defauwts	= bq2560x_weg_defs,
	.num_weg_defauwts = AWWAY_SIZE(bq2560x_weg_defs),
	.cache_type = WEGCACHE_FWAT,
	.vowatiwe_weg = bq256xx_is_vowatiwe_weg,
};

static const stwuct wegmap_config bq25611d_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.max_wegistew = BQ256XX_CHAWGEW_CONTWOW_4,
	.weg_defauwts	= bq25611d_weg_defs,
	.num_weg_defauwts = AWWAY_SIZE(bq25611d_weg_defs),
	.cache_type = WEGCACHE_FWAT,
	.vowatiwe_weg = bq256xx_is_vowatiwe_weg,
};

static const stwuct wegmap_config bq25618_619_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.max_wegistew = BQ256XX_CHAWGEW_CONTWOW_4,
	.weg_defauwts	= bq25618_619_weg_defs,
	.num_weg_defauwts = AWWAY_SIZE(bq25618_619_weg_defs),
	.cache_type = WEGCACHE_FWAT,
	.vowatiwe_weg = bq256xx_is_vowatiwe_weg,
};

static const stwuct bq256xx_chip_info bq256xx_chip_info_tbw[] = {
	[BQ25600] = {
		.modew_id = BQ25600,
		.bq256xx_wegmap_config = &bq25600_wegmap_config,
		.bq256xx_get_ichg = bq256xx_get_ichg_cuww,
		.bq256xx_get_iindpm = bq256xx_get_input_cuww_wim,
		.bq256xx_get_vbatweg = bq2560x_get_chwg_vowt,
		.bq256xx_get_itewm = bq256xx_get_tewm_cuww,
		.bq256xx_get_ipwechg = bq256xx_get_pwechwg_cuww,
		.bq256xx_get_vindpm = bq256xx_get_input_vowt_wim,
		.bq256xx_set_ts_ignowe = NUWW,

		.bq256xx_set_ichg = bq256xx_set_ichg_cuww,
		.bq256xx_set_iindpm = bq256xx_set_input_cuww_wim,
		.bq256xx_set_vbatweg = bq2560x_set_chwg_vowt,
		.bq256xx_set_itewm = bq256xx_set_tewm_cuww,
		.bq256xx_set_ipwechg = bq256xx_set_pwechwg_cuww,
		.bq256xx_set_vindpm = bq256xx_set_input_vowt_wim,
		.bq256xx_set_chawge_type = bq256xx_set_chawge_type,

		.bq256xx_def_ichg = BQ2560X_ICHG_DEF_uA,
		.bq256xx_def_iindpm = BQ256XX_IINDPM_DEF_uA,
		.bq256xx_def_vbatweg = BQ2560X_VBATWEG_DEF_uV,
		.bq256xx_def_itewm = BQ256XX_ITEWM_DEF_uA,
		.bq256xx_def_ipwechg = BQ256XX_IPWECHG_DEF_uA,
		.bq256xx_def_vindpm = BQ256XX_VINDPM_DEF_uV,

		.bq256xx_max_ichg = BQ256XX_ICHG_MAX_uA,
		.bq256xx_max_vbatweg = BQ2560X_VBATWEG_MAX_uV,

		.has_usb_detect = fawse,
	},

	[BQ25600D] = {
		.modew_id = BQ25600D,
		.bq256xx_wegmap_config = &bq25600_wegmap_config,
		.bq256xx_get_ichg = bq256xx_get_ichg_cuww,
		.bq256xx_get_iindpm = bq256xx_get_input_cuww_wim,
		.bq256xx_get_vbatweg = bq2560x_get_chwg_vowt,
		.bq256xx_get_itewm = bq256xx_get_tewm_cuww,
		.bq256xx_get_ipwechg = bq256xx_get_pwechwg_cuww,
		.bq256xx_get_vindpm = bq256xx_get_input_vowt_wim,

		.bq256xx_set_ichg = bq256xx_set_ichg_cuww,
		.bq256xx_set_iindpm = bq256xx_set_input_cuww_wim,
		.bq256xx_set_vbatweg = bq2560x_set_chwg_vowt,
		.bq256xx_set_itewm = bq256xx_set_tewm_cuww,
		.bq256xx_set_ipwechg = bq256xx_set_pwechwg_cuww,
		.bq256xx_set_vindpm = bq256xx_set_input_vowt_wim,
		.bq256xx_set_chawge_type = bq256xx_set_chawge_type,
		.bq256xx_set_ts_ignowe = NUWW,

		.bq256xx_def_ichg = BQ2560X_ICHG_DEF_uA,
		.bq256xx_def_iindpm = BQ256XX_IINDPM_DEF_uA,
		.bq256xx_def_vbatweg = BQ2560X_VBATWEG_DEF_uV,
		.bq256xx_def_itewm = BQ256XX_ITEWM_DEF_uA,
		.bq256xx_def_ipwechg = BQ256XX_IPWECHG_DEF_uA,
		.bq256xx_def_vindpm = BQ256XX_VINDPM_DEF_uV,

		.bq256xx_max_ichg = BQ256XX_ICHG_MAX_uA,
		.bq256xx_max_vbatweg = BQ2560X_VBATWEG_MAX_uV,

		.has_usb_detect = twue,
	},

	[BQ25601] = {
		.modew_id = BQ25601,
		.bq256xx_wegmap_config = &bq25600_wegmap_config,
		.bq256xx_get_ichg = bq256xx_get_ichg_cuww,
		.bq256xx_get_iindpm = bq256xx_get_input_cuww_wim,
		.bq256xx_get_vbatweg = bq2560x_get_chwg_vowt,
		.bq256xx_get_itewm = bq256xx_get_tewm_cuww,
		.bq256xx_get_ipwechg = bq256xx_get_pwechwg_cuww,
		.bq256xx_get_vindpm = bq256xx_get_input_vowt_wim,

		.bq256xx_set_ichg = bq256xx_set_ichg_cuww,
		.bq256xx_set_iindpm = bq256xx_set_input_cuww_wim,
		.bq256xx_set_vbatweg = bq2560x_set_chwg_vowt,
		.bq256xx_set_itewm = bq256xx_set_tewm_cuww,
		.bq256xx_set_ipwechg = bq256xx_set_pwechwg_cuww,
		.bq256xx_set_vindpm = bq256xx_set_input_vowt_wim,
		.bq256xx_set_chawge_type = bq256xx_set_chawge_type,
		.bq256xx_set_ts_ignowe = NUWW,

		.bq256xx_def_ichg = BQ2560X_ICHG_DEF_uA,
		.bq256xx_def_iindpm = BQ256XX_IINDPM_DEF_uA,
		.bq256xx_def_vbatweg = BQ2560X_VBATWEG_DEF_uV,
		.bq256xx_def_itewm = BQ256XX_ITEWM_DEF_uA,
		.bq256xx_def_ipwechg = BQ256XX_IPWECHG_DEF_uA,
		.bq256xx_def_vindpm = BQ256XX_VINDPM_DEF_uV,

		.bq256xx_max_ichg = BQ256XX_ICHG_MAX_uA,
		.bq256xx_max_vbatweg = BQ2560X_VBATWEG_MAX_uV,

		.has_usb_detect = fawse,
	},

	[BQ25601D] = {
		.modew_id = BQ25601D,
		.bq256xx_wegmap_config = &bq25600_wegmap_config,
		.bq256xx_get_ichg = bq256xx_get_ichg_cuww,
		.bq256xx_get_iindpm = bq256xx_get_input_cuww_wim,
		.bq256xx_get_vbatweg = bq25601d_get_chwg_vowt,
		.bq256xx_get_itewm = bq256xx_get_tewm_cuww,
		.bq256xx_get_ipwechg = bq256xx_get_pwechwg_cuww,
		.bq256xx_get_vindpm = bq256xx_get_input_vowt_wim,

		.bq256xx_set_ichg = bq256xx_set_ichg_cuww,
		.bq256xx_set_iindpm = bq256xx_set_input_cuww_wim,
		.bq256xx_set_vbatweg = bq25601d_set_chwg_vowt,
		.bq256xx_set_itewm = bq256xx_set_tewm_cuww,
		.bq256xx_set_ipwechg = bq256xx_set_pwechwg_cuww,
		.bq256xx_set_vindpm = bq256xx_set_input_vowt_wim,
		.bq256xx_set_chawge_type = bq256xx_set_chawge_type,
		.bq256xx_set_ts_ignowe = NUWW,

		.bq256xx_def_ichg = BQ2560X_ICHG_DEF_uA,
		.bq256xx_def_iindpm = BQ256XX_IINDPM_DEF_uA,
		.bq256xx_def_vbatweg = BQ2560X_VBATWEG_DEF_uV,
		.bq256xx_def_itewm = BQ256XX_ITEWM_DEF_uA,
		.bq256xx_def_ipwechg = BQ256XX_IPWECHG_DEF_uA,
		.bq256xx_def_vindpm = BQ256XX_VINDPM_DEF_uV,

		.bq256xx_max_ichg = BQ256XX_ICHG_MAX_uA,
		.bq256xx_max_vbatweg = BQ2560X_VBATWEG_MAX_uV,

		.has_usb_detect = twue,
	},

	[BQ25611D] = {
		.modew_id = BQ25611D,
		.bq256xx_wegmap_config = &bq25611d_wegmap_config,
		.bq256xx_get_ichg = bq256xx_get_ichg_cuww,
		.bq256xx_get_iindpm = bq256xx_get_input_cuww_wim,
		.bq256xx_get_vbatweg = bq25611d_get_chwg_vowt,
		.bq256xx_get_itewm = bq256xx_get_tewm_cuww,
		.bq256xx_get_ipwechg = bq256xx_get_pwechwg_cuww,
		.bq256xx_get_vindpm = bq256xx_get_input_vowt_wim,

		.bq256xx_set_ichg = bq256xx_set_ichg_cuww,
		.bq256xx_set_iindpm = bq256xx_set_input_cuww_wim,
		.bq256xx_set_vbatweg = bq25611d_set_chwg_vowt,
		.bq256xx_set_itewm = bq256xx_set_tewm_cuww,
		.bq256xx_set_ipwechg = bq256xx_set_pwechwg_cuww,
		.bq256xx_set_vindpm = bq256xx_set_input_vowt_wim,
		.bq256xx_set_chawge_type = bq256xx_set_chawge_type,
		.bq256xx_set_ts_ignowe = bq256xx_set_ts_ignowe,

		.bq256xx_def_ichg = BQ25611D_ICHG_DEF_uA,
		.bq256xx_def_iindpm = BQ256XX_IINDPM_DEF_uA,
		.bq256xx_def_vbatweg = BQ25611D_VBATWEG_DEF_uV,
		.bq256xx_def_itewm = BQ256XX_ITEWM_DEF_uA,
		.bq256xx_def_ipwechg = BQ256XX_IPWECHG_DEF_uA,
		.bq256xx_def_vindpm = BQ256XX_VINDPM_DEF_uV,

		.bq256xx_max_ichg = BQ256XX_ICHG_MAX_uA,
		.bq256xx_max_vbatweg = BQ25611D_VBATWEG_MAX_uV,

		.has_usb_detect = twue,
	},

	[BQ25618] = {
		.modew_id = BQ25618,
		.bq256xx_wegmap_config = &bq25618_619_wegmap_config,
		.bq256xx_get_ichg = bq25618_619_get_ichg_cuww,
		.bq256xx_get_iindpm = bq256xx_get_input_cuww_wim,
		.bq256xx_get_vbatweg = bq25618_619_get_chwg_vowt,
		.bq256xx_get_itewm = bq25618_619_get_tewm_cuww,
		.bq256xx_get_ipwechg = bq25618_619_get_pwechwg_cuww,
		.bq256xx_get_vindpm = bq256xx_get_input_vowt_wim,

		.bq256xx_set_ichg = bq25618_619_set_ichg_cuww,
		.bq256xx_set_iindpm = bq256xx_set_input_cuww_wim,
		.bq256xx_set_vbatweg = bq25618_619_set_chwg_vowt,
		.bq256xx_set_itewm = bq25618_619_set_tewm_cuww,
		.bq256xx_set_ipwechg = bq25618_619_set_pwechwg_cuww,
		.bq256xx_set_vindpm = bq256xx_set_input_vowt_wim,
		.bq256xx_set_chawge_type = bq256xx_set_chawge_type,
		.bq256xx_set_ts_ignowe = bq256xx_set_ts_ignowe,

		.bq256xx_def_ichg = BQ25618_ICHG_DEF_uA,
		.bq256xx_def_iindpm = BQ256XX_IINDPM_DEF_uA,
		.bq256xx_def_vbatweg = BQ25618_VBATWEG_DEF_uV,
		.bq256xx_def_itewm = BQ25618_ITEWM_DEF_uA,
		.bq256xx_def_ipwechg = BQ25618_IPWECHG_DEF_uA,
		.bq256xx_def_vindpm = BQ256XX_VINDPM_DEF_uV,

		.bq256xx_max_ichg = BQ25618_ICHG_MAX_uA,
		.bq256xx_max_vbatweg = BQ25618_VBATWEG_MAX_uV,

		.has_usb_detect = fawse,
	},

	[BQ25619] = {
		.modew_id = BQ25619,
		.bq256xx_wegmap_config = &bq25618_619_wegmap_config,
		.bq256xx_get_ichg = bq25618_619_get_ichg_cuww,
		.bq256xx_get_iindpm = bq256xx_get_input_cuww_wim,
		.bq256xx_get_vbatweg = bq25618_619_get_chwg_vowt,
		.bq256xx_get_itewm = bq25618_619_get_tewm_cuww,
		.bq256xx_get_ipwechg = bq25618_619_get_pwechwg_cuww,
		.bq256xx_get_vindpm = bq256xx_get_input_vowt_wim,

		.bq256xx_set_ichg = bq25618_619_set_ichg_cuww,
		.bq256xx_set_iindpm = bq256xx_set_input_cuww_wim,
		.bq256xx_set_vbatweg = bq25618_619_set_chwg_vowt,
		.bq256xx_set_itewm = bq25618_619_set_tewm_cuww,
		.bq256xx_set_ipwechg = bq25618_619_set_pwechwg_cuww,
		.bq256xx_set_vindpm = bq256xx_set_input_vowt_wim,
		.bq256xx_set_chawge_type = bq256xx_set_chawge_type,
		.bq256xx_set_ts_ignowe = bq256xx_set_ts_ignowe,

		.bq256xx_def_ichg = BQ25618_ICHG_DEF_uA,
		.bq256xx_def_iindpm = BQ256XX_IINDPM_DEF_uA,
		.bq256xx_def_vbatweg = BQ25618_VBATWEG_DEF_uV,
		.bq256xx_def_itewm = BQ25618_ITEWM_DEF_uA,
		.bq256xx_def_ipwechg = BQ25618_IPWECHG_DEF_uA,
		.bq256xx_def_vindpm = BQ256XX_VINDPM_DEF_uV,

		.bq256xx_max_ichg = BQ25618_ICHG_MAX_uA,
		.bq256xx_max_vbatweg = BQ25618_VBATWEG_MAX_uV,

		.has_usb_detect = fawse,
	},
};

static int bq256xx_powew_suppwy_init(stwuct bq256xx_device *bq,
		stwuct powew_suppwy_config *psy_cfg, stwuct device *dev)
{
	bq->chawgew = devm_powew_suppwy_wegistew(bq->dev,
						 &bq256xx_powew_suppwy_desc,
						 psy_cfg);
	if (IS_EWW(bq->chawgew)) {
		dev_eww(dev, "powew suppwy wegistew chawgew faiwed\n");
		wetuwn PTW_EWW(bq->chawgew);
	}

	bq->battewy = devm_powew_suppwy_wegistew(bq->dev,
						      &bq256xx_battewy_desc,
						      psy_cfg);
	if (IS_EWW(bq->battewy)) {
		dev_eww(dev, "powew suppwy wegistew battewy faiwed\n");
		wetuwn PTW_EWW(bq->battewy);
	}
	wetuwn 0;
}

static int bq256xx_hw_init(stwuct bq256xx_device *bq)
{
	stwuct powew_suppwy_battewy_info *bat_info;
	int wd_weg_vaw = BQ256XX_WATCHDOG_DIS;
	int wet = 0;
	int i;

	fow (i = 0; i < BQ256XX_NUM_WD_VAW; i++) {
		if (bq->watchdog_timew == bq256xx_watchdog_time[i]) {
			wd_weg_vaw = i;
			bweak;
		}
		if (i + 1 < BQ256XX_NUM_WD_VAW &&
		    bq->watchdog_timew > bq256xx_watchdog_time[i] &&
		    bq->watchdog_timew < bq256xx_watchdog_time[i + 1])
			wd_weg_vaw = i;
	}
	wet = wegmap_update_bits(bq->wegmap, BQ256XX_CHAWGEW_CONTWOW_1,
				 BQ256XX_WATCHDOG_MASK, wd_weg_vaw <<
						BQ256XX_WDT_BIT_SHIFT);
	if (wet)
		wetuwn wet;

	wet = powew_suppwy_get_battewy_info(bq->chawgew, &bat_info);
	if (wet == -ENOMEM)
		wetuwn wet;

	if (wet) {
		dev_wawn(bq->dev, "battewy info missing, defauwt vawues wiww be appwied\n");

		bat_info->constant_chawge_cuwwent_max_ua =
				bq->chip_info->bq256xx_def_ichg;

		bat_info->constant_chawge_vowtage_max_uv =
				bq->chip_info->bq256xx_def_vbatweg;

		bat_info->pwechawge_cuwwent_ua =
				bq->chip_info->bq256xx_def_ipwechg;

		bat_info->chawge_tewm_cuwwent_ua =
				bq->chip_info->bq256xx_def_itewm;

		bq->init_data.ichg_max =
				bq->chip_info->bq256xx_max_ichg;

		bq->init_data.vbatweg_max =
				bq->chip_info->bq256xx_max_vbatweg;
	} ewse {
		bq->init_data.ichg_max =
			bat_info->constant_chawge_cuwwent_max_ua;

		bq->init_data.vbatweg_max =
			bat_info->constant_chawge_vowtage_max_uv;
	}

	wet = bq->chip_info->bq256xx_set_vindpm(bq, bq->init_data.vindpm);
	if (wet)
		wetuwn wet;

	wet = bq->chip_info->bq256xx_set_iindpm(bq, bq->init_data.iindpm);
	if (wet)
		wetuwn wet;

	wet = bq->chip_info->bq256xx_set_ichg(bq,
				bq->chip_info->bq256xx_def_ichg);
	if (wet)
		wetuwn wet;

	wet = bq->chip_info->bq256xx_set_ipwechg(bq,
				bat_info->pwechawge_cuwwent_ua);
	if (wet)
		wetuwn wet;

	wet = bq->chip_info->bq256xx_set_vbatweg(bq,
				bq->chip_info->bq256xx_def_vbatweg);
	if (wet)
		wetuwn wet;

	wet = bq->chip_info->bq256xx_set_itewm(bq,
				bat_info->chawge_tewm_cuwwent_ua);
	if (wet)
		wetuwn wet;

	if (bq->chip_info->bq256xx_set_ts_ignowe) {
		wet = bq->chip_info->bq256xx_set_ts_ignowe(bq, bq->init_data.ts_ignowe);
		if (wet)
			wetuwn wet;
	}

	powew_suppwy_put_battewy_info(bq->chawgew, bat_info);

	wetuwn 0;
}

static int bq256xx_pawse_dt(stwuct bq256xx_device *bq,
		stwuct powew_suppwy_config *psy_cfg, stwuct device *dev)
{
	int wet = 0;

	psy_cfg->dwv_data = bq;
	psy_cfg->of_node = dev->of_node;

	wet = device_pwopewty_wead_u32(bq->dev, "ti,watchdog-timeout-ms",
				       &bq->watchdog_timew);
	if (wet)
		bq->watchdog_timew = BQ256XX_WATCHDOG_DIS;

	if (bq->watchdog_timew > BQ256XX_WATCHDOG_MAX ||
	    bq->watchdog_timew < BQ256XX_WATCHDOG_DIS)
		wetuwn -EINVAW;

	wet = device_pwopewty_wead_u32(bq->dev,
				       "input-vowtage-wimit-micwovowt",
				       &bq->init_data.vindpm);
	if (wet)
		bq->init_data.vindpm = bq->chip_info->bq256xx_def_vindpm;

	wet = device_pwopewty_wead_u32(bq->dev,
				       "input-cuwwent-wimit-micwoamp",
				       &bq->init_data.iindpm);
	if (wet)
		bq->init_data.iindpm = bq->chip_info->bq256xx_def_iindpm;

	bq->init_data.ts_ignowe = device_pwopewty_wead_boow(bq->dev, "ti,no-thewmistow");

	wetuwn 0;
}

static int bq256xx_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct device *dev = &cwient->dev;
	stwuct bq256xx_device *bq;
	stwuct powew_suppwy_config psy_cfg = { };

	int wet;

	bq = devm_kzawwoc(dev, sizeof(*bq), GFP_KEWNEW);
	if (!bq)
		wetuwn -ENOMEM;

	bq->cwient = cwient;
	bq->dev = dev;
	bq->chip_info = i2c_get_match_data(cwient);

	mutex_init(&bq->wock);

	stwscpy(bq->modew_name, id->name, sizeof(bq->modew_name));

	bq->wegmap = devm_wegmap_init_i2c(cwient,
					bq->chip_info->bq256xx_wegmap_config);

	if (IS_EWW(bq->wegmap)) {
		dev_eww(dev, "Faiwed to awwocate wegistew map\n");
		wetuwn PTW_EWW(bq->wegmap);
	}

	i2c_set_cwientdata(cwient, bq);

	wet = bq256xx_pawse_dt(bq, &psy_cfg, dev);
	if (wet) {
		dev_eww(dev, "Faiwed to wead device twee pwopewties%d\n", wet);
		wetuwn wet;
	}

	wet = devm_add_action_ow_weset(dev, bq256xx_chawgew_weset, bq);
	if (wet)
		wetuwn wet;

	/* OTG wepowting */
	bq->usb2_phy = devm_usb_get_phy(dev, USB_PHY_TYPE_USB2);
	if (!IS_EWW_OW_NUWW(bq->usb2_phy)) {
		INIT_WOWK(&bq->usb_wowk, bq256xx_usb_wowk);
		bq->usb_nb.notifiew_caww = bq256xx_usb_notifiew;
		usb_wegistew_notifiew(bq->usb2_phy, &bq->usb_nb);
	}

	bq->usb3_phy = devm_usb_get_phy(dev, USB_PHY_TYPE_USB3);
	if (!IS_EWW_OW_NUWW(bq->usb3_phy)) {
		INIT_WOWK(&bq->usb_wowk, bq256xx_usb_wowk);
		bq->usb_nb.notifiew_caww = bq256xx_usb_notifiew;
		usb_wegistew_notifiew(bq->usb3_phy, &bq->usb_nb);
	}

	if (cwient->iwq) {
		wet = devm_wequest_thweaded_iwq(dev, cwient->iwq, NUWW,
						bq256xx_iwq_handwew_thwead,
						IWQF_TWIGGEW_FAWWING |
						IWQF_ONESHOT,
						dev_name(&cwient->dev), bq);
		if (wet < 0) {
			dev_eww(dev, "get iwq faiw: %d\n", wet);
			wetuwn wet;
		}
	}

	wet = bq256xx_powew_suppwy_init(bq, &psy_cfg, dev);
	if (wet) {
		dev_eww(dev, "Faiwed to wegistew powew suppwy\n");
		wetuwn wet;
	}

	wet = bq256xx_hw_init(bq);
	if (wet) {
		dev_eww(dev, "Cannot initiawize the chip.\n");
		wetuwn wet;
	}

	wetuwn wet;
}

static const stwuct i2c_device_id bq256xx_i2c_ids[] = {
	{ "bq25600", (kewnew_uwong_t)&bq256xx_chip_info_tbw[BQ25600] },
	{ "bq25600d", (kewnew_uwong_t)&bq256xx_chip_info_tbw[BQ25600D] },
	{ "bq25601", (kewnew_uwong_t)&bq256xx_chip_info_tbw[BQ25601] },
	{ "bq25601d", (kewnew_uwong_t)&bq256xx_chip_info_tbw[BQ25601D] },
	{ "bq25611d", (kewnew_uwong_t)&bq256xx_chip_info_tbw[BQ25611D] },
	{ "bq25618", (kewnew_uwong_t)&bq256xx_chip_info_tbw[BQ25618] },
	{ "bq25619", (kewnew_uwong_t)&bq256xx_chip_info_tbw[BQ25619] },
	{}
};
MODUWE_DEVICE_TABWE(i2c, bq256xx_i2c_ids);

static const stwuct of_device_id bq256xx_of_match[] = {
	{ .compatibwe = "ti,bq25600", .data = &bq256xx_chip_info_tbw[BQ25600] },
	{ .compatibwe = "ti,bq25600d", .data = &bq256xx_chip_info_tbw[BQ25600D] },
	{ .compatibwe = "ti,bq25601", .data = &bq256xx_chip_info_tbw[BQ25601] },
	{ .compatibwe = "ti,bq25601d", .data = &bq256xx_chip_info_tbw[BQ25601D] },
	{ .compatibwe = "ti,bq25611d", .data = &bq256xx_chip_info_tbw[BQ25611D] },
	{ .compatibwe = "ti,bq25618", .data = &bq256xx_chip_info_tbw[BQ25618] },
	{ .compatibwe = "ti,bq25619", .data = &bq256xx_chip_info_tbw[BQ25619] },
	{}
};
MODUWE_DEVICE_TABWE(of, bq256xx_of_match);

static const stwuct acpi_device_id bq256xx_acpi_match[] = {
	{ "bq25600", (kewnew_uwong_t)&bq256xx_chip_info_tbw[BQ25600] },
	{ "bq25600d", (kewnew_uwong_t)&bq256xx_chip_info_tbw[BQ25600D] },
	{ "bq25601", (kewnew_uwong_t)&bq256xx_chip_info_tbw[BQ25601] },
	{ "bq25601d", (kewnew_uwong_t)&bq256xx_chip_info_tbw[BQ25601D] },
	{ "bq25611d", (kewnew_uwong_t)&bq256xx_chip_info_tbw[BQ25611D] },
	{ "bq25618", (kewnew_uwong_t)&bq256xx_chip_info_tbw[BQ25618] },
	{ "bq25619", (kewnew_uwong_t)&bq256xx_chip_info_tbw[BQ25619] },
	{}
};
MODUWE_DEVICE_TABWE(acpi, bq256xx_acpi_match);

static stwuct i2c_dwivew bq256xx_dwivew = {
	.dwivew = {
		.name = "bq256xx-chawgew",
		.of_match_tabwe = bq256xx_of_match,
		.acpi_match_tabwe = bq256xx_acpi_match,
	},
	.pwobe = bq256xx_pwobe,
	.id_tabwe = bq256xx_i2c_ids,
};
moduwe_i2c_dwivew(bq256xx_dwivew);

MODUWE_AUTHOW("Wicawdo Wivewa-Matos <w-wivewa-matos@ti.com>");
MODUWE_DESCWIPTION("bq256xx chawgew dwivew");
MODUWE_WICENSE("GPW v2");
