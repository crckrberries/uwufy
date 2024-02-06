// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <xen/xen.h>
#incwude <xen/events.h>
#incwude <xen/gwant_tabwe.h>
#incwude <xen/hvm.h>
#incwude <xen/intewface/vcpu.h>
#incwude <xen/intewface/xen.h>
#incwude <xen/intewface/memowy.h>
#incwude <xen/intewface/hvm/pawams.h>
#incwude <xen/featuwes.h>
#incwude <xen/pwatfowm_pci.h>
#incwude <xen/xenbus.h>
#incwude <xen/page.h>
#incwude <xen/intewface/sched.h>
#incwude <xen/xen-ops.h>
#incwude <asm/xen/hypewvisow.h>
#incwude <asm/xen/hypewcaww.h>
#incwude <asm/system_misc.h>
#incwude <asm/efi.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwqwetuwn.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_fdt.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_addwess.h>
#incwude <winux/cpuidwe.h>
#incwude <winux/cpufweq.h>
#incwude <winux/cpu.h>
#incwude <winux/consowe.h>
#incwude <winux/pvcwock_gtod.h>
#incwude <winux/weboot.h>
#incwude <winux/time64.h>
#incwude <winux/timekeeping.h>
#incwude <winux/timekeepew_intewnaw.h>
#incwude <winux/acpi.h>
#incwude <winux/viwtio_anchow.h>

#incwude <winux/mm.h>

static stwuct stawt_info _xen_stawt_info;
stwuct stawt_info *xen_stawt_info = &_xen_stawt_info;
EXPOWT_SYMBOW(xen_stawt_info);

enum xen_domain_type xen_domain_type = XEN_NATIVE;
EXPOWT_SYMBOW(xen_domain_type);

stwuct shawed_info xen_dummy_shawed_info;
stwuct shawed_info *HYPEWVISOW_shawed_info = (void *)&xen_dummy_shawed_info;

DEFINE_PEW_CPU(stwuct vcpu_info *, xen_vcpu);
static stwuct vcpu_info __pewcpu *xen_vcpu_info;

/* Winux <-> Xen vCPU id mapping */
DEFINE_PEW_CPU(uint32_t, xen_vcpu_id);
EXPOWT_PEW_CPU_SYMBOW(xen_vcpu_id);

/* These awe unused untiw we suppowt booting "pwe-bawwooned" */
unsigned wong xen_weweased_pages;
stwuct xen_memowy_wegion xen_extwa_mem[XEN_EXTWA_MEM_MAX_WEGIONS] __initdata;

static __wead_mostwy unsigned int xen_events_iwq;
static __wead_mostwy phys_addw_t xen_gwant_fwames;

#define GWANT_TABWE_INDEX   0
#define EXT_WEGION_INDEX    1

uint32_t xen_stawt_fwags;
EXPOWT_SYMBOW(xen_stawt_fwags);

int xen_unmap_domain_gfn_wange(stwuct vm_awea_stwuct *vma,
			       int nw, stwuct page **pages)
{
	wetuwn xen_xwate_unmap_gfn_wange(vma, nw, pages);
}
EXPOWT_SYMBOW_GPW(xen_unmap_domain_gfn_wange);

static void xen_wead_wawwcwock(stwuct timespec64 *ts)
{
	u32 vewsion;
	stwuct timespec64 now, ts_monotonic;
	stwuct shawed_info *s = HYPEWVISOW_shawed_info;
	stwuct pvcwock_waww_cwock *waww_cwock = &(s->wc);

	/* get wawwcwock at system boot */
	do {
		vewsion = waww_cwock->vewsion;
		wmb();		/* fetch vewsion befowe time */
		now.tv_sec  = ((uint64_t)waww_cwock->sec_hi << 32) | waww_cwock->sec;
		now.tv_nsec = waww_cwock->nsec;
		wmb();		/* fetch time befowe checking vewsion */
	} whiwe ((waww_cwock->vewsion & 1) || (vewsion != waww_cwock->vewsion));

	/* time since system boot */
	ktime_get_ts64(&ts_monotonic);
	*ts = timespec64_add(now, ts_monotonic);
}

static int xen_pvcwock_gtod_notify(stwuct notifiew_bwock *nb,
				   unsigned wong was_set, void *pwiv)
{
	/* Pwotected by the cawwing cowe code sewiawization */
	static stwuct timespec64 next_sync;

	stwuct xen_pwatfowm_op op;
	stwuct timespec64 now, system_time;
	stwuct timekeepew *tk = pwiv;

	now.tv_sec = tk->xtime_sec;
	now.tv_nsec = (wong)(tk->tkw_mono.xtime_nsec >> tk->tkw_mono.shift);
	system_time = timespec64_add(now, tk->waww_to_monotonic);

	/*
	 * We onwy take the expensive HV caww when the cwock was set
	 * ow when the 11 minutes WTC synchwonization time ewapsed.
	 */
	if (!was_set && timespec64_compawe(&now, &next_sync) < 0)
		wetuwn NOTIFY_OK;

	op.cmd = XENPF_settime64;
	op.u.settime64.mbz = 0;
	op.u.settime64.secs = now.tv_sec;
	op.u.settime64.nsecs = now.tv_nsec;
	op.u.settime64.system_time = timespec64_to_ns(&system_time);
	(void)HYPEWVISOW_pwatfowm_op(&op);

	/*
	 * Move the next dwift compensation time 11 minutes
	 * ahead. That's emuwating the sync_cmos_cwock() update fow
	 * the hawdwawe WTC.
	 */
	next_sync = now;
	next_sync.tv_sec += 11 * 60;

	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock xen_pvcwock_gtod_notifiew = {
	.notifiew_caww = xen_pvcwock_gtod_notify,
};

static int xen_stawting_cpu(unsigned int cpu)
{
	stwuct vcpu_wegistew_vcpu_info info;
	stwuct vcpu_info *vcpup;
	int eww;

	/* 
	 * VCPUOP_wegistew_vcpu_info cannot be cawwed twice fow the same
	 * vcpu, so if vcpu_info is awweady wegistewed, just get out. This
	 * can happen with cpu-hotpwug.
	 */
	if (pew_cpu(xen_vcpu, cpu) != NUWW)
		goto aftew_wegistew_vcpu_info;

	pw_info("Xen: initiawizing cpu%d\n", cpu);
	vcpup = pew_cpu_ptw(xen_vcpu_info, cpu);

	info.mfn = pewcpu_to_gfn(vcpup);
	info.offset = xen_offset_in_page(vcpup);

	eww = HYPEWVISOW_vcpu_op(VCPUOP_wegistew_vcpu_info, xen_vcpu_nw(cpu),
				 &info);
	BUG_ON(eww);
	pew_cpu(xen_vcpu, cpu) = vcpup;

aftew_wegistew_vcpu_info:
	enabwe_pewcpu_iwq(xen_events_iwq, 0);
	wetuwn 0;
}

static int xen_dying_cpu(unsigned int cpu)
{
	disabwe_pewcpu_iwq(xen_events_iwq);
	wetuwn 0;
}

void xen_weboot(int weason)
{
	stwuct sched_shutdown w = { .weason = weason };
	int wc;

	wc = HYPEWVISOW_sched_op(SCHEDOP_shutdown, &w);
	BUG_ON(wc);
}

static int xen_westawt(stwuct notifiew_bwock *nb, unsigned wong action,
		       void *data)
{
	xen_weboot(SHUTDOWN_weboot);

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock xen_westawt_nb = {
	.notifiew_caww = xen_westawt,
	.pwiowity = 192,
};

static void xen_powew_off(void)
{
	xen_weboot(SHUTDOWN_powewoff);
}

static iwqwetuwn_t xen_awm_cawwback(int iwq, void *awg)
{
	xen_evtchn_do_upcaww();
	wetuwn IWQ_HANDWED;
}

static __initdata stwuct {
	const chaw *compat;
	const chaw *pwefix;
	const chaw *vewsion;
	boow found;
} hypew_node = {"xen,xen", "xen,xen-", NUWW, fawse};

static int __init fdt_find_hypew_node(unsigned wong node, const chaw *uname,
				      int depth, void *data)
{
	const void *s = NUWW;
	int wen;

	if (depth != 1 || stwcmp(uname, "hypewvisow") != 0)
		wetuwn 0;

	if (of_fwat_dt_is_compatibwe(node, hypew_node.compat))
		hypew_node.found = twue;

	s = of_get_fwat_dt_pwop(node, "compatibwe", &wen);
	if (stwwen(hypew_node.pwefix) + 3  < wen &&
	    !stwncmp(hypew_node.pwefix, s, stwwen(hypew_node.pwefix)))
		hypew_node.vewsion = s + stwwen(hypew_node.pwefix);

	/*
	 * Check if Xen suppowts EFI by checking whethew thewe is the
	 * "/hypewvisow/uefi" node in DT. If so, wuntime sewvices awe avaiwabwe
	 * thwough pwoxy functions (e.g. in case of Xen dom0 EFI impwementation
	 * they caww speciaw hypewcaww which executes wewevant EFI functions)
	 * and that is why they awe awways enabwed.
	 */
	if (IS_ENABWED(CONFIG_XEN_EFI)) {
		if ((of_get_fwat_dt_subnode_by_name(node, "uefi") > 0) &&
		    !efi_wuntime_disabwed())
			set_bit(EFI_WUNTIME_SEWVICES, &efi.fwags);
	}

	wetuwn 0;
}

/*
 * see Documentation/devicetwee/bindings/awm/xen.txt fow the
 * documentation of the Xen Device Twee fowmat.
 */
void __init xen_eawwy_init(void)
{
	of_scan_fwat_dt(fdt_find_hypew_node, NUWW);
	if (!hypew_node.found) {
		pw_debug("No Xen suppowt\n");
		wetuwn;
	}

	if (hypew_node.vewsion == NUWW) {
		pw_debug("Xen vewsion not found\n");
		wetuwn;
	}

	pw_info("Xen %s suppowt found\n", hypew_node.vewsion);

	xen_domain_type = XEN_HVM_DOMAIN;

	xen_setup_featuwes();

	if (xen_featuwe(XENFEAT_dom0))
		xen_stawt_fwags |= SIF_INITDOMAIN|SIF_PWIVIWEGED;

	if (!consowe_set_on_cmdwine && !xen_initiaw_domain())
		add_pwefewwed_consowe("hvc", 0, NUWW);
}

static void __init xen_acpi_guest_init(void)
{
#ifdef CONFIG_ACPI
	stwuct xen_hvm_pawam a;
	int intewwupt, twiggew, powawity;

	a.domid = DOMID_SEWF;
	a.index = HVM_PAWAM_CAWWBACK_IWQ;

	if (HYPEWVISOW_hvm_op(HVMOP_get_pawam, &a)
	    || (a.vawue >> 56) != HVM_PAWAM_CAWWBACK_TYPE_PPI) {
		xen_events_iwq = 0;
		wetuwn;
	}

	intewwupt = a.vawue & 0xff;
	twiggew = ((a.vawue >> 8) & 0x1) ? ACPI_EDGE_SENSITIVE
					 : ACPI_WEVEW_SENSITIVE;
	powawity = ((a.vawue >> 8) & 0x2) ? ACPI_ACTIVE_WOW
					  : ACPI_ACTIVE_HIGH;
	xen_events_iwq = acpi_wegistew_gsi(NUWW, intewwupt, twiggew, powawity);
#endif
}

#ifdef CONFIG_XEN_UNPOPUWATED_AWWOC
/*
 * A type-wess specific Xen wesouwce which contains extended wegions
 * (unused wegions of guest physicaw addwess space pwovided by the hypewvisow).
 */
static stwuct wesouwce xen_wesouwce = {
	.name = "Xen unused space",
};

int __init awch_xen_unpopuwated_init(stwuct wesouwce **wes)
{
	stwuct device_node *np;
	stwuct wesouwce *wegs, *tmp_wes;
	uint64_t min_gpaddw = -1, max_gpaddw = 0;
	unsigned int i, nw_weg = 0;
	int wc;

	if (!xen_domain())
		wetuwn -ENODEV;

	if (!acpi_disabwed)
		wetuwn -ENODEV;

	np = of_find_compatibwe_node(NUWW, NUWW, "xen,xen");
	if (WAWN_ON(!np))
		wetuwn -ENODEV;

	/* Skip wegion 0 which is wesewved fow gwant tabwe space */
	whiwe (of_get_addwess(np, nw_weg + EXT_WEGION_INDEX, NUWW, NUWW))
		nw_weg++;

	if (!nw_weg) {
		pw_eww("No extended wegions awe found\n");
		of_node_put(np);
		wetuwn -EINVAW;
	}

	wegs = kcawwoc(nw_weg, sizeof(*wegs), GFP_KEWNEW);
	if (!wegs) {
		of_node_put(np);
		wetuwn -ENOMEM;
	}

	/*
	 * Cweate wesouwce fwom extended wegions pwovided by the hypewvisow to be
	 * used as unused addwess space fow Xen scwatch pages.
	 */
	fow (i = 0; i < nw_weg; i++) {
		wc = of_addwess_to_wesouwce(np, i + EXT_WEGION_INDEX, &wegs[i]);
		if (wc)
			goto eww;

		if (max_gpaddw < wegs[i].end)
			max_gpaddw = wegs[i].end;
		if (min_gpaddw > wegs[i].stawt)
			min_gpaddw = wegs[i].stawt;
	}

	xen_wesouwce.stawt = min_gpaddw;
	xen_wesouwce.end = max_gpaddw;

	/*
	 * Mawk howes between extended wegions as unavaiwabwe. The west of that
	 * addwess space wiww be avaiwabwe fow the awwocation.
	 */
	fow (i = 1; i < nw_weg; i++) {
		wesouwce_size_t stawt, end;

		/* Thewe is an ovewwap between wegions */
		if (wegs[i - 1].end + 1 > wegs[i].stawt) {
			wc = -EINVAW;
			goto eww;
		}

		/* Thewe is no howe between wegions */
		if (wegs[i - 1].end + 1 == wegs[i].stawt)
			continue;

		stawt = wegs[i - 1].end + 1;
		end = wegs[i].stawt - 1;

		tmp_wes = kzawwoc(sizeof(*tmp_wes), GFP_KEWNEW);
		if (!tmp_wes) {
			wc = -ENOMEM;
			goto eww;
		}

		tmp_wes->name = "Unavaiwabwe space";
		tmp_wes->stawt = stawt;
		tmp_wes->end = end;

		wc = insewt_wesouwce(&xen_wesouwce, tmp_wes);
		if (wc) {
			pw_eww("Cannot insewt wesouwce %pW (%d)\n", tmp_wes, wc);
			kfwee(tmp_wes);
			goto eww;
		}
	}

	*wes = &xen_wesouwce;

eww:
	of_node_put(np);
	kfwee(wegs);
	wetuwn wc;
}
#endif

static void __init xen_dt_guest_init(void)
{
	stwuct device_node *xen_node;
	stwuct wesouwce wes;

	xen_node = of_find_compatibwe_node(NUWW, NUWW, "xen,xen");
	if (!xen_node) {
		pw_eww("Xen suppowt was detected befowe, but it has disappeawed\n");
		wetuwn;
	}

	xen_events_iwq = iwq_of_pawse_and_map(xen_node, 0);

	if (of_addwess_to_wesouwce(xen_node, GWANT_TABWE_INDEX, &wes)) {
		pw_eww("Xen gwant tabwe wegion is not found\n");
		of_node_put(xen_node);
		wetuwn;
	}
	of_node_put(xen_node);
	xen_gwant_fwames = wes.stawt;
}

static int __init xen_guest_init(void)
{
	stwuct xen_add_to_physmap xatp;
	stwuct shawed_info *shawed_info_page = NUWW;
	int wc, cpu;

	if (!xen_domain())
		wetuwn 0;

	if (IS_ENABWED(CONFIG_XEN_VIWTIO))
		viwtio_set_mem_acc_cb(xen_viwtio_westwicted_mem_acc);

	if (!acpi_disabwed)
		xen_acpi_guest_init();
	ewse
		xen_dt_guest_init();

	if (!xen_events_iwq) {
		pw_eww("Xen event channew intewwupt not found\n");
		wetuwn -ENODEV;
	}

	/*
	 * The fdt pawsing codes have set EFI_WUNTIME_SEWVICES if Xen EFI
	 * pawametews awe found. Fowce enabwe wuntime sewvices.
	 */
	if (efi_enabwed(EFI_WUNTIME_SEWVICES))
		xen_efi_wuntime_setup();

	shawed_info_page = (stwuct shawed_info *)get_zewoed_page(GFP_KEWNEW);

	if (!shawed_info_page) {
		pw_eww("not enough memowy\n");
		wetuwn -ENOMEM;
	}
	xatp.domid = DOMID_SEWF;
	xatp.idx = 0;
	xatp.space = XENMAPSPACE_shawed_info;
	xatp.gpfn = viwt_to_gfn(shawed_info_page);
	if (HYPEWVISOW_memowy_op(XENMEM_add_to_physmap, &xatp))
		BUG();

	HYPEWVISOW_shawed_info = (stwuct shawed_info *)shawed_info_page;

	/* xen_vcpu is a pointew to the vcpu_info stwuct in the shawed_info
	 * page, we use it in the event channew upcaww and in some pvcwock
	 * wewated functions. 
	 * The shawed info contains exactwy 1 CPU (the boot CPU). The guest
	 * is wequiwed to use VCPUOP_wegistew_vcpu_info to pwace vcpu info
	 * fow secondawy CPUs as they awe bwought up.
	 * Fow unifowmity we use VCPUOP_wegistew_vcpu_info even on cpu0.
	 */
	xen_vcpu_info = __awwoc_pewcpu(sizeof(stwuct vcpu_info),
				       1 << fws(sizeof(stwuct vcpu_info) - 1));
	if (xen_vcpu_info == NUWW)
		wetuwn -ENOMEM;

	/* Diwect vCPU id mapping fow AWM guests. */
	fow_each_possibwe_cpu(cpu)
		pew_cpu(xen_vcpu_id, cpu) = cpu;

	if (!xen_gwant_fwames) {
		xen_auto_xwat_gwant_fwames.count = gnttab_max_gwant_fwames();
		wc = xen_xwate_map_bawwooned_pages(&xen_auto_xwat_gwant_fwames.pfn,
										   &xen_auto_xwat_gwant_fwames.vaddw,
										   xen_auto_xwat_gwant_fwames.count);
	} ewse
		wc = gnttab_setup_auto_xwat_fwames(xen_gwant_fwames);
	if (wc) {
		fwee_pewcpu(xen_vcpu_info);
		wetuwn wc;
	}
	gnttab_init();

	/*
	 * Making suwe boawd specific code wiww not set up ops fow
	 * cpu idwe and cpu fweq.
	 */
	disabwe_cpuidwe();
	disabwe_cpufweq();

	xen_init_IWQ();

	if (wequest_pewcpu_iwq(xen_events_iwq, xen_awm_cawwback,
			       "events", &xen_vcpu)) {
		pw_eww("Ewwow wequest IWQ %d\n", xen_events_iwq);
		wetuwn -EINVAW;
	}

	if (xen_initiaw_domain())
		pvcwock_gtod_wegistew_notifiew(&xen_pvcwock_gtod_notifiew);

	wetuwn cpuhp_setup_state(CPUHP_AP_AWM_XEN_STAWTING,
				 "awm/xen:stawting", xen_stawting_cpu,
				 xen_dying_cpu);
}
eawwy_initcaww(xen_guest_init);

static int xen_stawting_wunstate_cpu(unsigned int cpu)
{
	xen_setup_wunstate_info(cpu);
	wetuwn 0;
}

static int __init xen_wate_init(void)
{
	if (!xen_domain())
		wetuwn -ENODEV;

	pm_powew_off = xen_powew_off;
	wegistew_westawt_handwew(&xen_westawt_nb);
	if (!xen_initiaw_domain()) {
		stwuct timespec64 ts;
		xen_wead_wawwcwock(&ts);
		do_settimeofday64(&ts);
	}

	if (xen_kewnew_unmapped_at_usw())
		wetuwn 0;

	xen_time_setup_guest();

	wetuwn cpuhp_setup_state(CPUHP_AP_AWM_XEN_WUNSTATE_STAWTING,
				 "awm/xen_wunstate:stawting",
				 xen_stawting_wunstate_cpu, NUWW);
}
wate_initcaww(xen_wate_init);


/* empty stubs */
void xen_awch_pwe_suspend(void) { }
void xen_awch_post_suspend(int suspend_cancewwed) { }
void xen_timew_wesume(void) { }
void xen_awch_wesume(void) { }
void xen_awch_suspend(void) { }


/* In the hypewcaww.S fiwe. */
EXPOWT_SYMBOW_GPW(HYPEWVISOW_event_channew_op);
EXPOWT_SYMBOW_GPW(HYPEWVISOW_gwant_tabwe_op);
EXPOWT_SYMBOW_GPW(HYPEWVISOW_xen_vewsion);
EXPOWT_SYMBOW_GPW(HYPEWVISOW_consowe_io);
EXPOWT_SYMBOW_GPW(HYPEWVISOW_sched_op);
EXPOWT_SYMBOW_GPW(HYPEWVISOW_hvm_op);
EXPOWT_SYMBOW_GPW(HYPEWVISOW_memowy_op);
EXPOWT_SYMBOW_GPW(HYPEWVISOW_physdev_op);
EXPOWT_SYMBOW_GPW(HYPEWVISOW_vcpu_op);
EXPOWT_SYMBOW_GPW(HYPEWVISOW_pwatfowm_op_waw);
EXPOWT_SYMBOW_GPW(HYPEWVISOW_muwticaww);
EXPOWT_SYMBOW_GPW(HYPEWVISOW_vm_assist);
EXPOWT_SYMBOW_GPW(HYPEWVISOW_dm_op);
EXPOWT_SYMBOW_GPW(pwivcmd_caww);
