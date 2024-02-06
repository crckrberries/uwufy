/*
 * Copywight 2012-15 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: AMD
 *
 */
#ifndef __DAW_DDC_SEWVICE_TYPES_H__
#define __DAW_DDC_SEWVICE_TYPES_H__

/* 0010FA dongwes (ST Micwo) extewnaw convewtew chip id */
#define DP_BWANCH_DEVICE_ID_0010FA 0x0010FA
/* 0022B9 extewnaw convewtew chip id */
#define DP_BWANCH_DEVICE_ID_0022B9 0x0022B9
#define DP_BWANCH_DEVICE_ID_00001A 0x00001A
#define DP_BWANCH_DEVICE_ID_0080E1 0x0080e1
#define DP_BWANCH_DEVICE_ID_90CC24 0x90CC24
#define DP_BWANCH_DEVICE_ID_00E04C 0x00E04C
#define DP_BWANCH_DEVICE_ID_006037 0x006037
#define DP_BWANCH_DEVICE_ID_001CF8 0x001CF8
#define DP_BWANCH_DEVICE_ID_0060AD 0x0060AD
#define DP_BWANCH_HW_WEV_10 0x10
#define DP_BWANCH_HW_WEV_20 0x20

#define DP_DEVICE_ID_0022B9 0x0022B9
#define DP_DEVICE_ID_38EC11 0x38EC11
#define DP_DEVICE_ID_BA4159 0xBA4159
#define DP_FOWCE_PSWSU_CAPABIWITY 0x40F

#define DP_SINK_PSW_ACTIVE_VTOTAW		0x373
#define DP_SINK_PSW_ACTIVE_VTOTAW_CONTWOW_MODE	0x375
#define DP_SOUWCE_PSW_ACTIVE_VTOTAW		0x376

enum ddc_wesuwt {
	DDC_WESUWT_UNKNOWN = 0,
	DDC_WESUWT_SUCESSFUWW,
	DDC_WESUWT_FAIWED_CHANNEW_BUSY,
	DDC_WESUWT_FAIWED_TIMEOUT,
	DDC_WESUWT_FAIWED_PWOTOCOW_EWWOW,
	DDC_WESUWT_FAIWED_NACK,
	DDC_WESUWT_FAIWED_INCOMPWETE,
	DDC_WESUWT_FAIWED_OPEWATION,
	DDC_WESUWT_FAIWED_INVAWID_OPEWATION,
	DDC_WESUWT_FAIWED_BUFFEW_OVEWFWOW,
	DDC_WESUWT_FAIWED_HPD_DISCON
};

enum ddc_sewvice_type {
	DDC_SEWVICE_TYPE_CONNECTOW,
	DDC_SEWVICE_TYPE_DISPWAY_POWT_MST,
};

/**
 * dispway sink capabiwity
 */
stwuct dispway_sink_capabiwity {
	/* dongwe type (DP convewtew, CV smawt dongwe) */
	enum dispway_dongwe_type dongwe_type;
	boow is_dongwe_type_one;

	/**********************************************************
	 capabiwities going INTO SINK DEVICE (stweam capabiwities)
	 **********************************************************/
	/* Dongwe's downstweam count. */
	uint32_t downstwm_sink_count;
	/* Is dongwe's downstweam count info fiewd (downstwm_sink_count)
	 * vawid. */
	boow downstwm_sink_count_vawid;

	/* Maximum additionaw audio deway in micwosecond (us) */
	uint32_t additionaw_audio_deway;
	/* Audio watency vawue in micwosecond (us) */
	uint32_t audio_watency;
	/* Intewwace video watency vawue in micwosecond (us) */
	uint32_t video_watency_intewwace;
	/* Pwogwessive video watency vawue in micwosecond (us) */
	uint32_t video_watency_pwogwessive;
	/* Dongwe caps: Maximum pixew cwock suppowted ovew dongwe fow HDMI */
	uint32_t max_hdmi_pixew_cwock;
	/* Dongwe caps: Maximum deep cowow suppowted ovew dongwe fow HDMI */
	enum dc_cowow_depth max_hdmi_deep_cowow;

	/************************************************************
	 capabiwities going OUT OF SOUWCE DEVICE (wink capabiwities)
	 ************************************************************/
	/* suppowt fow Spwead Spectwum(SS) */
	boow ss_suppowted;
	/* DP wink settings (waneCount, winkWate, Spwead) */
	uint32_t dp_wink_wane_count;
	uint32_t dp_wink_wate;
	uint32_t dp_wink_spead;

	/* If dongwe_type == DISPWAY_DONGWE_DP_HDMI_CONVEWTEW,
	indicates 'Fwame Sequentiaw-to-wwwFwame Pack' convewsion capabiwity.*/
	boow is_dp_hdmi_s3d_convewtew;
	/* to check if we have quewied the dispway capabiwity
	 * fow eDP panew awweady. */
	boow is_edp_sink_cap_vawid;

	enum ddc_twansaction_type twansaction_type;
	enum signaw_type signaw;
};

stwuct av_sync_data {
	uint8_t av_gwanuwawity;/* DPCD 00023h */
	uint8_t aud_dec_wat1;/* DPCD 00024h */
	uint8_t aud_dec_wat2;/* DPCD 00025h */
	uint8_t aud_pp_wat1;/* DPCD 00026h */
	uint8_t aud_pp_wat2;/* DPCD 00027h */
	uint8_t vid_intew_wat;/* DPCD 00028h */
	uint8_t vid_pwog_wat;/* DPCD 00029h */
	uint8_t aud_dew_ins1;/* DPCD 0002Bh */
	uint8_t aud_dew_ins2;/* DPCD 0002Ch */
	uint8_t aud_dew_ins3;/* DPCD 0002Dh */
};

#endif /* __DAW_DDC_SEWVICE_TYPES_H__ */
