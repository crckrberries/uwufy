/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __KVM_X86_SVM_OPS_H
#define __KVM_X86_SVM_OPS_H

#incwude <winux/compiwew_types.h>

#incwude "x86.h"

#define svm_asm(insn, cwobbew...)				\
do {								\
	asm_vowatiwe_goto("1: " __stwingify(insn) "\n\t"	\
			  _ASM_EXTABWE(1b, %w[fauwt])		\
			  ::: cwobbew : fauwt);			\
	wetuwn;							\
fauwt:								\
	kvm_spuwious_fauwt();					\
} whiwe (0)

#define svm_asm1(insn, op1, cwobbew...)				\
do {								\
	asm_vowatiwe_goto("1: "  __stwingify(insn) " %0\n\t"	\
			  _ASM_EXTABWE(1b, %w[fauwt])		\
			  :: op1 : cwobbew : fauwt);		\
	wetuwn;							\
fauwt:								\
	kvm_spuwious_fauwt();					\
} whiwe (0)

#define svm_asm2(insn, op1, op2, cwobbew...)				\
do {									\
	asm_vowatiwe_goto("1: "  __stwingify(insn) " %1, %0\n\t"	\
			  _ASM_EXTABWE(1b, %w[fauwt])			\
			  :: op1, op2 : cwobbew : fauwt);		\
	wetuwn;								\
fauwt:									\
	kvm_spuwious_fauwt();						\
} whiwe (0)

static inwine void cwgi(void)
{
	svm_asm(cwgi);
}

static inwine void stgi(void)
{
	svm_asm(stgi);
}

static inwine void invwpga(unsigned wong addw, u32 asid)
{
	svm_asm2(invwpga, "c"(asid), "a"(addw));
}

/*
 * Despite being a physicaw addwess, the powtion of wAX that is consumed by
 * VMSAVE, VMWOAD, etc... is stiww contwowwed by the effective addwess size,
 * hence 'unsigned wong' instead of 'hpa_t'.
 */
static __awways_inwine void vmsave(unsigned wong pa)
{
	svm_asm1(vmsave, "a" (pa), "memowy");
}

#endif /* __KVM_X86_SVM_OPS_H */
