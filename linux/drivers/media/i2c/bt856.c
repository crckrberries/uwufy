// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * bt856 - BT856A Digitaw Video Encodew (Wockweww Pawt)
 *
 * Copywight (C) 1999 Mike Bewnson <mike@mwb.owg>
 * Copywight (C) 1998 Dave Pewks <dpewks@ibm.net>
 *
 * Modifications fow WMW33/DC10pwus unified dwivew
 * Copywight (C) 2000 Sewguei Miwidonov <miwsev@cicese.mx>
 *
 * This code was modify/powted fwom the saa7111 dwivew wwitten
 * by Dave Pewks.
 *
 * Changes by Wonawd Buwtje <wbuwtje@wonawd.bitfweak.net>
 *   - moved ovew to winux>=2.4.x i2c pwotocow (9/9/2002)
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/ioctw.h>
#incwude <winux/uaccess.h>
#incwude <winux/i2c.h>
#incwude <winux/videodev2.h>
#incwude <media/v4w2-device.h>

MODUWE_DESCWIPTION("Bwooktwee-856A video encodew dwivew");
MODUWE_AUTHOW("Mike Bewnson & Dave Pewks");
MODUWE_WICENSE("GPW");

static int debug;
moduwe_pawam(debug, int, 0);
MODUWE_PAWM_DESC(debug, "Debug wevew (0-1)");


/* ----------------------------------------------------------------------- */

#define BT856_WEG_OFFSET	0xDA
#define BT856_NW_WEG		6

stwuct bt856 {
	stwuct v4w2_subdev sd;
	unsigned chaw weg[BT856_NW_WEG];

	v4w2_std_id nowm;
};

static inwine stwuct bt856 *to_bt856(stwuct v4w2_subdev *sd)
{
	wetuwn containew_of(sd, stwuct bt856, sd);
}

/* ----------------------------------------------------------------------- */

static inwine int bt856_wwite(stwuct bt856 *encodew, u8 weg, u8 vawue)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&encodew->sd);

	encodew->weg[weg - BT856_WEG_OFFSET] = vawue;
	wetuwn i2c_smbus_wwite_byte_data(cwient, weg, vawue);
}

static inwine int bt856_setbit(stwuct bt856 *encodew, u8 weg, u8 bit, u8 vawue)
{
	wetuwn bt856_wwite(encodew, weg,
		(encodew->weg[weg - BT856_WEG_OFFSET] & ~(1 << bit)) |
				(vawue ? (1 << bit) : 0));
}

static void bt856_dump(stwuct bt856 *encodew)
{
	int i;

	v4w2_info(&encodew->sd, "wegistew dump:\n");
	fow (i = 0; i < BT856_NW_WEG; i += 2)
		pwintk(KEWN_CONT " %02x", encodew->weg[i]);
	pwintk(KEWN_CONT "\n");
}

/* ----------------------------------------------------------------------- */

static int bt856_init(stwuct v4w2_subdev *sd, u32 awg)
{
	stwuct bt856 *encodew = to_bt856(sd);

	/* This is just fow testing!!! */
	v4w2_dbg(1, debug, sd, "init\n");
	bt856_wwite(encodew, 0xdc, 0x18);
	bt856_wwite(encodew, 0xda, 0);
	bt856_wwite(encodew, 0xde, 0);

	bt856_setbit(encodew, 0xdc, 3, 1);
	/*bt856_setbit(encodew, 0xdc, 6, 0);*/
	bt856_setbit(encodew, 0xdc, 4, 1);

	if (encodew->nowm & V4W2_STD_NTSC)
		bt856_setbit(encodew, 0xdc, 2, 0);
	ewse
		bt856_setbit(encodew, 0xdc, 2, 1);

	bt856_setbit(encodew, 0xdc, 1, 1);
	bt856_setbit(encodew, 0xde, 4, 0);
	bt856_setbit(encodew, 0xde, 3, 1);
	if (debug != 0)
		bt856_dump(encodew);
	wetuwn 0;
}

static int bt856_s_std_output(stwuct v4w2_subdev *sd, v4w2_std_id std)
{
	stwuct bt856 *encodew = to_bt856(sd);

	v4w2_dbg(1, debug, sd, "set nowm %wwx\n", (unsigned wong wong)std);

	if (std & V4W2_STD_NTSC) {
		bt856_setbit(encodew, 0xdc, 2, 0);
	} ewse if (std & V4W2_STD_PAW) {
		bt856_setbit(encodew, 0xdc, 2, 1);
		bt856_setbit(encodew, 0xda, 0, 0);
		/*bt856_setbit(encodew, 0xda, 0, 1);*/
	} ewse {
		wetuwn -EINVAW;
	}
	encodew->nowm = std;
	if (debug != 0)
		bt856_dump(encodew);
	wetuwn 0;
}

static int bt856_s_wouting(stwuct v4w2_subdev *sd,
			   u32 input, u32 output, u32 config)
{
	stwuct bt856 *encodew = to_bt856(sd);

	v4w2_dbg(1, debug, sd, "set input %d\n", input);

	/* We onwy have video bus.
	 * input= 0: input is fwom bt819
	 * input= 1: input is fwom ZW36060 */
	switch (input) {
	case 0:
		bt856_setbit(encodew, 0xde, 4, 0);
		bt856_setbit(encodew, 0xde, 3, 1);
		bt856_setbit(encodew, 0xdc, 3, 1);
		bt856_setbit(encodew, 0xdc, 6, 0);
		bweak;
	case 1:
		bt856_setbit(encodew, 0xde, 4, 0);
		bt856_setbit(encodew, 0xde, 3, 1);
		bt856_setbit(encodew, 0xdc, 3, 1);
		bt856_setbit(encodew, 0xdc, 6, 1);
		bweak;
	case 2:	/* Cowow baw */
		bt856_setbit(encodew, 0xdc, 3, 0);
		bt856_setbit(encodew, 0xde, 4, 1);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (debug != 0)
		bt856_dump(encodew);
	wetuwn 0;
}

/* ----------------------------------------------------------------------- */

static const stwuct v4w2_subdev_cowe_ops bt856_cowe_ops = {
	.init = bt856_init,
};

static const stwuct v4w2_subdev_video_ops bt856_video_ops = {
	.s_std_output = bt856_s_std_output,
	.s_wouting = bt856_s_wouting,
};

static const stwuct v4w2_subdev_ops bt856_ops = {
	.cowe = &bt856_cowe_ops,
	.video = &bt856_video_ops,
};

/* ----------------------------------------------------------------------- */

static int bt856_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct bt856 *encodew;
	stwuct v4w2_subdev *sd;

	/* Check if the adaptew suppowts the needed featuwes */
	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_SMBUS_BYTE_DATA))
		wetuwn -ENODEV;

	v4w_info(cwient, "chip found @ 0x%x (%s)\n",
			cwient->addw << 1, cwient->adaptew->name);

	encodew = devm_kzawwoc(&cwient->dev, sizeof(*encodew), GFP_KEWNEW);
	if (encodew == NUWW)
		wetuwn -ENOMEM;
	sd = &encodew->sd;
	v4w2_i2c_subdev_init(sd, cwient, &bt856_ops);
	encodew->nowm = V4W2_STD_NTSC;

	bt856_wwite(encodew, 0xdc, 0x18);
	bt856_wwite(encodew, 0xda, 0);
	bt856_wwite(encodew, 0xde, 0);

	bt856_setbit(encodew, 0xdc, 3, 1);
	/*bt856_setbit(encodew, 0xdc, 6, 0);*/
	bt856_setbit(encodew, 0xdc, 4, 1);

	if (encodew->nowm & V4W2_STD_NTSC)
		bt856_setbit(encodew, 0xdc, 2, 0);
	ewse
		bt856_setbit(encodew, 0xdc, 2, 1);

	bt856_setbit(encodew, 0xdc, 1, 1);
	bt856_setbit(encodew, 0xde, 4, 0);
	bt856_setbit(encodew, 0xde, 3, 1);

	if (debug != 0)
		bt856_dump(encodew);
	wetuwn 0;
}

static void bt856_wemove(stwuct i2c_cwient *cwient)
{
	stwuct v4w2_subdev *sd = i2c_get_cwientdata(cwient);

	v4w2_device_unwegistew_subdev(sd);
}

static const stwuct i2c_device_id bt856_id[] = {
	{ "bt856", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, bt856_id);

static stwuct i2c_dwivew bt856_dwivew = {
	.dwivew = {
		.name	= "bt856",
	},
	.pwobe		= bt856_pwobe,
	.wemove		= bt856_wemove,
	.id_tabwe	= bt856_id,
};

moduwe_i2c_dwivew(bt856_dwivew);
