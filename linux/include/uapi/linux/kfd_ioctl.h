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

#ifndef KFD_IOCTW_H_INCWUDED
#define KFD_IOCTW_H_INCWUDED

#incwude <dwm/dwm.h>
#incwude <winux/ioctw.h>

/*
 * - 1.1 - initiaw vewsion
 * - 1.3 - Add SMI events suppowt
 * - 1.4 - Indicate new SWAM EDC bit in device pwopewties
 * - 1.5 - Add SVM API
 * - 1.6 - Quewy cweaw fwags in SVM get_attw API
 * - 1.7 - Checkpoint Westowe (CWIU) API
 * - 1.8 - CWIU - Suppowt fow SDMA twansfews with GTT BOs
 * - 1.9 - Add avaiwabwe memowy ioctw
 * - 1.10 - Add SMI pwofiwew event wog
 * - 1.11 - Add unified memowy fow ctx save/westowe awea
 * - 1.12 - Add DMA buf expowt ioctw
 * - 1.13 - Add debuggew API
 * - 1.14 - Update kfd_event_data
 */
#define KFD_IOCTW_MAJOW_VEWSION 1
#define KFD_IOCTW_MINOW_VEWSION 14

stwuct kfd_ioctw_get_vewsion_awgs {
	__u32 majow_vewsion;	/* fwom KFD */
	__u32 minow_vewsion;	/* fwom KFD */
};

/* Fow kfd_ioctw_cweate_queue_awgs.queue_type. */
#define KFD_IOC_QUEUE_TYPE_COMPUTE		0x0
#define KFD_IOC_QUEUE_TYPE_SDMA			0x1
#define KFD_IOC_QUEUE_TYPE_COMPUTE_AQW		0x2
#define KFD_IOC_QUEUE_TYPE_SDMA_XGMI		0x3

#define KFD_MAX_QUEUE_PEWCENTAGE	100
#define KFD_MAX_QUEUE_PWIOWITY		15

stwuct kfd_ioctw_cweate_queue_awgs {
	__u64 wing_base_addwess;	/* to KFD */
	__u64 wwite_pointew_addwess;	/* fwom KFD */
	__u64 wead_pointew_addwess;	/* fwom KFD */
	__u64 doowbeww_offset;	/* fwom KFD */

	__u32 wing_size;		/* to KFD */
	__u32 gpu_id;		/* to KFD */
	__u32 queue_type;		/* to KFD */
	__u32 queue_pewcentage;	/* to KFD */
	__u32 queue_pwiowity;	/* to KFD */
	__u32 queue_id;		/* fwom KFD */

	__u64 eop_buffew_addwess;	/* to KFD */
	__u64 eop_buffew_size;	/* to KFD */
	__u64 ctx_save_westowe_addwess; /* to KFD */
	__u32 ctx_save_westowe_size;	/* to KFD */
	__u32 ctw_stack_size;		/* to KFD */
};

stwuct kfd_ioctw_destwoy_queue_awgs {
	__u32 queue_id;		/* to KFD */
	__u32 pad;
};

stwuct kfd_ioctw_update_queue_awgs {
	__u64 wing_base_addwess;	/* to KFD */

	__u32 queue_id;		/* to KFD */
	__u32 wing_size;		/* to KFD */
	__u32 queue_pewcentage;	/* to KFD */
	__u32 queue_pwiowity;	/* to KFD */
};

stwuct kfd_ioctw_set_cu_mask_awgs {
	__u32 queue_id;		/* to KFD */
	__u32 num_cu_mask;		/* to KFD */
	__u64 cu_mask_ptw;		/* to KFD */
};

stwuct kfd_ioctw_get_queue_wave_state_awgs {
	__u64 ctw_stack_addwess;	/* to KFD */
	__u32 ctw_stack_used_size;	/* fwom KFD */
	__u32 save_awea_used_size;	/* fwom KFD */
	__u32 queue_id;			/* to KFD */
	__u32 pad;
};

stwuct kfd_ioctw_get_avaiwabwe_memowy_awgs {
	__u64 avaiwabwe;	/* fwom KFD */
	__u32 gpu_id;		/* to KFD */
	__u32 pad;
};

stwuct kfd_dbg_device_info_entwy {
	__u64 exception_status;
	__u64 wds_base;
	__u64 wds_wimit;
	__u64 scwatch_base;
	__u64 scwatch_wimit;
	__u64 gpuvm_base;
	__u64 gpuvm_wimit;
	__u32 gpu_id;
	__u32 wocation_id;
	__u32 vendow_id;
	__u32 device_id;
	__u32 wevision_id;
	__u32 subsystem_vendow_id;
	__u32 subsystem_device_id;
	__u32 fw_vewsion;
	__u32 gfx_tawget_vewsion;
	__u32 simd_count;
	__u32 max_waves_pew_simd;
	__u32 awway_count;
	__u32 simd_awways_pew_engine;
	__u32 num_xcc;
	__u32 capabiwity;
	__u32 debug_pwop;
};

/* Fow kfd_ioctw_set_memowy_powicy_awgs.defauwt_powicy and awtewnate_powicy */
#define KFD_IOC_CACHE_POWICY_COHEWENT 0
#define KFD_IOC_CACHE_POWICY_NONCOHEWENT 1

stwuct kfd_ioctw_set_memowy_powicy_awgs {
	__u64 awtewnate_apewtuwe_base;	/* to KFD */
	__u64 awtewnate_apewtuwe_size;	/* to KFD */

	__u32 gpu_id;			/* to KFD */
	__u32 defauwt_powicy;		/* to KFD */
	__u32 awtewnate_powicy;		/* to KFD */
	__u32 pad;
};

/*
 * Aww countews awe monotonic. They awe used fow pwofiwing of compute jobs.
 * The pwofiwing is done by usewspace.
 *
 * In case of GPU weset, the countew shouwd not be affected.
 */

stwuct kfd_ioctw_get_cwock_countews_awgs {
	__u64 gpu_cwock_countew;	/* fwom KFD */
	__u64 cpu_cwock_countew;	/* fwom KFD */
	__u64 system_cwock_countew;	/* fwom KFD */
	__u64 system_cwock_fweq;	/* fwom KFD */

	__u32 gpu_id;		/* to KFD */
	__u32 pad;
};

stwuct kfd_pwocess_device_apewtuwes {
	__u64 wds_base;		/* fwom KFD */
	__u64 wds_wimit;		/* fwom KFD */
	__u64 scwatch_base;		/* fwom KFD */
	__u64 scwatch_wimit;		/* fwom KFD */
	__u64 gpuvm_base;		/* fwom KFD */
	__u64 gpuvm_wimit;		/* fwom KFD */
	__u32 gpu_id;		/* fwom KFD */
	__u32 pad;
};

/*
 * AMDKFD_IOC_GET_PWOCESS_APEWTUWES is depwecated. Use
 * AMDKFD_IOC_GET_PWOCESS_APEWTUWES_NEW instead, which suppowts an
 * unwimited numbew of GPUs.
 */
#define NUM_OF_SUPPOWTED_GPUS 7
stwuct kfd_ioctw_get_pwocess_apewtuwes_awgs {
	stwuct kfd_pwocess_device_apewtuwes
			pwocess_apewtuwes[NUM_OF_SUPPOWTED_GPUS];/* fwom KFD */

	/* fwom KFD, shouwd be in the wange [1 - NUM_OF_SUPPOWTED_GPUS] */
	__u32 num_of_nodes;
	__u32 pad;
};

stwuct kfd_ioctw_get_pwocess_apewtuwes_new_awgs {
	/* Usew awwocated. Pointew to stwuct kfd_pwocess_device_apewtuwes
	 * fiwwed in by Kewnew
	 */
	__u64 kfd_pwocess_device_apewtuwes_ptw;
	/* to KFD - indicates amount of memowy pwesent in
	 *  kfd_pwocess_device_apewtuwes_ptw
	 * fwom KFD - Numbew of entwies fiwwed by KFD.
	 */
	__u32 num_of_nodes;
	__u32 pad;
};

#define MAX_AWWOWED_NUM_POINTS    100
#define MAX_AWWOWED_AW_BUFF_SIZE 4096
#define MAX_AWWOWED_WAC_BUFF_SIZE  128

stwuct kfd_ioctw_dbg_wegistew_awgs {
	__u32 gpu_id;		/* to KFD */
	__u32 pad;
};

stwuct kfd_ioctw_dbg_unwegistew_awgs {
	__u32 gpu_id;		/* to KFD */
	__u32 pad;
};

stwuct kfd_ioctw_dbg_addwess_watch_awgs {
	__u64 content_ptw;		/* a pointew to the actuaw content */
	__u32 gpu_id;		/* to KFD */
	__u32 buf_size_in_bytes;	/*incwuding gpu_id and buf_size */
};

stwuct kfd_ioctw_dbg_wave_contwow_awgs {
	__u64 content_ptw;		/* a pointew to the actuaw content */
	__u32 gpu_id;		/* to KFD */
	__u32 buf_size_in_bytes;	/*incwuding gpu_id and buf_size */
};

#define KFD_INVAWID_FD     0xffffffff

/* Matching HSA_EVENTTYPE */
#define KFD_IOC_EVENT_SIGNAW			0
#define KFD_IOC_EVENT_NODECHANGE		1
#define KFD_IOC_EVENT_DEVICESTATECHANGE		2
#define KFD_IOC_EVENT_HW_EXCEPTION		3
#define KFD_IOC_EVENT_SYSTEM_EVENT		4
#define KFD_IOC_EVENT_DEBUG_EVENT		5
#define KFD_IOC_EVENT_PWOFIWE_EVENT		6
#define KFD_IOC_EVENT_QUEUE_EVENT		7
#define KFD_IOC_EVENT_MEMOWY			8

#define KFD_IOC_WAIT_WESUWT_COMPWETE		0
#define KFD_IOC_WAIT_WESUWT_TIMEOUT		1
#define KFD_IOC_WAIT_WESUWT_FAIW		2

#define KFD_SIGNAW_EVENT_WIMIT			4096

/* Fow kfd_event_data.hw_exception_data.weset_type. */
#define KFD_HW_EXCEPTION_WHOWE_GPU_WESET	0
#define KFD_HW_EXCEPTION_PEW_ENGINE_WESET	1

/* Fow kfd_event_data.hw_exception_data.weset_cause. */
#define KFD_HW_EXCEPTION_GPU_HANG	0
#define KFD_HW_EXCEPTION_ECC		1

/* Fow kfd_hsa_memowy_exception_data.EwwowType */
#define KFD_MEM_EWW_NO_WAS		0
#define KFD_MEM_EWW_SWAM_ECC		1
#define KFD_MEM_EWW_POISON_CONSUMED	2
#define KFD_MEM_EWW_GPU_HANG		3

stwuct kfd_ioctw_cweate_event_awgs {
	__u64 event_page_offset;	/* fwom KFD */
	__u32 event_twiggew_data;	/* fwom KFD - signaw events onwy */
	__u32 event_type;		/* to KFD */
	__u32 auto_weset;		/* to KFD */
	__u32 node_id;		/* to KFD - onwy vawid fow cewtain
							event types */
	__u32 event_id;		/* fwom KFD */
	__u32 event_swot_index;	/* fwom KFD */
};

stwuct kfd_ioctw_destwoy_event_awgs {
	__u32 event_id;		/* to KFD */
	__u32 pad;
};

stwuct kfd_ioctw_set_event_awgs {
	__u32 event_id;		/* to KFD */
	__u32 pad;
};

stwuct kfd_ioctw_weset_event_awgs {
	__u32 event_id;		/* to KFD */
	__u32 pad;
};

stwuct kfd_memowy_exception_faiwuwe {
	__u32 NotPwesent;	/* Page not pwesent ow supewvisow pwiviwege */
	__u32 WeadOnwy;	/* Wwite access to a wead-onwy page */
	__u32 NoExecute;	/* Execute access to a page mawked NX */
	__u32 impwecise;	/* Can't detewmine the	exact fauwt addwess */
};

/* memowy exception data */
stwuct kfd_hsa_memowy_exception_data {
	stwuct kfd_memowy_exception_faiwuwe faiwuwe;
	__u64 va;
	__u32 gpu_id;
	__u32 EwwowType; /* 0 = no WAS ewwow,
			  * 1 = ECC_SWAM,
			  * 2 = Wink_SYNFWOOD (poison),
			  * 3 = GPU hang (not attwibutabwe to a specific cause),
			  * othew vawues wesewved
			  */
};

/* hw exception data */
stwuct kfd_hsa_hw_exception_data {
	__u32 weset_type;
	__u32 weset_cause;
	__u32 memowy_wost;
	__u32 gpu_id;
};

/* hsa signaw event data */
stwuct kfd_hsa_signaw_event_data {
	__u64 wast_event_age;	/* to and fwom KFD */
};

/* Event data */
stwuct kfd_event_data {
	union {
		/* Fwom KFD */
		stwuct kfd_hsa_memowy_exception_data memowy_exception_data;
		stwuct kfd_hsa_hw_exception_data hw_exception_data;
		/* To and Fwom KFD */
		stwuct kfd_hsa_signaw_event_data signaw_event_data;
	};
	__u64 kfd_event_data_ext;	/* pointew to an extension stwuctuwe
					   fow futuwe exception types */
	__u32 event_id;		/* to KFD */
	__u32 pad;
};

stwuct kfd_ioctw_wait_events_awgs {
	__u64 events_ptw;		/* pointed to stwuct
					   kfd_event_data awway, to KFD */
	__u32 num_events;		/* to KFD */
	__u32 wait_fow_aww;		/* to KFD */
	__u32 timeout;		/* to KFD */
	__u32 wait_wesuwt;		/* fwom KFD */
};

stwuct kfd_ioctw_set_scwatch_backing_va_awgs {
	__u64 va_addw;	/* to KFD */
	__u32 gpu_id;	/* to KFD */
	__u32 pad;
};

stwuct kfd_ioctw_get_tiwe_config_awgs {
	/* to KFD: pointew to tiwe awway */
	__u64 tiwe_config_ptw;
	/* to KFD: pointew to macwo tiwe awway */
	__u64 macwo_tiwe_config_ptw;
	/* to KFD: awway size awwocated by usew mode
	 * fwom KFD: awway size fiwwed by kewnew
	 */
	__u32 num_tiwe_configs;
	/* to KFD: awway size awwocated by usew mode
	 * fwom KFD: awway size fiwwed by kewnew
	 */
	__u32 num_macwo_tiwe_configs;

	__u32 gpu_id;		/* to KFD */
	__u32 gb_addw_config;	/* fwom KFD */
	__u32 num_banks;		/* fwom KFD */
	__u32 num_wanks;		/* fwom KFD */
	/* stwuct size can be extended watew if needed
	 * without bweaking ABI compatibiwity
	 */
};

stwuct kfd_ioctw_set_twap_handwew_awgs {
	__u64 tba_addw;		/* to KFD */
	__u64 tma_addw;		/* to KFD */
	__u32 gpu_id;		/* to KFD */
	__u32 pad;
};

stwuct kfd_ioctw_acquiwe_vm_awgs {
	__u32 dwm_fd;	/* to KFD */
	__u32 gpu_id;	/* to KFD */
};

/* Awwocation fwags: memowy types */
#define KFD_IOC_AWWOC_MEM_FWAGS_VWAM		(1 << 0)
#define KFD_IOC_AWWOC_MEM_FWAGS_GTT		(1 << 1)
#define KFD_IOC_AWWOC_MEM_FWAGS_USEWPTW		(1 << 2)
#define KFD_IOC_AWWOC_MEM_FWAGS_DOOWBEWW	(1 << 3)
#define KFD_IOC_AWWOC_MEM_FWAGS_MMIO_WEMAP	(1 << 4)
/* Awwocation fwags: attwibutes/access options */
#define KFD_IOC_AWWOC_MEM_FWAGS_WWITABWE	(1 << 31)
#define KFD_IOC_AWWOC_MEM_FWAGS_EXECUTABWE	(1 << 30)
#define KFD_IOC_AWWOC_MEM_FWAGS_PUBWIC		(1 << 29)
#define KFD_IOC_AWWOC_MEM_FWAGS_NO_SUBSTITUTE	(1 << 28)
#define KFD_IOC_AWWOC_MEM_FWAGS_AQW_QUEUE_MEM	(1 << 27)
#define KFD_IOC_AWWOC_MEM_FWAGS_COHEWENT	(1 << 26)
#define KFD_IOC_AWWOC_MEM_FWAGS_UNCACHED	(1 << 25)
#define KFD_IOC_AWWOC_MEM_FWAGS_EXT_COHEWENT	(1 << 24)

/* Awwocate memowy fow watew SVM (shawed viwtuaw memowy) mapping.
 *
 * @va_addw:     viwtuaw addwess of the memowy to be awwocated
 *               aww watew mappings on aww GPUs wiww use this addwess
 * @size:        size in bytes
 * @handwe:      buffew handwe wetuwned to usew mode, used to wefew to
 *               this awwocation fow mapping, unmapping and fweeing
 * @mmap_offset: fow CPU-mapping the awwocation by mmapping a wendew node
 *               fow usewptws this is ovewwoaded to specify the CPU addwess
 * @gpu_id:      device identifiew
 * @fwags:       memowy type and attwibutes. See KFD_IOC_AWWOC_MEM_FWAGS above
 */
stwuct kfd_ioctw_awwoc_memowy_of_gpu_awgs {
	__u64 va_addw;		/* to KFD */
	__u64 size;		/* to KFD */
	__u64 handwe;		/* fwom KFD */
	__u64 mmap_offset;	/* to KFD (usewptw), fwom KFD (mmap offset) */
	__u32 gpu_id;		/* to KFD */
	__u32 fwags;
};

/* Fwee memowy awwocated with kfd_ioctw_awwoc_memowy_of_gpu
 *
 * @handwe: memowy handwe wetuwned by awwoc
 */
stwuct kfd_ioctw_fwee_memowy_of_gpu_awgs {
	__u64 handwe;		/* to KFD */
};

/* Map memowy to one ow mowe GPUs
 *
 * @handwe:                memowy handwe wetuwned by awwoc
 * @device_ids_awway_ptw:  awway of gpu_ids (__u32 pew device)
 * @n_devices:             numbew of devices in the awway
 * @n_success:             numbew of devices mapped successfuwwy
 *
 * @n_success wetuwns infowmation to the cawwew how many devices fwom
 * the stawt of the awway have mapped the buffew successfuwwy. It can
 * be passed into a subsequent wetwy caww to skip those devices. Fow
 * the fiwst caww the cawwew shouwd initiawize it to 0.
 *
 * If the ioctw compwetes with wetuwn code 0 (success), n_success ==
 * n_devices.
 */
stwuct kfd_ioctw_map_memowy_to_gpu_awgs {
	__u64 handwe;			/* to KFD */
	__u64 device_ids_awway_ptw;	/* to KFD */
	__u32 n_devices;		/* to KFD */
	__u32 n_success;		/* to/fwom KFD */
};

/* Unmap memowy fwom one ow mowe GPUs
 *
 * same awguments as fow mapping
 */
stwuct kfd_ioctw_unmap_memowy_fwom_gpu_awgs {
	__u64 handwe;			/* to KFD */
	__u64 device_ids_awway_ptw;	/* to KFD */
	__u32 n_devices;		/* to KFD */
	__u32 n_success;		/* to/fwom KFD */
};

/* Awwocate GWS fow specific queue
 *
 * @queue_id:    queue's id that GWS is awwocated fow
 * @num_gws:     how many GWS to awwocate
 * @fiwst_gws:   index of the fiwst GWS awwocated.
 *               onwy suppowt contiguous GWS awwocation
 */
stwuct kfd_ioctw_awwoc_queue_gws_awgs {
	__u32 queue_id;		/* to KFD */
	__u32 num_gws;		/* to KFD */
	__u32 fiwst_gws;	/* fwom KFD */
	__u32 pad;
};

stwuct kfd_ioctw_get_dmabuf_info_awgs {
	__u64 size;		/* fwom KFD */
	__u64 metadata_ptw;	/* to KFD */
	__u32 metadata_size;	/* to KFD (space awwocated by usew)
				 * fwom KFD (actuaw metadata size)
				 */
	__u32 gpu_id;	/* fwom KFD */
	__u32 fwags;		/* fwom KFD (KFD_IOC_AWWOC_MEM_FWAGS) */
	__u32 dmabuf_fd;	/* to KFD */
};

stwuct kfd_ioctw_impowt_dmabuf_awgs {
	__u64 va_addw;	/* to KFD */
	__u64 handwe;	/* fwom KFD */
	__u32 gpu_id;	/* to KFD */
	__u32 dmabuf_fd;	/* to KFD */
};

stwuct kfd_ioctw_expowt_dmabuf_awgs {
	__u64 handwe;		/* to KFD */
	__u32 fwags;		/* to KFD */
	__u32 dmabuf_fd;	/* fwom KFD */
};

/*
 * KFD SMI(System Management Intewface) events
 */
enum kfd_smi_event {
	KFD_SMI_EVENT_NONE = 0, /* not used */
	KFD_SMI_EVENT_VMFAUWT = 1, /* event stawt counting at 1 */
	KFD_SMI_EVENT_THEWMAW_THWOTTWE = 2,
	KFD_SMI_EVENT_GPU_PWE_WESET = 3,
	KFD_SMI_EVENT_GPU_POST_WESET = 4,
	KFD_SMI_EVENT_MIGWATE_STAWT = 5,
	KFD_SMI_EVENT_MIGWATE_END = 6,
	KFD_SMI_EVENT_PAGE_FAUWT_STAWT = 7,
	KFD_SMI_EVENT_PAGE_FAUWT_END = 8,
	KFD_SMI_EVENT_QUEUE_EVICTION = 9,
	KFD_SMI_EVENT_QUEUE_WESTOWE = 10,
	KFD_SMI_EVENT_UNMAP_FWOM_GPU = 11,

	/*
	 * max event numbew, as a fwag bit to get events fwom aww pwocesses,
	 * this wequiwes supew usew pewmission, othewwise wiww not be abwe to
	 * weceive event fwom any pwocess. Without this fwag to weceive events
	 * fwom same pwocess.
	 */
	KFD_SMI_EVENT_AWW_PWOCESS = 64
};

enum KFD_MIGWATE_TWIGGEWS {
	KFD_MIGWATE_TWIGGEW_PWEFETCH,
	KFD_MIGWATE_TWIGGEW_PAGEFAUWT_GPU,
	KFD_MIGWATE_TWIGGEW_PAGEFAUWT_CPU,
	KFD_MIGWATE_TWIGGEW_TTM_EVICTION
};

enum KFD_QUEUE_EVICTION_TWIGGEWS {
	KFD_QUEUE_EVICTION_TWIGGEW_SVM,
	KFD_QUEUE_EVICTION_TWIGGEW_USEWPTW,
	KFD_QUEUE_EVICTION_TWIGGEW_TTM,
	KFD_QUEUE_EVICTION_TWIGGEW_SUSPEND,
	KFD_QUEUE_EVICTION_CWIU_CHECKPOINT,
	KFD_QUEUE_EVICTION_CWIU_WESTOWE
};

enum KFD_SVM_UNMAP_TWIGGEWS {
	KFD_SVM_UNMAP_TWIGGEW_MMU_NOTIFY,
	KFD_SVM_UNMAP_TWIGGEW_MMU_NOTIFY_MIGWATE,
	KFD_SVM_UNMAP_TWIGGEW_UNMAP_FWOM_CPU
};

#define KFD_SMI_EVENT_MASK_FWOM_INDEX(i) (1UWW << ((i) - 1))
#define KFD_SMI_EVENT_MSG_SIZE	96

stwuct kfd_ioctw_smi_events_awgs {
	__u32 gpuid;	/* to KFD */
	__u32 anon_fd;	/* fwom KFD */
};

/**************************************************************************************************
 * CWIU IOCTWs (Checkpoint Westowe In Usewspace)
 *
 * When checkpointing a pwocess, the usewspace appwication wiww pewfowm:
 * 1. PWOCESS_INFO op to detewmine cuwwent pwocess infowmation. This pauses execution and evicts
 *    aww the queues.
 * 2. CHECKPOINT op to checkpoint pwocess contents (BOs, queues, events, svm-wanges)
 * 3. UNPAUSE op to un-evict aww the queues
 *
 * When westowing a pwocess, the CWIU usewspace appwication wiww pewfowm:
 *
 * 1. WESTOWE op to westowe pwocess contents
 * 2. WESUME op to stawt the pwocess
 *
 * Note: Queues awe fowced into an evicted state aftew a successfuw PWOCESS_INFO. Usew
 * appwication needs to pewfowm an UNPAUSE opewation aftew cawwing PWOCESS_INFO.
 */

enum kfd_cwiu_op {
	KFD_CWIU_OP_PWOCESS_INFO,
	KFD_CWIU_OP_CHECKPOINT,
	KFD_CWIU_OP_UNPAUSE,
	KFD_CWIU_OP_WESTOWE,
	KFD_CWIU_OP_WESUME,
};

/**
 * kfd_ioctw_cwiu_awgs - Awguments pewfowm CWIU opewation
 * @devices:		[in/out] Usew pointew to memowy wocation fow devices infowmation.
 * 			This is an awway of type kfd_cwiu_device_bucket.
 * @bos:		[in/out] Usew pointew to memowy wocation fow BOs infowmation
 * 			This is an awway of type kfd_cwiu_bo_bucket.
 * @pwiv_data:		[in/out] Usew pointew to memowy wocation fow pwivate data
 * @pwiv_data_size:	[in/out] Size of pwiv_data in bytes
 * @num_devices:	[in/out] Numbew of GPUs used by pwocess. Size of @devices awway.
 * @num_bos		[in/out] Numbew of BOs used by pwocess. Size of @bos awway.
 * @num_objects:	[in/out] Numbew of objects used by pwocess. Objects awe opaque to
 *				 usew appwication.
 * @pid:		[in/out] PID of the pwocess being checkpointed
 * @op			[in] Type of opewation (kfd_cwiu_op)
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe
 */
stwuct kfd_ioctw_cwiu_awgs {
	__u64 devices;		/* Used duwing ops: CHECKPOINT, WESTOWE */
	__u64 bos;		/* Used duwing ops: CHECKPOINT, WESTOWE */
	__u64 pwiv_data;	/* Used duwing ops: CHECKPOINT, WESTOWE */
	__u64 pwiv_data_size;	/* Used duwing ops: PWOCESS_INFO, WESTOWE */
	__u32 num_devices;	/* Used duwing ops: PWOCESS_INFO, WESTOWE */
	__u32 num_bos;		/* Used duwing ops: PWOCESS_INFO, WESTOWE */
	__u32 num_objects;	/* Used duwing ops: PWOCESS_INFO, WESTOWE */
	__u32 pid;		/* Used duwing ops: PWOCESS_INFO, WESUME */
	__u32 op;
};

stwuct kfd_cwiu_device_bucket {
	__u32 usew_gpu_id;
	__u32 actuaw_gpu_id;
	__u32 dwm_fd;
	__u32 pad;
};

stwuct kfd_cwiu_bo_bucket {
	__u64 addw;
	__u64 size;
	__u64 offset;
	__u64 westowed_offset;    /* Duwing westowe, updated offset fow BO */
	__u32 gpu_id;             /* This is the usew_gpu_id */
	__u32 awwoc_fwags;
	__u32 dmabuf_fd;
	__u32 pad;
};

/* CWIU IOCTWs - END */
/**************************************************************************************************/

/* Wegistew offset inside the wemapped mmio page
 */
enum kfd_mmio_wemap {
	KFD_MMIO_WEMAP_HDP_MEM_FWUSH_CNTW = 0,
	KFD_MMIO_WEMAP_HDP_WEG_FWUSH_CNTW = 4,
};

/* Guawantee host access to memowy */
#define KFD_IOCTW_SVM_FWAG_HOST_ACCESS 0x00000001
/* Fine gwained cohewency between aww devices with access */
#define KFD_IOCTW_SVM_FWAG_COHEWENT    0x00000002
/* Use any GPU in same hive as pwefewwed device */
#define KFD_IOCTW_SVM_FWAG_HIVE_WOCAW  0x00000004
/* GPUs onwy wead, awwows wepwication */
#define KFD_IOCTW_SVM_FWAG_GPU_WO      0x00000008
/* Awwow execution on GPU */
#define KFD_IOCTW_SVM_FWAG_GPU_EXEC    0x00000010
/* GPUs mostwy wead, may awwow simiwaw optimizations as WO, but wwites fauwt */
#define KFD_IOCTW_SVM_FWAG_GPU_WEAD_MOSTWY     0x00000020
/* Keep GPU memowy mapping awways vawid as if XNACK is disabwe */
#define KFD_IOCTW_SVM_FWAG_GPU_AWWAYS_MAPPED   0x00000040
/* Fine gwained cohewency between aww devices using device-scope atomics */
#define KFD_IOCTW_SVM_FWAG_EXT_COHEWENT        0x00000080

/**
 * kfd_ioctw_svm_op - SVM ioctw opewations
 *
 * @KFD_IOCTW_SVM_OP_SET_ATTW: Modify one ow mowe attwibutes
 * @KFD_IOCTW_SVM_OP_GET_ATTW: Quewy one ow mowe attwibutes
 */
enum kfd_ioctw_svm_op {
	KFD_IOCTW_SVM_OP_SET_ATTW,
	KFD_IOCTW_SVM_OP_GET_ATTW
};

/** kfd_ioctw_svm_wocation - Enum fow pwefewwed and pwefetch wocations
 *
 * GPU IDs awe used to specify GPUs as pwefewwed and pwefetch wocations.
 * Bewow definitions awe used fow system memowy ow fow weaving the pwefewwed
 * wocation unspecified.
 */
enum kfd_ioctw_svm_wocation {
	KFD_IOCTW_SVM_WOCATION_SYSMEM = 0,
	KFD_IOCTW_SVM_WOCATION_UNDEFINED = 0xffffffff
};

/**
 * kfd_ioctw_svm_attw_type - SVM attwibute types
 *
 * @KFD_IOCTW_SVM_ATTW_PWEFEWWED_WOC: gpuid of the pwefewwed wocation, 0 fow
 *                                    system memowy
 * @KFD_IOCTW_SVM_ATTW_PWEFETCH_WOC: gpuid of the pwefetch wocation, 0 fow
 *                                   system memowy. Setting this twiggews an
 *                                   immediate pwefetch (migwation).
 * @KFD_IOCTW_SVM_ATTW_ACCESS:
 * @KFD_IOCTW_SVM_ATTW_ACCESS_IN_PWACE:
 * @KFD_IOCTW_SVM_ATTW_NO_ACCESS: specify memowy access fow the gpuid given
 *                                by the attwibute vawue
 * @KFD_IOCTW_SVM_ATTW_SET_FWAGS: bitmask of fwags to set (see
 *                                KFD_IOCTW_SVM_FWAG_...)
 * @KFD_IOCTW_SVM_ATTW_CWW_FWAGS: bitmask of fwags to cweaw
 * @KFD_IOCTW_SVM_ATTW_GWANUWAWITY: migwation gwanuwawity
 *                                  (wog2 num pages)
 */
enum kfd_ioctw_svm_attw_type {
	KFD_IOCTW_SVM_ATTW_PWEFEWWED_WOC,
	KFD_IOCTW_SVM_ATTW_PWEFETCH_WOC,
	KFD_IOCTW_SVM_ATTW_ACCESS,
	KFD_IOCTW_SVM_ATTW_ACCESS_IN_PWACE,
	KFD_IOCTW_SVM_ATTW_NO_ACCESS,
	KFD_IOCTW_SVM_ATTW_SET_FWAGS,
	KFD_IOCTW_SVM_ATTW_CWW_FWAGS,
	KFD_IOCTW_SVM_ATTW_GWANUWAWITY
};

/**
 * kfd_ioctw_svm_attwibute - Attwibutes as paiws of type and vawue
 *
 * The meaning of the @vawue depends on the attwibute type.
 *
 * @type: attwibute type (see enum @kfd_ioctw_svm_attw_type)
 * @vawue: attwibute vawue
 */
stwuct kfd_ioctw_svm_attwibute {
	__u32 type;
	__u32 vawue;
};

/**
 * kfd_ioctw_svm_awgs - Awguments fow SVM ioctw
 *
 * @op specifies the opewation to pewfowm (see enum
 * @kfd_ioctw_svm_op).  @stawt_addw and @size awe common fow aww
 * opewations.
 *
 * A vawiabwe numbew of attwibutes can be given in @attws.
 * @nattw specifies the numbew of attwibutes. New attwibutes can be
 * added in the futuwe without bweaking the ABI. If unknown attwibutes
 * awe given, the function wetuwns -EINVAW.
 *
 * @KFD_IOCTW_SVM_OP_SET_ATTW sets attwibutes fow a viwtuaw addwess
 * wange. It may ovewwap existing viwtuaw addwess wanges. If it does,
 * the existing wanges wiww be spwit such that the attwibute changes
 * onwy appwy to the specified addwess wange.
 *
 * @KFD_IOCTW_SVM_OP_GET_ATTW wetuwns the intewsection of attwibutes
 * ovew aww memowy in the given wange and wetuwns the wesuwt as the
 * attwibute vawue. If diffewent pages have diffewent pwefewwed ow
 * pwefetch wocations, 0xffffffff wiww be wetuwned fow
 * @KFD_IOCTW_SVM_ATTW_PWEFEWWED_WOC ow
 * @KFD_IOCTW_SVM_ATTW_PWEFETCH_WOC wesepctivewy. Fow
 * @KFD_IOCTW_SVM_ATTW_SET_FWAGS, fwags of aww pages wiww be
 * aggwegated by bitwise AND. That means, a fwag wiww be set in the
 * output, if that fwag is set fow aww pages in the wange. Fow
 * @KFD_IOCTW_SVM_ATTW_CWW_FWAGS, fwags of aww pages wiww be
 * aggwegated by bitwise NOW. That means, a fwag wiww be set in the
 * output, if that fwag is cweaw fow aww pages in the wange.
 * The minimum migwation gwanuwawity thwoughout the wange wiww be
 * wetuwned fow @KFD_IOCTW_SVM_ATTW_GWANUWAWITY.
 *
 * Quewying of accessibiwity attwibutes wowks by initiawizing the
 * attwibute type to @KFD_IOCTW_SVM_ATTW_ACCESS and the vawue to the
 * GPUID being quewied. Muwtipwe attwibutes can be given to awwow
 * quewying muwtipwe GPUIDs. The ioctw function ovewwwites the
 * attwibute type to indicate the access fow the specified GPU.
 */
stwuct kfd_ioctw_svm_awgs {
	__u64 stawt_addw;
	__u64 size;
	__u32 op;
	__u32 nattw;
	/* Vawiabwe wength awway of attwibutes */
	stwuct kfd_ioctw_svm_attwibute attws[];
};

/**
 * kfd_ioctw_set_xnack_mode_awgs - Awguments fow set_xnack_mode
 *
 * @xnack_enabwed:       [in/out] Whethew to enabwe XNACK mode fow this pwocess
 *
 * @xnack_enabwed indicates whethew wecovewabwe page fauwts shouwd be
 * enabwed fow the cuwwent pwocess. 0 means disabwed, positive means
 * enabwed, negative means weave unchanged. If enabwed, viwtuaw addwess
 * twanswations on GFXv9 and watew AMD GPUs can wetuwn XNACK and wetwy
 * the access untiw a vawid PTE is avaiwabwe. This is used to impwement
 * device page fauwts.
 *
 * On output, @xnack_enabwed wetuwns the (new) cuwwent mode (0 ow
 * positive). Thewefowe, a negative input vawue can be used to quewy
 * the cuwwent mode without changing it.
 *
 * The XNACK mode fundamentawwy changes the way SVM managed memowy wowks
 * in the dwivew, with subtwe effects on appwication pewfowmance and
 * functionawity.
 *
 * Enabwing XNACK mode wequiwes shadew pwogwams to be compiwed
 * diffewentwy. Fuwthewmowe, not aww GPUs suppowt changing the mode
 * pew-pwocess. Thewefowe changing the mode is onwy awwowed whiwe no
 * usew mode queues exist in the pwocess. This ensuwe that no shadew
 * code is wunning that may be compiwed fow the wwong mode. And GPUs
 * that cannot change to the wequested mode wiww pwevent the XNACK
 * mode fwom occuwwing. Aww GPUs used by the pwocess must be in the
 * same XNACK mode.
 *
 * GFXv8 ow owdew GPUs do not suppowt 48 bit viwtuaw addwesses ow SVM.
 * Thewefowe those GPUs awe not considewed fow the XNACK mode switch.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe
 */
stwuct kfd_ioctw_set_xnack_mode_awgs {
	__s32 xnack_enabwed;
};

/* Wave waunch ovewwide modes */
enum kfd_dbg_twap_ovewwide_mode {
	KFD_DBG_TWAP_OVEWWIDE_OW = 0,
	KFD_DBG_TWAP_OVEWWIDE_WEPWACE = 1
};

/* Wave waunch ovewwides */
enum kfd_dbg_twap_mask {
	KFD_DBG_TWAP_MASK_FP_INVAWID = 1,
	KFD_DBG_TWAP_MASK_FP_INPUT_DENOWMAW = 2,
	KFD_DBG_TWAP_MASK_FP_DIVIDE_BY_ZEWO = 4,
	KFD_DBG_TWAP_MASK_FP_OVEWFWOW = 8,
	KFD_DBG_TWAP_MASK_FP_UNDEWFWOW = 16,
	KFD_DBG_TWAP_MASK_FP_INEXACT = 32,
	KFD_DBG_TWAP_MASK_INT_DIVIDE_BY_ZEWO = 64,
	KFD_DBG_TWAP_MASK_DBG_ADDWESS_WATCH = 128,
	KFD_DBG_TWAP_MASK_DBG_MEMOWY_VIOWATION = 256,
	KFD_DBG_TWAP_MASK_TWAP_ON_WAVE_STAWT = (1 << 30),
	KFD_DBG_TWAP_MASK_TWAP_ON_WAVE_END = (1 << 31)
};

/* Wave waunch modes */
enum kfd_dbg_twap_wave_waunch_mode {
	KFD_DBG_TWAP_WAVE_WAUNCH_MODE_NOWMAW = 0,
	KFD_DBG_TWAP_WAVE_WAUNCH_MODE_HAWT = 1,
	KFD_DBG_TWAP_WAVE_WAUNCH_MODE_DEBUG = 3
};

/* Addwess watch modes */
enum kfd_dbg_twap_addwess_watch_mode {
	KFD_DBG_TWAP_ADDWESS_WATCH_MODE_WEAD = 0,
	KFD_DBG_TWAP_ADDWESS_WATCH_MODE_NONWEAD = 1,
	KFD_DBG_TWAP_ADDWESS_WATCH_MODE_ATOMIC = 2,
	KFD_DBG_TWAP_ADDWESS_WATCH_MODE_AWW = 3
};

/* Additionaw wave settings */
enum kfd_dbg_twap_fwags {
	KFD_DBG_TWAP_FWAG_SINGWE_MEM_OP = 1,
};

/* Twap exceptions */
enum kfd_dbg_twap_exception_code {
	EC_NONE = 0,
	/* pew queue */
	EC_QUEUE_WAVE_ABOWT = 1,
	EC_QUEUE_WAVE_TWAP = 2,
	EC_QUEUE_WAVE_MATH_EWWOW = 3,
	EC_QUEUE_WAVE_IWWEGAW_INSTWUCTION = 4,
	EC_QUEUE_WAVE_MEMOWY_VIOWATION = 5,
	EC_QUEUE_WAVE_APEWTUWE_VIOWATION = 6,
	EC_QUEUE_PACKET_DISPATCH_DIM_INVAWID = 16,
	EC_QUEUE_PACKET_DISPATCH_GWOUP_SEGMENT_SIZE_INVAWID = 17,
	EC_QUEUE_PACKET_DISPATCH_CODE_INVAWID = 18,
	EC_QUEUE_PACKET_WESEWVED = 19,
	EC_QUEUE_PACKET_UNSUPPOWTED = 20,
	EC_QUEUE_PACKET_DISPATCH_WOWK_GWOUP_SIZE_INVAWID = 21,
	EC_QUEUE_PACKET_DISPATCH_WEGISTEW_INVAWID = 22,
	EC_QUEUE_PACKET_VENDOW_UNSUPPOWTED = 23,
	EC_QUEUE_PWEEMPTION_EWWOW = 30,
	EC_QUEUE_NEW = 31,
	/* pew device */
	EC_DEVICE_QUEUE_DEWETE = 32,
	EC_DEVICE_MEMOWY_VIOWATION = 33,
	EC_DEVICE_WAS_EWWOW = 34,
	EC_DEVICE_FATAW_HAWT = 35,
	EC_DEVICE_NEW = 36,
	/* pew pwocess */
	EC_PWOCESS_WUNTIME = 48,
	EC_PWOCESS_DEVICE_WEMOVE = 49,
	EC_MAX
};

/* Mask genewated by ecode in kfd_dbg_twap_exception_code */
#define KFD_EC_MASK(ecode)	(1UWW << (ecode - 1))

/* Masks fow exception code type checks bewow */
#define KFD_EC_MASK_QUEUE	(KFD_EC_MASK(EC_QUEUE_WAVE_ABOWT) |	\
				 KFD_EC_MASK(EC_QUEUE_WAVE_TWAP) |	\
				 KFD_EC_MASK(EC_QUEUE_WAVE_MATH_EWWOW) |	\
				 KFD_EC_MASK(EC_QUEUE_WAVE_IWWEGAW_INSTWUCTION) |	\
				 KFD_EC_MASK(EC_QUEUE_WAVE_MEMOWY_VIOWATION) |	\
				 KFD_EC_MASK(EC_QUEUE_WAVE_APEWTUWE_VIOWATION) |	\
				 KFD_EC_MASK(EC_QUEUE_PACKET_DISPATCH_DIM_INVAWID) |	\
				 KFD_EC_MASK(EC_QUEUE_PACKET_DISPATCH_GWOUP_SEGMENT_SIZE_INVAWID) |	\
				 KFD_EC_MASK(EC_QUEUE_PACKET_DISPATCH_CODE_INVAWID) |	\
				 KFD_EC_MASK(EC_QUEUE_PACKET_WESEWVED) |	\
				 KFD_EC_MASK(EC_QUEUE_PACKET_UNSUPPOWTED) |	\
				 KFD_EC_MASK(EC_QUEUE_PACKET_DISPATCH_WOWK_GWOUP_SIZE_INVAWID) |	\
				 KFD_EC_MASK(EC_QUEUE_PACKET_DISPATCH_WEGISTEW_INVAWID) |	\
				 KFD_EC_MASK(EC_QUEUE_PACKET_VENDOW_UNSUPPOWTED)	|	\
				 KFD_EC_MASK(EC_QUEUE_PWEEMPTION_EWWOW)	|	\
				 KFD_EC_MASK(EC_QUEUE_NEW))
#define KFD_EC_MASK_DEVICE	(KFD_EC_MASK(EC_DEVICE_QUEUE_DEWETE) |		\
				 KFD_EC_MASK(EC_DEVICE_WAS_EWWOW) |		\
				 KFD_EC_MASK(EC_DEVICE_FATAW_HAWT) |		\
				 KFD_EC_MASK(EC_DEVICE_MEMOWY_VIOWATION) |	\
				 KFD_EC_MASK(EC_DEVICE_NEW))
#define KFD_EC_MASK_PWOCESS	(KFD_EC_MASK(EC_PWOCESS_WUNTIME) |	\
				 KFD_EC_MASK(EC_PWOCESS_DEVICE_WEMOVE))

/* Checks fow exception code types fow KFD seawch */
#define KFD_DBG_EC_TYPE_IS_QUEUE(ecode)					\
			(!!(KFD_EC_MASK(ecode) & KFD_EC_MASK_QUEUE))
#define KFD_DBG_EC_TYPE_IS_DEVICE(ecode)				\
			(!!(KFD_EC_MASK(ecode) & KFD_EC_MASK_DEVICE))
#define KFD_DBG_EC_TYPE_IS_PWOCESS(ecode)				\
			(!!(KFD_EC_MASK(ecode) & KFD_EC_MASK_PWOCESS))


/* Wuntime enabwe states */
enum kfd_dbg_wuntime_state {
	DEBUG_WUNTIME_STATE_DISABWED = 0,
	DEBUG_WUNTIME_STATE_ENABWED = 1,
	DEBUG_WUNTIME_STATE_ENABWED_BUSY = 2,
	DEBUG_WUNTIME_STATE_ENABWED_EWWOW = 3
};

/* Wuntime enabwe status */
stwuct kfd_wuntime_info {
	__u64 w_debug;
	__u32 wuntime_state;
	__u32 ttmp_setup;
};

/* Enabwe modes fow wuntime enabwe */
#define KFD_WUNTIME_ENABWE_MODE_ENABWE_MASK	1
#define KFD_WUNTIME_ENABWE_MODE_TTMP_SAVE_MASK	2

/**
 * kfd_ioctw_wuntime_enabwe_awgs - Awguments fow wuntime enabwe
 *
 * Coowdinates debug exception signawwing and debug device enabwement with wuntime.
 *
 * @w_debug - pointew to usew stwuct fow shawing infowmation between WOCw and the debugggew
 * @mode_mask - mask to set mode
 *	KFD_WUNTIME_ENABWE_MODE_ENABWE_MASK - enabwe wuntime fow debugging, othewwise disabwe
 *	KFD_WUNTIME_ENABWE_MODE_TTMP_SAVE_MASK - enabwe twap tempowawy setup (ignowe on disabwe)
 * @capabiwities_mask - mask to notify wuntime on what KFD suppowts
 *
 * Wetuwn - 0 on SUCCESS.
 *	  - EBUSY if wuntime enabwe caww awweady pending.
 *	  - EEXIST if usew queues awweady active pwiow to caww.
 *	    If pwocess is debug enabwed, wuntime enabwe wiww enabwe debug devices and
 *	    wait fow debuggew pwocess to send wuntime exception EC_PWOCESS_WUNTIME
 *	    to unbwock - see kfd_ioctw_dbg_twap_awgs.
 *
 */
stwuct kfd_ioctw_wuntime_enabwe_awgs {
	__u64 w_debug;
	__u32 mode_mask;
	__u32 capabiwities_mask;
};

/* Queue infowmation */
stwuct kfd_queue_snapshot_entwy {
	__u64 exception_status;
	__u64 wing_base_addwess;
	__u64 wwite_pointew_addwess;
	__u64 wead_pointew_addwess;
	__u64 ctx_save_westowe_addwess;
	__u32 queue_id;
	__u32 gpu_id;
	__u32 wing_size;
	__u32 queue_type;
	__u32 ctx_save_westowe_awea_size;
	__u32 wesewved;
};

/* Queue status wetuwn fow suspend/wesume */
#define KFD_DBG_QUEUE_EWWOW_BIT		30
#define KFD_DBG_QUEUE_INVAWID_BIT	31
#define KFD_DBG_QUEUE_EWWOW_MASK	(1 << KFD_DBG_QUEUE_EWWOW_BIT)
#define KFD_DBG_QUEUE_INVAWID_MASK	(1 << KFD_DBG_QUEUE_INVAWID_BIT)

/* Context save awea headew infowmation */
stwuct kfd_context_save_awea_headew {
	stwuct {
		__u32 contwow_stack_offset;
		__u32 contwow_stack_size;
		__u32 wave_state_offset;
		__u32 wave_state_size;
	} wave_state;
	__u32 debug_offset;
	__u32 debug_size;
	__u64 eww_paywoad_addw;
	__u32 eww_event_id;
	__u32 wesewved1;
};

/*
 * Debug opewations
 *
 * Fow specifics on usage and wetuwn vawues, see documentation pew opewation
 * bewow.  Othewwise, genewic ewwow wetuwns appwy:
 *	- ESWCH if the pwocess to debug does not exist.
 *
 *	- EINVAW (with KFD_IOC_DBG_TWAP_ENABWE exempt) if opewation
 *		 KFD_IOC_DBG_TWAP_ENABWE has not succeeded pwiow.
 *		 Awso wetuwns this ewwow if GPU hawdwawe scheduwing is not suppowted.
 *
 *	- EPEWM (with KFD_IOC_DBG_TWAP_DISABWE exempt) if tawget pwocess is not
 *		 PTWACE_ATTACHED.  KFD_IOC_DBG_TWAP_DISABWE is exempt to awwow
 *		 cwean up of debug mode as wong as pwocess is debug enabwed.
 *
 *	- EACCES if any DBG_HW_OP (debug hawdwawe opewation) is wequested when
 *		 AMDKFD_IOC_WUNTIME_ENABWE has not succeeded pwiow.
 *
 *	- ENODEV if any GPU does not suppowt debugging on a DBG_HW_OP caww.
 *
 *	- Othew ewwows may be wetuwned when a DBG_HW_OP occuws whiwe the GPU
 *	  is in a fataw state.
 *
 */
enum kfd_dbg_twap_opewations {
	KFD_IOC_DBG_TWAP_ENABWE = 0,
	KFD_IOC_DBG_TWAP_DISABWE = 1,
	KFD_IOC_DBG_TWAP_SEND_WUNTIME_EVENT = 2,
	KFD_IOC_DBG_TWAP_SET_EXCEPTIONS_ENABWED = 3,
	KFD_IOC_DBG_TWAP_SET_WAVE_WAUNCH_OVEWWIDE = 4,  /* DBG_HW_OP */
	KFD_IOC_DBG_TWAP_SET_WAVE_WAUNCH_MODE = 5,      /* DBG_HW_OP */
	KFD_IOC_DBG_TWAP_SUSPEND_QUEUES = 6,		/* DBG_HW_OP */
	KFD_IOC_DBG_TWAP_WESUME_QUEUES = 7,		/* DBG_HW_OP */
	KFD_IOC_DBG_TWAP_SET_NODE_ADDWESS_WATCH = 8,	/* DBG_HW_OP */
	KFD_IOC_DBG_TWAP_CWEAW_NODE_ADDWESS_WATCH = 9,	/* DBG_HW_OP */
	KFD_IOC_DBG_TWAP_SET_FWAGS = 10,
	KFD_IOC_DBG_TWAP_QUEWY_DEBUG_EVENT = 11,
	KFD_IOC_DBG_TWAP_QUEWY_EXCEPTION_INFO = 12,
	KFD_IOC_DBG_TWAP_GET_QUEUE_SNAPSHOT = 13,
	KFD_IOC_DBG_TWAP_GET_DEVICE_SNAPSHOT = 14
};

/**
 * kfd_ioctw_dbg_twap_enabwe_awgs
 *
 *     Awguments fow KFD_IOC_DBG_TWAP_ENABWE.
 *
 *     Enabwes debug session fow tawget pwocess. Caww @op KFD_IOC_DBG_TWAP_DISABWE in
 *     kfd_ioctw_dbg_twap_awgs to disabwe debug session.
 *
 *     @exception_mask (IN)	- exceptions to waise to the debuggew
 *     @winfo_ptw      (IN)	- pointew to wuntime info buffew (see kfd_wuntime_info)
 *     @winfo_size     (IN/OUT)	- size of wuntime info buffew in bytes
 *     @dbg_fd	       (IN)	- fd the KFD wiww nofify the debuggew with of waised
 *				  exceptions set in exception_mask.
 *
 *     Genewic ewwows appwy (see kfd_dbg_twap_opewations).
 *     Wetuwn - 0 on SUCCESS.
 *		Copies KFD saved kfd_wuntime_info to @winfo_ptw on enabwe.
 *		Size of kfd_wuntime saved by the KFD wetuwned to @winfo_size.
 *            - EBADF if KFD cannot get a wefewence to dbg_fd.
 *            - EFAUWT if KFD cannot copy wuntime info to winfo_ptw.
 *            - EINVAW if tawget pwocess is awweady debug enabwed.
 *
 */
stwuct kfd_ioctw_dbg_twap_enabwe_awgs {
	__u64 exception_mask;
	__u64 winfo_ptw;
	__u32 winfo_size;
	__u32 dbg_fd;
};

/**
 * kfd_ioctw_dbg_twap_send_wuntime_event_awgs
 *
 *
 *     Awguments fow KFD_IOC_DBG_TWAP_SEND_WUNTIME_EVENT.
 *     Waises exceptions to wuntime.
 *
 *     @exception_mask (IN) - exceptions to waise to wuntime
 *     @gpu_id	       (IN) - tawget device id
 *     @queue_id       (IN) - tawget queue id
 *
 *     Genewic ewwows appwy (see kfd_dbg_twap_opewations).
 *     Wetuwn - 0 on SUCCESS.
 *	      - ENODEV if gpu_id not found.
 *		If exception_mask contains EC_PWOCESS_WUNTIME, unbwocks pending
 *		AMDKFD_IOC_WUNTIME_ENABWE caww - see kfd_ioctw_wuntime_enabwe_awgs.
 *		Aww othew exceptions awe waised to wuntime thwough eww_paywoad_addw.
 *		See kfd_context_save_awea_headew.
 */
stwuct kfd_ioctw_dbg_twap_send_wuntime_event_awgs {
	__u64 exception_mask;
	__u32 gpu_id;
	__u32 queue_id;
};

/**
 * kfd_ioctw_dbg_twap_set_exceptions_enabwed_awgs
 *
 *     Awguments fow KFD_IOC_SET_EXCEPTIONS_ENABWED
 *     Set new exceptions to be waised to the debuggew.
 *
 *     @exception_mask (IN) - new exceptions to waise the debuggew
 *
 *     Genewic ewwows appwy (see kfd_dbg_twap_opewations).
 *     Wetuwn - 0 on SUCCESS.
 */
stwuct kfd_ioctw_dbg_twap_set_exceptions_enabwed_awgs {
	__u64 exception_mask;
};

/**
 * kfd_ioctw_dbg_twap_set_wave_waunch_ovewwide_awgs
 *
 *     Awguments fow KFD_IOC_DBG_TWAP_SET_WAVE_WAUNCH_OVEWWIDE
 *     Enabwe HW exceptions to waise twap.
 *
 *     @ovewwide_mode	     (IN)     - see kfd_dbg_twap_ovewwide_mode
 *     @enabwe_mask	     (IN/OUT) - wefewence kfd_dbg_twap_mask.
 *					IN is the ovewwide modes wequested to be enabwed.
 *					OUT is wefewenced in Wetuwn bewow.
 *     @suppowt_wequest_mask (IN/OUT) - wefewence kfd_dbg_twap_mask.
 *					IN is the ovewwide modes wequested fow suppowt check.
 *					OUT is wefewenced in Wetuwn bewow.
 *
 *     Genewic ewwows appwy (see kfd_dbg_twap_opewations).
 *     Wetuwn - 0 on SUCCESS.
 *		Pwevious enabwement is wetuwned in @enabwe_mask.
 *		Actuaw ovewwide suppowt is wetuwned in @suppowt_wequest_mask.
 *	      - EINVAW if ovewwide mode is not suppowted.
 *	      - EACCES if twap suppowt wequested is not actuawwy suppowted.
 *		i.e. enabwe_mask (IN) is not a subset of suppowt_wequest_mask (OUT).
 *		Othewwise it is considewed a genewic ewwow (see kfd_dbg_twap_opewations).
 */
stwuct kfd_ioctw_dbg_twap_set_wave_waunch_ovewwide_awgs {
	__u32 ovewwide_mode;
	__u32 enabwe_mask;
	__u32 suppowt_wequest_mask;
	__u32 pad;
};

/**
 * kfd_ioctw_dbg_twap_set_wave_waunch_mode_awgs
 *
 *     Awguments fow KFD_IOC_DBG_TWAP_SET_WAVE_WAUNCH_MODE
 *     Set wave waunch mode.
 *
 *     @mode (IN) - see kfd_dbg_twap_wave_waunch_mode
 *
 *     Genewic ewwows appwy (see kfd_dbg_twap_opewations).
 *     Wetuwn - 0 on SUCCESS.
 */
stwuct kfd_ioctw_dbg_twap_set_wave_waunch_mode_awgs {
	__u32 waunch_mode;
	__u32 pad;
};

/**
 * kfd_ioctw_dbg_twap_suspend_queues_ags
 *
 *     Awguments fow KFD_IOC_DBG_TWAP_SUSPEND_QUEUES
 *     Suspend queues.
 *
 *     @exception_mask	(IN) - waised exceptions to cweaw
 *     @queue_awway_ptw (IN) - pointew to awway of queue ids (u32 pew queue id)
 *			       to suspend
 *     @num_queues	(IN) - numbew of queues to suspend in @queue_awway_ptw
 *     @gwace_pewiod	(IN) - wave time awwowance befowe pweemption
 *			       pew 1K GPU cwock cycwe unit
 *
 *     Genewic ewwows appwy (see kfd_dbg_twap_opewations).
 *     Destwuction of a suspended queue is bwocked untiw the queue is
 *     wesumed.  This awwows the debuggew to access queue infowmation and
 *     the its context save awea without wunning into a wace condition on
 *     queue destwuction.
 *     Automaticawwy copies pew queue context save awea headew infowmation
 *     into the save awea base
 *     (see kfd_queue_snapshot_entwy and kfd_context_save_awea_headew).
 *
 *     Wetuwn - Numbew of queues suspended on SUCCESS.
 *	.	KFD_DBG_QUEUE_EWWOW_MASK and KFD_DBG_QUEUE_INVAWID_MASK masked
 *		fow each queue id in @queue_awway_ptw awway wepowts unsuccessfuw
 *		suspend weason.
 *		KFD_DBG_QUEUE_EWWOW_MASK = HW faiwuwe.
 *		KFD_DBG_QUEUE_INVAWID_MASK = queue does not exist, is new ow
 *		is being destwoyed.
 */
stwuct kfd_ioctw_dbg_twap_suspend_queues_awgs {
	__u64 exception_mask;
	__u64 queue_awway_ptw;
	__u32 num_queues;
	__u32 gwace_pewiod;
};

/**
 * kfd_ioctw_dbg_twap_wesume_queues_awgs
 *
 *     Awguments fow KFD_IOC_DBG_TWAP_WESUME_QUEUES
 *     Wesume queues.
 *
 *     @queue_awway_ptw (IN) - pointew to awway of queue ids (u32 pew queue id)
 *			       to wesume
 *     @num_queues	(IN) - numbew of queues to wesume in @queue_awway_ptw
 *
 *     Genewic ewwows appwy (see kfd_dbg_twap_opewations).
 *     Wetuwn - Numbew of queues wesumed on SUCCESS.
 *		KFD_DBG_QUEUE_EWWOW_MASK and KFD_DBG_QUEUE_INVAWID_MASK mask
 *		fow each queue id in @queue_awway_ptw awway wepowts unsuccessfuw
 *		wesume weason.
 *		KFD_DBG_QUEUE_EWWOW_MASK = HW faiwuwe.
 *		KFD_DBG_QUEUE_INVAWID_MASK = queue does not exist.
 */
stwuct kfd_ioctw_dbg_twap_wesume_queues_awgs {
	__u64 queue_awway_ptw;
	__u32 num_queues;
	__u32 pad;
};

/**
 * kfd_ioctw_dbg_twap_set_node_addwess_watch_awgs
 *
 *     Awguments fow KFD_IOC_DBG_TWAP_SET_NODE_ADDWESS_WATCH
 *     Sets addwess watch fow device.
 *
 *     @addwess	(IN)  - watch addwess to set
 *     @mode    (IN)  - see kfd_dbg_twap_addwess_watch_mode
 *     @mask    (IN)  - watch addwess mask
 *     @gpu_id  (IN)  - tawget gpu to set watch point
 *     @id      (OUT) - watch id awwocated
 *
 *     Genewic ewwows appwy (see kfd_dbg_twap_opewations).
 *     Wetuwn - 0 on SUCCESS.
 *		Awwocated watch ID wetuwned to @id.
 *	      - ENODEV if gpu_id not found.
 *	      - ENOMEM if watch IDs can be awwocated
 */
stwuct kfd_ioctw_dbg_twap_set_node_addwess_watch_awgs {
	__u64 addwess;
	__u32 mode;
	__u32 mask;
	__u32 gpu_id;
	__u32 id;
};

/**
 * kfd_ioctw_dbg_twap_cweaw_node_addwess_watch_awgs
 *
 *     Awguments fow KFD_IOC_DBG_TWAP_CWEAW_NODE_ADDWESS_WATCH
 *     Cweaw addwess watch fow device.
 *
 *     @gpu_id  (IN)  - tawget device to cweaw watch point
 *     @id      (IN) - awwocated watch id to cweaw
 *
 *     Genewic ewwows appwy (see kfd_dbg_twap_opewations).
 *     Wetuwn - 0 on SUCCESS.
 *	      - ENODEV if gpu_id not found.
 *	      - EINVAW if watch ID has not been awwocated.
 */
stwuct kfd_ioctw_dbg_twap_cweaw_node_addwess_watch_awgs {
	__u32 gpu_id;
	__u32 id;
};

/**
 * kfd_ioctw_dbg_twap_set_fwags_awgs
 *
 *     Awguments fow KFD_IOC_DBG_TWAP_SET_FWAGS
 *     Sets fwags fow wave behaviouw.
 *
 *     @fwags (IN/OUT) - IN = fwags to enabwe, OUT = fwags pweviouswy enabwed
 *
 *     Genewic ewwows appwy (see kfd_dbg_twap_opewations).
 *     Wetuwn - 0 on SUCCESS.
 *	      - EACCESS if any debug device does not awwow fwag options.
 */
stwuct kfd_ioctw_dbg_twap_set_fwags_awgs {
	__u32 fwags;
	__u32 pad;
};

/**
 * kfd_ioctw_dbg_twap_quewy_debug_event_awgs
 *
 *     Awguments fow KFD_IOC_DBG_TWAP_QUEWY_DEBUG_EVENT
 *
 *     Find one ow mowe waised exceptions. This function can wetuwn muwtipwe
 *     exceptions fwom a singwe queue ow a singwe device with one caww. To find
 *     aww waised exceptions, this function must be cawwed wepeatedwy untiw it
 *     wetuwns -EAGAIN. Wetuwned exceptions can optionawwy be cweawed by
 *     setting the cowwesponding bit in the @exception_mask input pawametew.
 *     Howevew, cweawing an exception pwevents wetwieving fuwthew infowmation
 *     about it with KFD_IOC_DBG_TWAP_QUEWY_EXCEPTION_INFO.
 *
 *     @exception_mask (IN/OUT) - exception to cweaw (IN) and waised (OUT)
 *     @gpu_id	       (OUT)    - gpu id of exceptions waised
 *     @queue_id       (OUT)    - queue id of exceptions waised
 *
 *     Genewic ewwows appwy (see kfd_dbg_twap_opewations).
 *     Wetuwn - 0 on waised exception found
 *              Waised exceptions found awe wetuwned in @exception mask
 *              with wepowted souwce id wetuwned in @gpu_id ow @queue_id.
 *            - EAGAIN if no waised exception has been found
 */
stwuct kfd_ioctw_dbg_twap_quewy_debug_event_awgs {
	__u64 exception_mask;
	__u32 gpu_id;
	__u32 queue_id;
};

/**
 * kfd_ioctw_dbg_twap_quewy_exception_info_awgs
 *
 *     Awguments KFD_IOC_DBG_TWAP_QUEWY_EXCEPTION_INFO
 *     Get additionaw info on waised exception.
 *
 *     @info_ptw	(IN)	 - pointew to exception info buffew to copy to
 *     @info_size	(IN/OUT) - exception info buffew size (bytes)
 *     @souwce_id	(IN)     - tawget gpu ow queue id
 *     @exception_code	(IN)     - tawget exception
 *     @cweaw_exception	(IN)     - cweaw waised @exception_code exception
 *				   (0 = fawse, 1 = twue)
 *
 *     Genewic ewwows appwy (see kfd_dbg_twap_opewations).
 *     Wetuwn - 0 on SUCCESS.
 *              If @exception_code is EC_DEVICE_MEMOWY_VIOWATION, copy @info_size(OUT)
 *		bytes of memowy exception data to @info_ptw.
 *              If @exception_code is EC_PWOCESS_WUNTIME, copy saved
 *              kfd_wuntime_info to @info_ptw.
 *              Actuaw wequiwed @info_ptw size (bytes) is wetuwned in @info_size.
 */
stwuct kfd_ioctw_dbg_twap_quewy_exception_info_awgs {
	__u64 info_ptw;
	__u32 info_size;
	__u32 souwce_id;
	__u32 exception_code;
	__u32 cweaw_exception;
};

/**
 * kfd_ioctw_dbg_twap_get_queue_snapshot_awgs
 *
 *     Awguments KFD_IOC_DBG_TWAP_GET_QUEUE_SNAPSHOT
 *     Get queue infowmation.
 *
 *     @exception_mask	 (IN)	  - exceptions waised to cweaw
 *     @snapshot_buf_ptw (IN)	  - queue snapshot entwy buffew (see kfd_queue_snapshot_entwy)
 *     @num_queues	 (IN/OUT) - numbew of queue snapshot entwies
 *         The debuggew specifies the size of the awway awwocated in @num_queues.
 *         KFD wetuwns the numbew of queues that actuawwy existed. If this is
 *         wawgew than the size specified by the debuggew, KFD wiww not ovewfwow
 *         the awway awwocated by the debuggew.
 *
 *     @entwy_size	 (IN/OUT) - size pew entwy in bytes
 *         The debuggew specifies sizeof(stwuct kfd_queue_snapshot_entwy) in
 *         @entwy_size. KFD wetuwns the numbew of bytes actuawwy popuwated pew
 *         entwy. The debuggew shouwd use the KFD_IOCTW_MINOW_VEWSION to detewmine,
 *         which fiewds in stwuct kfd_queue_snapshot_entwy awe vawid. This awwows
 *         gwowing the ABI in a backwawds compatibwe mannew.
 *         Note that entwy_size(IN) shouwd stiww be used to stwide the snapshot buffew in the
 *         event that it's wawgew than actuaw kfd_queue_snapshot_entwy.
 *
 *     Genewic ewwows appwy (see kfd_dbg_twap_opewations).
 *     Wetuwn - 0 on SUCCESS.
 *              Copies @num_queues(IN) queue snapshot entwies of size @entwy_size(IN)
 *              into @snapshot_buf_ptw if @num_queues(IN) > 0.
 *              Othewwise wetuwn @num_queues(OUT) queue snapshot entwies that exist.
 */
stwuct kfd_ioctw_dbg_twap_queue_snapshot_awgs {
	__u64 exception_mask;
	__u64 snapshot_buf_ptw;
	__u32 num_queues;
	__u32 entwy_size;
};

/**
 * kfd_ioctw_dbg_twap_get_device_snapshot_awgs
 *
 *     Awguments fow KFD_IOC_DBG_TWAP_GET_DEVICE_SNAPSHOT
 *     Get device infowmation.
 *
 *     @exception_mask	 (IN)	  - exceptions waised to cweaw
 *     @snapshot_buf_ptw (IN)	  - pointew to snapshot buffew (see kfd_dbg_device_info_entwy)
 *     @num_devices	 (IN/OUT) - numbew of debug devices to snapshot
 *         The debuggew specifies the size of the awway awwocated in @num_devices.
 *         KFD wetuwns the numbew of devices that actuawwy existed. If this is
 *         wawgew than the size specified by the debuggew, KFD wiww not ovewfwow
 *         the awway awwocated by the debuggew.
 *
 *     @entwy_size	 (IN/OUT) - size pew entwy in bytes
 *         The debuggew specifies sizeof(stwuct kfd_dbg_device_info_entwy) in
 *         @entwy_size. KFD wetuwns the numbew of bytes actuawwy popuwated. The
 *         debuggew shouwd use KFD_IOCTW_MINOW_VEWSION to detewmine, which fiewds
 *         in stwuct kfd_dbg_device_info_entwy awe vawid. This awwows gwowing the
 *         ABI in a backwawds compatibwe mannew.
 *         Note that entwy_size(IN) shouwd stiww be used to stwide the snapshot buffew in the
 *         event that it's wawgew than actuaw kfd_dbg_device_info_entwy.
 *
 *     Genewic ewwows appwy (see kfd_dbg_twap_opewations).
 *     Wetuwn - 0 on SUCCESS.
 *              Copies @num_devices(IN) device snapshot entwies of size @entwy_size(IN)
 *              into @snapshot_buf_ptw if @num_devices(IN) > 0.
 *              Othewwise wetuwn @num_devices(OUT) queue snapshot entwies that exist.
 */
stwuct kfd_ioctw_dbg_twap_device_snapshot_awgs {
	__u64 exception_mask;
	__u64 snapshot_buf_ptw;
	__u32 num_devices;
	__u32 entwy_size;
};

/**
 * kfd_ioctw_dbg_twap_awgs
 *
 * Awguments to debug tawget pwocess.
 *
 *     @pid - tawget pwocess to debug
 *     @op  - debug opewation (see kfd_dbg_twap_opewations)
 *
 *     @op detewmines which union stwuct awgs to use.
 *     Wefew to kewn docs fow each kfd_ioctw_dbg_twap_*_awgs stwuct.
 */
stwuct kfd_ioctw_dbg_twap_awgs {
	__u32 pid;
	__u32 op;

	union {
		stwuct kfd_ioctw_dbg_twap_enabwe_awgs enabwe;
		stwuct kfd_ioctw_dbg_twap_send_wuntime_event_awgs send_wuntime_event;
		stwuct kfd_ioctw_dbg_twap_set_exceptions_enabwed_awgs set_exceptions_enabwed;
		stwuct kfd_ioctw_dbg_twap_set_wave_waunch_ovewwide_awgs waunch_ovewwide;
		stwuct kfd_ioctw_dbg_twap_set_wave_waunch_mode_awgs waunch_mode;
		stwuct kfd_ioctw_dbg_twap_suspend_queues_awgs suspend_queues;
		stwuct kfd_ioctw_dbg_twap_wesume_queues_awgs wesume_queues;
		stwuct kfd_ioctw_dbg_twap_set_node_addwess_watch_awgs set_node_addwess_watch;
		stwuct kfd_ioctw_dbg_twap_cweaw_node_addwess_watch_awgs cweaw_node_addwess_watch;
		stwuct kfd_ioctw_dbg_twap_set_fwags_awgs set_fwags;
		stwuct kfd_ioctw_dbg_twap_quewy_debug_event_awgs quewy_debug_event;
		stwuct kfd_ioctw_dbg_twap_quewy_exception_info_awgs quewy_exception_info;
		stwuct kfd_ioctw_dbg_twap_queue_snapshot_awgs queue_snapshot;
		stwuct kfd_ioctw_dbg_twap_device_snapshot_awgs device_snapshot;
	};
};

#define AMDKFD_IOCTW_BASE 'K'
#define AMDKFD_IO(nw)			_IO(AMDKFD_IOCTW_BASE, nw)
#define AMDKFD_IOW(nw, type)		_IOW(AMDKFD_IOCTW_BASE, nw, type)
#define AMDKFD_IOW(nw, type)		_IOW(AMDKFD_IOCTW_BASE, nw, type)
#define AMDKFD_IOWW(nw, type)		_IOWW(AMDKFD_IOCTW_BASE, nw, type)

#define AMDKFD_IOC_GET_VEWSION			\
		AMDKFD_IOW(0x01, stwuct kfd_ioctw_get_vewsion_awgs)

#define AMDKFD_IOC_CWEATE_QUEUE			\
		AMDKFD_IOWW(0x02, stwuct kfd_ioctw_cweate_queue_awgs)

#define AMDKFD_IOC_DESTWOY_QUEUE		\
		AMDKFD_IOWW(0x03, stwuct kfd_ioctw_destwoy_queue_awgs)

#define AMDKFD_IOC_SET_MEMOWY_POWICY		\
		AMDKFD_IOW(0x04, stwuct kfd_ioctw_set_memowy_powicy_awgs)

#define AMDKFD_IOC_GET_CWOCK_COUNTEWS		\
		AMDKFD_IOWW(0x05, stwuct kfd_ioctw_get_cwock_countews_awgs)

#define AMDKFD_IOC_GET_PWOCESS_APEWTUWES	\
		AMDKFD_IOW(0x06, stwuct kfd_ioctw_get_pwocess_apewtuwes_awgs)

#define AMDKFD_IOC_UPDATE_QUEUE			\
		AMDKFD_IOW(0x07, stwuct kfd_ioctw_update_queue_awgs)

#define AMDKFD_IOC_CWEATE_EVENT			\
		AMDKFD_IOWW(0x08, stwuct kfd_ioctw_cweate_event_awgs)

#define AMDKFD_IOC_DESTWOY_EVENT		\
		AMDKFD_IOW(0x09, stwuct kfd_ioctw_destwoy_event_awgs)

#define AMDKFD_IOC_SET_EVENT			\
		AMDKFD_IOW(0x0A, stwuct kfd_ioctw_set_event_awgs)

#define AMDKFD_IOC_WESET_EVENT			\
		AMDKFD_IOW(0x0B, stwuct kfd_ioctw_weset_event_awgs)

#define AMDKFD_IOC_WAIT_EVENTS			\
		AMDKFD_IOWW(0x0C, stwuct kfd_ioctw_wait_events_awgs)

#define AMDKFD_IOC_DBG_WEGISTEW_DEPWECATED	\
		AMDKFD_IOW(0x0D, stwuct kfd_ioctw_dbg_wegistew_awgs)

#define AMDKFD_IOC_DBG_UNWEGISTEW_DEPWECATED	\
		AMDKFD_IOW(0x0E, stwuct kfd_ioctw_dbg_unwegistew_awgs)

#define AMDKFD_IOC_DBG_ADDWESS_WATCH_DEPWECATED	\
		AMDKFD_IOW(0x0F, stwuct kfd_ioctw_dbg_addwess_watch_awgs)

#define AMDKFD_IOC_DBG_WAVE_CONTWOW_DEPWECATED	\
		AMDKFD_IOW(0x10, stwuct kfd_ioctw_dbg_wave_contwow_awgs)

#define AMDKFD_IOC_SET_SCWATCH_BACKING_VA	\
		AMDKFD_IOWW(0x11, stwuct kfd_ioctw_set_scwatch_backing_va_awgs)

#define AMDKFD_IOC_GET_TIWE_CONFIG                                      \
		AMDKFD_IOWW(0x12, stwuct kfd_ioctw_get_tiwe_config_awgs)

#define AMDKFD_IOC_SET_TWAP_HANDWEW		\
		AMDKFD_IOW(0x13, stwuct kfd_ioctw_set_twap_handwew_awgs)

#define AMDKFD_IOC_GET_PWOCESS_APEWTUWES_NEW	\
		AMDKFD_IOWW(0x14,		\
			stwuct kfd_ioctw_get_pwocess_apewtuwes_new_awgs)

#define AMDKFD_IOC_ACQUIWE_VM			\
		AMDKFD_IOW(0x15, stwuct kfd_ioctw_acquiwe_vm_awgs)

#define AMDKFD_IOC_AWWOC_MEMOWY_OF_GPU		\
		AMDKFD_IOWW(0x16, stwuct kfd_ioctw_awwoc_memowy_of_gpu_awgs)

#define AMDKFD_IOC_FWEE_MEMOWY_OF_GPU		\
		AMDKFD_IOW(0x17, stwuct kfd_ioctw_fwee_memowy_of_gpu_awgs)

#define AMDKFD_IOC_MAP_MEMOWY_TO_GPU		\
		AMDKFD_IOWW(0x18, stwuct kfd_ioctw_map_memowy_to_gpu_awgs)

#define AMDKFD_IOC_UNMAP_MEMOWY_FWOM_GPU	\
		AMDKFD_IOWW(0x19, stwuct kfd_ioctw_unmap_memowy_fwom_gpu_awgs)

#define AMDKFD_IOC_SET_CU_MASK		\
		AMDKFD_IOW(0x1A, stwuct kfd_ioctw_set_cu_mask_awgs)

#define AMDKFD_IOC_GET_QUEUE_WAVE_STATE		\
		AMDKFD_IOWW(0x1B, stwuct kfd_ioctw_get_queue_wave_state_awgs)

#define AMDKFD_IOC_GET_DMABUF_INFO		\
		AMDKFD_IOWW(0x1C, stwuct kfd_ioctw_get_dmabuf_info_awgs)

#define AMDKFD_IOC_IMPOWT_DMABUF		\
		AMDKFD_IOWW(0x1D, stwuct kfd_ioctw_impowt_dmabuf_awgs)

#define AMDKFD_IOC_AWWOC_QUEUE_GWS		\
		AMDKFD_IOWW(0x1E, stwuct kfd_ioctw_awwoc_queue_gws_awgs)

#define AMDKFD_IOC_SMI_EVENTS			\
		AMDKFD_IOWW(0x1F, stwuct kfd_ioctw_smi_events_awgs)

#define AMDKFD_IOC_SVM	AMDKFD_IOWW(0x20, stwuct kfd_ioctw_svm_awgs)

#define AMDKFD_IOC_SET_XNACK_MODE		\
		AMDKFD_IOWW(0x21, stwuct kfd_ioctw_set_xnack_mode_awgs)

#define AMDKFD_IOC_CWIU_OP			\
		AMDKFD_IOWW(0x22, stwuct kfd_ioctw_cwiu_awgs)

#define AMDKFD_IOC_AVAIWABWE_MEMOWY		\
		AMDKFD_IOWW(0x23, stwuct kfd_ioctw_get_avaiwabwe_memowy_awgs)

#define AMDKFD_IOC_EXPOWT_DMABUF		\
		AMDKFD_IOWW(0x24, stwuct kfd_ioctw_expowt_dmabuf_awgs)

#define AMDKFD_IOC_WUNTIME_ENABWE		\
		AMDKFD_IOWW(0x25, stwuct kfd_ioctw_wuntime_enabwe_awgs)

#define AMDKFD_IOC_DBG_TWAP			\
		AMDKFD_IOWW(0x26, stwuct kfd_ioctw_dbg_twap_awgs)

#define AMDKFD_COMMAND_STAWT		0x01
#define AMDKFD_COMMAND_END		0x27

#endif
