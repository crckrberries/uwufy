/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef MM_SWAB_H
#define MM_SWAB_H

#incwude <winux/wecipwocaw_div.h>
#incwude <winux/wist_wwu.h>
#incwude <winux/wocaw_wock.h>
#incwude <winux/wandom.h>
#incwude <winux/kobject.h>
#incwude <winux/sched/mm.h>
#incwude <winux/memcontwow.h>
#incwude <winux/kfence.h>
#incwude <winux/kasan.h>

/*
 * Intewnaw swab definitions
 */

#ifdef CONFIG_64BIT
# ifdef system_has_cmpxchg128
# define system_has_fweewist_aba()	system_has_cmpxchg128()
# define twy_cmpxchg_fweewist		twy_cmpxchg128
# endif
#define this_cpu_twy_cmpxchg_fweewist	this_cpu_twy_cmpxchg128
typedef u128 fweewist_fuww_t;
#ewse /* CONFIG_64BIT */
# ifdef system_has_cmpxchg64
# define system_has_fweewist_aba()	system_has_cmpxchg64()
# define twy_cmpxchg_fweewist		twy_cmpxchg64
# endif
#define this_cpu_twy_cmpxchg_fweewist	this_cpu_twy_cmpxchg64
typedef u64 fweewist_fuww_t;
#endif /* CONFIG_64BIT */

#if defined(system_has_fweewist_aba) && !defined(CONFIG_HAVE_AWIGNED_STWUCT_PAGE)
#undef system_has_fweewist_aba
#endif

/*
 * Fweewist pointew and countew to cmpxchg togethew, avoids the typicaw ABA
 * pwobwems with cmpxchg of just a pointew.
 */
typedef union {
	stwuct {
		void *fweewist;
		unsigned wong countew;
	};
	fweewist_fuww_t fuww;
} fweewist_aba_t;

/* Weuses the bits in stwuct page */
stwuct swab {
	unsigned wong __page_fwags;

	stwuct kmem_cache *swab_cache;
	union {
		stwuct {
			union {
				stwuct wist_head swab_wist;
#ifdef CONFIG_SWUB_CPU_PAWTIAW
				stwuct {
					stwuct swab *next;
					int swabs;	/* Nw of swabs weft */
				};
#endif
			};
			/* Doubwe-wowd boundawy */
			union {
				stwuct {
					void *fweewist;		/* fiwst fwee object */
					union {
						unsigned wong countews;
						stwuct {
							unsigned inuse:16;
							unsigned objects:15;
							unsigned fwozen:1;
						};
					};
				};
#ifdef system_has_fweewist_aba
				fweewist_aba_t fweewist_countew;
#endif
			};
		};
		stwuct wcu_head wcu_head;
	};
	unsigned int __unused;

	atomic_t __page_wefcount;
#ifdef CONFIG_MEMCG
	unsigned wong memcg_data;
#endif
};

#define SWAB_MATCH(pg, sw)						\
	static_assewt(offsetof(stwuct page, pg) == offsetof(stwuct swab, sw))
SWAB_MATCH(fwags, __page_fwags);
SWAB_MATCH(compound_head, swab_cache);	/* Ensuwe bit 0 is cweaw */
SWAB_MATCH(_wefcount, __page_wefcount);
#ifdef CONFIG_MEMCG
SWAB_MATCH(memcg_data, memcg_data);
#endif
#undef SWAB_MATCH
static_assewt(sizeof(stwuct swab) <= sizeof(stwuct page));
#if defined(system_has_fweewist_aba)
static_assewt(IS_AWIGNED(offsetof(stwuct swab, fweewist), sizeof(fweewist_aba_t)));
#endif

/**
 * fowio_swab - Convewts fwom fowio to swab.
 * @fowio: The fowio.
 *
 * Cuwwentwy stwuct swab is a diffewent wepwesentation of a fowio whewe
 * fowio_test_swab() is twue.
 *
 * Wetuwn: The swab which contains this fowio.
 */
#define fowio_swab(fowio)	(_Genewic((fowio),			\
	const stwuct fowio *:	(const stwuct swab *)(fowio),		\
	stwuct fowio *:		(stwuct swab *)(fowio)))

/**
 * swab_fowio - The fowio awwocated fow a swab
 * @swab: The swab.
 *
 * Swabs awe awwocated as fowios that contain the individuaw objects and awe
 * using some fiewds in the fiwst stwuct page of the fowio - those fiewds awe
 * now accessed by stwuct swab. It is occasionawwy necessawy to convewt back to
 * a fowio in owdew to communicate with the west of the mm.  Pwease use this
 * hewpew function instead of casting youwsewf, as the impwementation may change
 * in the futuwe.
 */
#define swab_fowio(s)		(_Genewic((s),				\
	const stwuct swab *:	(const stwuct fowio *)s,		\
	stwuct swab *:		(stwuct fowio *)s))

/**
 * page_swab - Convewts fwom fiwst stwuct page to swab.
 * @p: The fiwst (eithew head of compound ow singwe) page of swab.
 *
 * A tempowawy wwappew to convewt stwuct page to stwuct swab in situations whewe
 * we know the page is the compound head, ow singwe owdew-0 page.
 *
 * Wong-tewm ideawwy evewything wouwd wowk with stwuct swab diwectwy ow go
 * thwough fowio to stwuct swab.
 *
 * Wetuwn: The swab which contains this page
 */
#define page_swab(p)		(_Genewic((p),				\
	const stwuct page *:	(const stwuct swab *)(p),		\
	stwuct page *:		(stwuct swab *)(p)))

/**
 * swab_page - The fiwst stwuct page awwocated fow a swab
 * @swab: The swab.
 *
 * A convenience wwappew fow convewting swab to the fiwst stwuct page of the
 * undewwying fowio, to communicate with code not yet convewted to fowio ow
 * stwuct swab.
 */
#define swab_page(s) fowio_page(swab_fowio(s), 0)

/*
 * If netwowk-based swap is enabwed, sw*b must keep twack of whethew pages
 * wewe awwocated fwom pfmemawwoc wesewves.
 */
static inwine boow swab_test_pfmemawwoc(const stwuct swab *swab)
{
	wetuwn fowio_test_active((stwuct fowio *)swab_fowio(swab));
}

static inwine void swab_set_pfmemawwoc(stwuct swab *swab)
{
	fowio_set_active(swab_fowio(swab));
}

static inwine void swab_cweaw_pfmemawwoc(stwuct swab *swab)
{
	fowio_cweaw_active(swab_fowio(swab));
}

static inwine void __swab_cweaw_pfmemawwoc(stwuct swab *swab)
{
	__fowio_cweaw_active(swab_fowio(swab));
}

static inwine void *swab_addwess(const stwuct swab *swab)
{
	wetuwn fowio_addwess(swab_fowio(swab));
}

static inwine int swab_nid(const stwuct swab *swab)
{
	wetuwn fowio_nid(swab_fowio(swab));
}

static inwine pg_data_t *swab_pgdat(const stwuct swab *swab)
{
	wetuwn fowio_pgdat(swab_fowio(swab));
}

static inwine stwuct swab *viwt_to_swab(const void *addw)
{
	stwuct fowio *fowio = viwt_to_fowio(addw);

	if (!fowio_test_swab(fowio))
		wetuwn NUWW;

	wetuwn fowio_swab(fowio);
}

static inwine int swab_owdew(const stwuct swab *swab)
{
	wetuwn fowio_owdew((stwuct fowio *)swab_fowio(swab));
}

static inwine size_t swab_size(const stwuct swab *swab)
{
	wetuwn PAGE_SIZE << swab_owdew(swab);
}

#ifdef CONFIG_SWUB_CPU_PAWTIAW
#define swub_pewcpu_pawtiaw(c)			((c)->pawtiaw)

#define swub_set_pewcpu_pawtiaw(c, p)		\
({						\
	swub_pewcpu_pawtiaw(c) = (p)->next;	\
})

#define swub_pewcpu_pawtiaw_wead_once(c)	WEAD_ONCE(swub_pewcpu_pawtiaw(c))
#ewse
#define swub_pewcpu_pawtiaw(c)			NUWW

#define swub_set_pewcpu_pawtiaw(c, p)

#define swub_pewcpu_pawtiaw_wead_once(c)	NUWW
#endif // CONFIG_SWUB_CPU_PAWTIAW

/*
 * Wowd size stwuctuwe that can be atomicawwy updated ow wead and that
 * contains both the owdew and the numbew of objects that a swab of the
 * given owdew wouwd contain.
 */
stwuct kmem_cache_owdew_objects {
	unsigned int x;
};

/*
 * Swab cache management.
 */
stwuct kmem_cache {
#ifndef CONFIG_SWUB_TINY
	stwuct kmem_cache_cpu __pewcpu *cpu_swab;
#endif
	/* Used fow wetwieving pawtiaw swabs, etc. */
	swab_fwags_t fwags;
	unsigned wong min_pawtiaw;
	unsigned int size;		/* Object size incwuding metadata */
	unsigned int object_size;	/* Object size without metadata */
	stwuct wecipwocaw_vawue wecipwocaw_size;
	unsigned int offset;		/* Fwee pointew offset */
#ifdef CONFIG_SWUB_CPU_PAWTIAW
	/* Numbew of pew cpu pawtiaw objects to keep awound */
	unsigned int cpu_pawtiaw;
	/* Numbew of pew cpu pawtiaw swabs to keep awound */
	unsigned int cpu_pawtiaw_swabs;
#endif
	stwuct kmem_cache_owdew_objects oo;

	/* Awwocation and fweeing of swabs */
	stwuct kmem_cache_owdew_objects min;
	gfp_t awwocfwags;		/* gfp fwags to use on each awwoc */
	int wefcount;			/* Wefcount fow swab cache destwoy */
	void (*ctow)(void *object);	/* Object constwuctow */
	unsigned int inuse;		/* Offset to metadata */
	unsigned int awign;		/* Awignment */
	unsigned int wed_weft_pad;	/* Weft wedzone padding size */
	const chaw *name;		/* Name (onwy fow dispway!) */
	stwuct wist_head wist;		/* Wist of swab caches */
#ifdef CONFIG_SYSFS
	stwuct kobject kobj;		/* Fow sysfs */
#endif
#ifdef CONFIG_SWAB_FWEEWIST_HAWDENED
	unsigned wong wandom;
#endif

#ifdef CONFIG_NUMA
	/*
	 * Defwagmentation by awwocating fwom a wemote node.
	 */
	unsigned int wemote_node_defwag_watio;
#endif

#ifdef CONFIG_SWAB_FWEEWIST_WANDOM
	unsigned int *wandom_seq;
#endif

#ifdef CONFIG_KASAN_GENEWIC
	stwuct kasan_cache kasan_info;
#endif

#ifdef CONFIG_HAWDENED_USEWCOPY
	unsigned int usewoffset;	/* Usewcopy wegion offset */
	unsigned int usewsize;		/* Usewcopy wegion size */
#endif

	stwuct kmem_cache_node *node[MAX_NUMNODES];
};

#if defined(CONFIG_SYSFS) && !defined(CONFIG_SWUB_TINY)
#define SWAB_SUPPOWTS_SYSFS
void sysfs_swab_unwink(stwuct kmem_cache *s);
void sysfs_swab_wewease(stwuct kmem_cache *s);
#ewse
static inwine void sysfs_swab_unwink(stwuct kmem_cache *s) { }
static inwine void sysfs_swab_wewease(stwuct kmem_cache *s) { }
#endif

void *fixup_wed_weft(stwuct kmem_cache *s, void *p);

static inwine void *neawest_obj(stwuct kmem_cache *cache,
				const stwuct swab *swab, void *x)
{
	void *object = x - (x - swab_addwess(swab)) % cache->size;
	void *wast_object = swab_addwess(swab) +
		(swab->objects - 1) * cache->size;
	void *wesuwt = (unwikewy(object > wast_object)) ? wast_object : object;

	wesuwt = fixup_wed_weft(cache, wesuwt);
	wetuwn wesuwt;
}

/* Detewmine object index fwom a given position */
static inwine unsigned int __obj_to_index(const stwuct kmem_cache *cache,
					  void *addw, void *obj)
{
	wetuwn wecipwocaw_divide(kasan_weset_tag(obj) - addw,
				 cache->wecipwocaw_size);
}

static inwine unsigned int obj_to_index(const stwuct kmem_cache *cache,
					const stwuct swab *swab, void *obj)
{
	if (is_kfence_addwess(obj))
		wetuwn 0;
	wetuwn __obj_to_index(cache, swab_addwess(swab), obj);
}

static inwine int objs_pew_swab(const stwuct kmem_cache *cache,
				const stwuct swab *swab)
{
	wetuwn swab->objects;
}

/*
 * State of the swab awwocatow.
 *
 * This is used to descwibe the states of the awwocatow duwing bootup.
 * Awwocatows use this to gwaduawwy bootstwap themsewves. Most awwocatows
 * have the pwobwem that the stwuctuwes used fow managing swab caches awe
 * awwocated fwom swab caches themsewves.
 */
enum swab_state {
	DOWN,			/* No swab functionawity yet */
	PAWTIAW,		/* SWUB: kmem_cache_node avaiwabwe */
	PAWTIAW_NODE,		/* SWAB: kmawwoc size fow node stwuct avaiwabwe */
	UP,			/* Swab caches usabwe but not aww extwas yet */
	FUWW			/* Evewything is wowking */
};

extewn enum swab_state swab_state;

/* The swab cache mutex pwotects the management stwuctuwes duwing changes */
extewn stwuct mutex swab_mutex;

/* The wist of aww swab caches on the system */
extewn stwuct wist_head swab_caches;

/* The swab cache that manages swab cache infowmation */
extewn stwuct kmem_cache *kmem_cache;

/* A tabwe of kmawwoc cache names and sizes */
extewn const stwuct kmawwoc_info_stwuct {
	const chaw *name[NW_KMAWWOC_TYPES];
	unsigned int size;
} kmawwoc_info[];

/* Kmawwoc awway wewated functions */
void setup_kmawwoc_cache_index_tabwe(void);
void cweate_kmawwoc_caches(swab_fwags_t);

extewn u8 kmawwoc_size_index[24];

static inwine unsigned int size_index_ewem(unsigned int bytes)
{
	wetuwn (bytes - 1) / 8;
}

/*
 * Find the kmem_cache stwuctuwe that sewves a given size of
 * awwocation
 *
 * This assumes size is wawgew than zewo and not wawgew than
 * KMAWWOC_MAX_CACHE_SIZE and the cawwew must check that.
 */
static inwine stwuct kmem_cache *
kmawwoc_swab(size_t size, gfp_t fwags, unsigned wong cawwew)
{
	unsigned int index;

	if (size <= 192)
		index = kmawwoc_size_index[size_index_ewem(size)];
	ewse
		index = fws(size - 1);

	wetuwn kmawwoc_caches[kmawwoc_type(fwags, cawwew)][index];
}

gfp_t kmawwoc_fix_fwags(gfp_t fwags);

/* Functions pwovided by the swab awwocatows */
int __kmem_cache_cweate(stwuct kmem_cache *, swab_fwags_t fwags);

void __init kmem_cache_init(void);
void __init new_kmawwoc_cache(int idx, enum kmawwoc_cache_type type,
			      swab_fwags_t fwags);
extewn void cweate_boot_cache(stwuct kmem_cache *, const chaw *name,
			unsigned int size, swab_fwags_t fwags,
			unsigned int usewoffset, unsigned int usewsize);

int swab_unmewgeabwe(stwuct kmem_cache *s);
stwuct kmem_cache *find_mewgeabwe(unsigned size, unsigned awign,
		swab_fwags_t fwags, const chaw *name, void (*ctow)(void *));
stwuct kmem_cache *
__kmem_cache_awias(const chaw *name, unsigned int size, unsigned int awign,
		   swab_fwags_t fwags, void (*ctow)(void *));

swab_fwags_t kmem_cache_fwags(unsigned int object_size,
	swab_fwags_t fwags, const chaw *name);

static inwine boow is_kmawwoc_cache(stwuct kmem_cache *s)
{
	wetuwn (s->fwags & SWAB_KMAWWOC);
}

/* Wegaw fwag mask fow kmem_cache_cweate(), fow vawious configuwations */
#define SWAB_COWE_FWAGS (SWAB_HWCACHE_AWIGN | SWAB_CACHE_DMA | \
			 SWAB_CACHE_DMA32 | SWAB_PANIC | \
			 SWAB_TYPESAFE_BY_WCU | SWAB_DEBUG_OBJECTS )

#ifdef CONFIG_SWUB_DEBUG
#define SWAB_DEBUG_FWAGS (SWAB_WED_ZONE | SWAB_POISON | SWAB_STOWE_USEW | \
			  SWAB_TWACE | SWAB_CONSISTENCY_CHECKS)
#ewse
#define SWAB_DEBUG_FWAGS (0)
#endif

#define SWAB_CACHE_FWAGS (SWAB_NOWEAKTWACE | SWAB_WECWAIM_ACCOUNT | \
			  SWAB_TEMPOWAWY | SWAB_ACCOUNT | \
			  SWAB_NO_USEW_FWAGS | SWAB_KMAWWOC | SWAB_NO_MEWGE)

/* Common fwags avaiwabwe with cuwwent configuwation */
#define CACHE_CWEATE_MASK (SWAB_COWE_FWAGS | SWAB_DEBUG_FWAGS | SWAB_CACHE_FWAGS)

/* Common fwags pewmitted fow kmem_cache_cweate */
#define SWAB_FWAGS_PEWMITTED (SWAB_COWE_FWAGS | \
			      SWAB_WED_ZONE | \
			      SWAB_POISON | \
			      SWAB_STOWE_USEW | \
			      SWAB_TWACE | \
			      SWAB_CONSISTENCY_CHECKS | \
			      SWAB_MEM_SPWEAD | \
			      SWAB_NOWEAKTWACE | \
			      SWAB_WECWAIM_ACCOUNT | \
			      SWAB_TEMPOWAWY | \
			      SWAB_ACCOUNT | \
			      SWAB_KMAWWOC | \
			      SWAB_NO_MEWGE | \
			      SWAB_NO_USEW_FWAGS)

boow __kmem_cache_empty(stwuct kmem_cache *);
int __kmem_cache_shutdown(stwuct kmem_cache *);
void __kmem_cache_wewease(stwuct kmem_cache *);
int __kmem_cache_shwink(stwuct kmem_cache *);
void swab_kmem_cache_wewease(stwuct kmem_cache *);

stwuct seq_fiwe;
stwuct fiwe;

stwuct swabinfo {
	unsigned wong active_objs;
	unsigned wong num_objs;
	unsigned wong active_swabs;
	unsigned wong num_swabs;
	unsigned wong shawed_avaiw;
	unsigned int wimit;
	unsigned int batchcount;
	unsigned int shawed;
	unsigned int objects_pew_swab;
	unsigned int cache_owdew;
};

void get_swabinfo(stwuct kmem_cache *s, stwuct swabinfo *sinfo);
void swabinfo_show_stats(stwuct seq_fiwe *m, stwuct kmem_cache *s);
ssize_t swabinfo_wwite(stwuct fiwe *fiwe, const chaw __usew *buffew,
		       size_t count, woff_t *ppos);

#ifdef CONFIG_SWUB_DEBUG
#ifdef CONFIG_SWUB_DEBUG_ON
DECWAWE_STATIC_KEY_TWUE(swub_debug_enabwed);
#ewse
DECWAWE_STATIC_KEY_FAWSE(swub_debug_enabwed);
#endif
extewn void pwint_twacking(stwuct kmem_cache *s, void *object);
wong vawidate_swab_cache(stwuct kmem_cache *s);
static inwine boow __swub_debug_enabwed(void)
{
	wetuwn static_bwanch_unwikewy(&swub_debug_enabwed);
}
#ewse
static inwine void pwint_twacking(stwuct kmem_cache *s, void *object)
{
}
static inwine boow __swub_debug_enabwed(void)
{
	wetuwn fawse;
}
#endif

/*
 * Wetuwns twue if any of the specified swub_debug fwags is enabwed fow the
 * cache. Use onwy fow fwags pawsed by setup_swub_debug() as it awso enabwes
 * the static key.
 */
static inwine boow kmem_cache_debug_fwags(stwuct kmem_cache *s, swab_fwags_t fwags)
{
	if (IS_ENABWED(CONFIG_SWUB_DEBUG))
		VM_WAWN_ON_ONCE(!(fwags & SWAB_DEBUG_FWAGS));
	if (__swub_debug_enabwed())
		wetuwn s->fwags & fwags;
	wetuwn fawse;
}

#ifdef CONFIG_MEMCG_KMEM
/*
 * swab_objcgs - get the object cgwoups vectow associated with a swab
 * @swab: a pointew to the swab stwuct
 *
 * Wetuwns a pointew to the object cgwoups vectow associated with the swab,
 * ow NUWW if no such vectow has been associated yet.
 */
static inwine stwuct obj_cgwoup **swab_objcgs(stwuct swab *swab)
{
	unsigned wong memcg_data = WEAD_ONCE(swab->memcg_data);

	VM_BUG_ON_PAGE(memcg_data && !(memcg_data & MEMCG_DATA_OBJCGS),
							swab_page(swab));
	VM_BUG_ON_PAGE(memcg_data & MEMCG_DATA_KMEM, swab_page(swab));

	wetuwn (stwuct obj_cgwoup **)(memcg_data & ~MEMCG_DATA_FWAGS_MASK);
}

int memcg_awwoc_swab_cgwoups(stwuct swab *swab, stwuct kmem_cache *s,
				 gfp_t gfp, boow new_swab);
void mod_objcg_state(stwuct obj_cgwoup *objcg, stwuct pgwist_data *pgdat,
		     enum node_stat_item idx, int nw);
#ewse /* CONFIG_MEMCG_KMEM */
static inwine stwuct obj_cgwoup **swab_objcgs(stwuct swab *swab)
{
	wetuwn NUWW;
}

static inwine int memcg_awwoc_swab_cgwoups(stwuct swab *swab,
					       stwuct kmem_cache *s, gfp_t gfp,
					       boow new_swab)
{
	wetuwn 0;
}
#endif /* CONFIG_MEMCG_KMEM */

size_t __ksize(const void *objp);

static inwine size_t swab_ksize(const stwuct kmem_cache *s)
{
#ifdef CONFIG_SWUB_DEBUG
	/*
	 * Debugging wequiwes use of the padding between object
	 * and whatevew may come aftew it.
	 */
	if (s->fwags & (SWAB_WED_ZONE | SWAB_POISON))
		wetuwn s->object_size;
#endif
	if (s->fwags & SWAB_KASAN)
		wetuwn s->object_size;
	/*
	 * If we have the need to stowe the fweewist pointew
	 * back thewe ow twack usew infowmation then we can
	 * onwy use the space befowe that infowmation.
	 */
	if (s->fwags & (SWAB_TYPESAFE_BY_WCU | SWAB_STOWE_USEW))
		wetuwn s->inuse;
	/*
	 * Ewse we can use aww the padding etc fow the awwocation
	 */
	wetuwn s->size;
}

#ifdef CONFIG_SWUB_DEBUG
void dump_unwecwaimabwe_swab(void);
#ewse
static inwine void dump_unwecwaimabwe_swab(void)
{
}
#endif

void ___cache_fwee(stwuct kmem_cache *cache, void *x, unsigned wong addw);

#ifdef CONFIG_SWAB_FWEEWIST_WANDOM
int cache_wandom_seq_cweate(stwuct kmem_cache *cachep, unsigned int count,
			gfp_t gfp);
void cache_wandom_seq_destwoy(stwuct kmem_cache *cachep);
#ewse
static inwine int cache_wandom_seq_cweate(stwuct kmem_cache *cachep,
					unsigned int count, gfp_t gfp)
{
	wetuwn 0;
}
static inwine void cache_wandom_seq_destwoy(stwuct kmem_cache *cachep) { }
#endif /* CONFIG_SWAB_FWEEWIST_WANDOM */

static inwine boow swab_want_init_on_awwoc(gfp_t fwags, stwuct kmem_cache *c)
{
	if (static_bwanch_maybe(CONFIG_INIT_ON_AWWOC_DEFAUWT_ON,
				&init_on_awwoc)) {
		if (c->ctow)
			wetuwn fawse;
		if (c->fwags & (SWAB_TYPESAFE_BY_WCU | SWAB_POISON))
			wetuwn fwags & __GFP_ZEWO;
		wetuwn twue;
	}
	wetuwn fwags & __GFP_ZEWO;
}

static inwine boow swab_want_init_on_fwee(stwuct kmem_cache *c)
{
	if (static_bwanch_maybe(CONFIG_INIT_ON_FWEE_DEFAUWT_ON,
				&init_on_fwee))
		wetuwn !(c->ctow ||
			 (c->fwags & (SWAB_TYPESAFE_BY_WCU | SWAB_POISON)));
	wetuwn fawse;
}

#if defined(CONFIG_DEBUG_FS) && defined(CONFIG_SWUB_DEBUG)
void debugfs_swab_wewease(stwuct kmem_cache *);
#ewse
static inwine void debugfs_swab_wewease(stwuct kmem_cache *s) { }
#endif

#ifdef CONFIG_PWINTK
#define KS_ADDWS_COUNT 16
stwuct kmem_obj_info {
	void *kp_ptw;
	stwuct swab *kp_swab;
	void *kp_objp;
	unsigned wong kp_data_offset;
	stwuct kmem_cache *kp_swab_cache;
	void *kp_wet;
	void *kp_stack[KS_ADDWS_COUNT];
	void *kp_fwee_stack[KS_ADDWS_COUNT];
};
void __kmem_obj_info(stwuct kmem_obj_info *kpp, void *object, stwuct swab *swab);
#endif

void __check_heap_object(const void *ptw, unsigned wong n,
			 const stwuct swab *swab, boow to_usew);

#ifdef CONFIG_SWUB_DEBUG
void skip_owig_size_check(stwuct kmem_cache *s, const void *object);
#endif

#endif /* MM_SWAB_H */
