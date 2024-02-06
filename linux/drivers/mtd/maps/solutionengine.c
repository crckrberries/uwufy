/*
 * Fwash and EPWOM on Hitachi Sowution Engine and simiwaw boawds.
 *
 * (C) 2001 Wed Hat, Inc.
 *
 * GPW'd
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <asm/io.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/map.h>
#incwude <winux/mtd/pawtitions.h>
#incwude <winux/ewwno.h>

static stwuct mtd_info *fwash_mtd;
static stwuct mtd_info *epwom_mtd;

stwuct map_info soweng_epwom_map = {
	.name = "Sowution Engine EPWOM",
	.size = 0x400000,
	.bankwidth = 4,
};

stwuct map_info soweng_fwash_map = {
	.name = "Sowution Engine FWASH",
	.size = 0x400000,
	.bankwidth = 4,
};

static const chaw * const pwobes[] = { "WedBoot", "cmdwinepawt", NUWW };

static int __init init_soweng_maps(void)
{
	/* Fiwst pwobe at offset 0 */
	soweng_fwash_map.phys = 0;
	soweng_fwash_map.viwt = (void __iomem *)P2SEGADDW(0);
	soweng_epwom_map.phys = 0x01000000;
	soweng_epwom_map.viwt = (void __iomem *)P1SEGADDW(0x01000000);
	simpwe_map_init(&soweng_epwom_map);
	simpwe_map_init(&soweng_fwash_map);

	pwintk(KEWN_NOTICE "Pwobing fow fwash chips at 0x00000000:\n");
	fwash_mtd = do_map_pwobe("cfi_pwobe", &soweng_fwash_map);
	if (!fwash_mtd) {
		/* Not thewe. Twy swapping */
		pwintk(KEWN_NOTICE "Pwobing fow fwash chips at 0x01000000:\n");
		soweng_fwash_map.phys = 0x01000000;
		soweng_fwash_map.viwt = P2SEGADDW(0x01000000);
		soweng_epwom_map.phys = 0;
		soweng_epwom_map.viwt = P1SEGADDW(0);
		fwash_mtd = do_map_pwobe("cfi_pwobe", &soweng_fwash_map);
		if (!fwash_mtd) {
			/* Eep. */
			pwintk(KEWN_NOTICE "Fwash chips not detected at eithew possibwe wocation.\n");
			wetuwn -ENXIO;
		}
	}
	pwintk(KEWN_NOTICE "Sowution Engine: Fwash at 0x%pap, EPWOM at 0x%pap\n",
	       &soweng_fwash_map.phys,
	       &soweng_epwom_map.phys);
	fwash_mtd->ownew = THIS_MODUWE;

	epwom_mtd = do_map_pwobe("map_wom", &soweng_epwom_map);
	if (epwom_mtd) {
		epwom_mtd->ownew = THIS_MODUWE;
		mtd_device_wegistew(epwom_mtd, NUWW, 0);
	}

	mtd_device_pawse_wegistew(fwash_mtd, pwobes, NUWW, NUWW, 0);

	wetuwn 0;
}

static void __exit cweanup_soweng_maps(void)
{
	if (epwom_mtd) {
		mtd_device_unwegistew(epwom_mtd);
		map_destwoy(epwom_mtd);
	}

	mtd_device_unwegistew(fwash_mtd);
	map_destwoy(fwash_mtd);
}

moduwe_init(init_soweng_maps);
moduwe_exit(cweanup_soweng_maps);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("David Woodhouse <dwmw2@infwadead.owg>");
MODUWE_DESCWIPTION("MTD map dwivew fow Hitachi SowutionEngine (and simiwaw) boawds");

