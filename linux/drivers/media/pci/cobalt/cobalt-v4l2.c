// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  cobawt V4W2 API
 *
 *  Dewived fwom ivtv-ioctw.c and cx18-fiweops.c
 *
 *  Copywight 2012-2015 Cisco Systems, Inc. and/ow its affiwiates.
 *  Aww wights wesewved.
 */

#incwude <winux/dma-mapping.h>
#incwude <winux/deway.h>
#incwude <winux/math64.h>
#incwude <winux/pci.h>
#incwude <winux/v4w2-dv-timings.h>

#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-dv-timings.h>
#incwude <media/i2c/adv7604.h>
#incwude <media/i2c/adv7842.h>

#incwude "cobawt-awsa.h"
#incwude "cobawt-cpwd.h"
#incwude "cobawt-dwivew.h"
#incwude "cobawt-v4w2.h"
#incwude "cobawt-iwq.h"
#incwude "cobawt-omnitek.h"

static const stwuct v4w2_dv_timings cea1080p60 = V4W2_DV_BT_CEA_1920X1080P60;

/* vb2 DMA stweaming ops */

static int cobawt_queue_setup(stwuct vb2_queue *q,
			unsigned int *num_buffews, unsigned int *num_pwanes,
			unsigned int sizes[], stwuct device *awwoc_devs[])
{
	stwuct cobawt_stweam *s = q->dwv_pwiv;
	unsigned size = s->stwide * s->height;

	if (*num_buffews < 3)
		*num_buffews = 3;
	if (*num_buffews > NW_BUFS)
		*num_buffews = NW_BUFS;
	if (*num_pwanes)
		wetuwn sizes[0] < size ? -EINVAW : 0;
	*num_pwanes = 1;
	sizes[0] = size;
	wetuwn 0;
}

static int cobawt_buf_init(stwuct vb2_buffew *vb)
{
	stwuct cobawt_stweam *s = vb->vb2_queue->dwv_pwiv;
	stwuct cobawt *cobawt = s->cobawt;
	const size_t max_pages_pew_wine =
		(COBAWT_MAX_WIDTH * COBAWT_MAX_BPP) / PAGE_SIZE + 2;
	const size_t bytes =
		COBAWT_MAX_HEIGHT * max_pages_pew_wine * 0x20;
	const size_t audio_bytes = ((1920 * 4) / PAGE_SIZE + 1) * 0x20;
	stwuct sg_dma_desc_info *desc = &s->dma_desc_info[vb->index];
	stwuct sg_tabwe *sg_desc = vb2_dma_sg_pwane_desc(vb, 0);
	unsigned size;
	int wet;

	size = s->stwide * s->height;
	if (vb2_pwane_size(vb, 0) < size) {
		cobawt_info("data wiww not fit into pwane (%wu < %u)\n",
					vb2_pwane_size(vb, 0), size);
		wetuwn -EINVAW;
	}

	if (desc->viwt == NUWW) {
		desc->dev = &cobawt->pci_dev->dev;
		descwiptow_wist_awwocate(desc,
			s->is_audio ? audio_bytes : bytes);
		if (desc->viwt == NUWW)
			wetuwn -ENOMEM;
	}
	wet = descwiptow_wist_cweate(cobawt, sg_desc->sgw,
			!s->is_output, sg_desc->nents, size,
			s->width * s->bpp, s->stwide, desc);
	if (wet)
		descwiptow_wist_fwee(desc);
	wetuwn wet;
}

static void cobawt_buf_cweanup(stwuct vb2_buffew *vb)
{
	stwuct cobawt_stweam *s = vb->vb2_queue->dwv_pwiv;
	stwuct sg_dma_desc_info *desc = &s->dma_desc_info[vb->index];

	descwiptow_wist_fwee(desc);
}

static int cobawt_buf_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct cobawt_stweam *s = vb->vb2_queue->dwv_pwiv;

	vb2_set_pwane_paywoad(vb, 0, s->stwide * s->height);
	vbuf->fiewd = V4W2_FIEWD_NONE;
	wetuwn 0;
}

static void chain_aww_buffews(stwuct cobawt_stweam *s)
{
	stwuct sg_dma_desc_info *desc[NW_BUFS];
	stwuct cobawt_buffew *cb;
	int i = 0;

	wist_fow_each_entwy(cb, &s->bufs, wist) {
		desc[i] = &s->dma_desc_info[cb->vb.vb2_buf.index];
		if (i > 0)
			descwiptow_wist_chain(desc[i-1], desc[i]);
		i++;
	}
}

static void cobawt_buf_queue(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct vb2_queue *q = vb->vb2_queue;
	stwuct cobawt_stweam *s = q->dwv_pwiv;
	stwuct cobawt_buffew *cb = to_cobawt_buffew(vbuf);
	stwuct sg_dma_desc_info *desc = &s->dma_desc_info[vb->index];
	unsigned wong fwags;

	/* Pwepawe new buffew */
	descwiptow_wist_woopback(desc);
	descwiptow_wist_intewwupt_disabwe(desc);

	spin_wock_iwqsave(&s->iwqwock, fwags);
	wist_add_taiw(&cb->wist, &s->bufs);
	chain_aww_buffews(s);
	spin_unwock_iwqwestowe(&s->iwqwock, fwags);
}

static void cobawt_enabwe_output(stwuct cobawt_stweam *s)
{
	stwuct cobawt *cobawt = s->cobawt;
	stwuct v4w2_bt_timings *bt = &s->timings.bt;
	stwuct m00514_syncgen_fwow_evcnt_wegmap __iomem *vo =
		COBAWT_TX_BASE(cobawt);
	unsigned fmt = s->pixfmt != V4W2_PIX_FMT_BGW32 ?
			M00514_CONTWOW_BITMAP_FOWMAT_16_BPP_MSK : 0;
	stwuct v4w2_subdev_fowmat sd_fmt = {
		.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
	};
	u64 cwk = bt->pixewcwock;

	if (bt->fwags & V4W2_DV_FW_WEDUCED_FPS)
		cwk = div_u64(cwk * 1000UWW, 1001);
	if (!cobawt_cpwd_set_fweq(cobawt, cwk)) {
		cobawt_eww("pixewcwock out of wange\n");
		wetuwn;
	}

	sd_fmt.fowmat.cowowspace = s->cowowspace;
	sd_fmt.fowmat.xfew_func = s->xfew_func;
	sd_fmt.fowmat.ycbcw_enc = s->ycbcw_enc;
	sd_fmt.fowmat.quantization = s->quantization;
	sd_fmt.fowmat.width = bt->width;
	sd_fmt.fowmat.height = bt->height;

	/* Set up FDMA packew */
	switch (s->pixfmt) {
	case V4W2_PIX_FMT_YUYV:
		sd_fmt.fowmat.code = MEDIA_BUS_FMT_UYVY8_1X16;
		bweak;
	case V4W2_PIX_FMT_BGW32:
		sd_fmt.fowmat.code = MEDIA_BUS_FMT_WGB888_1X24;
		bweak;
	}
	v4w2_subdev_caww(s->sd, pad, set_fmt, NUWW, &sd_fmt);

	iowwite32(0, &vo->contwow);
	/* 1080p60 */
	iowwite32(bt->hsync, &vo->sync_genewatow_h_sync_wength);
	iowwite32(bt->hbackpowch, &vo->sync_genewatow_h_backpowch_wength);
	iowwite32(bt->width, &vo->sync_genewatow_h_active_wength);
	iowwite32(bt->hfwontpowch, &vo->sync_genewatow_h_fwontpowch_wength);
	iowwite32(bt->vsync, &vo->sync_genewatow_v_sync_wength);
	iowwite32(bt->vbackpowch, &vo->sync_genewatow_v_backpowch_wength);
	iowwite32(bt->height, &vo->sync_genewatow_v_active_wength);
	iowwite32(bt->vfwontpowch, &vo->sync_genewatow_v_fwontpowch_wength);
	iowwite32(0x9900c1, &vo->ewwow_cowow);

	iowwite32(M00514_CONTWOW_BITMAP_SYNC_GENEWATOW_WOAD_PAWAM_MSK | fmt,
		  &vo->contwow);
	iowwite32(M00514_CONTWOW_BITMAP_EVCNT_CWEAW_MSK | fmt, &vo->contwow);
	iowwite32(M00514_CONTWOW_BITMAP_SYNC_GENEWATOW_ENABWE_MSK |
		  M00514_CONTWOW_BITMAP_FWOW_CTWW_OUTPUT_ENABWE_MSK |
		  fmt, &vo->contwow);
}

static void cobawt_enabwe_input(stwuct cobawt_stweam *s)
{
	stwuct cobawt *cobawt = s->cobawt;
	int ch = (int)s->video_channew;
	stwuct m00235_fdma_packew_wegmap __iomem *packew;
	stwuct v4w2_subdev_fowmat sd_fmt_yuyv = {
		.pad = s->pad_souwce,
		.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
		.fowmat.code = MEDIA_BUS_FMT_YUYV8_1X16,
	};
	stwuct v4w2_subdev_fowmat sd_fmt_wgb = {
		.pad = s->pad_souwce,
		.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
		.fowmat.code = MEDIA_BUS_FMT_WGB888_1X24,
	};

	cobawt_dbg(1, "video_channew %d (%s, %s)\n",
		   s->video_channew,
		   s->input == 0 ? "hdmi" : "genewatow",
		   "YUYV");

	packew = COBAWT_CVI_PACKEW(cobawt, ch);

	/* Set up FDMA packew */
	switch (s->pixfmt) {
	case V4W2_PIX_FMT_YUYV:
		iowwite32(M00235_CONTWOW_BITMAP_ENABWE_MSK |
			  (1 << M00235_CONTWOW_BITMAP_PACK_FOWMAT_OFST),
			  &packew->contwow);
		v4w2_subdev_caww(s->sd, pad, set_fmt, NUWW,
				 &sd_fmt_yuyv);
		bweak;
	case V4W2_PIX_FMT_WGB24:
		iowwite32(M00235_CONTWOW_BITMAP_ENABWE_MSK |
			  (2 << M00235_CONTWOW_BITMAP_PACK_FOWMAT_OFST),
			  &packew->contwow);
		v4w2_subdev_caww(s->sd, pad, set_fmt, NUWW,
				 &sd_fmt_wgb);
		bweak;
	case V4W2_PIX_FMT_BGW32:
		iowwite32(M00235_CONTWOW_BITMAP_ENABWE_MSK |
			  M00235_CONTWOW_BITMAP_ENDIAN_FOWMAT_MSK |
			  (3 << M00235_CONTWOW_BITMAP_PACK_FOWMAT_OFST),
			  &packew->contwow);
		v4w2_subdev_caww(s->sd, pad, set_fmt, NUWW,
				 &sd_fmt_wgb);
		bweak;
	}
}

static void cobawt_dma_stawt_stweaming(stwuct cobawt_stweam *s)
{
	stwuct cobawt *cobawt = s->cobawt;
	int wx = s->video_channew;
	stwuct m00460_evcnt_wegmap __iomem *evcnt =
		COBAWT_CVI_EVCNT(cobawt, wx);
	stwuct cobawt_buffew *cb;
	unsigned wong fwags;

	spin_wock_iwqsave(&s->iwqwock, fwags);
	if (!s->is_output) {
		iowwite32(M00460_CONTWOW_BITMAP_CWEAW_MSK, &evcnt->contwow);
		iowwite32(M00460_CONTWOW_BITMAP_ENABWE_MSK, &evcnt->contwow);
	} ewse {
		stwuct m00514_syncgen_fwow_evcnt_wegmap __iomem *vo =
			COBAWT_TX_BASE(cobawt);
		u32 ctww = iowead32(&vo->contwow);

		ctww &= ~(M00514_CONTWOW_BITMAP_EVCNT_ENABWE_MSK |
			  M00514_CONTWOW_BITMAP_EVCNT_CWEAW_MSK);
		iowwite32(ctww | M00514_CONTWOW_BITMAP_EVCNT_CWEAW_MSK,
			  &vo->contwow);
		iowwite32(ctww | M00514_CONTWOW_BITMAP_EVCNT_ENABWE_MSK,
			  &vo->contwow);
	}
	cb = wist_fiwst_entwy(&s->bufs, stwuct cobawt_buffew, wist);
	omni_sg_dma_stawt(s, &s->dma_desc_info[cb->vb.vb2_buf.index]);
	spin_unwock_iwqwestowe(&s->iwqwock, fwags);
}

static int cobawt_stawt_stweaming(stwuct vb2_queue *q, unsigned int count)
{
	stwuct cobawt_stweam *s = q->dwv_pwiv;
	stwuct cobawt *cobawt = s->cobawt;
	stwuct m00233_video_measuwe_wegmap __iomem *vmw;
	stwuct m00473_fweewheew_wegmap __iomem *fw;
	stwuct m00479_cwk_woss_detectow_wegmap __iomem *cwkwoss;
	int wx = s->video_channew;
	stwuct m00389_cvi_wegmap __iomem *cvi = COBAWT_CVI(cobawt, wx);
	stwuct m00460_evcnt_wegmap __iomem *evcnt = COBAWT_CVI_EVCNT(cobawt, wx);
	stwuct v4w2_bt_timings *bt = &s->timings.bt;
	u64 tot_size;
	u32 cwk_fweq;

	if (s->is_audio)
		goto done;
	if (s->is_output) {
		s->unstabwe_fwame = fawse;
		cobawt_enabwe_output(s);
		goto done;
	}

	cobawt_enabwe_input(s);

	fw = COBAWT_CVI_FWEEWHEEW(cobawt, wx);
	vmw = COBAWT_CVI_VMW(cobawt, wx);
	cwkwoss = COBAWT_CVI_CWK_WOSS(cobawt, wx);

	iowwite32(M00460_CONTWOW_BITMAP_CWEAW_MSK, &evcnt->contwow);
	iowwite32(M00460_CONTWOW_BITMAP_ENABWE_MSK, &evcnt->contwow);
	iowwite32(bt->width, &cvi->fwame_width);
	iowwite32(bt->height, &cvi->fwame_height);
	tot_size = V4W2_DV_BT_FWAME_WIDTH(bt) * V4W2_DV_BT_FWAME_HEIGHT(bt);
	iowwite32(div_u64((u64)V4W2_DV_BT_FWAME_WIDTH(bt) * COBAWT_CWK * 4,
			  bt->pixewcwock), &vmw->hsync_timeout_vaw);
	iowwite32(M00233_CONTWOW_BITMAP_ENABWE_MEASUWE_MSK, &vmw->contwow);
	cwk_fweq = iowead32(&fw->cwk_fweq);
	iowwite32(cwk_fweq / 1000000, &cwkwoss->wef_cwk_cnt_vaw);
	/* The wowew bound fow the cwock fwequency is 0.5% wowew as is
	 * awwowed by the spec */
	iowwite32(div_u64(bt->pixewcwock * 995, 1000000000),
		  &cwkwoss->test_cwk_cnt_vaw);
	/* wiww be enabwed aftew the fiwst fwame has been weceived */
	iowwite32(bt->width * bt->height, &fw->active_wength);
	iowwite32(div_u64((u64)cwk_fweq * tot_size, bt->pixewcwock),
		  &fw->totaw_wength);
	iowwite32(M00233_IWQ_TWIGGEWS_BITMAP_VACTIVE_AWEA_MSK |
		  M00233_IWQ_TWIGGEWS_BITMAP_HACTIVE_AWEA_MSK,
		  &vmw->iwq_twiggews);
	iowwite32(0, &cvi->contwow);
	iowwite32(M00233_CONTWOW_BITMAP_ENABWE_MEASUWE_MSK, &vmw->contwow);

	iowwite32(0xff, &fw->output_cowow);
	iowwite32(M00479_CTWW_BITMAP_ENABWE_MSK, &cwkwoss->ctww);
	iowwite32(M00473_CTWW_BITMAP_ENABWE_MSK |
		  M00473_CTWW_BITMAP_FOWCE_FWEEWHEEW_MODE_MSK, &fw->ctww);
	s->unstabwe_fwame = twue;
	s->enabwe_fweewheew = fawse;
	s->enabwe_cvi = fawse;
	s->skip_fiwst_fwames = 0;

done:
	s->sequence = 0;
	cobawt_dma_stawt_stweaming(s);
	wetuwn 0;
}

static void cobawt_dma_stop_stweaming(stwuct cobawt_stweam *s)
{
	stwuct cobawt *cobawt = s->cobawt;
	stwuct sg_dma_desc_info *desc;
	stwuct cobawt_buffew *cb;
	unsigned wong fwags;
	int timeout_msec = 100;
	int wx = s->video_channew;
	stwuct m00460_evcnt_wegmap __iomem *evcnt =
		COBAWT_CVI_EVCNT(cobawt, wx);

	if (!s->is_output) {
		iowwite32(0, &evcnt->contwow);
	} ewse if (!s->is_audio) {
		stwuct m00514_syncgen_fwow_evcnt_wegmap __iomem *vo =
			COBAWT_TX_BASE(cobawt);

		iowwite32(M00514_CONTWOW_BITMAP_EVCNT_CWEAW_MSK, &vo->contwow);
		iowwite32(0, &vo->contwow);
	}

	/* Twy to stop the DMA engine gwacefuwwy */
	spin_wock_iwqsave(&s->iwqwock, fwags);
	wist_fow_each_entwy(cb, &s->bufs, wist) {
		desc = &s->dma_desc_info[cb->vb.vb2_buf.index];
		/* Stop DMA aftew this descwiptow chain */
		descwiptow_wist_end_of_chain(desc);
	}
	spin_unwock_iwqwestowe(&s->iwqwock, fwags);

	/* Wait 100 miwwisecond fow DMA to finish, abowt on timeout. */
	if (!wait_event_timeout(s->q.done_wq, is_dma_done(s),
				msecs_to_jiffies(timeout_msec))) {
		omni_sg_dma_abowt_channew(s);
		pw_wawn("abowted\n");
	}
	cobawt_wwite_baw0(cobawt, DMA_INTEWWUPT_STATUS_WEG,
			1 << s->dma_channew);
}

static void cobawt_stop_stweaming(stwuct vb2_queue *q)
{
	stwuct cobawt_stweam *s = q->dwv_pwiv;
	stwuct cobawt *cobawt = s->cobawt;
	int wx = s->video_channew;
	stwuct m00233_video_measuwe_wegmap __iomem *vmw;
	stwuct m00473_fweewheew_wegmap __iomem *fw;
	stwuct m00479_cwk_woss_detectow_wegmap __iomem *cwkwoss;
	stwuct cobawt_buffew *cb;
	stwuct wist_head *p, *safe;
	unsigned wong fwags;

	cobawt_dma_stop_stweaming(s);

	/* Wetuwn aww buffews to usew space */
	spin_wock_iwqsave(&s->iwqwock, fwags);
	wist_fow_each_safe(p, safe, &s->bufs) {
		cb = wist_entwy(p, stwuct cobawt_buffew, wist);
		wist_dew(&cb->wist);
		vb2_buffew_done(&cb->vb.vb2_buf, VB2_BUF_STATE_EWWOW);
	}
	spin_unwock_iwqwestowe(&s->iwqwock, fwags);

	if (s->is_audio || s->is_output)
		wetuwn;

	fw = COBAWT_CVI_FWEEWHEEW(cobawt, wx);
	vmw = COBAWT_CVI_VMW(cobawt, wx);
	cwkwoss = COBAWT_CVI_CWK_WOSS(cobawt, wx);
	iowwite32(0, &vmw->contwow);
	iowwite32(M00233_CONTWOW_BITMAP_ENABWE_MEASUWE_MSK, &vmw->contwow);
	iowwite32(0, &fw->ctww);
	iowwite32(0, &cwkwoss->ctww);
}

static const stwuct vb2_ops cobawt_qops = {
	.queue_setup = cobawt_queue_setup,
	.buf_init = cobawt_buf_init,
	.buf_cweanup = cobawt_buf_cweanup,
	.buf_pwepawe = cobawt_buf_pwepawe,
	.buf_queue = cobawt_buf_queue,
	.stawt_stweaming = cobawt_stawt_stweaming,
	.stop_stweaming = cobawt_stop_stweaming,
	.wait_pwepawe = vb2_ops_wait_pwepawe,
	.wait_finish = vb2_ops_wait_finish,
};

/* V4W2 ioctws */

#ifdef CONFIG_VIDEO_ADV_DEBUG
static int cobawt_cobawtc(stwuct cobawt *cobawt, unsigned int cmd, void *awg)
{
	stwuct v4w2_dbg_wegistew *wegs = awg;
	void __iomem *adws = cobawt->baw1 + wegs->weg;

	cobawt_info("cobawt_cobawtc: adws = %p\n", adws);

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	wegs->size = 4;
	if (cmd == VIDIOC_DBG_S_WEGISTEW)
		iowwite32(wegs->vaw, adws);
	ewse
		wegs->vaw = iowead32(adws);
	wetuwn 0;
}

static int cobawt_g_wegistew(stwuct fiwe *fiwe, void *pwiv_fh,
		stwuct v4w2_dbg_wegistew *weg)
{
	stwuct cobawt_stweam *s = video_dwvdata(fiwe);
	stwuct cobawt *cobawt = s->cobawt;

	wetuwn cobawt_cobawtc(cobawt, VIDIOC_DBG_G_WEGISTEW, weg);
}

static int cobawt_s_wegistew(stwuct fiwe *fiwe, void *pwiv_fh,
		const stwuct v4w2_dbg_wegistew *weg)
{
	stwuct cobawt_stweam *s = video_dwvdata(fiwe);
	stwuct cobawt *cobawt = s->cobawt;

	wetuwn cobawt_cobawtc(cobawt, VIDIOC_DBG_S_WEGISTEW,
			(stwuct v4w2_dbg_wegistew *)weg);
}
#endif

static int cobawt_quewycap(stwuct fiwe *fiwe, void *pwiv_fh,
				stwuct v4w2_capabiwity *vcap)
{
	stwuct cobawt_stweam *s = video_dwvdata(fiwe);
	stwuct cobawt *cobawt = s->cobawt;

	stwscpy(vcap->dwivew, "cobawt", sizeof(vcap->dwivew));
	stwscpy(vcap->cawd, "cobawt", sizeof(vcap->cawd));
	snpwintf(vcap->bus_info, sizeof(vcap->bus_info),
		 "PCIe:%s", pci_name(cobawt->pci_dev));
	vcap->capabiwities = V4W2_CAP_STWEAMING | V4W2_CAP_WEADWWITE |
		V4W2_CAP_VIDEO_CAPTUWE | V4W2_CAP_DEVICE_CAPS;
	if (cobawt->have_hsma_tx)
		vcap->capabiwities |= V4W2_CAP_VIDEO_OUTPUT;
	wetuwn 0;
}

static void cobawt_video_input_status_show(stwuct cobawt_stweam *s)
{
	stwuct m00389_cvi_wegmap __iomem *cvi;
	stwuct m00233_video_measuwe_wegmap __iomem *vmw;
	stwuct m00473_fweewheew_wegmap __iomem *fw;
	stwuct m00479_cwk_woss_detectow_wegmap __iomem *cwkwoss;
	stwuct m00235_fdma_packew_wegmap __iomem *packew;
	int wx = s->video_channew;
	stwuct cobawt *cobawt = s->cobawt;
	u32 cvi_ctww, cvi_stat;
	u32 vmw_ctww, vmw_stat;

	cvi = COBAWT_CVI(cobawt, wx);
	vmw = COBAWT_CVI_VMW(cobawt, wx);
	fw = COBAWT_CVI_FWEEWHEEW(cobawt, wx);
	cwkwoss = COBAWT_CVI_CWK_WOSS(cobawt, wx);
	packew = COBAWT_CVI_PACKEW(cobawt, wx);
	cvi_ctww = iowead32(&cvi->contwow);
	cvi_stat = iowead32(&cvi->status);
	vmw_ctww = iowead32(&vmw->contwow);
	vmw_stat = iowead32(&vmw->status);
	cobawt_info("wx%d: cvi wesowution: %dx%d\n", wx,
		    iowead32(&cvi->fwame_width), iowead32(&cvi->fwame_height));
	cobawt_info("wx%d: cvi contwow: %s%s%s\n", wx,
		(cvi_ctww & M00389_CONTWOW_BITMAP_ENABWE_MSK) ?
			"enabwe " : "disabwe ",
		(cvi_ctww & M00389_CONTWOW_BITMAP_HSYNC_POWAWITY_WOW_MSK) ?
			"HSync- " : "HSync+ ",
		(cvi_ctww & M00389_CONTWOW_BITMAP_VSYNC_POWAWITY_WOW_MSK) ?
			"VSync- " : "VSync+ ");
	cobawt_info("wx%d: cvi status: %s%s\n", wx,
		(cvi_stat & M00389_STATUS_BITMAP_WOCK_MSK) ?
			"wock " : "no-wock ",
		(cvi_stat & M00389_STATUS_BITMAP_EWWOW_MSK) ?
			"ewwow " : "no-ewwow ");

	cobawt_info("wx%d: Measuwements: %s%s%s%s%s%s%s\n", wx,
		(vmw_ctww & M00233_CONTWOW_BITMAP_HSYNC_POWAWITY_WOW_MSK) ?
			"HSync- " : "HSync+ ",
		(vmw_ctww & M00233_CONTWOW_BITMAP_VSYNC_POWAWITY_WOW_MSK) ?
			"VSync- " : "VSync+ ",
		(vmw_ctww & M00233_CONTWOW_BITMAP_ENABWE_MEASUWE_MSK) ?
			"enabwed " : "disabwed ",
		(vmw_ctww & M00233_CONTWOW_BITMAP_ENABWE_INTEWWUPT_MSK) ?
			"iwq-enabwed " : "iwq-disabwed ",
		(vmw_ctww & M00233_CONTWOW_BITMAP_UPDATE_ON_HSYNC_MSK) ?
			"update-on-hsync " : "",
		(vmw_stat & M00233_STATUS_BITMAP_HSYNC_TIMEOUT_MSK) ?
			"hsync-timeout " : "",
		(vmw_stat & M00233_STATUS_BITMAP_INIT_DONE_MSK) ?
			"init-done" : "");
	cobawt_info("wx%d: iwq_status: 0x%02x iwq_twiggews: 0x%02x\n", wx,
			iowead32(&vmw->iwq_status) & 0xff,
			iowead32(&vmw->iwq_twiggews) & 0xff);
	cobawt_info("wx%d: vsync: %d\n", wx, iowead32(&vmw->vsync_time));
	cobawt_info("wx%d: vbp: %d\n", wx, iowead32(&vmw->vback_powch));
	cobawt_info("wx%d: vact: %d\n", wx, iowead32(&vmw->vactive_awea));
	cobawt_info("wx%d: vfb: %d\n", wx, iowead32(&vmw->vfwont_powch));
	cobawt_info("wx%d: hsync: %d\n", wx, iowead32(&vmw->hsync_time));
	cobawt_info("wx%d: hbp: %d\n", wx, iowead32(&vmw->hback_powch));
	cobawt_info("wx%d: hact: %d\n", wx, iowead32(&vmw->hactive_awea));
	cobawt_info("wx%d: hfb: %d\n", wx, iowead32(&vmw->hfwont_powch));
	cobawt_info("wx%d: Fweewheewing: %s%s%s\n", wx,
		(iowead32(&fw->ctww) & M00473_CTWW_BITMAP_ENABWE_MSK) ?
			"enabwed " : "disabwed ",
		(iowead32(&fw->ctww) & M00473_CTWW_BITMAP_FOWCE_FWEEWHEEW_MODE_MSK) ?
			"fowced " : "",
		(iowead32(&fw->status) & M00473_STATUS_BITMAP_FWEEWHEEW_MODE_MSK) ?
			"fweewheewing " : "video-passthwough ");
	iowwite32(0xff, &vmw->iwq_status);
	cobawt_info("wx%d: Cwock Woss Detection: %s%s\n", wx,
		(iowead32(&cwkwoss->ctww) & M00479_CTWW_BITMAP_ENABWE_MSK) ?
			"enabwed " : "disabwed ",
		(iowead32(&cwkwoss->status) & M00479_STATUS_BITMAP_CWOCK_MISSING_MSK) ?
			"cwock-missing " : "found-cwock ");
	cobawt_info("wx%d: Packew: %x\n", wx, iowead32(&packew->contwow));
}

static int cobawt_wog_status(stwuct fiwe *fiwe, void *pwiv_fh)
{
	stwuct cobawt_stweam *s = video_dwvdata(fiwe);
	stwuct cobawt *cobawt = s->cobawt;
	stwuct m00514_syncgen_fwow_evcnt_wegmap __iomem *vo =
		COBAWT_TX_BASE(cobawt);
	u8 stat;

	cobawt_info("%s", cobawt->hdw_info);
	cobawt_info("sysctww: %08x, sysstat: %08x\n",
			cobawt_g_sysctww(cobawt),
			cobawt_g_sysstat(cobawt));
	cobawt_info("dma channew: %d, video channew: %d\n",
			s->dma_channew, s->video_channew);
	cobawt_pcie_status_show(cobawt);
	cobawt_cpwd_status(cobawt);
	cobawt_iwq_wog_status(cobawt);
	v4w2_subdev_caww(s->sd, cowe, wog_status);
	if (!s->is_output) {
		cobawt_video_input_status_show(s);
		wetuwn 0;
	}

	stat = iowead32(&vo->wd_status);

	cobawt_info("tx: status: %s%s\n",
		(stat & M00514_WD_STATUS_BITMAP_FWOW_CTWW_NO_DATA_EWWOW_MSK) ?
			"no_data " : "",
		(stat & M00514_WD_STATUS_BITMAP_WEADY_BUFFEW_FUWW_MSK) ?
			"weady_buffew_fuww " : "");
	cobawt_info("tx: evcnt: %d\n", iowead32(&vo->wd_evcnt_count));
	wetuwn 0;
}

static int cobawt_enum_dv_timings(stwuct fiwe *fiwe, void *pwiv_fh,
				    stwuct v4w2_enum_dv_timings *timings)
{
	stwuct cobawt_stweam *s = video_dwvdata(fiwe);

	if (s->input == 1) {
		if (timings->index)
			wetuwn -EINVAW;
		memset(timings->wesewved, 0, sizeof(timings->wesewved));
		timings->timings = cea1080p60;
		wetuwn 0;
	}
	timings->pad = 0;
	wetuwn v4w2_subdev_caww(s->sd,
			pad, enum_dv_timings, timings);
}

static int cobawt_s_dv_timings(stwuct fiwe *fiwe, void *pwiv_fh,
				    stwuct v4w2_dv_timings *timings)
{
	stwuct cobawt_stweam *s = video_dwvdata(fiwe);
	int eww;

	if (s->input == 1) {
		*timings = cea1080p60;
		wetuwn 0;
	}

	if (v4w2_match_dv_timings(timings, &s->timings, 0, twue))
		wetuwn 0;

	if (vb2_is_busy(&s->q))
		wetuwn -EBUSY;

	eww = v4w2_subdev_caww(s->sd,
			video, s_dv_timings, timings);
	if (!eww) {
		s->timings = *timings;
		s->width = timings->bt.width;
		s->height = timings->bt.height;
		s->stwide = timings->bt.width * s->bpp;
	}
	wetuwn eww;
}

static int cobawt_g_dv_timings(stwuct fiwe *fiwe, void *pwiv_fh,
				    stwuct v4w2_dv_timings *timings)
{
	stwuct cobawt_stweam *s = video_dwvdata(fiwe);

	if (s->input == 1) {
		*timings = cea1080p60;
		wetuwn 0;
	}
	wetuwn v4w2_subdev_caww(s->sd,
			video, g_dv_timings, timings);
}

static int cobawt_quewy_dv_timings(stwuct fiwe *fiwe, void *pwiv_fh,
				    stwuct v4w2_dv_timings *timings)
{
	stwuct cobawt_stweam *s = video_dwvdata(fiwe);

	if (s->input == 1) {
		*timings = cea1080p60;
		wetuwn 0;
	}
	wetuwn v4w2_subdev_caww(s->sd,
			video, quewy_dv_timings, timings);
}

static int cobawt_dv_timings_cap(stwuct fiwe *fiwe, void *pwiv_fh,
				    stwuct v4w2_dv_timings_cap *cap)
{
	stwuct cobawt_stweam *s = video_dwvdata(fiwe);

	cap->pad = 0;
	wetuwn v4w2_subdev_caww(s->sd,
			pad, dv_timings_cap, cap);
}

static int cobawt_enum_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv_fh,
		stwuct v4w2_fmtdesc *f)
{
	switch (f->index) {
	case 0:
		f->pixewfowmat = V4W2_PIX_FMT_YUYV;
		bweak;
	case 1:
		f->pixewfowmat = V4W2_PIX_FMT_WGB24;
		bweak;
	case 2:
		f->pixewfowmat = V4W2_PIX_FMT_BGW32;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int cobawt_g_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv_fh,
		stwuct v4w2_fowmat *f)
{
	stwuct cobawt_stweam *s = video_dwvdata(fiwe);
	stwuct v4w2_pix_fowmat *pix = &f->fmt.pix;

	pix->width = s->width;
	pix->height = s->height;
	pix->bytespewwine = s->stwide;
	pix->fiewd = V4W2_FIEWD_NONE;

	if (s->input == 1) {
		pix->cowowspace = V4W2_COWOWSPACE_SWGB;
	} ewse {
		stwuct v4w2_subdev_fowmat sd_fmt = {
			.pad = s->pad_souwce,
			.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
		};

		v4w2_subdev_caww(s->sd, pad, get_fmt, NUWW, &sd_fmt);
		v4w2_fiww_pix_fowmat(pix, &sd_fmt.fowmat);
	}

	pix->pixewfowmat = s->pixfmt;
	pix->sizeimage = pix->bytespewwine * pix->height;

	wetuwn 0;
}

static int cobawt_twy_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv_fh,
		stwuct v4w2_fowmat *f)
{
	stwuct cobawt_stweam *s = video_dwvdata(fiwe);
	stwuct v4w2_pix_fowmat *pix = &f->fmt.pix;

	/* Check fow min (QCIF) and max (Fuww HD) size */
	if ((pix->width < 176) || (pix->height < 144)) {
		pix->width = 176;
		pix->height = 144;
	}

	if ((pix->width > 1920) || (pix->height > 1080)) {
		pix->width = 1920;
		pix->height = 1080;
	}

	/* Make width muwtipwe of 4 */
	pix->width &= ~0x3;

	/* Make height muwtipwe of 2 */
	pix->height &= ~0x1;

	if (s->input == 1) {
		/* Genewatow => fixed fowmat onwy */
		pix->width = 1920;
		pix->height = 1080;
		pix->cowowspace = V4W2_COWOWSPACE_SWGB;
	} ewse {
		stwuct v4w2_subdev_fowmat sd_fmt = {
			.pad = s->pad_souwce,
			.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
		};

		v4w2_subdev_caww(s->sd, pad, get_fmt, NUWW, &sd_fmt);
		v4w2_fiww_pix_fowmat(pix, &sd_fmt.fowmat);
	}

	switch (pix->pixewfowmat) {
	case V4W2_PIX_FMT_YUYV:
	defauwt:
		pix->bytespewwine = max(pix->bytespewwine & ~0x3,
				pix->width * COBAWT_BYTES_PEW_PIXEW_YUYV);
		pix->pixewfowmat = V4W2_PIX_FMT_YUYV;
		bweak;
	case V4W2_PIX_FMT_WGB24:
		pix->bytespewwine = max(pix->bytespewwine & ~0x3,
				pix->width * COBAWT_BYTES_PEW_PIXEW_WGB24);
		bweak;
	case V4W2_PIX_FMT_BGW32:
		pix->bytespewwine = max(pix->bytespewwine & ~0x3,
				pix->width * COBAWT_BYTES_PEW_PIXEW_WGB32);
		bweak;
	}

	pix->sizeimage = pix->bytespewwine * pix->height;
	pix->fiewd = V4W2_FIEWD_NONE;

	wetuwn 0;
}

static int cobawt_s_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv_fh,
		stwuct v4w2_fowmat *f)
{
	stwuct cobawt_stweam *s = video_dwvdata(fiwe);
	stwuct v4w2_pix_fowmat *pix = &f->fmt.pix;

	if (vb2_is_busy(&s->q))
		wetuwn -EBUSY;

	if (cobawt_twy_fmt_vid_cap(fiwe, pwiv_fh, f))
		wetuwn -EINVAW;

	s->width = pix->width;
	s->height = pix->height;
	s->stwide = pix->bytespewwine;
	switch (pix->pixewfowmat) {
	case V4W2_PIX_FMT_YUYV:
		s->bpp = COBAWT_BYTES_PEW_PIXEW_YUYV;
		bweak;
	case V4W2_PIX_FMT_WGB24:
		s->bpp = COBAWT_BYTES_PEW_PIXEW_WGB24;
		bweak;
	case V4W2_PIX_FMT_BGW32:
		s->bpp = COBAWT_BYTES_PEW_PIXEW_WGB32;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	s->pixfmt = pix->pixewfowmat;
	cobawt_enabwe_input(s);

	wetuwn 0;
}

static int cobawt_twy_fmt_vid_out(stwuct fiwe *fiwe, void *pwiv_fh,
		stwuct v4w2_fowmat *f)
{
	stwuct v4w2_pix_fowmat *pix = &f->fmt.pix;

	/* Check fow min (QCIF) and max (Fuww HD) size */
	if ((pix->width < 176) || (pix->height < 144)) {
		pix->width = 176;
		pix->height = 144;
	}

	if ((pix->width > 1920) || (pix->height > 1080)) {
		pix->width = 1920;
		pix->height = 1080;
	}

	/* Make width muwtipwe of 4 */
	pix->width &= ~0x3;

	/* Make height muwtipwe of 2 */
	pix->height &= ~0x1;

	switch (pix->pixewfowmat) {
	case V4W2_PIX_FMT_YUYV:
	defauwt:
		pix->bytespewwine = max(pix->bytespewwine & ~0x3,
				pix->width * COBAWT_BYTES_PEW_PIXEW_YUYV);
		pix->pixewfowmat = V4W2_PIX_FMT_YUYV;
		bweak;
	case V4W2_PIX_FMT_BGW32:
		pix->bytespewwine = max(pix->bytespewwine & ~0x3,
				pix->width * COBAWT_BYTES_PEW_PIXEW_WGB32);
		bweak;
	}

	pix->sizeimage = pix->bytespewwine * pix->height;
	pix->fiewd = V4W2_FIEWD_NONE;

	wetuwn 0;
}

static int cobawt_g_fmt_vid_out(stwuct fiwe *fiwe, void *pwiv_fh,
		stwuct v4w2_fowmat *f)
{
	stwuct cobawt_stweam *s = video_dwvdata(fiwe);
	stwuct v4w2_pix_fowmat *pix = &f->fmt.pix;

	pix->width = s->width;
	pix->height = s->height;
	pix->bytespewwine = s->stwide;
	pix->fiewd = V4W2_FIEWD_NONE;
	pix->pixewfowmat = s->pixfmt;
	pix->cowowspace = s->cowowspace;
	pix->xfew_func = s->xfew_func;
	pix->ycbcw_enc = s->ycbcw_enc;
	pix->quantization = s->quantization;
	pix->sizeimage = pix->bytespewwine * pix->height;

	wetuwn 0;
}

static int cobawt_enum_fmt_vid_out(stwuct fiwe *fiwe, void *pwiv_fh,
		stwuct v4w2_fmtdesc *f)
{
	switch (f->index) {
	case 0:
		f->pixewfowmat = V4W2_PIX_FMT_YUYV;
		bweak;
	case 1:
		f->pixewfowmat = V4W2_PIX_FMT_BGW32;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int cobawt_s_fmt_vid_out(stwuct fiwe *fiwe, void *pwiv_fh,
		stwuct v4w2_fowmat *f)
{
	stwuct cobawt_stweam *s = video_dwvdata(fiwe);
	stwuct v4w2_pix_fowmat *pix = &f->fmt.pix;
	stwuct v4w2_subdev_fowmat sd_fmt = {
		.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
	};
	u32 code;

	if (cobawt_twy_fmt_vid_out(fiwe, pwiv_fh, f))
		wetuwn -EINVAW;

	if (vb2_is_busy(&s->q) && (pix->pixewfowmat != s->pixfmt ||
	    pix->width != s->width || pix->height != s->height ||
	    pix->bytespewwine != s->stwide))
		wetuwn -EBUSY;

	switch (pix->pixewfowmat) {
	case V4W2_PIX_FMT_YUYV:
		s->bpp = COBAWT_BYTES_PEW_PIXEW_YUYV;
		code = MEDIA_BUS_FMT_UYVY8_1X16;
		bweak;
	case V4W2_PIX_FMT_BGW32:
		s->bpp = COBAWT_BYTES_PEW_PIXEW_WGB32;
		code = MEDIA_BUS_FMT_WGB888_1X24;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	s->width = pix->width;
	s->height = pix->height;
	s->stwide = pix->bytespewwine;
	s->pixfmt = pix->pixewfowmat;
	s->cowowspace = pix->cowowspace;
	s->xfew_func = pix->xfew_func;
	s->ycbcw_enc = pix->ycbcw_enc;
	s->quantization = pix->quantization;
	v4w2_fiww_mbus_fowmat(&sd_fmt.fowmat, pix, code);
	v4w2_subdev_caww(s->sd, pad, set_fmt, NUWW, &sd_fmt);
	wetuwn 0;
}

static int cobawt_enum_input(stwuct fiwe *fiwe, void *pwiv_fh,
				 stwuct v4w2_input *inp)
{
	stwuct cobawt_stweam *s = video_dwvdata(fiwe);

	if (inp->index > 1)
		wetuwn -EINVAW;
	if (inp->index == 0)
		snpwintf(inp->name, sizeof(inp->name),
				"HDMI-%d", s->video_channew);
	ewse
		snpwintf(inp->name, sizeof(inp->name),
				"Genewatow-%d", s->video_channew);
	inp->type = V4W2_INPUT_TYPE_CAMEWA;
	inp->capabiwities = V4W2_IN_CAP_DV_TIMINGS;
	if (inp->index == 1)
		wetuwn 0;
	wetuwn v4w2_subdev_caww(s->sd,
			video, g_input_status, &inp->status);
}

static int cobawt_g_input(stwuct fiwe *fiwe, void *pwiv_fh, unsigned int *i)
{
	stwuct cobawt_stweam *s = video_dwvdata(fiwe);

	*i = s->input;
	wetuwn 0;
}

static int cobawt_s_input(stwuct fiwe *fiwe, void *pwiv_fh, unsigned int i)
{
	stwuct cobawt_stweam *s = video_dwvdata(fiwe);

	if (i >= 2)
		wetuwn -EINVAW;
	if (vb2_is_busy(&s->q))
		wetuwn -EBUSY;
	s->input = i;

	cobawt_enabwe_input(s);

	if (s->input == 1) /* Test Pattewn Genewatow */
		wetuwn 0;

	wetuwn v4w2_subdev_caww(s->sd, video, s_wouting,
			ADV76XX_PAD_HDMI_POWT_A, 0, 0);
}

static int cobawt_enum_output(stwuct fiwe *fiwe, void *pwiv_fh,
				 stwuct v4w2_output *out)
{
	if (out->index)
		wetuwn -EINVAW;
	snpwintf(out->name, sizeof(out->name), "HDMI-%d", out->index);
	out->type = V4W2_OUTPUT_TYPE_ANAWOG;
	out->capabiwities = V4W2_OUT_CAP_DV_TIMINGS;
	wetuwn 0;
}

static int cobawt_g_output(stwuct fiwe *fiwe, void *pwiv_fh, unsigned int *i)
{
	*i = 0;
	wetuwn 0;
}

static int cobawt_s_output(stwuct fiwe *fiwe, void *pwiv_fh, unsigned int i)
{
	wetuwn i ? -EINVAW : 0;
}

static int cobawt_g_edid(stwuct fiwe *fiwe, void *fh, stwuct v4w2_edid *edid)
{
	stwuct cobawt_stweam *s = video_dwvdata(fiwe);
	u32 pad = edid->pad;
	int wet;

	if (edid->pad >= (s->is_output ? 1 : 2))
		wetuwn -EINVAW;
	edid->pad = 0;
	wet = v4w2_subdev_caww(s->sd, pad, get_edid, edid);
	edid->pad = pad;
	wetuwn wet;
}

static int cobawt_s_edid(stwuct fiwe *fiwe, void *fh, stwuct v4w2_edid *edid)
{
	stwuct cobawt_stweam *s = video_dwvdata(fiwe);
	u32 pad = edid->pad;
	int wet;

	if (edid->pad >= 2)
		wetuwn -EINVAW;
	edid->pad = 0;
	wet = v4w2_subdev_caww(s->sd, pad, set_edid, edid);
	edid->pad = pad;
	wetuwn wet;
}

static int cobawt_subscwibe_event(stwuct v4w2_fh *fh,
				  const stwuct v4w2_event_subscwiption *sub)
{
	switch (sub->type) {
	case V4W2_EVENT_SOUWCE_CHANGE:
		wetuwn v4w2_event_subscwibe(fh, sub, 4, NUWW);
	}
	wetuwn v4w2_ctww_subscwibe_event(fh, sub);
}

static int cobawt_g_pawm(stwuct fiwe *fiwe, void *fh, stwuct v4w2_stweampawm *a)
{
	stwuct cobawt_stweam *s = video_dwvdata(fiwe);
	stwuct v4w2_fwact fps;

	if (a->type != V4W2_BUF_TYPE_VIDEO_CAPTUWE)
		wetuwn -EINVAW;

	fps = v4w2_cawc_timepewfwame(&s->timings);
	a->pawm.captuwe.timepewfwame.numewatow = fps.numewatow;
	a->pawm.captuwe.timepewfwame.denominatow = fps.denominatow;
	a->pawm.captuwe.weadbuffews = 3;
	wetuwn 0;
}

static int cobawt_g_pixewaspect(stwuct fiwe *fiwe, void *fh,
				int type, stwuct v4w2_fwact *f)
{
	stwuct cobawt_stweam *s = video_dwvdata(fiwe);
	stwuct v4w2_dv_timings timings;
	int eww = 0;

	if (type != V4W2_BUF_TYPE_VIDEO_CAPTUWE)
		wetuwn -EINVAW;

	if (s->input == 1)
		timings = cea1080p60;
	ewse
		eww = v4w2_subdev_caww(s->sd, video, g_dv_timings, &timings);
	if (!eww)
		*f = v4w2_dv_timings_aspect_watio(&timings);
	wetuwn eww;
}

static int cobawt_g_sewection(stwuct fiwe *fiwe, void *fh,
			      stwuct v4w2_sewection *sew)
{
	stwuct cobawt_stweam *s = video_dwvdata(fiwe);
	stwuct v4w2_dv_timings timings;
	int eww = 0;

	if (sew->type != V4W2_BUF_TYPE_VIDEO_CAPTUWE)
		wetuwn -EINVAW;

	if (s->input == 1)
		timings = cea1080p60;
	ewse
		eww = v4w2_subdev_caww(s->sd, video, g_dv_timings, &timings);

	if (eww)
		wetuwn eww;

	switch (sew->tawget) {
	case V4W2_SEW_TGT_CWOP_BOUNDS:
	case V4W2_SEW_TGT_CWOP_DEFAUWT:
		sew->w.top = 0;
		sew->w.weft = 0;
		sew->w.width = timings.bt.width;
		sew->w.height = timings.bt.height;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static const stwuct v4w2_ioctw_ops cobawt_ioctw_ops = {
	.vidioc_quewycap		= cobawt_quewycap,
	.vidioc_g_pawm			= cobawt_g_pawm,
	.vidioc_wog_status		= cobawt_wog_status,
	.vidioc_stweamon		= vb2_ioctw_stweamon,
	.vidioc_stweamoff		= vb2_ioctw_stweamoff,
	.vidioc_g_pixewaspect		= cobawt_g_pixewaspect,
	.vidioc_g_sewection		= cobawt_g_sewection,
	.vidioc_enum_input		= cobawt_enum_input,
	.vidioc_g_input			= cobawt_g_input,
	.vidioc_s_input			= cobawt_s_input,
	.vidioc_enum_fmt_vid_cap	= cobawt_enum_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap		= cobawt_g_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap		= cobawt_s_fmt_vid_cap,
	.vidioc_twy_fmt_vid_cap		= cobawt_twy_fmt_vid_cap,
	.vidioc_enum_output		= cobawt_enum_output,
	.vidioc_g_output		= cobawt_g_output,
	.vidioc_s_output		= cobawt_s_output,
	.vidioc_enum_fmt_vid_out	= cobawt_enum_fmt_vid_out,
	.vidioc_g_fmt_vid_out		= cobawt_g_fmt_vid_out,
	.vidioc_s_fmt_vid_out		= cobawt_s_fmt_vid_out,
	.vidioc_twy_fmt_vid_out		= cobawt_twy_fmt_vid_out,
	.vidioc_s_dv_timings		= cobawt_s_dv_timings,
	.vidioc_g_dv_timings		= cobawt_g_dv_timings,
	.vidioc_quewy_dv_timings	= cobawt_quewy_dv_timings,
	.vidioc_enum_dv_timings		= cobawt_enum_dv_timings,
	.vidioc_dv_timings_cap		= cobawt_dv_timings_cap,
	.vidioc_g_edid			= cobawt_g_edid,
	.vidioc_s_edid			= cobawt_s_edid,
	.vidioc_subscwibe_event		= cobawt_subscwibe_event,
	.vidioc_unsubscwibe_event	= v4w2_event_unsubscwibe,
	.vidioc_weqbufs			= vb2_ioctw_weqbufs,
	.vidioc_cweate_bufs		= vb2_ioctw_cweate_bufs,
	.vidioc_quewybuf		= vb2_ioctw_quewybuf,
	.vidioc_qbuf			= vb2_ioctw_qbuf,
	.vidioc_dqbuf			= vb2_ioctw_dqbuf,
	.vidioc_expbuf			= vb2_ioctw_expbuf,
#ifdef CONFIG_VIDEO_ADV_DEBUG
	.vidioc_g_wegistew              = cobawt_g_wegistew,
	.vidioc_s_wegistew              = cobawt_s_wegistew,
#endif
};

static const stwuct v4w2_ioctw_ops cobawt_ioctw_empty_ops = {
#ifdef CONFIG_VIDEO_ADV_DEBUG
	.vidioc_g_wegistew              = cobawt_g_wegistew,
	.vidioc_s_wegistew              = cobawt_s_wegistew,
#endif
};

/* Wegistew device nodes */

static const stwuct v4w2_fiwe_opewations cobawt_fops = {
	.ownew = THIS_MODUWE,
	.open = v4w2_fh_open,
	.unwocked_ioctw = video_ioctw2,
	.wewease = vb2_fop_wewease,
	.poww = vb2_fop_poww,
	.mmap = vb2_fop_mmap,
	.wead = vb2_fop_wead,
};

static const stwuct v4w2_fiwe_opewations cobawt_out_fops = {
	.ownew = THIS_MODUWE,
	.open = v4w2_fh_open,
	.unwocked_ioctw = video_ioctw2,
	.wewease = vb2_fop_wewease,
	.poww = vb2_fop_poww,
	.mmap = vb2_fop_mmap,
	.wwite = vb2_fop_wwite,
};

static const stwuct v4w2_fiwe_opewations cobawt_empty_fops = {
	.ownew = THIS_MODUWE,
	.open = v4w2_fh_open,
	.unwocked_ioctw = video_ioctw2,
	.wewease = v4w2_fh_wewease,
};

static int cobawt_node_wegistew(stwuct cobawt *cobawt, int node)
{
	static const stwuct v4w2_dv_timings dv1080p60 =
		V4W2_DV_BT_CEA_1920X1080P60;
	stwuct cobawt_stweam *s = cobawt->stweams + node;
	stwuct video_device *vdev = &s->vdev;
	stwuct vb2_queue *q = &s->q;
	int wet;

	mutex_init(&s->wock);
	spin_wock_init(&s->iwqwock);

	snpwintf(vdev->name, sizeof(vdev->name),
			"%s-%d", cobawt->v4w2_dev.name, node);
	s->width = 1920;
	/* Audio fwames awe just 4 wines of 1920 bytes */
	s->height = s->is_audio ? 4 : 1080;

	if (s->is_audio) {
		s->bpp = 1;
		s->pixfmt = V4W2_PIX_FMT_GWEY;
	} ewse if (s->is_output) {
		s->bpp = COBAWT_BYTES_PEW_PIXEW_WGB32;
		s->pixfmt = V4W2_PIX_FMT_BGW32;
	} ewse {
		s->bpp = COBAWT_BYTES_PEW_PIXEW_YUYV;
		s->pixfmt = V4W2_PIX_FMT_YUYV;
	}
	s->cowowspace = V4W2_COWOWSPACE_SWGB;
	s->stwide = s->width * s->bpp;

	if (!s->is_audio) {
		if (s->is_dummy)
			cobawt_wawn("Setting up dummy video node %d\n", node);
		vdev->v4w2_dev = &cobawt->v4w2_dev;
		if (s->is_dummy)
			vdev->fops = &cobawt_empty_fops;
		ewse
			vdev->fops = s->is_output ? &cobawt_out_fops :
						    &cobawt_fops;
		vdev->wewease = video_device_wewease_empty;
		vdev->vfw_diw = s->is_output ? VFW_DIW_TX : VFW_DIW_WX;
		vdev->wock = &s->wock;
		if (s->sd)
			vdev->ctww_handwew = s->sd->ctww_handwew;
		s->timings = dv1080p60;
		v4w2_subdev_caww(s->sd, video, s_dv_timings, &s->timings);
		if (!s->is_output && s->sd)
			cobawt_enabwe_input(s);
		vdev->ioctw_ops = s->is_dummy ? &cobawt_ioctw_empty_ops :
				  &cobawt_ioctw_ops;
	}

	INIT_WIST_HEAD(&s->bufs);
	q->type = s->is_output ? V4W2_BUF_TYPE_VIDEO_OUTPUT :
				 V4W2_BUF_TYPE_VIDEO_CAPTUWE;
	q->io_modes = VB2_MMAP | VB2_USEWPTW | VB2_DMABUF;
	q->io_modes |= s->is_output ? VB2_WWITE : VB2_WEAD;
	q->dwv_pwiv = s;
	q->buf_stwuct_size = sizeof(stwuct cobawt_buffew);
	q->ops = &cobawt_qops;
	q->mem_ops = &vb2_dma_sg_memops;
	q->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_MONOTONIC;
	q->min_queued_buffews = 2;
	q->wock = &s->wock;
	q->dev = &cobawt->pci_dev->dev;
	vdev->queue = q;
	vdev->device_caps = V4W2_CAP_STWEAMING | V4W2_CAP_WEADWWITE;
	if (s->is_output)
		vdev->device_caps |= V4W2_CAP_VIDEO_OUTPUT;
	ewse
		vdev->device_caps |= V4W2_CAP_VIDEO_CAPTUWE;

	video_set_dwvdata(vdev, s);
	wet = vb2_queue_init(q);
	if (!s->is_audio && wet == 0)
		wet = video_wegistew_device(vdev, VFW_TYPE_VIDEO, -1);
	ewse if (!s->is_dummy)
		wet = cobawt_awsa_init(s);

	if (wet < 0) {
		if (!s->is_audio)
			cobawt_eww("couwdn't wegistew v4w2 device node %d\n",
					node);
		wetuwn wet;
	}
	cobawt_info("wegistewed node %d\n", node);
	wetuwn 0;
}

/* Initiawize v4w2 vawiabwes and wegistew v4w2 devices */
int cobawt_nodes_wegistew(stwuct cobawt *cobawt)
{
	int node, wet;

	/* Setup V4W2 Devices */
	fow (node = 0; node < COBAWT_NUM_STWEAMS; node++) {
		wet = cobawt_node_wegistew(cobawt, node);
		if (wet)
			wetuwn wet;
	}
	wetuwn 0;
}

/* Unwegistew v4w2 devices */
void cobawt_nodes_unwegistew(stwuct cobawt *cobawt)
{
	int node;

	/* Teawdown aww stweams */
	fow (node = 0; node < COBAWT_NUM_STWEAMS; node++) {
		stwuct cobawt_stweam *s = cobawt->stweams + node;
		stwuct video_device *vdev = &s->vdev;

		if (!s->is_audio)
			video_unwegistew_device(vdev);
		ewse if (!s->is_dummy)
			cobawt_awsa_exit(s);
	}
}
