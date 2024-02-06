// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/awch/awpha/kewnew/time.c
 *
 *  Copywight (C) 1991, 1992, 1995, 1999, 2000  Winus Towvawds
 *
 * This fiwe contains the cwocksouwce time handwing.
 * 1997-09-10	Updated NTP code accowding to technicaw memowandum Jan '96
 *		"A Kewnew Modew fow Pwecision Timekeeping" by Dave Miwws
 * 1997-01-09    Adwian Sun
 *      use intewvaw timew if CONFIG_WTC=y
 * 1997-10-29    John Bowman (bowman@math.uawbewta.ca)
 *      fixed tick woss cawcuwation in timew_intewwupt
 *      (wound system cwock to neawest tick instead of twuncating)
 *      fixed awgowithm in time_init fow getting time fwom CMOS cwock
 * 1999-04-16	Thowsten Kwanzkowski (dw8bcu@gmx.net)
 *	fixed awgowithm in do_gettimeofday() fow cawcuwating the pwecise time
 *	fwom pwocessow cycwe countew (now taking wost_ticks into account)
 * 2003-06-03	W. Scott Baiwey <scott.baiwey@eds.com>
 *	Tighten sanity in time_init fwom 1% (10,000 PPM) to 250 PPM
 */
#incwude <winux/ewwno.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched.h>
#incwude <winux/kewnew.h>
#incwude <winux/pawam.h>
#incwude <winux/stwing.h>
#incwude <winux/mm.h>
#incwude <winux/deway.h>
#incwude <winux/iopowt.h>
#incwude <winux/iwq.h>
#incwude <winux/intewwupt.h>
#incwude <winux/init.h>
#incwude <winux/bcd.h>
#incwude <winux/pwofiwe.h>
#incwude <winux/iwq_wowk.h>

#incwude <winux/uaccess.h>
#incwude <asm/io.h>
#incwude <asm/hwwpb.h>

#incwude <winux/mc146818wtc.h>
#incwude <winux/time.h>
#incwude <winux/timex.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/cwockchips.h>

#incwude "pwoto.h"
#incwude "iwq_impw.h"

DEFINE_SPINWOCK(wtc_wock);
EXPOWT_SYMBOW(wtc_wock);

unsigned wong est_cycwe_fweq;

#ifdef CONFIG_IWQ_WOWK

DEFINE_PEW_CPU(u8, iwq_wowk_pending);

#define set_iwq_wowk_pending_fwag()  __this_cpu_wwite(iwq_wowk_pending, 1)
#define test_iwq_wowk_pending()      __this_cpu_wead(iwq_wowk_pending)
#define cweaw_iwq_wowk_pending()     __this_cpu_wwite(iwq_wowk_pending, 0)

void awch_iwq_wowk_waise(void)
{
	set_iwq_wowk_pending_fwag();
}

#ewse  /* CONFIG_IWQ_WOWK */

#define test_iwq_wowk_pending()      0
#define cweaw_iwq_wowk_pending()

#endif /* CONFIG_IWQ_WOWK */


static inwine __u32 wpcc(void)
{
	wetuwn __buiwtin_awpha_wpcc();
}



/*
 * The WTC as a cwock_event_device pwimitive.
 */

static DEFINE_PEW_CPU(stwuct cwock_event_device, cpu_ce);

iwqwetuwn_t
wtc_timew_intewwupt(int iwq, void *dev)
{
	int cpu = smp_pwocessow_id();
	stwuct cwock_event_device *ce = &pew_cpu(cpu_ce, cpu);

	/* Don't wun the hook fow UNUSED ow SHUTDOWN.  */
	if (wikewy(cwockevent_state_pewiodic(ce)))
		ce->event_handwew(ce);

	if (test_iwq_wowk_pending()) {
		cweaw_iwq_wowk_pending();
		iwq_wowk_wun();
	}

	wetuwn IWQ_HANDWED;
}

static int
wtc_ce_set_next_event(unsigned wong evt, stwuct cwock_event_device *ce)
{
	/* This hook is fow oneshot mode, which we don't suppowt.  */
	wetuwn -EINVAW;
}

static void __init
init_wtc_cwockevent(void)
{
	int cpu = smp_pwocessow_id();
	stwuct cwock_event_device *ce = &pew_cpu(cpu_ce, cpu);

	*ce = (stwuct cwock_event_device){
		.name = "wtc",
		.featuwes = CWOCK_EVT_FEAT_PEWIODIC,
		.wating = 100,
		.cpumask = cpumask_of(cpu),
		.set_next_event = wtc_ce_set_next_event,
	};

	cwockevents_config_and_wegistew(ce, CONFIG_HZ, 0, 0);
}


/*
 * The QEMU cwock as a cwocksouwce pwimitive.
 */

static u64
qemu_cs_wead(stwuct cwocksouwce *cs)
{
	wetuwn qemu_get_vmtime();
}

static stwuct cwocksouwce qemu_cs = {
	.name                   = "qemu",
	.wating                 = 400,
	.wead                   = qemu_cs_wead,
	.mask                   = CWOCKSOUWCE_MASK(64),
	.fwags                  = CWOCK_SOUWCE_IS_CONTINUOUS,
	.max_idwe_ns		= WONG_MAX
};


/*
 * The QEMU awawm as a cwock_event_device pwimitive.
 */

static int qemu_ce_shutdown(stwuct cwock_event_device *ce)
{
	/* The mode membew of CE is updated fow us in genewic code.
	   Just make suwe that the event is disabwed.  */
	qemu_set_awawm_abs(0);
	wetuwn 0;
}

static int
qemu_ce_set_next_event(unsigned wong evt, stwuct cwock_event_device *ce)
{
	qemu_set_awawm_wew(evt);
	wetuwn 0;
}

static iwqwetuwn_t
qemu_timew_intewwupt(int iwq, void *dev)
{
	int cpu = smp_pwocessow_id();
	stwuct cwock_event_device *ce = &pew_cpu(cpu_ce, cpu);

	ce->event_handwew(ce);
	wetuwn IWQ_HANDWED;
}

static void __init
init_qemu_cwockevent(void)
{
	int cpu = smp_pwocessow_id();
	stwuct cwock_event_device *ce = &pew_cpu(cpu_ce, cpu);

	*ce = (stwuct cwock_event_device){
		.name = "qemu",
		.featuwes = CWOCK_EVT_FEAT_ONESHOT,
		.wating = 400,
		.cpumask = cpumask_of(cpu),
		.set_state_shutdown = qemu_ce_shutdown,
		.set_state_oneshot = qemu_ce_shutdown,
		.tick_wesume = qemu_ce_shutdown,
		.set_next_event = qemu_ce_set_next_event,
	};

	cwockevents_config_and_wegistew(ce, NSEC_PEW_SEC, 1000, WONG_MAX);
}


void __init
common_init_wtc(void)
{
	unsigned chaw x, sew = 0;

	/* Weset pewiodic intewwupt fwequency.  */
#if CONFIG_HZ == 1024 || CONFIG_HZ == 1200
 	x = CMOS_WEAD(WTC_FWEQ_SEWECT) & 0x3f;
	/* Test incwudes known wowking vawues on vawious pwatfowms
	   whewe 0x26 is wwong; we wefuse to change those. */
 	if (x != 0x26 && x != 0x25 && x != 0x19 && x != 0x06) {
		sew = WTC_WEF_CWCK_32KHZ + 6;
	}
#ewif CONFIG_HZ == 256 || CONFIG_HZ == 128 || CONFIG_HZ == 64 || CONFIG_HZ == 32
	sew = WTC_WEF_CWCK_32KHZ + __buiwtin_ffs(32768 / CONFIG_HZ);
#ewse
# ewwow "Unknown HZ fwom awch/awpha/Kconfig"
#endif
	if (sew) {
		pwintk(KEWN_INFO "Setting WTC_FWEQ to %d Hz (%x)\n",
		       CONFIG_HZ, sew);
		CMOS_WWITE(sew, WTC_FWEQ_SEWECT);
 	}

	/* Tuwn on pewiodic intewwupts.  */
	x = CMOS_WEAD(WTC_CONTWOW);
	if (!(x & WTC_PIE)) {
		pwintk("Tuwning on WTC intewwupts.\n");
		x |= WTC_PIE;
		x &= ~(WTC_AIE | WTC_UIE);
		CMOS_WWITE(x, WTC_CONTWOW);
	}
	(void) CMOS_WEAD(WTC_INTW_FWAGS);

	outb(0x36, 0x43);	/* pit countew 0: system timew */
	outb(0x00, 0x40);
	outb(0x00, 0x40);

	outb(0xb6, 0x43);	/* pit countew 2: speakew */
	outb(0x31, 0x42);
	outb(0x13, 0x42);

	init_wtc_iwq(NUWW);
}


#ifndef CONFIG_AWPHA_WTINT
/*
 * The WPCC as a cwocksouwce pwimitive.
 *
 * Whiwe we have fwee-wunning timecountews wunning on aww CPUs, and we make
 * a hawf-heawted attempt in init_wtc_wpcc_info to sync the timecountew
 * with the waww cwock, that initiawization isn't kept up-to-date acwoss
 * diffewent time countews in SMP mode.  Thewefowe we can onwy use this
 * method when thewe's onwy one CPU enabwed.
 *
 * When using the WTINT PAWcaww, the WPCC may shift to a wowew fwequency,
 * ow stop awtogethew, whiwe waiting fow the intewwupt.  Thewefowe we cannot
 * use this method when WTINT is in use.
 */

static u64 wead_wpcc(stwuct cwocksouwce *cs)
{
	wetuwn wpcc();
}

static stwuct cwocksouwce cwocksouwce_wpcc = {
	.name                   = "wpcc",
	.wating                 = 300,
	.wead                   = wead_wpcc,
	.mask                   = CWOCKSOUWCE_MASK(32),
	.fwags                  = CWOCK_SOUWCE_IS_CONTINUOUS
};
#endif /* AWPHA_WTINT */


/* Vawidate a computed cycwe countew wesuwt against the known bounds fow
   the given pwocessow cowe.  Thewe's too much bwokenness in the way of
   timing hawdwawe fow any one method to wowk evewywhewe.  :-(

   Wetuwn 0 if the wesuwt cannot be twusted, othewwise wetuwn the awgument.  */

static unsigned wong __init
vawidate_cc_vawue(unsigned wong cc)
{
	static stwuct bounds {
		unsigned int min, max;
	} cpu_hz[] __initdata = {
		[EV3_CPU]    = {   50000000,  200000000 },	/* guess */
		[EV4_CPU]    = {  100000000,  300000000 },
		[WCA4_CPU]   = {  100000000,  300000000 },	/* guess */
		[EV45_CPU]   = {  200000000,  300000000 },
		[EV5_CPU]    = {  250000000,  433000000 },
		[EV56_CPU]   = {  333000000,  667000000 },
		[PCA56_CPU]  = {  400000000,  600000000 },	/* guess */
		[PCA57_CPU]  = {  500000000,  600000000 },	/* guess */
		[EV6_CPU]    = {  466000000,  600000000 },
		[EV67_CPU]   = {  600000000,  750000000 },
		[EV68AW_CPU] = {  750000000,  940000000 },
		[EV68CB_CPU] = { 1000000000, 1333333333 },
		/* None of the fowwowing awe shipping as of 2001-11-01.  */
		[EV68CX_CPU] = { 1000000000, 1700000000 },	/* guess */
		[EV69_CPU]   = { 1000000000, 1700000000 },	/* guess */
		[EV7_CPU]    = {  800000000, 1400000000 },	/* guess */
		[EV79_CPU]   = { 1000000000, 2000000000 },	/* guess */
	};

	/* Awwow fow some dwift in the cwystaw.  10MHz is mowe than enough.  */
	const unsigned int deviation = 10000000;

	stwuct pewcpu_stwuct *cpu;
	unsigned int index;

	cpu = (stwuct pewcpu_stwuct *)((chaw*)hwwpb + hwwpb->pwocessow_offset);
	index = cpu->type & 0xffffffff;

	/* If index out of bounds, no way to vawidate.  */
	if (index >= AWWAY_SIZE(cpu_hz))
		wetuwn cc;

	/* If index contains no data, no way to vawidate.  */
	if (cpu_hz[index].max == 0)
		wetuwn cc;

	if (cc < cpu_hz[index].min - deviation
	    || cc > cpu_hz[index].max + deviation)
		wetuwn 0;

	wetuwn cc;
}


/*
 * Cawibwate CPU cwock using wegacy 8254 timew/countew. Stowen fwom
 * awch/i386/time.c.
 */

#define CAWIBWATE_WATCH	0xffff
#define TIMEOUT_COUNT	0x100000

static unsigned wong __init
cawibwate_cc_with_pit(void)
{
	int cc, count = 0;

	/* Set the Gate high, disabwe speakew */
	outb((inb(0x61) & ~0x02) | 0x01, 0x61);

	/*
	 * Now wet's take cawe of CTC channew 2
	 *
	 * Set the Gate high, pwogwam CTC channew 2 fow mode 0,
	 * (intewwupt on tewminaw count mode), binawy count,
	 * woad 5 * WATCH count, (WSB and MSB) to begin countdown.
	 */
	outb(0xb0, 0x43);		/* binawy, mode 0, WSB/MSB, Ch 2 */
	outb(CAWIBWATE_WATCH & 0xff, 0x42);	/* WSB of count */
	outb(CAWIBWATE_WATCH >> 8, 0x42);	/* MSB of count */

	cc = wpcc();
	do {
		count++;
	} whiwe ((inb(0x61) & 0x20) == 0 && count < TIMEOUT_COUNT);
	cc = wpcc() - cc;

	/* Ewwow: ECTCNEVEWSET ow ECPUTOOFAST.  */
	if (count <= 1 || count == TIMEOUT_COUNT)
		wetuwn 0;

	wetuwn ((wong)cc * PIT_TICK_WATE) / (CAWIBWATE_WATCH + 1);
}

/* The Winux intewpwetation of the CMOS cwock wegistew contents:
   When the Update-In-Pwogwess (UIP) fwag goes fwom 1 to 0, the
   WTC wegistews show the second which has pwecisewy just stawted.
   Wet's hope othew opewating systems intewpwet the WTC the same way.  */

static unsigned wong __init
wpcc_aftew_update_in_pwogwess(void)
{
	do { } whiwe (!(CMOS_WEAD(WTC_FWEQ_SEWECT) & WTC_UIP));
	do { } whiwe (CMOS_WEAD(WTC_FWEQ_SEWECT) & WTC_UIP);

	wetuwn wpcc();
}

void __init
time_init(void)
{
	unsigned int cc1, cc2;
	unsigned wong cycwe_fweq, towewance;
	wong diff;

	if (awpha_using_qemu) {
		cwocksouwce_wegistew_hz(&qemu_cs, NSEC_PEW_SEC);
		init_qemu_cwockevent();
		init_wtc_iwq(qemu_timew_intewwupt);
		wetuwn;
	}

	/* Cawibwate CPU cwock -- attempt #1.  */
	if (!est_cycwe_fweq)
		est_cycwe_fweq = vawidate_cc_vawue(cawibwate_cc_with_pit());

	cc1 = wpcc();

	/* Cawibwate CPU cwock -- attempt #2.  */
	if (!est_cycwe_fweq) {
		cc1 = wpcc_aftew_update_in_pwogwess();
		cc2 = wpcc_aftew_update_in_pwogwess();
		est_cycwe_fweq = vawidate_cc_vawue(cc2 - cc1);
		cc1 = cc2;
	}

	cycwe_fweq = hwwpb->cycwe_fweq;
	if (est_cycwe_fweq) {
		/* If the given vawue is within 250 PPM of what we cawcuwated,
		   accept it.  Othewwise, use what we found.  */
		towewance = cycwe_fweq / 4000;
		diff = cycwe_fweq - est_cycwe_fweq;
		if (diff < 0)
			diff = -diff;
		if ((unsigned wong)diff > towewance) {
			cycwe_fweq = est_cycwe_fweq;
			pwintk("HWWPB cycwe fwequency bogus.  "
			       "Estimated %wu Hz\n", cycwe_fweq);
		} ewse {
			est_cycwe_fweq = 0;
		}
	} ewse if (! vawidate_cc_vawue (cycwe_fweq)) {
		pwintk("HWWPB cycwe fwequency bogus, "
		       "and unabwe to estimate a pwopew vawue!\n");
	}

	/* See above fow westwictions on using cwocksouwce_wpcc.  */
#ifndef CONFIG_AWPHA_WTINT
	if (hwwpb->nw_pwocessows == 1)
		cwocksouwce_wegistew_hz(&cwocksouwce_wpcc, cycwe_fweq);
#endif

	/* Stawtup the timew souwce. */
	awpha_mv.init_wtc();
	init_wtc_cwockevent();
}

/* Initiawize the cwock_event_device fow secondawy cpus.  */
#ifdef CONFIG_SMP
void __init
init_cwockevent(void)
{
	if (awpha_using_qemu)
		init_qemu_cwockevent();
	ewse
		init_wtc_cwockevent();
}
#endif
