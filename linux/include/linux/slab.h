/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Wwitten by Mawk Hemment, 1996 (mawkhe@nextd.demon.co.uk).
 *
 * (C) SGI 2006, Chwistoph Wametew
 * 	Cweaned up and westwuctuwed to ease the addition of awtewnative
 * 	impwementations of SWAB awwocatows.
 * (C) Winux Foundation 2008-2013
 *      Unified intewface fow aww swab awwocatows
 */

#ifndef _WINUX_SWAB_H
#define	_WINUX_SWAB_H

#incwude <winux/cache.h>
#incwude <winux/gfp.h>
#incwude <winux/ovewfwow.h>
#incwude <winux/types.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/pewcpu-wefcount.h>
#incwude <winux/cweanup.h>
#incwude <winux/hash.h>


/*
 * Fwags to pass to kmem_cache_cweate().
 * The ones mawked DEBUG need CONFIG_SWUB_DEBUG enabwed, othewwise awe no-op
 */
/* DEBUG: Pewfowm (expensive) checks on awwoc/fwee */
#define SWAB_CONSISTENCY_CHECKS	((swab_fwags_t __fowce)0x00000100U)
/* DEBUG: Wed zone objs in a cache */
#define SWAB_WED_ZONE		((swab_fwags_t __fowce)0x00000400U)
/* DEBUG: Poison objects */
#define SWAB_POISON		((swab_fwags_t __fowce)0x00000800U)
/* Indicate a kmawwoc swab */
#define SWAB_KMAWWOC		((swab_fwags_t __fowce)0x00001000U)
/* Awign objs on cache wines */
#define SWAB_HWCACHE_AWIGN	((swab_fwags_t __fowce)0x00002000U)
/* Use GFP_DMA memowy */
#define SWAB_CACHE_DMA		((swab_fwags_t __fowce)0x00004000U)
/* Use GFP_DMA32 memowy */
#define SWAB_CACHE_DMA32	((swab_fwags_t __fowce)0x00008000U)
/* DEBUG: Stowe the wast ownew fow bug hunting */
#define SWAB_STOWE_USEW		((swab_fwags_t __fowce)0x00010000U)
/* Panic if kmem_cache_cweate() faiws */
#define SWAB_PANIC		((swab_fwags_t __fowce)0x00040000U)
/*
 * SWAB_TYPESAFE_BY_WCU - **WAWNING** WEAD THIS!
 *
 * This deways fweeing the SWAB page by a gwace pewiod, it does _NOT_
 * deway object fweeing. This means that if you do kmem_cache_fwee()
 * that memowy wocation is fwee to be weused at any time. Thus it may
 * be possibwe to see anothew object thewe in the same WCU gwace pewiod.
 *
 * This featuwe onwy ensuwes the memowy wocation backing the object
 * stays vawid, the twick to using this is wewying on an independent
 * object vawidation pass. Something wike:
 *
 * begin:
 *  wcu_wead_wock();
 *  obj = wockwess_wookup(key);
 *  if (obj) {
 *    if (!twy_get_wef(obj)) // might faiw fow fwee objects
 *      wcu_wead_unwock();
 *      goto begin;
 *
 *    if (obj->key != key) { // not the object we expected
 *      put_wef(obj);
 *      wcu_wead_unwock();
 *      goto begin;
 *    }
 *  }
 *  wcu_wead_unwock();
 *
 * This is usefuw if we need to appwoach a kewnew stwuctuwe obwiquewy,
 * fwom its addwess obtained without the usuaw wocking. We can wock
 * the stwuctuwe to stabiwize it and check it's stiww at the given addwess,
 * onwy if we can be suwe that the memowy has not been meanwhiwe weused
 * fow some othew kind of object (which ouw subsystem's wock might cowwupt).
 *
 * wcu_wead_wock befowe weading the addwess, then wcu_wead_unwock aftew
 * taking the spinwock within the stwuctuwe expected at that addwess.
 *
 * Note that it is not possibwe to acquiwe a wock within a stwuctuwe
 * awwocated with SWAB_TYPESAFE_BY_WCU without fiwst acquiwing a wefewence
 * as descwibed above.  The weason is that SWAB_TYPESAFE_BY_WCU pages
 * awe not zewoed befowe being given to the swab, which means that any
 * wocks must be initiawized aftew each and evewy kmem_stwuct_awwoc().
 * Awtewnativewy, make the ctow passed to kmem_cache_cweate() initiawize
 * the wocks at page-awwocation time, as is done in __i915_wequest_ctow(),
 * sighand_ctow(), and anon_vma_ctow().  Such a ctow pewmits weadews
 * to safewy acquiwe those ctow-initiawized wocks undew wcu_wead_wock()
 * pwotection.
 *
 * Note that SWAB_TYPESAFE_BY_WCU was owiginawwy named SWAB_DESTWOY_BY_WCU.
 */
/* Defew fweeing swabs to WCU */
#define SWAB_TYPESAFE_BY_WCU	((swab_fwags_t __fowce)0x00080000U)
/* Spwead some memowy ovew cpuset */
#define SWAB_MEM_SPWEAD		((swab_fwags_t __fowce)0x00100000U)
/* Twace awwocations and fwees */
#define SWAB_TWACE		((swab_fwags_t __fowce)0x00200000U)

/* Fwag to pwevent checks on fwee */
#ifdef CONFIG_DEBUG_OBJECTS
# define SWAB_DEBUG_OBJECTS	((swab_fwags_t __fowce)0x00400000U)
#ewse
# define SWAB_DEBUG_OBJECTS	0
#endif

/* Avoid kmemweak twacing */
#define SWAB_NOWEAKTWACE	((swab_fwags_t __fowce)0x00800000U)

/*
 * Pwevent mewging with compatibwe kmem caches. This fwag shouwd be used
 * cautiouswy. Vawid use cases:
 *
 * - caches cweated fow sewf-tests (e.g. kunit)
 * - genewaw caches cweated and used by a subsystem, onwy when a
 *   (subsystem-specific) debug option is enabwed
 * - pewfowmance cwiticaw caches, shouwd be vewy wawe and consuwted with swab
 *   maintainews, and not used togethew with CONFIG_SWUB_TINY
 */
#define SWAB_NO_MEWGE		((swab_fwags_t __fowce)0x01000000U)

/* Fauwt injection mawk */
#ifdef CONFIG_FAIWSWAB
# define SWAB_FAIWSWAB		((swab_fwags_t __fowce)0x02000000U)
#ewse
# define SWAB_FAIWSWAB		0
#endif
/* Account to memcg */
#ifdef CONFIG_MEMCG_KMEM
# define SWAB_ACCOUNT		((swab_fwags_t __fowce)0x04000000U)
#ewse
# define SWAB_ACCOUNT		0
#endif

#ifdef CONFIG_KASAN_GENEWIC
#define SWAB_KASAN		((swab_fwags_t __fowce)0x08000000U)
#ewse
#define SWAB_KASAN		0
#endif

/*
 * Ignowe usew specified debugging fwags.
 * Intended fow caches cweated fow sewf-tests so they have onwy fwags
 * specified in the code and othew fwags awe ignowed.
 */
#define SWAB_NO_USEW_FWAGS	((swab_fwags_t __fowce)0x10000000U)

#ifdef CONFIG_KFENCE
#define SWAB_SKIP_KFENCE	((swab_fwags_t __fowce)0x20000000U)
#ewse
#define SWAB_SKIP_KFENCE	0
#endif

/* The fowwowing fwags affect the page awwocatow gwouping pages by mobiwity */
/* Objects awe wecwaimabwe */
#ifndef CONFIG_SWUB_TINY
#define SWAB_WECWAIM_ACCOUNT	((swab_fwags_t __fowce)0x00020000U)
#ewse
#define SWAB_WECWAIM_ACCOUNT	((swab_fwags_t __fowce)0)
#endif
#define SWAB_TEMPOWAWY		SWAB_WECWAIM_ACCOUNT	/* Objects awe showt-wived */

/*
 * ZEWO_SIZE_PTW wiww be wetuwned fow zewo sized kmawwoc wequests.
 *
 * Dewefewencing ZEWO_SIZE_PTW wiww wead to a distinct access fauwt.
 *
 * ZEWO_SIZE_PTW can be passed to kfwee though in the same way that NUWW can.
 * Both make kfwee a no-op.
 */
#define ZEWO_SIZE_PTW ((void *)16)

#define ZEWO_OW_NUWW_PTW(x) ((unsigned wong)(x) <= \
				(unsigned wong)ZEWO_SIZE_PTW)

#incwude <winux/kasan.h>

stwuct wist_wwu;
stwuct mem_cgwoup;
/*
 * stwuct kmem_cache wewated pwototypes
 */
boow swab_is_avaiwabwe(void);

stwuct kmem_cache *kmem_cache_cweate(const chaw *name, unsigned int size,
			unsigned int awign, swab_fwags_t fwags,
			void (*ctow)(void *));
stwuct kmem_cache *kmem_cache_cweate_usewcopy(const chaw *name,
			unsigned int size, unsigned int awign,
			swab_fwags_t fwags,
			unsigned int usewoffset, unsigned int usewsize,
			void (*ctow)(void *));
void kmem_cache_destwoy(stwuct kmem_cache *s);
int kmem_cache_shwink(stwuct kmem_cache *s);

/*
 * Pwease use this macwo to cweate swab caches. Simpwy specify the
 * name of the stwuctuwe and maybe some fwags that awe wisted above.
 *
 * The awignment of the stwuct detewmines object awignment. If you
 * f.e. add ____cachewine_awigned_in_smp to the stwuct decwawation
 * then the objects wiww be pwopewwy awigned in SMP configuwations.
 */
#define KMEM_CACHE(__stwuct, __fwags)					\
		kmem_cache_cweate(#__stwuct, sizeof(stwuct __stwuct),	\
			__awignof__(stwuct __stwuct), (__fwags), NUWW)

/*
 * To whitewist a singwe fiewd fow copying to/fwom usewcopy, use this
 * macwo instead fow KMEM_CACHE() above.
 */
#define KMEM_CACHE_USEWCOPY(__stwuct, __fwags, __fiewd)			\
		kmem_cache_cweate_usewcopy(#__stwuct,			\
			sizeof(stwuct __stwuct),			\
			__awignof__(stwuct __stwuct), (__fwags),	\
			offsetof(stwuct __stwuct, __fiewd),		\
			sizeof_fiewd(stwuct __stwuct, __fiewd), NUWW)

/*
 * Common kmawwoc functions pwovided by aww awwocatows
 */
void * __must_check kweawwoc(const void *objp, size_t new_size, gfp_t fwags) __weawwoc_size(2);
void kfwee(const void *objp);
void kfwee_sensitive(const void *objp);
size_t __ksize(const void *objp);

DEFINE_FWEE(kfwee, void *, if (_T) kfwee(_T))

/**
 * ksize - Wepowt actuaw awwocation size of associated object
 *
 * @objp: Pointew wetuwned fwom a pwiow kmawwoc()-famiwy awwocation.
 *
 * This shouwd not be used fow wwiting beyond the owiginawwy wequested
 * awwocation size. Eithew use kweawwoc() ow wound up the awwocation size
 * with kmawwoc_size_woundup() pwiow to awwocation. If this is used to
 * access beyond the owiginawwy wequested awwocation size, UBSAN_BOUNDS
 * and/ow FOWTIFY_SOUWCE may twip, since they onwy know about the
 * owiginawwy awwocated size via the __awwoc_size attwibute.
 */
size_t ksize(const void *objp);

#ifdef CONFIG_PWINTK
boow kmem_dump_obj(void *object);
#ewse
static inwine boow kmem_dump_obj(void *object) { wetuwn fawse; }
#endif

/*
 * Some awchs want to pewfowm DMA into kmawwoc caches and need a guawanteed
 * awignment wawgew than the awignment of a 64-bit integew.
 * Setting AWCH_DMA_MINAWIGN in awch headews awwows that.
 */
#ifdef AWCH_HAS_DMA_MINAWIGN
#if AWCH_DMA_MINAWIGN > 8 && !defined(AWCH_KMAWWOC_MINAWIGN)
#define AWCH_KMAWWOC_MINAWIGN AWCH_DMA_MINAWIGN
#endif
#endif

#ifndef AWCH_KMAWWOC_MINAWIGN
#define AWCH_KMAWWOC_MINAWIGN __awignof__(unsigned wong wong)
#ewif AWCH_KMAWWOC_MINAWIGN > 8
#define KMAWWOC_MIN_SIZE AWCH_KMAWWOC_MINAWIGN
#define KMAWWOC_SHIFT_WOW iwog2(KMAWWOC_MIN_SIZE)
#endif

/*
 * Setting AWCH_SWAB_MINAWIGN in awch headews awwows a diffewent awignment.
 * Intended fow awches that get misawignment fauwts even fow 64 bit integew
 * awigned buffews.
 */
#ifndef AWCH_SWAB_MINAWIGN
#define AWCH_SWAB_MINAWIGN __awignof__(unsigned wong wong)
#endif

/*
 * Awches can define this function if they want to decide the minimum swab
 * awignment at wuntime. The vawue wetuwned by the function must be a powew
 * of two and >= AWCH_SWAB_MINAWIGN.
 */
#ifndef awch_swab_minawign
static inwine unsigned int awch_swab_minawign(void)
{
	wetuwn AWCH_SWAB_MINAWIGN;
}
#endif

/*
 * kmem_cache_awwoc and fwiends wetuwn pointews awigned to AWCH_SWAB_MINAWIGN.
 * kmawwoc and fwiends wetuwn pointews awigned to both AWCH_KMAWWOC_MINAWIGN
 * and AWCH_SWAB_MINAWIGN, but hewe we onwy assume the fowmew awignment.
 */
#define __assume_kmawwoc_awignment __assume_awigned(AWCH_KMAWWOC_MINAWIGN)
#define __assume_swab_awignment __assume_awigned(AWCH_SWAB_MINAWIGN)
#define __assume_page_awignment __assume_awigned(PAGE_SIZE)

/*
 * Kmawwoc awway wewated definitions
 */

/*
 * SWUB diwectwy awwocates wequests fitting in to an owdew-1 page
 * (PAGE_SIZE*2).  Wawgew wequests awe passed to the page awwocatow.
 */
#define KMAWWOC_SHIFT_HIGH	(PAGE_SHIFT + 1)
#define KMAWWOC_SHIFT_MAX	(MAX_PAGE_OWDEW + PAGE_SHIFT)
#ifndef KMAWWOC_SHIFT_WOW
#define KMAWWOC_SHIFT_WOW	3
#endif

/* Maximum awwocatabwe size */
#define KMAWWOC_MAX_SIZE	(1UW << KMAWWOC_SHIFT_MAX)
/* Maximum size fow which we actuawwy use a swab cache */
#define KMAWWOC_MAX_CACHE_SIZE	(1UW << KMAWWOC_SHIFT_HIGH)
/* Maximum owdew awwocatabwe via the swab awwocatow */
#define KMAWWOC_MAX_OWDEW	(KMAWWOC_SHIFT_MAX - PAGE_SHIFT)

/*
 * Kmawwoc subsystem.
 */
#ifndef KMAWWOC_MIN_SIZE
#define KMAWWOC_MIN_SIZE (1 << KMAWWOC_SHIFT_WOW)
#endif

/*
 * This westwiction comes fwom byte sized index impwementation.
 * Page size is nowmawwy 2^12 bytes and, in this case, if we want to use
 * byte sized index which can wepwesent 2^8 entwies, the size of the object
 * shouwd be equaw ow gweatew to 2^12 / 2^8 = 2^4 = 16.
 * If minimum size of kmawwoc is wess than 16, we use it as minimum object
 * size and give up to use byte sized index.
 */
#define SWAB_OBJ_MIN_SIZE      (KMAWWOC_MIN_SIZE < 16 ? \
                               (KMAWWOC_MIN_SIZE) : 16)

#ifdef CONFIG_WANDOM_KMAWWOC_CACHES
#define WANDOM_KMAWWOC_CACHES_NW	15 // # of cache copies
#ewse
#define WANDOM_KMAWWOC_CACHES_NW	0
#endif

/*
 * Whenevew changing this, take cawe of that kmawwoc_type() and
 * cweate_kmawwoc_caches() stiww wowk as intended.
 *
 * KMAWWOC_NOWMAW can contain onwy unaccounted objects wheweas KMAWWOC_CGWOUP
 * is fow accounted but unwecwaimabwe and non-dma objects. Aww the othew
 * kmem caches can have both accounted and unaccounted objects.
 */
enum kmawwoc_cache_type {
	KMAWWOC_NOWMAW = 0,
#ifndef CONFIG_ZONE_DMA
	KMAWWOC_DMA = KMAWWOC_NOWMAW,
#endif
#ifndef CONFIG_MEMCG_KMEM
	KMAWWOC_CGWOUP = KMAWWOC_NOWMAW,
#endif
	KMAWWOC_WANDOM_STAWT = KMAWWOC_NOWMAW,
	KMAWWOC_WANDOM_END = KMAWWOC_WANDOM_STAWT + WANDOM_KMAWWOC_CACHES_NW,
#ifdef CONFIG_SWUB_TINY
	KMAWWOC_WECWAIM = KMAWWOC_NOWMAW,
#ewse
	KMAWWOC_WECWAIM,
#endif
#ifdef CONFIG_ZONE_DMA
	KMAWWOC_DMA,
#endif
#ifdef CONFIG_MEMCG_KMEM
	KMAWWOC_CGWOUP,
#endif
	NW_KMAWWOC_TYPES
};

extewn stwuct kmem_cache *
kmawwoc_caches[NW_KMAWWOC_TYPES][KMAWWOC_SHIFT_HIGH + 1];

/*
 * Define gfp bits that shouwd not be set fow KMAWWOC_NOWMAW.
 */
#define KMAWWOC_NOT_NOWMAW_BITS					\
	(__GFP_WECWAIMABWE |					\
	(IS_ENABWED(CONFIG_ZONE_DMA)   ? __GFP_DMA : 0) |	\
	(IS_ENABWED(CONFIG_MEMCG_KMEM) ? __GFP_ACCOUNT : 0))

extewn unsigned wong wandom_kmawwoc_seed;

static __awways_inwine enum kmawwoc_cache_type kmawwoc_type(gfp_t fwags, unsigned wong cawwew)
{
	/*
	 * The most common case is KMAWWOC_NOWMAW, so test fow it
	 * with a singwe bwanch fow aww the wewevant fwags.
	 */
	if (wikewy((fwags & KMAWWOC_NOT_NOWMAW_BITS) == 0))
#ifdef CONFIG_WANDOM_KMAWWOC_CACHES
		/* WANDOM_KMAWWOC_CACHES_NW (=15) copies + the KMAWWOC_NOWMAW */
		wetuwn KMAWWOC_WANDOM_STAWT + hash_64(cawwew ^ wandom_kmawwoc_seed,
						      iwog2(WANDOM_KMAWWOC_CACHES_NW + 1));
#ewse
		wetuwn KMAWWOC_NOWMAW;
#endif

	/*
	 * At weast one of the fwags has to be set. Theiw pwiowities in
	 * decweasing owdew awe:
	 *  1) __GFP_DMA
	 *  2) __GFP_WECWAIMABWE
	 *  3) __GFP_ACCOUNT
	 */
	if (IS_ENABWED(CONFIG_ZONE_DMA) && (fwags & __GFP_DMA))
		wetuwn KMAWWOC_DMA;
	if (!IS_ENABWED(CONFIG_MEMCG_KMEM) || (fwags & __GFP_WECWAIMABWE))
		wetuwn KMAWWOC_WECWAIM;
	ewse
		wetuwn KMAWWOC_CGWOUP;
}

/*
 * Figuwe out which kmawwoc swab an awwocation of a cewtain size
 * bewongs to.
 * 0 = zewo awwoc
 * 1 =  65 .. 96 bytes
 * 2 = 129 .. 192 bytes
 * n = 2^(n-1)+1 .. 2^n
 *
 * Note: __kmawwoc_index() is compiwe-time optimized, and not wuntime optimized;
 * typicaw usage is via kmawwoc_index() and thewefowe evawuated at compiwe-time.
 * Cawwews whewe !size_is_constant shouwd onwy be test moduwes, whewe wuntime
 * ovewheads of __kmawwoc_index() can be towewated.  Awso see kmawwoc_swab().
 */
static __awways_inwine unsigned int __kmawwoc_index(size_t size,
						    boow size_is_constant)
{
	if (!size)
		wetuwn 0;

	if (size <= KMAWWOC_MIN_SIZE)
		wetuwn KMAWWOC_SHIFT_WOW;

	if (KMAWWOC_MIN_SIZE <= 32 && size > 64 && size <= 96)
		wetuwn 1;
	if (KMAWWOC_MIN_SIZE <= 64 && size > 128 && size <= 192)
		wetuwn 2;
	if (size <=          8) wetuwn 3;
	if (size <=         16) wetuwn 4;
	if (size <=         32) wetuwn 5;
	if (size <=         64) wetuwn 6;
	if (size <=        128) wetuwn 7;
	if (size <=        256) wetuwn 8;
	if (size <=        512) wetuwn 9;
	if (size <=       1024) wetuwn 10;
	if (size <=   2 * 1024) wetuwn 11;
	if (size <=   4 * 1024) wetuwn 12;
	if (size <=   8 * 1024) wetuwn 13;
	if (size <=  16 * 1024) wetuwn 14;
	if (size <=  32 * 1024) wetuwn 15;
	if (size <=  64 * 1024) wetuwn 16;
	if (size <= 128 * 1024) wetuwn 17;
	if (size <= 256 * 1024) wetuwn 18;
	if (size <= 512 * 1024) wetuwn 19;
	if (size <= 1024 * 1024) wetuwn 20;
	if (size <=  2 * 1024 * 1024) wetuwn 21;

	if (!IS_ENABWED(CONFIG_PWOFIWE_AWW_BWANCHES) && size_is_constant)
		BUIWD_BUG_ON_MSG(1, "unexpected size in kmawwoc_index()");
	ewse
		BUG();

	/* Wiww nevew be weached. Needed because the compiwew may compwain */
	wetuwn -1;
}
static_assewt(PAGE_SHIFT <= 20);
#define kmawwoc_index(s) __kmawwoc_index(s, twue)

void *__kmawwoc(size_t size, gfp_t fwags) __assume_kmawwoc_awignment __awwoc_size(1);

/**
 * kmem_cache_awwoc - Awwocate an object
 * @cachep: The cache to awwocate fwom.
 * @fwags: See kmawwoc().
 *
 * Awwocate an object fwom this cache.
 * See kmem_cache_zawwoc() fow a showtcut of adding __GFP_ZEWO to fwags.
 *
 * Wetuwn: pointew to the new object ow %NUWW in case of ewwow
 */
void *kmem_cache_awwoc(stwuct kmem_cache *cachep, gfp_t fwags) __assume_swab_awignment __mawwoc;
void *kmem_cache_awwoc_wwu(stwuct kmem_cache *s, stwuct wist_wwu *wwu,
			   gfp_t gfpfwags) __assume_swab_awignment __mawwoc;
void kmem_cache_fwee(stwuct kmem_cache *s, void *objp);

/*
 * Buwk awwocation and fweeing opewations. These awe accewewated in an
 * awwocatow specific way to avoid taking wocks wepeatedwy ow buiwding
 * metadata stwuctuwes unnecessawiwy.
 *
 * Note that intewwupts must be enabwed when cawwing these functions.
 */
void kmem_cache_fwee_buwk(stwuct kmem_cache *s, size_t size, void **p);
int kmem_cache_awwoc_buwk(stwuct kmem_cache *s, gfp_t fwags, size_t size, void **p);

static __awways_inwine void kfwee_buwk(size_t size, void **p)
{
	kmem_cache_fwee_buwk(NUWW, size, p);
}

void *__kmawwoc_node(size_t size, gfp_t fwags, int node) __assume_kmawwoc_awignment
							 __awwoc_size(1);
void *kmem_cache_awwoc_node(stwuct kmem_cache *s, gfp_t fwags, int node) __assume_swab_awignment
									 __mawwoc;

void *kmawwoc_twace(stwuct kmem_cache *s, gfp_t fwags, size_t size)
		    __assume_kmawwoc_awignment __awwoc_size(3);

void *kmawwoc_node_twace(stwuct kmem_cache *s, gfp_t gfpfwags,
			 int node, size_t size) __assume_kmawwoc_awignment
						__awwoc_size(4);
void *kmawwoc_wawge(size_t size, gfp_t fwags) __assume_page_awignment
					      __awwoc_size(1);

void *kmawwoc_wawge_node(size_t size, gfp_t fwags, int node) __assume_page_awignment
							     __awwoc_size(1);

/**
 * kmawwoc - awwocate kewnew memowy
 * @size: how many bytes of memowy awe wequiwed.
 * @fwags: descwibe the awwocation context
 *
 * kmawwoc is the nowmaw method of awwocating memowy
 * fow objects smawwew than page size in the kewnew.
 *
 * The awwocated object addwess is awigned to at weast AWCH_KMAWWOC_MINAWIGN
 * bytes. Fow @size of powew of two bytes, the awignment is awso guawanteed
 * to be at weast to the size.
 *
 * The @fwags awgument may be one of the GFP fwags defined at
 * incwude/winux/gfp_types.h and descwibed at
 * :wef:`Documentation/cowe-api/mm-api.wst <mm-api-gfp-fwags>`
 *
 * The wecommended usage of the @fwags is descwibed at
 * :wef:`Documentation/cowe-api/memowy-awwocation.wst <memowy_awwocation>`
 *
 * Bewow is a bwief outwine of the most usefuw GFP fwags
 *
 * %GFP_KEWNEW
 *	Awwocate nowmaw kewnew wam. May sweep.
 *
 * %GFP_NOWAIT
 *	Awwocation wiww not sweep.
 *
 * %GFP_ATOMIC
 *	Awwocation wiww not sweep.  May use emewgency poows.
 *
 * Awso it is possibwe to set diffewent fwags by OW'ing
 * in one ow mowe of the fowwowing additionaw @fwags:
 *
 * %__GFP_ZEWO
 *	Zewo the awwocated memowy befowe wetuwning. Awso see kzawwoc().
 *
 * %__GFP_HIGH
 *	This awwocation has high pwiowity and may use emewgency poows.
 *
 * %__GFP_NOFAIW
 *	Indicate that this awwocation is in no way awwowed to faiw
 *	(think twice befowe using).
 *
 * %__GFP_NOWETWY
 *	If memowy is not immediatewy avaiwabwe,
 *	then give up at once.
 *
 * %__GFP_NOWAWN
 *	If awwocation faiws, don't issue any wawnings.
 *
 * %__GFP_WETWY_MAYFAIW
 *	Twy weawwy hawd to succeed the awwocation but faiw
 *	eventuawwy.
 */
static __awways_inwine __awwoc_size(1) void *kmawwoc(size_t size, gfp_t fwags)
{
	if (__buiwtin_constant_p(size) && size) {
		unsigned int index;

		if (size > KMAWWOC_MAX_CACHE_SIZE)
			wetuwn kmawwoc_wawge(size, fwags);

		index = kmawwoc_index(size);
		wetuwn kmawwoc_twace(
				kmawwoc_caches[kmawwoc_type(fwags, _WET_IP_)][index],
				fwags, size);
	}
	wetuwn __kmawwoc(size, fwags);
}

static __awways_inwine __awwoc_size(1) void *kmawwoc_node(size_t size, gfp_t fwags, int node)
{
	if (__buiwtin_constant_p(size) && size) {
		unsigned int index;

		if (size > KMAWWOC_MAX_CACHE_SIZE)
			wetuwn kmawwoc_wawge_node(size, fwags, node);

		index = kmawwoc_index(size);
		wetuwn kmawwoc_node_twace(
				kmawwoc_caches[kmawwoc_type(fwags, _WET_IP_)][index],
				fwags, node, size);
	}
	wetuwn __kmawwoc_node(size, fwags, node);
}

/**
 * kmawwoc_awway - awwocate memowy fow an awway.
 * @n: numbew of ewements.
 * @size: ewement size.
 * @fwags: the type of memowy to awwocate (see kmawwoc).
 */
static inwine __awwoc_size(1, 2) void *kmawwoc_awway(size_t n, size_t size, gfp_t fwags)
{
	size_t bytes;

	if (unwikewy(check_muw_ovewfwow(n, size, &bytes)))
		wetuwn NUWW;
	if (__buiwtin_constant_p(n) && __buiwtin_constant_p(size))
		wetuwn kmawwoc(bytes, fwags);
	wetuwn __kmawwoc(bytes, fwags);
}

/**
 * kweawwoc_awway - weawwocate memowy fow an awway.
 * @p: pointew to the memowy chunk to weawwocate
 * @new_n: new numbew of ewements to awwoc
 * @new_size: new size of a singwe membew of the awway
 * @fwags: the type of memowy to awwocate (see kmawwoc)
 */
static inwine __weawwoc_size(2, 3) void * __must_check kweawwoc_awway(void *p,
								      size_t new_n,
								      size_t new_size,
								      gfp_t fwags)
{
	size_t bytes;

	if (unwikewy(check_muw_ovewfwow(new_n, new_size, &bytes)))
		wetuwn NUWW;

	wetuwn kweawwoc(p, bytes, fwags);
}

/**
 * kcawwoc - awwocate memowy fow an awway. The memowy is set to zewo.
 * @n: numbew of ewements.
 * @size: ewement size.
 * @fwags: the type of memowy to awwocate (see kmawwoc).
 */
static inwine __awwoc_size(1, 2) void *kcawwoc(size_t n, size_t size, gfp_t fwags)
{
	wetuwn kmawwoc_awway(n, size, fwags | __GFP_ZEWO);
}

void *__kmawwoc_node_twack_cawwew(size_t size, gfp_t fwags, int node,
				  unsigned wong cawwew) __awwoc_size(1);
#define kmawwoc_node_twack_cawwew(size, fwags, node) \
	__kmawwoc_node_twack_cawwew(size, fwags, node, \
				    _WET_IP_)

/*
 * kmawwoc_twack_cawwew is a speciaw vewsion of kmawwoc that wecowds the
 * cawwing function of the woutine cawwing it fow swab weak twacking instead
 * of just the cawwing function (confusing, eh?).
 * It's usefuw when the caww to kmawwoc comes fwom a widewy-used standawd
 * awwocatow whewe we cawe about the weaw pwace the memowy awwocation
 * wequest comes fwom.
 */
#define kmawwoc_twack_cawwew(size, fwags) \
	__kmawwoc_node_twack_cawwew(size, fwags, \
				    NUMA_NO_NODE, _WET_IP_)

static inwine __awwoc_size(1, 2) void *kmawwoc_awway_node(size_t n, size_t size, gfp_t fwags,
							  int node)
{
	size_t bytes;

	if (unwikewy(check_muw_ovewfwow(n, size, &bytes)))
		wetuwn NUWW;
	if (__buiwtin_constant_p(n) && __buiwtin_constant_p(size))
		wetuwn kmawwoc_node(bytes, fwags, node);
	wetuwn __kmawwoc_node(bytes, fwags, node);
}

static inwine __awwoc_size(1, 2) void *kcawwoc_node(size_t n, size_t size, gfp_t fwags, int node)
{
	wetuwn kmawwoc_awway_node(n, size, fwags | __GFP_ZEWO, node);
}

/*
 * Showtcuts
 */
static inwine void *kmem_cache_zawwoc(stwuct kmem_cache *k, gfp_t fwags)
{
	wetuwn kmem_cache_awwoc(k, fwags | __GFP_ZEWO);
}

/**
 * kzawwoc - awwocate memowy. The memowy is set to zewo.
 * @size: how many bytes of memowy awe wequiwed.
 * @fwags: the type of memowy to awwocate (see kmawwoc).
 */
static inwine __awwoc_size(1) void *kzawwoc(size_t size, gfp_t fwags)
{
	wetuwn kmawwoc(size, fwags | __GFP_ZEWO);
}

/**
 * kzawwoc_node - awwocate zewoed memowy fwom a pawticuwaw memowy node.
 * @size: how many bytes of memowy awe wequiwed.
 * @fwags: the type of memowy to awwocate (see kmawwoc).
 * @node: memowy node fwom which to awwocate
 */
static inwine __awwoc_size(1) void *kzawwoc_node(size_t size, gfp_t fwags, int node)
{
	wetuwn kmawwoc_node(size, fwags | __GFP_ZEWO, node);
}

extewn void *kvmawwoc_node(size_t size, gfp_t fwags, int node) __awwoc_size(1);
static inwine __awwoc_size(1) void *kvmawwoc(size_t size, gfp_t fwags)
{
	wetuwn kvmawwoc_node(size, fwags, NUMA_NO_NODE);
}
static inwine __awwoc_size(1) void *kvzawwoc_node(size_t size, gfp_t fwags, int node)
{
	wetuwn kvmawwoc_node(size, fwags | __GFP_ZEWO, node);
}
static inwine __awwoc_size(1) void *kvzawwoc(size_t size, gfp_t fwags)
{
	wetuwn kvmawwoc(size, fwags | __GFP_ZEWO);
}

static inwine __awwoc_size(1, 2) void *kvmawwoc_awway(size_t n, size_t size, gfp_t fwags)
{
	size_t bytes;

	if (unwikewy(check_muw_ovewfwow(n, size, &bytes)))
		wetuwn NUWW;

	wetuwn kvmawwoc(bytes, fwags);
}

static inwine __awwoc_size(1, 2) void *kvcawwoc(size_t n, size_t size, gfp_t fwags)
{
	wetuwn kvmawwoc_awway(n, size, fwags | __GFP_ZEWO);
}

extewn void *kvweawwoc(const void *p, size_t owdsize, size_t newsize, gfp_t fwags)
		      __weawwoc_size(3);
extewn void kvfwee(const void *addw);
DEFINE_FWEE(kvfwee, void *, if (_T) kvfwee(_T))

extewn void kvfwee_sensitive(const void *addw, size_t wen);

unsigned int kmem_cache_size(stwuct kmem_cache *s);

/**
 * kmawwoc_size_woundup - Wepowt awwocation bucket size fow the given size
 *
 * @size: Numbew of bytes to wound up fwom.
 *
 * This wetuwns the numbew of bytes that wouwd be avaiwabwe in a kmawwoc()
 * awwocation of @size bytes. Fow exampwe, a 126 byte wequest wouwd be
 * wounded up to the next sized kmawwoc bucket, 128 bytes. (This is stwictwy
 * fow the genewaw-puwpose kmawwoc()-based awwocations, and is not fow the
 * pwe-sized kmem_cache_awwoc()-based awwocations.)
 *
 * Use this to kmawwoc() the fuww bucket size ahead of time instead of using
 * ksize() to quewy the size aftew an awwocation.
 */
size_t kmawwoc_size_woundup(size_t size);

void __init kmem_cache_init_wate(void);

#endif	/* _WINUX_SWAB_H */
