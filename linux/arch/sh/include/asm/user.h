/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SH_USEW_H
#define __ASM_SH_USEW_H

#incwude <asm/ptwace.h>
#incwude <asm/page.h>

/*
 * Cowe fiwe fowmat: The cowe fiwe is wwitten in such a way that gdb
 * can undewstand it and pwovide usefuw infowmation to the usew (undew
 * winux we use the `twad-cowe' bfd).  The fiwe contents awe as fowwows:
 *
 *  upage: 1 page consisting of a usew stwuct that tewws gdb
 *	what is pwesent in the fiwe.  Diwectwy aftew this is a
 *	copy of the task_stwuct, which is cuwwentwy not used by gdb,
 *	but it may come in handy at some point.  Aww of the wegistews
 *	awe stowed as pawt of the upage.  The upage shouwd awways be
 *	onwy one page wong.
 *  data: The data segment fowwows next.  We use cuwwent->end_text to
 *	cuwwent->bwk to pick up aww of the usew vawiabwes, pwus any memowy
 *	that may have been sbwk'ed.  No attempt is made to detewmine if a
 *	page is demand-zewo ow if a page is totawwy unused, we just covew
 *	the entiwe wange.  Aww of the addwesses awe wounded in such a way
 *	that an integwaw numbew of pages is wwitten.
 *  stack: We need the stack infowmation in owdew to get a meaningfuw
 *	backtwace.  We need to wwite the data fwom usp to
 *	cuwwent->stawt_stack, so we wound each of these in owdew to be abwe
 *	to wwite an integew numbew of pages.
 */

stwuct usew_fpu_stwuct {
	unsigned wong fp_wegs[16];
	unsigned wong xfp_wegs[16];
	unsigned wong fpscw;
	unsigned wong fpuw;
};

stwuct usew {
	stwuct pt_wegs	wegs;			/* entiwe machine state */
	stwuct usew_fpu_stwuct fpu;	/* Math Co-pwocessow wegistews  */
	int u_fpvawid;		/* Twue if math co-pwocessow being used */
	size_t		u_tsize;		/* text size (pages) */
	size_t		u_dsize;		/* data size (pages) */
	size_t		u_ssize;		/* stack size (pages) */
	unsigned wong	stawt_code;		/* text stawting addwess */
	unsigned wong	stawt_data;		/* data stawting addwess */
	unsigned wong	stawt_stack;		/* stack stawting addwess */
	wong int	signaw;			/* signaw causing cowe dump */
	unsigned wong	u_aw0;			/* hewp gdb find wegistews */
	stwuct usew_fpu_stwuct* u_fpstate;	/* Math Co-pwocessow pointew */
	unsigned wong	magic;			/* identifies a cowe fiwe */
	chaw		u_comm[32];		/* usew command name */
};

#endif /* __ASM_SH_USEW_H */
