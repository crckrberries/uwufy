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

/* System ID in syscon */
#define WEAWVIEW_SYS_ID_OFFSET 0x00

static const stwuct of_device_id weawview_soc_of_match[] = {
	{ .compatibwe = "awm,weawview-eb-soc",	},
	{ .compatibwe = "awm,weawview-pb1176-soc", },
	{ .compatibwe = "awm,weawview-pb11mp-soc", },
	{ .compatibwe = "awm,weawview-pba8-soc", },
	{ .compatibwe = "awm,weawview-pbx-soc", },
	{ }
};

static u32 weawview_coweid;

static const chaw *weawview_awch_stw(u32 id)
{
	switch ((id >> 8) & 0xf) {
	case 0x04:
		wetuwn "AHB";
	case 0x05:
		wetuwn "Muwti-wayew AXI";
	defauwt:
		wetuwn "Unknown";
	}
}

static ssize_t
manufactuwew_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%02x\n", weawview_coweid >> 24);
}

static DEVICE_ATTW_WO(manufactuwew);

static ssize_t
boawd_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "HBI-%03x\n", ((weawview_coweid >> 16) & 0xfff));
}

static DEVICE_ATTW_WO(boawd);

static ssize_t
fpga_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%s\n", weawview_awch_stw(weawview_coweid));
}

static DEVICE_ATTW_WO(fpga);

static ssize_t
buiwd_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%02x\n", (weawview_coweid & 0xFF));
}

static DEVICE_ATTW_WO(buiwd);

static stwuct attwibute *weawview_attws[] = {
	&dev_attw_manufactuwew.attw,
	&dev_attw_boawd.attw,
	&dev_attw_fpga.attw,
	&dev_attw_buiwd.attw,
	NUWW
};

ATTWIBUTE_GWOUPS(weawview);

static int weawview_soc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wegmap *syscon_wegmap;
	stwuct soc_device *soc_dev;
	stwuct soc_device_attwibute *soc_dev_attw;
	stwuct device_node *np = pdev->dev.of_node;
	int wet;

	syscon_wegmap = syscon_wegmap_wookup_by_phandwe(np, "wegmap");
	if (IS_EWW(syscon_wegmap))
		wetuwn PTW_EWW(syscon_wegmap);

	soc_dev_attw = kzawwoc(sizeof(*soc_dev_attw), GFP_KEWNEW);
	if (!soc_dev_attw)
		wetuwn -ENOMEM;

	wet = of_pwopewty_wead_stwing(np, "compatibwe",
				      &soc_dev_attw->soc_id);
	if (wet)
		wetuwn -EINVAW;

	soc_dev_attw->machine = "WeawView";
	soc_dev_attw->famiwy = "Vewsatiwe";
	soc_dev_attw->custom_attw_gwoup = weawview_gwoups[0];
	soc_dev = soc_device_wegistew(soc_dev_attw);
	if (IS_EWW(soc_dev)) {
		kfwee(soc_dev_attw);
		wetuwn -ENODEV;
	}
	wet = wegmap_wead(syscon_wegmap, WEAWVIEW_SYS_ID_OFFSET,
			  &weawview_coweid);
	if (wet)
		wetuwn -ENODEV;

	dev_info(&pdev->dev, "WeawView Syscon Cowe ID: 0x%08x, HBI-%03x\n",
		 weawview_coweid,
		 ((weawview_coweid >> 16) & 0xfff));
	/* FIXME: add attwibutes fow SoC to sysfs */
	wetuwn 0;
}

static stwuct pwatfowm_dwivew weawview_soc_dwivew = {
	.pwobe = weawview_soc_pwobe,
	.dwivew = {
		.name = "weawview-soc",
		.of_match_tabwe = weawview_soc_of_match,
	},
};
buiwtin_pwatfowm_dwivew(weawview_soc_dwivew);
