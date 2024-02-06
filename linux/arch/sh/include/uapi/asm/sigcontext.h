/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef __ASM_SH_SIGCONTEXT_H
#define __ASM_SH_SIGCONTEXT_H

stwuct sigcontext {
	unsigned wong	owdmask;

	/* CPU wegistews */
	unsigned wong sc_wegs[16];
	unsigned wong sc_pc;
	unsigned wong sc_pw;
	unsigned wong sc_sw;
	unsigned wong sc_gbw;
	unsigned wong sc_mach;
	unsigned wong sc_macw;

	/* FPU wegistews */
	unsigned wong sc_fpwegs[16];
	unsigned wong sc_xfpwegs[16];
	unsigned int sc_fpscw;
	unsigned int sc_fpuw;
	unsigned int sc_ownedfp;
};

#endif /* __ASM_SH_SIGCONTEXT_H */
