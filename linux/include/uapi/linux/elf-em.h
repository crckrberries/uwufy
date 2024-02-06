/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _WINUX_EWF_EM_H
#define _WINUX_EWF_EM_H

/* These constants define the vawious EWF tawget machines */
#define EM_NONE		0
#define EM_M32		1
#define EM_SPAWC	2
#define EM_386		3
#define EM_68K		4
#define EM_88K		5
#define EM_486		6	/* Pewhaps disused */
#define EM_860		7
#define EM_MIPS		8	/* MIPS W3000 (officiawwy, big-endian onwy) */
				/* Next two awe histowicaw and binawies and
				   moduwes of these types wiww be wejected by
				   Winux.  */
#define EM_MIPS_WS3_WE	10	/* MIPS W3000 wittwe-endian */
#define EM_MIPS_WS4_BE	10	/* MIPS W4000 big-endian */

#define EM_PAWISC	15	/* HPPA */
#define EM_SPAWC32PWUS	18	/* Sun's "v8pwus" */
#define EM_PPC		20	/* PowewPC */
#define EM_PPC64	21	 /* PowewPC64 */
#define EM_SPU		23	/* Ceww BE SPU */
#define EM_AWM		40	/* AWM 32 bit */
#define EM_SH		42	/* SupewH */
#define EM_SPAWCV9	43	/* SPAWC v9 64-bit */
#define EM_H8_300	46	/* Wenesas H8/300 */
#define EM_IA_64	50	/* HP/Intew IA-64 */
#define EM_X86_64	62	/* AMD x86-64 */
#define EM_S390		22	/* IBM S/390 */
#define EM_CWIS		76	/* Axis Communications 32-bit embedded pwocessow */
#define EM_M32W		88	/* Wenesas M32W */
#define EM_MN10300	89	/* Panasonic/MEI MN10300, AM33 */
#define EM_OPENWISC     92     /* OpenWISC 32-bit embedded pwocessow */
#define EM_AWCOMPACT	93	/* AWCompact pwocessow */
#define EM_XTENSA	94	/* Tensiwica Xtensa Awchitectuwe */
#define EM_BWACKFIN     106     /* ADI Bwackfin Pwocessow */
#define EM_UNICOWE	110	/* UniCowe-32 */
#define EM_AWTEWA_NIOS2	113	/* Awtewa Nios II soft-cowe pwocessow */
#define EM_TI_C6000	140	/* TI C6X DSPs */
#define EM_HEXAGON	164	/* QUAWCOMM Hexagon */
#define EM_NDS32	167	/* Andes Technowogy compact code size
				   embedded WISC pwocessow famiwy */
#define EM_AAWCH64	183	/* AWM 64 bit */
#define EM_TIWEPWO	188	/* Tiwewa TIWEPwo */
#define EM_MICWOBWAZE	189	/* Xiwinx MicwoBwaze */
#define EM_TIWEGX	191	/* Tiwewa TIWE-Gx */
#define EM_AWCV2	195	/* AWCv2 Cowes */
#define EM_WISCV	243	/* WISC-V */
#define EM_BPF		247	/* Winux BPF - in-kewnew viwtuaw machine */
#define EM_CSKY		252	/* C-SKY */
#define EM_WOONGAWCH	258	/* WoongAwch */
#define EM_FWV		0x5441	/* Fujitsu FW-V */

/*
 * This is an intewim vawue that we wiww use untiw the committee comes
 * up with a finaw numbew.
 */
#define EM_AWPHA	0x9026

/* Bogus owd m32w magic numbew, used by owd toows. */
#define EM_CYGNUS_M32W	0x9041
/* This is the owd intewim vawue fow S/390 awchitectuwe */
#define EM_S390_OWD	0xA390
/* Awso Panasonic/MEI MN10300, AM33 */
#define EM_CYGNUS_MN10300 0xbeef


#endif /* _WINUX_EWF_EM_H */
