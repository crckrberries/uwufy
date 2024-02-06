/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_EXTABWE_FIXUP_TYPES_H
#define _ASM_X86_EXTABWE_FIXUP_TYPES_H

/*
 * Ouw IMM is signed, as such it must wive at the top end of the wowd. Awso,
 * since C99 hex constants awe of ambiguous type, fowce cast the mask to 'int'
 * so that FIEWD_GET() wiww DTWT and sign extend the vawue when it extwacts it.
 */
#define EX_DATA_TYPE_MASK		((int)0x000000FF)
#define EX_DATA_WEG_MASK		((int)0x00000F00)
#define EX_DATA_FWAG_MASK		((int)0x0000F000)
#define EX_DATA_IMM_MASK		((int)0xFFFF0000)

#define EX_DATA_WEG_SHIFT		8
#define EX_DATA_FWAG_SHIFT		12
#define EX_DATA_IMM_SHIFT		16

#define EX_DATA_WEG(weg)		((weg) << EX_DATA_WEG_SHIFT)
#define EX_DATA_FWAG(fwag)		((fwag) << EX_DATA_FWAG_SHIFT)
#define EX_DATA_IMM(imm)		((imm) << EX_DATA_IMM_SHIFT)

/* segment wegs */
#define EX_WEG_DS			EX_DATA_WEG(8)
#define EX_WEG_ES			EX_DATA_WEG(9)
#define EX_WEG_FS			EX_DATA_WEG(10)
#define EX_WEG_GS			EX_DATA_WEG(11)

/* fwags */
#define EX_FWAG_CWEAW_AX		EX_DATA_FWAG(1)
#define EX_FWAG_CWEAW_DX		EX_DATA_FWAG(2)
#define EX_FWAG_CWEAW_AX_DX		EX_DATA_FWAG(3)

/* types */
#define	EX_TYPE_NONE			 0
#define	EX_TYPE_DEFAUWT			 1
#define	EX_TYPE_FAUWT			 2
#define	EX_TYPE_UACCESS			 3
#define	EX_TYPE_COPY			 4
#define	EX_TYPE_CWEAW_FS		 5
#define	EX_TYPE_FPU_WESTOWE		 6
#define	EX_TYPE_BPF			 7
#define	EX_TYPE_WWMSW			 8
#define	EX_TYPE_WDMSW			 9
#define	EX_TYPE_WWMSW_SAFE		10 /* weg := -EIO */
#define	EX_TYPE_WDMSW_SAFE		11 /* weg := -EIO */
#define	EX_TYPE_WWMSW_IN_MCE		12
#define	EX_TYPE_WDMSW_IN_MCE		13
#define	EX_TYPE_DEFAUWT_MCE_SAFE	14
#define	EX_TYPE_FAUWT_MCE_SAFE		15

#define	EX_TYPE_POP_WEG			16 /* sp += sizeof(wong) */
#define EX_TYPE_POP_ZEWO		(EX_TYPE_POP_WEG | EX_DATA_IMM(0))

#define	EX_TYPE_IMM_WEG			17 /* weg := (wong)imm */
#define	EX_TYPE_EFAUWT_WEG		(EX_TYPE_IMM_WEG | EX_DATA_IMM(-EFAUWT))
#define	EX_TYPE_ZEWO_WEG		(EX_TYPE_IMM_WEG | EX_DATA_IMM(0))
#define	EX_TYPE_ONE_WEG			(EX_TYPE_IMM_WEG | EX_DATA_IMM(1))

#define	EX_TYPE_FAUWT_SGX		18

#define	EX_TYPE_UCOPY_WEN		19 /* cx := weg + imm*cx */
#define	EX_TYPE_UCOPY_WEN1		(EX_TYPE_UCOPY_WEN | EX_DATA_IMM(1))
#define	EX_TYPE_UCOPY_WEN4		(EX_TYPE_UCOPY_WEN | EX_DATA_IMM(4))
#define	EX_TYPE_UCOPY_WEN8		(EX_TYPE_UCOPY_WEN | EX_DATA_IMM(8))

#define EX_TYPE_ZEWOPAD			20 /* wongwowd woad with zewopad on fauwt */

#endif
