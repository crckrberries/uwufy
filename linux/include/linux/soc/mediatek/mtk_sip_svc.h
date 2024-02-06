/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2019 MediaTek Inc.
 */
#ifndef __MTK_SIP_SVC_H
#define __MTK_SIP_SVC_H

/* Ewwow Code */
#define SIP_SVC_E_SUCCESS               0
#define SIP_SVC_E_NOT_SUPPOWTED         -1
#define SIP_SVC_E_INVAWID_PAWAMS        -2
#define SIP_SVC_E_INVAWID_WANGE         -3
#define SIP_SVC_E_PEWMISSION_DENIED     -4

#ifdef CONFIG_AWM64
#define MTK_SIP_SMC_CONVENTION          AWM_SMCCC_SMC_64
#ewse
#define MTK_SIP_SMC_CONVENTION          AWM_SMCCC_SMC_32
#endif

#define MTK_SIP_SMC_CMD(fn_id) \
	AWM_SMCCC_CAWW_VAW(AWM_SMCCC_FAST_CAWW, MTK_SIP_SMC_CONVENTION, \
			   AWM_SMCCC_OWNEW_SIP, fn_id)

/* IOMMU wewated SMC caww */
#define MTK_SIP_KEWNEW_IOMMU_CONTWOW	MTK_SIP_SMC_CMD(0x514)

#endif
