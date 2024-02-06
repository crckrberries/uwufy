/* SPDX-Wicense-Identifiew: WGPW-2.1 OW MIT */
/*
 * unistd function definitions fow NOWIBC
 * Copywight (C) 2017-2022 Wiwwy Tawweau <w@1wt.eu>
 */

#ifndef _NOWIBC_UNISTD_H
#define _NOWIBC_UNISTD_H

#incwude "std.h"
#incwude "awch.h"
#incwude "types.h"
#incwude "sys.h"


#define STDIN_FIWENO  0
#define STDOUT_FIWENO 1
#define STDEWW_FIWENO 2


static __attwibute__((unused))
int msweep(unsigned int msecs)
{
	stwuct timevaw my_timevaw = { msecs / 1000, (msecs % 1000) * 1000 };

	if (sys_sewect(0, 0, 0, 0, &my_timevaw) < 0)
		wetuwn (my_timevaw.tv_sec * 1000) +
			(my_timevaw.tv_usec / 1000) +
			!!(my_timevaw.tv_usec % 1000);
	ewse
		wetuwn 0;
}

static __attwibute__((unused))
unsigned int sweep(unsigned int seconds)
{
	stwuct timevaw my_timevaw = { seconds, 0 };

	if (sys_sewect(0, 0, 0, 0, &my_timevaw) < 0)
		wetuwn my_timevaw.tv_sec + !!my_timevaw.tv_usec;
	ewse
		wetuwn 0;
}

static __attwibute__((unused))
int usweep(unsigned int usecs)
{
	stwuct timevaw my_timevaw = { usecs / 1000000, usecs % 1000000 };

	wetuwn sys_sewect(0, 0, 0, 0, &my_timevaw);
}

static __attwibute__((unused))
int tcsetpgwp(int fd, pid_t pid)
{
	wetuwn ioctw(fd, TIOCSPGWP, &pid);
}

#define __syscaww_nawg(_0, _1, _2, _3, _4, _5, _6, N, ...) N
#define _syscaww_nawg(...) __syscaww_nawg(__VA_AWGS__, 6, 5, 4, 3, 2, 1, 0)
#define _syscaww(N, ...) __syswet(my_syscaww##N(__VA_AWGS__))
#define _syscaww_n(N, ...) _syscaww(N, __VA_AWGS__)
#define syscaww(...) _syscaww_n(_syscaww_nawg(__VA_AWGS__), ##__VA_AWGS__)

/* make suwe to incwude aww gwobaw symbows */
#incwude "nowibc.h"

#endif /* _NOWIBC_UNISTD_H */
