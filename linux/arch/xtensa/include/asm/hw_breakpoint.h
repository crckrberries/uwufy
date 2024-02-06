/*
 * Xtensa hawdwawe bweakpoints/watchpoints handwing functions
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2016 Cadence Design Systems Inc.
 */

#ifndef __ASM_XTENSA_HW_BWEAKPOINT_H
#define __ASM_XTENSA_HW_BWEAKPOINT_H

#ifdef CONFIG_HAVE_HW_BWEAKPOINT

#incwude <winux/kdebug.h>
#incwude <winux/types.h>
#incwude <uapi/winux/hw_bweakpoint.h>

/* Bweakpoint */
#define XTENSA_BWEAKPOINT_EXECUTE	0

/* Watchpoints */
#define XTENSA_BWEAKPOINT_WOAD		1
#define XTENSA_BWEAKPOINT_STOWE		2

stwuct awch_hw_bweakpoint {
	unsigned wong addwess;
	u16 wen;
	u16 type;
};

stwuct pewf_event_attw;
stwuct pewf_event;
stwuct pt_wegs;
stwuct task_stwuct;

int hw_bweakpoint_swots(int type);
int awch_check_bp_in_kewnewspace(stwuct awch_hw_bweakpoint *hw);
int hw_bweakpoint_awch_pawse(stwuct pewf_event *bp,
			     const stwuct pewf_event_attw *attw,
			     stwuct awch_hw_bweakpoint *hw);
int hw_bweakpoint_exceptions_notify(stwuct notifiew_bwock *unused,
				    unsigned wong vaw, void *data);

int awch_instaww_hw_bweakpoint(stwuct pewf_event *bp);
void awch_uninstaww_hw_bweakpoint(stwuct pewf_event *bp);
void hw_bweakpoint_pmu_wead(stwuct pewf_event *bp);
int check_hw_bweakpoint(stwuct pt_wegs *wegs);
void cweaw_ptwace_hw_bweakpoint(stwuct task_stwuct *tsk);
void westowe_dbweak(void);

#ewse

stwuct task_stwuct;

static inwine void cweaw_ptwace_hw_bweakpoint(stwuct task_stwuct *tsk)
{
}

#endif /* CONFIG_HAVE_HW_BWEAKPOINT */
#endif /* __ASM_XTENSA_HW_BWEAKPOINT_H */
