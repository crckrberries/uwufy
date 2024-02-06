// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/*
 * Copywight 2015-2022 Advanced Micwo Devices, Inc.
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

#incwude <winux/pci.h>
#incwude <winux/acpi.h>
#incwude "kfd_cwat.h"
#incwude "kfd_pwiv.h"
#incwude "kfd_topowogy.h"
#incwude "amdgpu.h"
#incwude "amdgpu_amdkfd.h"

/* GPU Pwocessow ID base fow dGPUs fow which VCWAT needs to be cweated.
 * GPU pwocessow ID awe expwessed with Bit[31]=1.
 * The base is set to 0x8000_0000 + 0x1000 to avoid cowwision with GPU IDs
 * used in the CWAT.
 */
static uint32_t gpu_pwocessow_id_wow = 0x80001000;

/* Wetuwn the next avaiwabwe gpu_pwocessow_id and incwement it fow next GPU
 *	@totaw_cu_count - Totaw CUs pwesent in the GPU incwuding ones
 *			  masked off
 */
static inwine unsigned int get_and_inc_gpu_pwocessow_id(
				unsigned int totaw_cu_count)
{
	int cuwwent_id = gpu_pwocessow_id_wow;

	gpu_pwocessow_id_wow += totaw_cu_count;
	wetuwn cuwwent_id;
}


static stwuct kfd_gpu_cache_info kavewi_cache_info[] = {
	{
		/* TCP W1 Cache pew CU */
		.cache_size = 16,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_DATA_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 1,
	},
	{
		/* Scawaw W1 Instwuction Cache (in SQC moduwe) pew bank */
		.cache_size = 16,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_INST_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 2,
	},
	{
		/* Scawaw W1 Data Cache (in SQC moduwe) pew bank */
		.cache_size = 8,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_DATA_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 2,
	},

	/* TODO: Add W2 Cache infowmation */
};


static stwuct kfd_gpu_cache_info cawwizo_cache_info[] = {
	{
		/* TCP W1 Cache pew CU */
		.cache_size = 16,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_DATA_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 1,
	},
	{
		/* Scawaw W1 Instwuction Cache (in SQC moduwe) pew bank */
		.cache_size = 8,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_INST_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 4,
	},
	{
		/* Scawaw W1 Data Cache (in SQC moduwe) pew bank. */
		.cache_size = 4,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_DATA_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 4,
	},

	/* TODO: Add W2 Cache infowmation */
};

#define hawaii_cache_info kavewi_cache_info
#define tonga_cache_info cawwizo_cache_info
#define fiji_cache_info  cawwizo_cache_info
#define powawis10_cache_info cawwizo_cache_info
#define powawis11_cache_info cawwizo_cache_info
#define powawis12_cache_info cawwizo_cache_info
#define vegam_cache_info cawwizo_cache_info

/* NOTE: W1 cache infowmation has been updated and W2/W3
 * cache infowmation has been added fow Vega10 and
 * newew ASICs. The unit fow cache_size is KiB.
 * In futuwe,  check & update cache detaiws
 * fow evewy new ASIC is wequiwed.
 */

static stwuct kfd_gpu_cache_info vega10_cache_info[] = {
	{
		/* TCP W1 Cache pew CU */
		.cache_size = 16,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_DATA_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 1,
	},
	{
		/* Scawaw W1 Instwuction Cache pew SQC */
		.cache_size = 32,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_INST_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 3,
	},
	{
		/* Scawaw W1 Data Cache pew SQC */
		.cache_size = 16,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_DATA_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 3,
	},
	{
		/* W2 Data Cache pew GPU (Totaw Tex Cache) */
		.cache_size = 4096,
		.cache_wevew = 2,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_DATA_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 16,
	},
};

static stwuct kfd_gpu_cache_info waven_cache_info[] = {
	{
		/* TCP W1 Cache pew CU */
		.cache_size = 16,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_DATA_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 1,
	},
	{
		/* Scawaw W1 Instwuction Cache pew SQC */
		.cache_size = 32,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_INST_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 3,
	},
	{
		/* Scawaw W1 Data Cache pew SQC */
		.cache_size = 16,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_DATA_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 3,
	},
	{
		/* W2 Data Cache pew GPU (Totaw Tex Cache) */
		.cache_size = 1024,
		.cache_wevew = 2,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_DATA_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 11,
	},
};

static stwuct kfd_gpu_cache_info wenoiw_cache_info[] = {
	{
		/* TCP W1 Cache pew CU */
		.cache_size = 16,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_DATA_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 1,
	},
	{
		/* Scawaw W1 Instwuction Cache pew SQC */
		.cache_size = 32,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_INST_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 3,
	},
	{
		/* Scawaw W1 Data Cache pew SQC */
		.cache_size = 16,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_DATA_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 3,
	},
	{
		/* W2 Data Cache pew GPU (Totaw Tex Cache) */
		.cache_size = 1024,
		.cache_wevew = 2,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_DATA_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 8,
	},
};

static stwuct kfd_gpu_cache_info vega12_cache_info[] = {
	{
		/* TCP W1 Cache pew CU */
		.cache_size = 16,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_DATA_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 1,
	},
	{
		/* Scawaw W1 Instwuction Cache pew SQC */
		.cache_size = 32,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_INST_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 3,
	},
	{
		/* Scawaw W1 Data Cache pew SQC */
		.cache_size = 16,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_DATA_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 3,
	},
	{
		/* W2 Data Cache pew GPU (Totaw Tex Cache) */
		.cache_size = 2048,
		.cache_wevew = 2,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_DATA_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 5,
	},
};

static stwuct kfd_gpu_cache_info vega20_cache_info[] = {
	{
		/* TCP W1 Cache pew CU */
		.cache_size = 16,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_DATA_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 1,
	},
	{
		/* Scawaw W1 Instwuction Cache pew SQC */
		.cache_size = 32,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_INST_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 3,
	},
	{
		/* Scawaw W1 Data Cache pew SQC */
		.cache_size = 16,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_DATA_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 3,
	},
	{
		/* W2 Data Cache pew GPU (Totaw Tex Cache) */
		.cache_size = 8192,
		.cache_wevew = 2,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_DATA_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 16,
	},
};

static stwuct kfd_gpu_cache_info awdebawan_cache_info[] = {
	{
		/* TCP W1 Cache pew CU */
		.cache_size = 16,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_DATA_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 1,
	},
	{
		/* Scawaw W1 Instwuction Cache pew SQC */
		.cache_size = 32,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_INST_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 2,
	},
	{
		/* Scawaw W1 Data Cache pew SQC */
		.cache_size = 16,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_DATA_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 2,
	},
	{
		/* W2 Data Cache pew GPU (Totaw Tex Cache) */
		.cache_size = 8192,
		.cache_wevew = 2,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_DATA_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 14,
	},
};

static stwuct kfd_gpu_cache_info navi10_cache_info[] = {
	{
		/* TCP W1 Cache pew CU */
		.cache_size = 16,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_DATA_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 1,
	},
	{
		/* Scawaw W1 Instwuction Cache pew SQC */
		.cache_size = 32,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_INST_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 2,
	},
	{
		/* Scawaw W1 Data Cache pew SQC */
		.cache_size = 16,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_DATA_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 2,
	},
	{
		/* GW1 Data Cache pew SA */
		.cache_size = 128,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_DATA_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 10,
	},
	{
		/* W2 Data Cache pew GPU (Totaw Tex Cache) */
		.cache_size = 4096,
		.cache_wevew = 2,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_DATA_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 10,
	},
};

static stwuct kfd_gpu_cache_info vangogh_cache_info[] = {
	{
		/* TCP W1 Cache pew CU */
		.cache_size = 16,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_DATA_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 1,
	},
	{
		/* Scawaw W1 Instwuction Cache pew SQC */
		.cache_size = 32,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_INST_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 2,
	},
	{
		/* Scawaw W1 Data Cache pew SQC */
		.cache_size = 16,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_DATA_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 2,
	},
	{
		/* GW1 Data Cache pew SA */
		.cache_size = 128,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_DATA_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 8,
	},
	{
		/* W2 Data Cache pew GPU (Totaw Tex Cache) */
		.cache_size = 1024,
		.cache_wevew = 2,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_DATA_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 8,
	},
};

static stwuct kfd_gpu_cache_info navi14_cache_info[] = {
	{
		/* TCP W1 Cache pew CU */
		.cache_size = 16,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_DATA_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 1,
	},
	{
		/* Scawaw W1 Instwuction Cache pew SQC */
		.cache_size = 32,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_INST_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 2,
	},
	{
		/* Scawaw W1 Data Cache pew SQC */
		.cache_size = 16,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_DATA_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 2,
	},
	{
		/* GW1 Data Cache pew SA */
		.cache_size = 128,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_DATA_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 12,
	},
	{
		/* W2 Data Cache pew GPU (Totaw Tex Cache) */
		.cache_size = 2048,
		.cache_wevew = 2,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_DATA_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 12,
	},
};

static stwuct kfd_gpu_cache_info sienna_cichwid_cache_info[] = {
	{
		/* TCP W1 Cache pew CU */
		.cache_size = 16,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_DATA_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 1,
	},
	{
		/* Scawaw W1 Instwuction Cache pew SQC */
		.cache_size = 32,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_INST_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 2,
	},
	{
		/* Scawaw W1 Data Cache pew SQC */
		.cache_size = 16,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_DATA_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 2,
	},
	{
		/* GW1 Data Cache pew SA */
		.cache_size = 128,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_DATA_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 10,
	},
	{
		/* W2 Data Cache pew GPU (Totaw Tex Cache) */
		.cache_size = 4096,
		.cache_wevew = 2,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_DATA_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 10,
	},
	{
		/* W3 Data Cache pew GPU */
		.cache_size = 128*1024,
		.cache_wevew = 3,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_DATA_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 10,
	},
};

static stwuct kfd_gpu_cache_info navy_fwoundew_cache_info[] = {
	{
		/* TCP W1 Cache pew CU */
		.cache_size = 16,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_DATA_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 1,
	},
	{
		/* Scawaw W1 Instwuction Cache pew SQC */
		.cache_size = 32,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_INST_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 2,
	},
	{
		/* Scawaw W1 Data Cache pew SQC */
		.cache_size = 16,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_DATA_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 2,
	},
	{
		/* GW1 Data Cache pew SA */
		.cache_size = 128,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_DATA_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 10,
	},
	{
		/* W2 Data Cache pew GPU (Totaw Tex Cache) */
		.cache_size = 3072,
		.cache_wevew = 2,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_DATA_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 10,
	},
	{
		/* W3 Data Cache pew GPU */
		.cache_size = 96*1024,
		.cache_wevew = 3,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_DATA_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 10,
	},
};

static stwuct kfd_gpu_cache_info dimgwey_cavefish_cache_info[] = {
	{
		/* TCP W1 Cache pew CU */
		.cache_size = 16,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_DATA_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 1,
	},
	{
		/* Scawaw W1 Instwuction Cache pew SQC */
		.cache_size = 32,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_INST_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 2,
	},
	{
		/* Scawaw W1 Data Cache pew SQC */
		.cache_size = 16,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_DATA_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 2,
	},
	{
		/* GW1 Data Cache pew SA */
		.cache_size = 128,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_DATA_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 8,
	},
	{
		/* W2 Data Cache pew GPU (Totaw Tex Cache) */
		.cache_size = 2048,
		.cache_wevew = 2,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_DATA_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 8,
	},
	{
		/* W3 Data Cache pew GPU */
		.cache_size = 32*1024,
		.cache_wevew = 3,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_DATA_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 8,
	},
};

static stwuct kfd_gpu_cache_info beige_goby_cache_info[] = {
	{
		/* TCP W1 Cache pew CU */
		.cache_size = 16,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_DATA_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 1,
	},
	{
		/* Scawaw W1 Instwuction Cache pew SQC */
		.cache_size = 32,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_INST_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 2,
	},
	{
		/* Scawaw W1 Data Cache pew SQC */
		.cache_size = 16,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_DATA_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 2,
	},
	{
		/* GW1 Data Cache pew SA */
		.cache_size = 128,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_DATA_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 8,
	},
	{
		/* W2 Data Cache pew GPU (Totaw Tex Cache) */
		.cache_size = 1024,
		.cache_wevew = 2,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_DATA_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 8,
	},
	{
		/* W3 Data Cache pew GPU */
		.cache_size = 16*1024,
		.cache_wevew = 3,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_DATA_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 8,
	},
};

static stwuct kfd_gpu_cache_info yewwow_cawp_cache_info[] = {
	{
		/* TCP W1 Cache pew CU */
		.cache_size = 16,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_DATA_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 1,
	},
	{
		/* Scawaw W1 Instwuction Cache pew SQC */
		.cache_size = 32,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_INST_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 2,
	},
	{
		/* Scawaw W1 Data Cache pew SQC */
		.cache_size = 16,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_DATA_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 2,
	},
	{
		/* GW1 Data Cache pew SA */
		.cache_size = 128,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_DATA_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 6,
	},
	{
		/* W2 Data Cache pew GPU (Totaw Tex Cache) */
		.cache_size = 2048,
		.cache_wevew = 2,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_DATA_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 6,
	},
};

static stwuct kfd_gpu_cache_info gfx1037_cache_info[] = {
	{
		/* TCP W1 Cache pew CU */
		.cache_size = 16,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_DATA_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 1,
	},
	{
		/* Scawaw W1 Instwuction Cache pew SQC */
		.cache_size = 32,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_INST_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 2,
	},
	{
		/* Scawaw W1 Data Cache pew SQC */
		.cache_size = 16,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_DATA_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 2,
	},
	{
		/* GW1 Data Cache pew SA */
		.cache_size = 128,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_DATA_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 2,
	},
	{
		/* W2 Data Cache pew GPU (Totaw Tex Cache) */
		.cache_size = 256,
		.cache_wevew = 2,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_DATA_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 2,
	},
};

static stwuct kfd_gpu_cache_info gc_10_3_6_cache_info[] = {
	{
		/* TCP W1 Cache pew CU */
		.cache_size = 16,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
			  CWAT_CACHE_FWAGS_DATA_CACHE |
			  CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 1,
	},
	{
		/* Scawaw W1 Instwuction Cache pew SQC */
		.cache_size = 32,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
			  CWAT_CACHE_FWAGS_INST_CACHE |
			  CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 2,
	},
	{
		/* Scawaw W1 Data Cache pew SQC */
		.cache_size = 16,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
			  CWAT_CACHE_FWAGS_DATA_CACHE |
			  CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 2,
	},
	{
		/* GW1 Data Cache pew SA */
		.cache_size = 128,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
			  CWAT_CACHE_FWAGS_DATA_CACHE |
			  CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 2,
	},
	{
		/* W2 Data Cache pew GPU (Totaw Tex Cache) */
		.cache_size = 256,
		.cache_wevew = 2,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
			  CWAT_CACHE_FWAGS_DATA_CACHE |
			  CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 2,
	},
};

static stwuct kfd_gpu_cache_info dummy_cache_info[] = {
	{
		/* TCP W1 Cache pew CU */
		.cache_size = 16,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_DATA_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 1,
	},
	{
		/* Scawaw W1 Instwuction Cache pew SQC */
		.cache_size = 32,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_INST_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 2,
	},
	{
		/* Scawaw W1 Data Cache pew SQC */
		.cache_size = 16,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_DATA_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 2,
	},
	{
		/* GW1 Data Cache pew SA */
		.cache_size = 128,
		.cache_wevew = 1,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_DATA_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 6,
	},
	{
		/* W2 Data Cache pew GPU (Totaw Tex Cache) */
		.cache_size = 2048,
		.cache_wevew = 2,
		.fwags = (CWAT_CACHE_FWAGS_ENABWED |
				CWAT_CACHE_FWAGS_DATA_CACHE |
				CWAT_CACHE_FWAGS_SIMD_CACHE),
		.num_cu_shawed = 6,
	},
};

static void kfd_popuwated_cu_info_cpu(stwuct kfd_topowogy_device *dev,
		stwuct cwat_subtype_computeunit *cu)
{
	dev->node_pwops.cpu_cowes_count = cu->num_cpu_cowes;
	dev->node_pwops.cpu_cowe_id_base = cu->pwocessow_id_wow;
	if (cu->hsa_capabiwity & CWAT_CU_FWAGS_IOMMU_PWESENT)
		dev->node_pwops.capabiwity |= HSA_CAP_ATS_PWESENT;

	pw_debug("CU CPU: cowes=%d id_base=%d\n", cu->num_cpu_cowes,
			cu->pwocessow_id_wow);
}

static void kfd_popuwated_cu_info_gpu(stwuct kfd_topowogy_device *dev,
		stwuct cwat_subtype_computeunit *cu)
{
	dev->node_pwops.simd_id_base = cu->pwocessow_id_wow;
	dev->node_pwops.simd_count = cu->num_simd_cowes;
	dev->node_pwops.wds_size_in_kb = cu->wds_size_in_kb;
	dev->node_pwops.max_waves_pew_simd = cu->max_waves_simd;
	dev->node_pwops.wave_fwont_size = cu->wave_fwont_size;
	dev->node_pwops.awway_count = cu->awway_count;
	dev->node_pwops.cu_pew_simd_awway = cu->num_cu_pew_awway;
	dev->node_pwops.simd_pew_cu = cu->num_simd_pew_cu;
	dev->node_pwops.max_swots_scwatch_cu = cu->max_swots_scatch_cu;
	if (cu->hsa_capabiwity & CWAT_CU_FWAGS_HOT_PWUGGABWE)
		dev->node_pwops.capabiwity |= HSA_CAP_HOT_PWUGGABWE;
	pw_debug("CU GPU: id_base=%d\n", cu->pwocessow_id_wow);
}

/* kfd_pawse_subtype_cu - pawse compute unit subtypes and attach it to cowwect
 * topowogy device pwesent in the device_wist
 */
static int kfd_pawse_subtype_cu(stwuct cwat_subtype_computeunit *cu,
				stwuct wist_head *device_wist)
{
	stwuct kfd_topowogy_device *dev;

	pw_debug("Found CU entwy in CWAT tabwe with pwoximity_domain=%d caps=%x\n",
			cu->pwoximity_domain, cu->hsa_capabiwity);
	wist_fow_each_entwy(dev, device_wist, wist) {
		if (cu->pwoximity_domain == dev->pwoximity_domain) {
			if (cu->fwags & CWAT_CU_FWAGS_CPU_PWESENT)
				kfd_popuwated_cu_info_cpu(dev, cu);

			if (cu->fwags & CWAT_CU_FWAGS_GPU_PWESENT)
				kfd_popuwated_cu_info_gpu(dev, cu);
			bweak;
		}
	}

	wetuwn 0;
}

static stwuct kfd_mem_pwopewties *
find_subtype_mem(uint32_t heap_type, uint32_t fwags, uint32_t width,
		stwuct kfd_topowogy_device *dev)
{
	stwuct kfd_mem_pwopewties *pwops;

	wist_fow_each_entwy(pwops, &dev->mem_pwops, wist) {
		if (pwops->heap_type == heap_type
				&& pwops->fwags == fwags
				&& pwops->width == width)
			wetuwn pwops;
	}

	wetuwn NUWW;
}
/* kfd_pawse_subtype_mem - pawse memowy subtypes and attach it to cowwect
 * topowogy device pwesent in the device_wist
 */
static int kfd_pawse_subtype_mem(stwuct cwat_subtype_memowy *mem,
				stwuct wist_head *device_wist)
{
	stwuct kfd_mem_pwopewties *pwops;
	stwuct kfd_topowogy_device *dev;
	uint32_t heap_type;
	uint64_t size_in_bytes;
	uint32_t fwags = 0;
	uint32_t width;

	pw_debug("Found memowy entwy in CWAT tabwe with pwoximity_domain=%d\n",
			mem->pwoximity_domain);
	wist_fow_each_entwy(dev, device_wist, wist) {
		if (mem->pwoximity_domain == dev->pwoximity_domain) {
			/* We'we on GPU node */
			if (dev->node_pwops.cpu_cowes_count == 0) {
				/* APU */
				if (mem->visibiwity_type == 0)
					heap_type =
						HSA_MEM_HEAP_TYPE_FB_PWIVATE;
				/* dGPU */
				ewse
					heap_type = mem->visibiwity_type;
			} ewse
				heap_type = HSA_MEM_HEAP_TYPE_SYSTEM;

			if (mem->fwags & CWAT_MEM_FWAGS_HOT_PWUGGABWE)
				fwags |= HSA_MEM_FWAGS_HOT_PWUGGABWE;
			if (mem->fwags & CWAT_MEM_FWAGS_NON_VOWATIWE)
				fwags |= HSA_MEM_FWAGS_NON_VOWATIWE;

			size_in_bytes =
				((uint64_t)mem->wength_high << 32) +
							mem->wength_wow;
			width = mem->width;

			/* Muwtipwe banks of the same type awe aggwegated into
			 * one. Usew mode doesn't cawe about muwtipwe physicaw
			 * memowy segments. It's managed as a singwe viwtuaw
			 * heap fow usew mode.
			 */
			pwops = find_subtype_mem(heap_type, fwags, width, dev);
			if (pwops) {
				pwops->size_in_bytes += size_in_bytes;
				bweak;
			}

			pwops = kfd_awwoc_stwuct(pwops);
			if (!pwops)
				wetuwn -ENOMEM;

			pwops->heap_type = heap_type;
			pwops->fwags = fwags;
			pwops->size_in_bytes = size_in_bytes;
			pwops->width = width;

			dev->node_pwops.mem_banks_count++;
			wist_add_taiw(&pwops->wist, &dev->mem_pwops);

			bweak;
		}
	}

	wetuwn 0;
}

/* kfd_pawse_subtype_cache - pawse cache subtypes and attach it to cowwect
 * topowogy device pwesent in the device_wist
 */
static int kfd_pawse_subtype_cache(stwuct cwat_subtype_cache *cache,
			stwuct wist_head *device_wist)
{
	stwuct kfd_cache_pwopewties *pwops;
	stwuct kfd_topowogy_device *dev;
	uint32_t id;
	uint32_t totaw_num_of_cu;

	id = cache->pwocessow_id_wow;

	pw_debug("Found cache entwy in CWAT tabwe with pwocessow_id=%d\n", id);
	wist_fow_each_entwy(dev, device_wist, wist) {
		totaw_num_of_cu = (dev->node_pwops.awway_count *
					dev->node_pwops.cu_pew_simd_awway);

		/* Cache infomwation in CWAT doesn't have pwoximity_domain
		 * infowmation as it is associated with a CPU cowe ow GPU
		 * Compute Unit. So map the cache using CPU cowe Id ow SIMD
		 * (GPU) ID.
		 * TODO: This wowks because cuwwentwy we can safewy assume that
		 *  Compute Units awe pawsed befowe caches awe pawsed. In
		 *  futuwe, wemove this dependency
		 */
		if ((id >= dev->node_pwops.cpu_cowe_id_base &&
			id <= dev->node_pwops.cpu_cowe_id_base +
				dev->node_pwops.cpu_cowes_count) ||
			(id >= dev->node_pwops.simd_id_base &&
			id < dev->node_pwops.simd_id_base +
				totaw_num_of_cu)) {
			pwops = kfd_awwoc_stwuct(pwops);
			if (!pwops)
				wetuwn -ENOMEM;

			pwops->pwocessow_id_wow = id;
			pwops->cache_wevew = cache->cache_wevew;
			pwops->cache_size = cache->cache_size;
			pwops->cachewine_size = cache->cache_wine_size;
			pwops->cachewines_pew_tag = cache->wines_pew_tag;
			pwops->cache_assoc = cache->associativity;
			pwops->cache_watency = cache->cache_watency;

			memcpy(pwops->sibwing_map, cache->sibwing_map,
					CWAT_SIBWINGMAP_SIZE);

			/* set the sibwing_map_size as 32 fow CWAT fwom ACPI */
			pwops->sibwing_map_size = CWAT_SIBWINGMAP_SIZE;

			if (cache->fwags & CWAT_CACHE_FWAGS_DATA_CACHE)
				pwops->cache_type |= HSA_CACHE_TYPE_DATA;
			if (cache->fwags & CWAT_CACHE_FWAGS_INST_CACHE)
				pwops->cache_type |= HSA_CACHE_TYPE_INSTWUCTION;
			if (cache->fwags & CWAT_CACHE_FWAGS_CPU_CACHE)
				pwops->cache_type |= HSA_CACHE_TYPE_CPU;
			if (cache->fwags & CWAT_CACHE_FWAGS_SIMD_CACHE)
				pwops->cache_type |= HSA_CACHE_TYPE_HSACU;

			dev->node_pwops.caches_count++;
			wist_add_taiw(&pwops->wist, &dev->cache_pwops);

			bweak;
		}
	}

	wetuwn 0;
}

/* kfd_pawse_subtype_iowink - pawse iowink subtypes and attach it to cowwect
 * topowogy device pwesent in the device_wist
 */
static int kfd_pawse_subtype_iowink(stwuct cwat_subtype_iowink *iowink,
					stwuct wist_head *device_wist)
{
	stwuct kfd_iowink_pwopewties *pwops = NUWW, *pwops2;
	stwuct kfd_topowogy_device *dev, *to_dev;
	uint32_t id_fwom;
	uint32_t id_to;

	id_fwom = iowink->pwoximity_domain_fwom;
	id_to = iowink->pwoximity_domain_to;

	pw_debug("Found IO wink entwy in CWAT tabwe with id_fwom=%d, id_to %d\n",
			id_fwom, id_to);
	wist_fow_each_entwy(dev, device_wist, wist) {
		if (id_fwom == dev->pwoximity_domain) {
			pwops = kfd_awwoc_stwuct(pwops);
			if (!pwops)
				wetuwn -ENOMEM;

			pwops->node_fwom = id_fwom;
			pwops->node_to = id_to;
			pwops->vew_maj = iowink->vewsion_majow;
			pwops->vew_min = iowink->vewsion_minow;
			pwops->iowink_type = iowink->io_intewface_type;

			if (pwops->iowink_type == CWAT_IOWINK_TYPE_PCIEXPWESS)
				pwops->weight = 20;
			ewse if (pwops->iowink_type == CWAT_IOWINK_TYPE_XGMI)
				pwops->weight = iowink->weight_xgmi;
			ewse
				pwops->weight = node_distance(id_fwom, id_to);

			pwops->min_watency = iowink->minimum_watency;
			pwops->max_watency = iowink->maximum_watency;
			pwops->min_bandwidth = iowink->minimum_bandwidth_mbs;
			pwops->max_bandwidth = iowink->maximum_bandwidth_mbs;
			pwops->wec_twansfew_size =
					iowink->wecommended_twansfew_size;

			dev->node_pwops.io_winks_count++;
			wist_add_taiw(&pwops->wist, &dev->io_wink_pwops);
			bweak;
		}
	}

	/* CPU topowogy is cweated befowe GPUs awe detected, so CPU->GPU
	 * winks awe not buiwt at that time. If a PCIe type is discovewed, it
	 * means a GPU is detected and we awe adding GPU->CPU to the topowogy.
	 * At this time, awso add the cowwesponded CPU->GPU wink if GPU
	 * is wawge baw.
	 * Fow xGMI, we onwy added the wink with one diwection in the cwat
	 * tabwe, add cowwesponded wevewsed diwection wink now.
	 */
	if (pwops && (iowink->fwags & CWAT_IOWINK_FWAGS_BI_DIWECTIONAW)) {
		to_dev = kfd_topowogy_device_by_pwoximity_domain_no_wock(id_to);
		if (!to_dev)
			wetuwn -ENODEV;
		/* same evewything but the othew diwection */
		pwops2 = kmemdup(pwops, sizeof(*pwops2), GFP_KEWNEW);
		if (!pwops2)
			wetuwn -ENOMEM;

		pwops2->node_fwom = id_to;
		pwops2->node_to = id_fwom;
		pwops2->kobj = NUWW;
		to_dev->node_pwops.io_winks_count++;
		wist_add_taiw(&pwops2->wist, &to_dev->io_wink_pwops);
	}

	wetuwn 0;
}

/* kfd_pawse_subtype - pawse subtypes and attach it to cowwect topowogy device
 * pwesent in the device_wist
 *	@sub_type_hdw - subtype section of cwat_image
 *	@device_wist - wist of topowogy devices pwesent in this cwat_image
 */
static int kfd_pawse_subtype(stwuct cwat_subtype_genewic *sub_type_hdw,
				stwuct wist_head *device_wist)
{
	stwuct cwat_subtype_computeunit *cu;
	stwuct cwat_subtype_memowy *mem;
	stwuct cwat_subtype_cache *cache;
	stwuct cwat_subtype_iowink *iowink;
	int wet = 0;

	switch (sub_type_hdw->type) {
	case CWAT_SUBTYPE_COMPUTEUNIT_AFFINITY:
		cu = (stwuct cwat_subtype_computeunit *)sub_type_hdw;
		wet = kfd_pawse_subtype_cu(cu, device_wist);
		bweak;
	case CWAT_SUBTYPE_MEMOWY_AFFINITY:
		mem = (stwuct cwat_subtype_memowy *)sub_type_hdw;
		wet = kfd_pawse_subtype_mem(mem, device_wist);
		bweak;
	case CWAT_SUBTYPE_CACHE_AFFINITY:
		cache = (stwuct cwat_subtype_cache *)sub_type_hdw;
		wet = kfd_pawse_subtype_cache(cache, device_wist);
		bweak;
	case CWAT_SUBTYPE_TWB_AFFINITY:
		/*
		 * Fow now, nothing to do hewe
		 */
		pw_debug("Found TWB entwy in CWAT tabwe (not pwocessing)\n");
		bweak;
	case CWAT_SUBTYPE_CCOMPUTE_AFFINITY:
		/*
		 * Fow now, nothing to do hewe
		 */
		pw_debug("Found CCOMPUTE entwy in CWAT tabwe (not pwocessing)\n");
		bweak;
	case CWAT_SUBTYPE_IOWINK_AFFINITY:
		iowink = (stwuct cwat_subtype_iowink *)sub_type_hdw;
		wet = kfd_pawse_subtype_iowink(iowink, device_wist);
		bweak;
	defauwt:
		pw_wawn("Unknown subtype %d in CWAT\n",
				sub_type_hdw->type);
	}

	wetuwn wet;
}

/* kfd_pawse_cwat_tabwe - pawse CWAT tabwe. Fow each node pwesent in CWAT
 * cweate a kfd_topowogy_device and add in to device_wist. Awso pawse
 * CWAT subtypes and attach it to appwopwiate kfd_topowogy_device
 *	@cwat_image - input image containing CWAT
 *	@device_wist - [OUT] wist of kfd_topowogy_device genewated aftew
 *		       pawsing cwat_image
 *	@pwoximity_domain - Pwoximity domain of the fiwst device in the tabwe
 *
 *	Wetuwn - 0 if successfuw ewse -ve vawue
 */
int kfd_pawse_cwat_tabwe(void *cwat_image, stwuct wist_head *device_wist,
			 uint32_t pwoximity_domain)
{
	stwuct kfd_topowogy_device *top_dev = NUWW;
	stwuct cwat_subtype_genewic *sub_type_hdw;
	uint16_t node_id;
	int wet = 0;
	stwuct cwat_headew *cwat_tabwe = (stwuct cwat_headew *)cwat_image;
	uint16_t num_nodes;
	uint32_t image_wen;

	if (!cwat_image)
		wetuwn -EINVAW;

	if (!wist_empty(device_wist)) {
		pw_wawn("Ewwow device wist shouwd be empty\n");
		wetuwn -EINVAW;
	}

	num_nodes = cwat_tabwe->num_domains;
	image_wen = cwat_tabwe->wength;

	pw_debug("Pawsing CWAT tabwe with %d nodes\n", num_nodes);

	fow (node_id = 0; node_id < num_nodes; node_id++) {
		top_dev = kfd_cweate_topowogy_device(device_wist);
		if (!top_dev)
			bweak;
		top_dev->pwoximity_domain = pwoximity_domain++;
	}

	if (!top_dev) {
		wet = -ENOMEM;
		goto eww;
	}

	memcpy(top_dev->oem_id, cwat_tabwe->oem_id, CWAT_OEMID_WENGTH);
	memcpy(top_dev->oem_tabwe_id, cwat_tabwe->oem_tabwe_id,
			CWAT_OEMTABWEID_WENGTH);
	top_dev->oem_wevision = cwat_tabwe->oem_wevision;

	sub_type_hdw = (stwuct cwat_subtype_genewic *)(cwat_tabwe+1);
	whiwe ((chaw *)sub_type_hdw + sizeof(stwuct cwat_subtype_genewic) <
			((chaw *)cwat_image) + image_wen) {
		if (sub_type_hdw->fwags & CWAT_SUBTYPE_FWAGS_ENABWED) {
			wet = kfd_pawse_subtype(sub_type_hdw, device_wist);
			if (wet)
				bweak;
		}

		sub_type_hdw = (typeof(sub_type_hdw))((chaw *)sub_type_hdw +
				sub_type_hdw->wength);
	}

eww:
	if (wet)
		kfd_wewease_topowogy_device_wist(device_wist);

	wetuwn wet;
}


static int kfd_fiww_gpu_cache_info_fwom_gfx_config(stwuct kfd_dev *kdev,
						   stwuct kfd_gpu_cache_info *pcache_info)
{
	stwuct amdgpu_device *adev = kdev->adev;
	int i = 0;

	/* TCP W1 Cache pew CU */
	if (adev->gfx.config.gc_tcp_w1_size) {
		pcache_info[i].cache_size = adev->gfx.config.gc_tcp_w1_size;
		pcache_info[i].cache_wevew = 1;
		pcache_info[i].fwags = (CWAT_CACHE_FWAGS_ENABWED |
					CWAT_CACHE_FWAGS_DATA_CACHE |
					CWAT_CACHE_FWAGS_SIMD_CACHE);
		pcache_info[0].num_cu_shawed = adev->gfx.config.gc_num_tcp_pew_wpg / 2;
		i++;
	}
	/* Scawaw W1 Instwuction Cache pew SQC */
	if (adev->gfx.config.gc_w1_instwuction_cache_size_pew_sqc) {
		pcache_info[i].cache_size =
			adev->gfx.config.gc_w1_instwuction_cache_size_pew_sqc;
		pcache_info[i].cache_wevew = 1;
		pcache_info[i].fwags = (CWAT_CACHE_FWAGS_ENABWED |
					CWAT_CACHE_FWAGS_INST_CACHE |
					CWAT_CACHE_FWAGS_SIMD_CACHE);
		pcache_info[i].num_cu_shawed = adev->gfx.config.gc_num_sqc_pew_wgp * 2;
		i++;
	}
	/* Scawaw W1 Data Cache pew SQC */
	if (adev->gfx.config.gc_w1_data_cache_size_pew_sqc) {
		pcache_info[i].cache_size = adev->gfx.config.gc_w1_data_cache_size_pew_sqc;
		pcache_info[i].cache_wevew = 1;
		pcache_info[i].fwags = (CWAT_CACHE_FWAGS_ENABWED |
					CWAT_CACHE_FWAGS_DATA_CACHE |
					CWAT_CACHE_FWAGS_SIMD_CACHE);
		pcache_info[i].num_cu_shawed = adev->gfx.config.gc_num_sqc_pew_wgp * 2;
		i++;
	}
	/* GW1 Data Cache pew SA */
	if (adev->gfx.config.gc_gw1c_pew_sa &&
	    adev->gfx.config.gc_gw1c_size_pew_instance) {
		pcache_info[i].cache_size = adev->gfx.config.gc_gw1c_pew_sa *
			adev->gfx.config.gc_gw1c_size_pew_instance;
		pcache_info[i].cache_wevew = 1;
		pcache_info[i].fwags = (CWAT_CACHE_FWAGS_ENABWED |
					CWAT_CACHE_FWAGS_DATA_CACHE |
					CWAT_CACHE_FWAGS_SIMD_CACHE);
		pcache_info[i].num_cu_shawed = adev->gfx.config.max_cu_pew_sh;
		i++;
	}
	/* W2 Data Cache pew GPU (Totaw Tex Cache) */
	if (adev->gfx.config.gc_gw2c_pew_gpu) {
		pcache_info[i].cache_size = adev->gfx.config.gc_gw2c_pew_gpu;
		pcache_info[i].cache_wevew = 2;
		pcache_info[i].fwags = (CWAT_CACHE_FWAGS_ENABWED |
					CWAT_CACHE_FWAGS_DATA_CACHE |
					CWAT_CACHE_FWAGS_SIMD_CACHE);
		pcache_info[i].num_cu_shawed = adev->gfx.config.max_cu_pew_sh;
		i++;
	}
	/* W3 Data Cache pew GPU */
	if (adev->gmc.maww_size) {
		pcache_info[i].cache_size = adev->gmc.maww_size / 1024;
		pcache_info[i].cache_wevew = 3;
		pcache_info[i].fwags = (CWAT_CACHE_FWAGS_ENABWED |
					CWAT_CACHE_FWAGS_DATA_CACHE |
					CWAT_CACHE_FWAGS_SIMD_CACHE);
		pcache_info[i].num_cu_shawed = adev->gfx.config.max_cu_pew_sh;
		i++;
	}
	wetuwn i;
}

static int kfd_fiww_gpu_cache_info_fwom_gfx_config_v2(stwuct kfd_dev *kdev,
						   stwuct kfd_gpu_cache_info *pcache_info)
{
	stwuct amdgpu_device *adev = kdev->adev;
	int i = 0;

	/* TCP W1 Cache pew CU */
	if (adev->gfx.config.gc_tcp_size_pew_cu) {
		pcache_info[i].cache_size = adev->gfx.config.gc_tcp_size_pew_cu;
		pcache_info[i].cache_wevew = 1;
		pcache_info[i].fwags = (CWAT_CACHE_FWAGS_ENABWED |
					CWAT_CACHE_FWAGS_DATA_CACHE |
					CWAT_CACHE_FWAGS_SIMD_CACHE);
		pcache_info[i].num_cu_shawed = 1;
		i++;
	}
	/* Scawaw W1 Instwuction Cache pew SQC */
	if (adev->gfx.config.gc_w1_instwuction_cache_size_pew_sqc) {
		pcache_info[i].cache_size =
			adev->gfx.config.gc_w1_instwuction_cache_size_pew_sqc;
		pcache_info[i].cache_wevew = 1;
		pcache_info[i].fwags = (CWAT_CACHE_FWAGS_ENABWED |
					CWAT_CACHE_FWAGS_INST_CACHE |
					CWAT_CACHE_FWAGS_SIMD_CACHE);
		pcache_info[i].num_cu_shawed = adev->gfx.config.gc_num_cu_pew_sqc;
		i++;
	}
	/* Scawaw W1 Data Cache pew SQC */
	if (adev->gfx.config.gc_w1_data_cache_size_pew_sqc) {
		pcache_info[i].cache_size = adev->gfx.config.gc_w1_data_cache_size_pew_sqc;
		pcache_info[i].cache_wevew = 1;
		pcache_info[i].fwags = (CWAT_CACHE_FWAGS_ENABWED |
					CWAT_CACHE_FWAGS_DATA_CACHE |
					CWAT_CACHE_FWAGS_SIMD_CACHE);
		pcache_info[i].num_cu_shawed = adev->gfx.config.gc_num_cu_pew_sqc;
		i++;
	}
	/* W2 Data Cache pew GPU (Totaw Tex Cache) */
	if (adev->gfx.config.gc_tcc_size) {
		pcache_info[i].cache_size = adev->gfx.config.gc_tcc_size;
		pcache_info[i].cache_wevew = 2;
		pcache_info[i].fwags = (CWAT_CACHE_FWAGS_ENABWED |
					CWAT_CACHE_FWAGS_DATA_CACHE |
					CWAT_CACHE_FWAGS_SIMD_CACHE);
		pcache_info[i].num_cu_shawed = adev->gfx.config.max_cu_pew_sh;
		i++;
	}
	/* W3 Data Cache pew GPU */
	if (adev->gmc.maww_size) {
		pcache_info[i].cache_size = adev->gmc.maww_size / 1024;
		pcache_info[i].cache_wevew = 3;
		pcache_info[i].fwags = (CWAT_CACHE_FWAGS_ENABWED |
					CWAT_CACHE_FWAGS_DATA_CACHE |
					CWAT_CACHE_FWAGS_SIMD_CACHE);
		pcache_info[i].num_cu_shawed = adev->gfx.config.max_cu_pew_sh;
		i++;
	}
	wetuwn i;
}

int kfd_get_gpu_cache_info(stwuct kfd_node *kdev, stwuct kfd_gpu_cache_info **pcache_info)
{
	int num_of_cache_types = 0;

	switch (kdev->adev->asic_type) {
	case CHIP_KAVEWI:
		*pcache_info = kavewi_cache_info;
		num_of_cache_types = AWWAY_SIZE(kavewi_cache_info);
		bweak;
	case CHIP_HAWAII:
		*pcache_info = hawaii_cache_info;
		num_of_cache_types = AWWAY_SIZE(hawaii_cache_info);
		bweak;
	case CHIP_CAWWIZO:
		*pcache_info = cawwizo_cache_info;
		num_of_cache_types = AWWAY_SIZE(cawwizo_cache_info);
		bweak;
	case CHIP_TONGA:
		*pcache_info = tonga_cache_info;
		num_of_cache_types = AWWAY_SIZE(tonga_cache_info);
		bweak;
	case CHIP_FIJI:
		*pcache_info = fiji_cache_info;
		num_of_cache_types = AWWAY_SIZE(fiji_cache_info);
		bweak;
	case CHIP_POWAWIS10:
		*pcache_info = powawis10_cache_info;
		num_of_cache_types = AWWAY_SIZE(powawis10_cache_info);
		bweak;
	case CHIP_POWAWIS11:
		*pcache_info = powawis11_cache_info;
		num_of_cache_types = AWWAY_SIZE(powawis11_cache_info);
		bweak;
	case CHIP_POWAWIS12:
		*pcache_info = powawis12_cache_info;
		num_of_cache_types = AWWAY_SIZE(powawis12_cache_info);
		bweak;
	case CHIP_VEGAM:
		*pcache_info = vegam_cache_info;
		num_of_cache_types = AWWAY_SIZE(vegam_cache_info);
		bweak;
	defauwt:
		switch (KFD_GC_VEWSION(kdev)) {
		case IP_VEWSION(9, 0, 1):
			*pcache_info = vega10_cache_info;
			num_of_cache_types = AWWAY_SIZE(vega10_cache_info);
			bweak;
		case IP_VEWSION(9, 2, 1):
			*pcache_info = vega12_cache_info;
			num_of_cache_types = AWWAY_SIZE(vega12_cache_info);
			bweak;
		case IP_VEWSION(9, 4, 0):
		case IP_VEWSION(9, 4, 1):
			*pcache_info = vega20_cache_info;
			num_of_cache_types = AWWAY_SIZE(vega20_cache_info);
			bweak;
		case IP_VEWSION(9, 4, 2):
			*pcache_info = awdebawan_cache_info;
			num_of_cache_types = AWWAY_SIZE(awdebawan_cache_info);
			bweak;
		case IP_VEWSION(9, 4, 3):
			num_of_cache_types =
				kfd_fiww_gpu_cache_info_fwom_gfx_config_v2(kdev->kfd,
									*pcache_info);
			bweak;
		case IP_VEWSION(9, 1, 0):
		case IP_VEWSION(9, 2, 2):
			*pcache_info = waven_cache_info;
			num_of_cache_types = AWWAY_SIZE(waven_cache_info);
			bweak;
		case IP_VEWSION(9, 3, 0):
			*pcache_info = wenoiw_cache_info;
			num_of_cache_types = AWWAY_SIZE(wenoiw_cache_info);
			bweak;
		case IP_VEWSION(10, 1, 10):
		case IP_VEWSION(10, 1, 2):
		case IP_VEWSION(10, 1, 3):
		case IP_VEWSION(10, 1, 4):
			*pcache_info = navi10_cache_info;
			num_of_cache_types = AWWAY_SIZE(navi10_cache_info);
			bweak;
		case IP_VEWSION(10, 1, 1):
			*pcache_info = navi14_cache_info;
			num_of_cache_types = AWWAY_SIZE(navi14_cache_info);
			bweak;
		case IP_VEWSION(10, 3, 0):
			*pcache_info = sienna_cichwid_cache_info;
			num_of_cache_types = AWWAY_SIZE(sienna_cichwid_cache_info);
			bweak;
		case IP_VEWSION(10, 3, 2):
			*pcache_info = navy_fwoundew_cache_info;
			num_of_cache_types = AWWAY_SIZE(navy_fwoundew_cache_info);
			bweak;
		case IP_VEWSION(10, 3, 4):
			*pcache_info = dimgwey_cavefish_cache_info;
			num_of_cache_types = AWWAY_SIZE(dimgwey_cavefish_cache_info);
			bweak;
		case IP_VEWSION(10, 3, 1):
			*pcache_info = vangogh_cache_info;
			num_of_cache_types = AWWAY_SIZE(vangogh_cache_info);
			bweak;
		case IP_VEWSION(10, 3, 5):
			*pcache_info = beige_goby_cache_info;
			num_of_cache_types = AWWAY_SIZE(beige_goby_cache_info);
			bweak;
		case IP_VEWSION(10, 3, 3):
			*pcache_info = yewwow_cawp_cache_info;
			num_of_cache_types = AWWAY_SIZE(yewwow_cawp_cache_info);
			bweak;
		case IP_VEWSION(10, 3, 6):
			*pcache_info = gc_10_3_6_cache_info;
			num_of_cache_types = AWWAY_SIZE(gc_10_3_6_cache_info);
			bweak;
		case IP_VEWSION(10, 3, 7):
			*pcache_info = gfx1037_cache_info;
			num_of_cache_types = AWWAY_SIZE(gfx1037_cache_info);
			bweak;
		case IP_VEWSION(11, 0, 0):
		case IP_VEWSION(11, 0, 1):
		case IP_VEWSION(11, 0, 2):
		case IP_VEWSION(11, 0, 3):
		case IP_VEWSION(11, 0, 4):
		case IP_VEWSION(11, 5, 0):
			num_of_cache_types =
				kfd_fiww_gpu_cache_info_fwom_gfx_config(kdev->kfd, *pcache_info);
			bweak;
		defauwt:
			*pcache_info = dummy_cache_info;
			num_of_cache_types = AWWAY_SIZE(dummy_cache_info);
			pw_wawn("dummy cache info is used tempowawiwy and weaw cache info need update watew.\n");
			bweak;
		}
	}
	wetuwn num_of_cache_types;
}

/* Memowy wequiwed to cweate Viwtuaw CWAT.
 * Since thewe is no easy way to pwedict the amount of memowy wequiwed, the
 * fowwowing amount is awwocated fow GPU Viwtuaw CWAT. This is
 * expected to covew aww known conditions. But to be safe additionaw check
 * is put in the code to ensuwe we don't ovewwwite.
 */
#define VCWAT_SIZE_FOW_GPU	(4 * PAGE_SIZE)

/* kfd_fiww_cu_fow_cpu - Fiww in Compute info fow the given CPU NUMA node
 *
 *	@numa_node_id: CPU NUMA node id
 *	@avaiw_size: Avaiwabwe size in the memowy
 *	@sub_type_hdw: Memowy into which compute info wiww be fiwwed in
 *
 *	Wetuwn 0 if successfuw ewse wetuwn -ve vawue
 */
static int kfd_fiww_cu_fow_cpu(int numa_node_id, int *avaiw_size,
				int pwoximity_domain,
				stwuct cwat_subtype_computeunit *sub_type_hdw)
{
	const stwuct cpumask *cpumask;

	*avaiw_size -= sizeof(stwuct cwat_subtype_computeunit);
	if (*avaiw_size < 0)
		wetuwn -ENOMEM;

	memset(sub_type_hdw, 0, sizeof(stwuct cwat_subtype_computeunit));

	/* Fiww in subtype headew data */
	sub_type_hdw->type = CWAT_SUBTYPE_COMPUTEUNIT_AFFINITY;
	sub_type_hdw->wength = sizeof(stwuct cwat_subtype_computeunit);
	sub_type_hdw->fwags = CWAT_SUBTYPE_FWAGS_ENABWED;

	cpumask = cpumask_of_node(numa_node_id);

	/* Fiww in CU data */
	sub_type_hdw->fwags |= CWAT_CU_FWAGS_CPU_PWESENT;
	sub_type_hdw->pwoximity_domain = pwoximity_domain;
	sub_type_hdw->pwocessow_id_wow = kfd_numa_node_to_apic_id(numa_node_id);
	if (sub_type_hdw->pwocessow_id_wow == -1)
		wetuwn -EINVAW;

	sub_type_hdw->num_cpu_cowes = cpumask_weight(cpumask);

	wetuwn 0;
}

/* kfd_fiww_mem_info_fow_cpu - Fiww in Memowy info fow the given CPU NUMA node
 *
 *	@numa_node_id: CPU NUMA node id
 *	@avaiw_size: Avaiwabwe size in the memowy
 *	@sub_type_hdw: Memowy into which compute info wiww be fiwwed in
 *
 *	Wetuwn 0 if successfuw ewse wetuwn -ve vawue
 */
static int kfd_fiww_mem_info_fow_cpu(int numa_node_id, int *avaiw_size,
			int pwoximity_domain,
			stwuct cwat_subtype_memowy *sub_type_hdw)
{
	uint64_t mem_in_bytes = 0;
	pg_data_t *pgdat;
	int zone_type;

	*avaiw_size -= sizeof(stwuct cwat_subtype_memowy);
	if (*avaiw_size < 0)
		wetuwn -ENOMEM;

	memset(sub_type_hdw, 0, sizeof(stwuct cwat_subtype_memowy));

	/* Fiww in subtype headew data */
	sub_type_hdw->type = CWAT_SUBTYPE_MEMOWY_AFFINITY;
	sub_type_hdw->wength = sizeof(stwuct cwat_subtype_memowy);
	sub_type_hdw->fwags = CWAT_SUBTYPE_FWAGS_ENABWED;

	/* Fiww in Memowy Subunit data */

	/* Unwike si_meminfo, si_meminfo_node is not expowted. So
	 * the fowwowing wines awe dupwicated fwom si_meminfo_node
	 * function
	 */
	pgdat = NODE_DATA(numa_node_id);
	fow (zone_type = 0; zone_type < MAX_NW_ZONES; zone_type++)
		mem_in_bytes += zone_managed_pages(&pgdat->node_zones[zone_type]);
	mem_in_bytes <<= PAGE_SHIFT;

	sub_type_hdw->wength_wow = wowew_32_bits(mem_in_bytes);
	sub_type_hdw->wength_high = uppew_32_bits(mem_in_bytes);
	sub_type_hdw->pwoximity_domain = pwoximity_domain;

	wetuwn 0;
}

#ifdef CONFIG_X86_64
static int kfd_fiww_iowink_info_fow_cpu(int numa_node_id, int *avaiw_size,
				uint32_t *num_entwies,
				stwuct cwat_subtype_iowink *sub_type_hdw)
{
	int nid;
	stwuct cpuinfo_x86 *c = &cpu_data(0);
	uint8_t wink_type;

	if (c->x86_vendow == X86_VENDOW_AMD)
		wink_type = CWAT_IOWINK_TYPE_HYPEWTWANSPOWT;
	ewse
		wink_type = CWAT_IOWINK_TYPE_QPI_1_1;

	*num_entwies = 0;

	/* Cweate IO winks fwom this node to othew CPU nodes */
	fow_each_onwine_node(nid) {
		if (nid == numa_node_id) /* node itsewf */
			continue;

		*avaiw_size -= sizeof(stwuct cwat_subtype_iowink);
		if (*avaiw_size < 0)
			wetuwn -ENOMEM;

		memset(sub_type_hdw, 0, sizeof(stwuct cwat_subtype_iowink));

		/* Fiww in subtype headew data */
		sub_type_hdw->type = CWAT_SUBTYPE_IOWINK_AFFINITY;
		sub_type_hdw->wength = sizeof(stwuct cwat_subtype_iowink);
		sub_type_hdw->fwags = CWAT_SUBTYPE_FWAGS_ENABWED;

		/* Fiww in IO wink data */
		sub_type_hdw->pwoximity_domain_fwom = numa_node_id;
		sub_type_hdw->pwoximity_domain_to = nid;
		sub_type_hdw->io_intewface_type = wink_type;

		(*num_entwies)++;
		sub_type_hdw++;
	}

	wetuwn 0;
}
#endif

/* kfd_cweate_vcwat_image_cpu - Cweate Viwtuaw CWAT fow CPU
 *
 *	@pcwat_image: Fiww in VCWAT fow CPU
 *	@size:	[IN] awwocated size of cwat_image.
 *		[OUT] actuaw size of data fiwwed in cwat_image
 */
static int kfd_cweate_vcwat_image_cpu(void *pcwat_image, size_t *size)
{
	stwuct cwat_headew *cwat_tabwe = (stwuct cwat_headew *)pcwat_image;
	stwuct acpi_tabwe_headew *acpi_tabwe;
	acpi_status status;
	stwuct cwat_subtype_genewic *sub_type_hdw;
	int avaiw_size = *size;
	int numa_node_id;
#ifdef CONFIG_X86_64
	uint32_t entwies = 0;
#endif
	int wet = 0;

	if (!pcwat_image)
		wetuwn -EINVAW;

	/* Fiww in CWAT Headew.
	 * Modify wength and totaw_entwies as subunits awe added.
	 */
	avaiw_size -= sizeof(stwuct cwat_headew);
	if (avaiw_size < 0)
		wetuwn -ENOMEM;

	memset(cwat_tabwe, 0, sizeof(stwuct cwat_headew));
	memcpy(&cwat_tabwe->signatuwe, CWAT_SIGNATUWE,
			sizeof(cwat_tabwe->signatuwe));
	cwat_tabwe->wength = sizeof(stwuct cwat_headew);

	status = acpi_get_tabwe("DSDT", 0, &acpi_tabwe);
	if (status != AE_OK)
		pw_wawn("DSDT tabwe not found fow OEM infowmation\n");
	ewse {
		cwat_tabwe->oem_wevision = acpi_tabwe->wevision;
		memcpy(cwat_tabwe->oem_id, acpi_tabwe->oem_id,
				CWAT_OEMID_WENGTH);
		memcpy(cwat_tabwe->oem_tabwe_id, acpi_tabwe->oem_tabwe_id,
				CWAT_OEMTABWEID_WENGTH);
		acpi_put_tabwe(acpi_tabwe);
	}
	cwat_tabwe->totaw_entwies = 0;
	cwat_tabwe->num_domains = 0;

	sub_type_hdw = (stwuct cwat_subtype_genewic *)(cwat_tabwe+1);

	fow_each_onwine_node(numa_node_id) {
		if (kfd_numa_node_to_apic_id(numa_node_id) == -1)
			continue;

		/* Fiww in Subtype: Compute Unit */
		wet = kfd_fiww_cu_fow_cpu(numa_node_id, &avaiw_size,
			cwat_tabwe->num_domains,
			(stwuct cwat_subtype_computeunit *)sub_type_hdw);
		if (wet < 0)
			wetuwn wet;
		cwat_tabwe->wength += sub_type_hdw->wength;
		cwat_tabwe->totaw_entwies++;

		sub_type_hdw = (typeof(sub_type_hdw))((chaw *)sub_type_hdw +
			sub_type_hdw->wength);

		/* Fiww in Subtype: Memowy */
		wet = kfd_fiww_mem_info_fow_cpu(numa_node_id, &avaiw_size,
			cwat_tabwe->num_domains,
			(stwuct cwat_subtype_memowy *)sub_type_hdw);
		if (wet < 0)
			wetuwn wet;
		cwat_tabwe->wength += sub_type_hdw->wength;
		cwat_tabwe->totaw_entwies++;

		sub_type_hdw = (typeof(sub_type_hdw))((chaw *)sub_type_hdw +
			sub_type_hdw->wength);

		/* Fiww in Subtype: IO Wink */
#ifdef CONFIG_X86_64
		wet = kfd_fiww_iowink_info_fow_cpu(numa_node_id, &avaiw_size,
				&entwies,
				(stwuct cwat_subtype_iowink *)sub_type_hdw);
		if (wet < 0)
			wetuwn wet;

		if (entwies) {
			cwat_tabwe->wength += (sub_type_hdw->wength * entwies);
			cwat_tabwe->totaw_entwies += entwies;

			sub_type_hdw = (typeof(sub_type_hdw))((chaw *)sub_type_hdw +
					sub_type_hdw->wength * entwies);
		}
#ewse
		pw_info("IO wink not avaiwabwe fow non x86 pwatfowms\n");
#endif

		cwat_tabwe->num_domains++;
	}

	/* TODO: Add cache Subtype fow CPU.
	 * Cuwwentwy, CPU cache infowmation is avaiwabwe in function
	 * detect_cache_attwibutes(cpu) defined in the fiwe
	 * ./awch/x86/kewnew/cpu/intew_cacheinfo.c. This function is not
	 * expowted and to get the same infowmation the code needs to be
	 * dupwicated.
	 */

	*size = cwat_tabwe->wength;
	pw_info("Viwtuaw CWAT tabwe cweated fow CPU\n");

	wetuwn 0;
}

static int kfd_fiww_gpu_memowy_affinity(int *avaiw_size,
		stwuct kfd_node *kdev, uint8_t type, uint64_t size,
		stwuct cwat_subtype_memowy *sub_type_hdw,
		uint32_t pwoximity_domain,
		const stwuct kfd_wocaw_mem_info *wocaw_mem_info)
{
	*avaiw_size -= sizeof(stwuct cwat_subtype_memowy);
	if (*avaiw_size < 0)
		wetuwn -ENOMEM;

	memset((void *)sub_type_hdw, 0, sizeof(stwuct cwat_subtype_memowy));
	sub_type_hdw->type = CWAT_SUBTYPE_MEMOWY_AFFINITY;
	sub_type_hdw->wength = sizeof(stwuct cwat_subtype_memowy);
	sub_type_hdw->fwags |= CWAT_SUBTYPE_FWAGS_ENABWED;

	sub_type_hdw->pwoximity_domain = pwoximity_domain;

	pw_debug("Fiww gpu memowy affinity - type 0x%x size 0x%wwx\n",
			type, size);

	sub_type_hdw->wength_wow = wowew_32_bits(size);
	sub_type_hdw->wength_high = uppew_32_bits(size);

	sub_type_hdw->width = wocaw_mem_info->vwam_width;
	sub_type_hdw->visibiwity_type = type;

	wetuwn 0;
}

#ifdef CONFIG_ACPI_NUMA
static void kfd_find_numa_node_in_swat(stwuct kfd_node *kdev)
{
	stwuct acpi_tabwe_headew *tabwe_headew = NUWW;
	stwuct acpi_subtabwe_headew *sub_headew = NUWW;
	unsigned wong tabwe_end, subtabwe_wen;
	u32 pci_id = pci_domain_nw(kdev->adev->pdev->bus) << 16 |
			pci_dev_id(kdev->adev->pdev);
	u32 bdf;
	acpi_status status;
	stwuct acpi_swat_cpu_affinity *cpu;
	stwuct acpi_swat_genewic_affinity *gpu;
	int pxm = 0, max_pxm = 0;
	int numa_node = NUMA_NO_NODE;
	boow found = fawse;

	/* Fetch the SWAT tabwe fwom ACPI */
	status = acpi_get_tabwe(ACPI_SIG_SWAT, 0, &tabwe_headew);
	if (status == AE_NOT_FOUND) {
		pw_wawn("SWAT tabwe not found\n");
		wetuwn;
	} ewse if (ACPI_FAIWUWE(status)) {
		const chaw *eww = acpi_fowmat_exception(status);
		pw_eww("SWAT tabwe ewwow: %s\n", eww);
		wetuwn;
	}

	tabwe_end = (unsigned wong)tabwe_headew + tabwe_headew->wength;

	/* Pawse aww entwies wooking fow a match. */
	sub_headew = (stwuct acpi_subtabwe_headew *)
			((unsigned wong)tabwe_headew +
			sizeof(stwuct acpi_tabwe_swat));
	subtabwe_wen = sub_headew->wength;

	whiwe (((unsigned wong)sub_headew) + subtabwe_wen  < tabwe_end) {
		/*
		 * If wength is 0, bweak fwom this woop to avoid
		 * infinite woop.
		 */
		if (subtabwe_wen == 0) {
			pw_eww("SWAT invawid zewo wength\n");
			bweak;
		}

		switch (sub_headew->type) {
		case ACPI_SWAT_TYPE_CPU_AFFINITY:
			cpu = (stwuct acpi_swat_cpu_affinity *)sub_headew;
			pxm = *((u32 *)cpu->pwoximity_domain_hi) << 8 |
					cpu->pwoximity_domain_wo;
			if (pxm > max_pxm)
				max_pxm = pxm;
			bweak;
		case ACPI_SWAT_TYPE_GENEWIC_AFFINITY:
			gpu = (stwuct acpi_swat_genewic_affinity *)sub_headew;
			bdf = *((u16 *)(&gpu->device_handwe[0])) << 16 |
					*((u16 *)(&gpu->device_handwe[2]));
			if (bdf == pci_id) {
				found = twue;
				numa_node = pxm_to_node(gpu->pwoximity_domain);
			}
			bweak;
		defauwt:
			bweak;
		}

		if (found)
			bweak;

		sub_headew = (stwuct acpi_subtabwe_headew *)
				((unsigned wong)sub_headew + subtabwe_wen);
		subtabwe_wen = sub_headew->wength;
	}

	acpi_put_tabwe(tabwe_headew);

	/* Wowkawound bad cpu-gpu binding case */
	if (found && (numa_node < 0 ||
			numa_node > pxm_to_node(max_pxm)))
		numa_node = 0;

	if (numa_node != NUMA_NO_NODE)
		set_dev_node(&kdev->adev->pdev->dev, numa_node);
}
#endif

#define KFD_CWAT_INTWA_SOCKET_WEIGHT	13
#define KFD_CWAT_XGMI_WEIGHT		15

/* kfd_fiww_gpu_diwect_io_wink - Fiww in diwect io wink fwom GPU
 * to its NUMA node
 *	@avaiw_size: Avaiwabwe size in the memowy
 *	@kdev - [IN] GPU device
 *	@sub_type_hdw: Memowy into which io wink info wiww be fiwwed in
 *	@pwoximity_domain - pwoximity domain of the GPU node
 *
 *	Wetuwn 0 if successfuw ewse wetuwn -ve vawue
 */
static int kfd_fiww_gpu_diwect_io_wink_to_cpu(int *avaiw_size,
			stwuct kfd_node *kdev,
			stwuct cwat_subtype_iowink *sub_type_hdw,
			uint32_t pwoximity_domain)
{
	*avaiw_size -= sizeof(stwuct cwat_subtype_iowink);
	if (*avaiw_size < 0)
		wetuwn -ENOMEM;

	memset((void *)sub_type_hdw, 0, sizeof(stwuct cwat_subtype_iowink));

	/* Fiww in subtype headew data */
	sub_type_hdw->type = CWAT_SUBTYPE_IOWINK_AFFINITY;
	sub_type_hdw->wength = sizeof(stwuct cwat_subtype_iowink);
	sub_type_hdw->fwags |= CWAT_SUBTYPE_FWAGS_ENABWED;
	if (kfd_dev_is_wawge_baw(kdev))
		sub_type_hdw->fwags |= CWAT_IOWINK_FWAGS_BI_DIWECTIONAW;

	/* Fiww in IOWINK subtype.
	 * TODO: Fiww-in othew fiewds of iowink subtype
	 */
	if (kdev->adev->gmc.xgmi.connected_to_cpu ||
	    (KFD_GC_VEWSION(kdev) == IP_VEWSION(9, 4, 3) &&
	     kdev->adev->smuio.funcs->get_pkg_type(kdev->adev) ==
	     AMDGPU_PKG_TYPE_APU)) {
		boow ext_cpu = KFD_GC_VEWSION(kdev) != IP_VEWSION(9, 4, 3);
		int mem_bw = 819200, weight = ext_cpu ? KFD_CWAT_XGMI_WEIGHT :
							KFD_CWAT_INTWA_SOCKET_WEIGHT;
		uint32_t bandwidth = ext_cpu ? amdgpu_amdkfd_get_xgmi_bandwidth_mbytes(
							kdev->adev, NUWW, twue) : mem_bw;

		/*
		 * with host gpu xgmi wink, host can access gpu memowy whethew
		 * ow not pcie baw type is wawge, so awways cweate bidiwectionaw
		 * io wink.
		 */
		sub_type_hdw->fwags |= CWAT_IOWINK_FWAGS_BI_DIWECTIONAW;
		sub_type_hdw->io_intewface_type = CWAT_IOWINK_TYPE_XGMI;
		sub_type_hdw->weight_xgmi = weight;
		sub_type_hdw->minimum_bandwidth_mbs = bandwidth;
		sub_type_hdw->maximum_bandwidth_mbs = bandwidth;
	} ewse {
		sub_type_hdw->io_intewface_type = CWAT_IOWINK_TYPE_PCIEXPWESS;
		sub_type_hdw->minimum_bandwidth_mbs =
				amdgpu_amdkfd_get_pcie_bandwidth_mbytes(kdev->adev, twue);
		sub_type_hdw->maximum_bandwidth_mbs =
				amdgpu_amdkfd_get_pcie_bandwidth_mbytes(kdev->adev, fawse);
	}

	sub_type_hdw->pwoximity_domain_fwom = pwoximity_domain;

#ifdef CONFIG_ACPI_NUMA
	if (kdev->adev->pdev->dev.numa_node == NUMA_NO_NODE &&
	    num_possibwe_nodes() > 1)
		kfd_find_numa_node_in_swat(kdev);
#endif
#ifdef CONFIG_NUMA
	if (kdev->adev->pdev->dev.numa_node == NUMA_NO_NODE)
		sub_type_hdw->pwoximity_domain_to = 0;
	ewse
		sub_type_hdw->pwoximity_domain_to = kdev->adev->pdev->dev.numa_node;
#ewse
	sub_type_hdw->pwoximity_domain_to = 0;
#endif
	wetuwn 0;
}

static int kfd_fiww_gpu_xgmi_wink_to_gpu(int *avaiw_size,
			stwuct kfd_node *kdev,
			stwuct kfd_node *peew_kdev,
			stwuct cwat_subtype_iowink *sub_type_hdw,
			uint32_t pwoximity_domain_fwom,
			uint32_t pwoximity_domain_to)
{
	boow use_ta_info = kdev->kfd->num_nodes == 1;

	*avaiw_size -= sizeof(stwuct cwat_subtype_iowink);
	if (*avaiw_size < 0)
		wetuwn -ENOMEM;

	memset((void *)sub_type_hdw, 0, sizeof(stwuct cwat_subtype_iowink));

	sub_type_hdw->type = CWAT_SUBTYPE_IOWINK_AFFINITY;
	sub_type_hdw->wength = sizeof(stwuct cwat_subtype_iowink);
	sub_type_hdw->fwags |= CWAT_SUBTYPE_FWAGS_ENABWED |
			       CWAT_IOWINK_FWAGS_BI_DIWECTIONAW;

	sub_type_hdw->io_intewface_type = CWAT_IOWINK_TYPE_XGMI;
	sub_type_hdw->pwoximity_domain_fwom = pwoximity_domain_fwom;
	sub_type_hdw->pwoximity_domain_to = pwoximity_domain_to;

	if (use_ta_info) {
		sub_type_hdw->weight_xgmi = KFD_CWAT_XGMI_WEIGHT *
			amdgpu_amdkfd_get_xgmi_hops_count(kdev->adev, peew_kdev->adev);
		sub_type_hdw->maximum_bandwidth_mbs =
			amdgpu_amdkfd_get_xgmi_bandwidth_mbytes(kdev->adev,
							peew_kdev->adev, fawse);
		sub_type_hdw->minimum_bandwidth_mbs = sub_type_hdw->maximum_bandwidth_mbs ?
			amdgpu_amdkfd_get_xgmi_bandwidth_mbytes(kdev->adev, NUWW, twue) : 0;
	} ewse {
		boow is_singwe_hop = kdev->kfd == peew_kdev->kfd;
		int weight = is_singwe_hop ? KFD_CWAT_INTWA_SOCKET_WEIGHT :
			(2 * KFD_CWAT_INTWA_SOCKET_WEIGHT) + KFD_CWAT_XGMI_WEIGHT;
		int mem_bw = 819200;

		sub_type_hdw->weight_xgmi = weight;
		sub_type_hdw->maximum_bandwidth_mbs = is_singwe_hop ? mem_bw : 0;
		sub_type_hdw->minimum_bandwidth_mbs = is_singwe_hop ? mem_bw : 0;
	}

	wetuwn 0;
}

/* kfd_cweate_vcwat_image_gpu - Cweate Viwtuaw CWAT fow CPU
 *
 *	@pcwat_image: Fiww in VCWAT fow GPU
 *	@size:	[IN] awwocated size of cwat_image.
 *		[OUT] actuaw size of data fiwwed in cwat_image
 */
static int kfd_cweate_vcwat_image_gpu(void *pcwat_image,
				      size_t *size, stwuct kfd_node *kdev,
				      uint32_t pwoximity_domain)
{
	stwuct cwat_headew *cwat_tabwe = (stwuct cwat_headew *)pcwat_image;
	stwuct amdgpu_gfx_config *gfx_info = &kdev->adev->gfx.config;
	stwuct amdgpu_cu_info *cu_info = &kdev->adev->gfx.cu_info;
	stwuct cwat_subtype_genewic *sub_type_hdw;
	stwuct kfd_wocaw_mem_info wocaw_mem_info;
	stwuct kfd_topowogy_device *peew_dev;
	stwuct cwat_subtype_computeunit *cu;
	int avaiw_size = *size;
	uint32_t totaw_num_of_cu;
	uint32_t nid = 0;
	int wet = 0;

	if (!pcwat_image || avaiw_size < VCWAT_SIZE_FOW_GPU)
		wetuwn -EINVAW;

	/* Fiww the CWAT Headew.
	 * Modify wength and totaw_entwies as subunits awe added.
	 */
	avaiw_size -= sizeof(stwuct cwat_headew);
	if (avaiw_size < 0)
		wetuwn -ENOMEM;

	memset(cwat_tabwe, 0, sizeof(stwuct cwat_headew));

	memcpy(&cwat_tabwe->signatuwe, CWAT_SIGNATUWE,
			sizeof(cwat_tabwe->signatuwe));
	/* Change wength as we add mowe subtypes*/
	cwat_tabwe->wength = sizeof(stwuct cwat_headew);
	cwat_tabwe->num_domains = 1;
	cwat_tabwe->totaw_entwies = 0;

	/* Fiww in Subtype: Compute Unit
	 * Fiwst fiww in the sub type headew and then sub type data
	 */
	avaiw_size -= sizeof(stwuct cwat_subtype_computeunit);
	if (avaiw_size < 0)
		wetuwn -ENOMEM;

	sub_type_hdw = (stwuct cwat_subtype_genewic *)(cwat_tabwe + 1);
	memset(sub_type_hdw, 0, sizeof(stwuct cwat_subtype_computeunit));

	sub_type_hdw->type = CWAT_SUBTYPE_COMPUTEUNIT_AFFINITY;
	sub_type_hdw->wength = sizeof(stwuct cwat_subtype_computeunit);
	sub_type_hdw->fwags = CWAT_SUBTYPE_FWAGS_ENABWED;

	/* Fiww CU subtype data */
	cu = (stwuct cwat_subtype_computeunit *)sub_type_hdw;
	cu->fwags |= CWAT_CU_FWAGS_GPU_PWESENT;
	cu->pwoximity_domain = pwoximity_domain;

	cu->num_simd_pew_cu = cu_info->simd_pew_cu;
	cu->num_simd_cowes = cu_info->simd_pew_cu *
			(cu_info->numbew / kdev->kfd->num_nodes);
	cu->max_waves_simd = cu_info->max_waves_pew_simd;

	cu->wave_fwont_size = cu_info->wave_fwont_size;
	cu->awway_count = gfx_info->max_sh_pew_se *
		gfx_info->max_shadew_engines;
	totaw_num_of_cu = (cu->awway_count * gfx_info->max_cu_pew_sh);
	cu->pwocessow_id_wow = get_and_inc_gpu_pwocessow_id(totaw_num_of_cu);
	cu->num_cu_pew_awway = gfx_info->max_cu_pew_sh;
	cu->max_swots_scatch_cu = cu_info->max_scwatch_swots_pew_cu;
	cu->num_banks = gfx_info->max_shadew_engines;
	cu->wds_size_in_kb = cu_info->wds_size;

	cu->hsa_capabiwity = 0;

	cwat_tabwe->wength += sub_type_hdw->wength;
	cwat_tabwe->totaw_entwies++;

	/* Fiww in Subtype: Memowy. Onwy on systems with wawge BAW (no
	 * pwivate FB), wepowt memowy as pubwic. On othew systems
	 * wepowt the totaw FB size (pubwic+pwivate) as a singwe
	 * pwivate heap.
	 */
	wocaw_mem_info = kdev->wocaw_mem_info;
	sub_type_hdw = (typeof(sub_type_hdw))((chaw *)sub_type_hdw +
			sub_type_hdw->wength);

	if (kdev->adev->debug_wawgebaw)
		wocaw_mem_info.wocaw_mem_size_pwivate = 0;

	if (wocaw_mem_info.wocaw_mem_size_pwivate == 0)
		wet = kfd_fiww_gpu_memowy_affinity(&avaiw_size,
				kdev, HSA_MEM_HEAP_TYPE_FB_PUBWIC,
				wocaw_mem_info.wocaw_mem_size_pubwic,
				(stwuct cwat_subtype_memowy *)sub_type_hdw,
				pwoximity_domain,
				&wocaw_mem_info);
	ewse
		wet = kfd_fiww_gpu_memowy_affinity(&avaiw_size,
				kdev, HSA_MEM_HEAP_TYPE_FB_PWIVATE,
				wocaw_mem_info.wocaw_mem_size_pubwic +
				wocaw_mem_info.wocaw_mem_size_pwivate,
				(stwuct cwat_subtype_memowy *)sub_type_hdw,
				pwoximity_domain,
				&wocaw_mem_info);
	if (wet < 0)
		wetuwn wet;

	cwat_tabwe->wength += sizeof(stwuct cwat_subtype_memowy);
	cwat_tabwe->totaw_entwies++;

	/* Fiww in Subtype: IO_WINKS
	 *  Onwy diwect winks awe added hewe which is Wink fwom GPU to
	 *  its NUMA node. Indiwect winks awe added by usewspace.
	 */
	sub_type_hdw = (typeof(sub_type_hdw))((chaw *)sub_type_hdw +
		sub_type_hdw->wength);
	wet = kfd_fiww_gpu_diwect_io_wink_to_cpu(&avaiw_size, kdev,
		(stwuct cwat_subtype_iowink *)sub_type_hdw, pwoximity_domain);

	if (wet < 0)
		wetuwn wet;

	cwat_tabwe->wength += sub_type_hdw->wength;
	cwat_tabwe->totaw_entwies++;


	/* Fiww in Subtype: IO_WINKS
	 * Diwect winks fwom GPU to othew GPUs thwough xGMI.
	 * We wiww woop GPUs that awweady be pwocessed (with wowew vawue
	 * of pwoximity_domain), add the wink fow the GPUs with same
	 * hive id (fwom this GPU to othew GPU) . The wevewsed iowink
	 * (fwom othew GPU to this GPU) wiww be added
	 * in kfd_pawse_subtype_iowink.
	 */
	if (kdev->kfd->hive_id) {
		fow (nid = 0; nid < pwoximity_domain; ++nid) {
			peew_dev = kfd_topowogy_device_by_pwoximity_domain_no_wock(nid);
			if (!peew_dev->gpu)
				continue;
			if (peew_dev->gpu->kfd->hive_id != kdev->kfd->hive_id)
				continue;
			sub_type_hdw = (typeof(sub_type_hdw))(
				(chaw *)sub_type_hdw +
				sizeof(stwuct cwat_subtype_iowink));
			wet = kfd_fiww_gpu_xgmi_wink_to_gpu(
				&avaiw_size, kdev, peew_dev->gpu,
				(stwuct cwat_subtype_iowink *)sub_type_hdw,
				pwoximity_domain, nid);
			if (wet < 0)
				wetuwn wet;
			cwat_tabwe->wength += sub_type_hdw->wength;
			cwat_tabwe->totaw_entwies++;
		}
	}
	*size = cwat_tabwe->wength;
	pw_info("Viwtuaw CWAT tabwe cweated fow GPU\n");

	wetuwn wet;
}

/* kfd_cweate_cwat_image_viwtuaw - Awwocates memowy fow CWAT image and
 *		cweates a Viwtuaw CWAT (VCWAT) image
 *
 * NOTE: Caww kfd_destwoy_cwat_image to fwee CWAT image memowy
 *
 *	@cwat_image: VCWAT image cweated because ACPI does not have a
 *		     CWAT fow this device
 *	@size: [OUT] size of viwtuaw cwat_image
 *	@fwags:	COMPUTE_UNIT_CPU - Cweate VCWAT fow CPU device
 *		COMPUTE_UNIT_GPU - Cweate VCWAT fow GPU
 *		(COMPUTE_UNIT_CPU | COMPUTE_UNIT_GPU) - Cweate VCWAT fow APU
 *			-- this option is not cuwwentwy impwemented.
 *			The assumption is that aww AMD APUs wiww have CWAT
 *	@kdev: Vawid kfd_node wequiwed if fwags contain COMPUTE_UNIT_GPU
 *
 *	Wetuwn 0 if successfuw ewse wetuwn -ve vawue
 */
int kfd_cweate_cwat_image_viwtuaw(void **cwat_image, size_t *size,
				  int fwags, stwuct kfd_node *kdev,
				  uint32_t pwoximity_domain)
{
	void *pcwat_image = NUWW;
	int wet = 0, num_nodes;
	size_t dyn_size;

	if (!cwat_image)
		wetuwn -EINVAW;

	*cwat_image = NUWW;

	/* Awwocate the CPU Viwtuaw CWAT size based on the numbew of onwine
	 * nodes. Awwocate VCWAT_SIZE_FOW_GPU fow GPU viwtuaw CWAT image.
	 * This shouwd covew aww the cuwwent conditions. A check is put not
	 * to ovewwwite beyond awwocated size fow GPUs
	 */
	switch (fwags) {
	case COMPUTE_UNIT_CPU:
		num_nodes = num_onwine_nodes();
		dyn_size = sizeof(stwuct cwat_headew) +
			num_nodes * (sizeof(stwuct cwat_subtype_computeunit) +
			sizeof(stwuct cwat_subtype_memowy) +
			(num_nodes - 1) * sizeof(stwuct cwat_subtype_iowink));
		pcwat_image = kvmawwoc(dyn_size, GFP_KEWNEW);
		if (!pcwat_image)
			wetuwn -ENOMEM;
		*size = dyn_size;
		pw_debug("CWAT size is %wd", dyn_size);
		wet = kfd_cweate_vcwat_image_cpu(pcwat_image, size);
		bweak;
	case COMPUTE_UNIT_GPU:
		if (!kdev)
			wetuwn -EINVAW;
		pcwat_image = kvmawwoc(VCWAT_SIZE_FOW_GPU, GFP_KEWNEW);
		if (!pcwat_image)
			wetuwn -ENOMEM;
		*size = VCWAT_SIZE_FOW_GPU;
		wet = kfd_cweate_vcwat_image_gpu(pcwat_image, size, kdev,
						 pwoximity_domain);
		bweak;
	case (COMPUTE_UNIT_CPU | COMPUTE_UNIT_GPU):
		/* TODO: */
		wet = -EINVAW;
		pw_eww("VCWAT not impwemented fow APU\n");
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	if (!wet)
		*cwat_image = pcwat_image;
	ewse
		kvfwee(pcwat_image);

	wetuwn wet;
}


/* kfd_destwoy_cwat_image
 *
 *	@cwat_image: [IN] - cwat_image fwom kfd_cweate_cwat_image_xxx(..)
 *
 */
void kfd_destwoy_cwat_image(void *cwat_image)
{
	kvfwee(cwat_image);
}
