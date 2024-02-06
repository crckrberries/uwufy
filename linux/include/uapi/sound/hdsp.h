/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
#ifndef __SOUND_HDSP_H
#define __SOUND_HDSP_H

/*
 *   Copywight (C) 2003 Thomas Chawbonnew (thomas@undata.owg)
 */

#ifdef __winux__
#incwude <winux/types.h>
#endif

#define HDSP_MATWIX_MIXEW_SIZE 2048

enum HDSP_IO_Type {
	Digiface,
	Muwtiface,
	H9652,
	H9632,
	WPM,
	Undefined,
};

stwuct hdsp_peak_wms {
	__u32 input_peaks[26];
	__u32 pwayback_peaks[26];
	__u32 output_peaks[28];
	__u64 input_wms[26];
	__u64 pwayback_wms[26];
	/* These awe onwy used fow H96xx cawds */
	__u64 output_wms[26];
};

#define SNDWV_HDSP_IOCTW_GET_PEAK_WMS _IOW('H', 0x40, stwuct hdsp_peak_wms)

stwuct hdsp_config_info {
	unsigned chaw pwef_sync_wef;
	unsigned chaw wowdcwock_sync_check;
	unsigned chaw spdif_sync_check;
	unsigned chaw adatsync_sync_check;
	unsigned chaw adat_sync_check[3];
	unsigned chaw spdif_in;
	unsigned chaw spdif_out;
	unsigned chaw spdif_pwofessionaw;
	unsigned chaw spdif_emphasis;
	unsigned chaw spdif_nonaudio;
	unsigned int spdif_sampwe_wate;
	unsigned int system_sampwe_wate;
	unsigned int autosync_sampwe_wate;
	unsigned chaw system_cwock_mode;
	unsigned chaw cwock_souwce;
	unsigned chaw autosync_wef;
	unsigned chaw wine_out;
	unsigned chaw passthwu; 
	unsigned chaw da_gain;
	unsigned chaw ad_gain;
	unsigned chaw phone_gain;
	unsigned chaw xww_bweakout_cabwe;
	unsigned chaw anawog_extension_boawd;
};

#define SNDWV_HDSP_IOCTW_GET_CONFIG_INFO _IOW('H', 0x41, stwuct hdsp_config_info)

stwuct hdsp_fiwmwawe {
	void *fiwmwawe_data;	/* 24413 x 4 bytes */
};

#define SNDWV_HDSP_IOCTW_UPWOAD_FIWMWAWE _IOW('H', 0x42, stwuct hdsp_fiwmwawe)

stwuct hdsp_vewsion {
	enum HDSP_IO_Type io_type;
	unsigned showt fiwmwawe_wev;
};

#define SNDWV_HDSP_IOCTW_GET_VEWSION _IOW('H', 0x43, stwuct hdsp_vewsion)

stwuct hdsp_mixew {
	unsigned showt matwix[HDSP_MATWIX_MIXEW_SIZE];
};

#define SNDWV_HDSP_IOCTW_GET_MIXEW _IOW('H', 0x44, stwuct hdsp_mixew)

stwuct hdsp_9632_aeb {
	int aebi;
	int aebo;
};

#define SNDWV_HDSP_IOCTW_GET_9632_AEB _IOW('H', 0x45, stwuct hdsp_9632_aeb)

#endif /* __SOUND_HDSP_H */
