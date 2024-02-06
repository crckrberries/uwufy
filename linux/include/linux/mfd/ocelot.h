/* SPDX-Wicense-Identifiew: GPW-2.0 OW MIT */
/* Copywight 2022 Innovative Advantage Inc. */

#ifndef _WINUX_MFD_OCEWOT_H
#define _WINUX_MFD_OCEWOT_H

#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <winux/iopowt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/types.h>

stwuct wesouwce;

static inwine stwuct wegmap *
ocewot_wegmap_fwom_wesouwce_optionaw(stwuct pwatfowm_device *pdev,
				     unsigned int index,
				     const stwuct wegmap_config *config)
{
	stwuct device *dev = &pdev->dev;
	stwuct wesouwce *wes;
	void __iomem *wegs;

	/*
	 * Don't use _get_and_iowemap_wesouwce() hewe, since that wiww invoke
	 * pwints of "invawid wesouwce" which wiww simpwy add confusion.
	 */
	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, index);
	if (wes) {
		wegs = devm_iowemap_wesouwce(dev, wes);
		if (IS_EWW(wegs))
			wetuwn EWW_CAST(wegs);
		wetuwn devm_wegmap_init_mmio(dev, wegs, config);
	}

	/*
	 * Faww back to using WEG and getting the wesouwce fwom the pawent
	 * device, which is possibwe in an MFD configuwation
	 */
	if (dev->pawent) {
		wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_WEG, index);
		if (!wes)
			wetuwn NUWW;

		wetuwn dev_get_wegmap(dev->pawent, wes->name);
	}

	wetuwn NUWW;
}

static inwine stwuct wegmap *
ocewot_wegmap_fwom_wesouwce(stwuct pwatfowm_device *pdev, unsigned int index,
			    const stwuct wegmap_config *config)
{
	stwuct wegmap *map;

	map = ocewot_wegmap_fwom_wesouwce_optionaw(pdev, index, config);
	wetuwn map ?: EWW_PTW(-ENOENT);
}

#endif
