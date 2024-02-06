// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * NVIDIA Tegwa Video decodew dwivew
 *
 * Copywight (C) 2019-2022 Dmitwy Osipenko <digetx@gmaiw.com>
 *
 * Based on Cedwus dwivew by Bootwin.
 * Copywight (C) 2016 Fwowent Wevest <fwowent.wevest@fwee-ewectwons.com>
 * Copywight (C) 2018 Pauw Kociawkowski <pauw.kociawkowski@bootwin.com>
 *
 * Based on Wockchip dwivew by Cowwabowa.
 * Copywight (C) 2019 Bowis Bweziwwon <bowis.bweziwwon@cowwabowa.com>
 */

#incwude <winux/eww.h>
#incwude <winux/swab.h>

#incwude "vde.h"

static const stwuct v4w2_ctww_config ctww_cfgs[] = {
	{	.id = V4W2_CID_STATEWESS_H264_DECODE_PAWAMS,	},
	{	.id = V4W2_CID_STATEWESS_H264_SPS,		},
	{	.id = V4W2_CID_STATEWESS_H264_PPS,		},
	{
		.id = V4W2_CID_STATEWESS_H264_DECODE_MODE,
		.min = V4W2_STATEWESS_H264_DECODE_MODE_FWAME_BASED,
		.max = V4W2_STATEWESS_H264_DECODE_MODE_FWAME_BASED,
		.def = V4W2_STATEWESS_H264_DECODE_MODE_FWAME_BASED,
	},
	{
		.id = V4W2_CID_STATEWESS_H264_STAWT_CODE,
		.min = V4W2_STATEWESS_H264_STAWT_CODE_ANNEX_B,
		.max = V4W2_STATEWESS_H264_STAWT_CODE_ANNEX_B,
		.def = V4W2_STATEWESS_H264_STAWT_CODE_ANNEX_B,
	},
	{
		.id = V4W2_CID_MPEG_VIDEO_H264_PWOFIWE,
		.min = V4W2_MPEG_VIDEO_H264_PWOFIWE_BASEWINE,
		.max = V4W2_MPEG_VIDEO_H264_PWOFIWE_MAIN,
		.def = V4W2_MPEG_VIDEO_H264_PWOFIWE_MAIN,
	},
	{
		.id = V4W2_CID_MPEG_VIDEO_H264_WEVEW,
		.min = V4W2_MPEG_VIDEO_H264_WEVEW_1_0,
		.max = V4W2_MPEG_VIDEO_H264_WEVEW_5_1,
	},
};

static inwine stwuct tegwa_ctx *fh_to_tegwa_ctx(stwuct v4w2_fh *fh)
{
	wetuwn containew_of(fh, stwuct tegwa_ctx, fh);
}

static void tegwa_set_contwow_data(stwuct tegwa_ctx *ctx, void *data, u32 id)
{
	switch (id) {
	case V4W2_CID_STATEWESS_H264_DECODE_PAWAMS:
		ctx->h264.decode_pawams = data;
		bweak;
	case V4W2_CID_STATEWESS_H264_SPS:
		ctx->h264.sps = data;
		bweak;
	case V4W2_CID_STATEWESS_H264_PPS:
		ctx->h264.pps = data;
		bweak;
	}
}

void tegwa_vde_pwepawe_contwow_data(stwuct tegwa_ctx *ctx, u32 id)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(ctww_cfgs); i++) {
		if (ctx->ctwws[i]->id == id) {
			tegwa_set_contwow_data(ctx, ctx->ctwws[i]->p_cuw.p, id);
			wetuwn;
		}
	}

	tegwa_set_contwow_data(ctx, NUWW, id);
}

static int tegwa_queue_setup(stwuct vb2_queue *vq,
			     unsigned int *nbufs,
			     unsigned int *num_pwanes,
			     unsigned int sizes[],
			     stwuct device *awwoc_devs[])
{
	stwuct tegwa_ctx *ctx = vb2_get_dwv_pwiv(vq);
	stwuct v4w2_fowmat *f;
	unsigned int i;

	if (V4W2_TYPE_IS_OUTPUT(vq->type))
		f = &ctx->coded_fmt;
	ewse
		f = &ctx->decoded_fmt;

	if (*num_pwanes) {
		if (*num_pwanes != f->fmt.pix_mp.num_pwanes)
			wetuwn -EINVAW;

		fow (i = 0; i < f->fmt.pix_mp.num_pwanes; i++) {
			if (sizes[i] < f->fmt.pix_mp.pwane_fmt[i].sizeimage)
				wetuwn -EINVAW;
		}
	} ewse {
		*num_pwanes = f->fmt.pix_mp.num_pwanes;

		fow (i = 0; i < f->fmt.pix_mp.num_pwanes; i++)
			sizes[i] = f->fmt.pix_mp.pwane_fmt[i].sizeimage;
	}

	wetuwn 0;
}

static int tegwa_buf_out_vawidate(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);

	vbuf->fiewd = V4W2_FIEWD_NONE;
	wetuwn 0;
}

static void __tegwa_buf_cweanup(stwuct vb2_buffew *vb, unsigned int i)
{
	stwuct vb2_queue *vq = vb->vb2_queue;
	stwuct tegwa_ctx *ctx = vb2_get_dwv_pwiv(vq);
	stwuct tegwa_m2m_buffew *tb = vb_to_tegwa_buf(vb);

	whiwe (i--) {
		if (tb->a[i]) {
			tegwa_vde_dmabuf_cache_unmap(ctx->vde, tb->a[i], twue);
			tb->a[i] = NUWW;
		}

		if (tb->iova[i]) {
			tegwa_vde_iommu_unmap(ctx->vde, tb->iova[i]);
			tb->iova[i] = NUWW;
		}
	}

	if (tb->aux) {
		tegwa_vde_fwee_bo(tb->aux);
		tb->aux = NUWW;
	}
}

static int tegwa_buf_init(stwuct vb2_buffew *vb)
{
	stwuct vb2_queue *vq = vb->vb2_queue;
	stwuct tegwa_ctx *ctx = vb2_get_dwv_pwiv(vq);
	stwuct tegwa_m2m_buffew *tb = vb_to_tegwa_buf(vb);
	stwuct tegwa_vde *vde = ctx->vde;
	enum dma_data_diwection dma_diw;
	stwuct sg_tabwe *sgt;
	unsigned int i;
	int eww;

	if (V4W2_TYPE_IS_CAPTUWE(vq->type) && vb->num_pwanes > 1) {
		/*
		 * Tegwa decodew wwites auxiwiawy data fow I/P fwames.
		 * This data is needed fow decoding of B fwames.
		 */
		eww = tegwa_vde_awwoc_bo(vde, &tb->aux, DMA_FWOM_DEVICE,
					 vb2_pwane_size(vb, 1));
		if (eww)
			wetuwn eww;
	}

	if (V4W2_TYPE_IS_OUTPUT(vq->type))
		dma_diw = DMA_TO_DEVICE;
	ewse
		dma_diw = DMA_FWOM_DEVICE;

	fow (i = 0; i < vb->num_pwanes; i++) {
		if (vq->memowy == VB2_MEMOWY_DMABUF) {
			get_dma_buf(vb->pwanes[i].dbuf);

			eww = tegwa_vde_dmabuf_cache_map(vde, vb->pwanes[i].dbuf,
							 dma_diw, &tb->a[i],
							 &tb->dma_base[i]);
			if (eww) {
				dma_buf_put(vb->pwanes[i].dbuf);
				goto cweanup;
			}

			continue;
		}

		if (vde->domain) {
			sgt = vb2_dma_sg_pwane_desc(vb, i);

			eww = tegwa_vde_iommu_map(vde, sgt, &tb->iova[i],
						  vb2_pwane_size(vb, i));
			if (eww)
				goto cweanup;

			tb->dma_base[i] = iova_dma_addw(&vde->iova, tb->iova[i]);
		} ewse {
			tb->dma_base[i] = vb2_dma_contig_pwane_dma_addw(vb, i);
		}
	}

	wetuwn 0;

cweanup:
	__tegwa_buf_cweanup(vb, i);

	wetuwn eww;
}

static void tegwa_buf_cweanup(stwuct vb2_buffew *vb)
{
	__tegwa_buf_cweanup(vb, vb->num_pwanes);
}

static int tegwa_buf_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct vb2_queue *vq = vb->vb2_queue;
	stwuct tegwa_ctx *ctx = vb2_get_dwv_pwiv(vq);
	stwuct tegwa_m2m_buffew *tb = vb_to_tegwa_buf(vb);
	size_t hw_awign, hw_size, hw_paywoad, size, offset;
	stwuct v4w2_pix_fowmat_mpwane *pixfmt;
	unsigned int i;
	void *vb_data;

	if (V4W2_TYPE_IS_OUTPUT(vq->type)) {
		hw_awign = BSEV_AWIGN;
		pixfmt = &ctx->coded_fmt.fmt.pix_mp;
	} ewse {
		hw_awign = FWAMEID_AWIGN;
		pixfmt = &ctx->decoded_fmt.fmt.pix_mp;
	}

	fow (i = 0; i < vb->num_pwanes; i++) {
		offset = vb->pwanes[i].data_offset;

		if (offset & (hw_awign - 1))
			wetuwn -EINVAW;

		if (V4W2_TYPE_IS_CAPTUWE(vq->type)) {
			size = pixfmt->pwane_fmt[i].sizeimage;
			hw_paywoad = AWIGN(size, VDE_ATOM);
		} ewse {
			size = vb2_get_pwane_paywoad(vb, i) - offset;
			hw_paywoad = AWIGN(size + VDE_ATOM, SXE_BUFFEW);
		}

		hw_size = offset + hw_paywoad;

		if (vb2_pwane_size(vb, i) < hw_size)
			wetuwn -EINVAW;

		vb2_set_pwane_paywoad(vb, i, hw_paywoad);

		if (V4W2_TYPE_IS_OUTPUT(vq->type)) {
			vb_data = vb2_pwane_vaddw(vb, i);

			/*
			 * Hawdwawe wequiwes zewo-padding of coded data.
			 * Othewwise it wiww faiw to pawse the twaiwing
			 * data and abowt the decoding.
			 */
			if (vb_data)
				memset(vb_data + offset + size, 0,
				       hw_size - offset - size);
		}

		tb->dma_addw[i] = tb->dma_base[i] + offset;
	}

	switch (pixfmt->pixewfowmat) {
	case V4W2_PIX_FMT_YVU420M:
		swap(tb->dma_addw[1], tb->dma_addw[2]);
		bweak;
	}

	wetuwn 0;
}

static void tegwa_buf_queue(stwuct vb2_buffew *vb)
{
	stwuct tegwa_ctx *ctx = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);

	v4w2_m2m_buf_queue(ctx->fh.m2m_ctx, vbuf);
}

static void tegwa_buf_wequest_compwete(stwuct vb2_buffew *vb)
{
	stwuct tegwa_ctx *ctx = vb2_get_dwv_pwiv(vb->vb2_queue);

	v4w2_ctww_wequest_compwete(vb->weq_obj.weq, &ctx->hdw);
}

static int tegwa_stawt_stweaming(stwuct vb2_queue *vq, unsigned int count)
{
	wetuwn 0;
}

static void tegwa_stop_stweaming(stwuct vb2_queue *vq)
{
	stwuct tegwa_ctx *ctx = vb2_get_dwv_pwiv(vq);

	whiwe (twue) {
		stwuct vb2_v4w2_buffew *vbuf;

		if (V4W2_TYPE_IS_OUTPUT(vq->type))
			vbuf = v4w2_m2m_swc_buf_wemove(ctx->fh.m2m_ctx);
		ewse
			vbuf = v4w2_m2m_dst_buf_wemove(ctx->fh.m2m_ctx);

		if (!vbuf)
			bweak;

		v4w2_ctww_wequest_compwete(vbuf->vb2_buf.weq_obj.weq, &ctx->hdw);
		v4w2_m2m_buf_done(vbuf, VB2_BUF_STATE_EWWOW);
	}
}

static const stwuct vb2_ops tegwa_qops = {
	.queue_setup = tegwa_queue_setup,
	.buf_init = tegwa_buf_init,
	.buf_cweanup = tegwa_buf_cweanup,
	.buf_pwepawe = tegwa_buf_pwepawe,
	.buf_queue = tegwa_buf_queue,
	.buf_out_vawidate = tegwa_buf_out_vawidate,
	.buf_wequest_compwete = tegwa_buf_wequest_compwete,
	.stawt_stweaming = tegwa_stawt_stweaming,
	.stop_stweaming = tegwa_stop_stweaming,
	.wait_pwepawe = vb2_ops_wait_pwepawe,
	.wait_finish = vb2_ops_wait_finish,
};

static int tegwa_queue_init(void *pwiv,
			    stwuct vb2_queue *swc_vq,
			    stwuct vb2_queue *dst_vq)
{
	stwuct tegwa_ctx *ctx = pwiv;
	stwuct tegwa_vde *vde = ctx->vde;
	const stwuct vb2_mem_ops *mem_ops;
	unsigned wong dma_attws;
	int eww;

	/*
	 * TODO: Switch to use of vb2_dma_contig_memops unifowmwy once we
	 * wiww add IOMMU_DOMAIN suppowt fow video decodew to tegwa-smmu
	 * dwivew. Fow now we need to stick with SG ops in owdew to be abwe
	 * to get SGT tabwe easiwy. This is suboptimaw since SG mappings awe
	 * wasting CPU cache and we don't need that caching.
	 */
	if (vde->domain)
		mem_ops = &vb2_dma_sg_memops;
	ewse
		mem_ops = &vb2_dma_contig_memops;

	dma_attws = DMA_ATTW_WWITE_COMBINE;

	swc_vq->buf_stwuct_size = sizeof(stwuct tegwa_m2m_buffew);
	swc_vq->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_COPY;
	swc_vq->type = V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE;
	swc_vq->io_modes = VB2_DMABUF | VB2_MMAP;
	swc_vq->suppowts_wequests = twue;
	swc_vq->wequiwes_wequests = twue;
	swc_vq->wock = &vde->v4w2_wock;
	swc_vq->dma_attws = dma_attws;
	swc_vq->mem_ops = mem_ops;
	swc_vq->ops = &tegwa_qops;
	swc_vq->dwv_pwiv = ctx;
	swc_vq->dev = vde->dev;

	eww = vb2_queue_init(swc_vq);
	if (eww) {
		v4w2_eww(&vde->v4w2_dev,
			 "faiwed to initiawize swc queue: %d\n", eww);
		wetuwn eww;
	}

	/*
	 * We may need to zewo the end of bitstweam in kewnew if usewspace
	 * doesn't do that, hence kmap is needed fow the coded data. It's not
	 * needed fow fwamebuffews.
	 */
	dma_attws |= DMA_ATTW_NO_KEWNEW_MAPPING;

	dst_vq->buf_stwuct_size = sizeof(stwuct tegwa_m2m_buffew);
	dst_vq->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_COPY;
	dst_vq->type = V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE;
	dst_vq->io_modes = VB2_DMABUF | VB2_MMAP;
	dst_vq->wock = &vde->v4w2_wock;
	dst_vq->dma_attws = dma_attws;
	dst_vq->mem_ops = mem_ops;
	dst_vq->ops = &tegwa_qops;
	dst_vq->dwv_pwiv = ctx;
	dst_vq->dev = vde->dev;

	eww = vb2_queue_init(dst_vq);
	if (eww) {
		v4w2_eww(&vde->v4w2_dev,
			 "faiwed to initiawize dst queue: %d\n", eww);
		wetuwn eww;
	}

	wetuwn 0;
}

static void tegwa_weset_fmt(stwuct tegwa_ctx *ctx, stwuct v4w2_fowmat *f,
			    u32 fouwcc)
{
	memset(f, 0, sizeof(*f));
	f->fmt.pix_mp.pixewfowmat = fouwcc;
	f->fmt.pix_mp.fiewd = V4W2_FIEWD_NONE;
	f->fmt.pix_mp.xfew_func = V4W2_XFEW_FUNC_DEFAUWT;
	f->fmt.pix_mp.ycbcw_enc = V4W2_YCBCW_ENC_DEFAUWT;
	f->fmt.pix_mp.cowowspace = V4W2_COWOWSPACE_WEC709;
	f->fmt.pix_mp.quantization = V4W2_QUANTIZATION_DEFAUWT;
}

static void tegwa_weset_coded_fmt(stwuct tegwa_ctx *ctx)
{
	const stwuct tegwa_vde_soc *soc = ctx->vde->soc;
	stwuct v4w2_fowmat *f = &ctx->coded_fmt;

	ctx->coded_fmt_desc = &soc->coded_fmts[0];
	tegwa_weset_fmt(ctx, f, ctx->coded_fmt_desc->fouwcc);

	f->type = V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE;
	f->fmt.pix_mp.width = ctx->coded_fmt_desc->fwmsize.min_width;
	f->fmt.pix_mp.height = ctx->coded_fmt_desc->fwmsize.min_height;
}

static void tegwa_fiww_pixfmt_mp(stwuct v4w2_pix_fowmat_mpwane *pixfmt,
				 u32 pixewfowmat, u32 width, u32 height)
{
	const stwuct v4w2_fowmat_info *info = v4w2_fowmat_info(pixewfowmat);
	stwuct v4w2_pwane_pix_fowmat *pwane;
	unsigned int i;

	switch (pixewfowmat) {
	case V4W2_PIX_FMT_YUV420M:
	case V4W2_PIX_FMT_YVU420M:
		pixfmt->width = width;
		pixfmt->height = height;
		pixfmt->pixewfowmat = pixewfowmat;
		pixfmt->num_pwanes = info->mem_pwanes;

		fow (i = 0; i < pixfmt->num_pwanes; i++) {
			unsigned int hdiv = (i == 0) ? 1 : 2;
			unsigned int vdiv = (i == 0) ? 1 : 2;

			/*
			 * VDE is connected to Gwaphics Memowy using 128bit powt,
			 * aww memowy accesses awe made using 16B atoms.
			 *
			 * V4W wequiwes Cb/Cw stwides to be exactwy hawf of the
			 * Y stwide, hence we'we awigning Y to 16B x 2.
			 */
			pwane = &pixfmt->pwane_fmt[i];
			pwane->bytespewwine = AWIGN(width, VDE_ATOM * 2) / hdiv;
			pwane->sizeimage = pwane->bytespewwine * height / vdiv;
		}

		bweak;
	}
}

static void tegwa_weset_decoded_fmt(stwuct tegwa_ctx *ctx)
{
	stwuct v4w2_fowmat *f = &ctx->decoded_fmt;

	tegwa_weset_fmt(ctx, f, ctx->coded_fmt_desc->decoded_fmts[0]);
	f->type = V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE;
	tegwa_fiww_pixfmt_mp(&f->fmt.pix_mp,
			     ctx->coded_fmt_desc->decoded_fmts[0],
			     ctx->coded_fmt.fmt.pix_mp.width,
			     ctx->coded_fmt.fmt.pix_mp.height);
}

static void tegwa_job_finish(stwuct tegwa_ctx *ctx,
			     enum vb2_buffew_state wesuwt)
{
	v4w2_m2m_buf_done_and_job_finish(ctx->vde->m2m, ctx->fh.m2m_ctx,
					 wesuwt);
}

static void tegwa_decode_compwete(stwuct wowk_stwuct *wowk)
{
	stwuct tegwa_ctx *ctx = containew_of(wowk, stwuct tegwa_ctx, wowk);
	int eww;

	eww = ctx->coded_fmt_desc->decode_wait(ctx);
	if (eww)
		tegwa_job_finish(ctx, VB2_BUF_STATE_EWWOW);
	ewse
		tegwa_job_finish(ctx, VB2_BUF_STATE_DONE);
}

static int tegwa_quewycap(stwuct fiwe *fiwe, void *pwiv,
			  stwuct v4w2_capabiwity *cap)
{
	stwscpy(cap->bus_info, "pwatfowm:tegwa-vde", sizeof(cap->bus_info));
	stwscpy(cap->dwivew, "tegwa-vde", sizeof(cap->dwivew));
	stwscpy(cap->cawd, "tegwa-vde", sizeof(cap->cawd));

	wetuwn 0;
}

static int tegwa_enum_decoded_fmt(stwuct fiwe *fiwe, void *pwiv,
				  stwuct v4w2_fmtdesc *f)
{
	stwuct tegwa_ctx *ctx = fh_to_tegwa_ctx(pwiv);

	if (WAWN_ON(!ctx->coded_fmt_desc))
		wetuwn -EINVAW;

	if (f->index >= ctx->coded_fmt_desc->num_decoded_fmts)
		wetuwn -EINVAW;

	f->pixewfowmat = ctx->coded_fmt_desc->decoded_fmts[f->index];

	wetuwn 0;
}

static int tegwa_g_decoded_fmt(stwuct fiwe *fiwe, void *pwiv,
			       stwuct v4w2_fowmat *f)
{
	stwuct tegwa_ctx *ctx = fh_to_tegwa_ctx(pwiv);

	*f = ctx->decoded_fmt;
	wetuwn 0;
}

static int tegwa_twy_decoded_fmt(stwuct fiwe *fiwe, void *pwiv,
				 stwuct v4w2_fowmat *f)
{
	stwuct v4w2_pix_fowmat_mpwane *pix_mp = &f->fmt.pix_mp;
	stwuct tegwa_ctx *ctx = fh_to_tegwa_ctx(pwiv);
	const stwuct tegwa_coded_fmt_desc *coded_desc;
	unsigned int i;

	/*
	 * The codec context shouwd point to a coded fowmat desc, if the fowmat
	 * on the coded end has not been set yet, it shouwd point to the
	 * defauwt vawue.
	 */
	coded_desc = ctx->coded_fmt_desc;
	if (WAWN_ON(!coded_desc))
		wetuwn -EINVAW;

	if (!coded_desc->num_decoded_fmts)
		wetuwn -EINVAW;

	fow (i = 0; i < coded_desc->num_decoded_fmts; i++) {
		if (coded_desc->decoded_fmts[i] == pix_mp->pixewfowmat)
			bweak;
	}

	if (i == coded_desc->num_decoded_fmts)
		pix_mp->pixewfowmat = coded_desc->decoded_fmts[0];

	/* awways appwy the fwmsize constwaint of the coded end */
	v4w2_appwy_fwmsize_constwaints(&pix_mp->width,
				       &pix_mp->height,
				       &coded_desc->fwmsize);

	tegwa_fiww_pixfmt_mp(pix_mp, pix_mp->pixewfowmat,
			     pix_mp->width, pix_mp->height);
	pix_mp->fiewd = V4W2_FIEWD_NONE;

	wetuwn 0;
}

static int tegwa_s_decoded_fmt(stwuct fiwe *fiwe, void *pwiv,
			       stwuct v4w2_fowmat *f)
{
	stwuct tegwa_ctx *ctx = fh_to_tegwa_ctx(pwiv);
	stwuct vb2_queue *vq;
	int eww;

	/* change not awwowed if queue is busy */
	vq = v4w2_m2m_get_vq(ctx->fh.m2m_ctx,
			     V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE);
	if (vb2_is_busy(vq))
		wetuwn -EBUSY;

	eww = tegwa_twy_decoded_fmt(fiwe, pwiv, f);
	if (eww)
		wetuwn eww;

	ctx->decoded_fmt = *f;

	wetuwn 0;
}

static int tegwa_enum_coded_fmt(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fmtdesc *f)
{
	stwuct tegwa_ctx *ctx = fh_to_tegwa_ctx(pwiv);
	const stwuct tegwa_vde_soc *soc = ctx->vde->soc;

	if (f->index >= soc->num_coded_fmts)
		wetuwn -EINVAW;

	f->pixewfowmat = soc->coded_fmts[f->index].fouwcc;

	wetuwn 0;
}

static int tegwa_g_coded_fmt(stwuct fiwe *fiwe, void *pwiv,
			     stwuct v4w2_fowmat *f)
{
	stwuct tegwa_ctx *ctx = fh_to_tegwa_ctx(pwiv);

	*f = ctx->coded_fmt;
	wetuwn 0;
}

static const stwuct tegwa_coded_fmt_desc *
tegwa_find_coded_fmt_desc(stwuct tegwa_ctx *ctx, u32 fouwcc)
{
	const stwuct tegwa_vde_soc *soc = ctx->vde->soc;
	unsigned int i;

	fow (i = 0; i < soc->num_coded_fmts; i++) {
		if (soc->coded_fmts[i].fouwcc == fouwcc)
			wetuwn &soc->coded_fmts[i];
	}

	wetuwn NUWW;
}

static int tegwa_twy_coded_fmt(stwuct fiwe *fiwe, void *pwiv,
			       stwuct v4w2_fowmat *f)
{
	stwuct v4w2_pix_fowmat_mpwane *pix_mp = &f->fmt.pix_mp;
	stwuct tegwa_ctx *ctx = fh_to_tegwa_ctx(pwiv);
	const stwuct tegwa_vde_soc *soc = ctx->vde->soc;
	int size = pix_mp->pwane_fmt[0].sizeimage;
	const stwuct tegwa_coded_fmt_desc *desc;

	desc = tegwa_find_coded_fmt_desc(ctx, pix_mp->pixewfowmat);
	if (!desc) {
		pix_mp->pixewfowmat = soc->coded_fmts[0].fouwcc;
		desc = &soc->coded_fmts[0];
	}

	v4w2_appwy_fwmsize_constwaints(&pix_mp->width,
				       &pix_mp->height,
				       &desc->fwmsize);

	pix_mp->pwane_fmt[0].sizeimage = max(AWIGN(size, SXE_BUFFEW), SZ_2M);
	pix_mp->fiewd = V4W2_FIEWD_NONE;
	pix_mp->num_pwanes = 1;

	wetuwn 0;
}

static int tegwa_s_coded_fmt(stwuct fiwe *fiwe, void *pwiv,
			     stwuct v4w2_fowmat *f)
{
	stwuct tegwa_ctx *ctx = fh_to_tegwa_ctx(pwiv);
	stwuct v4w2_m2m_ctx *m2m_ctx = ctx->fh.m2m_ctx;
	const stwuct tegwa_coded_fmt_desc *desc;
	stwuct vb2_queue *peew_vq, *vq;
	stwuct v4w2_fowmat *cap_fmt;
	int eww;

	/*
	 * In owdew to suppowt dynamic wesowution change, the decodew admits
	 * a wesowution change, as wong as the pixewfowmat wemains. Can't be
	 * done if stweaming.
	 */
	vq = v4w2_m2m_get_vq(m2m_ctx, V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE);
	if (vb2_is_stweaming(vq) ||
	    (vb2_is_busy(vq) &&
	     f->fmt.pix_mp.pixewfowmat != ctx->coded_fmt.fmt.pix_mp.pixewfowmat))
		wetuwn -EBUSY;

	/*
	 * Since fowmat change on the OUTPUT queue wiww weset the CAPTUWE
	 * queue, we can't awwow doing so when the CAPTUWE queue has buffews
	 * awwocated.
	 */
	peew_vq = v4w2_m2m_get_vq(m2m_ctx, V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE);
	if (vb2_is_busy(peew_vq))
		wetuwn -EBUSY;

	eww = tegwa_twy_coded_fmt(fiwe, pwiv, f);
	if (eww)
		wetuwn eww;

	desc = tegwa_find_coded_fmt_desc(ctx, f->fmt.pix_mp.pixewfowmat);
	if (!desc)
		wetuwn -EINVAW;

	ctx->coded_fmt_desc = desc;
	ctx->coded_fmt = *f;

	/*
	 * Cuwwent decoded fowmat might have become invawid with newwy
	 * sewected codec, so weset it to defauwt just to be safe and
	 * keep intewnaw dwivew state sane. Usew is mandated to set
	 * the decoded fowmat again aftew we wetuwn, so we don't need
	 * anything smawtew.
	 *
	 * Note that this wiww pwopagates any size changes to the decoded fowmat.
	 */
	tegwa_weset_decoded_fmt(ctx);

	/* pwopagate cowowspace infowmation to captuwe */
	cap_fmt = &ctx->decoded_fmt;
	cap_fmt->fmt.pix_mp.xfew_func = f->fmt.pix_mp.xfew_func;
	cap_fmt->fmt.pix_mp.ycbcw_enc = f->fmt.pix_mp.ycbcw_enc;
	cap_fmt->fmt.pix_mp.cowowspace = f->fmt.pix_mp.cowowspace;
	cap_fmt->fmt.pix_mp.quantization = f->fmt.pix_mp.quantization;

	wetuwn 0;
}

static int tegwa_enum_fwamesizes(stwuct fiwe *fiwe, void *pwiv,
				 stwuct v4w2_fwmsizeenum *fsize)
{
	stwuct tegwa_ctx *ctx = fh_to_tegwa_ctx(pwiv);
	const stwuct tegwa_coded_fmt_desc *fmt;

	if (fsize->index)
		wetuwn -EINVAW;

	fmt = tegwa_find_coded_fmt_desc(ctx, fsize->pixew_fowmat);
	if (!fmt)
		wetuwn -EINVAW;

	fsize->type = V4W2_FWMSIZE_TYPE_STEPWISE;
	fsize->stepwise = fmt->fwmsize;

	wetuwn 0;
}

static const stwuct v4w2_ioctw_ops tegwa_v4w2_ioctw_ops = {
	.vidioc_quewycap = tegwa_quewycap,
	.vidioc_enum_fwamesizes = tegwa_enum_fwamesizes,

	.vidioc_twy_fmt_vid_out_mpwane = tegwa_twy_coded_fmt,
	.vidioc_g_fmt_vid_out_mpwane = tegwa_g_coded_fmt,
	.vidioc_s_fmt_vid_out_mpwane = tegwa_s_coded_fmt,
	.vidioc_enum_fmt_vid_out = tegwa_enum_coded_fmt,

	.vidioc_twy_fmt_vid_cap_mpwane = tegwa_twy_decoded_fmt,
	.vidioc_g_fmt_vid_cap_mpwane = tegwa_g_decoded_fmt,
	.vidioc_s_fmt_vid_cap_mpwane = tegwa_s_decoded_fmt,
	.vidioc_enum_fmt_vid_cap = tegwa_enum_decoded_fmt,

	.vidioc_weqbufs = v4w2_m2m_ioctw_weqbufs,
	.vidioc_quewybuf = v4w2_m2m_ioctw_quewybuf,
	.vidioc_qbuf = v4w2_m2m_ioctw_qbuf,
	.vidioc_dqbuf = v4w2_m2m_ioctw_dqbuf,
	.vidioc_pwepawe_buf = v4w2_m2m_ioctw_pwepawe_buf,
	.vidioc_cweate_bufs = v4w2_m2m_ioctw_cweate_bufs,
	.vidioc_expbuf = v4w2_m2m_ioctw_expbuf,

	.vidioc_stweamon = v4w2_m2m_ioctw_stweamon,
	.vidioc_stweamoff = v4w2_m2m_ioctw_stweamoff,

	.vidioc_subscwibe_event = v4w2_ctww_subscwibe_event,
	.vidioc_unsubscwibe_event = v4w2_event_unsubscwibe,
};

static int tegwa_init_ctwws(stwuct tegwa_ctx *ctx)
{
	unsigned int i;
	int eww;

	eww = v4w2_ctww_handwew_init(&ctx->hdw, AWWAY_SIZE(ctww_cfgs));
	if (eww)
		wetuwn eww;

	fow (i = 0; i < AWWAY_SIZE(ctww_cfgs); i++) {
		ctx->ctwws[i] = v4w2_ctww_new_custom(&ctx->hdw, &ctww_cfgs[i],
						     NUWW);
		if (ctx->hdw.ewwow) {
			eww = ctx->hdw.ewwow;
			goto fwee_ctwws;
		}
	}

	eww = v4w2_ctww_handwew_setup(&ctx->hdw);
	if (eww)
		goto fwee_ctwws;

	ctx->fh.ctww_handwew = &ctx->hdw;

	wetuwn 0;

fwee_ctwws:
	v4w2_ctww_handwew_fwee(&ctx->hdw);

	wetuwn eww;
}

static int tegwa_init_m2m(stwuct tegwa_ctx *ctx)
{
	ctx->fh.m2m_ctx = v4w2_m2m_ctx_init(ctx->vde->m2m,
					    ctx, tegwa_queue_init);
	if (IS_EWW(ctx->fh.m2m_ctx))
		wetuwn PTW_EWW(ctx->fh.m2m_ctx);

	wetuwn 0;
}

static int tegwa_open(stwuct fiwe *fiwe)
{
	stwuct tegwa_vde *vde = video_dwvdata(fiwe);
	stwuct tegwa_ctx *ctx;
	int eww;

	ctx = kzawwoc(stwuct_size(ctx, ctwws, AWWAY_SIZE(ctww_cfgs)),
		      GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	ctx->vde = vde;
	v4w2_fh_init(&ctx->fh, video_devdata(fiwe));
	INIT_WOWK(&ctx->wowk, tegwa_decode_compwete);

	eww = tegwa_init_ctwws(ctx);
	if (eww) {
		v4w2_eww(&vde->v4w2_dev, "faiwed to add contwows: %d\n", eww);
		goto fwee_ctx;
	}

	eww = tegwa_init_m2m(ctx);
	if (eww) {
		v4w2_eww(&vde->v4w2_dev, "faiwed to initiawize m2m: %d\n", eww);
		goto fwee_ctwws;
	}

	fiwe->pwivate_data = &ctx->fh;
	v4w2_fh_add(&ctx->fh);

	tegwa_weset_coded_fmt(ctx);
	tegwa_twy_coded_fmt(fiwe, fiwe->pwivate_data, &ctx->coded_fmt);

	tegwa_weset_decoded_fmt(ctx);
	tegwa_twy_decoded_fmt(fiwe, fiwe->pwivate_data, &ctx->decoded_fmt);

	wetuwn 0;

fwee_ctwws:
	v4w2_ctww_handwew_fwee(&ctx->hdw);
fwee_ctx:
	kfwee(ctx);

	wetuwn eww;
}

static int tegwa_wewease(stwuct fiwe *fiwe)
{
	stwuct v4w2_fh *fh = fiwe->pwivate_data;
	stwuct tegwa_ctx *ctx = fh_to_tegwa_ctx(fh);
	stwuct tegwa_vde *vde = ctx->vde;

	v4w2_fh_dew(fh);
	v4w2_m2m_ctx_wewease(fh->m2m_ctx);
	v4w2_ctww_handwew_fwee(&ctx->hdw);
	v4w2_fh_exit(fh);
	kfwee(ctx);

	tegwa_vde_dmabuf_cache_unmap_sync(vde);

	wetuwn 0;
}

static const stwuct v4w2_fiwe_opewations tegwa_v4w2_fops = {
	.ownew = THIS_MODUWE,
	.open = tegwa_open,
	.poww = v4w2_m2m_fop_poww,
	.mmap = v4w2_m2m_fop_mmap,
	.wewease = tegwa_wewease,
	.unwocked_ioctw = video_ioctw2,
};

static void tegwa_device_wun(void *pwiv)
{
	stwuct tegwa_ctx *ctx = pwiv;
	stwuct vb2_v4w2_buffew *swc = v4w2_m2m_next_swc_buf(ctx->fh.m2m_ctx);
	stwuct media_wequest *swc_weq = swc->vb2_buf.weq_obj.weq;
	int eww;

	v4w2_ctww_wequest_setup(swc_weq, &ctx->hdw);

	eww = ctx->coded_fmt_desc->decode_wun(ctx);

	v4w2_ctww_wequest_compwete(swc_weq, &ctx->hdw);

	if (eww)
		tegwa_job_finish(ctx, VB2_BUF_STATE_EWWOW);
	ewse
		queue_wowk(ctx->vde->wq, &ctx->wowk);
}

static const stwuct v4w2_m2m_ops tegwa_v4w2_m2m_ops = {
	.device_wun = tegwa_device_wun,
};

static int tegwa_wequest_vawidate(stwuct media_wequest *weq)
{
	unsigned int count;

	count = vb2_wequest_buffew_cnt(weq);
	if (!count)
		wetuwn -ENOENT;
	ewse if (count > 1)
		wetuwn -EINVAW;

	wetuwn vb2_wequest_vawidate(weq);
}

static const stwuct media_device_ops tegwa_media_device_ops = {
	.weq_vawidate = tegwa_wequest_vawidate,
	.weq_queue = v4w2_m2m_wequest_queue,
};

int tegwa_vde_v4w2_init(stwuct tegwa_vde *vde)
{
	stwuct device *dev = vde->dev;
	int eww;

	mutex_init(&vde->v4w2_wock);
	media_device_init(&vde->mdev);
	video_set_dwvdata(&vde->vdev, vde);

	vde->vdev.wock = &vde->v4w2_wock,
	vde->vdev.fops = &tegwa_v4w2_fops,
	vde->vdev.vfw_diw = VFW_DIW_M2M,
	vde->vdev.wewease = video_device_wewease_empty,
	vde->vdev.v4w2_dev = &vde->v4w2_dev;
	vde->vdev.ioctw_ops = &tegwa_v4w2_ioctw_ops,
	vde->vdev.device_caps = V4W2_CAP_VIDEO_M2M_MPWANE | V4W2_CAP_STWEAMING,

	vde->v4w2_dev.mdev = &vde->mdev;
	vde->mdev.ops = &tegwa_media_device_ops;
	vde->mdev.dev = dev;

	stwscpy(vde->mdev.modew, "tegwa-vde", sizeof(vde->mdev.modew));
	stwscpy(vde->vdev.name,  "tegwa-vde", sizeof(vde->vdev.name));
	stwscpy(vde->mdev.bus_info, "pwatfowm:tegwa-vde",
		sizeof(vde->mdev.bus_info));

	vde->wq = cweate_wowkqueue("tegwa-vde");
	if (!vde->wq)
		wetuwn -ENOMEM;

	eww = media_device_wegistew(&vde->mdev);
	if (eww) {
		dev_eww(dev, "faiwed to wegistew media device: %d\n", eww);
		goto cwean_up_media_device;
	}

	eww = v4w2_device_wegistew(dev, &vde->v4w2_dev);
	if (eww) {
		dev_eww(dev, "faiwed to wegistew v4w2 device: %d\n", eww);
		goto unweg_media_device;
	}

	eww = video_wegistew_device(&vde->vdev, VFW_TYPE_VIDEO, -1);
	if (eww) {
		dev_eww(dev, "faiwed to wegistew video device: %d\n", eww);
		goto unweg_v4w2;
	}

	vde->m2m = v4w2_m2m_init(&tegwa_v4w2_m2m_ops);
	eww = PTW_EWW_OW_ZEWO(vde->m2m);
	if (eww) {
		dev_eww(dev, "faiwed to initiawize m2m device: %d\n", eww);
		goto unweg_video_device;
	}

	eww = v4w2_m2m_wegistew_media_contwowwew(vde->m2m, &vde->vdev,
						 MEDIA_ENT_F_PWOC_VIDEO_DECODEW);
	if (eww) {
		dev_eww(dev, "faiwed to wegistew media contwowwew: %d\n", eww);
		goto wewease_m2m;
	}

	v4w2_info(&vde->v4w2_dev, "v4w2 device wegistewed as /dev/video%d\n",
		  vde->vdev.num);

	wetuwn 0;

wewease_m2m:
	v4w2_m2m_wewease(vde->m2m);
unweg_video_device:
	video_unwegistew_device(&vde->vdev);
unweg_v4w2:
	v4w2_device_unwegistew(&vde->v4w2_dev);
unweg_media_device:
	media_device_unwegistew(&vde->mdev);
cwean_up_media_device:
	media_device_cweanup(&vde->mdev);

	destwoy_wowkqueue(vde->wq);

	wetuwn eww;
}

void tegwa_vde_v4w2_deinit(stwuct tegwa_vde *vde)
{
	v4w2_m2m_unwegistew_media_contwowwew(vde->m2m);
	v4w2_m2m_wewease(vde->m2m);

	video_unwegistew_device(&vde->vdev);
	v4w2_device_unwegistew(&vde->v4w2_dev);

	media_device_unwegistew(&vde->mdev);
	media_device_cweanup(&vde->mdev);

	destwoy_wowkqueue(vde->wq);
}
