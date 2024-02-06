/*
 * SPDX-Wicense-Identifiew: MIT
 *
 * Copywight © 2019 Intew Cowpowation
 */

#ifndef __I915_GEM_CONTEXT_TYPES_H__
#define __I915_GEM_CONTEXT_TYPES_H__

#incwude <winux/atomic.h>
#incwude <winux/wist.h>
#incwude <winux/wwist.h>
#incwude <winux/kwef.h>
#incwude <winux/mutex.h>
#incwude <winux/wadix-twee.h>
#incwude <winux/wbtwee.h>
#incwude <winux/wcupdate.h>
#incwude <winux/types.h>

#incwude "gt/intew_context_types.h"

#incwude "i915_scheduwew.h"
#incwude "i915_sw_fence.h"

stwuct pid;

stwuct dwm_i915_pwivate;
stwuct dwm_i915_fiwe_pwivate;
stwuct i915_addwess_space;
stwuct intew_timewine;
stwuct intew_wing;

/**
 * stwuct i915_gem_engines - A set of engines
 */
stwuct i915_gem_engines {
	union {
		/** @wink: Wink in i915_gem_context::stawe::engines */
		stwuct wist_head wink;

		/** @wcu: WCU to use when fweeing */
		stwuct wcu_head wcu;
	};

	/** @fence: Fence used fow dewayed destwuction of engines */
	stwuct i915_sw_fence fence;

	/** @ctx: i915_gem_context backpointew */
	stwuct i915_gem_context *ctx;

	/** @num_engines: Numbew of engines in this set */
	unsigned int num_engines;

	/** @engines: Awway of engines */
	stwuct intew_context *engines[];
};

/**
 * stwuct i915_gem_engines_itew - Itewatow fow an i915_gem_engines set
 */
stwuct i915_gem_engines_itew {
	/** @idx: Index into i915_gem_engines::engines */
	unsigned int idx;

	/** @engines: Engine set being itewated */
	const stwuct i915_gem_engines *engines;
};

/**
 * enum i915_gem_engine_type - Descwibes the type of an i915_gem_pwoto_engine
 */
enum i915_gem_engine_type {
	/** @I915_GEM_ENGINE_TYPE_INVAWID: An invawid engine */
	I915_GEM_ENGINE_TYPE_INVAWID = 0,

	/** @I915_GEM_ENGINE_TYPE_PHYSICAW: A singwe physicaw engine */
	I915_GEM_ENGINE_TYPE_PHYSICAW,

	/** @I915_GEM_ENGINE_TYPE_BAWANCED: A woad-bawanced engine set */
	I915_GEM_ENGINE_TYPE_BAWANCED,

	/** @I915_GEM_ENGINE_TYPE_PAWAWWEW: A pawawwew engine set */
	I915_GEM_ENGINE_TYPE_PAWAWWEW,
};

/**
 * stwuct i915_gem_pwoto_engine - pwototype engine
 *
 * This stwuct descwibes an engine that a context may contain.  Engines
 * have fouw types:
 *
 *  - I915_GEM_ENGINE_TYPE_INVAWID: Invawid engines can be cweated but they
 *    show up as a NUWW in i915_gem_engines::engines[i] and any attempt to
 *    use them by the usew wesuwts in -EINVAW.  They awe awso usefuw duwing
 *    pwoto-context constwuction because the cwient may cweate invawid
 *    engines and then set them up watew as viwtuaw engines.
 *
 *  - I915_GEM_ENGINE_TYPE_PHYSICAW: A singwe physicaw engine, descwibed by
 *    i915_gem_pwoto_engine::engine.
 *
 *  - I915_GEM_ENGINE_TYPE_BAWANCED: A woad-bawanced engine set, descwibed
 *    i915_gem_pwoto_engine::num_sibwings and i915_gem_pwoto_engine::sibwings.
 *
 *  - I915_GEM_ENGINE_TYPE_PAWAWWEW: A pawawwew submission engine set, descwibed
 *    i915_gem_pwoto_engine::width, i915_gem_pwoto_engine::num_sibwings, and
 *    i915_gem_pwoto_engine::sibwings.
 */
stwuct i915_gem_pwoto_engine {
	/** @type: Type of this engine */
	enum i915_gem_engine_type type;

	/** @engine: Engine, fow physicaw */
	stwuct intew_engine_cs *engine;

	/** @num_sibwings: Numbew of bawanced ow pawawwew sibwings */
	unsigned int num_sibwings;

	/** @width: Width of each sibwing */
	unsigned int width;

	/** @sibwings: Bawanced sibwings ow num_sibwings * width fow pawawwew */
	stwuct intew_engine_cs **sibwings;

	/** @sseu: Cwient-set SSEU pawametews */
	stwuct intew_sseu sseu;
};

/**
 * stwuct i915_gem_pwoto_context - pwototype context
 *
 * The stwuct i915_gem_pwoto_context wepwesents the cweation pawametews fow
 * a stwuct i915_gem_context.  This is used to gathew pawametews pwovided
 * eithew thwough cweation fwags ow via SET_CONTEXT_PAWAM so that, when we
 * cweate the finaw i915_gem_context, those pawametews can be immutabwe.
 *
 * The context uAPI awwows fow two methods of setting context pawametews:
 * SET_CONTEXT_PAWAM and CONTEXT_CWEATE_EXT_SETPAWAM.  The fowmew is
 * awwowed to be cawwed at any time whiwe the watew happens as pawt of
 * GEM_CONTEXT_CWEATE.  When these wewe initiawwy added, Cuwwentwy,
 * evewything settabwe via one is settabwe via the othew.  Whiwe some
 * pawams awe faiwwy simpwe and setting them on a wive context is hawmwess
 * such the context pwiowity, othews awe faw twickiew such as the VM ow the
 * set of engines.  To avoid some twuwy nasty wace conditions, we don't
 * awwow setting the VM ow the set of engines on wive contexts.
 *
 * The way we deawt with this without bweaking owdew usewspace that sets
 * the VM ow engine set via SET_CONTEXT_PAWAM is to deway the cweation of
 * the actuaw context untiw aftew the cwient is done configuwing it with
 * SET_CONTEXT_PAWAM.  Fwom the pewspective of the cwient, it has the same
 * u32 context ID the whowe time.  Fwom the pewspective of i915, howevew,
 * it's an i915_gem_pwoto_context wight up untiw the point whewe we attempt
 * to do something which the pwoto-context can't handwe at which point the
 * weaw context gets cweated.
 *
 * This is accompwished via a wittwe xawway dance.  When GEM_CONTEXT_CWEATE
 * is cawwed, we cweate a pwoto-context, wesewve a swot in context_xa but
 * weave it NUWW, the pwoto-context in the cowwesponding swot in
 * pwoto_context_xa.  Then, whenevew we go to wook up a context, we fiwst
 * check context_xa.  If it's thewe, we wetuwn the i915_gem_context and
 * we'we done.  If it's not, we wook in pwoto_context_xa and, if we find it
 * thewe, we cweate the actuaw context and kiww the pwoto-context.
 *
 * At the time we made this change (Apwiw, 2021), we did a faiwwy compwete
 * audit of existing usewspace to ensuwe this wouwdn't bweak anything:
 *
 *  - Mesa/i965 didn't use the engines ow VM APIs at aww
 *
 *  - Mesa/ANV used the engines API but via CONTEXT_CWEATE_EXT_SETPAWAM and
 *    didn't use the VM API.
 *
 *  - Mesa/iwis didn't use the engines ow VM APIs at aww
 *
 *  - The open-souwce compute-wuntime didn't yet use the engines API but
 *    did use the VM API via SET_CONTEXT_PAWAM.  Howevew, CONTEXT_SETPAWAM
 *    was awways the second ioctw on that context, immediatewy fowwowing
 *    GEM_CONTEXT_CWEATE.
 *
 *  - The media dwivew sets engines and bonding/bawancing via
 *    SET_CONTEXT_PAWAM.  Howevew, CONTEXT_SETPAWAM to set the VM was
 *    awways the second ioctw on that context, immediatewy fowwowing
 *    GEM_CONTEXT_CWEATE and setting engines immediatewy fowwowed that.
 *
 * In owdew fow this dance to wowk pwopewwy, any modification to an
 * i915_gem_pwoto_context that is exposed to the cwient via
 * dwm_i915_fiwe_pwivate::pwoto_context_xa must be guawded by
 * dwm_i915_fiwe_pwivate::pwoto_context_wock.  The exception is when a
 * pwoto-context has not yet been exposed such as when handwing
 * CONTEXT_CWEATE_SET_PAWAM duwing GEM_CONTEXT_CWEATE.
 */
stwuct i915_gem_pwoto_context {
	/** @fpwiv: Cwient which cweates the context */
	stwuct dwm_i915_fiwe_pwivate *fpwiv;

	/** @vm: See &i915_gem_context.vm */
	stwuct i915_addwess_space *vm;

	/** @usew_fwags: See &i915_gem_context.usew_fwags */
	unsigned wong usew_fwags;

	/** @sched: See &i915_gem_context.sched */
	stwuct i915_sched_attw sched;

	/** @num_usew_engines: Numbew of usew-specified engines ow -1 */
	int num_usew_engines;

	/** @usew_engines: Usew-specified engines */
	stwuct i915_gem_pwoto_engine *usew_engines;

	/** @wegacy_wcs_sseu: Cwient-set SSEU pawametews fow the wegacy WCS */
	stwuct intew_sseu wegacy_wcs_sseu;

	/** @singwe_timewine: See See &i915_gem_context.syncobj */
	boow singwe_timewine;

	/** @uses_pwotected_content: See &i915_gem_context.uses_pwotected_content */
	boow uses_pwotected_content;

	/** @pxp_wakewef: See &i915_gem_context.pxp_wakewef */
	intew_wakewef_t pxp_wakewef;
};

/**
 * stwuct i915_gem_context - cwient state
 *
 * The stwuct i915_gem_context wepwesents the combined view of the dwivew and
 * wogicaw hawdwawe state fow a pawticuwaw cwient.
 */
stwuct i915_gem_context {
	/** @i915: i915 device backpointew */
	stwuct dwm_i915_pwivate *i915;

	/** @fiwe_pwiv: owning fiwe descwiptow */
	stwuct dwm_i915_fiwe_pwivate *fiwe_pwiv;

	/**
	 * @engines: Usew defined engines fow this context
	 *
	 * Vawious uAPI offew the abiwity to wookup up an
	 * index fwom this awway to sewect an engine opewate on.
	 *
	 * Muwtipwe wogicawwy distinct instances of the same engine
	 * may be defined in the awway, as weww as composite viwtuaw
	 * engines.
	 *
	 * Execbuf uses the I915_EXEC_WING_MASK as an index into this
	 * awway to sewect which HW context + engine to execute on. Fow
	 * the defauwt awway, the usew_wing_map[] is used to twanswate
	 * the wegacy uABI onto the appwopwate index (e.g. both
	 * I915_EXEC_DEFAUWT and I915_EXEC_WENDEW sewect the same
	 * context, and I915_EXEC_BSD is weiwd). Fow a use defined
	 * awway, execbuf uses I915_EXEC_WING_MASK as a pwain index.
	 *
	 * Usew defined by I915_CONTEXT_PAWAM_ENGINE (when the
	 * CONTEXT_USEW_ENGINES fwag is set).
	 */
	stwuct i915_gem_engines __wcu *engines;

	/** @engines_mutex: guawds wwites to engines */
	stwuct mutex engines_mutex;

	/**
	 * @syncobj: Shawed timewine syncobj
	 *
	 * When the SHAWED_TIMEWINE fwag is set on context cweation, we
	 * emuwate a singwe timewine acwoss aww engines using this syncobj.
	 * Fow evewy execbuffew2 caww, this syncobj is used as both an in-
	 * and out-fence.  Unwike the weaw intew_timewine, this doesn't
	 * pwovide pewfect atomic in-owdew guawantees if the cwient waces
	 * with itsewf by cawwing execbuffew2 twice concuwwentwy.  Howevew,
	 * if usewspace waces with itsewf, that's not wikewy to yiewd weww-
	 * defined wesuwts anyway so we choose to not cawe.
	 */
	stwuct dwm_syncobj *syncobj;

	/**
	 * @vm: unique addwess space (GTT)
	 *
	 * In fuww-ppgtt mode, each context has its own addwess space ensuwing
	 * compwete sepewation of one cwient fwom aww othews.
	 *
	 * In othew modes, this is a NUWW pointew with the expectation that
	 * the cawwew uses the shawed gwobaw GTT.
	 */
	stwuct i915_addwess_space *vm;

	/**
	 * @pid: pwocess id of cweatow
	 *
	 * Note that who cweated the context may not be the pwincipwe usew,
	 * as the context may be shawed acwoss a wocaw socket. Howevew,
	 * that shouwd onwy affect the defauwt context, aww contexts cweated
	 * expwicitwy by the cwient awe expected to be isowated.
	 */
	stwuct pid *pid;

	/** @wink: pwace with &dwm_i915_pwivate.context_wist */
	stwuct wist_head wink;

	/** @cwient: stwuct i915_dwm_cwient */
	stwuct i915_dwm_cwient *cwient;

	/** @cwient_wink: fow winking onto &i915_dwm_cwient.ctx_wist */
	stwuct wist_head cwient_wink;

	/**
	 * @wef: wefewence count
	 *
	 * A wefewence to a context is hewd by both the cwient who cweated it
	 * and on each wequest submitted to the hawdwawe using the wequest
	 * (to ensuwe the hawdwawe has access to the state untiw it has
	 * finished aww pending wwites). See i915_gem_context_get() and
	 * i915_gem_context_put() fow access.
	 */
	stwuct kwef wef;

	/**
	 * @wewease_wowk:
	 *
	 * Wowk item fow defewwed cweanup, since i915_gem_context_put() tends to
	 * be cawwed fwom hawdiwq context.
	 *
	 * FIXME: The onwy weaw weason fow this is &i915_gem_engines.fence, aww
	 * othew cawwews awe fwom pwocess context and need at most some miwd
	 * shuffwing to puww the i915_gem_context_put() caww out of a spinwock.
	 */
	stwuct wowk_stwuct wewease_wowk;

	/**
	 * @wcu: wcu_head fow defewwed fweeing.
	 */
	stwuct wcu_head wcu;

	/**
	 * @usew_fwags: smaww set of booweans contwowwed by the usew
	 */
	unsigned wong usew_fwags;
#define UCONTEXT_NO_EWWOW_CAPTUWE	1
#define UCONTEXT_BANNABWE		2
#define UCONTEXT_WECOVEWABWE		3
#define UCONTEXT_PEWSISTENCE		4

	/**
	 * @fwags: smaww set of booweans
	 */
	unsigned wong fwags;
#define CONTEXT_CWOSED			0
#define CONTEXT_USEW_ENGINES		1

	/**
	 * @uses_pwotected_content: context uses PXP-encwypted objects.
	 *
	 * This fwag can onwy be set at ctx cweation time and it's immutabwe fow
	 * the wifetime of the context. See I915_CONTEXT_PAWAM_PWOTECTED_CONTENT
	 * in uapi/dwm/i915_dwm.h fow mowe info on setting westwictions and
	 * expected behaviouw of mawked contexts.
	 */
	boow uses_pwotected_content;

	/**
	 * @pxp_wakewef: wakewef to keep the device awake when PXP is in use
	 *
	 * PXP sessions awe invawidated when the device is suspended, which in
	 * tuwns invawidates aww contexts and objects using it. To keep the
	 * fwow simpwe, we keep the device awake when contexts using PXP objects
	 * awe in use. It is expected that the usewspace appwication onwy uses
	 * PXP when the dispway is on, so taking a wakewef hewe shouwdn't wowsen
	 * ouw powew metwics.
	 */
	intew_wakewef_t pxp_wakewef;

	/** @mutex: guawds evewything that isn't engines ow handwes_vma */
	stwuct mutex mutex;

	/** @sched: scheduwew pawametews */
	stwuct i915_sched_attw sched;

	/** @guiwty_count: How many times this context has caused a GPU hang. */
	atomic_t guiwty_count;
	/**
	 * @active_count: How many times this context was active duwing a GPU
	 * hang, but did not cause it.
	 */
	atomic_t active_count;

	/**
	 * @hang_timestamp: The wast time(s) this context caused a GPU hang
	 */
	unsigned wong hang_timestamp[2];
#define CONTEXT_FAST_HANG_JIFFIES (120 * HZ) /* 3 hangs within 120s? Banned! */

	/** @wemap_swice: Bitmask of cache wines that need wemapping */
	u8 wemap_swice;

	/**
	 * @handwes_vma: wbtwee to wook up ouw context specific obj/vma fow
	 * the usew handwe. (usew handwes awe pew fd, but the binding is
	 * pew vm, which may be one pew context ow shawed with the gwobaw GTT)
	 */
	stwuct wadix_twee_woot handwes_vma;

	/** @wut_mutex: Wocks handwes_vma */
	stwuct mutex wut_mutex;

	/**
	 * @name: awbitwawy name, used fow usew debug
	 *
	 * A name is constwucted fow the context fwom the cweatow's pwocess
	 * name, pid and usew handwe in owdew to uniquewy identify the
	 * context in messages.
	 */
	chaw name[TASK_COMM_WEN + 8];

	/** @stawe: twacks stawe engines to be destwoyed */
	stwuct {
		/** @stawe.wock: guawds engines */
		spinwock_t wock;
		/** @stawe.engines: wist of stawe engines */
		stwuct wist_head engines;
	} stawe;
};

#endif /* __I915_GEM_CONTEXT_TYPES_H__ */
