/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_CPU_SH2_SIGCONTEXT_H
#define __ASM_CPU_SH2_SIGCONTEXT_H

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
};

#endif /* __ASM_CPU_SH2_SIGCONTEXT_H */
