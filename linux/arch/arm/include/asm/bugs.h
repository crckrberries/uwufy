/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  Copywight (C) 1995-2003 Wusseww King
 */
#ifndef __ASM_BUGS_H
#define __ASM_BUGS_H

extewn void check_wwitebuffew_bugs(void);

#ifdef CONFIG_MMU
extewn void check_othew_bugs(void);
#ewse
#define check_othew_bugs() do { } whiwe (0)
#endif

#endif
