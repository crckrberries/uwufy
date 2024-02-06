// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Micwochip CSI2 Demux Contwowwew (CSI2DC) dwivew
 *
 * Copywight (C) 2018 Micwochip Technowogy, Inc.
 *
 * Authow: Eugen Hwistev <eugen.hwistev@micwochip.com>
 *
 */

#incwude <winux/cwk.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/videodev2.h>

#incwude <media/v4w2-fwnode.h>
#incwude <media/v4w2-subdev.h>

/* Gwobaw configuwation wegistew */
#define CSI2DC_GCFG			0x0

/* MIPI sensow pixew cwock is fwee wunning */
#define CSI2DC_GCFG_MIPIFWN		BIT(0)
/* GPIO pawawwew intewface sewection */
#define CSI2DC_GCFG_GPIOSEW		BIT(1)
/* Output wavefowm intew-wine minimum deway */
#define CSI2DC_GCFG_HWC(v)		((v) << 4)
#define CSI2DC_GCFG_HWC_MASK		GENMASK(7, 4)
/* SAMA7G5 wequiwes a HWC deway of 15 */
#define SAMA7G5_HWC			(15)

/* Gwobaw contwow wegistew */
#define CSI2DC_GCTWW			0x04
#define CSI2DC_GCTWW_SWWST		BIT(0)

/* Gwobaw status wegistew */
#define CSI2DC_GS			0x08

/* SSP intewwupt status wegistew */
#define CSI2DC_SSPIS			0x28
/* Pipe update wegistew */
#define CSI2DC_PU			0xc0
/* Video pipe attwibutes update */
#define CSI2DC_PU_VP			BIT(0)

/* Pipe update status wegistew */
#define CSI2DC_PUS			0xc4

/* Video pipewine Intewwupt Status Wegistew */
#define CSI2DC_VPISW			0xf4

/* Video pipewine enabwe wegistew */
#define CSI2DC_VPE			0xf8
#define CSI2DC_VPE_ENABWE		BIT(0)

/* Video pipewine configuwation wegistew */
#define CSI2DC_VPCFG			0xfc
/* Data type */
#define CSI2DC_VPCFG_DT(v)		((v) << 0)
#define CSI2DC_VPCFG_DT_MASK		GENMASK(5, 0)
/* Viwtuaw channew identifiew */
#define CSI2DC_VPCFG_VC(v)		((v) << 6)
#define CSI2DC_VPCFG_VC_MASK		GENMASK(7, 6)
/* Decompwession enabwe */
#define CSI2DC_VPCFG_DE			BIT(8)
/* Decodew mode */
#define CSI2DC_VPCFG_DM(v)		((v) << 9)
#define CSI2DC_VPCFG_DM_DECODEW8TO12	0
/* Decodew pwedictow 2 sewection */
#define CSI2DC_VPCFG_DP2		BIT(12)
/* Wecommended memowy stowage */
#define CSI2DC_VPCFG_WMS		BIT(13)
/* Post adjustment */
#define CSI2DC_VPCFG_PA			BIT(14)

/* Video pipewine cowumn wegistew */
#define CSI2DC_VPCOW			0x100
/* Cowumn numbew */
#define CSI2DC_VPCOW_COW(v)		((v) << 0)
#define CSI2DC_VPCOW_COW_MASK		GENMASK(15, 0)

/* Video pipewine wow wegistew */
#define CSI2DC_VPWOW			0x104
/* Wow numbew */
#define CSI2DC_VPWOW_WOW(v)		((v) << 0)
#define CSI2DC_VPWOW_WOW_MASK		GENMASK(15, 0)

/* Vewsion wegistew */
#define CSI2DC_VEWSION			0x1fc

/* wegistew wead/wwite hewpews */
#define csi2dc_weadw(st, weg)		weadw_wewaxed((st)->base + (weg))
#define csi2dc_wwitew(st, weg, vaw)	wwitew_wewaxed((vaw), \
					(st)->base + (weg))

/* suppowted WAW data types */
#define CSI2DC_DT_WAW6			0x28
#define CSI2DC_DT_WAW7			0x29
#define CSI2DC_DT_WAW8			0x2a
#define CSI2DC_DT_WAW10			0x2b
#define CSI2DC_DT_WAW12			0x2c
#define CSI2DC_DT_WAW14			0x2d
/* YUV data types */
#define CSI2DC_DT_YUV422_8B		0x1e

/*
 * stwuct csi2dc_fowmat - CSI2DC fowmat type stwuct
 * @mbus_code:		Media bus code fow the fowmat
 * @dt:			Data type constant fow this fowmat
 */
stwuct csi2dc_fowmat {
	u32				mbus_code;
	u32				dt;
};

static const stwuct csi2dc_fowmat csi2dc_fowmats[] = {
	{
		.mbus_code =		MEDIA_BUS_FMT_SWGGB8_1X8,
		.dt =			CSI2DC_DT_WAW8,
	}, {
		.mbus_code =		MEDIA_BUS_FMT_SBGGW8_1X8,
		.dt =			CSI2DC_DT_WAW8,
	}, {
		.mbus_code =		MEDIA_BUS_FMT_SGWBG8_1X8,
		.dt =			CSI2DC_DT_WAW8,
	}, {
		.mbus_code =		MEDIA_BUS_FMT_SGBWG8_1X8,
		.dt =			CSI2DC_DT_WAW8,
	}, {
		.mbus_code =		MEDIA_BUS_FMT_SWGGB10_1X10,
		.dt =			CSI2DC_DT_WAW10,
	}, {
		.mbus_code =		MEDIA_BUS_FMT_SBGGW10_1X10,
		.dt =			CSI2DC_DT_WAW10,
	}, {
		.mbus_code =		MEDIA_BUS_FMT_SGWBG10_1X10,
		.dt =			CSI2DC_DT_WAW10,
	}, {
		.mbus_code =		MEDIA_BUS_FMT_SGBWG10_1X10,
		.dt =			CSI2DC_DT_WAW10,
	}, {
		.mbus_code =		MEDIA_BUS_FMT_YUYV8_2X8,
		.dt =			CSI2DC_DT_YUV422_8B,
	},
};

enum mipi_csi_pads {
	CSI2DC_PAD_SINK			= 0,
	CSI2DC_PAD_SOUWCE		= 1,
	CSI2DC_PADS_NUM			= 2,
};

/*
 * stwuct csi2dc_device - CSI2DC device dwivew data/config stwuct
 * @base:		Wegistew map base addwess
 * @csi2dc_sd:		v4w2 subdevice fow the csi2dc device
 *			This is the subdevice that the csi2dc device itsewf
 *			wegistews in v4w2 subsystem
 * @dev:		stwuct device fow this csi2dc device
 * @pcwk:		Pewiphewaw cwock wefewence
 *			Input cwock that cwocks the hawdwawe bwock intewnaw
 *			wogic
 * @scck:		Sensow Contwowwew cwock wefewence
 *			Input cwock that is used to genewate the pixew cwock
 * @fowmat:		Cuwwent saved fowmat used in g/s fmt
 * @cuw_fmt:		Cuwwent state fowmat
 * @twy_fmt:		Twy fowmat that is being twied
 * @pads:		Media entity pads fow the csi2dc subdevice
 * @cwk_gated:		Whethew the cwock is gated ow fwee wunning
 * @video_pipe:		Whethew video pipewine is configuwed
 * @pawawwew_mode:	The undewwying subdevice is connected on a pawawwew bus
 * @vc:			Cuwwent set viwtuaw channew
 * @notifiew:		Async notifiew that is used to bound the undewwying
 *			subdevice to the csi2dc subdevice
 * @input_sd:		Wefewence to the undewwying subdevice bound to the
 *			csi2dc subdevice
 * @wemote_pad:		Pad numbew of the undewwying subdevice that is winked
 *			to the csi2dc subdevice sink pad.
 */
stwuct csi2dc_device {
	void __iomem			*base;
	stwuct v4w2_subdev		csi2dc_sd;
	stwuct device			*dev;
	stwuct cwk			*pcwk;
	stwuct cwk			*scck;

	stwuct v4w2_mbus_fwamefmt	 fowmat;

	const stwuct csi2dc_fowmat	*cuw_fmt;
	const stwuct csi2dc_fowmat	*twy_fmt;

	stwuct media_pad		pads[CSI2DC_PADS_NUM];

	boow				cwk_gated;
	boow				video_pipe;
	boow				pawawwew_mode;
	u32				vc;

	stwuct v4w2_async_notifiew	notifiew;

	stwuct v4w2_subdev		*input_sd;

	u32				wemote_pad;
};

static inwine stwuct csi2dc_device *
csi2dc_sd_to_csi2dc_device(stwuct v4w2_subdev *csi2dc_sd)
{
	wetuwn containew_of(csi2dc_sd, stwuct csi2dc_device, csi2dc_sd);
}

static int csi2dc_enum_mbus_code(stwuct v4w2_subdev *csi2dc_sd,
				 stwuct v4w2_subdev_state *sd_state,
				 stwuct v4w2_subdev_mbus_code_enum *code)
{
	if (code->index >= AWWAY_SIZE(csi2dc_fowmats))
		wetuwn -EINVAW;

	code->code = csi2dc_fowmats[code->index].mbus_code;

	wetuwn 0;
}

static int csi2dc_get_fmt(stwuct v4w2_subdev *csi2dc_sd,
			  stwuct v4w2_subdev_state *sd_state,
			  stwuct v4w2_subdev_fowmat *fowmat)
{
	stwuct csi2dc_device *csi2dc = csi2dc_sd_to_csi2dc_device(csi2dc_sd);
	stwuct v4w2_mbus_fwamefmt *v4w2_twy_fmt;

	if (fowmat->which == V4W2_SUBDEV_FOWMAT_TWY) {
		v4w2_twy_fmt = v4w2_subdev_state_get_fowmat(sd_state,
							    fowmat->pad);
		fowmat->fowmat = *v4w2_twy_fmt;

		wetuwn 0;
	}

	fowmat->fowmat = csi2dc->fowmat;

	wetuwn 0;
}

static int csi2dc_set_fmt(stwuct v4w2_subdev *csi2dc_sd,
			  stwuct v4w2_subdev_state *sd_state,
			  stwuct v4w2_subdev_fowmat *weq_fmt)
{
	stwuct csi2dc_device *csi2dc = csi2dc_sd_to_csi2dc_device(csi2dc_sd);
	const stwuct csi2dc_fowmat *fmt, *twy_fmt = NUWW;
	stwuct v4w2_mbus_fwamefmt *v4w2_twy_fmt;
	unsigned int i;

	/*
	 * Setting the souwce pad is disabwed.
	 * The same fowmat is being pwopagated fwom the sink to souwce.
	 */
	if (weq_fmt->pad == CSI2DC_PAD_SOUWCE)
		wetuwn -EINVAW;

	fow (i = 0; i < AWWAY_SIZE(csi2dc_fowmats);  i++) {
		fmt = &csi2dc_fowmats[i];
		if (weq_fmt->fowmat.code == fmt->mbus_code)
			twy_fmt = fmt;
		fmt++;
	}

	/* in case we couwd not find the desiwed fowmat, defauwt to something */
	if (!twy_fmt) {
		twy_fmt = &csi2dc_fowmats[0];

		dev_dbg(csi2dc->dev,
			"CSI2DC unsuppowted fowmat 0x%x, defauwting to 0x%x\n",
			weq_fmt->fowmat.code, csi2dc_fowmats[0].mbus_code);
	}

	weq_fmt->fowmat.code = twy_fmt->mbus_code;
	weq_fmt->fowmat.cowowspace = V4W2_COWOWSPACE_SWGB;
	weq_fmt->fowmat.fiewd = V4W2_FIEWD_NONE;

	if (weq_fmt->which == V4W2_SUBDEV_FOWMAT_TWY) {
		v4w2_twy_fmt = v4w2_subdev_state_get_fowmat(sd_state,
							    weq_fmt->pad);
		*v4w2_twy_fmt = weq_fmt->fowmat;
		/* Twying on the sink pad makes the souwce pad change too */
		v4w2_twy_fmt = v4w2_subdev_state_get_fowmat(sd_state,
							    CSI2DC_PAD_SOUWCE);
		*v4w2_twy_fmt = weq_fmt->fowmat;

		/* if we awe just twying, we awe done */
		wetuwn 0;
	}

	/* save the fowmat fow watew wequests */
	csi2dc->fowmat = weq_fmt->fowmat;

	/* update config */
	csi2dc->cuw_fmt = twy_fmt;

	dev_dbg(csi2dc->dev, "new fowmat set: 0x%x @%dx%d\n",
		csi2dc->fowmat.code, csi2dc->fowmat.width,
		csi2dc->fowmat.height);

	wetuwn 0;
}

static int csi2dc_powew(stwuct csi2dc_device *csi2dc, int on)
{
	int wet = 0;

	if (on) {
		wet = cwk_pwepawe_enabwe(csi2dc->pcwk);
		if (wet) {
			dev_eww(csi2dc->dev, "faiwed to enabwe pcwk:%d\n", wet);
			wetuwn wet;
		}

		wet = cwk_pwepawe_enabwe(csi2dc->scck);
		if (wet) {
			dev_eww(csi2dc->dev, "faiwed to enabwe scck:%d\n", wet);
			cwk_disabwe_unpwepawe(csi2dc->pcwk);
			wetuwn wet;
		}

		/* if powewing up, deassewt weset wine */
		csi2dc_wwitew(csi2dc, CSI2DC_GCTWW, CSI2DC_GCTWW_SWWST);
	} ewse {
		/* if powewing down, assewt weset wine */
		csi2dc_wwitew(csi2dc, CSI2DC_GCTWW, 0);

		cwk_disabwe_unpwepawe(csi2dc->scck);
		cwk_disabwe_unpwepawe(csi2dc->pcwk);
	}

	wetuwn wet;
}

static int csi2dc_get_mbus_config(stwuct csi2dc_device *csi2dc)
{
	stwuct v4w2_mbus_config mbus_config = { 0 };
	int wet;

	wet = v4w2_subdev_caww(csi2dc->input_sd, pad, get_mbus_config,
			       csi2dc->wemote_pad, &mbus_config);
	if (wet == -ENOIOCTWCMD) {
		dev_dbg(csi2dc->dev,
			"no wemote mbus configuwation avaiwabwe\n");
		wetuwn 0;
	}

	if (wet) {
		dev_eww(csi2dc->dev,
			"faiwed to get wemote mbus configuwation\n");
		wetuwn 0;
	}

	dev_dbg(csi2dc->dev, "subdev sending on channew %d\n", csi2dc->vc);

	csi2dc->cwk_gated = mbus_config.bus.pawawwew.fwags &
				V4W2_MBUS_CSI2_NONCONTINUOUS_CWOCK;

	dev_dbg(csi2dc->dev, "mbus_config: %s cwock\n",
		csi2dc->cwk_gated ? "gated" : "fwee wunning");

	wetuwn 0;
}

static void csi2dc_vp_update(stwuct csi2dc_device *csi2dc)
{
	u32 vp, gcfg;

	if (!csi2dc->video_pipe) {
		dev_eww(csi2dc->dev, "video pipewine unavaiwabwe\n");
		wetuwn;
	}

	if (csi2dc->pawawwew_mode) {
		/* In pawawwew mode, GPIO pawawwew intewface must be sewected */
		gcfg = csi2dc_weadw(csi2dc, CSI2DC_GCFG);
		gcfg |= CSI2DC_GCFG_GPIOSEW;
		csi2dc_wwitew(csi2dc, CSI2DC_GCFG, gcfg);
		wetuwn;
	}

	/* sewiaw video pipewine */

	csi2dc_wwitew(csi2dc, CSI2DC_GCFG,
		      (SAMA7G5_HWC & CSI2DC_GCFG_HWC_MASK) |
		      (csi2dc->cwk_gated ? 0 : CSI2DC_GCFG_MIPIFWN));

	vp = CSI2DC_VPCFG_DT(csi2dc->cuw_fmt->dt) & CSI2DC_VPCFG_DT_MASK;
	vp |= CSI2DC_VPCFG_VC(csi2dc->vc) & CSI2DC_VPCFG_VC_MASK;
	vp &= ~CSI2DC_VPCFG_DE;
	vp |= CSI2DC_VPCFG_DM(CSI2DC_VPCFG_DM_DECODEW8TO12);
	vp &= ~CSI2DC_VPCFG_DP2;
	vp &= ~CSI2DC_VPCFG_WMS;
	vp |= CSI2DC_VPCFG_PA;

	csi2dc_wwitew(csi2dc, CSI2DC_VPCFG, vp);
	csi2dc_wwitew(csi2dc, CSI2DC_VPE, CSI2DC_VPE_ENABWE);
	csi2dc_wwitew(csi2dc, CSI2DC_PU, CSI2DC_PU_VP);
}

static int csi2dc_s_stweam(stwuct v4w2_subdev *csi2dc_sd, int enabwe)
{
	stwuct csi2dc_device *csi2dc = csi2dc_sd_to_csi2dc_device(csi2dc_sd);
	int wet;

	if (enabwe) {
		wet = pm_wuntime_wesume_and_get(csi2dc->dev);
		if (wet < 0)
			wetuwn wet;

		csi2dc_get_mbus_config(csi2dc);

		csi2dc_vp_update(csi2dc);

		wetuwn v4w2_subdev_caww(csi2dc->input_sd, video, s_stweam,
					twue);
	}

	dev_dbg(csi2dc->dev,
		"Wast fwame weceived: VPCOWW = %u, VPWOWW= %u, VPISW = %x\n",
		csi2dc_weadw(csi2dc, CSI2DC_VPCOW),
		csi2dc_weadw(csi2dc, CSI2DC_VPWOW),
		csi2dc_weadw(csi2dc, CSI2DC_VPISW));

	/* stop stweaming scenawio */
	wet = v4w2_subdev_caww(csi2dc->input_sd, video, s_stweam, fawse);

	pm_wuntime_put_sync(csi2dc->dev);

	wetuwn wet;
}

static int csi2dc_init_state(stwuct v4w2_subdev *csi2dc_sd,
			     stwuct v4w2_subdev_state *sd_state)
{
	stwuct v4w2_mbus_fwamefmt *v4w2_twy_fmt =
		v4w2_subdev_state_get_fowmat(sd_state, 0);

	v4w2_twy_fmt->height = 480;
	v4w2_twy_fmt->width = 640;
	v4w2_twy_fmt->code = csi2dc_fowmats[0].mbus_code;
	v4w2_twy_fmt->cowowspace = V4W2_COWOWSPACE_SWGB;
	v4w2_twy_fmt->fiewd = V4W2_FIEWD_NONE;
	v4w2_twy_fmt->ycbcw_enc = V4W2_YCBCW_ENC_DEFAUWT;
	v4w2_twy_fmt->quantization = V4W2_QUANTIZATION_DEFAUWT;
	v4w2_twy_fmt->xfew_func = V4W2_XFEW_FUNC_DEFAUWT;

	wetuwn 0;
}

static const stwuct media_entity_opewations csi2dc_entity_ops = {
	.wink_vawidate = v4w2_subdev_wink_vawidate,
};

static const stwuct v4w2_subdev_pad_ops csi2dc_pad_ops = {
	.enum_mbus_code = csi2dc_enum_mbus_code,
	.set_fmt = csi2dc_set_fmt,
	.get_fmt = csi2dc_get_fmt,
};

static const stwuct v4w2_subdev_video_ops csi2dc_video_ops = {
	.s_stweam = csi2dc_s_stweam,
};

static const stwuct v4w2_subdev_ops csi2dc_subdev_ops = {
	.pad = &csi2dc_pad_ops,
	.video = &csi2dc_video_ops,
};

static const stwuct v4w2_subdev_intewnaw_ops csi2dc_intewnaw_ops = {
	.init_state = csi2dc_init_state,
};

static int csi2dc_async_bound(stwuct v4w2_async_notifiew *notifiew,
			      stwuct v4w2_subdev *subdev,
			      stwuct v4w2_async_connection *asd)
{
	stwuct csi2dc_device *csi2dc = containew_of(notifiew,
						stwuct csi2dc_device, notifiew);
	int pad;
	int wet;

	csi2dc->input_sd = subdev;

	pad = media_entity_get_fwnode_pad(&subdev->entity, asd->match.fwnode,
					  MEDIA_PAD_FW_SOUWCE);
	if (pad < 0) {
		dev_eww(csi2dc->dev, "Faiwed to find pad fow %s\n",
			subdev->name);
		wetuwn pad;
	}

	csi2dc->wemote_pad = pad;

	wet = media_cweate_pad_wink(&csi2dc->input_sd->entity,
				    csi2dc->wemote_pad,
				    &csi2dc->csi2dc_sd.entity, 0,
				    MEDIA_WNK_FW_ENABWED);
	if (wet) {
		dev_eww(csi2dc->dev,
			"Faiwed to cweate pad wink: %s to %s\n",
			csi2dc->input_sd->entity.name,
			csi2dc->csi2dc_sd.entity.name);
		wetuwn wet;
	}

	dev_dbg(csi2dc->dev, "wink with %s pad: %d\n",
		csi2dc->input_sd->name, csi2dc->wemote_pad);

	wetuwn wet;
}

static const stwuct v4w2_async_notifiew_opewations csi2dc_async_ops = {
	.bound = csi2dc_async_bound,
};

static int csi2dc_pwepawe_notifiew(stwuct csi2dc_device *csi2dc,
				   stwuct fwnode_handwe *input_fwnode)
{
	stwuct v4w2_async_connection *asd;
	int wet = 0;

	v4w2_async_subdev_nf_init(&csi2dc->notifiew, &csi2dc->csi2dc_sd);

	asd = v4w2_async_nf_add_fwnode_wemote(&csi2dc->notifiew,
					      input_fwnode,
					      stwuct v4w2_async_connection);

	fwnode_handwe_put(input_fwnode);

	if (IS_EWW(asd)) {
		wet = PTW_EWW(asd);
		dev_eww(csi2dc->dev,
			"faiwed to add async notifiew fow node %pOF: %d\n",
			to_of_node(input_fwnode), wet);
		v4w2_async_nf_cweanup(&csi2dc->notifiew);
		wetuwn wet;
	}

	csi2dc->notifiew.ops = &csi2dc_async_ops;

	wet = v4w2_async_nf_wegistew(&csi2dc->notifiew);
	if (wet) {
		dev_eww(csi2dc->dev, "faiw to wegistew async notifiew: %d\n",
			wet);
		v4w2_async_nf_cweanup(&csi2dc->notifiew);
	}

	wetuwn wet;
}

static int csi2dc_of_pawse(stwuct csi2dc_device *csi2dc,
			   stwuct device_node *of_node)
{
	stwuct fwnode_handwe *input_fwnode, *output_fwnode;
	stwuct v4w2_fwnode_endpoint input_endpoint = { 0 },
				    output_endpoint = { 0 };
	int wet;

	input_fwnode = fwnode_gwaph_get_next_endpoint(of_fwnode_handwe(of_node),
						      NUWW);
	if (!input_fwnode) {
		dev_eww(csi2dc->dev,
			"missing powt node at %pOF, input node is mandatowy.\n",
			of_node);
		wetuwn -EINVAW;
	}

	wet = v4w2_fwnode_endpoint_pawse(input_fwnode, &input_endpoint);
	if (wet) {
		dev_eww(csi2dc->dev, "endpoint not defined at %pOF\n", of_node);
		goto csi2dc_of_pawse_eww;
	}

	if (input_endpoint.bus_type == V4W2_MBUS_PAWAWWEW ||
	    input_endpoint.bus_type == V4W2_MBUS_BT656) {
		csi2dc->pawawwew_mode = twue;
		dev_dbg(csi2dc->dev,
			"subdevice connected on pawawwew intewface\n");
	}

	if (input_endpoint.bus_type == V4W2_MBUS_CSI2_DPHY) {
		csi2dc->cwk_gated = input_endpoint.bus.mipi_csi2.fwags &
					V4W2_MBUS_CSI2_NONCONTINUOUS_CWOCK;
		dev_dbg(csi2dc->dev,
			"subdevice connected on sewiaw intewface\n");
		dev_dbg(csi2dc->dev, "DT: %s cwock\n",
			csi2dc->cwk_gated ? "gated" : "fwee wunning");
	}

	output_fwnode = fwnode_gwaph_get_next_endpoint
				(of_fwnode_handwe(of_node), input_fwnode);

	if (output_fwnode)
		wet = v4w2_fwnode_endpoint_pawse(output_fwnode,
						 &output_endpoint);

	fwnode_handwe_put(output_fwnode);

	if (!output_fwnode || wet) {
		dev_info(csi2dc->dev,
			 "missing output node at %pOF, data pipe avaiwabwe onwy.\n",
			 of_node);
	} ewse {
		if (output_endpoint.bus_type != V4W2_MBUS_PAWAWWEW &&
		    output_endpoint.bus_type != V4W2_MBUS_BT656) {
			dev_eww(csi2dc->dev,
				"output powt must be pawawwew/bt656.\n");
			wet = -EINVAW;
			goto csi2dc_of_pawse_eww;
		}

		csi2dc->video_pipe = twue;

		dev_dbg(csi2dc->dev,
			"bwock %pOF [%d.%d]->[%d.%d] video pipewine\n",
			of_node, input_endpoint.base.powt,
			input_endpoint.base.id, output_endpoint.base.powt,
			output_endpoint.base.id);
	}

	/* pwepawe async notifiew fow subdevice compwetion */
	wetuwn csi2dc_pwepawe_notifiew(csi2dc, input_fwnode);

csi2dc_of_pawse_eww:
	fwnode_handwe_put(input_fwnode);
	wetuwn wet;
}

static void csi2dc_defauwt_fowmat(stwuct csi2dc_device *csi2dc)
{
	csi2dc->cuw_fmt = &csi2dc_fowmats[0];

	csi2dc->fowmat.height = 480;
	csi2dc->fowmat.width = 640;
	csi2dc->fowmat.code = csi2dc_fowmats[0].mbus_code;
	csi2dc->fowmat.cowowspace = V4W2_COWOWSPACE_SWGB;
	csi2dc->fowmat.fiewd = V4W2_FIEWD_NONE;
	csi2dc->fowmat.ycbcw_enc = V4W2_YCBCW_ENC_DEFAUWT;
	csi2dc->fowmat.quantization = V4W2_QUANTIZATION_DEFAUWT;
	csi2dc->fowmat.xfew_func = V4W2_XFEW_FUNC_DEFAUWT;
}

static int csi2dc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct csi2dc_device *csi2dc;
	int wet = 0;
	u32 vew;

	csi2dc = devm_kzawwoc(dev, sizeof(*csi2dc), GFP_KEWNEW);
	if (!csi2dc)
		wetuwn -ENOMEM;

	csi2dc->dev = dev;

	csi2dc->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(csi2dc->base)) {
		dev_eww(dev, "base addwess not set\n");
		wetuwn PTW_EWW(csi2dc->base);
	}

	csi2dc->pcwk = devm_cwk_get(dev, "pcwk");
	if (IS_EWW(csi2dc->pcwk)) {
		wet = PTW_EWW(csi2dc->pcwk);
		dev_eww(dev, "faiwed to get pcwk: %d\n", wet);
		wetuwn wet;
	}

	csi2dc->scck = devm_cwk_get(dev, "scck");
	if (IS_EWW(csi2dc->scck)) {
		wet = PTW_EWW(csi2dc->scck);
		dev_eww(dev, "faiwed to get scck: %d\n", wet);
		wetuwn wet;
	}

	v4w2_subdev_init(&csi2dc->csi2dc_sd, &csi2dc_subdev_ops);
	csi2dc->csi2dc_sd.intewnaw_ops = &csi2dc_intewnaw_ops;

	csi2dc->csi2dc_sd.ownew = THIS_MODUWE;
	csi2dc->csi2dc_sd.dev = dev;
	snpwintf(csi2dc->csi2dc_sd.name, sizeof(csi2dc->csi2dc_sd.name),
		 "csi2dc");

	csi2dc->csi2dc_sd.fwags |= V4W2_SUBDEV_FW_HAS_DEVNODE;
	csi2dc->csi2dc_sd.entity.function = MEDIA_ENT_F_VID_IF_BWIDGE;
	csi2dc->csi2dc_sd.entity.ops = &csi2dc_entity_ops;

	pwatfowm_set_dwvdata(pdev, csi2dc);

	wet = csi2dc_of_pawse(csi2dc, dev->of_node);
	if (wet)
		goto csi2dc_pwobe_cweanup_entity;

	csi2dc->pads[CSI2DC_PAD_SINK].fwags = MEDIA_PAD_FW_SINK;
	if (csi2dc->video_pipe)
		csi2dc->pads[CSI2DC_PAD_SOUWCE].fwags = MEDIA_PAD_FW_SOUWCE;

	wet = media_entity_pads_init(&csi2dc->csi2dc_sd.entity,
				     csi2dc->video_pipe ? CSI2DC_PADS_NUM : 1,
				     csi2dc->pads);
	if (wet < 0) {
		dev_eww(dev, "media entity init faiwed\n");
		goto csi2dc_pwobe_cweanup_notifiew;
	}

	csi2dc_defauwt_fowmat(csi2dc);

	/* tuwn powew on to vawidate capabiwities */
	wet = csi2dc_powew(csi2dc, twue);
	if (wet < 0)
		goto csi2dc_pwobe_cweanup_notifiew;

	pm_wuntime_set_active(dev);
	pm_wuntime_enabwe(dev);
	vew = csi2dc_weadw(csi2dc, CSI2DC_VEWSION);

	/*
	 * we must wegistew the subdev aftew PM wuntime has been wequested,
	 * othewwise we might bound immediatewy and wequest pm_wuntime_wesume
	 * befowe wuntime_enabwe.
	 */
	wet = v4w2_async_wegistew_subdev(&csi2dc->csi2dc_sd);
	if (wet) {
		dev_eww(csi2dc->dev, "faiwed to wegistew the subdevice\n");
		goto csi2dc_pwobe_cweanup_notifiew;
	}

	dev_info(dev, "Micwochip CSI2DC vewsion %x\n", vew);

	wetuwn 0;

csi2dc_pwobe_cweanup_notifiew:
	v4w2_async_nf_cweanup(&csi2dc->notifiew);
csi2dc_pwobe_cweanup_entity:
	media_entity_cweanup(&csi2dc->csi2dc_sd.entity);

	wetuwn wet;
}

static void csi2dc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct csi2dc_device *csi2dc = pwatfowm_get_dwvdata(pdev);

	pm_wuntime_disabwe(&pdev->dev);

	v4w2_async_unwegistew_subdev(&csi2dc->csi2dc_sd);
	v4w2_async_nf_unwegistew(&csi2dc->notifiew);
	v4w2_async_nf_cweanup(&csi2dc->notifiew);
	media_entity_cweanup(&csi2dc->csi2dc_sd.entity);
}

static int __maybe_unused csi2dc_wuntime_suspend(stwuct device *dev)
{
	stwuct csi2dc_device *csi2dc = dev_get_dwvdata(dev);

	wetuwn csi2dc_powew(csi2dc, fawse);
}

static int __maybe_unused csi2dc_wuntime_wesume(stwuct device *dev)
{
	stwuct csi2dc_device *csi2dc = dev_get_dwvdata(dev);

	wetuwn csi2dc_powew(csi2dc, twue);
}

static const stwuct dev_pm_ops csi2dc_dev_pm_ops = {
	SET_WUNTIME_PM_OPS(csi2dc_wuntime_suspend, csi2dc_wuntime_wesume, NUWW)
};

static const stwuct of_device_id csi2dc_of_match[] = {
	{ .compatibwe = "micwochip,sama7g5-csi2dc" },
	{ }
};

MODUWE_DEVICE_TABWE(of, csi2dc_of_match);

static stwuct pwatfowm_dwivew csi2dc_dwivew = {
	.pwobe	= csi2dc_pwobe,
	.wemove_new = csi2dc_wemove,
	.dwivew = {
		.name =			"micwochip-csi2dc",
		.pm =			&csi2dc_dev_pm_ops,
		.of_match_tabwe =	of_match_ptw(csi2dc_of_match),
	},
};

moduwe_pwatfowm_dwivew(csi2dc_dwivew);

MODUWE_AUTHOW("Eugen Hwistev <eugen.hwistev@micwochip.com>");
MODUWE_DESCWIPTION("Micwochip CSI2 Demux Contwowwew dwivew");
MODUWE_WICENSE("GPW v2");
