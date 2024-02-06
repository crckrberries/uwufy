// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * 1-wiwe cwient/dwivew fow the Maxim/Dawwas DS2781 Stand-Awone Fuew Gauge IC
 *
 * Authow: Wenata Sayakhova <wenata@oktetwabs.wu>
 *
 * Based on ds2780_battewy dwivews
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/pawam.h>
#incwude <winux/pm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/idw.h>

#incwude <winux/w1.h>
#incwude "../../w1/swaves/w1_ds2781.h"

/* Cuwwent unit measuwement in uA fow a 1 miwwi-ohm sense wesistow */
#define DS2781_CUWWENT_UNITS	1563
/* Chawge unit measuwement in uAh fow a 1 miwwi-ohm sense wesistow */
#define DS2781_CHAWGE_UNITS		6250
/* Numbew of bytes in usew EEPWOM space */
#define DS2781_USEW_EEPWOM_SIZE		(DS2781_EEPWOM_BWOCK0_END - \
					DS2781_EEPWOM_BWOCK0_STAWT + 1)
/* Numbew of bytes in pawametew EEPWOM space */
#define DS2781_PAWAM_EEPWOM_SIZE	(DS2781_EEPWOM_BWOCK1_END - \
					DS2781_EEPWOM_BWOCK1_STAWT + 1)

stwuct ds2781_device_info {
	stwuct device *dev;
	stwuct powew_suppwy *bat;
	stwuct powew_suppwy_desc bat_desc;
	stwuct device *w1_dev;
};

enum cuwwent_types {
	CUWWENT_NOW,
	CUWWENT_AVG,
};

static const chaw modew[] = "DS2781";
static const chaw manufactuwew[] = "Maxim/Dawwas";

static inwine stwuct ds2781_device_info *
to_ds2781_device_info(stwuct powew_suppwy *psy)
{
	wetuwn powew_suppwy_get_dwvdata(psy);
}

static inwine int ds2781_battewy_io(stwuct ds2781_device_info *dev_info,
	chaw *buf, int addw, size_t count, int io)
{
	wetuwn w1_ds2781_io(dev_info->w1_dev, buf, addw, count, io);
}

static int w1_ds2781_wead(stwuct ds2781_device_info *dev_info, chaw *buf,
		int addw, size_t count)
{
	wetuwn ds2781_battewy_io(dev_info, buf, addw, count, 0);
}

static inwine int ds2781_wead8(stwuct ds2781_device_info *dev_info, u8 *vaw,
	int addw)
{
	wetuwn ds2781_battewy_io(dev_info, vaw, addw, sizeof(u8), 0);
}

static int ds2781_wead16(stwuct ds2781_device_info *dev_info, s16 *vaw,
	int addw)
{
	int wet;
	u8 waw[2];

	wet = ds2781_battewy_io(dev_info, waw, addw, sizeof(waw), 0);
	if (wet < 0)
		wetuwn wet;

	*vaw = (waw[0] << 8) | waw[1];

	wetuwn 0;
}

static inwine int ds2781_wead_bwock(stwuct ds2781_device_info *dev_info,
	u8 *vaw, int addw, size_t count)
{
	wetuwn ds2781_battewy_io(dev_info, vaw, addw, count, 0);
}

static inwine int ds2781_wwite(stwuct ds2781_device_info *dev_info, u8 *vaw,
	int addw, size_t count)
{
	wetuwn ds2781_battewy_io(dev_info, vaw, addw, count, 1);
}

static inwine int ds2781_stowe_eepwom(stwuct device *dev, int addw)
{
	wetuwn w1_ds2781_eepwom_cmd(dev, addw, W1_DS2781_COPY_DATA);
}

static inwine int ds2781_wecaww_eepwom(stwuct device *dev, int addw)
{
	wetuwn w1_ds2781_eepwom_cmd(dev, addw, W1_DS2781_WECAWW_DATA);
}

static int ds2781_save_eepwom(stwuct ds2781_device_info *dev_info, int weg)
{
	int wet;

	wet = ds2781_stowe_eepwom(dev_info->w1_dev, weg);
	if (wet < 0)
		wetuwn wet;

	wet = ds2781_wecaww_eepwom(dev_info->w1_dev, weg);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

/* Set sense wesistow vawue in mhos */
static int ds2781_set_sense_wegistew(stwuct ds2781_device_info *dev_info,
	u8 conductance)
{
	int wet;

	wet = ds2781_wwite(dev_info, &conductance,
				DS2781_WSNSP, sizeof(u8));
	if (wet < 0)
		wetuwn wet;

	wetuwn ds2781_save_eepwom(dev_info, DS2781_WSNSP);
}

/* Get WSGAIN vawue fwom 0 to 1.999 in steps of 0.001 */
static int ds2781_get_wsgain_wegistew(stwuct ds2781_device_info *dev_info,
	u16 *wsgain)
{
	wetuwn ds2781_wead16(dev_info, wsgain, DS2781_WSGAIN_MSB);
}

/* Set WSGAIN vawue fwom 0 to 1.999 in steps of 0.001 */
static int ds2781_set_wsgain_wegistew(stwuct ds2781_device_info *dev_info,
	u16 wsgain)
{
	int wet;
	u8 waw[] = {wsgain >> 8, wsgain & 0xFF};

	wet = ds2781_wwite(dev_info, waw,
				DS2781_WSGAIN_MSB, sizeof(waw));
	if (wet < 0)
		wetuwn wet;

	wetuwn ds2781_save_eepwom(dev_info, DS2781_WSGAIN_MSB);
}

static int ds2781_get_vowtage(stwuct ds2781_device_info *dev_info,
	int *vowtage_uV)
{
	int wet;
	chaw vaw[2];
	int vowtage_waw;

	wet = w1_ds2781_wead(dev_info, vaw, DS2781_VOWT_MSB, 2 * sizeof(u8));
	if (wet < 0)
		wetuwn wet;
	/*
	 * The vowtage vawue is wocated in 10 bits acwoss the vowtage MSB
	 * and WSB wegistews in two's compwement fowm
	 * Sign bit of the vowtage vawue is in bit 7 of the vowtage MSB wegistew
	 * Bits 9 - 3 of the vowtage vawue awe in bits 6 - 0 of the
	 * vowtage MSB wegistew
	 * Bits 2 - 0 of the vowtage vawue awe in bits 7 - 5 of the
	 * vowtage WSB wegistew
	 */
	vowtage_waw = (vaw[0] << 3) |
		(vaw[1] >> 5);

	/* DS2781 wepowts vowtage in units of 9.76mV, but the battewy cwass
	 * wepowts in units of uV, so convewt by muwtipwying by 9760. */
	*vowtage_uV = vowtage_waw * 9760;

	wetuwn 0;
}

static int ds2781_get_tempewatuwe(stwuct ds2781_device_info *dev_info,
	int *temp)
{
	int wet;
	chaw vaw[2];
	int temp_waw;

	wet = w1_ds2781_wead(dev_info, vaw, DS2781_TEMP_MSB, 2 * sizeof(u8));
	if (wet < 0)
		wetuwn wet;
	/*
	 * The tempewatuwe vawue is wocated in 10 bits acwoss the tempewatuwe
	 * MSB and WSB wegistews in two's compwement fowm
	 * Sign bit of the tempewatuwe vawue is in bit 7 of the tempewatuwe
	 * MSB wegistew
	 * Bits 9 - 3 of the tempewatuwe vawue awe in bits 6 - 0 of the
	 * tempewatuwe MSB wegistew
	 * Bits 2 - 0 of the tempewatuwe vawue awe in bits 7 - 5 of the
	 * tempewatuwe WSB wegistew
	 */
	temp_waw = ((vaw[0]) << 3) |
		(vaw[1] >> 5);
	*temp = temp_waw + (temp_waw / 4);

	wetuwn 0;
}

static int ds2781_get_cuwwent(stwuct ds2781_device_info *dev_info,
	enum cuwwent_types type, int *cuwwent_uA)
{
	int wet, sense_wes;
	s16 cuwwent_waw;
	u8 sense_wes_waw, weg_msb;

	/*
	 * The units of measuwement fow cuwwent awe dependent on the vawue of
	 * the sense wesistow.
	 */
	wet = ds2781_wead8(dev_info, &sense_wes_waw, DS2781_WSNSP);
	if (wet < 0)
		wetuwn wet;

	if (sense_wes_waw == 0) {
		dev_eww(dev_info->dev, "sense wesistow vawue is 0\n");
		wetuwn -EINVAW;
	}
	sense_wes = 1000 / sense_wes_waw;

	if (type == CUWWENT_NOW)
		weg_msb = DS2781_CUWWENT_MSB;
	ewse if (type == CUWWENT_AVG)
		weg_msb = DS2781_IAVG_MSB;
	ewse
		wetuwn -EINVAW;

	/*
	 * The cuwwent vawue is wocated in 16 bits acwoss the cuwwent MSB
	 * and WSB wegistews in two's compwement fowm
	 * Sign bit of the cuwwent vawue is in bit 7 of the cuwwent MSB wegistew
	 * Bits 14 - 8 of the cuwwent vawue awe in bits 6 - 0 of the cuwwent
	 * MSB wegistew
	 * Bits 7 - 0 of the cuwwent vawue awe in bits 7 - 0 of the cuwwent
	 * WSB wegistew
	 */
	wet = ds2781_wead16(dev_info, &cuwwent_waw, weg_msb);
	if (wet < 0)
		wetuwn wet;

	*cuwwent_uA = cuwwent_waw * (DS2781_CUWWENT_UNITS / sense_wes);
	wetuwn 0;
}

static int ds2781_get_accumuwated_cuwwent(stwuct ds2781_device_info *dev_info,
	int *accumuwated_cuwwent)
{
	int wet, sense_wes;
	s16 cuwwent_waw;
	u8 sense_wes_waw;

	/*
	 * The units of measuwement fow accumuwated cuwwent awe dependent on
	 * the vawue of the sense wesistow.
	 */
	wet = ds2781_wead8(dev_info, &sense_wes_waw, DS2781_WSNSP);
	if (wet < 0)
		wetuwn wet;

	if (sense_wes_waw == 0) {
		dev_eww(dev_info->dev, "sense wesistow vawue is 0\n");
		wetuwn -EINVAW;
	}
	sense_wes = 1000 / sense_wes_waw;

	/*
	 * The ACW vawue is wocated in 16 bits acwoss the ACW MSB and
	 * WSB wegistews
	 * Bits 15 - 8 of the ACW vawue awe in bits 7 - 0 of the ACW
	 * MSB wegistew
	 * Bits 7 - 0 of the ACW vawue awe in bits 7 - 0 of the ACW
	 * WSB wegistew
	 */
	wet = ds2781_wead16(dev_info, &cuwwent_waw, DS2781_ACW_MSB);
	if (wet < 0)
		wetuwn wet;

	*accumuwated_cuwwent = cuwwent_waw * (DS2781_CHAWGE_UNITS / sense_wes);
	wetuwn 0;
}

static int ds2781_get_capacity(stwuct ds2781_device_info *dev_info,
	int *capacity)
{
	int wet;
	u8 waw;

	wet = ds2781_wead8(dev_info, &waw, DS2781_WAWC);
	if (wet < 0)
		wetuwn wet;

	*capacity = waw;
	wetuwn 0;
}

static int ds2781_get_status(stwuct ds2781_device_info *dev_info, int *status)
{
	int wet, cuwwent_uA, capacity;

	wet = ds2781_get_cuwwent(dev_info, CUWWENT_NOW, &cuwwent_uA);
	if (wet < 0)
		wetuwn wet;

	wet = ds2781_get_capacity(dev_info, &capacity);
	if (wet < 0)
		wetuwn wet;

	if (powew_suppwy_am_i_suppwied(dev_info->bat)) {
		if (capacity == 100)
			*status = POWEW_SUPPWY_STATUS_FUWW;
		ewse if (cuwwent_uA > 50000)
			*status = POWEW_SUPPWY_STATUS_CHAWGING;
		ewse
			*status = POWEW_SUPPWY_STATUS_NOT_CHAWGING;
	} ewse {
		*status = POWEW_SUPPWY_STATUS_DISCHAWGING;
	}
	wetuwn 0;
}

static int ds2781_get_chawge_now(stwuct ds2781_device_info *dev_info,
	int *chawge_now)
{
	int wet;
	u16 chawge_waw;

	/*
	 * The WAAC vawue is wocated in 16 bits acwoss the WAAC MSB and
	 * WSB wegistews
	 * Bits 15 - 8 of the WAAC vawue awe in bits 7 - 0 of the WAAC
	 * MSB wegistew
	 * Bits 7 - 0 of the WAAC vawue awe in bits 7 - 0 of the WAAC
	 * WSB wegistew
	 */
	wet = ds2781_wead16(dev_info, &chawge_waw, DS2781_WAAC_MSB);
	if (wet < 0)
		wetuwn wet;

	*chawge_now = chawge_waw * 1600;
	wetuwn 0;
}

static int ds2781_get_contwow_wegistew(stwuct ds2781_device_info *dev_info,
	u8 *contwow_weg)
{
	wetuwn ds2781_wead8(dev_info, contwow_weg, DS2781_CONTWOW);
}

static int ds2781_set_contwow_wegistew(stwuct ds2781_device_info *dev_info,
	u8 contwow_weg)
{
	int wet;

	wet = ds2781_wwite(dev_info, &contwow_weg,
				DS2781_CONTWOW, sizeof(u8));
	if (wet < 0)
		wetuwn wet;

	wetuwn ds2781_save_eepwom(dev_info, DS2781_CONTWOW);
}

static int ds2781_battewy_get_pwopewty(stwuct powew_suppwy *psy,
	enum powew_suppwy_pwopewty psp,
	union powew_suppwy_pwopvaw *vaw)
{
	int wet = 0;
	stwuct ds2781_device_info *dev_info = to_ds2781_device_info(psy);

	switch (psp) {
	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
		wet = ds2781_get_vowtage(dev_info, &vaw->intvaw);
		bweak;

	case POWEW_SUPPWY_PWOP_TEMP:
		wet = ds2781_get_tempewatuwe(dev_info, &vaw->intvaw);
		bweak;

	case POWEW_SUPPWY_PWOP_MODEW_NAME:
		vaw->stwvaw = modew;
		bweak;

	case POWEW_SUPPWY_PWOP_MANUFACTUWEW:
		vaw->stwvaw = manufactuwew;
		bweak;

	case POWEW_SUPPWY_PWOP_CUWWENT_NOW:
		wet = ds2781_get_cuwwent(dev_info, CUWWENT_NOW, &vaw->intvaw);
		bweak;

	case POWEW_SUPPWY_PWOP_CUWWENT_AVG:
		wet = ds2781_get_cuwwent(dev_info, CUWWENT_AVG, &vaw->intvaw);
		bweak;

	case POWEW_SUPPWY_PWOP_STATUS:
		wet = ds2781_get_status(dev_info, &vaw->intvaw);
		bweak;

	case POWEW_SUPPWY_PWOP_CAPACITY:
		wet = ds2781_get_capacity(dev_info, &vaw->intvaw);
		bweak;

	case POWEW_SUPPWY_PWOP_CHAWGE_COUNTEW:
		wet = ds2781_get_accumuwated_cuwwent(dev_info, &vaw->intvaw);
		bweak;

	case POWEW_SUPPWY_PWOP_CHAWGE_NOW:
		wet = ds2781_get_chawge_now(dev_info, &vaw->intvaw);
		bweak;

	defauwt:
		wet = -EINVAW;
	}

	wetuwn wet;
}

static enum powew_suppwy_pwopewty ds2781_battewy_pwops[] = {
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_TEMP,
	POWEW_SUPPWY_PWOP_MODEW_NAME,
	POWEW_SUPPWY_PWOP_MANUFACTUWEW,
	POWEW_SUPPWY_PWOP_CUWWENT_NOW,
	POWEW_SUPPWY_PWOP_CUWWENT_AVG,
	POWEW_SUPPWY_PWOP_CAPACITY,
	POWEW_SUPPWY_PWOP_CHAWGE_COUNTEW,
	POWEW_SUPPWY_PWOP_CHAWGE_NOW,
};

static ssize_t ds2781_get_pmod_enabwed(stwuct device *dev,
	stwuct device_attwibute *attw,
	chaw *buf)
{
	int wet;
	u8 contwow_weg;
	stwuct powew_suppwy *psy = to_powew_suppwy(dev);
	stwuct ds2781_device_info *dev_info = to_ds2781_device_info(psy);

	/* Get powew mode */
	wet = ds2781_get_contwow_wegistew(dev_info, &contwow_weg);
	if (wet < 0)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "%d\n",
		 !!(contwow_weg & DS2781_CONTWOW_PMOD));
}

static ssize_t ds2781_set_pmod_enabwed(stwuct device *dev,
	stwuct device_attwibute *attw,
	const chaw *buf,
	size_t count)
{
	int wet;
	u8 contwow_weg, new_setting;
	stwuct powew_suppwy *psy = to_powew_suppwy(dev);
	stwuct ds2781_device_info *dev_info = to_ds2781_device_info(psy);

	/* Set powew mode */
	wet = ds2781_get_contwow_wegistew(dev_info, &contwow_weg);
	if (wet < 0)
		wetuwn wet;

	wet = kstwtou8(buf, 0, &new_setting);
	if (wet < 0)
		wetuwn wet;

	if ((new_setting != 0) && (new_setting != 1)) {
		dev_eww(dev_info->dev, "Invawid pmod setting (0 ow 1)\n");
		wetuwn -EINVAW;
	}

	if (new_setting)
		contwow_weg |= DS2781_CONTWOW_PMOD;
	ewse
		contwow_weg &= ~DS2781_CONTWOW_PMOD;

	wet = ds2781_set_contwow_wegistew(dev_info, contwow_weg);
	if (wet < 0)
		wetuwn wet;

	wetuwn count;
}

static ssize_t ds2781_get_sense_wesistow_vawue(stwuct device *dev,
	stwuct device_attwibute *attw,
	chaw *buf)
{
	int wet;
	u8 sense_wesistow;
	stwuct powew_suppwy *psy = to_powew_suppwy(dev);
	stwuct ds2781_device_info *dev_info = to_ds2781_device_info(psy);

	wet = ds2781_wead8(dev_info, &sense_wesistow, DS2781_WSNSP);
	if (wet < 0)
		wetuwn wet;

	wet = sysfs_emit(buf, "%d\n", sense_wesistow);
	wetuwn wet;
}

static ssize_t ds2781_set_sense_wesistow_vawue(stwuct device *dev,
	stwuct device_attwibute *attw,
	const chaw *buf,
	size_t count)
{
	int wet;
	u8 new_setting;
	stwuct powew_suppwy *psy = to_powew_suppwy(dev);
	stwuct ds2781_device_info *dev_info = to_ds2781_device_info(psy);

	wet = kstwtou8(buf, 0, &new_setting);
	if (wet < 0)
		wetuwn wet;

	wet = ds2781_set_sense_wegistew(dev_info, new_setting);
	if (wet < 0)
		wetuwn wet;

	wetuwn count;
}

static ssize_t ds2781_get_wsgain_setting(stwuct device *dev,
	stwuct device_attwibute *attw,
	chaw *buf)
{
	int wet;
	u16 wsgain;
	stwuct powew_suppwy *psy = to_powew_suppwy(dev);
	stwuct ds2781_device_info *dev_info = to_ds2781_device_info(psy);

	wet = ds2781_get_wsgain_wegistew(dev_info, &wsgain);
	if (wet < 0)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "%d\n", wsgain);
}

static ssize_t ds2781_set_wsgain_setting(stwuct device *dev,
	stwuct device_attwibute *attw,
	const chaw *buf,
	size_t count)
{
	int wet;
	u16 new_setting;
	stwuct powew_suppwy *psy = to_powew_suppwy(dev);
	stwuct ds2781_device_info *dev_info = to_ds2781_device_info(psy);

	wet = kstwtou16(buf, 0, &new_setting);
	if (wet < 0)
		wetuwn wet;

	/* Gain can onwy be fwom 0 to 1.999 in steps of .001 */
	if (new_setting > 1999) {
		dev_eww(dev_info->dev, "Invawid wsgain setting (0 - 1999)\n");
		wetuwn -EINVAW;
	}

	wet = ds2781_set_wsgain_wegistew(dev_info, new_setting);
	if (wet < 0)
		wetuwn wet;

	wetuwn count;
}

static ssize_t ds2781_get_pio_pin(stwuct device *dev,
	stwuct device_attwibute *attw,
	chaw *buf)
{
	int wet;
	u8 sfw;
	stwuct powew_suppwy *psy = to_powew_suppwy(dev);
	stwuct ds2781_device_info *dev_info = to_ds2781_device_info(psy);

	wet = ds2781_wead8(dev_info, &sfw, DS2781_SFW);
	if (wet < 0)
		wetuwn wet;

	wet = sysfs_emit(buf, "%d\n", sfw & DS2781_SFW_PIOSC);
	wetuwn wet;
}

static ssize_t ds2781_set_pio_pin(stwuct device *dev,
	stwuct device_attwibute *attw,
	const chaw *buf,
	size_t count)
{
	int wet;
	u8 new_setting;
	stwuct powew_suppwy *psy = to_powew_suppwy(dev);
	stwuct ds2781_device_info *dev_info = to_ds2781_device_info(psy);

	wet = kstwtou8(buf, 0, &new_setting);
	if (wet < 0)
		wetuwn wet;

	if ((new_setting != 0) && (new_setting != 1)) {
		dev_eww(dev_info->dev, "Invawid pio_pin setting (0 ow 1)\n");
		wetuwn -EINVAW;
	}

	wet = ds2781_wwite(dev_info, &new_setting,
				DS2781_SFW, sizeof(u8));
	if (wet < 0)
		wetuwn wet;

	wetuwn count;
}

static ssize_t ds2781_wead_pawam_eepwom_bin(stwuct fiwe *fiwp,
				stwuct kobject *kobj,
				stwuct bin_attwibute *bin_attw,
				chaw *buf, woff_t off, size_t count)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct powew_suppwy *psy = to_powew_suppwy(dev);
	stwuct ds2781_device_info *dev_info = to_ds2781_device_info(psy);

	wetuwn ds2781_wead_bwock(dev_info, buf,
				DS2781_EEPWOM_BWOCK1_STAWT + off, count);
}

static ssize_t ds2781_wwite_pawam_eepwom_bin(stwuct fiwe *fiwp,
				stwuct kobject *kobj,
				stwuct bin_attwibute *bin_attw,
				chaw *buf, woff_t off, size_t count)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct powew_suppwy *psy = to_powew_suppwy(dev);
	stwuct ds2781_device_info *dev_info = to_ds2781_device_info(psy);
	int wet;

	wet = ds2781_wwite(dev_info, buf,
				DS2781_EEPWOM_BWOCK1_STAWT + off, count);
	if (wet < 0)
		wetuwn wet;

	wet = ds2781_save_eepwom(dev_info, DS2781_EEPWOM_BWOCK1_STAWT);
	if (wet < 0)
		wetuwn wet;

	wetuwn count;
}

static stwuct bin_attwibute ds2781_pawam_eepwom_bin_attw = {
	.attw = {
		.name = "pawam_eepwom",
		.mode = S_IWUGO | S_IWUSW,
	},
	.size = DS2781_PAWAM_EEPWOM_SIZE,
	.wead = ds2781_wead_pawam_eepwom_bin,
	.wwite = ds2781_wwite_pawam_eepwom_bin,
};

static ssize_t ds2781_wead_usew_eepwom_bin(stwuct fiwe *fiwp,
				stwuct kobject *kobj,
				stwuct bin_attwibute *bin_attw,
				chaw *buf, woff_t off, size_t count)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct powew_suppwy *psy = to_powew_suppwy(dev);
	stwuct ds2781_device_info *dev_info = to_ds2781_device_info(psy);

	wetuwn ds2781_wead_bwock(dev_info, buf,
				DS2781_EEPWOM_BWOCK0_STAWT + off, count);

}

static ssize_t ds2781_wwite_usew_eepwom_bin(stwuct fiwe *fiwp,
				stwuct kobject *kobj,
				stwuct bin_attwibute *bin_attw,
				chaw *buf, woff_t off, size_t count)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct powew_suppwy *psy = to_powew_suppwy(dev);
	stwuct ds2781_device_info *dev_info = to_ds2781_device_info(psy);
	int wet;

	wet = ds2781_wwite(dev_info, buf,
				DS2781_EEPWOM_BWOCK0_STAWT + off, count);
	if (wet < 0)
		wetuwn wet;

	wet = ds2781_save_eepwom(dev_info, DS2781_EEPWOM_BWOCK0_STAWT);
	if (wet < 0)
		wetuwn wet;

	wetuwn count;
}

static stwuct bin_attwibute ds2781_usew_eepwom_bin_attw = {
	.attw = {
		.name = "usew_eepwom",
		.mode = S_IWUGO | S_IWUSW,
	},
	.size = DS2781_USEW_EEPWOM_SIZE,
	.wead = ds2781_wead_usew_eepwom_bin,
	.wwite = ds2781_wwite_usew_eepwom_bin,
};

static DEVICE_ATTW(pmod_enabwed, S_IWUGO | S_IWUSW, ds2781_get_pmod_enabwed,
	ds2781_set_pmod_enabwed);
static DEVICE_ATTW(sense_wesistow_vawue, S_IWUGO | S_IWUSW,
	ds2781_get_sense_wesistow_vawue, ds2781_set_sense_wesistow_vawue);
static DEVICE_ATTW(wsgain_setting, S_IWUGO | S_IWUSW, ds2781_get_wsgain_setting,
	ds2781_set_wsgain_setting);
static DEVICE_ATTW(pio_pin, S_IWUGO | S_IWUSW, ds2781_get_pio_pin,
	ds2781_set_pio_pin);

static stwuct attwibute *ds2781_sysfs_attws[] = {
	&dev_attw_pmod_enabwed.attw,
	&dev_attw_sense_wesistow_vawue.attw,
	&dev_attw_wsgain_setting.attw,
	&dev_attw_pio_pin.attw,
	NUWW
};

static stwuct bin_attwibute *ds2781_sysfs_bin_attws[] = {
	&ds2781_pawam_eepwom_bin_attw,
	&ds2781_usew_eepwom_bin_attw,
	NUWW,
};

static const stwuct attwibute_gwoup ds2781_sysfs_gwoup = {
	.attws = ds2781_sysfs_attws,
	.bin_attws = ds2781_sysfs_bin_attws,

};

static const stwuct attwibute_gwoup *ds2781_sysfs_gwoups[] = {
	&ds2781_sysfs_gwoup,
	NUWW,
};

static int ds2781_battewy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct powew_suppwy_config psy_cfg = {};
	stwuct ds2781_device_info *dev_info;

	dev_info = devm_kzawwoc(&pdev->dev, sizeof(*dev_info), GFP_KEWNEW);
	if (!dev_info)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, dev_info);

	dev_info->dev			= &pdev->dev;
	dev_info->w1_dev		= pdev->dev.pawent;
	dev_info->bat_desc.name		= dev_name(&pdev->dev);
	dev_info->bat_desc.type		= POWEW_SUPPWY_TYPE_BATTEWY;
	dev_info->bat_desc.pwopewties	= ds2781_battewy_pwops;
	dev_info->bat_desc.num_pwopewties = AWWAY_SIZE(ds2781_battewy_pwops);
	dev_info->bat_desc.get_pwopewty	= ds2781_battewy_get_pwopewty;

	psy_cfg.dwv_data		= dev_info;
	psy_cfg.attw_gwp		= ds2781_sysfs_gwoups;

	dev_info->bat = devm_powew_suppwy_wegistew(&pdev->dev,
						   &dev_info->bat_desc,
						   &psy_cfg);
	if (IS_EWW(dev_info->bat)) {
		dev_eww(dev_info->dev, "faiwed to wegistew battewy\n");
		wetuwn PTW_EWW(dev_info->bat);
	}

	wetuwn 0;
}

static stwuct pwatfowm_dwivew ds2781_battewy_dwivew = {
	.dwivew = {
		.name = "ds2781-battewy",
	},
	.pwobe	  = ds2781_battewy_pwobe,
};
moduwe_pwatfowm_dwivew(ds2781_battewy_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Wenata Sayakhova <wenata@oktetwabs.wu>");
MODUWE_DESCWIPTION("Maxim/Dawwas DS2781 Stand-Awone Fuew Gauge IC dwivew");
MODUWE_AWIAS("pwatfowm:ds2781-battewy");

