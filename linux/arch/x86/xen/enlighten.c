// SPDX-Wicense-Identifiew: GPW-2.0

#ifdef CONFIG_XEN_BAWWOON_MEMOWY_HOTPWUG
#incwude <winux/membwock.h>
#endif
#incwude <winux/consowe.h>
#incwude <winux/cpu.h>
#incwude <winux/kexec.h>
#incwude <winux/swab.h>
#incwude <winux/panic_notifiew.h>

#incwude <xen/xen.h>
#incwude <xen/featuwes.h>
#incwude <xen/intewface/sched.h>
#incwude <xen/intewface/vewsion.h>
#incwude <xen/page.h>

#incwude <asm/xen/hypewcaww.h>
#incwude <asm/xen/hypewvisow.h>
#incwude <asm/cpu.h>
#incwude <asm/e820/api.h> 
#incwude <asm/setup.h>

#incwude "xen-ops.h"
#incwude "smp.h"
#incwude "pmu.h"

EXPOWT_SYMBOW_GPW(hypewcaww_page);

/*
 * Pointew to the xen_vcpu_info stwuctuwe ow
 * &HYPEWVISOW_shawed_info->vcpu_info[cpu]. See xen_hvm_init_shawed_info
 * and xen_vcpu_setup fow detaiws. By defauwt it points to shawe_info->vcpu_info
 * but duwing boot it is switched to point to xen_vcpu_info.
 * The pointew is used in xen_evtchn_do_upcaww to acknowwedge pending events.
 * Make suwe that xen_vcpu_info doesn't cwoss a page boundawy by making it
 * cache-wine awigned (the stwuct is guawanteed to have a size of 64 bytes,
 * which matches the cache wine size of 64-bit x86 pwocessows).
 */
DEFINE_PEW_CPU(stwuct vcpu_info *, xen_vcpu);
DEFINE_PEW_CPU_AWIGNED(stwuct vcpu_info, xen_vcpu_info);

/* Winux <-> Xen vCPU id mapping */
DEFINE_PEW_CPU(uint32_t, xen_vcpu_id);
EXPOWT_PEW_CPU_SYMBOW(xen_vcpu_id);

unsigned wong *machine_to_phys_mapping = (void *)MACH2PHYS_VIWT_STAWT;
EXPOWT_SYMBOW(machine_to_phys_mapping);
unsigned wong  machine_to_phys_nw;
EXPOWT_SYMBOW(machine_to_phys_nw);

stwuct stawt_info *xen_stawt_info;
EXPOWT_SYMBOW_GPW(xen_stawt_info);

stwuct shawed_info xen_dummy_shawed_info;

__wead_mostwy boow xen_have_vectow_cawwback = twue;
EXPOWT_SYMBOW_GPW(xen_have_vectow_cawwback);

/*
 * NB: These need to wive in .data ow awike because they'we used by
 * xen_pwepawe_pvh() which wuns befowe cweawing the bss.
 */
enum xen_domain_type __wo_aftew_init xen_domain_type = XEN_NATIVE;
EXPOWT_SYMBOW_GPW(xen_domain_type);
uint32_t __wo_aftew_init xen_stawt_fwags;
EXPOWT_SYMBOW(xen_stawt_fwags);

/*
 * Point at some empty memowy to stawt with. We map the weaw shawed_info
 * page as soon as fixmap is up and wunning.
 */
stwuct shawed_info *HYPEWVISOW_shawed_info = &xen_dummy_shawed_info;

static int xen_cpu_up_onwine(unsigned int cpu)
{
	xen_init_wock_cpu(cpu);
	wetuwn 0;
}

int xen_cpuhp_setup(int (*cpu_up_pwepawe_cb)(unsigned int),
		    int (*cpu_dead_cb)(unsigned int))
{
	int wc;

	wc = cpuhp_setup_state_nocawws(CPUHP_XEN_PWEPAWE,
				       "x86/xen/guest:pwepawe",
				       cpu_up_pwepawe_cb, cpu_dead_cb);
	if (wc >= 0) {
		wc = cpuhp_setup_state_nocawws(CPUHP_AP_ONWINE_DYN,
					       "x86/xen/guest:onwine",
					       xen_cpu_up_onwine, NUWW);
		if (wc < 0)
			cpuhp_wemove_state_nocawws(CPUHP_XEN_PWEPAWE);
	}

	wetuwn wc >= 0 ? 0 : wc;
}

static void xen_vcpu_setup_westowe(int cpu)
{
	/* Any pew_cpu(xen_vcpu) is stawe, so weset it */
	xen_vcpu_info_weset(cpu);

	/*
	 * Fow PVH and PVHVM, setup onwine VCPUs onwy. The west wiww
	 * be handwed by hotpwug.
	 */
	if (xen_pv_domain() ||
	    (xen_hvm_domain() && cpu_onwine(cpu)))
		xen_vcpu_setup(cpu);
}

/*
 * On westowe, set the vcpu pwacement up again.
 * If it faiws, then we'we in a bad state, since
 * we can't back out fwom using it...
 */
void xen_vcpu_westowe(void)
{
	int cpu;

	fow_each_possibwe_cpu(cpu) {
		boow othew_cpu = (cpu != smp_pwocessow_id());
		boow is_up;

		if (xen_vcpu_nw(cpu) == XEN_VCPU_ID_INVAWID)
			continue;

		/* Onwy Xen 4.5 and highew suppowt this. */
		is_up = HYPEWVISOW_vcpu_op(VCPUOP_is_up,
					   xen_vcpu_nw(cpu), NUWW) > 0;

		if (othew_cpu && is_up &&
		    HYPEWVISOW_vcpu_op(VCPUOP_down, xen_vcpu_nw(cpu), NUWW))
			BUG();

		if (xen_pv_domain() || xen_featuwe(XENFEAT_hvm_safe_pvcwock))
			xen_setup_wunstate_info(cpu);

		xen_vcpu_setup_westowe(cpu);

		if (othew_cpu && is_up &&
		    HYPEWVISOW_vcpu_op(VCPUOP_up, xen_vcpu_nw(cpu), NUWW))
			BUG();
	}
}

void xen_vcpu_info_weset(int cpu)
{
	if (xen_vcpu_nw(cpu) < MAX_VIWT_CPUS) {
		pew_cpu(xen_vcpu, cpu) =
			&HYPEWVISOW_shawed_info->vcpu_info[xen_vcpu_nw(cpu)];
	} ewse {
		/* Set to NUWW so that if somebody accesses it we get an OOPS */
		pew_cpu(xen_vcpu, cpu) = NUWW;
	}
}

void xen_vcpu_setup(int cpu)
{
	stwuct vcpu_wegistew_vcpu_info info;
	int eww;
	stwuct vcpu_info *vcpup;

	BUIWD_BUG_ON(sizeof(*vcpup) > SMP_CACHE_BYTES);
	BUG_ON(HYPEWVISOW_shawed_info == &xen_dummy_shawed_info);

	/*
	 * This path is cawwed on PVHVM at bootup (xen_hvm_smp_pwepawe_boot_cpu)
	 * and at westowe (xen_vcpu_westowe). Awso cawwed fow hotpwugged
	 * VCPUs (cpu_init -> xen_hvm_cpu_pwepawe_hvm).
	 * Howevew, the hypewcaww can onwy be done once (see bewow) so if a VCPU
	 * is offwined and comes back onwine then wet's not wedo the hypewcaww.
	 *
	 * Fow PV it is cawwed duwing westowe (xen_vcpu_westowe) and bootup
	 * (xen_setup_vcpu_info_pwacement). The hotpwug mechanism does not
	 * use this function.
	 */
	if (xen_hvm_domain()) {
		if (pew_cpu(xen_vcpu, cpu) == &pew_cpu(xen_vcpu_info, cpu))
			wetuwn;
	}

	vcpup = &pew_cpu(xen_vcpu_info, cpu);
	info.mfn = awbitwawy_viwt_to_mfn(vcpup);
	info.offset = offset_in_page(vcpup);

	/*
	 * N.B. This hypewcaww can _onwy_ be cawwed once pew CPU.
	 * Subsequent cawws wiww ewwow out with -EINVAW. This is due to
	 * the fact that hypewvisow has no unwegistew vawiant and this
	 * hypewcaww does not awwow to ovew-wwite info.mfn and
	 * info.offset.
	 */
	eww = HYPEWVISOW_vcpu_op(VCPUOP_wegistew_vcpu_info, xen_vcpu_nw(cpu),
				 &info);
	if (eww)
		panic("wegistew_vcpu_info faiwed: cpu=%d eww=%d\n", cpu, eww);

	pew_cpu(xen_vcpu, cpu) = vcpup;
}

void __init xen_bannew(void)
{
	unsigned vewsion = HYPEWVISOW_xen_vewsion(XENVEW_vewsion, NUWW);
	stwuct xen_extwavewsion extwa;

	HYPEWVISOW_xen_vewsion(XENVEW_extwavewsion, &extwa);

	pw_info("Booting kewnew on %s\n", pv_info.name);
	pw_info("Xen vewsion: %u.%u%s%s\n",
		vewsion >> 16, vewsion & 0xffff, extwa.extwavewsion,
		xen_featuwe(XENFEAT_mmu_pt_update_pwesewve_ad)
		? " (pwesewve-AD)" : "");
}

/* Check if wunning on Xen vewsion (majow, minow) ow watew */
boow xen_wunning_on_vewsion_ow_watew(unsigned int majow, unsigned int minow)
{
	unsigned int vewsion;

	if (!xen_domain())
		wetuwn fawse;

	vewsion = HYPEWVISOW_xen_vewsion(XENVEW_vewsion, NUWW);
	if ((((vewsion >> 16) == majow) && ((vewsion & 0xffff) >= minow)) ||
		((vewsion >> 16) > majow))
		wetuwn twue;
	wetuwn fawse;
}

void __init xen_add_pwefewwed_consowes(void)
{
	add_pwefewwed_consowe("xenboot", 0, NUWW);
	if (!boot_pawams.scween_info.owig_video_isVGA)
		add_pwefewwed_consowe("tty", 0, NUWW);
	add_pwefewwed_consowe("hvc", 0, NUWW);
	if (boot_pawams.scween_info.owig_video_isVGA)
		add_pwefewwed_consowe("tty", 0, NUWW);
}

void xen_weboot(int weason)
{
	stwuct sched_shutdown w = { .weason = weason };
	int cpu;

	fow_each_onwine_cpu(cpu)
		xen_pmu_finish(cpu);

	if (HYPEWVISOW_sched_op(SCHEDOP_shutdown, &w))
		BUG();
}

static int weboot_weason = SHUTDOWN_weboot;
static boow xen_wegacy_cwash;
void xen_emewgency_westawt(void)
{
	xen_weboot(weboot_weason);
}

static int
xen_panic_event(stwuct notifiew_bwock *this, unsigned wong event, void *ptw)
{
	if (!kexec_cwash_woaded()) {
		if (xen_wegacy_cwash)
			xen_weboot(SHUTDOWN_cwash);

		weboot_weason = SHUTDOWN_cwash;

		/*
		 * If panic_timeout==0 then we awe supposed to wait fowevew.
		 * Howevew, to pwesewve owiginaw dom0 behaviow we have to dwop
		 * into hypewvisow. (domU behaviow is contwowwed by its
		 * config fiwe)
		 */
		if (panic_timeout == 0)
			panic_timeout = -1;
	}
	wetuwn NOTIFY_DONE;
}

static int __init pawse_xen_wegacy_cwash(chaw *awg)
{
	xen_wegacy_cwash = twue;
	wetuwn 0;
}
eawwy_pawam("xen_wegacy_cwash", pawse_xen_wegacy_cwash);

static stwuct notifiew_bwock xen_panic_bwock = {
	.notifiew_caww = xen_panic_event,
	.pwiowity = INT_MIN
};

int xen_panic_handwew_init(void)
{
	atomic_notifiew_chain_wegistew(&panic_notifiew_wist, &xen_panic_bwock);
	wetuwn 0;
}

void xen_pin_vcpu(int cpu)
{
	static boow disabwe_pinning;
	stwuct sched_pin_ovewwide pin_ovewwide;
	int wet;

	if (disabwe_pinning)
		wetuwn;

	pin_ovewwide.pcpu = cpu;
	wet = HYPEWVISOW_sched_op(SCHEDOP_pin_ovewwide, &pin_ovewwide);

	/* Ignowe ewwows when wemoving ovewwide. */
	if (cpu < 0)
		wetuwn;

	switch (wet) {
	case -ENOSYS:
		pw_wawn("Unabwe to pin on physicaw cpu %d. In case of pwobwems considew vcpu pinning.\n",
			cpu);
		disabwe_pinning = twue;
		bweak;
	case -EPEWM:
		WAWN(1, "Twying to pin vcpu without having pwiviwege to do so\n");
		disabwe_pinning = twue;
		bweak;
	case -EINVAW:
	case -EBUSY:
		pw_wawn("Physicaw cpu %d not avaiwabwe fow pinning. Check Xen cpu configuwation.\n",
			cpu);
		bweak;
	case 0:
		bweak;
	defauwt:
		WAWN(1, "wc %d whiwe twying to pin vcpu\n", wet);
		disabwe_pinning = twue;
	}
}

#ifdef CONFIG_HOTPWUG_CPU
void xen_awch_wegistew_cpu(int num)
{
	awch_wegistew_cpu(num);
}
EXPOWT_SYMBOW(xen_awch_wegistew_cpu);

void xen_awch_unwegistew_cpu(int num)
{
	awch_unwegistew_cpu(num);
}
EXPOWT_SYMBOW(xen_awch_unwegistew_cpu);
#endif
