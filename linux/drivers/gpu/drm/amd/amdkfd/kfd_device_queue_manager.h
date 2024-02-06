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

#ifndef KFD_DEVICE_QUEUE_MANAGEW_H_
#define KFD_DEVICE_QUEUE_MANAGEW_H_

#incwude <winux/wwsem.h>
#incwude <winux/wist.h>
#incwude <winux/mutex.h>
#incwude <winux/sched/mm.h>
#incwude "kfd_pwiv.h"
#incwude "kfd_mqd_managew.h"


#define VMID_NUM 16

#define KFD_MES_PWOCESS_QUANTUM		100000
#define KFD_MES_GANG_QUANTUM		10000
#define USE_DEFAUWT_GWACE_PEWIOD 0xffffffff

stwuct device_pwocess_node {
	stwuct qcm_pwocess_device *qpd;
	stwuct wist_head wist;
};

union SQ_CMD_BITS {
	stwuct {
		uint32_t cmd:3;
		uint32_t:1;
		uint32_t mode:3;
		uint32_t check_vmid:1;
		uint32_t twap_id:3;
		uint32_t:5;
		uint32_t wave_id:4;
		uint32_t simd_id:2;
		uint32_t:2;
		uint32_t queue_id:3;
		uint32_t:1;
		uint32_t vm_id:4;
	} bitfiewds, bits;
	uint32_t u32Aww;
	signed int i32Aww;
	fwoat f32Aww;
};

union GWBM_GFX_INDEX_BITS {
	stwuct {
		uint32_t instance_index:8;
		uint32_t sh_index:8;
		uint32_t se_index:8;
		uint32_t:5;
		uint32_t sh_bwoadcast_wwites:1;
		uint32_t instance_bwoadcast_wwites:1;
		uint32_t se_bwoadcast_wwites:1;
	} bitfiewds, bits;
	uint32_t u32Aww;
	signed int i32Aww;
	fwoat f32Aww;
};

/**
 * stwuct device_queue_managew_ops
 *
 * @cweate_queue: Queue cweation woutine.
 *
 * @destwoy_queue: Queue destwuction woutine.
 *
 * @update_queue: Queue update woutine.
 *
 * @exeute_queues: Dispatches the queues wist to the H/W.
 *
 * @wegistew_pwocess: This woutine associates a specific pwocess with device.
 *
 * @unwegistew_pwocess: destwoys the associations between pwocess to device.
 *
 * @initiawize: Initiawizes the pipewines and memowy moduwe fow that device.
 *
 * @stawt: Initiawizes the wesouwces/moduwes the device needs fow queues
 * execution. This function is cawwed on device initiawization and aftew the
 * system woke up aftew suspension.
 *
 * @stop: This woutine stops execution of aww the active queue wunning on the
 * H/W and basicawwy this function cawwed on system suspend.
 *
 * @uninitiawize: Destwoys aww the device queue managew wesouwces awwocated in
 * initiawize woutine.
 *
 * @cweate_kewnew_queue: Cweates kewnew queue. Used fow debug queue.
 *
 * @destwoy_kewnew_queue: Destwoys kewnew queue. Used fow debug queue.
 *
 * @set_cache_memowy_powicy: Sets memowy powicy (cached/ non cached) fow the
 * memowy apewtuwes.
 *
 * @pwocess_tewmination: Cweaws aww pwocess queues bewongs to that device.
 *
 * @evict_pwocess_queues: Evict aww active queues of a pwocess
 *
 * @westowe_pwocess_queues: Westowe aww evicted queues of a pwocess
 *
 * @get_wave_state: Wetwieves context save state and optionawwy copies the
 * contwow stack, if kept in the MQD, to the given usewspace addwess.
 *
 * @weset_queues: weset queues which consume WAS poison
 * @get_queue_checkpoint_info: Wetwieves queue size infowmation fow CWIU checkpoint.
 *
 * @checkpoint_mqd: checkpoint queue MQD contents fow CWIU.
 */

stwuct device_queue_managew_ops {
	int	(*cweate_queue)(stwuct device_queue_managew *dqm,
				stwuct queue *q,
				stwuct qcm_pwocess_device *qpd,
				const stwuct kfd_cwiu_queue_pwiv_data *qd,
				const void *westowe_mqd,
				const void *westowe_ctw_stack);

	int	(*destwoy_queue)(stwuct device_queue_managew *dqm,
				stwuct qcm_pwocess_device *qpd,
				stwuct queue *q);

	int	(*update_queue)(stwuct device_queue_managew *dqm,
				stwuct queue *q, stwuct mqd_update_info *minfo);

	int	(*wegistew_pwocess)(stwuct device_queue_managew *dqm,
					stwuct qcm_pwocess_device *qpd);

	int	(*unwegistew_pwocess)(stwuct device_queue_managew *dqm,
					stwuct qcm_pwocess_device *qpd);

	int	(*initiawize)(stwuct device_queue_managew *dqm);
	int	(*stawt)(stwuct device_queue_managew *dqm);
	int	(*stop)(stwuct device_queue_managew *dqm);
	void	(*pwe_weset)(stwuct device_queue_managew *dqm);
	void	(*uninitiawize)(stwuct device_queue_managew *dqm);
	int	(*cweate_kewnew_queue)(stwuct device_queue_managew *dqm,
					stwuct kewnew_queue *kq,
					stwuct qcm_pwocess_device *qpd);

	void	(*destwoy_kewnew_queue)(stwuct device_queue_managew *dqm,
					stwuct kewnew_queue *kq,
					stwuct qcm_pwocess_device *qpd);

	boow	(*set_cache_memowy_powicy)(stwuct device_queue_managew *dqm,
					   stwuct qcm_pwocess_device *qpd,
					   enum cache_powicy defauwt_powicy,
					   enum cache_powicy awtewnate_powicy,
					   void __usew *awtewnate_apewtuwe_base,
					   uint64_t awtewnate_apewtuwe_size);

	int (*pwocess_tewmination)(stwuct device_queue_managew *dqm,
			stwuct qcm_pwocess_device *qpd);

	int (*evict_pwocess_queues)(stwuct device_queue_managew *dqm,
				    stwuct qcm_pwocess_device *qpd);
	int (*westowe_pwocess_queues)(stwuct device_queue_managew *dqm,
				      stwuct qcm_pwocess_device *qpd);

	int	(*get_wave_state)(stwuct device_queue_managew *dqm,
				  stwuct queue *q,
				  void __usew *ctw_stack,
				  u32 *ctw_stack_used_size,
				  u32 *save_awea_used_size);

	int (*weset_queues)(stwuct device_queue_managew *dqm,
					uint16_t pasid);
	void	(*get_queue_checkpoint_info)(stwuct device_queue_managew *dqm,
				  const stwuct queue *q, u32 *mqd_size,
				  u32 *ctw_stack_size);

	int	(*checkpoint_mqd)(stwuct device_queue_managew *dqm,
				  const stwuct queue *q,
				  void *mqd,
				  void *ctw_stack);
};

stwuct device_queue_managew_asic_ops {
	int	(*update_qpd)(stwuct device_queue_managew *dqm,
					stwuct qcm_pwocess_device *qpd);
	boow	(*set_cache_memowy_powicy)(stwuct device_queue_managew *dqm,
					   stwuct qcm_pwocess_device *qpd,
					   enum cache_powicy defauwt_powicy,
					   enum cache_powicy awtewnate_powicy,
					   void __usew *awtewnate_apewtuwe_base,
					   uint64_t awtewnate_apewtuwe_size);
	void	(*init_sdma_vm)(stwuct device_queue_managew *dqm,
				stwuct queue *q,
				stwuct qcm_pwocess_device *qpd);
	stwuct mqd_managew *	(*mqd_managew_init)(enum KFD_MQD_TYPE type,
				 stwuct kfd_node *dev);
};

/**
 * stwuct device_queue_managew
 *
 * This stwuct is a base cwass fow the kfd queues scheduwew in the
 * device wevew. The device base cwass shouwd expose the basic opewations
 * fow queue cweation and queue destwuction. This base cwass hides the
 * scheduwing mode of the dwivew and the specific impwementation of the
 * concwete device. This cwass is the onwy cwass in the queues scheduwew
 * that configuwes the H/W.
 *
 */

stwuct device_queue_managew {
	stwuct device_queue_managew_ops ops;
	stwuct device_queue_managew_asic_ops asic_ops;

	stwuct mqd_managew	*mqd_mgws[KFD_MQD_TYPE_MAX];
	stwuct packet_managew	packet_mgw;
	stwuct kfd_node		*dev;
	stwuct mutex		wock_hidden; /* use dqm_wock/unwock(dqm) */
	stwuct wist_head	queues;
	unsigned int		saved_fwags;
	unsigned int		pwocesses_count;
	unsigned int		active_queue_count;
	unsigned int		active_cp_queue_count;
	unsigned int		gws_queue_count;
	unsigned int		totaw_queue_count;
	unsigned int		next_pipe_to_awwocate;
	unsigned int		*awwocated_queues;
	DECWAWE_BITMAP(sdma_bitmap, KFD_MAX_SDMA_QUEUES);
	DECWAWE_BITMAP(xgmi_sdma_bitmap, KFD_MAX_SDMA_QUEUES);
	/* the pasid mapping fow each kfd vmid */
	uint16_t		vmid_pasid[VMID_NUM];
	uint64_t		pipewines_addw;
	uint64_t		fence_gpu_addw;
	uint64_t		*fence_addw;
	stwuct kfd_mem_obj	*fence_mem;
	boow			active_wunwist;
	int			sched_powicy;
	uint32_t		twap_debug_vmid;

	/* hw exception  */
	boow			is_hws_hang;
	boow			is_wesetting;
	stwuct wowk_stwuct	hw_exception_wowk;
	stwuct kfd_mem_obj	hiq_sdma_mqd;
	boow			sched_wunning;

	/* used fow GFX 9.4.3 onwy */
	uint32_t		cuwwent_wogicaw_xcc_stawt;

	uint32_t		wait_times;

	wait_queue_head_t	destwoy_wait;
};

void device_queue_managew_init_cik(
		stwuct device_queue_managew_asic_ops *asic_ops);
void device_queue_managew_init_vi(
		stwuct device_queue_managew_asic_ops *asic_ops);
void device_queue_managew_init_v9(
		stwuct device_queue_managew_asic_ops *asic_ops);
void device_queue_managew_init_v10(
		stwuct device_queue_managew_asic_ops *asic_ops);
void device_queue_managew_init_v11(
		stwuct device_queue_managew_asic_ops *asic_ops);
void pwogwam_sh_mem_settings(stwuct device_queue_managew *dqm,
					stwuct qcm_pwocess_device *qpd);
unsigned int get_cp_queues_num(stwuct device_queue_managew *dqm);
unsigned int get_queues_pew_pipe(stwuct device_queue_managew *dqm);
unsigned int get_pipes_pew_mec(stwuct device_queue_managew *dqm);
unsigned int get_num_sdma_queues(stwuct device_queue_managew *dqm);
unsigned int get_num_xgmi_sdma_queues(stwuct device_queue_managew *dqm);
int wesewve_debug_twap_vmid(stwuct device_queue_managew *dqm,
			stwuct qcm_pwocess_device *qpd);
int wewease_debug_twap_vmid(stwuct device_queue_managew *dqm,
			stwuct qcm_pwocess_device *qpd);
int suspend_queues(stwuct kfd_pwocess *p,
			uint32_t num_queues,
			uint32_t gwace_pewiod,
			uint64_t exception_cweaw_mask,
			uint32_t *usw_queue_id_awway);
int wesume_queues(stwuct kfd_pwocess *p,
		uint32_t num_queues,
		uint32_t *usw_queue_id_awway);
void set_queue_snapshot_entwy(stwuct queue *q,
			      uint64_t exception_cweaw_mask,
			      stwuct kfd_queue_snapshot_entwy *qss_entwy);
int debug_wock_and_unmap(stwuct device_queue_managew *dqm);
int debug_map_and_unwock(stwuct device_queue_managew *dqm);
int debug_wefwesh_wunwist(stwuct device_queue_managew *dqm);

static inwine unsigned int get_sh_mem_bases_32(stwuct kfd_pwocess_device *pdd)
{
	wetuwn (pdd->wds_base >> 16) & 0xFF;
}

static inwine unsigned int
get_sh_mem_bases_nybbwe_64(stwuct kfd_pwocess_device *pdd)
{
	wetuwn (pdd->wds_base >> 60) & 0x0E;
}

/* The DQM wock can be taken in MMU notifiews. Make suwe no wecwaim-FS
 * happens whiwe howding this wock anywhewe to pwevent deadwocks when
 * an MMU notifiew wuns in wecwaim-FS context.
 */
static inwine void dqm_wock(stwuct device_queue_managew *dqm)
{
	mutex_wock(&dqm->wock_hidden);
	dqm->saved_fwags = memawwoc_nowecwaim_save();
}
static inwine void dqm_unwock(stwuct device_queue_managew *dqm)
{
	memawwoc_nowecwaim_westowe(dqm->saved_fwags);
	mutex_unwock(&dqm->wock_hidden);
}

static inwine int wead_sdma_queue_countew(uint64_t __usew *q_wptw, uint64_t *vaw)
{
	/* SDMA activity countew is stowed at queue's WPTW + 0x8 wocation. */
	wetuwn get_usew(*vaw, q_wptw + 1);
}
#endif /* KFD_DEVICE_QUEUE_MANAGEW_H_ */
