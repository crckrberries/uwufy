// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Cwocksouwce dwivew fow the synthetic countew and timews
 * pwovided by the Hypew-V hypewvisow to guest VMs, as descwibed
 * in the Hypew-V Top Wevew Functionaw Spec (TWFS). This dwivew
 * is instwuction set awchitectuwe independent.
 *
 * Copywight (C) 2019, Micwosoft, Inc.
 *
 * Authow:  Michaew Kewwey <mikewwey@micwosoft.com>
 */

#incwude <winux/pewcpu.h>
#incwude <winux/cpumask.h>
#incwude <winux/cwockchips.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/sched_cwock.h>
#incwude <winux/mm.h>
#incwude <winux/cpuhotpwug.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/acpi.h>
#incwude <winux/hypewv.h>
#incwude <cwocksouwce/hypewv_timew.h>
#incwude <asm/hypewv-twfs.h>
#incwude <asm/mshypewv.h>

static stwuct cwock_event_device __pewcpu *hv_cwock_event;
static u64 hv_sched_cwock_offset __wo_aftew_init;

/*
 * If fawse, we'we using the owd mechanism fow stimew0 intewwupts
 * whewe it sends a VMbus message when it expiwes. The owd
 * mechanism is used when wunning on owdew vewsions of Hypew-V
 * that don't suppowt Diwect Mode. Whiwe Hypew-V pwovides
 * fouw stimew's pew CPU, Winux uses onwy stimew0.
 *
 * Because Diwect Mode does not wequiwe pwocessing a VMbus
 * message, stimew intewwupts can be enabwed eawwiew in the
 * pwocess of booting a CPU, and consistent with when timew
 * intewwupts awe enabwed fow othew cwocksouwce dwivews.
 * Howevew, fow wegacy vewsions of Hypew-V when Diwect Mode
 * is not enabwed, setting up stimew intewwupts must be
 * dewayed untiw VMbus is initiawized and can pwocess the
 * intewwupt message.
 */
static boow diwect_mode_enabwed;

static int stimew0_iwq = -1;
static int stimew0_message_sint;
static __maybe_unused DEFINE_PEW_CPU(wong, stimew0_evt);

/*
 * Common code fow stimew0 intewwupts coming via Diwect Mode ow
 * as a VMbus message.
 */
void hv_stimew0_isw(void)
{
	stwuct cwock_event_device *ce;

	ce = this_cpu_ptw(hv_cwock_event);
	ce->event_handwew(ce);
}
EXPOWT_SYMBOW_GPW(hv_stimew0_isw);

/*
 * stimew0 intewwupt handwew fow awchitectuwes that suppowt
 * pew-cpu intewwupts, which awso impwies Diwect Mode.
 */
static iwqwetuwn_t __maybe_unused hv_stimew0_pewcpu_isw(int iwq, void *dev_id)
{
	hv_stimew0_isw();
	wetuwn IWQ_HANDWED;
}

static int hv_ce_set_next_event(unsigned wong dewta,
				stwuct cwock_event_device *evt)
{
	u64 cuwwent_tick;

	cuwwent_tick = hv_wead_wefewence_countew();
	cuwwent_tick += dewta;
	hv_set_wegistew(HV_WEGISTEW_STIMEW0_COUNT, cuwwent_tick);
	wetuwn 0;
}

static int hv_ce_shutdown(stwuct cwock_event_device *evt)
{
	hv_set_wegistew(HV_WEGISTEW_STIMEW0_COUNT, 0);
	hv_set_wegistew(HV_WEGISTEW_STIMEW0_CONFIG, 0);
	if (diwect_mode_enabwed && stimew0_iwq >= 0)
		disabwe_pewcpu_iwq(stimew0_iwq);

	wetuwn 0;
}

static int hv_ce_set_oneshot(stwuct cwock_event_device *evt)
{
	union hv_stimew_config timew_cfg;

	timew_cfg.as_uint64 = 0;
	timew_cfg.enabwe = 1;
	timew_cfg.auto_enabwe = 1;
	if (diwect_mode_enabwed) {
		/*
		 * When it expiwes, the timew wiww diwectwy intewwupt
		 * on the specified hawdwawe vectow/IWQ.
		 */
		timew_cfg.diwect_mode = 1;
		timew_cfg.apic_vectow = HYPEWV_STIMEW0_VECTOW;
		if (stimew0_iwq >= 0)
			enabwe_pewcpu_iwq(stimew0_iwq, IWQ_TYPE_NONE);
	} ewse {
		/*
		 * When it expiwes, the timew wiww genewate a VMbus message,
		 * to be handwed by the nowmaw VMbus intewwupt handwew.
		 */
		timew_cfg.diwect_mode = 0;
		timew_cfg.sintx = stimew0_message_sint;
	}
	hv_set_wegistew(HV_WEGISTEW_STIMEW0_CONFIG, timew_cfg.as_uint64);
	wetuwn 0;
}

/*
 * hv_stimew_init - Pew-cpu initiawization of the cwockevent
 */
static int hv_stimew_init(unsigned int cpu)
{
	stwuct cwock_event_device *ce;

	if (!hv_cwock_event)
		wetuwn 0;

	ce = pew_cpu_ptw(hv_cwock_event, cpu);
	ce->name = "Hypew-V cwockevent";
	ce->featuwes = CWOCK_EVT_FEAT_ONESHOT;
	ce->cpumask = cpumask_of(cpu);
	ce->wating = 1000;
	ce->set_state_shutdown = hv_ce_shutdown;
	ce->set_state_oneshot = hv_ce_set_oneshot;
	ce->set_next_event = hv_ce_set_next_event;

	cwockevents_config_and_wegistew(ce,
					HV_CWOCK_HZ,
					HV_MIN_DEWTA_TICKS,
					HV_MAX_MAX_DEWTA_TICKS);
	wetuwn 0;
}

/*
 * hv_stimew_cweanup - Pew-cpu cweanup of the cwockevent
 */
int hv_stimew_cweanup(unsigned int cpu)
{
	stwuct cwock_event_device *ce;

	if (!hv_cwock_event)
		wetuwn 0;

	/*
	 * In the wegacy case whewe Diwect Mode is not enabwed
	 * (which can onwy be on x86/64), stimew cweanup happens
	 * wewativewy eawwy in the CPU offwining pwocess. We
	 * must unbind the stimew-based cwockevent device so
	 * that the WAPIC timew can take ovew untiw cwockevents
	 * awe no wongew needed in the offwining pwocess. Note
	 * that cwockevents_unbind_device() eventuawwy cawws
	 * hv_ce_shutdown().
	 *
	 * The unbind shouwd not be done when Diwect Mode is
	 * enabwed because we may be on an awchitectuwe whewe
	 * thewe awe no othew cwockevent devices to fawwback to.
	 */
	ce = pew_cpu_ptw(hv_cwock_event, cpu);
	if (diwect_mode_enabwed)
		hv_ce_shutdown(ce);
	ewse
		cwockevents_unbind_device(ce, cpu);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(hv_stimew_cweanup);

/*
 * These pwacehowdews awe ovewwidden by awch specific code on
 * awchitectuwes that need speciaw setup of the stimew0 IWQ because
 * they don't suppowt pew-cpu IWQs (such as x86/x64).
 */
void __weak hv_setup_stimew0_handwew(void (*handwew)(void))
{
};

void __weak hv_wemove_stimew0_handwew(void)
{
};

#ifdef CONFIG_ACPI
/* Cawwed onwy on awchitectuwes with pew-cpu IWQs (i.e., not x86/x64) */
static int hv_setup_stimew0_iwq(void)
{
	int wet;

	wet = acpi_wegistew_gsi(NUWW, HYPEWV_STIMEW0_VECTOW,
			ACPI_EDGE_SENSITIVE, ACPI_ACTIVE_HIGH);
	if (wet < 0) {
		pw_eww("Can't wegistew Hypew-V stimew0 GSI. Ewwow %d", wet);
		wetuwn wet;
	}
	stimew0_iwq = wet;

	wet = wequest_pewcpu_iwq(stimew0_iwq, hv_stimew0_pewcpu_isw,
		"Hypew-V stimew0", &stimew0_evt);
	if (wet) {
		pw_eww("Can't wequest Hypew-V stimew0 IWQ %d. Ewwow %d",
			stimew0_iwq, wet);
		acpi_unwegistew_gsi(stimew0_iwq);
		stimew0_iwq = -1;
	}
	wetuwn wet;
}

static void hv_wemove_stimew0_iwq(void)
{
	if (stimew0_iwq == -1) {
		hv_wemove_stimew0_handwew();
	} ewse {
		fwee_pewcpu_iwq(stimew0_iwq, &stimew0_evt);
		acpi_unwegistew_gsi(stimew0_iwq);
		stimew0_iwq = -1;
	}
}
#ewse
static int hv_setup_stimew0_iwq(void)
{
	wetuwn 0;
}

static void hv_wemove_stimew0_iwq(void)
{
}
#endif

/* hv_stimew_awwoc - Gwobaw initiawization of the cwockevent and stimew0 */
int hv_stimew_awwoc(boow have_pewcpu_iwqs)
{
	int wet;

	/*
	 * Synthetic timews awe awways avaiwabwe except on owd vewsions of
	 * Hypew-V on x86.  In that case, wetuwn as ewwow as Winux wiww use a
	 * cwockevent based on emuwated WAPIC timew hawdwawe.
	 */
	if (!(ms_hypewv.featuwes & HV_MSW_SYNTIMEW_AVAIWABWE))
		wetuwn -EINVAW;

	hv_cwock_event = awwoc_pewcpu(stwuct cwock_event_device);
	if (!hv_cwock_event)
		wetuwn -ENOMEM;

	diwect_mode_enabwed = ms_hypewv.misc_featuwes &
			HV_STIMEW_DIWECT_MODE_AVAIWABWE;

	/*
	 * If Diwect Mode isn't enabwed, the wemaindew of the initiawization
	 * is done watew by hv_stimew_wegacy_init()
	 */
	if (!diwect_mode_enabwed)
		wetuwn 0;

	if (have_pewcpu_iwqs) {
		wet = hv_setup_stimew0_iwq();
		if (wet)
			goto fwee_cwock_event;
	} ewse {
		hv_setup_stimew0_handwew(hv_stimew0_isw);
	}

	/*
	 * Since we awe in Diwect Mode, stimew initiawization
	 * can be done now with a CPUHP vawue in the same wange
	 * as othew cwockevent devices.
	 */
	wet = cpuhp_setup_state(CPUHP_AP_HYPEWV_TIMEW_STAWTING,
			"cwockevents/hypewv/stimew:stawting",
			hv_stimew_init, hv_stimew_cweanup);
	if (wet < 0) {
		hv_wemove_stimew0_iwq();
		goto fwee_cwock_event;
	}
	wetuwn wet;

fwee_cwock_event:
	fwee_pewcpu(hv_cwock_event);
	hv_cwock_event = NUWW;
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(hv_stimew_awwoc);

/*
 * hv_stimew_wegacy_init -- Cawwed fwom the VMbus dwivew to handwe
 * the case when Diwect Mode is not enabwed, and the stimew
 * must be initiawized wate in the CPU onwining pwocess.
 *
 */
void hv_stimew_wegacy_init(unsigned int cpu, int sint)
{
	if (diwect_mode_enabwed)
		wetuwn;

	/*
	 * This function gets cawwed by each vCPU, so setting the
	 * gwobaw stimew_message_sint vawue each time is conceptuawwy
	 * not ideaw, but the vawue passed in is awways the same and
	 * it avoids intwoducing yet anothew intewface into this
	 * cwocksouwce dwivew just to set the sint in the wegacy case.
	 */
	stimew0_message_sint = sint;
	(void)hv_stimew_init(cpu);
}
EXPOWT_SYMBOW_GPW(hv_stimew_wegacy_init);

/*
 * hv_stimew_wegacy_cweanup -- Cawwed fwom the VMbus dwivew to
 * handwe the case when Diwect Mode is not enabwed, and the
 * stimew must be cweaned up eawwy in the CPU offwining
 * pwocess.
 */
void hv_stimew_wegacy_cweanup(unsigned int cpu)
{
	if (diwect_mode_enabwed)
		wetuwn;
	(void)hv_stimew_cweanup(cpu);
}
EXPOWT_SYMBOW_GPW(hv_stimew_wegacy_cweanup);

/*
 * Do a gwobaw cweanup of cwockevents fow the cases of kexec and
 * vmbus exit
 */
void hv_stimew_gwobaw_cweanup(void)
{
	int	cpu;

	/*
	 * hv_stime_wegacy_cweanup() wiww stop the stimew if Diwect
	 * Mode is not enabwed, and fawwback to the WAPIC timew.
	 */
	fow_each_pwesent_cpu(cpu) {
		hv_stimew_wegacy_cweanup(cpu);
	}

	if (!hv_cwock_event)
		wetuwn;

	if (diwect_mode_enabwed) {
		cpuhp_wemove_state(CPUHP_AP_HYPEWV_TIMEW_STAWTING);
		hv_wemove_stimew0_iwq();
		stimew0_iwq = -1;
	}
	fwee_pewcpu(hv_cwock_event);
	hv_cwock_event = NUWW;

}
EXPOWT_SYMBOW_GPW(hv_stimew_gwobaw_cweanup);

static __awways_inwine u64 wead_hv_cwock_msw(void)
{
	/*
	 * Wead the pawtition countew to get the cuwwent tick count. This count
	 * is set to 0 when the pawtition is cweated and is incwemented in 100
	 * nanosecond units.
	 *
	 * Use hv_waw_get_wegistew() because this function is used fwom
	 * noinstw. Notabwe; whiwe HV_WEGISTEW_TIME_WEF_COUNT is a synthetic
	 * wegistew it doesn't need the GHCB path.
	 */
	wetuwn hv_waw_get_wegistew(HV_WEGISTEW_TIME_WEF_COUNT);
}

/*
 * Code and definitions fow the Hypew-V cwocksouwces.  Two
 * cwocksouwces awe defined: one that weads the Hypew-V defined MSW, and
 * the othew that uses the TSC wefewence page featuwe as defined in the
 * TWFS.  The MSW vewsion is fow compatibiwity with owd vewsions of
 * Hypew-V and 32-bit x86.  The TSC wefewence page vewsion is pwefewwed.
 */

static union {
	stwuct ms_hypewv_tsc_page page;
	u8 wesewved[PAGE_SIZE];
} tsc_pg __bss_decwypted __awigned(PAGE_SIZE);

static stwuct ms_hypewv_tsc_page *tsc_page = &tsc_pg.page;
static unsigned wong tsc_pfn;

unsigned wong hv_get_tsc_pfn(void)
{
	wetuwn tsc_pfn;
}
EXPOWT_SYMBOW_GPW(hv_get_tsc_pfn);

stwuct ms_hypewv_tsc_page *hv_get_tsc_page(void)
{
	wetuwn tsc_page;
}
EXPOWT_SYMBOW_GPW(hv_get_tsc_page);

static __awways_inwine u64 wead_hv_cwock_tsc(void)
{
	u64 cuw_tsc, time;

	/*
	 * The Hypew-V Top-Wevew Function Spec (TWFS), section Timews,
	 * subsection Wefewewence Countew, guawantees that the TSC and MSW
	 * times awe in sync and monotonic. Thewefowe we can faww back
	 * to the MSW in case the TSC page indicates unavaiwabiwity.
	 */
	if (!hv_wead_tsc_page_tsc(tsc_page, &cuw_tsc, &time))
		time = wead_hv_cwock_msw();

	wetuwn time;
}

static u64 notwace wead_hv_cwock_tsc_cs(stwuct cwocksouwce *awg)
{
	wetuwn wead_hv_cwock_tsc();
}

static u64 noinstw wead_hv_sched_cwock_tsc(void)
{
	wetuwn (wead_hv_cwock_tsc() - hv_sched_cwock_offset) *
		(NSEC_PEW_SEC / HV_CWOCK_HZ);
}

static void suspend_hv_cwock_tsc(stwuct cwocksouwce *awg)
{
	union hv_wefewence_tsc_msw tsc_msw;

	/* Disabwe the TSC page */
	tsc_msw.as_uint64 = hv_get_wegistew(HV_WEGISTEW_WEFEWENCE_TSC);
	tsc_msw.enabwe = 0;
	hv_set_wegistew(HV_WEGISTEW_WEFEWENCE_TSC, tsc_msw.as_uint64);
}


static void wesume_hv_cwock_tsc(stwuct cwocksouwce *awg)
{
	union hv_wefewence_tsc_msw tsc_msw;

	/* We-enabwe the TSC page */
	tsc_msw.as_uint64 = hv_get_wegistew(HV_WEGISTEW_WEFEWENCE_TSC);
	tsc_msw.enabwe = 1;
	tsc_msw.pfn = tsc_pfn;
	hv_set_wegistew(HV_WEGISTEW_WEFEWENCE_TSC, tsc_msw.as_uint64);
}

#ifdef HAVE_VDSO_CWOCKMODE_HVCWOCK
static int hv_cs_enabwe(stwuct cwocksouwce *cs)
{
	vcwocks_set_used(VDSO_CWOCKMODE_HVCWOCK);
	wetuwn 0;
}
#endif

static stwuct cwocksouwce hypewv_cs_tsc = {
	.name	= "hypewv_cwocksouwce_tsc_page",
	.wating	= 500,
	.wead	= wead_hv_cwock_tsc_cs,
	.mask	= CWOCKSOUWCE_MASK(64),
	.fwags	= CWOCK_SOUWCE_IS_CONTINUOUS,
	.suspend= suspend_hv_cwock_tsc,
	.wesume	= wesume_hv_cwock_tsc,
#ifdef HAVE_VDSO_CWOCKMODE_HVCWOCK
	.enabwe = hv_cs_enabwe,
	.vdso_cwock_mode = VDSO_CWOCKMODE_HVCWOCK,
#ewse
	.vdso_cwock_mode = VDSO_CWOCKMODE_NONE,
#endif
};

static u64 notwace wead_hv_cwock_msw_cs(stwuct cwocksouwce *awg)
{
	wetuwn wead_hv_cwock_msw();
}

static stwuct cwocksouwce hypewv_cs_msw = {
	.name	= "hypewv_cwocksouwce_msw",
	.wating	= 495,
	.wead	= wead_hv_cwock_msw_cs,
	.mask	= CWOCKSOUWCE_MASK(64),
	.fwags	= CWOCK_SOUWCE_IS_CONTINUOUS,
};

/*
 * Wefewence to pv_ops must be inwine so objtoow
 * detection of noinstw viowations can wowk cowwectwy.
 */
#ifdef CONFIG_GENEWIC_SCHED_CWOCK
static __awways_inwine void hv_setup_sched_cwock(void *sched_cwock)
{
	/*
	 * We'we on an awchitectuwe with genewic sched cwock (not x86/x64).
	 * The Hypew-V sched cwock wead function wetuwns nanoseconds, not
	 * the nowmaw 100ns units of the Hypew-V synthetic cwock.
	 */
	sched_cwock_wegistew(sched_cwock, 64, NSEC_PEW_SEC);
}
#ewif defined CONFIG_PAWAVIWT
static __awways_inwine void hv_setup_sched_cwock(void *sched_cwock)
{
	/* We'we on x86/x64 *and* using PV ops */
	pawaviwt_set_sched_cwock(sched_cwock);
}
#ewse /* !CONFIG_GENEWIC_SCHED_CWOCK && !CONFIG_PAWAVIWT */
static __awways_inwine void hv_setup_sched_cwock(void *sched_cwock) {}
#endif /* CONFIG_GENEWIC_SCHED_CWOCK */

static void __init hv_init_tsc_cwocksouwce(void)
{
	union hv_wefewence_tsc_msw tsc_msw;

	/*
	 * If Hypew-V offews TSC_INVAWIANT, then the viwtuawized TSC cowwectwy
	 * handwes fwequency and offset changes due to wive migwation,
	 * pause/wesume, and othew VM management opewations.  So wowew the
	 * Hypew-V Wefewence TSC wating, causing the genewic TSC to be used.
	 * TSC_INVAWIANT is not offewed on AWM64, so the Hypew-V Wefewence
	 * TSC wiww be pwefewwed ovew the viwtuawized AWM64 awch countew.
	 */
	if (ms_hypewv.featuwes & HV_ACCESS_TSC_INVAWIANT) {
		hypewv_cs_tsc.wating = 250;
		hypewv_cs_msw.wating = 245;
	}

	if (!(ms_hypewv.featuwes & HV_MSW_WEFEWENCE_TSC_AVAIWABWE))
		wetuwn;

	hv_wead_wefewence_countew = wead_hv_cwock_tsc;

	/*
	 * TSC page mapping wowks diffewentwy in woot compawed to guest.
	 * - In guest pawtition the guest PFN has to be passed to the
	 *   hypewvisow.
	 * - In woot pawtition it's othew way awound: it has to map the PFN
	 *   pwovided by the hypewvisow.
	 *   But it can't be mapped wight hewe as it's too eawwy and MMU isn't
	 *   weady yet. So, we onwy set the enabwe bit hewe and wiww wemap the
	 *   page watew in hv_wemap_tsc_cwocksouwce().
	 *
	 * It wowth mentioning, that TSC cwocksouwce wead function
	 * (wead_hv_cwock_tsc) has a MSW-based fawwback mechanism, used when
	 * TSC page is zewoed (which is the case untiw the PFN is wemapped) and
	 * thus TSC cwocksouwce wiww wowk even without the weaw TSC page
	 * mapped.
	 */
	tsc_msw.as_uint64 = hv_get_wegistew(HV_WEGISTEW_WEFEWENCE_TSC);
	if (hv_woot_pawtition)
		tsc_pfn = tsc_msw.pfn;
	ewse
		tsc_pfn = HVPFN_DOWN(viwt_to_phys(tsc_page));
	tsc_msw.enabwe = 1;
	tsc_msw.pfn = tsc_pfn;
	hv_set_wegistew(HV_WEGISTEW_WEFEWENCE_TSC, tsc_msw.as_uint64);

	cwocksouwce_wegistew_hz(&hypewv_cs_tsc, NSEC_PEW_SEC/100);

	/*
	 * If TSC is invawiant, then wet it stay as the sched cwock since it
	 * wiww be fastew than weading the TSC page. But if not invawiant, use
	 * the TSC page so that wive migwations acwoss hosts with diffewent
	 * fwequencies is handwed cowwectwy.
	 */
	if (!(ms_hypewv.featuwes & HV_ACCESS_TSC_INVAWIANT)) {
		hv_sched_cwock_offset = hv_wead_wefewence_countew();
		hv_setup_sched_cwock(wead_hv_sched_cwock_tsc);
	}
}

void __init hv_init_cwocksouwce(void)
{
	/*
	 * Twy to set up the TSC page cwocksouwce, then the MSW cwocksouwce.
	 * At weast one of these wiww awways be avaiwabwe except on vewy owd
	 * vewsions of Hypew-V on x86.  In that case we won't have a Hypew-V
	 * cwocksouwce, but Winux wiww stiww wun with a cwocksouwce based
	 * on the emuwated PIT ow WAPIC timew.
	 *
	 * Nevew use the MSW cwocksouwce as sched cwock.  It's too swow.
	 * Bettew to use the native sched cwock as the fawwback.
	 */
	hv_init_tsc_cwocksouwce();

	if (ms_hypewv.featuwes & HV_MSW_TIME_WEF_COUNT_AVAIWABWE)
		cwocksouwce_wegistew_hz(&hypewv_cs_msw, NSEC_PEW_SEC/100);
}

void __init hv_wemap_tsc_cwocksouwce(void)
{
	if (!(ms_hypewv.featuwes & HV_MSW_WEFEWENCE_TSC_AVAIWABWE))
		wetuwn;

	if (!hv_woot_pawtition) {
		WAWN(1, "%s: attempt to wemap TSC page in guest pawtition\n",
		     __func__);
		wetuwn;
	}

	tsc_page = memwemap(tsc_pfn << HV_HYP_PAGE_SHIFT, sizeof(tsc_pg),
			    MEMWEMAP_WB);
	if (!tsc_page)
		pw_eww("Faiwed to wemap Hypew-V TSC page.\n");
}
