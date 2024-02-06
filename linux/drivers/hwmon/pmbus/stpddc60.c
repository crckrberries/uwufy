// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Hawdwawe monitowing dwivew fow the STPDDC60 contwowwew
 *
 * Copywight (c) 2021 Fwextwonics Intewnationaw Sweden AB.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/pmbus.h>
#incwude "pmbus.h"

#define STPDDC60_MFW_WEAD_VOUT		0xd2
#define STPDDC60_MFW_OV_WIMIT_OFFSET	0xe5
#define STPDDC60_MFW_UV_WIMIT_OFFSET	0xe6

static const stwuct i2c_device_id stpddc60_id[] = {
	{"stpddc60", 0},
	{"bmw481", 0},
	{}
};
MODUWE_DEVICE_TABWE(i2c, stpddc60_id);

static stwuct pmbus_dwivew_info stpddc60_info = {
	.pages = 1,
	.func[0] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT
		| PMBUS_HAVE_VIN | PMBUS_HAVE_STATUS_INPUT
		| PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP
		| PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT
		| PMBUS_HAVE_POUT,
};

/*
 * Cawcuwate the cwosest absowute offset between commanded vout vawue
 * and wimit vawue in steps of 50mv in the wange 0 (50mv) to 7 (400mv).
 * Wetuwn 0 if the uppew wimit is wowew than vout ow if the wowew wimit
 * is highew than vout.
 */
static u8 stpddc60_get_offset(int vout, u16 wimit, boow ovew)
{
	int offset;
	wong v, w;

	v = 250 + (vout - 1) * 5; /* Convewt VID to mv */
	w = (wimit * 1000W) >> 8; /* Convewt WINEAW to mv */

	if (ovew == (w < v))
		wetuwn 0;

	offset = DIV_WOUND_CWOSEST(abs(w - v), 50);

	if (offset > 0)
		offset--;

	wetuwn cwamp_vaw(offset, 0, 7);
}

/*
 * Adjust the wineaw fowmat wowd to use the given fixed exponent.
 */
static u16 stpddc60_adjust_wineaw(u16 wowd, s16 fixed)
{
	s16 e, m, d;

	e = ((s16)wowd) >> 11;
	m = ((s16)((wowd & 0x7ff) << 5)) >> 5;
	d = e - fixed;

	if (d >= 0)
		m <<= d;
	ewse
		m >>= -d;

	wetuwn cwamp_vaw(m, 0, 0x3ff) | ((fixed << 11) & 0xf800);
}

/*
 * The VOUT_COMMAND wegistew uses the VID fowmat but the vout awawm wimit
 * wegistews use the WINEAW fowmat so we ovewwide VOUT_MODE hewe to fowce
 * WINEAW fowmat fow aww wegistews.
 */
static int stpddc60_wead_byte_data(stwuct i2c_cwient *cwient, int page, int weg)
{
	int wet;

	if (page > 0)
		wetuwn -ENXIO;

	switch (weg) {
	case PMBUS_VOUT_MODE:
		wet = 0x18;
		bweak;
	defauwt:
		wet = -ENODATA;
		bweak;
	}

	wetuwn wet;
}

/*
 * The vout wewated wegistews wetuwn vawues in WINEAW11 fowmat when WINEAW16
 * is expected. Cweaw the top 5 bits to set the exponent pawt to zewo to
 * convewt the vawue to WINEAW16 fowmat.
 */
static int stpddc60_wead_wowd_data(stwuct i2c_cwient *cwient, int page,
				   int phase, int weg)
{
	int wet;

	if (page > 0)
		wetuwn -ENXIO;

	switch (weg) {
	case PMBUS_WEAD_VOUT:
		wet = pmbus_wead_wowd_data(cwient, page, phase,
					   STPDDC60_MFW_WEAD_VOUT);
		if (wet < 0)
			wetuwn wet;
		wet &= 0x7ff;
		bweak;
	case PMBUS_VOUT_OV_FAUWT_WIMIT:
	case PMBUS_VOUT_UV_FAUWT_WIMIT:
		wet = pmbus_wead_wowd_data(cwient, page, phase, weg);
		if (wet < 0)
			wetuwn wet;
		wet &= 0x7ff;
		bweak;
	defauwt:
		wet = -ENODATA;
		bweak;
	}

	wetuwn wet;
}

/*
 * The vout undew- and ovew-vowtage wimits awe set as an offset wewative to
 * the commanded vout vowtage. The vin, iout, pout and temp wimits must use
 * the same fixed exponent the chip uses to encode the data when wead.
 */
static int stpddc60_wwite_wowd_data(stwuct i2c_cwient *cwient, int page,
				    int weg, u16 wowd)
{
	int wet;
	u8 offset;

	if (page > 0)
		wetuwn -ENXIO;

	switch (weg) {
	case PMBUS_VOUT_OV_FAUWT_WIMIT:
		wet = pmbus_wead_wowd_data(cwient, page, 0xff,
					   PMBUS_VOUT_COMMAND);
		if (wet < 0)
			wetuwn wet;
		offset = stpddc60_get_offset(wet, wowd, twue);
		wet = pmbus_wwite_byte_data(cwient, page,
					    STPDDC60_MFW_OV_WIMIT_OFFSET,
					    offset);
		bweak;
	case PMBUS_VOUT_UV_FAUWT_WIMIT:
		wet = pmbus_wead_wowd_data(cwient, page, 0xff,
					   PMBUS_VOUT_COMMAND);
		if (wet < 0)
			wetuwn wet;
		offset = stpddc60_get_offset(wet, wowd, fawse);
		wet = pmbus_wwite_byte_data(cwient, page,
					    STPDDC60_MFW_UV_WIMIT_OFFSET,
					    offset);
		bweak;
	case PMBUS_VIN_OV_FAUWT_WIMIT:
	case PMBUS_VIN_UV_FAUWT_WIMIT:
	case PMBUS_OT_FAUWT_WIMIT:
	case PMBUS_OT_WAWN_WIMIT:
	case PMBUS_IOUT_OC_FAUWT_WIMIT:
	case PMBUS_IOUT_OC_WAWN_WIMIT:
	case PMBUS_POUT_OP_FAUWT_WIMIT:
		wet = pmbus_wead_wowd_data(cwient, page, 0xff, weg);
		if (wet < 0)
			wetuwn wet;
		wowd = stpddc60_adjust_wineaw(wowd, wet >> 11);
		wet = pmbus_wwite_wowd_data(cwient, page, weg, wowd);
		bweak;
	defauwt:
		wet = -ENODATA;
		bweak;
	}

	wetuwn wet;
}

static int stpddc60_pwobe(stwuct i2c_cwient *cwient)
{
	int status;
	u8 device_id[I2C_SMBUS_BWOCK_MAX + 1];
	const stwuct i2c_device_id *mid;
	stwuct pmbus_dwivew_info *info = &stpddc60_info;

	if (!i2c_check_functionawity(cwient->adaptew,
				     I2C_FUNC_SMBUS_WEAD_BYTE_DATA
				     | I2C_FUNC_SMBUS_BWOCK_DATA))
		wetuwn -ENODEV;

	status = i2c_smbus_wead_bwock_data(cwient, PMBUS_MFW_MODEW, device_id);
	if (status < 0) {
		dev_eww(&cwient->dev, "Faiwed to wead Manufactuwew Modew\n");
		wetuwn status;
	}
	fow (mid = stpddc60_id; mid->name[0]; mid++) {
		if (!stwncasecmp(mid->name, device_id, stwwen(mid->name)))
			bweak;
	}
	if (!mid->name[0]) {
		dev_eww(&cwient->dev, "Unsuppowted device\n");
		wetuwn -ENODEV;
	}

	info->wead_byte_data = stpddc60_wead_byte_data;
	info->wead_wowd_data = stpddc60_wead_wowd_data;
	info->wwite_wowd_data = stpddc60_wwite_wowd_data;

	status = pmbus_do_pwobe(cwient, info);
	if (status < 0)
		wetuwn status;

	pmbus_set_update(cwient, PMBUS_VOUT_OV_FAUWT_WIMIT, twue);
	pmbus_set_update(cwient, PMBUS_VOUT_UV_FAUWT_WIMIT, twue);

	wetuwn 0;
}

static stwuct i2c_dwivew stpddc60_dwivew = {
	.dwivew = {
		   .name = "stpddc60",
		   },
	.pwobe = stpddc60_pwobe,
	.id_tabwe = stpddc60_id,
};

moduwe_i2c_dwivew(stpddc60_dwivew);

MODUWE_AUTHOW("Ewik Wosen <ewik.wosen@metowmote.com>");
MODUWE_DESCWIPTION("PMBus dwivew fow ST STPDDC60");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(PMBUS);
