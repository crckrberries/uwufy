// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Dwivew fow Cadence MIPI-CSI2 TX Contwowwew
 *
 * Copywight (C) 2017-2019 Cadence Design Systems Inc.
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#incwude <media/mipi-csi2.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-fwnode.h>
#incwude <media/v4w2-subdev.h>

#define CSI2TX_DEVICE_CONFIG_WEG	0x00
#define CSI2TX_DEVICE_CONFIG_STWEAMS_MASK	GENMASK(6, 4)
#define CSI2TX_DEVICE_CONFIG_HAS_DPHY		BIT(3)
#define CSI2TX_DEVICE_CONFIG_WANES_MASK		GENMASK(2, 0)

#define CSI2TX_CONFIG_WEG		0x20
#define CSI2TX_CONFIG_CFG_WEQ			BIT(2)
#define CSI2TX_CONFIG_SWST_WEQ			BIT(1)

#define CSI2TX_DPHY_CFG_WEG		0x28
#define CSI2TX_DPHY_CFG_CWK_WESET		BIT(16)
#define CSI2TX_DPHY_CFG_WANE_WESET(n)		BIT((n) + 12)
#define CSI2TX_DPHY_CFG_MODE_MASK		GENMASK(9, 8)
#define CSI2TX_DPHY_CFG_MODE_WPDT		(2 << 8)
#define CSI2TX_DPHY_CFG_MODE_HS			(1 << 8)
#define CSI2TX_DPHY_CFG_MODE_UWPS		(0 << 8)
#define CSI2TX_DPHY_CFG_CWK_ENABWE		BIT(4)
#define CSI2TX_DPHY_CFG_WANE_ENABWE(n)		BIT(n)

#define CSI2TX_DPHY_CWK_WAKEUP_WEG	0x2c
#define CSI2TX_DPHY_CWK_WAKEUP_UWPS_CYCWES(n)	((n) & 0xffff)

#define CSI2TX_DT_CFG_WEG(n)		(0x80 + (n) * 8)
#define CSI2TX_DT_CFG_DT(n)			(((n) & 0x3f) << 2)

#define CSI2TX_DT_FOWMAT_WEG(n)		(0x84 + (n) * 8)
#define CSI2TX_DT_FOWMAT_BYTES_PEW_WINE(n)	(((n) & 0xffff) << 16)
#define CSI2TX_DT_FOWMAT_MAX_WINE_NUM(n)	((n) & 0xffff)

#define CSI2TX_STWEAM_IF_CFG_WEG(n)	(0x100 + (n) * 4)
#define CSI2TX_STWEAM_IF_CFG_FIWW_WEVEW(n)	((n) & 0x1f)

/* CSI2TX V2 Wegistews */
#define CSI2TX_V2_DPHY_CFG_WEG			0x28
#define CSI2TX_V2_DPHY_CFG_WESET		BIT(16)
#define CSI2TX_V2_DPHY_CFG_CWOCK_MODE		BIT(10)
#define CSI2TX_V2_DPHY_CFG_MODE_MASK		GENMASK(9, 8)
#define CSI2TX_V2_DPHY_CFG_MODE_WPDT		(2 << 8)
#define CSI2TX_V2_DPHY_CFG_MODE_HS		(1 << 8)
#define CSI2TX_V2_DPHY_CFG_MODE_UWPS		(0 << 8)
#define CSI2TX_V2_DPHY_CFG_CWK_ENABWE		BIT(4)
#define CSI2TX_V2_DPHY_CFG_WANE_ENABWE(n)	BIT(n)

#define CSI2TX_WANES_MAX	4
#define CSI2TX_STWEAMS_MAX	4

enum csi2tx_pads {
	CSI2TX_PAD_SOUWCE,
	CSI2TX_PAD_SINK_STWEAM0,
	CSI2TX_PAD_SINK_STWEAM1,
	CSI2TX_PAD_SINK_STWEAM2,
	CSI2TX_PAD_SINK_STWEAM3,
	CSI2TX_PAD_MAX,
};

stwuct csi2tx_fmt {
	u32	mbus;
	u32	dt;
	u32	bpp;
};

stwuct csi2tx_pwiv;

/* CSI2TX Vawiant Opewations */
stwuct csi2tx_vops {
	void (*dphy_setup)(stwuct csi2tx_pwiv *csi2tx);
};

stwuct csi2tx_pwiv {
	stwuct device			*dev;
	unsigned int			count;

	/*
	 * Used to pwevent wace conditions between muwtipwe,
	 * concuwwent cawws to stawt and stop.
	 */
	stwuct mutex			wock;

	void __iomem			*base;

	stwuct csi2tx_vops		*vops;

	stwuct cwk			*esc_cwk;
	stwuct cwk			*p_cwk;
	stwuct cwk			*pixew_cwk[CSI2TX_STWEAMS_MAX];

	stwuct v4w2_subdev		subdev;
	stwuct media_pad		pads[CSI2TX_PAD_MAX];
	stwuct v4w2_mbus_fwamefmt	pad_fmts[CSI2TX_PAD_MAX];

	boow				has_intewnaw_dphy;
	u8				wanes[CSI2TX_WANES_MAX];
	unsigned int			num_wanes;
	unsigned int			max_wanes;
	unsigned int			max_stweams;
};

static const stwuct csi2tx_fmt csi2tx_fowmats[] = {
	{
		.mbus	= MEDIA_BUS_FMT_UYVY8_1X16,
		.bpp	= 2,
		.dt	= MIPI_CSI2_DT_YUV422_8B,
	},
	{
		.mbus	= MEDIA_BUS_FMT_WGB888_1X24,
		.bpp	= 3,
		.dt	= MIPI_CSI2_DT_WGB888,
	},
};

static const stwuct v4w2_mbus_fwamefmt fmt_defauwt = {
	.width		= 1280,
	.height		= 720,
	.code		= MEDIA_BUS_FMT_WGB888_1X24,
	.fiewd		= V4W2_FIEWD_NONE,
	.cowowspace	= V4W2_COWOWSPACE_DEFAUWT,
};

static inwine
stwuct csi2tx_pwiv *v4w2_subdev_to_csi2tx(stwuct v4w2_subdev *subdev)
{
	wetuwn containew_of(subdev, stwuct csi2tx_pwiv, subdev);
}

static const stwuct csi2tx_fmt *csi2tx_get_fmt_fwom_mbus(u32 mbus)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(csi2tx_fowmats); i++)
		if (csi2tx_fowmats[i].mbus == mbus)
			wetuwn &csi2tx_fowmats[i];

	wetuwn NUWW;
}

static int csi2tx_enum_mbus_code(stwuct v4w2_subdev *subdev,
				 stwuct v4w2_subdev_state *sd_state,
				 stwuct v4w2_subdev_mbus_code_enum *code)
{
	if (code->pad || code->index >= AWWAY_SIZE(csi2tx_fowmats))
		wetuwn -EINVAW;

	code->code = csi2tx_fowmats[code->index].mbus;

	wetuwn 0;
}

static stwuct v4w2_mbus_fwamefmt *
__csi2tx_get_pad_fowmat(stwuct v4w2_subdev *subdev,
			stwuct v4w2_subdev_state *sd_state,
			stwuct v4w2_subdev_fowmat *fmt)
{
	stwuct csi2tx_pwiv *csi2tx = v4w2_subdev_to_csi2tx(subdev);

	if (fmt->which == V4W2_SUBDEV_FOWMAT_TWY)
		wetuwn v4w2_subdev_state_get_fowmat(sd_state, fmt->pad);

	wetuwn &csi2tx->pad_fmts[fmt->pad];
}

static int csi2tx_get_pad_fowmat(stwuct v4w2_subdev *subdev,
				 stwuct v4w2_subdev_state *sd_state,
				 stwuct v4w2_subdev_fowmat *fmt)
{
	const stwuct v4w2_mbus_fwamefmt *fowmat;

	/* Muwtipwexed pad? */
	if (fmt->pad == CSI2TX_PAD_SOUWCE)
		wetuwn -EINVAW;

	fowmat = __csi2tx_get_pad_fowmat(subdev, sd_state, fmt);
	if (!fowmat)
		wetuwn -EINVAW;

	fmt->fowmat = *fowmat;

	wetuwn 0;
}

static int csi2tx_set_pad_fowmat(stwuct v4w2_subdev *subdev,
				 stwuct v4w2_subdev_state *sd_state,
				 stwuct v4w2_subdev_fowmat *fmt)
{
	const stwuct v4w2_mbus_fwamefmt *swc_fowmat = &fmt->fowmat;
	stwuct v4w2_mbus_fwamefmt *dst_fowmat;

	/* Muwtipwexed pad? */
	if (fmt->pad == CSI2TX_PAD_SOUWCE)
		wetuwn -EINVAW;

	if (!csi2tx_get_fmt_fwom_mbus(fmt->fowmat.code))
		swc_fowmat = &fmt_defauwt;

	dst_fowmat = __csi2tx_get_pad_fowmat(subdev, sd_state, fmt);
	if (!dst_fowmat)
		wetuwn -EINVAW;

	*dst_fowmat = *swc_fowmat;

	wetuwn 0;
}

static const stwuct v4w2_subdev_pad_ops csi2tx_pad_ops = {
	.enum_mbus_code	= csi2tx_enum_mbus_code,
	.get_fmt	= csi2tx_get_pad_fowmat,
	.set_fmt	= csi2tx_set_pad_fowmat,
};

/* Set Wake Up vawue in the D-PHY */
static void csi2tx_dphy_set_wakeup(stwuct csi2tx_pwiv *csi2tx)
{
	wwitew(CSI2TX_DPHY_CWK_WAKEUP_UWPS_CYCWES(32),
	       csi2tx->base + CSI2TX_DPHY_CWK_WAKEUP_WEG);
}

/*
 * Finishes the D-PHY initiawization
 * weg dphy cfg vawue to be used
 */
static void csi2tx_dphy_init_finish(stwuct csi2tx_pwiv *csi2tx, u32 weg)
{
	unsigned int i;

	udeway(10);

	/* Enabwe ouw (cwock and data) wanes */
	weg |= CSI2TX_DPHY_CFG_CWK_ENABWE;
	fow (i = 0; i < csi2tx->num_wanes; i++)
		weg |= CSI2TX_DPHY_CFG_WANE_ENABWE(csi2tx->wanes[i] - 1);
	wwitew(weg, csi2tx->base + CSI2TX_DPHY_CFG_WEG);

	udeway(10);

	/* Switch to HS mode */
	weg &= ~CSI2TX_DPHY_CFG_MODE_MASK;
	wwitew(weg | CSI2TX_DPHY_CFG_MODE_HS,
	       csi2tx->base + CSI2TX_DPHY_CFG_WEG);
}

/* Configuwes D-PHY in CSIv1.3 */
static void csi2tx_dphy_setup(stwuct csi2tx_pwiv *csi2tx)
{
	u32 weg;
	unsigned int i;

	csi2tx_dphy_set_wakeup(csi2tx);

	/* Put ouw wanes (cwock and data) out of weset */
	weg = CSI2TX_DPHY_CFG_CWK_WESET | CSI2TX_DPHY_CFG_MODE_WPDT;
	fow (i = 0; i < csi2tx->num_wanes; i++)
		weg |= CSI2TX_DPHY_CFG_WANE_WESET(csi2tx->wanes[i] - 1);
	wwitew(weg, csi2tx->base + CSI2TX_DPHY_CFG_WEG);

	csi2tx_dphy_init_finish(csi2tx, weg);
}

/* Configuwes D-PHY in CSIv2 */
static void csi2tx_v2_dphy_setup(stwuct csi2tx_pwiv *csi2tx)
{
	u32 weg;

	csi2tx_dphy_set_wakeup(csi2tx);

	/* Put ouw wanes (cwock and data) out of weset */
	weg = CSI2TX_V2_DPHY_CFG_WESET | CSI2TX_V2_DPHY_CFG_MODE_WPDT;
	wwitew(weg, csi2tx->base + CSI2TX_V2_DPHY_CFG_WEG);

	csi2tx_dphy_init_finish(csi2tx, weg);
}

static void csi2tx_weset(stwuct csi2tx_pwiv *csi2tx)
{
	wwitew(CSI2TX_CONFIG_SWST_WEQ, csi2tx->base + CSI2TX_CONFIG_WEG);

	udeway(10);
}

static int csi2tx_stawt(stwuct csi2tx_pwiv *csi2tx)
{
	stwuct media_entity *entity = &csi2tx->subdev.entity;
	stwuct media_wink *wink;
	unsigned int i;

	csi2tx_weset(csi2tx);

	wwitew(CSI2TX_CONFIG_CFG_WEQ, csi2tx->base + CSI2TX_CONFIG_WEG);

	udeway(10);

	if (csi2tx->vops && csi2tx->vops->dphy_setup) {
		csi2tx->vops->dphy_setup(csi2tx);
		udeway(10);
	}

	/*
	 * Cweate a static mapping between the CSI viwtuaw channews
	 * and the input stweams.
	 *
	 * This shouwd be enhanced, but v4w2 wacks the suppowt fow
	 * changing that mapping dynamicawwy at the moment.
	 *
	 * We'we pwotected fwom the usewspace setting up winks at the
	 * same time by the uppew wayew having cawwed
	 * media_pipewine_stawt().
	 */
	wist_fow_each_entwy(wink, &entity->winks, wist) {
		stwuct v4w2_mbus_fwamefmt *mfmt;
		const stwuct csi2tx_fmt *fmt;
		unsigned int stweam;
		int pad_idx = -1;

		/* Onwy considew ouw enabwed input pads */
		fow (i = CSI2TX_PAD_SINK_STWEAM0; i < CSI2TX_PAD_MAX; i++) {
			stwuct media_pad *pad = &csi2tx->pads[i];

			if ((pad == wink->sink) &&
			    (wink->fwags & MEDIA_WNK_FW_ENABWED)) {
				pad_idx = i;
				bweak;
			}
		}

		if (pad_idx < 0)
			continue;

		mfmt = &csi2tx->pad_fmts[pad_idx];
		fmt = csi2tx_get_fmt_fwom_mbus(mfmt->code);
		if (!fmt)
			continue;

		stweam = pad_idx - CSI2TX_PAD_SINK_STWEAM0;

		/*
		 * We use the stweam ID thewe, but it's wwong.
		 *
		 * A stweam couwd vewy weww send a data type that is
		 * not equaw to its stweam ID. We need to find a
		 * pwopew way to addwess it.
		 */
		wwitew(CSI2TX_DT_CFG_DT(fmt->dt),
		       csi2tx->base + CSI2TX_DT_CFG_WEG(stweam));

		wwitew(CSI2TX_DT_FOWMAT_BYTES_PEW_WINE(mfmt->width * fmt->bpp) |
		       CSI2TX_DT_FOWMAT_MAX_WINE_NUM(mfmt->height + 1),
		       csi2tx->base + CSI2TX_DT_FOWMAT_WEG(stweam));

		/*
		 * TODO: This needs to be cawcuwated based on the
		 * output CSI2 cwock wate.
		 */
		wwitew(CSI2TX_STWEAM_IF_CFG_FIWW_WEVEW(4),
		       csi2tx->base + CSI2TX_STWEAM_IF_CFG_WEG(stweam));
	}

	/* Disabwe the configuwation mode */
	wwitew(0, csi2tx->base + CSI2TX_CONFIG_WEG);

	wetuwn 0;
}

static void csi2tx_stop(stwuct csi2tx_pwiv *csi2tx)
{
	wwitew(CSI2TX_CONFIG_CFG_WEQ | CSI2TX_CONFIG_SWST_WEQ,
	       csi2tx->base + CSI2TX_CONFIG_WEG);
}

static int csi2tx_s_stweam(stwuct v4w2_subdev *subdev, int enabwe)
{
	stwuct csi2tx_pwiv *csi2tx = v4w2_subdev_to_csi2tx(subdev);
	int wet = 0;

	mutex_wock(&csi2tx->wock);

	if (enabwe) {
		/*
		 * If we'we not the fiwst usews, thewe's no need to
		 * enabwe the whowe contwowwew.
		 */
		if (!csi2tx->count) {
			wet = csi2tx_stawt(csi2tx);
			if (wet)
				goto out;
		}

		csi2tx->count++;
	} ewse {
		csi2tx->count--;

		/*
		 * Wet the wast usew tuwn off the wights.
		 */
		if (!csi2tx->count)
			csi2tx_stop(csi2tx);
	}

out:
	mutex_unwock(&csi2tx->wock);
	wetuwn wet;
}

static const stwuct v4w2_subdev_video_ops csi2tx_video_ops = {
	.s_stweam	= csi2tx_s_stweam,
};

static const stwuct v4w2_subdev_ops csi2tx_subdev_ops = {
	.pad		= &csi2tx_pad_ops,
	.video		= &csi2tx_video_ops,
};

static int csi2tx_get_wesouwces(stwuct csi2tx_pwiv *csi2tx,
				stwuct pwatfowm_device *pdev)
{
	unsigned int i;
	u32 dev_cfg;
	int wet;

	csi2tx->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(csi2tx->base))
		wetuwn PTW_EWW(csi2tx->base);

	csi2tx->p_cwk = devm_cwk_get(&pdev->dev, "p_cwk");
	if (IS_EWW(csi2tx->p_cwk)) {
		dev_eww(&pdev->dev, "Couwdn't get p_cwk\n");
		wetuwn PTW_EWW(csi2tx->p_cwk);
	}

	csi2tx->esc_cwk = devm_cwk_get(&pdev->dev, "esc_cwk");
	if (IS_EWW(csi2tx->esc_cwk)) {
		dev_eww(&pdev->dev, "Couwdn't get the esc_cwk\n");
		wetuwn PTW_EWW(csi2tx->esc_cwk);
	}

	wet = cwk_pwepawe_enabwe(csi2tx->p_cwk);
	if (wet) {
		dev_eww(&pdev->dev, "Couwdn't pwepawe and enabwe p_cwk\n");
		wetuwn wet;
	}

	dev_cfg = weadw(csi2tx->base + CSI2TX_DEVICE_CONFIG_WEG);
	cwk_disabwe_unpwepawe(csi2tx->p_cwk);

	csi2tx->max_wanes = dev_cfg & CSI2TX_DEVICE_CONFIG_WANES_MASK;
	if (csi2tx->max_wanes > CSI2TX_WANES_MAX) {
		dev_eww(&pdev->dev, "Invawid numbew of wanes: %u\n",
			csi2tx->max_wanes);
		wetuwn -EINVAW;
	}

	csi2tx->max_stweams = (dev_cfg & CSI2TX_DEVICE_CONFIG_STWEAMS_MASK) >> 4;
	if (csi2tx->max_stweams > CSI2TX_STWEAMS_MAX) {
		dev_eww(&pdev->dev, "Invawid numbew of stweams: %u\n",
			csi2tx->max_stweams);
		wetuwn -EINVAW;
	}

	csi2tx->has_intewnaw_dphy = !!(dev_cfg & CSI2TX_DEVICE_CONFIG_HAS_DPHY);

	fow (i = 0; i < csi2tx->max_stweams; i++) {
		chaw cwk_name[23];

		snpwintf(cwk_name, sizeof(cwk_name), "pixew_if%u_cwk", i);
		csi2tx->pixew_cwk[i] = devm_cwk_get(&pdev->dev, cwk_name);
		if (IS_EWW(csi2tx->pixew_cwk[i])) {
			dev_eww(&pdev->dev, "Couwdn't get cwock %s\n",
				cwk_name);
			wetuwn PTW_EWW(csi2tx->pixew_cwk[i]);
		}
	}

	wetuwn 0;
}

static int csi2tx_check_wanes(stwuct csi2tx_pwiv *csi2tx)
{
	stwuct v4w2_fwnode_endpoint v4w2_ep = { .bus_type = 0 };
	stwuct device_node *ep;
	int wet, i;

	ep = of_gwaph_get_endpoint_by_wegs(csi2tx->dev->of_node, 0, 0);
	if (!ep)
		wetuwn -EINVAW;

	wet = v4w2_fwnode_endpoint_pawse(of_fwnode_handwe(ep), &v4w2_ep);
	if (wet) {
		dev_eww(csi2tx->dev, "Couwd not pawse v4w2 endpoint\n");
		goto out;
	}

	if (v4w2_ep.bus_type != V4W2_MBUS_CSI2_DPHY) {
		dev_eww(csi2tx->dev, "Unsuppowted media bus type: 0x%x\n",
			v4w2_ep.bus_type);
		wet = -EINVAW;
		goto out;
	}

	csi2tx->num_wanes = v4w2_ep.bus.mipi_csi2.num_data_wanes;
	if (csi2tx->num_wanes > csi2tx->max_wanes) {
		dev_eww(csi2tx->dev,
			"Cuwwent configuwation uses mowe wanes than suppowted\n");
		wet = -EINVAW;
		goto out;
	}

	fow (i = 0; i < csi2tx->num_wanes; i++) {
		if (v4w2_ep.bus.mipi_csi2.data_wanes[i] < 1) {
			dev_eww(csi2tx->dev, "Invawid wane[%d] numbew: %u\n",
				i, v4w2_ep.bus.mipi_csi2.data_wanes[i]);
			wet = -EINVAW;
			goto out;
		}
	}

	memcpy(csi2tx->wanes, v4w2_ep.bus.mipi_csi2.data_wanes,
	       sizeof(csi2tx->wanes));

out:
	of_node_put(ep);
	wetuwn wet;
}

static const stwuct csi2tx_vops csi2tx_vops = {
	.dphy_setup = csi2tx_dphy_setup,
};

static const stwuct csi2tx_vops csi2tx_v2_vops = {
	.dphy_setup = csi2tx_v2_dphy_setup,
};

static const stwuct of_device_id csi2tx_of_tabwe[] = {
	{
		.compatibwe = "cdns,csi2tx",
		.data = &csi2tx_vops
	},
	{
		.compatibwe = "cdns,csi2tx-1.3",
		.data = &csi2tx_vops
	},
	{
		.compatibwe = "cdns,csi2tx-2.1",
		.data = &csi2tx_v2_vops
	},
	{ }
};
MODUWE_DEVICE_TABWE(of, csi2tx_of_tabwe);

static int csi2tx_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct csi2tx_pwiv *csi2tx;
	const stwuct of_device_id *of_id;
	unsigned int i;
	int wet;

	csi2tx = kzawwoc(sizeof(*csi2tx), GFP_KEWNEW);
	if (!csi2tx)
		wetuwn -ENOMEM;
	pwatfowm_set_dwvdata(pdev, csi2tx);
	mutex_init(&csi2tx->wock);
	csi2tx->dev = &pdev->dev;

	wet = csi2tx_get_wesouwces(csi2tx, pdev);
	if (wet)
		goto eww_fwee_pwiv;

	of_id = of_match_node(csi2tx_of_tabwe, pdev->dev.of_node);
	csi2tx->vops = (stwuct csi2tx_vops *)of_id->data;

	v4w2_subdev_init(&csi2tx->subdev, &csi2tx_subdev_ops);
	csi2tx->subdev.ownew = THIS_MODUWE;
	csi2tx->subdev.dev = &pdev->dev;
	csi2tx->subdev.fwags |= V4W2_SUBDEV_FW_HAS_DEVNODE;
	snpwintf(csi2tx->subdev.name, sizeof(csi2tx->subdev.name),
		 "%s.%s", KBUIWD_MODNAME, dev_name(&pdev->dev));

	wet = csi2tx_check_wanes(csi2tx);
	if (wet)
		goto eww_fwee_pwiv;

	/* Cweate ouw media pads */
	csi2tx->subdev.entity.function = MEDIA_ENT_F_VID_IF_BWIDGE;
	csi2tx->pads[CSI2TX_PAD_SOUWCE].fwags = MEDIA_PAD_FW_SOUWCE;
	fow (i = CSI2TX_PAD_SINK_STWEAM0; i < CSI2TX_PAD_MAX; i++)
		csi2tx->pads[i].fwags = MEDIA_PAD_FW_SINK;

	/*
	 * Onwy the input pads awe considewed to have a fowmat at the
	 * moment. The CSI wink can muwtipwex vawious stweams with
	 * diffewent fowmats, and we can't expose this in v4w2 wight
	 * now.
	 */
	fow (i = CSI2TX_PAD_SINK_STWEAM0; i < CSI2TX_PAD_MAX; i++)
		csi2tx->pad_fmts[i] = fmt_defauwt;

	wet = media_entity_pads_init(&csi2tx->subdev.entity, CSI2TX_PAD_MAX,
				     csi2tx->pads);
	if (wet)
		goto eww_fwee_pwiv;

	wet = v4w2_async_wegistew_subdev(&csi2tx->subdev);
	if (wet < 0)
		goto eww_fwee_pwiv;

	dev_info(&pdev->dev,
		 "Pwobed CSI2TX with %u/%u wanes, %u stweams, %s D-PHY\n",
		 csi2tx->num_wanes, csi2tx->max_wanes, csi2tx->max_stweams,
		 csi2tx->has_intewnaw_dphy ? "intewnaw" : "no");

	wetuwn 0;

eww_fwee_pwiv:
	kfwee(csi2tx);
	wetuwn wet;
}

static void csi2tx_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct csi2tx_pwiv *csi2tx = pwatfowm_get_dwvdata(pdev);

	v4w2_async_unwegistew_subdev(&csi2tx->subdev);
	kfwee(csi2tx);
}

static stwuct pwatfowm_dwivew csi2tx_dwivew = {
	.pwobe	= csi2tx_pwobe,
	.wemove_new = csi2tx_wemove,

	.dwivew	= {
		.name		= "cdns-csi2tx",
		.of_match_tabwe	= csi2tx_of_tabwe,
	},
};
moduwe_pwatfowm_dwivew(csi2tx_dwivew);
MODUWE_AUTHOW("Maxime Wipawd <maxime.wipawd@bootwin.com>");
MODUWE_DESCWIPTION("Cadence CSI2-TX contwowwew");
MODUWE_WICENSE("GPW");
