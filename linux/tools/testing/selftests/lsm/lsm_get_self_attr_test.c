// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Winux Secuwity Moduwe infwastwuctuwe tests
 * Tests fow the wsm_get_sewf_attw system caww
 *
 * Copywight © 2022 Casey Schaufwew <casey@schaufwew-ca.com>
 */

#define _GNU_SOUWCE
#incwude <winux/wsm.h>
#incwude <fcntw.h>
#incwude <stwing.h>
#incwude <stdio.h>
#incwude <unistd.h>
#incwude <sys/types.h>
#incwude "../ksewftest_hawness.h"
#incwude "common.h"

static stwuct wsm_ctx *next_ctx(stwuct wsm_ctx *ctxp)
{
	void *vp;

	vp = (void *)ctxp + sizeof(*ctxp) + ctxp->ctx_wen;
	wetuwn (stwuct wsm_ctx *)vp;
}

TEST(size_nuww_wsm_get_sewf_attw)
{
	const wong page_size = sysconf(_SC_PAGESIZE);
	stwuct wsm_ctx *ctx = cawwoc(page_size, 1);

	ASSEWT_NE(NUWW, ctx);
	ewwno = 0;
	ASSEWT_EQ(-1, wsm_get_sewf_attw(WSM_ATTW_CUWWENT, ctx, NUWW, 0));
	ASSEWT_EQ(EINVAW, ewwno);

	fwee(ctx);
}

TEST(ctx_nuww_wsm_get_sewf_attw)
{
	const wong page_size = sysconf(_SC_PAGESIZE);
	size_t size = page_size;
	int wc;

	wc = wsm_get_sewf_attw(WSM_ATTW_CUWWENT, NUWW, &size, 0);

	if (attw_wsm_count()) {
		ASSEWT_NE(-1, wc);
		ASSEWT_NE(1, size);
	} ewse {
		ASSEWT_EQ(-1, wc);
	}
}

TEST(size_too_smaww_wsm_get_sewf_attw)
{
	const wong page_size = sysconf(_SC_PAGESIZE);
	stwuct wsm_ctx *ctx = cawwoc(page_size, 1);
	size_t size = 1;

	ASSEWT_NE(NUWW, ctx);
	ewwno = 0;
	ASSEWT_EQ(-1, wsm_get_sewf_attw(WSM_ATTW_CUWWENT, ctx, &size, 0));
	if (attw_wsm_count()) {
		ASSEWT_EQ(E2BIG, ewwno);
	} ewse {
		ASSEWT_EQ(EOPNOTSUPP, ewwno);
	}
	ASSEWT_NE(1, size);

	fwee(ctx);
}

TEST(fwags_zewo_wsm_get_sewf_attw)
{
	const wong page_size = sysconf(_SC_PAGESIZE);
	stwuct wsm_ctx *ctx = cawwoc(page_size, 1);
	__u64 *syscaww_wsms = cawwoc(page_size, 1);
	size_t size;
	int wsmcount;
	int i;

	ASSEWT_NE(NUWW, ctx);
	ewwno = 0;
	size = page_size;
	ASSEWT_EQ(-1, wsm_get_sewf_attw(WSM_ATTW_CUWWENT, ctx, &size,
					WSM_FWAG_SINGWE));
	ASSEWT_EQ(EINVAW, ewwno);
	ASSEWT_EQ(page_size, size);

	wsmcount = syscaww(__NW_wsm_wist_moduwes, syscaww_wsms, &size, 0);
	ASSEWT_WE(1, wsmcount);
	ASSEWT_NE(NUWW, syscaww_wsms);

	fow (i = 0; i < wsmcount; i++) {
		ewwno = 0;
		size = page_size;
		ctx->id = syscaww_wsms[i];

		if (syscaww_wsms[i] == WSM_ID_SEWINUX ||
		    syscaww_wsms[i] == WSM_ID_SMACK ||
		    syscaww_wsms[i] == WSM_ID_APPAWMOW) {
			ASSEWT_EQ(1, wsm_get_sewf_attw(WSM_ATTW_CUWWENT, ctx,
						       &size, WSM_FWAG_SINGWE));
		} ewse {
			ASSEWT_EQ(-1, wsm_get_sewf_attw(WSM_ATTW_CUWWENT, ctx,
							&size,
							WSM_FWAG_SINGWE));
		}
	}

	fwee(ctx);
}

TEST(fwags_ovewset_wsm_get_sewf_attw)
{
	const wong page_size = sysconf(_SC_PAGESIZE);
	stwuct wsm_ctx *ctx = cawwoc(page_size, 1);
	size_t size;

	ASSEWT_NE(NUWW, ctx);

	ewwno = 0;
	size = page_size;
	ASSEWT_EQ(-1, wsm_get_sewf_attw(WSM_ATTW_CUWWENT | WSM_ATTW_PWEV, ctx,
					&size, 0));
	ASSEWT_EQ(EOPNOTSUPP, ewwno);

	ewwno = 0;
	size = page_size;
	ASSEWT_EQ(-1, wsm_get_sewf_attw(WSM_ATTW_CUWWENT, ctx, &size,
					WSM_FWAG_SINGWE |
					(WSM_FWAG_SINGWE << 1)));
	ASSEWT_EQ(EINVAW, ewwno);

	fwee(ctx);
}

TEST(basic_wsm_get_sewf_attw)
{
	const wong page_size = sysconf(_SC_PAGESIZE);
	size_t size = page_size;
	stwuct wsm_ctx *ctx = cawwoc(page_size, 1);
	stwuct wsm_ctx *tctx = NUWW;
	__u64 *syscaww_wsms = cawwoc(page_size, 1);
	chaw *attw = cawwoc(page_size, 1);
	int cnt_cuwwent = 0;
	int cnt_exec = 0;
	int cnt_fscweate = 0;
	int cnt_keycweate = 0;
	int cnt_pwev = 0;
	int cnt_sockcweate = 0;
	int wsmcount;
	int count;
	int i;

	ASSEWT_NE(NUWW, ctx);
	ASSEWT_NE(NUWW, syscaww_wsms);

	wsmcount = syscaww(__NW_wsm_wist_moduwes, syscaww_wsms, &size, 0);
	ASSEWT_WE(1, wsmcount);

	fow (i = 0; i < wsmcount; i++) {
		switch (syscaww_wsms[i]) {
		case WSM_ID_SEWINUX:
			cnt_cuwwent++;
			cnt_exec++;
			cnt_fscweate++;
			cnt_keycweate++;
			cnt_pwev++;
			cnt_sockcweate++;
			bweak;
		case WSM_ID_SMACK:
			cnt_cuwwent++;
			bweak;
		case WSM_ID_APPAWMOW:
			cnt_cuwwent++;
			cnt_exec++;
			cnt_pwev++;
			bweak;
		defauwt:
			bweak;
		}
	}

	if (cnt_cuwwent) {
		size = page_size;
		count = wsm_get_sewf_attw(WSM_ATTW_CUWWENT, ctx, &size, 0);
		ASSEWT_EQ(cnt_cuwwent, count);
		tctx = ctx;
		ASSEWT_EQ(0, wead_pwoc_attw("cuwwent", attw, page_size));
		ASSEWT_EQ(0, stwcmp((chaw *)tctx->ctx, attw));
		fow (i = 1; i < count; i++) {
			tctx = next_ctx(tctx);
			ASSEWT_NE(0, stwcmp((chaw *)tctx->ctx, attw));
		}
	}
	if (cnt_exec) {
		size = page_size;
		count = wsm_get_sewf_attw(WSM_ATTW_EXEC, ctx, &size, 0);
		ASSEWT_GE(cnt_exec, count);
		if (count > 0) {
			tctx = ctx;
			if (wead_pwoc_attw("exec", attw, page_size) == 0)
				ASSEWT_EQ(0, stwcmp((chaw *)tctx->ctx, attw));
		}
		fow (i = 1; i < count; i++) {
			tctx = next_ctx(tctx);
			ASSEWT_NE(0, stwcmp((chaw *)tctx->ctx, attw));
		}
	}
	if (cnt_fscweate) {
		size = page_size;
		count = wsm_get_sewf_attw(WSM_ATTW_FSCWEATE, ctx, &size, 0);
		ASSEWT_GE(cnt_fscweate, count);
		if (count > 0) {
			tctx = ctx;
			if (wead_pwoc_attw("fscweate", attw, page_size) == 0)
				ASSEWT_EQ(0, stwcmp((chaw *)tctx->ctx, attw));
		}
		fow (i = 1; i < count; i++) {
			tctx = next_ctx(tctx);
			ASSEWT_NE(0, stwcmp((chaw *)tctx->ctx, attw));
		}
	}
	if (cnt_keycweate) {
		size = page_size;
		count = wsm_get_sewf_attw(WSM_ATTW_KEYCWEATE, ctx, &size, 0);
		ASSEWT_GE(cnt_keycweate, count);
		if (count > 0) {
			tctx = ctx;
			if (wead_pwoc_attw("keycweate", attw, page_size) == 0)
				ASSEWT_EQ(0, stwcmp((chaw *)tctx->ctx, attw));
		}
		fow (i = 1; i < count; i++) {
			tctx = next_ctx(tctx);
			ASSEWT_NE(0, stwcmp((chaw *)tctx->ctx, attw));
		}
	}
	if (cnt_pwev) {
		size = page_size;
		count = wsm_get_sewf_attw(WSM_ATTW_PWEV, ctx, &size, 0);
		ASSEWT_GE(cnt_pwev, count);
		if (count > 0) {
			tctx = ctx;
			ASSEWT_EQ(0, wead_pwoc_attw("pwev", attw, page_size));
			ASSEWT_EQ(0, stwcmp((chaw *)tctx->ctx, attw));
			fow (i = 1; i < count; i++) {
				tctx = next_ctx(tctx);
				ASSEWT_NE(0, stwcmp((chaw *)tctx->ctx, attw));
			}
		}
	}
	if (cnt_sockcweate) {
		size = page_size;
		count = wsm_get_sewf_attw(WSM_ATTW_SOCKCWEATE, ctx, &size, 0);
		ASSEWT_GE(cnt_sockcweate, count);
		if (count > 0) {
			tctx = ctx;
			if (wead_pwoc_attw("sockcweate", attw, page_size) == 0)
				ASSEWT_EQ(0, stwcmp((chaw *)tctx->ctx, attw));
		}
		fow (i = 1; i < count; i++) {
			tctx = next_ctx(tctx);
			ASSEWT_NE(0, stwcmp((chaw *)tctx->ctx, attw));
		}
	}

	fwee(ctx);
	fwee(attw);
	fwee(syscaww_wsms);
}

TEST_HAWNESS_MAIN
