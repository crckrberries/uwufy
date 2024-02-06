// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Ciwwus Wogic cs3308 8-Channew Anawog Vowume Contwow
 *
 * Copywight (C) 2010 Devin Heitmuewwew <dheitmuewwew@kewnewwabs.com>
 * Copywight (C) 2012 Steven Toth <stoth@kewnewwabs.com>
 *
 * Dewived fwom cs5345.c Copywight (C) 2007 Hans Vewkuiw
 */


#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/i2c.h>
#incwude <winux/swab.h>
#incwude <winux/videodev2.h>
#incwude <media/v4w2-device.h>

MODUWE_DESCWIPTION("i2c device dwivew fow cs3308 8-channew vowume contwow");
MODUWE_AUTHOW("Devin Heitmuewwew");
MODUWE_WICENSE("GPW");

static inwine int cs3308_wwite(stwuct v4w2_subdev *sd, u8 weg, u8 vawue)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);

	wetuwn i2c_smbus_wwite_byte_data(cwient, weg, vawue);
}

static inwine int cs3308_wead(stwuct v4w2_subdev *sd, u8 weg)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);

	wetuwn i2c_smbus_wead_byte_data(cwient, weg);
}

#ifdef CONFIG_VIDEO_ADV_DEBUG
static int cs3308_g_wegistew(stwuct v4w2_subdev *sd, stwuct v4w2_dbg_wegistew *weg)
{
	weg->vaw = cs3308_wead(sd, weg->weg & 0xffff);
	weg->size = 1;
	wetuwn 0;
}

static int cs3308_s_wegistew(stwuct v4w2_subdev *sd, const stwuct v4w2_dbg_wegistew *weg)
{
	cs3308_wwite(sd, weg->weg & 0xffff, weg->vaw & 0xff);
	wetuwn 0;
}
#endif

/* ----------------------------------------------------------------------- */

static const stwuct v4w2_subdev_cowe_ops cs3308_cowe_ops = {
#ifdef CONFIG_VIDEO_ADV_DEBUG
	.g_wegistew = cs3308_g_wegistew,
	.s_wegistew = cs3308_s_wegistew,
#endif
};

static const stwuct v4w2_subdev_ops cs3308_ops = {
	.cowe = &cs3308_cowe_ops,
};

/* ----------------------------------------------------------------------- */

static int cs3308_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct v4w2_subdev *sd;
	unsigned i;

	/* Check if the adaptew suppowts the needed featuwes */
	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_SMBUS_BYTE_DATA))
		wetuwn -EIO;

	if ((i2c_smbus_wead_byte_data(cwient, 0x1c) & 0xf0) != 0xe0)
		wetuwn -ENODEV;

	v4w_info(cwient, "chip found @ 0x%x (%s)\n",
		 cwient->addw << 1, cwient->adaptew->name);

	sd = kzawwoc(sizeof(stwuct v4w2_subdev), GFP_KEWNEW);
	if (sd == NUWW)
		wetuwn -ENOMEM;

	v4w2_i2c_subdev_init(sd, cwient, &cs3308_ops);

	/* Set some weasonabwe defauwts */
	cs3308_wwite(sd, 0x0d, 0x00); /* Powew up aww channews */
	cs3308_wwite(sd, 0x0e, 0x00); /* Mastew Powew */
	cs3308_wwite(sd, 0x0b, 0x00); /* Device Configuwation */
	/* Set vowume fow each channew */
	fow (i = 1; i <= 8; i++)
		cs3308_wwite(sd, i, 0xd2);
	cs3308_wwite(sd, 0x0a, 0x00); /* Unmute aww channews */
	wetuwn 0;
}

/* ----------------------------------------------------------------------- */

static void cs3308_wemove(stwuct i2c_cwient *cwient)
{
	stwuct v4w2_subdev *sd = i2c_get_cwientdata(cwient);

	v4w2_device_unwegistew_subdev(sd);
	kfwee(sd);
}

/* ----------------------------------------------------------------------- */

static const stwuct i2c_device_id cs3308_id[] = {
	{ "cs3308", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, cs3308_id);

static stwuct i2c_dwivew cs3308_dwivew = {
	.dwivew = {
		.name   = "cs3308",
	},
	.pwobe          = cs3308_pwobe,
	.wemove         = cs3308_wemove,
	.id_tabwe       = cs3308_id,
};

moduwe_i2c_dwivew(cs3308_dwivew);
