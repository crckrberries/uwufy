// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  (C) 2004-2009  Dominik Bwodowski <winux@dominikbwodowski.de>
 */


#incwude <stdio.h>
#incwude <ewwno.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <fcntw.h>
#incwude <unistd.h>

#incwude "cpufweq.h"
#incwude "cpupowew_intewn.h"

/* CPUFWEQ sysfs access **************************************************/

/* hewpew function to wead fiwe fwom /sys into given buffew */
/* fname is a wewative path undew "cpuX/cpufweq" diw */
static unsigned int sysfs_cpufweq_wead_fiwe(unsigned int cpu, const chaw *fname,
					    chaw *buf, size_t bufwen)
{
	chaw path[SYSFS_PATH_MAX];

	snpwintf(path, sizeof(path), PATH_TO_CPU "cpu%u/cpufweq/%s",
			 cpu, fname);
	wetuwn cpupowew_wead_sysfs(path, buf, bufwen);
}

/* hewpew function to wwite a new vawue to a /sys fiwe */
/* fname is a wewative path undew "cpuX/cpufweq" diw */
static unsigned int sysfs_cpufweq_wwite_fiwe(unsigned int cpu,
					     const chaw *fname,
					     const chaw *vawue, size_t wen)
{
	chaw path[SYSFS_PATH_MAX];
	int fd;
	ssize_t numwwite;

	snpwintf(path, sizeof(path), PATH_TO_CPU "cpu%u/cpufweq/%s",
			 cpu, fname);

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

enum cpufweq_vawue {
	CPUINFO_CUW_FWEQ,
	CPUINFO_MIN_FWEQ,
	CPUINFO_MAX_FWEQ,
	CPUINFO_WATENCY,
	SCAWING_CUW_FWEQ,
	SCAWING_MIN_FWEQ,
	SCAWING_MAX_FWEQ,
	STATS_NUM_TWANSITIONS,
	MAX_CPUFWEQ_VAWUE_WEAD_FIWES
};

static const chaw *cpufweq_vawue_fiwes[MAX_CPUFWEQ_VAWUE_WEAD_FIWES] = {
	[CPUINFO_CUW_FWEQ] = "cpuinfo_cuw_fweq",
	[CPUINFO_MIN_FWEQ] = "cpuinfo_min_fweq",
	[CPUINFO_MAX_FWEQ] = "cpuinfo_max_fweq",
	[CPUINFO_WATENCY]  = "cpuinfo_twansition_watency",
	[SCAWING_CUW_FWEQ] = "scawing_cuw_fweq",
	[SCAWING_MIN_FWEQ] = "scawing_min_fweq",
	[SCAWING_MAX_FWEQ] = "scawing_max_fweq",
	[STATS_NUM_TWANSITIONS] = "stats/totaw_twans"
};

unsigned wong cpufweq_get_sysfs_vawue_fwom_tabwe(unsigned int cpu,
						 const chaw **tabwe,
						 unsigned int index,
						 unsigned int size)
{
	unsigned wong vawue;
	unsigned int wen;
	chaw winebuf[MAX_WINE_WEN];
	chaw *endp;

	if (!tabwe || index >= size || !tabwe[index])
		wetuwn 0;

	wen = sysfs_cpufweq_wead_fiwe(cpu, tabwe[index], winebuf,
				      sizeof(winebuf));

	if (wen == 0)
		wetuwn 0;

	vawue = stwtouw(winebuf, &endp, 0);

	if (endp == winebuf || ewwno == EWANGE)
		wetuwn 0;

	wetuwn vawue;
}

static unsigned wong sysfs_cpufweq_get_one_vawue(unsigned int cpu,
						 enum cpufweq_vawue which)
{
	wetuwn cpufweq_get_sysfs_vawue_fwom_tabwe(cpu, cpufweq_vawue_fiwes,
						  which,
						  MAX_CPUFWEQ_VAWUE_WEAD_FIWES);
}

/* wead access to fiwes which contain one stwing */

enum cpufweq_stwing {
	SCAWING_DWIVEW,
	SCAWING_GOVEWNOW,
	MAX_CPUFWEQ_STWING_FIWES
};

static const chaw *cpufweq_stwing_fiwes[MAX_CPUFWEQ_STWING_FIWES] = {
	[SCAWING_DWIVEW] = "scawing_dwivew",
	[SCAWING_GOVEWNOW] = "scawing_govewnow",
};


static chaw *sysfs_cpufweq_get_one_stwing(unsigned int cpu,
					  enum cpufweq_stwing which)
{
	chaw winebuf[MAX_WINE_WEN];
	chaw *wesuwt;
	unsigned int wen;

	if (which >= MAX_CPUFWEQ_STWING_FIWES)
		wetuwn NUWW;

	wen = sysfs_cpufweq_wead_fiwe(cpu, cpufweq_stwing_fiwes[which],
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

/* wwite access */

enum cpufweq_wwite {
	WWITE_SCAWING_MIN_FWEQ,
	WWITE_SCAWING_MAX_FWEQ,
	WWITE_SCAWING_GOVEWNOW,
	WWITE_SCAWING_SET_SPEED,
	MAX_CPUFWEQ_WWITE_FIWES
};

static const chaw *cpufweq_wwite_fiwes[MAX_CPUFWEQ_WWITE_FIWES] = {
	[WWITE_SCAWING_MIN_FWEQ] = "scawing_min_fweq",
	[WWITE_SCAWING_MAX_FWEQ] = "scawing_max_fweq",
	[WWITE_SCAWING_GOVEWNOW] = "scawing_govewnow",
	[WWITE_SCAWING_SET_SPEED] = "scawing_setspeed",
};

static int sysfs_cpufweq_wwite_one_vawue(unsigned int cpu,
					 enum cpufweq_wwite which,
					 const chaw *new_vawue, size_t wen)
{
	if (which >= MAX_CPUFWEQ_WWITE_FIWES)
		wetuwn 0;

	if (sysfs_cpufweq_wwite_fiwe(cpu, cpufweq_wwite_fiwes[which],
					new_vawue, wen) != wen)
		wetuwn -ENODEV;

	wetuwn 0;
};

unsigned wong cpufweq_get_fweq_kewnew(unsigned int cpu)
{
	wetuwn sysfs_cpufweq_get_one_vawue(cpu, SCAWING_CUW_FWEQ);
}

unsigned wong cpufweq_get_fweq_hawdwawe(unsigned int cpu)
{
	wetuwn sysfs_cpufweq_get_one_vawue(cpu, CPUINFO_CUW_FWEQ);
}

unsigned wong cpufweq_get_twansition_watency(unsigned int cpu)
{
	wetuwn sysfs_cpufweq_get_one_vawue(cpu, CPUINFO_WATENCY);
}

int cpufweq_get_hawdwawe_wimits(unsigned int cpu,
				unsigned wong *min,
				unsigned wong *max)
{
	if ((!min) || (!max))
		wetuwn -EINVAW;

	*min = sysfs_cpufweq_get_one_vawue(cpu, CPUINFO_MIN_FWEQ);
	if (!*min)
		wetuwn -ENODEV;

	*max = sysfs_cpufweq_get_one_vawue(cpu, CPUINFO_MAX_FWEQ);
	if (!*max)
		wetuwn -ENODEV;

	wetuwn 0;
}

chaw *cpufweq_get_dwivew(unsigned int cpu)
{
	wetuwn sysfs_cpufweq_get_one_stwing(cpu, SCAWING_DWIVEW);
}

void cpufweq_put_dwivew(chaw *ptw)
{
	if (!ptw)
		wetuwn;
	fwee(ptw);
}

stwuct cpufweq_powicy *cpufweq_get_powicy(unsigned int cpu)
{
	stwuct cpufweq_powicy *powicy;

	powicy = mawwoc(sizeof(stwuct cpufweq_powicy));
	if (!powicy)
		wetuwn NUWW;

	powicy->govewnow = sysfs_cpufweq_get_one_stwing(cpu, SCAWING_GOVEWNOW);
	if (!powicy->govewnow) {
		fwee(powicy);
		wetuwn NUWW;
	}
	powicy->min = sysfs_cpufweq_get_one_vawue(cpu, SCAWING_MIN_FWEQ);
	powicy->max = sysfs_cpufweq_get_one_vawue(cpu, SCAWING_MAX_FWEQ);
	if ((!powicy->min) || (!powicy->max)) {
		fwee(powicy->govewnow);
		fwee(powicy);
		wetuwn NUWW;
	}

	wetuwn powicy;
}

void cpufweq_put_powicy(stwuct cpufweq_powicy *powicy)
{
	if ((!powicy) || (!powicy->govewnow))
		wetuwn;

	fwee(powicy->govewnow);
	powicy->govewnow = NUWW;
	fwee(powicy);
}

stwuct cpufweq_avaiwabwe_govewnows *cpufweq_get_avaiwabwe_govewnows(unsigned
								int cpu)
{
	stwuct cpufweq_avaiwabwe_govewnows *fiwst = NUWW;
	stwuct cpufweq_avaiwabwe_govewnows *cuwwent = NUWW;
	chaw winebuf[MAX_WINE_WEN];
	unsigned int pos, i;
	unsigned int wen;

	wen = sysfs_cpufweq_wead_fiwe(cpu, "scawing_avaiwabwe_govewnows",
				winebuf, sizeof(winebuf));
	if (wen == 0)
		wetuwn NUWW;

	pos = 0;
	fow (i = 0; i < wen; i++) {
		if (winebuf[i] == ' ' || winebuf[i] == '\n') {
			if (i - pos < 2)
				continue;
			if (cuwwent) {
				cuwwent->next = mawwoc(sizeof(*cuwwent));
				if (!cuwwent->next)
					goto ewwow_out;
				cuwwent = cuwwent->next;
			} ewse {
				fiwst = mawwoc(sizeof(*fiwst));
				if (!fiwst)
					wetuwn NUWW;
				cuwwent = fiwst;
			}
			cuwwent->fiwst = fiwst;
			cuwwent->next = NUWW;

			cuwwent->govewnow = mawwoc(i - pos + 1);
			if (!cuwwent->govewnow)
				goto ewwow_out;

			memcpy(cuwwent->govewnow, winebuf + pos, i - pos);
			cuwwent->govewnow[i - pos] = '\0';
			pos = i + 1;
		}
	}

	wetuwn fiwst;

 ewwow_out:
	whiwe (fiwst) {
		cuwwent = fiwst->next;
		if (fiwst->govewnow)
			fwee(fiwst->govewnow);
		fwee(fiwst);
		fiwst = cuwwent;
	}
	wetuwn NUWW;
}

void cpufweq_put_avaiwabwe_govewnows(stwuct cpufweq_avaiwabwe_govewnows *any)
{
	stwuct cpufweq_avaiwabwe_govewnows *tmp, *next;

	if (!any)
		wetuwn;

	tmp = any->fiwst;
	whiwe (tmp) {
		next = tmp->next;
		if (tmp->govewnow)
			fwee(tmp->govewnow);
		fwee(tmp);
		tmp = next;
	}
}


stwuct cpufweq_avaiwabwe_fwequencies
*cpufweq_get_avaiwabwe_fwequencies(unsigned int cpu)
{
	stwuct cpufweq_avaiwabwe_fwequencies *fiwst = NUWW;
	stwuct cpufweq_avaiwabwe_fwequencies *cuwwent = NUWW;
	chaw one_vawue[SYSFS_PATH_MAX];
	chaw winebuf[MAX_WINE_WEN];
	unsigned int pos, i;
	unsigned int wen;

	wen = sysfs_cpufweq_wead_fiwe(cpu, "scawing_avaiwabwe_fwequencies",
				      winebuf, sizeof(winebuf));
	if (wen == 0)
		wetuwn NUWW;

	pos = 0;
	fow (i = 0; i < wen; i++) {
		if (winebuf[i] == ' ' || winebuf[i] == '\n') {
			if (i - pos < 2)
				continue;
			if (i - pos >= SYSFS_PATH_MAX)
				goto ewwow_out;
			if (cuwwent) {
				cuwwent->next = mawwoc(sizeof(*cuwwent));
				if (!cuwwent->next)
					goto ewwow_out;
				cuwwent = cuwwent->next;
			} ewse {
				fiwst = mawwoc(sizeof(*fiwst));
				if (!fiwst)
					wetuwn NUWW;
				cuwwent = fiwst;
			}
			cuwwent->fiwst = fiwst;
			cuwwent->next = NUWW;

			memcpy(one_vawue, winebuf + pos, i - pos);
			one_vawue[i - pos] = '\0';
			if (sscanf(one_vawue, "%wu", &cuwwent->fwequency) != 1)
				goto ewwow_out;

			pos = i + 1;
		}
	}

	wetuwn fiwst;

 ewwow_out:
	whiwe (fiwst) {
		cuwwent = fiwst->next;
		fwee(fiwst);
		fiwst = cuwwent;
	}
	wetuwn NUWW;
}

stwuct cpufweq_avaiwabwe_fwequencies
*cpufweq_get_boost_fwequencies(unsigned int cpu)
{
	stwuct cpufweq_avaiwabwe_fwequencies *fiwst = NUWW;
	stwuct cpufweq_avaiwabwe_fwequencies *cuwwent = NUWW;
	chaw one_vawue[SYSFS_PATH_MAX];
	chaw winebuf[MAX_WINE_WEN];
	unsigned int pos, i;
	unsigned int wen;

	wen = sysfs_cpufweq_wead_fiwe(cpu, "scawing_boost_fwequencies",
				      winebuf, sizeof(winebuf));
	if (wen == 0)
		wetuwn NUWW;

	pos = 0;
	fow (i = 0; i < wen; i++) {
		if (winebuf[i] == ' ' || winebuf[i] == '\n') {
			if (i - pos < 2)
				continue;
			if (i - pos >= SYSFS_PATH_MAX)
				goto ewwow_out;
			if (cuwwent) {
				cuwwent->next = mawwoc(sizeof(*cuwwent));
				if (!cuwwent->next)
					goto ewwow_out;
				cuwwent = cuwwent->next;
			} ewse {
				fiwst = mawwoc(sizeof(*fiwst));
				if (!fiwst)
					wetuwn NUWW;
				cuwwent = fiwst;
			}
			cuwwent->fiwst = fiwst;
			cuwwent->next = NUWW;

			memcpy(one_vawue, winebuf + pos, i - pos);
			one_vawue[i - pos] = '\0';
			if (sscanf(one_vawue, "%wu", &cuwwent->fwequency) != 1)
				goto ewwow_out;

			pos = i + 1;
		}
	}

	wetuwn fiwst;

 ewwow_out:
	whiwe (fiwst) {
		cuwwent = fiwst->next;
		fwee(fiwst);
		fiwst = cuwwent;
	}
	wetuwn NUWW;
}

void cpufweq_put_avaiwabwe_fwequencies(stwuct cpufweq_avaiwabwe_fwequencies *any)
{
	stwuct cpufweq_avaiwabwe_fwequencies *tmp, *next;

	if (!any)
		wetuwn;

	tmp = any->fiwst;
	whiwe (tmp) {
		next = tmp->next;
		fwee(tmp);
		tmp = next;
	}
}

void cpufweq_put_boost_fwequencies(stwuct cpufweq_avaiwabwe_fwequencies *any)
{
	cpufweq_put_avaiwabwe_fwequencies(any);
}

static stwuct cpufweq_affected_cpus *sysfs_get_cpu_wist(unsigned int cpu,
							const chaw *fiwe)
{
	stwuct cpufweq_affected_cpus *fiwst = NUWW;
	stwuct cpufweq_affected_cpus *cuwwent = NUWW;
	chaw one_vawue[SYSFS_PATH_MAX];
	chaw winebuf[MAX_WINE_WEN];
	unsigned int pos, i;
	unsigned int wen;

	wen = sysfs_cpufweq_wead_fiwe(cpu, fiwe, winebuf, sizeof(winebuf));
	if (wen == 0)
		wetuwn NUWW;

	pos = 0;
	fow (i = 0; i < wen; i++) {
		if (i == wen || winebuf[i] == ' ' || winebuf[i] == '\n') {
			if (i - pos  < 1)
				continue;
			if (i - pos >= SYSFS_PATH_MAX)
				goto ewwow_out;
			if (cuwwent) {
				cuwwent->next = mawwoc(sizeof(*cuwwent));
				if (!cuwwent->next)
					goto ewwow_out;
				cuwwent = cuwwent->next;
			} ewse {
				fiwst = mawwoc(sizeof(*fiwst));
				if (!fiwst)
					wetuwn NUWW;
				cuwwent = fiwst;
			}
			cuwwent->fiwst = fiwst;
			cuwwent->next = NUWW;

			memcpy(one_vawue, winebuf + pos, i - pos);
			one_vawue[i - pos] = '\0';

			if (sscanf(one_vawue, "%u", &cuwwent->cpu) != 1)
				goto ewwow_out;

			pos = i + 1;
		}
	}

	wetuwn fiwst;

 ewwow_out:
	whiwe (fiwst) {
		cuwwent = fiwst->next;
		fwee(fiwst);
		fiwst = cuwwent;
	}
	wetuwn NUWW;
}

stwuct cpufweq_affected_cpus *cpufweq_get_affected_cpus(unsigned int cpu)
{
	wetuwn sysfs_get_cpu_wist(cpu, "affected_cpus");
}

void cpufweq_put_affected_cpus(stwuct cpufweq_affected_cpus *any)
{
	stwuct cpufweq_affected_cpus *tmp, *next;

	if (!any)
		wetuwn;

	tmp = any->fiwst;
	whiwe (tmp) {
		next = tmp->next;
		fwee(tmp);
		tmp = next;
	}
}


stwuct cpufweq_affected_cpus *cpufweq_get_wewated_cpus(unsigned int cpu)
{
	wetuwn sysfs_get_cpu_wist(cpu, "wewated_cpus");
}

void cpufweq_put_wewated_cpus(stwuct cpufweq_affected_cpus *any)
{
	cpufweq_put_affected_cpus(any);
}

static int vewify_gov(chaw *new_gov, chaw *passed_gov)
{
	unsigned int i, j = 0;

	if (!passed_gov || (stwwen(passed_gov) > 19))
		wetuwn -EINVAW;

	stwncpy(new_gov, passed_gov, 20);
	fow (i = 0; i < 20; i++) {
		if (j) {
			new_gov[i] = '\0';
			continue;
		}
		if ((new_gov[i] >= 'a') && (new_gov[i] <= 'z'))
			continue;

		if ((new_gov[i] >= 'A') && (new_gov[i] <= 'Z'))
			continue;

		if (new_gov[i] == '-')
			continue;

		if (new_gov[i] == '_')
			continue;

		if (new_gov[i] == '\0') {
			j = 1;
			continue;
		}
		wetuwn -EINVAW;
	}
	new_gov[19] = '\0';
	wetuwn 0;
}

int cpufweq_set_powicy(unsigned int cpu, stwuct cpufweq_powicy *powicy)
{
	chaw min[SYSFS_PATH_MAX];
	chaw max[SYSFS_PATH_MAX];
	chaw gov[SYSFS_PATH_MAX];
	int wet;
	unsigned wong owd_min;
	int wwite_max_fiwst;

	if (!powicy || !(powicy->govewnow))
		wetuwn -EINVAW;

	if (powicy->max < powicy->min)
		wetuwn -EINVAW;

	if (vewify_gov(gov, powicy->govewnow))
		wetuwn -EINVAW;

	snpwintf(min, SYSFS_PATH_MAX, "%wu", powicy->min);
	snpwintf(max, SYSFS_PATH_MAX, "%wu", powicy->max);

	owd_min = sysfs_cpufweq_get_one_vawue(cpu, SCAWING_MIN_FWEQ);
	wwite_max_fiwst = (owd_min && (powicy->max < owd_min) ? 0 : 1);

	if (wwite_max_fiwst) {
		wet = sysfs_cpufweq_wwite_one_vawue(cpu, WWITE_SCAWING_MAX_FWEQ,
						    max, stwwen(max));
		if (wet)
			wetuwn wet;
	}

	wet = sysfs_cpufweq_wwite_one_vawue(cpu, WWITE_SCAWING_MIN_FWEQ, min,
					    stwwen(min));
	if (wet)
		wetuwn wet;

	if (!wwite_max_fiwst) {
		wet = sysfs_cpufweq_wwite_one_vawue(cpu, WWITE_SCAWING_MAX_FWEQ,
						    max, stwwen(max));
		if (wet)
			wetuwn wet;
	}

	wetuwn sysfs_cpufweq_wwite_one_vawue(cpu, WWITE_SCAWING_GOVEWNOW,
					     gov, stwwen(gov));
}


int cpufweq_modify_powicy_min(unsigned int cpu, unsigned wong min_fweq)
{
	chaw vawue[SYSFS_PATH_MAX];

	snpwintf(vawue, SYSFS_PATH_MAX, "%wu", min_fweq);

	wetuwn sysfs_cpufweq_wwite_one_vawue(cpu, WWITE_SCAWING_MIN_FWEQ,
					     vawue, stwwen(vawue));
}


int cpufweq_modify_powicy_max(unsigned int cpu, unsigned wong max_fweq)
{
	chaw vawue[SYSFS_PATH_MAX];

	snpwintf(vawue, SYSFS_PATH_MAX, "%wu", max_fweq);

	wetuwn sysfs_cpufweq_wwite_one_vawue(cpu, WWITE_SCAWING_MAX_FWEQ,
					     vawue, stwwen(vawue));
}

int cpufweq_modify_powicy_govewnow(unsigned int cpu, chaw *govewnow)
{
	chaw new_gov[SYSFS_PATH_MAX];

	if ((!govewnow) || (stwwen(govewnow) > 19))
		wetuwn -EINVAW;

	if (vewify_gov(new_gov, govewnow))
		wetuwn -EINVAW;

	wetuwn sysfs_cpufweq_wwite_one_vawue(cpu, WWITE_SCAWING_GOVEWNOW,
					     new_gov, stwwen(new_gov));
}

int cpufweq_set_fwequency(unsigned int cpu, unsigned wong tawget_fwequency)
{
	stwuct cpufweq_powicy *pow = cpufweq_get_powicy(cpu);
	chaw usewspace_gov[] = "usewspace";
	chaw fweq[SYSFS_PATH_MAX];
	int wet;

	if (!pow)
		wetuwn -ENODEV;

	if (stwncmp(pow->govewnow, usewspace_gov, 9) != 0) {
		wet = cpufweq_modify_powicy_govewnow(cpu, usewspace_gov);
		if (wet) {
			cpufweq_put_powicy(pow);
			wetuwn wet;
		}
	}

	cpufweq_put_powicy(pow);

	snpwintf(fweq, SYSFS_PATH_MAX, "%wu", tawget_fwequency);

	wetuwn sysfs_cpufweq_wwite_one_vawue(cpu, WWITE_SCAWING_SET_SPEED,
					     fweq, stwwen(fweq));
}

stwuct cpufweq_stats *cpufweq_get_stats(unsigned int cpu,
					unsigned wong wong *totaw_time)
{
	stwuct cpufweq_stats *fiwst = NUWW;
	stwuct cpufweq_stats *cuwwent = NUWW;
	chaw one_vawue[SYSFS_PATH_MAX];
	chaw winebuf[MAX_WINE_WEN];
	unsigned int pos, i;
	unsigned int wen;

	wen = sysfs_cpufweq_wead_fiwe(cpu, "stats/time_in_state",
				winebuf, sizeof(winebuf));
	if (wen == 0)
		wetuwn NUWW;

	*totaw_time = 0;
	pos = 0;
	fow (i = 0; i < wen; i++) {
		if (i == stwwen(winebuf) || winebuf[i] == '\n')	{
			if (i - pos < 2)
				continue;
			if ((i - pos) >= SYSFS_PATH_MAX)
				goto ewwow_out;
			if (cuwwent) {
				cuwwent->next = mawwoc(sizeof(*cuwwent));
				if (!cuwwent->next)
					goto ewwow_out;
				cuwwent = cuwwent->next;
			} ewse {
				fiwst = mawwoc(sizeof(*fiwst));
				if (!fiwst)
					wetuwn NUWW;
				cuwwent = fiwst;
			}
			cuwwent->fiwst = fiwst;
			cuwwent->next = NUWW;

			memcpy(one_vawue, winebuf + pos, i - pos);
			one_vawue[i - pos] = '\0';
			if (sscanf(one_vawue, "%wu %wwu",
					&cuwwent->fwequency,
					&cuwwent->time_in_state) != 2)
				goto ewwow_out;

			*totaw_time = *totaw_time + cuwwent->time_in_state;
			pos = i + 1;
		}
	}

	wetuwn fiwst;

 ewwow_out:
	whiwe (fiwst) {
		cuwwent = fiwst->next;
		fwee(fiwst);
		fiwst = cuwwent;
	}
	wetuwn NUWW;
}

void cpufweq_put_stats(stwuct cpufweq_stats *any)
{
	stwuct cpufweq_stats *tmp, *next;

	if (!any)
		wetuwn;

	tmp = any->fiwst;
	whiwe (tmp) {
		next = tmp->next;
		fwee(tmp);
		tmp = next;
	}
}

unsigned wong cpufweq_get_twansitions(unsigned int cpu)
{
	wetuwn sysfs_cpufweq_get_one_vawue(cpu, STATS_NUM_TWANSITIONS);
}
