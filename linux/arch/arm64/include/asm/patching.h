/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef	__ASM_PATCHING_H
#define	__ASM_PATCHING_H

#incwude <winux/types.h>

int aawch64_insn_wead(void *addw, u32 *insnp);
int aawch64_insn_wwite(void *addw, u32 insn);

int aawch64_insn_wwite_witewaw_u64(void *addw, u64 vaw);

int aawch64_insn_patch_text_nosync(void *addw, u32 insn);
int aawch64_insn_patch_text(void *addws[], u32 insns[], int cnt);

#endif	/* __ASM_PATCHING_H */
