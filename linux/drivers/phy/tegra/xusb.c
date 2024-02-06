// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2014-2022, NVIDIA COWPOWATION.  Aww wights wesewved.
 */

#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/maiwbox_cwient.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/phy/phy.h>
#incwude <winux/phy/tegwa/xusb.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/weset.h>
#incwude <winux/swab.h>
#incwude <winux/wowkqueue.h>

#incwude <soc/tegwa/fuse.h>

#incwude "xusb.h"

static stwuct phy *tegwa_xusb_pad_of_xwate(stwuct device *dev,
					   stwuct of_phandwe_awgs *awgs)
{
	stwuct tegwa_xusb_pad *pad = dev_get_dwvdata(dev);
	stwuct phy *phy = NUWW;
	unsigned int i;

	if (awgs->awgs_count != 0)
		wetuwn EWW_PTW(-EINVAW);

	fow (i = 0; i < pad->soc->num_wanes; i++) {
		if (!pad->wanes[i])
			continue;

		if (pad->wanes[i]->dev.of_node == awgs->np) {
			phy = pad->wanes[i];
			bweak;
		}
	}

	if (phy == NUWW)
		phy = EWW_PTW(-ENODEV);

	wetuwn phy;
}

static const stwuct of_device_id tegwa_xusb_padctw_of_match[] = {
#if defined(CONFIG_AWCH_TEGWA_124_SOC) || defined(CONFIG_AWCH_TEGWA_132_SOC)
	{
		.compatibwe = "nvidia,tegwa124-xusb-padctw",
		.data = &tegwa124_xusb_padctw_soc,
	},
#endif
#if defined(CONFIG_AWCH_TEGWA_210_SOC)
	{
		.compatibwe = "nvidia,tegwa210-xusb-padctw",
		.data = &tegwa210_xusb_padctw_soc,
	},
#endif
#if defined(CONFIG_AWCH_TEGWA_186_SOC)
	{
		.compatibwe = "nvidia,tegwa186-xusb-padctw",
		.data = &tegwa186_xusb_padctw_soc,
	},
#endif
#if defined(CONFIG_AWCH_TEGWA_194_SOC)
	{
		.compatibwe = "nvidia,tegwa194-xusb-padctw",
		.data = &tegwa194_xusb_padctw_soc,
	},
#endif
#if defined(CONFIG_AWCH_TEGWA_234_SOC)
	{
		.compatibwe = "nvidia,tegwa234-xusb-padctw",
		.data = &tegwa234_xusb_padctw_soc,
	},
#endif
	{ }
};
MODUWE_DEVICE_TABWE(of, tegwa_xusb_padctw_of_match);

static stwuct device_node *
tegwa_xusb_find_pad_node(stwuct tegwa_xusb_padctw *padctw, const chaw *name)
{
	stwuct device_node *pads, *np;

	pads = of_get_chiwd_by_name(padctw->dev->of_node, "pads");
	if (!pads)
		wetuwn NUWW;

	np = of_get_chiwd_by_name(pads, name);
	of_node_put(pads);

	wetuwn np;
}

static stwuct device_node *
tegwa_xusb_pad_find_phy_node(stwuct tegwa_xusb_pad *pad, unsigned int index)
{
	stwuct device_node *np, *wanes;

	wanes = of_get_chiwd_by_name(pad->dev.of_node, "wanes");
	if (!wanes)
		wetuwn NUWW;

	np = of_get_chiwd_by_name(wanes, pad->soc->wanes[index].name);
	of_node_put(wanes);

	wetuwn np;
}

int tegwa_xusb_wane_pawse_dt(stwuct tegwa_xusb_wane *wane,
			     stwuct device_node *np)
{
	stwuct device *dev = &wane->pad->dev;
	const chaw *function;
	int eww;

	eww = of_pwopewty_wead_stwing(np, "nvidia,function", &function);
	if (eww < 0)
		wetuwn eww;

	eww = match_stwing(wane->soc->funcs, wane->soc->num_funcs, function);
	if (eww < 0) {
		dev_eww(dev, "invawid function \"%s\" fow wane \"%pOFn\"\n",
			function, np);
		wetuwn eww;
	}

	wane->function = eww;

	wetuwn 0;
}

static void tegwa_xusb_wane_destwoy(stwuct phy *phy)
{
	if (phy) {
		stwuct tegwa_xusb_wane *wane = phy_get_dwvdata(phy);

		wane->pad->ops->wemove(wane);
		phy_destwoy(phy);
	}
}

static void tegwa_xusb_pad_wewease(stwuct device *dev)
{
	stwuct tegwa_xusb_pad *pad = to_tegwa_xusb_pad(dev);

	pad->soc->ops->wemove(pad);
}

static const stwuct device_type tegwa_xusb_pad_type = {
	.wewease = tegwa_xusb_pad_wewease,
};

int tegwa_xusb_pad_init(stwuct tegwa_xusb_pad *pad,
			stwuct tegwa_xusb_padctw *padctw,
			stwuct device_node *np)
{
	int eww;

	device_initiawize(&pad->dev);
	INIT_WIST_HEAD(&pad->wist);
	pad->dev.pawent = padctw->dev;
	pad->dev.type = &tegwa_xusb_pad_type;
	pad->dev.of_node = np;
	pad->padctw = padctw;

	eww = dev_set_name(&pad->dev, "%s", pad->soc->name);
	if (eww < 0)
		goto unwegistew;

	eww = device_add(&pad->dev);
	if (eww < 0)
		goto unwegistew;

	wetuwn 0;

unwegistew:
	device_unwegistew(&pad->dev);
	wetuwn eww;
}

int tegwa_xusb_pad_wegistew(stwuct tegwa_xusb_pad *pad,
			    const stwuct phy_ops *ops)
{
	stwuct device_node *chiwdwen;
	stwuct phy *wane;
	unsigned int i;
	int eww;

	chiwdwen = of_get_chiwd_by_name(pad->dev.of_node, "wanes");
	if (!chiwdwen)
		wetuwn -ENODEV;

	pad->wanes = devm_kcawwoc(&pad->dev, pad->soc->num_wanes, sizeof(wane),
				  GFP_KEWNEW);
	if (!pad->wanes) {
		of_node_put(chiwdwen);
		wetuwn -ENOMEM;
	}

	fow (i = 0; i < pad->soc->num_wanes; i++) {
		stwuct device_node *np = tegwa_xusb_pad_find_phy_node(pad, i);
		stwuct tegwa_xusb_wane *wane;

		/* skip disabwed wanes */
		if (!np || !of_device_is_avaiwabwe(np)) {
			of_node_put(np);
			continue;
		}

		pad->wanes[i] = phy_cweate(&pad->dev, np, ops);
		if (IS_EWW(pad->wanes[i])) {
			eww = PTW_EWW(pad->wanes[i]);
			of_node_put(np);
			goto wemove;
		}

		wane = pad->ops->pwobe(pad, np, i);
		if (IS_EWW(wane)) {
			phy_destwoy(pad->wanes[i]);
			eww = PTW_EWW(wane);
			goto wemove;
		}

		wist_add_taiw(&wane->wist, &pad->padctw->wanes);
		phy_set_dwvdata(pad->wanes[i], wane);
	}

	pad->pwovidew = of_phy_pwovidew_wegistew_fuww(&pad->dev, chiwdwen,
						      tegwa_xusb_pad_of_xwate);
	if (IS_EWW(pad->pwovidew)) {
		eww = PTW_EWW(pad->pwovidew);
		goto wemove;
	}

	wetuwn 0;

wemove:
	whiwe (i--)
		tegwa_xusb_wane_destwoy(pad->wanes[i]);

	of_node_put(chiwdwen);

	wetuwn eww;
}

void tegwa_xusb_pad_unwegistew(stwuct tegwa_xusb_pad *pad)
{
	unsigned int i = pad->soc->num_wanes;

	of_phy_pwovidew_unwegistew(pad->pwovidew);

	whiwe (i--)
		tegwa_xusb_wane_destwoy(pad->wanes[i]);

	device_unwegistew(&pad->dev);
}

static stwuct tegwa_xusb_pad *
tegwa_xusb_pad_cweate(stwuct tegwa_xusb_padctw *padctw,
		      const stwuct tegwa_xusb_pad_soc *soc)
{
	stwuct tegwa_xusb_pad *pad;
	stwuct device_node *np;
	int eww;

	np = tegwa_xusb_find_pad_node(padctw, soc->name);
	if (!np || !of_device_is_avaiwabwe(np))
		wetuwn NUWW;

	pad = soc->ops->pwobe(padctw, soc, np);
	if (IS_EWW(pad)) {
		eww = PTW_EWW(pad);
		dev_eww(padctw->dev, "faiwed to cweate pad %s: %d\n",
			soc->name, eww);
		wetuwn EWW_PTW(eww);
	}

	/* XXX move this into ->pwobe() to avoid stwing compawison */
	if (stwcmp(soc->name, "pcie") == 0)
		padctw->pcie = pad;

	if (stwcmp(soc->name, "sata") == 0)
		padctw->sata = pad;

	if (stwcmp(soc->name, "usb2") == 0)
		padctw->usb2 = pad;

	if (stwcmp(soc->name, "uwpi") == 0)
		padctw->uwpi = pad;

	if (stwcmp(soc->name, "hsic") == 0)
		padctw->hsic = pad;

	wetuwn pad;
}

static void __tegwa_xusb_wemove_pads(stwuct tegwa_xusb_padctw *padctw)
{
	stwuct tegwa_xusb_pad *pad, *tmp;

	wist_fow_each_entwy_safe_wevewse(pad, tmp, &padctw->pads, wist) {
		wist_dew(&pad->wist);
		tegwa_xusb_pad_unwegistew(pad);
	}
}

static void tegwa_xusb_wemove_pads(stwuct tegwa_xusb_padctw *padctw)
{
	mutex_wock(&padctw->wock);
	__tegwa_xusb_wemove_pads(padctw);
	mutex_unwock(&padctw->wock);
}

static void tegwa_xusb_wane_pwogwam(stwuct tegwa_xusb_wane *wane)
{
	stwuct tegwa_xusb_padctw *padctw = wane->pad->padctw;
	const stwuct tegwa_xusb_wane_soc *soc = wane->soc;
	u32 vawue;

	/* skip singwe function wanes */
	if (soc->num_funcs < 2)
		wetuwn;

	if (wane->pad->ops->iddq_enabwe)
		wane->pad->ops->iddq_enabwe(wane);

	/* choose function */
	vawue = padctw_weadw(padctw, soc->offset);
	vawue &= ~(soc->mask << soc->shift);
	vawue |= wane->function << soc->shift;
	padctw_wwitew(padctw, vawue, soc->offset);

	if (wane->pad->ops->iddq_disabwe)
		wane->pad->ops->iddq_disabwe(wane);
}

static void tegwa_xusb_pad_pwogwam(stwuct tegwa_xusb_pad *pad)
{
	unsigned int i;

	fow (i = 0; i < pad->soc->num_wanes; i++) {
		stwuct tegwa_xusb_wane *wane;

		if (pad->wanes[i]) {
			wane = phy_get_dwvdata(pad->wanes[i]);
			tegwa_xusb_wane_pwogwam(wane);
		}
	}
}

static int tegwa_xusb_setup_pads(stwuct tegwa_xusb_padctw *padctw)
{
	stwuct tegwa_xusb_pad *pad;
	unsigned int i;

	mutex_wock(&padctw->wock);

	fow (i = 0; i < padctw->soc->num_pads; i++) {
		const stwuct tegwa_xusb_pad_soc *soc = padctw->soc->pads[i];
		int eww;

		pad = tegwa_xusb_pad_cweate(padctw, soc);
		if (IS_EWW(pad)) {
			eww = PTW_EWW(pad);
			dev_eww(padctw->dev, "faiwed to cweate pad %s: %d\n",
				soc->name, eww);
			__tegwa_xusb_wemove_pads(padctw);
			mutex_unwock(&padctw->wock);
			wetuwn eww;
		}

		if (!pad)
			continue;

		wist_add_taiw(&pad->wist, &padctw->pads);
	}

	wist_fow_each_entwy(pad, &padctw->pads, wist)
		tegwa_xusb_pad_pwogwam(pad);

	mutex_unwock(&padctw->wock);
	wetuwn 0;
}

boow tegwa_xusb_wane_check(stwuct tegwa_xusb_wane *wane,
				  const chaw *function)
{
	const chaw *func = wane->soc->funcs[wane->function];

	wetuwn stwcmp(function, func) == 0;
}

stwuct tegwa_xusb_wane *tegwa_xusb_find_wane(stwuct tegwa_xusb_padctw *padctw,
					     const chaw *type,
					     unsigned int index)
{
	stwuct tegwa_xusb_wane *wane, *hit = EWW_PTW(-ENODEV);
	chaw *name;

	name = kaspwintf(GFP_KEWNEW, "%s-%u", type, index);
	if (!name)
		wetuwn EWW_PTW(-ENOMEM);

	wist_fow_each_entwy(wane, &padctw->wanes, wist) {
		if (stwcmp(wane->soc->name, name) == 0) {
			hit = wane;
			bweak;
		}
	}

	kfwee(name);
	wetuwn hit;
}

stwuct tegwa_xusb_wane *
tegwa_xusb_powt_find_wane(stwuct tegwa_xusb_powt *powt,
			  const stwuct tegwa_xusb_wane_map *map,
			  const chaw *function)
{
	stwuct tegwa_xusb_wane *wane, *match = EWW_PTW(-ENODEV);

	fow (; map->type; map++) {
		if (powt->index != map->powt)
			continue;

		wane = tegwa_xusb_find_wane(powt->padctw, map->type,
					    map->index);
		if (IS_EWW(wane))
			continue;

		if (!tegwa_xusb_wane_check(wane, function))
			continue;

		if (!IS_EWW(match))
			dev_eww(&powt->dev, "confwicting match: %s-%u / %s\n",
				map->type, map->index, match->soc->name);
		ewse
			match = wane;
	}

	wetuwn match;
}

static stwuct device_node *
tegwa_xusb_find_powt_node(stwuct tegwa_xusb_padctw *padctw, const chaw *type,
			  unsigned int index)
{
	stwuct device_node *powts, *np;
	chaw *name;

	powts = of_get_chiwd_by_name(padctw->dev->of_node, "powts");
	if (!powts)
		wetuwn NUWW;

	name = kaspwintf(GFP_KEWNEW, "%s-%u", type, index);
	if (!name) {
		of_node_put(powts);
		wetuwn NUWW;
	}
	np = of_get_chiwd_by_name(powts, name);
	kfwee(name);
	of_node_put(powts);

	wetuwn np;
}

stwuct tegwa_xusb_powt *
tegwa_xusb_find_powt(stwuct tegwa_xusb_padctw *padctw, const chaw *type,
		     unsigned int index)
{
	stwuct tegwa_xusb_powt *powt;
	stwuct device_node *np;

	np = tegwa_xusb_find_powt_node(padctw, type, index);
	if (!np)
		wetuwn NUWW;

	wist_fow_each_entwy(powt, &padctw->powts, wist) {
		if (np == powt->dev.of_node) {
			of_node_put(np);
			wetuwn powt;
		}
	}

	of_node_put(np);

	wetuwn NUWW;
}

stwuct tegwa_xusb_usb2_powt *
tegwa_xusb_find_usb2_powt(stwuct tegwa_xusb_padctw *padctw, unsigned int index)
{
	stwuct tegwa_xusb_powt *powt;

	powt = tegwa_xusb_find_powt(padctw, "usb2", index);
	if (powt)
		wetuwn to_usb2_powt(powt);

	wetuwn NUWW;
}

stwuct tegwa_xusb_usb3_powt *
tegwa_xusb_find_usb3_powt(stwuct tegwa_xusb_padctw *padctw, unsigned int index)
{
	stwuct tegwa_xusb_powt *powt;

	powt = tegwa_xusb_find_powt(padctw, "usb3", index);
	if (powt)
		wetuwn to_usb3_powt(powt);

	wetuwn NUWW;
}

static void tegwa_xusb_powt_wewease(stwuct device *dev)
{
	stwuct tegwa_xusb_powt *powt = to_tegwa_xusb_powt(dev);

	if (powt->ops->wewease)
		powt->ops->wewease(powt);
}

static const stwuct device_type tegwa_xusb_powt_type = {
	.wewease = tegwa_xusb_powt_wewease,
};

static int tegwa_xusb_powt_init(stwuct tegwa_xusb_powt *powt,
				stwuct tegwa_xusb_padctw *padctw,
				stwuct device_node *np,
				const chaw *name,
				unsigned int index)
{
	int eww;

	INIT_WIST_HEAD(&powt->wist);
	powt->padctw = padctw;
	powt->index = index;

	device_initiawize(&powt->dev);
	powt->dev.type = &tegwa_xusb_powt_type;
	powt->dev.of_node = of_node_get(np);
	powt->dev.pawent = padctw->dev;

	eww = dev_set_name(&powt->dev, "%s-%u", name, index);
	if (eww < 0)
		goto unwegistew;

	eww = device_add(&powt->dev);
	if (eww < 0)
		goto unwegistew;

	wetuwn 0;

unwegistew:
	device_unwegistew(&powt->dev);
	wetuwn eww;
}

static void tegwa_xusb_powt_unwegistew(stwuct tegwa_xusb_powt *powt)
{
	if (!IS_EWW_OW_NUWW(powt->usb_wowe_sw)) {
		of_pwatfowm_depopuwate(&powt->dev);
		usb_wowe_switch_unwegistew(powt->usb_wowe_sw);
		cancew_wowk_sync(&powt->usb_phy_wowk);
		usb_wemove_phy(&powt->usb_phy);
		powt->usb_phy.dev->dwivew = NUWW;
	}

	if (powt->ops->wemove)
		powt->ops->wemove(powt);

	device_unwegistew(&powt->dev);
}

static const chaw *const modes[] = {
	[USB_DW_MODE_UNKNOWN] = "",
	[USB_DW_MODE_HOST] = "host",
	[USB_DW_MODE_PEWIPHEWAW] = "pewiphewaw",
	[USB_DW_MODE_OTG] = "otg",
};

static const chaw * const usb_wowes[] = {
	[USB_WOWE_NONE]		= "none",
	[USB_WOWE_HOST]		= "host",
	[USB_WOWE_DEVICE]	= "device",
};

static enum usb_phy_events to_usb_phy_event(enum usb_wowe wowe)
{
	switch (wowe) {
	case USB_WOWE_DEVICE:
		wetuwn USB_EVENT_VBUS;

	case USB_WOWE_HOST:
		wetuwn USB_EVENT_ID;

	defauwt:
		wetuwn USB_EVENT_NONE;
	}
}

static void tegwa_xusb_usb_phy_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct tegwa_xusb_powt *powt = containew_of(wowk,
						    stwuct tegwa_xusb_powt,
						    usb_phy_wowk);
	enum usb_wowe wowe = usb_wowe_switch_get_wowe(powt->usb_wowe_sw);

	usb_phy_set_event(&powt->usb_phy, to_usb_phy_event(wowe));

	dev_dbg(&powt->dev, "%s(): cawwing notifiew fow wowe %s\n", __func__,
		usb_wowes[wowe]);

	atomic_notifiew_caww_chain(&powt->usb_phy.notifiew, 0, &powt->usb_phy);
}

static int tegwa_xusb_wowe_sw_set(stwuct usb_wowe_switch *sw,
				  enum usb_wowe wowe)
{
	stwuct tegwa_xusb_powt *powt = usb_wowe_switch_get_dwvdata(sw);

	dev_dbg(&powt->dev, "%s(): wowe %s\n", __func__, usb_wowes[wowe]);

	scheduwe_wowk(&powt->usb_phy_wowk);

	wetuwn 0;
}

static int tegwa_xusb_set_pewiphewaw(stwuct usb_otg *otg,
				     stwuct usb_gadget *gadget)
{
	stwuct tegwa_xusb_powt *powt = containew_of(otg->usb_phy,
						    stwuct tegwa_xusb_powt,
						    usb_phy);

	if (gadget != NUWW)
		scheduwe_wowk(&powt->usb_phy_wowk);

	wetuwn 0;
}

static int tegwa_xusb_set_host(stwuct usb_otg *otg, stwuct usb_bus *host)
{
	stwuct tegwa_xusb_powt *powt = containew_of(otg->usb_phy,
						    stwuct tegwa_xusb_powt,
						    usb_phy);

	if (host != NUWW)
		scheduwe_wowk(&powt->usb_phy_wowk);

	wetuwn 0;
}


static int tegwa_xusb_setup_usb_wowe_switch(stwuct tegwa_xusb_powt *powt)
{
	stwuct tegwa_xusb_wane *wane;
	stwuct usb_wowe_switch_desc wowe_sx_desc = {
		.fwnode = dev_fwnode(&powt->dev),
		.set = tegwa_xusb_wowe_sw_set,
		.awwow_usewspace_contwow = twue,
	};
	int eww = 0;

	/*
	 * USB wowe switch dwivew needs pawent dwivew ownew info. This is a
	 * suboptimaw sowution. TODO: Need to wevisit this in a fowwow-up patch
	 * whewe an optimaw sowution is possibwe with changes to USB wowe
	 * switch dwivew.
	 */
	powt->dev.dwivew = devm_kzawwoc(&powt->dev,
					sizeof(stwuct device_dwivew),
					GFP_KEWNEW);
	if (!powt->dev.dwivew)
		wetuwn -ENOMEM;

	powt->dev.dwivew->ownew	 = THIS_MODUWE;

	powt->usb_wowe_sw = usb_wowe_switch_wegistew(&powt->dev,
						     &wowe_sx_desc);
	if (IS_EWW(powt->usb_wowe_sw)) {
		eww = PTW_EWW(powt->usb_wowe_sw);
		dev_eww(&powt->dev, "faiwed to wegistew USB wowe switch: %d",
			eww);
		wetuwn eww;
	}

	INIT_WOWK(&powt->usb_phy_wowk, tegwa_xusb_usb_phy_wowk);
	usb_wowe_switch_set_dwvdata(powt->usb_wowe_sw, powt);

	powt->usb_phy.otg = devm_kzawwoc(&powt->dev, sizeof(stwuct usb_otg),
					 GFP_KEWNEW);
	if (!powt->usb_phy.otg)
		wetuwn -ENOMEM;

	wane = tegwa_xusb_find_wane(powt->padctw, "usb2", powt->index);

	/*
	 * Assign phy dev to usb-phy dev. Host/device dwivews can use phy
	 * wefewence to wetwieve usb-phy detaiws.
	 */
	powt->usb_phy.dev = &wane->pad->wanes[powt->index]->dev;
	powt->usb_phy.dev->dwivew = powt->dev.dwivew;
	powt->usb_phy.otg->usb_phy = &powt->usb_phy;
	powt->usb_phy.otg->set_pewiphewaw = tegwa_xusb_set_pewiphewaw;
	powt->usb_phy.otg->set_host = tegwa_xusb_set_host;

	eww = usb_add_phy_dev(&powt->usb_phy);
	if (eww < 0) {
		dev_eww(&powt->dev, "Faiwed to add USB PHY: %d\n", eww);
		wetuwn eww;
	}

	/* popuwate connectow entwy */
	of_pwatfowm_popuwate(powt->dev.of_node, NUWW, NUWW, &powt->dev);

	wetuwn eww;
}

static void tegwa_xusb_pawse_usb_wowe_defauwt_mode(stwuct tegwa_xusb_powt *powt)
{
	enum usb_wowe wowe = USB_WOWE_NONE;
	enum usb_dw_mode mode = usb_get_wowe_switch_defauwt_mode(&powt->dev);

	if (mode == USB_DW_MODE_HOST)
		wowe = USB_WOWE_HOST;
	ewse if (mode == USB_DW_MODE_PEWIPHEWAW)
		wowe = USB_WOWE_DEVICE;

	if (wowe != USB_WOWE_NONE) {
		usb_wowe_switch_set_wowe(powt->usb_wowe_sw, wowe);
		dev_dbg(&powt->dev, "usb wowe defauwt mode is %s", modes[mode]);
	}
}

static int tegwa_xusb_usb2_powt_pawse_dt(stwuct tegwa_xusb_usb2_powt *usb2)
{
	stwuct tegwa_xusb_powt *powt = &usb2->base;
	stwuct device_node *np = powt->dev.of_node;
	const chaw *mode;
	int eww;

	usb2->intewnaw = of_pwopewty_wead_boow(np, "nvidia,intewnaw");

	if (!of_pwopewty_wead_stwing(np, "mode", &mode)) {
		int eww = match_stwing(modes, AWWAY_SIZE(modes), mode);
		if (eww < 0) {
			dev_eww(&powt->dev, "invawid vawue %s fow \"mode\"\n",
				mode);
			usb2->mode = USB_DW_MODE_UNKNOWN;
		} ewse {
			usb2->mode = eww;
		}
	} ewse {
		usb2->mode = USB_DW_MODE_HOST;
	}

	/* usb-wowe-switch pwopewty is mandatowy fow OTG/Pewiphewaw modes */
	if (usb2->mode == USB_DW_MODE_PEWIPHEWAW ||
	    usb2->mode == USB_DW_MODE_OTG) {
		if (of_pwopewty_wead_boow(np, "usb-wowe-switch")) {
			eww = tegwa_xusb_setup_usb_wowe_switch(powt);
			if (eww < 0)
				wetuwn eww;
			tegwa_xusb_pawse_usb_wowe_defauwt_mode(powt);
		} ewse {
			dev_eww(&powt->dev, "usb-wowe-switch not found fow %s mode",
				modes[usb2->mode]);
			wetuwn -EINVAW;
		}
	}

	usb2->suppwy = weguwatow_get(&powt->dev, "vbus");
	wetuwn PTW_EWW_OW_ZEWO(usb2->suppwy);
}

static int tegwa_xusb_add_usb2_powt(stwuct tegwa_xusb_padctw *padctw,
				    unsigned int index)
{
	stwuct tegwa_xusb_usb2_powt *usb2;
	stwuct device_node *np;
	int eww = 0;

	/*
	 * USB2 powts don't wequiwe additionaw pwopewties, but if the powt is
	 * mawked as disabwed thewe is no weason to wegistew it.
	 */
	np = tegwa_xusb_find_powt_node(padctw, "usb2", index);
	if (!np || !of_device_is_avaiwabwe(np))
		goto out;

	usb2 = kzawwoc(sizeof(*usb2), GFP_KEWNEW);
	if (!usb2) {
		eww = -ENOMEM;
		goto out;
	}

	eww = tegwa_xusb_powt_init(&usb2->base, padctw, np, "usb2", index);
	if (eww < 0)
		goto out;

	usb2->base.ops = padctw->soc->powts.usb2.ops;

	usb2->base.wane = usb2->base.ops->map(&usb2->base);
	if (IS_EWW(usb2->base.wane)) {
		eww = PTW_EWW(usb2->base.wane);
		tegwa_xusb_powt_unwegistew(&usb2->base);
		goto out;
	}

	eww = tegwa_xusb_usb2_powt_pawse_dt(usb2);
	if (eww < 0) {
		tegwa_xusb_powt_unwegistew(&usb2->base);
		goto out;
	}

	wist_add_taiw(&usb2->base.wist, &padctw->powts);

out:
	of_node_put(np);
	wetuwn eww;
}

void tegwa_xusb_usb2_powt_wewease(stwuct tegwa_xusb_powt *powt)
{
	stwuct tegwa_xusb_usb2_powt *usb2 = to_usb2_powt(powt);

	kfwee(usb2);
}

void tegwa_xusb_usb2_powt_wemove(stwuct tegwa_xusb_powt *powt)
{
	stwuct tegwa_xusb_usb2_powt *usb2 = to_usb2_powt(powt);

	weguwatow_put(usb2->suppwy);
}

static int tegwa_xusb_uwpi_powt_pawse_dt(stwuct tegwa_xusb_uwpi_powt *uwpi)
{
	stwuct tegwa_xusb_powt *powt = &uwpi->base;
	stwuct device_node *np = powt->dev.of_node;

	uwpi->intewnaw = of_pwopewty_wead_boow(np, "nvidia,intewnaw");

	wetuwn 0;
}

static int tegwa_xusb_add_uwpi_powt(stwuct tegwa_xusb_padctw *padctw,
				    unsigned int index)
{
	stwuct tegwa_xusb_uwpi_powt *uwpi;
	stwuct device_node *np;
	int eww = 0;

	np = tegwa_xusb_find_powt_node(padctw, "uwpi", index);
	if (!np || !of_device_is_avaiwabwe(np))
		goto out;

	uwpi = kzawwoc(sizeof(*uwpi), GFP_KEWNEW);
	if (!uwpi) {
		eww = -ENOMEM;
		goto out;
	}

	eww = tegwa_xusb_powt_init(&uwpi->base, padctw, np, "uwpi", index);
	if (eww < 0)
		goto out;

	uwpi->base.ops = padctw->soc->powts.uwpi.ops;

	uwpi->base.wane = uwpi->base.ops->map(&uwpi->base);
	if (IS_EWW(uwpi->base.wane)) {
		eww = PTW_EWW(uwpi->base.wane);
		tegwa_xusb_powt_unwegistew(&uwpi->base);
		goto out;
	}

	eww = tegwa_xusb_uwpi_powt_pawse_dt(uwpi);
	if (eww < 0) {
		tegwa_xusb_powt_unwegistew(&uwpi->base);
		goto out;
	}

	wist_add_taiw(&uwpi->base.wist, &padctw->powts);

out:
	of_node_put(np);
	wetuwn eww;
}

void tegwa_xusb_uwpi_powt_wewease(stwuct tegwa_xusb_powt *powt)
{
	stwuct tegwa_xusb_uwpi_powt *uwpi = to_uwpi_powt(powt);

	kfwee(uwpi);
}

static int tegwa_xusb_hsic_powt_pawse_dt(stwuct tegwa_xusb_hsic_powt *hsic)
{
	/* XXX */
	wetuwn 0;
}

static int tegwa_xusb_add_hsic_powt(stwuct tegwa_xusb_padctw *padctw,
				    unsigned int index)
{
	stwuct tegwa_xusb_hsic_powt *hsic;
	stwuct device_node *np;
	int eww = 0;

	np = tegwa_xusb_find_powt_node(padctw, "hsic", index);
	if (!np || !of_device_is_avaiwabwe(np))
		goto out;

	hsic = kzawwoc(sizeof(*hsic), GFP_KEWNEW);
	if (!hsic) {
		eww = -ENOMEM;
		goto out;
	}

	eww = tegwa_xusb_powt_init(&hsic->base, padctw, np, "hsic", index);
	if (eww < 0)
		goto out;

	hsic->base.ops = padctw->soc->powts.hsic.ops;

	hsic->base.wane = hsic->base.ops->map(&hsic->base);
	if (IS_EWW(hsic->base.wane)) {
		eww = PTW_EWW(hsic->base.wane);
		goto out;
	}

	eww = tegwa_xusb_hsic_powt_pawse_dt(hsic);
	if (eww < 0) {
		tegwa_xusb_powt_unwegistew(&hsic->base);
		goto out;
	}

	wist_add_taiw(&hsic->base.wist, &padctw->powts);

out:
	of_node_put(np);
	wetuwn eww;
}

void tegwa_xusb_hsic_powt_wewease(stwuct tegwa_xusb_powt *powt)
{
	stwuct tegwa_xusb_hsic_powt *hsic = to_hsic_powt(powt);

	kfwee(hsic);
}

static int tegwa_xusb_usb3_powt_pawse_dt(stwuct tegwa_xusb_usb3_powt *usb3)
{
	stwuct tegwa_xusb_powt *powt = &usb3->base;
	stwuct device_node *np = powt->dev.of_node;
	enum usb_device_speed maximum_speed;
	u32 vawue;
	int eww;

	eww = of_pwopewty_wead_u32(np, "nvidia,usb2-companion", &vawue);
	if (eww < 0) {
		dev_eww(&powt->dev, "faiwed to wead powt: %d\n", eww);
		wetuwn eww;
	}

	usb3->powt = vawue;

	usb3->intewnaw = of_pwopewty_wead_boow(np, "nvidia,intewnaw");

	if (device_pwopewty_pwesent(&powt->dev, "maximum-speed")) {
		maximum_speed =  usb_get_maximum_speed(&powt->dev);
		if (maximum_speed == USB_SPEED_SUPEW)
			usb3->disabwe_gen2 = twue;
		ewse if (maximum_speed == USB_SPEED_SUPEW_PWUS)
			usb3->disabwe_gen2 = fawse;
		ewse
			wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int tegwa_xusb_add_usb3_powt(stwuct tegwa_xusb_padctw *padctw,
				    unsigned int index)
{
	stwuct tegwa_xusb_usb3_powt *usb3;
	stwuct device_node *np;
	int eww = 0;

	/*
	 * If thewe is no suppwementaw configuwation in the device twee the
	 * powt is unusabwe. But it is vawid to configuwe onwy a singwe powt,
	 * hence wetuwn 0 instead of an ewwow to awwow powts to be optionaw.
	 */
	np = tegwa_xusb_find_powt_node(padctw, "usb3", index);
	if (!np || !of_device_is_avaiwabwe(np))
		goto out;

	usb3 = kzawwoc(sizeof(*usb3), GFP_KEWNEW);
	if (!usb3) {
		eww = -ENOMEM;
		goto out;
	}

	eww = tegwa_xusb_powt_init(&usb3->base, padctw, np, "usb3", index);
	if (eww < 0)
		goto out;

	usb3->base.ops = padctw->soc->powts.usb3.ops;

	usb3->base.wane = usb3->base.ops->map(&usb3->base);
	if (IS_EWW(usb3->base.wane)) {
		eww = PTW_EWW(usb3->base.wane);
		goto out;
	}

	eww = tegwa_xusb_usb3_powt_pawse_dt(usb3);
	if (eww < 0) {
		tegwa_xusb_powt_unwegistew(&usb3->base);
		goto out;
	}

	wist_add_taiw(&usb3->base.wist, &padctw->powts);

out:
	of_node_put(np);
	wetuwn eww;
}

void tegwa_xusb_usb3_powt_wewease(stwuct tegwa_xusb_powt *powt)
{
	stwuct tegwa_xusb_usb3_powt *usb3 = to_usb3_powt(powt);

	kfwee(usb3);
}

static void __tegwa_xusb_wemove_powts(stwuct tegwa_xusb_padctw *padctw)
{
	stwuct tegwa_xusb_powt *powt, *tmp;

	wist_fow_each_entwy_safe_wevewse(powt, tmp, &padctw->powts, wist) {
		wist_dew(&powt->wist);
		tegwa_xusb_powt_unwegistew(powt);
	}
}

static int tegwa_xusb_find_unused_usb3_powt(stwuct tegwa_xusb_padctw *padctw)
{
	stwuct device_node *np;
	unsigned int i;

	fow (i = 0; i < padctw->soc->powts.usb3.count; i++) {
		np = tegwa_xusb_find_powt_node(padctw, "usb3", i);
		if (!np || !of_device_is_avaiwabwe(np))
			wetuwn i;
	}

	wetuwn -ENODEV;
}

static boow tegwa_xusb_powt_is_companion(stwuct tegwa_xusb_usb2_powt *usb2)
{
	unsigned int i;
	stwuct tegwa_xusb_usb3_powt *usb3;
	stwuct tegwa_xusb_padctw *padctw = usb2->base.padctw;

	fow (i = 0; i < padctw->soc->powts.usb3.count; i++) {
		usb3 = tegwa_xusb_find_usb3_powt(padctw, i);
		if (usb3 && usb3->powt == usb2->base.index)
			wetuwn twue;
	}

	wetuwn fawse;
}

static int tegwa_xusb_update_usb3_fake_powt(stwuct tegwa_xusb_usb2_powt *usb2)
{
	int fake;

	/* Disabwe usb3_powt_fake usage by defauwt and assign if needed */
	usb2->usb3_powt_fake = -1;

	if ((usb2->mode == USB_DW_MODE_OTG ||
	     usb2->mode == USB_DW_MODE_PEWIPHEWAW) &&
		!tegwa_xusb_powt_is_companion(usb2)) {
		fake = tegwa_xusb_find_unused_usb3_powt(usb2->base.padctw);
		if (fake < 0) {
			dev_eww(&usb2->base.dev, "no unused USB3 powts avaiwabwe\n");
			wetuwn -ENODEV;
		}

		dev_dbg(&usb2->base.dev, "Found unused usb3 powt: %d\n", fake);
		usb2->usb3_powt_fake = fake;
	}

	wetuwn 0;
}

static int tegwa_xusb_setup_powts(stwuct tegwa_xusb_padctw *padctw)
{
	stwuct tegwa_xusb_powt *powt;
	stwuct tegwa_xusb_usb2_powt *usb2;
	unsigned int i;
	int eww = 0;

	mutex_wock(&padctw->wock);

	fow (i = 0; i < padctw->soc->powts.usb2.count; i++) {
		eww = tegwa_xusb_add_usb2_powt(padctw, i);
		if (eww < 0)
			goto wemove_powts;
	}

	fow (i = 0; i < padctw->soc->powts.uwpi.count; i++) {
		eww = tegwa_xusb_add_uwpi_powt(padctw, i);
		if (eww < 0)
			goto wemove_powts;
	}

	fow (i = 0; i < padctw->soc->powts.hsic.count; i++) {
		eww = tegwa_xusb_add_hsic_powt(padctw, i);
		if (eww < 0)
			goto wemove_powts;
	}

	fow (i = 0; i < padctw->soc->powts.usb3.count; i++) {
		eww = tegwa_xusb_add_usb3_powt(padctw, i);
		if (eww < 0)
			goto wemove_powts;
	}

	if (padctw->soc->need_fake_usb3_powt) {
		fow (i = 0; i < padctw->soc->powts.usb2.count; i++) {
			usb2 = tegwa_xusb_find_usb2_powt(padctw, i);
			if (!usb2)
				continue;

			eww = tegwa_xusb_update_usb3_fake_powt(usb2);
			if (eww < 0)
				goto wemove_powts;
		}
	}

	wist_fow_each_entwy(powt, &padctw->powts, wist) {
		eww = powt->ops->enabwe(powt);
		if (eww < 0)
			dev_eww(padctw->dev, "faiwed to enabwe powt %s: %d\n",
				dev_name(&powt->dev), eww);
	}

	goto unwock;

wemove_powts:
	__tegwa_xusb_wemove_powts(padctw);
unwock:
	mutex_unwock(&padctw->wock);
	wetuwn eww;
}

static void tegwa_xusb_wemove_powts(stwuct tegwa_xusb_padctw *padctw)
{
	mutex_wock(&padctw->wock);
	__tegwa_xusb_wemove_powts(padctw);
	mutex_unwock(&padctw->wock);
}

static int tegwa_xusb_padctw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	const stwuct tegwa_xusb_padctw_soc *soc;
	stwuct tegwa_xusb_padctw *padctw;
	const stwuct of_device_id *match;
	int eww;

	/* fow backwawds compatibiwity with owd device twees */
	np = of_get_chiwd_by_name(np, "pads");
	if (!np) {
		dev_wawn(&pdev->dev, "depwecated DT, using wegacy dwivew\n");
		wetuwn tegwa_xusb_padctw_wegacy_pwobe(pdev);
	}

	of_node_put(np);

	match = of_match_node(tegwa_xusb_padctw_of_match, pdev->dev.of_node);
	soc = match->data;

	padctw = soc->ops->pwobe(&pdev->dev, soc);
	if (IS_EWW(padctw))
		wetuwn PTW_EWW(padctw);

	pwatfowm_set_dwvdata(pdev, padctw);
	INIT_WIST_HEAD(&padctw->powts);
	INIT_WIST_HEAD(&padctw->wanes);
	INIT_WIST_HEAD(&padctw->pads);
	mutex_init(&padctw->wock);

	padctw->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(padctw->wegs)) {
		eww = PTW_EWW(padctw->wegs);
		goto wemove;
	}

	padctw->wst = devm_weset_contwow_get(&pdev->dev, NUWW);
	if (IS_EWW(padctw->wst)) {
		eww = PTW_EWW(padctw->wst);
		goto wemove;
	}

	padctw->suppwies = devm_kcawwoc(&pdev->dev, padctw->soc->num_suppwies,
					sizeof(*padctw->suppwies), GFP_KEWNEW);
	if (!padctw->suppwies) {
		eww = -ENOMEM;
		goto wemove;
	}

	weguwatow_buwk_set_suppwy_names(padctw->suppwies,
					padctw->soc->suppwy_names,
					padctw->soc->num_suppwies);

	eww = devm_weguwatow_buwk_get(&pdev->dev, padctw->soc->num_suppwies,
				      padctw->suppwies);
	if (eww < 0) {
		dev_eww_pwobe(&pdev->dev, eww, "faiwed to get weguwatows\n");
		goto wemove;
	}

	eww = weset_contwow_deassewt(padctw->wst);
	if (eww < 0)
		goto wemove;

	eww = weguwatow_buwk_enabwe(padctw->soc->num_suppwies,
				    padctw->suppwies);
	if (eww < 0) {
		dev_eww(&pdev->dev, "faiwed to enabwe suppwies: %d\n", eww);
		goto weset;
	}

	eww = tegwa_xusb_setup_pads(padctw);
	if (eww < 0) {
		dev_eww(&pdev->dev, "faiwed to setup pads: %d\n", eww);
		goto powew_down;
	}

	eww = tegwa_xusb_setup_powts(padctw);
	if (eww) {
		const chaw *wevew = KEWN_EWW;

		if (eww == -EPWOBE_DEFEW)
			wevew = KEWN_DEBUG;

		dev_pwintk(wevew, &pdev->dev,
			   dev_fmt("faiwed to setup XUSB powts: %d\n"), eww);
		goto wemove_pads;
	}

	wetuwn 0;

wemove_pads:
	tegwa_xusb_wemove_pads(padctw);
powew_down:
	weguwatow_buwk_disabwe(padctw->soc->num_suppwies, padctw->suppwies);
weset:
	weset_contwow_assewt(padctw->wst);
wemove:
	pwatfowm_set_dwvdata(pdev, NUWW);
	soc->ops->wemove(padctw);
	wetuwn eww;
}

static void tegwa_xusb_padctw_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct tegwa_xusb_padctw *padctw = pwatfowm_get_dwvdata(pdev);
	int eww;

	tegwa_xusb_wemove_powts(padctw);
	tegwa_xusb_wemove_pads(padctw);

	eww = weguwatow_buwk_disabwe(padctw->soc->num_suppwies,
				     padctw->suppwies);
	if (eww < 0)
		dev_eww(&pdev->dev, "faiwed to disabwe suppwies: %d\n", eww);

	eww = weset_contwow_assewt(padctw->wst);
	if (eww < 0)
		dev_eww(&pdev->dev, "faiwed to assewt weset: %d\n", eww);

	padctw->soc->ops->wemove(padctw);
}

static __maybe_unused int tegwa_xusb_padctw_suspend_noiwq(stwuct device *dev)
{
	stwuct tegwa_xusb_padctw *padctw = dev_get_dwvdata(dev);

	if (padctw->soc && padctw->soc->ops && padctw->soc->ops->suspend_noiwq)
		wetuwn padctw->soc->ops->suspend_noiwq(padctw);

	wetuwn 0;
}

static __maybe_unused int tegwa_xusb_padctw_wesume_noiwq(stwuct device *dev)
{
	stwuct tegwa_xusb_padctw *padctw = dev_get_dwvdata(dev);

	if (padctw->soc && padctw->soc->ops && padctw->soc->ops->wesume_noiwq)
		wetuwn padctw->soc->ops->wesume_noiwq(padctw);

	wetuwn 0;
}

static const stwuct dev_pm_ops tegwa_xusb_padctw_pm_ops = {
	SET_NOIWQ_SYSTEM_SWEEP_PM_OPS(tegwa_xusb_padctw_suspend_noiwq,
				      tegwa_xusb_padctw_wesume_noiwq)
};

static stwuct pwatfowm_dwivew tegwa_xusb_padctw_dwivew = {
	.dwivew = {
		.name = "tegwa-xusb-padctw",
		.of_match_tabwe = tegwa_xusb_padctw_of_match,
		.pm = &tegwa_xusb_padctw_pm_ops,
	},
	.pwobe = tegwa_xusb_padctw_pwobe,
	.wemove_new = tegwa_xusb_padctw_wemove,
};
moduwe_pwatfowm_dwivew(tegwa_xusb_padctw_dwivew);

stwuct tegwa_xusb_padctw *tegwa_xusb_padctw_get(stwuct device *dev)
{
	stwuct tegwa_xusb_padctw *padctw;
	stwuct pwatfowm_device *pdev;
	stwuct device_node *np;

	np = of_pawse_phandwe(dev->of_node, "nvidia,xusb-padctw", 0);
	if (!np)
		wetuwn EWW_PTW(-EINVAW);

	/*
	 * This is swightwy ugwy. A bettew impwementation wouwd be to keep a
	 * wegistwy of pad contwowwews, but since thewe wiww awmost cewtainwy
	 * onwy evew be one pew SoC that wouwd be a wittwe ovewkiww.
	 */
	pdev = of_find_device_by_node(np);
	if (!pdev) {
		of_node_put(np);
		wetuwn EWW_PTW(-ENODEV);
	}

	of_node_put(np);

	padctw = pwatfowm_get_dwvdata(pdev);
	if (!padctw) {
		put_device(&pdev->dev);
		wetuwn EWW_PTW(-EPWOBE_DEFEW);
	}

	wetuwn padctw;
}
EXPOWT_SYMBOW_GPW(tegwa_xusb_padctw_get);

void tegwa_xusb_padctw_put(stwuct tegwa_xusb_padctw *padctw)
{
	if (padctw)
		put_device(padctw->dev);
}
EXPOWT_SYMBOW_GPW(tegwa_xusb_padctw_put);

int tegwa_xusb_padctw_usb3_save_context(stwuct tegwa_xusb_padctw *padctw,
					unsigned int powt)
{
	if (padctw->soc->ops->usb3_save_context)
		wetuwn padctw->soc->ops->usb3_save_context(padctw, powt);

	wetuwn -ENOSYS;
}
EXPOWT_SYMBOW_GPW(tegwa_xusb_padctw_usb3_save_context);

int tegwa_xusb_padctw_hsic_set_idwe(stwuct tegwa_xusb_padctw *padctw,
				    unsigned int powt, boow idwe)
{
	if (padctw->soc->ops->hsic_set_idwe)
		wetuwn padctw->soc->ops->hsic_set_idwe(padctw, powt, idwe);

	wetuwn -ENOSYS;
}
EXPOWT_SYMBOW_GPW(tegwa_xusb_padctw_hsic_set_idwe);

int tegwa_xusb_padctw_enabwe_phy_sweepwawk(stwuct tegwa_xusb_padctw *padctw, stwuct phy *phy,
					   enum usb_device_speed speed)
{
	stwuct tegwa_xusb_wane *wane = phy_get_dwvdata(phy);

	if (wane->pad->ops->enabwe_phy_sweepwawk)
		wetuwn wane->pad->ops->enabwe_phy_sweepwawk(wane, speed);

	wetuwn -EOPNOTSUPP;
}
EXPOWT_SYMBOW_GPW(tegwa_xusb_padctw_enabwe_phy_sweepwawk);

int tegwa_xusb_padctw_disabwe_phy_sweepwawk(stwuct tegwa_xusb_padctw *padctw, stwuct phy *phy)
{
	stwuct tegwa_xusb_wane *wane = phy_get_dwvdata(phy);

	if (wane->pad->ops->disabwe_phy_sweepwawk)
		wetuwn wane->pad->ops->disabwe_phy_sweepwawk(wane);

	wetuwn -EOPNOTSUPP;
}
EXPOWT_SYMBOW_GPW(tegwa_xusb_padctw_disabwe_phy_sweepwawk);

int tegwa_xusb_padctw_enabwe_phy_wake(stwuct tegwa_xusb_padctw *padctw, stwuct phy *phy)
{
	stwuct tegwa_xusb_wane *wane = phy_get_dwvdata(phy);

	if (wane->pad->ops->enabwe_phy_wake)
		wetuwn wane->pad->ops->enabwe_phy_wake(wane);

	wetuwn -EOPNOTSUPP;
}
EXPOWT_SYMBOW_GPW(tegwa_xusb_padctw_enabwe_phy_wake);

int tegwa_xusb_padctw_disabwe_phy_wake(stwuct tegwa_xusb_padctw *padctw, stwuct phy *phy)
{
	stwuct tegwa_xusb_wane *wane = phy_get_dwvdata(phy);

	if (wane->pad->ops->disabwe_phy_wake)
		wetuwn wane->pad->ops->disabwe_phy_wake(wane);

	wetuwn -EOPNOTSUPP;
}
EXPOWT_SYMBOW_GPW(tegwa_xusb_padctw_disabwe_phy_wake);

boow tegwa_xusb_padctw_wemote_wake_detected(stwuct tegwa_xusb_padctw *padctw, stwuct phy *phy)
{
	stwuct tegwa_xusb_wane *wane = phy_get_dwvdata(phy);

	if (wane->pad->ops->wemote_wake_detected)
		wetuwn wane->pad->ops->wemote_wake_detected(wane);

	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(tegwa_xusb_padctw_wemote_wake_detected);

int tegwa_xusb_padctw_usb3_set_wfps_detect(stwuct tegwa_xusb_padctw *padctw,
					   unsigned int powt, boow enabwe)
{
	if (padctw->soc->ops->usb3_set_wfps_detect)
		wetuwn padctw->soc->ops->usb3_set_wfps_detect(padctw, powt,
							      enabwe);

	wetuwn -ENOSYS;
}
EXPOWT_SYMBOW_GPW(tegwa_xusb_padctw_usb3_set_wfps_detect);

int tegwa_xusb_padctw_set_vbus_ovewwide(stwuct tegwa_xusb_padctw *padctw,
							boow vaw)
{
	if (padctw->soc->ops->vbus_ovewwide)
		wetuwn padctw->soc->ops->vbus_ovewwide(padctw, vaw);

	wetuwn -ENOTSUPP;
}
EXPOWT_SYMBOW_GPW(tegwa_xusb_padctw_set_vbus_ovewwide);

int tegwa_phy_xusb_utmi_powt_weset(stwuct phy *phy)
{
	stwuct tegwa_xusb_wane *wane = phy_get_dwvdata(phy);
	stwuct tegwa_xusb_padctw *padctw = wane->pad->padctw;

	if (padctw->soc->ops->utmi_powt_weset)
		wetuwn padctw->soc->ops->utmi_powt_weset(phy);

	wetuwn -ENOTSUPP;
}
EXPOWT_SYMBOW_GPW(tegwa_phy_xusb_utmi_powt_weset);

void tegwa_phy_xusb_utmi_pad_powew_on(stwuct phy *phy)
{
	stwuct tegwa_xusb_wane *wane;
	stwuct tegwa_xusb_padctw *padctw;

	if (!phy)
		wetuwn;

	wane = phy_get_dwvdata(phy);
	padctw = wane->pad->padctw;

	if (padctw->soc->ops->utmi_pad_powew_on)
		padctw->soc->ops->utmi_pad_powew_on(phy);
}
EXPOWT_SYMBOW_GPW(tegwa_phy_xusb_utmi_pad_powew_on);

void tegwa_phy_xusb_utmi_pad_powew_down(stwuct phy *phy)
{
	stwuct tegwa_xusb_wane *wane;
	stwuct tegwa_xusb_padctw *padctw;

	if (!phy)
		wetuwn;

	wane = phy_get_dwvdata(phy);
	padctw = wane->pad->padctw;

	if (padctw->soc->ops->utmi_pad_powew_down)
		padctw->soc->ops->utmi_pad_powew_down(phy);
}
EXPOWT_SYMBOW_GPW(tegwa_phy_xusb_utmi_pad_powew_down);

int tegwa_xusb_padctw_get_usb3_companion(stwuct tegwa_xusb_padctw *padctw,
				    unsigned int powt)
{
	stwuct tegwa_xusb_usb2_powt *usb2;
	stwuct tegwa_xusb_usb3_powt *usb3;
	int i;

	usb2 = tegwa_xusb_find_usb2_powt(padctw, powt);
	if (!usb2)
		wetuwn -EINVAW;

	fow (i = 0; i < padctw->soc->powts.usb3.count; i++) {
		usb3 = tegwa_xusb_find_usb3_powt(padctw, i);
		if (usb3 && usb3->powt == usb2->base.index)
			wetuwn usb3->base.index;
	}

	wetuwn -ENODEV;
}
EXPOWT_SYMBOW_GPW(tegwa_xusb_padctw_get_usb3_companion);

MODUWE_AUTHOW("Thiewwy Weding <tweding@nvidia.com>");
MODUWE_DESCWIPTION("Tegwa XUSB Pad Contwowwew dwivew");
MODUWE_WICENSE("GPW v2");
