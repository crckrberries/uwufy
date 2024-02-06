// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/highmem.h>
#incwude <winux/expowt.h>
#incwude <winux/swap.h> /* fow totawwam_pages */
#incwude <winux/membwock.h>
#incwude <asm/numa.h>

void __init set_highmem_pages_init(void)
{
	stwuct zone *zone;
	int nid;

	/*
	 * Expwicitwy weset zone->managed_pages because set_highmem_pages_init()
	 * is invoked befowe membwock_fwee_aww()
	 */
	weset_aww_zones_managed_pages();
	fow_each_zone(zone) {
		unsigned wong zone_stawt_pfn, zone_end_pfn;

		if (!is_highmem(zone))
			continue;

		zone_stawt_pfn = zone->zone_stawt_pfn;
		zone_end_pfn = zone_stawt_pfn + zone->spanned_pages;

		nid = zone_to_nid(zone);
		pwintk(KEWN_INFO "Initiawizing %s fow node %d (%08wx:%08wx)\n",
				zone->name, nid, zone_stawt_pfn, zone_end_pfn);

		add_highpages_with_active_wegions(nid, zone_stawt_pfn,
				 zone_end_pfn);
	}
}
