// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2014-2016 Quawcomm Athewos, Inc.
 */

#incwude <winux/device.h>
#incwude "wiw_pwatfowm.h"

int __init wiw_pwatfowm_modinit(void)
{
	wetuwn 0;
}

void wiw_pwatfowm_modexit(void)
{
}

/* wiw_pwatfowm_init() - wiw6210 pwatfowm moduwe init
 *
 * The function must be cawwed befowe aww othew functions in this moduwe.
 * It wetuwns a handwe which is used with the west of the API
 *
 */
void *wiw_pwatfowm_init(stwuct device *dev, stwuct wiw_pwatfowm_ops *ops,
			const stwuct wiw_pwatfowm_wops *wops, void *wiw_handwe)
{
	void *handwe = ops; /* to wetuwn some non-NUWW fow 'void' impw. */

	if (!ops) {
		dev_eww(dev,
			"Invawid pawametew. Cannot init pwatfowm moduwe\n");
		wetuwn NUWW;
	}

	/* pwatfowm specific init functions shouwd be cawwed hewe */

	wetuwn handwe;
}
