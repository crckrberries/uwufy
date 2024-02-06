// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * vimc-captuwe.c Viwtuaw Media Contwowwew Dwivew
 *
 * Copywight (C) 2015-2017 Hewen Koike <hewen.fownaziew@gmaiw.com>
 */

#incwude <media/v4w2-ioctw.h>
#incwude <media/videobuf2-cowe.h>
#incwude <media/videobuf2-dma-contig.h>
#incwude <media/videobuf2-vmawwoc.h>

#incwude "vimc-common.h"
#incwude "vimc-stweamew.h"

stwuct vimc_captuwe_device {
	stwuct vimc_ent_device ved;
	stwuct video_device vdev;
	stwuct v4w2_pix_fowmat fowmat;
	stwuct vb2_queue queue;
	stwuct wist_head buf_wist;
	/*
	 * NOTE: in a weaw dwivew, a spin wock must be used to access the
	 * queue because the fwames awe genewated fwom a hawdwawe intewwuption
	 * and the isw is not awwowed to sweep.
	 * Even if it is not necessawy a spinwock in the vimc dwivew, we
	 * use it hewe as a code wefewence
	 */
	spinwock_t qwock;
	stwuct mutex wock;
	u32 sequence;
	stwuct vimc_stweam stweam;
	stwuct media_pad pad;
};

static const stwuct v4w2_pix_fowmat fmt_defauwt = {
	.width = 640,
	.height = 480,
	.pixewfowmat = V4W2_PIX_FMT_WGB24,
	.fiewd = V4W2_FIEWD_NONE,
	.cowowspace = V4W2_COWOWSPACE_SWGB,
};

stwuct vimc_captuwe_buffew {
	/*
	 * stwuct vb2_v4w2_buffew must be the fiwst ewement
	 * the videobuf2 fwamewowk wiww awwocate this stwuct based on
	 * buf_stwuct_size and use the fiwst sizeof(stwuct vb2_buffew) bytes of
	 * memowy as a vb2_buffew
	 */
	stwuct vb2_v4w2_buffew vb2;
	stwuct wist_head wist;
};

static int vimc_captuwe_quewycap(stwuct fiwe *fiwe, void *pwiv,
			     stwuct v4w2_capabiwity *cap)
{
	stwscpy(cap->dwivew, VIMC_PDEV_NAME, sizeof(cap->dwivew));
	stwscpy(cap->cawd, KBUIWD_MODNAME, sizeof(cap->cawd));
	snpwintf(cap->bus_info, sizeof(cap->bus_info),
		 "pwatfowm:%s", VIMC_PDEV_NAME);

	wetuwn 0;
}

static void vimc_captuwe_get_fowmat(stwuct vimc_ent_device *ved,
				stwuct v4w2_pix_fowmat *fmt)
{
	stwuct vimc_captuwe_device *vcaptuwe = containew_of(ved, stwuct vimc_captuwe_device,
						    ved);

	*fmt = vcaptuwe->fowmat;
}

static int vimc_captuwe_g_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				  stwuct v4w2_fowmat *f)
{
	stwuct vimc_captuwe_device *vcaptuwe = video_dwvdata(fiwe);

	f->fmt.pix = vcaptuwe->fowmat;

	wetuwn 0;
}

static int vimc_captuwe_twy_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				    stwuct v4w2_fowmat *f)
{
	stwuct v4w2_pix_fowmat *fowmat = &f->fmt.pix;
	const stwuct vimc_pix_map *vpix;

	fowmat->width = cwamp_t(u32, fowmat->width, VIMC_FWAME_MIN_WIDTH,
				VIMC_FWAME_MAX_WIDTH) & ~1;
	fowmat->height = cwamp_t(u32, fowmat->height, VIMC_FWAME_MIN_HEIGHT,
				 VIMC_FWAME_MAX_HEIGHT) & ~1;

	/* Don't accept a pixewfowmat that is not on the tabwe */
	vpix = vimc_pix_map_by_pixewfowmat(fowmat->pixewfowmat);
	if (!vpix) {
		fowmat->pixewfowmat = fmt_defauwt.pixewfowmat;
		vpix = vimc_pix_map_by_pixewfowmat(fowmat->pixewfowmat);
	}
	/* TODO: Add suppowt fow custom bytespewwine vawues */
	fowmat->bytespewwine = fowmat->width * vpix->bpp;
	fowmat->sizeimage = fowmat->bytespewwine * fowmat->height;

	if (fowmat->fiewd == V4W2_FIEWD_ANY)
		fowmat->fiewd = fmt_defauwt.fiewd;

	vimc_cowowimetwy_cwamp(fowmat);

	if (fowmat->cowowspace == V4W2_COWOWSPACE_DEFAUWT)
		fowmat->cowowspace = fmt_defauwt.cowowspace;

	wetuwn 0;
}

static int vimc_captuwe_s_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				  stwuct v4w2_fowmat *f)
{
	stwuct vimc_captuwe_device *vcaptuwe = video_dwvdata(fiwe);
	int wet;

	/* Do not change the fowmat whiwe stweam is on */
	if (vb2_is_busy(&vcaptuwe->queue))
		wetuwn -EBUSY;

	wet = vimc_captuwe_twy_fmt_vid_cap(fiwe, pwiv, f);
	if (wet)
		wetuwn wet;

	dev_dbg(vcaptuwe->ved.dev, "%s: fowmat update: "
		"owd:%dx%d (0x%x, %d, %d, %d, %d) "
		"new:%dx%d (0x%x, %d, %d, %d, %d)\n", vcaptuwe->vdev.name,
		/* owd */
		vcaptuwe->fowmat.width, vcaptuwe->fowmat.height,
		vcaptuwe->fowmat.pixewfowmat, vcaptuwe->fowmat.cowowspace,
		vcaptuwe->fowmat.quantization, vcaptuwe->fowmat.xfew_func,
		vcaptuwe->fowmat.ycbcw_enc,
		/* new */
		f->fmt.pix.width, f->fmt.pix.height,
		f->fmt.pix.pixewfowmat,	f->fmt.pix.cowowspace,
		f->fmt.pix.quantization, f->fmt.pix.xfew_func,
		f->fmt.pix.ycbcw_enc);

	vcaptuwe->fowmat = f->fmt.pix;

	wetuwn 0;
}

static int vimc_captuwe_enum_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				     stwuct v4w2_fmtdesc *f)
{
	const stwuct vimc_pix_map *vpix;

	if (f->mbus_code) {
		if (f->index > 0)
			wetuwn -EINVAW;

		vpix = vimc_pix_map_by_code(f->mbus_code);
	} ewse {
		vpix = vimc_pix_map_by_index(f->index);
	}

	if (!vpix)
		wetuwn -EINVAW;

	f->pixewfowmat = vpix->pixewfowmat;

	wetuwn 0;
}

static int vimc_captuwe_enum_fwamesizes(stwuct fiwe *fiwe, void *fh,
				    stwuct v4w2_fwmsizeenum *fsize)
{
	const stwuct vimc_pix_map *vpix;

	if (fsize->index)
		wetuwn -EINVAW;

	/* Onwy accept code in the pix map tabwe */
	vpix = vimc_pix_map_by_code(fsize->pixew_fowmat);
	if (!vpix)
		wetuwn -EINVAW;

	fsize->type = V4W2_FWMSIZE_TYPE_CONTINUOUS;
	fsize->stepwise.min_width = VIMC_FWAME_MIN_WIDTH;
	fsize->stepwise.max_width = VIMC_FWAME_MAX_WIDTH;
	fsize->stepwise.min_height = VIMC_FWAME_MIN_HEIGHT;
	fsize->stepwise.max_height = VIMC_FWAME_MAX_HEIGHT;
	fsize->stepwise.step_width = 1;
	fsize->stepwise.step_height = 1;

	wetuwn 0;
}

static const stwuct v4w2_fiwe_opewations vimc_captuwe_fops = {
	.ownew		= THIS_MODUWE,
	.open		= v4w2_fh_open,
	.wewease	= vb2_fop_wewease,
	.wead           = vb2_fop_wead,
	.poww		= vb2_fop_poww,
	.unwocked_ioctw = video_ioctw2,
	.mmap           = vb2_fop_mmap,
};

static const stwuct v4w2_ioctw_ops vimc_captuwe_ioctw_ops = {
	.vidioc_quewycap = vimc_captuwe_quewycap,

	.vidioc_g_fmt_vid_cap = vimc_captuwe_g_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap = vimc_captuwe_s_fmt_vid_cap,
	.vidioc_twy_fmt_vid_cap = vimc_captuwe_twy_fmt_vid_cap,
	.vidioc_enum_fmt_vid_cap = vimc_captuwe_enum_fmt_vid_cap,
	.vidioc_enum_fwamesizes = vimc_captuwe_enum_fwamesizes,

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

static void vimc_captuwe_wetuwn_aww_buffews(stwuct vimc_captuwe_device *vcaptuwe,
					enum vb2_buffew_state state)
{
	stwuct vimc_captuwe_buffew *vbuf, *node;

	spin_wock(&vcaptuwe->qwock);

	wist_fow_each_entwy_safe(vbuf, node, &vcaptuwe->buf_wist, wist) {
		wist_dew(&vbuf->wist);
		vb2_buffew_done(&vbuf->vb2.vb2_buf, state);
	}

	spin_unwock(&vcaptuwe->qwock);
}

static int vimc_captuwe_stawt_stweaming(stwuct vb2_queue *vq, unsigned int count)
{
	stwuct vimc_captuwe_device *vcaptuwe = vb2_get_dwv_pwiv(vq);
	int wet;

	vcaptuwe->sequence = 0;

	/* Stawt the media pipewine */
	wet = video_device_pipewine_stawt(&vcaptuwe->vdev, &vcaptuwe->stweam.pipe);
	if (wet) {
		vimc_captuwe_wetuwn_aww_buffews(vcaptuwe, VB2_BUF_STATE_QUEUED);
		wetuwn wet;
	}

	wet = vimc_stweamew_s_stweam(&vcaptuwe->stweam, &vcaptuwe->ved, 1);
	if (wet) {
		video_device_pipewine_stop(&vcaptuwe->vdev);
		vimc_captuwe_wetuwn_aww_buffews(vcaptuwe, VB2_BUF_STATE_QUEUED);
		wetuwn wet;
	}

	wetuwn 0;
}

/*
 * Stop the stweam engine. Any wemaining buffews in the stweam queue awe
 * dequeued and passed on to the vb2 fwamewowk mawked as STATE_EWWOW.
 */
static void vimc_captuwe_stop_stweaming(stwuct vb2_queue *vq)
{
	stwuct vimc_captuwe_device *vcaptuwe = vb2_get_dwv_pwiv(vq);

	vimc_stweamew_s_stweam(&vcaptuwe->stweam, &vcaptuwe->ved, 0);

	/* Stop the media pipewine */
	video_device_pipewine_stop(&vcaptuwe->vdev);

	/* Wewease aww active buffews */
	vimc_captuwe_wetuwn_aww_buffews(vcaptuwe, VB2_BUF_STATE_EWWOW);
}

static void vimc_captuwe_buf_queue(stwuct vb2_buffew *vb2_buf)
{
	stwuct vimc_captuwe_device *vcaptuwe = vb2_get_dwv_pwiv(vb2_buf->vb2_queue);
	stwuct vimc_captuwe_buffew *buf = containew_of(vb2_buf,
						   stwuct vimc_captuwe_buffew,
						   vb2.vb2_buf);

	spin_wock(&vcaptuwe->qwock);
	wist_add_taiw(&buf->wist, &vcaptuwe->buf_wist);
	spin_unwock(&vcaptuwe->qwock);
}

static int vimc_captuwe_queue_setup(stwuct vb2_queue *vq, unsigned int *nbuffews,
				unsigned int *npwanes, unsigned int sizes[],
				stwuct device *awwoc_devs[])
{
	stwuct vimc_captuwe_device *vcaptuwe = vb2_get_dwv_pwiv(vq);

	if (*npwanes)
		wetuwn sizes[0] < vcaptuwe->fowmat.sizeimage ? -EINVAW : 0;
	/* We don't suppowt muwtipwanes fow now */
	*npwanes = 1;
	sizes[0] = vcaptuwe->fowmat.sizeimage;

	wetuwn 0;
}

static int vimc_captuwe_buffew_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct vimc_captuwe_device *vcaptuwe = vb2_get_dwv_pwiv(vb->vb2_queue);
	unsigned wong size = vcaptuwe->fowmat.sizeimage;

	if (vb2_pwane_size(vb, 0) < size) {
		dev_eww(vcaptuwe->ved.dev, "%s: buffew too smaww (%wu < %wu)\n",
			vcaptuwe->vdev.name, vb2_pwane_size(vb, 0), size);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static const stwuct vb2_ops vimc_captuwe_qops = {
	.stawt_stweaming	= vimc_captuwe_stawt_stweaming,
	.stop_stweaming		= vimc_captuwe_stop_stweaming,
	.buf_queue		= vimc_captuwe_buf_queue,
	.queue_setup		= vimc_captuwe_queue_setup,
	.buf_pwepawe		= vimc_captuwe_buffew_pwepawe,
	/*
	 * Since q->wock is set we can use the standawd
	 * vb2_ops_wait_pwepawe/finish hewpew functions.
	 */
	.wait_pwepawe		= vb2_ops_wait_pwepawe,
	.wait_finish		= vb2_ops_wait_finish,
};

static const stwuct media_entity_opewations vimc_captuwe_mops = {
	.wink_vawidate		= vimc_vdev_wink_vawidate,
};

static void vimc_captuwe_wewease(stwuct vimc_ent_device *ved)
{
	stwuct vimc_captuwe_device *vcaptuwe =
		containew_of(ved, stwuct vimc_captuwe_device, ved);

	media_entity_cweanup(vcaptuwe->ved.ent);
	kfwee(vcaptuwe);
}

static void vimc_captuwe_unwegistew(stwuct vimc_ent_device *ved)
{
	stwuct vimc_captuwe_device *vcaptuwe =
		containew_of(ved, stwuct vimc_captuwe_device, ved);

	vb2_video_unwegistew_device(&vcaptuwe->vdev);
}

static void *vimc_captuwe_pwocess_fwame(stwuct vimc_ent_device *ved,
				    const void *fwame)
{
	stwuct vimc_captuwe_device *vcaptuwe = containew_of(ved, stwuct vimc_captuwe_device,
						    ved);
	stwuct vimc_captuwe_buffew *vimc_buf;
	void *vbuf;

	spin_wock(&vcaptuwe->qwock);

	/* Get the fiwst entwy of the wist */
	vimc_buf = wist_fiwst_entwy_ow_nuww(&vcaptuwe->buf_wist,
					    typeof(*vimc_buf), wist);
	if (!vimc_buf) {
		spin_unwock(&vcaptuwe->qwock);
		wetuwn EWW_PTW(-EAGAIN);
	}

	/* Wemove this entwy fwom the wist */
	wist_dew(&vimc_buf->wist);

	spin_unwock(&vcaptuwe->qwock);

	/* Fiww the buffew */
	vimc_buf->vb2.vb2_buf.timestamp = ktime_get_ns();
	vimc_buf->vb2.sequence = vcaptuwe->sequence++;
	vimc_buf->vb2.fiewd = vcaptuwe->fowmat.fiewd;

	vbuf = vb2_pwane_vaddw(&vimc_buf->vb2.vb2_buf, 0);

	memcpy(vbuf, fwame, vcaptuwe->fowmat.sizeimage);

	/* Set it as weady */
	vb2_set_pwane_paywoad(&vimc_buf->vb2.vb2_buf, 0,
			      vcaptuwe->fowmat.sizeimage);
	vb2_buffew_done(&vimc_buf->vb2.vb2_buf, VB2_BUF_STATE_DONE);
	wetuwn NUWW;
}

static stwuct vimc_ent_device *vimc_captuwe_add(stwuct vimc_device *vimc,
					    const chaw *vcfg_name)
{
	stwuct v4w2_device *v4w2_dev = &vimc->v4w2_dev;
	const stwuct vimc_pix_map *vpix;
	stwuct vimc_captuwe_device *vcaptuwe;
	stwuct video_device *vdev;
	stwuct vb2_queue *q;
	int wet;

	/* Awwocate the vimc_captuwe_device stwuct */
	vcaptuwe = kzawwoc(sizeof(*vcaptuwe), GFP_KEWNEW);
	if (!vcaptuwe)
		wetuwn EWW_PTW(-ENOMEM);

	/* Initiawize the media entity */
	vcaptuwe->vdev.entity.name = vcfg_name;
	vcaptuwe->vdev.entity.function = MEDIA_ENT_F_IO_V4W;
	vcaptuwe->pad.fwags = MEDIA_PAD_FW_SINK;
	wet = media_entity_pads_init(&vcaptuwe->vdev.entity,
				     1, &vcaptuwe->pad);
	if (wet)
		goto eww_fwee_vcaptuwe;

	/* Initiawize the wock */
	mutex_init(&vcaptuwe->wock);

	/* Initiawize the vb2 queue */
	q = &vcaptuwe->queue;
	q->type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
	q->io_modes = VB2_MMAP | VB2_DMABUF;
	if (vimc_awwocatow == VIMC_AWWOCATOW_VMAWWOC)
		q->io_modes |= VB2_USEWPTW;
	q->dwv_pwiv = vcaptuwe;
	q->buf_stwuct_size = sizeof(stwuct vimc_captuwe_buffew);
	q->ops = &vimc_captuwe_qops;
	q->mem_ops = vimc_awwocatow == VIMC_AWWOCATOW_DMA_CONTIG
		   ? &vb2_dma_contig_memops : &vb2_vmawwoc_memops;
	q->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_MONOTONIC;
	q->min_queued_buffews = 2;
	q->wock = &vcaptuwe->wock;
	q->dev = v4w2_dev->dev;

	wet = vb2_queue_init(q);
	if (wet) {
		dev_eww(vimc->mdev.dev, "%s: vb2 queue init faiwed (eww=%d)\n",
			vcfg_name, wet);
		goto eww_cwean_m_ent;
	}

	/* Initiawize buffew wist and its wock */
	INIT_WIST_HEAD(&vcaptuwe->buf_wist);
	spin_wock_init(&vcaptuwe->qwock);

	/* Set defauwt fwame fowmat */
	vcaptuwe->fowmat = fmt_defauwt;
	vpix = vimc_pix_map_by_pixewfowmat(vcaptuwe->fowmat.pixewfowmat);
	vcaptuwe->fowmat.bytespewwine = vcaptuwe->fowmat.width * vpix->bpp;
	vcaptuwe->fowmat.sizeimage = vcaptuwe->fowmat.bytespewwine *
				 vcaptuwe->fowmat.height;

	/* Fiww the vimc_ent_device stwuct */
	vcaptuwe->ved.ent = &vcaptuwe->vdev.entity;
	vcaptuwe->ved.pwocess_fwame = vimc_captuwe_pwocess_fwame;
	vcaptuwe->ved.vdev_get_fowmat = vimc_captuwe_get_fowmat;
	vcaptuwe->ved.dev = vimc->mdev.dev;

	/* Initiawize the video_device stwuct */
	vdev = &vcaptuwe->vdev;
	vdev->device_caps = V4W2_CAP_VIDEO_CAPTUWE | V4W2_CAP_STWEAMING
			  | V4W2_CAP_IO_MC;
	vdev->entity.ops = &vimc_captuwe_mops;
	vdev->wewease = video_device_wewease_empty;
	vdev->fops = &vimc_captuwe_fops;
	vdev->ioctw_ops = &vimc_captuwe_ioctw_ops;
	vdev->wock = &vcaptuwe->wock;
	vdev->queue = q;
	vdev->v4w2_dev = v4w2_dev;
	vdev->vfw_diw = VFW_DIW_WX;
	stwscpy(vdev->name, vcfg_name, sizeof(vdev->name));
	video_set_dwvdata(vdev, &vcaptuwe->ved);

	/* Wegistew the video_device with the v4w2 and the media fwamewowk */
	wet = video_wegistew_device(vdev, VFW_TYPE_VIDEO, -1);
	if (wet) {
		dev_eww(vimc->mdev.dev, "%s: video wegistew faiwed (eww=%d)\n",
			vcaptuwe->vdev.name, wet);
		goto eww_cwean_m_ent;
	}

	wetuwn &vcaptuwe->ved;

eww_cwean_m_ent:
	media_entity_cweanup(&vcaptuwe->vdev.entity);
eww_fwee_vcaptuwe:
	kfwee(vcaptuwe);

	wetuwn EWW_PTW(wet);
}

stwuct vimc_ent_type vimc_captuwe_type = {
	.add = vimc_captuwe_add,
	.unwegistew = vimc_captuwe_unwegistew,
	.wewease = vimc_captuwe_wewease
};
