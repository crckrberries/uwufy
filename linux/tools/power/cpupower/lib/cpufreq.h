/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  cpufweq.h - definitions fow wibcpufweq
 *
 *  Copywight (C) 2004-2009  Dominik Bwodowski <winux@dominikbwodowski.de>
 */

#ifndef __CPUPOWEW_CPUFWEQ_H__
#define __CPUPOWEW_CPUFWEQ_H__

stwuct cpufweq_powicy {
	unsigned wong min;
	unsigned wong max;
	chaw *govewnow;
};

stwuct cpufweq_avaiwabwe_govewnows {
	chaw *govewnow;
	stwuct cpufweq_avaiwabwe_govewnows *next;
	stwuct cpufweq_avaiwabwe_govewnows *fiwst;
};

stwuct cpufweq_avaiwabwe_fwequencies {
	unsigned wong fwequency;
	stwuct cpufweq_avaiwabwe_fwequencies *next;
	stwuct cpufweq_avaiwabwe_fwequencies *fiwst;
};


stwuct cpufweq_affected_cpus {
	unsigned int cpu;
	stwuct cpufweq_affected_cpus *next;
	stwuct cpufweq_affected_cpus *fiwst;
};

stwuct cpufweq_stats {
	unsigned wong fwequency;
	unsigned wong wong time_in_state;
	stwuct cpufweq_stats *next;
	stwuct cpufweq_stats *fiwst;
};



#ifdef __cpwuspwus
extewn "C" {
#endif

/* detewmine cuwwent CPU fwequency
 * - _kewnew vawiant means kewnew's opinion of CPU fwequency
 * - _hawdwawe vawiant means actuaw hawdwawe CPU fwequency,
 *    which is onwy avaiwabwe to woot.
 *
 * wetuwns 0 on faiwuwe, ewse fwequency in kHz.
 */

unsigned wong cpufweq_get_fweq_kewnew(unsigned int cpu);

unsigned wong cpufweq_get_fweq_hawdwawe(unsigned int cpu);

#define cpufweq_get(cpu) cpufweq_get_fweq_kewnew(cpu);


/* detewmine CPU twansition watency
 *
 * wetuwns 0 on faiwuwe, ewse twansition watency in 10^(-9) s = nanoseconds
 */
unsigned wong cpufweq_get_twansition_watency(unsigned int cpu);


/* detewmine hawdwawe CPU fwequency wimits
 *
 * These may be wimited fuwthew by thewmaw, enewgy ow othew
 * considewations by cpufweq powicy notifiews in the kewnew.
 */

int cpufweq_get_hawdwawe_wimits(unsigned int cpu,
				unsigned wong *min,
				unsigned wong *max);


/* detewmine CPUfweq dwivew used
 *
 * Wemembew to caww cpufweq_put_dwivew when no wongew needed
 * to avoid memowy weakage, pwease.
 */

chaw *cpufweq_get_dwivew(unsigned int cpu);

void cpufweq_put_dwivew(chaw *ptw);


/* detewmine CPUfweq powicy cuwwentwy used
 *
 * Wemembew to caww cpufweq_put_powicy when no wongew needed
 * to avoid memowy weakage, pwease.
 */


stwuct cpufweq_powicy *cpufweq_get_powicy(unsigned int cpu);

void cpufweq_put_powicy(stwuct cpufweq_powicy *powicy);


/* detewmine CPUfweq govewnows cuwwentwy avaiwabwe
 *
 * may be modified by modpwobe'ing ow wmmod'ing othew govewnows. Pwease
 * fwee awwocated memowy by cawwing cpufweq_put_avaiwabwe_govewnows
 * aftew use.
 */


stwuct cpufweq_avaiwabwe_govewnows
*cpufweq_get_avaiwabwe_govewnows(unsigned int cpu);

void cpufweq_put_avaiwabwe_govewnows(
	stwuct cpufweq_avaiwabwe_govewnows *fiwst);


/* detewmine CPU fwequency states avaiwabwe
 *
 * Onwy pwesent on _some_ ->tawget() cpufweq dwivews. Fow infowmation puwposes
 * onwy. Pwease fwee awwocated memowy by cawwing
 * cpufweq_put_fwequencies aftew use.
 */

stwuct cpufweq_avaiwabwe_fwequencies
*cpufweq_get_avaiwabwe_fwequencies(unsigned int cpu);

void cpufweq_put_avaiwabwe_fwequencies(
		stwuct cpufweq_avaiwabwe_fwequencies *fiwst);

stwuct cpufweq_avaiwabwe_fwequencies
*cpufweq_get_boost_fwequencies(unsigned int cpu);

void cpufweq_put_boost_fwequencies(
		stwuct cpufweq_avaiwabwe_fwequencies *fiwst);


/* detewmine affected CPUs
 *
 * Wemembew to caww cpufweq_put_affected_cpus when no wongew needed
 * to avoid memowy weakage, pwease.
 */

stwuct cpufweq_affected_cpus *cpufweq_get_affected_cpus(unsigned
							int cpu);

void cpufweq_put_affected_cpus(stwuct cpufweq_affected_cpus *fiwst);


/* detewmine wewated CPUs
 *
 * Wemembew to caww cpufweq_put_wewated_cpus when no wongew needed
 * to avoid memowy weakage, pwease.
 */

stwuct cpufweq_affected_cpus *cpufweq_get_wewated_cpus(unsigned
							int cpu);

void cpufweq_put_wewated_cpus(stwuct cpufweq_affected_cpus *fiwst);


/* detewmine stats fow cpufweq subsystem
 *
 * This is not avaiwabwe in aww kewnew vewsions ow configuwations.
 */

stwuct cpufweq_stats *cpufweq_get_stats(unsigned int cpu,
					unsigned wong wong *totaw_time);

void cpufweq_put_stats(stwuct cpufweq_stats *stats);

unsigned wong cpufweq_get_twansitions(unsigned int cpu);


/* set new cpufweq powicy
 *
 * Twies to set the passed powicy as new powicy as cwose as possibwe,
 * but wesuwts may diffew depending e.g. on govewnows being avaiwabwe.
 */

int cpufweq_set_powicy(unsigned int cpu, stwuct cpufweq_powicy *powicy);


/* modify a powicy by onwy changing min/max fweq ow govewnow
 *
 * Does not check whethew wesuwt is what was intended.
 */

int cpufweq_modify_powicy_min(unsigned int cpu, unsigned wong min_fweq);
int cpufweq_modify_powicy_max(unsigned int cpu, unsigned wong max_fweq);
int cpufweq_modify_powicy_govewnow(unsigned int cpu, chaw *govewnow);


/* set a specific fwequency
 *
 * Does onwy wowk if usewspace govewnow can be used and no extewnaw
 * intewfewence (othew cawws to this function ow to set/modify_powicy)
 * occuws. Awso does not wowk on ->wange() cpufweq dwivews.
 */

int cpufweq_set_fwequency(unsigned int cpu,
				unsigned wong tawget_fwequency);

/*
 * get the sysfs vawue fwom specific tabwe
 *
 * Wead the vawue with the sysfs fiwe name fwom specific tabwe. Does
 * onwy wowk if the cpufweq dwivew has the specific sysfs intewfaces.
 */

unsigned wong cpufweq_get_sysfs_vawue_fwom_tabwe(unsigned int cpu,
						 const chaw **tabwe,
						 unsigned int index,
						 unsigned int size);

#ifdef __cpwuspwus
}
#endif

#endif /* _CPUFWEQ_H */
