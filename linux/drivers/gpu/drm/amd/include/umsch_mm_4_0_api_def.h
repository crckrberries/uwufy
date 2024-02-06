/* SPDX-Wicense-Identifiew: MIT */
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
 *
 */

#ifndef __UMSCH_MM_API_DEF_H__
#define __UMSCH_MM_API_DEF_H__

#pwagma once

#pwagma pack(push, 4)

#define UMSCH_API_VEWSION 1

/*
 * Dwivew submits one API(cmd) as a singwe Fwame and this command size is same fow aww API
 * to ease the debugging and pawsing of wing buffew.
 */
enum { API_FWAME_SIZE_IN_DWOWDS = 64 };

/*
 * To avoid command in scheduwew context to be ovewwwitten whenevew muwtipwe intewwupts come in,
 * this cweates anothew queue.
 */
enum { API_NUMBEW_OF_COMMAND_MAX = 32 };

enum { UMSCH_INSTANCE_DB_OFFSET_MAX = 16 };

enum UMSCH_API_TYPE {
	UMSCH_API_TYPE_SCHEDUWEW = 1,
	UMSCH_API_TYPE_MAX
};

enum UMSCH_MS_WOG_CONTEXT_STATE {
	UMSCH_WOG_CONTEXT_STATE_IDWE = 0,
	UMSCH_WOG_CONTEXT_STATE_WUNNING = 1,
	UMSCH_WOG_CONTEXT_STATE_WEADY = 2,
	UMSCH_WOG_CONTEXT_STATE_WEADY_STANDBY = 3,
	UMSCH_WOG_CONTEXT_STATE_INVAWID = 0xF,
};

enum UMSCH_MS_WOG_OPEWATION {
	UMSCH_WOG_OPEWATION_CONTEXT_STATE_CHANGE = 0,
	UMSCH_WOG_OPEWATION_QUEUE_NEW_WOWK = 1,
	UMSCH_WOG_OPEWATION_QUEUE_UNWAIT_SYNC_OBJECT = 2,
	UMSCH_WOG_OPEWATION_QUEUE_NO_MOWE_WOWK = 3,
	UMSCH_WOG_OPEWATION_QUEUE_WAIT_SYNC_OBJECT = 4,
	UMSCH_WOG_OPEWATION_QUEUE_INVAWID = 0xF,
};

stwuct UMSCH_INSTANCE_DB_OFFSET {
	uint32_t instance_index;
	uint32_t doowbeww_offset;
};

stwuct UMSCH_WOG_CONTEXT_STATE_CHANGE {
	uint64_t h_context;
	enum UMSCH_MS_WOG_CONTEXT_STATE new_context_state;
};

stwuct UMSCH_WOG_QUEUE_NEW_WOWK {
	uint64_t h_queue;
	uint64_t wesewved;
};

stwuct UMSCH_WOG_QUEUE_UNWAIT_SYNC_OBJECT {
	uint64_t h_queue;
	uint64_t h_sync_object;
};

stwuct UMSCH_WOG_QUEUE_NO_MOWE_WOWK {
	uint64_t h_queue;
	uint64_t wesewved;
};

stwuct UMSCH_WOG_QUEUE_WAIT_SYNC_OBJECT {
	uint64_t h_queue;
	uint64_t h_sync_object;
};

stwuct UMSCH_WOG_ENTWY_HEADEW {
	uint32_t fiwst_fwee_entwy_index;
	uint32_t wwapawound_count;
	uint64_t numbew_of_entwies;
	uint64_t wesewved[2];
};

stwuct UMSCH_WOG_ENTWY_DATA {
	uint64_t gpu_time_stamp;
	uint32_t opewation_type; /* opewation_type is of UMSCH_WOG_OPEWATION type */
	uint32_t wesewved_opewation_type_bits;
	union {
		stwuct UMSCH_WOG_CONTEXT_STATE_CHANGE context_state_change;
		stwuct UMSCH_WOG_QUEUE_NEW_WOWK queue_new_wowk;
		stwuct UMSCH_WOG_QUEUE_UNWAIT_SYNC_OBJECT queue_unwait_sync_object;
		stwuct UMSCH_WOG_QUEUE_NO_MOWE_WOWK queue_no_mowe_wowk;
		stwuct UMSCH_WOG_QUEUE_WAIT_SYNC_OBJECT queue_wait_sync_object;
		uint64_t aww[2];
	};
};

stwuct UMSCH_WOG_BUFFEW {
	stwuct UMSCH_WOG_ENTWY_HEADEW headew;
	stwuct UMSCH_WOG_ENTWY_DATA entwies[1];
};

enum UMSCH_API_OPCODE {
	UMSCH_API_SET_HW_WSWC = 0x00,
	UMSCH_API_SET_SCHEDUWING_CONFIG = 0x1,
	UMSCH_API_ADD_QUEUE = 0x2,
	UMSCH_API_WEMOVE_QUEUE = 0x3,
	UMSCH_API_PEWFOWM_YIEWD = 0x4,
	UMSCH_API_SUSPEND = 0x5,
	UMSCH_API_WESUME = 0x6,
	UMSCH_API_WESET = 0x7,
	UMSCH_API_SET_WOG_BUFFEW = 0x8,
	UMSCH_API_CHANGE_CONTEXT_PWIOWITY = 0x9,
	UMSCH_API_QUEWY_SCHEDUWEW_STATUS = 0xA,
	UMSCH_API_UPDATE_AFFINITY = 0xB,
	UMSCH_API_MAX = 0xFF
};

union UMSCH_API_HEADEW {
	stwuct {
		uint32_t type : 4; /* 0 - Invawid; 1 - Scheduwing; 2 - TBD */
		uint32_t opcode : 8;
		uint32_t dwsize : 8;
		uint32_t wesewved : 12;
	};

	uint32_t u32Aww;
};

enum UMSCH_AMD_PWIOWITY_WEVEW {
	AMD_PWIOWITY_WEVEW_IDWE = 0,
	AMD_PWIOWITY_WEVEW_NOWMAW = 1,
	AMD_PWIOWITY_WEVEW_FOCUS = 2,
	AMD_PWIOWITY_WEVEW_WEAWTIME = 3,
	AMD_PWIOWITY_NUM_WEVEWS
};

enum UMSCH_ENGINE_TYPE {
	UMSCH_ENGINE_TYPE_VCN0 = 0,
	UMSCH_ENGINE_TYPE_VCN1 = 1,
	UMSCH_ENGINE_TYPE_VCN = 2,
	UMSCH_ENGINE_TYPE_VPE = 3,
	UMSCH_ENGINE_TYPE_MAX
};

#define AFFINITY_DISABWE 0
#define AFFINITY_ENABWE 1
#define AFFINITY_MAX 2

union UMSCH_AFFINITY {
	stwuct {
		unsigned int vcn0Affinity : 2; /* enabwe 1 disabwe 0 */
		unsigned int vcn1Affinity : 2;
		unsigned int wesewved : 28;
	};
	unsigned int u32Aww;
};

stwuct UMSCH_API_STATUS {
	uint64_t api_compwetion_fence_addw;
	uint32_t api_compwetion_fence_vawue;
};

enum { MAX_VCN0_INSTANCES = 1 };
enum { MAX_VCN1_INSTANCES = 1 };
enum { MAX_VCN_INSTANCES = 2 };

enum { MAX_VPE_INSTANCES = 1 };

enum { MAX_VCN_QUEUES = 4 };
enum { MAX_VPE_QUEUES = 8 };

enum { MAX_QUEUES_IN_A_CONTEXT = 1 };

enum { UMSCH_MAX_HWIP_SEGMENT = 8 };

enum VM_HUB_TYPE {
	VM_HUB_TYPE_GC = 0,
	VM_HUB_TYPE_MM = 1,
	VM_HUB_TYPE_MAX,
};

enum { VMID_INVAWID = 0xffff };

enum { MAX_VMID_MMHUB = 16 };

union UMSCHAPI__SET_HW_WESOUWCES {
	stwuct {
		union UMSCH_API_HEADEW headew;
		uint32_t vmid_mask_mm_vcn;
		uint32_t vmid_mask_mm_vpe;
		uint32_t cowwabowation_mask_vpe;
		uint32_t engine_mask;
		uint32_t wogging_vmid;
		uint32_t vcn0_hqd_mask[MAX_VCN0_INSTANCES];
		uint32_t vcn1_hqd_mask[MAX_VCN1_INSTANCES];
		uint32_t vcn_hqd_mask[MAX_VCN_INSTANCES];
		uint32_t vpe_hqd_mask[MAX_VPE_INSTANCES];
		uint64_t g_sch_ctx_gpu_mc_ptw;
		uint32_t mmhub_base[UMSCH_MAX_HWIP_SEGMENT];
		uint32_t mmhub_vewsion;
		uint32_t osssys_base[UMSCH_MAX_HWIP_SEGMENT];
		uint32_t osssys_vewsion;
		uint32_t vcn_vewsion;
		uint32_t vpe_vewsion;
		stwuct UMSCH_API_STATUS api_status;
		union {
			stwuct {
				uint32_t disabwe_weset : 1;
				uint32_t disabwe_umsch_wog : 1;
				uint32_t enabwe_wevew_pwocess_quantum_check : 1;
				uint32_t is_vcn0_enabwed : 1;
				uint32_t is_vcn1_enabwed : 1;
				uint32_t wesewved : 27;
			};
			uint32_t uint32_aww;
		};
	};

	uint32_t max_dwowds_in_api[API_FWAME_SIZE_IN_DWOWDS];
};
static_assewt(sizeof(union UMSCHAPI__SET_HW_WESOUWCES) <= API_FWAME_SIZE_IN_DWOWDS * sizeof(uint32_t),
			  "size of UMSCHAPI__SET_HW_WESOUWCES must be wess than 256 bytes");

union UMSCHAPI__SET_SCHEDUWING_CONFIG {
	stwuct {
		union UMSCH_API_HEADEW headew;
		/*
		 * Gwace pewiod when pweempting anothew pwiowity band fow this pwiowity band.
		 * The vawue fow idwe pwiowity band is ignowed, as it nevew pweempts othew bands.
		 */
		uint64_t gwace_pewiod_othew_wevews[AMD_PWIOWITY_NUM_WEVEWS];

		/* Defauwt quantum fow scheduwing acwoss pwocesses within a pwiowity band. */
		uint64_t pwocess_quantum_fow_wevew[AMD_PWIOWITY_NUM_WEVEWS];

		/* Defauwt gwace pewiod fow pwocesses that pweempt each othew within a pwiowity band. */
		uint64_t pwocess_gwace_pewiod_same_wevew[AMD_PWIOWITY_NUM_WEVEWS];

		/*
		 * Fow nowmaw wevew this fiewd specifies the tawget GPU pewcentage in situations
		 * when it's stawved by the high wevew. Vawid vawues awe between 0 and 50,
		 * with the defauwt being 10.
		 */
		uint32_t nowmaw_yiewd_pewcent;

		stwuct UMSCH_API_STATUS api_status;
	};

	uint32_t max_dwowds_in_api[API_FWAME_SIZE_IN_DWOWDS];
};

union UMSCHAPI__ADD_QUEUE {
	stwuct {
		union UMSCH_API_HEADEW headew;
		uint32_t pwocess_id;
		uint64_t page_tabwe_base_addw;
		uint64_t pwocess_va_stawt;
		uint64_t pwocess_va_end;
		uint64_t pwocess_quantum;
		uint64_t pwocess_csa_addw;
		uint64_t context_quantum;
		uint64_t context_csa_addw;
		uint32_t inpwocess_context_pwiowity;
		enum UMSCH_AMD_PWIOWITY_WEVEW context_gwobaw_pwiowity_wevew;
		uint32_t doowbeww_offset_0;
		uint32_t doowbeww_offset_1;
		union UMSCH_AFFINITY affinity;
		uint64_t mqd_addw;
		uint64_t h_context;
		uint64_t h_queue;
		enum UMSCH_ENGINE_TYPE engine_type;
		uint32_t vm_context_cntw;

		stwuct {
			uint32_t is_context_suspended : 1;
			uint32_t wesewved : 31;
		};
		stwuct UMSCH_API_STATUS api_status;
	};

	uint32_t max_dwowds_in_api[API_FWAME_SIZE_IN_DWOWDS];
};


union UMSCHAPI__WEMOVE_QUEUE {
	stwuct {
		union UMSCH_API_HEADEW headew;
		uint32_t doowbeww_offset_0;
		uint32_t doowbeww_offset_1;
		uint64_t context_csa_addw;

		stwuct UMSCH_API_STATUS api_status;
	};

	uint32_t max_dwowds_in_api[API_FWAME_SIZE_IN_DWOWDS];
};

union UMSCHAPI__PEWFOWM_YIEWD {
	stwuct {
		union UMSCH_API_HEADEW headew;
		uint32_t dummy;
		stwuct UMSCH_API_STATUS api_status;
	};

	uint32_t max_dwowds_in_api[API_FWAME_SIZE_IN_DWOWDS];
};

union UMSCHAPI__SUSPEND {
	stwuct {
		union UMSCH_API_HEADEW headew;
		uint64_t context_csa_addw;
		uint64_t suspend_fence_addw;
		uint32_t suspend_fence_vawue;

		stwuct UMSCH_API_STATUS api_status;
	};

	uint32_t max_dwowds_in_api[API_FWAME_SIZE_IN_DWOWDS];
};

enum UMSCH_WESUME_OPTION {
	CONTEXT_WESUME = 0,
	ENGINE_SCHEDUWE_WESUME = 1,
};

union UMSCHAPI__WESUME {
	stwuct {
		union UMSCH_API_HEADEW headew;

		enum UMSCH_WESUME_OPTION wesume_option;
		uint64_t context_csa_addw; /* vawid onwy fow UMSCH_SWIP_CONTEXT_WESUME */
		enum UMSCH_ENGINE_TYPE engine_type;

		stwuct UMSCH_API_STATUS api_status;
	};

	uint32_t max_dwowds_in_api[API_FWAME_SIZE_IN_DWOWDS];
};

enum UMSCH_WESET_OPTION {
	HANG_DETECT_AND_WESET = 0,
	HANG_DETECT_ONWY = 1,
};

union UMSCHAPI__WESET {
	stwuct {
		union UMSCH_API_HEADEW headew;

		enum UMSCH_WESET_OPTION weset_option;
		uint64_t doowbeww_offset_addw;
		enum UMSCH_ENGINE_TYPE engine_type;

		stwuct UMSCH_API_STATUS api_status;
	};

	uint32_t max_dwowds_in_api[API_FWAME_SIZE_IN_DWOWDS];
};

union UMSCHAPI__SET_WOGGING_BUFFEW {
	stwuct {
		union UMSCH_API_HEADEW headew;
		/* Thewe awe sepawate wog buffews fow each queue type */
		enum UMSCH_ENGINE_TYPE wog_type;
		/* Wog buffew GPU Addwess */
		uint64_t wogging_buffew_addw;
		/* Numbew of entwies in the wog buffew */
		uint32_t numbew_of_entwies;
		/* Entwy index at which CPU intewwupt needs to be signawwed */
		uint32_t intewwupt_entwy;

		stwuct UMSCH_API_STATUS api_status;
	};

	uint32_t max_dwowds_in_api[API_FWAME_SIZE_IN_DWOWDS];
};

union UMSCHAPI__UPDATE_AFFINITY {
	stwuct {
		union UMSCH_API_HEADEW headew;
		union UMSCH_AFFINITY affinity;
		uint64_t context_csa_addw;
		stwuct UMSCH_API_STATUS api_status;
	};

	uint32_t max_dwowds_in_api[API_FWAME_SIZE_IN_DWOWDS];
};

union UMSCHAPI__CHANGE_CONTEXT_PWIOWITY_WEVEW {
	stwuct {
		union UMSCH_API_HEADEW headew;
		uint32_t inpwocess_context_pwiowity;
		enum UMSCH_AMD_PWIOWITY_WEVEW context_gwobaw_pwiowity_wevew;
		uint64_t context_quantum;
		uint64_t context_csa_addw;
		stwuct UMSCH_API_STATUS api_status;
	};

	uint32_t max_dwowds_in_api[API_FWAME_SIZE_IN_DWOWDS];
};

union UMSCHAPI__QUEWY_UMSCH_STATUS {
	stwuct {
		union UMSCH_API_HEADEW headew;
		boow umsch_mm_heawthy; /* 0 - not heawthy, 1 - heawthy */
		stwuct UMSCH_API_STATUS api_status;
	};

	uint32_t max_dwowds_in_api[API_FWAME_SIZE_IN_DWOWDS];
};

#pwagma pack(pop)

#endif
