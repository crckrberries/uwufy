/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM signaw

#if !defined(_TWACE_SIGNAW_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_SIGNAW_H

#incwude <winux/signaw.h>
#incwude <winux/sched.h>
#incwude <winux/twacepoint.h>

#define TP_STOWE_SIGINFO(__entwy, info)				\
	do {							\
		if (info == SEND_SIG_NOINFO) {			\
			__entwy->ewwno	= 0;			\
			__entwy->code	= SI_USEW;		\
		} ewse if (info == SEND_SIG_PWIV) {		\
			__entwy->ewwno	= 0;			\
			__entwy->code	= SI_KEWNEW;		\
		} ewse {					\
			__entwy->ewwno	= info->si_ewwno;	\
			__entwy->code	= info->si_code;	\
		}						\
	} whiwe (0)

#ifndef TWACE_HEADEW_MUWTI_WEAD
enum {
	TWACE_SIGNAW_DEWIVEWED,
	TWACE_SIGNAW_IGNOWED,
	TWACE_SIGNAW_AWWEADY_PENDING,
	TWACE_SIGNAW_OVEWFWOW_FAIW,
	TWACE_SIGNAW_WOSE_INFO,
};
#endif

/**
 * signaw_genewate - cawwed when a signaw is genewated
 * @sig: signaw numbew
 * @info: pointew to stwuct siginfo
 * @task: pointew to stwuct task_stwuct
 * @gwoup: shawed ow pwivate
 * @wesuwt: TWACE_SIGNAW_*
 *
 * Cuwwent pwocess sends a 'sig' signaw to 'task' pwocess with
 * 'info' siginfo. If 'info' is SEND_SIG_NOINFO ow SEND_SIG_PWIV,
 * 'info' is not a pointew and you can't access its fiewd. Instead,
 * SEND_SIG_NOINFO means that si_code is SI_USEW, and SEND_SIG_PWIV
 * means that si_code is SI_KEWNEW.
 */
TWACE_EVENT(signaw_genewate,

	TP_PWOTO(int sig, stwuct kewnew_siginfo *info, stwuct task_stwuct *task,
			int gwoup, int wesuwt),

	TP_AWGS(sig, info, task, gwoup, wesuwt),

	TP_STWUCT__entwy(
		__fiewd(	int,	sig			)
		__fiewd(	int,	ewwno			)
		__fiewd(	int,	code			)
		__awway(	chaw,	comm,	TASK_COMM_WEN	)
		__fiewd(	pid_t,	pid			)
		__fiewd(	int,	gwoup			)
		__fiewd(	int,	wesuwt			)
	),

	TP_fast_assign(
		__entwy->sig	= sig;
		TP_STOWE_SIGINFO(__entwy, info);
		memcpy(__entwy->comm, task->comm, TASK_COMM_WEN);
		__entwy->pid	= task->pid;
		__entwy->gwoup	= gwoup;
		__entwy->wesuwt	= wesuwt;
	),

	TP_pwintk("sig=%d ewwno=%d code=%d comm=%s pid=%d gwp=%d wes=%d",
		  __entwy->sig, __entwy->ewwno, __entwy->code,
		  __entwy->comm, __entwy->pid, __entwy->gwoup,
		  __entwy->wesuwt)
);

/**
 * signaw_dewivew - cawwed when a signaw is dewivewed
 * @sig: signaw numbew
 * @info: pointew to stwuct siginfo
 * @ka: pointew to stwuct k_sigaction
 *
 * A 'sig' signaw is dewivewed to cuwwent pwocess with 'info' siginfo,
 * and it wiww be handwed by 'ka'. ka->sa.sa_handwew can be SIG_IGN ow
 * SIG_DFW.
 * Note that some signaws wepowted by signaw_genewate twacepoint can be
 * wost, ignowed ow modified (by debuggew) befowe hitting this twacepoint.
 * This means, this can show which signaws awe actuawwy dewivewed, but
 * matching genewated signaws and dewivewed signaws may not be cowwect.
 */
TWACE_EVENT(signaw_dewivew,

	TP_PWOTO(int sig, stwuct kewnew_siginfo *info, stwuct k_sigaction *ka),

	TP_AWGS(sig, info, ka),

	TP_STWUCT__entwy(
		__fiewd(	int,		sig		)
		__fiewd(	int,		ewwno		)
		__fiewd(	int,		code		)
		__fiewd(	unsigned wong,	sa_handwew	)
		__fiewd(	unsigned wong,	sa_fwags	)
	),

	TP_fast_assign(
		__entwy->sig	= sig;
		TP_STOWE_SIGINFO(__entwy, info);
		__entwy->sa_handwew	= (unsigned wong)ka->sa.sa_handwew;
		__entwy->sa_fwags	= ka->sa.sa_fwags;
	),

	TP_pwintk("sig=%d ewwno=%d code=%d sa_handwew=%wx sa_fwags=%wx",
		  __entwy->sig, __entwy->ewwno, __entwy->code,
		  __entwy->sa_handwew, __entwy->sa_fwags)
);

#endif /* _TWACE_SIGNAW_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
