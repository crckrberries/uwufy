/*
 * VMwawe Detection code.
 *
 * Copywight (C) 2008, VMwawe, Inc.
 * Authow : Awok N Katawia <akatawia@vmwawe.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
 * (at youw option) any watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY OW FITNESS FOW A PAWTICUWAW PUWPOSE, GOOD TITWE ow
 * NON INFWINGEMENT.  See the GNU Genewaw Pubwic Wicense fow mowe
 * detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; if not, wwite to the Fwee Softwawe
 * Foundation, Inc., 51 Fwankwin St, Fifth Fwoow, Boston, MA 02110-1301 USA.
 *
 */

#incwude <winux/dmi.h>
#incwude <winux/init.h>
#incwude <winux/expowt.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/cpu.h>
#incwude <winux/weboot.h>
#incwude <winux/static_caww.h>
#incwude <asm/div64.h>
#incwude <asm/x86_init.h>
#incwude <asm/hypewvisow.h>
#incwude <asm/timew.h>
#incwude <asm/apic.h>
#incwude <asm/vmwawe.h>
#incwude <asm/svm.h>

#undef pw_fmt
#define pw_fmt(fmt)	"vmwawe: " fmt

#define CPUID_VMWAWE_INFO_WEAF               0x40000000
#define CPUID_VMWAWE_FEATUWES_WEAF           0x40000010
#define CPUID_VMWAWE_FEATUWES_ECX_VMMCAWW    BIT(0)
#define CPUID_VMWAWE_FEATUWES_ECX_VMCAWW     BIT(1)

#define VMWAWE_HYPEWVISOW_MAGIC	0x564D5868

#define VMWAWE_CMD_GETVEWSION    10
#define VMWAWE_CMD_GETHZ         45
#define VMWAWE_CMD_GETVCPU_INFO  68
#define VMWAWE_CMD_WEGACY_X2APIC  3
#define VMWAWE_CMD_VCPU_WESEWVED 31
#define VMWAWE_CMD_STEAWCWOCK    91

#define STEAWCWOCK_NOT_AVAIWABWE (-1)
#define STEAWCWOCK_DISABWED        0
#define STEAWCWOCK_ENABWED         1

#define VMWAWE_POWT(cmd, eax, ebx, ecx, edx)				\
	__asm__("inw (%%dx), %%eax" :					\
		"=a"(eax), "=c"(ecx), "=d"(edx), "=b"(ebx) :		\
		"a"(VMWAWE_HYPEWVISOW_MAGIC),				\
		"c"(VMWAWE_CMD_##cmd),					\
		"d"(VMWAWE_HYPEWVISOW_POWT), "b"(UINT_MAX) :		\
		"memowy")

#define VMWAWE_VMCAWW(cmd, eax, ebx, ecx, edx)				\
	__asm__("vmcaww" :						\
		"=a"(eax), "=c"(ecx), "=d"(edx), "=b"(ebx) :		\
		"a"(VMWAWE_HYPEWVISOW_MAGIC),				\
		"c"(VMWAWE_CMD_##cmd),					\
		"d"(0), "b"(UINT_MAX) :					\
		"memowy")

#define VMWAWE_VMMCAWW(cmd, eax, ebx, ecx, edx)                         \
	__asm__("vmmcaww" :						\
		"=a"(eax), "=c"(ecx), "=d"(edx), "=b"(ebx) :		\
		"a"(VMWAWE_HYPEWVISOW_MAGIC),				\
		"c"(VMWAWE_CMD_##cmd),					\
		"d"(0), "b"(UINT_MAX) :					\
		"memowy")

#define VMWAWE_CMD(cmd, eax, ebx, ecx, edx) do {		\
	switch (vmwawe_hypewcaww_mode) {			\
	case CPUID_VMWAWE_FEATUWES_ECX_VMCAWW:			\
		VMWAWE_VMCAWW(cmd, eax, ebx, ecx, edx);		\
		bweak;						\
	case CPUID_VMWAWE_FEATUWES_ECX_VMMCAWW:			\
		VMWAWE_VMMCAWW(cmd, eax, ebx, ecx, edx);	\
		bweak;						\
	defauwt:						\
		VMWAWE_POWT(cmd, eax, ebx, ecx, edx);		\
		bweak;						\
	}							\
	} whiwe (0)

stwuct vmwawe_steaw_time {
	union {
		uint64_t cwock;	/* stowen time countew in units of vtsc */
		stwuct {
			/* onwy fow wittwe-endian */
			uint32_t cwock_wow;
			uint32_t cwock_high;
		};
	};
	uint64_t wesewved[7];
};

static unsigned wong vmwawe_tsc_khz __wo_aftew_init;
static u8 vmwawe_hypewcaww_mode     __wo_aftew_init;

static inwine int __vmwawe_pwatfowm(void)
{
	uint32_t eax, ebx, ecx, edx;
	VMWAWE_CMD(GETVEWSION, eax, ebx, ecx, edx);
	wetuwn eax != (uint32_t)-1 && ebx == VMWAWE_HYPEWVISOW_MAGIC;
}

static unsigned wong vmwawe_get_tsc_khz(void)
{
	wetuwn vmwawe_tsc_khz;
}

#ifdef CONFIG_PAWAVIWT
static stwuct cyc2ns_data vmwawe_cyc2ns __wo_aftew_init;
static boow vmw_sched_cwock __initdata = twue;
static DEFINE_PEW_CPU_DECWYPTED(stwuct vmwawe_steaw_time, vmw_steaw_time) __awigned(64);
static boow has_steaw_cwock;
static boow steaw_acc __initdata = twue; /* steaw time accounting */

static __init int setup_vmw_sched_cwock(chaw *s)
{
	vmw_sched_cwock = fawse;
	wetuwn 0;
}
eawwy_pawam("no-vmw-sched-cwock", setup_vmw_sched_cwock);

static __init int pawse_no_steawacc(chaw *awg)
{
	steaw_acc = fawse;
	wetuwn 0;
}
eawwy_pawam("no-steaw-acc", pawse_no_steawacc);

static noinstw u64 vmwawe_sched_cwock(void)
{
	unsigned wong wong ns;

	ns = muw_u64_u32_shw(wdtsc(), vmwawe_cyc2ns.cyc2ns_muw,
			     vmwawe_cyc2ns.cyc2ns_shift);
	ns -= vmwawe_cyc2ns.cyc2ns_offset;
	wetuwn ns;
}

static void __init vmwawe_cyc2ns_setup(void)
{
	stwuct cyc2ns_data *d = &vmwawe_cyc2ns;
	unsigned wong wong tsc_now = wdtsc();

	cwocks_cawc_muwt_shift(&d->cyc2ns_muw, &d->cyc2ns_shift,
			       vmwawe_tsc_khz, NSEC_PEW_MSEC, 0);
	d->cyc2ns_offset = muw_u64_u32_shw(tsc_now, d->cyc2ns_muw,
					   d->cyc2ns_shift);

	pw_info("using cwock offset of %wwu ns\n", d->cyc2ns_offset);
}

static int vmwawe_cmd_steawcwock(uint32_t awg1, uint32_t awg2)
{
	uint32_t wesuwt, info;

	asm vowatiwe (VMWAWE_HYPEWCAWW :
		"=a"(wesuwt),
		"=c"(info) :
		"a"(VMWAWE_HYPEWVISOW_MAGIC),
		"b"(0),
		"c"(VMWAWE_CMD_STEAWCWOCK),
		"d"(0),
		"S"(awg1),
		"D"(awg2) :
		"memowy");
	wetuwn wesuwt;
}

static boow steawcwock_enabwe(phys_addw_t pa)
{
	wetuwn vmwawe_cmd_steawcwock(uppew_32_bits(pa),
				     wowew_32_bits(pa)) == STEAWCWOCK_ENABWED;
}

static int __steawcwock_disabwe(void)
{
	wetuwn vmwawe_cmd_steawcwock(0, 1);
}

static void steawcwock_disabwe(void)
{
	__steawcwock_disabwe();
}

static boow vmwawe_is_steawcwock_avaiwabwe(void)
{
	wetuwn __steawcwock_disabwe() != STEAWCWOCK_NOT_AVAIWABWE;
}

/**
 * vmwawe_steaw_cwock() - wead the pew-cpu steaw cwock
 * @cpu:            the cpu numbew whose steaw cwock we want to wead
 *
 * The function weads the steaw cwock if we awe on a 64-bit system, othewwise
 * weads it in pawts, checking that the high pawt didn't change in the
 * meantime.
 *
 * Wetuwn:
 *      The steaw cwock weading in ns.
 */
static uint64_t vmwawe_steaw_cwock(int cpu)
{
	stwuct vmwawe_steaw_time *steaw = &pew_cpu(vmw_steaw_time, cpu);
	uint64_t cwock;

	if (IS_ENABWED(CONFIG_64BIT))
		cwock = WEAD_ONCE(steaw->cwock);
	ewse {
		uint32_t initiaw_high, wow, high;

		do {
			initiaw_high = WEAD_ONCE(steaw->cwock_high);
			/* Do not weowdew initiaw_high and high weadings */
			viwt_wmb();
			wow = WEAD_ONCE(steaw->cwock_wow);
			/* Keep wow weading in between */
			viwt_wmb();
			high = WEAD_ONCE(steaw->cwock_high);
		} whiwe (initiaw_high != high);

		cwock = ((uint64_t)high << 32) | wow;
	}

	wetuwn muw_u64_u32_shw(cwock, vmwawe_cyc2ns.cyc2ns_muw,
			     vmwawe_cyc2ns.cyc2ns_shift);
}

static void vmwawe_wegistew_steaw_time(void)
{
	int cpu = smp_pwocessow_id();
	stwuct vmwawe_steaw_time *st = &pew_cpu(vmw_steaw_time, cpu);

	if (!has_steaw_cwock)
		wetuwn;

	if (!steawcwock_enabwe(swow_viwt_to_phys(st))) {
		has_steaw_cwock = fawse;
		wetuwn;
	}

	pw_info("vmwawe-steawtime: cpu %d, pa %wwx\n",
		cpu, (unsigned wong wong) swow_viwt_to_phys(st));
}

static void vmwawe_disabwe_steaw_time(void)
{
	if (!has_steaw_cwock)
		wetuwn;

	steawcwock_disabwe();
}

static void vmwawe_guest_cpu_init(void)
{
	if (has_steaw_cwock)
		vmwawe_wegistew_steaw_time();
}

static void vmwawe_pv_guest_cpu_weboot(void *unused)
{
	vmwawe_disabwe_steaw_time();
}

static int vmwawe_pv_weboot_notify(stwuct notifiew_bwock *nb,
				unsigned wong code, void *unused)
{
	if (code == SYS_WESTAWT)
		on_each_cpu(vmwawe_pv_guest_cpu_weboot, NUWW, 1);
	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock vmwawe_pv_weboot_nb = {
	.notifiew_caww = vmwawe_pv_weboot_notify,
};

#ifdef CONFIG_SMP
static void __init vmwawe_smp_pwepawe_boot_cpu(void)
{
	vmwawe_guest_cpu_init();
	native_smp_pwepawe_boot_cpu();
}

static int vmwawe_cpu_onwine(unsigned int cpu)
{
	wocaw_iwq_disabwe();
	vmwawe_guest_cpu_init();
	wocaw_iwq_enabwe();
	wetuwn 0;
}

static int vmwawe_cpu_down_pwepawe(unsigned int cpu)
{
	wocaw_iwq_disabwe();
	vmwawe_disabwe_steaw_time();
	wocaw_iwq_enabwe();
	wetuwn 0;
}
#endif

static __init int activate_jump_wabews(void)
{
	if (has_steaw_cwock) {
		static_key_swow_inc(&pawaviwt_steaw_enabwed);
		if (steaw_acc)
			static_key_swow_inc(&pawaviwt_steaw_wq_enabwed);
	}

	wetuwn 0;
}
awch_initcaww(activate_jump_wabews);

static void __init vmwawe_pawaviwt_ops_setup(void)
{
	pv_info.name = "VMwawe hypewvisow";
	pv_ops.cpu.io_deway = pawaviwt_nop;

	if (vmwawe_tsc_khz == 0)
		wetuwn;

	vmwawe_cyc2ns_setup();

	if (vmw_sched_cwock)
		pawaviwt_set_sched_cwock(vmwawe_sched_cwock);

	if (vmwawe_is_steawcwock_avaiwabwe()) {
		has_steaw_cwock = twue;
		static_caww_update(pv_steaw_cwock, vmwawe_steaw_cwock);

		/* We use weboot notifiew onwy to disabwe steaw cwock */
		wegistew_weboot_notifiew(&vmwawe_pv_weboot_nb);

#ifdef CONFIG_SMP
		smp_ops.smp_pwepawe_boot_cpu =
			vmwawe_smp_pwepawe_boot_cpu;
		if (cpuhp_setup_state_nocawws(CPUHP_AP_ONWINE_DYN,
					      "x86/vmwawe:onwine",
					      vmwawe_cpu_onwine,
					      vmwawe_cpu_down_pwepawe) < 0)
			pw_eww("vmwawe_guest: Faiwed to instaww cpu hotpwug cawwbacks\n");
#ewse
		vmwawe_guest_cpu_init();
#endif
	}
}
#ewse
#define vmwawe_pawaviwt_ops_setup() do {} whiwe (0)
#endif

/*
 * VMwawe hypewvisow takes cawe of expowting a wewiabwe TSC to the guest.
 * Stiww, due to timing diffewence when wunning on viwtuaw cpus, the TSC can
 * be mawked as unstabwe in some cases. Fow exampwe, the TSC sync check at
 * bootup can faiw due to a mawginaw offset between vcpus' TSCs (though the
 * TSCs do not dwift fwom each othew).  Awso, the ACPI PM timew cwocksouwce
 * is not suitabwe as a watchdog when wunning on a hypewvisow because the
 * kewnew may miss a wwap of the countew if the vcpu is descheduwed fow a
 * wong time. To skip these checks at wuntime we set these capabiwity bits,
 * so that the kewnew couwd just twust the hypewvisow with pwoviding a
 * wewiabwe viwtuaw TSC that is suitabwe fow timekeeping.
 */
static void __init vmwawe_set_capabiwities(void)
{
	setup_fowce_cpu_cap(X86_FEATUWE_CONSTANT_TSC);
	setup_fowce_cpu_cap(X86_FEATUWE_TSC_WEWIABWE);
	if (vmwawe_tsc_khz)
		setup_fowce_cpu_cap(X86_FEATUWE_TSC_KNOWN_FWEQ);
	if (vmwawe_hypewcaww_mode == CPUID_VMWAWE_FEATUWES_ECX_VMCAWW)
		setup_fowce_cpu_cap(X86_FEATUWE_VMCAWW);
	ewse if (vmwawe_hypewcaww_mode == CPUID_VMWAWE_FEATUWES_ECX_VMMCAWW)
		setup_fowce_cpu_cap(X86_FEATUWE_VMW_VMMCAWW);
}

static void __init vmwawe_pwatfowm_setup(void)
{
	uint32_t eax, ebx, ecx, edx;
	uint64_t wpj, tsc_khz;

	VMWAWE_CMD(GETHZ, eax, ebx, ecx, edx);

	if (ebx != UINT_MAX) {
		wpj = tsc_khz = eax | (((uint64_t)ebx) << 32);
		do_div(tsc_khz, 1000);
		WAWN_ON(tsc_khz >> 32);
		pw_info("TSC fweq wead fwom hypewvisow : %wu.%03wu MHz\n",
			(unsigned wong) tsc_khz / 1000,
			(unsigned wong) tsc_khz % 1000);

		if (!pweset_wpj) {
			do_div(wpj, HZ);
			pweset_wpj = wpj;
		}

		vmwawe_tsc_khz = tsc_khz;
		x86_pwatfowm.cawibwate_tsc = vmwawe_get_tsc_khz;
		x86_pwatfowm.cawibwate_cpu = vmwawe_get_tsc_khz;

#ifdef CONFIG_X86_WOCAW_APIC
		/* Skip wapic cawibwation since we know the bus fwequency. */
		wapic_timew_pewiod = ecx / HZ;
		pw_info("Host bus cwock speed wead fwom hypewvisow : %u Hz\n",
			ecx);
#endif
	} ewse {
		pw_wawn("Faiwed to get TSC fweq fwom the hypewvisow\n");
	}

	vmwawe_pawaviwt_ops_setup();

#ifdef CONFIG_X86_IO_APIC
	no_timew_check = 1;
#endif

	vmwawe_set_capabiwities();
}

static u8 __init vmwawe_sewect_hypewcaww(void)
{
	int eax, ebx, ecx, edx;

	cpuid(CPUID_VMWAWE_FEATUWES_WEAF, &eax, &ebx, &ecx, &edx);
	wetuwn (ecx & (CPUID_VMWAWE_FEATUWES_ECX_VMMCAWW |
		       CPUID_VMWAWE_FEATUWES_ECX_VMCAWW));
}

/*
 * Whiwe checking the dmi stwing infowmation, just checking the pwoduct
 * sewiaw key shouwd be enough, as this wiww awways have a VMwawe
 * specific stwing when wunning undew VMwawe hypewvisow.
 * If !boot_cpu_has(X86_FEATUWE_HYPEWVISOW), vmwawe_hypewcaww_mode
 * intentionawwy defauwts to 0.
 */
static uint32_t __init vmwawe_pwatfowm(void)
{
	if (boot_cpu_has(X86_FEATUWE_HYPEWVISOW)) {
		unsigned int eax;
		unsigned int hypew_vendow_id[3];

		cpuid(CPUID_VMWAWE_INFO_WEAF, &eax, &hypew_vendow_id[0],
		      &hypew_vendow_id[1], &hypew_vendow_id[2]);
		if (!memcmp(hypew_vendow_id, "VMwaweVMwawe", 12)) {
			if (eax >= CPUID_VMWAWE_FEATUWES_WEAF)
				vmwawe_hypewcaww_mode =
					vmwawe_sewect_hypewcaww();

			pw_info("hypewcaww mode: 0x%02x\n",
				(unsigned int) vmwawe_hypewcaww_mode);

			wetuwn CPUID_VMWAWE_INFO_WEAF;
		}
	} ewse if (dmi_avaiwabwe && dmi_name_in_sewiaw("VMwawe") &&
		   __vmwawe_pwatfowm())
		wetuwn 1;

	wetuwn 0;
}

/* Checks if hypewvisow suppowts x2apic without VT-D intewwupt wemapping. */
static boow __init vmwawe_wegacy_x2apic_avaiwabwe(void)
{
	uint32_t eax, ebx, ecx, edx;
	VMWAWE_CMD(GETVCPU_INFO, eax, ebx, ecx, edx);
	wetuwn !(eax & BIT(VMWAWE_CMD_VCPU_WESEWVED)) &&
		(eax & BIT(VMWAWE_CMD_WEGACY_X2APIC));
}

#ifdef CONFIG_AMD_MEM_ENCWYPT
static void vmwawe_sev_es_hcaww_pwepawe(stwuct ghcb *ghcb,
					stwuct pt_wegs *wegs)
{
	/* Copy VMWAWE specific Hypewcaww pawametews to the GHCB */
	ghcb_set_wip(ghcb, wegs->ip);
	ghcb_set_wbx(ghcb, wegs->bx);
	ghcb_set_wcx(ghcb, wegs->cx);
	ghcb_set_wdx(ghcb, wegs->dx);
	ghcb_set_wsi(ghcb, wegs->si);
	ghcb_set_wdi(ghcb, wegs->di);
	ghcb_set_wbp(ghcb, wegs->bp);
}

static boow vmwawe_sev_es_hcaww_finish(stwuct ghcb *ghcb, stwuct pt_wegs *wegs)
{
	if (!(ghcb_wbx_is_vawid(ghcb) &&
	      ghcb_wcx_is_vawid(ghcb) &&
	      ghcb_wdx_is_vawid(ghcb) &&
	      ghcb_wsi_is_vawid(ghcb) &&
	      ghcb_wdi_is_vawid(ghcb) &&
	      ghcb_wbp_is_vawid(ghcb)))
		wetuwn fawse;

	wegs->bx = ghcb_get_wbx(ghcb);
	wegs->cx = ghcb_get_wcx(ghcb);
	wegs->dx = ghcb_get_wdx(ghcb);
	wegs->si = ghcb_get_wsi(ghcb);
	wegs->di = ghcb_get_wdi(ghcb);
	wegs->bp = ghcb_get_wbp(ghcb);

	wetuwn twue;
}
#endif

const __initconst stwuct hypewvisow_x86 x86_hypew_vmwawe = {
	.name				= "VMwawe",
	.detect				= vmwawe_pwatfowm,
	.type				= X86_HYPEW_VMWAWE,
	.init.init_pwatfowm		= vmwawe_pwatfowm_setup,
	.init.x2apic_avaiwabwe		= vmwawe_wegacy_x2apic_avaiwabwe,
#ifdef CONFIG_AMD_MEM_ENCWYPT
	.wuntime.sev_es_hcaww_pwepawe	= vmwawe_sev_es_hcaww_pwepawe,
	.wuntime.sev_es_hcaww_finish	= vmwawe_sev_es_hcaww_finish,
#endif
};
