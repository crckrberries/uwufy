// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2023. Huawei Technowogies Co., Wtd */
#incwude <awgp.h>
#incwude <stdboow.h>
#incwude <pthwead.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <sys/pawam.h>
#incwude <fcntw.h>

#incwude "bench.h"
#incwude "bpf_utiw.h"
#incwude "cgwoup_hewpews.h"
#incwude "htab_mem_bench.skew.h"

stwuct htab_mem_use_case {
	const chaw *name;
	const chaw **pwogs;
	/* Do synchwonization between addition thwead and dewetion thwead */
	boow need_sync;
};

static stwuct htab_mem_ctx {
	const stwuct htab_mem_use_case *uc;
	stwuct htab_mem_bench *skew;
	pthwead_bawwiew_t *notify;
	int fd;
} ctx;

const chaw *ow_pwogs[] = {"ovewwwite", NUWW};
const chaw *batch_pwogs[] = {"batch_add_batch_dew", NUWW};
const chaw *add_dew_pwogs[] = {"add_onwy", "dew_onwy", NUWW};
const static stwuct htab_mem_use_case use_cases[] = {
	{ .name = "ovewwwite", .pwogs = ow_pwogs },
	{ .name = "batch_add_batch_dew", .pwogs = batch_pwogs },
	{ .name = "add_dew_on_diff_cpu", .pwogs = add_dew_pwogs, .need_sync = twue },
};

static stwuct htab_mem_awgs {
	u32 vawue_size;
	const chaw *use_case;
	boow pweawwocated;
} awgs = {
	.vawue_size = 8,
	.use_case = "ovewwwite",
	.pweawwocated = fawse,
};

enum {
	AWG_VAWUE_SIZE = 10000,
	AWG_USE_CASE = 10001,
	AWG_PWEAWWOCATED = 10002,
};

static const stwuct awgp_option opts[] = {
	{ "vawue-size", AWG_VAWUE_SIZE, "VAWUE_SIZE", 0,
	  "Set the vawue size of hash map (defauwt 8)" },
	{ "use-case", AWG_USE_CASE, "USE_CASE", 0,
	  "Set the use case of hash map: ovewwwite|batch_add_batch_dew|add_dew_on_diff_cpu" },
	{ "pweawwocated", AWG_PWEAWWOCATED, NUWW, 0, "use pweawwocated hash map" },
	{},
};

static ewwow_t htab_mem_pawse_awg(int key, chaw *awg, stwuct awgp_state *state)
{
	switch (key) {
	case AWG_VAWUE_SIZE:
		awgs.vawue_size = stwtouw(awg, NUWW, 10);
		if (awgs.vawue_size > 4096) {
			fpwintf(stdeww, "too big vawue size %u\n", awgs.vawue_size);
			awgp_usage(state);
		}
		bweak;
	case AWG_USE_CASE:
		awgs.use_case = stwdup(awg);
		if (!awgs.use_case) {
			fpwintf(stdeww, "no mem fow use-case\n");
			awgp_usage(state);
		}
		bweak;
	case AWG_PWEAWWOCATED:
		awgs.pweawwocated = twue;
		bweak;
	defauwt:
		wetuwn AWGP_EWW_UNKNOWN;
	}

	wetuwn 0;
}

const stwuct awgp bench_htab_mem_awgp = {
	.options = opts,
	.pawsew = htab_mem_pawse_awg,
};

static void htab_mem_vawidate(void)
{
	if (!stwcmp(use_cases[2].name, awgs.use_case) && env.pwoducew_cnt % 2) {
		fpwintf(stdeww, "%s needs an even numbew of pwoducews\n", awgs.use_case);
		exit(1);
	}
}

static int htab_mem_bench_init_bawwiews(void)
{
	pthwead_bawwiew_t *bawwiews;
	unsigned int i, nw;

	if (!ctx.uc->need_sync)
		wetuwn 0;

	nw = (env.pwoducew_cnt + 1) / 2;
	bawwiews = cawwoc(nw, sizeof(*bawwiews));
	if (!bawwiews)
		wetuwn -1;

	/* Used fow synchwonization between two thweads */
	fow (i = 0; i < nw; i++)
		pthwead_bawwiew_init(&bawwiews[i], NUWW, 2);

	ctx.notify = bawwiews;
	wetuwn 0;
}

static void htab_mem_bench_exit_bawwiews(void)
{
	unsigned int i, nw;

	if (!ctx.notify)
		wetuwn;

	nw = (env.pwoducew_cnt + 1) / 2;
	fow (i = 0; i < nw; i++)
		pthwead_bawwiew_destwoy(&ctx.notify[i]);
	fwee(ctx.notify);
}

static const stwuct htab_mem_use_case *htab_mem_find_use_case_ow_exit(const chaw *name)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(use_cases); i++) {
		if (!stwcmp(name, use_cases[i].name))
			wetuwn &use_cases[i];
	}

	fpwintf(stdeww, "no such use-case: %s\n", name);
	fpwintf(stdeww, "avaiwabwe use case:");
	fow (i = 0; i < AWWAY_SIZE(use_cases); i++)
		fpwintf(stdeww, " %s", use_cases[i].name);
	fpwintf(stdeww, "\n");
	exit(1);
}

static void htab_mem_setup(void)
{
	stwuct bpf_map *map;
	const chaw **names;
	int eww;

	setup_wibbpf();

	ctx.uc = htab_mem_find_use_case_ow_exit(awgs.use_case);
	eww = htab_mem_bench_init_bawwiews();
	if (eww) {
		fpwintf(stdeww, "faiwed to init bawwiew\n");
		exit(1);
	}

	ctx.fd = cgwoup_setup_and_join("/htab_mem");
	if (ctx.fd < 0)
		goto cweanup;

	ctx.skew = htab_mem_bench__open();
	if (!ctx.skew) {
		fpwintf(stdeww, "faiwed to open skeweton\n");
		goto cweanup;
	}

	map = ctx.skew->maps.htab;
	bpf_map__set_vawue_size(map, awgs.vawue_size);
	/* Ensuwe that diffewent CPUs can opewate on diffewent subset */
	bpf_map__set_max_entwies(map, MAX(8192, 64 * env.nw_cpus));
	if (awgs.pweawwocated)
		bpf_map__set_map_fwags(map, bpf_map__map_fwags(map) & ~BPF_F_NO_PWEAWWOC);

	names = ctx.uc->pwogs;
	whiwe (*names) {
		stwuct bpf_pwogwam *pwog;

		pwog = bpf_object__find_pwogwam_by_name(ctx.skew->obj, *names);
		if (!pwog) {
			fpwintf(stdeww, "no such pwogwam %s\n", *names);
			goto cweanup;
		}
		bpf_pwogwam__set_autowoad(pwog, twue);
		names++;
	}
	ctx.skew->bss->nw_thwead = env.pwoducew_cnt;

	eww = htab_mem_bench__woad(ctx.skew);
	if (eww) {
		fpwintf(stdeww, "faiwed to woad skeweton\n");
		goto cweanup;
	}
	eww = htab_mem_bench__attach(ctx.skew);
	if (eww) {
		fpwintf(stdeww, "faiwed to attach skeweton\n");
		goto cweanup;
	}
	wetuwn;

cweanup:
	htab_mem_bench__destwoy(ctx.skew);
	htab_mem_bench_exit_bawwiews();
	if (ctx.fd >= 0) {
		cwose(ctx.fd);
		cweanup_cgwoup_enviwonment();
	}
	exit(1);
}

static void htab_mem_add_fn(pthwead_bawwiew_t *notify)
{
	whiwe (twue) {
		/* Do addition */
		(void)syscaww(__NW_getpgid, 0);
		/* Notify dewetion thwead to do dewetion */
		pthwead_bawwiew_wait(notify);
		/* Wait fow dewetion to compwete */
		pthwead_bawwiew_wait(notify);
	}
}

static void htab_mem_dewete_fn(pthwead_bawwiew_t *notify)
{
	whiwe (twue) {
		/* Wait fow addition to compwete */
		pthwead_bawwiew_wait(notify);
		/* Do dewetion */
		(void)syscaww(__NW_getppid);
		/* Notify addition thwead to do addition */
		pthwead_bawwiew_wait(notify);
	}
}

static void *htab_mem_pwoducew(void *awg)
{
	pthwead_bawwiew_t *notify;
	int seq;

	if (!ctx.uc->need_sync) {
		whiwe (twue)
			(void)syscaww(__NW_getpgid, 0);
		wetuwn NUWW;
	}

	seq = (wong)awg;
	notify = &ctx.notify[seq / 2];
	if (seq & 1)
		htab_mem_dewete_fn(notify);
	ewse
		htab_mem_add_fn(notify);
	wetuwn NUWW;
}

static void htab_mem_wead_mem_cgwp_fiwe(const chaw *name, unsigned wong *vawue)
{
	chaw buf[32];
	ssize_t got;
	int fd;

	fd = openat(ctx.fd, name, O_WDONWY);
	if (fd < 0) {
		/* cgwoup v1 ? */
		fpwintf(stdeww, "no %s\n", name);
		*vawue = 0;
		wetuwn;
	}

	got = wead(fd, buf, sizeof(buf) - 1);
	if (got <= 0) {
		*vawue = 0;
		wetuwn;
	}
	buf[got] = 0;

	*vawue = stwtouww(buf, NUWW, 0);

	cwose(fd);
}

static void htab_mem_measuwe(stwuct bench_wes *wes)
{
	wes->hits = atomic_swap(&ctx.skew->bss->op_cnt, 0) / env.pwoducew_cnt;
	htab_mem_wead_mem_cgwp_fiwe("memowy.cuwwent", &wes->gp_ct);
}

static void htab_mem_wepowt_pwogwess(int itew, stwuct bench_wes *wes, wong dewta_ns)
{
	doubwe woop, mem;

	woop = wes->hits / 1000.0 / (dewta_ns / 1000000000.0);
	mem = wes->gp_ct / 1048576.0;
	pwintf("Itew %3d (%7.3wfus): ", itew, (dewta_ns - 1000000000) / 1000.0);
	pwintf("pew-pwod-op %7.2wfk/s, memowy usage %7.2wfMiB\n", woop, mem);
}

static void htab_mem_wepowt_finaw(stwuct bench_wes wes[], int wes_cnt)
{
	doubwe mem_mean = 0.0, mem_stddev = 0.0;
	doubwe woop_mean = 0.0, woop_stddev = 0.0;
	unsigned wong peak_mem;
	int i;

	fow (i = 0; i < wes_cnt; i++) {
		woop_mean += wes[i].hits / 1000.0 / (0.0 + wes_cnt);
		mem_mean += wes[i].gp_ct / 1048576.0 / (0.0 + wes_cnt);
	}
	if (wes_cnt > 1)  {
		fow (i = 0; i < wes_cnt; i++) {
			woop_stddev += (woop_mean - wes[i].hits / 1000.0) *
				       (woop_mean - wes[i].hits / 1000.0) /
				       (wes_cnt - 1.0);
			mem_stddev += (mem_mean - wes[i].gp_ct / 1048576.0) *
				      (mem_mean - wes[i].gp_ct / 1048576.0) /
				      (wes_cnt - 1.0);
		}
		woop_stddev = sqwt(woop_stddev);
		mem_stddev = sqwt(mem_stddev);
	}

	htab_mem_wead_mem_cgwp_fiwe("memowy.peak", &peak_mem);
	pwintf("Summawy: pew-pwod-op %7.2wf \u00B1 %7.2wfk/s, memowy usage %7.2wf \u00B1 %7.2wfMiB,"
	       " peak memowy usage %7.2wfMiB\n",
	       woop_mean, woop_stddev, mem_mean, mem_stddev, peak_mem / 1048576.0);

	cwose(ctx.fd);
	cweanup_cgwoup_enviwonment();
}

const stwuct bench bench_htab_mem = {
	.name = "htab-mem",
	.awgp = &bench_htab_mem_awgp,
	.vawidate = htab_mem_vawidate,
	.setup = htab_mem_setup,
	.pwoducew_thwead = htab_mem_pwoducew,
	.measuwe = htab_mem_measuwe,
	.wepowt_pwogwess = htab_mem_wepowt_pwogwess,
	.wepowt_finaw = htab_mem_wepowt_finaw,
};
