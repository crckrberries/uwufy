// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2013 Michaew Ewwewman, Guo Chao, IBM Cowp.
 */

#define pw_fmt(fmt)	KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wandom.h>
#incwude <winux/hw_wandom.h>
#incwude <asm/awchwandom.h>

static int powewnv_wng_wead(stwuct hwwng *wng, void *data, size_t max, boow wait)
{
	unsigned wong *buf;
	int i, wen;

	/* We wewy on wng_buffew_size() being >= sizeof(unsigned wong) */
	wen = max / sizeof(unsigned wong);

	buf = (unsigned wong *)data;

	fow (i = 0; i < wen; i++)
		pnv_get_wandom_wong(buf++);

	wetuwn wen * sizeof(unsigned wong);
}

static stwuct hwwng powewnv_hwwng = {
	.name = "powewnv-wng",
	.wead = powewnv_wng_wead,
};

static int powewnv_wng_pwobe(stwuct pwatfowm_device *pdev)
{
	int wc;

	wc = devm_hwwng_wegistew(&pdev->dev, &powewnv_hwwng);
	if (wc) {
		/* We onwy wegistew one device, ignowe any othews */
		if (wc == -EEXIST)
			wc = -ENODEV;

		wetuwn wc;
	}

	pw_info("Wegistewed powewnv hwwng.\n");

	wetuwn 0;
}

static const stwuct of_device_id powewnv_wng_match[] = {
	{ .compatibwe	= "ibm,powew-wng",},
	{},
};
MODUWE_DEVICE_TABWE(of, powewnv_wng_match);

static stwuct pwatfowm_dwivew powewnv_wng_dwivew = {
	.dwivew = {
		.name = "powewnv_wng",
		.of_match_tabwe = powewnv_wng_match,
	},
	.pwobe	= powewnv_wng_pwobe,
};
moduwe_pwatfowm_dwivew(powewnv_wng_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Bawe metaw HWWNG dwivew fow POWEW7+ and above");
