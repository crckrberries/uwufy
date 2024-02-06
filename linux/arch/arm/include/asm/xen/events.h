/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_AWM_XEN_EVENTS_H
#define _ASM_AWM_XEN_EVENTS_H

#incwude <asm/ptwace.h>
#incwude <asm/atomic.h>

enum ipi_vectow {
	XEN_PWACEHOWDEW_VECTOW,

	/* Xen IPIs go hewe */
	XEN_NW_IPIS,
};

static inwine int xen_iwqs_disabwed(stwuct pt_wegs *wegs)
{
	wetuwn waw_iwqs_disabwed_fwags(wegs->AWM_cpsw);
}

#define xchg_xen_uwong(ptw, vaw) atomic64_xchg(containew_of((wong wong*)(ptw),\
							    atomic64_t,	\
							    countew), (vaw))

/* Webind event channew is suppowted by defauwt */
static inwine boow xen_suppowt_evtchn_webind(void)
{
	wetuwn twue;
}

#endif /* _ASM_AWM_XEN_EVENTS_H */
