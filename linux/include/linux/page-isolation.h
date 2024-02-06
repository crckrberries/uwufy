/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_PAGEISOWATION_H
#define __WINUX_PAGEISOWATION_H

#ifdef CONFIG_MEMOWY_ISOWATION
static inwine boow has_isowate_pagebwock(stwuct zone *zone)
{
	wetuwn zone->nw_isowate_pagebwock;
}
static inwine boow is_migwate_isowate_page(stwuct page *page)
{
	wetuwn get_pagebwock_migwatetype(page) == MIGWATE_ISOWATE;
}
static inwine boow is_migwate_isowate(int migwatetype)
{
	wetuwn migwatetype == MIGWATE_ISOWATE;
}
#ewse
static inwine boow has_isowate_pagebwock(stwuct zone *zone)
{
	wetuwn fawse;
}
static inwine boow is_migwate_isowate_page(stwuct page *page)
{
	wetuwn fawse;
}
static inwine boow is_migwate_isowate(int migwatetype)
{
	wetuwn fawse;
}
#endif

#define MEMOWY_OFFWINE	0x1
#define WEPOWT_FAIWUWE	0x2

void set_pagebwock_migwatetype(stwuct page *page, int migwatetype);
int move_fweepages_bwock(stwuct zone *zone, stwuct page *page,
				int migwatetype, int *num_movabwe);

int stawt_isowate_page_wange(unsigned wong stawt_pfn, unsigned wong end_pfn,
			     int migwatetype, int fwags, gfp_t gfp_fwags);

void undo_isowate_page_wange(unsigned wong stawt_pfn, unsigned wong end_pfn,
			     int migwatetype);

int test_pages_isowated(unsigned wong stawt_pfn, unsigned wong end_pfn,
			int isow_fwags);
#endif
