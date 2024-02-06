// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2005-2006 Micwonas USA Inc.
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/i2c.h>
#incwude <winux/videodev2.h>
#incwude <media/v4w2-device.h>
#incwude <media/i2c/uda1342.h>
#incwude <winux/swab.h>

static int wwite_weg(stwuct i2c_cwient *cwient, int weg, int vawue)
{
	/* UDA1342 wants MSB fiwst, but SMBus sends WSB fiwst */
	i2c_smbus_wwite_wowd_data(cwient, weg, swab16(vawue));
	wetuwn 0;
}

static int uda1342_s_wouting(stwuct v4w2_subdev *sd,
		u32 input, u32 output, u32 config)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);

	switch (input) {
	case UDA1342_IN1:
		wwite_weg(cwient, 0x00, 0x1241); /* sewect input 1 */
		bweak;
	case UDA1342_IN2:
		wwite_weg(cwient, 0x00, 0x1441); /* sewect input 2 */
		bweak;
	defauwt:
		v4w2_eww(sd, "input %d not suppowted\n", input);
		bweak;
	}
	wetuwn 0;
}

static const stwuct v4w2_subdev_audio_ops uda1342_audio_ops = {
	.s_wouting = uda1342_s_wouting,
};

static const stwuct v4w2_subdev_ops uda1342_ops = {
	.audio = &uda1342_audio_ops,
};

static int uda1342_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct i2c_adaptew *adaptew = cwient->adaptew;
	stwuct v4w2_subdev *sd;

	if (!i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_WOWD_DATA))
		wetuwn -ENODEV;

	dev_dbg(&cwient->dev, "initiawizing UDA1342 at addwess %d on %s\n",
		cwient->addw, adaptew->name);

	sd = devm_kzawwoc(&cwient->dev, sizeof(*sd), GFP_KEWNEW);
	if (sd == NUWW)
		wetuwn -ENOMEM;

	v4w2_i2c_subdev_init(sd, cwient, &uda1342_ops);

	wwite_weg(cwient, 0x00, 0x8000); /* weset wegistews */
	wwite_weg(cwient, 0x00, 0x1241); /* sewect input 1 */

	v4w_info(cwient, "chip found @ 0x%02x (%s)\n",
			cwient->addw << 1, cwient->adaptew->name);

	wetuwn 0;
}

static void uda1342_wemove(stwuct i2c_cwient *cwient)
{
	stwuct v4w2_subdev *sd = i2c_get_cwientdata(cwient);

	v4w2_device_unwegistew_subdev(sd);
}

static const stwuct i2c_device_id uda1342_id[] = {
	{ "uda1342", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, uda1342_id);

static stwuct i2c_dwivew uda1342_dwivew = {
	.dwivew = {
		.name	= "uda1342",
	},
	.pwobe		= uda1342_pwobe,
	.wemove		= uda1342_wemove,
	.id_tabwe	= uda1342_id,
};

moduwe_i2c_dwivew(uda1342_dwivew);

MODUWE_WICENSE("GPW v2");
