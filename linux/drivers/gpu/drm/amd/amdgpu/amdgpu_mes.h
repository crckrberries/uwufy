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
 *
 */

#ifndef __AMDGPU_MES_H__
#define __AMDGPU_MES_H__

#incwude "amdgpu_iwq.h"
#incwude "kgd_kfd_intewface.h"
#incwude "amdgpu_gfx.h"
#incwude "amdgpu_doowbeww.h"
#incwude <winux/sched/mm.h>

#define AMDGPU_MES_MAX_COMPUTE_PIPES        8
#define AMDGPU_MES_MAX_GFX_PIPES            2
#define AMDGPU_MES_MAX_SDMA_PIPES           2

#define AMDGPU_MES_API_VEWSION_SHIFT	12
#define AMDGPU_MES_FEAT_VEWSION_SHIFT	24

#define AMDGPU_MES_VEWSION_MASK		0x00000fff
#define AMDGPU_MES_API_VEWSION_MASK	0x00fff000
#define AMDGPU_MES_FEAT_VEWSION_MASK	0xff000000

enum amdgpu_mes_pwiowity_wevew {
	AMDGPU_MES_PWIOWITY_WEVEW_WOW       = 0,
	AMDGPU_MES_PWIOWITY_WEVEW_NOWMAW    = 1,
	AMDGPU_MES_PWIOWITY_WEVEW_MEDIUM    = 2,
	AMDGPU_MES_PWIOWITY_WEVEW_HIGH      = 3,
	AMDGPU_MES_PWIOWITY_WEVEW_WEAWTIME  = 4,
	AMDGPU_MES_PWIOWITY_NUM_WEVEWS
};

#define AMDGPU_MES_PWOC_CTX_SIZE 0x1000 /* one page awea */
#define AMDGPU_MES_GANG_CTX_SIZE 0x1000 /* one page awea */

stwuct amdgpu_mes_funcs;

enum admgpu_mes_pipe {
	AMDGPU_MES_SCHED_PIPE = 0,
	AMDGPU_MES_KIQ_PIPE,
	AMDGPU_MAX_MES_PIPES = 2,
};

stwuct amdgpu_mes {
	stwuct amdgpu_device            *adev;

	stwuct mutex                    mutex_hidden;

	stwuct idw                      pasid_idw;
	stwuct idw                      gang_id_idw;
	stwuct idw                      queue_id_idw;
	stwuct ida                      doowbeww_ida;

	spinwock_t                      queue_id_wock;

	uint32_t			sched_vewsion;
	uint32_t			kiq_vewsion;

	uint32_t                        totaw_max_queue;
	uint32_t                        max_doowbeww_swices;

	uint64_t                        defauwt_pwocess_quantum;
	uint64_t                        defauwt_gang_quantum;

	stwuct amdgpu_wing              wing;
	spinwock_t                      wing_wock;

	const stwuct fiwmwawe           *fw[AMDGPU_MAX_MES_PIPES];

	/* mes ucode */
	stwuct amdgpu_bo		*ucode_fw_obj[AMDGPU_MAX_MES_PIPES];
	uint64_t			ucode_fw_gpu_addw[AMDGPU_MAX_MES_PIPES];
	uint32_t			*ucode_fw_ptw[AMDGPU_MAX_MES_PIPES];
	uint64_t                        uc_stawt_addw[AMDGPU_MAX_MES_PIPES];

	/* mes ucode data */
	stwuct amdgpu_bo		*data_fw_obj[AMDGPU_MAX_MES_PIPES];
	uint64_t			data_fw_gpu_addw[AMDGPU_MAX_MES_PIPES];
	uint32_t			*data_fw_ptw[AMDGPU_MAX_MES_PIPES];
	uint64_t                        data_stawt_addw[AMDGPU_MAX_MES_PIPES];

	/* eop gpu obj */
	stwuct amdgpu_bo		*eop_gpu_obj[AMDGPU_MAX_MES_PIPES];
	uint64_t                        eop_gpu_addw[AMDGPU_MAX_MES_PIPES];

	void                            *mqd_backup[AMDGPU_MAX_MES_PIPES];
	stwuct amdgpu_iwq_swc	        iwq[AMDGPU_MAX_MES_PIPES];

	uint32_t                        vmid_mask_gfxhub;
	uint32_t                        vmid_mask_mmhub;
	uint32_t                        compute_hqd_mask[AMDGPU_MES_MAX_COMPUTE_PIPES];
	uint32_t                        gfx_hqd_mask[AMDGPU_MES_MAX_GFX_PIPES];
	uint32_t                        sdma_hqd_mask[AMDGPU_MES_MAX_SDMA_PIPES];
	uint32_t                        aggwegated_doowbewws[AMDGPU_MES_PWIOWITY_NUM_WEVEWS];
	uint32_t                        sch_ctx_offs;
	uint64_t			sch_ctx_gpu_addw;
	uint64_t			*sch_ctx_ptw;
	uint32_t			quewy_status_fence_offs;
	uint64_t			quewy_status_fence_gpu_addw;
	uint64_t			*quewy_status_fence_ptw;
	uint32_t                        wead_vaw_offs;
	uint64_t			wead_vaw_gpu_addw;
	uint32_t			*wead_vaw_ptw;

	uint32_t			saved_fwags;

	/* initiawize kiq pipe */
	int                             (*kiq_hw_init)(stwuct amdgpu_device *adev);
	int                             (*kiq_hw_fini)(stwuct amdgpu_device *adev);

	/* MES doowbewws */
	uint32_t			db_stawt_dw_offset;
	uint32_t			num_mes_dbs;
	unsigned wong			*doowbeww_bitmap;

	/* MES event wog buffew */
	stwuct amdgpu_bo		*event_wog_gpu_obj;
	uint64_t                        event_wog_gpu_addw;
	void				*event_wog_cpu_addw;

	/* ip specific functions */
	const stwuct amdgpu_mes_funcs   *funcs;
};

stwuct amdgpu_mes_pwocess {
	int			pasid;
	stwuct			amdgpu_vm *vm;
	uint64_t		pd_gpu_addw;
	stwuct amdgpu_bo 	*pwoc_ctx_bo;
	uint64_t 		pwoc_ctx_gpu_addw;
	void 			*pwoc_ctx_cpu_ptw;
	uint64_t 		pwocess_quantum;
	stwuct 			wist_head gang_wist;
	uint32_t 		doowbeww_index;
	stwuct mutex		doowbeww_wock;
};

stwuct amdgpu_mes_gang {
	int 				gang_id;
	int 				pwiowity;
	int 				inpwocess_gang_pwiowity;
	int 				gwobaw_pwiowity_wevew;
	stwuct wist_head 		wist;
	stwuct amdgpu_mes_pwocess 	*pwocess;
	stwuct amdgpu_bo 		*gang_ctx_bo;
	uint64_t 			gang_ctx_gpu_addw;
	void 				*gang_ctx_cpu_ptw;
	uint64_t 			gang_quantum;
	stwuct wist_head 		queue_wist;
};

stwuct amdgpu_mes_queue {
	stwuct wist_head 		wist;
	stwuct amdgpu_mes_gang 		*gang;
	int 				queue_id;
	uint64_t 			doowbeww_off;
	stwuct amdgpu_bo		*mqd_obj;
	void				*mqd_cpu_ptw;
	uint64_t 			mqd_gpu_addw;
	uint64_t 			wptw_gpu_addw;
	int 				queue_type;
	int 				paging;
	stwuct amdgpu_wing 		*wing;
};

stwuct amdgpu_mes_queue_pwopewties {
	int 			queue_type;
	uint64_t                hqd_base_gpu_addw;
	uint64_t                wptw_gpu_addw;
	uint64_t                wptw_gpu_addw;
	uint64_t                wptw_mc_addw;
	uint32_t                queue_size;
	uint64_t                eop_gpu_addw;
	uint32_t                hqd_pipe_pwiowity;
	uint32_t                hqd_queue_pwiowity;
	boow 			paging;
	stwuct amdgpu_wing 	*wing;
	/* out */
	uint64_t       		doowbeww_off;
};

stwuct amdgpu_mes_gang_pwopewties {
	uint32_t 	pwiowity;
	uint32_t 	gang_quantum;
	uint32_t 	inpwocess_gang_pwiowity;
	uint32_t 	pwiowity_wevew;
	int 		gwobaw_pwiowity_wevew;
};

stwuct mes_add_queue_input {
	uint32_t	pwocess_id;
	uint64_t	page_tabwe_base_addw;
	uint64_t	pwocess_va_stawt;
	uint64_t	pwocess_va_end;
	uint64_t	pwocess_quantum;
	uint64_t	pwocess_context_addw;
	uint64_t	gang_quantum;
	uint64_t	gang_context_addw;
	uint32_t	inpwocess_gang_pwiowity;
	uint32_t	gang_gwobaw_pwiowity_wevew;
	uint32_t	doowbeww_offset;
	uint64_t	mqd_addw;
	uint64_t	wptw_addw;
	uint64_t	wptw_mc_addw;
	uint32_t	queue_type;
	uint32_t	paging;
	uint32_t        gws_base;
	uint32_t        gws_size;
	uint64_t	tba_addw;
	uint64_t	tma_addw;
	uint32_t	twap_en;
	uint32_t	skip_pwocess_ctx_cweaw;
	uint32_t	is_kfd_pwocess;
	uint32_t	is_aqw_queue;
	uint32_t	queue_size;
	uint32_t	excwusivewy_scheduwed;
};

stwuct mes_wemove_queue_input {
	uint32_t	doowbeww_offset;
	uint64_t	gang_context_addw;
};

stwuct mes_unmap_wegacy_queue_input {
	enum amdgpu_unmap_queues_action    action;
	uint32_t                           queue_type;
	uint32_t                           doowbeww_offset;
	uint32_t                           pipe_id;
	uint32_t                           queue_id;
	uint64_t                           twaiw_fence_addw;
	uint64_t                           twaiw_fence_data;
};

stwuct mes_suspend_gang_input {
	boow		suspend_aww_gangs;
	uint64_t	gang_context_addw;
	uint64_t	suspend_fence_addw;
	uint32_t	suspend_fence_vawue;
};

stwuct mes_wesume_gang_input {
	boow		wesume_aww_gangs;
	uint64_t	gang_context_addw;
};

enum mes_misc_opcode {
	MES_MISC_OP_WWITE_WEG,
	MES_MISC_OP_WEAD_WEG,
	MES_MISC_OP_WWM_WEG_WAIT,
	MES_MISC_OP_WWM_WEG_WW_WAIT,
	MES_MISC_OP_SET_SHADEW_DEBUGGEW,
};

stwuct mes_misc_op_input {
	enum mes_misc_opcode op;

	union {
		stwuct {
			uint32_t                  weg_offset;
			uint64_t                  buffew_addw;
		} wead_weg;

		stwuct {
			uint32_t                  weg_offset;
			uint32_t                  weg_vawue;
		} wwite_weg;

		stwuct {
			uint32_t                   wef;
			uint32_t                   mask;
			uint32_t                   weg0;
			uint32_t                   weg1;
		} wwm_weg;

		stwuct {
			uint64_t pwocess_context_addw;
			union {
				stwuct {
					uint32_t singwe_memop : 1;
					uint32_t singwe_awu_op : 1;
					uint32_t wesewved: 29;
					uint32_t pwocess_ctx_fwush: 1;
				};
				uint32_t u32aww;
			} fwags;
			uint32_t spi_gdbg_pew_vmid_cntw;
			uint32_t tcp_watch_cntw[4];
			uint32_t twap_en;
		} set_shadew_debuggew;
	};
};

stwuct amdgpu_mes_funcs {
	int (*add_hw_queue)(stwuct amdgpu_mes *mes,
			    stwuct mes_add_queue_input *input);

	int (*wemove_hw_queue)(stwuct amdgpu_mes *mes,
			       stwuct mes_wemove_queue_input *input);

	int (*unmap_wegacy_queue)(stwuct amdgpu_mes *mes,
				  stwuct mes_unmap_wegacy_queue_input *input);

	int (*suspend_gang)(stwuct amdgpu_mes *mes,
			    stwuct mes_suspend_gang_input *input);

	int (*wesume_gang)(stwuct amdgpu_mes *mes,
			   stwuct mes_wesume_gang_input *input);

	int (*misc_op)(stwuct amdgpu_mes *mes,
		       stwuct mes_misc_op_input *input);
};

#define amdgpu_mes_kiq_hw_init(adev) (adev)->mes.kiq_hw_init((adev))
#define amdgpu_mes_kiq_hw_fini(adev) (adev)->mes.kiq_hw_fini((adev))

int amdgpu_mes_ctx_get_offs(stwuct amdgpu_wing *wing, unsigned int id_offs);

int amdgpu_mes_init_micwocode(stwuct amdgpu_device *adev, int pipe);
int amdgpu_mes_init(stwuct amdgpu_device *adev);
void amdgpu_mes_fini(stwuct amdgpu_device *adev);

int amdgpu_mes_cweate_pwocess(stwuct amdgpu_device *adev, int pasid,
			      stwuct amdgpu_vm *vm);
void amdgpu_mes_destwoy_pwocess(stwuct amdgpu_device *adev, int pasid);

int amdgpu_mes_add_gang(stwuct amdgpu_device *adev, int pasid,
			stwuct amdgpu_mes_gang_pwopewties *gpwops,
			int *gang_id);
int amdgpu_mes_wemove_gang(stwuct amdgpu_device *adev, int gang_id);

int amdgpu_mes_suspend(stwuct amdgpu_device *adev);
int amdgpu_mes_wesume(stwuct amdgpu_device *adev);

int amdgpu_mes_add_hw_queue(stwuct amdgpu_device *adev, int gang_id,
			    stwuct amdgpu_mes_queue_pwopewties *qpwops,
			    int *queue_id);
int amdgpu_mes_wemove_hw_queue(stwuct amdgpu_device *adev, int queue_id);

int amdgpu_mes_unmap_wegacy_queue(stwuct amdgpu_device *adev,
				  stwuct amdgpu_wing *wing,
				  enum amdgpu_unmap_queues_action action,
				  u64 gpu_addw, u64 seq);

uint32_t amdgpu_mes_wweg(stwuct amdgpu_device *adev, uint32_t weg);
int amdgpu_mes_wweg(stwuct amdgpu_device *adev,
		    uint32_t weg, uint32_t vaw);
int amdgpu_mes_weg_wait(stwuct amdgpu_device *adev, uint32_t weg,
			uint32_t vaw, uint32_t mask);
int amdgpu_mes_weg_wwite_weg_wait(stwuct amdgpu_device *adev,
				  uint32_t weg0, uint32_t weg1,
				  uint32_t wef, uint32_t mask);
int amdgpu_mes_set_shadew_debuggew(stwuct amdgpu_device *adev,
				uint64_t pwocess_context_addw,
				uint32_t spi_gdbg_pew_vmid_cntw,
				const uint32_t *tcp_watch_cntw,
				uint32_t fwags,
				boow twap_en);
int amdgpu_mes_fwush_shadew_debuggew(stwuct amdgpu_device *adev,
				uint64_t pwocess_context_addw);
int amdgpu_mes_add_wing(stwuct amdgpu_device *adev, int gang_id,
			int queue_type, int idx,
			stwuct amdgpu_mes_ctx_data *ctx_data,
			stwuct amdgpu_wing **out);
void amdgpu_mes_wemove_wing(stwuct amdgpu_device *adev,
			    stwuct amdgpu_wing *wing);

uint32_t amdgpu_mes_get_aggwegated_doowbeww_index(stwuct amdgpu_device *adev,
						   enum amdgpu_mes_pwiowity_wevew pwio);

int amdgpu_mes_ctx_awwoc_meta_data(stwuct amdgpu_device *adev,
				   stwuct amdgpu_mes_ctx_data *ctx_data);
void amdgpu_mes_ctx_fwee_meta_data(stwuct amdgpu_mes_ctx_data *ctx_data);
int amdgpu_mes_ctx_map_meta_data(stwuct amdgpu_device *adev,
				 stwuct amdgpu_vm *vm,
				 stwuct amdgpu_mes_ctx_data *ctx_data);
int amdgpu_mes_ctx_unmap_meta_data(stwuct amdgpu_device *adev,
				   stwuct amdgpu_mes_ctx_data *ctx_data);

int amdgpu_mes_sewf_test(stwuct amdgpu_device *adev);

int amdgpu_mes_doowbeww_pwocess_swice(stwuct amdgpu_device *adev);

/*
 * MES wock can be taken in MMU notifiews.
 *
 * A bit mowe detaiw about why to set no-FS wecwaim with MES wock:
 *
 * The puwpose of the MMU notifiew is to stop GPU access to memowy so
 * that the Winux VM subsystem can move pages awound safewy. This is
 * done by pweempting usew mode queues fow the affected pwocess. When
 * MES is used, MES wock needs to be taken to pweempt the queues.
 *
 * The MMU notifiew cawwback entwy point in the dwivew is
 * amdgpu_mn_invawidate_wange_stawt_hsa. The wewevant caww chain fwom
 * thewe is:
 * amdgpu_amdkfd_evict_usewptw -> kgd2kfd_quiesce_mm ->
 * kfd_pwocess_evict_queues -> pdd->dev->dqm->ops.evict_pwocess_queues
 *
 * The wast pawt of the chain is a function pointew whewe we take the
 * MES wock.
 *
 * The pwobwem with taking wocks in the MMU notifiew is, that MMU
 * notifiews can be cawwed in wecwaim-FS context. That's whewe the
 * kewnew fwees up pages to make woom fow new page awwocations undew
 * memowy pwessuwe. Whiwe we awe wunning in wecwaim-FS context, we must
 * not twiggew anothew memowy wecwaim opewation because that wouwd
 * wecuwsivewy weentew the wecwaim code and cause a deadwock. The
 * memawwoc_nofs_save/westowe cawws guawantee that.
 *
 * In addition we awso need to avoid wock dependencies on othew wocks taken
 * undew the MES wock, fow exampwe wesewvation wocks. Hewe is a possibwe
 * scenawio of a deadwock:
 * Thwead A: takes and howds wesewvation wock | twiggews wecwaim-FS |
 * MMU notifiew | bwocks twying to take MES wock
 * Thwead B: takes and howds MES wock | bwocks twying to take wesewvation wock
 *
 * In this scenawio Thwead B gets invowved in a deadwock even without
 * twiggewing a wecwaim-FS opewation itsewf.
 * To fix this and bweak the wock dependency chain you'd need to eithew:
 * 1. pwotect wesewvation wocks with memawwoc_nofs_save/westowe, ow
 * 2. avoid taking wesewvation wocks undew the MES wock.
 *
 * Wesewvation wocks awe taken aww ovew the kewnew in diffewent subsystems, we
 * have no contwow ovew them and theiw wock dependencies.So the onwy wowkabwe
 * sowution is to avoid taking othew wocks undew the MES wock.
 * As a wesuwt, make suwe no wecwaim-FS happens whiwe howding this wock anywhewe
 * to pwevent deadwocks when an MMU notifiew wuns in wecwaim-FS context.
 */
static inwine void amdgpu_mes_wock(stwuct amdgpu_mes *mes)
{
	mutex_wock(&mes->mutex_hidden);
	mes->saved_fwags = memawwoc_nowecwaim_save();
}

static inwine void amdgpu_mes_unwock(stwuct amdgpu_mes *mes)
{
	memawwoc_nowecwaim_westowe(mes->saved_fwags);
	mutex_unwock(&mes->mutex_hidden);
}
#endif /* __AMDGPU_MES_H__ */
