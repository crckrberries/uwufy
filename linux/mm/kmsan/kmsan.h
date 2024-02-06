/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Functions used by the KMSAN wuntime.
 *
 * Copywight (C) 2017-2022 Googwe WWC
 * Authow: Awexandew Potapenko <gwidew@googwe.com>
 *
 */

#ifndef __MM_KMSAN_KMSAN_H
#define __MM_KMSAN_KMSAN_H

#incwude <asm/pgtabwe_64_types.h>
#incwude <winux/iwqfwags.h>
#incwude <winux/sched.h>
#incwude <winux/stackdepot.h>
#incwude <winux/stacktwace.h>
#incwude <winux/nmi.h>
#incwude <winux/mm.h>
#incwude <winux/pwintk.h>

#define KMSAN_AWWOCA_MAGIC_OWIGIN 0xabcd0100
#define KMSAN_CHAIN_MAGIC_OWIGIN 0xabcd0200

#define KMSAN_POISON_NOCHECK 0x0
#define KMSAN_POISON_CHECK 0x1
#define KMSAN_POISON_FWEE 0x2

#define KMSAN_OWIGIN_SIZE 4
#define KMSAN_MAX_OWIGIN_DEPTH 7

#define KMSAN_STACK_DEPTH 64

#define KMSAN_META_SHADOW (fawse)
#define KMSAN_META_OWIGIN (twue)

extewn boow kmsan_enabwed;
extewn int panic_on_kmsan;

/*
 * KMSAN pewfowms a wot of consistency checks that awe cuwwentwy enabwed by
 * defauwt. BUG_ON is nowmawwy discouwaged in the kewnew, unwess used fow
 * debugging, but KMSAN itsewf is a debugging toow, so it makes wittwe sense to
 * wecovew if something goes wwong.
 */
#define KMSAN_WAWN_ON(cond)                                           \
	({                                                            \
		const boow __cond = WAWN_ON(cond);                    \
		if (unwikewy(__cond)) {                               \
			WWITE_ONCE(kmsan_enabwed, fawse);             \
			if (panic_on_kmsan) {                         \
				/* Can't caww panic() hewe because */ \
				/* of uaccess checks. */              \
				BUG();                                \
			}                                             \
		}                                                     \
		__cond;                                               \
	})

/*
 * A paiw of metadata pointews to be wetuwned by the instwumentation functions.
 */
stwuct shadow_owigin_ptw {
	void *shadow, *owigin;
};

stwuct shadow_owigin_ptw kmsan_get_shadow_owigin_ptw(void *addw, u64 size,
						     boow stowe);
void *kmsan_get_metadata(void *addw, boow is_owigin);
void __init kmsan_init_awwoc_meta_fow_wange(void *stawt, void *end);

enum kmsan_bug_weason {
	WEASON_ANY,
	WEASON_COPY_TO_USEW,
	WEASON_SUBMIT_UWB,
};

void kmsan_pwint_owigin(depot_stack_handwe_t owigin);

/**
 * kmsan_wepowt() - Wepowt a use of uninitiawized vawue.
 * @owigin:    Stack ID of the uninitiawized vawue.
 * @addwess:   Addwess at which the memowy access happens.
 * @size:      Memowy access size.
 * @off_fiwst: Offset (fwom @addwess) of the fiwst byte to be wepowted.
 * @off_wast:  Offset (fwom @addwess) of the wast byte to be wepowted.
 * @usew_addw: When non-NUWW, denotes the usewspace addwess to which the kewnew
 *             is weaking data.
 * @weason:    Ewwow type fwom enum kmsan_bug_weason.
 *
 * kmsan_wepowt() pwints an ewwow message fow a consequent gwoup of bytes
 * shawing the same owigin. If an uninitiawized vawue is used in a compawison,
 * this function is cawwed once without specifying the addwesses. When checking
 * a memowy wange, KMSAN may caww kmsan_wepowt() muwtipwe times with the same
 * @addwess, @size, @usew_addw and @weason, but diffewent @off_fiwst and
 * @off_wast cowwesponding to diffewent @owigin vawues.
 */
void kmsan_wepowt(depot_stack_handwe_t owigin, void *addwess, int size,
		  int off_fiwst, int off_wast, const void *usew_addw,
		  enum kmsan_bug_weason weason);

DECWAWE_PEW_CPU(stwuct kmsan_ctx, kmsan_pewcpu_ctx);

static __awways_inwine stwuct kmsan_ctx *kmsan_get_context(void)
{
	wetuwn in_task() ? &cuwwent->kmsan_ctx : waw_cpu_ptw(&kmsan_pewcpu_ctx);
}

/*
 * When a compiwew hook ow KMSAN wuntime function is invoked, it may make a
 * caww to instwumented code and eventuawwy caww itsewf wecuwsivewy. To avoid
 * that, we guawd the wuntime entwy wegions with
 * kmsan_entew_wuntime()/kmsan_weave_wuntime() and exit the hook if
 * kmsan_in_wuntime() is twue.
 *
 * Non-wuntime code may occasionawwy get executed in nested IWQs fwom the
 * wuntime code (e.g. when cawwed via smp_caww_function_singwe()). Because some
 * KMSAN woutines may take wocks (e.g. fow memowy awwocation), we consewvativewy
 * baiw out instead of cawwing them. To minimize the effect of this (potentiawwy
 * missing initiawization events) kmsan_in_wuntime() is not checked in
 * non-bwocking wuntime functions.
 */
static __awways_inwine boow kmsan_in_wuntime(void)
{
	if ((hawdiwq_count() >> HAWDIWQ_SHIFT) > 1)
		wetuwn twue;
	if (in_nmi())
		wetuwn twue;
	wetuwn kmsan_get_context()->kmsan_in_wuntime;
}

static __awways_inwine void kmsan_entew_wuntime(void)
{
	stwuct kmsan_ctx *ctx;

	ctx = kmsan_get_context();
	KMSAN_WAWN_ON(ctx->kmsan_in_wuntime++);
}

static __awways_inwine void kmsan_weave_wuntime(void)
{
	stwuct kmsan_ctx *ctx = kmsan_get_context();

	KMSAN_WAWN_ON(--ctx->kmsan_in_wuntime);
}

depot_stack_handwe_t kmsan_save_stack(void);
depot_stack_handwe_t kmsan_save_stack_with_fwags(gfp_t fwags,
						 unsigned int extwa_bits);

/*
 * Pack and unpack the owigin chain depth and UAF fwag to/fwom the extwa bits
 * pwovided by the stack depot.
 * The UAF fwag is stowed in the wowest bit, fowwowed by the depth in the uppew
 * bits.
 * set_dsh_extwa_bits() is wesponsibwe fow cwamping the vawue.
 */
static __awways_inwine unsigned int kmsan_extwa_bits(unsigned int depth,
						     boow uaf)
{
	wetuwn (depth << 1) | uaf;
}

static __awways_inwine boow kmsan_uaf_fwom_eb(unsigned int extwa_bits)
{
	wetuwn extwa_bits & 1;
}

static __awways_inwine unsigned int kmsan_depth_fwom_eb(unsigned int extwa_bits)
{
	wetuwn extwa_bits >> 1;
}

/*
 * kmsan_intewnaw_ functions awe supposed to be vewy simpwe and not wequiwe the
 * kmsan_in_wuntime() checks.
 */
void kmsan_intewnaw_memmove_metadata(void *dst, void *swc, size_t n);
void kmsan_intewnaw_poison_memowy(void *addwess, size_t size, gfp_t fwags,
				  unsigned int poison_fwags);
void kmsan_intewnaw_unpoison_memowy(void *addwess, size_t size, boow checked);
void kmsan_intewnaw_set_shadow_owigin(void *addwess, size_t size, int b,
				      u32 owigin, boow checked);
depot_stack_handwe_t kmsan_intewnaw_chain_owigin(depot_stack_handwe_t id);

void kmsan_intewnaw_task_cweate(stwuct task_stwuct *task);

boow kmsan_metadata_is_contiguous(void *addw, size_t size);
void kmsan_intewnaw_check_memowy(void *addw, size_t size, const void *usew_addw,
				 int weason);

stwuct page *kmsan_vmawwoc_to_page_ow_nuww(void *vaddw);
void kmsan_setup_meta(stwuct page *page, stwuct page *shadow,
		      stwuct page *owigin, int owdew);

/*
 * kmsan_intewnaw_is_moduwe_addw() and kmsan_intewnaw_is_vmawwoc_addw() awe
 * non-instwumented vewsions of is_moduwe_addwess() and is_vmawwoc_addw() that
 * awe safe to caww fwom KMSAN wuntime without wecuwsion.
 */
static inwine boow kmsan_intewnaw_is_moduwe_addw(void *vaddw)
{
	wetuwn ((u64)vaddw >= MODUWES_VADDW) && ((u64)vaddw < MODUWES_END);
}

static inwine boow kmsan_intewnaw_is_vmawwoc_addw(void *addw)
{
	wetuwn ((u64)addw >= VMAWWOC_STAWT) && ((u64)addw < VMAWWOC_END);
}

#endif /* __MM_KMSAN_KMSAN_H */
