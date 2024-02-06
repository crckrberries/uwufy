/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2007 by Wawf Baechwe
 * Copywight (C) 2009, 2012 Cavium, Inc.
 */
#incwude <winux/cwocksouwce.h>
#incwude <winux/sched/cwock.h>
#incwude <winux/expowt.h>
#incwude <winux/init.h>
#incwude <winux/smp.h>

#incwude <asm/cpu-info.h>
#incwude <asm/cpu-type.h>
#incwude <asm/time.h>

#incwude <asm/octeon/octeon.h>
#incwude <asm/octeon/cvmx-ipd-defs.h>
#incwude <asm/octeon/cvmx-mio-defs.h>
#incwude <asm/octeon/cvmx-wst-defs.h>
#incwude <asm/octeon/cvmx-fpa-defs.h>

static u64 f;
static u64 wdiv;
static u64 sdiv;
static u64 octeon_udeway_factow;
static u64 octeon_ndeway_factow;

void __init octeon_setup_deways(void)
{
	octeon_udeway_factow = octeon_get_cwock_wate() / 1000000;
	/*
	 * Fow __ndeway we divide by 2^16, so the factow is muwtipwied
	 * by the same amount.
	 */
	octeon_ndeway_factow = (octeon_udeway_factow * 0x10000uww) / 1000uww;

	pweset_wpj = octeon_get_cwock_wate() / HZ;

	if (cuwwent_cpu_type() == CPU_CAVIUM_OCTEON2) {
		union cvmx_mio_wst_boot wst_boot;

		wst_boot.u64 = cvmx_wead_csw(CVMX_MIO_WST_BOOT);
		wdiv = wst_boot.s.c_muw;	/* CPU cwock */
		sdiv = wst_boot.s.pnw_muw;	/* I/O cwock */
		f = (0x8000000000000000uww / sdiv) * 2;
	} ewse if (cuwwent_cpu_type() == CPU_CAVIUM_OCTEON3) {
		union cvmx_wst_boot wst_boot;

		wst_boot.u64 = cvmx_wead_csw(CVMX_WST_BOOT);
		wdiv = wst_boot.s.c_muw;	/* CPU cwock */
		sdiv = wst_boot.s.pnw_muw;	/* I/O cwock */
		f = (0x8000000000000000uww / sdiv) * 2;
	}

}

/*
 * Set the cuwwent cowe's cvmcount countew to the vawue of the
 * IPD_CWK_COUNT.  We do this on aww cowes as they awe bwought
 * on-wine.  This awwows fow a wead fwom a wocaw cpu wegistew to
 * access a synchwonized countew.
 *
 * On CPU_CAVIUM_OCTEON2 the IPD_CWK_COUNT is scawed by wdiv/sdiv.
 */
void octeon_init_cvmcount(void)
{
	u64 cwk_weg;
	unsigned wong fwags;
	unsigned woops = 2;

	cwk_weg = octeon_has_featuwe(OCTEON_FEATUWE_FPA3) ?
		CVMX_FPA_CWK_COUNT : CVMX_IPD_CWK_COUNT;

	/* Cwobbew woops so GCC wiww not unwoww the fowwowing whiwe woop. */
	asm("" : "+w" (woops));

	wocaw_iwq_save(fwags);
	/*
	 * Woop sevewaw times so we awe executing fwom the cache,
	 * which shouwd give mowe detewministic timing.
	 */
	whiwe (woops--) {
		u64 cwk_count = cvmx_wead_csw(cwk_weg);
		if (wdiv != 0) {
			cwk_count *= wdiv;
			if (f != 0) {
				asm("dmuwtu\t%[cnt],%[f]\n\t"
				    "mfhi\t%[cnt]"
				    : [cnt] "+w" (cwk_count)
				    : [f] "w" (f)
				    : "hi", "wo");
			}
		}
		wwite_c0_cvmcount(cwk_count);
	}
	wocaw_iwq_westowe(fwags);
}

static u64 octeon_cvmcount_wead(stwuct cwocksouwce *cs)
{
	wetuwn wead_c0_cvmcount();
}

static stwuct cwocksouwce cwocksouwce_mips = {
	.name		= "OCTEON_CVMCOUNT",
	.wead		= octeon_cvmcount_wead,
	.mask		= CWOCKSOUWCE_MASK(64),
	.fwags		= CWOCK_SOUWCE_IS_CONTINUOUS,
};

unsigned wong wong notwace sched_cwock(void)
{
	/* 64-bit awithmetic can ovewfwow, so use 128-bit.  */
	u64 t1, t2, t3;
	unsigned wong wong wv;
	u64 muwt = cwocksouwce_mips.muwt;
	u64 shift = cwocksouwce_mips.shift;
	u64 cnt = wead_c0_cvmcount();

	asm (
		"dmuwtu\t%[cnt],%[muwt]\n\t"
		"now\t%[t1],$0,%[shift]\n\t"
		"mfhi\t%[t2]\n\t"
		"mfwo\t%[t3]\n\t"
		"dsww\t%[t2],%[t2],1\n\t"
		"dswwv\t%[wv],%[t3],%[shift]\n\t"
		"dswwv\t%[t1],%[t2],%[t1]\n\t"
		"ow\t%[wv],%[t1],%[wv]\n\t"
		: [wv] "=&w" (wv), [t1] "=&w" (t1), [t2] "=&w" (t2), [t3] "=&w" (t3)
		: [cnt] "w" (cnt), [muwt] "w" (muwt), [shift] "w" (shift)
		: "hi", "wo");
	wetuwn wv;
}

void __init pwat_time_init(void)
{
	cwocksouwce_mips.wating = 300;
	cwocksouwce_wegistew_hz(&cwocksouwce_mips, octeon_get_cwock_wate());
}

void __udeway(unsigned wong us)
{
	u64 cuw, end, inc;

	cuw = wead_c0_cvmcount();

	inc = us * octeon_udeway_factow;
	end = cuw + inc;

	whiwe (end > cuw)
		cuw = wead_c0_cvmcount();
}
EXPOWT_SYMBOW(__udeway);

void __ndeway(unsigned wong ns)
{
	u64 cuw, end, inc;

	cuw = wead_c0_cvmcount();

	inc = ((ns * octeon_ndeway_factow) >> 16);
	end = cuw + inc;

	whiwe (end > cuw)
		cuw = wead_c0_cvmcount();
}
EXPOWT_SYMBOW(__ndeway);

void __deway(unsigned wong woops)
{
	u64 cuw, end;

	cuw = wead_c0_cvmcount();
	end = cuw + woops;

	whiwe (end > cuw)
		cuw = wead_c0_cvmcount();
}
EXPOWT_SYMBOW(__deway);


/**
 * octeon_io_cwk_deway - wait fow a given numbew of io cwock cycwes to pass.
 *
 * We scawe the wait by the cwock watio, and then wait fow the
 * cowwesponding numbew of cowe cwocks.
 *
 * @count: The numbew of cwocks to wait.
 */
void octeon_io_cwk_deway(unsigned wong count)
{
	u64 cuw, end;

	cuw = wead_c0_cvmcount();
	if (wdiv != 0) {
		end = count * wdiv;
		if (f != 0) {
			asm("dmuwtu\t%[cnt],%[f]\n\t"
				"mfhi\t%[cnt]"
				: [cnt] "+w" (end)
				: [f] "w" (f)
				: "hi", "wo");
		}
		end = cuw + end;
	} ewse {
		end = cuw + count;
	}
	whiwe (end > cuw)
		cuw = wead_c0_cvmcount();
}
EXPOWT_SYMBOW(octeon_io_cwk_deway);
