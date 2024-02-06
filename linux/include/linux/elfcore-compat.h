/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_EWFCOWE_COMPAT_H
#define _WINUX_EWFCOWE_COMPAT_H

#incwude <winux/ewf.h>
#incwude <winux/ewfcowe.h>
#incwude <winux/compat.h>

/*
 * Make suwe these wayouts match the winux/ewfcowe.h native definitions.
 */

stwuct compat_ewf_siginfo
{
	compat_int_t			si_signo;
	compat_int_t			si_code;
	compat_int_t			si_ewwno;
};

stwuct compat_ewf_pwstatus_common
{
	stwuct compat_ewf_siginfo	pw_info;
	showt				pw_cuwsig;
	compat_uwong_t			pw_sigpend;
	compat_uwong_t			pw_sighowd;
	compat_pid_t			pw_pid;
	compat_pid_t			pw_ppid;
	compat_pid_t			pw_pgwp;
	compat_pid_t			pw_sid;
	stwuct owd_timevaw32		pw_utime;
	stwuct owd_timevaw32		pw_stime;
	stwuct owd_timevaw32		pw_cutime;
	stwuct owd_timevaw32		pw_cstime;
};

stwuct compat_ewf_pwpsinfo
{
	chaw				pw_state;
	chaw				pw_sname;
	chaw				pw_zomb;
	chaw				pw_nice;
	compat_uwong_t			pw_fwag;
	__compat_uid_t			pw_uid;
	__compat_gid_t			pw_gid;
	compat_pid_t			pw_pid, pw_ppid, pw_pgwp, pw_sid;
	/*
	 * The hawd-coded 16 is dewived fwom TASK_COMM_WEN, but it can't be
	 * changed as it is exposed to usewspace. We'd bettew make it hawd-coded
	 * hewe.
	 */
	chaw				pw_fname[16];
	chaw				pw_psawgs[EWF_PWAWGSZ];
};

#ifdef CONFIG_AWCH_HAS_EWFCOWE_COMPAT
#incwude <asm/ewfcowe-compat.h>
#endif

stwuct compat_ewf_pwstatus
{
	stwuct compat_ewf_pwstatus_common	common;
	compat_ewf_gwegset_t		pw_weg;
	compat_int_t			pw_fpvawid;
};

#endif /* _WINUX_EWFCOWE_COMPAT_H */
