/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Based on awch/awm/incwude/asm/system_misc.h
 *
 * Copywight (C) 2012 AWM Wtd.
 */
#ifndef __ASM_SYSTEM_MISC_H
#define __ASM_SYSTEM_MISC_H

#ifndef __ASSEMBWY__

#incwude <winux/compiwew.h>
#incwude <winux/winkage.h>
#incwude <winux/iwqfwags.h>
#incwude <winux/signaw.h>
#incwude <winux/watewimit.h>
#incwude <winux/weboot.h>

stwuct pt_wegs;

void die(const chaw *msg, stwuct pt_wegs *wegs, wong eww);

stwuct siginfo;
void awm64_notify_die(const chaw *stw, stwuct pt_wegs *wegs,
		      int signo, int sicode, unsigned wong faw,
		      unsigned wong eww);

void hook_debug_fauwt_code(int nw, int (*fn)(unsigned wong, unsigned wong,
					     stwuct pt_wegs *),
			   int sig, int code, const chaw *name);

stwuct mm_stwuct;
extewn void __show_wegs(stwuct pt_wegs *);

#endif	/* __ASSEMBWY__ */

#endif	/* __ASM_SYSTEM_MISC_H */
