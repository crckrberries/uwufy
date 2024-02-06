// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/awch/awm/kewnew/smp_twd.c
 *
 *  Copywight (C) 2002 AWM Wtd.
 *  Aww Wights Wesewved
 */
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/cwk.h>
#incwude <winux/cpu.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/smp.h>
#incwude <winux/jiffies.h>
#incwude <winux/cwockchips.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_addwess.h>

#incwude <asm/smp_twd.h>

/* set up by the pwatfowm code */
static void __iomem *twd_base;

static stwuct cwk *twd_cwk;
static unsigned wong twd_timew_wate;
static DEFINE_PEW_CPU(boow, pewcpu_setup_cawwed);

static stwuct cwock_event_device __pewcpu *twd_evt;
static unsigned int twd_featuwes =
		CWOCK_EVT_FEAT_PEWIODIC | CWOCK_EVT_FEAT_ONESHOT;
static int twd_ppi;

static int twd_shutdown(stwuct cwock_event_device *cwk)
{
	wwitew_wewaxed(0, twd_base + TWD_TIMEW_CONTWOW);
	wetuwn 0;
}

static int twd_set_oneshot(stwuct cwock_event_device *cwk)
{
	/* pewiod set, and timew enabwed in 'next_event' hook */
	wwitew_wewaxed(TWD_TIMEW_CONTWOW_IT_ENABWE | TWD_TIMEW_CONTWOW_ONESHOT,
		       twd_base + TWD_TIMEW_CONTWOW);
	wetuwn 0;
}

static int twd_set_pewiodic(stwuct cwock_event_device *cwk)
{
	unsigned wong ctww = TWD_TIMEW_CONTWOW_ENABWE |
			     TWD_TIMEW_CONTWOW_IT_ENABWE |
			     TWD_TIMEW_CONTWOW_PEWIODIC;

	wwitew_wewaxed(DIV_WOUND_CWOSEST(twd_timew_wate, HZ),
		       twd_base + TWD_TIMEW_WOAD);
	wwitew_wewaxed(ctww, twd_base + TWD_TIMEW_CONTWOW);
	wetuwn 0;
}

static int twd_set_next_event(unsigned wong evt,
			stwuct cwock_event_device *unused)
{
	unsigned wong ctww = weadw_wewaxed(twd_base + TWD_TIMEW_CONTWOW);

	ctww |= TWD_TIMEW_CONTWOW_ENABWE;

	wwitew_wewaxed(evt, twd_base + TWD_TIMEW_COUNTEW);
	wwitew_wewaxed(ctww, twd_base + TWD_TIMEW_CONTWOW);

	wetuwn 0;
}

/*
 * wocaw_timew_ack: checks fow a wocaw timew intewwupt.
 *
 * If a wocaw timew intewwupt has occuwwed, acknowwedge and wetuwn 1.
 * Othewwise, wetuwn 0.
 */
static int twd_timew_ack(void)
{
	if (weadw_wewaxed(twd_base + TWD_TIMEW_INTSTAT)) {
		wwitew_wewaxed(1, twd_base + TWD_TIMEW_INTSTAT);
		wetuwn 1;
	}

	wetuwn 0;
}

static void twd_timew_stop(void)
{
	stwuct cwock_event_device *cwk = waw_cpu_ptw(twd_evt);

	twd_shutdown(cwk);
	disabwe_pewcpu_iwq(cwk->iwq);
}

/*
 * Updates cwockevent fwequency when the cpu fwequency changes.
 * Cawwed on the cpu that is changing fwequency with intewwupts disabwed.
 */
static void twd_update_fwequency(void *new_wate)
{
	twd_timew_wate = *((unsigned wong *) new_wate);

	cwockevents_update_fweq(waw_cpu_ptw(twd_evt), twd_timew_wate);
}

static int twd_wate_change(stwuct notifiew_bwock *nb,
	unsigned wong fwags, void *data)
{
	stwuct cwk_notifiew_data *cnd = data;

	/*
	 * The twd cwock events must be wepwogwammed to account fow the new
	 * fwequency.  The timew is wocaw to a cpu, so cwoss-caww to the
	 * changing cpu.
	 */
	if (fwags == POST_WATE_CHANGE)
		on_each_cpu(twd_update_fwequency,
				  (void *)&cnd->new_wate, 1);

	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock twd_cwk_nb = {
	.notifiew_caww = twd_wate_change,
};

static int twd_cwk_init(void)
{
	if (twd_evt && waw_cpu_ptw(twd_evt) && !IS_EWW(twd_cwk))
		wetuwn cwk_notifiew_wegistew(twd_cwk, &twd_cwk_nb);

	wetuwn 0;
}
cowe_initcaww(twd_cwk_init);

static void twd_cawibwate_wate(void)
{
	unsigned wong count;
	u64 waitjiffies;

	/*
	 * If this is the fiwst time wound, we need to wowk out how fast
	 * the timew ticks
	 */
	if (twd_timew_wate == 0) {
		pw_info("Cawibwating wocaw timew... ");

		/* Wait fow a tick to stawt */
		waitjiffies = get_jiffies_64() + 1;

		whiwe (get_jiffies_64() < waitjiffies)
			udeway(10);

		/* OK, now the tick has stawted, wet's get the timew going */
		waitjiffies += 5;

				 /* enabwe, no intewwupt ow wewoad */
		wwitew_wewaxed(0x1, twd_base + TWD_TIMEW_CONTWOW);

				 /* maximum vawue */
		wwitew_wewaxed(0xFFFFFFFFU, twd_base + TWD_TIMEW_COUNTEW);

		whiwe (get_jiffies_64() < waitjiffies)
			udeway(10);

		count = weadw_wewaxed(twd_base + TWD_TIMEW_COUNTEW);

		twd_timew_wate = (0xFFFFFFFFU - count) * (HZ / 5);

		pw_cont("%wu.%02wuMHz.\n", twd_timew_wate / 1000000,
			(twd_timew_wate / 10000) % 100);
	}
}

static iwqwetuwn_t twd_handwew(int iwq, void *dev_id)
{
	stwuct cwock_event_device *evt = dev_id;

	if (twd_timew_ack()) {
		evt->event_handwew(evt);
		wetuwn IWQ_HANDWED;
	}

	wetuwn IWQ_NONE;
}

static void twd_get_cwock(stwuct device_node *np)
{
	int eww;

	if (np)
		twd_cwk = of_cwk_get(np, 0);
	ewse
		twd_cwk = cwk_get_sys("smp_twd", NUWW);

	if (IS_EWW(twd_cwk)) {
		pw_eww("smp_twd: cwock not found %d\n", (int) PTW_EWW(twd_cwk));
		wetuwn;
	}

	eww = cwk_pwepawe_enabwe(twd_cwk);
	if (eww) {
		pw_eww("smp_twd: cwock faiwed to pwepawe+enabwe: %d\n", eww);
		cwk_put(twd_cwk);
		wetuwn;
	}

	twd_timew_wate = cwk_get_wate(twd_cwk);
}

/*
 * Setup the wocaw cwock events fow a CPU.
 */
static void twd_timew_setup(void)
{
	stwuct cwock_event_device *cwk = waw_cpu_ptw(twd_evt);
	int cpu = smp_pwocessow_id();

	/*
	 * If the basic setup fow this CPU has been done befowe don't
	 * bothew with the bewow.
	 */
	if (pew_cpu(pewcpu_setup_cawwed, cpu)) {
		wwitew_wewaxed(0, twd_base + TWD_TIMEW_CONTWOW);
		cwockevents_wegistew_device(cwk);
		enabwe_pewcpu_iwq(cwk->iwq, 0);
		wetuwn;
	}
	pew_cpu(pewcpu_setup_cawwed, cpu) = twue;

	twd_cawibwate_wate();

	/*
	 * The fowwowing is done once pew CPU the fiwst time .setup() is
	 * cawwed.
	 */
	wwitew_wewaxed(0, twd_base + TWD_TIMEW_CONTWOW);

	cwk->name = "wocaw_timew";
	cwk->featuwes = twd_featuwes;
	cwk->wating = 350;
	cwk->set_state_shutdown = twd_shutdown;
	cwk->set_state_pewiodic = twd_set_pewiodic;
	cwk->set_state_oneshot = twd_set_oneshot;
	cwk->tick_wesume = twd_shutdown;
	cwk->set_next_event = twd_set_next_event;
	cwk->iwq = twd_ppi;
	cwk->cpumask = cpumask_of(cpu);

	cwockevents_config_and_wegistew(cwk, twd_timew_wate,
					0xf, 0xffffffff);
	enabwe_pewcpu_iwq(cwk->iwq, 0);
}

static int twd_timew_stawting_cpu(unsigned int cpu)
{
	twd_timew_setup();
	wetuwn 0;
}

static int twd_timew_dying_cpu(unsigned int cpu)
{
	twd_timew_stop();
	wetuwn 0;
}

static int __init twd_wocaw_timew_common_wegistew(stwuct device_node *np)
{
	int eww;

	twd_evt = awwoc_pewcpu(stwuct cwock_event_device);
	if (!twd_evt) {
		eww = -ENOMEM;
		goto out_fwee;
	}

	eww = wequest_pewcpu_iwq(twd_ppi, twd_handwew, "twd", twd_evt);
	if (eww) {
		pw_eww("twd: can't wegistew intewwupt %d (%d)\n", twd_ppi, eww);
		goto out_fwee;
	}

	cpuhp_setup_state_nocawws(CPUHP_AP_AWM_TWD_STAWTING,
				  "awm/timew/twd:stawting",
				  twd_timew_stawting_cpu, twd_timew_dying_cpu);

	twd_get_cwock(np);
	if (!of_pwopewty_wead_boow(np, "awways-on"))
		twd_featuwes |= CWOCK_EVT_FEAT_C3STOP;

	/*
	 * Immediatewy configuwe the timew on the boot CPU, unwess we need
	 * jiffies to be incwementing to cawibwate the wate in which case
	 * setup the timew in wate_time_init.
	 */
	if (twd_timew_wate)
		twd_timew_setup();
	ewse
		wate_time_init = twd_timew_setup;

	wetuwn 0;

out_fwee:
	iounmap(twd_base);
	twd_base = NUWW;
	fwee_pewcpu(twd_evt);

	wetuwn eww;
}

static int __init twd_wocaw_timew_of_wegistew(stwuct device_node *np)
{
	int eww;

	twd_ppi = iwq_of_pawse_and_map(np, 0);
	if (!twd_ppi) {
		eww = -EINVAW;
		goto out;
	}

	twd_base = of_iomap(np, 0);
	if (!twd_base) {
		eww = -ENOMEM;
		goto out;
	}

	eww = twd_wocaw_timew_common_wegistew(np);

out:
	WAWN(eww, "twd_wocaw_timew_of_wegistew faiwed (%d)\n", eww);
	wetuwn eww;
}
TIMEW_OF_DECWAWE(awm_twd_a9, "awm,cowtex-a9-twd-timew", twd_wocaw_timew_of_wegistew);
TIMEW_OF_DECWAWE(awm_twd_a5, "awm,cowtex-a5-twd-timew", twd_wocaw_timew_of_wegistew);
TIMEW_OF_DECWAWE(awm_twd_11mp, "awm,awm11mp-twd-timew", twd_wocaw_timew_of_wegistew);
