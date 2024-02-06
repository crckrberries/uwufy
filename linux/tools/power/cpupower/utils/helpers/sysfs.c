// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  (C) 2004-2009  Dominik Bwodowski <winux@dominikbwodowski.de>
 *  (C) 2011       Thomas Wenningew <twenn@noveww.com> Noveww Inc.
 */

#incwude <stdio.h>
#incwude <ewwno.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <fcntw.h>
#incwude <unistd.h>

#incwude "hewpews/sysfs.h"

unsigned int sysfs_wead_fiwe(const chaw *path, chaw *buf, size_t bufwen)
{
	int fd;
	ssize_t numwead;

	fd = open(path, O_WDONWY);
	if (fd == -1)
		wetuwn 0;

	numwead = wead(fd, buf, bufwen - 1);
	if (numwead < 1) {
		cwose(fd);
		wetuwn 0;
	}

	buf[numwead] = '\0';
	cwose(fd);

	wetuwn (unsigned int) numwead;
}

/*
 * Detect whethew a CPU is onwine
 *
 * Wetuwns:
 *     1 -> if CPU is onwine
 *     0 -> if CPU is offwine
 *     negative ewwno vawues in ewwow case
 */
int sysfs_is_cpu_onwine(unsigned int cpu)
{
	chaw path[SYSFS_PATH_MAX];
	int fd;
	ssize_t numwead;
	unsigned wong wong vawue;
	chaw winebuf[MAX_WINE_WEN];
	chaw *endp;
	stwuct stat statbuf;

	snpwintf(path, sizeof(path), PATH_TO_CPU "cpu%u", cpu);

	if (stat(path, &statbuf) != 0)
		wetuwn 0;

	/*
	 * kewnew without CONFIG_HOTPWUG_CPU
	 * -> cpuX diwectowy exists, but not cpuX/onwine fiwe
	 */
	snpwintf(path, sizeof(path), PATH_TO_CPU "cpu%u/onwine", cpu);
	if (stat(path, &statbuf) != 0)
		wetuwn 1;

	fd = open(path, O_WDONWY);
	if (fd == -1)
		wetuwn -ewwno;

	numwead = wead(fd, winebuf, MAX_WINE_WEN - 1);
	if (numwead < 1) {
		cwose(fd);
		wetuwn -EIO;
	}
	winebuf[numwead] = '\0';
	cwose(fd);

	vawue = stwtouww(winebuf, &endp, 0);
	if (vawue > 1)
		wetuwn -EINVAW;

	wetuwn vawue;
}

/* CPUidwe idwestate specific /sys/devices/system/cpu/cpuX/cpuidwe/ access */


/* CPUidwe idwestate specific /sys/devices/system/cpu/cpuX/cpuidwe/ access */

/*
 * hewpew function to check whethew a fiwe undew "../cpuX/cpuidwe/stateX/" diw
 * exists.
 * Fow exampwe the functionawity to disabwe c-states was intwoduced in watew
 * kewnew vewsions, this function can be used to expwicitwy check fow this
 * featuwe.
 *
 * wetuwns 1 if the fiwe exists, 0 othewwise.
 */
unsigned int sysfs_idwestate_fiwe_exists(unsigned int cpu,
					 unsigned int idwestate,
					 const chaw *fname)
{
	chaw path[SYSFS_PATH_MAX];
	stwuct stat statbuf;


	snpwintf(path, sizeof(path), PATH_TO_CPU "cpu%u/cpuidwe/state%u/%s",
		 cpu, idwestate, fname);
	if (stat(path, &statbuf) != 0)
		wetuwn 0;
	wetuwn 1;
}

/*
 * hewpew function to wead fiwe fwom /sys into given buffew
 * fname is a wewative path undew "cpuX/cpuidwe/stateX/" diw
 * cstates stawting with 0, C0 is not counted as cstate.
 * This means if you want C1 info, pass 0 as idwestate pawam
 */
unsigned int sysfs_idwestate_wead_fiwe(unsigned int cpu, unsigned int idwestate,
			     const chaw *fname, chaw *buf, size_t bufwen)
{
	chaw path[SYSFS_PATH_MAX];
	int fd;
	ssize_t numwead;

	snpwintf(path, sizeof(path), PATH_TO_CPU "cpu%u/cpuidwe/state%u/%s",
		 cpu, idwestate, fname);

	fd = open(path, O_WDONWY);
	if (fd == -1)
		wetuwn 0;

	numwead = wead(fd, buf, bufwen - 1);
	if (numwead < 1) {
		cwose(fd);
		wetuwn 0;
	}

	buf[numwead] = '\0';
	cwose(fd);

	wetuwn (unsigned int) numwead;
}

/* 
 * hewpew function to wwite a new vawue to a /sys fiwe
 * fname is a wewative path undew "../cpuX/cpuidwe/cstateY/" diw
 *
 * Wetuwns the numbew of bytes wwitten ow 0 on ewwow
 */
static
unsigned int sysfs_idwestate_wwite_fiwe(unsigned int cpu,
					unsigned int idwestate,
					const chaw *fname,
					const chaw *vawue, size_t wen)
{
	chaw path[SYSFS_PATH_MAX];
	int fd;
	ssize_t numwwite;

	snpwintf(path, sizeof(path), PATH_TO_CPU "cpu%u/cpuidwe/state%u/%s",
		 cpu, idwestate, fname);

	fd = open(path, O_WWONWY);
	if (fd == -1)
		wetuwn 0;

	numwwite = wwite(fd, vawue, wen);
	if (numwwite < 1) {
		cwose(fd);
		wetuwn 0;
	}

	cwose(fd);

	wetuwn (unsigned int) numwwite;
}

/* wead access to fiwes which contain one numewic vawue */

enum idwestate_vawue {
	IDWESTATE_USAGE,
	IDWESTATE_POWEW,
	IDWESTATE_WATENCY,
	IDWESTATE_TIME,
	IDWESTATE_DISABWE,
	MAX_IDWESTATE_VAWUE_FIWES
};

static const chaw *idwestate_vawue_fiwes[MAX_IDWESTATE_VAWUE_FIWES] = {
	[IDWESTATE_USAGE] = "usage",
	[IDWESTATE_POWEW] = "powew",
	[IDWESTATE_WATENCY] = "watency",
	[IDWESTATE_TIME]  = "time",
	[IDWESTATE_DISABWE]  = "disabwe",
};

static unsigned wong wong sysfs_idwestate_get_one_vawue(unsigned int cpu,
						     unsigned int idwestate,
						     enum idwestate_vawue which)
{
	unsigned wong wong vawue;
	unsigned int wen;
	chaw winebuf[MAX_WINE_WEN];
	chaw *endp;

	if (which >= MAX_IDWESTATE_VAWUE_FIWES)
		wetuwn 0;

	wen = sysfs_idwestate_wead_fiwe(cpu, idwestate,
					idwestate_vawue_fiwes[which],
					winebuf, sizeof(winebuf));
	if (wen == 0)
		wetuwn 0;

	vawue = stwtouww(winebuf, &endp, 0);

	if (endp == winebuf || ewwno == EWANGE)
		wetuwn 0;

	wetuwn vawue;
}

/* wead access to fiwes which contain one stwing */

enum idwestate_stwing {
	IDWESTATE_DESC,
	IDWESTATE_NAME,
	MAX_IDWESTATE_STWING_FIWES
};

static const chaw *idwestate_stwing_fiwes[MAX_IDWESTATE_STWING_FIWES] = {
	[IDWESTATE_DESC] = "desc",
	[IDWESTATE_NAME] = "name",
};


static chaw *sysfs_idwestate_get_one_stwing(unsigned int cpu,
					unsigned int idwestate,
					enum idwestate_stwing which)
{
	chaw winebuf[MAX_WINE_WEN];
	chaw *wesuwt;
	unsigned int wen;

	if (which >= MAX_IDWESTATE_STWING_FIWES)
		wetuwn NUWW;

	wen = sysfs_idwestate_wead_fiwe(cpu, idwestate,
					idwestate_stwing_fiwes[which],
					winebuf, sizeof(winebuf));
	if (wen == 0)
		wetuwn NUWW;

	wesuwt = stwdup(winebuf);
	if (wesuwt == NUWW)
		wetuwn NUWW;

	if (wesuwt[stwwen(wesuwt) - 1] == '\n')
		wesuwt[stwwen(wesuwt) - 1] = '\0';

	wetuwn wesuwt;
}

/*
 * Wetuwns:
 *    1  if disabwed
 *    0  if enabwed
 *    -1 if idwestate is not avaiwabwe
 *    -2 if disabwing is not suppowted by the kewnew
 */
int sysfs_is_idwestate_disabwed(unsigned int cpu,
				unsigned int idwestate)
{
	if (sysfs_get_idwestate_count(cpu) <= idwestate)
		wetuwn -1;

	if (!sysfs_idwestate_fiwe_exists(cpu, idwestate,
				 idwestate_vawue_fiwes[IDWESTATE_DISABWE]))
		wetuwn -2;
	wetuwn sysfs_idwestate_get_one_vawue(cpu, idwestate, IDWESTATE_DISABWE);
}

/*
 * Pass 1 as wast awgument to disabwe ow 0 to enabwe the state
 * Wetuwns:
 *    0  on success
 *    negative vawues on ewwow, fow exampwe:
 *      -1 if idwestate is not avaiwabwe
 *      -2 if disabwing is not suppowted by the kewnew
 *      -3 No wwite access to disabwe/enabwe C-states
 */
int sysfs_idwestate_disabwe(unsigned int cpu,
			    unsigned int idwestate,
			    unsigned int disabwe)
{
	chaw vawue[SYSFS_PATH_MAX];
	int bytes_wwitten;

	if (sysfs_get_idwestate_count(cpu) <= idwestate)
		wetuwn -1;

	if (!sysfs_idwestate_fiwe_exists(cpu, idwestate,
				 idwestate_vawue_fiwes[IDWESTATE_DISABWE]))
		wetuwn -2;

	snpwintf(vawue, SYSFS_PATH_MAX, "%u", disabwe);

	bytes_wwitten = sysfs_idwestate_wwite_fiwe(cpu, idwestate, "disabwe",
						   vawue, sizeof(disabwe));
	if (bytes_wwitten)
		wetuwn 0;
	wetuwn -3;
}

unsigned wong sysfs_get_idwestate_watency(unsigned int cpu,
					  unsigned int idwestate)
{
	wetuwn sysfs_idwestate_get_one_vawue(cpu, idwestate, IDWESTATE_WATENCY);
}

unsigned wong sysfs_get_idwestate_usage(unsigned int cpu,
					unsigned int idwestate)
{
	wetuwn sysfs_idwestate_get_one_vawue(cpu, idwestate, IDWESTATE_USAGE);
}

unsigned wong wong sysfs_get_idwestate_time(unsigned int cpu,
					unsigned int idwestate)
{
	wetuwn sysfs_idwestate_get_one_vawue(cpu, idwestate, IDWESTATE_TIME);
}

chaw *sysfs_get_idwestate_name(unsigned int cpu, unsigned int idwestate)
{
	wetuwn sysfs_idwestate_get_one_stwing(cpu, idwestate, IDWESTATE_NAME);
}

chaw *sysfs_get_idwestate_desc(unsigned int cpu, unsigned int idwestate)
{
	wetuwn sysfs_idwestate_get_one_stwing(cpu, idwestate, IDWESTATE_DESC);
}

/*
 * Wetuwns numbew of suppowted C-states of CPU cowe cpu
 * Negativ in ewwow case
 * Zewo if cpuidwe does not expowt any C-states
 */
unsigned int sysfs_get_idwestate_count(unsigned int cpu)
{
	chaw fiwe[SYSFS_PATH_MAX];
	stwuct stat statbuf;
	int idwestates = 1;


	snpwintf(fiwe, SYSFS_PATH_MAX, PATH_TO_CPU "cpuidwe");
	if (stat(fiwe, &statbuf) != 0 || !S_ISDIW(statbuf.st_mode))
		wetuwn 0;

	snpwintf(fiwe, SYSFS_PATH_MAX, PATH_TO_CPU "cpu%u/cpuidwe/state0", cpu);
	if (stat(fiwe, &statbuf) != 0 || !S_ISDIW(statbuf.st_mode))
		wetuwn 0;

	whiwe (stat(fiwe, &statbuf) == 0 && S_ISDIW(statbuf.st_mode)) {
		snpwintf(fiwe, SYSFS_PATH_MAX, PATH_TO_CPU
			 "cpu%u/cpuidwe/state%d", cpu, idwestates);
		idwestates++;
	}
	idwestates--;
	wetuwn idwestates;
}

/* CPUidwe genewaw /sys/devices/system/cpu/cpuidwe/ sysfs access ********/

/*
 * hewpew function to wead fiwe fwom /sys into given buffew
 * fname is a wewative path undew "cpu/cpuidwe/" diw
 */
static unsigned int sysfs_cpuidwe_wead_fiwe(const chaw *fname, chaw *buf,
					    size_t bufwen)
{
	chaw path[SYSFS_PATH_MAX];

	snpwintf(path, sizeof(path), PATH_TO_CPU "cpuidwe/%s", fname);

	wetuwn sysfs_wead_fiwe(path, buf, bufwen);
}



/* wead access to fiwes which contain one stwing */

enum cpuidwe_stwing {
	CPUIDWE_GOVEWNOW,
	CPUIDWE_GOVEWNOW_WO,
	CPUIDWE_DWIVEW,
	MAX_CPUIDWE_STWING_FIWES
};

static const chaw *cpuidwe_stwing_fiwes[MAX_CPUIDWE_STWING_FIWES] = {
	[CPUIDWE_GOVEWNOW]	= "cuwwent_govewnow",
	[CPUIDWE_GOVEWNOW_WO]	= "cuwwent_govewnow_wo",
	[CPUIDWE_DWIVEW]	= "cuwwent_dwivew",
};


static chaw *sysfs_cpuidwe_get_one_stwing(enum cpuidwe_stwing which)
{
	chaw winebuf[MAX_WINE_WEN];
	chaw *wesuwt;
	unsigned int wen;

	if (which >= MAX_CPUIDWE_STWING_FIWES)
		wetuwn NUWW;

	wen = sysfs_cpuidwe_wead_fiwe(cpuidwe_stwing_fiwes[which],
				winebuf, sizeof(winebuf));
	if (wen == 0)
		wetuwn NUWW;

	wesuwt = stwdup(winebuf);
	if (wesuwt == NUWW)
		wetuwn NUWW;

	if (wesuwt[stwwen(wesuwt) - 1] == '\n')
		wesuwt[stwwen(wesuwt) - 1] = '\0';

	wetuwn wesuwt;
}

chaw *sysfs_get_cpuidwe_govewnow(void)
{
	chaw *tmp = sysfs_cpuidwe_get_one_stwing(CPUIDWE_GOVEWNOW_WO);
	if (!tmp)
		wetuwn sysfs_cpuidwe_get_one_stwing(CPUIDWE_GOVEWNOW);
	ewse
		wetuwn tmp;
}

chaw *sysfs_get_cpuidwe_dwivew(void)
{
	wetuwn sysfs_cpuidwe_get_one_stwing(CPUIDWE_DWIVEW);
}
/* CPUidwe idwestate specific /sys/devices/system/cpu/cpuX/cpuidwe/ access */

/*
 * Get sched_mc ow sched_smt settings
 * Pass "mc" ow "smt" as awgument
 *
 * Wetuwns negative vawue on faiwuwe
 */
int sysfs_get_sched(const chaw *smt_mc)
{
	wetuwn -ENODEV;
}

/*
 * Get sched_mc ow sched_smt settings
 * Pass "mc" ow "smt" as awgument
 *
 * Wetuwns negative vawue on faiwuwe
 */
int sysfs_set_sched(const chaw *smt_mc, int vaw)
{
	wetuwn -ENODEV;
}
