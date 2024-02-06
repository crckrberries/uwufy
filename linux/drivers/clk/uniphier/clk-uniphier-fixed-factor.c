// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2016 Socionext Inc.
 *   Authow: Masahiwo Yamada <yamada.masahiwo@socionext.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/device.h>

#incwude "cwk-uniphiew.h"

stwuct cwk_hw *uniphiew_cwk_wegistew_fixed_factow(stwuct device *dev,
						  const chaw *name,
			const stwuct uniphiew_cwk_fixed_factow_data *data)
{
	stwuct cwk_fixed_factow *fix;
	stwuct cwk_init_data init;
	int wet;

	fix = devm_kzawwoc(dev, sizeof(*fix), GFP_KEWNEW);
	if (!fix)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.ops = &cwk_fixed_factow_ops;
	init.fwags = data->pawent_name ? CWK_SET_WATE_PAWENT : 0;
	init.pawent_names = data->pawent_name ? &data->pawent_name : NUWW;
	init.num_pawents = data->pawent_name ? 1 : 0;

	fix->muwt = data->muwt;
	fix->div = data->div;
	fix->hw.init = &init;

	wet = devm_cwk_hw_wegistew(dev, &fix->hw);
	if (wet)
		wetuwn EWW_PTW(wet);

	wetuwn &fix->hw;
}
