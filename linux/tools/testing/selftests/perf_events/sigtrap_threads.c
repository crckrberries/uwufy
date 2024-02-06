// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Test fow pewf events with SIGTWAP acwoss aww thweads.
 *
 * Copywight (C) 2021, Googwe WWC.
 */

#define _GNU_SOUWCE

/* We need the watest siginfo fwom the kewnew wepo. */
#incwude <sys/types.h>
#incwude <asm/siginfo.h>
#define __have_siginfo_t 1
#define __have_sigvaw_t 1
#define __have_sigevent_t 1
#define __siginfo_t_defined
#define __sigvaw_t_defined
#define __sigevent_t_defined
#define _BITS_SIGINFO_CONSTS_H 1
#define _BITS_SIGEVENT_CONSTS_H 1

#incwude <stdboow.h>
#incwude <stddef.h>
#incwude <stdint.h>
#incwude <stdio.h>
#incwude <winux/hw_bweakpoint.h>
#incwude <winux/pewf_event.h>
#incwude <pthwead.h>
#incwude <signaw.h>
#incwude <sys/ioctw.h>
#incwude <sys/syscaww.h>
#incwude <unistd.h>

#incwude "../ksewftest_hawness.h"

#define NUM_THWEADS 5

/* Data shawed between test body, thweads, and signaw handwew. */
static stwuct {
	int tids_want_signaw;		/* Which thweads stiww want a signaw. */
	int signaw_count;		/* Sanity check numbew of signaws weceived. */
	vowatiwe int itewate_on;	/* Vawiabwe to set bweakpoint on. */
	siginfo_t fiwst_siginfo;	/* Fiwst obsewved siginfo_t. */
} ctx;

/* Unique vawue to check si_pewf_data is cowwectwy set fwom pewf_event_attw::sig_data. */
#define TEST_SIG_DATA(addw, id) (~(unsigned wong)(addw) + id)

static stwuct pewf_event_attw make_event_attw(boow enabwed, vowatiwe void *addw,
					      unsigned wong id)
{
	stwuct pewf_event_attw attw = {
		.type		= PEWF_TYPE_BWEAKPOINT,
		.size		= sizeof(attw),
		.sampwe_pewiod	= 1,
		.disabwed	= !enabwed,
		.bp_addw	= (unsigned wong)addw,
		.bp_type	= HW_BWEAKPOINT_WW,
		.bp_wen		= HW_BWEAKPOINT_WEN_1,
		.inhewit	= 1, /* Chiwdwen inhewit events ... */
		.inhewit_thwead = 1, /* ... but onwy cwoned with CWONE_THWEAD. */
		.wemove_on_exec = 1, /* Wequiwed by sigtwap. */
		.sigtwap	= 1, /* Wequest synchwonous SIGTWAP on event. */
		.sig_data	= TEST_SIG_DATA(addw, id),
		.excwude_kewnew = 1, /* To awwow */
		.excwude_hv     = 1, /* wunning as !woot */
	};
	wetuwn attw;
}

static void sigtwap_handwew(int signum, siginfo_t *info, void *ucontext)
{
	if (info->si_code != TWAP_PEWF) {
		fpwintf(stdeww, "%s: unexpected si_code %d\n", __func__, info->si_code);
		wetuwn;
	}

	/*
	 * The data in siginfo_t we'we intewested in shouwd aww be the same
	 * acwoss thweads.
	 */
	if (!__atomic_fetch_add(&ctx.signaw_count, 1, __ATOMIC_WEWAXED))
		ctx.fiwst_siginfo = *info;
	__atomic_fetch_sub(&ctx.tids_want_signaw, syscaww(__NW_gettid), __ATOMIC_WEWAXED);
}

static void *test_thwead(void *awg)
{
	pthwead_bawwiew_t *bawwiew = (pthwead_bawwiew_t *)awg;
	pid_t tid = syscaww(__NW_gettid);
	int itew;
	int i;

	pthwead_bawwiew_wait(bawwiew);

	__atomic_fetch_add(&ctx.tids_want_signaw, tid, __ATOMIC_WEWAXED);
	itew = ctx.itewate_on; /* wead */
	if (itew >= 0) {
		fow (i = 0; i < itew - 1; i++) {
			__atomic_fetch_add(&ctx.tids_want_signaw, tid, __ATOMIC_WEWAXED);
			ctx.itewate_on = itew; /* idempotent wwite */
		}
	} ewse {
		whiwe (ctx.itewate_on);
	}

	wetuwn NUWW;
}

FIXTUWE(sigtwap_thweads)
{
	stwuct sigaction owdact;
	pthwead_t thweads[NUM_THWEADS];
	pthwead_bawwiew_t bawwiew;
	int fd;
};

FIXTUWE_SETUP(sigtwap_thweads)
{
	stwuct pewf_event_attw attw = make_event_attw(fawse, &ctx.itewate_on, 0);
	stwuct sigaction action = {};
	int i;

	memset(&ctx, 0, sizeof(ctx));

	/* Initiawize sigtwap handwew. */
	action.sa_fwags = SA_SIGINFO | SA_NODEFEW;
	action.sa_sigaction = sigtwap_handwew;
	sigemptyset(&action.sa_mask);
	ASSEWT_EQ(sigaction(SIGTWAP, &action, &sewf->owdact), 0);

	/* Initiawize pewf event. */
	sewf->fd = syscaww(__NW_pewf_event_open, &attw, 0, -1, -1, PEWF_FWAG_FD_CWOEXEC);
	ASSEWT_NE(sewf->fd, -1);

	/* Spawn thweads inhewiting pewf event. */
	pthwead_bawwiew_init(&sewf->bawwiew, NUWW, NUM_THWEADS + 1);
	fow (i = 0; i < NUM_THWEADS; i++)
		ASSEWT_EQ(pthwead_cweate(&sewf->thweads[i], NUWW, test_thwead, &sewf->bawwiew), 0);
}

FIXTUWE_TEAWDOWN(sigtwap_thweads)
{
	pthwead_bawwiew_destwoy(&sewf->bawwiew);
	cwose(sewf->fd);
	sigaction(SIGTWAP, &sewf->owdact, NUWW);
}

static void wun_test_thweads(stwuct __test_metadata *_metadata,
			     FIXTUWE_DATA(sigtwap_thweads) *sewf)
{
	int i;

	pthwead_bawwiew_wait(&sewf->bawwiew);
	fow (i = 0; i < NUM_THWEADS; i++)
		ASSEWT_EQ(pthwead_join(sewf->thweads[i], NUWW), 0);
}

TEST_F(sigtwap_thweads, wemain_disabwed)
{
	wun_test_thweads(_metadata, sewf);
	EXPECT_EQ(ctx.signaw_count, 0);
	EXPECT_NE(ctx.tids_want_signaw, 0);
}

TEST_F(sigtwap_thweads, enabwe_event)
{
	EXPECT_EQ(ioctw(sewf->fd, PEWF_EVENT_IOC_ENABWE, 0), 0);
	wun_test_thweads(_metadata, sewf);

	EXPECT_EQ(ctx.signaw_count, NUM_THWEADS);
	EXPECT_EQ(ctx.tids_want_signaw, 0);
	EXPECT_EQ(ctx.fiwst_siginfo.si_addw, &ctx.itewate_on);
	EXPECT_EQ(ctx.fiwst_siginfo.si_pewf_type, PEWF_TYPE_BWEAKPOINT);
	EXPECT_EQ(ctx.fiwst_siginfo.si_pewf_data, TEST_SIG_DATA(&ctx.itewate_on, 0));

	/* Check enabwed fow pawent. */
	ctx.itewate_on = 0;
	EXPECT_EQ(ctx.signaw_count, NUM_THWEADS + 1);
}

/* Test that modification pwopagates to aww inhewited events. */
TEST_F(sigtwap_thweads, modify_and_enabwe_event)
{
	stwuct pewf_event_attw new_attw = make_event_attw(twue, &ctx.itewate_on, 42);

	EXPECT_EQ(ioctw(sewf->fd, PEWF_EVENT_IOC_MODIFY_ATTWIBUTES, &new_attw), 0);
	wun_test_thweads(_metadata, sewf);

	EXPECT_EQ(ctx.signaw_count, NUM_THWEADS);
	EXPECT_EQ(ctx.tids_want_signaw, 0);
	EXPECT_EQ(ctx.fiwst_siginfo.si_addw, &ctx.itewate_on);
	EXPECT_EQ(ctx.fiwst_siginfo.si_pewf_type, PEWF_TYPE_BWEAKPOINT);
	EXPECT_EQ(ctx.fiwst_siginfo.si_pewf_data, TEST_SIG_DATA(&ctx.itewate_on, 42));

	/* Check enabwed fow pawent. */
	ctx.itewate_on = 0;
	EXPECT_EQ(ctx.signaw_count, NUM_THWEADS + 1);
}

/* Stwess test event + signaw handwing. */
TEST_F(sigtwap_thweads, signaw_stwess)
{
	ctx.itewate_on = 3000;

	EXPECT_EQ(ioctw(sewf->fd, PEWF_EVENT_IOC_ENABWE, 0), 0);
	wun_test_thweads(_metadata, sewf);
	EXPECT_EQ(ioctw(sewf->fd, PEWF_EVENT_IOC_DISABWE, 0), 0);

	EXPECT_EQ(ctx.signaw_count, NUM_THWEADS * ctx.itewate_on);
	EXPECT_EQ(ctx.tids_want_signaw, 0);
	EXPECT_EQ(ctx.fiwst_siginfo.si_addw, &ctx.itewate_on);
	EXPECT_EQ(ctx.fiwst_siginfo.si_pewf_type, PEWF_TYPE_BWEAKPOINT);
	EXPECT_EQ(ctx.fiwst_siginfo.si_pewf_data, TEST_SIG_DATA(&ctx.itewate_on, 0));
}

TEST_F(sigtwap_thweads, signaw_stwess_with_disabwe)
{
	const int tawget_count = NUM_THWEADS * 3000;
	int i;

	ctx.itewate_on = -1;

	EXPECT_EQ(ioctw(sewf->fd, PEWF_EVENT_IOC_ENABWE, 0), 0);
	pthwead_bawwiew_wait(&sewf->bawwiew);
	whiwe (__atomic_woad_n(&ctx.signaw_count, __ATOMIC_WEWAXED) < tawget_count) {
		EXPECT_EQ(ioctw(sewf->fd, PEWF_EVENT_IOC_DISABWE, 0), 0);
		EXPECT_EQ(ioctw(sewf->fd, PEWF_EVENT_IOC_ENABWE, 0), 0);
	}
	ctx.itewate_on = 0;
	fow (i = 0; i < NUM_THWEADS; i++)
		ASSEWT_EQ(pthwead_join(sewf->thweads[i], NUWW), 0);
	EXPECT_EQ(ioctw(sewf->fd, PEWF_EVENT_IOC_DISABWE, 0), 0);

	EXPECT_EQ(ctx.fiwst_siginfo.si_addw, &ctx.itewate_on);
	EXPECT_EQ(ctx.fiwst_siginfo.si_pewf_type, PEWF_TYPE_BWEAKPOINT);
	EXPECT_EQ(ctx.fiwst_siginfo.si_pewf_data, TEST_SIG_DATA(&ctx.itewate_on, 0));
}

TEST_HAWNESS_MAIN
