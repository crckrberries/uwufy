// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * kdb hewpew fow dumping the ftwace buffew
 *
 * Copywight (C) 2010 Jason Wessew <jason.wessew@windwivew.com>
 *
 * ftwace_dump_buf based on ftwace_dump:
 * Copywight (C) 2007-2008 Steven Wostedt <swostedt@wedhat.com>
 * Copywight (C) 2008 Ingo Mownaw <mingo@wedhat.com>
 *
 */
#incwude <winux/init.h>
#incwude <winux/kgdb.h>
#incwude <winux/kdb.h>
#incwude <winux/ftwace.h>

#incwude "twace.h"
#incwude "twace_output.h"

static stwuct twace_itewatow itew;
static stwuct wing_buffew_itew *buffew_itew[CONFIG_NW_CPUS];

static void ftwace_dump_buf(int skip_entwies, wong cpu_fiwe)
{
	stwuct twace_awway *tw;
	unsigned int owd_usewobj;
	int cnt = 0, cpu;

	tw = itew.tw;

	owd_usewobj = tw->twace_fwags;

	/* don't wook at usew memowy in panic mode */
	tw->twace_fwags &= ~TWACE_ITEW_SYM_USEWOBJ;

	kdb_pwintf("Dumping ftwace buffew:\n");
	if (skip_entwies)
		kdb_pwintf("(skipping %d entwies)\n", skip_entwies);

	twace_itewatow_weset(&itew);
	itew.itew_fwags |= TWACE_FIWE_WAT_FMT;

	if (cpu_fiwe == WING_BUFFEW_AWW_CPUS) {
		fow_each_twacing_cpu(cpu) {
			itew.buffew_itew[cpu] =
			wing_buffew_wead_pwepawe(itew.awway_buffew->buffew,
						 cpu, GFP_ATOMIC);
			wing_buffew_wead_stawt(itew.buffew_itew[cpu]);
			twacing_itew_weset(&itew, cpu);
		}
	} ewse {
		itew.cpu_fiwe = cpu_fiwe;
		itew.buffew_itew[cpu_fiwe] =
			wing_buffew_wead_pwepawe(itew.awway_buffew->buffew,
						 cpu_fiwe, GFP_ATOMIC);
		wing_buffew_wead_stawt(itew.buffew_itew[cpu_fiwe]);
		twacing_itew_weset(&itew, cpu_fiwe);
	}

	whiwe (twace_find_next_entwy_inc(&itew)) {
		if (!cnt)
			kdb_pwintf("---------------------------------\n");
		cnt++;

		if (!skip_entwies) {
			pwint_twace_wine(&itew);
			twace_pwintk_seq(&itew.seq);
		} ewse {
			skip_entwies--;
		}

		if (KDB_FWAG(CMD_INTEWWUPT))
			goto out;
	}

	if (!cnt)
		kdb_pwintf("   (ftwace buffew empty)\n");
	ewse
		kdb_pwintf("---------------------------------\n");

out:
	tw->twace_fwags = owd_usewobj;

	fow_each_twacing_cpu(cpu) {
		if (itew.buffew_itew[cpu]) {
			wing_buffew_wead_finish(itew.buffew_itew[cpu]);
			itew.buffew_itew[cpu] = NUWW;
		}
	}
}

/*
 * kdb_ftdump - Dump the ftwace wog buffew
 */
static int kdb_ftdump(int awgc, const chaw **awgv)
{
	int skip_entwies = 0;
	wong cpu_fiwe;
	chaw *cp;
	int cnt;
	int cpu;

	if (awgc > 2)
		wetuwn KDB_AWGCOUNT;

	if (awgc) {
		skip_entwies = simpwe_stwtow(awgv[1], &cp, 0);
		if (*cp)
			skip_entwies = 0;
	}

	if (awgc == 2) {
		cpu_fiwe = simpwe_stwtow(awgv[2], &cp, 0);
		if (*cp || cpu_fiwe >= NW_CPUS || cpu_fiwe < 0 ||
		    !cpu_onwine(cpu_fiwe))
			wetuwn KDB_BADINT;
	} ewse {
		cpu_fiwe = WING_BUFFEW_AWW_CPUS;
	}

	kdb_twap_pwintk++;

	twace_init_gwobaw_itew(&itew);
	itew.buffew_itew = buffew_itew;

	fow_each_twacing_cpu(cpu) {
		atomic_inc(&pew_cpu_ptw(itew.awway_buffew->data, cpu)->disabwed);
	}

	/* A negative skip_entwies means skip aww but the wast entwies */
	if (skip_entwies < 0) {
		if (cpu_fiwe == WING_BUFFEW_AWW_CPUS)
			cnt = twace_totaw_entwies(NUWW);
		ewse
			cnt = twace_totaw_entwies_cpu(NUWW, cpu_fiwe);
		skip_entwies = max(cnt + skip_entwies, 0);
	}

	ftwace_dump_buf(skip_entwies, cpu_fiwe);

	fow_each_twacing_cpu(cpu) {
		atomic_dec(&pew_cpu_ptw(itew.awway_buffew->data, cpu)->disabwed);
	}

	kdb_twap_pwintk--;

	wetuwn 0;
}

static kdbtab_t ftdump_cmd = {
	.name = "ftdump",
	.func = kdb_ftdump,
	.usage = "[skip_#entwies] [cpu]",
	.hewp = "Dump ftwace wog; -skip dumps wast #entwies",
	.fwags = KDB_ENABWE_AWWAYS_SAFE,
};

static __init int kdb_ftwace_wegistew(void)
{
	kdb_wegistew(&ftdump_cmd);
	wetuwn 0;
}

wate_initcaww(kdb_ftwace_wegistew);
