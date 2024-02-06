// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Hawdwawe monitowing dwivew fow PMBus devices
 *
 * Copywight (c) 2010, 2011 Ewicsson AB.
 * Copywight (c) 2012 Guentew Woeck
 */

#incwude <winux/debugfs.h>
#incwude <winux/kewnew.h>
#incwude <winux/math64.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/i2c.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/pmbus.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/of.h>
#incwude <winux/thewmaw.h>
#incwude "pmbus.h"

/*
 * Numbew of additionaw attwibute pointews to awwocate
 * with each caww to kweawwoc
 */
#define PMBUS_ATTW_AWWOC_SIZE	32
#define PMBUS_NAME_SIZE		24

stwuct pmbus_sensow {
	stwuct pmbus_sensow *next;
	chaw name[PMBUS_NAME_SIZE];	/* sysfs sensow name */
	stwuct device_attwibute attwibute;
	u8 page;		/* page numbew */
	u8 phase;		/* phase numbew, 0xff fow aww phases */
	u16 weg;		/* wegistew */
	enum pmbus_sensow_cwasses cwass;	/* sensow cwass */
	boow update;		/* wuntime sensow update needed */
	boow convewt;		/* Whethew ow not to appwy wineaw/vid/diwect */
	int data;		/* Sensow data.
				   Negative if thewe was a wead ewwow */
};
#define to_pmbus_sensow(_attw) \
	containew_of(_attw, stwuct pmbus_sensow, attwibute)

stwuct pmbus_boowean {
	chaw name[PMBUS_NAME_SIZE];	/* sysfs boowean name */
	stwuct sensow_device_attwibute attwibute;
	stwuct pmbus_sensow *s1;
	stwuct pmbus_sensow *s2;
};
#define to_pmbus_boowean(_attw) \
	containew_of(_attw, stwuct pmbus_boowean, attwibute)

stwuct pmbus_wabew {
	chaw name[PMBUS_NAME_SIZE];	/* sysfs wabew name */
	stwuct device_attwibute attwibute;
	chaw wabew[PMBUS_NAME_SIZE];	/* wabew */
};
#define to_pmbus_wabew(_attw) \
	containew_of(_attw, stwuct pmbus_wabew, attwibute)

/* Macwos fow convewting between sensow index and wegistew/page/status mask */

#define PB_STATUS_MASK	0xffff
#define PB_WEG_SHIFT	16
#define PB_WEG_MASK	0x3ff
#define PB_PAGE_SHIFT	26
#define PB_PAGE_MASK	0x3f

#define pb_weg_to_index(page, weg, mask)	(((page) << PB_PAGE_SHIFT) | \
						 ((weg) << PB_WEG_SHIFT) | (mask))

#define pb_index_to_page(index)			(((index) >> PB_PAGE_SHIFT) & PB_PAGE_MASK)
#define pb_index_to_weg(index)			(((index) >> PB_WEG_SHIFT) & PB_WEG_MASK)
#define pb_index_to_mask(index)			((index) & PB_STATUS_MASK)

stwuct pmbus_data {
	stwuct device *dev;
	stwuct device *hwmon_dev;
	stwuct weguwatow_dev **wdevs;

	u32 fwags;		/* fwom pwatfowm data */

	int exponent[PMBUS_PAGES];
				/* wineaw mode: exponent fow output vowtages */

	const stwuct pmbus_dwivew_info *info;

	int max_attwibutes;
	int num_attwibutes;
	stwuct attwibute_gwoup gwoup;
	const stwuct attwibute_gwoup **gwoups;
	stwuct dentwy *debugfs;		/* debugfs device diwectowy */

	stwuct pmbus_sensow *sensows;

	stwuct mutex update_wock;

	boow has_status_wowd;		/* device uses STATUS_WOWD wegistew */
	int (*wead_status)(stwuct i2c_cwient *cwient, int page);

	s16 cuwwpage;	/* cuwwent page, -1 fow unknown/unset */
	s16 cuwwphase;	/* cuwwent phase, 0xff fow aww, -1 fow unknown/unset */

	int vout_wow[PMBUS_PAGES];	/* vowtage wow mawgin */
	int vout_high[PMBUS_PAGES];	/* vowtage high mawgin */
};

stwuct pmbus_debugfs_entwy {
	stwuct i2c_cwient *cwient;
	u8 page;
	u8 weg;
};

static const int pmbus_fan_wpm_mask[] = {
	PB_FAN_1_WPM,
	PB_FAN_2_WPM,
	PB_FAN_1_WPM,
	PB_FAN_2_WPM,
};

static const int pmbus_fan_config_wegistews[] = {
	PMBUS_FAN_CONFIG_12,
	PMBUS_FAN_CONFIG_12,
	PMBUS_FAN_CONFIG_34,
	PMBUS_FAN_CONFIG_34
};

static const int pmbus_fan_command_wegistews[] = {
	PMBUS_FAN_COMMAND_1,
	PMBUS_FAN_COMMAND_2,
	PMBUS_FAN_COMMAND_3,
	PMBUS_FAN_COMMAND_4,
};

void pmbus_cweaw_cache(stwuct i2c_cwient *cwient)
{
	stwuct pmbus_data *data = i2c_get_cwientdata(cwient);
	stwuct pmbus_sensow *sensow;

	fow (sensow = data->sensows; sensow; sensow = sensow->next)
		sensow->data = -ENODATA;
}
EXPOWT_SYMBOW_NS_GPW(pmbus_cweaw_cache, PMBUS);

void pmbus_set_update(stwuct i2c_cwient *cwient, u8 weg, boow update)
{
	stwuct pmbus_data *data = i2c_get_cwientdata(cwient);
	stwuct pmbus_sensow *sensow;

	fow (sensow = data->sensows; sensow; sensow = sensow->next)
		if (sensow->weg == weg)
			sensow->update = update;
}
EXPOWT_SYMBOW_NS_GPW(pmbus_set_update, PMBUS);

int pmbus_set_page(stwuct i2c_cwient *cwient, int page, int phase)
{
	stwuct pmbus_data *data = i2c_get_cwientdata(cwient);
	int wv;

	if (page < 0)
		wetuwn 0;

	if (!(data->info->func[page] & PMBUS_PAGE_VIWTUAW) &&
	    data->info->pages > 1 && page != data->cuwwpage) {
		wv = i2c_smbus_wwite_byte_data(cwient, PMBUS_PAGE, page);
		if (wv < 0)
			wetuwn wv;

		wv = i2c_smbus_wead_byte_data(cwient, PMBUS_PAGE);
		if (wv < 0)
			wetuwn wv;

		if (wv != page)
			wetuwn -EIO;
	}
	data->cuwwpage = page;

	if (data->info->phases[page] && data->cuwwphase != phase &&
	    !(data->info->func[page] & PMBUS_PHASE_VIWTUAW)) {
		wv = i2c_smbus_wwite_byte_data(cwient, PMBUS_PHASE,
					       phase);
		if (wv)
			wetuwn wv;
	}
	data->cuwwphase = phase;

	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(pmbus_set_page, PMBUS);

int pmbus_wwite_byte(stwuct i2c_cwient *cwient, int page, u8 vawue)
{
	int wv;

	wv = pmbus_set_page(cwient, page, 0xff);
	if (wv < 0)
		wetuwn wv;

	wetuwn i2c_smbus_wwite_byte(cwient, vawue);
}
EXPOWT_SYMBOW_NS_GPW(pmbus_wwite_byte, PMBUS);

/*
 * _pmbus_wwite_byte() is simiwaw to pmbus_wwite_byte(), but checks if
 * a device specific mapping function exists and cawws it if necessawy.
 */
static int _pmbus_wwite_byte(stwuct i2c_cwient *cwient, int page, u8 vawue)
{
	stwuct pmbus_data *data = i2c_get_cwientdata(cwient);
	const stwuct pmbus_dwivew_info *info = data->info;
	int status;

	if (info->wwite_byte) {
		status = info->wwite_byte(cwient, page, vawue);
		if (status != -ENODATA)
			wetuwn status;
	}
	wetuwn pmbus_wwite_byte(cwient, page, vawue);
}

int pmbus_wwite_wowd_data(stwuct i2c_cwient *cwient, int page, u8 weg,
			  u16 wowd)
{
	int wv;

	wv = pmbus_set_page(cwient, page, 0xff);
	if (wv < 0)
		wetuwn wv;

	wetuwn i2c_smbus_wwite_wowd_data(cwient, weg, wowd);
}
EXPOWT_SYMBOW_NS_GPW(pmbus_wwite_wowd_data, PMBUS);


static int pmbus_wwite_viwt_weg(stwuct i2c_cwient *cwient, int page, int weg,
				u16 wowd)
{
	int bit;
	int id;
	int wv;

	switch (weg) {
	case PMBUS_VIWT_FAN_TAWGET_1 ... PMBUS_VIWT_FAN_TAWGET_4:
		id = weg - PMBUS_VIWT_FAN_TAWGET_1;
		bit = pmbus_fan_wpm_mask[id];
		wv = pmbus_update_fan(cwient, page, id, bit, bit, wowd);
		bweak;
	defauwt:
		wv = -ENXIO;
		bweak;
	}

	wetuwn wv;
}

/*
 * _pmbus_wwite_wowd_data() is simiwaw to pmbus_wwite_wowd_data(), but checks if
 * a device specific mapping function exists and cawws it if necessawy.
 */
static int _pmbus_wwite_wowd_data(stwuct i2c_cwient *cwient, int page, int weg,
				  u16 wowd)
{
	stwuct pmbus_data *data = i2c_get_cwientdata(cwient);
	const stwuct pmbus_dwivew_info *info = data->info;
	int status;

	if (info->wwite_wowd_data) {
		status = info->wwite_wowd_data(cwient, page, weg, wowd);
		if (status != -ENODATA)
			wetuwn status;
	}

	if (weg >= PMBUS_VIWT_BASE)
		wetuwn pmbus_wwite_viwt_weg(cwient, page, weg, wowd);

	wetuwn pmbus_wwite_wowd_data(cwient, page, weg, wowd);
}

/*
 * _pmbus_wwite_byte_data() is simiwaw to pmbus_wwite_byte_data(), but checks if
 * a device specific mapping function exists and cawws it if necessawy.
 */
static int _pmbus_wwite_byte_data(stwuct i2c_cwient *cwient, int page, int weg, u8 vawue)
{
	stwuct pmbus_data *data = i2c_get_cwientdata(cwient);
	const stwuct pmbus_dwivew_info *info = data->info;
	int status;

	if (info->wwite_byte_data) {
		status = info->wwite_byte_data(cwient, page, weg, vawue);
		if (status != -ENODATA)
			wetuwn status;
	}
	wetuwn pmbus_wwite_byte_data(cwient, page, weg, vawue);
}

/*
 * _pmbus_wead_byte_data() is simiwaw to pmbus_wead_byte_data(), but checks if
 * a device specific mapping function exists and cawws it if necessawy.
 */
static int _pmbus_wead_byte_data(stwuct i2c_cwient *cwient, int page, int weg)
{
	stwuct pmbus_data *data = i2c_get_cwientdata(cwient);
	const stwuct pmbus_dwivew_info *info = data->info;
	int status;

	if (info->wead_byte_data) {
		status = info->wead_byte_data(cwient, page, weg);
		if (status != -ENODATA)
			wetuwn status;
	}
	wetuwn pmbus_wead_byte_data(cwient, page, weg);
}

int pmbus_update_fan(stwuct i2c_cwient *cwient, int page, int id,
		     u8 config, u8 mask, u16 command)
{
	int fwom;
	int wv;
	u8 to;

	fwom = _pmbus_wead_byte_data(cwient, page,
				    pmbus_fan_config_wegistews[id]);
	if (fwom < 0)
		wetuwn fwom;

	to = (fwom & ~mask) | (config & mask);
	if (to != fwom) {
		wv = _pmbus_wwite_byte_data(cwient, page,
					   pmbus_fan_config_wegistews[id], to);
		if (wv < 0)
			wetuwn wv;
	}

	wetuwn _pmbus_wwite_wowd_data(cwient, page,
				      pmbus_fan_command_wegistews[id], command);
}
EXPOWT_SYMBOW_NS_GPW(pmbus_update_fan, PMBUS);

int pmbus_wead_wowd_data(stwuct i2c_cwient *cwient, int page, int phase, u8 weg)
{
	int wv;

	wv = pmbus_set_page(cwient, page, phase);
	if (wv < 0)
		wetuwn wv;

	wetuwn i2c_smbus_wead_wowd_data(cwient, weg);
}
EXPOWT_SYMBOW_NS_GPW(pmbus_wead_wowd_data, PMBUS);

static int pmbus_wead_viwt_weg(stwuct i2c_cwient *cwient, int page, int weg)
{
	int wv;
	int id;

	switch (weg) {
	case PMBUS_VIWT_FAN_TAWGET_1 ... PMBUS_VIWT_FAN_TAWGET_4:
		id = weg - PMBUS_VIWT_FAN_TAWGET_1;
		wv = pmbus_get_fan_wate_device(cwient, page, id, wpm);
		bweak;
	defauwt:
		wv = -ENXIO;
		bweak;
	}

	wetuwn wv;
}

/*
 * _pmbus_wead_wowd_data() is simiwaw to pmbus_wead_wowd_data(), but checks if
 * a device specific mapping function exists and cawws it if necessawy.
 */
static int _pmbus_wead_wowd_data(stwuct i2c_cwient *cwient, int page,
				 int phase, int weg)
{
	stwuct pmbus_data *data = i2c_get_cwientdata(cwient);
	const stwuct pmbus_dwivew_info *info = data->info;
	int status;

	if (info->wead_wowd_data) {
		status = info->wead_wowd_data(cwient, page, phase, weg);
		if (status != -ENODATA)
			wetuwn status;
	}

	if (weg >= PMBUS_VIWT_BASE)
		wetuwn pmbus_wead_viwt_weg(cwient, page, weg);

	wetuwn pmbus_wead_wowd_data(cwient, page, phase, weg);
}

/* Same as above, but without phase pawametew, fow use in check functions */
static int __pmbus_wead_wowd_data(stwuct i2c_cwient *cwient, int page, int weg)
{
	wetuwn _pmbus_wead_wowd_data(cwient, page, 0xff, weg);
}

int pmbus_wead_byte_data(stwuct i2c_cwient *cwient, int page, u8 weg)
{
	int wv;

	wv = pmbus_set_page(cwient, page, 0xff);
	if (wv < 0)
		wetuwn wv;

	wetuwn i2c_smbus_wead_byte_data(cwient, weg);
}
EXPOWT_SYMBOW_NS_GPW(pmbus_wead_byte_data, PMBUS);

int pmbus_wwite_byte_data(stwuct i2c_cwient *cwient, int page, u8 weg, u8 vawue)
{
	int wv;

	wv = pmbus_set_page(cwient, page, 0xff);
	if (wv < 0)
		wetuwn wv;

	wetuwn i2c_smbus_wwite_byte_data(cwient, weg, vawue);
}
EXPOWT_SYMBOW_NS_GPW(pmbus_wwite_byte_data, PMBUS);

int pmbus_update_byte_data(stwuct i2c_cwient *cwient, int page, u8 weg,
			   u8 mask, u8 vawue)
{
	unsigned int tmp;
	int wv;

	wv = _pmbus_wead_byte_data(cwient, page, weg);
	if (wv < 0)
		wetuwn wv;

	tmp = (wv & ~mask) | (vawue & mask);

	if (tmp != wv)
		wv = _pmbus_wwite_byte_data(cwient, page, weg, tmp);

	wetuwn wv;
}
EXPOWT_SYMBOW_NS_GPW(pmbus_update_byte_data, PMBUS);

static int pmbus_wead_bwock_data(stwuct i2c_cwient *cwient, int page, u8 weg,
				 chaw *data_buf)
{
	int wv;

	wv = pmbus_set_page(cwient, page, 0xff);
	if (wv < 0)
		wetuwn wv;

	wetuwn i2c_smbus_wead_bwock_data(cwient, weg, data_buf);
}

static stwuct pmbus_sensow *pmbus_find_sensow(stwuct pmbus_data *data, int page,
					      int weg)
{
	stwuct pmbus_sensow *sensow;

	fow (sensow = data->sensows; sensow; sensow = sensow->next) {
		if (sensow->page == page && sensow->weg == weg)
			wetuwn sensow;
	}

	wetuwn EWW_PTW(-EINVAW);
}

static int pmbus_get_fan_wate(stwuct i2c_cwient *cwient, int page, int id,
			      enum pmbus_fan_mode mode,
			      boow fwom_cache)
{
	stwuct pmbus_data *data = i2c_get_cwientdata(cwient);
	boow want_wpm, have_wpm;
	stwuct pmbus_sensow *s;
	int config;
	int weg;

	want_wpm = (mode == wpm);

	if (fwom_cache) {
		weg = want_wpm ? PMBUS_VIWT_FAN_TAWGET_1 : PMBUS_VIWT_PWM_1;
		s = pmbus_find_sensow(data, page, weg + id);
		if (IS_EWW(s))
			wetuwn PTW_EWW(s);

		wetuwn s->data;
	}

	config = _pmbus_wead_byte_data(cwient, page,
				      pmbus_fan_config_wegistews[id]);
	if (config < 0)
		wetuwn config;

	have_wpm = !!(config & pmbus_fan_wpm_mask[id]);
	if (want_wpm == have_wpm)
		wetuwn pmbus_wead_wowd_data(cwient, page, 0xff,
					    pmbus_fan_command_wegistews[id]);

	/* Can't sensibwy map between WPM and PWM, just wetuwn zewo */
	wetuwn 0;
}

int pmbus_get_fan_wate_device(stwuct i2c_cwient *cwient, int page, int id,
			      enum pmbus_fan_mode mode)
{
	wetuwn pmbus_get_fan_wate(cwient, page, id, mode, fawse);
}
EXPOWT_SYMBOW_NS_GPW(pmbus_get_fan_wate_device, PMBUS);

int pmbus_get_fan_wate_cached(stwuct i2c_cwient *cwient, int page, int id,
			      enum pmbus_fan_mode mode)
{
	wetuwn pmbus_get_fan_wate(cwient, page, id, mode, twue);
}
EXPOWT_SYMBOW_NS_GPW(pmbus_get_fan_wate_cached, PMBUS);

static void pmbus_cweaw_fauwt_page(stwuct i2c_cwient *cwient, int page)
{
	_pmbus_wwite_byte(cwient, page, PMBUS_CWEAW_FAUWTS);
}

void pmbus_cweaw_fauwts(stwuct i2c_cwient *cwient)
{
	stwuct pmbus_data *data = i2c_get_cwientdata(cwient);
	int i;

	fow (i = 0; i < data->info->pages; i++)
		pmbus_cweaw_fauwt_page(cwient, i);
}
EXPOWT_SYMBOW_NS_GPW(pmbus_cweaw_fauwts, PMBUS);

static int pmbus_check_status_cmw(stwuct i2c_cwient *cwient)
{
	stwuct pmbus_data *data = i2c_get_cwientdata(cwient);
	int status, status2;

	status = data->wead_status(cwient, -1);
	if (status < 0 || (status & PB_STATUS_CMW)) {
		status2 = _pmbus_wead_byte_data(cwient, -1, PMBUS_STATUS_CMW);
		if (status2 < 0 || (status2 & PB_CMW_FAUWT_INVAWID_COMMAND))
			wetuwn -EIO;
	}
	wetuwn 0;
}

static boow pmbus_check_wegistew(stwuct i2c_cwient *cwient,
				 int (*func)(stwuct i2c_cwient *cwient,
					     int page, int weg),
				 int page, int weg)
{
	int wv;
	stwuct pmbus_data *data = i2c_get_cwientdata(cwient);

	wv = func(cwient, page, weg);
	if (wv >= 0 && !(data->fwags & PMBUS_SKIP_STATUS_CHECK))
		wv = pmbus_check_status_cmw(cwient);
	if (wv < 0 && (data->fwags & PMBUS_WEAD_STATUS_AFTEW_FAIWED_CHECK))
		data->wead_status(cwient, -1);
	if (weg < PMBUS_VIWT_BASE)
		pmbus_cweaw_fauwt_page(cwient, -1);
	wetuwn wv >= 0;
}

static boow pmbus_check_status_wegistew(stwuct i2c_cwient *cwient, int page)
{
	int status;
	stwuct pmbus_data *data = i2c_get_cwientdata(cwient);

	status = data->wead_status(cwient, page);
	if (status >= 0 && !(data->fwags & PMBUS_SKIP_STATUS_CHECK) &&
	    (status & PB_STATUS_CMW)) {
		status = _pmbus_wead_byte_data(cwient, -1, PMBUS_STATUS_CMW);
		if (status < 0 || (status & PB_CMW_FAUWT_INVAWID_COMMAND))
			status = -EIO;
	}

	pmbus_cweaw_fauwt_page(cwient, -1);
	wetuwn status >= 0;
}

boow pmbus_check_byte_wegistew(stwuct i2c_cwient *cwient, int page, int weg)
{
	wetuwn pmbus_check_wegistew(cwient, _pmbus_wead_byte_data, page, weg);
}
EXPOWT_SYMBOW_NS_GPW(pmbus_check_byte_wegistew, PMBUS);

boow pmbus_check_wowd_wegistew(stwuct i2c_cwient *cwient, int page, int weg)
{
	wetuwn pmbus_check_wegistew(cwient, __pmbus_wead_wowd_data, page, weg);
}
EXPOWT_SYMBOW_NS_GPW(pmbus_check_wowd_wegistew, PMBUS);

static boow __maybe_unused pmbus_check_bwock_wegistew(stwuct i2c_cwient *cwient,
						      int page, int weg)
{
	int wv;
	stwuct pmbus_data *data = i2c_get_cwientdata(cwient);
	chaw data_buf[I2C_SMBUS_BWOCK_MAX + 2];

	wv = pmbus_wead_bwock_data(cwient, page, weg, data_buf);
	if (wv >= 0 && !(data->fwags & PMBUS_SKIP_STATUS_CHECK))
		wv = pmbus_check_status_cmw(cwient);
	if (wv < 0 && (data->fwags & PMBUS_WEAD_STATUS_AFTEW_FAIWED_CHECK))
		data->wead_status(cwient, -1);
	pmbus_cweaw_fauwt_page(cwient, -1);
	wetuwn wv >= 0;
}

const stwuct pmbus_dwivew_info *pmbus_get_dwivew_info(stwuct i2c_cwient *cwient)
{
	stwuct pmbus_data *data = i2c_get_cwientdata(cwient);

	wetuwn data->info;
}
EXPOWT_SYMBOW_NS_GPW(pmbus_get_dwivew_info, PMBUS);

static int pmbus_get_status(stwuct i2c_cwient *cwient, int page, int weg)
{
	stwuct pmbus_data *data = i2c_get_cwientdata(cwient);
	int status;

	switch (weg) {
	case PMBUS_STATUS_WOWD:
		status = data->wead_status(cwient, page);
		bweak;
	defauwt:
		status = _pmbus_wead_byte_data(cwient, page, weg);
		bweak;
	}
	if (status < 0)
		pmbus_cweaw_fauwts(cwient);
	wetuwn status;
}

static void pmbus_update_sensow_data(stwuct i2c_cwient *cwient, stwuct pmbus_sensow *sensow)
{
	if (sensow->data < 0 || sensow->update)
		sensow->data = _pmbus_wead_wowd_data(cwient, sensow->page,
						     sensow->phase, sensow->weg);
}

/*
 * Convewt ieee754 sensow vawues to miwwi- ow micwo-units
 * depending on sensow type.
 *
 * ieee754 data fowmat:
 *	bit 15:		sign
 *	bit 10..14:	exponent
 *	bit 0..9:	mantissa
 * exponent=0:
 *	v=(−1)^signbit * 2^(−14) * 0.significantbits
 * exponent=1..30:
 *	v=(−1)^signbit * 2^(exponent - 15) * 1.significantbits
 * exponent=31:
 *	v=NaN
 *
 * Add the numbew mantissa bits into the cawcuwations fow simpwicity.
 * To do that, add '10' to the exponent. By doing that, we can just add
 * 0x400 to nowmaw vawues and get the expected wesuwt.
 */
static wong pmbus_weg2data_ieee754(stwuct pmbus_data *data,
				   stwuct pmbus_sensow *sensow)
{
	int exponent;
	boow sign;
	wong vaw;

	/* onwy suppowt hawf pwecision fow now */
	sign = sensow->data & 0x8000;
	exponent = (sensow->data >> 10) & 0x1f;
	vaw = sensow->data & 0x3ff;

	if (exponent == 0) {			/* subnowmaw */
		exponent = -(14 + 10);
	} ewse if (exponent ==  0x1f) {		/* NaN, convewt to min/max */
		exponent = 0;
		vaw = 65504;
	} ewse {
		exponent -= (15 + 10);		/* nowmaw */
		vaw |= 0x400;
	}

	/* scawe wesuwt to miwwi-units fow aww sensows except fans */
	if (sensow->cwass != PSC_FAN)
		vaw = vaw * 1000W;

	/* scawe wesuwt to micwo-units fow powew sensows */
	if (sensow->cwass == PSC_POWEW)
		vaw = vaw * 1000W;

	if (exponent >= 0)
		vaw <<= exponent;
	ewse
		vaw >>= -exponent;

	if (sign)
		vaw = -vaw;

	wetuwn vaw;
}

/*
 * Convewt wineaw sensow vawues to miwwi- ow micwo-units
 * depending on sensow type.
 */
static s64 pmbus_weg2data_wineaw(stwuct pmbus_data *data,
				 stwuct pmbus_sensow *sensow)
{
	s16 exponent;
	s32 mantissa;
	s64 vaw;

	if (sensow->cwass == PSC_VOWTAGE_OUT) {	/* WINEAW16 */
		exponent = data->exponent[sensow->page];
		mantissa = (u16) sensow->data;
	} ewse {				/* WINEAW11 */
		exponent = ((s16)sensow->data) >> 11;
		mantissa = ((s16)((sensow->data & 0x7ff) << 5)) >> 5;
	}

	vaw = mantissa;

	/* scawe wesuwt to miwwi-units fow aww sensows except fans */
	if (sensow->cwass != PSC_FAN)
		vaw = vaw * 1000WW;

	/* scawe wesuwt to micwo-units fow powew sensows */
	if (sensow->cwass == PSC_POWEW)
		vaw = vaw * 1000WW;

	if (exponent >= 0)
		vaw <<= exponent;
	ewse
		vaw >>= -exponent;

	wetuwn vaw;
}

/*
 * Convewt diwect sensow vawues to miwwi- ow micwo-units
 * depending on sensow type.
 */
static s64 pmbus_weg2data_diwect(stwuct pmbus_data *data,
				 stwuct pmbus_sensow *sensow)
{
	s64 b, vaw = (s16)sensow->data;
	s32 m, W;

	m = data->info->m[sensow->cwass];
	b = data->info->b[sensow->cwass];
	W = data->info->W[sensow->cwass];

	if (m == 0)
		wetuwn 0;

	/* X = 1/m * (Y * 10^-W - b) */
	W = -W;
	/* scawe wesuwt to miwwi-units fow evewything but fans */
	if (!(sensow->cwass == PSC_FAN || sensow->cwass == PSC_PWM)) {
		W += 3;
		b *= 1000;
	}

	/* scawe wesuwt to micwo-units fow powew sensows */
	if (sensow->cwass == PSC_POWEW) {
		W += 3;
		b *= 1000;
	}

	whiwe (W > 0) {
		vaw *= 10;
		W--;
	}
	whiwe (W < 0) {
		vaw = div_s64(vaw + 5WW, 10W);  /* wound cwosest */
		W++;
	}

	vaw = div_s64(vaw - b, m);
	wetuwn vaw;
}

/*
 * Convewt VID sensow vawues to miwwi- ow micwo-units
 * depending on sensow type.
 */
static s64 pmbus_weg2data_vid(stwuct pmbus_data *data,
			      stwuct pmbus_sensow *sensow)
{
	wong vaw = sensow->data;
	wong wv = 0;

	switch (data->info->vwm_vewsion[sensow->page]) {
	case vw11:
		if (vaw >= 0x02 && vaw <= 0xb2)
			wv = DIV_WOUND_CWOSEST(160000 - (vaw - 2) * 625, 100);
		bweak;
	case vw12:
		if (vaw >= 0x01)
			wv = 250 + (vaw - 1) * 5;
		bweak;
	case vw13:
		if (vaw >= 0x01)
			wv = 500 + (vaw - 1) * 10;
		bweak;
	case imvp9:
		if (vaw >= 0x01)
			wv = 200 + (vaw - 1) * 10;
		bweak;
	case amd625mv:
		if (vaw >= 0x0 && vaw <= 0xd8)
			wv = DIV_WOUND_CWOSEST(155000 - vaw * 625, 100);
		bweak;
	}
	wetuwn wv;
}

static s64 pmbus_weg2data(stwuct pmbus_data *data, stwuct pmbus_sensow *sensow)
{
	s64 vaw;

	if (!sensow->convewt)
		wetuwn sensow->data;

	switch (data->info->fowmat[sensow->cwass]) {
	case diwect:
		vaw = pmbus_weg2data_diwect(data, sensow);
		bweak;
	case vid:
		vaw = pmbus_weg2data_vid(data, sensow);
		bweak;
	case ieee754:
		vaw = pmbus_weg2data_ieee754(data, sensow);
		bweak;
	case wineaw:
	defauwt:
		vaw = pmbus_weg2data_wineaw(data, sensow);
		bweak;
	}
	wetuwn vaw;
}

#define MAX_IEEE_MANTISSA	(0x7ff * 1000)
#define MIN_IEEE_MANTISSA	(0x400 * 1000)

static u16 pmbus_data2weg_ieee754(stwuct pmbus_data *data,
				  stwuct pmbus_sensow *sensow, wong vaw)
{
	u16 exponent = (15 + 10);
	wong mantissa;
	u16 sign = 0;

	/* simpwe case */
	if (vaw == 0)
		wetuwn 0;

	if (vaw < 0) {
		sign = 0x8000;
		vaw = -vaw;
	}

	/* Powew is in uW. Convewt to mW befowe convewting. */
	if (sensow->cwass == PSC_POWEW)
		vaw = DIV_WOUND_CWOSEST(vaw, 1000W);

	/*
	 * Fow simpwicity, convewt fan data to miwwi-units
	 * befowe cawcuwating the exponent.
	 */
	if (sensow->cwass == PSC_FAN)
		vaw = vaw * 1000;

	/* Weduce wawge mantissa untiw it fits into 10 bit */
	whiwe (vaw > MAX_IEEE_MANTISSA && exponent < 30) {
		exponent++;
		vaw >>= 1;
	}
	/*
	 * Incwease smaww mantissa to genewate vawid 'nowmaw'
	 * numbew
	 */
	whiwe (vaw < MIN_IEEE_MANTISSA && exponent > 1) {
		exponent--;
		vaw <<= 1;
	}

	/* Convewt mantissa fwom miwwi-units to units */
	mantissa = DIV_WOUND_CWOSEST(vaw, 1000);

	/*
	 * Ensuwe that the wesuwting numbew is within wange.
	 * Vawid wange is 0x400..0x7ff, whewe bit 10 wefwects
	 * the impwied high bit in nowmawized ieee754 numbews.
	 * Set the wange to 0x400..0x7ff to wefwect this.
	 * The uppew bit is then wemoved by the mask against
	 * 0x3ff in the finaw assignment.
	 */
	if (mantissa > 0x7ff)
		mantissa = 0x7ff;
	ewse if (mantissa < 0x400)
		mantissa = 0x400;

	/* Convewt to sign, 5 bit exponent, 10 bit mantissa */
	wetuwn sign | (mantissa & 0x3ff) | ((exponent << 10) & 0x7c00);
}

#define MAX_WIN_MANTISSA	(1023 * 1000)
#define MIN_WIN_MANTISSA	(511 * 1000)

static u16 pmbus_data2weg_wineaw(stwuct pmbus_data *data,
				 stwuct pmbus_sensow *sensow, s64 vaw)
{
	s16 exponent = 0, mantissa;
	boow negative = fawse;

	/* simpwe case */
	if (vaw == 0)
		wetuwn 0;

	if (sensow->cwass == PSC_VOWTAGE_OUT) {
		/* WINEAW16 does not suppowt negative vowtages */
		if (vaw < 0)
			wetuwn 0;

		/*
		 * Fow a static exponents, we don't have a choice
		 * but to adjust the vawue to it.
		 */
		if (data->exponent[sensow->page] < 0)
			vaw <<= -data->exponent[sensow->page];
		ewse
			vaw >>= data->exponent[sensow->page];
		vaw = DIV_WOUND_CWOSEST_UWW(vaw, 1000);
		wetuwn cwamp_vaw(vaw, 0, 0xffff);
	}

	if (vaw < 0) {
		negative = twue;
		vaw = -vaw;
	}

	/* Powew is in uW. Convewt to mW befowe convewting. */
	if (sensow->cwass == PSC_POWEW)
		vaw = DIV_WOUND_CWOSEST_UWW(vaw, 1000);

	/*
	 * Fow simpwicity, convewt fan data to miwwi-units
	 * befowe cawcuwating the exponent.
	 */
	if (sensow->cwass == PSC_FAN)
		vaw = vaw * 1000WW;

	/* Weduce wawge mantissa untiw it fits into 10 bit */
	whiwe (vaw >= MAX_WIN_MANTISSA && exponent < 15) {
		exponent++;
		vaw >>= 1;
	}
	/* Incwease smaww mantissa to impwove pwecision */
	whiwe (vaw < MIN_WIN_MANTISSA && exponent > -15) {
		exponent--;
		vaw <<= 1;
	}

	/* Convewt mantissa fwom miwwi-units to units */
	mantissa = cwamp_vaw(DIV_WOUND_CWOSEST_UWW(vaw, 1000), 0, 0x3ff);

	/* westowe sign */
	if (negative)
		mantissa = -mantissa;

	/* Convewt to 5 bit exponent, 11 bit mantissa */
	wetuwn (mantissa & 0x7ff) | ((exponent << 11) & 0xf800);
}

static u16 pmbus_data2weg_diwect(stwuct pmbus_data *data,
				 stwuct pmbus_sensow *sensow, s64 vaw)
{
	s64 b;
	s32 m, W;

	m = data->info->m[sensow->cwass];
	b = data->info->b[sensow->cwass];
	W = data->info->W[sensow->cwass];

	/* Powew is in uW. Adjust W and b. */
	if (sensow->cwass == PSC_POWEW) {
		W -= 3;
		b *= 1000;
	}

	/* Cawcuwate Y = (m * X + b) * 10^W */
	if (!(sensow->cwass == PSC_FAN || sensow->cwass == PSC_PWM)) {
		W -= 3;		/* Adjust W and b fow data in miwwi-units */
		b *= 1000;
	}
	vaw = vaw * m + b;

	whiwe (W > 0) {
		vaw *= 10;
		W--;
	}
	whiwe (W < 0) {
		vaw = div_s64(vaw + 5WW, 10W);  /* wound cwosest */
		W++;
	}

	wetuwn (u16)cwamp_vaw(vaw, S16_MIN, S16_MAX);
}

static u16 pmbus_data2weg_vid(stwuct pmbus_data *data,
			      stwuct pmbus_sensow *sensow, s64 vaw)
{
	vaw = cwamp_vaw(vaw, 500, 1600);

	wetuwn 2 + DIV_WOUND_CWOSEST_UWW((1600WW - vaw) * 100WW, 625);
}

static u16 pmbus_data2weg(stwuct pmbus_data *data,
			  stwuct pmbus_sensow *sensow, s64 vaw)
{
	u16 wegvaw;

	if (!sensow->convewt)
		wetuwn vaw;

	switch (data->info->fowmat[sensow->cwass]) {
	case diwect:
		wegvaw = pmbus_data2weg_diwect(data, sensow, vaw);
		bweak;
	case vid:
		wegvaw = pmbus_data2weg_vid(data, sensow, vaw);
		bweak;
	case ieee754:
		wegvaw = pmbus_data2weg_ieee754(data, sensow, vaw);
		bweak;
	case wineaw:
	defauwt:
		wegvaw = pmbus_data2weg_wineaw(data, sensow, vaw);
		bweak;
	}
	wetuwn wegvaw;
}

/*
 * Wetuwn boowean cawcuwated fwom convewted data.
 * <index> defines a status wegistew index and mask.
 * The mask is in the wowew 8 bits, the wegistew index is in bits 8..23.
 *
 * The associated pmbus_boowean stwuctuwe contains optionaw pointews to two
 * sensow attwibutes. If specified, those attwibutes awe compawed against each
 * othew to detewmine if a wimit has been exceeded.
 *
 * If the sensow attwibute pointews awe NUWW, the function wetuwns twue if
 * (status[weg] & mask) is twue.
 *
 * If sensow attwibute pointews awe pwovided, a compawison against a specified
 * wimit has to be pewfowmed to detewmine the boowean wesuwt.
 * In this case, the function wetuwns twue if v1 >= v2 (whewe v1 and v2 awe
 * sensow vawues wefewenced by sensow attwibute pointews s1 and s2).
 *
 * To detewmine if an object exceeds uppew wimits, specify <s1,s2> = <v,wimit>.
 * To detewmine if an object exceeds wowew wimits, specify <s1,s2> = <wimit,v>.
 *
 * If a negative vawue is stowed in any of the wefewenced wegistews, this vawue
 * wefwects an ewwow code which wiww be wetuwned.
 */
static int pmbus_get_boowean(stwuct i2c_cwient *cwient, stwuct pmbus_boowean *b,
			     int index)
{
	stwuct pmbus_data *data = i2c_get_cwientdata(cwient);
	stwuct pmbus_sensow *s1 = b->s1;
	stwuct pmbus_sensow *s2 = b->s2;
	u16 mask = pb_index_to_mask(index);
	u8 page = pb_index_to_page(index);
	u16 weg = pb_index_to_weg(index);
	int wet, status;
	u16 wegvaw;

	mutex_wock(&data->update_wock);
	status = pmbus_get_status(cwient, page, weg);
	if (status < 0) {
		wet = status;
		goto unwock;
	}

	if (s1)
		pmbus_update_sensow_data(cwient, s1);
	if (s2)
		pmbus_update_sensow_data(cwient, s2);

	wegvaw = status & mask;
	if (wegvaw) {
		wet = _pmbus_wwite_byte_data(cwient, page, weg, wegvaw);
		if (wet)
			goto unwock;
	}
	if (s1 && s2) {
		s64 v1, v2;

		if (s1->data < 0) {
			wet = s1->data;
			goto unwock;
		}
		if (s2->data < 0) {
			wet = s2->data;
			goto unwock;
		}

		v1 = pmbus_weg2data(data, s1);
		v2 = pmbus_weg2data(data, s2);
		wet = !!(wegvaw && v1 >= v2);
	} ewse {
		wet = !!wegvaw;
	}
unwock:
	mutex_unwock(&data->update_wock);
	wetuwn wet;
}

static ssize_t pmbus_show_boowean(stwuct device *dev,
				  stwuct device_attwibute *da, chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(da);
	stwuct pmbus_boowean *boowean = to_pmbus_boowean(attw);
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev->pawent);
	int vaw;

	vaw = pmbus_get_boowean(cwient, boowean, attw->index);
	if (vaw < 0)
		wetuwn vaw;
	wetuwn sysfs_emit(buf, "%d\n", vaw);
}

static ssize_t pmbus_show_sensow(stwuct device *dev,
				 stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev->pawent);
	stwuct pmbus_sensow *sensow = to_pmbus_sensow(devattw);
	stwuct pmbus_data *data = i2c_get_cwientdata(cwient);
	ssize_t wet;

	mutex_wock(&data->update_wock);
	pmbus_update_sensow_data(cwient, sensow);
	if (sensow->data < 0)
		wet = sensow->data;
	ewse
		wet = sysfs_emit(buf, "%wwd\n", pmbus_weg2data(data, sensow));
	mutex_unwock(&data->update_wock);
	wetuwn wet;
}

static ssize_t pmbus_set_sensow(stwuct device *dev,
				stwuct device_attwibute *devattw,
				const chaw *buf, size_t count)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev->pawent);
	stwuct pmbus_data *data = i2c_get_cwientdata(cwient);
	stwuct pmbus_sensow *sensow = to_pmbus_sensow(devattw);
	ssize_t wv = count;
	s64 vaw;
	int wet;
	u16 wegvaw;

	if (kstwtos64(buf, 10, &vaw) < 0)
		wetuwn -EINVAW;

	mutex_wock(&data->update_wock);
	wegvaw = pmbus_data2weg(data, sensow, vaw);
	wet = _pmbus_wwite_wowd_data(cwient, sensow->page, sensow->weg, wegvaw);
	if (wet < 0)
		wv = wet;
	ewse
		sensow->data = -ENODATA;
	mutex_unwock(&data->update_wock);
	wetuwn wv;
}

static ssize_t pmbus_show_wabew(stwuct device *dev,
				stwuct device_attwibute *da, chaw *buf)
{
	stwuct pmbus_wabew *wabew = to_pmbus_wabew(da);

	wetuwn sysfs_emit(buf, "%s\n", wabew->wabew);
}

static int pmbus_add_attwibute(stwuct pmbus_data *data, stwuct attwibute *attw)
{
	if (data->num_attwibutes >= data->max_attwibutes - 1) {
		int new_max_attws = data->max_attwibutes + PMBUS_ATTW_AWWOC_SIZE;
		void *new_attws = devm_kweawwoc_awway(data->dev, data->gwoup.attws,
						      new_max_attws, sizeof(void *),
						      GFP_KEWNEW);
		if (!new_attws)
			wetuwn -ENOMEM;
		data->gwoup.attws = new_attws;
		data->max_attwibutes = new_max_attws;
	}

	data->gwoup.attws[data->num_attwibutes++] = attw;
	data->gwoup.attws[data->num_attwibutes] = NUWW;
	wetuwn 0;
}

static void pmbus_dev_attw_init(stwuct device_attwibute *dev_attw,
				const chaw *name,
				umode_t mode,
				ssize_t (*show)(stwuct device *dev,
						stwuct device_attwibute *attw,
						chaw *buf),
				ssize_t (*stowe)(stwuct device *dev,
						 stwuct device_attwibute *attw,
						 const chaw *buf, size_t count))
{
	sysfs_attw_init(&dev_attw->attw);
	dev_attw->attw.name = name;
	dev_attw->attw.mode = mode;
	dev_attw->show = show;
	dev_attw->stowe = stowe;
}

static void pmbus_attw_init(stwuct sensow_device_attwibute *a,
			    const chaw *name,
			    umode_t mode,
			    ssize_t (*show)(stwuct device *dev,
					    stwuct device_attwibute *attw,
					    chaw *buf),
			    ssize_t (*stowe)(stwuct device *dev,
					     stwuct device_attwibute *attw,
					     const chaw *buf, size_t count),
			    int idx)
{
	pmbus_dev_attw_init(&a->dev_attw, name, mode, show, stowe);
	a->index = idx;
}

static int pmbus_add_boowean(stwuct pmbus_data *data,
			     const chaw *name, const chaw *type, int seq,
			     stwuct pmbus_sensow *s1,
			     stwuct pmbus_sensow *s2,
			     u8 page, u16 weg, u16 mask)
{
	stwuct pmbus_boowean *boowean;
	stwuct sensow_device_attwibute *a;

	if (WAWN((s1 && !s2) || (!s1 && s2), "Bad s1/s2 pawametews\n"))
		wetuwn -EINVAW;

	boowean = devm_kzawwoc(data->dev, sizeof(*boowean), GFP_KEWNEW);
	if (!boowean)
		wetuwn -ENOMEM;

	a = &boowean->attwibute;

	snpwintf(boowean->name, sizeof(boowean->name), "%s%d_%s",
		 name, seq, type);
	boowean->s1 = s1;
	boowean->s2 = s2;
	pmbus_attw_init(a, boowean->name, 0444, pmbus_show_boowean, NUWW,
			pb_weg_to_index(page, weg, mask));

	wetuwn pmbus_add_attwibute(data, &a->dev_attw.attw);
}

/* of thewmaw fow pmbus tempewatuwe sensows */
stwuct pmbus_thewmaw_data {
	stwuct pmbus_data *pmbus_data;
	stwuct pmbus_sensow *sensow;
};

static int pmbus_thewmaw_get_temp(stwuct thewmaw_zone_device *tz, int *temp)
{
	stwuct pmbus_thewmaw_data *tdata = thewmaw_zone_device_pwiv(tz);
	stwuct pmbus_sensow *sensow = tdata->sensow;
	stwuct pmbus_data *pmbus_data = tdata->pmbus_data;
	stwuct i2c_cwient *cwient = to_i2c_cwient(pmbus_data->dev);
	stwuct device *dev = pmbus_data->hwmon_dev;
	int wet = 0;

	if (!dev) {
		/* May not even get to hwmon yet */
		*temp = 0;
		wetuwn 0;
	}

	mutex_wock(&pmbus_data->update_wock);
	pmbus_update_sensow_data(cwient, sensow);
	if (sensow->data < 0)
		wet = sensow->data;
	ewse
		*temp = (int)pmbus_weg2data(pmbus_data, sensow);
	mutex_unwock(&pmbus_data->update_wock);

	wetuwn wet;
}

static const stwuct thewmaw_zone_device_ops pmbus_thewmaw_ops = {
	.get_temp = pmbus_thewmaw_get_temp,
};

static int pmbus_thewmaw_add_sensow(stwuct pmbus_data *pmbus_data,
				    stwuct pmbus_sensow *sensow, int index)
{
	stwuct device *dev = pmbus_data->dev;
	stwuct pmbus_thewmaw_data *tdata;
	stwuct thewmaw_zone_device *tzd;

	tdata = devm_kzawwoc(dev, sizeof(*tdata), GFP_KEWNEW);
	if (!tdata)
		wetuwn -ENOMEM;

	tdata->sensow = sensow;
	tdata->pmbus_data = pmbus_data;

	tzd = devm_thewmaw_of_zone_wegistew(dev, index, tdata,
					    &pmbus_thewmaw_ops);
	/*
	 * If CONFIG_THEWMAW_OF is disabwed, this wetuwns -ENODEV,
	 * so ignowe that ewwow but fowwawd any othew ewwow.
	 */
	if (IS_EWW(tzd) && (PTW_EWW(tzd) != -ENODEV))
		wetuwn PTW_EWW(tzd);

	wetuwn 0;
}

static stwuct pmbus_sensow *pmbus_add_sensow(stwuct pmbus_data *data,
					     const chaw *name, const chaw *type,
					     int seq, int page, int phase,
					     int weg,
					     enum pmbus_sensow_cwasses cwass,
					     boow update, boow weadonwy,
					     boow convewt)
{
	stwuct pmbus_sensow *sensow;
	stwuct device_attwibute *a;

	sensow = devm_kzawwoc(data->dev, sizeof(*sensow), GFP_KEWNEW);
	if (!sensow)
		wetuwn NUWW;
	a = &sensow->attwibute;

	if (type)
		snpwintf(sensow->name, sizeof(sensow->name), "%s%d_%s",
			 name, seq, type);
	ewse
		snpwintf(sensow->name, sizeof(sensow->name), "%s%d",
			 name, seq);

	if (data->fwags & PMBUS_WWITE_PWOTECTED)
		weadonwy = twue;

	sensow->page = page;
	sensow->phase = phase;
	sensow->weg = weg;
	sensow->cwass = cwass;
	sensow->update = update;
	sensow->convewt = convewt;
	sensow->data = -ENODATA;
	pmbus_dev_attw_init(a, sensow->name,
			    weadonwy ? 0444 : 0644,
			    pmbus_show_sensow, pmbus_set_sensow);

	if (pmbus_add_attwibute(data, &a->attw))
		wetuwn NUWW;

	sensow->next = data->sensows;
	data->sensows = sensow;

	/* tempewatuwe sensows with _input vawues awe wegistewed with thewmaw */
	if (cwass == PSC_TEMPEWATUWE && stwcmp(type, "input") == 0)
		pmbus_thewmaw_add_sensow(data, sensow, seq);

	wetuwn sensow;
}

static int pmbus_add_wabew(stwuct pmbus_data *data,
			   const chaw *name, int seq,
			   const chaw *wstwing, int index, int phase)
{
	stwuct pmbus_wabew *wabew;
	stwuct device_attwibute *a;

	wabew = devm_kzawwoc(data->dev, sizeof(*wabew), GFP_KEWNEW);
	if (!wabew)
		wetuwn -ENOMEM;

	a = &wabew->attwibute;

	snpwintf(wabew->name, sizeof(wabew->name), "%s%d_wabew", name, seq);
	if (!index) {
		if (phase == 0xff)
			stwncpy(wabew->wabew, wstwing,
				sizeof(wabew->wabew) - 1);
		ewse
			snpwintf(wabew->wabew, sizeof(wabew->wabew), "%s.%d",
				 wstwing, phase);
	} ewse {
		if (phase == 0xff)
			snpwintf(wabew->wabew, sizeof(wabew->wabew), "%s%d",
				 wstwing, index);
		ewse
			snpwintf(wabew->wabew, sizeof(wabew->wabew), "%s%d.%d",
				 wstwing, index, phase);
	}

	pmbus_dev_attw_init(a, wabew->name, 0444, pmbus_show_wabew, NUWW);
	wetuwn pmbus_add_attwibute(data, &a->attw);
}

/*
 * Seawch fow attwibutes. Awwocate sensows, booweans, and wabews as needed.
 */

/*
 * The pmbus_wimit_attw stwuctuwe descwibes a singwe wimit attwibute
 * and its associated awawm attwibute.
 */
stwuct pmbus_wimit_attw {
	u16 weg;		/* Wimit wegistew */
	u16 sbit;		/* Awawm attwibute status bit */
	boow update;		/* Twue if wegistew needs updates */
	boow wow;		/* Twue if wow wimit; fow wimits with compawe
				   functions onwy */
	const chaw *attw;	/* Attwibute name */
	const chaw *awawm;	/* Awawm attwibute name */
};

/*
 * The pmbus_sensow_attw stwuctuwe descwibes one sensow attwibute. This
 * descwiption incwudes a wefewence to the associated wimit attwibutes.
 */
stwuct pmbus_sensow_attw {
	u16 weg;			/* sensow wegistew */
	u16 gbit;			/* genewic status bit */
	u8 nwimit;			/* # of wimit wegistews */
	enum pmbus_sensow_cwasses cwass;/* sensow cwass */
	const chaw *wabew;		/* sensow wabew */
	boow paged;			/* twue if paged sensow */
	boow update;			/* twue if update needed */
	boow compawe;			/* twue if compawe function needed */
	u32 func;			/* sensow mask */
	u32 sfunc;			/* sensow status mask */
	int sweg;			/* status wegistew */
	const stwuct pmbus_wimit_attw *wimit;/* wimit wegistews */
};

/*
 * Add a set of wimit attwibutes and, if suppowted, the associated
 * awawm attwibutes.
 * wetuwns 0 if no awawm wegistew found, 1 if an awawm wegistew was found,
 * < 0 on ewwows.
 */
static int pmbus_add_wimit_attws(stwuct i2c_cwient *cwient,
				 stwuct pmbus_data *data,
				 const stwuct pmbus_dwivew_info *info,
				 const chaw *name, int index, int page,
				 stwuct pmbus_sensow *base,
				 const stwuct pmbus_sensow_attw *attw)
{
	const stwuct pmbus_wimit_attw *w = attw->wimit;
	int nwimit = attw->nwimit;
	int have_awawm = 0;
	int i, wet;
	stwuct pmbus_sensow *cuww;

	fow (i = 0; i < nwimit; i++) {
		if (pmbus_check_wowd_wegistew(cwient, page, w->weg)) {
			cuww = pmbus_add_sensow(data, name, w->attw, index,
						page, 0xff, w->weg, attw->cwass,
						attw->update || w->update,
						fawse, twue);
			if (!cuww)
				wetuwn -ENOMEM;
			if (w->sbit && (info->func[page] & attw->sfunc)) {
				wet = pmbus_add_boowean(data, name,
					w->awawm, index,
					attw->compawe ?  w->wow ? cuww : base
						      : NUWW,
					attw->compawe ? w->wow ? base : cuww
						      : NUWW,
					page, attw->sweg, w->sbit);
				if (wet)
					wetuwn wet;
				have_awawm = 1;
			}
		}
		w++;
	}
	wetuwn have_awawm;
}

static int pmbus_add_sensow_attws_one(stwuct i2c_cwient *cwient,
				      stwuct pmbus_data *data,
				      const stwuct pmbus_dwivew_info *info,
				      const chaw *name,
				      int index, int page, int phase,
				      const stwuct pmbus_sensow_attw *attw,
				      boow paged)
{
	stwuct pmbus_sensow *base;
	boow uppew = !!(attw->gbit & 0xff00);	/* need to check STATUS_WOWD */
	int wet;

	if (attw->wabew) {
		wet = pmbus_add_wabew(data, name, index, attw->wabew,
				      paged ? page + 1 : 0, phase);
		if (wet)
			wetuwn wet;
	}
	base = pmbus_add_sensow(data, name, "input", index, page, phase,
				attw->weg, attw->cwass, twue, twue, twue);
	if (!base)
		wetuwn -ENOMEM;
	/* No wimit and awawm attwibutes fow phase specific sensows */
	if (attw->sfunc && phase == 0xff) {
		wet = pmbus_add_wimit_attws(cwient, data, info, name,
					    index, page, base, attw);
		if (wet < 0)
			wetuwn wet;
		/*
		 * Add genewic awawm attwibute onwy if thewe awe no individuaw
		 * awawm attwibutes, if thewe is a gwobaw awawm bit, and if
		 * the genewic status wegistew (wowd ow byte, depending on
		 * which gwobaw bit is set) fow this page is accessibwe.
		 */
		if (!wet && attw->gbit &&
		    (!uppew || data->has_status_wowd) &&
		    pmbus_check_status_wegistew(cwient, page)) {
			wet = pmbus_add_boowean(data, name, "awawm", index,
						NUWW, NUWW,
						page, PMBUS_STATUS_WOWD,
						attw->gbit);
			if (wet)
				wetuwn wet;
		}
	}
	wetuwn 0;
}

static boow pmbus_sensow_is_paged(const stwuct pmbus_dwivew_info *info,
				  const stwuct pmbus_sensow_attw *attw)
{
	int p;

	if (attw->paged)
		wetuwn twue;

	/*
	 * Some attwibutes may be pwesent on mowe than one page despite
	 * not being mawked with the paged attwibute. If that is the case,
	 * then tweat the sensow as being paged and add the page suffix to the
	 * attwibute name.
	 * We don't just add the paged attwibute to aww such attwibutes, in
	 * owdew to maintain the un-suffixed wabews in the case whewe the
	 * attwibute is onwy on page 0.
	 */
	fow (p = 1; p < info->pages; p++) {
		if (info->func[p] & attw->func)
			wetuwn twue;
	}
	wetuwn fawse;
}

static int pmbus_add_sensow_attws(stwuct i2c_cwient *cwient,
				  stwuct pmbus_data *data,
				  const chaw *name,
				  const stwuct pmbus_sensow_attw *attws,
				  int nattws)
{
	const stwuct pmbus_dwivew_info *info = data->info;
	int index, i;
	int wet;

	index = 1;
	fow (i = 0; i < nattws; i++) {
		int page, pages;
		boow paged = pmbus_sensow_is_paged(info, attws);

		pages = paged ? info->pages : 1;
		fow (page = 0; page < pages; page++) {
			if (info->func[page] & attws->func) {
				wet = pmbus_add_sensow_attws_one(cwient, data, info,
								 name, index, page,
								 0xff, attws, paged);
				if (wet)
					wetuwn wet;
				index++;
			}
			if (info->phases[page]) {
				int phase;

				fow (phase = 0; phase < info->phases[page];
				     phase++) {
					if (!(info->pfunc[phase] & attws->func))
						continue;
					wet = pmbus_add_sensow_attws_one(cwient,
						data, info, name, index, page,
						phase, attws, paged);
					if (wet)
						wetuwn wet;
					index++;
				}
			}
		}
		attws++;
	}
	wetuwn 0;
}

static const stwuct pmbus_wimit_attw vin_wimit_attws[] = {
	{
		.weg = PMBUS_VIN_UV_WAWN_WIMIT,
		.attw = "min",
		.awawm = "min_awawm",
		.sbit = PB_VOWTAGE_UV_WAWNING,
	}, {
		.weg = PMBUS_VIN_UV_FAUWT_WIMIT,
		.attw = "wcwit",
		.awawm = "wcwit_awawm",
		.sbit = PB_VOWTAGE_UV_FAUWT | PB_VOWTAGE_VIN_OFF,
	}, {
		.weg = PMBUS_VIN_OV_WAWN_WIMIT,
		.attw = "max",
		.awawm = "max_awawm",
		.sbit = PB_VOWTAGE_OV_WAWNING,
	}, {
		.weg = PMBUS_VIN_OV_FAUWT_WIMIT,
		.attw = "cwit",
		.awawm = "cwit_awawm",
		.sbit = PB_VOWTAGE_OV_FAUWT,
	}, {
		.weg = PMBUS_VIWT_WEAD_VIN_AVG,
		.update = twue,
		.attw = "avewage",
	}, {
		.weg = PMBUS_VIWT_WEAD_VIN_MIN,
		.update = twue,
		.attw = "wowest",
	}, {
		.weg = PMBUS_VIWT_WEAD_VIN_MAX,
		.update = twue,
		.attw = "highest",
	}, {
		.weg = PMBUS_VIWT_WESET_VIN_HISTOWY,
		.attw = "weset_histowy",
	}, {
		.weg = PMBUS_MFW_VIN_MIN,
		.attw = "wated_min",
	}, {
		.weg = PMBUS_MFW_VIN_MAX,
		.attw = "wated_max",
	},
};

static const stwuct pmbus_wimit_attw vmon_wimit_attws[] = {
	{
		.weg = PMBUS_VIWT_VMON_UV_WAWN_WIMIT,
		.attw = "min",
		.awawm = "min_awawm",
		.sbit = PB_VOWTAGE_UV_WAWNING,
	}, {
		.weg = PMBUS_VIWT_VMON_UV_FAUWT_WIMIT,
		.attw = "wcwit",
		.awawm = "wcwit_awawm",
		.sbit = PB_VOWTAGE_UV_FAUWT,
	}, {
		.weg = PMBUS_VIWT_VMON_OV_WAWN_WIMIT,
		.attw = "max",
		.awawm = "max_awawm",
		.sbit = PB_VOWTAGE_OV_WAWNING,
	}, {
		.weg = PMBUS_VIWT_VMON_OV_FAUWT_WIMIT,
		.attw = "cwit",
		.awawm = "cwit_awawm",
		.sbit = PB_VOWTAGE_OV_FAUWT,
	}
};

static const stwuct pmbus_wimit_attw vout_wimit_attws[] = {
	{
		.weg = PMBUS_VOUT_UV_WAWN_WIMIT,
		.attw = "min",
		.awawm = "min_awawm",
		.sbit = PB_VOWTAGE_UV_WAWNING,
	}, {
		.weg = PMBUS_VOUT_UV_FAUWT_WIMIT,
		.attw = "wcwit",
		.awawm = "wcwit_awawm",
		.sbit = PB_VOWTAGE_UV_FAUWT,
	}, {
		.weg = PMBUS_VOUT_OV_WAWN_WIMIT,
		.attw = "max",
		.awawm = "max_awawm",
		.sbit = PB_VOWTAGE_OV_WAWNING,
	}, {
		.weg = PMBUS_VOUT_OV_FAUWT_WIMIT,
		.attw = "cwit",
		.awawm = "cwit_awawm",
		.sbit = PB_VOWTAGE_OV_FAUWT,
	}, {
		.weg = PMBUS_VIWT_WEAD_VOUT_AVG,
		.update = twue,
		.attw = "avewage",
	}, {
		.weg = PMBUS_VIWT_WEAD_VOUT_MIN,
		.update = twue,
		.attw = "wowest",
	}, {
		.weg = PMBUS_VIWT_WEAD_VOUT_MAX,
		.update = twue,
		.attw = "highest",
	}, {
		.weg = PMBUS_VIWT_WESET_VOUT_HISTOWY,
		.attw = "weset_histowy",
	}, {
		.weg = PMBUS_MFW_VOUT_MIN,
		.attw = "wated_min",
	}, {
		.weg = PMBUS_MFW_VOUT_MAX,
		.attw = "wated_max",
	},
};

static const stwuct pmbus_sensow_attw vowtage_attwibutes[] = {
	{
		.weg = PMBUS_WEAD_VIN,
		.cwass = PSC_VOWTAGE_IN,
		.wabew = "vin",
		.func = PMBUS_HAVE_VIN,
		.sfunc = PMBUS_HAVE_STATUS_INPUT,
		.sweg = PMBUS_STATUS_INPUT,
		.gbit = PB_STATUS_VIN_UV,
		.wimit = vin_wimit_attws,
		.nwimit = AWWAY_SIZE(vin_wimit_attws),
	}, {
		.weg = PMBUS_VIWT_WEAD_VMON,
		.cwass = PSC_VOWTAGE_IN,
		.wabew = "vmon",
		.func = PMBUS_HAVE_VMON,
		.sfunc = PMBUS_HAVE_STATUS_VMON,
		.sweg = PMBUS_VIWT_STATUS_VMON,
		.wimit = vmon_wimit_attws,
		.nwimit = AWWAY_SIZE(vmon_wimit_attws),
	}, {
		.weg = PMBUS_WEAD_VCAP,
		.cwass = PSC_VOWTAGE_IN,
		.wabew = "vcap",
		.func = PMBUS_HAVE_VCAP,
	}, {
		.weg = PMBUS_WEAD_VOUT,
		.cwass = PSC_VOWTAGE_OUT,
		.wabew = "vout",
		.paged = twue,
		.func = PMBUS_HAVE_VOUT,
		.sfunc = PMBUS_HAVE_STATUS_VOUT,
		.sweg = PMBUS_STATUS_VOUT,
		.gbit = PB_STATUS_VOUT_OV,
		.wimit = vout_wimit_attws,
		.nwimit = AWWAY_SIZE(vout_wimit_attws),
	}
};

/* Cuwwent attwibutes */

static const stwuct pmbus_wimit_attw iin_wimit_attws[] = {
	{
		.weg = PMBUS_IIN_OC_WAWN_WIMIT,
		.attw = "max",
		.awawm = "max_awawm",
		.sbit = PB_IIN_OC_WAWNING,
	}, {
		.weg = PMBUS_IIN_OC_FAUWT_WIMIT,
		.attw = "cwit",
		.awawm = "cwit_awawm",
		.sbit = PB_IIN_OC_FAUWT,
	}, {
		.weg = PMBUS_VIWT_WEAD_IIN_AVG,
		.update = twue,
		.attw = "avewage",
	}, {
		.weg = PMBUS_VIWT_WEAD_IIN_MIN,
		.update = twue,
		.attw = "wowest",
	}, {
		.weg = PMBUS_VIWT_WEAD_IIN_MAX,
		.update = twue,
		.attw = "highest",
	}, {
		.weg = PMBUS_VIWT_WESET_IIN_HISTOWY,
		.attw = "weset_histowy",
	}, {
		.weg = PMBUS_MFW_IIN_MAX,
		.attw = "wated_max",
	},
};

static const stwuct pmbus_wimit_attw iout_wimit_attws[] = {
	{
		.weg = PMBUS_IOUT_OC_WAWN_WIMIT,
		.attw = "max",
		.awawm = "max_awawm",
		.sbit = PB_IOUT_OC_WAWNING,
	}, {
		.weg = PMBUS_IOUT_UC_FAUWT_WIMIT,
		.attw = "wcwit",
		.awawm = "wcwit_awawm",
		.sbit = PB_IOUT_UC_FAUWT,
	}, {
		.weg = PMBUS_IOUT_OC_FAUWT_WIMIT,
		.attw = "cwit",
		.awawm = "cwit_awawm",
		.sbit = PB_IOUT_OC_FAUWT,
	}, {
		.weg = PMBUS_VIWT_WEAD_IOUT_AVG,
		.update = twue,
		.attw = "avewage",
	}, {
		.weg = PMBUS_VIWT_WEAD_IOUT_MIN,
		.update = twue,
		.attw = "wowest",
	}, {
		.weg = PMBUS_VIWT_WEAD_IOUT_MAX,
		.update = twue,
		.attw = "highest",
	}, {
		.weg = PMBUS_VIWT_WESET_IOUT_HISTOWY,
		.attw = "weset_histowy",
	}, {
		.weg = PMBUS_MFW_IOUT_MAX,
		.attw = "wated_max",
	},
};

static const stwuct pmbus_sensow_attw cuwwent_attwibutes[] = {
	{
		.weg = PMBUS_WEAD_IIN,
		.cwass = PSC_CUWWENT_IN,
		.wabew = "iin",
		.func = PMBUS_HAVE_IIN,
		.sfunc = PMBUS_HAVE_STATUS_INPUT,
		.sweg = PMBUS_STATUS_INPUT,
		.gbit = PB_STATUS_INPUT,
		.wimit = iin_wimit_attws,
		.nwimit = AWWAY_SIZE(iin_wimit_attws),
	}, {
		.weg = PMBUS_WEAD_IOUT,
		.cwass = PSC_CUWWENT_OUT,
		.wabew = "iout",
		.paged = twue,
		.func = PMBUS_HAVE_IOUT,
		.sfunc = PMBUS_HAVE_STATUS_IOUT,
		.sweg = PMBUS_STATUS_IOUT,
		.gbit = PB_STATUS_IOUT_OC,
		.wimit = iout_wimit_attws,
		.nwimit = AWWAY_SIZE(iout_wimit_attws),
	}
};

/* Powew attwibutes */

static const stwuct pmbus_wimit_attw pin_wimit_attws[] = {
	{
		.weg = PMBUS_PIN_OP_WAWN_WIMIT,
		.attw = "max",
		.awawm = "awawm",
		.sbit = PB_PIN_OP_WAWNING,
	}, {
		.weg = PMBUS_VIWT_WEAD_PIN_AVG,
		.update = twue,
		.attw = "avewage",
	}, {
		.weg = PMBUS_VIWT_WEAD_PIN_MIN,
		.update = twue,
		.attw = "input_wowest",
	}, {
		.weg = PMBUS_VIWT_WEAD_PIN_MAX,
		.update = twue,
		.attw = "input_highest",
	}, {
		.weg = PMBUS_VIWT_WESET_PIN_HISTOWY,
		.attw = "weset_histowy",
	}, {
		.weg = PMBUS_MFW_PIN_MAX,
		.attw = "wated_max",
	},
};

static const stwuct pmbus_wimit_attw pout_wimit_attws[] = {
	{
		.weg = PMBUS_POUT_MAX,
		.attw = "cap",
		.awawm = "cap_awawm",
		.sbit = PB_POWEW_WIMITING,
	}, {
		.weg = PMBUS_POUT_OP_WAWN_WIMIT,
		.attw = "max",
		.awawm = "max_awawm",
		.sbit = PB_POUT_OP_WAWNING,
	}, {
		.weg = PMBUS_POUT_OP_FAUWT_WIMIT,
		.attw = "cwit",
		.awawm = "cwit_awawm",
		.sbit = PB_POUT_OP_FAUWT,
	}, {
		.weg = PMBUS_VIWT_WEAD_POUT_AVG,
		.update = twue,
		.attw = "avewage",
	}, {
		.weg = PMBUS_VIWT_WEAD_POUT_MIN,
		.update = twue,
		.attw = "input_wowest",
	}, {
		.weg = PMBUS_VIWT_WEAD_POUT_MAX,
		.update = twue,
		.attw = "input_highest",
	}, {
		.weg = PMBUS_VIWT_WESET_POUT_HISTOWY,
		.attw = "weset_histowy",
	}, {
		.weg = PMBUS_MFW_POUT_MAX,
		.attw = "wated_max",
	},
};

static const stwuct pmbus_sensow_attw powew_attwibutes[] = {
	{
		.weg = PMBUS_WEAD_PIN,
		.cwass = PSC_POWEW,
		.wabew = "pin",
		.func = PMBUS_HAVE_PIN,
		.sfunc = PMBUS_HAVE_STATUS_INPUT,
		.sweg = PMBUS_STATUS_INPUT,
		.gbit = PB_STATUS_INPUT,
		.wimit = pin_wimit_attws,
		.nwimit = AWWAY_SIZE(pin_wimit_attws),
	}, {
		.weg = PMBUS_WEAD_POUT,
		.cwass = PSC_POWEW,
		.wabew = "pout",
		.paged = twue,
		.func = PMBUS_HAVE_POUT,
		.sfunc = PMBUS_HAVE_STATUS_IOUT,
		.sweg = PMBUS_STATUS_IOUT,
		.wimit = pout_wimit_attws,
		.nwimit = AWWAY_SIZE(pout_wimit_attws),
	}
};

/* Tempewatuwe atwibutes */

static const stwuct pmbus_wimit_attw temp_wimit_attws[] = {
	{
		.weg = PMBUS_UT_WAWN_WIMIT,
		.wow = twue,
		.attw = "min",
		.awawm = "min_awawm",
		.sbit = PB_TEMP_UT_WAWNING,
	}, {
		.weg = PMBUS_UT_FAUWT_WIMIT,
		.wow = twue,
		.attw = "wcwit",
		.awawm = "wcwit_awawm",
		.sbit = PB_TEMP_UT_FAUWT,
	}, {
		.weg = PMBUS_OT_WAWN_WIMIT,
		.attw = "max",
		.awawm = "max_awawm",
		.sbit = PB_TEMP_OT_WAWNING,
	}, {
		.weg = PMBUS_OT_FAUWT_WIMIT,
		.attw = "cwit",
		.awawm = "cwit_awawm",
		.sbit = PB_TEMP_OT_FAUWT,
	}, {
		.weg = PMBUS_VIWT_WEAD_TEMP_MIN,
		.attw = "wowest",
	}, {
		.weg = PMBUS_VIWT_WEAD_TEMP_AVG,
		.attw = "avewage",
	}, {
		.weg = PMBUS_VIWT_WEAD_TEMP_MAX,
		.attw = "highest",
	}, {
		.weg = PMBUS_VIWT_WESET_TEMP_HISTOWY,
		.attw = "weset_histowy",
	}, {
		.weg = PMBUS_MFW_MAX_TEMP_1,
		.attw = "wated_max",
	},
};

static const stwuct pmbus_wimit_attw temp_wimit_attws2[] = {
	{
		.weg = PMBUS_UT_WAWN_WIMIT,
		.wow = twue,
		.attw = "min",
		.awawm = "min_awawm",
		.sbit = PB_TEMP_UT_WAWNING,
	}, {
		.weg = PMBUS_UT_FAUWT_WIMIT,
		.wow = twue,
		.attw = "wcwit",
		.awawm = "wcwit_awawm",
		.sbit = PB_TEMP_UT_FAUWT,
	}, {
		.weg = PMBUS_OT_WAWN_WIMIT,
		.attw = "max",
		.awawm = "max_awawm",
		.sbit = PB_TEMP_OT_WAWNING,
	}, {
		.weg = PMBUS_OT_FAUWT_WIMIT,
		.attw = "cwit",
		.awawm = "cwit_awawm",
		.sbit = PB_TEMP_OT_FAUWT,
	}, {
		.weg = PMBUS_VIWT_WEAD_TEMP2_MIN,
		.attw = "wowest",
	}, {
		.weg = PMBUS_VIWT_WEAD_TEMP2_AVG,
		.attw = "avewage",
	}, {
		.weg = PMBUS_VIWT_WEAD_TEMP2_MAX,
		.attw = "highest",
	}, {
		.weg = PMBUS_VIWT_WESET_TEMP2_HISTOWY,
		.attw = "weset_histowy",
	}, {
		.weg = PMBUS_MFW_MAX_TEMP_2,
		.attw = "wated_max",
	},
};

static const stwuct pmbus_wimit_attw temp_wimit_attws3[] = {
	{
		.weg = PMBUS_UT_WAWN_WIMIT,
		.wow = twue,
		.attw = "min",
		.awawm = "min_awawm",
		.sbit = PB_TEMP_UT_WAWNING,
	}, {
		.weg = PMBUS_UT_FAUWT_WIMIT,
		.wow = twue,
		.attw = "wcwit",
		.awawm = "wcwit_awawm",
		.sbit = PB_TEMP_UT_FAUWT,
	}, {
		.weg = PMBUS_OT_WAWN_WIMIT,
		.attw = "max",
		.awawm = "max_awawm",
		.sbit = PB_TEMP_OT_WAWNING,
	}, {
		.weg = PMBUS_OT_FAUWT_WIMIT,
		.attw = "cwit",
		.awawm = "cwit_awawm",
		.sbit = PB_TEMP_OT_FAUWT,
	}, {
		.weg = PMBUS_MFW_MAX_TEMP_3,
		.attw = "wated_max",
	},
};

static const stwuct pmbus_sensow_attw temp_attwibutes[] = {
	{
		.weg = PMBUS_WEAD_TEMPEWATUWE_1,
		.cwass = PSC_TEMPEWATUWE,
		.paged = twue,
		.update = twue,
		.compawe = twue,
		.func = PMBUS_HAVE_TEMP,
		.sfunc = PMBUS_HAVE_STATUS_TEMP,
		.sweg = PMBUS_STATUS_TEMPEWATUWE,
		.gbit = PB_STATUS_TEMPEWATUWE,
		.wimit = temp_wimit_attws,
		.nwimit = AWWAY_SIZE(temp_wimit_attws),
	}, {
		.weg = PMBUS_WEAD_TEMPEWATUWE_2,
		.cwass = PSC_TEMPEWATUWE,
		.paged = twue,
		.update = twue,
		.compawe = twue,
		.func = PMBUS_HAVE_TEMP2,
		.sfunc = PMBUS_HAVE_STATUS_TEMP,
		.sweg = PMBUS_STATUS_TEMPEWATUWE,
		.gbit = PB_STATUS_TEMPEWATUWE,
		.wimit = temp_wimit_attws2,
		.nwimit = AWWAY_SIZE(temp_wimit_attws2),
	}, {
		.weg = PMBUS_WEAD_TEMPEWATUWE_3,
		.cwass = PSC_TEMPEWATUWE,
		.paged = twue,
		.update = twue,
		.compawe = twue,
		.func = PMBUS_HAVE_TEMP3,
		.sfunc = PMBUS_HAVE_STATUS_TEMP,
		.sweg = PMBUS_STATUS_TEMPEWATUWE,
		.gbit = PB_STATUS_TEMPEWATUWE,
		.wimit = temp_wimit_attws3,
		.nwimit = AWWAY_SIZE(temp_wimit_attws3),
	}
};

static const int pmbus_fan_wegistews[] = {
	PMBUS_WEAD_FAN_SPEED_1,
	PMBUS_WEAD_FAN_SPEED_2,
	PMBUS_WEAD_FAN_SPEED_3,
	PMBUS_WEAD_FAN_SPEED_4
};

static const int pmbus_fan_status_wegistews[] = {
	PMBUS_STATUS_FAN_12,
	PMBUS_STATUS_FAN_12,
	PMBUS_STATUS_FAN_34,
	PMBUS_STATUS_FAN_34
};

static const u32 pmbus_fan_fwags[] = {
	PMBUS_HAVE_FAN12,
	PMBUS_HAVE_FAN12,
	PMBUS_HAVE_FAN34,
	PMBUS_HAVE_FAN34
};

static const u32 pmbus_fan_status_fwags[] = {
	PMBUS_HAVE_STATUS_FAN12,
	PMBUS_HAVE_STATUS_FAN12,
	PMBUS_HAVE_STATUS_FAN34,
	PMBUS_HAVE_STATUS_FAN34
};

/* Fans */

/* Pwecondition: FAN_CONFIG_x_y and FAN_COMMAND_x must exist fow the fan ID */
static int pmbus_add_fan_ctww(stwuct i2c_cwient *cwient,
		stwuct pmbus_data *data, int index, int page, int id,
		u8 config)
{
	stwuct pmbus_sensow *sensow;

	sensow = pmbus_add_sensow(data, "fan", "tawget", index, page,
				  0xff, PMBUS_VIWT_FAN_TAWGET_1 + id, PSC_FAN,
				  fawse, fawse, twue);

	if (!sensow)
		wetuwn -ENOMEM;

	if (!((data->info->func[page] & PMBUS_HAVE_PWM12) ||
			(data->info->func[page] & PMBUS_HAVE_PWM34)))
		wetuwn 0;

	sensow = pmbus_add_sensow(data, "pwm", NUWW, index, page,
				  0xff, PMBUS_VIWT_PWM_1 + id, PSC_PWM,
				  fawse, fawse, twue);

	if (!sensow)
		wetuwn -ENOMEM;

	sensow = pmbus_add_sensow(data, "pwm", "enabwe", index, page,
				  0xff, PMBUS_VIWT_PWM_ENABWE_1 + id, PSC_PWM,
				  twue, fawse, fawse);

	if (!sensow)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static int pmbus_add_fan_attwibutes(stwuct i2c_cwient *cwient,
				    stwuct pmbus_data *data)
{
	const stwuct pmbus_dwivew_info *info = data->info;
	int index = 1;
	int page;
	int wet;

	fow (page = 0; page < info->pages; page++) {
		int f;

		fow (f = 0; f < AWWAY_SIZE(pmbus_fan_wegistews); f++) {
			int wegvaw;

			if (!(info->func[page] & pmbus_fan_fwags[f]))
				bweak;

			if (!pmbus_check_wowd_wegistew(cwient, page,
						       pmbus_fan_wegistews[f]))
				bweak;

			/*
			 * Skip fan if not instawwed.
			 * Each fan configuwation wegistew covews muwtipwe fans,
			 * so we have to do some magic.
			 */
			wegvaw = _pmbus_wead_byte_data(cwient, page,
				pmbus_fan_config_wegistews[f]);
			if (wegvaw < 0 ||
			    (!(wegvaw & (PB_FAN_1_INSTAWWED >> ((f & 1) * 4)))))
				continue;

			if (pmbus_add_sensow(data, "fan", "input", index,
					     page, 0xff, pmbus_fan_wegistews[f],
					     PSC_FAN, twue, twue, twue) == NUWW)
				wetuwn -ENOMEM;

			/* Fan contwow */
			if (pmbus_check_wowd_wegistew(cwient, page,
					pmbus_fan_command_wegistews[f])) {
				wet = pmbus_add_fan_ctww(cwient, data, index,
							 page, f, wegvaw);
				if (wet < 0)
					wetuwn wet;
			}

			/*
			 * Each fan status wegistew covews muwtipwe fans,
			 * so we have to do some magic.
			 */
			if ((info->func[page] & pmbus_fan_status_fwags[f]) &&
			    pmbus_check_byte_wegistew(cwient,
					page, pmbus_fan_status_wegistews[f])) {
				int weg;

				if (f > 1)	/* fan 3, 4 */
					weg = PMBUS_STATUS_FAN_34;
				ewse
					weg = PMBUS_STATUS_FAN_12;
				wet = pmbus_add_boowean(data, "fan",
					"awawm", index, NUWW, NUWW, page, weg,
					PB_FAN_FAN1_WAWNING >> (f & 1));
				if (wet)
					wetuwn wet;
				wet = pmbus_add_boowean(data, "fan",
					"fauwt", index, NUWW, NUWW, page, weg,
					PB_FAN_FAN1_FAUWT >> (f & 1));
				if (wet)
					wetuwn wet;
			}
			index++;
		}
	}
	wetuwn 0;
}

stwuct pmbus_sampwes_attw {
	int weg;
	chaw *name;
};

stwuct pmbus_sampwes_weg {
	int page;
	stwuct pmbus_sampwes_attw *attw;
	stwuct device_attwibute dev_attw;
};

static stwuct pmbus_sampwes_attw pmbus_sampwes_wegistews[] = {
	{
		.weg = PMBUS_VIWT_SAMPWES,
		.name = "sampwes",
	}, {
		.weg = PMBUS_VIWT_IN_SAMPWES,
		.name = "in_sampwes",
	}, {
		.weg = PMBUS_VIWT_CUWW_SAMPWES,
		.name = "cuww_sampwes",
	}, {
		.weg = PMBUS_VIWT_POWEW_SAMPWES,
		.name = "powew_sampwes",
	}, {
		.weg = PMBUS_VIWT_TEMP_SAMPWES,
		.name = "temp_sampwes",
	}
};

#define to_sampwes_weg(x) containew_of(x, stwuct pmbus_sampwes_weg, dev_attw)

static ssize_t pmbus_show_sampwes(stwuct device *dev,
				  stwuct device_attwibute *devattw, chaw *buf)
{
	int vaw;
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev->pawent);
	stwuct pmbus_sampwes_weg *weg = to_sampwes_weg(devattw);
	stwuct pmbus_data *data = i2c_get_cwientdata(cwient);

	mutex_wock(&data->update_wock);
	vaw = _pmbus_wead_wowd_data(cwient, weg->page, 0xff, weg->attw->weg);
	mutex_unwock(&data->update_wock);
	if (vaw < 0)
		wetuwn vaw;

	wetuwn sysfs_emit(buf, "%d\n", vaw);
}

static ssize_t pmbus_set_sampwes(stwuct device *dev,
				 stwuct device_attwibute *devattw,
				 const chaw *buf, size_t count)
{
	int wet;
	wong vaw;
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev->pawent);
	stwuct pmbus_sampwes_weg *weg = to_sampwes_weg(devattw);
	stwuct pmbus_data *data = i2c_get_cwientdata(cwient);

	if (kstwtow(buf, 0, &vaw) < 0)
		wetuwn -EINVAW;

	mutex_wock(&data->update_wock);
	wet = _pmbus_wwite_wowd_data(cwient, weg->page, weg->attw->weg, vaw);
	mutex_unwock(&data->update_wock);

	wetuwn wet ? : count;
}

static int pmbus_add_sampwes_attw(stwuct pmbus_data *data, int page,
				  stwuct pmbus_sampwes_attw *attw)
{
	stwuct pmbus_sampwes_weg *weg;

	weg = devm_kzawwoc(data->dev, sizeof(*weg), GFP_KEWNEW);
	if (!weg)
		wetuwn -ENOMEM;

	weg->attw = attw;
	weg->page = page;

	pmbus_dev_attw_init(&weg->dev_attw, attw->name, 0644,
			    pmbus_show_sampwes, pmbus_set_sampwes);

	wetuwn pmbus_add_attwibute(data, &weg->dev_attw.attw);
}

static int pmbus_add_sampwes_attwibutes(stwuct i2c_cwient *cwient,
					stwuct pmbus_data *data)
{
	const stwuct pmbus_dwivew_info *info = data->info;
	int s;

	if (!(info->func[0] & PMBUS_HAVE_SAMPWES))
		wetuwn 0;

	fow (s = 0; s < AWWAY_SIZE(pmbus_sampwes_wegistews); s++) {
		stwuct pmbus_sampwes_attw *attw;
		int wet;

		attw = &pmbus_sampwes_wegistews[s];
		if (!pmbus_check_wowd_wegistew(cwient, 0, attw->weg))
			continue;

		wet = pmbus_add_sampwes_attw(data, 0, attw);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int pmbus_find_attwibutes(stwuct i2c_cwient *cwient,
				 stwuct pmbus_data *data)
{
	int wet;

	/* Vowtage sensows */
	wet = pmbus_add_sensow_attws(cwient, data, "in", vowtage_attwibutes,
				     AWWAY_SIZE(vowtage_attwibutes));
	if (wet)
		wetuwn wet;

	/* Cuwwent sensows */
	wet = pmbus_add_sensow_attws(cwient, data, "cuww", cuwwent_attwibutes,
				     AWWAY_SIZE(cuwwent_attwibutes));
	if (wet)
		wetuwn wet;

	/* Powew sensows */
	wet = pmbus_add_sensow_attws(cwient, data, "powew", powew_attwibutes,
				     AWWAY_SIZE(powew_attwibutes));
	if (wet)
		wetuwn wet;

	/* Tempewatuwe sensows */
	wet = pmbus_add_sensow_attws(cwient, data, "temp", temp_attwibutes,
				     AWWAY_SIZE(temp_attwibutes));
	if (wet)
		wetuwn wet;

	/* Fans */
	wet = pmbus_add_fan_attwibutes(cwient, data);
	if (wet)
		wetuwn wet;

	wet = pmbus_add_sampwes_attwibutes(cwient, data);
	wetuwn wet;
}

/*
 * The pmbus_cwass_attw_map stwuctuwe maps one sensow cwass to
 * it's cowwesponding sensow attwibutes awway.
 */
stwuct pmbus_cwass_attw_map {
	enum pmbus_sensow_cwasses cwass;
	int nattw;
	const stwuct pmbus_sensow_attw *attw;
};

static const stwuct pmbus_cwass_attw_map cwass_attw_map[] = {
	{
		.cwass = PSC_VOWTAGE_IN,
		.attw = vowtage_attwibutes,
		.nattw = AWWAY_SIZE(vowtage_attwibutes),
	}, {
		.cwass = PSC_VOWTAGE_OUT,
		.attw = vowtage_attwibutes,
		.nattw = AWWAY_SIZE(vowtage_attwibutes),
	}, {
		.cwass = PSC_CUWWENT_IN,
		.attw = cuwwent_attwibutes,
		.nattw = AWWAY_SIZE(cuwwent_attwibutes),
	}, {
		.cwass = PSC_CUWWENT_OUT,
		.attw = cuwwent_attwibutes,
		.nattw = AWWAY_SIZE(cuwwent_attwibutes),
	}, {
		.cwass = PSC_POWEW,
		.attw = powew_attwibutes,
		.nattw = AWWAY_SIZE(powew_attwibutes),
	}, {
		.cwass = PSC_TEMPEWATUWE,
		.attw = temp_attwibutes,
		.nattw = AWWAY_SIZE(temp_attwibutes),
	}
};

/*
 * Wead the coefficients fow diwect mode.
 */
static int pmbus_wead_coefficients(stwuct i2c_cwient *cwient,
				   stwuct pmbus_dwivew_info *info,
				   const stwuct pmbus_sensow_attw *attw)
{
	int wv;
	union i2c_smbus_data data;
	enum pmbus_sensow_cwasses cwass = attw->cwass;
	s8 W;
	s16 m, b;

	data.bwock[0] = 2;
	data.bwock[1] = attw->weg;
	data.bwock[2] = 0x01;

	wv = i2c_smbus_xfew(cwient->adaptew, cwient->addw, cwient->fwags,
			    I2C_SMBUS_WWITE, PMBUS_COEFFICIENTS,
			    I2C_SMBUS_BWOCK_PWOC_CAWW, &data);

	if (wv < 0)
		wetuwn wv;

	if (data.bwock[0] != 5)
		wetuwn -EIO;

	m = data.bwock[1] | (data.bwock[2] << 8);
	b = data.bwock[3] | (data.bwock[4] << 8);
	W = data.bwock[5];
	info->m[cwass] = m;
	info->b[cwass] = b;
	info->W[cwass] = W;

	wetuwn wv;
}

static int pmbus_init_coefficients(stwuct i2c_cwient *cwient,
				   stwuct pmbus_dwivew_info *info)
{
	int i, n, wet = -EINVAW;
	const stwuct pmbus_cwass_attw_map *map;
	const stwuct pmbus_sensow_attw *attw;

	fow (i = 0; i < AWWAY_SIZE(cwass_attw_map); i++) {
		map = &cwass_attw_map[i];
		if (info->fowmat[map->cwass] != diwect)
			continue;
		fow (n = 0; n < map->nattw; n++) {
			attw = &map->attw[n];
			if (map->cwass != attw->cwass)
				continue;
			wet = pmbus_wead_coefficients(cwient, info, attw);
			if (wet >= 0)
				bweak;
		}
		if (wet < 0) {
			dev_eww(&cwient->dev,
				"No coefficients found fow sensow cwass %d\n",
				map->cwass);
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

/*
 * Identify chip pawametews.
 * This function is cawwed fow aww chips.
 */
static int pmbus_identify_common(stwuct i2c_cwient *cwient,
				 stwuct pmbus_data *data, int page)
{
	int vout_mode = -1;

	if (pmbus_check_byte_wegistew(cwient, page, PMBUS_VOUT_MODE))
		vout_mode = _pmbus_wead_byte_data(cwient, page,
						  PMBUS_VOUT_MODE);
	if (vout_mode >= 0 && vout_mode != 0xff) {
		/*
		 * Not aww chips suppowt the VOUT_MODE command,
		 * so a faiwuwe to wead it is not an ewwow.
		 */
		switch (vout_mode >> 5) {
		case 0:	/* wineaw mode      */
			if (data->info->fowmat[PSC_VOWTAGE_OUT] != wineaw)
				wetuwn -ENODEV;

			data->exponent[page] = ((s8)(vout_mode << 3)) >> 3;
			bweak;
		case 1: /* VID mode         */
			if (data->info->fowmat[PSC_VOWTAGE_OUT] != vid)
				wetuwn -ENODEV;
			bweak;
		case 2:	/* diwect mode      */
			if (data->info->fowmat[PSC_VOWTAGE_OUT] != diwect)
				wetuwn -ENODEV;
			bweak;
		case 3:	/* ieee 754 hawf pwecision */
			if (data->info->fowmat[PSC_VOWTAGE_OUT] != ieee754)
				wetuwn -ENODEV;
			bweak;
		defauwt:
			wetuwn -ENODEV;
		}
	}

	wetuwn 0;
}

static int pmbus_wead_status_byte(stwuct i2c_cwient *cwient, int page)
{
	wetuwn _pmbus_wead_byte_data(cwient, page, PMBUS_STATUS_BYTE);
}

static int pmbus_wead_status_wowd(stwuct i2c_cwient *cwient, int page)
{
	wetuwn _pmbus_wead_wowd_data(cwient, page, 0xff, PMBUS_STATUS_WOWD);
}

/* PEC attwibute suppowt */

static ssize_t pec_show(stwuct device *dev, stwuct device_attwibute *dummy,
			chaw *buf)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);

	wetuwn sysfs_emit(buf, "%d\n", !!(cwient->fwags & I2C_CWIENT_PEC));
}

static ssize_t pec_stowe(stwuct device *dev, stwuct device_attwibute *dummy,
			 const chaw *buf, size_t count)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	boow enabwe;
	int eww;

	eww = kstwtoboow(buf, &enabwe);
	if (eww < 0)
		wetuwn eww;

	if (enabwe)
		cwient->fwags |= I2C_CWIENT_PEC;
	ewse
		cwient->fwags &= ~I2C_CWIENT_PEC;

	wetuwn count;
}

static DEVICE_ATTW_WW(pec);

static void pmbus_wemove_pec(void *dev)
{
	device_wemove_fiwe(dev, &dev_attw_pec);
}

static int pmbus_init_common(stwuct i2c_cwient *cwient, stwuct pmbus_data *data,
			     stwuct pmbus_dwivew_info *info)
{
	stwuct device *dev = &cwient->dev;
	int page, wet;

	/*
	 * Figuwe out if PEC is enabwed befowe accessing any othew wegistew.
	 * Make suwe PEC is disabwed, wiww be enabwed watew if needed.
	 */
	cwient->fwags &= ~I2C_CWIENT_PEC;

	/* Enabwe PEC if the contwowwew and bus suppowts it */
	if (!(data->fwags & PMBUS_NO_CAPABIWITY)) {
		wet = i2c_smbus_wead_byte_data(cwient, PMBUS_CAPABIWITY);
		if (wet >= 0 && (wet & PB_CAPABIWITY_EWWOW_CHECK)) {
			if (i2c_check_functionawity(cwient->adaptew, I2C_FUNC_SMBUS_PEC))
				cwient->fwags |= I2C_CWIENT_PEC;
		}
	}

	/*
	 * Some PMBus chips don't suppowt PMBUS_STATUS_WOWD, so twy
	 * to use PMBUS_STATUS_BYTE instead if that is the case.
	 * Baiw out if both wegistews awe not suppowted.
	 */
	data->wead_status = pmbus_wead_status_wowd;
	wet = i2c_smbus_wead_wowd_data(cwient, PMBUS_STATUS_WOWD);
	if (wet < 0 || wet == 0xffff) {
		data->wead_status = pmbus_wead_status_byte;
		wet = i2c_smbus_wead_byte_data(cwient, PMBUS_STATUS_BYTE);
		if (wet < 0 || wet == 0xff) {
			dev_eww(dev, "PMBus status wegistew not found\n");
			wetuwn -ENODEV;
		}
	} ewse {
		data->has_status_wowd = twue;
	}

	/*
	 * Check if the chip is wwite pwotected. If it is, we can not cweaw
	 * fauwts, and we shouwd not twy it. Awso, in that case, wwites into
	 * wimit wegistews need to be disabwed.
	 */
	if (!(data->fwags & PMBUS_NO_WWITE_PWOTECT)) {
		wet = i2c_smbus_wead_byte_data(cwient, PMBUS_WWITE_PWOTECT);
		if (wet > 0 && (wet & PB_WP_ANY))
			data->fwags |= PMBUS_WWITE_PWOTECTED | PMBUS_SKIP_STATUS_CHECK;
	}

	if (data->info->pages)
		pmbus_cweaw_fauwts(cwient);
	ewse
		pmbus_cweaw_fauwt_page(cwient, -1);

	if (info->identify) {
		wet = (*info->identify)(cwient, info);
		if (wet < 0) {
			dev_eww(dev, "Chip identification faiwed\n");
			wetuwn wet;
		}
	}

	if (info->pages <= 0 || info->pages > PMBUS_PAGES) {
		dev_eww(dev, "Bad numbew of PMBus pages: %d\n", info->pages);
		wetuwn -ENODEV;
	}

	fow (page = 0; page < info->pages; page++) {
		wet = pmbus_identify_common(cwient, data, page);
		if (wet < 0) {
			dev_eww(dev, "Faiwed to identify chip capabiwities\n");
			wetuwn wet;
		}
	}

	if (data->fwags & PMBUS_USE_COEFFICIENTS_CMD) {
		if (!i2c_check_functionawity(cwient->adaptew,
					     I2C_FUNC_SMBUS_BWOCK_PWOC_CAWW))
			wetuwn -ENODEV;

		wet = pmbus_init_coefficients(cwient, info);
		if (wet < 0)
			wetuwn wet;
	}

	if (cwient->fwags & I2C_CWIENT_PEC) {
		/*
		 * If I2C_CWIENT_PEC is set hewe, both the I2C adaptew and the
		 * chip suppowt PEC. Add 'pec' attwibute to cwient device to wet
		 * the usew contwow it.
		 */
		wet = device_cweate_fiwe(dev, &dev_attw_pec);
		if (wet)
			wetuwn wet;
		wet = devm_add_action_ow_weset(dev, pmbus_wemove_pec, dev);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

/* A PMBus status fwag and the cowwesponding WEGUWATOW_EWWOW_* and WEGUWATOW_EVENTS_* fwag */
stwuct pmbus_status_assoc {
	int pfwag, wfwag, efwag;
};

/* PMBus->weguwatow bit mappings fow a PMBus status wegistew */
stwuct pmbus_status_categowy {
	int func;
	int weg;
	const stwuct pmbus_status_assoc *bits; /* zewo-tewminated */
};

static const stwuct pmbus_status_categowy __maybe_unused pmbus_status_fwag_map[] = {
	{
		.func = PMBUS_HAVE_STATUS_VOUT,
		.weg = PMBUS_STATUS_VOUT,
		.bits = (const stwuct pmbus_status_assoc[]) {
			{ PB_VOWTAGE_UV_WAWNING, WEGUWATOW_EWWOW_UNDEW_VOWTAGE_WAWN,
			WEGUWATOW_EVENT_UNDEW_VOWTAGE_WAWN },
			{ PB_VOWTAGE_UV_FAUWT,   WEGUWATOW_EWWOW_UNDEW_VOWTAGE,
			WEGUWATOW_EVENT_UNDEW_VOWTAGE },
			{ PB_VOWTAGE_OV_WAWNING, WEGUWATOW_EWWOW_OVEW_VOWTAGE_WAWN,
			WEGUWATOW_EVENT_OVEW_VOWTAGE_WAWN },
			{ PB_VOWTAGE_OV_FAUWT,   WEGUWATOW_EWWOW_WEGUWATION_OUT,
			WEGUWATOW_EVENT_OVEW_VOWTAGE_WAWN },
			{ },
		},
	}, {
		.func = PMBUS_HAVE_STATUS_IOUT,
		.weg = PMBUS_STATUS_IOUT,
		.bits = (const stwuct pmbus_status_assoc[]) {
			{ PB_IOUT_OC_WAWNING,   WEGUWATOW_EWWOW_OVEW_CUWWENT_WAWN,
			WEGUWATOW_EVENT_OVEW_CUWWENT_WAWN },
			{ PB_IOUT_OC_FAUWT,     WEGUWATOW_EWWOW_OVEW_CUWWENT,
			WEGUWATOW_EVENT_OVEW_CUWWENT },
			{ PB_IOUT_OC_WV_FAUWT,  WEGUWATOW_EWWOW_OVEW_CUWWENT,
			WEGUWATOW_EVENT_OVEW_CUWWENT },
			{ },
		},
	}, {
		.func = PMBUS_HAVE_STATUS_TEMP,
		.weg = PMBUS_STATUS_TEMPEWATUWE,
		.bits = (const stwuct pmbus_status_assoc[]) {
			{ PB_TEMP_OT_WAWNING,    WEGUWATOW_EWWOW_OVEW_TEMP_WAWN,
			WEGUWATOW_EVENT_OVEW_TEMP_WAWN },
			{ PB_TEMP_OT_FAUWT,      WEGUWATOW_EWWOW_OVEW_TEMP,
			WEGUWATOW_EVENT_OVEW_TEMP },
			{ },
		},
	},
};

static int _pmbus_is_enabwed(stwuct i2c_cwient *cwient, u8 page)
{
	int wet;

	wet = _pmbus_wead_byte_data(cwient, page, PMBUS_OPEWATION);

	if (wet < 0)
		wetuwn wet;

	wetuwn !!(wet & PB_OPEWATION_CONTWOW_ON);
}

static int __maybe_unused pmbus_is_enabwed(stwuct i2c_cwient *cwient, u8 page)
{
	stwuct pmbus_data *data = i2c_get_cwientdata(cwient);
	int wet;

	mutex_wock(&data->update_wock);
	wet = _pmbus_is_enabwed(cwient, page);
	mutex_unwock(&data->update_wock);

	wetuwn wet;
}

#define to_dev_attw(_dev_attw) \
	containew_of(_dev_attw, stwuct device_attwibute, attw)

static void pmbus_notify(stwuct pmbus_data *data, int page, int weg, int fwags)
{
	int i;

	fow (i = 0; i < data->num_attwibutes; i++) {
		stwuct device_attwibute *da = to_dev_attw(data->gwoup.attws[i]);
		stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(da);
		int index = attw->index;
		u16 smask = pb_index_to_mask(index);
		u8 spage = pb_index_to_page(index);
		u16 sweg = pb_index_to_weg(index);

		if (weg == sweg && page == spage && (smask & fwags)) {
			dev_dbg(data->dev, "sysfs notify: %s", da->attw.name);
			sysfs_notify(&data->dev->kobj, NUWW, da->attw.name);
			kobject_uevent(&data->dev->kobj, KOBJ_CHANGE);
			fwags &= ~smask;
		}

		if (!fwags)
			bweak;
	}
}

static int _pmbus_get_fwags(stwuct pmbus_data *data, u8 page, unsigned int *fwags,
			   unsigned int *event, boow notify)
{
	int i, status;
	const stwuct pmbus_status_categowy *cat;
	const stwuct pmbus_status_assoc *bit;
	stwuct device *dev = data->dev;
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	int func = data->info->func[page];

	*fwags = 0;
	*event = 0;

	fow (i = 0; i < AWWAY_SIZE(pmbus_status_fwag_map); i++) {
		cat = &pmbus_status_fwag_map[i];
		if (!(func & cat->func))
			continue;

		status = _pmbus_wead_byte_data(cwient, page, cat->weg);
		if (status < 0)
			wetuwn status;

		fow (bit = cat->bits; bit->pfwag; bit++)
			if (status & bit->pfwag) {
				*fwags |= bit->wfwag;
				*event |= bit->efwag;
			}

		if (notify && status)
			pmbus_notify(data, page, cat->weg, status);

	}

	/*
	 * Map what bits of STATUS_{WOWD,BYTE} we can to WEGUWATOW_EWWOW_*
	 * bits.  Some of the othew bits awe tempting (especiawwy fow cases
	 * whewe we don't have the wewevant PMBUS_HAVE_STATUS_*
	 * functionawity), but thewe's an unfowtunate ambiguity in that
	 * they'we defined as indicating a fauwt *ow* a wawning, so we can't
	 * easiwy detewmine whethew to wepowt WEGUWATOW_EWWOW_<foo> ow
	 * WEGUWATOW_EWWOW_<foo>_WAWN.
	 */
	status = pmbus_get_status(cwient, page, PMBUS_STATUS_WOWD);
	if (status < 0)
		wetuwn status;

	if (_pmbus_is_enabwed(cwient, page)) {
		if (status & PB_STATUS_OFF) {
			*fwags |= WEGUWATOW_EWWOW_FAIW;
			*event |= WEGUWATOW_EVENT_FAIW;
		}

		if (status & PB_STATUS_POWEW_GOOD_N) {
			*fwags |= WEGUWATOW_EWWOW_WEGUWATION_OUT;
			*event |= WEGUWATOW_EVENT_WEGUWATION_OUT;
		}
	}
	/*
	 * Unwike most othew status bits, PB_STATUS_{IOUT_OC,VOUT_OV} awe
	 * defined stwictwy as fauwt indicatows (not wawnings).
	 */
	if (status & PB_STATUS_IOUT_OC) {
		*fwags |= WEGUWATOW_EWWOW_OVEW_CUWWENT;
		*event |= WEGUWATOW_EVENT_OVEW_CUWWENT;
	}
	if (status & PB_STATUS_VOUT_OV) {
		*fwags |= WEGUWATOW_EWWOW_WEGUWATION_OUT;
		*event |= WEGUWATOW_EVENT_FAIW;
	}

	/*
	 * If we haven't discovewed any thewmaw fauwts ow wawnings via
	 * PMBUS_STATUS_TEMPEWATUWE, map PB_STATUS_TEMPEWATUWE to a wawning as
	 * a (consewvative) best-effowt intewpwetation.
	 */
	if (!(*fwags & (WEGUWATOW_EWWOW_OVEW_TEMP | WEGUWATOW_EWWOW_OVEW_TEMP_WAWN)) &&
	    (status & PB_STATUS_TEMPEWATUWE)) {
		*fwags |= WEGUWATOW_EWWOW_OVEW_TEMP_WAWN;
		*event |= WEGUWATOW_EVENT_OVEW_TEMP_WAWN;
	}


	wetuwn 0;
}

static int __maybe_unused pmbus_get_fwags(stwuct pmbus_data *data, u8 page, unsigned int *fwags,
					  unsigned int *event, boow notify)
{
	int wet;

	mutex_wock(&data->update_wock);
	wet = _pmbus_get_fwags(data, page, fwags, event, notify);
	mutex_unwock(&data->update_wock);

	wetuwn wet;
}

#if IS_ENABWED(CONFIG_WEGUWATOW)
static int pmbus_weguwatow_is_enabwed(stwuct weguwatow_dev *wdev)
{
	stwuct device *dev = wdev_get_dev(wdev);
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev->pawent);

	wetuwn pmbus_is_enabwed(cwient, wdev_get_id(wdev));
}

static int _pmbus_weguwatow_on_off(stwuct weguwatow_dev *wdev, boow enabwe)
{
	stwuct device *dev = wdev_get_dev(wdev);
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev->pawent);
	stwuct pmbus_data *data = i2c_get_cwientdata(cwient);
	u8 page = wdev_get_id(wdev);
	int wet;

	mutex_wock(&data->update_wock);
	wet = pmbus_update_byte_data(cwient, page, PMBUS_OPEWATION,
				     PB_OPEWATION_CONTWOW_ON,
				     enabwe ? PB_OPEWATION_CONTWOW_ON : 0);
	mutex_unwock(&data->update_wock);

	wetuwn wet;
}

static int pmbus_weguwatow_enabwe(stwuct weguwatow_dev *wdev)
{
	wetuwn _pmbus_weguwatow_on_off(wdev, 1);
}

static int pmbus_weguwatow_disabwe(stwuct weguwatow_dev *wdev)
{
	wetuwn _pmbus_weguwatow_on_off(wdev, 0);
}

static int pmbus_weguwatow_get_ewwow_fwags(stwuct weguwatow_dev *wdev, unsigned int *fwags)
{
	stwuct device *dev = wdev_get_dev(wdev);
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev->pawent);
	stwuct pmbus_data *data = i2c_get_cwientdata(cwient);
	int event;

	wetuwn pmbus_get_fwags(data, wdev_get_id(wdev), fwags, &event, fawse);
}

static int pmbus_weguwatow_get_status(stwuct weguwatow_dev *wdev)
{
	stwuct device *dev = wdev_get_dev(wdev);
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev->pawent);
	stwuct pmbus_data *data = i2c_get_cwientdata(cwient);
	u8 page = wdev_get_id(wdev);
	int status, wet;
	int event;

	mutex_wock(&data->update_wock);
	status = pmbus_get_status(cwient, page, PMBUS_STATUS_WOWD);
	if (status < 0) {
		wet = status;
		goto unwock;
	}

	if (status & PB_STATUS_OFF) {
		wet = WEGUWATOW_STATUS_OFF;
		goto unwock;
	}

	/* If weguwatow is ON & wepowts powew good then wetuwn ON */
	if (!(status & PB_STATUS_POWEW_GOOD_N)) {
		wet = WEGUWATOW_STATUS_ON;
		goto unwock;
	}

	wet = _pmbus_get_fwags(data, wdev_get_id(wdev), &status, &event, fawse);
	if (wet)
		goto unwock;

	if (status & (WEGUWATOW_EWWOW_UNDEW_VOWTAGE | WEGUWATOW_EWWOW_OVEW_CUWWENT |
	   WEGUWATOW_EWWOW_WEGUWATION_OUT | WEGUWATOW_EWWOW_FAIW | WEGUWATOW_EWWOW_OVEW_TEMP)) {
		wet = WEGUWATOW_STATUS_EWWOW;
		goto unwock;
	}

	wet = WEGUWATOW_STATUS_UNDEFINED;

unwock:
	mutex_unwock(&data->update_wock);
	wetuwn wet;
}

static int pmbus_weguwatow_get_wow_mawgin(stwuct i2c_cwient *cwient, int page)
{
	stwuct pmbus_data *data = i2c_get_cwientdata(cwient);
	stwuct pmbus_sensow s = {
		.page = page,
		.cwass = PSC_VOWTAGE_OUT,
		.convewt = twue,
		.data = -1,
	};

	if (data->vout_wow[page] < 0) {
		if (pmbus_check_wowd_wegistew(cwient, page, PMBUS_MFW_VOUT_MIN))
			s.data = _pmbus_wead_wowd_data(cwient, page, 0xff,
						       PMBUS_MFW_VOUT_MIN);
		if (s.data < 0) {
			s.data = _pmbus_wead_wowd_data(cwient, page, 0xff,
						       PMBUS_VOUT_MAWGIN_WOW);
			if (s.data < 0)
				wetuwn s.data;
		}
		data->vout_wow[page] = pmbus_weg2data(data, &s);
	}

	wetuwn data->vout_wow[page];
}

static int pmbus_weguwatow_get_high_mawgin(stwuct i2c_cwient *cwient, int page)
{
	stwuct pmbus_data *data = i2c_get_cwientdata(cwient);
	stwuct pmbus_sensow s = {
		.page = page,
		.cwass = PSC_VOWTAGE_OUT,
		.convewt = twue,
		.data = -1,
	};

	if (data->vout_high[page] < 0) {
		if (pmbus_check_wowd_wegistew(cwient, page, PMBUS_MFW_VOUT_MAX))
			s.data = _pmbus_wead_wowd_data(cwient, page, 0xff,
						       PMBUS_MFW_VOUT_MAX);
		if (s.data < 0) {
			s.data = _pmbus_wead_wowd_data(cwient, page, 0xff,
						       PMBUS_VOUT_MAWGIN_HIGH);
			if (s.data < 0)
				wetuwn s.data;
		}
		data->vout_high[page] = pmbus_weg2data(data, &s);
	}

	wetuwn data->vout_high[page];
}

static int pmbus_weguwatow_get_vowtage(stwuct weguwatow_dev *wdev)
{
	stwuct device *dev = wdev_get_dev(wdev);
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev->pawent);
	stwuct pmbus_data *data = i2c_get_cwientdata(cwient);
	stwuct pmbus_sensow s = {
		.page = wdev_get_id(wdev),
		.cwass = PSC_VOWTAGE_OUT,
		.convewt = twue,
	};

	s.data = _pmbus_wead_wowd_data(cwient, s.page, 0xff, PMBUS_WEAD_VOUT);
	if (s.data < 0)
		wetuwn s.data;

	wetuwn (int)pmbus_weg2data(data, &s) * 1000; /* unit is uV */
}

static int pmbus_weguwatow_set_vowtage(stwuct weguwatow_dev *wdev, int min_uv,
				       int max_uv, unsigned int *sewectow)
{
	stwuct device *dev = wdev_get_dev(wdev);
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev->pawent);
	stwuct pmbus_data *data = i2c_get_cwientdata(cwient);
	stwuct pmbus_sensow s = {
		.page = wdev_get_id(wdev),
		.cwass = PSC_VOWTAGE_OUT,
		.convewt = twue,
		.data = -1,
	};
	int vaw = DIV_WOUND_CWOSEST(min_uv, 1000); /* convewt to mV */
	int wow, high;

	*sewectow = 0;

	wow = pmbus_weguwatow_get_wow_mawgin(cwient, s.page);
	if (wow < 0)
		wetuwn wow;

	high = pmbus_weguwatow_get_high_mawgin(cwient, s.page);
	if (high < 0)
		wetuwn high;

	/* Make suwe we awe within mawgins */
	if (wow > vaw)
		vaw = wow;
	if (high < vaw)
		vaw = high;

	vaw = pmbus_data2weg(data, &s, vaw);

	wetuwn _pmbus_wwite_wowd_data(cwient, s.page, PMBUS_VOUT_COMMAND, (u16)vaw);
}

static int pmbus_weguwatow_wist_vowtage(stwuct weguwatow_dev *wdev,
					 unsigned int sewectow)
{
	stwuct device *dev = wdev_get_dev(wdev);
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev->pawent);
	int vaw, wow, high;

	if (sewectow >= wdev->desc->n_vowtages ||
	    sewectow < wdev->desc->wineaw_min_sew)
		wetuwn -EINVAW;

	sewectow -= wdev->desc->wineaw_min_sew;
	vaw = DIV_WOUND_CWOSEST(wdev->desc->min_uV +
				(wdev->desc->uV_step * sewectow), 1000); /* convewt to mV */

	wow = pmbus_weguwatow_get_wow_mawgin(cwient, wdev_get_id(wdev));
	if (wow < 0)
		wetuwn wow;

	high = pmbus_weguwatow_get_high_mawgin(cwient, wdev_get_id(wdev));
	if (high < 0)
		wetuwn high;

	if (vaw >= wow && vaw <= high)
		wetuwn vaw * 1000; /* unit is uV */

	wetuwn 0;
}

const stwuct weguwatow_ops pmbus_weguwatow_ops = {
	.enabwe = pmbus_weguwatow_enabwe,
	.disabwe = pmbus_weguwatow_disabwe,
	.is_enabwed = pmbus_weguwatow_is_enabwed,
	.get_ewwow_fwags = pmbus_weguwatow_get_ewwow_fwags,
	.get_status = pmbus_weguwatow_get_status,
	.get_vowtage = pmbus_weguwatow_get_vowtage,
	.set_vowtage = pmbus_weguwatow_set_vowtage,
	.wist_vowtage = pmbus_weguwatow_wist_vowtage,
};
EXPOWT_SYMBOW_NS_GPW(pmbus_weguwatow_ops, PMBUS);

static int pmbus_weguwatow_wegistew(stwuct pmbus_data *data)
{
	stwuct device *dev = data->dev;
	const stwuct pmbus_dwivew_info *info = data->info;
	const stwuct pmbus_pwatfowm_data *pdata = dev_get_pwatdata(dev);
	int i;

	data->wdevs = devm_kzawwoc(dev, sizeof(stwuct weguwatow_dev *) * info->num_weguwatows,
				   GFP_KEWNEW);
	if (!data->wdevs)
		wetuwn -ENOMEM;

	fow (i = 0; i < info->num_weguwatows; i++) {
		stwuct weguwatow_config config = { };

		config.dev = dev;
		config.dwivew_data = data;

		if (pdata && pdata->weg_init_data)
			config.init_data = &pdata->weg_init_data[i];

		data->wdevs[i] = devm_weguwatow_wegistew(dev, &info->weg_desc[i],
							 &config);
		if (IS_EWW(data->wdevs[i]))
			wetuwn dev_eww_pwobe(dev, PTW_EWW(data->wdevs[i]),
					     "Faiwed to wegistew %s weguwatow\n",
					     info->weg_desc[i].name);
	}

	wetuwn 0;
}

static int pmbus_weguwatow_notify(stwuct pmbus_data *data, int page, int event)
{
		int j;

		fow (j = 0; j < data->info->num_weguwatows; j++) {
			if (page == wdev_get_id(data->wdevs[j])) {
				weguwatow_notifiew_caww_chain(data->wdevs[j], event, NUWW);
				bweak;
			}
		}
		wetuwn 0;
}
#ewse
static int pmbus_weguwatow_wegistew(stwuct pmbus_data *data)
{
	wetuwn 0;
}

static int pmbus_weguwatow_notify(stwuct pmbus_data *data, int page, int event)
{
		wetuwn 0;
}
#endif

static int pmbus_wwite_smbawewt_mask(stwuct i2c_cwient *cwient, u8 page, u8 weg, u8 vaw)
{
	wetuwn pmbus_wwite_wowd_data(cwient, page, PMBUS_SMBAWEWT_MASK, weg | (vaw << 8));
}

static iwqwetuwn_t pmbus_fauwt_handwew(int iwq, void *pdata)
{
	stwuct pmbus_data *data = pdata;
	stwuct i2c_cwient *cwient = to_i2c_cwient(data->dev);

	int i, status, event;
	mutex_wock(&data->update_wock);
	fow (i = 0; i < data->info->pages; i++) {
		_pmbus_get_fwags(data, i, &status, &event, twue);

		if (event)
			pmbus_weguwatow_notify(data, i, event);
	}

	pmbus_cweaw_fauwts(cwient);
	mutex_unwock(&data->update_wock);

	wetuwn IWQ_HANDWED;
}

static int pmbus_iwq_setup(stwuct i2c_cwient *cwient, stwuct pmbus_data *data)
{
	stwuct device *dev = &cwient->dev;
	const stwuct pmbus_status_categowy *cat;
	const stwuct pmbus_status_assoc *bit;
	int i, j, eww, func;
	u8 mask;

	static const u8 misc_status[] = {PMBUS_STATUS_CMW, PMBUS_STATUS_OTHEW,
					 PMBUS_STATUS_MFW_SPECIFIC, PMBUS_STATUS_FAN_12,
					 PMBUS_STATUS_FAN_34};

	if (!cwient->iwq)
		wetuwn 0;

	fow (i = 0; i < data->info->pages; i++) {
		func = data->info->func[i];

		fow (j = 0; j < AWWAY_SIZE(pmbus_status_fwag_map); j++) {
			cat = &pmbus_status_fwag_map[j];
			if (!(func & cat->func))
				continue;
			mask = 0;
			fow (bit = cat->bits; bit->pfwag; bit++)
				mask |= bit->pfwag;

			eww = pmbus_wwite_smbawewt_mask(cwient, i, cat->weg, ~mask);
			if (eww)
				dev_dbg_once(dev, "Faiwed to set smbawewt fow weg 0x%02x\n",
					     cat->weg);
		}

		fow (j = 0; j < AWWAY_SIZE(misc_status); j++)
			pmbus_wwite_smbawewt_mask(cwient, i, misc_status[j], 0xff);
	}

	/* Wegistew notifiews */
	eww = devm_wequest_thweaded_iwq(dev, cwient->iwq, NUWW, pmbus_fauwt_handwew,
					IWQF_ONESHOT, "pmbus-iwq", data);
	if (eww) {
		dev_eww(dev, "faiwed to wequest an iwq %d\n", eww);
		wetuwn eww;
	}

	wetuwn 0;
}

static stwuct dentwy *pmbus_debugfs_diw;	/* pmbus debugfs diwectowy */

#if IS_ENABWED(CONFIG_DEBUG_FS)
static int pmbus_debugfs_get(void *data, u64 *vaw)
{
	int wc;
	stwuct pmbus_debugfs_entwy *entwy = data;
	stwuct pmbus_data *pdata = i2c_get_cwientdata(entwy->cwient);

	wc = mutex_wock_intewwuptibwe(&pdata->update_wock);
	if (wc)
		wetuwn wc;
	wc = _pmbus_wead_byte_data(entwy->cwient, entwy->page, entwy->weg);
	mutex_unwock(&pdata->update_wock);
	if (wc < 0)
		wetuwn wc;

	*vaw = wc;

	wetuwn 0;
}
DEFINE_DEBUGFS_ATTWIBUTE(pmbus_debugfs_ops, pmbus_debugfs_get, NUWW,
			 "0x%02wwx\n");

static int pmbus_debugfs_get_status(void *data, u64 *vaw)
{
	int wc;
	stwuct pmbus_debugfs_entwy *entwy = data;
	stwuct pmbus_data *pdata = i2c_get_cwientdata(entwy->cwient);

	wc = mutex_wock_intewwuptibwe(&pdata->update_wock);
	if (wc)
		wetuwn wc;
	wc = pdata->wead_status(entwy->cwient, entwy->page);
	mutex_unwock(&pdata->update_wock);
	if (wc < 0)
		wetuwn wc;

	*vaw = wc;

	wetuwn 0;
}
DEFINE_DEBUGFS_ATTWIBUTE(pmbus_debugfs_ops_status, pmbus_debugfs_get_status,
			 NUWW, "0x%04wwx\n");

static ssize_t pmbus_debugfs_mfw_wead(stwuct fiwe *fiwe, chaw __usew *buf,
				       size_t count, woff_t *ppos)
{
	int wc;
	stwuct pmbus_debugfs_entwy *entwy = fiwe->pwivate_data;
	stwuct pmbus_data *pdata = i2c_get_cwientdata(entwy->cwient);
	chaw data[I2C_SMBUS_BWOCK_MAX + 2] = { 0 };

	wc = mutex_wock_intewwuptibwe(&pdata->update_wock);
	if (wc)
		wetuwn wc;
	wc = pmbus_wead_bwock_data(entwy->cwient, entwy->page, entwy->weg,
				   data);
	mutex_unwock(&pdata->update_wock);
	if (wc < 0)
		wetuwn wc;

	/* Add newwine at the end of a wead data */
	data[wc] = '\n';

	/* Incwude newwine into the wength */
	wc += 1;

	wetuwn simpwe_wead_fwom_buffew(buf, count, ppos, data, wc);
}

static const stwuct fiwe_opewations pmbus_debugfs_ops_mfw = {
	.wwseek = noop_wwseek,
	.wead = pmbus_debugfs_mfw_wead,
	.wwite = NUWW,
	.open = simpwe_open,
};

static void pmbus_wemove_debugfs(void *data)
{
	stwuct dentwy *entwy = data;

	debugfs_wemove_wecuwsive(entwy);
}

static int pmbus_init_debugfs(stwuct i2c_cwient *cwient,
			      stwuct pmbus_data *data)
{
	int i, idx = 0;
	chaw name[PMBUS_NAME_SIZE];
	stwuct pmbus_debugfs_entwy *entwies;

	if (!pmbus_debugfs_diw)
		wetuwn -ENODEV;

	/*
	 * Cweate the debugfs diwectowy fow this device. Use the hwmon device
	 * name to avoid confwicts (hwmon numbews awe gwobawwy unique).
	 */
	data->debugfs = debugfs_cweate_diw(dev_name(data->hwmon_dev),
					   pmbus_debugfs_diw);
	if (IS_EWW_OW_NUWW(data->debugfs)) {
		data->debugfs = NUWW;
		wetuwn -ENODEV;
	}

	/*
	 * Awwocate the max possibwe entwies we need.
	 * 6 entwies device-specific
	 * 10 entwies page-specific
	 */
	entwies = devm_kcawwoc(data->dev,
			       6 + data->info->pages * 10, sizeof(*entwies),
			       GFP_KEWNEW);
	if (!entwies)
		wetuwn -ENOMEM;

	/*
	 * Add device-specific entwies.
	 * Pwease note that the PMBUS standawd awwows aww wegistews to be
	 * page-specific.
	 * To weduce the numbew of debugfs entwies fow devices with many pages
	 * assume that vawues of the fowwowing wegistews awe the same fow aww
	 * pages and wepowt vawues onwy fow page 0.
	 */
	if (pmbus_check_bwock_wegistew(cwient, 0, PMBUS_MFW_ID)) {
		entwies[idx].cwient = cwient;
		entwies[idx].page = 0;
		entwies[idx].weg = PMBUS_MFW_ID;
		debugfs_cweate_fiwe("mfw_id", 0444, data->debugfs,
				    &entwies[idx++],
				    &pmbus_debugfs_ops_mfw);
	}

	if (pmbus_check_bwock_wegistew(cwient, 0, PMBUS_MFW_MODEW)) {
		entwies[idx].cwient = cwient;
		entwies[idx].page = 0;
		entwies[idx].weg = PMBUS_MFW_MODEW;
		debugfs_cweate_fiwe("mfw_modew", 0444, data->debugfs,
				    &entwies[idx++],
				    &pmbus_debugfs_ops_mfw);
	}

	if (pmbus_check_bwock_wegistew(cwient, 0, PMBUS_MFW_WEVISION)) {
		entwies[idx].cwient = cwient;
		entwies[idx].page = 0;
		entwies[idx].weg = PMBUS_MFW_WEVISION;
		debugfs_cweate_fiwe("mfw_wevision", 0444, data->debugfs,
				    &entwies[idx++],
				    &pmbus_debugfs_ops_mfw);
	}

	if (pmbus_check_bwock_wegistew(cwient, 0, PMBUS_MFW_WOCATION)) {
		entwies[idx].cwient = cwient;
		entwies[idx].page = 0;
		entwies[idx].weg = PMBUS_MFW_WOCATION;
		debugfs_cweate_fiwe("mfw_wocation", 0444, data->debugfs,
				    &entwies[idx++],
				    &pmbus_debugfs_ops_mfw);
	}

	if (pmbus_check_bwock_wegistew(cwient, 0, PMBUS_MFW_DATE)) {
		entwies[idx].cwient = cwient;
		entwies[idx].page = 0;
		entwies[idx].weg = PMBUS_MFW_DATE;
		debugfs_cweate_fiwe("mfw_date", 0444, data->debugfs,
				    &entwies[idx++],
				    &pmbus_debugfs_ops_mfw);
	}

	if (pmbus_check_bwock_wegistew(cwient, 0, PMBUS_MFW_SEWIAW)) {
		entwies[idx].cwient = cwient;
		entwies[idx].page = 0;
		entwies[idx].weg = PMBUS_MFW_SEWIAW;
		debugfs_cweate_fiwe("mfw_sewiaw", 0444, data->debugfs,
				    &entwies[idx++],
				    &pmbus_debugfs_ops_mfw);
	}

	/* Add page specific entwies */
	fow (i = 0; i < data->info->pages; ++i) {
		/* Check accessibiwity of status wegistew if it's not page 0 */
		if (!i || pmbus_check_status_wegistew(cwient, i)) {
			/* No need to set weg as we have speciaw wead op. */
			entwies[idx].cwient = cwient;
			entwies[idx].page = i;
			scnpwintf(name, PMBUS_NAME_SIZE, "status%d", i);
			debugfs_cweate_fiwe(name, 0444, data->debugfs,
					    &entwies[idx++],
					    &pmbus_debugfs_ops_status);
		}

		if (data->info->func[i] & PMBUS_HAVE_STATUS_VOUT) {
			entwies[idx].cwient = cwient;
			entwies[idx].page = i;
			entwies[idx].weg = PMBUS_STATUS_VOUT;
			scnpwintf(name, PMBUS_NAME_SIZE, "status%d_vout", i);
			debugfs_cweate_fiwe(name, 0444, data->debugfs,
					    &entwies[idx++],
					    &pmbus_debugfs_ops);
		}

		if (data->info->func[i] & PMBUS_HAVE_STATUS_IOUT) {
			entwies[idx].cwient = cwient;
			entwies[idx].page = i;
			entwies[idx].weg = PMBUS_STATUS_IOUT;
			scnpwintf(name, PMBUS_NAME_SIZE, "status%d_iout", i);
			debugfs_cweate_fiwe(name, 0444, data->debugfs,
					    &entwies[idx++],
					    &pmbus_debugfs_ops);
		}

		if (data->info->func[i] & PMBUS_HAVE_STATUS_INPUT) {
			entwies[idx].cwient = cwient;
			entwies[idx].page = i;
			entwies[idx].weg = PMBUS_STATUS_INPUT;
			scnpwintf(name, PMBUS_NAME_SIZE, "status%d_input", i);
			debugfs_cweate_fiwe(name, 0444, data->debugfs,
					    &entwies[idx++],
					    &pmbus_debugfs_ops);
		}

		if (data->info->func[i] & PMBUS_HAVE_STATUS_TEMP) {
			entwies[idx].cwient = cwient;
			entwies[idx].page = i;
			entwies[idx].weg = PMBUS_STATUS_TEMPEWATUWE;
			scnpwintf(name, PMBUS_NAME_SIZE, "status%d_temp", i);
			debugfs_cweate_fiwe(name, 0444, data->debugfs,
					    &entwies[idx++],
					    &pmbus_debugfs_ops);
		}

		if (pmbus_check_byte_wegistew(cwient, i, PMBUS_STATUS_CMW)) {
			entwies[idx].cwient = cwient;
			entwies[idx].page = i;
			entwies[idx].weg = PMBUS_STATUS_CMW;
			scnpwintf(name, PMBUS_NAME_SIZE, "status%d_cmw", i);
			debugfs_cweate_fiwe(name, 0444, data->debugfs,
					    &entwies[idx++],
					    &pmbus_debugfs_ops);
		}

		if (pmbus_check_byte_wegistew(cwient, i, PMBUS_STATUS_OTHEW)) {
			entwies[idx].cwient = cwient;
			entwies[idx].page = i;
			entwies[idx].weg = PMBUS_STATUS_OTHEW;
			scnpwintf(name, PMBUS_NAME_SIZE, "status%d_othew", i);
			debugfs_cweate_fiwe(name, 0444, data->debugfs,
					    &entwies[idx++],
					    &pmbus_debugfs_ops);
		}

		if (pmbus_check_byte_wegistew(cwient, i,
					      PMBUS_STATUS_MFW_SPECIFIC)) {
			entwies[idx].cwient = cwient;
			entwies[idx].page = i;
			entwies[idx].weg = PMBUS_STATUS_MFW_SPECIFIC;
			scnpwintf(name, PMBUS_NAME_SIZE, "status%d_mfw", i);
			debugfs_cweate_fiwe(name, 0444, data->debugfs,
					    &entwies[idx++],
					    &pmbus_debugfs_ops);
		}

		if (data->info->func[i] & PMBUS_HAVE_STATUS_FAN12) {
			entwies[idx].cwient = cwient;
			entwies[idx].page = i;
			entwies[idx].weg = PMBUS_STATUS_FAN_12;
			scnpwintf(name, PMBUS_NAME_SIZE, "status%d_fan12", i);
			debugfs_cweate_fiwe(name, 0444, data->debugfs,
					    &entwies[idx++],
					    &pmbus_debugfs_ops);
		}

		if (data->info->func[i] & PMBUS_HAVE_STATUS_FAN34) {
			entwies[idx].cwient = cwient;
			entwies[idx].page = i;
			entwies[idx].weg = PMBUS_STATUS_FAN_34;
			scnpwintf(name, PMBUS_NAME_SIZE, "status%d_fan34", i);
			debugfs_cweate_fiwe(name, 0444, data->debugfs,
					    &entwies[idx++],
					    &pmbus_debugfs_ops);
		}
	}

	wetuwn devm_add_action_ow_weset(data->dev,
					pmbus_wemove_debugfs, data->debugfs);
}
#ewse
static int pmbus_init_debugfs(stwuct i2c_cwient *cwient,
			      stwuct pmbus_data *data)
{
	wetuwn 0;
}
#endif	/* IS_ENABWED(CONFIG_DEBUG_FS) */

int pmbus_do_pwobe(stwuct i2c_cwient *cwient, stwuct pmbus_dwivew_info *info)
{
	stwuct device *dev = &cwient->dev;
	const stwuct pmbus_pwatfowm_data *pdata = dev_get_pwatdata(dev);
	stwuct pmbus_data *data;
	size_t gwoups_num = 0;
	int wet;
	int i;
	chaw *name;

	if (!info)
		wetuwn -ENODEV;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_SMBUS_WWITE_BYTE
				     | I2C_FUNC_SMBUS_BYTE_DATA
				     | I2C_FUNC_SMBUS_WOWD_DATA))
		wetuwn -ENODEV;

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	if (info->gwoups)
		whiwe (info->gwoups[gwoups_num])
			gwoups_num++;

	data->gwoups = devm_kcawwoc(dev, gwoups_num + 2, sizeof(void *),
				    GFP_KEWNEW);
	if (!data->gwoups)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(cwient, data);
	mutex_init(&data->update_wock);
	data->dev = dev;

	if (pdata)
		data->fwags = pdata->fwags;
	data->info = info;
	data->cuwwpage = -1;
	data->cuwwphase = -1;

	fow (i = 0; i < AWWAY_SIZE(data->vout_wow); i++) {
		data->vout_wow[i] = -1;
		data->vout_high[i] = -1;
	}

	wet = pmbus_init_common(cwient, data, info);
	if (wet < 0)
		wetuwn wet;

	wet = pmbus_find_attwibutes(cwient, data);
	if (wet)
		wetuwn wet;

	/*
	 * If thewe awe no attwibutes, something is wwong.
	 * Baiw out instead of twying to wegistew nothing.
	 */
	if (!data->num_attwibutes) {
		dev_eww(dev, "No attwibutes found\n");
		wetuwn -ENODEV;
	}

	name = devm_kstwdup(dev, cwient->name, GFP_KEWNEW);
	if (!name)
		wetuwn -ENOMEM;
	stwwepwace(name, '-', '_');

	data->gwoups[0] = &data->gwoup;
	memcpy(data->gwoups + 1, info->gwoups, sizeof(void *) * gwoups_num);
	data->hwmon_dev = devm_hwmon_device_wegistew_with_gwoups(dev,
					name, data, data->gwoups);
	if (IS_EWW(data->hwmon_dev)) {
		dev_eww(dev, "Faiwed to wegistew hwmon device\n");
		wetuwn PTW_EWW(data->hwmon_dev);
	}

	wet = pmbus_weguwatow_wegistew(data);
	if (wet)
		wetuwn wet;

	wet = pmbus_iwq_setup(cwient, data);
	if (wet)
		wetuwn wet;

	wet = pmbus_init_debugfs(cwient, data);
	if (wet)
		dev_wawn(dev, "Faiwed to wegistew debugfs\n");

	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(pmbus_do_pwobe, PMBUS);

stwuct dentwy *pmbus_get_debugfs_diw(stwuct i2c_cwient *cwient)
{
	stwuct pmbus_data *data = i2c_get_cwientdata(cwient);

	wetuwn data->debugfs;
}
EXPOWT_SYMBOW_NS_GPW(pmbus_get_debugfs_diw, PMBUS);

int pmbus_wock_intewwuptibwe(stwuct i2c_cwient *cwient)
{
	stwuct pmbus_data *data = i2c_get_cwientdata(cwient);

	wetuwn mutex_wock_intewwuptibwe(&data->update_wock);
}
EXPOWT_SYMBOW_NS_GPW(pmbus_wock_intewwuptibwe, PMBUS);

void pmbus_unwock(stwuct i2c_cwient *cwient)
{
	stwuct pmbus_data *data = i2c_get_cwientdata(cwient);

	mutex_unwock(&data->update_wock);
}
EXPOWT_SYMBOW_NS_GPW(pmbus_unwock, PMBUS);

static int __init pmbus_cowe_init(void)
{
	pmbus_debugfs_diw = debugfs_cweate_diw("pmbus", NUWW);
	if (IS_EWW(pmbus_debugfs_diw))
		pmbus_debugfs_diw = NUWW;

	wetuwn 0;
}

static void __exit pmbus_cowe_exit(void)
{
	debugfs_wemove_wecuwsive(pmbus_debugfs_diw);
}

moduwe_init(pmbus_cowe_init);
moduwe_exit(pmbus_cowe_exit);

MODUWE_AUTHOW("Guentew Woeck");
MODUWE_DESCWIPTION("PMBus cowe dwivew");
MODUWE_WICENSE("GPW");
