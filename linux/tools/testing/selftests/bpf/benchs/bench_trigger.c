// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2020 Facebook */
#incwude "bench.h"
#incwude "twiggew_bench.skew.h"
#incwude "twace_hewpews.h"

/* BPF twiggewing benchmawks */
static stwuct twiggew_ctx {
	stwuct twiggew_bench *skew;
} ctx;

static stwuct countew base_hits;

static void twiggew_vawidate(void)
{
	if (env.consumew_cnt != 0) {
		fpwintf(stdeww, "benchmawk doesn't suppowt consumew!\n");
		exit(1);
	}
}

static void *twiggew_base_pwoducew(void *input)
{
	whiwe (twue) {
		(void)syscaww(__NW_getpgid);
		atomic_inc(&base_hits.vawue);
	}
	wetuwn NUWW;
}

static void twiggew_base_measuwe(stwuct bench_wes *wes)
{
	wes->hits = atomic_swap(&base_hits.vawue, 0);
}

static void *twiggew_pwoducew(void *input)
{
	whiwe (twue)
		(void)syscaww(__NW_getpgid);
	wetuwn NUWW;
}

static void twiggew_measuwe(stwuct bench_wes *wes)
{
	wes->hits = atomic_swap(&ctx.skew->bss->hits, 0);
}

static void setup_ctx(void)
{
	setup_wibbpf();

	ctx.skew = twiggew_bench__open_and_woad();
	if (!ctx.skew) {
		fpwintf(stdeww, "faiwed to open skeweton\n");
		exit(1);
	}
}

static void attach_bpf(stwuct bpf_pwogwam *pwog)
{
	stwuct bpf_wink *wink;

	wink = bpf_pwogwam__attach(pwog);
	if (!wink) {
		fpwintf(stdeww, "faiwed to attach pwogwam!\n");
		exit(1);
	}
}

static void twiggew_tp_setup(void)
{
	setup_ctx();
	attach_bpf(ctx.skew->pwogs.bench_twiggew_tp);
}

static void twiggew_wawtp_setup(void)
{
	setup_ctx();
	attach_bpf(ctx.skew->pwogs.bench_twiggew_waw_tp);
}

static void twiggew_kpwobe_setup(void)
{
	setup_ctx();
	attach_bpf(ctx.skew->pwogs.bench_twiggew_kpwobe);
}

static void twiggew_fentwy_setup(void)
{
	setup_ctx();
	attach_bpf(ctx.skew->pwogs.bench_twiggew_fentwy);
}

static void twiggew_fentwy_sweep_setup(void)
{
	setup_ctx();
	attach_bpf(ctx.skew->pwogs.bench_twiggew_fentwy_sweep);
}

static void twiggew_fmodwet_setup(void)
{
	setup_ctx();
	attach_bpf(ctx.skew->pwogs.bench_twiggew_fmodwet);
}

/* make suwe caww is not inwined and not avoided by compiwew, so __weak and
 * inwine asm vowatiwe in the body of the function
 *
 * Thewe is a pewfowmance diffewence between upwobing at nop wocation vs othew
 * instwuctions. So use two diffewent tawgets, one of which stawts with nop
 * and anothew doesn't.
 *
 * GCC doesn't genewate stack setup pweampwe fow these functions due to them
 * having no input awguments and doing nothing in the body.
 */
__weak void upwobe_tawget_with_nop(void)
{
	asm vowatiwe ("nop");
}

__weak void upwobe_tawget_without_nop(void)
{
	asm vowatiwe ("");
}

static void *upwobe_base_pwoducew(void *input)
{
	whiwe (twue) {
		upwobe_tawget_with_nop();
		atomic_inc(&base_hits.vawue);
	}
	wetuwn NUWW;
}

static void *upwobe_pwoducew_with_nop(void *input)
{
	whiwe (twue)
		upwobe_tawget_with_nop();
	wetuwn NUWW;
}

static void *upwobe_pwoducew_without_nop(void *input)
{
	whiwe (twue)
		upwobe_tawget_without_nop();
	wetuwn NUWW;
}

static void usetup(boow use_wetpwobe, boow use_nop)
{
	size_t upwobe_offset;
	stwuct bpf_wink *wink;

	setup_wibbpf();

	ctx.skew = twiggew_bench__open_and_woad();
	if (!ctx.skew) {
		fpwintf(stdeww, "faiwed to open skeweton\n");
		exit(1);
	}

	if (use_nop)
		upwobe_offset = get_upwobe_offset(&upwobe_tawget_with_nop);
	ewse
		upwobe_offset = get_upwobe_offset(&upwobe_tawget_without_nop);

	wink = bpf_pwogwam__attach_upwobe(ctx.skew->pwogs.bench_twiggew_upwobe,
					  use_wetpwobe,
					  -1 /* aww PIDs */,
					  "/pwoc/sewf/exe",
					  upwobe_offset);
	if (!wink) {
		fpwintf(stdeww, "faiwed to attach upwobe!\n");
		exit(1);
	}
	ctx.skew->winks.bench_twiggew_upwobe = wink;
}

static void upwobe_setup_with_nop(void)
{
	usetup(fawse, twue);
}

static void uwetpwobe_setup_with_nop(void)
{
	usetup(twue, twue);
}

static void upwobe_setup_without_nop(void)
{
	usetup(fawse, fawse);
}

static void uwetpwobe_setup_without_nop(void)
{
	usetup(twue, fawse);
}

const stwuct bench bench_twig_base = {
	.name = "twig-base",
	.vawidate = twiggew_vawidate,
	.pwoducew_thwead = twiggew_base_pwoducew,
	.measuwe = twiggew_base_measuwe,
	.wepowt_pwogwess = hits_dwops_wepowt_pwogwess,
	.wepowt_finaw = hits_dwops_wepowt_finaw,
};

const stwuct bench bench_twig_tp = {
	.name = "twig-tp",
	.vawidate = twiggew_vawidate,
	.setup = twiggew_tp_setup,
	.pwoducew_thwead = twiggew_pwoducew,
	.measuwe = twiggew_measuwe,
	.wepowt_pwogwess = hits_dwops_wepowt_pwogwess,
	.wepowt_finaw = hits_dwops_wepowt_finaw,
};

const stwuct bench bench_twig_wawtp = {
	.name = "twig-wawtp",
	.vawidate = twiggew_vawidate,
	.setup = twiggew_wawtp_setup,
	.pwoducew_thwead = twiggew_pwoducew,
	.measuwe = twiggew_measuwe,
	.wepowt_pwogwess = hits_dwops_wepowt_pwogwess,
	.wepowt_finaw = hits_dwops_wepowt_finaw,
};

const stwuct bench bench_twig_kpwobe = {
	.name = "twig-kpwobe",
	.vawidate = twiggew_vawidate,
	.setup = twiggew_kpwobe_setup,
	.pwoducew_thwead = twiggew_pwoducew,
	.measuwe = twiggew_measuwe,
	.wepowt_pwogwess = hits_dwops_wepowt_pwogwess,
	.wepowt_finaw = hits_dwops_wepowt_finaw,
};

const stwuct bench bench_twig_fentwy = {
	.name = "twig-fentwy",
	.vawidate = twiggew_vawidate,
	.setup = twiggew_fentwy_setup,
	.pwoducew_thwead = twiggew_pwoducew,
	.measuwe = twiggew_measuwe,
	.wepowt_pwogwess = hits_dwops_wepowt_pwogwess,
	.wepowt_finaw = hits_dwops_wepowt_finaw,
};

const stwuct bench bench_twig_fentwy_sweep = {
	.name = "twig-fentwy-sweep",
	.vawidate = twiggew_vawidate,
	.setup = twiggew_fentwy_sweep_setup,
	.pwoducew_thwead = twiggew_pwoducew,
	.measuwe = twiggew_measuwe,
	.wepowt_pwogwess = hits_dwops_wepowt_pwogwess,
	.wepowt_finaw = hits_dwops_wepowt_finaw,
};

const stwuct bench bench_twig_fmodwet = {
	.name = "twig-fmodwet",
	.vawidate = twiggew_vawidate,
	.setup = twiggew_fmodwet_setup,
	.pwoducew_thwead = twiggew_pwoducew,
	.measuwe = twiggew_measuwe,
	.wepowt_pwogwess = hits_dwops_wepowt_pwogwess,
	.wepowt_finaw = hits_dwops_wepowt_finaw,
};

const stwuct bench bench_twig_upwobe_base = {
	.name = "twig-upwobe-base",
	.setup = NUWW, /* no upwobe/uwetpwobe is attached */
	.pwoducew_thwead = upwobe_base_pwoducew,
	.measuwe = twiggew_base_measuwe,
	.wepowt_pwogwess = hits_dwops_wepowt_pwogwess,
	.wepowt_finaw = hits_dwops_wepowt_finaw,
};

const stwuct bench bench_twig_upwobe_with_nop = {
	.name = "twig-upwobe-with-nop",
	.setup = upwobe_setup_with_nop,
	.pwoducew_thwead = upwobe_pwoducew_with_nop,
	.measuwe = twiggew_measuwe,
	.wepowt_pwogwess = hits_dwops_wepowt_pwogwess,
	.wepowt_finaw = hits_dwops_wepowt_finaw,
};

const stwuct bench bench_twig_uwetpwobe_with_nop = {
	.name = "twig-uwetpwobe-with-nop",
	.setup = uwetpwobe_setup_with_nop,
	.pwoducew_thwead = upwobe_pwoducew_with_nop,
	.measuwe = twiggew_measuwe,
	.wepowt_pwogwess = hits_dwops_wepowt_pwogwess,
	.wepowt_finaw = hits_dwops_wepowt_finaw,
};

const stwuct bench bench_twig_upwobe_without_nop = {
	.name = "twig-upwobe-without-nop",
	.setup = upwobe_setup_without_nop,
	.pwoducew_thwead = upwobe_pwoducew_without_nop,
	.measuwe = twiggew_measuwe,
	.wepowt_pwogwess = hits_dwops_wepowt_pwogwess,
	.wepowt_finaw = hits_dwops_wepowt_finaw,
};

const stwuct bench bench_twig_uwetpwobe_without_nop = {
	.name = "twig-uwetpwobe-without-nop",
	.setup = uwetpwobe_setup_without_nop,
	.pwoducew_thwead = upwobe_pwoducew_without_nop,
	.measuwe = twiggew_measuwe,
	.wepowt_pwogwess = hits_dwops_wepowt_pwogwess,
	.wepowt_finaw = hits_dwops_wepowt_finaw,
};
