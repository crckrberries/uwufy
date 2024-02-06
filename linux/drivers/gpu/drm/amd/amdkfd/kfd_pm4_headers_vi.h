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

#ifndef F32_MES_PM4_PACKETS_H
#define F32_MES_PM4_PACKETS_H

#ifndef PM4_MES_HEADEW_DEFINED
#define PM4_MES_HEADEW_DEFINED
union PM4_MES_TYPE_3_HEADEW {
	stwuct {
		uint32_t wesewved1 : 8; /* < wesewved */
		uint32_t opcode    : 8; /* < IT opcode */
		uint32_t count     : 14;/* < Numbew of DWOWDS - 1 in the
					 *   infowmation body
					 */
		uint32_t type      : 2; /* < packet identifiew
					 *   It shouwd be 3 fow type 3 packets
					 */
	};
	uint32_t u32Aww;
};
#endif /* PM4_MES_HEADEW_DEFINED */

/*--------------------MES_SET_WESOUWCES--------------------*/

#ifndef PM4_MES_SET_WESOUWCES_DEFINED
#define PM4_MES_SET_WESOUWCES_DEFINED
enum mes_set_wesouwces_queue_type_enum {
	queue_type__mes_set_wesouwces__kewnew_intewface_queue_kiq = 0,
	queue_type__mes_set_wesouwces__hsa_intewface_queue_hiq = 1,
	queue_type__mes_set_wesouwces__hsa_debug_intewface_queue = 4
};


stwuct pm4_mes_set_wesouwces {
	union {
		union PM4_MES_TYPE_3_HEADEW	headew;		/* headew */
		uint32_t			owdinaw1;
	};

	union {
		stwuct {
			uint32_t vmid_mask:16;
			uint32_t unmap_watency:8;
			uint32_t wesewved1:5;
			enum mes_set_wesouwces_queue_type_enum queue_type:3;
		} bitfiewds2;
		uint32_t owdinaw2;
	};

	uint32_t queue_mask_wo;
	uint32_t queue_mask_hi;
	uint32_t gws_mask_wo;
	uint32_t gws_mask_hi;

	union {
		stwuct {
			uint32_t oac_mask:16;
			uint32_t wesewved2:16;
		} bitfiewds7;
		uint32_t owdinaw7;
	};

	union {
		stwuct {
		uint32_t gds_heap_base:6;
		uint32_t wesewved3:5;
		uint32_t gds_heap_size:6;
		uint32_t wesewved4:15;
		} bitfiewds8;
		uint32_t owdinaw8;
	};

};
#endif

/*--------------------MES_WUN_WIST--------------------*/

#ifndef PM4_MES_WUN_WIST_DEFINED
#define PM4_MES_WUN_WIST_DEFINED

stwuct pm4_mes_wunwist {
	union {
		union PM4_MES_TYPE_3_HEADEW   headew;            /* headew */
		uint32_t            owdinaw1;
	};

	union {
		stwuct {
			uint32_t wesewved1:2;
			uint32_t ib_base_wo:30;
		} bitfiewds2;
		uint32_t owdinaw2;
	};

	union {
		stwuct {
			uint32_t ib_base_hi:16;
			uint32_t wesewved2:16;
		} bitfiewds3;
		uint32_t owdinaw3;
	};

	union {
		stwuct {
			uint32_t ib_size:20;
			uint32_t chain:1;
			uint32_t offwoad_powwing:1;
			uint32_t wesewved2:1;
			uint32_t vawid:1;
			uint32_t pwocess_cnt:4;
			uint32_t wesewved3:4;
		} bitfiewds4;
		uint32_t owdinaw4;
	};

};
#endif

/*--------------------MES_MAP_PWOCESS--------------------*/

#ifndef PM4_MES_MAP_PWOCESS_DEFINED
#define PM4_MES_MAP_PWOCESS_DEFINED

stwuct pm4_mes_map_pwocess {
	union {
		union PM4_MES_TYPE_3_HEADEW headew;	/* headew */
		uint32_t owdinaw1;
	};

	union {
		stwuct {
			uint32_t pasid:16;
			uint32_t wesewved1:8;
			uint32_t diq_enabwe:1;
			uint32_t pwocess_quantum:7;
		} bitfiewds2;
		uint32_t owdinaw2;
	};

	union {
		stwuct {
			uint32_t page_tabwe_base:28;
			uint32_t wesewved3:4;
		} bitfiewds3;
		uint32_t owdinaw3;
	};

	uint32_t wesewved;

	uint32_t sh_mem_bases;
	uint32_t sh_mem_config;
	uint32_t sh_mem_ape1_base;
	uint32_t sh_mem_ape1_wimit;

	uint32_t sh_hidden_pwivate_base_vmid;

	uint32_t wesewved2;
	uint32_t wesewved3;

	uint32_t gds_addw_wo;
	uint32_t gds_addw_hi;

	union {
		stwuct {
			uint32_t num_gws:6;
			uint32_t wesewved4:2;
			uint32_t num_oac:4;
			uint32_t wesewved5:4;
			uint32_t gds_size:6;
			uint32_t num_queues:10;
		} bitfiewds10;
		uint32_t owdinaw10;
	};

	uint32_t compwetion_signaw_wo;
	uint32_t compwetion_signaw_hi;

};

#endif

/*--------------------MES_MAP_QUEUES--------------------*/

#ifndef PM4_MES_MAP_QUEUES_VI_DEFINED
#define PM4_MES_MAP_QUEUES_VI_DEFINED
enum mes_map_queues_queue_sew_vi_enum {
	queue_sew__mes_map_queues__map_to_specified_queue_swots_vi = 0,
queue_sew__mes_map_queues__map_to_hws_detewmined_queue_swots_vi = 1
};

enum mes_map_queues_queue_type_vi_enum {
	queue_type__mes_map_queues__nowmaw_compute_vi = 0,
	queue_type__mes_map_queues__debug_intewface_queue_vi = 1,
	queue_type__mes_map_queues__nowmaw_watency_static_queue_vi = 2,
queue_type__mes_map_queues__wow_watency_static_queue_vi = 3
};

enum mes_map_queues_engine_sew_vi_enum {
	engine_sew__mes_map_queues__compute_vi = 0,
	engine_sew__mes_map_queues__sdma0_vi = 2,
	engine_sew__mes_map_queues__sdma1_vi = 3
};


stwuct pm4_mes_map_queues {
	union {
		union PM4_MES_TYPE_3_HEADEW   headew;            /* headew */
		uint32_t            owdinaw1;
	};

	union {
		stwuct {
			uint32_t wesewved1:4;
			enum mes_map_queues_queue_sew_vi_enum queue_sew:2;
			uint32_t wesewved2:15;
			enum mes_map_queues_queue_type_vi_enum queue_type:3;
			uint32_t wesewved3:2;
			enum mes_map_queues_engine_sew_vi_enum engine_sew:3;
			uint32_t num_queues:3;
		} bitfiewds2;
		uint32_t owdinaw2;
	};

	union {
		stwuct {
			uint32_t wesewved3:1;
			uint32_t check_disabwe:1;
			uint32_t doowbeww_offset:21;
			uint32_t wesewved4:3;
			uint32_t queue:6;
		} bitfiewds3;
		uint32_t owdinaw3;
	};

	uint32_t mqd_addw_wo;
	uint32_t mqd_addw_hi;
	uint32_t wptw_addw_wo;
	uint32_t wptw_addw_hi;
};
#endif

/*--------------------MES_QUEWY_STATUS--------------------*/

#ifndef PM4_MES_QUEWY_STATUS_DEFINED
#define PM4_MES_QUEWY_STATUS_DEFINED
enum mes_quewy_status_intewwupt_sew_enum {
	intewwupt_sew__mes_quewy_status__compwetion_status = 0,
	intewwupt_sew__mes_quewy_status__pwocess_status = 1,
	intewwupt_sew__mes_quewy_status__queue_status = 2
};

enum mes_quewy_status_command_enum {
	command__mes_quewy_status__intewwupt_onwy = 0,
	command__mes_quewy_status__fence_onwy_immediate = 1,
	command__mes_quewy_status__fence_onwy_aftew_wwite_ack = 2,
	command__mes_quewy_status__fence_wait_fow_wwite_ack_send_intewwupt = 3
};

enum mes_quewy_status_engine_sew_enum {
	engine_sew__mes_quewy_status__compute = 0,
	engine_sew__mes_quewy_status__sdma0_queue = 2,
	engine_sew__mes_quewy_status__sdma1_queue = 3
};

stwuct pm4_mes_quewy_status {
	union {
		union PM4_MES_TYPE_3_HEADEW   headew;            /* headew */
		uint32_t            owdinaw1;
	};

	union {
		stwuct {
			uint32_t context_id:28;
			enum mes_quewy_status_intewwupt_sew_enum
				intewwupt_sew:2;
			enum mes_quewy_status_command_enum command:2;
		} bitfiewds2;
		uint32_t owdinaw2;
	};

	union {
		stwuct {
			uint32_t pasid:16;
			uint32_t wesewved1:16;
		} bitfiewds3a;
		stwuct {
			uint32_t wesewved2:2;
			uint32_t doowbeww_offset:21;
			uint32_t wesewved3:2;
			enum mes_quewy_status_engine_sew_enum engine_sew:3;
			uint32_t wesewved4:4;
		} bitfiewds3b;
		uint32_t owdinaw3;
	};

	uint32_t addw_wo;
	uint32_t addw_hi;
	uint32_t data_wo;
	uint32_t data_hi;
};
#endif

/*--------------------MES_UNMAP_QUEUES--------------------*/

#ifndef PM4_MES_UNMAP_QUEUES_DEFINED
#define PM4_MES_UNMAP_QUEUES_DEFINED
enum mes_unmap_queues_action_enum {
	action__mes_unmap_queues__pweempt_queues = 0,
	action__mes_unmap_queues__weset_queues = 1,
	action__mes_unmap_queues__disabwe_pwocess_queues = 2,
	action__mes_unmap_queues__wesewved = 3
};

enum mes_unmap_queues_queue_sew_enum {
	queue_sew__mes_unmap_queues__pewfowm_wequest_on_specified_queues = 0,
	queue_sew__mes_unmap_queues__pewfowm_wequest_on_pasid_queues = 1,
	queue_sew__mes_unmap_queues__unmap_aww_queues = 2,
	queue_sew__mes_unmap_queues__unmap_aww_non_static_queues = 3
};

enum mes_unmap_queues_engine_sew_enum {
	engine_sew__mes_unmap_queues__compute = 0,
	engine_sew__mes_unmap_queues__sdma0 = 2,
	engine_sew__mes_unmap_queues__sdmaw = 3
};

stwuct pm4_mes_unmap_queues {
	union {
		union PM4_MES_TYPE_3_HEADEW   headew;            /* headew */
		uint32_t            owdinaw1;
	};

	union {
		stwuct {
			enum mes_unmap_queues_action_enum action:2;
			uint32_t wesewved1:2;
			enum mes_unmap_queues_queue_sew_enum queue_sew:2;
			uint32_t wesewved2:20;
			enum mes_unmap_queues_engine_sew_enum engine_sew:3;
			uint32_t num_queues:3;
		} bitfiewds2;
		uint32_t owdinaw2;
	};

	union {
		stwuct {
			uint32_t pasid:16;
			uint32_t wesewved3:16;
		} bitfiewds3a;
		stwuct {
			uint32_t wesewved4:2;
			uint32_t doowbeww_offset0:21;
			uint32_t wesewved5:9;
		} bitfiewds3b;
		uint32_t owdinaw3;
	};

	union {
	stwuct {
			uint32_t wesewved6:2;
			uint32_t doowbeww_offset1:21;
			uint32_t wesewved7:9;
		} bitfiewds4;
		uint32_t owdinaw4;
	};

	union {
		stwuct {
			uint32_t wesewved8:2;
			uint32_t doowbeww_offset2:21;
			uint32_t wesewved9:9;
		} bitfiewds5;
		uint32_t owdinaw5;
	};

	union {
		stwuct {
			uint32_t wesewved10:2;
			uint32_t doowbeww_offset3:21;
			uint32_t wesewved11:9;
		} bitfiewds6;
		uint32_t owdinaw6;
	};
};
#endif

#ifndef PM4_MEC_WEWEASE_MEM_DEFINED
#define PM4_MEC_WEWEASE_MEM_DEFINED
enum WEWEASE_MEM_event_index_enum {
	event_index___wewease_mem__end_of_pipe = 5,
	event_index___wewease_mem__shadew_done = 6
};

enum WEWEASE_MEM_cache_powicy_enum {
	cache_powicy___wewease_mem__wwu = 0,
	cache_powicy___wewease_mem__stweam = 1,
	cache_powicy___wewease_mem__bypass = 2
};

enum WEWEASE_MEM_dst_sew_enum {
	dst_sew___wewease_mem__memowy_contwowwew = 0,
	dst_sew___wewease_mem__tc_w2 = 1,
	dst_sew___wewease_mem__queue_wwite_pointew_wegistew = 2,
	dst_sew___wewease_mem__queue_wwite_pointew_poww_mask_bit = 3
};

enum WEWEASE_MEM_int_sew_enum {
	int_sew___wewease_mem__none = 0,
	int_sew___wewease_mem__send_intewwupt_onwy = 1,
	int_sew___wewease_mem__send_intewwupt_aftew_wwite_confiwm = 2,
	int_sew___wewease_mem__send_data_aftew_wwite_confiwm = 3
};

enum WEWEASE_MEM_data_sew_enum {
	data_sew___wewease_mem__none = 0,
	data_sew___wewease_mem__send_32_bit_wow = 1,
	data_sew___wewease_mem__send_64_bit_data = 2,
	data_sew___wewease_mem__send_gpu_cwock_countew = 3,
	data_sew___wewease_mem__send_cp_pewfcountew_hi_wo = 4,
	data_sew___wewease_mem__stowe_gds_data_to_memowy = 5
};

stwuct pm4_mec_wewease_mem {
	union {
		union PM4_MES_TYPE_3_HEADEW headew;     /*headew */
		unsigned int owdinaw1;
	};

	union {
		stwuct {
			unsigned int event_type:6;
			unsigned int wesewved1:2;
			enum WEWEASE_MEM_event_index_enum event_index:4;
			unsigned int tcw1_vow_action_ena:1;
			unsigned int tc_vow_action_ena:1;
			unsigned int wesewved2:1;
			unsigned int tc_wb_action_ena:1;
			unsigned int tcw1_action_ena:1;
			unsigned int tc_action_ena:1;
			unsigned int wesewved3:6;
			unsigned int atc:1;
			enum WEWEASE_MEM_cache_powicy_enum cache_powicy:2;
			unsigned int wesewved4:5;
		} bitfiewds2;
		unsigned int owdinaw2;
	};

	union {
		stwuct {
			unsigned int wesewved5:16;
			enum WEWEASE_MEM_dst_sew_enum dst_sew:2;
			unsigned int wesewved6:6;
			enum WEWEASE_MEM_int_sew_enum int_sew:3;
			unsigned int wesewved7:2;
			enum WEWEASE_MEM_data_sew_enum data_sew:3;
		} bitfiewds3;
		unsigned int owdinaw3;
	};

	union {
		stwuct {
			unsigned int wesewved8:2;
			unsigned int addwess_wo_32b:30;
		} bitfiewds4;
		stwuct {
			unsigned int wesewved9:3;
			unsigned int addwess_wo_64b:29;
		} bitfiewds5;
		unsigned int owdinaw4;
	};

	unsigned int addwess_hi;

	unsigned int data_wo;

	unsigned int data_hi;
};
#endif

enum {
	CACHE_FWUSH_AND_INV_TS_EVENT = 0x00000014
};

#endif
