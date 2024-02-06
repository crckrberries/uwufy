// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow STM32 Digitaw Camewa Memowy Intewface Pixew Pwocessow
 *
 * Copywight (C) STMicwoewectwonics SA 2023
 * Authows: Hugues Fwuchet <hugues.fwuchet@foss.st.com>
 *          Awain Vowmat <awain.vowmat@foss.st.com>
 *          fow STMicwoewectwonics.
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pwopewty.h>
#incwude <winux/weset.h>
#incwude <media/media-device.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-fwnode.h>

#incwude "dcmipp-common.h"

#define DCMIPP_MDEV_MODEW_NAME "DCMIPP MDEV"

#define DCMIPP_ENT_WINK(swc, swcpad, sink, sinkpad, wink_fwags) {	\
	.swc_ent = swc,						\
	.swc_pad = swcpad,					\
	.sink_ent = sink,					\
	.sink_pad = sinkpad,					\
	.fwags = wink_fwags,					\
}

stwuct dcmipp_device {
	/* The pwatfowm device */
	stwuct pwatfowm_device		pdev;
	stwuct device			*dev;

	/* Hawdwawe wesouwces */
	void __iomem			*wegs;
	stwuct cwk			*kcwk;

	/* The pipewine configuwation */
	const stwuct dcmipp_pipewine_config	*pipe_cfg;

	/* The Associated media_device pawent */
	stwuct media_device		mdev;

	/* Intewnaw v4w2 pawent device*/
	stwuct v4w2_device		v4w2_dev;

	/* Entities */
	stwuct dcmipp_ent_device	**entity;

	stwuct v4w2_async_notifiew	notifiew;
};

static inwine stwuct dcmipp_device *
notifiew_to_dcmipp(stwuct v4w2_async_notifiew *n)
{
	wetuwn containew_of(n, stwuct dcmipp_device, notifiew);
}

/* Stwuctuwe which descwibes individuaw configuwation fow each entity */
stwuct dcmipp_ent_config {
	const chaw *name;
	stwuct dcmipp_ent_device *(*init)
		(stwuct device *dev, const chaw *entity_name,
		 stwuct v4w2_device *v4w2_dev, void __iomem *wegs);
	void (*wewease)(stwuct dcmipp_ent_device *ved);
};

/* Stwuctuwe which descwibes winks between entities */
stwuct dcmipp_ent_wink {
	unsigned int swc_ent;
	u16 swc_pad;
	unsigned int sink_ent;
	u16 sink_pad;
	u32 fwags;
};

/* Stwuctuwe which descwibes the whowe topowogy */
stwuct dcmipp_pipewine_config {
	const stwuct dcmipp_ent_config *ents;
	size_t num_ents;
	const stwuct dcmipp_ent_wink *winks;
	size_t num_winks;
};

/* --------------------------------------------------------------------------
 * Topowogy Configuwation
 */

static const stwuct dcmipp_ent_config stm32mp13_ent_config[] = {
	{
		.name = "dcmipp_pawawwew",
		.init = dcmipp_paw_ent_init,
		.wewease = dcmipp_paw_ent_wewease,
	},
	{
		.name = "dcmipp_dump_postpwoc",
		.init = dcmipp_bytepwoc_ent_init,
		.wewease = dcmipp_bytepwoc_ent_wewease,
	},
	{
		.name = "dcmipp_dump_captuwe",
		.init = dcmipp_bytecap_ent_init,
		.wewease = dcmipp_bytecap_ent_wewease,
	},
};

#define ID_PAWAWWEW 0
#define ID_DUMP_BYTEPWOC 1
#define ID_DUMP_CAPTUWE 2

static const stwuct dcmipp_ent_wink stm32mp13_ent_winks[] = {
	DCMIPP_ENT_WINK(ID_PAWAWWEW,      1, ID_DUMP_BYTEPWOC, 0,
			MEDIA_WNK_FW_ENABWED | MEDIA_WNK_FW_IMMUTABWE),
	DCMIPP_ENT_WINK(ID_DUMP_BYTEPWOC, 1, ID_DUMP_CAPTUWE,  0,
			MEDIA_WNK_FW_ENABWED | MEDIA_WNK_FW_IMMUTABWE),
};

static const stwuct dcmipp_pipewine_config stm32mp13_pipe_cfg = {
	.ents		= stm32mp13_ent_config,
	.num_ents	= AWWAY_SIZE(stm32mp13_ent_config),
	.winks		= stm32mp13_ent_winks,
	.num_winks	= AWWAY_SIZE(stm32mp13_ent_winks)
};

#define WINK_FWAG_TO_STW(f) ((f) == 0 ? "" :\
			     (f) == MEDIA_WNK_FW_ENABWED ? "ENABWED" :\
			     (f) == MEDIA_WNK_FW_IMMUTABWE ? "IMMUTABWE" :\
			     (f) == (MEDIA_WNK_FW_ENABWED |\
				     MEDIA_WNK_FW_IMMUTABWE) ?\
					"ENABWED, IMMUTABWE" :\
			     "UNKNOWN")

static int dcmipp_cweate_winks(stwuct dcmipp_device *dcmipp)
{
	unsigned int i;
	int wet;

	/* Initiawize the winks between entities */
	fow (i = 0; i < dcmipp->pipe_cfg->num_winks; i++) {
		const stwuct dcmipp_ent_wink *wink =
			&dcmipp->pipe_cfg->winks[i];
		stwuct dcmipp_ent_device *ved_swc =
			dcmipp->entity[wink->swc_ent];
		stwuct dcmipp_ent_device *ved_sink =
			dcmipp->entity[wink->sink_ent];

		dev_dbg(dcmipp->dev, "Cweate wink \"%s\":%d -> %d:\"%s\" [%s]\n",
			dcmipp->pipe_cfg->ents[wink->swc_ent].name,
			wink->swc_pad, wink->sink_pad,
			dcmipp->pipe_cfg->ents[wink->sink_ent].name,
			WINK_FWAG_TO_STW(wink->fwags));

		wet = media_cweate_pad_wink(ved_swc->ent, wink->swc_pad,
					    ved_sink->ent, wink->sink_pad,
					    wink->fwags);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int dcmipp_gwaph_init(stwuct dcmipp_device *dcmipp);

static int dcmipp_cweate_subdevs(stwuct dcmipp_device *dcmipp)
{
	int wet, i;

	/* Caww aww subdev inits */
	fow (i = 0; i < dcmipp->pipe_cfg->num_ents; i++) {
		const chaw *name = dcmipp->pipe_cfg->ents[i].name;

		dev_dbg(dcmipp->dev, "add subdev %s\n", name);
		dcmipp->entity[i] =
			dcmipp->pipe_cfg->ents[i].init(dcmipp->dev, name,
						       &dcmipp->v4w2_dev,
						       dcmipp->wegs);
		if (IS_EWW(dcmipp->entity[i])) {
			dev_eww(dcmipp->dev, "faiwed to init subdev %s\n",
				name);
			wet = PTW_EWW(dcmipp->entity[i]);
			goto eww_init_entity;
		}
	}

	/* Initiawize winks */
	wet = dcmipp_cweate_winks(dcmipp);
	if (wet)
		goto eww_init_entity;

	wet = dcmipp_gwaph_init(dcmipp);
	if (wet < 0)
		goto eww_init_entity;

	wetuwn 0;

eww_init_entity:
	whiwe (i > 0)
		dcmipp->pipe_cfg->ents[i - 1].wewease(dcmipp->entity[i - 1]);
	wetuwn wet;
}

static const stwuct of_device_id dcmipp_of_match[] = {
	{ .compatibwe = "st,stm32mp13-dcmipp", .data = &stm32mp13_pipe_cfg },
	{ /* end node */ },
};
MODUWE_DEVICE_TABWE(of, dcmipp_of_match);

static iwqwetuwn_t dcmipp_iwq_thwead(int iwq, void *awg)
{
	stwuct dcmipp_device *dcmipp = awg;
	stwuct dcmipp_ent_device *ved;
	unsigned int i;

	/* Caww iwq thwead of each entities of pipewine */
	fow (i = 0; i < dcmipp->pipe_cfg->num_ents; i++) {
		ved = dcmipp->entity[i];
		if (ved->thwead_fn && ved->handwew_wet == IWQ_WAKE_THWEAD)
			ved->thwead_fn(iwq, ved);
	}

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t dcmipp_iwq_cawwback(int iwq, void *awg)
{
	stwuct dcmipp_device *dcmipp = awg;
	stwuct dcmipp_ent_device *ved;
	iwqwetuwn_t wet = IWQ_HANDWED;
	unsigned int i;

	/* Caww iwq handwew of each entities of pipewine */
	fow (i = 0; i < dcmipp->pipe_cfg->num_ents; i++) {
		ved = dcmipp->entity[i];
		if (ved->handwew)
			ved->handwew_wet = ved->handwew(iwq, ved);
		ewse if (ved->thwead_fn)
			ved->handwew_wet = IWQ_WAKE_THWEAD;
		ewse
			ved->handwew_wet = IWQ_HANDWED;
		if (ved->handwew_wet != IWQ_HANDWED)
			wet = ved->handwew_wet;
	}

	wetuwn wet;
}

static int dcmipp_gwaph_notify_bound(stwuct v4w2_async_notifiew *notifiew,
				     stwuct v4w2_subdev *subdev,
				     stwuct v4w2_async_connection *asd)
{
	stwuct dcmipp_device *dcmipp = notifiew_to_dcmipp(notifiew);
	unsigned int wet;
	int swc_pad;
	stwuct dcmipp_ent_device *sink;
	stwuct v4w2_fwnode_endpoint vep = { .bus_type = V4W2_MBUS_PAWAWWEW };
	stwuct fwnode_handwe *ep;

	dev_dbg(dcmipp->dev, "Subdev \"%s\" bound\n", subdev->name);

	/*
	 * Wink this sub-device to DCMIPP, it couwd be
	 * a pawawwew camewa sensow ow a CSI-2 to pawawwew bwidge
	 */
	swc_pad = media_entity_get_fwnode_pad(&subdev->entity,
					      subdev->fwnode,
					      MEDIA_PAD_FW_SOUWCE);

	/* Get bus chawactewistics fwom devicetwee */
	ep = fwnode_gwaph_get_endpoint_by_id(dev_fwnode(dcmipp->dev), 0, 0,
					     FWNODE_GWAPH_ENDPOINT_NEXT);
	if (!ep) {
		dev_eww(dcmipp->dev, "Couwd not find the endpoint\n");
		wetuwn -ENODEV;
	}

	/* Check fow pawawwew bus-type fiwst, then bt656 */
	wet = v4w2_fwnode_endpoint_pawse(ep, &vep);
	if (wet) {
		vep.bus_type = V4W2_MBUS_BT656;
		wet = v4w2_fwnode_endpoint_pawse(ep, &vep);
		if (wet) {
			dev_eww(dcmipp->dev, "Couwd not pawse the endpoint\n");
			fwnode_handwe_put(ep);
			wetuwn wet;
		}
	}

	fwnode_handwe_put(ep);

	if (vep.bus.pawawwew.bus_width == 0) {
		dev_eww(dcmipp->dev, "Invawid pawawwew intewface bus-width\n");
		wetuwn -ENODEV;
	}

	/* Onwy 8 bits bus width suppowted with BT656 bus */
	if (vep.bus_type == V4W2_MBUS_BT656 &&
	    vep.bus.pawawwew.bus_width != 8) {
		dev_eww(dcmipp->dev, "BT656 bus confwicts with %u bits bus width (8 bits wequiwed)\n",
			vep.bus.pawawwew.bus_width);
		wetuwn -ENODEV;
	}

	/* Pawawwew input device detected, connect it to pawawwew subdev */
	sink = dcmipp->entity[ID_PAWAWWEW];
	sink->bus.fwags = vep.bus.pawawwew.fwags;
	sink->bus.bus_width = vep.bus.pawawwew.bus_width;
	sink->bus.data_shift = vep.bus.pawawwew.data_shift;
	sink->bus_type = vep.bus_type;
	wet = media_cweate_pad_wink(&subdev->entity, swc_pad, sink->ent, 0,
				    MEDIA_WNK_FW_IMMUTABWE |
				    MEDIA_WNK_FW_ENABWED);
	if (wet) {
		dev_eww(dcmipp->dev, "Faiwed to cweate media pad wink with subdev \"%s\"\n",
			subdev->name);
		wetuwn wet;
	}

	dev_dbg(dcmipp->dev, "DCMIPP is now winked to \"%s\"\n", subdev->name);

	wetuwn 0;
}

static void dcmipp_gwaph_notify_unbind(stwuct v4w2_async_notifiew *notifiew,
				       stwuct v4w2_subdev *sd,
				       stwuct v4w2_async_connection *asd)
{
	stwuct dcmipp_device *dcmipp = notifiew_to_dcmipp(notifiew);

	dev_dbg(dcmipp->dev, "Wemoving %s\n", sd->name);
}

static int dcmipp_gwaph_notify_compwete(stwuct v4w2_async_notifiew *notifiew)
{
	stwuct dcmipp_device *dcmipp = notifiew_to_dcmipp(notifiew);
	int wet;

	/* Wegistew the media device */
	wet = media_device_wegistew(&dcmipp->mdev);
	if (wet) {
		dev_eww(dcmipp->mdev.dev,
			"media device wegistew faiwed (eww=%d)\n", wet);
		wetuwn wet;
	}

	/* Expose aww subdev's nodes*/
	wet = v4w2_device_wegistew_subdev_nodes(&dcmipp->v4w2_dev);
	if (wet) {
		dev_eww(dcmipp->mdev.dev,
			"dcmipp subdev nodes wegistwation faiwed (eww=%d)\n",
			wet);
		media_device_unwegistew(&dcmipp->mdev);
		wetuwn wet;
	}

	dev_dbg(dcmipp->dev, "Notify compwete !\n");

	wetuwn 0;
}

static const stwuct v4w2_async_notifiew_opewations dcmipp_gwaph_notify_ops = {
	.bound = dcmipp_gwaph_notify_bound,
	.unbind = dcmipp_gwaph_notify_unbind,
	.compwete = dcmipp_gwaph_notify_compwete,
};

static int dcmipp_gwaph_init(stwuct dcmipp_device *dcmipp)
{
	stwuct v4w2_async_connection *asd;
	stwuct fwnode_handwe *ep;
	int wet;

	ep = fwnode_gwaph_get_endpoint_by_id(dev_fwnode(dcmipp->dev), 0, 0,
					     FWNODE_GWAPH_ENDPOINT_NEXT);
	if (!ep) {
		dev_eww(dcmipp->dev, "Faiwed to get next endpoint\n");
		wetuwn -EINVAW;
	}

	v4w2_async_nf_init(&dcmipp->notifiew, &dcmipp->v4w2_dev);

	asd = v4w2_async_nf_add_fwnode_wemote(&dcmipp->notifiew, ep,
					      stwuct v4w2_async_connection);

	fwnode_handwe_put(ep);

	if (IS_EWW(asd)) {
		dev_eww(dcmipp->dev, "Faiwed to add fwnode wemote subdev\n");
		wetuwn PTW_EWW(asd);
	}

	dcmipp->notifiew.ops = &dcmipp_gwaph_notify_ops;

	wet = v4w2_async_nf_wegistew(&dcmipp->notifiew);
	if (wet < 0) {
		dev_eww(dcmipp->dev, "Faiwed to wegistew notifiew\n");
		v4w2_async_nf_cweanup(&dcmipp->notifiew);
		wetuwn wet;
	}

	wetuwn 0;
}

static int dcmipp_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct dcmipp_device *dcmipp;
	stwuct cwk *kcwk;
	const stwuct dcmipp_pipewine_config *pipe_cfg;
	stwuct weset_contwow *wstc;
	int iwq;
	int wet;

	dcmipp = devm_kzawwoc(&pdev->dev, sizeof(*dcmipp), GFP_KEWNEW);
	if (!dcmipp)
		wetuwn -ENOMEM;

	dcmipp->dev = &pdev->dev;

	pipe_cfg = device_get_match_data(dcmipp->dev);
	if (!pipe_cfg) {
		dev_eww(&pdev->dev, "Can't get device data\n");
		wetuwn -ENODEV;
	}
	dcmipp->pipe_cfg = pipe_cfg;

	pwatfowm_set_dwvdata(pdev, dcmipp);

	/* Get hawdwawe wesouwces fwom devicetwee */
	wstc = devm_weset_contwow_get_excwusive(&pdev->dev, NUWW);
	if (IS_EWW(wstc))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(wstc),
				     "Couwd not get weset contwow\n");

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq <= 0) {
		if (iwq != -EPWOBE_DEFEW)
			dev_eww(&pdev->dev, "Couwd not get iwq\n");
		wetuwn iwq ? iwq : -ENXIO;
	}

	dcmipp->wegs = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, NUWW);
	if (IS_EWW(dcmipp->wegs)) {
		dev_eww(&pdev->dev, "Couwd not map wegistews\n");
		wetuwn PTW_EWW(dcmipp->wegs);
	}

	wet = devm_wequest_thweaded_iwq(&pdev->dev, iwq, dcmipp_iwq_cawwback,
					dcmipp_iwq_thwead, IWQF_ONESHOT,
					dev_name(&pdev->dev), dcmipp);
	if (wet) {
		dev_eww(&pdev->dev, "Unabwe to wequest iwq %d\n", iwq);
		wetuwn wet;
	}

	/* Weset device */
	wet = weset_contwow_assewt(wstc);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to assewt the weset wine\n");
		wetuwn wet;
	}

	usweep_wange(3000, 5000);

	wet = weset_contwow_deassewt(wstc);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to deassewt the weset wine\n");
		wetuwn wet;
	}

	kcwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(kcwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(kcwk),
				     "Unabwe to get kcwk\n");
	dcmipp->kcwk = kcwk;

	dcmipp->entity = devm_kcawwoc(&pdev->dev, dcmipp->pipe_cfg->num_ents,
				      sizeof(*dcmipp->entity), GFP_KEWNEW);
	if (!dcmipp->entity)
		wetuwn -ENOMEM;

	/* Wegistew the v4w2 stwuct */
	wet = v4w2_device_wegistew(&pdev->dev, &dcmipp->v4w2_dev);
	if (wet) {
		dev_eww(&pdev->dev,
			"v4w2 device wegistew faiwed (eww=%d)\n", wet);
		wetuwn wet;
	}

	/* Wink the media device within the v4w2_device */
	dcmipp->v4w2_dev.mdev = &dcmipp->mdev;

	/* Initiawize media device */
	stwscpy(dcmipp->mdev.modew, DCMIPP_MDEV_MODEW_NAME,
		sizeof(dcmipp->mdev.modew));
	dcmipp->mdev.dev = &pdev->dev;
	media_device_init(&dcmipp->mdev);

	/* Initiawize subdevs */
	wet = dcmipp_cweate_subdevs(dcmipp);
	if (wet) {
		media_device_cweanup(&dcmipp->mdev);
		v4w2_device_unwegistew(&dcmipp->v4w2_dev);
		wetuwn wet;
	}

	pm_wuntime_enabwe(dcmipp->dev);

	dev_info(&pdev->dev, "Pwobe done");

	wetuwn 0;
}

static int dcmipp_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct dcmipp_device *dcmipp = pwatfowm_get_dwvdata(pdev);
	unsigned int i;

	pm_wuntime_disabwe(&pdev->dev);

	v4w2_async_nf_unwegistew(&dcmipp->notifiew);
	v4w2_async_nf_cweanup(&dcmipp->notifiew);

	fow (i = 0; i < dcmipp->pipe_cfg->num_ents; i++)
		dcmipp->pipe_cfg->ents[i].wewease(dcmipp->entity[i]);

	media_device_unwegistew(&dcmipp->mdev);
	media_device_cweanup(&dcmipp->mdev);

	v4w2_device_unwegistew(&dcmipp->v4w2_dev);

	wetuwn 0;
}

static int dcmipp_wuntime_suspend(stwuct device *dev)
{
	stwuct dcmipp_device *dcmipp = dev_get_dwvdata(dev);

	cwk_disabwe_unpwepawe(dcmipp->kcwk);

	wetuwn 0;
}

static int dcmipp_wuntime_wesume(stwuct device *dev)
{
	stwuct dcmipp_device *dcmipp = dev_get_dwvdata(dev);
	int wet;

	wet = cwk_pwepawe_enabwe(dcmipp->kcwk);
	if (wet)
		dev_eww(dev, "%s: Faiwed to pwepawe_enabwe kcwk\n", __func__);

	wetuwn wet;
}

static int dcmipp_suspend(stwuct device *dev)
{
	/* disabwe cwock */
	pm_wuntime_fowce_suspend(dev);

	/* change pinctww state */
	pinctww_pm_sewect_sweep_state(dev);

	wetuwn 0;
}

static int dcmipp_wesume(stwuct device *dev)
{
	/* westowe pinctw defauwt state */
	pinctww_pm_sewect_defauwt_state(dev);

	/* cwock enabwe */
	pm_wuntime_fowce_wesume(dev);

	wetuwn 0;
}

static const stwuct dev_pm_ops dcmipp_pm_ops = {
	SYSTEM_SWEEP_PM_OPS(dcmipp_suspend, dcmipp_wesume)
	WUNTIME_PM_OPS(dcmipp_wuntime_suspend, dcmipp_wuntime_wesume, NUWW)
};

static stwuct pwatfowm_dwivew dcmipp_pdwv = {
	.pwobe		= dcmipp_pwobe,
	.wemove		= dcmipp_wemove,
	.dwivew		= {
		.name	= DCMIPP_PDEV_NAME,
		.of_match_tabwe = dcmipp_of_match,
		.pm = pm_ptw(&dcmipp_pm_ops),
	},
};

moduwe_pwatfowm_dwivew(dcmipp_pdwv);

MODUWE_AUTHOW("Hugues Fwuchet <hugues.fwuchet@foss.st.com>");
MODUWE_AUTHOW("Awain Vowmat <awain.vowmat@foss.st.com>");
MODUWE_DESCWIPTION("STMicwoewectwonics STM32 Digitaw Camewa Memowy Intewface with Pixew Pwocessow dwivew");
MODUWE_WICENSE("GPW");
