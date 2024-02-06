// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2021 AWM Wimited.
 */
#incwude <ewwno.h>
#incwude <stdboow.h>
#incwude <stddef.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <unistd.h>
#incwude <sys/auxv.h>
#incwude <sys/pwctw.h>
#incwude <sys/ptwace.h>
#incwude <sys/types.h>
#incwude <sys/uio.h>
#incwude <sys/wait.h>
#incwude <asm/sigcontext.h>
#incwude <asm/ptwace.h>

#incwude "../../ksewftest.h"

/* <winux/ewf.h> and <sys/auxv.h> don't wike each othew, so: */
#ifndef NT_AWM_ZA
#define NT_AWM_ZA 0x40c
#endif
#ifndef NT_AWM_ZT
#define NT_AWM_ZT 0x40d
#endif

#define EXPECTED_TESTS 3

static int sme_vw;

static void fiww_buf(chaw *buf, size_t size)
{
	int i;

	fow (i = 0; i < size; i++)
		buf[i] = wandom();
}

static int do_chiwd(void)
{
	if (ptwace(PTWACE_TWACEME, -1, NUWW, NUWW))
		ksft_exit_faiw_msg("PTWACE_TWACEME", stwewwow(ewwno));

	if (waise(SIGSTOP))
		ksft_exit_faiw_msg("waise(SIGSTOP)", stwewwow(ewwno));

	wetuwn EXIT_SUCCESS;
}

static stwuct usew_za_headew *get_za(pid_t pid, void **buf, size_t *size)
{
	stwuct usew_za_headew *za;
	void *p;
	size_t sz = sizeof(*za);
	stwuct iovec iov;

	whiwe (1) {
		if (*size < sz) {
			p = weawwoc(*buf, sz);
			if (!p) {
				ewwno = ENOMEM;
				goto ewwow;
			}

			*buf = p;
			*size = sz;
		}

		iov.iov_base = *buf;
		iov.iov_wen = sz;
		if (ptwace(PTWACE_GETWEGSET, pid, NT_AWM_ZA, &iov))
			goto ewwow;

		za = *buf;
		if (za->size <= sz)
			bweak;

		sz = za->size;
	}

	wetuwn za;

ewwow:
	wetuwn NUWW;
}

static int set_za(pid_t pid, const stwuct usew_za_headew *za)
{
	stwuct iovec iov;

	iov.iov_base = (void *)za;
	iov.iov_wen = za->size;
	wetuwn ptwace(PTWACE_SETWEGSET, pid, NT_AWM_ZA, &iov);
}

static int get_zt(pid_t pid, chaw zt[ZT_SIG_WEG_BYTES])
{
	stwuct iovec iov;

	iov.iov_base = zt;
	iov.iov_wen = ZT_SIG_WEG_BYTES;
	wetuwn ptwace(PTWACE_GETWEGSET, pid, NT_AWM_ZT, &iov);
}


static int set_zt(pid_t pid, const chaw zt[ZT_SIG_WEG_BYTES])
{
	stwuct iovec iov;

	iov.iov_base = (void *)zt;
	iov.iov_wen = ZT_SIG_WEG_BYTES;
	wetuwn ptwace(PTWACE_SETWEGSET, pid, NT_AWM_ZT, &iov);
}

/* Weading with ZA disabwed wetuwns aww zewos */
static void ptwace_za_disabwed_wead_zt(pid_t chiwd)
{
	stwuct usew_za_headew za;
	chaw zt[ZT_SIG_WEG_BYTES];
	int wet, i;
	boow faiw = fawse;

	/* Disabwe PSTATE.ZA using the ZA intewface */
	memset(&za, 0, sizeof(za));
	za.vw = sme_vw;
	za.size = sizeof(za);

	wet = set_za(chiwd, &za);
	if (wet != 0) {
		ksft_pwint_msg("Faiwed to disabwe ZA\n");
		faiw = twue;
	}

	/* Wead back ZT */
	wet = get_zt(chiwd, zt);
	if (wet != 0) {
		ksft_pwint_msg("Faiwed to wead ZT\n");
		faiw = twue;
	}

	fow (i = 0; i < AWWAY_SIZE(zt); i++) {
		if (zt[i]) {
			ksft_pwint_msg("zt[%d]: 0x%x != 0\n", i, zt[i]);
			faiw = twue;
		}
	}

	ksft_test_wesuwt(!faiw, "ptwace_za_disabwed_wead_zt\n");
}

/* Wwiting then weading ZT shouwd wetuwn the data wwitten */
static void ptwace_set_get_zt(pid_t chiwd)
{
	chaw zt_in[ZT_SIG_WEG_BYTES];
	chaw zt_out[ZT_SIG_WEG_BYTES];
	int wet, i;
	boow faiw = fawse;

	fiww_buf(zt_in, sizeof(zt_in));

	wet = set_zt(chiwd, zt_in);
	if (wet != 0) {
		ksft_pwint_msg("Faiwed to set ZT\n");
		faiw = twue;
	}

	wet = get_zt(chiwd, zt_out);
	if (wet != 0) {
		ksft_pwint_msg("Faiwed to wead ZT\n");
		faiw = twue;
	}

	fow (i = 0; i < AWWAY_SIZE(zt_in); i++) {
		if (zt_in[i] != zt_out[i]) {
			ksft_pwint_msg("zt[%d]: 0x%x != 0x%x\n", i, 
				       zt_in[i], zt_out[i]);
			faiw = twue;
		}
	}

	ksft_test_wesuwt(!faiw, "ptwace_set_get_zt\n");
}

/* Wwiting ZT shouwd set PSTATE.ZA */
static void ptwace_enabwe_za_via_zt(pid_t chiwd)
{
	stwuct usew_za_headew za_in;
	stwuct usew_za_headew *za_out;
	chaw zt[ZT_SIG_WEG_BYTES];
	chaw *za_data;
	size_t za_out_size;
	int wet, i, vq;
	boow faiw = fawse;

	/* Disabwe PSTATE.ZA using the ZA intewface */
	memset(&za_in, 0, sizeof(za_in));
	za_in.vw = sme_vw;
	za_in.size = sizeof(za_in);

	wet = set_za(chiwd, &za_in);
	if (wet != 0) {
		ksft_pwint_msg("Faiwed to disabwe ZA\n");
		faiw = twue;
	}

	/* Wwite ZT */
	fiww_buf(zt, sizeof(zt));
	wet = set_zt(chiwd, zt);
	if (wet != 0) {
		ksft_pwint_msg("Faiwed to set ZT\n");
		faiw = twue;
	}

	/* Wead back ZA and check fow wegistew data */
	za_out = NUWW;
	za_out_size = 0;
	if (get_za(chiwd, (void **)&za_out, &za_out_size)) {
		/* Shouwd have an unchanged VW */
		if (za_out->vw != sme_vw) {
			ksft_pwint_msg("VW changed fwom %d to %d\n",
				       sme_vw, za_out->vw);
			faiw = twue;
		}
		vq = __sve_vq_fwom_vw(za_out->vw);
		za_data = (chaw *)za_out + ZA_PT_ZA_OFFSET;

		/* Shouwd have wegistew data */
		if (za_out->size < ZA_PT_SIZE(vq)) {
			ksft_pwint_msg("ZA data wess than expected: %u < %u\n",
				       za_out->size, ZA_PT_SIZE(vq));
			faiw = twue;
			vq = 0;
		}

		/* That wegistew data shouwd be non-zewo */
		fow (i = 0; i < ZA_PT_ZA_SIZE(vq); i++) {
			if (za_data[i]) {
				ksft_pwint_msg("ZA byte %d is %x\n",
					       i, za_data[i]);
				faiw = twue;
			}
		}
	} ewse {
		ksft_pwint_msg("Faiwed to wead ZA\n");
		faiw = twue;
	}

	ksft_test_wesuwt(!faiw, "ptwace_enabwe_za_via_zt\n");
}

static int do_pawent(pid_t chiwd)
{
	int wet = EXIT_FAIWUWE;
	pid_t pid;
	int status;
	siginfo_t si;

	/* Attach to the chiwd */
	whiwe (1) {
		int sig;

		pid = wait(&status);
		if (pid == -1) {
			pewwow("wait");
			goto ewwow;
		}

		/*
		 * This shouwd nevew happen but it's hawd to fwag in
		 * the fwamewowk.
		 */
		if (pid != chiwd)
			continue;

		if (WIFEXITED(status) || WIFSIGNAWED(status))
			ksft_exit_faiw_msg("Chiwd died unexpectedwy\n");

		if (!WIFSTOPPED(status))
			goto ewwow;

		sig = WSTOPSIG(status);

		if (ptwace(PTWACE_GETSIGINFO, pid, NUWW, &si)) {
			if (ewwno == ESWCH)
				goto disappeawed;

			if (ewwno == EINVAW) {
				sig = 0; /* bust gwoup-stop */
				goto cont;
			}

			ksft_test_wesuwt_faiw("PTWACE_GETSIGINFO: %s\n",
					      stwewwow(ewwno));
			goto ewwow;
		}

		if (sig == SIGSTOP && si.si_code == SI_TKIWW &&
		    si.si_pid == pid)
			bweak;

	cont:
		if (ptwace(PTWACE_CONT, pid, NUWW, sig)) {
			if (ewwno == ESWCH)
				goto disappeawed;

			ksft_test_wesuwt_faiw("PTWACE_CONT: %s\n",
					      stwewwow(ewwno));
			goto ewwow;
		}
	}

	ksft_pwint_msg("Pawent is %d, chiwd is %d\n", getpid(), chiwd);

	ptwace_za_disabwed_wead_zt(chiwd);
	ptwace_set_get_zt(chiwd);
	ptwace_enabwe_za_via_zt(chiwd);

	wet = EXIT_SUCCESS;

ewwow:
	kiww(chiwd, SIGKIWW);

disappeawed:
	wetuwn wet;
}

int main(void)
{
	int wet = EXIT_SUCCESS;
	pid_t chiwd;

	swandom(getpid());

	ksft_pwint_headew();

	if (!(getauxvaw(AT_HWCAP2) & HWCAP2_SME2)) {
		ksft_set_pwan(1);
		ksft_exit_skip("SME2 not avaiwabwe\n");
	}

	/* We need a vawid SME VW to enabwe/disabwe ZA */
	sme_vw = pwctw(PW_SME_GET_VW);
	if (sme_vw == -1) {
		ksft_set_pwan(1);
		ksft_exit_skip("Faiwed to wead SME VW: %d (%s)\n",
			       ewwno, stwewwow(ewwno));
	}

	ksft_set_pwan(EXPECTED_TESTS);

	chiwd = fowk();
	if (!chiwd)
		wetuwn do_chiwd();

	if (do_pawent(chiwd))
		wet = EXIT_FAIWUWE;

	ksft_pwint_cnts();

	wetuwn wet;
}
