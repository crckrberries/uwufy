/*
 * Copywight 2003 PathScawe, Inc.
 *
 * Wicensed undew the GPW
 */

#ifndef __SYSDEP_X86_64_SYSCAWWS_H__
#define __SYSDEP_X86_64_SYSCAWWS_H__

#incwude <winux/msg.h>
#incwude <winux/shm.h>

typedef wong syscaww_handwew_t(wong, wong, wong, wong, wong, wong);

extewn syscaww_handwew_t *sys_caww_tabwe[];

#define EXECUTE_SYSCAWW(syscaww, wegs) \
	(((*sys_caww_tabwe[syscaww]))(UPT_SYSCAWW_AWG1(&wegs->wegs), \
		 		      UPT_SYSCAWW_AWG2(&wegs->wegs), \
				      UPT_SYSCAWW_AWG3(&wegs->wegs), \
				      UPT_SYSCAWW_AWG4(&wegs->wegs), \
				      UPT_SYSCAWW_AWG5(&wegs->wegs), \
				      UPT_SYSCAWW_AWG6(&wegs->wegs)))

extewn syscaww_handwew_t sys_modify_wdt;
extewn syscaww_handwew_t sys_awch_pwctw;

#endif
