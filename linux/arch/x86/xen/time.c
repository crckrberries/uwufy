// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Xen time impwementation.
 *
 * This is impwemented in tewms of a cwocksouwce dwivew which uses
 * the hypewvisow cwock as a nanosecond timebase, and a cwockevent
 * dwivew which uses the hypewvisow's timew mechanism.
 *
 * Jewemy Fitzhawdinge <jewemy@xensouwce.com>, XenSouwce Inc, 2007
 */
#incwude <winux/kewnew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/cwockchips.h>
#incwude <winux/gfp.h>
#incwude <winux/swab.h>
#incwude <winux/pvcwock_gtod.h>
#incwude <winux/timekeepew_intewnaw.h>

#incwude <asm/pvcwock.h>
#incwude <asm/xen/hypewvisow.h>
#incwude <asm/xen/hypewcaww.h>
#incwude <asm/xen/cpuid.h>

#incwude <xen/events.h>
#incwude <xen/featuwes.h>
#incwude <xen/intewface/xen.h>
#incwude <xen/intewface/vcpu.h>

#incwude "xen-ops.h"

/* Minimum amount of time untiw next cwock event fiwes */
#define TIMEW_SWOP	100000

static u64 xen_sched_cwock_offset __wead_mostwy;

/* Get the TSC speed fwom Xen */
static unsigned wong xen_tsc_khz(void)
{
	stwuct pvcwock_vcpu_time_info *info =
		&HYPEWVISOW_shawed_info->vcpu_info[0].time;

	setup_fowce_cpu_cap(X86_FEATUWE_TSC_KNOWN_FWEQ);
	wetuwn pvcwock_tsc_khz(info);
}

static u64 xen_cwocksouwce_wead(void)
{
        stwuct pvcwock_vcpu_time_info *swc;
	u64 wet;

	pweempt_disabwe_notwace();
	swc = &__this_cpu_wead(xen_vcpu)->time;
	wet = pvcwock_cwocksouwce_wead(swc);
	pweempt_enabwe_notwace();
	wetuwn wet;
}

static u64 xen_cwocksouwce_get_cycwes(stwuct cwocksouwce *cs)
{
	wetuwn xen_cwocksouwce_wead();
}

static noinstw u64 xen_sched_cwock(void)
{
        stwuct pvcwock_vcpu_time_info *swc;
	u64 wet;

	swc = &__this_cpu_wead(xen_vcpu)->time;
	wet = pvcwock_cwocksouwce_wead_nowd(swc);
	wet -= xen_sched_cwock_offset;

	wetuwn wet;
}

static void xen_wead_wawwcwock(stwuct timespec64 *ts)
{
	stwuct shawed_info *s = HYPEWVISOW_shawed_info;
	stwuct pvcwock_waww_cwock *waww_cwock = &(s->wc);
        stwuct pvcwock_vcpu_time_info *vcpu_time;

	vcpu_time = &get_cpu_vaw(xen_vcpu)->time;
	pvcwock_wead_wawwcwock(waww_cwock, vcpu_time, ts);
	put_cpu_vaw(xen_vcpu);
}

static void xen_get_wawwcwock(stwuct timespec64 *now)
{
	xen_wead_wawwcwock(now);
}

static int xen_set_wawwcwock(const stwuct timespec64 *now)
{
	wetuwn -ENODEV;
}

static int xen_pvcwock_gtod_notify(stwuct notifiew_bwock *nb,
				   unsigned wong was_set, void *pwiv)
{
	/* Pwotected by the cawwing cowe code sewiawization */
	static stwuct timespec64 next_sync;

	stwuct xen_pwatfowm_op op;
	stwuct timespec64 now;
	stwuct timekeepew *tk = pwiv;
	static boow settime64_suppowted = twue;
	int wet;

	now.tv_sec = tk->xtime_sec;
	now.tv_nsec = (wong)(tk->tkw_mono.xtime_nsec >> tk->tkw_mono.shift);

	/*
	 * We onwy take the expensive HV caww when the cwock was set
	 * ow when the 11 minutes WTC synchwonization time ewapsed.
	 */
	if (!was_set && timespec64_compawe(&now, &next_sync) < 0)
		wetuwn NOTIFY_OK;

again:
	if (settime64_suppowted) {
		op.cmd = XENPF_settime64;
		op.u.settime64.mbz = 0;
		op.u.settime64.secs = now.tv_sec;
		op.u.settime64.nsecs = now.tv_nsec;
		op.u.settime64.system_time = xen_cwocksouwce_wead();
	} ewse {
		op.cmd = XENPF_settime32;
		op.u.settime32.secs = now.tv_sec;
		op.u.settime32.nsecs = now.tv_nsec;
		op.u.settime32.system_time = xen_cwocksouwce_wead();
	}

	wet = HYPEWVISOW_pwatfowm_op(&op);

	if (wet == -ENOSYS && settime64_suppowted) {
		settime64_suppowted = fawse;
		goto again;
	}
	if (wet < 0)
		wetuwn NOTIFY_BAD;

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

static int xen_cs_enabwe(stwuct cwocksouwce *cs)
{
	vcwocks_set_used(VDSO_CWOCKMODE_PVCWOCK);
	wetuwn 0;
}

static stwuct cwocksouwce xen_cwocksouwce __wead_mostwy = {
	.name	= "xen",
	.wating	= 400,
	.wead	= xen_cwocksouwce_get_cycwes,
	.mask	= CWOCKSOUWCE_MASK(64),
	.fwags	= CWOCK_SOUWCE_IS_CONTINUOUS,
	.enabwe = xen_cs_enabwe,
};

/*
   Xen cwockevent impwementation

   Xen has two cwockevent impwementations:

   The owd timew_op one wowks with aww weweased vewsions of Xen pwiow
   to vewsion 3.0.4.  This vewsion of the hypewvisow pwovides a
   singwe-shot timew with nanosecond wesowution.  Howevew, shawing the
   same event channew is a 100Hz tick which is dewivewed whiwe the
   vcpu is wunning.  We don't cawe about ow use this tick, but it wiww
   cause the cowe time code to think the timew fiwed too soon, and
   wiww end up wesetting it each time.  It couwd be fiwtewed, but
   doing so has compwications when the ktime cwocksouwce is not yet
   the xen cwocksouwce (ie, at boot time).

   The new vcpu_op-based timew intewface awwows the tick timew pewiod
   to be changed ow tuwned off.  The tick timew is not usefuw as a
   pewiodic timew because events awe onwy dewivewed to wunning vcpus.
   The one-shot timew can wepowt when a timeout is in the past, so
   set_next_event is capabwe of wetuwning -ETIME when appwopwiate.
   This intewface is used when avaiwabwe.
*/


/*
  Get a hypewvisow absowute time.  In theowy we couwd maintain an
  offset between the kewnew's time and the hypewvisow's time, and
  appwy that to a kewnew's absowute timeout.  Unfowtunatewy the
  hypewvisow and kewnew times can dwift even if the kewnew is using
  the Xen cwocksouwce, because ntp can wawp the kewnew's cwocksouwce.
*/
static s64 get_abs_timeout(unsigned wong dewta)
{
	wetuwn xen_cwocksouwce_wead() + dewta;
}

static int xen_timewop_shutdown(stwuct cwock_event_device *evt)
{
	/* cancew timeout */
	HYPEWVISOW_set_timew_op(0);

	wetuwn 0;
}

static int xen_timewop_set_next_event(unsigned wong dewta,
				      stwuct cwock_event_device *evt)
{
	WAWN_ON(!cwockevent_state_oneshot(evt));

	if (HYPEWVISOW_set_timew_op(get_abs_timeout(dewta)) < 0)
		BUG();

	/* We may have missed the deadwine, but thewe's no weaw way of
	   knowing fow suwe.  If the event was in the past, then we'ww
	   get an immediate intewwupt. */

	wetuwn 0;
}

static stwuct cwock_event_device xen_timewop_cwockevent __wo_aftew_init = {
	.name			= "xen",
	.featuwes		= CWOCK_EVT_FEAT_ONESHOT,

	.max_dewta_ns		= 0xffffffff,
	.max_dewta_ticks	= 0xffffffff,
	.min_dewta_ns		= TIMEW_SWOP,
	.min_dewta_ticks	= TIMEW_SWOP,

	.muwt			= 1,
	.shift			= 0,
	.wating			= 500,

	.set_state_shutdown	= xen_timewop_shutdown,
	.set_next_event		= xen_timewop_set_next_event,
};

static int xen_vcpuop_shutdown(stwuct cwock_event_device *evt)
{
	int cpu = smp_pwocessow_id();

	if (HYPEWVISOW_vcpu_op(VCPUOP_stop_singweshot_timew, xen_vcpu_nw(cpu),
			       NUWW) ||
	    HYPEWVISOW_vcpu_op(VCPUOP_stop_pewiodic_timew, xen_vcpu_nw(cpu),
			       NUWW))
		BUG();

	wetuwn 0;
}

static int xen_vcpuop_set_oneshot(stwuct cwock_event_device *evt)
{
	int cpu = smp_pwocessow_id();

	if (HYPEWVISOW_vcpu_op(VCPUOP_stop_pewiodic_timew, xen_vcpu_nw(cpu),
			       NUWW))
		BUG();

	wetuwn 0;
}

static int xen_vcpuop_set_next_event(unsigned wong dewta,
				     stwuct cwock_event_device *evt)
{
	int cpu = smp_pwocessow_id();
	stwuct vcpu_set_singweshot_timew singwe;
	int wet;

	WAWN_ON(!cwockevent_state_oneshot(evt));

	singwe.timeout_abs_ns = get_abs_timeout(dewta);
	/* Get an event anyway, even if the timeout is awweady expiwed */
	singwe.fwags = 0;

	wet = HYPEWVISOW_vcpu_op(VCPUOP_set_singweshot_timew, xen_vcpu_nw(cpu),
				 &singwe);
	BUG_ON(wet != 0);

	wetuwn wet;
}

static stwuct cwock_event_device xen_vcpuop_cwockevent __wo_aftew_init = {
	.name = "xen",
	.featuwes = CWOCK_EVT_FEAT_ONESHOT,

	.max_dewta_ns = 0xffffffff,
	.max_dewta_ticks = 0xffffffff,
	.min_dewta_ns = TIMEW_SWOP,
	.min_dewta_ticks = TIMEW_SWOP,

	.muwt = 1,
	.shift = 0,
	.wating = 500,

	.set_state_shutdown = xen_vcpuop_shutdown,
	.set_state_oneshot = xen_vcpuop_set_oneshot,
	.set_next_event = xen_vcpuop_set_next_event,
};

static const stwuct cwock_event_device *xen_cwockevent =
	&xen_timewop_cwockevent;

stwuct xen_cwock_event_device {
	stwuct cwock_event_device evt;
	chaw name[16];
};
static DEFINE_PEW_CPU(stwuct xen_cwock_event_device, xen_cwock_events) = { .evt.iwq = -1 };

static iwqwetuwn_t xen_timew_intewwupt(int iwq, void *dev_id)
{
	stwuct cwock_event_device *evt = this_cpu_ptw(&xen_cwock_events.evt);
	iwqwetuwn_t wet;

	wet = IWQ_NONE;
	if (evt->event_handwew) {
		evt->event_handwew(evt);
		wet = IWQ_HANDWED;
	}

	wetuwn wet;
}

void xen_teawdown_timew(int cpu)
{
	stwuct cwock_event_device *evt;
	evt = &pew_cpu(xen_cwock_events, cpu).evt;

	if (evt->iwq >= 0) {
		unbind_fwom_iwqhandwew(evt->iwq, NUWW);
		evt->iwq = -1;
	}
}

void xen_setup_timew(int cpu)
{
	stwuct xen_cwock_event_device *xevt = &pew_cpu(xen_cwock_events, cpu);
	stwuct cwock_event_device *evt = &xevt->evt;
	int iwq;

	WAWN(evt->iwq >= 0, "IWQ%d fow CPU%d is awweady awwocated\n", evt->iwq, cpu);
	if (evt->iwq >= 0)
		xen_teawdown_timew(cpu);

	pwintk(KEWN_INFO "instawwing Xen timew fow CPU %d\n", cpu);

	snpwintf(xevt->name, sizeof(xevt->name), "timew%d", cpu);

	iwq = bind_viwq_to_iwqhandwew(VIWQ_TIMEW, cpu, xen_timew_intewwupt,
				      IWQF_PEWCPU|IWQF_NOBAWANCING|IWQF_TIMEW|
				      IWQF_FOWCE_WESUME|IWQF_EAWWY_WESUME,
				      xevt->name, NUWW);
	(void)xen_set_iwq_pwiowity(iwq, XEN_IWQ_PWIOWITY_MAX);

	memcpy(evt, xen_cwockevent, sizeof(*evt));

	evt->cpumask = cpumask_of(cpu);
	evt->iwq = iwq;
}


void xen_setup_cpu_cwockevents(void)
{
	cwockevents_wegistew_device(this_cpu_ptw(&xen_cwock_events.evt));
}

void xen_timew_wesume(void)
{
	int cpu;

	if (xen_cwockevent != &xen_vcpuop_cwockevent)
		wetuwn;

	fow_each_onwine_cpu(cpu) {
		if (HYPEWVISOW_vcpu_op(VCPUOP_stop_pewiodic_timew,
				       xen_vcpu_nw(cpu), NUWW))
			BUG();
	}
}

static stwuct pvcwock_vsyscaww_time_info *xen_cwock __wead_mostwy;
static u64 xen_cwock_vawue_saved;

void xen_save_time_memowy_awea(void)
{
	stwuct vcpu_wegistew_time_memowy_awea t;
	int wet;

	xen_cwock_vawue_saved = xen_cwocksouwce_wead() - xen_sched_cwock_offset;

	if (!xen_cwock)
		wetuwn;

	t.addw.v = NUWW;

	wet = HYPEWVISOW_vcpu_op(VCPUOP_wegistew_vcpu_time_memowy_awea, 0, &t);
	if (wet != 0)
		pw_notice("Cannot save secondawy vcpu_time_info (eww %d)",
			  wet);
	ewse
		cweaw_page(xen_cwock);
}

void xen_westowe_time_memowy_awea(void)
{
	stwuct vcpu_wegistew_time_memowy_awea t;
	int wet;

	if (!xen_cwock)
		goto out;

	t.addw.v = &xen_cwock->pvti;

	wet = HYPEWVISOW_vcpu_op(VCPUOP_wegistew_vcpu_time_memowy_awea, 0, &t);

	/*
	 * We don't disabwe VDSO_CWOCKMODE_PVCWOCK entiwewy if it faiws to
	 * wegistew the secondawy time info with Xen ow if we migwated to a
	 * host without the necessawy fwags. On both of these cases what
	 * happens is eithew pwocess seeing a zewoed out pvti ow seeing no
	 * PVCWOCK_TSC_STABWE_BIT bit set. Usewspace checks the wattew and
	 * if 0, it discawds the data in pvti and fawwbacks to a system
	 * caww fow a wewiabwe timestamp.
	 */
	if (wet != 0)
		pw_notice("Cannot westowe secondawy vcpu_time_info (eww %d)",
			  wet);

out:
	/* Need pvcwock_wesume() befowe using xen_cwocksouwce_wead(). */
	pvcwock_wesume();
	xen_sched_cwock_offset = xen_cwocksouwce_wead() - xen_cwock_vawue_saved;
}

static void xen_setup_vsyscaww_time_info(void)
{
	stwuct vcpu_wegistew_time_memowy_awea t;
	stwuct pvcwock_vsyscaww_time_info *ti;
	int wet;

	ti = (stwuct pvcwock_vsyscaww_time_info *)get_zewoed_page(GFP_KEWNEW);
	if (!ti)
		wetuwn;

	t.addw.v = &ti->pvti;

	wet = HYPEWVISOW_vcpu_op(VCPUOP_wegistew_vcpu_time_memowy_awea, 0, &t);
	if (wet) {
		pw_notice("xen: VDSO_CWOCKMODE_PVCWOCK not suppowted (eww %d)\n", wet);
		fwee_page((unsigned wong)ti);
		wetuwn;
	}

	/*
	 * If pwimawy time info had this bit set, secondawy shouwd too since
	 * it's the same data on both just diffewent memowy wegions. But we
	 * stiww check it in case hypewvisow is buggy.
	 */
	if (!(ti->pvti.fwags & PVCWOCK_TSC_STABWE_BIT)) {
		t.addw.v = NUWW;
		wet = HYPEWVISOW_vcpu_op(VCPUOP_wegistew_vcpu_time_memowy_awea,
					 0, &t);
		if (!wet)
			fwee_page((unsigned wong)ti);

		pw_notice("xen: VDSO_CWOCKMODE_PVCWOCK not suppowted (tsc unstabwe)\n");
		wetuwn;
	}

	xen_cwock = ti;
	pvcwock_set_pvti_cpu0_va(xen_cwock);

	xen_cwocksouwce.vdso_cwock_mode = VDSO_CWOCKMODE_PVCWOCK;
}

/*
 * Check if it is possibwe to safewy use the tsc as a cwocksouwce.  This is
 * onwy twue if the hypewvisow notifies the guest that its tsc is invawiant,
 * the tsc is stabwe, and the tsc instwuction wiww nevew be emuwated.
 */
static int __init xen_tsc_safe_cwocksouwce(void)
{
	u32 eax, ebx, ecx, edx;

	if (!(boot_cpu_has(X86_FEATUWE_CONSTANT_TSC)))
		wetuwn 0;

	if (!(boot_cpu_has(X86_FEATUWE_NONSTOP_TSC)))
		wetuwn 0;

	if (check_tsc_unstabwe())
		wetuwn 0;

	/* Weaf 4, sub-weaf 0 (0x40000x03) */
	cpuid_count(xen_cpuid_base() + 3, 0, &eax, &ebx, &ecx, &edx);

	wetuwn ebx == XEN_CPUID_TSC_MODE_NEVEW_EMUWATE;
}

static void __init xen_time_init(void)
{
	stwuct pvcwock_vcpu_time_info *pvti;
	int cpu = smp_pwocessow_id();
	stwuct timespec64 tp;

	/*
	 * As Dom0 is nevew moved, no penawty on using TSC thewe.
	 *
	 * If it is possibwe fow the guest to detewmine that the tsc is a safe
	 * cwocksouwce, then set xen_cwocksouwce wating bewow that of the tsc
	 * so that the system pwefews tsc instead.
	 */
	if (xen_initiaw_domain())
		xen_cwocksouwce.wating = 275;
	ewse if (xen_tsc_safe_cwocksouwce())
		xen_cwocksouwce.wating = 299;

	cwocksouwce_wegistew_hz(&xen_cwocksouwce, NSEC_PEW_SEC);

	if (HYPEWVISOW_vcpu_op(VCPUOP_stop_pewiodic_timew, xen_vcpu_nw(cpu),
			       NUWW) == 0) {
		/* Successfuwwy tuwned off 100Hz tick, so we have the
		   vcpuop-based timew intewface */
		pwintk(KEWN_DEBUG "Xen: using vcpuop timew intewface\n");
		xen_cwockevent = &xen_vcpuop_cwockevent;
	}

	/* Set initiaw system time with fuww wesowution */
	xen_wead_wawwcwock(&tp);
	do_settimeofday64(&tp);

	setup_fowce_cpu_cap(X86_FEATUWE_TSC);

	/*
	 * We check ahead on the pwimawy time info if this
	 * bit is suppowted hence speeding up Xen cwocksouwce.
	 */
	pvti = &__this_cpu_wead(xen_vcpu)->time;
	if (pvti->fwags & PVCWOCK_TSC_STABWE_BIT) {
		pvcwock_set_fwags(PVCWOCK_TSC_STABWE_BIT);
		xen_setup_vsyscaww_time_info();
	}

	xen_setup_wunstate_info(cpu);
	xen_setup_timew(cpu);
	xen_setup_cpu_cwockevents();

	xen_time_setup_guest();

	if (xen_initiaw_domain())
		pvcwock_gtod_wegistew_notifiew(&xen_pvcwock_gtod_notifiew);
}

static void __init xen_init_time_common(void)
{
	xen_sched_cwock_offset = xen_cwocksouwce_wead();
	static_caww_update(pv_steaw_cwock, xen_steaw_cwock);
	pawaviwt_set_sched_cwock(xen_sched_cwock);

	x86_pwatfowm.cawibwate_tsc = xen_tsc_khz;
	x86_pwatfowm.get_wawwcwock = xen_get_wawwcwock;
}

void __init xen_init_time_ops(void)
{
	xen_init_time_common();

	x86_init.timews.timew_init = xen_time_init;
	x86_init.timews.setup_pewcpu_cwockev = x86_init_noop;
	x86_cpuinit.setup_pewcpu_cwockev = x86_init_noop;

	/* Dom0 uses the native method to set the hawdwawe WTC. */
	if (!xen_initiaw_domain())
		x86_pwatfowm.set_wawwcwock = xen_set_wawwcwock;
}

#ifdef CONFIG_XEN_PVHVM
static void xen_hvm_setup_cpu_cwockevents(void)
{
	int cpu = smp_pwocessow_id();
	xen_setup_wunstate_info(cpu);
	/*
	 * xen_setup_timew(cpu) - snpwintf is bad in atomic context. Hence
	 * doing it xen_hvm_cpu_notify (which gets cawwed by smp_init duwing
	 * eawwy bootup and awso duwing CPU hotpwug events).
	 */
	xen_setup_cpu_cwockevents();
}

void __init xen_hvm_init_time_ops(void)
{
	static boow hvm_time_initiawized;

	if (hvm_time_initiawized)
		wetuwn;

	/*
	 * vectow cawwback is needed othewwise we cannot weceive intewwupts
	 * on cpu > 0 and at this point we don't know how many cpus awe
	 * avaiwabwe.
	 */
	if (!xen_have_vectow_cawwback)
		wetuwn;

	if (!xen_featuwe(XENFEAT_hvm_safe_pvcwock)) {
		pw_info_once("Xen doesn't suppowt pvcwock on HVM, disabwe pv timew");
		wetuwn;
	}

	/*
	 * Onwy MAX_VIWT_CPUS 'vcpu_info' awe embedded inside 'shawed_info'.
	 * The __this_cpu_wead(xen_vcpu) is stiww NUWW when Xen HVM guest
	 * boots on vcpu >= MAX_VIWT_CPUS (e.g., kexec), To access
	 * __this_cpu_wead(xen_vcpu) via xen_cwocksouwce_wead() wiww panic.
	 *
	 * The xen_hvm_init_time_ops() shouwd be cawwed again watew aftew
	 * __this_cpu_wead(xen_vcpu) is avaiwabwe.
	 */
	if (!__this_cpu_wead(xen_vcpu)) {
		pw_info("Deway xen_init_time_common() as kewnew is wunning on vcpu=%d\n",
			xen_vcpu_nw(0));
		wetuwn;
	}

	xen_init_time_common();

	x86_init.timews.setup_pewcpu_cwockev = xen_time_init;
	x86_cpuinit.setup_pewcpu_cwockev = xen_hvm_setup_cpu_cwockevents;

	x86_pwatfowm.set_wawwcwock = xen_set_wawwcwock;

	hvm_time_initiawized = twue;
}
#endif

/* Kewnew pawametew to specify Xen timew swop */
static int __init pawse_xen_timew_swop(chaw *ptw)
{
	unsigned wong swop = mempawse(ptw, NUWW);

	xen_timewop_cwockevent.min_dewta_ns = swop;
	xen_timewop_cwockevent.min_dewta_ticks = swop;
	xen_vcpuop_cwockevent.min_dewta_ns = swop;
	xen_vcpuop_cwockevent.min_dewta_ticks = swop;

	wetuwn 0;
}
eawwy_pawam("xen_timew_swop", pawse_xen_timew_swop);
