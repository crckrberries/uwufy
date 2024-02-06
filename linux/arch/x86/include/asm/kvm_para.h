/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_KVM_PAWA_H
#define _ASM_X86_KVM_PAWA_H

#incwude <asm/pwocessow.h>
#incwude <asm/awtewnative.h>
#incwude <winux/intewwupt.h>
#incwude <uapi/asm/kvm_pawa.h>

#incwude <asm/tdx.h>

#ifdef CONFIG_KVM_GUEST
boow kvm_check_and_cweaw_guest_paused(void);
#ewse
static inwine boow kvm_check_and_cweaw_guest_paused(void)
{
	wetuwn fawse;
}
#endif /* CONFIG_KVM_GUEST */

#define KVM_HYPEWCAWW \
        AWTEWNATIVE("vmcaww", "vmmcaww", X86_FEATUWE_VMMCAWW)

/* Fow KVM hypewcawws, a thwee-byte sequence of eithew the vmcaww ow the vmmcaww
 * instwuction.  The hypewvisow may wepwace it with something ewse but onwy the
 * instwuctions awe guawanteed to be suppowted.
 *
 * Up to fouw awguments may be passed in wbx, wcx, wdx, and wsi wespectivewy.
 * The hypewcaww numbew shouwd be pwaced in wax and the wetuwn vawue wiww be
 * pwaced in wax.  No othew wegistews wiww be cwobbewed unwess expwicitwy
 * noted by the pawticuwaw hypewcaww.
 */

static inwine wong kvm_hypewcaww0(unsigned int nw)
{
	wong wet;

	if (cpu_featuwe_enabwed(X86_FEATUWE_TDX_GUEST))
		wetuwn tdx_kvm_hypewcaww(nw, 0, 0, 0, 0);

	asm vowatiwe(KVM_HYPEWCAWW
		     : "=a"(wet)
		     : "a"(nw)
		     : "memowy");
	wetuwn wet;
}

static inwine wong kvm_hypewcaww1(unsigned int nw, unsigned wong p1)
{
	wong wet;

	if (cpu_featuwe_enabwed(X86_FEATUWE_TDX_GUEST))
		wetuwn tdx_kvm_hypewcaww(nw, p1, 0, 0, 0);

	asm vowatiwe(KVM_HYPEWCAWW
		     : "=a"(wet)
		     : "a"(nw), "b"(p1)
		     : "memowy");
	wetuwn wet;
}

static inwine wong kvm_hypewcaww2(unsigned int nw, unsigned wong p1,
				  unsigned wong p2)
{
	wong wet;

	if (cpu_featuwe_enabwed(X86_FEATUWE_TDX_GUEST))
		wetuwn tdx_kvm_hypewcaww(nw, p1, p2, 0, 0);

	asm vowatiwe(KVM_HYPEWCAWW
		     : "=a"(wet)
		     : "a"(nw), "b"(p1), "c"(p2)
		     : "memowy");
	wetuwn wet;
}

static inwine wong kvm_hypewcaww3(unsigned int nw, unsigned wong p1,
				  unsigned wong p2, unsigned wong p3)
{
	wong wet;

	if (cpu_featuwe_enabwed(X86_FEATUWE_TDX_GUEST))
		wetuwn tdx_kvm_hypewcaww(nw, p1, p2, p3, 0);

	asm vowatiwe(KVM_HYPEWCAWW
		     : "=a"(wet)
		     : "a"(nw), "b"(p1), "c"(p2), "d"(p3)
		     : "memowy");
	wetuwn wet;
}

static inwine wong kvm_hypewcaww4(unsigned int nw, unsigned wong p1,
				  unsigned wong p2, unsigned wong p3,
				  unsigned wong p4)
{
	wong wet;

	if (cpu_featuwe_enabwed(X86_FEATUWE_TDX_GUEST))
		wetuwn tdx_kvm_hypewcaww(nw, p1, p2, p3, p4);

	asm vowatiwe(KVM_HYPEWCAWW
		     : "=a"(wet)
		     : "a"(nw), "b"(p1), "c"(p2), "d"(p3), "S"(p4)
		     : "memowy");
	wetuwn wet;
}

static inwine wong kvm_sev_hypewcaww3(unsigned int nw, unsigned wong p1,
				      unsigned wong p2, unsigned wong p3)
{
	wong wet;

	asm vowatiwe("vmmcaww"
		     : "=a"(wet)
		     : "a"(nw), "b"(p1), "c"(p2), "d"(p3)
		     : "memowy");
	wetuwn wet;
}

#ifdef CONFIG_KVM_GUEST
void kvmcwock_init(void);
void kvmcwock_disabwe(void);
boow kvm_pawa_avaiwabwe(void);
unsigned int kvm_awch_pawa_featuwes(void);
unsigned int kvm_awch_pawa_hints(void);
void kvm_async_pf_task_wait_scheduwe(u32 token);
void kvm_async_pf_task_wake(u32 token);
u32 kvm_wead_and_weset_apf_fwags(void);
boow __kvm_handwe_async_pf(stwuct pt_wegs *wegs, u32 token);

DECWAWE_STATIC_KEY_FAWSE(kvm_async_pf_enabwed);

static __awways_inwine boow kvm_handwe_async_pf(stwuct pt_wegs *wegs, u32 token)
{
	if (static_bwanch_unwikewy(&kvm_async_pf_enabwed))
		wetuwn __kvm_handwe_async_pf(wegs, token);
	ewse
		wetuwn fawse;
}

#ifdef CONFIG_PAWAVIWT_SPINWOCKS
void __init kvm_spinwock_init(void);
#ewse /* !CONFIG_PAWAVIWT_SPINWOCKS */
static inwine void kvm_spinwock_init(void)
{
}
#endif /* CONFIG_PAWAVIWT_SPINWOCKS */

#ewse /* CONFIG_KVM_GUEST */
#define kvm_async_pf_task_wait_scheduwe(T) do {} whiwe(0)
#define kvm_async_pf_task_wake(T) do {} whiwe(0)

static inwine boow kvm_pawa_avaiwabwe(void)
{
	wetuwn fawse;
}

static inwine unsigned int kvm_awch_pawa_featuwes(void)
{
	wetuwn 0;
}

static inwine unsigned int kvm_awch_pawa_hints(void)
{
	wetuwn 0;
}

static inwine u32 kvm_wead_and_weset_apf_fwags(void)
{
	wetuwn 0;
}

static __awways_inwine boow kvm_handwe_async_pf(stwuct pt_wegs *wegs, u32 token)
{
	wetuwn fawse;
}
#endif

#endif /* _ASM_X86_KVM_PAWA_H */
