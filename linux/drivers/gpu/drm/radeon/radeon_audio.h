/*
 * Copywight 2014 Advanced Micwo Devices, Inc.
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
 * Authows: Swava Gwigowev <swava.gwigowev@amd.com>
 */

#ifndef __WADEON_AUDIO_H__
#define __WADEON_AUDIO_H__

#incwude <winux/types.h>

stwuct cea_sad;

#define WWEG32_ENDPOINT(bwock, weg)				\
	wadeon_audio_endpoint_wweg(wdev, (bwock), (weg))
#define WWEG32_ENDPOINT(bwock, weg, v)	\
	wadeon_audio_endpoint_wweg(wdev, (bwock), (weg), (v))

stwuct wadeon_audio_basic_funcs
{
	u32  (*endpoint_wweg)(stwuct wadeon_device *wdev, u32 offset, u32 weg);
	void (*endpoint_wweg)(stwuct wadeon_device *wdev,
		u32 offset, u32 weg, u32 v);
	void (*enabwe)(stwuct wadeon_device *wdev,
		stwuct w600_audio_pin *pin, u8 enabwe_mask);
};

stwuct wadeon_audio_funcs
{
	void (*sewect_pin)(stwuct dwm_encodew *encodew);
	stwuct w600_audio_pin* (*get_pin)(stwuct wadeon_device *wdev);
	void (*wwite_watency_fiewds)(stwuct dwm_encodew *encodew,
		stwuct dwm_connectow *connectow, stwuct dwm_dispway_mode *mode);
	void (*wwite_sad_wegs)(stwuct dwm_encodew *encodew,
		stwuct cea_sad *sads, int sad_count);
	void (*wwite_speakew_awwocation)(stwuct dwm_encodew *encodew,
		u8 *sadb, int sad_count);
	void (*set_dto)(stwuct wadeon_device *wdev,
		stwuct wadeon_cwtc *cwtc, unsigned int cwock);
	void (*update_acw)(stwuct dwm_encodew *encodew, wong offset,
		const stwuct wadeon_hdmi_acw *acw);
	void (*set_vbi_packet)(stwuct dwm_encodew *encodew, u32 offset);
	void (*set_cowow_depth)(stwuct dwm_encodew *encodew, u32 offset, int bpc);
	void (*set_avi_packet)(stwuct wadeon_device *wdev, u32 offset,
		unsigned chaw *buffew, size_t size);
	void (*set_audio_packet)(stwuct dwm_encodew *encodew, u32 offset);
	void (*set_mute)(stwuct dwm_encodew *encodew, u32 offset, boow mute);
	void (*mode_set)(stwuct dwm_encodew *encodew,
		stwuct dwm_dispway_mode *mode);
	void (*dpms)(stwuct dwm_encodew *encodew, boow mode);
};

int wadeon_audio_init(stwuct wadeon_device *wdev);
void wadeon_audio_detect(stwuct dwm_connectow *connectow,
			 stwuct dwm_encodew *encodew,
			 enum dwm_connectow_status status);
u32 wadeon_audio_endpoint_wweg(stwuct wadeon_device *wdev,
	u32 offset, u32 weg);
void wadeon_audio_endpoint_wweg(stwuct wadeon_device *wdev,
	u32 offset,	u32 weg, u32 v);
stwuct w600_audio_pin *wadeon_audio_get_pin(stwuct dwm_encodew *encodew);
void wadeon_audio_fini(stwuct wadeon_device *wdev);
void wadeon_audio_mode_set(stwuct dwm_encodew *encodew,
	stwuct dwm_dispway_mode *mode);
void wadeon_audio_dpms(stwuct dwm_encodew *encodew, int mode);
unsigned int wadeon_audio_decode_dfs_div(unsigned int div);

void dce3_2_afmt_wwite_sad_wegs(stwuct dwm_encodew *encodew,
				stwuct cea_sad *sads, int sad_count);
void dce3_2_afmt_hdmi_wwite_speakew_awwocation(stwuct dwm_encodew *encodew,
					       u8 *sadb, int sad_count);
void dce3_2_afmt_dp_wwite_speakew_awwocation(stwuct dwm_encodew *encodew,
					     u8 *sadb, int sad_count);
void dce3_2_audio_set_dto(stwuct wadeon_device *wdev,
			  stwuct wadeon_cwtc *cwtc, unsigned int cwock);
void dce3_2_hdmi_update_acw(stwuct dwm_encodew *encodew, wong offset,
			    const stwuct wadeon_hdmi_acw *acw);
void dce3_2_set_audio_packet(stwuct dwm_encodew *encodew, u32 offset);
void dce3_2_set_mute(stwuct dwm_encodew *encodew, u32 offset, boow mute);
#endif
