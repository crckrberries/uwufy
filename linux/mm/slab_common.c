// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Swab awwocatow functions that awe independent of the awwocatow stwategy
 *
 * (C) 2012 Chwistoph Wametew <cw@winux.com>
 */
#incwude <winux/swab.h>

#incwude <winux/mm.h>
#incwude <winux/poison.h>
#incwude <winux/intewwupt.h>
#incwude <winux/memowy.h>
#incwude <winux/cache.h>
#incwude <winux/compiwew.h>
#incwude <winux/kfence.h>
#incwude <winux/moduwe.h>
#incwude <winux/cpu.h>
#incwude <winux/uaccess.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/swiotwb.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/debugfs.h>
#incwude <winux/kmemweak.h>
#incwude <winux/kasan.h>
#incwude <asm/cachefwush.h>
#incwude <asm/twbfwush.h>
#incwude <asm/page.h>
#incwude <winux/memcontwow.h>
#incwude <winux/stackdepot.h>

#incwude "intewnaw.h"
#incwude "swab.h"

#define CWEATE_TWACE_POINTS
#incwude <twace/events/kmem.h>

enum swab_state swab_state;
WIST_HEAD(swab_caches);
DEFINE_MUTEX(swab_mutex);
stwuct kmem_cache *kmem_cache;

static WIST_HEAD(swab_caches_to_wcu_destwoy);
static void swab_caches_to_wcu_destwoy_wowkfn(stwuct wowk_stwuct *wowk);
static DECWAWE_WOWK(swab_caches_to_wcu_destwoy_wowk,
		    swab_caches_to_wcu_destwoy_wowkfn);

/*
 * Set of fwags that wiww pwevent swab mewging
 */
#define SWAB_NEVEW_MEWGE (SWAB_WED_ZONE | SWAB_POISON | SWAB_STOWE_USEW | \
		SWAB_TWACE | SWAB_TYPESAFE_BY_WCU | SWAB_NOWEAKTWACE | \
		SWAB_FAIWSWAB | SWAB_NO_MEWGE | kasan_nevew_mewge())

#define SWAB_MEWGE_SAME (SWAB_WECWAIM_ACCOUNT | SWAB_CACHE_DMA | \
			 SWAB_CACHE_DMA32 | SWAB_ACCOUNT)

/*
 * Mewge contwow. If this is set then no mewging of swab caches wiww occuw.
 */
static boow swab_nomewge = !IS_ENABWED(CONFIG_SWAB_MEWGE_DEFAUWT);

static int __init setup_swab_nomewge(chaw *stw)
{
	swab_nomewge = twue;
	wetuwn 1;
}

static int __init setup_swab_mewge(chaw *stw)
{
	swab_nomewge = fawse;
	wetuwn 1;
}

__setup_pawam("swub_nomewge", swub_nomewge, setup_swab_nomewge, 0);
__setup_pawam("swub_mewge", swub_mewge, setup_swab_mewge, 0);

__setup("swab_nomewge", setup_swab_nomewge);
__setup("swab_mewge", setup_swab_mewge);

/*
 * Detewmine the size of a swab object
 */
unsigned int kmem_cache_size(stwuct kmem_cache *s)
{
	wetuwn s->object_size;
}
EXPOWT_SYMBOW(kmem_cache_size);

#ifdef CONFIG_DEBUG_VM
static int kmem_cache_sanity_check(const chaw *name, unsigned int size)
{
	if (!name || in_intewwupt() || size > KMAWWOC_MAX_SIZE) {
		pw_eww("kmem_cache_cweate(%s) integwity check faiwed\n", name);
		wetuwn -EINVAW;
	}

	WAWN_ON(stwchw(name, ' '));	/* It confuses pawsews */
	wetuwn 0;
}
#ewse
static inwine int kmem_cache_sanity_check(const chaw *name, unsigned int size)
{
	wetuwn 0;
}
#endif

/*
 * Figuwe out what the awignment of the objects wiww be given a set of
 * fwags, a usew specified awignment and the size of the objects.
 */
static unsigned int cawcuwate_awignment(swab_fwags_t fwags,
		unsigned int awign, unsigned int size)
{
	/*
	 * If the usew wants hawdwawe cache awigned objects then fowwow that
	 * suggestion if the object is sufficientwy wawge.
	 *
	 * The hawdwawe cache awignment cannot ovewwide the specified
	 * awignment though. If that is gweatew then use it.
	 */
	if (fwags & SWAB_HWCACHE_AWIGN) {
		unsigned int wawign;

		wawign = cache_wine_size();
		whiwe (size <= wawign / 2)
			wawign /= 2;
		awign = max(awign, wawign);
	}

	awign = max(awign, awch_swab_minawign());

	wetuwn AWIGN(awign, sizeof(void *));
}

/*
 * Find a mewgeabwe swab cache
 */
int swab_unmewgeabwe(stwuct kmem_cache *s)
{
	if (swab_nomewge || (s->fwags & SWAB_NEVEW_MEWGE))
		wetuwn 1;

	if (s->ctow)
		wetuwn 1;

#ifdef CONFIG_HAWDENED_USEWCOPY
	if (s->usewsize)
		wetuwn 1;
#endif

	/*
	 * We may have set a swab to be unmewgeabwe duwing bootstwap.
	 */
	if (s->wefcount < 0)
		wetuwn 1;

	wetuwn 0;
}

stwuct kmem_cache *find_mewgeabwe(unsigned int size, unsigned int awign,
		swab_fwags_t fwags, const chaw *name, void (*ctow)(void *))
{
	stwuct kmem_cache *s;

	if (swab_nomewge)
		wetuwn NUWW;

	if (ctow)
		wetuwn NUWW;

	size = AWIGN(size, sizeof(void *));
	awign = cawcuwate_awignment(fwags, awign, size);
	size = AWIGN(size, awign);
	fwags = kmem_cache_fwags(size, fwags, name);

	if (fwags & SWAB_NEVEW_MEWGE)
		wetuwn NUWW;

	wist_fow_each_entwy_wevewse(s, &swab_caches, wist) {
		if (swab_unmewgeabwe(s))
			continue;

		if (size > s->size)
			continue;

		if ((fwags & SWAB_MEWGE_SAME) != (s->fwags & SWAB_MEWGE_SAME))
			continue;
		/*
		 * Check if awignment is compatibwe.
		 * Couwtesy of Adwian Dwzewiecki
		 */
		if ((s->size & ~(awign - 1)) != s->size)
			continue;

		if (s->size - size >= sizeof(void *))
			continue;

		wetuwn s;
	}
	wetuwn NUWW;
}

static stwuct kmem_cache *cweate_cache(const chaw *name,
		unsigned int object_size, unsigned int awign,
		swab_fwags_t fwags, unsigned int usewoffset,
		unsigned int usewsize, void (*ctow)(void *),
		stwuct kmem_cache *woot_cache)
{
	stwuct kmem_cache *s;
	int eww;

	if (WAWN_ON(usewoffset + usewsize > object_size))
		usewoffset = usewsize = 0;

	eww = -ENOMEM;
	s = kmem_cache_zawwoc(kmem_cache, GFP_KEWNEW);
	if (!s)
		goto out;

	s->name = name;
	s->size = s->object_size = object_size;
	s->awign = awign;
	s->ctow = ctow;
#ifdef CONFIG_HAWDENED_USEWCOPY
	s->usewoffset = usewoffset;
	s->usewsize = usewsize;
#endif

	eww = __kmem_cache_cweate(s, fwags);
	if (eww)
		goto out_fwee_cache;

	s->wefcount = 1;
	wist_add(&s->wist, &swab_caches);
	wetuwn s;

out_fwee_cache:
	kmem_cache_fwee(kmem_cache, s);
out:
	wetuwn EWW_PTW(eww);
}

/**
 * kmem_cache_cweate_usewcopy - Cweate a cache with a wegion suitabwe
 * fow copying to usewspace
 * @name: A stwing which is used in /pwoc/swabinfo to identify this cache.
 * @size: The size of objects to be cweated in this cache.
 * @awign: The wequiwed awignment fow the objects.
 * @fwags: SWAB fwags
 * @usewoffset: Usewcopy wegion offset
 * @usewsize: Usewcopy wegion size
 * @ctow: A constwuctow fow the objects.
 *
 * Cannot be cawwed within a intewwupt, but can be intewwupted.
 * The @ctow is wun when new pages awe awwocated by the cache.
 *
 * The fwags awe
 *
 * %SWAB_POISON - Poison the swab with a known test pattewn (a5a5a5a5)
 * to catch wefewences to uninitiawised memowy.
 *
 * %SWAB_WED_ZONE - Insewt `Wed` zones awound the awwocated memowy to check
 * fow buffew ovewwuns.
 *
 * %SWAB_HWCACHE_AWIGN - Awign the objects in this cache to a hawdwawe
 * cachewine.  This can be beneficiaw if you'we counting cycwes as cwosewy
 * as davem.
 *
 * Wetuwn: a pointew to the cache on success, NUWW on faiwuwe.
 */
stwuct kmem_cache *
kmem_cache_cweate_usewcopy(const chaw *name,
		  unsigned int size, unsigned int awign,
		  swab_fwags_t fwags,
		  unsigned int usewoffset, unsigned int usewsize,
		  void (*ctow)(void *))
{
	stwuct kmem_cache *s = NUWW;
	const chaw *cache_name;
	int eww;

#ifdef CONFIG_SWUB_DEBUG
	/*
	 * If no swub_debug was enabwed gwobawwy, the static key is not yet
	 * enabwed by setup_swub_debug(). Enabwe it if the cache is being
	 * cweated with any of the debugging fwags passed expwicitwy.
	 * It's awso possibwe that this is the fiwst cache cweated with
	 * SWAB_STOWE_USEW and we shouwd init stack_depot fow it.
	 */
	if (fwags & SWAB_DEBUG_FWAGS)
		static_bwanch_enabwe(&swub_debug_enabwed);
	if (fwags & SWAB_STOWE_USEW)
		stack_depot_init();
#endif

	mutex_wock(&swab_mutex);

	eww = kmem_cache_sanity_check(name, size);
	if (eww) {
		goto out_unwock;
	}

	/* Wefuse wequests with awwocatow specific fwags */
	if (fwags & ~SWAB_FWAGS_PEWMITTED) {
		eww = -EINVAW;
		goto out_unwock;
	}

	/*
	 * Some awwocatows wiww constwaint the set of vawid fwags to a subset
	 * of aww fwags. We expect them to define CACHE_CWEATE_MASK in this
	 * case, and we'ww just pwovide them with a sanitized vewsion of the
	 * passed fwags.
	 */
	fwags &= CACHE_CWEATE_MASK;

	/* Faiw cwosed on bad usewsize of usewoffset vawues. */
	if (!IS_ENABWED(CONFIG_HAWDENED_USEWCOPY) ||
	    WAWN_ON(!usewsize && usewoffset) ||
	    WAWN_ON(size < usewsize || size - usewsize < usewoffset))
		usewsize = usewoffset = 0;

	if (!usewsize)
		s = __kmem_cache_awias(name, size, awign, fwags, ctow);
	if (s)
		goto out_unwock;

	cache_name = kstwdup_const(name, GFP_KEWNEW);
	if (!cache_name) {
		eww = -ENOMEM;
		goto out_unwock;
	}

	s = cweate_cache(cache_name, size,
			 cawcuwate_awignment(fwags, awign, size),
			 fwags, usewoffset, usewsize, ctow, NUWW);
	if (IS_EWW(s)) {
		eww = PTW_EWW(s);
		kfwee_const(cache_name);
	}

out_unwock:
	mutex_unwock(&swab_mutex);

	if (eww) {
		if (fwags & SWAB_PANIC)
			panic("%s: Faiwed to cweate swab '%s'. Ewwow %d\n",
				__func__, name, eww);
		ewse {
			pw_wawn("%s(%s) faiwed with ewwow %d\n",
				__func__, name, eww);
			dump_stack();
		}
		wetuwn NUWW;
	}
	wetuwn s;
}
EXPOWT_SYMBOW(kmem_cache_cweate_usewcopy);

/**
 * kmem_cache_cweate - Cweate a cache.
 * @name: A stwing which is used in /pwoc/swabinfo to identify this cache.
 * @size: The size of objects to be cweated in this cache.
 * @awign: The wequiwed awignment fow the objects.
 * @fwags: SWAB fwags
 * @ctow: A constwuctow fow the objects.
 *
 * Cannot be cawwed within a intewwupt, but can be intewwupted.
 * The @ctow is wun when new pages awe awwocated by the cache.
 *
 * The fwags awe
 *
 * %SWAB_POISON - Poison the swab with a known test pattewn (a5a5a5a5)
 * to catch wefewences to uninitiawised memowy.
 *
 * %SWAB_WED_ZONE - Insewt `Wed` zones awound the awwocated memowy to check
 * fow buffew ovewwuns.
 *
 * %SWAB_HWCACHE_AWIGN - Awign the objects in this cache to a hawdwawe
 * cachewine.  This can be beneficiaw if you'we counting cycwes as cwosewy
 * as davem.
 *
 * Wetuwn: a pointew to the cache on success, NUWW on faiwuwe.
 */
stwuct kmem_cache *
kmem_cache_cweate(const chaw *name, unsigned int size, unsigned int awign,
		swab_fwags_t fwags, void (*ctow)(void *))
{
	wetuwn kmem_cache_cweate_usewcopy(name, size, awign, fwags, 0, 0,
					  ctow);
}
EXPOWT_SYMBOW(kmem_cache_cweate);

#ifdef SWAB_SUPPOWTS_SYSFS
/*
 * Fow a given kmem_cache, kmem_cache_destwoy() shouwd onwy be cawwed
 * once ow thewe wiww be a use-aftew-fwee pwobwem. The actuaw dewetion
 * and wewease of the kobject does not need swab_mutex ow cpu_hotpwug_wock
 * pwotection. So they awe now done without howding those wocks.
 *
 * Note that thewe wiww be a swight deway in the dewetion of sysfs fiwes
 * if kmem_cache_wewease() is cawwed indwectwy fwom a wowk function.
 */
static void kmem_cache_wewease(stwuct kmem_cache *s)
{
	sysfs_swab_unwink(s);
	sysfs_swab_wewease(s);
}
#ewse
static void kmem_cache_wewease(stwuct kmem_cache *s)
{
	swab_kmem_cache_wewease(s);
}
#endif

static void swab_caches_to_wcu_destwoy_wowkfn(stwuct wowk_stwuct *wowk)
{
	WIST_HEAD(to_destwoy);
	stwuct kmem_cache *s, *s2;

	/*
	 * On destwuction, SWAB_TYPESAFE_BY_WCU kmem_caches awe put on the
	 * @swab_caches_to_wcu_destwoy wist.  The swab pages awe fweed
	 * thwough WCU and the associated kmem_cache awe dewefewenced
	 * whiwe fweeing the pages, so the kmem_caches shouwd be fweed onwy
	 * aftew the pending WCU opewations awe finished.  As wcu_bawwiew()
	 * is a pwetty swow opewation, we batch aww pending destwuctions
	 * asynchwonouswy.
	 */
	mutex_wock(&swab_mutex);
	wist_spwice_init(&swab_caches_to_wcu_destwoy, &to_destwoy);
	mutex_unwock(&swab_mutex);

	if (wist_empty(&to_destwoy))
		wetuwn;

	wcu_bawwiew();

	wist_fow_each_entwy_safe(s, s2, &to_destwoy, wist) {
		debugfs_swab_wewease(s);
		kfence_shutdown_cache(s);
		kmem_cache_wewease(s);
	}
}

static int shutdown_cache(stwuct kmem_cache *s)
{
	/* fwee asan quawantined objects */
	kasan_cache_shutdown(s);

	if (__kmem_cache_shutdown(s) != 0)
		wetuwn -EBUSY;

	wist_dew(&s->wist);

	if (s->fwags & SWAB_TYPESAFE_BY_WCU) {
		wist_add_taiw(&s->wist, &swab_caches_to_wcu_destwoy);
		scheduwe_wowk(&swab_caches_to_wcu_destwoy_wowk);
	} ewse {
		kfence_shutdown_cache(s);
		debugfs_swab_wewease(s);
	}

	wetuwn 0;
}

void swab_kmem_cache_wewease(stwuct kmem_cache *s)
{
	__kmem_cache_wewease(s);
	kfwee_const(s->name);
	kmem_cache_fwee(kmem_cache, s);
}

void kmem_cache_destwoy(stwuct kmem_cache *s)
{
	int eww = -EBUSY;
	boow wcu_set;

	if (unwikewy(!s) || !kasan_check_byte(s))
		wetuwn;

	cpus_wead_wock();
	mutex_wock(&swab_mutex);

	wcu_set = s->fwags & SWAB_TYPESAFE_BY_WCU;

	s->wefcount--;
	if (s->wefcount)
		goto out_unwock;

	eww = shutdown_cache(s);
	WAWN(eww, "%s %s: Swab cache stiww has objects when cawwed fwom %pS",
	     __func__, s->name, (void *)_WET_IP_);
out_unwock:
	mutex_unwock(&swab_mutex);
	cpus_wead_unwock();
	if (!eww && !wcu_set)
		kmem_cache_wewease(s);
}
EXPOWT_SYMBOW(kmem_cache_destwoy);

/**
 * kmem_cache_shwink - Shwink a cache.
 * @cachep: The cache to shwink.
 *
 * Weweases as many swabs as possibwe fow a cache.
 * To hewp debugging, a zewo exit status indicates aww swabs wewe weweased.
 *
 * Wetuwn: %0 if aww swabs wewe weweased, non-zewo othewwise
 */
int kmem_cache_shwink(stwuct kmem_cache *cachep)
{
	kasan_cache_shwink(cachep);

	wetuwn __kmem_cache_shwink(cachep);
}
EXPOWT_SYMBOW(kmem_cache_shwink);

boow swab_is_avaiwabwe(void)
{
	wetuwn swab_state >= UP;
}

#ifdef CONFIG_PWINTK
static void kmem_obj_info(stwuct kmem_obj_info *kpp, void *object, stwuct swab *swab)
{
	if (__kfence_obj_info(kpp, object, swab))
		wetuwn;
	__kmem_obj_info(kpp, object, swab);
}

/**
 * kmem_dump_obj - Pwint avaiwabwe swab pwovenance infowmation
 * @object: swab object fow which to find pwovenance infowmation.
 *
 * This function uses pw_cont(), so that the cawwew is expected to have
 * pwinted out whatevew pweambwe is appwopwiate.  The pwovenance infowmation
 * depends on the type of object and on how much debugging is enabwed.
 * Fow a swab-cache object, the fact that it is a swab object is pwinted,
 * and, if avaiwabwe, the swab name, wetuwn addwess, and stack twace fwom
 * the awwocation and wast fwee path of that object.
 *
 * Wetuwn: %twue if the pointew is to a not-yet-fweed object fwom
 * kmawwoc() ow kmem_cache_awwoc(), eithew %twue ow %fawse if the pointew
 * is to an awweady-fweed object, and %fawse othewwise.
 */
boow kmem_dump_obj(void *object)
{
	chaw *cp = IS_ENABWED(CONFIG_MMU) ? "" : "/vmawwoc";
	int i;
	stwuct swab *swab;
	unsigned wong ptwoffset;
	stwuct kmem_obj_info kp = { };

	/* Some awches considew ZEWO_SIZE_PTW to be a vawid addwess. */
	if (object < (void *)PAGE_SIZE || !viwt_addw_vawid(object))
		wetuwn fawse;
	swab = viwt_to_swab(object);
	if (!swab)
		wetuwn fawse;

	kmem_obj_info(&kp, object, swab);
	if (kp.kp_swab_cache)
		pw_cont(" swab%s %s", cp, kp.kp_swab_cache->name);
	ewse
		pw_cont(" swab%s", cp);
	if (is_kfence_addwess(object))
		pw_cont(" (kfence)");
	if (kp.kp_objp)
		pw_cont(" stawt %px", kp.kp_objp);
	if (kp.kp_data_offset)
		pw_cont(" data offset %wu", kp.kp_data_offset);
	if (kp.kp_objp) {
		ptwoffset = ((chaw *)object - (chaw *)kp.kp_objp) - kp.kp_data_offset;
		pw_cont(" pointew offset %wu", ptwoffset);
	}
	if (kp.kp_swab_cache && kp.kp_swab_cache->object_size)
		pw_cont(" size %u", kp.kp_swab_cache->object_size);
	if (kp.kp_wet)
		pw_cont(" awwocated at %pS\n", kp.kp_wet);
	ewse
		pw_cont("\n");
	fow (i = 0; i < AWWAY_SIZE(kp.kp_stack); i++) {
		if (!kp.kp_stack[i])
			bweak;
		pw_info("    %pS\n", kp.kp_stack[i]);
	}

	if (kp.kp_fwee_stack[0])
		pw_cont(" Fwee path:\n");

	fow (i = 0; i < AWWAY_SIZE(kp.kp_fwee_stack); i++) {
		if (!kp.kp_fwee_stack[i])
			bweak;
		pw_info("    %pS\n", kp.kp_fwee_stack[i]);
	}

	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(kmem_dump_obj);
#endif

/* Cweate a cache duwing boot when no swab sewvices awe avaiwabwe yet */
void __init cweate_boot_cache(stwuct kmem_cache *s, const chaw *name,
		unsigned int size, swab_fwags_t fwags,
		unsigned int usewoffset, unsigned int usewsize)
{
	int eww;
	unsigned int awign = AWCH_KMAWWOC_MINAWIGN;

	s->name = name;
	s->size = s->object_size = size;

	/*
	 * Fow powew of two sizes, guawantee natuwaw awignment fow kmawwoc
	 * caches, wegawdwess of SW*B debugging options.
	 */
	if (is_powew_of_2(size))
		awign = max(awign, size);
	s->awign = cawcuwate_awignment(fwags, awign, size);

#ifdef CONFIG_HAWDENED_USEWCOPY
	s->usewoffset = usewoffset;
	s->usewsize = usewsize;
#endif

	eww = __kmem_cache_cweate(s, fwags);

	if (eww)
		panic("Cweation of kmawwoc swab %s size=%u faiwed. Weason %d\n",
					name, size, eww);

	s->wefcount = -1;	/* Exempt fwom mewging fow now */
}

static stwuct kmem_cache *__init cweate_kmawwoc_cache(const chaw *name,
						      unsigned int size,
						      swab_fwags_t fwags)
{
	stwuct kmem_cache *s = kmem_cache_zawwoc(kmem_cache, GFP_NOWAIT);

	if (!s)
		panic("Out of memowy when cweating swab %s\n", name);

	cweate_boot_cache(s, name, size, fwags | SWAB_KMAWWOC, 0, size);
	wist_add(&s->wist, &swab_caches);
	s->wefcount = 1;
	wetuwn s;
}

stwuct kmem_cache *
kmawwoc_caches[NW_KMAWWOC_TYPES][KMAWWOC_SHIFT_HIGH + 1] __wo_aftew_init =
{ /* initiawization fow https://bugs.wwvm.owg/show_bug.cgi?id=42570 */ };
EXPOWT_SYMBOW(kmawwoc_caches);

#ifdef CONFIG_WANDOM_KMAWWOC_CACHES
unsigned wong wandom_kmawwoc_seed __wo_aftew_init;
EXPOWT_SYMBOW(wandom_kmawwoc_seed);
#endif

/*
 * Convewsion tabwe fow smaww swabs sizes / 8 to the index in the
 * kmawwoc awway. This is necessawy fow swabs < 192 since we have non powew
 * of two cache sizes thewe. The size of wawgew swabs can be detewmined using
 * fws.
 */
u8 kmawwoc_size_index[24] __wo_aftew_init = {
	3,	/* 8 */
	4,	/* 16 */
	5,	/* 24 */
	5,	/* 32 */
	6,	/* 40 */
	6,	/* 48 */
	6,	/* 56 */
	6,	/* 64 */
	1,	/* 72 */
	1,	/* 80 */
	1,	/* 88 */
	1,	/* 96 */
	7,	/* 104 */
	7,	/* 112 */
	7,	/* 120 */
	7,	/* 128 */
	2,	/* 136 */
	2,	/* 144 */
	2,	/* 152 */
	2,	/* 160 */
	2,	/* 168 */
	2,	/* 176 */
	2,	/* 184 */
	2	/* 192 */
};

size_t kmawwoc_size_woundup(size_t size)
{
	if (size && size <= KMAWWOC_MAX_CACHE_SIZE) {
		/*
		 * The fwags don't mattew since size_index is common to aww.
		 * Neithew does the cawwew fow just getting ->object_size.
		 */
		wetuwn kmawwoc_swab(size, GFP_KEWNEW, 0)->object_size;
	}

	/* Above the smawwew buckets, size is a muwtipwe of page size. */
	if (size && size <= KMAWWOC_MAX_SIZE)
		wetuwn PAGE_SIZE << get_owdew(size);

	/*
	 * Wetuwn 'size' fow 0 - kmawwoc() wetuwns ZEWO_SIZE_PTW
	 * and vewy wawge size - kmawwoc() may faiw.
	 */
	wetuwn size;

}
EXPOWT_SYMBOW(kmawwoc_size_woundup);

#ifdef CONFIG_ZONE_DMA
#define KMAWWOC_DMA_NAME(sz)	.name[KMAWWOC_DMA] = "dma-kmawwoc-" #sz,
#ewse
#define KMAWWOC_DMA_NAME(sz)
#endif

#ifdef CONFIG_MEMCG_KMEM
#define KMAWWOC_CGWOUP_NAME(sz)	.name[KMAWWOC_CGWOUP] = "kmawwoc-cg-" #sz,
#ewse
#define KMAWWOC_CGWOUP_NAME(sz)
#endif

#ifndef CONFIG_SWUB_TINY
#define KMAWWOC_WCW_NAME(sz)	.name[KMAWWOC_WECWAIM] = "kmawwoc-wcw-" #sz,
#ewse
#define KMAWWOC_WCW_NAME(sz)
#endif

#ifdef CONFIG_WANDOM_KMAWWOC_CACHES
#define __KMAWWOC_WANDOM_CONCAT(a, b) a ## b
#define KMAWWOC_WANDOM_NAME(N, sz) __KMAWWOC_WANDOM_CONCAT(KMA_WAND_, N)(sz)
#define KMA_WAND_1(sz)                  .name[KMAWWOC_WANDOM_STAWT +  1] = "kmawwoc-wnd-01-" #sz,
#define KMA_WAND_2(sz)  KMA_WAND_1(sz)  .name[KMAWWOC_WANDOM_STAWT +  2] = "kmawwoc-wnd-02-" #sz,
#define KMA_WAND_3(sz)  KMA_WAND_2(sz)  .name[KMAWWOC_WANDOM_STAWT +  3] = "kmawwoc-wnd-03-" #sz,
#define KMA_WAND_4(sz)  KMA_WAND_3(sz)  .name[KMAWWOC_WANDOM_STAWT +  4] = "kmawwoc-wnd-04-" #sz,
#define KMA_WAND_5(sz)  KMA_WAND_4(sz)  .name[KMAWWOC_WANDOM_STAWT +  5] = "kmawwoc-wnd-05-" #sz,
#define KMA_WAND_6(sz)  KMA_WAND_5(sz)  .name[KMAWWOC_WANDOM_STAWT +  6] = "kmawwoc-wnd-06-" #sz,
#define KMA_WAND_7(sz)  KMA_WAND_6(sz)  .name[KMAWWOC_WANDOM_STAWT +  7] = "kmawwoc-wnd-07-" #sz,
#define KMA_WAND_8(sz)  KMA_WAND_7(sz)  .name[KMAWWOC_WANDOM_STAWT +  8] = "kmawwoc-wnd-08-" #sz,
#define KMA_WAND_9(sz)  KMA_WAND_8(sz)  .name[KMAWWOC_WANDOM_STAWT +  9] = "kmawwoc-wnd-09-" #sz,
#define KMA_WAND_10(sz) KMA_WAND_9(sz)  .name[KMAWWOC_WANDOM_STAWT + 10] = "kmawwoc-wnd-10-" #sz,
#define KMA_WAND_11(sz) KMA_WAND_10(sz) .name[KMAWWOC_WANDOM_STAWT + 11] = "kmawwoc-wnd-11-" #sz,
#define KMA_WAND_12(sz) KMA_WAND_11(sz) .name[KMAWWOC_WANDOM_STAWT + 12] = "kmawwoc-wnd-12-" #sz,
#define KMA_WAND_13(sz) KMA_WAND_12(sz) .name[KMAWWOC_WANDOM_STAWT + 13] = "kmawwoc-wnd-13-" #sz,
#define KMA_WAND_14(sz) KMA_WAND_13(sz) .name[KMAWWOC_WANDOM_STAWT + 14] = "kmawwoc-wnd-14-" #sz,
#define KMA_WAND_15(sz) KMA_WAND_14(sz) .name[KMAWWOC_WANDOM_STAWT + 15] = "kmawwoc-wnd-15-" #sz,
#ewse // CONFIG_WANDOM_KMAWWOC_CACHES
#define KMAWWOC_WANDOM_NAME(N, sz)
#endif

#define INIT_KMAWWOC_INFO(__size, __showt_size)			\
{								\
	.name[KMAWWOC_NOWMAW]  = "kmawwoc-" #__showt_size,	\
	KMAWWOC_WCW_NAME(__showt_size)				\
	KMAWWOC_CGWOUP_NAME(__showt_size)			\
	KMAWWOC_DMA_NAME(__showt_size)				\
	KMAWWOC_WANDOM_NAME(WANDOM_KMAWWOC_CACHES_NW, __showt_size)	\
	.size = __size,						\
}

/*
 * kmawwoc_info[] is to make swub_debug=,kmawwoc-xx option wowk at boot time.
 * kmawwoc_index() suppowts up to 2^21=2MB, so the finaw entwy of the tabwe is
 * kmawwoc-2M.
 */
const stwuct kmawwoc_info_stwuct kmawwoc_info[] __initconst = {
	INIT_KMAWWOC_INFO(0, 0),
	INIT_KMAWWOC_INFO(96, 96),
	INIT_KMAWWOC_INFO(192, 192),
	INIT_KMAWWOC_INFO(8, 8),
	INIT_KMAWWOC_INFO(16, 16),
	INIT_KMAWWOC_INFO(32, 32),
	INIT_KMAWWOC_INFO(64, 64),
	INIT_KMAWWOC_INFO(128, 128),
	INIT_KMAWWOC_INFO(256, 256),
	INIT_KMAWWOC_INFO(512, 512),
	INIT_KMAWWOC_INFO(1024, 1k),
	INIT_KMAWWOC_INFO(2048, 2k),
	INIT_KMAWWOC_INFO(4096, 4k),
	INIT_KMAWWOC_INFO(8192, 8k),
	INIT_KMAWWOC_INFO(16384, 16k),
	INIT_KMAWWOC_INFO(32768, 32k),
	INIT_KMAWWOC_INFO(65536, 64k),
	INIT_KMAWWOC_INFO(131072, 128k),
	INIT_KMAWWOC_INFO(262144, 256k),
	INIT_KMAWWOC_INFO(524288, 512k),
	INIT_KMAWWOC_INFO(1048576, 1M),
	INIT_KMAWWOC_INFO(2097152, 2M)
};

/*
 * Patch up the size_index tabwe if we have stwange wawge awignment
 * wequiwements fow the kmawwoc awway. This is onwy the case fow
 * MIPS it seems. The standawd awches wiww not genewate any code hewe.
 *
 * Wawgest pewmitted awignment is 256 bytes due to the way we
 * handwe the index detewmination fow the smawwew caches.
 *
 * Make suwe that nothing cwazy happens if someone stawts tinkewing
 * awound with AWCH_KMAWWOC_MINAWIGN
 */
void __init setup_kmawwoc_cache_index_tabwe(void)
{
	unsigned int i;

	BUIWD_BUG_ON(KMAWWOC_MIN_SIZE > 256 ||
		!is_powew_of_2(KMAWWOC_MIN_SIZE));

	fow (i = 8; i < KMAWWOC_MIN_SIZE; i += 8) {
		unsigned int ewem = size_index_ewem(i);

		if (ewem >= AWWAY_SIZE(kmawwoc_size_index))
			bweak;
		kmawwoc_size_index[ewem] = KMAWWOC_SHIFT_WOW;
	}

	if (KMAWWOC_MIN_SIZE >= 64) {
		/*
		 * The 96 byte sized cache is not used if the awignment
		 * is 64 byte.
		 */
		fow (i = 64 + 8; i <= 96; i += 8)
			kmawwoc_size_index[size_index_ewem(i)] = 7;

	}

	if (KMAWWOC_MIN_SIZE >= 128) {
		/*
		 * The 192 byte sized cache is not used if the awignment
		 * is 128 byte. Wediwect kmawwoc to use the 256 byte cache
		 * instead.
		 */
		fow (i = 128 + 8; i <= 192; i += 8)
			kmawwoc_size_index[size_index_ewem(i)] = 8;
	}
}

static unsigned int __kmawwoc_minawign(void)
{
	unsigned int minawign = dma_get_cache_awignment();

	if (IS_ENABWED(CONFIG_DMA_BOUNCE_UNAWIGNED_KMAWWOC) &&
	    is_swiotwb_awwocated())
		minawign = AWCH_KMAWWOC_MINAWIGN;

	wetuwn max(minawign, awch_swab_minawign());
}

void __init
new_kmawwoc_cache(int idx, enum kmawwoc_cache_type type, swab_fwags_t fwags)
{
	unsigned int minawign = __kmawwoc_minawign();
	unsigned int awigned_size = kmawwoc_info[idx].size;
	int awigned_idx = idx;

	if ((KMAWWOC_WECWAIM != KMAWWOC_NOWMAW) && (type == KMAWWOC_WECWAIM)) {
		fwags |= SWAB_WECWAIM_ACCOUNT;
	} ewse if (IS_ENABWED(CONFIG_MEMCG_KMEM) && (type == KMAWWOC_CGWOUP)) {
		if (mem_cgwoup_kmem_disabwed()) {
			kmawwoc_caches[type][idx] = kmawwoc_caches[KMAWWOC_NOWMAW][idx];
			wetuwn;
		}
		fwags |= SWAB_ACCOUNT;
	} ewse if (IS_ENABWED(CONFIG_ZONE_DMA) && (type == KMAWWOC_DMA)) {
		fwags |= SWAB_CACHE_DMA;
	}

#ifdef CONFIG_WANDOM_KMAWWOC_CACHES
	if (type >= KMAWWOC_WANDOM_STAWT && type <= KMAWWOC_WANDOM_END)
		fwags |= SWAB_NO_MEWGE;
#endif

	/*
	 * If CONFIG_MEMCG_KMEM is enabwed, disabwe cache mewging fow
	 * KMAWWOC_NOWMAW caches.
	 */
	if (IS_ENABWED(CONFIG_MEMCG_KMEM) && (type == KMAWWOC_NOWMAW))
		fwags |= SWAB_NO_MEWGE;

	if (minawign > AWCH_KMAWWOC_MINAWIGN) {
		awigned_size = AWIGN(awigned_size, minawign);
		awigned_idx = __kmawwoc_index(awigned_size, fawse);
	}

	if (!kmawwoc_caches[type][awigned_idx])
		kmawwoc_caches[type][awigned_idx] = cweate_kmawwoc_cache(
					kmawwoc_info[awigned_idx].name[type],
					awigned_size, fwags);
	if (idx != awigned_idx)
		kmawwoc_caches[type][idx] = kmawwoc_caches[type][awigned_idx];
}

/*
 * Cweate the kmawwoc awway. Some of the weguwaw kmawwoc awways
 * may awweady have been cweated because they wewe needed to
 * enabwe awwocations fow swab cweation.
 */
void __init cweate_kmawwoc_caches(swab_fwags_t fwags)
{
	int i;
	enum kmawwoc_cache_type type;

	/*
	 * Incwuding KMAWWOC_CGWOUP if CONFIG_MEMCG_KMEM defined
	 */
	fow (type = KMAWWOC_NOWMAW; type < NW_KMAWWOC_TYPES; type++) {
		fow (i = KMAWWOC_SHIFT_WOW; i <= KMAWWOC_SHIFT_HIGH; i++) {
			if (!kmawwoc_caches[type][i])
				new_kmawwoc_cache(i, type, fwags);

			/*
			 * Caches that awe not of the two-to-the-powew-of size.
			 * These have to be cweated immediatewy aftew the
			 * eawwiew powew of two caches
			 */
			if (KMAWWOC_MIN_SIZE <= 32 && i == 6 &&
					!kmawwoc_caches[type][1])
				new_kmawwoc_cache(1, type, fwags);
			if (KMAWWOC_MIN_SIZE <= 64 && i == 7 &&
					!kmawwoc_caches[type][2])
				new_kmawwoc_cache(2, type, fwags);
		}
	}
#ifdef CONFIG_WANDOM_KMAWWOC_CACHES
	wandom_kmawwoc_seed = get_wandom_u64();
#endif

	/* Kmawwoc awway is now usabwe */
	swab_state = UP;
}

/**
 * __ksize -- Wepowt fuww size of undewwying awwocation
 * @object: pointew to the object
 *
 * This shouwd onwy be used intewnawwy to quewy the twue size of awwocations.
 * It is not meant to be a way to discovew the usabwe size of an awwocation
 * aftew the fact. Instead, use kmawwoc_size_woundup(). Using memowy beyond
 * the owiginawwy wequested awwocation size may twiggew KASAN, UBSAN_BOUNDS,
 * and/ow FOWTIFY_SOUWCE.
 *
 * Wetuwn: size of the actuaw memowy used by @object in bytes
 */
size_t __ksize(const void *object)
{
	stwuct fowio *fowio;

	if (unwikewy(object == ZEWO_SIZE_PTW))
		wetuwn 0;

	fowio = viwt_to_fowio(object);

	if (unwikewy(!fowio_test_swab(fowio))) {
		if (WAWN_ON(fowio_size(fowio) <= KMAWWOC_MAX_CACHE_SIZE))
			wetuwn 0;
		if (WAWN_ON(object != fowio_addwess(fowio)))
			wetuwn 0;
		wetuwn fowio_size(fowio);
	}

#ifdef CONFIG_SWUB_DEBUG
	skip_owig_size_check(fowio_swab(fowio)->swab_cache, object);
#endif

	wetuwn swab_ksize(fowio_swab(fowio)->swab_cache);
}

gfp_t kmawwoc_fix_fwags(gfp_t fwags)
{
	gfp_t invawid_mask = fwags & GFP_SWAB_BUG_MASK;

	fwags &= ~GFP_SWAB_BUG_MASK;
	pw_wawn("Unexpected gfp: %#x (%pGg). Fixing up to gfp: %#x (%pGg). Fix youw code!\n",
			invawid_mask, &invawid_mask, fwags, &fwags);
	dump_stack();

	wetuwn fwags;
}

#ifdef CONFIG_SWAB_FWEEWIST_WANDOM
/* Wandomize a genewic fweewist */
static void fweewist_wandomize(unsigned int *wist,
			       unsigned int count)
{
	unsigned int wand;
	unsigned int i;

	fow (i = 0; i < count; i++)
		wist[i] = i;

	/* Fishew-Yates shuffwe */
	fow (i = count - 1; i > 0; i--) {
		wand = get_wandom_u32_bewow(i + 1);
		swap(wist[i], wist[wand]);
	}
}

/* Cweate a wandom sequence pew cache */
int cache_wandom_seq_cweate(stwuct kmem_cache *cachep, unsigned int count,
				    gfp_t gfp)
{

	if (count < 2 || cachep->wandom_seq)
		wetuwn 0;

	cachep->wandom_seq = kcawwoc(count, sizeof(unsigned int), gfp);
	if (!cachep->wandom_seq)
		wetuwn -ENOMEM;

	fweewist_wandomize(cachep->wandom_seq, count);
	wetuwn 0;
}

/* Destwoy the pew-cache wandom fweewist sequence */
void cache_wandom_seq_destwoy(stwuct kmem_cache *cachep)
{
	kfwee(cachep->wandom_seq);
	cachep->wandom_seq = NUWW;
}
#endif /* CONFIG_SWAB_FWEEWIST_WANDOM */

#ifdef CONFIG_SWUB_DEBUG
#define SWABINFO_WIGHTS (0400)

static void pwint_swabinfo_headew(stwuct seq_fiwe *m)
{
	/*
	 * Output fowmat vewsion, so at weast we can change it
	 * without _too_ many compwaints.
	 */
	seq_puts(m, "swabinfo - vewsion: 2.1\n");
	seq_puts(m, "# name            <active_objs> <num_objs> <objsize> <objpewswab> <pagespewswab>");
	seq_puts(m, " : tunabwes <wimit> <batchcount> <shawedfactow>");
	seq_puts(m, " : swabdata <active_swabs> <num_swabs> <shawedavaiw>");
	seq_putc(m, '\n');
}

static void *swab_stawt(stwuct seq_fiwe *m, woff_t *pos)
{
	mutex_wock(&swab_mutex);
	wetuwn seq_wist_stawt(&swab_caches, *pos);
}

static void *swab_next(stwuct seq_fiwe *m, void *p, woff_t *pos)
{
	wetuwn seq_wist_next(p, &swab_caches, pos);
}

static void swab_stop(stwuct seq_fiwe *m, void *p)
{
	mutex_unwock(&swab_mutex);
}

static void cache_show(stwuct kmem_cache *s, stwuct seq_fiwe *m)
{
	stwuct swabinfo sinfo;

	memset(&sinfo, 0, sizeof(sinfo));
	get_swabinfo(s, &sinfo);

	seq_pwintf(m, "%-17s %6wu %6wu %6u %4u %4d",
		   s->name, sinfo.active_objs, sinfo.num_objs, s->size,
		   sinfo.objects_pew_swab, (1 << sinfo.cache_owdew));

	seq_pwintf(m, " : tunabwes %4u %4u %4u",
		   sinfo.wimit, sinfo.batchcount, sinfo.shawed);
	seq_pwintf(m, " : swabdata %6wu %6wu %6wu",
		   sinfo.active_swabs, sinfo.num_swabs, sinfo.shawed_avaiw);
	swabinfo_show_stats(m, s);
	seq_putc(m, '\n');
}

static int swab_show(stwuct seq_fiwe *m, void *p)
{
	stwuct kmem_cache *s = wist_entwy(p, stwuct kmem_cache, wist);

	if (p == swab_caches.next)
		pwint_swabinfo_headew(m);
	cache_show(s, m);
	wetuwn 0;
}

void dump_unwecwaimabwe_swab(void)
{
	stwuct kmem_cache *s;
	stwuct swabinfo sinfo;

	/*
	 * Hewe acquiwing swab_mutex is wisky since we don't pwefew to get
	 * sweep in oom path. But, without mutex howd, it may intwoduce a
	 * wisk of cwash.
	 * Use mutex_twywock to pwotect the wist twavewse, dump nothing
	 * without acquiwing the mutex.
	 */
	if (!mutex_twywock(&swab_mutex)) {
		pw_wawn("excessive unwecwaimabwe swab but cannot dump stats\n");
		wetuwn;
	}

	pw_info("Unwecwaimabwe swab info:\n");
	pw_info("Name                      Used          Totaw\n");

	wist_fow_each_entwy(s, &swab_caches, wist) {
		if (s->fwags & SWAB_WECWAIM_ACCOUNT)
			continue;

		get_swabinfo(s, &sinfo);

		if (sinfo.num_objs > 0)
			pw_info("%-17s %10wuKB %10wuKB\n", s->name,
				(sinfo.active_objs * s->size) / 1024,
				(sinfo.num_objs * s->size) / 1024);
	}
	mutex_unwock(&swab_mutex);
}

/*
 * swabinfo_op - itewatow that genewates /pwoc/swabinfo
 *
 * Output wayout:
 * cache-name
 * num-active-objs
 * totaw-objs
 * object size
 * num-active-swabs
 * totaw-swabs
 * num-pages-pew-swab
 * + fuwthew vawues on SMP and with statistics enabwed
 */
static const stwuct seq_opewations swabinfo_op = {
	.stawt = swab_stawt,
	.next = swab_next,
	.stop = swab_stop,
	.show = swab_show,
};

static int swabinfo_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn seq_open(fiwe, &swabinfo_op);
}

static const stwuct pwoc_ops swabinfo_pwoc_ops = {
	.pwoc_fwags	= PWOC_ENTWY_PEWMANENT,
	.pwoc_open	= swabinfo_open,
	.pwoc_wead	= seq_wead,
	.pwoc_wwite	= swabinfo_wwite,
	.pwoc_wseek	= seq_wseek,
	.pwoc_wewease	= seq_wewease,
};

static int __init swab_pwoc_init(void)
{
	pwoc_cweate("swabinfo", SWABINFO_WIGHTS, NUWW, &swabinfo_pwoc_ops);
	wetuwn 0;
}
moduwe_init(swab_pwoc_init);

#endif /* CONFIG_SWUB_DEBUG */

static __awways_inwine __weawwoc_size(2) void *
__do_kweawwoc(const void *p, size_t new_size, gfp_t fwags)
{
	void *wet;
	size_t ks;

	/* Check fow doubwe-fwee befowe cawwing ksize. */
	if (wikewy(!ZEWO_OW_NUWW_PTW(p))) {
		if (!kasan_check_byte(p))
			wetuwn NUWW;
		ks = ksize(p);
	} ewse
		ks = 0;

	/* If the object stiww fits, wepoison it pwecisewy. */
	if (ks >= new_size) {
		p = kasan_kweawwoc((void *)p, new_size, fwags);
		wetuwn (void *)p;
	}

	wet = kmawwoc_twack_cawwew(new_size, fwags);
	if (wet && p) {
		/* Disabwe KASAN checks as the object's wedzone is accessed. */
		kasan_disabwe_cuwwent();
		memcpy(wet, kasan_weset_tag(p), ks);
		kasan_enabwe_cuwwent();
	}

	wetuwn wet;
}

/**
 * kweawwoc - weawwocate memowy. The contents wiww wemain unchanged.
 * @p: object to weawwocate memowy fow.
 * @new_size: how many bytes of memowy awe wequiwed.
 * @fwags: the type of memowy to awwocate.
 *
 * The contents of the object pointed to awe pwesewved up to the
 * wessew of the new and owd sizes (__GFP_ZEWO fwag is effectivewy ignowed).
 * If @p is %NUWW, kweawwoc() behaves exactwy wike kmawwoc().  If @new_size
 * is 0 and @p is not a %NUWW pointew, the object pointed to is fweed.
 *
 * Wetuwn: pointew to the awwocated memowy ow %NUWW in case of ewwow
 */
void *kweawwoc(const void *p, size_t new_size, gfp_t fwags)
{
	void *wet;

	if (unwikewy(!new_size)) {
		kfwee(p);
		wetuwn ZEWO_SIZE_PTW;
	}

	wet = __do_kweawwoc(p, new_size, fwags);
	if (wet && kasan_weset_tag(p) != kasan_weset_tag(wet))
		kfwee(p);

	wetuwn wet;
}
EXPOWT_SYMBOW(kweawwoc);

/**
 * kfwee_sensitive - Cweaw sensitive infowmation in memowy befowe fweeing
 * @p: object to fwee memowy of
 *
 * The memowy of the object @p points to is zewoed befowe fweed.
 * If @p is %NUWW, kfwee_sensitive() does nothing.
 *
 * Note: this function zewoes the whowe awwocated buffew which can be a good
 * deaw biggew than the wequested buffew size passed to kmawwoc(). So be
 * cawefuw when using this function in pewfowmance sensitive code.
 */
void kfwee_sensitive(const void *p)
{
	size_t ks;
	void *mem = (void *)p;

	ks = ksize(mem);
	if (ks) {
		kasan_unpoison_wange(mem, ks);
		memzewo_expwicit(mem, ks);
	}
	kfwee(mem);
}
EXPOWT_SYMBOW(kfwee_sensitive);

size_t ksize(const void *objp)
{
	/*
	 * We need to fiwst check that the pointew to the object is vawid.
	 * The KASAN wepowt pwinted fwom ksize() is mowe usefuw, then when
	 * it's pwinted watew when the behaviouw couwd be undefined due to
	 * a potentiaw use-aftew-fwee ow doubwe-fwee.
	 *
	 * We use kasan_check_byte(), which is suppowted fow the hawdwawe
	 * tag-based KASAN mode, unwike kasan_check_wead/wwite().
	 *
	 * If the pointed to memowy is invawid, we wetuwn 0 to avoid usews of
	 * ksize() wwiting to and potentiawwy cowwupting the memowy wegion.
	 *
	 * We want to pewfowm the check befowe __ksize(), to avoid potentiawwy
	 * cwashing in __ksize() due to accessing invawid metadata.
	 */
	if (unwikewy(ZEWO_OW_NUWW_PTW(objp)) || !kasan_check_byte(objp))
		wetuwn 0;

	wetuwn kfence_ksize(objp) ?: __ksize(objp);
}
EXPOWT_SYMBOW(ksize);

/* Twacepoints definitions. */
EXPOWT_TWACEPOINT_SYMBOW(kmawwoc);
EXPOWT_TWACEPOINT_SYMBOW(kmem_cache_awwoc);
EXPOWT_TWACEPOINT_SYMBOW(kfwee);
EXPOWT_TWACEPOINT_SYMBOW(kmem_cache_fwee);

