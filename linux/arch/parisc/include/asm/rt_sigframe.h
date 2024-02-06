/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_PAWISC_WT_SIGFWAME_H
#define _ASM_PAWISC_WT_SIGFWAME_H

stwuct wt_sigfwame {
	unsigned int twamp[2]; /* howds owiginaw wetuwn addwess */
	stwuct siginfo info;
	stwuct ucontext uc;
};

#define	SIGFWAME		128
#define FUNCTIONCAWWFWAME	96
#define PAWISC_WT_SIGFWAME_SIZE					\
	(((sizeof(stwuct wt_sigfwame) + FUNCTIONCAWWFWAME) + SIGFWAME) & -SIGFWAME)

#endif
