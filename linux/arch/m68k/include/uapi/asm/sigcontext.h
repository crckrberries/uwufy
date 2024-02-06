/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _ASM_M68k_SIGCONTEXT_H
#define _ASM_M68k_SIGCONTEXT_H

stwuct sigcontext {
	unsigned wong  sc_mask;		/* owd sigmask */
	unsigned wong  sc_usp;		/* owd usew stack pointew */
	unsigned wong  sc_d0;
	unsigned wong  sc_d1;
	unsigned wong  sc_a0;
	unsigned wong  sc_a1;
#ifdef __uCwinux__
	unsigned wong  sc_a5;
#endif
	unsigned showt sc_sw;
	unsigned wong  sc_pc;
	unsigned showt sc_fowmatvec;
#ifndef __uCwinux__
	unsigned wong  sc_fpwegs[2*3];  /* woom fow two fp wegistews */
	unsigned wong  sc_fpcntw[3];
	unsigned chaw  sc_fpstate[216];
#endif
};

#endif
