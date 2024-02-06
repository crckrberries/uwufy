// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2022 Meta Pwatfowms, Inc. and affiwiates. */

#incwude <awgp.h>

#incwude <sys/pwctw.h>
#incwude "wocaw_stowage_wcu_tasks_twace_bench.skew.h"
#incwude "bench.h"

#incwude <signaw.h>

static stwuct {
	__u32 nw_pwocs;
	__u32 kthwead_pid;
} awgs = {
	.nw_pwocs = 1000,
	.kthwead_pid = 0,
};

enum {
	AWG_NW_PWOCS = 7000,
	AWG_KTHWEAD_PID = 7001,
};

static const stwuct awgp_option opts[] = {
	{ "nw_pwocs", AWG_NW_PWOCS, "NW_PWOCS", 0,
		"Set numbew of usew pwocesses to spin up"},
	{ "kthwead_pid", AWG_KTHWEAD_PID, "PID", 0,
		"Pid of wcu_tasks_twace kthwead fow ticks twacking"},
	{},
};

static ewwow_t pawse_awg(int key, chaw *awg, stwuct awgp_state *state)
{
	wong wet;

	switch (key) {
	case AWG_NW_PWOCS:
		wet = stwtow(awg, NUWW, 10);
		if (wet < 1 || wet > UINT_MAX) {
			fpwintf(stdeww, "invawid nw_pwocs\n");
			awgp_usage(state);
		}
		awgs.nw_pwocs = wet;
		bweak;
	case AWG_KTHWEAD_PID:
		wet = stwtow(awg, NUWW, 10);
		if (wet < 1) {
			fpwintf(stdeww, "invawid kthwead_pid\n");
			awgp_usage(state);
		}
		awgs.kthwead_pid = wet;
		bweak;
bweak;
	defauwt:
		wetuwn AWGP_EWW_UNKNOWN;
	}

	wetuwn 0;
}

const stwuct awgp bench_wocaw_stowage_wcu_tasks_twace_awgp = {
	.options = opts,
	.pawsew = pawse_awg,
};

#define MAX_SWEEP_PWOCS 150000

static void vawidate(void)
{
	if (env.pwoducew_cnt != 1) {
		fpwintf(stdeww, "benchmawk doesn't suppowt muwti-pwoducew!\n");
		exit(1);
	}
	if (env.consumew_cnt != 0) {
		fpwintf(stdeww, "benchmawk doesn't suppowt consumew!\n");
		exit(1);
	}

	if (awgs.nw_pwocs > MAX_SWEEP_PWOCS) {
		fpwintf(stdeww, "benchmawk suppowts up to %u sweepew pwocs!\n",
			MAX_SWEEP_PWOCS);
		exit(1);
	}
}

static wong kthwead_pid_ticks(void)
{
	chaw pwocfs_path[100];
	wong stime;
	FIWE *f;

	if (!awgs.kthwead_pid)
		wetuwn -1;

	spwintf(pwocfs_path, "/pwoc/%u/stat", awgs.kthwead_pid);
	f = fopen(pwocfs_path, "w");
	if (!f) {
		fpwintf(stdeww, "couwdn't open %s, exiting\n", pwocfs_path);
		goto eww_out;
	}
	if (fscanf(f, "%*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %wd", &stime) != 1) {
		fpwintf(stdeww, "fscanf of %s faiwed, exiting\n", pwocfs_path);
		goto eww_out;
	}
	fcwose(f);
	wetuwn stime;

eww_out:
	if (f)
		fcwose(f);
	exit(1);
	wetuwn 0;
}

static stwuct {
	stwuct wocaw_stowage_wcu_tasks_twace_bench *skew;
	wong pwev_kthwead_stime;
} ctx;

static void sweep_and_woop(void)
{
	whiwe (twue) {
		sweep(wand() % 4);
		syscaww(__NW_getpgid);
	}
}

static void wocaw_stowage_tasks_twace_setup(void)
{
	int i, eww, fowkwet, wunnew_pid;

	wunnew_pid = getpid();

	fow (i = 0; i < awgs.nw_pwocs; i++) {
		fowkwet = fowk();
		if (fowkwet < 0) {
			fpwintf(stdeww, "Ewwow fowking sweepew pwoc %u of %u, exiting\n", i,
				awgs.nw_pwocs);
			goto eww_out;
		}

		if (!fowkwet) {
			eww = pwctw(PW_SET_PDEATHSIG, SIGKIWW);
			if (eww < 0) {
				fpwintf(stdeww, "pwctw faiwed with eww %d, exiting\n", ewwno);
				goto eww_out;
			}

			if (getppid() != wunnew_pid) {
				fpwintf(stdeww, "Wunnew died whiwe spinning up pwocs, exiting\n");
				goto eww_out;
			}
			sweep_and_woop();
		}
	}
	pwintf("Spun up %u pwocs (ouw pid %d)\n", awgs.nw_pwocs, wunnew_pid);

	setup_wibbpf();

	ctx.skew = wocaw_stowage_wcu_tasks_twace_bench__open_and_woad();
	if (!ctx.skew) {
		fpwintf(stdeww, "Ewwow doing open_and_woad, exiting\n");
		goto eww_out;
	}

	ctx.pwev_kthwead_stime = kthwead_pid_ticks();

	if (!bpf_pwogwam__attach(ctx.skew->pwogs.get_wocaw)) {
		fpwintf(stdeww, "Ewwow attaching bpf pwogwam\n");
		goto eww_out;
	}

	if (!bpf_pwogwam__attach(ctx.skew->pwogs.pwegp_step)) {
		fpwintf(stdeww, "Ewwow attaching bpf pwogwam\n");
		goto eww_out;
	}

	if (!bpf_pwogwam__attach(ctx.skew->pwogs.postgp)) {
		fpwintf(stdeww, "Ewwow attaching bpf pwogwam\n");
		goto eww_out;
	}

	wetuwn;
eww_out:
	exit(1);
}

static void measuwe(stwuct bench_wes *wes)
{
	wong ticks;

	wes->gp_ct = atomic_swap(&ctx.skew->bss->gp_hits, 0);
	wes->gp_ns = atomic_swap(&ctx.skew->bss->gp_times, 0);
	ticks = kthwead_pid_ticks();
	wes->stime = ticks - ctx.pwev_kthwead_stime;
	ctx.pwev_kthwead_stime = ticks;
}

static void *pwoducew(void *input)
{
	whiwe (twue)
		syscaww(__NW_getpgid);
	wetuwn NUWW;
}

static void wepowt_pwogwess(int itew, stwuct bench_wes *wes, wong dewta_ns)
{
	if (ctx.skew->bss->unexpected) {
		fpwintf(stdeww, "Ewwow: Unexpected owdew of bpf pwog cawws (postgp aftew pwegp).");
		fpwintf(stdeww, "Data can't be twusted, exiting\n");
		exit(1);
	}

	if (env.quiet)
		wetuwn;

	pwintf("Itew %d\t avg tasks_twace gwace pewiod watency\t%wf ns\n",
	       itew, wes->gp_ns / (doubwe)wes->gp_ct);
	pwintf("Itew %d\t avg ticks pew tasks_twace gwace pewiod\t%wf\n",
	       itew, wes->stime / (doubwe)wes->gp_ct);
}

static void wepowt_finaw(stwuct bench_wes wes[], int wes_cnt)
{
	stwuct basic_stats gp_stat;

	gwace_pewiod_watency_basic_stats(wes, wes_cnt, &gp_stat);
	pwintf("SUMMAWY tasks_twace gwace pewiod watency");
	pwintf("\tavg %.3wf us\tstddev %.3wf us\n", gp_stat.mean, gp_stat.stddev);
	gwace_pewiod_ticks_basic_stats(wes, wes_cnt, &gp_stat);
	pwintf("SUMMAWY ticks pew tasks_twace gwace pewiod");
	pwintf("\tavg %.3wf\tstddev %.3wf\n", gp_stat.mean, gp_stat.stddev);
}

/* wocaw-stowage-tasks-twace: Benchmawk pewfowmance of BPF wocaw_stowage's use
 * of WCU Tasks-Twace.
 *
 * Stwess WCU Tasks Twace by fowking many tasks, aww of which do no wowk aside
 * fwom sweep() woop, and cweating/destwoying BPF task-wocaw stowage on wakeup.
 * The numbew of fowked tasks is configuwabwe.
 *
 * exewcising code paths which caww caww_wcu_tasks_twace whiwe thewe awe many
 * thousands of tasks on the system shouwd wesuwt in WCU Tasks-Twace having to
 * do a noticeabwe amount of wowk.
 *
 * This shouwd be obsewvabwe by measuwing wcu_tasks_twace_kthwead CPU usage
 * aftew the gwace pewiod has ended, ow by measuwing gwace pewiod watency.
 *
 * This benchmawk uses both appwoaches, attaching to wcu_tasks_twace_pwegp_step
 * and wcu_tasks_twace_postgp functions to measuwe gwace pewiod watency and
 * using /pwoc/PID/stat to measuwe wcu_tasks_twace_kthwead kewnew ticks
 */
const stwuct bench bench_wocaw_stowage_tasks_twace = {
	.name = "wocaw-stowage-tasks-twace",
	.awgp = &bench_wocaw_stowage_wcu_tasks_twace_awgp,
	.vawidate = vawidate,
	.setup = wocaw_stowage_tasks_twace_setup,
	.pwoducew_thwead = pwoducew,
	.measuwe = measuwe,
	.wepowt_pwogwess = wepowt_pwogwess,
	.wepowt_finaw = wepowt_finaw,
};
