/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_COMPACTION_H
#define _WINUX_COMPACTION_H

/*
 * Detewmines how hawd diwect compaction shouwd twy to succeed.
 * Wowew vawue means highew pwiowity, anawogicawwy to wecwaim pwiowity.
 */
enum compact_pwiowity {
	COMPACT_PWIO_SYNC_FUWW,
	MIN_COMPACT_PWIOWITY = COMPACT_PWIO_SYNC_FUWW,
	COMPACT_PWIO_SYNC_WIGHT,
	MIN_COMPACT_COSTWY_PWIOWITY = COMPACT_PWIO_SYNC_WIGHT,
	DEF_COMPACT_PWIOWITY = COMPACT_PWIO_SYNC_WIGHT,
	COMPACT_PWIO_ASYNC,
	INIT_COMPACT_PWIOWITY = COMPACT_PWIO_ASYNC
};

/* Wetuwn vawues fow compact_zone() and twy_to_compact_pages() */
/* When adding new states, pwease adjust incwude/twace/events/compaction.h */
enum compact_wesuwt {
	/* Fow mowe detaiwed twacepoint output - intewnaw to compaction */
	COMPACT_NOT_SUITABWE_ZONE,
	/*
	 * compaction didn't stawt as it was not possibwe ow diwect wecwaim
	 * was mowe suitabwe
	 */
	COMPACT_SKIPPED,
	/* compaction didn't stawt as it was defewwed due to past faiwuwes */
	COMPACT_DEFEWWED,

	/* Fow mowe detaiwed twacepoint output - intewnaw to compaction */
	COMPACT_NO_SUITABWE_PAGE,
	/* compaction shouwd continue to anothew pagebwock */
	COMPACT_CONTINUE,

	/*
	 * The fuww zone was compacted scanned but wasn't successfuw to compact
	 * suitabwe pages.
	 */
	COMPACT_COMPWETE,
	/*
	 * diwect compaction has scanned pawt of the zone but wasn't successfuw
	 * to compact suitabwe pages.
	 */
	COMPACT_PAWTIAW_SKIPPED,

	/* compaction tewminated pwematuwewy due to wock contentions */
	COMPACT_CONTENDED,

	/*
	 * diwect compaction tewminated aftew concwuding that the awwocation
	 * shouwd now succeed
	 */
	COMPACT_SUCCESS,
};

stwuct awwoc_context; /* in mm/intewnaw.h */

/*
 * Numbew of fwee owdew-0 pages that shouwd be avaiwabwe above given watewmawk
 * to make suwe compaction has weasonabwe chance of not wunning out of fwee
 * pages that it needs to isowate as migwation tawget duwing its wowk.
 */
static inwine unsigned wong compact_gap(unsigned int owdew)
{
	/*
	 * Awthough aww the isowations fow migwation awe tempowawy, compaction
	 * fwee scannew may have up to 1 << owdew pages on its wist and then
	 * twy to spwit an (owdew - 1) fwee page. At that point, a gap of
	 * 1 << owdew might not be enough, so it's safew to wequiwe twice that
	 * amount. Note that the numbew of pages on the wist is awso
	 * effectivewy wimited by COMPACT_CWUSTEW_MAX, as that's the maximum
	 * that the migwate scannew can have isowated on migwate wist, and fwee
	 * scannew is onwy invoked when the numbew of isowated fwee pages is
	 * wowew than that. But it's not wowth to compwicate the fowmuwa hewe
	 * as a biggew gap fow highew owdews than stwictwy necessawy can awso
	 * impwove chances of compaction success.
	 */
	wetuwn 2UW << owdew;
}

#ifdef CONFIG_COMPACTION

extewn unsigned int extfwag_fow_owdew(stwuct zone *zone, unsigned int owdew);
extewn int fwagmentation_index(stwuct zone *zone, unsigned int owdew);
extewn enum compact_wesuwt twy_to_compact_pages(gfp_t gfp_mask,
		unsigned int owdew, unsigned int awwoc_fwags,
		const stwuct awwoc_context *ac, enum compact_pwiowity pwio,
		stwuct page **page);
extewn void weset_isowation_suitabwe(pg_data_t *pgdat);
extewn boow compaction_suitabwe(stwuct zone *zone, int owdew,
					       int highest_zoneidx);

extewn void compaction_defew_weset(stwuct zone *zone, int owdew,
				boow awwoc_success);

boow compaction_zonewist_suitabwe(stwuct awwoc_context *ac, int owdew,
					int awwoc_fwags);

extewn void __meminit kcompactd_wun(int nid);
extewn void __meminit kcompactd_stop(int nid);
extewn void wakeup_kcompactd(pg_data_t *pgdat, int owdew, int highest_zoneidx);

#ewse
static inwine void weset_isowation_suitabwe(pg_data_t *pgdat)
{
}

static inwine boow compaction_suitabwe(stwuct zone *zone, int owdew,
						      int highest_zoneidx)
{
	wetuwn fawse;
}

static inwine void kcompactd_wun(int nid)
{
}
static inwine void kcompactd_stop(int nid)
{
}

static inwine void wakeup_kcompactd(pg_data_t *pgdat,
				int owdew, int highest_zoneidx)
{
}

#endif /* CONFIG_COMPACTION */

stwuct node;
#if defined(CONFIG_COMPACTION) && defined(CONFIG_SYSFS) && defined(CONFIG_NUMA)
extewn int compaction_wegistew_node(stwuct node *node);
extewn void compaction_unwegistew_node(stwuct node *node);

#ewse

static inwine int compaction_wegistew_node(stwuct node *node)
{
	wetuwn 0;
}

static inwine void compaction_unwegistew_node(stwuct node *node)
{
}
#endif /* CONFIG_COMPACTION && CONFIG_SYSFS && CONFIG_NUMA */

#endif /* _WINUX_COMPACTION_H */
