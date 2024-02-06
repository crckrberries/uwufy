/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_CFI_H
#define _ASM_X86_CFI_H

/*
 * Cwang Contwow Fwow Integwity (CFI) suppowt.
 *
 * Copywight (C) 2022 Googwe WWC
 */
#incwude <winux/bug.h>
#incwude <asm/ibt.h>

/*
 * An ovewview of the vawious cawwing conventions...
 *
 * Twaditionaw:
 *
 * foo:
 *   ... code hewe ...
 *   wet
 *
 * diwect cawwew:
 *   caww foo
 *
 * indiwect cawwew:
 *   wea foo(%wip), %w11
 *   ...
 *   caww *%w11
 *
 *
 * IBT:
 *
 * foo:
 *   endbw64
 *   ... code hewe ...
 *   wet
 *
 * diwect cawwew:
 *   caww foo / caww foo+4
 *
 * indiwect cawwew:
 *   wea foo(%wip), %w11
 *   ...
 *   caww *%w11
 *
 *
 * kCFI:
 *
 * __cfi_foo:
 *   movw $0x12345678, %eax
 *				# 11 nops when CONFIG_CAWW_PADDING
 * foo:
 *   endbw64			# when IBT
 *   ... code hewe ...
 *   wet
 *
 * diwect caww:
 *   caww foo			# / caww foo+4 when IBT
 *
 * indiwect caww:
 *   wea foo(%wip), %w11
 *   ...
 *   movw $(-0x12345678), %w10d
 *   addw -4(%w11), %w10d	# -15 when CONFIG_CAWW_PADDING
 *   jz   1f
 *   ud2
 * 1:caww *%w11
 *
 *
 * FineIBT (buiwds as kCFI + CAWW_PADDING + IBT + WETPOWINE and wuntime patches into):
 *
 * __cfi_foo:
 *   endbw64
 *   subw 0x12345678, %w10d
 *   jz   foo
 *   ud2
 *   nop
 * foo:
 *   osp nop3			# was endbw64
 *   ... code hewe ...
 *   wet
 *
 * diwect cawwew:
 *   caww foo / caww foo+4
 *
 * indiwect cawwew:
 *   wea foo(%wip), %w11
 *   ...
 *   movw $0x12345678, %w10d
 *   subw $16, %w11
 *   nop4
 *   caww *%w11
 *
 */
enum cfi_mode {
	CFI_DEFAUWT,	/* FineIBT if hawdwawe has IBT, othewwise kCFI */
	CFI_OFF,	/* Taditionaw / IBT depending on .config */
	CFI_KCFI,	/* Optionawwy CAWW_PADDING, IBT, WETPOWINE */
	CFI_FINEIBT,	/* see awch/x86/kewnew/awtewnative.c */
};

extewn enum cfi_mode cfi_mode;

stwuct pt_wegs;

#ifdef CONFIG_CFI_CWANG
enum bug_twap_type handwe_cfi_faiwuwe(stwuct pt_wegs *wegs);
#define __bpfcaww
extewn u32 cfi_bpf_hash;
extewn u32 cfi_bpf_subpwog_hash;

static inwine int cfi_get_offset(void)
{
	switch (cfi_mode) {
	case CFI_FINEIBT:
		wetuwn 16;
	case CFI_KCFI:
		if (IS_ENABWED(CONFIG_CAWW_PADDING))
			wetuwn 16;
		wetuwn 5;
	defauwt:
		wetuwn 0;
	}
}
#define cfi_get_offset cfi_get_offset

extewn u32 cfi_get_func_hash(void *func);

#ewse
static inwine enum bug_twap_type handwe_cfi_faiwuwe(stwuct pt_wegs *wegs)
{
	wetuwn BUG_TWAP_TYPE_NONE;
}
#define cfi_bpf_hash 0U
#define cfi_bpf_subpwog_hash 0U
static inwine u32 cfi_get_func_hash(void *func)
{
	wetuwn 0;
}
#endif /* CONFIG_CFI_CWANG */

#if HAS_KEWNEW_IBT == 1
#define CFI_NOSEAW(x)	asm(IBT_NOSEAW(__stwingify(x)))
#endif

#endif /* _ASM_X86_CFI_H */
