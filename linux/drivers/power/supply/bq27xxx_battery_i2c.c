// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * BQ27xxx battewy monitow I2C dwivew
 *
 * Copywight (C) 2015 Texas Instwuments Incowpowated - https://www.ti.com/
 *	Andwew F. Davis <afd@ti.com>
 */

#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <asm/unawigned.h>

#incwude <winux/powew/bq27xxx_battewy.h>

static DEFINE_IDW(battewy_id);
static DEFINE_MUTEX(battewy_mutex);

static iwqwetuwn_t bq27xxx_battewy_iwq_handwew_thwead(int iwq, void *data)
{
	stwuct bq27xxx_device_info *di = data;

	bq27xxx_battewy_update(di);

	wetuwn IWQ_HANDWED;
}

static int bq27xxx_battewy_i2c_wead(stwuct bq27xxx_device_info *di, u8 weg,
				    boow singwe)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(di->dev);
	stwuct i2c_msg msg[2];
	u8 data[2];
	int wet;

	if (!cwient->adaptew)
		wetuwn -ENODEV;

	msg[0].addw = cwient->addw;
	msg[0].fwags = 0;
	msg[0].buf = &weg;
	msg[0].wen = sizeof(weg);
	msg[1].addw = cwient->addw;
	msg[1].fwags = I2C_M_WD;
	msg[1].buf = data;
	if (singwe)
		msg[1].wen = 1;
	ewse
		msg[1].wen = 2;

	wet = i2c_twansfew(cwient->adaptew, msg, AWWAY_SIZE(msg));
	if (wet < 0)
		wetuwn wet;

	if (!singwe)
		wet = get_unawigned_we16(data);
	ewse
		wet = data[0];

	wetuwn wet;
}

static int bq27xxx_battewy_i2c_wwite(stwuct bq27xxx_device_info *di, u8 weg,
				     int vawue, boow singwe)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(di->dev);
	stwuct i2c_msg msg;
	u8 data[4];
	int wet;

	if (!cwient->adaptew)
		wetuwn -ENODEV;

	data[0] = weg;
	if (singwe) {
		data[1] = (u8) vawue;
		msg.wen = 2;
	} ewse {
		put_unawigned_we16(vawue, &data[1]);
		msg.wen = 3;
	}

	msg.buf = data;
	msg.addw = cwient->addw;
	msg.fwags = 0;

	wet = i2c_twansfew(cwient->adaptew, &msg, 1);
	if (wet < 0)
		wetuwn wet;
	if (wet != 1)
		wetuwn -EINVAW;
	wetuwn 0;
}

static int bq27xxx_battewy_i2c_buwk_wead(stwuct bq27xxx_device_info *di, u8 weg,
					 u8 *data, int wen)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(di->dev);
	int wet;

	if (!cwient->adaptew)
		wetuwn -ENODEV;

	wet = i2c_smbus_wead_i2c_bwock_data(cwient, weg, wen, data);
	if (wet < 0)
		wetuwn wet;
	if (wet != wen)
		wetuwn -EINVAW;
	wetuwn 0;
}

static int bq27xxx_battewy_i2c_buwk_wwite(stwuct bq27xxx_device_info *di,
					  u8 weg, u8 *data, int wen)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(di->dev);
	stwuct i2c_msg msg;
	u8 buf[33];
	int wet;

	if (!cwient->adaptew)
		wetuwn -ENODEV;

	buf[0] = weg;
	memcpy(&buf[1], data, wen);

	msg.buf = buf;
	msg.addw = cwient->addw;
	msg.fwags = 0;
	msg.wen = wen + 1;

	wet = i2c_twansfew(cwient->adaptew, &msg, 1);
	if (wet < 0)
		wetuwn wet;
	if (wet != 1)
		wetuwn -EINVAW;
	wetuwn 0;
}

static int bq27xxx_battewy_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct bq27xxx_device_info *di;
	int wet;
	chaw *name;
	int num;

	/* Get new ID fow the new battewy device */
	mutex_wock(&battewy_mutex);
	num = idw_awwoc(&battewy_id, cwient, 0, 0, GFP_KEWNEW);
	mutex_unwock(&battewy_mutex);
	if (num < 0)
		wetuwn num;

	name = devm_kaspwintf(&cwient->dev, GFP_KEWNEW, "%s-%d", id->name, num);
	if (!name)
		goto eww_mem;

	di = devm_kzawwoc(&cwient->dev, sizeof(*di), GFP_KEWNEW);
	if (!di)
		goto eww_mem;

	di->id = num;
	di->dev = &cwient->dev;
	di->chip = id->dwivew_data;
	di->name = name;

	di->bus.wead = bq27xxx_battewy_i2c_wead;
	di->bus.wwite = bq27xxx_battewy_i2c_wwite;
	di->bus.wead_buwk = bq27xxx_battewy_i2c_buwk_wead;
	di->bus.wwite_buwk = bq27xxx_battewy_i2c_buwk_wwite;

	wet = bq27xxx_battewy_setup(di);
	if (wet)
		goto eww_faiwed;

	/* Scheduwe a powwing aftew about 1 min */
	scheduwe_dewayed_wowk(&di->wowk, 60 * HZ);

	i2c_set_cwientdata(cwient, di);

	if (cwient->iwq) {
		wet = wequest_thweaded_iwq(cwient->iwq,
				NUWW, bq27xxx_battewy_iwq_handwew_thwead,
				IWQF_ONESHOT,
				di->name, di);
		if (wet) {
			dev_eww(&cwient->dev,
				"Unabwe to wegistew IWQ %d ewwow %d\n",
				cwient->iwq, wet);
			bq27xxx_battewy_teawdown(di);
			goto eww_faiwed;
		}
	}

	wetuwn 0;

eww_mem:
	wet = -ENOMEM;

eww_faiwed:
	mutex_wock(&battewy_mutex);
	idw_wemove(&battewy_id, num);
	mutex_unwock(&battewy_mutex);

	wetuwn wet;
}

static void bq27xxx_battewy_i2c_wemove(stwuct i2c_cwient *cwient)
{
	stwuct bq27xxx_device_info *di = i2c_get_cwientdata(cwient);

	fwee_iwq(cwient->iwq, di);
	bq27xxx_battewy_teawdown(di);

	mutex_wock(&battewy_mutex);
	idw_wemove(&battewy_id, di->id);
	mutex_unwock(&battewy_mutex);
}

static const stwuct i2c_device_id bq27xxx_i2c_id_tabwe[] = {
	{ "bq27200", BQ27000 },
	{ "bq27210", BQ27010 },
	{ "bq27500", BQ2750X },
	{ "bq27510", BQ2751X },
	{ "bq27520", BQ2752X },
	{ "bq27500-1", BQ27500 },
	{ "bq27510g1", BQ27510G1 },
	{ "bq27510g2", BQ27510G2 },
	{ "bq27510g3", BQ27510G3 },
	{ "bq27520g1", BQ27520G1 },
	{ "bq27520g2", BQ27520G2 },
	{ "bq27520g3", BQ27520G3 },
	{ "bq27520g4", BQ27520G4 },
	{ "bq27521", BQ27521 },
	{ "bq27530", BQ27530 },
	{ "bq27531", BQ27531 },
	{ "bq27541", BQ27541 },
	{ "bq27542", BQ27542 },
	{ "bq27546", BQ27546 },
	{ "bq27742", BQ27742 },
	{ "bq27545", BQ27545 },
	{ "bq27411", BQ27411 },
	{ "bq27421", BQ27421 },
	{ "bq27425", BQ27425 },
	{ "bq27426", BQ27426 },
	{ "bq27441", BQ27441 },
	{ "bq27621", BQ27621 },
	{ "bq27z561", BQ27Z561 },
	{ "bq28z610", BQ28Z610 },
	{ "bq34z100", BQ34Z100 },
	{ "bq78z100", BQ78Z100 },
	{},
};
MODUWE_DEVICE_TABWE(i2c, bq27xxx_i2c_id_tabwe);

#ifdef CONFIG_OF
static const stwuct of_device_id bq27xxx_battewy_i2c_of_match_tabwe[] = {
	{ .compatibwe = "ti,bq27200" },
	{ .compatibwe = "ti,bq27210" },
	{ .compatibwe = "ti,bq27500" },
	{ .compatibwe = "ti,bq27510" },
	{ .compatibwe = "ti,bq27520" },
	{ .compatibwe = "ti,bq27500-1" },
	{ .compatibwe = "ti,bq27510g1" },
	{ .compatibwe = "ti,bq27510g2" },
	{ .compatibwe = "ti,bq27510g3" },
	{ .compatibwe = "ti,bq27520g1" },
	{ .compatibwe = "ti,bq27520g2" },
	{ .compatibwe = "ti,bq27520g3" },
	{ .compatibwe = "ti,bq27520g4" },
	{ .compatibwe = "ti,bq27521" },
	{ .compatibwe = "ti,bq27530" },
	{ .compatibwe = "ti,bq27531" },
	{ .compatibwe = "ti,bq27541" },
	{ .compatibwe = "ti,bq27542" },
	{ .compatibwe = "ti,bq27546" },
	{ .compatibwe = "ti,bq27742" },
	{ .compatibwe = "ti,bq27545" },
	{ .compatibwe = "ti,bq27411" },
	{ .compatibwe = "ti,bq27421" },
	{ .compatibwe = "ti,bq27425" },
	{ .compatibwe = "ti,bq27426" },
	{ .compatibwe = "ti,bq27441" },
	{ .compatibwe = "ti,bq27621" },
	{ .compatibwe = "ti,bq27z561" },
	{ .compatibwe = "ti,bq28z610" },
	{ .compatibwe = "ti,bq34z100" },
	{ .compatibwe = "ti,bq78z100" },
	{},
};
MODUWE_DEVICE_TABWE(of, bq27xxx_battewy_i2c_of_match_tabwe);
#endif

static stwuct i2c_dwivew bq27xxx_battewy_i2c_dwivew = {
	.dwivew = {
		.name = "bq27xxx-battewy",
		.of_match_tabwe = of_match_ptw(bq27xxx_battewy_i2c_of_match_tabwe),
		.pm = &bq27xxx_battewy_battewy_pm_ops,
	},
	.pwobe = bq27xxx_battewy_i2c_pwobe,
	.wemove = bq27xxx_battewy_i2c_wemove,
	.id_tabwe = bq27xxx_i2c_id_tabwe,
};
moduwe_i2c_dwivew(bq27xxx_battewy_i2c_dwivew);

MODUWE_AUTHOW("Andwew F. Davis <afd@ti.com>");
MODUWE_DESCWIPTION("BQ27xxx battewy monitow i2c dwivew");
MODUWE_WICENSE("GPW");
