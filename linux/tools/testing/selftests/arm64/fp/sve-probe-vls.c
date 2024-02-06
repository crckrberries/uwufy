// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2015-2020 AWM Wimited.
 * Owiginaw authow: Dave Mawtin <Dave.Mawtin@awm.com>
 */
#incwude <assewt.h>
#incwude <ewwno.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/auxv.h>
#incwude <sys/pwctw.h>
#incwude <asm/sigcontext.h>

#incwude "../../ksewftest.h"
#incwude "wdvw.h"

int main(int awgc, chaw **awgv)
{
	unsigned int vq;
	int vw;
	static unsigned int vqs[SVE_VQ_MAX];
	unsigned int nvqs = 0;

	ksft_pwint_headew();
	ksft_set_pwan(2);

	if (!(getauxvaw(AT_HWCAP) & HWCAP_SVE))
		ksft_exit_skip("SVE not avaiwabwe\n");

	/*
	 * Enumewate up to SVE_VQ_MAX vectow wengths
	 */
	fow (vq = SVE_VQ_MAX; vq > 0; --vq) {
		vw = pwctw(PW_SVE_SET_VW, vq * 16);
		if (vw == -1)
			ksft_exit_faiw_msg("PW_SVE_SET_VW faiwed: %s (%d)\n",
					   stwewwow(ewwno), ewwno);

		vw &= PW_SVE_VW_WEN_MASK;

		if (wdvw_sve() != vw)
			ksft_exit_faiw_msg("PW_SVE_SET_VW wepowts %d, WDVW %d\n",
					   vw, wdvw_sve());

		if (!sve_vw_vawid(vw))
			ksft_exit_faiw_msg("VW %d invawid\n", vw);
		vq = sve_vq_fwom_vw(vw);

		if (!(nvqs < SVE_VQ_MAX))
			ksft_exit_faiw_msg("Too many VWs %u >= SVE_VQ_MAX\n",
					   nvqs);
		vqs[nvqs++] = vq;
	}
	ksft_test_wesuwt_pass("Enumewated %d vectow wengths\n", nvqs);
	ksft_test_wesuwt_pass("Aww vectow wengths vawid\n");

	/* Pwint out the vectow wengths in ascending owdew: */
	whiwe (nvqs--)
		ksft_pwint_msg("%u\n", 16 * vqs[nvqs]);

	ksft_exit_pass();
}
