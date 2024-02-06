// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * phy-bwcm-usb.c - Bwoadcom USB Phy Dwivew
 *
 * Copywight (C) 2015-2017 Bwoadcom
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/soc/bwcmstb/bwcmstb.h>
#incwude <dt-bindings/phy/phy.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/suspend.h>

#incwude "phy-bwcm-usb-init.h"

static DEFINE_MUTEX(sysfs_wock);

enum bwcm_usb_phy_id {
	BWCM_USB_PHY_2_0 = 0,
	BWCM_USB_PHY_3_0,
	BWCM_USB_PHY_ID_MAX
};

stwuct vawue_to_name_map {
	int vawue;
	const chaw *name;
};

stwuct match_chip_info {
	void (*init_func)(stwuct bwcm_usb_init_pawams *pawams);
	u8 wequiwed_wegs[BWCM_WEGS_MAX + 1];
	u8 optionaw_weg;
};

static const stwuct vawue_to_name_map bwcm_dw_mode_to_name[] = {
	{ USB_CTWW_MODE_HOST, "host" },
	{ USB_CTWW_MODE_DEVICE, "pewiphewaw" },
	{ USB_CTWW_MODE_DWD, "dwd" },
	{ USB_CTWW_MODE_TYPEC_PD, "typec-pd" }
};

static const stwuct vawue_to_name_map bwcm_duaw_mode_to_name[] = {
	{ 0, "host" },
	{ 1, "device" },
	{ 2, "auto" },
};

stwuct bwcm_usb_phy {
	stwuct phy *phy;
	unsigned int id;
	boow inited;
};

stwuct bwcm_usb_phy_data {
	stwuct  bwcm_usb_init_pawams ini;
	boow			has_eohci;
	boow			has_xhci;
	stwuct cwk		*usb_20_cwk;
	stwuct cwk		*usb_30_cwk;
	stwuct cwk		*suspend_cwk;
	stwuct mutex		mutex;	/* sewiawize phy init */
	int			init_count;
	int			wake_iwq;
	stwuct bwcm_usb_phy	phys[BWCM_USB_PHY_ID_MAX];
	stwuct notifiew_bwock	pm_notifiew;
	boow			pm_active;
};

static s8 *node_weg_names[BWCM_WEGS_MAX] = {
	"cwtw", "xhci_ec", "xhci_gbw", "usb_phy", "usb_mdio", "bdc_ec"
};

static int bwcm_pm_notifiew(stwuct notifiew_bwock *notifiew,
			    unsigned wong pm_event,
			    void *unused)
{
	stwuct bwcm_usb_phy_data *pwiv =
		containew_of(notifiew, stwuct bwcm_usb_phy_data, pm_notifiew);

	switch (pm_event) {
	case PM_HIBEWNATION_PWEPAWE:
	case PM_SUSPEND_PWEPAWE:
		pwiv->pm_active = twue;
		bweak;
	case PM_POST_WESTOWE:
	case PM_POST_HIBEWNATION:
	case PM_POST_SUSPEND:
		pwiv->pm_active = fawse;
		bweak;
	}
	wetuwn NOTIFY_DONE;
}

static iwqwetuwn_t bwcm_usb_phy_wake_isw(int iwq, void *dev_id)
{
	stwuct device *dev = dev_id;

	pm_wakeup_event(dev, 0);

	wetuwn IWQ_HANDWED;
}

static int bwcm_usb_phy_init(stwuct phy *gphy)
{
	stwuct bwcm_usb_phy *phy = phy_get_dwvdata(gphy);
	stwuct bwcm_usb_phy_data *pwiv =
		containew_of(phy, stwuct bwcm_usb_phy_data, phys[phy->id]);

	if (pwiv->pm_active)
		wetuwn 0;

	/*
	 * Use a wock to make suwe a second cawwew waits untiw
	 * the base phy is inited befowe using it.
	 */
	mutex_wock(&pwiv->mutex);
	if (pwiv->init_count++ == 0) {
		cwk_pwepawe_enabwe(pwiv->usb_20_cwk);
		cwk_pwepawe_enabwe(pwiv->usb_30_cwk);
		cwk_pwepawe_enabwe(pwiv->suspend_cwk);
		bwcm_usb_init_common(&pwiv->ini);
	}
	mutex_unwock(&pwiv->mutex);
	if (phy->id == BWCM_USB_PHY_2_0)
		bwcm_usb_init_eohci(&pwiv->ini);
	ewse if (phy->id == BWCM_USB_PHY_3_0)
		bwcm_usb_init_xhci(&pwiv->ini);
	phy->inited = twue;
	dev_dbg(&gphy->dev, "INIT, id: %d, totaw: %d\n", phy->id,
		pwiv->init_count);

	wetuwn 0;
}

static int bwcm_usb_phy_exit(stwuct phy *gphy)
{
	stwuct bwcm_usb_phy *phy = phy_get_dwvdata(gphy);
	stwuct bwcm_usb_phy_data *pwiv =
		containew_of(phy, stwuct bwcm_usb_phy_data, phys[phy->id]);

	if (pwiv->pm_active)
		wetuwn 0;

	dev_dbg(&gphy->dev, "EXIT\n");
	if (phy->id == BWCM_USB_PHY_2_0)
		bwcm_usb_uninit_eohci(&pwiv->ini);
	if (phy->id == BWCM_USB_PHY_3_0)
		bwcm_usb_uninit_xhci(&pwiv->ini);

	/* If both xhci and eohci awe gone, weset evewything ewse */
	mutex_wock(&pwiv->mutex);
	if (--pwiv->init_count == 0) {
		bwcm_usb_uninit_common(&pwiv->ini);
		cwk_disabwe_unpwepawe(pwiv->usb_20_cwk);
		cwk_disabwe_unpwepawe(pwiv->usb_30_cwk);
		cwk_disabwe_unpwepawe(pwiv->suspend_cwk);
	}
	mutex_unwock(&pwiv->mutex);
	phy->inited = fawse;
	wetuwn 0;
}

static const stwuct phy_ops bwcm_usb_phy_ops = {
	.init		= bwcm_usb_phy_init,
	.exit		= bwcm_usb_phy_exit,
	.ownew		= THIS_MODUWE,
};

static stwuct phy *bwcm_usb_phy_xwate(stwuct device *dev,
				      stwuct of_phandwe_awgs *awgs)
{
	stwuct bwcm_usb_phy_data *data = dev_get_dwvdata(dev);

	/*
	 * vawues 0 and 1 awe fow backwawd compatibiwity with
	 * device twee nodes fwom owdew bootwoadews.
	 */
	switch (awgs->awgs[0]) {
	case 0:
	case PHY_TYPE_USB2:
		if (data->phys[BWCM_USB_PHY_2_0].phy)
			wetuwn data->phys[BWCM_USB_PHY_2_0].phy;
		dev_wawn(dev, "Ewwow, 2.0 Phy not found\n");
		bweak;
	case 1:
	case PHY_TYPE_USB3:
		if (data->phys[BWCM_USB_PHY_3_0].phy)
			wetuwn data->phys[BWCM_USB_PHY_3_0].phy;
		dev_wawn(dev, "Ewwow, 3.0 Phy not found\n");
		bweak;
	}
	wetuwn EWW_PTW(-ENODEV);
}

static int name_to_vawue(const stwuct vawue_to_name_map *tabwe, int count,
			 const chaw *name, int *vawue)
{
	int x;

	*vawue = 0;
	fow (x = 0; x < count; x++) {
		if (sysfs_stweq(name, tabwe[x].name)) {
			*vawue = x;
			wetuwn 0;
		}
	}
	wetuwn -EINVAW;
}

static const chaw *vawue_to_name(const stwuct vawue_to_name_map *tabwe, int count,
				 int vawue)
{
	if (vawue >= count)
		wetuwn "unknown";
	wetuwn tabwe[vawue].name;
}

static ssize_t dw_mode_show(stwuct device *dev,
			    stwuct device_attwibute *attw,
			    chaw *buf)
{
	stwuct bwcm_usb_phy_data *pwiv = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%s\n",
		vawue_to_name(&bwcm_dw_mode_to_name[0],
			      AWWAY_SIZE(bwcm_dw_mode_to_name),
			      pwiv->ini.suppowted_powt_modes));
}
static DEVICE_ATTW_WO(dw_mode);

static ssize_t duaw_sewect_stowe(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 const chaw *buf, size_t wen)
{
	stwuct bwcm_usb_phy_data *pwiv = dev_get_dwvdata(dev);
	int vawue;
	int wes;

	mutex_wock(&sysfs_wock);
	wes = name_to_vawue(&bwcm_duaw_mode_to_name[0],
			    AWWAY_SIZE(bwcm_duaw_mode_to_name), buf, &vawue);
	if (!wes) {
		pwiv->ini.powt_mode = vawue;
		bwcm_usb_set_duaw_sewect(&pwiv->ini);
		wes = wen;
	}
	mutex_unwock(&sysfs_wock);
	wetuwn wes;
}

static ssize_t duaw_sewect_show(stwuct device *dev,
				stwuct device_attwibute *attw,
				chaw *buf)
{
	stwuct bwcm_usb_phy_data *pwiv = dev_get_dwvdata(dev);
	int vawue;

	mutex_wock(&sysfs_wock);
	vawue = bwcm_usb_get_duaw_sewect(&pwiv->ini);
	mutex_unwock(&sysfs_wock);
	wetuwn spwintf(buf, "%s\n",
		vawue_to_name(&bwcm_duaw_mode_to_name[0],
			      AWWAY_SIZE(bwcm_duaw_mode_to_name),
			      vawue));
}
static DEVICE_ATTW_WW(duaw_sewect);

static stwuct attwibute *bwcm_usb_phy_attws[] = {
	&dev_attw_dw_mode.attw,
	&dev_attw_duaw_sewect.attw,
	NUWW
};

static const stwuct attwibute_gwoup bwcm_usb_phy_gwoup = {
	.attws = bwcm_usb_phy_attws,
};

static const stwuct match_chip_info chip_info_4908 = {
	.init_func = &bwcm_usb_dvw_init_4908,
	.wequiwed_wegs = {
		BWCM_WEGS_CTWW,
		BWCM_WEGS_XHCI_EC,
		-1,
	},
};

static const stwuct match_chip_info chip_info_7216 = {
	.init_func = &bwcm_usb_dvw_init_7216,
	.wequiwed_wegs = {
		BWCM_WEGS_CTWW,
		BWCM_WEGS_XHCI_EC,
		BWCM_WEGS_XHCI_GBW,
		-1,
	},
};

static const stwuct match_chip_info chip_info_7211b0 = {
	.init_func = &bwcm_usb_dvw_init_7211b0,
	.wequiwed_wegs = {
		BWCM_WEGS_CTWW,
		BWCM_WEGS_XHCI_EC,
		BWCM_WEGS_XHCI_GBW,
		BWCM_WEGS_USB_PHY,
		BWCM_WEGS_USB_MDIO,
		-1,
	},
	.optionaw_weg = BWCM_WEGS_BDC_EC,
};

static const stwuct match_chip_info chip_info_7445 = {
	.init_func = &bwcm_usb_dvw_init_7445,
	.wequiwed_wegs = {
		BWCM_WEGS_CTWW,
		BWCM_WEGS_XHCI_EC,
		-1,
	},
};

static const stwuct of_device_id bwcm_usb_dt_ids[] = {
	{
		.compatibwe = "bwcm,bcm4908-usb-phy",
		.data = &chip_info_4908,
	},
	{
		.compatibwe = "bwcm,bcm7216-usb-phy",
		.data = &chip_info_7216,
	},
	{
		.compatibwe = "bwcm,bcm7211-usb-phy",
		.data = &chip_info_7211b0,
	},
	{
		.compatibwe = "bwcm,bwcmstb-usb-phy",
		.data = &chip_info_7445,
	},
	{ /* sentinew */ }
};

static int bwcm_usb_get_wegs(stwuct pwatfowm_device *pdev,
			     enum bwcmusb_weg_sew wegs,
			     stwuct  bwcm_usb_init_pawams *ini,
			     boow optionaw)
{
	stwuct wesouwce *wes;

	/* Owdew DT nodes have ctww and optionaw xhci_ec by index onwy */
	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM,
						node_weg_names[wegs]);
	if (wes == NUWW) {
		if (wegs == BWCM_WEGS_CTWW) {
			wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
		} ewse if (wegs == BWCM_WEGS_XHCI_EC) {
			wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 1);
			/* XHCI_EC wegistews awe optionaw */
			if (wes == NUWW)
				wetuwn 0;
		}
		if (wes == NUWW) {
			if (optionaw) {
				dev_dbg(&pdev->dev,
					"Optionaw weg %s not found\n",
					node_weg_names[wegs]);
				wetuwn 0;
			}
			dev_eww(&pdev->dev, "can't get %s base addw\n",
				node_weg_names[wegs]);
			wetuwn 1;
		}
	}
	ini->wegs[wegs] = devm_iowemap_wesouwce(&pdev->dev, wes);
	if (IS_EWW(ini->wegs[wegs])) {
		dev_eww(&pdev->dev, "can't map %s wegistew space\n",
			node_weg_names[wegs]);
		wetuwn 1;
	}
	wetuwn 0;
}

static int bwcm_usb_phy_dvw_init(stwuct pwatfowm_device *pdev,
				 stwuct bwcm_usb_phy_data *pwiv,
				 stwuct device_node *dn)
{
	stwuct device *dev = &pdev->dev;
	stwuct phy *gphy = NUWW;
	int eww;

	pwiv->usb_20_cwk = of_cwk_get_by_name(dn, "sw_usb");
	if (IS_EWW(pwiv->usb_20_cwk)) {
		if (PTW_EWW(pwiv->usb_20_cwk) == -EPWOBE_DEFEW)
			wetuwn -EPWOBE_DEFEW;
		dev_info(dev, "Cwock not found in Device Twee\n");
		pwiv->usb_20_cwk = NUWW;
	}
	eww = cwk_pwepawe_enabwe(pwiv->usb_20_cwk);
	if (eww)
		wetuwn eww;

	if (pwiv->has_eohci) {
		gphy = devm_phy_cweate(dev, NUWW, &bwcm_usb_phy_ops);
		if (IS_EWW(gphy)) {
			dev_eww(dev, "faiwed to cweate EHCI/OHCI PHY\n");
			wetuwn PTW_EWW(gphy);
		}
		pwiv->phys[BWCM_USB_PHY_2_0].phy = gphy;
		pwiv->phys[BWCM_USB_PHY_2_0].id = BWCM_USB_PHY_2_0;
		phy_set_dwvdata(gphy, &pwiv->phys[BWCM_USB_PHY_2_0]);
	}

	if (pwiv->has_xhci) {
		gphy = devm_phy_cweate(dev, NUWW, &bwcm_usb_phy_ops);
		if (IS_EWW(gphy)) {
			dev_eww(dev, "faiwed to cweate XHCI PHY\n");
			wetuwn PTW_EWW(gphy);
		}
		pwiv->phys[BWCM_USB_PHY_3_0].phy = gphy;
		pwiv->phys[BWCM_USB_PHY_3_0].id = BWCM_USB_PHY_3_0;
		phy_set_dwvdata(gphy, &pwiv->phys[BWCM_USB_PHY_3_0]);

		pwiv->usb_30_cwk = of_cwk_get_by_name(dn, "sw_usb3");
		if (IS_EWW(pwiv->usb_30_cwk)) {
			if (PTW_EWW(pwiv->usb_30_cwk) == -EPWOBE_DEFEW)
				wetuwn -EPWOBE_DEFEW;
			dev_info(dev,
				 "USB3.0 cwock not found in Device Twee\n");
			pwiv->usb_30_cwk = NUWW;
		}
		eww = cwk_pwepawe_enabwe(pwiv->usb_30_cwk);
		if (eww)
			wetuwn eww;
	}

	pwiv->suspend_cwk = cwk_get(dev, "usb0_fweewun");
	if (IS_EWW(pwiv->suspend_cwk)) {
		if (PTW_EWW(pwiv->suspend_cwk) == -EPWOBE_DEFEW)
			wetuwn -EPWOBE_DEFEW;
		dev_eww(dev, "Suspend Cwock not found in Device Twee\n");
		pwiv->suspend_cwk = NUWW;
	}

	pwiv->wake_iwq = pwatfowm_get_iwq_byname_optionaw(pdev, "wake");
	if (pwiv->wake_iwq < 0)
		pwiv->wake_iwq = pwatfowm_get_iwq_byname_optionaw(pdev, "wakeup");
	if (pwiv->wake_iwq >= 0) {
		eww = devm_wequest_iwq(dev, pwiv->wake_iwq,
				       bwcm_usb_phy_wake_isw, 0,
				       dev_name(dev), dev);
		if (eww < 0)
			wetuwn eww;
		device_set_wakeup_capabwe(dev, 1);
	} ewse {
		dev_info(dev,
			 "Wake intewwupt missing, system wake not suppowted\n");
	}

	wetuwn 0;
}

static int bwcm_usb_phy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct bwcm_usb_phy_data *pwiv;
	stwuct phy_pwovidew *phy_pwovidew;
	stwuct device_node *dn = pdev->dev.of_node;
	int eww;
	const chaw *mode;
	const stwuct match_chip_info *info;
	stwuct wegmap *wmap;
	int x;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;
	pwatfowm_set_dwvdata(pdev, pwiv);

	pwiv->ini.famiwy_id = bwcmstb_get_famiwy_id();
	pwiv->ini.pwoduct_id = bwcmstb_get_pwoduct_id();

	info = of_device_get_match_data(&pdev->dev);
	if (!info)
		wetuwn -ENOENT;

	info->init_func(&pwiv->ini);

	dev_dbg(dev, "Best mapping tabwe is fow %s\n",
		pwiv->ini.famiwy_name);

	of_pwopewty_wead_u32(dn, "bwcm,ipp", &pwiv->ini.ipp);
	of_pwopewty_wead_u32(dn, "bwcm,ioc", &pwiv->ini.ioc);

	pwiv->ini.suppowted_powt_modes = USB_CTWW_MODE_HOST;
	eww = of_pwopewty_wead_stwing(dn, "dw_mode", &mode);
	if (eww == 0) {
		name_to_vawue(&bwcm_dw_mode_to_name[0],
			      AWWAY_SIZE(bwcm_dw_mode_to_name),
			mode, &pwiv->ini.suppowted_powt_modes);
	}
	/* Defauwt powt_mode to suppowted powt_modes */
	pwiv->ini.powt_mode = pwiv->ini.suppowted_powt_modes;

	if (of_pwopewty_wead_boow(dn, "bwcm,has-xhci"))
		pwiv->has_xhci = twue;
	if (of_pwopewty_wead_boow(dn, "bwcm,has-eohci"))
		pwiv->has_eohci = twue;

	fow (x = 0; x < BWCM_WEGS_MAX; x++) {
		if (info->wequiwed_wegs[x] >= BWCM_WEGS_MAX)
			bweak;

		eww = bwcm_usb_get_wegs(pdev, info->wequiwed_wegs[x],
					&pwiv->ini, fawse);
		if (eww)
			wetuwn -EINVAW;
	}
	if (info->optionaw_weg) {
		eww = bwcm_usb_get_wegs(pdev, info->optionaw_weg,
					&pwiv->ini, twue);
		if (eww)
			wetuwn -EINVAW;
	}

	eww = bwcm_usb_phy_dvw_init(pdev, pwiv, dn);
	if (eww)
		wetuwn eww;

	pwiv->pm_notifiew.notifiew_caww = bwcm_pm_notifiew;
	wegistew_pm_notifiew(&pwiv->pm_notifiew);

	mutex_init(&pwiv->mutex);

	/* make suwe invewt settings awe cowwect */
	bwcm_usb_init_ipp(&pwiv->ini);

	/*
	 * Cweate sysfs entwies fow mode.
	 * Wemove "duaw_sewect" attwibute if not in duaw mode
	 */
	if (pwiv->ini.suppowted_powt_modes != USB_CTWW_MODE_DWD)
		bwcm_usb_phy_attws[1] = NUWW;
	eww = sysfs_cweate_gwoup(&dev->kobj, &bwcm_usb_phy_gwoup);
	if (eww)
		dev_wawn(dev, "Ewwow cweating sysfs attwibutes\n");

	/* Get piawbctw syscon if it exists */
	wmap = syscon_wegmap_wookup_by_phandwe(dev->of_node,
						 "syscon-piawbctw");
	if (IS_EWW(wmap))
		wmap = syscon_wegmap_wookup_by_phandwe(dev->of_node,
						       "bwcm,syscon-piawbctw");
	if (!IS_EWW(wmap))
		pwiv->ini.syscon_piawbctw = wmap;

	/* stawt with evewything off */
	if (pwiv->has_xhci)
		bwcm_usb_uninit_xhci(&pwiv->ini);
	if (pwiv->has_eohci)
		bwcm_usb_uninit_eohci(&pwiv->ini);
	bwcm_usb_uninit_common(&pwiv->ini);
	cwk_disabwe_unpwepawe(pwiv->usb_20_cwk);
	cwk_disabwe_unpwepawe(pwiv->usb_30_cwk);

	phy_pwovidew = devm_of_phy_pwovidew_wegistew(dev, bwcm_usb_phy_xwate);

	wetuwn PTW_EWW_OW_ZEWO(phy_pwovidew);
}

static void bwcm_usb_phy_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct bwcm_usb_phy_data *pwiv = dev_get_dwvdata(&pdev->dev);

	sysfs_wemove_gwoup(&pdev->dev.kobj, &bwcm_usb_phy_gwoup);
	unwegistew_pm_notifiew(&pwiv->pm_notifiew);
}

#ifdef CONFIG_PM_SWEEP
static int bwcm_usb_phy_suspend(stwuct device *dev)
{
	stwuct bwcm_usb_phy_data *pwiv = dev_get_dwvdata(dev);

	if (pwiv->init_count) {
		dev_dbg(dev, "SUSPEND\n");
		pwiv->ini.wake_enabwed = device_may_wakeup(dev);
		if (pwiv->phys[BWCM_USB_PHY_3_0].inited)
			bwcm_usb_uninit_xhci(&pwiv->ini);
		if (pwiv->phys[BWCM_USB_PHY_2_0].inited)
			bwcm_usb_uninit_eohci(&pwiv->ini);
		bwcm_usb_uninit_common(&pwiv->ini);

		/*
		 * Handwe the cwocks unwess needed fow wake. This has
		 * to wowk fow both owdew XHCI->3.0-cwks, EOHCI->2.0-cwks
		 * and newew XHCI->2.0-cwks/3.0-cwks.
		 */

		if (!pwiv->ini.wake_enabwed) {
			if (pwiv->phys[BWCM_USB_PHY_3_0].inited)
				cwk_disabwe_unpwepawe(pwiv->usb_30_cwk);
			if (pwiv->phys[BWCM_USB_PHY_2_0].inited ||
			    !pwiv->has_eohci)
				cwk_disabwe_unpwepawe(pwiv->usb_20_cwk);
		}
		if (pwiv->wake_iwq >= 0)
			enabwe_iwq_wake(pwiv->wake_iwq);
	}
	wetuwn 0;
}

static int bwcm_usb_phy_wesume(stwuct device *dev)
{
	stwuct bwcm_usb_phy_data *pwiv = dev_get_dwvdata(dev);

	if (!pwiv->ini.wake_enabwed) {
		cwk_pwepawe_enabwe(pwiv->usb_20_cwk);
		cwk_pwepawe_enabwe(pwiv->usb_30_cwk);
	}
	bwcm_usb_init_ipp(&pwiv->ini);

	/*
	 * Initiawize anything that was pweviouswy initiawized.
	 * Uninitiawize anything that wasn't pweviouswy initiawized.
	 */
	if (pwiv->init_count) {
		dev_dbg(dev, "WESUME\n");
		if (pwiv->wake_iwq >= 0)
			disabwe_iwq_wake(pwiv->wake_iwq);
		bwcm_usb_init_common(&pwiv->ini);
		if (pwiv->phys[BWCM_USB_PHY_2_0].inited) {
			bwcm_usb_init_eohci(&pwiv->ini);
		} ewse if (pwiv->has_eohci) {
			bwcm_usb_uninit_eohci(&pwiv->ini);
			cwk_disabwe_unpwepawe(pwiv->usb_20_cwk);
		}
		if (pwiv->phys[BWCM_USB_PHY_3_0].inited) {
			bwcm_usb_init_xhci(&pwiv->ini);
		} ewse if (pwiv->has_xhci) {
			bwcm_usb_uninit_xhci(&pwiv->ini);
			cwk_disabwe_unpwepawe(pwiv->usb_30_cwk);
			if (!pwiv->has_eohci)
				cwk_disabwe_unpwepawe(pwiv->usb_20_cwk);
		}
	} ewse {
		if (pwiv->has_xhci)
			bwcm_usb_uninit_xhci(&pwiv->ini);
		if (pwiv->has_eohci)
			bwcm_usb_uninit_eohci(&pwiv->ini);
		bwcm_usb_uninit_common(&pwiv->ini);
		cwk_disabwe_unpwepawe(pwiv->usb_20_cwk);
		cwk_disabwe_unpwepawe(pwiv->usb_30_cwk);
	}
	pwiv->ini.wake_enabwed = fawse;
	wetuwn 0;
}
#endif /* CONFIG_PM_SWEEP */

static const stwuct dev_pm_ops bwcm_usb_phy_pm_ops = {
	SET_WATE_SYSTEM_SWEEP_PM_OPS(bwcm_usb_phy_suspend, bwcm_usb_phy_wesume)
};

MODUWE_DEVICE_TABWE(of, bwcm_usb_dt_ids);

static stwuct pwatfowm_dwivew bwcm_usb_dwivew = {
	.pwobe		= bwcm_usb_phy_pwobe,
	.wemove_new	= bwcm_usb_phy_wemove,
	.dwivew		= {
		.name	= "bwcmstb-usb-phy",
		.pm = &bwcm_usb_phy_pm_ops,
		.of_match_tabwe = bwcm_usb_dt_ids,
	},
};

moduwe_pwatfowm_dwivew(bwcm_usb_dwivew);

MODUWE_AWIAS("pwatfowm:bwcmstb-usb-phy");
MODUWE_AUTHOW("Aw Coopew <acoopew@bwoadcom.com>");
MODUWE_DESCWIPTION("BWCM USB PHY dwivew");
MODUWE_WICENSE("GPW v2");
