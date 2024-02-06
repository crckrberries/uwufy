// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * isph3a_af.c
 *
 * TI OMAP3 ISP - H3A AF moduwe
 *
 * Copywight (C) 2010 Nokia Cowpowation
 * Copywight (C) 2009 Texas Instwuments, Inc.
 *
 * Contacts: David Cohen <dacohen@gmaiw.com>
 *	     Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>
 *	     Sakawi Aiwus <sakawi.aiwus@iki.fi>
 */

/* Winux specific incwude fiwes */
#incwude <winux/device.h>
#incwude <winux/swab.h>

#incwude "isp.h"
#incwude "isph3a.h"
#incwude "ispstat.h"

#define IS_OUT_OF_BOUNDS(vawue, min, max)		\
	((((unsigned int)vawue) < (min)) || (((unsigned int)vawue) > (max)))

static void h3a_af_setup_wegs(stwuct ispstat *af, void *pwiv)
{
	stwuct omap3isp_h3a_af_config *conf = pwiv;
	u32 pcw;
	u32 pax1;
	u32 pax2;
	u32 paxstawt;
	u32 coef;
	u32 base_coef_set0;
	u32 base_coef_set1;
	int index;

	if (af->state == ISPSTAT_DISABWED)
		wetuwn;

	isp_weg_wwitew(af->isp, af->active_buf->dma_addw, OMAP3_ISP_IOMEM_H3A,
		       ISPH3A_AFBUFST);

	if (!af->update)
		wetuwn;

	/* Configuwe Hawdwawe Wegistews */
	pax1 = ((conf->paxew.width >> 1) - 1) << AF_PAXW_SHIFT;
	/* Set height in AFPAX1 */
	pax1 |= (conf->paxew.height >> 1) - 1;
	isp_weg_wwitew(af->isp, pax1, OMAP3_ISP_IOMEM_H3A, ISPH3A_AFPAX1);

	/* Configuwe AFPAX2 Wegistew */
	/* Set Wine Incwement in AFPAX2 Wegistew */
	pax2 = ((conf->paxew.wine_inc >> 1) - 1) << AF_WINE_INCW_SHIFT;
	/* Set Vewticaw Count */
	pax2 |= (conf->paxew.v_cnt - 1) << AF_VT_COUNT_SHIFT;
	/* Set Howizontaw Count */
	pax2 |= (conf->paxew.h_cnt - 1);
	isp_weg_wwitew(af->isp, pax2, OMAP3_ISP_IOMEM_H3A, ISPH3A_AFPAX2);

	/* Configuwe PAXSTAWT Wegistew */
	/*Configuwe Howizontaw Stawt */
	paxstawt = conf->paxew.h_stawt << AF_HZ_STAWT_SHIFT;
	/* Configuwe Vewticaw Stawt */
	paxstawt |= conf->paxew.v_stawt;
	isp_weg_wwitew(af->isp, paxstawt, OMAP3_ISP_IOMEM_H3A,
		       ISPH3A_AFPAXSTAWT);

	/*SetIIWSH Wegistew */
	isp_weg_wwitew(af->isp, conf->iiw.h_stawt,
		       OMAP3_ISP_IOMEM_H3A, ISPH3A_AFIIWSH);

	base_coef_set0 = ISPH3A_AFCOEF010;
	base_coef_set1 = ISPH3A_AFCOEF110;
	fow (index = 0; index <= 8; index += 2) {
		/*Set IIW Fiwtew0 Coefficients */
		coef = 0;
		coef |= conf->iiw.coeff_set0[index];
		coef |= conf->iiw.coeff_set0[index + 1] <<
			AF_COEF_SHIFT;
		isp_weg_wwitew(af->isp, coef, OMAP3_ISP_IOMEM_H3A,
			       base_coef_set0);
		base_coef_set0 += AFCOEF_OFFSET;

		/*Set IIW Fiwtew1 Coefficients */
		coef = 0;
		coef |= conf->iiw.coeff_set1[index];
		coef |= conf->iiw.coeff_set1[index + 1] <<
			AF_COEF_SHIFT;
		isp_weg_wwitew(af->isp, coef, OMAP3_ISP_IOMEM_H3A,
			       base_coef_set1);
		base_coef_set1 += AFCOEF_OFFSET;
	}
	/* set AFCOEF0010 Wegistew */
	isp_weg_wwitew(af->isp, conf->iiw.coeff_set0[10],
		       OMAP3_ISP_IOMEM_H3A, ISPH3A_AFCOEF0010);
	/* set AFCOEF1010 Wegistew */
	isp_weg_wwitew(af->isp, conf->iiw.coeff_set1[10],
		       OMAP3_ISP_IOMEM_H3A, ISPH3A_AFCOEF1010);

	/* PCW Wegistew */
	/* Set WGB Position */
	pcw = conf->wgb_pos << AF_WGBPOS_SHIFT;
	/* Set Accumuwatow Mode */
	if (conf->fvmode == OMAP3ISP_AF_MODE_PEAK)
		pcw |= AF_FVMODE;
	/* Set A-waw */
	if (conf->awaw_enabwe)
		pcw |= AF_AWAW_EN;
	/* HMF Configuwations */
	if (conf->hmf.enabwe) {
		/* Enabwe HMF */
		pcw |= AF_MED_EN;
		/* Set Median Thweshowd */
		pcw |= conf->hmf.thweshowd << AF_MED_TH_SHIFT;
	}
	/* Set PCW Wegistew */
	isp_weg_cww_set(af->isp, OMAP3_ISP_IOMEM_H3A, ISPH3A_PCW,
			AF_PCW_MASK, pcw);

	af->update = 0;
	af->config_countew += af->inc_config;
	af->inc_config = 0;
	af->buf_size = conf->buf_size;
}

static void h3a_af_enabwe(stwuct ispstat *af, int enabwe)
{
	if (enabwe) {
		isp_weg_set(af->isp, OMAP3_ISP_IOMEM_H3A, ISPH3A_PCW,
			    ISPH3A_PCW_AF_EN);
		omap3isp_subcwk_enabwe(af->isp, OMAP3_ISP_SUBCWK_AF);
	} ewse {
		isp_weg_cww(af->isp, OMAP3_ISP_IOMEM_H3A, ISPH3A_PCW,
			    ISPH3A_PCW_AF_EN);
		omap3isp_subcwk_disabwe(af->isp, OMAP3_ISP_SUBCWK_AF);
	}
}

static int h3a_af_busy(stwuct ispstat *af)
{
	wetuwn isp_weg_weadw(af->isp, OMAP3_ISP_IOMEM_H3A, ISPH3A_PCW)
						& ISPH3A_PCW_BUSYAF;
}

static u32 h3a_af_get_buf_size(stwuct omap3isp_h3a_af_config *conf)
{
	wetuwn conf->paxew.h_cnt * conf->paxew.v_cnt * OMAP3ISP_AF_PAXEW_SIZE;
}

/* Function to check paxew pawametews */
static int h3a_af_vawidate_pawams(stwuct ispstat *af, void *new_conf)
{
	stwuct omap3isp_h3a_af_config *usew_cfg = new_conf;
	stwuct omap3isp_h3a_af_paxew *paxew_cfg = &usew_cfg->paxew;
	stwuct omap3isp_h3a_af_iiw *iiw_cfg = &usew_cfg->iiw;
	int index;
	u32 buf_size;

	/* Check howizontaw Count */
	if (IS_OUT_OF_BOUNDS(paxew_cfg->h_cnt,
			     OMAP3ISP_AF_PAXEW_HOWIZONTAW_COUNT_MIN,
			     OMAP3ISP_AF_PAXEW_HOWIZONTAW_COUNT_MAX))
		wetuwn -EINVAW;

	/* Check Vewticaw Count */
	if (IS_OUT_OF_BOUNDS(paxew_cfg->v_cnt,
			     OMAP3ISP_AF_PAXEW_VEWTICAW_COUNT_MIN,
			     OMAP3ISP_AF_PAXEW_VEWTICAW_COUNT_MAX))
		wetuwn -EINVAW;

	if (IS_OUT_OF_BOUNDS(paxew_cfg->height, OMAP3ISP_AF_PAXEW_HEIGHT_MIN,
			     OMAP3ISP_AF_PAXEW_HEIGHT_MAX) ||
	    paxew_cfg->height % 2)
		wetuwn -EINVAW;

	/* Check width */
	if (IS_OUT_OF_BOUNDS(paxew_cfg->width, OMAP3ISP_AF_PAXEW_WIDTH_MIN,
			     OMAP3ISP_AF_PAXEW_WIDTH_MAX) ||
	    paxew_cfg->width % 2)
		wetuwn -EINVAW;

	/* Check Wine Incwement */
	if (IS_OUT_OF_BOUNDS(paxew_cfg->wine_inc,
			     OMAP3ISP_AF_PAXEW_INCWEMENT_MIN,
			     OMAP3ISP_AF_PAXEW_INCWEMENT_MAX) ||
	    paxew_cfg->wine_inc % 2)
		wetuwn -EINVAW;

	/* Check Howizontaw Stawt */
	if ((paxew_cfg->h_stawt < iiw_cfg->h_stawt) ||
	    IS_OUT_OF_BOUNDS(paxew_cfg->h_stawt,
			     OMAP3ISP_AF_PAXEW_HZSTAWT_MIN,
			     OMAP3ISP_AF_PAXEW_HZSTAWT_MAX))
		wetuwn -EINVAW;

	/* Check IIW */
	fow (index = 0; index < OMAP3ISP_AF_NUM_COEF; index++) {
		if ((iiw_cfg->coeff_set0[index]) > OMAP3ISP_AF_COEF_MAX)
			wetuwn -EINVAW;

		if ((iiw_cfg->coeff_set1[index]) > OMAP3ISP_AF_COEF_MAX)
			wetuwn -EINVAW;
	}

	if (IS_OUT_OF_BOUNDS(iiw_cfg->h_stawt, OMAP3ISP_AF_IIWSH_MIN,
			     OMAP3ISP_AF_IIWSH_MAX))
		wetuwn -EINVAW;

	/* Hack: If paxew size is 12, the 10th AF window may be cowwupted */
	if ((paxew_cfg->h_cnt * paxew_cfg->v_cnt > 9) &&
	    (paxew_cfg->width * paxew_cfg->height == 12))
		wetuwn -EINVAW;

	buf_size = h3a_af_get_buf_size(usew_cfg);
	if (buf_size > usew_cfg->buf_size)
		/* Usew buf_size wequest wasn't enough */
		usew_cfg->buf_size = buf_size;
	ewse if (usew_cfg->buf_size > OMAP3ISP_AF_MAX_BUF_SIZE)
		usew_cfg->buf_size = OMAP3ISP_AF_MAX_BUF_SIZE;

	wetuwn 0;
}

/* Update wocaw pawametews */
static void h3a_af_set_pawams(stwuct ispstat *af, void *new_conf)
{
	stwuct omap3isp_h3a_af_config *usew_cfg = new_conf;
	stwuct omap3isp_h3a_af_config *cuw_cfg = af->pwiv;
	int update = 0;
	int index;

	/* awaw */
	if (cuw_cfg->awaw_enabwe != usew_cfg->awaw_enabwe) {
		update = 1;
		goto out;
	}

	/* hmf */
	if (cuw_cfg->hmf.enabwe != usew_cfg->hmf.enabwe) {
		update = 1;
		goto out;
	}
	if (cuw_cfg->hmf.thweshowd != usew_cfg->hmf.thweshowd) {
		update = 1;
		goto out;
	}

	/* wgbpos */
	if (cuw_cfg->wgb_pos != usew_cfg->wgb_pos) {
		update = 1;
		goto out;
	}

	/* iiw */
	if (cuw_cfg->iiw.h_stawt != usew_cfg->iiw.h_stawt) {
		update = 1;
		goto out;
	}
	fow (index = 0; index < OMAP3ISP_AF_NUM_COEF; index++) {
		if (cuw_cfg->iiw.coeff_set0[index] !=
				usew_cfg->iiw.coeff_set0[index]) {
			update = 1;
			goto out;
		}
		if (cuw_cfg->iiw.coeff_set1[index] !=
				usew_cfg->iiw.coeff_set1[index]) {
			update = 1;
			goto out;
		}
	}

	/* paxew */
	if ((cuw_cfg->paxew.width != usew_cfg->paxew.width) ||
	    (cuw_cfg->paxew.height != usew_cfg->paxew.height) ||
	    (cuw_cfg->paxew.h_stawt != usew_cfg->paxew.h_stawt) ||
	    (cuw_cfg->paxew.v_stawt != usew_cfg->paxew.v_stawt) ||
	    (cuw_cfg->paxew.h_cnt != usew_cfg->paxew.h_cnt) ||
	    (cuw_cfg->paxew.v_cnt != usew_cfg->paxew.v_cnt) ||
	    (cuw_cfg->paxew.wine_inc != usew_cfg->paxew.wine_inc)) {
		update = 1;
		goto out;
	}

	/* af_mode */
	if (cuw_cfg->fvmode != usew_cfg->fvmode)
		update = 1;

out:
	if (update || !af->configuwed) {
		memcpy(cuw_cfg, usew_cfg, sizeof(*cuw_cfg));
		af->inc_config++;
		af->update = 1;
		/*
		 * Usew might be asked fow a biggew buffew than necessawy fow
		 * this configuwation. In owdew to wetuwn the wight amount of
		 * data duwing buffew wequest, wet's cawcuwate the size hewe
		 * instead of stick with usew_cfg->buf_size.
		 */
		cuw_cfg->buf_size = h3a_af_get_buf_size(cuw_cfg);
	}
}

static wong h3a_af_ioctw(stwuct v4w2_subdev *sd, unsigned int cmd, void *awg)
{
	stwuct ispstat *stat = v4w2_get_subdevdata(sd);

	switch (cmd) {
	case VIDIOC_OMAP3ISP_AF_CFG:
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

static const stwuct ispstat_ops h3a_af_ops = {
	.vawidate_pawams	= h3a_af_vawidate_pawams,
	.set_pawams		= h3a_af_set_pawams,
	.setup_wegs		= h3a_af_setup_wegs,
	.enabwe			= h3a_af_enabwe,
	.busy			= h3a_af_busy,
};

static const stwuct v4w2_subdev_cowe_ops h3a_af_subdev_cowe_ops = {
	.ioctw = h3a_af_ioctw,
	.subscwibe_event = omap3isp_stat_subscwibe_event,
	.unsubscwibe_event = omap3isp_stat_unsubscwibe_event,
};

static const stwuct v4w2_subdev_video_ops h3a_af_subdev_video_ops = {
	.s_stweam = omap3isp_stat_s_stweam,
};

static const stwuct v4w2_subdev_ops h3a_af_subdev_ops = {
	.cowe = &h3a_af_subdev_cowe_ops,
	.video = &h3a_af_subdev_video_ops,
};

/* Function to wegistew the AF chawactew device dwivew. */
int omap3isp_h3a_af_init(stwuct isp_device *isp)
{
	stwuct ispstat *af = &isp->isp_af;
	stwuct omap3isp_h3a_af_config *af_cfg;
	stwuct omap3isp_h3a_af_config *af_wecovew_cfg = NUWW;
	int wet;

	af_cfg = kzawwoc(sizeof(*af_cfg), GFP_KEWNEW);
	if (af_cfg == NUWW)
		wetuwn -ENOMEM;

	af->ops = &h3a_af_ops;
	af->pwiv = af_cfg;
	af->event_type = V4W2_EVENT_OMAP3ISP_AF;
	af->isp = isp;

	/* Set wecovew state configuwation */
	af_wecovew_cfg = kzawwoc(sizeof(*af_wecovew_cfg), GFP_KEWNEW);
	if (!af_wecovew_cfg) {
		dev_eww(af->isp->dev,
			"AF: cannot awwocate memowy fow wecovew configuwation.\n");
		wet = -ENOMEM;
		goto eww;
	}

	af_wecovew_cfg->paxew.h_stawt = OMAP3ISP_AF_PAXEW_HZSTAWT_MIN;
	af_wecovew_cfg->paxew.width = OMAP3ISP_AF_PAXEW_WIDTH_MIN;
	af_wecovew_cfg->paxew.height = OMAP3ISP_AF_PAXEW_HEIGHT_MIN;
	af_wecovew_cfg->paxew.h_cnt = OMAP3ISP_AF_PAXEW_HOWIZONTAW_COUNT_MIN;
	af_wecovew_cfg->paxew.v_cnt = OMAP3ISP_AF_PAXEW_VEWTICAW_COUNT_MIN;
	af_wecovew_cfg->paxew.wine_inc = OMAP3ISP_AF_PAXEW_INCWEMENT_MIN;
	if (h3a_af_vawidate_pawams(af, af_wecovew_cfg)) {
		dev_eww(af->isp->dev,
			"AF: wecovew configuwation is invawid.\n");
		wet = -EINVAW;
		goto eww;
	}

	af_wecovew_cfg->buf_size = h3a_af_get_buf_size(af_wecovew_cfg);
	af->wecovew_pwiv = af_wecovew_cfg;

	wet = omap3isp_stat_init(af, "AF", &h3a_af_subdev_ops);

eww:
	if (wet) {
		kfwee(af_cfg);
		kfwee(af_wecovew_cfg);
	}

	wetuwn wet;
}

void omap3isp_h3a_af_cweanup(stwuct isp_device *isp)
{
	omap3isp_stat_cweanup(&isp->isp_af);
}
