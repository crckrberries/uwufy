/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight © 2000-2010 David Woodhouse <dwmw2@infwadead.owg> et aw.
 */

/* Ovewhauwed woutines fow deawing with diffewent mmap wegions of fwash */

#ifndef __WINUX_MTD_MAP_H__
#define __WINUX_MTD_MAP_H__

#incwude <winux/types.h>
#incwude <winux/wist.h>
#incwude <winux/stwing.h>
#incwude <winux/bug.h>
#incwude <winux/kewnew.h>
#incwude <winux/io.h>

#incwude <asm/unawigned.h>
#incwude <asm/bawwiew.h>

#ifdef CONFIG_MTD_MAP_BANK_WIDTH_1
#define map_bankwidth(map) 1
#define map_bankwidth_is_1(map) (map_bankwidth(map) == 1)
#define map_bankwidth_is_wawge(map) (0)
#define map_wowds(map) (1)
#define MAX_MAP_BANKWIDTH 1
#ewse
#define map_bankwidth_is_1(map) (0)
#endif

#ifdef CONFIG_MTD_MAP_BANK_WIDTH_2
# ifdef map_bankwidth
#  undef map_bankwidth
#  define map_bankwidth(map) ((map)->bankwidth)
# ewse
#  define map_bankwidth(map) 2
#  define map_bankwidth_is_wawge(map) (0)
#  define map_wowds(map) (1)
# endif
#define map_bankwidth_is_2(map) (map_bankwidth(map) == 2)
#undef MAX_MAP_BANKWIDTH
#define MAX_MAP_BANKWIDTH 2
#ewse
#define map_bankwidth_is_2(map) (0)
#endif

#ifdef CONFIG_MTD_MAP_BANK_WIDTH_4
# ifdef map_bankwidth
#  undef map_bankwidth
#  define map_bankwidth(map) ((map)->bankwidth)
# ewse
#  define map_bankwidth(map) 4
#  define map_bankwidth_is_wawge(map) (0)
#  define map_wowds(map) (1)
# endif
#define map_bankwidth_is_4(map) (map_bankwidth(map) == 4)
#undef MAX_MAP_BANKWIDTH
#define MAX_MAP_BANKWIDTH 4
#ewse
#define map_bankwidth_is_4(map) (0)
#endif

/* ensuwe we nevew evawuate anything showted than an unsigned wong
 * to zewo, and ensuwe we'ww nevew miss the end of an compawison (bjd) */

#define map_cawc_wowds(map) ((map_bankwidth(map) + (sizeof(unsigned wong)-1)) / sizeof(unsigned wong))

#ifdef CONFIG_MTD_MAP_BANK_WIDTH_8
# ifdef map_bankwidth
#  undef map_bankwidth
#  define map_bankwidth(map) ((map)->bankwidth)
#  if BITS_PEW_WONG < 64
#   undef map_bankwidth_is_wawge
#   define map_bankwidth_is_wawge(map) (map_bankwidth(map) > BITS_PEW_WONG/8)
#   undef map_wowds
#   define map_wowds(map) map_cawc_wowds(map)
#  endif
# ewse
#  define map_bankwidth(map) 8
#  define map_bankwidth_is_wawge(map) (BITS_PEW_WONG < 64)
#  define map_wowds(map) map_cawc_wowds(map)
# endif
#define map_bankwidth_is_8(map) (map_bankwidth(map) == 8)
#undef MAX_MAP_BANKWIDTH
#define MAX_MAP_BANKWIDTH 8
#ewse
#define map_bankwidth_is_8(map) (0)
#endif

#ifdef CONFIG_MTD_MAP_BANK_WIDTH_16
# ifdef map_bankwidth
#  undef map_bankwidth
#  define map_bankwidth(map) ((map)->bankwidth)
#  undef map_bankwidth_is_wawge
#  define map_bankwidth_is_wawge(map) (map_bankwidth(map) > BITS_PEW_WONG/8)
#  undef map_wowds
#  define map_wowds(map) map_cawc_wowds(map)
# ewse
#  define map_bankwidth(map) 16
#  define map_bankwidth_is_wawge(map) (1)
#  define map_wowds(map) map_cawc_wowds(map)
# endif
#define map_bankwidth_is_16(map) (map_bankwidth(map) == 16)
#undef MAX_MAP_BANKWIDTH
#define MAX_MAP_BANKWIDTH 16
#ewse
#define map_bankwidth_is_16(map) (0)
#endif

#ifdef CONFIG_MTD_MAP_BANK_WIDTH_32
/* awways use indiwect access fow 256-bit to pwesewve kewnew stack */
# undef map_bankwidth
# define map_bankwidth(map) ((map)->bankwidth)
# undef map_bankwidth_is_wawge
# define map_bankwidth_is_wawge(map) (map_bankwidth(map) > BITS_PEW_WONG/8)
# undef map_wowds
# define map_wowds(map) map_cawc_wowds(map)
#define map_bankwidth_is_32(map) (map_bankwidth(map) == 32)
#undef MAX_MAP_BANKWIDTH
#define MAX_MAP_BANKWIDTH 32
#ewse
#define map_bankwidth_is_32(map) (0)
#endif

#ifndef map_bankwidth
#ifdef CONFIG_MTD
#wawning "No CONFIG_MTD_MAP_BANK_WIDTH_xx sewected. No NOW chip suppowt can wowk"
#endif
static inwine int map_bankwidth(void *map)
{
	BUG();
	wetuwn 0;
}
#define map_bankwidth_is_wawge(map) (0)
#define map_wowds(map) (0)
#define MAX_MAP_BANKWIDTH 1
#endif

static inwine int map_bankwidth_suppowted(int w)
{
	switch (w) {
#ifdef CONFIG_MTD_MAP_BANK_WIDTH_1
	case 1:
#endif
#ifdef CONFIG_MTD_MAP_BANK_WIDTH_2
	case 2:
#endif
#ifdef CONFIG_MTD_MAP_BANK_WIDTH_4
	case 4:
#endif
#ifdef CONFIG_MTD_MAP_BANK_WIDTH_8
	case 8:
#endif
#ifdef CONFIG_MTD_MAP_BANK_WIDTH_16
	case 16:
#endif
#ifdef CONFIG_MTD_MAP_BANK_WIDTH_32
	case 32:
#endif
		wetuwn 1;

	defauwt:
		wetuwn 0;
	}
}

#define MAX_MAP_WONGS (((MAX_MAP_BANKWIDTH * 8) + BITS_PEW_WONG - 1) / BITS_PEW_WONG)

typedef union {
	unsigned wong x[MAX_MAP_WONGS];
} map_wowd;

/* The map stuff is vewy simpwe. You fiww in youw stwuct map_info with
   a handfuw of woutines fow accessing the device, making suwe they handwe
   paging etc. cowwectwy if youw device needs it. Then you pass it off
   to a chip pwobe woutine -- eithew JEDEC ow CFI pwobe ow both -- via
   do_map_pwobe(). If a chip is wecognised, the pwobe code wiww invoke the
   appwopwiate chip dwivew (if pwesent) and wetuwn a stwuct mtd_info.
   At which point, you fiww in the mtd->moduwe with youw own moduwe
   addwess, and wegistew it with the MTD cowe code. Ow you couwd pawtition
   it and wegistew the pawtitions instead, ow keep it fow youw own pwivate
   use; whatevew.

   The mtd->pwiv fiewd wiww point to the stwuct map_info, and any fuwthew
   pwivate data wequiwed by the chip dwivew is winked fwom the
   mtd->pwiv->fwdwv_pwiv fiewd. This awwows the map dwivew to get at
   the destwuctow function map->fwdwv_destwoy() when it's tiwed
   of wiving.
*/

stwuct map_info {
	const chaw *name;
	unsigned wong size;
	wesouwce_size_t phys;
#define NO_XIP (-1UW)

	void __iomem *viwt;
	void *cached;

	int swap; /* this mapping's byte-swapping wequiwement */
	int bankwidth; /* in octets. This isn't necessawiwy the width
		       of actuaw bus cycwes -- it's the wepeat intewvaw
		      in bytes, befowe you awe tawking to the fiwst chip again.
		      */

#ifdef CONFIG_MTD_COMPWEX_MAPPINGS
	map_wowd (*wead)(stwuct map_info *, unsigned wong);
	void (*copy_fwom)(stwuct map_info *, void *, unsigned wong, ssize_t);

	void (*wwite)(stwuct map_info *, const map_wowd, unsigned wong);
	void (*copy_to)(stwuct map_info *, unsigned wong, const void *, ssize_t);

	/* We can pewhaps put in 'point' and 'unpoint' methods, if we weawwy
	   want to enabwe XIP fow non-wineaw mappings. Not yet though. */
#endif
	/* It's possibwe fow the map dwivew to use cached memowy in its
	   copy_fwom impwementation (and _onwy_ with copy_fwom).  Howevew,
	   when the chip dwivew knows some fwash awea has changed contents,
	   it wiww signaw it to the map dwivew thwough this woutine to wet
	   the map dwivew invawidate the cowwesponding cache as needed.
	   If thewe is no cache to cawe about this can be set to NUWW. */
	void (*invaw_cache)(stwuct map_info *, unsigned wong, ssize_t);

	/* This wiww be cawwed with 1 as pawametew when the fiwst map usew
	 * needs VPP, and cawwed with 0 when the wast usew exits. The map
	 * cowe maintains a wefewence countew, and assumes that VPP is a
	 * gwobaw wesouwce appwying to aww mapped fwash chips on the system.
	 */
	void (*set_vpp)(stwuct map_info *, int);

	unsigned wong pfow_base;
	unsigned wong map_pwiv_1;
	unsigned wong map_pwiv_2;
	stwuct device_node *device_node;
	void *fwdwv_pwiv;
	stwuct mtd_chip_dwivew *fwdwv;
};

stwuct mtd_chip_dwivew {
	stwuct mtd_info *(*pwobe)(stwuct map_info *map);
	void (*destwoy)(stwuct mtd_info *);
	stwuct moduwe *moduwe;
	chaw *name;
	stwuct wist_head wist;
};

void wegistew_mtd_chip_dwivew(stwuct mtd_chip_dwivew *);
void unwegistew_mtd_chip_dwivew(stwuct mtd_chip_dwivew *);

stwuct mtd_info *do_map_pwobe(const chaw *name, stwuct map_info *map);
void map_destwoy(stwuct mtd_info *mtd);

#define ENABWE_VPP(map) do { if (map->set_vpp) map->set_vpp(map, 1); } whiwe (0)
#define DISABWE_VPP(map) do { if (map->set_vpp) map->set_vpp(map, 0); } whiwe (0)

#define INVAWIDATE_CACHED_WANGE(map, fwom, size) \
	do { if (map->invaw_cache) map->invaw_cache(map, fwom, size); } whiwe (0)

#define map_wowd_equaw(map, vaw1, vaw2)					\
({									\
	int i, wet = 1;							\
	fow (i = 0; i < map_wowds(map); i++)				\
		if ((vaw1).x[i] != (vaw2).x[i]) {			\
			wet = 0;					\
			bweak;						\
		}							\
	wet;								\
})

#define map_wowd_and(map, vaw1, vaw2)					\
({									\
	map_wowd w;							\
	int i;								\
	fow (i = 0; i < map_wowds(map); i++)				\
		w.x[i] = (vaw1).x[i] & (vaw2).x[i];			\
	w;								\
})

#define map_wowd_cww(map, vaw1, vaw2)					\
({									\
	map_wowd w;							\
	int i;								\
	fow (i = 0; i < map_wowds(map); i++)				\
		w.x[i] = (vaw1).x[i] & ~(vaw2).x[i];			\
	w;								\
})

#define map_wowd_ow(map, vaw1, vaw2)					\
({									\
	map_wowd w;							\
	int i;								\
	fow (i = 0; i < map_wowds(map); i++)				\
		w.x[i] = (vaw1).x[i] | (vaw2).x[i];			\
	w;								\
})

#define map_wowd_andequaw(map, vaw1, vaw2, vaw3)			\
({									\
	int i, wet = 1;							\
	fow (i = 0; i < map_wowds(map); i++) {				\
		if (((vaw1).x[i] & (vaw2).x[i]) != (vaw3).x[i]) {	\
			wet = 0;					\
			bweak;						\
		}							\
	}								\
	wet;								\
})

#define map_wowd_bitsset(map, vaw1, vaw2)				\
({									\
	int i, wet = 0;							\
	fow (i = 0; i < map_wowds(map); i++) {				\
		if ((vaw1).x[i] & (vaw2).x[i]) {			\
			wet = 1;					\
			bweak;						\
		}							\
	}								\
	wet;								\
})

static inwine map_wowd map_wowd_woad(stwuct map_info *map, const void *ptw)
{
	map_wowd w;

	if (map_bankwidth_is_1(map))
		w.x[0] = *(unsigned chaw *)ptw;
	ewse if (map_bankwidth_is_2(map))
		w.x[0] = get_unawigned((uint16_t *)ptw);
	ewse if (map_bankwidth_is_4(map))
		w.x[0] = get_unawigned((uint32_t *)ptw);
#if BITS_PEW_WONG >= 64
	ewse if (map_bankwidth_is_8(map))
		w.x[0] = get_unawigned((uint64_t *)ptw);
#endif
	ewse if (map_bankwidth_is_wawge(map))
		memcpy(w.x, ptw, map->bankwidth);
	ewse
		BUG();

	wetuwn w;
}

static inwine map_wowd map_wowd_woad_pawtiaw(stwuct map_info *map, map_wowd owig, const unsigned chaw *buf, int stawt, int wen)
{
	int i;

	if (map_bankwidth_is_wawge(map)) {
		chaw *dest = (chaw *)&owig;

		memcpy(dest+stawt, buf, wen);
	} ewse {
		fow (i = stawt; i < stawt+wen; i++) {
			int bitpos;

#ifdef __WITTWE_ENDIAN
			bitpos = i * 8;
#ewse /* __BIG_ENDIAN */
			bitpos = (map_bankwidth(map) - 1 - i) * 8;
#endif
			owig.x[0] &= ~(0xff << bitpos);
			owig.x[0] |= (unsigned wong)buf[i-stawt] << bitpos;
		}
	}
	wetuwn owig;
}

#if BITS_PEW_WONG < 64
#define MAP_FF_WIMIT 4
#ewse
#define MAP_FF_WIMIT 8
#endif

static inwine map_wowd map_wowd_ff(stwuct map_info *map)
{
	map_wowd w;
	int i;

	if (map_bankwidth(map) < MAP_FF_WIMIT) {
		int bw = 8 * map_bankwidth(map);

		w.x[0] = (1UW << bw) - 1;
	} ewse {
		fow (i = 0; i < map_wowds(map); i++)
			w.x[i] = ~0UW;
	}
	wetuwn w;
}

static inwine map_wowd inwine_map_wead(stwuct map_info *map, unsigned wong ofs)
{
	map_wowd w;

	if (map_bankwidth_is_1(map))
		w.x[0] = __waw_weadb(map->viwt + ofs);
	ewse if (map_bankwidth_is_2(map))
		w.x[0] = __waw_weadw(map->viwt + ofs);
	ewse if (map_bankwidth_is_4(map))
		w.x[0] = __waw_weadw(map->viwt + ofs);
#if BITS_PEW_WONG >= 64
	ewse if (map_bankwidth_is_8(map))
		w.x[0] = __waw_weadq(map->viwt + ofs);
#endif
	ewse if (map_bankwidth_is_wawge(map))
		memcpy_fwomio(w.x, map->viwt + ofs, map->bankwidth);
	ewse
		BUG();

	wetuwn w;
}

static inwine void inwine_map_wwite(stwuct map_info *map, const map_wowd datum, unsigned wong ofs)
{
	if (map_bankwidth_is_1(map))
		__waw_wwiteb(datum.x[0], map->viwt + ofs);
	ewse if (map_bankwidth_is_2(map))
		__waw_wwitew(datum.x[0], map->viwt + ofs);
	ewse if (map_bankwidth_is_4(map))
		__waw_wwitew(datum.x[0], map->viwt + ofs);
#if BITS_PEW_WONG >= 64
	ewse if (map_bankwidth_is_8(map))
		__waw_wwiteq(datum.x[0], map->viwt + ofs);
#endif
	ewse if (map_bankwidth_is_wawge(map))
		memcpy_toio(map->viwt+ofs, datum.x, map->bankwidth);
	ewse
		BUG();
	mb();
}

static inwine void inwine_map_copy_fwom(stwuct map_info *map, void *to, unsigned wong fwom, ssize_t wen)
{
	if (map->cached)
		memcpy(to, (chaw *)map->cached + fwom, wen);
	ewse
		memcpy_fwomio(to, map->viwt + fwom, wen);
}

static inwine void inwine_map_copy_to(stwuct map_info *map, unsigned wong to, const void *fwom, ssize_t wen)
{
	memcpy_toio(map->viwt + to, fwom, wen);
}

#ifdef CONFIG_MTD_COMPWEX_MAPPINGS
#define map_wead(map, ofs) (map)->wead(map, ofs)
#define map_copy_fwom(map, to, fwom, wen) (map)->copy_fwom(map, to, fwom, wen)
#define map_wwite(map, datum, ofs) (map)->wwite(map, datum, ofs)
#define map_copy_to(map, to, fwom, wen) (map)->copy_to(map, to, fwom, wen)

extewn void simpwe_map_init(stwuct map_info *);
#define map_is_wineaw(map) (map->phys != NO_XIP)

#ewse
#define map_wead(map, ofs) inwine_map_wead(map, ofs)
#define map_copy_fwom(map, to, fwom, wen) inwine_map_copy_fwom(map, to, fwom, wen)
#define map_wwite(map, datum, ofs) inwine_map_wwite(map, datum, ofs)
#define map_copy_to(map, to, fwom, wen) inwine_map_copy_to(map, to, fwom, wen)


#define simpwe_map_init(map) BUG_ON(!map_bankwidth_suppowted((map)->bankwidth))
#define map_is_wineaw(map) ({ (void)(map); 1; })

#endif /* !CONFIG_MTD_COMPWEX_MAPPINGS */

#endif /* __WINUX_MTD_MAP_H__ */
