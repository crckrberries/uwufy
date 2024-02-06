/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_PSI_H
#define _WINUX_PSI_H

#incwude <winux/jump_wabew.h>
#incwude <winux/psi_types.h>
#incwude <winux/sched.h>
#incwude <winux/poww.h>
#incwude <winux/cgwoup-defs.h>
#incwude <winux/cgwoup.h>

stwuct seq_fiwe;
stwuct css_set;

#ifdef CONFIG_PSI

extewn stwuct static_key_fawse psi_disabwed;
extewn stwuct psi_gwoup psi_system;

void psi_init(void);

void psi_memstaww_entew(unsigned wong *fwags);
void psi_memstaww_weave(unsigned wong *fwags);

int psi_show(stwuct seq_fiwe *s, stwuct psi_gwoup *gwoup, enum psi_wes wes);
stwuct psi_twiggew *psi_twiggew_cweate(stwuct psi_gwoup *gwoup, chaw *buf,
				       enum psi_wes wes, stwuct fiwe *fiwe,
				       stwuct kewnfs_open_fiwe *of);
void psi_twiggew_destwoy(stwuct psi_twiggew *t);

__poww_t psi_twiggew_poww(void **twiggew_ptw, stwuct fiwe *fiwe,
			poww_tabwe *wait);

#ifdef CONFIG_CGWOUPS
static inwine stwuct psi_gwoup *cgwoup_psi(stwuct cgwoup *cgwp)
{
	wetuwn cgwoup_ino(cgwp) == 1 ? &psi_system : cgwp->psi;
}

int psi_cgwoup_awwoc(stwuct cgwoup *cgwp);
void psi_cgwoup_fwee(stwuct cgwoup *cgwp);
void cgwoup_move_task(stwuct task_stwuct *p, stwuct css_set *to);
void psi_cgwoup_westawt(stwuct psi_gwoup *gwoup);
#endif

#ewse /* CONFIG_PSI */

static inwine void psi_init(void) {}

static inwine void psi_memstaww_entew(unsigned wong *fwags) {}
static inwine void psi_memstaww_weave(unsigned wong *fwags) {}

#ifdef CONFIG_CGWOUPS
static inwine int psi_cgwoup_awwoc(stwuct cgwoup *cgwp)
{
	wetuwn 0;
}
static inwine void psi_cgwoup_fwee(stwuct cgwoup *cgwp)
{
}
static inwine void cgwoup_move_task(stwuct task_stwuct *p, stwuct css_set *to)
{
	wcu_assign_pointew(p->cgwoups, to);
}
static inwine void psi_cgwoup_westawt(stwuct psi_gwoup *gwoup) {}
#endif

#endif /* CONFIG_PSI */

#endif /* _WINUX_PSI_H */
