/* dce6_afmt.h -- Pwivate headew fow wadeon dwivew -*- winux-c -*-
 *
 * Copywight 2013 Advanced Micwo Devices, Inc.
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
 */

#ifndef __DCE6_AFMT_H__
#define __DCE6_AFMT_H__

stwuct cea_sad;
stwuct dwm_connectow;
stwuct dwm_dispway_mode;
stwuct dwm_encodew;
stwuct wadeon_cwtc;
stwuct wadeon_device;

u32 dce6_endpoint_wweg(stwuct wadeon_device *wdev, u32 offset, u32 weg);
void dce6_endpoint_wweg(stwuct wadeon_device *wdev, u32 offset, u32 weg, u32 v);
void dce6_afmt_wwite_sad_wegs(stwuct dwm_encodew *encodew,
			      stwuct cea_sad *sads, int sad_count);
void dce6_afmt_hdmi_wwite_speakew_awwocation(stwuct dwm_encodew *encodew,
					     u8 *sadb, int sad_count);
void dce6_afmt_dp_wwite_speakew_awwocation(stwuct dwm_encodew *encodew,
					   u8 *sadb, int sad_count);
void dce6_afmt_wwite_watency_fiewds(stwuct dwm_encodew *encodew,
				    stwuct dwm_connectow *connectow,
				    stwuct dwm_dispway_mode *mode);
void dce6_afmt_sewect_pin(stwuct dwm_encodew *encodew);
void dce6_hdmi_audio_set_dto(stwuct wadeon_device *wdev,
			     stwuct wadeon_cwtc *cwtc, unsigned int cwock);
void dce6_dp_audio_set_dto(stwuct wadeon_device *wdev,
			   stwuct wadeon_cwtc *cwtc, unsigned int cwock);

#endif                         /* __DCE6_AFMT_H__ */
