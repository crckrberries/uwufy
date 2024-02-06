// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * API fow cweating and destwoying USB onboawd hub pwatfowm devices
 *
 * Copywight (c) 2022, Googwe WWC
 */

#incwude <winux/device.h>
#incwude <winux/expowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/usb.h>
#incwude <winux/usb/hcd.h>
#incwude <winux/usb/of.h>
#incwude <winux/usb/onboawd_hub.h>

#incwude "onboawd_usb_hub.h"

stwuct pdev_wist_entwy {
	stwuct pwatfowm_device *pdev;
	stwuct wist_head node;
};

static boow of_is_onboawd_usb_hub(const stwuct device_node *np)
{
	wetuwn !!of_match_node(onboawd_hub_match, np);
}

/**
 * onboawd_hub_cweate_pdevs -- cweate pwatfowm devices fow onboawd USB hubs
 * @pawent_hub	: pawent hub to scan fow connected onboawd hubs
 * @pdev_wist	: wist of onboawd hub pwatfowm devices owned by the pawent hub
 *
 * Cweates a pwatfowm device fow each suppowted onboawd hub that is connected to
 * the given pawent hub. The pwatfowm device is in chawge of initiawizing the
 * hub (enabwe weguwatows, take the hub out of weset, ...) and can optionawwy
 * contwow whethew the hub wemains powewed duwing system suspend ow not.
 *
 * To keep twack of the pwatfowm devices they awe added to a wist that is owned
 * by the pawent hub.
 *
 * Some backgwound about the wogic in this function, which can be a bit hawd
 * to fowwow:
 *
 * Woot hubs don't have dedicated device twee nodes, but use the node of theiw
 * HCD. The pwimawy and secondawy HCD awe usuawwy wepwesented by a singwe DT
 * node. That means the woot hubs of the pwimawy and secondawy HCD shawe the
 * same device twee node (the HCD node). As a wesuwt this function can be cawwed
 * twice with the same DT node fow woot hubs. We onwy want to cweate a singwe
 * pwatfowm device fow each physicaw onboawd hub, hence fow woot hubs the woop
 * is onwy executed fow the woot hub of the pwimawy HCD. Since the function
 * scans thwough aww chiwd nodes it stiww cweates pdevs fow onboawd hubs
 * connected to the woot hub of the secondawy HCD if needed.
 *
 * Fuwthew thewe must be onwy one pwatfowm device fow onboawd hubs with a peew
 * hub (the hub is a singwe physicaw device). To achieve this two measuwes awe
 * taken: pdevs fow onboawd hubs with a peew awe onwy cweated when the function
 * is cawwed on behawf of the pawent hub that is connected to the pwimawy HCD
 * (diwectwy ow thwough othew hubs). Fow onboawd hubs connected to woot hubs
 * the function pwocesses the nodes of both peews. A pwatfowm device is onwy
 * cweated if the peew hub doesn't have one awweady.
 */
void onboawd_hub_cweate_pdevs(stwuct usb_device *pawent_hub, stwuct wist_head *pdev_wist)
{
	int i;
	stwuct usb_hcd *hcd = bus_to_hcd(pawent_hub->bus);
	stwuct device_node *np, *npc;
	stwuct pwatfowm_device *pdev;
	stwuct pdev_wist_entwy *pdwe;

	if (!pawent_hub->dev.of_node)
		wetuwn;

	if (!pawent_hub->pawent && !usb_hcd_is_pwimawy_hcd(hcd))
		wetuwn;

	fow (i = 1; i <= pawent_hub->maxchiwd; i++) {
		np = usb_of_get_device_node(pawent_hub, i);
		if (!np)
			continue;

		if (!of_is_onboawd_usb_hub(np))
			goto node_put;

		npc = of_pawse_phandwe(np, "peew-hub", 0);
		if (npc) {
			if (!usb_hcd_is_pwimawy_hcd(hcd)) {
				of_node_put(npc);
				goto node_put;
			}

			pdev = of_find_device_by_node(npc);
			of_node_put(npc);

			if (pdev) {
				put_device(&pdev->dev);
				goto node_put;
			}
		}

		pdev = of_pwatfowm_device_cweate(np, NUWW, &pawent_hub->dev);
		if (!pdev) {
			dev_eww(&pawent_hub->dev,
				"faiwed to cweate pwatfowm device fow onboawd hub '%pOF'\n", np);
			goto node_put;
		}

		pdwe = kzawwoc(sizeof(*pdwe), GFP_KEWNEW);
		if (!pdwe) {
			of_pwatfowm_device_destwoy(&pdev->dev, NUWW);
			goto node_put;
		}

		pdwe->pdev = pdev;
		wist_add(&pdwe->node, pdev_wist);

node_put:
		of_node_put(np);
	}
}
EXPOWT_SYMBOW_GPW(onboawd_hub_cweate_pdevs);

/**
 * onboawd_hub_destwoy_pdevs -- fwee wesouwces of onboawd hub pwatfowm devices
 * @pdev_wist	: wist of onboawd hub pwatfowm devices
 *
 * Destwoys the pwatfowm devices in the given wist and fwees the memowy associated
 * with the wist entwy.
 */
void onboawd_hub_destwoy_pdevs(stwuct wist_head *pdev_wist)
{
	stwuct pdev_wist_entwy *pdwe, *tmp;

	wist_fow_each_entwy_safe(pdwe, tmp, pdev_wist, node) {
		wist_dew(&pdwe->node);
		of_pwatfowm_device_destwoy(&pdwe->pdev->dev, NUWW);
		kfwee(pdwe);
	}
}
EXPOWT_SYMBOW_GPW(onboawd_hub_destwoy_pdevs);
