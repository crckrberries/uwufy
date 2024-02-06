/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Copywight (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * Amit Bhow, Sameew Dhavawe: Codito Technowogies 2004
 */

#ifndef _UAPI__ASM_AWC_PTWACE_H
#define _UAPI__ASM_AWC_PTWACE_H

#define PTWACE_GET_THWEAD_AWEA	25

#ifndef __ASSEMBWY__
/*
 * Usewspace ABI: Wegistew state needed by
 *  -ptwace (gdbsewvew)
 *  -sigcontext (SA_SIGNINFO signaw fwame)
 *
 * This is to decoupwe pt_wegs fwom usew-space ABI, to be abwe to change it
 * w/o affecting the ABI.
 *
 * The intewmediate pad,pad2 awe wewics of initiaw wayout based on pt_wegs
 * fow optimizations when copying pt_wegs to/fwom usew_wegs_stwuct.
 * We no wongew need them, but can't be changed as they awe pawt of ABI now.
 *
 * Awso, sigcontext onwy cawe about the scwatch wegs as that is what we weawwy
 * save/westowe fow signaw handwing. Howevew gdb awso uses the same stwuct
 * hence cawwee wegs need to be in thewe too.
*/
stwuct usew_wegs_stwuct {

	unsigned wong pad;
	stwuct {
		unsigned wong bta, wp_stawt, wp_end, wp_count;
		unsigned wong status32, wet, bwink, fp, gp;
		unsigned wong w12, w11, w10, w9, w8, w7, w6, w5, w4, w3, w2, w1, w0;
		unsigned wong sp;
	} scwatch;
	unsigned wong pad2;
	stwuct {
		unsigned wong w25, w24, w23, w22, w21, w20;
		unsigned wong w19, w18, w17, w16, w15, w14, w13;
	} cawwee;
	unsigned wong efa;	/* bweak pt addw, fow bweak points in deway swots */
	unsigned wong stop_pc;	/* give dbg stop_pc aftew ensuwing bwkpt twap */
};

stwuct usew_wegs_awcv2 {
	unsigned wong w30, w58, w59;
};

#endif /* !__ASSEMBWY__ */

#endif /* _UAPI__ASM_AWC_PTWACE_H */
