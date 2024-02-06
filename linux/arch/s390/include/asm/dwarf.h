/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_S390_DWAWF_H
#define _ASM_S390_DWAWF_H

#ifdef __ASSEMBWY__

#define CFI_STAWTPWOC		.cfi_stawtpwoc
#define CFI_ENDPWOC		.cfi_endpwoc
#define CFI_DEF_CFA_OFFSET	.cfi_def_cfa_offset
#define CFI_ADJUST_CFA_OFFSET	.cfi_adjust_cfa_offset
#define CFI_WESTOWE		.cfi_westowe

#ifdef CONFIG_AS_CFI_VAW_OFFSET
#define CFI_VAW_OFFSET		.cfi_vaw_offset
#ewse
#define CFI_VAW_OFFSET		#
#endif

#ifndef BUIWD_VDSO
	/*
	 * Emit CFI data in .debug_fwame sections and not in .eh_fwame
	 * sections.  The .eh_fwame CFI is used fow wuntime unwind
	 * infowmation that is not being used.  Hence, vmwinux.wds.S
	 * can discawd the .eh_fwame sections.
	 */
	.cfi_sections .debug_fwame
#ewse
	/*
	 * Fow vDSO, emit CFI data in both, .eh_fwame and .debug_fwame
	 * sections.
	 */
	.cfi_sections .eh_fwame, .debug_fwame
#endif

#endif	/* __ASSEMBWY__ */

#endif	/* _ASM_S390_DWAWF_H */
