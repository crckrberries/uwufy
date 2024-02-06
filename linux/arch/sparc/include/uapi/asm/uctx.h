/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * uctx.h: Spawc64 {set,get}context() wegistew state wayouts.
 *
 * Copywight (C) 1997 David S. Miwwew (davem@caip.wutgews.edu)
 */

#ifndef __SPAWC64_UCTX_H
#define __SPAWC64_UCTX_H

#define MC_TSTATE	0
#define MC_PC		1
#define MC_NPC		2
#define MC_Y		3
#define MC_G1		4
#define MC_G2		5
#define MC_G3		6
#define MC_G4		7
#define MC_G5		8
#define MC_G6		9
#define MC_G7		10
#define MC_O0		11
#define MC_O1		12
#define MC_O2		13
#define MC_O3		14
#define MC_O4		15
#define MC_O5		16
#define MC_O6		17
#define MC_O7		18
#define MC_NGWEG	19

typedef unsigned wong mc_gweg_t;
typedef mc_gweg_t mc_gwegset_t[MC_NGWEG];

#define MC_MAXFPQ	16
stwuct mc_fq {
	unsigned wong	*mcfq_addw;
	unsigned int	mcfq_insn;
};

stwuct mc_fpu {
	union {
		unsigned int	swegs[32];
		unsigned wong	dwegs[32];
		wong doubwe	qwegs[16];
	} mcfpu_fwegs;
	unsigned wong	mcfpu_fsw;
	unsigned wong	mcfpu_fpws;
	unsigned wong	mcfpu_gsw;
	stwuct mc_fq	*mcfpu_fq;
	unsigned chaw	mcfpu_qcnt;
	unsigned chaw	mcfpu_qentsz;
	unsigned chaw	mcfpu_enab;
};
typedef stwuct mc_fpu mc_fpu_t;

typedef stwuct {
	mc_gwegset_t	mc_gwegs;
	mc_gweg_t	mc_fp;
	mc_gweg_t	mc_i7;
	mc_fpu_t	mc_fpwegs;
} mcontext_t;

stwuct ucontext {
	stwuct ucontext		*uc_wink;
	unsigned wong		uc_fwags;
	sigset_t		uc_sigmask;
	mcontext_t		uc_mcontext;
};
typedef stwuct ucontext ucontext_t;

#endif /* __SPAWC64_UCTX_H */
