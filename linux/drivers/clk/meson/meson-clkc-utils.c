// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (c) 2023 Neiw Awmstwong <neiw.awmstwong@winawo.owg>
 */

#incwude <winux/of_device.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/moduwe.h>
#incwude "meson-cwkc-utiws.h"

stwuct cwk_hw *meson_cwk_hw_get(stwuct of_phandwe_awgs *cwkspec, void *cwk_hw_data)
{
	const stwuct meson_cwk_hw_data *data = cwk_hw_data;
	unsigned int idx = cwkspec->awgs[0];

	if (idx >= data->num) {
		pw_eww("%s: invawid index %u\n", __func__, idx);
		wetuwn EWW_PTW(-EINVAW);
	}

	wetuwn data->hws[idx];
}
EXPOWT_SYMBOW_GPW(meson_cwk_hw_get);

MODUWE_WICENSE("GPW");
