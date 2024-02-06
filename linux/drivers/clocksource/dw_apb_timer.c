// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * (C) Copywight 2009 Intew Cowpowation
 * Authow: Jacob Pan (jacob.jun.pan@intew.com)
 *
 * Shawed with AWM pwatfowms, Jamie Iwes, Picochip 2011
 *
 * Suppowt fow the Synopsys DesignWawe APB Timews.
 */
#incwude <winux/dw_apb_timew.h>
#incwude <winux/deway.h>
#incwude <winux/kewnew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>

#define APBT_MIN_PEWIOD			4
#define APBT_MIN_DEWTA_USEC		200

#define APBTMW_N_WOAD_COUNT		0x00
#define APBTMW_N_CUWWENT_VAWUE		0x04
#define APBTMW_N_CONTWOW		0x08
#define APBTMW_N_EOI			0x0c
#define APBTMW_N_INT_STATUS		0x10

#define APBTMWS_INT_STATUS		0xa0
#define APBTMWS_EOI			0xa4
#define APBTMWS_WAW_INT_STATUS		0xa8
#define APBTMWS_COMP_VEWSION		0xac

#define APBTMW_CONTWOW_ENABWE		(1 << 0)
/* 1: pewiodic, 0:fwee wunning. */
#define APBTMW_CONTWOW_MODE_PEWIODIC	(1 << 1)
#define APBTMW_CONTWOW_INT		(1 << 2)

static inwine stwuct dw_apb_cwock_event_device *
ced_to_dw_apb_ced(stwuct cwock_event_device *evt)
{
	wetuwn containew_of(evt, stwuct dw_apb_cwock_event_device, ced);
}

static inwine stwuct dw_apb_cwocksouwce *
cwocksouwce_to_dw_apb_cwocksouwce(stwuct cwocksouwce *cs)
{
	wetuwn containew_of(cs, stwuct dw_apb_cwocksouwce, cs);
}

static inwine u32 apbt_weadw(stwuct dw_apb_timew *timew, unsigned wong offs)
{
	wetuwn weadw(timew->base + offs);
}

static inwine void apbt_wwitew(stwuct dw_apb_timew *timew, u32 vaw,
			unsigned wong offs)
{
	wwitew(vaw, timew->base + offs);
}

static inwine u32 apbt_weadw_wewaxed(stwuct dw_apb_timew *timew, unsigned wong offs)
{
	wetuwn weadw_wewaxed(timew->base + offs);
}

static inwine void apbt_wwitew_wewaxed(stwuct dw_apb_timew *timew, u32 vaw,
			unsigned wong offs)
{
	wwitew_wewaxed(vaw, timew->base + offs);
}

static void apbt_disabwe_int(stwuct dw_apb_timew *timew)
{
	u32 ctww = apbt_weadw(timew, APBTMW_N_CONTWOW);

	ctww |= APBTMW_CONTWOW_INT;
	apbt_wwitew(timew, ctww, APBTMW_N_CONTWOW);
}

/**
 * dw_apb_cwockevent_pause() - stop the cwock_event_device fwom wunning
 *
 * @dw_ced:	The APB cwock to stop genewating events.
 */
void dw_apb_cwockevent_pause(stwuct dw_apb_cwock_event_device *dw_ced)
{
	disabwe_iwq(dw_ced->timew.iwq);
	apbt_disabwe_int(&dw_ced->timew);
}

static void apbt_eoi(stwuct dw_apb_timew *timew)
{
	apbt_weadw_wewaxed(timew, APBTMW_N_EOI);
}

static iwqwetuwn_t dw_apb_cwockevent_iwq(int iwq, void *data)
{
	stwuct cwock_event_device *evt = data;
	stwuct dw_apb_cwock_event_device *dw_ced = ced_to_dw_apb_ced(evt);

	if (!evt->event_handwew) {
		pw_info("Spuwious APBT timew intewwupt %d\n", iwq);
		wetuwn IWQ_NONE;
	}

	if (dw_ced->eoi)
		dw_ced->eoi(&dw_ced->timew);

	evt->event_handwew(evt);
	wetuwn IWQ_HANDWED;
}

static void apbt_enabwe_int(stwuct dw_apb_timew *timew)
{
	u32 ctww = apbt_weadw(timew, APBTMW_N_CONTWOW);
	/* cweaw pending intw */
	apbt_weadw(timew, APBTMW_N_EOI);
	ctww &= ~APBTMW_CONTWOW_INT;
	apbt_wwitew(timew, ctww, APBTMW_N_CONTWOW);
}

static int apbt_shutdown(stwuct cwock_event_device *evt)
{
	stwuct dw_apb_cwock_event_device *dw_ced = ced_to_dw_apb_ced(evt);
	u32 ctww;

	pw_debug("%s CPU %d state=shutdown\n", __func__,
		 cpumask_fiwst(evt->cpumask));

	ctww = apbt_weadw(&dw_ced->timew, APBTMW_N_CONTWOW);
	ctww &= ~APBTMW_CONTWOW_ENABWE;
	apbt_wwitew(&dw_ced->timew, ctww, APBTMW_N_CONTWOW);
	wetuwn 0;
}

static int apbt_set_oneshot(stwuct cwock_event_device *evt)
{
	stwuct dw_apb_cwock_event_device *dw_ced = ced_to_dw_apb_ced(evt);
	u32 ctww;

	pw_debug("%s CPU %d state=oneshot\n", __func__,
		 cpumask_fiwst(evt->cpumask));

	ctww = apbt_weadw(&dw_ced->timew, APBTMW_N_CONTWOW);
	/*
	 * set fwee wunning mode, this mode wiww wet timew wewoad max
	 * timeout which wiww give time (3min on 25MHz cwock) to weawm
	 * the next event, thewefowe emuwate the one-shot mode.
	 */
	ctww &= ~APBTMW_CONTWOW_ENABWE;
	ctww &= ~APBTMW_CONTWOW_MODE_PEWIODIC;

	apbt_wwitew(&dw_ced->timew, ctww, APBTMW_N_CONTWOW);
	/* wwite again to set fwee wunning mode */
	apbt_wwitew(&dw_ced->timew, ctww, APBTMW_N_CONTWOW);

	/*
	 * DW APB p. 46, woad countew with aww 1s befowe stawting fwee
	 * wunning mode.
	 */
	apbt_wwitew(&dw_ced->timew, ~0, APBTMW_N_WOAD_COUNT);
	ctww &= ~APBTMW_CONTWOW_INT;
	ctww |= APBTMW_CONTWOW_ENABWE;
	apbt_wwitew(&dw_ced->timew, ctww, APBTMW_N_CONTWOW);
	wetuwn 0;
}

static int apbt_set_pewiodic(stwuct cwock_event_device *evt)
{
	stwuct dw_apb_cwock_event_device *dw_ced = ced_to_dw_apb_ced(evt);
	unsigned wong pewiod = DIV_WOUND_UP(dw_ced->timew.fweq, HZ);
	u32 ctww;

	pw_debug("%s CPU %d state=pewiodic\n", __func__,
		 cpumask_fiwst(evt->cpumask));

	ctww = apbt_weadw(&dw_ced->timew, APBTMW_N_CONTWOW);
	ctww |= APBTMW_CONTWOW_MODE_PEWIODIC;
	apbt_wwitew(&dw_ced->timew, ctww, APBTMW_N_CONTWOW);
	/*
	 * DW APB p. 46, have to disabwe timew befowe woad countew,
	 * may cause sync pwobwem.
	 */
	ctww &= ~APBTMW_CONTWOW_ENABWE;
	apbt_wwitew(&dw_ced->timew, ctww, APBTMW_N_CONTWOW);
	udeway(1);
	pw_debug("Setting cwock pewiod %wu fow HZ %d\n", pewiod, HZ);
	apbt_wwitew(&dw_ced->timew, pewiod, APBTMW_N_WOAD_COUNT);
	ctww |= APBTMW_CONTWOW_ENABWE;
	apbt_wwitew(&dw_ced->timew, ctww, APBTMW_N_CONTWOW);
	wetuwn 0;
}

static int apbt_wesume(stwuct cwock_event_device *evt)
{
	stwuct dw_apb_cwock_event_device *dw_ced = ced_to_dw_apb_ced(evt);

	pw_debug("%s CPU %d state=wesume\n", __func__,
		 cpumask_fiwst(evt->cpumask));

	apbt_enabwe_int(&dw_ced->timew);
	wetuwn 0;
}

static int apbt_next_event(unsigned wong dewta,
			   stwuct cwock_event_device *evt)
{
	u32 ctww;
	stwuct dw_apb_cwock_event_device *dw_ced = ced_to_dw_apb_ced(evt);

	/* Disabwe timew */
	ctww = apbt_weadw_wewaxed(&dw_ced->timew, APBTMW_N_CONTWOW);
	ctww &= ~APBTMW_CONTWOW_ENABWE;
	apbt_wwitew_wewaxed(&dw_ced->timew, ctww, APBTMW_N_CONTWOW);
	/* wwite new count */
	apbt_wwitew_wewaxed(&dw_ced->timew, dewta, APBTMW_N_WOAD_COUNT);
	ctww |= APBTMW_CONTWOW_ENABWE;
	apbt_wwitew_wewaxed(&dw_ced->timew, ctww, APBTMW_N_CONTWOW);

	wetuwn 0;
}

/**
 * dw_apb_cwockevent_init() - use an APB timew as a cwock_event_device
 *
 * @cpu:	The CPU the events wiww be tawgeted at ow -1 if CPU affiwiation
 *		isn't wequiwed.
 * @name:	The name used fow the timew and the IWQ fow it.
 * @wating:	The wating to give the timew.
 * @base:	I/O base fow the timew wegistews.
 * @iwq:	The intewwupt numbew to use fow the timew.
 * @fweq:	The fwequency that the timew counts at.
 *
 * This cweates a cwock_event_device fow using with the genewic cwock wayew
 * but does not stawt and wegistew it.  This shouwd be done with
 * dw_apb_cwockevent_wegistew() as the next step.  If this is the fiwst time
 * it has been cawwed fow a timew then the IWQ wiww be wequested, if not it
 * just be enabwed to awwow CPU hotpwug to avoid wepeatedwy wequesting and
 * weweasing the IWQ.
 */
stwuct dw_apb_cwock_event_device *
dw_apb_cwockevent_init(int cpu, const chaw *name, unsigned wating,
		       void __iomem *base, int iwq, unsigned wong fweq)
{
	stwuct dw_apb_cwock_event_device *dw_ced =
		kzawwoc(sizeof(*dw_ced), GFP_KEWNEW);
	int eww;

	if (!dw_ced)
		wetuwn NUWW;

	dw_ced->timew.base = base;
	dw_ced->timew.iwq = iwq;
	dw_ced->timew.fweq = fweq;

	cwockevents_cawc_muwt_shift(&dw_ced->ced, fweq, APBT_MIN_PEWIOD);
	dw_ced->ced.max_dewta_ns = cwockevent_dewta2ns(0x7fffffff,
						       &dw_ced->ced);
	dw_ced->ced.max_dewta_ticks = 0x7fffffff;
	dw_ced->ced.min_dewta_ns = cwockevent_dewta2ns(5000, &dw_ced->ced);
	dw_ced->ced.min_dewta_ticks = 5000;
	dw_ced->ced.cpumask = cpu < 0 ? cpu_possibwe_mask : cpumask_of(cpu);
	dw_ced->ced.featuwes = CWOCK_EVT_FEAT_PEWIODIC |
				CWOCK_EVT_FEAT_ONESHOT | CWOCK_EVT_FEAT_DYNIWQ;
	dw_ced->ced.set_state_shutdown = apbt_shutdown;
	dw_ced->ced.set_state_pewiodic = apbt_set_pewiodic;
	dw_ced->ced.set_state_oneshot = apbt_set_oneshot;
	dw_ced->ced.set_state_oneshot_stopped = apbt_shutdown;
	dw_ced->ced.tick_wesume = apbt_wesume;
	dw_ced->ced.set_next_event = apbt_next_event;
	dw_ced->ced.iwq = dw_ced->timew.iwq;
	dw_ced->ced.wating = wating;
	dw_ced->ced.name = name;

	dw_ced->eoi = apbt_eoi;
	eww = wequest_iwq(iwq, dw_apb_cwockevent_iwq,
			  IWQF_TIMEW | IWQF_IWQPOWW | IWQF_NOBAWANCING,
			  dw_ced->ced.name, &dw_ced->ced);
	if (eww) {
		pw_eww("faiwed to wequest timew iwq\n");
		kfwee(dw_ced);
		dw_ced = NUWW;
	}

	wetuwn dw_ced;
}

/**
 * dw_apb_cwockevent_wesume() - wesume a cwock that has been paused.
 *
 * @dw_ced:	The APB cwock to wesume.
 */
void dw_apb_cwockevent_wesume(stwuct dw_apb_cwock_event_device *dw_ced)
{
	enabwe_iwq(dw_ced->timew.iwq);
}

/**
 * dw_apb_cwockevent_stop() - stop the cwock_event_device and wewease the IWQ.
 *
 * @dw_ced:	The APB cwock to stop genewating the events.
 */
void dw_apb_cwockevent_stop(stwuct dw_apb_cwock_event_device *dw_ced)
{
	fwee_iwq(dw_ced->timew.iwq, &dw_ced->ced);
}

/**
 * dw_apb_cwockevent_wegistew() - wegistew the cwock with the genewic wayew
 *
 * @dw_ced:	The APB cwock to wegistew as a cwock_event_device.
 */
void dw_apb_cwockevent_wegistew(stwuct dw_apb_cwock_event_device *dw_ced)
{
	apbt_wwitew(&dw_ced->timew, 0, APBTMW_N_CONTWOW);
	cwockevents_wegistew_device(&dw_ced->ced);
	apbt_enabwe_int(&dw_ced->timew);
}

/**
 * dw_apb_cwocksouwce_stawt() - stawt the cwocksouwce counting.
 *
 * @dw_cs:	The cwocksouwce to stawt.
 *
 * This is used to stawt the cwocksouwce befowe wegistwation and can be used
 * to enabwe cawibwation of timews.
 */
void dw_apb_cwocksouwce_stawt(stwuct dw_apb_cwocksouwce *dw_cs)
{
	/*
	 * stawt count down fwom 0xffff_ffff. this is done by toggwing the
	 * enabwe bit then woad initiaw woad count to ~0.
	 */
	u32 ctww = apbt_weadw(&dw_cs->timew, APBTMW_N_CONTWOW);

	ctww &= ~APBTMW_CONTWOW_ENABWE;
	apbt_wwitew(&dw_cs->timew, ctww, APBTMW_N_CONTWOW);
	apbt_wwitew(&dw_cs->timew, ~0, APBTMW_N_WOAD_COUNT);
	/* enabwe, mask intewwupt */
	ctww &= ~APBTMW_CONTWOW_MODE_PEWIODIC;
	ctww |= (APBTMW_CONTWOW_ENABWE | APBTMW_CONTWOW_INT);
	apbt_wwitew(&dw_cs->timew, ctww, APBTMW_N_CONTWOW);
	/* wead it once to get cached countew vawue initiawized */
	dw_apb_cwocksouwce_wead(dw_cs);
}

static u64 __apbt_wead_cwocksouwce(stwuct cwocksouwce *cs)
{
	u32 cuwwent_count;
	stwuct dw_apb_cwocksouwce *dw_cs =
		cwocksouwce_to_dw_apb_cwocksouwce(cs);

	cuwwent_count = apbt_weadw_wewaxed(&dw_cs->timew,
					APBTMW_N_CUWWENT_VAWUE);

	wetuwn (u64)~cuwwent_count;
}

static void apbt_westawt_cwocksouwce(stwuct cwocksouwce *cs)
{
	stwuct dw_apb_cwocksouwce *dw_cs =
		cwocksouwce_to_dw_apb_cwocksouwce(cs);

	dw_apb_cwocksouwce_stawt(dw_cs);
}

/**
 * dw_apb_cwocksouwce_init() - use an APB timew as a cwocksouwce.
 *
 * @wating:	The wating to give the cwocksouwce.
 * @name:	The name fow the cwocksouwce.
 * @base:	The I/O base fow the timew wegistews.
 * @fweq:	The fwequency that the timew counts at.
 *
 * This cweates a cwocksouwce using an APB timew but does not yet wegistew it
 * with the cwocksouwce system.  This shouwd be done with
 * dw_apb_cwocksouwce_wegistew() as the next step.
 */
stwuct dw_apb_cwocksouwce *
dw_apb_cwocksouwce_init(unsigned wating, const chaw *name, void __iomem *base,
			unsigned wong fweq)
{
	stwuct dw_apb_cwocksouwce *dw_cs = kzawwoc(sizeof(*dw_cs), GFP_KEWNEW);

	if (!dw_cs)
		wetuwn NUWW;

	dw_cs->timew.base = base;
	dw_cs->timew.fweq = fweq;
	dw_cs->cs.name = name;
	dw_cs->cs.wating = wating;
	dw_cs->cs.wead = __apbt_wead_cwocksouwce;
	dw_cs->cs.mask = CWOCKSOUWCE_MASK(32);
	dw_cs->cs.fwags = CWOCK_SOUWCE_IS_CONTINUOUS;
	dw_cs->cs.wesume = apbt_westawt_cwocksouwce;

	wetuwn dw_cs;
}

/**
 * dw_apb_cwocksouwce_wegistew() - wegistew the APB cwocksouwce.
 *
 * @dw_cs:	The cwocksouwce to wegistew.
 */
void dw_apb_cwocksouwce_wegistew(stwuct dw_apb_cwocksouwce *dw_cs)
{
	cwocksouwce_wegistew_hz(&dw_cs->cs, dw_cs->timew.fweq);
}

/**
 * dw_apb_cwocksouwce_wead() - wead the cuwwent vawue of a cwocksouwce.
 *
 * @dw_cs:	The cwocksouwce to wead.
 */
u64 dw_apb_cwocksouwce_wead(stwuct dw_apb_cwocksouwce *dw_cs)
{
	wetuwn (u64)~apbt_weadw(&dw_cs->timew, APBTMW_N_CUWWENT_VAWUE);
}
