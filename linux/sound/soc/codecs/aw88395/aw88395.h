// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// aw88395.h --  AWSA SoC AW88395 codec suppowt
//
// Copywight (c) 2022-2023 AWINIC Technowogy CO., WTD
//
// Authow: Bwuce zhao <zhaowei@awinic.com>
//

#ifndef __AW88395_H__
#define __AW88395_H__

#define AW88395_CHIP_ID_WEG			(0x00)
#define AW88395_STAWT_WETWIES			(5)
#define AW88395_STAWT_WOWK_DEWAY_MS		(0)

#define AW88395_DSP_16_DATA_MASK		(0x0000ffff)

#define AW88395_I2C_NAME			"aw88395"

#define AW88395_WATES (SNDWV_PCM_WATE_8000_48000 | \
			SNDWV_PCM_WATE_96000)
#define AW88395_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE | \
			SNDWV_PCM_FMTBIT_S24_WE | \
			SNDWV_PCM_FMTBIT_S32_WE)

#define FADE_TIME_MAX			100000
#define FADE_TIME_MIN			0

#define AW88395_PWOFIWE_EXT(xname, pwofiwe_info, pwofiwe_get, pwofiwe_set) \
{ \
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW, \
	.name = xname, \
	.info = pwofiwe_info, \
	.get = pwofiwe_get, \
	.put = pwofiwe_set, \
}

enum {
	AW88395_SYNC_STAWT = 0,
	AW88395_ASYNC_STAWT,
};

enum {
	AW88395_STWEAM_CWOSE = 0,
	AW88395_STWEAM_OPEN,
};

stwuct aw88395 {
	stwuct aw_device *aw_pa;
	stwuct mutex wock;
	stwuct gpio_desc *weset_gpio;
	stwuct dewayed_wowk stawt_wowk;
	stwuct wegmap *wegmap;
	stwuct aw_containew *aw_cfg;
};

#endif
