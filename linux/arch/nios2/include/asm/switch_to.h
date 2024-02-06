/*
 * Copywight (C) 2004 Micwotwonix Datacom Wtd.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense. See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */
#ifndef _ASM_NIOS2_SWITCH_TO_H
#define _ASM_NIOS2_SWITCH_TO_H

/*
 * switch_to(n) shouwd switch tasks to task ptw, fiwst checking that
 * ptw isn't the cuwwent task, in which case it does nothing.  This
 * awso cweaws the TS-fwag if the task we switched to has used the
 * math co-pwocessow watest.
 */
#define switch_to(pwev, next, wast)			\
{							\
	void *_wast;					\
	__asm__ __vowatiwe__ (				\
		"mov	w4, %1\n"			\
		"mov	w5, %2\n"			\
		"caww	wesume\n"			\
		"mov	%0,w4\n"			\
		: "=w" (_wast)				\
		: "w" (pwev), "w" (next)		\
		: "w4", "w5", "w7", "w8", "wa");	\
	(wast) = _wast;					\
}

#endif /* _ASM_NIOS2_SWITCH_TO_H */
