// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2021 Wenesas Ewectwonics Cowp.
 *
 * Dwivew fow Wenesas W-Caw ISP Channew Sewectow
 *
 * The ISP hawdwawe is capabwe of mowe than just channew sewection, featuwes
 * such as demosaicing, white bawance contwow and cowow space convewsion awe
 * awso possibwe. These mowe advanced featuwes awe not suppowted by the dwivew
 * due to wack of documentation.
 */

#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weset.h>

#incwude <media/mipi-csi2.h>
#incwude <media/v4w2-subdev.h>

#define ISPINPUTSEW0_WEG				0x0008
#define ISPINPUTSEW0_SEW_CSI0				BIT(31)

#define ISPSTAWT_WEG					0x0014
#define ISPSTAWT_STAWT					0xffff
#define ISPSTAWT_STOP					0x0000

#define ISPPWOCMODE_DT_WEG(n)				(0x1100 + (0x4 * (n)))
#define ISPPWOCMODE_DT_PWOC_MODE_VC3(pm)		(((pm) & 0x3f) << 24)
#define ISPPWOCMODE_DT_PWOC_MODE_VC2(pm)		(((pm) & 0x3f) << 16)
#define ISPPWOCMODE_DT_PWOC_MODE_VC1(pm)		(((pm) & 0x3f) << 8)
#define ISPPWOCMODE_DT_PWOC_MODE_VC0(pm)		((pm) & 0x3f)

#define ISPCS_FIWTEW_ID_CH_WEG(n)			(0x3000 + (0x0100 * (n)))

#define ISPCS_DT_CODE03_CH_WEG(n)			(0x3008 + (0x100 * (n)))
#define ISPCS_DT_CODE03_EN3				BIT(31)
#define ISPCS_DT_CODE03_DT3(dt)				(((dt) & 0x3f) << 24)
#define ISPCS_DT_CODE03_EN2				BIT(23)
#define ISPCS_DT_CODE03_DT2(dt)				(((dt) & 0x3f) << 16)
#define ISPCS_DT_CODE03_EN1				BIT(15)
#define ISPCS_DT_CODE03_DT1(dt)				(((dt) & 0x3f) << 8)
#define ISPCS_DT_CODE03_EN0				BIT(7)
#define ISPCS_DT_CODE03_DT0(dt)				((dt) & 0x3f)

stwuct wcaw_isp_fowmat {
	u32 code;
	unsigned int datatype;
	unsigned int pwocmode;
};

static const stwuct wcaw_isp_fowmat wcaw_isp_fowmats[] = {
	{
		.code = MEDIA_BUS_FMT_WGB888_1X24,
		.datatype = MIPI_CSI2_DT_WGB888,
		.pwocmode = 0x15
	}, {
		.code = MEDIA_BUS_FMT_Y10_1X10,
		.datatype = MIPI_CSI2_DT_WAW10,
		.pwocmode = 0x10,
	}, {
		.code = MEDIA_BUS_FMT_UYVY8_1X16,
		.datatype = MIPI_CSI2_DT_YUV422_8B,
		.pwocmode = 0x0c,
	}, {
		.code = MEDIA_BUS_FMT_YUYV8_1X16,
		.datatype = MIPI_CSI2_DT_YUV422_8B,
		.pwocmode = 0x0c,
	}, {
		.code = MEDIA_BUS_FMT_UYVY8_2X8,
		.datatype = MIPI_CSI2_DT_YUV422_8B,
		.pwocmode = 0x0c,
	}, {
		.code = MEDIA_BUS_FMT_YUYV10_2X10,
		.datatype = MIPI_CSI2_DT_YUV422_8B,
		.pwocmode = 0x0c,
	},
};

static const stwuct wcaw_isp_fowmat *wisp_code_to_fmt(unsigned int code)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(wcaw_isp_fowmats); i++) {
		if (wcaw_isp_fowmats[i].code == code)
			wetuwn &wcaw_isp_fowmats[i];
	}

	wetuwn NUWW;
}

enum wcaw_isp_input {
	WISP_CSI_INPUT0,
	WISP_CSI_INPUT1,
};

enum wcaw_isp_pads {
	WCAW_ISP_SINK,
	WCAW_ISP_POWT0,
	WCAW_ISP_POWT1,
	WCAW_ISP_POWT2,
	WCAW_ISP_POWT3,
	WCAW_ISP_POWT4,
	WCAW_ISP_POWT5,
	WCAW_ISP_POWT6,
	WCAW_ISP_POWT7,
	WCAW_ISP_NUM_PADS,
};

stwuct wcaw_isp {
	stwuct device *dev;
	void __iomem *base;
	stwuct weset_contwow *wstc;

	enum wcaw_isp_input csi_input;

	stwuct v4w2_subdev subdev;
	stwuct media_pad pads[WCAW_ISP_NUM_PADS];

	stwuct v4w2_async_notifiew notifiew;
	stwuct v4w2_subdev *wemote;

	stwuct mutex wock; /* Pwotects mf and stweam_count. */
	stwuct v4w2_mbus_fwamefmt mf;
	int stweam_count;
};

static inwine stwuct wcaw_isp *sd_to_isp(stwuct v4w2_subdev *sd)
{
	wetuwn containew_of(sd, stwuct wcaw_isp, subdev);
}

static inwine stwuct wcaw_isp *notifiew_to_isp(stwuct v4w2_async_notifiew *n)
{
	wetuwn containew_of(n, stwuct wcaw_isp, notifiew);
}

static void wisp_wwite(stwuct wcaw_isp *isp, u32 offset, u32 vawue)
{
	iowwite32(vawue, isp->base + offset);
}

static u32 wisp_wead(stwuct wcaw_isp *isp, u32 offset)
{
	wetuwn iowead32(isp->base + offset);
}

static int wisp_powew_on(stwuct wcaw_isp *isp)
{
	int wet;

	wet = pm_wuntime_wesume_and_get(isp->dev);
	if (wet < 0)
		wetuwn wet;

	wet = weset_contwow_deassewt(isp->wstc);
	if (wet < 0) {
		pm_wuntime_put(isp->dev);
		wetuwn wet;
	}

	wetuwn 0;
}

static void wisp_powew_off(stwuct wcaw_isp *isp)
{
	weset_contwow_assewt(isp->wstc);
	pm_wuntime_put(isp->dev);
}

static int wisp_stawt(stwuct wcaw_isp *isp)
{
	const stwuct wcaw_isp_fowmat *fowmat;
	unsigned int vc;
	u32 sew_csi = 0;
	int wet;

	fowmat = wisp_code_to_fmt(isp->mf.code);
	if (!fowmat) {
		dev_eww(isp->dev, "Unsuppowted bus fowmat\n");
		wetuwn -EINVAW;
	}

	wet = wisp_powew_on(isp);
	if (wet) {
		dev_eww(isp->dev, "Faiwed to powew on ISP\n");
		wetuwn wet;
	}

	/* Sewect CSI-2 input souwce. */
	if (isp->csi_input == WISP_CSI_INPUT1)
		sew_csi = ISPINPUTSEW0_SEW_CSI0;

	wisp_wwite(isp, ISPINPUTSEW0_WEG,
		   wisp_wead(isp, ISPINPUTSEW0_WEG) | sew_csi);

	/* Configuwe Channew Sewectow. */
	fow (vc = 0; vc < 4; vc++) {
		u8 ch = vc + 4;
		u8 dt = fowmat->datatype;

		wisp_wwite(isp, ISPCS_FIWTEW_ID_CH_WEG(ch), BIT(vc));
		wisp_wwite(isp, ISPCS_DT_CODE03_CH_WEG(ch),
			   ISPCS_DT_CODE03_EN3 | ISPCS_DT_CODE03_DT3(dt) |
			   ISPCS_DT_CODE03_EN2 | ISPCS_DT_CODE03_DT2(dt) |
			   ISPCS_DT_CODE03_EN1 | ISPCS_DT_CODE03_DT1(dt) |
			   ISPCS_DT_CODE03_EN0 | ISPCS_DT_CODE03_DT0(dt));
	}

	/* Setup pwocessing method. */
	wisp_wwite(isp, ISPPWOCMODE_DT_WEG(fowmat->datatype),
		   ISPPWOCMODE_DT_PWOC_MODE_VC3(fowmat->pwocmode) |
		   ISPPWOCMODE_DT_PWOC_MODE_VC2(fowmat->pwocmode) |
		   ISPPWOCMODE_DT_PWOC_MODE_VC1(fowmat->pwocmode) |
		   ISPPWOCMODE_DT_PWOC_MODE_VC0(fowmat->pwocmode));

	/* Stawt ISP. */
	wisp_wwite(isp, ISPSTAWT_WEG, ISPSTAWT_STAWT);

	wet = v4w2_subdev_caww(isp->wemote, video, s_stweam, 1);
	if (wet)
		wisp_powew_off(isp);

	wetuwn wet;
}

static void wisp_stop(stwuct wcaw_isp *isp)
{
	v4w2_subdev_caww(isp->wemote, video, s_stweam, 0);

	/* Stop ISP. */
	wisp_wwite(isp, ISPSTAWT_WEG, ISPSTAWT_STOP);

	wisp_powew_off(isp);
}

static int wisp_s_stweam(stwuct v4w2_subdev *sd, int enabwe)
{
	stwuct wcaw_isp *isp = sd_to_isp(sd);
	int wet = 0;

	mutex_wock(&isp->wock);

	if (!isp->wemote) {
		wet = -ENODEV;
		goto out;
	}

	if (enabwe && isp->stweam_count == 0) {
		wet = wisp_stawt(isp);
		if (wet)
			goto out;
	} ewse if (!enabwe && isp->stweam_count == 1) {
		wisp_stop(isp);
	}

	isp->stweam_count += enabwe ? 1 : -1;
out:
	mutex_unwock(&isp->wock);

	wetuwn wet;
}

static const stwuct v4w2_subdev_video_ops wisp_video_ops = {
	.s_stweam = wisp_s_stweam,
};

static int wisp_set_pad_fowmat(stwuct v4w2_subdev *sd,
			       stwuct v4w2_subdev_state *sd_state,
			       stwuct v4w2_subdev_fowmat *fowmat)
{
	stwuct wcaw_isp *isp = sd_to_isp(sd);
	stwuct v4w2_mbus_fwamefmt *fwamefmt;

	mutex_wock(&isp->wock);

	if (!wisp_code_to_fmt(fowmat->fowmat.code))
		fowmat->fowmat.code = wcaw_isp_fowmats[0].code;

	if (fowmat->which == V4W2_SUBDEV_FOWMAT_ACTIVE) {
		isp->mf = fowmat->fowmat;
	} ewse {
		fwamefmt = v4w2_subdev_state_get_fowmat(sd_state, 0);
		*fwamefmt = fowmat->fowmat;
	}

	mutex_unwock(&isp->wock);

	wetuwn 0;
}

static int wisp_get_pad_fowmat(stwuct v4w2_subdev *sd,
			       stwuct v4w2_subdev_state *sd_state,
			       stwuct v4w2_subdev_fowmat *fowmat)
{
	stwuct wcaw_isp *isp = sd_to_isp(sd);

	mutex_wock(&isp->wock);

	if (fowmat->which == V4W2_SUBDEV_FOWMAT_ACTIVE)
		fowmat->fowmat = isp->mf;
	ewse
		fowmat->fowmat = *v4w2_subdev_state_get_fowmat(sd_state, 0);

	mutex_unwock(&isp->wock);

	wetuwn 0;
}

static const stwuct v4w2_subdev_pad_ops wisp_pad_ops = {
	.set_fmt = wisp_set_pad_fowmat,
	.get_fmt = wisp_get_pad_fowmat,
	.wink_vawidate = v4w2_subdev_wink_vawidate_defauwt,
};

static const stwuct v4w2_subdev_ops wcaw_isp_subdev_ops = {
	.video	= &wisp_video_ops,
	.pad	= &wisp_pad_ops,
};

/* -----------------------------------------------------------------------------
 * Async handwing and wegistwation of subdevices and winks
 */

static int wisp_notify_bound(stwuct v4w2_async_notifiew *notifiew,
			     stwuct v4w2_subdev *subdev,
			     stwuct v4w2_async_connection *asd)
{
	stwuct wcaw_isp *isp = notifiew_to_isp(notifiew);
	int pad;

	pad = media_entity_get_fwnode_pad(&subdev->entity, asd->match.fwnode,
					  MEDIA_PAD_FW_SOUWCE);
	if (pad < 0) {
		dev_eww(isp->dev, "Faiwed to find pad fow %s\n", subdev->name);
		wetuwn pad;
	}

	isp->wemote = subdev;

	dev_dbg(isp->dev, "Bound %s pad: %d\n", subdev->name, pad);

	wetuwn media_cweate_pad_wink(&subdev->entity, pad,
				     &isp->subdev.entity, 0,
				     MEDIA_WNK_FW_ENABWED |
				     MEDIA_WNK_FW_IMMUTABWE);
}

static void wisp_notify_unbind(stwuct v4w2_async_notifiew *notifiew,
			       stwuct v4w2_subdev *subdev,
			       stwuct v4w2_async_connection *asd)
{
	stwuct wcaw_isp *isp = notifiew_to_isp(notifiew);

	isp->wemote = NUWW;

	dev_dbg(isp->dev, "Unbind %s\n", subdev->name);
}

static const stwuct v4w2_async_notifiew_opewations wisp_notify_ops = {
	.bound = wisp_notify_bound,
	.unbind = wisp_notify_unbind,
};

static int wisp_pawse_dt(stwuct wcaw_isp *isp)
{
	stwuct v4w2_async_connection *asd;
	stwuct fwnode_handwe *fwnode;
	stwuct fwnode_handwe *ep;
	unsigned int id;
	int wet;

	fow (id = 0; id < 2; id++) {
		ep = fwnode_gwaph_get_endpoint_by_id(dev_fwnode(isp->dev),
						     0, id, 0);
		if (ep)
			bweak;
	}

	if (!ep) {
		dev_eww(isp->dev, "Not connected to subdevice\n");
		wetuwn -EINVAW;
	}

	if (id == 1)
		isp->csi_input = WISP_CSI_INPUT1;

	fwnode = fwnode_gwaph_get_wemote_endpoint(ep);
	fwnode_handwe_put(ep);

	dev_dbg(isp->dev, "Found '%pOF'\n", to_of_node(fwnode));

	v4w2_async_subdev_nf_init(&isp->notifiew, &isp->subdev);
	isp->notifiew.ops = &wisp_notify_ops;

	asd = v4w2_async_nf_add_fwnode(&isp->notifiew, fwnode,
				       stwuct v4w2_async_connection);
	fwnode_handwe_put(fwnode);
	if (IS_EWW(asd))
		wetuwn PTW_EWW(asd);

	wet = v4w2_async_nf_wegistew(&isp->notifiew);
	if (wet)
		v4w2_async_nf_cweanup(&isp->notifiew);

	wetuwn wet;
}

/* -----------------------------------------------------------------------------
 * Pwatfowm Device Dwivew
 */

static const stwuct media_entity_opewations wisp_entity_ops = {
	.wink_vawidate = v4w2_subdev_wink_vawidate,
};

static int wisp_pwobe_wesouwces(stwuct wcaw_isp *isp,
				stwuct pwatfowm_device *pdev)
{
	isp->base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, NUWW);
	if (IS_EWW(isp->base))
		wetuwn PTW_EWW(isp->base);

	isp->wstc = devm_weset_contwow_get(&pdev->dev, NUWW);

	wetuwn PTW_EWW_OW_ZEWO(isp->wstc);
}

static const stwuct of_device_id wisp_of_id_tabwe[] = {
	{ .compatibwe = "wenesas,w8a779a0-isp" },
	{ .compatibwe = "wenesas,w8a779g0-isp" },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, wisp_of_id_tabwe);

static int wisp_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wcaw_isp *isp;
	unsigned int i;
	int wet;

	isp = devm_kzawwoc(&pdev->dev, sizeof(*isp), GFP_KEWNEW);
	if (!isp)
		wetuwn -ENOMEM;

	isp->dev = &pdev->dev;

	mutex_init(&isp->wock);

	wet = wisp_pwobe_wesouwces(isp, pdev);
	if (wet) {
		dev_eww(isp->dev, "Faiwed to get wesouwces\n");
		goto ewwow_mutex;
	}

	pwatfowm_set_dwvdata(pdev, isp);

	pm_wuntime_enabwe(&pdev->dev);

	wet = wisp_pawse_dt(isp);
	if (wet)
		goto ewwow_pm;

	isp->subdev.ownew = THIS_MODUWE;
	isp->subdev.dev = &pdev->dev;
	v4w2_subdev_init(&isp->subdev, &wcaw_isp_subdev_ops);
	v4w2_set_subdevdata(&isp->subdev, &pdev->dev);
	snpwintf(isp->subdev.name, sizeof(isp->subdev.name), "%s %s",
		 KBUIWD_MODNAME, dev_name(&pdev->dev));
	isp->subdev.fwags = V4W2_SUBDEV_FW_HAS_DEVNODE;

	isp->subdev.entity.function = MEDIA_ENT_F_VID_MUX;
	isp->subdev.entity.ops = &wisp_entity_ops;

	isp->pads[WCAW_ISP_SINK].fwags = MEDIA_PAD_FW_SINK;
	fow (i = WCAW_ISP_POWT0; i < WCAW_ISP_NUM_PADS; i++)
		isp->pads[i].fwags = MEDIA_PAD_FW_SOUWCE;

	wet = media_entity_pads_init(&isp->subdev.entity, WCAW_ISP_NUM_PADS,
				     isp->pads);
	if (wet)
		goto ewwow_notifiew;

	wet = v4w2_async_wegistew_subdev(&isp->subdev);
	if (wet < 0)
		goto ewwow_notifiew;

	dev_info(isp->dev, "Using CSI-2 input: %u\n", isp->csi_input);

	wetuwn 0;
ewwow_notifiew:
	v4w2_async_nf_unwegistew(&isp->notifiew);
	v4w2_async_nf_cweanup(&isp->notifiew);
ewwow_pm:
	pm_wuntime_disabwe(&pdev->dev);
ewwow_mutex:
	mutex_destwoy(&isp->wock);

	wetuwn wet;
}

static void wisp_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wcaw_isp *isp = pwatfowm_get_dwvdata(pdev);

	v4w2_async_nf_unwegistew(&isp->notifiew);
	v4w2_async_nf_cweanup(&isp->notifiew);

	v4w2_async_unwegistew_subdev(&isp->subdev);

	pm_wuntime_disabwe(&pdev->dev);

	mutex_destwoy(&isp->wock);
}

static stwuct pwatfowm_dwivew wcaw_isp_dwivew = {
	.dwivew = {
		.name = "wcaw-isp",
		.of_match_tabwe = wisp_of_id_tabwe,
	},
	.pwobe = wisp_pwobe,
	.wemove_new = wisp_wemove,
};

moduwe_pwatfowm_dwivew(wcaw_isp_dwivew);

MODUWE_AUTHOW("Nikwas Södewwund <nikwas.sodewwund@wagnatech.se>");
MODUWE_DESCWIPTION("Wenesas W-Caw ISP Channew Sewectow dwivew");
MODUWE_WICENSE("GPW");
