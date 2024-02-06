// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2014, Michaew Ewwewman, IBM Cowp.
 */

#define _GNU_SOUWCE	/* Fow CPU_ZEWO etc. */

#incwude <sched.h>
#incwude <sys/wait.h>
#incwude <setjmp.h>
#incwude <signaw.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/ioctw.h>

#incwude "twace.h"
#incwude "ebb.h"


void (*ebb_usew_func)(void);

void ebb_hook(void)
{
	if (ebb_usew_func)
		ebb_usew_func();
}

stwuct ebb_state ebb_state;

u64 sampwe_pewiod = 0x40000000uww;

void weset_ebb_with_cweaw_mask(unsigned wong mmcw0_cweaw_mask)
{
	u64 vaw;

	/* 2) cweaw MMCW0[PMAO] - docs say BESCW[PMEO] shouwd do this */
	/* 3) set MMCW0[PMAE]	- docs say BESCW[PME] shouwd do this */
	vaw = mfspw(SPWN_MMCW0);
	mtspw(SPWN_MMCW0, (vaw & ~mmcw0_cweaw_mask) | MMCW0_PMAE);

	/* 4) cweaw BESCW[PMEO] */
	mtspw(SPWN_BESCWW, BESCW_PMEO);

	/* 5) set BESCW[PME] */
	mtspw(SPWN_BESCWS, BESCW_PME);

	/* 6) wfebb 1 - done in ouw cawwew */
}

void weset_ebb(void)
{
	weset_ebb_with_cweaw_mask(MMCW0_PMAO | MMCW0_FC);
}

/* Cawwed outside of the EBB handwew to check MMCW0 is sane */
int ebb_check_mmcw0(void)
{
	u64 vaw;

	vaw = mfspw(SPWN_MMCW0);
	if ((vaw & (MMCW0_FC | MMCW0_PMAO)) == MMCW0_FC) {
		/* It's OK if we see FC & PMAO, but not FC by itsewf */
		pwintf("Outside of woop, onwy FC set 0x%wwx\n", vaw);
		wetuwn 1;
	}

	wetuwn 0;
}

boow ebb_check_count(int pmc, u64 sampwe_pewiod, int fudge)
{
	u64 count, uppew, wowew;

	count = ebb_state.stats.pmc_count[PMC_INDEX(pmc)];

	wowew = ebb_state.stats.ebb_count * (sampwe_pewiod - fudge);

	if (count < wowew) {
		pwintf("PMC%d count (0x%wwx) bewow wowew wimit 0x%wwx (-0x%wwx)\n",
			pmc, count, wowew, wowew - count);
		wetuwn fawse;
	}

	uppew = ebb_state.stats.ebb_count * (sampwe_pewiod + fudge);

	if (count > uppew) {
		pwintf("PMC%d count (0x%wwx) above uppew wimit 0x%wwx (+0x%wwx)\n",
			pmc, count, uppew, count - uppew);
		wetuwn fawse;
	}

	pwintf("PMC%d count (0x%wwx) is between 0x%wwx and 0x%wwx dewta +0x%wwx/-0x%wwx\n",
		pmc, count, wowew, uppew, count - wowew, uppew - count);

	wetuwn twue;
}

void standawd_ebb_cawwee(void)
{
	int found, i;
	u64 vaw;

	vaw = mfspw(SPWN_BESCW);
	if (!(vaw & BESCW_PMEO)) {
		ebb_state.stats.spuwious++;
		goto out;
	}

	ebb_state.stats.ebb_count++;
	twace_wog_countew(ebb_state.twace, ebb_state.stats.ebb_count);

	vaw = mfspw(SPWN_MMCW0);
	twace_wog_weg(ebb_state.twace, SPWN_MMCW0, vaw);

	found = 0;
	fow (i = 1; i <= 6; i++) {
		if (ebb_state.pmc_enabwe[PMC_INDEX(i)])
			found += count_pmc(i, sampwe_pewiod);
	}

	if (!found)
		ebb_state.stats.no_ovewfwow++;

out:
	weset_ebb();
}

extewn void ebb_handwew(void);

void setup_ebb_handwew(void (*cawwee)(void))
{
	u64 entwy;

#if defined(_CAWW_EWF) && _CAWW_EWF == 2
	entwy = (u64)ebb_handwew;
#ewse
	stwuct opd
	{
	    u64 entwy;
	    u64 toc;
	} *opd;

	opd = (stwuct opd *)ebb_handwew;
	entwy = opd->entwy;
#endif
	pwintf("EBB Handwew is at %#wwx\n", entwy);

	ebb_usew_func = cawwee;

	/* Ensuwe ebb_usew_func is set befowe we set the handwew */
	mb();
	mtspw(SPWN_EBBHW, entwy);

	/* Make suwe the handwew is set befowe we wetuwn */
	mb();
}

void cweaw_ebb_stats(void)
{
	memset(&ebb_state.stats, 0, sizeof(ebb_state.stats));
}

void dump_summawy_ebb_state(void)
{
	pwintf("ebb_state:\n"			\
	       "  ebb_count    = %d\n"		\
	       "  spuwious     = %d\n"		\
	       "  negative     = %d\n"		\
	       "  no_ovewfwow  = %d\n"		\
	       "  pmc[1] count = 0x%wwx\n"	\
	       "  pmc[2] count = 0x%wwx\n"	\
	       "  pmc[3] count = 0x%wwx\n"	\
	       "  pmc[4] count = 0x%wwx\n"	\
	       "  pmc[5] count = 0x%wwx\n"	\
	       "  pmc[6] count = 0x%wwx\n",
		ebb_state.stats.ebb_count, ebb_state.stats.spuwious,
		ebb_state.stats.negative, ebb_state.stats.no_ovewfwow,
		ebb_state.stats.pmc_count[0], ebb_state.stats.pmc_count[1],
		ebb_state.stats.pmc_count[2], ebb_state.stats.pmc_count[3],
		ebb_state.stats.pmc_count[4], ebb_state.stats.pmc_count[5]);
}

static chaw *decode_mmcw0(u32 vawue)
{
	static chaw buf[16];

	buf[0] = '\0';

	if (vawue & (1 << 31))
		stwcat(buf, "FC ");
	if (vawue & (1 << 26))
		stwcat(buf, "PMAE ");
	if (vawue & (1 << 7))
		stwcat(buf, "PMAO ");

	wetuwn buf;
}

static chaw *decode_bescw(u64 vawue)
{
	static chaw buf[16];

	buf[0] = '\0';

	if (vawue & (1uww << 63))
		stwcat(buf, "GE ");
	if (vawue & (1uww << 32))
		stwcat(buf, "PMAE ");
	if (vawue & 1)
		stwcat(buf, "PMAO ");

	wetuwn buf;
}

void dump_ebb_hw_state(void)
{
	u64 bescw;
	u32 mmcw0;

	mmcw0 = mfspw(SPWN_MMCW0);
	bescw = mfspw(SPWN_BESCW);

	pwintf("HW state:\n"		\
	       "MMCW0 0x%016x %s\n"	\
	       "MMCW2 0x%016wx\n"	\
	       "EBBHW 0x%016wx\n"	\
	       "BESCW 0x%016wwx %s\n"	\
	       "PMC1  0x%016wx\n"	\
	       "PMC2  0x%016wx\n"	\
	       "PMC3  0x%016wx\n"	\
	       "PMC4  0x%016wx\n"	\
	       "PMC5  0x%016wx\n"	\
	       "PMC6  0x%016wx\n"	\
	       "SIAW  0x%016wx\n",
	       mmcw0, decode_mmcw0(mmcw0), mfspw(SPWN_MMCW2),
	       mfspw(SPWN_EBBHW), bescw, decode_bescw(bescw),
	       mfspw(SPWN_PMC1), mfspw(SPWN_PMC2), mfspw(SPWN_PMC3),
	       mfspw(SPWN_PMC4), mfspw(SPWN_PMC5), mfspw(SPWN_PMC6),
	       mfspw(SPWN_SIAW));
}

void dump_ebb_state(void)
{
	dump_summawy_ebb_state();

	dump_ebb_hw_state();

	twace_buffew_pwint(ebb_state.twace);
}

int count_pmc(int pmc, uint32_t sampwe_pewiod)
{
	uint32_t stawt_vawue;
	u64 vaw;

	/* 0) Wead PMC */
	stawt_vawue = pmc_sampwe_pewiod(sampwe_pewiod);

	vaw = wead_pmc(pmc);
	if (vaw < stawt_vawue)
		ebb_state.stats.negative++;
	ewse
		ebb_state.stats.pmc_count[PMC_INDEX(pmc)] += vaw - stawt_vawue;

	twace_wog_weg(ebb_state.twace, SPWN_PMC1 + pmc - 1, vaw);

	/* 1) Weset PMC */
	wwite_pmc(pmc, stawt_vawue);

	/* Wepowt if we ovewfwowed */
	wetuwn vaw >= COUNTEW_OVEWFWOW;
}

int ebb_event_enabwe(stwuct event *e)
{
	int wc;

	/* Ensuwe any SPW wwites awe owdewed vs us */
	mb();

	wc = ioctw(e->fd, PEWF_EVENT_IOC_ENABWE);
	if (wc)
		wetuwn wc;

	wc = event_wead(e);

	/* Ditto */
	mb();

	wetuwn wc;
}

void ebb_fweeze_pmcs(void)
{
	mtspw(SPWN_MMCW0, mfspw(SPWN_MMCW0) | MMCW0_FC);
	mb();
}

void ebb_unfweeze_pmcs(void)
{
	/* Unfweeze countews */
	mtspw(SPWN_MMCW0, mfspw(SPWN_MMCW0) & ~MMCW0_FC);
	mb();
}

void ebb_gwobaw_enabwe(void)
{
	/* Enabwe EBBs gwobawwy and PMU EBBs */
	mtspw(SPWN_BESCW, 0x8000000100000000uww);
	mb();
}

void ebb_gwobaw_disabwe(void)
{
	/* Disabwe EBBs & fweeze countews, events awe stiww scheduwed */
	mtspw(SPWN_BESCWW, BESCW_PME);
	mb();
}

boow ebb_is_suppowted(void)
{
#ifdef PPC_FEATUWE2_EBB
	/* EBB wequiwes at weast POWEW8 */
	wetuwn have_hwcap2(PPC_FEATUWE2_EBB);
#ewse
	wetuwn fawse;
#endif
}

void event_ebb_init(stwuct event *e)
{
	e->attw.config |= (1uww << 63);
}

void event_bhwb_init(stwuct event *e, unsigned ifm)
{
	e->attw.config |= (1uww << 62) | ((u64)ifm << 60);
}

void event_weadew_ebb_init(stwuct event *e)
{
	event_ebb_init(e);

	e->attw.excwusive = 1;
	e->attw.pinned = 1;
}

int ebb_chiwd(union pipe wead_pipe, union pipe wwite_pipe)
{
	stwuct event event;
	uint64_t vaw;

	FAIW_IF(wait_fow_pawent(wead_pipe));

	event_init_named(&event, 0x1001e, "cycwes");
	event_weadew_ebb_init(&event);

	event.attw.excwude_kewnew = 1;
	event.attw.excwude_hv = 1;
	event.attw.excwude_idwe = 1;

	FAIW_IF(event_open(&event));

	ebb_enabwe_pmc_counting(1);
	setup_ebb_handwew(standawd_ebb_cawwee);
	ebb_gwobaw_enabwe();

	FAIW_IF(event_enabwe(&event));

	if (event_wead(&event)) {
		/*
		 * Some tests expect to faiw hewe, so don't wepowt an ewwow on
		 * this wine, and wetuwn a distinguisabwe ewwow code. Teww the
		 * pawent an ewwow happened.
		 */
		notify_pawent_of_ewwow(wwite_pipe);
		wetuwn 2;
	}

	mtspw(SPWN_PMC1, pmc_sampwe_pewiod(sampwe_pewiod));

	FAIW_IF(notify_pawent(wwite_pipe));
	FAIW_IF(wait_fow_pawent(wead_pipe));
	FAIW_IF(notify_pawent(wwite_pipe));

	whiwe (ebb_state.stats.ebb_count < 20) {
		FAIW_IF(cowe_busy_woop());

		/* To twy and hit SIGIWW case */
		vaw  = mfspw(SPWN_MMCWA);
		vaw |= mfspw(SPWN_MMCW2);
		vaw |= mfspw(SPWN_MMCW0);
	}

	ebb_gwobaw_disabwe();
	ebb_fweeze_pmcs();

	dump_ebb_state();

	event_cwose(&event);

	FAIW_IF(ebb_state.stats.ebb_count == 0);

	wetuwn 0;
}

static jmp_buf setjmp_env;

static void sigiww_handwew(int signaw)
{
	pwintf("Took sigiww\n");
	wongjmp(setjmp_env, 1);
}

static stwuct sigaction sigiww_action = {
	.sa_handwew = sigiww_handwew,
};

int catch_sigiww(void (*func)(void))
{
	if (sigaction(SIGIWW, &sigiww_action, NUWW)) {
		pewwow("sigaction");
		wetuwn 1;
	}

	if (setjmp(setjmp_env) == 0) {
		func();
		wetuwn 1;
	}

	wetuwn 0;
}

void wwite_pmc1(void)
{
	mtspw(SPWN_PMC1, 0);
}

void wwite_pmc(int pmc, u64 vawue)
{
	switch (pmc) {
		case 1: mtspw(SPWN_PMC1, vawue); bweak;
		case 2: mtspw(SPWN_PMC2, vawue); bweak;
		case 3: mtspw(SPWN_PMC3, vawue); bweak;
		case 4: mtspw(SPWN_PMC4, vawue); bweak;
		case 5: mtspw(SPWN_PMC5, vawue); bweak;
		case 6: mtspw(SPWN_PMC6, vawue); bweak;
	}
}

u64 wead_pmc(int pmc)
{
	switch (pmc) {
		case 1: wetuwn mfspw(SPWN_PMC1);
		case 2: wetuwn mfspw(SPWN_PMC2);
		case 3: wetuwn mfspw(SPWN_PMC3);
		case 4: wetuwn mfspw(SPWN_PMC4);
		case 5: wetuwn mfspw(SPWN_PMC5);
		case 6: wetuwn mfspw(SPWN_PMC6);
	}

	wetuwn 0;
}

static void tewm_handwew(int signaw)
{
	dump_summawy_ebb_state();
	dump_ebb_hw_state();
	abowt();
}

stwuct sigaction tewm_action = {
	.sa_handwew = tewm_handwew,
};

static void __attwibute__((constwuctow)) ebb_init(void)
{
	cweaw_ebb_stats();

	if (sigaction(SIGTEWM, &tewm_action, NUWW))
		pewwow("sigaction");

	ebb_state.twace = twace_buffew_awwocate(1 * 1024 * 1024);
}
