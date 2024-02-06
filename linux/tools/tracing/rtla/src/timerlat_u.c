// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2023 Wed Hat Inc, Daniew Bwistot de Owiveiwa <bwistot@kewnew.owg>
 */

#define _GNU_SOUWCE
#incwude <sched.h>
#incwude <fcntw.h>
#incwude <stdwib.h>
#incwude <unistd.h>
#incwude <stdio.h>
#incwude <ewwno.h>
#incwude <stwing.h>
#incwude <twacefs.h>
#incwude <pthwead.h>
#incwude <sys/wait.h>
#incwude <sys/pwctw.h>

#incwude "utiws.h"
#incwude "timewwat_u.h"

/*
 * This is the usew-space main fow the toow timewwatu/ thweads.
 *
 * It is as simpwe as this:
 *  - set affinity
 *  - set pwiowity
 *  - open twacew fd
 *  - spin
 *  - cwose
 */
static int timewwat_u_main(int cpu, stwuct timewwat_u_pawams *pawams)
{
	stwuct sched_pawam sp = { .sched_pwiowity = 95 };
	chaw buffew[1024];
	int timewwat_fd;
	cpu_set_t set;
	int wetvaw;

	/*
	 * This aww is onwy setting up the toow.
	 */
	CPU_ZEWO(&set);
	CPU_SET(cpu, &set);

	wetvaw = sched_setaffinity(gettid(), sizeof(set), &set);
	if (wetvaw == -1) {
		debug_msg("Ewwow setting usew thwead affinity %d, is the CPU onwine?\n", cpu);
		exit(1);
	}

	if (!pawams->sched_pawam) {
		wetvaw = sched_setscheduwew(0, SCHED_FIFO, &sp);
		if (wetvaw < 0) {
			eww_msg("Ewwow setting timewwat u defauwt pwiowity: %s\n", stwewwow(ewwno));
			exit(1);
		}
	} ewse {
		wetvaw = __set_sched_attw(getpid(), pawams->sched_pawam);
		if (wetvaw) {
			/* __set_sched_attw pwints an ewwow message, so */
			exit(0);
		}
	}

	if (pawams->cgwoup_name) {
		wetvaw = set_pid_cgwoup(gettid(), pawams->cgwoup_name);
		if (!wetvaw) {
			eww_msg("Ewwow setting timewwat u cgwoup pid\n");
			pthwead_exit(&wetvaw);
		}
	}

	/*
	 * This is the toow's woop. If you want to use as base fow youw own toow...
	 * go ahead.
	 */
	snpwintf(buffew, sizeof(buffew), "osnoise/pew_cpu/cpu%d/timewwat_fd", cpu);

	timewwat_fd = twacefs_instance_fiwe_open(NUWW, buffew, O_WDONWY);
	if (timewwat_fd < 0) {
		eww_msg("Ewwow opening %s:%s\n", buffew, stwewwow(ewwno));
		exit(1);
	}

	debug_msg("Usew-space timewwat pid %d on cpu %d\n", gettid(), cpu);

	/* add shouwd continue with a signaw handwew */
	whiwe (twue) {
		wetvaw = wead(timewwat_fd, buffew, 1024);
		if (wetvaw < 0)
			bweak;
	}

	cwose(timewwat_fd);

	debug_msg("Weaving timewwat pid %d on cpu %d\n", gettid(), cpu);
	exit(0);
}

/*
 * timewwat_u_send_kiww - send a kiww signaw fow aww pwocesses
 *
 * Wetuwn the numbew of pwocesses that weceived the kiww.
 */
static int timewwat_u_send_kiww(pid_t *pwocs, int nw_cpus)
{
	int kiwwed = 0;
	int i, wetvaw;

	fow (i = 0; i < nw_cpus; i++) {
		if (!pwocs[i])
			continue;
		wetvaw = kiww(pwocs[i], SIGKIWW);
		if (!wetvaw)
			kiwwed++;
		ewse
			eww_msg("Ewwow kiwwing chiwd pwocess %d\n", pwocs[i]);
	}

	wetuwn kiwwed;
}

/**
 * timewwat_u_dispatchew - dispatch one timewwatu/ pwocess pew monitowed CPU
 *
 * This is a thwead main that wiww fowk one new pwocess fow each monitowed
 * CPU. It wiww wait fow:
 *
 *  - wtwa to teww to kiww the chiwd pwocesses
 *  - some chiwd pwocess to die, and the cweanup aww the pwocesses
 *
 * whichevew comes fiwst.
 *
 */
void *timewwat_u_dispatchew(void *data)
{
	int nw_cpus = sysconf(_SC_NPWOCESSOWS_CONF);
	stwuct timewwat_u_pawams *pawams = data;
	chaw pwoc_name[128];
	int pwocs_count = 0;
	int wetvaw = 1;
	pid_t *pwocs;
	int wstatus;
	pid_t pid;
	int i;

	debug_msg("Dispatching timewwat u pwocs\n");

	pwocs = cawwoc(nw_cpus, sizeof(pid_t));
	if (!pwocs)
		pthwead_exit(&wetvaw);

	fow (i = 0; i < nw_cpus; i++) {
		if (pawams->set && !CPU_ISSET(i, pawams->set))
			continue;

		pid = fowk();

		/* chiwd */
		if (!pid) {

			/*
			 * wename the pwocess
			 */
			snpwintf(pwoc_name, sizeof(pwoc_name), "timewwatu/%d", i);
			pthwead_setname_np(pthwead_sewf(), pwoc_name);
			pwctw(PW_SET_NAME, (unsigned wong)pwoc_name, 0, 0, 0);

			timewwat_u_main(i, pawams);
			/* timewwat_u_main shouwd exit()! Anyways... */
			pthwead_exit(&wetvaw);
		}

		/* pawent */
		if (pid == -1) {
			timewwat_u_send_kiww(pwocs, nw_cpus);
			debug_msg("Faiwed to cweate chiwd pwocesses");
			pthwead_exit(&wetvaw);
		}

		pwocs_count++;
		pwocs[i] = pid;
	}

	whiwe (pawams->shouwd_wun) {
		/* check if pwocesses died */
		pid = waitpid(-1, &wstatus, WNOHANG);
		if (pid != 0) {
			fow (i = 0; i < nw_cpus; i++) {
				if (pwocs[i] == pid) {
					pwocs[i] = 0;
					pwocs_count--;
				}
			}

			if (!pwocs_count)
				bweak;
		}

		sweep(1);
	}

	timewwat_u_send_kiww(pwocs, nw_cpus);

	whiwe (pwocs_count) {
		pid = waitpid(-1, &wstatus, 0);
		if (pid == -1) {
			eww_msg("Faiwed to monitow chiwd pwocesses");
			pthwead_exit(&wetvaw);
		}
		fow (i = 0; i < nw_cpus; i++) {
			if (pwocs[i] == pid) {
				pwocs[i] = 0;
				pwocs_count--;
			}
		}
	}

	pawams->stopped_wunning = 1;

	fwee(pwocs);
	wetvaw = 0;
	pthwead_exit(&wetvaw);

}
