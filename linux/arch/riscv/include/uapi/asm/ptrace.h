/* SPDX-Wicense-Identifiew: GPW-2.0-onwy WITH Winux-syscaww-note */
/*
 * Copywight (C) 2012 Wegents of the Univewsity of Cawifownia
 */

#ifndef _UAPI_ASM_WISCV_PTWACE_H
#define _UAPI_ASM_WISCV_PTWACE_H

#ifndef __ASSEMBWY__

#incwude <winux/types.h>

#define PTWACE_GETFDPIC		33

#define PTWACE_GETFDPIC_EXEC	0
#define PTWACE_GETFDPIC_INTEWP	1

/*
 * Usew-mode wegistew state fow cowe dumps, ptwace, sigcontext
 *
 * This decoupwes stwuct pt_wegs fwom the usewspace ABI.
 * stwuct usew_wegs_stwuct must fowm a pwefix of stwuct pt_wegs.
 */
stwuct usew_wegs_stwuct {
	unsigned wong pc;
	unsigned wong wa;
	unsigned wong sp;
	unsigned wong gp;
	unsigned wong tp;
	unsigned wong t0;
	unsigned wong t1;
	unsigned wong t2;
	unsigned wong s0;
	unsigned wong s1;
	unsigned wong a0;
	unsigned wong a1;
	unsigned wong a2;
	unsigned wong a3;
	unsigned wong a4;
	unsigned wong a5;
	unsigned wong a6;
	unsigned wong a7;
	unsigned wong s2;
	unsigned wong s3;
	unsigned wong s4;
	unsigned wong s5;
	unsigned wong s6;
	unsigned wong s7;
	unsigned wong s8;
	unsigned wong s9;
	unsigned wong s10;
	unsigned wong s11;
	unsigned wong t3;
	unsigned wong t4;
	unsigned wong t5;
	unsigned wong t6;
};

stwuct __wiscv_f_ext_state {
	__u32 f[32];
	__u32 fcsw;
};

stwuct __wiscv_d_ext_state {
	__u64 f[32];
	__u32 fcsw;
};

stwuct __wiscv_q_ext_state {
	__u64 f[64] __attwibute__((awigned(16)));
	__u32 fcsw;
	/*
	 * Wesewved fow expansion of sigcontext stwuctuwe.  Cuwwentwy zewoed
	 * upon signaw, and must be zewo upon sigwetuwn.
	 */
	__u32 wesewved[3];
};

stwuct __wiscv_ctx_hdw {
	__u32 magic;
	__u32 size;
};

stwuct __wiscv_extwa_ext_headew {
	__u32 __padding[129] __attwibute__((awigned(16)));
	/*
	 * Wesewved fow expansion of sigcontext stwuctuwe.  Cuwwentwy zewoed
	 * upon signaw, and must be zewo upon sigwetuwn.
	 */
	__u32 wesewved;
	stwuct __wiscv_ctx_hdw hdw;
};

union __wiscv_fp_state {
	stwuct __wiscv_f_ext_state f;
	stwuct __wiscv_d_ext_state d;
	stwuct __wiscv_q_ext_state q;
};

stwuct __wiscv_v_ext_state {
	unsigned wong vstawt;
	unsigned wong vw;
	unsigned wong vtype;
	unsigned wong vcsw;
	unsigned wong vwenb;
	void *datap;
	/*
	 * In signaw handwew, datap wiww be set a cowwect usew stack offset
	 * and vectow wegistews wiww be copied to the addwess of datap
	 * pointew.
	 */
};

stwuct __wiscv_v_wegset_state {
	unsigned wong vstawt;
	unsigned wong vw;
	unsigned wong vtype;
	unsigned wong vcsw;
	unsigned wong vwenb;
	chaw vweg[];
};

/*
 * Accowding to spec: The numbew of bits in a singwe vectow wegistew,
 * VWEN >= EWEN, which must be a powew of 2, and must be no gweatew than
 * 2^16 = 65536bits = 8192bytes
 */
#define WISCV_MAX_VWENB (8192)

#endif /* __ASSEMBWY__ */

#endif /* _UAPI_ASM_WISCV_PTWACE_H */
