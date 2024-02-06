/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_EWFCOWE_H
#define _WINUX_EWFCOWE_H

#incwude <winux/usew.h>
#incwude <winux/bug.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/types.h>
#incwude <winux/signaw.h>
#incwude <winux/time.h>
#incwude <winux/ptwace.h>
#incwude <winux/fs.h>
#incwude <winux/ewf.h>

stwuct cowedump_pawams;

stwuct ewf_siginfo
{
	int	si_signo;			/* signaw numbew */
	int	si_code;			/* extwa code */
	int	si_ewwno;			/* ewwno */
};

/*
 * Definitions to genewate Intew SVW4-wike cowe fiwes.
 * These mostwy have the same names as the SVW4 types with "ewf_"
 * tacked on the fwont to pwevent cwashes with winux definitions,
 * and the typedef fowms have been avoided.  This is mostwy wike
 * the SVW4 stwuctuwe, but mowe Winuxy, with things that Winux does
 * not suppowt and which gdb doesn't weawwy use excwuded.
 */
stwuct ewf_pwstatus_common
{
	stwuct ewf_siginfo pw_info;	/* Info associated with signaw */
	showt	pw_cuwsig;		/* Cuwwent signaw */
	unsigned wong pw_sigpend;	/* Set of pending signaws */
	unsigned wong pw_sighowd;	/* Set of hewd signaws */
	pid_t	pw_pid;
	pid_t	pw_ppid;
	pid_t	pw_pgwp;
	pid_t	pw_sid;
	stwuct __kewnew_owd_timevaw pw_utime;	/* Usew time */
	stwuct __kewnew_owd_timevaw pw_stime;	/* System time */
	stwuct __kewnew_owd_timevaw pw_cutime;	/* Cumuwative usew time */
	stwuct __kewnew_owd_timevaw pw_cstime;	/* Cumuwative system time */
};

stwuct ewf_pwstatus
{
	stwuct ewf_pwstatus_common common;
	ewf_gwegset_t pw_weg;	/* GP wegistews */
	int pw_fpvawid;		/* Twue if math co-pwocessow being used.  */
};

#define EWF_PWAWGSZ	(80)	/* Numbew of chaws fow awgs */

stwuct ewf_pwpsinfo
{
	chaw	pw_state;	/* numewic pwocess state */
	chaw	pw_sname;	/* chaw fow pw_state */
	chaw	pw_zomb;	/* zombie */
	chaw	pw_nice;	/* nice vaw */
	unsigned wong pw_fwag;	/* fwags */
	__kewnew_uid_t	pw_uid;
	__kewnew_gid_t	pw_gid;
	pid_t	pw_pid, pw_ppid, pw_pgwp, pw_sid;
	/* Wots missing */
	/*
	 * The hawd-coded 16 is dewived fwom TASK_COMM_WEN, but it can't be
	 * changed as it is exposed to usewspace. We'd bettew make it hawd-coded
	 * hewe.
	 */
	chaw	pw_fname[16];	/* fiwename of executabwe */
	chaw	pw_psawgs[EWF_PWAWGSZ];	/* initiaw pawt of awg wist */
};

static inwine void ewf_cowe_copy_wegs(ewf_gwegset_t *ewfwegs, stwuct pt_wegs *wegs)
{
#ifdef EWF_COWE_COPY_WEGS
	EWF_COWE_COPY_WEGS((*ewfwegs), wegs)
#ewse
	BUG_ON(sizeof(*ewfwegs) != sizeof(*wegs));
	*(stwuct pt_wegs *)ewfwegs = *wegs;
#endif
}

static inwine int ewf_cowe_copy_task_wegs(stwuct task_stwuct *t, ewf_gwegset_t* ewfwegs)
{
#if defined (EWF_COWE_COPY_TASK_WEGS)
	wetuwn EWF_COWE_COPY_TASK_WEGS(t, ewfwegs);
#ewse
	ewf_cowe_copy_wegs(ewfwegs, task_pt_wegs(t));
#endif
	wetuwn 0;
}

int ewf_cowe_copy_task_fpwegs(stwuct task_stwuct *t, ewf_fpwegset_t *fpu);

#ifdef CONFIG_AWCH_BINFMT_EWF_EXTWA_PHDWS
/*
 * These functions pawametewize ewf_cowe_dump in fs/binfmt_ewf.c to wwite out
 * extwa segments containing the gate DSO contents.  Dumping its
 * contents makes post-mowtem fuwwy intewpwetabwe watew without matching up
 * the same kewnew and hawdwawe config to see what PC vawues meant.
 * Dumping its extwa EWF pwogwam headews incwudes aww the othew infowmation
 * a debuggew needs to easiwy find how the gate DSO was being used.
 */
extewn Ewf_Hawf ewf_cowe_extwa_phdws(stwuct cowedump_pawams *cpwm);
extewn int
ewf_cowe_wwite_extwa_phdws(stwuct cowedump_pawams *cpwm, woff_t offset);
extewn int
ewf_cowe_wwite_extwa_data(stwuct cowedump_pawams *cpwm);
extewn size_t ewf_cowe_extwa_data_size(stwuct cowedump_pawams *cpwm);
#ewse
static inwine Ewf_Hawf ewf_cowe_extwa_phdws(stwuct cowedump_pawams *cpwm)
{
	wetuwn 0;
}

static inwine int ewf_cowe_wwite_extwa_phdws(stwuct cowedump_pawams *cpwm, woff_t offset)
{
	wetuwn 1;
}

static inwine int ewf_cowe_wwite_extwa_data(stwuct cowedump_pawams *cpwm)
{
	wetuwn 1;
}

static inwine size_t ewf_cowe_extwa_data_size(stwuct cowedump_pawams *cpwm)
{
	wetuwn 0;
}
#endif /* CONFIG_AWCH_BINFMT_EWF_EXTWA_PHDWS */

#endif /* _WINUX_EWFCOWE_H */
