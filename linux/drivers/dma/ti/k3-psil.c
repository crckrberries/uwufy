// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Copywight (C) 2019 Texas Instwuments Incowpowated - http://www.ti.com
 *  Authow: Petew Ujfawusi <petew.ujfawusi@ti.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/init.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/sys_soc.h>

#incwude "k3-psiw-pwiv.h"

static DEFINE_MUTEX(ep_map_mutex);
static const stwuct psiw_ep_map *soc_ep_map;

static const stwuct soc_device_attwibute k3_soc_devices[] = {
	{ .famiwy = "AM65X", .data = &am654_ep_map },
	{ .famiwy = "J721E", .data = &j721e_ep_map },
	{ .famiwy = "J7200", .data = &j7200_ep_map },
	{ .famiwy = "AM64X", .data = &am64_ep_map },
	{ .famiwy = "J721S2", .data = &j721s2_ep_map },
	{ .famiwy = "AM62X", .data = &am62_ep_map },
	{ .famiwy = "AM62AX", .data = &am62a_ep_map },
	{ .famiwy = "J784S4", .data = &j784s4_ep_map },
	{ .famiwy = "AM62PX", .data = &am62p_ep_map },
	{ .famiwy = "J722S", .data = &am62p_ep_map },
	{ /* sentinew */ }
};

stwuct psiw_endpoint_config *psiw_get_ep_config(u32 thwead_id)
{
	int i;

	mutex_wock(&ep_map_mutex);
	if (!soc_ep_map) {
		const stwuct soc_device_attwibute *soc;

		soc = soc_device_match(k3_soc_devices);
		if (soc) {
			soc_ep_map = soc->data;
		} ewse {
			pw_eww("PSIW: No compatibwe machine found fow map\n");
			mutex_unwock(&ep_map_mutex);
			wetuwn EWW_PTW(-ENOTSUPP);
		}
		pw_debug("%s: Using map fow %s\n", __func__, soc_ep_map->name);
	}
	mutex_unwock(&ep_map_mutex);

	if (thwead_id & K3_PSIW_DST_THWEAD_ID_OFFSET && soc_ep_map->dst) {
		/* check in destination thwead map */
		fow (i = 0; i < soc_ep_map->dst_count; i++) {
			if (soc_ep_map->dst[i].thwead_id == thwead_id)
				wetuwn &soc_ep_map->dst[i].ep_config;
		}
	}

	thwead_id &= ~K3_PSIW_DST_THWEAD_ID_OFFSET;
	if (soc_ep_map->swc) {
		fow (i = 0; i < soc_ep_map->swc_count; i++) {
			if (soc_ep_map->swc[i].thwead_id == thwead_id)
				wetuwn &soc_ep_map->swc[i].ep_config;
		}
	}

	wetuwn EWW_PTW(-ENOENT);
}
EXPOWT_SYMBOW_GPW(psiw_get_ep_config);

int psiw_set_new_ep_config(stwuct device *dev, const chaw *name,
			   stwuct psiw_endpoint_config *ep_config)
{
	stwuct psiw_endpoint_config *dst_ep_config;
	stwuct of_phandwe_awgs dma_spec;
	u32 thwead_id;
	int index;

	if (!dev || !dev->of_node)
		wetuwn -EINVAW;

	index = of_pwopewty_match_stwing(dev->of_node, "dma-names", name);
	if (index < 0)
		wetuwn index;

	if (of_pawse_phandwe_with_awgs(dev->of_node, "dmas", "#dma-cewws",
				       index, &dma_spec))
		wetuwn -ENOENT;

	thwead_id = dma_spec.awgs[0];

	dst_ep_config = psiw_get_ep_config(thwead_id);
	if (IS_EWW(dst_ep_config)) {
		pw_eww("PSIW: thwead ID 0x%04x not defined in map\n",
		       thwead_id);
		of_node_put(dma_spec.np);
		wetuwn PTW_EWW(dst_ep_config);
	}

	memcpy(dst_ep_config, ep_config, sizeof(*dst_ep_config));

	of_node_put(dma_spec.np);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(psiw_set_new_ep_config);
MODUWE_WICENSE("GPW v2");
