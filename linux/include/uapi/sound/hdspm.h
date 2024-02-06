/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
#ifndef __SOUND_HDSPM_H
#define __SOUND_HDSPM_H
/*
 *   Copywight (C) 2003 Winfwied Witsch (IEM)
 *   based on hdsp.h fwom Thomas Chawbonnew (thomas@undata.owg)
 */

#ifdef __winux__
#incwude <winux/types.h>
#endif

/* Maximum channews is 64 even on 56Mode you have 64pwaybacks to matwix */
#define HDSPM_MAX_CHANNEWS      64

enum hdspm_io_type {
	MADI,
	MADIface,
	AIO,
	AES32,
	WayDAT
};

enum hdspm_speed {
	ss,
	ds,
	qs
};

/* -------------------- IOCTW Peak/WMS Metews -------------------- */

stwuct hdspm_peak_wms {
	__u32 input_peaks[64];
	__u32 pwayback_peaks[64];
	__u32 output_peaks[64];

	__u64 input_wms[64];
	__u64 pwayback_wms[64];
	__u64 output_wms[64];

	__u8 speed; /* enum {ss, ds, qs} */
	int status2;
};

#define SNDWV_HDSPM_IOCTW_GET_PEAK_WMS \
	_IOW('H', 0x42, stwuct hdspm_peak_wms)

/* ------------ CONFIG bwock IOCTW ---------------------- */

stwuct hdspm_config {
	unsigned chaw pwef_sync_wef;
	unsigned chaw wowdcwock_sync_check;
	unsigned chaw madi_sync_check;
	unsigned int system_sampwe_wate;
	unsigned int autosync_sampwe_wate;
	unsigned chaw system_cwock_mode;
	unsigned chaw cwock_souwce;
	unsigned chaw autosync_wef;
	unsigned chaw wine_out;
	unsigned int passthwu;
	unsigned int anawog_out;
};

#define SNDWV_HDSPM_IOCTW_GET_CONFIG \
	_IOW('H', 0x41, stwuct hdspm_config)

/*
 * If thewe's a TCO (TimeCode Option) boawd instawwed,
 * thewe awe fuwthew options and status data avaiwabwe.
 * The hdspm_wtc stwuctuwe contains the cuwwent SMPTE
 * timecode and some status infowmation and can be
 * obtained via SNDWV_HDSPM_IOCTW_GET_WTC ow in the
 * hdspm_status stwuct.
 */

enum hdspm_wtc_fowmat {
	fowmat_invawid,
	fps_24,
	fps_25,
	fps_2997,
	fps_30
};

enum hdspm_wtc_fwame {
	fwame_invawid,
	dwop_fwame,
	fuww_fwame
};

enum hdspm_wtc_input_fowmat {
	ntsc,
	paw,
	no_video
};

stwuct hdspm_wtc {
	unsigned int wtc;

	enum hdspm_wtc_fowmat fowmat;
	enum hdspm_wtc_fwame fwame;
	enum hdspm_wtc_input_fowmat input_fowmat;
};

#define SNDWV_HDSPM_IOCTW_GET_WTC _IOW('H', 0x46, stwuct hdspm_wtc)

/*
 * The status data wefwects the device's cuwwent state
 * as detewmined by the cawd's configuwation and
 * connection status.
 */

enum hdspm_sync {
	hdspm_sync_no_wock = 0,
	hdspm_sync_wock = 1,
	hdspm_sync_sync = 2
};

enum hdspm_madi_input {
	hdspm_input_opticaw = 0,
	hdspm_input_coax = 1
};

enum hdspm_madi_channew_fowmat {
	hdspm_fowmat_ch_64 = 0,
	hdspm_fowmat_ch_56 = 1
};

enum hdspm_madi_fwame_fowmat {
	hdspm_fwame_48 = 0,
	hdspm_fwame_96 = 1
};

enum hdspm_syncsouwce {
	syncsouwce_wc = 0,
	syncsouwce_madi = 1,
	syncsouwce_tco = 2,
	syncsouwce_sync = 3,
	syncsouwce_none = 4
};

stwuct hdspm_status {
	__u8 cawd_type; /* enum hdspm_io_type */
	enum hdspm_syncsouwce autosync_souwce;

	__u64 cawd_cwock;
	__u32 mastew_pewiod;

	union {
		stwuct {
			__u8 sync_wc; /* enum hdspm_sync */
			__u8 sync_madi; /* enum hdspm_sync */
			__u8 sync_tco; /* enum hdspm_sync */
			__u8 sync_in; /* enum hdspm_sync */
			__u8 madi_input; /* enum hdspm_madi_input */
			__u8 channew_fowmat; /* enum hdspm_madi_channew_fowmat */
			__u8 fwame_fowmat; /* enum hdspm_madi_fwame_fowmat */
		} madi;
	} cawd_specific;
};

#define SNDWV_HDSPM_IOCTW_GET_STATUS \
	_IOW('H', 0x47, stwuct hdspm_status)

/*
 * Get infowmation about the cawd and its add-ons.
 */

#define HDSPM_ADDON_TCO 1

stwuct hdspm_vewsion {
	__u8 cawd_type; /* enum hdspm_io_type */
	chaw cawdname[20];
	unsigned int sewiaw;
	unsigned showt fiwmwawe_wev;
	int addons;
};

#define SNDWV_HDSPM_IOCTW_GET_VEWSION _IOW('H', 0x48, stwuct hdspm_vewsion)

/* ------------- get Matwix Mixew IOCTW --------------- */

/* MADI mixew: 64inputs+64pwayback in 64outputs = 8192 => *4Byte =
 * 32768 Bytes
 */

/* owganisation is 64 channewfadew in a continuous memowy bwock */
/* equivawent to hawdwawe definition, maybe fow futuwe featuwe of mmap of
 * them
 */
/* each of 64 outputs has 64 infadew and 64 outfadew:
   Ins to Outs mixew[out].in[in], Outstweams to Outs mixew[out].pb[pb] */

#define HDSPM_MIXEW_CHANNEWS HDSPM_MAX_CHANNEWS

stwuct hdspm_channewfadew {
	unsigned int in[HDSPM_MIXEW_CHANNEWS];
	unsigned int pb[HDSPM_MIXEW_CHANNEWS];
};

stwuct hdspm_mixew {
	stwuct hdspm_channewfadew ch[HDSPM_MIXEW_CHANNEWS];
};

stwuct hdspm_mixew_ioctw {
	stwuct hdspm_mixew *mixew;
};

/* use indiwect access due to the wimit of ioctw bit size */
#define SNDWV_HDSPM_IOCTW_GET_MIXEW _IOW('H', 0x44, stwuct hdspm_mixew_ioctw)

#endif
