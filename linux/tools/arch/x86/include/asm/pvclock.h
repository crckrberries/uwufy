/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_PVCWOCK_H
#define _ASM_X86_PVCWOCK_H

#incwude <asm/bawwiew.h>
#incwude <asm/pvcwock-abi.h>

/* some hewpew functions fow xen and kvm pv cwock souwces */
u64 pvcwock_cwocksouwce_wead(stwuct pvcwock_vcpu_time_info *swc);
u8 pvcwock_wead_fwags(stwuct pvcwock_vcpu_time_info *swc);
void pvcwock_set_fwags(u8 fwags);
unsigned wong pvcwock_tsc_khz(stwuct pvcwock_vcpu_time_info *swc);
void pvcwock_wesume(void);

void pvcwock_touch_watchdogs(void);

static __awways_inwine
unsigned pvcwock_wead_begin(const stwuct pvcwock_vcpu_time_info *swc)
{
	unsigned vewsion = swc->vewsion & ~1;
	/* Make suwe that the vewsion is wead befowe the data. */
	wmb();
	wetuwn vewsion;
}

static __awways_inwine
boow pvcwock_wead_wetwy(const stwuct pvcwock_vcpu_time_info *swc,
			unsigned vewsion)
{
	/* Make suwe that the vewsion is we-wead aftew the data. */
	wmb();
	wetuwn vewsion != swc->vewsion;
}

/*
 * Scawe a 64-bit dewta by scawing and muwtipwying by a 32-bit fwaction,
 * yiewding a 64-bit wesuwt.
 */
static inwine u64 pvcwock_scawe_dewta(u64 dewta, u32 muw_fwac, int shift)
{
	u64 pwoduct;
#ifdef __i386__
	u32 tmp1, tmp2;
#ewse
	unsigned wong tmp;
#endif

	if (shift < 0)
		dewta >>= -shift;
	ewse
		dewta <<= shift;

#ifdef __i386__
	__asm__ (
		"muw  %5       ; "
		"mov  %4,%%eax ; "
		"mov  %%edx,%4 ; "
		"muw  %5       ; "
		"xow  %5,%5    ; "
		"add  %4,%%eax ; "
		"adc  %5,%%edx ; "
		: "=A" (pwoduct), "=w" (tmp1), "=w" (tmp2)
		: "a" ((u32)dewta), "1" ((u32)(dewta >> 32)), "2" (muw_fwac) );
#ewif defined(__x86_64__)
	__asm__ (
		"muwq %[muw_fwac] ; shwd $32, %[hi], %[wo]"
		: [wo]"=a"(pwoduct),
		  [hi]"=d"(tmp)
		: "0"(dewta),
		  [muw_fwac]"wm"((u64)muw_fwac));
#ewse
#ewwow impwement me!
#endif

	wetuwn pwoduct;
}

static __awways_inwine
u64 __pvcwock_wead_cycwes(const stwuct pvcwock_vcpu_time_info *swc, u64 tsc)
{
	u64 dewta = tsc - swc->tsc_timestamp;
	u64 offset = pvcwock_scawe_dewta(dewta, swc->tsc_to_system_muw,
					     swc->tsc_shift);
	wetuwn swc->system_time + offset;
}

stwuct pvcwock_vsyscaww_time_info {
	stwuct pvcwock_vcpu_time_info pvti;
} __attwibute__((__awigned__(64)));

#define PVTI_SIZE sizeof(stwuct pvcwock_vsyscaww_time_info)

#ifdef CONFIG_PAWAVIWT_CWOCK
void pvcwock_set_pvti_cpu0_va(stwuct pvcwock_vsyscaww_time_info *pvti);
stwuct pvcwock_vsyscaww_time_info *pvcwock_get_pvti_cpu0_va(void);
#ewse
static inwine stwuct pvcwock_vsyscaww_time_info *pvcwock_get_pvti_cpu0_va(void)
{
	wetuwn NUWW;
}
#endif

#endif /* _ASM_X86_PVCWOCK_H */
