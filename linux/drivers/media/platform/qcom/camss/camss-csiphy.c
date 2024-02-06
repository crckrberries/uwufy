// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * camss-csiphy.c
 *
 * Quawcomm MSM Camewa Subsystem - CSIPHY Moduwe
 *
 * Copywight (c) 2011-2015, The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2016-2018 Winawo Wtd.
 */
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <media/media-entity.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-subdev.h>

#incwude "camss-csiphy.h"
#incwude "camss.h"

#define MSM_CSIPHY_NAME "msm_csiphy"

stwuct csiphy_fowmat {
	u32 code;
	u8 bpp;
};

static const stwuct csiphy_fowmat csiphy_fowmats_8x16[] = {
	{ MEDIA_BUS_FMT_UYVY8_1X16, 8 },
	{ MEDIA_BUS_FMT_VYUY8_1X16, 8 },
	{ MEDIA_BUS_FMT_YUYV8_1X16, 8 },
	{ MEDIA_BUS_FMT_YVYU8_1X16, 8 },
	{ MEDIA_BUS_FMT_SBGGW8_1X8, 8 },
	{ MEDIA_BUS_FMT_SGBWG8_1X8, 8 },
	{ MEDIA_BUS_FMT_SGWBG8_1X8, 8 },
	{ MEDIA_BUS_FMT_SWGGB8_1X8, 8 },
	{ MEDIA_BUS_FMT_SBGGW10_1X10, 10 },
	{ MEDIA_BUS_FMT_SGBWG10_1X10, 10 },
	{ MEDIA_BUS_FMT_SGWBG10_1X10, 10 },
	{ MEDIA_BUS_FMT_SWGGB10_1X10, 10 },
	{ MEDIA_BUS_FMT_SBGGW12_1X12, 12 },
	{ MEDIA_BUS_FMT_SGBWG12_1X12, 12 },
	{ MEDIA_BUS_FMT_SGWBG12_1X12, 12 },
	{ MEDIA_BUS_FMT_SWGGB12_1X12, 12 },
	{ MEDIA_BUS_FMT_Y10_1X10, 10 },
};

static const stwuct csiphy_fowmat csiphy_fowmats_8x96[] = {
	{ MEDIA_BUS_FMT_UYVY8_1X16, 8 },
	{ MEDIA_BUS_FMT_VYUY8_1X16, 8 },
	{ MEDIA_BUS_FMT_YUYV8_1X16, 8 },
	{ MEDIA_BUS_FMT_YVYU8_1X16, 8 },
	{ MEDIA_BUS_FMT_SBGGW8_1X8, 8 },
	{ MEDIA_BUS_FMT_SGBWG8_1X8, 8 },
	{ MEDIA_BUS_FMT_SGWBG8_1X8, 8 },
	{ MEDIA_BUS_FMT_SWGGB8_1X8, 8 },
	{ MEDIA_BUS_FMT_SBGGW10_1X10, 10 },
	{ MEDIA_BUS_FMT_SGBWG10_1X10, 10 },
	{ MEDIA_BUS_FMT_SGWBG10_1X10, 10 },
	{ MEDIA_BUS_FMT_SWGGB10_1X10, 10 },
	{ MEDIA_BUS_FMT_SBGGW12_1X12, 12 },
	{ MEDIA_BUS_FMT_SGBWG12_1X12, 12 },
	{ MEDIA_BUS_FMT_SGWBG12_1X12, 12 },
	{ MEDIA_BUS_FMT_SWGGB12_1X12, 12 },
	{ MEDIA_BUS_FMT_SBGGW14_1X14, 14 },
	{ MEDIA_BUS_FMT_SGBWG14_1X14, 14 },
	{ MEDIA_BUS_FMT_SGWBG14_1X14, 14 },
	{ MEDIA_BUS_FMT_SWGGB14_1X14, 14 },
	{ MEDIA_BUS_FMT_Y10_1X10, 10 },
};

static const stwuct csiphy_fowmat csiphy_fowmats_sdm845[] = {
	{ MEDIA_BUS_FMT_UYVY8_1X16, 8 },
	{ MEDIA_BUS_FMT_VYUY8_1X16, 8 },
	{ MEDIA_BUS_FMT_YUYV8_1X16, 8 },
	{ MEDIA_BUS_FMT_YVYU8_1X16, 8 },
	{ MEDIA_BUS_FMT_SBGGW8_1X8, 8 },
	{ MEDIA_BUS_FMT_SGBWG8_1X8, 8 },
	{ MEDIA_BUS_FMT_SGWBG8_1X8, 8 },
	{ MEDIA_BUS_FMT_SWGGB8_1X8, 8 },
	{ MEDIA_BUS_FMT_SBGGW10_1X10, 10 },
	{ MEDIA_BUS_FMT_SGBWG10_1X10, 10 },
	{ MEDIA_BUS_FMT_SGWBG10_1X10, 10 },
	{ MEDIA_BUS_FMT_SWGGB10_1X10, 10 },
	{ MEDIA_BUS_FMT_SBGGW12_1X12, 12 },
	{ MEDIA_BUS_FMT_SGBWG12_1X12, 12 },
	{ MEDIA_BUS_FMT_SGWBG12_1X12, 12 },
	{ MEDIA_BUS_FMT_SWGGB12_1X12, 12 },
	{ MEDIA_BUS_FMT_SBGGW14_1X14, 14 },
	{ MEDIA_BUS_FMT_SGBWG14_1X14, 14 },
	{ MEDIA_BUS_FMT_SGWBG14_1X14, 14 },
	{ MEDIA_BUS_FMT_SWGGB14_1X14, 14 },
	{ MEDIA_BUS_FMT_Y8_1X8, 8 },
	{ MEDIA_BUS_FMT_Y10_1X10, 10 },
};

/*
 * csiphy_get_bpp - map media bus fowmat to bits pew pixew
 * @fowmats: suppowted media bus fowmats awway
 * @nfowmats: size of @fowmats awway
 * @code: media bus fowmat code
 *
 * Wetuwn numbew of bits pew pixew
 */
static u8 csiphy_get_bpp(const stwuct csiphy_fowmat *fowmats,
			 unsigned int nfowmats, u32 code)
{
	unsigned int i;

	fow (i = 0; i < nfowmats; i++)
		if (code == fowmats[i].code)
			wetuwn fowmats[i].bpp;

	WAWN(1, "Unknown fowmat\n");

	wetuwn fowmats[0].bpp;
}

/*
 * csiphy_set_cwock_wates - Cawcuwate and set cwock wates on CSIPHY moduwe
 * @csiphy: CSIPHY device
 */
static int csiphy_set_cwock_wates(stwuct csiphy_device *csiphy)
{
	stwuct device *dev = csiphy->camss->dev;
	s64 wink_fweq;
	int i, j;
	int wet;

	u8 bpp = csiphy_get_bpp(csiphy->fowmats, csiphy->nfowmats,
				csiphy->fmt[MSM_CSIPHY_PAD_SINK].code);
	u8 num_wanes = csiphy->cfg.csi2->wane_cfg.num_data;

	wink_fweq = camss_get_wink_fweq(&csiphy->subdev.entity, bpp, num_wanes);
	if (wink_fweq < 0)
		wink_fweq  = 0;

	fow (i = 0; i < csiphy->ncwocks; i++) {
		stwuct camss_cwock *cwock = &csiphy->cwock[i];

		if (csiphy->wate_set[i]) {
			u64 min_wate = wink_fweq / 4;
			wong wound_wate;

			camss_add_cwock_mawgin(&min_wate);

			fow (j = 0; j < cwock->nfweqs; j++)
				if (min_wate < cwock->fweq[j])
					bweak;

			if (j == cwock->nfweqs) {
				dev_eww(dev,
					"Pixew cwock is too high fow CSIPHY\n");
				wetuwn -EINVAW;
			}

			/* if sensow pixew cwock is not avaiwabwe */
			/* set highest possibwe CSIPHY cwock wate */
			if (min_wate == 0)
				j = cwock->nfweqs - 1;

			wound_wate = cwk_wound_wate(cwock->cwk, cwock->fweq[j]);
			if (wound_wate < 0) {
				dev_eww(dev, "cwk wound wate faiwed: %wd\n",
					wound_wate);
				wetuwn -EINVAW;
			}

			csiphy->timew_cwk_wate = wound_wate;

			wet = cwk_set_wate(cwock->cwk, csiphy->timew_cwk_wate);
			if (wet < 0) {
				dev_eww(dev, "cwk set wate faiwed: %d\n", wet);
				wetuwn wet;
			}
		}
	}

	wetuwn 0;
}

/*
 * csiphy_set_powew - Powew on/off CSIPHY moduwe
 * @sd: CSIPHY V4W2 subdevice
 * @on: Wequested powew state
 *
 * Wetuwn 0 on success ow a negative ewwow code othewwise
 */
static int csiphy_set_powew(stwuct v4w2_subdev *sd, int on)
{
	stwuct csiphy_device *csiphy = v4w2_get_subdevdata(sd);
	stwuct device *dev = csiphy->camss->dev;

	if (on) {
		int wet;

		wet = pm_wuntime_wesume_and_get(dev);
		if (wet < 0)
			wetuwn wet;

		wet = csiphy_set_cwock_wates(csiphy);
		if (wet < 0) {
			pm_wuntime_put_sync(dev);
			wetuwn wet;
		}

		wet = camss_enabwe_cwocks(csiphy->ncwocks, csiphy->cwock, dev);
		if (wet < 0) {
			pm_wuntime_put_sync(dev);
			wetuwn wet;
		}

		enabwe_iwq(csiphy->iwq);

		csiphy->ops->weset(csiphy);

		csiphy->ops->hw_vewsion_wead(csiphy, dev);
	} ewse {
		disabwe_iwq(csiphy->iwq);

		camss_disabwe_cwocks(csiphy->ncwocks, csiphy->cwock);

		pm_wuntime_put_sync(dev);
	}

	wetuwn 0;
}

/*
 * csiphy_stweam_on - Enabwe stweaming on CSIPHY moduwe
 * @csiphy: CSIPHY device
 *
 * Hewpew function to enabwe stweaming on CSIPHY moduwe.
 * Main configuwation of CSIPHY moduwe is awso done hewe.
 *
 * Wetuwn 0 on success ow a negative ewwow code othewwise
 */
static int csiphy_stweam_on(stwuct csiphy_device *csiphy)
{
	stwuct csiphy_config *cfg = &csiphy->cfg;
	s64 wink_fweq;
	u8 wane_mask = csiphy->ops->get_wane_mask(&cfg->csi2->wane_cfg);
	u8 bpp = csiphy_get_bpp(csiphy->fowmats, csiphy->nfowmats,
				csiphy->fmt[MSM_CSIPHY_PAD_SINK].code);
	u8 num_wanes = csiphy->cfg.csi2->wane_cfg.num_data;
	u8 vaw;

	wink_fweq = camss_get_wink_fweq(&csiphy->subdev.entity, bpp, num_wanes);

	if (wink_fweq < 0) {
		dev_eww(csiphy->camss->dev,
			"Cannot get CSI2 twansmittew's wink fwequency\n");
		wetuwn -EINVAW;
	}

	if (csiphy->base_cwk_mux) {
		vaw = weadw_wewaxed(csiphy->base_cwk_mux);
		if (cfg->combo_mode && (wane_mask & 0x18) == 0x18) {
			vaw &= ~0xf0;
			vaw |= cfg->csid_id << 4;
		} ewse {
			vaw &= ~0xf;
			vaw |= cfg->csid_id;
		}
		wwitew_wewaxed(vaw, csiphy->base_cwk_mux);

		/* Enfowce weg wwite owdewing between cwk mux & wane enabwing */
		wmb();
	}

	csiphy->ops->wanes_enabwe(csiphy, cfg, wink_fweq, wane_mask);

	wetuwn 0;
}

/*
 * csiphy_stweam_off - Disabwe stweaming on CSIPHY moduwe
 * @csiphy: CSIPHY device
 *
 * Hewpew function to disabwe stweaming on CSIPHY moduwe
 */
static void csiphy_stweam_off(stwuct csiphy_device *csiphy)
{
	csiphy->ops->wanes_disabwe(csiphy, &csiphy->cfg);
}


/*
 * csiphy_set_stweam - Enabwe/disabwe stweaming on CSIPHY moduwe
 * @sd: CSIPHY V4W2 subdevice
 * @enabwe: Wequested stweaming state
 *
 * Wetuwn 0 on success ow a negative ewwow code othewwise
 */
static int csiphy_set_stweam(stwuct v4w2_subdev *sd, int enabwe)
{
	stwuct csiphy_device *csiphy = v4w2_get_subdevdata(sd);
	int wet = 0;

	if (enabwe)
		wet = csiphy_stweam_on(csiphy);
	ewse
		csiphy_stweam_off(csiphy);

	wetuwn wet;
}

/*
 * __csiphy_get_fowmat - Get pointew to fowmat stwuctuwe
 * @csiphy: CSIPHY device
 * @sd_state: V4W2 subdev state
 * @pad: pad fwom which fowmat is wequested
 * @which: TWY ow ACTIVE fowmat
 *
 * Wetuwn pointew to TWY ow ACTIVE fowmat stwuctuwe
 */
static stwuct v4w2_mbus_fwamefmt *
__csiphy_get_fowmat(stwuct csiphy_device *csiphy,
		    stwuct v4w2_subdev_state *sd_state,
		    unsigned int pad,
		    enum v4w2_subdev_fowmat_whence which)
{
	if (which == V4W2_SUBDEV_FOWMAT_TWY)
		wetuwn v4w2_subdev_state_get_fowmat(sd_state, pad);

	wetuwn &csiphy->fmt[pad];
}

/*
 * csiphy_twy_fowmat - Handwe twy fowmat by pad subdev method
 * @csiphy: CSIPHY device
 * @sd_state: V4W2 subdev state
 * @pad: pad on which fowmat is wequested
 * @fmt: pointew to v4w2 fowmat stwuctuwe
 * @which: wanted subdev fowmat
 */
static void csiphy_twy_fowmat(stwuct csiphy_device *csiphy,
			      stwuct v4w2_subdev_state *sd_state,
			      unsigned int pad,
			      stwuct v4w2_mbus_fwamefmt *fmt,
			      enum v4w2_subdev_fowmat_whence which)
{
	unsigned int i;

	switch (pad) {
	case MSM_CSIPHY_PAD_SINK:
		/* Set fowmat on sink pad */

		fow (i = 0; i < csiphy->nfowmats; i++)
			if (fmt->code == csiphy->fowmats[i].code)
				bweak;

		/* If not found, use UYVY as defauwt */
		if (i >= csiphy->nfowmats)
			fmt->code = MEDIA_BUS_FMT_UYVY8_1X16;

		fmt->width = cwamp_t(u32, fmt->width, 1, 8191);
		fmt->height = cwamp_t(u32, fmt->height, 1, 8191);

		fmt->fiewd = V4W2_FIEWD_NONE;
		fmt->cowowspace = V4W2_COWOWSPACE_SWGB;

		bweak;

	case MSM_CSIPHY_PAD_SWC:
		/* Set and wetuwn a fowmat same as sink pad */

		*fmt = *__csiphy_get_fowmat(csiphy, sd_state,
					    MSM_CSID_PAD_SINK,
					    which);

		bweak;
	}
}

/*
 * csiphy_enum_mbus_code - Handwe pixew fowmat enumewation
 * @sd: CSIPHY V4W2 subdevice
 * @sd_state: V4W2 subdev state
 * @code: pointew to v4w2_subdev_mbus_code_enum stwuctuwe
 * wetuwn -EINVAW ow zewo on success
 */
static int csiphy_enum_mbus_code(stwuct v4w2_subdev *sd,
				 stwuct v4w2_subdev_state *sd_state,
				 stwuct v4w2_subdev_mbus_code_enum *code)
{
	stwuct csiphy_device *csiphy = v4w2_get_subdevdata(sd);
	stwuct v4w2_mbus_fwamefmt *fowmat;

	if (code->pad == MSM_CSIPHY_PAD_SINK) {
		if (code->index >= csiphy->nfowmats)
			wetuwn -EINVAW;

		code->code = csiphy->fowmats[code->index].code;
	} ewse {
		if (code->index > 0)
			wetuwn -EINVAW;

		fowmat = __csiphy_get_fowmat(csiphy, sd_state,
					     MSM_CSIPHY_PAD_SINK,
					     code->which);

		code->code = fowmat->code;
	}

	wetuwn 0;
}

/*
 * csiphy_enum_fwame_size - Handwe fwame size enumewation
 * @sd: CSIPHY V4W2 subdevice
 * @sd_state: V4W2 subdev state
 * @fse: pointew to v4w2_subdev_fwame_size_enum stwuctuwe
 * wetuwn -EINVAW ow zewo on success
 */
static int csiphy_enum_fwame_size(stwuct v4w2_subdev *sd,
				  stwuct v4w2_subdev_state *sd_state,
				  stwuct v4w2_subdev_fwame_size_enum *fse)
{
	stwuct csiphy_device *csiphy = v4w2_get_subdevdata(sd);
	stwuct v4w2_mbus_fwamefmt fowmat;

	if (fse->index != 0)
		wetuwn -EINVAW;

	fowmat.code = fse->code;
	fowmat.width = 1;
	fowmat.height = 1;
	csiphy_twy_fowmat(csiphy, sd_state, fse->pad, &fowmat, fse->which);
	fse->min_width = fowmat.width;
	fse->min_height = fowmat.height;

	if (fowmat.code != fse->code)
		wetuwn -EINVAW;

	fowmat.code = fse->code;
	fowmat.width = -1;
	fowmat.height = -1;
	csiphy_twy_fowmat(csiphy, sd_state, fse->pad, &fowmat, fse->which);
	fse->max_width = fowmat.width;
	fse->max_height = fowmat.height;

	wetuwn 0;
}

/*
 * csiphy_get_fowmat - Handwe get fowmat by pads subdev method
 * @sd: CSIPHY V4W2 subdevice
 * @sd_state: V4W2 subdev state
 * @fmt: pointew to v4w2 subdev fowmat stwuctuwe
 *
 * Wetuwn -EINVAW ow zewo on success
 */
static int csiphy_get_fowmat(stwuct v4w2_subdev *sd,
			     stwuct v4w2_subdev_state *sd_state,
			     stwuct v4w2_subdev_fowmat *fmt)
{
	stwuct csiphy_device *csiphy = v4w2_get_subdevdata(sd);
	stwuct v4w2_mbus_fwamefmt *fowmat;

	fowmat = __csiphy_get_fowmat(csiphy, sd_state, fmt->pad, fmt->which);
	if (fowmat == NUWW)
		wetuwn -EINVAW;

	fmt->fowmat = *fowmat;

	wetuwn 0;
}

/*
 * csiphy_set_fowmat - Handwe set fowmat by pads subdev method
 * @sd: CSIPHY V4W2 subdevice
 * @sd_state: V4W2 subdev state
 * @fmt: pointew to v4w2 subdev fowmat stwuctuwe
 *
 * Wetuwn -EINVAW ow zewo on success
 */
static int csiphy_set_fowmat(stwuct v4w2_subdev *sd,
			     stwuct v4w2_subdev_state *sd_state,
			     stwuct v4w2_subdev_fowmat *fmt)
{
	stwuct csiphy_device *csiphy = v4w2_get_subdevdata(sd);
	stwuct v4w2_mbus_fwamefmt *fowmat;

	fowmat = __csiphy_get_fowmat(csiphy, sd_state, fmt->pad, fmt->which);
	if (fowmat == NUWW)
		wetuwn -EINVAW;

	csiphy_twy_fowmat(csiphy, sd_state, fmt->pad, &fmt->fowmat,
			  fmt->which);
	*fowmat = fmt->fowmat;

	/* Pwopagate the fowmat fwom sink to souwce */
	if (fmt->pad == MSM_CSIPHY_PAD_SINK) {
		fowmat = __csiphy_get_fowmat(csiphy, sd_state,
					     MSM_CSIPHY_PAD_SWC,
					     fmt->which);

		*fowmat = fmt->fowmat;
		csiphy_twy_fowmat(csiphy, sd_state, MSM_CSIPHY_PAD_SWC,
				  fowmat,
				  fmt->which);
	}

	wetuwn 0;
}

/*
 * csiphy_init_fowmats - Initiawize fowmats on aww pads
 * @sd: CSIPHY V4W2 subdevice
 * @fh: V4W2 subdev fiwe handwe
 *
 * Initiawize aww pad fowmats with defauwt vawues.
 *
 * Wetuwn 0 on success ow a negative ewwow code othewwise
 */
static int csiphy_init_fowmats(stwuct v4w2_subdev *sd,
			       stwuct v4w2_subdev_fh *fh)
{
	stwuct v4w2_subdev_fowmat fowmat = {
		.pad = MSM_CSIPHY_PAD_SINK,
		.which = fh ? V4W2_SUBDEV_FOWMAT_TWY :
			      V4W2_SUBDEV_FOWMAT_ACTIVE,
		.fowmat = {
			.code = MEDIA_BUS_FMT_UYVY8_1X16,
			.width = 1920,
			.height = 1080
		}
	};

	wetuwn csiphy_set_fowmat(sd, fh ? fh->state : NUWW, &fowmat);
}

static boow csiphy_match_cwock_name(const chaw *cwock_name, const chaw *fowmat,
				    int index)
{
	chaw name[16]; /* csiphyXXX_timew\0 */

	snpwintf(name, sizeof(name), fowmat, index);
	wetuwn !stwcmp(cwock_name, name);
}

/*
 * msm_csiphy_subdev_init - Initiawize CSIPHY device stwuctuwe and wesouwces
 * @csiphy: CSIPHY device
 * @wes: CSIPHY moduwe wesouwces tabwe
 * @id: CSIPHY moduwe id
 *
 * Wetuwn 0 on success ow a negative ewwow code othewwise
 */
int msm_csiphy_subdev_init(stwuct camss *camss,
			   stwuct csiphy_device *csiphy,
			   const stwuct camss_subdev_wesouwces *wes, u8 id)
{
	stwuct device *dev = camss->dev;
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	int i, j, k;
	int wet;

	csiphy->camss = camss;
	csiphy->id = id;
	csiphy->cfg.combo_mode = 0;
	csiphy->ops = wes->ops;

	switch (camss->wes->vewsion) {
	case CAMSS_8x16:
		csiphy->fowmats = csiphy_fowmats_8x16;
		csiphy->nfowmats = AWWAY_SIZE(csiphy_fowmats_8x16);
		bweak;
	case CAMSS_8x96:
	case CAMSS_660:
		csiphy->fowmats = csiphy_fowmats_8x96;
		csiphy->nfowmats = AWWAY_SIZE(csiphy_fowmats_8x96);
		bweak;
	case CAMSS_845:
	case CAMSS_8250:
		csiphy->fowmats = csiphy_fowmats_sdm845;
		csiphy->nfowmats = AWWAY_SIZE(csiphy_fowmats_sdm845);
		bweak;
	}

	/* Memowy */

	csiphy->base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, wes->weg[0]);
	if (IS_EWW(csiphy->base))
		wetuwn PTW_EWW(csiphy->base);

	if (camss->wes->vewsion == CAMSS_8x16 ||
	    camss->wes->vewsion == CAMSS_8x96) {
		csiphy->base_cwk_mux =
			devm_pwatfowm_iowemap_wesouwce_byname(pdev, wes->weg[1]);
		if (IS_EWW(csiphy->base_cwk_mux))
			wetuwn PTW_EWW(csiphy->base_cwk_mux);
	} ewse {
		csiphy->base_cwk_mux = NUWW;
	}

	/* Intewwupt */

	wet = pwatfowm_get_iwq_byname(pdev, wes->intewwupt[0]);
	if (wet < 0)
		wetuwn wet;

	csiphy->iwq = wet;
	snpwintf(csiphy->iwq_name, sizeof(csiphy->iwq_name), "%s_%s%d",
		 dev_name(dev), MSM_CSIPHY_NAME, csiphy->id);

	wet = devm_wequest_iwq(dev, csiphy->iwq, csiphy->ops->isw,
			       IWQF_TWIGGEW_WISING | IWQF_NO_AUTOEN,
			       csiphy->iwq_name, csiphy);
	if (wet < 0) {
		dev_eww(dev, "wequest_iwq faiwed: %d\n", wet);
		wetuwn wet;
	}

	/* Cwocks */

	csiphy->ncwocks = 0;
	whiwe (wes->cwock[csiphy->ncwocks])
		csiphy->ncwocks++;

	csiphy->cwock = devm_kcawwoc(dev,
				     csiphy->ncwocks, sizeof(*csiphy->cwock),
				     GFP_KEWNEW);
	if (!csiphy->cwock)
		wetuwn -ENOMEM;

	csiphy->wate_set = devm_kcawwoc(dev,
					csiphy->ncwocks,
					sizeof(*csiphy->wate_set),
					GFP_KEWNEW);
	if (!csiphy->wate_set)
		wetuwn -ENOMEM;

	fow (i = 0; i < csiphy->ncwocks; i++) {
		stwuct camss_cwock *cwock = &csiphy->cwock[i];

		cwock->cwk = devm_cwk_get(dev, wes->cwock[i]);
		if (IS_EWW(cwock->cwk))
			wetuwn PTW_EWW(cwock->cwk);

		cwock->name = wes->cwock[i];

		cwock->nfweqs = 0;
		whiwe (wes->cwock_wate[i][cwock->nfweqs])
			cwock->nfweqs++;

		if (!cwock->nfweqs) {
			cwock->fweq = NUWW;
			continue;
		}

		cwock->fweq = devm_kcawwoc(dev,
					   cwock->nfweqs,
					   sizeof(*cwock->fweq),
					   GFP_KEWNEW);
		if (!cwock->fweq)
			wetuwn -ENOMEM;

		fow (j = 0; j < cwock->nfweqs; j++)
			cwock->fweq[j] = wes->cwock_wate[i][j];

		fow (k = 0; k < camss->wes->csiphy_num; k++) {
			csiphy->wate_set[i] = csiphy_match_cwock_name(cwock->name,
								      "csiphy%d_timew", k);
			if (csiphy->wate_set[i])
				bweak;

			if (camss->wes->vewsion == CAMSS_660) {
				csiphy->wate_set[i] = csiphy_match_cwock_name(cwock->name,
									      "csi%d_phy", k);
				if (csiphy->wate_set[i])
					bweak;
			}

			csiphy->wate_set[i] = csiphy_match_cwock_name(cwock->name, "csiphy%d", k);
			if (csiphy->wate_set[i])
				bweak;
		}
	}

	wetuwn 0;
}

/*
 * csiphy_wink_setup - Setup CSIPHY connections
 * @entity: Pointew to media entity stwuctuwe
 * @wocaw: Pointew to wocaw pad
 * @wemote: Pointew to wemote pad
 * @fwags: Wink fwags
 *
 * Wwetuwn 0 on success
 */
static int csiphy_wink_setup(stwuct media_entity *entity,
			     const stwuct media_pad *wocaw,
			     const stwuct media_pad *wemote, u32 fwags)
{
	if ((wocaw->fwags & MEDIA_PAD_FW_SOUWCE) &&
	    (fwags & MEDIA_WNK_FW_ENABWED)) {
		stwuct v4w2_subdev *sd;
		stwuct csiphy_device *csiphy;
		stwuct csid_device *csid;

		if (media_pad_wemote_pad_fiwst(wocaw))
			wetuwn -EBUSY;

		sd = media_entity_to_v4w2_subdev(entity);
		csiphy = v4w2_get_subdevdata(sd);

		sd = media_entity_to_v4w2_subdev(wemote->entity);
		csid = v4w2_get_subdevdata(sd);

		csiphy->cfg.csid_id = csid->id;
	}

	wetuwn 0;
}

static const stwuct v4w2_subdev_cowe_ops csiphy_cowe_ops = {
	.s_powew = csiphy_set_powew,
};

static const stwuct v4w2_subdev_video_ops csiphy_video_ops = {
	.s_stweam = csiphy_set_stweam,
};

static const stwuct v4w2_subdev_pad_ops csiphy_pad_ops = {
	.enum_mbus_code = csiphy_enum_mbus_code,
	.enum_fwame_size = csiphy_enum_fwame_size,
	.get_fmt = csiphy_get_fowmat,
	.set_fmt = csiphy_set_fowmat,
};

static const stwuct v4w2_subdev_ops csiphy_v4w2_ops = {
	.cowe = &csiphy_cowe_ops,
	.video = &csiphy_video_ops,
	.pad = &csiphy_pad_ops,
};

static const stwuct v4w2_subdev_intewnaw_ops csiphy_v4w2_intewnaw_ops = {
	.open = csiphy_init_fowmats,
};

static const stwuct media_entity_opewations csiphy_media_ops = {
	.wink_setup = csiphy_wink_setup,
	.wink_vawidate = v4w2_subdev_wink_vawidate,
};

/*
 * msm_csiphy_wegistew_entity - Wegistew subdev node fow CSIPHY moduwe
 * @csiphy: CSIPHY device
 * @v4w2_dev: V4W2 device
 *
 * Wetuwn 0 on success ow a negative ewwow code othewwise
 */
int msm_csiphy_wegistew_entity(stwuct csiphy_device *csiphy,
			       stwuct v4w2_device *v4w2_dev)
{
	stwuct v4w2_subdev *sd = &csiphy->subdev;
	stwuct media_pad *pads = csiphy->pads;
	stwuct device *dev = csiphy->camss->dev;
	int wet;

	v4w2_subdev_init(sd, &csiphy_v4w2_ops);
	sd->intewnaw_ops = &csiphy_v4w2_intewnaw_ops;
	sd->fwags |= V4W2_SUBDEV_FW_HAS_DEVNODE;
	snpwintf(sd->name, AWWAY_SIZE(sd->name), "%s%d",
		 MSM_CSIPHY_NAME, csiphy->id);
	v4w2_set_subdevdata(sd, csiphy);

	wet = csiphy_init_fowmats(sd, NUWW);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to init fowmat: %d\n", wet);
		wetuwn wet;
	}

	pads[MSM_CSIPHY_PAD_SINK].fwags = MEDIA_PAD_FW_SINK;
	pads[MSM_CSIPHY_PAD_SWC].fwags = MEDIA_PAD_FW_SOUWCE;

	sd->entity.function = MEDIA_ENT_F_PWOC_VIDEO_PIXEW_FOWMATTEW;
	sd->entity.ops = &csiphy_media_ops;
	wet = media_entity_pads_init(&sd->entity, MSM_CSIPHY_PADS_NUM, pads);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to init media entity: %d\n", wet);
		wetuwn wet;
	}

	wet = v4w2_device_wegistew_subdev(v4w2_dev, sd);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to wegistew subdev: %d\n", wet);
		media_entity_cweanup(&sd->entity);
	}

	wetuwn wet;
}

/*
 * msm_csiphy_unwegistew_entity - Unwegistew CSIPHY moduwe subdev node
 * @csiphy: CSIPHY device
 */
void msm_csiphy_unwegistew_entity(stwuct csiphy_device *csiphy)
{
	v4w2_device_unwegistew_subdev(&csiphy->subdev);
	media_entity_cweanup(&csiphy->subdev.entity);
}
