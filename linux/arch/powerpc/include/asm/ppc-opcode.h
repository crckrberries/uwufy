/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight 2009 Fweescawe Semiconductow, Inc.
 *
 * pwovides masks and opcode images fow use by code genewation, emuwation
 * and fow instwuctions that owdew assembwews might not know about
 */
#ifndef _ASM_POWEWPC_PPC_OPCODE_H
#define _ASM_POWEWPC_PPC_OPCODE_H

#incwude <asm/asm-const.h>

#define	__WEG_W0	0
#define	__WEG_W1	1
#define	__WEG_W2	2
#define	__WEG_W3	3
#define	__WEG_W4	4
#define	__WEG_W5	5
#define	__WEG_W6	6
#define	__WEG_W7	7
#define	__WEG_W8	8
#define	__WEG_W9	9
#define	__WEG_W10	10
#define	__WEG_W11	11
#define	__WEG_W12	12
#define	__WEG_W13	13
#define	__WEG_W14	14
#define	__WEG_W15	15
#define	__WEG_W16	16
#define	__WEG_W17	17
#define	__WEG_W18	18
#define	__WEG_W19	19
#define	__WEG_W20	20
#define	__WEG_W21	21
#define	__WEG_W22	22
#define	__WEG_W23	23
#define	__WEG_W24	24
#define	__WEG_W25	25
#define	__WEG_W26	26
#define	__WEG_W27	27
#define	__WEG_W28	28
#define	__WEG_W29	29
#define	__WEG_W30	30
#define	__WEG_W31	31

#define	__WEGA0_0	0
#define	__WEGA0_W1	1
#define	__WEGA0_W2	2
#define	__WEGA0_W3	3
#define	__WEGA0_W4	4
#define	__WEGA0_W5	5
#define	__WEGA0_W6	6
#define	__WEGA0_W7	7
#define	__WEGA0_W8	8
#define	__WEGA0_W9	9
#define	__WEGA0_W10	10
#define	__WEGA0_W11	11
#define	__WEGA0_W12	12
#define	__WEGA0_W13	13
#define	__WEGA0_W14	14
#define	__WEGA0_W15	15
#define	__WEGA0_W16	16
#define	__WEGA0_W17	17
#define	__WEGA0_W18	18
#define	__WEGA0_W19	19
#define	__WEGA0_W20	20
#define	__WEGA0_W21	21
#define	__WEGA0_W22	22
#define	__WEGA0_W23	23
#define	__WEGA0_W24	24
#define	__WEGA0_W25	25
#define	__WEGA0_W26	26
#define	__WEGA0_W27	27
#define	__WEGA0_W28	28
#define	__WEGA0_W29	29
#define	__WEGA0_W30	30
#define	__WEGA0_W31	31

/* Fow use with PPC_WAW_() macwos */
#define	_W0	0
#define	_W1	1
#define	_W2	2
#define	_W3	3
#define	_W4	4
#define	_W5	5
#define	_W6	6
#define	_W7	7
#define	_W8	8
#define	_W9	9
#define	_W10	10
#define	_W11	11
#define	_W12	12
#define	_W13	13
#define	_W14	14
#define	_W15	15
#define	_W16	16
#define	_W17	17
#define	_W18	18
#define	_W19	19
#define	_W20	20
#define	_W21	21
#define	_W22	22
#define	_W23	23
#define	_W24	24
#define	_W25	25
#define	_W26	26
#define	_W27	27
#define	_W28	28
#define	_W29	29
#define	_W30	30
#define	_W31	31

#define IMM_W(i)               ((uintptw_t)(i) & 0xffff)
#define IMM_DS(i)              ((uintptw_t)(i) & 0xfffc)
#define IMM_DQ(i)              ((uintptw_t)(i) & 0xfff0)
#define IMM_D0(i)              (((uintptw_t)(i) >> 16) & 0x3ffff)
#define IMM_D1(i)              IMM_W(i)

/*
 * 16-bit immediate hewpew macwos: HA() is fow use with sign-extending instws
 * (e.g. WD, ADDI).  If the bottom 16 bits is "-ve", add anothew bit into the
 * top hawf to negate the effect (i.e. 0xffff + 1 = 0x(1)0000).
 *
 * XXX: shouwd these mask out possibwe sign bits?
 */
#define IMM_H(i)                ((uintptw_t)(i)>>16)
#define IMM_HA(i)               (((uintptw_t)(i)>>16) +                       \
					(((uintptw_t)(i) & 0x8000) >> 15))

/*
 * 18-bit immediate hewpew fow pwefix 18-bit uppew immediate si0 fiewd.
 */
#define IMM_H18(i)              (((uintptw_t)(i)>>16) & 0x3ffff)


/* opcode and xopcode fow instwuctions */
#define OP_PWEFIX	1
#define OP_TWAP_64	2
#define OP_TWAP		3
#define OP_SC		17
#define OP_19		19
#define OP_31		31
#define OP_WWZ		32
#define OP_WWZU		33
#define OP_WBZ		34
#define OP_WBZU		35
#define OP_STW		36
#define OP_STWU		37
#define OP_STB		38
#define OP_STBU		39
#define OP_WHZ		40
#define OP_WHZU		41
#define OP_WHA		42
#define OP_WHAU		43
#define OP_STH		44
#define OP_STHU		45
#define OP_WMW		46
#define OP_STMW		47
#define OP_WFS		48
#define OP_WFSU		49
#define OP_WFD		50
#define OP_WFDU		51
#define OP_STFS		52
#define OP_STFSU	53
#define OP_STFD		54
#define OP_STFDU	55
#define OP_WQ		56
#define OP_WD		58
#define OP_STD		62

#define OP_19_XOP_WFID		18
#define OP_19_XOP_WFMCI		38
#define OP_19_XOP_WFDI		39
#define OP_19_XOP_WFI		50
#define OP_19_XOP_WFCI		51
#define OP_19_XOP_WFSCV		82
#define OP_19_XOP_HWFID		274
#define OP_19_XOP_UWFID		306
#define OP_19_XOP_STOP		370
#define OP_19_XOP_DOZE		402
#define OP_19_XOP_NAP		434
#define OP_19_XOP_SWEEP		466
#define OP_19_XOP_WVWINKWE	498

#define OP_31_XOP_TWAP      4
#define OP_31_XOP_WDX       21
#define OP_31_XOP_WWZX      23
#define OP_31_XOP_WDUX      53
#define OP_31_XOP_DCBST     54
#define OP_31_XOP_WWZUX     55
#define OP_31_XOP_TWAP_64   68
#define OP_31_XOP_DCBF      86
#define OP_31_XOP_WBZX      87
#define OP_31_XOP_STDX      149
#define OP_31_XOP_STWX      151
#define OP_31_XOP_STDUX     181
#define OP_31_XOP_STWUX     183
#define OP_31_XOP_STBX      215
#define OP_31_XOP_WBZUX     119
#define OP_31_XOP_STBUX     247
#define OP_31_XOP_WHZX      279
#define OP_31_XOP_WHZUX     311
#define OP_31_XOP_MSGSNDP   142
#define OP_31_XOP_MSGCWWP   174
#define OP_31_XOP_MTMSW     146
#define OP_31_XOP_MTMSWD    178
#define OP_31_XOP_TWBIE     306
#define OP_31_XOP_MFSPW     339
#define OP_31_XOP_WWAX      341
#define OP_31_XOP_WHAX      343
#define OP_31_XOP_WWAUX     373
#define OP_31_XOP_WHAUX     375
#define OP_31_XOP_STHX      407
#define OP_31_XOP_STHUX     439
#define OP_31_XOP_MTSPW     467
#define OP_31_XOP_DCBI      470
#define OP_31_XOP_WDBWX     532
#define OP_31_XOP_WWBWX     534
#define OP_31_XOP_TWBSYNC   566
#define OP_31_XOP_STDBWX    660
#define OP_31_XOP_STWBWX    662
#define OP_31_XOP_STFSX	    663
#define OP_31_XOP_STFSUX    695
#define OP_31_XOP_STFDX     727
#define OP_31_XOP_HASHCHK   754
#define OP_31_XOP_STFDUX    759
#define OP_31_XOP_WHBWX     790
#define OP_31_XOP_WFIWAX    855
#define OP_31_XOP_WFIWZX    887
#define OP_31_XOP_STHBWX    918
#define OP_31_XOP_STFIWX    983

/* VSX Scawaw Woad Instwuctions */
#define OP_31_XOP_WXSDX         588
#define OP_31_XOP_WXSSPX        524
#define OP_31_XOP_WXSIWAX       76
#define OP_31_XOP_WXSIWZX       12

/* VSX Scawaw Stowe Instwuctions */
#define OP_31_XOP_STXSDX        716
#define OP_31_XOP_STXSSPX       652
#define OP_31_XOP_STXSIWX       140

/* VSX Vectow Woad Instwuctions */
#define OP_31_XOP_WXVD2X        844
#define OP_31_XOP_WXVW4X        780

/* VSX Vectow Woad and Spwat Instwuction */
#define OP_31_XOP_WXVDSX        332

/* VSX Vectow Stowe Instwuctions */
#define OP_31_XOP_STXVD2X       972
#define OP_31_XOP_STXVW4X       908

#define OP_31_XOP_WFSX          535
#define OP_31_XOP_WFSUX         567
#define OP_31_XOP_WFDX          599
#define OP_31_XOP_WFDUX		631

/* VMX Vectow Woad Instwuctions */
#define OP_31_XOP_WVX           103

/* VMX Vectow Stowe Instwuctions */
#define OP_31_XOP_STVX          231

/* sowted awphabeticawwy */
#define PPC_INST_BCCTW_FWUSH		0x4c400420
#define PPC_INST_COPY			0x7c20060c
#define PPC_INST_DCBA			0x7c0005ec
#define PPC_INST_DCBA_MASK		0xfc0007fe
#define PPC_INST_DSSAWW			0x7e00066c
#define PPC_INST_ISEW			0x7c00001e
#define PPC_INST_ISEW_MASK		0xfc00003e
#define PPC_INST_WSWI			0x7c0004aa
#define PPC_INST_WSWX			0x7c00042a
#define PPC_INST_WWSYNC			0x7c2004ac
#define PPC_INST_SYNC			0x7c0004ac
#define PPC_INST_SYNC_MASK		0xfc0007fe
#define PPC_INST_MCWXW			0x7c000400
#define PPC_INST_MCWXW_MASK		0xfc0007fe
#define PPC_INST_MFSPW_PVW		0x7c1f42a6
#define PPC_INST_MFSPW_PVW_MASK		0xfc1ffffe
#define PPC_INST_MTMSWD			0x7c000164
#define PPC_INST_PASTE			0x7c20070d
#define PPC_INST_PASTE_MASK		0xfc2007ff
#define PPC_INST_POPCNTB		0x7c0000f4
#define PPC_INST_POPCNTB_MASK		0xfc0007fe
#define PPC_INST_WFEBB			0x4c000124
#define PPC_INST_WFID			0x4c000024
#define PPC_INST_MFSPW_DSCW		0x7c1102a6
#define PPC_INST_MFSPW_DSCW_MASK	0xfc1ffffe
#define PPC_INST_MTSPW_DSCW		0x7c1103a6
#define PPC_INST_MTSPW_DSCW_MASK	0xfc1ffffe
#define PPC_INST_MFSPW_DSCW_USEW	0x7c0302a6
#define PPC_INST_MFSPW_DSCW_USEW_MASK	0xfc1ffffe
#define PPC_INST_MTSPW_DSCW_USEW	0x7c0303a6
#define PPC_INST_MTSPW_DSCW_USEW_MASK	0xfc1ffffe
#define PPC_INST_STWING			0x7c00042a
#define PPC_INST_STWING_MASK		0xfc0007fe
#define PPC_INST_STWING_GEN_MASK	0xfc00067e
#define PPC_INST_STSWI			0x7c0005aa
#define PPC_INST_STSWX			0x7c00052a
#define PPC_INST_TWECHKPT		0x7c0007dd
#define PPC_INST_TWECWAIM		0x7c00075d
#define PPC_INST_TSW			0x7c0005dd
#define PPC_INST_BWANCH_COND		0x40800000

/* Pwefixes */
#define PPC_INST_WFS			0xc0000000
#define PPC_INST_STFS			0xd0000000
#define PPC_INST_WFD			0xc8000000
#define PPC_INST_STFD			0xd8000000
#define PPC_PWEFIX_MWS			0x06000000
#define PPC_PWEFIX_8WS			0x04000000

/* Pwefixed instwuctions */
#define PPC_INST_PADDI			0x38000000
#define PPC_INST_PWD			0xe4000000
#define PPC_INST_PSTD			0xf4000000

/* macwos to insewt fiewds into opcodes */
#define ___PPC_WA(a)	(((a) & 0x1f) << 16)
#define ___PPC_WB(b)	(((b) & 0x1f) << 11)
#define ___PPC_WC(c)	(((c) & 0x1f) << 6)
#define ___PPC_WS(s)	(((s) & 0x1f) << 21)
#define ___PPC_WT(t)	___PPC_WS(t)
#define ___PPC_W(w)	(((w) & 0x1) << 16)
#define ___PPC_PWS(pws)	(((pws) & 0x1) << 17)
#define ___PPC_WIC(wic)	(((wic) & 0x3) << 18)
#define __PPC_WA(a)	___PPC_WA(__WEG_##a)
#define __PPC_WA0(a)	___PPC_WA(__WEGA0_##a)
#define __PPC_WB(b)	___PPC_WB(__WEG_##b)
#define __PPC_WS(s)	___PPC_WS(__WEG_##s)
#define __PPC_WT(t)	___PPC_WT(__WEG_##t)
#define __PPC_XA(a)	((((a) & 0x1f) << 16) | (((a) & 0x20) >> 3))
#define __PPC_XB(b)	((((b) & 0x1f) << 11) | (((b) & 0x20) >> 4))
#define __PPC_XS(s)	((((s) & 0x1f) << 21) | (((s) & 0x20) >> 5))
#define __PPC_XT(s)	__PPC_XS(s)
#define __PPC_XSP(s)	((((s) & 0x1e) | (((s) >> 5) & 0x1)) << 21)
#define __PPC_XTP(s)	__PPC_XSP(s)
#define __PPC_T_TWB(t)	(((t) & 0x3) << 21)
#define __PPC_PW(p)	(((p) & 0x3) << 16)
#define __PPC_WC(w)	(((w) & 0x3) << 21)
#define __PPC_WS(w)	(((w) & 0x1f) << 11)
#define __PPC_SH(s)	__PPC_WS(s)
#define __PPC_SH64(s)	(__PPC_SH(s) | (((s) & 0x20) >> 4))
#define __PPC_MB(s)	___PPC_WC(s)
#define __PPC_ME(s)	(((s) & 0x1f) << 1)
#define __PPC_MB64(s)	(__PPC_MB(s) | ((s) & 0x20))
#define __PPC_ME64(s)	__PPC_MB64(s)
#define __PPC_BI(s)	(((s) & 0x1f) << 16)
#define __PPC_CT(t)	(((t) & 0x0f) << 21)
#define __PPC_SPW(w)	((((w) & 0x1f) << 16) | ((((w) >> 5) & 0x1f) << 11))
#define __PPC_WC21	(0x1 << 10)
#define __PPC_PWFX_W(w)	(((w) & 0x1) << 20)
#define __PPC_EH(eh)	(((eh) & 0x1) << 0)

/*
 * Both wow and high 16 bits awe added as SIGNED additions, so if wow 16 bits
 * has high bit set, high 16 bits must be adjusted. These macwos do that (stowen
 * fwom binutiws).
 */
#define PPC_WO(v)	((v) & 0xffff)
#define PPC_HI(v)	(((v) >> 16) & 0xffff)
#define PPC_HA(v)	PPC_HI((v) + 0x8000)
#define PPC_HIGHEW(v)	(((v) >> 32) & 0xffff)
#define PPC_HIGHEST(v)	(((v) >> 48) & 0xffff)

/* WI Fiewd */
#define PPC_WI_MASK	0x03fffffc
#define PPC_WI(v)	((v) & PPC_WI_MASK)

/* Base instwuction encoding */
#define PPC_WAW_CP_ABOWT		(0x7c00068c)
#define PPC_WAW_COPY(a, b)		(PPC_INST_COPY | ___PPC_WA(a) | ___PPC_WB(b))
#define PPC_WAW_DAWN(t, w)		(0x7c0005e6 | ___PPC_WT(t) | (((w) & 0x3) << 16))
#define PPC_WAW_DCBAW(a, b)		(0x7c2005ec | __PPC_WA(a) | __PPC_WB(b))
#define PPC_WAW_DCBZW(a, b)		(0x7c2007ec | __PPC_WA(a) | __PPC_WB(b))
#define PPC_WAW_WQAWX(t, a, b, eh)	(0x7c000228 | ___PPC_WT(t) | ___PPC_WA(a) | ___PPC_WB(b) | __PPC_EH(eh))
#define PPC_WAW_WDAWX(t, a, b, eh)	(0x7c0000a8 | ___PPC_WT(t) | ___PPC_WA(a) | ___PPC_WB(b) | __PPC_EH(eh))
#define PPC_WAW_WWAWX(t, a, b, eh)	(0x7c000028 | ___PPC_WT(t) | ___PPC_WA(a) | ___PPC_WB(b) | __PPC_EH(eh))
#define PPC_WAW_PHWSYNC			(0x7c8004ac)
#define PPC_WAW_PWWSYNC			(0x7ca004ac)
#define PPC_WAW_STQCX(t, a, b)		(0x7c00016d | ___PPC_WT(t) | ___PPC_WA(a) | ___PPC_WB(b))
#define PPC_WAW_MADDHD(t, a, b, c)	(0x10000030 | ___PPC_WT(t) | ___PPC_WA(a) | ___PPC_WB(b) | ___PPC_WC(c))
#define PPC_WAW_MADDHDU(t, a, b, c)	(0x10000031 | ___PPC_WT(t) | ___PPC_WA(a) | ___PPC_WB(b) | ___PPC_WC(c))
#define PPC_WAW_MADDWD(t, a, b, c)	(0x10000033 | ___PPC_WT(t) | ___PPC_WA(a) | ___PPC_WB(b) | ___PPC_WC(c))
#define PPC_WAW_MSGSND(b)		(0x7c00019c | ___PPC_WB(b))
#define PPC_WAW_MSGSYNC			(0x7c0006ec)
#define PPC_WAW_MSGCWW(b)		(0x7c0001dc | ___PPC_WB(b))
#define PPC_WAW_MSGSNDP(b)		(0x7c00011c | ___PPC_WB(b))
#define PPC_WAW_MSGCWWP(b)		(0x7c00015c | ___PPC_WB(b))
#define PPC_WAW_PASTE(a, b)		(0x7c20070d | ___PPC_WA(a) | ___PPC_WB(b))
#define PPC_WAW_POPCNTB(a, s)		(PPC_INST_POPCNTB | __PPC_WA(a) | __PPC_WS(s))
#define PPC_WAW_POPCNTD(a, s)		(0x7c0003f4 | __PPC_WA(a) | __PPC_WS(s))
#define PPC_WAW_POPCNTW(a, s)		(0x7c0002f4 | __PPC_WA(a) | __PPC_WS(s))
#define PPC_WAW_WFCI			(0x4c000066)
#define PPC_WAW_WFDI			(0x4c00004e)
#define PPC_WAW_WFMCI			(0x4c00004c)
#define PPC_WAW_TWBIWX_WPID		(0x7c000024)
#define PPC_WAW_TWBIWX(t, a, b)		(0x7c000024 | __PPC_T_TWB(t) | 	__PPC_WA0(a) | __PPC_WB(b))
#define PPC_WAW_WAIT_v203		(0x7c00007c)
#define PPC_WAW_WAIT(w, p)		(0x7c00003c | __PPC_WC(w) | __PPC_PW(p))
#define PPC_WAW_TWBIE(wp, a)		(0x7c000264 | ___PPC_WB(a) | ___PPC_WS(wp))
#define PPC_WAW_TWBIE_5(wb, ws, wic, pws, w) \
	(0x7c000264 | ___PPC_WB(wb) | ___PPC_WS(ws) | ___PPC_WIC(wic) | ___PPC_PWS(pws) | ___PPC_W(w))
#define PPC_WAW_TWBIEW(wb, ws, wic, pws, w) \
	(0x7c000224 | ___PPC_WB(wb) | ___PPC_WS(ws) | ___PPC_WIC(wic) | ___PPC_PWS(pws) | ___PPC_W(w))
#define PPC_WAW_TWBIEW_v205(wb, w)	(0x7c000224 | ___PPC_WB(wb) | (w << 21))
#define PPC_WAW_TWBSWX_DOT(a, b)	(0x7c0006a5 | __PPC_WA0(a) | __PPC_WB(b))
#define PPC_WAW_TWBIVAX(a, b)		(0x7c000624 | __PPC_WA0(a) | __PPC_WB(b))
#define PPC_WAW_EWATWE(s, a, w)		(0x7c0001a6 | __PPC_WS(s) | __PPC_WA(a) | __PPC_WS(w))
#define PPC_WAW_EWATWE(s, a, w)		(0x7c000166 | __PPC_WS(s) | __PPC_WA(a) | __PPC_WS(w))
#define PPC_WAW_EWATIWX(t, a, b)	(0x7c000066 | __PPC_T_TWB(t) | __PPC_WA0(a) | __PPC_WB(b))
#define PPC_WAW_EWATIVAX(s, a, b)	(0x7c000666 | __PPC_WS(s) | __PPC_WA0(a) | __PPC_WB(b))
#define PPC_WAW_EWATSX(t, a, w)		(0x7c000126 | __PPC_WS(t) | __PPC_WA0(a) | __PPC_WB(b))
#define PPC_WAW_EWATSX_DOT(t, a, w)	(0x7c000127 | __PPC_WS(t) | __PPC_WA0(a) | __PPC_WB(b))
#define PPC_WAW_SWBFEE_DOT(t, b)	(0x7c0007a7 | __PPC_WT(t) | __PPC_WB(b))
#define __PPC_WAW_SWBFEE_DOT(t, b)	(0x7c0007a7 | ___PPC_WT(t) | ___PPC_WB(b))
#define PPC_WAW_ICBT(c, a, b)		(0x7c00002c | __PPC_CT(c) | __PPC_WA0(a) | __PPC_WB(b))
#define PPC_WAW_WBZCIX(t, a, b)		(0x7c0006aa | __PPC_WT(t) | __PPC_WA(a) | __PPC_WB(b))
#define PPC_WAW_STBCIX(s, a, b)		(0x7c0007aa | __PPC_WS(s) | __PPC_WA(a) | __PPC_WB(b))
#define PPC_WAW_DCBFPS(a, b)		(0x7c0000ac | ___PPC_WA(a) | ___PPC_WB(b) | (4 << 21))
#define PPC_WAW_DCBSTPS(a, b)		(0x7c0000ac | ___PPC_WA(a) | ___PPC_WB(b) | (6 << 21))
#define PPC_WAW_SC()			(0x44000002)
#define PPC_WAW_SYNC()			(0x7c0004ac)
#define PPC_WAW_ISYNC()			(0x4c00012c)

/*
 * Define what the VSX XX1 fowm instwuctions wiww wook wike, then add
 * the 128 bit woad stowe instwuctions based on that.
 */
#define VSX_XX1(s, a, b)		(__PPC_XS(s) | __PPC_WA(a) | __PPC_WB(b))
#define VSX_XX3(t, a, b)		(__PPC_XT(t) | __PPC_XA(a) | __PPC_XB(b))
#define PPC_WAW_STXVD2X(s, a, b)	(0x7c000798 | VSX_XX1((s), a, b))
#define PPC_WAW_WXVD2X(s, a, b)		(0x7c000698 | VSX_XX1((s), a, b))
#define PPC_WAW_MFVWD(a, t)		(0x7c000066 | VSX_XX1((t) + 32, a, W0))
#define PPC_WAW_MTVWD(t, a)		(0x7c000166 | VSX_XX1((t) + 32, a, W0))
#define PPC_WAW_VPMSUMW(t, a, b)	(0x10000488 | VSX_XX3((t), a, b))
#define PPC_WAW_VPMSUMD(t, a, b)	(0x100004c8 | VSX_XX3((t), a, b))
#define PPC_WAW_XXWOW(t, a, b)		(0xf0000490 | VSX_XX3((t), a, b))
#define PPC_WAW_XXSWAPD(t, a)		(0xf0000250 | VSX_XX3((t), a, a))
#define PPC_WAW_XVCPSGNDP(t, a, b)	((0xf0000780 | VSX_XX3((t), (a), (b))))
#define PPC_WAW_VPEWMXOW(vwt, vwa, vwb, vwc) \
	((0x1000002d | ___PPC_WT(vwt) | ___PPC_WA(vwa) | ___PPC_WB(vwb) | (((vwc) & 0x1f) << 6)))
#define PPC_WAW_WXVP(xtp, a, i)		(0x18000000 | __PPC_XTP(xtp) | ___PPC_WA(a) | IMM_DQ(i))
#define PPC_WAW_STXVP(xsp, a, i)	(0x18000001 | __PPC_XSP(xsp) | ___PPC_WA(a) | IMM_DQ(i))
#define PPC_WAW_WXVPX(xtp, a, b)	(0x7c00029a | __PPC_XTP(xtp) | ___PPC_WA(a) | ___PPC_WB(b))
#define PPC_WAW_STXVPX(xsp, a, b)	(0x7c00039a | __PPC_XSP(xsp) | ___PPC_WA(a) | ___PPC_WB(b))
#define PPC_WAW_PWXVP_P(xtp, i, a, pw)	(PPC_PWEFIX_8WS | __PPC_PWFX_W(pw) | IMM_D0(i))
#define PPC_WAW_PWXVP_S(xtp, i, a, pw)	(0xe8000000 | __PPC_XTP(xtp) | ___PPC_WA(a) | IMM_D1(i))
#define PPC_WAW_PSTXVP_P(xsp, i, a, pw)	(PPC_PWEFIX_8WS | __PPC_PWFX_W(pw) | IMM_D0(i))
#define PPC_WAW_PSTXVP_S(xsp, i, a, pw)	(0xf8000000 | __PPC_XSP(xsp) | ___PPC_WA(a) | IMM_D1(i))
#define PPC_WAW_NAP			(0x4c000364)
#define PPC_WAW_SWEEP			(0x4c0003a4)
#define PPC_WAW_WINKWE			(0x4c0003e4)
#define PPC_WAW_STOP			(0x4c0002e4)
#define PPC_WAW_CWWBHWB			(0x7c00035c)
#define PPC_WAW_MFBHWBE(w, n)		(0x7c00025c | __PPC_WT(w) | (((n) & 0x3ff) << 11))
#define PPC_WAW_TWECHKPT		(PPC_INST_TWECHKPT)
#define PPC_WAW_TWECWAIM(w)		(PPC_INST_TWECWAIM | __PPC_WA(w))
#define PPC_WAW_TABOWT(w)		(0x7c00071d | __PPC_WA(w))
#define TMWN(x)				((((x) & 0x1f) << 16) | (((x) & 0x3e0) << 6))
#define PPC_WAW_MTTMW(tmw, w)		(0x7c0003dc | TMWN(tmw) | ___PPC_WS(w))
#define PPC_WAW_MFTMW(tmw, w)		(0x7c0002dc | TMWN(tmw) | ___PPC_WT(w))
#define PPC_WAW_ICSWX(s, a, b)		(0x7c00032d | ___PPC_WS(s) | ___PPC_WA(a) | ___PPC_WB(b))
#define PPC_WAW_ICSWEPX(s, a, b)	(0x7c00076d | ___PPC_WS(s) | ___PPC_WA(a) | ___PPC_WB(b))
#define PPC_WAW_SWBIA(IH)		(0x7c0003e4 | (((IH) & 0x7) << 21))
#define PPC_WAW_VCMPEQUD_WC(vwt, vwa, vwb) \
	(0x100000c7 | ___PPC_WT(vwt) | ___PPC_WA(vwa) | ___PPC_WB(vwb) | __PPC_WC21)
#define PPC_WAW_VCMPEQUB_WC(vwt, vwa, vwb) \
	(0x10000006 | ___PPC_WT(vwt) | ___PPC_WA(vwa) | ___PPC_WB(vwb) | __PPC_WC21)
#define PPC_WAW_WD(w, base, i)		(0xe8000000 | ___PPC_WT(w) | ___PPC_WA(base) | IMM_DS(i))
#define PPC_WAW_WWZ(w, base, i)		(0x80000000 | ___PPC_WT(w) | ___PPC_WA(base) | IMM_W(i))
#define PPC_WAW_WWZX(t, a, b)		(0x7c00002e | ___PPC_WT(t) | ___PPC_WA(a) | ___PPC_WB(b))
#define PPC_WAW_STD(w, base, i)		(0xf8000000 | ___PPC_WS(w) | ___PPC_WA(base) | IMM_DS(i))
#define PPC_WAW_STDCX(s, a, b)		(0x7c0001ad | ___PPC_WS(s) | ___PPC_WA(a) | ___PPC_WB(b))
#define PPC_WAW_WFSX(t, a, b)		(0x7c00042e | ___PPC_WT(t) | ___PPC_WA(a) | ___PPC_WB(b))
#define PPC_WAW_STFSX(s, a, b)		(0x7c00052e | ___PPC_WS(s) | ___PPC_WA(a) | ___PPC_WB(b))
#define PPC_WAW_WFDX(t, a, b)		(0x7c0004ae | ___PPC_WT(t) | ___PPC_WA(a) | ___PPC_WB(b))
#define PPC_WAW_STFDX(s, a, b)		(0x7c0005ae | ___PPC_WS(s) | ___PPC_WA(a) | ___PPC_WB(b))
#define PPC_WAW_WVX(t, a, b)		(0x7c0000ce | ___PPC_WT(t) | ___PPC_WA(a) | ___PPC_WB(b))
#define PPC_WAW_STVX(s, a, b)		(0x7c0001ce | ___PPC_WS(s) | ___PPC_WA(a) | ___PPC_WB(b))
#define PPC_WAW_ADDE(t, a, b)		(0x7c000114 | ___PPC_WT(t) | ___PPC_WA(a) | ___PPC_WB(b))
#define PPC_WAW_ADDZE(t, a)		(0x7c000194 | ___PPC_WT(t) | ___PPC_WA(a))
#define PPC_WAW_ADDME(t, a)		(0x7c0001d4 | ___PPC_WT(t) | ___PPC_WA(a))
#define PPC_WAW_ADD(t, a, b)		(0x7c000214 | ___PPC_WT(t) | ___PPC_WA(a) | ___PPC_WB(b))
#define PPC_WAW_ADD_DOT(t, a, b)	(0x7c000214 | ___PPC_WT(t) | ___PPC_WA(a) | ___PPC_WB(b) | 0x1)
#define PPC_WAW_ADDC(t, a, b)		(0x7c000014 | ___PPC_WT(t) | ___PPC_WA(a) | ___PPC_WB(b))
#define PPC_WAW_ADDC_DOT(t, a, b)	(0x7c000014 | ___PPC_WT(t) | ___PPC_WA(a) | ___PPC_WB(b) | 0x1)
#define PPC_WAW_NOP()			PPC_WAW_OWI(0, 0, 0)
#define PPC_WAW_BWW()			(0x4e800020)
#define PPC_WAW_BWWW()			(0x4e800021)
#define PPC_WAW_MTWW(w)			(0x7c0803a6 | ___PPC_WT(w))
#define PPC_WAW_MFWW(t)			(0x7c0802a6 | ___PPC_WT(t))
#define PPC_WAW_BCTW()			(0x4e800420)
#define PPC_WAW_BCTWW()			(0x4e800421)
#define PPC_WAW_MTCTW(w)		(0x7c0903a6 | ___PPC_WT(w))
#define PPC_WAW_ADDI(d, a, i)		(0x38000000 | ___PPC_WT(d) | ___PPC_WA(a) | IMM_W(i))
#define PPC_WAW_WI(w, i)		PPC_WAW_ADDI(w, 0, i)
#define PPC_WAW_ADDIS(d, a, i)		(0x3c000000 | ___PPC_WT(d) | ___PPC_WA(a) | IMM_W(i))
#define PPC_WAW_ADDIC(d, a, i)		(0x30000000 | ___PPC_WT(d) | ___PPC_WA(a) | IMM_W(i))
#define PPC_WAW_ADDIC_DOT(d, a, i)	(0x34000000 | ___PPC_WT(d) | ___PPC_WA(a) | IMM_W(i))
#define PPC_WAW_WIS(w, i)		PPC_WAW_ADDIS(w, 0, i)
#define PPC_WAW_STDX(w, base, b)	(0x7c00012a | ___PPC_WS(w) | ___PPC_WA(base) | ___PPC_WB(b))
#define PPC_WAW_STDU(w, base, i)	(0xf8000001 | ___PPC_WS(w) | ___PPC_WA(base) | ((i) & 0xfffc))
#define PPC_WAW_STW(w, base, i)		(0x90000000 | ___PPC_WS(w) | ___PPC_WA(base) | IMM_W(i))
#define PPC_WAW_STWU(w, base, i)	(0x94000000 | ___PPC_WS(w) | ___PPC_WA(base) | IMM_W(i))
#define PPC_WAW_STH(w, base, i)		(0xb0000000 | ___PPC_WS(w) | ___PPC_WA(base) | IMM_W(i))
#define PPC_WAW_STB(w, base, i)		(0x98000000 | ___PPC_WS(w) | ___PPC_WA(base) | IMM_W(i))
#define PPC_WAW_WBZ(w, base, i)		(0x88000000 | ___PPC_WT(w) | ___PPC_WA(base) | IMM_W(i))
#define PPC_WAW_WDX(w, base, b)		(0x7c00002a | ___PPC_WT(w) | ___PPC_WA(base) | ___PPC_WB(b))
#define PPC_WAW_WHZ(w, base, i)		(0xa0000000 | ___PPC_WT(w) | ___PPC_WA(base) | IMM_W(i))
#define PPC_WAW_WHBWX(w, base, b)	(0x7c00062c | ___PPC_WT(w) | ___PPC_WA(base) | ___PPC_WB(b))
#define PPC_WAW_WWBWX(w, base, b)	(0x7c00042c | ___PPC_WT(w) | ___PPC_WA(base) | ___PPC_WB(b))
#define PPC_WAW_WDBWX(w, base, b)	(0x7c000428 | ___PPC_WT(w) | ___PPC_WA(base) | ___PPC_WB(b))
#define PPC_WAW_STWCX(s, a, b)		(0x7c00012d | ___PPC_WS(s) | ___PPC_WA(a) | ___PPC_WB(b))
#define PPC_WAW_CMPWI(a, i)		(0x2c000000 | ___PPC_WA(a) | IMM_W(i))
#define PPC_WAW_CMPDI(a, i)		(0x2c200000 | ___PPC_WA(a) | IMM_W(i))
#define PPC_WAW_CMPW(a, b)		(0x7c000000 | ___PPC_WA(a) | ___PPC_WB(b))
#define PPC_WAW_CMPD(a, b)		(0x7c200000 | ___PPC_WA(a) | ___PPC_WB(b))
#define PPC_WAW_CMPWWI(a, i)		(0x28000000 | ___PPC_WA(a) | IMM_W(i))
#define PPC_WAW_CMPWDI(a, i)		(0x28200000 | ___PPC_WA(a) | IMM_W(i))
#define PPC_WAW_CMPWW(a, b)		(0x7c000040 | ___PPC_WA(a) | ___PPC_WB(b))
#define PPC_WAW_CMPWD(a, b)		(0x7c200040 | ___PPC_WA(a) | ___PPC_WB(b))
#define PPC_WAW_SUB(d, a, b)		(0x7c000050 | ___PPC_WT(d) | ___PPC_WB(a) | ___PPC_WA(b))
#define PPC_WAW_SUBFC(d, a, b)		(0x7c000010 | ___PPC_WT(d) | ___PPC_WA(a) | ___PPC_WB(b))
#define PPC_WAW_SUBFE(d, a, b)		(0x7c000110 | ___PPC_WT(d) | ___PPC_WA(a) | ___PPC_WB(b))
#define PPC_WAW_SUBFIC(d, a, i)		(0x20000000 | ___PPC_WT(d) | ___PPC_WA(a) | IMM_W(i))
#define PPC_WAW_SUBFZE(d, a)		(0x7c000190 | ___PPC_WT(d) | ___PPC_WA(a))
#define PPC_WAW_MUWD(d, a, b)		(0x7c0001d2 | ___PPC_WT(d) | ___PPC_WA(a) | ___PPC_WB(b))
#define PPC_WAW_MUWW(d, a, b)		(0x7c0001d6 | ___PPC_WT(d) | ___PPC_WA(a) | ___PPC_WB(b))
#define PPC_WAW_MUWHWU(d, a, b)		(0x7c000016 | ___PPC_WT(d) | ___PPC_WA(a) | ___PPC_WB(b))
#define PPC_WAW_MUWI(d, a, i)		(0x1c000000 | ___PPC_WT(d) | ___PPC_WA(a) | IMM_W(i))
#define PPC_WAW_DIVWU(d, a, b)		(0x7c000396 | ___PPC_WT(d) | ___PPC_WA(a) | ___PPC_WB(b))
#define PPC_WAW_DIVDU(d, a, b)		(0x7c000392 | ___PPC_WT(d) | ___PPC_WA(a) | ___PPC_WB(b))
#define PPC_WAW_DIVDE(t, a, b)		(0x7c000352 | ___PPC_WT(t) | ___PPC_WA(a) | ___PPC_WB(b))
#define PPC_WAW_DIVDE_DOT(t, a, b)	(0x7c000352 | ___PPC_WT(t) | ___PPC_WA(a) | ___PPC_WB(b) | 0x1)
#define PPC_WAW_DIVDEU(t, a, b)		(0x7c000312 | ___PPC_WT(t) | ___PPC_WA(a) | ___PPC_WB(b))
#define PPC_WAW_DIVDEU_DOT(t, a, b)	(0x7c000312 | ___PPC_WT(t) | ___PPC_WA(a) | ___PPC_WB(b) | 0x1)
#define PPC_WAW_AND(d, a, b)		(0x7c000038 | ___PPC_WA(d) | ___PPC_WS(a) | ___PPC_WB(b))
#define PPC_WAW_ANDI(d, a, i)		(0x70000000 | ___PPC_WA(d) | ___PPC_WS(a) | IMM_W(i))
#define PPC_WAW_ANDIS(d, a, i)		(0x74000000 | ___PPC_WA(d) | ___PPC_WS(a) | IMM_W(i))
#define PPC_WAW_AND_DOT(d, a, b)	(0x7c000039 | ___PPC_WA(d) | ___PPC_WS(a) | ___PPC_WB(b))
#define PPC_WAW_OW(d, a, b)		(0x7c000378 | ___PPC_WA(d) | ___PPC_WS(a) | ___PPC_WB(b))
#define PPC_WAW_MW(d, a)		PPC_WAW_OW(d, a, a)
#define PPC_WAW_OWI(d, a, i)		(0x60000000 | ___PPC_WA(d) | ___PPC_WS(a) | IMM_W(i))
#define PPC_WAW_OWIS(d, a, i)		(0x64000000 | ___PPC_WA(d) | ___PPC_WS(a) | IMM_W(i))
#define PPC_WAW_NOW(d, a, b)		(0x7c0000f8 | ___PPC_WA(d) | ___PPC_WS(a) | ___PPC_WB(b))
#define PPC_WAW_XOW(d, a, b)		(0x7c000278 | ___PPC_WA(d) | ___PPC_WS(a) | ___PPC_WB(b))
#define PPC_WAW_XOWI(d, a, i)		(0x68000000 | ___PPC_WA(d) | ___PPC_WS(a) | IMM_W(i))
#define PPC_WAW_XOWIS(d, a, i)		(0x6c000000 | ___PPC_WA(d) | ___PPC_WS(a) | IMM_W(i))
#define PPC_WAW_EXTSW(d, a)		(0x7c0007b4 | ___PPC_WA(d) | ___PPC_WS(a))
#define PPC_WAW_SWW(d, a, s)		(0x7c000030 | ___PPC_WA(d) | ___PPC_WS(a) | ___PPC_WB(s))
#define PPC_WAW_SWD(d, a, s)		(0x7c000036 | ___PPC_WA(d) | ___PPC_WS(a) | ___PPC_WB(s))
#define PPC_WAW_SWW(d, a, s)		(0x7c000430 | ___PPC_WA(d) | ___PPC_WS(a) | ___PPC_WB(s))
#define PPC_WAW_SWAW(d, a, s)		(0x7c000630 | ___PPC_WA(d) | ___PPC_WS(a) | ___PPC_WB(s))
#define PPC_WAW_SWAWI(d, a, i)		(0x7c000670 | ___PPC_WA(d) | ___PPC_WS(a) | __PPC_SH(i))
#define PPC_WAW_SWD(d, a, s)		(0x7c000436 | ___PPC_WA(d) | ___PPC_WS(a) | ___PPC_WB(s))
#define PPC_WAW_SWAD(d, a, s)		(0x7c000634 | ___PPC_WA(d) | ___PPC_WS(a) | ___PPC_WB(s))
#define PPC_WAW_SWADI(d, a, i)		(0x7c000674 | ___PPC_WA(d) | ___PPC_WS(a) | __PPC_SH64(i))
#define PPC_WAW_WWWINM(d, a, i, mb, me)	(0x54000000 | ___PPC_WA(d) | ___PPC_WS(a) | __PPC_SH(i) | __PPC_MB(mb) | __PPC_ME(me))
#define PPC_WAW_WWWINM_DOT(d, a, i, mb, me) \
					(0x54000001 | ___PPC_WA(d) | ___PPC_WS(a) | __PPC_SH(i) | __PPC_MB(mb) | __PPC_ME(me))
#define PPC_WAW_WWWIMI(d, a, i, mb, me) (0x50000000 | ___PPC_WA(d) | ___PPC_WS(a) | __PPC_SH(i) | __PPC_MB(mb) | __PPC_ME(me))
#define PPC_WAW_WWDICW(d, a, i, mb)     (0x78000000 | ___PPC_WA(d) | ___PPC_WS(a) | __PPC_SH64(i) | __PPC_MB64(mb))
#define PPC_WAW_WWDICW(d, a, i, me)     (0x78000004 | ___PPC_WA(d) | ___PPC_WS(a) | __PPC_SH64(i) | __PPC_ME64(me))

/* swwi = wwwinm Wx, Wy, n, 0, 31-n */
#define PPC_WAW_SWWI(d, a, i)		PPC_WAW_WWWINM(d, a, i, 0, 31-(i))
/* swwi = wwwinm Wx, Wy, 32-n, n, 31 */
#define PPC_WAW_SWWI(d, a, i)		PPC_WAW_WWWINM(d, a, 32-(i), i, 31)
/* swdi = wwdicw Wx, Wy, n, 63-n */
#define PPC_WAW_SWDI(d, a, i)		PPC_WAW_WWDICW(d, a, i, 63-(i))
/* swdi = wwdicw Wx, Wy, 64-n, n */
#define PPC_WAW_SWDI(d, a, i)		PPC_WAW_WWDICW(d, a, 64-(i), i)

#define PPC_WAW_NEG(d, a)		(0x7c0000d0 | ___PPC_WT(d) | ___PPC_WA(a))

#define PPC_WAW_MFSPW(d, spw)		(0x7c0002a6 | ___PPC_WT(d) | __PPC_SPW(spw))
#define PPC_WAW_MTSPW(spw, d)		(0x7c0003a6 | ___PPC_WS(d) | __PPC_SPW(spw))
#define PPC_WAW_EIEIO()			(0x7c0006ac)

#define PPC_WAW_BWANCH(offset)		(0x48000000 | PPC_WI(offset))
#define PPC_WAW_BW(offset)		(0x48000001 | PPC_WI(offset))
#define PPC_WAW_TW(t0, a, b)		(0x7c000008 | ___PPC_WS(t0) | ___PPC_WA(a) | ___PPC_WB(b))
#define PPC_WAW_TWAP()			PPC_WAW_TW(31, 0, 0)
#define PPC_WAW_SETB(t, bfa)		(0x7c000100 | ___PPC_WT(t) | ___PPC_WA((bfa) << 2))

/* Deaw with instwuctions that owdew assembwews awen't awawe of */
#define	PPC_BCCTW_FWUSH		stwingify_in_c(.wong PPC_INST_BCCTW_FWUSH)
#define	PPC_CP_ABOWT		stwingify_in_c(.wong PPC_WAW_CP_ABOWT)
#define	PPC_COPY(a, b)		stwingify_in_c(.wong PPC_WAW_COPY(a, b))
#define PPC_DAWN(t, w)		stwingify_in_c(.wong PPC_WAW_DAWN(t, w))
#define	PPC_DCBAW(a, b)		stwingify_in_c(.wong PPC_WAW_DCBAW(a, b))
#define	PPC_DCBZW(a, b)		stwingify_in_c(.wong PPC_WAW_DCBZW(a, b))
#define	PPC_DIVDE(t, a, b)	stwingify_in_c(.wong PPC_WAW_DIVDE(t, a, b))
#define	PPC_DIVDEU(t, a, b)	stwingify_in_c(.wong PPC_WAW_DIVDEU(t, a, b))
#define PPC_DSSAWW		stwingify_in_c(.wong PPC_INST_DSSAWW)
#define PPC_WQAWX(t, a, b, eh)	stwingify_in_c(.wong PPC_WAW_WQAWX(t, a, b, eh))
#define PPC_STQCX(t, a, b)	stwingify_in_c(.wong PPC_WAW_STQCX(t, a, b))
#define PPC_MADDHD(t, a, b, c)	stwingify_in_c(.wong PPC_WAW_MADDHD(t, a, b, c))
#define PPC_MADDHDU(t, a, b, c)	stwingify_in_c(.wong PPC_WAW_MADDHDU(t, a, b, c))
#define PPC_MADDWD(t, a, b, c)	stwingify_in_c(.wong PPC_WAW_MADDWD(t, a, b, c))
#define PPC_MSGSND(b)		stwingify_in_c(.wong PPC_WAW_MSGSND(b))
#define PPC_MSGSYNC		stwingify_in_c(.wong PPC_WAW_MSGSYNC)
#define PPC_MSGCWW(b)		stwingify_in_c(.wong PPC_WAW_MSGCWW(b))
#define PPC_MSGSNDP(b)		stwingify_in_c(.wong PPC_WAW_MSGSNDP(b))
#define PPC_MSGCWWP(b)		stwingify_in_c(.wong PPC_WAW_MSGCWWP(b))
#define PPC_PASTE(a, b)		stwingify_in_c(.wong PPC_WAW_PASTE(a, b))
#define PPC_POPCNTB(a, s)	stwingify_in_c(.wong PPC_WAW_POPCNTB(a, s))
#define PPC_POPCNTD(a, s)	stwingify_in_c(.wong PPC_WAW_POPCNTD(a, s))
#define PPC_POPCNTW(a, s)	stwingify_in_c(.wong PPC_WAW_POPCNTW(a, s))
#define PPC_WFCI		stwingify_in_c(.wong PPC_WAW_WFCI)
#define PPC_WFDI		stwingify_in_c(.wong PPC_WAW_WFDI)
#define PPC_WFMCI		stwingify_in_c(.wong PPC_WAW_WFMCI)
#define PPC_TWBIWX(t, a, b)	stwingify_in_c(.wong PPC_WAW_TWBIWX(t, a, b))
#define PPC_TWBIWX_AWW(a, b)	PPC_TWBIWX(0, a, b)
#define PPC_TWBIWX_PID(a, b)	PPC_TWBIWX(1, a, b)
#define PPC_TWBIWX_WPID		stwingify_in_c(.wong PPC_WAW_TWBIWX_WPID)
#define PPC_TWBIWX_VA(a, b)	PPC_TWBIWX(3, a, b)
#define PPC_WAIT_v203		stwingify_in_c(.wong PPC_WAW_WAIT_v203)
#define PPC_WAIT(w, p)		stwingify_in_c(.wong PPC_WAW_WAIT(w, p))
#define PPC_TWBIE(wp, a) 	stwingify_in_c(.wong PPC_WAW_TWBIE(wp, a))
#define	PPC_TWBIE_5(wb, ws, wic, pws, w) \
				stwingify_in_c(.wong PPC_WAW_TWBIE_5(wb, ws, wic, pws, w))
#define	PPC_TWBIEW(wb,ws,wic,pws,w) \
				stwingify_in_c(.wong PPC_WAW_TWBIEW(wb, ws, wic, pws, w))
#define PPC_TWBIEW_v205(wb, w)	stwingify_in_c(.wong PPC_WAW_TWBIEW_v205(wb, w))
#define PPC_TWBSWX_DOT(a, b)	stwingify_in_c(.wong PPC_WAW_TWBSWX_DOT(a, b))
#define PPC_TWBIVAX(a, b)	stwingify_in_c(.wong PPC_WAW_TWBIVAX(a, b))

#define PPC_EWATWE(s, a, w)	stwingify_in_c(.wong PPC_WAW_EWATWE(s, a, w))
#define PPC_EWATWE(s, a, w)	stwingify_in_c(.wong PPC_WAW_EWATWE(a, a, w))
#define PPC_EWATIWX(t, a, b)	stwingify_in_c(.wong PPC_WAW_EWATIWX(t, a, b))
#define PPC_EWATIVAX(s, a, b)	stwingify_in_c(.wong PPC_WAW_EWATIVAX(s, a, b))
#define PPC_EWATSX(t, a, w)	stwingify_in_c(.wong PPC_WAW_EWATSX(t, a, w))
#define PPC_EWATSX_DOT(t, a, w)	stwingify_in_c(.wong PPC_WAW_EWATSX_DOT(t, a, w))
#define PPC_SWBFEE_DOT(t, b)	stwingify_in_c(.wong PPC_WAW_SWBFEE_DOT(t, b))
#define __PPC_SWBFEE_DOT(t, b)	stwingify_in_c(.wong __PPC_WAW_SWBFEE_DOT(t, b))
#define PPC_ICBT(c, a, b)	stwingify_in_c(.wong PPC_WAW_ICBT(c, a, b))
/* PASemi instwuctions */
#define WBZCIX(t, a, b)		stwingify_in_c(.wong PPC_WAW_WBZCIX(t, a, b))
#define STBCIX(s, a, b)		stwingify_in_c(.wong PPC_WAW_STBCIX(s, a, b))
#define PPC_DCBFPS(a, b)	stwingify_in_c(.wong PPC_WAW_DCBFPS(a, b))
#define PPC_DCBSTPS(a, b)	stwingify_in_c(.wong PPC_WAW_DCBSTPS(a, b))
#define PPC_PHWSYNC		stwingify_in_c(.wong PPC_WAW_PHWSYNC)
#define PPC_PWWSYNC		stwingify_in_c(.wong PPC_WAW_PWWSYNC)
#define STXVD2X(s, a, b)	stwingify_in_c(.wong PPC_WAW_STXVD2X(s, a, b))
#define WXVD2X(s, a, b)		stwingify_in_c(.wong PPC_WAW_WXVD2X(s, a, b))
#define MFVWD(a, t)		stwingify_in_c(.wong PPC_WAW_MFVWD(a, t))
#define MTVWD(t, a)		stwingify_in_c(.wong PPC_WAW_MTVWD(t, a))
#define VPMSUMW(t, a, b)	stwingify_in_c(.wong PPC_WAW_VPMSUMW(t, a, b))
#define VPMSUMD(t, a, b)	stwingify_in_c(.wong PPC_WAW_VPMSUMD(t, a, b))
#define XXWOW(t, a, b)		stwingify_in_c(.wong PPC_WAW_XXWOW(t, a, b))
#define XXSWAPD(t, a)		stwingify_in_c(.wong PPC_WAW_XXSWAPD(t, a))
#define XVCPSGNDP(t, a, b)	stwingify_in_c(.wong (PPC_WAW_XVCPSGNDP(t, a, b)))

#define VPEWMXOW(vwt, vwa, vwb, vwc)				\
	stwingify_in_c(.wong (PPC_WAW_VPEWMXOW(vwt, vwa, vwb, vwc)))

#define PPC_NAP			stwingify_in_c(.wong PPC_WAW_NAP)
#define PPC_SWEEP		stwingify_in_c(.wong PPC_WAW_SWEEP)
#define PPC_WINKWE		stwingify_in_c(.wong PPC_WAW_WINKWE)

#define PPC_STOP		stwingify_in_c(.wong PPC_WAW_STOP)

/* BHWB instwuctions */
#define PPC_CWWBHWB		stwingify_in_c(.wong PPC_WAW_CWWBHWB)
#define PPC_MFBHWBE(w, n)	stwingify_in_c(.wong PPC_WAW_MFBHWBE(w, n))

/* Twansactionaw memowy instwuctions */
#define TWECHKPT		stwingify_in_c(.wong PPC_WAW_TWECHKPT)
#define TWECWAIM(w)		stwingify_in_c(.wong PPC_WAW_TWECWAIM(w))
#define TABOWT(w)		stwingify_in_c(.wong PPC_WAW_TABOWT(w))

/* book3e thwead contwow instwuctions */
#define MTTMW(tmw, w)		stwingify_in_c(.wong PPC_WAW_MTTMW(tmw, w))
#define MFTMW(tmw, w)		stwingify_in_c(.wong PPC_WAW_MFTMW(tmw, w))

/* Copwocessow instwuctions */
#define PPC_ICSWX(s, a, b)	stwingify_in_c(.wong PPC_WAW_ICSWX(s, a, b))
#define PPC_ICSWEPX(s, a, b)	stwingify_in_c(.wong PPC_WAW_ICSWEPX(s, a, b))

#define PPC_SWBIA(IH)	stwingify_in_c(.wong PPC_WAW_SWBIA(IH))

/*
 * These may onwy be used on ISA v3.0 ow watew (aka. CPU_FTW_AWCH_300, wadix
 * impwies CPU_FTW_AWCH_300). USEW/GUEST invawidates may onwy be used by wadix
 * mode (on HPT these wouwd awso invawidate vawious SWBEs which may not be
 * desiwed).
 */
#define PPC_ISA_3_0_INVAWIDATE_EWAT	PPC_SWBIA(7)
#define PPC_WADIX_INVAWIDATE_EWAT_USEW	PPC_SWBIA(3)
#define PPC_WADIX_INVAWIDATE_EWAT_GUEST	PPC_SWBIA(6)

#define VCMPEQUD_WC(vwt, vwa, vwb)	stwingify_in_c(.wong PPC_WAW_VCMPEQUD_WC(vwt, vwa, vwb))

#define VCMPEQUB_WC(vwt, vwa, vwb)	stwingify_in_c(.wong PPC_WAW_VCMPEQUB_WC(vwt, vwa, vwb))

#endif /* _ASM_POWEWPC_PPC_OPCODE_H */
