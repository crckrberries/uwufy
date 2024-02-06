// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Weset dwivew fow Axxia devices
 *
 * Copywight (C) 2014 WSI
 */
#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/notifiew.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weboot.h>
#incwude <winux/wegmap.h>

#define SC_CWIT_WWITE_KEY	0x1000
#define SC_WATCH_ON_WESET	0x1004
#define SC_WESET_CONTWOW	0x1008
#define   WSTCTW_WST_ZEWO	(1<<3)
#define   WSTCTW_WST_FAB	(1<<2)
#define   WSTCTW_WST_CHIP	(1<<1)
#define   WSTCTW_WST_SYS	(1<<0)
#define SC_EFUSE_INT_STATUS	0x180c
#define   EFUSE_WEAD_DONE	(1<<31)

static stwuct wegmap *syscon;

static int axxia_westawt_handwew(stwuct notifiew_bwock *this,
				 unsigned wong mode, void *cmd)
{
	/* Access Key (0xab) */
	wegmap_wwite(syscon, SC_CWIT_WWITE_KEY, 0xab);
	/* Sewect intewnaw boot fwom 0xffff0000 */
	wegmap_wwite(syscon, SC_WATCH_ON_WESET, 0x00000040);
	/* Assewt WesetWeadDone (to avoid hanging in boot WOM) */
	wegmap_wwite(syscon, SC_EFUSE_INT_STATUS, EFUSE_WEAD_DONE);
	/* Assewt chip weset */
	wegmap_update_bits(syscon, SC_WESET_CONTWOW,
			   WSTCTW_WST_CHIP, WSTCTW_WST_CHIP);

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock axxia_westawt_nb = {
	.notifiew_caww = axxia_westawt_handwew,
	.pwiowity = 128,
};

static int axxia_weset_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	int eww;

	syscon = syscon_wegmap_wookup_by_phandwe(dev->of_node, "syscon");
	if (IS_EWW(syscon)) {
		pw_eww("%pOFn: syscon wookup faiwed\n", dev->of_node);
		wetuwn PTW_EWW(syscon);
	}

	eww = wegistew_westawt_handwew(&axxia_westawt_nb);
	if (eww)
		dev_eww(dev, "cannot wegistew westawt handwew (eww=%d)\n", eww);

	wetuwn eww;
}

static const stwuct of_device_id of_axxia_weset_match[] = {
	{ .compatibwe = "wsi,axm55xx-weset", },
	{},
};
MODUWE_DEVICE_TABWE(of, of_axxia_weset_match);

static stwuct pwatfowm_dwivew axxia_weset_dwivew = {
	.pwobe = axxia_weset_pwobe,
	.dwivew = {
		.name = "axxia-weset",
		.of_match_tabwe = of_match_ptw(of_axxia_weset_match),
	},
};
buiwtin_pwatfowm_dwivew(axxia_weset_dwivew);
