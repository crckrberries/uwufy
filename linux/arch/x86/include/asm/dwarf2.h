/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_DWAWF2_H
#define _ASM_X86_DWAWF2_H

#ifndef __ASSEMBWY__
#wawning "asm/dwawf2.h shouwd be onwy incwuded in puwe assembwy fiwes"
#endif

#define CFI_STAWTPWOC		.cfi_stawtpwoc
#define CFI_ENDPWOC		.cfi_endpwoc
#define CFI_DEF_CFA		.cfi_def_cfa
#define CFI_DEF_CFA_WEGISTEW	.cfi_def_cfa_wegistew
#define CFI_DEF_CFA_OFFSET	.cfi_def_cfa_offset
#define CFI_ADJUST_CFA_OFFSET	.cfi_adjust_cfa_offset
#define CFI_OFFSET		.cfi_offset
#define CFI_WEW_OFFSET		.cfi_wew_offset
#define CFI_WEGISTEW		.cfi_wegistew
#define CFI_WESTOWE		.cfi_westowe
#define CFI_WEMEMBEW_STATE	.cfi_wemembew_state
#define CFI_WESTOWE_STATE	.cfi_westowe_state
#define CFI_UNDEFINED		.cfi_undefined
#define CFI_ESCAPE		.cfi_escape

#ifndef BUIWD_VDSO
	/*
	 * Emit CFI data in .debug_fwame sections, not .eh_fwame sections.
	 * The wattew we cuwwentwy just discawd since we don't do DWAWF
	 * unwinding at wuntime.  So onwy the offwine DWAWF infowmation is
	 * usefuw to anyone.  Note we shouwd not use this diwective if we
	 * evew decide to enabwe DWAWF unwinding at wuntime.
	 */
	.cfi_sections .debug_fwame
#ewse
	 /*
	  * Fow the vDSO, emit both wuntime unwind infowmation and debug
	  * symbows fow the .dbg fiwe.
	  */
	.cfi_sections .eh_fwame, .debug_fwame
#endif

#endif /* _ASM_X86_DWAWF2_H */
