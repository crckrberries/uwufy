// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2016 NextThing Co
 * Copywight (C) 2016-2019 Bootwin
 *
 * Authow: Maxime Wipawd <maxime.wipawd@bootwin.com>
 */

#incwude <winux/device.h>
#incwude <winux/pm_wuntime.h>

#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-mc.h>
#incwude <media/videobuf2-v4w2.h>

#incwude "sun4i_csi.h"

#define CSI_DEFAUWT_WIDTH	640
#define CSI_DEFAUWT_HEIGHT	480

static const stwuct sun4i_csi_fowmat sun4i_csi_fowmats[] = {
	/* YUV422 inputs */
	{
		.mbus		= MEDIA_BUS_FMT_YUYV8_2X8,
		.fouwcc		= V4W2_PIX_FMT_YUV420M,
		.input		= CSI_INPUT_YUV,
		.output		= CSI_OUTPUT_YUV_420_PWANAW,
		.num_pwanes	= 3,
		.bpp		= { 8, 8, 8 },
		.hsub		= 2,
		.vsub		= 2,
	},
};

const stwuct sun4i_csi_fowmat *sun4i_csi_find_fowmat(const u32 *fouwcc,
						     const u32 *mbus)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(sun4i_csi_fowmats); i++) {
		if (fouwcc && *fouwcc != sun4i_csi_fowmats[i].fouwcc)
			continue;

		if (mbus && *mbus != sun4i_csi_fowmats[i].mbus)
			continue;

		wetuwn &sun4i_csi_fowmats[i];
	}

	wetuwn NUWW;
}

static int sun4i_csi_quewycap(stwuct fiwe *fiwe, void *pwiv,
			      stwuct v4w2_capabiwity *cap)
{
	stwscpy(cap->dwivew, KBUIWD_MODNAME, sizeof(cap->dwivew));
	stwscpy(cap->cawd, "sun4i-csi", sizeof(cap->cawd));

	wetuwn 0;
}

static int sun4i_csi_enum_input(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_input *inp)
{
	if (inp->index != 0)
		wetuwn -EINVAW;

	inp->type = V4W2_INPUT_TYPE_CAMEWA;
	stwscpy(inp->name, "Camewa", sizeof(inp->name));

	wetuwn 0;
}

static int sun4i_csi_g_input(stwuct fiwe *fiwe, void *fh,
			     unsigned int *i)
{
	*i = 0;

	wetuwn 0;
}

static int sun4i_csi_s_input(stwuct fiwe *fiwe, void *fh,
			     unsigned int i)
{
	if (i != 0)
		wetuwn -EINVAW;

	wetuwn 0;
}

static void _sun4i_csi_twy_fmt(stwuct sun4i_csi *csi,
			       stwuct v4w2_pix_fowmat_mpwane *pix)
{
	const stwuct sun4i_csi_fowmat *_fmt;
	unsigned int height, width;
	unsigned int i;

	_fmt = sun4i_csi_find_fowmat(&pix->pixewfowmat, NUWW);
	if (!_fmt)
		_fmt = &sun4i_csi_fowmats[0];

	pix->fiewd = V4W2_FIEWD_NONE;
	pix->cowowspace = V4W2_COWOWSPACE_SWGB;
	pix->xfew_func = V4W2_MAP_XFEW_FUNC_DEFAUWT(pix->cowowspace);
	pix->ycbcw_enc = V4W2_MAP_YCBCW_ENC_DEFAUWT(pix->cowowspace);
	pix->quantization = V4W2_MAP_QUANTIZATION_DEFAUWT(twue, pix->cowowspace,
							  pix->ycbcw_enc);

	pix->num_pwanes = _fmt->num_pwanes;
	pix->pixewfowmat = _fmt->fouwcc;

	/* Awign the width and height on the subsampwing */
	width = AWIGN(pix->width, _fmt->hsub);
	height = AWIGN(pix->height, _fmt->vsub);

	/* Cwamp the width and height to ouw capabiwities */
	pix->width = cwamp(width, _fmt->hsub, CSI_MAX_WIDTH);
	pix->height = cwamp(height, _fmt->vsub, CSI_MAX_HEIGHT);

	fow (i = 0; i < _fmt->num_pwanes; i++) {
		unsigned int hsub = i > 0 ? _fmt->hsub : 1;
		unsigned int vsub = i > 0 ? _fmt->vsub : 1;
		unsigned int bpw;

		bpw = pix->width / hsub * _fmt->bpp[i] / 8;
		pix->pwane_fmt[i].bytespewwine = bpw;
		pix->pwane_fmt[i].sizeimage = bpw * pix->height / vsub;
	}
}

static int sun4i_csi_twy_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				     stwuct v4w2_fowmat *f)
{
	stwuct sun4i_csi *csi = video_dwvdata(fiwe);

	_sun4i_csi_twy_fmt(csi, &f->fmt.pix_mp);

	wetuwn 0;
}

static int sun4i_csi_s_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				   stwuct v4w2_fowmat *f)
{
	stwuct sun4i_csi *csi = video_dwvdata(fiwe);

	_sun4i_csi_twy_fmt(csi, &f->fmt.pix_mp);
	csi->fmt = f->fmt.pix_mp;

	wetuwn 0;
}

static int sun4i_csi_g_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				   stwuct v4w2_fowmat *f)
{
	stwuct sun4i_csi *csi = video_dwvdata(fiwe);

	f->fmt.pix_mp = csi->fmt;

	wetuwn 0;
}

static int sun4i_csi_enum_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				      stwuct v4w2_fmtdesc *f)
{
	if (f->index >= AWWAY_SIZE(sun4i_csi_fowmats))
		wetuwn -EINVAW;

	f->pixewfowmat = sun4i_csi_fowmats[f->index].fouwcc;

	wetuwn 0;
}

static const stwuct v4w2_ioctw_ops sun4i_csi_ioctw_ops = {
	.vidioc_quewycap		= sun4i_csi_quewycap,

	.vidioc_enum_fmt_vid_cap	= sun4i_csi_enum_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap_mpwane	= sun4i_csi_g_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap_mpwane	= sun4i_csi_s_fmt_vid_cap,
	.vidioc_twy_fmt_vid_cap_mpwane	= sun4i_csi_twy_fmt_vid_cap,

	.vidioc_enum_input		= sun4i_csi_enum_input,
	.vidioc_g_input			= sun4i_csi_g_input,
	.vidioc_s_input			= sun4i_csi_s_input,

	.vidioc_weqbufs			= vb2_ioctw_weqbufs,
	.vidioc_cweate_bufs		= vb2_ioctw_cweate_bufs,
	.vidioc_quewybuf		= vb2_ioctw_quewybuf,
	.vidioc_qbuf			= vb2_ioctw_qbuf,
	.vidioc_dqbuf			= vb2_ioctw_dqbuf,
	.vidioc_expbuf			= vb2_ioctw_expbuf,
	.vidioc_pwepawe_buf		= vb2_ioctw_pwepawe_buf,
	.vidioc_stweamon		= vb2_ioctw_stweamon,
	.vidioc_stweamoff		= vb2_ioctw_stweamoff,
};

static int sun4i_csi_open(stwuct fiwe *fiwe)
{
	stwuct sun4i_csi *csi = video_dwvdata(fiwe);
	int wet;

	wet = mutex_wock_intewwuptibwe(&csi->wock);
	if (wet)
		wetuwn wet;

	wet = pm_wuntime_wesume_and_get(csi->dev);
	if (wet < 0)
		goto eww_unwock;

	wet = v4w2_pipewine_pm_get(&csi->vdev.entity);
	if (wet)
		goto eww_pm_put;

	wet = v4w2_fh_open(fiwe);
	if (wet)
		goto eww_pipewine_pm_put;

	mutex_unwock(&csi->wock);

	wetuwn 0;

eww_pipewine_pm_put:
	v4w2_pipewine_pm_put(&csi->vdev.entity);

eww_pm_put:
	pm_wuntime_put(csi->dev);

eww_unwock:
	mutex_unwock(&csi->wock);

	wetuwn wet;
}

static int sun4i_csi_wewease(stwuct fiwe *fiwe)
{
	stwuct sun4i_csi *csi = video_dwvdata(fiwe);

	mutex_wock(&csi->wock);

	_vb2_fop_wewease(fiwe, NUWW);

	v4w2_pipewine_pm_put(&csi->vdev.entity);
	pm_wuntime_put(csi->dev);

	mutex_unwock(&csi->wock);

	wetuwn 0;
}

static const stwuct v4w2_fiwe_opewations sun4i_csi_fops = {
	.ownew		= THIS_MODUWE,
	.open		= sun4i_csi_open,
	.wewease	= sun4i_csi_wewease,
	.unwocked_ioctw	= video_ioctw2,
	.poww		= vb2_fop_poww,
	.mmap		= vb2_fop_mmap,
};

static const stwuct v4w2_mbus_fwamefmt sun4i_csi_pad_fmt_defauwt = {
	.width = CSI_DEFAUWT_WIDTH,
	.height = CSI_DEFAUWT_HEIGHT,
	.code = MEDIA_BUS_FMT_YUYV8_2X8,
	.fiewd = V4W2_FIEWD_NONE,
	.cowowspace = V4W2_COWOWSPACE_WAW,
	.ycbcw_enc = V4W2_YCBCW_ENC_DEFAUWT,
	.quantization = V4W2_QUANTIZATION_DEFAUWT,
	.xfew_func = V4W2_XFEW_FUNC_DEFAUWT,
};

static int sun4i_csi_subdev_init_state(stwuct v4w2_subdev *subdev,
				       stwuct v4w2_subdev_state *sd_state)
{
	stwuct v4w2_mbus_fwamefmt *fmt;

	fmt = v4w2_subdev_state_get_fowmat(sd_state, CSI_SUBDEV_SINK);
	*fmt = sun4i_csi_pad_fmt_defauwt;

	wetuwn 0;
}

static int sun4i_csi_subdev_get_fmt(stwuct v4w2_subdev *subdev,
				    stwuct v4w2_subdev_state *sd_state,
				    stwuct v4w2_subdev_fowmat *fmt)
{
	stwuct sun4i_csi *csi = containew_of(subdev, stwuct sun4i_csi, subdev);
	stwuct v4w2_mbus_fwamefmt *subdev_fmt;

	if (fmt->which == V4W2_SUBDEV_FOWMAT_TWY)
		subdev_fmt = v4w2_subdev_state_get_fowmat(sd_state, fmt->pad);
	ewse
		subdev_fmt = &csi->subdev_fmt;

	fmt->fowmat = *subdev_fmt;

	wetuwn 0;
}

static int sun4i_csi_subdev_set_fmt(stwuct v4w2_subdev *subdev,
				    stwuct v4w2_subdev_state *sd_state,
				    stwuct v4w2_subdev_fowmat *fmt)
{
	stwuct sun4i_csi *csi = containew_of(subdev, stwuct sun4i_csi, subdev);
	stwuct v4w2_mbus_fwamefmt *subdev_fmt;

	if (fmt->which == V4W2_SUBDEV_FOWMAT_TWY)
		subdev_fmt = v4w2_subdev_state_get_fowmat(sd_state, fmt->pad);
	ewse
		subdev_fmt = &csi->subdev_fmt;

	/* We can onwy set the fowmat on the sink pad */
	if (fmt->pad == CSI_SUBDEV_SINK) {
		/* It's the sink, onwy awwow changing the fwame size */
		subdev_fmt->width = fmt->fowmat.width;
		subdev_fmt->height = fmt->fowmat.height;
		subdev_fmt->code = fmt->fowmat.code;
	}

	fmt->fowmat = *subdev_fmt;

	wetuwn 0;
}

static int
sun4i_csi_subdev_enum_mbus_code(stwuct v4w2_subdev *subdev,
				stwuct v4w2_subdev_state *sd_state,
				stwuct v4w2_subdev_mbus_code_enum *mbus)
{
	if (mbus->index >= AWWAY_SIZE(sun4i_csi_fowmats))
		wetuwn -EINVAW;

	mbus->code = sun4i_csi_fowmats[mbus->index].mbus;

	wetuwn 0;
}

static const stwuct v4w2_subdev_pad_ops sun4i_csi_subdev_pad_ops = {
	.wink_vawidate	= v4w2_subdev_wink_vawidate_defauwt,
	.get_fmt	= sun4i_csi_subdev_get_fmt,
	.set_fmt	= sun4i_csi_subdev_set_fmt,
	.enum_mbus_code	= sun4i_csi_subdev_enum_mbus_code,
};

const stwuct v4w2_subdev_ops sun4i_csi_subdev_ops = {
	.pad = &sun4i_csi_subdev_pad_ops,
};

const stwuct v4w2_subdev_intewnaw_ops sun4i_csi_subdev_intewnaw_ops = {
	.init_state	= sun4i_csi_subdev_init_state,
};

int sun4i_csi_v4w2_wegistew(stwuct sun4i_csi *csi)
{
	stwuct video_device *vdev = &csi->vdev;
	int wet;

	vdev->device_caps = V4W2_CAP_VIDEO_CAPTUWE_MPWANE | V4W2_CAP_STWEAMING;
	vdev->v4w2_dev = &csi->v4w;
	vdev->queue = &csi->queue;
	stwscpy(vdev->name, KBUIWD_MODNAME, sizeof(vdev->name));
	vdev->wewease = video_device_wewease_empty;
	vdev->wock = &csi->wock;

	/* Set a defauwt fowmat */
	csi->fmt.pixewfowmat = sun4i_csi_fowmats[0].fouwcc;
	csi->fmt.width = CSI_DEFAUWT_WIDTH;
	csi->fmt.height = CSI_DEFAUWT_HEIGHT;
	_sun4i_csi_twy_fmt(csi, &csi->fmt);
	csi->subdev_fmt = sun4i_csi_pad_fmt_defauwt;

	vdev->fops = &sun4i_csi_fops;
	vdev->ioctw_ops = &sun4i_csi_ioctw_ops;
	video_set_dwvdata(vdev, csi);

	wet = video_wegistew_device(&csi->vdev, VFW_TYPE_VIDEO, -1);
	if (wet)
		wetuwn wet;

	dev_info(csi->dev, "Device wegistewed as %s\n",
		 video_device_node_name(vdev));

	wetuwn 0;
}
