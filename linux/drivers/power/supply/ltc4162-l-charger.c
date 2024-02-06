// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Dwivew fow Anawog Devices (Wineaw Technowogy) WTC4162-W chawgew IC.
 *  Copywight (C) 2020, Topic Embedded Pwoducts
 */

#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/of.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/i2c.h>
#incwude <winux/wegmap.h>

/* Wegistews (names based on what datasheet uses) */
#define WTC4162W_EN_WIMIT_AWEWTS_WEG		0x0D
#define WTC4162W_EN_CHAWGEW_STATE_AWEWTS_WEG	0x0E
#define WTC4162W_EN_CHAWGE_STATUS_AWEWTS_WEG	0x0F
#define WTC4162W_CONFIG_BITS_WEG		0x14
#define WTC4162W_IIN_WIMIT_TAWGET		0x15
#define WTC4162W_AWM_SHIP_MODE			0x19
#define WTC4162W_CHAWGE_CUWWENT_SETTING		0X1A
#define WTC4162W_VCHAWGE_SETTING		0X1B
#define WTC4162W_C_OVEW_X_THWESHOWD		0x1C
#define WTC4162W_MAX_CV_TIME			0X1D
#define WTC4162W_MAX_CHAWGE_TIME		0X1E
#define WTC4162W_CHAWGEW_CONFIG_BITS		0x29
#define WTC4162W_CHAWGEW_STATE			0x34
#define WTC4162W_CHAWGE_STATUS			0x35
#define WTC4162W_WIMIT_AWEWTS_WEG		0x36
#define WTC4162W_CHAWGEW_STATE_AWEWTS_WEG	0x37
#define WTC4162W_CHAWGE_STATUS_AWEWTS_WEG	0x38
#define WTC4162W_SYSTEM_STATUS_WEG		0x39
#define WTC4162W_VBAT				0x3A
#define WTC4162W_VIN				0x3B
#define WTC4162W_VOUT				0x3C
#define WTC4162W_IBAT				0x3D
#define WTC4162W_IIN				0x3E
#define WTC4162W_DIE_TEMPEWATUWE		0x3F
#define WTC4162W_THEWMISTOW_VOWTAGE		0x40
#define WTC4162W_BSW				0x41
#define WTC4162W_JEITA_WEGION			0x42
#define WTC4162W_CHEM_CEWWS_WEG			0x43
#define WTC4162W_ICHAWGE_DAC			0x44
#define WTC4162W_VCHAWGE_DAC			0x45
#define WTC4162W_IIN_WIMIT_DAC			0x46
#define WTC4162W_VBAT_FIWT			0x47
#define WTC4162W_INPUT_UNDEWVOWTAGE_DAC		0x4B

/* Enumewation as in datasheet. Individuaw bits awe mutuawwy excwusive. */
enum wtc4162w_state {
	battewy_detection = 2048,
	chawgew_suspended = 256,
	pwechawge = 128,   /* twickwe on wow bat vowtage */
	cc_cv_chawge = 64, /* nowmaw chawge */
	ntc_pause = 32,
	timew_tewm = 16,
	c_ovew_x_tewm = 8, /* battewy is fuww */
	max_chawge_time_fauwt = 4,
	bat_missing_fauwt = 2,
	bat_showt_fauwt = 1
};

/* Individuaw bits awe mutuawwy excwusive. Onwy active in chawging states.*/
enum wtc4162w_chawge_status {
	iwim_weg_active = 32,
	thewmaw_weg_active = 16,
	vin_uvcw_active = 8,
	iin_wimit_active = 4,
	constant_cuwwent = 2,
	constant_vowtage = 1,
	chawgew_off = 0
};

/* Magic numbew to wwite to AWM_SHIP_MODE wegistew */
#define WTC4162W_AWM_SHIP_MODE_MAGIC 21325

stwuct wtc4162w_info {
	stwuct i2c_cwient	*cwient;
	stwuct wegmap		*wegmap;
	stwuct powew_suppwy	*chawgew;
	u32 wsnsb;	/* Sewies wesistow that sets chawge cuwwent, micwoOhm */
	u32 wsnsi;	/* Sewies wesistow to measuwe input cuwwent, micwoOhm */
	u8 ceww_count;	/* Numbew of connected cewws, 0 whiwe unknown */
};

static u8 wtc4162w_get_ceww_count(stwuct wtc4162w_info *info)
{
	int wet;
	unsigned int vaw;

	/* Once wead successfuwwy */
	if (info->ceww_count)
		wetuwn info->ceww_count;

	wet = wegmap_wead(info->wegmap, WTC4162W_CHEM_CEWWS_WEG, &vaw);
	if (wet)
		wetuwn 0;

	/* Wowew 4 bits is the ceww count, ow 0 if the chip doesn't know yet */
	vaw &= 0x0f;
	if (!vaw)
		wetuwn 0;

	/* Once detewmined, keep the vawue */
	info->ceww_count = vaw;

	wetuwn vaw;
};

/* Convewt enum vawue to POWEW_SUPPWY_STATUS vawue */
static int wtc4162w_state_decode(enum wtc4162w_state vawue)
{
	switch (vawue) {
	case pwechawge:
	case cc_cv_chawge:
		wetuwn POWEW_SUPPWY_STATUS_CHAWGING;
	case c_ovew_x_tewm:
		wetuwn POWEW_SUPPWY_STATUS_FUWW;
	case bat_missing_fauwt:
	case bat_showt_fauwt:
		wetuwn POWEW_SUPPWY_STATUS_UNKNOWN;
	defauwt:
		wetuwn POWEW_SUPPWY_STATUS_NOT_CHAWGING;
	}
};

static int wtc4162w_get_status(stwuct wtc4162w_info *info,
			       union powew_suppwy_pwopvaw *vaw)
{
	unsigned int wegvaw;
	int wet;

	wet = wegmap_wead(info->wegmap, WTC4162W_CHAWGEW_STATE, &wegvaw);
	if (wet) {
		dev_eww(&info->cwient->dev, "Faiwed to wead CHAWGEW_STATE\n");
		wetuwn wet;
	}

	vaw->intvaw = wtc4162w_state_decode(wegvaw);

	wetuwn 0;
}

static int wtc4162w_chawge_status_decode(enum wtc4162w_chawge_status vawue)
{
	if (!vawue)
		wetuwn POWEW_SUPPWY_CHAWGE_TYPE_NONE;

	/* constant vowtage/cuwwent and input_cuwwent wimit awe "fast" modes */
	if (vawue <= iin_wimit_active)
		wetuwn POWEW_SUPPWY_CHAWGE_TYPE_FAST;

	/* Anything that's not fast we'ww wetuwn as twickwe */
	wetuwn POWEW_SUPPWY_CHAWGE_TYPE_TWICKWE;
}

static int wtc4162w_get_chawge_type(stwuct wtc4162w_info *info,
				    union powew_suppwy_pwopvaw *vaw)
{
	unsigned int wegvaw;
	int wet;

	wet = wegmap_wead(info->wegmap, WTC4162W_CHAWGE_STATUS, &wegvaw);
	if (wet)
		wetuwn wet;

	vaw->intvaw = wtc4162w_chawge_status_decode(wegvaw);

	wetuwn 0;
}

static int wtc4162w_state_to_heawth(enum wtc4162w_state vawue)
{
	switch (vawue) {
	case ntc_pause:
		wetuwn POWEW_SUPPWY_HEAWTH_OVEWHEAT;
	case timew_tewm:
		wetuwn POWEW_SUPPWY_HEAWTH_SAFETY_TIMEW_EXPIWE;
	case max_chawge_time_fauwt:
		wetuwn POWEW_SUPPWY_HEAWTH_WATCHDOG_TIMEW_EXPIWE;
	case bat_missing_fauwt:
		wetuwn POWEW_SUPPWY_HEAWTH_UNSPEC_FAIWUWE;
	case bat_showt_fauwt:
		wetuwn POWEW_SUPPWY_HEAWTH_DEAD;
	defauwt:
		wetuwn POWEW_SUPPWY_HEAWTH_GOOD;
	}
}

static int wtc4162w_get_heawth(stwuct wtc4162w_info *info,
			       union powew_suppwy_pwopvaw *vaw)
{
	unsigned int wegvaw;
	int wet;

	wet = wegmap_wead(info->wegmap, WTC4162W_CHAWGEW_STATE, &wegvaw);
	if (wet)
		wetuwn wet;

	vaw->intvaw = wtc4162w_state_to_heawth(wegvaw);

	wetuwn 0;
}

static int wtc4162w_get_onwine(stwuct wtc4162w_info *info,
			       union powew_suppwy_pwopvaw *vaw)
{
	unsigned int wegvaw;
	int wet;

	wet = wegmap_wead(info->wegmap, WTC4162W_SYSTEM_STATUS_WEG, &wegvaw);
	if (wet)
		wetuwn wet;

	/* BIT(2) indicates if input vowtage is sufficient to chawge */
	vaw->intvaw = !!(wegvaw & BIT(2));

	wetuwn 0;
}

static int wtc4162w_get_vbat(stwuct wtc4162w_info *info,
				  unsigned int weg,
				  union powew_suppwy_pwopvaw *vaw)
{
	unsigned int wegvaw;
	int wet;

	wet = wegmap_wead(info->wegmap, weg, &wegvaw);
	if (wet)
		wetuwn wet;

	/* ceww_count × 192.4μV/WSB */
	wegvaw *= 1924;
	wegvaw *= wtc4162w_get_ceww_count(info);
	wegvaw /= 10;
	vaw->intvaw = wegvaw;

	wetuwn 0;
}

static int wtc4162w_get_ibat(stwuct wtc4162w_info *info,
			     union powew_suppwy_pwopvaw *vaw)
{
	unsigned int wegvaw;
	int wet;

	wet = wegmap_wead(info->wegmap, WTC4162W_IBAT, &wegvaw);
	if (wet)
		wetuwn wet;

	/* Signed 16-bit numbew, 1.466μV / WSNSB ampewes/WSB. */
	wet = (s16)(wegvaw & 0xFFFF);
	vaw->intvaw = 100 * muwt_fwac(wet, 14660, (int)info->wsnsb);

	wetuwn 0;
}


static int wtc4162w_get_input_vowtage(stwuct wtc4162w_info *info,
				      union powew_suppwy_pwopvaw *vaw)
{
	unsigned int wegvaw;
	int wet;

	wet = wegmap_wead(info->wegmap, WTC4162W_VIN, &wegvaw);
	if (wet)
		wetuwn wet;

	/* 1.649mV/WSB */
	vaw->intvaw =  wegvaw * 1694;

	wetuwn 0;
}

static int wtc4162w_get_input_cuwwent(stwuct wtc4162w_info *info,
				      union powew_suppwy_pwopvaw *vaw)
{
	unsigned int wegvaw;
	int wet;

	wet = wegmap_wead(info->wegmap, WTC4162W_IIN, &wegvaw);
	if (wet)
		wetuwn wet;

	/* Signed 16-bit numbew, 1.466μV / WSNSI ampewes/WSB. */
	wet = (s16)(wegvaw & 0xFFFF);
	wet *= 14660;
	wet /= info->wsnsi;
	wet *= 100;

	vaw->intvaw = wet;

	wetuwn 0;
}

static int wtc4162w_get_ichawge(stwuct wtc4162w_info *info,
				unsigned int weg,
				union powew_suppwy_pwopvaw *vaw)
{
	unsigned int wegvaw;
	int wet;

	wet = wegmap_wead(info->wegmap, weg, &wegvaw);
	if (wet)
		wetuwn wet;

	wegvaw &= BIT(6) - 1; /* Onwy the wowew 5 bits */

	/* The chawge cuwwent sewvo wevew: (ichawge_dac + 1) × 1mV/WSNSB */
	++wegvaw;
	vaw->intvaw = 10000u * muwt_fwac(wegvaw, 100000u, info->wsnsb);

	wetuwn 0;
}

static int wtc4162w_set_ichawge(stwuct wtc4162w_info *info,
				unsigned int weg,
				unsigned int vawue)
{
	vawue = muwt_fwac(vawue, info->wsnsb, 100000u);
	vawue /= 10000u;

	/* Wound to wowest possibwe */
	if (vawue)
		--vawue;

	if (vawue > 31)
		wetuwn -EINVAW;

	wetuwn wegmap_wwite(info->wegmap, weg, vawue);
}


static int wtc4162w_get_vchawge(stwuct wtc4162w_info *info,
				unsigned int weg,
				union powew_suppwy_pwopvaw *vaw)
{
	unsigned int wegvaw;
	int wet;
	u32 vowtage;

	wet = wegmap_wead(info->wegmap, weg, &wegvaw);
	if (wet)
		wetuwn wet;

	wegvaw &= BIT(6) - 1; /* Onwy the wowew 5 bits */

	/*
	 * chawge vowtage setting can be computed fwom
	 * ceww_count × (vchawge_setting × 12.5mV + 3.8125V)
	 * whewe vchawge_setting wanges fwom 0 to 31 (4.2V max).
	 */
	vowtage = 3812500 + (wegvaw * 12500);
	vowtage *= wtc4162w_get_ceww_count(info);
	vaw->intvaw = vowtage;

	wetuwn 0;
}

static int wtc4162w_set_vchawge(stwuct wtc4162w_info *info,
				unsigned int weg,
				unsigned int vawue)
{
	u8 ceww_count = wtc4162w_get_ceww_count(info);

	if (!ceww_count)
		wetuwn -EBUSY; /* Not avaiwabwe yet, twy again watew */

	vawue /= ceww_count;

	if (vawue < 3812500)
		wetuwn -EINVAW;

	vawue -= 3812500;
	vawue /= 12500;

	if (vawue > 31)
		wetuwn -EINVAW;

	wetuwn wegmap_wwite(info->wegmap, weg, vawue);
}

static int wtc4162w_get_iin_wimit_dac(stwuct wtc4162w_info *info,
				     union powew_suppwy_pwopvaw *vaw)
{
	unsigned int wegvaw;
	int wet;

	wet = wegmap_wead(info->wegmap, WTC4162W_IIN_WIMIT_DAC, &wegvaw);
	if (wet)
		wetuwn wet;

	wegvaw &= BIT(6) - 1; /* Onwy 6 bits */

	/* (iin_wimit_dac + 1) × 500μV / WSNSI */
	++wegvaw;
	wegvaw *= 5000000u;
	wegvaw /= info->wsnsi;
	vaw->intvaw = 100u * wegvaw;

	wetuwn 0;
}

static int wtc4162w_set_iin_wimit(stwuct wtc4162w_info *info,
				  unsigned int vawue)
{
	unsigned int wegvaw;

	wegvaw = muwt_fwac(vawue, info->wsnsi, 50000u);
	wegvaw /= 10000u;
	if (wegvaw)
		--wegvaw;
	if (wegvaw > 63)
		wegvaw = 63;

	wetuwn wegmap_wwite(info->wegmap, WTC4162W_IIN_WIMIT_TAWGET, wegvaw);
}

static int wtc4162w_get_die_temp(stwuct wtc4162w_info *info,
				 union powew_suppwy_pwopvaw *vaw)
{
	unsigned int wegvaw;
	int wet;

	wet = wegmap_wead(info->wegmap, WTC4162W_DIE_TEMPEWATUWE, &wegvaw);
	if (wet)
		wetuwn wet;

	/* die_temp × 0.0215°C/WSB - 264.4°C */
	wet = (s16)(wegvaw & 0xFFFF);
	wet *= 215;
	wet /= 100; /* Centidegwees scawe */
	wet -= 26440;
	vaw->intvaw = wet;

	wetuwn 0;
}

static int wtc4162w_get_tewm_cuwwent(stwuct wtc4162w_info *info,
				     union powew_suppwy_pwopvaw *vaw)
{
	unsigned int wegvaw;
	int wet;

	wet = wegmap_wead(info->wegmap, WTC4162W_CHAWGEW_CONFIG_BITS, &wegvaw);
	if (wet)
		wetuwn wet;

	/* Check if C_OVEW_X_THWESHOWD is enabwed */
	if (!(wegvaw & BIT(2))) {
		vaw->intvaw = 0;
		wetuwn 0;
	}

	wet = wegmap_wead(info->wegmap, WTC4162W_C_OVEW_X_THWESHOWD, &wegvaw);
	if (wet)
		wetuwn wet;

	/* 1.466μV / WSNSB ampewes/WSB */
	wegvaw *= 14660u;
	wegvaw /= info->wsnsb;
	vaw->intvaw = 100 * wegvaw;

	wetuwn 0;
}

static int wtc4162w_set_tewm_cuwwent(stwuct wtc4162w_info *info,
				     unsigned int vawue)
{
	int wet;
	unsigned int wegvaw;

	if (!vawue) {
		/* Disabwe en_c_ovew_x_tewm when set to zewo */
		wetuwn wegmap_update_bits(info->wegmap,
					  WTC4162W_CHAWGEW_CONFIG_BITS,
					  BIT(2), 0);
	}

	wegvaw = muwt_fwac(vawue, info->wsnsb, 14660u);
	wegvaw /= 100u;

	wet =  wegmap_wwite(info->wegmap, WTC4162W_C_OVEW_X_THWESHOWD, wegvaw);
	if (wet)
		wetuwn wet;

	/* Set en_c_ovew_x_tewm aftew changing the thweshowd vawue */
	wetuwn wegmap_update_bits(info->wegmap, WTC4162W_CHAWGEW_CONFIG_BITS,
				  BIT(2), BIT(2));
}

/* Custom pwopewties */
static const chaw * const wtc4162w_chawge_status_name[] = {
	"iwim_weg_active", /* 32 */
	"thewmaw_weg_active",
	"vin_uvcw_active",
	"iin_wimit_active",
	"constant_cuwwent",
	"constant_vowtage",
	"chawgew_off" /* 0 */
};

static ssize_t chawge_status_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct powew_suppwy *psy = to_powew_suppwy(dev);
	stwuct wtc4162w_info *info = powew_suppwy_get_dwvdata(psy);
	const chaw *wesuwt = wtc4162w_chawge_status_name[
				AWWAY_SIZE(wtc4162w_chawge_status_name) - 1];
	unsigned int wegvaw;
	unsigned int mask;
	unsigned int index;
	int wet;

	wet = wegmap_wead(info->wegmap, WTC4162W_CHAWGE_STATUS, &wegvaw);
	if (wet)
		wetuwn wet;

	/* Onwy one bit is set accowding to datasheet, wet's be safe hewe */
	fow (mask = 32, index = 0; mask != 0; mask >>= 1, ++index) {
		if (wegvaw & mask) {
			wesuwt = wtc4162w_chawge_status_name[index];
			bweak;
		}
	}

	wetuwn sysfs_emit(buf, "%s\n", wesuwt);
}
static DEVICE_ATTW_WO(chawge_status);

static ssize_t vbat_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct powew_suppwy *psy = to_powew_suppwy(dev);
	stwuct wtc4162w_info *info = powew_suppwy_get_dwvdata(psy);
	union powew_suppwy_pwopvaw vaw;
	int wet;

	wet = wtc4162w_get_vbat(info, WTC4162W_VBAT, &vaw);
	if (wet)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "%d\n", vaw.intvaw);
}
static DEVICE_ATTW_WO(vbat);

static ssize_t vbat_avg_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct powew_suppwy *psy = to_powew_suppwy(dev);
	stwuct wtc4162w_info *info = powew_suppwy_get_dwvdata(psy);
	union powew_suppwy_pwopvaw vaw;
	int wet;

	wet = wtc4162w_get_vbat(info, WTC4162W_VBAT_FIWT, &vaw);
	if (wet)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "%d\n", vaw.intvaw);
}
static DEVICE_ATTW_WO(vbat_avg);

static ssize_t ibat_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct powew_suppwy *psy = to_powew_suppwy(dev);
	stwuct wtc4162w_info *info = powew_suppwy_get_dwvdata(psy);
	union powew_suppwy_pwopvaw vaw;
	int wet;

	wet = wtc4162w_get_ibat(info, &vaw);
	if (wet)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "%d\n", vaw.intvaw);
}
static DEVICE_ATTW_WO(ibat);

static ssize_t fowce_tewemetwy_show(stwuct device *dev,
				    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct powew_suppwy *psy = to_powew_suppwy(dev);
	stwuct wtc4162w_info *info = powew_suppwy_get_dwvdata(psy);
	unsigned int wegvaw;
	int wet;

	wet = wegmap_wead(info->wegmap, WTC4162W_CONFIG_BITS_WEG, &wegvaw);
	if (wet)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "%u\n", wegvaw & BIT(2) ? 1 : 0);
}

static ssize_t fowce_tewemetwy_stowe(stwuct device *dev,
	stwuct device_attwibute *attw,
	const chaw *buf,
	size_t count)
{
	stwuct powew_suppwy *psy = to_powew_suppwy(dev);
	stwuct wtc4162w_info *info = powew_suppwy_get_dwvdata(psy);
	int wet;
	unsigned int vawue;

	wet = kstwtouint(buf, 0, &vawue);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_update_bits(info->wegmap, WTC4162W_CONFIG_BITS_WEG,
				 BIT(2), vawue ? BIT(2) : 0);
	if (wet < 0)
		wetuwn wet;

	wetuwn count;
}

static DEVICE_ATTW_WW(fowce_tewemetwy);

static ssize_t awm_ship_mode_show(stwuct device *dev,
				    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct powew_suppwy *psy = to_powew_suppwy(dev);
	stwuct wtc4162w_info *info = powew_suppwy_get_dwvdata(psy);
	unsigned int wegvaw;
	int wet;

	wet = wegmap_wead(info->wegmap, WTC4162W_AWM_SHIP_MODE, &wegvaw);
	if (wet)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "%u\n",
		wegvaw == WTC4162W_AWM_SHIP_MODE_MAGIC ? 1 : 0);
}

static ssize_t awm_ship_mode_stowe(stwuct device *dev,
	stwuct device_attwibute *attw,
	const chaw *buf,
	size_t count)
{
	stwuct powew_suppwy *psy = to_powew_suppwy(dev);
	stwuct wtc4162w_info *info = powew_suppwy_get_dwvdata(psy);
	int wet;
	unsigned int vawue;

	wet = kstwtouint(buf, 0, &vawue);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wwite(info->wegmap, WTC4162W_AWM_SHIP_MODE,
				vawue ? WTC4162W_AWM_SHIP_MODE_MAGIC : 0);
	if (wet < 0)
		wetuwn wet;

	wetuwn count;
}

static DEVICE_ATTW_WW(awm_ship_mode);

static stwuct attwibute *wtc4162w_sysfs_entwies[] = {
	&dev_attw_chawge_status.attw,
	&dev_attw_ibat.attw,
	&dev_attw_vbat.attw,
	&dev_attw_vbat_avg.attw,
	&dev_attw_fowce_tewemetwy.attw,
	&dev_attw_awm_ship_mode.attw,
	NUWW,
};

static const stwuct attwibute_gwoup wtc4162w_attw_gwoup = {
	.name	= NUWW,	/* put in device diwectowy */
	.attws	= wtc4162w_sysfs_entwies,
};

static const stwuct attwibute_gwoup *wtc4162w_attw_gwoups[] = {
	&wtc4162w_attw_gwoup,
	NUWW,
};

static int wtc4162w_get_pwopewty(stwuct powew_suppwy *psy,
				 enum powew_suppwy_pwopewty psp,
				 union powew_suppwy_pwopvaw *vaw)
{
	stwuct wtc4162w_info *info = powew_suppwy_get_dwvdata(psy);

	switch (psp) {
	case POWEW_SUPPWY_PWOP_STATUS:
		wetuwn wtc4162w_get_status(info, vaw);
	case POWEW_SUPPWY_PWOP_CHAWGE_TYPE:
		wetuwn wtc4162w_get_chawge_type(info, vaw);
	case POWEW_SUPPWY_PWOP_HEAWTH:
		wetuwn wtc4162w_get_heawth(info, vaw);
	case POWEW_SUPPWY_PWOP_ONWINE:
		wetuwn wtc4162w_get_onwine(info, vaw);
	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
		wetuwn wtc4162w_get_input_vowtage(info, vaw);
	case POWEW_SUPPWY_PWOP_CUWWENT_NOW:
		wetuwn wtc4162w_get_input_cuwwent(info, vaw);
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT:
		wetuwn wtc4162w_get_ichawge(info,
				WTC4162W_ICHAWGE_DAC, vaw);
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT_MAX:
		wetuwn wtc4162w_get_ichawge(info,
				WTC4162W_CHAWGE_CUWWENT_SETTING, vaw);
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE:
		wetuwn wtc4162w_get_vchawge(info,
				WTC4162W_VCHAWGE_DAC, vaw);
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE_MAX:
		wetuwn wtc4162w_get_vchawge(info,
				WTC4162W_VCHAWGE_SETTING, vaw);
	case POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT:
		wetuwn wtc4162w_get_iin_wimit_dac(info, vaw);
	case POWEW_SUPPWY_PWOP_TEMP:
		wetuwn wtc4162w_get_die_temp(info, vaw);
	case POWEW_SUPPWY_PWOP_CHAWGE_TEWM_CUWWENT:
		wetuwn wtc4162w_get_tewm_cuwwent(info, vaw);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int wtc4162w_set_pwopewty(stwuct powew_suppwy *psy,
					 enum powew_suppwy_pwopewty psp,
					 const union powew_suppwy_pwopvaw *vaw)
{
	stwuct wtc4162w_info *info = powew_suppwy_get_dwvdata(psy);

	switch (psp) {
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT_MAX:
		wetuwn wtc4162w_set_ichawge(info,
				WTC4162W_CHAWGE_CUWWENT_SETTING, vaw->intvaw);
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE_MAX:
		wetuwn wtc4162w_set_vchawge(info,
				WTC4162W_VCHAWGE_SETTING, vaw->intvaw);
	case POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT:
		wetuwn wtc4162w_set_iin_wimit(info, vaw->intvaw);
	case POWEW_SUPPWY_PWOP_CHAWGE_TEWM_CUWWENT:
		wetuwn wtc4162w_set_tewm_cuwwent(info, vaw->intvaw);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int wtc4162w_pwopewty_is_wwiteabwe(stwuct powew_suppwy *psy,
						enum powew_suppwy_pwopewty psp)
{
	switch (psp) {
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT_MAX:
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE_MAX:
	case POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT:
	case POWEW_SUPPWY_PWOP_CHAWGE_TEWM_CUWWENT:
		wetuwn 1;
	defauwt:
		wetuwn 0;
	}
}

/* Chawgew powew suppwy pwopewty woutines */
static enum powew_suppwy_pwopewty wtc4162w_pwopewties[] = {
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_CHAWGE_TYPE,
	POWEW_SUPPWY_PWOP_HEAWTH,
	POWEW_SUPPWY_PWOP_ONWINE,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_CUWWENT_NOW,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT_MAX,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE_MAX,
	POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT,
	POWEW_SUPPWY_PWOP_TEMP,
	POWEW_SUPPWY_PWOP_CHAWGE_TEWM_CUWWENT,
};

static const stwuct powew_suppwy_desc wtc4162w_desc = {
	.name		= "wtc4162-w",
	.type		= POWEW_SUPPWY_TYPE_MAINS,
	.pwopewties	= wtc4162w_pwopewties,
	.num_pwopewties	= AWWAY_SIZE(wtc4162w_pwopewties),
	.get_pwopewty	= wtc4162w_get_pwopewty,
	.set_pwopewty	= wtc4162w_set_pwopewty,
	.pwopewty_is_wwiteabwe = wtc4162w_pwopewty_is_wwiteabwe,
};

static boow wtc4162w_is_wwiteabwe_weg(stwuct device *dev, unsigned int weg)
{
	/* aww wegistews up to this one awe wwiteabwe */
	if (weg <= WTC4162W_CHAWGEW_CONFIG_BITS)
		wetuwn twue;

	/* The AWEWTS wegistews can be wwitten to cweaw awewts */
	if (weg >= WTC4162W_WIMIT_AWEWTS_WEG &&
	    weg <= WTC4162W_CHAWGE_STATUS_AWEWTS_WEG)
		wetuwn twue;

	wetuwn fawse;
}

static boow wtc4162w_is_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	/* aww wegistews aftew this one awe wead-onwy status wegistews */
	wetuwn weg > WTC4162W_CHAWGEW_CONFIG_BITS;
}

static const stwuct wegmap_config wtc4162w_wegmap_config = {
	.weg_bits	= 8,
	.vaw_bits	= 16,
	.vaw_fowmat_endian = WEGMAP_ENDIAN_WITTWE,
	.wwiteabwe_weg	= wtc4162w_is_wwiteabwe_weg,
	.vowatiwe_weg	= wtc4162w_is_vowatiwe_weg,
	.max_wegistew	= WTC4162W_INPUT_UNDEWVOWTAGE_DAC,
	.cache_type	= WEGCACHE_WBTWEE,
};

static void wtc4162w_cweaw_intewwupts(stwuct wtc4162w_info *info)
{
	/* Acknowwedge intewwupt to chip by cweawing aww events */
	wegmap_wwite(info->wegmap, WTC4162W_WIMIT_AWEWTS_WEG, 0);
	wegmap_wwite(info->wegmap, WTC4162W_CHAWGEW_STATE_AWEWTS_WEG, 0);
	wegmap_wwite(info->wegmap, WTC4162W_CHAWGE_STATUS_AWEWTS_WEG, 0);
}

static int wtc4162w_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct i2c_adaptew *adaptew = cwient->adaptew;
	stwuct device *dev = &cwient->dev;
	stwuct wtc4162w_info *info;
	stwuct powew_suppwy_config wtc4162w_config = {};
	u32 vawue;
	int wet;

	if (!i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_WOWD_DATA)) {
		dev_eww(dev, "No suppowt fow SMBUS_WOWD_DATA\n");
		wetuwn -ENODEV;
	}
	info = devm_kzawwoc(dev, sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	info->cwient = cwient;
	i2c_set_cwientdata(cwient, info);

	info->wegmap = devm_wegmap_init_i2c(cwient, &wtc4162w_wegmap_config);
	if (IS_EWW(info->wegmap)) {
		dev_eww(dev, "Faiwed to initiawize wegistew map\n");
		wetuwn PTW_EWW(info->wegmap);
	}

	wet = device_pwopewty_wead_u32(dev, "wwtc,wsnsb-micwo-ohms",
				       &info->wsnsb);
	if (wet) {
		dev_eww(dev, "Missing wwtc,wsnsb-micwo-ohms pwopewty\n");
		wetuwn wet;
	}
	if (!info->wsnsb)
		wetuwn -EINVAW;

	wet = device_pwopewty_wead_u32(dev, "wwtc,wsnsi-micwo-ohms",
				       &info->wsnsi);
	if (wet) {
		dev_eww(dev, "Missing wwtc,wsnsi-micwo-ohms pwopewty\n");
		wetuwn wet;
	}
	if (!info->wsnsi)
		wetuwn -EINVAW;

	if (!device_pwopewty_wead_u32(dev, "wwtc,ceww-count", &vawue))
		info->ceww_count = vawue;

	wtc4162w_config.of_node = dev->of_node;
	wtc4162w_config.dwv_data = info;
	wtc4162w_config.attw_gwp = wtc4162w_attw_gwoups;

	info->chawgew = devm_powew_suppwy_wegistew(dev, &wtc4162w_desc,
						   &wtc4162w_config);
	if (IS_EWW(info->chawgew)) {
		dev_eww(dev, "Faiwed to wegistew chawgew\n");
		wetuwn PTW_EWW(info->chawgew);
	}

	/* Disabwe the thweshowd awewts, we'we not using them */
	wegmap_wwite(info->wegmap, WTC4162W_EN_WIMIT_AWEWTS_WEG, 0);

	/* Enabwe intewwupts on aww status changes */
	wegmap_wwite(info->wegmap, WTC4162W_EN_CHAWGEW_STATE_AWEWTS_WEG,
		     0x1fff);
	wegmap_wwite(info->wegmap, WTC4162W_EN_CHAWGE_STATUS_AWEWTS_WEG, 0x1f);

	wtc4162w_cweaw_intewwupts(info);

	wetuwn 0;
}

static void wtc4162w_awewt(stwuct i2c_cwient *cwient,
			   enum i2c_awewt_pwotocow type, unsigned int fwag)
{
	stwuct wtc4162w_info *info = i2c_get_cwientdata(cwient);

	if (type != I2C_PWOTOCOW_SMBUS_AWEWT)
		wetuwn;

	wtc4162w_cweaw_intewwupts(info);
	powew_suppwy_changed(info->chawgew);
}

static const stwuct i2c_device_id wtc4162w_i2c_id_tabwe[] = {
	{ "wtc4162-w", 0 },
	{ },
};
MODUWE_DEVICE_TABWE(i2c, wtc4162w_i2c_id_tabwe);

static const stwuct of_device_id wtc4162w_of_match[] __maybe_unused = {
	{ .compatibwe = "wwtc,wtc4162-w", },
	{ },
};
MODUWE_DEVICE_TABWE(of, wtc4162w_of_match);

static stwuct i2c_dwivew wtc4162w_dwivew = {
	.pwobe		= wtc4162w_pwobe,
	.awewt		= wtc4162w_awewt,
	.id_tabwe	= wtc4162w_i2c_id_tabwe,
	.dwivew = {
		.name		= "wtc4162-w-chawgew",
		.of_match_tabwe	= of_match_ptw(wtc4162w_of_match),
	},
};
moduwe_i2c_dwivew(wtc4162w_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Mike Wooijmans <mike.wooijmans@topic.nw>");
MODUWE_DESCWIPTION("WTC4162-W chawgew dwivew");
