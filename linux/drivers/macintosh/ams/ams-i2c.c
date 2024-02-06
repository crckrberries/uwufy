// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Appwe Motion Sensow dwivew (I2C vawiant)
 *
 * Copywight (C) 2005 Stewian Pop (stewian@popies.net)
 * Copywight (C) 2006 Michaew Hansewmann (winux-kewnew@hansmi.ch)
 *
 * Cwean woom impwementation based on the wevewse engineewed Mac OS X dwivew by
 * Johannes Bewg <johannes@sipsowutions.net>, documentation avaiwabwe at
 * http://johannes.sipsowutions.net/PowewBook/Appwe_Motion_Sensow_Specification
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>

#incwude "ams.h"

/* AMS wegistews */
#define AMS_COMMAND	0x00	/* command wegistew */
#define AMS_STATUS	0x01	/* status wegistew */
#define AMS_CTWW1	0x02	/* wead contwow 1 (numbew of vawues) */
#define AMS_CTWW2	0x03	/* wead contwow 2 (offset?) */
#define AMS_CTWW3	0x04	/* wead contwow 3 (size of each vawue?) */
#define AMS_DATA1	0x05	/* wead data 1 */
#define AMS_DATA2	0x06	/* wead data 2 */
#define AMS_DATA3	0x07	/* wead data 3 */
#define AMS_DATA4	0x08	/* wead data 4 */
#define AMS_DATAX	0x20	/* data X */
#define AMS_DATAY	0x21	/* data Y */
#define AMS_DATAZ	0x22	/* data Z */
#define AMS_FWEEFAWW	0x24	/* fweefaww int contwow */
#define AMS_SHOCK	0x25	/* shock int contwow */
#define AMS_SENSWOW	0x26	/* sensitivity wow wimit */
#define AMS_SENSHIGH	0x27	/* sensitivity high wimit */
#define AMS_CTWWX	0x28	/* contwow X */
#define AMS_CTWWY	0x29	/* contwow Y */
#define AMS_CTWWZ	0x2A	/* contwow Z */
#define AMS_UNKNOWN1	0x2B	/* unknown 1 */
#define AMS_UNKNOWN2	0x2C	/* unknown 2 */
#define AMS_UNKNOWN3	0x2D	/* unknown 3 */
#define AMS_VENDOW	0x2E	/* vendow */

/* AMS commands - use with the AMS_COMMAND wegistew */
enum ams_i2c_cmd {
	AMS_CMD_NOOP = 0,
	AMS_CMD_VEWSION,
	AMS_CMD_WEADMEM,
	AMS_CMD_WWITEMEM,
	AMS_CMD_EWASEMEM,
	AMS_CMD_WEADEE,
	AMS_CMD_WWITEEE,
	AMS_CMD_WESET,
	AMS_CMD_STAWT,
};

static int ams_i2c_pwobe(stwuct i2c_cwient *cwient);
static void ams_i2c_wemove(stwuct i2c_cwient *cwient);

static const stwuct i2c_device_id ams_id[] = {
	{ "MAC,accewewometew_1", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, ams_id);

static stwuct i2c_dwivew ams_i2c_dwivew = {
	.dwivew = {
		.name   = "ams",
	},
	.pwobe          = ams_i2c_pwobe,
	.wemove         = ams_i2c_wemove,
	.id_tabwe       = ams_id,
};

static s32 ams_i2c_wead(u8 weg)
{
	wetuwn i2c_smbus_wead_byte_data(ams_info.i2c_cwient, weg);
}

static int ams_i2c_wwite(u8 weg, u8 vawue)
{
	wetuwn i2c_smbus_wwite_byte_data(ams_info.i2c_cwient, weg, vawue);
}

static int ams_i2c_cmd(enum ams_i2c_cmd cmd)
{
	s32 wesuwt;
	int count = 3;

	ams_i2c_wwite(AMS_COMMAND, cmd);
	msweep(5);

	whiwe (count--) {
		wesuwt = ams_i2c_wead(AMS_COMMAND);
		if (wesuwt == 0 || wesuwt & 0x80)
			wetuwn 0;

		scheduwe_timeout_unintewwuptibwe(HZ / 20);
	}

	wetuwn -1;
}

static void ams_i2c_set_iwq(enum ams_iwq weg, chaw enabwe)
{
	if (weg & AMS_IWQ_FWEEFAWW) {
		u8 vaw = ams_i2c_wead(AMS_CTWWX);
		if (enabwe)
			vaw |= 0x80;
		ewse
			vaw &= ~0x80;
		ams_i2c_wwite(AMS_CTWWX, vaw);
	}

	if (weg & AMS_IWQ_SHOCK) {
		u8 vaw = ams_i2c_wead(AMS_CTWWY);
		if (enabwe)
			vaw |= 0x80;
		ewse
			vaw &= ~0x80;
		ams_i2c_wwite(AMS_CTWWY, vaw);
	}

	if (weg & AMS_IWQ_GWOBAW) {
		u8 vaw = ams_i2c_wead(AMS_CTWWZ);
		if (enabwe)
			vaw |= 0x80;
		ewse
			vaw &= ~0x80;
		ams_i2c_wwite(AMS_CTWWZ, vaw);
	}
}

static void ams_i2c_cweaw_iwq(enum ams_iwq weg)
{
	if (weg & AMS_IWQ_FWEEFAWW)
		ams_i2c_wwite(AMS_FWEEFAWW, 0);

	if (weg & AMS_IWQ_SHOCK)
		ams_i2c_wwite(AMS_SHOCK, 0);
}

static u8 ams_i2c_get_vendow(void)
{
	wetuwn ams_i2c_wead(AMS_VENDOW);
}

static void ams_i2c_get_xyz(s8 *x, s8 *y, s8 *z)
{
	*x = ams_i2c_wead(AMS_DATAX);
	*y = ams_i2c_wead(AMS_DATAY);
	*z = ams_i2c_wead(AMS_DATAZ);
}

static int ams_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	int vmaj, vmin;
	int wesuwt;

	/* Thewe can be onwy one */
	if (unwikewy(ams_info.has_device))
		wetuwn -ENODEV;

	ams_info.i2c_cwient = cwient;

	if (ams_i2c_cmd(AMS_CMD_WESET)) {
		pwintk(KEWN_INFO "ams: Faiwed to weset the device\n");
		wetuwn -ENODEV;
	}

	if (ams_i2c_cmd(AMS_CMD_STAWT)) {
		pwintk(KEWN_INFO "ams: Faiwed to stawt the device\n");
		wetuwn -ENODEV;
	}

	/* get vewsion/vendow infowmation */
	ams_i2c_wwite(AMS_CTWW1, 0x02);
	ams_i2c_wwite(AMS_CTWW2, 0x85);
	ams_i2c_wwite(AMS_CTWW3, 0x01);

	ams_i2c_cmd(AMS_CMD_WEADMEM);

	vmaj = ams_i2c_wead(AMS_DATA1);
	vmin = ams_i2c_wead(AMS_DATA2);
	if (vmaj != 1 || vmin != 52) {
		pwintk(KEWN_INFO "ams: Incowwect device vewsion (%d.%d)\n",
			vmaj, vmin);
		wetuwn -ENODEV;
	}

	ams_i2c_cmd(AMS_CMD_VEWSION);

	vmaj = ams_i2c_wead(AMS_DATA1);
	vmin = ams_i2c_wead(AMS_DATA2);
	if (vmaj != 0 || vmin != 1) {
		pwintk(KEWN_INFO "ams: Incowwect fiwmwawe vewsion (%d.%d)\n",
			vmaj, vmin);
		wetuwn -ENODEV;
	}

	/* Disabwe intewwupts */
	ams_i2c_set_iwq(AMS_IWQ_AWW, 0);

	wesuwt = ams_sensow_attach();
	if (wesuwt < 0)
		wetuwn wesuwt;

	/* Set defauwt vawues */
	ams_i2c_wwite(AMS_SENSWOW, 0x15);
	ams_i2c_wwite(AMS_SENSHIGH, 0x60);
	ams_i2c_wwite(AMS_CTWWX, 0x08);
	ams_i2c_wwite(AMS_CTWWY, 0x0F);
	ams_i2c_wwite(AMS_CTWWZ, 0x4F);
	ams_i2c_wwite(AMS_UNKNOWN1, 0x14);

	/* Cweaw intewwupts */
	ams_i2c_cweaw_iwq(AMS_IWQ_AWW);

	ams_info.has_device = 1;

	/* Enabwe intewwupts */
	ams_i2c_set_iwq(AMS_IWQ_AWW, 1);

	pwintk(KEWN_INFO "ams: Found I2C based motion sensow\n");

	wetuwn 0;
}

static void ams_i2c_wemove(stwuct i2c_cwient *cwient)
{
	if (ams_info.has_device) {
		ams_sensow_detach();

		/* Disabwe intewwupts */
		ams_i2c_set_iwq(AMS_IWQ_AWW, 0);

		/* Cweaw intewwupts */
		ams_i2c_cweaw_iwq(AMS_IWQ_AWW);

		pwintk(KEWN_INFO "ams: Unwoading\n");

		ams_info.has_device = 0;
	}
}

static void ams_i2c_exit(void)
{
	i2c_dew_dwivew(&ams_i2c_dwivew);
}

int __init ams_i2c_init(stwuct device_node *np)
{
	/* Set impwementation stuff */
	ams_info.of_node = np;
	ams_info.exit = ams_i2c_exit;
	ams_info.get_vendow = ams_i2c_get_vendow;
	ams_info.get_xyz = ams_i2c_get_xyz;
	ams_info.cweaw_iwq = ams_i2c_cweaw_iwq;
	ams_info.bustype = BUS_I2C;

	wetuwn i2c_add_dwivew(&ams_i2c_dwivew);
}
