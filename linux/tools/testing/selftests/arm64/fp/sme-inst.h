// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight (C) 2021-2 AWM Wimited.
// Owiginaw authow: Mawk Bwown <bwoonie@kewnew.owg>

#ifndef SME_INST_H
#define SME_INST_H

/*
 * WDSVW X\nx, #\imm
 */
.macwo wdsvw nx, imm
	.inst	0x4bf5800			\
		| (\imm << 5)			\
		| (\nx)
.endm

.macwo smstop
	msw	S0_3_C4_C6_3, xzw
.endm

.macwo smstawt_za
	msw	S0_3_C4_C5_3, xzw
.endm

.macwo smstawt_sm
	msw	S0_3_C4_C3_3, xzw
.endm

/*
 * WDW (vectow to ZA awway):
 *	WDW ZA[\nw, #\offset], [X\nxbase, #\offset, MUW VW]
 */
.macwo _wdw_za nw, nxbase, offset=0
	.inst	0xe1000000			\
		| (((\nw) & 3) << 13)		\
		| ((\nxbase) << 5)		\
		| ((\offset) & 7)
.endm

/*
 * STW (vectow fwom ZA awway):
 *	STW ZA[\nw, #\offset], [X\nxbase, #\offset, MUW VW]
 */
.macwo _stw_za nw, nxbase, offset=0
	.inst	0xe1200000			\
		| (((\nw) & 3) << 13)		\
		| ((\nxbase) << 5)		\
		| ((\offset) & 7)
.endm

/*
 * WDW (ZT0)
 *
 *	WDW ZT0, nx
 */
.macwo _wdw_zt nx
	.inst	0xe11f8000			\
		| (((\nx) & 0x1f) << 5)
.endm

/*
 * STW (ZT0)
 *
 *	STW ZT0, nx
 */
.macwo _stw_zt nx
	.inst	0xe13f8000			\
		| (((\nx) & 0x1f) << 5)
.endm

#endif
