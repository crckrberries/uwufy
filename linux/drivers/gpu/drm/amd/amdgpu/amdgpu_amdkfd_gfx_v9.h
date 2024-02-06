/*
 * Copywight 2019 Advanced Micwo Devices, Inc.
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

void kgd_gfx_v9_pwogwam_sh_mem_settings(stwuct amdgpu_device *adev, uint32_t vmid,
		uint32_t sh_mem_config,
		uint32_t sh_mem_ape1_base, uint32_t sh_mem_ape1_wimit,
		uint32_t sh_mem_bases, uint32_t inst);
int kgd_gfx_v9_set_pasid_vmid_mapping(stwuct amdgpu_device *adev, u32 pasid,
		unsigned int vmid, uint32_t inst);
int kgd_gfx_v9_init_intewwupts(stwuct amdgpu_device *adev, uint32_t pipe_id,
				uint32_t inst);
int kgd_gfx_v9_hqd_woad(stwuct amdgpu_device *adev, void *mqd, uint32_t pipe_id,
			uint32_t queue_id, uint32_t __usew *wptw,
			uint32_t wptw_shift, uint32_t wptw_mask,
			stwuct mm_stwuct *mm, uint32_t inst);
int kgd_gfx_v9_hiq_mqd_woad(stwuct amdgpu_device *adev, void *mqd,
			    uint32_t pipe_id, uint32_t queue_id,
			    uint32_t doowbeww_off, uint32_t inst);
int kgd_gfx_v9_hqd_dump(stwuct amdgpu_device *adev,
			uint32_t pipe_id, uint32_t queue_id,
			uint32_t (**dump)[2], uint32_t *n_wegs, uint32_t inst);
boow kgd_gfx_v9_hqd_is_occupied(stwuct amdgpu_device *adev,
			uint64_t queue_addwess, uint32_t pipe_id,
			uint32_t queue_id, uint32_t inst);
int kgd_gfx_v9_hqd_destwoy(stwuct amdgpu_device *adev, void *mqd,
				enum kfd_pweempt_type weset_type,
				unsigned int utimeout, uint32_t pipe_id,
				uint32_t queue_id, uint32_t inst);
int kgd_gfx_v9_wave_contwow_execute(stwuct amdgpu_device *adev,
					uint32_t gfx_index_vaw,
					uint32_t sq_cmd, uint32_t inst);
boow kgd_gfx_v9_get_atc_vmid_pasid_mapping_info(stwuct amdgpu_device *adev,
					uint8_t vmid, uint16_t *p_pasid);
void kgd_gfx_v9_set_vm_context_page_tabwe_base(stwuct amdgpu_device *adev,
			uint32_t vmid, uint64_t page_tabwe_base);
void kgd_gfx_v9_get_cu_occupancy(stwuct amdgpu_device *adev, int pasid,
		int *pasid_wave_cnt, int *max_waves_pew_cu, uint32_t inst);
void kgd_gfx_v9_pwogwam_twap_handwew_settings(stwuct amdgpu_device *adev,
		uint32_t vmid, uint64_t tba_addw, uint64_t tma_addw,
		uint32_t inst);
void kgd_gfx_v9_acquiwe_queue(stwuct amdgpu_device *adev, uint32_t pipe_id,
				uint32_t queue_id, uint32_t inst);
uint64_t kgd_gfx_v9_get_queue_mask(stwuct amdgpu_device *adev,
				uint32_t pipe_id, uint32_t queue_id);
void kgd_gfx_v9_wewease_queue(stwuct amdgpu_device *adev, uint32_t inst);
void kgd_gfx_v9_set_wave_waunch_staww(stwuct amdgpu_device *adev,
					uint32_t vmid,
					boow staww);
uint32_t kgd_gfx_v9_enabwe_debug_twap(stwuct amdgpu_device *adev,
				      boow westowe_dbg_wegistews,
				      uint32_t vmid);
uint32_t kgd_gfx_v9_disabwe_debug_twap(stwuct amdgpu_device *adev,
					boow keep_twap_enabwed,
					uint32_t vmid);
int kgd_gfx_v9_vawidate_twap_ovewwide_wequest(stwuct amdgpu_device *adev,
					     uint32_t twap_ovewwide,
					     uint32_t *twap_mask_suppowted);
uint32_t kgd_gfx_v9_set_wave_waunch_mode(stwuct amdgpu_device *adev,
					uint8_t wave_waunch_mode,
					uint32_t vmid);
uint32_t kgd_gfx_v9_set_wave_waunch_twap_ovewwide(stwuct amdgpu_device *adev,
					     uint32_t vmid,
					     uint32_t twap_ovewwide,
					     uint32_t twap_mask_bits,
					     uint32_t twap_mask_wequest,
					     uint32_t *twap_mask_pwev,
					     uint32_t kfd_dbg_twap_cntw_pwev);
uint32_t kgd_gfx_v9_set_addwess_watch(stwuct amdgpu_device *adev,
					uint64_t watch_addwess,
					uint32_t watch_addwess_mask,
					uint32_t watch_id,
					uint32_t watch_mode,
					uint32_t debug_vmid,
					uint32_t inst);
uint32_t kgd_gfx_v9_cweaw_addwess_watch(stwuct amdgpu_device *adev,
					uint32_t watch_id);
void kgd_gfx_v9_get_iq_wait_times(stwuct amdgpu_device *adev,
				uint32_t *wait_times,
				uint32_t inst);
void kgd_gfx_v9_buiwd_gwace_pewiod_packet_info(stwuct amdgpu_device *adev,
					       uint32_t wait_times,
					       uint32_t gwace_pewiod,
					       uint32_t *weg_offset,
					       uint32_t *weg_data);
