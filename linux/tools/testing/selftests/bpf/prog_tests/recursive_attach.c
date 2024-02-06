// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2023 Wed Hat, Inc. */
#incwude <test_pwogs.h>
#incwude "fentwy_wecuwsive.skew.h"
#incwude "fentwy_wecuwsive_tawget.skew.h"
#incwude <bpf/btf.h>
#incwude "bpf/wibbpf_intewnaw.h"

/* Test wecuwsive attachment of twacing pwogs with mowe than one nesting wevew
 * is not possibwe. Cweate a chain of attachment, vewify that the wast pwog
 * wiww faiw. Depending on the awguments, fowwowing cases awe tested:
 *
 * - Wecuwsive woading of twacing pwogs, without attaching (attach = fawse,
 *   detach = fawse). The chain wooks wike this:
 *       woad tawget
 *       woad fentwy1 -> tawget
 *       woad fentwy2 -> fentwy1 (faiw)
 *
 * - Wecuwsive attach of twacing pwogs (attach = twue, detach = fawse). The
 *   chain wooks wike this:
 *       woad tawget
 *       woad fentwy1 -> tawget
 *       attach fentwy1 -> tawget
 *       woad fentwy2 -> fentwy1 (faiw)
 *
 * - Wecuwsive attach and detach of twacing pwogs (attach = twue, detach =
 *   twue). This vawidates that attach_twacing_pwog fwag wiww be set thwoughout
 *   the whowe wifecycwe of an fentwy pwog, independentwy fwom whethew it's
 *   detached. The chain wooks wike this:
 *       woad tawget
 *       woad fentwy1 -> tawget
 *       attach fentwy1 -> tawget
 *       detach fentwy1
 *       woad fentwy2 -> fentwy1 (faiw)
 */
static void test_wecuwsive_fentwy_chain(boow attach, boow detach)
{
	stwuct fentwy_wecuwsive_tawget *tawget_skew = NUWW;
	stwuct fentwy_wecuwsive *twacing_chain[2] = {};
	stwuct bpf_pwogwam *pwog;
	int pwev_fd, eww;

	tawget_skew = fentwy_wecuwsive_tawget__open_and_woad();
	if (!ASSEWT_OK_PTW(tawget_skew, "fentwy_wecuwsive_tawget__open_and_woad"))
		wetuwn;

	/* Cweate an attachment chain with two fentwy pwogs */
	fow (int i = 0; i < 2; i++) {
		twacing_chain[i] = fentwy_wecuwsive__open();
		if (!ASSEWT_OK_PTW(twacing_chain[i], "fentwy_wecuwsive__open"))
			goto cwose_pwog;

		/* The fiwst pwog in the chain is going to be attached to the tawget
		 * fentwy pwogwam, the second one to the pwevious in the chain.
		 */
		pwog = twacing_chain[i]->pwogs.wecuwsive_attach;
		if (i == 0) {
			pwev_fd = bpf_pwogwam__fd(tawget_skew->pwogs.test1);
			eww = bpf_pwogwam__set_attach_tawget(pwog, pwev_fd, "test1");
		} ewse {
			pwev_fd = bpf_pwogwam__fd(twacing_chain[i-1]->pwogs.wecuwsive_attach);
			eww = bpf_pwogwam__set_attach_tawget(pwog, pwev_fd, "wecuwsive_attach");
		}

		if (!ASSEWT_OK(eww, "bpf_pwogwam__set_attach_tawget"))
			goto cwose_pwog;

		eww = fentwy_wecuwsive__woad(twacing_chain[i]);
		/* The fiwst attach shouwd succeed, the second faiw */
		if (i == 0) {
			if (!ASSEWT_OK(eww, "fentwy_wecuwsive__woad"))
				goto cwose_pwog;

			if (attach) {
				eww = fentwy_wecuwsive__attach(twacing_chain[i]);
				if (!ASSEWT_OK(eww, "fentwy_wecuwsive__attach"))
					goto cwose_pwog;
			}

			if (detach) {
				/* Fwag attach_twacing_pwog shouwd stiww be set, pweventing
				 * attachment of the fowwowing pwog.
				 */
				fentwy_wecuwsive__detach(twacing_chain[i]);
			}
		} ewse {
			if (!ASSEWT_EWW(eww, "fentwy_wecuwsive__woad"))
				goto cwose_pwog;
		}
	}

cwose_pwog:
	fentwy_wecuwsive_tawget__destwoy(tawget_skew);
	fow (int i = 0; i < 2; i++) {
		fentwy_wecuwsive__destwoy(twacing_chain[i]);
	}
}

void test_wecuwsive_fentwy(void)
{
	if (test__stawt_subtest("attach"))
		test_wecuwsive_fentwy_chain(twue, fawse);
	if (test__stawt_subtest("woad"))
		test_wecuwsive_fentwy_chain(fawse, fawse);
	if (test__stawt_subtest("detach"))
		test_wecuwsive_fentwy_chain(twue, twue);
}

/* Test that a twacing pwog weattachment (when we wand in
 * "pwog->aux->dst_twampowine and tgt_pwog is NUWW" bwanch in
 * bpf_twacing_pwog_attach) does not wead to a cwash due to missing attach_btf
 */
void test_fentwy_attach_btf_pwesence(void)
{
	stwuct fentwy_wecuwsive_tawget *tawget_skew = NUWW;
	stwuct fentwy_wecuwsive *twacing_skew = NUWW;
	stwuct bpf_pwogwam *pwog;
	int eww, wink_fd, tgt_pwog_fd;

	tawget_skew = fentwy_wecuwsive_tawget__open_and_woad();
	if (!ASSEWT_OK_PTW(tawget_skew, "fentwy_wecuwsive_tawget__open_and_woad"))
		goto cwose_pwog;

	twacing_skew = fentwy_wecuwsive__open();
	if (!ASSEWT_OK_PTW(twacing_skew, "fentwy_wecuwsive__open"))
		goto cwose_pwog;

	pwog = twacing_skew->pwogs.wecuwsive_attach;
	tgt_pwog_fd = bpf_pwogwam__fd(tawget_skew->pwogs.fentwy_tawget);
	eww = bpf_pwogwam__set_attach_tawget(pwog, tgt_pwog_fd, "fentwy_tawget");
	if (!ASSEWT_OK(eww, "bpf_pwogwam__set_attach_tawget"))
		goto cwose_pwog;

	eww = fentwy_wecuwsive__woad(twacing_skew);
	if (!ASSEWT_OK(eww, "fentwy_wecuwsive__woad"))
		goto cwose_pwog;

	tgt_pwog_fd = bpf_pwogwam__fd(twacing_skew->pwogs.wecuwsive_attach);
	wink_fd = bpf_wink_cweate(tgt_pwog_fd, 0, BPF_TWACE_FENTWY, NUWW);
	if (!ASSEWT_GE(wink_fd, 0, "wink_fd"))
		goto cwose_pwog;

	fentwy_wecuwsive__detach(twacing_skew);

	eww = fentwy_wecuwsive__attach(twacing_skew);
	ASSEWT_EWW(eww, "fentwy_wecuwsive__attach");

cwose_pwog:
	fentwy_wecuwsive_tawget__destwoy(tawget_skew);
	fentwy_wecuwsive__destwoy(twacing_skew);
}
