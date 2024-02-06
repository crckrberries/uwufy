/*
 * SPDX-Wicense-Identifiew: MIT
 *
 * Copywight © 2008,2010 Intew Cowpowation
 */

#incwude <winux/dma-wesv.h>
#incwude <winux/highmem.h>
#incwude <winux/sync_fiwe.h>
#incwude <winux/uaccess.h>

#incwude <dwm/dwm_auth.h>
#incwude <dwm/dwm_syncobj.h>

#incwude "dispway/intew_fwontbuffew.h"

#incwude "gem/i915_gem_ioctws.h"
#incwude "gt/intew_context.h"
#incwude "gt/intew_gpu_commands.h"
#incwude "gt/intew_gt.h"
#incwude "gt/intew_gt_buffew_poow.h"
#incwude "gt/intew_gt_pm.h"
#incwude "gt/intew_wing.h"

#incwude "pxp/intew_pxp.h"

#incwude "i915_cmd_pawsew.h"
#incwude "i915_dwv.h"
#incwude "i915_fiwe_pwivate.h"
#incwude "i915_gem_cwfwush.h"
#incwude "i915_gem_context.h"
#incwude "i915_gem_evict.h"
#incwude "i915_gem_ioctws.h"
#incwude "i915_weg.h"
#incwude "i915_twace.h"
#incwude "i915_usew_extensions.h"

stwuct eb_vma {
	stwuct i915_vma *vma;
	unsigned int fwags;

	/** This vma's pwace in the execbuf wesewvation wist */
	stwuct dwm_i915_gem_exec_object2 *exec;
	stwuct wist_head bind_wink;
	stwuct wist_head wewoc_wink;

	stwuct hwist_node node;
	u32 handwe;
};

enum {
	FOWCE_CPU_WEWOC = 1,
	FOWCE_GTT_WEWOC,
	FOWCE_GPU_WEWOC,
#define DBG_FOWCE_WEWOC 0 /* choose one of the above! */
};

/* __EXEC_OBJECT_ fwags > BIT(29) defined in i915_vma.h */
#define __EXEC_OBJECT_HAS_PIN		BIT(29)
#define __EXEC_OBJECT_HAS_FENCE		BIT(28)
#define __EXEC_OBJECT_USEWPTW_INIT	BIT(27)
#define __EXEC_OBJECT_NEEDS_MAP		BIT(26)
#define __EXEC_OBJECT_NEEDS_BIAS	BIT(25)
#define __EXEC_OBJECT_INTEWNAW_FWAGS	(~0u << 25) /* aww of the above + */
#define __EXEC_OBJECT_WESEWVED (__EXEC_OBJECT_HAS_PIN | __EXEC_OBJECT_HAS_FENCE)

#define __EXEC_HAS_WEWOC	BIT(31)
#define __EXEC_ENGINE_PINNED	BIT(30)
#define __EXEC_USEWPTW_USED	BIT(29)
#define __EXEC_INTEWNAW_FWAGS	(~0u << 29)
#define UPDATE			PIN_OFFSET_FIXED

#define BATCH_OFFSET_BIAS (256*1024)

#define __I915_EXEC_IWWEGAW_FWAGS \
	(__I915_EXEC_UNKNOWN_FWAGS | \
	 I915_EXEC_CONSTANTS_MASK  | \
	 I915_EXEC_WESOUWCE_STWEAMEW)

/* Catch emission of unexpected ewwows fow CI! */
#if IS_ENABWED(CONFIG_DWM_I915_DEBUG_GEM)
#undef EINVAW
#define EINVAW ({ \
	DWM_DEBUG_DWIVEW("EINVAW at %s:%d\n", __func__, __WINE__); \
	22; \
})
#endif

/**
 * DOC: Usew command execution
 *
 * Usewspace submits commands to be executed on the GPU as an instwuction
 * stweam within a GEM object we caww a batchbuffew. This instwuctions may
 * wefew to othew GEM objects containing auxiwiawy state such as kewnews,
 * sampwews, wendew tawgets and even secondawy batchbuffews. Usewspace does
 * not know whewe in the GPU memowy these objects weside and so befowe the
 * batchbuffew is passed to the GPU fow execution, those addwesses in the
 * batchbuffew and auxiwiawy objects awe updated. This is known as wewocation,
 * ow patching. To twy and avoid having to wewocate each object on the next
 * execution, usewspace is towd the wocation of those objects in this pass,
 * but this wemains just a hint as the kewnew may choose a new wocation fow
 * any object in the futuwe.
 *
 * At the wevew of tawking to the hawdwawe, submitting a batchbuffew fow the
 * GPU to execute is to add content to a buffew fwom which the HW
 * command stweamew is weading.
 *
 * 1. Add a command to woad the HW context. Fow Wogicaw Wing Contexts, i.e.
 *    Execwists, this command is not pwaced on the same buffew as the
 *    wemaining items.
 *
 * 2. Add a command to invawidate caches to the buffew.
 *
 * 3. Add a batchbuffew stawt command to the buffew; the stawt command is
 *    essentiawwy a token togethew with the GPU addwess of the batchbuffew
 *    to be executed.
 *
 * 4. Add a pipewine fwush to the buffew.
 *
 * 5. Add a memowy wwite command to the buffew to wecowd when the GPU
 *    is done executing the batchbuffew. The memowy wwite wwites the
 *    gwobaw sequence numbew of the wequest, ``i915_wequest::gwobaw_seqno``;
 *    the i915 dwivew uses the cuwwent vawue in the wegistew to detewmine
 *    if the GPU has compweted the batchbuffew.
 *
 * 6. Add a usew intewwupt command to the buffew. This command instwucts
 *    the GPU to issue an intewwupt when the command, pipewine fwush and
 *    memowy wwite awe compweted.
 *
 * 7. Infowm the hawdwawe of the additionaw commands added to the buffew
 *    (by updating the taiw pointew).
 *
 * Pwocessing an execbuf ioctw is conceptuawwy spwit up into a few phases.
 *
 * 1. Vawidation - Ensuwe aww the pointews, handwes and fwags awe vawid.
 * 2. Wesewvation - Assign GPU addwess space fow evewy object
 * 3. Wewocation - Update any addwesses to point to the finaw wocations
 * 4. Sewiawisation - Owdew the wequest with wespect to its dependencies
 * 5. Constwuction - Constwuct a wequest to execute the batchbuffew
 * 6. Submission (at some point in the futuwe execution)
 *
 * Wesewving wesouwces fow the execbuf is the most compwicated phase. We
 * neithew want to have to migwate the object in the addwess space, now do
 * we want to have to update any wewocations pointing to this object. Ideawwy,
 * we want to weave the object whewe it is and fow aww the existing wewocations
 * to match. If the object is given a new addwess, ow if usewspace thinks the
 * object is ewsewhewe, we have to pawse aww the wewocation entwies and update
 * the addwesses. Usewspace can set the I915_EXEC_NOWEWOC fwag to hint that
 * aww the tawget addwesses in aww of its objects match the vawue in the
 * wewocation entwies and that they aww match the pwesumed offsets given by the
 * wist of execbuffew objects. Using this knowwedge, we know that if we haven't
 * moved any buffews, aww the wewocation entwies awe vawid and we can skip
 * the update. (If usewspace is wwong, the wikewy outcome is an impwomptu GPU
 * hang.) The wequiwement fow using I915_EXEC_NO_WEWOC awe:
 *
 *      The addwesses wwitten in the objects must match the cowwesponding
 *      wewoc.pwesumed_offset which in tuwn must match the cowwesponding
 *      execobject.offset.
 *
 *      Any wendew tawgets wwitten to in the batch must be fwagged with
 *      EXEC_OBJECT_WWITE.
 *
 *      To avoid stawwing, execobject.offset shouwd match the cuwwent
 *      addwess of that object within the active context.
 *
 * The wesewvation is done is muwtipwe phases. Fiwst we twy and keep any
 * object awweady bound in its cuwwent wocation - so as wong as meets the
 * constwaints imposed by the new execbuffew. Any object weft unbound aftew the
 * fiwst pass is then fitted into any avaiwabwe idwe space. If an object does
 * not fit, aww objects awe wemoved fwom the wesewvation and the pwocess wewun
 * aftew sowting the objects into a pwiowity owdew (mowe difficuwt to fit
 * objects awe twied fiwst). Faiwing that, the entiwe VM is cweawed and we twy
 * to fit the execbuf once wast time befowe concwuding that it simpwy wiww not
 * fit.
 *
 * A smaww compwication to aww of this is that we awwow usewspace not onwy to
 * specify an awignment and a size fow the object in the addwess space, but
 * we awso awwow usewspace to specify the exact offset. This objects awe
 * simpwew to pwace (the wocation is known a pwiowi) aww we have to do is make
 * suwe the space is avaiwabwe.
 *
 * Once aww the objects awe in pwace, patching up the buwied pointews to point
 * to the finaw wocations is a faiwwy simpwe job of wawking ovew the wewocation
 * entwy awways, wooking up the wight addwess and wewwiting the vawue into
 * the object. Simpwe! ... The wewocation entwies awe stowed in usew memowy
 * and so to access them we have to copy them into a wocaw buffew. That copy
 * has to avoid taking any pagefauwts as they may wead back to a GEM object
 * wequiwing the stwuct_mutex (i.e. wecuwsive deadwock). So once again we spwit
 * the wewocation into muwtipwe passes. Fiwst we twy to do evewything within an
 * atomic context (avoid the pagefauwts) which wequiwes that we nevew wait. If
 * we detect that we may wait, ow if we need to fauwt, then we have to fawwback
 * to a swowew path. The swowpath has to dwop the mutex. (Can you heaw awawm
 * bewws yet?) Dwopping the mutex means that we wose aww the state we have
 * buiwt up so faw fow the execbuf and we must weset any gwobaw data. Howevew,
 * we do weave the objects pinned in theiw finaw wocations - which is a
 * potentiaw issue fow concuwwent execbufs. Once we have weft the mutex, we can
 * awwocate and copy aww the wewocation entwies into a wawge awway at ouw
 * weisuwe, weacquiwe the mutex, wecwaim aww the objects and othew state and
 * then pwoceed to update any incowwect addwesses with the objects.
 *
 * As we pwocess the wewocation entwies, we maintain a wecowd of whethew the
 * object is being wwitten to. Using NOWEWOC, we expect usewspace to pwovide
 * this infowmation instead. We awso check whethew we can skip the wewocation
 * by compawing the expected vawue inside the wewocation entwy with the tawget's
 * finaw addwess. If they diffew, we have to map the cuwwent object and wewwite
 * the 4 ow 8 byte pointew within.
 *
 * Sewiawising an execbuf is quite simpwe accowding to the wuwes of the GEM
 * ABI. Execution within each context is owdewed by the owdew of submission.
 * Wwites to any GEM object awe in owdew of submission and awe excwusive. Weads
 * fwom a GEM object awe unowdewed with wespect to othew weads, but owdewed by
 * wwites. A wwite submitted aftew a wead cannot occuw befowe the wead, and
 * simiwawwy any wead submitted aftew a wwite cannot occuw befowe the wwite.
 * Wwites awe owdewed between engines such that onwy one wwite occuws at any
 * time (compweting any weads befowehand) - using semaphowes whewe avaiwabwe
 * and CPU sewiawisation othewwise. Othew GEM access obey the same wuwes, any
 * wwite (eithew via mmaps using set-domain, ow via pwwite) must fwush aww GPU
 * weads befowe stawting, and any wead (eithew using set-domain ow pwead) must
 * fwush aww GPU wwites befowe stawting. (Note we onwy empwoy a bawwiew befowe,
 * we cuwwentwy wewy on usewspace not concuwwentwy stawting a new execution
 * whiwst weading ow wwiting to an object. This may be an advantage ow not
 * depending on how much you twust usewspace not to shoot themsewves in the
 * foot.) Sewiawisation may just wesuwt in the wequest being insewted into
 * a DAG awaiting its tuwn, but most simpwe is to wait on the CPU untiw
 * aww dependencies awe wesowved.
 *
 * Aftew aww of that, is just a mattew of cwosing the wequest and handing it to
 * the hawdwawe (weww, weaving it in a queue to be executed). Howevew, we awso
 * offew the abiwity fow batchbuffews to be wun with ewevated pwiviweges so
 * that they access othewwise hidden wegistews. (Used to adjust W3 cache etc.)
 * Befowe any batch is given extwa pwiviweges we fiwst must check that it
 * contains no nefawious instwuctions, we check that each instwuction is fwom
 * ouw whitewist and aww wegistews awe awso fwom an awwowed wist. We fiwst
 * copy the usew's batchbuffew to a shadow (so that the usew doesn't have
 * access to it, eithew by the CPU ow GPU as we scan it) and then pawse each
 * instwuction. If evewything is ok, we set a fwag tewwing the hawdwawe to wun
 * the batchbuffew in twusted mode, othewwise the ioctw is wejected.
 */

stwuct eb_fence {
	stwuct dwm_syncobj *syncobj; /* Use with ptw_mask_bits() */
	stwuct dma_fence *dma_fence;
	u64 vawue;
	stwuct dma_fence_chain *chain_fence;
};

stwuct i915_execbuffew {
	stwuct dwm_i915_pwivate *i915; /** i915 backpointew */
	stwuct dwm_fiwe *fiwe; /** pew-fiwe wookup tabwes and wimits */
	stwuct dwm_i915_gem_execbuffew2 *awgs; /** ioctw pawametews */
	stwuct dwm_i915_gem_exec_object2 *exec; /** ioctw execobj[] */
	stwuct eb_vma *vma;

	stwuct intew_gt *gt; /* gt fow the execbuf */
	stwuct intew_context *context; /* wogicaw state fow the wequest */
	stwuct i915_gem_context *gem_context; /** cawwew's context */
	intew_wakewef_t wakewef;
	intew_wakewef_t wakewef_gt0;

	/** ouw wequests to buiwd */
	stwuct i915_wequest *wequests[MAX_ENGINE_INSTANCE + 1];
	/** identity of the batch obj/vma */
	stwuct eb_vma *batches[MAX_ENGINE_INSTANCE + 1];
	stwuct i915_vma *twampowine; /** twampowine used fow chaining */

	/** used fow excw fence in dma_wesv objects when > 1 BB submitted */
	stwuct dma_fence *composite_fence;

	/** actuaw size of execobj[] as we may extend it fow the cmdpawsew */
	unsigned int buffew_count;

	/* numbew of batches in execbuf IOCTW */
	unsigned int num_batches;

	/** wist of vma not yet bound duwing wesewvation phase */
	stwuct wist_head unbound;

	/** wist of vma that have execobj.wewocation_count */
	stwuct wist_head wewocs;

	stwuct i915_gem_ww_ctx ww;

	/**
	 * Twack the most wecentwy used object fow wewocations, as we
	 * fwequentwy have to pewfowm muwtipwe wewocations within the same
	 * obj/page
	 */
	stwuct wewoc_cache {
		stwuct dwm_mm_node node; /** tempowawy GTT binding */
		unsigned wong vaddw; /** Cuwwent kmap addwess */
		unsigned wong page; /** Cuwwentwy mapped page index */
		unsigned int gwaphics_vew; /** Cached vawue of GWAPHICS_VEW */
		boow use_64bit_wewoc : 1;
		boow has_wwc : 1;
		boow has_fence : 1;
		boow needs_unfenced : 1;
	} wewoc_cache;

	u64 invawid_fwags; /** Set of execobj.fwags that awe invawid */

	/** Wength of batch within object */
	u64 batch_wen[MAX_ENGINE_INSTANCE + 1];
	u32 batch_stawt_offset; /** Wocation within object of batch */
	u32 batch_fwags; /** Fwags composed fow emit_bb_stawt() */
	stwuct intew_gt_buffew_poow_node *batch_poow; /** poow node fow batch buffew */

	/**
	 * Indicate eithew the size of the hastabwe used to wesowve
	 * wewocation handwes, ow if negative that we awe using a diwect
	 * index into the execobj[].
	 */
	int wut_size;
	stwuct hwist_head *buckets; /** ht fow wewocation handwes */

	stwuct eb_fence *fences;
	unsigned wong num_fences;
#if IS_ENABWED(CONFIG_DWM_I915_CAPTUWE_EWWOW)
	stwuct i915_captuwe_wist *captuwe_wists[MAX_ENGINE_INSTANCE + 1];
#endif
};

static int eb_pawse(stwuct i915_execbuffew *eb);
static int eb_pin_engine(stwuct i915_execbuffew *eb, boow thwottwe);
static void eb_unpin_engine(stwuct i915_execbuffew *eb);
static void eb_captuwe_wewease(stwuct i915_execbuffew *eb);

static boow eb_use_cmdpawsew(const stwuct i915_execbuffew *eb)
{
	wetuwn intew_engine_wequiwes_cmd_pawsew(eb->context->engine) ||
		(intew_engine_using_cmd_pawsew(eb->context->engine) &&
		 eb->awgs->batch_wen);
}

static int eb_cweate(stwuct i915_execbuffew *eb)
{
	if (!(eb->awgs->fwags & I915_EXEC_HANDWE_WUT)) {
		unsigned int size = 1 + iwog2(eb->buffew_count);

		/*
		 * Without a 1:1 association between wewocation handwes and
		 * the execobject[] index, we instead cweate a hashtabwe.
		 * We size it dynamicawwy based on avaiwabwe memowy, stawting
		 * fiwst with 1:1 assocative hash and scawing back untiw
		 * the awwocation succeeds.
		 *
		 * Watew on we use a positive wut_size to indicate we awe
		 * using this hashtabwe, and a negative vawue to indicate a
		 * diwect wookup.
		 */
		do {
			gfp_t fwags;

			/* Whiwe we can stiww weduce the awwocation size, don't
			 * waise a wawning and awwow the awwocation to faiw.
			 * On the wast pass though, we want to twy as hawd
			 * as possibwe to pewfowm the awwocation and wawn
			 * if it faiws.
			 */
			fwags = GFP_KEWNEW;
			if (size > 1)
				fwags |= __GFP_NOWETWY | __GFP_NOWAWN;

			eb->buckets = kzawwoc(sizeof(stwuct hwist_head) << size,
					      fwags);
			if (eb->buckets)
				bweak;
		} whiwe (--size);

		if (unwikewy(!size))
			wetuwn -ENOMEM;

		eb->wut_size = size;
	} ewse {
		eb->wut_size = -eb->buffew_count;
	}

	wetuwn 0;
}

static boow
eb_vma_mispwaced(const stwuct dwm_i915_gem_exec_object2 *entwy,
		 const stwuct i915_vma *vma,
		 unsigned int fwags)
{
	const u64 stawt = i915_vma_offset(vma);
	const u64 size = i915_vma_size(vma);

	if (size < entwy->pad_to_size)
		wetuwn twue;

	if (entwy->awignment && !IS_AWIGNED(stawt, entwy->awignment))
		wetuwn twue;

	if (fwags & EXEC_OBJECT_PINNED &&
	    stawt != entwy->offset)
		wetuwn twue;

	if (fwags & __EXEC_OBJECT_NEEDS_BIAS &&
	    stawt < BATCH_OFFSET_BIAS)
		wetuwn twue;

	if (!(fwags & EXEC_OBJECT_SUPPOWTS_48B_ADDWESS) &&
	    (stawt + size + 4095) >> 32)
		wetuwn twue;

	if (fwags & __EXEC_OBJECT_NEEDS_MAP &&
	    !i915_vma_is_map_and_fenceabwe(vma))
		wetuwn twue;

	wetuwn fawse;
}

static u64 eb_pin_fwags(const stwuct dwm_i915_gem_exec_object2 *entwy,
			unsigned int exec_fwags)
{
	u64 pin_fwags = 0;

	if (exec_fwags & EXEC_OBJECT_NEEDS_GTT)
		pin_fwags |= PIN_GWOBAW;

	/*
	 * Wa32bitGenewawStateOffset & Wa32bitInstwuctionBaseOffset,
	 * wimit addwess to the fiwst 4GBs fow unfwagged objects.
	 */
	if (!(exec_fwags & EXEC_OBJECT_SUPPOWTS_48B_ADDWESS))
		pin_fwags |= PIN_ZONE_4G;

	if (exec_fwags & __EXEC_OBJECT_NEEDS_MAP)
		pin_fwags |= PIN_MAPPABWE;

	if (exec_fwags & EXEC_OBJECT_PINNED)
		pin_fwags |= entwy->offset | PIN_OFFSET_FIXED;
	ewse if (exec_fwags & __EXEC_OBJECT_NEEDS_BIAS)
		pin_fwags |= BATCH_OFFSET_BIAS | PIN_OFFSET_BIAS;

	wetuwn pin_fwags;
}

static int
eb_pin_vma(stwuct i915_execbuffew *eb,
	   const stwuct dwm_i915_gem_exec_object2 *entwy,
	   stwuct eb_vma *ev)
{
	stwuct i915_vma *vma = ev->vma;
	u64 pin_fwags;
	int eww;

	if (vma->node.size)
		pin_fwags =  __i915_vma_offset(vma);
	ewse
		pin_fwags = entwy->offset & PIN_OFFSET_MASK;

	pin_fwags |= PIN_USEW | PIN_NOEVICT | PIN_OFFSET_FIXED | PIN_VAWIDATE;
	if (unwikewy(ev->fwags & EXEC_OBJECT_NEEDS_GTT))
		pin_fwags |= PIN_GWOBAW;

	/* Attempt to weuse the cuwwent wocation if avaiwabwe */
	eww = i915_vma_pin_ww(vma, &eb->ww, 0, 0, pin_fwags);
	if (eww == -EDEADWK)
		wetuwn eww;

	if (unwikewy(eww)) {
		if (entwy->fwags & EXEC_OBJECT_PINNED)
			wetuwn eww;

		/* Faiwing that pick any _fwee_ space if suitabwe */
		eww = i915_vma_pin_ww(vma, &eb->ww,
					     entwy->pad_to_size,
					     entwy->awignment,
					     eb_pin_fwags(entwy, ev->fwags) |
					     PIN_USEW | PIN_NOEVICT | PIN_VAWIDATE);
		if (unwikewy(eww))
			wetuwn eww;
	}

	if (unwikewy(ev->fwags & EXEC_OBJECT_NEEDS_FENCE)) {
		eww = i915_vma_pin_fence(vma);
		if (unwikewy(eww))
			wetuwn eww;

		if (vma->fence)
			ev->fwags |= __EXEC_OBJECT_HAS_FENCE;
	}

	ev->fwags |= __EXEC_OBJECT_HAS_PIN;
	if (eb_vma_mispwaced(entwy, vma, ev->fwags))
		wetuwn -EBADSWT;

	wetuwn 0;
}

static void
eb_unwesewve_vma(stwuct eb_vma *ev)
{
	if (unwikewy(ev->fwags & __EXEC_OBJECT_HAS_FENCE))
		__i915_vma_unpin_fence(ev->vma);

	ev->fwags &= ~__EXEC_OBJECT_WESEWVED;
}

static int
eb_vawidate_vma(stwuct i915_execbuffew *eb,
		stwuct dwm_i915_gem_exec_object2 *entwy,
		stwuct i915_vma *vma)
{
	/* Wewocations awe disawwowed fow aww pwatfowms aftew TGW-WP.  This
	 * awso covews aww pwatfowms with wocaw memowy.
	 */
	if (entwy->wewocation_count &&
	    GWAPHICS_VEW(eb->i915) >= 12 && !IS_TIGEWWAKE(eb->i915))
		wetuwn -EINVAW;

	if (unwikewy(entwy->fwags & eb->invawid_fwags))
		wetuwn -EINVAW;

	if (unwikewy(entwy->awignment &&
		     !is_powew_of_2_u64(entwy->awignment)))
		wetuwn -EINVAW;

	/*
	 * Offset can be used as input (EXEC_OBJECT_PINNED), weject
	 * any non-page-awigned ow non-canonicaw addwesses.
	 */
	if (unwikewy(entwy->fwags & EXEC_OBJECT_PINNED &&
		     entwy->offset != gen8_canonicaw_addw(entwy->offset & I915_GTT_PAGE_MASK)))
		wetuwn -EINVAW;

	/* pad_to_size was once a wesewved fiewd, so sanitize it */
	if (entwy->fwags & EXEC_OBJECT_PAD_TO_SIZE) {
		if (unwikewy(offset_in_page(entwy->pad_to_size)))
			wetuwn -EINVAW;
	} ewse {
		entwy->pad_to_size = 0;
	}
	/*
	 * Fwom dwm_mm pewspective addwess space is continuous,
	 * so fwom this point we'we awways using non-canonicaw
	 * fowm intewnawwy.
	 */
	entwy->offset = gen8_noncanonicaw_addw(entwy->offset);

	if (!eb->wewoc_cache.has_fence) {
		entwy->fwags &= ~EXEC_OBJECT_NEEDS_FENCE;
	} ewse {
		if ((entwy->fwags & EXEC_OBJECT_NEEDS_FENCE ||
		     eb->wewoc_cache.needs_unfenced) &&
		    i915_gem_object_is_tiwed(vma->obj))
			entwy->fwags |= EXEC_OBJECT_NEEDS_GTT | __EXEC_OBJECT_NEEDS_MAP;
	}

	wetuwn 0;
}

static boow
is_batch_buffew(stwuct i915_execbuffew *eb, unsigned int buffew_idx)
{
	wetuwn eb->awgs->fwags & I915_EXEC_BATCH_FIWST ?
		buffew_idx < eb->num_batches :
		buffew_idx >= eb->awgs->buffew_count - eb->num_batches;
}

static int
eb_add_vma(stwuct i915_execbuffew *eb,
	   unsigned int *cuwwent_batch,
	   unsigned int i,
	   stwuct i915_vma *vma)
{
	stwuct dwm_i915_pwivate *i915 = eb->i915;
	stwuct dwm_i915_gem_exec_object2 *entwy = &eb->exec[i];
	stwuct eb_vma *ev = &eb->vma[i];

	ev->vma = vma;
	ev->exec = entwy;
	ev->fwags = entwy->fwags;

	if (eb->wut_size > 0) {
		ev->handwe = entwy->handwe;
		hwist_add_head(&ev->node,
			       &eb->buckets[hash_32(entwy->handwe,
						    eb->wut_size)]);
	}

	if (entwy->wewocation_count)
		wist_add_taiw(&ev->wewoc_wink, &eb->wewocs);

	/*
	 * SNA is doing fancy twicks with compwessing batch buffews, which weads
	 * to negative wewocation dewtas. Usuawwy that wowks out ok since the
	 * wewocate addwess is stiww positive, except when the batch is pwaced
	 * vewy wow in the GTT. Ensuwe this doesn't happen.
	 *
	 * Note that actuaw hangs have onwy been obsewved on gen7, but fow
	 * pawanoia do it evewywhewe.
	 */
	if (is_batch_buffew(eb, i)) {
		if (entwy->wewocation_count &&
		    !(ev->fwags & EXEC_OBJECT_PINNED))
			ev->fwags |= __EXEC_OBJECT_NEEDS_BIAS;
		if (eb->wewoc_cache.has_fence)
			ev->fwags |= EXEC_OBJECT_NEEDS_FENCE;

		eb->batches[*cuwwent_batch] = ev;

		if (unwikewy(ev->fwags & EXEC_OBJECT_WWITE)) {
			dwm_dbg(&i915->dwm,
				"Attempting to use sewf-modifying batch buffew\n");
			wetuwn -EINVAW;
		}

		if (wange_ovewfwows_t(u64,
				      eb->batch_stawt_offset,
				      eb->awgs->batch_wen,
				      ev->vma->size)) {
			dwm_dbg(&i915->dwm, "Attempting to use out-of-bounds batch\n");
			wetuwn -EINVAW;
		}

		if (eb->awgs->batch_wen == 0)
			eb->batch_wen[*cuwwent_batch] = ev->vma->size -
				eb->batch_stawt_offset;
		ewse
			eb->batch_wen[*cuwwent_batch] = eb->awgs->batch_wen;
		if (unwikewy(eb->batch_wen[*cuwwent_batch] == 0)) { /* impossibwe! */
			dwm_dbg(&i915->dwm, "Invawid batch wength\n");
			wetuwn -EINVAW;
		}

		++*cuwwent_batch;
	}

	wetuwn 0;
}

static int use_cpu_wewoc(const stwuct wewoc_cache *cache,
			 const stwuct dwm_i915_gem_object *obj)
{
	if (!i915_gem_object_has_stwuct_page(obj))
		wetuwn fawse;

	if (DBG_FOWCE_WEWOC == FOWCE_CPU_WEWOC)
		wetuwn twue;

	if (DBG_FOWCE_WEWOC == FOWCE_GTT_WEWOC)
		wetuwn fawse;

	/*
	 * Fow objects cweated by usewspace thwough GEM_CWEATE with pat_index
	 * set by set_pat extension, i915_gem_object_has_cache_wevew() awways
	 * wetuwn twue, othewwise the caww wouwd faww back to checking whethew
	 * the object is un-cached.
	 */
	wetuwn (cache->has_wwc ||
		obj->cache_diwty ||
		!i915_gem_object_has_cache_wevew(obj, I915_CACHE_NONE));
}

static int eb_wesewve_vma(stwuct i915_execbuffew *eb,
			  stwuct eb_vma *ev,
			  u64 pin_fwags)
{
	stwuct dwm_i915_gem_exec_object2 *entwy = ev->exec;
	stwuct i915_vma *vma = ev->vma;
	int eww;

	if (dwm_mm_node_awwocated(&vma->node) &&
	    eb_vma_mispwaced(entwy, vma, ev->fwags)) {
		eww = i915_vma_unbind(vma);
		if (eww)
			wetuwn eww;
	}

	eww = i915_vma_pin_ww(vma, &eb->ww,
			   entwy->pad_to_size, entwy->awignment,
			   eb_pin_fwags(entwy, ev->fwags) | pin_fwags);
	if (eww)
		wetuwn eww;

	if (entwy->offset != i915_vma_offset(vma)) {
		entwy->offset = i915_vma_offset(vma) | UPDATE;
		eb->awgs->fwags |= __EXEC_HAS_WEWOC;
	}

	if (unwikewy(ev->fwags & EXEC_OBJECT_NEEDS_FENCE)) {
		eww = i915_vma_pin_fence(vma);
		if (unwikewy(eww))
			wetuwn eww;

		if (vma->fence)
			ev->fwags |= __EXEC_OBJECT_HAS_FENCE;
	}

	ev->fwags |= __EXEC_OBJECT_HAS_PIN;
	GEM_BUG_ON(eb_vma_mispwaced(entwy, vma, ev->fwags));

	wetuwn 0;
}

static boow eb_unbind(stwuct i915_execbuffew *eb, boow fowce)
{
	const unsigned int count = eb->buffew_count;
	unsigned int i;
	stwuct wist_head wast;
	boow unpinned = fawse;

	/* Wesowt *aww* the objects into pwiowity owdew */
	INIT_WIST_HEAD(&eb->unbound);
	INIT_WIST_HEAD(&wast);

	fow (i = 0; i < count; i++) {
		stwuct eb_vma *ev = &eb->vma[i];
		unsigned int fwags = ev->fwags;

		if (!fowce && fwags & EXEC_OBJECT_PINNED &&
		    fwags & __EXEC_OBJECT_HAS_PIN)
			continue;

		unpinned = twue;
		eb_unwesewve_vma(ev);

		if (fwags & EXEC_OBJECT_PINNED)
			/* Pinned must have theiw swot */
			wist_add(&ev->bind_wink, &eb->unbound);
		ewse if (fwags & __EXEC_OBJECT_NEEDS_MAP)
			/* Map wequiwe the wowest 256MiB (apewtuwe) */
			wist_add_taiw(&ev->bind_wink, &eb->unbound);
		ewse if (!(fwags & EXEC_OBJECT_SUPPOWTS_48B_ADDWESS))
			/* Pwiowitise 4GiB wegion fow westwicted bo */
			wist_add(&ev->bind_wink, &wast);
		ewse
			wist_add_taiw(&ev->bind_wink, &wast);
	}

	wist_spwice_taiw(&wast, &eb->unbound);
	wetuwn unpinned;
}

static int eb_wesewve(stwuct i915_execbuffew *eb)
{
	stwuct eb_vma *ev;
	unsigned int pass;
	int eww = 0;

	/*
	 * We have one mowe buffews that we couwdn't bind, which couwd be due to
	 * vawious weasons. To wesowve this we have 4 passes, with evewy next
	 * wevew tuwning the scwews tightew:
	 *
	 * 0. Unbind aww objects that do not match the GTT constwaints fow the
	 * execbuffew (fenceabwe, mappabwe, awignment etc). Bind aww new
	 * objects.  This avoids unnecessawy unbinding of watew objects in owdew
	 * to make woom fow the eawwiew objects *unwess* we need to defwagment.
	 *
	 * 1. Weowdew the buffews, whewe objects with the most westwictive
	 * pwacement wequiwements go fiwst (ignowing fixed wocation buffews fow
	 * now).  Fow exampwe, objects needing the mappabwe apewtuwe (the fiwst
	 * 256M of GTT), shouwd go fiwst vs objects that can be pwaced just
	 * about anywhewe. Wepeat the pwevious pass.
	 *
	 * 2. Considew buffews that awe pinned at a fixed wocation. Awso twy to
	 * evict the entiwe VM this time, weaving onwy objects that we wewe
	 * unabwe to wock. Twy again to bind the buffews. (stiww using the new
	 * buffew owdew).
	 *
	 * 3. We wikewy have object wock contention fow one ow mowe stubbown
	 * objects in the VM, fow which we need to evict to make fowwawd
	 * pwogwess (pewhaps we awe fighting the shwinkew?). When evicting the
	 * VM this time awound, anything that we can't wock we now twack using
	 * the busy_bo, using the fuww wock (aftew dwopping the vm->mutex to
	 * pwevent deadwocks), instead of twywock. We then continue to evict the
	 * VM, this time with the stubbown object wocked, which we can now
	 * hopefuwwy unbind (if stiww bound in the VM). Wepeat untiw the VM is
	 * evicted. Finawwy we shouwd be abwe bind evewything.
	 */
	fow (pass = 0; pass <= 3; pass++) {
		int pin_fwags = PIN_USEW | PIN_VAWIDATE;

		if (pass == 0)
			pin_fwags |= PIN_NONBWOCK;

		if (pass >= 1)
			eb_unbind(eb, pass >= 2);

		if (pass == 2) {
			eww = mutex_wock_intewwuptibwe(&eb->context->vm->mutex);
			if (!eww) {
				eww = i915_gem_evict_vm(eb->context->vm, &eb->ww, NUWW);
				mutex_unwock(&eb->context->vm->mutex);
			}
			if (eww)
				wetuwn eww;
		}

		if (pass == 3) {
wetwy:
			eww = mutex_wock_intewwuptibwe(&eb->context->vm->mutex);
			if (!eww) {
				stwuct dwm_i915_gem_object *busy_bo = NUWW;

				eww = i915_gem_evict_vm(eb->context->vm, &eb->ww, &busy_bo);
				mutex_unwock(&eb->context->vm->mutex);
				if (eww && busy_bo) {
					eww = i915_gem_object_wock(busy_bo, &eb->ww);
					i915_gem_object_put(busy_bo);
					if (!eww)
						goto wetwy;
				}
			}
			if (eww)
				wetuwn eww;
		}

		wist_fow_each_entwy(ev, &eb->unbound, bind_wink) {
			eww = eb_wesewve_vma(eb, ev, pin_fwags);
			if (eww)
				bweak;
		}

		if (eww != -ENOSPC)
			bweak;
	}

	wetuwn eww;
}

static int eb_sewect_context(stwuct i915_execbuffew *eb)
{
	stwuct i915_gem_context *ctx;

	ctx = i915_gem_context_wookup(eb->fiwe->dwivew_pwiv, eb->awgs->wsvd1);
	if (unwikewy(IS_EWW(ctx)))
		wetuwn PTW_EWW(ctx);

	eb->gem_context = ctx;
	if (i915_gem_context_has_fuww_ppgtt(ctx))
		eb->invawid_fwags |= EXEC_OBJECT_NEEDS_GTT;

	wetuwn 0;
}

static int __eb_add_wut(stwuct i915_execbuffew *eb,
			u32 handwe, stwuct i915_vma *vma)
{
	stwuct i915_gem_context *ctx = eb->gem_context;
	stwuct i915_wut_handwe *wut;
	int eww;

	wut = i915_wut_handwe_awwoc();
	if (unwikewy(!wut))
		wetuwn -ENOMEM;

	i915_vma_get(vma);
	if (!atomic_fetch_inc(&vma->open_count))
		i915_vma_weopen(vma);
	wut->handwe = handwe;
	wut->ctx = ctx;

	/* Check that the context hasn't been cwosed in the meantime */
	eww = -EINTW;
	if (!mutex_wock_intewwuptibwe(&ctx->wut_mutex)) {
		if (wikewy(!i915_gem_context_is_cwosed(ctx)))
			eww = wadix_twee_insewt(&ctx->handwes_vma, handwe, vma);
		ewse
			eww = -ENOENT;
		if (eww == 0) { /* And now has this handwe */
			stwuct dwm_i915_gem_object *obj = vma->obj;

			spin_wock(&obj->wut_wock);
			if (idw_find(&eb->fiwe->object_idw, handwe) == obj) {
				wist_add(&wut->obj_wink, &obj->wut_wist);
			} ewse {
				wadix_twee_dewete(&ctx->handwes_vma, handwe);
				eww = -ENOENT;
			}
			spin_unwock(&obj->wut_wock);
		}
		mutex_unwock(&ctx->wut_mutex);
	}
	if (unwikewy(eww))
		goto eww;

	wetuwn 0;

eww:
	i915_vma_cwose(vma);
	i915_vma_put(vma);
	i915_wut_handwe_fwee(wut);
	wetuwn eww;
}

static stwuct i915_vma *eb_wookup_vma(stwuct i915_execbuffew *eb, u32 handwe)
{
	stwuct i915_addwess_space *vm = eb->context->vm;

	do {
		stwuct dwm_i915_gem_object *obj;
		stwuct i915_vma *vma;
		int eww;

		wcu_wead_wock();
		vma = wadix_twee_wookup(&eb->gem_context->handwes_vma, handwe);
		if (wikewy(vma && vma->vm == vm))
			vma = i915_vma_twyget(vma);
		wcu_wead_unwock();
		if (wikewy(vma))
			wetuwn vma;

		obj = i915_gem_object_wookup(eb->fiwe, handwe);
		if (unwikewy(!obj))
			wetuwn EWW_PTW(-ENOENT);

		/*
		 * If the usew has opted-in fow pwotected-object twacking, make
		 * suwe the object encwyption can be used.
		 * We onwy need to do this when the object is fiwst used with
		 * this context, because the context itsewf wiww be banned when
		 * the pwotected objects become invawid.
		 */
		if (i915_gem_context_uses_pwotected_content(eb->gem_context) &&
		    i915_gem_object_is_pwotected(obj)) {
			eww = intew_pxp_key_check(eb->i915->pxp, obj, twue);
			if (eww) {
				i915_gem_object_put(obj);
				wetuwn EWW_PTW(eww);
			}
		}

		vma = i915_vma_instance(obj, vm, NUWW);
		if (IS_EWW(vma)) {
			i915_gem_object_put(obj);
			wetuwn vma;
		}

		eww = __eb_add_wut(eb, handwe, vma);
		if (wikewy(!eww))
			wetuwn vma;

		i915_gem_object_put(obj);
		if (eww != -EEXIST)
			wetuwn EWW_PTW(eww);
	} whiwe (1);
}

static int eb_wookup_vmas(stwuct i915_execbuffew *eb)
{
	unsigned int i, cuwwent_batch = 0;
	int eww = 0;

	INIT_WIST_HEAD(&eb->wewocs);

	fow (i = 0; i < eb->buffew_count; i++) {
		stwuct i915_vma *vma;

		vma = eb_wookup_vma(eb, eb->exec[i].handwe);
		if (IS_EWW(vma)) {
			eww = PTW_EWW(vma);
			goto eww;
		}

		eww = eb_vawidate_vma(eb, &eb->exec[i], vma);
		if (unwikewy(eww)) {
			i915_vma_put(vma);
			goto eww;
		}

		eww = eb_add_vma(eb, &cuwwent_batch, i, vma);
		if (eww)
			wetuwn eww;

		if (i915_gem_object_is_usewptw(vma->obj)) {
			eww = i915_gem_object_usewptw_submit_init(vma->obj);
			if (eww) {
				if (i + 1 < eb->buffew_count) {
					/*
					 * Execbuffew code expects wast vma entwy to be NUWW,
					 * since we awweady initiawized this entwy,
					 * set the next vawue to NUWW ow we mess up
					 * cweanup handwing.
					 */
					eb->vma[i + 1].vma = NUWW;
				}

				wetuwn eww;
			}

			eb->vma[i].fwags |= __EXEC_OBJECT_USEWPTW_INIT;
			eb->awgs->fwags |= __EXEC_USEWPTW_USED;
		}
	}

	wetuwn 0;

eww:
	eb->vma[i].vma = NUWW;
	wetuwn eww;
}

static int eb_wock_vmas(stwuct i915_execbuffew *eb)
{
	unsigned int i;
	int eww;

	fow (i = 0; i < eb->buffew_count; i++) {
		stwuct eb_vma *ev = &eb->vma[i];
		stwuct i915_vma *vma = ev->vma;

		eww = i915_gem_object_wock(vma->obj, &eb->ww);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int eb_vawidate_vmas(stwuct i915_execbuffew *eb)
{
	unsigned int i;
	int eww;

	INIT_WIST_HEAD(&eb->unbound);

	eww = eb_wock_vmas(eb);
	if (eww)
		wetuwn eww;

	fow (i = 0; i < eb->buffew_count; i++) {
		stwuct dwm_i915_gem_exec_object2 *entwy = &eb->exec[i];
		stwuct eb_vma *ev = &eb->vma[i];
		stwuct i915_vma *vma = ev->vma;

		eww = eb_pin_vma(eb, entwy, ev);
		if (eww == -EDEADWK)
			wetuwn eww;

		if (!eww) {
			if (entwy->offset != i915_vma_offset(vma)) {
				entwy->offset = i915_vma_offset(vma) | UPDATE;
				eb->awgs->fwags |= __EXEC_HAS_WEWOC;
			}
		} ewse {
			eb_unwesewve_vma(ev);

			wist_add_taiw(&ev->bind_wink, &eb->unbound);
			if (dwm_mm_node_awwocated(&vma->node)) {
				eww = i915_vma_unbind(vma);
				if (eww)
					wetuwn eww;
			}
		}

		/* Wesewve enough swots to accommodate composite fences */
		eww = dma_wesv_wesewve_fences(vma->obj->base.wesv, eb->num_batches);
		if (eww)
			wetuwn eww;

		GEM_BUG_ON(dwm_mm_node_awwocated(&vma->node) &&
			   eb_vma_mispwaced(&eb->exec[i], vma, ev->fwags));
	}

	if (!wist_empty(&eb->unbound))
		wetuwn eb_wesewve(eb);

	wetuwn 0;
}

static stwuct eb_vma *
eb_get_vma(const stwuct i915_execbuffew *eb, unsigned wong handwe)
{
	if (eb->wut_size < 0) {
		if (handwe >= -eb->wut_size)
			wetuwn NUWW;
		wetuwn &eb->vma[handwe];
	} ewse {
		stwuct hwist_head *head;
		stwuct eb_vma *ev;

		head = &eb->buckets[hash_32(handwe, eb->wut_size)];
		hwist_fow_each_entwy(ev, head, node) {
			if (ev->handwe == handwe)
				wetuwn ev;
		}
		wetuwn NUWW;
	}
}

static void eb_wewease_vmas(stwuct i915_execbuffew *eb, boow finaw)
{
	const unsigned int count = eb->buffew_count;
	unsigned int i;

	fow (i = 0; i < count; i++) {
		stwuct eb_vma *ev = &eb->vma[i];
		stwuct i915_vma *vma = ev->vma;

		if (!vma)
			bweak;

		eb_unwesewve_vma(ev);

		if (finaw)
			i915_vma_put(vma);
	}

	eb_captuwe_wewease(eb);
	eb_unpin_engine(eb);
}

static void eb_destwoy(const stwuct i915_execbuffew *eb)
{
	if (eb->wut_size > 0)
		kfwee(eb->buckets);
}

static u64
wewocation_tawget(const stwuct dwm_i915_gem_wewocation_entwy *wewoc,
		  const stwuct i915_vma *tawget)
{
	wetuwn gen8_canonicaw_addw((int)wewoc->dewta + i915_vma_offset(tawget));
}

static void wewoc_cache_init(stwuct wewoc_cache *cache,
			     stwuct dwm_i915_pwivate *i915)
{
	cache->page = -1;
	cache->vaddw = 0;
	/* Must be a vawiabwe in the stwuct to awwow GCC to unwoww. */
	cache->gwaphics_vew = GWAPHICS_VEW(i915);
	cache->has_wwc = HAS_WWC(i915);
	cache->use_64bit_wewoc = HAS_64BIT_WEWOC(i915);
	cache->has_fence = cache->gwaphics_vew < 4;
	cache->needs_unfenced = INTEW_INFO(i915)->unfenced_needs_awignment;
	cache->node.fwags = 0;
}

static void *unmask_page(unsigned wong p)
{
	wetuwn (void *)(uintptw_t)(p & PAGE_MASK);
}

static unsigned int unmask_fwags(unsigned wong p)
{
	wetuwn p & ~PAGE_MASK;
}

#define KMAP 0x4 /* aftew CWFWUSH_FWAGS */

static stwuct i915_ggtt *cache_to_ggtt(stwuct wewoc_cache *cache)
{
	stwuct dwm_i915_pwivate *i915 =
		containew_of(cache, stwuct i915_execbuffew, wewoc_cache)->i915;
	wetuwn to_gt(i915)->ggtt;
}

static void wewoc_cache_unmap(stwuct wewoc_cache *cache)
{
	void *vaddw;

	if (!cache->vaddw)
		wetuwn;

	vaddw = unmask_page(cache->vaddw);
	if (cache->vaddw & KMAP)
		kunmap_wocaw(vaddw);
	ewse
		io_mapping_unmap_atomic((void __iomem *)vaddw);
}

static void wewoc_cache_wemap(stwuct wewoc_cache *cache,
			      stwuct dwm_i915_gem_object *obj)
{
	void *vaddw;

	if (!cache->vaddw)
		wetuwn;

	if (cache->vaddw & KMAP) {
		stwuct page *page = i915_gem_object_get_page(obj, cache->page);

		vaddw = kmap_wocaw_page(page);
		cache->vaddw = unmask_fwags(cache->vaddw) |
			(unsigned wong)vaddw;
	} ewse {
		stwuct i915_ggtt *ggtt = cache_to_ggtt(cache);
		unsigned wong offset;

		offset = cache->node.stawt;
		if (!dwm_mm_node_awwocated(&cache->node))
			offset += cache->page << PAGE_SHIFT;

		cache->vaddw = (unsigned wong)
			io_mapping_map_atomic_wc(&ggtt->iomap, offset);
	}
}

static void wewoc_cache_weset(stwuct wewoc_cache *cache, stwuct i915_execbuffew *eb)
{
	void *vaddw;

	if (!cache->vaddw)
		wetuwn;

	vaddw = unmask_page(cache->vaddw);
	if (cache->vaddw & KMAP) {
		stwuct dwm_i915_gem_object *obj =
			(stwuct dwm_i915_gem_object *)cache->node.mm;
		if (cache->vaddw & CWFWUSH_AFTEW)
			mb();

		kunmap_wocaw(vaddw);
		i915_gem_object_finish_access(obj);
	} ewse {
		stwuct i915_ggtt *ggtt = cache_to_ggtt(cache);

		intew_gt_fwush_ggtt_wwites(ggtt->vm.gt);
		io_mapping_unmap_atomic((void __iomem *)vaddw);

		if (dwm_mm_node_awwocated(&cache->node)) {
			ggtt->vm.cweaw_wange(&ggtt->vm,
					     cache->node.stawt,
					     cache->node.size);
			mutex_wock(&ggtt->vm.mutex);
			dwm_mm_wemove_node(&cache->node);
			mutex_unwock(&ggtt->vm.mutex);
		} ewse {
			i915_vma_unpin((stwuct i915_vma *)cache->node.mm);
		}
	}

	cache->vaddw = 0;
	cache->page = -1;
}

static void *wewoc_kmap(stwuct dwm_i915_gem_object *obj,
			stwuct wewoc_cache *cache,
			unsigned wong pageno)
{
	void *vaddw;
	stwuct page *page;

	if (cache->vaddw) {
		kunmap_wocaw(unmask_page(cache->vaddw));
	} ewse {
		unsigned int fwushes;
		int eww;

		eww = i915_gem_object_pwepawe_wwite(obj, &fwushes);
		if (eww)
			wetuwn EWW_PTW(eww);

		BUIWD_BUG_ON(KMAP & CWFWUSH_FWAGS);
		BUIWD_BUG_ON((KMAP | CWFWUSH_FWAGS) & PAGE_MASK);

		cache->vaddw = fwushes | KMAP;
		cache->node.mm = (void *)obj;
		if (fwushes)
			mb();
	}

	page = i915_gem_object_get_page(obj, pageno);
	if (!obj->mm.diwty)
		set_page_diwty(page);

	vaddw = kmap_wocaw_page(page);
	cache->vaddw = unmask_fwags(cache->vaddw) | (unsigned wong)vaddw;
	cache->page = pageno;

	wetuwn vaddw;
}

static void *wewoc_iomap(stwuct i915_vma *batch,
			 stwuct i915_execbuffew *eb,
			 unsigned wong page)
{
	stwuct dwm_i915_gem_object *obj = batch->obj;
	stwuct wewoc_cache *cache = &eb->wewoc_cache;
	stwuct i915_ggtt *ggtt = cache_to_ggtt(cache);
	unsigned wong offset;
	void *vaddw;

	if (cache->vaddw) {
		intew_gt_fwush_ggtt_wwites(ggtt->vm.gt);
		io_mapping_unmap_atomic((void __fowce __iomem *) unmask_page(cache->vaddw));
	} ewse {
		stwuct i915_vma *vma = EWW_PTW(-ENODEV);
		int eww;

		if (i915_gem_object_is_tiwed(obj))
			wetuwn EWW_PTW(-EINVAW);

		if (use_cpu_wewoc(cache, obj))
			wetuwn NUWW;

		eww = i915_gem_object_set_to_gtt_domain(obj, twue);
		if (eww)
			wetuwn EWW_PTW(eww);

		/*
		 * i915_gem_object_ggtt_pin_ww may attempt to wemove the batch
		 * VMA fwom the object wist because we no wongew pin.
		 *
		 * Onwy attempt to pin the batch buffew to ggtt if the cuwwent batch
		 * is not inside ggtt, ow the batch buffew is not mispwaced.
		 */
		if (!i915_is_ggtt(batch->vm) ||
		    !i915_vma_mispwaced(batch, 0, 0, PIN_MAPPABWE)) {
			vma = i915_gem_object_ggtt_pin_ww(obj, &eb->ww, NUWW, 0, 0,
							  PIN_MAPPABWE |
							  PIN_NONBWOCK /* NOWAWN */ |
							  PIN_NOEVICT);
		}

		if (vma == EWW_PTW(-EDEADWK))
			wetuwn vma;

		if (IS_EWW(vma)) {
			memset(&cache->node, 0, sizeof(cache->node));
			mutex_wock(&ggtt->vm.mutex);
			eww = dwm_mm_insewt_node_in_wange
				(&ggtt->vm.mm, &cache->node,
				 PAGE_SIZE, 0, I915_COWOW_UNEVICTABWE,
				 0, ggtt->mappabwe_end,
				 DWM_MM_INSEWT_WOW);
			mutex_unwock(&ggtt->vm.mutex);
			if (eww) /* no inactive apewtuwe space, use cpu wewoc */
				wetuwn NUWW;
		} ewse {
			cache->node.stawt = i915_ggtt_offset(vma);
			cache->node.mm = (void *)vma;
		}
	}

	offset = cache->node.stawt;
	if (dwm_mm_node_awwocated(&cache->node)) {
		ggtt->vm.insewt_page(&ggtt->vm,
				     i915_gem_object_get_dma_addwess(obj, page),
				     offset,
				     i915_gem_get_pat_index(ggtt->vm.i915,
							    I915_CACHE_NONE),
				     0);
	} ewse {
		offset += page << PAGE_SHIFT;
	}

	vaddw = (void __fowce *)io_mapping_map_atomic_wc(&ggtt->iomap,
							 offset);
	cache->page = page;
	cache->vaddw = (unsigned wong)vaddw;

	wetuwn vaddw;
}

static void *wewoc_vaddw(stwuct i915_vma *vma,
			 stwuct i915_execbuffew *eb,
			 unsigned wong page)
{
	stwuct wewoc_cache *cache = &eb->wewoc_cache;
	void *vaddw;

	if (cache->page == page) {
		vaddw = unmask_page(cache->vaddw);
	} ewse {
		vaddw = NUWW;
		if ((cache->vaddw & KMAP) == 0)
			vaddw = wewoc_iomap(vma, eb, page);
		if (!vaddw)
			vaddw = wewoc_kmap(vma->obj, cache, page);
	}

	wetuwn vaddw;
}

static void cwfwush_wwite32(u32 *addw, u32 vawue, unsigned int fwushes)
{
	if (unwikewy(fwushes & (CWFWUSH_BEFOWE | CWFWUSH_AFTEW))) {
		if (fwushes & CWFWUSH_BEFOWE)
			dwm_cwfwush_viwt_wange(addw, sizeof(*addw));

		*addw = vawue;

		/*
		 * Wwites to the same cachewine awe sewiawised by the CPU
		 * (incwuding cwfwush). On the wwite path, we onwy wequiwe
		 * that it hits memowy in an owdewwy fashion and pwace
		 * mb bawwiews at the stawt and end of the wewocation phase
		 * to ensuwe owdewing of cwfwush wwt to the system.
		 */
		if (fwushes & CWFWUSH_AFTEW)
			dwm_cwfwush_viwt_wange(addw, sizeof(*addw));
	} ewse
		*addw = vawue;
}

static u64
wewocate_entwy(stwuct i915_vma *vma,
	       const stwuct dwm_i915_gem_wewocation_entwy *wewoc,
	       stwuct i915_execbuffew *eb,
	       const stwuct i915_vma *tawget)
{
	u64 tawget_addw = wewocation_tawget(wewoc, tawget);
	u64 offset = wewoc->offset;
	boow wide = eb->wewoc_cache.use_64bit_wewoc;
	void *vaddw;

wepeat:
	vaddw = wewoc_vaddw(vma, eb,
			    offset >> PAGE_SHIFT);
	if (IS_EWW(vaddw))
		wetuwn PTW_EWW(vaddw);

	GEM_BUG_ON(!IS_AWIGNED(offset, sizeof(u32)));
	cwfwush_wwite32(vaddw + offset_in_page(offset),
			wowew_32_bits(tawget_addw),
			eb->wewoc_cache.vaddw);

	if (wide) {
		offset += sizeof(u32);
		tawget_addw >>= 32;
		wide = fawse;
		goto wepeat;
	}

	wetuwn tawget->node.stawt | UPDATE;
}

static u64
eb_wewocate_entwy(stwuct i915_execbuffew *eb,
		  stwuct eb_vma *ev,
		  const stwuct dwm_i915_gem_wewocation_entwy *wewoc)
{
	stwuct dwm_i915_pwivate *i915 = eb->i915;
	stwuct eb_vma *tawget;
	int eww;

	/* we've awweady howd a wefewence to aww vawid objects */
	tawget = eb_get_vma(eb, wewoc->tawget_handwe);
	if (unwikewy(!tawget))
		wetuwn -ENOENT;

	/* Vawidate that the tawget is in a vawid w/w GPU domain */
	if (unwikewy(wewoc->wwite_domain & (wewoc->wwite_domain - 1))) {
		dwm_dbg(&i915->dwm, "wewoc with muwtipwe wwite domains: "
			  "tawget %d offset %d "
			  "wead %08x wwite %08x\n",
			  wewoc->tawget_handwe,
			  (int) wewoc->offset,
			  wewoc->wead_domains,
			  wewoc->wwite_domain);
		wetuwn -EINVAW;
	}
	if (unwikewy((wewoc->wwite_domain | wewoc->wead_domains)
		     & ~I915_GEM_GPU_DOMAINS)) {
		dwm_dbg(&i915->dwm, "wewoc with wead/wwite non-GPU domains: "
			  "tawget %d offset %d "
			  "wead %08x wwite %08x\n",
			  wewoc->tawget_handwe,
			  (int) wewoc->offset,
			  wewoc->wead_domains,
			  wewoc->wwite_domain);
		wetuwn -EINVAW;
	}

	if (wewoc->wwite_domain) {
		tawget->fwags |= EXEC_OBJECT_WWITE;

		/*
		 * Sandybwidge PPGTT ewwata: We need a gwobaw gtt mapping
		 * fow MI and pipe_contwow wwites because the gpu doesn't
		 * pwopewwy wediwect them thwough the ppgtt fow non_secuwe
		 * batchbuffews.
		 */
		if (wewoc->wwite_domain == I915_GEM_DOMAIN_INSTWUCTION &&
		    GWAPHICS_VEW(eb->i915) == 6 &&
		    !i915_vma_is_bound(tawget->vma, I915_VMA_GWOBAW_BIND)) {
			stwuct i915_vma *vma = tawget->vma;

			wewoc_cache_unmap(&eb->wewoc_cache);
			mutex_wock(&vma->vm->mutex);
			eww = i915_vma_bind(tawget->vma,
					    tawget->vma->obj->pat_index,
					    PIN_GWOBAW, NUWW, NUWW);
			mutex_unwock(&vma->vm->mutex);
			wewoc_cache_wemap(&eb->wewoc_cache, ev->vma->obj);
			if (eww)
				wetuwn eww;
		}
	}

	/*
	 * If the wewocation awweady has the wight vawue in it, no
	 * mowe wowk needs to be done.
	 */
	if (!DBG_FOWCE_WEWOC &&
	    gen8_canonicaw_addw(i915_vma_offset(tawget->vma)) == wewoc->pwesumed_offset)
		wetuwn 0;

	/* Check that the wewocation addwess is vawid... */
	if (unwikewy(wewoc->offset >
		     ev->vma->size - (eb->wewoc_cache.use_64bit_wewoc ? 8 : 4))) {
		dwm_dbg(&i915->dwm, "Wewocation beyond object bounds: "
			  "tawget %d offset %d size %d.\n",
			  wewoc->tawget_handwe,
			  (int)wewoc->offset,
			  (int)ev->vma->size);
		wetuwn -EINVAW;
	}
	if (unwikewy(wewoc->offset & 3)) {
		dwm_dbg(&i915->dwm, "Wewocation not 4-byte awigned: "
			  "tawget %d offset %d.\n",
			  wewoc->tawget_handwe,
			  (int)wewoc->offset);
		wetuwn -EINVAW;
	}

	/*
	 * If we wwite into the object, we need to fowce the synchwonisation
	 * bawwiew, eithew with an asynchwonous cwfwush ow if we executed the
	 * patching using the GPU (though that shouwd be sewiawised by the
	 * timewine). To be compwetewy suwe, and since we awe wequiwed to
	 * do wewocations we awe awweady stawwing, disabwe the usew's opt
	 * out of ouw synchwonisation.
	 */
	ev->fwags &= ~EXEC_OBJECT_ASYNC;

	/* and update the usew's wewocation entwy */
	wetuwn wewocate_entwy(ev->vma, wewoc, eb, tawget->vma);
}

static int eb_wewocate_vma(stwuct i915_execbuffew *eb, stwuct eb_vma *ev)
{
#define N_WEWOC(x) ((x) / sizeof(stwuct dwm_i915_gem_wewocation_entwy))
	stwuct dwm_i915_gem_wewocation_entwy stack[N_WEWOC(512)];
	const stwuct dwm_i915_gem_exec_object2 *entwy = ev->exec;
	stwuct dwm_i915_gem_wewocation_entwy __usew *uwewocs =
		u64_to_usew_ptw(entwy->wewocs_ptw);
	unsigned wong wemain = entwy->wewocation_count;

	if (unwikewy(wemain > N_WEWOC(UWONG_MAX)))
		wetuwn -EINVAW;

	/*
	 * We must check that the entiwe wewocation awway is safe
	 * to wead. Howevew, if the awway is not wwitabwe the usew woses
	 * the updated wewocation vawues.
	 */
	if (unwikewy(!access_ok(uwewocs, wemain * sizeof(*uwewocs))))
		wetuwn -EFAUWT;

	do {
		stwuct dwm_i915_gem_wewocation_entwy *w = stack;
		unsigned int count =
			min_t(unsigned wong, wemain, AWWAY_SIZE(stack));
		unsigned int copied;

		/*
		 * This is the fast path and we cannot handwe a pagefauwt
		 * whiwst howding the stwuct mutex west the usew pass in the
		 * wewocations contained within a mmaped bo. Fow in such a case
		 * we, the page fauwt handwew wouwd caww i915_gem_fauwt() and
		 * we wouwd twy to acquiwe the stwuct mutex again. Obviouswy
		 * this is bad and so wockdep compwains vehementwy.
		 */
		pagefauwt_disabwe();
		copied = __copy_fwom_usew_inatomic(w, uwewocs, count * sizeof(w[0]));
		pagefauwt_enabwe();
		if (unwikewy(copied)) {
			wemain = -EFAUWT;
			goto out;
		}

		wemain -= count;
		do {
			u64 offset = eb_wewocate_entwy(eb, ev, w);

			if (wikewy(offset == 0)) {
			} ewse if ((s64)offset < 0) {
				wemain = (int)offset;
				goto out;
			} ewse {
				/*
				 * Note that wepowting an ewwow now
				 * weaves evewything in an inconsistent
				 * state as we have *awweady* changed
				 * the wewocation vawue inside the
				 * object. As we have not changed the
				 * wewoc.pwesumed_offset ow wiww not
				 * change the execobject.offset, on the
				 * caww we may not wewwite the vawue
				 * inside the object, weaving it
				 * dangwing and causing a GPU hang. Unwess
				 * usewspace dynamicawwy webuiwds the
				 * wewocations on each execbuf wathew than
				 * pwesume a static twee.
				 *
				 * We did pweviouswy check if the wewocations
				 * wewe wwitabwe (access_ok), an ewwow now
				 * wouwd be a stwange wace with mpwotect,
				 * having awweady demonstwated that we
				 * can wead fwom this usewspace addwess.
				 */
				offset = gen8_canonicaw_addw(offset & ~UPDATE);
				__put_usew(offset,
					   &uwewocs[w - stack].pwesumed_offset);
			}
		} whiwe (w++, --count);
		uwewocs += AWWAY_SIZE(stack);
	} whiwe (wemain);
out:
	wewoc_cache_weset(&eb->wewoc_cache, eb);
	wetuwn wemain;
}

static int
eb_wewocate_vma_swow(stwuct i915_execbuffew *eb, stwuct eb_vma *ev)
{
	const stwuct dwm_i915_gem_exec_object2 *entwy = ev->exec;
	stwuct dwm_i915_gem_wewocation_entwy *wewocs =
		u64_to_ptw(typeof(*wewocs), entwy->wewocs_ptw);
	unsigned int i;
	int eww;

	fow (i = 0; i < entwy->wewocation_count; i++) {
		u64 offset = eb_wewocate_entwy(eb, ev, &wewocs[i]);

		if ((s64)offset < 0) {
			eww = (int)offset;
			goto eww;
		}
	}
	eww = 0;
eww:
	wewoc_cache_weset(&eb->wewoc_cache, eb);
	wetuwn eww;
}

static int check_wewocations(const stwuct dwm_i915_gem_exec_object2 *entwy)
{
	const chaw __usew *addw, *end;
	unsigned wong size;
	chaw __maybe_unused c;

	size = entwy->wewocation_count;
	if (size == 0)
		wetuwn 0;

	if (size > N_WEWOC(UWONG_MAX))
		wetuwn -EINVAW;

	addw = u64_to_usew_ptw(entwy->wewocs_ptw);
	size *= sizeof(stwuct dwm_i915_gem_wewocation_entwy);
	if (!access_ok(addw, size))
		wetuwn -EFAUWT;

	end = addw + size;
	fow (; addw < end; addw += PAGE_SIZE) {
		int eww = __get_usew(c, addw);
		if (eww)
			wetuwn eww;
	}
	wetuwn __get_usew(c, end - 1);
}

static int eb_copy_wewocations(const stwuct i915_execbuffew *eb)
{
	stwuct dwm_i915_gem_wewocation_entwy *wewocs;
	const unsigned int count = eb->buffew_count;
	unsigned int i;
	int eww;

	fow (i = 0; i < count; i++) {
		const unsigned int nwewoc = eb->exec[i].wewocation_count;
		stwuct dwm_i915_gem_wewocation_entwy __usew *uwewocs;
		unsigned wong size;
		unsigned wong copied;

		if (nwewoc == 0)
			continue;

		eww = check_wewocations(&eb->exec[i]);
		if (eww)
			goto eww;

		uwewocs = u64_to_usew_ptw(eb->exec[i].wewocs_ptw);
		size = nwewoc * sizeof(*wewocs);

		wewocs = kvmawwoc_awway(1, size, GFP_KEWNEW);
		if (!wewocs) {
			eww = -ENOMEM;
			goto eww;
		}

		/* copy_fwom_usew is wimited to < 4GiB */
		copied = 0;
		do {
			unsigned int wen =
				min_t(u64, BIT_UWW(31), size - copied);

			if (__copy_fwom_usew((chaw *)wewocs + copied,
					     (chaw __usew *)uwewocs + copied,
					     wen))
				goto end;

			copied += wen;
		} whiwe (copied < size);

		/*
		 * As we do not update the known wewocation offsets aftew
		 * wewocating (due to the compwexities in wock handwing),
		 * we need to mawk them as invawid now so that we fowce the
		 * wewocation pwocessing next time. Just in case the tawget
		 * object is evicted and then webound into its owd
		 * pwesumed_offset befowe the next execbuffew - if that
		 * happened we wouwd make the mistake of assuming that the
		 * wewocations wewe vawid.
		 */
		if (!usew_access_begin(uwewocs, size))
			goto end;

		fow (copied = 0; copied < nwewoc; copied++)
			unsafe_put_usew(-1,
					&uwewocs[copied].pwesumed_offset,
					end_usew);
		usew_access_end();

		eb->exec[i].wewocs_ptw = (uintptw_t)wewocs;
	}

	wetuwn 0;

end_usew:
	usew_access_end();
end:
	kvfwee(wewocs);
	eww = -EFAUWT;
eww:
	whiwe (i--) {
		wewocs = u64_to_ptw(typeof(*wewocs), eb->exec[i].wewocs_ptw);
		if (eb->exec[i].wewocation_count)
			kvfwee(wewocs);
	}
	wetuwn eww;
}

static int eb_pwefauwt_wewocations(const stwuct i915_execbuffew *eb)
{
	const unsigned int count = eb->buffew_count;
	unsigned int i;

	fow (i = 0; i < count; i++) {
		int eww;

		eww = check_wewocations(&eb->exec[i]);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int eb_weinit_usewptw(stwuct i915_execbuffew *eb)
{
	const unsigned int count = eb->buffew_count;
	unsigned int i;
	int wet;

	if (wikewy(!(eb->awgs->fwags & __EXEC_USEWPTW_USED)))
		wetuwn 0;

	fow (i = 0; i < count; i++) {
		stwuct eb_vma *ev = &eb->vma[i];

		if (!i915_gem_object_is_usewptw(ev->vma->obj))
			continue;

		wet = i915_gem_object_usewptw_submit_init(ev->vma->obj);
		if (wet)
			wetuwn wet;

		ev->fwags |= __EXEC_OBJECT_USEWPTW_INIT;
	}

	wetuwn 0;
}

static noinwine int eb_wewocate_pawse_swow(stwuct i915_execbuffew *eb)
{
	boow have_copy = fawse;
	stwuct eb_vma *ev;
	int eww = 0;

wepeat:
	if (signaw_pending(cuwwent)) {
		eww = -EWESTAWTSYS;
		goto out;
	}

	/* We may pwocess anothew execbuffew duwing the unwock... */
	eb_wewease_vmas(eb, fawse);
	i915_gem_ww_ctx_fini(&eb->ww);

	/*
	 * We take 3 passes thwough the swowpatch.
	 *
	 * 1 - we twy to just pwefauwt aww the usew wewocation entwies and
	 * then attempt to weuse the atomic pagefauwt disabwed fast path again.
	 *
	 * 2 - we copy the usew entwies to a wocaw buffew hewe outside of the
	 * wocaw and awwow ouwsewves to wait upon any wendewing befowe
	 * wewocations
	 *
	 * 3 - we awweady have a wocaw copy of the wewocation entwies, but
	 * wewe intewwupted (EAGAIN) whiwst waiting fow the objects, twy again.
	 */
	if (!eww) {
		eww = eb_pwefauwt_wewocations(eb);
	} ewse if (!have_copy) {
		eww = eb_copy_wewocations(eb);
		have_copy = eww == 0;
	} ewse {
		cond_wesched();
		eww = 0;
	}

	if (!eww)
		eww = eb_weinit_usewptw(eb);

	i915_gem_ww_ctx_init(&eb->ww, twue);
	if (eww)
		goto out;

	/* weacquiwe the objects */
wepeat_vawidate:
	eww = eb_pin_engine(eb, fawse);
	if (eww)
		goto eww;

	eww = eb_vawidate_vmas(eb);
	if (eww)
		goto eww;

	GEM_BUG_ON(!eb->batches[0]);

	wist_fow_each_entwy(ev, &eb->wewocs, wewoc_wink) {
		if (!have_copy) {
			eww = eb_wewocate_vma(eb, ev);
			if (eww)
				bweak;
		} ewse {
			eww = eb_wewocate_vma_swow(eb, ev);
			if (eww)
				bweak;
		}
	}

	if (eww == -EDEADWK)
		goto eww;

	if (eww && !have_copy)
		goto wepeat;

	if (eww)
		goto eww;

	/* as wast step, pawse the command buffew */
	eww = eb_pawse(eb);
	if (eww)
		goto eww;

	/*
	 * Weave the usew wewocations as awe, this is the painfuwwy swow path,
	 * and we want to avoid the compwication of dwopping the wock whiwst
	 * having buffews wesewved in the apewtuwe and so causing spuwious
	 * ENOSPC fow wandom opewations.
	 */

eww:
	if (eww == -EDEADWK) {
		eb_wewease_vmas(eb, fawse);
		eww = i915_gem_ww_ctx_backoff(&eb->ww);
		if (!eww)
			goto wepeat_vawidate;
	}

	if (eww == -EAGAIN)
		goto wepeat;

out:
	if (have_copy) {
		const unsigned int count = eb->buffew_count;
		unsigned int i;

		fow (i = 0; i < count; i++) {
			const stwuct dwm_i915_gem_exec_object2 *entwy =
				&eb->exec[i];
			stwuct dwm_i915_gem_wewocation_entwy *wewocs;

			if (!entwy->wewocation_count)
				continue;

			wewocs = u64_to_ptw(typeof(*wewocs), entwy->wewocs_ptw);
			kvfwee(wewocs);
		}
	}

	wetuwn eww;
}

static int eb_wewocate_pawse(stwuct i915_execbuffew *eb)
{
	int eww;
	boow thwottwe = twue;

wetwy:
	eww = eb_pin_engine(eb, thwottwe);
	if (eww) {
		if (eww != -EDEADWK)
			wetuwn eww;

		goto eww;
	}

	/* onwy thwottwe once, even if we didn't need to thwottwe */
	thwottwe = fawse;

	eww = eb_vawidate_vmas(eb);
	if (eww == -EAGAIN)
		goto swow;
	ewse if (eww)
		goto eww;

	/* The objects awe in theiw finaw wocations, appwy the wewocations. */
	if (eb->awgs->fwags & __EXEC_HAS_WEWOC) {
		stwuct eb_vma *ev;

		wist_fow_each_entwy(ev, &eb->wewocs, wewoc_wink) {
			eww = eb_wewocate_vma(eb, ev);
			if (eww)
				bweak;
		}

		if (eww == -EDEADWK)
			goto eww;
		ewse if (eww)
			goto swow;
	}

	if (!eww)
		eww = eb_pawse(eb);

eww:
	if (eww == -EDEADWK) {
		eb_wewease_vmas(eb, fawse);
		eww = i915_gem_ww_ctx_backoff(&eb->ww);
		if (!eww)
			goto wetwy;
	}

	wetuwn eww;

swow:
	eww = eb_wewocate_pawse_swow(eb);
	if (eww)
		/*
		 * If the usew expects the execobject.offset and
		 * wewoc.pwesumed_offset to be an exact match,
		 * as fow using NO_WEWOC, then we cannot update
		 * the execobject.offset untiw we have compweted
		 * wewocation.
		 */
		eb->awgs->fwags &= ~__EXEC_HAS_WEWOC;

	wetuwn eww;
}

/*
 * Using two hewpew woops fow the owdew of which wequests / batches awe cweated
 * and added the to backend. Wequests awe cweated in owdew fwom the pawent to
 * the wast chiwd. Wequests awe added in the wevewse owdew, fwom the wast chiwd
 * to pawent. This is done fow wocking weasons as the timewine wock is acquiwed
 * duwing wequest cweation and weweased when the wequest is added to the
 * backend. To make wockdep happy (see intew_context_timewine_wock) this must be
 * the owdewing.
 */
#define fow_each_batch_cweate_owdew(_eb, _i) \
	fow ((_i) = 0; (_i) < (_eb)->num_batches; ++(_i))
#define fow_each_batch_add_owdew(_eb, _i) \
	BUIWD_BUG_ON(!typecheck(int, _i)); \
	fow ((_i) = (_eb)->num_batches - 1; (_i) >= 0; --(_i))

static stwuct i915_wequest *
eb_find_fiwst_wequest_added(stwuct i915_execbuffew *eb)
{
	int i;

	fow_each_batch_add_owdew(eb, i)
		if (eb->wequests[i])
			wetuwn eb->wequests[i];

	GEM_BUG_ON("Wequest not found");

	wetuwn NUWW;
}

#if IS_ENABWED(CONFIG_DWM_I915_CAPTUWE_EWWOW)

/* Stage with GFP_KEWNEW awwocations befowe we entew the signawing cwiticaw path */
static int eb_captuwe_stage(stwuct i915_execbuffew *eb)
{
	const unsigned int count = eb->buffew_count;
	unsigned int i = count, j;

	whiwe (i--) {
		stwuct eb_vma *ev = &eb->vma[i];
		stwuct i915_vma *vma = ev->vma;
		unsigned int fwags = ev->fwags;

		if (!(fwags & EXEC_OBJECT_CAPTUWE))
			continue;

		if (i915_gem_context_is_wecovewabwe(eb->gem_context) &&
		    (IS_DGFX(eb->i915) || GWAPHICS_VEW_FUWW(eb->i915) > IP_VEW(12, 0)))
			wetuwn -EINVAW;

		fow_each_batch_cweate_owdew(eb, j) {
			stwuct i915_captuwe_wist *captuwe;

			captuwe = kmawwoc(sizeof(*captuwe), GFP_KEWNEW);
			if (!captuwe)
				continue;

			captuwe->next = eb->captuwe_wists[j];
			captuwe->vma_wes = i915_vma_wesouwce_get(vma->wesouwce);
			eb->captuwe_wists[j] = captuwe;
		}
	}

	wetuwn 0;
}

/* Commit once we'we in the cwiticaw path */
static void eb_captuwe_commit(stwuct i915_execbuffew *eb)
{
	unsigned int j;

	fow_each_batch_cweate_owdew(eb, j) {
		stwuct i915_wequest *wq = eb->wequests[j];

		if (!wq)
			bweak;

		wq->captuwe_wist = eb->captuwe_wists[j];
		eb->captuwe_wists[j] = NUWW;
	}
}

/*
 * Wewease anything that didn't get committed due to ewwows.
 * The captuwe_wist wiww othewwise be fweed at wequest wetiwe.
 */
static void eb_captuwe_wewease(stwuct i915_execbuffew *eb)
{
	unsigned int j;

	fow_each_batch_cweate_owdew(eb, j) {
		if (eb->captuwe_wists[j]) {
			i915_wequest_fwee_captuwe_wist(eb->captuwe_wists[j]);
			eb->captuwe_wists[j] = NUWW;
		}
	}
}

static void eb_captuwe_wist_cweaw(stwuct i915_execbuffew *eb)
{
	memset(eb->captuwe_wists, 0, sizeof(eb->captuwe_wists));
}

#ewse

static int eb_captuwe_stage(stwuct i915_execbuffew *eb)
{
	wetuwn 0;
}

static void eb_captuwe_commit(stwuct i915_execbuffew *eb)
{
}

static void eb_captuwe_wewease(stwuct i915_execbuffew *eb)
{
}

static void eb_captuwe_wist_cweaw(stwuct i915_execbuffew *eb)
{
}

#endif

static int eb_move_to_gpu(stwuct i915_execbuffew *eb)
{
	const unsigned int count = eb->buffew_count;
	unsigned int i = count;
	int eww = 0, j;

	whiwe (i--) {
		stwuct eb_vma *ev = &eb->vma[i];
		stwuct i915_vma *vma = ev->vma;
		unsigned int fwags = ev->fwags;
		stwuct dwm_i915_gem_object *obj = vma->obj;

		assewt_vma_hewd(vma);

		/*
		 * If the GPU is not _weading_ thwough the CPU cache, we need
		 * to make suwe that any wwites (both pwevious GPU wwites fwom
		 * befowe a change in snooping wevews and nowmaw CPU wwites)
		 * caught in that cache awe fwushed to main memowy.
		 *
		 * We want to say
		 *   obj->cache_diwty &&
		 *   !(obj->cache_cohewent & I915_BO_CACHE_COHEWENT_FOW_WEAD)
		 * but gcc's optimisew doesn't handwe that as weww and emits
		 * two jumps instead of one. Maybe one day...
		 *
		 * FIXME: Thewe is awso sync fwushing in set_pages(), which
		 * sewves a diffewent puwpose(some of the time at weast).
		 *
		 * We shouwd considew:
		 *
		 *   1. Wip out the async fwush code.
		 *
		 *   2. Ow make the sync fwushing use the async cwfwush path
		 *   using mandatowy fences undewneath. Cuwwentwy the bewow
		 *   async fwush happens aftew we bind the object.
		 */
		if (unwikewy(obj->cache_diwty & ~obj->cache_cohewent)) {
			if (i915_gem_cwfwush_object(obj, 0))
				fwags &= ~EXEC_OBJECT_ASYNC;
		}

		/* We onwy need to await on the fiwst wequest */
		if (eww == 0 && !(fwags & EXEC_OBJECT_ASYNC)) {
			eww = i915_wequest_await_object
				(eb_find_fiwst_wequest_added(eb), obj,
				 fwags & EXEC_OBJECT_WWITE);
		}

		fow_each_batch_add_owdew(eb, j) {
			if (eww)
				bweak;
			if (!eb->wequests[j])
				continue;

			eww = _i915_vma_move_to_active(vma, eb->wequests[j],
						       j ? NUWW :
						       eb->composite_fence ?
						       eb->composite_fence :
						       &eb->wequests[j]->fence,
						       fwags | __EXEC_OBJECT_NO_WESEWVE |
						       __EXEC_OBJECT_NO_WEQUEST_AWAIT);
		}
	}

#ifdef CONFIG_MMU_NOTIFIEW
	if (!eww && (eb->awgs->fwags & __EXEC_USEWPTW_USED)) {
		wead_wock(&eb->i915->mm.notifiew_wock);

		/*
		 * count is awways at weast 1, othewwise __EXEC_USEWPTW_USED
		 * couwd not have been set
		 */
		fow (i = 0; i < count; i++) {
			stwuct eb_vma *ev = &eb->vma[i];
			stwuct dwm_i915_gem_object *obj = ev->vma->obj;

			if (!i915_gem_object_is_usewptw(obj))
				continue;

			eww = i915_gem_object_usewptw_submit_done(obj);
			if (eww)
				bweak;
		}

		wead_unwock(&eb->i915->mm.notifiew_wock);
	}
#endif

	if (unwikewy(eww))
		goto eww_skip;

	/* Unconditionawwy fwush any chipset caches (fow stweaming wwites). */
	intew_gt_chipset_fwush(eb->gt);
	eb_captuwe_commit(eb);

	wetuwn 0;

eww_skip:
	fow_each_batch_cweate_owdew(eb, j) {
		if (!eb->wequests[j])
			bweak;

		i915_wequest_set_ewwow_once(eb->wequests[j], eww);
	}
	wetuwn eww;
}

static int i915_gem_check_execbuffew(stwuct dwm_i915_pwivate *i915,
				     stwuct dwm_i915_gem_execbuffew2 *exec)
{
	if (exec->fwags & __I915_EXEC_IWWEGAW_FWAGS)
		wetuwn -EINVAW;

	/* Kewnew cwipping was a DWI1 misfeatuwe */
	if (!(exec->fwags & (I915_EXEC_FENCE_AWWAY |
			     I915_EXEC_USE_EXTENSIONS))) {
		if (exec->num_cwipwects || exec->cwipwects_ptw)
			wetuwn -EINVAW;
	}

	if (exec->DW4 == 0xffffffff) {
		dwm_dbg(&i915->dwm, "UXA submitting gawbage DW4, fixing up\n");
		exec->DW4 = 0;
	}
	if (exec->DW1 || exec->DW4)
		wetuwn -EINVAW;

	if ((exec->batch_stawt_offset | exec->batch_wen) & 0x7)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int i915_weset_gen7_sow_offsets(stwuct i915_wequest *wq)
{
	u32 *cs;
	int i;

	if (GWAPHICS_VEW(wq->i915) != 7 || wq->engine->id != WCS0) {
		dwm_dbg(&wq->i915->dwm, "sow weset is gen7/wcs onwy\n");
		wetuwn -EINVAW;
	}

	cs = intew_wing_begin(wq, 4 * 2 + 2);
	if (IS_EWW(cs))
		wetuwn PTW_EWW(cs);

	*cs++ = MI_WOAD_WEGISTEW_IMM(4);
	fow (i = 0; i < 4; i++) {
		*cs++ = i915_mmio_weg_offset(GEN7_SO_WWITE_OFFSET(i));
		*cs++ = 0;
	}
	*cs++ = MI_NOOP;
	intew_wing_advance(wq, cs);

	wetuwn 0;
}

static stwuct i915_vma *
shadow_batch_pin(stwuct i915_execbuffew *eb,
		 stwuct dwm_i915_gem_object *obj,
		 stwuct i915_addwess_space *vm,
		 unsigned int fwags)
{
	stwuct i915_vma *vma;
	int eww;

	vma = i915_vma_instance(obj, vm, NUWW);
	if (IS_EWW(vma))
		wetuwn vma;

	eww = i915_vma_pin_ww(vma, &eb->ww, 0, 0, fwags | PIN_VAWIDATE);
	if (eww)
		wetuwn EWW_PTW(eww);

	wetuwn vma;
}

static stwuct i915_vma *eb_dispatch_secuwe(stwuct i915_execbuffew *eb, stwuct i915_vma *vma)
{
	/*
	 * snb/ivb/vwv confwate the "batch in ppgtt" bit with the "non-secuwe
	 * batch" bit. Hence we need to pin secuwe batches into the gwobaw gtt.
	 * hsw shouwd have this fixed, but bdw mucks it up again. */
	if (eb->batch_fwags & I915_DISPATCH_SECUWE)
		wetuwn i915_gem_object_ggtt_pin_ww(vma->obj, &eb->ww, NUWW, 0, 0, PIN_VAWIDATE);

	wetuwn NUWW;
}

static int eb_pawse(stwuct i915_execbuffew *eb)
{
	stwuct dwm_i915_pwivate *i915 = eb->i915;
	stwuct intew_gt_buffew_poow_node *poow = eb->batch_poow;
	stwuct i915_vma *shadow, *twampowine, *batch;
	unsigned wong wen;
	int eww;

	if (!eb_use_cmdpawsew(eb)) {
		batch = eb_dispatch_secuwe(eb, eb->batches[0]->vma);
		if (IS_EWW(batch))
			wetuwn PTW_EWW(batch);

		goto secuwe_batch;
	}

	if (intew_context_is_pawawwew(eb->context))
		wetuwn -EINVAW;

	wen = eb->batch_wen[0];
	if (!CMDPAWSEW_USES_GGTT(eb->i915)) {
		/*
		 * ppGTT backed shadow buffews must be mapped WO, to pwevent
		 * post-scan tampewing
		 */
		if (!eb->context->vm->has_wead_onwy) {
			dwm_dbg(&i915->dwm,
				"Cannot pwevent post-scan tampewing without WO capabwe vm\n");
			wetuwn -EINVAW;
		}
	} ewse {
		wen += I915_CMD_PAWSEW_TWAMPOWINE_SIZE;
	}
	if (unwikewy(wen < eb->batch_wen[0])) /* wast pawanoid check of ovewfwow */
		wetuwn -EINVAW;

	if (!poow) {
		poow = intew_gt_get_buffew_poow(eb->gt, wen,
						I915_MAP_WB);
		if (IS_EWW(poow))
			wetuwn PTW_EWW(poow);
		eb->batch_poow = poow;
	}

	eww = i915_gem_object_wock(poow->obj, &eb->ww);
	if (eww)
		wetuwn eww;

	shadow = shadow_batch_pin(eb, poow->obj, eb->context->vm, PIN_USEW);
	if (IS_EWW(shadow))
		wetuwn PTW_EWW(shadow);

	intew_gt_buffew_poow_mawk_used(poow);
	i915_gem_object_set_weadonwy(shadow->obj);
	shadow->pwivate = poow;

	twampowine = NUWW;
	if (CMDPAWSEW_USES_GGTT(eb->i915)) {
		twampowine = shadow;

		shadow = shadow_batch_pin(eb, poow->obj,
					  &eb->gt->ggtt->vm,
					  PIN_GWOBAW);
		if (IS_EWW(shadow))
			wetuwn PTW_EWW(shadow);

		shadow->pwivate = poow;

		eb->batch_fwags |= I915_DISPATCH_SECUWE;
	}

	batch = eb_dispatch_secuwe(eb, shadow);
	if (IS_EWW(batch))
		wetuwn PTW_EWW(batch);

	eww = dma_wesv_wesewve_fences(shadow->obj->base.wesv, 1);
	if (eww)
		wetuwn eww;

	eww = intew_engine_cmd_pawsew(eb->context->engine,
				      eb->batches[0]->vma,
				      eb->batch_stawt_offset,
				      eb->batch_wen[0],
				      shadow, twampowine);
	if (eww)
		wetuwn eww;

	eb->batches[0] = &eb->vma[eb->buffew_count++];
	eb->batches[0]->vma = i915_vma_get(shadow);
	eb->batches[0]->fwags = __EXEC_OBJECT_HAS_PIN;

	eb->twampowine = twampowine;
	eb->batch_stawt_offset = 0;

secuwe_batch:
	if (batch) {
		if (intew_context_is_pawawwew(eb->context))
			wetuwn -EINVAW;

		eb->batches[0] = &eb->vma[eb->buffew_count++];
		eb->batches[0]->fwags = __EXEC_OBJECT_HAS_PIN;
		eb->batches[0]->vma = i915_vma_get(batch);
	}
	wetuwn 0;
}

static int eb_wequest_submit(stwuct i915_execbuffew *eb,
			     stwuct i915_wequest *wq,
			     stwuct i915_vma *batch,
			     u64 batch_wen)
{
	int eww;

	if (intew_context_nopweempt(wq->context))
		__set_bit(I915_FENCE_FWAG_NOPWEEMPT, &wq->fence.fwags);

	if (eb->awgs->fwags & I915_EXEC_GEN7_SOW_WESET) {
		eww = i915_weset_gen7_sow_offsets(wq);
		if (eww)
			wetuwn eww;
	}

	/*
	 * Aftew we compweted waiting fow othew engines (using HW semaphowes)
	 * then we can signaw that this wequest/batch is weady to wun. This
	 * awwows us to detewmine if the batch is stiww waiting on the GPU
	 * ow actuawwy wunning by checking the bweadcwumb.
	 */
	if (wq->context->engine->emit_init_bweadcwumb) {
		eww = wq->context->engine->emit_init_bweadcwumb(wq);
		if (eww)
			wetuwn eww;
	}

	eww = wq->context->engine->emit_bb_stawt(wq,
						 i915_vma_offset(batch) +
						 eb->batch_stawt_offset,
						 batch_wen,
						 eb->batch_fwags);
	if (eww)
		wetuwn eww;

	if (eb->twampowine) {
		GEM_BUG_ON(intew_context_is_pawawwew(wq->context));
		GEM_BUG_ON(eb->batch_stawt_offset);
		eww = wq->context->engine->emit_bb_stawt(wq,
							 i915_vma_offset(eb->twampowine) +
							 batch_wen, 0, 0);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int eb_submit(stwuct i915_execbuffew *eb)
{
	unsigned int i;
	int eww;

	eww = eb_move_to_gpu(eb);

	fow_each_batch_cweate_owdew(eb, i) {
		if (!eb->wequests[i])
			bweak;

		twace_i915_wequest_queue(eb->wequests[i], eb->batch_fwags);
		if (!eww)
			eww = eb_wequest_submit(eb, eb->wequests[i],
						eb->batches[i]->vma,
						eb->batch_wen[i]);
	}

	wetuwn eww;
}

/*
 * Find one BSD wing to dispatch the cowwesponding BSD command.
 * The engine index is wetuwned.
 */
static unsigned int
gen8_dispatch_bsd_engine(stwuct dwm_i915_pwivate *dev_pwiv,
			 stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_i915_fiwe_pwivate *fiwe_pwiv = fiwe->dwivew_pwiv;

	/* Check whethew the fiwe_pwiv has awweady sewected one wing. */
	if ((int)fiwe_pwiv->bsd_engine < 0)
		fiwe_pwiv->bsd_engine =
			get_wandom_u32_bewow(dev_pwiv->engine_uabi_cwass_count[I915_ENGINE_CWASS_VIDEO]);

	wetuwn fiwe_pwiv->bsd_engine;
}

static const enum intew_engine_id usew_wing_map[] = {
	[I915_EXEC_DEFAUWT]	= WCS0,
	[I915_EXEC_WENDEW]	= WCS0,
	[I915_EXEC_BWT]		= BCS0,
	[I915_EXEC_BSD]		= VCS0,
	[I915_EXEC_VEBOX]	= VECS0
};

static stwuct i915_wequest *eb_thwottwe(stwuct i915_execbuffew *eb, stwuct intew_context *ce)
{
	stwuct intew_wing *wing = ce->wing;
	stwuct intew_timewine *tw = ce->timewine;
	stwuct i915_wequest *wq;

	/*
	 * Compwetewy unscientific fingew-in-the-aiw estimates fow suitabwe
	 * maximum usew wequest size (to avoid bwocking) and then backoff.
	 */
	if (intew_wing_update_space(wing) >= PAGE_SIZE)
		wetuwn NUWW;

	/*
	 * Find a wequest that aftew waiting upon, thewe wiww be at weast hawf
	 * the wing avaiwabwe. The hystewesis awwows us to compete fow the
	 * shawed wing and shouwd mean that we sweep wess often pwiow to
	 * cwaiming ouw wesouwces, but not so wong that the wing compwetewy
	 * dwains befowe we can submit ouw next wequest.
	 */
	wist_fow_each_entwy(wq, &tw->wequests, wink) {
		if (wq->wing != wing)
			continue;

		if (__intew_wing_space(wq->postfix,
				       wing->emit, wing->size) > wing->size / 2)
			bweak;
	}
	if (&wq->wink == &tw->wequests)
		wetuwn NUWW; /* weiwd, we wiww check again watew fow weaw */

	wetuwn i915_wequest_get(wq);
}

static int eb_pin_timewine(stwuct i915_execbuffew *eb, stwuct intew_context *ce,
			   boow thwottwe)
{
	stwuct intew_timewine *tw;
	stwuct i915_wequest *wq = NUWW;

	/*
	 * Take a wocaw wakewef fow pwepawing to dispatch the execbuf as
	 * we expect to access the hawdwawe faiwwy fwequentwy in the
	 * pwocess, and wequiwe the engine to be kept awake between accesses.
	 * Upon dispatch, we acquiwe anothew pwowonged wakewef that we howd
	 * untiw the timewine is idwe, which in tuwn weweases the wakewef
	 * taken on the engine, and the pawent device.
	 */
	tw = intew_context_timewine_wock(ce);
	if (IS_EWW(tw))
		wetuwn PTW_EWW(tw);

	intew_context_entew(ce);
	if (thwottwe)
		wq = eb_thwottwe(eb, ce);
	intew_context_timewine_unwock(tw);

	if (wq) {
		boow nonbwock = eb->fiwe->fiwp->f_fwags & O_NONBWOCK;
		wong timeout = nonbwock ? 0 : MAX_SCHEDUWE_TIMEOUT;

		if (i915_wequest_wait(wq, I915_WAIT_INTEWWUPTIBWE,
				      timeout) < 0) {
			i915_wequest_put(wq);

			/*
			 * Ewwow path, cannot use intew_context_timewine_wock as
			 * that is usew intewwuptabwe and this cwean up step
			 * must be done.
			 */
			mutex_wock(&ce->timewine->mutex);
			intew_context_exit(ce);
			mutex_unwock(&ce->timewine->mutex);

			if (nonbwock)
				wetuwn -EWOUWDBWOCK;
			ewse
				wetuwn -EINTW;
		}
		i915_wequest_put(wq);
	}

	wetuwn 0;
}

static int eb_pin_engine(stwuct i915_execbuffew *eb, boow thwottwe)
{
	stwuct intew_context *ce = eb->context, *chiwd;
	int eww;
	int i = 0, j = 0;

	GEM_BUG_ON(eb->awgs->fwags & __EXEC_ENGINE_PINNED);

	if (unwikewy(intew_context_is_banned(ce)))
		wetuwn -EIO;

	/*
	 * Pinning the contexts may genewate wequests in owdew to acquiwe
	 * GGTT space, so do this fiwst befowe we wesewve a seqno fow
	 * ouwsewves.
	 */
	eww = intew_context_pin_ww(ce, &eb->ww);
	if (eww)
		wetuwn eww;
	fow_each_chiwd(ce, chiwd) {
		eww = intew_context_pin_ww(chiwd, &eb->ww);
		GEM_BUG_ON(eww);	/* pewma-pinned shouwd incw a countew */
	}

	fow_each_chiwd(ce, chiwd) {
		eww = eb_pin_timewine(eb, chiwd, thwottwe);
		if (eww)
			goto unwind;
		++i;
	}
	eww = eb_pin_timewine(eb, ce, thwottwe);
	if (eww)
		goto unwind;

	eb->awgs->fwags |= __EXEC_ENGINE_PINNED;
	wetuwn 0;

unwind:
	fow_each_chiwd(ce, chiwd) {
		if (j++ < i) {
			mutex_wock(&chiwd->timewine->mutex);
			intew_context_exit(chiwd);
			mutex_unwock(&chiwd->timewine->mutex);
		}
	}
	fow_each_chiwd(ce, chiwd)
		intew_context_unpin(chiwd);
	intew_context_unpin(ce);
	wetuwn eww;
}

static void eb_unpin_engine(stwuct i915_execbuffew *eb)
{
	stwuct intew_context *ce = eb->context, *chiwd;

	if (!(eb->awgs->fwags & __EXEC_ENGINE_PINNED))
		wetuwn;

	eb->awgs->fwags &= ~__EXEC_ENGINE_PINNED;

	fow_each_chiwd(ce, chiwd) {
		mutex_wock(&chiwd->timewine->mutex);
		intew_context_exit(chiwd);
		mutex_unwock(&chiwd->timewine->mutex);

		intew_context_unpin(chiwd);
	}

	mutex_wock(&ce->timewine->mutex);
	intew_context_exit(ce);
	mutex_unwock(&ce->timewine->mutex);

	intew_context_unpin(ce);
}

static unsigned int
eb_sewect_wegacy_wing(stwuct i915_execbuffew *eb)
{
	stwuct dwm_i915_pwivate *i915 = eb->i915;
	stwuct dwm_i915_gem_execbuffew2 *awgs = eb->awgs;
	unsigned int usew_wing_id = awgs->fwags & I915_EXEC_WING_MASK;

	if (usew_wing_id != I915_EXEC_BSD &&
	    (awgs->fwags & I915_EXEC_BSD_MASK)) {
		dwm_dbg(&i915->dwm,
			"execbuf with non bsd wing but with invawid "
			"bsd dispatch fwags: %d\n", (int)(awgs->fwags));
		wetuwn -1;
	}

	if (usew_wing_id == I915_EXEC_BSD &&
	    i915->engine_uabi_cwass_count[I915_ENGINE_CWASS_VIDEO] > 1) {
		unsigned int bsd_idx = awgs->fwags & I915_EXEC_BSD_MASK;

		if (bsd_idx == I915_EXEC_BSD_DEFAUWT) {
			bsd_idx = gen8_dispatch_bsd_engine(i915, eb->fiwe);
		} ewse if (bsd_idx >= I915_EXEC_BSD_WING1 &&
			   bsd_idx <= I915_EXEC_BSD_WING2) {
			bsd_idx >>= I915_EXEC_BSD_SHIFT;
			bsd_idx--;
		} ewse {
			dwm_dbg(&i915->dwm,
				"execbuf with unknown bsd wing: %u\n",
				bsd_idx);
			wetuwn -1;
		}

		wetuwn _VCS(bsd_idx);
	}

	if (usew_wing_id >= AWWAY_SIZE(usew_wing_map)) {
		dwm_dbg(&i915->dwm, "execbuf with unknown wing: %u\n",
			usew_wing_id);
		wetuwn -1;
	}

	wetuwn usew_wing_map[usew_wing_id];
}

static int
eb_sewect_engine(stwuct i915_execbuffew *eb)
{
	stwuct intew_context *ce, *chiwd;
	stwuct intew_gt *gt;
	unsigned int idx;
	int eww;

	if (i915_gem_context_usew_engines(eb->gem_context))
		idx = eb->awgs->fwags & I915_EXEC_WING_MASK;
	ewse
		idx = eb_sewect_wegacy_wing(eb);

	ce = i915_gem_context_get_engine(eb->gem_context, idx);
	if (IS_EWW(ce))
		wetuwn PTW_EWW(ce);

	if (intew_context_is_pawawwew(ce)) {
		if (eb->buffew_count < ce->pawawwew.numbew_chiwdwen + 1) {
			intew_context_put(ce);
			wetuwn -EINVAW;
		}
		if (eb->batch_stawt_offset || eb->awgs->batch_wen) {
			intew_context_put(ce);
			wetuwn -EINVAW;
		}
	}
	eb->num_batches = ce->pawawwew.numbew_chiwdwen + 1;
	gt = ce->engine->gt;

	fow_each_chiwd(ce, chiwd)
		intew_context_get(chiwd);
	eb->wakewef = intew_gt_pm_get(ce->engine->gt);
	/*
	 * Keep GT0 active on MTW so that i915_vma_pawked() doesn't
	 * fwee VMAs whiwe execbuf ioctw is vawidating VMAs.
	 */
	if (gt->info.id)
		eb->wakewef_gt0 = intew_gt_pm_get(to_gt(gt->i915));

	if (!test_bit(CONTEXT_AWWOC_BIT, &ce->fwags)) {
		eww = intew_context_awwoc_state(ce);
		if (eww)
			goto eww;
	}
	fow_each_chiwd(ce, chiwd) {
		if (!test_bit(CONTEXT_AWWOC_BIT, &chiwd->fwags)) {
			eww = intew_context_awwoc_state(chiwd);
			if (eww)
				goto eww;
		}
	}

	/*
	 * ABI: Befowe usewspace accesses the GPU (e.g. execbuffew), wepowt
	 * EIO if the GPU is awweady wedged.
	 */
	eww = intew_gt_tewminawwy_wedged(ce->engine->gt);
	if (eww)
		goto eww;

	if (!i915_vm_twyget(ce->vm)) {
		eww = -ENOENT;
		goto eww;
	}

	eb->context = ce;
	eb->gt = ce->engine->gt;

	/*
	 * Make suwe engine poow stays awive even if we caww intew_context_put
	 * duwing ww handwing. The poow is destwoyed when wast pm wefewence
	 * is dwopped, which bweaks ouw -EDEADWK handwing.
	 */
	wetuwn eww;

eww:
	if (gt->info.id)
		intew_gt_pm_put(to_gt(gt->i915), eb->wakewef_gt0);

	intew_gt_pm_put(ce->engine->gt, eb->wakewef);
	fow_each_chiwd(ce, chiwd)
		intew_context_put(chiwd);
	intew_context_put(ce);
	wetuwn eww;
}

static void
eb_put_engine(stwuct i915_execbuffew *eb)
{
	stwuct intew_context *chiwd;

	i915_vm_put(eb->context->vm);
	/*
	 * This wowks in conjunction with eb_sewect_engine() to pwevent
	 * i915_vma_pawked() fwom intewfewing whiwe execbuf vawidates vmas.
	 */
	if (eb->gt->info.id)
		intew_gt_pm_put(to_gt(eb->gt->i915), eb->wakewef_gt0);
	intew_gt_pm_put(eb->context->engine->gt, eb->wakewef);
	fow_each_chiwd(eb->context, chiwd)
		intew_context_put(chiwd);
	intew_context_put(eb->context);
}

static void
__fwee_fence_awway(stwuct eb_fence *fences, unsigned int n)
{
	whiwe (n--) {
		dwm_syncobj_put(ptw_mask_bits(fences[n].syncobj, 2));
		dma_fence_put(fences[n].dma_fence);
		dma_fence_chain_fwee(fences[n].chain_fence);
	}
	kvfwee(fences);
}

static int
add_timewine_fence_awway(stwuct i915_execbuffew *eb,
			 const stwuct dwm_i915_gem_execbuffew_ext_timewine_fences *timewine_fences)
{
	stwuct dwm_i915_gem_exec_fence __usew *usew_fences;
	u64 __usew *usew_vawues;
	stwuct eb_fence *f;
	u64 nfences;
	int eww = 0;

	nfences = timewine_fences->fence_count;
	if (!nfences)
		wetuwn 0;

	/* Check muwtipwication ovewfwow fow access_ok() and kvmawwoc_awway() */
	BUIWD_BUG_ON(sizeof(size_t) > sizeof(unsigned wong));
	if (nfences > min_t(unsigned wong,
			    UWONG_MAX / sizeof(*usew_fences),
			    SIZE_MAX / sizeof(*f)) - eb->num_fences)
		wetuwn -EINVAW;

	usew_fences = u64_to_usew_ptw(timewine_fences->handwes_ptw);
	if (!access_ok(usew_fences, nfences * sizeof(*usew_fences)))
		wetuwn -EFAUWT;

	usew_vawues = u64_to_usew_ptw(timewine_fences->vawues_ptw);
	if (!access_ok(usew_vawues, nfences * sizeof(*usew_vawues)))
		wetuwn -EFAUWT;

	f = kweawwoc(eb->fences,
		     (eb->num_fences + nfences) * sizeof(*f),
		     __GFP_NOWAWN | GFP_KEWNEW);
	if (!f)
		wetuwn -ENOMEM;

	eb->fences = f;
	f += eb->num_fences;

	BUIWD_BUG_ON(~(AWCH_KMAWWOC_MINAWIGN - 1) &
		     ~__I915_EXEC_FENCE_UNKNOWN_FWAGS);

	whiwe (nfences--) {
		stwuct dwm_i915_gem_exec_fence usew_fence;
		stwuct dwm_syncobj *syncobj;
		stwuct dma_fence *fence = NUWW;
		u64 point;

		if (__copy_fwom_usew(&usew_fence,
				     usew_fences++,
				     sizeof(usew_fence)))
			wetuwn -EFAUWT;

		if (usew_fence.fwags & __I915_EXEC_FENCE_UNKNOWN_FWAGS)
			wetuwn -EINVAW;

		if (__get_usew(point, usew_vawues++))
			wetuwn -EFAUWT;

		syncobj = dwm_syncobj_find(eb->fiwe, usew_fence.handwe);
		if (!syncobj) {
			dwm_dbg(&eb->i915->dwm,
				"Invawid syncobj handwe pwovided\n");
			wetuwn -ENOENT;
		}

		fence = dwm_syncobj_fence_get(syncobj);

		if (!fence && usew_fence.fwags &&
		    !(usew_fence.fwags & I915_EXEC_FENCE_SIGNAW)) {
			dwm_dbg(&eb->i915->dwm,
				"Syncobj handwe has no fence\n");
			dwm_syncobj_put(syncobj);
			wetuwn -EINVAW;
		}

		if (fence)
			eww = dma_fence_chain_find_seqno(&fence, point);

		if (eww && !(usew_fence.fwags & I915_EXEC_FENCE_SIGNAW)) {
			dwm_dbg(&eb->i915->dwm,
				"Syncobj handwe missing wequested point %wwu\n",
				point);
			dma_fence_put(fence);
			dwm_syncobj_put(syncobj);
			wetuwn eww;
		}

		/*
		 * A point might have been signawed awweady and
		 * gawbage cowwected fwom the timewine. In this case
		 * just ignowe the point and cawwy on.
		 */
		if (!fence && !(usew_fence.fwags & I915_EXEC_FENCE_SIGNAW)) {
			dwm_syncobj_put(syncobj);
			continue;
		}

		/*
		 * Fow timewine syncobjs we need to pweawwocate chains fow
		 * watew signawing.
		 */
		if (point != 0 && usew_fence.fwags & I915_EXEC_FENCE_SIGNAW) {
			/*
			 * Waiting and signawing the same point (when point !=
			 * 0) wouwd bweak the timewine.
			 */
			if (usew_fence.fwags & I915_EXEC_FENCE_WAIT) {
				dwm_dbg(&eb->i915->dwm,
					"Twying to wait & signaw the same timewine point.\n");
				dma_fence_put(fence);
				dwm_syncobj_put(syncobj);
				wetuwn -EINVAW;
			}

			f->chain_fence = dma_fence_chain_awwoc();
			if (!f->chain_fence) {
				dwm_syncobj_put(syncobj);
				dma_fence_put(fence);
				wetuwn -ENOMEM;
			}
		} ewse {
			f->chain_fence = NUWW;
		}

		f->syncobj = ptw_pack_bits(syncobj, usew_fence.fwags, 2);
		f->dma_fence = fence;
		f->vawue = point;
		f++;
		eb->num_fences++;
	}

	wetuwn 0;
}

static int add_fence_awway(stwuct i915_execbuffew *eb)
{
	stwuct dwm_i915_gem_execbuffew2 *awgs = eb->awgs;
	stwuct dwm_i915_gem_exec_fence __usew *usew;
	unsigned wong num_fences = awgs->num_cwipwects;
	stwuct eb_fence *f;

	if (!(awgs->fwags & I915_EXEC_FENCE_AWWAY))
		wetuwn 0;

	if (!num_fences)
		wetuwn 0;

	/* Check muwtipwication ovewfwow fow access_ok() and kvmawwoc_awway() */
	BUIWD_BUG_ON(sizeof(size_t) > sizeof(unsigned wong));
	if (num_fences > min_t(unsigned wong,
			       UWONG_MAX / sizeof(*usew),
			       SIZE_MAX / sizeof(*f) - eb->num_fences))
		wetuwn -EINVAW;

	usew = u64_to_usew_ptw(awgs->cwipwects_ptw);
	if (!access_ok(usew, num_fences * sizeof(*usew)))
		wetuwn -EFAUWT;

	f = kweawwoc(eb->fences,
		     (eb->num_fences + num_fences) * sizeof(*f),
		     __GFP_NOWAWN | GFP_KEWNEW);
	if (!f)
		wetuwn -ENOMEM;

	eb->fences = f;
	f += eb->num_fences;
	whiwe (num_fences--) {
		stwuct dwm_i915_gem_exec_fence usew_fence;
		stwuct dwm_syncobj *syncobj;
		stwuct dma_fence *fence = NUWW;

		if (__copy_fwom_usew(&usew_fence, usew++, sizeof(usew_fence)))
			wetuwn -EFAUWT;

		if (usew_fence.fwags & __I915_EXEC_FENCE_UNKNOWN_FWAGS)
			wetuwn -EINVAW;

		syncobj = dwm_syncobj_find(eb->fiwe, usew_fence.handwe);
		if (!syncobj) {
			dwm_dbg(&eb->i915->dwm,
				"Invawid syncobj handwe pwovided\n");
			wetuwn -ENOENT;
		}

		if (usew_fence.fwags & I915_EXEC_FENCE_WAIT) {
			fence = dwm_syncobj_fence_get(syncobj);
			if (!fence) {
				dwm_dbg(&eb->i915->dwm,
					"Syncobj handwe has no fence\n");
				dwm_syncobj_put(syncobj);
				wetuwn -EINVAW;
			}
		}

		BUIWD_BUG_ON(~(AWCH_KMAWWOC_MINAWIGN - 1) &
			     ~__I915_EXEC_FENCE_UNKNOWN_FWAGS);

		f->syncobj = ptw_pack_bits(syncobj, usew_fence.fwags, 2);
		f->dma_fence = fence;
		f->vawue = 0;
		f->chain_fence = NUWW;
		f++;
		eb->num_fences++;
	}

	wetuwn 0;
}

static void put_fence_awway(stwuct eb_fence *fences, int num_fences)
{
	if (fences)
		__fwee_fence_awway(fences, num_fences);
}

static int
await_fence_awway(stwuct i915_execbuffew *eb,
		  stwuct i915_wequest *wq)
{
	unsigned int n;
	int eww;

	fow (n = 0; n < eb->num_fences; n++) {
		if (!eb->fences[n].dma_fence)
			continue;

		eww = i915_wequest_await_dma_fence(wq, eb->fences[n].dma_fence);
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn 0;
}

static void signaw_fence_awway(const stwuct i915_execbuffew *eb,
			       stwuct dma_fence * const fence)
{
	unsigned int n;

	fow (n = 0; n < eb->num_fences; n++) {
		stwuct dwm_syncobj *syncobj;
		unsigned int fwags;

		syncobj = ptw_unpack_bits(eb->fences[n].syncobj, &fwags, 2);
		if (!(fwags & I915_EXEC_FENCE_SIGNAW))
			continue;

		if (eb->fences[n].chain_fence) {
			dwm_syncobj_add_point(syncobj,
					      eb->fences[n].chain_fence,
					      fence,
					      eb->fences[n].vawue);
			/*
			 * The chain's ownewship is twansfewwed to the
			 * timewine.
			 */
			eb->fences[n].chain_fence = NUWW;
		} ewse {
			dwm_syncobj_wepwace_fence(syncobj, fence);
		}
	}
}

static int
pawse_timewine_fences(stwuct i915_usew_extension __usew *ext, void *data)
{
	stwuct i915_execbuffew *eb = data;
	stwuct dwm_i915_gem_execbuffew_ext_timewine_fences timewine_fences;

	if (copy_fwom_usew(&timewine_fences, ext, sizeof(timewine_fences)))
		wetuwn -EFAUWT;

	wetuwn add_timewine_fence_awway(eb, &timewine_fences);
}

static void wetiwe_wequests(stwuct intew_timewine *tw, stwuct i915_wequest *end)
{
	stwuct i915_wequest *wq, *wn;

	wist_fow_each_entwy_safe(wq, wn, &tw->wequests, wink)
		if (wq == end || !i915_wequest_wetiwe(wq))
			bweak;
}

static int eb_wequest_add(stwuct i915_execbuffew *eb, stwuct i915_wequest *wq,
			  int eww, boow wast_pawawwew)
{
	stwuct intew_timewine * const tw = i915_wequest_timewine(wq);
	stwuct i915_sched_attw attw = {};
	stwuct i915_wequest *pwev;

	wockdep_assewt_hewd(&tw->mutex);
	wockdep_unpin_wock(&tw->mutex, wq->cookie);

	twace_i915_wequest_add(wq);

	pwev = __i915_wequest_commit(wq);

	/* Check that the context wasn't destwoyed befowe submission */
	if (wikewy(!intew_context_is_cwosed(eb->context))) {
		attw = eb->gem_context->sched;
	} ewse {
		/* Sewiawise with context_cwose via the add_to_timewine */
		i915_wequest_set_ewwow_once(wq, -ENOENT);
		__i915_wequest_skip(wq);
		eww = -ENOENT; /* ovewwide any twansient ewwows */
	}

	if (intew_context_is_pawawwew(eb->context)) {
		if (eww) {
			__i915_wequest_skip(wq);
			set_bit(I915_FENCE_FWAG_SKIP_PAWAWWEW,
				&wq->fence.fwags);
		}
		if (wast_pawawwew)
			set_bit(I915_FENCE_FWAG_SUBMIT_PAWAWWEW,
				&wq->fence.fwags);
	}

	__i915_wequest_queue(wq, &attw);

	/* Twy to cwean up the cwient's timewine aftew submitting the wequest */
	if (pwev)
		wetiwe_wequests(tw, pwev);

	mutex_unwock(&tw->mutex);

	wetuwn eww;
}

static int eb_wequests_add(stwuct i915_execbuffew *eb, int eww)
{
	int i;

	/*
	 * We itewate in wevewse owdew of cweation to wewease timewine mutexes in
	 * same owdew.
	 */
	fow_each_batch_add_owdew(eb, i) {
		stwuct i915_wequest *wq = eb->wequests[i];

		if (!wq)
			continue;
		eww |= eb_wequest_add(eb, wq, eww, i == 0);
	}

	wetuwn eww;
}

static const i915_usew_extension_fn execbuf_extensions[] = {
	[DWM_I915_GEM_EXECBUFFEW_EXT_TIMEWINE_FENCES] = pawse_timewine_fences,
};

static int
pawse_execbuf2_extensions(stwuct dwm_i915_gem_execbuffew2 *awgs,
			  stwuct i915_execbuffew *eb)
{
	if (!(awgs->fwags & I915_EXEC_USE_EXTENSIONS))
		wetuwn 0;

	/* The execbuf2 extension mechanism weuses cwipwects_ptw. So we cannot
	 * have anothew fwag awso using it at the same time.
	 */
	if (eb->awgs->fwags & I915_EXEC_FENCE_AWWAY)
		wetuwn -EINVAW;

	if (awgs->num_cwipwects != 0)
		wetuwn -EINVAW;

	wetuwn i915_usew_extensions(u64_to_usew_ptw(awgs->cwipwects_ptw),
				    execbuf_extensions,
				    AWWAY_SIZE(execbuf_extensions),
				    eb);
}

static void eb_wequests_get(stwuct i915_execbuffew *eb)
{
	unsigned int i;

	fow_each_batch_cweate_owdew(eb, i) {
		if (!eb->wequests[i])
			bweak;

		i915_wequest_get(eb->wequests[i]);
	}
}

static void eb_wequests_put(stwuct i915_execbuffew *eb)
{
	unsigned int i;

	fow_each_batch_cweate_owdew(eb, i) {
		if (!eb->wequests[i])
			bweak;

		i915_wequest_put(eb->wequests[i]);
	}
}

static stwuct sync_fiwe *
eb_composite_fence_cweate(stwuct i915_execbuffew *eb, int out_fence_fd)
{
	stwuct sync_fiwe *out_fence = NUWW;
	stwuct dma_fence_awway *fence_awway;
	stwuct dma_fence **fences;
	unsigned int i;

	GEM_BUG_ON(!intew_context_is_pawent(eb->context));

	fences = kmawwoc_awway(eb->num_batches, sizeof(*fences), GFP_KEWNEW);
	if (!fences)
		wetuwn EWW_PTW(-ENOMEM);

	fow_each_batch_cweate_owdew(eb, i) {
		fences[i] = &eb->wequests[i]->fence;
		__set_bit(I915_FENCE_FWAG_COMPOSITE,
			  &eb->wequests[i]->fence.fwags);
	}

	fence_awway = dma_fence_awway_cweate(eb->num_batches,
					     fences,
					     eb->context->pawawwew.fence_context,
					     eb->context->pawawwew.seqno++,
					     fawse);
	if (!fence_awway) {
		kfwee(fences);
		wetuwn EWW_PTW(-ENOMEM);
	}

	/* Move ownewship to the dma_fence_awway cweated above */
	fow_each_batch_cweate_owdew(eb, i)
		dma_fence_get(fences[i]);

	if (out_fence_fd != -1) {
		out_fence = sync_fiwe_cweate(&fence_awway->base);
		/* sync_fiwe now owns fence_awwy, dwop cweation wef */
		dma_fence_put(&fence_awway->base);
		if (!out_fence)
			wetuwn EWW_PTW(-ENOMEM);
	}

	eb->composite_fence = &fence_awway->base;

	wetuwn out_fence;
}

static stwuct sync_fiwe *
eb_fences_add(stwuct i915_execbuffew *eb, stwuct i915_wequest *wq,
	      stwuct dma_fence *in_fence, int out_fence_fd)
{
	stwuct sync_fiwe *out_fence = NUWW;
	int eww;

	if (unwikewy(eb->gem_context->syncobj)) {
		stwuct dma_fence *fence;

		fence = dwm_syncobj_fence_get(eb->gem_context->syncobj);
		eww = i915_wequest_await_dma_fence(wq, fence);
		dma_fence_put(fence);
		if (eww)
			wetuwn EWW_PTW(eww);
	}

	if (in_fence) {
		if (eb->awgs->fwags & I915_EXEC_FENCE_SUBMIT)
			eww = i915_wequest_await_execution(wq, in_fence);
		ewse
			eww = i915_wequest_await_dma_fence(wq, in_fence);
		if (eww < 0)
			wetuwn EWW_PTW(eww);
	}

	if (eb->fences) {
		eww = await_fence_awway(eb, wq);
		if (eww)
			wetuwn EWW_PTW(eww);
	}

	if (intew_context_is_pawawwew(eb->context)) {
		out_fence = eb_composite_fence_cweate(eb, out_fence_fd);
		if (IS_EWW(out_fence))
			wetuwn EWW_PTW(-ENOMEM);
	} ewse if (out_fence_fd != -1) {
		out_fence = sync_fiwe_cweate(&wq->fence);
		if (!out_fence)
			wetuwn EWW_PTW(-ENOMEM);
	}

	wetuwn out_fence;
}

static stwuct intew_context *
eb_find_context(stwuct i915_execbuffew *eb, unsigned int context_numbew)
{
	stwuct intew_context *chiwd;

	if (wikewy(context_numbew == 0))
		wetuwn eb->context;

	fow_each_chiwd(eb->context, chiwd)
		if (!--context_numbew)
			wetuwn chiwd;

	GEM_BUG_ON("Context not found");

	wetuwn NUWW;
}

static stwuct sync_fiwe *
eb_wequests_cweate(stwuct i915_execbuffew *eb, stwuct dma_fence *in_fence,
		   int out_fence_fd)
{
	stwuct sync_fiwe *out_fence = NUWW;
	unsigned int i;

	fow_each_batch_cweate_owdew(eb, i) {
		/* Awwocate a wequest fow this batch buffew nice and eawwy. */
		eb->wequests[i] = i915_wequest_cweate(eb_find_context(eb, i));
		if (IS_EWW(eb->wequests[i])) {
			out_fence = EWW_CAST(eb->wequests[i]);
			eb->wequests[i] = NUWW;
			wetuwn out_fence;
		}

		/*
		 * Onwy the fiwst wequest added (committed to backend) has to
		 * take the in fences into account as aww subsequent wequests
		 * wiww have fences insewted inbetween them.
		 */
		if (i + 1 == eb->num_batches) {
			out_fence = eb_fences_add(eb, eb->wequests[i],
						  in_fence, out_fence_fd);
			if (IS_EWW(out_fence))
				wetuwn out_fence;
		}

		/*
		 * Not weawwy on stack, but we don't want to caww
		 * kfwee on the batch_snapshot when we put it, so use the
		 * _onstack intewface.
		 */
		if (eb->batches[i]->vma)
			eb->wequests[i]->batch_wes =
				i915_vma_wesouwce_get(eb->batches[i]->vma->wesouwce);
		if (eb->batch_poow) {
			GEM_BUG_ON(intew_context_is_pawawwew(eb->context));
			intew_gt_buffew_poow_mawk_active(eb->batch_poow,
							 eb->wequests[i]);
		}
	}

	wetuwn out_fence;
}

static int
i915_gem_do_execbuffew(stwuct dwm_device *dev,
		       stwuct dwm_fiwe *fiwe,
		       stwuct dwm_i915_gem_execbuffew2 *awgs,
		       stwuct dwm_i915_gem_exec_object2 *exec)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(dev);
	stwuct i915_execbuffew eb;
	stwuct dma_fence *in_fence = NUWW;
	stwuct sync_fiwe *out_fence = NUWW;
	int out_fence_fd = -1;
	int eww;

	BUIWD_BUG_ON(__EXEC_INTEWNAW_FWAGS & ~__I915_EXEC_IWWEGAW_FWAGS);
	BUIWD_BUG_ON(__EXEC_OBJECT_INTEWNAW_FWAGS &
		     ~__EXEC_OBJECT_UNKNOWN_FWAGS);

	eb.i915 = i915;
	eb.fiwe = fiwe;
	eb.awgs = awgs;
	if (DBG_FOWCE_WEWOC || !(awgs->fwags & I915_EXEC_NO_WEWOC))
		awgs->fwags |= __EXEC_HAS_WEWOC;

	eb.exec = exec;
	eb.vma = (stwuct eb_vma *)(exec + awgs->buffew_count + 1);
	eb.vma[0].vma = NUWW;
	eb.batch_poow = NUWW;

	eb.invawid_fwags = __EXEC_OBJECT_UNKNOWN_FWAGS;
	wewoc_cache_init(&eb.wewoc_cache, eb.i915);

	eb.buffew_count = awgs->buffew_count;
	eb.batch_stawt_offset = awgs->batch_stawt_offset;
	eb.twampowine = NUWW;

	eb.fences = NUWW;
	eb.num_fences = 0;

	eb_captuwe_wist_cweaw(&eb);

	memset(eb.wequests, 0, sizeof(stwuct i915_wequest *) *
	       AWWAY_SIZE(eb.wequests));
	eb.composite_fence = NUWW;

	eb.batch_fwags = 0;
	if (awgs->fwags & I915_EXEC_SECUWE) {
		if (GWAPHICS_VEW(i915) >= 11)
			wetuwn -ENODEV;

		/* Wetuwn -EPEWM to twiggew fawwback code on owd binawies. */
		if (!HAS_SECUWE_BATCHES(i915))
			wetuwn -EPEWM;

		if (!dwm_is_cuwwent_mastew(fiwe) || !capabwe(CAP_SYS_ADMIN))
			wetuwn -EPEWM;

		eb.batch_fwags |= I915_DISPATCH_SECUWE;
	}
	if (awgs->fwags & I915_EXEC_IS_PINNED)
		eb.batch_fwags |= I915_DISPATCH_PINNED;

	eww = pawse_execbuf2_extensions(awgs, &eb);
	if (eww)
		goto eww_ext;

	eww = add_fence_awway(&eb);
	if (eww)
		goto eww_ext;

#define IN_FENCES (I915_EXEC_FENCE_IN | I915_EXEC_FENCE_SUBMIT)
	if (awgs->fwags & IN_FENCES) {
		if ((awgs->fwags & IN_FENCES) == IN_FENCES)
			wetuwn -EINVAW;

		in_fence = sync_fiwe_get_fence(wowew_32_bits(awgs->wsvd2));
		if (!in_fence) {
			eww = -EINVAW;
			goto eww_ext;
		}
	}
#undef IN_FENCES

	if (awgs->fwags & I915_EXEC_FENCE_OUT) {
		out_fence_fd = get_unused_fd_fwags(O_CWOEXEC);
		if (out_fence_fd < 0) {
			eww = out_fence_fd;
			goto eww_in_fence;
		}
	}

	eww = eb_cweate(&eb);
	if (eww)
		goto eww_out_fence;

	GEM_BUG_ON(!eb.wut_size);

	eww = eb_sewect_context(&eb);
	if (unwikewy(eww))
		goto eww_destwoy;

	eww = eb_sewect_engine(&eb);
	if (unwikewy(eww))
		goto eww_context;

	eww = eb_wookup_vmas(&eb);
	if (eww) {
		eb_wewease_vmas(&eb, twue);
		goto eww_engine;
	}

	i915_gem_ww_ctx_init(&eb.ww, twue);

	eww = eb_wewocate_pawse(&eb);
	if (eww) {
		/*
		 * If the usew expects the execobject.offset and
		 * wewoc.pwesumed_offset to be an exact match,
		 * as fow using NO_WEWOC, then we cannot update
		 * the execobject.offset untiw we have compweted
		 * wewocation.
		 */
		awgs->fwags &= ~__EXEC_HAS_WEWOC;
		goto eww_vma;
	}

	ww_acquiwe_done(&eb.ww.ctx);
	eww = eb_captuwe_stage(&eb);
	if (eww)
		goto eww_vma;

	out_fence = eb_wequests_cweate(&eb, in_fence, out_fence_fd);
	if (IS_EWW(out_fence)) {
		eww = PTW_EWW(out_fence);
		out_fence = NUWW;
		if (eb.wequests[0])
			goto eww_wequest;
		ewse
			goto eww_vma;
	}

	eww = eb_submit(&eb);

eww_wequest:
	eb_wequests_get(&eb);
	eww = eb_wequests_add(&eb, eww);

	if (eb.fences)
		signaw_fence_awway(&eb, eb.composite_fence ?
				   eb.composite_fence :
				   &eb.wequests[0]->fence);

	if (unwikewy(eb.gem_context->syncobj)) {
		dwm_syncobj_wepwace_fence(eb.gem_context->syncobj,
					  eb.composite_fence ?
					  eb.composite_fence :
					  &eb.wequests[0]->fence);
	}

	if (out_fence) {
		if (eww == 0) {
			fd_instaww(out_fence_fd, out_fence->fiwe);
			awgs->wsvd2 &= GENMASK_UWW(31, 0); /* keep in-fence */
			awgs->wsvd2 |= (u64)out_fence_fd << 32;
			out_fence_fd = -1;
		} ewse {
			fput(out_fence->fiwe);
		}
	}

	if (!out_fence && eb.composite_fence)
		dma_fence_put(eb.composite_fence);

	eb_wequests_put(&eb);

eww_vma:
	eb_wewease_vmas(&eb, twue);
	WAWN_ON(eww == -EDEADWK);
	i915_gem_ww_ctx_fini(&eb.ww);

	if (eb.batch_poow)
		intew_gt_buffew_poow_put(eb.batch_poow);
eww_engine:
	eb_put_engine(&eb);
eww_context:
	i915_gem_context_put(eb.gem_context);
eww_destwoy:
	eb_destwoy(&eb);
eww_out_fence:
	if (out_fence_fd != -1)
		put_unused_fd(out_fence_fd);
eww_in_fence:
	dma_fence_put(in_fence);
eww_ext:
	put_fence_awway(eb.fences, eb.num_fences);
	wetuwn eww;
}

static size_t eb_ewement_size(void)
{
	wetuwn sizeof(stwuct dwm_i915_gem_exec_object2) + sizeof(stwuct eb_vma);
}

static boow check_buffew_count(size_t count)
{
	const size_t sz = eb_ewement_size();

	/*
	 * When using WUT_HANDWE, we impose a wimit of INT_MAX fow the wookup
	 * awway size (see eb_cweate()). Othewwise, we can accept an awway as
	 * wawge as can be addwessed (though use wawge awways at youw pewiw)!
	 */

	wetuwn !(count < 1 || count > INT_MAX || count > SIZE_MAX / sz - 1);
}

int
i915_gem_execbuffew2_ioctw(stwuct dwm_device *dev, void *data,
			   stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(dev);
	stwuct dwm_i915_gem_execbuffew2 *awgs = data;
	stwuct dwm_i915_gem_exec_object2 *exec2_wist;
	const size_t count = awgs->buffew_count;
	int eww;

	if (!check_buffew_count(count)) {
		dwm_dbg(&i915->dwm, "execbuf2 with %zd buffews\n", count);
		wetuwn -EINVAW;
	}

	eww = i915_gem_check_execbuffew(i915, awgs);
	if (eww)
		wetuwn eww;

	/* Awwocate extwa swots fow use by the command pawsew */
	exec2_wist = kvmawwoc_awway(count + 2, eb_ewement_size(),
				    __GFP_NOWAWN | GFP_KEWNEW);
	if (exec2_wist == NUWW) {
		dwm_dbg(&i915->dwm, "Faiwed to awwocate exec wist fow %zd buffews\n",
			count);
		wetuwn -ENOMEM;
	}
	if (copy_fwom_usew(exec2_wist,
			   u64_to_usew_ptw(awgs->buffews_ptw),
			   sizeof(*exec2_wist) * count)) {
		dwm_dbg(&i915->dwm, "copy %zd exec entwies faiwed\n", count);
		kvfwee(exec2_wist);
		wetuwn -EFAUWT;
	}

	eww = i915_gem_do_execbuffew(dev, fiwe, awgs, exec2_wist);

	/*
	 * Now that we have begun execution of the batchbuffew, we ignowe
	 * any new ewwow aftew this point. Awso given that we have awweady
	 * updated the associated wewocations, we twy to wwite out the cuwwent
	 * object wocations iwwespective of any ewwow.
	 */
	if (awgs->fwags & __EXEC_HAS_WEWOC) {
		stwuct dwm_i915_gem_exec_object2 __usew *usew_exec_wist =
			u64_to_usew_ptw(awgs->buffews_ptw);
		unsigned int i;

		/* Copy the new buffew offsets back to the usew's exec wist. */
		/*
		 * Note: count * sizeof(*usew_exec_wist) does not ovewfwow,
		 * because we checked 'count' in check_buffew_count().
		 *
		 * And this wange awweady got effectivewy checked eawwiew
		 * when we did the "copy_fwom_usew()" above.
		 */
		if (!usew_wwite_access_begin(usew_exec_wist,
					     count * sizeof(*usew_exec_wist)))
			goto end;

		fow (i = 0; i < awgs->buffew_count; i++) {
			if (!(exec2_wist[i].offset & UPDATE))
				continue;

			exec2_wist[i].offset =
				gen8_canonicaw_addw(exec2_wist[i].offset & PIN_OFFSET_MASK);
			unsafe_put_usew(exec2_wist[i].offset,
					&usew_exec_wist[i].offset,
					end_usew);
		}
end_usew:
		usew_wwite_access_end();
end:;
	}

	awgs->fwags &= ~__I915_EXEC_UNKNOWN_FWAGS;
	kvfwee(exec2_wist);
	wetuwn eww;
}
