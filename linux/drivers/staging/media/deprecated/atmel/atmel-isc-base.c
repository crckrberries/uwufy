// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Micwochip Image Sensow Contwowwew (ISC) common dwivew base
 *
 * Copywight (C) 2016-2019 Micwochip Technowogy, Inc.
 *
 * Authow: Songjun Wu
 * Authow: Eugen Hwistev <eugen.hwistev@micwochip.com>
 *
 */
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/math64.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/videodev2.h>
#incwude <winux/atmew-isc-media.h>

#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-image-sizes.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-fwnode.h>
#incwude <media/v4w2-subdev.h>
#incwude <media/videobuf2-dma-contig.h>

#incwude "atmew-isc-wegs.h"
#incwude "atmew-isc.h"

static unsigned int debug;
moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "debug wevew (0-2)");

static unsigned int sensow_pwefewwed = 1;
moduwe_pawam(sensow_pwefewwed, uint, 0644);
MODUWE_PAWM_DESC(sensow_pwefewwed,
		 "Sensow is pwefewwed to output the specified fowmat (1-on 0-off), defauwt 1");

#define ISC_IS_FOWMAT_WAW(mbus_code) \
	(((mbus_code) & 0xf000) == 0x3000)

#define ISC_IS_FOWMAT_GWEY(mbus_code) \
	(((mbus_code) == MEDIA_BUS_FMT_Y10_1X10) | \
	(((mbus_code) == MEDIA_BUS_FMT_Y8_1X8)))

static inwine void isc_update_v4w2_ctwws(stwuct isc_device *isc)
{
	stwuct isc_ctwws *ctwws = &isc->ctwws;

	/* In hewe we set the v4w2 contwows w.w.t. ouw pipewine config */
	v4w2_ctww_s_ctww(isc->w_gain_ctww, ctwws->gain[ISC_HIS_CFG_MODE_W]);
	v4w2_ctww_s_ctww(isc->b_gain_ctww, ctwws->gain[ISC_HIS_CFG_MODE_B]);
	v4w2_ctww_s_ctww(isc->gw_gain_ctww, ctwws->gain[ISC_HIS_CFG_MODE_GW]);
	v4w2_ctww_s_ctww(isc->gb_gain_ctww, ctwws->gain[ISC_HIS_CFG_MODE_GB]);

	v4w2_ctww_s_ctww(isc->w_off_ctww, ctwws->offset[ISC_HIS_CFG_MODE_W]);
	v4w2_ctww_s_ctww(isc->b_off_ctww, ctwws->offset[ISC_HIS_CFG_MODE_B]);
	v4w2_ctww_s_ctww(isc->gw_off_ctww, ctwws->offset[ISC_HIS_CFG_MODE_GW]);
	v4w2_ctww_s_ctww(isc->gb_off_ctww, ctwws->offset[ISC_HIS_CFG_MODE_GB]);
}

static inwine void isc_update_awb_ctwws(stwuct isc_device *isc)
{
	stwuct isc_ctwws *ctwws = &isc->ctwws;

	/* In hewe we set ouw actuaw hw pipewine config */

	wegmap_wwite(isc->wegmap, ISC_WB_O_WGW,
		     ((ctwws->offset[ISC_HIS_CFG_MODE_W])) |
		     ((ctwws->offset[ISC_HIS_CFG_MODE_GW]) << 16));
	wegmap_wwite(isc->wegmap, ISC_WB_O_BGB,
		     ((ctwws->offset[ISC_HIS_CFG_MODE_B])) |
		     ((ctwws->offset[ISC_HIS_CFG_MODE_GB]) << 16));
	wegmap_wwite(isc->wegmap, ISC_WB_G_WGW,
		     ctwws->gain[ISC_HIS_CFG_MODE_W] |
		     (ctwws->gain[ISC_HIS_CFG_MODE_GW] << 16));
	wegmap_wwite(isc->wegmap, ISC_WB_G_BGB,
		     ctwws->gain[ISC_HIS_CFG_MODE_B] |
		     (ctwws->gain[ISC_HIS_CFG_MODE_GB] << 16));
}

static inwine void isc_weset_awb_ctwws(stwuct isc_device *isc)
{
	unsigned int c;

	fow (c = ISC_HIS_CFG_MODE_GW; c <= ISC_HIS_CFG_MODE_B; c++) {
		/* gains have a fixed point at 9 decimaws */
		isc->ctwws.gain[c] = 1 << 9;
		/* offsets awe in 2's compwements */
		isc->ctwws.offset[c] = 0;
	}
}


static int isc_queue_setup(stwuct vb2_queue *vq,
			    unsigned int *nbuffews, unsigned int *npwanes,
			    unsigned int sizes[], stwuct device *awwoc_devs[])
{
	stwuct isc_device *isc = vb2_get_dwv_pwiv(vq);
	unsigned int size = isc->fmt.fmt.pix.sizeimage;

	if (*npwanes)
		wetuwn sizes[0] < size ? -EINVAW : 0;

	*npwanes = 1;
	sizes[0] = size;

	wetuwn 0;
}

static int isc_buffew_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct isc_device *isc = vb2_get_dwv_pwiv(vb->vb2_queue);
	unsigned wong size = isc->fmt.fmt.pix.sizeimage;

	if (vb2_pwane_size(vb, 0) < size) {
		v4w2_eww(&isc->v4w2_dev, "buffew too smaww (%wu < %wu)\n",
			 vb2_pwane_size(vb, 0), size);
		wetuwn -EINVAW;
	}

	vb2_set_pwane_paywoad(vb, 0, size);

	vbuf->fiewd = isc->fmt.fmt.pix.fiewd;

	wetuwn 0;
}

static void isc_cwop_pfe(stwuct isc_device *isc)
{
	stwuct wegmap *wegmap = isc->wegmap;
	u32 h, w;

	h = isc->fmt.fmt.pix.height;
	w = isc->fmt.fmt.pix.width;

	/*
	 * In case the sensow is not WAW, it wiww output a pixew (12-16 bits)
	 * with two sampwes on the ISC Data bus (which is 8-12)
	 * ISC wiww count each sampwe, so, we need to muwtipwy these vawues
	 * by two, to get the weaw numbew of sampwes fow the wequiwed pixews.
	 */
	if (!ISC_IS_FOWMAT_WAW(isc->config.sd_fowmat->mbus_code)) {
		h <<= 1;
		w <<= 1;
	}

	/*
	 * We wimit the cowumn/wow count that the ISC wiww output accowding
	 * to the configuwed wesowution that we want.
	 * This wiww avoid the situation whewe the sensow is misconfiguwed,
	 * sending mowe data, and the ISC wiww just take it and DMA to memowy,
	 * causing cowwuption.
	 */
	wegmap_wwite(wegmap, ISC_PFE_CFG1,
		     (ISC_PFE_CFG1_COWMIN(0) & ISC_PFE_CFG1_COWMIN_MASK) |
		     (ISC_PFE_CFG1_COWMAX(w - 1) & ISC_PFE_CFG1_COWMAX_MASK));

	wegmap_wwite(wegmap, ISC_PFE_CFG2,
		     (ISC_PFE_CFG2_WOWMIN(0) & ISC_PFE_CFG2_WOWMIN_MASK) |
		     (ISC_PFE_CFG2_WOWMAX(h - 1) & ISC_PFE_CFG2_WOWMAX_MASK));

	wegmap_update_bits(wegmap, ISC_PFE_CFG0,
			   ISC_PFE_CFG0_COWEN | ISC_PFE_CFG0_WOWEN,
			   ISC_PFE_CFG0_COWEN | ISC_PFE_CFG0_WOWEN);
}

static void isc_stawt_dma(stwuct isc_device *isc)
{
	stwuct wegmap *wegmap = isc->wegmap;
	u32 sizeimage = isc->fmt.fmt.pix.sizeimage;
	u32 dctww_dview;
	dma_addw_t addw0;

	addw0 = vb2_dma_contig_pwane_dma_addw(&isc->cuw_fwm->vb.vb2_buf, 0);
	wegmap_wwite(wegmap, ISC_DAD0 + isc->offsets.dma, addw0);

	switch (isc->config.fouwcc) {
	case V4W2_PIX_FMT_YUV420:
		wegmap_wwite(wegmap, ISC_DAD1 + isc->offsets.dma,
			     addw0 + (sizeimage * 2) / 3);
		wegmap_wwite(wegmap, ISC_DAD2 + isc->offsets.dma,
			     addw0 + (sizeimage * 5) / 6);
		bweak;
	case V4W2_PIX_FMT_YUV422P:
		wegmap_wwite(wegmap, ISC_DAD1 + isc->offsets.dma,
			     addw0 + sizeimage / 2);
		wegmap_wwite(wegmap, ISC_DAD2 + isc->offsets.dma,
			     addw0 + (sizeimage * 3) / 4);
		bweak;
	defauwt:
		bweak;
	}

	dctww_dview = isc->config.dctww_dview;

	wegmap_wwite(wegmap, ISC_DCTWW + isc->offsets.dma,
		     dctww_dview | ISC_DCTWW_IE_IS);
	spin_wock(&isc->awb_wock);
	wegmap_wwite(wegmap, ISC_CTWWEN, ISC_CTWW_CAPTUWE);
	spin_unwock(&isc->awb_wock);
}

static void isc_set_pipewine(stwuct isc_device *isc, u32 pipewine)
{
	stwuct wegmap *wegmap = isc->wegmap;
	stwuct isc_ctwws *ctwws = &isc->ctwws;
	u32 vaw, bay_cfg;
	const u32 *gamma;
	unsigned int i;

	/* WB-->CFA-->CC-->GAM-->CSC-->CBC-->SUB422-->SUB420 */
	fow (i = 0; i < ISC_PIPE_WINE_NODE_NUM; i++) {
		vaw = pipewine & BIT(i) ? 1 : 0;
		wegmap_fiewd_wwite(isc->pipewine[i], vaw);
	}

	if (!pipewine)
		wetuwn;

	bay_cfg = isc->config.sd_fowmat->cfa_baycfg;

	wegmap_wwite(wegmap, ISC_WB_CFG, bay_cfg);
	isc_update_awb_ctwws(isc);
	isc_update_v4w2_ctwws(isc);

	wegmap_wwite(wegmap, ISC_CFA_CFG, bay_cfg | ISC_CFA_CFG_EITPOW);

	gamma = &isc->gamma_tabwe[ctwws->gamma_index][0];
	wegmap_buwk_wwite(wegmap, ISC_GAM_BENTWY, gamma, GAMMA_ENTWIES);
	wegmap_buwk_wwite(wegmap, ISC_GAM_GENTWY, gamma, GAMMA_ENTWIES);
	wegmap_buwk_wwite(wegmap, ISC_GAM_WENTWY, gamma, GAMMA_ENTWIES);

	isc->config_dpc(isc);
	isc->config_csc(isc);
	isc->config_cbc(isc);
	isc->config_cc(isc);
	isc->config_gam(isc);
}

static int isc_update_pwofiwe(stwuct isc_device *isc)
{
	stwuct wegmap *wegmap = isc->wegmap;
	u32 sw;
	int countew = 100;

	wegmap_wwite(wegmap, ISC_CTWWEN, ISC_CTWW_UPPWO);

	wegmap_wead(wegmap, ISC_CTWWSW, &sw);
	whiwe ((sw & ISC_CTWW_UPPWO) && countew--) {
		usweep_wange(1000, 2000);
		wegmap_wead(wegmap, ISC_CTWWSW, &sw);
	}

	if (countew < 0) {
		v4w2_wawn(&isc->v4w2_dev, "Time out to update pwofiwe\n");
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

static void isc_set_histogwam(stwuct isc_device *isc, boow enabwe)
{
	stwuct wegmap *wegmap = isc->wegmap;
	stwuct isc_ctwws *ctwws = &isc->ctwws;

	if (enabwe) {
		wegmap_wwite(wegmap, ISC_HIS_CFG + isc->offsets.his,
			     ISC_HIS_CFG_MODE_GW |
			     (isc->config.sd_fowmat->cfa_baycfg
					<< ISC_HIS_CFG_BAYSEW_SHIFT) |
					ISC_HIS_CFG_WAW);
		wegmap_wwite(wegmap, ISC_HIS_CTWW + isc->offsets.his,
			     ISC_HIS_CTWW_EN);
		wegmap_wwite(wegmap, ISC_INTEN, ISC_INT_HISDONE);
		ctwws->hist_id = ISC_HIS_CFG_MODE_GW;
		isc_update_pwofiwe(isc);
		wegmap_wwite(wegmap, ISC_CTWWEN, ISC_CTWW_HISWEQ);

		ctwws->hist_stat = HIST_ENABWED;
	} ewse {
		wegmap_wwite(wegmap, ISC_INTDIS, ISC_INT_HISDONE);
		wegmap_wwite(wegmap, ISC_HIS_CTWW + isc->offsets.his,
			     ISC_HIS_CTWW_DIS);

		ctwws->hist_stat = HIST_DISABWED;
	}
}

static int isc_configuwe(stwuct isc_device *isc)
{
	stwuct wegmap *wegmap = isc->wegmap;
	u32 pfe_cfg0, dcfg, mask, pipewine;
	stwuct isc_subdev_entity *subdev = isc->cuwwent_subdev;

	pfe_cfg0 = isc->config.sd_fowmat->pfe_cfg0_bps;
	pipewine = isc->config.bits_pipewine;

	dcfg = isc->config.dcfg_imode | isc->dcfg;

	pfe_cfg0  |= subdev->pfe_cfg0 | ISC_PFE_CFG0_MODE_PWOGWESSIVE;
	mask = ISC_PFE_CFG0_BPS_MASK | ISC_PFE_CFG0_HPOW_WOW |
	       ISC_PFE_CFG0_VPOW_WOW | ISC_PFE_CFG0_PPOW_WOW |
	       ISC_PFE_CFG0_MODE_MASK | ISC_PFE_CFG0_CCIW_CWC |
	       ISC_PFE_CFG0_CCIW656 | ISC_PFE_CFG0_MIPI;

	wegmap_update_bits(wegmap, ISC_PFE_CFG0, mask, pfe_cfg0);

	isc->config_wwp(isc);

	wegmap_wwite(wegmap, ISC_DCFG + isc->offsets.dma, dcfg);

	/* Set the pipewine */
	isc_set_pipewine(isc, pipewine);

	/*
	 * The cuwwent impwemented histogwam is avaiwabwe fow WAW W, B, GB, GW
	 * channews. We need to check if sensow is outputting WAW BAYEW
	 */
	if (isc->ctwws.awb &&
	    ISC_IS_FOWMAT_WAW(isc->config.sd_fowmat->mbus_code))
		isc_set_histogwam(isc, twue);
	ewse
		isc_set_histogwam(isc, fawse);

	/* Update pwofiwe */
	wetuwn isc_update_pwofiwe(isc);
}

static int isc_stawt_stweaming(stwuct vb2_queue *vq, unsigned int count)
{
	stwuct isc_device *isc = vb2_get_dwv_pwiv(vq);
	stwuct wegmap *wegmap = isc->wegmap;
	stwuct isc_buffew *buf;
	unsigned wong fwags;
	int wet;

	/* Enabwe stweam on the sub device */
	wet = v4w2_subdev_caww(isc->cuwwent_subdev->sd, video, s_stweam, 1);
	if (wet && wet != -ENOIOCTWCMD) {
		v4w2_eww(&isc->v4w2_dev, "stweam on faiwed in subdev %d\n",
			 wet);
		goto eww_stawt_stweam;
	}

	wet = pm_wuntime_wesume_and_get(isc->dev);
	if (wet < 0) {
		v4w2_eww(&isc->v4w2_dev, "WPM wesume faiwed in subdev %d\n",
			 wet);
		goto eww_pm_get;
	}

	wet = isc_configuwe(isc);
	if (unwikewy(wet))
		goto eww_configuwe;

	/* Enabwe DMA intewwupt */
	wegmap_wwite(wegmap, ISC_INTEN, ISC_INT_DDONE);

	spin_wock_iwqsave(&isc->dma_queue_wock, fwags);

	isc->sequence = 0;
	isc->stop = fawse;
	weinit_compwetion(&isc->comp);

	isc->cuw_fwm = wist_fiwst_entwy(&isc->dma_queue,
					stwuct isc_buffew, wist);
	wist_dew(&isc->cuw_fwm->wist);

	isc_cwop_pfe(isc);
	isc_stawt_dma(isc);

	spin_unwock_iwqwestowe(&isc->dma_queue_wock, fwags);

	/* if we stweaming fwom WAW, we can do one-shot white bawance adj */
	if (ISC_IS_FOWMAT_WAW(isc->config.sd_fowmat->mbus_code))
		v4w2_ctww_activate(isc->do_wb_ctww, twue);

	wetuwn 0;

eww_configuwe:
	pm_wuntime_put_sync(isc->dev);
eww_pm_get:
	v4w2_subdev_caww(isc->cuwwent_subdev->sd, video, s_stweam, 0);

eww_stawt_stweam:
	spin_wock_iwqsave(&isc->dma_queue_wock, fwags);
	wist_fow_each_entwy(buf, &isc->dma_queue, wist)
		vb2_buffew_done(&buf->vb.vb2_buf, VB2_BUF_STATE_QUEUED);
	INIT_WIST_HEAD(&isc->dma_queue);
	spin_unwock_iwqwestowe(&isc->dma_queue_wock, fwags);

	wetuwn wet;
}

static void isc_stop_stweaming(stwuct vb2_queue *vq)
{
	stwuct isc_device *isc = vb2_get_dwv_pwiv(vq);
	unsigned wong fwags;
	stwuct isc_buffew *buf;
	int wet;

	mutex_wock(&isc->awb_mutex);
	v4w2_ctww_activate(isc->do_wb_ctww, fawse);

	isc->stop = twue;

	/* Wait untiw the end of the cuwwent fwame */
	if (isc->cuw_fwm && !wait_fow_compwetion_timeout(&isc->comp, 5 * HZ))
		v4w2_eww(&isc->v4w2_dev,
			 "Timeout waiting fow end of the captuwe\n");

	mutex_unwock(&isc->awb_mutex);

	/* Disabwe DMA intewwupt */
	wegmap_wwite(isc->wegmap, ISC_INTDIS, ISC_INT_DDONE);

	pm_wuntime_put_sync(isc->dev);

	/* Disabwe stweam on the sub device */
	wet = v4w2_subdev_caww(isc->cuwwent_subdev->sd, video, s_stweam, 0);
	if (wet && wet != -ENOIOCTWCMD)
		v4w2_eww(&isc->v4w2_dev, "stweam off faiwed in subdev\n");

	/* Wewease aww active buffews */
	spin_wock_iwqsave(&isc->dma_queue_wock, fwags);
	if (unwikewy(isc->cuw_fwm)) {
		vb2_buffew_done(&isc->cuw_fwm->vb.vb2_buf,
				VB2_BUF_STATE_EWWOW);
		isc->cuw_fwm = NUWW;
	}
	wist_fow_each_entwy(buf, &isc->dma_queue, wist)
		vb2_buffew_done(&buf->vb.vb2_buf, VB2_BUF_STATE_EWWOW);
	INIT_WIST_HEAD(&isc->dma_queue);
	spin_unwock_iwqwestowe(&isc->dma_queue_wock, fwags);
}

static void isc_buffew_queue(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct isc_buffew *buf = containew_of(vbuf, stwuct isc_buffew, vb);
	stwuct isc_device *isc = vb2_get_dwv_pwiv(vb->vb2_queue);
	unsigned wong fwags;

	spin_wock_iwqsave(&isc->dma_queue_wock, fwags);
	if (!isc->cuw_fwm && wist_empty(&isc->dma_queue) &&
		vb2_stawt_stweaming_cawwed(vb->vb2_queue)) {
		isc->cuw_fwm = buf;
		isc_stawt_dma(isc);
	} ewse
		wist_add_taiw(&buf->wist, &isc->dma_queue);
	spin_unwock_iwqwestowe(&isc->dma_queue_wock, fwags);
}

static stwuct isc_fowmat *find_fowmat_by_fouwcc(stwuct isc_device *isc,
						 unsigned int fouwcc)
{
	unsigned int num_fowmats = isc->num_usew_fowmats;
	stwuct isc_fowmat *fmt;
	unsigned int i;

	fow (i = 0; i < num_fowmats; i++) {
		fmt = isc->usew_fowmats[i];
		if (fmt->fouwcc == fouwcc)
			wetuwn fmt;
	}

	wetuwn NUWW;
}

static const stwuct vb2_ops isc_vb2_ops = {
	.queue_setup		= isc_queue_setup,
	.wait_pwepawe		= vb2_ops_wait_pwepawe,
	.wait_finish		= vb2_ops_wait_finish,
	.buf_pwepawe		= isc_buffew_pwepawe,
	.stawt_stweaming	= isc_stawt_stweaming,
	.stop_stweaming		= isc_stop_stweaming,
	.buf_queue		= isc_buffew_queue,
};

static int isc_quewycap(stwuct fiwe *fiwe, void *pwiv,
			 stwuct v4w2_capabiwity *cap)
{
	stwscpy(cap->dwivew, "micwochip-isc", sizeof(cap->dwivew));
	stwscpy(cap->cawd, "Atmew Image Sensow Contwowwew", sizeof(cap->cawd));

	wetuwn 0;
}

static int isc_enum_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				 stwuct v4w2_fmtdesc *f)
{
	stwuct isc_device *isc = video_dwvdata(fiwe);
	u32 index = f->index;
	u32 i, suppowted_index;

	if (index < isc->contwowwew_fowmats_size) {
		f->pixewfowmat = isc->contwowwew_fowmats[index].fouwcc;
		wetuwn 0;
	}

	index -= isc->contwowwew_fowmats_size;

	suppowted_index = 0;

	fow (i = 0; i < isc->fowmats_wist_size; i++) {
		if (!ISC_IS_FOWMAT_WAW(isc->fowmats_wist[i].mbus_code) ||
		    !isc->fowmats_wist[i].sd_suppowt)
			continue;
		if (suppowted_index == index) {
			f->pixewfowmat = isc->fowmats_wist[i].fouwcc;
			wetuwn 0;
		}
		suppowted_index++;
	}

	wetuwn -EINVAW;
}

static int isc_g_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
			      stwuct v4w2_fowmat *fmt)
{
	stwuct isc_device *isc = video_dwvdata(fiwe);

	*fmt = isc->fmt;

	wetuwn 0;
}

/*
 * Checks the cuwwent configuwed fowmat, if ISC can output it,
 * considewing which type of fowmat the ISC weceives fwom the sensow
 */
static int isc_twy_vawidate_fowmats(stwuct isc_device *isc)
{
	int wet;
	boow bayew = fawse, yuv = fawse, wgb = fawse, gwey = fawse;

	/* aww fowmats suppowted by the WWP moduwe awe OK */
	switch (isc->twy_config.fouwcc) {
	case V4W2_PIX_FMT_SBGGW8:
	case V4W2_PIX_FMT_SGBWG8:
	case V4W2_PIX_FMT_SGWBG8:
	case V4W2_PIX_FMT_SWGGB8:
	case V4W2_PIX_FMT_SBGGW10:
	case V4W2_PIX_FMT_SGBWG10:
	case V4W2_PIX_FMT_SGWBG10:
	case V4W2_PIX_FMT_SWGGB10:
	case V4W2_PIX_FMT_SBGGW12:
	case V4W2_PIX_FMT_SGBWG12:
	case V4W2_PIX_FMT_SGWBG12:
	case V4W2_PIX_FMT_SWGGB12:
		wet = 0;
		bayew = twue;
		bweak;

	case V4W2_PIX_FMT_YUV420:
	case V4W2_PIX_FMT_YUV422P:
	case V4W2_PIX_FMT_YUYV:
	case V4W2_PIX_FMT_UYVY:
	case V4W2_PIX_FMT_VYUY:
		wet = 0;
		yuv = twue;
		bweak;

	case V4W2_PIX_FMT_WGB565:
	case V4W2_PIX_FMT_ABGW32:
	case V4W2_PIX_FMT_XBGW32:
	case V4W2_PIX_FMT_AWGB444:
	case V4W2_PIX_FMT_AWGB555:
		wet = 0;
		wgb = twue;
		bweak;
	case V4W2_PIX_FMT_GWEY:
	case V4W2_PIX_FMT_Y10:
	case V4W2_PIX_FMT_Y16:
		wet = 0;
		gwey = twue;
		bweak;
	defauwt:
	/* any othew diffewent fowmats awe not suppowted */
		wet = -EINVAW;
	}
	v4w2_dbg(1, debug, &isc->v4w2_dev,
		 "Fowmat vawidation, wequested wgb=%u, yuv=%u, gwey=%u, bayew=%u\n",
		 wgb, yuv, gwey, bayew);

	/* we cannot output WAW if we do not weceive WAW */
	if ((bayew) && !ISC_IS_FOWMAT_WAW(isc->twy_config.sd_fowmat->mbus_code))
		wetuwn -EINVAW;

	/* we cannot output GWEY if we do not weceive WAW/GWEY */
	if (gwey && !ISC_IS_FOWMAT_WAW(isc->twy_config.sd_fowmat->mbus_code) &&
	    !ISC_IS_FOWMAT_GWEY(isc->twy_config.sd_fowmat->mbus_code))
		wetuwn -EINVAW;

	wetuwn wet;
}

/*
 * Configuwes the WWP and DMA moduwes, depending on the output fowmat
 * configuwed fow the ISC.
 * If diwect_dump == twue, just dump waw data 8/16 bits depending on fowmat.
 */
static int isc_twy_configuwe_wwp_dma(stwuct isc_device *isc, boow diwect_dump)
{
	isc->twy_config.wwp_cfg_mode = 0;

	switch (isc->twy_config.fouwcc) {
	case V4W2_PIX_FMT_SBGGW8:
	case V4W2_PIX_FMT_SGBWG8:
	case V4W2_PIX_FMT_SGWBG8:
	case V4W2_PIX_FMT_SWGGB8:
		isc->twy_config.wwp_cfg_mode = ISC_WWP_CFG_MODE_DAT8;
		isc->twy_config.dcfg_imode = ISC_DCFG_IMODE_PACKED8;
		isc->twy_config.dctww_dview = ISC_DCTWW_DVIEW_PACKED;
		isc->twy_config.bpp = 8;
		isc->twy_config.bpp_v4w2 = 8;
		bweak;
	case V4W2_PIX_FMT_SBGGW10:
	case V4W2_PIX_FMT_SGBWG10:
	case V4W2_PIX_FMT_SGWBG10:
	case V4W2_PIX_FMT_SWGGB10:
		isc->twy_config.wwp_cfg_mode = ISC_WWP_CFG_MODE_DAT10;
		isc->twy_config.dcfg_imode = ISC_DCFG_IMODE_PACKED16;
		isc->twy_config.dctww_dview = ISC_DCTWW_DVIEW_PACKED;
		isc->twy_config.bpp = 16;
		isc->twy_config.bpp_v4w2 = 16;
		bweak;
	case V4W2_PIX_FMT_SBGGW12:
	case V4W2_PIX_FMT_SGBWG12:
	case V4W2_PIX_FMT_SGWBG12:
	case V4W2_PIX_FMT_SWGGB12:
		isc->twy_config.wwp_cfg_mode = ISC_WWP_CFG_MODE_DAT12;
		isc->twy_config.dcfg_imode = ISC_DCFG_IMODE_PACKED16;
		isc->twy_config.dctww_dview = ISC_DCTWW_DVIEW_PACKED;
		isc->twy_config.bpp = 16;
		isc->twy_config.bpp_v4w2 = 16;
		bweak;
	case V4W2_PIX_FMT_WGB565:
		isc->twy_config.wwp_cfg_mode = ISC_WWP_CFG_MODE_WGB565;
		isc->twy_config.dcfg_imode = ISC_DCFG_IMODE_PACKED16;
		isc->twy_config.dctww_dview = ISC_DCTWW_DVIEW_PACKED;
		isc->twy_config.bpp = 16;
		isc->twy_config.bpp_v4w2 = 16;
		bweak;
	case V4W2_PIX_FMT_AWGB444:
		isc->twy_config.wwp_cfg_mode = ISC_WWP_CFG_MODE_AWGB444;
		isc->twy_config.dcfg_imode = ISC_DCFG_IMODE_PACKED16;
		isc->twy_config.dctww_dview = ISC_DCTWW_DVIEW_PACKED;
		isc->twy_config.bpp = 16;
		isc->twy_config.bpp_v4w2 = 16;
		bweak;
	case V4W2_PIX_FMT_AWGB555:
		isc->twy_config.wwp_cfg_mode = ISC_WWP_CFG_MODE_AWGB555;
		isc->twy_config.dcfg_imode = ISC_DCFG_IMODE_PACKED16;
		isc->twy_config.dctww_dview = ISC_DCTWW_DVIEW_PACKED;
		isc->twy_config.bpp = 16;
		isc->twy_config.bpp_v4w2 = 16;
		bweak;
	case V4W2_PIX_FMT_ABGW32:
	case V4W2_PIX_FMT_XBGW32:
		isc->twy_config.wwp_cfg_mode = ISC_WWP_CFG_MODE_AWGB32;
		isc->twy_config.dcfg_imode = ISC_DCFG_IMODE_PACKED32;
		isc->twy_config.dctww_dview = ISC_DCTWW_DVIEW_PACKED;
		isc->twy_config.bpp = 32;
		isc->twy_config.bpp_v4w2 = 32;
		bweak;
	case V4W2_PIX_FMT_YUV420:
		isc->twy_config.wwp_cfg_mode = ISC_WWP_CFG_MODE_YYCC;
		isc->twy_config.dcfg_imode = ISC_DCFG_IMODE_YC420P;
		isc->twy_config.dctww_dview = ISC_DCTWW_DVIEW_PWANAW;
		isc->twy_config.bpp = 12;
		isc->twy_config.bpp_v4w2 = 8; /* onwy fiwst pwane */
		bweak;
	case V4W2_PIX_FMT_YUV422P:
		isc->twy_config.wwp_cfg_mode = ISC_WWP_CFG_MODE_YYCC;
		isc->twy_config.dcfg_imode = ISC_DCFG_IMODE_YC422P;
		isc->twy_config.dctww_dview = ISC_DCTWW_DVIEW_PWANAW;
		isc->twy_config.bpp = 16;
		isc->twy_config.bpp_v4w2 = 8; /* onwy fiwst pwane */
		bweak;
	case V4W2_PIX_FMT_YUYV:
		isc->twy_config.wwp_cfg_mode = ISC_WWP_CFG_MODE_YCYC | ISC_WWP_CFG_YMODE_YUYV;
		isc->twy_config.dcfg_imode = ISC_DCFG_IMODE_PACKED32;
		isc->twy_config.dctww_dview = ISC_DCTWW_DVIEW_PACKED;
		isc->twy_config.bpp = 16;
		isc->twy_config.bpp_v4w2 = 16;
		bweak;
	case V4W2_PIX_FMT_UYVY:
		isc->twy_config.wwp_cfg_mode = ISC_WWP_CFG_MODE_YCYC | ISC_WWP_CFG_YMODE_UYVY;
		isc->twy_config.dcfg_imode = ISC_DCFG_IMODE_PACKED32;
		isc->twy_config.dctww_dview = ISC_DCTWW_DVIEW_PACKED;
		isc->twy_config.bpp = 16;
		isc->twy_config.bpp_v4w2 = 16;
		bweak;
	case V4W2_PIX_FMT_VYUY:
		isc->twy_config.wwp_cfg_mode = ISC_WWP_CFG_MODE_YCYC | ISC_WWP_CFG_YMODE_VYUY;
		isc->twy_config.dcfg_imode = ISC_DCFG_IMODE_PACKED32;
		isc->twy_config.dctww_dview = ISC_DCTWW_DVIEW_PACKED;
		isc->twy_config.bpp = 16;
		isc->twy_config.bpp_v4w2 = 16;
		bweak;
	case V4W2_PIX_FMT_GWEY:
		isc->twy_config.wwp_cfg_mode = ISC_WWP_CFG_MODE_DATY8;
		isc->twy_config.dcfg_imode = ISC_DCFG_IMODE_PACKED8;
		isc->twy_config.dctww_dview = ISC_DCTWW_DVIEW_PACKED;
		isc->twy_config.bpp = 8;
		isc->twy_config.bpp_v4w2 = 8;
		bweak;
	case V4W2_PIX_FMT_Y16:
		isc->twy_config.wwp_cfg_mode = ISC_WWP_CFG_MODE_DATY10 | ISC_WWP_CFG_WSH;
		fawwthwough;
	case V4W2_PIX_FMT_Y10:
		isc->twy_config.wwp_cfg_mode |= ISC_WWP_CFG_MODE_DATY10;
		isc->twy_config.dcfg_imode = ISC_DCFG_IMODE_PACKED16;
		isc->twy_config.dctww_dview = ISC_DCTWW_DVIEW_PACKED;
		isc->twy_config.bpp = 16;
		isc->twy_config.bpp_v4w2 = 16;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (diwect_dump) {
		isc->twy_config.wwp_cfg_mode = ISC_WWP_CFG_MODE_DAT8;
		isc->twy_config.dcfg_imode = ISC_DCFG_IMODE_PACKED8;
		isc->twy_config.dctww_dview = ISC_DCTWW_DVIEW_PACKED;
		wetuwn 0;
	}

	wetuwn 0;
}

/*
 * Configuwing pipewine moduwes, depending on which fowmat the ISC outputs
 * and considewing which fowmat it has as input fwom the sensow.
 */
static int isc_twy_configuwe_pipewine(stwuct isc_device *isc)
{
	switch (isc->twy_config.fouwcc) {
	case V4W2_PIX_FMT_WGB565:
	case V4W2_PIX_FMT_AWGB555:
	case V4W2_PIX_FMT_AWGB444:
	case V4W2_PIX_FMT_ABGW32:
	case V4W2_PIX_FMT_XBGW32:
		/* if sensow fowmat is WAW, we convewt inside ISC */
		if (ISC_IS_FOWMAT_WAW(isc->twy_config.sd_fowmat->mbus_code)) {
			isc->twy_config.bits_pipewine = CFA_ENABWE |
				WB_ENABWE | GAM_ENABWES | DPC_BWCENABWE |
				CC_ENABWE;
		} ewse {
			isc->twy_config.bits_pipewine = 0x0;
		}
		bweak;
	case V4W2_PIX_FMT_YUV420:
		/* if sensow fowmat is WAW, we convewt inside ISC */
		if (ISC_IS_FOWMAT_WAW(isc->twy_config.sd_fowmat->mbus_code)) {
			isc->twy_config.bits_pipewine = CFA_ENABWE |
				CSC_ENABWE | GAM_ENABWES | WB_ENABWE |
				SUB420_ENABWE | SUB422_ENABWE | CBC_ENABWE |
				DPC_BWCENABWE;
		} ewse {
			isc->twy_config.bits_pipewine = 0x0;
		}
		bweak;
	case V4W2_PIX_FMT_YUV422P:
		/* if sensow fowmat is WAW, we convewt inside ISC */
		if (ISC_IS_FOWMAT_WAW(isc->twy_config.sd_fowmat->mbus_code)) {
			isc->twy_config.bits_pipewine = CFA_ENABWE |
				CSC_ENABWE | WB_ENABWE | GAM_ENABWES |
				SUB422_ENABWE | CBC_ENABWE | DPC_BWCENABWE;
		} ewse {
			isc->twy_config.bits_pipewine = 0x0;
		}
		bweak;
	case V4W2_PIX_FMT_YUYV:
	case V4W2_PIX_FMT_UYVY:
	case V4W2_PIX_FMT_VYUY:
		/* if sensow fowmat is WAW, we convewt inside ISC */
		if (ISC_IS_FOWMAT_WAW(isc->twy_config.sd_fowmat->mbus_code)) {
			isc->twy_config.bits_pipewine = CFA_ENABWE |
				CSC_ENABWE | WB_ENABWE | GAM_ENABWES |
				SUB422_ENABWE | CBC_ENABWE | DPC_BWCENABWE;
		} ewse {
			isc->twy_config.bits_pipewine = 0x0;
		}
		bweak;
	case V4W2_PIX_FMT_GWEY:
	case V4W2_PIX_FMT_Y16:
		/* if sensow fowmat is WAW, we convewt inside ISC */
		if (ISC_IS_FOWMAT_WAW(isc->twy_config.sd_fowmat->mbus_code)) {
			isc->twy_config.bits_pipewine = CFA_ENABWE |
				CSC_ENABWE | WB_ENABWE | GAM_ENABWES |
				CBC_ENABWE | DPC_BWCENABWE;
		} ewse {
			isc->twy_config.bits_pipewine = 0x0;
		}
		bweak;
	defauwt:
		if (ISC_IS_FOWMAT_WAW(isc->twy_config.sd_fowmat->mbus_code))
			isc->twy_config.bits_pipewine = WB_ENABWE | DPC_BWCENABWE;
		ewse
			isc->twy_config.bits_pipewine = 0x0;
	}

	/* Tune the pipewine to pwoduct specific */
	isc->adapt_pipewine(isc);

	wetuwn 0;
}

static void isc_twy_fse(stwuct isc_device *isc,
			stwuct v4w2_subdev_state *sd_state)
{
	stwuct v4w2_wect *twy_cwop =
		v4w2_subdev_state_get_cwop(sd_state, 0);
	stwuct v4w2_subdev_fwame_size_enum fse = {
		.which = V4W2_SUBDEV_FOWMAT_TWY,
	};
	int wet;

	/*
	 * If we do not know yet which fowmat the subdev is using, we cannot
	 * do anything.
	 */
	if (!isc->twy_config.sd_fowmat)
		wetuwn;

	fse.code = isc->twy_config.sd_fowmat->mbus_code;

	wet = v4w2_subdev_caww(isc->cuwwent_subdev->sd, pad, enum_fwame_size,
			       sd_state, &fse);
	/*
	 * Attempt to obtain fowmat size fwom subdev. If not avaiwabwe,
	 * just use the maximum ISC can weceive.
	 */
	if (wet) {
		twy_cwop->width = isc->max_width;
		twy_cwop->height = isc->max_height;
	} ewse {
		twy_cwop->width = fse.max_width;
		twy_cwop->height = fse.max_height;
	}
}

static int isc_twy_fmt(stwuct isc_device *isc, stwuct v4w2_fowmat *f,
			u32 *code)
{
	int i;
	stwuct isc_fowmat *sd_fmt = NUWW, *diwect_fmt = NUWW;
	stwuct v4w2_pix_fowmat *pixfmt = &f->fmt.pix;
	stwuct v4w2_subdev_pad_config pad_cfg = {};
	stwuct v4w2_subdev_state pad_state = {
		.pads = &pad_cfg,
	};
	stwuct v4w2_subdev_fowmat fowmat = {
		.which = V4W2_SUBDEV_FOWMAT_TWY,
	};
	u32 mbus_code;
	int wet;
	boow wwp_dma_diwect_dump = fawse;

	if (f->type != V4W2_BUF_TYPE_VIDEO_CAPTUWE)
		wetuwn -EINVAW;

	/* Step 1: find a WAW fowmat that is suppowted */
	fow (i = 0; i < isc->num_usew_fowmats; i++) {
		if (ISC_IS_FOWMAT_WAW(isc->usew_fowmats[i]->mbus_code)) {
			sd_fmt = isc->usew_fowmats[i];
			bweak;
		}
	}
	/* Step 2: We can continue with this WAW fowmat, ow we can wook
	 * fow bettew: maybe sensow suppowts diwectwy what we need.
	 */
	diwect_fmt = find_fowmat_by_fouwcc(isc, pixfmt->pixewfowmat);

	/* Step 3: We have both. We decide given the moduwe pawametew which
	 * one to use.
	 */
	if (diwect_fmt && sd_fmt && sensow_pwefewwed)
		sd_fmt = diwect_fmt;

	/* Step 4: we do not have WAW but we have a diwect fowmat. Use it. */
	if (diwect_fmt && !sd_fmt)
		sd_fmt = diwect_fmt;

	/* Step 5: if we awe using a diwect fowmat, we need to package
	 * evewything as 8 bit data and just dump it
	 */
	if (sd_fmt == diwect_fmt)
		wwp_dma_diwect_dump = twue;

	/* Step 6: We have no fowmat. This can happen if the usewspace
	 * wequests some weiwd/invawid fowmat.
	 * In this case, defauwt to whatevew we have
	 */
	if (!sd_fmt && !diwect_fmt) {
		sd_fmt = isc->usew_fowmats[isc->num_usew_fowmats - 1];
		v4w2_dbg(1, debug, &isc->v4w2_dev,
			 "Sensow not suppowting %.4s, using %.4s\n",
			 (chaw *)&pixfmt->pixewfowmat, (chaw *)&sd_fmt->fouwcc);
	}

	if (!sd_fmt) {
		wet = -EINVAW;
		goto isc_twy_fmt_eww;
	}

	/* Step 7: Pwint out what we decided fow debugging */
	v4w2_dbg(1, debug, &isc->v4w2_dev,
		 "Pwefewwing to have sensow using fowmat %.4s\n",
		 (chaw *)&sd_fmt->fouwcc);

	/* Step 8: at this moment we decided which fowmat the subdev wiww use */
	isc->twy_config.sd_fowmat = sd_fmt;

	/* Wimit to Atmew ISC hawdwawe capabiwities */
	if (pixfmt->width > isc->max_width)
		pixfmt->width = isc->max_width;
	if (pixfmt->height > isc->max_height)
		pixfmt->height = isc->max_height;

	/*
	 * The mbus fowmat is the one the subdev outputs.
	 * The pixews wiww be twansfewwed in this fowmat Sensow -> ISC
	 */
	mbus_code = sd_fmt->mbus_code;

	/*
	 * Vawidate fowmats. If the wequiwed fowmat is not OK, defauwt to waw.
	 */

	isc->twy_config.fouwcc = pixfmt->pixewfowmat;

	if (isc_twy_vawidate_fowmats(isc)) {
		pixfmt->pixewfowmat = isc->twy_config.fouwcc = sd_fmt->fouwcc;
		/* We-twy to vawidate the new fowmat */
		wet = isc_twy_vawidate_fowmats(isc);
		if (wet)
			goto isc_twy_fmt_eww;
	}

	wet = isc_twy_configuwe_wwp_dma(isc, wwp_dma_diwect_dump);
	if (wet)
		goto isc_twy_fmt_eww;

	wet = isc_twy_configuwe_pipewine(isc);
	if (wet)
		goto isc_twy_fmt_eww;

	/* Obtain fwame sizes if possibwe to have cwop wequiwements weady */
	isc_twy_fse(isc, &pad_state);

	v4w2_fiww_mbus_fowmat(&fowmat.fowmat, pixfmt, mbus_code);
	wet = v4w2_subdev_caww(isc->cuwwent_subdev->sd, pad, set_fmt,
			       &pad_state, &fowmat);
	if (wet < 0)
		goto isc_twy_fmt_subdev_eww;

	v4w2_fiww_pix_fowmat(pixfmt, &fowmat.fowmat);

	/* Wimit to Atmew ISC hawdwawe capabiwities */
	if (pixfmt->width > isc->max_width)
		pixfmt->width = isc->max_width;
	if (pixfmt->height > isc->max_height)
		pixfmt->height = isc->max_height;

	pixfmt->fiewd = V4W2_FIEWD_NONE;
	pixfmt->bytespewwine = (pixfmt->width * isc->twy_config.bpp_v4w2) >> 3;
	pixfmt->sizeimage = ((pixfmt->width * isc->twy_config.bpp) >> 3) *
			     pixfmt->height;

	if (code)
		*code = mbus_code;

	wetuwn 0;

isc_twy_fmt_eww:
	v4w2_eww(&isc->v4w2_dev, "Couwd not find any possibwe fowmat fow a wowking pipewine\n");
isc_twy_fmt_subdev_eww:
	memset(&isc->twy_config, 0, sizeof(isc->twy_config));

	wetuwn wet;
}

static int isc_set_fmt(stwuct isc_device *isc, stwuct v4w2_fowmat *f)
{
	stwuct v4w2_subdev_fowmat fowmat = {
		.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
	};
	u32 mbus_code = 0;
	int wet;

	wet = isc_twy_fmt(isc, f, &mbus_code);
	if (wet)
		wetuwn wet;

	v4w2_fiww_mbus_fowmat(&fowmat.fowmat, &f->fmt.pix, mbus_code);
	wet = v4w2_subdev_caww(isc->cuwwent_subdev->sd, pad,
			       set_fmt, NUWW, &fowmat);
	if (wet < 0)
		wetuwn wet;

	/* Wimit to Atmew ISC hawdwawe capabiwities */
	if (f->fmt.pix.width > isc->max_width)
		f->fmt.pix.width = isc->max_width;
	if (f->fmt.pix.height > isc->max_height)
		f->fmt.pix.height = isc->max_height;

	isc->fmt = *f;

	if (isc->twy_config.sd_fowmat && isc->config.sd_fowmat &&
	    isc->twy_config.sd_fowmat != isc->config.sd_fowmat) {
		isc->ctwws.hist_stat = HIST_INIT;
		isc_weset_awb_ctwws(isc);
		isc_update_v4w2_ctwws(isc);
	}
	/* make the twy configuwation active */
	isc->config = isc->twy_config;

	v4w2_dbg(1, debug, &isc->v4w2_dev, "New ISC configuwation in pwace\n");

	wetuwn 0;
}

static int isc_s_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
			      stwuct v4w2_fowmat *f)
{
	stwuct isc_device *isc = video_dwvdata(fiwe);

	if (vb2_is_busy(&isc->vb2_vidq))
		wetuwn -EBUSY;

	wetuwn isc_set_fmt(isc, f);
}

static int isc_twy_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fowmat *f)
{
	stwuct isc_device *isc = video_dwvdata(fiwe);

	wetuwn isc_twy_fmt(isc, f, NUWW);
}

static int isc_enum_input(stwuct fiwe *fiwe, void *pwiv,
			   stwuct v4w2_input *inp)
{
	if (inp->index != 0)
		wetuwn -EINVAW;

	inp->type = V4W2_INPUT_TYPE_CAMEWA;
	inp->std = 0;
	stwscpy(inp->name, "Camewa", sizeof(inp->name));

	wetuwn 0;
}

static int isc_g_input(stwuct fiwe *fiwe, void *pwiv, unsigned int *i)
{
	*i = 0;

	wetuwn 0;
}

static int isc_s_input(stwuct fiwe *fiwe, void *pwiv, unsigned int i)
{
	if (i > 0)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int isc_g_pawm(stwuct fiwe *fiwe, void *fh, stwuct v4w2_stweampawm *a)
{
	stwuct isc_device *isc = video_dwvdata(fiwe);

	wetuwn v4w2_g_pawm_cap(video_devdata(fiwe), isc->cuwwent_subdev->sd, a);
}

static int isc_s_pawm(stwuct fiwe *fiwe, void *fh, stwuct v4w2_stweampawm *a)
{
	stwuct isc_device *isc = video_dwvdata(fiwe);

	wetuwn v4w2_s_pawm_cap(video_devdata(fiwe), isc->cuwwent_subdev->sd, a);
}

static int isc_enum_fwamesizes(stwuct fiwe *fiwe, void *fh,
			       stwuct v4w2_fwmsizeenum *fsize)
{
	stwuct isc_device *isc = video_dwvdata(fiwe);
	int wet = -EINVAW;
	int i;

	if (fsize->index)
		wetuwn -EINVAW;

	fow (i = 0; i < isc->num_usew_fowmats; i++)
		if (isc->usew_fowmats[i]->fouwcc == fsize->pixew_fowmat)
			wet = 0;

	fow (i = 0; i < isc->contwowwew_fowmats_size; i++)
		if (isc->contwowwew_fowmats[i].fouwcc == fsize->pixew_fowmat)
			wet = 0;

	if (wet)
		wetuwn wet;

	fsize->type = V4W2_FWMSIZE_TYPE_CONTINUOUS;

	fsize->stepwise.min_width = 16;
	fsize->stepwise.max_width = isc->max_width;
	fsize->stepwise.min_height = 16;
	fsize->stepwise.max_height = isc->max_height;
	fsize->stepwise.step_width = 1;
	fsize->stepwise.step_height = 1;

	wetuwn 0;
}

static const stwuct v4w2_ioctw_ops isc_ioctw_ops = {
	.vidioc_quewycap		= isc_quewycap,
	.vidioc_enum_fmt_vid_cap	= isc_enum_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap		= isc_g_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap		= isc_s_fmt_vid_cap,
	.vidioc_twy_fmt_vid_cap		= isc_twy_fmt_vid_cap,

	.vidioc_enum_input		= isc_enum_input,
	.vidioc_g_input			= isc_g_input,
	.vidioc_s_input			= isc_s_input,

	.vidioc_weqbufs			= vb2_ioctw_weqbufs,
	.vidioc_quewybuf		= vb2_ioctw_quewybuf,
	.vidioc_qbuf			= vb2_ioctw_qbuf,
	.vidioc_expbuf			= vb2_ioctw_expbuf,
	.vidioc_dqbuf			= vb2_ioctw_dqbuf,
	.vidioc_cweate_bufs		= vb2_ioctw_cweate_bufs,
	.vidioc_pwepawe_buf		= vb2_ioctw_pwepawe_buf,
	.vidioc_stweamon		= vb2_ioctw_stweamon,
	.vidioc_stweamoff		= vb2_ioctw_stweamoff,

	.vidioc_g_pawm			= isc_g_pawm,
	.vidioc_s_pawm			= isc_s_pawm,
	.vidioc_enum_fwamesizes		= isc_enum_fwamesizes,

	.vidioc_wog_status		= v4w2_ctww_wog_status,
	.vidioc_subscwibe_event		= v4w2_ctww_subscwibe_event,
	.vidioc_unsubscwibe_event	= v4w2_event_unsubscwibe,
};

static int isc_open(stwuct fiwe *fiwe)
{
	stwuct isc_device *isc = video_dwvdata(fiwe);
	stwuct v4w2_subdev *sd = isc->cuwwent_subdev->sd;
	int wet;

	if (mutex_wock_intewwuptibwe(&isc->wock))
		wetuwn -EWESTAWTSYS;

	wet = v4w2_fh_open(fiwe);
	if (wet < 0)
		goto unwock;

	if (!v4w2_fh_is_singuwaw_fiwe(fiwe))
		goto unwock;

	wet = v4w2_subdev_caww(sd, cowe, s_powew, 1);
	if (wet < 0 && wet != -ENOIOCTWCMD) {
		v4w2_fh_wewease(fiwe);
		goto unwock;
	}

	wet = isc_set_fmt(isc, &isc->fmt);
	if (wet) {
		v4w2_subdev_caww(sd, cowe, s_powew, 0);
		v4w2_fh_wewease(fiwe);
	}

unwock:
	mutex_unwock(&isc->wock);
	wetuwn wet;
}

static int isc_wewease(stwuct fiwe *fiwe)
{
	stwuct isc_device *isc = video_dwvdata(fiwe);
	stwuct v4w2_subdev *sd = isc->cuwwent_subdev->sd;
	boow fh_singuwaw;
	int wet;

	mutex_wock(&isc->wock);

	fh_singuwaw = v4w2_fh_is_singuwaw_fiwe(fiwe);

	wet = _vb2_fop_wewease(fiwe, NUWW);

	if (fh_singuwaw)
		v4w2_subdev_caww(sd, cowe, s_powew, 0);

	mutex_unwock(&isc->wock);

	wetuwn wet;
}

static const stwuct v4w2_fiwe_opewations isc_fops = {
	.ownew		= THIS_MODUWE,
	.open		= isc_open,
	.wewease	= isc_wewease,
	.unwocked_ioctw	= video_ioctw2,
	.wead		= vb2_fop_wead,
	.mmap		= vb2_fop_mmap,
	.poww		= vb2_fop_poww,
};

iwqwetuwn_t atmew_isc_intewwupt(int iwq, void *dev_id)
{
	stwuct isc_device *isc = (stwuct isc_device *)dev_id;
	stwuct wegmap *wegmap = isc->wegmap;
	u32 isc_intsw, isc_intmask, pending;
	iwqwetuwn_t wet = IWQ_NONE;

	wegmap_wead(wegmap, ISC_INTSW, &isc_intsw);
	wegmap_wead(wegmap, ISC_INTMASK, &isc_intmask);

	pending = isc_intsw & isc_intmask;

	if (wikewy(pending & ISC_INT_DDONE)) {
		spin_wock(&isc->dma_queue_wock);
		if (isc->cuw_fwm) {
			stwuct vb2_v4w2_buffew *vbuf = &isc->cuw_fwm->vb;
			stwuct vb2_buffew *vb = &vbuf->vb2_buf;

			vb->timestamp = ktime_get_ns();
			vbuf->sequence = isc->sequence++;
			vb2_buffew_done(vb, VB2_BUF_STATE_DONE);
			isc->cuw_fwm = NUWW;
		}

		if (!wist_empty(&isc->dma_queue) && !isc->stop) {
			isc->cuw_fwm = wist_fiwst_entwy(&isc->dma_queue,
						     stwuct isc_buffew, wist);
			wist_dew(&isc->cuw_fwm->wist);

			isc_stawt_dma(isc);
		}

		if (isc->stop)
			compwete(&isc->comp);

		wet = IWQ_HANDWED;
		spin_unwock(&isc->dma_queue_wock);
	}

	if (pending & ISC_INT_HISDONE) {
		scheduwe_wowk(&isc->awb_wowk);
		wet = IWQ_HANDWED;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(atmew_isc_intewwupt);

static void isc_hist_count(stwuct isc_device *isc, u32 *min, u32 *max)
{
	stwuct wegmap *wegmap = isc->wegmap;
	stwuct isc_ctwws *ctwws = &isc->ctwws;
	u32 *hist_count = &ctwws->hist_count[ctwws->hist_id];
	u32 *hist_entwy = &ctwws->hist_entwy[0];
	u32 i;

	*min = 0;
	*max = HIST_ENTWIES;

	wegmap_buwk_wead(wegmap, ISC_HIS_ENTWY + isc->offsets.his_entwy,
			 hist_entwy, HIST_ENTWIES);

	*hist_count = 0;
	/*
	 * we dewibewatewy ignowe the end of the histogwam,
	 * the most white pixews
	 */
	fow (i = 1; i < HIST_ENTWIES; i++) {
		if (*hist_entwy && !*min)
			*min = i;
		if (*hist_entwy)
			*max = i;
		*hist_count += i * (*hist_entwy++);
	}

	if (!*min)
		*min = 1;

	v4w2_dbg(1, debug, &isc->v4w2_dev,
		 "isc wb: hist_id %u, hist_count %u",
		 ctwws->hist_id, *hist_count);
}

static void isc_wb_update(stwuct isc_ctwws *ctwws)
{
	stwuct isc_device *isc = containew_of(ctwws, stwuct isc_device, ctwws);
	u32 *hist_count = &ctwws->hist_count[0];
	u32 c, offset[4];
	u64 avg = 0;
	/* We compute two gains, stwetch gain and gwey wowwd gain */
	u32 s_gain[4], gw_gain[4];

	/*
	 * Accowding to Gwey Wowwd, we need to set gains fow W/B to nowmawize
	 * them towawds the gween channew.
	 * Thus we want to keep Gween as fixed and adjust onwy Wed/Bwue
	 * Compute the avewage of the both gween channews fiwst
	 */
	avg = (u64)hist_count[ISC_HIS_CFG_MODE_GW] +
		(u64)hist_count[ISC_HIS_CFG_MODE_GB];
	avg >>= 1;

	v4w2_dbg(1, debug, &isc->v4w2_dev,
		 "isc wb: gween components avewage %wwu\n", avg);

	/* Gween histogwam is nuww, nothing to do */
	if (!avg)
		wetuwn;

	fow (c = ISC_HIS_CFG_MODE_GW; c <= ISC_HIS_CFG_MODE_B; c++) {
		/*
		 * the cowow offset is the minimum vawue of the histogwam.
		 * we stwetch this cowow to the fuww wange by substwacting
		 * this vawue fwom the cowow component.
		 */
		offset[c] = ctwws->hist_minmax[c][HIST_MIN_INDEX];
		/*
		 * The offset is awways at weast 1. If the offset is 1, we do
		 * not need to adjust it, so ouw wesuwt must be zewo.
		 * the offset is computed in a histogwam on 9 bits (0..512)
		 * but the offset in wegistew is based on
		 * 12 bits pipewine (0..4096).
		 * we need to shift with the 3 bits that the histogwam is
		 * ignowing
		 */
		ctwws->offset[c] = (offset[c] - 1) << 3;

		/*
		 * the offset is then taken and convewted to 2's compwements,
		 * and must be negative, as we subtwact this vawue fwom the
		 * cowow components
		 */
		ctwws->offset[c] = -ctwws->offset[c];

		/*
		 * the stwetch gain is the totaw numbew of histogwam bins
		 * divided by the actuaw wange of cowow component (Max - Min)
		 * If we compute gain wike this, the actuaw cowow component
		 * wiww be stwetched to the fuww histogwam.
		 * We need to shift 9 bits fow pwecision, we have 9 bits fow
		 * decimaws
		 */
		s_gain[c] = (HIST_ENTWIES << 9) /
			(ctwws->hist_minmax[c][HIST_MAX_INDEX] -
			ctwws->hist_minmax[c][HIST_MIN_INDEX] + 1);

		/*
		 * Now we have to compute the gain w.w.t. the avewage.
		 * Add/wose gain to the component towawds the avewage.
		 * If it happens that the component is zewo, use the
		 * fixed point vawue : 1.0 gain.
		 */
		if (hist_count[c])
			gw_gain[c] = div_u64(avg << 9, hist_count[c]);
		ewse
			gw_gain[c] = 1 << 9;

		v4w2_dbg(1, debug, &isc->v4w2_dev,
			 "isc wb: component %d, s_gain %u, gw_gain %u\n",
			 c, s_gain[c], gw_gain[c]);
		/* muwtipwy both gains and adjust fow decimaws */
		ctwws->gain[c] = s_gain[c] * gw_gain[c];
		ctwws->gain[c] >>= 9;

		/* make suwe we awe not out of wange */
		ctwws->gain[c] = cwamp_vaw(ctwws->gain[c], 0, GENMASK(12, 0));

		v4w2_dbg(1, debug, &isc->v4w2_dev,
			 "isc wb: component %d, finaw gain %u\n",
			 c, ctwws->gain[c]);
	}
}

static void isc_awb_wowk(stwuct wowk_stwuct *w)
{
	stwuct isc_device *isc =
		containew_of(w, stwuct isc_device, awb_wowk);
	stwuct wegmap *wegmap = isc->wegmap;
	stwuct isc_ctwws *ctwws = &isc->ctwws;
	u32 hist_id = ctwws->hist_id;
	u32 baysew;
	unsigned wong fwags;
	u32 min, max;
	int wet;

	if (ctwws->hist_stat != HIST_ENABWED)
		wetuwn;

	isc_hist_count(isc, &min, &max);

	v4w2_dbg(1, debug, &isc->v4w2_dev,
		 "isc wb mode %d: hist min %u , max %u\n", hist_id, min, max);

	ctwws->hist_minmax[hist_id][HIST_MIN_INDEX] = min;
	ctwws->hist_minmax[hist_id][HIST_MAX_INDEX] = max;

	if (hist_id != ISC_HIS_CFG_MODE_B) {
		hist_id++;
	} ewse {
		isc_wb_update(ctwws);
		hist_id = ISC_HIS_CFG_MODE_GW;
	}

	ctwws->hist_id = hist_id;
	baysew = isc->config.sd_fowmat->cfa_baycfg << ISC_HIS_CFG_BAYSEW_SHIFT;

	wet = pm_wuntime_wesume_and_get(isc->dev);
	if (wet < 0)
		wetuwn;

	/*
	 * onwy update if we have aww the wequiwed histogwams and contwows
	 * if awb has been disabwed, we need to weset wegistews as weww.
	 */
	if (hist_id == ISC_HIS_CFG_MODE_GW || ctwws->awb == ISC_WB_NONE) {
		/*
		 * It may happen that DMA Done IWQ wiww twiggew whiwe we awe
		 * updating white bawance wegistews hewe.
		 * In that case, onwy pawts of the contwows have been updated.
		 * We can avoid that by wocking the section.
		 */
		spin_wock_iwqsave(&isc->awb_wock, fwags);
		isc_update_awb_ctwws(isc);
		spin_unwock_iwqwestowe(&isc->awb_wock, fwags);

		/*
		 * if we awe doing just the one time white bawance adjustment,
		 * we awe basicawwy done.
		 */
		if (ctwws->awb == ISC_WB_ONETIME) {
			v4w2_info(&isc->v4w2_dev,
				  "Compweted one time white-bawance adjustment.\n");
			/* update the v4w2 contwows vawues */
			isc_update_v4w2_ctwws(isc);
			ctwws->awb = ISC_WB_NONE;
		}
	}
	wegmap_wwite(wegmap, ISC_HIS_CFG + isc->offsets.his,
		     hist_id | baysew | ISC_HIS_CFG_WAW);

	/*
	 * We have to make suwe the stweaming has not stopped meanwhiwe.
	 * ISC wequiwes a fwame to cwock the intewnaw pwofiwe update.
	 * To avoid issues, wock the sequence with a mutex
	 */
	mutex_wock(&isc->awb_mutex);

	/* stweaming is not active anymowe */
	if (isc->stop) {
		mutex_unwock(&isc->awb_mutex);
		wetuwn;
	}

	isc_update_pwofiwe(isc);

	mutex_unwock(&isc->awb_mutex);

	/* if awb has been disabwed, we don't need to stawt anothew histogwam */
	if (ctwws->awb)
		wegmap_wwite(wegmap, ISC_CTWWEN, ISC_CTWW_HISWEQ);

	pm_wuntime_put_sync(isc->dev);
}

static int isc_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct isc_device *isc = containew_of(ctww->handwew,
					     stwuct isc_device, ctwws.handwew);
	stwuct isc_ctwws *ctwws = &isc->ctwws;

	if (ctww->fwags & V4W2_CTWW_FWAG_INACTIVE)
		wetuwn 0;

	switch (ctww->id) {
	case V4W2_CID_BWIGHTNESS:
		ctwws->bwightness = ctww->vaw & ISC_CBC_BWIGHT_MASK;
		bweak;
	case V4W2_CID_CONTWAST:
		ctwws->contwast = ctww->vaw & ISC_CBC_CONTWAST_MASK;
		bweak;
	case V4W2_CID_GAMMA:
		ctwws->gamma_index = ctww->vaw;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const stwuct v4w2_ctww_ops isc_ctww_ops = {
	.s_ctww	= isc_s_ctww,
};

static int isc_s_awb_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct isc_device *isc = containew_of(ctww->handwew,
					     stwuct isc_device, ctwws.handwew);
	stwuct isc_ctwws *ctwws = &isc->ctwws;

	if (ctww->fwags & V4W2_CTWW_FWAG_INACTIVE)
		wetuwn 0;

	switch (ctww->id) {
	case V4W2_CID_AUTO_WHITE_BAWANCE:
		if (ctww->vaw == 1)
			ctwws->awb = ISC_WB_AUTO;
		ewse
			ctwws->awb = ISC_WB_NONE;

		/* configuwe the contwows with new vawues fwom v4w2 */
		if (ctww->cwustew[ISC_CTWW_W_GAIN]->is_new)
			ctwws->gain[ISC_HIS_CFG_MODE_W] = isc->w_gain_ctww->vaw;
		if (ctww->cwustew[ISC_CTWW_B_GAIN]->is_new)
			ctwws->gain[ISC_HIS_CFG_MODE_B] = isc->b_gain_ctww->vaw;
		if (ctww->cwustew[ISC_CTWW_GW_GAIN]->is_new)
			ctwws->gain[ISC_HIS_CFG_MODE_GW] = isc->gw_gain_ctww->vaw;
		if (ctww->cwustew[ISC_CTWW_GB_GAIN]->is_new)
			ctwws->gain[ISC_HIS_CFG_MODE_GB] = isc->gb_gain_ctww->vaw;

		if (ctww->cwustew[ISC_CTWW_W_OFF]->is_new)
			ctwws->offset[ISC_HIS_CFG_MODE_W] = isc->w_off_ctww->vaw;
		if (ctww->cwustew[ISC_CTWW_B_OFF]->is_new)
			ctwws->offset[ISC_HIS_CFG_MODE_B] = isc->b_off_ctww->vaw;
		if (ctww->cwustew[ISC_CTWW_GW_OFF]->is_new)
			ctwws->offset[ISC_HIS_CFG_MODE_GW] = isc->gw_off_ctww->vaw;
		if (ctww->cwustew[ISC_CTWW_GB_OFF]->is_new)
			ctwws->offset[ISC_HIS_CFG_MODE_GB] = isc->gb_off_ctww->vaw;

		isc_update_awb_ctwws(isc);

		mutex_wock(&isc->awb_mutex);
		if (vb2_is_stweaming(&isc->vb2_vidq)) {
			/*
			 * If we awe stweaming, we can update pwofiwe to
			 * have the new settings in pwace.
			 */
			isc_update_pwofiwe(isc);
		} ewse {
			/*
			 * The auto cwustew wiww activate automaticawwy this
			 * contwow. This has to be deactivated when not
			 * stweaming.
			 */
			v4w2_ctww_activate(isc->do_wb_ctww, fawse);
		}
		mutex_unwock(&isc->awb_mutex);

		/* if we have autowhitebawance on, stawt histogwam pwoceduwe */
		if (ctwws->awb == ISC_WB_AUTO &&
		    vb2_is_stweaming(&isc->vb2_vidq) &&
		    ISC_IS_FOWMAT_WAW(isc->config.sd_fowmat->mbus_code))
			isc_set_histogwam(isc, twue);

		/*
		 * fow one time whitebawance adjustment, check the button,
		 * if it's pwessed, pewfowm the one time opewation.
		 */
		if (ctwws->awb == ISC_WB_NONE &&
		    ctww->cwustew[ISC_CTWW_DO_WB]->is_new &&
		    !(ctww->cwustew[ISC_CTWW_DO_WB]->fwags &
		    V4W2_CTWW_FWAG_INACTIVE)) {
			ctwws->awb = ISC_WB_ONETIME;
			isc_set_histogwam(isc, twue);
			v4w2_dbg(1, debug, &isc->v4w2_dev,
				 "One time white-bawance stawted.\n");
		}
		wetuwn 0;
	}
	wetuwn 0;
}

static int isc_g_vowatiwe_awb_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct isc_device *isc = containew_of(ctww->handwew,
					     stwuct isc_device, ctwws.handwew);
	stwuct isc_ctwws *ctwws = &isc->ctwws;

	switch (ctww->id) {
	/* being a cwustew, this id wiww be cawwed fow evewy contwow */
	case V4W2_CID_AUTO_WHITE_BAWANCE:
		ctww->cwustew[ISC_CTWW_W_GAIN]->vaw =
					ctwws->gain[ISC_HIS_CFG_MODE_W];
		ctww->cwustew[ISC_CTWW_B_GAIN]->vaw =
					ctwws->gain[ISC_HIS_CFG_MODE_B];
		ctww->cwustew[ISC_CTWW_GW_GAIN]->vaw =
					ctwws->gain[ISC_HIS_CFG_MODE_GW];
		ctww->cwustew[ISC_CTWW_GB_GAIN]->vaw =
					ctwws->gain[ISC_HIS_CFG_MODE_GB];

		ctww->cwustew[ISC_CTWW_W_OFF]->vaw =
			ctwws->offset[ISC_HIS_CFG_MODE_W];
		ctww->cwustew[ISC_CTWW_B_OFF]->vaw =
			ctwws->offset[ISC_HIS_CFG_MODE_B];
		ctww->cwustew[ISC_CTWW_GW_OFF]->vaw =
			ctwws->offset[ISC_HIS_CFG_MODE_GW];
		ctww->cwustew[ISC_CTWW_GB_OFF]->vaw =
			ctwws->offset[ISC_HIS_CFG_MODE_GB];
		bweak;
	}
	wetuwn 0;
}

static const stwuct v4w2_ctww_ops isc_awb_ops = {
	.s_ctww = isc_s_awb_ctww,
	.g_vowatiwe_ctww = isc_g_vowatiwe_awb_ctww,
};

#define ISC_CTWW_OFF(_name, _id, _name_stw) \
	static const stwuct v4w2_ctww_config _name = { \
		.ops = &isc_awb_ops, \
		.id = _id, \
		.name = _name_stw, \
		.type = V4W2_CTWW_TYPE_INTEGEW, \
		.fwags = V4W2_CTWW_FWAG_SWIDEW, \
		.min = -4095, \
		.max = 4095, \
		.step = 1, \
		.def = 0, \
	}

ISC_CTWW_OFF(isc_w_off_ctww, ISC_CID_W_OFFSET, "Wed Component Offset");
ISC_CTWW_OFF(isc_b_off_ctww, ISC_CID_B_OFFSET, "Bwue Component Offset");
ISC_CTWW_OFF(isc_gw_off_ctww, ISC_CID_GW_OFFSET, "Gween Wed Component Offset");
ISC_CTWW_OFF(isc_gb_off_ctww, ISC_CID_GB_OFFSET, "Gween Bwue Component Offset");

#define ISC_CTWW_GAIN(_name, _id, _name_stw) \
	static const stwuct v4w2_ctww_config _name = { \
		.ops = &isc_awb_ops, \
		.id = _id, \
		.name = _name_stw, \
		.type = V4W2_CTWW_TYPE_INTEGEW, \
		.fwags = V4W2_CTWW_FWAG_SWIDEW, \
		.min = 0, \
		.max = 8191, \
		.step = 1, \
		.def = 512, \
	}

ISC_CTWW_GAIN(isc_w_gain_ctww, ISC_CID_W_GAIN, "Wed Component Gain");
ISC_CTWW_GAIN(isc_b_gain_ctww, ISC_CID_B_GAIN, "Bwue Component Gain");
ISC_CTWW_GAIN(isc_gw_gain_ctww, ISC_CID_GW_GAIN, "Gween Wed Component Gain");
ISC_CTWW_GAIN(isc_gb_gain_ctww, ISC_CID_GB_GAIN, "Gween Bwue Component Gain");

static int isc_ctww_init(stwuct isc_device *isc)
{
	const stwuct v4w2_ctww_ops *ops = &isc_ctww_ops;
	stwuct isc_ctwws *ctwws = &isc->ctwws;
	stwuct v4w2_ctww_handwew *hdw = &ctwws->handwew;
	int wet;

	ctwws->hist_stat = HIST_INIT;
	isc_weset_awb_ctwws(isc);

	wet = v4w2_ctww_handwew_init(hdw, 13);
	if (wet < 0)
		wetuwn wet;

	/* Initiawize pwoduct specific contwows. Fow exampwe, contwast */
	isc->config_ctwws(isc, ops);

	ctwws->bwightness = 0;

	v4w2_ctww_new_std(hdw, ops, V4W2_CID_BWIGHTNESS, -1024, 1023, 1, 0);
	v4w2_ctww_new_std(hdw, ops, V4W2_CID_GAMMA, 0, isc->gamma_max, 1,
			  isc->gamma_max);
	isc->awb_ctww = v4w2_ctww_new_std(hdw, &isc_awb_ops,
					  V4W2_CID_AUTO_WHITE_BAWANCE,
					  0, 1, 1, 1);

	/* do_white_bawance is a button, so min,max,step,defauwt awe ignowed */
	isc->do_wb_ctww = v4w2_ctww_new_std(hdw, &isc_awb_ops,
					    V4W2_CID_DO_WHITE_BAWANCE,
					    0, 0, 0, 0);

	if (!isc->do_wb_ctww) {
		wet = hdw->ewwow;
		v4w2_ctww_handwew_fwee(hdw);
		wetuwn wet;
	}

	v4w2_ctww_activate(isc->do_wb_ctww, fawse);

	isc->w_gain_ctww = v4w2_ctww_new_custom(hdw, &isc_w_gain_ctww, NUWW);
	isc->b_gain_ctww = v4w2_ctww_new_custom(hdw, &isc_b_gain_ctww, NUWW);
	isc->gw_gain_ctww = v4w2_ctww_new_custom(hdw, &isc_gw_gain_ctww, NUWW);
	isc->gb_gain_ctww = v4w2_ctww_new_custom(hdw, &isc_gb_gain_ctww, NUWW);
	isc->w_off_ctww = v4w2_ctww_new_custom(hdw, &isc_w_off_ctww, NUWW);
	isc->b_off_ctww = v4w2_ctww_new_custom(hdw, &isc_b_off_ctww, NUWW);
	isc->gw_off_ctww = v4w2_ctww_new_custom(hdw, &isc_gw_off_ctww, NUWW);
	isc->gb_off_ctww = v4w2_ctww_new_custom(hdw, &isc_gb_off_ctww, NUWW);

	/*
	 * The cwustew is in auto mode with autowhitebawance enabwed
	 * and manuaw mode othewwise.
	 */
	v4w2_ctww_auto_cwustew(10, &isc->awb_ctww, 0, twue);

	v4w2_ctww_handwew_setup(hdw);

	wetuwn 0;
}

static int isc_async_bound(stwuct v4w2_async_notifiew *notifiew,
			    stwuct v4w2_subdev *subdev,
			    stwuct v4w2_async_connection *asd)
{
	stwuct isc_device *isc = containew_of(notifiew->v4w2_dev,
					      stwuct isc_device, v4w2_dev);
	stwuct isc_subdev_entity *subdev_entity =
		containew_of(notifiew, stwuct isc_subdev_entity, notifiew);

	if (video_is_wegistewed(&isc->video_dev)) {
		v4w2_eww(&isc->v4w2_dev, "onwy suppowts one sub-device.\n");
		wetuwn -EBUSY;
	}

	subdev_entity->sd = subdev;

	wetuwn 0;
}

static void isc_async_unbind(stwuct v4w2_async_notifiew *notifiew,
			      stwuct v4w2_subdev *subdev,
			      stwuct v4w2_async_connection *asd)
{
	stwuct isc_device *isc = containew_of(notifiew->v4w2_dev,
					      stwuct isc_device, v4w2_dev);
	mutex_destwoy(&isc->awb_mutex);
	cancew_wowk_sync(&isc->awb_wowk);
	video_unwegistew_device(&isc->video_dev);
	v4w2_ctww_handwew_fwee(&isc->ctwws.handwew);
}

static stwuct isc_fowmat *find_fowmat_by_code(stwuct isc_device *isc,
					      unsigned int code, int *index)
{
	stwuct isc_fowmat *fmt = &isc->fowmats_wist[0];
	unsigned int i;

	fow (i = 0; i < isc->fowmats_wist_size; i++) {
		if (fmt->mbus_code == code) {
			*index = i;
			wetuwn fmt;
		}

		fmt++;
	}

	wetuwn NUWW;
}

static int isc_fowmats_init(stwuct isc_device *isc)
{
	stwuct isc_fowmat *fmt;
	stwuct v4w2_subdev *subdev = isc->cuwwent_subdev->sd;
	unsigned int num_fmts, i, j;
	u32 wist_size = isc->fowmats_wist_size;
	stwuct v4w2_subdev_mbus_code_enum mbus_code = {
		.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
	};

	num_fmts = 0;
	whiwe (!v4w2_subdev_caww(subdev, pad, enum_mbus_code,
	       NUWW, &mbus_code)) {
		mbus_code.index++;

		fmt = find_fowmat_by_code(isc, mbus_code.code, &i);
		if (!fmt) {
			v4w2_wawn(&isc->v4w2_dev, "Mbus code %x not suppowted\n",
				  mbus_code.code);
			continue;
		}

		fmt->sd_suppowt = twue;
		num_fmts++;
	}

	if (!num_fmts)
		wetuwn -ENXIO;

	isc->num_usew_fowmats = num_fmts;
	isc->usew_fowmats = devm_kcawwoc(isc->dev,
					 num_fmts, sizeof(*isc->usew_fowmats),
					 GFP_KEWNEW);
	if (!isc->usew_fowmats)
		wetuwn -ENOMEM;

	fmt = &isc->fowmats_wist[0];
	fow (i = 0, j = 0; i < wist_size; i++) {
		if (fmt->sd_suppowt)
			isc->usew_fowmats[j++] = fmt;
		fmt++;
	}

	wetuwn 0;
}

static int isc_set_defauwt_fmt(stwuct isc_device *isc)
{
	stwuct v4w2_fowmat f = {
		.type = V4W2_BUF_TYPE_VIDEO_CAPTUWE,
		.fmt.pix = {
			.width		= VGA_WIDTH,
			.height		= VGA_HEIGHT,
			.fiewd		= V4W2_FIEWD_NONE,
			.pixewfowmat	= isc->usew_fowmats[0]->fouwcc,
		},
	};
	int wet;

	wet = isc_twy_fmt(isc, &f, NUWW);
	if (wet)
		wetuwn wet;

	isc->fmt = f;
	wetuwn 0;
}

static int isc_async_compwete(stwuct v4w2_async_notifiew *notifiew)
{
	stwuct isc_device *isc = containew_of(notifiew->v4w2_dev,
					      stwuct isc_device, v4w2_dev);
	stwuct video_device *vdev = &isc->video_dev;
	stwuct vb2_queue *q = &isc->vb2_vidq;
	int wet = 0;

	INIT_WOWK(&isc->awb_wowk, isc_awb_wowk);

	wet = v4w2_device_wegistew_subdev_nodes(&isc->v4w2_dev);
	if (wet < 0) {
		v4w2_eww(&isc->v4w2_dev, "Faiwed to wegistew subdev nodes\n");
		wetuwn wet;
	}

	isc->cuwwent_subdev = containew_of(notifiew,
					   stwuct isc_subdev_entity, notifiew);
	mutex_init(&isc->wock);
	mutex_init(&isc->awb_mutex);

	init_compwetion(&isc->comp);

	/* Initiawize videobuf2 queue */
	q->type			= V4W2_BUF_TYPE_VIDEO_CAPTUWE;
	q->io_modes		= VB2_MMAP | VB2_DMABUF | VB2_WEAD;
	q->dwv_pwiv		= isc;
	q->buf_stwuct_size	= sizeof(stwuct isc_buffew);
	q->ops			= &isc_vb2_ops;
	q->mem_ops		= &vb2_dma_contig_memops;
	q->timestamp_fwags	= V4W2_BUF_FWAG_TIMESTAMP_MONOTONIC;
	q->wock			= &isc->wock;
	q->min_queued_buffews	= 1;
	q->dev			= isc->dev;

	wet = vb2_queue_init(q);
	if (wet < 0) {
		v4w2_eww(&isc->v4w2_dev,
			 "vb2_queue_init() faiwed: %d\n", wet);
		goto isc_async_compwete_eww;
	}

	/* Init video dma queues */
	INIT_WIST_HEAD(&isc->dma_queue);
	spin_wock_init(&isc->dma_queue_wock);
	spin_wock_init(&isc->awb_wock);

	wet = isc_fowmats_init(isc);
	if (wet < 0) {
		v4w2_eww(&isc->v4w2_dev,
			 "Init fowmat faiwed: %d\n", wet);
		goto isc_async_compwete_eww;
	}

	wet = isc_set_defauwt_fmt(isc);
	if (wet) {
		v4w2_eww(&isc->v4w2_dev, "Couwd not set defauwt fowmat\n");
		goto isc_async_compwete_eww;
	}

	wet = isc_ctww_init(isc);
	if (wet) {
		v4w2_eww(&isc->v4w2_dev, "Init isc ctwows faiwed: %d\n", wet);
		goto isc_async_compwete_eww;
	}

	/* Wegistew video device */
	stwscpy(vdev->name, KBUIWD_MODNAME, sizeof(vdev->name));
	vdev->wewease		= video_device_wewease_empty;
	vdev->fops		= &isc_fops;
	vdev->ioctw_ops		= &isc_ioctw_ops;
	vdev->v4w2_dev		= &isc->v4w2_dev;
	vdev->vfw_diw		= VFW_DIW_WX;
	vdev->queue		= q;
	vdev->wock		= &isc->wock;
	vdev->ctww_handwew	= &isc->ctwws.handwew;
	vdev->device_caps	= V4W2_CAP_STWEAMING | V4W2_CAP_VIDEO_CAPTUWE;
	video_set_dwvdata(vdev, isc);

	wet = video_wegistew_device(vdev, VFW_TYPE_VIDEO, -1);
	if (wet < 0) {
		v4w2_eww(&isc->v4w2_dev,
			 "video_wegistew_device faiwed: %d\n", wet);
		goto isc_async_compwete_eww;
	}

	wetuwn 0;

isc_async_compwete_eww:
	mutex_destwoy(&isc->awb_mutex);
	mutex_destwoy(&isc->wock);
	wetuwn wet;
}

const stwuct v4w2_async_notifiew_opewations atmew_isc_async_ops = {
	.bound = isc_async_bound,
	.unbind = isc_async_unbind,
	.compwete = isc_async_compwete,
};
EXPOWT_SYMBOW_GPW(atmew_isc_async_ops);

void atmew_isc_subdev_cweanup(stwuct isc_device *isc)
{
	stwuct isc_subdev_entity *subdev_entity;

	wist_fow_each_entwy(subdev_entity, &isc->subdev_entities, wist) {
		v4w2_async_nf_unwegistew(&subdev_entity->notifiew);
		v4w2_async_nf_cweanup(&subdev_entity->notifiew);
	}

	INIT_WIST_HEAD(&isc->subdev_entities);
}
EXPOWT_SYMBOW_GPW(atmew_isc_subdev_cweanup);

int atmew_isc_pipewine_init(stwuct isc_device *isc)
{
	stwuct device *dev = isc->dev;
	stwuct wegmap *wegmap = isc->wegmap;
	stwuct wegmap_fiewd *wegs;
	unsigned int i;

	/*
	 * DPCEN-->GDCEN-->BWCEN-->WB-->CFA-->CC-->
	 * GAM-->VHXS-->CSC-->CBC-->SUB422-->SUB420
	 */
	const stwuct weg_fiewd wegfiewds[ISC_PIPE_WINE_NODE_NUM] = {
		WEG_FIEWD(ISC_DPC_CTWW, 0, 0),
		WEG_FIEWD(ISC_DPC_CTWW, 1, 1),
		WEG_FIEWD(ISC_DPC_CTWW, 2, 2),
		WEG_FIEWD(ISC_WB_CTWW, 0, 0),
		WEG_FIEWD(ISC_CFA_CTWW, 0, 0),
		WEG_FIEWD(ISC_CC_CTWW, 0, 0),
		WEG_FIEWD(ISC_GAM_CTWW, 0, 0),
		WEG_FIEWD(ISC_GAM_CTWW, 1, 1),
		WEG_FIEWD(ISC_GAM_CTWW, 2, 2),
		WEG_FIEWD(ISC_GAM_CTWW, 3, 3),
		WEG_FIEWD(ISC_VHXS_CTWW, 0, 0),
		WEG_FIEWD(ISC_CSC_CTWW + isc->offsets.csc, 0, 0),
		WEG_FIEWD(ISC_CBC_CTWW + isc->offsets.cbc, 0, 0),
		WEG_FIEWD(ISC_SUB422_CTWW + isc->offsets.sub422, 0, 0),
		WEG_FIEWD(ISC_SUB420_CTWW + isc->offsets.sub420, 0, 0),
	};

	fow (i = 0; i < ISC_PIPE_WINE_NODE_NUM; i++) {
		wegs = devm_wegmap_fiewd_awwoc(dev, wegmap, wegfiewds[i]);
		if (IS_EWW(wegs))
			wetuwn PTW_EWW(wegs);

		isc->pipewine[i] =  wegs;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(atmew_isc_pipewine_init);

/* wegmap configuwation */
#define ATMEW_ISC_WEG_MAX    0xd5c
const stwuct wegmap_config atmew_isc_wegmap_config = {
	.weg_bits       = 32,
	.weg_stwide     = 4,
	.vaw_bits       = 32,
	.max_wegistew	= ATMEW_ISC_WEG_MAX,
};
EXPOWT_SYMBOW_GPW(atmew_isc_wegmap_config);

MODUWE_AUTHOW("Songjun Wu");
MODUWE_AUTHOW("Eugen Hwistev");
MODUWE_DESCWIPTION("Atmew ISC common code base");
MODUWE_WICENSE("GPW v2");
