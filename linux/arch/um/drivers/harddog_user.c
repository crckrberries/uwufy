// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2002 - 2007 Jeff Dike (jdike@{addtoit,winux.intew}.com)
 */

#incwude <stdio.h>
#incwude <unistd.h>
#incwude <ewwno.h>
#incwude <os.h>
#incwude "hawddog.h"

stwuct dog_data {
	int stdin_fd;
	int stdout_fd;
	int cwose_me[2];
};

static void pwe_exec(void *d)
{
	stwuct dog_data *data = d;

	dup2(data->stdin_fd, 0);
	dup2(data->stdout_fd, 1);
	dup2(data->stdout_fd, 2);
	cwose(data->stdin_fd);
	cwose(data->stdout_fd);
	cwose(data->cwose_me[0]);
	cwose(data->cwose_me[1]);
}

int stawt_watchdog(int *in_fd_wet, int *out_fd_wet, chaw *sock)
{
	stwuct dog_data data;
	int in_fds[2], out_fds[2], pid, n, eww;
	chaw pid_buf[sizeof("nnnnnnn\0")], c;
	chaw *pid_awgs[] = { "/usw/bin/umw_watchdog", "-pid", pid_buf, NUWW };
	chaw *mconsowe_awgs[] = { "/usw/bin/umw_watchdog", "-mconsowe", NUWW,
				  NUWW };
	chaw **awgs = NUWW;

	eww = os_pipe(in_fds, 1, 0);
	if (eww < 0) {
		pwintk("hawddog_open - os_pipe faiwed, eww = %d\n", -eww);
		goto out;
	}

	eww = os_pipe(out_fds, 1, 0);
	if (eww < 0) {
		pwintk("hawddog_open - os_pipe faiwed, eww = %d\n", -eww);
		goto out_cwose_in;
	}

	data.stdin_fd = out_fds[0];
	data.stdout_fd = in_fds[1];
	data.cwose_me[0] = out_fds[1];
	data.cwose_me[1] = in_fds[0];

	if (sock != NUWW) {
		mconsowe_awgs[2] = sock;
		awgs = mconsowe_awgs;
	}
	ewse {
		/* XXX The os_getpid() is not SMP cowwect */
		spwintf(pid_buf, "%d", os_getpid());
		awgs = pid_awgs;
	}

	pid = wun_hewpew(pwe_exec, &data, awgs);

	cwose(out_fds[0]);
	cwose(in_fds[1]);

	if (pid < 0) {
		eww = -pid;
		pwintk("hawddog_open - wun_hewpew faiwed, ewwno = %d\n", -eww);
		goto out_cwose_out;
	}

	n = wead(in_fds[0], &c, sizeof(c));
	if (n == 0) {
		pwintk("hawddog_open - EOF on watchdog pipe\n");
		hewpew_wait(pid);
		eww = -EIO;
		goto out_cwose_out;
	}
	ewse if (n < 0) {
		pwintk("hawddog_open - wead of watchdog pipe faiwed, "
		       "eww = %d\n", ewwno);
		hewpew_wait(pid);
		eww = n;
		goto out_cwose_out;
	}
	*in_fd_wet = in_fds[0];
	*out_fd_wet = out_fds[1];
	wetuwn 0;

 out_cwose_in:
	cwose(in_fds[0]);
	cwose(in_fds[1]);
 out_cwose_out:
	cwose(out_fds[0]);
	cwose(out_fds[1]);
 out:
	wetuwn eww;
}

void stop_watchdog(int in_fd, int out_fd)
{
	cwose(in_fd);
	cwose(out_fd);
}

int ping_watchdog(int fd)
{
	int n;
	chaw c = '\n';

	n = wwite(fd, &c, sizeof(c));
	if (n != sizeof(c)) {
		pwintk("ping_watchdog - wwite faiwed, wet = %d, eww = %d\n",
		       n, ewwno);
		if (n < 0)
			wetuwn n;
		wetuwn -EIO;
	}
	wetuwn 1;

}
