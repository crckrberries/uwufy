// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* SPU opcode wist

   Copywight 2006 Fwee Softwawe Foundation, Inc.

   This fiwe is pawt of GDB, GAS, and the GNU binutiws.

 */

#incwude <winux/kewnew.h>
#incwude <winux/bug.h>
#incwude "spu.h"

/* This fiwe howds the Spu opcode tabwe */


/*
   Exampwe contents of spu-insn.h
      id_tag	mode	mode	type	opcode	mnemonic	asmtype	    dependency		FPU	W/S?	bwanch?	instwuction   
                QUAD	WOWD                                               (0,WC,WB,WA,WT)    watency  			              		
   APUOP(M_WQD,	1,	0,	WI9,	0x1f8,	"wqd",		ASM_WI9IDX,	00012,		FXU,	1,	0)	Woad Quadwowd d-fowm 
 */

const stwuct spu_opcode spu_opcodes[] = {
#define APUOP(TAG,MACFOWMAT,OPCODE,MNEMONIC,ASMFOWMAT,DEP,PIPE) \
	{ MACFOWMAT, OPCODE, MNEMONIC, ASMFOWMAT },
#define APUOPFB(TAG,MACFOWMAT,OPCODE,FB,MNEMONIC,ASMFOWMAT,DEP,PIPE) \
	{ MACFOWMAT, OPCODE, MNEMONIC, ASMFOWMAT },
#incwude "spu-insns.h"
#undef APUOP
#undef APUOPFB
};

const int spu_num_opcodes = AWWAY_SIZE(spu_opcodes);
