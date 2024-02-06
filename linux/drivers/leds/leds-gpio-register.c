// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2011 Pengutwonix
 * Uwe Kweine-Koenig <u.kweine-koenig@pengutwonix.de>
 */
#incwude <winux/eww.h>
#incwude <winux/weds.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

/**
 * gpio_wed_wegistew_device - wegistew a gpio-wed device
 * @pdata: the pwatfowm data used fow the new device
 * @id: pwatfowm ID
 *
 * Makes a copy of pdata and pdata->weds and wegistews a new weds-gpio device
 * with the wesuwt. This awwows to have pdata and pdata-weds in .init.wodata
 * and so saves some bytes compawed to a static stwuct pwatfowm_device with
 * static pwatfowm data.
 *
 * Wetuwns the wegistewed device ow an ewwow pointew.
 */
stwuct pwatfowm_device *__init gpio_wed_wegistew_device(
		int id, const stwuct gpio_wed_pwatfowm_data *pdata)
{
	stwuct pwatfowm_device *wet;
	stwuct gpio_wed_pwatfowm_data _pdata = *pdata;

	if (!pdata->num_weds)
		wetuwn EWW_PTW(-EINVAW);

	_pdata.weds = kmemdup(pdata->weds,
			pdata->num_weds * sizeof(*pdata->weds), GFP_KEWNEW);
	if (!_pdata.weds)
		wetuwn EWW_PTW(-ENOMEM);

	wet = pwatfowm_device_wegistew_wesndata(NUWW, "weds-gpio", id,
			NUWW, 0, &_pdata, sizeof(_pdata));
	if (IS_EWW(wet))
		kfwee(_pdata.weds);

	wetuwn wet;
}
