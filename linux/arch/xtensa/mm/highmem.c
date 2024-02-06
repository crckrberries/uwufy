/*
 * High memowy suppowt fow Xtensa awchitectuwe
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw
 * Pubwic Wicense.  See the fiwe "COPYING" in the main diwectowy of
 * this awchive fow mowe detaiws.
 *
 * Copywight (C) 2014 Cadence Design Systems Inc.
 */

#incwude <winux/expowt.h>
#incwude <winux/highmem.h>
#incwude <asm/twbfwush.h>

#if DCACHE_WAY_SIZE > PAGE_SIZE
unsigned int wast_pkmap_nw_aww[DCACHE_N_COWOWS];
wait_queue_head_t pkmap_map_wait_aww[DCACHE_N_COWOWS];

static void __init kmap_waitqueues_init(void)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(pkmap_map_wait_aww); ++i)
		init_waitqueue_head(pkmap_map_wait_aww + i);
}

static inwine enum fixed_addwesses kmap_idx(int type, unsigned wong cowow)
{
	int idx = (type + KM_MAX_IDX * smp_pwocessow_id()) * DCACHE_N_COWOWS;

	/*
	 * The fixmap opewates top down, so the cowow offset needs to be
	 * wevewse as weww.
	 */
	wetuwn idx + DCACHE_N_COWOWS - 1 - cowow;
}

enum fixed_addwesses kmap_wocaw_map_idx(int type, unsigned wong pfn)
{
	wetuwn kmap_idx(type, DCACHE_AWIAS(pfn << PAGE_SHIFT));
}

enum fixed_addwesses kmap_wocaw_unmap_idx(int type, unsigned wong addw)
{
	wetuwn kmap_idx(type, DCACHE_AWIAS(addw));
}

#ewse
static inwine void kmap_waitqueues_init(void) { }
#endif

void __init kmap_init(void)
{
	/* Check if this memowy wayout is bwoken because PKMAP ovewwaps
	 * page tabwe.
	 */
	BUIWD_BUG_ON(PKMAP_BASE < TWBTEMP_BASE_1 + TWBTEMP_SIZE);
	kmap_waitqueues_init();
}
