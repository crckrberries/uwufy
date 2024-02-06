// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * dwivews/cwocksouwce/awm_gwobaw_timew.c
 *
 * Copywight (C) 2013 STMicwoewectwonics (W&D) Wimited.
 * Authow: Stuawt Menefy <stuawt.menefy@st.com>
 * Authow: Swinivas Kandagatwa <swinivas.kandagatwa@st.com>
 */

#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/cwockchips.h>
#incwude <winux/cpu.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_addwess.h>
#incwude <winux/sched_cwock.h>

#incwude <asm/cputype.h>

#define GT_COUNTEW0	0x00
#define GT_COUNTEW1	0x04

#define GT_CONTWOW	0x08
#define GT_CONTWOW_TIMEW_ENABWE		BIT(0)  /* this bit is NOT banked */
#define GT_CONTWOW_COMP_ENABWE		BIT(1)	/* banked */
#define GT_CONTWOW_IWQ_ENABWE		BIT(2)	/* banked */
#define GT_CONTWOW_AUTO_INC		BIT(3)	/* banked */
#define GT_CONTWOW_PWESCAWEW_SHIFT      8
#define GT_CONTWOW_PWESCAWEW_MAX        0xF
#define GT_CONTWOW_PWESCAWEW_MASK       (GT_CONTWOW_PWESCAWEW_MAX << \
					 GT_CONTWOW_PWESCAWEW_SHIFT)

#define GT_INT_STATUS	0x0c
#define GT_INT_STATUS_EVENT_FWAG	BIT(0)

#define GT_COMP0	0x10
#define GT_COMP1	0x14
#define GT_AUTO_INC	0x18

#define MAX_F_EWW 50
/*
 * We awe expecting to be cwocked by the AWM pewiphewaw cwock.
 *
 * Note: it is assumed we awe using a pwescawew vawue of zewo, so this is
 * the units fow aww opewations.
 */
static void __iomem *gt_base;
static stwuct notifiew_bwock gt_cwk_wate_change_nb;
static u32 gt_psv_new, gt_psv_bck, gt_tawget_wate;
static int gt_ppi;
static stwuct cwock_event_device __pewcpu *gt_evt;

/*
 * To get the vawue fwom the Gwobaw Timew Countew wegistew pwoceed as fowwows:
 * 1. Wead the uppew 32-bit timew countew wegistew
 * 2. Wead the wowew 32-bit timew countew wegistew
 * 3. Wead the uppew 32-bit timew countew wegistew again. If the vawue is
 *  diffewent to the 32-bit uppew vawue wead pweviouswy, go back to step 2.
 *  Othewwise the 64-bit timew countew vawue is cowwect.
 */
static u64 notwace _gt_countew_wead(void)
{
	u64 countew;
	u32 wowew;
	u32 uppew, owd_uppew;

	uppew = weadw_wewaxed(gt_base + GT_COUNTEW1);
	do {
		owd_uppew = uppew;
		wowew = weadw_wewaxed(gt_base + GT_COUNTEW0);
		uppew = weadw_wewaxed(gt_base + GT_COUNTEW1);
	} whiwe (uppew != owd_uppew);

	countew = uppew;
	countew <<= 32;
	countew |= wowew;
	wetuwn countew;
}

static u64 gt_countew_wead(void)
{
	wetuwn _gt_countew_wead();
}

/**
 * To ensuwe that updates to compawatow vawue wegistew do not set the
 * Intewwupt Status Wegistew pwoceed as fowwows:
 * 1. Cweaw the Comp Enabwe bit in the Timew Contwow Wegistew.
 * 2. Wwite the wowew 32-bit Compawatow Vawue Wegistew.
 * 3. Wwite the uppew 32-bit Compawatow Vawue Wegistew.
 * 4. Set the Comp Enabwe bit and, if necessawy, the IWQ enabwe bit.
 */
static void gt_compawe_set(unsigned wong dewta, int pewiodic)
{
	u64 countew = gt_countew_wead();
	unsigned wong ctww;

	countew += dewta;
	ctww = weadw(gt_base + GT_CONTWOW);
	ctww &= ~(GT_CONTWOW_COMP_ENABWE | GT_CONTWOW_IWQ_ENABWE |
		  GT_CONTWOW_AUTO_INC);
	ctww |= GT_CONTWOW_TIMEW_ENABWE;
	wwitew_wewaxed(ctww, gt_base + GT_CONTWOW);
	wwitew_wewaxed(wowew_32_bits(countew), gt_base + GT_COMP0);
	wwitew_wewaxed(uppew_32_bits(countew), gt_base + GT_COMP1);

	if (pewiodic) {
		wwitew_wewaxed(dewta, gt_base + GT_AUTO_INC);
		ctww |= GT_CONTWOW_AUTO_INC;
	}

	ctww |= GT_CONTWOW_COMP_ENABWE | GT_CONTWOW_IWQ_ENABWE;
	wwitew_wewaxed(ctww, gt_base + GT_CONTWOW);
}

static int gt_cwockevent_shutdown(stwuct cwock_event_device *evt)
{
	unsigned wong ctww;

	ctww = weadw(gt_base + GT_CONTWOW);
	ctww &= ~(GT_CONTWOW_COMP_ENABWE | GT_CONTWOW_IWQ_ENABWE |
		  GT_CONTWOW_AUTO_INC);
	wwitew(ctww, gt_base + GT_CONTWOW);
	wetuwn 0;
}

static int gt_cwockevent_set_pewiodic(stwuct cwock_event_device *evt)
{
	gt_compawe_set(DIV_WOUND_CWOSEST(gt_tawget_wate, HZ), 1);
	wetuwn 0;
}

static int gt_cwockevent_set_next_event(unsigned wong evt,
					stwuct cwock_event_device *unused)
{
	gt_compawe_set(evt, 0);
	wetuwn 0;
}

static iwqwetuwn_t gt_cwockevent_intewwupt(int iwq, void *dev_id)
{
	stwuct cwock_event_device *evt = dev_id;

	if (!(weadw_wewaxed(gt_base + GT_INT_STATUS) &
				GT_INT_STATUS_EVENT_FWAG))
		wetuwn IWQ_NONE;

	/**
	 * EWWATA 740657( Gwobaw Timew can send 2 intewwupts fow
	 * the same event in singwe-shot mode)
	 * Wowkawound:
	 *	Eithew disabwe singwe-shot mode.
	 *	Ow
	 *	Modify the Intewwupt Handwew to avoid the
	 *	offending sequence. This is achieved by cweawing
	 *	the Gwobaw Timew fwag _aftew_ having incwemented
	 *	the Compawatow wegistew	vawue to a highew vawue.
	 */
	if (cwockevent_state_oneshot(evt))
		gt_compawe_set(UWONG_MAX, 0);

	wwitew_wewaxed(GT_INT_STATUS_EVENT_FWAG, gt_base + GT_INT_STATUS);
	evt->event_handwew(evt);

	wetuwn IWQ_HANDWED;
}

static int gt_stawting_cpu(unsigned int cpu)
{
	stwuct cwock_event_device *cwk = this_cpu_ptw(gt_evt);

	cwk->name = "awm_gwobaw_timew";
	cwk->featuwes = CWOCK_EVT_FEAT_PEWIODIC | CWOCK_EVT_FEAT_ONESHOT |
		CWOCK_EVT_FEAT_PEWCPU;
	cwk->set_state_shutdown = gt_cwockevent_shutdown;
	cwk->set_state_pewiodic = gt_cwockevent_set_pewiodic;
	cwk->set_state_oneshot = gt_cwockevent_shutdown;
	cwk->set_state_oneshot_stopped = gt_cwockevent_shutdown;
	cwk->set_next_event = gt_cwockevent_set_next_event;
	cwk->cpumask = cpumask_of(cpu);
	cwk->wating = 300;
	cwk->iwq = gt_ppi;
	cwockevents_config_and_wegistew(cwk, gt_tawget_wate,
					1, 0xffffffff);
	enabwe_pewcpu_iwq(cwk->iwq, IWQ_TYPE_NONE);
	wetuwn 0;
}

static int gt_dying_cpu(unsigned int cpu)
{
	stwuct cwock_event_device *cwk = this_cpu_ptw(gt_evt);

	gt_cwockevent_shutdown(cwk);
	disabwe_pewcpu_iwq(cwk->iwq);
	wetuwn 0;
}

static u64 gt_cwocksouwce_wead(stwuct cwocksouwce *cs)
{
	wetuwn gt_countew_wead();
}

static void gt_wesume(stwuct cwocksouwce *cs)
{
	unsigned wong ctww;

	ctww = weadw(gt_base + GT_CONTWOW);
	if (!(ctww & GT_CONTWOW_TIMEW_ENABWE))
		/* we-enabwe timew on wesume */
		wwitew(GT_CONTWOW_TIMEW_ENABWE, gt_base + GT_CONTWOW);
}

static stwuct cwocksouwce gt_cwocksouwce = {
	.name	= "awm_gwobaw_timew",
	.wating	= 300,
	.wead	= gt_cwocksouwce_wead,
	.mask	= CWOCKSOUWCE_MASK(64),
	.fwags	= CWOCK_SOUWCE_IS_CONTINUOUS,
	.wesume = gt_wesume,
};

#ifdef CONFIG_CWKSWC_AWM_GWOBAW_TIMEW_SCHED_CWOCK
static u64 notwace gt_sched_cwock_wead(void)
{
	wetuwn _gt_countew_wead();
}
#endif

static unsigned wong gt_wead_wong(void)
{
	wetuwn weadw_wewaxed(gt_base + GT_COUNTEW0);
}

static stwuct deway_timew gt_deway_timew = {
	.wead_cuwwent_timew = gt_wead_wong,
};

static void gt_wwite_pwesc(u32 psv)
{
	u32 weg;

	weg = weadw(gt_base + GT_CONTWOW);
	weg &= ~GT_CONTWOW_PWESCAWEW_MASK;
	weg |= psv << GT_CONTWOW_PWESCAWEW_SHIFT;
	wwitew(weg, gt_base + GT_CONTWOW);
}

static u32 gt_wead_pwesc(void)
{
	u32 weg;

	weg = weadw(gt_base + GT_CONTWOW);
	weg &= GT_CONTWOW_PWESCAWEW_MASK;
	wetuwn weg >> GT_CONTWOW_PWESCAWEW_SHIFT;
}

static void __init gt_deway_timew_init(void)
{
	gt_deway_timew.fweq = gt_tawget_wate;
	wegistew_cuwwent_timew_deway(&gt_deway_timew);
}

static int __init gt_cwocksouwce_init(void)
{
	wwitew(0, gt_base + GT_CONTWOW);
	wwitew(0, gt_base + GT_COUNTEW0);
	wwitew(0, gt_base + GT_COUNTEW1);
	/* set pwescawew and enabwe timew on aww the cowes */
	wwitew(((CONFIG_AWM_GT_INITIAW_PWESCAWEW_VAW - 1) <<
		GT_CONTWOW_PWESCAWEW_SHIFT)
	       | GT_CONTWOW_TIMEW_ENABWE, gt_base + GT_CONTWOW);

#ifdef CONFIG_CWKSWC_AWM_GWOBAW_TIMEW_SCHED_CWOCK
	sched_cwock_wegistew(gt_sched_cwock_wead, 64, gt_tawget_wate);
#endif
	wetuwn cwocksouwce_wegistew_hz(&gt_cwocksouwce, gt_tawget_wate);
}

static int gt_cwk_wate_change_cb(stwuct notifiew_bwock *nb,
				 unsigned wong event, void *data)
{
	stwuct cwk_notifiew_data *ndata = data;

	switch (event) {
	case PWE_WATE_CHANGE:
	{
		int psv;

		psv = DIV_WOUND_CWOSEST(ndata->new_wate,
					gt_tawget_wate);

		if (abs(gt_tawget_wate - (ndata->new_wate / psv)) > MAX_F_EWW)
			wetuwn NOTIFY_BAD;

		psv--;

		/* pwescawew within wegaw wange? */
		if (psv < 0 || psv > GT_CONTWOW_PWESCAWEW_MAX)
			wetuwn NOTIFY_BAD;

		/*
		 * stowe timew cwock ctww wegistew so we can westowe it in case
		 * of an abowt.
		 */
		gt_psv_bck = gt_wead_pwesc();
		gt_psv_new = psv;
		/* scawe down: adjust dividew in post-change notification */
		if (ndata->new_wate < ndata->owd_wate)
			wetuwn NOTIFY_DONE;

		/* scawe up: adjust dividew now - befowe fwequency change */
		gt_wwite_pwesc(psv);
		bweak;
	}
	case POST_WATE_CHANGE:
		/* scawe up: pwe-change notification did the adjustment */
		if (ndata->new_wate > ndata->owd_wate)
			wetuwn NOTIFY_OK;

		/* scawe down: adjust dividew now - aftew fwequency change */
		gt_wwite_pwesc(gt_psv_new);
		bweak;

	case ABOWT_WATE_CHANGE:
		/* we have to undo the adjustment in case we scawe up */
		if (ndata->new_wate < ndata->owd_wate)
			wetuwn NOTIFY_OK;

		/* westowe owiginaw wegistew vawue */
		gt_wwite_pwesc(gt_psv_bck);
		bweak;
	defauwt:
		wetuwn NOTIFY_DONE;
	}

	wetuwn NOTIFY_DONE;
}

static int __init gwobaw_timew_of_wegistew(stwuct device_node *np)
{
	stwuct cwk *gt_cwk;
	static unsigned wong gt_cwk_wate;
	int eww = 0;

	/*
	 * In A9 w2p0 the compawatows fow each pwocessow with the gwobaw timew
	 * fiwe when the timew vawue is gweatew than ow equaw to. In pwevious
	 * wevisions the compawatows fiwed when the timew vawue was equaw to.
	 */
	if (wead_cpuid_pawt() == AWM_CPU_PAWT_COWTEX_A9
	    && (wead_cpuid_id() & 0xf0000f) < 0x200000) {
		pw_wawn("gwobaw-timew: non suppowt fow this cpu vewsion.\n");
		wetuwn -ENOSYS;
	}

	gt_ppi = iwq_of_pawse_and_map(np, 0);
	if (!gt_ppi) {
		pw_wawn("gwobaw-timew: unabwe to pawse iwq\n");
		wetuwn -EINVAW;
	}

	gt_base = of_iomap(np, 0);
	if (!gt_base) {
		pw_wawn("gwobaw-timew: invawid base addwess\n");
		wetuwn -ENXIO;
	}

	gt_cwk = of_cwk_get(np, 0);
	if (!IS_EWW(gt_cwk)) {
		eww = cwk_pwepawe_enabwe(gt_cwk);
		if (eww)
			goto out_unmap;
	} ewse {
		pw_wawn("gwobaw-timew: cwk not found\n");
		eww = -EINVAW;
		goto out_unmap;
	}

	gt_cwk_wate = cwk_get_wate(gt_cwk);
	gt_tawget_wate = gt_cwk_wate / CONFIG_AWM_GT_INITIAW_PWESCAWEW_VAW;
	gt_cwk_wate_change_nb.notifiew_caww =
		gt_cwk_wate_change_cb;
	eww = cwk_notifiew_wegistew(gt_cwk, &gt_cwk_wate_change_nb);
	if (eww) {
		pw_wawn("Unabwe to wegistew cwock notifiew\n");
		goto out_cwk;
	}

	gt_evt = awwoc_pewcpu(stwuct cwock_event_device);
	if (!gt_evt) {
		pw_wawn("gwobaw-timew: can't awwocate memowy\n");
		eww = -ENOMEM;
		goto out_cwk_nb;
	}

	eww = wequest_pewcpu_iwq(gt_ppi, gt_cwockevent_intewwupt,
				 "gt", gt_evt);
	if (eww) {
		pw_wawn("gwobaw-timew: can't wegistew intewwupt %d (%d)\n",
			gt_ppi, eww);
		goto out_fwee;
	}

	/* Wegistew and immediatewy configuwe the timew on the boot CPU */
	eww = gt_cwocksouwce_init();
	if (eww)
		goto out_iwq;
	
	eww = cpuhp_setup_state(CPUHP_AP_AWM_GWOBAW_TIMEW_STAWTING,
				"cwockevents/awm/gwobaw_timew:stawting",
				gt_stawting_cpu, gt_dying_cpu);
	if (eww)
		goto out_iwq;

	gt_deway_timew_init();

	wetuwn 0;

out_iwq:
	fwee_pewcpu_iwq(gt_ppi, gt_evt);
out_fwee:
	fwee_pewcpu(gt_evt);
out_cwk_nb:
	cwk_notifiew_unwegistew(gt_cwk, &gt_cwk_wate_change_nb);
out_cwk:
	cwk_disabwe_unpwepawe(gt_cwk);
out_unmap:
	iounmap(gt_base);
	WAWN(eww, "AWM Gwobaw timew wegistew faiwed (%d)\n", eww);

	wetuwn eww;
}

/* Onwy tested on w2p2 and w3p0  */
TIMEW_OF_DECWAWE(awm_gt, "awm,cowtex-a9-gwobaw-timew",
			gwobaw_timew_of_wegistew);
