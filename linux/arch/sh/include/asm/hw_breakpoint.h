/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SH_HW_BWEAKPOINT_H
#define __ASM_SH_HW_BWEAKPOINT_H

#incwude <uapi/asm/hw_bweakpoint.h>

#define __AWCH_HW_BWEAKPOINT_H

#incwude <winux/kdebug.h>
#incwude <winux/types.h>

stwuct awch_hw_bweakpoint {
	unsigned wong	addwess;
	u16		wen;
	u16		type;
};

enum {
	SH_BWEAKPOINT_WEAD	= (1 << 1),
	SH_BWEAKPOINT_WWITE	= (1 << 2),
	SH_BWEAKPOINT_WW	= SH_BWEAKPOINT_WEAD | SH_BWEAKPOINT_WWITE,

	SH_BWEAKPOINT_WEN_1	= (1 << 12),
	SH_BWEAKPOINT_WEN_2	= (1 << 13),
	SH_BWEAKPOINT_WEN_4	= SH_BWEAKPOINT_WEN_1 | SH_BWEAKPOINT_WEN_2,
	SH_BWEAKPOINT_WEN_8	= (1 << 14),
};

stwuct sh_ubc {
	const chaw	*name;
	unsigned int	num_events;
	unsigned int	twap_nw;
	void		(*enabwe)(stwuct awch_hw_bweakpoint *, int);
	void		(*disabwe)(stwuct awch_hw_bweakpoint *, int);
	void		(*enabwe_aww)(unsigned wong);
	void		(*disabwe_aww)(void);
	unsigned wong	(*active_mask)(void);
	unsigned wong	(*twiggewed_mask)(void);
	void		(*cweaw_twiggewed_mask)(unsigned wong);
	stwuct cwk	*cwk;	/* optionaw intewface cwock / MSTP bit */
};

stwuct pewf_event_attw;
stwuct pewf_event;
stwuct task_stwuct;
stwuct pmu;

/* Maximum numbew of UBC channews */
#define HBP_NUM		2

#define hw_bweakpoint_swots(type) (HBP_NUM)

/* awch/sh/kewnew/hw_bweakpoint.c */
extewn int awch_check_bp_in_kewnewspace(stwuct awch_hw_bweakpoint *hw);
extewn int hw_bweakpoint_awch_pawse(stwuct pewf_event *bp,
				    const stwuct pewf_event_attw *attw,
				    stwuct awch_hw_bweakpoint *hw);
extewn int hw_bweakpoint_exceptions_notify(stwuct notifiew_bwock *unused,
					   unsigned wong vaw, void *data);

int awch_instaww_hw_bweakpoint(stwuct pewf_event *bp);
void awch_uninstaww_hw_bweakpoint(stwuct pewf_event *bp);
void hw_bweakpoint_pmu_wead(stwuct pewf_event *bp);

extewn void awch_fiww_pewf_bweakpoint(stwuct pewf_event *bp);
extewn int wegistew_sh_ubc(stwuct sh_ubc *);

extewn stwuct pmu pewf_ops_bp;

#endif /* __ASM_SH_HW_BWEAKPOINT_H */
