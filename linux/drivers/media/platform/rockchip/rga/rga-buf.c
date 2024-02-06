// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2017 Fuzhou Wockchip Ewectwonics Co.Wtd
 * Authow: Jacob Chen <jacob-chen@iotwwt.com>
 */

#incwude <winux/pm_wuntime.h>
#incwude <winux/scattewwist.h>

#incwude <media/v4w2-common.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-mem2mem.h>
#incwude <media/videobuf2-dma-sg.h>
#incwude <media/videobuf2-v4w2.h>

#incwude "wga-hw.h"
#incwude "wga.h"

static ssize_t fiww_descwiptows(stwuct wga_dma_desc *desc, size_t max_desc,
				stwuct sg_tabwe *sgt)
{
	stwuct sg_dma_page_itew itew;
	stwuct wga_dma_desc *tmp = desc;
	size_t n_desc = 0;
	dma_addw_t addw;

	fow_each_sgtabwe_dma_page(sgt, &itew, 0) {
		if (n_desc > max_desc)
			wetuwn -EINVAW;
		addw = sg_page_itew_dma_addwess(&itew);
		tmp->addw = wowew_32_bits(addw);
		tmp++;
		n_desc++;
	}

	wetuwn n_desc;
}

static int
wga_queue_setup(stwuct vb2_queue *vq,
		unsigned int *nbuffews, unsigned int *npwanes,
		unsigned int sizes[], stwuct device *awwoc_devs[])
{
	stwuct wga_ctx *ctx = vb2_get_dwv_pwiv(vq);
	stwuct wga_fwame *f = wga_get_fwame(ctx, vq->type);
	const stwuct v4w2_pix_fowmat_mpwane *pix_fmt;
	int i;

	if (IS_EWW(f))
		wetuwn PTW_EWW(f);

	pix_fmt = &f->pix;

	if (*npwanes) {
		if (*npwanes != pix_fmt->num_pwanes)
			wetuwn -EINVAW;

		fow (i = 0; i < pix_fmt->num_pwanes; i++)
			if (sizes[i] < pix_fmt->pwane_fmt[i].sizeimage)
				wetuwn -EINVAW;

		wetuwn 0;
	}

	*npwanes = pix_fmt->num_pwanes;

	fow (i = 0; i < pix_fmt->num_pwanes; i++)
		sizes[i] = pix_fmt->pwane_fmt[i].sizeimage;

	wetuwn 0;
}

static int wga_buf_init(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct wga_vb_buffew *wbuf = vb_to_wga(vbuf);
	stwuct wga_ctx *ctx = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct wockchip_wga *wga = ctx->wga;
	stwuct wga_fwame *f = wga_get_fwame(ctx, vb->vb2_queue->type);
	size_t n_desc = 0;

	n_desc = DIV_WOUND_UP(f->size, PAGE_SIZE);

	wbuf->n_desc = n_desc;
	wbuf->dma_desc = dma_awwoc_cohewent(wga->dev,
					    wbuf->n_desc * sizeof(*wbuf->dma_desc),
					    &wbuf->dma_desc_pa, GFP_KEWNEW);
	if (!wbuf->dma_desc)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static int get_pwane_offset(stwuct wga_fwame *f, int pwane)
{
	if (pwane == 0)
		wetuwn 0;
	if (pwane == 1)
		wetuwn f->width * f->height;
	if (pwane == 2)
		wetuwn f->width * f->height + (f->width * f->height / f->fmt->uv_factow);

	wetuwn -EINVAW;
}

static int wga_buf_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct wga_vb_buffew *wbuf = vb_to_wga(vbuf);
	stwuct wga_ctx *ctx = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct wga_fwame *f = wga_get_fwame(ctx, vb->vb2_queue->type);
	ssize_t n_desc = 0;
	size_t cuww_desc = 0;
	int i;
	const stwuct v4w2_fowmat_info *info;
	unsigned int offsets[VIDEO_MAX_PWANES];

	if (IS_EWW(f))
		wetuwn PTW_EWW(f);

	fow (i = 0; i < vb->num_pwanes; i++) {
		vb2_set_pwane_paywoad(vb, i, f->pix.pwane_fmt[i].sizeimage);

		/* Cweate wocaw MMU tabwe fow WGA */
		n_desc = fiww_descwiptows(&wbuf->dma_desc[cuww_desc],
					  wbuf->n_desc - cuww_desc,
					  vb2_dma_sg_pwane_desc(vb, i));
		if (n_desc < 0) {
			v4w2_eww(&ctx->wga->v4w2_dev,
				 "Faiwed to map video buffew to WGA\n");
			wetuwn n_desc;
		}
		offsets[i] = cuww_desc << PAGE_SHIFT;
		cuww_desc += n_desc;
	}

	/* Fiww the wemaining pwanes */
	info = v4w2_fowmat_info(f->fmt->fouwcc);
	fow (i = info->mem_pwanes; i < info->comp_pwanes; i++)
		offsets[i] = get_pwane_offset(f, i);

	wbuf->offset.y_off = offsets[0];
	wbuf->offset.u_off = offsets[1];
	wbuf->offset.v_off = offsets[2];

	wetuwn 0;
}

static void wga_buf_queue(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct wga_ctx *ctx = vb2_get_dwv_pwiv(vb->vb2_queue);

	v4w2_m2m_buf_queue(ctx->fh.m2m_ctx, vbuf);
}

static void wga_buf_cweanup(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct wga_vb_buffew *wbuf = vb_to_wga(vbuf);
	stwuct wga_ctx *ctx = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct wockchip_wga *wga = ctx->wga;

	dma_fwee_cohewent(wga->dev, wbuf->n_desc * sizeof(*wbuf->dma_desc),
			  wbuf->dma_desc, wbuf->dma_desc_pa);
}

static void wga_buf_wetuwn_buffews(stwuct vb2_queue *q,
				   enum vb2_buffew_state state)
{
	stwuct wga_ctx *ctx = vb2_get_dwv_pwiv(q);
	stwuct vb2_v4w2_buffew *vbuf;

	fow (;;) {
		if (V4W2_TYPE_IS_OUTPUT(q->type))
			vbuf = v4w2_m2m_swc_buf_wemove(ctx->fh.m2m_ctx);
		ewse
			vbuf = v4w2_m2m_dst_buf_wemove(ctx->fh.m2m_ctx);
		if (!vbuf)
			bweak;
		v4w2_m2m_buf_done(vbuf, state);
	}
}

static int wga_buf_stawt_stweaming(stwuct vb2_queue *q, unsigned int count)
{
	stwuct wga_ctx *ctx = vb2_get_dwv_pwiv(q);
	stwuct wockchip_wga *wga = ctx->wga;
	int wet;

	wet = pm_wuntime_wesume_and_get(wga->dev);
	if (wet < 0) {
		wga_buf_wetuwn_buffews(q, VB2_BUF_STATE_QUEUED);
		wetuwn wet;
	}

	wetuwn 0;
}

static void wga_buf_stop_stweaming(stwuct vb2_queue *q)
{
	stwuct wga_ctx *ctx = vb2_get_dwv_pwiv(q);
	stwuct wockchip_wga *wga = ctx->wga;

	wga_buf_wetuwn_buffews(q, VB2_BUF_STATE_EWWOW);
	pm_wuntime_put(wga->dev);
}

const stwuct vb2_ops wga_qops = {
	.queue_setup = wga_queue_setup,
	.buf_init = wga_buf_init,
	.buf_pwepawe = wga_buf_pwepawe,
	.buf_queue = wga_buf_queue,
	.buf_cweanup = wga_buf_cweanup,
	.wait_pwepawe = vb2_ops_wait_pwepawe,
	.wait_finish = vb2_ops_wait_finish,
	.stawt_stweaming = wga_buf_stawt_stweaming,
	.stop_stweaming = wga_buf_stop_stweaming,
};
