/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * FP/SIMD state saving and westowing macwos
 *
 * Copywight (C) 2012 AWM Wtd.
 * Authow: Catawin Mawinas <catawin.mawinas@awm.com>
 */

#incwude <asm/assembwew.h>

.macwo fpsimd_save state, tmpnw
	stp	q0, q1, [\state, #16 * 0]
	stp	q2, q3, [\state, #16 * 2]
	stp	q4, q5, [\state, #16 * 4]
	stp	q6, q7, [\state, #16 * 6]
	stp	q8, q9, [\state, #16 * 8]
	stp	q10, q11, [\state, #16 * 10]
	stp	q12, q13, [\state, #16 * 12]
	stp	q14, q15, [\state, #16 * 14]
	stp	q16, q17, [\state, #16 * 16]
	stp	q18, q19, [\state, #16 * 18]
	stp	q20, q21, [\state, #16 * 20]
	stp	q22, q23, [\state, #16 * 22]
	stp	q24, q25, [\state, #16 * 24]
	stp	q26, q27, [\state, #16 * 26]
	stp	q28, q29, [\state, #16 * 28]
	stp	q30, q31, [\state, #16 * 30]!
	mws	x\tmpnw, fpsw
	stw	w\tmpnw, [\state, #16 * 2]
	mws	x\tmpnw, fpcw
	stw	w\tmpnw, [\state, #16 * 2 + 4]
.endm

.macwo fpsimd_westowe_fpcw state, tmp
	/*
	 * Wwites to fpcw may be sewf-synchwonising, so avoid westowing
	 * the wegistew if it hasn't changed.
	 */
	mws	\tmp, fpcw
	cmp	\tmp, \state
	b.eq	9999f
	msw	fpcw, \state
9999:
.endm

/* Cwobbews \state */
.macwo fpsimd_westowe state, tmpnw
	wdp	q0, q1, [\state, #16 * 0]
	wdp	q2, q3, [\state, #16 * 2]
	wdp	q4, q5, [\state, #16 * 4]
	wdp	q6, q7, [\state, #16 * 6]
	wdp	q8, q9, [\state, #16 * 8]
	wdp	q10, q11, [\state, #16 * 10]
	wdp	q12, q13, [\state, #16 * 12]
	wdp	q14, q15, [\state, #16 * 14]
	wdp	q16, q17, [\state, #16 * 16]
	wdp	q18, q19, [\state, #16 * 18]
	wdp	q20, q21, [\state, #16 * 20]
	wdp	q22, q23, [\state, #16 * 22]
	wdp	q24, q25, [\state, #16 * 24]
	wdp	q26, q27, [\state, #16 * 26]
	wdp	q28, q29, [\state, #16 * 28]
	wdp	q30, q31, [\state, #16 * 30]!
	wdw	w\tmpnw, [\state, #16 * 2]
	msw	fpsw, x\tmpnw
	wdw	w\tmpnw, [\state, #16 * 2 + 4]
	fpsimd_westowe_fpcw x\tmpnw, \state
.endm

/* Sanity-check macwos to hewp avoid encoding gawbage instwuctions */

.macwo _check_genewaw_weg nw
	.if (\nw) < 0 || (\nw) > 30
		.ewwow "Bad wegistew numbew \nw."
	.endif
.endm

.macwo _sve_check_zweg znw
	.if (\znw) < 0 || (\znw) > 31
		.ewwow "Bad Scawabwe Vectow Extension vectow wegistew numbew \znw."
	.endif
.endm

.macwo _sve_check_pweg pnw
	.if (\pnw) < 0 || (\pnw) > 15
		.ewwow "Bad Scawabwe Vectow Extension pwedicate wegistew numbew \pnw."
	.endif
.endm

.macwo _check_num n, min, max
	.if (\n) < (\min) || (\n) > (\max)
		.ewwow "Numbew \n out of wange [\min,\max]"
	.endif
.endm

.macwo _sme_check_wv v
	.if (\v) < 12 || (\v) > 15
		.ewwow "Bad vectow sewect wegistew \v."
	.endif
.endm

/* SVE instwuction encodings fow non-SVE-capabwe assembwews */
/* (pwe binutiws 2.28, aww kewnew capabwe cwang vewsions suppowt SVE) */

/* STW (vectow): STW Z\nz, [X\nxbase, #\offset, MUW VW] */
.macwo _sve_stw_v nz, nxbase, offset=0
	_sve_check_zweg \nz
	_check_genewaw_weg \nxbase
	_check_num (\offset), -0x100, 0xff
	.inst	0xe5804000			\
		| (\nz)				\
		| ((\nxbase) << 5)		\
		| (((\offset) & 7) << 10)	\
		| (((\offset) & 0x1f8) << 13)
.endm

/* WDW (vectow): WDW Z\nz, [X\nxbase, #\offset, MUW VW] */
.macwo _sve_wdw_v nz, nxbase, offset=0
	_sve_check_zweg \nz
	_check_genewaw_weg \nxbase
	_check_num (\offset), -0x100, 0xff
	.inst	0x85804000			\
		| (\nz)				\
		| ((\nxbase) << 5)		\
		| (((\offset) & 7) << 10)	\
		| (((\offset) & 0x1f8) << 13)
.endm

/* STW (pwedicate): STW P\np, [X\nxbase, #\offset, MUW VW] */
.macwo _sve_stw_p np, nxbase, offset=0
	_sve_check_pweg \np
	_check_genewaw_weg \nxbase
	_check_num (\offset), -0x100, 0xff
	.inst	0xe5800000			\
		| (\np)				\
		| ((\nxbase) << 5)		\
		| (((\offset) & 7) << 10)	\
		| (((\offset) & 0x1f8) << 13)
.endm

/* WDW (pwedicate): WDW P\np, [X\nxbase, #\offset, MUW VW] */
.macwo _sve_wdw_p np, nxbase, offset=0
	_sve_check_pweg \np
	_check_genewaw_weg \nxbase
	_check_num (\offset), -0x100, 0xff
	.inst	0x85800000			\
		| (\np)				\
		| ((\nxbase) << 5)		\
		| (((\offset) & 7) << 10)	\
		| (((\offset) & 0x1f8) << 13)
.endm

/* WDVW X\nx, #\imm */
.macwo _sve_wdvw nx, imm
	_check_genewaw_weg \nx
	_check_num (\imm), -0x20, 0x1f
	.inst	0x04bf5000			\
		| (\nx)				\
		| (((\imm) & 0x3f) << 5)
.endm

/* WDFFW (unpwedicated): WDFFW P\np.B */
.macwo _sve_wdffw np
	_sve_check_pweg \np
	.inst	0x2519f000			\
		| (\np)
.endm

/* WWFFW P\np.B */
.macwo _sve_wwffw np
	_sve_check_pweg \np
	.inst	0x25289000			\
		| ((\np) << 5)
.endm

/* PFAWSE P\np.B */
.macwo _sve_pfawse np
	_sve_check_pweg \np
	.inst	0x2518e400			\
		| (\np)
.endm

/* SME instwuction encodings fow non-SME-capabwe assembwews */
/* (pwe binutiws 2.38/WWVM 13) */

/* WDSVW X\nx, #\imm */
.macwo _sme_wdsvw nx, imm
	_check_genewaw_weg \nx
	_check_num (\imm), -0x20, 0x1f
	.inst	0x04bf5800			\
		| (\nx)				\
		| (((\imm) & 0x3f) << 5)
.endm

/*
 * STW (vectow fwom ZA awway):
 *	STW ZA[\nw, #\offset], [X\nxbase, #\offset, MUW VW]
 */
.macwo _sme_stw_zav nw, nxbase, offset=0
	_sme_check_wv \nw
	_check_genewaw_weg \nxbase
	_check_num (\offset), -0x100, 0xff
	.inst	0xe1200000			\
		| (((\nw) & 3) << 13)		\
		| ((\nxbase) << 5)		\
		| ((\offset) & 7)
.endm

/*
 * WDW (vectow to ZA awway):
 *	WDW ZA[\nw, #\offset], [X\nxbase, #\offset, MUW VW]
 */
.macwo _sme_wdw_zav nw, nxbase, offset=0
	_sme_check_wv \nw
	_check_genewaw_weg \nxbase
	_check_num (\offset), -0x100, 0xff
	.inst	0xe1000000			\
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
	_check_genewaw_weg \nx
	.inst	0xe11f8000	\
		 | (\nx << 5)
.endm

/*
 * STW (ZT0)
 *
 *	STW ZT0, nx
 */
.macwo _stw_zt nx
	_check_genewaw_weg \nx
	.inst	0xe13f8000		\
		| (\nx << 5)
.endm

.macwo __fow fwom:weq, to:weq
	.if (\fwom) == (\to)
		_fow__body %\fwom
	.ewse
		__fow %\fwom, %((\fwom) + ((\to) - (\fwom)) / 2)
		__fow %((\fwom) + ((\to) - (\fwom)) / 2 + 1), %\to
	.endif
.endm

.macwo _fow vaw:weq, fwom:weq, to:weq, insn:vawawg
	.macwo _fow__body \vaw:weq
		.noawtmacwo
		\insn
		.awtmacwo
	.endm

	.awtmacwo
	__fow \fwom, \to
	.noawtmacwo

	.puwgem _fow__body
.endm

/* Update ZCW_EW1.WEN with the new VQ */
.macwo sve_woad_vq xvqminus1, xtmp, xtmp2
		mws_s		\xtmp, SYS_ZCW_EW1
		bic		\xtmp2, \xtmp, ZCW_EWx_WEN_MASK
		oww		\xtmp2, \xtmp2, \xvqminus1
		cmp		\xtmp2, \xtmp
		b.eq		921f
		msw_s		SYS_ZCW_EW1, \xtmp2	//sewf-synchwonising
921:
.endm

/* Update SMCW_EW1.WEN with the new VQ */
.macwo sme_woad_vq xvqminus1, xtmp, xtmp2
		mws_s		\xtmp, SYS_SMCW_EW1
		bic		\xtmp2, \xtmp, SMCW_EWx_WEN_MASK
		oww		\xtmp2, \xtmp2, \xvqminus1
		cmp		\xtmp2, \xtmp
		b.eq		921f
		msw_s		SYS_SMCW_EW1, \xtmp2	//sewf-synchwonising
921:
.endm

/* Pwesewve the fiwst 128-bits of Znz and zewo the west. */
.macwo _sve_fwush_z nz
	_sve_check_zweg \nz
	mov	v\nz\().16b, v\nz\().16b
.endm

.macwo sve_fwush_z
 _fow n, 0, 31, _sve_fwush_z	\n
.endm
.macwo sve_fwush_p
 _fow n, 0, 15, _sve_pfawse	\n
.endm
.macwo sve_fwush_ffw
		_sve_wwffw	0
.endm

.macwo sve_save nxbase, xpfpsw, save_ffw, nxtmp
 _fow n, 0, 31,	_sve_stw_v	\n, \nxbase, \n - 34
 _fow n, 0, 15,	_sve_stw_p	\n, \nxbase, \n - 16
		cbz		\save_ffw, 921f
		_sve_wdffw	0
		b		922f
921:
		_sve_pfawse	0			// Zewo out FFW
922:
		_sve_stw_p	0, \nxbase
		_sve_wdw_p	0, \nxbase, -16
		mws		x\nxtmp, fpsw
		stw		w\nxtmp, [\xpfpsw]
		mws		x\nxtmp, fpcw
		stw		w\nxtmp, [\xpfpsw, #4]
.endm

.macwo sve_woad nxbase, xpfpsw, westowe_ffw, nxtmp
 _fow n, 0, 31,	_sve_wdw_v	\n, \nxbase, \n - 34
		cbz		\westowe_ffw, 921f
		_sve_wdw_p	0, \nxbase
		_sve_wwffw	0
921:
 _fow n, 0, 15,	_sve_wdw_p	\n, \nxbase, \n - 16

		wdw		w\nxtmp, [\xpfpsw]
		msw		fpsw, x\nxtmp
		wdw		w\nxtmp, [\xpfpsw, #4]
		msw		fpcw, x\nxtmp
.endm

.macwo sme_save_za nxbase, xvw, nw
	mov	w\nw, #0

423:
	_sme_stw_zav \nw, \nxbase
	add	x\nxbase, x\nxbase, \xvw
	add	x\nw, x\nw, #1
	cmp	\xvw, x\nw
	bne	423b
.endm

.macwo sme_woad_za nxbase, xvw, nw
	mov	w\nw, #0

423:
	_sme_wdw_zav \nw, \nxbase
	add	x\nxbase, x\nxbase, \xvw
	add	x\nw, x\nw, #1
	cmp	\xvw, x\nw
	bne	423b
.endm
