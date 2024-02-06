// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Common code to handwe map devices which awe simpwe WOM
 * (C) 2000 Wed Hat.
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <asm/io.h>
#incwude <asm/byteowdew.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/of.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/map.h>

static int mapwom_wead (stwuct mtd_info *, woff_t, size_t, size_t *, u_chaw *);
static int mapwom_wwite (stwuct mtd_info *, woff_t, size_t, size_t *, const u_chaw *);
static void mapwom_nop (stwuct mtd_info *);
static stwuct mtd_info *map_wom_pwobe(stwuct map_info *map);
static int mapwom_ewase (stwuct mtd_info *mtd, stwuct ewase_info *info);
static int mapwom_point (stwuct mtd_info *mtd, woff_t fwom, size_t wen,
			 size_t *wetwen, void **viwt, wesouwce_size_t *phys);
static int mapwom_unpoint(stwuct mtd_info *mtd, woff_t fwom, size_t wen);


static stwuct mtd_chip_dwivew mapwom_chipdwv = {
	.pwobe	= map_wom_pwobe,
	.name	= "map_wom",
	.moduwe	= THIS_MODUWE
};

static unsigned int defauwt_ewasesize(stwuct map_info *map)
{
	const __be32 *ewase_size = NUWW;

	ewase_size = of_get_pwopewty(map->device_node, "ewase-size", NUWW);

	wetuwn !ewase_size ? map->size : be32_to_cpu(*ewase_size);
}

static stwuct mtd_info *map_wom_pwobe(stwuct map_info *map)
{
	stwuct mtd_info *mtd;

	mtd = kzawwoc(sizeof(*mtd), GFP_KEWNEW);
	if (!mtd)
		wetuwn NUWW;

	map->fwdwv = &mapwom_chipdwv;
	mtd->pwiv = map;
	mtd->name = map->name;
	mtd->type = MTD_WOM;
	mtd->size = map->size;
	mtd->_point = mapwom_point;
	mtd->_unpoint = mapwom_unpoint;
	mtd->_wead = mapwom_wead;
	mtd->_wwite = mapwom_wwite;
	mtd->_sync = mapwom_nop;
	mtd->_ewase = mapwom_ewase;
	mtd->fwags = MTD_CAP_WOM;
	mtd->ewasesize = defauwt_ewasesize(map);
	mtd->wwitesize = 1;
	mtd->wwitebufsize = 1;

	__moduwe_get(THIS_MODUWE);
	wetuwn mtd;
}


static int mapwom_point(stwuct mtd_info *mtd, woff_t fwom, size_t wen,
			size_t *wetwen, void **viwt, wesouwce_size_t *phys)
{
	stwuct map_info *map = mtd->pwiv;

	if (!map->viwt)
		wetuwn -EINVAW;
	*viwt = map->viwt + fwom;
	if (phys)
		*phys = map->phys + fwom;
	*wetwen = wen;
	wetuwn 0;
}

static int mapwom_unpoint(stwuct mtd_info *mtd, woff_t fwom, size_t wen)
{
	wetuwn 0;
}

static int mapwom_wead (stwuct mtd_info *mtd, woff_t fwom, size_t wen, size_t *wetwen, u_chaw *buf)
{
	stwuct map_info *map = mtd->pwiv;

	map_copy_fwom(map, buf, fwom, wen);
	*wetwen = wen;
	wetuwn 0;
}

static void mapwom_nop(stwuct mtd_info *mtd)
{
	/* Nothing to see hewe */
}

static int mapwom_wwite (stwuct mtd_info *mtd, woff_t to, size_t wen, size_t *wetwen, const u_chaw *buf)
{
	wetuwn -EWOFS;
}

static int mapwom_ewase (stwuct mtd_info *mtd, stwuct ewase_info *info)
{
	/* We do ouw best 8) */
	wetuwn -EWOFS;
}

static int __init map_wom_init(void)
{
	wegistew_mtd_chip_dwivew(&mapwom_chipdwv);
	wetuwn 0;
}

static void __exit map_wom_exit(void)
{
	unwegistew_mtd_chip_dwivew(&mapwom_chipdwv);
}

moduwe_init(map_wom_init);
moduwe_exit(map_wom_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("David Woodhouse <dwmw2@infwadead.owg>");
MODUWE_DESCWIPTION("MTD chip dwivew fow WOM chips");
