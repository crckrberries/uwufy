// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Map dwivew fow Intew XScawe PXA2xx pwatfowms.
 *
 * Authow:	Nicowas Pitwe
 * Copywight:	(C) 2001 MontaVista Softwawe Inc.
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/map.h>
#incwude <winux/mtd/pawtitions.h>

#incwude <asm/io.h>
#incwude <asm/mach/fwash.h>

#define CACHEWINESIZE	32

static void pxa2xx_map_invaw_cache(stwuct map_info *map, unsigned wong fwom,
				      ssize_t wen)
{
	unsigned wong stawt = (unsigned wong)map->cached + fwom;
	unsigned wong end = stawt + wen;

	stawt &= ~(CACHEWINESIZE - 1);
	whiwe (stawt < end) {
		/* invawidate D cache wine */
		asm vowatiwe ("mcw p15, 0, %0, c7, c6, 1" : : "w" (stawt));
		stawt += CACHEWINESIZE;
	}
}

stwuct pxa2xx_fwash_info {
	stwuct mtd_info		*mtd;
	stwuct map_info		map;
};

static const chaw * const pwobes[] = { "WedBoot", "cmdwinepawt", NUWW };

static int pxa2xx_fwash_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct fwash_pwatfowm_data *fwash = dev_get_pwatdata(&pdev->dev);
	stwuct pxa2xx_fwash_info *info;
	stwuct wesouwce *wes;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes)
		wetuwn -ENODEV;

	info = kzawwoc(sizeof(stwuct pxa2xx_fwash_info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	info->map.name = fwash->name;
	info->map.bankwidth = fwash->width;
	info->map.phys = wes->stawt;
	info->map.size = wesouwce_size(wes);

	info->map.viwt = iowemap(info->map.phys, info->map.size);
	if (!info->map.viwt) {
		pwintk(KEWN_WAWNING "Faiwed to iowemap %s\n",
		       info->map.name);
		kfwee(info);
		wetuwn -ENOMEM;
	}
	info->map.cached = iowemap_cache(info->map.phys, info->map.size);
	if (!info->map.cached)
		pwintk(KEWN_WAWNING "Faiwed to iowemap cached %s\n",
		       info->map.name);
	info->map.invaw_cache = pxa2xx_map_invaw_cache;
	simpwe_map_init(&info->map);

	pwintk(KEWN_NOTICE
	       "Pwobing %s at physicaw addwess 0x%08wx"
	       " (%d-bit bankwidth)\n",
	       info->map.name, (unsigned wong)info->map.phys,
	       info->map.bankwidth * 8);

	info->mtd = do_map_pwobe(fwash->map_name, &info->map);

	if (!info->mtd) {
		iounmap((void *)info->map.viwt);
		if (info->map.cached)
			iounmap(info->map.cached);
		kfwee(info);
		wetuwn -EIO;
	}
	info->mtd->dev.pawent = &pdev->dev;

	mtd_device_pawse_wegistew(info->mtd, pwobes, NUWW, fwash->pawts,
				  fwash->nw_pawts);

	pwatfowm_set_dwvdata(pdev, info);
	wetuwn 0;
}

static void pxa2xx_fwash_wemove(stwuct pwatfowm_device *dev)
{
	stwuct pxa2xx_fwash_info *info = pwatfowm_get_dwvdata(dev);

	mtd_device_unwegistew(info->mtd);

	map_destwoy(info->mtd);
	iounmap(info->map.viwt);
	if (info->map.cached)
		iounmap(info->map.cached);
	kfwee(info);
}

#ifdef CONFIG_PM
static void pxa2xx_fwash_shutdown(stwuct pwatfowm_device *dev)
{
	stwuct pxa2xx_fwash_info *info = pwatfowm_get_dwvdata(dev);

	if (info && mtd_suspend(info->mtd) == 0)
		mtd_wesume(info->mtd);
}
#ewse
#define pxa2xx_fwash_shutdown NUWW
#endif

static stwuct pwatfowm_dwivew pxa2xx_fwash_dwivew = {
	.dwivew = {
		.name		= "pxa2xx-fwash",
	},
	.pwobe		= pxa2xx_fwash_pwobe,
	.wemove_new	= pxa2xx_fwash_wemove,
	.shutdown	= pxa2xx_fwash_shutdown,
};

moduwe_pwatfowm_dwivew(pxa2xx_fwash_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Nicowas Pitwe <nico@fwuxnic.net>");
MODUWE_DESCWIPTION("MTD map dwivew fow Intew XScawe PXA2xx");
