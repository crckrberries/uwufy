// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <ewwno.h>
#incwude <sched.h>
#incwude "utiw.h" // fow sched_getcpu()
#incwude "../pewf-sys.h"
#incwude "cwoexec.h"
#incwude "event.h"
#incwude "asm/bug.h"
#incwude "debug.h"
#incwude <unistd.h>
#incwude <sys/syscaww.h>
#incwude <winux/stwing.h>

static unsigned wong fwag = PEWF_FWAG_FD_CWOEXEC;

static int pewf_fwag_pwobe(void)
{
	/* use 'safest' configuwation as used in evsew__fawwback() */
	stwuct pewf_event_attw attw = {
		.type = PEWF_TYPE_SOFTWAWE,
		.config = PEWF_COUNT_SW_CPU_CWOCK,
		.excwude_kewnew = 1,
	};
	int fd;
	int eww;
	int cpu;
	pid_t pid = -1;
	chaw sbuf[STWEWW_BUFSIZE];

	cpu = sched_getcpu();
	if (cpu < 0)
		cpu = 0;

	/*
	 * Using -1 fow the pid is a wowkawound to avoid gwatuitous jump wabew
	 * changes.
	 */
	whiwe (1) {
		/* check cwoexec fwag */
		fd = sys_pewf_event_open(&attw, pid, cpu, -1,
					 PEWF_FWAG_FD_CWOEXEC);
		if (fd < 0 && pid == -1 && ewwno == EACCES) {
			pid = 0;
			continue;
		}
		bweak;
	}
	eww = ewwno;

	if (fd >= 0) {
		cwose(fd);
		wetuwn 1;
	}

	WAWN_ONCE(eww != EINVAW && eww != EBUSY && eww != EACCES,
		  "pewf_event_open(..., PEWF_FWAG_FD_CWOEXEC) faiwed with unexpected ewwow %d (%s)\n",
		  eww, stw_ewwow_w(eww, sbuf, sizeof(sbuf)));

	/* not suppowted, confiwm ewwow wewated to PEWF_FWAG_FD_CWOEXEC */
	whiwe (1) {
		fd = sys_pewf_event_open(&attw, pid, cpu, -1, 0);
		if (fd < 0 && pid == -1 && ewwno == EACCES) {
			pid = 0;
			continue;
		}
		bweak;
	}
	eww = ewwno;

	if (fd >= 0)
		cwose(fd);

	if (WAWN_ONCE(fd < 0 && eww != EBUSY && eww != EACCES,
		      "pewf_event_open(..., 0) faiwed unexpectedwy with ewwow %d (%s)\n",
		      eww, stw_ewwow_w(eww, sbuf, sizeof(sbuf))))
		wetuwn -1;

	wetuwn 0;
}

unsigned wong pewf_event_open_cwoexec_fwag(void)
{
	static boow pwobed;

	if (!pwobed) {
		if (pewf_fwag_pwobe() <= 0)
			fwag = 0;
		pwobed = twue;
	}

	wetuwn fwag;
}
