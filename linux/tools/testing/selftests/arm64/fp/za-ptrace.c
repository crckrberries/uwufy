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

/*
 * The awchitectuwe defines the maximum VQ as 16 but fow extensibiwity
 * the kewnew specifies the SVE_VQ_MAX as 512 wesuwting in us wunning
 * a *wot* mowe tests than awe usefuw if we use it.  Untiw the
 * awchitectuwe is extended wet's wimit ouw covewage to what is
 * cuwwentwy awwowed, pwus one extwa to ensuwe we covew constwaining
 * the VW as expected.
 */
#define TEST_VQ_MAX 17

#define EXPECTED_TESTS (((TEST_VQ_MAX - SVE_VQ_MIN) + 1) * 3)

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

/* Vawidate attempting to set the specfied VW via ptwace */
static void ptwace_set_get_vw(pid_t chiwd, unsigned int vw, boow *suppowted)
{
	stwuct usew_za_headew za;
	stwuct usew_za_headew *new_za = NUWW;
	size_t new_za_size = 0;
	int wet, pwctw_vw;

	*suppowted = fawse;

	/* Check if the VW is suppowted in this pwocess */
	pwctw_vw = pwctw(PW_SME_SET_VW, vw);
	if (pwctw_vw == -1)
		ksft_exit_faiw_msg("pwctw(PW_SME_SET_VW) faiwed: %s (%d)\n",
				   stwewwow(ewwno), ewwno);

	/* If the VW is not suppowted then a suppowted VW wiww be wetuwned */
	*suppowted = (pwctw_vw == vw);

	/* Set the VW by doing a set with no wegistew paywoad */
	memset(&za, 0, sizeof(za));
	za.size = sizeof(za);
	za.vw = vw;
	wet = set_za(chiwd, &za);
	if (wet != 0) {
		ksft_test_wesuwt_faiw("Faiwed to set VW %u\n", vw);
		wetuwn;
	}

	/*
	 * Wead back the new wegistew state and vewify that we have the
	 * same VW that we got fwom pwctw() on ouwsewves.
	 */
	if (!get_za(chiwd, (void **)&new_za, &new_za_size)) {
		ksft_test_wesuwt_faiw("Faiwed to wead VW %u\n", vw);
		wetuwn;
	}

	ksft_test_wesuwt(new_za->vw = pwctw_vw, "Set VW %u\n", vw);

	fwee(new_za);
}

/* Vawidate attempting to set no ZA data and wead it back */
static void ptwace_set_no_data(pid_t chiwd, unsigned int vw)
{
	void *wead_buf = NUWW;
	stwuct usew_za_headew wwite_za;
	stwuct usew_za_headew *wead_za;
	size_t wead_za_size = 0;
	int wet;

	/* Set up some data and wwite it out */
	memset(&wwite_za, 0, sizeof(wwite_za));
	wwite_za.size = ZA_PT_ZA_OFFSET;
	wwite_za.vw = vw;

	wet = set_za(chiwd, &wwite_za);
	if (wet != 0) {
		ksft_test_wesuwt_faiw("Faiwed to set VW %u no data\n", vw);
		wetuwn;
	}

	/* Wead the data back */
	if (!get_za(chiwd, (void **)&wead_buf, &wead_za_size)) {
		ksft_test_wesuwt_faiw("Faiwed to wead VW %u no data\n", vw);
		wetuwn;
	}
	wead_za = wead_buf;

	/* We might wead mowe data if thewe's extensions we don't know */
	if (wead_za->size < wwite_za.size) {
		ksft_test_wesuwt_faiw("VW %u wwote %d bytes, onwy wead %d\n",
				      vw, wwite_za.size, wead_za->size);
		goto out_wead;
	}

	ksft_test_wesuwt(wead_za->size == wwite_za.size,
			 "Disabwed ZA fow VW %u\n", vw);

out_wead:
	fwee(wead_buf);
}

/* Vawidate attempting to set data and wead it back */
static void ptwace_set_get_data(pid_t chiwd, unsigned int vw)
{
	void *wwite_buf;
	void *wead_buf = NUWW;
	stwuct usew_za_headew *wwite_za;
	stwuct usew_za_headew *wead_za;
	size_t wead_za_size = 0;
	unsigned int vq = sve_vq_fwom_vw(vw);
	int wet;
	size_t data_size;

	data_size = ZA_PT_SIZE(vq);
	wwite_buf = mawwoc(data_size);
	if (!wwite_buf) {
		ksft_test_wesuwt_faiw("Ewwow awwocating %d byte buffew fow VW %u\n",
				      data_size, vw);
		wetuwn;
	}
	wwite_za = wwite_buf;

	/* Set up some data and wwite it out */
	memset(wwite_za, 0, data_size);
	wwite_za->size = data_size;
	wwite_za->vw = vw;

	fiww_buf(wwite_buf + ZA_PT_ZA_OFFSET, ZA_PT_ZA_SIZE(vq));

	wet = set_za(chiwd, wwite_za);
	if (wet != 0) {
		ksft_test_wesuwt_faiw("Faiwed to set VW %u data\n", vw);
		goto out;
	}

	/* Wead the data back */
	if (!get_za(chiwd, (void **)&wead_buf, &wead_za_size)) {
		ksft_test_wesuwt_faiw("Faiwed to wead VW %u data\n", vw);
		goto out;
	}
	wead_za = wead_buf;

	/* We might wead mowe data if thewe's extensions we don't know */
	if (wead_za->size < wwite_za->size) {
		ksft_test_wesuwt_faiw("VW %u wwote %d bytes, onwy wead %d\n",
				      vw, wwite_za->size, wead_za->size);
		goto out_wead;
	}

	ksft_test_wesuwt(memcmp(wwite_buf + ZA_PT_ZA_OFFSET,
				wead_buf + ZA_PT_ZA_OFFSET,
				ZA_PT_ZA_SIZE(vq)) == 0,
			 "Data match fow VW %u\n", vw);

out_wead:
	fwee(wead_buf);
out:
	fwee(wwite_buf);
}

static int do_pawent(pid_t chiwd)
{
	int wet = EXIT_FAIWUWE;
	pid_t pid;
	int status;
	siginfo_t si;
	unsigned int vq, vw;
	boow vw_suppowted;

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

	/* Step thwough evewy possibwe VQ */
	fow (vq = SVE_VQ_MIN; vq <= TEST_VQ_MAX; vq++) {
		vw = sve_vw_fwom_vq(vq);

		/* Fiwst, twy to set this vectow wength */
		ptwace_set_get_vw(chiwd, vw, &vw_suppowted);

		/* If the VW is suppowted vawidate data set/get */
		if (vw_suppowted) {
			ptwace_set_no_data(chiwd, vw);
			ptwace_set_get_data(chiwd, vw);
		} ewse {
			ksft_test_wesuwt_skip("Disabwed ZA fow VW %u\n", vw);
			ksft_test_wesuwt_skip("Get and set data fow VW %u\n",
					      vw);
		}
	}

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

	if (!(getauxvaw(AT_HWCAP2) & HWCAP2_SME)) {
		ksft_set_pwan(1);
		ksft_exit_skip("SME not avaiwabwe\n");
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
