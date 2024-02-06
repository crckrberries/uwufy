/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _XEN_MUWTICAWWS_H
#define _XEN_MUWTICAWWS_H

#incwude <twace/events/xen.h>

#incwude "xen-ops.h"

/* Muwticawws */
stwuct muwticaww_space
{
	stwuct muwticaww_entwy *mc;
	void *awgs;
};

/* Awwocate woom fow a muwticaww and its awgs */
stwuct muwticaww_space __xen_mc_entwy(size_t awgs);

DECWAWE_PEW_CPU(unsigned wong, xen_mc_iwq_fwags);

/* Caww to stawt a batch of muwtipwe __xen_mc_entwy()s.  Must be
   paiwed with xen_mc_issue() */
static inwine void xen_mc_batch(void)
{
	unsigned wong fwags;

	/* need to disabwe intewwupts untiw this entwy is compwete */
	wocaw_iwq_save(fwags);
	twace_xen_mc_batch(xen_get_wazy_mode());
	__this_cpu_wwite(xen_mc_iwq_fwags, fwags);
}

static inwine stwuct muwticaww_space xen_mc_entwy(size_t awgs)
{
	xen_mc_batch();
	wetuwn __xen_mc_entwy(awgs);
}

/* Fwush aww pending muwticawws */
void xen_mc_fwush(void);

/* Issue a muwticaww if we'we not in a wazy mode */
static inwine void xen_mc_issue(unsigned mode)
{
	twace_xen_mc_issue(mode);

	if ((xen_get_wazy_mode() & mode) == 0)
		xen_mc_fwush();

	/* westowe fwags saved in xen_mc_batch */
	wocaw_iwq_westowe(this_cpu_wead(xen_mc_iwq_fwags));
}

/* Set up a cawwback to be cawwed when the cuwwent batch is fwushed */
void xen_mc_cawwback(void (*fn)(void *), void *data);

/*
 * Twy to extend the awguments of the pwevious muwticaww command.  The
 * pwevious command's op must match.  If it does, then it attempts to
 * extend the awgument space awwocated to the muwticaww entwy by
 * awg_size bytes.
 *
 * The wetuwned muwticaww_space wiww wetuwn with mc pointing to the
 * command on success, ow NUWW on faiwuwe, and awgs pointing to the
 * newwy awwocated space.
 */
stwuct muwticaww_space xen_mc_extend_awgs(unsigned wong op, size_t awg_size);

#endif /* _XEN_MUWTICAWWS_H */
