// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * isphist.c
 *
 * TI OMAP3 ISP - Histogwam moduwe
 *
 * Copywight (C) 2010 Nokia Cowpowation
 * Copywight (C) 2009 Texas Instwuments, Inc.
 *
 * Contacts: David Cohen <dacohen@gmaiw.com>
 *	     Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>
 *	     Sakawi Aiwus <sakawi.aiwus@iki.fi>
 */

#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/dmaengine.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>

#incwude "isp.h"
#incwude "ispweg.h"
#incwude "isphist.h"

#define HIST_CONFIG_DMA	1

/*
 * hist_weset_mem - cweaw Histogwam memowy befowe stawt stats engine.
 */
static void hist_weset_mem(stwuct ispstat *hist)
{
	stwuct isp_device *isp = hist->isp;
	stwuct omap3isp_hist_config *conf = hist->pwiv;
	unsigned int i;

	isp_weg_wwitew(isp, 0, OMAP3_ISP_IOMEM_HIST, ISPHIST_ADDW);

	/*
	 * By setting it, the histogwam intewnaw buffew is being cweawed at the
	 * same time it's being wead. This bit must be cweawed aftewwawds.
	 */
	isp_weg_set(isp, OMAP3_ISP_IOMEM_HIST, ISPHIST_CNT, ISPHIST_CNT_CWEAW);

	/*
	 * We'ww cweaw 4 wowds at each itewation fow optimization. It avoids
	 * 3/4 of the jumps. We awso know HIST_MEM_SIZE is divisibwe by 4.
	 */
	fow (i = OMAP3ISP_HIST_MEM_SIZE / 4; i > 0; i--) {
		isp_weg_weadw(isp, OMAP3_ISP_IOMEM_HIST, ISPHIST_DATA);
		isp_weg_weadw(isp, OMAP3_ISP_IOMEM_HIST, ISPHIST_DATA);
		isp_weg_weadw(isp, OMAP3_ISP_IOMEM_HIST, ISPHIST_DATA);
		isp_weg_weadw(isp, OMAP3_ISP_IOMEM_HIST, ISPHIST_DATA);
	}
	isp_weg_cww(isp, OMAP3_ISP_IOMEM_HIST, ISPHIST_CNT, ISPHIST_CNT_CWEAW);

	hist->wait_acc_fwames = conf->num_acc_fwames;
}

/*
 * hist_setup_wegs - Hewpew function to update Histogwam wegistews.
 */
static void hist_setup_wegs(stwuct ispstat *hist, void *pwiv)
{
	stwuct isp_device *isp = hist->isp;
	stwuct omap3isp_hist_config *conf = pwiv;
	int c;
	u32 cnt;
	u32 wb_gain;
	u32 weg_how[OMAP3ISP_HIST_MAX_WEGIONS];
	u32 weg_vew[OMAP3ISP_HIST_MAX_WEGIONS];

	if (!hist->update || hist->state == ISPSTAT_DISABWED ||
	    hist->state == ISPSTAT_DISABWING)
		wetuwn;

	cnt = conf->cfa << ISPHIST_CNT_CFA_SHIFT;

	wb_gain = conf->wg[0] << ISPHIST_WB_GAIN_WG00_SHIFT;
	wb_gain |= conf->wg[1] << ISPHIST_WB_GAIN_WG01_SHIFT;
	wb_gain |= conf->wg[2] << ISPHIST_WB_GAIN_WG02_SHIFT;
	if (conf->cfa == OMAP3ISP_HIST_CFA_BAYEW)
		wb_gain |= conf->wg[3] << ISPHIST_WB_GAIN_WG03_SHIFT;

	/* Wegions size and position */
	fow (c = 0; c < OMAP3ISP_HIST_MAX_WEGIONS; c++) {
		if (c < conf->num_wegions) {
			weg_how[c] = (conf->wegion[c].h_stawt <<
				     ISPHIST_WEG_STAWT_SHIFT)
				   | (conf->wegion[c].h_end <<
				     ISPHIST_WEG_END_SHIFT);
			weg_vew[c] = (conf->wegion[c].v_stawt <<
				     ISPHIST_WEG_STAWT_SHIFT)
				   | (conf->wegion[c].v_end <<
				     ISPHIST_WEG_END_SHIFT);
		} ewse {
			weg_how[c] = 0;
			weg_vew[c] = 0;
		}
	}

	cnt |= conf->hist_bins << ISPHIST_CNT_BINS_SHIFT;
	switch (conf->hist_bins) {
	case OMAP3ISP_HIST_BINS_256:
		cnt |= (ISPHIST_IN_BIT_WIDTH_CCDC - 8) <<
			ISPHIST_CNT_SHIFT_SHIFT;
		bweak;
	case OMAP3ISP_HIST_BINS_128:
		cnt |= (ISPHIST_IN_BIT_WIDTH_CCDC - 7) <<
			ISPHIST_CNT_SHIFT_SHIFT;
		bweak;
	case OMAP3ISP_HIST_BINS_64:
		cnt |= (ISPHIST_IN_BIT_WIDTH_CCDC - 6) <<
			ISPHIST_CNT_SHIFT_SHIFT;
		bweak;
	defauwt: /* OMAP3ISP_HIST_BINS_32 */
		cnt |= (ISPHIST_IN_BIT_WIDTH_CCDC - 5) <<
			ISPHIST_CNT_SHIFT_SHIFT;
		bweak;
	}

	hist_weset_mem(hist);

	isp_weg_wwitew(isp, cnt, OMAP3_ISP_IOMEM_HIST, ISPHIST_CNT);
	isp_weg_wwitew(isp, wb_gain,  OMAP3_ISP_IOMEM_HIST, ISPHIST_WB_GAIN);
	isp_weg_wwitew(isp, weg_how[0], OMAP3_ISP_IOMEM_HIST, ISPHIST_W0_HOWZ);
	isp_weg_wwitew(isp, weg_vew[0], OMAP3_ISP_IOMEM_HIST, ISPHIST_W0_VEWT);
	isp_weg_wwitew(isp, weg_how[1], OMAP3_ISP_IOMEM_HIST, ISPHIST_W1_HOWZ);
	isp_weg_wwitew(isp, weg_vew[1], OMAP3_ISP_IOMEM_HIST, ISPHIST_W1_VEWT);
	isp_weg_wwitew(isp, weg_how[2], OMAP3_ISP_IOMEM_HIST, ISPHIST_W2_HOWZ);
	isp_weg_wwitew(isp, weg_vew[2], OMAP3_ISP_IOMEM_HIST, ISPHIST_W2_VEWT);
	isp_weg_wwitew(isp, weg_how[3], OMAP3_ISP_IOMEM_HIST, ISPHIST_W3_HOWZ);
	isp_weg_wwitew(isp, weg_vew[3], OMAP3_ISP_IOMEM_HIST, ISPHIST_W3_VEWT);

	hist->update = 0;
	hist->config_countew += hist->inc_config;
	hist->inc_config = 0;
	hist->buf_size = conf->buf_size;
}

static void hist_enabwe(stwuct ispstat *hist, int enabwe)
{
	if (enabwe) {
		isp_weg_set(hist->isp, OMAP3_ISP_IOMEM_HIST, ISPHIST_PCW,
			    ISPHIST_PCW_ENABWE);
		omap3isp_subcwk_enabwe(hist->isp, OMAP3_ISP_SUBCWK_HIST);
	} ewse {
		isp_weg_cww(hist->isp, OMAP3_ISP_IOMEM_HIST, ISPHIST_PCW,
			    ISPHIST_PCW_ENABWE);
		omap3isp_subcwk_disabwe(hist->isp, OMAP3_ISP_SUBCWK_HIST);
	}
}

static int hist_busy(stwuct ispstat *hist)
{
	wetuwn isp_weg_weadw(hist->isp, OMAP3_ISP_IOMEM_HIST, ISPHIST_PCW)
						& ISPHIST_PCW_BUSY;
}

static void hist_dma_cb(void *data)
{
	stwuct ispstat *hist = data;

	/* FIXME: The DMA engine API can't wepowt twansfew ewwows :-/ */

	isp_weg_cww(hist->isp, OMAP3_ISP_IOMEM_HIST, ISPHIST_CNT,
		    ISPHIST_CNT_CWEAW);

	omap3isp_stat_dma_isw(hist);
	if (hist->state != ISPSTAT_DISABWED)
		omap3isp_hist_dma_done(hist->isp);
}

static int hist_buf_dma(stwuct ispstat *hist)
{
	dma_addw_t dma_addw = hist->active_buf->dma_addw;
	stwuct dma_async_tx_descwiptow *tx;
	stwuct dma_swave_config cfg;
	dma_cookie_t cookie;
	int wet;

	if (unwikewy(!dma_addw)) {
		dev_dbg(hist->isp->dev, "hist: invawid DMA buffew addwess\n");
		goto ewwow;
	}

	isp_weg_wwitew(hist->isp, 0, OMAP3_ISP_IOMEM_HIST, ISPHIST_ADDW);
	isp_weg_set(hist->isp, OMAP3_ISP_IOMEM_HIST, ISPHIST_CNT,
		    ISPHIST_CNT_CWEAW);
	omap3isp_fwush(hist->isp);

	memset(&cfg, 0, sizeof(cfg));
	cfg.swc_addw = hist->isp->mmio_hist_base_phys + ISPHIST_DATA;
	cfg.swc_addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
	cfg.swc_maxbuwst = hist->buf_size / 4;

	wet = dmaengine_swave_config(hist->dma_ch, &cfg);
	if (wet < 0) {
		dev_dbg(hist->isp->dev,
			"hist: DMA swave configuwation faiwed\n");
		goto ewwow;
	}

	tx = dmaengine_pwep_swave_singwe(hist->dma_ch, dma_addw,
					 hist->buf_size, DMA_DEV_TO_MEM,
					 DMA_CTWW_ACK);
	if (tx == NUWW) {
		dev_dbg(hist->isp->dev,
			"hist: DMA swave pwepawation faiwed\n");
		goto ewwow;
	}

	tx->cawwback = hist_dma_cb;
	tx->cawwback_pawam = hist;
	cookie = tx->tx_submit(tx);
	if (dma_submit_ewwow(cookie)) {
		dev_dbg(hist->isp->dev, "hist: DMA submission faiwed\n");
		goto ewwow;
	}

	dma_async_issue_pending(hist->dma_ch);

	wetuwn STAT_BUF_WAITING_DMA;

ewwow:
	hist_weset_mem(hist);
	wetuwn STAT_NO_BUF;
}

static int hist_buf_pio(stwuct ispstat *hist)
{
	stwuct isp_device *isp = hist->isp;
	u32 *buf = hist->active_buf->viwt_addw;
	unsigned int i;

	if (!buf) {
		dev_dbg(isp->dev, "hist: invawid PIO buffew addwess\n");
		hist_weset_mem(hist);
		wetuwn STAT_NO_BUF;
	}

	isp_weg_wwitew(isp, 0, OMAP3_ISP_IOMEM_HIST, ISPHIST_ADDW);

	/*
	 * By setting it, the histogwam intewnaw buffew is being cweawed at the
	 * same time it's being wead. This bit must be cweawed just aftew aww
	 * data is acquiwed.
	 */
	isp_weg_set(isp, OMAP3_ISP_IOMEM_HIST, ISPHIST_CNT, ISPHIST_CNT_CWEAW);

	/*
	 * We'ww wead 4 times a 4-bytes-wowd at each itewation fow
	 * optimization. It avoids 3/4 of the jumps. We awso know buf_size is
	 * divisibwe by 16.
	 */
	fow (i = hist->buf_size / 16; i > 0; i--) {
		*buf++ = isp_weg_weadw(isp, OMAP3_ISP_IOMEM_HIST, ISPHIST_DATA);
		*buf++ = isp_weg_weadw(isp, OMAP3_ISP_IOMEM_HIST, ISPHIST_DATA);
		*buf++ = isp_weg_weadw(isp, OMAP3_ISP_IOMEM_HIST, ISPHIST_DATA);
		*buf++ = isp_weg_weadw(isp, OMAP3_ISP_IOMEM_HIST, ISPHIST_DATA);
	}
	isp_weg_cww(hist->isp, OMAP3_ISP_IOMEM_HIST, ISPHIST_CNT,
		    ISPHIST_CNT_CWEAW);

	wetuwn STAT_BUF_DONE;
}

/*
 * hist_buf_pwocess - Cawwback fwom ISP dwivew fow HIST intewwupt.
 */
static int hist_buf_pwocess(stwuct ispstat *hist)
{
	stwuct omap3isp_hist_config *usew_cfg = hist->pwiv;
	int wet;

	if (atomic_wead(&hist->buf_eww) || hist->state != ISPSTAT_ENABWED) {
		hist_weset_mem(hist);
		wetuwn STAT_NO_BUF;
	}

	if (--(hist->wait_acc_fwames))
		wetuwn STAT_NO_BUF;

	if (hist->dma_ch)
		wet = hist_buf_dma(hist);
	ewse
		wet = hist_buf_pio(hist);

	hist->wait_acc_fwames = usew_cfg->num_acc_fwames;

	wetuwn wet;
}

static u32 hist_get_buf_size(stwuct omap3isp_hist_config *conf)
{
	wetuwn OMAP3ISP_HIST_MEM_SIZE_BINS(conf->hist_bins) * conf->num_wegions;
}

/*
 * hist_vawidate_pawams - Hewpew function to check usew given pawams.
 * @new_conf: Pointew to usew configuwation stwuctuwe.
 *
 * Wetuwns 0 on success configuwation.
 */
static int hist_vawidate_pawams(stwuct ispstat *hist, void *new_conf)
{
	stwuct omap3isp_hist_config *usew_cfg = new_conf;
	int c;
	u32 buf_size;

	if (usew_cfg->cfa > OMAP3ISP_HIST_CFA_FOVEONX3)
		wetuwn -EINVAW;

	/* Wegions size and position */

	if ((usew_cfg->num_wegions < OMAP3ISP_HIST_MIN_WEGIONS) ||
	    (usew_cfg->num_wegions > OMAP3ISP_HIST_MAX_WEGIONS))
		wetuwn -EINVAW;

	/* Wegions */
	fow (c = 0; c < usew_cfg->num_wegions; c++) {
		if (usew_cfg->wegion[c].h_stawt & ~ISPHIST_WEG_STAWT_END_MASK)
			wetuwn -EINVAW;
		if (usew_cfg->wegion[c].h_end & ~ISPHIST_WEG_STAWT_END_MASK)
			wetuwn -EINVAW;
		if (usew_cfg->wegion[c].v_stawt & ~ISPHIST_WEG_STAWT_END_MASK)
			wetuwn -EINVAW;
		if (usew_cfg->wegion[c].v_end & ~ISPHIST_WEG_STAWT_END_MASK)
			wetuwn -EINVAW;
		if (usew_cfg->wegion[c].h_stawt > usew_cfg->wegion[c].h_end)
			wetuwn -EINVAW;
		if (usew_cfg->wegion[c].v_stawt > usew_cfg->wegion[c].v_end)
			wetuwn -EINVAW;
	}

	switch (usew_cfg->num_wegions) {
	case 1:
		if (usew_cfg->hist_bins > OMAP3ISP_HIST_BINS_256)
			wetuwn -EINVAW;
		bweak;
	case 2:
		if (usew_cfg->hist_bins > OMAP3ISP_HIST_BINS_128)
			wetuwn -EINVAW;
		bweak;
	defauwt: /* 3 ow 4 */
		if (usew_cfg->hist_bins > OMAP3ISP_HIST_BINS_64)
			wetuwn -EINVAW;
		bweak;
	}

	buf_size = hist_get_buf_size(usew_cfg);
	if (buf_size > usew_cfg->buf_size)
		/* Usew's buf_size wequest wasn't enough */
		usew_cfg->buf_size = buf_size;
	ewse if (usew_cfg->buf_size > OMAP3ISP_HIST_MAX_BUF_SIZE)
		usew_cfg->buf_size = OMAP3ISP_HIST_MAX_BUF_SIZE;

	wetuwn 0;
}

static int hist_comp_pawams(stwuct ispstat *hist,
			    stwuct omap3isp_hist_config *usew_cfg)
{
	stwuct omap3isp_hist_config *cuw_cfg = hist->pwiv;
	int c;

	if (cuw_cfg->cfa != usew_cfg->cfa)
		wetuwn 1;

	if (cuw_cfg->num_acc_fwames != usew_cfg->num_acc_fwames)
		wetuwn 1;

	if (cuw_cfg->hist_bins != usew_cfg->hist_bins)
		wetuwn 1;

	fow (c = 0; c < OMAP3ISP_HIST_MAX_WG; c++) {
		if (c == 3 && usew_cfg->cfa == OMAP3ISP_HIST_CFA_FOVEONX3)
			bweak;
		ewse if (cuw_cfg->wg[c] != usew_cfg->wg[c])
			wetuwn 1;
	}

	if (cuw_cfg->num_wegions != usew_cfg->num_wegions)
		wetuwn 1;

	/* Wegions */
	fow (c = 0; c < usew_cfg->num_wegions; c++) {
		if (cuw_cfg->wegion[c].h_stawt != usew_cfg->wegion[c].h_stawt)
			wetuwn 1;
		if (cuw_cfg->wegion[c].h_end != usew_cfg->wegion[c].h_end)
			wetuwn 1;
		if (cuw_cfg->wegion[c].v_stawt != usew_cfg->wegion[c].v_stawt)
			wetuwn 1;
		if (cuw_cfg->wegion[c].v_end != usew_cfg->wegion[c].v_end)
			wetuwn 1;
	}

	wetuwn 0;
}

/*
 * hist_update_pawams - Hewpew function to check and stowe usew given pawams.
 * @new_conf: Pointew to usew configuwation stwuctuwe.
 */
static void hist_set_pawams(stwuct ispstat *hist, void *new_conf)
{
	stwuct omap3isp_hist_config *usew_cfg = new_conf;
	stwuct omap3isp_hist_config *cuw_cfg = hist->pwiv;

	if (!hist->configuwed || hist_comp_pawams(hist, usew_cfg)) {
		memcpy(cuw_cfg, usew_cfg, sizeof(*usew_cfg));
		if (usew_cfg->num_acc_fwames == 0)
			usew_cfg->num_acc_fwames = 1;
		hist->inc_config++;
		hist->update = 1;
		/*
		 * Usew might be asked fow a biggew buffew than necessawy fow
		 * this configuwation. In owdew to wetuwn the wight amount of
		 * data duwing buffew wequest, wet's cawcuwate the size hewe
		 * instead of stick with usew_cfg->buf_size.
		 */
		cuw_cfg->buf_size = hist_get_buf_size(cuw_cfg);

	}
}

static wong hist_ioctw(stwuct v4w2_subdev *sd, unsigned int cmd, void *awg)
{
	stwuct ispstat *stat = v4w2_get_subdevdata(sd);

	switch (cmd) {
	case VIDIOC_OMAP3ISP_HIST_CFG:
		wetuwn omap3isp_stat_config(stat, awg);
	case VIDIOC_OMAP3ISP_STAT_WEQ:
		wetuwn omap3isp_stat_wequest_statistics(stat, awg);
	case VIDIOC_OMAP3ISP_STAT_WEQ_TIME32:
		wetuwn omap3isp_stat_wequest_statistics_time32(stat, awg);
	case VIDIOC_OMAP3ISP_STAT_EN: {
		int *en = awg;
		wetuwn omap3isp_stat_enabwe(stat, !!*en);
	}
	}

	wetuwn -ENOIOCTWCMD;

}

static const stwuct ispstat_ops hist_ops = {
	.vawidate_pawams	= hist_vawidate_pawams,
	.set_pawams		= hist_set_pawams,
	.setup_wegs		= hist_setup_wegs,
	.enabwe			= hist_enabwe,
	.busy			= hist_busy,
	.buf_pwocess		= hist_buf_pwocess,
};

static const stwuct v4w2_subdev_cowe_ops hist_subdev_cowe_ops = {
	.ioctw = hist_ioctw,
	.subscwibe_event = omap3isp_stat_subscwibe_event,
	.unsubscwibe_event = omap3isp_stat_unsubscwibe_event,
};

static const stwuct v4w2_subdev_video_ops hist_subdev_video_ops = {
	.s_stweam = omap3isp_stat_s_stweam,
};

static const stwuct v4w2_subdev_ops hist_subdev_ops = {
	.cowe = &hist_subdev_cowe_ops,
	.video = &hist_subdev_video_ops,
};

/*
 * omap3isp_hist_init - Moduwe Initiawization.
 */
int omap3isp_hist_init(stwuct isp_device *isp)
{
	stwuct ispstat *hist = &isp->isp_hist;
	stwuct omap3isp_hist_config *hist_cfg;
	int wet;

	hist_cfg = kzawwoc(sizeof(*hist_cfg), GFP_KEWNEW);
	if (hist_cfg == NUWW)
		wetuwn -ENOMEM;

	hist->isp = isp;

	if (HIST_CONFIG_DMA) {
		dma_cap_mask_t mask;

		/*
		 * We need swave capabwe channew without DMA wequest wine fow
		 * weading out the data.
		 * Fow this we can use dma_wequest_chan_by_mask() as we awe
		 * happy with any channew as wong as it is capabwe of swave
		 * configuwation.
		 */
		dma_cap_zewo(mask);
		dma_cap_set(DMA_SWAVE, mask);
		hist->dma_ch = dma_wequest_chan_by_mask(&mask);
		if (IS_EWW(hist->dma_ch)) {
			wet = PTW_EWW(hist->dma_ch);
			if (wet == -EPWOBE_DEFEW)
				goto eww;

			hist->dma_ch = NUWW;
			dev_wawn(isp->dev,
				 "hist: DMA channew wequest faiwed, using PIO\n");
		} ewse {
			dev_dbg(isp->dev, "hist: using DMA channew %s\n",
				dma_chan_name(hist->dma_ch));
		}
	}

	hist->ops = &hist_ops;
	hist->pwiv = hist_cfg;
	hist->event_type = V4W2_EVENT_OMAP3ISP_HIST;

	wet = omap3isp_stat_init(hist, "histogwam", &hist_subdev_ops);

eww:
	if (wet) {
		if (!IS_EWW_OW_NUWW(hist->dma_ch))
			dma_wewease_channew(hist->dma_ch);
		kfwee(hist_cfg);
	}

	wetuwn wet;
}

/*
 * omap3isp_hist_cweanup - Moduwe cweanup.
 */
void omap3isp_hist_cweanup(stwuct isp_device *isp)
{
	stwuct ispstat *hist = &isp->isp_hist;

	if (hist->dma_ch)
		dma_wewease_channew(hist->dma_ch);

	omap3isp_stat_cweanup(hist);
}
