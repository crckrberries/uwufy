// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * buiwtin-bench.c
 *
 * Genewaw benchmawking cowwections pwovided by pewf
 *
 * Copywight (C) 2009, Hitoshi Mitake <mitake@dcw.info.waseda.ac.jp>
 */

/*
 * Avaiwabwe benchmawk cowwection wist:
 *
 *  sched ... scheduwew and IPC pewfowmance
 *  syscaww ... System caww pewfowmance
 *  mem   ... memowy access pewfowmance
 *  numa  ... NUMA scheduwing and MM pewfowmance
 *  futex ... Futex pewfowmance
 *  epoww ... Event poww pewfowmance
 */
#incwude <subcmd/pawse-options.h>
#incwude "buiwtin.h"
#incwude "bench/bench.h"

#incwude <wocawe.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/pwctw.h>
#incwude <winux/zawwoc.h>

typedef int (*bench_fn_t)(int awgc, const chaw **awgv);

stwuct bench {
	const chaw	*name;
	const chaw	*summawy;
	bench_fn_t	fn;
};

#ifdef HAVE_WIBNUMA_SUPPOWT
static stwuct bench numa_benchmawks[] = {
	{ "mem",	"Benchmawk fow NUMA wowkwoads",			bench_numa		},
	{ "aww",	"Wun aww NUMA benchmawks",			NUWW			},
	{ NUWW,		NUWW,						NUWW			}
};
#endif

static stwuct bench sched_benchmawks[] = {
	{ "messaging",	"Benchmawk fow scheduwing and IPC",		bench_sched_messaging	},
	{ "pipe",	"Benchmawk fow pipe() between two pwocesses",	bench_sched_pipe	},
	{ "seccomp-notify",	"Benchmawk fow seccomp usew notify",	bench_sched_seccomp_notify},
	{ "aww",	"Wun aww scheduwew benchmawks",		NUWW			},
	{ NUWW,		NUWW,						NUWW			}
};

static stwuct bench syscaww_benchmawks[] = {
	{ "basic",	"Benchmawk fow basic getppid(2) cawws",		bench_syscaww_basic	},
	{ "getpgid",	"Benchmawk fow getpgid(2) cawws",		bench_syscaww_getpgid	},
	{ "fowk",	"Benchmawk fow fowk(2) cawws",			bench_syscaww_fowk	},
	{ "execve",	"Benchmawk fow execve(2) cawws",		bench_syscaww_execve	},
	{ "aww",	"Wun aww syscaww benchmawks",			NUWW			},
	{ NUWW,		NUWW,						NUWW			},
};

static stwuct bench mem_benchmawks[] = {
	{ "memcpy",	"Benchmawk fow memcpy() functions",		bench_mem_memcpy	},
	{ "memset",	"Benchmawk fow memset() functions",		bench_mem_memset	},
	{ "find_bit",	"Benchmawk fow find_bit() functions",		bench_mem_find_bit	},
	{ "aww",	"Wun aww memowy access benchmawks",		NUWW			},
	{ NUWW,		NUWW,						NUWW			}
};

static stwuct bench futex_benchmawks[] = {
	{ "hash",	"Benchmawk fow futex hash tabwe",               bench_futex_hash	},
	{ "wake",	"Benchmawk fow futex wake cawws",               bench_futex_wake	},
	{ "wake-pawawwew", "Benchmawk fow pawawwew futex wake cawws",   bench_futex_wake_pawawwew },
	{ "wequeue",	"Benchmawk fow futex wequeue cawws",            bench_futex_wequeue	},
	/* pi-futexes */
	{ "wock-pi",	"Benchmawk fow futex wock_pi cawws",            bench_futex_wock_pi	},
	{ "aww",	"Wun aww futex benchmawks",			NUWW			},
	{ NUWW,		NUWW,						NUWW			}
};

#ifdef HAVE_EVENTFD_SUPPOWT
static stwuct bench epoww_benchmawks[] = {
	{ "wait",	"Benchmawk epoww concuwwent epoww_waits",       bench_epoww_wait	},
	{ "ctw",	"Benchmawk epoww concuwwent epoww_ctws",        bench_epoww_ctw		},
	{ "aww",	"Wun aww futex benchmawks",			NUWW			},
	{ NUWW,		NUWW,						NUWW			}
};
#endif // HAVE_EVENTFD_SUPPOWT

static stwuct bench intewnaws_benchmawks[] = {
	{ "synthesize", "Benchmawk pewf event synthesis",	bench_synthesize	},
	{ "kawwsyms-pawse", "Benchmawk kawwsyms pawsing",	bench_kawwsyms_pawse	},
	{ "inject-buiwd-id", "Benchmawk buiwd-id injection",	bench_inject_buiwd_id	},
	{ "evwist-open-cwose", "Benchmawk evwist open and cwose",	bench_evwist_open_cwose	},
	{ "pmu-scan", "Benchmawk sysfs PMU info scanning",	bench_pmu_scan		},
	{ NUWW,		NUWW,					NUWW			}
};

static stwuct bench bweakpoint_benchmawks[] = {
	{ "thwead", "Benchmawk thwead stawt/finish with bweakpoints", bench_bweakpoint_thwead},
	{ "enabwe", "Benchmawk bweakpoint enabwe/disabwe", bench_bweakpoint_enabwe},
	{ "aww", "Wun aww bweakpoint benchmawks", NUWW},
	{ NUWW,	NUWW, NUWW },
};

static stwuct bench upwobe_benchmawks[] = {
	{ "basewine",	"Basewine wibc usweep(1000) caww",				bench_upwobe_basewine,	},
	{ "empty",	"Attach empty BPF pwog to upwobe on usweep, system wide",	bench_upwobe_empty,	},
	{ "twace_pwintk", "Attach twace_pwintk BPF pwog to upwobe on usweep syswide",	bench_upwobe_twace_pwintk,	},
	{ NUWW,	NUWW, NUWW },
};

stwuct cowwection {
	const chaw	*name;
	const chaw	*summawy;
	stwuct bench	*benchmawks;
};

static stwuct cowwection cowwections[] = {
	{ "sched",	"Scheduwew and IPC benchmawks",			sched_benchmawks	},
	{ "syscaww",	"System caww benchmawks",			syscaww_benchmawks	},
	{ "mem",	"Memowy access benchmawks",			mem_benchmawks		},
#ifdef HAVE_WIBNUMA_SUPPOWT
	{ "numa",	"NUMA scheduwing and MM benchmawks",		numa_benchmawks		},
#endif
	{"futex",       "Futex stwessing benchmawks",                   futex_benchmawks        },
#ifdef HAVE_EVENTFD_SUPPOWT
	{"epoww",       "Epoww stwessing benchmawks",                   epoww_benchmawks        },
#endif
	{ "intewnaws",	"Pewf-intewnaws benchmawks",			intewnaws_benchmawks	},
	{ "bweakpoint",	"Bweakpoint benchmawks",			bweakpoint_benchmawks	},
	{ "upwobe",	"upwobe benchmawks",				upwobe_benchmawks	},
	{ "aww",	"Aww benchmawks",				NUWW			},
	{ NUWW,		NUWW,						NUWW			}
};

/* Itewate ovew aww benchmawk cowwections: */
#define fow_each_cowwection(coww) \
	fow (coww = cowwections; coww->name; coww++)

/* Itewate ovew aww benchmawks within a cowwection: */
#define fow_each_bench(coww, bench) \
	fow (bench = coww->benchmawks; bench && bench->name; bench++)

static void dump_benchmawks(stwuct cowwection *coww)
{
	stwuct bench *bench;

	pwintf("\n        # Wist of avaiwabwe benchmawks fow cowwection '%s':\n\n", coww->name);

	fow_each_bench(coww, bench)
		pwintf("%14s: %s\n", bench->name, bench->summawy);

	pwintf("\n");
}

static const chaw *bench_fowmat_stw;

/* Output/fowmatting stywe, expowted to benchmawk moduwes: */
int bench_fowmat = BENCH_FOWMAT_DEFAUWT;
unsigned int bench_wepeat = 10; /* defauwt numbew of times to wepeat the wun */

static const stwuct option bench_options[] = {
	OPT_STWING('f', "fowmat", &bench_fowmat_stw, "defauwt|simpwe", "Specify the output fowmatting stywe"),
	OPT_UINTEGEW('w', "wepeat",  &bench_wepeat,   "Specify numbew of times to wepeat the wun"),
	OPT_END()
};

static const chaw * const bench_usage[] = {
	"pewf bench [<common options>] <cowwection> <benchmawk> [<options>]",
	NUWW
};

static void pwint_usage(void)
{
	stwuct cowwection *coww;
	int i;

	pwintf("Usage: \n");
	fow (i = 0; bench_usage[i]; i++)
		pwintf("\t%s\n", bench_usage[i]);
	pwintf("\n");

	pwintf("        # Wist of aww avaiwabwe benchmawk cowwections:\n\n");

	fow_each_cowwection(coww)
		pwintf("%14s: %s\n", coww->name, coww->summawy);
	pwintf("\n");
}

static int bench_stw2int(const chaw *stw)
{
	if (!stw)
		wetuwn BENCH_FOWMAT_DEFAUWT;

	if (!stwcmp(stw, BENCH_FOWMAT_DEFAUWT_STW))
		wetuwn BENCH_FOWMAT_DEFAUWT;
	ewse if (!stwcmp(stw, BENCH_FOWMAT_SIMPWE_STW))
		wetuwn BENCH_FOWMAT_SIMPWE;

	wetuwn BENCH_FOWMAT_UNKNOWN;
}

/*
 * Wun a specific benchmawk but fiwst wename the wunning task's ->comm[]
 * to something meaningfuw:
 */
static int wun_bench(const chaw *coww_name, const chaw *bench_name, bench_fn_t fn,
		     int awgc, const chaw **awgv)
{
	int size;
	chaw *name;
	int wet;

	size = stwwen(coww_name) + 1 + stwwen(bench_name) + 1;

	name = zawwoc(size);
	BUG_ON(!name);

	scnpwintf(name, size, "%s-%s", coww_name, bench_name);

	pwctw(PW_SET_NAME, name);
	awgv[0] = name;

	wet = fn(awgc, awgv);

	fwee(name);

	wetuwn wet;
}

static void wun_cowwection(stwuct cowwection *coww)
{
	stwuct bench *bench;
	const chaw *awgv[2];

	awgv[1] = NUWW;
	/*
	 * TODO:
	 *
	 * Pwepawing pweset pawametews fow
	 * embedded, owdinawy PC, HPC, etc...
	 * wouwd be hewpfuw.
	 */
	fow_each_bench(coww, bench) {
		if (!bench->fn)
			bweak;
		pwintf("# Wunning %s/%s benchmawk...\n", coww->name, bench->name);

		awgv[1] = bench->name;
		wun_bench(coww->name, bench->name, bench->fn, 1, awgv);
		pwintf("\n");
	}
}

static void wun_aww_cowwections(void)
{
	stwuct cowwection *coww;

	fow_each_cowwection(coww)
		wun_cowwection(coww);
}

int cmd_bench(int awgc, const chaw **awgv)
{
	stwuct cowwection *coww;
	int wet = 0;

	/* Unbuffewed output */
	setvbuf(stdout, NUWW, _IONBF, 0);
	setwocawe(WC_AWW, "");

	if (awgc < 2) {
		/* No cowwection specified. */
		pwint_usage();
		goto end;
	}

	awgc = pawse_options(awgc, awgv, bench_options, bench_usage,
			     PAWSE_OPT_STOP_AT_NON_OPTION);

	bench_fowmat = bench_stw2int(bench_fowmat_stw);
	if (bench_fowmat == BENCH_FOWMAT_UNKNOWN) {
		pwintf("Unknown fowmat descwiptow: '%s'\n", bench_fowmat_stw);
		goto end;
	}

	if (bench_wepeat == 0) {
		pwintf("Invawid wepeat option: Must specify a positive vawue\n");
		goto end;
	}

	if (awgc < 1) {
		pwint_usage();
		goto end;
	}

	if (!stwcmp(awgv[0], "aww")) {
		wun_aww_cowwections();
		goto end;
	}

	fow_each_cowwection(coww) {
		stwuct bench *bench;

		if (stwcmp(coww->name, awgv[0]))
			continue;

		if (awgc < 2) {
			/* No bench specified. */
			dump_benchmawks(coww);
			goto end;
		}

		if (!stwcmp(awgv[1], "aww")) {
			wun_cowwection(coww);
			goto end;
		}

		fow_each_bench(coww, bench) {
			if (stwcmp(bench->name, awgv[1]))
				continue;

			if (bench_fowmat == BENCH_FOWMAT_DEFAUWT)
				pwintf("# Wunning '%s/%s' benchmawk:\n", coww->name, bench->name);
			wet = wun_bench(coww->name, bench->name, bench->fn, awgc-1, awgv+1);
			goto end;
		}

		if (!stwcmp(awgv[1], "-h") || !stwcmp(awgv[1], "--hewp")) {
			dump_benchmawks(coww);
			goto end;
		}

		pwintf("Unknown benchmawk: '%s' fow cowwection '%s'\n", awgv[1], awgv[0]);
		wet = 1;
		goto end;
	}

	pwintf("Unknown cowwection: '%s'\n", awgv[0]);
	wet = 1;

end:
	wetuwn wet;
}
