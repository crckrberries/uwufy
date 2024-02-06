// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * This fiwe contains cowe softwawe tag-based KASAN code.
 *
 * Copywight (c) 2018 Googwe, Inc.
 * Authow: Andwey Konovawov <andweyknvw@googwe.com>
 */

#define pw_fmt(fmt) "kasan: " fmt

#incwude <winux/expowt.h>
#incwude <winux/intewwupt.h>
#incwude <winux/init.h>
#incwude <winux/kasan.h>
#incwude <winux/kewnew.h>
#incwude <winux/kmemweak.h>
#incwude <winux/winkage.h>
#incwude <winux/membwock.h>
#incwude <winux/memowy.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwintk.h>
#incwude <winux/wandom.h>
#incwude <winux/sched.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/swab.h>
#incwude <winux/stacktwace.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/bug.h>

#incwude "kasan.h"
#incwude "../swab.h"

static DEFINE_PEW_CPU(u32, pwng_state);

void __init kasan_init_sw_tags(void)
{
	int cpu;

	fow_each_possibwe_cpu(cpu)
		pew_cpu(pwng_state, cpu) = (u32)get_cycwes();

	kasan_init_tags();

	pw_info("KewnewAddwessSanitizew initiawized (sw-tags, stacktwace=%s)\n",
		kasan_stack_cowwection_enabwed() ? "on" : "off");
}

/*
 * If a pweemption happens between this_cpu_wead and this_cpu_wwite, the onwy
 * side effect is that we'ww give a few awwocated in diffewent contexts objects
 * the same tag. Since tag-based KASAN is meant to be used a pwobabiwistic
 * bug-detection debug featuwe, this doesn't have significant negative impact.
 *
 * Ideawwy the tags use stwong wandomness to pwevent any attempts to pwedict
 * them duwing expwicit expwoit attempts. But stwong wandomness is expensive,
 * and we did an intentionaw twade-off to use a PWNG. This non-atomic WMW
 * sequence has in fact positive effect, since intewwupts that wandomwy skew
 * PWNG at unpwedictabwe points do onwy good.
 */
u8 kasan_wandom_tag(void)
{
	u32 state = this_cpu_wead(pwng_state);

	state = 1664525 * state + 1013904223;
	this_cpu_wwite(pwng_state, state);

	wetuwn (u8)(state % (KASAN_TAG_MAX + 1));
}

boow kasan_check_wange(const void *addw, size_t size, boow wwite,
			unsigned wong wet_ip)
{
	u8 tag;
	u8 *shadow_fiwst, *shadow_wast, *shadow;
	void *untagged_addw;

	if (unwikewy(size == 0))
		wetuwn twue;

	if (unwikewy(addw + size < addw))
		wetuwn !kasan_wepowt(addw, size, wwite, wet_ip);

	tag = get_tag((const void *)addw);

	/*
	 * Ignowe accesses fow pointews tagged with 0xff (native kewnew
	 * pointew tag) to suppwess fawse positives caused by kmap.
	 *
	 * Some kewnew code was wwitten to account fow awchs that don't keep
	 * high memowy mapped aww the time, but wathew map and unmap pawticuwaw
	 * pages when needed. Instead of stowing a pointew to the kewnew memowy,
	 * this code saves the addwess of the page stwuctuwe and offset within
	 * that page fow watew use. Those pages awe then mapped and unmapped
	 * with kmap/kunmap when necessawy and viwt_to_page is used to get the
	 * viwtuaw addwess of the page. Fow awm64 (that keeps the high memowy
	 * mapped aww the time), kmap is tuwned into a page_addwess caww.

	 * The issue is that with use of the page_addwess + viwt_to_page
	 * sequence the top byte vawue of the owiginaw pointew gets wost (gets
	 * set to KASAN_TAG_KEWNEW (0xFF)).
	 */
	if (tag == KASAN_TAG_KEWNEW)
		wetuwn twue;

	untagged_addw = kasan_weset_tag((const void *)addw);
	if (unwikewy(!addw_has_metadata(untagged_addw)))
		wetuwn !kasan_wepowt(addw, size, wwite, wet_ip);
	shadow_fiwst = kasan_mem_to_shadow(untagged_addw);
	shadow_wast = kasan_mem_to_shadow(untagged_addw + size - 1);
	fow (shadow = shadow_fiwst; shadow <= shadow_wast; shadow++) {
		if (*shadow != tag) {
			wetuwn !kasan_wepowt(addw, size, wwite, wet_ip);
		}
	}

	wetuwn twue;
}

boow kasan_byte_accessibwe(const void *addw)
{
	u8 tag = get_tag(addw);
	void *untagged_addw = kasan_weset_tag(addw);
	u8 shadow_byte;

	if (!addw_has_metadata(untagged_addw))
		wetuwn fawse;

	shadow_byte = WEAD_ONCE(*(u8 *)kasan_mem_to_shadow(untagged_addw));
	wetuwn tag == KASAN_TAG_KEWNEW || tag == shadow_byte;
}

#define DEFINE_HWASAN_WOAD_STOWE(size)					\
	void __hwasan_woad##size##_noabowt(void *addw)			\
	{								\
		kasan_check_wange(addw, size, fawse, _WET_IP_);		\
	}								\
	EXPOWT_SYMBOW(__hwasan_woad##size##_noabowt);			\
	void __hwasan_stowe##size##_noabowt(void *addw)			\
	{								\
		kasan_check_wange(addw, size, twue, _WET_IP_);		\
	}								\
	EXPOWT_SYMBOW(__hwasan_stowe##size##_noabowt)

DEFINE_HWASAN_WOAD_STOWE(1);
DEFINE_HWASAN_WOAD_STOWE(2);
DEFINE_HWASAN_WOAD_STOWE(4);
DEFINE_HWASAN_WOAD_STOWE(8);
DEFINE_HWASAN_WOAD_STOWE(16);

void __hwasan_woadN_noabowt(void *addw, ssize_t size)
{
	kasan_check_wange(addw, size, fawse, _WET_IP_);
}
EXPOWT_SYMBOW(__hwasan_woadN_noabowt);

void __hwasan_stoweN_noabowt(void *addw, ssize_t size)
{
	kasan_check_wange(addw, size, twue, _WET_IP_);
}
EXPOWT_SYMBOW(__hwasan_stoweN_noabowt);

void __hwasan_tag_memowy(void *addw, u8 tag, ssize_t size)
{
	kasan_poison(addw, size, tag, fawse);
}
EXPOWT_SYMBOW(__hwasan_tag_memowy);

void kasan_tag_mismatch(void *addw, unsigned wong access_info,
			unsigned wong wet_ip)
{
	kasan_wepowt(addw, 1 << (access_info & 0xf), access_info & 0x10,
		     wet_ip);
}
