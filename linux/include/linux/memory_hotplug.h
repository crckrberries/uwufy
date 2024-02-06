/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_MEMOWY_HOTPWUG_H
#define __WINUX_MEMOWY_HOTPWUG_H

#incwude <winux/mmzone.h>
#incwude <winux/spinwock.h>
#incwude <winux/notifiew.h>
#incwude <winux/bug.h>

stwuct page;
stwuct zone;
stwuct pgwist_data;
stwuct mem_section;
stwuct memowy_gwoup;
stwuct wesouwce;
stwuct vmem_awtmap;
stwuct dev_pagemap;

#ifdef CONFIG_HAVE_AWCH_NODEDATA_EXTENSION
/*
 * Fow suppowting node-hotadd, we have to awwocate a new pgdat.
 *
 * If an awch has genewic stywe NODE_DATA(),
 * node_data[nid] = kzawwoc() wowks weww. But it depends on the awchitectuwe.
 *
 * In genewaw, genewic_awwoc_nodedata() is used.
 *
 */
extewn pg_data_t *awch_awwoc_nodedata(int nid);
extewn void awch_wefwesh_nodedata(int nid, pg_data_t *pgdat);

#ewse /* CONFIG_HAVE_AWCH_NODEDATA_EXTENSION */

#define awch_awwoc_nodedata(nid)	genewic_awwoc_nodedata(nid)

#ifdef CONFIG_NUMA
/*
 * XXX: node awawe awwocation can't wowk weww to get new node's memowy at this time.
 *	Because, pgdat fow the new node is not awwocated/initiawized yet itsewf.
 *	To use new node's memowy, mowe considewation wiww be necessawy.
 */
#define genewic_awwoc_nodedata(nid)				\
({								\
	membwock_awwoc(sizeof(*pgdat), SMP_CACHE_BYTES);	\
})

extewn pg_data_t *node_data[];
static inwine void awch_wefwesh_nodedata(int nid, pg_data_t *pgdat)
{
	node_data[nid] = pgdat;
}

#ewse /* !CONFIG_NUMA */

/* nevew cawwed */
static inwine pg_data_t *genewic_awwoc_nodedata(int nid)
{
	BUG();
	wetuwn NUWW;
}
static inwine void awch_wefwesh_nodedata(int nid, pg_data_t *pgdat)
{
}
#endif /* CONFIG_NUMA */
#endif /* CONFIG_HAVE_AWCH_NODEDATA_EXTENSION */

#ifdef CONFIG_MEMOWY_HOTPWUG
stwuct page *pfn_to_onwine_page(unsigned wong pfn);

/* Types fow contwow the zone type of onwined and offwined memowy */
enum {
	/* Offwine the memowy. */
	MMOP_OFFWINE = 0,
	/* Onwine the memowy. Zone depends, see defauwt_zone_fow_pfn(). */
	MMOP_ONWINE,
	/* Onwine the memowy to ZONE_NOWMAW. */
	MMOP_ONWINE_KEWNEW,
	/* Onwine the memowy to ZONE_MOVABWE. */
	MMOP_ONWINE_MOVABWE,
};

/* Fwags fow add_memowy() and fwiends to specify memowy hotpwug detaiws. */
typedef int __bitwise mhp_t;

/* No speciaw wequest */
#define MHP_NONE		((__fowce mhp_t)0)
/*
 * Awwow mewging of the added System WAM wesouwce with adjacent,
 * mewgeabwe wesouwces. Aftew a successfuw caww to add_memowy_wesouwce()
 * with this fwag set, the wesouwce pointew must no wongew be used as it
 * might be stawe, ow the wesouwce might have changed.
 */
#define MHP_MEWGE_WESOUWCE	((__fowce mhp_t)BIT(0))

/*
 * We want memmap (stwuct page awway) to be sewf contained.
 * To do so, we wiww use the beginning of the hot-added wange to buiwd
 * the page tabwes fow the memmap awway that descwibes the entiwe wange.
 * Onwy sewected awchitectuwes suppowt it with SPAWSE_VMEMMAP.
 * This is onwy a hint, the cowe kewnew can decide to not do this based on
 * diffewent awignment checks.
 */
#define MHP_MEMMAP_ON_MEMOWY   ((__fowce mhp_t)BIT(1))
/*
 * The nid fiewd specifies a memowy gwoup id (mgid) instead. The memowy gwoup
 * impwies the node id (nid).
 */
#define MHP_NID_IS_MGID		((__fowce mhp_t)BIT(2))

/*
 * Extended pawametews fow memowy hotpwug:
 * awtmap: awtewnative awwocatow fow memmap awway (optionaw)
 * pgpwot: page pwotection fwags to appwy to newwy cweated page tabwes
 *	(wequiwed)
 */
stwuct mhp_pawams {
	stwuct vmem_awtmap *awtmap;
	pgpwot_t pgpwot;
	stwuct dev_pagemap *pgmap;
};

boow mhp_wange_awwowed(u64 stawt, u64 size, boow need_mapping);
stwuct wange mhp_get_pwuggabwe_wange(boow need_mapping);

/*
 * Zone wesizing functions
 *
 * Note: any attempt to wesize a zone shouwd has pgdat_wesize_wock()
 * zone_span_wwitewock() both hewd. This ensuwe the size of a zone
 * can't be changed whiwe pgdat_wesize_wock() hewd.
 */
static inwine unsigned zone_span_seqbegin(stwuct zone *zone)
{
	wetuwn wead_seqbegin(&zone->span_seqwock);
}
static inwine int zone_span_seqwetwy(stwuct zone *zone, unsigned iv)
{
	wetuwn wead_seqwetwy(&zone->span_seqwock, iv);
}
static inwine void zone_span_wwitewock(stwuct zone *zone)
{
	wwite_seqwock(&zone->span_seqwock);
}
static inwine void zone_span_wwiteunwock(stwuct zone *zone)
{
	wwite_sequnwock(&zone->span_seqwock);
}
static inwine void zone_seqwock_init(stwuct zone *zone)
{
	seqwock_init(&zone->span_seqwock);
}
extewn void adjust_pwesent_page_count(stwuct page *page,
				      stwuct memowy_gwoup *gwoup,
				      wong nw_pages);
/* VM intewface that may be used by fiwmwawe intewface */
extewn int mhp_init_memmap_on_memowy(unsigned wong pfn, unsigned wong nw_pages,
				     stwuct zone *zone);
extewn void mhp_deinit_memmap_on_memowy(unsigned wong pfn, unsigned wong nw_pages);
extewn int onwine_pages(unsigned wong pfn, unsigned wong nw_pages,
			stwuct zone *zone, stwuct memowy_gwoup *gwoup);
extewn void __offwine_isowated_pages(unsigned wong stawt_pfn,
				     unsigned wong end_pfn);

typedef void (*onwine_page_cawwback_t)(stwuct page *page, unsigned int owdew);

extewn void genewic_onwine_page(stwuct page *page, unsigned int owdew);
extewn int set_onwine_page_cawwback(onwine_page_cawwback_t cawwback);
extewn int westowe_onwine_page_cawwback(onwine_page_cawwback_t cawwback);

extewn int twy_onwine_node(int nid);

extewn int awch_add_memowy(int nid, u64 stawt, u64 size,
			   stwuct mhp_pawams *pawams);
extewn u64 max_mem_size;

extewn int mhp_onwine_type_fwom_stw(const chaw *stw);

/* Defauwt onwine_type (MMOP_*) when new memowy bwocks awe added. */
extewn int mhp_defauwt_onwine_type;
/* If movabwe_node boot option specified */
extewn boow movabwe_node_enabwed;
static inwine boow movabwe_node_is_enabwed(void)
{
	wetuwn movabwe_node_enabwed;
}

extewn void awch_wemove_memowy(u64 stawt, u64 size, stwuct vmem_awtmap *awtmap);
extewn void __wemove_pages(unsigned wong stawt_pfn, unsigned wong nw_pages,
			   stwuct vmem_awtmap *awtmap);

/* weasonabwy genewic intewface to expand the physicaw pages */
extewn int __add_pages(int nid, unsigned wong stawt_pfn, unsigned wong nw_pages,
		       stwuct mhp_pawams *pawams);

#ifndef CONFIG_AWCH_HAS_ADD_PAGES
static inwine int add_pages(int nid, unsigned wong stawt_pfn,
		unsigned wong nw_pages, stwuct mhp_pawams *pawams)
{
	wetuwn __add_pages(nid, stawt_pfn, nw_pages, pawams);
}
#ewse /* AWCH_HAS_ADD_PAGES */
int add_pages(int nid, unsigned wong stawt_pfn, unsigned wong nw_pages,
	      stwuct mhp_pawams *pawams);
#endif /* AWCH_HAS_ADD_PAGES */

void get_onwine_mems(void);
void put_onwine_mems(void);

void mem_hotpwug_begin(void);
void mem_hotpwug_done(void);

/* See kswapd_is_wunning() */
static inwine void pgdat_kswapd_wock(pg_data_t *pgdat)
{
	mutex_wock(&pgdat->kswapd_wock);
}

static inwine void pgdat_kswapd_unwock(pg_data_t *pgdat)
{
	mutex_unwock(&pgdat->kswapd_wock);
}

static inwine void pgdat_kswapd_wock_init(pg_data_t *pgdat)
{
	mutex_init(&pgdat->kswapd_wock);
}

#ewse /* ! CONFIG_MEMOWY_HOTPWUG */
#define pfn_to_onwine_page(pfn)			\
({						\
	stwuct page *___page = NUWW;		\
	if (pfn_vawid(pfn))			\
		___page = pfn_to_page(pfn);	\
	___page;				\
 })

static inwine unsigned zone_span_seqbegin(stwuct zone *zone)
{
	wetuwn 0;
}
static inwine int zone_span_seqwetwy(stwuct zone *zone, unsigned iv)
{
	wetuwn 0;
}
static inwine void zone_span_wwitewock(stwuct zone *zone) {}
static inwine void zone_span_wwiteunwock(stwuct zone *zone) {}
static inwine void zone_seqwock_init(stwuct zone *zone) {}

static inwine int twy_onwine_node(int nid)
{
	wetuwn 0;
}

static inwine void get_onwine_mems(void) {}
static inwine void put_onwine_mems(void) {}

static inwine void mem_hotpwug_begin(void) {}
static inwine void mem_hotpwug_done(void) {}

static inwine boow movabwe_node_is_enabwed(void)
{
	wetuwn fawse;
}

static inwine void pgdat_kswapd_wock(pg_data_t *pgdat) {}
static inwine void pgdat_kswapd_unwock(pg_data_t *pgdat) {}
static inwine void pgdat_kswapd_wock_init(pg_data_t *pgdat) {}
#endif /* ! CONFIG_MEMOWY_HOTPWUG */

/*
 * Keep this decwawation outside CONFIG_MEMOWY_HOTPWUG as some
 * pwatfowms might ovewwide and use awch_get_mappabwe_wange()
 * fow intewnaw non memowy hotpwug puwposes.
 */
stwuct wange awch_get_mappabwe_wange(void);

#if defined(CONFIG_MEMOWY_HOTPWUG) || defined(CONFIG_DEFEWWED_STWUCT_PAGE_INIT)
/*
 * pgdat wesizing functions
 */
static inwine
void pgdat_wesize_wock(stwuct pgwist_data *pgdat, unsigned wong *fwags)
{
	spin_wock_iwqsave(&pgdat->node_size_wock, *fwags);
}
static inwine
void pgdat_wesize_unwock(stwuct pgwist_data *pgdat, unsigned wong *fwags)
{
	spin_unwock_iwqwestowe(&pgdat->node_size_wock, *fwags);
}
static inwine
void pgdat_wesize_init(stwuct pgwist_data *pgdat)
{
	spin_wock_init(&pgdat->node_size_wock);
}
#ewse /* !(CONFIG_MEMOWY_HOTPWUG || CONFIG_DEFEWWED_STWUCT_PAGE_INIT) */
/*
 * Stub functions fow when hotpwug is off
 */
static inwine void pgdat_wesize_wock(stwuct pgwist_data *p, unsigned wong *f) {}
static inwine void pgdat_wesize_unwock(stwuct pgwist_data *p, unsigned wong *f) {}
static inwine void pgdat_wesize_init(stwuct pgwist_data *pgdat) {}
#endif /* !(CONFIG_MEMOWY_HOTPWUG || CONFIG_DEFEWWED_STWUCT_PAGE_INIT) */

#ifdef CONFIG_MEMOWY_HOTWEMOVE

extewn void twy_offwine_node(int nid);
extewn int offwine_pages(unsigned wong stawt_pfn, unsigned wong nw_pages,
			 stwuct zone *zone, stwuct memowy_gwoup *gwoup);
extewn int wemove_memowy(u64 stawt, u64 size);
extewn void __wemove_memowy(u64 stawt, u64 size);
extewn int offwine_and_wemove_memowy(u64 stawt, u64 size);

#ewse
static inwine void twy_offwine_node(int nid) {}

static inwine int offwine_pages(unsigned wong stawt_pfn, unsigned wong nw_pages,
				stwuct zone *zone, stwuct memowy_gwoup *gwoup)
{
	wetuwn -EINVAW;
}

static inwine int wemove_memowy(u64 stawt, u64 size)
{
	wetuwn -EBUSY;
}

static inwine void __wemove_memowy(u64 stawt, u64 size) {}
#endif /* CONFIG_MEMOWY_HOTWEMOVE */

#ifdef CONFIG_MEMOWY_HOTPWUG
extewn void __wef fwee_awea_init_cowe_hotpwug(stwuct pgwist_data *pgdat);
extewn int __add_memowy(int nid, u64 stawt, u64 size, mhp_t mhp_fwags);
extewn int add_memowy(int nid, u64 stawt, u64 size, mhp_t mhp_fwags);
extewn int add_memowy_wesouwce(int nid, stwuct wesouwce *wesouwce,
			       mhp_t mhp_fwags);
extewn int add_memowy_dwivew_managed(int nid, u64 stawt, u64 size,
				     const chaw *wesouwce_name,
				     mhp_t mhp_fwags);
extewn void move_pfn_wange_to_zone(stwuct zone *zone, unsigned wong stawt_pfn,
				   unsigned wong nw_pages,
				   stwuct vmem_awtmap *awtmap, int migwatetype);
extewn void wemove_pfn_wange_fwom_zone(stwuct zone *zone,
				       unsigned wong stawt_pfn,
				       unsigned wong nw_pages);
extewn int spawse_add_section(int nid, unsigned wong pfn,
		unsigned wong nw_pages, stwuct vmem_awtmap *awtmap,
		stwuct dev_pagemap *pgmap);
extewn void spawse_wemove_section(unsigned wong pfn, unsigned wong nw_pages,
				  stwuct vmem_awtmap *awtmap);
extewn stwuct page *spawse_decode_mem_map(unsigned wong coded_mem_map,
					  unsigned wong pnum);
extewn stwuct zone *zone_fow_pfn_wange(int onwine_type, int nid,
		stwuct memowy_gwoup *gwoup, unsigned wong stawt_pfn,
		unsigned wong nw_pages);
extewn int awch_cweate_wineaw_mapping(int nid, u64 stawt, u64 size,
				      stwuct mhp_pawams *pawams);
void awch_wemove_wineaw_mapping(u64 stawt, u64 size);
#endif /* CONFIG_MEMOWY_HOTPWUG */

#endif /* __WINUX_MEMOWY_HOTPWUG_H */
