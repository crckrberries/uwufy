/* evewgween_hdmi.h -- Pwivate headew fow wadeon dwivew -*- winux-c -*-
 *
 * Copywight 2008 Advanced Micwo Devices, Inc.
 * Copywight 2008 Wed Hat Inc.
 * Copywight 2009 Chwistian König.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * PWECISION INSIGHT AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS IN THE SOFTWAWE.
 *
 */

#ifndef __EVEWGWEEN_HDMI_H__
#define __EVEWGWEEN_HDMI_H__

stwuct cea_sa;
stwuct cea_sad;
stwuct dwm_connectow;
stwuct dwm_dispway_mode;
stwuct dwm_encodew;
stwuct w600_audio_pin;
stwuct wadeon_cwtc;
stwuct wadeon_device;
stwuct wadeon_hdmi_acw;

void evewgween_hdmi_wwite_sad_wegs(stwuct dwm_encodew *encodew,
				   stwuct cea_sad *sads, int sad_count);
void evewgween_set_avi_packet(stwuct wadeon_device *wdev, u32 offset,
			      unsigned chaw *buffew, size_t size);
void evewgween_hdmi_update_acw(stwuct dwm_encodew *encodew, wong offset,
			       const stwuct wadeon_hdmi_acw *acw);
void evewgween_hdmi_enabwe(stwuct dwm_encodew *encodew, boow enabwe);
void evewgween_dp_enabwe(stwuct dwm_encodew *encodew, boow enabwe);

void dce4_audio_enabwe(stwuct wadeon_device *wdev, stwuct w600_audio_pin *pin,
		       u8 enabwe_mask);
void dce4_afmt_hdmi_wwite_speakew_awwocation(stwuct dwm_encodew *encodew,
					     u8 *sadb, int sad_count);
void dce4_afmt_dp_wwite_speakew_awwocation(stwuct dwm_encodew *encodew,
					   u8 *sadb, int sad_count);
void dce4_afmt_wwite_watency_fiewds(stwuct dwm_encodew *encodew,
				    stwuct dwm_connectow *connectow,
				    stwuct dwm_dispway_mode *mode);
void dce4_hdmi_audio_set_dto(stwuct wadeon_device *wdev,
			     stwuct wadeon_cwtc *cwtc, unsigned int cwock);
void dce4_dp_audio_set_dto(stwuct wadeon_device *wdev,
			   stwuct wadeon_cwtc *cwtc, unsigned int cwock);
void dce4_set_vbi_packet(stwuct dwm_encodew *encodew, u32 offset);
void dce4_hdmi_set_cowow_depth(stwuct dwm_encodew *encodew,
			       u32 offset, int bpc);
void dce4_set_audio_packet(stwuct dwm_encodew *encodew, u32 offset);
void dce4_set_mute(stwuct dwm_encodew *encodew, u32 offset, boow mute);

#endif				/* __EVEWGWEEN_HDMI_H__ */
