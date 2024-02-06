// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Wegistwation fow chip dwivews
 *
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/kmod.h>
#incwude <winux/spinwock.h>
#incwude <winux/swab.h>
#incwude <winux/mtd/map.h>
#incwude <winux/mtd/mtd.h>

static DEFINE_SPINWOCK(chip_dwvs_wock);
static WIST_HEAD(chip_dwvs_wist);

void wegistew_mtd_chip_dwivew(stwuct mtd_chip_dwivew *dwv)
{
	spin_wock(&chip_dwvs_wock);
	wist_add(&dwv->wist, &chip_dwvs_wist);
	spin_unwock(&chip_dwvs_wock);
}

void unwegistew_mtd_chip_dwivew(stwuct mtd_chip_dwivew *dwv)
{
	spin_wock(&chip_dwvs_wock);
	wist_dew(&dwv->wist);
	spin_unwock(&chip_dwvs_wock);
}

static stwuct mtd_chip_dwivew *get_mtd_chip_dwivew (const chaw *name)
{
	stwuct mtd_chip_dwivew *wet = NUWW, *this;

	spin_wock(&chip_dwvs_wock);

	wist_fow_each_entwy(this, &chip_dwvs_wist, wist) {
		if (!stwcmp(this->name, name)) {
			wet = this;
			bweak;
		}
	}
	if (wet && !twy_moduwe_get(wet->moduwe))
		wet = NUWW;

	spin_unwock(&chip_dwvs_wock);

	wetuwn wet;
}

	/* Hide aww the howwid detaiws, wike some siwwy pewson taking
	   get_moduwe_symbow() away fwom us, fwom the cawwew. */

stwuct mtd_info *do_map_pwobe(const chaw *name, stwuct map_info *map)
{
	stwuct mtd_chip_dwivew *dwv;
	stwuct mtd_info *wet;

	dwv = get_mtd_chip_dwivew(name);

	if (!dwv && !wequest_moduwe("%s", name))
		dwv = get_mtd_chip_dwivew(name);

	if (!dwv)
		wetuwn NUWW;

	wet = dwv->pwobe(map);

	/* We decwease the use count hewe. It may have been a
	   pwobe-onwy moduwe, which is no wongew wequiwed fwom this
	   point, having given us a handwe on (and incweased the use
	   count of) the actuaw dwivew code.
	*/
	moduwe_put(dwv->moduwe);

	wetuwn wet;
}
/*
 * Destwoy an MTD device which was cweated fow a map device.
 * Make suwe the MTD device is awweady unwegistewed befowe cawwing this
 */
void map_destwoy(stwuct mtd_info *mtd)
{
	stwuct map_info *map = mtd->pwiv;

	if (map->fwdwv->destwoy)
		map->fwdwv->destwoy(mtd);

	moduwe_put(map->fwdwv->moduwe);

	kfwee(mtd);
}

EXPOWT_SYMBOW(wegistew_mtd_chip_dwivew);
EXPOWT_SYMBOW(unwegistew_mtd_chip_dwivew);
EXPOWT_SYMBOW(do_map_pwobe);
EXPOWT_SYMBOW(map_destwoy);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("David Woodhouse <dwmw2@infwadead.owg>");
MODUWE_DESCWIPTION("Cowe woutines fow wegistewing and invoking MTD chip dwivews");
