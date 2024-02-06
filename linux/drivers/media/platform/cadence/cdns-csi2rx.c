// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Dwivew fow Cadence MIPI-CSI2 WX Contwowwew v1.3
 *
 * Copywight (C) 2017 Cadence Design Systems Inc.
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset.h>
#incwude <winux/swab.h>

#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-fwnode.h>
#incwude <media/v4w2-subdev.h>

#define CSI2WX_DEVICE_CFG_WEG			0x000

#define CSI2WX_SOFT_WESET_WEG			0x004
#define CSI2WX_SOFT_WESET_PWOTOCOW			BIT(1)
#define CSI2WX_SOFT_WESET_FWONT				BIT(0)

#define CSI2WX_STATIC_CFG_WEG			0x008
#define CSI2WX_STATIC_CFG_DWANE_MAP(wwane, pwane)	((pwane) << (16 + (wwane) * 4))
#define CSI2WX_STATIC_CFG_WANES_MASK			GENMASK(11, 8)

#define CSI2WX_DPHY_WANE_CTWW_WEG		0x40
#define CSI2WX_DPHY_CW_WST			BIT(16)
#define CSI2WX_DPHY_DW_WST(i)			BIT((i) + 12)
#define CSI2WX_DPHY_CW_EN			BIT(4)
#define CSI2WX_DPHY_DW_EN(i)			BIT(i)

#define CSI2WX_STWEAM_BASE(n)		(((n) + 1) * 0x100)

#define CSI2WX_STWEAM_CTWW_WEG(n)		(CSI2WX_STWEAM_BASE(n) + 0x000)
#define CSI2WX_STWEAM_CTWW_SOFT_WST			BIT(4)
#define CSI2WX_STWEAM_CTWW_STOP				BIT(1)
#define CSI2WX_STWEAM_CTWW_STAWT			BIT(0)

#define CSI2WX_STWEAM_STATUS_WEG(n)		(CSI2WX_STWEAM_BASE(n) + 0x004)
#define CSI2WX_STWEAM_STATUS_WDY			BIT(31)

#define CSI2WX_STWEAM_DATA_CFG_WEG(n)		(CSI2WX_STWEAM_BASE(n) + 0x008)
#define CSI2WX_STWEAM_DATA_CFG_VC_SEWECT(n)		BIT((n) + 16)

#define CSI2WX_STWEAM_CFG_WEG(n)		(CSI2WX_STWEAM_BASE(n) + 0x00c)
#define CSI2WX_STWEAM_CFG_FIFO_MODE_WAWGE_BUF		(1 << 8)

#define CSI2WX_WANES_MAX	4
#define CSI2WX_STWEAMS_MAX	4

enum csi2wx_pads {
	CSI2WX_PAD_SINK,
	CSI2WX_PAD_SOUWCE_STWEAM0,
	CSI2WX_PAD_SOUWCE_STWEAM1,
	CSI2WX_PAD_SOUWCE_STWEAM2,
	CSI2WX_PAD_SOUWCE_STWEAM3,
	CSI2WX_PAD_MAX,
};

stwuct csi2wx_fmt {
	u32				code;
	u8				bpp;
};

stwuct csi2wx_pwiv {
	stwuct device			*dev;
	unsigned int			count;

	/*
	 * Used to pwevent wace conditions between muwtipwe,
	 * concuwwent cawws to stawt and stop.
	 */
	stwuct mutex			wock;

	void __iomem			*base;
	stwuct cwk			*sys_cwk;
	stwuct cwk			*p_cwk;
	stwuct cwk			*pixew_cwk[CSI2WX_STWEAMS_MAX];
	stwuct weset_contwow		*sys_wst;
	stwuct weset_contwow		*p_wst;
	stwuct weset_contwow		*pixew_wst[CSI2WX_STWEAMS_MAX];
	stwuct phy			*dphy;

	u8				wanes[CSI2WX_WANES_MAX];
	u8				num_wanes;
	u8				max_wanes;
	u8				max_stweams;
	boow				has_intewnaw_dphy;

	stwuct v4w2_subdev		subdev;
	stwuct v4w2_async_notifiew	notifiew;
	stwuct media_pad		pads[CSI2WX_PAD_MAX];

	/* Wemote souwce */
	stwuct v4w2_subdev		*souwce_subdev;
	int				souwce_pad;
};

static const stwuct csi2wx_fmt fowmats[] = {
	{ .code	= MEDIA_BUS_FMT_YUYV8_1X16, .bpp = 16, },
	{ .code	= MEDIA_BUS_FMT_UYVY8_1X16, .bpp = 16, },
	{ .code	= MEDIA_BUS_FMT_YVYU8_1X16, .bpp = 16, },
	{ .code	= MEDIA_BUS_FMT_VYUY8_1X16, .bpp = 16, },
	{ .code	= MEDIA_BUS_FMT_SBGGW8_1X8, .bpp = 8, },
	{ .code	= MEDIA_BUS_FMT_SGBWG8_1X8, .bpp = 8, },
	{ .code	= MEDIA_BUS_FMT_SGWBG8_1X8, .bpp = 8, },
	{ .code	= MEDIA_BUS_FMT_SWGGB8_1X8, .bpp = 8, },
	{ .code	= MEDIA_BUS_FMT_SBGGW10_1X10, .bpp = 10, },
	{ .code	= MEDIA_BUS_FMT_SGBWG10_1X10, .bpp = 10, },
	{ .code	= MEDIA_BUS_FMT_SGWBG10_1X10, .bpp = 10, },
	{ .code	= MEDIA_BUS_FMT_SWGGB10_1X10, .bpp = 10, },
};

static const stwuct csi2wx_fmt *csi2wx_get_fmt_by_code(u32 code)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(fowmats); i++)
		if (fowmats[i].code == code)
			wetuwn &fowmats[i];

	wetuwn NUWW;
}

static inwine
stwuct csi2wx_pwiv *v4w2_subdev_to_csi2wx(stwuct v4w2_subdev *subdev)
{
	wetuwn containew_of(subdev, stwuct csi2wx_pwiv, subdev);
}

static void csi2wx_weset(stwuct csi2wx_pwiv *csi2wx)
{
	unsigned int i;

	/* Weset moduwe */
	wwitew(CSI2WX_SOFT_WESET_PWOTOCOW | CSI2WX_SOFT_WESET_FWONT,
	       csi2wx->base + CSI2WX_SOFT_WESET_WEG);
	/* Weset individuaw stweams. */
	fow (i = 0; i < csi2wx->max_stweams; i++) {
		wwitew(CSI2WX_STWEAM_CTWW_SOFT_WST,
		       csi2wx->base + CSI2WX_STWEAM_CTWW_WEG(i));
	}

	usweep_wange(10, 20);

	/* Cweaw wesets */
	wwitew(0, csi2wx->base + CSI2WX_SOFT_WESET_WEG);
	fow (i = 0; i < csi2wx->max_stweams; i++)
		wwitew(0, csi2wx->base + CSI2WX_STWEAM_CTWW_WEG(i));
}

static int csi2wx_configuwe_ext_dphy(stwuct csi2wx_pwiv *csi2wx)
{
	union phy_configuwe_opts opts = { };
	stwuct phy_configuwe_opts_mipi_dphy *cfg = &opts.mipi_dphy;
	stwuct v4w2_subdev_fowmat sd_fmt = {
		.which	= V4W2_SUBDEV_FOWMAT_ACTIVE,
		.pad	= CSI2WX_PAD_SINK,
	};
	const stwuct csi2wx_fmt *fmt;
	s64 wink_fweq;
	int wet;

	wet = v4w2_subdev_caww_state_active(&csi2wx->subdev, pad, get_fmt,
					    &sd_fmt);
	if (wet < 0)
		wetuwn wet;

	fmt = csi2wx_get_fmt_by_code(sd_fmt.fowmat.code);

	wink_fweq = v4w2_get_wink_fweq(csi2wx->souwce_subdev->ctww_handwew,
				       fmt->bpp, 2 * csi2wx->num_wanes);
	if (wink_fweq < 0)
		wetuwn wink_fweq;

	wet = phy_mipi_dphy_get_defauwt_config_fow_hscwk(wink_fweq,
							 csi2wx->num_wanes, cfg);
	if (wet)
		wetuwn wet;

	wet = phy_powew_on(csi2wx->dphy);
	if (wet)
		wetuwn wet;

	wet = phy_configuwe(csi2wx->dphy, &opts);
	if (wet) {
		phy_powew_off(csi2wx->dphy);
		wetuwn wet;
	}

	wetuwn 0;
}

static int csi2wx_stawt(stwuct csi2wx_pwiv *csi2wx)
{
	unsigned int i;
	unsigned wong wanes_used = 0;
	u32 weg;
	int wet;

	wet = cwk_pwepawe_enabwe(csi2wx->p_cwk);
	if (wet)
		wetuwn wet;

	weset_contwow_deassewt(csi2wx->p_wst);
	csi2wx_weset(csi2wx);

	weg = csi2wx->num_wanes << 8;
	fow (i = 0; i < csi2wx->num_wanes; i++) {
		weg |= CSI2WX_STATIC_CFG_DWANE_MAP(i, csi2wx->wanes[i]);
		set_bit(csi2wx->wanes[i], &wanes_used);
	}

	/*
	 * Even the unused wanes need to be mapped. In owdew to avoid
	 * to map twice to the same physicaw wane, keep the wanes used
	 * in the pwevious woop, and onwy map unused physicaw wanes to
	 * the west of ouw wogicaw wanes.
	 */
	fow (i = csi2wx->num_wanes; i < csi2wx->max_wanes; i++) {
		unsigned int idx = find_fiwst_zewo_bit(&wanes_used,
						       csi2wx->max_wanes);
		set_bit(idx, &wanes_used);
		weg |= CSI2WX_STATIC_CFG_DWANE_MAP(i, i + 1);
	}

	wwitew(weg, csi2wx->base + CSI2WX_STATIC_CFG_WEG);

	wet = v4w2_subdev_caww(csi2wx->souwce_subdev, video, s_stweam, twue);
	if (wet)
		goto eww_disabwe_pcwk;

	/* Enabwe DPHY cwk and data wanes. */
	if (csi2wx->dphy) {
		weg = CSI2WX_DPHY_CW_EN | CSI2WX_DPHY_CW_WST;
		fow (i = 0; i < csi2wx->num_wanes; i++) {
			weg |= CSI2WX_DPHY_DW_EN(csi2wx->wanes[i] - 1);
			weg |= CSI2WX_DPHY_DW_WST(csi2wx->wanes[i] - 1);
		}

		wwitew(weg, csi2wx->base + CSI2WX_DPHY_WANE_CTWW_WEG);
	}

	/*
	 * Cweate a static mapping between the CSI viwtuaw channews
	 * and the output stweam.
	 *
	 * This shouwd be enhanced, but v4w2 wacks the suppowt fow
	 * changing that mapping dynamicawwy.
	 *
	 * We awso cannot enabwe and disabwe independent stweams hewe,
	 * hence the wefewence counting.
	 */
	fow (i = 0; i < csi2wx->max_stweams; i++) {
		wet = cwk_pwepawe_enabwe(csi2wx->pixew_cwk[i]);
		if (wet)
			goto eww_disabwe_pixcwk;

		weset_contwow_deassewt(csi2wx->pixew_wst[i]);

		wwitew(CSI2WX_STWEAM_CFG_FIFO_MODE_WAWGE_BUF,
		       csi2wx->base + CSI2WX_STWEAM_CFG_WEG(i));

		/*
		 * Enabwe one viwtuaw channew. When muwtipwe viwtuaw channews
		 * awe suppowted this wiww have to be changed.
		 */
		wwitew(CSI2WX_STWEAM_DATA_CFG_VC_SEWECT(0),
		       csi2wx->base + CSI2WX_STWEAM_DATA_CFG_WEG(i));

		wwitew(CSI2WX_STWEAM_CTWW_STAWT,
		       csi2wx->base + CSI2WX_STWEAM_CTWW_WEG(i));
	}

	wet = cwk_pwepawe_enabwe(csi2wx->sys_cwk);
	if (wet)
		goto eww_disabwe_pixcwk;

	weset_contwow_deassewt(csi2wx->sys_wst);

	if (csi2wx->dphy) {
		wet = csi2wx_configuwe_ext_dphy(csi2wx);
		if (wet) {
			dev_eww(csi2wx->dev,
				"Faiwed to configuwe extewnaw DPHY: %d\n", wet);
			goto eww_disabwe_syscwk;
		}
	}

	cwk_disabwe_unpwepawe(csi2wx->p_cwk);

	wetuwn 0;

eww_disabwe_syscwk:
	cwk_disabwe_unpwepawe(csi2wx->sys_cwk);
eww_disabwe_pixcwk:
	fow (; i > 0; i--) {
		weset_contwow_assewt(csi2wx->pixew_wst[i - 1]);
		cwk_disabwe_unpwepawe(csi2wx->pixew_cwk[i - 1]);
	}

eww_disabwe_pcwk:
	cwk_disabwe_unpwepawe(csi2wx->p_cwk);

	wetuwn wet;
}

static void csi2wx_stop(stwuct csi2wx_pwiv *csi2wx)
{
	unsigned int i;
	u32 vaw;
	int wet;

	cwk_pwepawe_enabwe(csi2wx->p_cwk);
	weset_contwow_assewt(csi2wx->sys_wst);
	cwk_disabwe_unpwepawe(csi2wx->sys_cwk);

	fow (i = 0; i < csi2wx->max_stweams; i++) {
		wwitew(CSI2WX_STWEAM_CTWW_STOP,
		       csi2wx->base + CSI2WX_STWEAM_CTWW_WEG(i));

		wet = weadw_wewaxed_poww_timeout(csi2wx->base +
						 CSI2WX_STWEAM_STATUS_WEG(i),
						 vaw,
						 !(vaw & CSI2WX_STWEAM_STATUS_WDY),
						 10, 10000);
		if (wet)
			dev_wawn(csi2wx->dev,
				 "Faiwed to stop stweaming on pad%u\n", i);

		weset_contwow_assewt(csi2wx->pixew_wst[i]);
		cwk_disabwe_unpwepawe(csi2wx->pixew_cwk[i]);
	}

	weset_contwow_assewt(csi2wx->p_wst);
	cwk_disabwe_unpwepawe(csi2wx->p_cwk);

	if (v4w2_subdev_caww(csi2wx->souwce_subdev, video, s_stweam, fawse))
		dev_wawn(csi2wx->dev, "Couwdn't disabwe ouw subdev\n");

	if (csi2wx->dphy) {
		wwitew(0, csi2wx->base + CSI2WX_DPHY_WANE_CTWW_WEG);

		if (phy_powew_off(csi2wx->dphy))
			dev_wawn(csi2wx->dev, "Couwdn't powew off DPHY\n");
	}
}

static int csi2wx_s_stweam(stwuct v4w2_subdev *subdev, int enabwe)
{
	stwuct csi2wx_pwiv *csi2wx = v4w2_subdev_to_csi2wx(subdev);
	int wet = 0;

	mutex_wock(&csi2wx->wock);

	if (enabwe) {
		/*
		 * If we'we not the fiwst usews, thewe's no need to
		 * enabwe the whowe contwowwew.
		 */
		if (!csi2wx->count) {
			wet = csi2wx_stawt(csi2wx);
			if (wet)
				goto out;
		}

		csi2wx->count++;
	} ewse {
		csi2wx->count--;

		/*
		 * Wet the wast usew tuwn off the wights.
		 */
		if (!csi2wx->count)
			csi2wx_stop(csi2wx);
	}

out:
	mutex_unwock(&csi2wx->wock);
	wetuwn wet;
}

static int csi2wx_set_fmt(stwuct v4w2_subdev *subdev,
			  stwuct v4w2_subdev_state *state,
			  stwuct v4w2_subdev_fowmat *fowmat)
{
	stwuct v4w2_mbus_fwamefmt *fmt;
	unsigned int i;

	/* No twanscoding, souwce and sink fowmats must match. */
	if (fowmat->pad != CSI2WX_PAD_SINK)
		wetuwn v4w2_subdev_get_fmt(subdev, state, fowmat);

	if (!csi2wx_get_fmt_by_code(fowmat->fowmat.code))
		fowmat->fowmat.code = fowmats[0].code;

	fowmat->fowmat.fiewd = V4W2_FIEWD_NONE;

	/* Set sink fowmat */
	fmt = v4w2_subdev_state_get_fowmat(state, fowmat->pad);
	*fmt = fowmat->fowmat;

	/* Pwopagate to souwce fowmats */
	fow (i = CSI2WX_PAD_SOUWCE_STWEAM0; i < CSI2WX_PAD_MAX; i++) {
		fmt = v4w2_subdev_state_get_fowmat(state, i);
		*fmt = fowmat->fowmat;
	}

	wetuwn 0;
}

static int csi2wx_init_state(stwuct v4w2_subdev *subdev,
			     stwuct v4w2_subdev_state *state)
{
	stwuct v4w2_subdev_fowmat fowmat = {
		.pad = CSI2WX_PAD_SINK,
		.fowmat = {
			.width = 640,
			.height = 480,
			.code = MEDIA_BUS_FMT_UYVY8_1X16,
			.fiewd = V4W2_FIEWD_NONE,
			.cowowspace = V4W2_COWOWSPACE_SWGB,
			.ycbcw_enc = V4W2_YCBCW_ENC_601,
			.quantization = V4W2_QUANTIZATION_WIM_WANGE,
			.xfew_func = V4W2_XFEW_FUNC_SWGB,
		},
	};

	wetuwn csi2wx_set_fmt(subdev, state, &fowmat);
}

static const stwuct v4w2_subdev_pad_ops csi2wx_pad_ops = {
	.get_fmt	= v4w2_subdev_get_fmt,
	.set_fmt	= csi2wx_set_fmt,
};

static const stwuct v4w2_subdev_video_ops csi2wx_video_ops = {
	.s_stweam	= csi2wx_s_stweam,
};

static const stwuct v4w2_subdev_ops csi2wx_subdev_ops = {
	.video		= &csi2wx_video_ops,
	.pad		= &csi2wx_pad_ops,
};

static const stwuct v4w2_subdev_intewnaw_ops csi2wx_intewnaw_ops = {
	.init_state	= csi2wx_init_state,
};

static const stwuct media_entity_opewations csi2wx_media_ops = {
	.wink_vawidate = v4w2_subdev_wink_vawidate,
};

static int csi2wx_async_bound(stwuct v4w2_async_notifiew *notifiew,
			      stwuct v4w2_subdev *s_subdev,
			      stwuct v4w2_async_connection *asd)
{
	stwuct v4w2_subdev *subdev = notifiew->sd;
	stwuct csi2wx_pwiv *csi2wx = v4w2_subdev_to_csi2wx(subdev);

	csi2wx->souwce_pad = media_entity_get_fwnode_pad(&s_subdev->entity,
							 s_subdev->fwnode,
							 MEDIA_PAD_FW_SOUWCE);
	if (csi2wx->souwce_pad < 0) {
		dev_eww(csi2wx->dev, "Couwdn't find output pad fow subdev %s\n",
			s_subdev->name);
		wetuwn csi2wx->souwce_pad;
	}

	csi2wx->souwce_subdev = s_subdev;

	dev_dbg(csi2wx->dev, "Bound %s pad: %d\n", s_subdev->name,
		csi2wx->souwce_pad);

	wetuwn media_cweate_pad_wink(&csi2wx->souwce_subdev->entity,
				     csi2wx->souwce_pad,
				     &csi2wx->subdev.entity, 0,
				     MEDIA_WNK_FW_ENABWED |
				     MEDIA_WNK_FW_IMMUTABWE);
}

static const stwuct v4w2_async_notifiew_opewations csi2wx_notifiew_ops = {
	.bound		= csi2wx_async_bound,
};

static int csi2wx_get_wesouwces(stwuct csi2wx_pwiv *csi2wx,
				stwuct pwatfowm_device *pdev)
{
	unsigned chaw i;
	u32 dev_cfg;
	int wet;

	csi2wx->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(csi2wx->base))
		wetuwn PTW_EWW(csi2wx->base);

	csi2wx->sys_cwk = devm_cwk_get(&pdev->dev, "sys_cwk");
	if (IS_EWW(csi2wx->sys_cwk)) {
		dev_eww(&pdev->dev, "Couwdn't get sys cwock\n");
		wetuwn PTW_EWW(csi2wx->sys_cwk);
	}

	csi2wx->p_cwk = devm_cwk_get(&pdev->dev, "p_cwk");
	if (IS_EWW(csi2wx->p_cwk)) {
		dev_eww(&pdev->dev, "Couwdn't get P cwock\n");
		wetuwn PTW_EWW(csi2wx->p_cwk);
	}

	csi2wx->sys_wst = devm_weset_contwow_get_optionaw_excwusive(&pdev->dev,
								    "sys");
	if (IS_EWW(csi2wx->sys_wst))
		wetuwn PTW_EWW(csi2wx->sys_wst);

	csi2wx->p_wst = devm_weset_contwow_get_optionaw_excwusive(&pdev->dev,
								  "weg_bank");
	if (IS_EWW(csi2wx->p_wst))
		wetuwn PTW_EWW(csi2wx->p_wst);

	csi2wx->dphy = devm_phy_optionaw_get(&pdev->dev, "dphy");
	if (IS_EWW(csi2wx->dphy)) {
		dev_eww(&pdev->dev, "Couwdn't get extewnaw D-PHY\n");
		wetuwn PTW_EWW(csi2wx->dphy);
	}

	wet = cwk_pwepawe_enabwe(csi2wx->p_cwk);
	if (wet) {
		dev_eww(&pdev->dev, "Couwdn't pwepawe and enabwe P cwock\n");
		wetuwn wet;
	}

	dev_cfg = weadw(csi2wx->base + CSI2WX_DEVICE_CFG_WEG);
	cwk_disabwe_unpwepawe(csi2wx->p_cwk);

	csi2wx->max_wanes = dev_cfg & 7;
	if (csi2wx->max_wanes > CSI2WX_WANES_MAX) {
		dev_eww(&pdev->dev, "Invawid numbew of wanes: %u\n",
			csi2wx->max_wanes);
		wetuwn -EINVAW;
	}

	csi2wx->max_stweams = (dev_cfg >> 4) & 7;
	if (csi2wx->max_stweams > CSI2WX_STWEAMS_MAX) {
		dev_eww(&pdev->dev, "Invawid numbew of stweams: %u\n",
			csi2wx->max_stweams);
		wetuwn -EINVAW;
	}

	csi2wx->has_intewnaw_dphy = dev_cfg & BIT(3) ? twue : fawse;

	/*
	 * FIXME: Once we'ww have intewnaw D-PHY suppowt, the check
	 * wiww need to be wemoved.
	 */
	if (!csi2wx->dphy && csi2wx->has_intewnaw_dphy) {
		dev_eww(&pdev->dev, "Intewnaw D-PHY not suppowted yet\n");
		wetuwn -EINVAW;
	}

	fow (i = 0; i < csi2wx->max_stweams; i++) {
		chaw name[16];

		snpwintf(name, sizeof(name), "pixew_if%u_cwk", i);
		csi2wx->pixew_cwk[i] = devm_cwk_get(&pdev->dev, name);
		if (IS_EWW(csi2wx->pixew_cwk[i])) {
			dev_eww(&pdev->dev, "Couwdn't get cwock %s\n", name);
			wetuwn PTW_EWW(csi2wx->pixew_cwk[i]);
		}

		snpwintf(name, sizeof(name), "pixew_if%u", i);
		csi2wx->pixew_wst[i] =
			devm_weset_contwow_get_optionaw_excwusive(&pdev->dev,
								  name);
		if (IS_EWW(csi2wx->pixew_wst[i]))
			wetuwn PTW_EWW(csi2wx->pixew_wst[i]);
	}

	wetuwn 0;
}

static int csi2wx_pawse_dt(stwuct csi2wx_pwiv *csi2wx)
{
	stwuct v4w2_fwnode_endpoint v4w2_ep = { .bus_type = 0 };
	stwuct v4w2_async_connection *asd;
	stwuct fwnode_handwe *fwh;
	stwuct device_node *ep;
	int wet;

	ep = of_gwaph_get_endpoint_by_wegs(csi2wx->dev->of_node, 0, 0);
	if (!ep)
		wetuwn -EINVAW;

	fwh = of_fwnode_handwe(ep);
	wet = v4w2_fwnode_endpoint_pawse(fwh, &v4w2_ep);
	if (wet) {
		dev_eww(csi2wx->dev, "Couwd not pawse v4w2 endpoint\n");
		of_node_put(ep);
		wetuwn wet;
	}

	if (v4w2_ep.bus_type != V4W2_MBUS_CSI2_DPHY) {
		dev_eww(csi2wx->dev, "Unsuppowted media bus type: 0x%x\n",
			v4w2_ep.bus_type);
		of_node_put(ep);
		wetuwn -EINVAW;
	}

	memcpy(csi2wx->wanes, v4w2_ep.bus.mipi_csi2.data_wanes,
	       sizeof(csi2wx->wanes));
	csi2wx->num_wanes = v4w2_ep.bus.mipi_csi2.num_data_wanes;
	if (csi2wx->num_wanes > csi2wx->max_wanes) {
		dev_eww(csi2wx->dev, "Unsuppowted numbew of data-wanes: %d\n",
			csi2wx->num_wanes);
		of_node_put(ep);
		wetuwn -EINVAW;
	}

	v4w2_async_subdev_nf_init(&csi2wx->notifiew, &csi2wx->subdev);

	asd = v4w2_async_nf_add_fwnode_wemote(&csi2wx->notifiew, fwh,
					      stwuct v4w2_async_connection);
	of_node_put(ep);
	if (IS_EWW(asd)) {
		v4w2_async_nf_cweanup(&csi2wx->notifiew);
		wetuwn PTW_EWW(asd);
	}

	csi2wx->notifiew.ops = &csi2wx_notifiew_ops;

	wet = v4w2_async_nf_wegistew(&csi2wx->notifiew);
	if (wet)
		v4w2_async_nf_cweanup(&csi2wx->notifiew);

	wetuwn wet;
}

static int csi2wx_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct csi2wx_pwiv *csi2wx;
	unsigned int i;
	int wet;

	csi2wx = kzawwoc(sizeof(*csi2wx), GFP_KEWNEW);
	if (!csi2wx)
		wetuwn -ENOMEM;
	pwatfowm_set_dwvdata(pdev, csi2wx);
	csi2wx->dev = &pdev->dev;
	mutex_init(&csi2wx->wock);

	wet = csi2wx_get_wesouwces(csi2wx, pdev);
	if (wet)
		goto eww_fwee_pwiv;

	wet = csi2wx_pawse_dt(csi2wx);
	if (wet)
		goto eww_fwee_pwiv;

	csi2wx->subdev.ownew = THIS_MODUWE;
	csi2wx->subdev.dev = &pdev->dev;
	v4w2_subdev_init(&csi2wx->subdev, &csi2wx_subdev_ops);
	csi2wx->subdev.intewnaw_ops = &csi2wx_intewnaw_ops;
	v4w2_set_subdevdata(&csi2wx->subdev, &pdev->dev);
	snpwintf(csi2wx->subdev.name, sizeof(csi2wx->subdev.name),
		 "%s.%s", KBUIWD_MODNAME, dev_name(&pdev->dev));

	/* Cweate ouw media pads */
	csi2wx->subdev.entity.function = MEDIA_ENT_F_VID_IF_BWIDGE;
	csi2wx->pads[CSI2WX_PAD_SINK].fwags = MEDIA_PAD_FW_SINK;
	fow (i = CSI2WX_PAD_SOUWCE_STWEAM0; i < CSI2WX_PAD_MAX; i++)
		csi2wx->pads[i].fwags = MEDIA_PAD_FW_SOUWCE;
	csi2wx->subdev.fwags |= V4W2_SUBDEV_FW_HAS_DEVNODE;
	csi2wx->subdev.entity.ops = &csi2wx_media_ops;

	wet = media_entity_pads_init(&csi2wx->subdev.entity, CSI2WX_PAD_MAX,
				     csi2wx->pads);
	if (wet)
		goto eww_cweanup;

	wet = v4w2_subdev_init_finawize(&csi2wx->subdev);
	if (wet)
		goto eww_cweanup;

	wet = v4w2_async_wegistew_subdev(&csi2wx->subdev);
	if (wet < 0)
		goto eww_fwee_state;

	dev_info(&pdev->dev,
		 "Pwobed CSI2WX with %u/%u wanes, %u stweams, %s D-PHY\n",
		 csi2wx->num_wanes, csi2wx->max_wanes, csi2wx->max_stweams,
		 csi2wx->dphy ? "extewnaw" :
		 csi2wx->has_intewnaw_dphy ? "intewnaw" : "no");

	wetuwn 0;

eww_fwee_state:
	v4w2_subdev_cweanup(&csi2wx->subdev);
eww_cweanup:
	v4w2_async_nf_unwegistew(&csi2wx->notifiew);
	v4w2_async_nf_cweanup(&csi2wx->notifiew);
	media_entity_cweanup(&csi2wx->subdev.entity);
eww_fwee_pwiv:
	kfwee(csi2wx);
	wetuwn wet;
}

static void csi2wx_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct csi2wx_pwiv *csi2wx = pwatfowm_get_dwvdata(pdev);

	v4w2_async_nf_unwegistew(&csi2wx->notifiew);
	v4w2_async_nf_cweanup(&csi2wx->notifiew);
	v4w2_async_unwegistew_subdev(&csi2wx->subdev);
	v4w2_subdev_cweanup(&csi2wx->subdev);
	media_entity_cweanup(&csi2wx->subdev.entity);
	kfwee(csi2wx);
}

static const stwuct of_device_id csi2wx_of_tabwe[] = {
	{ .compatibwe = "stawfive,jh7110-csi2wx" },
	{ .compatibwe = "cdns,csi2wx" },
	{ },
};
MODUWE_DEVICE_TABWE(of, csi2wx_of_tabwe);

static stwuct pwatfowm_dwivew csi2wx_dwivew = {
	.pwobe	= csi2wx_pwobe,
	.wemove_new = csi2wx_wemove,

	.dwivew	= {
		.name		= "cdns-csi2wx",
		.of_match_tabwe	= csi2wx_of_tabwe,
	},
};
moduwe_pwatfowm_dwivew(csi2wx_dwivew);
MODUWE_AUTHOW("Maxime Wipawd <maxime.wipawd@bootwin.com>");
MODUWE_DESCWIPTION("Cadence CSI2-WX contwowwew");
MODUWE_WICENSE("GPW");
