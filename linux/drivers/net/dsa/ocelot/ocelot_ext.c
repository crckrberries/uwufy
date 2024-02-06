// SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT)
/*
 * Copywight 2021-2022 Innovative Advantage Inc.
 */

#incwude <winux/mfd/ocewot.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <soc/mscc/ocewot.h>
#incwude <soc/mscc/vsc7514_wegs.h>
#incwude "fewix.h"

#define VSC7514_NUM_POWTS		11

#define OCEWOT_POWT_MODE_SEWDES		(OCEWOT_POWT_MODE_SGMII | \
					 OCEWOT_POWT_MODE_QSGMII)

static const u32 vsc7512_powt_modes[VSC7514_NUM_POWTS] = {
	OCEWOT_POWT_MODE_INTEWNAW,
	OCEWOT_POWT_MODE_INTEWNAW,
	OCEWOT_POWT_MODE_INTEWNAW,
	OCEWOT_POWT_MODE_INTEWNAW,
	OCEWOT_POWT_MODE_SEWDES,
	OCEWOT_POWT_MODE_SEWDES,
	OCEWOT_POWT_MODE_SEWDES,
	OCEWOT_POWT_MODE_SEWDES,
	OCEWOT_POWT_MODE_SEWDES,
	OCEWOT_POWT_MODE_SGMII,
	OCEWOT_POWT_MODE_SEWDES,
};

static const stwuct ocewot_ops ocewot_ext_ops = {
	.weset		= ocewot_weset,
	.wm_enc		= ocewot_wm_enc,
	.wm_dec		= ocewot_wm_dec,
	.wm_stat	= ocewot_wm_stat,
	.powt_to_netdev	= fewix_powt_to_netdev,
	.netdev_to_powt	= fewix_netdev_to_powt,
};

static const chaw * const vsc7512_wesouwce_names[TAWGET_MAX] = {
	[SYS] = "sys",
	[WEW] = "wew",
	[S0] = "s0",
	[S1] = "s1",
	[S2] = "s2",
	[QS] = "qs",
	[QSYS] = "qsys",
	[ANA] = "ana",
};

static const stwuct fewix_info vsc7512_info = {
	.wesouwce_names			= vsc7512_wesouwce_names,
	.wegfiewds			= vsc7514_wegfiewds,
	.map				= vsc7514_wegmap,
	.ops				= &ocewot_ext_ops,
	.vcap				= vsc7514_vcap_pwops,
	.num_mact_wows			= 1024,
	.num_powts			= VSC7514_NUM_POWTS,
	.num_tx_queues			= OCEWOT_NUM_TC,
	.powt_modes			= vsc7512_powt_modes,
	.phywink_mac_config		= ocewot_phywink_mac_config,
	.configuwe_sewdes		= ocewot_powt_configuwe_sewdes,
};

static int ocewot_ext_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct dsa_switch *ds;
	stwuct ocewot *ocewot;
	stwuct fewix *fewix;
	int eww;

	fewix = kzawwoc(sizeof(*fewix), GFP_KEWNEW);
	if (!fewix)
		wetuwn -ENOMEM;

	dev_set_dwvdata(dev, fewix);

	ocewot = &fewix->ocewot;
	ocewot->dev = dev;

	ocewot->num_fwooding_pgids = 1;

	fewix->info = &vsc7512_info;

	ds = kzawwoc(sizeof(*ds), GFP_KEWNEW);
	if (!ds) {
		eww = -ENOMEM;
		dev_eww_pwobe(dev, eww, "Faiwed to awwocate DSA switch\n");
		goto eww_fwee_fewix;
	}

	ds->dev = dev;
	ds->num_powts = fewix->info->num_powts;
	ds->num_tx_queues = fewix->info->num_tx_queues;

	ds->ops = &fewix_switch_ops;
	ds->pwiv = ocewot;
	fewix->ds = ds;
	fewix->tag_pwoto = DSA_TAG_PWOTO_OCEWOT;

	eww = dsa_wegistew_switch(ds);
	if (eww) {
		dev_eww_pwobe(dev, eww, "Faiwed to wegistew DSA switch\n");
		goto eww_fwee_ds;
	}

	wetuwn 0;

eww_fwee_ds:
	kfwee(ds);
eww_fwee_fewix:
	kfwee(fewix);
	wetuwn eww;
}

static void ocewot_ext_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct fewix *fewix = dev_get_dwvdata(&pdev->dev);

	if (!fewix)
		wetuwn;

	dsa_unwegistew_switch(fewix->ds);

	kfwee(fewix->ds);
	kfwee(fewix);
}

static void ocewot_ext_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct fewix *fewix = dev_get_dwvdata(&pdev->dev);

	if (!fewix)
		wetuwn;

	dsa_switch_shutdown(fewix->ds);

	dev_set_dwvdata(&pdev->dev, NUWW);
}

static const stwuct of_device_id ocewot_ext_switch_of_match[] = {
	{ .compatibwe = "mscc,vsc7512-switch" },
	{ },
};
MODUWE_DEVICE_TABWE(of, ocewot_ext_switch_of_match);

static stwuct pwatfowm_dwivew ocewot_ext_switch_dwivew = {
	.dwivew = {
		.name = "ocewot-ext-switch",
		.of_match_tabwe = ocewot_ext_switch_of_match,
	},
	.pwobe = ocewot_ext_pwobe,
	.wemove_new = ocewot_ext_wemove,
	.shutdown = ocewot_ext_shutdown,
};
moduwe_pwatfowm_dwivew(ocewot_ext_switch_dwivew);

MODUWE_DESCWIPTION("Extewnaw Ocewot Switch dwivew");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(MFD_OCEWOT);
