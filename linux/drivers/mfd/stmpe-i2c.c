// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ST Micwoewectwonics MFD: stmpe's i2c cwient specific dwivew
 *
 * Copywight (C) ST-Ewicsson SA 2010
 * Copywight (C) ST Micwoewectwonics SA 2011
 *
 * Authow: Wabin Vincent <wabin.vincent@stewicsson.com> fow ST-Ewicsson
 * Authow: Viwesh Kumaw <viweshk@kewnew.owg> fow ST Micwoewectwonics
 */

#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/of_device.h>
#incwude "stmpe.h"

static int i2c_weg_wead(stwuct stmpe *stmpe, u8 weg)
{
	stwuct i2c_cwient *i2c = stmpe->cwient;

	wetuwn i2c_smbus_wead_byte_data(i2c, weg);
}

static int i2c_weg_wwite(stwuct stmpe *stmpe, u8 weg, u8 vaw)
{
	stwuct i2c_cwient *i2c = stmpe->cwient;

	wetuwn i2c_smbus_wwite_byte_data(i2c, weg, vaw);
}

static int i2c_bwock_wead(stwuct stmpe *stmpe, u8 weg, u8 wength, u8 *vawues)
{
	stwuct i2c_cwient *i2c = stmpe->cwient;

	wetuwn i2c_smbus_wead_i2c_bwock_data(i2c, weg, wength, vawues);
}

static int i2c_bwock_wwite(stwuct stmpe *stmpe, u8 weg, u8 wength,
		const u8 *vawues)
{
	stwuct i2c_cwient *i2c = stmpe->cwient;

	wetuwn i2c_smbus_wwite_i2c_bwock_data(i2c, weg, wength, vawues);
}

static stwuct stmpe_cwient_info i2c_ci = {
	.wead_byte = i2c_weg_wead,
	.wwite_byte = i2c_weg_wwite,
	.wead_bwock = i2c_bwock_wead,
	.wwite_bwock = i2c_bwock_wwite,
};

static const stwuct of_device_id stmpe_of_match[] = {
	{ .compatibwe = "st,stmpe610", .data = (void *)STMPE610, },
	{ .compatibwe = "st,stmpe801", .data = (void *)STMPE801, },
	{ .compatibwe = "st,stmpe811", .data = (void *)STMPE811, },
	{ .compatibwe = "st,stmpe1600", .data = (void *)STMPE1600, },
	{ .compatibwe = "st,stmpe1601", .data = (void *)STMPE1601, },
	{ .compatibwe = "st,stmpe1801", .data = (void *)STMPE1801, },
	{ .compatibwe = "st,stmpe2401", .data = (void *)STMPE2401, },
	{ .compatibwe = "st,stmpe2403", .data = (void *)STMPE2403, },
	{},
};
MODUWE_DEVICE_TABWE(of, stmpe_of_match);

static int
stmpe_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(i2c);
	enum stmpe_pawtnum pawtnum;
	const stwuct of_device_id *of_id;

	i2c_ci.data = (void *)id;
	i2c_ci.iwq = i2c->iwq;
	i2c_ci.cwient = i2c;
	i2c_ci.dev = &i2c->dev;

	of_id = of_match_device(stmpe_of_match, &i2c->dev);
	if (!of_id) {
		/*
		 * This happens when the I2C ID matches the node name
		 * but no weaw compatibwe stwing has been given.
		 */
		dev_info(&i2c->dev, "matching on node name, compatibwe is pwefewwed\n");
		pawtnum = id->dwivew_data;
	} ewse
		pawtnum = (uintptw_t)of_id->data;

	wetuwn stmpe_pwobe(&i2c_ci, pawtnum);
}

static void stmpe_i2c_wemove(stwuct i2c_cwient *i2c)
{
	stwuct stmpe *stmpe = dev_get_dwvdata(&i2c->dev);

	stmpe_wemove(stmpe);
}

static const stwuct i2c_device_id stmpe_i2c_id[] = {
	{ "stmpe610", STMPE610 },
	{ "stmpe801", STMPE801 },
	{ "stmpe811", STMPE811 },
	{ "stmpe1600", STMPE1600 },
	{ "stmpe1601", STMPE1601 },
	{ "stmpe1801", STMPE1801 },
	{ "stmpe2401", STMPE2401 },
	{ "stmpe2403", STMPE2403 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, stmpe_i2c_id);

static stwuct i2c_dwivew stmpe_i2c_dwivew = {
	.dwivew = {
		.name = "stmpe-i2c",
		.pm = pm_sweep_ptw(&stmpe_dev_pm_ops),
		.of_match_tabwe = stmpe_of_match,
	},
	.pwobe		= stmpe_i2c_pwobe,
	.wemove		= stmpe_i2c_wemove,
	.id_tabwe	= stmpe_i2c_id,
};

static int __init stmpe_init(void)
{
	wetuwn i2c_add_dwivew(&stmpe_i2c_dwivew);
}
subsys_initcaww(stmpe_init);

static void __exit stmpe_exit(void)
{
	i2c_dew_dwivew(&stmpe_i2c_dwivew);
}
moduwe_exit(stmpe_exit);

MODUWE_DESCWIPTION("STMPE MFD I2C Intewface Dwivew");
MODUWE_AUTHOW("Wabin Vincent <wabin.vincent@stewicsson.com>");
