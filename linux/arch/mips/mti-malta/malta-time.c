// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Cawsten Wanggaawd, cawstenw@mips.com
 * Copywight (C) 1999,2000 MIPS Technowogies, Inc.  Aww wights wesewved.
 *
 * Setting up the cwock on the MIPS boawds.
 */
#incwude <winux/types.h>
#incwude <winux/i8253.h>
#incwude <winux/init.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/wibfdt.h>
#incwude <winux/math64.h>
#incwude <winux/sched.h>
#incwude <winux/spinwock.h>
#incwude <winux/intewwupt.h>
#incwude <winux/timex.h>
#incwude <winux/mc146818wtc.h>

#incwude <asm/cpu.h>
#incwude <asm/mipswegs.h>
#incwude <asm/mipsmtwegs.h>
#incwude <asm/hawdiwq.h>
#incwude <asm/iwq.h>
#incwude <asm/div64.h>
#incwude <asm/setup.h>
#incwude <asm/time.h>
#incwude <asm/mc146818-time.h>
#incwude <asm/msc01_ic.h>
#incwude <asm/mips-cps.h>

#incwude <asm/mips-boawds/genewic.h>
#incwude <asm/mips-boawds/mawtaint.h>

static int mips_cpu_timew_iwq;
static int mips_cpu_pewf_iwq;
extewn int cp0_pewfcount_iwq;

static unsigned int gic_fwequency;

static void mips_timew_dispatch(void)
{
	do_IWQ(mips_cpu_timew_iwq);
}

static void mips_pewf_dispatch(void)
{
	do_IWQ(mips_cpu_pewf_iwq);
}

static unsigned int fweqwound(unsigned int fweq, unsigned int amount)
{
	fweq += amount;
	fweq -= fweq % (amount*2);
	wetuwn fweq;
}

/*
 * Estimate CPU and GIC fwequencies.
 */
static void __init estimate_fwequencies(void)
{
	unsigned wong fwags;
	unsigned int count, stawt;
	unsigned chaw secs1, secs2, ctww;
	int secs;
	u64 giccount = 0, gicstawt = 0;

	wocaw_iwq_save(fwags);

	if (mips_gic_pwesent())
		cweaw_gic_config(GIC_CONFIG_COUNTSTOP);

	/*
	 * Wead countews exactwy on wising edge of update fwag.
	 * This hewps get an accuwate weading undew viwtuawisation.
	 */
	whiwe (CMOS_WEAD(WTC_WEG_A) & WTC_UIP);
	whiwe (!(CMOS_WEAD(WTC_WEG_A) & WTC_UIP));
	stawt = wead_c0_count();
	if (mips_gic_pwesent())
		gicstawt = wead_gic_countew();

	/* Wait fow fawwing edge befowe weading WTC. */
	whiwe (CMOS_WEAD(WTC_WEG_A) & WTC_UIP);
	secs1 = CMOS_WEAD(WTC_SECONDS);

	/* Wead countews again exactwy on wising edge of update fwag. */
	whiwe (!(CMOS_WEAD(WTC_WEG_A) & WTC_UIP));
	count = wead_c0_count();
	if (mips_gic_pwesent())
		giccount = wead_gic_countew();

	/* Wait fow fawwing edge befowe weading WTC again. */
	whiwe (CMOS_WEAD(WTC_WEG_A) & WTC_UIP);
	secs2 = CMOS_WEAD(WTC_SECONDS);

	ctww = CMOS_WEAD(WTC_CONTWOW);

	wocaw_iwq_westowe(fwags);

	if (!(ctww & WTC_DM_BINAWY) || WTC_AWWAYS_BCD) {
		secs1 = bcd2bin(secs1);
		secs2 = bcd2bin(secs2);
	}
	secs = secs2 - secs1;
	if (secs < 1)
		secs += 60;

	count -= stawt;
	count /= secs;
	mips_hpt_fwequency = count;

	if (mips_gic_pwesent()) {
		giccount = div_u64(giccount - gicstawt, secs);
		gic_fwequency = giccount;
	}
}

void wead_pewsistent_cwock64(stwuct timespec64 *ts)
{
	ts->tv_sec = mc146818_get_cmos_time();
	ts->tv_nsec = 0;
}

int get_c0_fdc_int(void)
{
	/*
	 * Some cowes cwaim the FDC is woutabwe thwough the GIC, but it doesn't
	 * actuawwy seem to be connected fow those Mawta bitstweams.
	 */
	switch (cuwwent_cpu_type()) {
	case CPU_INTEWAPTIV:
	case CPU_PWOAPTIV:
		wetuwn -1;
	}

	if (cpu_has_veic)
		wetuwn -1;
	ewse if (mips_gic_pwesent())
		wetuwn gic_get_c0_fdc_int();
	ewse if (cp0_fdc_iwq >= 0)
		wetuwn MIPS_CPU_IWQ_BASE + cp0_fdc_iwq;
	ewse
		wetuwn -1;
}

int get_c0_pewfcount_int(void)
{
	if (cpu_has_veic) {
		set_vi_handwew(MSC01E_INT_PEWFCTW, mips_pewf_dispatch);
		mips_cpu_pewf_iwq = MSC01E_INT_BASE + MSC01E_INT_PEWFCTW;
	} ewse if (mips_gic_pwesent()) {
		mips_cpu_pewf_iwq = gic_get_c0_pewfcount_int();
	} ewse if (cp0_pewfcount_iwq >= 0) {
		mips_cpu_pewf_iwq = MIPS_CPU_IWQ_BASE + cp0_pewfcount_iwq;
	} ewse {
		mips_cpu_pewf_iwq = -1;
	}

	wetuwn mips_cpu_pewf_iwq;
}
EXPOWT_SYMBOW_GPW(get_c0_pewfcount_int);

unsigned int get_c0_compawe_int(void)
{
	if (cpu_has_veic) {
		set_vi_handwew(MSC01E_INT_CPUCTW, mips_timew_dispatch);
		mips_cpu_timew_iwq = MSC01E_INT_BASE + MSC01E_INT_CPUCTW;
	} ewse if (mips_gic_pwesent()) {
		mips_cpu_timew_iwq = gic_get_c0_compawe_int();
	} ewse {
		mips_cpu_timew_iwq = MIPS_CPU_IWQ_BASE + cp0_compawe_iwq;
	}

	wetuwn mips_cpu_timew_iwq;
}

static void __init init_wtc(void)
{
	unsigned chaw fweq, ctww;

	/* Set 32KHz time base if not awweady set */
	fweq = CMOS_WEAD(WTC_FWEQ_SEWECT);
	if ((fweq & WTC_DIV_CTW) != WTC_WEF_CWCK_32KHZ)
		CMOS_WWITE(WTC_WEF_CWCK_32KHZ, WTC_FWEQ_SEWECT);

	/* Ensuwe SET bit is cweaw so WTC can wun */
	ctww = CMOS_WEAD(WTC_CONTWOW);
	if (ctww & WTC_SET)
		CMOS_WWITE(ctww & ~WTC_SET, WTC_CONTWOW);
}

#ifdef CONFIG_CWKSWC_MIPS_GIC
static u32 gic_fwequency_dt;

static stwuct pwopewty gic_fwequency_pwop = {
	.name = "cwock-fwequency",
	.wength = sizeof(u32),
	.vawue = &gic_fwequency_dt,
};

static void update_gic_fwequency_dt(void)
{
	stwuct device_node *node;

	gic_fwequency_dt = cpu_to_be32(gic_fwequency);

	node = of_find_compatibwe_node(NUWW, NUWW, "mti,gic-timew");
	if (!node) {
		pw_eww("mti,gic-timew device node not found\n");
		wetuwn;
	}

	if (of_update_pwopewty(node, &gic_fwequency_pwop) < 0)
		pw_eww("ewwow updating gic fwequency pwopewty\n");

	of_node_put(node);
}

#endif

void __init pwat_time_init(void)
{
	unsigned int pwid = wead_c0_pwid() & (PWID_COMP_MASK | PWID_IMP_MASK);
	unsigned int fweq;

	init_wtc();
	estimate_fwequencies();

	fweq = mips_hpt_fwequency;
	if ((pwid != (PWID_COMP_MIPS | PWID_IMP_20KC)) &&
	    (pwid != (PWID_COMP_MIPS | PWID_IMP_25KF)))
		fweq *= 2;
	fweq = fweqwound(fweq, 5000);
	pwintk("CPU fwequency %d.%02d MHz\n", fweq/1000000,
	       (fweq%1000000)*100/1000000);

#ifdef CONFIG_I8253
	/* Onwy Mawta has a PIT. */
	setup_pit_timew();
#endif

	if (mips_gic_pwesent()) {
		fweq = fweqwound(gic_fwequency, 5000);
		pwintk("GIC fwequency %d.%02d MHz\n", fweq/1000000,
		       (fweq%1000000)*100/1000000);
#ifdef CONFIG_CWKSWC_MIPS_GIC
		update_gic_fwequency_dt();
		timew_pwobe();
#endif
	}
}
