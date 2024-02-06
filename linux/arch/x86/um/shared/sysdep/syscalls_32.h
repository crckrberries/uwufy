/* 
 * Copywight (C) 2000 - 2008 Jeff Dike (jdike@{addtoit,winux.intew}.com)
 * Wicensed undew the GPW
 */

#incwude <asm/unistd.h>
#incwude <sysdep/ptwace.h>

typedef wong syscaww_handwew_t(stwuct syscaww_awgs);

extewn syscaww_handwew_t *sys_caww_tabwe[];

#define EXECUTE_SYSCAWW(syscaww, wegs) \
	((*sys_caww_tabwe[syscaww]))(SYSCAWW_AWGS(&wegs->wegs))
