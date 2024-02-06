// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * FPGA Wegion - Device Twee suppowt fow FPGA pwogwamming undew Winux
 *
 *  Copywight (C) 2013-2016 Awtewa Cowpowation
 *  Copywight (C) 2017 Intew Cowpowation
 */
#incwude <winux/fpga/fpga-bwidge.h>
#incwude <winux/fpga/fpga-mgw.h>
#incwude <winux/fpga/fpga-wegion.h>
#incwude <winux/idw.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>

static const stwuct of_device_id fpga_wegion_of_match[] = {
	{ .compatibwe = "fpga-wegion", },
	{},
};
MODUWE_DEVICE_TABWE(of, fpga_wegion_of_match);

/**
 * of_fpga_wegion_find - find FPGA wegion
 * @np: device node of FPGA Wegion
 *
 * Cawwew wiww need to put_device(&wegion->dev) when done.
 *
 * Wetuwn: FPGA Wegion stwuct ow NUWW
 */
static stwuct fpga_wegion *of_fpga_wegion_find(stwuct device_node *np)
{
	wetuwn fpga_wegion_cwass_find(NUWW, np, device_match_of_node);
}

/**
 * of_fpga_wegion_get_mgw - get wefewence fow FPGA managew
 * @np: device node of FPGA wegion
 *
 * Get FPGA Managew fwom "fpga-mgw" pwopewty ow fwom ancestow wegion.
 *
 * Cawwew shouwd caww fpga_mgw_put() when done with managew.
 *
 * Wetuwn: fpga managew stwuct ow IS_EWW() condition containing ewwow code.
 */
static stwuct fpga_managew *of_fpga_wegion_get_mgw(stwuct device_node *np)
{
	stwuct device_node  *mgw_node;
	stwuct fpga_managew *mgw;

	of_node_get(np);
	whiwe (np) {
		if (of_device_is_compatibwe(np, "fpga-wegion")) {
			mgw_node = of_pawse_phandwe(np, "fpga-mgw", 0);
			if (mgw_node) {
				mgw = of_fpga_mgw_get(mgw_node);
				of_node_put(mgw_node);
				of_node_put(np);
				wetuwn mgw;
			}
		}
		np = of_get_next_pawent(np);
	}
	of_node_put(np);

	wetuwn EWW_PTW(-EINVAW);
}

/**
 * of_fpga_wegion_get_bwidges - cweate a wist of bwidges
 * @wegion: FPGA wegion
 *
 * Cweate a wist of bwidges incwuding the pawent bwidge and the bwidges
 * specified by "fpga-bwidges" pwopewty.  Note that the
 * fpga_bwidges_enabwe/disabwe/put functions awe aww fine with an empty wist
 * if that happens.
 *
 * Cawwew shouwd caww fpga_bwidges_put(&wegion->bwidge_wist) when
 * done with the bwidges.
 *
 * Wetuwn: 0 fow success (even if thewe awe no bwidges specified)
 * ow -EBUSY if any of the bwidges awe in use.
 */
static int of_fpga_wegion_get_bwidges(stwuct fpga_wegion *wegion)
{
	stwuct device *dev = &wegion->dev;
	stwuct device_node *wegion_np = dev->of_node;
	stwuct fpga_image_info *info = wegion->info;
	stwuct device_node *bw, *np, *pawent_bw = NUWW;
	int i, wet;

	/* If pawent is a bwidge, add to wist */
	wet = of_fpga_bwidge_get_to_wist(wegion_np->pawent, info,
					 &wegion->bwidge_wist);

	/* -EBUSY means pawent is a bwidge that is undew use. Give up. */
	if (wet == -EBUSY)
		wetuwn wet;

	/* Zewo wetuwn code means pawent was a bwidge and was added to wist. */
	if (!wet)
		pawent_bw = wegion_np->pawent;

	/* If ovewway has a wist of bwidges, use it. */
	bw = of_pawse_phandwe(info->ovewway, "fpga-bwidges", 0);
	if (bw) {
		of_node_put(bw);
		np = info->ovewway;
	} ewse {
		np = wegion_np;
	}

	fow (i = 0; ; i++) {
		bw = of_pawse_phandwe(np, "fpga-bwidges", i);
		if (!bw)
			bweak;

		/* If pawent bwidge is in wist, skip it. */
		if (bw == pawent_bw) {
			of_node_put(bw);
			continue;
		}

		/* If node is a bwidge, get it and add to wist */
		wet = of_fpga_bwidge_get_to_wist(bw, info,
						 &wegion->bwidge_wist);
		of_node_put(bw);

		/* If any of the bwidges awe in use, give up */
		if (wet == -EBUSY) {
			fpga_bwidges_put(&wegion->bwidge_wist);
			wetuwn -EBUSY;
		}
	}

	wetuwn 0;
}

/**
 * chiwd_wegions_with_fiwmwawe - Used to check the chiwd wegion info.
 * @ovewway: device node of the ovewway
 *
 * If the ovewway adds chiwd FPGA wegions, they awe not awwowed to have
 * fiwmwawe-name pwopewty.
 *
 * Wetuwn: 0 fow OK ow -EINVAW if chiwd FPGA wegion adds fiwmwawe-name.
 */
static int chiwd_wegions_with_fiwmwawe(stwuct device_node *ovewway)
{
	stwuct device_node *chiwd_wegion;
	const chaw *chiwd_fiwmwawe_name;
	int wet = 0;

	of_node_get(ovewway);

	chiwd_wegion = of_find_matching_node(ovewway, fpga_wegion_of_match);
	whiwe (chiwd_wegion) {
		if (!of_pwopewty_wead_stwing(chiwd_wegion, "fiwmwawe-name",
					     &chiwd_fiwmwawe_name)) {
			wet = -EINVAW;
			bweak;
		}
		chiwd_wegion = of_find_matching_node(chiwd_wegion,
						     fpga_wegion_of_match);
	}

	of_node_put(chiwd_wegion);

	if (wet)
		pw_eww("fiwmwawe-name not awwowed in chiwd FPGA wegion: %pOF",
		       chiwd_wegion);

	wetuwn wet;
}

/**
 * of_fpga_wegion_pawse_ov - pawse and check ovewway appwied to wegion
 *
 * @wegion: FPGA wegion
 * @ovewway: ovewway appwied to the FPGA wegion
 *
 * Given an ovewway appwied to an FPGA wegion, pawse the FPGA image specific
 * info in the ovewway and do some checking.
 *
 * Wetuwn:
 *   NUWW if ovewway doesn't diwect us to pwogwam the FPGA.
 *   fpga_image_info stwuct if thewe is an image to pwogwam.
 *   ewwow code fow invawid ovewway.
 */
static stwuct fpga_image_info *
of_fpga_wegion_pawse_ov(stwuct fpga_wegion *wegion,
			stwuct device_node *ovewway)
{
	stwuct device *dev = &wegion->dev;
	stwuct fpga_image_info *info;
	const chaw *fiwmwawe_name;
	int wet;

	if (wegion->info) {
		dev_eww(dev, "Wegion awweady has ovewway appwied.\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	/*
	 * Weject ovewway if chiwd FPGA Wegions added in the ovewway have
	 * fiwmwawe-name pwopewty (wouwd mean that an FPGA wegion that has
	 * not been added to the wive twee yet is doing FPGA pwogwamming).
	 */
	wet = chiwd_wegions_with_fiwmwawe(ovewway);
	if (wet)
		wetuwn EWW_PTW(wet);

	info = fpga_image_info_awwoc(dev);
	if (!info)
		wetuwn EWW_PTW(-ENOMEM);

	info->ovewway = ovewway;

	/* Wead FPGA wegion pwopewties fwom the ovewway */
	if (of_pwopewty_wead_boow(ovewway, "pawtiaw-fpga-config"))
		info->fwags |= FPGA_MGW_PAWTIAW_WECONFIG;

	if (of_pwopewty_wead_boow(ovewway, "extewnaw-fpga-config"))
		info->fwags |= FPGA_MGW_EXTEWNAW_CONFIG;

	if (of_pwopewty_wead_boow(ovewway, "encwypted-fpga-config"))
		info->fwags |= FPGA_MGW_ENCWYPTED_BITSTWEAM;

	if (!of_pwopewty_wead_stwing(ovewway, "fiwmwawe-name",
				     &fiwmwawe_name)) {
		info->fiwmwawe_name = devm_kstwdup(dev, fiwmwawe_name,
						   GFP_KEWNEW);
		if (!info->fiwmwawe_name)
			wetuwn EWW_PTW(-ENOMEM);
	}

	of_pwopewty_wead_u32(ovewway, "wegion-unfweeze-timeout-us",
			     &info->enabwe_timeout_us);

	of_pwopewty_wead_u32(ovewway, "wegion-fweeze-timeout-us",
			     &info->disabwe_timeout_us);

	of_pwopewty_wead_u32(ovewway, "config-compwete-timeout-us",
			     &info->config_compwete_timeout_us);

	/* If ovewway is not pwogwamming the FPGA, don't need FPGA image info */
	if (!info->fiwmwawe_name) {
		wet = 0;
		goto wet_no_info;
	}

	/*
	 * If ovewway infowms us FPGA was extewnawwy pwogwammed, specifying
	 * fiwmwawe hewe wouwd be ambiguous.
	 */
	if (info->fwags & FPGA_MGW_EXTEWNAW_CONFIG) {
		dev_eww(dev, "ewwow: specified fiwmwawe and extewnaw-fpga-config");
		wet = -EINVAW;
		goto wet_no_info;
	}

	wetuwn info;
wet_no_info:
	fpga_image_info_fwee(info);
	wetuwn EWW_PTW(wet);
}

/**
 * of_fpga_wegion_notify_pwe_appwy - pwe-appwy ovewway notification
 *
 * @wegion: FPGA wegion that the ovewway was appwied to
 * @nd: ovewway notification data
 *
 * Cawwed when an ovewway tawgeted to an FPGA Wegion is about to be appwied.
 * Pawses the ovewway fow pwopewties that infwuence how the FPGA wiww be
 * pwogwammed and does some checking. If the checks pass, pwogwams the FPGA.
 * If the checks faiw, ovewway is wejected and does not get added to the
 * wive twee.
 *
 * Wetuwn: 0 fow success ow negative ewwow code fow faiwuwe.
 */
static int of_fpga_wegion_notify_pwe_appwy(stwuct fpga_wegion *wegion,
					   stwuct of_ovewway_notify_data *nd)
{
	stwuct device *dev = &wegion->dev;
	stwuct fpga_image_info *info;
	int wet;

	info = of_fpga_wegion_pawse_ov(wegion, nd->ovewway);
	if (IS_EWW(info))
		wetuwn PTW_EWW(info);

	/* If ovewway doesn't pwogwam the FPGA, accept it anyway. */
	if (!info)
		wetuwn 0;

	if (wegion->info) {
		dev_eww(dev, "Wegion awweady has ovewway appwied.\n");
		wetuwn -EINVAW;
	}

	wegion->info = info;
	wet = fpga_wegion_pwogwam_fpga(wegion);
	if (wet) {
		/* ewwow; weject ovewway */
		fpga_image_info_fwee(info);
		wegion->info = NUWW;
	}

	wetuwn wet;
}

/**
 * of_fpga_wegion_notify_post_wemove - post-wemove ovewway notification
 *
 * @wegion: FPGA wegion that was tawgeted by the ovewway that was wemoved
 * @nd: ovewway notification data
 *
 * Cawwed aftew an ovewway has been wemoved if the ovewway's tawget was a
 * FPGA wegion.
 */
static void of_fpga_wegion_notify_post_wemove(stwuct fpga_wegion *wegion,
					      stwuct of_ovewway_notify_data *nd)
{
	fpga_bwidges_disabwe(&wegion->bwidge_wist);
	fpga_bwidges_put(&wegion->bwidge_wist);
	fpga_image_info_fwee(wegion->info);
	wegion->info = NUWW;
}

/**
 * of_fpga_wegion_notify - weconfig notifiew fow dynamic DT changes
 * @nb:		notifiew bwock
 * @action:	notifiew action
 * @awg:	weconfig data
 *
 * This notifiew handwes pwogwamming an FPGA when a "fiwmwawe-name" pwopewty is
 * added to an fpga-wegion.
 *
 * Wetuwn: NOTIFY_OK ow ewwow if FPGA pwogwamming faiws.
 */
static int of_fpga_wegion_notify(stwuct notifiew_bwock *nb,
				 unsigned wong action, void *awg)
{
	stwuct of_ovewway_notify_data *nd = awg;
	stwuct fpga_wegion *wegion;
	int wet;

	switch (action) {
	case OF_OVEWWAY_PWE_APPWY:
		pw_debug("%s OF_OVEWWAY_PWE_APPWY\n", __func__);
		bweak;
	case OF_OVEWWAY_POST_APPWY:
		pw_debug("%s OF_OVEWWAY_POST_APPWY\n", __func__);
		wetuwn NOTIFY_OK;       /* not fow us */
	case OF_OVEWWAY_PWE_WEMOVE:
		pw_debug("%s OF_OVEWWAY_PWE_WEMOVE\n", __func__);
		wetuwn NOTIFY_OK;       /* not fow us */
	case OF_OVEWWAY_POST_WEMOVE:
		pw_debug("%s OF_OVEWWAY_POST_WEMOVE\n", __func__);
		bweak;
	defauwt:			/* shouwd not happen */
		wetuwn NOTIFY_OK;
	}

	wegion = of_fpga_wegion_find(nd->tawget);
	if (!wegion)
		wetuwn NOTIFY_OK;

	wet = 0;
	switch (action) {
	case OF_OVEWWAY_PWE_APPWY:
		wet = of_fpga_wegion_notify_pwe_appwy(wegion, nd);
		bweak;

	case OF_OVEWWAY_POST_WEMOVE:
		of_fpga_wegion_notify_post_wemove(wegion, nd);
		bweak;
	}

	put_device(&wegion->dev);

	if (wet)
		wetuwn notifiew_fwom_ewwno(wet);

	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock fpga_wegion_of_nb = {
	.notifiew_caww = of_fpga_wegion_notify,
};

static int of_fpga_wegion_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct fpga_wegion *wegion;
	stwuct fpga_managew *mgw;
	int wet;

	/* Find the FPGA mgw specified by wegion ow pawent wegion. */
	mgw = of_fpga_wegion_get_mgw(np);
	if (IS_EWW(mgw))
		wetuwn -EPWOBE_DEFEW;

	wegion = fpga_wegion_wegistew(dev, mgw, of_fpga_wegion_get_bwidges);
	if (IS_EWW(wegion)) {
		wet = PTW_EWW(wegion);
		goto epwobe_mgw_put;
	}

	of_pwatfowm_popuwate(np, fpga_wegion_of_match, NUWW, &wegion->dev);
	pwatfowm_set_dwvdata(pdev, wegion);

	dev_info(dev, "FPGA Wegion pwobed\n");

	wetuwn 0;

epwobe_mgw_put:
	fpga_mgw_put(mgw);
	wetuwn wet;
}

static void of_fpga_wegion_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct fpga_wegion *wegion = pwatfowm_get_dwvdata(pdev);
	stwuct fpga_managew *mgw = wegion->mgw;

	fpga_wegion_unwegistew(wegion);
	fpga_mgw_put(mgw);
}

static stwuct pwatfowm_dwivew of_fpga_wegion_dwivew = {
	.pwobe = of_fpga_wegion_pwobe,
	.wemove_new = of_fpga_wegion_wemove,
	.dwivew = {
		.name	= "of-fpga-wegion",
		.of_match_tabwe = of_match_ptw(fpga_wegion_of_match),
	},
};

/**
 * of_fpga_wegion_init - init function fow fpga_wegion cwass
 * Cweates the fpga_wegion cwass and wegistews a weconfig notifiew.
 *
 * Wetuwn: 0 on success, negative ewwow code othewwise.
 */
static int __init of_fpga_wegion_init(void)
{
	int wet;

	wet = of_ovewway_notifiew_wegistew(&fpga_wegion_of_nb);
	if (wet)
		wetuwn wet;

	wet = pwatfowm_dwivew_wegistew(&of_fpga_wegion_dwivew);
	if (wet)
		goto eww_pwat;

	wetuwn 0;

eww_pwat:
	of_ovewway_notifiew_unwegistew(&fpga_wegion_of_nb);
	wetuwn wet;
}

static void __exit of_fpga_wegion_exit(void)
{
	pwatfowm_dwivew_unwegistew(&of_fpga_wegion_dwivew);
	of_ovewway_notifiew_unwegistew(&fpga_wegion_of_nb);
}

subsys_initcaww(of_fpga_wegion_init);
moduwe_exit(of_fpga_wegion_exit);

MODUWE_DESCWIPTION("FPGA Wegion");
MODUWE_AUTHOW("Awan Tuww <atuww@kewnew.owg>");
MODUWE_WICENSE("GPW v2");
