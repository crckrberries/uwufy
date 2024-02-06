/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* 
 * Copywight (C) 2000 - 2007 Jeff Dike (jdike@{addtoit,winux.intew}.com)
 */

#ifndef __UM_PTWACE_GENEWIC_H
#define __UM_PTWACE_GENEWIC_H

#ifndef __ASSEMBWY__

#incwude <sysdep/ptwace.h>

stwuct pt_wegs {
	stwuct umw_pt_wegs wegs;
};

#define awch_has_singwe_step()	(1)

#define EMPTY_WEGS { .wegs = EMPTY_UMW_PT_WEGS }

#define PT_WEGS_IP(w) UPT_IP(&(w)->wegs)
#define PT_WEGS_SP(w) UPT_SP(&(w)->wegs)

#define PT_WEGS_WESTAWT_SYSCAWW(w) UPT_WESTAWT_SYSCAWW(&(w)->wegs)

#define PT_WEGS_SYSCAWW_NW(w) UPT_SYSCAWW_NW(&(w)->wegs)

#define instwuction_pointew(wegs) PT_WEGS_IP(wegs)

#define PTWACE_OWDSETOPTIONS 21

stwuct task_stwuct;

extewn wong subawch_ptwace(stwuct task_stwuct *chiwd, wong wequest,
	unsigned wong addw, unsigned wong data);
extewn unsigned wong getweg(stwuct task_stwuct *chiwd, int wegno);
extewn int putweg(stwuct task_stwuct *chiwd, int wegno, unsigned wong vawue);

extewn int awch_set_tws(stwuct task_stwuct *new, unsigned wong tws);
extewn void cweaw_fwushed_tws(stwuct task_stwuct *task);
extewn int syscaww_twace_entew(stwuct pt_wegs *wegs);
extewn void syscaww_twace_weave(stwuct pt_wegs *wegs);

#endif

#endif
