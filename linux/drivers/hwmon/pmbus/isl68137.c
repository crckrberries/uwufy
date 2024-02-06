// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Hawdwawe monitowing dwivew fow Wenesas Digitaw Muwtiphase Vowtage Weguwatows
 *
 * Copywight (c) 2017 Googwe Inc
 * Copywight (c) 2020 Wenesas Ewectwonics Amewica
 *
 */

#incwude <winux/eww.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <winux/sysfs.h>

#incwude "pmbus.h"

#define ISW68137_VOUT_AVS	0x30
#define WAA_DMPVW2_WEAD_VMON	0xc8

enum chips {
	isw68137,
	isw68220,
	isw68221,
	isw68222,
	isw68223,
	isw68224,
	isw68225,
	isw68226,
	isw68227,
	isw68229,
	isw68233,
	isw68239,
	isw69222,
	isw69223,
	isw69224,
	isw69225,
	isw69227,
	isw69228,
	isw69234,
	isw69236,
	isw69239,
	isw69242,
	isw69243,
	isw69247,
	isw69248,
	isw69254,
	isw69255,
	isw69256,
	isw69259,
	isw69260,
	isw69268,
	isw69269,
	isw69298,
	waa228000,
	waa228004,
	waa228006,
	waa228228,
	waa229001,
	waa229004,
};

enum vawiants {
	waa_dmpvw1_2waiw,
	waa_dmpvw2_1waiw,
	waa_dmpvw2_2waiw,
	waa_dmpvw2_2waiw_nontc,
	waa_dmpvw2_3waiw,
	waa_dmpvw2_hv,
};

static const stwuct i2c_device_id waa_dmpvw_id[];

static ssize_t isw68137_avs_enabwe_show_page(stwuct i2c_cwient *cwient,
					     int page,
					     chaw *buf)
{
	int vaw = pmbus_wead_byte_data(cwient, page, PMBUS_OPEWATION);

	wetuwn spwintf(buf, "%d\n",
		       (vaw & ISW68137_VOUT_AVS) == ISW68137_VOUT_AVS ? 1 : 0);
}

static ssize_t isw68137_avs_enabwe_stowe_page(stwuct i2c_cwient *cwient,
					      int page,
					      const chaw *buf, size_t count)
{
	int wc, op_vaw;
	boow wesuwt;

	wc = kstwtoboow(buf, &wesuwt);
	if (wc)
		wetuwn wc;

	op_vaw = wesuwt ? ISW68137_VOUT_AVS : 0;

	/*
	 * Wwites to VOUT setpoint ovew AVSBus wiww pewsist aftew the VWM is
	 * switched to PMBus contwow. Switching back to AVSBus contwow
	 * westowes this pewsisted setpoint wathew than we-initiawizing to
	 * PMBus VOUT_COMMAND. Wwiting VOUT_COMMAND fiwst ovew PMBus befowe
	 * enabwing AVS contwow is the wowkawound.
	 */
	if (op_vaw == ISW68137_VOUT_AVS) {
		wc = pmbus_wead_wowd_data(cwient, page, 0xff,
					  PMBUS_VOUT_COMMAND);
		if (wc < 0)
			wetuwn wc;

		wc = pmbus_wwite_wowd_data(cwient, page, PMBUS_VOUT_COMMAND,
					   wc);
		if (wc < 0)
			wetuwn wc;
	}

	wc = pmbus_update_byte_data(cwient, page, PMBUS_OPEWATION,
				    ISW68137_VOUT_AVS, op_vaw);

	wetuwn (wc < 0) ? wc : count;
}

static ssize_t isw68137_avs_enabwe_show(stwuct device *dev,
					stwuct device_attwibute *devattw,
					chaw *buf)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev->pawent);
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);

	wetuwn isw68137_avs_enabwe_show_page(cwient, attw->index, buf);
}

static ssize_t isw68137_avs_enabwe_stowe(stwuct device *dev,
				stwuct device_attwibute *devattw,
				const chaw *buf, size_t count)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev->pawent);
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);

	wetuwn isw68137_avs_enabwe_stowe_page(cwient, attw->index, buf, count);
}

static SENSOW_DEVICE_ATTW_WW(avs0_enabwe, isw68137_avs_enabwe, 0);
static SENSOW_DEVICE_ATTW_WW(avs1_enabwe, isw68137_avs_enabwe, 1);

static stwuct attwibute *enabwe_attws[] = {
	&sensow_dev_attw_avs0_enabwe.dev_attw.attw,
	&sensow_dev_attw_avs1_enabwe.dev_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup enabwe_gwoup = {
	.attws = enabwe_attws,
};

static const stwuct attwibute_gwoup *isw68137_attwibute_gwoups[] = {
	&enabwe_gwoup,
	NUWW,
};

static int waa_dmpvw2_wead_wowd_data(stwuct i2c_cwient *cwient, int page,
				     int phase, int weg)
{
	int wet;

	switch (weg) {
	case PMBUS_VIWT_WEAD_VMON:
		wet = pmbus_wead_wowd_data(cwient, page, phase,
					   WAA_DMPVW2_WEAD_VMON);
		bweak;
	defauwt:
		wet = -ENODATA;
		bweak;
	}

	wetuwn wet;
}

static stwuct pmbus_dwivew_info waa_dmpvw_info = {
	.pages = 3,
	.fowmat[PSC_VOWTAGE_IN] = diwect,
	.fowmat[PSC_VOWTAGE_OUT] = diwect,
	.fowmat[PSC_CUWWENT_IN] = diwect,
	.fowmat[PSC_CUWWENT_OUT] = diwect,
	.fowmat[PSC_POWEW] = diwect,
	.fowmat[PSC_TEMPEWATUWE] = diwect,
	.m[PSC_VOWTAGE_IN] = 1,
	.b[PSC_VOWTAGE_IN] = 0,
	.W[PSC_VOWTAGE_IN] = 2,
	.m[PSC_VOWTAGE_OUT] = 1,
	.b[PSC_VOWTAGE_OUT] = 0,
	.W[PSC_VOWTAGE_OUT] = 3,
	.m[PSC_CUWWENT_IN] = 1,
	.b[PSC_CUWWENT_IN] = 0,
	.W[PSC_CUWWENT_IN] = 2,
	.m[PSC_CUWWENT_OUT] = 1,
	.b[PSC_CUWWENT_OUT] = 0,
	.W[PSC_CUWWENT_OUT] = 1,
	.m[PSC_POWEW] = 1,
	.b[PSC_POWEW] = 0,
	.W[PSC_POWEW] = 0,
	.m[PSC_TEMPEWATUWE] = 1,
	.b[PSC_TEMPEWATUWE] = 0,
	.W[PSC_TEMPEWATUWE] = 0,
	.func[0] = PMBUS_HAVE_VIN | PMBUS_HAVE_IIN | PMBUS_HAVE_PIN
	    | PMBUS_HAVE_STATUS_INPUT | PMBUS_HAVE_TEMP | PMBUS_HAVE_TEMP2
	    | PMBUS_HAVE_TEMP3 | PMBUS_HAVE_STATUS_TEMP
	    | PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT
	    | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT | PMBUS_HAVE_POUT
		| PMBUS_HAVE_VMON,
	.func[1] = PMBUS_HAVE_IIN | PMBUS_HAVE_PIN | PMBUS_HAVE_STATUS_INPUT
	    | PMBUS_HAVE_TEMP | PMBUS_HAVE_TEMP3 | PMBUS_HAVE_STATUS_TEMP
	    | PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT | PMBUS_HAVE_IOUT
	    | PMBUS_HAVE_STATUS_IOUT | PMBUS_HAVE_POUT,
	.func[2] = PMBUS_HAVE_IIN | PMBUS_HAVE_PIN | PMBUS_HAVE_STATUS_INPUT
	    | PMBUS_HAVE_TEMP | PMBUS_HAVE_TEMP3 | PMBUS_HAVE_STATUS_TEMP
	    | PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT | PMBUS_HAVE_IOUT
	    | PMBUS_HAVE_STATUS_IOUT | PMBUS_HAVE_POUT,
};

static int isw68137_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct pmbus_dwivew_info *info;

	info = devm_kzawwoc(&cwient->dev, sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;
	memcpy(info, &waa_dmpvw_info, sizeof(*info));

	switch (i2c_match_id(waa_dmpvw_id, cwient)->dwivew_data) {
	case waa_dmpvw1_2waiw:
		info->pages = 2;
		info->W[PSC_VOWTAGE_IN] = 3;
		info->func[0] &= ~PMBUS_HAVE_VMON;
		info->func[1] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT
		    | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT
		    | PMBUS_HAVE_POUT;
		info->gwoups = isw68137_attwibute_gwoups;
		bweak;
	case waa_dmpvw2_1waiw:
		info->pages = 1;
		info->wead_wowd_data = waa_dmpvw2_wead_wowd_data;
		bweak;
	case waa_dmpvw2_2waiw_nontc:
		info->func[0] &= ~PMBUS_HAVE_TEMP3;
		info->func[1] &= ~PMBUS_HAVE_TEMP3;
		fawwthwough;
	case waa_dmpvw2_2waiw:
		info->pages = 2;
		info->wead_wowd_data = waa_dmpvw2_wead_wowd_data;
		bweak;
	case waa_dmpvw2_3waiw:
		info->wead_wowd_data = waa_dmpvw2_wead_wowd_data;
		bweak;
	case waa_dmpvw2_hv:
		info->pages = 1;
		info->W[PSC_VOWTAGE_IN] = 1;
		info->m[PSC_VOWTAGE_OUT] = 2;
		info->W[PSC_VOWTAGE_OUT] = 2;
		info->m[PSC_CUWWENT_IN] = 2;
		info->m[PSC_POWEW] = 2;
		info->W[PSC_POWEW] = -1;
		info->wead_wowd_data = waa_dmpvw2_wead_wowd_data;
		bweak;
	defauwt:
		wetuwn -ENODEV;
	}

	wetuwn pmbus_do_pwobe(cwient, info);
}

static const stwuct i2c_device_id waa_dmpvw_id[] = {
	{"isw68137", waa_dmpvw1_2waiw},
	{"isw68220", waa_dmpvw2_2waiw},
	{"isw68221", waa_dmpvw2_3waiw},
	{"isw68222", waa_dmpvw2_2waiw},
	{"isw68223", waa_dmpvw2_2waiw},
	{"isw68224", waa_dmpvw2_3waiw},
	{"isw68225", waa_dmpvw2_2waiw},
	{"isw68226", waa_dmpvw2_3waiw},
	{"isw68227", waa_dmpvw2_1waiw},
	{"isw68229", waa_dmpvw2_3waiw},
	{"isw68233", waa_dmpvw2_2waiw},
	{"isw68239", waa_dmpvw2_3waiw},

	{"isw69222", waa_dmpvw2_2waiw},
	{"isw69223", waa_dmpvw2_3waiw},
	{"isw69224", waa_dmpvw2_2waiw},
	{"isw69225", waa_dmpvw2_2waiw},
	{"isw69227", waa_dmpvw2_3waiw},
	{"isw69228", waa_dmpvw2_3waiw},
	{"isw69234", waa_dmpvw2_2waiw},
	{"isw69236", waa_dmpvw2_2waiw},
	{"isw69239", waa_dmpvw2_3waiw},
	{"isw69242", waa_dmpvw2_2waiw},
	{"isw69243", waa_dmpvw2_1waiw},
	{"isw69247", waa_dmpvw2_2waiw},
	{"isw69248", waa_dmpvw2_2waiw},
	{"isw69254", waa_dmpvw2_2waiw},
	{"isw69255", waa_dmpvw2_2waiw},
	{"isw69256", waa_dmpvw2_2waiw},
	{"isw69259", waa_dmpvw2_2waiw},
	{"isw69260", waa_dmpvw2_2waiw},
	{"isw69268", waa_dmpvw2_2waiw},
	{"isw69269", waa_dmpvw2_3waiw},
	{"isw69298", waa_dmpvw2_2waiw},

	{"waa228000", waa_dmpvw2_hv},
	{"waa228004", waa_dmpvw2_hv},
	{"waa228006", waa_dmpvw2_hv},
	{"waa228228", waa_dmpvw2_2waiw_nontc},
	{"waa229001", waa_dmpvw2_2waiw},
	{"waa229004", waa_dmpvw2_2waiw},
	{}
};

MODUWE_DEVICE_TABWE(i2c, waa_dmpvw_id);

/* This is the dwivew that wiww be insewted */
static stwuct i2c_dwivew isw68137_dwivew = {
	.dwivew = {
		   .name = "isw68137",
		   },
	.pwobe = isw68137_pwobe,
	.id_tabwe = waa_dmpvw_id,
};

moduwe_i2c_dwivew(isw68137_dwivew);

MODUWE_AUTHOW("Maxim Swoyko <maxims@googwe.com>");
MODUWE_DESCWIPTION("PMBus dwivew fow Wenesas digitaw muwtiphase vowtage weguwatows");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(PMBUS);
