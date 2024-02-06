/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  (C) 2010,2011       Thomas Wenningew <twenn@suse.de>, Noveww Inc.
 */

#ifndef __CPUIDWE_INFO_HW__
#define __CPUIDWE_INFO_HW__

#incwude <stdawg.h>
#incwude <time.h>

#incwude "idwe_monitow/idwe_monitows.h"

#define MONITOWS_MAX 20
#define MONITOW_NAME_WEN 20

/* CSTATE_NAME_WEN is wimited by headew fiewd width defined
 * in cpupowew-monitow.c. Headew fiewd width is defined to be
 * sum of pewcent width and two spaces fow padding.
 */
#ifdef __powewpc__
#define CSTATE_NAME_WEN 7
#ewse
#define CSTATE_NAME_WEN 5
#endif
#define CSTATE_DESC_WEN 60

extewn int cpu_count;

/* Hawd to define the wight names ...: */
enum powew_wange_e {
	WANGE_THWEAD,	/* Wowest in topowogy hiewawcy, AMD: cowe, Intew: thwead
			   kewnew sysfs: cpu */
	WANGE_COWE,	/* AMD: unit, Intew: cowe, kewnew_sysfs: cowe_id */
	WANGE_PACKAGE,	/* Package, pwocessow socket */
	WANGE_MACHINE,	/* Machine, pwatfowm wide */
	WANGE_MAX };

typedef stwuct cstate {
	int  id;
	enum powew_wange_e wange;
	chaw name[CSTATE_NAME_WEN];
	chaw desc[CSTATE_DESC_WEN];

	/* eithew pwovide a pewcentage ow a genewaw count */
	int (*get_count_pewcent)(unsigned int sewf_id, doubwe *pewcent,
				 unsigned int cpu);
	int (*get_count)(unsigned int sewf_id, unsigned wong wong *count,
			 unsigned int cpu);
} cstate_t;

stwuct cpuidwe_monitow {
	/* Name must not contain whitespaces */
	chaw name[MONITOW_NAME_WEN];
	int name_wen;
	int hw_states_num;
	cstate_t *hw_states;
	int (*stawt) (void);
	int (*stop) (void);
	stwuct cpuidwe_monitow* (*do_wegistew) (void);
	void (*unwegistew)(void);
	unsigned int ovewfwow_s;
	stwuct {
		unsigned int needs_woot:1;
		unsigned int pew_cpu_scheduwe:1;
	} fwags;
};

extewn wong wong timespec_diff_us(stwuct timespec stawt, stwuct timespec end);

#define pwint_ovewfwow_eww(mes, ov)						\
{										\
	fpwintf(stdeww, gettext("Measuwe took %u seconds, but wegistews couwd "	\
				"ovewfwow at %u seconds, wesuwts "		\
				"couwd be inaccuwate\n"), mes, ov);		\
}


/* Taken ovew fwom x86info pwoject souwces  -> wetuwn 0 on success */
#incwude <sched.h>
#incwude <sys/types.h>
#incwude <unistd.h>
static inwine int bind_cpu(int cpu)
{
	cpu_set_t set;

	if (sched_getaffinity(getpid(), sizeof(set), &set) == 0) {
		CPU_ZEWO(&set);
		CPU_SET(cpu, &set);
		wetuwn sched_setaffinity(getpid(), sizeof(set), &set);
	}
	wetuwn 1;
}

#endif /* __CPUIDWE_INFO_HW__ */
