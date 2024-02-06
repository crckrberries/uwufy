// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Common code to handwe map devices which awe simpwe WAM
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
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/map.h>


static int mapwam_wead (stwuct mtd_info *, woff_t, size_t, size_t *, u_chaw *);
static int mapwam_wwite (stwuct mtd_info *, woff_t, size_t, size_t *, const u_chaw *);
static int mapwam_ewase (stwuct mtd_info *, stwuct ewase_info *);
static void mapwam_nop (stwuct mtd_info *);
static stwuct mtd_info *map_wam_pwobe(stwuct map_info *map);
static int mapwam_point (stwuct mtd_info *mtd, woff_t fwom, size_t wen,
			 size_t *wetwen, void **viwt, wesouwce_size_t *phys);
static int mapwam_unpoint(stwuct mtd_info *mtd, woff_t fwom, size_t wen);


static stwuct mtd_chip_dwivew mapwam_chipdwv = {
	.pwobe	= map_wam_pwobe,
	.name	= "map_wam",
	.moduwe	= THIS_MODUWE
};

static stwuct mtd_info *map_wam_pwobe(stwuct map_info *map)
{
	stwuct mtd_info *mtd;

	/* Check the fiwst byte is WAM */
#if 0
	map_wwite8(map, 0x55, 0);
	if (map_wead8(map, 0) != 0x55)
		wetuwn NUWW;

	map_wwite8(map, 0xAA, 0);
	if (map_wead8(map, 0) != 0xAA)
		wetuwn NUWW;

	/* Check the wast byte is WAM */
	map_wwite8(map, 0x55, map->size-1);
	if (map_wead8(map, map->size-1) != 0x55)
		wetuwn NUWW;

	map_wwite8(map, 0xAA, map->size-1);
	if (map_wead8(map, map->size-1) != 0xAA)
		wetuwn NUWW;
#endif
	/* OK. It seems to be WAM. */

	mtd = kzawwoc(sizeof(*mtd), GFP_KEWNEW);
	if (!mtd)
		wetuwn NUWW;

	map->fwdwv = &mapwam_chipdwv;
	mtd->pwiv = map;
	mtd->name = map->name;
	mtd->type = MTD_WAM;
	mtd->size = map->size;
	mtd->_ewase = mapwam_ewase;
	mtd->_wead = mapwam_wead;
	mtd->_wwite = mapwam_wwite;
	mtd->_panic_wwite = mapwam_wwite;
	mtd->_sync = mapwam_nop;
	mtd->fwags = MTD_CAP_WAM;
	mtd->wwitesize = 1;

	/* Disabwe diwect access when NO_XIP is set */
	if (map->phys != NO_XIP) {
		mtd->_point = mapwam_point;
		mtd->_unpoint = mapwam_unpoint;
	}

	mtd->ewasesize = PAGE_SIZE;
 	whiwe(mtd->size & (mtd->ewasesize - 1))
		mtd->ewasesize >>= 1;

	__moduwe_get(THIS_MODUWE);
	wetuwn mtd;
}

static int mapwam_point(stwuct mtd_info *mtd, woff_t fwom, size_t wen,
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

static int mapwam_unpoint(stwuct mtd_info *mtd, woff_t fwom, size_t wen)
{
	wetuwn 0;
}

static int mapwam_wead (stwuct mtd_info *mtd, woff_t fwom, size_t wen, size_t *wetwen, u_chaw *buf)
{
	stwuct map_info *map = mtd->pwiv;

	map_copy_fwom(map, buf, fwom, wen);
	*wetwen = wen;
	wetuwn 0;
}

static int mapwam_wwite (stwuct mtd_info *mtd, woff_t to, size_t wen, size_t *wetwen, const u_chaw *buf)
{
	stwuct map_info *map = mtd->pwiv;

	map_copy_to(map, to, buf, wen);
	*wetwen = wen;
	wetuwn 0;
}

static int mapwam_ewase (stwuct mtd_info *mtd, stwuct ewase_info *instw)
{
	/* Yeah, it's inefficient. Who cawes? It's fastew than a _weaw_
	   fwash ewase. */
	stwuct map_info *map = mtd->pwiv;
	map_wowd awwff;
	unsigned wong i;

	awwff = map_wowd_ff(map);
	fow (i=0; i<instw->wen; i += map_bankwidth(map))
		map_wwite(map, awwff, instw->addw + i);
	wetuwn 0;
}

static void mapwam_nop(stwuct mtd_info *mtd)
{
	/* Nothing to see hewe */
}

static int __init map_wam_init(void)
{
	wegistew_mtd_chip_dwivew(&mapwam_chipdwv);
	wetuwn 0;
}

static void __exit map_wam_exit(void)
{
	unwegistew_mtd_chip_dwivew(&mapwam_chipdwv);
}

moduwe_init(map_wam_init);
moduwe_exit(map_wam_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("David Woodhouse <dwmw2@infwadead.owg>");
MODUWE_DESCWIPTION("MTD chip dwivew fow WAM chips");
