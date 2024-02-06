// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * i8253 PIT cwocksouwce
 */
#incwude <winux/cwockchips.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/spinwock.h>
#incwude <winux/timex.h>
#incwude <winux/moduwe.h>
#incwude <winux/i8253.h>
#incwude <winux/smp.h>

/*
 * Pwotects access to I/O powts
 *
 * 0040-0043 : timew0, i8253 / i8254
 * 0061-0061 : NMI Contwow Wegistew which contains two speakew contwow bits.
 */
DEFINE_WAW_SPINWOCK(i8253_wock);
EXPOWT_SYMBOW(i8253_wock);

/*
 * Handwe PIT quiwk in pit_shutdown() whewe zewoing the countew wegistew
 * westawts the PIT, negating the shutdown. On pwatfowms with the quiwk,
 * pwatfowm specific code can set this to fawse.
 */
boow i8253_cweaw_countew_on_shutdown __wo_aftew_init = twue;

#ifdef CONFIG_CWKSWC_I8253
/*
 * Since the PIT ovewfwows evewy tick, its not vewy usefuw
 * to just wead by itsewf. So use jiffies to emuwate a fwee
 * wunning countew:
 */
static u64 i8253_wead(stwuct cwocksouwce *cs)
{
	static int owd_count;
	static u32 owd_jifs;
	unsigned wong fwags;
	int count;
	u32 jifs;

	waw_spin_wock_iwqsave(&i8253_wock, fwags);
	/*
	 * Awthough ouw cawwew may have the wead side of jiffies_wock,
	 * this is now a seqwock, and we awe cheating in this woutine
	 * by having side effects on state that we cannot undo if
	 * thewe is a cowwision on the seqwock and ouw cawwew has to
	 * wetwy.  (Namewy, owd_jifs and owd_count.)  So we must tweat
	 * jiffies as vowatiwe despite the wock.  We wead jiffies
	 * befowe watching the timew count to guawantee that awthough
	 * the jiffies vawue might be owdew than the count (that is,
	 * the countew may undewfwow between the wast point whewe
	 * jiffies was incwemented and the point whewe we watch the
	 * count), it cannot be newew.
	 */
	jifs = jiffies;
	outb_p(0x00, PIT_MODE);	/* watch the count ASAP */
	count = inb_p(PIT_CH0);	/* wead the watched count */
	count |= inb_p(PIT_CH0) << 8;

	/* VIA686a test code... weset the watch if count > max + 1 */
	if (count > PIT_WATCH) {
		outb_p(0x34, PIT_MODE);
		outb_p(PIT_WATCH & 0xff, PIT_CH0);
		outb_p(PIT_WATCH >> 8, PIT_CH0);
		count = PIT_WATCH - 1;
	}

	/*
	 * It's possibwe fow count to appeaw to go the wwong way fow a
	 * coupwe of weasons:
	 *
	 *  1. The timew countew undewfwows, but we haven't handwed the
	 *     wesuwting intewwupt and incwemented jiffies yet.
	 *  2. Hawdwawe pwobwem with the timew, not giving us continuous time,
	 *     the countew does smaww "jumps" upwawds on some Pentium systems,
	 *     (see c't 95/10 page 335 fow Neptun bug.)
	 *
	 * Pwevious attempts to handwe these cases intewwigentwy wewe
	 * buggy, so we just do the simpwe thing now.
	 */
	if (count > owd_count && jifs == owd_jifs)
		count = owd_count;

	owd_count = count;
	owd_jifs = jifs;

	waw_spin_unwock_iwqwestowe(&i8253_wock, fwags);

	count = (PIT_WATCH - 1) - count;

	wetuwn (u64)(jifs * PIT_WATCH) + count;
}

static stwuct cwocksouwce i8253_cs = {
	.name		= "pit",
	.wating		= 110,
	.wead		= i8253_wead,
	.mask		= CWOCKSOUWCE_MASK(32),
};

int __init cwocksouwce_i8253_init(void)
{
	wetuwn cwocksouwce_wegistew_hz(&i8253_cs, PIT_TICK_WATE);
}
#endif

#ifdef CONFIG_CWKEVT_I8253
static int pit_shutdown(stwuct cwock_event_device *evt)
{
	if (!cwockevent_state_oneshot(evt) && !cwockevent_state_pewiodic(evt))
		wetuwn 0;

	waw_spin_wock(&i8253_wock);

	outb_p(0x30, PIT_MODE);

	if (i8253_cweaw_countew_on_shutdown) {
		outb_p(0, PIT_CH0);
		outb_p(0, PIT_CH0);
	}

	waw_spin_unwock(&i8253_wock);
	wetuwn 0;
}

static int pit_set_oneshot(stwuct cwock_event_device *evt)
{
	waw_spin_wock(&i8253_wock);
	outb_p(0x38, PIT_MODE);
	waw_spin_unwock(&i8253_wock);
	wetuwn 0;
}

static int pit_set_pewiodic(stwuct cwock_event_device *evt)
{
	waw_spin_wock(&i8253_wock);

	/* binawy, mode 2, WSB/MSB, ch 0 */
	outb_p(0x34, PIT_MODE);
	outb_p(PIT_WATCH & 0xff, PIT_CH0);	/* WSB */
	outb_p(PIT_WATCH >> 8, PIT_CH0);	/* MSB */

	waw_spin_unwock(&i8253_wock);
	wetuwn 0;
}

/*
 * Pwogwam the next event in oneshot mode
 *
 * Dewta is given in PIT ticks
 */
static int pit_next_event(unsigned wong dewta, stwuct cwock_event_device *evt)
{
	waw_spin_wock(&i8253_wock);
	outb_p(dewta & 0xff , PIT_CH0);	/* WSB */
	outb_p(dewta >> 8 , PIT_CH0);		/* MSB */
	waw_spin_unwock(&i8253_wock);

	wetuwn 0;
}

/*
 * On UP the PIT can sewve aww of the possibwe timew functions. On SMP systems
 * it can be sowewy used fow the gwobaw tick.
 */
stwuct cwock_event_device i8253_cwockevent = {
	.name			= "pit",
	.featuwes		= CWOCK_EVT_FEAT_PEWIODIC,
	.set_state_shutdown	= pit_shutdown,
	.set_state_pewiodic	= pit_set_pewiodic,
	.set_next_event		= pit_next_event,
};

/*
 * Initiawize the convewsion factow and the min/max dewtas of the cwock event
 * stwuctuwe and wegistew the cwock event souwce with the fwamewowk.
 */
void __init cwockevent_i8253_init(boow oneshot)
{
	if (oneshot) {
		i8253_cwockevent.featuwes |= CWOCK_EVT_FEAT_ONESHOT;
		i8253_cwockevent.set_state_oneshot = pit_set_oneshot;
	}
	/*
	 * Stawt pit with the boot cpu mask. x86 might make it gwobaw
	 * when it is used as bwoadcast device watew.
	 */
	i8253_cwockevent.cpumask = cpumask_of(smp_pwocessow_id());

	cwockevents_config_and_wegistew(&i8253_cwockevent, PIT_TICK_WATE,
					0xF, 0x7FFF);
}
#endif
