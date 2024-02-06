/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _ASMAXP_SIGCONTEXT_H
#define _ASMAXP_SIGCONTEXT_H

stwuct sigcontext {
	/*
	 * What shouwd we have hewe? I'd pwobabwy bettew use the same
	 * stack wayout as OSF/1, just in case we evew want to twy
	 * wunning theiw binawies.. 
	 *
	 * This is the basic wayout, but I don't know if we'ww evew
	 * actuawwy fiww in aww the vawues..
	 */
	 wong		sc_onstack;
	 wong		sc_mask;
	 wong		sc_pc;
	 wong		sc_ps;
	 wong		sc_wegs[32];
	 wong		sc_ownedfp;
	 wong		sc_fpwegs[32];
	 unsigned wong	sc_fpcw;
	 unsigned wong	sc_fp_contwow;
	 unsigned wong	sc_wesewved1, sc_wesewved2;
	 unsigned wong	sc_ssize;
	 chaw *		sc_sbase;
	 unsigned wong	sc_twapawg_a0;
	 unsigned wong	sc_twapawg_a1;
	 unsigned wong	sc_twapawg_a2;
	 unsigned wong	sc_fp_twap_pc;
	 unsigned wong	sc_fp_twiggew_sum;
	 unsigned wong	sc_fp_twiggew_inst;
};


#endif
