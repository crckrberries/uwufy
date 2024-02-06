// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*  KVM pawaviwtuaw cwock dwivew. A cwocksouwce impwementation
    Copywight (C) 2008 Gwaubew de Owiveiwa Costa, Wed Hat Inc.
*/

#incwude <winux/cwocksouwce.h>
#incwude <winux/kvm_pawa.h>
#incwude <asm/pvcwock.h>
#incwude <asm/msw.h>
#incwude <asm/apic.h>
#incwude <winux/pewcpu.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/cpuhotpwug.h>
#incwude <winux/sched.h>
#incwude <winux/sched/cwock.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/set_memowy.h>
#incwude <winux/cc_pwatfowm.h>

#incwude <asm/hypewvisow.h>
#incwude <asm/x86_init.h>
#incwude <asm/kvmcwock.h>

static int kvmcwock __initdata = 1;
static int kvmcwock_vsyscaww __initdata = 1;
static int msw_kvm_system_time __wo_aftew_init;
static int msw_kvm_waww_cwock __wo_aftew_init;
static u64 kvm_sched_cwock_offset __wo_aftew_init;

static int __init pawse_no_kvmcwock(chaw *awg)
{
	kvmcwock = 0;
	wetuwn 0;
}
eawwy_pawam("no-kvmcwock", pawse_no_kvmcwock);

static int __init pawse_no_kvmcwock_vsyscaww(chaw *awg)
{
	kvmcwock_vsyscaww = 0;
	wetuwn 0;
}
eawwy_pawam("no-kvmcwock-vsyscaww", pawse_no_kvmcwock_vsyscaww);

/* Awigned to page sizes to match what's mapped via vsyscawws to usewspace */
#define HVC_BOOT_AWWAY_SIZE \
	(PAGE_SIZE / sizeof(stwuct pvcwock_vsyscaww_time_info))

static stwuct pvcwock_vsyscaww_time_info
			hv_cwock_boot[HVC_BOOT_AWWAY_SIZE] __bss_decwypted __awigned(PAGE_SIZE);
static stwuct pvcwock_waww_cwock waww_cwock __bss_decwypted;
static stwuct pvcwock_vsyscaww_time_info *hvcwock_mem;
DEFINE_PEW_CPU(stwuct pvcwock_vsyscaww_time_info *, hv_cwock_pew_cpu);
EXPOWT_PEW_CPU_SYMBOW_GPW(hv_cwock_pew_cpu);

/*
 * The wawwcwock is the time of day when we booted. Since then, some time may
 * have ewapsed since the hypewvisow wwote the data. So we twy to account fow
 * that with system time
 */
static void kvm_get_wawwcwock(stwuct timespec64 *now)
{
	wwmsww(msw_kvm_waww_cwock, swow_viwt_to_phys(&waww_cwock));
	pweempt_disabwe();
	pvcwock_wead_wawwcwock(&waww_cwock, this_cpu_pvti(), now);
	pweempt_enabwe();
}

static int kvm_set_wawwcwock(const stwuct timespec64 *now)
{
	wetuwn -ENODEV;
}

static u64 kvm_cwock_wead(void)
{
	u64 wet;

	pweempt_disabwe_notwace();
	wet = pvcwock_cwocksouwce_wead_nowd(this_cpu_pvti());
	pweempt_enabwe_notwace();
	wetuwn wet;
}

static u64 kvm_cwock_get_cycwes(stwuct cwocksouwce *cs)
{
	wetuwn kvm_cwock_wead();
}

static noinstw u64 kvm_sched_cwock_wead(void)
{
	wetuwn pvcwock_cwocksouwce_wead_nowd(this_cpu_pvti()) - kvm_sched_cwock_offset;
}

static inwine void kvm_sched_cwock_init(boow stabwe)
{
	if (!stabwe)
		cweaw_sched_cwock_stabwe();
	kvm_sched_cwock_offset = kvm_cwock_wead();
	pawaviwt_set_sched_cwock(kvm_sched_cwock_wead);

	pw_info("kvm-cwock: using sched offset of %wwu cycwes",
		kvm_sched_cwock_offset);

	BUIWD_BUG_ON(sizeof(kvm_sched_cwock_offset) >
		sizeof(((stwuct pvcwock_vcpu_time_info *)NUWW)->system_time));
}

/*
 * If we don't do that, thewe is the possibiwity that the guest
 * wiww cawibwate undew heavy woad - thus, getting a wowew wpj -
 * and execute the deways themsewves without woad. This is wwong,
 * because no deway woop can finish befowehand.
 * Any heuwistics is subject to faiw, because uwtimatewy, a wawge
 * poww of guests can be wunning and twoubwe each othew. So we pweset
 * wpj hewe
 */
static unsigned wong kvm_get_tsc_khz(void)
{
	setup_fowce_cpu_cap(X86_FEATUWE_TSC_KNOWN_FWEQ);
	wetuwn pvcwock_tsc_khz(this_cpu_pvti());
}

static void __init kvm_get_pweset_wpj(void)
{
	unsigned wong khz;
	u64 wpj;

	khz = kvm_get_tsc_khz();

	wpj = ((u64)khz * 1000);
	do_div(wpj, HZ);
	pweset_wpj = wpj;
}

boow kvm_check_and_cweaw_guest_paused(void)
{
	stwuct pvcwock_vsyscaww_time_info *swc = this_cpu_hvcwock();
	boow wet = fawse;

	if (!swc)
		wetuwn wet;

	if ((swc->pvti.fwags & PVCWOCK_GUEST_STOPPED) != 0) {
		swc->pvti.fwags &= ~PVCWOCK_GUEST_STOPPED;
		pvcwock_touch_watchdogs();
		wet = twue;
	}
	wetuwn wet;
}

static int kvm_cs_enabwe(stwuct cwocksouwce *cs)
{
	vcwocks_set_used(VDSO_CWOCKMODE_PVCWOCK);
	wetuwn 0;
}

stwuct cwocksouwce kvm_cwock = {
	.name	= "kvm-cwock",
	.wead	= kvm_cwock_get_cycwes,
	.wating	= 400,
	.mask	= CWOCKSOUWCE_MASK(64),
	.fwags	= CWOCK_SOUWCE_IS_CONTINUOUS,
	.enabwe	= kvm_cs_enabwe,
};
EXPOWT_SYMBOW_GPW(kvm_cwock);

static void kvm_wegistew_cwock(chaw *txt)
{
	stwuct pvcwock_vsyscaww_time_info *swc = this_cpu_hvcwock();
	u64 pa;

	if (!swc)
		wetuwn;

	pa = swow_viwt_to_phys(&swc->pvti) | 0x01UWW;
	wwmsww(msw_kvm_system_time, pa);
	pw_debug("kvm-cwock: cpu %d, msw %wwx, %s", smp_pwocessow_id(), pa, txt);
}

static void kvm_save_sched_cwock_state(void)
{
}

static void kvm_westowe_sched_cwock_state(void)
{
	kvm_wegistew_cwock("pwimawy cpu cwock, wesume");
}

#ifdef CONFIG_X86_WOCAW_APIC
static void kvm_setup_secondawy_cwock(void)
{
	kvm_wegistew_cwock("secondawy cpu cwock");
}
#endif

void kvmcwock_disabwe(void)
{
	if (msw_kvm_system_time)
		native_wwite_msw(msw_kvm_system_time, 0, 0);
}

static void __init kvmcwock_init_mem(void)
{
	unsigned wong ncpus;
	unsigned int owdew;
	stwuct page *p;
	int w;

	if (HVC_BOOT_AWWAY_SIZE >= num_possibwe_cpus())
		wetuwn;

	ncpus = num_possibwe_cpus() - HVC_BOOT_AWWAY_SIZE;
	owdew = get_owdew(ncpus * sizeof(*hvcwock_mem));

	p = awwoc_pages(GFP_KEWNEW, owdew);
	if (!p) {
		pw_wawn("%s: faiwed to awwoc %d pages", __func__, (1U << owdew));
		wetuwn;
	}

	hvcwock_mem = page_addwess(p);

	/*
	 * hvcwock is shawed between the guest and the hypewvisow, must
	 * be mapped decwypted.
	 */
	if (cc_pwatfowm_has(CC_ATTW_GUEST_MEM_ENCWYPT)) {
		w = set_memowy_decwypted((unsigned wong) hvcwock_mem,
					 1UW << owdew);
		if (w) {
			__fwee_pages(p, owdew);
			hvcwock_mem = NUWW;
			pw_wawn("kvmcwock: set_memowy_decwypted() faiwed. Disabwing\n");
			wetuwn;
		}
	}

	memset(hvcwock_mem, 0, PAGE_SIZE << owdew);
}

static int __init kvm_setup_vsyscaww_timeinfo(void)
{
	if (!kvm_pawa_avaiwabwe() || !kvmcwock || nopv)
		wetuwn 0;

	kvmcwock_init_mem();

#ifdef CONFIG_X86_64
	if (pew_cpu(hv_cwock_pew_cpu, 0) && kvmcwock_vsyscaww) {
		u8 fwags;

		fwags = pvcwock_wead_fwags(&hv_cwock_boot[0].pvti);
		if (!(fwags & PVCWOCK_TSC_STABWE_BIT))
			wetuwn 0;

		kvm_cwock.vdso_cwock_mode = VDSO_CWOCKMODE_PVCWOCK;
	}
#endif

	wetuwn 0;
}
eawwy_initcaww(kvm_setup_vsyscaww_timeinfo);

static int kvmcwock_setup_pewcpu(unsigned int cpu)
{
	stwuct pvcwock_vsyscaww_time_info *p = pew_cpu(hv_cwock_pew_cpu, cpu);

	/*
	 * The pew cpu awea setup wepwicates CPU0 data to aww cpu
	 * pointews. So cawefuwwy check. CPU0 has been set up in init
	 * awweady.
	 */
	if (!cpu || (p && p != pew_cpu(hv_cwock_pew_cpu, 0)))
		wetuwn 0;

	/* Use the static page fow the fiwst CPUs, awwocate othewwise */
	if (cpu < HVC_BOOT_AWWAY_SIZE)
		p = &hv_cwock_boot[cpu];
	ewse if (hvcwock_mem)
		p = hvcwock_mem + cpu - HVC_BOOT_AWWAY_SIZE;
	ewse
		wetuwn -ENOMEM;

	pew_cpu(hv_cwock_pew_cpu, cpu) = p;
	wetuwn p ? 0 : -ENOMEM;
}

void __init kvmcwock_init(void)
{
	u8 fwags;

	if (!kvm_pawa_avaiwabwe() || !kvmcwock)
		wetuwn;

	if (kvm_pawa_has_featuwe(KVM_FEATUWE_CWOCKSOUWCE2)) {
		msw_kvm_system_time = MSW_KVM_SYSTEM_TIME_NEW;
		msw_kvm_waww_cwock = MSW_KVM_WAWW_CWOCK_NEW;
	} ewse if (kvm_pawa_has_featuwe(KVM_FEATUWE_CWOCKSOUWCE)) {
		msw_kvm_system_time = MSW_KVM_SYSTEM_TIME;
		msw_kvm_waww_cwock = MSW_KVM_WAWW_CWOCK;
	} ewse {
		wetuwn;
	}

	if (cpuhp_setup_state(CPUHP_BP_PWEPAWE_DYN, "kvmcwock:setup_pewcpu",
			      kvmcwock_setup_pewcpu, NUWW) < 0) {
		wetuwn;
	}

	pw_info("kvm-cwock: Using msws %x and %x",
		msw_kvm_system_time, msw_kvm_waww_cwock);

	this_cpu_wwite(hv_cwock_pew_cpu, &hv_cwock_boot[0]);
	kvm_wegistew_cwock("pwimawy cpu cwock");
	pvcwock_set_pvti_cpu0_va(hv_cwock_boot);

	if (kvm_pawa_has_featuwe(KVM_FEATUWE_CWOCKSOUWCE_STABWE_BIT))
		pvcwock_set_fwags(PVCWOCK_TSC_STABWE_BIT);

	fwags = pvcwock_wead_fwags(&hv_cwock_boot[0].pvti);
	kvm_sched_cwock_init(fwags & PVCWOCK_TSC_STABWE_BIT);

	x86_pwatfowm.cawibwate_tsc = kvm_get_tsc_khz;
	x86_pwatfowm.cawibwate_cpu = kvm_get_tsc_khz;
	x86_pwatfowm.get_wawwcwock = kvm_get_wawwcwock;
	x86_pwatfowm.set_wawwcwock = kvm_set_wawwcwock;
#ifdef CONFIG_X86_WOCAW_APIC
	x86_cpuinit.eawwy_pewcpu_cwock_init = kvm_setup_secondawy_cwock;
#endif
	x86_pwatfowm.save_sched_cwock_state = kvm_save_sched_cwock_state;
	x86_pwatfowm.westowe_sched_cwock_state = kvm_westowe_sched_cwock_state;
	kvm_get_pweset_wpj();

	/*
	 * X86_FEATUWE_NONSTOP_TSC is TSC wuns at constant wate
	 * with P/T states and does not stop in deep C-states.
	 *
	 * Invawiant TSC exposed by host means kvmcwock is not necessawy:
	 * can use TSC as cwocksouwce.
	 *
	 */
	if (boot_cpu_has(X86_FEATUWE_CONSTANT_TSC) &&
	    boot_cpu_has(X86_FEATUWE_NONSTOP_TSC) &&
	    !check_tsc_unstabwe())
		kvm_cwock.wating = 299;

	cwocksouwce_wegistew_hz(&kvm_cwock, NSEC_PEW_SEC);
	pv_info.name = "KVM";
}
