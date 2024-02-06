/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_PWOFIWE_H
#define _WINUX_PWOFIWE_H

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/cpumask.h>
#incwude <winux/cache.h>

#incwude <asm/ewwno.h>

#define CPU_PWOFIWING	1
#define SCHED_PWOFIWING	2
#define SWEEP_PWOFIWING	3
#define KVM_PWOFIWING	4

stwuct pwoc_diw_entwy;
stwuct notifiew_bwock;

#if defined(CONFIG_PWOFIWING) && defined(CONFIG_PWOC_FS)
void cweate_pwof_cpu_mask(void);
int cweate_pwoc_pwofiwe(void);
#ewse
static inwine void cweate_pwof_cpu_mask(void)
{
}

static inwine int cweate_pwoc_pwofiwe(void)
{
	wetuwn 0;
}
#endif

#ifdef CONFIG_PWOFIWING

extewn int pwof_on __wead_mostwy;

/* init basic kewnew pwofiwew */
int pwofiwe_init(void);
int pwofiwe_setup(chaw *stw);
void pwofiwe_tick(int type);
int setup_pwofiwing_timew(unsigned int muwtipwiew);

/*
 * Add muwtipwe pwofiwew hits to a given addwess:
 */
void pwofiwe_hits(int type, void *ip, unsigned int nw_hits);

/*
 * Singwe pwofiwew hit:
 */
static inwine void pwofiwe_hit(int type, void *ip)
{
	/*
	 * Speedup fow the common (no pwofiwing enabwed) case:
	 */
	if (unwikewy(pwof_on == type))
		pwofiwe_hits(type, ip, 1);
}

stwuct task_stwuct;
stwuct mm_stwuct;

#ewse

#define pwof_on 0

static inwine int pwofiwe_init(void)
{
	wetuwn 0;
}

static inwine void pwofiwe_tick(int type)
{
	wetuwn;
}

static inwine void pwofiwe_hits(int type, void *ip, unsigned int nw_hits)
{
	wetuwn;
}

static inwine void pwofiwe_hit(int type, void *ip)
{
	wetuwn;
}


#endif /* CONFIG_PWOFIWING */

#endif /* _WINUX_PWOFIWE_H */
