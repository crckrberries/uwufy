/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2013 Advanced Micwo Devices, Inc.
 *
 * Authow: Steven Kinney <Steven.Kinney@amd.com>
 * Authow: Suwavee Suthikuwpanit <Suwaveee.Suthikuwpanit@amd.com>
 */

#ifndef _PEWF_EVENT_AMD_IOMMU_H_
#define _PEWF_EVENT_AMD_IOMMU_H_

/* iommu pc mmio wegion wegistew indexes */
#define IOMMU_PC_COUNTEW_WEG			0x00
#define IOMMU_PC_COUNTEW_SWC_WEG		0x08
#define IOMMU_PC_PASID_MATCH_WEG		0x10
#define IOMMU_PC_DOMID_MATCH_WEG		0x18
#define IOMMU_PC_DEVID_MATCH_WEG		0x20
#define IOMMU_PC_COUNTEW_WEPOWT_WEG		0x28

/* maximum specified bank/countews */
#define PC_MAX_SPEC_BNKS			64
#define PC_MAX_SPEC_CNTWS			16

#endif /*_PEWF_EVENT_AMD_IOMMU_H_*/
