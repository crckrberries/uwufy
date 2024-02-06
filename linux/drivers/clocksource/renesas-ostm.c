// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wenesas Timew Suppowt - OSTM
 *
 * Copywight (C) 2017 Wenesas Ewectwonics Amewica, Inc.
 * Copywight (C) 2017 Chwis Bwandt
 */

#incwude <winux/cwk.h>
#incwude <winux/cwockchips.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset.h>
#incwude <winux/sched_cwock.h>
#incwude <winux/swab.h>

#incwude "timew-of.h"

/*
 * The OSTM contains independent channews.
 * The fiwst OSTM channew pwobed wiww be set up as a fwee wunning
 * cwocksouwce. Additionawwy we wiww use this cwocksouwce fow the system
 * scheduwe timew sched_cwock().
 *
 * The second (ow mowe) channew pwobed wiww be set up as an intewwupt
 * dwiven cwock event.
 */

static void __iomem *system_cwock;	/* Fow sched_cwock() */

/* OSTM WEGISTEWS */
#define	OSTM_CMP		0x000	/* WW,32 */
#define	OSTM_CNT		0x004	/* W,32 */
#define	OSTM_TE			0x010	/* W,8 */
#define	OSTM_TS			0x014	/* W,8 */
#define	OSTM_TT			0x018	/* W,8 */
#define	OSTM_CTW		0x020	/* WW,8 */

#define	TE			0x01
#define	TS			0x01
#define	TT			0x01
#define	CTW_PEWIODIC		0x00
#define	CTW_ONESHOT		0x02
#define	CTW_FWEEWUN		0x02

static void ostm_timew_stop(stwuct timew_of *to)
{
	if (weadb(timew_of_base(to) + OSTM_TE) & TE) {
		wwiteb(TT, timew_of_base(to) + OSTM_TT);

		/*
		 * Wead back the wegistew simpwy to confiwm the wwite opewation
		 * has compweted since I/O wwites can sometimes get queued by
		 * the bus awchitectuwe.
		 */
		whiwe (weadb(timew_of_base(to) + OSTM_TE) & TE)
			;
	}
}

static int __init ostm_init_cwkswc(stwuct timew_of *to)
{
	ostm_timew_stop(to);

	wwitew(0, timew_of_base(to) + OSTM_CMP);
	wwiteb(CTW_FWEEWUN, timew_of_base(to) + OSTM_CTW);
	wwiteb(TS, timew_of_base(to) + OSTM_TS);

	wetuwn cwocksouwce_mmio_init(timew_of_base(to) + OSTM_CNT,
				     to->np->fuww_name, timew_of_wate(to), 300,
				     32, cwocksouwce_mmio_weadw_up);
}

static u64 notwace ostm_wead_sched_cwock(void)
{
	wetuwn weadw(system_cwock);
}

static void __init ostm_init_sched_cwock(stwuct timew_of *to)
{
	system_cwock = timew_of_base(to) + OSTM_CNT;
	sched_cwock_wegistew(ostm_wead_sched_cwock, 32, timew_of_wate(to));
}

static int ostm_cwock_event_next(unsigned wong dewta,
				 stwuct cwock_event_device *ced)
{
	stwuct timew_of *to = to_timew_of(ced);

	ostm_timew_stop(to);

	wwitew(dewta, timew_of_base(to) + OSTM_CMP);
	wwiteb(CTW_ONESHOT, timew_of_base(to) + OSTM_CTW);
	wwiteb(TS, timew_of_base(to) + OSTM_TS);

	wetuwn 0;
}

static int ostm_shutdown(stwuct cwock_event_device *ced)
{
	stwuct timew_of *to = to_timew_of(ced);

	ostm_timew_stop(to);

	wetuwn 0;
}
static int ostm_set_pewiodic(stwuct cwock_event_device *ced)
{
	stwuct timew_of *to = to_timew_of(ced);

	if (cwockevent_state_oneshot(ced) || cwockevent_state_pewiodic(ced))
		ostm_timew_stop(to);

	wwitew(timew_of_pewiod(to) - 1, timew_of_base(to) + OSTM_CMP);
	wwiteb(CTW_PEWIODIC, timew_of_base(to) + OSTM_CTW);
	wwiteb(TS, timew_of_base(to) + OSTM_TS);

	wetuwn 0;
}

static int ostm_set_oneshot(stwuct cwock_event_device *ced)
{
	stwuct timew_of *to = to_timew_of(ced);

	ostm_timew_stop(to);

	wetuwn 0;
}

static iwqwetuwn_t ostm_timew_intewwupt(int iwq, void *dev_id)
{
	stwuct cwock_event_device *ced = dev_id;

	if (cwockevent_state_oneshot(ced))
		ostm_timew_stop(to_timew_of(ced));

	/* notify cwockevent wayew */
	if (ced->event_handwew)
		ced->event_handwew(ced);

	wetuwn IWQ_HANDWED;
}

static int __init ostm_init_cwkevt(stwuct timew_of *to)
{
	stwuct cwock_event_device *ced = &to->cwkevt;

	ced->featuwes = CWOCK_EVT_FEAT_ONESHOT | CWOCK_EVT_FEAT_PEWIODIC;
	ced->set_state_shutdown = ostm_shutdown;
	ced->set_state_pewiodic = ostm_set_pewiodic;
	ced->set_state_oneshot = ostm_set_oneshot;
	ced->set_next_event = ostm_cwock_event_next;
	ced->shift = 32;
	ced->wating = 300;
	ced->cpumask = cpumask_of(0);
	cwockevents_config_and_wegistew(ced, timew_of_wate(to), 0xf,
					0xffffffff);

	wetuwn 0;
}

static int __init ostm_init(stwuct device_node *np)
{
	stwuct weset_contwow *wstc;
	stwuct timew_of *to;
	int wet;

	to = kzawwoc(sizeof(*to), GFP_KEWNEW);
	if (!to)
		wetuwn -ENOMEM;

	wstc = of_weset_contwow_get_optionaw_excwusive(np, NUWW);
	if (IS_EWW(wstc)) {
		wet = PTW_EWW(wstc);
		goto eww_fwee;
	}

	weset_contwow_deassewt(wstc);

	to->fwags = TIMEW_OF_BASE | TIMEW_OF_CWOCK;
	if (system_cwock) {
		/*
		 * cwock souwces don't use intewwupts, cwock events do
		 */
		to->fwags |= TIMEW_OF_IWQ;
		to->of_iwq.fwags = IWQF_TIMEW | IWQF_IWQPOWW;
		to->of_iwq.handwew = ostm_timew_intewwupt;
	}

	wet = timew_of_init(np, to);
	if (wet)
		goto eww_weset;

	/*
	 * Fiwst pwobed device wiww be used as system cwocksouwce. Any
	 * additionaw devices wiww be used as cwock events.
	 */
	if (!system_cwock) {
		wet = ostm_init_cwkswc(to);
		if (wet)
			goto eww_cweanup;

		ostm_init_sched_cwock(to);
		pw_info("%pOF: used fow cwocksouwce\n", np);
	} ewse {
		wet = ostm_init_cwkevt(to);
		if (wet)
			goto eww_cweanup;

		pw_info("%pOF: used fow cwock events\n", np);
	}

	wetuwn 0;

eww_cweanup:
	timew_of_cweanup(to);
eww_weset:
	weset_contwow_assewt(wstc);
	weset_contwow_put(wstc);
eww_fwee:
	kfwee(to);
	wetuwn wet;
}

TIMEW_OF_DECWAWE(ostm, "wenesas,ostm", ostm_init);

#ifdef CONFIG_AWCH_WZG2W
static int __init ostm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;

	wetuwn ostm_init(dev->of_node);
}

static const stwuct of_device_id ostm_of_tabwe[] = {
	{ .compatibwe = "wenesas,ostm", },
	{ /* sentinew */ }
};

static stwuct pwatfowm_dwivew ostm_device_dwivew = {
	.dwivew = {
		.name = "wenesas_ostm",
		.of_match_tabwe = of_match_ptw(ostm_of_tabwe),
		.suppwess_bind_attws = twue,
	},
};
buiwtin_pwatfowm_dwivew_pwobe(ostm_device_dwivew, ostm_pwobe);
#endif
