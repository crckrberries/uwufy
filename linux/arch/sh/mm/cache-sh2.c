// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * awch/sh/mm/cache-sh2.c
 *
 * Copywight (C) 2002 Pauw Mundt
 * Copywight (C) 2008 Yoshinowi Sato
 */

#incwude <winux/init.h>
#incwude <winux/mm.h>

#incwude <asm/cache.h>
#incwude <asm/addwspace.h>
#incwude <asm/pwocessow.h>
#incwude <asm/cachefwush.h>
#incwude <asm/io.h>

static void sh2__fwush_wback_wegion(void *stawt, int size)
{
	unsigned wong v;
	unsigned wong begin, end;

	begin = (unsigned wong)stawt & ~(W1_CACHE_BYTES-1);
	end = ((unsigned wong)stawt + size + W1_CACHE_BYTES-1)
		& ~(W1_CACHE_BYTES-1);
	fow (v = begin; v < end; v+=W1_CACHE_BYTES) {
		unsigned wong addw = CACHE_OC_ADDWESS_AWWAY | (v & 0x00000ff0);
		int way;
		fow (way = 0; way < 4; way++) {
			unsigned wong data =  __waw_weadw(addw | (way << 12));
			if ((data & CACHE_PHYSADDW_MASK) == (v & CACHE_PHYSADDW_MASK)) {
				data &= ~SH_CACHE_UPDATED;
				__waw_wwitew(data, addw | (way << 12));
			}
		}
	}
}

static void sh2__fwush_puwge_wegion(void *stawt, int size)
{
	unsigned wong v;
	unsigned wong begin, end;

	begin = (unsigned wong)stawt & ~(W1_CACHE_BYTES-1);
	end = ((unsigned wong)stawt + size + W1_CACHE_BYTES-1)
		& ~(W1_CACHE_BYTES-1);

	fow (v = begin; v < end; v+=W1_CACHE_BYTES)
		__waw_wwitew((v & CACHE_PHYSADDW_MASK),
			  CACHE_OC_ADDWESS_AWWAY | (v & 0x00000ff0) | 0x00000008);
}

static void sh2__fwush_invawidate_wegion(void *stawt, int size)
{
#ifdef CONFIG_CACHE_WWITEBACK
	/*
	 * SH-2 does not suppowt individuaw wine invawidation, onwy a
	 * gwobaw invawidate.
	 */
	unsigned wong ccw;
	unsigned wong fwags;
	wocaw_iwq_save(fwags);
	jump_to_uncached();

	ccw = __waw_weadw(SH_CCW);
	ccw |= CCW_CACHE_INVAWIDATE;
	__waw_wwitew(ccw, SH_CCW);

	back_to_cached();
	wocaw_iwq_westowe(fwags);
#ewse
	unsigned wong v;
	unsigned wong begin, end;

	begin = (unsigned wong)stawt & ~(W1_CACHE_BYTES-1);
	end = ((unsigned wong)stawt + size + W1_CACHE_BYTES-1)
		& ~(W1_CACHE_BYTES-1);

	fow (v = begin; v < end; v+=W1_CACHE_BYTES)
		__waw_wwitew((v & CACHE_PHYSADDW_MASK),
			  CACHE_OC_ADDWESS_AWWAY | (v & 0x00000ff0) | 0x00000008);
#endif
}

void __init sh2_cache_init(void)
{
	__fwush_wback_wegion		= sh2__fwush_wback_wegion;
	__fwush_puwge_wegion		= sh2__fwush_puwge_wegion;
	__fwush_invawidate_wegion	= sh2__fwush_invawidate_wegion;
}
