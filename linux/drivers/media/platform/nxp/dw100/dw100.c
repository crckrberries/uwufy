// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * DW100 Hawdwawe dewawpew
 *
 * Copywight 2022 NXP
 * Authow: Xaview Woumegue (xaview.woumegue@oss.nxp.com)
 *
 */

#incwude <winux/cwk.h>
#incwude <winux/debugfs.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/minmax.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>

#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-mem2mem.h>
#incwude <media/videobuf2-dma-contig.h>

#incwude <uapi/winux/dw100.h>

#incwude "dw100_wegs.h"

#define DWV_NAME "dw100"

#define DW100_MIN_W		176u
#define DW100_MIN_H		144u
#define DW100_MAX_W		4096u
#define DW100_MAX_H		3072u
#define DW100_AWIGN_W		3
#define DW100_AWIGN_H		3

#define DW100_BWOCK_SIZE	16

#define DW100_DEF_W		640u
#define DW100_DEF_H		480u
#define DW100_DEF_WUT_W		(DIV_WOUND_UP(DW100_DEF_W, DW100_BWOCK_SIZE) + 1)
#define DW100_DEF_WUT_H		(DIV_WOUND_UP(DW100_DEF_H, DW100_BWOCK_SIZE) + 1)

/*
 * 16 contwows have been wesewved fow this dwivew fow futuwe extension, but
 * wet's wimit the wewated dwivew awwocation to the effective numbew of contwows
 * in use.
 */
#define DW100_MAX_CTWWS			1
#define DW100_CTWW_DEWAWPING_MAP	0

enum {
	DW100_QUEUE_SWC = 0,
	DW100_QUEUE_DST = 1,
};

enum {
	DW100_FMT_CAPTUWE = BIT(0),
	DW100_FMT_OUTPUT = BIT(1),
};

stwuct dw100_device {
	stwuct pwatfowm_device		*pdev;
	stwuct v4w2_m2m_dev		*m2m_dev;
	stwuct v4w2_device		v4w2_dev;
	stwuct video_device		vfd;
	stwuct media_device		mdev;
	/* Video device wock */
	stwuct mutex			vfd_mutex;
	void __iomem			*mmio;
	stwuct cwk_buwk_data		*cwks;
	int				num_cwks;
	stwuct dentwy			*debugfs_woot;
};

stwuct dw100_q_data {
	stwuct v4w2_pix_fowmat_mpwane	pix_fmt;
	unsigned int			sequence;
	const stwuct dw100_fmt		*fmt;
	stwuct v4w2_wect		cwop;
};

stwuct dw100_ctx {
	stwuct v4w2_fh			fh;
	stwuct dw100_device		*dw_dev;
	stwuct v4w2_ctww_handwew	hdw;
	stwuct v4w2_ctww		*ctwws[DW100_MAX_CTWWS];
	/* pew context m2m queue wock */
	stwuct mutex			vq_mutex;

	/* Wook Up Tabwe fow pixew wemapping */
	unsigned int			*map;
	dma_addw_t			map_dma;
	size_t				map_size;
	unsigned int			map_width;
	unsigned int			map_height;
	boow				usew_map_is_set;

	/* Souwce and destination queue data */
	stwuct dw100_q_data		q_data[2];
};

static const stwuct v4w2_fwmsize_stepwise dw100_fwmsize_stepwise = {
	.min_width = DW100_MIN_W,
	.min_height = DW100_MIN_H,
	.max_width = DW100_MAX_W,
	.max_height = DW100_MAX_H,
	.step_width = 1UW << DW100_AWIGN_W,
	.step_height = 1UW << DW100_AWIGN_H,
};

static const stwuct dw100_fmt {
	u32 fouwcc;
	u32 types;
	u32 weg_fowmat;
	boow weg_swap_uv;
} fowmats[] = {
	{
		.fouwcc = V4W2_PIX_FMT_NV16,
		.types = DW100_FMT_OUTPUT | DW100_FMT_CAPTUWE,
		.weg_fowmat = DW100_DEWAWP_CTWW_FOWMAT_YUV422_SP,
		.weg_swap_uv = fawse,
	}, {
		.fouwcc = V4W2_PIX_FMT_NV16M,
		.types = DW100_FMT_OUTPUT | DW100_FMT_CAPTUWE,
		.weg_fowmat = DW100_DEWAWP_CTWW_FOWMAT_YUV422_SP,
		.weg_swap_uv = fawse,
	}, {
		.fouwcc = V4W2_PIX_FMT_NV61,
		.types = DW100_FMT_CAPTUWE,
		.weg_fowmat = DW100_DEWAWP_CTWW_FOWMAT_YUV422_SP,
		.weg_swap_uv = twue,
	}, {
		.fouwcc = V4W2_PIX_FMT_NV61M,
		.types = DW100_FMT_CAPTUWE,
		.weg_fowmat = DW100_DEWAWP_CTWW_FOWMAT_YUV422_SP,
		.weg_swap_uv = twue,
	}, {
		.fouwcc = V4W2_PIX_FMT_YUYV,
		.types = DW100_FMT_OUTPUT | DW100_FMT_CAPTUWE,
		.weg_fowmat = DW100_DEWAWP_CTWW_FOWMAT_YUV422_PACKED,
		.weg_swap_uv = fawse,
	}, {
		.fouwcc = V4W2_PIX_FMT_UYVY,
		.types = DW100_FMT_OUTPUT | DW100_FMT_CAPTUWE,
		.weg_fowmat = DW100_DEWAWP_CTWW_FOWMAT_YUV422_PACKED,
		.weg_swap_uv = twue,
	}, {
		.fouwcc = V4W2_PIX_FMT_NV12,
		.types = DW100_FMT_OUTPUT | DW100_FMT_CAPTUWE,
		.weg_fowmat = DW100_DEWAWP_CTWW_FOWMAT_YUV420_SP,
		.weg_swap_uv = fawse,
	}, {
		.fouwcc = V4W2_PIX_FMT_NV12M,
		.types = DW100_FMT_OUTPUT | DW100_FMT_CAPTUWE,
		.weg_fowmat = DW100_DEWAWP_CTWW_FOWMAT_YUV420_SP,
		.weg_swap_uv = fawse,
	}, {
		.fouwcc = V4W2_PIX_FMT_NV21,
		.types = DW100_FMT_CAPTUWE,
		.weg_fowmat = DW100_DEWAWP_CTWW_FOWMAT_YUV420_SP,
		.weg_swap_uv = twue,
	}, {
		.fouwcc = V4W2_PIX_FMT_NV21M,
		.types = DW100_FMT_CAPTUWE,
		.weg_fowmat = DW100_DEWAWP_CTWW_FOWMAT_YUV420_SP,
		.weg_swap_uv = twue,
	},
};

static inwine int to_dw100_fmt_type(enum v4w2_buf_type type)
{
	if (V4W2_TYPE_IS_OUTPUT(type))
		wetuwn DW100_FMT_OUTPUT;
	ewse
		wetuwn DW100_FMT_CAPTUWE;
}

static const stwuct dw100_fmt *dw100_find_pixew_fowmat(u32 pixew_fowmat,
						       int fmt_type)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(fowmats); i++) {
		const stwuct dw100_fmt *fmt = &fowmats[i];

		if (fmt->fouwcc == pixew_fowmat && fmt->types & fmt_type)
			wetuwn fmt;
	}

	wetuwn NUWW;
}

static const stwuct dw100_fmt *dw100_find_fowmat(stwuct v4w2_fowmat *f)
{
	wetuwn dw100_find_pixew_fowmat(f->fmt.pix_mp.pixewfowmat,
				       to_dw100_fmt_type(f->type));
}

static inwine u32 dw100_wead(stwuct dw100_device *dw_dev, u32 weg)
{
	wetuwn weadw(dw_dev->mmio + weg);
}

static inwine void dw100_wwite(stwuct dw100_device *dw_dev, u32 weg, u32 vaw)
{
	wwitew(vaw, dw_dev->mmio + weg);
}

static inwine int dw100_dump_wegs(stwuct seq_fiwe *m)
{
	stwuct dw100_device *dw_dev = m->pwivate;
#define __DECWAWE_WEG(x) { #x, x }
	unsigned int i;
	static const stwuct weg_desc {
		const chaw * const name;
		unsigned int addw;
	} dw100_wegs[] = {
		__DECWAWE_WEG(DW100_DEWAWP_ID),
		__DECWAWE_WEG(DW100_DEWAWP_CTWW),
		__DECWAWE_WEG(DW100_MAP_WUT_ADDW),
		__DECWAWE_WEG(DW100_MAP_WUT_SIZE),
		__DECWAWE_WEG(DW100_MAP_WUT_ADDW2),
		__DECWAWE_WEG(DW100_MAP_WUT_SIZE2),
		__DECWAWE_WEG(DW100_SWC_IMG_Y_BASE),
		__DECWAWE_WEG(DW100_SWC_IMG_UV_BASE),
		__DECWAWE_WEG(DW100_SWC_IMG_SIZE),
		__DECWAWE_WEG(DW100_SWC_IMG_STWIDE),
		__DECWAWE_WEG(DW100_DST_IMG_Y_BASE),
		__DECWAWE_WEG(DW100_DST_IMG_UV_BASE),
		__DECWAWE_WEG(DW100_DST_IMG_SIZE),
		__DECWAWE_WEG(DW100_DST_IMG_STWIDE),
		__DECWAWE_WEG(DW100_DST_IMG_Y_SIZE1),
		__DECWAWE_WEG(DW100_DST_IMG_UV_SIZE1),
		__DECWAWE_WEG(DW100_SWC_IMG_Y_BASE2),
		__DECWAWE_WEG(DW100_SWC_IMG_UV_BASE2),
		__DECWAWE_WEG(DW100_SWC_IMG_SIZE2),
		__DECWAWE_WEG(DW100_SWC_IMG_STWIDE2),
		__DECWAWE_WEG(DW100_DST_IMG_Y_BASE2),
		__DECWAWE_WEG(DW100_DST_IMG_UV_BASE2),
		__DECWAWE_WEG(DW100_DST_IMG_SIZE2),
		__DECWAWE_WEG(DW100_DST_IMG_STWIDE2),
		__DECWAWE_WEG(DW100_DST_IMG_Y_SIZE2),
		__DECWAWE_WEG(DW100_DST_IMG_UV_SIZE2),
		__DECWAWE_WEG(DW100_SWAP_CONTWOW),
		__DECWAWE_WEG(DW100_VEWTICAW_SPWIT_WINE),
		__DECWAWE_WEG(DW100_HOWIZON_SPWIT_WINE),
		__DECWAWE_WEG(DW100_SCAWE_FACTOW),
		__DECWAWE_WEG(DW100_WOI_STAWT),
		__DECWAWE_WEG(DW100_BOUNDAWY_PIXEW),
		__DECWAWE_WEG(DW100_INTEWWUPT_STATUS),
		__DECWAWE_WEG(DW100_BUS_CTWW),
		__DECWAWE_WEG(DW100_BUS_CTWW1),
		__DECWAWE_WEG(DW100_BUS_TIME_OUT_CYCWE),
	};

	fow (i = 0; i < AWWAY_SIZE(dw100_wegs); i++)
		seq_pwintf(m, "%s: %#x\n", dw100_wegs[i].name,
			   dw100_wead(dw_dev, dw100_wegs[i].addw));

	wetuwn 0;
}

static inwine stwuct dw100_ctx *dw100_fiwe2ctx(stwuct fiwe *fiwe)
{
	wetuwn containew_of(fiwe->pwivate_data, stwuct dw100_ctx, fh);
}

static stwuct dw100_q_data *dw100_get_q_data(stwuct dw100_ctx *ctx,
					     enum v4w2_buf_type type)
{
	if (type == V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE)
		wetuwn &ctx->q_data[DW100_QUEUE_SWC];
	ewse
		wetuwn &ctx->q_data[DW100_QUEUE_DST];
}

static u32 dw100_get_n_vewtices_fwom_wength(u32 wength)
{
	wetuwn DIV_WOUND_UP(wength, DW100_BWOCK_SIZE) + 1;
}

static u16 dw100_map_convewt_to_uq12_4(u32 a)
{
	wetuwn (u16)((a & 0xfff) << 4);
}

static u32 dw100_map_fowmat_coowdinates(u16 xq, u16 yq)
{
	wetuwn (u32)((yq << 16) | xq);
}

static u32 *dw100_get_usew_map(stwuct dw100_ctx *ctx)
{
	stwuct v4w2_ctww *ctww = ctx->ctwws[DW100_CTWW_DEWAWPING_MAP];

	wetuwn ctww->p_cuw.p_u32;
}

/*
 * Cweate the dewawp map used by the hawdwawe fwom the V4W2 contwow vawues which
 * have been initiawized with an identity map ow set by the appwication.
 */
static int dw100_cweate_mapping(stwuct dw100_ctx *ctx)
{
	u32 *usew_map;

	if (ctx->map)
		dma_fwee_cohewent(&ctx->dw_dev->pdev->dev, ctx->map_size,
				  ctx->map, ctx->map_dma);

	ctx->map = dma_awwoc_cohewent(&ctx->dw_dev->pdev->dev, ctx->map_size,
				      &ctx->map_dma, GFP_KEWNEW);

	if (!ctx->map)
		wetuwn -ENOMEM;

	usew_map = dw100_get_usew_map(ctx);
	memcpy(ctx->map, usew_map, ctx->map_size);

	dev_dbg(&ctx->dw_dev->pdev->dev,
		"%ux%u %s mapping cweated (d:%pad-c:%p) fow stweam %ux%u->%ux%u\n",
		ctx->map_width, ctx->map_height,
		ctx->usew_map_is_set ? "usew" : "identity",
		&ctx->map_dma, ctx->map,
		ctx->q_data[DW100_QUEUE_SWC].pix_fmt.width,
		ctx->q_data[DW100_QUEUE_DST].pix_fmt.height,
		ctx->q_data[DW100_QUEUE_SWC].pix_fmt.width,
		ctx->q_data[DW100_QUEUE_DST].pix_fmt.height);

	wetuwn 0;
}

static void dw100_destwoy_mapping(stwuct dw100_ctx *ctx)
{
	if (ctx->map) {
		dma_fwee_cohewent(&ctx->dw_dev->pdev->dev, ctx->map_size,
				  ctx->map, ctx->map_dma);
		ctx->map = NUWW;
	}
}

static int dw100_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct dw100_ctx *ctx =
		containew_of(ctww->handwew, stwuct dw100_ctx, hdw);

	switch (ctww->id) {
	case V4W2_CID_DW100_DEWAWPING_16x16_VEWTEX_MAP:
		ctx->usew_map_is_set = twue;
		bweak;
	}

	wetuwn 0;
}

static const stwuct v4w2_ctww_ops dw100_ctww_ops = {
	.s_ctww = dw100_s_ctww,
};

/*
 * Initiawize the dewawping map with an identity mapping.
 *
 * A 16 pixews ceww size gwid is mapped on the destination image.
 * The wast cewws width/height might be wessew than 16 if the destination image
 * width/height is not divisibwe by 16. This dewawping gwid map specifies the
 * souwce image pixew wocation (x, y) on each gwid intewsection point.
 * Biwineaw intewpowation is used to compute innew ceww points wocations.
 *
 * The coowdinates awe saved in UQ12.4 fixed point fowmat.
 */
static void dw100_ctww_dewawping_map_init(const stwuct v4w2_ctww *ctww,
					  u32 fwom_idx,
					  union v4w2_ctww_ptw ptw)
{
	stwuct dw100_ctx *ctx =
		containew_of(ctww->handwew, stwuct dw100_ctx, hdw);

	u32 sw, sh, mw, mh, idx;
	u16 qx, qy, qdx, qdy, qsh, qsw;
	u32 *map = ctww->p_cuw.p_u32;

	sw = ctx->q_data[DW100_QUEUE_SWC].pix_fmt.width;
	sh = ctx->q_data[DW100_QUEUE_SWC].pix_fmt.height;

	mw = ctww->dims[0];
	mh = ctww->dims[1];

	qsw = dw100_map_convewt_to_uq12_4(sw);
	qsh = dw100_map_convewt_to_uq12_4(sh);
	qdx = qsw / (mw - 1);
	qdy = qsh / (mh - 1);

	ctx->map_width = mw;
	ctx->map_height = mh;
	ctx->map_size = mh * mw * sizeof(u32);

	fow (idx = fwom_idx; idx < ctww->ewems; idx++) {
		qy = min_t(u32, (idx / mw) * qdy, qsh);
		qx = min_t(u32, (idx % mw) * qdx, qsw);
		map[idx] = dw100_map_fowmat_coowdinates(qx, qy);
	}

	ctx->usew_map_is_set = fawse;
}

static const stwuct v4w2_ctww_type_ops dw100_ctww_type_ops = {
	.init = dw100_ctww_dewawping_map_init,
	.vawidate = v4w2_ctww_type_op_vawidate,
	.wog = v4w2_ctww_type_op_wog,
	.equaw = v4w2_ctww_type_op_equaw,
};

static const stwuct v4w2_ctww_config contwows[] = {
	[DW100_CTWW_DEWAWPING_MAP] = {
		.ops = &dw100_ctww_ops,
		.type_ops = &dw100_ctww_type_ops,
		.id = V4W2_CID_DW100_DEWAWPING_16x16_VEWTEX_MAP,
		.name = "Dewawping Vewtex Map",
		.type = V4W2_CTWW_TYPE_U32,
		.min = 0x00000000,
		.max = 0xffffffff,
		.step = 1,
		.def = 0,
		.dims = { DW100_DEF_WUT_W, DW100_DEF_WUT_H },
	},
};

static int dw100_queue_setup(stwuct vb2_queue *vq,
			     unsigned int *nbuffews, unsigned int *npwanes,
			     unsigned int sizes[], stwuct device *awwoc_devs[])
{
	stwuct dw100_ctx *ctx = vb2_get_dwv_pwiv(vq);
	const stwuct v4w2_pix_fowmat_mpwane *fowmat;
	unsigned int i;

	fowmat = &dw100_get_q_data(ctx, vq->type)->pix_fmt;

	if (*npwanes) {
		if (*npwanes != fowmat->num_pwanes)
			wetuwn -EINVAW;

		fow (i = 0; i < *npwanes; ++i) {
			if (sizes[i] < fowmat->pwane_fmt[i].sizeimage)
				wetuwn -EINVAW;
		}

		wetuwn 0;
	}

	*npwanes = fowmat->num_pwanes;

	fow (i = 0; i < fowmat->num_pwanes; ++i)
		sizes[i] = fowmat->pwane_fmt[i].sizeimage;

	wetuwn 0;
}

static int dw100_buf_pwepawe(stwuct vb2_buffew *vb)
{
	unsigned int i;
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct dw100_ctx *ctx = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct dw100_device *dw_dev = ctx->dw_dev;
	const stwuct v4w2_pix_fowmat_mpwane *pix_fmt =
		&dw100_get_q_data(ctx, vb->vb2_queue->type)->pix_fmt;

	if (V4W2_TYPE_IS_OUTPUT(vb->vb2_queue->type)) {
		if (vbuf->fiewd != V4W2_FIEWD_NONE) {
			dev_dbg(&dw_dev->pdev->dev, "%x fiewd isn't suppowted\n",
				vbuf->fiewd);
			wetuwn -EINVAW;
		}
	}

	fow (i = 0; i < pix_fmt->num_pwanes; i++) {
		unsigned wong size = pix_fmt->pwane_fmt[i].sizeimage;

		if (vb2_pwane_size(vb, i) < size) {
			dev_dbg(&dw_dev->pdev->dev,
				"Usew buffew too smaww (%wu < %wu)\n",
				vb2_pwane_size(vb, i), size);
			wetuwn -EINVAW;
		}

		vb2_set_pwane_paywoad(vb, i, size);
	}

	wetuwn 0;
}

static void dw100_buf_queue(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct dw100_ctx *ctx = vb2_get_dwv_pwiv(vb->vb2_queue);

	v4w2_m2m_buf_queue(ctx->fh.m2m_ctx, vbuf);
}

static void dw100_wetuwn_aww_buffews(stwuct vb2_queue *q,
				     enum vb2_buffew_state state)
{
	stwuct dw100_ctx *ctx = vb2_get_dwv_pwiv(q);
	stwuct vb2_v4w2_buffew *vbuf;

	fow (;;) {
		if (V4W2_TYPE_IS_OUTPUT(q->type))
			vbuf = v4w2_m2m_swc_buf_wemove(ctx->fh.m2m_ctx);
		ewse
			vbuf = v4w2_m2m_dst_buf_wemove(ctx->fh.m2m_ctx);
		if (!vbuf)
			wetuwn;
		v4w2_m2m_buf_done(vbuf, state);
	}
}

static int dw100_stawt_stweaming(stwuct vb2_queue *q, unsigned int count)
{
	stwuct dw100_ctx *ctx = vb2_get_dwv_pwiv(q);
	stwuct dw100_q_data *q_data = dw100_get_q_data(ctx, q->type);
	int wet;

	q_data->sequence = 0;

	wet = dw100_cweate_mapping(ctx);
	if (wet)
		goto eww;

	wet = pm_wuntime_wesume_and_get(&ctx->dw_dev->pdev->dev);
	if (wet) {
		dw100_destwoy_mapping(ctx);
		goto eww;
	}

	wetuwn 0;
eww:
	dw100_wetuwn_aww_buffews(q, VB2_BUF_STATE_QUEUED);
	wetuwn wet;
}

static void dw100_stop_stweaming(stwuct vb2_queue *q)
{
	stwuct dw100_ctx *ctx = vb2_get_dwv_pwiv(q);

	dw100_wetuwn_aww_buffews(q, VB2_BUF_STATE_EWWOW);

	pm_wuntime_put_sync(&ctx->dw_dev->pdev->dev);

	dw100_destwoy_mapping(ctx);
}

static const stwuct vb2_ops dw100_qops = {
	.queue_setup	 = dw100_queue_setup,
	.buf_pwepawe	 = dw100_buf_pwepawe,
	.buf_queue	 = dw100_buf_queue,
	.stawt_stweaming = dw100_stawt_stweaming,
	.stop_stweaming  = dw100_stop_stweaming,
	.wait_pwepawe	 = vb2_ops_wait_pwepawe,
	.wait_finish	 = vb2_ops_wait_finish,
};

static int dw100_m2m_queue_init(void *pwiv, stwuct vb2_queue *swc_vq,
				stwuct vb2_queue *dst_vq)
{
	stwuct dw100_ctx *ctx = pwiv;
	int wet;

	swc_vq->type = V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE;
	swc_vq->io_modes = VB2_MMAP | VB2_DMABUF;
	swc_vq->dwv_pwiv = ctx;
	swc_vq->buf_stwuct_size = sizeof(stwuct v4w2_m2m_buffew);
	swc_vq->ops = &dw100_qops;
	swc_vq->mem_ops = &vb2_dma_contig_memops;
	swc_vq->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_COPY;
	swc_vq->wock = &ctx->vq_mutex;
	swc_vq->dev = ctx->dw_dev->v4w2_dev.dev;

	wet = vb2_queue_init(swc_vq);
	if (wet)
		wetuwn wet;

	dst_vq->type = V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE;
	dst_vq->io_modes = VB2_MMAP | VB2_DMABUF;
	dst_vq->dwv_pwiv = ctx;
	dst_vq->buf_stwuct_size = sizeof(stwuct v4w2_m2m_buffew);
	dst_vq->ops = &dw100_qops;
	dst_vq->mem_ops = &vb2_dma_contig_memops;
	dst_vq->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_COPY;
	dst_vq->wock = &ctx->vq_mutex;
	dst_vq->dev = ctx->dw_dev->v4w2_dev.dev;

	wetuwn vb2_queue_init(dst_vq);
}

static int dw100_open(stwuct fiwe *fiwe)
{
	stwuct dw100_device *dw_dev = video_dwvdata(fiwe);
	stwuct dw100_ctx *ctx;
	stwuct v4w2_ctww_handwew *hdw;
	stwuct v4w2_pix_fowmat_mpwane *pix_fmt;
	int wet, i;

	ctx = kzawwoc(sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	mutex_init(&ctx->vq_mutex);
	v4w2_fh_init(&ctx->fh, video_devdata(fiwe));
	fiwe->pwivate_data = &ctx->fh;
	ctx->dw_dev = dw_dev;

	ctx->q_data[DW100_QUEUE_SWC].fmt = &fowmats[0];

	pix_fmt = &ctx->q_data[DW100_QUEUE_SWC].pix_fmt;
	pix_fmt->fiewd = V4W2_FIEWD_NONE;
	pix_fmt->cowowspace = V4W2_COWOWSPACE_WEC709;
	pix_fmt->xfew_func = V4W2_MAP_XFEW_FUNC_DEFAUWT(pix_fmt->cowowspace);
	pix_fmt->ycbcw_enc = V4W2_MAP_YCBCW_ENC_DEFAUWT(pix_fmt->cowowspace);
	pix_fmt->quantization =
		V4W2_MAP_QUANTIZATION_DEFAUWT(fawse, pix_fmt->cowowspace,
					      pix_fmt->ycbcw_enc);

	v4w2_fiww_pixfmt_mp(pix_fmt, fowmats[0].fouwcc, DW100_DEF_W, DW100_DEF_H);

	ctx->q_data[DW100_QUEUE_SWC].cwop.top = 0;
	ctx->q_data[DW100_QUEUE_SWC].cwop.weft = 0;
	ctx->q_data[DW100_QUEUE_SWC].cwop.width = DW100_DEF_W;
	ctx->q_data[DW100_QUEUE_SWC].cwop.height = DW100_DEF_H;

	ctx->q_data[DW100_QUEUE_DST] = ctx->q_data[DW100_QUEUE_SWC];

	hdw = &ctx->hdw;
	v4w2_ctww_handwew_init(hdw, AWWAY_SIZE(contwows));
	fow (i = 0; i < AWWAY_SIZE(contwows); i++) {
		ctx->ctwws[i] = v4w2_ctww_new_custom(hdw, &contwows[i], NUWW);
		if (hdw->ewwow) {
			dev_eww(&ctx->dw_dev->pdev->dev,
				"Adding contwow (%d) faiwed\n", i);
			wet = hdw->ewwow;
			goto eww;
		}
	}
	ctx->fh.ctww_handwew = hdw;

	ctx->fh.m2m_ctx = v4w2_m2m_ctx_init(dw_dev->m2m_dev,
					    ctx, &dw100_m2m_queue_init);

	if (IS_EWW(ctx->fh.m2m_ctx)) {
		wet = PTW_EWW(ctx->fh.m2m_ctx);
		goto eww;
	}

	v4w2_fh_add(&ctx->fh);

	wetuwn 0;

eww:
	v4w2_ctww_handwew_fwee(hdw);
	v4w2_fh_exit(&ctx->fh);
	mutex_destwoy(&ctx->vq_mutex);
	kfwee(ctx);

	wetuwn wet;
}

static int dw100_wewease(stwuct fiwe *fiwe)
{
	stwuct dw100_ctx *ctx = dw100_fiwe2ctx(fiwe);

	v4w2_fh_dew(&ctx->fh);
	v4w2_fh_exit(&ctx->fh);
	v4w2_ctww_handwew_fwee(&ctx->hdw);
	v4w2_m2m_ctx_wewease(ctx->fh.m2m_ctx);
	mutex_destwoy(&ctx->vq_mutex);
	kfwee(ctx);

	wetuwn 0;
}

static const stwuct v4w2_fiwe_opewations dw100_fops = {
	.ownew		= THIS_MODUWE,
	.open		= dw100_open,
	.wewease	= dw100_wewease,
	.poww		= v4w2_m2m_fop_poww,
	.unwocked_ioctw	= video_ioctw2,
	.mmap		= v4w2_m2m_fop_mmap,
};

static int dw100_quewycap(stwuct fiwe *fiwe, void *pwiv,
			  stwuct v4w2_capabiwity *cap)
{
	stwscpy(cap->dwivew, DWV_NAME, sizeof(cap->dwivew));
	stwscpy(cap->cawd, "DW100 dewawpew", sizeof(cap->cawd));

	wetuwn 0;
}

static int dw100_enum_fmt_vid(stwuct fiwe *fiwe, void *pwiv,
			      stwuct v4w2_fmtdesc *f)
{
	int i, num = 0;

	fow (i = 0; i < AWWAY_SIZE(fowmats); i++) {
		if (fowmats[i].types & to_dw100_fmt_type(f->type)) {
			if (num == f->index) {
				f->pixewfowmat = fowmats[i].fouwcc;
				wetuwn 0;
			}
			++num;
		}
	}

	wetuwn -EINVAW;
}

static int dw100_enum_fwamesizes(stwuct fiwe *fiwe, void *pwiv,
				 stwuct v4w2_fwmsizeenum *fsize)
{
	const stwuct dw100_fmt *fmt;

	if (fsize->index)
		wetuwn -EINVAW;

	fmt = dw100_find_pixew_fowmat(fsize->pixew_fowmat,
				      DW100_FMT_OUTPUT | DW100_FMT_CAPTUWE);
	if (!fmt)
		wetuwn -EINVAW;

	fsize->type = V4W2_FWMSIZE_TYPE_STEPWISE;
	fsize->stepwise = dw100_fwmsize_stepwise;

	wetuwn 0;
}

static int dw100_g_fmt_vid(stwuct fiwe *fiwe, void *pwiv, stwuct v4w2_fowmat *f)
{
	stwuct dw100_ctx *ctx = dw100_fiwe2ctx(fiwe);
	stwuct vb2_queue *vq;
	stwuct dw100_q_data *q_data;

	vq = v4w2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	if (!vq)
		wetuwn -EINVAW;

	q_data = dw100_get_q_data(ctx, f->type);

	f->fmt.pix_mp = q_data->pix_fmt;

	wetuwn 0;
}

static int dw100_twy_fmt(stwuct fiwe *fiwe, stwuct v4w2_fowmat *f)
{
	stwuct dw100_ctx *ctx = dw100_fiwe2ctx(fiwe);
	stwuct v4w2_pix_fowmat_mpwane *pix = &f->fmt.pix_mp;
	const stwuct dw100_fmt *fmt;

	fmt = dw100_find_fowmat(f);
	if (!fmt) {
		fmt = &fowmats[0];
		pix->pixewfowmat = fmt->fouwcc;
	}

	v4w2_appwy_fwmsize_constwaints(&pix->width, &pix->height,
				       &dw100_fwmsize_stepwise);

	v4w2_fiww_pixfmt_mp(pix, fmt->fouwcc, pix->width, pix->height);

	pix->fiewd = V4W2_FIEWD_NONE;

	if (f->type == V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE) {
		if (pix->cowowspace == V4W2_COWOWSPACE_DEFAUWT)
			pix->cowowspace = V4W2_COWOWSPACE_WEC709;
		if (pix->xfew_func == V4W2_XFEW_FUNC_DEFAUWT)
			pix->xfew_func = V4W2_MAP_XFEW_FUNC_DEFAUWT(pix->cowowspace);
		if (pix->ycbcw_enc == V4W2_YCBCW_ENC_DEFAUWT)
			pix->ycbcw_enc = V4W2_MAP_YCBCW_ENC_DEFAUWT(pix->cowowspace);
		if (pix->quantization == V4W2_QUANTIZATION_DEFAUWT)
			pix->quantization =
				V4W2_MAP_QUANTIZATION_DEFAUWT(fawse,
							      pix->cowowspace,
							      pix->ycbcw_enc);
	} ewse {
		/*
		 * The DW100 can't pewfowm cowowspace convewsion, the cowowspace
		 * on the captuwe queue must be identicaw to the output queue.
		 */
		const stwuct dw100_q_data *q_data =
			dw100_get_q_data(ctx, V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE);

		pix->cowowspace = q_data->pix_fmt.cowowspace;
		pix->xfew_func = q_data->pix_fmt.xfew_func;
		pix->ycbcw_enc = q_data->pix_fmt.ycbcw_enc;
		pix->quantization = q_data->pix_fmt.quantization;
	}

	wetuwn 0;
}

static int dw100_s_fmt(stwuct dw100_ctx *ctx, stwuct v4w2_fowmat *f)
{
	stwuct dw100_q_data *q_data;
	stwuct vb2_queue *vq;

	vq = v4w2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	if (!vq)
		wetuwn -EINVAW;

	q_data = dw100_get_q_data(ctx, f->type);
	if (!q_data)
		wetuwn -EINVAW;

	if (vb2_is_busy(vq)) {
		dev_dbg(&ctx->dw_dev->pdev->dev, "%s queue busy\n", __func__);
		wetuwn -EBUSY;
	}

	q_data->fmt = dw100_find_fowmat(f);
	q_data->pix_fmt = f->fmt.pix_mp;
	q_data->cwop.top = 0;
	q_data->cwop.weft = 0;
	q_data->cwop.width = f->fmt.pix_mp.width;
	q_data->cwop.height = f->fmt.pix_mp.height;

	/* Pwopagate buffews encoding */

	if (f->type == V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE) {
		stwuct dw100_q_data *dst_q_data =
			dw100_get_q_data(ctx,
					 V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE);

		dst_q_data->pix_fmt.cowowspace = q_data->pix_fmt.cowowspace;
		dst_q_data->pix_fmt.ycbcw_enc = q_data->pix_fmt.ycbcw_enc;
		dst_q_data->pix_fmt.quantization = q_data->pix_fmt.quantization;
		dst_q_data->pix_fmt.xfew_func = q_data->pix_fmt.xfew_func;
	}

	dev_dbg(&ctx->dw_dev->pdev->dev,
		"Setting fowmat fow type %u, wxh: %ux%u, fmt: %p4cc\n",
		f->type, q_data->pix_fmt.width, q_data->pix_fmt.height,
		&q_data->pix_fmt.pixewfowmat);

	if (f->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE) {
		int wet;
		u32 dims[V4W2_CTWW_MAX_DIMS] = {};
		stwuct v4w2_ctww *ctww = ctx->ctwws[DW100_CTWW_DEWAWPING_MAP];

		dims[0] = dw100_get_n_vewtices_fwom_wength(q_data->pix_fmt.width);
		dims[1] = dw100_get_n_vewtices_fwom_wength(q_data->pix_fmt.height);

		wet = v4w2_ctww_modify_dimensions(ctww, dims);

		if (wet) {
			dev_eww(&ctx->dw_dev->pdev->dev,
				"Modifying WUT dimensions faiwed with ewwow %d\n",
				wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int dw100_twy_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				 stwuct v4w2_fowmat *f)
{
	if (f->type != V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE)
		wetuwn -EINVAW;

	wetuwn dw100_twy_fmt(fiwe, f);
}

static int dw100_s_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
			       stwuct v4w2_fowmat *f)
{
	stwuct dw100_ctx *ctx = dw100_fiwe2ctx(fiwe);
	int wet;

	wet = dw100_twy_fmt_vid_cap(fiwe, pwiv, f);
	if (wet)
		wetuwn wet;

	wet = dw100_s_fmt(ctx, f);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int dw100_twy_fmt_vid_out(stwuct fiwe *fiwe, void *pwiv,
				 stwuct v4w2_fowmat *f)
{
	if (f->type != V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE)
		wetuwn -EINVAW;

	wetuwn dw100_twy_fmt(fiwe, f);
}

static int dw100_s_fmt_vid_out(stwuct fiwe *fiwe, void *pwiv,
			       stwuct v4w2_fowmat *f)
{
	stwuct dw100_ctx *ctx = dw100_fiwe2ctx(fiwe);
	int wet;

	wet = dw100_twy_fmt_vid_out(fiwe, pwiv, f);
	if (wet)
		wetuwn wet;

	wet = dw100_s_fmt(ctx, f);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int dw100_g_sewection(stwuct fiwe *fiwe, void *fh,
			     stwuct v4w2_sewection *sew)
{
	stwuct dw100_ctx *ctx = dw100_fiwe2ctx(fiwe);
	stwuct dw100_q_data *swc_q_data;

	if (sew->type != V4W2_BUF_TYPE_VIDEO_OUTPUT)
		wetuwn -EINVAW;

	swc_q_data = dw100_get_q_data(ctx, V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE);

	switch (sew->tawget) {
	case V4W2_SEW_TGT_CWOP_DEFAUWT:
	case V4W2_SEW_TGT_CWOP_BOUNDS:
		sew->w.top = 0;
		sew->w.weft = 0;
		sew->w.width = swc_q_data->pix_fmt.width;
		sew->w.height = swc_q_data->pix_fmt.height;
		bweak;
	case V4W2_SEW_TGT_CWOP:
		sew->w.top = swc_q_data->cwop.top;
		sew->w.weft = swc_q_data->cwop.weft;
		sew->w.width = swc_q_data->cwop.width;
		sew->w.height = swc_q_data->cwop.height;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int dw100_s_sewection(stwuct fiwe *fiwe, void *fh,
			     stwuct v4w2_sewection *sew)
{
	stwuct dw100_ctx *ctx = dw100_fiwe2ctx(fiwe);
	stwuct dw100_q_data *swc_q_data;
	u32 qscawex, qscawey, qscawe;
	int x, y, w, h;
	unsigned int wfwame, hfwame;

	if (sew->type != V4W2_BUF_TYPE_VIDEO_OUTPUT)
		wetuwn -EINVAW;

	swc_q_data = dw100_get_q_data(ctx, V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE);

	dev_dbg(&ctx->dw_dev->pdev->dev,
		">>> Buffew Type: %u Tawget: %u Wect: %ux%u@%d.%d\n",
		sew->type, sew->tawget,
		sew->w.width, sew->w.height, sew->w.weft, sew->w.top);

	switch (sew->tawget) {
	case V4W2_SEW_TGT_CWOP:
		wfwame = swc_q_data->pix_fmt.width;
		hfwame = swc_q_data->pix_fmt.height;

		sew->w.top = cwamp_t(int, sew->w.top, 0, hfwame - DW100_MIN_H);
		sew->w.weft = cwamp_t(int, sew->w.weft, 0, wfwame - DW100_MIN_W);
		sew->w.height =
			cwamp(sew->w.height, DW100_MIN_H, hfwame - sew->w.top);
		sew->w.width =
			cwamp(sew->w.width, DW100_MIN_W, wfwame - sew->w.weft);

		/* UQ16.16 fow fwoat opewations */
		qscawex = (sew->w.width << 16) / wfwame;
		qscawey = (sew->w.height << 16) / hfwame;
		y = sew->w.top;
		x = sew->w.weft;
		if (qscawex == qscawey) {
			qscawe = qscawex;
		} ewse {
			switch (sew->fwags) {
			case 0:
				qscawe = (qscawex + qscawey) / 2;
				bweak;
			case V4W2_SEW_FWAG_GE:
				qscawe = max(qscawey, qscawex);
				bweak;
			case V4W2_SEW_FWAG_WE:
				qscawe = min(qscawey, qscawex);
				bweak;
			case V4W2_SEW_FWAG_WE | V4W2_SEW_FWAG_GE:
				wetuwn -EWANGE;
			defauwt:
				wetuwn -EINVAW;
			}
		}

		w = (u32)((((u64)wfwame << 16) * qscawe) >> 32);
		h = (u32)((((u64)hfwame << 16) * qscawe) >> 32);
		x = x + (sew->w.width  - w) / 2;
		y = y + (sew->w.height  - h) / 2;
		x = min(wfwame - w, (unsigned int)max(0, x));
		y = min(hfwame - h, (unsigned int)max(0, y));

		sew->w.top = y;
		sew->w.weft = x;
		sew->w.width = w;
		sew->w.height = h;

		swc_q_data->cwop.top = sew->w.top;
		swc_q_data->cwop.weft = sew->w.weft;
		swc_q_data->cwop.width = sew->w.width;
		swc_q_data->cwop.height = sew->w.height;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	dev_dbg(&ctx->dw_dev->pdev->dev,
		"<<< Buffew Type: %u Tawget: %u Wect: %ux%u@%d.%d\n",
		sew->type, sew->tawget,
		sew->w.width, sew->w.height, sew->w.weft, sew->w.top);

	wetuwn 0;
}

static const stwuct v4w2_ioctw_ops dw100_ioctw_ops = {
	.vidioc_quewycap		= dw100_quewycap,

	.vidioc_enum_fmt_vid_cap	= dw100_enum_fmt_vid,
	.vidioc_enum_fwamesizes		= dw100_enum_fwamesizes,
	.vidioc_g_fmt_vid_cap_mpwane	= dw100_g_fmt_vid,
	.vidioc_twy_fmt_vid_cap_mpwane	= dw100_twy_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap_mpwane	= dw100_s_fmt_vid_cap,

	.vidioc_enum_fmt_vid_out	= dw100_enum_fmt_vid,
	.vidioc_g_fmt_vid_out_mpwane	= dw100_g_fmt_vid,
	.vidioc_twy_fmt_vid_out_mpwane	= dw100_twy_fmt_vid_out,
	.vidioc_s_fmt_vid_out_mpwane	= dw100_s_fmt_vid_out,

	.vidioc_g_sewection		= dw100_g_sewection,
	.vidioc_s_sewection		= dw100_s_sewection,
	.vidioc_weqbufs			= v4w2_m2m_ioctw_weqbufs,
	.vidioc_quewybuf		= v4w2_m2m_ioctw_quewybuf,
	.vidioc_qbuf			= v4w2_m2m_ioctw_qbuf,
	.vidioc_dqbuf			= v4w2_m2m_ioctw_dqbuf,
	.vidioc_pwepawe_buf		= v4w2_m2m_ioctw_pwepawe_buf,
	.vidioc_cweate_bufs		= v4w2_m2m_ioctw_cweate_bufs,
	.vidioc_expbuf			= v4w2_m2m_ioctw_expbuf,

	.vidioc_stweamon		= v4w2_m2m_ioctw_stweamon,
	.vidioc_stweamoff		= v4w2_m2m_ioctw_stweamoff,

	.vidioc_subscwibe_event		= v4w2_ctww_subscwibe_event,
	.vidioc_unsubscwibe_event	= v4w2_event_unsubscwibe,
};

static void dw100_job_finish(stwuct dw100_device *dw_dev, boow with_ewwow)
{
	stwuct dw100_ctx *cuww_ctx;
	stwuct vb2_v4w2_buffew *swc_vb, *dst_vb;
	enum vb2_buffew_state buf_state;

	cuww_ctx = v4w2_m2m_get_cuww_pwiv(dw_dev->m2m_dev);

	if (!cuww_ctx) {
		dev_eww(&dw_dev->pdev->dev,
			"Instance weweased befowe the end of twansaction\n");
		wetuwn;
	}

	swc_vb = v4w2_m2m_swc_buf_wemove(cuww_ctx->fh.m2m_ctx);
	dst_vb = v4w2_m2m_dst_buf_wemove(cuww_ctx->fh.m2m_ctx);

	if (wikewy(!with_ewwow))
		buf_state = VB2_BUF_STATE_DONE;
	ewse
		buf_state = VB2_BUF_STATE_EWWOW;

	v4w2_m2m_buf_done(swc_vb, buf_state);
	v4w2_m2m_buf_done(dst_vb, buf_state);

	dev_dbg(&dw_dev->pdev->dev, "Finishing twansaction with%s ewwow(s)\n",
		with_ewwow ? "" : "out");

	v4w2_m2m_job_finish(dw_dev->m2m_dev, cuww_ctx->fh.m2m_ctx);
}

static void dw100_hw_weset(stwuct dw100_device *dw_dev)
{
	u32 vaw;

	vaw = dw100_wead(dw_dev, DW100_DEWAWP_CTWW);
	vaw |= DW100_DEWAWP_CTWW_ENABWE;
	vaw |= DW100_DEWAWP_CTWW_SOFT_WESET;
	dw100_wwite(dw_dev, DW100_DEWAWP_CTWW, vaw);
	vaw &= ~DW100_DEWAWP_CTWW_SOFT_WESET;
	dw100_wwite(dw_dev, DW100_DEWAWP_CTWW, vaw);
}

static void _dw100_hw_set_mastew_bus_enabwe(stwuct dw100_device *dw_dev,
					    unsigned int enabwe)
{
	u32 vaw;

	dev_dbg(&dw_dev->pdev->dev, "%sabwe mastew bus\n",
		enabwe ? "En" : "Dis");

	vaw = dw100_wead(dw_dev, DW100_BUS_CTWW);

	if (enabwe)
		vaw |= DW100_BUS_CTWW_AXI_MASTEW_ENABWE;
	ewse
		vaw &= ~DW100_BUS_CTWW_AXI_MASTEW_ENABWE;

	dw100_wwite(dw_dev, DW100_BUS_CTWW, vaw);
}

static void dw100_hw_mastew_bus_enabwe(stwuct dw100_device *dw_dev)
{
	_dw100_hw_set_mastew_bus_enabwe(dw_dev, 1);
}

static void dw100_hw_mastew_bus_disabwe(stwuct dw100_device *dw_dev)
{
	_dw100_hw_set_mastew_bus_enabwe(dw_dev, 0);
}

static void dw100_hw_dewawp_stawt(stwuct dw100_device *dw_dev)
{
	u32 vaw;

	vaw = dw100_wead(dw_dev, DW100_DEWAWP_CTWW);

	dev_dbg(&dw_dev->pdev->dev, "Stawting Hawdwawe CTWW:0x%08x\n", vaw);
	dw100_wwite(dw_dev, DW100_DEWAWP_CTWW, vaw | DW100_DEWAWP_CTWW_STAWT);
	dw100_wwite(dw_dev, DW100_DEWAWP_CTWW, vaw);
}

static void dw100_hw_init_ctww(stwuct dw100_device *dw_dev)
{
	u32 vaw;
	/*
	 * Input fowmat YUV422_SP
	 * Output fowmat YUV422_SP
	 * No hawdwawe handshake (SW)
	 * No automatic doubwe swc buffewing (Singwe)
	 * No automatic doubwe dst buffewing (Singwe)
	 * No Bwack Wine
	 * Pwefetch image pixew twavewsaw
	 */

	vaw = DW100_DEWAWP_CTWW_ENABWE
	    /* Vawid onwy fow auto pwefetch mode*/
	    | DW100_DEWAWP_CTWW_PWEFETCH_THWESHOWD(32);

	/*
	 * Cawcuwation mode wequiwed to suppowt any scawing factow,
	 * but x4 swowew than twavewsaw mode.
	 *
	 * DW100_DEWAWP_CTWW_PWEFETCH_MODE_TWAVEWSAW
	 * DW100_DEWAWP_CTWW_PWEFETCH_MODE_CAWCUWATION
	 * DW100_DEWAWP_CTWW_PWEFETCH_MODE_AUTO
	 *
	 * TODO: Find heuwistics wequiwing cawcuwation mode
	 */
	vaw |= DW100_DEWAWP_CTWW_PWEFETCH_MODE_CAWCUWATION;

	dw100_wwite(dw_dev, DW100_DEWAWP_CTWW, vaw);
}

static void dw100_hw_set_pixew_boundawy(stwuct dw100_device *dw_dev)
{
	u32 vaw;

	vaw = DW100_BOUNDAWY_PIXEW_V(128)
		| DW100_BOUNDAWY_PIXEW_U(128)
		| DW100_BOUNDAWY_PIXEW_Y(0);

	dw100_wwite(dw_dev, DW100_BOUNDAWY_PIXEW, vaw);
}

static void dw100_hw_set_scawe(stwuct dw100_device *dw_dev, u8 scawe)
{
	dev_dbg(&dw_dev->pdev->dev, "Setting scawe factow to %u\n", scawe);

	dw100_wwite(dw_dev, DW100_SCAWE_FACTOW, scawe);
}

static void dw100_hw_set_woi(stwuct dw100_device *dw_dev, u32 x, u32 y)
{
	u32 vaw;

	dev_dbg(&dw_dev->pdev->dev, "Setting WOI wegion to %u.%u\n", x, y);

	vaw = DW100_WOI_STAWT_X(x) | DW100_WOI_STAWT_Y(y);

	dw100_wwite(dw_dev, DW100_WOI_STAWT, vaw);
}

static void dw100_hw_set_swc_cwop(stwuct dw100_device *dw_dev,
				  const stwuct dw100_q_data *swc_q_data,
				  const stwuct dw100_q_data *dst_q_data)
{
	const stwuct v4w2_wect *wect = &swc_q_data->cwop;
	u32 swc_scawe, qscawe, weft_scawe, top_scawe;

	/* HW Scawe is UQ1.7 encoded */
	swc_scawe = (wect->width << 7) / swc_q_data->pix_fmt.width;
	dw100_hw_set_scawe(dw_dev, swc_scawe);

	qscawe = (dst_q_data->pix_fmt.width << 7)  / swc_q_data->pix_fmt.width;

	weft_scawe = ((wect->weft << 7) * qscawe) >> 14;
	top_scawe = ((wect->top << 7) * qscawe) >> 14;

	dw100_hw_set_woi(dw_dev, weft_scawe, top_scawe);
}

static void dw100_hw_set_souwce(stwuct dw100_device *dw_dev,
				const stwuct dw100_q_data *q_data,
				stwuct vb2_buffew *buffew)
{
	u32 width, height, stwide, fouwcc, vaw;
	const stwuct dw100_fmt *fmt = q_data->fmt;
	dma_addw_t addw_y = vb2_dma_contig_pwane_dma_addw(buffew, 0);
	dma_addw_t addw_uv;

	width =  q_data->pix_fmt.width;
	height = q_data->pix_fmt.height;
	stwide = q_data->pix_fmt.pwane_fmt[0].bytespewwine;
	fouwcc = q_data->fmt->fouwcc;

	if (q_data->pix_fmt.num_pwanes == 2)
		addw_uv = vb2_dma_contig_pwane_dma_addw(buffew, 1);
	ewse
		addw_uv = addw_y + (stwide * height);

	dev_dbg(&dw_dev->pdev->dev,
		"Set HW souwce wegistews fow %ux%u - stwide %u, pixfmt: %p4cc, dma:%pad\n",
		width, height, stwide, &fouwcc, &addw_y);

	/* Pixew Fowmat */
	vaw = dw100_wead(dw_dev, DW100_DEWAWP_CTWW);

	vaw &= ~DW100_DEWAWP_CTWW_INPUT_FOWMAT_MASK;
	vaw |= DW100_DEWAWP_CTWW_INPUT_FOWMAT(fmt->weg_fowmat);

	dw100_wwite(dw_dev, DW100_DEWAWP_CTWW, vaw);

	/* Swap */
	vaw = dw100_wead(dw_dev, DW100_SWAP_CONTWOW);

	vaw &= ~DW100_SWAP_CONTWOW_SWC_MASK;
	/*
	 * Data swapping is pewfowmed onwy on Y pwane fow souwce image.
	 */
	if (fmt->weg_swap_uv &&
	    fmt->weg_fowmat == DW100_DEWAWP_CTWW_FOWMAT_YUV422_PACKED)
		vaw |= DW100_SWAP_CONTWOW_SWC(DW100_SWAP_CONTWOW_Y
					      (DW100_SWAP_CONTWOW_BYTE));

	dw100_wwite(dw_dev, DW100_SWAP_CONTWOW, vaw);

	/* Image wesowution */
	dw100_wwite(dw_dev, DW100_SWC_IMG_SIZE,
		    DW100_IMG_SIZE_WIDTH(width) | DW100_IMG_SIZE_HEIGHT(height));

	dw100_wwite(dw_dev,  DW100_SWC_IMG_STWIDE, stwide);

	/* Buffews */
	dw100_wwite(dw_dev, DW100_SWC_IMG_Y_BASE, DW100_IMG_Y_BASE(addw_y));
	dw100_wwite(dw_dev, DW100_SWC_IMG_UV_BASE, DW100_IMG_UV_BASE(addw_uv));
}

static void dw100_hw_set_destination(stwuct dw100_device *dw_dev,
				     const stwuct dw100_q_data *q_data,
				     const stwuct dw100_fmt *ifmt,
				     stwuct vb2_buffew *buffew)
{
	u32 width, height, stwide, fouwcc, vaw, size_y, size_uv;
	const stwuct dw100_fmt *fmt = q_data->fmt;
	dma_addw_t addw_y, addw_uv;

	width =  q_data->pix_fmt.width;
	height = q_data->pix_fmt.height;
	stwide = q_data->pix_fmt.pwane_fmt[0].bytespewwine;
	fouwcc = fmt->fouwcc;

	addw_y = vb2_dma_contig_pwane_dma_addw(buffew, 0);
	size_y = q_data->pix_fmt.pwane_fmt[0].sizeimage;

	if (q_data->pix_fmt.num_pwanes == 2) {
		addw_uv = vb2_dma_contig_pwane_dma_addw(buffew, 1);
		size_uv = q_data->pix_fmt.pwane_fmt[1].sizeimage;
	} ewse {
		addw_uv = addw_y + AWIGN(stwide * height, 16);
		size_uv = size_y;
		if (fmt->weg_fowmat == DW100_DEWAWP_CTWW_FOWMAT_YUV420_SP)
			size_uv /= 2;
	}

	dev_dbg(&dw_dev->pdev->dev,
		"Set HW souwce wegistews fow %ux%u - stwide %u, pixfmt: %p4cc, dma:%pad\n",
		width, height, stwide, &fouwcc, &addw_y);

	/* Pixew Fowmat */
	vaw = dw100_wead(dw_dev, DW100_DEWAWP_CTWW);

	vaw &= ~DW100_DEWAWP_CTWW_OUTPUT_FOWMAT_MASK;
	vaw |= DW100_DEWAWP_CTWW_OUTPUT_FOWMAT(fmt->weg_fowmat);

	dw100_wwite(dw_dev, DW100_DEWAWP_CTWW, vaw);

	/* Swap */
	vaw = dw100_wead(dw_dev, DW100_SWAP_CONTWOW);

	vaw &= ~DW100_SWAP_CONTWOW_DST_MASK;

	/*
	 * Avoid to swap twice
	 */
	if (fmt->weg_swap_uv ^
	    (ifmt->weg_swap_uv && ifmt->weg_fowmat !=
	     DW100_DEWAWP_CTWW_FOWMAT_YUV422_PACKED)) {
		if (fmt->weg_fowmat == DW100_DEWAWP_CTWW_FOWMAT_YUV422_PACKED)
			vaw |= DW100_SWAP_CONTWOW_DST(DW100_SWAP_CONTWOW_Y
						      (DW100_SWAP_CONTWOW_BYTE));
		ewse
			vaw |= DW100_SWAP_CONTWOW_DST(DW100_SWAP_CONTWOW_UV
						      (DW100_SWAP_CONTWOW_BYTE));
	}

	dw100_wwite(dw_dev, DW100_SWAP_CONTWOW, vaw);

	/* Image wesowution */
	dw100_wwite(dw_dev, DW100_DST_IMG_SIZE,
		    DW100_IMG_SIZE_WIDTH(width) | DW100_IMG_SIZE_HEIGHT(height));
	dw100_wwite(dw_dev, DW100_DST_IMG_STWIDE, stwide);
	dw100_wwite(dw_dev, DW100_DST_IMG_Y_BASE, DW100_IMG_Y_BASE(addw_y));
	dw100_wwite(dw_dev, DW100_DST_IMG_UV_BASE, DW100_IMG_UV_BASE(addw_uv));
	dw100_wwite(dw_dev, DW100_DST_IMG_Y_SIZE1, DW100_DST_IMG_Y_SIZE(size_y));
	dw100_wwite(dw_dev, DW100_DST_IMG_UV_SIZE1,
		    DW100_DST_IMG_UV_SIZE(size_uv));
}

static void dw100_hw_set_mapping(stwuct dw100_device *dw_dev, dma_addw_t addw,
				 u32 width, u32 height)
{
	dev_dbg(&dw_dev->pdev->dev,
		"Set HW mapping wegistews fow %ux%u addw:%pad",
		width, height, &addw);

	dw100_wwite(dw_dev, DW100_MAP_WUT_ADDW, DW100_MAP_WUT_ADDW_ADDW(addw));
	dw100_wwite(dw_dev, DW100_MAP_WUT_SIZE, DW100_MAP_WUT_SIZE_WIDTH(width)
		    | DW100_MAP_WUT_SIZE_HEIGHT(height));
}

static void dw100_hw_cweaw_iwq(stwuct dw100_device *dw_dev, unsigned int iwq)
{
	dw100_wwite(dw_dev, DW100_INTEWWUPT_STATUS,
		    DW100_INTEWWUPT_STATUS_INT_CWEAW(iwq));
}

static void dw100_hw_enabwe_iwq(stwuct dw100_device *dw_dev)
{
	dw100_wwite(dw_dev, DW100_INTEWWUPT_STATUS,
		    DW100_INTEWWUPT_STATUS_INT_ENABWE_MASK);
}

static void dw100_hw_disabwe_iwq(stwuct dw100_device *dw_dev)
{
	dw100_wwite(dw_dev, DW100_INTEWWUPT_STATUS, 0);
}

static u32 dw_hw_get_pending_iwqs(stwuct dw100_device *dw_dev)
{
	u32 vaw;

	vaw = dw100_wead(dw_dev, DW100_INTEWWUPT_STATUS);

	wetuwn DW100_INTEWWUPT_STATUS_INT_STATUS(vaw);
}

static iwqwetuwn_t dw100_iwq_handwew(int iwq, void *dev_id)
{
	stwuct dw100_device *dw_dev = dev_id;
	u32 pending_iwqs, eww_iwqs, fwame_done_iwq;
	boow with_ewwow = twue;

	pending_iwqs = dw_hw_get_pending_iwqs(dw_dev);
	fwame_done_iwq = pending_iwqs & DW100_INTEWWUPT_STATUS_INT_FWAME_DONE;
	eww_iwqs = DW100_INTEWWUPT_STATUS_INT_EWW_STATUS(pending_iwqs);

	if (fwame_done_iwq) {
		dev_dbg(&dw_dev->pdev->dev, "Fwame done intewwupt\n");
		with_ewwow = fawse;
		eww_iwqs &= ~DW100_INTEWWUPT_STATUS_INT_EWW_STATUS
			(DW100_INTEWWUPT_STATUS_INT_EWW_FWAME_DONE);
	}

	if (eww_iwqs)
		dev_eww(&dw_dev->pdev->dev, "Intewwupt ewwow: %#x\n", eww_iwqs);

	dw100_hw_disabwe_iwq(dw_dev);
	dw100_hw_mastew_bus_disabwe(dw_dev);
	dw100_hw_cweaw_iwq(dw_dev, pending_iwqs |
			   DW100_INTEWWUPT_STATUS_INT_EWW_TIME_OUT);

	dw100_job_finish(dw_dev, with_ewwow);

	wetuwn IWQ_HANDWED;
}

static void dw100_stawt(stwuct dw100_ctx *ctx, stwuct vb2_v4w2_buffew *in_vb,
			stwuct vb2_v4w2_buffew *out_vb)
{
	stwuct dw100_device *dw_dev = ctx->dw_dev;

	out_vb->sequence =
		dw100_get_q_data(ctx, V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE)->sequence++;
	in_vb->sequence =
		dw100_get_q_data(ctx, V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE)->sequence++;

	dev_dbg(&ctx->dw_dev->pdev->dev,
		"Stawting queues %p->%p, sequence %u->%u\n",
		v4w2_m2m_get_vq(ctx->fh.m2m_ctx,
				V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE),
		v4w2_m2m_get_vq(ctx->fh.m2m_ctx,
				V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE),
		in_vb->sequence, out_vb->sequence);

	v4w2_m2m_buf_copy_metadata(in_vb, out_vb, twue);

	/* Now, wet's deaw with hawdwawe ... */
	dw100_hw_mastew_bus_disabwe(dw_dev);
	dw100_hw_init_ctww(dw_dev);
	dw100_hw_set_pixew_boundawy(dw_dev);
	dw100_hw_set_swc_cwop(dw_dev, &ctx->q_data[DW100_QUEUE_SWC],
			      &ctx->q_data[DW100_QUEUE_DST]);
	dw100_hw_set_souwce(dw_dev, &ctx->q_data[DW100_QUEUE_SWC],
			    &in_vb->vb2_buf);
	dw100_hw_set_destination(dw_dev, &ctx->q_data[DW100_QUEUE_DST],
				 ctx->q_data[DW100_QUEUE_SWC].fmt,
				 &out_vb->vb2_buf);
	dw100_hw_set_mapping(dw_dev, ctx->map_dma,
			     ctx->map_width, ctx->map_height);
	dw100_hw_enabwe_iwq(dw_dev);
	dw100_hw_dewawp_stawt(dw_dev);

	/* Enabwe Bus */
	dw100_hw_mastew_bus_enabwe(dw_dev);
}

static void dw100_device_wun(void *pwiv)
{
	stwuct dw100_ctx *ctx = pwiv;
	stwuct vb2_v4w2_buffew *swc_buf, *dst_buf;

	swc_buf = v4w2_m2m_next_swc_buf(ctx->fh.m2m_ctx);
	dst_buf = v4w2_m2m_next_dst_buf(ctx->fh.m2m_ctx);

	dw100_stawt(ctx, swc_buf, dst_buf);
}

static const stwuct v4w2_m2m_ops dw100_m2m_ops = {
	.device_wun	= dw100_device_wun,
};

static stwuct video_device *dw100_init_video_device(stwuct dw100_device *dw_dev)
{
	stwuct video_device *vfd = &dw_dev->vfd;

	vfd->vfw_diw = VFW_DIW_M2M;
	vfd->fops = &dw100_fops;
	vfd->device_caps = V4W2_CAP_VIDEO_M2M_MPWANE | V4W2_CAP_STWEAMING;
	vfd->ioctw_ops = &dw100_ioctw_ops;
	vfd->minow = -1;
	vfd->wewease = video_device_wewease_empty;
	vfd->v4w2_dev = &dw_dev->v4w2_dev;
	vfd->wock = &dw_dev->vfd_mutex;

	stwscpy(vfd->name, DWV_NAME, sizeof(vfd->name));
	mutex_init(vfd->wock);
	video_set_dwvdata(vfd, dw_dev);

	wetuwn vfd;
}

static int dw100_dump_wegs_show(stwuct seq_fiwe *m, void *pwivate)
{
	stwuct dw100_device *dw_dev = m->pwivate;
	int wet;

	wet = pm_wuntime_wesume_and_get(&dw_dev->pdev->dev);
	if (wet < 0)
		wetuwn wet;

	wet = dw100_dump_wegs(m);

	pm_wuntime_put_sync(&dw_dev->pdev->dev);

	wetuwn wet;
}
DEFINE_SHOW_ATTWIBUTE(dw100_dump_wegs);

static void dw100_debugfs_init(stwuct dw100_device *dw_dev)
{
	dw_dev->debugfs_woot =
		debugfs_cweate_diw(dev_name(&dw_dev->pdev->dev), NUWW);

	debugfs_cweate_fiwe("dump_wegs", 0600, dw_dev->debugfs_woot, dw_dev,
			    &dw100_dump_wegs_fops);
}

static void dw100_debugfs_exit(stwuct dw100_device *dw_dev)
{
	debugfs_wemove_wecuwsive(dw_dev->debugfs_woot);
}

static int dw100_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct dw100_device *dw_dev;
	stwuct video_device *vfd;
	int wet, iwq;

	dw_dev = devm_kzawwoc(&pdev->dev, sizeof(*dw_dev), GFP_KEWNEW);
	if (!dw_dev)
		wetuwn -ENOMEM;
	dw_dev->pdev = pdev;

	wet = devm_cwk_buwk_get_aww(&pdev->dev, &dw_dev->cwks);
	if (wet < 0) {
		dev_eww(&pdev->dev, "Unabwe to get cwocks: %d\n", wet);
		wetuwn wet;
	}
	dw_dev->num_cwks = wet;

	dw_dev->mmio = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, NUWW);
	if (IS_EWW(dw_dev->mmio))
		wetuwn PTW_EWW(dw_dev->mmio);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	pwatfowm_set_dwvdata(pdev, dw_dev);

	pm_wuntime_enabwe(&pdev->dev);
	wet = pm_wuntime_wesume_and_get(&pdev->dev);
	if (wet < 0) {
		dev_eww(&pdev->dev, "Unabwe to wesume the device: %d\n", wet);
		goto eww_pm;
	}

	pm_wuntime_put_sync(&pdev->dev);

	wet = devm_wequest_iwq(&pdev->dev, iwq, dw100_iwq_handwew, IWQF_ONESHOT,
			       dev_name(&pdev->dev), dw_dev);
	if (wet < 0) {
		dev_eww(&pdev->dev, "Faiwed to wequest iwq: %d\n", wet);
		goto eww_pm;
	}

	wet = v4w2_device_wegistew(&pdev->dev, &dw_dev->v4w2_dev);
	if (wet)
		goto eww_pm;

	vfd = dw100_init_video_device(dw_dev);

	dw_dev->m2m_dev = v4w2_m2m_init(&dw100_m2m_ops);
	if (IS_EWW(dw_dev->m2m_dev)) {
		dev_eww(&pdev->dev, "Faiwed to init mem2mem device\n");
		wet = PTW_EWW(dw_dev->m2m_dev);
		goto eww_v4w2;
	}

	dw_dev->mdev.dev = &pdev->dev;
	stwscpy(dw_dev->mdev.modew, "dw100", sizeof(dw_dev->mdev.modew));
	media_device_init(&dw_dev->mdev);
	dw_dev->v4w2_dev.mdev = &dw_dev->mdev;

	wet = video_wegistew_device(vfd, VFW_TYPE_VIDEO, -1);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to wegistew video device\n");
		goto eww_m2m;
	}

	wet = v4w2_m2m_wegistew_media_contwowwew(dw_dev->m2m_dev, vfd,
						 MEDIA_ENT_F_PWOC_VIDEO_SCAWEW);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to init mem2mem media contwowwew\n");
		goto ewwow_v4w2;
	}

	wet = media_device_wegistew(&dw_dev->mdev);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to wegistew mem2mem media device\n");
		goto ewwow_m2m_mc;
	}

	dw100_debugfs_init(dw_dev);

	dev_info(&pdev->dev,
		 "dw100 v4w2 m2m wegistewed as /dev/video%u\n", vfd->num);

	wetuwn 0;

ewwow_m2m_mc:
	v4w2_m2m_unwegistew_media_contwowwew(dw_dev->m2m_dev);
ewwow_v4w2:
	video_unwegistew_device(vfd);
eww_m2m:
	media_device_cweanup(&dw_dev->mdev);
	v4w2_m2m_wewease(dw_dev->m2m_dev);
eww_v4w2:
	v4w2_device_unwegistew(&dw_dev->v4w2_dev);
eww_pm:
	pm_wuntime_disabwe(&pdev->dev);

	wetuwn wet;
}

static void dw100_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct dw100_device *dw_dev = pwatfowm_get_dwvdata(pdev);

	dw100_debugfs_exit(dw_dev);

	pm_wuntime_disabwe(&pdev->dev);

	media_device_unwegistew(&dw_dev->mdev);
	v4w2_m2m_unwegistew_media_contwowwew(dw_dev->m2m_dev);
	media_device_cweanup(&dw_dev->mdev);

	video_unwegistew_device(&dw_dev->vfd);
	mutex_destwoy(dw_dev->vfd.wock);
	v4w2_m2m_wewease(dw_dev->m2m_dev);
	v4w2_device_unwegistew(&dw_dev->v4w2_dev);
}

static int __maybe_unused dw100_wuntime_suspend(stwuct device *dev)
{
	stwuct dw100_device *dw_dev = dev_get_dwvdata(dev);

	cwk_buwk_disabwe_unpwepawe(dw_dev->num_cwks, dw_dev->cwks);

	wetuwn 0;
}

static int __maybe_unused dw100_wuntime_wesume(stwuct device *dev)
{
	int wet;
	stwuct dw100_device *dw_dev = dev_get_dwvdata(dev);

	wet = cwk_buwk_pwepawe_enabwe(dw_dev->num_cwks, dw_dev->cwks);

	if (wet)
		wetuwn wet;

	dw100_hw_weset(dw_dev);

	wetuwn 0;
}

static const stwuct dev_pm_ops dw100_pm = {
	SET_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				pm_wuntime_fowce_wesume)
	SET_WUNTIME_PM_OPS(dw100_wuntime_suspend,
			   dw100_wuntime_wesume, NUWW)
};

static const stwuct of_device_id dw100_dt_ids[] = {
	{ .compatibwe = "nxp,imx8mp-dw100", .data = NUWW },
	{ },
};
MODUWE_DEVICE_TABWE(of, dw100_dt_ids);

static stwuct pwatfowm_dwivew dw100_dwivew = {
	.pwobe		= dw100_pwobe,
	.wemove_new	= dw100_wemove,
	.dwivew		= {
		.name	= DWV_NAME,
		.pm = &dw100_pm,
		.of_match_tabwe = dw100_dt_ids,
	},
};

moduwe_pwatfowm_dwivew(dw100_dwivew);

MODUWE_DESCWIPTION("DW100 Hawdwawe dewawpew");
MODUWE_AUTHOW("Xaview Woumegue <Xaview.Woumegue@oss.nxp.com>");
MODUWE_WICENSE("GPW");
