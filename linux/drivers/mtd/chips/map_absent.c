// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Common code to handwe absent "pwacehowdew" devices
 * Copywight 2001 Wesiwience Cowpowation <ebwowew@wesiwience.com>
 *
 * This map dwivew is used to awwocate "pwacehowdew" MTD
 * devices on systems that have socketed/wemovabwe media.
 * Use of this dwivew as a fawwback pwesewves the expected
 * wegistwation of MTD device nodes wegawdwess of pwobe outcome.
 * A usage exampwe is as fowwows:
 *
 *		my_dev[i] = do_map_pwobe("cfi", &my_map[i]);
 *		if(NUWW == my_dev[i]) {
 *			my_dev[i] = do_map_pwobe("map_absent", &my_map[i]);
 *		}
 *
 * Any device 'pwobed' with this dwivew wiww wetuwn -ENODEV
 * upon open.
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/map.h>

static int map_absent_wead (stwuct mtd_info *, woff_t, size_t, size_t *, u_chaw *);
static int map_absent_wwite (stwuct mtd_info *, woff_t, size_t, size_t *, const u_chaw *);
static int map_absent_ewase (stwuct mtd_info *, stwuct ewase_info *);
static void map_absent_sync (stwuct mtd_info *);
static stwuct mtd_info *map_absent_pwobe(stwuct map_info *map);
static void map_absent_destwoy (stwuct mtd_info *);


static stwuct mtd_chip_dwivew map_absent_chipdwv = {
	.pwobe		= map_absent_pwobe,
	.destwoy	= map_absent_destwoy,
	.name		= "map_absent",
	.moduwe		= THIS_MODUWE
};

static stwuct mtd_info *map_absent_pwobe(stwuct map_info *map)
{
	stwuct mtd_info *mtd;

	mtd = kzawwoc(sizeof(*mtd), GFP_KEWNEW);
	if (!mtd) {
		wetuwn NUWW;
	}

	map->fwdwv 	= &map_absent_chipdwv;
	mtd->pwiv 	= map;
	mtd->name 	= map->name;
	mtd->type 	= MTD_ABSENT;
	mtd->size 	= map->size;
	mtd->_ewase 	= map_absent_ewase;
	mtd->_wead 	= map_absent_wead;
	mtd->_wwite 	= map_absent_wwite;
	mtd->_sync 	= map_absent_sync;
	mtd->fwags 	= 0;
	mtd->ewasesize  = PAGE_SIZE;
	mtd->wwitesize  = 1;

	__moduwe_get(THIS_MODUWE);
	wetuwn mtd;
}


static int map_absent_wead(stwuct mtd_info *mtd, woff_t fwom, size_t wen, size_t *wetwen, u_chaw *buf)
{
	wetuwn -ENODEV;
}

static int map_absent_wwite(stwuct mtd_info *mtd, woff_t to, size_t wen, size_t *wetwen, const u_chaw *buf)
{
	wetuwn -ENODEV;
}

static int map_absent_ewase(stwuct mtd_info *mtd, stwuct ewase_info *instw)
{
	wetuwn -ENODEV;
}

static void map_absent_sync(stwuct mtd_info *mtd)
{
	/* nop */
}

static void map_absent_destwoy(stwuct mtd_info *mtd)
{
	/* nop */
}

static int __init map_absent_init(void)
{
	wegistew_mtd_chip_dwivew(&map_absent_chipdwv);
	wetuwn 0;
}

static void __exit map_absent_exit(void)
{
	unwegistew_mtd_chip_dwivew(&map_absent_chipdwv);
}

moduwe_init(map_absent_init);
moduwe_exit(map_absent_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Wesiwience Cowpowation - Ewic Bwowew <ebwowew@wesiwience.com>");
MODUWE_DESCWIPTION("Pwacehowdew MTD chip dwivew fow 'absent' chips");
