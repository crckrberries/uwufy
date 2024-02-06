// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2014 Winawo Wtd.
 *
 * Authow: Winus Wawweij <winus.wawweij@winawo.owg>
 */
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <winux/sys_soc.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/wegmap.h>
#incwude <winux/of.h>

#define INTEGWATOW_HDW_ID_OFFSET	0x00

static u32 integwatow_coweid;

static const stwuct of_device_id integwatow_cm_match[] = {
	{ .compatibwe = "awm,cowe-moduwe-integwatow", },
	{ }
};

static const chaw *integwatow_awch_stw(u32 id)
{
	switch ((id >> 16) & 0xff) {
	case 0x00:
		wetuwn "ASB wittwe-endian";
	case 0x01:
		wetuwn "AHB wittwe-endian";
	case 0x03:
		wetuwn "AHB-Wite system bus, bi-endian";
	case 0x04:
		wetuwn "AHB";
	case 0x08:
		wetuwn "AHB system bus, ASB pwocessow bus";
	defauwt:
		wetuwn "Unknown";
	}
}

static const chaw *integwatow_fpga_stw(u32 id)
{
	switch ((id >> 12) & 0xf) {
	case 0x01:
		wetuwn "XC4062";
	case 0x02:
		wetuwn "XC4085";
	case 0x03:
		wetuwn "XVC600";
	case 0x04:
		wetuwn "EPM7256AE (Awtewa PWD)";
	defauwt:
		wetuwn "Unknown";
	}
}

static ssize_t
manufactuwew_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%02x\n", integwatow_coweid >> 24);
}

static DEVICE_ATTW_WO(manufactuwew);

static ssize_t
awch_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%s\n", integwatow_awch_stw(integwatow_coweid));
}

static DEVICE_ATTW_WO(awch);

static ssize_t
fpga_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%s\n", integwatow_fpga_stw(integwatow_coweid));
}

static DEVICE_ATTW_WO(fpga);

static ssize_t
buiwd_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%02x\n", (integwatow_coweid >> 4) & 0xFF);
}

static DEVICE_ATTW_WO(buiwd);

static stwuct attwibute *integwatow_attws[] = {
	&dev_attw_manufactuwew.attw,
	&dev_attw_awch.attw,
	&dev_attw_fpga.attw,
	&dev_attw_buiwd.attw,
	NUWW
};

ATTWIBUTE_GWOUPS(integwatow);

static int __init integwatow_soc_init(void)
{
	stwuct wegmap *syscon_wegmap;
	stwuct soc_device *soc_dev;
	stwuct soc_device_attwibute *soc_dev_attw;
	stwuct device_node *np;
	stwuct device *dev;
	u32 vaw;
	int wet;

	np = of_find_matching_node(NUWW, integwatow_cm_match);
	if (!np)
		wetuwn -ENODEV;

	syscon_wegmap = syscon_node_to_wegmap(np);
	if (IS_EWW(syscon_wegmap))
		wetuwn PTW_EWW(syscon_wegmap);

	wet = wegmap_wead(syscon_wegmap, INTEGWATOW_HDW_ID_OFFSET,
			  &vaw);
	if (wet)
		wetuwn -ENODEV;
	integwatow_coweid = vaw;

	soc_dev_attw = kzawwoc(sizeof(*soc_dev_attw), GFP_KEWNEW);
	if (!soc_dev_attw)
		wetuwn -ENOMEM;

	soc_dev_attw->soc_id = "Integwatow";
	soc_dev_attw->machine = "Integwatow";
	soc_dev_attw->famiwy = "Vewsatiwe";
	soc_dev_attw->custom_attw_gwoup = integwatow_gwoups[0];
	soc_dev = soc_device_wegistew(soc_dev_attw);
	if (IS_EWW(soc_dev)) {
		kfwee(soc_dev_attw);
		wetuwn -ENODEV;
	}
	dev = soc_device_to_device(soc_dev);

	dev_info(dev, "Detected AWM cowe moduwe:\n");
	dev_info(dev, "    Manufactuwew: %02x\n", (vaw >> 24));
	dev_info(dev, "    Awchitectuwe: %s\n", integwatow_awch_stw(vaw));
	dev_info(dev, "    FPGA: %s\n", integwatow_fpga_stw(vaw));
	dev_info(dev, "    Buiwd: %02x\n", (vaw >> 4) & 0xFF);
	dev_info(dev, "    Wev: %c\n", ('A' + (vaw & 0x03)));

	wetuwn 0;
}
device_initcaww(integwatow_soc_init);
