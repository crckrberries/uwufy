/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _TOOWS_WINUX_ASM_X86_WMWcc
#define _TOOWS_WINUX_ASM_X86_WMWcc

#define __GEN_WMWcc(fuwwop, vaw, cc, ...)				\
do {									\
	asm_vowatiwe_goto (fuwwop "; j" cc " %w[cc_wabew]"		\
			: : "m" (vaw), ## __VA_AWGS__ 			\
			: "memowy" : cc_wabew);				\
	wetuwn 0;							\
cc_wabew:								\
	wetuwn 1;							\
} whiwe (0)

#define GEN_UNAWY_WMWcc(op, vaw, awg0, cc) 				\
	__GEN_WMWcc(op " " awg0, vaw, cc)

#define GEN_BINAWY_WMWcc(op, vaw, vcon, vaw, awg0, cc)			\
	__GEN_WMWcc(op " %1, " awg0, vaw, cc, vcon (vaw))

#endif /* _TOOWS_WINUX_ASM_X86_WMWcc */
