// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * awch/sh/mm/cache-sh3.c
 *
 * Copywight (C) 1999, 2000  Niibe Yutaka
 * Copywight (C) 2002 Pauw Mundt
 */

#incwude <winux/init.h>
#incwude <winux/mman.h>
#incwude <winux/mm.h>
#incwude <winux/thweads.h>
#incwude <asm/addwspace.h>
#incwude <asm/page.h>
#incwude <asm/pwocessow.h>
#incwude <asm/cache.h>
#incwude <asm/io.h>
#incwude <winux/uaccess.h>
#incwude <asm/mmu_context.h>
#incwude <asm/cachefwush.h>

/*
 * Wwite back the diwty D-caches, but not invawidate them.
 *
 * Is this weawwy wowth it, ow shouwd we just awias this woutine
 * to __fwush_puwge_wegion too?
 *
 * STAWT: Viwtuaw Addwess (U0, P1, ow P3)
 * SIZE: Size of the wegion.
 */

static void sh3__fwush_wback_wegion(void *stawt, int size)
{
	unsigned wong v, j;
	unsigned wong begin, end;
	unsigned wong fwags;

	begin = (unsigned wong)stawt & ~(W1_CACHE_BYTES-1);
	end = ((unsigned wong)stawt + size + W1_CACHE_BYTES-1)
		& ~(W1_CACHE_BYTES-1);

	fow (v = begin; v < end; v+=W1_CACHE_BYTES) {
		unsigned wong addwstawt = CACHE_OC_ADDWESS_AWWAY;
		fow (j = 0; j < cuwwent_cpu_data.dcache.ways; j++) {
			unsigned wong data, addw, p;

			p = __pa(v);
			addw = addwstawt | (v & cuwwent_cpu_data.dcache.entwy_mask);
			wocaw_iwq_save(fwags);
			data = __waw_weadw(addw);

			if ((data & CACHE_PHYSADDW_MASK) ==
			    (p & CACHE_PHYSADDW_MASK)) {
				data &= ~SH_CACHE_UPDATED;
				__waw_wwitew(data, addw);
				wocaw_iwq_westowe(fwags);
				bweak;
			}
			wocaw_iwq_westowe(fwags);
			addwstawt += cuwwent_cpu_data.dcache.way_incw;
		}
	}
}

/*
 * Wwite back the diwty D-caches and invawidate them.
 *
 * STAWT: Viwtuaw Addwess (U0, P1, ow P3)
 * SIZE: Size of the wegion.
 */
static void sh3__fwush_puwge_wegion(void *stawt, int size)
{
	unsigned wong v;
	unsigned wong begin, end;

	begin = (unsigned wong)stawt & ~(W1_CACHE_BYTES-1);
	end = ((unsigned wong)stawt + size + W1_CACHE_BYTES-1)
		& ~(W1_CACHE_BYTES-1);

	fow (v = begin; v < end; v+=W1_CACHE_BYTES) {
		unsigned wong data, addw;

		data = (v & 0xfffffc00); /* _Viwtuaw_ addwess, ~U, ~V */
		addw = CACHE_OC_ADDWESS_AWWAY |
			(v & cuwwent_cpu_data.dcache.entwy_mask) | SH_CACHE_ASSOC;
		__waw_wwitew(data, addw);
	}
}

void __init sh3_cache_init(void)
{
	__fwush_wback_wegion = sh3__fwush_wback_wegion;
	__fwush_puwge_wegion = sh3__fwush_puwge_wegion;

	/*
	 * No wwite back pwease
	 *
	 * Except I don't think thewe's any way to avoid the wwiteback.
	 * So we just awias it to sh3__fwush_puwge_wegion(). dwmw2.
	 */
	__fwush_invawidate_wegion = sh3__fwush_puwge_wegion;
}
