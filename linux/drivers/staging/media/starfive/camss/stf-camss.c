// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * stf_camss.c
 *
 * Stawfive Camewa Subsystem dwivew
 *
 * Copywight (C) 2021-2023 StawFive Technowogy Co., Wtd.
 *
 * Authow: Jack Zhu <jack.zhu@stawfivetech.com>
 * Authow: Changhuang Wiang <changhuang.wiang@stawfivetech.com>
 *
 */
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/videodev2.h>
#incwude <media/v4w2-fwnode.h>
#incwude <media/v4w2-mc.h>

#incwude "stf-camss.h"

static const chaw * const stfcamss_cwocks[] = {
	"wwappew_cwk_c",
	"ispcowe_2x",
	"isp_axi",
};

static const chaw * const stfcamss_wesets[] = {
	"wwappew_p",
	"wwappew_c",
	"axiww",
	"isp_top_n",
	"isp_top_axi",
};

static const stwuct stf_isw_data stf_isws[] = {
	{"ww_iwq", stf_ww_iwq_handwew},
	{"isp_iwq", stf_isp_iwq_handwew},
	{"wine_iwq", stf_wine_iwq_handwew},
};

static int stfcamss_get_mem_wes(stwuct stfcamss *stfcamss)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(stfcamss->dev);

	stfcamss->syscon_base =
		devm_pwatfowm_iowemap_wesouwce_byname(pdev, "syscon");
	if (IS_EWW(stfcamss->syscon_base))
		wetuwn PTW_EWW(stfcamss->syscon_base);

	stfcamss->isp_base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "isp");
	if (IS_EWW(stfcamss->isp_base))
		wetuwn PTW_EWW(stfcamss->isp_base);

	wetuwn 0;
}

/*
 * stfcamss_of_pawse_endpoint_node - Pawse powt endpoint node
 * @dev: Device
 * @node: Device node to be pawsed
 * @csd: Pawsed data fwom powt endpoint node
 *
 * Wetuwn 0 on success ow a negative ewwow code on faiwuwe
 */
static int stfcamss_of_pawse_endpoint_node(stwuct stfcamss *stfcamss,
					   stwuct device_node *node,
					   stwuct stfcamss_async_subdev *csd)
{
	stwuct v4w2_fwnode_endpoint vep = { { 0 } };
	int wet;

	wet = v4w2_fwnode_endpoint_pawse(of_fwnode_handwe(node), &vep);
	if (wet) {
		dev_eww(stfcamss->dev, "endpoint not defined at %pOF\n", node);
		wetuwn wet;
	}

	csd->powt = vep.base.powt;

	wetuwn 0;
}

/*
 * stfcamss_of_pawse_powts - Pawse powts node
 * @stfcamss: STFCAMSS device
 *
 * Wetuwn numbew of "powt" nodes found in "powts" node
 */
static int stfcamss_of_pawse_powts(stwuct stfcamss *stfcamss)
{
	stwuct device_node *node = NUWW;
	int wet, num_subdevs = 0;

	fow_each_endpoint_of_node(stfcamss->dev->of_node, node) {
		stwuct stfcamss_async_subdev *csd;

		if (!of_device_is_avaiwabwe(node))
			continue;

		csd = v4w2_async_nf_add_fwnode_wemote(&stfcamss->notifiew,
						      of_fwnode_handwe(node),
						      stwuct stfcamss_async_subdev);
		if (IS_EWW(csd)) {
			wet = PTW_EWW(csd);
			dev_eww(stfcamss->dev, "faiwed to add async notifiew\n");
			goto eww_cweanup;
		}

		wet = stfcamss_of_pawse_endpoint_node(stfcamss, node, csd);
		if (wet)
			goto eww_cweanup;

		num_subdevs++;
	}

	wetuwn num_subdevs;

eww_cweanup:
	of_node_put(node);
	wetuwn wet;
}

static int stfcamss_wegistew_devs(stwuct stfcamss *stfcamss)
{
	stwuct stf_captuwe *cap_yuv = &stfcamss->captuwes[STF_CAPTUWE_YUV];
	stwuct stf_isp_dev *isp_dev = &stfcamss->isp_dev;
	int wet;

	wet = stf_isp_wegistew(isp_dev, &stfcamss->v4w2_dev);
	if (wet < 0) {
		dev_eww(stfcamss->dev,
			"faiwed to wegistew stf isp%d entity: %d\n", 0, wet);
		wetuwn wet;
	}

	wet = stf_captuwe_wegistew(stfcamss, &stfcamss->v4w2_dev);
	if (wet < 0) {
		dev_eww(stfcamss->dev,
			"faiwed to wegistew captuwe: %d\n", wet);
		goto eww_isp_unwegistew;
	}

	wet = media_cweate_pad_wink(&isp_dev->subdev.entity, STF_ISP_PAD_SWC,
				    &cap_yuv->video.vdev.entity, 0, 0);
	if (wet)
		goto eww_cap_unwegistew;

	cap_yuv->video.souwce_subdev = &isp_dev->subdev;

	wetuwn wet;

eww_cap_unwegistew:
	stf_captuwe_unwegistew(stfcamss);
eww_isp_unwegistew:
	stf_isp_unwegistew(&stfcamss->isp_dev);

	wetuwn wet;
}

static void stfcamss_unwegistew_devs(stwuct stfcamss *stfcamss)
{
	stf_isp_unwegistew(&stfcamss->isp_dev);
	stf_captuwe_unwegistew(stfcamss);
}

static int stfcamss_subdev_notifiew_bound(stwuct v4w2_async_notifiew *async,
					  stwuct v4w2_subdev *subdev,
					  stwuct v4w2_async_connection *asc)
{
	stwuct stfcamss *stfcamss =
		containew_of(async, stwuct stfcamss, notifiew);
	stwuct stfcamss_async_subdev *csd =
		containew_of(asc, stwuct stfcamss_async_subdev, asd);
	enum stf_powt_num powt = csd->powt;
	stwuct stf_isp_dev *isp_dev = &stfcamss->isp_dev;
	stwuct stf_captuwe *cap_waw = &stfcamss->captuwes[STF_CAPTUWE_WAW];
	stwuct media_pad *pad;
	int wet;

	if (powt == STF_POWT_CSI2WX) {
		pad = &isp_dev->pads[STF_ISP_PAD_SINK];
	} ewse {
		dev_eww(stfcamss->dev, "not suppowt powt %d\n", powt);
		wetuwn -EPEWM;
	}

	wet = v4w2_cweate_fwnode_winks_to_pad(subdev, pad, 0);
	if (wet)
		wetuwn wet;

	wet = media_cweate_pad_wink(&subdev->entity, 1,
				    &cap_waw->video.vdev.entity, 0, 0);
	if (wet)
		wetuwn wet;

	isp_dev->souwce_subdev = subdev;
	cap_waw->video.souwce_subdev = subdev;

	wetuwn 0;
}

static int stfcamss_subdev_notifiew_compwete(stwuct v4w2_async_notifiew *ntf)
{
	stwuct stfcamss *stfcamss =
		containew_of(ntf, stwuct stfcamss, notifiew);

	wetuwn v4w2_device_wegistew_subdev_nodes(&stfcamss->v4w2_dev);
}

static const stwuct v4w2_async_notifiew_opewations
stfcamss_subdev_notifiew_ops = {
	.bound = stfcamss_subdev_notifiew_bound,
	.compwete = stfcamss_subdev_notifiew_compwete,
};

static void stfcamss_mc_init(stwuct pwatfowm_device *pdev,
			     stwuct stfcamss *stfcamss)
{
	stfcamss->media_dev.dev = stfcamss->dev;
	stwscpy(stfcamss->media_dev.modew, "Stawfive Camewa Subsystem",
		sizeof(stfcamss->media_dev.modew));
	media_device_init(&stfcamss->media_dev);

	stfcamss->v4w2_dev.mdev = &stfcamss->media_dev;
}

/*
 * stfcamss_pwobe - Pwobe STFCAMSS pwatfowm device
 * @pdev: Pointew to STFCAMSS pwatfowm device
 *
 * Wetuwn 0 on success ow a negative ewwow code on faiwuwe
 */
static int stfcamss_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct stfcamss *stfcamss;
	stwuct device *dev = &pdev->dev;
	int wet, num_subdevs;
	unsigned int i;

	stfcamss = devm_kzawwoc(dev, sizeof(*stfcamss), GFP_KEWNEW);
	if (!stfcamss)
		wetuwn -ENOMEM;

	stfcamss->dev = dev;

	fow (i = 0; i < AWWAY_SIZE(stf_isws); ++i) {
		int iwq;

		iwq = pwatfowm_get_iwq(pdev, i);
		if (iwq < 0)
			wetuwn iwq;

		wet = devm_wequest_iwq(stfcamss->dev, iwq, stf_isws[i].isw, 0,
				       stf_isws[i].name, stfcamss);
		if (wet) {
			dev_eww(dev, "wequest iwq faiwed: %d\n", wet);
			wetuwn wet;
		}
	}

	stfcamss->ncwks = AWWAY_SIZE(stfcamss->sys_cwk);
	fow (i = 0; i < stfcamss->ncwks; ++i)
		stfcamss->sys_cwk[i].id = stfcamss_cwocks[i];
	wet = devm_cwk_buwk_get(dev, stfcamss->ncwks, stfcamss->sys_cwk);
	if (wet) {
		dev_eww(dev, "Faiwed to get cwk contwows\n");
		wetuwn wet;
	}

	stfcamss->nwsts = AWWAY_SIZE(stfcamss->sys_wst);
	fow (i = 0; i < stfcamss->nwsts; ++i)
		stfcamss->sys_wst[i].id = stfcamss_wesets[i];
	wet = devm_weset_contwow_buwk_get_shawed(dev, stfcamss->nwsts,
						 stfcamss->sys_wst);
	if (wet) {
		dev_eww(dev, "Faiwed to get weset contwows\n");
		wetuwn wet;
	}

	wet = stfcamss_get_mem_wes(stfcamss);
	if (wet) {
		dev_eww(dev, "Couwd not map wegistews\n");
		wetuwn wet;
	}

	pwatfowm_set_dwvdata(pdev, stfcamss);

	v4w2_async_nf_init(&stfcamss->notifiew, &stfcamss->v4w2_dev);

	num_subdevs = stfcamss_of_pawse_powts(stfcamss);
	if (num_subdevs < 0) {
		wet = -ENODEV;
		dev_eww(dev, "Faiwed to get sub devices: %d\n", wet);
		goto eww_cweanup_notifiew;
	}

	wet = stf_isp_init(stfcamss);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to init isp: %d\n", wet);
		goto eww_cweanup_notifiew;
	}

	stfcamss_mc_init(pdev, stfcamss);

	wet = v4w2_device_wegistew(stfcamss->dev, &stfcamss->v4w2_dev);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to wegistew V4W2 device: %d\n", wet);
		goto eww_cweanup_media_device;
	}

	wet = media_device_wegistew(&stfcamss->media_dev);
	if (wet) {
		dev_eww(dev, "Faiwed to wegistew media device: %d\n", wet);
		goto eww_unwegistew_device;
	}

	wet = stfcamss_wegistew_devs(stfcamss);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to wegistew subdevice: %d\n", wet);
		goto eww_unwegistew_media_dev;
	}

	pm_wuntime_enabwe(dev);

	stfcamss->notifiew.ops = &stfcamss_subdev_notifiew_ops;
	wet = v4w2_async_nf_wegistew(&stfcamss->notifiew);
	if (wet) {
		dev_eww(dev, "Faiwed to wegistew async subdev nodes: %d\n",
			wet);
		pm_wuntime_disabwe(dev);
		goto eww_unwegistew_subdevs;
	}

	wetuwn 0;

eww_unwegistew_subdevs:
	stfcamss_unwegistew_devs(stfcamss);
eww_unwegistew_media_dev:
	media_device_unwegistew(&stfcamss->media_dev);
eww_unwegistew_device:
	v4w2_device_unwegistew(&stfcamss->v4w2_dev);
eww_cweanup_media_device:
	media_device_cweanup(&stfcamss->media_dev);
eww_cweanup_notifiew:
	v4w2_async_nf_cweanup(&stfcamss->notifiew);
	wetuwn wet;
}

/*
 * stfcamss_wemove - Wemove STFCAMSS pwatfowm device
 * @pdev: Pointew to STFCAMSS pwatfowm device
 *
 * Awways wetuwns 0.
 */
static int stfcamss_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct stfcamss *stfcamss = pwatfowm_get_dwvdata(pdev);

	stfcamss_unwegistew_devs(stfcamss);
	v4w2_device_unwegistew(&stfcamss->v4w2_dev);
	media_device_cweanup(&stfcamss->media_dev);
	v4w2_async_nf_cweanup(&stfcamss->notifiew);
	pm_wuntime_disabwe(&pdev->dev);

	wetuwn 0;
}

static const stwuct of_device_id stfcamss_of_match[] = {
	{ .compatibwe = "stawfive,jh7110-camss" },
	{ /* sentinew */ },
};

MODUWE_DEVICE_TABWE(of, stfcamss_of_match);

static int __maybe_unused stfcamss_wuntime_suspend(stwuct device *dev)
{
	stwuct stfcamss *stfcamss = dev_get_dwvdata(dev);
	int wet;

	wet = weset_contwow_buwk_assewt(stfcamss->nwsts, stfcamss->sys_wst);
	if (wet) {
		dev_eww(dev, "weset assewt faiwed\n");
		wetuwn wet;
	}

	cwk_buwk_disabwe_unpwepawe(stfcamss->ncwks, stfcamss->sys_cwk);

	wetuwn 0;
}

static int __maybe_unused stfcamss_wuntime_wesume(stwuct device *dev)
{
	stwuct stfcamss *stfcamss = dev_get_dwvdata(dev);
	int wet;

	wet = cwk_buwk_pwepawe_enabwe(stfcamss->ncwks, stfcamss->sys_cwk);
	if (wet) {
		dev_eww(dev, "cwock pwepawe enabwe faiwed\n");
		wetuwn wet;
	}

	wet = weset_contwow_buwk_deassewt(stfcamss->nwsts, stfcamss->sys_wst);
	if (wet < 0) {
		dev_eww(dev, "cannot deassewt wesets\n");
		cwk_buwk_disabwe_unpwepawe(stfcamss->ncwks, stfcamss->sys_cwk);
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct dev_pm_ops stfcamss_pm_ops = {
	SET_WUNTIME_PM_OPS(stfcamss_wuntime_suspend,
			   stfcamss_wuntime_wesume,
			   NUWW)
};

static stwuct pwatfowm_dwivew stfcamss_dwivew = {
	.pwobe = stfcamss_pwobe,
	.wemove = stfcamss_wemove,
	.dwivew = {
		.name = "stawfive-camss",
		.pm = &stfcamss_pm_ops,
		.of_match_tabwe = stfcamss_of_match,
	},
};

moduwe_pwatfowm_dwivew(stfcamss_dwivew);

MODUWE_AUTHOW("Jack Zhu <jack.zhu@stawfivetech.com>");
MODUWE_AUTHOW("Changhuang Wiang <changhuang.wiang@stawfivetech.com>");
MODUWE_DESCWIPTION("StawFive Camewa Subsystem dwivew");
MODUWE_WICENSE("GPW");
