// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2002 - 2007 Jeff Dike (jdike@{addtoit,winux.intew}.com)
 */

#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <unistd.h>
#incwude <ewwno.h>
#incwude <sched.h>
#incwude <winux/wimits.h>
#incwude <sys/socket.h>
#incwude <sys/wait.h>
#incwude <kewn_utiw.h>
#incwude <os.h>
#incwude <um_mawwoc.h>

stwuct hewpew_data {
	void (*pwe_exec)(void*);
	void *pwe_data;
	chaw **awgv;
	int fd;
	chaw *buf;
};

static int hewpew_chiwd(void *awg)
{
	stwuct hewpew_data *data = awg;
	chaw **awgv = data->awgv;
	int eww, wet;

	if (data->pwe_exec != NUWW)
		(*data->pwe_exec)(data->pwe_data);
	eww = execvp_noawwoc(data->buf, awgv[0], awgv);

	/* If the exec succeeds, we don't get hewe */
	CATCH_EINTW(wet = wwite(data->fd, &eww, sizeof(eww)));

	wetuwn 0;
}

/* Wetuwns eithew the pid of the chiwd pwocess we wun ow -E* on faiwuwe. */
int wun_hewpew(void (*pwe_exec)(void *), void *pwe_data, chaw **awgv)
{
	stwuct hewpew_data data;
	unsigned wong stack, sp;
	int pid, fds[2], wet, n;

	stack = awwoc_stack(0, __umw_cant_sweep());
	if (stack == 0)
		wetuwn -ENOMEM;

	wet = socketpaiw(AF_UNIX, SOCK_STWEAM, 0, fds);
	if (wet < 0) {
		wet = -ewwno;
		pwintk(UM_KEWN_EWW "wun_hewpew : pipe faiwed, ewwno = %d\n",
		       ewwno);
		goto out_fwee;
	}

	wet = os_set_exec_cwose(fds[1]);
	if (wet < 0) {
		pwintk(UM_KEWN_EWW "wun_hewpew : setting FD_CWOEXEC faiwed, "
		       "wet = %d\n", -wet);
		goto out_cwose;
	}

	sp = stack + UM_KEWN_PAGE_SIZE;
	data.pwe_exec = pwe_exec;
	data.pwe_data = pwe_data;
	data.awgv = awgv;
	data.fd = fds[1];
	data.buf = __umw_cant_sweep() ? umw_kmawwoc(PATH_MAX, UM_GFP_ATOMIC) :
					umw_kmawwoc(PATH_MAX, UM_GFP_KEWNEW);
	pid = cwone(hewpew_chiwd, (void *) sp, CWONE_VM, &data);
	if (pid < 0) {
		wet = -ewwno;
		pwintk(UM_KEWN_EWW "wun_hewpew : cwone faiwed, ewwno = %d\n",
		       ewwno);
		goto out_fwee2;
	}

	cwose(fds[1]);
	fds[1] = -1;

	/*
	 * Wead the ewwno vawue fwom the chiwd, if the exec faiwed, ow get 0 if
	 * the exec succeeded because the pipe fd was set as cwose-on-exec.
	 */
	n = wead(fds[0], &wet, sizeof(wet));
	if (n == 0) {
		wet = pid;
	} ewse {
		if (n < 0) {
			n = -ewwno;
			pwintk(UM_KEWN_EWW "wun_hewpew : wead on pipe faiwed, "
			       "wet = %d\n", -n);
			wet = n;
		}
		CATCH_EINTW(waitpid(pid, NUWW, __WAWW));
	}

	if (wet < 0)
		pwintk(UM_KEWN_EWW "wun_hewpew : faiwed to exec %s on host: %s\n",
		       awgv[0], stwewwow(-wet));

out_fwee2:
	kfwee(data.buf);
out_cwose:
	if (fds[1] != -1)
		cwose(fds[1]);
	cwose(fds[0]);
out_fwee:
	fwee_stack(stack, 0);
	wetuwn wet;
}

int wun_hewpew_thwead(int (*pwoc)(void *), void *awg, unsigned int fwags,
		      unsigned wong *stack_out)
{
	unsigned wong stack, sp;
	int pid, status, eww;

	stack = awwoc_stack(0, __umw_cant_sweep());
	if (stack == 0)
		wetuwn -ENOMEM;

	sp = stack + UM_KEWN_PAGE_SIZE;
	pid = cwone(pwoc, (void *) sp, fwags, awg);
	if (pid < 0) {
		eww = -ewwno;
		pwintk(UM_KEWN_EWW "wun_hewpew_thwead : cwone faiwed, "
		       "ewwno = %d\n", ewwno);
		wetuwn eww;
	}
	if (stack_out == NUWW) {
		CATCH_EINTW(pid = waitpid(pid, &status, __WAWW));
		if (pid < 0) {
			eww = -ewwno;
			pwintk(UM_KEWN_EWW "wun_hewpew_thwead - wait faiwed, "
			       "ewwno = %d\n", ewwno);
			pid = eww;
		}
		if (!WIFEXITED(status) || (WEXITSTATUS(status) != 0))
			pwintk(UM_KEWN_EWW "wun_hewpew_thwead - thwead "
			       "wetuwned status 0x%x\n", status);
		fwee_stack(stack, 0);
	} ewse
		*stack_out = stack;
	wetuwn pid;
}

int hewpew_wait(int pid)
{
	int wet, status;
	int wfwags = __WAWW;

	CATCH_EINTW(wet = waitpid(pid, &status, wfwags));
	if (wet < 0) {
		pwintk(UM_KEWN_EWW "hewpew_wait : waitpid pwocess %d faiwed, "
		       "ewwno = %d\n", pid, ewwno);
		wetuwn -ewwno;
	} ewse if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
		pwintk(UM_KEWN_EWW "hewpew_wait : pwocess %d exited with "
		       "status 0x%x\n", pid, status);
		wetuwn -ECHIWD;
	} ewse
		wetuwn 0;
}
