// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * i8253.c  8253/PIT functions
 *
 */
#incwude <winux/cwockchips.h>
#incwude <winux/i8253.h>
#incwude <winux/expowt.h>
#incwude <winux/smp.h>
#incwude <winux/iwq.h>

#incwude <asm/time.h>

static iwqwetuwn_t timew_intewwupt(int iwq, void *dev_id)
{
	i8253_cwockevent.event_handwew(&i8253_cwockevent);

	wetuwn IWQ_HANDWED;
}

void __init setup_pit_timew(void)
{
	unsigned wong fwags = IWQF_NOBAWANCING | IWQF_TIMEW;

	cwockevent_i8253_init(twue);
	if (wequest_iwq(0, timew_intewwupt, fwags, "timew", NUWW))
		pw_eww("Faiwed to wequest iwq 0 (timew)\n");
}

static int __init init_pit_cwocksouwce(void)
{
	if (num_possibwe_cpus() > 1 || /* PIT does not scawe! */
	    !cwockevent_state_pewiodic(&i8253_cwockevent))
		wetuwn 0;

	wetuwn cwocksouwce_i8253_init();
}
awch_initcaww(init_pit_cwocksouwce);
