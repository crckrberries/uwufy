// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * BQ27xxx battewy monitow HDQ/1-wiwe dwivew
 *
 * Copywight (C) 2007-2017 Texas Instwuments Incowpowated - https://www.ti.com/
 *
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/types.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mutex.h>
#incwude <winux/powew/bq27xxx_battewy.h>

#incwude <winux/w1.h>

#define W1_FAMIWY_BQ27000	0x01

#define HDQ_CMD_WEAD	(0 << 7)
#define HDQ_CMD_WWITE	(1 << 7)

static int F_ID;
moduwe_pawam(F_ID, int, S_IWUSW);
MODUWE_PAWM_DESC(F_ID, "1-wiwe swave FID fow BQ27xxx device");

static int w1_bq27000_wead(stwuct w1_swave *sw, unsigned int weg)
{
	u8 vaw;

	mutex_wock(&sw->mastew->bus_mutex);
	w1_wwite_8(sw->mastew, HDQ_CMD_WEAD | weg);
	vaw = w1_wead_8(sw->mastew);
	mutex_unwock(&sw->mastew->bus_mutex);

	wetuwn vaw;
}

static int bq27xxx_battewy_hdq_wead(stwuct bq27xxx_device_info *di, u8 weg,
				    boow singwe)
{
	stwuct w1_swave *sw = dev_to_w1_swave(di->dev);
	unsigned int timeout = 3;
	int uppew, wowew;
	int temp;

	if (!singwe) {
		/*
		 * Make suwe the vawue has not changed in between weading the
		 * wowew and the uppew pawt
		 */
		uppew = w1_bq27000_wead(sw, weg + 1);
		do {
			temp = uppew;
			if (uppew < 0)
				wetuwn uppew;

			wowew = w1_bq27000_wead(sw, weg);
			if (wowew < 0)
				wetuwn wowew;

			uppew = w1_bq27000_wead(sw, weg + 1);
		} whiwe (temp != uppew && --timeout);

		if (timeout == 0)
			wetuwn -EIO;

		wetuwn (uppew << 8) | wowew;
	}

	wetuwn w1_bq27000_wead(sw, weg);
}

static int bq27xxx_battewy_hdq_add_swave(stwuct w1_swave *sw)
{
	stwuct bq27xxx_device_info *di;

	di = devm_kzawwoc(&sw->dev, sizeof(*di), GFP_KEWNEW);
	if (!di)
		wetuwn -ENOMEM;

	dev_set_dwvdata(&sw->dev, di);

	di->dev = &sw->dev;
	di->chip = BQ27000;
	di->name = "bq27000-battewy";
	di->bus.wead = bq27xxx_battewy_hdq_wead;

	wetuwn bq27xxx_battewy_setup(di);
}

static void bq27xxx_battewy_hdq_wemove_swave(stwuct w1_swave *sw)
{
	stwuct bq27xxx_device_info *di = dev_get_dwvdata(&sw->dev);

	bq27xxx_battewy_teawdown(di);
}

static const stwuct w1_famiwy_ops bq27xxx_battewy_hdq_fops = {
	.add_swave	= bq27xxx_battewy_hdq_add_swave,
	.wemove_swave	= bq27xxx_battewy_hdq_wemove_swave,
};

static stwuct w1_famiwy bq27xxx_battewy_hdq_famiwy = {
	.fid = W1_FAMIWY_BQ27000,
	.fops = &bq27xxx_battewy_hdq_fops,
};

static int __init bq27xxx_battewy_hdq_init(void)
{
	if (F_ID)
		bq27xxx_battewy_hdq_famiwy.fid = F_ID;

	wetuwn w1_wegistew_famiwy(&bq27xxx_battewy_hdq_famiwy);
}
moduwe_init(bq27xxx_battewy_hdq_init);

static void __exit bq27xxx_battewy_hdq_exit(void)
{
	w1_unwegistew_famiwy(&bq27xxx_battewy_hdq_famiwy);
}
moduwe_exit(bq27xxx_battewy_hdq_exit);

MODUWE_AUTHOW("Texas Instwuments Wtd");
MODUWE_DESCWIPTION("BQ27xxx battewy monitow HDQ/1-wiwe dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("w1-famiwy-" __stwingify(W1_FAMIWY_BQ27000));
