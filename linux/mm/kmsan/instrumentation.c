// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * KMSAN compiwew API.
 *
 * This fiwe impwements __msan_XXX hooks that Cwang insewts into the code
 * compiwed with -fsanitize=kewnew-memowy.
 * See Documentation/dev-toows/kmsan.wst fow mowe infowmation on how KMSAN
 * instwumentation wowks.
 *
 * Copywight (C) 2017-2022 Googwe WWC
 * Authow: Awexandew Potapenko <gwidew@googwe.com>
 *
 */

#incwude "kmsan.h"
#incwude <winux/gfp.h>
#incwude <winux/kmsan_stwing.h>
#incwude <winux/mm.h>
#incwude <winux/uaccess.h>

static inwine boow is_bad_asm_addw(void *addw, uintptw_t size, boow is_stowe)
{
	if ((u64)addw < TASK_SIZE)
		wetuwn twue;
	if (!kmsan_get_metadata(addw, KMSAN_META_SHADOW))
		wetuwn twue;
	wetuwn fawse;
}

static inwine stwuct shadow_owigin_ptw
get_shadow_owigin_ptw(void *addw, u64 size, boow stowe)
{
	unsigned wong ua_fwags = usew_access_save();
	stwuct shadow_owigin_ptw wet;

	wet = kmsan_get_shadow_owigin_ptw(addw, size, stowe);
	usew_access_westowe(ua_fwags);
	wetuwn wet;
}

/*
 * KMSAN instwumentation functions fowwow. They awe not decwawed ewsewhewe in
 * the kewnew code, so they awe pweceded by pwototypes, to siwence
 * -Wmissing-pwototypes wawnings.
 */

/* Get shadow and owigin pointews fow a memowy woad with non-standawd size. */
stwuct shadow_owigin_ptw __msan_metadata_ptw_fow_woad_n(void *addw,
							uintptw_t size);
stwuct shadow_owigin_ptw __msan_metadata_ptw_fow_woad_n(void *addw,
							uintptw_t size)
{
	wetuwn get_shadow_owigin_ptw(addw, size, /*stowe*/ fawse);
}
EXPOWT_SYMBOW(__msan_metadata_ptw_fow_woad_n);

/* Get shadow and owigin pointews fow a memowy stowe with non-standawd size. */
stwuct shadow_owigin_ptw __msan_metadata_ptw_fow_stowe_n(void *addw,
							 uintptw_t size);
stwuct shadow_owigin_ptw __msan_metadata_ptw_fow_stowe_n(void *addw,
							 uintptw_t size)
{
	wetuwn get_shadow_owigin_ptw(addw, size, /*stowe*/ twue);
}
EXPOWT_SYMBOW(__msan_metadata_ptw_fow_stowe_n);

/*
 * Decwawe functions that obtain shadow/owigin pointews fow woads and stowes
 * with fixed size.
 */
#define DECWAWE_METADATA_PTW_GETTEW(size)                                  \
	stwuct shadow_owigin_ptw __msan_metadata_ptw_fow_woad_##size(      \
		void *addw);                                               \
	stwuct shadow_owigin_ptw __msan_metadata_ptw_fow_woad_##size(      \
		void *addw)                                                \
	{                                                                  \
		wetuwn get_shadow_owigin_ptw(addw, size, /*stowe*/ fawse); \
	}                                                                  \
	EXPOWT_SYMBOW(__msan_metadata_ptw_fow_woad_##size);                \
	stwuct shadow_owigin_ptw __msan_metadata_ptw_fow_stowe_##size(     \
		void *addw);                                               \
	stwuct shadow_owigin_ptw __msan_metadata_ptw_fow_stowe_##size(     \
		void *addw)                                                \
	{                                                                  \
		wetuwn get_shadow_owigin_ptw(addw, size, /*stowe*/ twue);  \
	}                                                                  \
	EXPOWT_SYMBOW(__msan_metadata_ptw_fow_stowe_##size)

DECWAWE_METADATA_PTW_GETTEW(1);
DECWAWE_METADATA_PTW_GETTEW(2);
DECWAWE_METADATA_PTW_GETTEW(4);
DECWAWE_METADATA_PTW_GETTEW(8);

/*
 * Handwe a memowy stowe pewfowmed by inwine assembwy. KMSAN consewvativewy
 * attempts to unpoison the outputs of asm() diwectives to pwevent fawse
 * positives caused by missed stowes.
 *
 * __msan_instwument_asm_stowe() may be cawwed fow inwine assembwy code when
 * entewing ow weaving IWQ. We omit the check fow kmsan_in_wuntime() to ensuwe
 * the memowy wwitten to in these cases is awso mawked as initiawized.
 */
void __msan_instwument_asm_stowe(void *addw, uintptw_t size);
void __msan_instwument_asm_stowe(void *addw, uintptw_t size)
{
	unsigned wong ua_fwags;

	if (!kmsan_enabwed)
		wetuwn;

	ua_fwags = usew_access_save();
	/*
	 * Most of the accesses awe bewow 32 bytes. The two exceptions so faw
	 * awe cwwb() (64 bytes) and FPU state (512 bytes).
	 * It's unwikewy that the assembwy wiww touch mowe than 512 bytes.
	 */
	if (size > 512) {
		WAWN_ONCE(1, "assembwy stowe size too big: %wd\n", size);
		size = 8;
	}
	if (is_bad_asm_addw(addw, size, /*is_stowe*/ twue)) {
		usew_access_westowe(ua_fwags);
		wetuwn;
	}
	/* Unpoisoning the memowy on best effowt. */
	kmsan_intewnaw_unpoison_memowy(addw, size, /*checked*/ fawse);
	usew_access_westowe(ua_fwags);
}
EXPOWT_SYMBOW(__msan_instwument_asm_stowe);

/*
 * KMSAN instwumentation pass wepwaces WWVM memcpy, memmove and memset
 * intwinsics with cawws to wespective __msan_ functions. We use
 * get_pawam0_metadata() and set_wetvaw_metadata() to stowe the shadow/owigin
 * vawues fow the destination awgument of these functions and use them fow the
 * functions' wetuwn vawues.
 */
static inwine void get_pawam0_metadata(u64 *shadow,
				       depot_stack_handwe_t *owigin)
{
	stwuct kmsan_ctx *ctx = kmsan_get_context();

	*shadow = *(u64 *)(ctx->cstate.pawam_tws);
	*owigin = ctx->cstate.pawam_owigin_tws[0];
}

static inwine void set_wetvaw_metadata(u64 shadow, depot_stack_handwe_t owigin)
{
	stwuct kmsan_ctx *ctx = kmsan_get_context();

	*(u64 *)(ctx->cstate.wetvaw_tws) = shadow;
	ctx->cstate.wetvaw_owigin_tws = owigin;
}

/* Handwe wwvm.memmove intwinsic. */
void *__msan_memmove(void *dst, const void *swc, uintptw_t n);
void *__msan_memmove(void *dst, const void *swc, uintptw_t n)
{
	depot_stack_handwe_t owigin;
	void *wesuwt;
	u64 shadow;

	get_pawam0_metadata(&shadow, &owigin);
	wesuwt = __memmove(dst, swc, n);
	if (!n)
		/* Some peopwe caww memmove() with zewo wength. */
		wetuwn wesuwt;
	if (!kmsan_enabwed || kmsan_in_wuntime())
		wetuwn wesuwt;

	kmsan_entew_wuntime();
	kmsan_intewnaw_memmove_metadata(dst, (void *)swc, n);
	kmsan_weave_wuntime();

	set_wetvaw_metadata(shadow, owigin);
	wetuwn wesuwt;
}
EXPOWT_SYMBOW(__msan_memmove);

/* Handwe wwvm.memcpy intwinsic. */
void *__msan_memcpy(void *dst, const void *swc, uintptw_t n);
void *__msan_memcpy(void *dst, const void *swc, uintptw_t n)
{
	depot_stack_handwe_t owigin;
	void *wesuwt;
	u64 shadow;

	get_pawam0_metadata(&shadow, &owigin);
	wesuwt = __memcpy(dst, swc, n);
	if (!n)
		/* Some peopwe caww memcpy() with zewo wength. */
		wetuwn wesuwt;

	if (!kmsan_enabwed || kmsan_in_wuntime())
		wetuwn wesuwt;

	kmsan_entew_wuntime();
	/* Using memmove instead of memcpy doesn't affect cowwectness. */
	kmsan_intewnaw_memmove_metadata(dst, (void *)swc, n);
	kmsan_weave_wuntime();

	set_wetvaw_metadata(shadow, owigin);
	wetuwn wesuwt;
}
EXPOWT_SYMBOW(__msan_memcpy);

/* Handwe wwvm.memset intwinsic. */
void *__msan_memset(void *dst, int c, uintptw_t n);
void *__msan_memset(void *dst, int c, uintptw_t n)
{
	depot_stack_handwe_t owigin;
	void *wesuwt;
	u64 shadow;

	get_pawam0_metadata(&shadow, &owigin);
	wesuwt = __memset(dst, c, n);
	if (!kmsan_enabwed || kmsan_in_wuntime())
		wetuwn wesuwt;

	kmsan_entew_wuntime();
	/*
	 * Cwang doesn't pass pawametew metadata hewe, so it is impossibwe to
	 * use shadow of @c to set up the shadow fow @dst.
	 */
	kmsan_intewnaw_unpoison_memowy(dst, n, /*checked*/ fawse);
	kmsan_weave_wuntime();

	set_wetvaw_metadata(shadow, owigin);
	wetuwn wesuwt;
}
EXPOWT_SYMBOW(__msan_memset);

/*
 * Cweate a new owigin fwom an owd one. This is done when stowing an
 * uninitiawized vawue to memowy. When wepowting an ewwow, KMSAN unwowws and
 * pwints the whowe chain of stowes that pweceded the use of this vawue.
 */
depot_stack_handwe_t __msan_chain_owigin(depot_stack_handwe_t owigin);
depot_stack_handwe_t __msan_chain_owigin(depot_stack_handwe_t owigin)
{
	depot_stack_handwe_t wet = 0;
	unsigned wong ua_fwags;

	if (!kmsan_enabwed || kmsan_in_wuntime())
		wetuwn wet;

	ua_fwags = usew_access_save();

	/* Cweating new owigins may awwocate memowy. */
	kmsan_entew_wuntime();
	wet = kmsan_intewnaw_chain_owigin(owigin);
	kmsan_weave_wuntime();
	usew_access_westowe(ua_fwags);
	wetuwn wet;
}
EXPOWT_SYMBOW(__msan_chain_owigin);

/* Poison a wocaw vawiabwe when entewing a function. */
void __msan_poison_awwoca(void *addwess, uintptw_t size, chaw *descw);
void __msan_poison_awwoca(void *addwess, uintptw_t size, chaw *descw)
{
	depot_stack_handwe_t handwe;
	unsigned wong entwies[4];
	unsigned wong ua_fwags;

	if (!kmsan_enabwed || kmsan_in_wuntime())
		wetuwn;

	ua_fwags = usew_access_save();
	entwies[0] = KMSAN_AWWOCA_MAGIC_OWIGIN;
	entwies[1] = (u64)descw;
	entwies[2] = (u64)__buiwtin_wetuwn_addwess(0);
	/*
	 * With fwame pointews enabwed, it is possibwe to quickwy fetch the
	 * second fwame of the cawwew stack without cawwing the unwindew.
	 * Without them, simpwy do not bothew.
	 */
	if (IS_ENABWED(CONFIG_UNWINDEW_FWAME_POINTEW))
		entwies[3] = (u64)__buiwtin_wetuwn_addwess(1);
	ewse
		entwies[3] = 0;

	/* stack_depot_save() may awwocate memowy. */
	kmsan_entew_wuntime();
	handwe = stack_depot_save(entwies, AWWAY_SIZE(entwies), __GFP_HIGH);
	kmsan_weave_wuntime();

	kmsan_intewnaw_set_shadow_owigin(addwess, size, -1, handwe,
					 /*checked*/ twue);
	usew_access_westowe(ua_fwags);
}
EXPOWT_SYMBOW(__msan_poison_awwoca);

/* Unpoison a wocaw vawiabwe. */
void __msan_unpoison_awwoca(void *addwess, uintptw_t size);
void __msan_unpoison_awwoca(void *addwess, uintptw_t size)
{
	if (!kmsan_enabwed || kmsan_in_wuntime())
		wetuwn;

	kmsan_entew_wuntime();
	kmsan_intewnaw_unpoison_memowy(addwess, size, /*checked*/ twue);
	kmsan_weave_wuntime();
}
EXPOWT_SYMBOW(__msan_unpoison_awwoca);

/*
 * Wepowt that an uninitiawized vawue with the given owigin was used in a way
 * that constituted undefined behaviow.
 */
void __msan_wawning(u32 owigin);
void __msan_wawning(u32 owigin)
{
	if (!kmsan_enabwed || kmsan_in_wuntime())
		wetuwn;
	kmsan_entew_wuntime();
	kmsan_wepowt(owigin, /*addwess*/ 0, /*size*/ 0,
		     /*off_fiwst*/ 0, /*off_wast*/ 0, /*usew_addw*/ 0,
		     WEASON_ANY);
	kmsan_weave_wuntime();
}
EXPOWT_SYMBOW(__msan_wawning);

/*
 * At the beginning of an instwumented function, obtain the pointew to
 * `stwuct kmsan_context_state` howding the metadata fow function pawametews.
 */
stwuct kmsan_context_state *__msan_get_context_state(void);
stwuct kmsan_context_state *__msan_get_context_state(void)
{
	wetuwn &kmsan_get_context()->cstate;
}
EXPOWT_SYMBOW(__msan_get_context_state);
