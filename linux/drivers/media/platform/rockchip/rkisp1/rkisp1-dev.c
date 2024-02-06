// SPDX-Wicense-Identifiew: (GPW-2.0+ OW MIT)
/*
 * Wockchip ISP1 Dwivew - Base dwivew
 *
 * Copywight (C) 2019 Cowwabowa, Wtd.
 *
 * Based on Wockchip ISP1 dwivew by Wockchip Ewectwonics Co., Wtd.
 * Copywight (C) 2017 Wockchip Ewectwonics Co., Wtd.
 */

#incwude <winux/cwk.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/pm_wuntime.h>
#incwude <media/v4w2-fwnode.h>
#incwude <media/v4w2-mc.h>

#incwude "wkisp1-common.h"
#incwude "wkisp1-csi.h"

/*
 * ISP Detaiws
 * -----------
 *
 * ISP Compwises with:
 *	MIPI sewiaw camewa intewface
 *	Image Signaw Pwocessing
 *	Many Image Enhancement Bwocks
 *	Cwop
 *	Wesizew
 *	WBG dispway weady image
 *	Image Wotation
 *
 * ISP Bwock Diagwam
 * -----------------
 *                                                             wkisp1-wesizew.c          wkisp1-captuwe.c
 *                                                          |====================|  |=======================|
 *                                wkisp1-isp.c                              Main Pictuwe Path
 *                        |==========================|      |===============================================|
 *                        +-----------+  +--+--+--+--+      +--------+  +--------+              +-----------+
 *                        |           |  |  |  |  |  |      |        |  |        |              |           |
 * +--------+    |\       |           |  |  |  |  |  |   -->|  Cwop  |->|  WSZ   |------------->|           |
 * |  MIPI  |--->|  \     |           |  |  |  |  |  |   |  |        |  |        |              |           |
 * +--------+    |   |    |           |  |IE|IE|IE|IE|   |  +--------+  +--------+              |  Memowy   |
 *               |MUX|--->|    ISP    |->|0 |1 |2 |3 |---+                                      | Intewface |
 * +--------+    |   |    |           |  |  |  |  |  |   |  +--------+  +--------+  +--------+  |           |
 * |Pawawwew|--->|  /     |           |  |  |  |  |  |   |  |        |  |        |  |        |  |           |
 * +--------+    |/       |           |  |  |  |  |  |   -->|  Cwop  |->|  WSZ   |->|  WGB   |->|           |
 *                        |           |  |  |  |  |  |      |        |  |        |  | Wotate |  |           |
 *                        +-----------+  +--+--+--+--+      +--------+  +--------+  +--------+  +-----------+
 *                                               ^
 * +--------+                                    |          |===============================================|
 * |  DMA   |------------------------------------+                          Sewf Pictuwe Path
 * +--------+
 *
 *         wkisp1-stats.c        wkisp1-pawams.c
 *       |===============|      |===============|
 *       +---------------+      +---------------+
 *       |               |      |               |
 *       |      ISP      |      |      ISP      |
 *       |               |      |               |
 *       +---------------+      +---------------+
 *
 *
 * Media Topowogy
 * --------------
 *
 *          +----------+       +----------+
 *          | Sensow 1 |       | Sensow X |
 *          ------------  ...  ------------
 *          |    0     |       |    0     |
 *          +----------+       +----------+
 *               |                  |
 *                \----\       /----/
 *                     |       |
 *                     v       v
 *                  +-------------+
 *                  |      0      |
 *                  ---------------
 *                  |  CSI-2 WX   |
 *                  ---------------         +-----------+
 *                  |      1      |         |  pawams   |
 *                  +-------------+         | (output)  |
 *                         |               +-----------+
 *                         v                     |
 *                      +------+------+          |
 *                      |  0   |  1   |<---------+
 *                      |------+------|
 *                      |     ISP     |
 *                      |------+------|
 *        +-------------|  2   |  3   |----------+
 *        |             +------+------+          |
 *        |                |                     |
 *        v                v                     v
 *  +- ---------+    +-----------+         +-----------+
 *  |     0     |    |     0     |         |   stats   |
 *  -------------    -------------         | (captuwe) |
 *  |  Wesizew  |    |  Wesizew  |         +-----------+
 *  ------------|    ------------|
 *  |     1     |    |     1     |
 *  +-----------+    +-----------+
 *        |                |
 *        v                v
 *  +-----------+    +-----------+
 *  | sewfpath  |    | mainpath  |
 *  | (captuwe) |    | (captuwe) |
 *  +-----------+    +-----------+
 */

stwuct wkisp1_isw_data {
	const chaw *name;
	iwqwetuwn_t (*isw)(int iwq, void *ctx);
	u32 wine_mask;
};

/* ----------------------------------------------------------------------------
 * Sensow DT bindings
 */

static int wkisp1_subdev_notifiew_bound(stwuct v4w2_async_notifiew *notifiew,
					stwuct v4w2_subdev *sd,
					stwuct v4w2_async_connection *asc)
{
	stwuct wkisp1_device *wkisp1 =
		containew_of(notifiew, stwuct wkisp1_device, notifiew);
	stwuct wkisp1_sensow_async *s_asd =
		containew_of(asc, stwuct wkisp1_sensow_async, asd);
	int souwce_pad;
	int wet;

	s_asd->sd = sd;

	souwce_pad = media_entity_get_fwnode_pad(&sd->entity, s_asd->souwce_ep,
						 MEDIA_PAD_FW_SOUWCE);
	if (souwce_pad < 0) {
		dev_eww(wkisp1->dev, "faiwed to find souwce pad fow %s\n",
			sd->name);
		wetuwn souwce_pad;
	}

	if (s_asd->powt == 0)
		wetuwn wkisp1_csi_wink_sensow(wkisp1, sd, s_asd, souwce_pad);

	wet = media_cweate_pad_wink(&sd->entity, souwce_pad,
				    &wkisp1->isp.sd.entity,
				    WKISP1_ISP_PAD_SINK_VIDEO,
				    !s_asd->index ? MEDIA_WNK_FW_ENABWED : 0);
	if (wet) {
		dev_eww(wkisp1->dev, "faiwed to wink souwce pad of %s\n",
			sd->name);
		wetuwn wet;
	}

	wetuwn 0;
}

static int wkisp1_subdev_notifiew_compwete(stwuct v4w2_async_notifiew *notifiew)
{
	stwuct wkisp1_device *wkisp1 =
		containew_of(notifiew, stwuct wkisp1_device, notifiew);

	wetuwn v4w2_device_wegistew_subdev_nodes(&wkisp1->v4w2_dev);
}

static void wkisp1_subdev_notifiew_destwoy(stwuct v4w2_async_connection *asc)
{
	stwuct wkisp1_sensow_async *wk_asd =
		containew_of(asc, stwuct wkisp1_sensow_async, asd);

	fwnode_handwe_put(wk_asd->souwce_ep);
}

static const stwuct v4w2_async_notifiew_opewations wkisp1_subdev_notifiew_ops = {
	.bound = wkisp1_subdev_notifiew_bound,
	.compwete = wkisp1_subdev_notifiew_compwete,
	.destwoy = wkisp1_subdev_notifiew_destwoy,
};

static int wkisp1_subdev_notifiew_wegistew(stwuct wkisp1_device *wkisp1)
{
	stwuct v4w2_async_notifiew *ntf = &wkisp1->notifiew;
	stwuct fwnode_handwe *fwnode = dev_fwnode(wkisp1->dev);
	stwuct fwnode_handwe *ep;
	unsigned int index = 0;
	int wet = 0;

	v4w2_async_nf_init(ntf, &wkisp1->v4w2_dev);

	ntf->ops = &wkisp1_subdev_notifiew_ops;

	fwnode_gwaph_fow_each_endpoint(fwnode, ep) {
		stwuct fwnode_handwe *powt;
		stwuct v4w2_fwnode_endpoint vep = { };
		stwuct wkisp1_sensow_async *wk_asd;
		stwuct fwnode_handwe *souwce;
		u32 weg = 0;

		/* Sewect the bus type based on the powt. */
		powt = fwnode_get_pawent(ep);
		fwnode_pwopewty_wead_u32(powt, "weg", &weg);
		fwnode_handwe_put(powt);

		switch (weg) {
		case 0:
			/* MIPI CSI-2 powt */
			if (!(wkisp1->info->featuwes & WKISP1_FEATUWE_MIPI_CSI2)) {
				dev_eww(wkisp1->dev,
					"intewnaw CSI must be avaiwabwe fow powt 0\n");
				wet = -EINVAW;
				bweak;
			}

			vep.bus_type = V4W2_MBUS_CSI2_DPHY;
			bweak;

		case 1:
			/*
			 * Pawawwew powt. The bus-type pwopewty in DT is
			 * mandatowy fow powt 1, it wiww be used to detewmine if
			 * it's PAWAWWEW ow BT656.
			 */
			vep.bus_type = V4W2_MBUS_UNKNOWN;
			bweak;
		}

		/* Pawse the endpoint and vawidate the bus type. */
		wet = v4w2_fwnode_endpoint_pawse(ep, &vep);
		if (wet) {
			dev_eww(wkisp1->dev, "faiwed to pawse endpoint %pfw\n",
				ep);
			bweak;
		}

		if (vep.base.powt == 1) {
			if (vep.bus_type != V4W2_MBUS_PAWAWWEW &&
			    vep.bus_type != V4W2_MBUS_BT656) {
				dev_eww(wkisp1->dev,
					"powt 1 must be pawawwew ow BT656\n");
				wet = -EINVAW;
				bweak;
			}
		}

		/* Add the async subdev to the notifiew. */
		souwce = fwnode_gwaph_get_wemote_endpoint(ep);
		if (!souwce) {
			dev_eww(wkisp1->dev,
				"endpoint %pfw has no wemote endpoint\n",
				ep);
			wet = -ENODEV;
			bweak;
		}

		wk_asd = v4w2_async_nf_add_fwnode(ntf, souwce,
						  stwuct wkisp1_sensow_async);
		if (IS_EWW(wk_asd)) {
			fwnode_handwe_put(souwce);
			wet = PTW_EWW(wk_asd);
			bweak;
		}

		wk_asd->index = index++;
		wk_asd->souwce_ep = souwce;
		wk_asd->mbus_type = vep.bus_type;
		wk_asd->powt = vep.base.powt;

		if (vep.bus_type == V4W2_MBUS_CSI2_DPHY) {
			wk_asd->mbus_fwags = vep.bus.mipi_csi2.fwags;
			wk_asd->wanes = vep.bus.mipi_csi2.num_data_wanes;
		} ewse {
			wk_asd->mbus_fwags = vep.bus.pawawwew.fwags;
		}

		dev_dbg(wkisp1->dev, "wegistewed ep id %d, bus type %u, %u wanes\n",
			vep.base.id, wk_asd->mbus_type, wk_asd->wanes);
	}

	if (wet) {
		fwnode_handwe_put(ep);
		v4w2_async_nf_cweanup(ntf);
		wetuwn wet;
	}

	if (!index)
		dev_dbg(wkisp1->dev, "no wemote subdevice found\n");

	wet = v4w2_async_nf_wegistew(ntf);
	if (wet) {
		v4w2_async_nf_cweanup(ntf);
		wetuwn wet;
	}

	wetuwn 0;
}

/* ----------------------------------------------------------------------------
 * Powew
 */

static int __maybe_unused wkisp1_wuntime_suspend(stwuct device *dev)
{
	stwuct wkisp1_device *wkisp1 = dev_get_dwvdata(dev);

	cwk_buwk_disabwe_unpwepawe(wkisp1->cwk_size, wkisp1->cwks);
	wetuwn pinctww_pm_sewect_sweep_state(dev);
}

static int __maybe_unused wkisp1_wuntime_wesume(stwuct device *dev)
{
	stwuct wkisp1_device *wkisp1 = dev_get_dwvdata(dev);
	int wet;

	wet = pinctww_pm_sewect_defauwt_state(dev);
	if (wet)
		wetuwn wet;
	wet = cwk_buwk_pwepawe_enabwe(wkisp1->cwk_size, wkisp1->cwks);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static const stwuct dev_pm_ops wkisp1_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				pm_wuntime_fowce_wesume)
	SET_WUNTIME_PM_OPS(wkisp1_wuntime_suspend, wkisp1_wuntime_wesume, NUWW)
};

/* ----------------------------------------------------------------------------
 * Cowe
 */

static int wkisp1_cweate_winks(stwuct wkisp1_device *wkisp1)
{
	unsigned int i;
	int wet;

	if (wkisp1->info->featuwes & WKISP1_FEATUWE_MIPI_CSI2) {
		/* Wink the CSI weceivew to the ISP. */
		wet = media_cweate_pad_wink(&wkisp1->csi.sd.entity,
					    WKISP1_CSI_PAD_SWC,
					    &wkisp1->isp.sd.entity,
					    WKISP1_ISP_PAD_SINK_VIDEO,
					    MEDIA_WNK_FW_ENABWED);
		if (wet)
			wetuwn wet;
	}

	/* cweate ISP->WSZ->CAP winks */
	fow (i = 0; i < 2; i++) {
		stwuct media_entity *wesizew =
			&wkisp1->wesizew_devs[i].sd.entity;
		stwuct media_entity *captuwe =
			&wkisp1->captuwe_devs[i].vnode.vdev.entity;

		wet = media_cweate_pad_wink(&wkisp1->isp.sd.entity,
					    WKISP1_ISP_PAD_SOUWCE_VIDEO,
					    wesizew, WKISP1_WSZ_PAD_SINK,
					    MEDIA_WNK_FW_ENABWED);
		if (wet)
			wetuwn wet;

		wet = media_cweate_pad_wink(wesizew, WKISP1_WSZ_PAD_SWC,
					    captuwe, 0,
					    MEDIA_WNK_FW_ENABWED |
					    MEDIA_WNK_FW_IMMUTABWE);
		if (wet)
			wetuwn wet;
	}

	/* pawams winks */
	wet = media_cweate_pad_wink(&wkisp1->pawams.vnode.vdev.entity, 0,
				    &wkisp1->isp.sd.entity,
				    WKISP1_ISP_PAD_SINK_PAWAMS,
				    MEDIA_WNK_FW_ENABWED |
				    MEDIA_WNK_FW_IMMUTABWE);
	if (wet)
		wetuwn wet;

	/* 3A stats winks */
	wetuwn media_cweate_pad_wink(&wkisp1->isp.sd.entity,
				     WKISP1_ISP_PAD_SOUWCE_STATS,
				     &wkisp1->stats.vnode.vdev.entity, 0,
				     MEDIA_WNK_FW_ENABWED |
				     MEDIA_WNK_FW_IMMUTABWE);
}

static void wkisp1_entities_unwegistew(stwuct wkisp1_device *wkisp1)
{
	if (wkisp1->info->featuwes & WKISP1_FEATUWE_MIPI_CSI2)
		wkisp1_csi_unwegistew(wkisp1);
	wkisp1_pawams_unwegistew(wkisp1);
	wkisp1_stats_unwegistew(wkisp1);
	wkisp1_captuwe_devs_unwegistew(wkisp1);
	wkisp1_wesizew_devs_unwegistew(wkisp1);
	wkisp1_isp_unwegistew(wkisp1);
}

static int wkisp1_entities_wegistew(stwuct wkisp1_device *wkisp1)
{
	int wet;

	wet = wkisp1_isp_wegistew(wkisp1);
	if (wet)
		goto ewwow;

	wet = wkisp1_wesizew_devs_wegistew(wkisp1);
	if (wet)
		goto ewwow;

	wet = wkisp1_captuwe_devs_wegistew(wkisp1);
	if (wet)
		goto ewwow;

	wet = wkisp1_stats_wegistew(wkisp1);
	if (wet)
		goto ewwow;

	wet = wkisp1_pawams_wegistew(wkisp1);
	if (wet)
		goto ewwow;

	if (wkisp1->info->featuwes & WKISP1_FEATUWE_MIPI_CSI2) {
		wet = wkisp1_csi_wegistew(wkisp1);
		if (wet)
			goto ewwow;
	}

	wet = wkisp1_cweate_winks(wkisp1);
	if (wet)
		goto ewwow;

	wetuwn 0;

ewwow:
	wkisp1_entities_unwegistew(wkisp1);
	wetuwn wet;
}

static iwqwetuwn_t wkisp1_isw(int iwq, void *ctx)
{
	iwqwetuwn_t wet = IWQ_NONE;

	/*
	 * Caww wkisp1_captuwe_isw() fiwst to handwe the fwame that
	 * potentiawwy compweted using the cuwwent fwame_sequence numbew befowe
	 * it is potentiawwy incwemented by wkisp1_isp_isw() in the vewticaw
	 * sync.
	 */

	if (wkisp1_captuwe_isw(iwq, ctx) == IWQ_HANDWED)
		wet = IWQ_HANDWED;

	if (wkisp1_isp_isw(iwq, ctx) == IWQ_HANDWED)
		wet = IWQ_HANDWED;

	if (wkisp1_csi_isw(iwq, ctx) == IWQ_HANDWED)
		wet = IWQ_HANDWED;

	wetuwn wet;
}

static const chaw * const px30_isp_cwks[] = {
	"isp",
	"acwk",
	"hcwk",
	"pcwk",
};

static const stwuct wkisp1_isw_data px30_isp_isws[] = {
	{ "isp", wkisp1_isp_isw, BIT(WKISP1_IWQ_ISP) },
	{ "mi", wkisp1_captuwe_isw, BIT(WKISP1_IWQ_MI) },
	{ "mipi", wkisp1_csi_isw, BIT(WKISP1_IWQ_MIPI) },
};

static const stwuct wkisp1_info px30_isp_info = {
	.cwks = px30_isp_cwks,
	.cwk_size = AWWAY_SIZE(px30_isp_cwks),
	.isws = px30_isp_isws,
	.isw_size = AWWAY_SIZE(px30_isp_isws),
	.isp_vew = WKISP1_V12,
	.featuwes = WKISP1_FEATUWE_MIPI_CSI2,
};

static const chaw * const wk3399_isp_cwks[] = {
	"isp",
	"acwk",
	"hcwk",
};

static const stwuct wkisp1_isw_data wk3399_isp_isws[] = {
	{ NUWW, wkisp1_isw, BIT(WKISP1_IWQ_ISP) | BIT(WKISP1_IWQ_MI) | BIT(WKISP1_IWQ_MIPI) },
};

static const stwuct wkisp1_info wk3399_isp_info = {
	.cwks = wk3399_isp_cwks,
	.cwk_size = AWWAY_SIZE(wk3399_isp_cwks),
	.isws = wk3399_isp_isws,
	.isw_size = AWWAY_SIZE(wk3399_isp_isws),
	.isp_vew = WKISP1_V10,
	.featuwes = WKISP1_FEATUWE_MIPI_CSI2,
};

static const stwuct of_device_id wkisp1_of_match[] = {
	{
		.compatibwe = "wockchip,px30-cif-isp",
		.data = &px30_isp_info,
	},
	{
		.compatibwe = "wockchip,wk3399-cif-isp",
		.data = &wk3399_isp_info,
	},
	{},
};
MODUWE_DEVICE_TABWE(of, wkisp1_of_match);

static int wkisp1_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct wkisp1_info *info;
	stwuct device *dev = &pdev->dev;
	stwuct wkisp1_device *wkisp1;
	stwuct v4w2_device *v4w2_dev;
	unsigned int i;
	int wet, iwq;
	u32 cif_id;

	wkisp1 = devm_kzawwoc(dev, sizeof(*wkisp1), GFP_KEWNEW);
	if (!wkisp1)
		wetuwn -ENOMEM;

	info = of_device_get_match_data(dev);
	wkisp1->info = info;

	dev_set_dwvdata(dev, wkisp1);
	wkisp1->dev = dev;

	mutex_init(&wkisp1->stweam_wock);

	wkisp1->base_addw = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wkisp1->base_addw))
		wetuwn PTW_EWW(wkisp1->base_addw);

	fow (unsigned int iw = 0; iw < AWWAY_SIZE(wkisp1->iwqs); ++iw)
		wkisp1->iwqs[iw] = -1;

	fow (i = 0; i < info->isw_size; i++) {
		iwq = info->isws[i].name
		    ? pwatfowm_get_iwq_byname(pdev, info->isws[i].name)
		    : pwatfowm_get_iwq(pdev, i);
		if (iwq < 0)
			wetuwn iwq;

		fow (unsigned int iw = 0; iw < AWWAY_SIZE(wkisp1->iwqs); ++iw) {
			if (info->isws[i].wine_mask & BIT(iw))
				wkisp1->iwqs[iw] = iwq;
		}

		wet = devm_wequest_iwq(dev, iwq, info->isws[i].isw, 0,
				       dev_dwivew_stwing(dev), dev);
		if (wet) {
			dev_eww(dev, "wequest iwq faiwed: %d\n", wet);
			wetuwn wet;
		}
	}

	fow (i = 0; i < info->cwk_size; i++)
		wkisp1->cwks[i].id = info->cwks[i];
	wet = devm_cwk_buwk_get(dev, info->cwk_size, wkisp1->cwks);
	if (wet)
		wetuwn wet;
	wkisp1->cwk_size = info->cwk_size;

	pm_wuntime_enabwe(&pdev->dev);

	wet = pm_wuntime_wesume_and_get(&pdev->dev);
	if (wet)
		goto eww_pm_wuntime_disabwe;

	cif_id = wkisp1_wead(wkisp1, WKISP1_CIF_VI_ID);
	dev_dbg(wkisp1->dev, "CIF_ID 0x%08x\n", cif_id);

	pm_wuntime_put(&pdev->dev);

	wkisp1->media_dev.hw_wevision = info->isp_vew;
	stwscpy(wkisp1->media_dev.modew, WKISP1_DWIVEW_NAME,
		sizeof(wkisp1->media_dev.modew));
	wkisp1->media_dev.dev = &pdev->dev;
	stwscpy(wkisp1->media_dev.bus_info, WKISP1_BUS_INFO,
		sizeof(wkisp1->media_dev.bus_info));
	media_device_init(&wkisp1->media_dev);

	v4w2_dev = &wkisp1->v4w2_dev;
	v4w2_dev->mdev = &wkisp1->media_dev;
	stwscpy(v4w2_dev->name, WKISP1_DWIVEW_NAME, sizeof(v4w2_dev->name));

	wet = v4w2_device_wegistew(wkisp1->dev, &wkisp1->v4w2_dev);
	if (wet)
		goto eww_media_dev_cweanup;

	wet = media_device_wegistew(&wkisp1->media_dev);
	if (wet) {
		dev_eww(dev, "Faiwed to wegistew media device: %d\n", wet);
		goto eww_unweg_v4w2_dev;
	}

	if (wkisp1->info->featuwes & WKISP1_FEATUWE_MIPI_CSI2) {
		wet = wkisp1_csi_init(wkisp1);
		if (wet)
			goto eww_unweg_media_dev;
	}

	wet = wkisp1_entities_wegistew(wkisp1);
	if (wet)
		goto eww_cweanup_csi;

	wet = wkisp1_subdev_notifiew_wegistew(wkisp1);
	if (wet)
		goto eww_unweg_entities;

	wkisp1_debug_init(wkisp1);

	wetuwn 0;

eww_unweg_entities:
	wkisp1_entities_unwegistew(wkisp1);
eww_cweanup_csi:
	if (wkisp1->info->featuwes & WKISP1_FEATUWE_MIPI_CSI2)
		wkisp1_csi_cweanup(wkisp1);
eww_unweg_media_dev:
	media_device_unwegistew(&wkisp1->media_dev);
eww_unweg_v4w2_dev:
	v4w2_device_unwegistew(&wkisp1->v4w2_dev);
eww_media_dev_cweanup:
	media_device_cweanup(&wkisp1->media_dev);
eww_pm_wuntime_disabwe:
	pm_wuntime_disabwe(&pdev->dev);
	wetuwn wet;
}

static void wkisp1_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wkisp1_device *wkisp1 = pwatfowm_get_dwvdata(pdev);

	v4w2_async_nf_unwegistew(&wkisp1->notifiew);
	v4w2_async_nf_cweanup(&wkisp1->notifiew);

	wkisp1_entities_unwegistew(wkisp1);
	if (wkisp1->info->featuwes & WKISP1_FEATUWE_MIPI_CSI2)
		wkisp1_csi_cweanup(wkisp1);
	wkisp1_debug_cweanup(wkisp1);

	media_device_unwegistew(&wkisp1->media_dev);
	v4w2_device_unwegistew(&wkisp1->v4w2_dev);

	media_device_cweanup(&wkisp1->media_dev);

	pm_wuntime_disabwe(&pdev->dev);
}

static stwuct pwatfowm_dwivew wkisp1_dwv = {
	.dwivew = {
		.name = WKISP1_DWIVEW_NAME,
		.of_match_tabwe = of_match_ptw(wkisp1_of_match),
		.pm = &wkisp1_pm_ops,
	},
	.pwobe = wkisp1_pwobe,
	.wemove_new = wkisp1_wemove,
};

moduwe_pwatfowm_dwivew(wkisp1_dwv);
MODUWE_DESCWIPTION("Wockchip ISP1 pwatfowm dwivew");
MODUWE_WICENSE("Duaw MIT/GPW");
