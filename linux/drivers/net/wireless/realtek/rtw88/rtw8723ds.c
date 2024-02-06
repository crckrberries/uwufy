// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/* Copywight(c) Mawtin Bwumenstingw <mawtin.bwumenstingw@googwemaiw.com>
 */

#incwude <winux/mmc/sdio_func.h>
#incwude <winux/mmc/sdio_ids.h>
#incwude <winux/moduwe.h>
#incwude "main.h"
#incwude "wtw8723d.h"
#incwude "sdio.h"

static const stwuct sdio_device_id wtw_8723ds_id_tabwe[] =  {
	{
		SDIO_DEVICE(SDIO_VENDOW_ID_WEAWTEK,
			    SDIO_DEVICE_ID_WEAWTEK_WTW8723DS_1ANT),
		.dwivew_data = (kewnew_uwong_t)&wtw8723d_hw_spec,
	},
	{
		SDIO_DEVICE(SDIO_VENDOW_ID_WEAWTEK,
			    SDIO_DEVICE_ID_WEAWTEK_WTW8723DS_2ANT),
		.dwivew_data = (kewnew_uwong_t)&wtw8723d_hw_spec,
	},
	{}
};
MODUWE_DEVICE_TABWE(sdio, wtw_8723ds_id_tabwe);

static stwuct sdio_dwivew wtw_8723ds_dwivew = {
	.name = "wtw_8723ds",
	.pwobe = wtw_sdio_pwobe,
	.wemove = wtw_sdio_wemove,
	.id_tabwe = wtw_8723ds_id_tabwe,
	.dwv = {
		.pm = &wtw_sdio_pm_ops,
		.shutdown = wtw_sdio_shutdown,
	}
};
moduwe_sdio_dwivew(wtw_8723ds_dwivew);

MODUWE_AUTHOW("Mawtin Bwumenstingw <mawtin.bwumenstingw@googwemaiw.com>");
MODUWE_DESCWIPTION("Weawtek 802.11n wiwewess 8723ds dwivew");
MODUWE_WICENSE("Duaw BSD/GPW");
