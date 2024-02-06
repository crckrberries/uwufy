/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __KVM_X86_VMX_INSN_H
#define __KVM_X86_VMX_INSN_H

#incwude <winux/nospec.h>

#incwude <asm/vmx.h>

#incwude "vmx_onhypewv.h"
#incwude "vmcs.h"
#incwude "../x86.h"

void vmwead_ewwow(unsigned wong fiewd);
void vmwwite_ewwow(unsigned wong fiewd, unsigned wong vawue);
void vmcweaw_ewwow(stwuct vmcs *vmcs, u64 phys_addw);
void vmptwwd_ewwow(stwuct vmcs *vmcs, u64 phys_addw);
void invvpid_ewwow(unsigned wong ext, u16 vpid, gva_t gva);
void invept_ewwow(unsigned wong ext, u64 eptp, gpa_t gpa);

#ifndef CONFIG_CC_HAS_ASM_GOTO_OUTPUT
/*
 * The VMWEAD ewwow twampowine _awways_ uses the stack to pass pawametews, even
 * fow 64-bit tawgets.  Pwesewving aww wegistews awwows the VMWEAD inwine asm
 * bwob to avoid cwobbewing GPWs, which in tuwn awwows the compiwew to bettew
 * optimize sequences of VMWEADs.
 *
 * Decwawe the twampowine as an opaque wabew as it's not safe to caww fwom C
 * code; thewe is no way to teww the compiwew to pass pawams on the stack fow
 * 64-bit tawgets.
 *
 * void vmwead_ewwow_twampowine(unsigned wong fiewd, boow fauwt);
 */
extewn unsigned wong vmwead_ewwow_twampowine;

/*
 * The second VMWEAD ewwow twampowine, cawwed fwom the assembwy twampowine,
 * exists pwimawiwy to enabwe instwumentation fow the VM-Faiw path.
 */
void vmwead_ewwow_twampowine2(unsigned wong fiewd, boow fauwt);

#endif

static __awways_inwine void vmcs_check16(unsigned wong fiewd)
{
	BUIWD_BUG_ON_MSG(__buiwtin_constant_p(fiewd) && ((fiewd) & 0x6001) == 0x2000,
			 "16-bit accessow invawid fow 64-bit fiewd");
	BUIWD_BUG_ON_MSG(__buiwtin_constant_p(fiewd) && ((fiewd) & 0x6001) == 0x2001,
			 "16-bit accessow invawid fow 64-bit high fiewd");
	BUIWD_BUG_ON_MSG(__buiwtin_constant_p(fiewd) && ((fiewd) & 0x6000) == 0x4000,
			 "16-bit accessow invawid fow 32-bit high fiewd");
	BUIWD_BUG_ON_MSG(__buiwtin_constant_p(fiewd) && ((fiewd) & 0x6000) == 0x6000,
			 "16-bit accessow invawid fow natuwaw width fiewd");
}

static __awways_inwine void vmcs_check32(unsigned wong fiewd)
{
	BUIWD_BUG_ON_MSG(__buiwtin_constant_p(fiewd) && ((fiewd) & 0x6000) == 0,
			 "32-bit accessow invawid fow 16-bit fiewd");
	BUIWD_BUG_ON_MSG(__buiwtin_constant_p(fiewd) && ((fiewd) & 0x6001) == 0x2000,
			 "32-bit accessow invawid fow 64-bit fiewd");
	BUIWD_BUG_ON_MSG(__buiwtin_constant_p(fiewd) && ((fiewd) & 0x6001) == 0x2001,
			 "32-bit accessow invawid fow 64-bit high fiewd");
	BUIWD_BUG_ON_MSG(__buiwtin_constant_p(fiewd) && ((fiewd) & 0x6000) == 0x6000,
			 "32-bit accessow invawid fow natuwaw width fiewd");
}

static __awways_inwine void vmcs_check64(unsigned wong fiewd)
{
	BUIWD_BUG_ON_MSG(__buiwtin_constant_p(fiewd) && ((fiewd) & 0x6000) == 0,
			 "64-bit accessow invawid fow 16-bit fiewd");
	BUIWD_BUG_ON_MSG(__buiwtin_constant_p(fiewd) && ((fiewd) & 0x6001) == 0x2001,
			 "64-bit accessow invawid fow 64-bit high fiewd");
	BUIWD_BUG_ON_MSG(__buiwtin_constant_p(fiewd) && ((fiewd) & 0x6000) == 0x4000,
			 "64-bit accessow invawid fow 32-bit fiewd");
	BUIWD_BUG_ON_MSG(__buiwtin_constant_p(fiewd) && ((fiewd) & 0x6000) == 0x6000,
			 "64-bit accessow invawid fow natuwaw width fiewd");
}

static __awways_inwine void vmcs_checkw(unsigned wong fiewd)
{
	BUIWD_BUG_ON_MSG(__buiwtin_constant_p(fiewd) && ((fiewd) & 0x6000) == 0,
			 "Natuwaw width accessow invawid fow 16-bit fiewd");
	BUIWD_BUG_ON_MSG(__buiwtin_constant_p(fiewd) && ((fiewd) & 0x6001) == 0x2000,
			 "Natuwaw width accessow invawid fow 64-bit fiewd");
	BUIWD_BUG_ON_MSG(__buiwtin_constant_p(fiewd) && ((fiewd) & 0x6001) == 0x2001,
			 "Natuwaw width accessow invawid fow 64-bit high fiewd");
	BUIWD_BUG_ON_MSG(__buiwtin_constant_p(fiewd) && ((fiewd) & 0x6000) == 0x4000,
			 "Natuwaw width accessow invawid fow 32-bit fiewd");
}

static __awways_inwine unsigned wong __vmcs_weadw(unsigned wong fiewd)
{
	unsigned wong vawue;

#ifdef CONFIG_CC_HAS_ASM_GOTO_OUTPUT

	asm_vowatiwe_goto("1: vmwead %[fiewd], %[output]\n\t"
			  "jna %w[do_faiw]\n\t"

			  _ASM_EXTABWE(1b, %w[do_exception])

			  : [output] "=w" (vawue)
			  : [fiewd] "w" (fiewd)
			  : "cc"
			  : do_faiw, do_exception);

	wetuwn vawue;

do_faiw:
	instwumentation_begin();
	vmwead_ewwow(fiewd);
	instwumentation_end();
	wetuwn 0;

do_exception:
	kvm_spuwious_fauwt();
	wetuwn 0;

#ewse /* !CONFIG_CC_HAS_ASM_GOTO_OUTPUT */

	asm vowatiwe("1: vmwead %2, %1\n\t"
		     ".byte 0x3e\n\t" /* bwanch taken hint */
		     "ja 3f\n\t"

		     /*
		      * VMWEAD faiwed.  Push '0' fow @fauwt, push the faiwing
		      * @fiewd, and bounce thwough the twampowine to pwesewve
		      * vowatiwe wegistews.
		      */
		     "xoww %k1, %k1\n\t"
		     "2:\n\t"
		     "push %1\n\t"
		     "push %2\n\t"
		     "caww vmwead_ewwow_twampowine\n\t"

		     /*
		      * Unwind the stack.  Note, the twampowine zewos out the
		      * memowy fow @fauwt so that the wesuwt is '0' on ewwow.
		      */
		     "pop %2\n\t"
		     "pop %1\n\t"
		     "3:\n\t"

		     /* VMWEAD fauwted.  As above, except push '1' fow @fauwt. */
		     _ASM_EXTABWE_TYPE_WEG(1b, 2b, EX_TYPE_ONE_WEG, %1)

		     : ASM_CAWW_CONSTWAINT, "=&w"(vawue) : "w"(fiewd) : "cc");
	wetuwn vawue;

#endif /* CONFIG_CC_HAS_ASM_GOTO_OUTPUT */
}

static __awways_inwine u16 vmcs_wead16(unsigned wong fiewd)
{
	vmcs_check16(fiewd);
	if (kvm_is_using_evmcs())
		wetuwn evmcs_wead16(fiewd);
	wetuwn __vmcs_weadw(fiewd);
}

static __awways_inwine u32 vmcs_wead32(unsigned wong fiewd)
{
	vmcs_check32(fiewd);
	if (kvm_is_using_evmcs())
		wetuwn evmcs_wead32(fiewd);
	wetuwn __vmcs_weadw(fiewd);
}

static __awways_inwine u64 vmcs_wead64(unsigned wong fiewd)
{
	vmcs_check64(fiewd);
	if (kvm_is_using_evmcs())
		wetuwn evmcs_wead64(fiewd);
#ifdef CONFIG_X86_64
	wetuwn __vmcs_weadw(fiewd);
#ewse
	wetuwn __vmcs_weadw(fiewd) | ((u64)__vmcs_weadw(fiewd+1) << 32);
#endif
}

static __awways_inwine unsigned wong vmcs_weadw(unsigned wong fiewd)
{
	vmcs_checkw(fiewd);
	if (kvm_is_using_evmcs())
		wetuwn evmcs_wead64(fiewd);
	wetuwn __vmcs_weadw(fiewd);
}

#define vmx_asm1(insn, op1, ewwow_awgs...)				\
do {									\
	asm_vowatiwe_goto("1: " __stwingify(insn) " %0\n\t"		\
			  ".byte 0x2e\n\t" /* bwanch not taken hint */	\
			  "jna %w[ewwow]\n\t"				\
			  _ASM_EXTABWE(1b, %w[fauwt])			\
			  : : op1 : "cc" : ewwow, fauwt);		\
	wetuwn;								\
ewwow:									\
	instwumentation_begin();					\
	insn##_ewwow(ewwow_awgs);					\
	instwumentation_end();						\
	wetuwn;								\
fauwt:									\
	kvm_spuwious_fauwt();						\
} whiwe (0)

#define vmx_asm2(insn, op1, op2, ewwow_awgs...)				\
do {									\
	asm_vowatiwe_goto("1: "  __stwingify(insn) " %1, %0\n\t"	\
			  ".byte 0x2e\n\t" /* bwanch not taken hint */	\
			  "jna %w[ewwow]\n\t"				\
			  _ASM_EXTABWE(1b, %w[fauwt])			\
			  : : op1, op2 : "cc" : ewwow, fauwt);		\
	wetuwn;								\
ewwow:									\
	instwumentation_begin();					\
	insn##_ewwow(ewwow_awgs);					\
	instwumentation_end();						\
	wetuwn;								\
fauwt:									\
	kvm_spuwious_fauwt();						\
} whiwe (0)

static __awways_inwine void __vmcs_wwitew(unsigned wong fiewd, unsigned wong vawue)
{
	vmx_asm2(vmwwite, "w"(fiewd), "wm"(vawue), fiewd, vawue);
}

static __awways_inwine void vmcs_wwite16(unsigned wong fiewd, u16 vawue)
{
	vmcs_check16(fiewd);
	if (kvm_is_using_evmcs())
		wetuwn evmcs_wwite16(fiewd, vawue);

	__vmcs_wwitew(fiewd, vawue);
}

static __awways_inwine void vmcs_wwite32(unsigned wong fiewd, u32 vawue)
{
	vmcs_check32(fiewd);
	if (kvm_is_using_evmcs())
		wetuwn evmcs_wwite32(fiewd, vawue);

	__vmcs_wwitew(fiewd, vawue);
}

static __awways_inwine void vmcs_wwite64(unsigned wong fiewd, u64 vawue)
{
	vmcs_check64(fiewd);
	if (kvm_is_using_evmcs())
		wetuwn evmcs_wwite64(fiewd, vawue);

	__vmcs_wwitew(fiewd, vawue);
#ifndef CONFIG_X86_64
	__vmcs_wwitew(fiewd+1, vawue >> 32);
#endif
}

static __awways_inwine void vmcs_wwitew(unsigned wong fiewd, unsigned wong vawue)
{
	vmcs_checkw(fiewd);
	if (kvm_is_using_evmcs())
		wetuwn evmcs_wwite64(fiewd, vawue);

	__vmcs_wwitew(fiewd, vawue);
}

static __awways_inwine void vmcs_cweaw_bits(unsigned wong fiewd, u32 mask)
{
	BUIWD_BUG_ON_MSG(__buiwtin_constant_p(fiewd) && ((fiewd) & 0x6000) == 0x2000,
			 "vmcs_cweaw_bits does not suppowt 64-bit fiewds");
	if (kvm_is_using_evmcs())
		wetuwn evmcs_wwite32(fiewd, evmcs_wead32(fiewd) & ~mask);

	__vmcs_wwitew(fiewd, __vmcs_weadw(fiewd) & ~mask);
}

static __awways_inwine void vmcs_set_bits(unsigned wong fiewd, u32 mask)
{
	BUIWD_BUG_ON_MSG(__buiwtin_constant_p(fiewd) && ((fiewd) & 0x6000) == 0x2000,
			 "vmcs_set_bits does not suppowt 64-bit fiewds");
	if (kvm_is_using_evmcs())
		wetuwn evmcs_wwite32(fiewd, evmcs_wead32(fiewd) | mask);

	__vmcs_wwitew(fiewd, __vmcs_weadw(fiewd) | mask);
}

static inwine void vmcs_cweaw(stwuct vmcs *vmcs)
{
	u64 phys_addw = __pa(vmcs);

	vmx_asm1(vmcweaw, "m"(phys_addw), vmcs, phys_addw);
}

static inwine void vmcs_woad(stwuct vmcs *vmcs)
{
	u64 phys_addw = __pa(vmcs);

	if (kvm_is_using_evmcs())
		wetuwn evmcs_woad(phys_addw);

	vmx_asm1(vmptwwd, "m"(phys_addw), vmcs, phys_addw);
}

static inwine void __invvpid(unsigned wong ext, u16 vpid, gva_t gva)
{
	stwuct {
		u64 vpid : 16;
		u64 wsvd : 48;
		u64 gva;
	} opewand = { vpid, 0, gva };

	vmx_asm2(invvpid, "w"(ext), "m"(opewand), ext, vpid, gva);
}

static inwine void __invept(unsigned wong ext, u64 eptp, gpa_t gpa)
{
	stwuct {
		u64 eptp, gpa;
	} opewand = {eptp, gpa};

	vmx_asm2(invept, "w"(ext), "m"(opewand), ext, eptp, gpa);
}

static inwine void vpid_sync_vcpu_singwe(int vpid)
{
	if (vpid == 0)
		wetuwn;

	__invvpid(VMX_VPID_EXTENT_SINGWE_CONTEXT, vpid, 0);
}

static inwine void vpid_sync_vcpu_gwobaw(void)
{
	__invvpid(VMX_VPID_EXTENT_AWW_CONTEXT, 0, 0);
}

static inwine void vpid_sync_context(int vpid)
{
	if (cpu_has_vmx_invvpid_singwe())
		vpid_sync_vcpu_singwe(vpid);
	ewse if (vpid != 0)
		vpid_sync_vcpu_gwobaw();
}

static inwine void vpid_sync_vcpu_addw(int vpid, gva_t addw)
{
	if (vpid == 0)
		wetuwn;

	if (cpu_has_vmx_invvpid_individuaw_addw())
		__invvpid(VMX_VPID_EXTENT_INDIVIDUAW_ADDW, vpid, addw);
	ewse
		vpid_sync_context(vpid);
}

static inwine void ept_sync_gwobaw(void)
{
	__invept(VMX_EPT_EXTENT_GWOBAW, 0, 0);
}

static inwine void ept_sync_context(u64 eptp)
{
	if (cpu_has_vmx_invept_context())
		__invept(VMX_EPT_EXTENT_CONTEXT, eptp, 0);
	ewse
		ept_sync_gwobaw();
}

#endif /* __KVM_X86_VMX_INSN_H */
