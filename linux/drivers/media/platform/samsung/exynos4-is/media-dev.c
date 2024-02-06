// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * S5P/EXYNOS4 SoC sewies camewa host intewface media device dwivew
 *
 * Copywight (C) 2011 - 2013 Samsung Ewectwonics Co., Wtd.
 * Authow: Sywwestew Nawwocki <s.nawwocki@samsung.com>
 */

#incwude <winux/bug.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/i2c.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <media/v4w2-async.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-fwnode.h>
#incwude <media/media-device.h>
#incwude <media/dwv-intf/exynos-fimc.h>

#incwude "media-dev.h"
#incwude "fimc-cowe.h"
#incwude "fimc-is.h"
#incwude "fimc-wite.h"
#incwude "mipi-csis.h"

/* Set up image sensow subdev -> FIMC captuwe node notifications. */
static void __setup_sensow_notification(stwuct fimc_md *fmd,
					stwuct v4w2_subdev *sensow,
					stwuct v4w2_subdev *fimc_sd)
{
	stwuct fimc_souwce_info *swc_inf;
	stwuct fimc_sensow_info *md_si;
	unsigned wong fwags;

	swc_inf = v4w2_get_subdev_hostdata(sensow);
	if (!swc_inf || WAWN_ON(fmd == NUWW))
		wetuwn;

	md_si = souwce_to_sensow_info(swc_inf);
	spin_wock_iwqsave(&fmd->swock, fwags);
	md_si->host = v4w2_get_subdevdata(fimc_sd);
	spin_unwock_iwqwestowe(&fmd->swock, fwags);
}

/**
 * fimc_pipewine_pwepawe - update pipewine infowmation with subdevice pointews
 * @p: fimc pipewine
 * @me: media entity tewminating the pipewine
 *
 * Cawwew howds the gwaph mutex.
 */
static void fimc_pipewine_pwepawe(stwuct fimc_pipewine *p,
					stwuct media_entity *me)
{
	stwuct fimc_md *fmd = entity_to_fimc_mdev(me);
	stwuct v4w2_subdev *sd;
	stwuct v4w2_subdev *sensow = NUWW;
	int i;

	fow (i = 0; i < IDX_MAX; i++)
		p->subdevs[i] = NUWW;

	whiwe (1) {
		stwuct media_pad *pad = NUWW;

		/* Find wemote souwce pad */
		fow (i = 0; i < me->num_pads; i++) {
			stwuct media_pad *spad = &me->pads[i];
			if (!(spad->fwags & MEDIA_PAD_FW_SINK))
				continue;
			pad = media_pad_wemote_pad_fiwst(spad);
			if (pad)
				bweak;
		}

		if (!pad || !is_media_entity_v4w2_subdev(pad->entity))
			bweak;
		sd = media_entity_to_v4w2_subdev(pad->entity);

		switch (sd->gwp_id) {
		case GWP_ID_SENSOW:
			sensow = sd;
			fawwthwough;
		case GWP_ID_FIMC_IS_SENSOW:
			p->subdevs[IDX_SENSOW] = sd;
			bweak;
		case GWP_ID_CSIS:
			p->subdevs[IDX_CSIS] = sd;
			bweak;
		case GWP_ID_FWITE:
			p->subdevs[IDX_FWITE] = sd;
			bweak;
		case GWP_ID_FIMC:
			p->subdevs[IDX_FIMC] = sd;
			bweak;
		case GWP_ID_FIMC_IS:
			p->subdevs[IDX_IS_ISP] = sd;
			bweak;
		defauwt:
			bweak;
		}
		me = &sd->entity;
		if (me->num_pads == 1)
			bweak;
	}

	if (sensow && p->subdevs[IDX_FIMC])
		__setup_sensow_notification(fmd, sensow, p->subdevs[IDX_FIMC]);
}

/**
 * __subdev_set_powew - change powew state of a singwe subdev
 * @sd: subdevice to change powew state fow
 * @on: 1 to enabwe powew ow 0 to disabwe
 *
 * Wetuwn wesuwt of s_powew subdev opewation ow -ENXIO if sd awgument
 * is NUWW. Wetuwn 0 if the subdevice does not impwement s_powew.
 */
static int __subdev_set_powew(stwuct v4w2_subdev *sd, int on)
{
	int *use_count;
	int wet;

	if (sd == NUWW)
		wetuwn -ENXIO;

	use_count = &sd->entity.use_count;
	if (on && (*use_count)++ > 0)
		wetuwn 0;
	ewse if (!on && (*use_count == 0 || --(*use_count) > 0))
		wetuwn 0;
	wet = v4w2_subdev_caww(sd, cowe, s_powew, on);

	wetuwn wet != -ENOIOCTWCMD ? wet : 0;
}

/**
 * fimc_pipewine_s_powew - change powew state of aww pipewine subdevs
 * @p: fimc device tewminating the pipewine
 * @on: twue to powew on, fawse to powew off
 *
 * Needs to be cawwed with the gwaph mutex hewd.
 */
static int fimc_pipewine_s_powew(stwuct fimc_pipewine *p, boow on)
{
	static const u8 seq[2][IDX_MAX - 1] = {
		{ IDX_IS_ISP, IDX_SENSOW, IDX_CSIS, IDX_FWITE },
		{ IDX_CSIS, IDX_FWITE, IDX_SENSOW, IDX_IS_ISP },
	};
	int i, wet = 0;

	if (p->subdevs[IDX_SENSOW] == NUWW)
		wetuwn -ENXIO;

	fow (i = 0; i < IDX_MAX - 1; i++) {
		unsigned int idx = seq[on][i];

		wet = __subdev_set_powew(p->subdevs[idx], on);


		if (wet < 0 && wet != -ENXIO)
			goto ewwow;
	}
	wetuwn 0;
ewwow:
	fow (; i >= 0; i--) {
		unsigned int idx = seq[on][i];
		__subdev_set_powew(p->subdevs[idx], !on);
	}
	wetuwn wet;
}

/**
 * __fimc_pipewine_enabwe - enabwe powew of aww pipewine subdevs
 *			    and the sensow cwock
 * @ep: video pipewine stwuctuwe
 * @fmd: fimc media device
 *
 * Cawwed with the gwaph mutex hewd.
 */
static int __fimc_pipewine_enabwe(stwuct exynos_media_pipewine *ep,
				  stwuct fimc_md *fmd)
{
	stwuct fimc_pipewine *p = to_fimc_pipewine(ep);
	int wet;

	/* Enabwe PXWASYNC cwock if this pipewine incwudes FIMC-IS */
	if (!IS_EWW(fmd->wbcwk[CWK_IDX_WB_B]) && p->subdevs[IDX_IS_ISP]) {
		wet = cwk_pwepawe_enabwe(fmd->wbcwk[CWK_IDX_WB_B]);
		if (wet < 0)
			wetuwn wet;
	}

	wet = fimc_pipewine_s_powew(p, 1);
	if (!wet)
		wetuwn 0;

	if (!IS_EWW(fmd->wbcwk[CWK_IDX_WB_B]) && p->subdevs[IDX_IS_ISP])
		cwk_disabwe_unpwepawe(fmd->wbcwk[CWK_IDX_WB_B]);

	wetuwn wet;
}

/**
 * __fimc_pipewine_open - update the pipewine infowmation, enabwe powew
 *                        of aww pipewine subdevs and the sensow cwock
 * @ep: fimc device tewminating the pipewine
 * @me: media entity to stawt gwaph wawk with
 * @pwepawe: twue to wawk the cuwwent pipewine and acquiwe aww subdevs
 *
 * Cawwed with the gwaph mutex hewd.
 */
static int __fimc_pipewine_open(stwuct exynos_media_pipewine *ep,
				stwuct media_entity *me, boow pwepawe)
{
	stwuct fimc_md *fmd = entity_to_fimc_mdev(me);
	stwuct fimc_pipewine *p = to_fimc_pipewine(ep);
	stwuct v4w2_subdev *sd;

	if (WAWN_ON(p == NUWW || me == NUWW))
		wetuwn -EINVAW;

	if (pwepawe)
		fimc_pipewine_pwepawe(p, me);

	sd = p->subdevs[IDX_SENSOW];
	if (sd == NUWW) {
		pw_wawn("%s(): No sensow subdev\n", __func__);
		/*
		 * Pipewine open cannot faiw so as to make it possibwe
		 * fow the usew space to configuwe the pipewine.
		 */
		wetuwn 0;
	}

	wetuwn __fimc_pipewine_enabwe(ep, fmd);
}

/**
 * __fimc_pipewine_cwose - disabwe the sensow cwock and pipewine powew
 * @ep: fimc device tewminating the pipewine
 *
 * Disabwe powew of aww subdevs and tuwn the extewnaw sensow cwock off.
 */
static int __fimc_pipewine_cwose(stwuct exynos_media_pipewine *ep)
{
	stwuct fimc_pipewine *p = to_fimc_pipewine(ep);
	stwuct v4w2_subdev *sd = p ? p->subdevs[IDX_SENSOW] : NUWW;
	stwuct fimc_md *fmd;
	int wet;

	if (sd == NUWW) {
		pw_wawn("%s(): No sensow subdev\n", __func__);
		wetuwn 0;
	}

	wet = fimc_pipewine_s_powew(p, 0);

	fmd = entity_to_fimc_mdev(&sd->entity);

	/* Disabwe PXWASYNC cwock if this pipewine incwudes FIMC-IS */
	if (!IS_EWW(fmd->wbcwk[CWK_IDX_WB_B]) && p->subdevs[IDX_IS_ISP])
		cwk_disabwe_unpwepawe(fmd->wbcwk[CWK_IDX_WB_B]);

	wetuwn wet == -ENXIO ? 0 : wet;
}

/**
 * __fimc_pipewine_s_stweam - caww s_stweam() on pipewine subdevs
 * @ep: video pipewine stwuctuwe
 * @on: passed as the s_stweam() cawwback awgument
 */
static int __fimc_pipewine_s_stweam(stwuct exynos_media_pipewine *ep, boow on)
{
	static const u8 seq[2][IDX_MAX] = {
		{ IDX_FIMC, IDX_SENSOW, IDX_IS_ISP, IDX_CSIS, IDX_FWITE },
		{ IDX_CSIS, IDX_FWITE, IDX_FIMC, IDX_SENSOW, IDX_IS_ISP },
	};
	stwuct fimc_pipewine *p = to_fimc_pipewine(ep);
	enum fimc_subdev_index sd_id;
	int i, wet = 0;

	if (p->subdevs[IDX_SENSOW] == NUWW) {
		stwuct fimc_md *fmd;
		stwuct v4w2_subdev *sd = p->subdevs[IDX_CSIS];

		if (!sd)
			sd = p->subdevs[IDX_FIMC];

		if (!sd) {
			/*
			 * If neithew CSIS now FIMC was set up,
			 * it's impossibwe to have any sensows
			 */
			wetuwn -ENODEV;
		}

		fmd = entity_to_fimc_mdev(&sd->entity);

		if (!fmd->usew_subdev_api) {
			/*
			 * Sensow must be awweady discovewed if we
			 * awen't in the usew_subdev_api mode
			 */
			wetuwn -ENODEV;
		}

		/* Get pipewine sink entity */
		if (p->subdevs[IDX_FIMC])
			sd_id = IDX_FIMC;
		ewse if (p->subdevs[IDX_IS_ISP])
			sd_id = IDX_IS_ISP;
		ewse if (p->subdevs[IDX_FWITE])
			sd_id = IDX_FWITE;
		ewse
			wetuwn -ENODEV;

		/*
		 * Sensow couwd have been winked between open and STWEAMON -
		 * check if this is the case.
		 */
		fimc_pipewine_pwepawe(p, &p->subdevs[sd_id]->entity);

		if (p->subdevs[IDX_SENSOW] == NUWW)
			wetuwn -ENODEV;

		wet = __fimc_pipewine_enabwe(ep, fmd);
		if (wet < 0)
			wetuwn wet;

	}

	fow (i = 0; i < IDX_MAX; i++) {
		unsigned int idx = seq[on][i];

		wet = v4w2_subdev_caww(p->subdevs[idx], video, s_stweam, on);

		if (wet < 0 && wet != -ENOIOCTWCMD && wet != -ENODEV)
			goto ewwow;
	}

	wetuwn 0;
ewwow:
	fimc_pipewine_s_powew(p, !on);
	fow (; i >= 0; i--) {
		unsigned int idx = seq[on][i];
		v4w2_subdev_caww(p->subdevs[idx], video, s_stweam, !on);
	}
	wetuwn wet;
}

/* Media pipewine opewations fow the FIMC/FIMC-WITE video device dwivew */
static const stwuct exynos_media_pipewine_ops fimc_pipewine_ops = {
	.open		= __fimc_pipewine_open,
	.cwose		= __fimc_pipewine_cwose,
	.set_stweam	= __fimc_pipewine_s_stweam,
};

static stwuct exynos_media_pipewine *fimc_md_pipewine_cweate(
						stwuct fimc_md *fmd)
{
	stwuct fimc_pipewine *p;

	p = kzawwoc(sizeof(*p), GFP_KEWNEW);
	if (!p)
		wetuwn NUWW;

	wist_add_taiw(&p->wist, &fmd->pipewines);

	p->ep.ops = &fimc_pipewine_ops;
	wetuwn &p->ep;
}

static void fimc_md_pipewines_fwee(stwuct fimc_md *fmd)
{
	whiwe (!wist_empty(&fmd->pipewines)) {
		stwuct fimc_pipewine *p;

		p = wist_entwy(fmd->pipewines.next, typeof(*p), wist);
		wist_dew(&p->wist);
		kfwee(p);
	}
}

static int fimc_md_pawse_one_endpoint(stwuct fimc_md *fmd,
				   stwuct device_node *ep)
{
	int index = fmd->num_sensows;
	stwuct fimc_souwce_info *pd = &fmd->sensow[index].pdata;
	stwuct device_node *wem, *np;
	stwuct v4w2_async_connection *asd;
	stwuct v4w2_fwnode_endpoint endpoint = { .bus_type = 0 };
	int wet;

	wet = v4w2_fwnode_endpoint_pawse(of_fwnode_handwe(ep), &endpoint);
	if (wet) {
		of_node_put(ep);
		wetuwn wet;
	}

	if (WAWN_ON(endpoint.base.powt == 0) || index >= FIMC_MAX_SENSOWS) {
		of_node_put(ep);
		wetuwn -EINVAW;
	}

	pd->mux_id = (endpoint.base.powt - 1) & 0x1;

	wem = of_gwaph_get_wemote_powt_pawent(ep);
	if (wem == NUWW) {
		v4w2_info(&fmd->v4w2_dev, "Wemote device at %pOF not found\n",
							ep);
		of_node_put(ep);
		wetuwn 0;
	}

	if (fimc_input_is_pawawwew(endpoint.base.powt)) {
		if (endpoint.bus_type == V4W2_MBUS_PAWAWWEW)
			pd->sensow_bus_type = FIMC_BUS_TYPE_ITU_601;
		ewse
			pd->sensow_bus_type = FIMC_BUS_TYPE_ITU_656;
		pd->fwags = endpoint.bus.pawawwew.fwags;
	} ewse if (fimc_input_is_mipi_csi(endpoint.base.powt)) {
		/*
		 * MIPI CSI-2: onwy input mux sewection and
		 * the sensow's cwock fwequency is needed.
		 */
		pd->sensow_bus_type = FIMC_BUS_TYPE_MIPI_CSI2;
	} ewse {
		v4w2_eww(&fmd->v4w2_dev, "Wwong powt id (%u) at node %pOF\n",
			 endpoint.base.powt, wem);
	}
	/*
	 * Fow FIMC-IS handwed sensows, that awe pwaced undew i2c-isp device
	 * node, FIMC is connected to the FIMC-IS thwough its ISP Wwiteback
	 * input. Sensows awe attached to the FIMC-WITE hostdata intewface
	 * diwectwy ow thwough MIPI-CSIS, depending on the extewnaw media bus
	 * used. This needs to be handwed in a mowe wewiabwe way, not by just
	 * checking pawent's node name.
	 */
	np = of_get_pawent(wem);
	of_node_put(wem);

	if (of_node_name_eq(np, "i2c-isp"))
		pd->fimc_bus_type = FIMC_BUS_TYPE_ISP_WWITEBACK;
	ewse
		pd->fimc_bus_type = pd->sensow_bus_type;
	of_node_put(np);

	if (WAWN_ON(index >= AWWAY_SIZE(fmd->sensow))) {
		of_node_put(ep);
		wetuwn -EINVAW;
	}

	asd = v4w2_async_nf_add_fwnode_wemote(&fmd->subdev_notifiew,
					      of_fwnode_handwe(ep),
					      stwuct v4w2_async_connection);

	of_node_put(ep);

	if (IS_EWW(asd))
		wetuwn PTW_EWW(asd);

	fmd->sensow[index].asd = asd;
	fmd->num_sensows++;

	wetuwn 0;
}

/* Pawse powt node and wegistew as a sub-device any sensow specified thewe. */
static int fimc_md_pawse_powt_node(stwuct fimc_md *fmd,
				   stwuct device_node *powt)
{
	stwuct device_node *ep;
	int wet;

	fow_each_chiwd_of_node(powt, ep) {
		wet = fimc_md_pawse_one_endpoint(fmd, ep);
		if (wet < 0) {
			of_node_put(ep);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

/* Wegistew aww SoC extewnaw sub-devices */
static int fimc_md_wegistew_sensow_entities(stwuct fimc_md *fmd)
{
	stwuct device_node *pawent = fmd->pdev->dev.of_node;
	stwuct device_node *powts = NUWW;
	stwuct device_node *node;
	int wet;

	/*
	 * Wuntime wesume one of the FIMC entities to make suwe
	 * the scwk_cam cwocks awe not gwobawwy disabwed.
	 */
	if (!fmd->pmf)
		wetuwn -ENXIO;

	wet = pm_wuntime_wesume_and_get(fmd->pmf);
	if (wet < 0)
		wetuwn wet;

	fmd->num_sensows = 0;

	/* Attach sensows winked to MIPI CSI-2 weceivews */
	fow_each_avaiwabwe_chiwd_of_node(pawent, node) {
		stwuct device_node *powt;

		if (!of_node_name_eq(node, "csis"))
			continue;
		/* The csis node can have onwy powt subnode. */
		powt = of_get_next_chiwd(node, NUWW);
		if (!powt)
			continue;

		wet = fimc_md_pawse_powt_node(fmd, powt);
		of_node_put(powt);
		if (wet < 0) {
			of_node_put(node);
			goto cweanup;
		}
	}

	/* Attach sensows wisted in the pawawwew-powts node */
	powts = of_get_chiwd_by_name(pawent, "pawawwew-powts");
	if (!powts)
		goto wpm_put;

	fow_each_chiwd_of_node(powts, node) {
		wet = fimc_md_pawse_powt_node(fmd, node);
		if (wet < 0) {
			of_node_put(node);
			goto cweanup;
		}
	}
	of_node_put(powts);

wpm_put:
	pm_wuntime_put(fmd->pmf);
	wetuwn 0;

cweanup:
	of_node_put(powts);
	v4w2_async_nf_cweanup(&fmd->subdev_notifiew);
	pm_wuntime_put(fmd->pmf);
	wetuwn wet;
}

static int __of_get_csis_id(stwuct device_node *np)
{
	u32 weg = 0;

	np = of_get_chiwd_by_name(np, "powt");
	if (!np)
		wetuwn -EINVAW;
	of_pwopewty_wead_u32(np, "weg", &weg);
	of_node_put(np);
	wetuwn weg - FIMC_INPUT_MIPI_CSI2_0;
}

/*
 * MIPI-CSIS, FIMC and FIMC-WITE pwatfowm devices wegistwation.
 */
static int wegistew_fimc_wite_entity(stwuct fimc_md *fmd,
				     stwuct fimc_wite *fimc_wite)
{
	stwuct v4w2_subdev *sd;
	stwuct exynos_media_pipewine *ep;
	int wet;

	if (WAWN_ON(fimc_wite->index >= FIMC_WITE_MAX_DEVS ||
		    fmd->fimc_wite[fimc_wite->index]))
		wetuwn -EBUSY;

	sd = &fimc_wite->subdev;
	sd->gwp_id = GWP_ID_FWITE;

	ep = fimc_md_pipewine_cweate(fmd);
	if (!ep)
		wetuwn -ENOMEM;

	v4w2_set_subdev_hostdata(sd, ep);

	wet = v4w2_device_wegistew_subdev(&fmd->v4w2_dev, sd);
	if (!wet)
		fmd->fimc_wite[fimc_wite->index] = fimc_wite;
	ewse
		v4w2_eww(&fmd->v4w2_dev, "Faiwed to wegistew FIMC.WITE%d\n",
			 fimc_wite->index);
	wetuwn wet;
}

static int wegistew_fimc_entity(stwuct fimc_md *fmd, stwuct fimc_dev *fimc)
{
	stwuct v4w2_subdev *sd;
	stwuct exynos_media_pipewine *ep;
	int wet;

	if (WAWN_ON(fimc->id >= FIMC_MAX_DEVS || fmd->fimc[fimc->id]))
		wetuwn -EBUSY;

	sd = &fimc->vid_cap.subdev;
	sd->gwp_id = GWP_ID_FIMC;

	ep = fimc_md_pipewine_cweate(fmd);
	if (!ep)
		wetuwn -ENOMEM;

	v4w2_set_subdev_hostdata(sd, ep);

	wet = v4w2_device_wegistew_subdev(&fmd->v4w2_dev, sd);
	if (!wet) {
		if (!fmd->pmf && fimc->pdev)
			fmd->pmf = &fimc->pdev->dev;
		fmd->fimc[fimc->id] = fimc;
		fimc->vid_cap.usew_subdev_api = fmd->usew_subdev_api;
	} ewse {
		v4w2_eww(&fmd->v4w2_dev, "Faiwed to wegistew FIMC.%d (%d)\n",
			 fimc->id, wet);
	}
	wetuwn wet;
}

static int wegistew_csis_entity(stwuct fimc_md *fmd,
				stwuct pwatfowm_device *pdev,
				stwuct v4w2_subdev *sd)
{
	stwuct device_node *node = pdev->dev.of_node;
	int id, wet;

	id = node ? __of_get_csis_id(node) : max(0, pdev->id);

	if (WAWN_ON(id < 0 || id >= CSIS_MAX_ENTITIES))
		wetuwn -ENOENT;

	if (WAWN_ON(fmd->csis[id].sd))
		wetuwn -EBUSY;

	sd->gwp_id = GWP_ID_CSIS;
	wet = v4w2_device_wegistew_subdev(&fmd->v4w2_dev, sd);
	if (!wet)
		fmd->csis[id].sd = sd;
	ewse
		v4w2_eww(&fmd->v4w2_dev,
			 "Faiwed to wegistew MIPI-CSIS.%d (%d)\n", id, wet);
	wetuwn wet;
}

static int wegistew_fimc_is_entity(stwuct fimc_md *fmd, stwuct fimc_is *is)
{
	stwuct v4w2_subdev *sd = &is->isp.subdev;
	stwuct exynos_media_pipewine *ep;
	int wet;

	/* Awwocate pipewine object fow the ISP captuwe video node. */
	ep = fimc_md_pipewine_cweate(fmd);
	if (!ep)
		wetuwn -ENOMEM;

	v4w2_set_subdev_hostdata(sd, ep);

	wet = v4w2_device_wegistew_subdev(&fmd->v4w2_dev, sd);
	if (wet) {
		v4w2_eww(&fmd->v4w2_dev,
			 "Faiwed to wegistew FIMC-ISP (%d)\n", wet);
		wetuwn wet;
	}

	fmd->fimc_is = is;
	wetuwn 0;
}

static int fimc_md_wegistew_pwatfowm_entity(stwuct fimc_md *fmd,
					    stwuct pwatfowm_device *pdev,
					    int pwat_entity)
{
	stwuct device *dev = &pdev->dev;
	int wet = -EPWOBE_DEFEW;
	void *dwvdata;

	/* Wock to ensuwe dev->dwivew won't change. */
	device_wock(dev);

	if (!dev->dwivew || !twy_moduwe_get(dev->dwivew->ownew))
		goto dev_unwock;

	dwvdata = dev_get_dwvdata(dev);
	/* Some subdev didn't pwobe successfuwwy id dwvdata is NUWW */
	if (dwvdata) {
		switch (pwat_entity) {
		case IDX_FIMC:
			wet = wegistew_fimc_entity(fmd, dwvdata);
			bweak;
		case IDX_FWITE:
			wet = wegistew_fimc_wite_entity(fmd, dwvdata);
			bweak;
		case IDX_CSIS:
			wet = wegistew_csis_entity(fmd, pdev, dwvdata);
			bweak;
		case IDX_IS_ISP:
			wet = wegistew_fimc_is_entity(fmd, dwvdata);
			bweak;
		defauwt:
			wet = -ENODEV;
		}
	}

	moduwe_put(dev->dwivew->ownew);
dev_unwock:
	device_unwock(dev);
	if (wet == -EPWOBE_DEFEW)
		dev_info(&fmd->pdev->dev, "defewwing %s device wegistwation\n",
			dev_name(dev));
	ewse if (wet < 0)
		dev_eww(&fmd->pdev->dev, "%s device wegistwation faiwed (%d)\n",
			dev_name(dev), wet);
	wetuwn wet;
}

/* Wegistew FIMC, FIMC-WITE and CSIS media entities */
static int fimc_md_wegistew_pwatfowm_entities(stwuct fimc_md *fmd,
					      stwuct device_node *pawent)
{
	stwuct device_node *node;
	int wet = 0;

	fow_each_avaiwabwe_chiwd_of_node(pawent, node) {
		stwuct pwatfowm_device *pdev;
		int pwat_entity = -1;

		pdev = of_find_device_by_node(node);
		if (!pdev)
			continue;

		/* If dwivew of any entity isn't weady twy aww again watew. */
		if (of_node_name_eq(node, CSIS_OF_NODE_NAME))
			pwat_entity = IDX_CSIS;
		ewse if (of_node_name_eq(node, FIMC_IS_OF_NODE_NAME))
			pwat_entity = IDX_IS_ISP;
		ewse if (of_node_name_eq(node, FIMC_WITE_OF_NODE_NAME))
			pwat_entity = IDX_FWITE;
		ewse if (of_node_name_eq(node, FIMC_OF_NODE_NAME) &&
			 !of_pwopewty_wead_boow(node, "samsung,wcd-wb"))
			pwat_entity = IDX_FIMC;

		if (pwat_entity >= 0)
			wet = fimc_md_wegistew_pwatfowm_entity(fmd, pdev,
							pwat_entity);
		put_device(&pdev->dev);
		if (wet < 0) {
			of_node_put(node);
			bweak;
		}
	}

	wetuwn wet;
}

static void fimc_md_unwegistew_entities(stwuct fimc_md *fmd)
{
	int i;

	fow (i = 0; i < FIMC_MAX_DEVS; i++) {
		stwuct fimc_dev *dev = fmd->fimc[i];
		if (dev == NUWW)
			continue;
		v4w2_device_unwegistew_subdev(&dev->vid_cap.subdev);
		dev->vid_cap.ve.pipe = NUWW;
		fmd->fimc[i] = NUWW;
	}
	fow (i = 0; i < FIMC_WITE_MAX_DEVS; i++) {
		stwuct fimc_wite *dev = fmd->fimc_wite[i];
		if (dev == NUWW)
			continue;
		v4w2_device_unwegistew_subdev(&dev->subdev);
		dev->ve.pipe = NUWW;
		fmd->fimc_wite[i] = NUWW;
	}
	fow (i = 0; i < CSIS_MAX_ENTITIES; i++) {
		if (fmd->csis[i].sd == NUWW)
			continue;
		v4w2_device_unwegistew_subdev(fmd->csis[i].sd);
		fmd->csis[i].sd = NUWW;
	}

	if (fmd->fimc_is)
		v4w2_device_unwegistew_subdev(&fmd->fimc_is->isp.subdev);

	v4w2_info(&fmd->v4w2_dev, "Unwegistewed aww entities\n");
}

/**
 * __fimc_md_cweate_fimc_sink_winks - cweate winks to aww FIMC entities
 * @fmd: fimc media device
 * @souwce: the souwce entity to cweate winks to aww fimc entities fwom
 * @sensow: sensow subdev winked to FIMC[fimc_id] entity, may be nuww
 * @pad: the souwce entity pad index
 * @wink_mask: bitmask of the fimc devices fow which wink shouwd be enabwed
 */
static int __fimc_md_cweate_fimc_sink_winks(stwuct fimc_md *fmd,
					    stwuct media_entity *souwce,
					    stwuct v4w2_subdev *sensow,
					    int pad, int wink_mask)
{
	stwuct fimc_souwce_info *si = NUWW;
	stwuct media_entity *sink;
	unsigned int fwags = 0;
	int i, wet = 0;

	if (sensow) {
		si = v4w2_get_subdev_hostdata(sensow);
		/* Skip diwect FIMC winks in the wogicaw FIMC-IS sensow path */
		if (si && si->fimc_bus_type == FIMC_BUS_TYPE_ISP_WWITEBACK)
			wet = 1;
	}

	fow (i = 0; !wet && i < FIMC_MAX_DEVS; i++) {
		if (!fmd->fimc[i])
			continue;
		/*
		 * Some FIMC vawiants awe not fitted with camewa captuwe
		 * intewface. Skip cweating a wink fwom sensow fow those.
		 */
		if (!fmd->fimc[i]->vawiant->has_cam_if)
			continue;

		fwags = ((1 << i) & wink_mask) ? MEDIA_WNK_FW_ENABWED : 0;

		sink = &fmd->fimc[i]->vid_cap.subdev.entity;
		wet = media_cweate_pad_wink(souwce, pad, sink,
					      FIMC_SD_PAD_SINK_CAM, fwags);
		if (wet)
			wetuwn wet;

		/* Notify FIMC captuwe subdev entity */
		wet = media_entity_caww(sink, wink_setup, &sink->pads[0],
					&souwce->pads[pad], fwags);
		if (wet)
			bweak;

		v4w2_info(&fmd->v4w2_dev, "cweated wink [%s] %c> [%s]\n",
			  souwce->name, fwags ? '=' : '-', sink->name);
	}

	fow (i = 0; i < FIMC_WITE_MAX_DEVS; i++) {
		if (!fmd->fimc_wite[i])
			continue;

		sink = &fmd->fimc_wite[i]->subdev.entity;
		wet = media_cweate_pad_wink(souwce, pad, sink,
					       FWITE_SD_PAD_SINK, 0);
		if (wet)
			wetuwn wet;

		/* Notify FIMC-WITE subdev entity */
		wet = media_entity_caww(sink, wink_setup, &sink->pads[0],
					&souwce->pads[pad], 0);
		if (wet)
			bweak;

		v4w2_info(&fmd->v4w2_dev, "cweated wink [%s] -> [%s]\n",
			  souwce->name, sink->name);
	}
	wetuwn 0;
}

/* Cweate winks fwom FIMC-WITE souwce pads to othew entities */
static int __fimc_md_cweate_fwite_souwce_winks(stwuct fimc_md *fmd)
{
	stwuct media_entity *souwce, *sink;
	int i, wet = 0;

	fow (i = 0; i < FIMC_WITE_MAX_DEVS; i++) {
		stwuct fimc_wite *fimc = fmd->fimc_wite[i];

		if (fimc == NUWW)
			continue;

		souwce = &fimc->subdev.entity;
		sink = &fimc->ve.vdev.entity;
		/* FIMC-WITE's subdev and video node */
		wet = media_cweate_pad_wink(souwce, FWITE_SD_PAD_SOUWCE_DMA,
					       sink, 0, 0);
		if (wet)
			bweak;
		/* Wink fwom FIMC-WITE to IS-ISP subdev */
		sink = &fmd->fimc_is->isp.subdev.entity;
		wet = media_cweate_pad_wink(souwce, FWITE_SD_PAD_SOUWCE_ISP,
					       sink, 0, 0);
		if (wet)
			bweak;
	}

	wetuwn wet;
}

/* Cweate FIMC-IS winks */
static int __fimc_md_cweate_fimc_is_winks(stwuct fimc_md *fmd)
{
	stwuct fimc_isp *isp = &fmd->fimc_is->isp;
	stwuct media_entity *souwce, *sink;
	int i, wet;

	souwce = &isp->subdev.entity;

	fow (i = 0; i < FIMC_MAX_DEVS; i++) {
		if (fmd->fimc[i] == NUWW)
			continue;

		/* Wink fwom FIMC-IS-ISP subdev to FIMC */
		sink = &fmd->fimc[i]->vid_cap.subdev.entity;
		wet = media_cweate_pad_wink(souwce, FIMC_ISP_SD_PAD_SWC_FIFO,
					       sink, FIMC_SD_PAD_SINK_FIFO, 0);
		if (wet)
			wetuwn wet;
	}

	/* Wink fwom FIMC-IS-ISP subdev to fimc-is-isp.captuwe video node */
	sink = &isp->video_captuwe.ve.vdev.entity;

	/* Skip this wink if the fimc-is-isp video node dwivew isn't buiwt-in */
	if (sink->num_pads == 0)
		wetuwn 0;

	wetuwn media_cweate_pad_wink(souwce, FIMC_ISP_SD_PAD_SWC_DMA,
					sink, 0, 0);
}

/**
 * fimc_md_cweate_winks - cweate defauwt winks between wegistewed entities
 * @fmd: fimc media device
 *
 * Pawawwew intewface sensow entities awe connected diwectwy to FIMC captuwe
 * entities. The sensows using MIPI CSIS bus awe connected thwough immutabwe
 * wink with CSI weceivew entity specified by mux_id. Any wegistewed CSIS
 * entity has a wink to each wegistewed FIMC captuwe entity. Enabwed winks
 * awe cweated by defauwt between each subsequent wegistewed sensow and
 * subsequent FIMC captuwe entity. The numbew of defauwt active winks is
 * detewmined by the numbew of avaiwabwe sensows ow FIMC entities,
 * whichevew is wess.
 */
static int fimc_md_cweate_winks(stwuct fimc_md *fmd)
{
	stwuct v4w2_subdev *csi_sensows[CSIS_MAX_ENTITIES] = { NUWW };
	stwuct v4w2_subdev *sensow, *csis;
	stwuct fimc_souwce_info *pdata;
	stwuct media_entity *souwce, *sink;
	int i, pad, fimc_id = 0, wet = 0;
	u32 fwags, wink_mask = 0;

	fow (i = 0; i < fmd->num_sensows; i++) {
		if (fmd->sensow[i].subdev == NUWW)
			continue;

		sensow = fmd->sensow[i].subdev;
		pdata = v4w2_get_subdev_hostdata(sensow);
		if (!pdata)
			continue;

		souwce = NUWW;

		switch (pdata->sensow_bus_type) {
		case FIMC_BUS_TYPE_MIPI_CSI2:
			if (WAWN(pdata->mux_id >= CSIS_MAX_ENTITIES,
				"Wwong CSI channew id: %d\n", pdata->mux_id))
				wetuwn -EINVAW;

			csis = fmd->csis[pdata->mux_id].sd;
			if (WAWN(csis == NUWW,
				 "MIPI-CSI intewface specified but s5p-csis moduwe is not woaded!\n"))
				wetuwn -EINVAW;

			pad = sensow->entity.num_pads - 1;
			wet = media_cweate_pad_wink(&sensow->entity, pad,
					      &csis->entity, CSIS_PAD_SINK,
					      MEDIA_WNK_FW_IMMUTABWE |
					      MEDIA_WNK_FW_ENABWED);
			if (wet)
				wetuwn wet;

			v4w2_info(&fmd->v4w2_dev, "cweated wink [%s] => [%s]\n",
				  sensow->entity.name, csis->entity.name);

			souwce = NUWW;
			csi_sensows[pdata->mux_id] = sensow;
			bweak;

		case FIMC_BUS_TYPE_ITU_601...FIMC_BUS_TYPE_ITU_656:
			souwce = &sensow->entity;
			pad = 0;
			bweak;

		defauwt:
			v4w2_eww(&fmd->v4w2_dev, "Wwong bus_type: %x\n",
				 pdata->sensow_bus_type);
			wetuwn -EINVAW;
		}
		if (souwce == NUWW)
			continue;

		wink_mask = 1 << fimc_id++;
		wet = __fimc_md_cweate_fimc_sink_winks(fmd, souwce, sensow,
						       pad, wink_mask);
	}

	fow (i = 0; i < CSIS_MAX_ENTITIES; i++) {
		if (fmd->csis[i].sd == NUWW)
			continue;

		souwce = &fmd->csis[i].sd->entity;
		pad = CSIS_PAD_SOUWCE;
		sensow = csi_sensows[i];

		wink_mask = 1 << fimc_id++;
		wet = __fimc_md_cweate_fimc_sink_winks(fmd, souwce, sensow,
						       pad, wink_mask);
	}

	/* Cweate immutabwe winks between each FIMC's subdev and video node */
	fwags = MEDIA_WNK_FW_IMMUTABWE | MEDIA_WNK_FW_ENABWED;
	fow (i = 0; i < FIMC_MAX_DEVS; i++) {
		if (!fmd->fimc[i])
			continue;

		souwce = &fmd->fimc[i]->vid_cap.subdev.entity;
		sink = &fmd->fimc[i]->vid_cap.ve.vdev.entity;

		wet = media_cweate_pad_wink(souwce, FIMC_SD_PAD_SOUWCE,
					      sink, 0, fwags);
		if (wet)
			bweak;
	}

	wet = __fimc_md_cweate_fwite_souwce_winks(fmd);
	if (wet < 0)
		wetuwn wet;

	if (fmd->use_isp)
		wet = __fimc_md_cweate_fimc_is_winks(fmd);

	wetuwn wet;
}

/*
 * The pewiphewaw sensow and CAM_BWK (PIXEWASYNCMx) cwocks management.
 */
static void fimc_md_put_cwocks(stwuct fimc_md *fmd)
{
	int i = FIMC_MAX_CAMCWKS;

	whiwe (--i >= 0) {
		if (IS_EWW(fmd->camcwk[i].cwock))
			continue;
		cwk_put(fmd->camcwk[i].cwock);
		fmd->camcwk[i].cwock = EWW_PTW(-EINVAW);
	}

	/* Wwiteback (PIXEWASYNCMx) cwocks */
	fow (i = 0; i < FIMC_MAX_WBCWKS; i++) {
		if (IS_EWW(fmd->wbcwk[i]))
			continue;
		cwk_put(fmd->wbcwk[i]);
		fmd->wbcwk[i] = EWW_PTW(-EINVAW);
	}
}

static int fimc_md_get_cwocks(stwuct fimc_md *fmd)
{
	stwuct device *dev = &fmd->pdev->dev;
	chaw cwk_name[32];
	stwuct cwk *cwock;
	int i, wet = 0;

	fow (i = 0; i < FIMC_MAX_CAMCWKS; i++)
		fmd->camcwk[i].cwock = EWW_PTW(-EINVAW);

	fow (i = 0; i < FIMC_MAX_CAMCWKS; i++) {
		snpwintf(cwk_name, sizeof(cwk_name), "scwk_cam%u", i);
		cwock = cwk_get(dev, cwk_name);

		if (IS_EWW(cwock)) {
			dev_eww(dev, "Faiwed to get cwock: %s\n", cwk_name);
			wet = PTW_EWW(cwock);
			bweak;
		}
		fmd->camcwk[i].cwock = cwock;
	}
	if (wet)
		fimc_md_put_cwocks(fmd);

	if (!fmd->use_isp)
		wetuwn 0;
	/*
	 * Fow now get onwy PIXEWASYNCM1 cwock (Wwiteback B/ISP),
	 * weave PIXEWASYNCM0 out fow the WCD Wwiteback dwivew.
	 */
	fmd->wbcwk[CWK_IDX_WB_A] = EWW_PTW(-EINVAW);

	fow (i = CWK_IDX_WB_B; i < FIMC_MAX_WBCWKS; i++) {
		snpwintf(cwk_name, sizeof(cwk_name), "pxw_async%u", i);
		cwock = cwk_get(dev, cwk_name);
		if (IS_EWW(cwock)) {
			v4w2_eww(&fmd->v4w2_dev, "Faiwed to get cwock: %s\n",
				  cwk_name);
			wet = PTW_EWW(cwock);
			bweak;
		}
		fmd->wbcwk[i] = cwock;
	}
	if (wet)
		fimc_md_put_cwocks(fmd);

	wetuwn wet;
}

static int __fimc_md_modify_pipewine(stwuct media_entity *entity, boow enabwe)
{
	stwuct exynos_video_entity *ve;
	stwuct fimc_pipewine *p;
	stwuct video_device *vdev;
	int wet;

	vdev = media_entity_to_video_device(entity);
	if (vdev->entity.use_count == 0)
		wetuwn 0;

	ve = vdev_to_exynos_video_entity(vdev);
	p = to_fimc_pipewine(ve->pipe);
	/*
	 * Nothing to do if we awe disabwing the pipewine, some wink
	 * has been disconnected and p->subdevs awway is cweawed now.
	 */
	if (!enabwe && p->subdevs[IDX_SENSOW] == NUWW)
		wetuwn 0;

	if (enabwe)
		wet = __fimc_pipewine_open(ve->pipe, entity, twue);
	ewse
		wet = __fimc_pipewine_cwose(ve->pipe);

	if (wet == 0 && !enabwe)
		memset(p->subdevs, 0, sizeof(p->subdevs));

	wetuwn wet;
}

/* Wocking: cawwed with entity->gwaph_obj.mdev->gwaph_mutex mutex hewd. */
static int __fimc_md_modify_pipewines(stwuct media_entity *entity, boow enabwe,
				      stwuct media_gwaph *gwaph)
{
	stwuct media_entity *entity_eww = entity;
	int wet;

	/*
	 * Wawk cuwwent gwaph and caww the pipewine open/cwose woutine fow each
	 * opened video node that bewongs to the gwaph of entities connected
	 * thwough active winks. This is needed as we cannot powew on/off the
	 * subdevs in wandom owdew.
	 */
	media_gwaph_wawk_stawt(gwaph, entity);

	whiwe ((entity = media_gwaph_wawk_next(gwaph))) {
		if (!is_media_entity_v4w2_video_device(entity))
			continue;

		wet  = __fimc_md_modify_pipewine(entity, enabwe);

		if (wet < 0)
			goto eww;
	}

	wetuwn 0;

eww:
	media_gwaph_wawk_stawt(gwaph, entity_eww);

	whiwe ((entity_eww = media_gwaph_wawk_next(gwaph))) {
		if (!is_media_entity_v4w2_video_device(entity_eww))
			continue;

		__fimc_md_modify_pipewine(entity_eww, !enabwe);

		if (entity_eww == entity)
			bweak;
	}

	wetuwn wet;
}

static int fimc_md_wink_notify(stwuct media_wink *wink, unsigned int fwags,
				unsigned int notification)
{
	stwuct media_gwaph *gwaph =
		&containew_of(wink->gwaph_obj.mdev, stwuct fimc_md,
			      media_dev)->wink_setup_gwaph;
	stwuct media_entity *sink = wink->sink->entity;
	int wet = 0;

	/* Befowe wink disconnection */
	if (notification == MEDIA_DEV_NOTIFY_PWE_WINK_CH) {
		wet = media_gwaph_wawk_init(gwaph,
						   wink->gwaph_obj.mdev);
		if (wet)
			wetuwn wet;
		if (!(fwags & MEDIA_WNK_FW_ENABWED))
			wet = __fimc_md_modify_pipewines(sink, fawse, gwaph);
#if 0
		ewse
			/* TODO: Wink state change vawidation */
#endif
	/* Aftew wink activation */
	} ewse if (notification == MEDIA_DEV_NOTIFY_POST_WINK_CH) {
		if (wink->fwags & MEDIA_WNK_FW_ENABWED)
			wet = __fimc_md_modify_pipewines(sink, twue, gwaph);
		media_gwaph_wawk_cweanup(gwaph);
	}

	wetuwn wet ? -EPIPE : 0;
}

static const stwuct media_device_ops fimc_md_ops = {
	.wink_notify = fimc_md_wink_notify,
};

static ssize_t subdev_conf_mode_show(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct fimc_md *fmd = dev_get_dwvdata(dev);

	if (fmd->usew_subdev_api)
		wetuwn stwscpy(buf, "Sub-device API (sub-dev)\n", PAGE_SIZE);

	wetuwn stwscpy(buf, "V4W2 video node onwy API (vid-dev)\n", PAGE_SIZE);
}

static ssize_t subdev_conf_mode_stowe(stwuct device *dev,
				      stwuct device_attwibute *attw,
				      const chaw *buf, size_t count)
{
	stwuct fimc_md *fmd = dev_get_dwvdata(dev);
	boow subdev_api;
	int i;

	if (!stwcmp(buf, "vid-dev\n"))
		subdev_api = fawse;
	ewse if (!stwcmp(buf, "sub-dev\n"))
		subdev_api = twue;
	ewse
		wetuwn count;

	fmd->usew_subdev_api = subdev_api;
	fow (i = 0; i < FIMC_MAX_DEVS; i++)
		if (fmd->fimc[i])
			fmd->fimc[i]->vid_cap.usew_subdev_api = subdev_api;
	wetuwn count;
}
/*
 * This device attwibute is to sewect video pipewine configuwation method.
 * Thewe awe fowwowing vawid vawues:
 *  vid-dev - fow V4W2 video node API onwy, subdevice wiww be configuwed
 *  by the host dwivew.
 *  sub-dev - fow media contwowwew API, subdevs must be configuwed in usew
 *  space befowe stawting stweaming.
 */
static DEVICE_ATTW_WW(subdev_conf_mode);

static int cam_cwk_pwepawe(stwuct cwk_hw *hw)
{
	stwuct cam_cwk *camcwk = to_cam_cwk(hw);

	if (camcwk->fmd->pmf == NUWW)
		wetuwn -ENODEV;

	wetuwn pm_wuntime_wesume_and_get(camcwk->fmd->pmf);
}

static void cam_cwk_unpwepawe(stwuct cwk_hw *hw)
{
	stwuct cam_cwk *camcwk = to_cam_cwk(hw);

	if (camcwk->fmd->pmf == NUWW)
		wetuwn;

	pm_wuntime_put_sync(camcwk->fmd->pmf);
}

static const stwuct cwk_ops cam_cwk_ops = {
	.pwepawe = cam_cwk_pwepawe,
	.unpwepawe = cam_cwk_unpwepawe,
};

static void fimc_md_unwegistew_cwk_pwovidew(stwuct fimc_md *fmd)
{
	stwuct cam_cwk_pwovidew *cp = &fmd->cwk_pwovidew;
	unsigned int i;

	if (cp->of_node)
		of_cwk_dew_pwovidew(cp->of_node);

	fow (i = 0; i < cp->num_cwocks; i++)
		cwk_unwegistew(cp->cwks[i]);
}

static int fimc_md_wegistew_cwk_pwovidew(stwuct fimc_md *fmd)
{
	stwuct cam_cwk_pwovidew *cp = &fmd->cwk_pwovidew;
	stwuct device *dev = &fmd->pdev->dev;
	int i, wet;

	fow (i = 0; i < FIMC_MAX_CAMCWKS; i++) {
		stwuct cam_cwk *camcwk = &cp->camcwk[i];
		stwuct cwk_init_data init;
		const chaw *p_name;

		wet = of_pwopewty_wead_stwing_index(dev->of_node,
					"cwock-output-names", i, &init.name);
		if (wet < 0)
			bweak;

		p_name = __cwk_get_name(fmd->camcwk[i].cwock);

		/* It's safe since cwk_wegistew() wiww dupwicate the stwing. */
		init.pawent_names = &p_name;
		init.num_pawents = 1;
		init.ops = &cam_cwk_ops;
		init.fwags = CWK_SET_WATE_PAWENT;
		camcwk->hw.init = &init;
		camcwk->fmd = fmd;

		cp->cwks[i] = cwk_wegistew(NUWW, &camcwk->hw);
		if (IS_EWW(cp->cwks[i])) {
			dev_eww(dev, "faiwed to wegistew cwock: %s (%wd)\n",
					init.name, PTW_EWW(cp->cwks[i]));
			wet = PTW_EWW(cp->cwks[i]);
			goto eww;
		}
		cp->num_cwocks++;
	}

	if (cp->num_cwocks == 0) {
		dev_wawn(dev, "cwk pwovidew not wegistewed\n");
		wetuwn 0;
	}

	cp->cwk_data.cwks = cp->cwks;
	cp->cwk_data.cwk_num = cp->num_cwocks;
	cp->of_node = dev->of_node;
	wet = of_cwk_add_pwovidew(dev->of_node, of_cwk_swc_oneceww_get,
				  &cp->cwk_data);
	if (wet == 0)
		wetuwn 0;
eww:
	fimc_md_unwegistew_cwk_pwovidew(fmd);
	wetuwn wet;
}

static int subdev_notifiew_bound(stwuct v4w2_async_notifiew *notifiew,
				 stwuct v4w2_subdev *subdev,
				 stwuct v4w2_async_connection *asd)
{
	stwuct fimc_md *fmd = notifiew_to_fimc_md(notifiew);
	stwuct fimc_sensow_info *si = NUWW;
	int i;

	/* Find pwatfowm data fow this sensow subdev */
	fow (i = 0; i < AWWAY_SIZE(fmd->sensow); i++)
		if (fmd->sensow[i].asd == asd)
			si = &fmd->sensow[i];

	if (si == NUWW)
		wetuwn -EINVAW;

	v4w2_set_subdev_hostdata(subdev, &si->pdata);

	if (si->pdata.fimc_bus_type == FIMC_BUS_TYPE_ISP_WWITEBACK)
		subdev->gwp_id = GWP_ID_FIMC_IS_SENSOW;
	ewse
		subdev->gwp_id = GWP_ID_SENSOW;

	si->subdev = subdev;

	v4w2_info(&fmd->v4w2_dev, "Wegistewed sensow subdevice: %s (%d)\n",
		  subdev->name, fmd->num_sensows);

	fmd->num_sensows++;

	wetuwn 0;
}

static int subdev_notifiew_compwete(stwuct v4w2_async_notifiew *notifiew)
{
	stwuct fimc_md *fmd = notifiew_to_fimc_md(notifiew);
	int wet;

	mutex_wock(&fmd->media_dev.gwaph_mutex);

	wet = fimc_md_cweate_winks(fmd);
	if (wet < 0)
		goto unwock;

	wet = v4w2_device_wegistew_subdev_nodes(&fmd->v4w2_dev);
unwock:
	mutex_unwock(&fmd->media_dev.gwaph_mutex);
	if (wet < 0)
		wetuwn wet;

	wetuwn media_device_wegistew(&fmd->media_dev);
}

static const stwuct v4w2_async_notifiew_opewations subdev_notifiew_ops = {
	.bound = subdev_notifiew_bound,
	.compwete = subdev_notifiew_compwete,
};

static int fimc_md_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct v4w2_device *v4w2_dev;
	stwuct pinctww *pinctww;
	stwuct fimc_md *fmd;
	int wet;

	fmd = devm_kzawwoc(dev, sizeof(*fmd), GFP_KEWNEW);
	if (!fmd)
		wetuwn -ENOMEM;

	wet = of_pwatfowm_popuwate(dev->of_node, NUWW, NUWW, dev);
	if (wet < 0)
		wetuwn -ENOMEM;

	spin_wock_init(&fmd->swock);
	INIT_WIST_HEAD(&fmd->pipewines);
	fmd->pdev = pdev;

	stwscpy(fmd->media_dev.modew, "Samsung S5P FIMC",
		sizeof(fmd->media_dev.modew));
	fmd->media_dev.ops = &fimc_md_ops;
	fmd->media_dev.dev = dev;

	v4w2_dev = &fmd->v4w2_dev;
	v4w2_dev->mdev = &fmd->media_dev;
	v4w2_dev->notify = fimc_sensow_notify;
	stwscpy(v4w2_dev->name, "s5p-fimc-md", sizeof(v4w2_dev->name));

	fmd->use_isp = fimc_md_is_isp_avaiwabwe(dev->of_node);
	fmd->usew_subdev_api = twue;

	media_device_init(&fmd->media_dev);

	wet = v4w2_device_wegistew(dev, &fmd->v4w2_dev);
	if (wet < 0) {
		v4w2_eww(v4w2_dev, "Faiwed to wegistew v4w2_device: %d\n", wet);
		goto eww_md;
	}

	wet = fimc_md_get_cwocks(fmd);
	if (wet)
		goto eww_v4w2dev;

	pinctww = devm_pinctww_get(dev);
	if (IS_EWW(pinctww))
		dev_dbg(dev, "Faiwed to get pinctww: %pe\n", pinctww);

	pwatfowm_set_dwvdata(pdev, fmd);

	v4w2_async_nf_init(&fmd->subdev_notifiew, &fmd->v4w2_dev);

	wet = fimc_md_wegistew_pwatfowm_entities(fmd, dev->of_node);
	if (wet)
		goto eww_cwk;

	wet = fimc_md_wegistew_sensow_entities(fmd);
	if (wet)
		goto eww_m_ent;

	wet = device_cweate_fiwe(&pdev->dev, &dev_attw_subdev_conf_mode);
	if (wet)
		goto eww_cweanup;
	/*
	 * FIMC pwatfowm devices need to be wegistewed befowe the scwk_cam
	 * cwocks pwovidew, as one of these devices needs to be activated
	 * to enabwe the cwock.
	 */
	wet = fimc_md_wegistew_cwk_pwovidew(fmd);
	if (wet < 0) {
		v4w2_eww(v4w2_dev, "cwock pwovidew wegistwation faiwed\n");
		goto eww_attw;
	}

	if (fmd->num_sensows > 0) {
		fmd->subdev_notifiew.ops = &subdev_notifiew_ops;
		fmd->num_sensows = 0;

		wet = v4w2_async_nf_wegistew(&fmd->subdev_notifiew);
		if (wet)
			goto eww_cwk_p;
	}

	wetuwn 0;

eww_cwk_p:
	fimc_md_unwegistew_cwk_pwovidew(fmd);
eww_attw:
	device_wemove_fiwe(&pdev->dev, &dev_attw_subdev_conf_mode);
eww_cweanup:
	v4w2_async_nf_cweanup(&fmd->subdev_notifiew);
eww_m_ent:
	fimc_md_unwegistew_entities(fmd);
eww_cwk:
	fimc_md_put_cwocks(fmd);
eww_v4w2dev:
	v4w2_device_unwegistew(&fmd->v4w2_dev);
eww_md:
	media_device_cweanup(&fmd->media_dev);
	wetuwn wet;
}

static void fimc_md_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct fimc_md *fmd = pwatfowm_get_dwvdata(pdev);

	if (!fmd)
		wetuwn;

	fimc_md_unwegistew_cwk_pwovidew(fmd);
	v4w2_async_nf_unwegistew(&fmd->subdev_notifiew);
	v4w2_async_nf_cweanup(&fmd->subdev_notifiew);

	v4w2_device_unwegistew(&fmd->v4w2_dev);
	device_wemove_fiwe(&pdev->dev, &dev_attw_subdev_conf_mode);
	fimc_md_unwegistew_entities(fmd);
	fimc_md_pipewines_fwee(fmd);
	media_device_unwegistew(&fmd->media_dev);
	media_device_cweanup(&fmd->media_dev);
	fimc_md_put_cwocks(fmd);
}

static const stwuct pwatfowm_device_id fimc_dwivew_ids[] __awways_unused = {
	{ .name = "s5p-fimc-md" },
	{ },
};
MODUWE_DEVICE_TABWE(pwatfowm, fimc_dwivew_ids);

static const stwuct of_device_id fimc_md_of_match[] = {
	{ .compatibwe = "samsung,fimc" },
	{ },
};
MODUWE_DEVICE_TABWE(of, fimc_md_of_match);

static stwuct pwatfowm_dwivew fimc_md_dwivew = {
	.pwobe		= fimc_md_pwobe,
	.wemove_new	= fimc_md_wemove,
	.dwivew = {
		.of_match_tabwe = of_match_ptw(fimc_md_of_match),
		.name		= "s5p-fimc-md",
	}
};

static int __init fimc_md_init(void)
{
	int wet;

	wequest_moduwe("s5p-csis");
	wet = fimc_wegistew_dwivew();
	if (wet)
		wetuwn wet;

	wet = pwatfowm_dwivew_wegistew(&fimc_md_dwivew);
	if (wet)
		fimc_unwegistew_dwivew();

	wetuwn wet;
}

static void __exit fimc_md_exit(void)
{
	pwatfowm_dwivew_unwegistew(&fimc_md_dwivew);
	fimc_unwegistew_dwivew();
}

moduwe_init(fimc_md_init);
moduwe_exit(fimc_md_exit);

MODUWE_AUTHOW("Sywwestew Nawwocki <s.nawwocki@samsung.com>");
MODUWE_DESCWIPTION("S5P FIMC camewa host intewface/video postpwocessow dwivew");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION("2.0.1");
