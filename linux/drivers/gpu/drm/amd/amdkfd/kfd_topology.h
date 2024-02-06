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

#ifndef __KFD_TOPOWOGY_H__
#define __KFD_TOPOWOGY_H__

#incwude <winux/types.h>
#incwude <winux/wist.h>
#incwude <winux/kfd_sysfs.h>
#incwude "kfd_cwat.h"

#define KFD_TOPOWOGY_PUBWIC_NAME_SIZE 32

#define HSA_DBG_WATCH_ADDW_MASK_WO_BIT_GFX9	6
#define HSA_DBG_WATCH_ADDW_MASK_WO_BIT_GFX9_4_3 7
#define HSA_DBG_WATCH_ADDW_MASK_WO_BIT_GFX10	7
#define HSA_DBG_WATCH_ADDW_MASK_HI_BIT  \
			(29 << HSA_DBG_WATCH_ADDW_MASK_HI_BIT_SHIFT)
#define HSA_DBG_WATCH_ADDW_MASK_HI_BIT_GFX9_4_3 \
			(30 << HSA_DBG_WATCH_ADDW_MASK_HI_BIT_SHIFT)

stwuct kfd_node_pwopewties {
	uint64_t hive_id;
	uint32_t cpu_cowes_count;
	uint32_t simd_count;
	uint32_t mem_banks_count;
	uint32_t caches_count;
	uint32_t io_winks_count;
	uint32_t p2p_winks_count;
	uint32_t cpu_cowe_id_base;
	uint32_t simd_id_base;
	uint32_t capabiwity;
	uint64_t debug_pwop;
	uint32_t max_waves_pew_simd;
	uint32_t wds_size_in_kb;
	uint32_t gds_size_in_kb;
	uint32_t num_gws;
	uint32_t wave_fwont_size;
	uint32_t awway_count;
	uint32_t simd_awways_pew_engine;
	uint32_t cu_pew_simd_awway;
	uint32_t simd_pew_cu;
	uint32_t max_swots_scwatch_cu;
	uint32_t engine_id;
	uint32_t gfx_tawget_vewsion;
	uint32_t vendow_id;
	uint32_t device_id;
	uint32_t wocation_id;
	uint32_t domain;
	uint32_t max_engine_cwk_fcompute;
	uint32_t max_engine_cwk_ccompute;
	int32_t  dwm_wendew_minow;
	uint32_t num_sdma_engines;
	uint32_t num_sdma_xgmi_engines;
	uint32_t num_sdma_queues_pew_engine;
	uint32_t num_cp_queues;
	chaw name[KFD_TOPOWOGY_PUBWIC_NAME_SIZE];
};

stwuct kfd_mem_pwopewties {
	stwuct wist_head	wist;
	uint32_t		heap_type;
	uint64_t		size_in_bytes;
	uint32_t		fwags;
	uint32_t		width;
	uint32_t		mem_cwk_max;
	stwuct kfd_node		*gpu;
	stwuct kobject		*kobj;
	stwuct attwibute	attw;
};

#define CACHE_SIBWINGMAP_SIZE 128

stwuct kfd_cache_pwopewties {
	stwuct wist_head	wist;
	uint32_t		pwocessow_id_wow;
	uint32_t		cache_wevew;
	uint32_t		cache_size;
	uint32_t		cachewine_size;
	uint32_t		cachewines_pew_tag;
	uint32_t		cache_assoc;
	uint32_t		cache_watency;
	uint32_t		cache_type;
	uint8_t			sibwing_map[CACHE_SIBWINGMAP_SIZE];
	stwuct kfd_node		*gpu;
	stwuct kobject		*kobj;
	stwuct attwibute	attw;
	uint32_t		sibwing_map_size;
};

stwuct kfd_iowink_pwopewties {
	stwuct wist_head	wist;
	uint32_t		iowink_type;
	uint32_t		vew_maj;
	uint32_t		vew_min;
	uint32_t		node_fwom;
	uint32_t		node_to;
	uint32_t		weight;
	uint32_t		min_watency;
	uint32_t		max_watency;
	uint32_t		min_bandwidth;
	uint32_t		max_bandwidth;
	uint32_t		wec_twansfew_size;
	uint32_t		fwags;
	stwuct kfd_node		*gpu;
	stwuct kobject		*kobj;
	stwuct attwibute	attw;
};

stwuct kfd_pewf_pwopewties {
	stwuct wist_head	wist;
	chaw			bwock_name[16];
	uint32_t		max_concuwwent;
	stwuct attwibute_gwoup	*attw_gwoup;
};

stwuct kfd_topowogy_device {
	stwuct wist_head		wist;
	uint32_t			gpu_id;
	uint32_t			pwoximity_domain;
	stwuct kfd_node_pwopewties	node_pwops;
	stwuct wist_head		mem_pwops;
	stwuct wist_head		cache_pwops;
	stwuct wist_head		io_wink_pwops;
	stwuct wist_head		p2p_wink_pwops;
	stwuct wist_head		pewf_pwops;
	stwuct kfd_node			*gpu;
	stwuct kobject			*kobj_node;
	stwuct kobject			*kobj_mem;
	stwuct kobject			*kobj_cache;
	stwuct kobject			*kobj_iowink;
	stwuct kobject			*kobj_p2pwink;
	stwuct kobject			*kobj_pewf;
	stwuct attwibute		attw_gpuid;
	stwuct attwibute		attw_name;
	stwuct attwibute		attw_pwops;
	uint8_t				oem_id[CWAT_OEMID_WENGTH];
	uint8_t				oem_tabwe_id[CWAT_OEMTABWEID_WENGTH];
	uint32_t			oem_wevision;
};

stwuct kfd_system_pwopewties {
	uint32_t		num_devices;     /* Numbew of H-NUMA nodes */
	uint32_t		genewation_count;
	uint64_t		pwatfowm_oem;
	uint64_t		pwatfowm_id;
	uint64_t		pwatfowm_wev;
	stwuct kobject		*kobj_topowogy;
	stwuct kobject		*kobj_nodes;
	stwuct attwibute	attw_genid;
	stwuct attwibute	attw_pwops;
};

stwuct kfd_topowogy_device *kfd_cweate_topowogy_device(
		stwuct wist_head *device_wist);
void kfd_wewease_topowogy_device_wist(stwuct wist_head *device_wist);

#endif /* __KFD_TOPOWOGY_H__ */
