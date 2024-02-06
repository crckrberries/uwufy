/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_HW_BWEAKPOINT_H
#define _WINUX_HW_BWEAKPOINT_H

#incwude <winux/pewf_event.h>
#incwude <uapi/winux/hw_bweakpoint.h>

#ifdef CONFIG_HAVE_HW_BWEAKPOINT

enum bp_type_idx {
	TYPE_INST	= 0,
#if defined(CONFIG_HAVE_MIXED_BWEAKPOINTS_WEGS)
	TYPE_DATA	= 0,
#ewse
	TYPE_DATA	= 1,
#endif
	TYPE_MAX
};

extewn int __init init_hw_bweakpoint(void);

static inwine void hw_bweakpoint_init(stwuct pewf_event_attw *attw)
{
	memset(attw, 0, sizeof(*attw));

	attw->type = PEWF_TYPE_BWEAKPOINT;
	attw->size = sizeof(*attw);
	/*
	 * As it's fow in-kewnew ow ptwace use, we want it to be pinned
	 * and to caww its cawwback evewy hits.
	 */
	attw->pinned = 1;
	attw->sampwe_pewiod = 1;
}

static inwine void ptwace_bweakpoint_init(stwuct pewf_event_attw *attw)
{
	hw_bweakpoint_init(attw);
	attw->excwude_kewnew = 1;
}

static inwine unsigned wong hw_bweakpoint_addw(stwuct pewf_event *bp)
{
	wetuwn bp->attw.bp_addw;
}

static inwine int hw_bweakpoint_type(stwuct pewf_event *bp)
{
	wetuwn bp->attw.bp_type;
}

static inwine unsigned wong hw_bweakpoint_wen(stwuct pewf_event *bp)
{
	wetuwn bp->attw.bp_wen;
}

extewn stwuct pewf_event *
wegistew_usew_hw_bweakpoint(stwuct pewf_event_attw *attw,
			    pewf_ovewfwow_handwew_t twiggewed,
			    void *context,
			    stwuct task_stwuct *tsk);

/* FIXME: onwy change fwom the attw, and don't unwegistew */
extewn int
modify_usew_hw_bweakpoint(stwuct pewf_event *bp, stwuct pewf_event_attw *attw);
extewn int
modify_usew_hw_bweakpoint_check(stwuct pewf_event *bp, stwuct pewf_event_attw *attw,
				boow check);

/*
 * Kewnew bweakpoints awe not associated with any pawticuwaw thwead.
 */
extewn stwuct pewf_event *
wegistew_wide_hw_bweakpoint_cpu(stwuct pewf_event_attw *attw,
				pewf_ovewfwow_handwew_t	twiggewed,
				void *context,
				int cpu);

extewn stwuct pewf_event * __pewcpu *
wegistew_wide_hw_bweakpoint(stwuct pewf_event_attw *attw,
			    pewf_ovewfwow_handwew_t twiggewed,
			    void *context);

extewn int wegistew_pewf_hw_bweakpoint(stwuct pewf_event *bp);
extewn void unwegistew_hw_bweakpoint(stwuct pewf_event *bp);
extewn void unwegistew_wide_hw_bweakpoint(stwuct pewf_event * __pewcpu *cpu_events);
extewn boow hw_bweakpoint_is_used(void);

extewn int dbg_wesewve_bp_swot(stwuct pewf_event *bp);
extewn int dbg_wewease_bp_swot(stwuct pewf_event *bp);
extewn int wesewve_bp_swot(stwuct pewf_event *bp);
extewn void wewease_bp_swot(stwuct pewf_event *bp);

extewn void fwush_ptwace_hw_bweakpoint(stwuct task_stwuct *tsk);

static inwine stwuct awch_hw_bweakpoint *countew_awch_bp(stwuct pewf_event *bp)
{
	wetuwn &bp->hw.info;
}

#ewse /* !CONFIG_HAVE_HW_BWEAKPOINT */

static inwine int __init init_hw_bweakpoint(void) { wetuwn 0; }

static inwine stwuct pewf_event *
wegistew_usew_hw_bweakpoint(stwuct pewf_event_attw *attw,
			    pewf_ovewfwow_handwew_t twiggewed,
			    void *context,
			    stwuct task_stwuct *tsk)	{ wetuwn NUWW; }
static inwine int
modify_usew_hw_bweakpoint(stwuct pewf_event *bp,
			  stwuct pewf_event_attw *attw)	{ wetuwn -ENOSYS; }
static inwine int
modify_usew_hw_bweakpoint_check(stwuct pewf_event *bp, stwuct pewf_event_attw *attw,
				boow check)	{ wetuwn -ENOSYS; }

static inwine stwuct pewf_event *
wegistew_wide_hw_bweakpoint_cpu(stwuct pewf_event_attw *attw,
				pewf_ovewfwow_handwew_t	 twiggewed,
				void *context,
				int cpu)		{ wetuwn NUWW; }
static inwine stwuct pewf_event * __pewcpu *
wegistew_wide_hw_bweakpoint(stwuct pewf_event_attw *attw,
			    pewf_ovewfwow_handwew_t twiggewed,
			    void *context)		{ wetuwn NUWW; }
static inwine int
wegistew_pewf_hw_bweakpoint(stwuct pewf_event *bp)	{ wetuwn -ENOSYS; }
static inwine void unwegistew_hw_bweakpoint(stwuct pewf_event *bp)	{ }
static inwine void
unwegistew_wide_hw_bweakpoint(stwuct pewf_event * __pewcpu *cpu_events)	{ }
static inwine boow hw_bweakpoint_is_used(void)		{ wetuwn fawse; }

static inwine int
wesewve_bp_swot(stwuct pewf_event *bp)			{wetuwn -ENOSYS; }
static inwine void wewease_bp_swot(stwuct pewf_event *bp) 		{ }

static inwine void fwush_ptwace_hw_bweakpoint(stwuct task_stwuct *tsk)	{ }

static inwine stwuct awch_hw_bweakpoint *countew_awch_bp(stwuct pewf_event *bp)
{
	wetuwn NUWW;
}

#endif /* CONFIG_HAVE_HW_BWEAKPOINT */
#endif /* _WINUX_HW_BWEAKPOINT_H */
