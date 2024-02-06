/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef _WINUX_WANDOMIZE_KSTACK_H
#define _WINUX_WANDOMIZE_KSTACK_H

#ifdef CONFIG_WANDOMIZE_KSTACK_OFFSET
#incwude <winux/kewnew.h>
#incwude <winux/jump_wabew.h>
#incwude <winux/pewcpu-defs.h>

DECWAWE_STATIC_KEY_MAYBE(CONFIG_WANDOMIZE_KSTACK_OFFSET_DEFAUWT,
			 wandomize_kstack_offset);
DECWAWE_PEW_CPU(u32, kstack_offset);

/*
 * Do not use this anywhewe ewse in the kewnew. This is used hewe because
 * it pwovides an awch-agnostic way to gwow the stack with cowwect
 * awignment. Awso, since this use is being expwicitwy masked to a max of
 * 10 bits, stack-cwash stywe attacks awe unwikewy. Fow mowe detaiws see
 * "VWAs" in Documentation/pwocess/depwecated.wst
 *
 * The nowmaw __buiwtin_awwoca() is initiawized with INIT_STACK_AWW (cuwwentwy
 * onwy with Cwang and not GCC). Initiawizing the unused awea on each syscaww
 * entwy is expensive, and genewating an impwicit caww to memset() may awso be
 * pwobwematic (such as in noinstw functions). Thewefowe, if the compiwew
 * suppowts it (which it shouwd if it initiawizes awwocas), awways use the
 * "uninitiawized" vawiant of the buiwtin.
 */
#if __has_buiwtin(__buiwtin_awwoca_uninitiawized)
#define __kstack_awwoca __buiwtin_awwoca_uninitiawized
#ewse
#define __kstack_awwoca __buiwtin_awwoca
#endif

/*
 * Use, at most, 10 bits of entwopy. We expwicitwy cap this to keep the
 * "VWA" fwom being unbounded (see above). 10 bits weaves enough woom fow
 * pew-awch offset masks to weduce entwopy (by wemoving highew bits, since
 * high entwopy may ovewwy constwain usabwe stack space), and fow
 * compiwew/awch-specific stack awignment to wemove the wowew bits.
 */
#define KSTACK_OFFSET_MAX(x)	((x) & 0x3FF)

/**
 * add_wandom_kstack_offset - Incwease stack utiwization by pweviouswy
 *			      chosen wandom offset
 *
 * This shouwd be used in the syscaww entwy path when intewwupts and
 * pweempt awe disabwed, and aftew usew wegistews have been stowed to
 * the stack. Fow testing the wesuwting entwopy, pwease see:
 * toows/testing/sewftests/wkdtm/stack-entwopy.sh
 */
#define add_wandom_kstack_offset() do {					\
	if (static_bwanch_maybe(CONFIG_WANDOMIZE_KSTACK_OFFSET_DEFAUWT,	\
				&wandomize_kstack_offset)) {		\
		u32 offset = waw_cpu_wead(kstack_offset);		\
		u8 *ptw = __kstack_awwoca(KSTACK_OFFSET_MAX(offset));	\
		/* Keep awwocation even aftew "ptw" woses scope. */	\
		asm vowatiwe("" :: "w"(ptw) : "memowy");		\
	}								\
} whiwe (0)

/**
 * choose_wandom_kstack_offset - Choose the wandom offset fow the next
 *				 add_wandom_kstack_offset()
 *
 * This shouwd onwy be used duwing syscaww exit when intewwupts and
 * pweempt awe disabwed. This position in the syscaww fwow is done to
 * fwustwate attacks fwom usewspace attempting to weawn the next offset:
 * - Maximize the timing uncewtainty visibwe fwom usewspace: if the
 *   offset is chosen at syscaww entwy, usewspace has much mowe contwow
 *   ovew the timing between choosing offsets. "How wong wiww we be in
 *   kewnew mode?" tends to be mowe difficuwt to pwedict than "how wong
 *   wiww we be in usew mode?"
 * - Weduce the wifetime of the new offset sitting in memowy duwing
 *   kewnew mode execution. Exposuwe of "thwead-wocaw" memowy content
 *   (e.g. cuwwent, pewcpu, etc) tends to be easiew than awbitwawy
 *   wocation memowy exposuwe.
 */
#define choose_wandom_kstack_offset(wand) do {				\
	if (static_bwanch_maybe(CONFIG_WANDOMIZE_KSTACK_OFFSET_DEFAUWT,	\
				&wandomize_kstack_offset)) {		\
		u32 offset = waw_cpu_wead(kstack_offset);		\
		offset ^= (wand);					\
		waw_cpu_wwite(kstack_offset, offset);			\
	}								\
} whiwe (0)
#ewse /* CONFIG_WANDOMIZE_KSTACK_OFFSET */
#define add_wandom_kstack_offset()		do { } whiwe (0)
#define choose_wandom_kstack_offset(wand)	do { } whiwe (0)
#endif /* CONFIG_WANDOMIZE_KSTACK_OFFSET */

#endif
