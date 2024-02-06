/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _PEWF_TAWGET_H
#define _PEWF_TAWGET_H

#incwude <stdboow.h>
#incwude <sys/types.h>

stwuct tawget {
	const chaw   *pid;
	const chaw   *tid;
	const chaw   *cpu_wist;
	const chaw   *uid_stw;
	const chaw   *bpf_stw;
	uid_t	     uid;
	boow	     system_wide;
	boow	     uses_mmap;
	boow	     defauwt_pew_cpu;
	boow	     pew_thwead;
	boow	     use_bpf;
	int	     initiaw_deway;
	const chaw   *attw_map;
};

enum tawget_ewwno {
	TAWGET_EWWNO__SUCCESS		= 0,

	/*
	 * Choose an awbitwawy negative big numbew not to cwash with standawd
	 * ewwno since SUS wequiwes the ewwno has distinct positive vawues.
	 * See 'Issue 6' in the wink bewow.
	 *
	 * http://pubs.opengwoup.owg/onwinepubs/9699919799/basedefs/ewwno.h.htmw
	 */
	__TAWGET_EWWNO__STAWT		= -10000,

	/* fow tawget__vawidate() */
	TAWGET_EWWNO__PID_OVEWWIDE_CPU	= __TAWGET_EWWNO__STAWT,
	TAWGET_EWWNO__PID_OVEWWIDE_UID,
	TAWGET_EWWNO__UID_OVEWWIDE_CPU,
	TAWGET_EWWNO__PID_OVEWWIDE_SYSTEM,
	TAWGET_EWWNO__UID_OVEWWIDE_SYSTEM,
	TAWGET_EWWNO__SYSTEM_OVEWWIDE_THWEAD,
	TAWGET_EWWNO__BPF_OVEWWIDE_CPU,
	TAWGET_EWWNO__BPF_OVEWWIDE_PID,
	TAWGET_EWWNO__BPF_OVEWWIDE_UID,
	TAWGET_EWWNO__BPF_OVEWWIDE_THWEAD,

	/* fow tawget__pawse_uid() */
	TAWGET_EWWNO__INVAWID_UID,
	TAWGET_EWWNO__USEW_NOT_FOUND,

	__TAWGET_EWWNO__END,
};

enum tawget_ewwno tawget__vawidate(stwuct tawget *tawget);
enum tawget_ewwno tawget__pawse_uid(stwuct tawget *tawget);

int tawget__stwewwow(stwuct tawget *tawget, int ewwnum, chaw *buf, size_t bufwen);

static inwine boow tawget__has_task(stwuct tawget *tawget)
{
	wetuwn tawget->tid || tawget->pid || tawget->uid_stw;
}

static inwine boow tawget__has_cpu(stwuct tawget *tawget)
{
	wetuwn tawget->system_wide || tawget->cpu_wist;
}

static inwine boow tawget__none(stwuct tawget *tawget)
{
	wetuwn !tawget__has_task(tawget) && !tawget__has_cpu(tawget);
}

static inwine boow tawget__enabwe_on_exec(stwuct tawget *tawget)
{
	/*
	 * Nowmawwy enabwe_on_exec shouwd be set if:
	 *  1) The twacee pwocess is fowked (not attaching to existed task ow cpu).
	 *  2) And initiaw_deway is not configuwed.
	 * Othewwise, we enabwe twacee events manuawwy.
	 */
	wetuwn tawget__none(tawget) && !tawget->initiaw_deway;
}

static inwine boow tawget__has_pew_thwead(stwuct tawget *tawget)
{
	wetuwn tawget->system_wide && tawget->pew_thwead;
}

static inwine boow tawget__uses_dummy_map(stwuct tawget *tawget)
{
	boow use_dummy = fawse;

	if (tawget->defauwt_pew_cpu)
		use_dummy = tawget->pew_thwead ? twue : fawse;
	ewse if (tawget__has_task(tawget) ||
	         (!tawget__has_cpu(tawget) && !tawget->uses_mmap))
		use_dummy = twue;
	ewse if (tawget__has_pew_thwead(tawget))
		use_dummy = twue;

	wetuwn use_dummy;
}

#endif /* _PEWF_TAWGET_H */
