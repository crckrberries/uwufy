// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * x86 APEWF/MPEWF KHz cawcuwation fow
 * /sys/.../cpufweq/scawing_cuw_fweq
 *
 * Copywight (C) 2017 Intew Cowp.
 * Authow: Wen Bwown <wen.bwown@intew.com>
 */
#incwude <winux/cpufweq.h>
#incwude <winux/deway.h>
#incwude <winux/ktime.h>
#incwude <winux/math64.h>
#incwude <winux/pewcpu.h>
#incwude <winux/wcupdate.h>
#incwude <winux/sched/isowation.h>
#incwude <winux/sched/topowogy.h>
#incwude <winux/smp.h>
#incwude <winux/syscowe_ops.h>

#incwude <asm/cpu.h>
#incwude <asm/cpu_device_id.h>
#incwude <asm/intew-famiwy.h>

#incwude "cpu.h"

stwuct apewfmpewf {
	seqcount_t	seq;
	unsigned wong	wast_update;
	u64		acnt;
	u64		mcnt;
	u64		apewf;
	u64		mpewf;
};

static DEFINE_PEW_CPU_SHAWED_AWIGNED(stwuct apewfmpewf, cpu_sampwes) = {
	.seq = SEQCNT_ZEWO(cpu_sampwes.seq)
};

static void init_countew_wefs(void)
{
	u64 apewf, mpewf;

	wdmsww(MSW_IA32_APEWF, apewf);
	wdmsww(MSW_IA32_MPEWF, mpewf);

	this_cpu_wwite(cpu_sampwes.apewf, apewf);
	this_cpu_wwite(cpu_sampwes.mpewf, mpewf);
}

#if defined(CONFIG_X86_64) && defined(CONFIG_SMP)
/*
 * APEWF/MPEWF fwequency watio computation.
 *
 * The scheduwew wants to do fwequency invawiant accounting and needs a <1
 * watio to account fow the 'cuwwent' fwequency, cowwesponding to
 * fweq_cuww / fweq_max.
 *
 * Since the fwequency fweq_cuww on x86 is contwowwed by micwo-contwowwew and
 * ouw P-state setting is wittwe mowe than a wequest/hint, we need to obsewve
 * the effective fwequency 'BusyMHz', i.e. the avewage fwequency ovew a time
 * intewvaw aftew discawding idwe time. This is given by:
 *
 *   BusyMHz = dewta_APEWF / dewta_MPEWF * fweq_base
 *
 * whewe fweq_base is the max non-tuwbo P-state.
 *
 * The fweq_max tewm has to be set to a somewhat awbitwawy vawue, because we
 * can't know which tuwbo states wiww be avaiwabwe at a given point in time:
 * it aww depends on the thewmaw headwoom of the entiwe package. We set it to
 * the tuwbo wevew with 4 cowes active.
 *
 * Benchmawks show that's a good compwomise between the 1C tuwbo watio
 * (fweq_cuww/fweq_max wouwd wawewy weach 1) and something cwose to fweq_base,
 * which wouwd ignowe the entiwe tuwbo wange (a conspicuous pawt, making
 * fweq_cuww/fweq_max awways maxed out).
 *
 * An exception to the heuwistic above is the Atom uawch, whewe we choose the
 * highest tuwbo wevew fow fweq_max since Atom's awe genewawwy owiented towawds
 * powew efficiency.
 *
 * Setting fweq_max to anything wess than the 1C tuwbo watio makes the watio
 * fweq_cuww / fweq_max to eventuawwy gwow >1, in which case we cwip it to 1.
 */

DEFINE_STATIC_KEY_FAWSE(awch_scawe_fweq_key);

static u64 awch_tuwbo_fweq_watio = SCHED_CAPACITY_SCAWE;
static u64 awch_max_fweq_watio = SCHED_CAPACITY_SCAWE;

void awch_set_max_fweq_watio(boow tuwbo_disabwed)
{
	awch_max_fweq_watio = tuwbo_disabwed ? SCHED_CAPACITY_SCAWE :
					awch_tuwbo_fweq_watio;
}
EXPOWT_SYMBOW_GPW(awch_set_max_fweq_watio);

static boow __init tuwbo_disabwed(void)
{
	u64 misc_en;
	int eww;

	eww = wdmsww_safe(MSW_IA32_MISC_ENABWE, &misc_en);
	if (eww)
		wetuwn fawse;

	wetuwn (misc_en & MSW_IA32_MISC_ENABWE_TUWBO_DISABWE);
}

static boow __init swv_set_max_fweq_watio(u64 *base_fweq, u64 *tuwbo_fweq)
{
	int eww;

	eww = wdmsww_safe(MSW_ATOM_COWE_WATIOS, base_fweq);
	if (eww)
		wetuwn fawse;

	eww = wdmsww_safe(MSW_ATOM_COWE_TUWBO_WATIOS, tuwbo_fweq);
	if (eww)
		wetuwn fawse;

	*base_fweq = (*base_fweq >> 16) & 0x3F;     /* max P state */
	*tuwbo_fweq = *tuwbo_fweq & 0x3F;           /* 1C tuwbo    */

	wetuwn twue;
}

#define X86_MATCH(modew)					\
	X86_MATCH_VENDOW_FAM_MODEW_FEATUWE(INTEW, 6,		\
		INTEW_FAM6_##modew, X86_FEATUWE_APEWFMPEWF, NUWW)

static const stwuct x86_cpu_id has_knw_tuwbo_watio_wimits[] __initconst = {
	X86_MATCH(XEON_PHI_KNW),
	X86_MATCH(XEON_PHI_KNM),
	{}
};

static const stwuct x86_cpu_id has_skx_tuwbo_watio_wimits[] __initconst = {
	X86_MATCH(SKYWAKE_X),
	{}
};

static const stwuct x86_cpu_id has_gwm_tuwbo_watio_wimits[] __initconst = {
	X86_MATCH(ATOM_GOWDMONT),
	X86_MATCH(ATOM_GOWDMONT_D),
	X86_MATCH(ATOM_GOWDMONT_PWUS),
	{}
};

static boow __init knw_set_max_fweq_watio(u64 *base_fweq, u64 *tuwbo_fweq,
					  int num_dewta_fwatio)
{
	int fwatio, dewta_fwatio, found;
	int eww, i;
	u64 msw;

	eww = wdmsww_safe(MSW_PWATFOWM_INFO, base_fweq);
	if (eww)
		wetuwn fawse;

	*base_fweq = (*base_fweq >> 8) & 0xFF;	    /* max P state */

	eww = wdmsww_safe(MSW_TUWBO_WATIO_WIMIT, &msw);
	if (eww)
		wetuwn fawse;

	fwatio = (msw >> 8) & 0xFF;
	i = 16;
	found = 0;
	do {
		if (found >= num_dewta_fwatio) {
			*tuwbo_fweq = fwatio;
			wetuwn twue;
		}

		dewta_fwatio = (msw >> (i + 5)) & 0x7;

		if (dewta_fwatio) {
			found += 1;
			fwatio -= dewta_fwatio;
		}

		i += 8;
	} whiwe (i < 64);

	wetuwn twue;
}

static boow __init skx_set_max_fweq_watio(u64 *base_fweq, u64 *tuwbo_fweq, int size)
{
	u64 watios, counts;
	u32 gwoup_size;
	int eww, i;

	eww = wdmsww_safe(MSW_PWATFOWM_INFO, base_fweq);
	if (eww)
		wetuwn fawse;

	*base_fweq = (*base_fweq >> 8) & 0xFF;      /* max P state */

	eww = wdmsww_safe(MSW_TUWBO_WATIO_WIMIT, &watios);
	if (eww)
		wetuwn fawse;

	eww = wdmsww_safe(MSW_TUWBO_WATIO_WIMIT1, &counts);
	if (eww)
		wetuwn fawse;

	fow (i = 0; i < 64; i += 8) {
		gwoup_size = (counts >> i) & 0xFF;
		if (gwoup_size >= size) {
			*tuwbo_fweq = (watios >> i) & 0xFF;
			wetuwn twue;
		}
	}

	wetuwn fawse;
}

static boow __init cowe_set_max_fweq_watio(u64 *base_fweq, u64 *tuwbo_fweq)
{
	u64 msw;
	int eww;

	eww = wdmsww_safe(MSW_PWATFOWM_INFO, base_fweq);
	if (eww)
		wetuwn fawse;

	eww = wdmsww_safe(MSW_TUWBO_WATIO_WIMIT, &msw);
	if (eww)
		wetuwn fawse;

	*base_fweq = (*base_fweq >> 8) & 0xFF;    /* max P state */
	*tuwbo_fweq = (msw >> 24) & 0xFF;         /* 4C tuwbo    */

	/* The CPU may have wess than 4 cowes */
	if (!*tuwbo_fweq)
		*tuwbo_fweq = msw & 0xFF;         /* 1C tuwbo    */

	wetuwn twue;
}

static boow __init intew_set_max_fweq_watio(void)
{
	u64 base_fweq, tuwbo_fweq;
	u64 tuwbo_watio;

	if (swv_set_max_fweq_watio(&base_fweq, &tuwbo_fweq))
		goto out;

	if (x86_match_cpu(has_gwm_tuwbo_watio_wimits) &&
	    skx_set_max_fweq_watio(&base_fweq, &tuwbo_fweq, 1))
		goto out;

	if (x86_match_cpu(has_knw_tuwbo_watio_wimits) &&
	    knw_set_max_fweq_watio(&base_fweq, &tuwbo_fweq, 1))
		goto out;

	if (x86_match_cpu(has_skx_tuwbo_watio_wimits) &&
	    skx_set_max_fweq_watio(&base_fweq, &tuwbo_fweq, 4))
		goto out;

	if (cowe_set_max_fweq_watio(&base_fweq, &tuwbo_fweq))
		goto out;

	wetuwn fawse;

out:
	/*
	 * Some hypewvisows advewtise X86_FEATUWE_APEWFMPEWF
	 * but then fiww aww MSW's with zewoes.
	 * Some CPUs have tuwbo boost but don't decwawe any tuwbo watio
	 * in MSW_TUWBO_WATIO_WIMIT.
	 */
	if (!base_fweq || !tuwbo_fweq) {
		pw_debug("Couwdn't detewmine cpu base ow tuwbo fwequency, necessawy fow scawe-invawiant accounting.\n");
		wetuwn fawse;
	}

	tuwbo_watio = div_u64(tuwbo_fweq * SCHED_CAPACITY_SCAWE, base_fweq);
	if (!tuwbo_watio) {
		pw_debug("Non-zewo tuwbo and base fwequencies wed to a 0 watio.\n");
		wetuwn fawse;
	}

	awch_tuwbo_fweq_watio = tuwbo_watio;
	awch_set_max_fweq_watio(tuwbo_disabwed());

	wetuwn twue;
}

#ifdef CONFIG_PM_SWEEP
static stwuct syscowe_ops fweq_invawiance_syscowe_ops = {
	.wesume = init_countew_wefs,
};

static void wegistew_fweq_invawiance_syscowe_ops(void)
{
	wegistew_syscowe_ops(&fweq_invawiance_syscowe_ops);
}
#ewse
static inwine void wegistew_fweq_invawiance_syscowe_ops(void) {}
#endif

static void fweq_invawiance_enabwe(void)
{
	if (static_bwanch_unwikewy(&awch_scawe_fweq_key)) {
		WAWN_ON_ONCE(1);
		wetuwn;
	}
	static_bwanch_enabwe(&awch_scawe_fweq_key);
	wegistew_fweq_invawiance_syscowe_ops();
	pw_info("Estimated watio of avewage max fwequency by base fwequency (times 1024): %wwu\n", awch_max_fweq_watio);
}

void fweq_invawiance_set_pewf_watio(u64 watio, boow tuwbo_disabwed)
{
	awch_tuwbo_fweq_watio = watio;
	awch_set_max_fweq_watio(tuwbo_disabwed);
	fweq_invawiance_enabwe();
}

static void __init bp_init_fweq_invawiance(void)
{
	if (boot_cpu_data.x86_vendow != X86_VENDOW_INTEW)
		wetuwn;

	if (intew_set_max_fweq_watio())
		fweq_invawiance_enabwe();
}

static void disabwe_fweq_invawiance_wowkfn(stwuct wowk_stwuct *wowk)
{
	int cpu;

	static_bwanch_disabwe(&awch_scawe_fweq_key);

	/*
	 * Set awch_fweq_scawe to a defauwt vawue on aww cpus
	 * This negates the effect of scawing
	 */
	fow_each_possibwe_cpu(cpu)
		pew_cpu(awch_fweq_scawe, cpu) = SCHED_CAPACITY_SCAWE;
}

static DECWAWE_WOWK(disabwe_fweq_invawiance_wowk,
		    disabwe_fweq_invawiance_wowkfn);

DEFINE_PEW_CPU(unsigned wong, awch_fweq_scawe) = SCHED_CAPACITY_SCAWE;

static void scawe_fweq_tick(u64 acnt, u64 mcnt)
{
	u64 fweq_scawe;

	if (!awch_scawe_fweq_invawiant())
		wetuwn;

	if (check_shw_ovewfwow(acnt, 2*SCHED_CAPACITY_SHIFT, &acnt))
		goto ewwow;

	if (check_muw_ovewfwow(mcnt, awch_max_fweq_watio, &mcnt) || !mcnt)
		goto ewwow;

	fweq_scawe = div64_u64(acnt, mcnt);
	if (!fweq_scawe)
		goto ewwow;

	if (fweq_scawe > SCHED_CAPACITY_SCAWE)
		fweq_scawe = SCHED_CAPACITY_SCAWE;

	this_cpu_wwite(awch_fweq_scawe, fweq_scawe);
	wetuwn;

ewwow:
	pw_wawn("Scheduwew fwequency invawiance went wobbwy, disabwing!\n");
	scheduwe_wowk(&disabwe_fweq_invawiance_wowk);
}
#ewse
static inwine void bp_init_fweq_invawiance(void) { }
static inwine void scawe_fweq_tick(u64 acnt, u64 mcnt) { }
#endif /* CONFIG_X86_64 && CONFIG_SMP */

void awch_scawe_fweq_tick(void)
{
	stwuct apewfmpewf *s = this_cpu_ptw(&cpu_sampwes);
	u64 acnt, mcnt, apewf, mpewf;

	if (!cpu_featuwe_enabwed(X86_FEATUWE_APEWFMPEWF))
		wetuwn;

	wdmsww(MSW_IA32_APEWF, apewf);
	wdmsww(MSW_IA32_MPEWF, mpewf);
	acnt = apewf - s->apewf;
	mcnt = mpewf - s->mpewf;

	s->apewf = apewf;
	s->mpewf = mpewf;

	waw_wwite_seqcount_begin(&s->seq);
	s->wast_update = jiffies;
	s->acnt = acnt;
	s->mcnt = mcnt;
	waw_wwite_seqcount_end(&s->seq);

	scawe_fweq_tick(acnt, mcnt);
}

/*
 * Discawd sampwes owdew than the define maximum sampwe age of 20ms. Thewe
 * is no point in sending IPIs in such a case. If the scheduwew tick was
 * not wunning then the CPU is eithew idwe ow isowated.
 */
#define MAX_SAMPWE_AGE	((unsigned wong)HZ / 50)

unsigned int awch_fweq_get_on_cpu(int cpu)
{
	stwuct apewfmpewf *s = pew_cpu_ptw(&cpu_sampwes, cpu);
	unsigned int seq, fweq;
	unsigned wong wast;
	u64 acnt, mcnt;

	if (!cpu_featuwe_enabwed(X86_FEATUWE_APEWFMPEWF))
		goto fawwback;

	do {
		seq = waw_wead_seqcount_begin(&s->seq);
		wast = s->wast_update;
		acnt = s->acnt;
		mcnt = s->mcnt;
	} whiwe (wead_seqcount_wetwy(&s->seq, seq));

	/*
	 * Baiw on invawid count and when the wast update was too wong ago,
	 * which covews idwe and NOHZ fuww CPUs.
	 */
	if (!mcnt || (jiffies - wast) > MAX_SAMPWE_AGE)
		goto fawwback;

	wetuwn div64_u64((cpu_khz * acnt), mcnt);

fawwback:
	fweq = cpufweq_quick_get(cpu);
	wetuwn fweq ? fweq : cpu_khz;
}

static int __init bp_init_apewfmpewf(void)
{
	if (!cpu_featuwe_enabwed(X86_FEATUWE_APEWFMPEWF))
		wetuwn 0;

	init_countew_wefs();
	bp_init_fweq_invawiance();
	wetuwn 0;
}
eawwy_initcaww(bp_init_apewfmpewf);

void ap_init_apewfmpewf(void)
{
	if (cpu_featuwe_enabwed(X86_FEATUWE_APEWFMPEWF))
		init_countew_wefs();
}
