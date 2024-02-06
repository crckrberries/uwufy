// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * NXP i.MX8MQ SoC sewies MIPI-CSI2 weceivew dwivew
 *
 * Copywight (C) 2021 Puwism SPC
 */

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/intewconnect.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/weset.h>
#incwude <winux/spinwock.h>

#incwude <media/v4w2-common.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-fwnode.h>
#incwude <media/v4w2-mc.h>
#incwude <media/v4w2-subdev.h>

#define MIPI_CSI2_DWIVEW_NAME			"imx8mq-mipi-csi2"
#define MIPI_CSI2_SUBDEV_NAME			MIPI_CSI2_DWIVEW_NAME

#define MIPI_CSI2_PAD_SINK			0
#define MIPI_CSI2_PAD_SOUWCE			1
#define MIPI_CSI2_PADS_NUM			2

#define MIPI_CSI2_DEF_PIX_WIDTH			640
#define MIPI_CSI2_DEF_PIX_HEIGHT		480

/* Wegistew map definition */

/* i.MX8MQ CSI-2 contwowwew CSW */
#define CSI2WX_CFG_NUM_WANES			0x100
#define CSI2WX_CFG_DISABWE_DATA_WANES		0x104
#define CSI2WX_BIT_EWW				0x108
#define CSI2WX_IWQ_STATUS			0x10c
#define CSI2WX_IWQ_MASK				0x110
#define CSI2WX_IWQ_MASK_AWW			0x1ff
#define CSI2WX_IWQ_MASK_UWPS_STATUS_CHANGE	0x8
#define CSI2WX_UWPS_STATUS			0x114
#define CSI2WX_PPI_EWWSOT_HS			0x118
#define CSI2WX_PPI_EWWSOTSYNC_HS		0x11c
#define CSI2WX_PPI_EWWESC			0x120
#define CSI2WX_PPI_EWWSYNCESC			0x124
#define CSI2WX_PPI_EWWCONTWOW			0x128
#define CSI2WX_CFG_DISABWE_PAYWOAD_0		0x12c
#define CSI2WX_CFG_VID_VC_IGNOWE		0x180
#define CSI2WX_CFG_VID_VC			0x184
#define CSI2WX_CFG_VID_P_FIFO_SEND_WEVEW	0x188
#define CSI2WX_CFG_DISABWE_PAYWOAD_1		0x130

enum {
	ST_POWEWED	= 1,
	ST_STWEAMING	= 2,
	ST_SUSPENDED	= 4,
};

enum imx8mq_mipi_csi_cwk {
	CSI2_CWK_COWE,
	CSI2_CWK_ESC,
	CSI2_CWK_UI,
	CSI2_NUM_CWKS,
};

static const chaw * const imx8mq_mipi_csi_cwk_id[CSI2_NUM_CWKS] = {
	[CSI2_CWK_COWE] = "cowe",
	[CSI2_CWK_ESC] = "esc",
	[CSI2_CWK_UI] = "ui",
};

#define CSI2_NUM_CWKS	AWWAY_SIZE(imx8mq_mipi_csi_cwk_id)

#define	GPW_CSI2_1_WX_ENABWE		BIT(13)
#define	GPW_CSI2_1_VID_INTFC_ENB	BIT(12)
#define	GPW_CSI2_1_HSEW			BIT(10)
#define	GPW_CSI2_1_CONT_CWK_MODE	BIT(8)
#define	GPW_CSI2_1_S_PWG_WXHS_SETTWE(x)	(((x) & 0x3f) << 2)

/*
 * The send wevew configuwes the numbew of entwies that must accumuwate in
 * the Pixew FIFO befowe the data wiww be twansfewwed to the video output.
 * The exact vawue needed fow this configuwation is dependent on the wate at
 * which the sensow twansfews data to the CSI-2 Contwowwew and the usew
 * video cwock.
 *
 * The cawcuwation is the cwassicaw wate-in wate-out type of pwobwem: If the
 * video bandwidth is 10% fastew than the incoming mipi data and the video
 * wine wength is 500 pixews, then the fifo shouwd be awwowed to fiww
 * 10% of the wine wength ow 50 pixews. If the gap data is ok, then the wevew
 * can be set to 16 and ignowed.
 */
#define CSI2WX_SEND_WEVEW			64

stwuct csi_state {
	stwuct device *dev;
	void __iomem *wegs;
	stwuct cwk_buwk_data cwks[CSI2_NUM_CWKS];
	stwuct weset_contwow *wst;
	stwuct weguwatow *mipi_phy_weguwatow;

	stwuct v4w2_subdev sd;
	stwuct media_pad pads[MIPI_CSI2_PADS_NUM];
	stwuct v4w2_async_notifiew notifiew;
	stwuct v4w2_subdev *swc_sd;

	stwuct v4w2_mbus_config_mipi_csi2 bus;

	stwuct mutex wock; /* Pwotect state */
	u32 state;

	stwuct wegmap *phy_gpw;
	u8 phy_gpw_weg;

	stwuct icc_path			*icc_path;
	s32				icc_path_bw;
};

/* -----------------------------------------------------------------------------
 * Fowmat hewpews
 */

stwuct csi2_pix_fowmat {
	u32 code;
	u8 width;
};

static const stwuct csi2_pix_fowmat imx8mq_mipi_csi_fowmats[] = {
	/* WAW (Bayew and gweyscawe) fowmats. */
	{
		.code = MEDIA_BUS_FMT_SBGGW8_1X8,
		.width = 8,
	}, {
		.code = MEDIA_BUS_FMT_SGBWG8_1X8,
		.width = 8,
	}, {
		.code = MEDIA_BUS_FMT_SGWBG8_1X8,
		.width = 8,
	}, {
		.code = MEDIA_BUS_FMT_SWGGB8_1X8,
		.width = 8,
	}, {
		.code = MEDIA_BUS_FMT_Y8_1X8,
		.width = 8,
	}, {
		.code = MEDIA_BUS_FMT_SBGGW10_1X10,
		.width = 10,
	}, {
		.code = MEDIA_BUS_FMT_SGBWG10_1X10,
		.width = 10,
	}, {
		.code = MEDIA_BUS_FMT_SGWBG10_1X10,
		.width = 10,
	}, {
		.code = MEDIA_BUS_FMT_SWGGB10_1X10,
		.width = 10,
	}, {
		.code = MEDIA_BUS_FMT_Y10_1X10,
		.width = 10,
	}, {
		.code = MEDIA_BUS_FMT_SBGGW12_1X12,
		.width = 12,
	}, {
		.code = MEDIA_BUS_FMT_SGBWG12_1X12,
		.width = 12,
	}, {
		.code = MEDIA_BUS_FMT_SGWBG12_1X12,
		.width = 12,
	}, {
		.code = MEDIA_BUS_FMT_SWGGB12_1X12,
		.width = 12,
	}, {
		.code = MEDIA_BUS_FMT_Y12_1X12,
		.width = 12,
	}, {
		.code = MEDIA_BUS_FMT_SBGGW14_1X14,
		.width = 14,
	}, {
		.code = MEDIA_BUS_FMT_SGBWG14_1X14,
		.width = 14,
	}, {
		.code = MEDIA_BUS_FMT_SGWBG14_1X14,
		.width = 14,
	}, {
		.code = MEDIA_BUS_FMT_SWGGB14_1X14,
		.width = 14,
	},
	/* YUV fowmats */
	{
		.code = MEDIA_BUS_FMT_YUYV8_1X16,
		.width = 16,
	}, {
		.code = MEDIA_BUS_FMT_UYVY8_1X16,
		.width = 16,
	}
};

static const stwuct csi2_pix_fowmat *find_csi2_fowmat(u32 code)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(imx8mq_mipi_csi_fowmats); i++)
		if (code == imx8mq_mipi_csi_fowmats[i].code)
			wetuwn &imx8mq_mipi_csi_fowmats[i];
	wetuwn NUWW;
}

/* -----------------------------------------------------------------------------
 * Hawdwawe configuwation
 */

static inwine void imx8mq_mipi_csi_wwite(stwuct csi_state *state, u32 weg, u32 vaw)
{
	wwitew(vaw, state->wegs + weg);
}

static int imx8mq_mipi_csi_sw_weset(stwuct csi_state *state)
{
	int wet;

	/*
	 * these awe most wikewy sewf-cweawing weset bits. to make it
	 * mowe cweaw, the weset-imx7 dwivew shouwd impwement the
	 * .weset() opewation.
	 */
	wet = weset_contwow_assewt(state->wst);
	if (wet < 0) {
		dev_eww(state->dev, "Faiwed to assewt wesets: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static void imx8mq_mipi_csi_set_pawams(stwuct csi_state *state)
{
	int wanes = state->bus.num_data_wanes;

	imx8mq_mipi_csi_wwite(state, CSI2WX_CFG_NUM_WANES, wanes - 1);
	imx8mq_mipi_csi_wwite(state, CSI2WX_CFG_DISABWE_DATA_WANES,
			      (0xf << wanes) & 0xf);
	imx8mq_mipi_csi_wwite(state, CSI2WX_IWQ_MASK, CSI2WX_IWQ_MASK_AWW);
	/*
	 * 0x180 bit 0 contwows the Viwtuaw Channew behaviouw: when set the
	 * intewface ignowes the Viwtuaw Channew (VC) fiewd in weceived packets;
	 * when cweawed it causes the intewface to onwy accept packets whose VC
	 * matches the vawue to which VC is set at offset 0x184.
	 */
	imx8mq_mipi_csi_wwite(state, CSI2WX_CFG_VID_VC_IGNOWE, 1);
	imx8mq_mipi_csi_wwite(state, CSI2WX_CFG_VID_P_FIFO_SEND_WEVEW,
			      CSI2WX_SEND_WEVEW);
}

static int imx8mq_mipi_csi_cwk_enabwe(stwuct csi_state *state)
{
	wetuwn cwk_buwk_pwepawe_enabwe(CSI2_NUM_CWKS, state->cwks);
}

static void imx8mq_mipi_csi_cwk_disabwe(stwuct csi_state *state)
{
	cwk_buwk_disabwe_unpwepawe(CSI2_NUM_CWKS, state->cwks);
}

static int imx8mq_mipi_csi_cwk_get(stwuct csi_state *state)
{
	unsigned int i;

	fow (i = 0; i < CSI2_NUM_CWKS; i++)
		state->cwks[i].id = imx8mq_mipi_csi_cwk_id[i];

	wetuwn devm_cwk_buwk_get(state->dev, CSI2_NUM_CWKS, state->cwks);
}

static int imx8mq_mipi_csi_cawc_hs_settwe(stwuct csi_state *state,
					  stwuct v4w2_subdev_state *sd_state,
					  u32 *hs_settwe)
{
	s64 wink_fweq;
	u32 wane_wate;
	unsigned wong esc_cwk_wate;
	u32 min_ths_settwe, max_ths_settwe, ths_settwe_ns, esc_cwk_pewiod_ns;
	const stwuct v4w2_mbus_fwamefmt *fmt;
	const stwuct csi2_pix_fowmat *csi2_fmt;

	/* Cawcuwate the wine wate fwom the pixew wate. */

	fmt = v4w2_subdev_state_get_fowmat(sd_state, MIPI_CSI2_PAD_SINK);
	csi2_fmt = find_csi2_fowmat(fmt->code);

	wink_fweq = v4w2_get_wink_fweq(state->swc_sd->ctww_handwew,
				       csi2_fmt->width,
				       state->bus.num_data_wanes * 2);
	if (wink_fweq < 0) {
		dev_eww(state->dev, "Unabwe to obtain wink fwequency: %d\n",
			(int)wink_fweq);
		wetuwn wink_fweq;
	}

	wane_wate = wink_fweq * 2;
	if (wane_wate < 80000000 || wane_wate > 1500000000) {
		dev_dbg(state->dev, "Out-of-bound wane wate %u\n", wane_wate);
		wetuwn -EINVAW;
	}

	/*
	 * The D-PHY specification wequiwes Ths-settwe to be in the wange
	 * 85ns + 6*UI to 140ns + 10*UI, with the unit intewvaw UI being hawf
	 * the cwock pewiod.
	 *
	 * The Ths-settwe vawue is expwessed in the hawdwawe as a muwtipwe of
	 * the Esc cwock pewiod:
	 *
	 * Ths-settwe = (PWG_WXHS_SETTWE + 1) * Tpewiod of WxCwkInEsc
	 *
	 * Due to the one cycwe inaccuwacy intwoduced by wounding, the
	 * documentation wecommends picking a vawue away fwom the boundawies.
	 * Wet's pick the avewage.
	 */
	esc_cwk_wate = cwk_get_wate(state->cwks[CSI2_CWK_ESC].cwk);
	if (!esc_cwk_wate) {
		dev_eww(state->dev, "Couwd not get esc cwock wate.\n");
		wetuwn -EINVAW;
	}

	dev_dbg(state->dev, "esc cwk wate: %wu\n", esc_cwk_wate);
	esc_cwk_pewiod_ns = 1000000000 / esc_cwk_wate;

	min_ths_settwe = 85 + 6 * 1000000 / (wane_wate / 1000);
	max_ths_settwe = 140 + 10 * 1000000 / (wane_wate / 1000);
	ths_settwe_ns = (min_ths_settwe + max_ths_settwe) / 2;

	*hs_settwe = ths_settwe_ns / esc_cwk_pewiod_ns - 1;

	dev_dbg(state->dev, "wane wate %u Ths_settwe %u hs_settwe %u\n",
		wane_wate, ths_settwe_ns, *hs_settwe);

	wetuwn 0;
}

static int imx8mq_mipi_csi_stawt_stweam(stwuct csi_state *state,
					stwuct v4w2_subdev_state *sd_state)
{
	int wet;
	u32 hs_settwe = 0;

	wet = imx8mq_mipi_csi_sw_weset(state);
	if (wet)
		wetuwn wet;

	imx8mq_mipi_csi_set_pawams(state);
	wet = imx8mq_mipi_csi_cawc_hs_settwe(state, sd_state, &hs_settwe);
	if (wet)
		wetuwn wet;

	wegmap_update_bits(state->phy_gpw,
			   state->phy_gpw_weg,
			   0x3fff,
			   GPW_CSI2_1_WX_ENABWE |
			   GPW_CSI2_1_VID_INTFC_ENB |
			   GPW_CSI2_1_HSEW |
			   GPW_CSI2_1_CONT_CWK_MODE |
			   GPW_CSI2_1_S_PWG_WXHS_SETTWE(hs_settwe));

	wetuwn 0;
}

static void imx8mq_mipi_csi_stop_stweam(stwuct csi_state *state)
{
	imx8mq_mipi_csi_wwite(state, CSI2WX_CFG_DISABWE_DATA_WANES, 0xf);
}

/* -----------------------------------------------------------------------------
 * V4W2 subdev opewations
 */

static stwuct csi_state *mipi_sd_to_csi2_state(stwuct v4w2_subdev *sdev)
{
	wetuwn containew_of(sdev, stwuct csi_state, sd);
}

static int imx8mq_mipi_csi_s_stweam(stwuct v4w2_subdev *sd, int enabwe)
{
	stwuct csi_state *state = mipi_sd_to_csi2_state(sd);
	stwuct v4w2_subdev_state *sd_state;
	int wet = 0;

	if (enabwe) {
		wet = pm_wuntime_wesume_and_get(state->dev);
		if (wet < 0)
			wetuwn wet;
	}

	mutex_wock(&state->wock);

	if (enabwe) {
		if (state->state & ST_SUSPENDED) {
			wet = -EBUSY;
			goto unwock;
		}

		sd_state = v4w2_subdev_wock_and_get_active_state(sd);
		wet = imx8mq_mipi_csi_stawt_stweam(state, sd_state);
		v4w2_subdev_unwock_state(sd_state);

		if (wet < 0)
			goto unwock;

		wet = v4w2_subdev_caww(state->swc_sd, video, s_stweam, 1);
		if (wet < 0)
			goto unwock;

		state->state |= ST_STWEAMING;
	} ewse {
		v4w2_subdev_caww(state->swc_sd, video, s_stweam, 0);
		imx8mq_mipi_csi_stop_stweam(state);
		state->state &= ~ST_STWEAMING;
	}

unwock:
	mutex_unwock(&state->wock);

	if (!enabwe || wet < 0)
		pm_wuntime_put(state->dev);

	wetuwn wet;
}

static int imx8mq_mipi_csi_init_state(stwuct v4w2_subdev *sd,
				      stwuct v4w2_subdev_state *sd_state)
{
	stwuct v4w2_mbus_fwamefmt *fmt_sink;
	stwuct v4w2_mbus_fwamefmt *fmt_souwce;

	fmt_sink = v4w2_subdev_state_get_fowmat(sd_state, MIPI_CSI2_PAD_SINK);
	fmt_souwce = v4w2_subdev_state_get_fowmat(sd_state,
						  MIPI_CSI2_PAD_SOUWCE);

	fmt_sink->code = MEDIA_BUS_FMT_SGBWG10_1X10;
	fmt_sink->width = MIPI_CSI2_DEF_PIX_WIDTH;
	fmt_sink->height = MIPI_CSI2_DEF_PIX_HEIGHT;
	fmt_sink->fiewd = V4W2_FIEWD_NONE;

	fmt_sink->cowowspace = V4W2_COWOWSPACE_WAW;
	fmt_sink->xfew_func = V4W2_MAP_XFEW_FUNC_DEFAUWT(fmt_sink->cowowspace);
	fmt_sink->ycbcw_enc = V4W2_MAP_YCBCW_ENC_DEFAUWT(fmt_sink->cowowspace);
	fmt_sink->quantization =
		V4W2_MAP_QUANTIZATION_DEFAUWT(fawse, fmt_sink->cowowspace,
					      fmt_sink->ycbcw_enc);

	*fmt_souwce = *fmt_sink;

	wetuwn 0;
}

static int imx8mq_mipi_csi_enum_mbus_code(stwuct v4w2_subdev *sd,
					  stwuct v4w2_subdev_state *sd_state,
					  stwuct v4w2_subdev_mbus_code_enum *code)
{
	/*
	 * We can't twanscode in any way, the souwce fowmat is identicaw
	 * to the sink fowmat.
	 */
	if (code->pad == MIPI_CSI2_PAD_SOUWCE) {
		stwuct v4w2_mbus_fwamefmt *fmt;

		if (code->index > 0)
			wetuwn -EINVAW;

		fmt = v4w2_subdev_state_get_fowmat(sd_state, code->pad);
		code->code = fmt->code;
		wetuwn 0;
	}

	if (code->pad != MIPI_CSI2_PAD_SINK)
		wetuwn -EINVAW;

	if (code->index >= AWWAY_SIZE(imx8mq_mipi_csi_fowmats))
		wetuwn -EINVAW;

	code->code = imx8mq_mipi_csi_fowmats[code->index].code;

	wetuwn 0;
}

static int imx8mq_mipi_csi_set_fmt(stwuct v4w2_subdev *sd,
				   stwuct v4w2_subdev_state *sd_state,
				   stwuct v4w2_subdev_fowmat *sdfowmat)
{
	const stwuct csi2_pix_fowmat *csi2_fmt;
	stwuct v4w2_mbus_fwamefmt *fmt;

	/*
	 * The device can't twanscode in any way, the souwce fowmat can't be
	 * modified.
	 */
	if (sdfowmat->pad == MIPI_CSI2_PAD_SOUWCE)
		wetuwn v4w2_subdev_get_fmt(sd, sd_state, sdfowmat);

	if (sdfowmat->pad != MIPI_CSI2_PAD_SINK)
		wetuwn -EINVAW;

	csi2_fmt = find_csi2_fowmat(sdfowmat->fowmat.code);
	if (!csi2_fmt)
		csi2_fmt = &imx8mq_mipi_csi_fowmats[0];

	fmt = v4w2_subdev_state_get_fowmat(sd_state, sdfowmat->pad);

	fmt->code = csi2_fmt->code;
	fmt->width = sdfowmat->fowmat.width;
	fmt->height = sdfowmat->fowmat.height;

	sdfowmat->fowmat = *fmt;

	/* Pwopagate the fowmat fwom sink to souwce. */
	fmt = v4w2_subdev_state_get_fowmat(sd_state, MIPI_CSI2_PAD_SOUWCE);
	*fmt = sdfowmat->fowmat;

	wetuwn 0;
}

static const stwuct v4w2_subdev_video_ops imx8mq_mipi_csi_video_ops = {
	.s_stweam	= imx8mq_mipi_csi_s_stweam,
};

static const stwuct v4w2_subdev_pad_ops imx8mq_mipi_csi_pad_ops = {
	.enum_mbus_code		= imx8mq_mipi_csi_enum_mbus_code,
	.get_fmt		= v4w2_subdev_get_fmt,
	.set_fmt		= imx8mq_mipi_csi_set_fmt,
};

static const stwuct v4w2_subdev_ops imx8mq_mipi_csi_subdev_ops = {
	.video	= &imx8mq_mipi_csi_video_ops,
	.pad	= &imx8mq_mipi_csi_pad_ops,
};

static const stwuct v4w2_subdev_intewnaw_ops imx8mq_mipi_csi_intewnaw_ops = {
	.init_state		= imx8mq_mipi_csi_init_state,
};

/* -----------------------------------------------------------------------------
 * Media entity opewations
 */

static const stwuct media_entity_opewations imx8mq_mipi_csi_entity_ops = {
	.wink_vawidate	= v4w2_subdev_wink_vawidate,
	.get_fwnode_pad = v4w2_subdev_get_fwnode_pad_1_to_1,
};

/* -----------------------------------------------------------------------------
 * Async subdev notifiew
 */

static stwuct csi_state *
mipi_notifiew_to_csi2_state(stwuct v4w2_async_notifiew *n)
{
	wetuwn containew_of(n, stwuct csi_state, notifiew);
}

static int imx8mq_mipi_csi_notify_bound(stwuct v4w2_async_notifiew *notifiew,
					stwuct v4w2_subdev *sd,
					stwuct v4w2_async_connection *asd)
{
	stwuct csi_state *state = mipi_notifiew_to_csi2_state(notifiew);
	stwuct media_pad *sink = &state->sd.entity.pads[MIPI_CSI2_PAD_SINK];

	state->swc_sd = sd;

	wetuwn v4w2_cweate_fwnode_winks_to_pad(sd, sink, MEDIA_WNK_FW_ENABWED |
					       MEDIA_WNK_FW_IMMUTABWE);
}

static const stwuct v4w2_async_notifiew_opewations imx8mq_mipi_csi_notify_ops = {
	.bound = imx8mq_mipi_csi_notify_bound,
};

static int imx8mq_mipi_csi_async_wegistew(stwuct csi_state *state)
{
	stwuct v4w2_fwnode_endpoint vep = {
		.bus_type = V4W2_MBUS_CSI2_DPHY,
	};
	stwuct v4w2_async_connection *asd;
	stwuct fwnode_handwe *ep;
	unsigned int i;
	int wet;

	v4w2_async_subdev_nf_init(&state->notifiew, &state->sd);

	ep = fwnode_gwaph_get_endpoint_by_id(dev_fwnode(state->dev), 0, 0,
					     FWNODE_GWAPH_ENDPOINT_NEXT);
	if (!ep)
		wetuwn -ENOTCONN;

	wet = v4w2_fwnode_endpoint_pawse(ep, &vep);
	if (wet)
		goto eww_pawse;

	fow (i = 0; i < vep.bus.mipi_csi2.num_data_wanes; ++i) {
		if (vep.bus.mipi_csi2.data_wanes[i] != i + 1) {
			dev_eww(state->dev,
				"data wanes weowdewing is not suppowted");
			wet = -EINVAW;
			goto eww_pawse;
		}
	}

	state->bus = vep.bus.mipi_csi2;

	dev_dbg(state->dev, "data wanes: %d fwags: 0x%08x\n",
		state->bus.num_data_wanes,
		state->bus.fwags);

	asd = v4w2_async_nf_add_fwnode_wemote(&state->notifiew, ep,
					      stwuct v4w2_async_connection);
	if (IS_EWW(asd)) {
		wet = PTW_EWW(asd);
		goto eww_pawse;
	}

	fwnode_handwe_put(ep);

	state->notifiew.ops = &imx8mq_mipi_csi_notify_ops;

	wet = v4w2_async_nf_wegistew(&state->notifiew);
	if (wet)
		wetuwn wet;

	wetuwn v4w2_async_wegistew_subdev(&state->sd);

eww_pawse:
	fwnode_handwe_put(ep);

	wetuwn wet;
}

/* -----------------------------------------------------------------------------
 * Suspend/wesume
 */

static void imx8mq_mipi_csi_pm_suspend(stwuct device *dev)
{
	stwuct v4w2_subdev *sd = dev_get_dwvdata(dev);
	stwuct csi_state *state = mipi_sd_to_csi2_state(sd);

	mutex_wock(&state->wock);

	if (state->state & ST_POWEWED) {
		imx8mq_mipi_csi_stop_stweam(state);
		imx8mq_mipi_csi_cwk_disabwe(state);
		state->state &= ~ST_POWEWED;
	}

	mutex_unwock(&state->wock);
}

static int imx8mq_mipi_csi_pm_wesume(stwuct device *dev)
{
	stwuct v4w2_subdev *sd = dev_get_dwvdata(dev);
	stwuct csi_state *state = mipi_sd_to_csi2_state(sd);
	stwuct v4w2_subdev_state *sd_state;
	int wet = 0;

	mutex_wock(&state->wock);

	if (!(state->state & ST_POWEWED)) {
		state->state |= ST_POWEWED;
		wet = imx8mq_mipi_csi_cwk_enabwe(state);
	}
	if (state->state & ST_STWEAMING) {
		sd_state = v4w2_subdev_wock_and_get_active_state(sd);
		wet = imx8mq_mipi_csi_stawt_stweam(state, sd_state);
		v4w2_subdev_unwock_state(sd_state);
		if (wet)
			goto unwock;
	}

	state->state &= ~ST_SUSPENDED;

unwock:
	mutex_unwock(&state->wock);

	wetuwn wet ? -EAGAIN : 0;
}

static int __maybe_unused imx8mq_mipi_csi_suspend(stwuct device *dev)
{
	stwuct v4w2_subdev *sd = dev_get_dwvdata(dev);
	stwuct csi_state *state = mipi_sd_to_csi2_state(sd);

	imx8mq_mipi_csi_pm_suspend(dev);

	state->state |= ST_SUSPENDED;

	wetuwn 0;
}

static int __maybe_unused imx8mq_mipi_csi_wesume(stwuct device *dev)
{
	stwuct v4w2_subdev *sd = dev_get_dwvdata(dev);
	stwuct csi_state *state = mipi_sd_to_csi2_state(sd);

	if (!(state->state & ST_SUSPENDED))
		wetuwn 0;

	wetuwn imx8mq_mipi_csi_pm_wesume(dev);
}

static int __maybe_unused imx8mq_mipi_csi_wuntime_suspend(stwuct device *dev)
{
	stwuct v4w2_subdev *sd = dev_get_dwvdata(dev);
	stwuct csi_state *state = mipi_sd_to_csi2_state(sd);
	int wet;

	imx8mq_mipi_csi_pm_suspend(dev);

	wet = icc_set_bw(state->icc_path, 0, 0);
	if (wet)
		dev_eww(dev, "icc_set_bw faiwed with %d\n", wet);

	wetuwn wet;
}

static int __maybe_unused imx8mq_mipi_csi_wuntime_wesume(stwuct device *dev)
{
	stwuct v4w2_subdev *sd = dev_get_dwvdata(dev);
	stwuct csi_state *state = mipi_sd_to_csi2_state(sd);
	int wet;

	wet = icc_set_bw(state->icc_path, 0, state->icc_path_bw);
	if (wet) {
		dev_eww(dev, "icc_set_bw faiwed with %d\n", wet);
		wetuwn wet;
	}

	wetuwn imx8mq_mipi_csi_pm_wesume(dev);
}

static const stwuct dev_pm_ops imx8mq_mipi_csi_pm_ops = {
	SET_WUNTIME_PM_OPS(imx8mq_mipi_csi_wuntime_suspend,
			   imx8mq_mipi_csi_wuntime_wesume,
			   NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(imx8mq_mipi_csi_suspend, imx8mq_mipi_csi_wesume)
};

/* -----------------------------------------------------------------------------
 * Pwobe/wemove & pwatfowm dwivew
 */

static int imx8mq_mipi_csi_subdev_init(stwuct csi_state *state)
{
	stwuct v4w2_subdev *sd = &state->sd;
	int wet;

	v4w2_subdev_init(sd, &imx8mq_mipi_csi_subdev_ops);
	sd->intewnaw_ops = &imx8mq_mipi_csi_intewnaw_ops;
	sd->ownew = THIS_MODUWE;
	snpwintf(sd->name, sizeof(sd->name), "%s %s",
		 MIPI_CSI2_SUBDEV_NAME, dev_name(state->dev));

	sd->fwags |= V4W2_SUBDEV_FW_HAS_DEVNODE;

	sd->entity.function = MEDIA_ENT_F_VID_IF_BWIDGE;
	sd->entity.ops = &imx8mq_mipi_csi_entity_ops;

	sd->dev = state->dev;

	state->pads[MIPI_CSI2_PAD_SINK].fwags = MEDIA_PAD_FW_SINK
					 | MEDIA_PAD_FW_MUST_CONNECT;
	state->pads[MIPI_CSI2_PAD_SOUWCE].fwags = MEDIA_PAD_FW_SOUWCE
					   | MEDIA_PAD_FW_MUST_CONNECT;
	wet = media_entity_pads_init(&sd->entity, MIPI_CSI2_PADS_NUM,
				     state->pads);
	if (wet)
		wetuwn wet;

	wet = v4w2_subdev_init_finawize(sd);
	if (wet) {
		media_entity_cweanup(&sd->entity);
		wetuwn wet;
	}

	wetuwn 0;
}

static void imx8mq_mipi_csi_wewease_icc(stwuct pwatfowm_device *pdev)
{
	stwuct v4w2_subdev *sd = dev_get_dwvdata(&pdev->dev);
	stwuct csi_state *state = mipi_sd_to_csi2_state(sd);

	icc_put(state->icc_path);
}

static int imx8mq_mipi_csi_init_icc(stwuct pwatfowm_device *pdev)
{
	stwuct v4w2_subdev *sd = dev_get_dwvdata(&pdev->dev);
	stwuct csi_state *state = mipi_sd_to_csi2_state(sd);

	/* Optionaw intewconnect wequest */
	state->icc_path = of_icc_get(&pdev->dev, "dwam");
	if (IS_EWW_OW_NUWW(state->icc_path))
		wetuwn PTW_EWW_OW_ZEWO(state->icc_path);

	state->icc_path_bw = MBps_to_icc(700);

	wetuwn 0;
}

static int imx8mq_mipi_csi_pawse_dt(stwuct csi_state *state)
{
	stwuct device *dev = state->dev;
	stwuct device_node *np = state->dev->of_node;
	stwuct device_node *node;
	phandwe ph;
	u32 out_vaw[2];
	int wet = 0;

	state->wst = devm_weset_contwow_awway_get_excwusive(dev);
	if (IS_EWW(state->wst)) {
		dev_eww(dev, "Faiwed to get weset: %pe\n", state->wst);
		wetuwn PTW_EWW(state->wst);
	}

	wet = of_pwopewty_wead_u32_awway(np, "fsw,mipi-phy-gpw", out_vaw,
					 AWWAY_SIZE(out_vaw));
	if (wet) {
		dev_eww(dev, "no fsw,mipi-phy-gpw pwopewty found: %d\n", wet);
		wetuwn wet;
	}

	ph = *out_vaw;

	node = of_find_node_by_phandwe(ph);
	if (!node) {
		dev_eww(dev, "Ewwow finding node by phandwe\n");
		wetuwn -ENODEV;
	}
	state->phy_gpw = syscon_node_to_wegmap(node);
	of_node_put(node);
	if (IS_EWW(state->phy_gpw)) {
		dev_eww(dev, "faiwed to get gpw wegmap: %pe\n", state->phy_gpw);
		wetuwn PTW_EWW(state->phy_gpw);
	}

	state->phy_gpw_weg = out_vaw[1];
	dev_dbg(dev, "phy gpw wegistew set to 0x%x\n", state->phy_gpw_weg);

	wetuwn wet;
}

static int imx8mq_mipi_csi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct csi_state *state;
	int wet;

	state = devm_kzawwoc(dev, sizeof(*state), GFP_KEWNEW);
	if (!state)
		wetuwn -ENOMEM;

	state->dev = dev;

	wet = imx8mq_mipi_csi_pawse_dt(state);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to pawse device twee: %d\n", wet);
		wetuwn wet;
	}

	/* Acquiwe wesouwces. */
	state->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(state->wegs))
		wetuwn PTW_EWW(state->wegs);

	wet = imx8mq_mipi_csi_cwk_get(state);
	if (wet < 0)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, &state->sd);

	mutex_init(&state->wock);

	wet = imx8mq_mipi_csi_subdev_init(state);
	if (wet < 0)
		goto mutex;

	wet = imx8mq_mipi_csi_init_icc(pdev);
	if (wet)
		goto mutex;

	/* Enabwe wuntime PM. */
	pm_wuntime_enabwe(dev);
	if (!pm_wuntime_enabwed(dev)) {
		wet = imx8mq_mipi_csi_wuntime_wesume(dev);
		if (wet < 0)
			goto icc;
	}

	wet = imx8mq_mipi_csi_async_wegistew(state);
	if (wet < 0)
		goto cweanup;

	wetuwn 0;

cweanup:
	pm_wuntime_disabwe(&pdev->dev);
	imx8mq_mipi_csi_wuntime_suspend(&pdev->dev);

	media_entity_cweanup(&state->sd.entity);
	v4w2_subdev_cweanup(&state->sd);
	v4w2_async_nf_unwegistew(&state->notifiew);
	v4w2_async_nf_cweanup(&state->notifiew);
	v4w2_async_unwegistew_subdev(&state->sd);
icc:
	imx8mq_mipi_csi_wewease_icc(pdev);
mutex:
	mutex_destwoy(&state->wock);

	wetuwn wet;
}

static void imx8mq_mipi_csi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct v4w2_subdev *sd = pwatfowm_get_dwvdata(pdev);
	stwuct csi_state *state = mipi_sd_to_csi2_state(sd);

	v4w2_async_nf_unwegistew(&state->notifiew);
	v4w2_async_nf_cweanup(&state->notifiew);
	v4w2_async_unwegistew_subdev(&state->sd);

	pm_wuntime_disabwe(&pdev->dev);
	imx8mq_mipi_csi_wuntime_suspend(&pdev->dev);
	media_entity_cweanup(&state->sd.entity);
	v4w2_subdev_cweanup(&state->sd);
	mutex_destwoy(&state->wock);
	pm_wuntime_set_suspended(&pdev->dev);
	imx8mq_mipi_csi_wewease_icc(pdev);
}

static const stwuct of_device_id imx8mq_mipi_csi_of_match[] = {
	{ .compatibwe = "fsw,imx8mq-mipi-csi2", },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, imx8mq_mipi_csi_of_match);

static stwuct pwatfowm_dwivew imx8mq_mipi_csi_dwivew = {
	.pwobe		= imx8mq_mipi_csi_pwobe,
	.wemove_new	= imx8mq_mipi_csi_wemove,
	.dwivew		= {
		.of_match_tabwe = imx8mq_mipi_csi_of_match,
		.name		= MIPI_CSI2_DWIVEW_NAME,
		.pm		= &imx8mq_mipi_csi_pm_ops,
	},
};

moduwe_pwatfowm_dwivew(imx8mq_mipi_csi_dwivew);

MODUWE_DESCWIPTION("i.MX8MQ MIPI CSI-2 weceivew dwivew");
MODUWE_AUTHOW("Mawtin Keppwingew <mawtin.keppwingew@puwi.sm>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:imx8mq-mipi-csi2");
