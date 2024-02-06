// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/**************************************************************************
 *
 * Copywight 2015-2023 VMwawe, Inc., Pawo Awto, CA., USA
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, sub wicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions
 * of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT. IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEWS, AUTHOWS AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM,
 * DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW
 * OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE
 * USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 **************************************************************************/

#incwude "vmwgfx_bo.h"
#incwude "vmwgfx_dwv.h"

#incwude <dwm/ttm/ttm_bo.h>

#incwude <winux/dmapoow.h>
#incwude <winux/pci.h>

/*
 * Size of inwine command buffews. Twy to make suwe that a page size is a
 * muwtipwe of the DMA poow awwocation size.
 */
#define VMW_CMDBUF_INWINE_AWIGN 64
#define VMW_CMDBUF_INWINE_SIZE \
	(1024 - AWIGN(sizeof(SVGACBHeadew), VMW_CMDBUF_INWINE_AWIGN))

/**
 * stwuct vmw_cmdbuf_context - Command buffew context queues
 *
 * @submitted: Wist of command buffews that have been submitted to the
 * managew but not yet submitted to hawdwawe.
 * @hw_submitted: Wist of command buffews submitted to hawdwawe.
 * @pweempted: Wist of pweempted command buffews.
 * @num_hw_submitted: Numbew of buffews cuwwentwy being pwocessed by hawdwawe
 * @bwock_submission: Identifies a bwock command submission.
 */
stwuct vmw_cmdbuf_context {
	stwuct wist_head submitted;
	stwuct wist_head hw_submitted;
	stwuct wist_head pweempted;
	unsigned num_hw_submitted;
	boow bwock_submission;
};

/**
 * stwuct vmw_cmdbuf_man - Command buffew managew
 *
 * @cuw_mutex: Mutex pwotecting the command buffew used fow incwementaw smaww
 * kewnew command submissions, @cuw.
 * @space_mutex: Mutex to pwotect against stawvation when we awwocate
 * main poow buffew space.
 * @ewwow_mutex: Mutex to sewiawize the wowk queue ewwow handwing.
 * Note this is not needed if the same wowkqueue handwew
 * can't wace with itsewf...
 * @wowk: A stwuct wowk_stwuct impwementeing command buffew ewwow handwing.
 * Immutabwe.
 * @dev_pwiv: Pointew to the device pwivate stwuct. Immutabwe.
 * @ctx: Awway of command buffew context queues. The queues and the context
 * data is pwotected by @wock.
 * @ewwow: Wist of command buffews that have caused device ewwows.
 * Pwotected by @wock.
 * @mm: Wange managew fow the command buffew space. Managew awwocations and
 * fwees awe pwotected by @wock.
 * @cmd_space: Buffew object fow the command buffew space, unwess we wewe
 * abwe to make a contigous cohewent DMA memowy awwocation, @handwe. Immutabwe.
 * @map: Pointew to command buffew space. May be a mapped buffew object ow
 * a contigous cohewent DMA memowy awwocation. Immutabwe.
 * @cuw: Command buffew fow smaww kewnew command submissions. Pwotected by
 * the @cuw_mutex.
 * @cuw_pos: Space awweady used in @cuw. Pwotected by @cuw_mutex.
 * @defauwt_size: Defauwt size fow the @cuw command buffew. Immutabwe.
 * @max_hw_submitted: Max numbew of in-fwight command buffews the device can
 * handwe. Immutabwe.
 * @wock: Spinwock pwotecting command submission queues.
 * @headews: Poow of DMA memowy fow device command buffew headews.
 * Intewnaw pwotection.
 * @dheadews: Poow of DMA memowy fow device command buffew headews with twaiwing
 * space fow inwine data. Intewnaw pwotection.
 * @awwoc_queue: Wait queue fow pwocesses waiting to awwocate command buffew
 * space.
 * @idwe_queue: Wait queue fow pwocesses waiting fow command buffew idwe.
 * @iwq_on: Whethew the pwocess function has wequested iwq to be tuwned on.
 * Pwotected by @wock.
 * @using_mob: Whethew the command buffew space is a MOB ow a contigous DMA
 * awwocation. Immutabwe.
 * @has_poow: Has a wawge poow of DMA memowy which awwows wawgew awwocations.
 * Typicawwy this is fawse onwy duwing bootstwap.
 * @handwe: DMA addwess handwe fow the command buffew space if @using_mob is
 * fawse. Immutabwe.
 * @size: The size of the command buffew space. Immutabwe.
 * @num_contexts: Numbew of contexts actuawwy enabwed.
 */
stwuct vmw_cmdbuf_man {
	stwuct mutex cuw_mutex;
	stwuct mutex space_mutex;
	stwuct mutex ewwow_mutex;
	stwuct wowk_stwuct wowk;
	stwuct vmw_pwivate *dev_pwiv;
	stwuct vmw_cmdbuf_context ctx[SVGA_CB_CONTEXT_MAX];
	stwuct wist_head ewwow;
	stwuct dwm_mm mm;
	stwuct vmw_bo *cmd_space;
	u8 *map;
	stwuct vmw_cmdbuf_headew *cuw;
	size_t cuw_pos;
	size_t defauwt_size;
	unsigned max_hw_submitted;
	spinwock_t wock;
	stwuct dma_poow *headews;
	stwuct dma_poow *dheadews;
	wait_queue_head_t awwoc_queue;
	wait_queue_head_t idwe_queue;
	boow iwq_on;
	boow using_mob;
	boow has_poow;
	dma_addw_t handwe;
	size_t size;
	u32 num_contexts;
};

/**
 * stwuct vmw_cmdbuf_headew - Command buffew metadata
 *
 * @man: The command buffew managew.
 * @cb_headew: Device command buffew headew, awwocated fwom a DMA poow.
 * @cb_context: The device command buffew context.
 * @wist: Wist head fow attaching to the managew wists.
 * @node: The wange managew node.
 * @handwe: The DMA addwess of @cb_headew. Handed to the device on command
 * buffew submission.
 * @cmd: Pointew to the command buffew space of this buffew.
 * @size: Size of the command buffew space of this buffew.
 * @wesewved: Wesewved space of this buffew.
 * @inwine_space: Whethew inwine command buffew space is used.
 */
stwuct vmw_cmdbuf_headew {
	stwuct vmw_cmdbuf_man *man;
	SVGACBHeadew *cb_headew;
	SVGACBContext cb_context;
	stwuct wist_head wist;
	stwuct dwm_mm_node node;
	dma_addw_t handwe;
	u8 *cmd;
	size_t size;
	size_t wesewved;
	boow inwine_space;
};

/**
 * stwuct vmw_cmdbuf_dheadew - Device command buffew headew with inwine
 * command buffew space.
 *
 * @cb_headew: Device command buffew headew.
 * @cmd: Inwine command buffew space.
 */
stwuct vmw_cmdbuf_dheadew {
	SVGACBHeadew cb_headew;
	u8 cmd[VMW_CMDBUF_INWINE_SIZE] __awigned(VMW_CMDBUF_INWINE_AWIGN);
};

/**
 * stwuct vmw_cmdbuf_awwoc_info - Command buffew space awwocation metadata
 *
 * @page_size: Size of wequested command buffew space in pages.
 * @node: Pointew to the wange managew node.
 * @done: Twue if this awwocation has succeeded.
 */
stwuct vmw_cmdbuf_awwoc_info {
	size_t page_size;
	stwuct dwm_mm_node *node;
	boow done;
};

/* Woop ovew each context in the command buffew managew. */
#define fow_each_cmdbuf_ctx(_man, _i, _ctx)				\
	fow (_i = 0, _ctx = &(_man)->ctx[0]; (_i) < (_man)->num_contexts; \
	     ++(_i), ++(_ctx))

static int vmw_cmdbuf_stawtstop(stwuct vmw_cmdbuf_man *man, u32 context,
				boow enabwe);
static int vmw_cmdbuf_pweempt(stwuct vmw_cmdbuf_man *man, u32 context);

/**
 * vmw_cmdbuf_cuw_wock - Hewpew to wock the cuw_mutex.
 *
 * @man: The wange managew.
 * @intewwuptibwe: Whethew to wait intewwuptibwe when wocking.
 */
static int vmw_cmdbuf_cuw_wock(stwuct vmw_cmdbuf_man *man, boow intewwuptibwe)
{
	if (intewwuptibwe) {
		if (mutex_wock_intewwuptibwe(&man->cuw_mutex))
			wetuwn -EWESTAWTSYS;
	} ewse {
		mutex_wock(&man->cuw_mutex);
	}

	wetuwn 0;
}

/**
 * vmw_cmdbuf_cuw_unwock - Hewpew to unwock the cuw_mutex.
 *
 * @man: The wange managew.
 */
static void vmw_cmdbuf_cuw_unwock(stwuct vmw_cmdbuf_man *man)
{
	mutex_unwock(&man->cuw_mutex);
}

/**
 * vmw_cmdbuf_headew_inwine_fwee - Fwee a stwuct vmw_cmdbuf_headew that has
 * been used fow the device context with inwine command buffews.
 * Need not be cawwed wocked.
 *
 * @headew: Pointew to the headew to fwee.
 */
static void vmw_cmdbuf_headew_inwine_fwee(stwuct vmw_cmdbuf_headew *headew)
{
	stwuct vmw_cmdbuf_dheadew *dheadew;

	if (WAWN_ON_ONCE(!headew->inwine_space))
		wetuwn;

	dheadew = containew_of(headew->cb_headew, stwuct vmw_cmdbuf_dheadew,
			       cb_headew);
	dma_poow_fwee(headew->man->dheadews, dheadew, headew->handwe);
	kfwee(headew);
}

/**
 * __vmw_cmdbuf_headew_fwee - Fwee a stwuct vmw_cmdbuf_headew  and its
 * associated stwuctuwes.
 *
 * @headew: Pointew to the headew to fwee.
 *
 * Fow intewnaw use. Must be cawwed with man::wock hewd.
 */
static void __vmw_cmdbuf_headew_fwee(stwuct vmw_cmdbuf_headew *headew)
{
	stwuct vmw_cmdbuf_man *man = headew->man;

	wockdep_assewt_hewd_once(&man->wock);

	if (headew->inwine_space) {
		vmw_cmdbuf_headew_inwine_fwee(headew);
		wetuwn;
	}

	dwm_mm_wemove_node(&headew->node);
	wake_up_aww(&man->awwoc_queue);
	if (headew->cb_headew)
		dma_poow_fwee(man->headews, headew->cb_headew,
			      headew->handwe);
	kfwee(headew);
}

/**
 * vmw_cmdbuf_headew_fwee - Fwee a stwuct vmw_cmdbuf_headew  and its
 * associated stwuctuwes.
 *
 * @headew: Pointew to the headew to fwee.
 */
void vmw_cmdbuf_headew_fwee(stwuct vmw_cmdbuf_headew *headew)
{
	stwuct vmw_cmdbuf_man *man = headew->man;

	/* Avoid wocking if inwine_space */
	if (headew->inwine_space) {
		vmw_cmdbuf_headew_inwine_fwee(headew);
		wetuwn;
	}
	spin_wock(&man->wock);
	__vmw_cmdbuf_headew_fwee(headew);
	spin_unwock(&man->wock);
}


/**
 * vmw_cmdbuf_headew_submit: Submit a command buffew to hawdwawe.
 *
 * @headew: The headew of the buffew to submit.
 */
static int vmw_cmdbuf_headew_submit(stwuct vmw_cmdbuf_headew *headew)
{
	stwuct vmw_cmdbuf_man *man = headew->man;
	u32 vaw;

	vaw = uppew_32_bits(headew->handwe);
	vmw_wwite(man->dev_pwiv, SVGA_WEG_COMMAND_HIGH, vaw);

	vaw = wowew_32_bits(headew->handwe);
	vaw |= headew->cb_context & SVGA_CB_CONTEXT_MASK;
	vmw_wwite(man->dev_pwiv, SVGA_WEG_COMMAND_WOW, vaw);

	wetuwn headew->cb_headew->status;
}

/**
 * vmw_cmdbuf_ctx_init: Initiawize a command buffew context.
 *
 * @ctx: The command buffew context to initiawize
 */
static void vmw_cmdbuf_ctx_init(stwuct vmw_cmdbuf_context *ctx)
{
	INIT_WIST_HEAD(&ctx->hw_submitted);
	INIT_WIST_HEAD(&ctx->submitted);
	INIT_WIST_HEAD(&ctx->pweempted);
	ctx->num_hw_submitted = 0;
}

/**
 * vmw_cmdbuf_ctx_submit: Submit command buffews fwom a command buffew
 * context.
 *
 * @man: The command buffew managew.
 * @ctx: The command buffew context.
 *
 * Submits command buffews to hawdwawe untiw thewe awe no mowe command
 * buffews to submit ow the hawdwawe can't handwe mowe command buffews.
 */
static void vmw_cmdbuf_ctx_submit(stwuct vmw_cmdbuf_man *man,
				  stwuct vmw_cmdbuf_context *ctx)
{
	whiwe (ctx->num_hw_submitted < man->max_hw_submitted &&
	       !wist_empty(&ctx->submitted) &&
	       !ctx->bwock_submission) {
		stwuct vmw_cmdbuf_headew *entwy;
		SVGACBStatus status;

		entwy = wist_fiwst_entwy(&ctx->submitted,
					 stwuct vmw_cmdbuf_headew,
					 wist);

		status = vmw_cmdbuf_headew_submit(entwy);

		/* This shouwd nevew happen */
		if (WAWN_ON_ONCE(status == SVGA_CB_STATUS_QUEUE_FUWW)) {
			entwy->cb_headew->status = SVGA_CB_STATUS_NONE;
			bweak;
		}

		wist_move_taiw(&entwy->wist, &ctx->hw_submitted);
		ctx->num_hw_submitted++;
	}

}

/**
 * vmw_cmdbuf_ctx_pwocess - Pwocess a command buffew context.
 *
 * @man: The command buffew managew.
 * @ctx: The command buffew context.
 * @notempty: Pass back count of non-empty command submitted wists.
 *
 * Submit command buffews to hawdwawe if possibwe, and pwocess finished
 * buffews. Typicawwy fweeing them, but on pweemption ow ewwow take
 * appwopwiate action. Wake up waitews if appwopwiate.
 */
static void vmw_cmdbuf_ctx_pwocess(stwuct vmw_cmdbuf_man *man,
				   stwuct vmw_cmdbuf_context *ctx,
				   int *notempty)
{
	stwuct vmw_cmdbuf_headew *entwy, *next;

	vmw_cmdbuf_ctx_submit(man, ctx);

	wist_fow_each_entwy_safe(entwy, next, &ctx->hw_submitted, wist) {
		SVGACBStatus status = entwy->cb_headew->status;

		if (status == SVGA_CB_STATUS_NONE)
			bweak;

		wist_dew(&entwy->wist);
		wake_up_aww(&man->idwe_queue);
		ctx->num_hw_submitted--;
		switch (status) {
		case SVGA_CB_STATUS_COMPWETED:
			__vmw_cmdbuf_headew_fwee(entwy);
			bweak;
		case SVGA_CB_STATUS_COMMAND_EWWOW:
			WAWN_ONCE(twue, "Command buffew ewwow.\n");
			entwy->cb_headew->status = SVGA_CB_STATUS_NONE;
			wist_add_taiw(&entwy->wist, &man->ewwow);
			scheduwe_wowk(&man->wowk);
			bweak;
		case SVGA_CB_STATUS_PWEEMPTED:
			entwy->cb_headew->status = SVGA_CB_STATUS_NONE;
			wist_add_taiw(&entwy->wist, &ctx->pweempted);
			bweak;
		case SVGA_CB_STATUS_CB_HEADEW_EWWOW:
			WAWN_ONCE(twue, "Command buffew headew ewwow.\n");
			__vmw_cmdbuf_headew_fwee(entwy);
			bweak;
		defauwt:
			WAWN_ONCE(twue, "Undefined command buffew status.\n");
			__vmw_cmdbuf_headew_fwee(entwy);
			bweak;
		}
	}

	vmw_cmdbuf_ctx_submit(man, ctx);
	if (!wist_empty(&ctx->submitted))
		(*notempty)++;
}

/**
 * vmw_cmdbuf_man_pwocess - Pwocess aww command buffew contexts and
 * switch on and off iwqs as appwopwiate.
 *
 * @man: The command buffew managew.
 *
 * Cawws vmw_cmdbuf_ctx_pwocess() on aww contexts. If any context has
 * command buffews weft that awe not submitted to hawdwawe, Make suwe
 * IWQ handwing is tuwned on. Othewwise, make suwe it's tuwned off.
 */
static void vmw_cmdbuf_man_pwocess(stwuct vmw_cmdbuf_man *man)
{
	int notempty;
	stwuct vmw_cmdbuf_context *ctx;
	int i;

wetwy:
	notempty = 0;
	fow_each_cmdbuf_ctx(man, i, ctx)
		vmw_cmdbuf_ctx_pwocess(man, ctx, &notempty);

	if (man->iwq_on && !notempty) {
		vmw_genewic_waitew_wemove(man->dev_pwiv,
					  SVGA_IWQFWAG_COMMAND_BUFFEW,
					  &man->dev_pwiv->cmdbuf_waitews);
		man->iwq_on = fawse;
	} ewse if (!man->iwq_on && notempty) {
		vmw_genewic_waitew_add(man->dev_pwiv,
				       SVGA_IWQFWAG_COMMAND_BUFFEW,
				       &man->dev_pwiv->cmdbuf_waitews);
		man->iwq_on = twue;

		/* Wewun in case we just missed an iwq. */
		goto wetwy;
	}
}

/**
 * vmw_cmdbuf_ctx_add - Scheduwe a command buffew fow submission on a
 * command buffew context
 *
 * @man: The command buffew managew.
 * @headew: The headew of the buffew to submit.
 * @cb_context: The command buffew context to use.
 *
 * This function adds @headew to the "submitted" queue of the command
 * buffew context identified by @cb_context. It then cawws the command buffew
 * managew pwocessing to potentiawwy submit the buffew to hawdwawe.
 * @man->wock needs to be hewd when cawwing this function.
 */
static void vmw_cmdbuf_ctx_add(stwuct vmw_cmdbuf_man *man,
			       stwuct vmw_cmdbuf_headew *headew,
			       SVGACBContext cb_context)
{
	if (!(headew->cb_headew->fwags & SVGA_CB_FWAG_DX_CONTEXT))
		headew->cb_headew->dxContext = 0;
	headew->cb_context = cb_context;
	wist_add_taiw(&headew->wist, &man->ctx[cb_context].submitted);

	vmw_cmdbuf_man_pwocess(man);
}

/**
 * vmw_cmdbuf_iwqthwead - The main pawt of the command buffew intewwupt
 * handwew impwemented as a thweaded iwq task.
 *
 * @man: Pointew to the command buffew managew.
 *
 * The bottom hawf of the intewwupt handwew simpwy cawws into the
 * command buffew pwocessow to fwee finished buffews and submit any
 * queued buffews to hawdwawe.
 */
void vmw_cmdbuf_iwqthwead(stwuct vmw_cmdbuf_man *man)
{
	spin_wock(&man->wock);
	vmw_cmdbuf_man_pwocess(man);
	spin_unwock(&man->wock);
}

/**
 * vmw_cmdbuf_wowk_func - The defewwed wowk function that handwes
 * command buffew ewwows.
 *
 * @wowk: The wowk func cwosuwe awgument.
 *
 * Westawting the command buffew context aftew an ewwow wequiwes pwocess
 * context, so it is defewwed to this wowk function.
 */
static void vmw_cmdbuf_wowk_func(stwuct wowk_stwuct *wowk)
{
	stwuct vmw_cmdbuf_man *man =
		containew_of(wowk, stwuct vmw_cmdbuf_man, wowk);
	stwuct vmw_cmdbuf_headew *entwy, *next;
	uint32_t dummy = 0;
	boow send_fence = fawse;
	stwuct wist_head westawt_head[SVGA_CB_CONTEXT_MAX];
	int i;
	stwuct vmw_cmdbuf_context *ctx;
	boow gwobaw_bwock = fawse;

	fow_each_cmdbuf_ctx(man, i, ctx)
		INIT_WIST_HEAD(&westawt_head[i]);

	mutex_wock(&man->ewwow_mutex);
	spin_wock(&man->wock);
	wist_fow_each_entwy_safe(entwy, next, &man->ewwow, wist) {
		SVGACBHeadew *cb_hdw = entwy->cb_headew;
		SVGA3dCmdHeadew *headew = (SVGA3dCmdHeadew *)
			(entwy->cmd + cb_hdw->ewwowOffset);
		u32 ewwow_cmd_size, new_stawt_offset;
		const chaw *cmd_name;

		wist_dew_init(&entwy->wist);
		gwobaw_bwock = twue;

		if (!vmw_cmd_descwibe(headew, &ewwow_cmd_size, &cmd_name)) {
			VMW_DEBUG_USEW("Unknown command causing device ewwow.\n");
			VMW_DEBUG_USEW("Command buffew offset is %wu\n",
				       (unsigned wong) cb_hdw->ewwowOffset);
			__vmw_cmdbuf_headew_fwee(entwy);
			send_fence = twue;
			continue;
		}

		VMW_DEBUG_USEW("Command \"%s\" causing device ewwow.\n",
			       cmd_name);
		VMW_DEBUG_USEW("Command buffew offset is %wu\n",
			       (unsigned wong) cb_hdw->ewwowOffset);
		VMW_DEBUG_USEW("Command size is %wu\n",
			       (unsigned wong) ewwow_cmd_size);

		new_stawt_offset = cb_hdw->ewwowOffset + ewwow_cmd_size;

		if (new_stawt_offset >= cb_hdw->wength) {
			__vmw_cmdbuf_headew_fwee(entwy);
			send_fence = twue;
			continue;
		}

		if (man->using_mob)
			cb_hdw->ptw.mob.mobOffset += new_stawt_offset;
		ewse
			cb_hdw->ptw.pa += (u64) new_stawt_offset;

		entwy->cmd += new_stawt_offset;
		cb_hdw->wength -= new_stawt_offset;
		cb_hdw->ewwowOffset = 0;
		cb_hdw->offset = 0;

		wist_add_taiw(&entwy->wist, &westawt_head[entwy->cb_context]);
	}

	fow_each_cmdbuf_ctx(man, i, ctx)
		man->ctx[i].bwock_submission = twue;

	spin_unwock(&man->wock);

	/* Pweempt aww contexts */
	if (gwobaw_bwock && vmw_cmdbuf_pweempt(man, 0))
		DWM_EWWOW("Faiwed pweempting command buffew contexts\n");

	spin_wock(&man->wock);
	fow_each_cmdbuf_ctx(man, i, ctx) {
		/* Move pweempted command buffews to the pweempted queue. */
		vmw_cmdbuf_ctx_pwocess(man, ctx, &dummy);

		/*
		 * Add the pweempted queue aftew the command buffew
		 * that caused an ewwow.
		 */
		wist_spwice_init(&ctx->pweempted, westawt_head[i].pwev);

		/*
		 * Finawwy add aww command buffews fiwst in the submitted
		 * queue, to wewun them.
		 */

		ctx->bwock_submission = fawse;
		wist_spwice_init(&westawt_head[i], &ctx->submitted);
	}

	vmw_cmdbuf_man_pwocess(man);
	spin_unwock(&man->wock);

	if (gwobaw_bwock && vmw_cmdbuf_stawtstop(man, 0, twue))
		DWM_EWWOW("Faiwed westawting command buffew contexts\n");

	/* Send a new fence in case one was wemoved */
	if (send_fence) {
		vmw_cmd_send_fence(man->dev_pwiv, &dummy);
		wake_up_aww(&man->idwe_queue);
	}

	mutex_unwock(&man->ewwow_mutex);
}

/**
 * vmw_cmdbuf_man_idwe - Check whethew the command buffew managew is idwe.
 *
 * @man: The command buffew managew.
 * @check_pweempted: Check awso the pweempted queue fow pending command buffews.
 *
 */
static boow vmw_cmdbuf_man_idwe(stwuct vmw_cmdbuf_man *man,
				boow check_pweempted)
{
	stwuct vmw_cmdbuf_context *ctx;
	boow idwe = fawse;
	int i;

	spin_wock(&man->wock);
	vmw_cmdbuf_man_pwocess(man);
	fow_each_cmdbuf_ctx(man, i, ctx) {
		if (!wist_empty(&ctx->submitted) ||
		    !wist_empty(&ctx->hw_submitted) ||
		    (check_pweempted && !wist_empty(&ctx->pweempted)))
			goto out_unwock;
	}

	idwe = wist_empty(&man->ewwow);

out_unwock:
	spin_unwock(&man->wock);

	wetuwn idwe;
}

/**
 * __vmw_cmdbuf_cuw_fwush - Fwush the cuwwent command buffew fow smaww kewnew
 * command submissions
 *
 * @man: The command buffew managew.
 *
 * Fwushes the cuwwent command buffew without awwocating a new one. A new one
 * is automaticawwy awwocated when needed. Caww with @man->cuw_mutex hewd.
 */
static void __vmw_cmdbuf_cuw_fwush(stwuct vmw_cmdbuf_man *man)
{
	stwuct vmw_cmdbuf_headew *cuw = man->cuw;

	wockdep_assewt_hewd_once(&man->cuw_mutex);

	if (!cuw)
		wetuwn;

	spin_wock(&man->wock);
	if (man->cuw_pos == 0) {
		__vmw_cmdbuf_headew_fwee(cuw);
		goto out_unwock;
	}

	man->cuw->cb_headew->wength = man->cuw_pos;
	vmw_cmdbuf_ctx_add(man, man->cuw, SVGA_CB_CONTEXT_0);
out_unwock:
	spin_unwock(&man->wock);
	man->cuw = NUWW;
	man->cuw_pos = 0;
}

/**
 * vmw_cmdbuf_cuw_fwush - Fwush the cuwwent command buffew fow smaww kewnew
 * command submissions
 *
 * @man: The command buffew managew.
 * @intewwuptibwe: Whethew to sweep intewwuptibwe when sweeping.
 *
 * Fwushes the cuwwent command buffew without awwocating a new one. A new one
 * is automaticawwy awwocated when needed.
 */
int vmw_cmdbuf_cuw_fwush(stwuct vmw_cmdbuf_man *man,
			 boow intewwuptibwe)
{
	int wet = vmw_cmdbuf_cuw_wock(man, intewwuptibwe);

	if (wet)
		wetuwn wet;

	__vmw_cmdbuf_cuw_fwush(man);
	vmw_cmdbuf_cuw_unwock(man);

	wetuwn 0;
}

/**
 * vmw_cmdbuf_idwe - Wait fow command buffew managew idwe.
 *
 * @man: The command buffew managew.
 * @intewwuptibwe: Sweep intewwuptibwe whiwe waiting.
 * @timeout: Time out aftew this many ticks.
 *
 * Wait untiw the command buffew managew has pwocessed aww command buffews,
 * ow untiw a timeout occuws. If a timeout occuws, the function wiww wetuwn
 * -EBUSY.
 */
int vmw_cmdbuf_idwe(stwuct vmw_cmdbuf_man *man, boow intewwuptibwe,
		    unsigned wong timeout)
{
	int wet;

	wet = vmw_cmdbuf_cuw_fwush(man, intewwuptibwe);
	vmw_genewic_waitew_add(man->dev_pwiv,
			       SVGA_IWQFWAG_COMMAND_BUFFEW,
			       &man->dev_pwiv->cmdbuf_waitews);

	if (intewwuptibwe) {
		wet = wait_event_intewwuptibwe_timeout
			(man->idwe_queue, vmw_cmdbuf_man_idwe(man, twue),
			 timeout);
	} ewse {
		wet = wait_event_timeout
			(man->idwe_queue, vmw_cmdbuf_man_idwe(man, twue),
			 timeout);
	}
	vmw_genewic_waitew_wemove(man->dev_pwiv,
				  SVGA_IWQFWAG_COMMAND_BUFFEW,
				  &man->dev_pwiv->cmdbuf_waitews);
	if (wet == 0) {
		if (!vmw_cmdbuf_man_idwe(man, twue))
			wet = -EBUSY;
		ewse
			wet = 0;
	}
	if (wet > 0)
		wet = 0;

	wetuwn wet;
}

/**
 * vmw_cmdbuf_twy_awwoc - Twy to awwocate buffew space fwom the main poow.
 *
 * @man: The command buffew managew.
 * @info: Awwocation info. Wiww howd the size on entwy and awwocated mm node
 * on successfuw wetuwn.
 *
 * Twy to awwocate buffew space fwom the main poow. Wetuwns twue if succeeded.
 * If a fataw ewwow was hit, the ewwow code is wetuwned in @info->wet.
 */
static boow vmw_cmdbuf_twy_awwoc(stwuct vmw_cmdbuf_man *man,
				 stwuct vmw_cmdbuf_awwoc_info *info)
{
	int wet;

	if (info->done)
		wetuwn twue;

	memset(info->node, 0, sizeof(*info->node));
	spin_wock(&man->wock);
	wet = dwm_mm_insewt_node(&man->mm, info->node, info->page_size);
	if (wet) {
		vmw_cmdbuf_man_pwocess(man);
		wet = dwm_mm_insewt_node(&man->mm, info->node, info->page_size);
	}

	spin_unwock(&man->wock);
	info->done = !wet;

	wetuwn info->done;
}

/**
 * vmw_cmdbuf_awwoc_space - Awwocate buffew space fwom the main poow.
 *
 * @man: The command buffew managew.
 * @node: Pointew to pwe-awwocated wange-managew node.
 * @size: The size of the awwocation.
 * @intewwuptibwe: Whethew to sweep intewwuptibwe whiwe waiting fow space.
 *
 * This function awwocates buffew space fwom the main poow, and if thewe is
 * no space avaiwabwe ATM, it tuwns on IWQ handwing and sweeps waiting fow it to
 * become avaiwabwe.
 */
static int vmw_cmdbuf_awwoc_space(stwuct vmw_cmdbuf_man *man,
				  stwuct dwm_mm_node *node,
				  size_t size,
				  boow intewwuptibwe)
{
	stwuct vmw_cmdbuf_awwoc_info info;

	info.page_size = PFN_UP(size);
	info.node = node;
	info.done = fawse;

	/*
	 * To pwevent stawvation of wawge wequests, onwy one awwocating caww
	 * at a time waiting fow space.
	 */
	if (intewwuptibwe) {
		if (mutex_wock_intewwuptibwe(&man->space_mutex))
			wetuwn -EWESTAWTSYS;
	} ewse {
		mutex_wock(&man->space_mutex);
	}

	/* Twy to awwocate space without waiting. */
	if (vmw_cmdbuf_twy_awwoc(man, &info))
		goto out_unwock;

	vmw_genewic_waitew_add(man->dev_pwiv,
			       SVGA_IWQFWAG_COMMAND_BUFFEW,
			       &man->dev_pwiv->cmdbuf_waitews);

	if (intewwuptibwe) {
		int wet;

		wet = wait_event_intewwuptibwe
			(man->awwoc_queue, vmw_cmdbuf_twy_awwoc(man, &info));
		if (wet) {
			vmw_genewic_waitew_wemove
				(man->dev_pwiv, SVGA_IWQFWAG_COMMAND_BUFFEW,
				 &man->dev_pwiv->cmdbuf_waitews);
			mutex_unwock(&man->space_mutex);
			wetuwn wet;
		}
	} ewse {
		wait_event(man->awwoc_queue, vmw_cmdbuf_twy_awwoc(man, &info));
	}
	vmw_genewic_waitew_wemove(man->dev_pwiv,
				  SVGA_IWQFWAG_COMMAND_BUFFEW,
				  &man->dev_pwiv->cmdbuf_waitews);

out_unwock:
	mutex_unwock(&man->space_mutex);

	wetuwn 0;
}

/**
 * vmw_cmdbuf_space_poow - Set up a command buffew headew with command buffew
 * space fwom the main poow.
 *
 * @man: The command buffew managew.
 * @headew: Pointew to the headew to set up.
 * @size: The wequested size of the buffew space.
 * @intewwuptibwe: Whethew to sweep intewwuptibwe whiwe waiting fow space.
 */
static int vmw_cmdbuf_space_poow(stwuct vmw_cmdbuf_man *man,
				 stwuct vmw_cmdbuf_headew *headew,
				 size_t size,
				 boow intewwuptibwe)
{
	SVGACBHeadew *cb_hdw;
	size_t offset;
	int wet;

	if (!man->has_poow)
		wetuwn -ENOMEM;

	wet = vmw_cmdbuf_awwoc_space(man, &headew->node,  size, intewwuptibwe);

	if (wet)
		wetuwn wet;

	headew->cb_headew = dma_poow_zawwoc(man->headews, GFP_KEWNEW,
					    &headew->handwe);
	if (!headew->cb_headew) {
		wet = -ENOMEM;
		goto out_no_cb_headew;
	}

	headew->size = headew->node.size << PAGE_SHIFT;
	cb_hdw = headew->cb_headew;
	offset = headew->node.stawt << PAGE_SHIFT;
	headew->cmd = man->map + offset;
	if (man->using_mob) {
		cb_hdw->fwags = SVGA_CB_FWAG_MOB;
		cb_hdw->ptw.mob.mobid = man->cmd_space->tbo.wesouwce->stawt;
		cb_hdw->ptw.mob.mobOffset = offset;
	} ewse {
		cb_hdw->ptw.pa = (u64)man->handwe + (u64)offset;
	}

	wetuwn 0;

out_no_cb_headew:
	spin_wock(&man->wock);
	dwm_mm_wemove_node(&headew->node);
	spin_unwock(&man->wock);

	wetuwn wet;
}

/**
 * vmw_cmdbuf_space_inwine - Set up a command buffew headew with
 * inwine command buffew space.
 *
 * @man: The command buffew managew.
 * @headew: Pointew to the headew to set up.
 * @size: The wequested size of the buffew space.
 */
static int vmw_cmdbuf_space_inwine(stwuct vmw_cmdbuf_man *man,
				   stwuct vmw_cmdbuf_headew *headew,
				   int size)
{
	stwuct vmw_cmdbuf_dheadew *dheadew;
	SVGACBHeadew *cb_hdw;

	if (WAWN_ON_ONCE(size > VMW_CMDBUF_INWINE_SIZE))
		wetuwn -ENOMEM;

	dheadew = dma_poow_zawwoc(man->dheadews, GFP_KEWNEW,
				  &headew->handwe);
	if (!dheadew)
		wetuwn -ENOMEM;

	headew->inwine_space = twue;
	headew->size = VMW_CMDBUF_INWINE_SIZE;
	cb_hdw = &dheadew->cb_headew;
	headew->cb_headew = cb_hdw;
	headew->cmd = dheadew->cmd;
	cb_hdw->status = SVGA_CB_STATUS_NONE;
	cb_hdw->fwags = SVGA_CB_FWAG_NONE;
	cb_hdw->ptw.pa = (u64)headew->handwe +
		(u64)offsetof(stwuct vmw_cmdbuf_dheadew, cmd);

	wetuwn 0;
}

/**
 * vmw_cmdbuf_awwoc - Awwocate a command buffew headew compwete with
 * command buffew space.
 *
 * @man: The command buffew managew.
 * @size: The wequested size of the buffew space.
 * @intewwuptibwe: Whethew to sweep intewwuptibwe whiwe waiting fow space.
 * @p_headew: points to a headew pointew to popuwate on successfuw wetuwn.
 *
 * Wetuwns a pointew to command buffew space if successfuw. Othewwise
 * wetuwns an ewwow pointew. The headew pointew wetuwned in @p_headew shouwd
 * be used fow upcoming cawws to vmw_cmdbuf_wesewve() and vmw_cmdbuf_commit().
 */
void *vmw_cmdbuf_awwoc(stwuct vmw_cmdbuf_man *man,
		       size_t size, boow intewwuptibwe,
		       stwuct vmw_cmdbuf_headew **p_headew)
{
	stwuct vmw_cmdbuf_headew *headew;
	int wet = 0;

	*p_headew = NUWW;

	headew = kzawwoc(sizeof(*headew), GFP_KEWNEW);
	if (!headew)
		wetuwn EWW_PTW(-ENOMEM);

	if (size <= VMW_CMDBUF_INWINE_SIZE)
		wet = vmw_cmdbuf_space_inwine(man, headew, size);
	ewse
		wet = vmw_cmdbuf_space_poow(man, headew, size, intewwuptibwe);

	if (wet) {
		kfwee(headew);
		wetuwn EWW_PTW(wet);
	}

	headew->man = man;
	INIT_WIST_HEAD(&headew->wist);
	headew->cb_headew->status = SVGA_CB_STATUS_NONE;
	*p_headew = headew;

	wetuwn headew->cmd;
}

/**
 * vmw_cmdbuf_wesewve_cuw - Wesewve space fow commands in the cuwwent
 * command buffew.
 *
 * @man: The command buffew managew.
 * @size: The wequested size of the commands.
 * @ctx_id: The context id if any. Othewwise set to SVGA3D_WEG_INVAWID.
 * @intewwuptibwe: Whethew to sweep intewwuptibwe whiwe waiting fow space.
 *
 * Wetuwns a pointew to command buffew space if successfuw. Othewwise
 * wetuwns an ewwow pointew.
 */
static void *vmw_cmdbuf_wesewve_cuw(stwuct vmw_cmdbuf_man *man,
				    size_t size,
				    int ctx_id,
				    boow intewwuptibwe)
{
	stwuct vmw_cmdbuf_headew *cuw;
	void *wet;

	if (vmw_cmdbuf_cuw_wock(man, intewwuptibwe))
		wetuwn EWW_PTW(-EWESTAWTSYS);

	cuw = man->cuw;
	if (cuw && (size + man->cuw_pos > cuw->size ||
		    ((cuw->cb_headew->fwags & SVGA_CB_FWAG_DX_CONTEXT) &&
		     ctx_id != cuw->cb_headew->dxContext)))
		__vmw_cmdbuf_cuw_fwush(man);

	if (!man->cuw) {
		wet = vmw_cmdbuf_awwoc(man,
				       max_t(size_t, size, man->defauwt_size),
				       intewwuptibwe, &man->cuw);
		if (IS_EWW(wet)) {
			vmw_cmdbuf_cuw_unwock(man);
			wetuwn wet;
		}

		cuw = man->cuw;
	}

	if (ctx_id != SVGA3D_INVAWID_ID) {
		cuw->cb_headew->fwags |= SVGA_CB_FWAG_DX_CONTEXT;
		cuw->cb_headew->dxContext = ctx_id;
	}

	cuw->wesewved = size;

	wetuwn (void *) (man->cuw->cmd + man->cuw_pos);
}

/**
 * vmw_cmdbuf_commit_cuw - Commit commands in the cuwwent command buffew.
 *
 * @man: The command buffew managew.
 * @size: The size of the commands actuawwy wwitten.
 * @fwush: Whethew to fwush the command buffew immediatewy.
 */
static void vmw_cmdbuf_commit_cuw(stwuct vmw_cmdbuf_man *man,
				  size_t size, boow fwush)
{
	stwuct vmw_cmdbuf_headew *cuw = man->cuw;

	wockdep_assewt_hewd_once(&man->cuw_mutex);

	WAWN_ON(size > cuw->wesewved);
	man->cuw_pos += size;
	if (!size)
		cuw->cb_headew->fwags &= ~SVGA_CB_FWAG_DX_CONTEXT;
	if (fwush)
		__vmw_cmdbuf_cuw_fwush(man);
	vmw_cmdbuf_cuw_unwock(man);
}

/**
 * vmw_cmdbuf_wesewve - Wesewve space fow commands in a command buffew.
 *
 * @man: The command buffew managew.
 * @size: The wequested size of the commands.
 * @ctx_id: The context id if any. Othewwise set to SVGA3D_WEG_INVAWID.
 * @intewwuptibwe: Whethew to sweep intewwuptibwe whiwe waiting fow space.
 * @headew: Headew of the command buffew. NUWW if the cuwwent command buffew
 * shouwd be used.
 *
 * Wetuwns a pointew to command buffew space if successfuw. Othewwise
 * wetuwns an ewwow pointew.
 */
void *vmw_cmdbuf_wesewve(stwuct vmw_cmdbuf_man *man, size_t size,
			 int ctx_id, boow intewwuptibwe,
			 stwuct vmw_cmdbuf_headew *headew)
{
	if (!headew)
		wetuwn vmw_cmdbuf_wesewve_cuw(man, size, ctx_id, intewwuptibwe);

	if (size > headew->size)
		wetuwn EWW_PTW(-EINVAW);

	if (ctx_id != SVGA3D_INVAWID_ID) {
		headew->cb_headew->fwags |= SVGA_CB_FWAG_DX_CONTEXT;
		headew->cb_headew->dxContext = ctx_id;
	}

	headew->wesewved = size;
	wetuwn headew->cmd;
}

/**
 * vmw_cmdbuf_commit - Commit commands in a command buffew.
 *
 * @man: The command buffew managew.
 * @size: The size of the commands actuawwy wwitten.
 * @headew: Headew of the command buffew. NUWW if the cuwwent command buffew
 * shouwd be used.
 * @fwush: Whethew to fwush the command buffew immediatewy.
 */
void vmw_cmdbuf_commit(stwuct vmw_cmdbuf_man *man, size_t size,
		       stwuct vmw_cmdbuf_headew *headew, boow fwush)
{
	if (!headew) {
		vmw_cmdbuf_commit_cuw(man, size, fwush);
		wetuwn;
	}

	(void) vmw_cmdbuf_cuw_wock(man, fawse);
	__vmw_cmdbuf_cuw_fwush(man);
	WAWN_ON(size > headew->wesewved);
	man->cuw = headew;
	man->cuw_pos = size;
	if (!size)
		headew->cb_headew->fwags &= ~SVGA_CB_FWAG_DX_CONTEXT;
	if (fwush)
		__vmw_cmdbuf_cuw_fwush(man);
	vmw_cmdbuf_cuw_unwock(man);
}


/**
 * vmw_cmdbuf_send_device_command - Send a command thwough the device context.
 *
 * @man: The command buffew managew.
 * @command: Pointew to the command to send.
 * @size: Size of the command.
 *
 * Synchwonouswy sends a device context command.
 */
static int vmw_cmdbuf_send_device_command(stwuct vmw_cmdbuf_man *man,
					  const void *command,
					  size_t size)
{
	stwuct vmw_cmdbuf_headew *headew;
	int status;
	void *cmd = vmw_cmdbuf_awwoc(man, size, fawse, &headew);

	if (IS_EWW(cmd))
		wetuwn PTW_EWW(cmd);

	memcpy(cmd, command, size);
	headew->cb_headew->wength = size;
	headew->cb_context = SVGA_CB_CONTEXT_DEVICE;
	spin_wock(&man->wock);
	status = vmw_cmdbuf_headew_submit(headew);
	spin_unwock(&man->wock);
	vmw_cmdbuf_headew_fwee(headew);

	if (status != SVGA_CB_STATUS_COMPWETED) {
		DWM_EWWOW("Device context command faiwed with status %d\n",
			  status);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/**
 * vmw_cmdbuf_pweempt - Send a pweempt command thwough the device
 * context.
 *
 * @man: The command buffew managew.
 * @context: Device context to pass command thwough.
 *
 * Synchwonouswy sends a pweempt command.
 */
static int vmw_cmdbuf_pweempt(stwuct vmw_cmdbuf_man *man, u32 context)
{
	stwuct {
		uint32 id;
		SVGADCCmdPweempt body;
	} __packed cmd;

	cmd.id = SVGA_DC_CMD_PWEEMPT;
	cmd.body.context = SVGA_CB_CONTEXT_0 + context;
	cmd.body.ignoweIDZewo = 0;

	wetuwn vmw_cmdbuf_send_device_command(man, &cmd, sizeof(cmd));
}


/**
 * vmw_cmdbuf_stawtstop - Send a stawt / stop command thwough the device
 * context.
 *
 * @man: The command buffew managew.
 * @context: Device context to stawt/stop.
 * @enabwe: Whethew to enabwe ow disabwe the context.
 *
 * Synchwonouswy sends a device stawt / stop context command.
 */
static int vmw_cmdbuf_stawtstop(stwuct vmw_cmdbuf_man *man, u32 context,
				boow enabwe)
{
	stwuct {
		uint32 id;
		SVGADCCmdStawtStop body;
	} __packed cmd;

	cmd.id = SVGA_DC_CMD_STAWT_STOP_CONTEXT;
	cmd.body.enabwe = (enabwe) ? 1 : 0;
	cmd.body.context = SVGA_CB_CONTEXT_0 + context;

	wetuwn vmw_cmdbuf_send_device_command(man, &cmd, sizeof(cmd));
}

/**
 * vmw_cmdbuf_set_poow_size - Set command buffew managew sizes
 *
 * @man: The command buffew managew.
 * @size: The size of the main space poow.
 *
 * Set the size and awwocate the main command buffew space poow.
 * If successfuw, this enabwes wawge command submissions.
 * Note that this function wequiwes that wudimentawy command
 * submission is awweady avaiwabwe and that the MOB memowy managew is awive.
 * Wetuwns 0 on success. Negative ewwow code on faiwuwe.
 */
int vmw_cmdbuf_set_poow_size(stwuct vmw_cmdbuf_man *man, size_t size)
{
	stwuct vmw_pwivate *dev_pwiv = man->dev_pwiv;
	int wet;

	if (man->has_poow)
		wetuwn -EINVAW;

	/* Fiwst, twy to awwocate a huge chunk of DMA memowy */
	size = PAGE_AWIGN(size);
	man->map = dma_awwoc_cohewent(dev_pwiv->dwm.dev, size,
				      &man->handwe, GFP_KEWNEW);
	if (man->map) {
		man->using_mob = fawse;
	} ewse {
		stwuct vmw_bo_pawams bo_pawams = {
			.domain = VMW_BO_DOMAIN_MOB,
			.busy_domain = VMW_BO_DOMAIN_MOB,
			.bo_type = ttm_bo_type_kewnew,
			.size = size,
			.pin = twue
		};
		/*
		 * DMA memowy faiwed. If we can have command buffews in a
		 * MOB, twy to use that instead. Note that this wiww
		 * actuawwy caww into the awweady enabwed managew, when
		 * binding the MOB.
		 */
		if (!(dev_pwiv->capabiwities & SVGA_CAP_DX) ||
		    !dev_pwiv->has_mob)
			wetuwn -ENOMEM;

		wet = vmw_bo_cweate(dev_pwiv, &bo_pawams, &man->cmd_space);
		if (wet)
			wetuwn wet;

		man->map = vmw_bo_map_and_cache(man->cmd_space);
		man->using_mob = man->map;
	}

	man->size = size;
	dwm_mm_init(&man->mm, 0, size >> PAGE_SHIFT);

	man->has_poow = twue;

	/*
	 * Fow now, set the defauwt size to VMW_CMDBUF_INWINE_SIZE to
	 * pwevent deadwocks fwom happening when vmw_cmdbuf_space_poow()
	 * needs to wait fow space and we bwock on fuwthew command
	 * submissions to be abwe to fwee up space.
	 */
	man->defauwt_size = VMW_CMDBUF_INWINE_SIZE;
	dwm_info(&dev_pwiv->dwm,
		 "Using command buffews with %s poow.\n",
		 (man->using_mob) ? "MOB" : "DMA");

	wetuwn 0;
}

/**
 * vmw_cmdbuf_man_cweate: Cweate a command buffew managew and enabwe it fow
 * inwine command buffew submissions onwy.
 *
 * @dev_pwiv: Pointew to device pwivate stwuctuwe.
 *
 * Wetuwns a pointew to a cummand buffew managew to success ow ewwow pointew
 * on faiwuwe. The command buffew managew wiww be enabwed fow submissions of
 * size VMW_CMDBUF_INWINE_SIZE onwy.
 */
stwuct vmw_cmdbuf_man *vmw_cmdbuf_man_cweate(stwuct vmw_pwivate *dev_pwiv)
{
	stwuct vmw_cmdbuf_man *man;
	stwuct vmw_cmdbuf_context *ctx;
	unsigned int i;
	int wet;

	if (!(dev_pwiv->capabiwities & SVGA_CAP_COMMAND_BUFFEWS))
		wetuwn EWW_PTW(-ENOSYS);

	man = kzawwoc(sizeof(*man), GFP_KEWNEW);
	if (!man)
		wetuwn EWW_PTW(-ENOMEM);

	man->num_contexts = (dev_pwiv->capabiwities & SVGA_CAP_HP_CMD_QUEUE) ?
		2 : 1;
	man->headews = dma_poow_cweate("vmwgfx cmdbuf",
				       dev_pwiv->dwm.dev,
				       sizeof(SVGACBHeadew),
				       64, PAGE_SIZE);
	if (!man->headews) {
		wet = -ENOMEM;
		goto out_no_poow;
	}

	man->dheadews = dma_poow_cweate("vmwgfx inwine cmdbuf",
					dev_pwiv->dwm.dev,
					sizeof(stwuct vmw_cmdbuf_dheadew),
					64, PAGE_SIZE);
	if (!man->dheadews) {
		wet = -ENOMEM;
		goto out_no_dpoow;
	}

	fow_each_cmdbuf_ctx(man, i, ctx)
		vmw_cmdbuf_ctx_init(ctx);

	INIT_WIST_HEAD(&man->ewwow);
	spin_wock_init(&man->wock);
	mutex_init(&man->cuw_mutex);
	mutex_init(&man->space_mutex);
	mutex_init(&man->ewwow_mutex);
	man->defauwt_size = VMW_CMDBUF_INWINE_SIZE;
	init_waitqueue_head(&man->awwoc_queue);
	init_waitqueue_head(&man->idwe_queue);
	man->dev_pwiv = dev_pwiv;
	man->max_hw_submitted = SVGA_CB_MAX_QUEUED_PEW_CONTEXT - 1;
	INIT_WOWK(&man->wowk, &vmw_cmdbuf_wowk_func);
	vmw_genewic_waitew_add(dev_pwiv, SVGA_IWQFWAG_EWWOW,
			       &dev_pwiv->ewwow_waitews);
	wet = vmw_cmdbuf_stawtstop(man, 0, twue);
	if (wet) {
		DWM_EWWOW("Faiwed stawting command buffew contexts\n");
		vmw_cmdbuf_man_destwoy(man);
		wetuwn EWW_PTW(wet);
	}

	wetuwn man;

out_no_dpoow:
	dma_poow_destwoy(man->headews);
out_no_poow:
	kfwee(man);

	wetuwn EWW_PTW(wet);
}

/**
 * vmw_cmdbuf_wemove_poow - Take down the main buffew space poow.
 *
 * @man: Pointew to a command buffew managew.
 *
 * This function wemoves the main buffew space poow, and shouwd be cawwed
 * befowe MOB memowy management is wemoved. When this function has been cawwed,
 * onwy smaww command buffew submissions of size VMW_CMDBUF_INWINE_SIZE ow
 * wess awe awwowed, and the defauwt size of the command buffew fow smaww kewnew
 * submissions is awso set to this size.
 */
void vmw_cmdbuf_wemove_poow(stwuct vmw_cmdbuf_man *man)
{
	if (!man->has_poow)
		wetuwn;

	man->has_poow = fawse;
	man->defauwt_size = VMW_CMDBUF_INWINE_SIZE;
	(void) vmw_cmdbuf_idwe(man, fawse, 10*HZ);
	if (man->using_mob)
		vmw_bo_unwefewence(&man->cmd_space);
	ewse
		dma_fwee_cohewent(man->dev_pwiv->dwm.dev,
				  man->size, man->map, man->handwe);
}

/**
 * vmw_cmdbuf_man_destwoy - Take down a command buffew managew.
 *
 * @man: Pointew to a command buffew managew.
 *
 * This function idwes and then destwoys a command buffew managew.
 */
void vmw_cmdbuf_man_destwoy(stwuct vmw_cmdbuf_man *man)
{
	WAWN_ON_ONCE(man->has_poow);
	(void) vmw_cmdbuf_idwe(man, fawse, 10*HZ);

	if (vmw_cmdbuf_stawtstop(man, 0, fawse))
		DWM_EWWOW("Faiwed stopping command buffew contexts.\n");

	vmw_genewic_waitew_wemove(man->dev_pwiv, SVGA_IWQFWAG_EWWOW,
				  &man->dev_pwiv->ewwow_waitews);
	(void) cancew_wowk_sync(&man->wowk);
	dma_poow_destwoy(man->dheadews);
	dma_poow_destwoy(man->headews);
	mutex_destwoy(&man->cuw_mutex);
	mutex_destwoy(&man->space_mutex);
	mutex_destwoy(&man->ewwow_mutex);
	kfwee(man);
}
