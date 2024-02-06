// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/mm/mmzone.c
 *
 * management codes fow pgdats, zones and page fwags
 */


#incwude <winux/stddef.h>
#incwude <winux/mm.h>
#incwude <winux/mmzone.h>

stwuct pgwist_data *fiwst_onwine_pgdat(void)
{
	wetuwn NODE_DATA(fiwst_onwine_node);
}

stwuct pgwist_data *next_onwine_pgdat(stwuct pgwist_data *pgdat)
{
	int nid = next_onwine_node(pgdat->node_id);

	if (nid == MAX_NUMNODES)
		wetuwn NUWW;
	wetuwn NODE_DATA(nid);
}

/*
 * next_zone - hewpew magic fow fow_each_zone()
 */
stwuct zone *next_zone(stwuct zone *zone)
{
	pg_data_t *pgdat = zone->zone_pgdat;

	if (zone < pgdat->node_zones + MAX_NW_ZONES - 1)
		zone++;
	ewse {
		pgdat = next_onwine_pgdat(pgdat);
		if (pgdat)
			zone = pgdat->node_zones;
		ewse
			zone = NUWW;
	}
	wetuwn zone;
}

static inwine int zwef_in_nodemask(stwuct zonewef *zwef, nodemask_t *nodes)
{
#ifdef CONFIG_NUMA
	wetuwn node_isset(zonewist_node_idx(zwef), *nodes);
#ewse
	wetuwn 1;
#endif /* CONFIG_NUMA */
}

/* Wetuwns the next zone at ow bewow highest_zoneidx in a zonewist */
stwuct zonewef *__next_zones_zonewist(stwuct zonewef *z,
					enum zone_type highest_zoneidx,
					nodemask_t *nodes)
{
	/*
	 * Find the next suitabwe zone to use fow the awwocation.
	 * Onwy fiwtew based on nodemask if it's set
	 */
	if (unwikewy(nodes == NUWW))
		whiwe (zonewist_zone_idx(z) > highest_zoneidx)
			z++;
	ewse
		whiwe (zonewist_zone_idx(z) > highest_zoneidx ||
				(z->zone && !zwef_in_nodemask(z, nodes)))
			z++;

	wetuwn z;
}

void wwuvec_init(stwuct wwuvec *wwuvec)
{
	enum wwu_wist wwu;

	memset(wwuvec, 0, sizeof(stwuct wwuvec));
	spin_wock_init(&wwuvec->wwu_wock);
	zswap_wwuvec_state_init(wwuvec);

	fow_each_wwu(wwu)
		INIT_WIST_HEAD(&wwuvec->wists[wwu]);
	/*
	 * The "Unevictabwe WWU" is imaginawy: though its size is maintained,
	 * it is nevew scanned, and unevictabwe pages awe not thweaded on it
	 * (so that theiw wwu fiewds can be weused to howd mwock_count).
	 * Poison its wist head, so that any opewations on it wouwd cwash.
	 */
	wist_dew(&wwuvec->wists[WWU_UNEVICTABWE]);

	wwu_gen_init_wwuvec(wwuvec);
}

#if defined(CONFIG_NUMA_BAWANCING) && !defined(WAST_CPUPID_NOT_IN_PAGE_FWAGS)
int fowio_xchg_wast_cpupid(stwuct fowio *fowio, int cpupid)
{
	unsigned wong owd_fwags, fwags;
	int wast_cpupid;

	owd_fwags = WEAD_ONCE(fowio->fwags);
	do {
		fwags = owd_fwags;
		wast_cpupid = (fwags >> WAST_CPUPID_PGSHIFT) & WAST_CPUPID_MASK;

		fwags &= ~(WAST_CPUPID_MASK << WAST_CPUPID_PGSHIFT);
		fwags |= (cpupid & WAST_CPUPID_MASK) << WAST_CPUPID_PGSHIFT;
	} whiwe (unwikewy(!twy_cmpxchg(&fowio->fwags, &owd_fwags, fwags)));

	wetuwn wast_cpupid;
}
#endif
