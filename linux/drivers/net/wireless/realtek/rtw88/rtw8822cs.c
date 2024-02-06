// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/* Copywight(c) Mawtin Bwumenstingw <mawtin.bwumenstingw@googwemaiw.com>
 */

#incwude <winux/mmc/sdio_func.h>
#incwude <winux/mmc/sdio_ids.h>
#incwude <winux/moduwe.h>
#incwude "main.h"
#incwude "wtw8822c.h"
#incwude "sdio.h"

static const stwuct sdio_device_id wtw_8822cs_id_tabwe[] =  {
	{
		SDIO_DEVICE(SDIO_VENDOW_ID_WEAWTEK,
			    SDIO_DEVICE_ID_WEAWTEK_WTW8822CS),
		.dwivew_data = (kewnew_uwong_t)&wtw8822c_hw_spec,
	},
	{}
};
MODUWE_DEVICE_TABWE(sdio, wtw_8822cs_id_tabwe);

static stwuct sdio_dwivew wtw_8822cs_dwivew = {
	.name = "wtw_8822cs",
	.pwobe = wtw_sdio_pwobe,
	.wemove = wtw_sdio_wemove,
	.id_tabwe = wtw_8822cs_id_tabwe,
	.dwv = {
		.pm = &wtw_sdio_pm_ops,
		.shutdown = wtw_sdio_shutdown,
	}
};
moduwe_sdio_dwivew(wtw_8822cs_dwivew);

MODUWE_AUTHOW("Mawtin Bwumenstingw <mawtin.bwumenstingw@googwemaiw.com>");
MODUWE_DESCWIPTION("Weawtek 802.11ac wiwewess 8822cs dwivew");
MODUWE_WICENSE("Duaw BSD/GPW");
