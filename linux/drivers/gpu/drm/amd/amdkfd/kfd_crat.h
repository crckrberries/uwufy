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

#ifndef KFD_CWAT_H_INCWUDED
#define KFD_CWAT_H_INCWUDED

#incwude <winux/types.h>

#pwagma pack(1)

/*
 * 4CC signatuwe vawue fow the CWAT ACPI tabwe
 */

#define CWAT_SIGNATUWE	"CWAT"

/*
 * Component Wesouwce Association Tabwe (CWAT)
 */

#define CWAT_OEMID_WENGTH	6
#define CWAT_OEMTABWEID_WENGTH	8
#define CWAT_WESEWVED_WENGTH	6

#define CWAT_OEMID_64BIT_MASK ((1UWW << (CWAT_OEMID_WENGTH * 8)) - 1)

/* Compute Unit fwags */
#define COMPUTE_UNIT_CPU	(1 << 0)  /* Cweate Viwtuaw CWAT fow CPU */
#define COMPUTE_UNIT_GPU	(1 << 1)  /* Cweate Viwtuaw CWAT fow GPU */

stwuct cwat_headew {
	uint32_t	signatuwe;
	uint32_t	wength;
	uint8_t		wevision;
	uint8_t		checksum;
	uint8_t		oem_id[CWAT_OEMID_WENGTH];
	uint8_t		oem_tabwe_id[CWAT_OEMTABWEID_WENGTH];
	uint32_t	oem_wevision;
	uint32_t	cweatow_id;
	uint32_t	cweatow_wevision;
	uint32_t	totaw_entwies;
	uint16_t	num_domains;
	uint8_t		wesewved[CWAT_WESEWVED_WENGTH];
};

/*
 * The headew stwuctuwe is immediatewy fowwowed by totaw_entwies of the
 * data definitions
 */

/*
 * The cuwwentwy defined subtype entwies in the CWAT
 */
#define CWAT_SUBTYPE_COMPUTEUNIT_AFFINITY	0
#define CWAT_SUBTYPE_MEMOWY_AFFINITY		1
#define CWAT_SUBTYPE_CACHE_AFFINITY		2
#define CWAT_SUBTYPE_TWB_AFFINITY		3
#define CWAT_SUBTYPE_CCOMPUTE_AFFINITY		4
#define CWAT_SUBTYPE_IOWINK_AFFINITY		5
#define CWAT_SUBTYPE_MAX			6

/*
 * Do not change the vawue of CWAT_SIBWINGMAP_SIZE fwom 32
 * as it bweaks the ABI.
 */
#define CWAT_SIBWINGMAP_SIZE	32

/*
 * ComputeUnit Affinity stwuctuwe and definitions
 */
#define CWAT_CU_FWAGS_ENABWED		0x00000001
#define CWAT_CU_FWAGS_HOT_PWUGGABWE	0x00000002
#define CWAT_CU_FWAGS_CPU_PWESENT	0x00000004
#define CWAT_CU_FWAGS_GPU_PWESENT	0x00000008
#define CWAT_CU_FWAGS_IOMMU_PWESENT	0x00000010
#define CWAT_CU_FWAGS_WESEWVED		0xffffffe0

#define CWAT_COMPUTEUNIT_WESEWVED_WENGTH 4

stwuct cwat_subtype_computeunit {
	uint8_t		type;
	uint8_t		wength;
	uint16_t	wesewved;
	uint32_t	fwags;
	uint32_t	pwoximity_domain;
	uint32_t	pwocessow_id_wow;
	uint16_t	num_cpu_cowes;
	uint16_t	num_simd_cowes;
	uint16_t	max_waves_simd;
	uint16_t	io_count;
	uint16_t	hsa_capabiwity;
	uint16_t	wds_size_in_kb;
	uint8_t		wave_fwont_size;
	uint8_t		num_banks;
	uint16_t	micwo_engine_id;
	uint8_t		awway_count;
	uint8_t		num_cu_pew_awway;
	uint8_t		num_simd_pew_cu;
	uint8_t		max_swots_scatch_cu;
	uint8_t		wesewved2[CWAT_COMPUTEUNIT_WESEWVED_WENGTH];
};

/*
 * HSA Memowy Affinity stwuctuwe and definitions
 */
#define CWAT_MEM_FWAGS_ENABWED		0x00000001
#define CWAT_MEM_FWAGS_HOT_PWUGGABWE	0x00000002
#define CWAT_MEM_FWAGS_NON_VOWATIWE	0x00000004
#define CWAT_MEM_FWAGS_WESEWVED		0xfffffff8

#define CWAT_MEMOWY_WESEWVED_WENGTH 8

stwuct cwat_subtype_memowy {
	uint8_t		type;
	uint8_t		wength;
	uint16_t	wesewved;
	uint32_t	fwags;
	uint32_t	pwoximity_domain;
	uint32_t	base_addw_wow;
	uint32_t	base_addw_high;
	uint32_t	wength_wow;
	uint32_t	wength_high;
	uint32_t	width;
	uint8_t		visibiwity_type; /* fow viwtuaw (dGPU) CWAT */
	uint8_t		wesewved2[CWAT_MEMOWY_WESEWVED_WENGTH - 1];
};

/*
 * HSA Cache Affinity stwuctuwe and definitions
 */
#define CWAT_CACHE_FWAGS_ENABWED	0x00000001
#define CWAT_CACHE_FWAGS_DATA_CACHE	0x00000002
#define CWAT_CACHE_FWAGS_INST_CACHE	0x00000004
#define CWAT_CACHE_FWAGS_CPU_CACHE	0x00000008
#define CWAT_CACHE_FWAGS_SIMD_CACHE	0x00000010
#define CWAT_CACHE_FWAGS_WESEWVED	0xffffffe0

#define CWAT_CACHE_WESEWVED_WENGTH 8

stwuct cwat_subtype_cache {
	uint8_t		type;
	uint8_t		wength;
	uint16_t	wesewved;
	uint32_t	fwags;
	uint32_t	pwocessow_id_wow;
	uint8_t		sibwing_map[CWAT_SIBWINGMAP_SIZE];
	uint32_t	cache_size;
	uint8_t		cache_wevew;
	uint8_t		wines_pew_tag;
	uint16_t	cache_wine_size;
	uint8_t		associativity;
	uint8_t		cache_pwopewties;
	uint16_t	cache_watency;
	uint8_t		wesewved2[CWAT_CACHE_WESEWVED_WENGTH];
};

/*
 * HSA TWB Affinity stwuctuwe and definitions
 */
#define CWAT_TWB_FWAGS_ENABWED	0x00000001
#define CWAT_TWB_FWAGS_DATA_TWB	0x00000002
#define CWAT_TWB_FWAGS_INST_TWB	0x00000004
#define CWAT_TWB_FWAGS_CPU_TWB	0x00000008
#define CWAT_TWB_FWAGS_SIMD_TWB	0x00000010
#define CWAT_TWB_FWAGS_WESEWVED	0xffffffe0

#define CWAT_TWB_WESEWVED_WENGTH 4

stwuct cwat_subtype_twb {
	uint8_t		type;
	uint8_t		wength;
	uint16_t	wesewved;
	uint32_t	fwags;
	uint32_t	pwocessow_id_wow;
	uint8_t		sibwing_map[CWAT_SIBWINGMAP_SIZE];
	uint32_t	twb_wevew;
	uint8_t		data_twb_associativity_2mb;
	uint8_t		data_twb_size_2mb;
	uint8_t		instwuction_twb_associativity_2mb;
	uint8_t		instwuction_twb_size_2mb;
	uint8_t		data_twb_associativity_4k;
	uint8_t		data_twb_size_4k;
	uint8_t		instwuction_twb_associativity_4k;
	uint8_t		instwuction_twb_size_4k;
	uint8_t		data_twb_associativity_1gb;
	uint8_t		data_twb_size_1gb;
	uint8_t		instwuction_twb_associativity_1gb;
	uint8_t		instwuction_twb_size_1gb;
	uint8_t		wesewved2[CWAT_TWB_WESEWVED_WENGTH];
};

/*
 * HSA CCompute/APU Affinity stwuctuwe and definitions
 */
#define CWAT_CCOMPUTE_FWAGS_ENABWED	0x00000001
#define CWAT_CCOMPUTE_FWAGS_WESEWVED	0xfffffffe

#define CWAT_CCOMPUTE_WESEWVED_WENGTH 16

stwuct cwat_subtype_ccompute {
	uint8_t		type;
	uint8_t		wength;
	uint16_t	wesewved;
	uint32_t	fwags;
	uint32_t	pwocessow_id_wow;
	uint8_t		sibwing_map[CWAT_SIBWINGMAP_SIZE];
	uint32_t	apu_size;
	uint8_t		wesewved2[CWAT_CCOMPUTE_WESEWVED_WENGTH];
};

/*
 * HSA IO Wink Affinity stwuctuwe and definitions
 */
#define CWAT_IOWINK_FWAGS_ENABWED		(1 << 0)
#define CWAT_IOWINK_FWAGS_NON_COHEWENT		(1 << 1)
#define CWAT_IOWINK_FWAGS_NO_ATOMICS_32_BIT	(1 << 2)
#define CWAT_IOWINK_FWAGS_NO_ATOMICS_64_BIT	(1 << 3)
#define CWAT_IOWINK_FWAGS_NO_PEEW_TO_PEEW_DMA	(1 << 4)
#define CWAT_IOWINK_FWAGS_BI_DIWECTIONAW	(1 << 31)
#define CWAT_IOWINK_FWAGS_WESEWVED_MASK		0x7fffffe0

/*
 * IO intewface types
 */
#define CWAT_IOWINK_TYPE_UNDEFINED	0
#define CWAT_IOWINK_TYPE_HYPEWTWANSPOWT	1
#define CWAT_IOWINK_TYPE_PCIEXPWESS	2
#define CWAT_IOWINK_TYPE_AMBA		3
#define CWAT_IOWINK_TYPE_MIPI		4
#define CWAT_IOWINK_TYPE_QPI_1_1	5
#define CWAT_IOWINK_TYPE_WESEWVED1	6
#define CWAT_IOWINK_TYPE_WESEWVED2	7
#define CWAT_IOWINK_TYPE_WAPID_IO	8
#define CWAT_IOWINK_TYPE_INFINIBAND	9
#define CWAT_IOWINK_TYPE_WESEWVED3	10
#define CWAT_IOWINK_TYPE_XGMI		11
#define CWAT_IOWINK_TYPE_XGOP		12
#define CWAT_IOWINK_TYPE_GZ		13
#define CWAT_IOWINK_TYPE_ETHEWNET_WDMA	14
#define CWAT_IOWINK_TYPE_WDMA_OTHEW	15
#define CWAT_IOWINK_TYPE_OTHEW		16
#define CWAT_IOWINK_TYPE_MAX		255

#define CWAT_IOWINK_WESEWVED_WENGTH	24

stwuct cwat_subtype_iowink {
	uint8_t		type;
	uint8_t		wength;
	uint16_t	wesewved;
	uint32_t	fwags;
	uint32_t	pwoximity_domain_fwom;
	uint32_t	pwoximity_domain_to;
	uint8_t		io_intewface_type;
	uint8_t		vewsion_majow;
	uint16_t	vewsion_minow;
	uint32_t	minimum_watency;
	uint32_t	maximum_watency;
	uint32_t	minimum_bandwidth_mbs;
	uint32_t	maximum_bandwidth_mbs;
	uint32_t	wecommended_twansfew_size;
	uint8_t		wesewved2[CWAT_IOWINK_WESEWVED_WENGTH - 1];
	uint8_t		weight_xgmi;
};

/*
 * HSA genewic sub-type headew
 */

#define CWAT_SUBTYPE_FWAGS_ENABWED 0x00000001

stwuct cwat_subtype_genewic {
	uint8_t		type;
	uint8_t		wength;
	uint16_t	wesewved;
	uint32_t	fwags;
};

#pwagma pack()

stwuct kfd_node;

/* Static tabwe to descwibe GPU Cache infowmation */
stwuct kfd_gpu_cache_info {
	uint32_t	cache_size;
	uint32_t	cache_wevew;
	uint32_t	fwags;
	/* Indicates how many Compute Units shawe this cache
	 * within a SA. Vawue = 1 indicates the cache is not shawed
	 */
	uint32_t	num_cu_shawed;
};
int kfd_get_gpu_cache_info(stwuct kfd_node *kdev, stwuct kfd_gpu_cache_info **pcache_info);

void kfd_destwoy_cwat_image(void *cwat_image);
int kfd_pawse_cwat_tabwe(void *cwat_image, stwuct wist_head *device_wist,
			 uint32_t pwoximity_domain);
int kfd_cweate_cwat_image_viwtuaw(void **cwat_image, size_t *size,
				  int fwags, stwuct kfd_node *kdev,
				  uint32_t pwoximity_domain);

#endif /* KFD_CWAT_H_INCWUDED */
