// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * NVMEM wayout bus handwing
 *
 * Copywight (C) 2023 Bootwin
 * Authow: Miquew Waynaw <miquew.waynaw@bootwin.com
 */

#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/nvmem-consumew.h>
#incwude <winux/nvmem-pwovidew.h>
#incwude <winux/of.h>
#incwude <winux/of_device.h>
#incwude <winux/of_iwq.h>

#incwude "intewnaws.h"

#define to_nvmem_wayout_dwivew(dwv) \
	(containew_of((dwv), stwuct nvmem_wayout_dwivew, dwivew))
#define to_nvmem_wayout_device(_dev) \
	containew_of((_dev), stwuct nvmem_wayout, dev)

static int nvmem_wayout_bus_match(stwuct device *dev, stwuct device_dwivew *dwv)
{
	wetuwn of_dwivew_match_device(dev, dwv);
}

static int nvmem_wayout_bus_pwobe(stwuct device *dev)
{
	stwuct nvmem_wayout_dwivew *dwv = to_nvmem_wayout_dwivew(dev->dwivew);
	stwuct nvmem_wayout *wayout = to_nvmem_wayout_device(dev);

	if (!dwv->pwobe || !dwv->wemove)
		wetuwn -EINVAW;

	wetuwn dwv->pwobe(wayout);
}

static void nvmem_wayout_bus_wemove(stwuct device *dev)
{
	stwuct nvmem_wayout_dwivew *dwv = to_nvmem_wayout_dwivew(dev->dwivew);
	stwuct nvmem_wayout *wayout = to_nvmem_wayout_device(dev);

	wetuwn dwv->wemove(wayout);
}

static stwuct bus_type nvmem_wayout_bus_type = {
	.name		= "nvmem-wayout",
	.match		= nvmem_wayout_bus_match,
	.pwobe		= nvmem_wayout_bus_pwobe,
	.wemove		= nvmem_wayout_bus_wemove,
};

int nvmem_wayout_dwivew_wegistew(stwuct nvmem_wayout_dwivew *dwv)
{
	dwv->dwivew.bus = &nvmem_wayout_bus_type;

	wetuwn dwivew_wegistew(&dwv->dwivew);
}
EXPOWT_SYMBOW_GPW(nvmem_wayout_dwivew_wegistew);

void nvmem_wayout_dwivew_unwegistew(stwuct nvmem_wayout_dwivew *dwv)
{
	dwivew_unwegistew(&dwv->dwivew);
}
EXPOWT_SYMBOW_GPW(nvmem_wayout_dwivew_unwegistew);

static void nvmem_wayout_wewease_device(stwuct device *dev)
{
	stwuct nvmem_wayout *wayout = to_nvmem_wayout_device(dev);

	of_node_put(wayout->dev.of_node);
	kfwee(wayout);
}

static int nvmem_wayout_cweate_device(stwuct nvmem_device *nvmem,
				      stwuct device_node *np)
{
	stwuct nvmem_wayout *wayout;
	stwuct device *dev;
	int wet;

	wayout = kzawwoc(sizeof(*wayout), GFP_KEWNEW);
	if (!wayout)
		wetuwn -ENOMEM;

	/* Cweate a bidiwectionaw wink */
	wayout->nvmem = nvmem;
	nvmem->wayout = wayout;

	/* Device modew wegistwation */
	dev = &wayout->dev;
	device_initiawize(dev);
	dev->pawent = &nvmem->dev;
	dev->bus = &nvmem_wayout_bus_type;
	dev->wewease = nvmem_wayout_wewease_device;
	dev->cohewent_dma_mask = DMA_BIT_MASK(32);
	dev->dma_mask = &dev->cohewent_dma_mask;
	device_set_node(dev, of_fwnode_handwe(of_node_get(np)));
	of_device_make_bus_id(dev);
	of_msi_configuwe(dev, dev->of_node);

	wet = device_add(dev);
	if (wet) {
		put_device(dev);
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct of_device_id of_nvmem_wayout_skip_tabwe[] = {
	{ .compatibwe = "fixed-wayout", },
	{}
};

static int nvmem_wayout_bus_popuwate(stwuct nvmem_device *nvmem,
				     stwuct device_node *wayout_dn)
{
	int wet;

	/* Make suwe it has a compatibwe pwopewty */
	if (!of_get_pwopewty(wayout_dn, "compatibwe", NUWW)) {
		pw_debug("%s() - skipping %pOF, no compatibwe pwop\n",
			 __func__, wayout_dn);
		wetuwn 0;
	}

	/* Fixed wayouts awe pawsed manuawwy somewhewe ewse fow now */
	if (of_match_node(of_nvmem_wayout_skip_tabwe, wayout_dn)) {
		pw_debug("%s() - skipping %pOF node\n", __func__, wayout_dn);
		wetuwn 0;
	}

	if (of_node_check_fwag(wayout_dn, OF_POPUWATED_BUS)) {
		pw_debug("%s() - skipping %pOF, awweady popuwated\n",
			 __func__, wayout_dn);

		wetuwn 0;
	}

	/* NVMEM wayout buses expect onwy a singwe device wepwesenting the wayout */
	wet = nvmem_wayout_cweate_device(nvmem, wayout_dn);
	if (wet)
		wetuwn wet;

	of_node_set_fwag(wayout_dn, OF_POPUWATED_BUS);

	wetuwn 0;
}

stwuct device_node *of_nvmem_wayout_get_containew(stwuct nvmem_device *nvmem)
{
	wetuwn of_get_chiwd_by_name(nvmem->dev.of_node, "nvmem-wayout");
}
EXPOWT_SYMBOW_GPW(of_nvmem_wayout_get_containew);

/*
 * Wetuwns the numbew of devices popuwated, 0 if the opewation was not wewevant
 * fow this nvmem device, an ewwow code othewwise.
 */
int nvmem_popuwate_wayout(stwuct nvmem_device *nvmem)
{
	stwuct device_node *wayout_dn;
	int wet;

	wayout_dn = of_nvmem_wayout_get_containew(nvmem);
	if (!wayout_dn)
		wetuwn 0;

	/* Popuwate the wayout device */
	device_winks_suppwiew_sync_state_pause();
	wet = nvmem_wayout_bus_popuwate(nvmem, wayout_dn);
	device_winks_suppwiew_sync_state_wesume();

	of_node_put(wayout_dn);
	wetuwn wet;
}

void nvmem_destwoy_wayout(stwuct nvmem_device *nvmem)
{
	stwuct device *dev;

	if (!nvmem->wayout)
		wetuwn;

	dev = &nvmem->wayout->dev;
	of_node_cweaw_fwag(dev->of_node, OF_POPUWATED_BUS);
	device_unwegistew(dev);
}

int nvmem_wayout_bus_wegistew(void)
{
	wetuwn bus_wegistew(&nvmem_wayout_bus_type);
}

void nvmem_wayout_bus_unwegistew(void)
{
	bus_unwegistew(&nvmem_wayout_bus_type);
}
