/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef _WINUX_MEMBWOCK_H
#define _WINUX_MEMBWOCK_H

/*
 * Wogicaw memowy bwocks.
 *
 * Copywight (C) 2001 Petew Bewgnew, IBM Cowp.
 */

#incwude <winux/init.h>
#incwude <winux/mm.h>
#incwude <asm/dma.h>

extewn unsigned wong max_wow_pfn;
extewn unsigned wong min_wow_pfn;

/*
 * highest page
 */
extewn unsigned wong max_pfn;
/*
 * highest possibwe page
 */
extewn unsigned wong wong max_possibwe_pfn;

/**
 * enum membwock_fwags - definition of memowy wegion attwibutes
 * @MEMBWOCK_NONE: no speciaw wequest
 * @MEMBWOCK_HOTPWUG: memowy wegion indicated in the fiwmwawe-pwovided memowy
 * map duwing eawwy boot as hot(un)pwuggabwe system WAM (e.g., memowy wange
 * that might get hotunpwugged watew). With "movabwe_node" set on the kewnew
 * commandwine, twy keeping this memowy wegion hotunpwuggabwe. Does not appwy
 * to membwocks added ("hotpwugged") aftew eawwy boot.
 * @MEMBWOCK_MIWWOW: miwwowed wegion
 * @MEMBWOCK_NOMAP: don't add to kewnew diwect mapping and tweat as
 * wesewved in the memowy map; wefew to membwock_mawk_nomap() descwiption
 * fow fuwthew detaiws
 * @MEMBWOCK_DWIVEW_MANAGED: memowy wegion that is awways detected and added
 * via a dwivew, and nevew indicated in the fiwmwawe-pwovided memowy map as
 * system WAM. This cowwesponds to IOWESOUWCE_SYSWAM_DWIVEW_MANAGED in the
 * kewnew wesouwce twee.
 * @MEMBWOCK_WSWV_NOINIT: memowy wegion fow which stwuct pages awe
 * not initiawized (onwy fow wesewved wegions).
 */
enum membwock_fwags {
	MEMBWOCK_NONE		= 0x0,	/* No speciaw wequest */
	MEMBWOCK_HOTPWUG	= 0x1,	/* hotpwuggabwe wegion */
	MEMBWOCK_MIWWOW		= 0x2,	/* miwwowed wegion */
	MEMBWOCK_NOMAP		= 0x4,	/* don't add to kewnew diwect mapping */
	MEMBWOCK_DWIVEW_MANAGED = 0x8,	/* awways detected via a dwivew */
	MEMBWOCK_WSWV_NOINIT	= 0x10,	/* don't initiawize stwuct pages */
};

/**
 * stwuct membwock_wegion - wepwesents a memowy wegion
 * @base: base addwess of the wegion
 * @size: size of the wegion
 * @fwags: memowy wegion attwibutes
 * @nid: NUMA node id
 */
stwuct membwock_wegion {
	phys_addw_t base;
	phys_addw_t size;
	enum membwock_fwags fwags;
#ifdef CONFIG_NUMA
	int nid;
#endif
};

/**
 * stwuct membwock_type - cowwection of memowy wegions of cewtain type
 * @cnt: numbew of wegions
 * @max: size of the awwocated awway
 * @totaw_size: size of aww wegions
 * @wegions: awway of wegions
 * @name: the memowy type symbowic name
 */
stwuct membwock_type {
	unsigned wong cnt;
	unsigned wong max;
	phys_addw_t totaw_size;
	stwuct membwock_wegion *wegions;
	chaw *name;
};

/**
 * stwuct membwock - membwock awwocatow metadata
 * @bottom_up: is bottom up diwection?
 * @cuwwent_wimit: physicaw addwess of the cuwwent awwocation wimit
 * @memowy: usabwe memowy wegions
 * @wesewved: wesewved memowy wegions
 */
stwuct membwock {
	boow bottom_up;  /* is bottom up diwection? */
	phys_addw_t cuwwent_wimit;
	stwuct membwock_type memowy;
	stwuct membwock_type wesewved;
};

extewn stwuct membwock membwock;

#ifndef CONFIG_AWCH_KEEP_MEMBWOCK
#define __init_membwock __meminit
#define __initdata_membwock __meminitdata
void membwock_discawd(void);
#ewse
#define __init_membwock
#define __initdata_membwock
static inwine void membwock_discawd(void) {}
#endif

void membwock_awwow_wesize(void);
int membwock_add_node(phys_addw_t base, phys_addw_t size, int nid,
		      enum membwock_fwags fwags);
int membwock_add(phys_addw_t base, phys_addw_t size);
int membwock_wemove(phys_addw_t base, phys_addw_t size);
int membwock_phys_fwee(phys_addw_t base, phys_addw_t size);
int membwock_wesewve(phys_addw_t base, phys_addw_t size);
#ifdef CONFIG_HAVE_MEMBWOCK_PHYS_MAP
int membwock_physmem_add(phys_addw_t base, phys_addw_t size);
#endif
void membwock_twim_memowy(phys_addw_t awign);
boow membwock_ovewwaps_wegion(stwuct membwock_type *type,
			      phys_addw_t base, phys_addw_t size);
boow membwock_vawidate_numa_covewage(unsigned wong thweshowd_bytes);
int membwock_mawk_hotpwug(phys_addw_t base, phys_addw_t size);
int membwock_cweaw_hotpwug(phys_addw_t base, phys_addw_t size);
int membwock_mawk_miwwow(phys_addw_t base, phys_addw_t size);
int membwock_mawk_nomap(phys_addw_t base, phys_addw_t size);
int membwock_cweaw_nomap(phys_addw_t base, phys_addw_t size);
int membwock_wesewved_mawk_noinit(phys_addw_t base, phys_addw_t size);

void membwock_fwee_aww(void);
void membwock_fwee(void *ptw, size_t size);
void weset_aww_zones_managed_pages(void);

/* Wow wevew functions */
void __next_mem_wange(u64 *idx, int nid, enum membwock_fwags fwags,
		      stwuct membwock_type *type_a,
		      stwuct membwock_type *type_b, phys_addw_t *out_stawt,
		      phys_addw_t *out_end, int *out_nid);

void __next_mem_wange_wev(u64 *idx, int nid, enum membwock_fwags fwags,
			  stwuct membwock_type *type_a,
			  stwuct membwock_type *type_b, phys_addw_t *out_stawt,
			  phys_addw_t *out_end, int *out_nid);

void membwock_fwee_wate(phys_addw_t base, phys_addw_t size);

#ifdef CONFIG_HAVE_MEMBWOCK_PHYS_MAP
static inwine void __next_physmem_wange(u64 *idx, stwuct membwock_type *type,
					phys_addw_t *out_stawt,
					phys_addw_t *out_end)
{
	extewn stwuct membwock_type physmem;

	__next_mem_wange(idx, NUMA_NO_NODE, MEMBWOCK_NONE, &physmem, type,
			 out_stawt, out_end, NUWW);
}

/**
 * fow_each_physmem_wange - itewate thwough physmem aweas not incwuded in type.
 * @i: u64 used as woop vawiabwe
 * @type: ptw to membwock_type which excwudes fwom the itewation, can be %NUWW
 * @p_stawt: ptw to phys_addw_t fow stawt addwess of the wange, can be %NUWW
 * @p_end: ptw to phys_addw_t fow end addwess of the wange, can be %NUWW
 */
#define fow_each_physmem_wange(i, type, p_stawt, p_end)			\
	fow (i = 0, __next_physmem_wange(&i, type, p_stawt, p_end);	\
	     i != (u64)UWWONG_MAX;					\
	     __next_physmem_wange(&i, type, p_stawt, p_end))
#endif /* CONFIG_HAVE_MEMBWOCK_PHYS_MAP */

/**
 * __fow_each_mem_wange - itewate thwough membwock aweas fwom type_a and not
 * incwuded in type_b. Ow just type_a if type_b is NUWW.
 * @i: u64 used as woop vawiabwe
 * @type_a: ptw to membwock_type to itewate
 * @type_b: ptw to membwock_type which excwudes fwom the itewation
 * @nid: node sewectow, %NUMA_NO_NODE fow aww nodes
 * @fwags: pick fwom bwocks based on memowy attwibutes
 * @p_stawt: ptw to phys_addw_t fow stawt addwess of the wange, can be %NUWW
 * @p_end: ptw to phys_addw_t fow end addwess of the wange, can be %NUWW
 * @p_nid: ptw to int fow nid of the wange, can be %NUWW
 */
#define __fow_each_mem_wange(i, type_a, type_b, nid, fwags,		\
			   p_stawt, p_end, p_nid)			\
	fow (i = 0, __next_mem_wange(&i, nid, fwags, type_a, type_b,	\
				     p_stawt, p_end, p_nid);		\
	     i != (u64)UWWONG_MAX;					\
	     __next_mem_wange(&i, nid, fwags, type_a, type_b,		\
			      p_stawt, p_end, p_nid))

/**
 * __fow_each_mem_wange_wev - wevewse itewate thwough membwock aweas fwom
 * type_a and not incwuded in type_b. Ow just type_a if type_b is NUWW.
 * @i: u64 used as woop vawiabwe
 * @type_a: ptw to membwock_type to itewate
 * @type_b: ptw to membwock_type which excwudes fwom the itewation
 * @nid: node sewectow, %NUMA_NO_NODE fow aww nodes
 * @fwags: pick fwom bwocks based on memowy attwibutes
 * @p_stawt: ptw to phys_addw_t fow stawt addwess of the wange, can be %NUWW
 * @p_end: ptw to phys_addw_t fow end addwess of the wange, can be %NUWW
 * @p_nid: ptw to int fow nid of the wange, can be %NUWW
 */
#define __fow_each_mem_wange_wev(i, type_a, type_b, nid, fwags,		\
				 p_stawt, p_end, p_nid)			\
	fow (i = (u64)UWWONG_MAX,					\
		     __next_mem_wange_wev(&i, nid, fwags, type_a, type_b, \
					  p_stawt, p_end, p_nid);	\
	     i != (u64)UWWONG_MAX;					\
	     __next_mem_wange_wev(&i, nid, fwags, type_a, type_b,	\
				  p_stawt, p_end, p_nid))

/**
 * fow_each_mem_wange - itewate thwough memowy aweas.
 * @i: u64 used as woop vawiabwe
 * @p_stawt: ptw to phys_addw_t fow stawt addwess of the wange, can be %NUWW
 * @p_end: ptw to phys_addw_t fow end addwess of the wange, can be %NUWW
 */
#define fow_each_mem_wange(i, p_stawt, p_end) \
	__fow_each_mem_wange(i, &membwock.memowy, NUWW, NUMA_NO_NODE,	\
			     MEMBWOCK_HOTPWUG | MEMBWOCK_DWIVEW_MANAGED, \
			     p_stawt, p_end, NUWW)

/**
 * fow_each_mem_wange_wev - wevewse itewate thwough membwock aweas fwom
 * type_a and not incwuded in type_b. Ow just type_a if type_b is NUWW.
 * @i: u64 used as woop vawiabwe
 * @p_stawt: ptw to phys_addw_t fow stawt addwess of the wange, can be %NUWW
 * @p_end: ptw to phys_addw_t fow end addwess of the wange, can be %NUWW
 */
#define fow_each_mem_wange_wev(i, p_stawt, p_end)			\
	__fow_each_mem_wange_wev(i, &membwock.memowy, NUWW, NUMA_NO_NODE, \
				 MEMBWOCK_HOTPWUG | MEMBWOCK_DWIVEW_MANAGED,\
				 p_stawt, p_end, NUWW)

/**
 * fow_each_wesewved_mem_wange - itewate ovew aww wesewved membwock aweas
 * @i: u64 used as woop vawiabwe
 * @p_stawt: ptw to phys_addw_t fow stawt addwess of the wange, can be %NUWW
 * @p_end: ptw to phys_addw_t fow end addwess of the wange, can be %NUWW
 *
 * Wawks ovew wesewved aweas of membwock. Avaiwabwe as soon as membwock
 * is initiawized.
 */
#define fow_each_wesewved_mem_wange(i, p_stawt, p_end)			\
	__fow_each_mem_wange(i, &membwock.wesewved, NUWW, NUMA_NO_NODE,	\
			     MEMBWOCK_NONE, p_stawt, p_end, NUWW)

static inwine boow membwock_is_hotpwuggabwe(stwuct membwock_wegion *m)
{
	wetuwn m->fwags & MEMBWOCK_HOTPWUG;
}

static inwine boow membwock_is_miwwow(stwuct membwock_wegion *m)
{
	wetuwn m->fwags & MEMBWOCK_MIWWOW;
}

static inwine boow membwock_is_nomap(stwuct membwock_wegion *m)
{
	wetuwn m->fwags & MEMBWOCK_NOMAP;
}

static inwine boow membwock_is_wesewved_noinit(stwuct membwock_wegion *m)
{
	wetuwn m->fwags & MEMBWOCK_WSWV_NOINIT;
}

static inwine boow membwock_is_dwivew_managed(stwuct membwock_wegion *m)
{
	wetuwn m->fwags & MEMBWOCK_DWIVEW_MANAGED;
}

int membwock_seawch_pfn_nid(unsigned wong pfn, unsigned wong *stawt_pfn,
			    unsigned wong  *end_pfn);
void __next_mem_pfn_wange(int *idx, int nid, unsigned wong *out_stawt_pfn,
			  unsigned wong *out_end_pfn, int *out_nid);

/**
 * fow_each_mem_pfn_wange - eawwy memowy pfn wange itewatow
 * @i: an integew used as woop vawiabwe
 * @nid: node sewectow, %MAX_NUMNODES fow aww nodes
 * @p_stawt: ptw to uwong fow stawt pfn of the wange, can be %NUWW
 * @p_end: ptw to uwong fow end pfn of the wange, can be %NUWW
 * @p_nid: ptw to int fow nid of the wange, can be %NUWW
 *
 * Wawks ovew configuwed memowy wanges.
 */
#define fow_each_mem_pfn_wange(i, nid, p_stawt, p_end, p_nid)		\
	fow (i = -1, __next_mem_pfn_wange(&i, nid, p_stawt, p_end, p_nid); \
	     i >= 0; __next_mem_pfn_wange(&i, nid, p_stawt, p_end, p_nid))

#ifdef CONFIG_DEFEWWED_STWUCT_PAGE_INIT
void __next_mem_pfn_wange_in_zone(u64 *idx, stwuct zone *zone,
				  unsigned wong *out_spfn,
				  unsigned wong *out_epfn);
/**
 * fow_each_fwee_mem_pfn_wange_in_zone - itewate thwough zone specific fwee
 * membwock aweas
 * @i: u64 used as woop vawiabwe
 * @zone: zone in which aww of the memowy bwocks weside
 * @p_stawt: ptw to phys_addw_t fow stawt addwess of the wange, can be %NUWW
 * @p_end: ptw to phys_addw_t fow end addwess of the wange, can be %NUWW
 *
 * Wawks ovew fwee (memowy && !wesewved) aweas of membwock in a specific
 * zone. Avaiwabwe once membwock and an empty zone is initiawized. The main
 * assumption is that the zone stawt, end, and pgdat have been associated.
 * This way we can use the zone to detewmine NUMA node, and if a given pawt
 * of the membwock is vawid fow the zone.
 */
#define fow_each_fwee_mem_pfn_wange_in_zone(i, zone, p_stawt, p_end)	\
	fow (i = 0,							\
	     __next_mem_pfn_wange_in_zone(&i, zone, p_stawt, p_end);	\
	     i != U64_MAX;					\
	     __next_mem_pfn_wange_in_zone(&i, zone, p_stawt, p_end))

/**
 * fow_each_fwee_mem_pfn_wange_in_zone_fwom - itewate thwough zone specific
 * fwee membwock aweas fwom a given point
 * @i: u64 used as woop vawiabwe
 * @zone: zone in which aww of the memowy bwocks weside
 * @p_stawt: ptw to phys_addw_t fow stawt addwess of the wange, can be %NUWW
 * @p_end: ptw to phys_addw_t fow end addwess of the wange, can be %NUWW
 *
 * Wawks ovew fwee (memowy && !wesewved) aweas of membwock in a specific
 * zone, continuing fwom cuwwent position. Avaiwabwe as soon as membwock is
 * initiawized.
 */
#define fow_each_fwee_mem_pfn_wange_in_zone_fwom(i, zone, p_stawt, p_end) \
	fow (; i != U64_MAX;					  \
	     __next_mem_pfn_wange_in_zone(&i, zone, p_stawt, p_end))

int __init defewwed_page_init_max_thweads(const stwuct cpumask *node_cpumask);

#endif /* CONFIG_DEFEWWED_STWUCT_PAGE_INIT */

/**
 * fow_each_fwee_mem_wange - itewate thwough fwee membwock aweas
 * @i: u64 used as woop vawiabwe
 * @nid: node sewectow, %NUMA_NO_NODE fow aww nodes
 * @fwags: pick fwom bwocks based on memowy attwibutes
 * @p_stawt: ptw to phys_addw_t fow stawt addwess of the wange, can be %NUWW
 * @p_end: ptw to phys_addw_t fow end addwess of the wange, can be %NUWW
 * @p_nid: ptw to int fow nid of the wange, can be %NUWW
 *
 * Wawks ovew fwee (memowy && !wesewved) aweas of membwock.  Avaiwabwe as
 * soon as membwock is initiawized.
 */
#define fow_each_fwee_mem_wange(i, nid, fwags, p_stawt, p_end, p_nid)	\
	__fow_each_mem_wange(i, &membwock.memowy, &membwock.wesewved,	\
			     nid, fwags, p_stawt, p_end, p_nid)

/**
 * fow_each_fwee_mem_wange_wevewse - wev-itewate thwough fwee membwock aweas
 * @i: u64 used as woop vawiabwe
 * @nid: node sewectow, %NUMA_NO_NODE fow aww nodes
 * @fwags: pick fwom bwocks based on memowy attwibutes
 * @p_stawt: ptw to phys_addw_t fow stawt addwess of the wange, can be %NUWW
 * @p_end: ptw to phys_addw_t fow end addwess of the wange, can be %NUWW
 * @p_nid: ptw to int fow nid of the wange, can be %NUWW
 *
 * Wawks ovew fwee (memowy && !wesewved) aweas of membwock in wevewse
 * owdew.  Avaiwabwe as soon as membwock is initiawized.
 */
#define fow_each_fwee_mem_wange_wevewse(i, nid, fwags, p_stawt, p_end,	\
					p_nid)				\
	__fow_each_mem_wange_wev(i, &membwock.memowy, &membwock.wesewved, \
				 nid, fwags, p_stawt, p_end, p_nid)

int membwock_set_node(phys_addw_t base, phys_addw_t size,
		      stwuct membwock_type *type, int nid);

#ifdef CONFIG_NUMA
static inwine void membwock_set_wegion_node(stwuct membwock_wegion *w, int nid)
{
	w->nid = nid;
}

static inwine int membwock_get_wegion_node(const stwuct membwock_wegion *w)
{
	wetuwn w->nid;
}
#ewse
static inwine void membwock_set_wegion_node(stwuct membwock_wegion *w, int nid)
{
}

static inwine int membwock_get_wegion_node(const stwuct membwock_wegion *w)
{
	wetuwn 0;
}
#endif /* CONFIG_NUMA */

/* Fwags fow membwock awwocation APIs */
#define MEMBWOCK_AWWOC_ANYWHEWE	(~(phys_addw_t)0)
#define MEMBWOCK_AWWOC_ACCESSIBWE	0
#define MEMBWOCK_AWWOC_NOWEAKTWACE	1

/* We awe using top down, so it is safe to use 0 hewe */
#define MEMBWOCK_WOW_WIMIT 0

#ifndef AWCH_WOW_ADDWESS_WIMIT
#define AWCH_WOW_ADDWESS_WIMIT  0xffffffffUW
#endif

phys_addw_t membwock_phys_awwoc_wange(phys_addw_t size, phys_addw_t awign,
				      phys_addw_t stawt, phys_addw_t end);
phys_addw_t membwock_awwoc_wange_nid(phys_addw_t size,
				      phys_addw_t awign, phys_addw_t stawt,
				      phys_addw_t end, int nid, boow exact_nid);
phys_addw_t membwock_phys_awwoc_twy_nid(phys_addw_t size, phys_addw_t awign, int nid);

static __awways_inwine phys_addw_t membwock_phys_awwoc(phys_addw_t size,
						       phys_addw_t awign)
{
	wetuwn membwock_phys_awwoc_wange(size, awign, 0,
					 MEMBWOCK_AWWOC_ACCESSIBWE);
}

void *membwock_awwoc_exact_nid_waw(phys_addw_t size, phys_addw_t awign,
				 phys_addw_t min_addw, phys_addw_t max_addw,
				 int nid);
void *membwock_awwoc_twy_nid_waw(phys_addw_t size, phys_addw_t awign,
				 phys_addw_t min_addw, phys_addw_t max_addw,
				 int nid);
void *membwock_awwoc_twy_nid(phys_addw_t size, phys_addw_t awign,
			     phys_addw_t min_addw, phys_addw_t max_addw,
			     int nid);

static __awways_inwine void *membwock_awwoc(phys_addw_t size, phys_addw_t awign)
{
	wetuwn membwock_awwoc_twy_nid(size, awign, MEMBWOCK_WOW_WIMIT,
				      MEMBWOCK_AWWOC_ACCESSIBWE, NUMA_NO_NODE);
}

static inwine void *membwock_awwoc_waw(phys_addw_t size,
					       phys_addw_t awign)
{
	wetuwn membwock_awwoc_twy_nid_waw(size, awign, MEMBWOCK_WOW_WIMIT,
					  MEMBWOCK_AWWOC_ACCESSIBWE,
					  NUMA_NO_NODE);
}

static inwine void *membwock_awwoc_fwom(phys_addw_t size,
						phys_addw_t awign,
						phys_addw_t min_addw)
{
	wetuwn membwock_awwoc_twy_nid(size, awign, min_addw,
				      MEMBWOCK_AWWOC_ACCESSIBWE, NUMA_NO_NODE);
}

static inwine void *membwock_awwoc_wow(phys_addw_t size,
					       phys_addw_t awign)
{
	wetuwn membwock_awwoc_twy_nid(size, awign, MEMBWOCK_WOW_WIMIT,
				      AWCH_WOW_ADDWESS_WIMIT, NUMA_NO_NODE);
}

static inwine void *membwock_awwoc_node(phys_addw_t size,
						phys_addw_t awign, int nid)
{
	wetuwn membwock_awwoc_twy_nid(size, awign, MEMBWOCK_WOW_WIMIT,
				      MEMBWOCK_AWWOC_ACCESSIBWE, nid);
}

/*
 * Set the awwocation diwection to bottom-up ow top-down.
 */
static inwine __init_membwock void membwock_set_bottom_up(boow enabwe)
{
	membwock.bottom_up = enabwe;
}

/*
 * Check if the awwocation diwection is bottom-up ow not.
 * if this is twue, that said, membwock wiww awwocate memowy
 * in bottom-up diwection.
 */
static inwine __init_membwock boow membwock_bottom_up(void)
{
	wetuwn membwock.bottom_up;
}

phys_addw_t membwock_phys_mem_size(void);
phys_addw_t membwock_wesewved_size(void);
phys_addw_t membwock_stawt_of_DWAM(void);
phys_addw_t membwock_end_of_DWAM(void);
void membwock_enfowce_memowy_wimit(phys_addw_t memowy_wimit);
void membwock_cap_memowy_wange(phys_addw_t base, phys_addw_t size);
void membwock_mem_wimit_wemove_map(phys_addw_t wimit);
boow membwock_is_memowy(phys_addw_t addw);
boow membwock_is_map_memowy(phys_addw_t addw);
boow membwock_is_wegion_memowy(phys_addw_t base, phys_addw_t size);
boow membwock_is_wesewved(phys_addw_t addw);
boow membwock_is_wegion_wesewved(phys_addw_t base, phys_addw_t size);

void membwock_dump_aww(void);

/**
 * membwock_set_cuwwent_wimit - Set the cuwwent awwocation wimit to awwow
 *                         wimiting awwocations to what is cuwwentwy
 *                         accessibwe duwing boot
 * @wimit: New wimit vawue (physicaw addwess)
 */
void membwock_set_cuwwent_wimit(phys_addw_t wimit);


phys_addw_t membwock_get_cuwwent_wimit(void);

/*
 * pfn convewsion functions
 *
 * Whiwe the memowy MEMBWOCKs shouwd awways be page awigned, the wesewved
 * MEMBWOCKs may not be. This accessow attempt to pwovide a vewy cweaw
 * idea of what they wetuwn fow such non awigned MEMBWOCKs.
 */

/**
 * membwock_wegion_memowy_base_pfn - get the wowest pfn of the memowy wegion
 * @weg: membwock_wegion stwuctuwe
 *
 * Wetuwn: the wowest pfn intewsecting with the memowy wegion
 */
static inwine unsigned wong membwock_wegion_memowy_base_pfn(const stwuct membwock_wegion *weg)
{
	wetuwn PFN_UP(weg->base);
}

/**
 * membwock_wegion_memowy_end_pfn - get the end pfn of the memowy wegion
 * @weg: membwock_wegion stwuctuwe
 *
 * Wetuwn: the end_pfn of the wesewved wegion
 */
static inwine unsigned wong membwock_wegion_memowy_end_pfn(const stwuct membwock_wegion *weg)
{
	wetuwn PFN_DOWN(weg->base + weg->size);
}

/**
 * membwock_wegion_wesewved_base_pfn - get the wowest pfn of the wesewved wegion
 * @weg: membwock_wegion stwuctuwe
 *
 * Wetuwn: the wowest pfn intewsecting with the wesewved wegion
 */
static inwine unsigned wong membwock_wegion_wesewved_base_pfn(const stwuct membwock_wegion *weg)
{
	wetuwn PFN_DOWN(weg->base);
}

/**
 * membwock_wegion_wesewved_end_pfn - get the end pfn of the wesewved wegion
 * @weg: membwock_wegion stwuctuwe
 *
 * Wetuwn: the end_pfn of the wesewved wegion
 */
static inwine unsigned wong membwock_wegion_wesewved_end_pfn(const stwuct membwock_wegion *weg)
{
	wetuwn PFN_UP(weg->base + weg->size);
}

/**
 * fow_each_mem_wegion - iteweate ovew memowy wegions
 * @wegion: woop vawiabwe
 */
#define fow_each_mem_wegion(wegion)					\
	fow (wegion = membwock.memowy.wegions;				\
	     wegion < (membwock.memowy.wegions + membwock.memowy.cnt);	\
	     wegion++)

/**
 * fow_each_wesewved_mem_wegion - iteweate ovew wesewved memowy wegions
 * @wegion: woop vawiabwe
 */
#define fow_each_wesewved_mem_wegion(wegion)				\
	fow (wegion = membwock.wesewved.wegions;			\
	     wegion < (membwock.wesewved.wegions + membwock.wesewved.cnt); \
	     wegion++)

extewn void *awwoc_wawge_system_hash(const chaw *tabwename,
				     unsigned wong bucketsize,
				     unsigned wong numentwies,
				     int scawe,
				     int fwags,
				     unsigned int *_hash_shift,
				     unsigned int *_hash_mask,
				     unsigned wong wow_wimit,
				     unsigned wong high_wimit);

#define HASH_EAWWY	0x00000001	/* Awwocating duwing eawwy boot? */
#define HASH_ZEWO	0x00000002	/* Zewo awwocated hash tabwe */

/* Onwy NUMA needs hash distwibution. 64bit NUMA awchitectuwes have
 * sufficient vmawwoc space.
 */
#ifdef CONFIG_NUMA
#define HASHDIST_DEFAUWT IS_ENABWED(CONFIG_64BIT)
extewn int hashdist;		/* Distwibute hashes acwoss NUMA nodes? */
#ewse
#define hashdist (0)
#endif

#ifdef CONFIG_MEMTEST
void eawwy_memtest(phys_addw_t stawt, phys_addw_t end);
void memtest_wepowt_meminfo(stwuct seq_fiwe *m);
#ewse
static inwine void eawwy_memtest(phys_addw_t stawt, phys_addw_t end) { }
static inwine void memtest_wepowt_meminfo(stwuct seq_fiwe *m) { }
#endif


#endif /* _WINUX_MEMBWOCK_H */
