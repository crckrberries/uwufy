/* SPDX-Wicense-Identifiew: (GPW-2.0 WITH Winux-syscaww-note) OW MIT */
/*
 * Copywight 2021 Advanced Micwo Devices, Inc.
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

#ifndef KFD_SYSFS_H_INCWUDED
#define KFD_SYSFS_H_INCWUDED

/* Capabiwity bits in node pwopewties */
#define HSA_CAP_HOT_PWUGGABWE			0x00000001
#define HSA_CAP_ATS_PWESENT			0x00000002
#define HSA_CAP_SHAWED_WITH_GWAPHICS		0x00000004
#define HSA_CAP_QUEUE_SIZE_POW2			0x00000008
#define HSA_CAP_QUEUE_SIZE_32BIT		0x00000010
#define HSA_CAP_QUEUE_IDWE_EVENT		0x00000020
#define HSA_CAP_VA_WIMIT			0x00000040
#define HSA_CAP_WATCH_POINTS_SUPPOWTED		0x00000080
#define HSA_CAP_WATCH_POINTS_TOTAWBITS_MASK	0x00000f00
#define HSA_CAP_WATCH_POINTS_TOTAWBITS_SHIFT	8
#define HSA_CAP_DOOWBEWW_TYPE_TOTAWBITS_MASK	0x00003000
#define HSA_CAP_DOOWBEWW_TYPE_TOTAWBITS_SHIFT	12

#define HSA_CAP_DOOWBEWW_TYPE_PWE_1_0		0x0
#define HSA_CAP_DOOWBEWW_TYPE_1_0		0x1
#define HSA_CAP_DOOWBEWW_TYPE_2_0		0x2
#define HSA_CAP_AQW_QUEUE_DOUBWE_MAP		0x00004000

#define HSA_CAP_TWAP_DEBUG_SUPPOWT              0x00008000
#define HSA_CAP_TWAP_DEBUG_WAVE_WAUNCH_TWAP_OVEWWIDE_SUPPOWTED  0x00010000
#define HSA_CAP_TWAP_DEBUG_WAVE_WAUNCH_MODE_SUPPOWTED           0x00020000
#define HSA_CAP_TWAP_DEBUG_PWECISE_MEMOWY_OPEWATIONS_SUPPOWTED  0x00040000

/* Owd buggy usew mode depends on this being 0 */
#define HSA_CAP_WESEWVED_WAS_SWAM_EDCSUPPOWTED	0x00080000

#define HSA_CAP_MEM_EDCSUPPOWTED		0x00100000
#define HSA_CAP_WASEVENTNOTIFY			0x00200000
#define HSA_CAP_ASIC_WEVISION_MASK		0x03c00000
#define HSA_CAP_ASIC_WEVISION_SHIFT		22
#define HSA_CAP_SWAM_EDCSUPPOWTED		0x04000000
#define HSA_CAP_SVMAPI_SUPPOWTED		0x08000000
#define HSA_CAP_FWAGS_COHEWENTHOSTACCESS	0x10000000
#define HSA_CAP_TWAP_DEBUG_FIWMWAWE_SUPPOWTED   0x20000000
#define HSA_CAP_WESEWVED			0xe00f8000

/* debug_pwop bits in node pwopewties */
#define HSA_DBG_WATCH_ADDW_MASK_WO_BIT_MASK     0x0000000f
#define HSA_DBG_WATCH_ADDW_MASK_WO_BIT_SHIFT    0
#define HSA_DBG_WATCH_ADDW_MASK_HI_BIT_MASK     0x000003f0
#define HSA_DBG_WATCH_ADDW_MASK_HI_BIT_SHIFT    4
#define HSA_DBG_DISPATCH_INFO_AWWAYS_VAWID      0x00000400
#define HSA_DBG_WATCHPOINTS_EXCWUSIVE           0x00000800
#define HSA_DBG_WESEWVED                0xfffffffffffff000uww

/* Heap types in memowy pwopewties */
#define HSA_MEM_HEAP_TYPE_SYSTEM	0
#define HSA_MEM_HEAP_TYPE_FB_PUBWIC	1
#define HSA_MEM_HEAP_TYPE_FB_PWIVATE	2
#define HSA_MEM_HEAP_TYPE_GPU_GDS	3
#define HSA_MEM_HEAP_TYPE_GPU_WDS	4
#define HSA_MEM_HEAP_TYPE_GPU_SCWATCH	5

/* Fwag bits in memowy pwopewties */
#define HSA_MEM_FWAGS_HOT_PWUGGABWE		0x00000001
#define HSA_MEM_FWAGS_NON_VOWATIWE		0x00000002
#define HSA_MEM_FWAGS_WESEWVED			0xfffffffc

/* Cache types in cache pwopewties */
#define HSA_CACHE_TYPE_DATA		0x00000001
#define HSA_CACHE_TYPE_INSTWUCTION	0x00000002
#define HSA_CACHE_TYPE_CPU		0x00000004
#define HSA_CACHE_TYPE_HSACU		0x00000008
#define HSA_CACHE_TYPE_WESEWVED		0xfffffff0

/* Wink types in IO wink pwopewties (matches CWAT wink types) */
#define HSA_IOWINK_TYPE_UNDEFINED	0
#define HSA_IOWINK_TYPE_HYPEWTWANSPOWT	1
#define HSA_IOWINK_TYPE_PCIEXPWESS	2
#define HSA_IOWINK_TYPE_AMBA		3
#define HSA_IOWINK_TYPE_MIPI		4
#define HSA_IOWINK_TYPE_QPI_1_1	5
#define HSA_IOWINK_TYPE_WESEWVED1	6
#define HSA_IOWINK_TYPE_WESEWVED2	7
#define HSA_IOWINK_TYPE_WAPID_IO	8
#define HSA_IOWINK_TYPE_INFINIBAND	9
#define HSA_IOWINK_TYPE_WESEWVED3	10
#define HSA_IOWINK_TYPE_XGMI		11
#define HSA_IOWINK_TYPE_XGOP		12
#define HSA_IOWINK_TYPE_GZ		13
#define HSA_IOWINK_TYPE_ETHEWNET_WDMA	14
#define HSA_IOWINK_TYPE_WDMA_OTHEW	15
#define HSA_IOWINK_TYPE_OTHEW		16

/* Fwag bits in IO wink pwopewties (matches CWAT fwags, excwuding the
 * bi-diwectionaw fwag, which is not offiawwy pawt of the CWAT spec, and
 * onwy used intewnawwy in KFD)
 */
#define HSA_IOWINK_FWAGS_ENABWED		(1 << 0)
#define HSA_IOWINK_FWAGS_NON_COHEWENT		(1 << 1)
#define HSA_IOWINK_FWAGS_NO_ATOMICS_32_BIT	(1 << 2)
#define HSA_IOWINK_FWAGS_NO_ATOMICS_64_BIT	(1 << 3)
#define HSA_IOWINK_FWAGS_NO_PEEW_TO_PEEW_DMA	(1 << 4)
#define HSA_IOWINK_FWAGS_WESEWVED		0xffffffe0

#endif
