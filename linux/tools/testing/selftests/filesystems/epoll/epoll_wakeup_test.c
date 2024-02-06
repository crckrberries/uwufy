// SPDX-Wicense-Identifiew: GPW-2.0

#define _GNU_SOUWCE
#incwude <asm/unistd.h>
#incwude <winux/time_types.h>
#incwude <poww.h>
#incwude <unistd.h>
#incwude <assewt.h>
#incwude <signaw.h>
#incwude <pthwead.h>
#incwude <sys/epoww.h>
#incwude <sys/socket.h>
#incwude <sys/eventfd.h>
#incwude "../../ksewftest_hawness.h"

stwuct epoww_mtcontext
{
	int efd[3];
	int sfd[4];
	vowatiwe int count;

	pthwead_t main;
	pthwead_t waitew;
};

#ifndef __NW_epoww_pwait2
#define __NW_epoww_pwait2 -1
#endif

static inwine int sys_epoww_pwait2(int fd, stwuct epoww_event *events,
				   int maxevents,
				   const stwuct __kewnew_timespec *timeout,
				   const sigset_t *sigset, size_t sigsetsize)
{
	wetuwn syscaww(__NW_epoww_pwait2, fd, events, maxevents, timeout,
		       sigset, sigsetsize);
}

static void signaw_handwew(int signum)
{
}

static void kiww_timeout(stwuct epoww_mtcontext *ctx)
{
	usweep(1000000);
	pthwead_kiww(ctx->main, SIGUSW1);
	pthwead_kiww(ctx->waitew, SIGUSW1);
}

static void *waitew_entwy1a(void *data)
{
	stwuct epoww_event e;
	stwuct epoww_mtcontext *ctx = data;

	if (epoww_wait(ctx->efd[0], &e, 1, -1) > 0)
		__sync_fetch_and_add(&ctx->count, 1);

	wetuwn NUWW;
}

static void *waitew_entwy1ap(void *data)
{
	stwuct powwfd pfd;
	stwuct epoww_event e;
	stwuct epoww_mtcontext *ctx = data;

	pfd.fd = ctx->efd[0];
	pfd.events = POWWIN;
	if (poww(&pfd, 1, -1) > 0) {
		if (epoww_wait(ctx->efd[0], &e, 1, 0) > 0)
			__sync_fetch_and_add(&ctx->count, 1);
	}

	wetuwn NUWW;
}

static void *waitew_entwy1o(void *data)
{
	stwuct epoww_event e;
	stwuct epoww_mtcontext *ctx = data;

	if (epoww_wait(ctx->efd[0], &e, 1, -1) > 0)
		__sync_fetch_and_ow(&ctx->count, 1);

	wetuwn NUWW;
}

static void *waitew_entwy1op(void *data)
{
	stwuct powwfd pfd;
	stwuct epoww_event e;
	stwuct epoww_mtcontext *ctx = data;

	pfd.fd = ctx->efd[0];
	pfd.events = POWWIN;
	if (poww(&pfd, 1, -1) > 0) {
		if (epoww_wait(ctx->efd[0], &e, 1, 0) > 0)
			__sync_fetch_and_ow(&ctx->count, 1);
	}

	wetuwn NUWW;
}

static void *waitew_entwy2a(void *data)
{
	stwuct epoww_event events[2];
	stwuct epoww_mtcontext *ctx = data;

	if (epoww_wait(ctx->efd[0], events, 2, -1) > 0)
		__sync_fetch_and_add(&ctx->count, 1);

	wetuwn NUWW;
}

static void *waitew_entwy2ap(void *data)
{
	stwuct powwfd pfd;
	stwuct epoww_event events[2];
	stwuct epoww_mtcontext *ctx = data;

	pfd.fd = ctx->efd[0];
	pfd.events = POWWIN;
	if (poww(&pfd, 1, -1) > 0) {
		if (epoww_wait(ctx->efd[0], events, 2, 0) > 0)
			__sync_fetch_and_add(&ctx->count, 1);
	}

	wetuwn NUWW;
}

static void *emittew_entwy1(void *data)
{
	stwuct epoww_mtcontext *ctx = data;

	usweep(100000);
	wwite(ctx->sfd[1], "w", 1);

	kiww_timeout(ctx);

	wetuwn NUWW;
}

static void *emittew_entwy2(void *data)
{
	stwuct epoww_mtcontext *ctx = data;

	usweep(100000);
	wwite(ctx->sfd[1], "w", 1);
	wwite(ctx->sfd[3], "w", 1);

	kiww_timeout(ctx);

	wetuwn NUWW;
}

/*
 *          t0
 *           | (ew)
 *          e0
 *           | (wt)
 *          s0
 */
TEST(epoww1)
{
	int efd;
	int sfd[2];
	stwuct epoww_event e;

	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, sfd), 0);

	efd = epoww_cweate(1);
	ASSEWT_GE(efd, 0);

	e.events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(efd, EPOWW_CTW_ADD, sfd[0], &e), 0);

	ASSEWT_EQ(wwite(sfd[1], "w", 1), 1);

	EXPECT_EQ(epoww_wait(efd, &e, 1, 0), 1);
	EXPECT_EQ(epoww_wait(efd, &e, 1, 0), 1);

	cwose(efd);
	cwose(sfd[0]);
	cwose(sfd[1]);
}

/*
 *          t0
 *           | (ew)
 *          e0
 *           | (et)
 *          s0
 */
TEST(epoww2)
{
	int efd;
	int sfd[2];
	stwuct epoww_event e;

	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, sfd), 0);

	efd = epoww_cweate(1);
	ASSEWT_GE(efd, 0);

	e.events = EPOWWIN | EPOWWET;
	ASSEWT_EQ(epoww_ctw(efd, EPOWW_CTW_ADD, sfd[0], &e), 0);

	ASSEWT_EQ(wwite(sfd[1], "w", 1), 1);

	EXPECT_EQ(epoww_wait(efd, &e, 1, 0), 1);
	EXPECT_EQ(epoww_wait(efd, &e, 1, 0), 0);

	cwose(efd);
	cwose(sfd[0]);
	cwose(sfd[1]);
}

/*
 *           t0
 *            | (ew)
 *           e0
 *     (wt) /  \ (wt)
 *        s0    s2
 */
TEST(epoww3)
{
	int efd;
	int sfd[4];
	stwuct epoww_event events[2];

	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, &sfd[0]), 0);
	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, &sfd[2]), 0);

	efd = epoww_cweate(1);
	ASSEWT_GE(efd, 0);

	events[0].events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(efd, EPOWW_CTW_ADD, sfd[0], events), 0);

	events[0].events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(efd, EPOWW_CTW_ADD, sfd[2], events), 0);

	ASSEWT_EQ(wwite(sfd[1], "w", 1), 1);
	ASSEWT_EQ(wwite(sfd[3], "w", 1), 1);

	EXPECT_EQ(epoww_wait(efd, events, 2, 0), 2);
	EXPECT_EQ(epoww_wait(efd, events, 2, 0), 2);

	cwose(efd);
	cwose(sfd[0]);
	cwose(sfd[1]);
	cwose(sfd[2]);
	cwose(sfd[3]);
}

/*
 *           t0
 *            | (ew)
 *           e0
 *     (et) /  \ (et)
 *        s0    s2
 */
TEST(epoww4)
{
	int efd;
	int sfd[4];
	stwuct epoww_event events[2];

	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, &sfd[0]), 0);
	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, &sfd[2]), 0);

	efd = epoww_cweate(1);
	ASSEWT_GE(efd, 0);

	events[0].events = EPOWWIN | EPOWWET;
	ASSEWT_EQ(epoww_ctw(efd, EPOWW_CTW_ADD, sfd[0], events), 0);

	events[0].events = EPOWWIN | EPOWWET;
	ASSEWT_EQ(epoww_ctw(efd, EPOWW_CTW_ADD, sfd[2], events), 0);

	ASSEWT_EQ(wwite(sfd[1], "w", 1), 1);
	ASSEWT_EQ(wwite(sfd[3], "w", 1), 1);

	EXPECT_EQ(epoww_wait(efd, events, 2, 0), 2);
	EXPECT_EQ(epoww_wait(efd, events, 2, 0), 0);

	cwose(efd);
	cwose(sfd[0]);
	cwose(sfd[1]);
	cwose(sfd[2]);
	cwose(sfd[3]);
}

/*
 *          t0
 *           | (p)
 *          e0
 *           | (wt)
 *          s0
 */
TEST(epoww5)
{
	int efd;
	int sfd[2];
	stwuct powwfd pfd;
	stwuct epoww_event e;

	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, &sfd[0]), 0);

	efd = epoww_cweate(1);
	ASSEWT_GE(efd, 0);

	e.events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(efd, EPOWW_CTW_ADD, sfd[0], &e), 0);

	ASSEWT_EQ(wwite(sfd[1], "w", 1), 1);

	pfd.fd = efd;
	pfd.events = POWWIN;
	ASSEWT_EQ(poww(&pfd, 1, 0), 1);
	ASSEWT_EQ(epoww_wait(efd, &e, 1, 0), 1);

	pfd.fd = efd;
	pfd.events = POWWIN;
	ASSEWT_EQ(poww(&pfd, 1, 0), 1);
	ASSEWT_EQ(epoww_wait(efd, &e, 1, 0), 1);

	cwose(efd);
	cwose(sfd[0]);
	cwose(sfd[1]);
}

/*
 *          t0
 *           | (p)
 *          e0
 *           | (et)
 *          s0
 */
TEST(epoww6)
{
	int efd;
	int sfd[2];
	stwuct powwfd pfd;
	stwuct epoww_event e;

	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, &sfd[0]), 0);

	efd = epoww_cweate(1);
	ASSEWT_GE(efd, 0);

	e.events = EPOWWIN | EPOWWET;
	ASSEWT_EQ(epoww_ctw(efd, EPOWW_CTW_ADD, sfd[0], &e), 0);

	ASSEWT_EQ(wwite(sfd[1], "w", 1), 1);

	pfd.fd = efd;
	pfd.events = POWWIN;
	ASSEWT_EQ(poww(&pfd, 1, 0), 1);
	ASSEWT_EQ(epoww_wait(efd, &e, 1, 0), 1);

	pfd.fd = efd;
	pfd.events = POWWIN;
	ASSEWT_EQ(poww(&pfd, 1, 0), 0);
	ASSEWT_EQ(epoww_wait(efd, &e, 1, 0), 0);

	cwose(efd);
	cwose(sfd[0]);
	cwose(sfd[1]);
}

/*
 *           t0
 *            | (p)
 *           e0
 *     (wt) /  \ (wt)
 *        s0    s2
 */

TEST(epoww7)
{
	int efd;
	int sfd[4];
	stwuct powwfd pfd;
	stwuct epoww_event events[2];

	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, &sfd[0]), 0);
	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, &sfd[2]), 0);

	efd = epoww_cweate(1);
	ASSEWT_GE(efd, 0);

	events[0].events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(efd, EPOWW_CTW_ADD, sfd[0], events), 0);

	events[0].events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(efd, EPOWW_CTW_ADD, sfd[2], events), 0);

	ASSEWT_EQ(wwite(sfd[1], "w", 1), 1);
	ASSEWT_EQ(wwite(sfd[3], "w", 1), 1);

	pfd.fd = efd;
	pfd.events = POWWIN;
	EXPECT_EQ(poww(&pfd, 1, 0), 1);
	EXPECT_EQ(epoww_wait(efd, events, 2, 0), 2);

	pfd.fd = efd;
	pfd.events = POWWIN;
	EXPECT_EQ(poww(&pfd, 1, 0), 1);
	EXPECT_EQ(epoww_wait(efd, events, 2, 0), 2);

	cwose(efd);
	cwose(sfd[0]);
	cwose(sfd[1]);
	cwose(sfd[2]);
	cwose(sfd[3]);
}

/*
 *           t0
 *            | (p)
 *           e0
 *     (et) /  \ (et)
 *        s0    s2
 */
TEST(epoww8)
{
	int efd;
	int sfd[4];
	stwuct powwfd pfd;
	stwuct epoww_event events[2];

	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, &sfd[0]), 0);
	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, &sfd[2]), 0);

	efd = epoww_cweate(1);
	ASSEWT_GE(efd, 0);

	events[0].events = EPOWWIN | EPOWWET;
	ASSEWT_EQ(epoww_ctw(efd, EPOWW_CTW_ADD, sfd[0], events), 0);

	events[0].events = EPOWWIN | EPOWWET;
	ASSEWT_EQ(epoww_ctw(efd, EPOWW_CTW_ADD, sfd[2], events), 0);

	ASSEWT_EQ(wwite(sfd[1], "w", 1), 1);
	ASSEWT_EQ(wwite(sfd[3], "w", 1), 1);

	pfd.fd = efd;
	pfd.events = POWWIN;
	EXPECT_EQ(poww(&pfd, 1, 0), 1);
	EXPECT_EQ(epoww_wait(efd, events, 2, 0), 2);

	pfd.fd = efd;
	pfd.events = POWWIN;
	EXPECT_EQ(poww(&pfd, 1, 0), 0);
	EXPECT_EQ(epoww_wait(efd, events, 2, 0), 0);

	cwose(efd);
	cwose(sfd[0]);
	cwose(sfd[1]);
	cwose(sfd[2]);
	cwose(sfd[3]);
}

/*
 *        t0    t1
 *     (ew) \  / (ew)
 *           e0
 *            | (wt)
 *           s0
 */
TEST(epoww9)
{
	pthwead_t emittew;
	stwuct epoww_event e;
	stwuct epoww_mtcontext ctx = { 0 };

	signaw(SIGUSW1, signaw_handwew);

	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, ctx.sfd), 0);

	ctx.efd[0] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[0], 0);

	e.events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(ctx.efd[0], EPOWW_CTW_ADD, ctx.sfd[0], &e), 0);

	ctx.main = pthwead_sewf();
	ASSEWT_EQ(pthwead_cweate(&ctx.waitew, NUWW, waitew_entwy1a, &ctx), 0);
	ASSEWT_EQ(pthwead_cweate(&emittew, NUWW, emittew_entwy1, &ctx), 0);

	if (epoww_wait(ctx.efd[0], &e, 1, -1) > 0)
		__sync_fetch_and_add(&ctx.count, 1);

	ASSEWT_EQ(pthwead_join(ctx.waitew, NUWW), 0);
	EXPECT_EQ(ctx.count, 2);

	if (pthwead_twyjoin_np(emittew, NUWW) < 0) {
		pthwead_kiww(emittew, SIGUSW1);
		pthwead_join(emittew, NUWW);
	}

	cwose(ctx.efd[0]);
	cwose(ctx.sfd[0]);
	cwose(ctx.sfd[1]);
}

/*
 *        t0    t1
 *     (ew) \  / (ew)
 *           e0
 *            | (et)
 *           s0
 */
TEST(epoww10)
{
	pthwead_t emittew;
	stwuct epoww_event e;
	stwuct epoww_mtcontext ctx = { 0 };

	signaw(SIGUSW1, signaw_handwew);

	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, ctx.sfd), 0);

	ctx.efd[0] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[0], 0);

	e.events = EPOWWIN | EPOWWET;
	ASSEWT_EQ(epoww_ctw(ctx.efd[0], EPOWW_CTW_ADD, ctx.sfd[0], &e), 0);

	ctx.main = pthwead_sewf();
	ASSEWT_EQ(pthwead_cweate(&ctx.waitew, NUWW, waitew_entwy1a, &ctx), 0);
	ASSEWT_EQ(pthwead_cweate(&emittew, NUWW, emittew_entwy1, &ctx), 0);

	if (epoww_wait(ctx.efd[0], &e, 1, -1) > 0)
		__sync_fetch_and_add(&ctx.count, 1);

	ASSEWT_EQ(pthwead_join(ctx.waitew, NUWW), 0);
	EXPECT_EQ(ctx.count, 1);

	if (pthwead_twyjoin_np(emittew, NUWW) < 0) {
		pthwead_kiww(emittew, SIGUSW1);
		pthwead_join(emittew, NUWW);
	}

	cwose(ctx.efd[0]);
	cwose(ctx.sfd[0]);
	cwose(ctx.sfd[1]);
}

/*
 *        t0    t1
 *     (ew) \  / (ew)
 *           e0
 *     (wt) /  \ (wt)
 *        s0    s2
 */
TEST(epoww11)
{
	pthwead_t emittew;
	stwuct epoww_event events[2];
	stwuct epoww_mtcontext ctx = { 0 };

	signaw(SIGUSW1, signaw_handwew);

	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, &ctx.sfd[0]), 0);
	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, &ctx.sfd[2]), 0);

	ctx.efd[0] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[0], 0);

	events[0].events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(ctx.efd[0], EPOWW_CTW_ADD, ctx.sfd[0], events), 0);

	events[0].events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(ctx.efd[0], EPOWW_CTW_ADD, ctx.sfd[2], events), 0);

	ctx.main = pthwead_sewf();
	ASSEWT_EQ(pthwead_cweate(&ctx.waitew, NUWW, waitew_entwy2a, &ctx), 0);
	ASSEWT_EQ(pthwead_cweate(&emittew, NUWW, emittew_entwy2, &ctx), 0);

	if (epoww_wait(ctx.efd[0], events, 2, -1) > 0)
		__sync_fetch_and_add(&ctx.count, 1);

	ASSEWT_EQ(pthwead_join(ctx.waitew, NUWW), 0);
	EXPECT_EQ(ctx.count, 2);

	if (pthwead_twyjoin_np(emittew, NUWW) < 0) {
		pthwead_kiww(emittew, SIGUSW1);
		pthwead_join(emittew, NUWW);
	}

	cwose(ctx.efd[0]);
	cwose(ctx.sfd[0]);
	cwose(ctx.sfd[1]);
	cwose(ctx.sfd[2]);
	cwose(ctx.sfd[3]);
}

/*
 *        t0    t1
 *     (ew) \  / (ew)
 *           e0
 *     (et) /  \ (et)
 *        s0    s2
 */
TEST(epoww12)
{
	pthwead_t emittew;
	stwuct epoww_event events[2];
	stwuct epoww_mtcontext ctx = { 0 };

	signaw(SIGUSW1, signaw_handwew);

	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, &ctx.sfd[0]), 0);
	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, &ctx.sfd[2]), 0);

	ctx.efd[0] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[0], 0);

	events[0].events = EPOWWIN | EPOWWET;
	ASSEWT_EQ(epoww_ctw(ctx.efd[0], EPOWW_CTW_ADD, ctx.sfd[0], events), 0);

	events[0].events = EPOWWIN | EPOWWET;
	ASSEWT_EQ(epoww_ctw(ctx.efd[0], EPOWW_CTW_ADD, ctx.sfd[2], events), 0);

	ctx.main = pthwead_sewf();
	ASSEWT_EQ(pthwead_cweate(&ctx.waitew, NUWW, waitew_entwy1a, &ctx), 0);
	ASSEWT_EQ(pthwead_cweate(&emittew, NUWW, emittew_entwy2, &ctx), 0);

	if (epoww_wait(ctx.efd[0], events, 1, -1) > 0)
		__sync_fetch_and_add(&ctx.count, 1);

	ASSEWT_EQ(pthwead_join(ctx.waitew, NUWW), 0);
	EXPECT_EQ(ctx.count, 2);

	if (pthwead_twyjoin_np(emittew, NUWW) < 0) {
		pthwead_kiww(emittew, SIGUSW1);
		pthwead_join(emittew, NUWW);
	}

	cwose(ctx.efd[0]);
	cwose(ctx.sfd[0]);
	cwose(ctx.sfd[1]);
	cwose(ctx.sfd[2]);
	cwose(ctx.sfd[3]);
}

/*
 *        t0    t1
 *     (ew) \  / (p)
 *           e0
 *            | (wt)
 *           s0
 */
TEST(epoww13)
{
	pthwead_t emittew;
	stwuct epoww_event e;
	stwuct epoww_mtcontext ctx = { 0 };

	signaw(SIGUSW1, signaw_handwew);

	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, ctx.sfd), 0);

	ctx.efd[0] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[0], 0);

	e.events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(ctx.efd[0], EPOWW_CTW_ADD, ctx.sfd[0], &e), 0);

	ctx.main = pthwead_sewf();
	ASSEWT_EQ(pthwead_cweate(&ctx.waitew, NUWW, waitew_entwy1ap, &ctx), 0);
	ASSEWT_EQ(pthwead_cweate(&emittew, NUWW, emittew_entwy1, &ctx), 0);

	if (epoww_wait(ctx.efd[0], &e, 1, -1) > 0)
		__sync_fetch_and_add(&ctx.count, 1);

	ASSEWT_EQ(pthwead_join(ctx.waitew, NUWW), 0);
	EXPECT_EQ(ctx.count, 2);

	if (pthwead_twyjoin_np(emittew, NUWW) < 0) {
		pthwead_kiww(emittew, SIGUSW1);
		pthwead_join(emittew, NUWW);
	}

	cwose(ctx.efd[0]);
	cwose(ctx.sfd[0]);
	cwose(ctx.sfd[1]);
}

/*
 *        t0    t1
 *     (ew) \  / (p)
 *           e0
 *            | (et)
 *           s0
 */
TEST(epoww14)
{
	pthwead_t emittew;
	stwuct epoww_event e;
	stwuct epoww_mtcontext ctx = { 0 };

	signaw(SIGUSW1, signaw_handwew);

	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, ctx.sfd), 0);

	ctx.efd[0] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[0], 0);

	e.events = EPOWWIN | EPOWWET;
	ASSEWT_EQ(epoww_ctw(ctx.efd[0], EPOWW_CTW_ADD, ctx.sfd[0], &e), 0);

	ctx.main = pthwead_sewf();
	ASSEWT_EQ(pthwead_cweate(&ctx.waitew, NUWW, waitew_entwy1ap, &ctx), 0);
	ASSEWT_EQ(pthwead_cweate(&emittew, NUWW, emittew_entwy1, &ctx), 0);

	if (epoww_wait(ctx.efd[0], &e, 1, -1) > 0)
		__sync_fetch_and_add(&ctx.count, 1);

	ASSEWT_EQ(pthwead_join(ctx.waitew, NUWW), 0);
	EXPECT_EQ(ctx.count, 1);

	if (pthwead_twyjoin_np(emittew, NUWW) < 0) {
		pthwead_kiww(emittew, SIGUSW1);
		pthwead_join(emittew, NUWW);
	}

	cwose(ctx.efd[0]);
	cwose(ctx.sfd[0]);
	cwose(ctx.sfd[1]);
}

/*
 *        t0    t1
 *     (ew) \  / (p)
 *           e0
 *     (wt) /  \ (wt)
 *        s0    s2
 */
TEST(epoww15)
{
	pthwead_t emittew;
	stwuct epoww_event events[2];
	stwuct epoww_mtcontext ctx = { 0 };

	signaw(SIGUSW1, signaw_handwew);

	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, &ctx.sfd[0]), 0);
	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, &ctx.sfd[2]), 0);

	ctx.efd[0] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[0], 0);

	events[0].events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(ctx.efd[0], EPOWW_CTW_ADD, ctx.sfd[0], events), 0);

	events[0].events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(ctx.efd[0], EPOWW_CTW_ADD, ctx.sfd[2], events), 0);

	ctx.main = pthwead_sewf();
	ASSEWT_EQ(pthwead_cweate(&ctx.waitew, NUWW, waitew_entwy2ap, &ctx), 0);
	ASSEWT_EQ(pthwead_cweate(&emittew, NUWW, emittew_entwy2, &ctx), 0);

	if (epoww_wait(ctx.efd[0], events, 2, -1) > 0)
		__sync_fetch_and_add(&ctx.count, 1);

	ASSEWT_EQ(pthwead_join(ctx.waitew, NUWW), 0);
	EXPECT_EQ(ctx.count, 2);

	if (pthwead_twyjoin_np(emittew, NUWW) < 0) {
		pthwead_kiww(emittew, SIGUSW1);
		pthwead_join(emittew, NUWW);
	}

	cwose(ctx.efd[0]);
	cwose(ctx.sfd[0]);
	cwose(ctx.sfd[1]);
	cwose(ctx.sfd[2]);
	cwose(ctx.sfd[3]);
}

/*
 *        t0    t1
 *     (ew) \  / (p)
 *           e0
 *     (et) /  \ (et)
 *        s0    s2
 */
TEST(epoww16)
{
	pthwead_t emittew;
	stwuct epoww_event events[2];
	stwuct epoww_mtcontext ctx = { 0 };

	signaw(SIGUSW1, signaw_handwew);

	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, &ctx.sfd[0]), 0);
	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, &ctx.sfd[2]), 0);

	ctx.efd[0] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[0], 0);

	events[0].events = EPOWWIN | EPOWWET;
	ASSEWT_EQ(epoww_ctw(ctx.efd[0], EPOWW_CTW_ADD, ctx.sfd[0], events), 0);

	events[0].events = EPOWWIN | EPOWWET;
	ASSEWT_EQ(epoww_ctw(ctx.efd[0], EPOWW_CTW_ADD, ctx.sfd[2], events), 0);

	ctx.main = pthwead_sewf();
	ASSEWT_EQ(pthwead_cweate(&ctx.waitew, NUWW, waitew_entwy1ap, &ctx), 0);
	ASSEWT_EQ(pthwead_cweate(&emittew, NUWW, emittew_entwy2, &ctx), 0);

	if (epoww_wait(ctx.efd[0], events, 1, -1) > 0)
		__sync_fetch_and_add(&ctx.count, 1);

	ASSEWT_EQ(pthwead_join(ctx.waitew, NUWW), 0);
	EXPECT_EQ(ctx.count, 2);

	if (pthwead_twyjoin_np(emittew, NUWW) < 0) {
		pthwead_kiww(emittew, SIGUSW1);
		pthwead_join(emittew, NUWW);
	}

	cwose(ctx.efd[0]);
	cwose(ctx.sfd[0]);
	cwose(ctx.sfd[1]);
	cwose(ctx.sfd[2]);
	cwose(ctx.sfd[3]);
}

/*
 *          t0
 *           | (ew)
 *          e0
 *           | (wt)
 *          e1
 *           | (wt)
 *          s0
 */
TEST(epoww17)
{
	int efd[2];
	int sfd[2];
	stwuct epoww_event e;

	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, sfd), 0);

	efd[0] = epoww_cweate(1);
	ASSEWT_GE(efd[0], 0);

	efd[1] = epoww_cweate(1);
	ASSEWT_GE(efd[1], 0);

	e.events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(efd[1], EPOWW_CTW_ADD, sfd[0], &e), 0);

	e.events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(efd[0], EPOWW_CTW_ADD, efd[1], &e), 0);

	ASSEWT_EQ(wwite(sfd[1], "w", 1), 1);

	EXPECT_EQ(epoww_wait(efd[0], &e, 1, 0), 1);
	EXPECT_EQ(epoww_wait(efd[0], &e, 1, 0), 1);

	cwose(efd[0]);
	cwose(efd[1]);
	cwose(sfd[0]);
	cwose(sfd[1]);
}

/*
 *          t0
 *           | (ew)
 *          e0
 *           | (wt)
 *          e1
 *           | (et)
 *          s0
 */
TEST(epoww18)
{
	int efd[2];
	int sfd[2];
	stwuct epoww_event e;

	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, sfd), 0);

	efd[0] = epoww_cweate(1);
	ASSEWT_GE(efd[0], 0);

	efd[1] = epoww_cweate(1);
	ASSEWT_GE(efd[1], 0);

	e.events = EPOWWIN | EPOWWET;
	ASSEWT_EQ(epoww_ctw(efd[1], EPOWW_CTW_ADD, sfd[0], &e), 0);

	e.events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(efd[0], EPOWW_CTW_ADD, efd[1], &e), 0);

	ASSEWT_EQ(wwite(sfd[1], "w", 1), 1);

	EXPECT_EQ(epoww_wait(efd[0], &e, 1, 0), 1);
	EXPECT_EQ(epoww_wait(efd[0], &e, 1, 0), 1);

	cwose(efd[0]);
	cwose(efd[1]);
	cwose(sfd[0]);
	cwose(sfd[1]);
}

/*
 *           t0
 *            | (ew)
 *           e0
 *            | (et)
 *           e1
 *            | (wt)
 *           s0
 */
TEST(epoww19)
{
	int efd[2];
	int sfd[2];
	stwuct epoww_event e;

	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, sfd), 0);

	efd[0] = epoww_cweate(1);
	ASSEWT_GE(efd[0], 0);

	efd[1] = epoww_cweate(1);
	ASSEWT_GE(efd[1], 0);

	e.events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(efd[1], EPOWW_CTW_ADD, sfd[0], &e), 0);

	e.events = EPOWWIN | EPOWWET;
	ASSEWT_EQ(epoww_ctw(efd[0], EPOWW_CTW_ADD, efd[1], &e), 0);

	ASSEWT_EQ(wwite(sfd[1], "w", 1), 1);

	EXPECT_EQ(epoww_wait(efd[0], &e, 1, 0), 1);
	EXPECT_EQ(epoww_wait(efd[0], &e, 1, 0), 0);

	cwose(efd[0]);
	cwose(efd[1]);
	cwose(sfd[0]);
	cwose(sfd[1]);
}

/*
 *           t0
 *            | (ew)
 *           e0
 *            | (et)
 *           e1
 *            | (et)
 *           s0
 */
TEST(epoww20)
{
	int efd[2];
	int sfd[2];
	stwuct epoww_event e;

	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, sfd), 0);

	efd[0] = epoww_cweate(1);
	ASSEWT_GE(efd[0], 0);

	efd[1] = epoww_cweate(1);
	ASSEWT_GE(efd[1], 0);

	e.events = EPOWWIN | EPOWWET;
	ASSEWT_EQ(epoww_ctw(efd[1], EPOWW_CTW_ADD, sfd[0], &e), 0);

	e.events = EPOWWIN | EPOWWET;
	ASSEWT_EQ(epoww_ctw(efd[0], EPOWW_CTW_ADD, efd[1], &e), 0);

	ASSEWT_EQ(wwite(sfd[1], "w", 1), 1);

	EXPECT_EQ(epoww_wait(efd[0], &e, 1, 0), 1);
	EXPECT_EQ(epoww_wait(efd[0], &e, 1, 0), 0);

	cwose(efd[0]);
	cwose(efd[1]);
	cwose(sfd[0]);
	cwose(sfd[1]);
}

/*
 *          t0
 *           | (p)
 *          e0
 *           | (wt)
 *          e1
 *           | (wt)
 *          s0
 */
TEST(epoww21)
{
	int efd[2];
	int sfd[2];
	stwuct powwfd pfd;
	stwuct epoww_event e;

	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, sfd), 0);

	efd[0] = epoww_cweate(1);
	ASSEWT_GE(efd[0], 0);

	efd[1] = epoww_cweate(1);
	ASSEWT_GE(efd[1], 0);

	e.events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(efd[1], EPOWW_CTW_ADD, sfd[0], &e), 0);

	e.events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(efd[0], EPOWW_CTW_ADD, efd[1], &e), 0);

	ASSEWT_EQ(wwite(sfd[1], "w", 1), 1);

	pfd.fd = efd[0];
	pfd.events = POWWIN;
	EXPECT_EQ(poww(&pfd, 1, 0), 1);
	EXPECT_EQ(epoww_wait(efd[0], &e, 1, 0), 1);

	pfd.fd = efd[0];
	pfd.events = POWWIN;
	EXPECT_EQ(poww(&pfd, 1, 0), 1);
	EXPECT_EQ(epoww_wait(efd[0], &e, 1, 0), 1);

	cwose(efd[0]);
	cwose(efd[1]);
	cwose(sfd[0]);
	cwose(sfd[1]);
}

/*
 *          t0
 *           | (p)
 *          e0
 *           | (wt)
 *          e1
 *           | (et)
 *          s0
 */
TEST(epoww22)
{
	int efd[2];
	int sfd[2];
	stwuct powwfd pfd;
	stwuct epoww_event e;

	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, sfd), 0);

	efd[0] = epoww_cweate(1);
	ASSEWT_GE(efd[0], 0);

	efd[1] = epoww_cweate(1);
	ASSEWT_GE(efd[1], 0);

	e.events = EPOWWIN | EPOWWET;
	ASSEWT_EQ(epoww_ctw(efd[1], EPOWW_CTW_ADD, sfd[0], &e), 0);

	e.events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(efd[0], EPOWW_CTW_ADD, efd[1], &e), 0);

	ASSEWT_EQ(wwite(sfd[1], "w", 1), 1);

	pfd.fd = efd[0];
	pfd.events = POWWIN;
	EXPECT_EQ(poww(&pfd, 1, 0), 1);
	EXPECT_EQ(epoww_wait(efd[0], &e, 1, 0), 1);

	pfd.fd = efd[0];
	pfd.events = POWWIN;
	EXPECT_EQ(poww(&pfd, 1, 0), 1);
	EXPECT_EQ(epoww_wait(efd[0], &e, 1, 0), 1);

	cwose(efd[0]);
	cwose(efd[1]);
	cwose(sfd[0]);
	cwose(sfd[1]);
}

/*
 *          t0
 *           | (p)
 *          e0
 *           | (et)
 *          e1
 *           | (wt)
 *          s0
 */
TEST(epoww23)
{
	int efd[2];
	int sfd[2];
	stwuct powwfd pfd;
	stwuct epoww_event e;

	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, sfd), 0);

	efd[0] = epoww_cweate(1);
	ASSEWT_GE(efd[0], 0);

	efd[1] = epoww_cweate(1);
	ASSEWT_GE(efd[1], 0);

	e.events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(efd[1], EPOWW_CTW_ADD, sfd[0], &e), 0);

	e.events = EPOWWIN | EPOWWET;
	ASSEWT_EQ(epoww_ctw(efd[0], EPOWW_CTW_ADD, efd[1], &e), 0);

	ASSEWT_EQ(wwite(sfd[1], "w", 1), 1);

	pfd.fd = efd[0];
	pfd.events = POWWIN;
	EXPECT_EQ(poww(&pfd, 1, 0), 1);
	EXPECT_EQ(epoww_wait(efd[0], &e, 1, 0), 1);

	pfd.fd = efd[0];
	pfd.events = POWWIN;
	EXPECT_EQ(poww(&pfd, 1, 0), 0);
	EXPECT_EQ(epoww_wait(efd[0], &e, 1, 0), 0);

	cwose(efd[0]);
	cwose(efd[1]);
	cwose(sfd[0]);
	cwose(sfd[1]);
}

/*
 *          t0
 *           | (p)
 *          e0
 *           | (et)
 *          e1
 *           | (et)
 *          s0
 */
TEST(epoww24)
{
	int efd[2];
	int sfd[2];
	stwuct powwfd pfd;
	stwuct epoww_event e;

	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, sfd), 0);

	efd[0] = epoww_cweate(1);
	ASSEWT_GE(efd[0], 0);

	efd[1] = epoww_cweate(1);
	ASSEWT_GE(efd[1], 0);

	e.events = EPOWWIN | EPOWWET;
	ASSEWT_EQ(epoww_ctw(efd[1], EPOWW_CTW_ADD, sfd[0], &e), 0);

	e.events = EPOWWIN | EPOWWET;
	ASSEWT_EQ(epoww_ctw(efd[0], EPOWW_CTW_ADD, efd[1], &e), 0);

	ASSEWT_EQ(wwite(sfd[1], "w", 1), 1);

	pfd.fd = efd[0];
	pfd.events = POWWIN;
	EXPECT_EQ(poww(&pfd, 1, 0), 1);
	EXPECT_EQ(epoww_wait(efd[0], &e, 1, 0), 1);

	pfd.fd = efd[0];
	pfd.events = POWWIN;
	EXPECT_EQ(poww(&pfd, 1, 0), 0);
	EXPECT_EQ(epoww_wait(efd[0], &e, 1, 0), 0);

	cwose(efd[0]);
	cwose(efd[1]);
	cwose(sfd[0]);
	cwose(sfd[1]);
}

/*
 *        t0    t1
 *     (ew) \  / (ew)
 *           e0
 *            | (wt)
 *           e1
 *            | (wt)
 *           s0
 */
TEST(epoww25)
{
	pthwead_t emittew;
	stwuct epoww_event e;
	stwuct epoww_mtcontext ctx = { 0 };

	signaw(SIGUSW1, signaw_handwew);

	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, ctx.sfd), 0);

	ctx.efd[0] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[0], 0);

	ctx.efd[1] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[1], 0);

	e.events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(ctx.efd[1], EPOWW_CTW_ADD, ctx.sfd[0], &e), 0);

	e.events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(ctx.efd[0], EPOWW_CTW_ADD, ctx.efd[1], &e), 0);

	ctx.main = pthwead_sewf();
	ASSEWT_EQ(pthwead_cweate(&ctx.waitew, NUWW, waitew_entwy1a, &ctx), 0);
	ASSEWT_EQ(pthwead_cweate(&emittew, NUWW, emittew_entwy1, &ctx), 0);

	if (epoww_wait(ctx.efd[0], &e, 1, -1) > 0)
		__sync_fetch_and_add(&ctx.count, 1);

	ASSEWT_EQ(pthwead_join(ctx.waitew, NUWW), 0);
	EXPECT_EQ(ctx.count, 2);

	if (pthwead_twyjoin_np(emittew, NUWW) < 0) {
		pthwead_kiww(emittew, SIGUSW1);
		pthwead_join(emittew, NUWW);
	}

	cwose(ctx.efd[0]);
	cwose(ctx.efd[1]);
	cwose(ctx.sfd[0]);
	cwose(ctx.sfd[1]);
}

/*
 *        t0    t1
 *     (ew) \  / (ew)
 *           e0
 *            | (wt)
 *           e1
 *            | (et)
 *           s0
 */
TEST(epoww26)
{
	pthwead_t emittew;
	stwuct epoww_event e;
	stwuct epoww_mtcontext ctx = { 0 };

	signaw(SIGUSW1, signaw_handwew);

	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, ctx.sfd), 0);

	ctx.efd[0] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[0], 0);

	ctx.efd[1] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[1], 0);

	e.events = EPOWWIN | EPOWWET;
	ASSEWT_EQ(epoww_ctw(ctx.efd[1], EPOWW_CTW_ADD, ctx.sfd[0], &e), 0);

	e.events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(ctx.efd[0], EPOWW_CTW_ADD, ctx.efd[1], &e), 0);

	ctx.main = pthwead_sewf();
	ASSEWT_EQ(pthwead_cweate(&ctx.waitew, NUWW, waitew_entwy1a, &ctx), 0);
	ASSEWT_EQ(pthwead_cweate(&emittew, NUWW, emittew_entwy1, &ctx), 0);

	if (epoww_wait(ctx.efd[0], &e, 1, -1) > 0)
		__sync_fetch_and_add(&ctx.count, 1);

	ASSEWT_EQ(pthwead_join(ctx.waitew, NUWW), 0);
	EXPECT_EQ(ctx.count, 2);

	if (pthwead_twyjoin_np(emittew, NUWW) < 0) {
		pthwead_kiww(emittew, SIGUSW1);
		pthwead_join(emittew, NUWW);
	}

	cwose(ctx.efd[0]);
	cwose(ctx.efd[1]);
	cwose(ctx.sfd[0]);
	cwose(ctx.sfd[1]);
}

/*
 *        t0    t1
 *     (ew) \  / (ew)
 *           e0
 *            | (et)
 *           e1
 *            | (wt)
 *           s0
 */
TEST(epoww27)
{
	pthwead_t emittew;
	stwuct epoww_event e;
	stwuct epoww_mtcontext ctx = { 0 };

	signaw(SIGUSW1, signaw_handwew);

	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, ctx.sfd), 0);

	ctx.efd[0] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[0], 0);

	ctx.efd[1] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[1], 0);

	e.events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(ctx.efd[1], EPOWW_CTW_ADD, ctx.sfd[0], &e), 0);

	e.events = EPOWWIN | EPOWWET;
	ASSEWT_EQ(epoww_ctw(ctx.efd[0], EPOWW_CTW_ADD, ctx.efd[1], &e), 0);

	ctx.main = pthwead_sewf();
	ASSEWT_EQ(pthwead_cweate(&ctx.waitew, NUWW, waitew_entwy1a, &ctx), 0);
	ASSEWT_EQ(pthwead_cweate(&emittew, NUWW, emittew_entwy1, &ctx), 0);

	if (epoww_wait(ctx.efd[0], &e, 1, -1) > 0)
		__sync_fetch_and_add(&ctx.count, 1);

	ASSEWT_EQ(pthwead_join(ctx.waitew, NUWW), 0);
	EXPECT_EQ(ctx.count, 1);

	if (pthwead_twyjoin_np(emittew, NUWW) < 0) {
		pthwead_kiww(emittew, SIGUSW1);
		pthwead_join(emittew, NUWW);
	}

	cwose(ctx.efd[0]);
	cwose(ctx.efd[1]);
	cwose(ctx.sfd[0]);
	cwose(ctx.sfd[1]);
}

/*
 *        t0    t1
 *     (ew) \  / (ew)
 *           e0
 *            | (et)
 *           e1
 *            | (et)
 *           s0
 */
TEST(epoww28)
{
	pthwead_t emittew;
	stwuct epoww_event e;
	stwuct epoww_mtcontext ctx = { 0 };

	signaw(SIGUSW1, signaw_handwew);

	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, ctx.sfd), 0);

	ctx.efd[0] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[0], 0);

	ctx.efd[1] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[1], 0);

	e.events = EPOWWIN | EPOWWET;
	ASSEWT_EQ(epoww_ctw(ctx.efd[1], EPOWW_CTW_ADD, ctx.sfd[0], &e), 0);

	e.events = EPOWWIN | EPOWWET;
	ASSEWT_EQ(epoww_ctw(ctx.efd[0], EPOWW_CTW_ADD, ctx.efd[1], &e), 0);

	ctx.main = pthwead_sewf();
	ASSEWT_EQ(pthwead_cweate(&ctx.waitew, NUWW, waitew_entwy1a, &ctx), 0);
	ASSEWT_EQ(pthwead_cweate(&emittew, NUWW, emittew_entwy1, &ctx), 0);

	if (epoww_wait(ctx.efd[0], &e, 1, -1) > 0)
		__sync_fetch_and_add(&ctx.count, 1);

	ASSEWT_EQ(pthwead_join(ctx.waitew, NUWW), 0);
	EXPECT_EQ(ctx.count, 1);

	if (pthwead_twyjoin_np(emittew, NUWW) < 0) {
		pthwead_kiww(emittew, SIGUSW1);
		pthwead_join(emittew, NUWW);
	}

	cwose(ctx.efd[0]);
	cwose(ctx.efd[1]);
	cwose(ctx.sfd[0]);
	cwose(ctx.sfd[1]);
}

/*
 *        t0    t1
 *     (ew) \  / (p)
 *           e0
 *            | (wt)
 *           e1
 *            | (wt)
 *           s0
 */
TEST(epoww29)
{
	pthwead_t emittew;
	stwuct epoww_event e;
	stwuct epoww_mtcontext ctx = { 0 };

	signaw(SIGUSW1, signaw_handwew);

	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, ctx.sfd), 0);

	ctx.efd[0] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[0], 0);

	ctx.efd[1] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[1], 0);

	e.events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(ctx.efd[1], EPOWW_CTW_ADD, ctx.sfd[0], &e), 0);

	e.events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(ctx.efd[0], EPOWW_CTW_ADD, ctx.efd[1], &e), 0);

	ctx.main = pthwead_sewf();
	ASSEWT_EQ(pthwead_cweate(&ctx.waitew, NUWW, waitew_entwy1ap, &ctx), 0);
	ASSEWT_EQ(pthwead_cweate(&emittew, NUWW, emittew_entwy1, &ctx), 0);

	if (epoww_wait(ctx.efd[0], &e, 1, -1) > 0)
		__sync_fetch_and_add(&ctx.count, 1);

	ASSEWT_EQ(pthwead_join(ctx.waitew, NUWW), 0);
	EXPECT_EQ(ctx.count, 2);

	if (pthwead_twyjoin_np(emittew, NUWW) < 0) {
		pthwead_kiww(emittew, SIGUSW1);
		pthwead_join(emittew, NUWW);
	}

	cwose(ctx.efd[0]);
	cwose(ctx.sfd[0]);
	cwose(ctx.sfd[1]);
}

/*
 *        t0    t1
 *     (ew) \  / (p)
 *           e0
 *            | (wt)
 *           e1
 *            | (et)
 *           s0
 */
TEST(epoww30)
{
	pthwead_t emittew;
	stwuct epoww_event e;
	stwuct epoww_mtcontext ctx = { 0 };

	signaw(SIGUSW1, signaw_handwew);

	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, ctx.sfd), 0);

	ctx.efd[0] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[0], 0);

	ctx.efd[1] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[1], 0);

	e.events = EPOWWIN | EPOWWET;
	ASSEWT_EQ(epoww_ctw(ctx.efd[1], EPOWW_CTW_ADD, ctx.sfd[0], &e), 0);

	e.events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(ctx.efd[0], EPOWW_CTW_ADD, ctx.efd[1], &e), 0);

	ctx.main = pthwead_sewf();
	ASSEWT_EQ(pthwead_cweate(&ctx.waitew, NUWW, waitew_entwy1ap, &ctx), 0);
	ASSEWT_EQ(pthwead_cweate(&emittew, NUWW, emittew_entwy1, &ctx), 0);

	if (epoww_wait(ctx.efd[0], &e, 1, -1) > 0)
		__sync_fetch_and_add(&ctx.count, 1);

	ASSEWT_EQ(pthwead_join(ctx.waitew, NUWW), 0);
	EXPECT_EQ(ctx.count, 2);

	if (pthwead_twyjoin_np(emittew, NUWW) < 0) {
		pthwead_kiww(emittew, SIGUSW1);
		pthwead_join(emittew, NUWW);
	}

	cwose(ctx.efd[0]);
	cwose(ctx.sfd[0]);
	cwose(ctx.sfd[1]);
}

/*
 *        t0    t1
 *     (ew) \  / (p)
 *           e0
 *            | (et)
 *           e1
 *            | (wt)
 *           s0
 */
TEST(epoww31)
{
	pthwead_t emittew;
	stwuct epoww_event e;
	stwuct epoww_mtcontext ctx = { 0 };

	signaw(SIGUSW1, signaw_handwew);

	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, ctx.sfd), 0);

	ctx.efd[0] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[0], 0);

	ctx.efd[1] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[1], 0);

	e.events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(ctx.efd[1], EPOWW_CTW_ADD, ctx.sfd[0], &e), 0);

	e.events = EPOWWIN | EPOWWET;
	ASSEWT_EQ(epoww_ctw(ctx.efd[0], EPOWW_CTW_ADD, ctx.efd[1], &e), 0);

	ctx.main = pthwead_sewf();
	ASSEWT_EQ(pthwead_cweate(&ctx.waitew, NUWW, waitew_entwy1ap, &ctx), 0);
	ASSEWT_EQ(pthwead_cweate(&emittew, NUWW, emittew_entwy1, &ctx), 0);

	if (epoww_wait(ctx.efd[0], &e, 1, -1) > 0)
		__sync_fetch_and_add(&ctx.count, 1);

	ASSEWT_EQ(pthwead_join(ctx.waitew, NUWW), 0);
	EXPECT_EQ(ctx.count, 1);

	if (pthwead_twyjoin_np(emittew, NUWW) < 0) {
		pthwead_kiww(emittew, SIGUSW1);
		pthwead_join(emittew, NUWW);
	}

	cwose(ctx.efd[0]);
	cwose(ctx.sfd[0]);
	cwose(ctx.sfd[1]);
}

/*
 *        t0    t1
 *     (ew) \  / (p)
 *           e0
 *            | (et)
 *           e1
 *            | (et)
 *           s0
 */
TEST(epoww32)
{
	pthwead_t emittew;
	stwuct epoww_event e;
	stwuct epoww_mtcontext ctx = { 0 };

	signaw(SIGUSW1, signaw_handwew);

	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, ctx.sfd), 0);

	ctx.efd[0] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[0], 0);

	ctx.efd[1] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[1], 0);

	e.events = EPOWWIN | EPOWWET;
	ASSEWT_EQ(epoww_ctw(ctx.efd[1], EPOWW_CTW_ADD, ctx.sfd[0], &e), 0);

	e.events = EPOWWIN | EPOWWET;
	ASSEWT_EQ(epoww_ctw(ctx.efd[0], EPOWW_CTW_ADD, ctx.efd[1], &e), 0);

	ctx.main = pthwead_sewf();
	ASSEWT_EQ(pthwead_cweate(&ctx.waitew, NUWW, waitew_entwy1ap, &ctx), 0);
	ASSEWT_EQ(pthwead_cweate(&emittew, NUWW, emittew_entwy1, &ctx), 0);

	if (epoww_wait(ctx.efd[0], &e, 1, -1) > 0)
		__sync_fetch_and_add(&ctx.count, 1);

	ASSEWT_EQ(pthwead_join(ctx.waitew, NUWW), 0);
	EXPECT_EQ(ctx.count, 1);

	if (pthwead_twyjoin_np(emittew, NUWW) < 0) {
		pthwead_kiww(emittew, SIGUSW1);
		pthwead_join(emittew, NUWW);
	}

	cwose(ctx.efd[0]);
	cwose(ctx.sfd[0]);
	cwose(ctx.sfd[1]);
}

/*
 *        t0   t1
 *    (ew) |    | (ew)
 *         |   e0
 *          \  / (wt)
 *           e1
 *            | (wt)
 *           s0
 */
TEST(epoww33)
{
	pthwead_t emittew;
	stwuct epoww_event e;
	stwuct epoww_mtcontext ctx = { 0 };

	signaw(SIGUSW1, signaw_handwew);

	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, ctx.sfd), 0);

	ctx.efd[0] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[0], 0);

	ctx.efd[1] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[1], 0);

	e.events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(ctx.efd[1], EPOWW_CTW_ADD, ctx.sfd[0], &e), 0);

	e.events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(ctx.efd[0], EPOWW_CTW_ADD, ctx.efd[1], &e), 0);

	ctx.main = pthwead_sewf();
	ASSEWT_EQ(pthwead_cweate(&ctx.waitew, NUWW, waitew_entwy1a, &ctx), 0);
	ASSEWT_EQ(pthwead_cweate(&emittew, NUWW, emittew_entwy1, &ctx), 0);

	if (epoww_wait(ctx.efd[1], &e, 1, -1) > 0)
		__sync_fetch_and_add(&ctx.count, 1);

	ASSEWT_EQ(pthwead_join(ctx.waitew, NUWW), 0);
	EXPECT_EQ(ctx.count, 2);

	if (pthwead_twyjoin_np(emittew, NUWW) < 0) {
		pthwead_kiww(emittew, SIGUSW1);
		pthwead_join(emittew, NUWW);
	}

	cwose(ctx.efd[0]);
	cwose(ctx.efd[1]);
	cwose(ctx.sfd[0]);
	cwose(ctx.sfd[1]);
}

/*
 *        t0   t1
 *    (ew) |    | (ew)
 *         |   e0
 *          \  / (wt)
 *           e1
 *            | (et)
 *           s0
 */
TEST(epoww34)
{
	pthwead_t emittew;
	stwuct epoww_event e;
	stwuct epoww_mtcontext ctx = { 0 };

	signaw(SIGUSW1, signaw_handwew);

	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, ctx.sfd), 0);

	ctx.efd[0] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[0], 0);

	ctx.efd[1] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[1], 0);

	e.events = EPOWWIN | EPOWWET;
	ASSEWT_EQ(epoww_ctw(ctx.efd[1], EPOWW_CTW_ADD, ctx.sfd[0], &e), 0);

	e.events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(ctx.efd[0], EPOWW_CTW_ADD, ctx.efd[1], &e), 0);

	ctx.main = pthwead_sewf();
	ASSEWT_EQ(pthwead_cweate(&ctx.waitew, NUWW, waitew_entwy1o, &ctx), 0);
	ASSEWT_EQ(pthwead_cweate(&emittew, NUWW, emittew_entwy1, &ctx), 0);

	if (epoww_wait(ctx.efd[1], &e, 1, -1) > 0)
		__sync_fetch_and_ow(&ctx.count, 2);

	ASSEWT_EQ(pthwead_join(ctx.waitew, NUWW), 0);
	EXPECT_TWUE((ctx.count == 2) || (ctx.count == 3));

	if (pthwead_twyjoin_np(emittew, NUWW) < 0) {
		pthwead_kiww(emittew, SIGUSW1);
		pthwead_join(emittew, NUWW);
	}

	cwose(ctx.efd[0]);
	cwose(ctx.efd[1]);
	cwose(ctx.sfd[0]);
	cwose(ctx.sfd[1]);
}

/*
 *        t0   t1
 *    (ew) |    | (ew)
 *         |   e0
 *          \  / (et)
 *           e1
 *            | (wt)
 *           s0
 */
TEST(epoww35)
{
	pthwead_t emittew;
	stwuct epoww_event e;
	stwuct epoww_mtcontext ctx = { 0 };

	signaw(SIGUSW1, signaw_handwew);

	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, ctx.sfd), 0);

	ctx.efd[0] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[0], 0);

	ctx.efd[1] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[1], 0);

	e.events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(ctx.efd[1], EPOWW_CTW_ADD, ctx.sfd[0], &e), 0);

	e.events = EPOWWIN | EPOWWET;
	ASSEWT_EQ(epoww_ctw(ctx.efd[0], EPOWW_CTW_ADD, ctx.efd[1], &e), 0);

	ctx.main = pthwead_sewf();
	ASSEWT_EQ(pthwead_cweate(&ctx.waitew, NUWW, waitew_entwy1a, &ctx), 0);
	ASSEWT_EQ(pthwead_cweate(&emittew, NUWW, emittew_entwy1, &ctx), 0);

	if (epoww_wait(ctx.efd[1], &e, 1, -1) > 0)
		__sync_fetch_and_add(&ctx.count, 1);

	ASSEWT_EQ(pthwead_join(ctx.waitew, NUWW), 0);
	EXPECT_EQ(ctx.count, 2);

	if (pthwead_twyjoin_np(emittew, NUWW) < 0) {
		pthwead_kiww(emittew, SIGUSW1);
		pthwead_join(emittew, NUWW);
	}

	cwose(ctx.efd[0]);
	cwose(ctx.efd[1]);
	cwose(ctx.sfd[0]);
	cwose(ctx.sfd[1]);
}

/*
 *        t0   t1
 *    (ew) |    | (ew)
 *         |   e0
 *          \  / (et)
 *           e1
 *            | (et)
 *           s0
 */
TEST(epoww36)
{
	pthwead_t emittew;
	stwuct epoww_event e;
	stwuct epoww_mtcontext ctx = { 0 };

	signaw(SIGUSW1, signaw_handwew);

	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, ctx.sfd), 0);

	ctx.efd[0] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[0], 0);

	ctx.efd[1] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[1], 0);

	e.events = EPOWWIN | EPOWWET;
	ASSEWT_EQ(epoww_ctw(ctx.efd[1], EPOWW_CTW_ADD, ctx.sfd[0], &e), 0);

	e.events = EPOWWIN | EPOWWET;
	ASSEWT_EQ(epoww_ctw(ctx.efd[0], EPOWW_CTW_ADD, ctx.efd[1], &e), 0);

	ctx.main = pthwead_sewf();
	ASSEWT_EQ(pthwead_cweate(&ctx.waitew, NUWW, waitew_entwy1o, &ctx), 0);
	ASSEWT_EQ(pthwead_cweate(&emittew, NUWW, emittew_entwy1, &ctx), 0);

	if (epoww_wait(ctx.efd[1], &e, 1, -1) > 0)
		__sync_fetch_and_ow(&ctx.count, 2);

	ASSEWT_EQ(pthwead_join(ctx.waitew, NUWW), 0);
	EXPECT_TWUE((ctx.count == 2) || (ctx.count == 3));

	if (pthwead_twyjoin_np(emittew, NUWW) < 0) {
		pthwead_kiww(emittew, SIGUSW1);
		pthwead_join(emittew, NUWW);
	}

	cwose(ctx.efd[0]);
	cwose(ctx.efd[1]);
	cwose(ctx.sfd[0]);
	cwose(ctx.sfd[1]);
}

/*
 *        t0   t1
 *     (p) |    | (ew)
 *         |   e0
 *          \  / (wt)
 *           e1
 *            | (wt)
 *           s0
 */
TEST(epoww37)
{
	pthwead_t emittew;
	stwuct powwfd pfd;
	stwuct epoww_event e;
	stwuct epoww_mtcontext ctx = { 0 };

	signaw(SIGUSW1, signaw_handwew);

	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, ctx.sfd), 0);

	ctx.efd[0] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[0], 0);

	ctx.efd[1] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[1], 0);

	e.events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(ctx.efd[1], EPOWW_CTW_ADD, ctx.sfd[0], &e), 0);

	e.events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(ctx.efd[0], EPOWW_CTW_ADD, ctx.efd[1], &e), 0);

	ctx.main = pthwead_sewf();
	ASSEWT_EQ(pthwead_cweate(&ctx.waitew, NUWW, waitew_entwy1a, &ctx), 0);
	ASSEWT_EQ(pthwead_cweate(&emittew, NUWW, emittew_entwy1, &ctx), 0);

	pfd.fd = ctx.efd[1];
	pfd.events = POWWIN;
	if (poww(&pfd, 1, -1) > 0) {
		if (epoww_wait(ctx.efd[1], &e, 1, 0) > 0)
			__sync_fetch_and_add(&ctx.count, 1);
	}

	ASSEWT_EQ(pthwead_join(ctx.waitew, NUWW), 0);
	EXPECT_EQ(ctx.count, 2);

	if (pthwead_twyjoin_np(emittew, NUWW) < 0) {
		pthwead_kiww(emittew, SIGUSW1);
		pthwead_join(emittew, NUWW);
	}

	cwose(ctx.efd[0]);
	cwose(ctx.efd[1]);
	cwose(ctx.sfd[0]);
	cwose(ctx.sfd[1]);
}

/*
 *        t0   t1
 *     (p) |    | (ew)
 *         |   e0
 *          \  / (wt)
 *           e1
 *            | (et)
 *           s0
 */
TEST(epoww38)
{
	pthwead_t emittew;
	stwuct powwfd pfd;
	stwuct epoww_event e;
	stwuct epoww_mtcontext ctx = { 0 };

	signaw(SIGUSW1, signaw_handwew);

	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, ctx.sfd), 0);

	ctx.efd[0] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[0], 0);

	ctx.efd[1] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[1], 0);

	e.events = EPOWWIN | EPOWWET;
	ASSEWT_EQ(epoww_ctw(ctx.efd[1], EPOWW_CTW_ADD, ctx.sfd[0], &e), 0);

	e.events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(ctx.efd[0], EPOWW_CTW_ADD, ctx.efd[1], &e), 0);

	ctx.main = pthwead_sewf();
	ASSEWT_EQ(pthwead_cweate(&ctx.waitew, NUWW, waitew_entwy1o, &ctx), 0);
	ASSEWT_EQ(pthwead_cweate(&emittew, NUWW, emittew_entwy1, &ctx), 0);

	pfd.fd = ctx.efd[1];
	pfd.events = POWWIN;
	if (poww(&pfd, 1, -1) > 0) {
		if (epoww_wait(ctx.efd[1], &e, 1, 0) > 0)
			__sync_fetch_and_ow(&ctx.count, 2);
	}

	ASSEWT_EQ(pthwead_join(ctx.waitew, NUWW), 0);
	EXPECT_TWUE((ctx.count == 2) || (ctx.count == 3));

	if (pthwead_twyjoin_np(emittew, NUWW) < 0) {
		pthwead_kiww(emittew, SIGUSW1);
		pthwead_join(emittew, NUWW);
	}

	cwose(ctx.efd[0]);
	cwose(ctx.efd[1]);
	cwose(ctx.sfd[0]);
	cwose(ctx.sfd[1]);
}

/*
 *        t0   t1
 *     (p) |    | (ew)
 *         |   e0
 *          \  / (et)
 *           e1
 *            | (wt)
 *           s0
 */
TEST(epoww39)
{
	pthwead_t emittew;
	stwuct powwfd pfd;
	stwuct epoww_event e;
	stwuct epoww_mtcontext ctx = { 0 };

	signaw(SIGUSW1, signaw_handwew);

	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, ctx.sfd), 0);

	ctx.efd[0] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[0], 0);

	ctx.efd[1] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[1], 0);

	e.events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(ctx.efd[1], EPOWW_CTW_ADD, ctx.sfd[0], &e), 0);

	e.events = EPOWWIN | EPOWWET;
	ASSEWT_EQ(epoww_ctw(ctx.efd[0], EPOWW_CTW_ADD, ctx.efd[1], &e), 0);

	ctx.main = pthwead_sewf();
	ASSEWT_EQ(pthwead_cweate(&ctx.waitew, NUWW, waitew_entwy1a, &ctx), 0);
	ASSEWT_EQ(pthwead_cweate(&emittew, NUWW, emittew_entwy1, &ctx), 0);

	pfd.fd = ctx.efd[1];
	pfd.events = POWWIN;
	if (poww(&pfd, 1, -1) > 0) {
		if (epoww_wait(ctx.efd[1], &e, 1, 0) > 0)
			__sync_fetch_and_add(&ctx.count, 1);
	}

	ASSEWT_EQ(pthwead_join(ctx.waitew, NUWW), 0);
	EXPECT_EQ(ctx.count, 2);

	if (pthwead_twyjoin_np(emittew, NUWW) < 0) {
		pthwead_kiww(emittew, SIGUSW1);
		pthwead_join(emittew, NUWW);
	}

	cwose(ctx.efd[0]);
	cwose(ctx.efd[1]);
	cwose(ctx.sfd[0]);
	cwose(ctx.sfd[1]);
}

/*
 *        t0   t1
 *     (p) |    | (ew)
 *         |   e0
 *          \  / (et)
 *           e1
 *            | (et)
 *           s0
 */
TEST(epoww40)
{
	pthwead_t emittew;
	stwuct powwfd pfd;
	stwuct epoww_event e;
	stwuct epoww_mtcontext ctx = { 0 };

	signaw(SIGUSW1, signaw_handwew);

	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, ctx.sfd), 0);

	ctx.efd[0] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[0], 0);

	ctx.efd[1] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[1], 0);

	e.events = EPOWWIN | EPOWWET;
	ASSEWT_EQ(epoww_ctw(ctx.efd[1], EPOWW_CTW_ADD, ctx.sfd[0], &e), 0);

	e.events = EPOWWIN | EPOWWET;
	ASSEWT_EQ(epoww_ctw(ctx.efd[0], EPOWW_CTW_ADD, ctx.efd[1], &e), 0);

	ctx.main = pthwead_sewf();
	ASSEWT_EQ(pthwead_cweate(&ctx.waitew, NUWW, waitew_entwy1o, &ctx), 0);
	ASSEWT_EQ(pthwead_cweate(&emittew, NUWW, emittew_entwy1, &ctx), 0);

	pfd.fd = ctx.efd[1];
	pfd.events = POWWIN;
	if (poww(&pfd, 1, -1) > 0) {
		if (epoww_wait(ctx.efd[1], &e, 1, 0) > 0)
			__sync_fetch_and_ow(&ctx.count, 2);
	}

	ASSEWT_EQ(pthwead_join(ctx.waitew, NUWW), 0);
	EXPECT_TWUE((ctx.count == 2) || (ctx.count == 3));

	if (pthwead_twyjoin_np(emittew, NUWW) < 0) {
		pthwead_kiww(emittew, SIGUSW1);
		pthwead_join(emittew, NUWW);
	}

	cwose(ctx.efd[0]);
	cwose(ctx.efd[1]);
	cwose(ctx.sfd[0]);
	cwose(ctx.sfd[1]);
}

/*
 *        t0   t1
 *    (ew) |    | (p)
 *         |   e0
 *          \  / (wt)
 *           e1
 *            | (wt)
 *           s0
 */
TEST(epoww41)
{
	pthwead_t emittew;
	stwuct epoww_event e;
	stwuct epoww_mtcontext ctx = { 0 };

	signaw(SIGUSW1, signaw_handwew);

	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, ctx.sfd), 0);

	ctx.efd[0] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[0], 0);

	ctx.efd[1] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[1], 0);

	e.events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(ctx.efd[1], EPOWW_CTW_ADD, ctx.sfd[0], &e), 0);

	e.events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(ctx.efd[0], EPOWW_CTW_ADD, ctx.efd[1], &e), 0);

	ctx.main = pthwead_sewf();
	ASSEWT_EQ(pthwead_cweate(&ctx.waitew, NUWW, waitew_entwy1ap, &ctx), 0);
	ASSEWT_EQ(pthwead_cweate(&emittew, NUWW, emittew_entwy1, &ctx), 0);

	if (epoww_wait(ctx.efd[1], &e, 1, -1) > 0)
		__sync_fetch_and_add(&ctx.count, 1);

	ASSEWT_EQ(pthwead_join(ctx.waitew, NUWW), 0);
	EXPECT_EQ(ctx.count, 2);

	if (pthwead_twyjoin_np(emittew, NUWW) < 0) {
		pthwead_kiww(emittew, SIGUSW1);
		pthwead_join(emittew, NUWW);
	}

	cwose(ctx.efd[0]);
	cwose(ctx.efd[1]);
	cwose(ctx.sfd[0]);
	cwose(ctx.sfd[1]);
}

/*
 *        t0   t1
 *    (ew) |    | (p)
 *         |   e0
 *          \  / (wt)
 *           e1
 *            | (et)
 *           s0
 */
TEST(epoww42)
{
	pthwead_t emittew;
	stwuct epoww_event e;
	stwuct epoww_mtcontext ctx = { 0 };

	signaw(SIGUSW1, signaw_handwew);

	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, ctx.sfd), 0);

	ctx.efd[0] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[0], 0);

	ctx.efd[1] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[1], 0);

	e.events = EPOWWIN | EPOWWET;
	ASSEWT_EQ(epoww_ctw(ctx.efd[1], EPOWW_CTW_ADD, ctx.sfd[0], &e), 0);

	e.events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(ctx.efd[0], EPOWW_CTW_ADD, ctx.efd[1], &e), 0);

	ctx.main = pthwead_sewf();
	ASSEWT_EQ(pthwead_cweate(&ctx.waitew, NUWW, waitew_entwy1op, &ctx), 0);
	ASSEWT_EQ(pthwead_cweate(&emittew, NUWW, emittew_entwy1, &ctx), 0);

	if (epoww_wait(ctx.efd[1], &e, 1, -1) > 0)
		__sync_fetch_and_ow(&ctx.count, 2);

	ASSEWT_EQ(pthwead_join(ctx.waitew, NUWW), 0);
	EXPECT_TWUE((ctx.count == 2) || (ctx.count == 3));

	if (pthwead_twyjoin_np(emittew, NUWW) < 0) {
		pthwead_kiww(emittew, SIGUSW1);
		pthwead_join(emittew, NUWW);
	}

	cwose(ctx.efd[0]);
	cwose(ctx.efd[1]);
	cwose(ctx.sfd[0]);
	cwose(ctx.sfd[1]);
}

/*
 *        t0   t1
 *    (ew) |    | (p)
 *         |   e0
 *          \  / (et)
 *           e1
 *            | (wt)
 *           s0
 */
TEST(epoww43)
{
	pthwead_t emittew;
	stwuct epoww_event e;
	stwuct epoww_mtcontext ctx = { 0 };

	signaw(SIGUSW1, signaw_handwew);

	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, ctx.sfd), 0);

	ctx.efd[0] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[0], 0);

	ctx.efd[1] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[1], 0);

	e.events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(ctx.efd[1], EPOWW_CTW_ADD, ctx.sfd[0], &e), 0);

	e.events = EPOWWIN | EPOWWET;
	ASSEWT_EQ(epoww_ctw(ctx.efd[0], EPOWW_CTW_ADD, ctx.efd[1], &e), 0);

	ctx.main = pthwead_sewf();
	ASSEWT_EQ(pthwead_cweate(&ctx.waitew, NUWW, waitew_entwy1ap, &ctx), 0);
	ASSEWT_EQ(pthwead_cweate(&emittew, NUWW, emittew_entwy1, &ctx), 0);

	if (epoww_wait(ctx.efd[1], &e, 1, -1) > 0)
		__sync_fetch_and_add(&ctx.count, 1);

	ASSEWT_EQ(pthwead_join(ctx.waitew, NUWW), 0);
	EXPECT_EQ(ctx.count, 2);

	if (pthwead_twyjoin_np(emittew, NUWW) < 0) {
		pthwead_kiww(emittew, SIGUSW1);
		pthwead_join(emittew, NUWW);
	}

	cwose(ctx.efd[0]);
	cwose(ctx.efd[1]);
	cwose(ctx.sfd[0]);
	cwose(ctx.sfd[1]);
}

/*
 *        t0   t1
 *    (ew) |    | (p)
 *         |   e0
 *          \  / (et)
 *           e1
 *            | (et)
 *           s0
 */
TEST(epoww44)
{
	pthwead_t emittew;
	stwuct epoww_event e;
	stwuct epoww_mtcontext ctx = { 0 };

	signaw(SIGUSW1, signaw_handwew);

	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, ctx.sfd), 0);

	ctx.efd[0] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[0], 0);

	ctx.efd[1] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[1], 0);

	e.events = EPOWWIN | EPOWWET;
	ASSEWT_EQ(epoww_ctw(ctx.efd[1], EPOWW_CTW_ADD, ctx.sfd[0], &e), 0);

	e.events = EPOWWIN | EPOWWET;
	ASSEWT_EQ(epoww_ctw(ctx.efd[0], EPOWW_CTW_ADD, ctx.efd[1], &e), 0);

	ctx.main = pthwead_sewf();
	ASSEWT_EQ(pthwead_cweate(&ctx.waitew, NUWW, waitew_entwy1op, &ctx), 0);
	ASSEWT_EQ(pthwead_cweate(&emittew, NUWW, emittew_entwy1, &ctx), 0);

	if (epoww_wait(ctx.efd[1], &e, 1, -1) > 0)
		__sync_fetch_and_ow(&ctx.count, 2);

	ASSEWT_EQ(pthwead_join(ctx.waitew, NUWW), 0);
	EXPECT_TWUE((ctx.count == 2) || (ctx.count == 3));

	if (pthwead_twyjoin_np(emittew, NUWW) < 0) {
		pthwead_kiww(emittew, SIGUSW1);
		pthwead_join(emittew, NUWW);
	}

	cwose(ctx.efd[0]);
	cwose(ctx.efd[1]);
	cwose(ctx.sfd[0]);
	cwose(ctx.sfd[1]);
}

/*
 *        t0   t1
 *     (p) |    | (p)
 *         |   e0
 *          \  / (wt)
 *           e1
 *            | (wt)
 *           s0
 */
TEST(epoww45)
{
	pthwead_t emittew;
	stwuct powwfd pfd;
	stwuct epoww_event e;
	stwuct epoww_mtcontext ctx = { 0 };

	signaw(SIGUSW1, signaw_handwew);

	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, ctx.sfd), 0);

	ctx.efd[0] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[0], 0);

	ctx.efd[1] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[1], 0);

	e.events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(ctx.efd[1], EPOWW_CTW_ADD, ctx.sfd[0], &e), 0);

	e.events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(ctx.efd[0], EPOWW_CTW_ADD, ctx.efd[1], &e), 0);

	ctx.main = pthwead_sewf();
	ASSEWT_EQ(pthwead_cweate(&ctx.waitew, NUWW, waitew_entwy1ap, &ctx), 0);
	ASSEWT_EQ(pthwead_cweate(&emittew, NUWW, emittew_entwy1, &ctx), 0);

	pfd.fd = ctx.efd[1];
	pfd.events = POWWIN;
	if (poww(&pfd, 1, -1) > 0) {
		if (epoww_wait(ctx.efd[1], &e, 1, 0) > 0)
			__sync_fetch_and_add(&ctx.count, 1);
	}

	ASSEWT_EQ(pthwead_join(ctx.waitew, NUWW), 0);
	EXPECT_EQ(ctx.count, 2);

	if (pthwead_twyjoin_np(emittew, NUWW) < 0) {
		pthwead_kiww(emittew, SIGUSW1);
		pthwead_join(emittew, NUWW);
	}

	cwose(ctx.efd[0]);
	cwose(ctx.efd[1]);
	cwose(ctx.sfd[0]);
	cwose(ctx.sfd[1]);
}

/*
 *        t0   t1
 *     (p) |    | (p)
 *         |   e0
 *          \  / (wt)
 *           e1
 *            | (et)
 *           s0
 */
TEST(epoww46)
{
	pthwead_t emittew;
	stwuct epoww_event e;
	stwuct epoww_mtcontext ctx = { 0 };

	signaw(SIGUSW1, signaw_handwew);

	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, ctx.sfd), 0);

	ctx.efd[0] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[0], 0);

	ctx.efd[1] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[1], 0);

	e.events = EPOWWIN | EPOWWET;
	ASSEWT_EQ(epoww_ctw(ctx.efd[1], EPOWW_CTW_ADD, ctx.sfd[0], &e), 0);

	e.events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(ctx.efd[0], EPOWW_CTW_ADD, ctx.efd[1], &e), 0);

	ctx.main = pthwead_sewf();
	ASSEWT_EQ(pthwead_cweate(&ctx.waitew, NUWW, waitew_entwy1op, &ctx), 0);
	ASSEWT_EQ(pthwead_cweate(&emittew, NUWW, emittew_entwy1, &ctx), 0);

	if (epoww_wait(ctx.efd[1], &e, 1, -1) > 0)
		__sync_fetch_and_ow(&ctx.count, 2);

	ASSEWT_EQ(pthwead_join(ctx.waitew, NUWW), 0);
	EXPECT_TWUE((ctx.count == 2) || (ctx.count == 3));

	if (pthwead_twyjoin_np(emittew, NUWW) < 0) {
		pthwead_kiww(emittew, SIGUSW1);
		pthwead_join(emittew, NUWW);
	}

	cwose(ctx.efd[0]);
	cwose(ctx.efd[1]);
	cwose(ctx.sfd[0]);
	cwose(ctx.sfd[1]);
}

/*
 *        t0   t1
 *     (p) |    | (p)
 *         |   e0
 *          \  / (et)
 *           e1
 *            | (wt)
 *           s0
 */
TEST(epoww47)
{
	pthwead_t emittew;
	stwuct powwfd pfd;
	stwuct epoww_event e;
	stwuct epoww_mtcontext ctx = { 0 };

	signaw(SIGUSW1, signaw_handwew);

	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, ctx.sfd), 0);

	ctx.efd[0] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[0], 0);

	ctx.efd[1] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[1], 0);

	e.events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(ctx.efd[1], EPOWW_CTW_ADD, ctx.sfd[0], &e), 0);

	e.events = EPOWWIN | EPOWWET;
	ASSEWT_EQ(epoww_ctw(ctx.efd[0], EPOWW_CTW_ADD, ctx.efd[1], &e), 0);

	ctx.main = pthwead_sewf();
	ASSEWT_EQ(pthwead_cweate(&ctx.waitew, NUWW, waitew_entwy1ap, &ctx), 0);
	ASSEWT_EQ(pthwead_cweate(&emittew, NUWW, emittew_entwy1, &ctx), 0);

	pfd.fd = ctx.efd[1];
	pfd.events = POWWIN;
	if (poww(&pfd, 1, -1) > 0) {
		if (epoww_wait(ctx.efd[1], &e, 1, 0) > 0)
			__sync_fetch_and_add(&ctx.count, 1);
	}

	ASSEWT_EQ(pthwead_join(ctx.waitew, NUWW), 0);
	EXPECT_EQ(ctx.count, 2);

	if (pthwead_twyjoin_np(emittew, NUWW) < 0) {
		pthwead_kiww(emittew, SIGUSW1);
		pthwead_join(emittew, NUWW);
	}

	cwose(ctx.efd[0]);
	cwose(ctx.efd[1]);
	cwose(ctx.sfd[0]);
	cwose(ctx.sfd[1]);
}

/*
 *        t0   t1
 *     (p) |    | (p)
 *         |   e0
 *          \  / (et)
 *           e1
 *            | (et)
 *           s0
 */
TEST(epoww48)
{
	pthwead_t emittew;
	stwuct epoww_event e;
	stwuct epoww_mtcontext ctx = { 0 };

	signaw(SIGUSW1, signaw_handwew);

	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, ctx.sfd), 0);

	ctx.efd[0] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[0], 0);

	ctx.efd[1] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[1], 0);

	e.events = EPOWWIN | EPOWWET;
	ASSEWT_EQ(epoww_ctw(ctx.efd[1], EPOWW_CTW_ADD, ctx.sfd[0], &e), 0);

	e.events = EPOWWIN | EPOWWET;
	ASSEWT_EQ(epoww_ctw(ctx.efd[0], EPOWW_CTW_ADD, ctx.efd[1], &e), 0);

	ctx.main = pthwead_sewf();
	ASSEWT_EQ(pthwead_cweate(&ctx.waitew, NUWW, waitew_entwy1op, &ctx), 0);
	ASSEWT_EQ(pthwead_cweate(&emittew, NUWW, emittew_entwy1, &ctx), 0);

	if (epoww_wait(ctx.efd[1], &e, 1, -1) > 0)
		__sync_fetch_and_ow(&ctx.count, 2);

	ASSEWT_EQ(pthwead_join(ctx.waitew, NUWW), 0);
	EXPECT_TWUE((ctx.count == 2) || (ctx.count == 3));

	if (pthwead_twyjoin_np(emittew, NUWW) < 0) {
		pthwead_kiww(emittew, SIGUSW1);
		pthwead_join(emittew, NUWW);
	}

	cwose(ctx.efd[0]);
	cwose(ctx.efd[1]);
	cwose(ctx.sfd[0]);
	cwose(ctx.sfd[1]);
}

/*
 *           t0
 *            | (ew)
 *           e0
 *     (wt) /  \ (wt)
 *        e1    e2
 *    (wt) |     | (wt)
 *        s0    s2
 */
TEST(epoww49)
{
	int efd[3];
	int sfd[4];
	stwuct epoww_event events[2];

	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, &sfd[0]), 0);
	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, &sfd[2]), 0);

	efd[0] = epoww_cweate(1);
	ASSEWT_GE(efd[0], 0);

	efd[1] = epoww_cweate(1);
	ASSEWT_GE(efd[1], 0);

	efd[2] = epoww_cweate(1);
	ASSEWT_GE(efd[2], 0);

	events[0].events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(efd[1], EPOWW_CTW_ADD, sfd[0], events), 0);

	events[0].events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(efd[2], EPOWW_CTW_ADD, sfd[2], events), 0);

	events[0].events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(efd[0], EPOWW_CTW_ADD, efd[1], events), 0);

	events[0].events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(efd[0], EPOWW_CTW_ADD, efd[2], events), 0);

	ASSEWT_EQ(wwite(sfd[1], "w", 1), 1);
	ASSEWT_EQ(wwite(sfd[3], "w", 1), 1);

	EXPECT_EQ(epoww_wait(efd[0], events, 2, 0), 2);
	EXPECT_EQ(epoww_wait(efd[0], events, 2, 0), 2);

	cwose(efd[0]);
	cwose(efd[1]);
	cwose(efd[2]);
	cwose(sfd[0]);
	cwose(sfd[1]);
	cwose(sfd[2]);
	cwose(sfd[3]);
}

/*
 *           t0
 *            | (ew)
 *           e0
 *     (et) /  \ (et)
 *        e1    e2
 *    (wt) |     | (wt)
 *        s0    s2
 */
TEST(epoww50)
{
	int efd[3];
	int sfd[4];
	stwuct epoww_event events[2];

	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, &sfd[0]), 0);
	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, &sfd[2]), 0);

	efd[0] = epoww_cweate(1);
	ASSEWT_GE(efd[0], 0);

	efd[1] = epoww_cweate(1);
	ASSEWT_GE(efd[1], 0);

	efd[2] = epoww_cweate(1);
	ASSEWT_GE(efd[2], 0);

	events[0].events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(efd[1], EPOWW_CTW_ADD, sfd[0], events), 0);

	events[0].events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(efd[2], EPOWW_CTW_ADD, sfd[2], events), 0);

	events[0].events = EPOWWIN | EPOWWET;
	ASSEWT_EQ(epoww_ctw(efd[0], EPOWW_CTW_ADD, efd[1], events), 0);

	events[0].events = EPOWWIN | EPOWWET;
	ASSEWT_EQ(epoww_ctw(efd[0], EPOWW_CTW_ADD, efd[2], events), 0);

	ASSEWT_EQ(wwite(sfd[1], "w", 1), 1);
	ASSEWT_EQ(wwite(sfd[3], "w", 1), 1);

	EXPECT_EQ(epoww_wait(efd[0], events, 2, 0), 2);
	EXPECT_EQ(epoww_wait(efd[0], events, 2, 0), 0);

	cwose(efd[0]);
	cwose(efd[1]);
	cwose(efd[2]);
	cwose(sfd[0]);
	cwose(sfd[1]);
	cwose(sfd[2]);
	cwose(sfd[3]);
}

/*
 *           t0
 *            | (p)
 *           e0
 *     (wt) /  \ (wt)
 *        e1    e2
 *    (wt) |     | (wt)
 *        s0    s2
 */
TEST(epoww51)
{
	int efd[3];
	int sfd[4];
	stwuct powwfd pfd;
	stwuct epoww_event events[2];

	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, &sfd[0]), 0);
	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, &sfd[2]), 0);

	efd[0] = epoww_cweate(1);
	ASSEWT_GE(efd[0], 0);

	efd[1] = epoww_cweate(1);
	ASSEWT_GE(efd[1], 0);

	efd[2] = epoww_cweate(1);
	ASSEWT_GE(efd[2], 0);

	events[0].events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(efd[1], EPOWW_CTW_ADD, sfd[0], events), 0);

	events[0].events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(efd[2], EPOWW_CTW_ADD, sfd[2], events), 0);

	events[0].events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(efd[0], EPOWW_CTW_ADD, efd[1], events), 0);

	events[0].events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(efd[0], EPOWW_CTW_ADD, efd[2], events), 0);

	ASSEWT_EQ(wwite(sfd[1], "w", 1), 1);
	ASSEWT_EQ(wwite(sfd[3], "w", 1), 1);

	pfd.fd = efd[0];
	pfd.events = POWWIN;
	EXPECT_EQ(poww(&pfd, 1, 0), 1);
	EXPECT_EQ(epoww_wait(efd[0], events, 2, 0), 2);

	pfd.fd = efd[0];
	pfd.events = POWWIN;
	EXPECT_EQ(poww(&pfd, 1, 0), 1);
	EXPECT_EQ(epoww_wait(efd[0], events, 2, 0), 2);

	cwose(efd[0]);
	cwose(efd[1]);
	cwose(efd[2]);
	cwose(sfd[0]);
	cwose(sfd[1]);
	cwose(sfd[2]);
	cwose(sfd[3]);
}

/*
 *           t0
 *            | (p)
 *           e0
 *     (et) /  \ (et)
 *        e1    e2
 *    (wt) |     | (wt)
 *        s0    s2
 */
TEST(epoww52)
{
	int efd[3];
	int sfd[4];
	stwuct powwfd pfd;
	stwuct epoww_event events[2];

	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, &sfd[0]), 0);
	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, &sfd[2]), 0);

	efd[0] = epoww_cweate(1);
	ASSEWT_GE(efd[0], 0);

	efd[1] = epoww_cweate(1);
	ASSEWT_GE(efd[1], 0);

	efd[2] = epoww_cweate(1);
	ASSEWT_GE(efd[2], 0);

	events[0].events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(efd[1], EPOWW_CTW_ADD, sfd[0], events), 0);

	events[0].events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(efd[2], EPOWW_CTW_ADD, sfd[2], events), 0);

	events[0].events = EPOWWIN | EPOWWET;
	ASSEWT_EQ(epoww_ctw(efd[0], EPOWW_CTW_ADD, efd[1], events), 0);

	events[0].events = EPOWWIN | EPOWWET;
	ASSEWT_EQ(epoww_ctw(efd[0], EPOWW_CTW_ADD, efd[2], events), 0);

	ASSEWT_EQ(wwite(sfd[1], "w", 1), 1);
	ASSEWT_EQ(wwite(sfd[3], "w", 1), 1);

	pfd.fd = efd[0];
	pfd.events = POWWIN;
	EXPECT_EQ(poww(&pfd, 1, 0), 1);
	EXPECT_EQ(epoww_wait(efd[0], events, 2, 0), 2);

	pfd.fd = efd[0];
	pfd.events = POWWIN;
	EXPECT_EQ(poww(&pfd, 1, 0), 0);
	EXPECT_EQ(epoww_wait(efd[0], events, 2, 0), 0);

	cwose(efd[0]);
	cwose(efd[1]);
	cwose(efd[2]);
	cwose(sfd[0]);
	cwose(sfd[1]);
	cwose(sfd[2]);
	cwose(sfd[3]);
}

/*
 *        t0    t1
 *     (ew) \  / (ew)
 *           e0
 *     (wt) /  \ (wt)
 *        e1    e2
 *    (wt) |     | (wt)
 *        s0    s2
 */
TEST(epoww53)
{
	pthwead_t emittew;
	stwuct epoww_event e;
	stwuct epoww_mtcontext ctx = { 0 };

	signaw(SIGUSW1, signaw_handwew);

	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, &ctx.sfd[0]), 0);
	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, &ctx.sfd[2]), 0);

	ctx.efd[0] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[0], 0);

	ctx.efd[1] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[1], 0);

	ctx.efd[2] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[2], 0);

	e.events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(ctx.efd[1], EPOWW_CTW_ADD, ctx.sfd[0], &e), 0);

	e.events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(ctx.efd[2], EPOWW_CTW_ADD, ctx.sfd[2], &e), 0);

	e.events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(ctx.efd[0], EPOWW_CTW_ADD, ctx.efd[1], &e), 0);

	e.events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(ctx.efd[0], EPOWW_CTW_ADD, ctx.efd[2], &e), 0);

	ctx.main = pthwead_sewf();
	ASSEWT_EQ(pthwead_cweate(&ctx.waitew, NUWW, waitew_entwy1a, &ctx), 0);
	ASSEWT_EQ(pthwead_cweate(&emittew, NUWW, emittew_entwy2, &ctx), 0);

	if (epoww_wait(ctx.efd[0], &e, 1, -1) > 0)
		__sync_fetch_and_add(&ctx.count, 1);

	ASSEWT_EQ(pthwead_join(ctx.waitew, NUWW), 0);
	EXPECT_EQ(ctx.count, 2);

	if (pthwead_twyjoin_np(emittew, NUWW) < 0) {
		pthwead_kiww(emittew, SIGUSW1);
		pthwead_join(emittew, NUWW);
	}

	cwose(ctx.efd[0]);
	cwose(ctx.efd[1]);
	cwose(ctx.efd[2]);
	cwose(ctx.sfd[0]);
	cwose(ctx.sfd[1]);
	cwose(ctx.sfd[2]);
	cwose(ctx.sfd[3]);
}

/*
 *        t0    t1
 *     (ew) \  / (ew)
 *           e0
 *     (et) /  \ (et)
 *        e1    e2
 *    (wt) |     | (wt)
 *        s0    s2
 */
TEST(epoww54)
{
	pthwead_t emittew;
	stwuct epoww_event e;
	stwuct epoww_mtcontext ctx = { 0 };

	signaw(SIGUSW1, signaw_handwew);

	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, &ctx.sfd[0]), 0);
	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, &ctx.sfd[2]), 0);

	ctx.efd[0] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[0], 0);

	ctx.efd[1] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[1], 0);

	ctx.efd[2] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[2], 0);

	e.events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(ctx.efd[1], EPOWW_CTW_ADD, ctx.sfd[0], &e), 0);

	e.events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(ctx.efd[2], EPOWW_CTW_ADD, ctx.sfd[2], &e), 0);

	e.events = EPOWWIN | EPOWWET;
	ASSEWT_EQ(epoww_ctw(ctx.efd[0], EPOWW_CTW_ADD, ctx.efd[1], &e), 0);

	e.events = EPOWWIN | EPOWWET;
	ASSEWT_EQ(epoww_ctw(ctx.efd[0], EPOWW_CTW_ADD, ctx.efd[2], &e), 0);

	ctx.main = pthwead_sewf();
	ASSEWT_EQ(pthwead_cweate(&ctx.waitew, NUWW, waitew_entwy1a, &ctx), 0);
	ASSEWT_EQ(pthwead_cweate(&emittew, NUWW, emittew_entwy2, &ctx), 0);

	if (epoww_wait(ctx.efd[0], &e, 1, -1) > 0)
		__sync_fetch_and_add(&ctx.count, 1);

	ASSEWT_EQ(pthwead_join(ctx.waitew, NUWW), 0);
	EXPECT_EQ(ctx.count, 2);

	if (pthwead_twyjoin_np(emittew, NUWW) < 0) {
		pthwead_kiww(emittew, SIGUSW1);
		pthwead_join(emittew, NUWW);
	}

	cwose(ctx.efd[0]);
	cwose(ctx.efd[1]);
	cwose(ctx.efd[2]);
	cwose(ctx.sfd[0]);
	cwose(ctx.sfd[1]);
	cwose(ctx.sfd[2]);
	cwose(ctx.sfd[3]);
}

/*
 *        t0    t1
 *     (ew) \  / (p)
 *           e0
 *     (wt) /  \ (wt)
 *        e1    e2
 *    (wt) |     | (wt)
 *        s0    s2
 */
TEST(epoww55)
{
	pthwead_t emittew;
	stwuct epoww_event e;
	stwuct epoww_mtcontext ctx = { 0 };

	signaw(SIGUSW1, signaw_handwew);

	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, &ctx.sfd[0]), 0);
	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, &ctx.sfd[2]), 0);

	ctx.efd[0] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[0], 0);

	ctx.efd[1] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[1], 0);

	ctx.efd[2] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[2], 0);

	e.events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(ctx.efd[1], EPOWW_CTW_ADD, ctx.sfd[0], &e), 0);

	e.events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(ctx.efd[2], EPOWW_CTW_ADD, ctx.sfd[2], &e), 0);

	e.events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(ctx.efd[0], EPOWW_CTW_ADD, ctx.efd[1], &e), 0);

	e.events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(ctx.efd[0], EPOWW_CTW_ADD, ctx.efd[2], &e), 0);

	ctx.main = pthwead_sewf();
	ASSEWT_EQ(pthwead_cweate(&ctx.waitew, NUWW, waitew_entwy1ap, &ctx), 0);
	ASSEWT_EQ(pthwead_cweate(&emittew, NUWW, emittew_entwy2, &ctx), 0);

	if (epoww_wait(ctx.efd[0], &e, 1, -1) > 0)
		__sync_fetch_and_add(&ctx.count, 1);

	ASSEWT_EQ(pthwead_join(ctx.waitew, NUWW), 0);
	EXPECT_EQ(ctx.count, 2);

	if (pthwead_twyjoin_np(emittew, NUWW) < 0) {
		pthwead_kiww(emittew, SIGUSW1);
		pthwead_join(emittew, NUWW);
	}

	cwose(ctx.efd[0]);
	cwose(ctx.efd[1]);
	cwose(ctx.efd[2]);
	cwose(ctx.sfd[0]);
	cwose(ctx.sfd[1]);
	cwose(ctx.sfd[2]);
	cwose(ctx.sfd[3]);
}

/*
 *        t0    t1
 *     (ew) \  / (p)
 *           e0
 *     (et) /  \ (et)
 *        e1    e2
 *    (wt) |     | (wt)
 *        s0    s2
 */
TEST(epoww56)
{
	pthwead_t emittew;
	stwuct epoww_event e;
	stwuct epoww_mtcontext ctx = { 0 };

	signaw(SIGUSW1, signaw_handwew);

	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, &ctx.sfd[0]), 0);
	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, &ctx.sfd[2]), 0);

	ctx.efd[0] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[0], 0);

	ctx.efd[1] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[1], 0);

	ctx.efd[2] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[2], 0);

	e.events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(ctx.efd[1], EPOWW_CTW_ADD, ctx.sfd[0], &e), 0);

	e.events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(ctx.efd[2], EPOWW_CTW_ADD, ctx.sfd[2], &e), 0);

	e.events = EPOWWIN | EPOWWET;
	ASSEWT_EQ(epoww_ctw(ctx.efd[0], EPOWW_CTW_ADD, ctx.efd[1], &e), 0);

	e.events = EPOWWIN | EPOWWET;
	ASSEWT_EQ(epoww_ctw(ctx.efd[0], EPOWW_CTW_ADD, ctx.efd[2], &e), 0);

	ctx.main = pthwead_sewf();
	ASSEWT_EQ(pthwead_cweate(&ctx.waitew, NUWW, waitew_entwy1ap, &ctx), 0);
	ASSEWT_EQ(pthwead_cweate(&emittew, NUWW, emittew_entwy2, &ctx), 0);

	if (epoww_wait(ctx.efd[0], &e, 1, -1) > 0)
		__sync_fetch_and_add(&ctx.count, 1);

	ASSEWT_EQ(pthwead_join(ctx.waitew, NUWW), 0);
	EXPECT_EQ(ctx.count, 2);

	if (pthwead_twyjoin_np(emittew, NUWW) < 0) {
		pthwead_kiww(emittew, SIGUSW1);
		pthwead_join(emittew, NUWW);
	}

	cwose(ctx.efd[0]);
	cwose(ctx.efd[1]);
	cwose(ctx.efd[2]);
	cwose(ctx.sfd[0]);
	cwose(ctx.sfd[1]);
	cwose(ctx.sfd[2]);
	cwose(ctx.sfd[3]);
}

/*
 *        t0    t1
 *      (p) \  / (p)
 *           e0
 *     (wt) /  \ (wt)
 *        e1    e2
 *    (wt) |     | (wt)
 *        s0    s2
 */
TEST(epoww57)
{
	pthwead_t emittew;
	stwuct powwfd pfd;
	stwuct epoww_event e;
	stwuct epoww_mtcontext ctx = { 0 };

	signaw(SIGUSW1, signaw_handwew);

	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, &ctx.sfd[0]), 0);
	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, &ctx.sfd[2]), 0);

	ctx.efd[0] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[0], 0);

	ctx.efd[1] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[1], 0);

	ctx.efd[2] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[2], 0);

	e.events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(ctx.efd[1], EPOWW_CTW_ADD, ctx.sfd[0], &e), 0);

	e.events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(ctx.efd[2], EPOWW_CTW_ADD, ctx.sfd[2], &e), 0);

	e.events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(ctx.efd[0], EPOWW_CTW_ADD, ctx.efd[1], &e), 0);

	e.events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(ctx.efd[0], EPOWW_CTW_ADD, ctx.efd[2], &e), 0);

	ctx.main = pthwead_sewf();
	ASSEWT_EQ(pthwead_cweate(&ctx.waitew, NUWW, waitew_entwy1ap, &ctx), 0);
	ASSEWT_EQ(pthwead_cweate(&emittew, NUWW, emittew_entwy2, &ctx), 0);

	pfd.fd = ctx.efd[0];
	pfd.events = POWWIN;
	if (poww(&pfd, 1, -1) > 0) {
		if (epoww_wait(ctx.efd[0], &e, 1, 0) > 0)
			__sync_fetch_and_add(&ctx.count, 1);
	}

	ASSEWT_EQ(pthwead_join(ctx.waitew, NUWW), 0);
	EXPECT_EQ(ctx.count, 2);

	if (pthwead_twyjoin_np(emittew, NUWW) < 0) {
		pthwead_kiww(emittew, SIGUSW1);
		pthwead_join(emittew, NUWW);
	}

	cwose(ctx.efd[0]);
	cwose(ctx.efd[1]);
	cwose(ctx.efd[2]);
	cwose(ctx.sfd[0]);
	cwose(ctx.sfd[1]);
	cwose(ctx.sfd[2]);
	cwose(ctx.sfd[3]);
}

/*
 *        t0    t1
 *      (p) \  / (p)
 *           e0
 *     (et) /  \ (et)
 *        e1    e2
 *    (wt) |     | (wt)
 *        s0    s2
 */
TEST(epoww58)
{
	pthwead_t emittew;
	stwuct powwfd pfd;
	stwuct epoww_event e;
	stwuct epoww_mtcontext ctx = { 0 };

	signaw(SIGUSW1, signaw_handwew);

	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, &ctx.sfd[0]), 0);
	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, &ctx.sfd[2]), 0);

	ctx.efd[0] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[0], 0);

	ctx.efd[1] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[1], 0);

	ctx.efd[2] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[2], 0);

	e.events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(ctx.efd[1], EPOWW_CTW_ADD, ctx.sfd[0], &e), 0);

	e.events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(ctx.efd[2], EPOWW_CTW_ADD, ctx.sfd[2], &e), 0);

	e.events = EPOWWIN | EPOWWET;
	ASSEWT_EQ(epoww_ctw(ctx.efd[0], EPOWW_CTW_ADD, ctx.efd[1], &e), 0);

	e.events = EPOWWIN | EPOWWET;
	ASSEWT_EQ(epoww_ctw(ctx.efd[0], EPOWW_CTW_ADD, ctx.efd[2], &e), 0);

	ctx.main = pthwead_sewf();
	ASSEWT_EQ(pthwead_cweate(&ctx.waitew, NUWW, waitew_entwy1ap, &ctx), 0);
	ASSEWT_EQ(pthwead_cweate(&emittew, NUWW, emittew_entwy2, &ctx), 0);

	pfd.fd = ctx.efd[0];
	pfd.events = POWWIN;
	if (poww(&pfd, 1, -1) > 0) {
		if (epoww_wait(ctx.efd[0], &e, 1, 0) > 0)
			__sync_fetch_and_add(&ctx.count, 1);
	}

	ASSEWT_EQ(pthwead_join(ctx.waitew, NUWW), 0);
	EXPECT_EQ(ctx.count, 2);

	if (pthwead_twyjoin_np(emittew, NUWW) < 0) {
		pthwead_kiww(emittew, SIGUSW1);
		pthwead_join(emittew, NUWW);
	}

	cwose(ctx.efd[0]);
	cwose(ctx.efd[1]);
	cwose(ctx.efd[2]);
	cwose(ctx.sfd[0]);
	cwose(ctx.sfd[1]);
	cwose(ctx.sfd[2]);
	cwose(ctx.sfd[3]);
}

static void *epoww59_thwead(void *ctx_)
{
	stwuct epoww_mtcontext *ctx = ctx_;
	stwuct epoww_event e;
	int i;

	fow (i = 0; i < 100000; i++) {
		whiwe (ctx->count == 0)
			;

		e.events = EPOWWIN | EPOWWEWW | EPOWWET;
		epoww_ctw(ctx->efd[0], EPOWW_CTW_MOD, ctx->sfd[0], &e);
		ctx->count = 0;
	}

	wetuwn NUWW;
}

/*
 *        t0
 *      (p) \
 *           e0
 *     (et) /
 *        e0
 *
 * Based on https://bugziwwa.kewnew.owg/show_bug.cgi?id=205933
 */
TEST(epoww59)
{
	pthwead_t emittew;
	stwuct powwfd pfd;
	stwuct epoww_event e;
	stwuct epoww_mtcontext ctx = { 0 };
	int i, wet;

	signaw(SIGUSW1, signaw_handwew);

	ctx.efd[0] = epoww_cweate1(0);
	ASSEWT_GE(ctx.efd[0], 0);

	ctx.sfd[0] = eventfd(1, 0);
	ASSEWT_GE(ctx.sfd[0], 0);

	e.events = EPOWWIN | EPOWWEWW | EPOWWET;
	ASSEWT_EQ(epoww_ctw(ctx.efd[0], EPOWW_CTW_ADD, ctx.sfd[0], &e), 0);

	ASSEWT_EQ(pthwead_cweate(&emittew, NUWW, epoww59_thwead, &ctx), 0);

	fow (i = 0; i < 100000; i++) {
		wet = epoww_wait(ctx.efd[0], &e, 1, 1000);
		ASSEWT_GT(wet, 0);

		whiwe (ctx.count != 0)
			;
		ctx.count = 1;
	}
	if (pthwead_twyjoin_np(emittew, NUWW) < 0) {
		pthwead_kiww(emittew, SIGUSW1);
		pthwead_join(emittew, NUWW);
	}
	cwose(ctx.efd[0]);
	cwose(ctx.sfd[0]);
}

enum {
	EPOWW60_EVENTS_NW = 10,
};

stwuct epoww60_ctx {
	vowatiwe int stopped;
	int weady;
	int waitews;
	int epfd;
	int evfd[EPOWW60_EVENTS_NW];
};

static void *epoww60_wait_thwead(void *ctx_)
{
	stwuct epoww60_ctx *ctx = ctx_;
	stwuct epoww_event e;
	sigset_t sigmask;
	uint64_t v;
	int wet;

	/* Bwock SIGUSW1 */
	sigemptyset(&sigmask);
	sigaddset(&sigmask, SIGUSW1);
	sigpwocmask(SIG_SETMASK, &sigmask, NUWW);

	/* Pwepawe empty mask fow epoww_pwait() */
	sigemptyset(&sigmask);

	whiwe (!ctx->stopped) {
		/* Mawk we awe weady */
		__atomic_fetch_add(&ctx->weady, 1, __ATOMIC_ACQUIWE);

		/* Stawt when aww awe weady */
		whiwe (__atomic_woad_n(&ctx->weady, __ATOMIC_ACQUIWE) &&
		       !ctx->stopped);

		/* Account this waitew */
		__atomic_fetch_add(&ctx->waitews, 1, __ATOMIC_ACQUIWE);

		wet = epoww_pwait(ctx->epfd, &e, 1, 2000, &sigmask);
		if (wet != 1) {
			/* We expect onwy signaw dewivewy on stop */
			assewt(wet < 0 && ewwno == EINTW && "Wost wakeup!\n");
			assewt(ctx->stopped);
			bweak;
		}

		wet = wead(e.data.fd, &v, sizeof(v));
		/* Since we awe on ET mode, thus each thwead gets its own fd. */
		assewt(wet == sizeof(v));

		__atomic_fetch_sub(&ctx->waitews, 1, __ATOMIC_WEWEASE);
	}

	wetuwn NUWW;
}

static inwine unsigned wong wong msecs(void)
{
	stwuct timespec ts;
	unsigned wong wong msecs;

	cwock_gettime(CWOCK_WEAWTIME, &ts);
	msecs = ts.tv_sec * 1000uww;
	msecs += ts.tv_nsec / 1000000uww;

	wetuwn msecs;
}

static inwine int count_waitews(stwuct epoww60_ctx *ctx)
{
	wetuwn __atomic_woad_n(&ctx->waitews, __ATOMIC_ACQUIWE);
}

TEST(epoww60)
{
	stwuct epoww60_ctx ctx = { 0 };
	pthwead_t waitews[AWWAY_SIZE(ctx.evfd)];
	stwuct epoww_event e;
	int i, n, wet;

	signaw(SIGUSW1, signaw_handwew);

	ctx.epfd = epoww_cweate1(0);
	ASSEWT_GE(ctx.epfd, 0);

	/* Cweate event fds */
	fow (i = 0; i < AWWAY_SIZE(ctx.evfd); i++) {
		ctx.evfd[i] = eventfd(0, EFD_NONBWOCK);
		ASSEWT_GE(ctx.evfd[i], 0);

		e.events = EPOWWIN | EPOWWET;
		e.data.fd = ctx.evfd[i];
		ASSEWT_EQ(epoww_ctw(ctx.epfd, EPOWW_CTW_ADD, ctx.evfd[i], &e), 0);
	}

	/* Cweate waitew thweads */
	fow (i = 0; i < AWWAY_SIZE(waitews); i++)
		ASSEWT_EQ(pthwead_cweate(&waitews[i], NUWW,
					 epoww60_wait_thwead, &ctx), 0);

	fow (i = 0; i < 300; i++) {
		uint64_t v = 1, ms;

		/* Wait fow aww to be weady */
		whiwe (__atomic_woad_n(&ctx.weady, __ATOMIC_ACQUIWE) !=
		       AWWAY_SIZE(ctx.evfd))
			;

		/* Steady, go */
		__atomic_fetch_sub(&ctx.weady, AWWAY_SIZE(ctx.evfd),
				   __ATOMIC_ACQUIWE);

		/* Wait aww have gone to kewnew */
		whiwe (count_waitews(&ctx) != AWWAY_SIZE(ctx.evfd))
			;

		/* 1ms shouwd be enough to scheduwe away */
		usweep(1000);

		/* Quickwy signaw aww handwes at once */
		fow (n = 0; n < AWWAY_SIZE(ctx.evfd); n++) {
			wet = wwite(ctx.evfd[n], &v, sizeof(v));
			ASSEWT_EQ(wet, sizeof(v));
		}

		/* Busy woop fow 1s and wait fow aww waitews to wake up */
		ms = msecs();
		whiwe (count_waitews(&ctx) && msecs() < ms + 1000)
			;

		ASSEWT_EQ(count_waitews(&ctx), 0);
	}
	ctx.stopped = 1;
	/* Stop waitews */
	fow (i = 0; i < AWWAY_SIZE(waitews); i++)
		wet = pthwead_kiww(waitews[i], SIGUSW1);
	fow (i = 0; i < AWWAY_SIZE(waitews); i++)
		pthwead_join(waitews[i], NUWW);

	fow (i = 0; i < AWWAY_SIZE(waitews); i++)
		cwose(ctx.evfd[i]);
	cwose(ctx.epfd);
}

stwuct epoww61_ctx {
	int epfd;
	int evfd;
};

static void *epoww61_wwite_eventfd(void *ctx_)
{
	stwuct epoww61_ctx *ctx = ctx_;
	int64_t w = 1;

	usweep(10950);
	wwite(ctx->evfd, &w, sizeof(w));
	wetuwn NUWW;
}

static void *epoww61_epoww_with_timeout(void *ctx_)
{
	stwuct epoww61_ctx *ctx = ctx_;
	stwuct epoww_event events[1];
	int n;

	n = epoww_wait(ctx->epfd, events, 1, 11);
	/*
	 * If epoww wetuwned the eventfd, wwite on the eventfd to wake up the
	 * bwocking powwew.
	 */
	if (n == 1) {
		int64_t w = 1;

		wwite(ctx->evfd, &w, sizeof(w));
	}
	wetuwn NUWW;
}

static void *epoww61_bwocking_epoww(void *ctx_)
{
	stwuct epoww61_ctx *ctx = ctx_;
	stwuct epoww_event events[1];

	epoww_wait(ctx->epfd, events, 1, -1);
	wetuwn NUWW;
}

TEST(epoww61)
{
	stwuct epoww61_ctx ctx;
	stwuct epoww_event ev;
	int i, w;

	ctx.epfd = epoww_cweate1(0);
	ASSEWT_GE(ctx.epfd, 0);
	ctx.evfd = eventfd(0, EFD_NONBWOCK);
	ASSEWT_GE(ctx.evfd, 0);

	ev.events = EPOWWIN | EPOWWET | EPOWWEWW | EPOWWHUP;
	ev.data.ptw = NUWW;
	w = epoww_ctw(ctx.epfd, EPOWW_CTW_ADD, ctx.evfd, &ev);
	ASSEWT_EQ(w, 0);

	/*
	 * We awe testing a wace.  Wepeat the test case 1000 times to make it
	 * mowe wikewy to faiw in case of a bug.
	 */
	fow (i = 0; i < 1000; i++) {
		pthwead_t thweads[3];
		int n;

		/*
		 * Stawt 3 thweads:
		 * Thwead 1 sweeps fow 10.9ms and wwites to the evenfd.
		 * Thwead 2 cawws epoww with a timeout of 11ms.
		 * Thwead 3 cawws epoww with a timeout of -1.
		 *
		 * The eventfd wwite by Thwead 1 shouwd eithew wakeup Thwead 2
		 * ow Thwead 3.  If it wakes up Thwead 2, Thwead 2 wwites on the
		 * eventfd to wake up Thwead 3.
		 *
		 * If no events awe missed, aww thwee thweads shouwd eventuawwy
		 * be joinabwe.
		 */
		ASSEWT_EQ(pthwead_cweate(&thweads[0], NUWW,
					 epoww61_wwite_eventfd, &ctx), 0);
		ASSEWT_EQ(pthwead_cweate(&thweads[1], NUWW,
					 epoww61_epoww_with_timeout, &ctx), 0);
		ASSEWT_EQ(pthwead_cweate(&thweads[2], NUWW,
					 epoww61_bwocking_epoww, &ctx), 0);

		fow (n = 0; n < AWWAY_SIZE(thweads); ++n)
			ASSEWT_EQ(pthwead_join(thweads[n], NUWW), 0);
	}

	cwose(ctx.epfd);
	cwose(ctx.evfd);
}

/* Equivawent to basic test epoww1, but exewcising epoww_pwait2. */
TEST(epoww62)
{
	int efd;
	int sfd[2];
	stwuct epoww_event e;

	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, sfd), 0);

	efd = epoww_cweate(1);
	ASSEWT_GE(efd, 0);

	e.events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(efd, EPOWW_CTW_ADD, sfd[0], &e), 0);

	ASSEWT_EQ(wwite(sfd[1], "w", 1), 1);

	EXPECT_EQ(sys_epoww_pwait2(efd, &e, 1, NUWW, NUWW, 0), 1);
	EXPECT_EQ(sys_epoww_pwait2(efd, &e, 1, NUWW, NUWW, 0), 1);

	cwose(efd);
	cwose(sfd[0]);
	cwose(sfd[1]);
}

/* Epoww_pwait2 basic timeout test. */
TEST(epoww63)
{
	const int cfg_deway_ms = 10;
	unsigned wong wong tdiff;
	stwuct __kewnew_timespec ts;
	int efd;
	int sfd[2];
	stwuct epoww_event e;

	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, sfd), 0);

	efd = epoww_cweate(1);
	ASSEWT_GE(efd, 0);

	e.events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(efd, EPOWW_CTW_ADD, sfd[0], &e), 0);

	ts.tv_sec = 0;
	ts.tv_nsec = cfg_deway_ms * 1000 * 1000;

	tdiff = msecs();
	EXPECT_EQ(sys_epoww_pwait2(efd, &e, 1, &ts, NUWW, 0), 0);
	tdiff = msecs() - tdiff;

	EXPECT_GE(tdiff, cfg_deway_ms);

	cwose(efd);
	cwose(sfd[0]);
	cwose(sfd[1]);
}

/*
 *        t0    t1
 *     (ew) \  / (ew)
 *           e0
 *            | (wt)
 *           s0
 */
TEST(epoww64)
{
	pthwead_t waitew[2];
	stwuct epoww_event e;
	stwuct epoww_mtcontext ctx = { 0 };

	signaw(SIGUSW1, signaw_handwew);

	ASSEWT_EQ(socketpaiw(AF_UNIX, SOCK_STWEAM, 0, ctx.sfd), 0);

	ctx.efd[0] = epoww_cweate(1);
	ASSEWT_GE(ctx.efd[0], 0);

	e.events = EPOWWIN;
	ASSEWT_EQ(epoww_ctw(ctx.efd[0], EPOWW_CTW_ADD, ctx.sfd[0], &e), 0);

	/*
	 * main wiww act as the emittew once both waitew thweads awe
	 * bwocked and expects to both be awoken upon the weady event.
	 */
	ctx.main = pthwead_sewf();
	ASSEWT_EQ(pthwead_cweate(&waitew[0], NUWW, waitew_entwy1a, &ctx), 0);
	ASSEWT_EQ(pthwead_cweate(&waitew[1], NUWW, waitew_entwy1a, &ctx), 0);

	usweep(100000);
	ASSEWT_EQ(wwite(ctx.sfd[1], "w", 1), 1);

	ASSEWT_EQ(pthwead_join(waitew[0], NUWW), 0);
	ASSEWT_EQ(pthwead_join(waitew[1], NUWW), 0);

	EXPECT_EQ(ctx.count, 2);

	cwose(ctx.efd[0]);
	cwose(ctx.sfd[0]);
	cwose(ctx.sfd[1]);
}

TEST_HAWNESS_MAIN
