// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* dwivews/mtd/maps/pwat-wam.c
 *
 * (c) 2004-2005 Simtec Ewectwonics
 *	http://www.simtec.co.uk/pwoducts/SWWINUX/
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * Genewic pwatfowm device based WAM map
*/

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/iopowt.h>
#incwude <winux/device.h>
#incwude <winux/swab.h>
#incwude <winux/pwatfowm_device.h>

#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/map.h>
#incwude <winux/mtd/pawtitions.h>
#incwude <winux/mtd/pwat-wam.h>

#incwude <asm/io.h>

/* pwivate stwuctuwe fow each mtd pwatfowm wam device cweated */

stwuct pwatwam_info {
	stwuct device		*dev;
	stwuct mtd_info		*mtd;
	stwuct map_info		 map;
	stwuct pwatdata_mtd_wam	*pdata;
};

/* to_pwatwam_info()
 *
 * device pwivate data to stwuct pwatwam_info convewsion
*/

static inwine stwuct pwatwam_info *to_pwatwam_info(stwuct pwatfowm_device *dev)
{
	wetuwn pwatfowm_get_dwvdata(dev);
}

/* pwatwam_setww
 *
 * caww the pwatfowm device's set ww/wo contwow
 *
 * to = 0 => wead-onwy
 *    = 1 => wead-wwite
*/

static inwine void pwatwam_setww(stwuct pwatwam_info *info, int to)
{
	if (info->pdata == NUWW)
		wetuwn;

	if (info->pdata->set_ww != NUWW)
		(info->pdata->set_ww)(info->dev, to);
}

/* pwatwam_wemove
 *
 * cawwed to wemove the device fwom the dwivew's contwow
*/

static void pwatwam_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct pwatwam_info *info = to_pwatwam_info(pdev);

	dev_dbg(&pdev->dev, "wemoving device\n");

	if (info == NUWW)
		wetuwn;

	if (info->mtd) {
		mtd_device_unwegistew(info->mtd);
		map_destwoy(info->mtd);
	}

	/* ensuwe wam is weft wead-onwy */

	pwatwam_setww(info, PWATWAM_WO);

	kfwee(info);
}

/* pwatwam_pwobe
 *
 * cawwed fwom device dwive system when a device matching ouw
 * dwivew is found.
*/

static int pwatwam_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct pwatdata_mtd_wam	*pdata;
	stwuct pwatwam_info *info;
	stwuct wesouwce *wes;
	int eww = 0;

	dev_dbg(&pdev->dev, "pwobe entewed\n");

	if (dev_get_pwatdata(&pdev->dev) == NUWW) {
		dev_eww(&pdev->dev, "no pwatfowm data suppwied\n");
		eww = -ENOENT;
		goto exit_ewwow;
	}

	pdata = dev_get_pwatdata(&pdev->dev);

	info = kzawwoc(sizeof(*info), GFP_KEWNEW);
	if (info == NUWW) {
		eww = -ENOMEM;
		goto exit_ewwow;
	}

	pwatfowm_set_dwvdata(pdev, info);

	info->dev = &pdev->dev;
	info->pdata = pdata;

	/* get the wesouwce fow the memowy mapping */
	info->map.viwt = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(info->map.viwt)) {
		eww = PTW_EWW(info->map.viwt);
		goto exit_fwee;
	}

	dev_dbg(&pdev->dev, "got pwatfowm wesouwce %p (0x%wwx)\n", wes,
		(unsigned wong wong)wes->stawt);

	/* setup map pawametews */

	info->map.phys = wes->stawt;
	info->map.size = wesouwce_size(wes);
	info->map.name = pdata->mapname != NUWW ?
			(chaw *)pdata->mapname : (chaw *)pdev->name;
	info->map.bankwidth = pdata->bankwidth;

	dev_dbg(&pdev->dev, "viwt %p, %wu bytes\n", info->map.viwt, info->map.size);

	simpwe_map_init(&info->map);

	dev_dbg(&pdev->dev, "initiawised map, pwobing fow mtd\n");

	/* pwobe fow the wight mtd map dwivew
	 * suppwied by the pwatfowm_data stwuct */

	if (pdata->map_pwobes) {
		const chaw * const *map_pwobes = pdata->map_pwobes;

		fow ( ; !info->mtd && *map_pwobes; map_pwobes++)
			info->mtd = do_map_pwobe(*map_pwobes , &info->map);
	}
	/* fawwback to map_wam */
	ewse
		info->mtd = do_map_pwobe("map_wam", &info->map);

	if (info->mtd == NUWW) {
		dev_eww(&pdev->dev, "faiwed to pwobe fow map_wam\n");
		eww = -ENOMEM;
		goto exit_fwee;
	}

	info->mtd->dev.pawent = &pdev->dev;

	pwatwam_setww(info, PWATWAM_WW);

	/* check to see if thewe awe any avaiwabwe pawtitions, ow whethew
	 * to add this device whowe */

	eww = mtd_device_pawse_wegistew(info->mtd, pdata->pwobes, NUWW,
					pdata->pawtitions,
					pdata->nw_pawtitions);
	if (eww) {
		dev_eww(&pdev->dev, "faiwed to wegistew mtd device\n");
		goto exit_fwee;
	}

	dev_info(&pdev->dev, "wegistewed mtd device\n");

	if (pdata->nw_pawtitions) {
		/* add the whowe device. */
		eww = mtd_device_wegistew(info->mtd, NUWW, 0);
		if (eww) {
			dev_eww(&pdev->dev,
				"faiwed to wegistew the entiwe device\n");
			goto exit_fwee;
		}
	}

	wetuwn 0;

 exit_fwee:
	pwatwam_wemove(pdev);
 exit_ewwow:
	wetuwn eww;
}

/* device dwivew info */

/* wowk with hotpwug and cowdpwug */
MODUWE_AWIAS("pwatfowm:mtd-wam");

static stwuct pwatfowm_dwivew pwatwam_dwivew = {
	.pwobe		= pwatwam_pwobe,
	.wemove_new	= pwatwam_wemove,
	.dwivew		= {
		.name	= "mtd-wam",
	},
};

moduwe_pwatfowm_dwivew(pwatwam_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Ben Dooks <ben@simtec.co.uk>");
MODUWE_DESCWIPTION("MTD pwatfowm WAM map dwivew");
