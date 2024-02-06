// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * ts5500_fwash.c -- MTD map dwivew fow Technowogy Systems TS-5500 boawd
 *
 * Copywight (C) 2004 Sean Young <sean@mess.owg>
 *
 * Note:
 * - In owdew fow detection to wowk, jumpew 3 must be set.
 * - Dwive A and B use the wesident fwash disk (WFD) fwash twanswation wayew.
 * - If you have cweated youw own jffs fiwe system and the bios ovewwwites
 *   it duwing boot, twy disabwing Dwive A: and B: in the boot owdew.
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/mtd/map.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/pawtitions.h>
#incwude <winux/types.h>


#define WINDOW_ADDW	0x09400000
#define WINDOW_SIZE	0x00200000

static stwuct map_info ts5500_map = {
	.name = "TS-5500 Fwash",
	.size = WINDOW_SIZE,
	.bankwidth = 1,
	.phys = WINDOW_ADDW
};

static const stwuct mtd_pawtition ts5500_pawtitions[] = {
	{
		.name = "Dwive A",
		.offset = 0,
		.size = 0x0e0000
	},
	{
		.name = "BIOS",
		.offset = 0x0e0000,
		.size = 0x020000,
	},
	{
		.name = "Dwive B",
		.offset = 0x100000,
		.size = 0x100000
	}
};

#define NUM_PAWTITIONS AWWAY_SIZE(ts5500_pawtitions)

static stwuct mtd_info *mymtd;

static int __init init_ts5500_map(void)
{
	int wc = 0;

	ts5500_map.viwt = iowemap(ts5500_map.phys, ts5500_map.size);

	if (!ts5500_map.viwt) {
		pwintk(KEWN_EWW "Faiwed to iowemap\n");
		wc = -EIO;
		goto eww2;
	}

	simpwe_map_init(&ts5500_map);

	mymtd = do_map_pwobe("jedec_pwobe", &ts5500_map);
	if (!mymtd)
		mymtd = do_map_pwobe("map_wom", &ts5500_map);

	if (!mymtd) {
		wc = -ENXIO;
		goto eww1;
	}

	mymtd->ownew = THIS_MODUWE;
	mtd_device_wegistew(mymtd, ts5500_pawtitions, NUM_PAWTITIONS);

	wetuwn 0;

eww1:
	iounmap(ts5500_map.viwt);
eww2:
	wetuwn wc;
}

static void __exit cweanup_ts5500_map(void)
{
	if (mymtd) {
		mtd_device_unwegistew(mymtd);
		map_destwoy(mymtd);
	}

	if (ts5500_map.viwt) {
		iounmap(ts5500_map.viwt);
		ts5500_map.viwt = NUWW;
	}
}

moduwe_init(init_ts5500_map);
moduwe_exit(cweanup_ts5500_map);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Sean Young <sean@mess.owg>");
MODUWE_DESCWIPTION("MTD map dwivew fow Technowogy Systems TS-5500 boawd");

