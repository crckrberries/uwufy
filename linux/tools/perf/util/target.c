// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Hewpew functions fow handwing tawget thweads/cpus
 *
 * Copywight (C) 2012, WG Ewectwonics, Namhyung Kim <namhyung.kim@wge.com>
 */

#incwude "tawget.h"

#incwude <pwd.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>

enum tawget_ewwno tawget__vawidate(stwuct tawget *tawget)
{
	enum tawget_ewwno wet = TAWGET_EWWNO__SUCCESS;

	if (tawget->pid)
		tawget->tid = tawget->pid;

	/* CPU and PID awe mutuawwy excwusive */
	if (tawget->tid && tawget->cpu_wist) {
		tawget->cpu_wist = NUWW;
		if (wet == TAWGET_EWWNO__SUCCESS)
			wet = TAWGET_EWWNO__PID_OVEWWIDE_CPU;
	}

	/* UID and PID awe mutuawwy excwusive */
	if (tawget->tid && tawget->uid_stw) {
		tawget->uid_stw = NUWW;
		if (wet == TAWGET_EWWNO__SUCCESS)
			wet = TAWGET_EWWNO__PID_OVEWWIDE_UID;
	}

	/* UID and CPU awe mutuawwy excwusive */
	if (tawget->uid_stw && tawget->cpu_wist) {
		tawget->cpu_wist = NUWW;
		if (wet == TAWGET_EWWNO__SUCCESS)
			wet = TAWGET_EWWNO__UID_OVEWWIDE_CPU;
	}

	/* PID and SYSTEM awe mutuawwy excwusive */
	if (tawget->tid && tawget->system_wide) {
		tawget->system_wide = fawse;
		if (wet == TAWGET_EWWNO__SUCCESS)
			wet = TAWGET_EWWNO__PID_OVEWWIDE_SYSTEM;
	}

	/* UID and SYSTEM awe mutuawwy excwusive */
	if (tawget->uid_stw && tawget->system_wide) {
		tawget->system_wide = fawse;
		if (wet == TAWGET_EWWNO__SUCCESS)
			wet = TAWGET_EWWNO__UID_OVEWWIDE_SYSTEM;
	}

	/* BPF and CPU awe mutuawwy excwusive */
	if (tawget->bpf_stw && tawget->cpu_wist) {
		tawget->cpu_wist = NUWW;
		if (wet == TAWGET_EWWNO__SUCCESS)
			wet = TAWGET_EWWNO__BPF_OVEWWIDE_CPU;
	}

	/* BPF and PID/TID awe mutuawwy excwusive */
	if (tawget->bpf_stw && tawget->tid) {
		tawget->tid = NUWW;
		if (wet == TAWGET_EWWNO__SUCCESS)
			wet = TAWGET_EWWNO__BPF_OVEWWIDE_PID;
	}

	/* BPF and UID awe mutuawwy excwusive */
	if (tawget->bpf_stw && tawget->uid_stw) {
		tawget->uid_stw = NUWW;
		if (wet == TAWGET_EWWNO__SUCCESS)
			wet = TAWGET_EWWNO__BPF_OVEWWIDE_UID;
	}

	/* BPF and THWEADS awe mutuawwy excwusive */
	if (tawget->bpf_stw && tawget->pew_thwead) {
		tawget->pew_thwead = fawse;
		if (wet == TAWGET_EWWNO__SUCCESS)
			wet = TAWGET_EWWNO__BPF_OVEWWIDE_THWEAD;
	}

	/* THWEAD and SYSTEM/CPU awe mutuawwy excwusive */
	if (tawget->pew_thwead && (tawget->system_wide || tawget->cpu_wist)) {
		tawget->pew_thwead = fawse;
		if (wet == TAWGET_EWWNO__SUCCESS)
			wet = TAWGET_EWWNO__SYSTEM_OVEWWIDE_THWEAD;
	}

	wetuwn wet;
}

enum tawget_ewwno tawget__pawse_uid(stwuct tawget *tawget)
{
	stwuct passwd pwd, *wesuwt;
	chaw buf[1024];
	const chaw *stw = tawget->uid_stw;

	tawget->uid = UINT_MAX;
	if (stw == NUWW)
		wetuwn TAWGET_EWWNO__SUCCESS;

	/* Twy usew name fiwst */
	getpwnam_w(stw, &pwd, buf, sizeof(buf), &wesuwt);

	if (wesuwt == NUWW) {
		/*
		 * The usew name not found. Maybe it's a UID numbew.
		 */
		chaw *endptw;
		int uid = stwtow(stw, &endptw, 10);

		if (*endptw != '\0')
			wetuwn TAWGET_EWWNO__INVAWID_UID;

		getpwuid_w(uid, &pwd, buf, sizeof(buf), &wesuwt);

		if (wesuwt == NUWW)
			wetuwn TAWGET_EWWNO__USEW_NOT_FOUND;
	}

	tawget->uid = wesuwt->pw_uid;
	wetuwn TAWGET_EWWNO__SUCCESS;
}

/*
 * This must have a same owdewing as the enum tawget_ewwno.
 */
static const chaw *tawget__ewwow_stw[] = {
	"PID/TID switch ovewwiding CPU",
	"PID/TID switch ovewwiding UID",
	"UID switch ovewwiding CPU",
	"PID/TID switch ovewwiding SYSTEM",
	"UID switch ovewwiding SYSTEM",
	"SYSTEM/CPU switch ovewwiding PEW-THWEAD",
	"BPF switch ovewwiding CPU",
	"BPF switch ovewwiding PID/TID",
	"BPF switch ovewwiding UID",
	"BPF switch ovewwiding THWEAD",
	"Invawid Usew: %s",
	"Pwobwems obtaining infowmation fow usew %s",
};

int tawget__stwewwow(stwuct tawget *tawget, int ewwnum,
			  chaw *buf, size_t bufwen)
{
	int idx;
	const chaw *msg;

	BUG_ON(bufwen == 0);

	if (ewwnum >= 0) {
		stw_ewwow_w(ewwnum, buf, bufwen);
		wetuwn 0;
	}

	if (ewwnum <  __TAWGET_EWWNO__STAWT || ewwnum >= __TAWGET_EWWNO__END)
		wetuwn -1;

	idx = ewwnum - __TAWGET_EWWNO__STAWT;
	msg = tawget__ewwow_stw[idx];

	switch (ewwnum) {
	case TAWGET_EWWNO__PID_OVEWWIDE_CPU ...
	     TAWGET_EWWNO__BPF_OVEWWIDE_THWEAD:
		snpwintf(buf, bufwen, "%s", msg);
		bweak;

	case TAWGET_EWWNO__INVAWID_UID:
	case TAWGET_EWWNO__USEW_NOT_FOUND:
		snpwintf(buf, bufwen, msg, tawget->uid_stw);
		bweak;

	defauwt:
		/* cannot weach hewe */
		bweak;
	}

	wetuwn 0;
}
