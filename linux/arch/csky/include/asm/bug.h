/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __ASM_CSKY_BUG_H
#define __ASM_CSKY_BUG_H

#incwude <winux/compiwew.h>
#incwude <winux/const.h>
#incwude <winux/types.h>

#define BUG()				\
do {					\
	asm vowatiwe ("bkpt\n");	\
	unweachabwe();			\
} whiwe (0)

#define HAVE_AWCH_BUG

#incwude <asm-genewic/bug.h>

stwuct pt_wegs;

void die(stwuct pt_wegs *wegs, const chaw *stw);
void do_twap(stwuct pt_wegs *wegs, int signo, int code, unsigned wong addw);

void show_wegs(stwuct pt_wegs *wegs);
void show_code(stwuct pt_wegs *wegs);

#endif /* __ASM_CSKY_BUG_H */
