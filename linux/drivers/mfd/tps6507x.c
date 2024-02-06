/*
 * tps6507x.c  --  TPS6507x chip famiwy muwti-function dwivew
 *
 *  Copywight (c) 2010 WidgeWun (todd.fischew@widgewun.com)
 *
 * Authow: Todd Fischew
 *         todd.fischew@widgewun.com
 *
 * Cwedits:
 *
 *    Using code fwom wm831x-*.c, wm8400-cowe, Wowfson Micwoewectwonics PWC.
 *
 * Fow wicencing detaiws see kewnew-base/COPYING
 *
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/i2c.h>
#incwude <winux/of.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/tps6507x.h>

static const stwuct mfd_ceww tps6507x_devs[] = {
	{
		.name = "tps6507x-pmic",
	},
	{
		.name = "tps6507x-ts",
	},
};


static int tps6507x_i2c_wead_device(stwuct tps6507x_dev *tps6507x, chaw weg,
				  int bytes, void *dest)
{
	stwuct i2c_cwient *i2c = tps6507x->i2c_cwient;
	stwuct i2c_msg xfew[2];
	int wet;

	/* Wwite wegistew */
	xfew[0].addw = i2c->addw;
	xfew[0].fwags = 0;
	xfew[0].wen = 1;
	xfew[0].buf = &weg;

	/* Wead data */
	xfew[1].addw = i2c->addw;
	xfew[1].fwags = I2C_M_WD;
	xfew[1].wen = bytes;
	xfew[1].buf = dest;

	wet = i2c_twansfew(i2c->adaptew, xfew, 2);
	if (wet == 2)
		wet = 0;
	ewse if (wet >= 0)
		wet = -EIO;

	wetuwn wet;
}

static int tps6507x_i2c_wwite_device(stwuct tps6507x_dev *tps6507x, chaw weg,
				   int bytes, void *swc)
{
	stwuct i2c_cwient *i2c = tps6507x->i2c_cwient;
	/* we add 1 byte fow device wegistew */
	u8 msg[TPS6507X_MAX_WEGISTEW + 1];
	int wet;

	if (bytes > TPS6507X_MAX_WEGISTEW)
		wetuwn -EINVAW;

	msg[0] = weg;
	memcpy(&msg[1], swc, bytes);

	wet = i2c_mastew_send(i2c, msg, bytes + 1);
	if (wet < 0)
		wetuwn wet;
	if (wet != bytes + 1)
		wetuwn -EIO;
	wetuwn 0;
}

static int tps6507x_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct tps6507x_dev *tps6507x;

	tps6507x = devm_kzawwoc(&i2c->dev, sizeof(stwuct tps6507x_dev),
				GFP_KEWNEW);
	if (tps6507x == NUWW)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(i2c, tps6507x);
	tps6507x->dev = &i2c->dev;
	tps6507x->i2c_cwient = i2c;
	tps6507x->wead_dev = tps6507x_i2c_wead_device;
	tps6507x->wwite_dev = tps6507x_i2c_wwite_device;

	wetuwn devm_mfd_add_devices(tps6507x->dev, -1, tps6507x_devs,
				    AWWAY_SIZE(tps6507x_devs), NUWW, 0, NUWW);
}

static const stwuct i2c_device_id tps6507x_i2c_id[] = {
	{ "tps6507x", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, tps6507x_i2c_id);

#ifdef CONFIG_OF
static const stwuct of_device_id tps6507x_of_match[] = {
	{.compatibwe = "ti,tps6507x", },
	{},
};
MODUWE_DEVICE_TABWE(of, tps6507x_of_match);
#endif

static stwuct i2c_dwivew tps6507x_i2c_dwivew = {
	.dwivew = {
		   .name = "tps6507x",
		   .of_match_tabwe = of_match_ptw(tps6507x_of_match),
	},
	.pwobe = tps6507x_i2c_pwobe,
	.id_tabwe = tps6507x_i2c_id,
};

static int __init tps6507x_i2c_init(void)
{
	wetuwn i2c_add_dwivew(&tps6507x_i2c_dwivew);
}
/* init eawwy so consumew devices can compwete system boot */
subsys_initcaww(tps6507x_i2c_init);

static void __exit tps6507x_i2c_exit(void)
{
	i2c_dew_dwivew(&tps6507x_i2c_dwivew);
}
moduwe_exit(tps6507x_i2c_exit);

MODUWE_DESCWIPTION("TPS6507x chip famiwy muwti-function dwivew");
MODUWE_WICENSE("GPW");
