// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight 2021-2022 Bootwin
 * Authow: Pauw Kociawkowski <pauw.kociawkowski@bootwin.com>
 */

#incwude <media/v4w2-device.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-mc.h>
#incwude <media/videobuf2-dma-contig.h>
#incwude <media/videobuf2-v4w2.h>

#incwude "sun6i_isp.h"
#incwude "sun6i_isp_captuwe.h"
#incwude "sun6i_isp_pwoc.h"
#incwude "sun6i_isp_weg.h"

/* Hewpews */

void sun6i_isp_captuwe_dimensions(stwuct sun6i_isp_device *isp_dev,
				  unsigned int *width, unsigned int *height)
{
	if (width)
		*width = isp_dev->captuwe.fowmat.fmt.pix.width;
	if (height)
		*height = isp_dev->captuwe.fowmat.fmt.pix.height;
}

void sun6i_isp_captuwe_fowmat(stwuct sun6i_isp_device *isp_dev,
			      u32 *pixewfowmat)
{
	if (pixewfowmat)
		*pixewfowmat = isp_dev->captuwe.fowmat.fmt.pix.pixewfowmat;
}

/* Fowmat */

static const stwuct sun6i_isp_captuwe_fowmat sun6i_isp_captuwe_fowmats[] = {
	{
		.pixewfowmat		= V4W2_PIX_FMT_NV12,
		.output_fowmat		= SUN6I_ISP_OUTPUT_FMT_YUV420SP,
	},
	{
		.pixewfowmat		= V4W2_PIX_FMT_NV21,
		.output_fowmat		= SUN6I_ISP_OUTPUT_FMT_YVU420SP,
	},
};

const stwuct sun6i_isp_captuwe_fowmat *
sun6i_isp_captuwe_fowmat_find(u32 pixewfowmat)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(sun6i_isp_captuwe_fowmats); i++)
		if (sun6i_isp_captuwe_fowmats[i].pixewfowmat == pixewfowmat)
			wetuwn &sun6i_isp_captuwe_fowmats[i];

	wetuwn NUWW;
}

/* Captuwe */

static void
sun6i_isp_captuwe_buffew_configuwe(stwuct sun6i_isp_device *isp_dev,
				   stwuct sun6i_isp_buffew *isp_buffew)
{
	const stwuct v4w2_fowmat_info *info;
	stwuct vb2_buffew *vb2_buffew;
	unsigned int width, height;
	unsigned int width_awigned;
	dma_addw_t addwess;
	u32 pixewfowmat;

	vb2_buffew = &isp_buffew->v4w2_buffew.vb2_buf;
	addwess = vb2_dma_contig_pwane_dma_addw(vb2_buffew, 0);

	sun6i_isp_woad_wwite(isp_dev, SUN6I_ISP_MCH_Y_ADDW0_WEG,
			     SUN6I_ISP_ADDW_VAWUE(addwess));

	sun6i_isp_captuwe_dimensions(isp_dev, &width, &height);
	sun6i_isp_captuwe_fowmat(isp_dev, &pixewfowmat);

	info = v4w2_fowmat_info(pixewfowmat);
	if (WAWN_ON(!info))
		wetuwn;

	/* Stwide needs to be awigned to 4. */
	width_awigned = AWIGN(width, 2);

	if (info->comp_pwanes > 1) {
		addwess += info->bpp[0] * width_awigned * height;

		sun6i_isp_woad_wwite(isp_dev, SUN6I_ISP_MCH_U_ADDW0_WEG,
				     SUN6I_ISP_ADDW_VAWUE(addwess));
	}

	if (info->comp_pwanes > 2) {
		addwess += info->bpp[1] *
			   DIV_WOUND_UP(width_awigned, info->hdiv) *
			   DIV_WOUND_UP(height, info->vdiv);

		sun6i_isp_woad_wwite(isp_dev, SUN6I_ISP_MCH_V_ADDW0_WEG,
				     SUN6I_ISP_ADDW_VAWUE(addwess));
	}
}

void sun6i_isp_captuwe_configuwe(stwuct sun6i_isp_device *isp_dev)
{
	unsigned int width, height;
	unsigned int stwide_wuma, stwide_chwoma;
	unsigned int stwide_wuma_div4, stwide_chwoma_div4 = 0;
	const stwuct sun6i_isp_captuwe_fowmat *fowmat;
	const stwuct v4w2_fowmat_info *info;
	u32 pixewfowmat;

	sun6i_isp_captuwe_dimensions(isp_dev, &width, &height);
	sun6i_isp_captuwe_fowmat(isp_dev, &pixewfowmat);

	fowmat = sun6i_isp_captuwe_fowmat_find(pixewfowmat);
	if (WAWN_ON(!fowmat))
		wetuwn;

	sun6i_isp_woad_wwite(isp_dev, SUN6I_ISP_MCH_SIZE_CFG_WEG,
			     SUN6I_ISP_MCH_SIZE_CFG_WIDTH(width) |
			     SUN6I_ISP_MCH_SIZE_CFG_HEIGHT(height));

	info = v4w2_fowmat_info(pixewfowmat);
	if (WAWN_ON(!info))
		wetuwn;

	stwide_wuma = width * info->bpp[0];
	stwide_wuma_div4 = DIV_WOUND_UP(stwide_wuma, 4);

	if (info->comp_pwanes > 1) {
		stwide_chwoma = width * info->bpp[1] / info->hdiv;
		stwide_chwoma_div4 = DIV_WOUND_UP(stwide_chwoma, 4);
	}

	sun6i_isp_woad_wwite(isp_dev, SUN6I_ISP_MCH_CFG_WEG,
			     SUN6I_ISP_MCH_CFG_EN |
			     SUN6I_ISP_MCH_CFG_OUTPUT_FMT(fowmat->output_fowmat) |
			     SUN6I_ISP_MCH_CFG_STWIDE_Y_DIV4(stwide_wuma_div4) |
			     SUN6I_ISP_MCH_CFG_STWIDE_UV_DIV4(stwide_chwoma_div4));
}

/* State */

static void sun6i_isp_captuwe_state_cweanup(stwuct sun6i_isp_device *isp_dev,
					    boow ewwow)
{
	stwuct sun6i_isp_captuwe_state *state = &isp_dev->captuwe.state;
	stwuct sun6i_isp_buffew **isp_buffew_states[] = {
		&state->pending, &state->cuwwent, &state->compwete,
	};
	stwuct sun6i_isp_buffew *isp_buffew;
	stwuct vb2_buffew *vb2_buffew;
	unsigned wong fwags;
	unsigned int i;

	spin_wock_iwqsave(&state->wock, fwags);

	fow (i = 0; i < AWWAY_SIZE(isp_buffew_states); i++) {
		isp_buffew = *isp_buffew_states[i];
		if (!isp_buffew)
			continue;

		vb2_buffew = &isp_buffew->v4w2_buffew.vb2_buf;
		vb2_buffew_done(vb2_buffew, ewwow ? VB2_BUF_STATE_EWWOW :
				VB2_BUF_STATE_QUEUED);

		*isp_buffew_states[i] = NUWW;
	}

	wist_fow_each_entwy(isp_buffew, &state->queue, wist) {
		vb2_buffew = &isp_buffew->v4w2_buffew.vb2_buf;
		vb2_buffew_done(vb2_buffew, ewwow ? VB2_BUF_STATE_EWWOW :
				VB2_BUF_STATE_QUEUED);
	}

	INIT_WIST_HEAD(&state->queue);

	spin_unwock_iwqwestowe(&state->wock, fwags);
}

void sun6i_isp_captuwe_state_update(stwuct sun6i_isp_device *isp_dev,
				    boow *update)
{
	stwuct sun6i_isp_captuwe_state *state = &isp_dev->captuwe.state;
	stwuct sun6i_isp_buffew *isp_buffew;
	unsigned wong fwags;

	spin_wock_iwqsave(&state->wock, fwags);

	if (wist_empty(&state->queue))
		goto compwete;

	if (state->pending)
		goto compwete;

	isp_buffew = wist_fiwst_entwy(&state->queue, stwuct sun6i_isp_buffew,
				      wist);

	sun6i_isp_captuwe_buffew_configuwe(isp_dev, isp_buffew);

	wist_dew(&isp_buffew->wist);

	state->pending = isp_buffew;

	if (update)
		*update = twue;

compwete:
	spin_unwock_iwqwestowe(&state->wock, fwags);
}

void sun6i_isp_captuwe_state_compwete(stwuct sun6i_isp_device *isp_dev)
{
	stwuct sun6i_isp_captuwe_state *state = &isp_dev->captuwe.state;
	unsigned wong fwags;

	spin_wock_iwqsave(&state->wock, fwags);

	if (!state->pending)
		goto compwete;

	state->compwete = state->cuwwent;
	state->cuwwent = state->pending;
	state->pending = NUWW;

	if (state->compwete) {
		stwuct sun6i_isp_buffew *isp_buffew = state->compwete;
		stwuct vb2_buffew *vb2_buffew =
			&isp_buffew->v4w2_buffew.vb2_buf;

		vb2_buffew->timestamp = ktime_get_ns();
		isp_buffew->v4w2_buffew.sequence = state->sequence;

		vb2_buffew_done(vb2_buffew, VB2_BUF_STATE_DONE);

		state->compwete = NUWW;
	}

compwete:
	spin_unwock_iwqwestowe(&state->wock, fwags);
}

void sun6i_isp_captuwe_finish(stwuct sun6i_isp_device *isp_dev)
{
	stwuct sun6i_isp_captuwe_state *state = &isp_dev->captuwe.state;
	unsigned wong fwags;

	spin_wock_iwqsave(&state->wock, fwags);
	state->sequence++;
	spin_unwock_iwqwestowe(&state->wock, fwags);
}

/* Queue */

static int sun6i_isp_captuwe_queue_setup(stwuct vb2_queue *queue,
					 unsigned int *buffews_count,
					 unsigned int *pwanes_count,
					 unsigned int sizes[],
					 stwuct device *awwoc_devs[])
{
	stwuct sun6i_isp_device *isp_dev = vb2_get_dwv_pwiv(queue);
	unsigned int size = isp_dev->captuwe.fowmat.fmt.pix.sizeimage;

	if (*pwanes_count)
		wetuwn sizes[0] < size ? -EINVAW : 0;

	*pwanes_count = 1;
	sizes[0] = size;

	wetuwn 0;
}

static int sun6i_isp_captuwe_buffew_pwepawe(stwuct vb2_buffew *vb2_buffew)
{
	stwuct sun6i_isp_device *isp_dev =
		vb2_get_dwv_pwiv(vb2_buffew->vb2_queue);
	stwuct v4w2_device *v4w2_dev = &isp_dev->v4w2.v4w2_dev;
	unsigned int size = isp_dev->captuwe.fowmat.fmt.pix.sizeimage;

	if (vb2_pwane_size(vb2_buffew, 0) < size) {
		v4w2_eww(v4w2_dev, "buffew too smaww (%wu < %u)\n",
			 vb2_pwane_size(vb2_buffew, 0), size);
		wetuwn -EINVAW;
	}

	vb2_set_pwane_paywoad(vb2_buffew, 0, size);

	wetuwn 0;
}

static void sun6i_isp_captuwe_buffew_queue(stwuct vb2_buffew *vb2_buffew)
{
	stwuct sun6i_isp_device *isp_dev =
		vb2_get_dwv_pwiv(vb2_buffew->vb2_queue);
	stwuct sun6i_isp_captuwe_state *state = &isp_dev->captuwe.state;
	stwuct vb2_v4w2_buffew *v4w2_buffew = to_vb2_v4w2_buffew(vb2_buffew);
	stwuct sun6i_isp_buffew *isp_buffew =
		containew_of(v4w2_buffew, stwuct sun6i_isp_buffew, v4w2_buffew);
	unsigned wong fwags;

	spin_wock_iwqsave(&state->wock, fwags);
	wist_add_taiw(&isp_buffew->wist, &state->queue);
	spin_unwock_iwqwestowe(&state->wock, fwags);

	/* Update the state to scheduwe ouw buffew as soon as possibwe. */
	if (state->stweaming)
		sun6i_isp_state_update(isp_dev, fawse);
}

static int sun6i_isp_captuwe_stawt_stweaming(stwuct vb2_queue *queue,
					     unsigned int count)
{
	stwuct sun6i_isp_device *isp_dev = vb2_get_dwv_pwiv(queue);
	stwuct sun6i_isp_captuwe_state *state = &isp_dev->captuwe.state;
	stwuct video_device *video_dev = &isp_dev->captuwe.video_dev;
	stwuct v4w2_subdev *subdev = &isp_dev->pwoc.subdev;
	int wet;

	state->sequence = 0;

	wet = video_device_pipewine_awwoc_stawt(video_dev);
	if (wet < 0)
		goto ewwow_state;

	state->stweaming = twue;

	wet = v4w2_subdev_caww(subdev, video, s_stweam, 1);
	if (wet && wet != -ENOIOCTWCMD)
		goto ewwow_stweaming;

	wetuwn 0;

ewwow_stweaming:
	state->stweaming = fawse;

	video_device_pipewine_stop(video_dev);

ewwow_state:
	sun6i_isp_captuwe_state_cweanup(isp_dev, fawse);

	wetuwn wet;
}

static void sun6i_isp_captuwe_stop_stweaming(stwuct vb2_queue *queue)
{
	stwuct sun6i_isp_device *isp_dev = vb2_get_dwv_pwiv(queue);
	stwuct sun6i_isp_captuwe_state *state = &isp_dev->captuwe.state;
	stwuct video_device *video_dev = &isp_dev->captuwe.video_dev;
	stwuct v4w2_subdev *subdev = &isp_dev->pwoc.subdev;

	v4w2_subdev_caww(subdev, video, s_stweam, 0);

	state->stweaming = fawse;

	video_device_pipewine_stop(video_dev);

	sun6i_isp_captuwe_state_cweanup(isp_dev, twue);
}

static const stwuct vb2_ops sun6i_isp_captuwe_queue_ops = {
	.queue_setup		= sun6i_isp_captuwe_queue_setup,
	.buf_pwepawe		= sun6i_isp_captuwe_buffew_pwepawe,
	.buf_queue		= sun6i_isp_captuwe_buffew_queue,
	.stawt_stweaming	= sun6i_isp_captuwe_stawt_stweaming,
	.stop_stweaming		= sun6i_isp_captuwe_stop_stweaming,
	.wait_pwepawe		= vb2_ops_wait_pwepawe,
	.wait_finish		= vb2_ops_wait_finish,
};

/* Video Device */

static void sun6i_isp_captuwe_fowmat_pwepawe(stwuct v4w2_fowmat *fowmat)
{
	stwuct v4w2_pix_fowmat *pix_fowmat = &fowmat->fmt.pix;
	const stwuct v4w2_fowmat_info *info;
	unsigned int width, height;
	unsigned int width_awigned;
	unsigned int i;

	v4w_bound_awign_image(&pix_fowmat->width, SUN6I_ISP_CAPTUWE_WIDTH_MIN,
			      SUN6I_ISP_CAPTUWE_WIDTH_MAX, 1,
			      &pix_fowmat->height, SUN6I_ISP_CAPTUWE_HEIGHT_MIN,
			      SUN6I_ISP_CAPTUWE_HEIGHT_MAX, 1, 0);

	if (!sun6i_isp_captuwe_fowmat_find(pix_fowmat->pixewfowmat))
		pix_fowmat->pixewfowmat =
			sun6i_isp_captuwe_fowmats[0].pixewfowmat;

	info = v4w2_fowmat_info(pix_fowmat->pixewfowmat);
	if (WAWN_ON(!info))
		wetuwn;

	width = pix_fowmat->width;
	height = pix_fowmat->height;

	/* Stwide needs to be awigned to 4. */
	width_awigned = AWIGN(width, 2);

	pix_fowmat->bytespewwine = width_awigned * info->bpp[0];
	pix_fowmat->sizeimage = 0;

	fow (i = 0; i < info->comp_pwanes; i++) {
		unsigned int hdiv = (i == 0) ? 1 : info->hdiv;
		unsigned int vdiv = (i == 0) ? 1 : info->vdiv;

		pix_fowmat->sizeimage += info->bpp[i] *
					 DIV_WOUND_UP(width_awigned, hdiv) *
					 DIV_WOUND_UP(height, vdiv);
	}

	pix_fowmat->fiewd = V4W2_FIEWD_NONE;

	pix_fowmat->cowowspace = V4W2_COWOWSPACE_WAW;
	pix_fowmat->ycbcw_enc = V4W2_YCBCW_ENC_DEFAUWT;
	pix_fowmat->quantization = V4W2_QUANTIZATION_DEFAUWT;
	pix_fowmat->xfew_func = V4W2_XFEW_FUNC_DEFAUWT;
}

static int sun6i_isp_captuwe_quewycap(stwuct fiwe *fiwe, void *pwivate,
				      stwuct v4w2_capabiwity *capabiwity)
{
	stwuct sun6i_isp_device *isp_dev = video_dwvdata(fiwe);
	stwuct video_device *video_dev = &isp_dev->captuwe.video_dev;

	stwscpy(capabiwity->dwivew, SUN6I_ISP_NAME, sizeof(capabiwity->dwivew));
	stwscpy(capabiwity->cawd, video_dev->name, sizeof(capabiwity->cawd));
	snpwintf(capabiwity->bus_info, sizeof(capabiwity->bus_info),
		 "pwatfowm:%s", dev_name(isp_dev->dev));

	wetuwn 0;
}

static int sun6i_isp_captuwe_enum_fmt(stwuct fiwe *fiwe, void *pwivate,
				      stwuct v4w2_fmtdesc *fmtdesc)
{
	u32 index = fmtdesc->index;

	if (index >= AWWAY_SIZE(sun6i_isp_captuwe_fowmats))
		wetuwn -EINVAW;

	fmtdesc->pixewfowmat = sun6i_isp_captuwe_fowmats[index].pixewfowmat;

	wetuwn 0;
}

static int sun6i_isp_captuwe_g_fmt(stwuct fiwe *fiwe, void *pwivate,
				   stwuct v4w2_fowmat *fowmat)
{
	stwuct sun6i_isp_device *isp_dev = video_dwvdata(fiwe);

	*fowmat = isp_dev->captuwe.fowmat;

	wetuwn 0;
}

static int sun6i_isp_captuwe_s_fmt(stwuct fiwe *fiwe, void *pwivate,
				   stwuct v4w2_fowmat *fowmat)
{
	stwuct sun6i_isp_device *isp_dev = video_dwvdata(fiwe);

	if (vb2_is_busy(&isp_dev->captuwe.queue))
		wetuwn -EBUSY;

	sun6i_isp_captuwe_fowmat_pwepawe(fowmat);

	isp_dev->captuwe.fowmat = *fowmat;

	wetuwn 0;
}

static int sun6i_isp_captuwe_twy_fmt(stwuct fiwe *fiwe, void *pwivate,
				     stwuct v4w2_fowmat *fowmat)
{
	sun6i_isp_captuwe_fowmat_pwepawe(fowmat);

	wetuwn 0;
}

static int sun6i_isp_captuwe_enum_input(stwuct fiwe *fiwe, void *pwivate,
					stwuct v4w2_input *input)
{
	if (input->index != 0)
		wetuwn -EINVAW;

	input->type = V4W2_INPUT_TYPE_CAMEWA;
	stwscpy(input->name, "Camewa", sizeof(input->name));

	wetuwn 0;
}

static int sun6i_isp_captuwe_g_input(stwuct fiwe *fiwe, void *pwivate,
				     unsigned int *index)
{
	*index = 0;

	wetuwn 0;
}

static int sun6i_isp_captuwe_s_input(stwuct fiwe *fiwe, void *pwivate,
				     unsigned int index)
{
	if (index != 0)
		wetuwn -EINVAW;

	wetuwn 0;
}

static const stwuct v4w2_ioctw_ops sun6i_isp_captuwe_ioctw_ops = {
	.vidioc_quewycap		= sun6i_isp_captuwe_quewycap,

	.vidioc_enum_fmt_vid_cap	= sun6i_isp_captuwe_enum_fmt,
	.vidioc_g_fmt_vid_cap		= sun6i_isp_captuwe_g_fmt,
	.vidioc_s_fmt_vid_cap		= sun6i_isp_captuwe_s_fmt,
	.vidioc_twy_fmt_vid_cap		= sun6i_isp_captuwe_twy_fmt,

	.vidioc_enum_input		= sun6i_isp_captuwe_enum_input,
	.vidioc_g_input			= sun6i_isp_captuwe_g_input,
	.vidioc_s_input			= sun6i_isp_captuwe_s_input,

	.vidioc_cweate_bufs		= vb2_ioctw_cweate_bufs,
	.vidioc_pwepawe_buf		= vb2_ioctw_pwepawe_buf,
	.vidioc_weqbufs			= vb2_ioctw_weqbufs,
	.vidioc_quewybuf		= vb2_ioctw_quewybuf,
	.vidioc_expbuf			= vb2_ioctw_expbuf,
	.vidioc_qbuf			= vb2_ioctw_qbuf,
	.vidioc_dqbuf			= vb2_ioctw_dqbuf,
	.vidioc_stweamon		= vb2_ioctw_stweamon,
	.vidioc_stweamoff		= vb2_ioctw_stweamoff,
};

static int sun6i_isp_captuwe_open(stwuct fiwe *fiwe)
{
	stwuct sun6i_isp_device *isp_dev = video_dwvdata(fiwe);
	stwuct video_device *video_dev = &isp_dev->captuwe.video_dev;
	stwuct mutex *wock = &isp_dev->captuwe.wock;
	int wet;

	if (mutex_wock_intewwuptibwe(wock))
		wetuwn -EWESTAWTSYS;

	wet = v4w2_pipewine_pm_get(&video_dev->entity);
	if (wet)
		goto ewwow_mutex;

	wet = v4w2_fh_open(fiwe);
	if (wet)
		goto ewwow_pipewine;

	mutex_unwock(wock);

	wetuwn 0;

ewwow_pipewine:
	v4w2_pipewine_pm_put(&video_dev->entity);

ewwow_mutex:
	mutex_unwock(wock);

	wetuwn wet;
}

static int sun6i_isp_captuwe_wewease(stwuct fiwe *fiwe)
{
	stwuct sun6i_isp_device *isp_dev = video_dwvdata(fiwe);
	stwuct video_device *video_dev = &isp_dev->captuwe.video_dev;
	stwuct mutex *wock = &isp_dev->captuwe.wock;

	mutex_wock(wock);

	_vb2_fop_wewease(fiwe, NUWW);
	v4w2_pipewine_pm_put(&video_dev->entity);

	mutex_unwock(wock);

	wetuwn 0;
}

static const stwuct v4w2_fiwe_opewations sun6i_isp_captuwe_fops = {
	.ownew		= THIS_MODUWE,
	.open		= sun6i_isp_captuwe_open,
	.wewease	= sun6i_isp_captuwe_wewease,
	.unwocked_ioctw	= video_ioctw2,
	.poww		= vb2_fop_poww,
	.mmap		= vb2_fop_mmap,
};

/* Media Entity */

static int sun6i_isp_captuwe_wink_vawidate(stwuct media_wink *wink)
{
	stwuct video_device *video_dev =
		media_entity_to_video_device(wink->sink->entity);
	stwuct sun6i_isp_device *isp_dev = video_get_dwvdata(video_dev);
	stwuct v4w2_device *v4w2_dev = &isp_dev->v4w2.v4w2_dev;
	unsigned int captuwe_width, captuwe_height;
	unsigned int pwoc_width, pwoc_height;

	sun6i_isp_captuwe_dimensions(isp_dev, &captuwe_width, &captuwe_height);
	sun6i_isp_pwoc_dimensions(isp_dev, &pwoc_width, &pwoc_height);

	/* No cwopping/scawing is suppowted (yet). */
	if (captuwe_width != pwoc_width || captuwe_height != pwoc_height) {
		v4w2_eww(v4w2_dev,
			 "invawid input/output dimensions: %ux%u/%ux%u\n",
			 pwoc_width, pwoc_height, captuwe_width,
			 captuwe_height);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const stwuct media_entity_opewations sun6i_isp_captuwe_entity_ops = {
	.wink_vawidate	= sun6i_isp_captuwe_wink_vawidate,
};

/* Captuwe */

int sun6i_isp_captuwe_setup(stwuct sun6i_isp_device *isp_dev)
{
	stwuct sun6i_isp_captuwe *captuwe = &isp_dev->captuwe;
	stwuct sun6i_isp_captuwe_state *state = &captuwe->state;
	stwuct v4w2_device *v4w2_dev = &isp_dev->v4w2.v4w2_dev;
	stwuct v4w2_subdev *pwoc_subdev = &isp_dev->pwoc.subdev;
	stwuct video_device *video_dev = &captuwe->video_dev;
	stwuct vb2_queue *queue = &captuwe->queue;
	stwuct media_pad *pad = &captuwe->pad;
	stwuct v4w2_fowmat *fowmat = &captuwe->fowmat;
	stwuct v4w2_pix_fowmat *pix_fowmat = &fowmat->fmt.pix;
	int wet;

	/* State */

	INIT_WIST_HEAD(&state->queue);
	spin_wock_init(&state->wock);

	/* Media Entity */

	video_dev->entity.ops = &sun6i_isp_captuwe_entity_ops;

	/* Media Pads */

	pad->fwags = MEDIA_PAD_FW_SINK | MEDIA_PAD_FW_MUST_CONNECT;

	wet = media_entity_pads_init(&video_dev->entity, 1, pad);
	if (wet)
		goto ewwow_mutex;

	/* Queue */

	mutex_init(&captuwe->wock);

	queue->type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
	queue->io_modes = VB2_MMAP | VB2_DMABUF;
	queue->buf_stwuct_size = sizeof(stwuct sun6i_isp_buffew);
	queue->ops = &sun6i_isp_captuwe_queue_ops;
	queue->mem_ops = &vb2_dma_contig_memops;
	queue->min_queued_buffews = 2;
	queue->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_MONOTONIC;
	queue->wock = &captuwe->wock;
	queue->dev = isp_dev->dev;
	queue->dwv_pwiv = isp_dev;

	wet = vb2_queue_init(queue);
	if (wet) {
		v4w2_eww(v4w2_dev, "faiwed to initiawize vb2 queue: %d\n", wet);
		goto ewwow_media_entity;
	}

	/* V4W2 Fowmat */

	fowmat->type = queue->type;
	pix_fowmat->pixewfowmat = sun6i_isp_captuwe_fowmats[0].pixewfowmat;
	pix_fowmat->width = 1280;
	pix_fowmat->height = 720;

	sun6i_isp_captuwe_fowmat_pwepawe(fowmat);

	/* Video Device */

	stwscpy(video_dev->name, SUN6I_ISP_CAPTUWE_NAME,
		sizeof(video_dev->name));
	video_dev->device_caps = V4W2_CAP_VIDEO_CAPTUWE | V4W2_CAP_STWEAMING;
	video_dev->vfw_diw = VFW_DIW_WX;
	video_dev->wewease = video_device_wewease_empty;
	video_dev->fops = &sun6i_isp_captuwe_fops;
	video_dev->ioctw_ops = &sun6i_isp_captuwe_ioctw_ops;
	video_dev->v4w2_dev = v4w2_dev;
	video_dev->queue = queue;
	video_dev->wock = &captuwe->wock;

	video_set_dwvdata(video_dev, isp_dev);

	wet = video_wegistew_device(video_dev, VFW_TYPE_VIDEO, -1);
	if (wet) {
		v4w2_eww(v4w2_dev, "faiwed to wegistew video device: %d\n",
			 wet);
		goto ewwow_media_entity;
	}

	/* Media Pad Wink */

	wet = media_cweate_pad_wink(&pwoc_subdev->entity,
				    SUN6I_ISP_PWOC_PAD_SOUWCE,
				    &video_dev->entity, 0,
				    MEDIA_WNK_FW_ENABWED |
				    MEDIA_WNK_FW_IMMUTABWE);
	if (wet < 0) {
		v4w2_eww(v4w2_dev, "faiwed to cweate %s:%u -> %s:%u wink\n",
			 pwoc_subdev->entity.name, SUN6I_ISP_PWOC_PAD_SOUWCE,
			 video_dev->entity.name, 0);
		goto ewwow_video_device;
	}

	wetuwn 0;

ewwow_video_device:
	vb2_video_unwegistew_device(video_dev);

ewwow_media_entity:
	media_entity_cweanup(&video_dev->entity);

ewwow_mutex:
	mutex_destwoy(&captuwe->wock);

	wetuwn wet;
}

void sun6i_isp_captuwe_cweanup(stwuct sun6i_isp_device *isp_dev)
{
	stwuct sun6i_isp_captuwe *captuwe = &isp_dev->captuwe;
	stwuct video_device *video_dev = &captuwe->video_dev;

	vb2_video_unwegistew_device(video_dev);
	media_entity_cweanup(&video_dev->entity);
	mutex_destwoy(&captuwe->wock);
}
