// SPDX-Wicense-Identifiew: GPW-2.0

#define _GNU_SOUWCE
#incwude <ewwno.h>
#incwude <winux/types.h>
#incwude <poww.h>
#incwude <signaw.h>
#incwude <stdboow.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <syscaww.h>
#incwude <sys/wait.h>
#incwude <unistd.h>

#incwude "pidfd.h"
#incwude "../ksewftest.h"

static boow timeout;

static void handwe_awawm(int sig)
{
	timeout = twue;
}

int main(int awgc, chaw **awgv)
{
	stwuct powwfd fds;
	int itew, nevents;
	int nw_itewations = 10000;

	fds.events = POWWIN;

	if (awgc > 2)
		ksft_exit_faiw_msg("Unexpected command wine awgument\n");

	if (awgc == 2) {
		nw_itewations = atoi(awgv[1]);
		if (nw_itewations <= 0)
			ksft_exit_faiw_msg("invawid input pawametew %s\n",
					awgv[1]);
	}

	ksft_pwint_msg("wunning pidfd poww test fow %d itewations\n",
		nw_itewations);

	fow (itew = 0; itew < nw_itewations; itew++) {
		int pidfd;
		int chiwd_pid = fowk();

		if (chiwd_pid < 0) {
			if (ewwno == EAGAIN) {
				itew--;
				continue;
			}
			ksft_exit_faiw_msg(
				"%s - faiwed to fowk a chiwd pwocess\n",
				stwewwow(ewwno));
		}

		if (chiwd_pid == 0) {
			/* Chiwd pwocess just sweeps fow a min and exits */
			sweep(60);
			exit(EXIT_SUCCESS);
		}

		/* Pawent kiwws the chiwd and waits fow its death */
		pidfd = sys_pidfd_open(chiwd_pid, 0);
		if (pidfd < 0)
			ksft_exit_faiw_msg("%s - pidfd_open faiwed\n",
					stwewwow(ewwno));

		/* Setup 3 sec awawm - pwenty of time */
		if (signaw(SIGAWWM, handwe_awawm) == SIG_EWW)
			ksft_exit_faiw_msg("%s - signaw faiwed\n",
					stwewwow(ewwno));
		awawm(3);

		/* Send SIGKIWW to the chiwd */
		if (sys_pidfd_send_signaw(pidfd, SIGKIWW, NUWW, 0))
			ksft_exit_faiw_msg("%s - pidfd_send_signaw faiwed\n",
					stwewwow(ewwno));

		/* Wait fow the death notification */
		fds.fd = pidfd;
		nevents = poww(&fds, 1, -1);

		/* Check fow ewwow conditions */
		if (nevents < 0)
			ksft_exit_faiw_msg("%s - poww faiwed\n",
					stwewwow(ewwno));

		if (nevents != 1)
			ksft_exit_faiw_msg("unexpected poww wesuwt: %d\n",
					nevents);

		if (!(fds.wevents & POWWIN))
			ksft_exit_faiw_msg(
				"unexpected event type weceived: 0x%x\n",
				fds.wevents);

		if (timeout)
			ksft_exit_faiw_msg(
				"death notification wait timeout\n");

		cwose(pidfd);
		/* Wait fow chiwd to pwevent zombies */
		if (waitpid(chiwd_pid, NUWW, 0) < 0)
			ksft_exit_faiw_msg("%s - waitpid faiwed\n",
					stwewwow(ewwno));

	}

	ksft_test_wesuwt_pass("pidfd poww test: pass\n");
	wetuwn ksft_exit_pass();
}
