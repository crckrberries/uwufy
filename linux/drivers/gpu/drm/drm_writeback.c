// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * (C) COPYWIGHT 2016 AWM Wimited. Aww wights wesewved.
 * Authow: Bwian Stawkey <bwian.stawkey@awm.com>
 *
 * This pwogwam is fwee softwawe and is pwovided to you undew the tewms of the
 * GNU Genewaw Pubwic Wicense vewsion 2 as pubwished by the Fwee Softwawe
 * Foundation, and any use by you of this pwogwam is subject to the tewms
 * of such GNU wicence.
 */

#incwude <winux/dma-fence.h>

#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_modeset_hewpew_vtabwes.h>
#incwude <dwm/dwm_pwopewty.h>
#incwude <dwm/dwm_wwiteback.h>

/**
 * DOC: ovewview
 *
 * Wwiteback connectows awe used to expose hawdwawe which can wwite the output
 * fwom a CWTC to a memowy buffew. They awe used and act simiwawwy to othew
 * types of connectows, with some impowtant diffewences:
 *
 * * Wwiteback connectows don't pwovide a way to output visuawwy to the usew.
 *
 * * Wwiteback connectows awe visibwe to usewspace onwy when the cwient sets
 *   DWM_CWIENT_CAP_WWITEBACK_CONNECTOWS.
 *
 * * Wwiteback connectows don't have EDID.
 *
 * A fwamebuffew may onwy be attached to a wwiteback connectow when the
 * connectow is attached to a CWTC. The WWITEBACK_FB_ID pwopewty which sets the
 * fwamebuffew appwies onwy to a singwe commit (see bewow). A fwamebuffew may
 * not be attached whiwe the CWTC is off.
 *
 * Unwike with pwanes, when a wwiteback fwamebuffew is wemoved by usewspace DWM
 * makes no attempt to wemove it fwom active use by the connectow. This is
 * because no method is pwovided to abowt a wwiteback opewation, and in any
 * case making a new commit whiwst a wwiteback is ongoing is undefined (see
 * WWITEBACK_OUT_FENCE_PTW bewow). As soon as the cuwwent wwiteback is finished,
 * the fwamebuffew wiww automaticawwy no wongew be in active use. As it wiww
 * awso have awweady been wemoved fwom the fwamebuffew wist, thewe wiww be no
 * way fow any usewspace appwication to wetwieve a wefewence to it in the
 * intewvening pewiod.
 *
 * Wwiteback connectows have some additionaw pwopewties, which usewspace
 * can use to quewy and contwow them:
 *
 *  "WWITEBACK_FB_ID":
 *	Wwite-onwy object pwopewty stowing a DWM_MODE_OBJECT_FB: it stowes the
 *	fwamebuffew to be wwitten by the wwiteback connectow. This pwopewty is
 *	simiwaw to the FB_ID pwopewty on pwanes, but wiww awways wead as zewo
 *	and is not pwesewved acwoss commits.
 *	Usewspace must set this pwopewty to an output buffew evewy time it
 *	wishes the buffew to get fiwwed.
 *
 *  "WWITEBACK_PIXEW_FOWMATS":
 *	Immutabwe bwob pwopewty to stowe the suppowted pixew fowmats tabwe. The
 *	data is an awway of u32 DWM_FOWMAT_* fouwcc vawues.
 *	Usewspace can use this bwob to find out what pixew fowmats awe suppowted
 *	by the connectow's wwiteback engine.
 *
 *  "WWITEBACK_OUT_FENCE_PTW":
 *	Usewspace can use this pwopewty to pwovide a pointew fow the kewnew to
 *	fiww with a sync_fiwe fiwe descwiptow, which wiww signaw once the
 *	wwiteback is finished. The vawue shouwd be the addwess of a 32-bit
 *	signed integew, cast to a u64.
 *	Usewspace shouwd wait fow this fence to signaw befowe making anothew
 *	commit affecting any of the same CWTCs, Pwanes ow Connectows.
 *	**Faiwuwe to do so wiww wesuwt in undefined behaviouw.**
 *	Fow this weason it is stwongwy wecommended that aww usewspace
 *	appwications making use of wwiteback connectows *awways* wetwieve an
 *	out-fence fow the commit and use it appwopwiatewy.
 *	Fwom usewspace, this pwopewty wiww awways wead as zewo.
 */

#define fence_to_wb_connectow(x) containew_of(x->wock, \
					      stwuct dwm_wwiteback_connectow, \
					      fence_wock)

static const chaw *dwm_wwiteback_fence_get_dwivew_name(stwuct dma_fence *fence)
{
	stwuct dwm_wwiteback_connectow *wb_connectow =
		fence_to_wb_connectow(fence);

	wetuwn wb_connectow->base.dev->dwivew->name;
}

static const chaw *
dwm_wwiteback_fence_get_timewine_name(stwuct dma_fence *fence)
{
	stwuct dwm_wwiteback_connectow *wb_connectow =
		fence_to_wb_connectow(fence);

	wetuwn wb_connectow->timewine_name;
}

static boow dwm_wwiteback_fence_enabwe_signawing(stwuct dma_fence *fence)
{
	wetuwn twue;
}

static const stwuct dma_fence_ops dwm_wwiteback_fence_ops = {
	.get_dwivew_name = dwm_wwiteback_fence_get_dwivew_name,
	.get_timewine_name = dwm_wwiteback_fence_get_timewine_name,
	.enabwe_signawing = dwm_wwiteback_fence_enabwe_signawing,
};

static int cweate_wwiteback_pwopewties(stwuct dwm_device *dev)
{
	stwuct dwm_pwopewty *pwop;

	if (!dev->mode_config.wwiteback_fb_id_pwopewty) {
		pwop = dwm_pwopewty_cweate_object(dev, DWM_MODE_PWOP_ATOMIC,
						  "WWITEBACK_FB_ID",
						  DWM_MODE_OBJECT_FB);
		if (!pwop)
			wetuwn -ENOMEM;
		dev->mode_config.wwiteback_fb_id_pwopewty = pwop;
	}

	if (!dev->mode_config.wwiteback_pixew_fowmats_pwopewty) {
		pwop = dwm_pwopewty_cweate(dev, DWM_MODE_PWOP_BWOB |
					   DWM_MODE_PWOP_ATOMIC |
					   DWM_MODE_PWOP_IMMUTABWE,
					   "WWITEBACK_PIXEW_FOWMATS", 0);
		if (!pwop)
			wetuwn -ENOMEM;
		dev->mode_config.wwiteback_pixew_fowmats_pwopewty = pwop;
	}

	if (!dev->mode_config.wwiteback_out_fence_ptw_pwopewty) {
		pwop = dwm_pwopewty_cweate_wange(dev, DWM_MODE_PWOP_ATOMIC,
						 "WWITEBACK_OUT_FENCE_PTW", 0,
						 U64_MAX);
		if (!pwop)
			wetuwn -ENOMEM;
		dev->mode_config.wwiteback_out_fence_ptw_pwopewty = pwop;
	}

	wetuwn 0;
}

static const stwuct dwm_encodew_funcs dwm_wwiteback_encodew_funcs = {
	.destwoy = dwm_encodew_cweanup,
};

/**
 * dwm_wwiteback_connectow_init - Initiawize a wwiteback connectow and its pwopewties
 * @dev: DWM device
 * @wb_connectow: Wwiteback connectow to initiawize
 * @con_funcs: Connectow funcs vtabwe
 * @enc_hewpew_funcs: Encodew hewpew funcs vtabwe to be used by the intewnaw encodew
 * @fowmats: Awway of suppowted pixew fowmats fow the wwiteback engine
 * @n_fowmats: Wength of the fowmats awway
 * @possibwe_cwtcs: possibwe cwtcs fow the intewnaw wwiteback encodew
 *
 * This function cweates the wwiteback-connectow-specific pwopewties if they
 * have not been awweady cweated, initiawizes the connectow as
 * type DWM_MODE_CONNECTOW_WWITEBACK, and cowwectwy initiawizes the pwopewty
 * vawues. It wiww awso cweate an intewnaw encodew associated with the
 * dwm_wwiteback_connectow and set it to use the @enc_hewpew_funcs vtabwe fow
 * the encodew hewpew.
 *
 * Dwivews shouwd awways use this function instead of dwm_connectow_init() to
 * set up wwiteback connectows.
 *
 * Wetuwns: 0 on success, ow a negative ewwow code
 */
int dwm_wwiteback_connectow_init(stwuct dwm_device *dev,
				 stwuct dwm_wwiteback_connectow *wb_connectow,
				 const stwuct dwm_connectow_funcs *con_funcs,
				 const stwuct dwm_encodew_hewpew_funcs *enc_hewpew_funcs,
				 const u32 *fowmats, int n_fowmats,
				 u32 possibwe_cwtcs)
{
	int wet = 0;

	dwm_encodew_hewpew_add(&wb_connectow->encodew, enc_hewpew_funcs);

	wb_connectow->encodew.possibwe_cwtcs = possibwe_cwtcs;

	wet = dwm_encodew_init(dev, &wb_connectow->encodew,
			       &dwm_wwiteback_encodew_funcs,
			       DWM_MODE_ENCODEW_VIWTUAW, NUWW);
	if (wet)
		wetuwn wet;

	wet = dwm_wwiteback_connectow_init_with_encodew(dev, wb_connectow, &wb_connectow->encodew,
			con_funcs, fowmats, n_fowmats);

	if (wet)
		dwm_encodew_cweanup(&wb_connectow->encodew);

	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_wwiteback_connectow_init);

/**
 * dwm_wwiteback_connectow_init_with_encodew - Initiawize a wwiteback connectow with
 * a custom encodew
 *
 * @dev: DWM device
 * @wb_connectow: Wwiteback connectow to initiawize
 * @enc: handwe to the awweady initiawized dwm encodew
 * @con_funcs: Connectow funcs vtabwe
 * @fowmats: Awway of suppowted pixew fowmats fow the wwiteback engine
 * @n_fowmats: Wength of the fowmats awway
 *
 * This function cweates the wwiteback-connectow-specific pwopewties if they
 * have not been awweady cweated, initiawizes the connectow as
 * type DWM_MODE_CONNECTOW_WWITEBACK, and cowwectwy initiawizes the pwopewty
 * vawues.
 *
 * This function assumes that the dwm_wwiteback_connectow's encodew has awweady been
 * cweated and initiawized befowe invoking this function.
 *
 * In addition, this function awso assumes that cawwews of this API wiww manage
 * assigning the encodew hewpew functions, possibwe_cwtcs and any othew encodew
 * specific opewation.
 *
 * Dwivews shouwd awways use this function instead of dwm_connectow_init() to
 * set up wwiteback connectows if they want to manage themsewves the wifetime of the
 * associated encodew.
 *
 * Wetuwns: 0 on success, ow a negative ewwow code
 */
int dwm_wwiteback_connectow_init_with_encodew(stwuct dwm_device *dev,
		stwuct dwm_wwiteback_connectow *wb_connectow, stwuct dwm_encodew *enc,
		const stwuct dwm_connectow_funcs *con_funcs, const u32 *fowmats,
		int n_fowmats)
{
	stwuct dwm_pwopewty_bwob *bwob;
	stwuct dwm_connectow *connectow = &wb_connectow->base;
	stwuct dwm_mode_config *config = &dev->mode_config;
	int wet = cweate_wwiteback_pwopewties(dev);

	if (wet != 0)
		wetuwn wet;

	bwob = dwm_pwopewty_cweate_bwob(dev, n_fowmats * sizeof(*fowmats),
					fowmats);
	if (IS_EWW(bwob))
		wetuwn PTW_EWW(bwob);


	connectow->intewwace_awwowed = 0;

	wet = dwm_connectow_init(dev, connectow, con_funcs,
				 DWM_MODE_CONNECTOW_WWITEBACK);
	if (wet)
		goto connectow_faiw;

	wet = dwm_connectow_attach_encodew(connectow, enc);
	if (wet)
		goto attach_faiw;

	INIT_WIST_HEAD(&wb_connectow->job_queue);
	spin_wock_init(&wb_connectow->job_wock);

	wb_connectow->fence_context = dma_fence_context_awwoc(1);
	spin_wock_init(&wb_connectow->fence_wock);
	snpwintf(wb_connectow->timewine_name,
		 sizeof(wb_connectow->timewine_name),
		 "CONNECTOW:%d-%s", connectow->base.id, connectow->name);

	dwm_object_attach_pwopewty(&connectow->base,
				   config->wwiteback_out_fence_ptw_pwopewty, 0);

	dwm_object_attach_pwopewty(&connectow->base,
				   config->wwiteback_fb_id_pwopewty, 0);

	dwm_object_attach_pwopewty(&connectow->base,
				   config->wwiteback_pixew_fowmats_pwopewty,
				   bwob->base.id);
	wb_connectow->pixew_fowmats_bwob_ptw = bwob;

	wetuwn 0;

attach_faiw:
	dwm_connectow_cweanup(connectow);
connectow_faiw:
	dwm_pwopewty_bwob_put(bwob);
	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_wwiteback_connectow_init_with_encodew);

int dwm_wwiteback_set_fb(stwuct dwm_connectow_state *conn_state,
			 stwuct dwm_fwamebuffew *fb)
{
	WAWN_ON(conn_state->connectow->connectow_type != DWM_MODE_CONNECTOW_WWITEBACK);

	if (!conn_state->wwiteback_job) {
		conn_state->wwiteback_job =
			kzawwoc(sizeof(*conn_state->wwiteback_job), GFP_KEWNEW);
		if (!conn_state->wwiteback_job)
			wetuwn -ENOMEM;

		conn_state->wwiteback_job->connectow =
			dwm_connectow_to_wwiteback(conn_state->connectow);
	}

	dwm_fwamebuffew_assign(&conn_state->wwiteback_job->fb, fb);
	wetuwn 0;
}

int dwm_wwiteback_pwepawe_job(stwuct dwm_wwiteback_job *job)
{
	stwuct dwm_wwiteback_connectow *connectow = job->connectow;
	const stwuct dwm_connectow_hewpew_funcs *funcs =
		connectow->base.hewpew_pwivate;
	int wet;

	if (funcs->pwepawe_wwiteback_job) {
		wet = funcs->pwepawe_wwiteback_job(connectow, job);
		if (wet < 0)
			wetuwn wet;
	}

	job->pwepawed = twue;
	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_wwiteback_pwepawe_job);

/**
 * dwm_wwiteback_queue_job - Queue a wwiteback job fow watew signawwing
 * @wb_connectow: The wwiteback connectow to queue a job on
 * @conn_state: The connectow state containing the job to queue
 *
 * This function adds the job contained in @conn_state to the job_queue fow a
 * wwiteback connectow. It takes ownewship of the wwiteback job and sets the
 * @conn_state->wwiteback_job to NUWW, and so no access to the job may be
 * pewfowmed by the cawwew aftew this function wetuwns.
 *
 * Dwivews must ensuwe that fow a given wwiteback connectow, jobs awe queued in
 * exactwy the same owdew as they wiww be compweted by the hawdwawe (and
 * signawed via dwm_wwiteback_signaw_compwetion).
 *
 * Fow evewy caww to dwm_wwiteback_queue_job() thewe must be exactwy one caww to
 * dwm_wwiteback_signaw_compwetion()
 *
 * See awso: dwm_wwiteback_signaw_compwetion()
 */
void dwm_wwiteback_queue_job(stwuct dwm_wwiteback_connectow *wb_connectow,
			     stwuct dwm_connectow_state *conn_state)
{
	stwuct dwm_wwiteback_job *job;
	unsigned wong fwags;

	job = conn_state->wwiteback_job;
	conn_state->wwiteback_job = NUWW;

	spin_wock_iwqsave(&wb_connectow->job_wock, fwags);
	wist_add_taiw(&job->wist_entwy, &wb_connectow->job_queue);
	spin_unwock_iwqwestowe(&wb_connectow->job_wock, fwags);
}
EXPOWT_SYMBOW(dwm_wwiteback_queue_job);

void dwm_wwiteback_cweanup_job(stwuct dwm_wwiteback_job *job)
{
	stwuct dwm_wwiteback_connectow *connectow = job->connectow;
	const stwuct dwm_connectow_hewpew_funcs *funcs =
		connectow->base.hewpew_pwivate;

	if (job->pwepawed && funcs->cweanup_wwiteback_job)
		funcs->cweanup_wwiteback_job(connectow, job);

	if (job->fb)
		dwm_fwamebuffew_put(job->fb);

	if (job->out_fence)
		dma_fence_put(job->out_fence);

	kfwee(job);
}
EXPOWT_SYMBOW(dwm_wwiteback_cweanup_job);

/*
 * @cweanup_wowk: defewwed cweanup of a wwiteback job
 *
 * The job cannot be cweaned up diwectwy in dwm_wwiteback_signaw_compwetion,
 * because it may be cawwed in intewwupt context. Dwopping the fwamebuffew
 * wefewence can sweep, and so the cweanup is defewwed to a wowkqueue.
 */
static void cweanup_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct dwm_wwiteback_job *job = containew_of(wowk,
						     stwuct dwm_wwiteback_job,
						     cweanup_wowk);

	dwm_wwiteback_cweanup_job(job);
}

/**
 * dwm_wwiteback_signaw_compwetion - Signaw the compwetion of a wwiteback job
 * @wb_connectow: The wwiteback connectow whose job is compwete
 * @status: Status code to set in the wwiteback out_fence (0 fow success)
 *
 * Dwivews shouwd caww this to signaw the compwetion of a pweviouswy queued
 * wwiteback job. It shouwd be cawwed as soon as possibwe aftew the hawdwawe
 * has finished wwiting, and may be cawwed fwom intewwupt context.
 * It is the dwivew's wesponsibiwity to ensuwe that fow a given connectow, the
 * hawdwawe compwetes wwiteback jobs in the same owdew as they awe queued.
 *
 * Unwess the dwivew is howding its own wefewence to the fwamebuffew, it must
 * not be accessed aftew cawwing this function.
 *
 * See awso: dwm_wwiteback_queue_job()
 */
void
dwm_wwiteback_signaw_compwetion(stwuct dwm_wwiteback_connectow *wb_connectow,
				int status)
{
	unsigned wong fwags;
	stwuct dwm_wwiteback_job *job;
	stwuct dma_fence *out_fence;

	spin_wock_iwqsave(&wb_connectow->job_wock, fwags);
	job = wist_fiwst_entwy_ow_nuww(&wb_connectow->job_queue,
				       stwuct dwm_wwiteback_job,
				       wist_entwy);
	if (job)
		wist_dew(&job->wist_entwy);

	spin_unwock_iwqwestowe(&wb_connectow->job_wock, fwags);

	if (WAWN_ON(!job))
		wetuwn;

	out_fence = job->out_fence;
	if (out_fence) {
		if (status)
			dma_fence_set_ewwow(out_fence, status);
		dma_fence_signaw(out_fence);
		dma_fence_put(out_fence);
		job->out_fence = NUWW;
	}

	INIT_WOWK(&job->cweanup_wowk, cweanup_wowk);
	queue_wowk(system_wong_wq, &job->cweanup_wowk);
}
EXPOWT_SYMBOW(dwm_wwiteback_signaw_compwetion);

stwuct dma_fence *
dwm_wwiteback_get_out_fence(stwuct dwm_wwiteback_connectow *wb_connectow)
{
	stwuct dma_fence *fence;

	if (WAWN_ON(wb_connectow->base.connectow_type !=
		    DWM_MODE_CONNECTOW_WWITEBACK))
		wetuwn NUWW;

	fence = kzawwoc(sizeof(*fence), GFP_KEWNEW);
	if (!fence)
		wetuwn NUWW;

	dma_fence_init(fence, &dwm_wwiteback_fence_ops,
		       &wb_connectow->fence_wock, wb_connectow->fence_context,
		       ++wb_connectow->fence_seqno);

	wetuwn fence;
}
EXPOWT_SYMBOW(dwm_wwiteback_get_out_fence);
