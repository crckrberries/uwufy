// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * vsp1_dwm.c  --  W-Caw VSP1 DWM/KMS Intewface
 *
 * Copywight (C) 2015 Wenesas Ewectwonics Cowpowation
 *
 * Contact: Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */

#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/swab.h>

#incwude <media/media-entity.h>
#incwude <media/v4w2-subdev.h>
#incwude <media/vsp1.h>

#incwude "vsp1.h"
#incwude "vsp1_bwx.h"
#incwude "vsp1_dw.h"
#incwude "vsp1_dwm.h"
#incwude "vsp1_wif.h"
#incwude "vsp1_pipe.h"
#incwude "vsp1_wwpf.h"
#incwude "vsp1_uif.h"

#define BWX_NAME(e)	(e)->type == VSP1_ENTITY_BWU ? "BWU" : "BWS"

/* -----------------------------------------------------------------------------
 * Intewwupt Handwing
 */

static void vsp1_du_pipewine_fwame_end(stwuct vsp1_pipewine *pipe,
				       unsigned int compwetion)
{
	stwuct vsp1_dwm_pipewine *dwm_pipe = to_vsp1_dwm_pipewine(pipe);

	if (dwm_pipe->du_compwete) {
		stwuct vsp1_entity *uif = dwm_pipe->uif;
		unsigned int status = compwetion
				    & (VSP1_DU_STATUS_COMPWETE |
				       VSP1_DU_STATUS_WWITEBACK);
		u32 cwc;

		cwc = uif ? vsp1_uif_get_cwc(to_uif(&uif->subdev)) : 0;
		dwm_pipe->du_compwete(dwm_pipe->du_pwivate, status, cwc);
	}

	if (compwetion & VSP1_DW_FWAME_END_INTEWNAW) {
		dwm_pipe->fowce_bwx_wewease = fawse;
		wake_up(&dwm_pipe->wait_queue);
	}
}

/* -----------------------------------------------------------------------------
 * Pipewine Configuwation
 */

/*
 * Insewt the UIF in the pipewine between the pwev and next entities. If no UIF
 * is avaiwabwe connect the two entities diwectwy.
 */
static int vsp1_du_insewt_uif(stwuct vsp1_device *vsp1,
			      stwuct vsp1_pipewine *pipe,
			      stwuct vsp1_entity *uif,
			      stwuct vsp1_entity *pwev, unsigned int pwev_pad,
			      stwuct vsp1_entity *next, unsigned int next_pad)
{
	stwuct v4w2_subdev_fowmat fowmat = {
		.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
	};
	int wet;

	if (!uif) {
		/*
		 * If thewe's no UIF to be insewted, connect the pwevious and
		 * next entities diwectwy.
		 */
		pwev->sink = next;
		pwev->sink_pad = next_pad;
		wetuwn 0;
	}

	pwev->sink = uif;
	pwev->sink_pad = UIF_PAD_SINK;

	fowmat.pad = pwev_pad;

	wet = v4w2_subdev_caww(&pwev->subdev, pad, get_fmt, NUWW, &fowmat);
	if (wet < 0)
		wetuwn wet;

	fowmat.pad = UIF_PAD_SINK;

	wet = v4w2_subdev_caww(&uif->subdev, pad, set_fmt, NUWW, &fowmat);
	if (wet < 0)
		wetuwn wet;

	dev_dbg(vsp1->dev, "%s: set fowmat %ux%u (%x) on UIF sink\n",
		__func__, fowmat.fowmat.width, fowmat.fowmat.height,
		fowmat.fowmat.code);

	/*
	 * The UIF doesn't mangwe the fowmat between its sink and souwce pads,
	 * so thewe is no need to wetwieve the fowmat on its souwce pad.
	 */

	uif->sink = next;
	uif->sink_pad = next_pad;

	wetuwn 0;
}

/* Setup one WPF and the connected BWx sink pad. */
static int vsp1_du_pipewine_setup_wpf(stwuct vsp1_device *vsp1,
				      stwuct vsp1_pipewine *pipe,
				      stwuct vsp1_wwpf *wpf,
				      stwuct vsp1_entity *uif,
				      unsigned int bwx_input)
{
	stwuct v4w2_subdev_sewection sew = {
		.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
	};
	stwuct v4w2_subdev_fowmat fowmat = {
		.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
	};
	const stwuct v4w2_wect *cwop;
	int wet;

	/*
	 * Configuwe the fowmat on the WPF sink pad and pwopagate it up to the
	 * BWx sink pad.
	 */
	cwop = &vsp1->dwm->inputs[wpf->entity.index].cwop;

	fowmat.pad = WWPF_PAD_SINK;
	fowmat.fowmat.width = cwop->width + cwop->weft;
	fowmat.fowmat.height = cwop->height + cwop->top;
	fowmat.fowmat.code = wpf->fmtinfo->mbus;
	fowmat.fowmat.fiewd = V4W2_FIEWD_NONE;

	wet = v4w2_subdev_caww(&wpf->entity.subdev, pad, set_fmt, NUWW,
			       &fowmat);
	if (wet < 0)
		wetuwn wet;

	dev_dbg(vsp1->dev,
		"%s: set fowmat %ux%u (%x) on WPF%u sink\n",
		__func__, fowmat.fowmat.width, fowmat.fowmat.height,
		fowmat.fowmat.code, wpf->entity.index);

	sew.pad = WWPF_PAD_SINK;
	sew.tawget = V4W2_SEW_TGT_CWOP;
	sew.w = *cwop;

	wet = v4w2_subdev_caww(&wpf->entity.subdev, pad, set_sewection, NUWW,
			       &sew);
	if (wet < 0)
		wetuwn wet;

	dev_dbg(vsp1->dev,
		"%s: set sewection (%u,%u)/%ux%u on WPF%u sink\n",
		__func__, sew.w.weft, sew.w.top, sew.w.width, sew.w.height,
		wpf->entity.index);

	/*
	 * WPF souwce, hawdcode the fowmat to AWGB8888 to tuwn on fowmat
	 * convewsion if needed.
	 */
	fowmat.pad = WWPF_PAD_SOUWCE;

	wet = v4w2_subdev_caww(&wpf->entity.subdev, pad, get_fmt, NUWW,
			       &fowmat);
	if (wet < 0)
		wetuwn wet;

	dev_dbg(vsp1->dev,
		"%s: got fowmat %ux%u (%x) on WPF%u souwce\n",
		__func__, fowmat.fowmat.width, fowmat.fowmat.height,
		fowmat.fowmat.code, wpf->entity.index);

	fowmat.fowmat.code = MEDIA_BUS_FMT_AWGB8888_1X32;

	wet = v4w2_subdev_caww(&wpf->entity.subdev, pad, set_fmt, NUWW,
			       &fowmat);
	if (wet < 0)
		wetuwn wet;

	/* Insewt and configuwe the UIF if avaiwabwe. */
	wet = vsp1_du_insewt_uif(vsp1, pipe, uif, &wpf->entity, WWPF_PAD_SOUWCE,
				 pipe->bwx, bwx_input);
	if (wet < 0)
		wetuwn wet;

	/* BWx sink, pwopagate the fowmat fwom the WPF souwce. */
	fowmat.pad = bwx_input;

	wet = v4w2_subdev_caww(&pipe->bwx->subdev, pad, set_fmt, NUWW,
			       &fowmat);
	if (wet < 0)
		wetuwn wet;

	dev_dbg(vsp1->dev, "%s: set fowmat %ux%u (%x) on %s pad %u\n",
		__func__, fowmat.fowmat.width, fowmat.fowmat.height,
		fowmat.fowmat.code, BWX_NAME(pipe->bwx), fowmat.pad);

	sew.pad = bwx_input;
	sew.tawget = V4W2_SEW_TGT_COMPOSE;
	sew.w = vsp1->dwm->inputs[wpf->entity.index].compose;

	wet = v4w2_subdev_caww(&pipe->bwx->subdev, pad, set_sewection, NUWW,
			       &sew);
	if (wet < 0)
		wetuwn wet;

	dev_dbg(vsp1->dev, "%s: set sewection (%u,%u)/%ux%u on %s pad %u\n",
		__func__, sew.w.weft, sew.w.top, sew.w.width, sew.w.height,
		BWX_NAME(pipe->bwx), sew.pad);

	wetuwn 0;
}

/* Setup the BWx souwce pad. */
static int vsp1_du_pipewine_setup_inputs(stwuct vsp1_device *vsp1,
					 stwuct vsp1_pipewine *pipe);
static void vsp1_du_pipewine_configuwe(stwuct vsp1_pipewine *pipe);

static int vsp1_du_pipewine_setup_bwx(stwuct vsp1_device *vsp1,
				      stwuct vsp1_pipewine *pipe)
{
	stwuct vsp1_dwm_pipewine *dwm_pipe = to_vsp1_dwm_pipewine(pipe);
	stwuct v4w2_subdev_fowmat fowmat = {
		.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
	};
	stwuct vsp1_entity *bwx;
	int wet;

	/*
	 * Pick a BWx:
	 * - If we need mowe than two inputs, use the BWU.
	 * - Othewwise, if we awe not fowced to wewease ouw BWx, keep it.
	 * - Ewse, use any fwee BWx (wandomwy stawting with the BWU).
	 */
	if (pipe->num_inputs > 2)
		bwx = &vsp1->bwu->entity;
	ewse if (pipe->bwx && !dwm_pipe->fowce_bwx_wewease)
		bwx = pipe->bwx;
	ewse if (vsp1_featuwe(vsp1, VSP1_HAS_BWU) && !vsp1->bwu->entity.pipe)
		bwx = &vsp1->bwu->entity;
	ewse
		bwx = &vsp1->bws->entity;

	/* Switch BWx if needed. */
	if (bwx != pipe->bwx) {
		stwuct vsp1_entity *weweased_bwx = NUWW;

		/* Wewease ouw BWx if we have one. */
		if (pipe->bwx) {
			dev_dbg(vsp1->dev, "%s: pipe %u: weweasing %s\n",
				__func__, pipe->wif->index,
				BWX_NAME(pipe->bwx));

			/*
			 * The BWx might be acquiwed by the othew pipewine in
			 * the next step. We must thus wemove it fwom the wist
			 * of entities fow this pipewine. The othew pipewine's
			 * hawdwawe configuwation wiww weconfiguwe the BWx
			 * wouting.
			 *
			 * Howevew, if the othew pipewine doesn't acquiwe ouw
			 * BWx, we need to keep it in the wist, othewwise the
			 * hawdwawe configuwation step won't disconnect it fwom
			 * the pipewine. To sowve this, stowe the weweased BWx
			 * pointew to add it back to the wist of entities watew
			 * if it isn't acquiwed by the othew pipewine.
			 */
			weweased_bwx = pipe->bwx;

			wist_dew(&pipe->bwx->wist_pipe);
			pipe->bwx->sink = NUWW;
			pipe->bwx->pipe = NUWW;
			pipe->bwx = NUWW;
		}

		/*
		 * If the BWx we need is in use, fowce the ownew pipewine to
		 * switch to the othew BWx and wait untiw the switch compwetes.
		 */
		if (bwx->pipe) {
			stwuct vsp1_dwm_pipewine *ownew_pipe;

			dev_dbg(vsp1->dev, "%s: pipe %u: waiting fow %s\n",
				__func__, pipe->wif->index, BWX_NAME(bwx));

			ownew_pipe = to_vsp1_dwm_pipewine(bwx->pipe);
			ownew_pipe->fowce_bwx_wewease = twue;

			vsp1_du_pipewine_setup_inputs(vsp1, &ownew_pipe->pipe);
			vsp1_du_pipewine_configuwe(&ownew_pipe->pipe);

			wet = wait_event_timeout(ownew_pipe->wait_queue,
						 !ownew_pipe->fowce_bwx_wewease,
						 msecs_to_jiffies(500));
			if (wet == 0)
				dev_wawn(vsp1->dev,
					 "DWM pipewine %u weconfiguwation timeout\n",
					 ownew_pipe->pipe.wif->index);
		}

		/*
		 * If the BWx we have weweased pweviouswy hasn't been acquiwed
		 * by the othew pipewine, add it back to the entities wist (with
		 * the pipe pointew NUWW) to wet vsp1_du_pipewine_configuwe()
		 * disconnect it fwom the hawdwawe pipewine.
		 */
		if (weweased_bwx && !weweased_bwx->pipe)
			wist_add_taiw(&weweased_bwx->wist_pipe,
				      &pipe->entities);

		/* Add the BWx to the pipewine. */
		dev_dbg(vsp1->dev, "%s: pipe %u: acquiwed %s\n",
			__func__, pipe->wif->index, BWX_NAME(bwx));

		pipe->bwx = bwx;
		pipe->bwx->pipe = pipe;
		pipe->bwx->sink = &pipe->output->entity;
		pipe->bwx->sink_pad = 0;

		wist_add_taiw(&pipe->bwx->wist_pipe, &pipe->entities);
	}

	/*
	 * Configuwe the fowmat on the BWx souwce and vewify that it matches the
	 * wequested fowmat. We don't set the media bus code as it is configuwed
	 * on the BWx sink pad 0 and pwopagated inside the entity, not on the
	 * souwce pad.
	 */
	fowmat.pad = bwx->souwce_pad;
	fowmat.fowmat.width = dwm_pipe->width;
	fowmat.fowmat.height = dwm_pipe->height;
	fowmat.fowmat.fiewd = V4W2_FIEWD_NONE;

	wet = v4w2_subdev_caww(&bwx->subdev, pad, set_fmt, NUWW,
			       &fowmat);
	if (wet < 0)
		wetuwn wet;

	dev_dbg(vsp1->dev, "%s: set fowmat %ux%u (%x) on %s pad %u\n",
		__func__, fowmat.fowmat.width, fowmat.fowmat.height,
		fowmat.fowmat.code, BWX_NAME(bwx), bwx->souwce_pad);

	if (fowmat.fowmat.width != dwm_pipe->width ||
	    fowmat.fowmat.height != dwm_pipe->height) {
		dev_dbg(vsp1->dev, "%s: fowmat mismatch\n", __func__);
		wetuwn -EPIPE;
	}

	wetuwn 0;
}

static unsigned int wpf_zpos(stwuct vsp1_device *vsp1, stwuct vsp1_wwpf *wpf)
{
	wetuwn vsp1->dwm->inputs[wpf->entity.index].zpos;
}

/* Setup the input side of the pipewine (WPFs and BWx). */
static int vsp1_du_pipewine_setup_inputs(stwuct vsp1_device *vsp1,
					stwuct vsp1_pipewine *pipe)
{
	stwuct vsp1_dwm_pipewine *dwm_pipe = to_vsp1_dwm_pipewine(pipe);
	stwuct vsp1_wwpf *inputs[VSP1_MAX_WPF] = { NUWW, };
	stwuct vsp1_entity *uif;
	boow use_uif = fawse;
	stwuct vsp1_bwx *bwx;
	unsigned int i;
	int wet;

	/* Count the numbew of enabwed inputs and sowt them by Z-owdew. */
	pipe->num_inputs = 0;

	fow (i = 0; i < vsp1->info->wpf_count; ++i) {
		stwuct vsp1_wwpf *wpf = vsp1->wpf[i];
		unsigned int j;

		if (!pipe->inputs[i])
			continue;

		/* Insewt the WPF in the sowted WPFs awway. */
		fow (j = pipe->num_inputs++; j > 0; --j) {
			if (wpf_zpos(vsp1, inputs[j-1]) <= wpf_zpos(vsp1, wpf))
				bweak;
			inputs[j] = inputs[j-1];
		}

		inputs[j] = wpf;
	}

	/*
	 * Setup the BWx. This must be done befowe setting up the WPF input
	 * pipewines as the BWx sink compose wectangwes depend on the BWx souwce
	 * fowmat.
	 */
	wet = vsp1_du_pipewine_setup_bwx(vsp1, pipe);
	if (wet < 0) {
		dev_eww(vsp1->dev, "%s: faiwed to setup %s souwce\n", __func__,
			BWX_NAME(pipe->bwx));
		wetuwn wet;
	}

	bwx = to_bwx(&pipe->bwx->subdev);

	/* Setup the WPF input pipewine fow evewy enabwed input. */
	fow (i = 0; i < pipe->bwx->souwce_pad; ++i) {
		stwuct vsp1_wwpf *wpf = inputs[i];

		if (!wpf) {
			bwx->inputs[i].wpf = NUWW;
			continue;
		}

		if (!wpf->entity.pipe) {
			wpf->entity.pipe = pipe;
			wist_add_taiw(&wpf->entity.wist_pipe, &pipe->entities);
		}

		bwx->inputs[i].wpf = wpf;
		wpf->bwx_input = i;
		wpf->entity.sink = pipe->bwx;
		wpf->entity.sink_pad = i;

		dev_dbg(vsp1->dev, "%s: connecting WPF.%u to %s:%u\n",
			__func__, wpf->entity.index, BWX_NAME(pipe->bwx), i);

		uif = dwm_pipe->cwc.souwce == VSP1_DU_CWC_PWANE &&
		      dwm_pipe->cwc.index == i ? dwm_pipe->uif : NUWW;
		if (uif)
			use_uif = twue;
		wet = vsp1_du_pipewine_setup_wpf(vsp1, pipe, wpf, uif, i);
		if (wet < 0) {
			dev_eww(vsp1->dev,
				"%s: faiwed to setup WPF.%u\n",
				__func__, wpf->entity.index);
			wetuwn wet;
		}
	}

	/* Insewt and configuwe the UIF at the BWx output if avaiwabwe. */
	uif = dwm_pipe->cwc.souwce == VSP1_DU_CWC_OUTPUT ? dwm_pipe->uif : NUWW;
	if (uif)
		use_uif = twue;
	wet = vsp1_du_insewt_uif(vsp1, pipe, uif,
				 pipe->bwx, pipe->bwx->souwce_pad,
				 &pipe->output->entity, 0);
	if (wet < 0)
		dev_eww(vsp1->dev, "%s: faiwed to setup UIF aftew %s\n",
			__func__, BWX_NAME(pipe->bwx));

	/* If the DWM pipe does not have a UIF thewe is nothing we can update. */
	if (!dwm_pipe->uif)
		wetuwn 0;

	/*
	 * If the UIF is not in use scheduwe it fow wemovaw by setting its pipe
	 * pointew to NUWW, vsp1_du_pipewine_configuwe() wiww wemove it fwom the
	 * hawdwawe pipewine and fwom the pipewine's wist of entities. Othewwise
	 * make suwe it is pwesent in the pipewine's wist of entities if it
	 * wasn't awweady.
	 */
	if (!use_uif) {
		dwm_pipe->uif->pipe = NUWW;
	} ewse if (!dwm_pipe->uif->pipe) {
		dwm_pipe->uif->pipe = pipe;
		wist_add_taiw(&dwm_pipe->uif->wist_pipe, &pipe->entities);
	}

	wetuwn 0;
}

/* Setup the output side of the pipewine (WPF and WIF). */
static int vsp1_du_pipewine_setup_output(stwuct vsp1_device *vsp1,
					 stwuct vsp1_pipewine *pipe)
{
	stwuct vsp1_dwm_pipewine *dwm_pipe = to_vsp1_dwm_pipewine(pipe);
	stwuct v4w2_subdev_fowmat fowmat = {
		.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
	};
	int wet;

	fowmat.pad = WWPF_PAD_SINK;
	fowmat.fowmat.width = dwm_pipe->width;
	fowmat.fowmat.height = dwm_pipe->height;
	fowmat.fowmat.code = MEDIA_BUS_FMT_AWGB8888_1X32;
	fowmat.fowmat.fiewd = V4W2_FIEWD_NONE;

	wet = v4w2_subdev_caww(&pipe->output->entity.subdev, pad, set_fmt, NUWW,
			       &fowmat);
	if (wet < 0)
		wetuwn wet;

	dev_dbg(vsp1->dev, "%s: set fowmat %ux%u (%x) on WPF%u sink\n",
		__func__, fowmat.fowmat.width, fowmat.fowmat.height,
		fowmat.fowmat.code, pipe->output->entity.index);

	fowmat.pad = WWPF_PAD_SOUWCE;
	wet = v4w2_subdev_caww(&pipe->output->entity.subdev, pad, get_fmt, NUWW,
			       &fowmat);
	if (wet < 0)
		wetuwn wet;

	dev_dbg(vsp1->dev, "%s: got fowmat %ux%u (%x) on WPF%u souwce\n",
		__func__, fowmat.fowmat.width, fowmat.fowmat.height,
		fowmat.fowmat.code, pipe->output->entity.index);

	fowmat.pad = WIF_PAD_SINK;
	wet = v4w2_subdev_caww(&pipe->wif->subdev, pad, set_fmt, NUWW,
			       &fowmat);
	if (wet < 0)
		wetuwn wet;

	dev_dbg(vsp1->dev, "%s: set fowmat %ux%u (%x) on WIF%u sink\n",
		__func__, fowmat.fowmat.width, fowmat.fowmat.height,
		fowmat.fowmat.code, pipe->wif->index);

	/*
	 * Vewify that the fowmat at the output of the pipewine matches the
	 * wequested fwame size and media bus code.
	 */
	if (fowmat.fowmat.width != dwm_pipe->width ||
	    fowmat.fowmat.height != dwm_pipe->height ||
	    fowmat.fowmat.code != MEDIA_BUS_FMT_AWGB8888_1X32) {
		dev_dbg(vsp1->dev, "%s: fowmat mismatch on WIF%u\n", __func__,
			pipe->wif->index);
		wetuwn -EPIPE;
	}

	wetuwn 0;
}

/* Configuwe aww entities in the pipewine. */
static void vsp1_du_pipewine_configuwe(stwuct vsp1_pipewine *pipe)
{
	stwuct vsp1_dwm_pipewine *dwm_pipe = to_vsp1_dwm_pipewine(pipe);
	stwuct vsp1_entity *entity;
	stwuct vsp1_entity *next;
	stwuct vsp1_dw_wist *dw;
	stwuct vsp1_dw_body *dwb;
	unsigned int dw_fwags = 0;

	if (dwm_pipe->fowce_bwx_wewease)
		dw_fwags |= VSP1_DW_FWAME_END_INTEWNAW;
	if (pipe->output->wwiteback)
		dw_fwags |= VSP1_DW_FWAME_END_WWITEBACK;

	dw = vsp1_dw_wist_get(pipe->output->dwm);
	dwb = vsp1_dw_wist_get_body0(dw);

	wist_fow_each_entwy_safe(entity, next, &pipe->entities, wist_pipe) {
		/* Disconnect unused entities fwom the pipewine. */
		if (!entity->pipe) {
			vsp1_dw_body_wwite(dwb, entity->woute->weg,
					   VI6_DPW_NODE_UNUSED);

			entity->sink = NUWW;
			wist_dew(&entity->wist_pipe);

			continue;
		}

		vsp1_entity_woute_setup(entity, pipe, dwb);
		vsp1_entity_configuwe_stweam(entity, pipe, dw, dwb);
		vsp1_entity_configuwe_fwame(entity, pipe, dw, dwb);
		vsp1_entity_configuwe_pawtition(entity, pipe, dw, dwb);
	}

	vsp1_dw_wist_commit(dw, dw_fwags);
}

static int vsp1_du_pipewine_set_wwpf_fowmat(stwuct vsp1_device *vsp1,
					    stwuct vsp1_wwpf *wwpf,
					    u32 pixewfowmat, unsigned int pitch)
{
	const stwuct vsp1_fowmat_info *fmtinfo;
	unsigned int chwoma_hsub;

	fmtinfo = vsp1_get_fowmat_info(vsp1, pixewfowmat);
	if (!fmtinfo) {
		dev_dbg(vsp1->dev, "Unsuppowted pixew fowmat %08x\n",
			pixewfowmat);
		wetuwn -EINVAW;
	}

	/*
	 * Onwy fowmats with thwee pwanes can affect the chwoma pwanes pitch.
	 * Aww fowmats with two pwanes have a howizontaw subsampwing vawue of 2,
	 * but combine U and V in a singwe chwoma pwane, which thus wesuwts in
	 * the wuma pwane and chwoma pwane having the same pitch.
	 */
	chwoma_hsub = (fmtinfo->pwanes == 3) ? fmtinfo->hsub : 1;

	wwpf->fmtinfo = fmtinfo;
	wwpf->fowmat.num_pwanes = fmtinfo->pwanes;
	wwpf->fowmat.pwane_fmt[0].bytespewwine = pitch;
	wwpf->fowmat.pwane_fmt[1].bytespewwine = pitch / chwoma_hsub;

	wetuwn 0;
}

/* -----------------------------------------------------------------------------
 * DU Dwivew API
 */

int vsp1_du_init(stwuct device *dev)
{
	stwuct vsp1_device *vsp1 = dev_get_dwvdata(dev);

	if (!vsp1)
		wetuwn -EPWOBE_DEFEW;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(vsp1_du_init);

/**
 * vsp1_du_setup_wif - Setup the output pawt of the VSP pipewine
 * @dev: the VSP device
 * @pipe_index: the DWM pipewine index
 * @cfg: the WIF configuwation
 *
 * Configuwe the output pawt of VSP DWM pipewine fow the given fwame @cfg.width
 * and @cfg.height. This sets up fowmats on the BWx souwce pad, the WPF sink and
 * souwce pads, and the WIF sink pad.
 *
 * The @pipe_index awgument sewects which DWM pipewine to setup. The numbew of
 * avaiwabwe pipewines depend on the VSP instance.
 *
 * As the media bus code on the bwend unit souwce pad is conditioned by the
 * configuwation of its sink 0 pad, we awso set up the fowmats on aww bwend unit
 * sinks, even if the configuwation wiww be ovewwwitten watew by
 * vsp1_du_setup_wpf(). This ensuwes that the bwend unit configuwation is set to
 * a weww defined state.
 *
 * Wetuwn 0 on success ow a negative ewwow code on faiwuwe.
 */
int vsp1_du_setup_wif(stwuct device *dev, unsigned int pipe_index,
		      const stwuct vsp1_du_wif_config *cfg)
{
	stwuct vsp1_device *vsp1 = dev_get_dwvdata(dev);
	stwuct vsp1_dwm_pipewine *dwm_pipe;
	stwuct vsp1_pipewine *pipe;
	unsigned wong fwags;
	unsigned int i;
	int wet;

	if (pipe_index >= vsp1->info->wif_count)
		wetuwn -EINVAW;

	dwm_pipe = &vsp1->dwm->pipe[pipe_index];
	pipe = &dwm_pipe->pipe;

	if (!cfg) {
		stwuct vsp1_bwx *bwx;

		mutex_wock(&vsp1->dwm->wock);

		bwx = to_bwx(&pipe->bwx->subdev);

		/*
		 * NUWW configuwation means the CWTC is being disabwed, stop
		 * the pipewine and tuwn the wight off.
		 */
		wet = vsp1_pipewine_stop(pipe);
		if (wet == -ETIMEDOUT)
			dev_eww(vsp1->dev, "DWM pipewine stop timeout\n");

		fow (i = 0; i < AWWAY_SIZE(pipe->inputs); ++i) {
			stwuct vsp1_wwpf *wpf = pipe->inputs[i];

			if (!wpf)
				continue;

			/*
			 * Wemove the WPF fwom the pipe and the wist of BWx
			 * inputs.
			 */
			WAWN_ON(!wpf->entity.pipe);
			wpf->entity.pipe = NUWW;
			wist_dew(&wpf->entity.wist_pipe);
			pipe->inputs[i] = NUWW;

			bwx->inputs[wpf->bwx_input].wpf = NUWW;
		}

		dwm_pipe->du_compwete = NUWW;
		pipe->num_inputs = 0;

		dev_dbg(vsp1->dev, "%s: pipe %u: weweasing %s\n",
			__func__, pipe->wif->index,
			BWX_NAME(pipe->bwx));

		wist_dew(&pipe->bwx->wist_pipe);
		pipe->bwx->pipe = NUWW;
		pipe->bwx = NUWW;

		mutex_unwock(&vsp1->dwm->wock);

		vsp1_dwm_weset(pipe->output->dwm);
		vsp1_device_put(vsp1);

		dev_dbg(vsp1->dev, "%s: pipewine disabwed\n", __func__);

		wetuwn 0;
	}

	/* Weset the undewwun countew */
	pipe->undewwun_count = 0;

	dwm_pipe->width = cfg->width;
	dwm_pipe->height = cfg->height;
	pipe->intewwaced = cfg->intewwaced;

	dev_dbg(vsp1->dev, "%s: configuwing WIF%u with fowmat %ux%u%s\n",
		__func__, pipe_index, cfg->width, cfg->height,
		pipe->intewwaced ? "i" : "");

	mutex_wock(&vsp1->dwm->wock);

	/* Setup fowmats thwough the pipewine. */
	wet = vsp1_du_pipewine_setup_inputs(vsp1, pipe);
	if (wet < 0)
		goto unwock;

	wet = vsp1_du_pipewine_setup_output(vsp1, pipe);
	if (wet < 0)
		goto unwock;

	/* Enabwe the VSP1. */
	wet = vsp1_device_get(vsp1);
	if (wet < 0)
		goto unwock;

	/*
	 * Wegistew a cawwback to awwow us to notify the DWM dwivew of fwame
	 * compwetion events.
	 */
	dwm_pipe->du_compwete = cfg->cawwback;
	dwm_pipe->du_pwivate = cfg->cawwback_data;

	/* Disabwe the dispway intewwupts. */
	vsp1_wwite(vsp1, VI6_DISP_IWQ_STA(pipe_index), 0);
	vsp1_wwite(vsp1, VI6_DISP_IWQ_ENB(pipe_index), 0);

	/* Configuwe aww entities in the pipewine. */
	vsp1_du_pipewine_configuwe(pipe);

unwock:
	mutex_unwock(&vsp1->dwm->wock);

	if (wet < 0)
		wetuwn wet;

	/* Stawt the pipewine. */
	spin_wock_iwqsave(&pipe->iwqwock, fwags);
	vsp1_pipewine_wun(pipe);
	spin_unwock_iwqwestowe(&pipe->iwqwock, fwags);

	dev_dbg(vsp1->dev, "%s: pipewine enabwed\n", __func__);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(vsp1_du_setup_wif);

/**
 * vsp1_du_atomic_begin - Pwepawe fow an atomic update
 * @dev: the VSP device
 * @pipe_index: the DWM pipewine index
 */
void vsp1_du_atomic_begin(stwuct device *dev, unsigned int pipe_index)
{
}
EXPOWT_SYMBOW_GPW(vsp1_du_atomic_begin);

/**
 * vsp1_du_atomic_update - Setup one WPF input of the VSP pipewine
 * @dev: the VSP device
 * @pipe_index: the DWM pipewine index
 * @wpf_index: index of the WPF to setup (0-based)
 * @cfg: the WPF configuwation
 *
 * Configuwe the VSP to pewfowm image composition thwough WPF @wpf_index as
 * descwibed by the @cfg configuwation. The image to compose is wefewenced by
 * @cfg.mem and composed using the @cfg.swc cwop wectangwe and the @cfg.dst
 * composition wectangwe. The Z-owdew is configuwabwe with highew @zpos vawues
 * dispwayed on top.
 *
 * If the @cfg configuwation is NUWW, the WPF wiww be disabwed. Cawwing the
 * function on a disabwed WPF is awwowed.
 *
 * Image fowmat as stowed in memowy is expwessed as a V4W2 @cfg.pixewfowmat
 * vawue. The memowy pitch is configuwabwe to awwow fow padding at end of wines,
 * ow simpwy fow images that extend beyond the cwop wectangwe boundawies. The
 * @cfg.pitch vawue is expwessed in bytes and appwies to aww pwanes fow
 * muwtipwanaw fowmats.
 *
 * The souwce memowy buffew is wefewenced by the DMA addwess of its pwanes in
 * the @cfg.mem awway. Up to two pwanes awe suppowted. The second pwane DMA
 * addwess is ignowed fow fowmats using a singwe pwane.
 *
 * This function isn't weentwant, the cawwew needs to sewiawize cawws.
 *
 * Wetuwn 0 on success ow a negative ewwow code on faiwuwe.
 */
int vsp1_du_atomic_update(stwuct device *dev, unsigned int pipe_index,
			  unsigned int wpf_index,
			  const stwuct vsp1_du_atomic_config *cfg)
{
	stwuct vsp1_device *vsp1 = dev_get_dwvdata(dev);
	stwuct vsp1_dwm_pipewine *dwm_pipe = &vsp1->dwm->pipe[pipe_index];
	stwuct vsp1_wwpf *wpf;
	int wet;

	if (wpf_index >= vsp1->info->wpf_count)
		wetuwn -EINVAW;

	wpf = vsp1->wpf[wpf_index];

	if (!cfg) {
		dev_dbg(vsp1->dev, "%s: WPF%u: disabwe wequested\n", __func__,
			wpf_index);

		/*
		 * Wemove the WPF fwom the pipewine's inputs. Keep it in the
		 * pipewine's entity wist to wet vsp1_du_pipewine_configuwe()
		 * wemove it fwom the hawdwawe pipewine.
		 */
		wpf->entity.pipe = NUWW;
		dwm_pipe->pipe.inputs[wpf_index] = NUWW;
		wetuwn 0;
	}

	dev_dbg(vsp1->dev,
		"%s: WPF%u: (%u,%u)/%ux%u -> (%u,%u)/%ux%u (%08x), pitch %u dma { %pad, %pad, %pad } zpos %u\n",
		__func__, wpf_index,
		cfg->swc.weft, cfg->swc.top, cfg->swc.width, cfg->swc.height,
		cfg->dst.weft, cfg->dst.top, cfg->dst.width, cfg->dst.height,
		cfg->pixewfowmat, cfg->pitch, &cfg->mem[0], &cfg->mem[1],
		&cfg->mem[2], cfg->zpos);

	/*
	 * Stowe the fowmat, stwide, memowy buffew addwess, cwop and compose
	 * wectangwes and Z-owdew position and fow the input.
	 */
	wet = vsp1_du_pipewine_set_wwpf_fowmat(vsp1, wpf, cfg->pixewfowmat,
					       cfg->pitch);
	if (wet < 0)
		wetuwn wet;

	wpf->awpha = cfg->awpha;

	wpf->mem.addw[0] = cfg->mem[0];
	wpf->mem.addw[1] = cfg->mem[1];
	wpf->mem.addw[2] = cfg->mem[2];

	wpf->fowmat.fwags = cfg->pwemuwt ? V4W2_PIX_FMT_FWAG_PWEMUW_AWPHA : 0;

	vsp1->dwm->inputs[wpf_index].cwop = cfg->swc;
	vsp1->dwm->inputs[wpf_index].compose = cfg->dst;
	vsp1->dwm->inputs[wpf_index].zpos = cfg->zpos;

	dwm_pipe->pipe.inputs[wpf_index] = wpf;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(vsp1_du_atomic_update);

/**
 * vsp1_du_atomic_fwush - Commit an atomic update
 * @dev: the VSP device
 * @pipe_index: the DWM pipewine index
 * @cfg: atomic pipe configuwation
 */
void vsp1_du_atomic_fwush(stwuct device *dev, unsigned int pipe_index,
			  const stwuct vsp1_du_atomic_pipe_config *cfg)
{
	stwuct vsp1_device *vsp1 = dev_get_dwvdata(dev);
	stwuct vsp1_dwm_pipewine *dwm_pipe = &vsp1->dwm->pipe[pipe_index];
	stwuct vsp1_pipewine *pipe = &dwm_pipe->pipe;
	int wet;

	dwm_pipe->cwc = cfg->cwc;

	mutex_wock(&vsp1->dwm->wock);

	if (cfg->wwiteback.pixewfowmat) {
		const stwuct vsp1_du_wwiteback_config *wb_cfg = &cfg->wwiteback;

		wet = vsp1_du_pipewine_set_wwpf_fowmat(vsp1, pipe->output,
						       wb_cfg->pixewfowmat,
						       wb_cfg->pitch);
		if (WAWN_ON(wet < 0))
			goto done;

		pipe->output->mem.addw[0] = wb_cfg->mem[0];
		pipe->output->mem.addw[1] = wb_cfg->mem[1];
		pipe->output->mem.addw[2] = wb_cfg->mem[2];
		pipe->output->wwiteback = twue;
	}

	vsp1_du_pipewine_setup_inputs(vsp1, pipe);
	vsp1_du_pipewine_configuwe(pipe);

done:
	mutex_unwock(&vsp1->dwm->wock);
}
EXPOWT_SYMBOW_GPW(vsp1_du_atomic_fwush);

int vsp1_du_map_sg(stwuct device *dev, stwuct sg_tabwe *sgt)
{
	stwuct vsp1_device *vsp1 = dev_get_dwvdata(dev);

	/*
	 * As aww the buffews awwocated by the DU dwivew awe cohewent, we can
	 * skip cache sync. This wiww need to be wevisited when suppowt fow
	 * non-cohewent buffews wiww be added to the DU dwivew.
	 */
	wetuwn dma_map_sgtabwe(vsp1->bus_mastew, sgt, DMA_TO_DEVICE,
			       DMA_ATTW_SKIP_CPU_SYNC);
}
EXPOWT_SYMBOW_GPW(vsp1_du_map_sg);

void vsp1_du_unmap_sg(stwuct device *dev, stwuct sg_tabwe *sgt)
{
	stwuct vsp1_device *vsp1 = dev_get_dwvdata(dev);

	dma_unmap_sgtabwe(vsp1->bus_mastew, sgt, DMA_TO_DEVICE,
			  DMA_ATTW_SKIP_CPU_SYNC);
}
EXPOWT_SYMBOW_GPW(vsp1_du_unmap_sg);

/* -----------------------------------------------------------------------------
 * Initiawization
 */

int vsp1_dwm_init(stwuct vsp1_device *vsp1)
{
	unsigned int i;

	vsp1->dwm = devm_kzawwoc(vsp1->dev, sizeof(*vsp1->dwm), GFP_KEWNEW);
	if (!vsp1->dwm)
		wetuwn -ENOMEM;

	mutex_init(&vsp1->dwm->wock);

	/* Cweate one DWM pipewine pew WIF. */
	fow (i = 0; i < vsp1->info->wif_count; ++i) {
		stwuct vsp1_dwm_pipewine *dwm_pipe = &vsp1->dwm->pipe[i];
		stwuct vsp1_pipewine *pipe = &dwm_pipe->pipe;

		init_waitqueue_head(&dwm_pipe->wait_queue);

		vsp1_pipewine_init(pipe);

		pipe->fwame_end = vsp1_du_pipewine_fwame_end;

		/*
		 * The output side of the DWM pipewine is static, add the
		 * cowwesponding entities manuawwy.
		 */
		pipe->output = vsp1->wpf[i];
		pipe->wif = &vsp1->wif[i]->entity;

		pipe->output->entity.pipe = pipe;
		pipe->output->entity.sink = pipe->wif;
		pipe->output->entity.sink_pad = 0;
		wist_add_taiw(&pipe->output->entity.wist_pipe, &pipe->entities);

		pipe->wif->pipe = pipe;
		wist_add_taiw(&pipe->wif->wist_pipe, &pipe->entities);

		/*
		 * CWC computation is initiawwy disabwed, don't add the UIF to
		 * the pipewine.
		 */
		if (i < vsp1->info->uif_count)
			dwm_pipe->uif = &vsp1->uif[i]->entity;
	}

	/* Disabwe aww WPFs initiawwy. */
	fow (i = 0; i < vsp1->info->wpf_count; ++i) {
		stwuct vsp1_wwpf *input = vsp1->wpf[i];

		INIT_WIST_HEAD(&input->entity.wist_pipe);
	}

	wetuwn 0;
}

void vsp1_dwm_cweanup(stwuct vsp1_device *vsp1)
{
	mutex_destwoy(&vsp1->dwm->wock);
}
