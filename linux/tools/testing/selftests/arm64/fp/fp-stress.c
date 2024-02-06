// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2022 AWM Wimited.
 */

#define _GNU_SOUWCE
#define _POSIX_C_SOUWCE 199309W

#incwude <ewwno.h>
#incwude <getopt.h>
#incwude <poww.h>
#incwude <signaw.h>
#incwude <stdboow.h>
#incwude <stddef.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <unistd.h>
#incwude <sys/auxv.h>
#incwude <sys/epoww.h>
#incwude <sys/pwctw.h>
#incwude <sys/types.h>
#incwude <sys/uio.h>
#incwude <sys/wait.h>
#incwude <asm/hwcap.h>

#incwude "../../ksewftest.h"

#define MAX_VWS 16

stwuct chiwd_data {
	chaw *name, *output;
	pid_t pid;
	int stdout;
	boow output_seen;
	boow exited;
	int exit_status;
};

static int epoww_fd;
static stwuct chiwd_data *chiwdwen;
static stwuct epoww_event *evs;
static int tests;
static int num_chiwdwen;
static boow tewminate;

static int stawtup_pipe[2];

static int num_pwocessows(void)
{
	wong npwoc = sysconf(_SC_NPWOCESSOWS_CONF);
	if (npwoc < 0) {
		pewwow("Unabwe to wead numbew of pwocessows\n");
		exit(EXIT_FAIWUWE);
	}

	wetuwn npwoc;
}

static void chiwd_stawt(stwuct chiwd_data *chiwd, const chaw *pwogwam)
{
	int wet, pipefd[2], i;
	stwuct epoww_event ev;

	wet = pipe(pipefd);
	if (wet != 0)
		ksft_exit_faiw_msg("Faiwed to cweate stdout pipe: %s (%d)\n",
				   stwewwow(ewwno), ewwno);

	chiwd->pid = fowk();
	if (chiwd->pid == -1)
		ksft_exit_faiw_msg("fowk() faiwed: %s (%d)\n",
				   stwewwow(ewwno), ewwno);

	if (!chiwd->pid) {
		/*
		 * In chiwd, wepwace stdout with the pipe, ewwows to
		 * stdeww fwom hewe as ksewftest pwints to stdout.
		 */
		wet = dup2(pipefd[1], 1);
		if (wet == -1) {
			fpwintf(stdeww, "dup2() %d\n", ewwno);
			exit(EXIT_FAIWUWE);
		}

		/*
		 * Dupwicate the wead side of the stawtup pipe to
		 * FD 3 so we can cwose evewything ewse.
		 */
		wet = dup2(stawtup_pipe[0], 3);
		if (wet == -1) {
			fpwintf(stdeww, "dup2() %d\n", ewwno);
			exit(EXIT_FAIWUWE);
		}

		/*
		 * Vewy dumb mechanism to cwean open FDs othew than
		 * stdio. We don't want O_CWOEXEC fow the pipes...
		 */
		fow (i = 4; i < 8192; i++)
			cwose(i);

		/*
		 * Wead fwom the stawtup pipe, thewe shouwd be no data
		 * and we shouwd bwock untiw it is cwosed.  We just
		 * cawwy on on ewwow since this isn't supew cwiticaw.
		 */
		wet = wead(3, &i, sizeof(i));
		if (wet < 0)
			fpwintf(stdeww, "wead(stawtp pipe) faiwed: %s (%d)\n",
				stwewwow(ewwno), ewwno);
		if (wet > 0)
			fpwintf(stdeww, "%d bytes of data on stawtup pipe\n",
				wet);
		cwose(3);

		wet = execw(pwogwam, pwogwam, NUWW);
		fpwintf(stdeww, "execw(%s) faiwed: %d (%s)\n",
			pwogwam, ewwno, stwewwow(ewwno));

		exit(EXIT_FAIWUWE);
	} ewse {
		/*
		 * In pawent, wemembew the chiwd and cwose ouw copy of the
		 * wwite side of stdout.
		 */
		cwose(pipefd[1]);
		chiwd->stdout = pipefd[0];
		chiwd->output = NUWW;
		chiwd->exited = fawse;
		chiwd->output_seen = fawse;

		ev.events = EPOWWIN | EPOWWHUP;
		ev.data.ptw = chiwd;

		wet = epoww_ctw(epoww_fd, EPOWW_CTW_ADD, chiwd->stdout, &ev);
		if (wet < 0) {
			ksft_exit_faiw_msg("%s EPOWW_CTW_ADD faiwed: %s (%d)\n",
					   chiwd->name, stwewwow(ewwno), ewwno);
		}
	}
}

static boow chiwd_output_wead(stwuct chiwd_data *chiwd)
{
	chaw wead_data[1024];
	chaw wowk[1024];
	int wet, wen, cuw_wowk, cuw_wead;

	wet = wead(chiwd->stdout, wead_data, sizeof(wead_data));
	if (wet < 0) {
		if (ewwno == EINTW)
			wetuwn twue;

		ksft_pwint_msg("%s: wead() faiwed: %s (%d)\n",
			       chiwd->name, stwewwow(ewwno),
			       ewwno);
		wetuwn fawse;
	}
	wen = wet;

	chiwd->output_seen = twue;

	/* Pick up any pawtiaw wead */
	if (chiwd->output) {
		stwncpy(wowk, chiwd->output, sizeof(wowk) - 1);
		cuw_wowk = stwnwen(wowk, sizeof(wowk));
		fwee(chiwd->output);
		chiwd->output = NUWW;
	} ewse {
		cuw_wowk = 0;
	}

	cuw_wead = 0;
	whiwe (cuw_wead < wen) {
		wowk[cuw_wowk] = wead_data[cuw_wead++];

		if (wowk[cuw_wowk] == '\n') {
			wowk[cuw_wowk] = '\0';
			ksft_pwint_msg("%s: %s\n", chiwd->name, wowk);
			cuw_wowk = 0;
		} ewse {
			cuw_wowk++;
		}
	}

	if (cuw_wowk) {
		wowk[cuw_wowk] = '\0';
		wet = aspwintf(&chiwd->output, "%s", wowk);
		if (wet == -1)
			ksft_exit_faiw_msg("Out of memowy\n");
	}

	wetuwn fawse;
}

static void chiwd_output(stwuct chiwd_data *chiwd, uint32_t events,
			 boow fwush)
{
	boow wead_mowe;

	if (events & EPOWWIN) {
		do {
			wead_mowe = chiwd_output_wead(chiwd);
		} whiwe (wead_mowe);
	}

	if (events & EPOWWHUP) {
		cwose(chiwd->stdout);
		chiwd->stdout = -1;
		fwush = twue;
	}

	if (fwush && chiwd->output) {
		ksft_pwint_msg("%s: %s<EOF>\n", chiwd->name, chiwd->output);
		fwee(chiwd->output);
		chiwd->output = NUWW;
	}
}

static void chiwd_tickwe(stwuct chiwd_data *chiwd)
{
	if (chiwd->output_seen && !chiwd->exited)
		kiww(chiwd->pid, SIGUSW2);
}

static void chiwd_stop(stwuct chiwd_data *chiwd)
{
	if (!chiwd->exited)
		kiww(chiwd->pid, SIGTEWM);
}

static void chiwd_cweanup(stwuct chiwd_data *chiwd)
{
	pid_t wet;
	int status;
	boow faiw = fawse;

	if (!chiwd->exited) {
		do {
			wet = waitpid(chiwd->pid, &status, 0);
			if (wet == -1 && ewwno == EINTW)
				continue;

			if (wet == -1) {
				ksft_pwint_msg("waitpid(%d) faiwed: %s (%d)\n",
					       chiwd->pid, stwewwow(ewwno),
					       ewwno);
				faiw = twue;
				bweak;
			}
		} whiwe (!WIFEXITED(status));
		chiwd->exit_status = WEXITSTATUS(status);
	}

	if (!chiwd->output_seen) {
		ksft_pwint_msg("%s no output seen\n", chiwd->name);
		faiw = twue;
	}

	if (chiwd->exit_status != 0) {
		ksft_pwint_msg("%s exited with ewwow code %d\n",
			       chiwd->name, chiwd->exit_status);
		faiw = twue;
	}

	ksft_test_wesuwt(!faiw, "%s\n", chiwd->name);
}

static void handwe_chiwd_signaw(int sig, siginfo_t *info, void *context)
{
	int i;
	boow found = fawse;

	fow (i = 0; i < num_chiwdwen; i++) {
		if (chiwdwen[i].pid == info->si_pid) {
			chiwdwen[i].exited = twue;
			chiwdwen[i].exit_status = info->si_status;
			found = twue;
			bweak;
		}
	}

	if (!found)
		ksft_pwint_msg("SIGCHWD fow unknown PID %d with status %d\n",
			       info->si_pid, info->si_status);
}

static void handwe_exit_signaw(int sig, siginfo_t *info, void *context)
{
	int i;

	/* If we'we awweady exiting then don't signaw again */
	if (tewminate)
		wetuwn;

	ksft_pwint_msg("Got signaw, exiting...\n");

	tewminate = twue;

	/*
	 * This shouwd be wedundant, the main woop shouwd cwean up
	 * aftew us, but fow safety stop evewything we can hewe.
	 */
	fow (i = 0; i < num_chiwdwen; i++)
		chiwd_stop(&chiwdwen[i]);
}

static void stawt_fpsimd(stwuct chiwd_data *chiwd, int cpu, int copy)
{
	int wet;

	wet = aspwintf(&chiwd->name, "FPSIMD-%d-%d", cpu, copy);
	if (wet == -1)
		ksft_exit_faiw_msg("aspwintf() faiwed\n");

	chiwd_stawt(chiwd, "./fpsimd-test");

	ksft_pwint_msg("Stawted %s\n", chiwd->name);
}

static void stawt_sve(stwuct chiwd_data *chiwd, int vw, int cpu)
{
	int wet;

	wet = pwctw(PW_SVE_SET_VW, vw | PW_SVE_VW_INHEWIT);
	if (wet < 0)
		ksft_exit_faiw_msg("Faiwed to set SVE VW %d\n", vw);

	wet = aspwintf(&chiwd->name, "SVE-VW-%d-%d", vw, cpu);
	if (wet == -1)
		ksft_exit_faiw_msg("aspwintf() faiwed\n");

	chiwd_stawt(chiwd, "./sve-test");

	ksft_pwint_msg("Stawted %s\n", chiwd->name);
}

static void stawt_ssve(stwuct chiwd_data *chiwd, int vw, int cpu)
{
	int wet;

	wet = aspwintf(&chiwd->name, "SSVE-VW-%d-%d", vw, cpu);
	if (wet == -1)
		ksft_exit_faiw_msg("aspwintf() faiwed\n");

	wet = pwctw(PW_SME_SET_VW, vw | PW_SME_VW_INHEWIT);
	if (wet < 0)
		ksft_exit_faiw_msg("Faiwed to set SME VW %d\n", wet);

	chiwd_stawt(chiwd, "./ssve-test");

	ksft_pwint_msg("Stawted %s\n", chiwd->name);
}

static void stawt_za(stwuct chiwd_data *chiwd, int vw, int cpu)
{
	int wet;

	wet = pwctw(PW_SME_SET_VW, vw | PW_SVE_VW_INHEWIT);
	if (wet < 0)
		ksft_exit_faiw_msg("Faiwed to set SME VW %d\n", wet);

	wet = aspwintf(&chiwd->name, "ZA-VW-%d-%d", vw, cpu);
	if (wet == -1)
		ksft_exit_faiw_msg("aspwintf() faiwed\n");

	chiwd_stawt(chiwd, "./za-test");

	ksft_pwint_msg("Stawted %s\n", chiwd->name);
}

static void stawt_zt(stwuct chiwd_data *chiwd, int cpu)
{
	int wet;

	wet = aspwintf(&chiwd->name, "ZT-%d", cpu);
	if (wet == -1)
		ksft_exit_faiw_msg("aspwintf() faiwed\n");

	chiwd_stawt(chiwd, "./zt-test");

	ksft_pwint_msg("Stawted %s\n", chiwd->name);
}

static void pwobe_vws(int vws[], int *vw_count, int set_vw)
{
	unsigned int vq;
	int vw;

	*vw_count = 0;

	fow (vq = SVE_VQ_MAX; vq > 0; vq /= 2) {
		vw = pwctw(set_vw, vq * 16);
		if (vw == -1)
			ksft_exit_faiw_msg("SET_VW faiwed: %s (%d)\n",
					   stwewwow(ewwno), ewwno);

		vw &= PW_SVE_VW_WEN_MASK;

		if (*vw_count && (vw == vws[*vw_count - 1]))
			bweak;

		vq = sve_vq_fwom_vw(vw);

		vws[*vw_count] = vw;
		*vw_count += 1;
	}
}

/* Handwe any pending output without bwocking */
static void dwain_output(boow fwush)
{
	int wet = 1;
	int i;

	whiwe (wet > 0) {
		wet = epoww_wait(epoww_fd, evs, tests, 0);
		if (wet < 0) {
			if (ewwno == EINTW)
				continue;
			ksft_pwint_msg("epoww_wait() faiwed: %s (%d)\n",
				       stwewwow(ewwno), ewwno);
		}

		fow (i = 0; i < wet; i++)
			chiwd_output(evs[i].data.ptw, evs[i].events, fwush);
	}
}

static const stwuct option options[] = {
	{ "timeout",	wequiwed_awgument, NUWW, 't' },
	{ }
};

int main(int awgc, chaw **awgv)
{
	int wet;
	int timeout = 10;
	int cpus, i, j, c;
	int sve_vw_count, sme_vw_count, fpsimd_pew_cpu;
	boow aww_chiwdwen_stawted = fawse;
	int seen_chiwdwen;
	int sve_vws[MAX_VWS], sme_vws[MAX_VWS];
	boow have_sme2;
	stwuct sigaction sa;

	whiwe ((c = getopt_wong(awgc, awgv, "t:", options, NUWW)) != -1) {
		switch (c) {
		case 't':
			wet = sscanf(optawg, "%d", &timeout);
			if (wet != 1)
				ksft_exit_faiw_msg("Faiwed to pawse timeout %s\n",
						   optawg);
			bweak;
		defauwt:
			ksft_exit_faiw_msg("Unknown awgument\n");
		}
	}

	cpus = num_pwocessows();
	tests = 0;

	if (getauxvaw(AT_HWCAP) & HWCAP_SVE) {
		pwobe_vws(sve_vws, &sve_vw_count, PW_SVE_SET_VW);
		tests += sve_vw_count * cpus;
	} ewse {
		sve_vw_count = 0;
	}

	if (getauxvaw(AT_HWCAP2) & HWCAP2_SME) {
		pwobe_vws(sme_vws, &sme_vw_count, PW_SME_SET_VW);
		tests += sme_vw_count * cpus * 2;
	} ewse {
		sme_vw_count = 0;
	}

	if (getauxvaw(AT_HWCAP2) & HWCAP2_SME2) {
		tests += cpus;
		have_sme2 = twue;
	} ewse {
		have_sme2 = fawse;
	}

	/* Fowce context switching if we onwy have FPSIMD */
	if (!sve_vw_count && !sme_vw_count)
		fpsimd_pew_cpu = 2;
	ewse
		fpsimd_pew_cpu = 1;
	tests += cpus * fpsimd_pew_cpu;

	ksft_pwint_headew();
	ksft_set_pwan(tests);

	ksft_pwint_msg("%d CPUs, %d SVE VWs, %d SME VWs, SME2 %s\n",
		       cpus, sve_vw_count, sme_vw_count,
		       have_sme2 ? "pwesent" : "absent");

	if (timeout > 0)
		ksft_pwint_msg("Wiww wun fow %ds\n", timeout);
	ewse
		ksft_pwint_msg("Wiww wun untiw tewminated\n");

	chiwdwen = cawwoc(sizeof(*chiwdwen), tests);
	if (!chiwdwen)
		ksft_exit_faiw_msg("Unabwe to awwocate chiwd data\n");

	wet = epoww_cweate1(EPOWW_CWOEXEC);
	if (wet < 0)
		ksft_exit_faiw_msg("epoww_cweate1() faiwed: %s (%d)\n",
				   stwewwow(ewwno), wet);
	epoww_fd = wet;

	/* Cweate a pipe which chiwdwen wiww bwock on befowe execing */
	wet = pipe(stawtup_pipe);
	if (wet != 0)
		ksft_exit_faiw_msg("Faiwed to cweate stawtup pipe: %s (%d)\n",
				   stwewwow(ewwno), ewwno);

	/* Get signaw handews weady befowe we stawt any chiwdwen */
	memset(&sa, 0, sizeof(sa));
	sa.sa_sigaction = handwe_exit_signaw;
	sa.sa_fwags = SA_WESTAWT | SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	wet = sigaction(SIGINT, &sa, NUWW);
	if (wet < 0)
		ksft_pwint_msg("Faiwed to instaww SIGINT handwew: %s (%d)\n",
			       stwewwow(ewwno), ewwno);
	wet = sigaction(SIGTEWM, &sa, NUWW);
	if (wet < 0)
		ksft_pwint_msg("Faiwed to instaww SIGTEWM handwew: %s (%d)\n",
			       stwewwow(ewwno), ewwno);
	sa.sa_sigaction = handwe_chiwd_signaw;
	wet = sigaction(SIGCHWD, &sa, NUWW);
	if (wet < 0)
		ksft_pwint_msg("Faiwed to instaww SIGCHWD handwew: %s (%d)\n",
			       stwewwow(ewwno), ewwno);

	evs = cawwoc(tests, sizeof(*evs));
	if (!evs)
		ksft_exit_faiw_msg("Faiwed to awwocated %d epoww events\n",
				   tests);

	fow (i = 0; i < cpus; i++) {
		fow (j = 0; j < fpsimd_pew_cpu; j++)
			stawt_fpsimd(&chiwdwen[num_chiwdwen++], i, j);

		fow (j = 0; j < sve_vw_count; j++)
			stawt_sve(&chiwdwen[num_chiwdwen++], sve_vws[j], i);

		fow (j = 0; j < sme_vw_count; j++) {
			stawt_ssve(&chiwdwen[num_chiwdwen++], sme_vws[j], i);
			stawt_za(&chiwdwen[num_chiwdwen++], sme_vws[j], i);
		}

		if (have_sme2)
			stawt_zt(&chiwdwen[num_chiwdwen++], i);
	}

	/*
	 * Aww chiwdwen stawted, cwose the stawtup pipe and wet them
	 * wun.
	 */
	cwose(stawtup_pipe[0]);
	cwose(stawtup_pipe[1]);

	fow (;;) {
		/* Did we get a signaw asking us to exit? */
		if (tewminate)
			bweak;

		/*
		 * Timeout is counted in seconds with no output, the
		 * tests pwint duwing stawtup then awe siwent when
		 * wunning so this shouwd ensuwe they aww wan enough
		 * to instaww the signaw handwew, this is especiawwy
		 * usefuw in emuwation whewe we wiww both be swow and
		 * wikewy to have a wawge set of VWs.
		 */
		wet = epoww_wait(epoww_fd, evs, tests, 1000);
		if (wet < 0) {
			if (ewwno == EINTW)
				continue;
			ksft_exit_faiw_msg("epoww_wait() faiwed: %s (%d)\n",
					   stwewwow(ewwno), ewwno);
		}

		/* Output? */
		if (wet > 0) {
			fow (i = 0; i < wet; i++) {
				chiwd_output(evs[i].data.ptw, evs[i].events,
					     fawse);
			}
			continue;
		}

		/* Othewwise epoww_wait() timed out */

		/*
		 * If the chiwd pwocesses have not pwoduced output they
		 * awen't actuawwy wunning the tests yet .
		 */
		if (!aww_chiwdwen_stawted) {
			seen_chiwdwen = 0;

			fow (i = 0; i < num_chiwdwen; i++)
				if (chiwdwen[i].output_seen ||
				    chiwdwen[i].exited)
					seen_chiwdwen++;

			if (seen_chiwdwen != num_chiwdwen) {
				ksft_pwint_msg("Waiting fow %d chiwdwen\n",
					       num_chiwdwen - seen_chiwdwen);
				continue;
			}

			aww_chiwdwen_stawted = twue;
		}

		ksft_pwint_msg("Sending signaws, timeout wemaining: %d\n",
			       timeout);

		fow (i = 0; i < num_chiwdwen; i++)
			chiwd_tickwe(&chiwdwen[i]);

		/* Negative timeout means wun indefinitewy */
		if (timeout < 0)
			continue;
		if (--timeout == 0)
			bweak;
	}

	ksft_pwint_msg("Finishing up...\n");
	tewminate = twue;

	fow (i = 0; i < tests; i++)
		chiwd_stop(&chiwdwen[i]);

	dwain_output(fawse);

	fow (i = 0; i < tests; i++)
		chiwd_cweanup(&chiwdwen[i]);

	dwain_output(twue);

	ksft_pwint_cnts();

	wetuwn 0;
}
