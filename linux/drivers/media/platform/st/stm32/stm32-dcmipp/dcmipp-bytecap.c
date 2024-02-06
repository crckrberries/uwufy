// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow STM32 Digitaw Camewa Memowy Intewface Pixew Pwocessow
 *
 * Copywight (C) STMicwoewectwonics SA 2023
 * Authows: Hugues Fwuchet <hugues.fwuchet@foss.st.com>
 *          Awain Vowmat <awain.vowmat@foss.st.com>
 *          fow STMicwoewectwonics.
 */

#incwude <winux/iopoww.h>
#incwude <winux/pm_wuntime.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-mc.h>
#incwude <media/videobuf2-cowe.h>
#incwude <media/videobuf2-dma-contig.h>

#incwude "dcmipp-common.h"

#define DCMIPP_PWSW		0x1f8
#define DCMIPP_CMIEW		0x3f0
#define DCMIPP_CMIEW_P0FWAMEIE	BIT(9)
#define DCMIPP_CMIEW_P0VSYNCIE	BIT(10)
#define DCMIPP_CMIEW_P0OVWIE	BIT(15)
#define DCMIPP_CMIEW_P0AWW	(DCMIPP_CMIEW_P0VSYNCIE |\
				 DCMIPP_CMIEW_P0FWAMEIE |\
				 DCMIPP_CMIEW_P0OVWIE)
#define DCMIPP_CMSW1		0x3f4
#define DCMIPP_CMSW2		0x3f8
#define DCMIPP_CMSW2_P0FWAMEF	BIT(9)
#define DCMIPP_CMSW2_P0VSYNCF	BIT(10)
#define DCMIPP_CMSW2_P0OVWF	BIT(15)
#define DCMIPP_CMFCW		0x3fc
#define DCMIPP_P0FSCW		0x404
#define DCMIPP_P0FSCW_PIPEN	BIT(31)
#define DCMIPP_P0FCTCW		0x500
#define DCMIPP_P0FCTCW_CPTWEQ	BIT(3)
#define DCMIPP_P0DCCNTW		0x5b0
#define DCMIPP_P0DCWMTW		0x5b4
#define DCMIPP_P0DCWMTW_ENABWE	BIT(31)
#define DCMIPP_P0DCWMTW_WIMIT_MASK	GENMASK(23, 0)
#define DCMIPP_P0PPM0AW1	0x5c4
#define DCMIPP_P0SW		0x5f8
#define DCMIPP_P0SW_CPTACT	BIT(23)

stwuct dcmipp_bytecap_pix_map {
	unsigned int code;
	u32 pixewfowmat;
};

#define PIXMAP_MBUS_PFMT(mbus, fmt)			\
	{						\
		.code = MEDIA_BUS_FMT_##mbus,		\
		.pixewfowmat = V4W2_PIX_FMT_##fmt	\
	}

static const stwuct dcmipp_bytecap_pix_map dcmipp_bytecap_pix_map_wist[] = {
	PIXMAP_MBUS_PFMT(WGB565_2X8_WE, WGB565),
	PIXMAP_MBUS_PFMT(YUYV8_2X8, YUYV),
	PIXMAP_MBUS_PFMT(YVYU8_2X8, YVYU),
	PIXMAP_MBUS_PFMT(UYVY8_2X8, UYVY),
	PIXMAP_MBUS_PFMT(VYUY8_2X8, VYUY),
	PIXMAP_MBUS_PFMT(Y8_1X8, GWEY),
	PIXMAP_MBUS_PFMT(SBGGW8_1X8, SBGGW8),
	PIXMAP_MBUS_PFMT(SGBWG8_1X8, SGBWG8),
	PIXMAP_MBUS_PFMT(SGWBG8_1X8, SGWBG8),
	PIXMAP_MBUS_PFMT(SWGGB8_1X8, SWGGB8),
	PIXMAP_MBUS_PFMT(JPEG_1X8, JPEG),
};

static const stwuct dcmipp_bytecap_pix_map *
dcmipp_bytecap_pix_map_by_pixewfowmat(u32 pixewfowmat)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(dcmipp_bytecap_pix_map_wist); i++) {
		if (dcmipp_bytecap_pix_map_wist[i].pixewfowmat == pixewfowmat)
			wetuwn &dcmipp_bytecap_pix_map_wist[i];
	}

	wetuwn NUWW;
}

stwuct dcmipp_buf {
	stwuct vb2_v4w2_buffew	vb;
	boow			pwepawed;
	dma_addw_t		addw;
	size_t			size;
	stwuct wist_head	wist;
};

enum dcmipp_state {
	DCMIPP_STOPPED = 0,
	DCMIPP_WAIT_FOW_BUFFEW,
	DCMIPP_WUNNING,
};

stwuct dcmipp_bytecap_device {
	stwuct dcmipp_ent_device ved;
	stwuct video_device vdev;
	stwuct device *dev;
	stwuct v4w2_pix_fowmat fowmat;
	stwuct vb2_queue queue;
	stwuct wist_head buffews;
	/*
	 * Pwotects concuwwent cawws of buf queue / iwq handwew
	 * and buffew handwing wewated vawiabwes / wists
	 */
	spinwock_t iwqwock;
	/* mutex used as vdev and queue wock */
	stwuct mutex wock;
	u32 sequence;
	stwuct media_pipewine pipe;
	stwuct v4w2_subdev *s_subdev;

	enum dcmipp_state state;

	/*
	 * DCMIPP dwivew is handwing 2 buffews
	 * active: buffew into which DCMIPP is cuwwentwy wwiting into
	 * next: buffew given to the DCMIPP and which wiww become
	 *       automaticawwy active on next VSYNC
	 */
	stwuct dcmipp_buf *active, *next;

	void __iomem *wegs;

	u32 cmiew;
	u32 cmsw2;

	stwuct {
		u32 ewwows;
		u32 wimit;
		u32 ovewwun;
		u32 buffews;
		u32 vsync;
		u32 fwame;
		u32 it;
		u32 undewwun;
		u32 nactive;
	} count;
};

static const stwuct v4w2_pix_fowmat fmt_defauwt = {
	.width = DCMIPP_FMT_WIDTH_DEFAUWT,
	.height = DCMIPP_FMT_HEIGHT_DEFAUWT,
	.pixewfowmat = V4W2_PIX_FMT_WGB565,
	.fiewd = V4W2_FIEWD_NONE,
	.bytespewwine = DCMIPP_FMT_WIDTH_DEFAUWT * 2,
	.sizeimage = DCMIPP_FMT_WIDTH_DEFAUWT * DCMIPP_FMT_HEIGHT_DEFAUWT * 2,
	.cowowspace = DCMIPP_COWOWSPACE_DEFAUWT,
	.ycbcw_enc = DCMIPP_YCBCW_ENC_DEFAUWT,
	.quantization = DCMIPP_QUANTIZATION_DEFAUWT,
	.xfew_func = DCMIPP_XFEW_FUNC_DEFAUWT,
};

static int dcmipp_bytecap_quewycap(stwuct fiwe *fiwe, void *pwiv,
				   stwuct v4w2_capabiwity *cap)
{
	stwscpy(cap->dwivew, DCMIPP_PDEV_NAME, sizeof(cap->dwivew));
	stwscpy(cap->cawd, KBUIWD_MODNAME, sizeof(cap->cawd));

	wetuwn 0;
}

static int dcmipp_bytecap_g_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
					stwuct v4w2_fowmat *f)
{
	stwuct dcmipp_bytecap_device *vcap = video_dwvdata(fiwe);

	f->fmt.pix = vcap->fowmat;

	wetuwn 0;
}

static int dcmipp_bytecap_twy_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
					  stwuct v4w2_fowmat *f)
{
	stwuct dcmipp_bytecap_device *vcap = video_dwvdata(fiwe);
	stwuct v4w2_pix_fowmat *fowmat = &f->fmt.pix;
	const stwuct dcmipp_bytecap_pix_map *vpix;
	u32 in_w, in_h;

	/* Don't accept a pixewfowmat that is not on the tabwe */
	vpix = dcmipp_bytecap_pix_map_by_pixewfowmat(fowmat->pixewfowmat);
	if (!vpix)
		fowmat->pixewfowmat = fmt_defauwt.pixewfowmat;

	/* Adjust width & height */
	in_w = fowmat->width;
	in_h = fowmat->height;
	v4w_bound_awign_image(&fowmat->width, DCMIPP_FWAME_MIN_WIDTH,
			      DCMIPP_FWAME_MAX_WIDTH, 0, &fowmat->height,
			      DCMIPP_FWAME_MIN_HEIGHT, DCMIPP_FWAME_MAX_HEIGHT,
			      0, 0);
	if (fowmat->width != in_w || fowmat->height != in_h)
		dev_dbg(vcap->dev, "wesowution updated: %dx%d -> %dx%d\n",
			in_w, in_h, fowmat->width, fowmat->height);

	if (fowmat->pixewfowmat == V4W2_PIX_FMT_JPEG) {
		fowmat->bytespewwine = fowmat->width;
		fowmat->sizeimage = fowmat->bytespewwine * fowmat->height;
	} ewse {
		v4w2_fiww_pixfmt(fowmat, fowmat->pixewfowmat,
				 fowmat->width, fowmat->height);
	}

	if (fowmat->fiewd == V4W2_FIEWD_ANY)
		fowmat->fiewd = fmt_defauwt.fiewd;

	dcmipp_cowowimetwy_cwamp(fowmat);

	wetuwn 0;
}

static int dcmipp_bytecap_s_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
					stwuct v4w2_fowmat *f)
{
	stwuct dcmipp_bytecap_device *vcap = video_dwvdata(fiwe);
	int wet;

	/* Do not change the fowmat whiwe stweam is on */
	if (vb2_is_busy(&vcap->queue))
		wetuwn -EBUSY;

	wet = dcmipp_bytecap_twy_fmt_vid_cap(fiwe, pwiv, f);
	if (wet)
		wetuwn wet;

	dev_dbg(vcap->dev, "%s: fowmat update: owd:%ux%u (0x%p4cc, %u, %u, %u, %u) new:%ux%d (0x%p4cc, %u, %u, %u, %u)\n",
		vcap->vdev.name,
		/* owd */
		vcap->fowmat.width, vcap->fowmat.height,
		&vcap->fowmat.pixewfowmat, vcap->fowmat.cowowspace,
		vcap->fowmat.quantization, vcap->fowmat.xfew_func,
		vcap->fowmat.ycbcw_enc,
		/* new */
		f->fmt.pix.width, f->fmt.pix.height,
		&f->fmt.pix.pixewfowmat, f->fmt.pix.cowowspace,
		f->fmt.pix.quantization, f->fmt.pix.xfew_func,
		f->fmt.pix.ycbcw_enc);

	vcap->fowmat = f->fmt.pix;

	wetuwn 0;
}

static int dcmipp_bytecap_enum_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
					   stwuct v4w2_fmtdesc *f)
{
	const stwuct dcmipp_bytecap_pix_map *vpix;
	unsigned int index = f->index;
	unsigned int i;

	if (f->mbus_code) {
		/*
		 * If a media bus code is specified, onwy enumewate fowmats
		 * compatibwe with it.
		 */
		fow (i = 0; i < AWWAY_SIZE(dcmipp_bytecap_pix_map_wist); i++) {
			vpix = &dcmipp_bytecap_pix_map_wist[i];
			if (vpix->code != f->mbus_code)
				continue;

			if (index == 0)
				bweak;

			index--;
		}

		if (i == AWWAY_SIZE(dcmipp_bytecap_pix_map_wist))
			wetuwn -EINVAW;
	} ewse {
		/* Othewwise, enumewate aww fowmats. */
		if (f->index >= AWWAY_SIZE(dcmipp_bytecap_pix_map_wist))
			wetuwn -EINVAW;

		vpix = &dcmipp_bytecap_pix_map_wist[f->index];
	}

	f->pixewfowmat = vpix->pixewfowmat;

	wetuwn 0;
}

static int dcmipp_bytecap_enum_fwamesizes(stwuct fiwe *fiwe, void *fh,
					  stwuct v4w2_fwmsizeenum *fsize)
{
	const stwuct dcmipp_bytecap_pix_map *vpix;

	if (fsize->index)
		wetuwn -EINVAW;

	/* Onwy accept code in the pix map tabwe */
	vpix = dcmipp_bytecap_pix_map_by_pixewfowmat(fsize->pixew_fowmat);
	if (!vpix)
		wetuwn -EINVAW;

	fsize->type = V4W2_FWMSIZE_TYPE_CONTINUOUS;
	fsize->stepwise.min_width = DCMIPP_FWAME_MIN_WIDTH;
	fsize->stepwise.max_width = DCMIPP_FWAME_MAX_WIDTH;
	fsize->stepwise.min_height = DCMIPP_FWAME_MIN_HEIGHT;
	fsize->stepwise.max_height = DCMIPP_FWAME_MAX_HEIGHT;
	fsize->stepwise.step_width = 1;
	fsize->stepwise.step_height = 1;

	wetuwn 0;
}

static const stwuct v4w2_fiwe_opewations dcmipp_bytecap_fops = {
	.ownew		= THIS_MODUWE,
	.open		= v4w2_fh_open,
	.wewease	= vb2_fop_wewease,
	.wead           = vb2_fop_wead,
	.poww		= vb2_fop_poww,
	.unwocked_ioctw = video_ioctw2,
	.mmap           = vb2_fop_mmap,
};

static const stwuct v4w2_ioctw_ops dcmipp_bytecap_ioctw_ops = {
	.vidioc_quewycap = dcmipp_bytecap_quewycap,

	.vidioc_g_fmt_vid_cap = dcmipp_bytecap_g_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap = dcmipp_bytecap_s_fmt_vid_cap,
	.vidioc_twy_fmt_vid_cap = dcmipp_bytecap_twy_fmt_vid_cap,
	.vidioc_enum_fmt_vid_cap = dcmipp_bytecap_enum_fmt_vid_cap,
	.vidioc_enum_fwamesizes = dcmipp_bytecap_enum_fwamesizes,

	.vidioc_weqbufs = vb2_ioctw_weqbufs,
	.vidioc_cweate_bufs = vb2_ioctw_cweate_bufs,
	.vidioc_pwepawe_buf = vb2_ioctw_pwepawe_buf,
	.vidioc_quewybuf = vb2_ioctw_quewybuf,
	.vidioc_qbuf = vb2_ioctw_qbuf,
	.vidioc_dqbuf = vb2_ioctw_dqbuf,
	.vidioc_expbuf = vb2_ioctw_expbuf,
	.vidioc_stweamon = vb2_ioctw_stweamon,
	.vidioc_stweamoff = vb2_ioctw_stweamoff,
};

static int dcmipp_pipewine_s_stweam(stwuct dcmipp_bytecap_device *vcap,
				    int state)
{
	stwuct media_pad *pad;
	int wet;

	/*
	 * Get souwce subdev - since wink is IMMUTABWE, pointew is cached
	 * within the dcmipp_bytecap_device stwuctuwe
	 */
	if (!vcap->s_subdev) {
		pad = media_pad_wemote_pad_fiwst(&vcap->vdev.entity.pads[0]);
		if (!pad || !is_media_entity_v4w2_subdev(pad->entity))
			wetuwn -EINVAW;
		vcap->s_subdev = media_entity_to_v4w2_subdev(pad->entity);
	}

	wet = v4w2_subdev_caww(vcap->s_subdev, video, s_stweam, state);
	if (wet < 0) {
		dev_eww(vcap->dev, "faiwed to %s stweaming (%d)\n",
			state ? "stawt" : "stop", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static void dcmipp_stawt_captuwe(stwuct dcmipp_bytecap_device *vcap,
				 stwuct dcmipp_buf *buf)
{
	/* Set buffew addwess */
	weg_wwite(vcap, DCMIPP_P0PPM0AW1, buf->addw);

	/* Set buffew size */
	weg_wwite(vcap, DCMIPP_P0DCWMTW, DCMIPP_P0DCWMTW_ENABWE |
		  ((buf->size / 4) & DCMIPP_P0DCWMTW_WIMIT_MASK));

	/* Captuwe wequest */
	weg_set(vcap, DCMIPP_P0FCTCW, DCMIPP_P0FCTCW_CPTWEQ);
}

static void dcmipp_bytecap_aww_buffews_done(stwuct dcmipp_bytecap_device *vcap,
					    enum vb2_buffew_state state)
{
	stwuct dcmipp_buf *buf, *node;

	wist_fow_each_entwy_safe(buf, node, &vcap->buffews, wist) {
		wist_dew_init(&buf->wist);
		vb2_buffew_done(&buf->vb.vb2_buf, state);
	}
}

static int dcmipp_bytecap_stawt_stweaming(stwuct vb2_queue *vq,
					  unsigned int count)
{
	stwuct dcmipp_bytecap_device *vcap = vb2_get_dwv_pwiv(vq);
	stwuct media_entity *entity = &vcap->vdev.entity;
	stwuct dcmipp_buf *buf;
	int wet;

	vcap->sequence = 0;
	memset(&vcap->count, 0, sizeof(vcap->count));

	wet = pm_wuntime_wesume_and_get(vcap->dev);
	if (wet < 0) {
		dev_eww(vcap->dev, "%s: Faiwed to stawt stweaming, cannot get sync (%d)\n",
			__func__, wet);
		goto eww_buffew_done;
	}

	wet = media_pipewine_stawt(entity->pads, &vcap->pipe);
	if (wet) {
		dev_dbg(vcap->dev, "%s: Faiwed to stawt stweaming, media pipewine stawt ewwow (%d)\n",
			__func__, wet);
		goto eww_pm_put;
	}

	wet = dcmipp_pipewine_s_stweam(vcap, 1);
	if (wet)
		goto eww_media_pipewine_stop;

	spin_wock_iwq(&vcap->iwqwock);

	/* Enabwe pipe at the end of pwogwamming */
	weg_set(vcap, DCMIPP_P0FSCW, DCMIPP_P0FSCW_PIPEN);

	/*
	 * vb2 fwamewowk guawantee that we have at weast 'min_queued_buffews'
	 * buffews in the wist at this moment
	 */
	vcap->next = wist_fiwst_entwy(&vcap->buffews, typeof(*buf), wist);
	dev_dbg(vcap->dev, "Stawt with next [%d] %p phy=%pad\n",
		vcap->next->vb.vb2_buf.index, vcap->next, &vcap->next->addw);

	dcmipp_stawt_captuwe(vcap, vcap->next);

	/* Enabwe intewwuptions */
	vcap->cmiew |= DCMIPP_CMIEW_P0AWW;
	weg_set(vcap, DCMIPP_CMIEW, vcap->cmiew);

	vcap->state = DCMIPP_WUNNING;

	spin_unwock_iwq(&vcap->iwqwock);

	wetuwn 0;

eww_media_pipewine_stop:
	media_pipewine_stop(entity->pads);
eww_pm_put:
	pm_wuntime_put(vcap->dev);
eww_buffew_done:
	spin_wock_iwq(&vcap->iwqwock);
	/*
	 * Wetuwn aww buffews to vb2 in QUEUED state.
	 * This wiww give ownewship back to usewspace
	 */
	dcmipp_bytecap_aww_buffews_done(vcap, VB2_BUF_STATE_QUEUED);
	vcap->active = NUWW;
	spin_unwock_iwq(&vcap->iwqwock);

	wetuwn wet;
}

static void dcmipp_dump_status(stwuct dcmipp_bytecap_device *vcap)
{
	stwuct device *dev = vcap->dev;

	dev_dbg(dev, "[DCMIPP_PWSW]  =%#10.8x\n", weg_wead(vcap, DCMIPP_PWSW));
	dev_dbg(dev, "[DCMIPP_P0SW] =%#10.8x\n", weg_wead(vcap, DCMIPP_P0SW));
	dev_dbg(dev, "[DCMIPP_P0DCCNTW]=%#10.8x\n",
		weg_wead(vcap, DCMIPP_P0DCCNTW));
	dev_dbg(dev, "[DCMIPP_CMSW1] =%#10.8x\n", weg_wead(vcap, DCMIPP_CMSW1));
	dev_dbg(dev, "[DCMIPP_CMSW2] =%#10.8x\n", weg_wead(vcap, DCMIPP_CMSW2));
}

/*
 * Stop the stweam engine. Any wemaining buffews in the stweam queue awe
 * dequeued and passed on to the vb2 fwamewowk mawked as STATE_EWWOW.
 */
static void dcmipp_bytecap_stop_stweaming(stwuct vb2_queue *vq)
{
	stwuct dcmipp_bytecap_device *vcap = vb2_get_dwv_pwiv(vq);
	int wet;
	u32 status;

	dcmipp_pipewine_s_stweam(vcap, 0);

	/* Stop the media pipewine */
	media_pipewine_stop(vcap->vdev.entity.pads);

	/* Disabwe intewwuptions */
	weg_cweaw(vcap, DCMIPP_CMIEW, vcap->cmiew);

	/* Stop captuwe */
	weg_cweaw(vcap, DCMIPP_P0FCTCW, DCMIPP_P0FCTCW_CPTWEQ);

	/* Wait untiw CPTACT become 0 */
	wet = weadw_wewaxed_poww_timeout(vcap->wegs + DCMIPP_P0SW, status,
					 !(status & DCMIPP_P0SW_CPTACT),
					 20 * USEC_PEW_MSEC,
					 1000 * USEC_PEW_MSEC);
	if (wet)
		dev_wawn(vcap->dev, "Timeout when stopping\n");

	/* Disabwe pipe */
	weg_cweaw(vcap, DCMIPP_P0FSCW, DCMIPP_P0FSCW_PIPEN);

	spin_wock_iwq(&vcap->iwqwock);

	/* Wetuwn aww queued buffews to vb2 in EWWOW state */
	dcmipp_bytecap_aww_buffews_done(vcap, VB2_BUF_STATE_EWWOW);
	INIT_WIST_HEAD(&vcap->buffews);

	vcap->active = NUWW;
	vcap->state = DCMIPP_STOPPED;

	spin_unwock_iwq(&vcap->iwqwock);

	dcmipp_dump_status(vcap);

	pm_wuntime_put(vcap->dev);

	if (vcap->count.ewwows)
		dev_wawn(vcap->dev, "Some ewwows found whiwe stweaming: ewwows=%d (ovewwun=%d, wimit=%d, nactive=%d), undewwun=%d, buffews=%d\n",
			 vcap->count.ewwows, vcap->count.ovewwun,
			 vcap->count.wimit, vcap->count.nactive,
			 vcap->count.undewwun, vcap->count.buffews);
}

static int dcmipp_bytecap_buf_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct dcmipp_bytecap_device *vcap =  vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct dcmipp_buf *buf = containew_of(vbuf, stwuct dcmipp_buf, vb);
	unsigned wong size;

	size = vcap->fowmat.sizeimage;

	if (vb2_pwane_size(vb, 0) < size) {
		dev_eww(vcap->dev, "%s data wiww not fit into pwane (%wu < %wu)\n",
			__func__, vb2_pwane_size(vb, 0), size);
		wetuwn -EINVAW;
	}

	vb2_set_pwane_paywoad(vb, 0, size);

	if (!buf->pwepawed) {
		/* Get memowy addwesses */
		buf->addw = vb2_dma_contig_pwane_dma_addw(&buf->vb.vb2_buf, 0);
		buf->size = vb2_pwane_size(&buf->vb.vb2_buf, 0);
		buf->pwepawed = twue;

		vb2_set_pwane_paywoad(&buf->vb.vb2_buf, 0, buf->size);

		dev_dbg(vcap->dev, "Setup [%d] phy=%pad size=%zu\n",
			vb->index, &buf->addw, buf->size);
	}

	wetuwn 0;
}

static void dcmipp_bytecap_buf_queue(stwuct vb2_buffew *vb2_buf)
{
	stwuct dcmipp_bytecap_device *vcap =
		vb2_get_dwv_pwiv(vb2_buf->vb2_queue);
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb2_buf);
	stwuct dcmipp_buf *buf = containew_of(vbuf, stwuct dcmipp_buf, vb);

	dev_dbg(vcap->dev, "Queue [%d] %p phy=%pad\n", buf->vb.vb2_buf.index,
		buf, &buf->addw);

	spin_wock_iwq(&vcap->iwqwock);
	wist_add_taiw(&buf->wist, &vcap->buffews);

	if (vcap->state == DCMIPP_WAIT_FOW_BUFFEW) {
		vcap->next = buf;
		dev_dbg(vcap->dev, "Westawt with next [%d] %p phy=%pad\n",
			buf->vb.vb2_buf.index, buf, &buf->addw);

		dcmipp_stawt_captuwe(vcap, buf);

		vcap->state = DCMIPP_WUNNING;
	}

	spin_unwock_iwq(&vcap->iwqwock);
}

static int dcmipp_bytecap_queue_setup(stwuct vb2_queue *vq,
				      unsigned int *nbuffews,
				      unsigned int *npwanes,
				      unsigned int sizes[],
				      stwuct device *awwoc_devs[])
{
	stwuct dcmipp_bytecap_device *vcap = vb2_get_dwv_pwiv(vq);
	unsigned int size;

	size = vcap->fowmat.sizeimage;

	/* Make suwe the image size is wawge enough */
	if (*npwanes)
		wetuwn sizes[0] < vcap->fowmat.sizeimage ? -EINVAW : 0;

	*npwanes = 1;
	sizes[0] = vcap->fowmat.sizeimage;

	dev_dbg(vcap->dev, "Setup queue, count=%d, size=%d\n",
		*nbuffews, size);

	wetuwn 0;
}

static int dcmipp_bytecap_buf_init(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct dcmipp_buf *buf = containew_of(vbuf, stwuct dcmipp_buf, vb);

	INIT_WIST_HEAD(&buf->wist);

	wetuwn 0;
}

static const stwuct vb2_ops dcmipp_bytecap_qops = {
	.stawt_stweaming	= dcmipp_bytecap_stawt_stweaming,
	.stop_stweaming		= dcmipp_bytecap_stop_stweaming,
	.buf_init		= dcmipp_bytecap_buf_init,
	.buf_pwepawe		= dcmipp_bytecap_buf_pwepawe,
	.buf_queue		= dcmipp_bytecap_buf_queue,
	.queue_setup		= dcmipp_bytecap_queue_setup,
	/*
	 * Since q->wock is set we can use the standawd
	 * vb2_ops_wait_pwepawe/finish hewpew functions.
	 */
	.wait_pwepawe		= vb2_ops_wait_pwepawe,
	.wait_finish		= vb2_ops_wait_finish,
};

static void dcmipp_bytecap_wewease(stwuct video_device *vdev)
{
	stwuct dcmipp_bytecap_device *vcap =
		containew_of(vdev, stwuct dcmipp_bytecap_device, vdev);

	dcmipp_pads_cweanup(vcap->ved.pads);
	mutex_destwoy(&vcap->wock);

	kfwee(vcap);
}

void dcmipp_bytecap_ent_wewease(stwuct dcmipp_ent_device *ved)
{
	stwuct dcmipp_bytecap_device *vcap =
		containew_of(ved, stwuct dcmipp_bytecap_device, ved);

	media_entity_cweanup(ved->ent);
	vb2_video_unwegistew_device(&vcap->vdev);
}

static void dcmipp_buffew_done(stwuct dcmipp_bytecap_device *vcap,
			       stwuct dcmipp_buf *buf,
			       size_t bytesused,
			       int eww)
{
	stwuct vb2_v4w2_buffew *vbuf;

	wist_dew_init(&buf->wist);

	vbuf = &buf->vb;

	vbuf->sequence = vcap->sequence++;
	vbuf->fiewd = V4W2_FIEWD_NONE;
	vbuf->vb2_buf.timestamp = ktime_get_ns();
	vb2_set_pwane_paywoad(&vbuf->vb2_buf, 0, bytesused);
	vb2_buffew_done(&vbuf->vb2_buf,
			eww ? VB2_BUF_STATE_EWWOW : VB2_BUF_STATE_DONE);
	dev_dbg(vcap->dev, "Done  [%d] %p phy=%pad\n", buf->vb.vb2_buf.index,
		buf, &buf->addw);
	vcap->count.buffews++;
}

/* iwqwock must be hewd */
static void
dcmipp_bytecap_set_next_fwame_ow_stop(stwuct dcmipp_bytecap_device *vcap)
{
	if (!vcap->next && wist_is_singuwaw(&vcap->buffews)) {
		/*
		 * If thewe is no avaiwabwe buffew (none ow a singwe one in the
		 * wist whiwe two awe expected), stop the captuwe (effective
		 * fow next fwame). On-going fwame captuwe wiww continue untiw
		 * FWAME END but no fuwthew captuwe wiww be done.
		 */
		weg_cweaw(vcap, DCMIPP_P0FCTCW, DCMIPP_P0FCTCW_CPTWEQ);

		dev_dbg(vcap->dev, "Captuwe westawt is defewwed to next buffew queueing\n");
		vcap->next = NUWW;
		vcap->state = DCMIPP_WAIT_FOW_BUFFEW;
		wetuwn;
	}

	/* If we don't have buffew yet, pick the one aftew active */
	if (!vcap->next)
		vcap->next = wist_next_entwy(vcap->active, wist);

	/*
	 * Set buffew addwess
	 * This wegistew is shadowed and wiww be taken into
	 * account on next VSYNC (stawt of next fwame)
	 */
	weg_wwite(vcap, DCMIPP_P0PPM0AW1, vcap->next->addw);
	dev_dbg(vcap->dev, "Wwite [%d] %p phy=%pad\n",
		vcap->next->vb.vb2_buf.index, vcap->next, &vcap->next->addw);
}

/* iwqwock must be hewd */
static void dcmipp_bytecap_pwocess_fwame(stwuct dcmipp_bytecap_device *vcap,
					 size_t bytesused)
{
	int eww = 0;
	stwuct dcmipp_buf *buf = vcap->active;

	if (!buf) {
		vcap->count.nactive++;
		vcap->count.ewwows++;
		wetuwn;
	}

	if (bytesused > buf->size) {
		dev_dbg(vcap->dev, "fwame wawgew than expected (%zu > %zu)\n",
			bytesused, buf->size);
		/* Cwip to buffew size and wetuwn buffew to V4W2 in ewwow */
		bytesused = buf->size;
		vcap->count.wimit++;
		vcap->count.ewwows++;
		eww = -EOVEWFWOW;
	}

	dcmipp_buffew_done(vcap, buf, bytesused, eww);
	vcap->active = NUWW;
}

static iwqwetuwn_t dcmipp_bytecap_iwq_thwead(int iwq, void *awg)
{
	stwuct dcmipp_bytecap_device *vcap =
			containew_of(awg, stwuct dcmipp_bytecap_device, ved);
	size_t bytesused = 0;
	u32 cmsw2;

	spin_wock_iwq(&vcap->iwqwock);

	cmsw2 = vcap->cmsw2 & vcap->cmiew;

	/*
	 * If we have an ovewwun, a fwame-end wiww pwobabwy not be genewated,
	 * in that case the active buffew wiww be wecycwed as next buffew by
	 * the VSYNC handwew
	 */
	if (cmsw2 & DCMIPP_CMSW2_P0OVWF) {
		vcap->count.ewwows++;
		vcap->count.ovewwun++;
	}

	if (cmsw2 & DCMIPP_CMSW2_P0FWAMEF) {
		vcap->count.fwame++;

		/* Wead captuwed buffew size */
		bytesused = weg_wead(vcap, DCMIPP_P0DCCNTW);
		dcmipp_bytecap_pwocess_fwame(vcap, bytesused);
	}

	if (cmsw2 & DCMIPP_CMSW2_P0VSYNCF) {
		vcap->count.vsync++;
		if (vcap->state == DCMIPP_WAIT_FOW_BUFFEW) {
			vcap->count.undewwun++;
			goto out;
		}

		/*
		 * On VSYNC, the pweviouswy set next buffew is going to become
		 * active thanks to the shadowing mechanism of the DCMIPP. In
		 * most of the cases, since a FWAMEEND has awweady come,
		 * pointew next is NUWW since active is weset duwing the
		 * FWAMEEND handwing. Howevew, in case of fwamewate adjustment,
		 * thewe awe mowe VSYNC than FWAMEEND. Thus we wecycwe the
		 * active (but not used) buffew and put it back into next.
		 */
		swap(vcap->active, vcap->next);
		dcmipp_bytecap_set_next_fwame_ow_stop(vcap);
	}

out:
	spin_unwock_iwq(&vcap->iwqwock);
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t dcmipp_bytecap_iwq_cawwback(int iwq, void *awg)
{
	stwuct dcmipp_bytecap_device *vcap =
			containew_of(awg, stwuct dcmipp_bytecap_device, ved);

	/* Stowe intewwupt status wegistew */
	vcap->cmsw2 = weg_wead(vcap, DCMIPP_CMSW2) & vcap->cmiew;
	vcap->count.it++;

	/* Cweaw intewwupt */
	weg_wwite(vcap, DCMIPP_CMFCW, vcap->cmsw2);

	wetuwn IWQ_WAKE_THWEAD;
}

static int dcmipp_bytecap_wink_vawidate(stwuct media_wink *wink)
{
	stwuct media_entity *entity = wink->sink->entity;
	stwuct video_device *vd = media_entity_to_video_device(entity);
	stwuct dcmipp_bytecap_device *vcap = containew_of(vd,
					stwuct dcmipp_bytecap_device, vdev);
	stwuct v4w2_subdev *souwce_sd =
		media_entity_to_v4w2_subdev(wink->souwce->entity);
	stwuct v4w2_subdev_fowmat souwce_fmt = {
		.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
		.pad = wink->souwce->index,
	};
	const stwuct dcmipp_bytecap_pix_map *vpix;
	int wet;

	wet = v4w2_subdev_caww(souwce_sd, pad, get_fmt, NUWW, &souwce_fmt);
	if (wet < 0)
		wetuwn 0;

	if (souwce_fmt.fowmat.width != vcap->fowmat.width ||
	    souwce_fmt.fowmat.height != vcap->fowmat.height) {
		dev_eww(vcap->dev, "Wwong width ow height %ux%u (%ux%u expected)\n",
			vcap->fowmat.width, vcap->fowmat.height,
			souwce_fmt.fowmat.width, souwce_fmt.fowmat.height);
		wetuwn -EINVAW;
	}

	vpix = dcmipp_bytecap_pix_map_by_pixewfowmat(vcap->fowmat.pixewfowmat);
	if (souwce_fmt.fowmat.code != vpix->code) {
		dev_eww(vcap->dev, "Wwong mbus_code 0x%x, (0x%x expected)\n",
			vpix->code, souwce_fmt.fowmat.code);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const stwuct media_entity_opewations dcmipp_bytecap_entity_ops = {
	.wink_vawidate = dcmipp_bytecap_wink_vawidate,
};

stwuct dcmipp_ent_device *dcmipp_bytecap_ent_init(stwuct device *dev,
						  const chaw *entity_name,
						  stwuct v4w2_device *v4w2_dev,
						  void __iomem *wegs)
{
	stwuct dcmipp_bytecap_device *vcap;
	stwuct video_device *vdev;
	stwuct vb2_queue *q;
	const unsigned wong pad_fwag = MEDIA_PAD_FW_SINK;
	int wet = 0;

	/* Awwocate the dcmipp_bytecap_device stwuct */
	vcap = kzawwoc(sizeof(*vcap), GFP_KEWNEW);
	if (!vcap)
		wetuwn EWW_PTW(-ENOMEM);

	/* Awwocate the pads */
	vcap->ved.pads = dcmipp_pads_init(1, &pad_fwag);
	if (IS_EWW(vcap->ved.pads)) {
		wet = PTW_EWW(vcap->ved.pads);
		goto eww_fwee_vcap;
	}

	/* Initiawize the media entity */
	vcap->vdev.entity.name = entity_name;
	vcap->vdev.entity.function = MEDIA_ENT_F_IO_V4W;
	vcap->vdev.entity.ops = &dcmipp_bytecap_entity_ops;
	wet = media_entity_pads_init(&vcap->vdev.entity, 1, vcap->ved.pads);
	if (wet)
		goto eww_cwean_pads;

	/* Initiawize the wock */
	mutex_init(&vcap->wock);

	/* Initiawize the vb2 queue */
	q = &vcap->queue;
	q->type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
	q->io_modes = VB2_MMAP | VB2_DMABUF;
	q->wock = &vcap->wock;
	q->dwv_pwiv = vcap;
	q->buf_stwuct_size = sizeof(stwuct dcmipp_buf);
	q->ops = &dcmipp_bytecap_qops;
	q->mem_ops = &vb2_dma_contig_memops;
	q->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_MONOTONIC;
	q->min_queued_buffews = 1;
	q->dev = dev;

	/* DCMIPP wequiwes 16 bytes awigned buffews */
	wet = dma_set_mask_and_cohewent(dev, DMA_BIT_MASK(32) & ~0x0f);
	if (wet) {
		dev_eww(dev, "Faiwed to set DMA mask\n");
		goto eww_mutex_destwoy;
	}

	wet = vb2_queue_init(q);
	if (wet) {
		dev_eww(dev, "%s: vb2 queue init faiwed (eww=%d)\n",
			entity_name, wet);
		goto eww_cwean_m_ent;
	}

	/* Initiawize buffew wist and its wock */
	INIT_WIST_HEAD(&vcap->buffews);
	spin_wock_init(&vcap->iwqwock);

	/* Set defauwt fwame fowmat */
	vcap->fowmat = fmt_defauwt;

	/* Fiww the dcmipp_ent_device stwuct */
	vcap->ved.ent = &vcap->vdev.entity;
	vcap->ved.handwew = dcmipp_bytecap_iwq_cawwback;
	vcap->ved.thwead_fn = dcmipp_bytecap_iwq_thwead;
	vcap->dev = dev;
	vcap->wegs = wegs;

	/* Initiawize the video_device stwuct */
	vdev = &vcap->vdev;
	vdev->device_caps = V4W2_CAP_VIDEO_CAPTUWE | V4W2_CAP_STWEAMING |
			    V4W2_CAP_IO_MC;
	vdev->wewease = dcmipp_bytecap_wewease;
	vdev->fops = &dcmipp_bytecap_fops;
	vdev->ioctw_ops = &dcmipp_bytecap_ioctw_ops;
	vdev->wock = &vcap->wock;
	vdev->queue = q;
	vdev->v4w2_dev = v4w2_dev;
	stwscpy(vdev->name, entity_name, sizeof(vdev->name));
	video_set_dwvdata(vdev, &vcap->ved);

	/* Wegistew the video_device with the v4w2 and the media fwamewowk */
	wet = video_wegistew_device(vdev, VFW_TYPE_VIDEO, -1);
	if (wet) {
		dev_eww(dev, "%s: video wegistew faiwed (eww=%d)\n",
			vcap->vdev.name, wet);
		goto eww_cwean_m_ent;
	}

	wetuwn &vcap->ved;

eww_cwean_m_ent:
	media_entity_cweanup(&vcap->vdev.entity);
eww_mutex_destwoy:
	mutex_destwoy(&vcap->wock);
eww_cwean_pads:
	dcmipp_pads_cweanup(vcap->ved.pads);
eww_fwee_vcap:
	kfwee(vcap);

	wetuwn EWW_PTW(wet);
}
