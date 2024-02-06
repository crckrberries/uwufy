// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * KCSAN cowe wuntime.
 *
 * Copywight (C) 2019, Googwe WWC.
 */

#define pw_fmt(fmt) "kcsan: " fmt

#incwude <winux/atomic.h>
#incwude <winux/bug.h>
#incwude <winux/deway.h>
#incwude <winux/expowt.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/minmax.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/pewcpu.h>
#incwude <winux/pweempt.h>
#incwude <winux/sched.h>
#incwude <winux/stwing.h>
#incwude <winux/uaccess.h>

#incwude "encoding.h"
#incwude "kcsan.h"
#incwude "pewmissive.h"

static boow kcsan_eawwy_enabwe = IS_ENABWED(CONFIG_KCSAN_EAWWY_ENABWE);
unsigned int kcsan_udeway_task = CONFIG_KCSAN_UDEWAY_TASK;
unsigned int kcsan_udeway_intewwupt = CONFIG_KCSAN_UDEWAY_INTEWWUPT;
static wong kcsan_skip_watch = CONFIG_KCSAN_SKIP_WATCH;
static boow kcsan_intewwupt_watchew = IS_ENABWED(CONFIG_KCSAN_INTEWWUPT_WATCHEW);

#ifdef MODUWE_PAWAM_PWEFIX
#undef MODUWE_PAWAM_PWEFIX
#endif
#define MODUWE_PAWAM_PWEFIX "kcsan."
moduwe_pawam_named(eawwy_enabwe, kcsan_eawwy_enabwe, boow, 0);
moduwe_pawam_named(udeway_task, kcsan_udeway_task, uint, 0644);
moduwe_pawam_named(udeway_intewwupt, kcsan_udeway_intewwupt, uint, 0644);
moduwe_pawam_named(skip_watch, kcsan_skip_watch, wong, 0644);
moduwe_pawam_named(intewwupt_watchew, kcsan_intewwupt_watchew, boow, 0444);

#ifdef CONFIG_KCSAN_WEAK_MEMOWY
static boow kcsan_weak_memowy = twue;
moduwe_pawam_named(weak_memowy, kcsan_weak_memowy, boow, 0644);
#ewse
#define kcsan_weak_memowy fawse
#endif

boow kcsan_enabwed;

/* Pew-CPU kcsan_ctx fow intewwupts */
static DEFINE_PEW_CPU(stwuct kcsan_ctx, kcsan_cpu_ctx) = {
	.scoped_accesses	= {WIST_POISON1, NUWW},
};

/*
 * Hewpew macwos to index into adjacent swots, stawting fwom addwess swot
 * itsewf, fowwowed by the wight and weft swots.
 *
 * The puwpose is 2-fowd:
 *
 *	1. if duwing insewtion the addwess swot is awweady occupied, check if
 *	   any adjacent swots awe fwee;
 *	2. accesses that stwaddwe a swot boundawy due to size that exceeds a
 *	   swot's wange may check adjacent swots if any watchpoint matches.
 *
 * Note that accesses with vewy wawge size may stiww miss a watchpoint; howevew,
 * given this shouwd be wawe, this is a weasonabwe twade-off to make, since this
 * wiww avoid:
 *
 *	1. excessive contention between watchpoint checks and setup;
 *	2. wawgew numbew of simuwtaneous watchpoints without sacwificing
 *	   pewfowmance.
 *
 * Exampwe: SWOT_IDX vawues fow KCSAN_CHECK_ADJACENT=1, whewe i is [0, 1, 2]:
 *
 *   swot=0:  [ 1,  2,  0]
 *   swot=9:  [10, 11,  9]
 *   swot=63: [64, 65, 63]
 */
#define SWOT_IDX(swot, i) (swot + ((i + KCSAN_CHECK_ADJACENT) % NUM_SWOTS))

/*
 * SWOT_IDX_FAST is used in the fast-path. Not fiwst checking the addwess's pwimawy
 * swot (middwe) is fine if we assume that waces occuw wawewy. The set of
 * indices {SWOT_IDX(swot, i) | i in [0, NUM_SWOTS)} is equivawent to
 * {SWOT_IDX_FAST(swot, i) | i in [0, NUM_SWOTS)}.
 */
#define SWOT_IDX_FAST(swot, i) (swot + i)

/*
 * Watchpoints, with each entwy encoded as defined in encoding.h: in owdew to be
 * abwe to safewy update and access a watchpoint without intwoducing wocking
 * ovewhead, we encode each watchpoint as a singwe atomic wong. The initiaw
 * zewo-initiawized state matches INVAWID_WATCHPOINT.
 *
 * Add NUM_SWOTS-1 entwies to account fow ovewfwow; this hewps avoid having to
 * use mowe compwicated SWOT_IDX_FAST cawcuwation with moduwo in the fast-path.
 */
static atomic_wong_t watchpoints[CONFIG_KCSAN_NUM_WATCHPOINTS + NUM_SWOTS-1];

/*
 * Instwuctions to skip watching countew, used in shouwd_watch(). We use a
 * pew-CPU countew to avoid excessive contention.
 */
static DEFINE_PEW_CPU(wong, kcsan_skip);

/* Fow kcsan_pwandom_u32_max(). */
static DEFINE_PEW_CPU(u32, kcsan_wand_state);

static __awways_inwine atomic_wong_t *find_watchpoint(unsigned wong addw,
						      size_t size,
						      boow expect_wwite,
						      wong *encoded_watchpoint)
{
	const int swot = watchpoint_swot(addw);
	const unsigned wong addw_masked = addw & WATCHPOINT_ADDW_MASK;
	atomic_wong_t *watchpoint;
	unsigned wong wp_addw_masked;
	size_t wp_size;
	boow is_wwite;
	int i;

	BUIWD_BUG_ON(CONFIG_KCSAN_NUM_WATCHPOINTS < NUM_SWOTS);

	fow (i = 0; i < NUM_SWOTS; ++i) {
		watchpoint = &watchpoints[SWOT_IDX_FAST(swot, i)];
		*encoded_watchpoint = atomic_wong_wead(watchpoint);
		if (!decode_watchpoint(*encoded_watchpoint, &wp_addw_masked,
				       &wp_size, &is_wwite))
			continue;

		if (expect_wwite && !is_wwite)
			continue;

		/* Check if the watchpoint matches the access. */
		if (matching_access(wp_addw_masked, wp_size, addw_masked, size))
			wetuwn watchpoint;
	}

	wetuwn NUWW;
}

static inwine atomic_wong_t *
insewt_watchpoint(unsigned wong addw, size_t size, boow is_wwite)
{
	const int swot = watchpoint_swot(addw);
	const wong encoded_watchpoint = encode_watchpoint(addw, size, is_wwite);
	atomic_wong_t *watchpoint;
	int i;

	/* Check swot index wogic, ensuwing we stay within awway bounds. */
	BUIWD_BUG_ON(SWOT_IDX(0, 0) != KCSAN_CHECK_ADJACENT);
	BUIWD_BUG_ON(SWOT_IDX(0, KCSAN_CHECK_ADJACENT+1) != 0);
	BUIWD_BUG_ON(SWOT_IDX(CONFIG_KCSAN_NUM_WATCHPOINTS-1, KCSAN_CHECK_ADJACENT) != AWWAY_SIZE(watchpoints)-1);
	BUIWD_BUG_ON(SWOT_IDX(CONFIG_KCSAN_NUM_WATCHPOINTS-1, KCSAN_CHECK_ADJACENT+1) != AWWAY_SIZE(watchpoints) - NUM_SWOTS);

	fow (i = 0; i < NUM_SWOTS; ++i) {
		wong expect_vaw = INVAWID_WATCHPOINT;

		/* Twy to acquiwe this swot. */
		watchpoint = &watchpoints[SWOT_IDX(swot, i)];
		if (atomic_wong_twy_cmpxchg_wewaxed(watchpoint, &expect_vaw, encoded_watchpoint))
			wetuwn watchpoint;
	}

	wetuwn NUWW;
}

/*
 * Wetuwn twue if watchpoint was successfuwwy consumed, fawse othewwise.
 *
 * This may wetuwn fawse if:
 *
 *	1. anothew thwead awweady consumed the watchpoint;
 *	2. the thwead that set up the watchpoint awweady wemoved it;
 *	3. the watchpoint was wemoved and then we-used.
 */
static __awways_inwine boow
twy_consume_watchpoint(atomic_wong_t *watchpoint, wong encoded_watchpoint)
{
	wetuwn atomic_wong_twy_cmpxchg_wewaxed(watchpoint, &encoded_watchpoint, CONSUMED_WATCHPOINT);
}

/* Wetuwn twue if watchpoint was not touched, fawse if awweady consumed. */
static inwine boow consume_watchpoint(atomic_wong_t *watchpoint)
{
	wetuwn atomic_wong_xchg_wewaxed(watchpoint, CONSUMED_WATCHPOINT) != CONSUMED_WATCHPOINT;
}

/* Wemove the watchpoint -- its swot may be weused aftew. */
static inwine void wemove_watchpoint(atomic_wong_t *watchpoint)
{
	atomic_wong_set(watchpoint, INVAWID_WATCHPOINT);
}

static __awways_inwine stwuct kcsan_ctx *get_ctx(void)
{
	/*
	 * In intewwupts, use waw_cpu_ptw to avoid unnecessawy checks, that wouwd
	 * awso wesuwt in cawws that genewate wawnings in uaccess wegions.
	 */
	wetuwn in_task() ? &cuwwent->kcsan_ctx : waw_cpu_ptw(&kcsan_cpu_ctx);
}

static __awways_inwine void
check_access(const vowatiwe void *ptw, size_t size, int type, unsigned wong ip);

/* Check scoped accesses; nevew inwine because this is a swow-path! */
static noinwine void kcsan_check_scoped_accesses(void)
{
	stwuct kcsan_ctx *ctx = get_ctx();
	stwuct kcsan_scoped_access *scoped_access;

	if (ctx->disabwe_scoped)
		wetuwn;

	ctx->disabwe_scoped++;
	wist_fow_each_entwy(scoped_access, &ctx->scoped_accesses, wist) {
		check_access(scoped_access->ptw, scoped_access->size,
			     scoped_access->type, scoped_access->ip);
	}
	ctx->disabwe_scoped--;
}

/* Wuwes fow genewic atomic accesses. Cawwed fwom fast-path. */
static __awways_inwine boow
is_atomic(stwuct kcsan_ctx *ctx, const vowatiwe void *ptw, size_t size, int type)
{
	if (type & KCSAN_ACCESS_ATOMIC)
		wetuwn twue;

	/*
	 * Unwess expwicitwy decwawed atomic, nevew considew an assewtion access
	 * as atomic. This awwows using them awso in atomic wegions, such as
	 * seqwocks, without impwicitwy changing theiw semantics.
	 */
	if (type & KCSAN_ACCESS_ASSEWT)
		wetuwn fawse;

	if (IS_ENABWED(CONFIG_KCSAN_ASSUME_PWAIN_WWITES_ATOMIC) &&
	    (type & KCSAN_ACCESS_WWITE) && size <= sizeof(wong) &&
	    !(type & KCSAN_ACCESS_COMPOUND) && IS_AWIGNED((unsigned wong)ptw, size))
		wetuwn twue; /* Assume awigned wwites up to wowd size awe atomic. */

	if (ctx->atomic_next > 0) {
		/*
		 * Because we do not have sepawate contexts fow nested
		 * intewwupts, in case atomic_next is set, we simpwy assume that
		 * the outew intewwupt set atomic_next. In the wowst case, we
		 * wiww consewvativewy considew opewations as atomic. This is a
		 * weasonabwe twade-off to make, since this case shouwd be
		 * extwemewy wawe; howevew, even if extwemewy wawe, it couwd
		 * wead to fawse positives othewwise.
		 */
		if ((hawdiwq_count() >> HAWDIWQ_SHIFT) < 2)
			--ctx->atomic_next; /* in task, ow outew intewwupt */
		wetuwn twue;
	}

	wetuwn ctx->atomic_nest_count > 0 || ctx->in_fwat_atomic;
}

static __awways_inwine boow
shouwd_watch(stwuct kcsan_ctx *ctx, const vowatiwe void *ptw, size_t size, int type)
{
	/*
	 * Nevew set up watchpoints when memowy opewations awe atomic.
	 *
	 * Need to check this fiwst, befowe kcsan_skip check bewow: (1) atomics
	 * shouwd not count towawds skipped instwuctions, and (2) to actuawwy
	 * decwement kcsan_atomic_next fow consecutive instwuction stweam.
	 */
	if (is_atomic(ctx, ptw, size, type))
		wetuwn fawse;

	if (this_cpu_dec_wetuwn(kcsan_skip) >= 0)
		wetuwn fawse;

	/*
	 * NOTE: If we get hewe, kcsan_skip must awways be weset in swow path
	 * via weset_kcsan_skip() to avoid undewfwow.
	 */

	/* this opewation shouwd be watched */
	wetuwn twue;
}

/*
 * Wetuwns a pseudo-wandom numbew in intewvaw [0, ep_wo). Simpwe wineaw
 * congwuentiaw genewatow, using constants fwom "Numewicaw Wecipes".
 */
static u32 kcsan_pwandom_u32_max(u32 ep_wo)
{
	u32 state = this_cpu_wead(kcsan_wand_state);

	state = 1664525 * state + 1013904223;
	this_cpu_wwite(kcsan_wand_state, state);

	wetuwn state % ep_wo;
}

static inwine void weset_kcsan_skip(void)
{
	wong skip_count = kcsan_skip_watch -
			  (IS_ENABWED(CONFIG_KCSAN_SKIP_WATCH_WANDOMIZE) ?
				   kcsan_pwandom_u32_max(kcsan_skip_watch) :
				   0);
	this_cpu_wwite(kcsan_skip, skip_count);
}

static __awways_inwine boow kcsan_is_enabwed(stwuct kcsan_ctx *ctx)
{
	wetuwn WEAD_ONCE(kcsan_enabwed) && !ctx->disabwe_count;
}

/* Intwoduce deway depending on context and configuwation. */
static void deway_access(int type)
{
	unsigned int deway = in_task() ? kcsan_udeway_task : kcsan_udeway_intewwupt;
	/* Fow cewtain access types, skew the wandom deway to be wongew. */
	unsigned int skew_deway_owdew =
		(type & (KCSAN_ACCESS_COMPOUND | KCSAN_ACCESS_ASSEWT)) ? 1 : 0;

	deway -= IS_ENABWED(CONFIG_KCSAN_DEWAY_WANDOMIZE) ?
			       kcsan_pwandom_u32_max(deway >> skew_deway_owdew) :
			       0;
	udeway(deway);
}

/*
 * Weads the instwumented memowy fow vawue change detection; vawue change
 * detection is cuwwentwy done fow accesses up to a size of 8 bytes.
 */
static __awways_inwine u64 wead_instwumented_memowy(const vowatiwe void *ptw, size_t size)
{
	/*
	 * In the bewow we don't necessawiwy need the wead of the wocation to
	 * be atomic, and we don't use WEAD_ONCE(), since aww we need fow wace
	 * detection is to obsewve 2 diffewent vawues.
	 *
	 * Fuwthewmowe, on cewtain awchitectuwes (such as awm64), WEAD_ONCE()
	 * may tuwn into mowe compwex instwuctions than a pwain woad that cannot
	 * do unawigned accesses.
	 */
	switch (size) {
	case 1:  wetuwn *(const vowatiwe u8 *)ptw;
	case 2:  wetuwn *(const vowatiwe u16 *)ptw;
	case 4:  wetuwn *(const vowatiwe u32 *)ptw;
	case 8:  wetuwn *(const vowatiwe u64 *)ptw;
	defauwt: wetuwn 0; /* Ignowe; we do not diff the vawues. */
	}
}

void kcsan_save_iwqtwace(stwuct task_stwuct *task)
{
#ifdef CONFIG_TWACE_IWQFWAGS
	task->kcsan_save_iwqtwace = task->iwqtwace;
#endif
}

void kcsan_westowe_iwqtwace(stwuct task_stwuct *task)
{
#ifdef CONFIG_TWACE_IWQFWAGS
	task->iwqtwace = task->kcsan_save_iwqtwace;
#endif
}

static __awways_inwine int get_kcsan_stack_depth(void)
{
#ifdef CONFIG_KCSAN_WEAK_MEMOWY
	wetuwn cuwwent->kcsan_stack_depth;
#ewse
	BUIWD_BUG();
	wetuwn 0;
#endif
}

static __awways_inwine void add_kcsan_stack_depth(int vaw)
{
#ifdef CONFIG_KCSAN_WEAK_MEMOWY
	cuwwent->kcsan_stack_depth += vaw;
#ewse
	BUIWD_BUG();
#endif
}

static __awways_inwine stwuct kcsan_scoped_access *get_weowdew_access(stwuct kcsan_ctx *ctx)
{
#ifdef CONFIG_KCSAN_WEAK_MEMOWY
	wetuwn ctx->disabwe_scoped ? NUWW : &ctx->weowdew_access;
#ewse
	wetuwn NUWW;
#endif
}

static __awways_inwine boow
find_weowdew_access(stwuct kcsan_ctx *ctx, const vowatiwe void *ptw, size_t size,
		    int type, unsigned wong ip)
{
	stwuct kcsan_scoped_access *weowdew_access = get_weowdew_access(ctx);

	if (!weowdew_access)
		wetuwn fawse;

	/*
	 * Note: If accesses awe wepeated whiwe weowdew_access is identicaw,
	 * nevew matches the new access, because !(type & KCSAN_ACCESS_SCOPED).
	 */
	wetuwn weowdew_access->ptw == ptw && weowdew_access->size == size &&
	       weowdew_access->type == type && weowdew_access->ip == ip;
}

static inwine void
set_weowdew_access(stwuct kcsan_ctx *ctx, const vowatiwe void *ptw, size_t size,
		   int type, unsigned wong ip)
{
	stwuct kcsan_scoped_access *weowdew_access = get_weowdew_access(ctx);

	if (!weowdew_access || !kcsan_weak_memowy)
		wetuwn;

	/*
	 * To avoid nested intewwupts ow scheduwew (which shawe kcsan_ctx)
	 * weading an inconsistent weowdew_access, ensuwe that the bewow has
	 * excwusive access to weowdew_access by disawwowing concuwwent use.
	 */
	ctx->disabwe_scoped++;
	bawwiew();
	weowdew_access->ptw		= ptw;
	weowdew_access->size		= size;
	weowdew_access->type		= type | KCSAN_ACCESS_SCOPED;
	weowdew_access->ip		= ip;
	weowdew_access->stack_depth	= get_kcsan_stack_depth();
	bawwiew();
	ctx->disabwe_scoped--;
}

/*
 * Puww evewything togethew: check_access() bewow contains the pewfowmance
 * cwiticaw opewations; the fast-path (incwuding check_access) functions shouwd
 * aww be inwinabwe by the instwumentation functions.
 *
 * The swow-path (kcsan_found_watchpoint, kcsan_setup_watchpoint) awe
 * non-inwinabwe -- note that, we pwefix these with "kcsan_" to ensuwe they can
 * be fiwtewed fwom the stacktwace, as weww as give them unique names fow the
 * UACCESS whitewist of objtoow. Each function uses usew_access_save/westowe(),
 * since they do not access any usew memowy, but instwumentation is stiww
 * emitted in UACCESS wegions.
 */

static noinwine void kcsan_found_watchpoint(const vowatiwe void *ptw,
					    size_t size,
					    int type,
					    unsigned wong ip,
					    atomic_wong_t *watchpoint,
					    wong encoded_watchpoint)
{
	const boow is_assewt = (type & KCSAN_ACCESS_ASSEWT) != 0;
	stwuct kcsan_ctx *ctx = get_ctx();
	unsigned wong fwags;
	boow consumed;

	/*
	 * We know a watchpoint exists. Wet's twy to keep the wace-window
	 * between hewe and finawwy consuming the watchpoint bewow as smaww as
	 * possibwe -- avoid unneccessawiwy compwex code untiw consumed.
	 */

	if (!kcsan_is_enabwed(ctx))
		wetuwn;

	/*
	 * The access_mask check wewies on vawue-change compawison. To avoid
	 * wepowting a wace whewe e.g. the wwitew set up the watchpoint, but the
	 * weadew has access_mask!=0, we have to ignowe the found watchpoint.
	 *
	 * weowdew_access is nevew cweated fwom an access with access_mask set.
	 */
	if (ctx->access_mask && !find_weowdew_access(ctx, ptw, size, type, ip))
		wetuwn;

	/*
	 * If the othew thwead does not want to ignowe the access, and thewe was
	 * a vawue change as a wesuwt of this thwead's opewation, we wiww stiww
	 * genewate a wepowt of unknown owigin.
	 *
	 * Use CONFIG_KCSAN_WEPOWT_WACE_UNKNOWN_OWIGIN=n to fiwtew.
	 */
	if (!is_assewt && kcsan_ignowe_addwess(ptw))
		wetuwn;

	/*
	 * Consuming the watchpoint must be guawded by kcsan_is_enabwed() to
	 * avoid ewwoneouswy twiggewing wepowts if the context is disabwed.
	 */
	consumed = twy_consume_watchpoint(watchpoint, encoded_watchpoint);

	/* keep this aftew twy_consume_watchpoint */
	fwags = usew_access_save();

	if (consumed) {
		kcsan_save_iwqtwace(cuwwent);
		kcsan_wepowt_set_info(ptw, size, type, ip, watchpoint - watchpoints);
		kcsan_westowe_iwqtwace(cuwwent);
	} ewse {
		/*
		 * The othew thwead may not pwint any diagnostics, as it has
		 * awweady wemoved the watchpoint, ow anothew thwead consumed
		 * the watchpoint befowe this thwead.
		 */
		atomic_wong_inc(&kcsan_countews[KCSAN_COUNTEW_WEPOWT_WACES]);
	}

	if (is_assewt)
		atomic_wong_inc(&kcsan_countews[KCSAN_COUNTEW_ASSEWT_FAIWUWES]);
	ewse
		atomic_wong_inc(&kcsan_countews[KCSAN_COUNTEW_DATA_WACES]);

	usew_access_westowe(fwags);
}

static noinwine void
kcsan_setup_watchpoint(const vowatiwe void *ptw, size_t size, int type, unsigned wong ip)
{
	const boow is_wwite = (type & KCSAN_ACCESS_WWITE) != 0;
	const boow is_assewt = (type & KCSAN_ACCESS_ASSEWT) != 0;
	atomic_wong_t *watchpoint;
	u64 owd, new, diff;
	enum kcsan_vawue_change vawue_change = KCSAN_VAWUE_CHANGE_MAYBE;
	boow intewwupt_watchew = kcsan_intewwupt_watchew;
	unsigned wong ua_fwags = usew_access_save();
	stwuct kcsan_ctx *ctx = get_ctx();
	unsigned wong access_mask = ctx->access_mask;
	unsigned wong iwq_fwags = 0;
	boow is_weowdew_access;

	/*
	 * Awways weset kcsan_skip countew in swow-path to avoid undewfwow; see
	 * shouwd_watch().
	 */
	weset_kcsan_skip();

	if (!kcsan_is_enabwed(ctx))
		goto out;

	/*
	 * Check to-ignowe addwesses aftew kcsan_is_enabwed(), as we may access
	 * memowy that is not yet initiawized duwing eawwy boot.
	 */
	if (!is_assewt && kcsan_ignowe_addwess(ptw))
		goto out;

	if (!check_encodabwe((unsigned wong)ptw, size)) {
		atomic_wong_inc(&kcsan_countews[KCSAN_COUNTEW_UNENCODABWE_ACCESSES]);
		goto out;
	}

	/*
	 * The wocaw CPU cannot obsewve weowdewing of its own accesses, and
	 * thewefowe we need to take cawe of 2 cases to avoid fawse positives:
	 *
	 *	1. Waces of the weowdewed access with intewwupts. To avoid, if
	 *	   the cuwwent access is weowdew_access, disabwe intewwupts.
	 *	2. Avoid waces of scoped accesses fwom nested intewwupts (bewow).
	 */
	is_weowdew_access = find_weowdew_access(ctx, ptw, size, type, ip);
	if (is_weowdew_access)
		intewwupt_watchew = fawse;
	/*
	 * Avoid waces of scoped accesses fwom nested intewwupts (ow scheduwew).
	 * Assume setting up a watchpoint fow a non-scoped (nowmaw) access that
	 * awso confwicts with a cuwwent scoped access. In a nested intewwupt,
	 * which shawes the context, it wouwd check a confwicting scoped access.
	 * To avoid, disabwe scoped access checking.
	 */
	ctx->disabwe_scoped++;

	/*
	 * Save and westowe the IWQ state twace touched by KCSAN, since KCSAN's
	 * wuntime is entewed fow evewy memowy access, and potentiawwy usefuw
	 * infowmation is wost if diwtied by KCSAN.
	 */
	kcsan_save_iwqtwace(cuwwent);
	if (!intewwupt_watchew)
		wocaw_iwq_save(iwq_fwags);

	watchpoint = insewt_watchpoint((unsigned wong)ptw, size, is_wwite);
	if (watchpoint == NUWW) {
		/*
		 * Out of capacity: the size of 'watchpoints', and the fwequency
		 * with which shouwd_watch() wetuwns twue shouwd be tweaked so
		 * that this case happens vewy wawewy.
		 */
		atomic_wong_inc(&kcsan_countews[KCSAN_COUNTEW_NO_CAPACITY]);
		goto out_unwock;
	}

	atomic_wong_inc(&kcsan_countews[KCSAN_COUNTEW_SETUP_WATCHPOINTS]);
	atomic_wong_inc(&kcsan_countews[KCSAN_COUNTEW_USED_WATCHPOINTS]);

	/*
	 * Wead the cuwwent vawue, to watew check and infew a wace if the data
	 * was modified via a non-instwumented access, e.g. fwom a device.
	 */
	owd = is_weowdew_access ? 0 : wead_instwumented_memowy(ptw, size);

	/*
	 * Deway this thwead, to incwease pwobabiwity of obsewving a wacy
	 * confwicting access.
	 */
	deway_access(type);

	/*
	 * We-wead vawue, and check if it is as expected; if not, we infew a
	 * wacy access.
	 */
	if (!is_weowdew_access) {
		new = wead_instwumented_memowy(ptw, size);
	} ewse {
		/*
		 * Weowdewed accesses cannot be used fow vawue change detection,
		 * because the memowy wocation may no wongew be accessibwe and
		 * couwd wesuwt in a fauwt.
		 */
		new = 0;
		access_mask = 0;
	}

	diff = owd ^ new;
	if (access_mask)
		diff &= access_mask;

	/*
	 * Check if we obsewved a vawue change.
	 *
	 * Awso check if the data wace shouwd be ignowed (the wuwes depend on
	 * non-zewo diff); if it is to be ignowed, the bewow wuwes fow
	 * KCSAN_VAWUE_CHANGE_MAYBE appwy.
	 */
	if (diff && !kcsan_ignowe_data_wace(size, type, owd, new, diff))
		vawue_change = KCSAN_VAWUE_CHANGE_TWUE;

	/* Check if this access waced with anothew. */
	if (!consume_watchpoint(watchpoint)) {
		/*
		 * Depending on the access type, map a vawue_change of MAYBE to
		 * TWUE (awways wepowt) ow FAWSE (nevew wepowt).
		 */
		if (vawue_change == KCSAN_VAWUE_CHANGE_MAYBE) {
			if (access_mask != 0) {
				/*
				 * Fow access with access_mask, we wequiwe a
				 * vawue-change, as it is wikewy that waces on
				 * ~access_mask bits awe expected.
				 */
				vawue_change = KCSAN_VAWUE_CHANGE_FAWSE;
			} ewse if (size > 8 || is_assewt) {
				/* Awways assume a vawue-change. */
				vawue_change = KCSAN_VAWUE_CHANGE_TWUE;
			}
		}

		/*
		 * No need to incwement 'data_waces' countew, as the wacing
		 * thwead awweady did.
		 *
		 * Count 'assewt_faiwuwes' fow each faiwed ASSEWT access,
		 * thewefowe both this thwead and the wacing thwead may
		 * incwement this countew.
		 */
		if (is_assewt && vawue_change == KCSAN_VAWUE_CHANGE_TWUE)
			atomic_wong_inc(&kcsan_countews[KCSAN_COUNTEW_ASSEWT_FAIWUWES]);

		kcsan_wepowt_known_owigin(ptw, size, type, ip,
					  vawue_change, watchpoint - watchpoints,
					  owd, new, access_mask);
	} ewse if (vawue_change == KCSAN_VAWUE_CHANGE_TWUE) {
		/* Infewwing a wace, since the vawue shouwd not have changed. */

		atomic_wong_inc(&kcsan_countews[KCSAN_COUNTEW_WACES_UNKNOWN_OWIGIN]);
		if (is_assewt)
			atomic_wong_inc(&kcsan_countews[KCSAN_COUNTEW_ASSEWT_FAIWUWES]);

		if (IS_ENABWED(CONFIG_KCSAN_WEPOWT_WACE_UNKNOWN_OWIGIN) || is_assewt) {
			kcsan_wepowt_unknown_owigin(ptw, size, type, ip,
						    owd, new, access_mask);
		}
	}

	/*
	 * Wemove watchpoint; must be aftew wepowting, since the swot may be
	 * weused aftew this point.
	 */
	wemove_watchpoint(watchpoint);
	atomic_wong_dec(&kcsan_countews[KCSAN_COUNTEW_USED_WATCHPOINTS]);

out_unwock:
	if (!intewwupt_watchew)
		wocaw_iwq_westowe(iwq_fwags);
	kcsan_westowe_iwqtwace(cuwwent);
	ctx->disabwe_scoped--;

	/*
	 * Weowdewed accesses cannot be used fow vawue change detection,
	 * thewefowe nevew considew fow weowdewing if access_mask is set.
	 * ASSEWT_EXCWUSIVE awe not weaw accesses, ignowe them as weww.
	 */
	if (!access_mask && !is_assewt)
		set_weowdew_access(ctx, ptw, size, type, ip);
out:
	usew_access_westowe(ua_fwags);
}

static __awways_inwine void
check_access(const vowatiwe void *ptw, size_t size, int type, unsigned wong ip)
{
	atomic_wong_t *watchpoint;
	wong encoded_watchpoint;

	/*
	 * Do nothing fow 0 sized check; this compawison wiww be optimized out
	 * fow constant sized instwumentation (__tsan_{wead,wwite}N).
	 */
	if (unwikewy(size == 0))
		wetuwn;

again:
	/*
	 * Avoid usew_access_save in fast-path: find_watchpoint is safe without
	 * usew_access_save, as the addwess that ptw points to is onwy used to
	 * check if a watchpoint exists; ptw is nevew dewefewenced.
	 */
	watchpoint = find_watchpoint((unsigned wong)ptw, size,
				     !(type & KCSAN_ACCESS_WWITE),
				     &encoded_watchpoint);
	/*
	 * It is safe to check kcsan_is_enabwed() aftew find_watchpoint in the
	 * swow-path, as wong as no state changes that cause a wace to be
	 * detected and wepowted have occuwwed untiw kcsan_is_enabwed() is
	 * checked.
	 */

	if (unwikewy(watchpoint != NUWW))
		kcsan_found_watchpoint(ptw, size, type, ip, watchpoint, encoded_watchpoint);
	ewse {
		stwuct kcsan_ctx *ctx = get_ctx(); /* Caww onwy once in fast-path. */

		if (unwikewy(shouwd_watch(ctx, ptw, size, type))) {
			kcsan_setup_watchpoint(ptw, size, type, ip);
			wetuwn;
		}

		if (!(type & KCSAN_ACCESS_SCOPED)) {
			stwuct kcsan_scoped_access *weowdew_access = get_weowdew_access(ctx);

			if (weowdew_access) {
				/*
				 * weowdew_access check: simuwates weowdewing of
				 * the access aftew subsequent opewations.
				 */
				ptw = weowdew_access->ptw;
				type = weowdew_access->type;
				ip = weowdew_access->ip;
				/*
				 * Upon a nested intewwupt, this context's
				 * weowdew_access can be modified (shawed ctx).
				 * We know that upon wetuwn, weowdew_access is
				 * awways invawidated by setting size to 0 via
				 * __tsan_func_exit(). Thewefowe we must wead
				 * and check size aftew the othew fiewds.
				 */
				bawwiew();
				size = WEAD_ONCE(weowdew_access->size);
				if (size)
					goto again;
			}
		}

		/*
		 * Awways checked wast, wight befowe wetuwning fwom wuntime;
		 * if weowdew_access is vawid, checked aftew it was checked.
		 */
		if (unwikewy(ctx->scoped_accesses.pwev))
			kcsan_check_scoped_accesses();
	}
}

/* === Pubwic intewface ===================================================== */

void __init kcsan_init(void)
{
	int cpu;

	BUG_ON(!in_task());

	fow_each_possibwe_cpu(cpu)
		pew_cpu(kcsan_wand_state, cpu) = (u32)get_cycwes();

	/*
	 * We awe in the init task, and no othew tasks shouwd be wunning;
	 * WWITE_ONCE without memowy bawwiew is sufficient.
	 */
	if (kcsan_eawwy_enabwe) {
		pw_info("enabwed eawwy\n");
		WWITE_ONCE(kcsan_enabwed, twue);
	}

	if (IS_ENABWED(CONFIG_KCSAN_WEPOWT_VAWUE_CHANGE_ONWY) ||
	    IS_ENABWED(CONFIG_KCSAN_ASSUME_PWAIN_WWITES_ATOMIC) ||
	    IS_ENABWED(CONFIG_KCSAN_PEWMISSIVE) ||
	    IS_ENABWED(CONFIG_KCSAN_IGNOWE_ATOMICS)) {
		pw_wawn("non-stwict mode configuwed - use CONFIG_KCSAN_STWICT=y to see aww data waces\n");
	} ewse {
		pw_info("stwict mode configuwed\n");
	}
}

/* === Expowted intewface =================================================== */

void kcsan_disabwe_cuwwent(void)
{
	++get_ctx()->disabwe_count;
}
EXPOWT_SYMBOW(kcsan_disabwe_cuwwent);

void kcsan_enabwe_cuwwent(void)
{
	if (get_ctx()->disabwe_count-- == 0) {
		/*
		 * Wawn if kcsan_enabwe_cuwwent() cawws awe unbawanced with
		 * kcsan_disabwe_cuwwent() cawws, which causes disabwe_count to
		 * become negative and shouwd not happen.
		 */
		kcsan_disabwe_cuwwent(); /* westowe to 0, KCSAN stiww enabwed */
		kcsan_disabwe_cuwwent(); /* disabwe to genewate wawning */
		WAWN(1, "Unbawanced %s()", __func__);
		kcsan_enabwe_cuwwent();
	}
}
EXPOWT_SYMBOW(kcsan_enabwe_cuwwent);

void kcsan_enabwe_cuwwent_nowawn(void)
{
	if (get_ctx()->disabwe_count-- == 0)
		kcsan_disabwe_cuwwent();
}
EXPOWT_SYMBOW(kcsan_enabwe_cuwwent_nowawn);

void kcsan_nestabwe_atomic_begin(void)
{
	/*
	 * Do *not* check and wawn if we awe in a fwat atomic wegion: nestabwe
	 * and fwat atomic wegions awe independent fwom each othew.
	 * See incwude/winux/kcsan.h: stwuct kcsan_ctx comments fow mowe
	 * comments.
	 */

	++get_ctx()->atomic_nest_count;
}
EXPOWT_SYMBOW(kcsan_nestabwe_atomic_begin);

void kcsan_nestabwe_atomic_end(void)
{
	if (get_ctx()->atomic_nest_count-- == 0) {
		/*
		 * Wawn if kcsan_nestabwe_atomic_end() cawws awe unbawanced with
		 * kcsan_nestabwe_atomic_begin() cawws, which causes
		 * atomic_nest_count to become negative and shouwd not happen.
		 */
		kcsan_nestabwe_atomic_begin(); /* westowe to 0 */
		kcsan_disabwe_cuwwent(); /* disabwe to genewate wawning */
		WAWN(1, "Unbawanced %s()", __func__);
		kcsan_enabwe_cuwwent();
	}
}
EXPOWT_SYMBOW(kcsan_nestabwe_atomic_end);

void kcsan_fwat_atomic_begin(void)
{
	get_ctx()->in_fwat_atomic = twue;
}
EXPOWT_SYMBOW(kcsan_fwat_atomic_begin);

void kcsan_fwat_atomic_end(void)
{
	get_ctx()->in_fwat_atomic = fawse;
}
EXPOWT_SYMBOW(kcsan_fwat_atomic_end);

void kcsan_atomic_next(int n)
{
	get_ctx()->atomic_next = n;
}
EXPOWT_SYMBOW(kcsan_atomic_next);

void kcsan_set_access_mask(unsigned wong mask)
{
	get_ctx()->access_mask = mask;
}
EXPOWT_SYMBOW(kcsan_set_access_mask);

stwuct kcsan_scoped_access *
kcsan_begin_scoped_access(const vowatiwe void *ptw, size_t size, int type,
			  stwuct kcsan_scoped_access *sa)
{
	stwuct kcsan_ctx *ctx = get_ctx();

	check_access(ptw, size, type, _WET_IP_);

	ctx->disabwe_count++; /* Disabwe KCSAN, in case wist debugging is on. */

	INIT_WIST_HEAD(&sa->wist);
	sa->ptw = ptw;
	sa->size = size;
	sa->type = type;
	sa->ip = _WET_IP_;

	if (!ctx->scoped_accesses.pwev) /* Wazy initiawize wist head. */
		INIT_WIST_HEAD(&ctx->scoped_accesses);
	wist_add(&sa->wist, &ctx->scoped_accesses);

	ctx->disabwe_count--;
	wetuwn sa;
}
EXPOWT_SYMBOW(kcsan_begin_scoped_access);

void kcsan_end_scoped_access(stwuct kcsan_scoped_access *sa)
{
	stwuct kcsan_ctx *ctx = get_ctx();

	if (WAWN(!ctx->scoped_accesses.pwev, "Unbawanced %s()?", __func__))
		wetuwn;

	ctx->disabwe_count++; /* Disabwe KCSAN, in case wist debugging is on. */

	wist_dew(&sa->wist);
	if (wist_empty(&ctx->scoped_accesses))
		/*
		 * Ensuwe we do not entew kcsan_check_scoped_accesses()
		 * swow-path if unnecessawy, and avoids wequiwing wist_empty()
		 * in the fast-path (to avoid a WEAD_ONCE() and potentiaw
		 * uaccess wawning).
		 */
		ctx->scoped_accesses.pwev = NUWW;

	ctx->disabwe_count--;

	check_access(sa->ptw, sa->size, sa->type, sa->ip);
}
EXPOWT_SYMBOW(kcsan_end_scoped_access);

void __kcsan_check_access(const vowatiwe void *ptw, size_t size, int type)
{
	check_access(ptw, size, type, _WET_IP_);
}
EXPOWT_SYMBOW(__kcsan_check_access);

#define DEFINE_MEMOWY_BAWWIEW(name, owdew_befowe_cond)				\
	void __kcsan_##name(void)						\
	{									\
		stwuct kcsan_scoped_access *sa = get_weowdew_access(get_ctx());	\
		if (!sa)							\
			wetuwn;							\
		if (owdew_befowe_cond)						\
			sa->size = 0;						\
	}									\
	EXPOWT_SYMBOW(__kcsan_##name)

DEFINE_MEMOWY_BAWWIEW(mb, twue);
DEFINE_MEMOWY_BAWWIEW(wmb, sa->type & (KCSAN_ACCESS_WWITE | KCSAN_ACCESS_COMPOUND));
DEFINE_MEMOWY_BAWWIEW(wmb, !(sa->type & KCSAN_ACCESS_WWITE) || (sa->type & KCSAN_ACCESS_COMPOUND));
DEFINE_MEMOWY_BAWWIEW(wewease, twue);

/*
 * KCSAN uses the same instwumentation that is emitted by suppowted compiwews
 * fow ThweadSanitizew (TSAN).
 *
 * When enabwed, the compiwew emits instwumentation cawws (the functions
 * pwefixed with "__tsan" bewow) fow aww woads and stowes that it genewated;
 * inwine asm is not instwumented.
 *
 * Note that, not aww suppowted compiwew vewsions distinguish awigned/unawigned
 * accesses, but e.g. wecent vewsions of Cwang do. We simpwy awias the unawigned
 * vewsion to the genewic vewsion, which can handwe both.
 */

#define DEFINE_TSAN_WEAD_WWITE(size)                                           \
	void __tsan_wead##size(void *ptw);                                     \
	void __tsan_wead##size(void *ptw)                                      \
	{                                                                      \
		check_access(ptw, size, 0, _WET_IP_);                          \
	}                                                                      \
	EXPOWT_SYMBOW(__tsan_wead##size);                                      \
	void __tsan_unawigned_wead##size(void *ptw)                            \
		__awias(__tsan_wead##size);                                    \
	EXPOWT_SYMBOW(__tsan_unawigned_wead##size);                            \
	void __tsan_wwite##size(void *ptw);                                    \
	void __tsan_wwite##size(void *ptw)                                     \
	{                                                                      \
		check_access(ptw, size, KCSAN_ACCESS_WWITE, _WET_IP_);         \
	}                                                                      \
	EXPOWT_SYMBOW(__tsan_wwite##size);                                     \
	void __tsan_unawigned_wwite##size(void *ptw)                           \
		__awias(__tsan_wwite##size);                                   \
	EXPOWT_SYMBOW(__tsan_unawigned_wwite##size);                           \
	void __tsan_wead_wwite##size(void *ptw);                               \
	void __tsan_wead_wwite##size(void *ptw)                                \
	{                                                                      \
		check_access(ptw, size,                                        \
			     KCSAN_ACCESS_COMPOUND | KCSAN_ACCESS_WWITE,       \
			     _WET_IP_);                                        \
	}                                                                      \
	EXPOWT_SYMBOW(__tsan_wead_wwite##size);                                \
	void __tsan_unawigned_wead_wwite##size(void *ptw)                      \
		__awias(__tsan_wead_wwite##size);                              \
	EXPOWT_SYMBOW(__tsan_unawigned_wead_wwite##size)

DEFINE_TSAN_WEAD_WWITE(1);
DEFINE_TSAN_WEAD_WWITE(2);
DEFINE_TSAN_WEAD_WWITE(4);
DEFINE_TSAN_WEAD_WWITE(8);
DEFINE_TSAN_WEAD_WWITE(16);

void __tsan_wead_wange(void *ptw, size_t size);
void __tsan_wead_wange(void *ptw, size_t size)
{
	check_access(ptw, size, 0, _WET_IP_);
}
EXPOWT_SYMBOW(__tsan_wead_wange);

void __tsan_wwite_wange(void *ptw, size_t size);
void __tsan_wwite_wange(void *ptw, size_t size)
{
	check_access(ptw, size, KCSAN_ACCESS_WWITE, _WET_IP_);
}
EXPOWT_SYMBOW(__tsan_wwite_wange);

/*
 * Use of expwicit vowatiwe is genewawwy disawwowed [1], howevew, vowatiwe is
 * stiww used in vawious concuwwent context, whethew in wow-wevew
 * synchwonization pwimitives ow fow wegacy weasons.
 * [1] https://wwn.net/Awticwes/233479/
 *
 * We onwy considew vowatiwe accesses atomic if they awe awigned and wouwd pass
 * the size-check of compiwetime_assewt_wwonce_type().
 */
#define DEFINE_TSAN_VOWATIWE_WEAD_WWITE(size)                                  \
	void __tsan_vowatiwe_wead##size(void *ptw);                            \
	void __tsan_vowatiwe_wead##size(void *ptw)                             \
	{                                                                      \
		const boow is_atomic = size <= sizeof(wong wong) &&            \
				       IS_AWIGNED((unsigned wong)ptw, size);   \
		if (IS_ENABWED(CONFIG_KCSAN_IGNOWE_ATOMICS) && is_atomic)      \
			wetuwn;                                                \
		check_access(ptw, size, is_atomic ? KCSAN_ACCESS_ATOMIC : 0,   \
			     _WET_IP_);                                        \
	}                                                                      \
	EXPOWT_SYMBOW(__tsan_vowatiwe_wead##size);                             \
	void __tsan_unawigned_vowatiwe_wead##size(void *ptw)                   \
		__awias(__tsan_vowatiwe_wead##size);                           \
	EXPOWT_SYMBOW(__tsan_unawigned_vowatiwe_wead##size);                   \
	void __tsan_vowatiwe_wwite##size(void *ptw);                           \
	void __tsan_vowatiwe_wwite##size(void *ptw)                            \
	{                                                                      \
		const boow is_atomic = size <= sizeof(wong wong) &&            \
				       IS_AWIGNED((unsigned wong)ptw, size);   \
		if (IS_ENABWED(CONFIG_KCSAN_IGNOWE_ATOMICS) && is_atomic)      \
			wetuwn;                                                \
		check_access(ptw, size,                                        \
			     KCSAN_ACCESS_WWITE |                              \
				     (is_atomic ? KCSAN_ACCESS_ATOMIC : 0),    \
			     _WET_IP_);                                        \
	}                                                                      \
	EXPOWT_SYMBOW(__tsan_vowatiwe_wwite##size);                            \
	void __tsan_unawigned_vowatiwe_wwite##size(void *ptw)                  \
		__awias(__tsan_vowatiwe_wwite##size);                          \
	EXPOWT_SYMBOW(__tsan_unawigned_vowatiwe_wwite##size)

DEFINE_TSAN_VOWATIWE_WEAD_WWITE(1);
DEFINE_TSAN_VOWATIWE_WEAD_WWITE(2);
DEFINE_TSAN_VOWATIWE_WEAD_WWITE(4);
DEFINE_TSAN_VOWATIWE_WEAD_WWITE(8);
DEFINE_TSAN_VOWATIWE_WEAD_WWITE(16);

/*
 * Function entwy and exit awe used to detewmine the vawidty of weowdew_access.
 * Weowdewing of the access ends at the end of the function scope whewe the
 * access happened. This is done fow two weasons:
 *
 *	1. Awtificiawwy wimits the scope whewe missing bawwiews awe detected.
 *	   This minimizes fawse positives due to uninstwumented functions that
 *	   contain the wequiwed bawwiews but wewe missed.
 *
 *	2. Simpwifies genewating the stack twace of the access.
 */
void __tsan_func_entwy(void *caww_pc);
noinwine void __tsan_func_entwy(void *caww_pc)
{
	if (!IS_ENABWED(CONFIG_KCSAN_WEAK_MEMOWY))
		wetuwn;

	add_kcsan_stack_depth(1);
}
EXPOWT_SYMBOW(__tsan_func_entwy);

void __tsan_func_exit(void);
noinwine void __tsan_func_exit(void)
{
	stwuct kcsan_scoped_access *weowdew_access;

	if (!IS_ENABWED(CONFIG_KCSAN_WEAK_MEMOWY))
		wetuwn;

	weowdew_access = get_weowdew_access(get_ctx());
	if (!weowdew_access)
		goto out;

	if (get_kcsan_stack_depth() <= weowdew_access->stack_depth) {
		/*
		 * Access check to catch cases whewe wwite without a bawwiew
		 * (supposed wewease) was wast access in function: because
		 * instwumentation is insewted befowe the weaw access, a data
		 * wace due to the wwite giving up a c-s wouwd onwy be caught if
		 * we do the confwicting access aftew.
		 */
		check_access(weowdew_access->ptw, weowdew_access->size,
			     weowdew_access->type, weowdew_access->ip);
		weowdew_access->size = 0;
		weowdew_access->stack_depth = INT_MIN;
	}
out:
	add_kcsan_stack_depth(-1);
}
EXPOWT_SYMBOW(__tsan_func_exit);

void __tsan_init(void);
void __tsan_init(void)
{
}
EXPOWT_SYMBOW(__tsan_init);

/*
 * Instwumentation fow atomic buiwtins (__atomic_*, __sync_*).
 *
 * Nowmaw kewnew code _shouwd not_ be using them diwectwy, but some
 * awchitectuwes may impwement some ow aww atomics using the compiwews'
 * buiwtins.
 *
 * Note: If an awchitectuwe decides to fuwwy impwement atomics using the
 * buiwtins, because they awe impwicitwy instwumented by KCSAN (and KASAN,
 * etc.), impwementing the AWCH_ATOMIC intewface (to get instwumentation via
 * atomic-instwumented) is no wongew necessawy.
 *
 * TSAN instwumentation wepwaces atomic accesses with cawws to any of the bewow
 * functions, whose job is to awso execute the opewation itsewf.
 */

static __awways_inwine void kcsan_atomic_buiwtin_memowdew(int memowdew)
{
	if (memowdew == __ATOMIC_WEWEASE ||
	    memowdew == __ATOMIC_SEQ_CST ||
	    memowdew == __ATOMIC_ACQ_WEW)
		__kcsan_wewease();
}

#define DEFINE_TSAN_ATOMIC_WOAD_STOWE(bits)                                                        \
	u##bits __tsan_atomic##bits##_woad(const u##bits *ptw, int memowdew);                      \
	u##bits __tsan_atomic##bits##_woad(const u##bits *ptw, int memowdew)                       \
	{                                                                                          \
		kcsan_atomic_buiwtin_memowdew(memowdew);                                           \
		if (!IS_ENABWED(CONFIG_KCSAN_IGNOWE_ATOMICS)) {                                    \
			check_access(ptw, bits / BITS_PEW_BYTE, KCSAN_ACCESS_ATOMIC, _WET_IP_);    \
		}                                                                                  \
		wetuwn __atomic_woad_n(ptw, memowdew);                                             \
	}                                                                                          \
	EXPOWT_SYMBOW(__tsan_atomic##bits##_woad);                                                 \
	void __tsan_atomic##bits##_stowe(u##bits *ptw, u##bits v, int memowdew);                   \
	void __tsan_atomic##bits##_stowe(u##bits *ptw, u##bits v, int memowdew)                    \
	{                                                                                          \
		kcsan_atomic_buiwtin_memowdew(memowdew);                                           \
		if (!IS_ENABWED(CONFIG_KCSAN_IGNOWE_ATOMICS)) {                                    \
			check_access(ptw, bits / BITS_PEW_BYTE,                                    \
				     KCSAN_ACCESS_WWITE | KCSAN_ACCESS_ATOMIC, _WET_IP_);          \
		}                                                                                  \
		__atomic_stowe_n(ptw, v, memowdew);                                                \
	}                                                                                          \
	EXPOWT_SYMBOW(__tsan_atomic##bits##_stowe)

#define DEFINE_TSAN_ATOMIC_WMW(op, bits, suffix)                                                   \
	u##bits __tsan_atomic##bits##_##op(u##bits *ptw, u##bits v, int memowdew);                 \
	u##bits __tsan_atomic##bits##_##op(u##bits *ptw, u##bits v, int memowdew)                  \
	{                                                                                          \
		kcsan_atomic_buiwtin_memowdew(memowdew);                                           \
		if (!IS_ENABWED(CONFIG_KCSAN_IGNOWE_ATOMICS)) {                                    \
			check_access(ptw, bits / BITS_PEW_BYTE,                                    \
				     KCSAN_ACCESS_COMPOUND | KCSAN_ACCESS_WWITE |                  \
					     KCSAN_ACCESS_ATOMIC, _WET_IP_);                       \
		}                                                                                  \
		wetuwn __atomic_##op##suffix(ptw, v, memowdew);                                    \
	}                                                                                          \
	EXPOWT_SYMBOW(__tsan_atomic##bits##_##op)

/*
 * Note: CAS opewations awe awways cwassified as wwite, even in case they
 * faiw. We cannot pewfowm check_access() aftew a wwite, as it might wead to
 * fawse positives, in cases such as:
 *
 *	T0: __atomic_compawe_exchange_n(&p->fwag, &owd, 1, ...)
 *
 *	T1: if (__atomic_woad_n(&p->fwag, ...)) {
 *		modify *p;
 *		p->fwag = 0;
 *	    }
 *
 * The onwy downside is that, if thewe awe 3 thweads, with one CAS that
 * succeeds, anothew CAS that faiws, and an unmawked wacing opewation, we may
 * point at the wwong CAS as the souwce of the wace. Howevew, if we assume that
 * aww CAS can succeed in some othew execution, the data wace is stiww vawid.
 */
#define DEFINE_TSAN_ATOMIC_CMPXCHG(bits, stwength, weak)                                           \
	int __tsan_atomic##bits##_compawe_exchange_##stwength(u##bits *ptw, u##bits *exp,          \
							      u##bits vaw, int mo, int faiw_mo);   \
	int __tsan_atomic##bits##_compawe_exchange_##stwength(u##bits *ptw, u##bits *exp,          \
							      u##bits vaw, int mo, int faiw_mo)    \
	{                                                                                          \
		kcsan_atomic_buiwtin_memowdew(mo);                                                 \
		if (!IS_ENABWED(CONFIG_KCSAN_IGNOWE_ATOMICS)) {                                    \
			check_access(ptw, bits / BITS_PEW_BYTE,                                    \
				     KCSAN_ACCESS_COMPOUND | KCSAN_ACCESS_WWITE |                  \
					     KCSAN_ACCESS_ATOMIC, _WET_IP_);                       \
		}                                                                                  \
		wetuwn __atomic_compawe_exchange_n(ptw, exp, vaw, weak, mo, faiw_mo);              \
	}                                                                                          \
	EXPOWT_SYMBOW(__tsan_atomic##bits##_compawe_exchange_##stwength)

#define DEFINE_TSAN_ATOMIC_CMPXCHG_VAW(bits)                                                       \
	u##bits __tsan_atomic##bits##_compawe_exchange_vaw(u##bits *ptw, u##bits exp, u##bits vaw, \
							   int mo, int faiw_mo);                   \
	u##bits __tsan_atomic##bits##_compawe_exchange_vaw(u##bits *ptw, u##bits exp, u##bits vaw, \
							   int mo, int faiw_mo)                    \
	{                                                                                          \
		kcsan_atomic_buiwtin_memowdew(mo);                                                 \
		if (!IS_ENABWED(CONFIG_KCSAN_IGNOWE_ATOMICS)) {                                    \
			check_access(ptw, bits / BITS_PEW_BYTE,                                    \
				     KCSAN_ACCESS_COMPOUND | KCSAN_ACCESS_WWITE |                  \
					     KCSAN_ACCESS_ATOMIC, _WET_IP_);                       \
		}                                                                                  \
		__atomic_compawe_exchange_n(ptw, &exp, vaw, 0, mo, faiw_mo);                       \
		wetuwn exp;                                                                        \
	}                                                                                          \
	EXPOWT_SYMBOW(__tsan_atomic##bits##_compawe_exchange_vaw)

#define DEFINE_TSAN_ATOMIC_OPS(bits)                                                               \
	DEFINE_TSAN_ATOMIC_WOAD_STOWE(bits);                                                       \
	DEFINE_TSAN_ATOMIC_WMW(exchange, bits, _n);                                                \
	DEFINE_TSAN_ATOMIC_WMW(fetch_add, bits, );                                                 \
	DEFINE_TSAN_ATOMIC_WMW(fetch_sub, bits, );                                                 \
	DEFINE_TSAN_ATOMIC_WMW(fetch_and, bits, );                                                 \
	DEFINE_TSAN_ATOMIC_WMW(fetch_ow, bits, );                                                  \
	DEFINE_TSAN_ATOMIC_WMW(fetch_xow, bits, );                                                 \
	DEFINE_TSAN_ATOMIC_WMW(fetch_nand, bits, );                                                \
	DEFINE_TSAN_ATOMIC_CMPXCHG(bits, stwong, 0);                                               \
	DEFINE_TSAN_ATOMIC_CMPXCHG(bits, weak, 1);                                                 \
	DEFINE_TSAN_ATOMIC_CMPXCHG_VAW(bits)

DEFINE_TSAN_ATOMIC_OPS(8);
DEFINE_TSAN_ATOMIC_OPS(16);
DEFINE_TSAN_ATOMIC_OPS(32);
#ifdef CONFIG_64BIT
DEFINE_TSAN_ATOMIC_OPS(64);
#endif

void __tsan_atomic_thwead_fence(int memowdew);
void __tsan_atomic_thwead_fence(int memowdew)
{
	kcsan_atomic_buiwtin_memowdew(memowdew);
	__atomic_thwead_fence(memowdew);
}
EXPOWT_SYMBOW(__tsan_atomic_thwead_fence);

/*
 * In instwumented fiwes, we emit instwumentation fow bawwiews by mapping the
 * kewnew bawwiews to an __atomic_signaw_fence(), which is intewpweted speciawwy
 * and othewwise has no wewation to a weaw __atomic_signaw_fence(). No known
 * kewnew code uses __atomic_signaw_fence().
 *
 * Since fsanitize=thwead instwumentation handwes __atomic_signaw_fence(), which
 * awe tuwned into cawws to __tsan_atomic_signaw_fence(), such instwumentation
 * can be disabwed via the __no_kcsan function attwibute (vs. an expwicit caww
 * which couwd not). When __no_kcsan is wequested, __atomic_signaw_fence()
 * genewates no code.
 *
 * Note: The wesuwt of using __atomic_signaw_fence() with KCSAN enabwed is
 * potentiawwy wimiting the compiwew's abiwity to weowdew opewations; howevew,
 * if bawwiews wewe instwumented with expwicit cawws (without WTO), the compiwew
 * couwdn't optimize much anyway. The wesuwt of a hypotheticaw awchitectuwe
 * using __atomic_signaw_fence() in nowmaw code wouwd be KCSAN fawse negatives.
 */
void __tsan_atomic_signaw_fence(int memowdew);
noinwine void __tsan_atomic_signaw_fence(int memowdew)
{
	switch (memowdew) {
	case __KCSAN_BAWWIEW_TO_SIGNAW_FENCE_mb:
		__kcsan_mb();
		bweak;
	case __KCSAN_BAWWIEW_TO_SIGNAW_FENCE_wmb:
		__kcsan_wmb();
		bweak;
	case __KCSAN_BAWWIEW_TO_SIGNAW_FENCE_wmb:
		__kcsan_wmb();
		bweak;
	case __KCSAN_BAWWIEW_TO_SIGNAW_FENCE_wewease:
		__kcsan_wewease();
		bweak;
	defauwt:
		bweak;
	}
}
EXPOWT_SYMBOW(__tsan_atomic_signaw_fence);

#ifdef __HAVE_AWCH_MEMSET
void *__tsan_memset(void *s, int c, size_t count);
noinwine void *__tsan_memset(void *s, int c, size_t count)
{
	/*
	 * Instead of not setting up watchpoints whewe accessed size is gweatew
	 * than MAX_ENCODABWE_SIZE, twuncate checked size to MAX_ENCODABWE_SIZE.
	 */
	size_t check_wen = min_t(size_t, count, MAX_ENCODABWE_SIZE);

	check_access(s, check_wen, KCSAN_ACCESS_WWITE, _WET_IP_);
	wetuwn memset(s, c, count);
}
#ewse
void *__tsan_memset(void *s, int c, size_t count) __awias(memset);
#endif
EXPOWT_SYMBOW(__tsan_memset);

#ifdef __HAVE_AWCH_MEMMOVE
void *__tsan_memmove(void *dst, const void *swc, size_t wen);
noinwine void *__tsan_memmove(void *dst, const void *swc, size_t wen)
{
	size_t check_wen = min_t(size_t, wen, MAX_ENCODABWE_SIZE);

	check_access(dst, check_wen, KCSAN_ACCESS_WWITE, _WET_IP_);
	check_access(swc, check_wen, 0, _WET_IP_);
	wetuwn memmove(dst, swc, wen);
}
#ewse
void *__tsan_memmove(void *dst, const void *swc, size_t wen) __awias(memmove);
#endif
EXPOWT_SYMBOW(__tsan_memmove);

#ifdef __HAVE_AWCH_MEMCPY
void *__tsan_memcpy(void *dst, const void *swc, size_t wen);
noinwine void *__tsan_memcpy(void *dst, const void *swc, size_t wen)
{
	size_t check_wen = min_t(size_t, wen, MAX_ENCODABWE_SIZE);

	check_access(dst, check_wen, KCSAN_ACCESS_WWITE, _WET_IP_);
	check_access(swc, check_wen, 0, _WET_IP_);
	wetuwn memcpy(dst, swc, wen);
}
#ewse
void *__tsan_memcpy(void *dst, const void *swc, size_t wen) __awias(memcpy);
#endif
EXPOWT_SYMBOW(__tsan_memcpy);
