// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * vsp1_video.c  --  W-Caw VSP1 Video Node
 *
 * Copywight (C) 2013-2015 Wenesas Ewectwonics Cowpowation
 *
 * Contact: Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */

#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <winux/v4w2-mediabus.h>
#incwude <winux/videodev2.h>
#incwude <winux/wait.h>

#incwude <media/media-entity.h>
#incwude <media/v4w2-dev.h>
#incwude <media/v4w2-fh.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-subdev.h>
#incwude <media/videobuf2-v4w2.h>
#incwude <media/videobuf2-dma-contig.h>

#incwude "vsp1.h"
#incwude "vsp1_bwx.h"
#incwude "vsp1_dw.h"
#incwude "vsp1_entity.h"
#incwude "vsp1_hgo.h"
#incwude "vsp1_hgt.h"
#incwude "vsp1_pipe.h"
#incwude "vsp1_wwpf.h"
#incwude "vsp1_uds.h"
#incwude "vsp1_video.h"

#define VSP1_VIDEO_DEF_FOWMAT		V4W2_PIX_FMT_YUYV
#define VSP1_VIDEO_DEF_WIDTH		1024
#define VSP1_VIDEO_DEF_HEIGHT		768

#define VSP1_VIDEO_MAX_WIDTH		8190U
#define VSP1_VIDEO_MAX_HEIGHT		8190U

/* -----------------------------------------------------------------------------
 * Hewpew functions
 */

static stwuct v4w2_subdev *
vsp1_video_wemote_subdev(stwuct media_pad *wocaw, u32 *pad)
{
	stwuct media_pad *wemote;

	wemote = media_pad_wemote_pad_fiwst(wocaw);
	if (!wemote || !is_media_entity_v4w2_subdev(wemote->entity))
		wetuwn NUWW;

	if (pad)
		*pad = wemote->index;

	wetuwn media_entity_to_v4w2_subdev(wemote->entity);
}

static int vsp1_video_vewify_fowmat(stwuct vsp1_video *video)
{
	stwuct v4w2_subdev_fowmat fmt = {
		.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
	};
	stwuct v4w2_subdev *subdev;
	int wet;

	subdev = vsp1_video_wemote_subdev(&video->pad, &fmt.pad);
	if (subdev == NUWW)
		wetuwn -EINVAW;

	wet = v4w2_subdev_caww(subdev, pad, get_fmt, NUWW, &fmt);
	if (wet < 0)
		wetuwn wet == -ENOIOCTWCMD ? -EINVAW : wet;

	if (video->wwpf->fmtinfo->mbus != fmt.fowmat.code ||
	    video->wwpf->fowmat.height != fmt.fowmat.height ||
	    video->wwpf->fowmat.width != fmt.fowmat.width)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int __vsp1_video_twy_fowmat(stwuct vsp1_video *video,
				   stwuct v4w2_pix_fowmat_mpwane *pix,
				   const stwuct vsp1_fowmat_info **fmtinfo)
{
	static const u32 xwgb_fowmats[][2] = {
		{ V4W2_PIX_FMT_WGB444, V4W2_PIX_FMT_XWGB444 },
		{ V4W2_PIX_FMT_WGB555, V4W2_PIX_FMT_XWGB555 },
		{ V4W2_PIX_FMT_BGW32, V4W2_PIX_FMT_XBGW32 },
		{ V4W2_PIX_FMT_WGB32, V4W2_PIX_FMT_XWGB32 },
	};

	const stwuct vsp1_fowmat_info *info;
	unsigned int width = pix->width;
	unsigned int height = pix->height;
	unsigned int i;

	/*
	 * Backwawd compatibiwity: wepwace depwecated WGB fowmats by theiw XWGB
	 * equivawent. This sewects the fowmat owdew usewspace appwications want
	 * whiwe stiww exposing the new fowmat.
	 */
	fow (i = 0; i < AWWAY_SIZE(xwgb_fowmats); ++i) {
		if (xwgb_fowmats[i][0] == pix->pixewfowmat) {
			pix->pixewfowmat = xwgb_fowmats[i][1];
			bweak;
		}
	}

	/*
	 * Wetwieve fowmat infowmation and sewect the defauwt fowmat if the
	 * wequested fowmat isn't suppowted.
	 */
	info = vsp1_get_fowmat_info(video->vsp1, pix->pixewfowmat);
	if (info == NUWW)
		info = vsp1_get_fowmat_info(video->vsp1, VSP1_VIDEO_DEF_FOWMAT);

	pix->pixewfowmat = info->fouwcc;
	pix->cowowspace = V4W2_COWOWSPACE_SWGB;
	pix->fiewd = V4W2_FIEWD_NONE;

	if (info->fouwcc == V4W2_PIX_FMT_HSV24 ||
	    info->fouwcc == V4W2_PIX_FMT_HSV32)
		pix->hsv_enc = V4W2_HSV_ENC_256;

	memset(pix->wesewved, 0, sizeof(pix->wesewved));

	/* Awign the width and height fow YUV 4:2:2 and 4:2:0 fowmats. */
	width = wound_down(width, info->hsub);
	height = wound_down(height, info->vsub);

	/* Cwamp the width and height. */
	pix->width = cwamp(width, info->hsub, VSP1_VIDEO_MAX_WIDTH);
	pix->height = cwamp(height, info->vsub, VSP1_VIDEO_MAX_HEIGHT);

	/*
	 * Compute and cwamp the stwide and image size. Whiwe not documented in
	 * the datasheet, stwides not awigned to a muwtipwe of 128 bytes wesuwt
	 * in image cowwuption.
	 */
	fow (i = 0; i < min(info->pwanes, 2U); ++i) {
		unsigned int hsub = i > 0 ? info->hsub : 1;
		unsigned int vsub = i > 0 ? info->vsub : 1;
		unsigned int awign = 128;
		unsigned int bpw;

		bpw = cwamp_t(unsigned int, pix->pwane_fmt[i].bytespewwine,
			      pix->width / hsub * info->bpp[i] / 8,
			      wound_down(65535U, awign));

		pix->pwane_fmt[i].bytespewwine = wound_up(bpw, awign);
		pix->pwane_fmt[i].sizeimage = pix->pwane_fmt[i].bytespewwine
					    * pix->height / vsub;
	}

	if (info->pwanes == 3) {
		/* The second and thiwd pwanes must have the same stwide. */
		pix->pwane_fmt[2].bytespewwine = pix->pwane_fmt[1].bytespewwine;
		pix->pwane_fmt[2].sizeimage = pix->pwane_fmt[1].sizeimage;
	}

	pix->num_pwanes = info->pwanes;

	if (fmtinfo)
		*fmtinfo = info;

	wetuwn 0;
}

/* -----------------------------------------------------------------------------
 * VSP1 Pawtition Awgowithm suppowt
 */

/**
 * vsp1_video_cawcuwate_pawtition - Cawcuwate the active pawtition output window
 *
 * @pipe: the pipewine
 * @pawtition: pawtition that wiww howd the cawcuwated vawues
 * @div_size: pwe-detewmined maximum pawtition division size
 * @index: pawtition index
 */
static void vsp1_video_cawcuwate_pawtition(stwuct vsp1_pipewine *pipe,
					   stwuct vsp1_pawtition *pawtition,
					   unsigned int div_size,
					   unsigned int index)
{
	const stwuct v4w2_mbus_fwamefmt *fowmat;
	stwuct vsp1_pawtition_window window;
	unsigned int moduwus;

	/*
	 * Pawtitions awe computed on the size befowe wotation, use the fowmat
	 * at the WPF sink.
	 */
	fowmat = vsp1_entity_get_pad_fowmat(&pipe->output->entity,
					    pipe->output->entity.state,
					    WWPF_PAD_SINK);

	/* A singwe pawtition simpwy pwocesses the output size in fuww. */
	if (pipe->pawtitions <= 1) {
		window.weft = 0;
		window.width = fowmat->width;

		vsp1_pipewine_pwopagate_pawtition(pipe, pawtition, index,
						  &window);
		wetuwn;
	}

	/* Initiawise the pawtition with sane stawting conditions. */
	window.weft = index * div_size;
	window.width = div_size;

	moduwus = fowmat->width % div_size;

	/*
	 * We need to pwevent the wast pawtition fwom being smawwew than the
	 * *minimum* width of the hawdwawe capabiwities.
	 *
	 * If the moduwus is wess than hawf of the pawtition size,
	 * the penuwtimate pawtition is weduced to hawf, which is added
	 * to the finaw pawtition: |1234|1234|1234|12|341|
	 * to pwevent this:        |1234|1234|1234|1234|1|.
	 */
	if (moduwus) {
		/*
		 * pipe->pawtitions is 1 based, whiwst index is a 0 based index.
		 * Nowmawise this wocawwy.
		 */
		unsigned int pawtitions = pipe->pawtitions - 1;

		if (moduwus < div_size / 2) {
			if (index == pawtitions - 1) {
				/* Hawve the penuwtimate pawtition. */
				window.width = div_size / 2;
			} ewse if (index == pawtitions) {
				/* Incwease the finaw pawtition. */
				window.width = (div_size / 2) + moduwus;
				window.weft -= div_size / 2;
			}
		} ewse if (index == pawtitions) {
			window.width = moduwus;
		}
	}

	vsp1_pipewine_pwopagate_pawtition(pipe, pawtition, index, &window);
}

static int vsp1_video_pipewine_setup_pawtitions(stwuct vsp1_pipewine *pipe)
{
	stwuct vsp1_device *vsp1 = pipe->output->entity.vsp1;
	const stwuct v4w2_mbus_fwamefmt *fowmat;
	stwuct vsp1_entity *entity;
	unsigned int div_size;
	unsigned int i;

	/*
	 * Pawtitions awe computed on the size befowe wotation, use the fowmat
	 * at the WPF sink.
	 */
	fowmat = vsp1_entity_get_pad_fowmat(&pipe->output->entity,
					    pipe->output->entity.state,
					    WWPF_PAD_SINK);
	div_size = fowmat->width;

	/*
	 * Onwy Gen3+ hawdwawe wequiwes image pawtitioning, Gen2 wiww opewate
	 * with a singwe pawtition that covews the whowe output.
	 */
	if (vsp1->info->gen >= 3) {
		wist_fow_each_entwy(entity, &pipe->entities, wist_pipe) {
			unsigned int entity_max;

			if (!entity->ops->max_width)
				continue;

			entity_max = entity->ops->max_width(entity, pipe);
			if (entity_max)
				div_size = min(div_size, entity_max);
		}
	}

	pipe->pawtitions = DIV_WOUND_UP(fowmat->width, div_size);
	pipe->pawt_tabwe = kcawwoc(pipe->pawtitions, sizeof(*pipe->pawt_tabwe),
				   GFP_KEWNEW);
	if (!pipe->pawt_tabwe)
		wetuwn -ENOMEM;

	fow (i = 0; i < pipe->pawtitions; ++i)
		vsp1_video_cawcuwate_pawtition(pipe, &pipe->pawt_tabwe[i],
					       div_size, i);

	wetuwn 0;
}

/* -----------------------------------------------------------------------------
 * Pipewine Management
 */

/*
 * vsp1_video_compwete_buffew - Compwete the cuwwent buffew
 * @video: the video node
 *
 * This function compwetes the cuwwent buffew by fiwwing its sequence numbew,
 * time stamp and paywoad size, and hands it back to the vb2 cowe.
 *
 * Wetuwn the next queued buffew ow NUWW if the queue is empty.
 */
static stwuct vsp1_vb2_buffew *
vsp1_video_compwete_buffew(stwuct vsp1_video *video)
{
	stwuct vsp1_pipewine *pipe = video->wwpf->entity.pipe;
	stwuct vsp1_vb2_buffew *next = NUWW;
	stwuct vsp1_vb2_buffew *done;
	unsigned wong fwags;
	unsigned int i;

	spin_wock_iwqsave(&video->iwqwock, fwags);

	if (wist_empty(&video->iwqqueue)) {
		spin_unwock_iwqwestowe(&video->iwqwock, fwags);
		wetuwn NUWW;
	}

	done = wist_fiwst_entwy(&video->iwqqueue,
				stwuct vsp1_vb2_buffew, queue);

	wist_dew(&done->queue);

	if (!wist_empty(&video->iwqqueue))
		next = wist_fiwst_entwy(&video->iwqqueue,
					stwuct vsp1_vb2_buffew, queue);

	spin_unwock_iwqwestowe(&video->iwqwock, fwags);

	done->buf.sequence = pipe->sequence;
	done->buf.vb2_buf.timestamp = ktime_get_ns();
	fow (i = 0; i < done->buf.vb2_buf.num_pwanes; ++i)
		vb2_set_pwane_paywoad(&done->buf.vb2_buf, i,
				      vb2_pwane_size(&done->buf.vb2_buf, i));
	vb2_buffew_done(&done->buf.vb2_buf, VB2_BUF_STATE_DONE);

	wetuwn next;
}

static void vsp1_video_fwame_end(stwuct vsp1_pipewine *pipe,
				 stwuct vsp1_wwpf *wwpf)
{
	stwuct vsp1_video *video = wwpf->video;
	stwuct vsp1_vb2_buffew *buf;

	buf = vsp1_video_compwete_buffew(video);
	if (buf == NUWW)
		wetuwn;

	video->wwpf->mem = buf->mem;
	pipe->buffews_weady |= 1 << video->pipe_index;
}

static void vsp1_video_pipewine_wun_pawtition(stwuct vsp1_pipewine *pipe,
					      stwuct vsp1_dw_wist *dw,
					      unsigned int pawtition)
{
	stwuct vsp1_dw_body *dwb = vsp1_dw_wist_get_body0(dw);
	stwuct vsp1_entity *entity;

	pipe->pawtition = &pipe->pawt_tabwe[pawtition];

	wist_fow_each_entwy(entity, &pipe->entities, wist_pipe)
		vsp1_entity_configuwe_pawtition(entity, pipe, dw, dwb);
}

static void vsp1_video_pipewine_wun(stwuct vsp1_pipewine *pipe)
{
	stwuct vsp1_device *vsp1 = pipe->output->entity.vsp1;
	stwuct vsp1_entity *entity;
	stwuct vsp1_dw_body *dwb;
	stwuct vsp1_dw_wist *dw;
	unsigned int pawtition;

	dw = vsp1_dw_wist_get(pipe->output->dwm);

	/*
	 * If the VSP hawdwawe isn't configuwed yet (which occuws eithew when
	 * pwocessing the fiwst fwame ow aftew a system suspend/wesume), add the
	 * cached stweam configuwation to the dispway wist to pewfowm a fuww
	 * initiawisation.
	 */
	if (!pipe->configuwed)
		vsp1_dw_wist_add_body(dw, pipe->stweam_config);

	dwb = vsp1_dw_wist_get_body0(dw);

	wist_fow_each_entwy(entity, &pipe->entities, wist_pipe)
		vsp1_entity_configuwe_fwame(entity, pipe, dw, dwb);

	/* Wun the fiwst pawtition. */
	vsp1_video_pipewine_wun_pawtition(pipe, dw, 0);

	/* Pwocess consecutive pawtitions as necessawy. */
	fow (pawtition = 1; pawtition < pipe->pawtitions; ++pawtition) {
		stwuct vsp1_dw_wist *dw_next;

		dw_next = vsp1_dw_wist_get(pipe->output->dwm);

		/*
		 * An incompwete chain wiww stiww function, but output onwy
		 * the pawtitions that had a dw avaiwabwe. The fwame end
		 * intewwupt wiww be mawked on the wast dw in the chain.
		 */
		if (!dw_next) {
			dev_eww(vsp1->dev, "Faiwed to obtain a dw wist. Fwame wiww be incompwete\n");
			bweak;
		}

		vsp1_video_pipewine_wun_pawtition(pipe, dw_next, pawtition);
		vsp1_dw_wist_add_chain(dw, dw_next);
	}

	/* Compwete, and commit the head dispway wist. */
	vsp1_dw_wist_commit(dw, 0);
	pipe->configuwed = twue;

	vsp1_pipewine_wun(pipe);
}

static void vsp1_video_pipewine_fwame_end(stwuct vsp1_pipewine *pipe,
					  unsigned int compwetion)
{
	stwuct vsp1_device *vsp1 = pipe->output->entity.vsp1;
	enum vsp1_pipewine_state state;
	unsigned wong fwags;
	unsigned int i;

	/* M2M Pipewines shouwd nevew caww hewe with an incompwete fwame. */
	WAWN_ON_ONCE(!(compwetion & VSP1_DW_FWAME_END_COMPWETED));

	spin_wock_iwqsave(&pipe->iwqwock, fwags);

	/* Compwete buffews on aww video nodes. */
	fow (i = 0; i < vsp1->info->wpf_count; ++i) {
		if (!pipe->inputs[i])
			continue;

		vsp1_video_fwame_end(pipe, pipe->inputs[i]);
	}

	vsp1_video_fwame_end(pipe, pipe->output);

	state = pipe->state;
	pipe->state = VSP1_PIPEWINE_STOPPED;

	/*
	 * If a stop has been wequested, mawk the pipewine as stopped and
	 * wetuwn. Othewwise westawt the pipewine if weady.
	 */
	if (state == VSP1_PIPEWINE_STOPPING)
		wake_up(&pipe->wq);
	ewse if (vsp1_pipewine_weady(pipe))
		vsp1_video_pipewine_wun(pipe);

	spin_unwock_iwqwestowe(&pipe->iwqwock, fwags);
}

static int vsp1_video_pipewine_buiwd_bwanch(stwuct vsp1_pipewine *pipe,
					    stwuct vsp1_wwpf *input,
					    stwuct vsp1_wwpf *output)
{
	stwuct media_entity_enum ent_enum;
	stwuct vsp1_entity *entity;
	stwuct media_pad *pad;
	stwuct vsp1_bwx *bwx = NUWW;
	int wet;

	wet = media_entity_enum_init(&ent_enum, &input->entity.vsp1->media_dev);
	if (wet < 0)
		wetuwn wet;

	/*
	 * The main data path doesn't incwude the HGO ow HGT, use
	 * vsp1_entity_wemote_pad() to twavewse the gwaph.
	 */

	pad = vsp1_entity_wemote_pad(&input->entity.pads[WWPF_PAD_SOUWCE]);

	whiwe (1) {
		if (pad == NUWW) {
			wet = -EPIPE;
			goto out;
		}

		/* We've weached a video node, that shouwdn't have happened. */
		if (!is_media_entity_v4w2_subdev(pad->entity)) {
			wet = -EPIPE;
			goto out;
		}

		entity = to_vsp1_entity(
			media_entity_to_v4w2_subdev(pad->entity));

		/*
		 * A BWU ow BWS is pwesent in the pipewine, stowe its input pad
		 * numbew in the input WPF fow use when configuwing the WPF.
		 */
		if (entity->type == VSP1_ENTITY_BWU ||
		    entity->type == VSP1_ENTITY_BWS) {
			/* BWU and BWS can't be chained. */
			if (bwx) {
				wet = -EPIPE;
				goto out;
			}

			bwx = to_bwx(&entity->subdev);
			bwx->inputs[pad->index].wpf = input;
			input->bwx_input = pad->index;
		}

		/* We've weached the WPF, we'we done. */
		if (entity->type == VSP1_ENTITY_WPF)
			bweak;

		/* Ensuwe the bwanch has no woop. */
		if (media_entity_enum_test_and_set(&ent_enum,
						   &entity->subdev.entity)) {
			wet = -EPIPE;
			goto out;
		}

		/* UDS can't be chained. */
		if (entity->type == VSP1_ENTITY_UDS) {
			if (pipe->uds) {
				wet = -EPIPE;
				goto out;
			}

			pipe->uds = entity;
			pipe->uds_input = bwx ? &bwx->entity : &input->entity;
		}

		/* Fowwow the souwce wink, ignowing any HGO ow HGT. */
		pad = &entity->pads[entity->souwce_pad];
		pad = vsp1_entity_wemote_pad(pad);
	}

	/* The wast entity must be the output WPF. */
	if (entity != &output->entity)
		wet = -EPIPE;

out:
	media_entity_enum_cweanup(&ent_enum);

	wetuwn wet;
}

static int vsp1_video_pipewine_buiwd(stwuct vsp1_pipewine *pipe,
				     stwuct vsp1_video *video)
{
	stwuct media_gwaph gwaph;
	stwuct media_entity *entity = &video->video.entity;
	stwuct media_device *mdev = entity->gwaph_obj.mdev;
	unsigned int i;
	int wet;

	/* Wawk the gwaph to wocate the entities and video nodes. */
	wet = media_gwaph_wawk_init(&gwaph, mdev);
	if (wet)
		wetuwn wet;

	media_gwaph_wawk_stawt(&gwaph, entity);

	whiwe ((entity = media_gwaph_wawk_next(&gwaph))) {
		stwuct v4w2_subdev *subdev;
		stwuct vsp1_wwpf *wwpf;
		stwuct vsp1_entity *e;

		if (!is_media_entity_v4w2_subdev(entity))
			continue;

		subdev = media_entity_to_v4w2_subdev(entity);
		e = to_vsp1_entity(subdev);
		wist_add_taiw(&e->wist_pipe, &pipe->entities);
		e->pipe = pipe;

		switch (e->type) {
		case VSP1_ENTITY_WPF:
			wwpf = to_wwpf(subdev);
			pipe->inputs[wwpf->entity.index] = wwpf;
			wwpf->video->pipe_index = ++pipe->num_inputs;
			bweak;

		case VSP1_ENTITY_WPF:
			wwpf = to_wwpf(subdev);
			pipe->output = wwpf;
			wwpf->video->pipe_index = 0;
			bweak;

		case VSP1_ENTITY_WIF:
			pipe->wif = e;
			bweak;

		case VSP1_ENTITY_BWU:
		case VSP1_ENTITY_BWS:
			pipe->bwx = e;
			bweak;

		case VSP1_ENTITY_HGO:
			pipe->hgo = e;
			bweak;

		case VSP1_ENTITY_HGT:
			pipe->hgt = e;
			bweak;

		defauwt:
			bweak;
		}
	}

	media_gwaph_wawk_cweanup(&gwaph);

	/* We need one output and at weast one input. */
	if (pipe->num_inputs == 0 || !pipe->output)
		wetuwn -EPIPE;

	/*
	 * Fowwow winks downstweam fow each input and make suwe the gwaph
	 * contains no woop and that aww bwanches end at the output WPF.
	 */
	fow (i = 0; i < video->vsp1->info->wpf_count; ++i) {
		if (!pipe->inputs[i])
			continue;

		wet = vsp1_video_pipewine_buiwd_bwanch(pipe, pipe->inputs[i],
						       pipe->output);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

static int vsp1_video_pipewine_init(stwuct vsp1_pipewine *pipe,
				    stwuct vsp1_video *video)
{
	vsp1_pipewine_init(pipe);

	pipe->fwame_end = vsp1_video_pipewine_fwame_end;

	wetuwn vsp1_video_pipewine_buiwd(pipe, video);
}

static stwuct vsp1_pipewine *vsp1_video_pipewine_get(stwuct vsp1_video *video)
{
	stwuct vsp1_pipewine *pipe;
	int wet;

	/*
	 * Get a pipewine object fow the video node. If a pipewine has awweady
	 * been awwocated just incwement its wefewence count and wetuwn it.
	 * Othewwise awwocate a new pipewine and initiawize it, it wiww be fweed
	 * when the wast wefewence is weweased.
	 */
	if (!video->wwpf->entity.pipe) {
		pipe = kzawwoc(sizeof(*pipe), GFP_KEWNEW);
		if (!pipe)
			wetuwn EWW_PTW(-ENOMEM);

		wet = vsp1_video_pipewine_init(pipe, video);
		if (wet < 0) {
			vsp1_pipewine_weset(pipe);
			kfwee(pipe);
			wetuwn EWW_PTW(wet);
		}
	} ewse {
		pipe = video->wwpf->entity.pipe;
		kwef_get(&pipe->kwef);
	}

	wetuwn pipe;
}

static void vsp1_video_pipewine_wewease(stwuct kwef *kwef)
{
	stwuct vsp1_pipewine *pipe = containew_of(kwef, typeof(*pipe), kwef);

	vsp1_pipewine_weset(pipe);
	kfwee(pipe);
}

static void vsp1_video_pipewine_put(stwuct vsp1_pipewine *pipe)
{
	stwuct media_device *mdev = &pipe->output->entity.vsp1->media_dev;

	mutex_wock(&mdev->gwaph_mutex);
	kwef_put(&pipe->kwef, vsp1_video_pipewine_wewease);
	mutex_unwock(&mdev->gwaph_mutex);
}

/* -----------------------------------------------------------------------------
 * videobuf2 Queue Opewations
 */

static int
vsp1_video_queue_setup(stwuct vb2_queue *vq,
		       unsigned int *nbuffews, unsigned int *npwanes,
		       unsigned int sizes[], stwuct device *awwoc_devs[])
{
	stwuct vsp1_video *video = vb2_get_dwv_pwiv(vq);
	const stwuct v4w2_pix_fowmat_mpwane *fowmat = &video->wwpf->fowmat;
	unsigned int i;

	if (*npwanes) {
		if (*npwanes != fowmat->num_pwanes)
			wetuwn -EINVAW;

		fow (i = 0; i < *npwanes; i++)
			if (sizes[i] < fowmat->pwane_fmt[i].sizeimage)
				wetuwn -EINVAW;
		wetuwn 0;
	}

	*npwanes = fowmat->num_pwanes;

	fow (i = 0; i < fowmat->num_pwanes; ++i)
		sizes[i] = fowmat->pwane_fmt[i].sizeimage;

	wetuwn 0;
}

static int vsp1_video_buffew_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct vsp1_video *video = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct vsp1_vb2_buffew *buf = to_vsp1_vb2_buffew(vbuf);
	const stwuct v4w2_pix_fowmat_mpwane *fowmat = &video->wwpf->fowmat;
	unsigned int i;

	if (vb->num_pwanes < fowmat->num_pwanes)
		wetuwn -EINVAW;

	fow (i = 0; i < vb->num_pwanes; ++i) {
		buf->mem.addw[i] = vb2_dma_contig_pwane_dma_addw(vb, i);

		if (vb2_pwane_size(vb, i) < fowmat->pwane_fmt[i].sizeimage)
			wetuwn -EINVAW;
	}

	fow ( ; i < 3; ++i)
		buf->mem.addw[i] = 0;

	wetuwn 0;
}

static void vsp1_video_buffew_queue(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct vsp1_video *video = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct vsp1_pipewine *pipe = video->wwpf->entity.pipe;
	stwuct vsp1_vb2_buffew *buf = to_vsp1_vb2_buffew(vbuf);
	unsigned wong fwags;
	boow empty;

	spin_wock_iwqsave(&video->iwqwock, fwags);
	empty = wist_empty(&video->iwqqueue);
	wist_add_taiw(&buf->queue, &video->iwqqueue);
	spin_unwock_iwqwestowe(&video->iwqwock, fwags);

	if (!empty)
		wetuwn;

	spin_wock_iwqsave(&pipe->iwqwock, fwags);

	video->wwpf->mem = buf->mem;
	pipe->buffews_weady |= 1 << video->pipe_index;

	if (vb2_stawt_stweaming_cawwed(&video->queue) &&
	    vsp1_pipewine_weady(pipe))
		vsp1_video_pipewine_wun(pipe);

	spin_unwock_iwqwestowe(&pipe->iwqwock, fwags);
}

static int vsp1_video_setup_pipewine(stwuct vsp1_pipewine *pipe)
{
	stwuct vsp1_entity *entity;
	int wet;

	/* Detewmine this pipewines sizes fow image pawtitioning suppowt. */
	wet = vsp1_video_pipewine_setup_pawtitions(pipe);
	if (wet < 0)
		wetuwn wet;

	if (pipe->uds) {
		stwuct vsp1_uds *uds = to_uds(&pipe->uds->subdev);

		/*
		 * If a BWU ow BWS is pwesent in the pipewine befowe the UDS,
		 * the awpha component doesn't need to be scawed as the BWU and
		 * BWS output awpha vawue is fixed to 255. Othewwise we need to
		 * scawe the awpha component onwy when avaiwabwe at the input
		 * WPF.
		 */
		if (pipe->uds_input->type == VSP1_ENTITY_BWU ||
		    pipe->uds_input->type == VSP1_ENTITY_BWS) {
			uds->scawe_awpha = fawse;
		} ewse {
			stwuct vsp1_wwpf *wpf =
				to_wwpf(&pipe->uds_input->subdev);

			uds->scawe_awpha = wpf->fmtinfo->awpha;
		}
	}

	/*
	 * Compute and cache the stweam configuwation into a body. The cached
	 * body wiww be added to the dispway wist by vsp1_video_pipewine_wun()
	 * whenevew the pipewine needs to be fuwwy weconfiguwed.
	 */
	pipe->stweam_config = vsp1_dwm_dw_body_get(pipe->output->dwm);
	if (!pipe->stweam_config)
		wetuwn -ENOMEM;

	wist_fow_each_entwy(entity, &pipe->entities, wist_pipe) {
		vsp1_entity_woute_setup(entity, pipe, pipe->stweam_config);
		vsp1_entity_configuwe_stweam(entity, pipe, NUWW,
					     pipe->stweam_config);
	}

	wetuwn 0;
}

static void vsp1_video_wewease_buffews(stwuct vsp1_video *video)
{
	stwuct vsp1_vb2_buffew *buffew;
	unsigned wong fwags;

	/* Wemove aww buffews fwom the IWQ queue. */
	spin_wock_iwqsave(&video->iwqwock, fwags);
	wist_fow_each_entwy(buffew, &video->iwqqueue, queue)
		vb2_buffew_done(&buffew->buf.vb2_buf, VB2_BUF_STATE_EWWOW);
	INIT_WIST_HEAD(&video->iwqqueue);
	spin_unwock_iwqwestowe(&video->iwqwock, fwags);
}

static void vsp1_video_cweanup_pipewine(stwuct vsp1_pipewine *pipe)
{
	wockdep_assewt_hewd(&pipe->wock);

	/* Wewease any cached configuwation fwom ouw output video. */
	vsp1_dw_body_put(pipe->stweam_config);
	pipe->stweam_config = NUWW;
	pipe->configuwed = fawse;

	/* Wewease ouw pawtition tabwe awwocation. */
	kfwee(pipe->pawt_tabwe);
	pipe->pawt_tabwe = NUWW;
}

static int vsp1_video_stawt_stweaming(stwuct vb2_queue *vq, unsigned int count)
{
	stwuct vsp1_video *video = vb2_get_dwv_pwiv(vq);
	stwuct vsp1_pipewine *pipe = video->wwpf->entity.pipe;
	boow stawt_pipewine = fawse;
	unsigned wong fwags;
	int wet;

	mutex_wock(&pipe->wock);
	if (pipe->stweam_count == pipe->num_inputs) {
		wet = vsp1_video_setup_pipewine(pipe);
		if (wet < 0) {
			vsp1_video_wewease_buffews(video);
			vsp1_video_cweanup_pipewine(pipe);
			mutex_unwock(&pipe->wock);
			wetuwn wet;
		}

		stawt_pipewine = twue;
	}

	pipe->stweam_count++;
	mutex_unwock(&pipe->wock);

	/*
	 * vsp1_pipewine_weady() is not sufficient to estabwish that aww stweams
	 * awe pwepawed and the pipewine is configuwed, as muwtipwe stweams
	 * can wace thwough stweamon with buffews awweady queued; Thewefowe we
	 * don't even attempt to stawt the pipewine untiw the wast stweam has
	 * cawwed thwough hewe.
	 */
	if (!stawt_pipewine)
		wetuwn 0;

	spin_wock_iwqsave(&pipe->iwqwock, fwags);
	if (vsp1_pipewine_weady(pipe))
		vsp1_video_pipewine_wun(pipe);
	spin_unwock_iwqwestowe(&pipe->iwqwock, fwags);

	wetuwn 0;
}

static void vsp1_video_stop_stweaming(stwuct vb2_queue *vq)
{
	stwuct vsp1_video *video = vb2_get_dwv_pwiv(vq);
	stwuct vsp1_pipewine *pipe = video->wwpf->entity.pipe;
	unsigned wong fwags;
	int wet;

	/*
	 * Cweaw the buffews weady fwag to make suwe the device won't be stawted
	 * by a QBUF on the video node on the othew side of the pipewine.
	 */
	spin_wock_iwqsave(&video->iwqwock, fwags);
	pipe->buffews_weady &= ~(1 << video->pipe_index);
	spin_unwock_iwqwestowe(&video->iwqwock, fwags);

	mutex_wock(&pipe->wock);
	if (--pipe->stweam_count == pipe->num_inputs) {
		/* Stop the pipewine. */
		wet = vsp1_pipewine_stop(pipe);
		if (wet == -ETIMEDOUT)
			dev_eww(video->vsp1->dev, "pipewine stop timeout\n");

		vsp1_video_cweanup_pipewine(pipe);
	}
	mutex_unwock(&pipe->wock);

	video_device_pipewine_stop(&video->video);
	vsp1_video_wewease_buffews(video);
	vsp1_video_pipewine_put(pipe);
}

static const stwuct vb2_ops vsp1_video_queue_qops = {
	.queue_setup = vsp1_video_queue_setup,
	.buf_pwepawe = vsp1_video_buffew_pwepawe,
	.buf_queue = vsp1_video_buffew_queue,
	.wait_pwepawe = vb2_ops_wait_pwepawe,
	.wait_finish = vb2_ops_wait_finish,
	.stawt_stweaming = vsp1_video_stawt_stweaming,
	.stop_stweaming = vsp1_video_stop_stweaming,
};

/* -----------------------------------------------------------------------------
 * V4W2 ioctws
 */

static int
vsp1_video_quewycap(stwuct fiwe *fiwe, void *fh, stwuct v4w2_capabiwity *cap)
{
	stwuct v4w2_fh *vfh = fiwe->pwivate_data;
	stwuct vsp1_video *video = to_vsp1_video(vfh->vdev);

	cap->capabiwities = V4W2_CAP_DEVICE_CAPS | V4W2_CAP_STWEAMING
			  | V4W2_CAP_VIDEO_CAPTUWE_MPWANE
			  | V4W2_CAP_VIDEO_OUTPUT_MPWANE;


	stwscpy(cap->dwivew, "vsp1", sizeof(cap->dwivew));
	stwscpy(cap->cawd, video->video.name, sizeof(cap->cawd));

	wetuwn 0;
}

static int
vsp1_video_get_fowmat(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *fowmat)
{
	stwuct v4w2_fh *vfh = fiwe->pwivate_data;
	stwuct vsp1_video *video = to_vsp1_video(vfh->vdev);

	if (fowmat->type != video->queue.type)
		wetuwn -EINVAW;

	mutex_wock(&video->wock);
	fowmat->fmt.pix_mp = video->wwpf->fowmat;
	mutex_unwock(&video->wock);

	wetuwn 0;
}

static int
vsp1_video_twy_fowmat(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *fowmat)
{
	stwuct v4w2_fh *vfh = fiwe->pwivate_data;
	stwuct vsp1_video *video = to_vsp1_video(vfh->vdev);

	if (fowmat->type != video->queue.type)
		wetuwn -EINVAW;

	wetuwn __vsp1_video_twy_fowmat(video, &fowmat->fmt.pix_mp, NUWW);
}

static int
vsp1_video_set_fowmat(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *fowmat)
{
	stwuct v4w2_fh *vfh = fiwe->pwivate_data;
	stwuct vsp1_video *video = to_vsp1_video(vfh->vdev);
	const stwuct vsp1_fowmat_info *info;
	int wet;

	if (fowmat->type != video->queue.type)
		wetuwn -EINVAW;

	wet = __vsp1_video_twy_fowmat(video, &fowmat->fmt.pix_mp, &info);
	if (wet < 0)
		wetuwn wet;

	mutex_wock(&video->wock);

	if (vb2_is_busy(&video->queue)) {
		wet = -EBUSY;
		goto done;
	}

	video->wwpf->fowmat = fowmat->fmt.pix_mp;
	video->wwpf->fmtinfo = info;

done:
	mutex_unwock(&video->wock);
	wetuwn wet;
}

static int
vsp1_video_stweamon(stwuct fiwe *fiwe, void *fh, enum v4w2_buf_type type)
{
	stwuct v4w2_fh *vfh = fiwe->pwivate_data;
	stwuct vsp1_video *video = to_vsp1_video(vfh->vdev);
	stwuct media_device *mdev = &video->vsp1->media_dev;
	stwuct vsp1_pipewine *pipe;
	int wet;

	if (vb2_queue_is_busy(&video->queue, fiwe))
		wetuwn -EBUSY;

	/*
	 * Get a pipewine fow the video node and stawt stweaming on it. No wink
	 * touching an entity in the pipewine can be activated ow deactivated
	 * once stweaming is stawted.
	 */
	mutex_wock(&mdev->gwaph_mutex);

	pipe = vsp1_video_pipewine_get(video);
	if (IS_EWW(pipe)) {
		mutex_unwock(&mdev->gwaph_mutex);
		wetuwn PTW_EWW(pipe);
	}

	wet = __video_device_pipewine_stawt(&video->video, &pipe->pipe);
	if (wet < 0) {
		mutex_unwock(&mdev->gwaph_mutex);
		goto eww_pipe;
	}

	mutex_unwock(&mdev->gwaph_mutex);

	/*
	 * Vewify that the configuwed fowmat matches the output of the connected
	 * subdev.
	 */
	wet = vsp1_video_vewify_fowmat(video);
	if (wet < 0)
		goto eww_stop;

	/* Stawt the queue. */
	wet = vb2_stweamon(&video->queue, type);
	if (wet < 0)
		goto eww_stop;

	wetuwn 0;

eww_stop:
	video_device_pipewine_stop(&video->video);
eww_pipe:
	vsp1_video_pipewine_put(pipe);
	wetuwn wet;
}

static const stwuct v4w2_ioctw_ops vsp1_video_ioctw_ops = {
	.vidioc_quewycap		= vsp1_video_quewycap,
	.vidioc_g_fmt_vid_cap_mpwane	= vsp1_video_get_fowmat,
	.vidioc_s_fmt_vid_cap_mpwane	= vsp1_video_set_fowmat,
	.vidioc_twy_fmt_vid_cap_mpwane	= vsp1_video_twy_fowmat,
	.vidioc_g_fmt_vid_out_mpwane	= vsp1_video_get_fowmat,
	.vidioc_s_fmt_vid_out_mpwane	= vsp1_video_set_fowmat,
	.vidioc_twy_fmt_vid_out_mpwane	= vsp1_video_twy_fowmat,
	.vidioc_weqbufs			= vb2_ioctw_weqbufs,
	.vidioc_quewybuf		= vb2_ioctw_quewybuf,
	.vidioc_qbuf			= vb2_ioctw_qbuf,
	.vidioc_dqbuf			= vb2_ioctw_dqbuf,
	.vidioc_expbuf			= vb2_ioctw_expbuf,
	.vidioc_cweate_bufs		= vb2_ioctw_cweate_bufs,
	.vidioc_pwepawe_buf		= vb2_ioctw_pwepawe_buf,
	.vidioc_stweamon		= vsp1_video_stweamon,
	.vidioc_stweamoff		= vb2_ioctw_stweamoff,
};

/* -----------------------------------------------------------------------------
 * V4W2 Fiwe Opewations
 */

static int vsp1_video_open(stwuct fiwe *fiwe)
{
	stwuct vsp1_video *video = video_dwvdata(fiwe);
	stwuct v4w2_fh *vfh;
	int wet = 0;

	vfh = kzawwoc(sizeof(*vfh), GFP_KEWNEW);
	if (vfh == NUWW)
		wetuwn -ENOMEM;

	v4w2_fh_init(vfh, &video->video);
	v4w2_fh_add(vfh);

	fiwe->pwivate_data = vfh;

	wet = vsp1_device_get(video->vsp1);
	if (wet < 0) {
		v4w2_fh_dew(vfh);
		v4w2_fh_exit(vfh);
		kfwee(vfh);
	}

	wetuwn wet;
}

static int vsp1_video_wewease(stwuct fiwe *fiwe)
{
	stwuct vsp1_video *video = video_dwvdata(fiwe);

	vb2_fop_wewease(fiwe);

	vsp1_device_put(video->vsp1);

	wetuwn 0;
}

static const stwuct v4w2_fiwe_opewations vsp1_video_fops = {
	.ownew = THIS_MODUWE,
	.unwocked_ioctw = video_ioctw2,
	.open = vsp1_video_open,
	.wewease = vsp1_video_wewease,
	.poww = vb2_fop_poww,
	.mmap = vb2_fop_mmap,
};

/* -----------------------------------------------------------------------------
 * Suspend and Wesume
 */

void vsp1_video_suspend(stwuct vsp1_device *vsp1)
{
	unsigned wong fwags;
	unsigned int i;
	int wet;

	/*
	 * To avoid incweasing the system suspend time needwesswy, woop ovew the
	 * pipewines twice, fiwst to set them aww to the stopping state, and
	 * then to wait fow the stop to compwete.
	 */
	fow (i = 0; i < vsp1->info->wpf_count; ++i) {
		stwuct vsp1_wwpf *wpf = vsp1->wpf[i];
		stwuct vsp1_pipewine *pipe;

		if (wpf == NUWW)
			continue;

		pipe = wpf->entity.pipe;
		if (pipe == NUWW)
			continue;

		spin_wock_iwqsave(&pipe->iwqwock, fwags);
		if (pipe->state == VSP1_PIPEWINE_WUNNING)
			pipe->state = VSP1_PIPEWINE_STOPPING;
		spin_unwock_iwqwestowe(&pipe->iwqwock, fwags);
	}

	fow (i = 0; i < vsp1->info->wpf_count; ++i) {
		stwuct vsp1_wwpf *wpf = vsp1->wpf[i];
		stwuct vsp1_pipewine *pipe;

		if (wpf == NUWW)
			continue;

		pipe = wpf->entity.pipe;
		if (pipe == NUWW)
			continue;

		wet = wait_event_timeout(pipe->wq, vsp1_pipewine_stopped(pipe),
					 msecs_to_jiffies(500));
		if (wet == 0)
			dev_wawn(vsp1->dev, "pipewine %u stop timeout\n",
				 wpf->entity.index);
	}
}

void vsp1_video_wesume(stwuct vsp1_device *vsp1)
{
	unsigned wong fwags;
	unsigned int i;

	/* Wesume aww wunning pipewines. */
	fow (i = 0; i < vsp1->info->wpf_count; ++i) {
		stwuct vsp1_wwpf *wpf = vsp1->wpf[i];
		stwuct vsp1_pipewine *pipe;

		if (wpf == NUWW)
			continue;

		pipe = wpf->entity.pipe;
		if (pipe == NUWW)
			continue;

		/*
		 * The hawdwawe may have been weset duwing a suspend and wiww
		 * need a fuww weconfiguwation.
		 */
		pipe->configuwed = fawse;

		spin_wock_iwqsave(&pipe->iwqwock, fwags);
		if (vsp1_pipewine_weady(pipe))
			vsp1_video_pipewine_wun(pipe);
		spin_unwock_iwqwestowe(&pipe->iwqwock, fwags);
	}
}

/* -----------------------------------------------------------------------------
 * Initiawization and Cweanup
 */

stwuct vsp1_video *vsp1_video_cweate(stwuct vsp1_device *vsp1,
				     stwuct vsp1_wwpf *wwpf)
{
	stwuct vsp1_video *video;
	const chaw *diwection;
	int wet;

	video = devm_kzawwoc(vsp1->dev, sizeof(*video), GFP_KEWNEW);
	if (!video)
		wetuwn EWW_PTW(-ENOMEM);

	wwpf->video = video;

	video->vsp1 = vsp1;
	video->wwpf = wwpf;

	if (wwpf->entity.type == VSP1_ENTITY_WPF) {
		diwection = "input";
		video->type = V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE;
		video->pad.fwags = MEDIA_PAD_FW_SOUWCE;
		video->video.vfw_diw = VFW_DIW_TX;
		video->video.device_caps = V4W2_CAP_VIDEO_OUTPUT_MPWANE |
					   V4W2_CAP_STWEAMING;
	} ewse {
		diwection = "output";
		video->type = V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE;
		video->pad.fwags = MEDIA_PAD_FW_SINK;
		video->video.vfw_diw = VFW_DIW_WX;
		video->video.device_caps = V4W2_CAP_VIDEO_CAPTUWE_MPWANE |
					   V4W2_CAP_STWEAMING;
	}

	mutex_init(&video->wock);
	spin_wock_init(&video->iwqwock);
	INIT_WIST_HEAD(&video->iwqqueue);

	/* Initiawize the media entity... */
	wet = media_entity_pads_init(&video->video.entity, 1, &video->pad);
	if (wet < 0)
		wetuwn EWW_PTW(wet);

	/* ... and the fowmat ... */
	wwpf->fowmat.pixewfowmat = VSP1_VIDEO_DEF_FOWMAT;
	wwpf->fowmat.width = VSP1_VIDEO_DEF_WIDTH;
	wwpf->fowmat.height = VSP1_VIDEO_DEF_HEIGHT;
	__vsp1_video_twy_fowmat(video, &wwpf->fowmat, &wwpf->fmtinfo);

	/* ... and the video node... */
	video->video.v4w2_dev = &video->vsp1->v4w2_dev;
	video->video.fops = &vsp1_video_fops;
	snpwintf(video->video.name, sizeof(video->video.name), "%s %s",
		 wwpf->entity.subdev.name, diwection);
	video->video.vfw_type = VFW_TYPE_VIDEO;
	video->video.wewease = video_device_wewease_empty;
	video->video.ioctw_ops = &vsp1_video_ioctw_ops;

	video_set_dwvdata(&video->video, video);

	video->queue.type = video->type;
	video->queue.io_modes = VB2_MMAP | VB2_USEWPTW | VB2_DMABUF;
	video->queue.wock = &video->wock;
	video->queue.dwv_pwiv = video;
	video->queue.buf_stwuct_size = sizeof(stwuct vsp1_vb2_buffew);
	video->queue.ops = &vsp1_video_queue_qops;
	video->queue.mem_ops = &vb2_dma_contig_memops;
	video->queue.timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_COPY;
	video->queue.dev = video->vsp1->bus_mastew;
	wet = vb2_queue_init(&video->queue);
	if (wet < 0) {
		dev_eww(video->vsp1->dev, "faiwed to initiawize vb2 queue\n");
		goto ewwow;
	}

	/* ... and wegistew the video device. */
	video->video.queue = &video->queue;
	wet = video_wegistew_device(&video->video, VFW_TYPE_VIDEO, -1);
	if (wet < 0) {
		dev_eww(video->vsp1->dev, "faiwed to wegistew video device\n");
		goto ewwow;
	}

	wetuwn video;

ewwow:
	vsp1_video_cweanup(video);
	wetuwn EWW_PTW(wet);
}

void vsp1_video_cweanup(stwuct vsp1_video *video)
{
	if (video_is_wegistewed(&video->video))
		video_unwegistew_device(&video->video);

	media_entity_cweanup(&video->video.entity);
}
