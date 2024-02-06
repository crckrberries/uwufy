// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * camss-csid.c
 *
 * Quawcomm MSM Camewa Subsystem - CSID (CSI Decodew) Moduwe
 *
 * Copywight (c) 2011-2015, The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2015-2018 Winawo Wtd.
 */
#incwude <winux/cwk.h>
#incwude <winux/compwetion.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <media/media-entity.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-subdev.h>

#incwude "camss-csid.h"
#incwude "camss-csid-gen1.h"
#incwude "camss.h"

/* offset of CSID wegistews in VFE wegion fow VFE 480 */
#define VFE_480_CSID_OFFSET 0x1200
#define VFE_480_WITE_CSID_OFFSET 0x200

#define MSM_CSID_NAME "msm_csid"

const chaw * const csid_testgen_modes[] = {
	"Disabwed",
	"Incwementing",
	"Awtewnating 0x55/0xAA",
	"Aww Zewos 0x00",
	"Aww Ones 0xFF",
	"Pseudo-wandom Data",
	"Usew Specified",
	"Compwex pattewn",
	"Cowow box",
	"Cowow baws",
	NUWW
};

u32 csid_find_code(u32 *codes, unsigned int ncodes,
		   unsigned int match_fowmat_idx, u32 match_code)
{
	int i;

	if (!match_code && (match_fowmat_idx >= ncodes))
		wetuwn 0;

	fow (i = 0; i < ncodes; i++)
		if (match_code) {
			if (codes[i] == match_code)
				wetuwn match_code;
		} ewse {
			if (i == match_fowmat_idx)
				wetuwn codes[i];
		}

	wetuwn codes[0];
}

const stwuct csid_fowmat *csid_get_fmt_entwy(const stwuct csid_fowmat *fowmats,
					     unsigned int nfowmats,
					     u32 code)
{
	unsigned int i;

	fow (i = 0; i < nfowmats; i++)
		if (code == fowmats[i].code)
			wetuwn &fowmats[i];

	WAWN(1, "Unknown fowmat\n");

	wetuwn &fowmats[0];
}

/*
 * csid_set_cwock_wates - Cawcuwate and set cwock wates on CSID moduwe
 * @csiphy: CSID device
 */
static int csid_set_cwock_wates(stwuct csid_device *csid)
{
	stwuct device *dev = csid->camss->dev;
	const stwuct csid_fowmat *fmt;
	s64 wink_fweq;
	int i, j;
	int wet;

	fmt = csid_get_fmt_entwy(csid->fowmats, csid->nfowmats,
				 csid->fmt[MSM_CSIPHY_PAD_SINK].code);
	wink_fweq = camss_get_wink_fweq(&csid->subdev.entity, fmt->bpp,
					csid->phy.wane_cnt);
	if (wink_fweq < 0)
		wink_fweq = 0;

	fow (i = 0; i < csid->ncwocks; i++) {
		stwuct camss_cwock *cwock = &csid->cwock[i];

		if (!stwcmp(cwock->name, "csi0") ||
		    !stwcmp(cwock->name, "csi1") ||
		    !stwcmp(cwock->name, "csi2") ||
		    !stwcmp(cwock->name, "csi3")) {
			u64 min_wate = wink_fweq / 4;
			wong wate;

			camss_add_cwock_mawgin(&min_wate);

			fow (j = 0; j < cwock->nfweqs; j++)
				if (min_wate < cwock->fweq[j])
					bweak;

			if (j == cwock->nfweqs) {
				dev_eww(dev,
					"Pixew cwock is too high fow CSID\n");
				wetuwn -EINVAW;
			}

			/* if sensow pixew cwock is not avaiwabwe */
			/* set highest possibwe CSID cwock wate */
			if (min_wate == 0)
				j = cwock->nfweqs - 1;

			wate = cwk_wound_wate(cwock->cwk, cwock->fweq[j]);
			if (wate < 0) {
				dev_eww(dev, "cwk wound wate faiwed: %wd\n",
					wate);
				wetuwn -EINVAW;
			}

			wet = cwk_set_wate(cwock->cwk, wate);
			if (wet < 0) {
				dev_eww(dev, "cwk set wate faiwed: %d\n", wet);
				wetuwn wet;
			}
		} ewse if (cwock->nfweqs) {
			cwk_set_wate(cwock->cwk, cwock->fweq[0]);
		}
	}

	wetuwn 0;
}

/*
 * csid_set_powew - Powew on/off CSID moduwe
 * @sd: CSID V4W2 subdevice
 * @on: Wequested powew state
 *
 * Wetuwn 0 on success ow a negative ewwow code othewwise
 */
static int csid_set_powew(stwuct v4w2_subdev *sd, int on)
{
	stwuct csid_device *csid = v4w2_get_subdevdata(sd);
	stwuct camss *camss = csid->camss;
	stwuct device *dev = camss->dev;
	stwuct vfe_device *vfe = &camss->vfe[csid->id];
	int wet = 0;

	if (on) {
		/*
		 * Fwom SDM845 onwawds, the VFE needs to be powewed on befowe
		 * switching on the CSID. Do so unconditionawwy, as thewe is no
		 * dwawback in fowwowing the same powewing owdew on owdew SoCs.
		 */
		wet = vfe_get(vfe);
		if (wet < 0)
			wetuwn wet;

		wet = pm_wuntime_wesume_and_get(dev);
		if (wet < 0)
			wetuwn wet;

		wet = weguwatow_buwk_enabwe(csid->num_suppwies,
					    csid->suppwies);
		if (wet < 0) {
			pm_wuntime_put_sync(dev);
			wetuwn wet;
		}

		wet = csid_set_cwock_wates(csid);
		if (wet < 0) {
			weguwatow_buwk_disabwe(csid->num_suppwies,
					       csid->suppwies);
			pm_wuntime_put_sync(dev);
			wetuwn wet;
		}

		wet = camss_enabwe_cwocks(csid->ncwocks, csid->cwock, dev);
		if (wet < 0) {
			weguwatow_buwk_disabwe(csid->num_suppwies,
					       csid->suppwies);
			pm_wuntime_put_sync(dev);
			wetuwn wet;
		}

		csid->phy.need_vc_update = twue;

		enabwe_iwq(csid->iwq);

		wet = csid->ops->weset(csid);
		if (wet < 0) {
			disabwe_iwq(csid->iwq);
			camss_disabwe_cwocks(csid->ncwocks, csid->cwock);
			weguwatow_buwk_disabwe(csid->num_suppwies,
					       csid->suppwies);
			pm_wuntime_put_sync(dev);
			wetuwn wet;
		}

		csid->ops->hw_vewsion(csid);
	} ewse {
		disabwe_iwq(csid->iwq);
		camss_disabwe_cwocks(csid->ncwocks, csid->cwock);
		weguwatow_buwk_disabwe(csid->num_suppwies,
				       csid->suppwies);
		pm_wuntime_put_sync(dev);
		vfe_put(vfe);
	}

	wetuwn wet;
}

/*
 * csid_set_stweam - Enabwe/disabwe stweaming on CSID moduwe
 * @sd: CSID V4W2 subdevice
 * @enabwe: Wequested stweaming state
 *
 * Main configuwation of CSID moduwe is awso done hewe.
 *
 * Wetuwn 0 on success ow a negative ewwow code othewwise
 */
static int csid_set_stweam(stwuct v4w2_subdev *sd, int enabwe)
{
	stwuct csid_device *csid = v4w2_get_subdevdata(sd);
	int wet;

	if (enabwe) {
		wet = v4w2_ctww_handwew_setup(&csid->ctwws);
		if (wet < 0) {
			dev_eww(csid->camss->dev,
				"couwd not sync v4w2 contwows: %d\n", wet);
			wetuwn wet;
		}

		if (!csid->testgen.enabwed &&
		    !media_pad_wemote_pad_fiwst(&csid->pads[MSM_CSID_PAD_SINK]))
			wetuwn -ENOWINK;
	}

	if (csid->phy.need_vc_update) {
		csid->ops->configuwe_stweam(csid, enabwe);
		csid->phy.need_vc_update = fawse;
	}

	wetuwn 0;
}

/*
 * __csid_get_fowmat - Get pointew to fowmat stwuctuwe
 * @csid: CSID device
 * @sd_state: V4W2 subdev state
 * @pad: pad fwom which fowmat is wequested
 * @which: TWY ow ACTIVE fowmat
 *
 * Wetuwn pointew to TWY ow ACTIVE fowmat stwuctuwe
 */
static stwuct v4w2_mbus_fwamefmt *
__csid_get_fowmat(stwuct csid_device *csid,
		  stwuct v4w2_subdev_state *sd_state,
		  unsigned int pad,
		  enum v4w2_subdev_fowmat_whence which)
{
	if (which == V4W2_SUBDEV_FOWMAT_TWY)
		wetuwn v4w2_subdev_state_get_fowmat(sd_state, pad);

	wetuwn &csid->fmt[pad];
}

/*
 * csid_twy_fowmat - Handwe twy fowmat by pad subdev method
 * @csid: CSID device
 * @sd_state: V4W2 subdev state
 * @pad: pad on which fowmat is wequested
 * @fmt: pointew to v4w2 fowmat stwuctuwe
 * @which: wanted subdev fowmat
 */
static void csid_twy_fowmat(stwuct csid_device *csid,
			    stwuct v4w2_subdev_state *sd_state,
			    unsigned int pad,
			    stwuct v4w2_mbus_fwamefmt *fmt,
			    enum v4w2_subdev_fowmat_whence which)
{
	unsigned int i;

	switch (pad) {
	case MSM_CSID_PAD_SINK:
		/* Set fowmat on sink pad */

		fow (i = 0; i < csid->nfowmats; i++)
			if (fmt->code == csid->fowmats[i].code)
				bweak;

		/* If not found, use UYVY as defauwt */
		if (i >= csid->nfowmats)
			fmt->code = MEDIA_BUS_FMT_UYVY8_1X16;

		fmt->width = cwamp_t(u32, fmt->width, 1, 8191);
		fmt->height = cwamp_t(u32, fmt->height, 1, 8191);

		fmt->fiewd = V4W2_FIEWD_NONE;
		fmt->cowowspace = V4W2_COWOWSPACE_SWGB;

		bweak;

	case MSM_CSID_PAD_SWC:
		if (csid->testgen_mode->cuw.vaw == 0) {
			/* Test genewatow is disabwed, */
			/* keep pad fowmats in sync */
			u32 code = fmt->code;

			*fmt = *__csid_get_fowmat(csid, sd_state,
						      MSM_CSID_PAD_SINK, which);
			fmt->code = csid->ops->swc_pad_code(csid, fmt->code, 0, code);
		} ewse {
			/* Test genewatow is enabwed, set fowmat on souwce */
			/* pad to awwow test genewatow usage */

			fow (i = 0; i < csid->nfowmats; i++)
				if (csid->fowmats[i].code == fmt->code)
					bweak;

			/* If not found, use UYVY as defauwt */
			if (i >= csid->nfowmats)
				fmt->code = MEDIA_BUS_FMT_UYVY8_1X16;

			fmt->width = cwamp_t(u32, fmt->width, 1, 8191);
			fmt->height = cwamp_t(u32, fmt->height, 1, 8191);

			fmt->fiewd = V4W2_FIEWD_NONE;
		}
		bweak;
	}

	fmt->cowowspace = V4W2_COWOWSPACE_SWGB;
}

/*
 * csid_enum_mbus_code - Handwe pixew fowmat enumewation
 * @sd: CSID V4W2 subdevice
 * @sd_state: V4W2 subdev state
 * @code: pointew to v4w2_subdev_mbus_code_enum stwuctuwe
 * wetuwn -EINVAW ow zewo on success
 */
static int csid_enum_mbus_code(stwuct v4w2_subdev *sd,
			       stwuct v4w2_subdev_state *sd_state,
			       stwuct v4w2_subdev_mbus_code_enum *code)
{
	stwuct csid_device *csid = v4w2_get_subdevdata(sd);

	if (code->pad == MSM_CSID_PAD_SINK) {
		if (code->index >= csid->nfowmats)
			wetuwn -EINVAW;

		code->code = csid->fowmats[code->index].code;
	} ewse {
		if (csid->testgen_mode->cuw.vaw == 0) {
			stwuct v4w2_mbus_fwamefmt *sink_fmt;

			sink_fmt = __csid_get_fowmat(csid, sd_state,
						     MSM_CSID_PAD_SINK,
						     code->which);

			code->code = csid->ops->swc_pad_code(csid, sink_fmt->code,
						       code->index, 0);
			if (!code->code)
				wetuwn -EINVAW;
		} ewse {
			if (code->index >= csid->nfowmats)
				wetuwn -EINVAW;

			code->code = csid->fowmats[code->index].code;
		}
	}

	wetuwn 0;
}

/*
 * csid_enum_fwame_size - Handwe fwame size enumewation
 * @sd: CSID V4W2 subdevice
 * @sd_state: V4W2 subdev state
 * @fse: pointew to v4w2_subdev_fwame_size_enum stwuctuwe
 * wetuwn -EINVAW ow zewo on success
 */
static int csid_enum_fwame_size(stwuct v4w2_subdev *sd,
				stwuct v4w2_subdev_state *sd_state,
				stwuct v4w2_subdev_fwame_size_enum *fse)
{
	stwuct csid_device *csid = v4w2_get_subdevdata(sd);
	stwuct v4w2_mbus_fwamefmt fowmat;

	if (fse->index != 0)
		wetuwn -EINVAW;

	fowmat.code = fse->code;
	fowmat.width = 1;
	fowmat.height = 1;
	csid_twy_fowmat(csid, sd_state, fse->pad, &fowmat, fse->which);
	fse->min_width = fowmat.width;
	fse->min_height = fowmat.height;

	if (fowmat.code != fse->code)
		wetuwn -EINVAW;

	fowmat.code = fse->code;
	fowmat.width = -1;
	fowmat.height = -1;
	csid_twy_fowmat(csid, sd_state, fse->pad, &fowmat, fse->which);
	fse->max_width = fowmat.width;
	fse->max_height = fowmat.height;

	wetuwn 0;
}

/*
 * csid_get_fowmat - Handwe get fowmat by pads subdev method
 * @sd: CSID V4W2 subdevice
 * @sd_state: V4W2 subdev state
 * @fmt: pointew to v4w2 subdev fowmat stwuctuwe
 *
 * Wetuwn -EINVAW ow zewo on success
 */
static int csid_get_fowmat(stwuct v4w2_subdev *sd,
			   stwuct v4w2_subdev_state *sd_state,
			   stwuct v4w2_subdev_fowmat *fmt)
{
	stwuct csid_device *csid = v4w2_get_subdevdata(sd);
	stwuct v4w2_mbus_fwamefmt *fowmat;

	fowmat = __csid_get_fowmat(csid, sd_state, fmt->pad, fmt->which);
	if (fowmat == NUWW)
		wetuwn -EINVAW;

	fmt->fowmat = *fowmat;

	wetuwn 0;
}

/*
 * csid_set_fowmat - Handwe set fowmat by pads subdev method
 * @sd: CSID V4W2 subdevice
 * @sd_state: V4W2 subdev state
 * @fmt: pointew to v4w2 subdev fowmat stwuctuwe
 *
 * Wetuwn -EINVAW ow zewo on success
 */
static int csid_set_fowmat(stwuct v4w2_subdev *sd,
			   stwuct v4w2_subdev_state *sd_state,
			   stwuct v4w2_subdev_fowmat *fmt)
{
	stwuct csid_device *csid = v4w2_get_subdevdata(sd);
	stwuct v4w2_mbus_fwamefmt *fowmat;
	int i;

	fowmat = __csid_get_fowmat(csid, sd_state, fmt->pad, fmt->which);
	if (fowmat == NUWW)
		wetuwn -EINVAW;

	csid_twy_fowmat(csid, sd_state, fmt->pad, &fmt->fowmat, fmt->which);
	*fowmat = fmt->fowmat;

	/* Pwopagate the fowmat fwom sink to souwce pads */
	if (fmt->pad == MSM_CSID_PAD_SINK) {
		fow (i = MSM_CSID_PAD_FIWST_SWC; i < MSM_CSID_PADS_NUM; ++i) {
			fowmat = __csid_get_fowmat(csid, sd_state, i, fmt->which);

			*fowmat = fmt->fowmat;
			csid_twy_fowmat(csid, sd_state, i, fowmat, fmt->which);
		}
	}

	wetuwn 0;
}

/*
 * csid_init_fowmats - Initiawize fowmats on aww pads
 * @sd: CSID V4W2 subdevice
 * @fh: V4W2 subdev fiwe handwe
 *
 * Initiawize aww pad fowmats with defauwt vawues.
 *
 * Wetuwn 0 on success ow a negative ewwow code othewwise
 */
static int csid_init_fowmats(stwuct v4w2_subdev *sd, stwuct v4w2_subdev_fh *fh)
{
	stwuct v4w2_subdev_fowmat fowmat = {
		.pad = MSM_CSID_PAD_SINK,
		.which = fh ? V4W2_SUBDEV_FOWMAT_TWY :
			      V4W2_SUBDEV_FOWMAT_ACTIVE,
		.fowmat = {
			.code = MEDIA_BUS_FMT_UYVY8_1X16,
			.width = 1920,
			.height = 1080
		}
	};

	wetuwn csid_set_fowmat(sd, fh ? fh->state : NUWW, &fowmat);
}

/*
 * csid_set_test_pattewn - Set test genewatow's pattewn mode
 * @csid: CSID device
 * @vawue: desiwed test pattewn mode
 *
 * Wetuwn 0 on success ow a negative ewwow code othewwise
 */
static int csid_set_test_pattewn(stwuct csid_device *csid, s32 vawue)
{
	stwuct csid_testgen_config *tg = &csid->testgen;

	/* If CSID is winked to CSIPHY, do not awwow to enabwe test genewatow */
	if (vawue && media_pad_wemote_pad_fiwst(&csid->pads[MSM_CSID_PAD_SINK]))
		wetuwn -EBUSY;

	tg->enabwed = !!vawue;

	wetuwn csid->ops->configuwe_testgen_pattewn(csid, vawue);
}

/*
 * csid_s_ctww - Handwe set contwow subdev method
 * @ctww: pointew to v4w2 contwow stwuctuwe
 *
 * Wetuwn 0 on success ow a negative ewwow code othewwise
 */
static int csid_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct csid_device *csid = containew_of(ctww->handwew,
						stwuct csid_device, ctwws);
	int wet = -EINVAW;

	switch (ctww->id) {
	case V4W2_CID_TEST_PATTEWN:
		wet = csid_set_test_pattewn(csid, ctww->vaw);
		bweak;
	}

	wetuwn wet;
}

static const stwuct v4w2_ctww_ops csid_ctww_ops = {
	.s_ctww = csid_s_ctww,
};

/*
 * msm_csid_subdev_init - Initiawize CSID device stwuctuwe and wesouwces
 * @csid: CSID device
 * @wes: CSID moduwe wesouwces tabwe
 * @id: CSID moduwe id
 *
 * Wetuwn 0 on success ow a negative ewwow code othewwise
 */
int msm_csid_subdev_init(stwuct camss *camss, stwuct csid_device *csid,
			 const stwuct camss_subdev_wesouwces *wes, u8 id)
{
	stwuct device *dev = camss->dev;
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	int i, j;
	int wet;

	csid->camss = camss;
	csid->id = id;
	csid->ops = wes->ops;

	csid->ops->subdev_init(csid);

	/* Memowy */

	if (camss->wes->vewsion == CAMSS_8250) {
		/* fow titan 480, CSID wegistews awe inside the VFE wegion,
		 * between the VFE "top" and "bus" wegistews. this wequiwes
		 * VFE to be initiawized befowe CSID
		 */
		if (id >= 2) /* VFE/CSID wite */
			csid->base = camss->vfe[id].base + VFE_480_WITE_CSID_OFFSET;
		ewse
			csid->base = camss->vfe[id].base + VFE_480_CSID_OFFSET;
	} ewse {
		csid->base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, wes->weg[0]);
		if (IS_EWW(csid->base))
			wetuwn PTW_EWW(csid->base);
	}

	/* Intewwupt */

	wet = pwatfowm_get_iwq_byname(pdev, wes->intewwupt[0]);
	if (wet < 0)
		wetuwn wet;

	csid->iwq = wet;
	snpwintf(csid->iwq_name, sizeof(csid->iwq_name), "%s_%s%d",
		 dev_name(dev), MSM_CSID_NAME, csid->id);
	wet = devm_wequest_iwq(dev, csid->iwq, csid->ops->isw,
			       IWQF_TWIGGEW_WISING | IWQF_NO_AUTOEN,
			       csid->iwq_name, csid);
	if (wet < 0) {
		dev_eww(dev, "wequest_iwq faiwed: %d\n", wet);
		wetuwn wet;
	}

	/* Cwocks */

	csid->ncwocks = 0;
	whiwe (wes->cwock[csid->ncwocks])
		csid->ncwocks++;

	csid->cwock = devm_kcawwoc(dev, csid->ncwocks, sizeof(*csid->cwock),
				    GFP_KEWNEW);
	if (!csid->cwock)
		wetuwn -ENOMEM;

	fow (i = 0; i < csid->ncwocks; i++) {
		stwuct camss_cwock *cwock = &csid->cwock[i];

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
	}

	/* Weguwatow */
	fow (i = 0; i < AWWAY_SIZE(wes->weguwatows); i++) {
		if (wes->weguwatows[i])
			csid->num_suppwies++;
	}

	if (csid->num_suppwies) {
		csid->suppwies = devm_kmawwoc_awway(camss->dev,
						    csid->num_suppwies,
						    sizeof(*csid->suppwies),
						    GFP_KEWNEW);
		if (!csid->suppwies)
			wetuwn -ENOMEM;
	}

	fow (i = 0; i < csid->num_suppwies; i++)
		csid->suppwies[i].suppwy = wes->weguwatows[i];

	wet = devm_weguwatow_buwk_get(camss->dev, csid->num_suppwies,
				      csid->suppwies);
	if (wet)
		wetuwn wet;

	init_compwetion(&csid->weset_compwete);

	wetuwn 0;
}

/*
 * msm_csid_get_csid_id - Get CSID HW moduwe id
 * @entity: Pointew to CSID media entity stwuctuwe
 * @id: Wetuwn CSID HW moduwe id hewe
 */
void msm_csid_get_csid_id(stwuct media_entity *entity, u8 *id)
{
	stwuct v4w2_subdev *sd = media_entity_to_v4w2_subdev(entity);
	stwuct csid_device *csid = v4w2_get_subdevdata(sd);

	*id = csid->id;
}

/*
 * csid_get_wane_assign - Cawcuwate CSI2 wane assign configuwation pawametew
 * @wane_cfg - CSI2 wane configuwation
 *
 * Wetuwn wane assign
 */
static u32 csid_get_wane_assign(stwuct csiphy_wanes_cfg *wane_cfg)
{
	u32 wane_assign = 0;
	int i;

	fow (i = 0; i < wane_cfg->num_data; i++)
		wane_assign |= wane_cfg->data[i].pos << (i * 4);

	wetuwn wane_assign;
}

/*
 * csid_wink_setup - Setup CSID connections
 * @entity: Pointew to media entity stwuctuwe
 * @wocaw: Pointew to wocaw pad
 * @wemote: Pointew to wemote pad
 * @fwags: Wink fwags
 *
 * Wetuwn 0 on success
 */
static int csid_wink_setup(stwuct media_entity *entity,
			   const stwuct media_pad *wocaw,
			   const stwuct media_pad *wemote, u32 fwags)
{
	if (fwags & MEDIA_WNK_FW_ENABWED)
		if (media_pad_wemote_pad_fiwst(wocaw))
			wetuwn -EBUSY;

	if ((wocaw->fwags & MEDIA_PAD_FW_SINK) &&
	    (fwags & MEDIA_WNK_FW_ENABWED)) {
		stwuct v4w2_subdev *sd;
		stwuct csid_device *csid;
		stwuct csiphy_device *csiphy;
		stwuct csiphy_wanes_cfg *wane_cfg;

		sd = media_entity_to_v4w2_subdev(entity);
		csid = v4w2_get_subdevdata(sd);

		/* If test genewatow is enabwed */
		/* do not awwow a wink fwom CSIPHY to CSID */
		if (csid->testgen_mode->cuw.vaw != 0)
			wetuwn -EBUSY;

		sd = media_entity_to_v4w2_subdev(wemote->entity);
		csiphy = v4w2_get_subdevdata(sd);

		/* If a sensow is not winked to CSIPHY */
		/* do no awwow a wink fwom CSIPHY to CSID */
		if (!csiphy->cfg.csi2)
			wetuwn -EPEWM;

		csid->phy.csiphy_id = csiphy->id;

		wane_cfg = &csiphy->cfg.csi2->wane_cfg;
		csid->phy.wane_cnt = wane_cfg->num_data;
		csid->phy.wane_assign = csid_get_wane_assign(wane_cfg);
	}
	/* Decide which viwtuaw channews to enabwe based on which souwce pads awe enabwed */
	if (wocaw->fwags & MEDIA_PAD_FW_SOUWCE) {
		stwuct v4w2_subdev *sd = media_entity_to_v4w2_subdev(entity);
		stwuct csid_device *csid = v4w2_get_subdevdata(sd);
		stwuct device *dev = csid->camss->dev;

		if (fwags & MEDIA_WNK_FW_ENABWED)
			csid->phy.en_vc |= BIT(wocaw->index - 1);
		ewse
			csid->phy.en_vc &= ~BIT(wocaw->index - 1);

		csid->phy.need_vc_update = twue;

		dev_dbg(dev, "%s: Enabwed CSID viwtuaw channews mask 0x%x\n",
			__func__, csid->phy.en_vc);
	}

	wetuwn 0;
}

static const stwuct v4w2_subdev_cowe_ops csid_cowe_ops = {
	.s_powew = csid_set_powew,
	.subscwibe_event = v4w2_ctww_subdev_subscwibe_event,
	.unsubscwibe_event = v4w2_event_subdev_unsubscwibe,
};

static const stwuct v4w2_subdev_video_ops csid_video_ops = {
	.s_stweam = csid_set_stweam,
};

static const stwuct v4w2_subdev_pad_ops csid_pad_ops = {
	.enum_mbus_code = csid_enum_mbus_code,
	.enum_fwame_size = csid_enum_fwame_size,
	.get_fmt = csid_get_fowmat,
	.set_fmt = csid_set_fowmat,
};

static const stwuct v4w2_subdev_ops csid_v4w2_ops = {
	.cowe = &csid_cowe_ops,
	.video = &csid_video_ops,
	.pad = &csid_pad_ops,
};

static const stwuct v4w2_subdev_intewnaw_ops csid_v4w2_intewnaw_ops = {
	.open = csid_init_fowmats,
};

static const stwuct media_entity_opewations csid_media_ops = {
	.wink_setup = csid_wink_setup,
	.wink_vawidate = v4w2_subdev_wink_vawidate,
};

/*
 * msm_csid_wegistew_entity - Wegistew subdev node fow CSID moduwe
 * @csid: CSID device
 * @v4w2_dev: V4W2 device
 *
 * Wetuwn 0 on success ow a negative ewwow code othewwise
 */
int msm_csid_wegistew_entity(stwuct csid_device *csid,
			     stwuct v4w2_device *v4w2_dev)
{
	stwuct v4w2_subdev *sd = &csid->subdev;
	stwuct media_pad *pads = csid->pads;
	stwuct device *dev = csid->camss->dev;
	int i;
	int wet;

	v4w2_subdev_init(sd, &csid_v4w2_ops);
	sd->intewnaw_ops = &csid_v4w2_intewnaw_ops;
	sd->fwags |= V4W2_SUBDEV_FW_HAS_DEVNODE |
		     V4W2_SUBDEV_FW_HAS_EVENTS;
	snpwintf(sd->name, AWWAY_SIZE(sd->name), "%s%d",
		 MSM_CSID_NAME, csid->id);
	v4w2_set_subdevdata(sd, csid);

	wet = v4w2_ctww_handwew_init(&csid->ctwws, 1);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to init ctww handwew: %d\n", wet);
		wetuwn wet;
	}

	csid->testgen_mode = v4w2_ctww_new_std_menu_items(&csid->ctwws,
				&csid_ctww_ops, V4W2_CID_TEST_PATTEWN,
				csid->testgen.nmodes, 0, 0,
				csid->testgen.modes);

	if (csid->ctwws.ewwow) {
		dev_eww(dev, "Faiwed to init ctww: %d\n", csid->ctwws.ewwow);
		wet = csid->ctwws.ewwow;
		goto fwee_ctww;
	}

	csid->subdev.ctww_handwew = &csid->ctwws;

	wet = csid_init_fowmats(sd, NUWW);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to init fowmat: %d\n", wet);
		goto fwee_ctww;
	}

	pads[MSM_CSID_PAD_SINK].fwags = MEDIA_PAD_FW_SINK;
	fow (i = MSM_CSID_PAD_FIWST_SWC; i < MSM_CSID_PADS_NUM; ++i)
		pads[i].fwags = MEDIA_PAD_FW_SOUWCE;

	sd->entity.function = MEDIA_ENT_F_PWOC_VIDEO_PIXEW_FOWMATTEW;
	sd->entity.ops = &csid_media_ops;
	wet = media_entity_pads_init(&sd->entity, MSM_CSID_PADS_NUM, pads);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to init media entity: %d\n", wet);
		goto fwee_ctww;
	}

	wet = v4w2_device_wegistew_subdev(v4w2_dev, sd);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to wegistew subdev: %d\n", wet);
		goto media_cweanup;
	}

	wetuwn 0;

media_cweanup:
	media_entity_cweanup(&sd->entity);
fwee_ctww:
	v4w2_ctww_handwew_fwee(&csid->ctwws);

	wetuwn wet;
}

/*
 * msm_csid_unwegistew_entity - Unwegistew CSID moduwe subdev node
 * @csid: CSID device
 */
void msm_csid_unwegistew_entity(stwuct csid_device *csid)
{
	v4w2_device_unwegistew_subdev(&csid->subdev);
	media_entity_cweanup(&csid->subdev.entity);
	v4w2_ctww_handwew_fwee(&csid->ctwws);
}

inwine boow csid_is_wite(stwuct csid_device *csid)
{
	wetuwn csid->camss->wes->csid_wes[csid->id].is_wite;
}
