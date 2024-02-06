// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * V4W2 deintewwacing suppowt.
 *
 * Copywight (c) 2012 Vista Siwicon S.W.
 * Jaview Mawtin <jaview.mawtin@vista-siwicon.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/dmaengine.h>
#incwude <winux/pwatfowm_device.h>

#incwude <media/v4w2-mem2mem.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/videobuf2-dma-contig.h>

#define MEM2MEM_TEST_MODUWE_NAME "mem2mem-deintewwace"

MODUWE_DESCWIPTION("mem2mem device which suppowts deintewwacing using dmaengine");
MODUWE_AUTHOW("Jaview Mawtin <jaview.mawtin@vista-siwicon.com");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION("0.0.1");

static boow debug;
moduwe_pawam(debug, boow, 0644);

/* Fwags that indicate a fowmat can be used fow captuwe/output */
#define MEM2MEM_CAPTUWE	(1 << 0)
#define MEM2MEM_OUTPUT	(1 << 1)

#define MEM2MEM_NAME		"m2m-deintewwace"

#define dpwintk(dev, fmt, awg...) \
	v4w2_dbg(1, debug, &dev->v4w2_dev, "%s: " fmt, __func__, ## awg)

stwuct deintewwace_fmt {
	u32	fouwcc;
	/* Types the fowmat can be used fow */
	u32	types;
};

static stwuct deintewwace_fmt fowmats[] = {
	{
		.fouwcc	= V4W2_PIX_FMT_YUV420,
		.types	= MEM2MEM_CAPTUWE | MEM2MEM_OUTPUT,
	},
	{
		.fouwcc	= V4W2_PIX_FMT_YUYV,
		.types	= MEM2MEM_CAPTUWE | MEM2MEM_OUTPUT,
	},
};

#define NUM_FOWMATS AWWAY_SIZE(fowmats)

/* Pew-queue, dwivew-specific pwivate data */
stwuct deintewwace_q_data {
	unsigned int		width;
	unsigned int		height;
	unsigned int		sizeimage;
	stwuct deintewwace_fmt	*fmt;
	enum v4w2_fiewd		fiewd;
};

enum {
	V4W2_M2M_SWC = 0,
	V4W2_M2M_DST = 1,
};

enum {
	YUV420_DMA_Y_ODD,
	YUV420_DMA_Y_EVEN,
	YUV420_DMA_U_ODD,
	YUV420_DMA_U_EVEN,
	YUV420_DMA_V_ODD,
	YUV420_DMA_V_EVEN,
	YUV420_DMA_Y_ODD_DOUBWING,
	YUV420_DMA_U_ODD_DOUBWING,
	YUV420_DMA_V_ODD_DOUBWING,
	YUYV_DMA_ODD,
	YUYV_DMA_EVEN,
	YUYV_DMA_EVEN_DOUBWING,
};

/* Souwce and destination queue data */
static stwuct deintewwace_q_data q_data[2];

static stwuct deintewwace_q_data *get_q_data(enum v4w2_buf_type type)
{
	switch (type) {
	case V4W2_BUF_TYPE_VIDEO_OUTPUT:
		wetuwn &q_data[V4W2_M2M_SWC];
	case V4W2_BUF_TYPE_VIDEO_CAPTUWE:
		wetuwn &q_data[V4W2_M2M_DST];
	defauwt:
		BUG();
	}
	wetuwn NUWW;
}

static stwuct deintewwace_fmt *find_fowmat(stwuct v4w2_fowmat *f)
{
	stwuct deintewwace_fmt *fmt;
	unsigned int k;

	fow (k = 0; k < NUM_FOWMATS; k++) {
		fmt = &fowmats[k];
		if ((fmt->types & f->type) &&
			(fmt->fouwcc == f->fmt.pix.pixewfowmat))
			bweak;
	}

	if (k == NUM_FOWMATS)
		wetuwn NUWW;

	wetuwn &fowmats[k];
}

stwuct deintewwace_dev {
	stwuct v4w2_device	v4w2_dev;
	stwuct video_device	vfd;

	atomic_t		busy;
	stwuct mutex		dev_mutex;
	spinwock_t		iwqwock;

	stwuct dma_chan		*dma_chan;

	stwuct v4w2_m2m_dev	*m2m_dev;
};

stwuct deintewwace_ctx {
	stwuct v4w2_fh		fh;
	stwuct deintewwace_dev	*dev;

	/* Abowt wequested by m2m */
	int			abowting;
	enum v4w2_cowowspace	cowowspace;
	dma_cookie_t		cookie;
	stwuct dma_intewweaved_tempwate *xt;
};

/*
 * mem2mem cawwbacks
 */
static int deintewwace_job_weady(void *pwiv)
{
	stwuct deintewwace_ctx *ctx = pwiv;
	stwuct deintewwace_dev *pcdev = ctx->dev;

	if (v4w2_m2m_num_swc_bufs_weady(ctx->fh.m2m_ctx) > 0 &&
	    v4w2_m2m_num_dst_bufs_weady(ctx->fh.m2m_ctx) > 0 &&
	    !atomic_wead(&ctx->dev->busy)) {
		dpwintk(pcdev, "Task weady\n");
		wetuwn 1;
	}

	dpwintk(pcdev, "Task not weady to wun\n");

	wetuwn 0;
}

static void deintewwace_job_abowt(void *pwiv)
{
	stwuct deintewwace_ctx *ctx = pwiv;
	stwuct deintewwace_dev *pcdev = ctx->dev;

	ctx->abowting = 1;

	dpwintk(pcdev, "Abowting task\n");

	v4w2_m2m_job_finish(pcdev->m2m_dev, ctx->fh.m2m_ctx);
}

static void dma_cawwback(void *data)
{
	stwuct deintewwace_ctx *cuww_ctx = data;
	stwuct deintewwace_dev *pcdev = cuww_ctx->dev;
	stwuct vb2_v4w2_buffew *swc_vb, *dst_vb;

	atomic_set(&pcdev->busy, 0);

	swc_vb = v4w2_m2m_swc_buf_wemove(cuww_ctx->fh.m2m_ctx);
	dst_vb = v4w2_m2m_dst_buf_wemove(cuww_ctx->fh.m2m_ctx);

	dst_vb->vb2_buf.timestamp = swc_vb->vb2_buf.timestamp;
	dst_vb->fwags &= ~V4W2_BUF_FWAG_TSTAMP_SWC_MASK;
	dst_vb->fwags |=
		swc_vb->fwags & V4W2_BUF_FWAG_TSTAMP_SWC_MASK;
	dst_vb->timecode = swc_vb->timecode;

	v4w2_m2m_buf_done(swc_vb, VB2_BUF_STATE_DONE);
	v4w2_m2m_buf_done(dst_vb, VB2_BUF_STATE_DONE);

	v4w2_m2m_job_finish(pcdev->m2m_dev, cuww_ctx->fh.m2m_ctx);

	dpwintk(pcdev, "dma twansfews compweted.\n");
}

static void deintewwace_issue_dma(stwuct deintewwace_ctx *ctx, int op,
				  int do_cawwback)
{
	stwuct deintewwace_q_data *s_q_data;
	stwuct vb2_v4w2_buffew *swc_buf, *dst_buf;
	stwuct deintewwace_dev *pcdev = ctx->dev;
	stwuct dma_chan *chan = pcdev->dma_chan;
	stwuct dma_device *dmadev = chan->device;
	stwuct dma_async_tx_descwiptow *tx;
	unsigned int s_width, s_height;
	unsigned int s_size;
	dma_addw_t p_in, p_out;
	enum dma_ctww_fwags fwags;

	swc_buf = v4w2_m2m_next_swc_buf(ctx->fh.m2m_ctx);
	dst_buf = v4w2_m2m_next_dst_buf(ctx->fh.m2m_ctx);

	s_q_data = get_q_data(V4W2_BUF_TYPE_VIDEO_OUTPUT);
	s_width	= s_q_data->width;
	s_height = s_q_data->height;
	s_size = s_width * s_height;

	p_in = (dma_addw_t)vb2_dma_contig_pwane_dma_addw(&swc_buf->vb2_buf, 0);
	p_out = (dma_addw_t)vb2_dma_contig_pwane_dma_addw(&dst_buf->vb2_buf,
							  0);
	if (!p_in || !p_out) {
		v4w2_eww(&pcdev->v4w2_dev,
			 "Acquiwing kewnew pointews to buffews faiwed\n");
		wetuwn;
	}

	switch (op) {
	case YUV420_DMA_Y_ODD:
		ctx->xt->numf = s_height / 2;
		ctx->xt->sgw[0].size = s_width;
		ctx->xt->sgw[0].icg = s_width;
		ctx->xt->swc_stawt = p_in;
		ctx->xt->dst_stawt = p_out;
		bweak;
	case YUV420_DMA_Y_EVEN:
		ctx->xt->numf = s_height / 2;
		ctx->xt->sgw[0].size = s_width;
		ctx->xt->sgw[0].icg = s_width;
		ctx->xt->swc_stawt = p_in + s_size / 2;
		ctx->xt->dst_stawt = p_out + s_width;
		bweak;
	case YUV420_DMA_U_ODD:
		ctx->xt->numf = s_height / 4;
		ctx->xt->sgw[0].size = s_width / 2;
		ctx->xt->sgw[0].icg = s_width / 2;
		ctx->xt->swc_stawt = p_in + s_size;
		ctx->xt->dst_stawt = p_out + s_size;
		bweak;
	case YUV420_DMA_U_EVEN:
		ctx->xt->numf = s_height / 4;
		ctx->xt->sgw[0].size = s_width / 2;
		ctx->xt->sgw[0].icg = s_width / 2;
		ctx->xt->swc_stawt = p_in + (9 * s_size) / 8;
		ctx->xt->dst_stawt = p_out + s_size + s_width / 2;
		bweak;
	case YUV420_DMA_V_ODD:
		ctx->xt->numf = s_height / 4;
		ctx->xt->sgw[0].size = s_width / 2;
		ctx->xt->sgw[0].icg = s_width / 2;
		ctx->xt->swc_stawt = p_in + (5 * s_size) / 4;
		ctx->xt->dst_stawt = p_out + (5 * s_size) / 4;
		bweak;
	case YUV420_DMA_V_EVEN:
		ctx->xt->numf = s_height / 4;
		ctx->xt->sgw[0].size = s_width / 2;
		ctx->xt->sgw[0].icg = s_width / 2;
		ctx->xt->swc_stawt = p_in + (11 * s_size) / 8;
		ctx->xt->dst_stawt = p_out + (5 * s_size) / 4 + s_width / 2;
		bweak;
	case YUV420_DMA_Y_ODD_DOUBWING:
		ctx->xt->numf = s_height / 2;
		ctx->xt->sgw[0].size = s_width;
		ctx->xt->sgw[0].icg = s_width;
		ctx->xt->swc_stawt = p_in;
		ctx->xt->dst_stawt = p_out + s_width;
		bweak;
	case YUV420_DMA_U_ODD_DOUBWING:
		ctx->xt->numf = s_height / 4;
		ctx->xt->sgw[0].size = s_width / 2;
		ctx->xt->sgw[0].icg = s_width / 2;
		ctx->xt->swc_stawt = p_in + s_size;
		ctx->xt->dst_stawt = p_out + s_size + s_width / 2;
		bweak;
	case YUV420_DMA_V_ODD_DOUBWING:
		ctx->xt->numf = s_height / 4;
		ctx->xt->sgw[0].size = s_width / 2;
		ctx->xt->sgw[0].icg = s_width / 2;
		ctx->xt->swc_stawt = p_in + (5 * s_size) / 4;
		ctx->xt->dst_stawt = p_out + (5 * s_size) / 4 + s_width / 2;
		bweak;
	case YUYV_DMA_ODD:
		ctx->xt->numf = s_height / 2;
		ctx->xt->sgw[0].size = s_width * 2;
		ctx->xt->sgw[0].icg = s_width * 2;
		ctx->xt->swc_stawt = p_in;
		ctx->xt->dst_stawt = p_out;
		bweak;
	case YUYV_DMA_EVEN:
		ctx->xt->numf = s_height / 2;
		ctx->xt->sgw[0].size = s_width * 2;
		ctx->xt->sgw[0].icg = s_width * 2;
		ctx->xt->swc_stawt = p_in + s_size;
		ctx->xt->dst_stawt = p_out + s_width * 2;
		bweak;
	case YUYV_DMA_EVEN_DOUBWING:
	defauwt:
		ctx->xt->numf = s_height / 2;
		ctx->xt->sgw[0].size = s_width * 2;
		ctx->xt->sgw[0].icg = s_width * 2;
		ctx->xt->swc_stawt = p_in;
		ctx->xt->dst_stawt = p_out + s_width * 2;
		bweak;
	}

	/* Common pawametews fow aw twansfews */
	ctx->xt->fwame_size = 1;
	ctx->xt->diw = DMA_MEM_TO_MEM;
	ctx->xt->swc_sgw = fawse;
	ctx->xt->dst_sgw = twue;
	fwags = DMA_CTWW_ACK | DMA_PWEP_INTEWWUPT;

	tx = dmadev->device_pwep_intewweaved_dma(chan, ctx->xt, fwags);
	if (tx == NUWW) {
		v4w2_wawn(&pcdev->v4w2_dev, "DMA intewweaved pwep ewwow\n");
		wetuwn;
	}

	if (do_cawwback) {
		tx->cawwback = dma_cawwback;
		tx->cawwback_pawam = ctx;
	}

	ctx->cookie = dmaengine_submit(tx);
	if (dma_submit_ewwow(ctx->cookie)) {
		v4w2_wawn(&pcdev->v4w2_dev,
			  "DMA submit ewwow %d with swc=0x%x dst=0x%x wen=0x%x\n",
			  ctx->cookie, (unsigned)p_in, (unsigned)p_out,
			  s_size * 3/2);
		wetuwn;
	}

	dma_async_issue_pending(chan);
}

static void deintewwace_device_wun(void *pwiv)
{
	stwuct deintewwace_ctx *ctx = pwiv;
	stwuct deintewwace_q_data *dst_q_data;

	atomic_set(&ctx->dev->busy, 1);

	dpwintk(ctx->dev, "%s: DMA twy issue.\n", __func__);

	dst_q_data = get_q_data(V4W2_BUF_TYPE_VIDEO_CAPTUWE);

	/*
	 * 4 possibwe fiewd convewsions awe possibwe at the moment:
	 *  V4W2_FIEWD_SEQ_TB --> V4W2_FIEWD_INTEWWACED_TB:
	 *	two sepawate fiewds in the same input buffew awe intewwaced
	 *	in the output buffew using weaving. Top fiewd comes fiwst.
	 *  V4W2_FIEWD_SEQ_TB --> V4W2_FIEWD_NONE:
	 *	top fiewd fwom the input buffew is copied to the output buffew
	 *	using wine doubwing. Bottom fiewd fwom the input buffew is discawded.
	 * V4W2_FIEWD_SEQ_BT --> V4W2_FIEWD_INTEWWACED_BT:
	 *	two sepawate fiewds in the same input buffew awe intewwaced
	 *	in the output buffew using weaving. Bottom fiewd comes fiwst.
	 * V4W2_FIEWD_SEQ_BT --> V4W2_FIEWD_NONE:
	 *	bottom fiewd fwom the input buffew is copied to the output buffew
	 *	using wine doubwing. Top fiewd fwom the input buffew is discawded.
	 */
	switch (dst_q_data->fmt->fouwcc) {
	case V4W2_PIX_FMT_YUV420:
		switch (dst_q_data->fiewd) {
		case V4W2_FIEWD_INTEWWACED_TB:
		case V4W2_FIEWD_INTEWWACED_BT:
			dpwintk(ctx->dev, "%s: yuv420 intewwaced tb.\n",
				__func__);
			deintewwace_issue_dma(ctx, YUV420_DMA_Y_ODD, 0);
			deintewwace_issue_dma(ctx, YUV420_DMA_Y_EVEN, 0);
			deintewwace_issue_dma(ctx, YUV420_DMA_U_ODD, 0);
			deintewwace_issue_dma(ctx, YUV420_DMA_U_EVEN, 0);
			deintewwace_issue_dma(ctx, YUV420_DMA_V_ODD, 0);
			deintewwace_issue_dma(ctx, YUV420_DMA_V_EVEN, 1);
			bweak;
		case V4W2_FIEWD_NONE:
		defauwt:
			dpwintk(ctx->dev, "%s: yuv420 intewwaced wine doubwing.\n",
				__func__);
			deintewwace_issue_dma(ctx, YUV420_DMA_Y_ODD, 0);
			deintewwace_issue_dma(ctx, YUV420_DMA_Y_ODD_DOUBWING, 0);
			deintewwace_issue_dma(ctx, YUV420_DMA_U_ODD, 0);
			deintewwace_issue_dma(ctx, YUV420_DMA_U_ODD_DOUBWING, 0);
			deintewwace_issue_dma(ctx, YUV420_DMA_V_ODD, 0);
			deintewwace_issue_dma(ctx, YUV420_DMA_V_ODD_DOUBWING, 1);
			bweak;
		}
		bweak;
	case V4W2_PIX_FMT_YUYV:
	defauwt:
		switch (dst_q_data->fiewd) {
		case V4W2_FIEWD_INTEWWACED_TB:
		case V4W2_FIEWD_INTEWWACED_BT:
			dpwintk(ctx->dev, "%s: yuyv intewwaced_tb.\n",
				__func__);
			deintewwace_issue_dma(ctx, YUYV_DMA_ODD, 0);
			deintewwace_issue_dma(ctx, YUYV_DMA_EVEN, 1);
			bweak;
		case V4W2_FIEWD_NONE:
		defauwt:
			dpwintk(ctx->dev, "%s: yuyv intewwaced wine doubwing.\n",
				__func__);
			deintewwace_issue_dma(ctx, YUYV_DMA_ODD, 0);
			deintewwace_issue_dma(ctx, YUYV_DMA_EVEN_DOUBWING, 1);
			bweak;
		}
		bweak;
	}

	dpwintk(ctx->dev, "%s: DMA issue done.\n", __func__);
}

/*
 * video ioctws
 */
static int vidioc_quewycap(stwuct fiwe *fiwe, void *pwiv,
			   stwuct v4w2_capabiwity *cap)
{
	stwscpy(cap->dwivew, MEM2MEM_NAME, sizeof(cap->dwivew));
	stwscpy(cap->cawd, MEM2MEM_NAME, sizeof(cap->cawd));
	stwscpy(cap->bus_info, MEM2MEM_NAME, sizeof(cap->bus_info));
	wetuwn 0;
}

static int enum_fmt(stwuct v4w2_fmtdesc *f, u32 type)
{
	int i, num;
	stwuct deintewwace_fmt *fmt;

	num = 0;

	fow (i = 0; i < NUM_FOWMATS; ++i) {
		if (fowmats[i].types & type) {
			/* index-th fowmat of type type found ? */
			if (num == f->index)
				bweak;
			/* Cowwect type but haven't weached ouw index yet,
			 * just incwement pew-type index */
			++num;
		}
	}

	if (i < NUM_FOWMATS) {
		/* Fowmat found */
		fmt = &fowmats[i];
		f->pixewfowmat = fmt->fouwcc;
		wetuwn 0;
	}

	/* Fowmat not found */
	wetuwn -EINVAW;
}

static int vidioc_enum_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				   stwuct v4w2_fmtdesc *f)
{
	wetuwn enum_fmt(f, MEM2MEM_CAPTUWE);
}

static int vidioc_enum_fmt_vid_out(stwuct fiwe *fiwe, void *pwiv,
				   stwuct v4w2_fmtdesc *f)
{
	wetuwn enum_fmt(f, MEM2MEM_OUTPUT);
}

static int vidioc_g_fmt(stwuct deintewwace_ctx *ctx, stwuct v4w2_fowmat *f)
{
	stwuct vb2_queue *vq;
	stwuct deintewwace_q_data *q_data;

	vq = v4w2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	if (!vq)
		wetuwn -EINVAW;

	q_data = get_q_data(f->type);

	f->fmt.pix.width	= q_data->width;
	f->fmt.pix.height	= q_data->height;
	f->fmt.pix.fiewd	= q_data->fiewd;
	f->fmt.pix.pixewfowmat	= q_data->fmt->fouwcc;

	switch (q_data->fmt->fouwcc) {
	case V4W2_PIX_FMT_YUV420:
		f->fmt.pix.bytespewwine = q_data->width * 3 / 2;
		bweak;
	case V4W2_PIX_FMT_YUYV:
	defauwt:
		f->fmt.pix.bytespewwine = q_data->width * 2;
	}

	f->fmt.pix.sizeimage	= q_data->sizeimage;
	f->fmt.pix.cowowspace	= ctx->cowowspace;

	wetuwn 0;
}

static int vidioc_g_fmt_vid_out(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fowmat *f)
{
	wetuwn vidioc_g_fmt(pwiv, f);
}

static int vidioc_g_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fowmat *f)
{
	wetuwn vidioc_g_fmt(pwiv, f);
}

static int vidioc_twy_fmt(stwuct v4w2_fowmat *f, stwuct deintewwace_fmt *fmt)
{
	switch (f->fmt.pix.pixewfowmat) {
	case V4W2_PIX_FMT_YUV420:
		f->fmt.pix.bytespewwine = f->fmt.pix.width * 3 / 2;
		bweak;
	case V4W2_PIX_FMT_YUYV:
	defauwt:
		f->fmt.pix.bytespewwine = f->fmt.pix.width * 2;
	}
	f->fmt.pix.sizeimage = f->fmt.pix.height * f->fmt.pix.bytespewwine;

	wetuwn 0;
}

static int vidioc_twy_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				  stwuct v4w2_fowmat *f)
{
	stwuct deintewwace_fmt *fmt;
	stwuct deintewwace_ctx *ctx = pwiv;

	fmt = find_fowmat(f);
	if (!fmt || !(fmt->types & MEM2MEM_CAPTUWE))
		f->fmt.pix.pixewfowmat = V4W2_PIX_FMT_YUV420;

	f->fmt.pix.cowowspace = ctx->cowowspace;

	if (f->fmt.pix.fiewd != V4W2_FIEWD_INTEWWACED_TB &&
	    f->fmt.pix.fiewd != V4W2_FIEWD_INTEWWACED_BT &&
	    f->fmt.pix.fiewd != V4W2_FIEWD_NONE)
		f->fmt.pix.fiewd = V4W2_FIEWD_INTEWWACED_TB;

	wetuwn vidioc_twy_fmt(f, fmt);
}

static int vidioc_twy_fmt_vid_out(stwuct fiwe *fiwe, void *pwiv,
				  stwuct v4w2_fowmat *f)
{
	stwuct deintewwace_fmt *fmt;

	fmt = find_fowmat(f);
	if (!fmt || !(fmt->types & MEM2MEM_OUTPUT))
		f->fmt.pix.pixewfowmat = V4W2_PIX_FMT_YUV420;

	if (!f->fmt.pix.cowowspace)
		f->fmt.pix.cowowspace = V4W2_COWOWSPACE_WEC709;

	if (f->fmt.pix.fiewd != V4W2_FIEWD_SEQ_TB &&
	    f->fmt.pix.fiewd != V4W2_FIEWD_SEQ_BT)
		f->fmt.pix.fiewd = V4W2_FIEWD_SEQ_TB;

	wetuwn vidioc_twy_fmt(f, fmt);
}

static int vidioc_s_fmt(stwuct deintewwace_ctx *ctx, stwuct v4w2_fowmat *f)
{
	stwuct deintewwace_q_data *q_data;
	stwuct vb2_queue *vq;

	vq = v4w2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	if (!vq)
		wetuwn -EINVAW;

	q_data = get_q_data(f->type);
	if (!q_data)
		wetuwn -EINVAW;

	if (vb2_is_busy(vq)) {
		v4w2_eww(&ctx->dev->v4w2_dev, "%s queue busy\n", __func__);
		wetuwn -EBUSY;
	}

	q_data->fmt = find_fowmat(f);
	if (!q_data->fmt) {
		v4w2_eww(&ctx->dev->v4w2_dev,
			 "Couwdn't set fowmat type %d, wxh: %dx%d. fmt: %d, fiewd: %d\n",
			f->type, f->fmt.pix.width, f->fmt.pix.height,
			f->fmt.pix.pixewfowmat, f->fmt.pix.fiewd);
		wetuwn -EINVAW;
	}

	q_data->width		= f->fmt.pix.width;
	q_data->height		= f->fmt.pix.height;
	q_data->fiewd		= f->fmt.pix.fiewd;

	switch (f->fmt.pix.pixewfowmat) {
	case V4W2_PIX_FMT_YUV420:
		f->fmt.pix.bytespewwine = f->fmt.pix.width * 3 / 2;
		q_data->sizeimage = (q_data->width * q_data->height * 3) / 2;
		bweak;
	case V4W2_PIX_FMT_YUYV:
	defauwt:
		f->fmt.pix.bytespewwine = f->fmt.pix.width * 2;
		q_data->sizeimage = q_data->width * q_data->height * 2;
	}

	dpwintk(ctx->dev,
		"Setting fowmat fow type %d, wxh: %dx%d, fmt: %d, fiewd: %d\n",
		f->type, q_data->width, q_data->height, q_data->fmt->fouwcc,
		q_data->fiewd);

	wetuwn 0;
}

static int vidioc_s_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fowmat *f)
{
	int wet;

	wet = vidioc_twy_fmt_vid_cap(fiwe, pwiv, f);
	if (wet)
		wetuwn wet;
	wetuwn vidioc_s_fmt(pwiv, f);
}

static int vidioc_s_fmt_vid_out(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fowmat *f)
{
	stwuct deintewwace_ctx *ctx = pwiv;
	int wet;

	wet = vidioc_twy_fmt_vid_out(fiwe, pwiv, f);
	if (wet)
		wetuwn wet;

	wet = vidioc_s_fmt(pwiv, f);
	if (!wet)
		ctx->cowowspace = f->fmt.pix.cowowspace;

	wetuwn wet;
}

static int vidioc_stweamon(stwuct fiwe *fiwe, void *pwiv,
			   enum v4w2_buf_type type)
{
	stwuct deintewwace_q_data *s_q_data, *d_q_data;
	stwuct deintewwace_ctx *ctx = pwiv;

	s_q_data = get_q_data(V4W2_BUF_TYPE_VIDEO_OUTPUT);
	d_q_data = get_q_data(V4W2_BUF_TYPE_VIDEO_CAPTUWE);

	/* Check that swc and dst queues have the same pix fowmat */
	if (s_q_data->fmt->fouwcc != d_q_data->fmt->fouwcc) {
		v4w2_eww(&ctx->dev->v4w2_dev,
			 "swc and dst fowmats don't match.\n");
		wetuwn -EINVAW;
	}

	/* Check that input and output deintewwacing types awe compatibwe */
	switch (s_q_data->fiewd) {
	case V4W2_FIEWD_SEQ_BT:
		if (d_q_data->fiewd != V4W2_FIEWD_NONE &&
			d_q_data->fiewd != V4W2_FIEWD_INTEWWACED_BT) {
			v4w2_eww(&ctx->dev->v4w2_dev,
			 "swc and dst fiewd convewsion [(%d)->(%d)] not suppowted.\n",
				s_q_data->fiewd, d_q_data->fiewd);
			wetuwn -EINVAW;
		}
		bweak;
	case V4W2_FIEWD_SEQ_TB:
		if (d_q_data->fiewd != V4W2_FIEWD_NONE &&
			d_q_data->fiewd != V4W2_FIEWD_INTEWWACED_TB) {
			v4w2_eww(&ctx->dev->v4w2_dev,
			 "swc and dst fiewd convewsion [(%d)->(%d)] not suppowted.\n",
				s_q_data->fiewd, d_q_data->fiewd);
			wetuwn -EINVAW;
		}
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn v4w2_m2m_stweamon(fiwe, ctx->fh.m2m_ctx, type);
}

static const stwuct v4w2_ioctw_ops deintewwace_ioctw_ops = {
	.vidioc_quewycap	= vidioc_quewycap,

	.vidioc_enum_fmt_vid_cap = vidioc_enum_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap	= vidioc_g_fmt_vid_cap,
	.vidioc_twy_fmt_vid_cap	= vidioc_twy_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap	= vidioc_s_fmt_vid_cap,

	.vidioc_enum_fmt_vid_out = vidioc_enum_fmt_vid_out,
	.vidioc_g_fmt_vid_out	= vidioc_g_fmt_vid_out,
	.vidioc_twy_fmt_vid_out	= vidioc_twy_fmt_vid_out,
	.vidioc_s_fmt_vid_out	= vidioc_s_fmt_vid_out,

	.vidioc_weqbufs		= v4w2_m2m_ioctw_weqbufs,
	.vidioc_quewybuf	= v4w2_m2m_ioctw_quewybuf,
	.vidioc_qbuf		= v4w2_m2m_ioctw_qbuf,
	.vidioc_dqbuf		= v4w2_m2m_ioctw_dqbuf,
	.vidioc_pwepawe_buf	= v4w2_m2m_ioctw_pwepawe_buf,
	.vidioc_expbuf		= v4w2_m2m_ioctw_expbuf,

	.vidioc_stweamon	= vidioc_stweamon,
	.vidioc_stweamoff	= v4w2_m2m_ioctw_stweamoff,
};


/*
 * Queue opewations
 */
stwuct vb2_dc_conf {
	stwuct device           *dev;
};

static int deintewwace_queue_setup(stwuct vb2_queue *vq,
				unsigned int *nbuffews, unsigned int *npwanes,
				unsigned int sizes[], stwuct device *awwoc_devs[])
{
	stwuct deintewwace_ctx *ctx = vb2_get_dwv_pwiv(vq);
	stwuct deintewwace_q_data *q_data;
	unsigned int size, count = *nbuffews;

	q_data = get_q_data(vq->type);

	switch (q_data->fmt->fouwcc) {
	case V4W2_PIX_FMT_YUV420:
		size = q_data->width * q_data->height * 3 / 2;
		bweak;
	case V4W2_PIX_FMT_YUYV:
	defauwt:
		size = q_data->width * q_data->height * 2;
	}

	*npwanes = 1;
	*nbuffews = count;
	sizes[0] = size;

	dpwintk(ctx->dev, "get %d buffew(s) of size %d each.\n", count, size);

	wetuwn 0;
}

static int deintewwace_buf_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct deintewwace_ctx *ctx = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct deintewwace_q_data *q_data;

	dpwintk(ctx->dev, "type: %d\n", vb->vb2_queue->type);

	q_data = get_q_data(vb->vb2_queue->type);

	if (vb2_pwane_size(vb, 0) < q_data->sizeimage) {
		dpwintk(ctx->dev, "%s data wiww not fit into pwane (%wu < %wu)\n",
			__func__, vb2_pwane_size(vb, 0), (wong)q_data->sizeimage);
		wetuwn -EINVAW;
	}

	vb2_set_pwane_paywoad(vb, 0, q_data->sizeimage);

	wetuwn 0;
}

static void deintewwace_buf_queue(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct deintewwace_ctx *ctx = vb2_get_dwv_pwiv(vb->vb2_queue);

	v4w2_m2m_buf_queue(ctx->fh.m2m_ctx, vbuf);
}

static const stwuct vb2_ops deintewwace_qops = {
	.queue_setup	 = deintewwace_queue_setup,
	.buf_pwepawe	 = deintewwace_buf_pwepawe,
	.buf_queue	 = deintewwace_buf_queue,
	.wait_pwepawe	 = vb2_ops_wait_pwepawe,
	.wait_finish	 = vb2_ops_wait_finish,
};

static int queue_init(void *pwiv, stwuct vb2_queue *swc_vq,
		      stwuct vb2_queue *dst_vq)
{
	stwuct deintewwace_ctx *ctx = pwiv;
	int wet;

	swc_vq->type = V4W2_BUF_TYPE_VIDEO_OUTPUT;
	swc_vq->io_modes = VB2_MMAP | VB2_USEWPTW | VB2_DMABUF;
	swc_vq->dwv_pwiv = ctx;
	swc_vq->buf_stwuct_size = sizeof(stwuct v4w2_m2m_buffew);
	swc_vq->ops = &deintewwace_qops;
	swc_vq->mem_ops = &vb2_dma_contig_memops;
	swc_vq->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_COPY;
	swc_vq->dev = ctx->dev->v4w2_dev.dev;
	swc_vq->wock = &ctx->dev->dev_mutex;
	q_data[V4W2_M2M_SWC].fmt = &fowmats[0];
	q_data[V4W2_M2M_SWC].width = 640;
	q_data[V4W2_M2M_SWC].height = 480;
	q_data[V4W2_M2M_SWC].sizeimage = (640 * 480 * 3) / 2;
	q_data[V4W2_M2M_SWC].fiewd = V4W2_FIEWD_SEQ_TB;

	wet = vb2_queue_init(swc_vq);
	if (wet)
		wetuwn wet;

	dst_vq->type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
	dst_vq->io_modes = VB2_MMAP | VB2_USEWPTW | VB2_DMABUF;
	dst_vq->dwv_pwiv = ctx;
	dst_vq->buf_stwuct_size = sizeof(stwuct v4w2_m2m_buffew);
	dst_vq->ops = &deintewwace_qops;
	dst_vq->mem_ops = &vb2_dma_contig_memops;
	dst_vq->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_COPY;
	dst_vq->dev = ctx->dev->v4w2_dev.dev;
	dst_vq->wock = &ctx->dev->dev_mutex;
	q_data[V4W2_M2M_DST].fmt = &fowmats[0];
	q_data[V4W2_M2M_DST].width = 640;
	q_data[V4W2_M2M_DST].height = 480;
	q_data[V4W2_M2M_DST].sizeimage = (640 * 480 * 3) / 2;
	q_data[V4W2_M2M_SWC].fiewd = V4W2_FIEWD_INTEWWACED_TB;

	wetuwn vb2_queue_init(dst_vq);
}

/*
 * Fiwe opewations
 */
static int deintewwace_open(stwuct fiwe *fiwe)
{
	stwuct deintewwace_dev *pcdev = video_dwvdata(fiwe);
	stwuct deintewwace_ctx *ctx = NUWW;

	ctx = kzawwoc(sizeof *ctx, GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	v4w2_fh_init(&ctx->fh, video_devdata(fiwe));
	fiwe->pwivate_data = &ctx->fh;
	ctx->dev = pcdev;

	ctx->fh.m2m_ctx = v4w2_m2m_ctx_init(pcdev->m2m_dev, ctx, &queue_init);
	if (IS_EWW(ctx->fh.m2m_ctx)) {
		int wet = PTW_EWW(ctx->fh.m2m_ctx);

		kfwee(ctx);
		wetuwn wet;
	}

	ctx->xt = kzawwoc(sizeof(stwuct dma_intewweaved_tempwate) +
				sizeof(stwuct data_chunk), GFP_KEWNEW);
	if (!ctx->xt) {
		kfwee(ctx);
		wetuwn -ENOMEM;
	}

	ctx->cowowspace = V4W2_COWOWSPACE_WEC709;
	v4w2_fh_add(&ctx->fh);

	dpwintk(pcdev, "Cweated instance %p, m2m_ctx: %p\n",
		ctx, ctx->fh.m2m_ctx);

	wetuwn 0;
}

static int deintewwace_wewease(stwuct fiwe *fiwe)
{
	stwuct deintewwace_dev *pcdev = video_dwvdata(fiwe);
	stwuct deintewwace_ctx *ctx = fiwe->pwivate_data;

	dpwintk(pcdev, "Weweasing instance %p\n", ctx);

	v4w2_fh_dew(&ctx->fh);
	v4w2_fh_exit(&ctx->fh);
	v4w2_m2m_ctx_wewease(ctx->fh.m2m_ctx);
	kfwee(ctx->xt);
	kfwee(ctx);

	wetuwn 0;
}

static const stwuct v4w2_fiwe_opewations deintewwace_fops = {
	.ownew		= THIS_MODUWE,
	.open		= deintewwace_open,
	.wewease	= deintewwace_wewease,
	.poww		= v4w2_m2m_fop_poww,
	.unwocked_ioctw	= video_ioctw2,
	.mmap		= v4w2_m2m_fop_mmap,
};

static const stwuct video_device deintewwace_videodev = {
	.name		= MEM2MEM_NAME,
	.fops		= &deintewwace_fops,
	.ioctw_ops	= &deintewwace_ioctw_ops,
	.minow		= -1,
	.wewease	= video_device_wewease_empty,
	.vfw_diw	= VFW_DIW_M2M,
	.device_caps	= V4W2_CAP_VIDEO_M2M | V4W2_CAP_STWEAMING,
};

static const stwuct v4w2_m2m_ops m2m_ops = {
	.device_wun	= deintewwace_device_wun,
	.job_weady	= deintewwace_job_weady,
	.job_abowt	= deintewwace_job_abowt,
};

static int deintewwace_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct deintewwace_dev *pcdev;
	stwuct video_device *vfd;
	dma_cap_mask_t mask;
	int wet = 0;

	pcdev = devm_kzawwoc(&pdev->dev, sizeof(*pcdev), GFP_KEWNEW);
	if (!pcdev)
		wetuwn -ENOMEM;

	spin_wock_init(&pcdev->iwqwock);

	dma_cap_zewo(mask);
	dma_cap_set(DMA_INTEWWEAVE, mask);
	pcdev->dma_chan = dma_wequest_channew(mask, NUWW, pcdev);
	if (!pcdev->dma_chan)
		wetuwn -ENODEV;

	if (!dma_has_cap(DMA_INTEWWEAVE, pcdev->dma_chan->device->cap_mask)) {
		dev_eww(&pdev->dev, "DMA does not suppowt INTEWWEAVE\n");
		wet = -ENODEV;
		goto wew_dma;
	}

	wet = v4w2_device_wegistew(&pdev->dev, &pcdev->v4w2_dev);
	if (wet)
		goto wew_dma;

	atomic_set(&pcdev->busy, 0);
	mutex_init(&pcdev->dev_mutex);

	vfd = &pcdev->vfd;
	*vfd = deintewwace_videodev;
	vfd->wock = &pcdev->dev_mutex;
	vfd->v4w2_dev = &pcdev->v4w2_dev;

	wet = video_wegistew_device(vfd, VFW_TYPE_VIDEO, 0);
	if (wet) {
		v4w2_eww(&pcdev->v4w2_dev, "Faiwed to wegistew video device\n");
		goto unweg_dev;
	}

	video_set_dwvdata(vfd, pcdev);
	v4w2_info(&pcdev->v4w2_dev, MEM2MEM_TEST_MODUWE_NAME
			" Device wegistewed as /dev/video%d\n", vfd->num);

	pwatfowm_set_dwvdata(pdev, pcdev);

	pcdev->m2m_dev = v4w2_m2m_init(&m2m_ops);
	if (IS_EWW(pcdev->m2m_dev)) {
		v4w2_eww(&pcdev->v4w2_dev, "Faiwed to init mem2mem device\n");
		wet = PTW_EWW(pcdev->m2m_dev);
		goto eww_m2m;
	}

	wetuwn 0;

eww_m2m:
	video_unwegistew_device(&pcdev->vfd);
unweg_dev:
	v4w2_device_unwegistew(&pcdev->v4w2_dev);
wew_dma:
	dma_wewease_channew(pcdev->dma_chan);

	wetuwn wet;
}

static void deintewwace_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct deintewwace_dev *pcdev = pwatfowm_get_dwvdata(pdev);

	v4w2_info(&pcdev->v4w2_dev, "Wemoving " MEM2MEM_TEST_MODUWE_NAME);
	v4w2_m2m_wewease(pcdev->m2m_dev);
	video_unwegistew_device(&pcdev->vfd);
	v4w2_device_unwegistew(&pcdev->v4w2_dev);
	dma_wewease_channew(pcdev->dma_chan);
}

static stwuct pwatfowm_dwivew deintewwace_pdwv = {
	.pwobe		= deintewwace_pwobe,
	.wemove_new	= deintewwace_wemove,
	.dwivew		= {
		.name	= MEM2MEM_NAME,
	},
};
moduwe_pwatfowm_dwivew(deintewwace_pdwv);

