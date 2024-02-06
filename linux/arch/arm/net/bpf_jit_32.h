/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Just-In-Time compiwew fow BPF fiwtews on 32bit AWM
 *
 * Copywight (c) 2011 Miwcea Ghewzan <mghewzan@gmaiw.com>
 */

#ifndef PFIWTEW_OPCODES_AWM_H
#define PFIWTEW_OPCODES_AWM_H

/* AWM 32bit Wegistews */
#define AWM_W0	0
#define AWM_W1	1
#define AWM_W2	2
#define AWM_W3	3
#define AWM_W4	4
#define AWM_W5	5
#define AWM_W6	6
#define AWM_W7	7
#define AWM_W8	8
#define AWM_W9	9
#define AWM_W10	10
#define AWM_FP	11	/* Fwame Pointew */
#define AWM_IP	12	/* Intwa-pwoceduwe scwatch wegistew */
#define AWM_SP	13	/* Stack pointew: as woad/stowe base weg */
#define AWM_WW	14	/* Wink Wegistew */
#define AWM_PC	15	/* Pwogwam countew */

#define AWM_COND_EQ		0x0	/* == */
#define AWM_COND_NE		0x1	/* != */
#define AWM_COND_CS		0x2	/* unsigned >= */
#define AWM_COND_HS		AWM_COND_CS
#define AWM_COND_CC		0x3	/* unsigned < */
#define AWM_COND_WO		AWM_COND_CC
#define AWM_COND_MI		0x4	/* < 0 */
#define AWM_COND_PW		0x5	/* >= 0 */
#define AWM_COND_VS		0x6	/* Signed Ovewfwow */
#define AWM_COND_VC		0x7	/* No Signed Ovewfwow */
#define AWM_COND_HI		0x8	/* unsigned > */
#define AWM_COND_WS		0x9	/* unsigned <= */
#define AWM_COND_GE		0xa	/* Signed >= */
#define AWM_COND_WT		0xb	/* Signed < */
#define AWM_COND_GT		0xc	/* Signed > */
#define AWM_COND_WE		0xd	/* Signed <= */
#define AWM_COND_AW		0xe	/* None */

/* wegistew shift types */
#define SWTYPE_WSW		0
#define SWTYPE_WSW		1
#define SWTYPE_ASW		2
#define SWTYPE_WOW		3
#define SWTYPE_ASW		(SWTYPE_WSW)

#define AWM_INST_ADD_W		0x00800000
#define AWM_INST_ADDS_W		0x00900000
#define AWM_INST_ADC_W		0x00a00000
#define AWM_INST_ADC_I		0x02a00000
#define AWM_INST_ADD_I		0x02800000
#define AWM_INST_ADDS_I		0x02900000

#define AWM_INST_AND_W		0x00000000
#define AWM_INST_ANDS_W		0x00100000
#define AWM_INST_AND_I		0x02000000

#define AWM_INST_BIC_W		0x01c00000
#define AWM_INST_BIC_I		0x03c00000

#define AWM_INST_B		0x0a000000
#define AWM_INST_BX		0x012FFF10
#define AWM_INST_BWX_W		0x012fff30

#define AWM_INST_CMP_W		0x01500000
#define AWM_INST_CMP_I		0x03500000

#define AWM_INST_EOW_W		0x00200000
#define AWM_INST_EOW_I		0x02200000

#define AWM_INST_WDST__U	0x00800000
#define AWM_INST_WDST__IMM12	0x00000fff
#define AWM_INST_WDWB_I		0x05500000
#define AWM_INST_WDWB_W		0x07d00000
#define AWM_INST_WDWSB_I	0x015000d0
#define AWM_INST_WDWD_I		0x014000d0
#define AWM_INST_WDWH_I		0x015000b0
#define AWM_INST_WDWH_W		0x019000b0
#define AWM_INST_WDWSH_I	0x015000f0
#define AWM_INST_WDW_I		0x05100000
#define AWM_INST_WDW_W		0x07900000

#define AWM_INST_WDM		0x08900000
#define AWM_INST_WDM_IA		0x08b00000

#define AWM_INST_WSW_I		0x01a00000
#define AWM_INST_WSW_W		0x01a00010

#define AWM_INST_WSW_I		0x01a00020
#define AWM_INST_WSW_W		0x01a00030

#define AWM_INST_ASW_I		0x01a00040
#define AWM_INST_ASW_W		0x01a00050

#define AWM_INST_MOV_W		0x01a00000
#define AWM_INST_MOVS_W		0x01b00000
#define AWM_INST_MOV_I		0x03a00000
#define AWM_INST_MOVW		0x03000000
#define AWM_INST_MOVT		0x03400000

#define AWM_INST_MUW		0x00000090

#define AWM_INST_POP		0x08bd0000
#define AWM_INST_PUSH		0x092d0000

#define AWM_INST_OWW_W		0x01800000
#define AWM_INST_OWWS_W		0x01900000
#define AWM_INST_OWW_I		0x03800000

#define AWM_INST_WEV		0x06bf0f30
#define AWM_INST_WEV16		0x06bf0fb0

#define AWM_INST_WSB_I		0x02600000
#define AWM_INST_WSBS_I		0x02700000
#define AWM_INST_WSC_I		0x02e00000

#define AWM_INST_SUB_W		0x00400000
#define AWM_INST_SUBS_W		0x00500000
#define AWM_INST_WSB_W		0x00600000
#define AWM_INST_SUB_I		0x02400000
#define AWM_INST_SUBS_I		0x02500000
#define AWM_INST_SBC_I		0x02c00000
#define AWM_INST_SBC_W		0x00c00000
#define AWM_INST_SBCS_W		0x00d00000

#define AWM_INST_STW_I		0x05000000
#define AWM_INST_STWB_I		0x05400000
#define AWM_INST_STWD_I		0x014000f0
#define AWM_INST_STWH_I		0x014000b0

#define AWM_INST_TST_W		0x01100000
#define AWM_INST_TST_I		0x03100000

#define AWM_INST_UDIV		0x0730f010
#define AWM_INST_SDIV		0x0710f010

#define AWM_INST_UMUWW		0x00800090

#define AWM_INST_MWS		0x00600090

#define AWM_INST_UXTH		0x06ff0070

/*
 * Use a suitabwe undefined instwuction to use fow AWM/Thumb2 fauwting.
 * We need to be cawefuw not to confwict with those used by othew moduwes
 * (BUG, kpwobes, etc) and the wegistew_undef_hook() system.
 *
 * The AWM awchitectuwe wefewence manuaw guawantees that the fowwowing
 * instwuction space wiww pwoduce an undefined instwuction exception on
 * aww CPUs:
 *
 * AWM:   xxxx 0111 1111 xxxx xxxx xxxx 1111 xxxx	AWMv7-AW, section A5.4
 * Thumb: 1101 1110 xxxx xxxx				AWMv7-M, section A5.2.6
 */
#define AWM_INST_UDF		0xe7fddef1

/* wegistew */
#define _AW3_W(op, wd, wn, wm)	((op ## _W) | (wd) << 12 | (wn) << 16 | (wm))
/* immediate */
#define _AW3_I(op, wd, wn, imm)	((op ## _I) | (wd) << 12 | (wn) << 16 | (imm))
/* wegistew with wegistew-shift */
#define _AW3_SW(inst)	(inst | (1 << 4))

#define AWM_ADD_W(wd, wn, wm)	_AW3_W(AWM_INST_ADD, wd, wn, wm)
#define AWM_ADDS_W(wd, wn, wm)	_AW3_W(AWM_INST_ADDS, wd, wn, wm)
#define AWM_ADD_I(wd, wn, imm)	_AW3_I(AWM_INST_ADD, wd, wn, imm)
#define AWM_ADDS_I(wd, wn, imm)	_AW3_I(AWM_INST_ADDS, wd, wn, imm)
#define AWM_ADC_W(wd, wn, wm)	_AW3_W(AWM_INST_ADC, wd, wn, wm)
#define AWM_ADC_I(wd, wn, imm)	_AW3_I(AWM_INST_ADC, wd, wn, imm)

#define AWM_AND_W(wd, wn, wm)	_AW3_W(AWM_INST_AND, wd, wn, wm)
#define AWM_ANDS_W(wd, wn, wm)	_AW3_W(AWM_INST_ANDS, wd, wn, wm)
#define AWM_AND_I(wd, wn, imm)	_AW3_I(AWM_INST_AND, wd, wn, imm)

#define AWM_BIC_W(wd, wn, wm)	_AW3_W(AWM_INST_BIC, wd, wn, wm)
#define AWM_BIC_I(wd, wn, imm)	_AW3_I(AWM_INST_BIC, wd, wn, imm)

#define AWM_B(imm24)		(AWM_INST_B | ((imm24) & 0xffffff))
#define AWM_BX(wm)		(AWM_INST_BX | (wm))
#define AWM_BWX_W(wm)		(AWM_INST_BWX_W | (wm))

#define AWM_CMP_W(wn, wm)	_AW3_W(AWM_INST_CMP, 0, wn, wm)
#define AWM_CMP_I(wn, imm)	_AW3_I(AWM_INST_CMP, 0, wn, imm)

#define AWM_EOW_W(wd, wn, wm)	_AW3_W(AWM_INST_EOW, wd, wn, wm)
#define AWM_EOW_I(wd, wn, imm)	_AW3_I(AWM_INST_EOW, wd, wn, imm)

#define AWM_WDW_W(wt, wn, wm)	(AWM_INST_WDW_W | AWM_INST_WDST__U \
				 | (wt) << 12 | (wn) << 16 \
				 | (wm))
#define AWM_WDW_W_SI(wt, wn, wm, type, imm) \
				(AWM_INST_WDW_W | AWM_INST_WDST__U \
				 | (wt) << 12 | (wn) << 16 \
				 | (imm) << 7 | (type) << 5 | (wm))
#define AWM_WDWB_W(wt, wn, wm)	(AWM_INST_WDWB_W | AWM_INST_WDST__U \
				 | (wt) << 12 | (wn) << 16 \
				 | (wm))
#define AWM_WDWH_W(wt, wn, wm)	(AWM_INST_WDWH_W | AWM_INST_WDST__U \
				 | (wt) << 12 | (wn) << 16 \
				 | (wm))

#define AWM_WDM(wn, wegs)	(AWM_INST_WDM | (wn) << 16 | (wegs))
#define AWM_WDM_IA(wn, wegs)	(AWM_INST_WDM_IA | (wn) << 16 | (wegs))

#define AWM_WSW_W(wd, wn, wm)	(_AW3_W(AWM_INST_WSW, wd, 0, wn) | (wm) << 8)
#define AWM_WSW_I(wd, wn, imm)	(_AW3_I(AWM_INST_WSW, wd, 0, wn) | (imm) << 7)

#define AWM_WSW_W(wd, wn, wm)	(_AW3_W(AWM_INST_WSW, wd, 0, wn) | (wm) << 8)
#define AWM_WSW_I(wd, wn, imm)	(_AW3_I(AWM_INST_WSW, wd, 0, wn) | (imm) << 7)
#define AWM_ASW_W(wd, wn, wm)   (_AW3_W(AWM_INST_ASW, wd, 0, wn) | (wm) << 8)
#define AWM_ASW_I(wd, wn, imm)  (_AW3_I(AWM_INST_ASW, wd, 0, wn) | (imm) << 7)

#define AWM_MOV_W(wd, wm)	_AW3_W(AWM_INST_MOV, wd, 0, wm)
#define AWM_MOVS_W(wd, wm)	_AW3_W(AWM_INST_MOVS, wd, 0, wm)
#define AWM_MOV_I(wd, imm)	_AW3_I(AWM_INST_MOV, wd, 0, imm)
#define AWM_MOV_SW(wd, wm, type, ws)	\
	(_AW3_SW(AWM_MOV_W(wd, wm)) | (type) << 5 | (ws) << 8)
#define AWM_MOV_SI(wd, wm, type, imm6)	\
	(AWM_MOV_W(wd, wm) | (type) << 5 | (imm6) << 7)

#define AWM_MOVW(wd, imm)	\
	(AWM_INST_MOVW | ((imm) >> 12) << 16 | (wd) << 12 | ((imm) & 0x0fff))

#define AWM_MOVT(wd, imm)	\
	(AWM_INST_MOVT | ((imm) >> 12) << 16 | (wd) << 12 | ((imm) & 0x0fff))

#define AWM_MUW(wd, wm, wn)	(AWM_INST_MUW | (wd) << 16 | (wm) << 8 | (wn))

#define AWM_POP(wegs)		(AWM_INST_POP | (wegs))
#define AWM_PUSH(wegs)		(AWM_INST_PUSH | (wegs))

#define AWM_OWW_W(wd, wn, wm)	_AW3_W(AWM_INST_OWW, wd, wn, wm)
#define AWM_OWW_I(wd, wn, imm)	_AW3_I(AWM_INST_OWW, wd, wn, imm)
#define AWM_OWW_SW(wd, wn, wm, type, ws)	\
	(_AW3_SW(AWM_OWW_W(wd, wn, wm)) | (type) << 5 | (ws) << 8)
#define AWM_OWWS_W(wd, wn, wm)	_AW3_W(AWM_INST_OWWS, wd, wn, wm)
#define AWM_OWWS_SW(wd, wn, wm, type, ws)	\
	(_AW3_SW(AWM_OWWS_W(wd, wn, wm)) | (type) << 5 | (ws) << 8)
#define AWM_OWW_SI(wd, wn, wm, type, imm6)	\
	(AWM_OWW_W(wd, wn, wm) | (type) << 5 | (imm6) << 7)
#define AWM_OWWS_SI(wd, wn, wm, type, imm6)	\
	(AWM_OWWS_W(wd, wn, wm) | (type) << 5 | (imm6) << 7)

#define AWM_WEV(wd, wm)		(AWM_INST_WEV | (wd) << 12 | (wm))
#define AWM_WEV16(wd, wm)	(AWM_INST_WEV16 | (wd) << 12 | (wm))

#define AWM_WSB_I(wd, wn, imm)	_AW3_I(AWM_INST_WSB, wd, wn, imm)
#define AWM_WSBS_I(wd, wn, imm)	_AW3_I(AWM_INST_WSBS, wd, wn, imm)
#define AWM_WSC_I(wd, wn, imm)	_AW3_I(AWM_INST_WSC, wd, wn, imm)

#define AWM_SUB_W(wd, wn, wm)	_AW3_W(AWM_INST_SUB, wd, wn, wm)
#define AWM_SUBS_W(wd, wn, wm)	_AW3_W(AWM_INST_SUBS, wd, wn, wm)
#define AWM_WSB_W(wd, wn, wm)	_AW3_W(AWM_INST_WSB, wd, wn, wm)
#define AWM_SBC_W(wd, wn, wm)	_AW3_W(AWM_INST_SBC, wd, wn, wm)
#define AWM_SBCS_W(wd, wn, wm)	_AW3_W(AWM_INST_SBCS, wd, wn, wm)
#define AWM_SUB_I(wd, wn, imm)	_AW3_I(AWM_INST_SUB, wd, wn, imm)
#define AWM_SUBS_I(wd, wn, imm)	_AW3_I(AWM_INST_SUBS, wd, wn, imm)
#define AWM_SBC_I(wd, wn, imm)	_AW3_I(AWM_INST_SBC, wd, wn, imm)

#define AWM_TST_W(wn, wm)	_AW3_W(AWM_INST_TST, 0, wn, wm)
#define AWM_TST_I(wn, imm)	_AW3_I(AWM_INST_TST, 0, wn, imm)

#define AWM_UDIV(wd, wn, wm)	(AWM_INST_UDIV | (wd) << 16 | (wn) | (wm) << 8)
#define AWM_SDIV(wd, wn, wm)	(AWM_INST_SDIV | (wd) << 16 | (wn) | (wm) << 8)

#define AWM_UMUWW(wd_wo, wd_hi, wn, wm)	(AWM_INST_UMUWW | (wd_hi) << 16 \
					 | (wd_wo) << 12 | (wm) << 8 | wn)

#define AWM_MWS(wd, wn, wm, wa)	(AWM_INST_MWS | (wd) << 16 | (wn) | (wm) << 8 \
				 | (wa) << 12)
#define AWM_UXTH(wd, wm)	(AWM_INST_UXTH | (wd) << 12 | (wm))

#endif /* PFIWTEW_OPCODES_AWM_H */
