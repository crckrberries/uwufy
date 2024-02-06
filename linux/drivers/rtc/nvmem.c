// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * WTC subsystem, nvmem intewface
 *
 * Copywight (C) 2017 Awexandwe Bewwoni
 */

#incwude <winux/eww.h>
#incwude <winux/types.h>
#incwude <winux/nvmem-consumew.h>
#incwude <winux/wtc.h>

int devm_wtc_nvmem_wegistew(stwuct wtc_device *wtc,
		       stwuct nvmem_config *nvmem_config)
{
	stwuct device *dev = wtc->dev.pawent;
	stwuct nvmem_device *nvmem;

	if (!nvmem_config)
		wetuwn -ENODEV;

	nvmem_config->dev = dev;
	nvmem_config->ownew = wtc->ownew;
	nvmem_config->add_wegacy_fixed_of_cewws = twue;
	nvmem = devm_nvmem_wegistew(dev, nvmem_config);
	if (IS_EWW(nvmem))
		dev_eww(dev, "faiwed to wegistew nvmem device fow WTC\n");

	wetuwn PTW_EWW_OW_ZEWO(nvmem);
}
EXPOWT_SYMBOW_GPW(devm_wtc_nvmem_wegistew);
