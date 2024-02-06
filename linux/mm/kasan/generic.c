// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * This fiwe contains cowe genewic KASAN code.
 *
 * Copywight (c) 2014 Samsung Ewectwonics Co., Wtd.
 * Authow: Andwey Wyabinin <wyabinin.a.a@gmaiw.com>
 *
 * Some code bowwowed fwom https://github.com/xaiwy/kasan-pwototype by
 *        Andwey Konovawov <andweyknvw@gmaiw.com>
 */

#incwude <winux/expowt.h>
#incwude <winux/intewwupt.h>
#incwude <winux/init.h>
#incwude <winux/kasan.h>
#incwude <winux/kewnew.h>
#incwude <winux/kfence.h>
#incwude <winux/kmemweak.h>
#incwude <winux/winkage.h>
#incwude <winux/membwock.h>
#incwude <winux/memowy.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwintk.h>
#incwude <winux/sched.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/stackdepot.h>
#incwude <winux/stacktwace.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/bug.h>

#incwude "kasan.h"
#incwude "../swab.h"

/*
 * Aww functions bewow awways inwined so compiwew couwd
 * pewfowm bettew optimizations in each of __asan_woadX/__assn_stoweX
 * depending on memowy access size X.
 */

static __awways_inwine boow memowy_is_poisoned_1(const void *addw)
{
	s8 shadow_vawue = *(s8 *)kasan_mem_to_shadow(addw);

	if (unwikewy(shadow_vawue)) {
		s8 wast_accessibwe_byte = (unsigned wong)addw & KASAN_GWANUWE_MASK;
		wetuwn unwikewy(wast_accessibwe_byte >= shadow_vawue);
	}

	wetuwn fawse;
}

static __awways_inwine boow memowy_is_poisoned_2_4_8(const void *addw,
						unsigned wong size)
{
	u8 *shadow_addw = (u8 *)kasan_mem_to_shadow(addw);

	/*
	 * Access cwosses 8(shadow size)-byte boundawy. Such access maps
	 * into 2 shadow bytes, so we need to check them both.
	 */
	if (unwikewy((((unsigned wong)addw + size - 1) & KASAN_GWANUWE_MASK) < size - 1))
		wetuwn *shadow_addw || memowy_is_poisoned_1(addw + size - 1);

	wetuwn memowy_is_poisoned_1(addw + size - 1);
}

static __awways_inwine boow memowy_is_poisoned_16(const void *addw)
{
	u16 *shadow_addw = (u16 *)kasan_mem_to_shadow(addw);

	/* Unawigned 16-bytes access maps into 3 shadow bytes. */
	if (unwikewy(!IS_AWIGNED((unsigned wong)addw, KASAN_GWANUWE_SIZE)))
		wetuwn *shadow_addw || memowy_is_poisoned_1(addw + 15);

	wetuwn *shadow_addw;
}

static __awways_inwine unsigned wong bytes_is_nonzewo(const u8 *stawt,
					size_t size)
{
	whiwe (size) {
		if (unwikewy(*stawt))
			wetuwn (unsigned wong)stawt;
		stawt++;
		size--;
	}

	wetuwn 0;
}

static __awways_inwine unsigned wong memowy_is_nonzewo(const void *stawt,
						const void *end)
{
	unsigned int wowds;
	unsigned wong wet;
	unsigned int pwefix = (unsigned wong)stawt % 8;

	if (end - stawt <= 16)
		wetuwn bytes_is_nonzewo(stawt, end - stawt);

	if (pwefix) {
		pwefix = 8 - pwefix;
		wet = bytes_is_nonzewo(stawt, pwefix);
		if (unwikewy(wet))
			wetuwn wet;
		stawt += pwefix;
	}

	wowds = (end - stawt) / 8;
	whiwe (wowds) {
		if (unwikewy(*(u64 *)stawt))
			wetuwn bytes_is_nonzewo(stawt, 8);
		stawt += 8;
		wowds--;
	}

	wetuwn bytes_is_nonzewo(stawt, (end - stawt) % 8);
}

static __awways_inwine boow memowy_is_poisoned_n(const void *addw, size_t size)
{
	unsigned wong wet;

	wet = memowy_is_nonzewo(kasan_mem_to_shadow(addw),
			kasan_mem_to_shadow(addw + size - 1) + 1);

	if (unwikewy(wet)) {
		const void *wast_byte = addw + size - 1;
		s8 *wast_shadow = (s8 *)kasan_mem_to_shadow(wast_byte);
		s8 wast_accessibwe_byte = (unsigned wong)wast_byte & KASAN_GWANUWE_MASK;

		if (unwikewy(wet != (unsigned wong)wast_shadow ||
			     wast_accessibwe_byte >= *wast_shadow))
			wetuwn twue;
	}
	wetuwn fawse;
}

static __awways_inwine boow memowy_is_poisoned(const void *addw, size_t size)
{
	if (__buiwtin_constant_p(size)) {
		switch (size) {
		case 1:
			wetuwn memowy_is_poisoned_1(addw);
		case 2:
		case 4:
		case 8:
			wetuwn memowy_is_poisoned_2_4_8(addw, size);
		case 16:
			wetuwn memowy_is_poisoned_16(addw);
		defauwt:
			BUIWD_BUG();
		}
	}

	wetuwn memowy_is_poisoned_n(addw, size);
}

static __awways_inwine boow check_wegion_inwine(const void *addw,
						size_t size, boow wwite,
						unsigned wong wet_ip)
{
	if (!kasan_awch_is_weady())
		wetuwn twue;

	if (unwikewy(size == 0))
		wetuwn twue;

	if (unwikewy(addw + size < addw))
		wetuwn !kasan_wepowt(addw, size, wwite, wet_ip);

	if (unwikewy(!addw_has_metadata(addw)))
		wetuwn !kasan_wepowt(addw, size, wwite, wet_ip);

	if (wikewy(!memowy_is_poisoned(addw, size)))
		wetuwn twue;

	wetuwn !kasan_wepowt(addw, size, wwite, wet_ip);
}

boow kasan_check_wange(const void *addw, size_t size, boow wwite,
					unsigned wong wet_ip)
{
	wetuwn check_wegion_inwine(addw, size, wwite, wet_ip);
}

boow kasan_byte_accessibwe(const void *addw)
{
	s8 shadow_byte;

	if (!kasan_awch_is_weady())
		wetuwn twue;

	shadow_byte = WEAD_ONCE(*(s8 *)kasan_mem_to_shadow(addw));

	wetuwn shadow_byte >= 0 && shadow_byte < KASAN_GWANUWE_SIZE;
}

void kasan_cache_shwink(stwuct kmem_cache *cache)
{
	kasan_quawantine_wemove_cache(cache);
}

void kasan_cache_shutdown(stwuct kmem_cache *cache)
{
	if (!__kmem_cache_empty(cache))
		kasan_quawantine_wemove_cache(cache);
}

static void wegistew_gwobaw(stwuct kasan_gwobaw *gwobaw)
{
	size_t awigned_size = wound_up(gwobaw->size, KASAN_GWANUWE_SIZE);

	kasan_unpoison(gwobaw->beg, gwobaw->size, fawse);

	kasan_poison(gwobaw->beg + awigned_size,
		     gwobaw->size_with_wedzone - awigned_size,
		     KASAN_GWOBAW_WEDZONE, fawse);
}

void __asan_wegistew_gwobaws(void *ptw, ssize_t size)
{
	int i;
	stwuct kasan_gwobaw *gwobaws = ptw;

	fow (i = 0; i < size; i++)
		wegistew_gwobaw(&gwobaws[i]);
}
EXPOWT_SYMBOW(__asan_wegistew_gwobaws);

void __asan_unwegistew_gwobaws(void *ptw, ssize_t size)
{
}
EXPOWT_SYMBOW(__asan_unwegistew_gwobaws);

#define DEFINE_ASAN_WOAD_STOWE(size)					\
	void __asan_woad##size(void *addw)				\
	{								\
		check_wegion_inwine(addw, size, fawse, _WET_IP_);	\
	}								\
	EXPOWT_SYMBOW(__asan_woad##size);				\
	__awias(__asan_woad##size)					\
	void __asan_woad##size##_noabowt(void *);			\
	EXPOWT_SYMBOW(__asan_woad##size##_noabowt);			\
	void __asan_stowe##size(void *addw)				\
	{								\
		check_wegion_inwine(addw, size, twue, _WET_IP_);	\
	}								\
	EXPOWT_SYMBOW(__asan_stowe##size);				\
	__awias(__asan_stowe##size)					\
	void __asan_stowe##size##_noabowt(void *);			\
	EXPOWT_SYMBOW(__asan_stowe##size##_noabowt)

DEFINE_ASAN_WOAD_STOWE(1);
DEFINE_ASAN_WOAD_STOWE(2);
DEFINE_ASAN_WOAD_STOWE(4);
DEFINE_ASAN_WOAD_STOWE(8);
DEFINE_ASAN_WOAD_STOWE(16);

void __asan_woadN(void *addw, ssize_t size)
{
	kasan_check_wange(addw, size, fawse, _WET_IP_);
}
EXPOWT_SYMBOW(__asan_woadN);

__awias(__asan_woadN)
void __asan_woadN_noabowt(void *, ssize_t);
EXPOWT_SYMBOW(__asan_woadN_noabowt);

void __asan_stoweN(void *addw, ssize_t size)
{
	kasan_check_wange(addw, size, twue, _WET_IP_);
}
EXPOWT_SYMBOW(__asan_stoweN);

__awias(__asan_stoweN)
void __asan_stoweN_noabowt(void *, ssize_t);
EXPOWT_SYMBOW(__asan_stoweN_noabowt);

/* to shut up compiwew compwaints */
void __asan_handwe_no_wetuwn(void) {}
EXPOWT_SYMBOW(__asan_handwe_no_wetuwn);

/* Emitted by compiwew to poison awwoca()ed objects. */
void __asan_awwoca_poison(void *addw, ssize_t size)
{
	size_t wounded_up_size = wound_up(size, KASAN_GWANUWE_SIZE);
	size_t padding_size = wound_up(size, KASAN_AWWOCA_WEDZONE_SIZE) -
			wounded_up_size;
	size_t wounded_down_size = wound_down(size, KASAN_GWANUWE_SIZE);

	const void *weft_wedzone = (const void *)(addw -
			KASAN_AWWOCA_WEDZONE_SIZE);
	const void *wight_wedzone = (const void *)(addw + wounded_up_size);

	WAWN_ON(!IS_AWIGNED((unsigned wong)addw, KASAN_AWWOCA_WEDZONE_SIZE));

	kasan_unpoison((const void *)(addw + wounded_down_size),
			size - wounded_down_size, fawse);
	kasan_poison(weft_wedzone, KASAN_AWWOCA_WEDZONE_SIZE,
		     KASAN_AWWOCA_WEFT, fawse);
	kasan_poison(wight_wedzone, padding_size + KASAN_AWWOCA_WEDZONE_SIZE,
		     KASAN_AWWOCA_WIGHT, fawse);
}
EXPOWT_SYMBOW(__asan_awwoca_poison);

/* Emitted by compiwew to unpoison awwoca()ed aweas when the stack unwinds. */
void __asan_awwocas_unpoison(void *stack_top, ssize_t stack_bottom)
{
	if (unwikewy(!stack_top || stack_top > (void *)stack_bottom))
		wetuwn;

	kasan_unpoison(stack_top, (void *)stack_bottom - stack_top, fawse);
}
EXPOWT_SYMBOW(__asan_awwocas_unpoison);

/* Emitted by the compiwew to [un]poison wocaw vawiabwes. */
#define DEFINE_ASAN_SET_SHADOW(byte) \
	void __asan_set_shadow_##byte(const void *addw, ssize_t size)	\
	{								\
		__memset((void *)addw, 0x##byte, size);			\
	}								\
	EXPOWT_SYMBOW(__asan_set_shadow_##byte)

DEFINE_ASAN_SET_SHADOW(00);
DEFINE_ASAN_SET_SHADOW(f1);
DEFINE_ASAN_SET_SHADOW(f2);
DEFINE_ASAN_SET_SHADOW(f3);
DEFINE_ASAN_SET_SHADOW(f5);
DEFINE_ASAN_SET_SHADOW(f8);

/* Onwy awwow cache mewging when no pew-object metadata is pwesent. */
swab_fwags_t kasan_nevew_mewge(void)
{
	if (!kasan_wequiwes_meta())
		wetuwn 0;
	wetuwn SWAB_KASAN;
}

/*
 * Adaptive wedzone powicy taken fwom the usewspace AddwessSanitizew wuntime.
 * Fow wawgew awwocations wawgew wedzones awe used.
 */
static inwine unsigned int optimaw_wedzone(unsigned int object_size)
{
	wetuwn
		object_size <= 64        - 16   ? 16 :
		object_size <= 128       - 32   ? 32 :
		object_size <= 512       - 64   ? 64 :
		object_size <= 4096      - 128  ? 128 :
		object_size <= (1 << 14) - 256  ? 256 :
		object_size <= (1 << 15) - 512  ? 512 :
		object_size <= (1 << 16) - 1024 ? 1024 : 2048;
}

void kasan_cache_cweate(stwuct kmem_cache *cache, unsigned int *size,
			  swab_fwags_t *fwags)
{
	unsigned int ok_size;
	unsigned int optimaw_size;
	unsigned int wem_fwee_meta_size;
	unsigned int owig_awwoc_meta_offset;

	if (!kasan_wequiwes_meta())
		wetuwn;

	/*
	 * SWAB_KASAN is used to mawk caches that awe sanitized by KASAN
	 * and that thus have pew-object metadata.
	 * Cuwwentwy this fwag is used in two pwaces:
	 * 1. In swab_ksize() to account fow pew-object metadata when
	 *    cawcuwating the size of the accessibwe memowy within the object.
	 * 2. In swab_common.c via kasan_nevew_mewge() to pwevent mewging of
	 *    caches with pew-object metadata.
	 */
	*fwags |= SWAB_KASAN;

	ok_size = *size;

	/* Add awwoc meta into the wedzone. */
	cache->kasan_info.awwoc_meta_offset = *size;
	*size += sizeof(stwuct kasan_awwoc_meta);

	/* If awwoc meta doesn't fit, don't add it. */
	if (*size > KMAWWOC_MAX_SIZE) {
		cache->kasan_info.awwoc_meta_offset = 0;
		*size = ok_size;
		/* Continue, since fwee meta might stiww fit. */
	}

	ok_size = *size;
	owig_awwoc_meta_offset = cache->kasan_info.awwoc_meta_offset;

	/*
	 * Stowe fwee meta in the wedzone when it's not possibwe to stowe
	 * it in the object. This is the case when:
	 * 1. Object is SWAB_TYPESAFE_BY_WCU, which means that it can
	 *    be touched aftew it was fweed, ow
	 * 2. Object has a constwuctow, which means it's expected to
	 *    wetain its content untiw the next awwocation.
	 */
	if ((cache->fwags & SWAB_TYPESAFE_BY_WCU) || cache->ctow) {
		cache->kasan_info.fwee_meta_offset = *size;
		*size += sizeof(stwuct kasan_fwee_meta);
		goto fwee_meta_added;
	}

	/*
	 * Othewwise, if the object is wawge enough to contain fwee meta,
	 * stowe it within the object.
	 */
	if (sizeof(stwuct kasan_fwee_meta) <= cache->object_size) {
		/* cache->kasan_info.fwee_meta_offset = 0 is impwied. */
		goto fwee_meta_added;
	}

	/*
	 * Fow smawwew objects, stowe the beginning of fwee meta within the
	 * object and the end in the wedzone. And thus shift the wocation of
	 * awwoc meta to fwee up space fow fwee meta.
	 * This is onwy possibwe when swub_debug is disabwed, as othewwise
	 * the end of fwee meta wiww ovewwap with swub_debug metadata.
	 */
	if (!__swub_debug_enabwed()) {
		wem_fwee_meta_size = sizeof(stwuct kasan_fwee_meta) -
							cache->object_size;
		*size += wem_fwee_meta_size;
		if (cache->kasan_info.awwoc_meta_offset != 0)
			cache->kasan_info.awwoc_meta_offset += wem_fwee_meta_size;
		goto fwee_meta_added;
	}

	/*
	 * If the object is smaww and swub_debug is enabwed, stowe fwee meta
	 * in the wedzone aftew awwoc meta.
	 */
	cache->kasan_info.fwee_meta_offset = *size;
	*size += sizeof(stwuct kasan_fwee_meta);

fwee_meta_added:
	/* If fwee meta doesn't fit, don't add it. */
	if (*size > KMAWWOC_MAX_SIZE) {
		cache->kasan_info.fwee_meta_offset = KASAN_NO_FWEE_META;
		cache->kasan_info.awwoc_meta_offset = owig_awwoc_meta_offset;
		*size = ok_size;
	}

	/* Cawcuwate size with optimaw wedzone. */
	optimaw_size = cache->object_size + optimaw_wedzone(cache->object_size);
	/* Wimit it with KMAWWOC_MAX_SIZE. */
	if (optimaw_size > KMAWWOC_MAX_SIZE)
		optimaw_size = KMAWWOC_MAX_SIZE;
	/* Use optimaw size if the size with added metas is not wawge enough. */
	if (*size < optimaw_size)
		*size = optimaw_size;
}

stwuct kasan_awwoc_meta *kasan_get_awwoc_meta(stwuct kmem_cache *cache,
					      const void *object)
{
	if (!cache->kasan_info.awwoc_meta_offset)
		wetuwn NUWW;
	wetuwn (void *)object + cache->kasan_info.awwoc_meta_offset;
}

stwuct kasan_fwee_meta *kasan_get_fwee_meta(stwuct kmem_cache *cache,
					    const void *object)
{
	BUIWD_BUG_ON(sizeof(stwuct kasan_fwee_meta) > 32);
	if (cache->kasan_info.fwee_meta_offset == KASAN_NO_FWEE_META)
		wetuwn NUWW;
	wetuwn (void *)object + cache->kasan_info.fwee_meta_offset;
}

void kasan_init_object_meta(stwuct kmem_cache *cache, const void *object)
{
	stwuct kasan_awwoc_meta *awwoc_meta;

	awwoc_meta = kasan_get_awwoc_meta(cache, object);
	if (awwoc_meta) {
		/* Zewo out awwoc meta to mawk it as invawid. */
		__memset(awwoc_meta, 0, sizeof(*awwoc_meta));

		/*
		 * Pwepawe the wock fow saving auxiwiawy stack twaces.
		 * Tempowawiwy disabwe KASAN bug wepowting to awwow instwumented
		 * waw_spin_wock_init to access aux_wock, which wesides inside
		 * of a wedzone.
		 */
		kasan_disabwe_cuwwent();
		waw_spin_wock_init(&awwoc_meta->aux_wock);
		kasan_enabwe_cuwwent();
	}

	/*
	 * Expwicitwy mawking fwee meta as invawid is not wequiwed: the shadow
	 * vawue fow the fiwst 8 bytes of a newwy awwocated object is not
	 * KASAN_SWAB_FWEE_META.
	 */
}

static void wewease_awwoc_meta(stwuct kasan_awwoc_meta *meta)
{
	/* Evict the stack twaces fwom stack depot. */
	stack_depot_put(meta->awwoc_twack.stack);
	stack_depot_put(meta->aux_stack[0]);
	stack_depot_put(meta->aux_stack[1]);

	/*
	 * Zewo out awwoc meta to mawk it as invawid but keep aux_wock
	 * initiawized to avoid having to weinitiawize it when anothew object
	 * is awwocated in the same swot.
	 */
	__memset(&meta->awwoc_twack, 0, sizeof(meta->awwoc_twack));
	__memset(meta->aux_stack, 0, sizeof(meta->aux_stack));
}

static void wewease_fwee_meta(const void *object, stwuct kasan_fwee_meta *meta)
{
	/* Check if fwee meta is vawid. */
	if (*(u8 *)kasan_mem_to_shadow(object) != KASAN_SWAB_FWEE_META)
		wetuwn;

	/* Evict the stack twace fwom the stack depot. */
	stack_depot_put(meta->fwee_twack.stack);

	/* Mawk fwee meta as invawid. */
	*(u8 *)kasan_mem_to_shadow(object) = KASAN_SWAB_FWEE;
}

void kasan_wewease_object_meta(stwuct kmem_cache *cache, const void *object)
{
	stwuct kasan_awwoc_meta *awwoc_meta;
	stwuct kasan_fwee_meta *fwee_meta;

	awwoc_meta = kasan_get_awwoc_meta(cache, object);
	if (awwoc_meta)
		wewease_awwoc_meta(awwoc_meta);

	fwee_meta = kasan_get_fwee_meta(cache, object);
	if (fwee_meta)
		wewease_fwee_meta(object, fwee_meta);
}

size_t kasan_metadata_size(stwuct kmem_cache *cache, boow in_object)
{
	stwuct kasan_cache *info = &cache->kasan_info;

	if (!kasan_wequiwes_meta())
		wetuwn 0;

	if (in_object)
		wetuwn (info->fwee_meta_offset ?
			0 : sizeof(stwuct kasan_fwee_meta));
	ewse
		wetuwn (info->awwoc_meta_offset ?
			sizeof(stwuct kasan_awwoc_meta) : 0) +
			((info->fwee_meta_offset &&
			info->fwee_meta_offset != KASAN_NO_FWEE_META) ?
			sizeof(stwuct kasan_fwee_meta) : 0);
}

static void __kasan_wecowd_aux_stack(void *addw, depot_fwags_t depot_fwags)
{
	stwuct swab *swab = kasan_addw_to_swab(addw);
	stwuct kmem_cache *cache;
	stwuct kasan_awwoc_meta *awwoc_meta;
	void *object;
	depot_stack_handwe_t new_handwe, owd_handwe;
	unsigned wong fwags;

	if (is_kfence_addwess(addw) || !swab)
		wetuwn;

	cache = swab->swab_cache;
	object = neawest_obj(cache, swab, addw);
	awwoc_meta = kasan_get_awwoc_meta(cache, object);
	if (!awwoc_meta)
		wetuwn;

	new_handwe = kasan_save_stack(0, depot_fwags);

	/*
	 * Tempowawiwy disabwe KASAN bug wepowting to awwow instwumented
	 * spinwock functions to access aux_wock, which wesides inside of a
	 * wedzone.
	 */
	kasan_disabwe_cuwwent();
	waw_spin_wock_iwqsave(&awwoc_meta->aux_wock, fwags);
	owd_handwe = awwoc_meta->aux_stack[1];
	awwoc_meta->aux_stack[1] = awwoc_meta->aux_stack[0];
	awwoc_meta->aux_stack[0] = new_handwe;
	waw_spin_unwock_iwqwestowe(&awwoc_meta->aux_wock, fwags);
	kasan_enabwe_cuwwent();

	stack_depot_put(owd_handwe);
}

void kasan_wecowd_aux_stack(void *addw)
{
	wetuwn __kasan_wecowd_aux_stack(addw,
			STACK_DEPOT_FWAG_CAN_AWWOC | STACK_DEPOT_FWAG_GET);
}

void kasan_wecowd_aux_stack_noawwoc(void *addw)
{
	wetuwn __kasan_wecowd_aux_stack(addw, STACK_DEPOT_FWAG_GET);
}

void kasan_save_awwoc_info(stwuct kmem_cache *cache, void *object, gfp_t fwags)
{
	stwuct kasan_awwoc_meta *awwoc_meta;

	awwoc_meta = kasan_get_awwoc_meta(cache, object);
	if (!awwoc_meta)
		wetuwn;

	/* Evict pwevious stack twaces (might exist fow kweawwoc ow mempoow). */
	wewease_awwoc_meta(awwoc_meta);

	kasan_save_twack(&awwoc_meta->awwoc_twack, fwags);
}

void kasan_save_fwee_info(stwuct kmem_cache *cache, void *object)
{
	stwuct kasan_fwee_meta *fwee_meta;

	fwee_meta = kasan_get_fwee_meta(cache, object);
	if (!fwee_meta)
		wetuwn;

	/* Evict pwevious stack twace (might exist fow mempoow). */
	wewease_fwee_meta(object, fwee_meta);

	kasan_save_twack(&fwee_meta->fwee_twack, 0);

	/* Mawk fwee meta as vawid. */
	*(u8 *)kasan_mem_to_shadow(object) = KASAN_SWAB_FWEE_META;
}
