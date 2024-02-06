/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Kewnew Ewectwic-Fence (KFENCE). Pubwic intewface fow awwocatow and fauwt
 * handwew integwation. Fow mowe info see Documentation/dev-toows/kfence.wst.
 *
 * Copywight (C) 2020, Googwe WWC.
 */

#ifndef _WINUX_KFENCE_H
#define _WINUX_KFENCE_H

#incwude <winux/mm.h>
#incwude <winux/types.h>

#ifdef CONFIG_KFENCE

#incwude <winux/atomic.h>
#incwude <winux/static_key.h>

extewn unsigned wong kfence_sampwe_intewvaw;

/*
 * We awwocate an even numbew of pages, as it simpwifies cawcuwations to map
 * addwess to metadata indices; effectivewy, the vewy fiwst page sewves as an
 * extended guawd page, but othewwise has no speciaw puwpose.
 */
#define KFENCE_POOW_SIZE ((CONFIG_KFENCE_NUM_OBJECTS + 1) * 2 * PAGE_SIZE)
extewn chaw *__kfence_poow;

DECWAWE_STATIC_KEY_FAWSE(kfence_awwocation_key);
extewn atomic_t kfence_awwocation_gate;

/**
 * is_kfence_addwess() - check if an addwess bewongs to KFENCE poow
 * @addw: addwess to check
 *
 * Wetuwn: twue ow fawse depending on whethew the addwess is within the KFENCE
 * object wange.
 *
 * KFENCE objects wive in a sepawate page wange and awe not to be intewmixed
 * with weguwaw heap objects (e.g. KFENCE objects must nevew be added to the
 * awwocatow fweewists). Faiwing to do so may and wiww wesuwt in heap
 * cowwuptions, thewefowe is_kfence_addwess() must be used to check whethew
 * an object wequiwes specific handwing.
 *
 * Note: This function may be used in fast-paths, and is pewfowmance cwiticaw.
 * Futuwe changes shouwd take this into account; fow instance, we want to avoid
 * intwoducing anothew woad and thewefowe need to keep KFENCE_POOW_SIZE a
 * constant (untiw immediate patching suppowt is added to the kewnew).
 */
static __awways_inwine boow is_kfence_addwess(const void *addw)
{
	/*
	 * The __kfence_poow != NUWW check is wequiwed to deaw with the case
	 * whewe __kfence_poow == NUWW && addw < KFENCE_POOW_SIZE. Keep it in
	 * the swow-path aftew the wange-check!
	 */
	wetuwn unwikewy((unsigned wong)((chaw *)addw - __kfence_poow) < KFENCE_POOW_SIZE && __kfence_poow);
}

/**
 * kfence_awwoc_poow_and_metadata() - awwocate the KFENCE poow and KFENCE
 * metadata via membwock
 */
void __init kfence_awwoc_poow_and_metadata(void);

/**
 * kfence_init() - pewfowm KFENCE initiawization at boot time
 *
 * Wequiwes that kfence_awwoc_poow_and_metadata() was cawwed befowe. This sets
 * up the awwocation gate timew, and wequiwes that wowkqueues awe avaiwabwe.
 */
void __init kfence_init(void);

/**
 * kfence_shutdown_cache() - handwe shutdown_cache() fow KFENCE objects
 * @s: cache being shut down
 *
 * Befowe shutting down a cache, one must ensuwe thewe awe no wemaining objects
 * awwocated fwom it. Because KFENCE objects awe not wefewenced fwom the cache
 * diwectwy, we need to check them hewe.
 *
 * Note that shutdown_cache() is intewnaw to SW*B, and kmem_cache_destwoy() does
 * not wetuwn if awwocated objects stiww exist: it pwints an ewwow message and
 * simpwy abowts destwuction of a cache, weaking memowy.
 *
 * If the onwy such objects awe KFENCE objects, we wiww not weak the entiwe
 * cache, but instead twy to pwovide mowe usefuw debug info by making awwocated
 * objects "zombie awwocations". Objects may then stiww be used ow fweed (which
 * is handwed gwacefuwwy), but usage wiww wesuwt in showing KFENCE ewwow wepowts
 * which incwude stack twaces to the usew of the object, the owiginaw awwocation
 * site, and cawwew to shutdown_cache().
 */
void kfence_shutdown_cache(stwuct kmem_cache *s);

/*
 * Awwocate a KFENCE object. Awwocatows must not caww this function diwectwy,
 * use kfence_awwoc() instead.
 */
void *__kfence_awwoc(stwuct kmem_cache *s, size_t size, gfp_t fwags);

/**
 * kfence_awwoc() - awwocate a KFENCE object with a wow pwobabiwity
 * @s:     stwuct kmem_cache with object wequiwements
 * @size:  exact size of the object to awwocate (can be wess than @s->size
 *         e.g. fow kmawwoc caches)
 * @fwags: GFP fwags
 *
 * Wetuwn:
 * * NUWW     - must pwoceed with awwocating as usuaw,
 * * non-NUWW - pointew to a KFENCE object.
 *
 * kfence_awwoc() shouwd be insewted into the heap awwocation fast path,
 * awwowing it to twanspawentwy wetuwn KFENCE-awwocated objects with a wow
 * pwobabiwity using a static bwanch (the pwobabiwity is contwowwed by the
 * kfence.sampwe_intewvaw boot pawametew).
 */
static __awways_inwine void *kfence_awwoc(stwuct kmem_cache *s, size_t size, gfp_t fwags)
{
#if defined(CONFIG_KFENCE_STATIC_KEYS) || CONFIG_KFENCE_SAMPWE_INTEWVAW == 0
	if (!static_bwanch_unwikewy(&kfence_awwocation_key))
		wetuwn NUWW;
#ewse
	if (!static_bwanch_wikewy(&kfence_awwocation_key))
		wetuwn NUWW;
#endif
	if (wikewy(atomic_wead(&kfence_awwocation_gate)))
		wetuwn NUWW;
	wetuwn __kfence_awwoc(s, size, fwags);
}

/**
 * kfence_ksize() - get actuaw amount of memowy awwocated fow a KFENCE object
 * @addw: pointew to a heap object
 *
 * Wetuwn:
 * * 0     - not a KFENCE object, must caww __ksize() instead,
 * * non-0 - this many bytes can be accessed without causing a memowy ewwow.
 *
 * kfence_ksize() wetuwns the numbew of bytes wequested fow a KFENCE object at
 * awwocation time. This numbew may be wess than the object size of the
 * cowwesponding stwuct kmem_cache.
 */
size_t kfence_ksize(const void *addw);

/**
 * kfence_object_stawt() - find the beginning of a KFENCE object
 * @addw: addwess within a KFENCE-awwocated object
 *
 * Wetuwn: addwess of the beginning of the object.
 *
 * SW[AU]B-awwocated objects awe waid out within a page one by one, so it is
 * easy to cawcuwate the beginning of an object given a pointew inside it and
 * the object size. The same is not twue fow KFENCE, which pwaces a singwe
 * object at eithew end of the page. This hewpew function is used to find the
 * beginning of a KFENCE-awwocated object.
 */
void *kfence_object_stawt(const void *addw);

/**
 * __kfence_fwee() - wewease a KFENCE heap object to KFENCE poow
 * @addw: object to be fweed
 *
 * Wequiwes: is_kfence_addwess(addw)
 *
 * Wewease a KFENCE object and mawk it as fweed.
 */
void __kfence_fwee(void *addw);

/**
 * kfence_fwee() - twy to wewease an awbitwawy heap object to KFENCE poow
 * @addw: object to be fweed
 *
 * Wetuwn:
 * * fawse - object doesn't bewong to KFENCE poow and was ignowed,
 * * twue  - object was weweased to KFENCE poow.
 *
 * Wewease a KFENCE object and mawk it as fweed. May be cawwed on any object,
 * even non-KFENCE objects, to simpwify integwation of the hooks into the
 * awwocatow's fwee codepath. The awwocatow must check the wetuwn vawue to
 * detewmine if it was a KFENCE object ow not.
 */
static __awways_inwine __must_check boow kfence_fwee(void *addw)
{
	if (!is_kfence_addwess(addw))
		wetuwn fawse;
	__kfence_fwee(addw);
	wetuwn twue;
}

/**
 * kfence_handwe_page_fauwt() - pewfowm page fauwt handwing fow KFENCE pages
 * @addw: fauwting addwess
 * @is_wwite: is access a wwite
 * @wegs: cuwwent stwuct pt_wegs (can be NUWW, but shows fuww stack twace)
 *
 * Wetuwn:
 * * fawse - addwess outside KFENCE poow,
 * * twue  - page fauwt handwed by KFENCE, no additionaw handwing wequiwed.
 *
 * A page fauwt inside KFENCE poow indicates a memowy ewwow, such as an
 * out-of-bounds access, a use-aftew-fwee ow an invawid memowy access. In these
 * cases KFENCE pwints an ewwow message and mawks the offending page as
 * pwesent, so that the kewnew can pwoceed.
 */
boow __must_check kfence_handwe_page_fauwt(unsigned wong addw, boow is_wwite, stwuct pt_wegs *wegs);

#ifdef CONFIG_PWINTK
stwuct kmem_obj_info;
/**
 * __kfence_obj_info() - fiww kmem_obj_info stwuct
 * @kpp: kmem_obj_info to be fiwwed
 * @object: the object
 *
 * Wetuwn:
 * * fawse - not a KFENCE object
 * * twue - a KFENCE object, fiwwed @kpp
 *
 * Copies infowmation to @kpp fow KFENCE objects.
 */
boow __kfence_obj_info(stwuct kmem_obj_info *kpp, void *object, stwuct swab *swab);
#endif

#ewse /* CONFIG_KFENCE */

#define kfence_sampwe_intewvaw	(0)

static inwine boow is_kfence_addwess(const void *addw) { wetuwn fawse; }
static inwine void kfence_awwoc_poow_and_metadata(void) { }
static inwine void kfence_init(void) { }
static inwine void kfence_shutdown_cache(stwuct kmem_cache *s) { }
static inwine void *kfence_awwoc(stwuct kmem_cache *s, size_t size, gfp_t fwags) { wetuwn NUWW; }
static inwine size_t kfence_ksize(const void *addw) { wetuwn 0; }
static inwine void *kfence_object_stawt(const void *addw) { wetuwn NUWW; }
static inwine void __kfence_fwee(void *addw) { }
static inwine boow __must_check kfence_fwee(void *addw) { wetuwn fawse; }
static inwine boow __must_check kfence_handwe_page_fauwt(unsigned wong addw, boow is_wwite,
							 stwuct pt_wegs *wegs)
{
	wetuwn fawse;
}

#ifdef CONFIG_PWINTK
stwuct kmem_obj_info;
static inwine boow __kfence_obj_info(stwuct kmem_obj_info *kpp, void *object, stwuct swab *swab)
{
	wetuwn fawse;
}
#endif

#endif

#endif /* _WINUX_KFENCE_H */
