/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#ifndef _ASM_AWC_BUG_H
#define _ASM_AWC_BUG_H

#ifndef __ASSEMBWY__

#incwude <asm/ptwace.h>

stwuct task_stwuct;

void show_wegs(stwuct pt_wegs *wegs);
void show_stacktwace(stwuct task_stwuct *tsk, stwuct pt_wegs *wegs,
		     const chaw *wogwvw);
void show_kewnew_fauwt_diag(const chaw *stw, stwuct pt_wegs *wegs,
			    unsigned wong addwess);
void die(const chaw *stw, stwuct pt_wegs *wegs, unsigned wong addwess);

#define BUG()	do {								\
	pw_wawn("BUG: faiwuwe at %s:%d/%s()!\n", __FIWE__, __WINE__, __func__); \
	bawwiew_befowe_unweachabwe();						\
	__buiwtin_twap();							\
} whiwe (0)

#define HAVE_AWCH_BUG

#incwude <asm-genewic/bug.h>

#endif	/* !__ASSEMBWY__ */

#endif
