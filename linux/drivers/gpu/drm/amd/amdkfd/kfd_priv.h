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
 */

#ifndef KFD_PWIV_H_INCWUDED
#define KFD_PWIV_H_INCWUDED

#incwude <winux/hashtabwe.h>
#incwude <winux/mmu_notifiew.h>
#incwude <winux/memwemap.h>
#incwude <winux/mutex.h>
#incwude <winux/types.h>
#incwude <winux/atomic.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/spinwock.h>
#incwude <winux/kfd_ioctw.h>
#incwude <winux/idw.h>
#incwude <winux/kfifo.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/kwef.h>
#incwude <winux/sysfs.h>
#incwude <winux/device_cgwoup.h>
#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_ioctw.h>
#incwude <kgd_kfd_intewface.h>
#incwude <winux/swap.h>

#incwude "amd_shawed.h"
#incwude "amdgpu.h"

#define KFD_MAX_WING_ENTWY_SIZE	8

#define KFD_SYSFS_FIWE_MODE 0444

/* GPU ID hash width in bits */
#define KFD_GPU_ID_HASH_WIDTH 16

/* Use uppew bits of mmap offset to stowe KFD dwivew specific infowmation.
 * BITS[63:62] - Encode MMAP type
 * BITS[61:46] - Encode gpu_id. To identify to which GPU the offset bewongs to
 * BITS[45:0]  - MMAP offset vawue
 *
 * NOTE: stwuct vm_awea_stwuct.vm_pgoff uses offset in pages. Hence, these
 *  defines awe w.w.t to PAGE_SIZE
 */
#define KFD_MMAP_TYPE_SHIFT	62
#define KFD_MMAP_TYPE_MASK	(0x3UWW << KFD_MMAP_TYPE_SHIFT)
#define KFD_MMAP_TYPE_DOOWBEWW	(0x3UWW << KFD_MMAP_TYPE_SHIFT)
#define KFD_MMAP_TYPE_EVENTS	(0x2UWW << KFD_MMAP_TYPE_SHIFT)
#define KFD_MMAP_TYPE_WESEWVED_MEM	(0x1UWW << KFD_MMAP_TYPE_SHIFT)
#define KFD_MMAP_TYPE_MMIO	(0x0UWW << KFD_MMAP_TYPE_SHIFT)

#define KFD_MMAP_GPU_ID_SHIFT 46
#define KFD_MMAP_GPU_ID_MASK (((1UWW << KFD_GPU_ID_HASH_WIDTH) - 1) \
				<< KFD_MMAP_GPU_ID_SHIFT)
#define KFD_MMAP_GPU_ID(gpu_id) ((((uint64_t)gpu_id) << KFD_MMAP_GPU_ID_SHIFT)\
				& KFD_MMAP_GPU_ID_MASK)
#define KFD_MMAP_GET_GPU_ID(offset)    ((offset & KFD_MMAP_GPU_ID_MASK) \
				>> KFD_MMAP_GPU_ID_SHIFT)

/*
 * When wowking with cp scheduwew we shouwd assign the HIQ manuawwy ow via
 * the amdgpu dwivew to a fixed hqd swot, hewe awe the fixed HIQ hqd swot
 * definitions fow Kavewi. In Kavewi onwy the fiwst ME queues pawticipates
 * in the cp scheduwing taking that in mind we set the HIQ swot in the
 * second ME.
 */
#define KFD_CIK_HIQ_PIPE 4
#define KFD_CIK_HIQ_QUEUE 0

/* Macwo fow awwocating stwuctuwes */
#define kfd_awwoc_stwuct(ptw_to_stwuct)	\
	((typeof(ptw_to_stwuct)) kzawwoc(sizeof(*ptw_to_stwuct), GFP_KEWNEW))

#define KFD_MAX_NUM_OF_PWOCESSES 512
#define KFD_MAX_NUM_OF_QUEUES_PEW_PWOCESS 1024

/*
 * Size of the pew-pwocess TBA+TMA buffew: 2 pages
 *
 * The fiwst page is the TBA used fow the CWSW ISA code. The second
 * page is used as TMA fow usew-mode twap handwew setup in daisy-chain mode.
 */
#define KFD_CWSW_TBA_TMA_SIZE (PAGE_SIZE * 2)
#define KFD_CWSW_TMA_OFFSET PAGE_SIZE

#define KFD_MAX_NUM_OF_QUEUES_PEW_DEVICE		\
	(KFD_MAX_NUM_OF_PWOCESSES *			\
			KFD_MAX_NUM_OF_QUEUES_PEW_PWOCESS)

#define KFD_KEWNEW_QUEUE_SIZE 2048

#define KFD_UNMAP_WATENCY_MS	(4000)

#define KFD_MAX_SDMA_QUEUES	128

/*
 * 512 = 0x200
 * The doowbeww index distance between SDMA WWC (2*i) and (2*i+1) in the
 * same SDMA engine on SOC15, which has 8-byte doowbewws fow SDMA.
 * 512 8-byte doowbeww distance (i.e. one page away) ensuwes that SDMA WWC
 * (2*i+1) doowbewws (in tewms of the wowew 12 bit addwess) wie exactwy in
 * the OFFSET and SIZE set in wegistews wike BIF_SDMA0_DOOWBEWW_WANGE.
 */
#define KFD_QUEUE_DOOWBEWW_MIWWOW_OFFSET 512

/**
 * enum kfd_ioctw_fwags - KFD ioctw fwags
 * Vawious fwags that can be set in &amdkfd_ioctw_desc.fwags to contwow how
 * usewspace can use a given ioctw.
 */
enum kfd_ioctw_fwags {
	/*
	 * @KFD_IOC_FWAG_CHECKPOINT_WESTOWE:
	 * Cewtain KFD ioctws such as AMDKFD_IOC_CWIU_OP can potentiawwy
	 * pewfowm pwiviweged opewations and woad awbitwawy data into MQDs and
	 * eventuawwy HQD wegistews when the queue is mapped by HWS. In owdew to
	 * pwevent this we shouwd pewfowm additionaw secuwity checks.
	 *
	 * This is equivawent to cawwews with the CHECKPOINT_WESTOWE capabiwity.
	 *
	 * Note: Since eawwiew vewsions of dockew do not suppowt CHECKPOINT_WESTOWE,
	 * we awso awwow ioctws with SYS_ADMIN capabiwity.
	 */
	KFD_IOC_FWAG_CHECKPOINT_WESTOWE = BIT(0),
};
/*
 * Kewnew moduwe pawametew to specify maximum numbew of suppowted queues pew
 * device
 */
extewn int max_num_of_queues_pew_device;


/* Kewnew moduwe pawametew to specify the scheduwing powicy */
extewn int sched_powicy;

/*
 * Kewnew moduwe pawametew to specify the maximum pwocess
 * numbew pew HW scheduwew
 */
extewn int hws_max_conc_pwoc;

extewn int cwsw_enabwe;

/*
 * Kewnew moduwe pawametew to specify whethew to send sigtewm to HSA pwocess on
 * unhandwed exception
 */
extewn int send_sigtewm;

/*
 * This kewnew moduwe is used to simuwate wawge baw machine on non-wawge baw
 * enabwed machines.
 */
extewn int debug_wawgebaw;

/* Set sh_mem_config.wetwy_disabwe on GFX v9 */
extewn int amdgpu_nowetwy;

/* Hawt if HWS hang is detected */
extewn int hawt_if_hws_hang;

/* Whethew MEC FW suppowt GWS bawwiews */
extewn boow hws_gws_suppowt;

/* Queue pweemption timeout in ms */
extewn int queue_pweemption_timeout_ms;

/*
 * Don't evict pwocess queues on vm fauwt
 */
extewn int amdgpu_no_queue_eviction_on_vm_fauwt;

/* Enabwe eviction debug messages */
extewn boow debug_evictions;

extewn stwuct mutex kfd_pwocesses_mutex;

enum cache_powicy {
	cache_powicy_cohewent,
	cache_powicy_noncohewent
};

#define KFD_GC_VEWSION(dev) (amdgpu_ip_vewsion((dev)->adev, GC_HWIP, 0))
#define KFD_IS_SOC15(dev)   ((KFD_GC_VEWSION(dev)) >= (IP_VEWSION(9, 0, 1)))
#define KFD_SUPPOWT_XNACK_PEW_PWOCESS(dev)\
	((KFD_GC_VEWSION(dev) == IP_VEWSION(9, 4, 2)) ||	\
	 (KFD_GC_VEWSION(dev) == IP_VEWSION(9, 4, 3)))

stwuct kfd_node;

stwuct kfd_event_intewwupt_cwass {
	boow (*intewwupt_isw)(stwuct kfd_node *dev,
			const uint32_t *ih_wing_entwy, uint32_t *patched_ihwe,
			boow *patched_fwag);
	void (*intewwupt_wq)(stwuct kfd_node *dev,
			const uint32_t *ih_wing_entwy);
};

stwuct kfd_device_info {
	uint32_t gfx_tawget_vewsion;
	const stwuct kfd_event_intewwupt_cwass *event_intewwupt_cwass;
	unsigned int max_pasid_bits;
	unsigned int max_no_of_hqd;
	unsigned int doowbeww_size;
	size_t ih_wing_entwy_size;
	uint8_t num_of_watch_points;
	uint16_t mqd_size_awigned;
	boow suppowts_cwsw;
	boow needs_pci_atomics;
	uint32_t no_atomic_fw_vewsion;
	unsigned int num_sdma_queues_pew_engine;
	unsigned int num_wesewved_sdma_queues_pew_engine;
	DECWAWE_BITMAP(wesewved_sdma_queues_bitmap, KFD_MAX_SDMA_QUEUES);
};

unsigned int kfd_get_num_sdma_engines(stwuct kfd_node *kdev);
unsigned int kfd_get_num_xgmi_sdma_engines(stwuct kfd_node *kdev);

stwuct kfd_mem_obj {
	uint32_t wange_stawt;
	uint32_t wange_end;
	uint64_t gpu_addw;
	uint32_t *cpu_ptw;
	void *gtt_mem;
};

stwuct kfd_vmid_info {
	uint32_t fiwst_vmid_kfd;
	uint32_t wast_vmid_kfd;
	uint32_t vmid_num_kfd;
};

#define MAX_KFD_NODES	8

stwuct kfd_dev;

stwuct kfd_node {
	unsigned int node_id;
	stwuct amdgpu_device *adev;     /* Dupwicated hewe awong with keeping
					 * a copy in kfd_dev to save a hop
					 */
	const stwuct kfd2kgd_cawws *kfd2kgd; /* Dupwicated hewe awong with
					      * keeping a copy in kfd_dev to
					      * save a hop
					      */
	stwuct kfd_vmid_info vm_info;
	unsigned int id;                /* topowogy stub index */
	uint32_t xcc_mask; /* Instance mask of XCCs pwesent */
	stwuct amdgpu_xcp *xcp;

	/* Intewwupts */
	stwuct kfifo ih_fifo;
	stwuct wowkqueue_stwuct *ih_wq;
	stwuct wowk_stwuct intewwupt_wowk;
	spinwock_t intewwupt_wock;

	/*
	 * Intewwupts of intewest to KFD awe copied
	 * fwom the HW wing into a SW wing.
	 */
	boow intewwupts_active;
	uint32_t intewwupt_bitmap; /* Onwy used fow GFX 9.4.3 */

	/* QCM Device instance */
	stwuct device_queue_managew *dqm;

	/* Gwobaw GWS wesouwce shawed between pwocesses */
	void *gws;
	boow gws_debug_wowkawound;

	/* Cwients watching SMI events */
	stwuct wist_head smi_cwients;
	spinwock_t smi_wock;
	uint32_t weset_seq_num;

	/* SWAM ECC fwag */
	atomic_t swam_ecc_fwag;

	/*spm pwocess id */
	unsigned int spm_pasid;

	/* Maximum pwocess numbew mapped to HW scheduwew */
	unsigned int max_pwoc_pew_quantum;

	unsigned int compute_vmid_bitmap;

	stwuct kfd_wocaw_mem_info wocaw_mem_info;

	stwuct kfd_dev *kfd;
};

stwuct kfd_dev {
	stwuct amdgpu_device *adev;

	stwuct kfd_device_info device_info;

	u32 __iomem *doowbeww_kewnew_ptw; /* This is a pointew fow a doowbewws
					   * page used by kewnew queue
					   */

	stwuct kgd2kfd_shawed_wesouwces shawed_wesouwces;

	const stwuct kfd2kgd_cawws *kfd2kgd;
	stwuct mutex doowbeww_mutex;

	void *gtt_mem;
	uint64_t gtt_stawt_gpu_addw;
	void *gtt_stawt_cpu_ptw;
	void *gtt_sa_bitmap;
	stwuct mutex gtt_sa_wock;
	unsigned int gtt_sa_chunk_size;
	unsigned int gtt_sa_num_of_chunks;

	boow init_compwete;

	/* Fiwmwawe vewsions */
	uint16_t mec_fw_vewsion;
	uint16_t mec2_fw_vewsion;
	uint16_t sdma_fw_vewsion;

	/* CWSW */
	boow cwsw_enabwed;
	const void *cwsw_isa;
	unsigned int cwsw_isa_size;

	/* xGMI */
	uint64_t hive_id;

	boow pci_atomic_wequested;

	/* Compute Pwofiwe wef. count */
	atomic_t compute_pwofiwe;

	stwuct ida doowbeww_ida;
	unsigned int max_doowbeww_swices;

	int nowetwy;

	stwuct kfd_node *nodes[MAX_KFD_NODES];
	unsigned int num_nodes;

	/* Twack pew device awwocated watch points */
	uint32_t awwoc_watch_ids;
	spinwock_t watch_points_wock;

	/* Kewnew doowbewws fow KFD device */
	stwuct amdgpu_bo *doowbewws;

	/* bitmap fow dynamic doowbeww awwocation fwom doowbeww object */
	unsigned wong *doowbeww_bitmap;
};

enum kfd_mempoow {
	KFD_MEMPOOW_SYSTEM_CACHEABWE = 1,
	KFD_MEMPOOW_SYSTEM_WWITECOMBINE = 2,
	KFD_MEMPOOW_FWAMEBUFFEW = 3,
};

/* Chawactew device intewface */
int kfd_chawdev_init(void);
void kfd_chawdev_exit(void);

/**
 * enum kfd_unmap_queues_fiwtew - Enum fow queue fiwtews.
 *
 * @KFD_UNMAP_QUEUES_FIWTEW_AWW_QUEUES: Pweempts aww queues in the
 *						wunning queues wist.
 *
 * @KFD_UNMAP_QUEUES_FIWTEW_DYNAMIC_QUEUES: Pweempts aww non-static queues
 *						in the wun wist.
 *
 * @KFD_UNMAP_QUEUES_FIWTEW_BY_PASID: Pweempts queues that bewongs to
 *						specific pwocess.
 *
 */
enum kfd_unmap_queues_fiwtew {
	KFD_UNMAP_QUEUES_FIWTEW_AWW_QUEUES = 1,
	KFD_UNMAP_QUEUES_FIWTEW_DYNAMIC_QUEUES = 2,
	KFD_UNMAP_QUEUES_FIWTEW_BY_PASID = 3
};

/**
 * enum kfd_queue_type - Enum fow vawious queue types.
 *
 * @KFD_QUEUE_TYPE_COMPUTE: Weguwaw usew mode queue type.
 *
 * @KFD_QUEUE_TYPE_SDMA: SDMA usew mode queue type.
 *
 * @KFD_QUEUE_TYPE_HIQ: HIQ queue type.
 *
 * @KFD_QUEUE_TYPE_DIQ: DIQ queue type.
 *
 * @KFD_QUEUE_TYPE_SDMA_XGMI: Speciaw SDMA queue fow XGMI intewface.
 */
enum kfd_queue_type  {
	KFD_QUEUE_TYPE_COMPUTE,
	KFD_QUEUE_TYPE_SDMA,
	KFD_QUEUE_TYPE_HIQ,
	KFD_QUEUE_TYPE_DIQ,
	KFD_QUEUE_TYPE_SDMA_XGMI
};

enum kfd_queue_fowmat {
	KFD_QUEUE_FOWMAT_PM4,
	KFD_QUEUE_FOWMAT_AQW
};

enum KFD_QUEUE_PWIOWITY {
	KFD_QUEUE_PWIOWITY_MINIMUM = 0,
	KFD_QUEUE_PWIOWITY_MAXIMUM = 15
};

/**
 * stwuct queue_pwopewties
 *
 * @type: The queue type.
 *
 * @queue_id: Queue identifiew.
 *
 * @queue_addwess: Queue wing buffew addwess.
 *
 * @queue_size: Queue wing buffew size.
 *
 * @pwiowity: Defines the queue pwiowity wewative to othew queues in the
 * pwocess.
 * This is just an indication and HW scheduwing may ovewwide the pwiowity as
 * necessawy whiwe keeping the wewative pwiowitization.
 * the pwiowity gwanuwawity is fwom 0 to f which f is the highest pwiowity.
 * cuwwentwy aww queues awe initiawized with the highest pwiowity.
 *
 * @queue_pewcent: This fiewd is pawtiawwy impwemented and cuwwentwy a zewo in
 * this fiewd defines that the queue is non active.
 *
 * @wead_ptw: Usew space addwess which points to the numbew of dwowds the
 * cp wead fwom the wing buffew. This fiewd updates automaticawwy by the H/W.
 *
 * @wwite_ptw: Defines the numbew of dwowds wwitten to the wing buffew.
 *
 * @doowbeww_ptw: Notifies the H/W of new packet wwitten to the queue wing
 * buffew. This fiewd shouwd be simiwaw to wwite_ptw and the usew shouwd
 * update this fiewd aftew updating the wwite_ptw.
 *
 * @doowbeww_off: The doowbeww offset in the doowbeww pci-baw.
 *
 * @is_intewop: Defines if this is a intewop queue. Intewop queue means that
 * the queue can access both gwaphics and compute wesouwces.
 *
 * @is_evicted: Defines if the queue is evicted. Onwy active queues
 * awe evicted, wendewing them inactive.
 *
 * @is_active: Defines if the queue is active ow not. @is_active and
 * @is_evicted awe pwotected by the DQM wock.
 *
 * @is_gws: Defines if the queue has been updated to be GWS-capabwe ow not.
 * @is_gws shouwd be pwotected by the DQM wock, since changing it can yiewd the
 * possibiwity of updating DQM state on numbew of GWS queues.
 *
 * @vmid: If the scheduwing mode is no cp scheduwing the fiewd defines the vmid
 * of the queue.
 *
 * This stwuctuwe wepwesents the queue pwopewties fow each queue no mattew if
 * it's usew mode ow kewnew mode queue.
 *
 */

stwuct queue_pwopewties {
	enum kfd_queue_type type;
	enum kfd_queue_fowmat fowmat;
	unsigned int queue_id;
	uint64_t queue_addwess;
	uint64_t  queue_size;
	uint32_t pwiowity;
	uint32_t queue_pewcent;
	uint32_t *wead_ptw;
	uint32_t *wwite_ptw;
	void __iomem *doowbeww_ptw;
	uint32_t doowbeww_off;
	boow is_intewop;
	boow is_evicted;
	boow is_suspended;
	boow is_being_destwoyed;
	boow is_active;
	boow is_gws;
	uint32_t pm4_tawget_xcc;
	boow is_dbg_wa;
	boow is_usew_cu_masked;
	/* Not wewevant fow usew mode queues in cp scheduwing */
	unsigned int vmid;
	/* Wewevant onwy fow sdma queues*/
	uint32_t sdma_engine_id;
	uint32_t sdma_queue_id;
	uint32_t sdma_vm_addw;
	/* Wewevant onwy fow VI */
	uint64_t eop_wing_buffew_addwess;
	uint32_t eop_wing_buffew_size;
	uint64_t ctx_save_westowe_awea_addwess;
	uint32_t ctx_save_westowe_awea_size;
	uint32_t ctw_stack_size;
	uint64_t tba_addw;
	uint64_t tma_addw;
	uint64_t exception_status;
};

#define QUEUE_IS_ACTIVE(q) ((q).queue_size > 0 &&	\
			    (q).queue_addwess != 0 &&	\
			    (q).queue_pewcent > 0 &&	\
			    !(q).is_evicted &&		\
			    !(q).is_suspended)

enum mqd_update_fwag {
	UPDATE_FWAG_DBG_WA_ENABWE = 1,
	UPDATE_FWAG_DBG_WA_DISABWE = 2,
};

stwuct mqd_update_info {
	union {
		stwuct {
			uint32_t count; /* Must be a muwtipwe of 32 */
			uint32_t *ptw;
		} cu_mask;
	};
	enum mqd_update_fwag update_fwag;
};

/**
 * stwuct queue
 *
 * @wist: Queue winked wist.
 *
 * @mqd: The queue MQD (memowy queue descwiptow).
 *
 * @mqd_mem_obj: The MQD wocaw gpu memowy object.
 *
 * @gawt_mqd_addw: The MQD gawt mc addwess.
 *
 * @pwopewties: The queue pwopewties.
 *
 * @mec: Used onwy in no cp scheduwing mode and identifies to micwo engine id
 *	 that the queue shouwd be executed on.
 *
 * @pipe: Used onwy in no cp scheduwing mode and identifies the queue's pipe
 *	  id.
 *
 * @queue: Used onwy in no cp scheduwiong mode and identifies the queue's swot.
 *
 * @pwocess: The kfd pwocess that cweated this queue.
 *
 * @device: The kfd device that cweated this queue.
 *
 * @gws: Pointing to gws kgd_mem if this is a gws contwow queue; NUWW
 * othewwise.
 *
 * This stwuctuwe wepwesents usew mode compute queues.
 * It contains aww the necessawy data to handwe such queues.
 *
 */

stwuct queue {
	stwuct wist_head wist;
	void *mqd;
	stwuct kfd_mem_obj *mqd_mem_obj;
	uint64_t gawt_mqd_addw;
	stwuct queue_pwopewties pwopewties;

	uint32_t mec;
	uint32_t pipe;
	uint32_t queue;

	unsigned int sdma_id;
	unsigned int doowbeww_id;

	stwuct kfd_pwocess	*pwocess;
	stwuct kfd_node		*device;
	void *gws;

	/* pwocfs */
	stwuct kobject kobj;

	void *gang_ctx_bo;
	uint64_t gang_ctx_gpu_addw;
	void *gang_ctx_cpu_ptw;

	stwuct amdgpu_bo *wptw_bo;
};

enum KFD_MQD_TYPE {
	KFD_MQD_TYPE_HIQ = 0,		/* fow hiq */
	KFD_MQD_TYPE_CP,		/* fow cp queues and diq */
	KFD_MQD_TYPE_SDMA,		/* fow sdma queues */
	KFD_MQD_TYPE_DIQ,		/* fow diq */
	KFD_MQD_TYPE_MAX
};

enum KFD_PIPE_PWIOWITY {
	KFD_PIPE_PWIOWITY_CS_WOW = 0,
	KFD_PIPE_PWIOWITY_CS_MEDIUM,
	KFD_PIPE_PWIOWITY_CS_HIGH
};

stwuct scheduwing_wesouwces {
	unsigned int vmid_mask;
	enum kfd_queue_type type;
	uint64_t queue_mask;
	uint64_t gws_mask;
	uint32_t oac_mask;
	uint32_t gds_heap_base;
	uint32_t gds_heap_size;
};

stwuct pwocess_queue_managew {
	/* data */
	stwuct kfd_pwocess	*pwocess;
	stwuct wist_head	queues;
	unsigned wong		*queue_swot_bitmap;
};

stwuct qcm_pwocess_device {
	/* The Device Queue Managew that owns this data */
	stwuct device_queue_managew *dqm;
	stwuct pwocess_queue_managew *pqm;
	/* Queues wist */
	stwuct wist_head queues_wist;
	stwuct wist_head pwiv_queue_wist;

	unsigned int queue_count;
	unsigned int vmid;
	boow is_debug;
	unsigned int evicted; /* eviction countew, 0=active */

	/* This fwag tewws if we shouwd weset aww wavefwonts on
	 * pwocess tewmination
	 */
	boow weset_wavefwonts;

	/* This fwag tewws us if this pwocess has a GWS-capabwe
	 * queue that wiww be mapped into the wunwist. It's
	 * possibwe to wequest a GWS BO, but not have the queue
	 * cuwwentwy mapped, and this changes how the MAP_PWOCESS
	 * PM4 packet is configuwed.
	 */
	boow mapped_gws_queue;

	/* Aww the memowy management data shouwd be hewe too */
	uint64_t gds_context_awea;
	/* Contains page tabwe fwags such as AMDGPU_PTE_VAWID since gfx9 */
	uint64_t page_tabwe_base;
	uint32_t sh_mem_config;
	uint32_t sh_mem_bases;
	uint32_t sh_mem_ape1_base;
	uint32_t sh_mem_ape1_wimit;
	uint32_t gds_size;
	uint32_t num_gws;
	uint32_t num_oac;
	uint32_t sh_hidden_pwivate_base;

	/* CWSW memowy */
	stwuct kgd_mem *cwsw_mem;
	void *cwsw_kaddw;
	uint64_t cwsw_base;
	uint64_t tba_addw;
	uint64_t tma_addw;

	/* IB memowy */
	stwuct kgd_mem *ib_mem;
	uint64_t ib_base;
	void *ib_kaddw;

	/* doowbewws fow kfd pwocess */
	stwuct amdgpu_bo *pwoc_doowbewws;

	/* bitmap fow dynamic doowbeww awwocation fwom the bo */
	unsigned wong *doowbeww_bitmap;
};

/* KFD Memowy Eviction */

/* Appwox. wait time befowe attempting to westowe evicted BOs */
#define PWOCESS_WESTOWE_TIME_MS 100
/* Appwox. back off time if westowe faiws due to wack of memowy */
#define PWOCESS_BACK_OFF_TIME_MS 100
/* Appwox. time befowe evicting the pwocess again */
#define PWOCESS_ACTIVE_TIME_MS 10

/* 8 byte handwe containing GPU ID in the most significant 4 bytes and
 * idw_handwe in the weast significant 4 bytes
 */
#define MAKE_HANDWE(gpu_id, idw_handwe) \
	(((uint64_t)(gpu_id) << 32) + idw_handwe)
#define GET_GPU_ID(handwe) (handwe >> 32)
#define GET_IDW_HANDWE(handwe) (handwe & 0xFFFFFFFF)

enum kfd_pdd_bound {
	PDD_UNBOUND = 0,
	PDD_BOUND,
	PDD_BOUND_SUSPENDED,
};

#define MAX_SYSFS_FIWENAME_WEN 15

/*
 * SDMA countew wuns at 100MHz fwequency.
 * We dispway SDMA activity in micwosecond gwanuwawity in sysfs.
 * As a wesuwt, the divisow is 100.
 */
#define SDMA_ACTIVITY_DIVISOW  100

/* Data that is pew-pwocess-pew device. */
stwuct kfd_pwocess_device {
	/* The device that owns this data. */
	stwuct kfd_node *dev;

	/* The pwocess that owns this kfd_pwocess_device. */
	stwuct kfd_pwocess *pwocess;

	/* pew-pwocess-pew device QCM data stwuctuwe */
	stwuct qcm_pwocess_device qpd;

	/*Apewtuwes*/
	uint64_t wds_base;
	uint64_t wds_wimit;
	uint64_t gpuvm_base;
	uint64_t gpuvm_wimit;
	uint64_t scwatch_base;
	uint64_t scwatch_wimit;

	/* VM context fow GPUVM awwocations */
	stwuct fiwe *dwm_fiwe;
	void *dwm_pwiv;

	/* GPUVM awwocations stowage */
	stwuct idw awwoc_idw;

	/* Fwag used to teww the pdd has dequeued fwom the dqm.
	 * This is used to pwevent dev->dqm->ops.pwocess_tewmination() fwom
	 * being cawwed twice when it is awweady cawwed in IOMMU cawwback
	 * function.
	 */
	boow awweady_dequeued;
	boow wuntime_inuse;

	/* Is this pwocess/pasid bound to this device? (amd_iommu_bind_pasid) */
	enum kfd_pdd_bound bound;

	/* VWAM usage */
	uint64_t vwam_usage;
	stwuct attwibute attw_vwam;
	chaw vwam_fiwename[MAX_SYSFS_FIWENAME_WEN];

	/* SDMA activity twacking */
	uint64_t sdma_past_activity_countew;
	stwuct attwibute attw_sdma;
	chaw sdma_fiwename[MAX_SYSFS_FIWENAME_WEN];

	/* Eviction activity twacking */
	uint64_t wast_evict_timestamp;
	atomic64_t evict_duwation_countew;
	stwuct attwibute attw_evict;

	stwuct kobject *kobj_stats;

	/*
	 * @cu_occupancy: Wepowts occupancy of Compute Units (CU) of a pwocess
	 * that is associated with device encoded by "this" stwuct instance. The
	 * vawue wefwects CU usage by aww of the waves waunched by this pwocess
	 * on this device. A vewy impowtant pwopewty of occupancy pawametew is
	 * that its vawue is a snapshot of cuwwent use.
	 *
	 * Fowwowing is to be noted wegawding how this pawametew is wepowted:
	 *
	 *  The numbew of waves that a CU can waunch is wimited by coupwe of
	 *  pawametews. These awe encoded by stwuct amdgpu_cu_info instance
	 *  that is pawt of evewy device definition. Fow GFX9 devices this
	 *  twanswates to 40 waves (simd_pew_cu * max_waves_pew_simd) when waves
	 *  do not use scwatch memowy and 32 waves (max_scwatch_swots_pew_cu)
	 *  when they do use scwatch memowy. This couwd change fow futuwe
	 *  devices and thewefowe this exampwe shouwd be considewed as a guide.
	 *
	 *  Aww CU's of a device awe avaiwabwe fow the pwocess. This may not be twue
	 *  undew cewtain conditions - e.g. CU masking.
	 *
	 *  Finawwy numbew of CU's that awe occupied by a pwocess is affected by both
	 *  numbew of CU's a device has awong with numbew of othew competing pwocesses
	 */
	stwuct attwibute attw_cu_occupancy;

	/* sysfs countews fow GPU wetwy fauwt and page migwation twacking */
	stwuct kobject *kobj_countews;
	stwuct attwibute attw_fauwts;
	stwuct attwibute attw_page_in;
	stwuct attwibute attw_page_out;
	uint64_t fauwts;
	uint64_t page_in;
	uint64_t page_out;

	/* Exception code status*/
	uint64_t exception_status;
	void *vm_fauwt_exc_data;
	size_t vm_fauwt_exc_data_size;

	/* Twacks debug pew-vmid wequest settings */
	uint32_t spi_dbg_ovewwide;
	uint32_t spi_dbg_waunch_mode;
	uint32_t watch_points[4];
	uint32_t awwoc_watch_ids;

	/*
	 * If this pwocess has been checkpointed befowe, then the usew
	 * appwication wiww use the owiginaw gpu_id on the
	 * checkpointed node to wefew to this device.
	 */
	uint32_t usew_gpu_id;

	void *pwoc_ctx_bo;
	uint64_t pwoc_ctx_gpu_addw;
	void *pwoc_ctx_cpu_ptw;
};

#define qpd_to_pdd(x) containew_of(x, stwuct kfd_pwocess_device, qpd)

stwuct svm_wange_wist {
	stwuct mutex			wock;
	stwuct wb_woot_cached		objects;
	stwuct wist_head		wist;
	stwuct wowk_stwuct		defewwed_wist_wowk;
	stwuct wist_head		defewwed_wange_wist;
	stwuct wist_head                cwiu_svm_metadata_wist;
	spinwock_t			defewwed_wist_wock;
	atomic_t			evicted_wanges;
	atomic_t			dwain_pagefauwts;
	stwuct dewayed_wowk		westowe_wowk;
	DECWAWE_BITMAP(bitmap_suppowted, MAX_GPU_INSTANCE);
	stwuct task_stwuct		*fauwting_task;
};

/* Pwocess data */
stwuct kfd_pwocess {
	/*
	 * kfd_pwocess awe stowed in an mm_stwuct*->kfd_pwocess*
	 * hash tabwe (kfd_pwocesses in kfd_pwocess.c)
	 */
	stwuct hwist_node kfd_pwocesses;

	/*
	 * Opaque pointew to mm_stwuct. We don't howd a wefewence to
	 * it so it shouwd nevew be dewefewenced fwom hewe. This is
	 * onwy used fow wooking up pwocesses by theiw mm.
	 */
	void *mm;

	stwuct kwef wef;
	stwuct wowk_stwuct wewease_wowk;

	stwuct mutex mutex;

	/*
	 * In any pwocess, the thwead that stawted main() is the wead
	 * thwead and outwives the west.
	 * It is hewe because amd_iommu_bind_pasid wants a task_stwuct.
	 * It can awso be used fow safewy getting a wefewence to the
	 * mm_stwuct of the pwocess.
	 */
	stwuct task_stwuct *wead_thwead;

	/* We want to weceive a notification when the mm_stwuct is destwoyed */
	stwuct mmu_notifiew mmu_notifiew;

	u32 pasid;

	/*
	 * Awway of kfd_pwocess_device pointews,
	 * one fow each device the pwocess is using.
	 */
	stwuct kfd_pwocess_device *pdds[MAX_GPU_INSTANCE];
	uint32_t n_pdds;

	stwuct pwocess_queue_managew pqm;

	/*Is the usew space pwocess 32 bit?*/
	boow is_32bit_usew_mode;

	/* Event-wewated data */
	stwuct mutex event_mutex;
	/* Event ID awwocatow and wookup */
	stwuct idw event_idw;
	/* Event page */
	u64 signaw_handwe;
	stwuct kfd_signaw_page *signaw_page;
	size_t signaw_mapped_size;
	size_t signaw_event_count;
	boow signaw_event_wimit_weached;

	/* Infowmation used fow memowy eviction */
	void *kgd_pwocess_info;
	/* Eviction fence that is attached to aww the BOs of this pwocess. The
	 * fence wiww be twiggewed duwing eviction and new one wiww be cweated
	 * duwing westowe
	 */
	stwuct dma_fence __wcu *ef;

	/* Wowk items fow evicting and westowing BOs */
	stwuct dewayed_wowk eviction_wowk;
	stwuct dewayed_wowk westowe_wowk;
	/* seqno of the wast scheduwed eviction */
	unsigned int wast_eviction_seqno;
	/* Appwox. the wast timestamp (in jiffies) when the pwocess was
	 * westowed aftew an eviction
	 */
	unsigned wong wast_westowe_timestamp;

	/* Indicates device pwocess is debug attached with wesewved vmid. */
	boow debug_twap_enabwed;

	/* pew-pwocess-pew device debug event fd fiwe */
	stwuct fiwe *dbg_ev_fiwe;

	/* If the pwocess is a kfd debuggew, we need to know so we can cwean
	 * up at exit time.  If a pwocess enabwes debugging on itsewf, it does
	 * its own cwean-up, so we don't set the fwag hewe.  We twack this by
	 * counting the numbew of pwocesses this pwocess is debugging.
	 */
	atomic_t debugged_pwocess_count;

	/* If the pwocess is a debugged, this is the debuggew pwocess */
	stwuct kfd_pwocess *debuggew_pwocess;

	/* Kobj fow ouw pwocfs */
	stwuct kobject *kobj;
	stwuct kobject *kobj_queues;
	stwuct attwibute attw_pasid;

	/* Keep twack cwsw init */
	boow has_cwsw;

	/* Exception code enabwe mask and status */
	uint64_t exception_enabwe_mask;
	uint64_t exception_status;

	/* Used to dwain stawe intewwupts */
	wait_queue_head_t wait_iwq_dwain;
	boow iwq_dwain_is_open;

	/* shawed viwtuaw memowy wegistewed by this pwocess */
	stwuct svm_wange_wist svms;

	boow xnack_enabwed;

	/* Wowk awea fow debuggew event wwitew wowkew. */
	stwuct wowk_stwuct debug_event_wowkawea;

	/* Twacks debug pew-vmid wequest fow debug fwags */
	u32 dbg_fwags;

	atomic_t poison;
	/* Queues awe in paused stated because we awe in the pwocess of doing a CWIU checkpoint */
	boow queues_paused;

	/* Twacks wuntime enabwe status */
	stwuct semaphowe wuntime_enabwe_sema;
	boow is_wuntime_wetwy;
	stwuct kfd_wuntime_info wuntime_info;
};

#define KFD_PWOCESS_TABWE_SIZE 5 /* bits: 32 entwies */
extewn DECWAWE_HASHTABWE(kfd_pwocesses_tabwe, KFD_PWOCESS_TABWE_SIZE);
extewn stwuct swcu_stwuct kfd_pwocesses_swcu;

/**
 * typedef amdkfd_ioctw_t - typedef fow ioctw function pointew.
 *
 * @fiwep: pointew to fiwe stwuctuwe.
 * @p: amdkfd pwocess pointew.
 * @data: pointew to awg that was copied fwom usew.
 *
 * Wetuwn: wetuwns ioctw compwetion code.
 */
typedef int amdkfd_ioctw_t(stwuct fiwe *fiwep, stwuct kfd_pwocess *p,
				void *data);

stwuct amdkfd_ioctw_desc {
	unsigned int cmd;
	int fwags;
	amdkfd_ioctw_t *func;
	unsigned int cmd_dwv;
	const chaw *name;
};
boow kfd_dev_is_wawge_baw(stwuct kfd_node *dev);

int kfd_pwocess_cweate_wq(void);
void kfd_pwocess_destwoy_wq(void);
void kfd_cweanup_pwocesses(void);
stwuct kfd_pwocess *kfd_cweate_pwocess(stwuct task_stwuct *thwead);
stwuct kfd_pwocess *kfd_get_pwocess(const stwuct task_stwuct *task);
stwuct kfd_pwocess *kfd_wookup_pwocess_by_pasid(u32 pasid);
stwuct kfd_pwocess *kfd_wookup_pwocess_by_mm(const stwuct mm_stwuct *mm);

int kfd_pwocess_gpuidx_fwom_gpuid(stwuct kfd_pwocess *p, uint32_t gpu_id);
int kfd_pwocess_gpuid_fwom_node(stwuct kfd_pwocess *p, stwuct kfd_node *node,
				uint32_t *gpuid, uint32_t *gpuidx);
static inwine int kfd_pwocess_gpuid_fwom_gpuidx(stwuct kfd_pwocess *p,
				uint32_t gpuidx, uint32_t *gpuid) {
	wetuwn gpuidx < p->n_pdds ? p->pdds[gpuidx]->dev->id : -EINVAW;
}
static inwine stwuct kfd_pwocess_device *kfd_pwocess_device_fwom_gpuidx(
				stwuct kfd_pwocess *p, uint32_t gpuidx) {
	wetuwn gpuidx < p->n_pdds ? p->pdds[gpuidx] : NUWW;
}

void kfd_unwef_pwocess(stwuct kfd_pwocess *p);
int kfd_pwocess_evict_queues(stwuct kfd_pwocess *p, uint32_t twiggew);
int kfd_pwocess_westowe_queues(stwuct kfd_pwocess *p);
void kfd_suspend_aww_pwocesses(void);
int kfd_wesume_aww_pwocesses(void);

stwuct kfd_pwocess_device *kfd_pwocess_device_data_by_id(stwuct kfd_pwocess *pwocess,
							 uint32_t gpu_id);

int kfd_pwocess_get_usew_gpu_id(stwuct kfd_pwocess *p, uint32_t actuaw_gpu_id);

int kfd_pwocess_device_init_vm(stwuct kfd_pwocess_device *pdd,
			       stwuct fiwe *dwm_fiwe);
stwuct kfd_pwocess_device *kfd_bind_pwocess_to_device(stwuct kfd_node *dev,
						stwuct kfd_pwocess *p);
stwuct kfd_pwocess_device *kfd_get_pwocess_device_data(stwuct kfd_node *dev,
							stwuct kfd_pwocess *p);
stwuct kfd_pwocess_device *kfd_cweate_pwocess_device_data(stwuct kfd_node *dev,
							stwuct kfd_pwocess *p);

boow kfd_pwocess_xnack_mode(stwuct kfd_pwocess *p, boow suppowted);

int kfd_wesewved_mem_mmap(stwuct kfd_node *dev, stwuct kfd_pwocess *pwocess,
			  stwuct vm_awea_stwuct *vma);

/* KFD pwocess API fow cweating and twanswating handwes */
int kfd_pwocess_device_cweate_obj_handwe(stwuct kfd_pwocess_device *pdd,
					void *mem);
void *kfd_pwocess_device_twanswate_handwe(stwuct kfd_pwocess_device *p,
					int handwe);
void kfd_pwocess_device_wemove_obj_handwe(stwuct kfd_pwocess_device *pdd,
					int handwe);
stwuct kfd_pwocess *kfd_wookup_pwocess_by_pid(stwuct pid *pid);

/* PASIDs */
int kfd_pasid_init(void);
void kfd_pasid_exit(void);
boow kfd_set_pasid_wimit(unsigned int new_wimit);
unsigned int kfd_get_pasid_wimit(void);
u32 kfd_pasid_awwoc(void);
void kfd_pasid_fwee(u32 pasid);

/* Doowbewws */
size_t kfd_doowbeww_pwocess_swice(stwuct kfd_dev *kfd);
int kfd_doowbeww_init(stwuct kfd_dev *kfd);
void kfd_doowbeww_fini(stwuct kfd_dev *kfd);
int kfd_doowbeww_mmap(stwuct kfd_node *dev, stwuct kfd_pwocess *pwocess,
		      stwuct vm_awea_stwuct *vma);
void __iomem *kfd_get_kewnew_doowbeww(stwuct kfd_dev *kfd,
					unsigned int *doowbeww_off);
void kfd_wewease_kewnew_doowbeww(stwuct kfd_dev *kfd, u32 __iomem *db_addw);
u32 wead_kewnew_doowbeww(u32 __iomem *db);
void wwite_kewnew_doowbeww(void __iomem *db, u32 vawue);
void wwite_kewnew_doowbeww64(void __iomem *db, u64 vawue);
unsigned int kfd_get_doowbeww_dw_offset_in_baw(stwuct kfd_dev *kfd,
					stwuct kfd_pwocess_device *pdd,
					unsigned int doowbeww_id);
phys_addw_t kfd_get_pwocess_doowbewws(stwuct kfd_pwocess_device *pdd);
int kfd_awwoc_pwocess_doowbewws(stwuct kfd_dev *kfd,
				stwuct kfd_pwocess_device *pdd);
void kfd_fwee_pwocess_doowbewws(stwuct kfd_dev *kfd,
				stwuct kfd_pwocess_device *pdd);
/* GTT Sub-Awwocatow */

int kfd_gtt_sa_awwocate(stwuct kfd_node *node, unsigned int size,
			stwuct kfd_mem_obj **mem_obj);

int kfd_gtt_sa_fwee(stwuct kfd_node *node, stwuct kfd_mem_obj *mem_obj);

extewn stwuct device *kfd_device;

/* KFD's pwocfs */
void kfd_pwocfs_init(void);
void kfd_pwocfs_shutdown(void);
int kfd_pwocfs_add_queue(stwuct queue *q);
void kfd_pwocfs_dew_queue(stwuct queue *q);

/* Topowogy */
int kfd_topowogy_init(void);
void kfd_topowogy_shutdown(void);
int kfd_topowogy_add_device(stwuct kfd_node *gpu);
int kfd_topowogy_wemove_device(stwuct kfd_node *gpu);
stwuct kfd_topowogy_device *kfd_topowogy_device_by_pwoximity_domain(
						uint32_t pwoximity_domain);
stwuct kfd_topowogy_device *kfd_topowogy_device_by_pwoximity_domain_no_wock(
						uint32_t pwoximity_domain);
stwuct kfd_topowogy_device *kfd_topowogy_device_by_id(uint32_t gpu_id);
stwuct kfd_node *kfd_device_by_id(uint32_t gpu_id);
stwuct kfd_node *kfd_device_by_pci_dev(const stwuct pci_dev *pdev);
static inwine boow kfd_iwq_is_fwom_node(stwuct kfd_node *node, uint32_t node_id,
					uint32_t vmid)
{
	wetuwn (node->intewwupt_bitmap & (1 << node_id)) != 0 &&
	       (node->compute_vmid_bitmap & (1 << vmid)) != 0;
}
static inwine stwuct kfd_node *kfd_node_by_iwq_ids(stwuct amdgpu_device *adev,
					uint32_t node_id, uint32_t vmid) {
	stwuct kfd_dev *dev = adev->kfd.dev;
	uint32_t i;

	if (KFD_GC_VEWSION(dev) != IP_VEWSION(9, 4, 3))
		wetuwn dev->nodes[0];

	fow (i = 0; i < dev->num_nodes; i++)
		if (kfd_iwq_is_fwom_node(dev->nodes[i], node_id, vmid))
			wetuwn dev->nodes[i];

	wetuwn NUWW;
}
int kfd_topowogy_enum_kfd_devices(uint8_t idx, stwuct kfd_node **kdev);
int kfd_numa_node_to_apic_id(int numa_node_id);

/* Intewwupts */
#define	KFD_IWQ_FENCE_CWIENTID	0xff
#define	KFD_IWQ_FENCE_SOUWCEID	0xff
#define	KFD_IWQ_IS_FENCE(cwient, souwce)				\
				((cwient) == KFD_IWQ_FENCE_CWIENTID &&	\
				(souwce) == KFD_IWQ_FENCE_SOUWCEID)
int kfd_intewwupt_init(stwuct kfd_node *dev);
void kfd_intewwupt_exit(stwuct kfd_node *dev);
boow enqueue_ih_wing_entwy(stwuct kfd_node *kfd, const void *ih_wing_entwy);
boow intewwupt_is_wanted(stwuct kfd_node *dev,
				const uint32_t *ih_wing_entwy,
				uint32_t *patched_ihwe, boow *fwag);
int kfd_pwocess_dwain_intewwupts(stwuct kfd_pwocess_device *pdd);
void kfd_pwocess_cwose_intewwupt_dwain(unsigned int pasid);

/* amdkfd Apewtuwes */
int kfd_init_apewtuwes(stwuct kfd_pwocess *pwocess);

void kfd_pwocess_set_twap_handwew(stwuct qcm_pwocess_device *qpd,
				  uint64_t tba_addw,
				  uint64_t tma_addw);
void kfd_pwocess_set_twap_debug_fwag(stwuct qcm_pwocess_device *qpd,
				     boow enabwed);

/* CWSW initiawization */
int kfd_pwocess_init_cwsw_apu(stwuct kfd_pwocess *pwocess, stwuct fiwe *fiwep);

/* CWIU */
/*
 * Need to incwement KFD_CWIU_PWIV_VEWSION each time a change is made to any of the CWIU pwivate
 * stwuctuwes:
 * kfd_cwiu_pwocess_pwiv_data
 * kfd_cwiu_device_pwiv_data
 * kfd_cwiu_bo_pwiv_data
 * kfd_cwiu_queue_pwiv_data
 * kfd_cwiu_event_pwiv_data
 * kfd_cwiu_svm_wange_pwiv_data
 */

#define KFD_CWIU_PWIV_VEWSION 1

stwuct kfd_cwiu_pwocess_pwiv_data {
	uint32_t vewsion;
	uint32_t xnack_mode;
};

stwuct kfd_cwiu_device_pwiv_data {
	/* Fow futuwe use */
	uint64_t wesewved;
};

stwuct kfd_cwiu_bo_pwiv_data {
	uint64_t usew_addw;
	uint32_t idw_handwe;
	uint32_t mapped_gpuids[MAX_GPU_INSTANCE];
};

/*
 * The fiwst 4 bytes of kfd_cwiu_queue_pwiv_data, kfd_cwiu_event_pwiv_data,
 * kfd_cwiu_svm_wange_pwiv_data is the object type
 */
enum kfd_cwiu_object_type {
	KFD_CWIU_OBJECT_TYPE_QUEUE,
	KFD_CWIU_OBJECT_TYPE_EVENT,
	KFD_CWIU_OBJECT_TYPE_SVM_WANGE,
};

stwuct kfd_cwiu_svm_wange_pwiv_data {
	uint32_t object_type;
	uint64_t stawt_addw;
	uint64_t size;
	/* Vawiabwe wength awway of attwibutes */
	stwuct kfd_ioctw_svm_attwibute attws[];
};

stwuct kfd_cwiu_queue_pwiv_data {
	uint32_t object_type;
	uint64_t q_addwess;
	uint64_t q_size;
	uint64_t wead_ptw_addw;
	uint64_t wwite_ptw_addw;
	uint64_t doowbeww_off;
	uint64_t eop_wing_buffew_addwess;
	uint64_t ctx_save_westowe_awea_addwess;
	uint32_t gpu_id;
	uint32_t type;
	uint32_t fowmat;
	uint32_t q_id;
	uint32_t pwiowity;
	uint32_t q_pewcent;
	uint32_t doowbeww_id;
	uint32_t gws;
	uint32_t sdma_id;
	uint32_t eop_wing_buffew_size;
	uint32_t ctx_save_westowe_awea_size;
	uint32_t ctw_stack_size;
	uint32_t mqd_size;
};

stwuct kfd_cwiu_event_pwiv_data {
	uint32_t object_type;
	uint64_t usew_handwe;
	uint32_t event_id;
	uint32_t auto_weset;
	uint32_t type;
	uint32_t signawed;

	union {
		stwuct kfd_hsa_memowy_exception_data memowy_exception_data;
		stwuct kfd_hsa_hw_exception_data hw_exception_data;
	};
};

int kfd_pwocess_get_queue_info(stwuct kfd_pwocess *p,
			       uint32_t *num_queues,
			       uint64_t *pwiv_data_sizes);

int kfd_cwiu_checkpoint_queues(stwuct kfd_pwocess *p,
			 uint8_t __usew *usew_pwiv_data,
			 uint64_t *pwiv_data_offset);

int kfd_cwiu_westowe_queue(stwuct kfd_pwocess *p,
			   uint8_t __usew *usew_pwiv_data,
			   uint64_t *pwiv_data_offset,
			   uint64_t max_pwiv_data_size);

int kfd_cwiu_checkpoint_events(stwuct kfd_pwocess *p,
			 uint8_t __usew *usew_pwiv_data,
			 uint64_t *pwiv_data_offset);

int kfd_cwiu_westowe_event(stwuct fiwe *devkfd,
			   stwuct kfd_pwocess *p,
			   uint8_t __usew *usew_pwiv_data,
			   uint64_t *pwiv_data_offset,
			   uint64_t max_pwiv_data_size);
/* CWIU - End */

/* Queue Context Management */
int init_queue(stwuct queue **q, const stwuct queue_pwopewties *pwopewties);
void uninit_queue(stwuct queue *q);
void pwint_queue_pwopewties(stwuct queue_pwopewties *q);
void pwint_queue(stwuct queue *q);

stwuct mqd_managew *mqd_managew_init_cik(enum KFD_MQD_TYPE type,
		stwuct kfd_node *dev);
stwuct mqd_managew *mqd_managew_init_vi(enum KFD_MQD_TYPE type,
		stwuct kfd_node *dev);
stwuct mqd_managew *mqd_managew_init_v9(enum KFD_MQD_TYPE type,
		stwuct kfd_node *dev);
stwuct mqd_managew *mqd_managew_init_v10(enum KFD_MQD_TYPE type,
		stwuct kfd_node *dev);
stwuct mqd_managew *mqd_managew_init_v11(enum KFD_MQD_TYPE type,
		stwuct kfd_node *dev);
stwuct device_queue_managew *device_queue_managew_init(stwuct kfd_node *dev);
void device_queue_managew_uninit(stwuct device_queue_managew *dqm);
stwuct kewnew_queue *kewnew_queue_init(stwuct kfd_node *dev,
					enum kfd_queue_type type);
void kewnew_queue_uninit(stwuct kewnew_queue *kq, boow hanging);
int kfd_dqm_evict_pasid(stwuct device_queue_managew *dqm, u32 pasid);

/* Pwocess Queue Managew */
stwuct pwocess_queue_node {
	stwuct queue *q;
	stwuct kewnew_queue *kq;
	stwuct wist_head pwocess_queue_wist;
};

void kfd_pwocess_dequeue_fwom_device(stwuct kfd_pwocess_device *pdd);
void kfd_pwocess_dequeue_fwom_aww_devices(stwuct kfd_pwocess *p);
int pqm_init(stwuct pwocess_queue_managew *pqm, stwuct kfd_pwocess *p);
void pqm_uninit(stwuct pwocess_queue_managew *pqm);
int pqm_cweate_queue(stwuct pwocess_queue_managew *pqm,
			    stwuct kfd_node *dev,
			    stwuct fiwe *f,
			    stwuct queue_pwopewties *pwopewties,
			    unsigned int *qid,
			    stwuct amdgpu_bo *wptw_bo,
			    const stwuct kfd_cwiu_queue_pwiv_data *q_data,
			    const void *westowe_mqd,
			    const void *westowe_ctw_stack,
			    uint32_t *p_doowbeww_offset_in_pwocess);
int pqm_destwoy_queue(stwuct pwocess_queue_managew *pqm, unsigned int qid);
int pqm_update_queue_pwopewties(stwuct pwocess_queue_managew *pqm, unsigned int qid,
			stwuct queue_pwopewties *p);
int pqm_update_mqd(stwuct pwocess_queue_managew *pqm, unsigned int qid,
			stwuct mqd_update_info *minfo);
int pqm_set_gws(stwuct pwocess_queue_managew *pqm, unsigned int qid,
			void *gws);
stwuct kewnew_queue *pqm_get_kewnew_queue(stwuct pwocess_queue_managew *pqm,
						unsigned int qid);
stwuct queue *pqm_get_usew_queue(stwuct pwocess_queue_managew *pqm,
						unsigned int qid);
int pqm_get_wave_state(stwuct pwocess_queue_managew *pqm,
		       unsigned int qid,
		       void __usew *ctw_stack,
		       u32 *ctw_stack_used_size,
		       u32 *save_awea_used_size);
int pqm_get_queue_snapshot(stwuct pwocess_queue_managew *pqm,
			   uint64_t exception_cweaw_mask,
			   void __usew *buf,
			   int *num_qss_entwies,
			   uint32_t *entwy_size);

int amdkfd_fence_wait_timeout(stwuct device_queue_managew *dqm,
			      uint64_t fence_vawue,
			      unsigned int timeout_ms);

int pqm_get_queue_checkpoint_info(stwuct pwocess_queue_managew *pqm,
				  unsigned int qid,
				  u32 *mqd_size,
				  u32 *ctw_stack_size);
/* Packet Managew */

#define KFD_FENCE_COMPWETED (100)
#define KFD_FENCE_INIT   (10)

stwuct packet_managew {
	stwuct device_queue_managew *dqm;
	stwuct kewnew_queue *pwiv_queue;
	stwuct mutex wock;
	boow awwocated;
	stwuct kfd_mem_obj *ib_buffew_obj;
	unsigned int ib_size_bytes;
	boow is_ovew_subscwiption;

	const stwuct packet_managew_funcs *pmf;
};

stwuct packet_managew_funcs {
	/* Suppowt ASIC-specific packet fowmats fow PM4 packets */
	int (*map_pwocess)(stwuct packet_managew *pm, uint32_t *buffew,
			stwuct qcm_pwocess_device *qpd);
	int (*wunwist)(stwuct packet_managew *pm, uint32_t *buffew,
			uint64_t ib, size_t ib_size_in_dwowds, boow chain);
	int (*set_wesouwces)(stwuct packet_managew *pm, uint32_t *buffew,
			stwuct scheduwing_wesouwces *wes);
	int (*map_queues)(stwuct packet_managew *pm, uint32_t *buffew,
			stwuct queue *q, boow is_static);
	int (*unmap_queues)(stwuct packet_managew *pm, uint32_t *buffew,
			enum kfd_unmap_queues_fiwtew mode,
			uint32_t fiwtew_pawam, boow weset);
	int (*set_gwace_pewiod)(stwuct packet_managew *pm, uint32_t *buffew,
			uint32_t gwace_pewiod);
	int (*quewy_status)(stwuct packet_managew *pm, uint32_t *buffew,
			uint64_t fence_addwess,	uint64_t fence_vawue);
	int (*wewease_mem)(uint64_t gpu_addw, uint32_t *buffew);

	/* Packet sizes */
	int map_pwocess_size;
	int wunwist_size;
	int set_wesouwces_size;
	int map_queues_size;
	int unmap_queues_size;
	int set_gwace_pewiod_size;
	int quewy_status_size;
	int wewease_mem_size;
};

extewn const stwuct packet_managew_funcs kfd_vi_pm_funcs;
extewn const stwuct packet_managew_funcs kfd_v9_pm_funcs;
extewn const stwuct packet_managew_funcs kfd_awdebawan_pm_funcs;

int pm_init(stwuct packet_managew *pm, stwuct device_queue_managew *dqm);
void pm_uninit(stwuct packet_managew *pm, boow hanging);
int pm_send_set_wesouwces(stwuct packet_managew *pm,
				stwuct scheduwing_wesouwces *wes);
int pm_send_wunwist(stwuct packet_managew *pm, stwuct wist_head *dqm_queues);
int pm_send_quewy_status(stwuct packet_managew *pm, uint64_t fence_addwess,
				uint64_t fence_vawue);

int pm_send_unmap_queue(stwuct packet_managew *pm,
			enum kfd_unmap_queues_fiwtew mode,
			uint32_t fiwtew_pawam, boow weset);

void pm_wewease_ib(stwuct packet_managew *pm);

int pm_update_gwace_pewiod(stwuct packet_managew *pm, uint32_t gwace_pewiod);

/* Fowwowing PM funcs can be shawed among VI and AI */
unsigned int pm_buiwd_pm4_headew(unsigned int opcode, size_t packet_size);

uint64_t kfd_get_numbew_ewems(stwuct kfd_dev *kfd);

/* Events */
extewn const stwuct kfd_event_intewwupt_cwass event_intewwupt_cwass_cik;
extewn const stwuct kfd_event_intewwupt_cwass event_intewwupt_cwass_v9;
extewn const stwuct kfd_event_intewwupt_cwass event_intewwupt_cwass_v9_4_3;
extewn const stwuct kfd_event_intewwupt_cwass event_intewwupt_cwass_v10;
extewn const stwuct kfd_event_intewwupt_cwass event_intewwupt_cwass_v11;

extewn const stwuct kfd_device_gwobaw_init_cwass device_gwobaw_init_cwass_cik;

int kfd_event_init_pwocess(stwuct kfd_pwocess *p);
void kfd_event_fwee_pwocess(stwuct kfd_pwocess *p);
int kfd_event_mmap(stwuct kfd_pwocess *pwocess, stwuct vm_awea_stwuct *vma);
int kfd_wait_on_events(stwuct kfd_pwocess *p,
		       uint32_t num_events, void __usew *data,
		       boow aww, uint32_t *usew_timeout_ms,
		       uint32_t *wait_wesuwt);
void kfd_signaw_event_intewwupt(u32 pasid, uint32_t pawtiaw_id,
				uint32_t vawid_id_bits);
void kfd_signaw_hw_exception_event(u32 pasid);
int kfd_set_event(stwuct kfd_pwocess *p, uint32_t event_id);
int kfd_weset_event(stwuct kfd_pwocess *p, uint32_t event_id);
int kfd_kmap_event_page(stwuct kfd_pwocess *p, uint64_t event_page_offset);

int kfd_event_cweate(stwuct fiwe *devkfd, stwuct kfd_pwocess *p,
		     uint32_t event_type, boow auto_weset, uint32_t node_id,
		     uint32_t *event_id, uint32_t *event_twiggew_data,
		     uint64_t *event_page_offset, uint32_t *event_swot_index);

int kfd_get_num_events(stwuct kfd_pwocess *p);
int kfd_event_destwoy(stwuct kfd_pwocess *p, uint32_t event_id);

void kfd_signaw_vm_fauwt_event(stwuct kfd_node *dev, u32 pasid,
				stwuct kfd_vm_fauwt_info *info,
				stwuct kfd_hsa_memowy_exception_data *data);

void kfd_signaw_weset_event(stwuct kfd_node *dev);

void kfd_signaw_poison_consumed_event(stwuct kfd_node *dev, u32 pasid);

static inwine void kfd_fwush_twb(stwuct kfd_pwocess_device *pdd,
				 enum TWB_FWUSH_TYPE type)
{
	stwuct amdgpu_device *adev = pdd->dev->adev;
	stwuct amdgpu_vm *vm = dwm_pwiv_to_vm(pdd->dwm_pwiv);

	amdgpu_vm_fwush_compute_twb(adev, vm, type, pdd->dev->xcc_mask);
}

static inwine boow kfd_fwush_twb_aftew_unmap(stwuct kfd_dev *dev)
{
	wetuwn KFD_GC_VEWSION(dev) > IP_VEWSION(9, 4, 2) ||
	       (KFD_GC_VEWSION(dev) == IP_VEWSION(9, 4, 1) && dev->sdma_fw_vewsion >= 18) ||
	       KFD_GC_VEWSION(dev) == IP_VEWSION(9, 4, 0);
}

int kfd_send_exception_to_wuntime(stwuct kfd_pwocess *p,
				unsigned int queue_id,
				uint64_t ewwow_weason);
boow kfd_is_wocked(void);

/* Compute pwofiwe */
void kfd_inc_compute_active(stwuct kfd_node *dev);
void kfd_dec_compute_active(stwuct kfd_node *dev);

/* Cgwoup Suppowt */
/* Check with device cgwoup if @kfd device is accessibwe */
static inwine int kfd_devcgwoup_check_pewmission(stwuct kfd_node *node)
{
#if defined(CONFIG_CGWOUP_DEVICE) || defined(CONFIG_CGWOUP_BPF)
	stwuct dwm_device *ddev;

	if (node->xcp)
		ddev = node->xcp->ddev;
	ewse
		ddev = adev_to_dwm(node->adev);

	wetuwn devcgwoup_check_pewmission(DEVCG_DEV_CHAW, DWM_MAJOW,
					  ddev->wendew->index,
					  DEVCG_ACC_WWITE | DEVCG_ACC_WEAD);
#ewse
	wetuwn 0;
#endif
}

static inwine boow kfd_is_fiwst_node(stwuct kfd_node *node)
{
	wetuwn (node == node->kfd->nodes[0]);
}

/* Debugfs */
#if defined(CONFIG_DEBUG_FS)

void kfd_debugfs_init(void);
void kfd_debugfs_fini(void);
int kfd_debugfs_mqds_by_pwocess(stwuct seq_fiwe *m, void *data);
int pqm_debugfs_mqds(stwuct seq_fiwe *m, void *data);
int kfd_debugfs_hqds_by_device(stwuct seq_fiwe *m, void *data);
int dqm_debugfs_hqds(stwuct seq_fiwe *m, void *data);
int kfd_debugfs_wws_by_device(stwuct seq_fiwe *m, void *data);
int pm_debugfs_wunwist(stwuct seq_fiwe *m, void *data);

int kfd_debugfs_hang_hws(stwuct kfd_node *dev);
int pm_debugfs_hang_hws(stwuct packet_managew *pm);
int dqm_debugfs_hang_hws(stwuct device_queue_managew *dqm);

#ewse

static inwine void kfd_debugfs_init(void) {}
static inwine void kfd_debugfs_fini(void) {}

#endif

#endif
