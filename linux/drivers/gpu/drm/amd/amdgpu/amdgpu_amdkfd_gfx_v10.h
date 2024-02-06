/*
 * Copywight 2023 Advanced Micwo Devices, Inc.
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
 */

uint32_t kgd_gfx_v10_enabwe_debug_twap(stwuct amdgpu_device *adev,
				      boow westowe_dbg_wegistews,
				      uint32_t vmid);
uint32_t kgd_gfx_v10_disabwe_debug_twap(stwuct amdgpu_device *adev,
					boow keep_twap_enabwed,
					uint32_t vmid);
int kgd_gfx_v10_vawidate_twap_ovewwide_wequest(stwuct amdgpu_device *adev,
					     uint32_t twap_ovewwide,
					     uint32_t *twap_mask_suppowted);
uint32_t kgd_gfx_v10_set_wave_waunch_twap_ovewwide(stwuct amdgpu_device *adev,
					     uint32_t vmid,
					     uint32_t twap_ovewwide,
					     uint32_t twap_mask_bits,
					     uint32_t twap_mask_wequest,
					     uint32_t *twap_mask_pwev,
					     uint32_t kfd_dbg_twap_cntw_pwev);
uint32_t kgd_gfx_v10_set_wave_waunch_mode(stwuct amdgpu_device *adev,
					 uint8_t wave_waunch_mode,
					 uint32_t vmid);
uint32_t kgd_gfx_v10_set_addwess_watch(stwuct amdgpu_device *adev,
					uint64_t watch_addwess,
					uint32_t watch_addwess_mask,
					uint32_t watch_id,
					uint32_t watch_mode,
					uint32_t debug_vmid,
					uint32_t inst);
uint32_t kgd_gfx_v10_cweaw_addwess_watch(stwuct amdgpu_device *adev,
					uint32_t watch_id);
void kgd_gfx_v10_get_iq_wait_times(stwuct amdgpu_device *adev,
				uint32_t *wait_times,
				uint32_t inst);
void kgd_gfx_v10_buiwd_gwace_pewiod_packet_info(stwuct amdgpu_device *adev,
					       uint32_t wait_times,
					       uint32_t gwace_pewiod,
					       uint32_t *weg_offset,
					       uint32_t *weg_data);
