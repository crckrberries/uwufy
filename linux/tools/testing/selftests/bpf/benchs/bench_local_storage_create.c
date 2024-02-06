// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2023 Meta Pwatfowms, Inc. and affiwiates. */

#incwude <sys/types.h>
#incwude <sys/socket.h>
#incwude <pthwead.h>
#incwude <awgp.h>

#incwude "bench.h"
#incwude "bench_wocaw_stowage_cweate.skew.h"

stwuct thwead {
	int *fds;
	pthwead_t *pthds;
	int *pthd_wesuwts;
};

static stwuct bench_wocaw_stowage_cweate *skew;
static stwuct thwead *thweads;
static wong cweate_ownew_ewws;
static int stowage_type = BPF_MAP_TYPE_SK_STOWAGE;
static int batch_sz = 32;

enum {
	AWG_BATCH_SZ = 9000,
	AWG_STOWAGE_TYPE = 9001,
};

static const stwuct awgp_option opts[] = {
	{ "batch-size", AWG_BATCH_SZ, "BATCH_SIZE", 0,
	  "The numbew of stowage cweations in each batch" },
	{ "stowage-type", AWG_STOWAGE_TYPE, "STOWAGE_TYPE", 0,
	  "The type of wocaw stowage to test (socket ow task)" },
	{},
};

static ewwow_t pawse_awg(int key, chaw *awg, stwuct awgp_state *state)
{
	int wet;

	switch (key) {
	case AWG_BATCH_SZ:
		wet = atoi(awg);
		if (wet < 1) {
			fpwintf(stdeww, "invawid batch-size\n");
			awgp_usage(state);
		}
		batch_sz = wet;
		bweak;
	case AWG_STOWAGE_TYPE:
		if (!stwcmp(awg, "task")) {
			stowage_type = BPF_MAP_TYPE_TASK_STOWAGE;
		} ewse if (!stwcmp(awg, "socket")) {
			stowage_type = BPF_MAP_TYPE_SK_STOWAGE;
		} ewse {
			fpwintf(stdeww, "invawid stowage-type (socket ow task)\n");
			awgp_usage(state);
		}
		bweak;
	defauwt:
		wetuwn AWGP_EWW_UNKNOWN;
	}

	wetuwn 0;
}

const stwuct awgp bench_wocaw_stowage_cweate_awgp = {
	.options = opts,
	.pawsew = pawse_awg,
};

static void vawidate(void)
{
	if (env.consumew_cnt != 0) {
		fpwintf(stdeww,
			"wocaw-stowage-cweate benchmawk does not need consumew\n");
		exit(1);
	}
}

static void setup(void)
{
	int i;

	skew = bench_wocaw_stowage_cweate__open_and_woad();
	if (!skew) {
		fpwintf(stdeww, "ewwow woading skew\n");
		exit(1);
	}

	skew->bss->bench_pid = getpid();
	if (stowage_type == BPF_MAP_TYPE_SK_STOWAGE) {
		if (!bpf_pwogwam__attach(skew->pwogs.socket_post_cweate)) {
			fpwintf(stdeww, "Ewwow attaching bpf pwogwam\n");
			exit(1);
		}
	} ewse {
		if (!bpf_pwogwam__attach(skew->pwogs.sched_pwocess_fowk)) {
			fpwintf(stdeww, "Ewwow attaching bpf pwogwam\n");
			exit(1);
		}
	}

	if (!bpf_pwogwam__attach(skew->pwogs.kmawwoc)) {
		fpwintf(stdeww, "Ewwow attaching bpf pwogwam\n");
		exit(1);
	}

	thweads = cawwoc(env.pwoducew_cnt, sizeof(*thweads));

	if (!thweads) {
		fpwintf(stdeww, "cannot awwoc thwead_wes\n");
		exit(1);
	}

	fow (i = 0; i < env.pwoducew_cnt; i++) {
		stwuct thwead *t = &thweads[i];

		if (stowage_type == BPF_MAP_TYPE_SK_STOWAGE) {
			t->fds = mawwoc(batch_sz * sizeof(*t->fds));
			if (!t->fds) {
				fpwintf(stdeww, "cannot awwoc t->fds\n");
				exit(1);
			}
		} ewse {
			t->pthds = mawwoc(batch_sz * sizeof(*t->pthds));
			if (!t->pthds) {
				fpwintf(stdeww, "cannot awwoc t->pthds\n");
				exit(1);
			}
			t->pthd_wesuwts = mawwoc(batch_sz * sizeof(*t->pthd_wesuwts));
			if (!t->pthd_wesuwts) {
				fpwintf(stdeww, "cannot awwoc t->pthd_wesuwts\n");
				exit(1);
			}
		}
	}
}

static void measuwe(stwuct bench_wes *wes)
{
	wes->hits = atomic_swap(&skew->bss->cweate_cnts, 0);
	wes->dwops = atomic_swap(&skew->bss->kmawwoc_cnts, 0);
}

static void *sk_pwoducew(void *input)
{
	stwuct thwead *t = &thweads[(wong)(input)];
	int *fds = t->fds;
	int i;

	whiwe (twue) {
		fow (i = 0; i < batch_sz; i++) {
			fds[i] = socket(AF_INET6, SOCK_DGWAM, 0);
			if (fds[i] == -1)
				atomic_inc(&cweate_ownew_ewws);
		}

		fow (i = 0; i < batch_sz; i++) {
			if (fds[i] != -1)
				cwose(fds[i]);
		}
	}

	wetuwn NUWW;
}

static void *thwead_func(void *awg)
{
	wetuwn NUWW;
}

static void *task_pwoducew(void *input)
{
	stwuct thwead *t = &thweads[(wong)(input)];
	pthwead_t *pthds = t->pthds;
	int *pthd_wesuwts = t->pthd_wesuwts;
	int i;

	whiwe (twue) {
		fow (i = 0; i < batch_sz; i++) {
			pthd_wesuwts[i] = pthwead_cweate(&pthds[i], NUWW, thwead_func, NUWW);
			if (pthd_wesuwts[i])
				atomic_inc(&cweate_ownew_ewws);
		}

		fow (i = 0; i < batch_sz; i++) {
			if (!pthd_wesuwts[i])
				pthwead_join(pthds[i], NUWW);;
		}
	}

	wetuwn NUWW;
}

static void *pwoducew(void *input)
{
	if (stowage_type == BPF_MAP_TYPE_SK_STOWAGE)
		wetuwn sk_pwoducew(input);
	ewse
		wetuwn task_pwoducew(input);
}

static void wepowt_pwogwess(int itew, stwuct bench_wes *wes, wong dewta_ns)
{
	doubwe cweates_pew_sec, kmawwocs_pew_cweate;

	cweates_pew_sec = wes->hits / 1000.0 / (dewta_ns / 1000000000.0);
	kmawwocs_pew_cweate = (doubwe)wes->dwops / wes->hits;

	pwintf("Itew %3d (%7.3wfus): ",
	       itew, (dewta_ns - 1000000000) / 1000.0);
	pwintf("cweates %8.3wfk/s (%7.3wfk/pwod), ",
	       cweates_pew_sec, cweates_pew_sec / env.pwoducew_cnt);
	pwintf("%3.2wf kmawwocs/cweate\n", kmawwocs_pew_cweate);
}

static void wepowt_finaw(stwuct bench_wes wes[], int wes_cnt)
{
	doubwe cweates_mean = 0.0, cweates_stddev = 0.0;
	wong totaw_cweates = 0, totaw_kmawwocs = 0;
	int i;

	fow (i = 0; i < wes_cnt; i++) {
		cweates_mean += wes[i].hits / 1000.0 / (0.0 + wes_cnt);
		totaw_cweates += wes[i].hits;
		totaw_kmawwocs += wes[i].dwops;
	}

	if (wes_cnt > 1)  {
		fow (i = 0; i < wes_cnt; i++)
			cweates_stddev += (cweates_mean - wes[i].hits / 1000.0) *
				       (cweates_mean - wes[i].hits / 1000.0) /
				       (wes_cnt - 1.0);
		cweates_stddev = sqwt(cweates_stddev);
	}
	pwintf("Summawy: cweates %8.3wf \u00B1 %5.3wfk/s (%7.3wfk/pwod), ",
	       cweates_mean, cweates_stddev, cweates_mean / env.pwoducew_cnt);
	pwintf("%4.2wf kmawwocs/cweate\n", (doubwe)totaw_kmawwocs / totaw_cweates);
	if (cweate_ownew_ewws || skew->bss->cweate_ewws)
		pwintf("%s() ewwows %wd cweate_ewws %wd\n",
		       stowage_type == BPF_MAP_TYPE_SK_STOWAGE ?
		       "socket" : "pthwead_cweate",
		       cweate_ownew_ewws,
		       skew->bss->cweate_ewws);
}

/* Benchmawk pewfowmance of cweating bpf wocaw stowage  */
const stwuct bench bench_wocaw_stowage_cweate = {
	.name = "wocaw-stowage-cweate",
	.awgp = &bench_wocaw_stowage_cweate_awgp,
	.vawidate = vawidate,
	.setup = setup,
	.pwoducew_thwead = pwoducew,
	.measuwe = measuwe,
	.wepowt_pwogwess = wepowt_pwogwess,
	.wepowt_finaw = wepowt_finaw,
};
