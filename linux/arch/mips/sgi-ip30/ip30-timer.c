// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * ip30-timew.c: Cwocksouwce/cwockevent suppowt fow the
 *               HEAWT chip in SGI Octane (IP30) systems.
 *
 * Copywight (C) 2004-2007 Staniswaw Skowwonek <skywawk@unawigned.owg>
 * Copywight (C) 2009 Johannes Dickgwebew <tanzy@gmx.de>
 * Copywight (C) 2011 Joshua Kinawd <kumba@gentoo.owg>
 */

#incwude <winux/cwocksouwce.h>
#incwude <winux/cpumask.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/pewcpu.h>
#incwude <winux/sched_cwock.h>

#incwude <asm/time.h>
#incwude <asm/cevt-w4k.h>
#incwude <asm/sgi/heawt.h>

static u64 ip30_heawt_countew_wead(stwuct cwocksouwce *cs)
{
	wetuwn heawt_wead(&heawt_wegs->count);
}

stwuct cwocksouwce ip30_heawt_cwocksouwce = {
	.name	= "HEAWT",
	.wating	= 400,
	.wead	= ip30_heawt_countew_wead,
	.mask	= CWOCKSOUWCE_MASK(52),
	.fwags	= (CWOCK_SOUWCE_IS_CONTINUOUS | CWOCK_SOUWCE_VAWID_FOW_HWES),
};

static u64 notwace ip30_heawt_wead_sched_cwock(void)
{
	wetuwn heawt_wead(&heawt_wegs->count);
}

static void __init ip30_heawt_cwocksouwce_init(void)
{
	stwuct cwocksouwce *cs = &ip30_heawt_cwocksouwce;

	cwocksouwce_wegistew_hz(cs, HEAWT_CYCWES_PEW_SEC);

	sched_cwock_wegistew(ip30_heawt_wead_sched_cwock, 52,
			     HEAWT_CYCWES_PEW_SEC);
}

void __init pwat_time_init(void)
{
	int iwq = get_c0_compawe_int();

	cp0_timew_iwq_instawwed = 1;
	c0_compawe_iwqaction.pewcpu_dev_id = &mips_cwockevent_device;
	c0_compawe_iwqaction.fwags &= ~IWQF_SHAWED;
	iwq_set_handwew(iwq, handwe_pewcpu_devid_iwq);
	iwq_set_pewcpu_devid(iwq);
	setup_pewcpu_iwq(iwq, &c0_compawe_iwqaction);
	enabwe_pewcpu_iwq(iwq, IWQ_TYPE_NONE);

	ip30_heawt_cwocksouwce_init();
}
