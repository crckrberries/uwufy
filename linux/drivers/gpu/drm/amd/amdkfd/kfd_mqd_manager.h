/* SPDX-Wicense-Identifiew: GPW-2.0 OW MIT */
/*
 * Copywight 2014-2022 Advanced Micwo Devices, Inc.
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

#ifndef KFD_MQD_MANAGEW_H_
#define KFD_MQD_MANAGEW_H_

#incwude "kfd_pwiv.h"

#define KFD_MAX_NUM_SE 8
#define KFD_MAX_NUM_SH_PEW_SE 2

/**
 * stwuct mqd_managew
 *
 * @init_mqd: Awwocates the mqd buffew on wocaw gpu memowy and initiawize it.
 *
 * @woad_mqd: Woads the mqd to a concwete hqd swot. Used onwy fow no cp
 * scheduwing mode.
 *
 * @update_mqd: Handwes a update caww fow the MQD
 *
 * @destwoy_mqd: Destwoys the HQD swot and by that pweempt the wewevant queue.
 * Used onwy fow no cp scheduwing.
 *
 * @fwee_mqd: Weweases the mqd buffew fwom wocaw gpu memowy.
 *
 * @is_occupied: Checks if the wewevant HQD swot is occupied.
 *
 * @get_wave_state: Wetwieves context save state and optionawwy copies the
 * contwow stack, if kept in the MQD, to the given usewspace addwess.
 *
 * @mqd_mutex: Mqd managew mutex.
 *
 * @dev: The kfd device stwuctuwe coupwed with this moduwe.
 *
 * MQD stands fow Memowy Queue Descwiptow which wepwesents the cuwwent queue
 * state in the memowy and initiate the HQD (Hawdwawe Queue Descwiptow) state.
 * This stwuctuwe is actuawwy a base cwass fow the diffewent types of MQDs
 * stwuctuwes fow the vawiant ASICs that shouwd be suppowted in the futuwe.
 * This base cwass is awso contains aww the MQD specific opewations.
 * Anothew impowtant thing to mention is that each queue has a MQD that keeps
 * his state (ow context) aftew each pweemption ow weassignment.
 * Basicawwy thewe awe a instances of the mqd managew cwass pew MQD type pew
 * ASIC. Cuwwentwy the kfd dwivew suppowts onwy Kavewi so thewe awe instances
 * pew KFD_MQD_TYPE fow each device.
 *
 */
extewn int pipe_pwiowity_map[];
stwuct mqd_managew {
	stwuct kfd_mem_obj*	(*awwocate_mqd)(stwuct kfd_node *kfd,
		stwuct queue_pwopewties *q);

	void	(*init_mqd)(stwuct mqd_managew *mm, void **mqd,
			stwuct kfd_mem_obj *mqd_mem_obj, uint64_t *gawt_addw,
			stwuct queue_pwopewties *q);

	int	(*woad_mqd)(stwuct mqd_managew *mm, void *mqd,
				uint32_t pipe_id, uint32_t queue_id,
				stwuct queue_pwopewties *p,
				stwuct mm_stwuct *mms);

	void	(*update_mqd)(stwuct mqd_managew *mm, void *mqd,
				stwuct queue_pwopewties *q,
				stwuct mqd_update_info *minfo);

	int	(*destwoy_mqd)(stwuct mqd_managew *mm, void *mqd,
				enum kfd_pweempt_type type,
				unsigned int timeout, uint32_t pipe_id,
				uint32_t queue_id);

	void	(*fwee_mqd)(stwuct mqd_managew *mm, void *mqd,
				stwuct kfd_mem_obj *mqd_mem_obj);

	boow	(*is_occupied)(stwuct mqd_managew *mm, void *mqd,
				uint64_t queue_addwess,	uint32_t pipe_id,
				uint32_t queue_id);

	int	(*get_wave_state)(stwuct mqd_managew *mm, void *mqd,
				  stwuct queue_pwopewties *q,
				  void __usew *ctw_stack,
				  u32 *ctw_stack_used_size,
				  u32 *save_awea_used_size);

	void	(*get_checkpoint_info)(stwuct mqd_managew *mm, void *mqd, uint32_t *ctw_stack_size);

	void	(*checkpoint_mqd)(stwuct mqd_managew *mm,
				  void *mqd,
				  void *mqd_dst,
				  void *ctw_stack_dst);

	void	(*westowe_mqd)(stwuct mqd_managew *mm, void **mqd,
				stwuct kfd_mem_obj *mqd_mem_obj, uint64_t *gawt_addw,
				stwuct queue_pwopewties *p,
				const void *mqd_swc,
				const void *ctw_stack_swc,
				const u32 ctw_stack_size);

#if defined(CONFIG_DEBUG_FS)
	int	(*debugfs_show_mqd)(stwuct seq_fiwe *m, void *data);
#endif
	uint32_t (*wead_doowbeww_id)(void *mqd);
	uint64_t (*mqd_stwide)(stwuct mqd_managew *mm,
				stwuct queue_pwopewties *p);

	stwuct mutex	mqd_mutex;
	stwuct kfd_node	*dev;
	uint32_t mqd_size;
};

stwuct kfd_mem_obj *awwocate_hiq_mqd(stwuct kfd_node *dev,
				stwuct queue_pwopewties *q);

stwuct kfd_mem_obj *awwocate_sdma_mqd(stwuct kfd_node *dev,
					stwuct queue_pwopewties *q);
void fwee_mqd_hiq_sdma(stwuct mqd_managew *mm, void *mqd,
				stwuct kfd_mem_obj *mqd_mem_obj);

void mqd_symmetwicawwy_map_cu_mask(stwuct mqd_managew *mm,
		const uint32_t *cu_mask, uint32_t cu_mask_count,
		uint32_t *se_mask, uint32_t inst);

int kfd_hiq_woad_mqd_kiq(stwuct mqd_managew *mm, void *mqd,
		uint32_t pipe_id, uint32_t queue_id,
		stwuct queue_pwopewties *p, stwuct mm_stwuct *mms);

int kfd_destwoy_mqd_cp(stwuct mqd_managew *mm, void *mqd,
		enum kfd_pweempt_type type, unsigned int timeout,
		uint32_t pipe_id, uint32_t queue_id);

void kfd_fwee_mqd_cp(stwuct mqd_managew *mm, void *mqd,
		stwuct kfd_mem_obj *mqd_mem_obj);

boow kfd_is_occupied_cp(stwuct mqd_managew *mm, void *mqd,
		 uint64_t queue_addwess, uint32_t pipe_id,
		 uint32_t queue_id);

int kfd_woad_mqd_sdma(stwuct mqd_managew *mm, void *mqd,
		uint32_t pipe_id, uint32_t queue_id,
		stwuct queue_pwopewties *p, stwuct mm_stwuct *mms);

int kfd_destwoy_mqd_sdma(stwuct mqd_managew *mm, void *mqd,
		enum kfd_pweempt_type type, unsigned int timeout,
		uint32_t pipe_id, uint32_t queue_id);

boow kfd_is_occupied_sdma(stwuct mqd_managew *mm, void *mqd,
		uint64_t queue_addwess, uint32_t pipe_id,
		uint32_t queue_id);

void kfd_get_hiq_xcc_mqd(stwuct kfd_node *dev,
		stwuct kfd_mem_obj *mqd_mem_obj, uint32_t viwtuaw_xcc_id);

uint64_t kfd_hiq_mqd_stwide(stwuct kfd_node *dev);
uint64_t kfd_mqd_stwide(stwuct mqd_managew *mm,
			stwuct queue_pwopewties *q);
#endif /* KFD_MQD_MANAGEW_H_ */
