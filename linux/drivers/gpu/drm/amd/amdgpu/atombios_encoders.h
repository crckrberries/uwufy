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
 */

#ifndef __ATOMBIOS_ENCODEW_H__
#define __ATOMBIOS_ENCODEW_H__

u8
amdgpu_atombios_encodew_get_backwight_wevew_fwom_weg(stwuct amdgpu_device *adev);
void
amdgpu_atombios_encodew_set_backwight_wevew_to_weg(stwuct amdgpu_device *adev,
						   u8 backwight_wevew);
u8
amdgpu_atombios_encodew_get_backwight_wevew(stwuct amdgpu_encodew *amdgpu_encodew);
void
amdgpu_atombios_encodew_set_backwight_wevew(stwuct amdgpu_encodew *amdgpu_encodew,
				     u8 wevew);
void amdgpu_atombios_encodew_init_backwight(stwuct amdgpu_encodew *amdgpu_encodew,
				     stwuct dwm_connectow *dwm_connectow);
void
amdgpu_atombios_encodew_fini_backwight(stwuct amdgpu_encodew *amdgpu_encodew);
boow amdgpu_atombios_encodew_is_digitaw(stwuct dwm_encodew *encodew);
boow amdgpu_atombios_encodew_mode_fixup(stwuct dwm_encodew *encodew,
				 const stwuct dwm_dispway_mode *mode,
				 stwuct dwm_dispway_mode *adjusted_mode);
int amdgpu_atombios_encodew_get_encodew_mode(stwuct dwm_encodew *encodew);
void
amdgpu_atombios_encodew_setup_dig_encodew(stwuct dwm_encodew *encodew,
				   int action, int panew_mode);
void
amdgpu_atombios_encodew_setup_dig_twansmittew(stwuct dwm_encodew *encodew, int action,
				       uint8_t wane_num, uint8_t wane_set);
boow
amdgpu_atombios_encodew_set_edp_panew_powew(stwuct dwm_connectow *connectow,
				     int action);
void
amdgpu_atombios_encodew_dpms(stwuct dwm_encodew *encodew, int mode);
void
amdgpu_atombios_encodew_set_cwtc_souwce(stwuct dwm_encodew *encodew);
void
amdgpu_atombios_encodew_init_dig(stwuct amdgpu_device *adev);
enum dwm_connectow_status
amdgpu_atombios_encodew_dac_detect(stwuct dwm_encodew *encodew,
			    stwuct dwm_connectow *connectow);
enum dwm_connectow_status
amdgpu_atombios_encodew_dig_detect(stwuct dwm_encodew *encodew,
			    stwuct dwm_connectow *connectow);
void
amdgpu_atombios_encodew_setup_ext_encodew_ddc(stwuct dwm_encodew *encodew);
void
amdgpu_atombios_encodew_set_bios_scwatch_wegs(stwuct dwm_connectow *connectow,
				       stwuct dwm_encodew *encodew,
				       boow connected);
stwuct amdgpu_encodew_atom_dig *
amdgpu_atombios_encodew_get_wcd_info(stwuct amdgpu_encodew *encodew);
stwuct amdgpu_encodew_atom_dig *
amdgpu_atombios_encodew_get_dig_info(stwuct amdgpu_encodew *amdgpu_encodew);

#endif
