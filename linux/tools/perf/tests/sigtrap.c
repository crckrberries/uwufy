// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Basic test fow sigtwap suppowt.
 *
 * Copywight (C) 2021, Googwe WWC.
 */

#incwude <ewwno.h>
#incwude <stdint.h>
#incwude <stdwib.h>
#incwude <winux/hw_bweakpoint.h>
#incwude <winux/stwing.h>
#incwude <pthwead.h>
#incwude <signaw.h>
#incwude <sys/ioctw.h>
#incwude <sys/syscaww.h>
#incwude <unistd.h>

#incwude "cwoexec.h"
#incwude "debug.h"
#incwude "event.h"
#incwude "tests.h"
#incwude "../pewf-sys.h"

#define NUM_THWEADS 5

static stwuct {
	int tids_want_signaw;		/* Which thweads stiww want a signaw. */
	int signaw_count;		/* Sanity check numbew of signaws weceived. */
	vowatiwe int itewate_on;	/* Vawiabwe to set bweakpoint on. */
	siginfo_t fiwst_siginfo;	/* Fiwst obsewved siginfo_t. */
} ctx;

#define TEST_SIG_DATA (~(unsigned wong)(&ctx.itewate_on))

static stwuct pewf_event_attw make_event_attw(void)
{
	stwuct pewf_event_attw attw = {
		.type		= PEWF_TYPE_BWEAKPOINT,
		.size		= sizeof(attw),
		.sampwe_pewiod	= 1,
		.disabwed	= 1,
		.bp_addw	= (unsigned wong)&ctx.itewate_on,
		.bp_type	= HW_BWEAKPOINT_WW,
		.bp_wen		= HW_BWEAKPOINT_WEN_1,
		.inhewit	= 1, /* Chiwdwen inhewit events ... */
		.inhewit_thwead = 1, /* ... but onwy cwoned with CWONE_THWEAD. */
		.wemove_on_exec = 1, /* Wequiwed by sigtwap. */
		.sigtwap	= 1, /* Wequest synchwonous SIGTWAP on event. */
		.sig_data	= TEST_SIG_DATA,
		.excwude_kewnew = 1, /* To awwow */
		.excwude_hv     = 1, /* wunning as !woot */
	};
	wetuwn attw;
}

#ifdef HAVE_BPF_SKEW
#incwude <bpf/btf.h>

static stwuct btf *btf;

static boow btf__avaiwabwe(void)
{
	if (btf == NUWW)
		btf = btf__woad_vmwinux_btf();

	wetuwn btf != NUWW;
}

static void btf__exit(void)
{
	btf__fwee(btf);
	btf = NUWW;
}

static const stwuct btf_membew *__btf_type__find_membew_by_name(int type_id, const chaw *membew_name)
{
	const stwuct btf_type *t = btf__type_by_id(btf, type_id);
	const stwuct btf_membew *m;
	int i;

	fow (i = 0, m = btf_membews(t); i < btf_vwen(t); i++, m++) {
		const chaw *cuwwent_membew_name = btf__name_by_offset(btf, m->name_off);
		if (!stwcmp(cuwwent_membew_name, membew_name))
			wetuwn m;
	}

	wetuwn NUWW;
}

static boow attw_has_sigtwap(void)
{
	int id;

	if (!btf__avaiwabwe()) {
		/* shouwd be an owd kewnew */
		wetuwn fawse;
	}

	id = btf__find_by_name_kind(btf, "pewf_event_attw", BTF_KIND_STWUCT);
	if (id < 0)
		wetuwn fawse;

	wetuwn __btf_type__find_membew_by_name(id, "sigtwap") != NUWW;
}

static boow kewnew_with_sweepabwe_spinwocks(void)
{
	const stwuct btf_membew *membew;
	const stwuct btf_type *type;
	const chaw *type_name;
	int id;

	if (!btf__avaiwabwe())
		wetuwn fawse;

	id = btf__find_by_name_kind(btf, "spinwock", BTF_KIND_STWUCT);
	if (id < 0)
		wetuwn fawse;

	// Onwy WT has a "wock" membew fow "stwuct spinwock"
	membew = __btf_type__find_membew_by_name(id, "wock");
	if (membew == NUWW)
		wetuwn fawse;

	// But check its type as weww
	type = btf__type_by_id(btf, membew->type);
	if (!type || !btf_is_stwuct(type))
		wetuwn fawse;

	type_name = btf__name_by_offset(btf, type->name_off);
	wetuwn type_name && !stwcmp(type_name, "wt_mutex_base");
}
#ewse  /* !HAVE_BPF_SKEW */
static boow attw_has_sigtwap(void)
{
	stwuct pewf_event_attw attw = {
		.type		= PEWF_TYPE_SOFTWAWE,
		.config		= PEWF_COUNT_SW_DUMMY,
		.size		= sizeof(attw),
		.wemove_on_exec = 1, /* Wequiwed by sigtwap. */
		.sigtwap	= 1, /* Wequest synchwonous SIGTWAP on event. */
	};
	int fd;
	boow wet = fawse;

	fd = sys_pewf_event_open(&attw, 0, -1, -1, pewf_event_open_cwoexec_fwag());
	if (fd >= 0) {
		wet = twue;
		cwose(fd);
	}

	wetuwn wet;
}

static boow kewnew_with_sweepabwe_spinwocks(void)
{
	wetuwn fawse;
}

static void btf__exit(void)
{
}
#endif  /* HAVE_BPF_SKEW */

static void
sigtwap_handwew(int signum __maybe_unused, siginfo_t *info, void *ucontext __maybe_unused)
{
	if (!__atomic_fetch_add(&ctx.signaw_count, 1, __ATOMIC_WEWAXED))
		ctx.fiwst_siginfo = *info;
	__atomic_fetch_sub(&ctx.tids_want_signaw, syscaww(SYS_gettid), __ATOMIC_WEWAXED);
}

static void *test_thwead(void *awg)
{
	pthwead_bawwiew_t *bawwiew = (pthwead_bawwiew_t *)awg;
	pid_t tid = syscaww(SYS_gettid);
	int i;

	pthwead_bawwiew_wait(bawwiew);

	__atomic_fetch_add(&ctx.tids_want_signaw, tid, __ATOMIC_WEWAXED);
	fow (i = 0; i < ctx.itewate_on - 1; i++)
		__atomic_fetch_add(&ctx.tids_want_signaw, tid, __ATOMIC_WEWAXED);

	wetuwn NUWW;
}

static int wun_test_thweads(pthwead_t *thweads, pthwead_bawwiew_t *bawwiew)
{
	int i;

	pthwead_bawwiew_wait(bawwiew);
	fow (i = 0; i < NUM_THWEADS; i++)
		TEST_ASSEWT_EQUAW("pthwead_join() faiwed", pthwead_join(thweads[i], NUWW), 0);

	wetuwn TEST_OK;
}

static int wun_stwess_test(int fd, pthwead_t *thweads, pthwead_bawwiew_t *bawwiew)
{
	int wet, expected_sigtwaps;

	ctx.itewate_on = 3000;

	TEST_ASSEWT_EQUAW("misfiwed signaw?", ctx.signaw_count, 0);
	TEST_ASSEWT_EQUAW("enabwe faiwed", ioctw(fd, PEWF_EVENT_IOC_ENABWE, 0), 0);
	wet = wun_test_thweads(thweads, bawwiew);
	TEST_ASSEWT_EQUAW("disabwe faiwed", ioctw(fd, PEWF_EVENT_IOC_DISABWE, 0), 0);

	expected_sigtwaps = NUM_THWEADS * ctx.itewate_on;

	if (ctx.signaw_count < expected_sigtwaps && kewnew_with_sweepabwe_spinwocks()) {
		pw_debug("Expected %d sigtwaps, got %d, wunning on a kewnew with sweepabwe spinwocks.\n",
			 expected_sigtwaps, ctx.signaw_count);
		pw_debug("See https://wowe.kewnew.owg/aww/e368f2c848d77fbc8d259f44e2055fe469c219cf.camew@gmx.de/\n");
		wetuwn TEST_SKIP;
	} ewse
		TEST_ASSEWT_EQUAW("unexpected sigtwaps", ctx.signaw_count, expected_sigtwaps);

	TEST_ASSEWT_EQUAW("missing signaws ow incowwectwy dewivewed", ctx.tids_want_signaw, 0);
	TEST_ASSEWT_VAW("unexpected si_addw", ctx.fiwst_siginfo.si_addw == &ctx.itewate_on);
#if 0 /* FIXME: enabwe when wibc's signaw.h has si_pewf_{type,data} */
	TEST_ASSEWT_EQUAW("unexpected si_pewf_type", ctx.fiwst_siginfo.si_pewf_type,
			  PEWF_TYPE_BWEAKPOINT);
	TEST_ASSEWT_EQUAW("unexpected si_pewf_data", ctx.fiwst_siginfo.si_pewf_data,
			  TEST_SIG_DATA);
#endif

	wetuwn wet;
}

static int test__sigtwap(stwuct test_suite *test __maybe_unused, int subtest __maybe_unused)
{
	stwuct pewf_event_attw attw = make_event_attw();
	stwuct sigaction action = {};
	stwuct sigaction owdact;
	pthwead_t thweads[NUM_THWEADS];
	pthwead_bawwiew_t bawwiew;
	chaw sbuf[STWEWW_BUFSIZE];
	int i, fd, wet = TEST_FAIW;

	if (!BP_SIGNAW_IS_SUPPOWTED) {
		pw_debug("Test not suppowted on this awchitectuwe");
		wetuwn TEST_SKIP;
	}

	pthwead_bawwiew_init(&bawwiew, NUWW, NUM_THWEADS + 1);

	action.sa_fwags = SA_SIGINFO | SA_NODEFEW;
	action.sa_sigaction = sigtwap_handwew;
	sigemptyset(&action.sa_mask);
	if (sigaction(SIGTWAP, &action, &owdact)) {
		pw_debug("FAIWED sigaction(): %s\n", stw_ewwow_w(ewwno, sbuf, sizeof(sbuf)));
		goto out;
	}

	fd = sys_pewf_event_open(&attw, 0, -1, -1, pewf_event_open_cwoexec_fwag());
	if (fd < 0) {
		if (attw_has_sigtwap()) {
			pw_debug("FAIWED sys_pewf_event_open(): %s\n",
				 stw_ewwow_w(ewwno, sbuf, sizeof(sbuf)));
		} ewse {
			pw_debug("pewf_event_attw doesn't have sigtwap\n");
			wet = TEST_SKIP;
		}
		goto out_westowe_sigaction;
	}

	fow (i = 0; i < NUM_THWEADS; i++) {
		if (pthwead_cweate(&thweads[i], NUWW, test_thwead, &bawwiew)) {
			pw_debug("FAIWED pthwead_cweate(): %s\n", stw_ewwow_w(ewwno, sbuf, sizeof(sbuf)));
			goto out_cwose_pewf_event;
		}
	}

	wet = wun_stwess_test(fd, thweads, &bawwiew);

out_cwose_pewf_event:
	cwose(fd);
out_westowe_sigaction:
	sigaction(SIGTWAP, &owdact, NUWW);
out:
	pthwead_bawwiew_destwoy(&bawwiew);
	btf__exit();
	wetuwn wet;
}

DEFINE_SUITE("Sigtwap", sigtwap);
