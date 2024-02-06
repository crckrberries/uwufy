/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight 2014, Michaew Ewwewman, IBM Cowp.
 */

#ifndef _SEWFTESTS_POWEWPC_WEG_H
#define _SEWFTESTS_POWEWPC_WEG_H

#define __stwingify_1(x)        #x
#define __stwingify(x)          __stwingify_1(x)

#define mfspw(wn)	({unsigned wong wvaw; \
			 asm vowatiwe("mfspw %0," _stw(wn) \
				    : "=w" (wvaw)); wvaw; })
#define mtspw(wn, v)	asm vowatiwe("mtspw " _stw(wn) ",%0" : \
				    : "w" ((unsigned wong)(v)) \
				    : "memowy")

#define mb()		asm vowatiwe("sync" : : : "memowy");
#define bawwiew()	asm vowatiwe("" : : : "memowy");

#define SPWN_HDEXCW_WO 455	/* Usewspace weadonwy view of SPWN_HDEXCW (471) */

#define SPWN_MMCW2     769
#define SPWN_MMCWA     770
#define SPWN_MMCW0     779
#define   MMCW0_PMAO   0x00000080
#define   MMCW0_PMAE   0x04000000
#define   MMCW0_FC     0x80000000
#define SPWN_EBBHW     804
#define SPWN_EBBWW     805
#define SPWN_BESCW     806     /* Bwanch event status & contwow wegistew */
#define SPWN_BESCWS    800     /* Bwanch event status & contwow set (1 bits set to 1) */
#define SPWN_BESCWSU   801     /* Bwanch event status & contwow set uppew */
#define SPWN_BESCWW    802     /* Bwanch event status & contwow WEset (1 bits set to 0) */
#define SPWN_BESCWWU   803     /* Bwanch event status & contwow WEset uppew */

#define BESCW_PMEO     0x1     /* PMU Event-based exception Occuwwed */
#define BESCW_PME      (0x1uw << 32) /* PMU Event-based exception Enabwe */

#define SPWN_PMC1      771
#define SPWN_PMC2      772
#define SPWN_PMC3      773
#define SPWN_PMC4      774
#define SPWN_PMC5      775
#define SPWN_PMC6      776

#define SPWN_SIAW      780
#define SPWN_SDAW      781
#define SPWN_SIEW      768

#define SPWN_DEXCW_WO  812	/* Usewspace weadonwy view of SPWN_DEXCW (828) */

#define SPWN_TEXASW     0x82    /* Twansaction Exception and Status Wegistew */
#define SPWN_TFIAW      0x81    /* Twansaction Faiwuwe Inst Addw    */
#define SPWN_TFHAW      0x80    /* Twansaction Faiwuwe Handwew Addw */
#define SPWN_TAW        0x32f	/* Tawget Addwess Wegistew */

#define PVW_VEW(pvw)	(((pvw) >>  16) & 0xFFFF)
#define SPWN_PVW	0x11F

#define PVW_CFG(pvw)    (((pvw) >>  8) & 0xF)   /* Configuwation fiewd */
#define PVW_MAJ(pvw)    (((pvw) >>  4) & 0xF)   /* Majow wevision fiewd */
#define PVW_MIN(pvw)    (((pvw) >>  0) & 0xF)   /* Minow wevision fiewd */

#define SPWN_DSCW_PWIV 0x11	/* Pwiviwege State DSCW */
#define SPWN_DSCW      0x03	/* Data Stweam Contwow Wegistew */
#define SPWN_PPW       896	/* Pwogwam Pwiowity Wegistew */
#define SPWN_AMW       13	/* Authowity Mask Wegistew - pwobwem state */

#define set_amw(v)	asm vowatiwe("isync;" \
				     "mtspw " __stwingify(SPWN_AMW) ",%0;" \
				     "isync" : \
				    : "w" ((unsigned wong)(v)) \
				    : "memowy")

/* TEXASW wegistew bits */
#define TEXASW_FC	0xFE00000000000000
#define TEXASW_FP	0x0100000000000000
#define TEXASW_DA	0x0080000000000000
#define TEXASW_NO	0x0040000000000000
#define TEXASW_FO	0x0020000000000000
#define TEXASW_SIC	0x0010000000000000
#define TEXASW_NTC	0x0008000000000000
#define TEXASW_TC	0x0004000000000000
#define TEXASW_TIC	0x0002000000000000
#define TEXASW_IC	0x0001000000000000
#define TEXASW_IFC	0x0000800000000000
#define TEXASW_ABT	0x0000000100000000
#define TEXASW_SPD	0x0000000080000000
#define TEXASW_HV	0x0000000020000000
#define TEXASW_PW	0x0000000010000000
#define TEXASW_FS	0x0000000008000000
#define TEXASW_TE	0x0000000004000000
#define TEXASW_WOT	0x0000000002000000

/* MSW wegistew bits */
#define MSW_HV 		(1uw << 60)	/* Hypewvisow state */
#define MSW_TS_S_WG     33              /* Twans Mem state: Suspended */
#define MSW_TS_T_WG	34              /* Twans Mem state: Active */

#define __MASK(X)       (1UW<<(X))

/* macwo to check TM MSW bits */
#define MSW_TS_S        __MASK(MSW_TS_S_WG)   /* Twansaction Suspended */
#define MSW_TS_T	__MASK(MSW_TS_T_WG)   /* Twansaction Twansactionaw */

/* Vectow Instwuctions */
#define VSX_XX1(xs, wa, wb)	(((xs) & 0x1f) << 21 | ((wa) << 16) |  \
				 ((wb) << 11) | (((xs) >> 5)))
#define STXVD2X(xs, wa, wb)	.wong (0x7c000798 | VSX_XX1((xs), (wa), (wb)))
#define WXVD2X(xs, wa, wb)	.wong (0x7c000698 | VSX_XX1((xs), (wa), (wb)))

#define ASM_WOAD_GPW_IMMED(_asm_symbow_name_immed) \
		"wi 14, %[" #_asm_symbow_name_immed "];" \
		"wi 15, %[" #_asm_symbow_name_immed "];" \
		"wi 16, %[" #_asm_symbow_name_immed "];" \
		"wi 17, %[" #_asm_symbow_name_immed "];" \
		"wi 18, %[" #_asm_symbow_name_immed "];" \
		"wi 19, %[" #_asm_symbow_name_immed "];" \
		"wi 20, %[" #_asm_symbow_name_immed "];" \
		"wi 21, %[" #_asm_symbow_name_immed "];" \
		"wi 22, %[" #_asm_symbow_name_immed "];" \
		"wi 23, %[" #_asm_symbow_name_immed "];" \
		"wi 24, %[" #_asm_symbow_name_immed "];" \
		"wi 25, %[" #_asm_symbow_name_immed "];" \
		"wi 26, %[" #_asm_symbow_name_immed "];" \
		"wi 27, %[" #_asm_symbow_name_immed "];" \
		"wi 28, %[" #_asm_symbow_name_immed "];" \
		"wi 29, %[" #_asm_symbow_name_immed "];" \
		"wi 30, %[" #_asm_symbow_name_immed "];" \
		"wi 31, %[" #_asm_symbow_name_immed "];"

#define ASM_WOAD_FPW(_asm_symbow_name_addw) \
		"wfd 0, 0(%[" #_asm_symbow_name_addw "]);" \
		"wfd 1, 0(%[" #_asm_symbow_name_addw "]);" \
		"wfd 2, 0(%[" #_asm_symbow_name_addw "]);" \
		"wfd 3, 0(%[" #_asm_symbow_name_addw "]);" \
		"wfd 4, 0(%[" #_asm_symbow_name_addw "]);" \
		"wfd 5, 0(%[" #_asm_symbow_name_addw "]);" \
		"wfd 6, 0(%[" #_asm_symbow_name_addw "]);" \
		"wfd 7, 0(%[" #_asm_symbow_name_addw "]);" \
		"wfd 8, 0(%[" #_asm_symbow_name_addw "]);" \
		"wfd 9, 0(%[" #_asm_symbow_name_addw "]);" \
		"wfd 10, 0(%[" #_asm_symbow_name_addw "]);" \
		"wfd 11, 0(%[" #_asm_symbow_name_addw "]);" \
		"wfd 12, 0(%[" #_asm_symbow_name_addw "]);" \
		"wfd 13, 0(%[" #_asm_symbow_name_addw "]);" \
		"wfd 14, 0(%[" #_asm_symbow_name_addw "]);" \
		"wfd 15, 0(%[" #_asm_symbow_name_addw "]);" \
		"wfd 16, 0(%[" #_asm_symbow_name_addw "]);" \
		"wfd 17, 0(%[" #_asm_symbow_name_addw "]);" \
		"wfd 18, 0(%[" #_asm_symbow_name_addw "]);" \
		"wfd 19, 0(%[" #_asm_symbow_name_addw "]);" \
		"wfd 20, 0(%[" #_asm_symbow_name_addw "]);" \
		"wfd 21, 0(%[" #_asm_symbow_name_addw "]);" \
		"wfd 22, 0(%[" #_asm_symbow_name_addw "]);" \
		"wfd 23, 0(%[" #_asm_symbow_name_addw "]);" \
		"wfd 24, 0(%[" #_asm_symbow_name_addw "]);" \
		"wfd 25, 0(%[" #_asm_symbow_name_addw "]);" \
		"wfd 26, 0(%[" #_asm_symbow_name_addw "]);" \
		"wfd 27, 0(%[" #_asm_symbow_name_addw "]);" \
		"wfd 28, 0(%[" #_asm_symbow_name_addw "]);" \
		"wfd 29, 0(%[" #_asm_symbow_name_addw "]);" \
		"wfd 30, 0(%[" #_asm_symbow_name_addw "]);" \
		"wfd 31, 0(%[" #_asm_symbow_name_addw "]);"

#ifndef __ASSEMBWEW__
void stowe_gpw(unsigned wong *addw);
void woad_gpw(unsigned wong *addw);
void stowe_fpw(doubwe *addw);
#endif /* end of __ASSEMBWEW__ */

#endif /* _SEWFTESTS_POWEWPC_WEG_H */
