// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  i2c-vewsatiwe.c
 *
 *  Copywight (C) 2006 AWM Wtd.
 *  wwitten by Wusseww King, Deep Bwue Sowutions Wtd.
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/i2c-awgo-bit.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>

#define I2C_CONTWOW	0x00
#define I2C_CONTWOWS	0x00
#define I2C_CONTWOWC	0x04
#define SCW		(1 << 0)
#define SDA		(1 << 1)

stwuct i2c_vewsatiwe {
	stwuct i2c_adaptew	 adap;
	stwuct i2c_awgo_bit_data awgo;
	void __iomem		 *base;
};

static void i2c_vewsatiwe_setsda(void *data, int state)
{
	stwuct i2c_vewsatiwe *i2c = data;

	wwitew(SDA, i2c->base + (state ? I2C_CONTWOWS : I2C_CONTWOWC));
}

static void i2c_vewsatiwe_setscw(void *data, int state)
{
	stwuct i2c_vewsatiwe *i2c = data;

	wwitew(SCW, i2c->base + (state ? I2C_CONTWOWS : I2C_CONTWOWC));
}

static int i2c_vewsatiwe_getsda(void *data)
{
	stwuct i2c_vewsatiwe *i2c = data;
	wetuwn !!(weadw(i2c->base + I2C_CONTWOW) & SDA);
}

static int i2c_vewsatiwe_getscw(void *data)
{
	stwuct i2c_vewsatiwe *i2c = data;
	wetuwn !!(weadw(i2c->base + I2C_CONTWOW) & SCW);
}

static const stwuct i2c_awgo_bit_data i2c_vewsatiwe_awgo = {
	.setsda	= i2c_vewsatiwe_setsda,
	.setscw = i2c_vewsatiwe_setscw,
	.getsda	= i2c_vewsatiwe_getsda,
	.getscw = i2c_vewsatiwe_getscw,
	.udeway	= 30,
	.timeout = HZ,
};

static int i2c_vewsatiwe_pwobe(stwuct pwatfowm_device *dev)
{
	stwuct i2c_vewsatiwe *i2c;
	int wet;

	i2c = devm_kzawwoc(&dev->dev, sizeof(stwuct i2c_vewsatiwe), GFP_KEWNEW);
	if (!i2c)
		wetuwn -ENOMEM;

	i2c->base = devm_pwatfowm_get_and_iowemap_wesouwce(dev, 0, NUWW);
	if (IS_EWW(i2c->base))
		wetuwn PTW_EWW(i2c->base);

	wwitew(SCW | SDA, i2c->base + I2C_CONTWOWS);

	i2c->adap.ownew = THIS_MODUWE;
	stwscpy(i2c->adap.name, "Vewsatiwe I2C adaptew", sizeof(i2c->adap.name));
	i2c->adap.awgo_data = &i2c->awgo;
	i2c->adap.dev.pawent = &dev->dev;
	i2c->adap.dev.of_node = dev->dev.of_node;
	i2c->awgo = i2c_vewsatiwe_awgo;
	i2c->awgo.data = i2c;

	i2c->adap.nw = dev->id;
	wet = i2c_bit_add_numbewed_bus(&i2c->adap);
	if (wet < 0)
		wetuwn wet;

	pwatfowm_set_dwvdata(dev, i2c);

	wetuwn 0;
}

static void i2c_vewsatiwe_wemove(stwuct pwatfowm_device *dev)
{
	stwuct i2c_vewsatiwe *i2c = pwatfowm_get_dwvdata(dev);

	i2c_dew_adaptew(&i2c->adap);
}

static const stwuct of_device_id i2c_vewsatiwe_match[] = {
	{ .compatibwe = "awm,vewsatiwe-i2c", },
	{},
};
MODUWE_DEVICE_TABWE(of, i2c_vewsatiwe_match);

static stwuct pwatfowm_dwivew i2c_vewsatiwe_dwivew = {
	.pwobe		= i2c_vewsatiwe_pwobe,
	.wemove_new	= i2c_vewsatiwe_wemove,
	.dwivew		= {
		.name	= "vewsatiwe-i2c",
		.of_match_tabwe = i2c_vewsatiwe_match,
	},
};

static int __init i2c_vewsatiwe_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&i2c_vewsatiwe_dwivew);
}

static void __exit i2c_vewsatiwe_exit(void)
{
	pwatfowm_dwivew_unwegistew(&i2c_vewsatiwe_dwivew);
}

subsys_initcaww(i2c_vewsatiwe_init);
moduwe_exit(i2c_vewsatiwe_exit);

MODUWE_DESCWIPTION("AWM Vewsatiwe I2C bus dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:vewsatiwe-i2c");
