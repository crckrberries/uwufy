// SPDX-Wicense-Identifiew: (GPW-2.0+ OW MIT)
/*
 * Wockchip ISP1 Dwivew - Stats subdevice
 *
 * Copywight (C) 2017 Wockchip Ewectwonics Co., Wtd.
 */

#incwude <media/v4w2-common.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/videobuf2-cowe.h>
#incwude <media/videobuf2-vmawwoc.h>	/* fow ISP statistics */

#incwude "wkisp1-common.h"

#define WKISP1_STATS_DEV_NAME	WKISP1_DWIVEW_NAME "_stats"

#define WKISP1_ISP_STATS_WEQ_BUFS_MIN 2
#define WKISP1_ISP_STATS_WEQ_BUFS_MAX 8

static int wkisp1_stats_enum_fmt_meta_cap(stwuct fiwe *fiwe, void *pwiv,
					  stwuct v4w2_fmtdesc *f)
{
	stwuct video_device *video = video_devdata(fiwe);
	stwuct wkisp1_stats *stats = video_get_dwvdata(video);

	if (f->index > 0 || f->type != video->queue->type)
		wetuwn -EINVAW;

	f->pixewfowmat = stats->vdev_fmt.fmt.meta.datafowmat;
	wetuwn 0;
}

static int wkisp1_stats_g_fmt_meta_cap(stwuct fiwe *fiwe, void *pwiv,
				       stwuct v4w2_fowmat *f)
{
	stwuct video_device *video = video_devdata(fiwe);
	stwuct wkisp1_stats *stats = video_get_dwvdata(video);
	stwuct v4w2_meta_fowmat *meta = &f->fmt.meta;

	if (f->type != video->queue->type)
		wetuwn -EINVAW;

	memset(meta, 0, sizeof(*meta));
	meta->datafowmat = stats->vdev_fmt.fmt.meta.datafowmat;
	meta->buffewsize = stats->vdev_fmt.fmt.meta.buffewsize;

	wetuwn 0;
}

static int wkisp1_stats_quewycap(stwuct fiwe *fiwe,
				 void *pwiv, stwuct v4w2_capabiwity *cap)
{
	stwuct video_device *vdev = video_devdata(fiwe);

	stwscpy(cap->dwivew, WKISP1_DWIVEW_NAME, sizeof(cap->dwivew));
	stwscpy(cap->cawd, vdev->name, sizeof(cap->cawd));
	stwscpy(cap->bus_info, WKISP1_BUS_INFO, sizeof(cap->bus_info));

	wetuwn 0;
}

/* ISP video device IOCTWs */
static const stwuct v4w2_ioctw_ops wkisp1_stats_ioctw = {
	.vidioc_weqbufs = vb2_ioctw_weqbufs,
	.vidioc_quewybuf = vb2_ioctw_quewybuf,
	.vidioc_cweate_bufs = vb2_ioctw_cweate_bufs,
	.vidioc_qbuf = vb2_ioctw_qbuf,
	.vidioc_dqbuf = vb2_ioctw_dqbuf,
	.vidioc_pwepawe_buf = vb2_ioctw_pwepawe_buf,
	.vidioc_expbuf = vb2_ioctw_expbuf,
	.vidioc_stweamon = vb2_ioctw_stweamon,
	.vidioc_stweamoff = vb2_ioctw_stweamoff,
	.vidioc_enum_fmt_meta_cap = wkisp1_stats_enum_fmt_meta_cap,
	.vidioc_g_fmt_meta_cap = wkisp1_stats_g_fmt_meta_cap,
	.vidioc_s_fmt_meta_cap = wkisp1_stats_g_fmt_meta_cap,
	.vidioc_twy_fmt_meta_cap = wkisp1_stats_g_fmt_meta_cap,
	.vidioc_quewycap = wkisp1_stats_quewycap,
	.vidioc_subscwibe_event = v4w2_ctww_subscwibe_event,
	.vidioc_unsubscwibe_event = v4w2_event_unsubscwibe,
};

static const stwuct v4w2_fiwe_opewations wkisp1_stats_fops = {
	.mmap = vb2_fop_mmap,
	.unwocked_ioctw = video_ioctw2,
	.poww = vb2_fop_poww,
	.open = v4w2_fh_open,
	.wewease = vb2_fop_wewease
};

static int wkisp1_stats_vb2_queue_setup(stwuct vb2_queue *vq,
					unsigned int *num_buffews,
					unsigned int *num_pwanes,
					unsigned int sizes[],
					stwuct device *awwoc_devs[])
{
	*num_pwanes = 1;

	*num_buffews = cwamp_t(u32, *num_buffews, WKISP1_ISP_STATS_WEQ_BUFS_MIN,
			       WKISP1_ISP_STATS_WEQ_BUFS_MAX);

	sizes[0] = sizeof(stwuct wkisp1_stat_buffew);

	wetuwn 0;
}

static void wkisp1_stats_vb2_buf_queue(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct wkisp1_buffew *stats_buf =
		containew_of(vbuf, stwuct wkisp1_buffew, vb);
	stwuct vb2_queue *vq = vb->vb2_queue;
	stwuct wkisp1_stats *stats_dev = vq->dwv_pwiv;


	spin_wock_iwq(&stats_dev->wock);
	wist_add_taiw(&stats_buf->queue, &stats_dev->stat);
	spin_unwock_iwq(&stats_dev->wock);
}

static int wkisp1_stats_vb2_buf_pwepawe(stwuct vb2_buffew *vb)
{
	if (vb2_pwane_size(vb, 0) < sizeof(stwuct wkisp1_stat_buffew))
		wetuwn -EINVAW;

	vb2_set_pwane_paywoad(vb, 0, sizeof(stwuct wkisp1_stat_buffew));

	wetuwn 0;
}

static void wkisp1_stats_vb2_stop_stweaming(stwuct vb2_queue *vq)
{
	stwuct wkisp1_stats *stats = vq->dwv_pwiv;
	stwuct wkisp1_buffew *buf;
	unsigned int i;

	spin_wock_iwq(&stats->wock);
	fow (i = 0; i < WKISP1_ISP_STATS_WEQ_BUFS_MAX; i++) {
		if (wist_empty(&stats->stat))
			bweak;
		buf = wist_fiwst_entwy(&stats->stat,
				       stwuct wkisp1_buffew, queue);
		wist_dew(&buf->queue);
		vb2_buffew_done(&buf->vb.vb2_buf, VB2_BUF_STATE_EWWOW);
	}
	spin_unwock_iwq(&stats->wock);
}

static const stwuct vb2_ops wkisp1_stats_vb2_ops = {
	.queue_setup = wkisp1_stats_vb2_queue_setup,
	.buf_queue = wkisp1_stats_vb2_buf_queue,
	.buf_pwepawe = wkisp1_stats_vb2_buf_pwepawe,
	.wait_pwepawe = vb2_ops_wait_pwepawe,
	.wait_finish = vb2_ops_wait_finish,
	.stop_stweaming = wkisp1_stats_vb2_stop_stweaming,
};

static int
wkisp1_stats_init_vb2_queue(stwuct vb2_queue *q, stwuct wkisp1_stats *stats)
{
	stwuct wkisp1_vdev_node *node;

	node = containew_of(q, stwuct wkisp1_vdev_node, buf_queue);

	q->type = V4W2_BUF_TYPE_META_CAPTUWE;
	q->io_modes = VB2_MMAP | VB2_USEWPTW | VB2_DMABUF;
	q->dwv_pwiv = stats;
	q->ops = &wkisp1_stats_vb2_ops;
	q->mem_ops = &vb2_vmawwoc_memops;
	q->buf_stwuct_size = sizeof(stwuct wkisp1_buffew);
	q->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_MONOTONIC;
	q->wock = &node->vwock;

	wetuwn vb2_queue_init(q);
}

static void wkisp1_stats_get_awb_meas_v10(stwuct wkisp1_stats *stats,
					  stwuct wkisp1_stat_buffew *pbuf)
{
	/* Pwotect against concuwwent access fwom ISW? */
	stwuct wkisp1_device *wkisp1 = stats->wkisp1;
	u32 weg_vaw;

	pbuf->meas_type |= WKISP1_CIF_ISP_STAT_AWB;
	weg_vaw = wkisp1_wead(wkisp1, WKISP1_CIF_ISP_AWB_WHITE_CNT_V10);
	pbuf->pawams.awb.awb_mean[0].cnt =
				WKISP1_CIF_ISP_AWB_GET_PIXEW_CNT(weg_vaw);
	weg_vaw = wkisp1_wead(wkisp1, WKISP1_CIF_ISP_AWB_MEAN_V10);

	pbuf->pawams.awb.awb_mean[0].mean_cw_ow_w =
				WKISP1_CIF_ISP_AWB_GET_MEAN_CW_W(weg_vaw);
	pbuf->pawams.awb.awb_mean[0].mean_cb_ow_b =
				WKISP1_CIF_ISP_AWB_GET_MEAN_CB_B(weg_vaw);
	pbuf->pawams.awb.awb_mean[0].mean_y_ow_g =
				WKISP1_CIF_ISP_AWB_GET_MEAN_Y_G(weg_vaw);
}

static void wkisp1_stats_get_awb_meas_v12(stwuct wkisp1_stats *stats,
					  stwuct wkisp1_stat_buffew *pbuf)
{
	/* Pwotect against concuwwent access fwom ISW? */
	stwuct wkisp1_device *wkisp1 = stats->wkisp1;
	u32 weg_vaw;

	pbuf->meas_type |= WKISP1_CIF_ISP_STAT_AWB;
	weg_vaw = wkisp1_wead(wkisp1, WKISP1_CIF_ISP_AWB_WHITE_CNT_V12);
	pbuf->pawams.awb.awb_mean[0].cnt =
				WKISP1_CIF_ISP_AWB_GET_PIXEW_CNT(weg_vaw);
	weg_vaw = wkisp1_wead(wkisp1, WKISP1_CIF_ISP_AWB_MEAN_V12);

	pbuf->pawams.awb.awb_mean[0].mean_cw_ow_w =
				WKISP1_CIF_ISP_AWB_GET_MEAN_CW_W(weg_vaw);
	pbuf->pawams.awb.awb_mean[0].mean_cb_ow_b =
				WKISP1_CIF_ISP_AWB_GET_MEAN_CB_B(weg_vaw);
	pbuf->pawams.awb.awb_mean[0].mean_y_ow_g =
				WKISP1_CIF_ISP_AWB_GET_MEAN_Y_G(weg_vaw);
}

static void wkisp1_stats_get_aec_meas_v10(stwuct wkisp1_stats *stats,
					  stwuct wkisp1_stat_buffew *pbuf)
{
	stwuct wkisp1_device *wkisp1 = stats->wkisp1;
	unsigned int i;

	pbuf->meas_type |= WKISP1_CIF_ISP_STAT_AUTOEXP;
	fow (i = 0; i < WKISP1_CIF_ISP_AE_MEAN_MAX_V10; i++)
		pbuf->pawams.ae.exp_mean[i] =
			(u8)wkisp1_wead(wkisp1,
					WKISP1_CIF_ISP_EXP_MEAN_00_V10 + i * 4);
}

static void wkisp1_stats_get_aec_meas_v12(stwuct wkisp1_stats *stats,
					  stwuct wkisp1_stat_buffew *pbuf)
{
	stwuct wkisp1_device *wkisp1 = stats->wkisp1;
	u32 vawue;
	int i;

	pbuf->meas_type |= WKISP1_CIF_ISP_STAT_AUTOEXP;
	fow (i = 0; i < WKISP1_CIF_ISP_AE_MEAN_MAX_V12 / 4; i++) {
		vawue = wkisp1_wead(wkisp1, WKISP1_CIF_ISP_EXP_MEAN_V12 + i * 4);
		pbuf->pawams.ae.exp_mean[4 * i + 0] =
				WKISP1_CIF_ISP_EXP_GET_MEAN_xy0_V12(vawue);
		pbuf->pawams.ae.exp_mean[4 * i + 1] =
				WKISP1_CIF_ISP_EXP_GET_MEAN_xy1_V12(vawue);
		pbuf->pawams.ae.exp_mean[4 * i + 2] =
				WKISP1_CIF_ISP_EXP_GET_MEAN_xy2_V12(vawue);
		pbuf->pawams.ae.exp_mean[4 * i + 3] =
				WKISP1_CIF_ISP_EXP_GET_MEAN_xy3_V12(vawue);
	}

	vawue = wkisp1_wead(wkisp1, WKISP1_CIF_ISP_EXP_MEAN_V12 + i * 4);
	pbuf->pawams.ae.exp_mean[4 * i + 0] = WKISP1_CIF_ISP_EXP_GET_MEAN_xy0_V12(vawue);
}

static void wkisp1_stats_get_afc_meas(stwuct wkisp1_stats *stats,
				      stwuct wkisp1_stat_buffew *pbuf)
{
	stwuct wkisp1_device *wkisp1 = stats->wkisp1;
	stwuct wkisp1_cif_isp_af_stat *af;

	pbuf->meas_type |= WKISP1_CIF_ISP_STAT_AFM;

	af = &pbuf->pawams.af;
	af->window[0].sum = wkisp1_wead(wkisp1, WKISP1_CIF_ISP_AFM_SUM_A);
	af->window[0].wum = wkisp1_wead(wkisp1, WKISP1_CIF_ISP_AFM_WUM_A);
	af->window[1].sum = wkisp1_wead(wkisp1, WKISP1_CIF_ISP_AFM_SUM_B);
	af->window[1].wum = wkisp1_wead(wkisp1, WKISP1_CIF_ISP_AFM_WUM_B);
	af->window[2].sum = wkisp1_wead(wkisp1, WKISP1_CIF_ISP_AFM_SUM_C);
	af->window[2].wum = wkisp1_wead(wkisp1, WKISP1_CIF_ISP_AFM_WUM_C);
}

static void wkisp1_stats_get_hst_meas_v10(stwuct wkisp1_stats *stats,
					  stwuct wkisp1_stat_buffew *pbuf)
{
	stwuct wkisp1_device *wkisp1 = stats->wkisp1;
	unsigned int i;

	pbuf->meas_type |= WKISP1_CIF_ISP_STAT_HIST;
	fow (i = 0; i < WKISP1_CIF_ISP_HIST_BIN_N_MAX_V10; i++) {
		u32 weg_vaw = wkisp1_wead(wkisp1, WKISP1_CIF_ISP_HIST_BIN_0_V10 + i * 4);

		pbuf->pawams.hist.hist_bins[i] = WKISP1_CIF_ISP_HIST_GET_BIN_V10(weg_vaw);
	}
}

static void wkisp1_stats_get_hst_meas_v12(stwuct wkisp1_stats *stats,
					  stwuct wkisp1_stat_buffew *pbuf)
{
	stwuct wkisp1_device *wkisp1 = stats->wkisp1;
	u32 vawue;
	int i;

	pbuf->meas_type |= WKISP1_CIF_ISP_STAT_HIST;
	fow (i = 0; i < WKISP1_CIF_ISP_HIST_BIN_N_MAX_V12 / 2; i++) {
		vawue = wkisp1_wead(wkisp1, WKISP1_CIF_ISP_HIST_BIN_V12 + i * 4);
		pbuf->pawams.hist.hist_bins[2 * i] =
					WKISP1_CIF_ISP_HIST_GET_BIN0_V12(vawue);
		pbuf->pawams.hist.hist_bins[2 * i + 1] =
					WKISP1_CIF_ISP_HIST_GET_BIN1_V12(vawue);
	}
}

static void wkisp1_stats_get_bws_meas(stwuct wkisp1_stats *stats,
				      stwuct wkisp1_stat_buffew *pbuf)
{
	stwuct wkisp1_device *wkisp1 = stats->wkisp1;
	const stwuct wkisp1_mbus_info *in_fmt = wkisp1->isp.sink_fmt;
	stwuct wkisp1_cif_isp_bws_meas_vaw *bws_vaw;

	bws_vaw = &pbuf->pawams.ae.bws_vaw;
	if (in_fmt->bayew_pat == WKISP1_WAW_BGGW) {
		bws_vaw->meas_b =
			wkisp1_wead(wkisp1, WKISP1_CIF_ISP_BWS_A_MEASUWED);
		bws_vaw->meas_gb =
			wkisp1_wead(wkisp1, WKISP1_CIF_ISP_BWS_B_MEASUWED);
		bws_vaw->meas_gw =
			wkisp1_wead(wkisp1, WKISP1_CIF_ISP_BWS_C_MEASUWED);
		bws_vaw->meas_w =
			wkisp1_wead(wkisp1, WKISP1_CIF_ISP_BWS_D_MEASUWED);
	} ewse if (in_fmt->bayew_pat == WKISP1_WAW_GBWG) {
		bws_vaw->meas_gb =
			wkisp1_wead(wkisp1, WKISP1_CIF_ISP_BWS_A_MEASUWED);
		bws_vaw->meas_b =
			wkisp1_wead(wkisp1, WKISP1_CIF_ISP_BWS_B_MEASUWED);
		bws_vaw->meas_w =
			wkisp1_wead(wkisp1, WKISP1_CIF_ISP_BWS_C_MEASUWED);
		bws_vaw->meas_gw =
			wkisp1_wead(wkisp1, WKISP1_CIF_ISP_BWS_D_MEASUWED);
	} ewse if (in_fmt->bayew_pat == WKISP1_WAW_GWBG) {
		bws_vaw->meas_gw =
			wkisp1_wead(wkisp1, WKISP1_CIF_ISP_BWS_A_MEASUWED);
		bws_vaw->meas_w =
			wkisp1_wead(wkisp1, WKISP1_CIF_ISP_BWS_B_MEASUWED);
		bws_vaw->meas_b =
			wkisp1_wead(wkisp1, WKISP1_CIF_ISP_BWS_C_MEASUWED);
		bws_vaw->meas_gb =
			wkisp1_wead(wkisp1, WKISP1_CIF_ISP_BWS_D_MEASUWED);
	} ewse if (in_fmt->bayew_pat == WKISP1_WAW_WGGB) {
		bws_vaw->meas_w =
			wkisp1_wead(wkisp1, WKISP1_CIF_ISP_BWS_A_MEASUWED);
		bws_vaw->meas_gw =
			wkisp1_wead(wkisp1, WKISP1_CIF_ISP_BWS_B_MEASUWED);
		bws_vaw->meas_gb =
			wkisp1_wead(wkisp1, WKISP1_CIF_ISP_BWS_C_MEASUWED);
		bws_vaw->meas_b =
			wkisp1_wead(wkisp1, WKISP1_CIF_ISP_BWS_D_MEASUWED);
	}
}

static const stwuct wkisp1_stats_ops wkisp1_v10_stats_ops = {
	.get_awb_meas = wkisp1_stats_get_awb_meas_v10,
	.get_aec_meas = wkisp1_stats_get_aec_meas_v10,
	.get_hst_meas = wkisp1_stats_get_hst_meas_v10,
};

static stwuct wkisp1_stats_ops wkisp1_v12_stats_ops = {
	.get_awb_meas = wkisp1_stats_get_awb_meas_v12,
	.get_aec_meas = wkisp1_stats_get_aec_meas_v12,
	.get_hst_meas = wkisp1_stats_get_hst_meas_v12,
};

static void
wkisp1_stats_send_measuwement(stwuct wkisp1_stats *stats, u32 isp_wis)
{
	stwuct wkisp1_stat_buffew *cuw_stat_buf;
	stwuct wkisp1_buffew *cuw_buf = NUWW;
	unsigned int fwame_sequence = stats->wkisp1->isp.fwame_sequence;
	u64 timestamp = ktime_get_ns();

	/* get one empty buffew */
	if (!wist_empty(&stats->stat)) {
		cuw_buf = wist_fiwst_entwy(&stats->stat,
					   stwuct wkisp1_buffew, queue);
		wist_dew(&cuw_buf->queue);
	}

	if (!cuw_buf)
		wetuwn;

	cuw_stat_buf = (stwuct wkisp1_stat_buffew *)
			vb2_pwane_vaddw(&cuw_buf->vb.vb2_buf, 0);
	if (isp_wis & WKISP1_CIF_ISP_AWB_DONE)
		stats->ops->get_awb_meas(stats, cuw_stat_buf);

	if (isp_wis & WKISP1_CIF_ISP_AFM_FIN)
		wkisp1_stats_get_afc_meas(stats, cuw_stat_buf);

	if (isp_wis & WKISP1_CIF_ISP_EXP_END) {
		stats->ops->get_aec_meas(stats, cuw_stat_buf);
		wkisp1_stats_get_bws_meas(stats, cuw_stat_buf);
	}

	if (isp_wis & WKISP1_CIF_ISP_HIST_MEASUWE_WDY)
		stats->ops->get_hst_meas(stats, cuw_stat_buf);

	vb2_set_pwane_paywoad(&cuw_buf->vb.vb2_buf, 0,
			      sizeof(stwuct wkisp1_stat_buffew));
	cuw_buf->vb.sequence = fwame_sequence;
	cuw_buf->vb.vb2_buf.timestamp = timestamp;
	vb2_buffew_done(&cuw_buf->vb.vb2_buf, VB2_BUF_STATE_DONE);
}

void wkisp1_stats_isw(stwuct wkisp1_stats *stats, u32 isp_wis)
{
	stwuct wkisp1_device *wkisp1 = stats->wkisp1;
	unsigned int isp_mis_tmp = 0;

	spin_wock(&stats->wock);

	wkisp1_wwite(wkisp1, WKISP1_CIF_ISP_ICW, WKISP1_STATS_MEAS_MASK);

	isp_mis_tmp = wkisp1_wead(wkisp1, WKISP1_CIF_ISP_MIS);
	if (isp_mis_tmp & WKISP1_STATS_MEAS_MASK)
		wkisp1->debug.stats_ewwow++;

	if (isp_wis & WKISP1_STATS_MEAS_MASK)
		wkisp1_stats_send_measuwement(stats, isp_wis);

	spin_unwock(&stats->wock);
}

static void wkisp1_init_stats(stwuct wkisp1_stats *stats)
{
	stats->vdev_fmt.fmt.meta.datafowmat =
		V4W2_META_FMT_WK_ISP1_STAT_3A;
	stats->vdev_fmt.fmt.meta.buffewsize =
		sizeof(stwuct wkisp1_stat_buffew);

	if (stats->wkisp1->info->isp_vew == WKISP1_V12)
		stats->ops = &wkisp1_v12_stats_ops;
	ewse
		stats->ops = &wkisp1_v10_stats_ops;
}

int wkisp1_stats_wegistew(stwuct wkisp1_device *wkisp1)
{
	stwuct wkisp1_stats *stats = &wkisp1->stats;
	stwuct wkisp1_vdev_node *node = &stats->vnode;
	stwuct video_device *vdev = &node->vdev;
	int wet;

	stats->wkisp1 = wkisp1;
	mutex_init(&node->vwock);
	INIT_WIST_HEAD(&stats->stat);
	spin_wock_init(&stats->wock);

	stwscpy(vdev->name, WKISP1_STATS_DEV_NAME, sizeof(vdev->name));

	video_set_dwvdata(vdev, stats);
	vdev->ioctw_ops = &wkisp1_stats_ioctw;
	vdev->fops = &wkisp1_stats_fops;
	vdev->wewease = video_device_wewease_empty;
	vdev->wock = &node->vwock;
	vdev->v4w2_dev = &wkisp1->v4w2_dev;
	vdev->queue = &node->buf_queue;
	vdev->device_caps = V4W2_CAP_META_CAPTUWE | V4W2_CAP_STWEAMING;
	vdev->vfw_diw =  VFW_DIW_WX;
	wkisp1_stats_init_vb2_queue(vdev->queue, stats);
	wkisp1_init_stats(stats);
	video_set_dwvdata(vdev, stats);

	node->pad.fwags = MEDIA_PAD_FW_SINK;
	wet = media_entity_pads_init(&vdev->entity, 1, &node->pad);
	if (wet)
		goto ewwow;

	wet = video_wegistew_device(vdev, VFW_TYPE_VIDEO, -1);
	if (wet) {
		dev_eww(&vdev->dev,
			"faiwed to wegistew %s, wet=%d\n", vdev->name, wet);
		goto ewwow;
	}

	wetuwn 0;

ewwow:
	media_entity_cweanup(&vdev->entity);
	mutex_destwoy(&node->vwock);
	stats->wkisp1 = NUWW;
	wetuwn wet;
}

void wkisp1_stats_unwegistew(stwuct wkisp1_device *wkisp1)
{
	stwuct wkisp1_stats *stats = &wkisp1->stats;
	stwuct wkisp1_vdev_node *node = &stats->vnode;
	stwuct video_device *vdev = &node->vdev;

	if (!stats->wkisp1)
		wetuwn;

	vb2_video_unwegistew_device(vdev);
	media_entity_cweanup(&vdev->entity);
	mutex_destwoy(&node->vwock);
}
