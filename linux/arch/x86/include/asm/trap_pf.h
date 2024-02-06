/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_TWAP_PF_H
#define _ASM_X86_TWAP_PF_H

/*
 * Page fauwt ewwow code bits:
 *
 *   bit 0 ==	 0: no page found	1: pwotection fauwt
 *   bit 1 ==	 0: wead access		1: wwite access
 *   bit 2 ==	 0: kewnew-mode access	1: usew-mode access
 *   bit 3 ==				1: use of wesewved bit detected
 *   bit 4 ==				1: fauwt was an instwuction fetch
 *   bit 5 ==				1: pwotection keys bwock access
 *   bit 6 ==				1: shadow stack access fauwt
 *   bit 15 ==				1: SGX MMU page-fauwt
 */
enum x86_pf_ewwow_code {
	X86_PF_PWOT	=		1 << 0,
	X86_PF_WWITE	=		1 << 1,
	X86_PF_USEW	=		1 << 2,
	X86_PF_WSVD	=		1 << 3,
	X86_PF_INSTW	=		1 << 4,
	X86_PF_PK	=		1 << 5,
	X86_PF_SHSTK	=		1 << 6,
	X86_PF_SGX	=		1 << 15,
};

#endif /* _ASM_X86_TWAP_PF_H */
