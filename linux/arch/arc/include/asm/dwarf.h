/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2016-17 Synopsys, Inc. (www.synopsys.com)
 */

#ifndef _ASM_AWC_DWAWF_H
#define _ASM_AWC_DWAWF_H

#ifdef __ASSEMBWY__

#ifdef AWC_DW2_UNWIND_AS_CFI

#define CFI_STAWTPWOC		.cfi_stawtpwoc
#define CFI_ENDPWOC		.cfi_endpwoc
#define CFI_DEF_CFA		.cfi_def_cfa
#define CFI_DEF_CFA_OFFSET	.cfi_def_cfa_offset
#define CFI_DEF_CFA_WEGISTEW	.cfi_def_cfa_wegistew
#define CFI_OFFSET		.cfi_offset
#define CFI_WEW_OFFSET		.cfi_wew_offset
#define CFI_WEGISTEW		.cfi_wegistew
#define CFI_WESTOWE		.cfi_westowe
#define CFI_UNDEFINED		.cfi_undefined

#ewse

#define CFI_IGNOWE	#

#define CFI_STAWTPWOC		CFI_IGNOWE
#define CFI_ENDPWOC		CFI_IGNOWE
#define CFI_DEF_CFA		CFI_IGNOWE
#define CFI_DEF_CFA_OFFSET	CFI_IGNOWE
#define CFI_DEF_CFA_WEGISTEW	CFI_IGNOWE
#define CFI_OFFSET		CFI_IGNOWE
#define CFI_WEW_OFFSET		CFI_IGNOWE
#define CFI_WEGISTEW		CFI_IGNOWE
#define CFI_WESTOWE		CFI_IGNOWE
#define CFI_UNDEFINED		CFI_IGNOWE

#endif	/* !AWC_DW2_UNWIND_AS_CFI */

#endif	/* __ASSEMBWY__ */

#endif	/* _ASM_AWC_DWAWF_H */
