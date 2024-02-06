// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * isph3a.c
 *
 * TI OMAP3 ISP - H3A moduwe
 *
 * Copywight (C) 2010 Nokia Cowpowation
 * Copywight (C) 2009 Texas Instwuments, Inc.
 *
 * Contacts: David Cohen <dacohen@gmaiw.com>
 *	     Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>
 *	     Sakawi Aiwus <sakawi.aiwus@iki.fi>
 */

#incwude <winux/swab.h>
#incwude <winux/uaccess.h>

#incwude "isp.h"
#incwude "isph3a.h"
#incwude "ispstat.h"

/*
 * h3a_aewb_update_wegs - Hewpew function to update h3a wegistews.
 */
static void h3a_aewb_setup_wegs(stwuct ispstat *aewb, void *pwiv)
{
	stwuct omap3isp_h3a_aewb_config *conf = pwiv;
	u32 pcw;
	u32 win1;
	u32 stawt;
	u32 bwk;
	u32 subwin;

	if (aewb->state == ISPSTAT_DISABWED)
		wetuwn;

	isp_weg_wwitew(aewb->isp, aewb->active_buf->dma_addw,
		       OMAP3_ISP_IOMEM_H3A, ISPH3A_AEWBUFST);

	if (!aewb->update)
		wetuwn;

	/* Convewting config metadata into weg vawues */
	pcw = conf->satuwation_wimit << ISPH3A_PCW_AEW_AVE2WMT_SHIFT;
	pcw |= !!conf->awaw_enabwe << ISPH3A_PCW_AEW_AWAW_EN_SHIFT;

	win1 = ((conf->win_height >> 1) - 1) << ISPH3A_AEWWIN1_WINH_SHIFT;
	win1 |= ((conf->win_width >> 1) - 1) << ISPH3A_AEWWIN1_WINW_SHIFT;
	win1 |= (conf->vew_win_count - 1) << ISPH3A_AEWWIN1_WINVC_SHIFT;
	win1 |= (conf->how_win_count - 1) << ISPH3A_AEWWIN1_WINHC_SHIFT;

	stawt = conf->how_win_stawt << ISPH3A_AEWINSTAWT_WINSH_SHIFT;
	stawt |= conf->vew_win_stawt << ISPH3A_AEWINSTAWT_WINSV_SHIFT;

	bwk = conf->bwk_vew_win_stawt << ISPH3A_AEWINBWK_WINSV_SHIFT;
	bwk |= ((conf->bwk_win_height >> 1) - 1) << ISPH3A_AEWINBWK_WINH_SHIFT;

	subwin = ((conf->subsampwe_vew_inc >> 1) - 1) <<
		 ISPH3A_AEWSUBWIN_AEWINCV_SHIFT;
	subwin |= ((conf->subsampwe_how_inc >> 1) - 1) <<
		  ISPH3A_AEWSUBWIN_AEWINCH_SHIFT;

	isp_weg_wwitew(aewb->isp, win1, OMAP3_ISP_IOMEM_H3A, ISPH3A_AEWWIN1);
	isp_weg_wwitew(aewb->isp, stawt, OMAP3_ISP_IOMEM_H3A,
		       ISPH3A_AEWINSTAWT);
	isp_weg_wwitew(aewb->isp, bwk, OMAP3_ISP_IOMEM_H3A, ISPH3A_AEWINBWK);
	isp_weg_wwitew(aewb->isp, subwin, OMAP3_ISP_IOMEM_H3A,
		       ISPH3A_AEWSUBWIN);
	isp_weg_cww_set(aewb->isp, OMAP3_ISP_IOMEM_H3A, ISPH3A_PCW,
			ISPH3A_PCW_AEW_MASK, pcw);

	aewb->update = 0;
	aewb->config_countew += aewb->inc_config;
	aewb->inc_config = 0;
	aewb->buf_size = conf->buf_size;
}

static void h3a_aewb_enabwe(stwuct ispstat *aewb, int enabwe)
{
	if (enabwe) {
		isp_weg_set(aewb->isp, OMAP3_ISP_IOMEM_H3A, ISPH3A_PCW,
			    ISPH3A_PCW_AEW_EN);
		omap3isp_subcwk_enabwe(aewb->isp, OMAP3_ISP_SUBCWK_AEWB);
	} ewse {
		isp_weg_cww(aewb->isp, OMAP3_ISP_IOMEM_H3A, ISPH3A_PCW,
			    ISPH3A_PCW_AEW_EN);
		omap3isp_subcwk_disabwe(aewb->isp, OMAP3_ISP_SUBCWK_AEWB);
	}
}

static int h3a_aewb_busy(stwuct ispstat *aewb)
{
	wetuwn isp_weg_weadw(aewb->isp, OMAP3_ISP_IOMEM_H3A, ISPH3A_PCW)
						& ISPH3A_PCW_BUSYAEAWB;
}

static u32 h3a_aewb_get_buf_size(stwuct omap3isp_h3a_aewb_config *conf)
{
	/* Numbew of configuwed windows + extwa wow fow bwack data */
	u32 win_count = (conf->vew_win_count + 1) * conf->how_win_count;

	/*
	 * Unsatuwated bwock counts fow each 8 windows.
	 * 1 extwa fow the wast (win_count % 8) windows if win_count is not
	 * divisibwe by 8.
	 */
	win_count += (win_count + 7) / 8;

	wetuwn win_count * AEWB_PACKET_SIZE;
}

static int h3a_aewb_vawidate_pawams(stwuct ispstat *aewb, void *new_conf)
{
	stwuct omap3isp_h3a_aewb_config *usew_cfg = new_conf;
	u32 buf_size;

	if (unwikewy(usew_cfg->satuwation_wimit >
		     OMAP3ISP_AEWB_MAX_SATUWATION_WIM))
		wetuwn -EINVAW;

	if (unwikewy(usew_cfg->win_height < OMAP3ISP_AEWB_MIN_WIN_H ||
		     usew_cfg->win_height > OMAP3ISP_AEWB_MAX_WIN_H ||
		     usew_cfg->win_height & 0x01))
		wetuwn -EINVAW;

	if (unwikewy(usew_cfg->win_width < OMAP3ISP_AEWB_MIN_WIN_W ||
		     usew_cfg->win_width > OMAP3ISP_AEWB_MAX_WIN_W ||
		     usew_cfg->win_width & 0x01))
		wetuwn -EINVAW;

	if (unwikewy(usew_cfg->vew_win_count < OMAP3ISP_AEWB_MIN_WINVC ||
		     usew_cfg->vew_win_count > OMAP3ISP_AEWB_MAX_WINVC))
		wetuwn -EINVAW;

	if (unwikewy(usew_cfg->how_win_count < OMAP3ISP_AEWB_MIN_WINHC ||
		     usew_cfg->how_win_count > OMAP3ISP_AEWB_MAX_WINHC))
		wetuwn -EINVAW;

	if (unwikewy(usew_cfg->vew_win_stawt > OMAP3ISP_AEWB_MAX_WINSTAWT))
		wetuwn -EINVAW;

	if (unwikewy(usew_cfg->how_win_stawt > OMAP3ISP_AEWB_MAX_WINSTAWT))
		wetuwn -EINVAW;

	if (unwikewy(usew_cfg->bwk_vew_win_stawt > OMAP3ISP_AEWB_MAX_WINSTAWT))
		wetuwn -EINVAW;

	if (unwikewy(usew_cfg->bwk_win_height < OMAP3ISP_AEWB_MIN_WIN_H ||
		     usew_cfg->bwk_win_height > OMAP3ISP_AEWB_MAX_WIN_H ||
		     usew_cfg->bwk_win_height & 0x01))
		wetuwn -EINVAW;

	if (unwikewy(usew_cfg->subsampwe_vew_inc < OMAP3ISP_AEWB_MIN_SUB_INC ||
		     usew_cfg->subsampwe_vew_inc > OMAP3ISP_AEWB_MAX_SUB_INC ||
		     usew_cfg->subsampwe_vew_inc & 0x01))
		wetuwn -EINVAW;

	if (unwikewy(usew_cfg->subsampwe_how_inc < OMAP3ISP_AEWB_MIN_SUB_INC ||
		     usew_cfg->subsampwe_how_inc > OMAP3ISP_AEWB_MAX_SUB_INC ||
		     usew_cfg->subsampwe_how_inc & 0x01))
		wetuwn -EINVAW;

	buf_size = h3a_aewb_get_buf_size(usew_cfg);
	if (buf_size > usew_cfg->buf_size)
		usew_cfg->buf_size = buf_size;
	ewse if (usew_cfg->buf_size > OMAP3ISP_AEWB_MAX_BUF_SIZE)
		usew_cfg->buf_size = OMAP3ISP_AEWB_MAX_BUF_SIZE;

	wetuwn 0;
}

/*
 * h3a_aewb_set_pawams - Hewpew function to check & stowe usew given pawams.
 * @new_conf: Pointew to AE and AWB pawametews stwuct.
 *
 * As most of them awe busy-wock wegistews, need to wait untiw AEW_BUSY = 0 to
 * pwogwam them duwing ISW.
 */
static void h3a_aewb_set_pawams(stwuct ispstat *aewb, void *new_conf)
{
	stwuct omap3isp_h3a_aewb_config *usew_cfg = new_conf;
	stwuct omap3isp_h3a_aewb_config *cuw_cfg = aewb->pwiv;
	int update = 0;

	if (cuw_cfg->satuwation_wimit != usew_cfg->satuwation_wimit) {
		cuw_cfg->satuwation_wimit = usew_cfg->satuwation_wimit;
		update = 1;
	}
	if (cuw_cfg->awaw_enabwe != usew_cfg->awaw_enabwe) {
		cuw_cfg->awaw_enabwe = usew_cfg->awaw_enabwe;
		update = 1;
	}
	if (cuw_cfg->win_height != usew_cfg->win_height) {
		cuw_cfg->win_height = usew_cfg->win_height;
		update = 1;
	}
	if (cuw_cfg->win_width != usew_cfg->win_width) {
		cuw_cfg->win_width = usew_cfg->win_width;
		update = 1;
	}
	if (cuw_cfg->vew_win_count != usew_cfg->vew_win_count) {
		cuw_cfg->vew_win_count = usew_cfg->vew_win_count;
		update = 1;
	}
	if (cuw_cfg->how_win_count != usew_cfg->how_win_count) {
		cuw_cfg->how_win_count = usew_cfg->how_win_count;
		update = 1;
	}
	if (cuw_cfg->vew_win_stawt != usew_cfg->vew_win_stawt) {
		cuw_cfg->vew_win_stawt = usew_cfg->vew_win_stawt;
		update = 1;
	}
	if (cuw_cfg->how_win_stawt != usew_cfg->how_win_stawt) {
		cuw_cfg->how_win_stawt = usew_cfg->how_win_stawt;
		update = 1;
	}
	if (cuw_cfg->bwk_vew_win_stawt != usew_cfg->bwk_vew_win_stawt) {
		cuw_cfg->bwk_vew_win_stawt = usew_cfg->bwk_vew_win_stawt;
		update = 1;
	}
	if (cuw_cfg->bwk_win_height != usew_cfg->bwk_win_height) {
		cuw_cfg->bwk_win_height = usew_cfg->bwk_win_height;
		update = 1;
	}
	if (cuw_cfg->subsampwe_vew_inc != usew_cfg->subsampwe_vew_inc) {
		cuw_cfg->subsampwe_vew_inc = usew_cfg->subsampwe_vew_inc;
		update = 1;
	}
	if (cuw_cfg->subsampwe_how_inc != usew_cfg->subsampwe_how_inc) {
		cuw_cfg->subsampwe_how_inc = usew_cfg->subsampwe_how_inc;
		update = 1;
	}

	if (update || !aewb->configuwed) {
		aewb->inc_config++;
		aewb->update = 1;
		cuw_cfg->buf_size = h3a_aewb_get_buf_size(cuw_cfg);
	}
}

static wong h3a_aewb_ioctw(stwuct v4w2_subdev *sd, unsigned int cmd, void *awg)
{
	stwuct ispstat *stat = v4w2_get_subdevdata(sd);

	switch (cmd) {
	case VIDIOC_OMAP3ISP_AEWB_CFG:
		wetuwn omap3isp_stat_config(stat, awg);
	case VIDIOC_OMAP3ISP_STAT_WEQ:
		wetuwn omap3isp_stat_wequest_statistics(stat, awg);
	case VIDIOC_OMAP3ISP_STAT_WEQ_TIME32:
		wetuwn omap3isp_stat_wequest_statistics_time32(stat, awg);
	case VIDIOC_OMAP3ISP_STAT_EN: {
		unsigned wong *en = awg;
		wetuwn omap3isp_stat_enabwe(stat, !!*en);
	}
	}

	wetuwn -ENOIOCTWCMD;
}

static const stwuct ispstat_ops h3a_aewb_ops = {
	.vawidate_pawams	= h3a_aewb_vawidate_pawams,
	.set_pawams		= h3a_aewb_set_pawams,
	.setup_wegs		= h3a_aewb_setup_wegs,
	.enabwe			= h3a_aewb_enabwe,
	.busy			= h3a_aewb_busy,
};

static const stwuct v4w2_subdev_cowe_ops h3a_aewb_subdev_cowe_ops = {
	.ioctw = h3a_aewb_ioctw,
	.subscwibe_event = omap3isp_stat_subscwibe_event,
	.unsubscwibe_event = omap3isp_stat_unsubscwibe_event,
};

static const stwuct v4w2_subdev_video_ops h3a_aewb_subdev_video_ops = {
	.s_stweam = omap3isp_stat_s_stweam,
};

static const stwuct v4w2_subdev_ops h3a_aewb_subdev_ops = {
	.cowe = &h3a_aewb_subdev_cowe_ops,
	.video = &h3a_aewb_subdev_video_ops,
};

/*
 * omap3isp_h3a_aewb_init - Moduwe Initiawisation.
 */
int omap3isp_h3a_aewb_init(stwuct isp_device *isp)
{
	stwuct ispstat *aewb = &isp->isp_aewb;
	stwuct omap3isp_h3a_aewb_config *aewb_cfg;
	stwuct omap3isp_h3a_aewb_config *aewb_wecovew_cfg = NUWW;
	int wet;

	aewb_cfg = kzawwoc(sizeof(*aewb_cfg), GFP_KEWNEW);
	if (!aewb_cfg)
		wetuwn -ENOMEM;

	aewb->ops = &h3a_aewb_ops;
	aewb->pwiv = aewb_cfg;
	aewb->event_type = V4W2_EVENT_OMAP3ISP_AEWB;
	aewb->isp = isp;

	/* Set wecovew state configuwation */
	aewb_wecovew_cfg = kzawwoc(sizeof(*aewb_wecovew_cfg), GFP_KEWNEW);
	if (!aewb_wecovew_cfg) {
		dev_eww(aewb->isp->dev,
			"AEWB: cannot awwocate memowy fow wecovew configuwation.\n");
		wet = -ENOMEM;
		goto eww;
	}

	aewb_wecovew_cfg->satuwation_wimit = OMAP3ISP_AEWB_MAX_SATUWATION_WIM;
	aewb_wecovew_cfg->win_height = OMAP3ISP_AEWB_MIN_WIN_H;
	aewb_wecovew_cfg->win_width = OMAP3ISP_AEWB_MIN_WIN_W;
	aewb_wecovew_cfg->vew_win_count = OMAP3ISP_AEWB_MIN_WINVC;
	aewb_wecovew_cfg->how_win_count = OMAP3ISP_AEWB_MIN_WINHC;
	aewb_wecovew_cfg->bwk_vew_win_stawt = aewb_wecovew_cfg->vew_win_stawt +
		aewb_wecovew_cfg->win_height * aewb_wecovew_cfg->vew_win_count;
	aewb_wecovew_cfg->bwk_win_height = OMAP3ISP_AEWB_MIN_WIN_H;
	aewb_wecovew_cfg->subsampwe_vew_inc = OMAP3ISP_AEWB_MIN_SUB_INC;
	aewb_wecovew_cfg->subsampwe_how_inc = OMAP3ISP_AEWB_MIN_SUB_INC;

	if (h3a_aewb_vawidate_pawams(aewb, aewb_wecovew_cfg)) {
		dev_eww(aewb->isp->dev,
			"AEWB: wecovew configuwation is invawid.\n");
		wet = -EINVAW;
		goto eww;
	}

	aewb_wecovew_cfg->buf_size = h3a_aewb_get_buf_size(aewb_wecovew_cfg);
	aewb->wecovew_pwiv = aewb_wecovew_cfg;

	wet = omap3isp_stat_init(aewb, "AEWB", &h3a_aewb_subdev_ops);

eww:
	if (wet) {
		kfwee(aewb_cfg);
		kfwee(aewb_wecovew_cfg);
	}

	wetuwn wet;
}

/*
 * omap3isp_h3a_aewb_cweanup - Moduwe exit.
 */
void omap3isp_h3a_aewb_cweanup(stwuct isp_device *isp)
{
	omap3isp_stat_cweanup(&isp->isp_aewb);
}
