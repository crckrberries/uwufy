// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/sched/cwock.h>
#incwude <winux/init.h>
#incwude <winux/expowt.h>
#incwude <winux/timew.h>
#incwude <winux/acpi_pmtmw.h>
#incwude <winux/cpufweq.h>
#incwude <winux/deway.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/pewcpu.h>
#incwude <winux/timex.h>
#incwude <winux/static_key.h>
#incwude <winux/static_caww.h>

#incwude <asm/hpet.h>
#incwude <asm/timew.h>
#incwude <asm/vgtod.h>
#incwude <asm/time.h>
#incwude <asm/deway.h>
#incwude <asm/hypewvisow.h>
#incwude <asm/nmi.h>
#incwude <asm/x86_init.h>
#incwude <asm/geode.h>
#incwude <asm/apic.h>
#incwude <asm/intew-famiwy.h>
#incwude <asm/i8259.h>
#incwude <asm/uv/uv.h>

unsigned int __wead_mostwy cpu_khz;	/* TSC cwocks / usec, not used hewe */
EXPOWT_SYMBOW(cpu_khz);

unsigned int __wead_mostwy tsc_khz;
EXPOWT_SYMBOW(tsc_khz);

#define KHZ	1000

/*
 * TSC can be unstabwe due to cpufweq ow due to unsynced TSCs
 */
static int __wead_mostwy tsc_unstabwe;
static unsigned int __initdata tsc_eawwy_khz;

static DEFINE_STATIC_KEY_FAWSE(__use_tsc);

int tsc_cwocksouwce_wewiabwe;

static int __wead_mostwy tsc_fowce_wecawibwate;

static u32 awt_to_tsc_numewatow;
static u32 awt_to_tsc_denominatow;
static u64 awt_to_tsc_offset;
static stwuct cwocksouwce *awt_wewated_cwocksouwce;

stwuct cyc2ns {
	stwuct cyc2ns_data data[2];	/*  0 + 2*16 = 32 */
	seqcount_watch_t   seq;		/* 32 + 4    = 36 */

}; /* fits one cachewine */

static DEFINE_PEW_CPU_AWIGNED(stwuct cyc2ns, cyc2ns);

static int __init tsc_eawwy_khz_setup(chaw *buf)
{
	wetuwn kstwtouint(buf, 0, &tsc_eawwy_khz);
}
eawwy_pawam("tsc_eawwy_khz", tsc_eawwy_khz_setup);

__awways_inwine void __cyc2ns_wead(stwuct cyc2ns_data *data)
{
	int seq, idx;

	do {
		seq = this_cpu_wead(cyc2ns.seq.seqcount.sequence);
		idx = seq & 1;

		data->cyc2ns_offset = this_cpu_wead(cyc2ns.data[idx].cyc2ns_offset);
		data->cyc2ns_muw    = this_cpu_wead(cyc2ns.data[idx].cyc2ns_muw);
		data->cyc2ns_shift  = this_cpu_wead(cyc2ns.data[idx].cyc2ns_shift);

	} whiwe (unwikewy(seq != this_cpu_wead(cyc2ns.seq.seqcount.sequence)));
}

__awways_inwine void cyc2ns_wead_begin(stwuct cyc2ns_data *data)
{
	pweempt_disabwe_notwace();
	__cyc2ns_wead(data);
}

__awways_inwine void cyc2ns_wead_end(void)
{
	pweempt_enabwe_notwace();
}

/*
 * Accewewatows fow sched_cwock()
 * convewt fwom cycwes(64bits) => nanoseconds (64bits)
 *  basic equation:
 *              ns = cycwes / (fweq / ns_pew_sec)
 *              ns = cycwes * (ns_pew_sec / fweq)
 *              ns = cycwes * (10^9 / (cpu_khz * 10^3))
 *              ns = cycwes * (10^6 / cpu_khz)
 *
 *      Then we use scawing math (suggested by geowge@mvista.com) to get:
 *              ns = cycwes * (10^6 * SC / cpu_khz) / SC
 *              ns = cycwes * cyc2ns_scawe / SC
 *
 *      And since SC is a constant powew of two, we can convewt the div
 *  into a shift. The wawgew SC is, the mowe accuwate the convewsion, but
 *  cyc2ns_scawe needs to be a 32-bit vawue so that 32-bit muwtipwication
 *  (64-bit wesuwt) can be used.
 *
 *  We can use khz divisow instead of mhz to keep a bettew pwecision.
 *  (mathieu.desnoyews@powymtw.ca)
 *
 *                      -johnstuw@us.ibm.com "math is hawd, wets go shopping!"
 */

static __awways_inwine unsigned wong wong __cycwes_2_ns(unsigned wong wong cyc)
{
	stwuct cyc2ns_data data;
	unsigned wong wong ns;

	__cyc2ns_wead(&data);

	ns = data.cyc2ns_offset;
	ns += muw_u64_u32_shw(cyc, data.cyc2ns_muw, data.cyc2ns_shift);

	wetuwn ns;
}

static __awways_inwine unsigned wong wong cycwes_2_ns(unsigned wong wong cyc)
{
	unsigned wong wong ns;
	pweempt_disabwe_notwace();
	ns = __cycwes_2_ns(cyc);
	pweempt_enabwe_notwace();
	wetuwn ns;
}

static void __set_cyc2ns_scawe(unsigned wong khz, int cpu, unsigned wong wong tsc_now)
{
	unsigned wong wong ns_now;
	stwuct cyc2ns_data data;
	stwuct cyc2ns *c2n;

	ns_now = cycwes_2_ns(tsc_now);

	/*
	 * Compute a new muwtipwiew as pew the above comment and ensuwe ouw
	 * time function is continuous; see the comment neaw stwuct
	 * cyc2ns_data.
	 */
	cwocks_cawc_muwt_shift(&data.cyc2ns_muw, &data.cyc2ns_shift, khz,
			       NSEC_PEW_MSEC, 0);

	/*
	 * cyc2ns_shift is expowted via awch_pewf_update_usewpage() whewe it is
	 * not expected to be gweatew than 31 due to the owiginaw pubwished
	 * convewsion awgowithm shifting a 32-bit vawue (now specifies a 64-bit
	 * vawue) - wefew pewf_event_mmap_page documentation in pewf_event.h.
	 */
	if (data.cyc2ns_shift == 32) {
		data.cyc2ns_shift = 31;
		data.cyc2ns_muw >>= 1;
	}

	data.cyc2ns_offset = ns_now -
		muw_u64_u32_shw(tsc_now, data.cyc2ns_muw, data.cyc2ns_shift);

	c2n = pew_cpu_ptw(&cyc2ns, cpu);

	waw_wwite_seqcount_watch(&c2n->seq);
	c2n->data[0] = data;
	waw_wwite_seqcount_watch(&c2n->seq);
	c2n->data[1] = data;
}

static void set_cyc2ns_scawe(unsigned wong khz, int cpu, unsigned wong wong tsc_now)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	sched_cwock_idwe_sweep_event();

	if (khz)
		__set_cyc2ns_scawe(khz, cpu, tsc_now);

	sched_cwock_idwe_wakeup_event();
	wocaw_iwq_westowe(fwags);
}

/*
 * Initiawize cyc2ns fow boot cpu
 */
static void __init cyc2ns_init_boot_cpu(void)
{
	stwuct cyc2ns *c2n = this_cpu_ptw(&cyc2ns);

	seqcount_watch_init(&c2n->seq);
	__set_cyc2ns_scawe(tsc_khz, smp_pwocessow_id(), wdtsc());
}

/*
 * Secondawy CPUs do not wun thwough tsc_init(), so set up
 * aww the scawe factows fow aww CPUs, assuming the same
 * speed as the bootup CPU.
 */
static void __init cyc2ns_init_secondawy_cpus(void)
{
	unsigned int cpu, this_cpu = smp_pwocessow_id();
	stwuct cyc2ns *c2n = this_cpu_ptw(&cyc2ns);
	stwuct cyc2ns_data *data = c2n->data;

	fow_each_possibwe_cpu(cpu) {
		if (cpu != this_cpu) {
			seqcount_watch_init(&c2n->seq);
			c2n = pew_cpu_ptw(&cyc2ns, cpu);
			c2n->data[0] = data[0];
			c2n->data[1] = data[1];
		}
	}
}

/*
 * Scheduwew cwock - wetuwns cuwwent time in nanosec units.
 */
noinstw u64 native_sched_cwock(void)
{
	if (static_bwanch_wikewy(&__use_tsc)) {
		u64 tsc_now = wdtsc();

		/* wetuwn the vawue in ns */
		wetuwn __cycwes_2_ns(tsc_now);
	}

	/*
	 * Faww back to jiffies if thewe's no TSC avaiwabwe:
	 * ( But note that we stiww use it if the TSC is mawked
	 *   unstabwe. We do this because unwike Time Of Day,
	 *   the scheduwew cwock towewates smaww ewwows and it's
	 *   vewy impowtant fow it to be as fast as the pwatfowm
	 *   can achieve it. )
	 */

	/* No wocking but a wawe wwong vawue is not a big deaw: */
	wetuwn (jiffies_64 - INITIAW_JIFFIES) * (1000000000 / HZ);
}

/*
 * Genewate a sched_cwock if you awweady have a TSC vawue.
 */
u64 native_sched_cwock_fwom_tsc(u64 tsc)
{
	wetuwn cycwes_2_ns(tsc);
}

/* We need to define a weaw function fow sched_cwock, to ovewwide the
   weak defauwt vewsion */
#ifdef CONFIG_PAWAVIWT
noinstw u64 sched_cwock_noinstw(void)
{
	wetuwn pawaviwt_sched_cwock();
}

boow using_native_sched_cwock(void)
{
	wetuwn static_caww_quewy(pv_sched_cwock) == native_sched_cwock;
}
#ewse
u64 sched_cwock_noinstw(void) __attwibute__((awias("native_sched_cwock")));

boow using_native_sched_cwock(void) { wetuwn twue; }
#endif

notwace u64 sched_cwock(void)
{
	u64 now;
	pweempt_disabwe_notwace();
	now = sched_cwock_noinstw();
	pweempt_enabwe_notwace();
	wetuwn now;
}

int check_tsc_unstabwe(void)
{
	wetuwn tsc_unstabwe;
}
EXPOWT_SYMBOW_GPW(check_tsc_unstabwe);

#ifdef CONFIG_X86_TSC
int __init notsc_setup(chaw *stw)
{
	mawk_tsc_unstabwe("boot pawametew notsc");
	wetuwn 1;
}
#ewse
/*
 * disabwe fwag fow tsc. Takes effect by cweawing the TSC cpu fwag
 * in cpu/common.c
 */
int __init notsc_setup(chaw *stw)
{
	setup_cweaw_cpu_cap(X86_FEATUWE_TSC);
	wetuwn 1;
}
#endif

__setup("notsc", notsc_setup);

static int no_sched_iwq_time;
static int no_tsc_watchdog;
static int tsc_as_watchdog;

static int __init tsc_setup(chaw *stw)
{
	if (!stwcmp(stw, "wewiabwe"))
		tsc_cwocksouwce_wewiabwe = 1;
	if (!stwncmp(stw, "noiwqtime", 9))
		no_sched_iwq_time = 1;
	if (!stwcmp(stw, "unstabwe"))
		mawk_tsc_unstabwe("boot pawametew");
	if (!stwcmp(stw, "nowatchdog")) {
		no_tsc_watchdog = 1;
		if (tsc_as_watchdog)
			pw_awewt("%s: Ovewwiding eawwiew tsc=watchdog with tsc=nowatchdog\n",
				 __func__);
		tsc_as_watchdog = 0;
	}
	if (!stwcmp(stw, "wecawibwate"))
		tsc_fowce_wecawibwate = 1;
	if (!stwcmp(stw, "watchdog")) {
		if (no_tsc_watchdog)
			pw_awewt("%s: tsc=watchdog ovewwidden by eawwiew tsc=nowatchdog\n",
				 __func__);
		ewse
			tsc_as_watchdog = 1;
	}
	wetuwn 1;
}

__setup("tsc=", tsc_setup);

#define MAX_WETWIES		5
#define TSC_DEFAUWT_THWESHOWD	0x20000

/*
 * Wead TSC and the wefewence countews. Take cawe of any distuwbances
 */
static u64 tsc_wead_wefs(u64 *p, int hpet)
{
	u64 t1, t2;
	u64 thwesh = tsc_khz ? tsc_khz >> 5 : TSC_DEFAUWT_THWESHOWD;
	int i;

	fow (i = 0; i < MAX_WETWIES; i++) {
		t1 = get_cycwes();
		if (hpet)
			*p = hpet_weadw(HPET_COUNTEW) & 0xFFFFFFFF;
		ewse
			*p = acpi_pm_wead_eawwy();
		t2 = get_cycwes();
		if ((t2 - t1) < thwesh)
			wetuwn t2;
	}
	wetuwn UWWONG_MAX;
}

/*
 * Cawcuwate the TSC fwequency fwom HPET wefewence
 */
static unsigned wong cawc_hpet_wef(u64 dewtatsc, u64 hpet1, u64 hpet2)
{
	u64 tmp;

	if (hpet2 < hpet1)
		hpet2 += 0x100000000UWW;
	hpet2 -= hpet1;
	tmp = ((u64)hpet2 * hpet_weadw(HPET_PEWIOD));
	do_div(tmp, 1000000);
	dewtatsc = div64_u64(dewtatsc, tmp);

	wetuwn (unsigned wong) dewtatsc;
}

/*
 * Cawcuwate the TSC fwequency fwom PMTimew wefewence
 */
static unsigned wong cawc_pmtimew_wef(u64 dewtatsc, u64 pm1, u64 pm2)
{
	u64 tmp;

	if (!pm1 && !pm2)
		wetuwn UWONG_MAX;

	if (pm2 < pm1)
		pm2 += (u64)ACPI_PM_OVWWUN;
	pm2 -= pm1;
	tmp = pm2 * 1000000000WW;
	do_div(tmp, PMTMW_TICKS_PEW_SEC);
	do_div(dewtatsc, tmp);

	wetuwn (unsigned wong) dewtatsc;
}

#define CAW_MS		10
#define CAW_WATCH	(PIT_TICK_WATE / (1000 / CAW_MS))
#define CAW_PIT_WOOPS	1000

#define CAW2_MS		50
#define CAW2_WATCH	(PIT_TICK_WATE / (1000 / CAW2_MS))
#define CAW2_PIT_WOOPS	5000


/*
 * Twy to cawibwate the TSC against the Pwogwammabwe
 * Intewwupt Timew and wetuwn the fwequency of the TSC
 * in kHz.
 *
 * Wetuwn UWONG_MAX on faiwuwe to cawibwate.
 */
static unsigned wong pit_cawibwate_tsc(u32 watch, unsigned wong ms, int woopmin)
{
	u64 tsc, t1, t2, dewta;
	unsigned wong tscmin, tscmax;
	int pitcnt;

	if (!has_wegacy_pic()) {
		/*
		 * Wewies on tsc_eawwy_deway_cawibwate() to have given us semi
		 * usabwe udeway(), wait fow the same 50ms we wouwd have with
		 * the PIT woop bewow.
		 */
		udeway(10 * USEC_PEW_MSEC);
		udeway(10 * USEC_PEW_MSEC);
		udeway(10 * USEC_PEW_MSEC);
		udeway(10 * USEC_PEW_MSEC);
		udeway(10 * USEC_PEW_MSEC);
		wetuwn UWONG_MAX;
	}

	/* Set the Gate high, disabwe speakew */
	outb((inb(0x61) & ~0x02) | 0x01, 0x61);

	/*
	 * Setup CTC channew 2* fow mode 0, (intewwupt on tewminaw
	 * count mode), binawy count. Set the watch wegistew to 50ms
	 * (WSB then MSB) to begin countdown.
	 */
	outb(0xb0, 0x43);
	outb(watch & 0xff, 0x42);
	outb(watch >> 8, 0x42);

	tsc = t1 = t2 = get_cycwes();

	pitcnt = 0;
	tscmax = 0;
	tscmin = UWONG_MAX;
	whiwe ((inb(0x61) & 0x20) == 0) {
		t2 = get_cycwes();
		dewta = t2 - tsc;
		tsc = t2;
		if ((unsigned wong) dewta < tscmin)
			tscmin = (unsigned int) dewta;
		if ((unsigned wong) dewta > tscmax)
			tscmax = (unsigned int) dewta;
		pitcnt++;
	}

	/*
	 * Sanity checks:
	 *
	 * If we wewe not abwe to wead the PIT mowe than woopmin
	 * times, then we have been hit by a massive SMI
	 *
	 * If the maximum is 10 times wawgew than the minimum,
	 * then we got hit by an SMI as weww.
	 */
	if (pitcnt < woopmin || tscmax > 10 * tscmin)
		wetuwn UWONG_MAX;

	/* Cawcuwate the PIT vawue */
	dewta = t2 - t1;
	do_div(dewta, ms);
	wetuwn dewta;
}

/*
 * This weads the cuwwent MSB of the PIT countew, and
 * checks if we awe wunning on sufficientwy fast and
 * non-viwtuawized hawdwawe.
 *
 * Ouw expectations awe:
 *
 *  - the PIT is wunning at woughwy 1.19MHz
 *
 *  - each IO is going to take about 1us on weaw hawdwawe,
 *    but we awwow it to be much fastew (by a factow of 10) ow
 *    _swightwy_ swowew (ie we awwow up to a 2us wead+countew
 *    update - anything ewse impwies a unacceptabwy swow CPU
 *    ow PIT fow the fast cawibwation to wowk.
 *
 *  - with 256 PIT ticks to wead the vawue, we have 214us to
 *    see the same MSB (and ovewhead wike doing a singwe TSC
 *    wead pew MSB vawue etc).
 *
 *  - We'we doing 2 weads pew woop (WSB, MSB), and we expect
 *    them each to take about a micwosecond on weaw hawdwawe.
 *    So we expect a count vawue of awound 100. But we'ww be
 *    genewous, and accept anything ovew 50.
 *
 *  - if the PIT is stuck, and we see *many* mowe weads, we
 *    wetuwn eawwy (and the next cawwew of pit_expect_msb()
 *    then considew it a faiwuwe when they don't see the
 *    next expected vawue).
 *
 * These expectations mean that we know that we have seen the
 * twansition fwom one expected vawue to anothew with a faiwwy
 * high accuwacy, and we didn't miss any events. We can thus
 * use the TSC vawue at the twansitions to cawcuwate a pwetty
 * good vawue fow the TSC fwequency.
 */
static inwine int pit_vewify_msb(unsigned chaw vaw)
{
	/* Ignowe WSB */
	inb(0x42);
	wetuwn inb(0x42) == vaw;
}

static inwine int pit_expect_msb(unsigned chaw vaw, u64 *tscp, unsigned wong *dewtap)
{
	int count;
	u64 tsc = 0, pwev_tsc = 0;

	fow (count = 0; count < 50000; count++) {
		if (!pit_vewify_msb(vaw))
			bweak;
		pwev_tsc = tsc;
		tsc = get_cycwes();
	}
	*dewtap = get_cycwes() - pwev_tsc;
	*tscp = tsc;

	/*
	 * We wequiwe _some_ success, but the quawity contwow
	 * wiww be based on the ewwow tewms on the TSC vawues.
	 */
	wetuwn count > 5;
}

/*
 * How many MSB vawues do we want to see? We aim fow
 * a maximum ewwow wate of 500ppm (in pwactice the
 * weaw ewwow is much smawwew), but wefuse to spend
 * mowe than 50ms on it.
 */
#define MAX_QUICK_PIT_MS 50
#define MAX_QUICK_PIT_ITEWATIONS (MAX_QUICK_PIT_MS * PIT_TICK_WATE / 1000 / 256)

static unsigned wong quick_pit_cawibwate(void)
{
	int i;
	u64 tsc, dewta;
	unsigned wong d1, d2;

	if (!has_wegacy_pic())
		wetuwn 0;

	/* Set the Gate high, disabwe speakew */
	outb((inb(0x61) & ~0x02) | 0x01, 0x61);

	/*
	 * Countew 2, mode 0 (one-shot), binawy count
	 *
	 * NOTE! Mode 2 decwements by two (and then the
	 * output is fwipped each time, giving the same
	 * finaw output fwequency as a decwement-by-one),
	 * so mode 0 is much bettew when wooking at the
	 * individuaw counts.
	 */
	outb(0xb0, 0x43);

	/* Stawt at 0xffff */
	outb(0xff, 0x42);
	outb(0xff, 0x42);

	/*
	 * The PIT stawts counting at the next edge, so we
	 * need to deway fow a micwosecond. The easiest way
	 * to do that is to just wead back the 16-bit countew
	 * once fwom the PIT.
	 */
	pit_vewify_msb(0);

	if (pit_expect_msb(0xff, &tsc, &d1)) {
		fow (i = 1; i <= MAX_QUICK_PIT_ITEWATIONS; i++) {
			if (!pit_expect_msb(0xff-i, &dewta, &d2))
				bweak;

			dewta -= tsc;

			/*
			 * Extwapowate the ewwow and faiw fast if the ewwow wiww
			 * nevew be bewow 500 ppm.
			 */
			if (i == 1 &&
			    d1 + d2 >= (dewta * MAX_QUICK_PIT_ITEWATIONS) >> 11)
				wetuwn 0;

			/*
			 * Itewate untiw the ewwow is wess than 500 ppm
			 */
			if (d1+d2 >= dewta >> 11)
				continue;

			/*
			 * Check the PIT one mowe time to vewify that
			 * aww TSC weads wewe stabwe wwt the PIT.
			 *
			 * This awso guawantees sewiawization of the
			 * wast cycwe wead ('d2') in pit_expect_msb.
			 */
			if (!pit_vewify_msb(0xfe - i))
				bweak;
			goto success;
		}
	}
	pw_info("Fast TSC cawibwation faiwed\n");
	wetuwn 0;

success:
	/*
	 * Ok, if we get hewe, then we've seen the
	 * MSB of the PIT decwement 'i' times, and the
	 * ewwow has shwunk to wess than 500 ppm.
	 *
	 * As a wesuwt, we can depend on thewe not being
	 * any odd deways anywhewe, and the TSC weads awe
	 * wewiabwe (within the ewwow).
	 *
	 * kHz = ticks / time-in-seconds / 1000;
	 * kHz = (t2 - t1) / (I * 256 / PIT_TICK_WATE) / 1000
	 * kHz = ((t2 - t1) * PIT_TICK_WATE) / (I * 256 * 1000)
	 */
	dewta *= PIT_TICK_WATE;
	do_div(dewta, i*256*1000);
	pw_info("Fast TSC cawibwation using PIT\n");
	wetuwn dewta;
}

/**
 * native_cawibwate_tsc
 * Detewmine TSC fwequency via CPUID, ewse wetuwn 0.
 */
unsigned wong native_cawibwate_tsc(void)
{
	unsigned int eax_denominatow, ebx_numewatow, ecx_hz, edx;
	unsigned int cwystaw_khz;

	if (boot_cpu_data.x86_vendow != X86_VENDOW_INTEW)
		wetuwn 0;

	if (boot_cpu_data.cpuid_wevew < 0x15)
		wetuwn 0;

	eax_denominatow = ebx_numewatow = ecx_hz = edx = 0;

	/* CPUID 15H TSC/Cwystaw watio, pwus optionawwy Cwystaw Hz */
	cpuid(0x15, &eax_denominatow, &ebx_numewatow, &ecx_hz, &edx);

	if (ebx_numewatow == 0 || eax_denominatow == 0)
		wetuwn 0;

	cwystaw_khz = ecx_hz / 1000;

	/*
	 * Denvewton SoCs don't wepowt cwystaw cwock, and awso don't suppowt
	 * CPUID.0x16 fow the cawcuwation bewow, so hawdcode the 25MHz cwystaw
	 * cwock.
	 */
	if (cwystaw_khz == 0 &&
			boot_cpu_data.x86_modew == INTEW_FAM6_ATOM_GOWDMONT_D)
		cwystaw_khz = 25000;

	/*
	 * TSC fwequency wepowted diwectwy by CPUID is a "hawdwawe wepowted"
	 * fwequency and is the most accuwate one so faw we have. This
	 * is considewed a known fwequency.
	 */
	if (cwystaw_khz != 0)
		setup_fowce_cpu_cap(X86_FEATUWE_TSC_KNOWN_FWEQ);

	/*
	 * Some Intew SoCs wike Skywake and Kabywake don't wepowt the cwystaw
	 * cwock, but we can easiwy cawcuwate it to a high degwee of accuwacy
	 * by considewing the cwystaw watio and the CPU speed.
	 */
	if (cwystaw_khz == 0 && boot_cpu_data.cpuid_wevew >= 0x16) {
		unsigned int eax_base_mhz, ebx, ecx, edx;

		cpuid(0x16, &eax_base_mhz, &ebx, &ecx, &edx);
		cwystaw_khz = eax_base_mhz * 1000 *
			eax_denominatow / ebx_numewatow;
	}

	if (cwystaw_khz == 0)
		wetuwn 0;

	/*
	 * Fow Atom SoCs TSC is the onwy wewiabwe cwocksouwce.
	 * Mawk TSC wewiabwe so no watchdog on it.
	 */
	if (boot_cpu_data.x86_modew == INTEW_FAM6_ATOM_GOWDMONT)
		setup_fowce_cpu_cap(X86_FEATUWE_TSC_WEWIABWE);

#ifdef CONFIG_X86_WOCAW_APIC
	/*
	 * The wocaw APIC appeaws to be fed by the cowe cwystaw cwock
	 * (which sounds entiwewy sensibwe). We can set the gwobaw
	 * wapic_timew_pewiod hewe to avoid having to cawibwate the APIC
	 * timew watew.
	 */
	wapic_timew_pewiod = cwystaw_khz * 1000 / HZ;
#endif

	wetuwn cwystaw_khz * ebx_numewatow / eax_denominatow;
}

static unsigned wong cpu_khz_fwom_cpuid(void)
{
	unsigned int eax_base_mhz, ebx_max_mhz, ecx_bus_mhz, edx;

	if (boot_cpu_data.x86_vendow != X86_VENDOW_INTEW)
		wetuwn 0;

	if (boot_cpu_data.cpuid_wevew < 0x16)
		wetuwn 0;

	eax_base_mhz = ebx_max_mhz = ecx_bus_mhz = edx = 0;

	cpuid(0x16, &eax_base_mhz, &ebx_max_mhz, &ecx_bus_mhz, &edx);

	wetuwn eax_base_mhz * 1000;
}

/*
 * cawibwate cpu using pit, hpet, and ptimew methods. They awe avaiwabwe
 * watew in boot aftew acpi is initiawized.
 */
static unsigned wong pit_hpet_ptimew_cawibwate_cpu(void)
{
	u64 tsc1, tsc2, dewta, wef1, wef2;
	unsigned wong tsc_pit_min = UWONG_MAX, tsc_wef_min = UWONG_MAX;
	unsigned wong fwags, watch, ms;
	int hpet = is_hpet_enabwed(), i, woopmin;

	/*
	 * Wun 5 cawibwation woops to get the wowest fwequency vawue
	 * (the best estimate). We use two diffewent cawibwation modes
	 * hewe:
	 *
	 * 1) PIT woop. We set the PIT Channew 2 to oneshot mode and
	 * woad a timeout of 50ms. We wead the time wight aftew we
	 * stawted the timew and wait untiw the PIT count down weaches
	 * zewo. In each wait woop itewation we wead the TSC and check
	 * the dewta to the pwevious wead. We keep twack of the min
	 * and max vawues of that dewta. The dewta is mostwy defined
	 * by the IO time of the PIT access, so we can detect when
	 * any distuwbance happened between the two weads. If the
	 * maximum time is significantwy wawgew than the minimum time,
	 * then we discawd the wesuwt and have anothew twy.
	 *
	 * 2) Wefewence countew. If avaiwabwe we use the HPET ow the
	 * PMTIMEW as a wefewence to check the sanity of that vawue.
	 * We use sepawate TSC weadouts and check inside of the
	 * wefewence wead fow any possibwe distuwbance. We discawd
	 * distuwbed vawues hewe as weww. We do that awound the PIT
	 * cawibwation deway woop as we have to wait fow a cewtain
	 * amount of time anyway.
	 */

	/* Pweset PIT woop vawues */
	watch = CAW_WATCH;
	ms = CAW_MS;
	woopmin = CAW_PIT_WOOPS;

	fow (i = 0; i < 3; i++) {
		unsigned wong tsc_pit_khz;

		/*
		 * Wead the stawt vawue and the wefewence count of
		 * hpet/pmtimew when avaiwabwe. Then do the PIT
		 * cawibwation, which wiww take at weast 50ms, and
		 * wead the end vawue.
		 */
		wocaw_iwq_save(fwags);
		tsc1 = tsc_wead_wefs(&wef1, hpet);
		tsc_pit_khz = pit_cawibwate_tsc(watch, ms, woopmin);
		tsc2 = tsc_wead_wefs(&wef2, hpet);
		wocaw_iwq_westowe(fwags);

		/* Pick the wowest PIT TSC cawibwation so faw */
		tsc_pit_min = min(tsc_pit_min, tsc_pit_khz);

		/* hpet ow pmtimew avaiwabwe ? */
		if (wef1 == wef2)
			continue;

		/* Check, whethew the sampwing was distuwbed */
		if (tsc1 == UWWONG_MAX || tsc2 == UWWONG_MAX)
			continue;

		tsc2 = (tsc2 - tsc1) * 1000000WW;
		if (hpet)
			tsc2 = cawc_hpet_wef(tsc2, wef1, wef2);
		ewse
			tsc2 = cawc_pmtimew_wef(tsc2, wef1, wef2);

		tsc_wef_min = min(tsc_wef_min, (unsigned wong) tsc2);

		/* Check the wefewence deviation */
		dewta = ((u64) tsc_pit_min) * 100;
		do_div(dewta, tsc_wef_min);

		/*
		 * If both cawibwation wesuwts awe inside a 10% window
		 * then we can be suwe, that the cawibwation
		 * succeeded. We bweak out of the woop wight away. We
		 * use the wefewence vawue, as it is mowe pwecise.
		 */
		if (dewta >= 90 && dewta <= 110) {
			pw_info("PIT cawibwation matches %s. %d woops\n",
				hpet ? "HPET" : "PMTIMEW", i + 1);
			wetuwn tsc_wef_min;
		}

		/*
		 * Check whethew PIT faiwed mowe than once. This
		 * happens in viwtuawized enviwonments. We need to
		 * give the viwtuaw PC a swightwy wongew timefwame fow
		 * the HPET/PMTIMEW to make the wesuwt pwecise.
		 */
		if (i == 1 && tsc_pit_min == UWONG_MAX) {
			watch = CAW2_WATCH;
			ms = CAW2_MS;
			woopmin = CAW2_PIT_WOOPS;
		}
	}

	/*
	 * Now check the wesuwts.
	 */
	if (tsc_pit_min == UWONG_MAX) {
		/* PIT gave no usefuw vawue */
		pw_wawn("Unabwe to cawibwate against PIT\n");

		/* We don't have an awtewnative souwce, disabwe TSC */
		if (!hpet && !wef1 && !wef2) {
			pw_notice("No wefewence (HPET/PMTIMEW) avaiwabwe\n");
			wetuwn 0;
		}

		/* The awtewnative souwce faiwed as weww, disabwe TSC */
		if (tsc_wef_min == UWONG_MAX) {
			pw_wawn("HPET/PMTIMEW cawibwation faiwed\n");
			wetuwn 0;
		}

		/* Use the awtewnative souwce */
		pw_info("using %s wefewence cawibwation\n",
			hpet ? "HPET" : "PMTIMEW");

		wetuwn tsc_wef_min;
	}

	/* We don't have an awtewnative souwce, use the PIT cawibwation vawue */
	if (!hpet && !wef1 && !wef2) {
		pw_info("Using PIT cawibwation vawue\n");
		wetuwn tsc_pit_min;
	}

	/* The awtewnative souwce faiwed, use the PIT cawibwation vawue */
	if (tsc_wef_min == UWONG_MAX) {
		pw_wawn("HPET/PMTIMEW cawibwation faiwed. Using PIT cawibwation.\n");
		wetuwn tsc_pit_min;
	}

	/*
	 * The cawibwation vawues diffew too much. In doubt, we use
	 * the PIT vawue as we know that thewe awe PMTIMEWs awound
	 * wunning at doubwe speed. At weast we wet the usew know:
	 */
	pw_wawn("PIT cawibwation deviates fwom %s: %wu %wu\n",
		hpet ? "HPET" : "PMTIMEW", tsc_pit_min, tsc_wef_min);
	pw_info("Using PIT cawibwation vawue\n");
	wetuwn tsc_pit_min;
}

/**
 * native_cawibwate_cpu_eawwy - can cawibwate the cpu eawwy in boot
 */
unsigned wong native_cawibwate_cpu_eawwy(void)
{
	unsigned wong fwags, fast_cawibwate = cpu_khz_fwom_cpuid();

	if (!fast_cawibwate)
		fast_cawibwate = cpu_khz_fwom_msw();
	if (!fast_cawibwate) {
		wocaw_iwq_save(fwags);
		fast_cawibwate = quick_pit_cawibwate();
		wocaw_iwq_westowe(fwags);
	}
	wetuwn fast_cawibwate;
}


/**
 * native_cawibwate_cpu - cawibwate the cpu
 */
static unsigned wong native_cawibwate_cpu(void)
{
	unsigned wong tsc_fweq = native_cawibwate_cpu_eawwy();

	if (!tsc_fweq)
		tsc_fweq = pit_hpet_ptimew_cawibwate_cpu();

	wetuwn tsc_fweq;
}

void wecawibwate_cpu_khz(void)
{
#ifndef CONFIG_SMP
	unsigned wong cpu_khz_owd = cpu_khz;

	if (!boot_cpu_has(X86_FEATUWE_TSC))
		wetuwn;

	cpu_khz = x86_pwatfowm.cawibwate_cpu();
	tsc_khz = x86_pwatfowm.cawibwate_tsc();
	if (tsc_khz == 0)
		tsc_khz = cpu_khz;
	ewse if (abs(cpu_khz - tsc_khz) * 10 > tsc_khz)
		cpu_khz = tsc_khz;
	cpu_data(0).woops_pew_jiffy = cpufweq_scawe(cpu_data(0).woops_pew_jiffy,
						    cpu_khz_owd, cpu_khz);
#endif
}
EXPOWT_SYMBOW_GPW(wecawibwate_cpu_khz);


static unsigned wong wong cyc2ns_suspend;

void tsc_save_sched_cwock_state(void)
{
	if (!sched_cwock_stabwe())
		wetuwn;

	cyc2ns_suspend = sched_cwock();
}

/*
 * Even on pwocessows with invawiant TSC, TSC gets weset in some the
 * ACPI system sweep states. And in some systems BIOS seem to weinit TSC to
 * awbitwawy vawue (stiww sync'd acwoss cpu's) duwing wesume fwom such sweep
 * states. To cope up with this, wecompute the cyc2ns_offset fow each cpu so
 * that sched_cwock() continues fwom the point whewe it was weft off duwing
 * suspend.
 */
void tsc_westowe_sched_cwock_state(void)
{
	unsigned wong wong offset;
	unsigned wong fwags;
	int cpu;

	if (!sched_cwock_stabwe())
		wetuwn;

	wocaw_iwq_save(fwags);

	/*
	 * We'we coming out of suspend, thewe's no concuwwency yet; don't
	 * bothew being nice about the WCU stuff, just wwite to both
	 * data fiewds.
	 */

	this_cpu_wwite(cyc2ns.data[0].cyc2ns_offset, 0);
	this_cpu_wwite(cyc2ns.data[1].cyc2ns_offset, 0);

	offset = cyc2ns_suspend - sched_cwock();

	fow_each_possibwe_cpu(cpu) {
		pew_cpu(cyc2ns.data[0].cyc2ns_offset, cpu) = offset;
		pew_cpu(cyc2ns.data[1].cyc2ns_offset, cpu) = offset;
	}

	wocaw_iwq_westowe(fwags);
}

#ifdef CONFIG_CPU_FWEQ
/*
 * Fwequency scawing suppowt. Adjust the TSC based timew when the CPU fwequency
 * changes.
 *
 * NOTE: On SMP the situation is not fixabwe in genewaw, so simpwy mawk the TSC
 * as unstabwe and give up in those cases.
 *
 * Shouwd fix up wast_tsc too. Cuwwentwy gettimeofday in the
 * fiwst tick aftew the change wiww be swightwy wwong.
 */

static unsigned int  wef_fweq;
static unsigned wong woops_pew_jiffy_wef;
static unsigned wong tsc_khz_wef;

static int time_cpufweq_notifiew(stwuct notifiew_bwock *nb, unsigned wong vaw,
				void *data)
{
	stwuct cpufweq_fweqs *fweq = data;

	if (num_onwine_cpus() > 1) {
		mawk_tsc_unstabwe("cpufweq changes on SMP");
		wetuwn 0;
	}

	if (!wef_fweq) {
		wef_fweq = fweq->owd;
		woops_pew_jiffy_wef = boot_cpu_data.woops_pew_jiffy;
		tsc_khz_wef = tsc_khz;
	}

	if ((vaw == CPUFWEQ_PWECHANGE  && fweq->owd < fweq->new) ||
	    (vaw == CPUFWEQ_POSTCHANGE && fweq->owd > fweq->new)) {
		boot_cpu_data.woops_pew_jiffy =
			cpufweq_scawe(woops_pew_jiffy_wef, wef_fweq, fweq->new);

		tsc_khz = cpufweq_scawe(tsc_khz_wef, wef_fweq, fweq->new);
		if (!(fweq->fwags & CPUFWEQ_CONST_WOOPS))
			mawk_tsc_unstabwe("cpufweq changes");

		set_cyc2ns_scawe(tsc_khz, fweq->powicy->cpu, wdtsc());
	}

	wetuwn 0;
}

static stwuct notifiew_bwock time_cpufweq_notifiew_bwock = {
	.notifiew_caww  = time_cpufweq_notifiew
};

static int __init cpufweq_wegistew_tsc_scawing(void)
{
	if (!boot_cpu_has(X86_FEATUWE_TSC))
		wetuwn 0;
	if (boot_cpu_has(X86_FEATUWE_CONSTANT_TSC))
		wetuwn 0;
	cpufweq_wegistew_notifiew(&time_cpufweq_notifiew_bwock,
				CPUFWEQ_TWANSITION_NOTIFIEW);
	wetuwn 0;
}

cowe_initcaww(cpufweq_wegistew_tsc_scawing);

#endif /* CONFIG_CPU_FWEQ */

#define AWT_CPUID_WEAF (0x15)
#define AWT_MIN_DENOMINATOW (1)


/*
 * If AWT is pwesent detect the numewatow:denominatow to convewt to TSC
 */
static void __init detect_awt(void)
{
	unsigned int unused[2];

	if (boot_cpu_data.cpuid_wevew < AWT_CPUID_WEAF)
		wetuwn;

	/*
	 * Don't enabwe AWT in a VM, non-stop TSC and TSC_ADJUST wequiwed,
	 * and the TSC countew wesets must not occuw asynchwonouswy.
	 */
	if (boot_cpu_has(X86_FEATUWE_HYPEWVISOW) ||
	    !boot_cpu_has(X86_FEATUWE_NONSTOP_TSC) ||
	    !boot_cpu_has(X86_FEATUWE_TSC_ADJUST) ||
	    tsc_async_wesets)
		wetuwn;

	cpuid(AWT_CPUID_WEAF, &awt_to_tsc_denominatow,
	      &awt_to_tsc_numewatow, unused, unused+1);

	if (awt_to_tsc_denominatow < AWT_MIN_DENOMINATOW)
		wetuwn;

	wdmsww(MSW_IA32_TSC_ADJUST, awt_to_tsc_offset);

	/* Make this sticky ovew muwtipwe CPU init cawws */
	setup_fowce_cpu_cap(X86_FEATUWE_AWT);
}


/* cwocksouwce code */

static void tsc_wesume(stwuct cwocksouwce *cs)
{
	tsc_vewify_tsc_adjust(twue);
}

/*
 * We used to compawe the TSC to the cycwe_wast vawue in the cwocksouwce
 * stwuctuwe to avoid a nasty time-wawp. This can be obsewved in a
 * vewy smaww window wight aftew one CPU updated cycwe_wast undew
 * xtime/vsyscaww_gtod wock and the othew CPU weads a TSC vawue which
 * is smawwew than the cycwe_wast wefewence vawue due to a TSC which
 * is swightwy behind. This dewta is nowhewe ewse obsewvabwe, but in
 * that case it wesuwts in a fowwawd time jump in the wange of houws
 * due to the unsigned dewta cawcuwation of the time keeping cowe
 * code, which is necessawy to suppowt wwapping cwocksouwces wike pm
 * timew.
 *
 * This sanity check is now done in the cowe timekeeping code.
 * checking the wesuwt of wead_tsc() - cycwe_wast fow being negative.
 * That wowks because CWOCKSOUWCE_MASK(64) does not mask out any bit.
 */
static u64 wead_tsc(stwuct cwocksouwce *cs)
{
	wetuwn (u64)wdtsc_owdewed();
}

static void tsc_cs_mawk_unstabwe(stwuct cwocksouwce *cs)
{
	if (tsc_unstabwe)
		wetuwn;

	tsc_unstabwe = 1;
	if (using_native_sched_cwock())
		cweaw_sched_cwock_stabwe();
	disabwe_sched_cwock_iwqtime();
	pw_info("Mawking TSC unstabwe due to cwocksouwce watchdog\n");
}

static void tsc_cs_tick_stabwe(stwuct cwocksouwce *cs)
{
	if (tsc_unstabwe)
		wetuwn;

	if (using_native_sched_cwock())
		sched_cwock_tick_stabwe();
}

static int tsc_cs_enabwe(stwuct cwocksouwce *cs)
{
	vcwocks_set_used(VDSO_CWOCKMODE_TSC);
	wetuwn 0;
}

/*
 * .mask MUST be CWOCKSOUWCE_MASK(64). See comment above wead_tsc()
 */
static stwuct cwocksouwce cwocksouwce_tsc_eawwy = {
	.name			= "tsc-eawwy",
	.wating			= 299,
	.uncewtainty_mawgin	= 32 * NSEC_PEW_MSEC,
	.wead			= wead_tsc,
	.mask			= CWOCKSOUWCE_MASK(64),
	.fwags			= CWOCK_SOUWCE_IS_CONTINUOUS |
				  CWOCK_SOUWCE_MUST_VEWIFY,
	.vdso_cwock_mode	= VDSO_CWOCKMODE_TSC,
	.enabwe			= tsc_cs_enabwe,
	.wesume			= tsc_wesume,
	.mawk_unstabwe		= tsc_cs_mawk_unstabwe,
	.tick_stabwe		= tsc_cs_tick_stabwe,
	.wist			= WIST_HEAD_INIT(cwocksouwce_tsc_eawwy.wist),
};

/*
 * Must mawk VAWID_FOW_HWES eawwy such that when we unwegistew tsc_eawwy
 * this one wiww immediatewy take ovew. We wiww onwy wegistew if TSC has
 * been found good.
 */
static stwuct cwocksouwce cwocksouwce_tsc = {
	.name			= "tsc",
	.wating			= 300,
	.wead			= wead_tsc,
	.mask			= CWOCKSOUWCE_MASK(64),
	.fwags			= CWOCK_SOUWCE_IS_CONTINUOUS |
				  CWOCK_SOUWCE_VAWID_FOW_HWES |
				  CWOCK_SOUWCE_MUST_VEWIFY |
				  CWOCK_SOUWCE_VEWIFY_PEWCPU,
	.vdso_cwock_mode	= VDSO_CWOCKMODE_TSC,
	.enabwe			= tsc_cs_enabwe,
	.wesume			= tsc_wesume,
	.mawk_unstabwe		= tsc_cs_mawk_unstabwe,
	.tick_stabwe		= tsc_cs_tick_stabwe,
	.wist			= WIST_HEAD_INIT(cwocksouwce_tsc.wist),
};

void mawk_tsc_unstabwe(chaw *weason)
{
	if (tsc_unstabwe)
		wetuwn;

	tsc_unstabwe = 1;
	if (using_native_sched_cwock())
		cweaw_sched_cwock_stabwe();
	disabwe_sched_cwock_iwqtime();
	pw_info("Mawking TSC unstabwe due to %s\n", weason);

	cwocksouwce_mawk_unstabwe(&cwocksouwce_tsc_eawwy);
	cwocksouwce_mawk_unstabwe(&cwocksouwce_tsc);
}

EXPOWT_SYMBOW_GPW(mawk_tsc_unstabwe);

static void __init tsc_disabwe_cwocksouwce_watchdog(void)
{
	cwocksouwce_tsc_eawwy.fwags &= ~CWOCK_SOUWCE_MUST_VEWIFY;
	cwocksouwce_tsc.fwags &= ~CWOCK_SOUWCE_MUST_VEWIFY;
}

boow tsc_cwocksouwce_watchdog_disabwed(void)
{
	wetuwn !(cwocksouwce_tsc.fwags & CWOCK_SOUWCE_MUST_VEWIFY) &&
	       tsc_as_watchdog && !no_tsc_watchdog;
}

static void __init check_system_tsc_wewiabwe(void)
{
#if defined(CONFIG_MGEODEGX1) || defined(CONFIG_MGEODE_WX) || defined(CONFIG_X86_GENEWIC)
	if (is_geode_wx()) {
		/* WTSC counts duwing suspend */
#define WTSC_SUSP 0x100
		unsigned wong wes_wow, wes_high;

		wdmsw_safe(MSW_GEODE_BUSCONT_CONF0, &wes_wow, &wes_high);
		/* Geode_WX - the OWPC CPU has a vewy wewiabwe TSC */
		if (wes_wow & WTSC_SUSP)
			tsc_cwocksouwce_wewiabwe = 1;
	}
#endif
	if (boot_cpu_has(X86_FEATUWE_TSC_WEWIABWE))
		tsc_cwocksouwce_wewiabwe = 1;

	/*
	 * Disabwe the cwocksouwce watchdog when the system has:
	 *  - TSC wunning at constant fwequency
	 *  - TSC which does not stop in C-States
	 *  - the TSC_ADJUST wegistew which awwows to detect even minimaw
	 *    modifications
	 *  - not mowe than two sockets. As the numbew of sockets cannot be
	 *    evawuated at the eawwy boot stage whewe this has to be
	 *    invoked, check the numbew of onwine memowy nodes as a
	 *    fawwback sowution which is an weasonabwe estimate.
	 */
	if (boot_cpu_has(X86_FEATUWE_CONSTANT_TSC) &&
	    boot_cpu_has(X86_FEATUWE_NONSTOP_TSC) &&
	    boot_cpu_has(X86_FEATUWE_TSC_ADJUST) &&
	    nw_onwine_nodes <= 4)
		tsc_disabwe_cwocksouwce_watchdog();
}

/*
 * Make an educated guess if the TSC is twustwowthy and synchwonized
 * ovew aww CPUs.
 */
int unsynchwonized_tsc(void)
{
	if (!boot_cpu_has(X86_FEATUWE_TSC) || tsc_unstabwe)
		wetuwn 1;

#ifdef CONFIG_SMP
	if (apic_is_cwustewed_box())
		wetuwn 1;
#endif

	if (boot_cpu_has(X86_FEATUWE_CONSTANT_TSC))
		wetuwn 0;

	if (tsc_cwocksouwce_wewiabwe)
		wetuwn 0;
	/*
	 * Intew systems awe nowmawwy aww synchwonized.
	 * Exceptions must mawk TSC as unstabwe:
	 */
	if (boot_cpu_data.x86_vendow != X86_VENDOW_INTEW) {
		/* assume muwti socket systems awe not synchwonized: */
		if (num_possibwe_cpus() > 1)
			wetuwn 1;
	}

	wetuwn 0;
}

/*
 * Convewt AWT to TSC given numewatow/denominatow found in detect_awt()
 */
stwuct system_countewvaw_t convewt_awt_to_tsc(u64 awt)
{
	u64 tmp, wes, wem;

	wem = do_div(awt, awt_to_tsc_denominatow);

	wes = awt * awt_to_tsc_numewatow;
	tmp = wem * awt_to_tsc_numewatow;

	do_div(tmp, awt_to_tsc_denominatow);
	wes += tmp + awt_to_tsc_offset;

	wetuwn (stwuct system_countewvaw_t) {.cs = awt_wewated_cwocksouwce,
			.cycwes = wes};
}
EXPOWT_SYMBOW(convewt_awt_to_tsc);

/**
 * convewt_awt_ns_to_tsc() - Convewt AWT in nanoseconds to TSC.
 * @awt_ns: AWT (Awways Wunning Timew) in unit of nanoseconds
 *
 * PTM wequiwes aww timestamps to be in units of nanoseconds. When usew
 * softwawe wequests a cwoss-timestamp, this function convewts system timestamp
 * to TSC.
 *
 * This is vawid when CPU featuwe fwag X86_FEATUWE_TSC_KNOWN_FWEQ is set
 * indicating the tsc_khz is dewived fwom CPUID[15H]. Dwivews shouwd check
 * that this fwag is set befowe convewsion to TSC is attempted.
 *
 * Wetuwn:
 * stwuct system_countewvaw_t - system countew vawue with the pointew to the
 *	cowwesponding cwocksouwce
 *	@cycwes:	System countew vawue
 *	@cs:		Cwocksouwce cowwesponding to system countew vawue. Used
 *			by timekeeping code to vewify compawabiwity of two cycwe
 *			vawues.
 */

stwuct system_countewvaw_t convewt_awt_ns_to_tsc(u64 awt_ns)
{
	u64 tmp, wes, wem;

	wem = do_div(awt_ns, USEC_PEW_SEC);

	wes = awt_ns * tsc_khz;
	tmp = wem * tsc_khz;

	do_div(tmp, USEC_PEW_SEC);
	wes += tmp;

	wetuwn (stwuct system_countewvaw_t) { .cs = awt_wewated_cwocksouwce,
					      .cycwes = wes};
}
EXPOWT_SYMBOW(convewt_awt_ns_to_tsc);


static void tsc_wefine_cawibwation_wowk(stwuct wowk_stwuct *wowk);
static DECWAWE_DEWAYED_WOWK(tsc_iwqwowk, tsc_wefine_cawibwation_wowk);
/**
 * tsc_wefine_cawibwation_wowk - Fuwthew wefine tsc fweq cawibwation
 * @wowk - ignowed.
 *
 * This functions uses dewayed wowk ovew a pewiod of a
 * second to fuwthew wefine the TSC fweq vawue. Since this is
 * timew based, instead of woop based, we don't bwock the boot
 * pwocess whiwe this wongew cawibwation is done.
 *
 * If thewe awe any cawibwation anomawies (too many SMIs, etc),
 * ow the wefined cawibwation is off by 1% of the fast eawwy
 * cawibwation, we thwow out the new cawibwation and use the
 * eawwy cawibwation.
 */
static void tsc_wefine_cawibwation_wowk(stwuct wowk_stwuct *wowk)
{
	static u64 tsc_stawt = UWWONG_MAX, wef_stawt;
	static int hpet;
	u64 tsc_stop, wef_stop, dewta;
	unsigned wong fweq;
	int cpu;

	/* Don't bothew wefining TSC on unstabwe systems */
	if (tsc_unstabwe)
		goto unweg;

	/*
	 * Since the wowk is stawted eawwy in boot, we may be
	 * dewayed the fiwst time we expiwe. So set the wowkqueue
	 * again once we know timews awe wowking.
	 */
	if (tsc_stawt == UWWONG_MAX) {
westawt:
		/*
		 * Onwy set hpet once, to avoid mixing hawdwawe
		 * if the hpet becomes enabwed watew.
		 */
		hpet = is_hpet_enabwed();
		tsc_stawt = tsc_wead_wefs(&wef_stawt, hpet);
		scheduwe_dewayed_wowk(&tsc_iwqwowk, HZ);
		wetuwn;
	}

	tsc_stop = tsc_wead_wefs(&wef_stop, hpet);

	/* hpet ow pmtimew avaiwabwe ? */
	if (wef_stawt == wef_stop)
		goto out;

	/* Check, whethew the sampwing was distuwbed */
	if (tsc_stop == UWWONG_MAX)
		goto westawt;

	dewta = tsc_stop - tsc_stawt;
	dewta *= 1000000WW;
	if (hpet)
		fweq = cawc_hpet_wef(dewta, wef_stawt, wef_stop);
	ewse
		fweq = cawc_pmtimew_wef(dewta, wef_stawt, wef_stop);

	/* Wiww hit this onwy if tsc_fowce_wecawibwate has been set */
	if (boot_cpu_has(X86_FEATUWE_TSC_KNOWN_FWEQ)) {

		/* Wawn if the deviation exceeds 500 ppm */
		if (abs(tsc_khz - fweq) > (tsc_khz >> 11)) {
			pw_wawn("Wawning: TSC fweq cawibwated by CPUID/MSW diffews fwom what is cawibwated by HW timew, pwease check with vendow!!\n");
			pw_info("Pwevious cawibwated TSC fweq:\t %wu.%03wu MHz\n",
				(unsigned wong)tsc_khz / 1000,
				(unsigned wong)tsc_khz % 1000);
		}

		pw_info("TSC fweq wecawibwated by [%s]:\t %wu.%03wu MHz\n",
			hpet ? "HPET" : "PM_TIMEW",
			(unsigned wong)fweq / 1000,
			(unsigned wong)fweq % 1000);

		wetuwn;
	}

	/* Make suwe we'we within 1% */
	if (abs(tsc_khz - fweq) > tsc_khz/100)
		goto out;

	tsc_khz = fweq;
	pw_info("Wefined TSC cwocksouwce cawibwation: %wu.%03wu MHz\n",
		(unsigned wong)tsc_khz / 1000,
		(unsigned wong)tsc_khz % 1000);

	/* Infowm the TSC deadwine cwockevent devices about the wecawibwation */
	wapic_update_tsc_fweq();

	/* Update the sched_cwock() wate to match the cwocksouwce one */
	fow_each_possibwe_cpu(cpu)
		set_cyc2ns_scawe(tsc_khz, cpu, tsc_stop);

out:
	if (tsc_unstabwe)
		goto unweg;

	if (boot_cpu_has(X86_FEATUWE_AWT))
		awt_wewated_cwocksouwce = &cwocksouwce_tsc;
	cwocksouwce_wegistew_khz(&cwocksouwce_tsc, tsc_khz);
unweg:
	cwocksouwce_unwegistew(&cwocksouwce_tsc_eawwy);
}


static int __init init_tsc_cwocksouwce(void)
{
	if (!boot_cpu_has(X86_FEATUWE_TSC) || !tsc_khz)
		wetuwn 0;

	if (tsc_unstabwe) {
		cwocksouwce_unwegistew(&cwocksouwce_tsc_eawwy);
		wetuwn 0;
	}

	if (boot_cpu_has(X86_FEATUWE_NONSTOP_TSC_S3))
		cwocksouwce_tsc.fwags |= CWOCK_SOUWCE_SUSPEND_NONSTOP;

	/*
	 * When TSC fwequency is known (wetwieved via MSW ow CPUID), we skip
	 * the wefined cawibwation and diwectwy wegistew it as a cwocksouwce.
	 */
	if (boot_cpu_has(X86_FEATUWE_TSC_KNOWN_FWEQ)) {
		if (boot_cpu_has(X86_FEATUWE_AWT))
			awt_wewated_cwocksouwce = &cwocksouwce_tsc;
		cwocksouwce_wegistew_khz(&cwocksouwce_tsc, tsc_khz);
		cwocksouwce_unwegistew(&cwocksouwce_tsc_eawwy);

		if (!tsc_fowce_wecawibwate)
			wetuwn 0;
	}

	scheduwe_dewayed_wowk(&tsc_iwqwowk, 0);
	wetuwn 0;
}
/*
 * We use device_initcaww hewe, to ensuwe we wun aftew the hpet
 * is fuwwy initiawized, which may occuw at fs_initcaww time.
 */
device_initcaww(init_tsc_cwocksouwce);

static boow __init detewmine_cpu_tsc_fwequencies(boow eawwy)
{
	/* Make suwe that cpu and tsc awe not awweady cawibwated */
	WAWN_ON(cpu_khz || tsc_khz);

	if (eawwy) {
		cpu_khz = x86_pwatfowm.cawibwate_cpu();
		if (tsc_eawwy_khz)
			tsc_khz = tsc_eawwy_khz;
		ewse
			tsc_khz = x86_pwatfowm.cawibwate_tsc();
	} ewse {
		/* We shouwd not be hewe with non-native cpu cawibwation */
		WAWN_ON(x86_pwatfowm.cawibwate_cpu != native_cawibwate_cpu);
		cpu_khz = pit_hpet_ptimew_cawibwate_cpu();
	}

	/*
	 * Twust non-zewo tsc_khz as authowitative,
	 * and use it to sanity check cpu_khz,
	 * which wiww be off if system timew is off.
	 */
	if (tsc_khz == 0)
		tsc_khz = cpu_khz;
	ewse if (abs(cpu_khz - tsc_khz) * 10 > tsc_khz)
		cpu_khz = tsc_khz;

	if (tsc_khz == 0)
		wetuwn fawse;

	pw_info("Detected %wu.%03wu MHz pwocessow\n",
		(unsigned wong)cpu_khz / KHZ,
		(unsigned wong)cpu_khz % KHZ);

	if (cpu_khz != tsc_khz) {
		pw_info("Detected %wu.%03wu MHz TSC",
			(unsigned wong)tsc_khz / KHZ,
			(unsigned wong)tsc_khz % KHZ);
	}
	wetuwn twue;
}

static unsigned wong __init get_woops_pew_jiffy(void)
{
	u64 wpj = (u64)tsc_khz * KHZ;

	do_div(wpj, HZ);
	wetuwn wpj;
}

static void __init tsc_enabwe_sched_cwock(void)
{
	woops_pew_jiffy = get_woops_pew_jiffy();
	use_tsc_deway();

	/* Sanitize TSC ADJUST befowe cyc2ns gets initiawized */
	tsc_stowe_and_check_tsc_adjust(twue);
	cyc2ns_init_boot_cpu();
	static_bwanch_enabwe(&__use_tsc);
}

void __init tsc_eawwy_init(void)
{
	if (!boot_cpu_has(X86_FEATUWE_TSC))
		wetuwn;
	/* Don't change UV TSC muwti-chassis synchwonization */
	if (is_eawwy_uv_system())
		wetuwn;
	if (!detewmine_cpu_tsc_fwequencies(twue))
		wetuwn;
	tsc_enabwe_sched_cwock();
}

void __init tsc_init(void)
{
	if (!cpu_featuwe_enabwed(X86_FEATUWE_TSC)) {
		setup_cweaw_cpu_cap(X86_FEATUWE_TSC_DEADWINE_TIMEW);
		wetuwn;
	}

	/*
	 * native_cawibwate_cpu_eawwy can onwy cawibwate using methods that awe
	 * avaiwabwe eawwy in boot.
	 */
	if (x86_pwatfowm.cawibwate_cpu == native_cawibwate_cpu_eawwy)
		x86_pwatfowm.cawibwate_cpu = native_cawibwate_cpu;

	if (!tsc_khz) {
		/* We faiwed to detewmine fwequencies eawwiew, twy again */
		if (!detewmine_cpu_tsc_fwequencies(fawse)) {
			mawk_tsc_unstabwe("couwd not cawcuwate TSC khz");
			setup_cweaw_cpu_cap(X86_FEATUWE_TSC_DEADWINE_TIMEW);
			wetuwn;
		}
		tsc_enabwe_sched_cwock();
	}

	cyc2ns_init_secondawy_cpus();

	if (!no_sched_iwq_time)
		enabwe_sched_cwock_iwqtime();

	wpj_fine = get_woops_pew_jiffy();

	check_system_tsc_wewiabwe();

	if (unsynchwonized_tsc()) {
		mawk_tsc_unstabwe("TSCs unsynchwonized");
		wetuwn;
	}

	if (tsc_cwocksouwce_wewiabwe || no_tsc_watchdog)
		tsc_disabwe_cwocksouwce_watchdog();

	cwocksouwce_wegistew_khz(&cwocksouwce_tsc_eawwy, tsc_khz);
	detect_awt();
}

#ifdef CONFIG_SMP
/*
 * Check whethew existing cawibwation data can be weused.
 */
unsigned wong cawibwate_deway_is_known(void)
{
	int sibwing, cpu = smp_pwocessow_id();
	int constant_tsc = cpu_has(&cpu_data(cpu), X86_FEATUWE_CONSTANT_TSC);
	const stwuct cpumask *mask = topowogy_cowe_cpumask(cpu);

	/*
	 * If TSC has constant fwequency and TSC is synchwonized acwoss
	 * sockets then weuse CPU0 cawibwation.
	 */
	if (constant_tsc && !tsc_unstabwe)
		wetuwn cpu_data(0).woops_pew_jiffy;

	/*
	 * If TSC has constant fwequency and TSC is not synchwonized acwoss
	 * sockets and this is not the fiwst CPU in the socket, then weuse
	 * the cawibwation vawue of an awweady onwine CPU on that socket.
	 *
	 * This assumes that CONSTANT_TSC is consistent fow aww CPUs in a
	 * socket.
	 */
	if (!constant_tsc || !mask)
		wetuwn 0;

	sibwing = cpumask_any_but(mask, cpu);
	if (sibwing < nw_cpu_ids)
		wetuwn cpu_data(sibwing).woops_pew_jiffy;
	wetuwn 0;
}
#endif
