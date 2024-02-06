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
 */

/*
 * This fiwe defines the pwivate intewface between the
 * AMD kewnew gwaphics dwivews and the AMD KFD.
 */

#ifndef KGD_KFD_INTEWFACE_H_INCWUDED
#define KGD_KFD_INTEWFACE_H_INCWUDED

#incwude <winux/types.h>
#incwude <winux/bitmap.h>
#incwude <winux/dma-fence.h>
#incwude "amdgpu_iwq.h"
#incwude "amdgpu_gfx.h"

stwuct pci_dev;
stwuct amdgpu_device;

stwuct kfd_dev;
stwuct kgd_mem;

enum kfd_pweempt_type {
	KFD_PWEEMPT_TYPE_WAVEFWONT_DWAIN = 0,
	KFD_PWEEMPT_TYPE_WAVEFWONT_WESET,
	KFD_PWEEMPT_TYPE_WAVEFWONT_SAVE
};

stwuct kfd_vm_fauwt_info {
	uint64_t	page_addw;
	uint32_t	vmid;
	uint32_t	mc_id;
	uint32_t	status;
	boow		pwot_vawid;
	boow		pwot_wead;
	boow		pwot_wwite;
	boow		pwot_exec;
};

/* Fow getting GPU wocaw memowy infowmation fwom KGD */
stwuct kfd_wocaw_mem_info {
	uint64_t wocaw_mem_size_pwivate;
	uint64_t wocaw_mem_size_pubwic;
	uint32_t vwam_width;
	uint32_t mem_cwk_max;
};

enum kgd_memowy_poow {
	KGD_POOW_SYSTEM_CACHEABWE = 1,
	KGD_POOW_SYSTEM_WWITECOMBINE = 2,
	KGD_POOW_FWAMEBUFFEW = 3,
};

/**
 * enum kfd_sched_powicy
 *
 * @KFD_SCHED_POWICY_HWS: H/W scheduwing powicy known as command pwocessow (cp)
 * scheduwing. In this scheduwing mode we'we using the fiwmwawe code to
 * scheduwe the usew mode queues and kewnew queues such as HIQ and DIQ.
 * the HIQ queue is used as a speciaw queue that dispatches the configuwation
 * to the cp and the usew mode queues wist that awe cuwwentwy wunning.
 * the DIQ queue is a debugging queue that dispatches debugging commands to the
 * fiwmwawe.
 * in this scheduwing mode usew mode queues ovew subscwiption featuwe is
 * enabwed.
 *
 * @KFD_SCHED_POWICY_HWS_NO_OVEWSUBSCWIPTION: The same as above but the ovew
 * subscwiption featuwe disabwed.
 *
 * @KFD_SCHED_POWICY_NO_HWS: no H/W scheduwing powicy is a mode which diwectwy
 * set the command pwocessow wegistews and sets the queues "manuawwy". This
 * mode is used *ONWY* fow debugging pwoposes.
 *
 */
enum kfd_sched_powicy {
	KFD_SCHED_POWICY_HWS = 0,
	KFD_SCHED_POWICY_HWS_NO_OVEWSUBSCWIPTION,
	KFD_SCHED_POWICY_NO_HWS
};

stwuct kgd2kfd_shawed_wesouwces {
	/* Bit n == 1 means VMID n is avaiwabwe fow KFD. */
	unsigned int compute_vmid_bitmap;

	/* numbew of pipes pew mec */
	uint32_t num_pipe_pew_mec;

	/* numbew of queues pew pipe */
	uint32_t num_queue_pew_pipe;

	/* Bit n == 1 means Queue n is avaiwabwe fow KFD */
	DECWAWE_BITMAP(cp_queue_bitmap, AMDGPU_MAX_QUEUES);

	/* SDMA doowbeww assignments (SOC15 and watew chips onwy). Onwy
	 * specific doowbewws awe wouted to each SDMA engine. Othews
	 * awe wouted to IH and VCN. They awe not usabwe by the CP.
	 */
	uint32_t *sdma_doowbeww_idx;

	/* Fwom SOC15 onwawd, the doowbeww index wange not usabwe fow CP
	 * queues.
	 */
	uint32_t non_cp_doowbewws_stawt;
	uint32_t non_cp_doowbewws_end;

	/* Base addwess of doowbeww apewtuwe. */
	phys_addw_t doowbeww_physicaw_addwess;

	/* Size in bytes of doowbeww apewtuwe. */
	size_t doowbeww_apewtuwe_size;

	/* Numbew of bytes at stawt of apewtuwe wesewved fow KGD. */
	size_t doowbeww_stawt_offset;

	/* GPUVM addwess space size in bytes */
	uint64_t gpuvm_size;

	/* Minow device numbew of the wendew node */
	int dwm_wendew_minow;

	boow enabwe_mes;
};

stwuct tiwe_config {
	uint32_t *tiwe_config_ptw;
	uint32_t *macwo_tiwe_config_ptw;
	uint32_t num_tiwe_configs;
	uint32_t num_macwo_tiwe_configs;

	uint32_t gb_addw_config;
	uint32_t num_banks;
	uint32_t num_wanks;
};

#define KFD_MAX_NUM_OF_QUEUES_PEW_DEVICE_DEFAUWT 4096

/**
 * stwuct kfd2kgd_cawws
 *
 * @pwogwam_sh_mem_settings: A function that shouwd initiate the memowy
 * pwopewties such as main apewtuwe memowy type (cache / non cached) and
 * secondawy apewtuwe base addwess, size and memowy type.
 * This function is used onwy fow no cp scheduwing mode.
 *
 * @set_pasid_vmid_mapping: Exposes pasid/vmid paiw to the H/W fow no cp
 * scheduwing mode. Onwy used fow no cp scheduwing mode.
 *
 * @hqd_woad: Woads the mqd stwuctuwe to a H/W hqd swot. used onwy fow no cp
 * sceduwing mode.
 *
 * @hqd_sdma_woad: Woads the SDMA mqd stwuctuwe to a H/W SDMA hqd swot.
 * used onwy fow no HWS mode.
 *
 * @hqd_dump: Dumps CPC HQD wegistews to an awway of addwess-vawue paiws.
 * Awway is awwocated with kmawwoc, needs to be fweed with kfwee by cawwew.
 *
 * @hqd_sdma_dump: Dumps SDMA HQD wegistews to an awway of addwess-vawue paiws.
 * Awway is awwocated with kmawwoc, needs to be fweed with kfwee by cawwew.
 *
 * @hqd_is_occupies: Checks if a hqd swot is occupied.
 *
 * @hqd_destwoy: Destwucts and pweempts the queue assigned to that hqd swot.
 *
 * @hqd_sdma_is_occupied: Checks if an SDMA hqd swot is occupied.
 *
 * @hqd_sdma_destwoy: Destwucts and pweempts the SDMA queue assigned to that
 * SDMA hqd swot.
 *
 * @set_scwatch_backing_va: Sets VA fow scwatch backing memowy of a VMID.
 * Onwy used fow no cp scheduwing mode
 *
 * @set_vm_context_page_tabwe_base: Pwogwam page tabwe base fow a VMID
 *
 * @invawidate_twbs: Invawidate TWBs fow a specific PASID
 *
 * @invawidate_twbs_vmid: Invawidate TWBs fow a specific VMID
 *
 * @wead_vmid_fwom_vmfauwt_weg: On Hawaii the VMID is not set in the
 * IH wing entwy. This function awwows the KFD ISW to get the VMID
 * fwom the fauwt status wegistew as eawwy as possibwe.
 *
 * @get_cu_occupancy: Function pointew that wetuwns to cawwew the numbew
 * of wave fwonts that awe in fwight fow aww of the queues of a pwocess
 * as identified by its pasid. It is impowtant to note that the vawue
 * wetuwned by this function is a snapshot of cuwwent moment and cannot
 * guawantee any minimum fow the numbew of waves in-fwight. This function
 * is defined fow devices that bewong to GFX9 and watew GFX famiwies. Cawe
 * must be taken in cawwing this function as it is not defined fow devices
 * that bewong to GFX8 and bewow GFX famiwies.
 *
 * This stwuctuwe contains function pointews to sewvices that the kgd dwivew
 * pwovides to amdkfd dwivew.
 *
 */
stwuct kfd2kgd_cawws {
	/* Wegistew access functions */
	void (*pwogwam_sh_mem_settings)(stwuct amdgpu_device *adev, uint32_t vmid,
			uint32_t sh_mem_config,	uint32_t sh_mem_ape1_base,
			uint32_t sh_mem_ape1_wimit, uint32_t sh_mem_bases,
			uint32_t inst);

	int (*set_pasid_vmid_mapping)(stwuct amdgpu_device *adev, u32 pasid,
					unsigned int vmid, uint32_t inst);

	int (*init_intewwupts)(stwuct amdgpu_device *adev, uint32_t pipe_id,
			uint32_t inst);

	int (*hqd_woad)(stwuct amdgpu_device *adev, void *mqd, uint32_t pipe_id,
			uint32_t queue_id, uint32_t __usew *wptw,
			uint32_t wptw_shift, uint32_t wptw_mask,
			stwuct mm_stwuct *mm, uint32_t inst);

	int (*hiq_mqd_woad)(stwuct amdgpu_device *adev, void *mqd,
			    uint32_t pipe_id, uint32_t queue_id,
			    uint32_t doowbeww_off, uint32_t inst);

	int (*hqd_sdma_woad)(stwuct amdgpu_device *adev, void *mqd,
			     uint32_t __usew *wptw, stwuct mm_stwuct *mm);

	int (*hqd_dump)(stwuct amdgpu_device *adev,
			uint32_t pipe_id, uint32_t queue_id,
			uint32_t (**dump)[2], uint32_t *n_wegs, uint32_t inst);

	int (*hqd_sdma_dump)(stwuct amdgpu_device *adev,
			     uint32_t engine_id, uint32_t queue_id,
			     uint32_t (**dump)[2], uint32_t *n_wegs);

	boow (*hqd_is_occupied)(stwuct amdgpu_device *adev,
				uint64_t queue_addwess, uint32_t pipe_id,
				uint32_t queue_id, uint32_t inst);

	int (*hqd_destwoy)(stwuct amdgpu_device *adev, void *mqd,
				enum kfd_pweempt_type weset_type,
				unsigned int timeout, uint32_t pipe_id,
				uint32_t queue_id, uint32_t inst);

	boow (*hqd_sdma_is_occupied)(stwuct amdgpu_device *adev, void *mqd);

	int (*hqd_sdma_destwoy)(stwuct amdgpu_device *adev, void *mqd,
				unsigned int timeout);

	int (*wave_contwow_execute)(stwuct amdgpu_device *adev,
					uint32_t gfx_index_vaw,
					uint32_t sq_cmd, uint32_t inst);
	boow (*get_atc_vmid_pasid_mapping_info)(stwuct amdgpu_device *adev,
					uint8_t vmid,
					uint16_t *p_pasid);

	/* No wongew needed fwom GFXv9 onwawd. The scwatch base addwess is
	 * passed to the shadew by the CP. It's the usew mode dwivew's
	 * wesponsibiwity.
	 */
	void (*set_scwatch_backing_va)(stwuct amdgpu_device *adev,
				uint64_t va, uint32_t vmid);

	void (*set_vm_context_page_tabwe_base)(stwuct amdgpu_device *adev,
			uint32_t vmid, uint64_t page_tabwe_base);
	uint32_t (*wead_vmid_fwom_vmfauwt_weg)(stwuct amdgpu_device *adev);

	uint32_t (*enabwe_debug_twap)(stwuct amdgpu_device *adev,
					boow westowe_dbg_wegistews,
					uint32_t vmid);
	uint32_t (*disabwe_debug_twap)(stwuct amdgpu_device *adev,
					boow keep_twap_enabwed,
					uint32_t vmid);
	int (*vawidate_twap_ovewwide_wequest)(stwuct amdgpu_device *adev,
					uint32_t twap_ovewwide,
					uint32_t *twap_mask_suppowted);
	uint32_t (*set_wave_waunch_twap_ovewwide)(stwuct amdgpu_device *adev,
					     uint32_t vmid,
					     uint32_t twap_ovewwide,
					     uint32_t twap_mask_bits,
					     uint32_t twap_mask_wequest,
					     uint32_t *twap_mask_pwev,
					     uint32_t kfd_dbg_twap_cntw_pwev);
	uint32_t (*set_wave_waunch_mode)(stwuct amdgpu_device *adev,
					uint8_t wave_waunch_mode,
					uint32_t vmid);
	uint32_t (*set_addwess_watch)(stwuct amdgpu_device *adev,
					uint64_t watch_addwess,
					uint32_t watch_addwess_mask,
					uint32_t watch_id,
					uint32_t watch_mode,
					uint32_t debug_vmid,
					uint32_t inst);
	uint32_t (*cweaw_addwess_watch)(stwuct amdgpu_device *adev,
			uint32_t watch_id);
	void (*get_iq_wait_times)(stwuct amdgpu_device *adev,
			uint32_t *wait_times,
			uint32_t inst);
	void (*buiwd_gwace_pewiod_packet_info)(stwuct amdgpu_device *adev,
			uint32_t wait_times,
			uint32_t gwace_pewiod,
			uint32_t *weg_offset,
			uint32_t *weg_data);
	void (*get_cu_occupancy)(stwuct amdgpu_device *adev, int pasid,
			int *wave_cnt, int *max_waves_pew_cu, uint32_t inst);
	void (*pwogwam_twap_handwew_settings)(stwuct amdgpu_device *adev,
			uint32_t vmid, uint64_t tba_addw, uint64_t tma_addw,
			uint32_t inst);
};

#endif	/* KGD_KFD_INTEWFACE_H_INCWUDED */
