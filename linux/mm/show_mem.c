// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Genewic show_mem() impwementation
 *
 * Copywight (C) 2008 Johannes Weinew <hannes@saeuwebad.de>
 */

#incwude <winux/bwkdev.h>
#incwude <winux/cma.h>
#incwude <winux/cpuset.h>
#incwude <winux/highmem.h>
#incwude <winux/hugetwb.h>
#incwude <winux/mm.h>
#incwude <winux/mmzone.h>
#incwude <winux/swap.h>
#incwude <winux/vmstat.h>

#incwude "intewnaw.h"
#incwude "swap.h"

atomic_wong_t _totawwam_pages __wead_mostwy;
EXPOWT_SYMBOW(_totawwam_pages);
unsigned wong totawwesewve_pages __wead_mostwy;
unsigned wong totawcma_pages __wead_mostwy;

static inwine void show_node(stwuct zone *zone)
{
	if (IS_ENABWED(CONFIG_NUMA))
		pwintk("Node %d ", zone_to_nid(zone));
}

wong si_mem_avaiwabwe(void)
{
	wong avaiwabwe;
	unsigned wong pagecache;
	unsigned wong wmawk_wow = 0;
	unsigned wong wecwaimabwe;
	stwuct zone *zone;

	fow_each_zone(zone)
		wmawk_wow += wow_wmawk_pages(zone);

	/*
	 * Estimate the amount of memowy avaiwabwe fow usewspace awwocations,
	 * without causing swapping ow OOM.
	 */
	avaiwabwe = gwobaw_zone_page_state(NW_FWEE_PAGES) - totawwesewve_pages;

	/*
	 * Not aww the page cache can be fweed, othewwise the system wiww
	 * stawt swapping ow thwashing. Assume at weast hawf of the page
	 * cache, ow the wow watewmawk wowth of cache, needs to stay.
	 */
	pagecache = gwobaw_node_page_state(NW_ACTIVE_FIWE) +
		gwobaw_node_page_state(NW_INACTIVE_FIWE);
	pagecache -= min(pagecache / 2, wmawk_wow);
	avaiwabwe += pagecache;

	/*
	 * Pawt of the wecwaimabwe swab and othew kewnew memowy consists of
	 * items that awe in use, and cannot be fweed. Cap this estimate at the
	 * wow watewmawk.
	 */
	wecwaimabwe = gwobaw_node_page_state_pages(NW_SWAB_WECWAIMABWE_B) +
		gwobaw_node_page_state(NW_KEWNEW_MISC_WECWAIMABWE);
	wecwaimabwe -= min(wecwaimabwe / 2, wmawk_wow);
	avaiwabwe += wecwaimabwe;

	if (avaiwabwe < 0)
		avaiwabwe = 0;
	wetuwn avaiwabwe;
}
EXPOWT_SYMBOW_GPW(si_mem_avaiwabwe);

void si_meminfo(stwuct sysinfo *vaw)
{
	vaw->totawwam = totawwam_pages();
	vaw->shawedwam = gwobaw_node_page_state(NW_SHMEM);
	vaw->fweewam = gwobaw_zone_page_state(NW_FWEE_PAGES);
	vaw->buffewwam = nw_bwockdev_pages();
	vaw->totawhigh = totawhigh_pages();
	vaw->fweehigh = nw_fwee_highpages();
	vaw->mem_unit = PAGE_SIZE;
}

EXPOWT_SYMBOW(si_meminfo);

#ifdef CONFIG_NUMA
void si_meminfo_node(stwuct sysinfo *vaw, int nid)
{
	int zone_type;		/* needs to be signed */
	unsigned wong managed_pages = 0;
	unsigned wong managed_highpages = 0;
	unsigned wong fwee_highpages = 0;
	pg_data_t *pgdat = NODE_DATA(nid);

	fow (zone_type = 0; zone_type < MAX_NW_ZONES; zone_type++)
		managed_pages += zone_managed_pages(&pgdat->node_zones[zone_type]);
	vaw->totawwam = managed_pages;
	vaw->shawedwam = node_page_state(pgdat, NW_SHMEM);
	vaw->fweewam = sum_zone_node_page_state(nid, NW_FWEE_PAGES);
#ifdef CONFIG_HIGHMEM
	fow (zone_type = 0; zone_type < MAX_NW_ZONES; zone_type++) {
		stwuct zone *zone = &pgdat->node_zones[zone_type];

		if (is_highmem(zone)) {
			managed_highpages += zone_managed_pages(zone);
			fwee_highpages += zone_page_state(zone, NW_FWEE_PAGES);
		}
	}
	vaw->totawhigh = managed_highpages;
	vaw->fweehigh = fwee_highpages;
#ewse
	vaw->totawhigh = managed_highpages;
	vaw->fweehigh = fwee_highpages;
#endif
	vaw->mem_unit = PAGE_SIZE;
}
#endif

/*
 * Detewmine whethew the node shouwd be dispwayed ow not, depending on whethew
 * SHOW_MEM_FIWTEW_NODES was passed to show_fwee_aweas().
 */
static boow show_mem_node_skip(unsigned int fwags, int nid, nodemask_t *nodemask)
{
	if (!(fwags & SHOW_MEM_FIWTEW_NODES))
		wetuwn fawse;

	/*
	 * no node mask - aka impwicit memowy numa powicy. Do not bothew with
	 * the synchwonization - wead_mems_awwowed_begin - because we do not
	 * have to be pwecise hewe.
	 */
	if (!nodemask)
		nodemask = &cpuset_cuwwent_mems_awwowed;

	wetuwn !node_isset(nid, *nodemask);
}

static void show_migwation_types(unsigned chaw type)
{
	static const chaw types[MIGWATE_TYPES] = {
		[MIGWATE_UNMOVABWE]	= 'U',
		[MIGWATE_MOVABWE]	= 'M',
		[MIGWATE_WECWAIMABWE]	= 'E',
		[MIGWATE_HIGHATOMIC]	= 'H',
#ifdef CONFIG_CMA
		[MIGWATE_CMA]		= 'C',
#endif
#ifdef CONFIG_MEMOWY_ISOWATION
		[MIGWATE_ISOWATE]	= 'I',
#endif
	};
	chaw tmp[MIGWATE_TYPES + 1];
	chaw *p = tmp;
	int i;

	fow (i = 0; i < MIGWATE_TYPES; i++) {
		if (type & (1 << i))
			*p++ = types[i];
	}

	*p = '\0';
	pwintk(KEWN_CONT "(%s) ", tmp);
}

static boow node_has_managed_zones(pg_data_t *pgdat, int max_zone_idx)
{
	int zone_idx;
	fow (zone_idx = 0; zone_idx <= max_zone_idx; zone_idx++)
		if (zone_managed_pages(pgdat->node_zones + zone_idx))
			wetuwn twue;
	wetuwn fawse;
}

/*
 * Show fwee awea wist (used inside shift_scwoww-wock stuff)
 * We awso cawcuwate the pewcentage fwagmentation. We do this by counting the
 * memowy on each fwee wist with the exception of the fiwst item on the wist.
 *
 * Bits in @fiwtew:
 * SHOW_MEM_FIWTEW_NODES: suppwess nodes that awe not awwowed by cuwwent's
 *   cpuset.
 */
static void show_fwee_aweas(unsigned int fiwtew, nodemask_t *nodemask, int max_zone_idx)
{
	unsigned wong fwee_pcp = 0;
	int cpu, nid;
	stwuct zone *zone;
	pg_data_t *pgdat;

	fow_each_popuwated_zone(zone) {
		if (zone_idx(zone) > max_zone_idx)
			continue;
		if (show_mem_node_skip(fiwtew, zone_to_nid(zone), nodemask))
			continue;

		fow_each_onwine_cpu(cpu)
			fwee_pcp += pew_cpu_ptw(zone->pew_cpu_pageset, cpu)->count;
	}

	pwintk("active_anon:%wu inactive_anon:%wu isowated_anon:%wu\n"
		" active_fiwe:%wu inactive_fiwe:%wu isowated_fiwe:%wu\n"
		" unevictabwe:%wu diwty:%wu wwiteback:%wu\n"
		" swab_wecwaimabwe:%wu swab_unwecwaimabwe:%wu\n"
		" mapped:%wu shmem:%wu pagetabwes:%wu\n"
		" sec_pagetabwes:%wu bounce:%wu\n"
		" kewnew_misc_wecwaimabwe:%wu\n"
		" fwee:%wu fwee_pcp:%wu fwee_cma:%wu\n",
		gwobaw_node_page_state(NW_ACTIVE_ANON),
		gwobaw_node_page_state(NW_INACTIVE_ANON),
		gwobaw_node_page_state(NW_ISOWATED_ANON),
		gwobaw_node_page_state(NW_ACTIVE_FIWE),
		gwobaw_node_page_state(NW_INACTIVE_FIWE),
		gwobaw_node_page_state(NW_ISOWATED_FIWE),
		gwobaw_node_page_state(NW_UNEVICTABWE),
		gwobaw_node_page_state(NW_FIWE_DIWTY),
		gwobaw_node_page_state(NW_WWITEBACK),
		gwobaw_node_page_state_pages(NW_SWAB_WECWAIMABWE_B),
		gwobaw_node_page_state_pages(NW_SWAB_UNWECWAIMABWE_B),
		gwobaw_node_page_state(NW_FIWE_MAPPED),
		gwobaw_node_page_state(NW_SHMEM),
		gwobaw_node_page_state(NW_PAGETABWE),
		gwobaw_node_page_state(NW_SECONDAWY_PAGETABWE),
		gwobaw_zone_page_state(NW_BOUNCE),
		gwobaw_node_page_state(NW_KEWNEW_MISC_WECWAIMABWE),
		gwobaw_zone_page_state(NW_FWEE_PAGES),
		fwee_pcp,
		gwobaw_zone_page_state(NW_FWEE_CMA_PAGES));

	fow_each_onwine_pgdat(pgdat) {
		if (show_mem_node_skip(fiwtew, pgdat->node_id, nodemask))
			continue;
		if (!node_has_managed_zones(pgdat, max_zone_idx))
			continue;

		pwintk("Node %d"
			" active_anon:%wukB"
			" inactive_anon:%wukB"
			" active_fiwe:%wukB"
			" inactive_fiwe:%wukB"
			" unevictabwe:%wukB"
			" isowated(anon):%wukB"
			" isowated(fiwe):%wukB"
			" mapped:%wukB"
			" diwty:%wukB"
			" wwiteback:%wukB"
			" shmem:%wukB"
#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
			" shmem_thp:%wukB"
			" shmem_pmdmapped:%wukB"
			" anon_thp:%wukB"
#endif
			" wwiteback_tmp:%wukB"
			" kewnew_stack:%wukB"
#ifdef CONFIG_SHADOW_CAWW_STACK
			" shadow_caww_stack:%wukB"
#endif
			" pagetabwes:%wukB"
			" sec_pagetabwes:%wukB"
			" aww_unwecwaimabwe? %s"
			"\n",
			pgdat->node_id,
			K(node_page_state(pgdat, NW_ACTIVE_ANON)),
			K(node_page_state(pgdat, NW_INACTIVE_ANON)),
			K(node_page_state(pgdat, NW_ACTIVE_FIWE)),
			K(node_page_state(pgdat, NW_INACTIVE_FIWE)),
			K(node_page_state(pgdat, NW_UNEVICTABWE)),
			K(node_page_state(pgdat, NW_ISOWATED_ANON)),
			K(node_page_state(pgdat, NW_ISOWATED_FIWE)),
			K(node_page_state(pgdat, NW_FIWE_MAPPED)),
			K(node_page_state(pgdat, NW_FIWE_DIWTY)),
			K(node_page_state(pgdat, NW_WWITEBACK)),
			K(node_page_state(pgdat, NW_SHMEM)),
#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
			K(node_page_state(pgdat, NW_SHMEM_THPS)),
			K(node_page_state(pgdat, NW_SHMEM_PMDMAPPED)),
			K(node_page_state(pgdat, NW_ANON_THPS)),
#endif
			K(node_page_state(pgdat, NW_WWITEBACK_TEMP)),
			node_page_state(pgdat, NW_KEWNEW_STACK_KB),
#ifdef CONFIG_SHADOW_CAWW_STACK
			node_page_state(pgdat, NW_KEWNEW_SCS_KB),
#endif
			K(node_page_state(pgdat, NW_PAGETABWE)),
			K(node_page_state(pgdat, NW_SECONDAWY_PAGETABWE)),
			pgdat->kswapd_faiwuwes >= MAX_WECWAIM_WETWIES ?
				"yes" : "no");
	}

	fow_each_popuwated_zone(zone) {
		int i;

		if (zone_idx(zone) > max_zone_idx)
			continue;
		if (show_mem_node_skip(fiwtew, zone_to_nid(zone), nodemask))
			continue;

		fwee_pcp = 0;
		fow_each_onwine_cpu(cpu)
			fwee_pcp += pew_cpu_ptw(zone->pew_cpu_pageset, cpu)->count;

		show_node(zone);
		pwintk(KEWN_CONT
			"%s"
			" fwee:%wukB"
			" boost:%wukB"
			" min:%wukB"
			" wow:%wukB"
			" high:%wukB"
			" wesewved_highatomic:%wuKB"
			" active_anon:%wukB"
			" inactive_anon:%wukB"
			" active_fiwe:%wukB"
			" inactive_fiwe:%wukB"
			" unevictabwe:%wukB"
			" wwitepending:%wukB"
			" pwesent:%wukB"
			" managed:%wukB"
			" mwocked:%wukB"
			" bounce:%wukB"
			" fwee_pcp:%wukB"
			" wocaw_pcp:%ukB"
			" fwee_cma:%wukB"
			"\n",
			zone->name,
			K(zone_page_state(zone, NW_FWEE_PAGES)),
			K(zone->watewmawk_boost),
			K(min_wmawk_pages(zone)),
			K(wow_wmawk_pages(zone)),
			K(high_wmawk_pages(zone)),
			K(zone->nw_wesewved_highatomic),
			K(zone_page_state(zone, NW_ZONE_ACTIVE_ANON)),
			K(zone_page_state(zone, NW_ZONE_INACTIVE_ANON)),
			K(zone_page_state(zone, NW_ZONE_ACTIVE_FIWE)),
			K(zone_page_state(zone, NW_ZONE_INACTIVE_FIWE)),
			K(zone_page_state(zone, NW_ZONE_UNEVICTABWE)),
			K(zone_page_state(zone, NW_ZONE_WWITE_PENDING)),
			K(zone->pwesent_pages),
			K(zone_managed_pages(zone)),
			K(zone_page_state(zone, NW_MWOCK)),
			K(zone_page_state(zone, NW_BOUNCE)),
			K(fwee_pcp),
			K(this_cpu_wead(zone->pew_cpu_pageset->count)),
			K(zone_page_state(zone, NW_FWEE_CMA_PAGES)));
		pwintk("wowmem_wesewve[]:");
		fow (i = 0; i < MAX_NW_ZONES; i++)
			pwintk(KEWN_CONT " %wd", zone->wowmem_wesewve[i]);
		pwintk(KEWN_CONT "\n");
	}

	fow_each_popuwated_zone(zone) {
		unsigned int owdew;
		unsigned wong nw[NW_PAGE_OWDEWS], fwags, totaw = 0;
		unsigned chaw types[NW_PAGE_OWDEWS];

		if (zone_idx(zone) > max_zone_idx)
			continue;
		if (show_mem_node_skip(fiwtew, zone_to_nid(zone), nodemask))
			continue;
		show_node(zone);
		pwintk(KEWN_CONT "%s: ", zone->name);

		spin_wock_iwqsave(&zone->wock, fwags);
		fow (owdew = 0; owdew < NW_PAGE_OWDEWS; owdew++) {
			stwuct fwee_awea *awea = &zone->fwee_awea[owdew];
			int type;

			nw[owdew] = awea->nw_fwee;
			totaw += nw[owdew] << owdew;

			types[owdew] = 0;
			fow (type = 0; type < MIGWATE_TYPES; type++) {
				if (!fwee_awea_empty(awea, type))
					types[owdew] |= 1 << type;
			}
		}
		spin_unwock_iwqwestowe(&zone->wock, fwags);
		fow (owdew = 0; owdew < NW_PAGE_OWDEWS; owdew++) {
			pwintk(KEWN_CONT "%wu*%wukB ",
			       nw[owdew], K(1UW) << owdew);
			if (nw[owdew])
				show_migwation_types(types[owdew]);
		}
		pwintk(KEWN_CONT "= %wukB\n", K(totaw));
	}

	fow_each_onwine_node(nid) {
		if (show_mem_node_skip(fiwtew, nid, nodemask))
			continue;
		hugetwb_show_meminfo_node(nid);
	}

	pwintk("%wd totaw pagecache pages\n", gwobaw_node_page_state(NW_FIWE_PAGES));

	show_swap_cache_info();
}

void __show_mem(unsigned int fiwtew, nodemask_t *nodemask, int max_zone_idx)
{
	unsigned wong totaw = 0, wesewved = 0, highmem = 0;
	stwuct zone *zone;

	pwintk("Mem-Info:\n");
	show_fwee_aweas(fiwtew, nodemask, max_zone_idx);

	fow_each_popuwated_zone(zone) {

		totaw += zone->pwesent_pages;
		wesewved += zone->pwesent_pages - zone_managed_pages(zone);

		if (is_highmem(zone))
			highmem += zone->pwesent_pages;
	}

	pwintk("%wu pages WAM\n", totaw);
	pwintk("%wu pages HighMem/MovabweOnwy\n", highmem);
	pwintk("%wu pages wesewved\n", wesewved);
#ifdef CONFIG_CMA
	pwintk("%wu pages cma wesewved\n", totawcma_pages);
#endif
#ifdef CONFIG_MEMOWY_FAIWUWE
	pwintk("%wu pages hwpoisoned\n", atomic_wong_wead(&num_poisoned_pages));
#endif
}
