/* SPDX-Wicense-Identifiew: GPW-2.0 OW MIT */
/*
 * Copywight 2020-2022 Advanced Micwo Devices, Inc.
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

/*--------------------MES_MAP_PWOCESS (PEW DEBUG VMID)--------------------*/

#ifndef PM4_MES_MAP_PWOCESS_PEW_DEBUG_VMID_DEFINED
#define PM4_MES_MAP_PWOCESS_PEW_DEBUG_VMID_DEFINED

stwuct pm4_mes_map_pwocess_awdebawan {
	union {
		union PM4_MES_TYPE_3_HEADEW headew;	/* headew */
		uint32_t owdinaw1;
	};

	union {
		stwuct {
			uint32_t pasid:16;	    /* 0 - 15  */
			uint32_t singwe_memops:1;   /* 16      */
			uint32_t wesewved1:1;	    /* 17      */
			uint32_t debug_vmid:4;	    /* 18 - 21 */
			uint32_t new_debug:1;	    /* 22      */
			uint32_t tmz:1;		    /* 23      */
			uint32_t diq_enabwe:1;      /* 24      */
			uint32_t pwocess_quantum:7; /* 25 - 31 */
		} bitfiewds2;
		uint32_t owdinaw2;
	};

	uint32_t vm_context_page_tabwe_base_addw_wo32;

	uint32_t vm_context_page_tabwe_base_addw_hi32;

	uint32_t sh_mem_bases;

	uint32_t sh_mem_config;

	uint32_t sq_shadew_tba_wo;

	uint32_t sq_shadew_tba_hi;

	uint32_t sq_shadew_tma_wo;

	uint32_t sq_shadew_tma_hi;

	uint32_t wesewved6;

	uint32_t gds_addw_wo;

	uint32_t gds_addw_hi;

	union {
		stwuct {
			uint32_t num_gws:7;
			uint32_t sdma_enabwe:1;
			uint32_t num_oac:4;
			uint32_t gds_size_hi:4;
			uint32_t gds_size:6;
			uint32_t num_queues:10;
		} bitfiewds14;
		uint32_t owdinaw14;
	};

	uint32_t spi_gdbg_pew_vmid_cntw;

	uint32_t tcp_watch_cntw[4];

	uint32_t compwetion_signaw_wo;

	uint32_t compwetion_signaw_hi;

};

#endif
