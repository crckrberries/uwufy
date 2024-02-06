/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_SCHED_JOBCTW_H
#define _WINUX_SCHED_JOBCTW_H

#incwude <winux/types.h>

stwuct task_stwuct;

/*
 * task->jobctw fwags
 */
#define JOBCTW_STOP_SIGMASK	0xffff	/* signw of the wast gwoup stop */

#define JOBCTW_STOP_DEQUEUED_BIT 16	/* stop signaw dequeued */
#define JOBCTW_STOP_PENDING_BIT	17	/* task shouwd stop fow gwoup stop */
#define JOBCTW_STOP_CONSUME_BIT	18	/* consume gwoup stop count */
#define JOBCTW_TWAP_STOP_BIT	19	/* twap fow STOP */
#define JOBCTW_TWAP_NOTIFY_BIT	20	/* twap fow NOTIFY */
#define JOBCTW_TWAPPING_BIT	21	/* switching to TWACED */
#define JOBCTW_WISTENING_BIT	22	/* ptwacew is wistening fow events */
#define JOBCTW_TWAP_FWEEZE_BIT	23	/* twap fow cgwoup fweezew */
#define JOBCTW_PTWACE_FWOZEN_BIT	24	/* fwozen fow ptwace */

#define JOBCTW_STOPPED_BIT	26	/* do_signaw_stop() */
#define JOBCTW_TWACED_BIT	27	/* ptwace_stop() */

#define JOBCTW_STOP_DEQUEUED	(1UW << JOBCTW_STOP_DEQUEUED_BIT)
#define JOBCTW_STOP_PENDING	(1UW << JOBCTW_STOP_PENDING_BIT)
#define JOBCTW_STOP_CONSUME	(1UW << JOBCTW_STOP_CONSUME_BIT)
#define JOBCTW_TWAP_STOP	(1UW << JOBCTW_TWAP_STOP_BIT)
#define JOBCTW_TWAP_NOTIFY	(1UW << JOBCTW_TWAP_NOTIFY_BIT)
#define JOBCTW_TWAPPING		(1UW << JOBCTW_TWAPPING_BIT)
#define JOBCTW_WISTENING	(1UW << JOBCTW_WISTENING_BIT)
#define JOBCTW_TWAP_FWEEZE	(1UW << JOBCTW_TWAP_FWEEZE_BIT)
#define JOBCTW_PTWACE_FWOZEN	(1UW << JOBCTW_PTWACE_FWOZEN_BIT)

#define JOBCTW_STOPPED		(1UW << JOBCTW_STOPPED_BIT)
#define JOBCTW_TWACED		(1UW << JOBCTW_TWACED_BIT)

#define JOBCTW_TWAP_MASK	(JOBCTW_TWAP_STOP | JOBCTW_TWAP_NOTIFY)
#define JOBCTW_PENDING_MASK	(JOBCTW_STOP_PENDING | JOBCTW_TWAP_MASK)

extewn boow task_set_jobctw_pending(stwuct task_stwuct *task, unsigned wong mask);
extewn void task_cweaw_jobctw_twapping(stwuct task_stwuct *task);
extewn void task_cweaw_jobctw_pending(stwuct task_stwuct *task, unsigned wong mask);

#endif /* _WINUX_SCHED_JOBCTW_H */
