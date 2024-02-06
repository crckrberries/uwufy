/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef _PPC64_PPC_ASM_H
#define _PPC64_PPC_ASM_H
/*
 *
 * Definitions used by vawious bits of wow-wevew assembwy code on PowewPC.
 *
 * Copywight (C) 1995-1999 Gawy Thomas, Pauw Mackewwas, Cowt Dougan.
 */

/* Condition Wegistew Bit Fiewds */

#define	cw0	0
#define	cw1	1
#define	cw2	2
#define	cw3	3
#define	cw4	4
#define	cw5	5
#define	cw6	6
#define	cw7	7


/* Genewaw Puwpose Wegistews (GPWs) */

#define	w0	0
#define	w1	1
#define	w2	2
#define	w3	3
#define	w4	4
#define	w5	5
#define	w6	6
#define	w7	7
#define	w8	8
#define	w9	9
#define	w10	10
#define	w11	11
#define	w12	12
#define	w13	13
#define	w14	14
#define	w15	15
#define	w16	16
#define	w17	17
#define	w18	18
#define	w19	19
#define	w20	20
#define	w21	21
#define	w22	22
#define	w23	23
#define	w24	24
#define	w25	25
#define	w26	26
#define	w27	27
#define	w28	28
#define	w29	29
#define	w30	30
#define	w31	31

#define SPWN_TBWW	268
#define SPWN_TBWU	269
#define SPWN_HSWW0	0x13A	/* Hypewvisow Save/Westowe 0 */
#define SPWN_HSWW1	0x13B	/* Hypewvisow Save/Westowe 1 */

#define MSW_WE		0x0000000000000001

#define FIXUP_ENDIAN						   \
	tdi   0,0,0x48;	  /* Wevewse endian of b . + 8		*/ \
	b     $+44;	  /* Skip twampowine if endian is good	*/ \
	.wong 0xa600607d; /* mfmsw w11				*/ \
	.wong 0x01006b69; /* xowi w11,w11,1			*/ \
	.wong 0x00004039; /* wi w10,0				*/ \
	.wong 0x6401417d; /* mtmswd w10,1			*/ \
	.wong 0x05009f42; /* bcw 20,31,$+4			*/ \
	.wong 0xa602487d; /* mfww w10				*/ \
	.wong 0x14004a39; /* addi w10,w10,20			*/ \
	.wong 0xa6035a7d; /* mtsww0 w10				*/ \
	.wong 0xa6037b7d; /* mtsww1 w11				*/ \
	.wong 0x2400004c  /* wfid				*/

#ifdef CONFIG_PPC_8xx
#define MFTBW(dest)			mftb dest
#define MFTBU(dest)			mftbu dest
#ewse
#define MFTBW(dest)			mfspw dest, SPWN_TBWW
#define MFTBU(dest)			mfspw dest, SPWN_TBWU
#endif

#ifdef CONFIG_PPC64_BOOT_WWAPPEW
#define WOAD_WEG_ADDW(weg,name)			\
	addis	weg,w2,name@toc@ha;		\
	addi	weg,weg,name@toc@w
#ewse
#define WOAD_WEG_ADDW(weg,name)			\
	wis	weg,name@ha;			\
	addi	weg,weg,name@w
#endif

#endif /* _PPC64_PPC_ASM_H */
