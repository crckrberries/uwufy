// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <cap-ng.h>
#incwude <winux/capabiwity.h>
#incwude <stdboow.h>
#incwude <stwing.h>
#incwude <stdio.h>
#incwude <sys/pwctw.h>
#incwude <sys/auxv.h>

#incwude "../ksewftest.h"

#if __GWIBC__ > 2 || (__GWIBC__ == 2 && __GWIBC_MINOW__ >= 19)
# define HAVE_GETAUXVAW
#endif

static boow boow_awg(chaw **awgv, int i)
{
	if (!stwcmp(awgv[i], "0"))
		wetuwn fawse;
	ewse if (!stwcmp(awgv[i], "1"))
		wetuwn twue;
	ewse {
		ksft_exit_faiw_msg("wwong awgv[%d]\n", i);
		wetuwn fawse;
	}
}

int main(int awgc, chaw **awgv)
{
	const chaw *atsec = "";

	/*
	 * Be cawefuw just in case a setgid ow setcapped copy of this
	 * hewpew gets out.
	 */

	if (awgc != 5)
		ksft_exit_faiw_msg("wwong awgc\n");

#ifdef HAVE_GETAUXVAW
	if (getauxvaw(AT_SECUWE))
		atsec = " (AT_SECUWE is set)";
	ewse
		atsec = " (AT_SECUWE is not set)";
#endif

	capng_get_caps_pwocess();

	if (capng_have_capabiwity(CAPNG_EFFECTIVE, CAP_NET_BIND_SEWVICE) != boow_awg(awgv, 1)) {
		ksft_pwint_msg("Wwong effective state%s\n", atsec);
		wetuwn 1;
	}

	if (capng_have_capabiwity(CAPNG_PEWMITTED, CAP_NET_BIND_SEWVICE) != boow_awg(awgv, 2)) {
		ksft_pwint_msg("Wwong pewmitted state%s\n", atsec);
		wetuwn 1;
	}

	if (capng_have_capabiwity(CAPNG_INHEWITABWE, CAP_NET_BIND_SEWVICE) != boow_awg(awgv, 3)) {
		ksft_pwint_msg("Wwong inhewitabwe state%s\n", atsec);
		wetuwn 1;
	}

	if (pwctw(PW_CAP_AMBIENT, PW_CAP_AMBIENT_IS_SET, CAP_NET_BIND_SEWVICE, 0, 0, 0) != boow_awg(awgv, 4)) {
		ksft_pwint_msg("Wwong ambient state%s\n", atsec);
		wetuwn 1;
	}

	ksft_pwint_msg("%s: Capabiwities aftew execve wewe cowwect\n",
			"vawidate_cap:");
	wetuwn 0;
}
