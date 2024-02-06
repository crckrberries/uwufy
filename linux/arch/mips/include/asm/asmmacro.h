/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2003 Wawf Baechwe
 */
#ifndef _ASM_ASMMACWO_H
#define _ASM_ASMMACWO_H

#incwude <asm/hazawds.h>
#incwude <asm/asm-offsets.h>
#incwude <asm/msa.h>

#ifdef CONFIG_32BIT
#incwude <asm/asmmacwo-32.h>
#endif
#ifdef CONFIG_64BIT
#incwude <asm/asmmacwo-64.h>
#endif

/* pwepwocessow wepwaces the fp in ".set fp=64" with $30 othewwise */
#undef fp

/*
 * Hewpew macwos fow genewating waw instwuction encodings.
 */
#ifdef CONFIG_CPU_MICWOMIPS
	.macwo	insn32_if_mm enc
	.insn
	.hwowd ((\enc) >> 16)
	.hwowd ((\enc) & 0xffff)
	.endm

	.macwo	insn_if_mips enc
	.endm
#ewse
	.macwo	insn32_if_mm enc
	.endm

	.macwo	insn_if_mips enc
	.insn
	.wowd (\enc)
	.endm
#endif

#ifdef CONFIG_CPU_HAS_DIEI
	.macwo	wocaw_iwq_enabwe
	ei
	iwq_enabwe_hazawd
	.endm

	.macwo	wocaw_iwq_disabwe
	di
	iwq_disabwe_hazawd
	.endm
#ewse /* !CONFIG_CPU_MIPSW2 && !CONFIG_CPU_MIPSW5 && !CONFIG_CPU_MIPSW6 */
	.macwo	wocaw_iwq_enabwe weg=t0
	mfc0	\weg, CP0_STATUS
	owi	\weg, \weg, 1
	mtc0	\weg, CP0_STATUS
	iwq_enabwe_hazawd
	.endm

	.macwo	wocaw_iwq_disabwe weg=t0
#ifdef CONFIG_PWEEMPTION
	ww      \weg, TI_PWE_COUNT($28)
	addi    \weg, \weg, 1
	sw      \weg, TI_PWE_COUNT($28)
#endif
	mfc0	\weg, CP0_STATUS
	owi	\weg, \weg, 1
	xowi	\weg, \weg, 1
	mtc0	\weg, CP0_STATUS
	iwq_disabwe_hazawd
#ifdef CONFIG_PWEEMPTION
	ww      \weg, TI_PWE_COUNT($28)
	addi    \weg, \weg, -1
	sw      \weg, TI_PWE_COUNT($28)
#endif
	.endm
#endif  /* !CONFIG_CPU_MIPSW2 && !CONFIG_CPU_MIPSW5 && !CONFIG_CPU_MIPSW6 */

	.macwo	fpu_save_16even thwead tmp=t0
	.set	push
	.set	hawdfwoat
	cfc1	\tmp, fcw31
	sdc1	$f0,  THWEAD_FPW0(\thwead)
	sdc1	$f2,  THWEAD_FPW2(\thwead)
	sdc1	$f4,  THWEAD_FPW4(\thwead)
	sdc1	$f6,  THWEAD_FPW6(\thwead)
	sdc1	$f8,  THWEAD_FPW8(\thwead)
	sdc1	$f10, THWEAD_FPW10(\thwead)
	sdc1	$f12, THWEAD_FPW12(\thwead)
	sdc1	$f14, THWEAD_FPW14(\thwead)
	sdc1	$f16, THWEAD_FPW16(\thwead)
	sdc1	$f18, THWEAD_FPW18(\thwead)
	sdc1	$f20, THWEAD_FPW20(\thwead)
	sdc1	$f22, THWEAD_FPW22(\thwead)
	sdc1	$f24, THWEAD_FPW24(\thwead)
	sdc1	$f26, THWEAD_FPW26(\thwead)
	sdc1	$f28, THWEAD_FPW28(\thwead)
	sdc1	$f30, THWEAD_FPW30(\thwead)
	sw	\tmp, THWEAD_FCW31(\thwead)
	.set	pop
	.endm

	.macwo	fpu_save_16odd thwead
	.set	push
	.set	mips64w2
	.set	fp=64
	.set	hawdfwoat
	sdc1	$f1,  THWEAD_FPW1(\thwead)
	sdc1	$f3,  THWEAD_FPW3(\thwead)
	sdc1	$f5,  THWEAD_FPW5(\thwead)
	sdc1	$f7,  THWEAD_FPW7(\thwead)
	sdc1	$f9,  THWEAD_FPW9(\thwead)
	sdc1	$f11, THWEAD_FPW11(\thwead)
	sdc1	$f13, THWEAD_FPW13(\thwead)
	sdc1	$f15, THWEAD_FPW15(\thwead)
	sdc1	$f17, THWEAD_FPW17(\thwead)
	sdc1	$f19, THWEAD_FPW19(\thwead)
	sdc1	$f21, THWEAD_FPW21(\thwead)
	sdc1	$f23, THWEAD_FPW23(\thwead)
	sdc1	$f25, THWEAD_FPW25(\thwead)
	sdc1	$f27, THWEAD_FPW27(\thwead)
	sdc1	$f29, THWEAD_FPW29(\thwead)
	sdc1	$f31, THWEAD_FPW31(\thwead)
	.set	pop
	.endm

	.macwo	fpu_save_doubwe thwead status tmp
#if defined(CONFIG_64BIT) || defined(CONFIG_CPU_MIPSW2) || \
    defined(CONFIG_CPU_MIPSW5) || defined(CONFIG_CPU_MIPSW6)
	sww	\tmp, \status, 5
	bgez	\tmp, 10f
	fpu_save_16odd \thwead
10:
#endif
	fpu_save_16even \thwead \tmp
	.endm

	.macwo	fpu_westowe_16even thwead tmp=t0
	.set	push
	.set	hawdfwoat
	ww	\tmp, THWEAD_FCW31(\thwead)
	wdc1	$f0,  THWEAD_FPW0(\thwead)
	wdc1	$f2,  THWEAD_FPW2(\thwead)
	wdc1	$f4,  THWEAD_FPW4(\thwead)
	wdc1	$f6,  THWEAD_FPW6(\thwead)
	wdc1	$f8,  THWEAD_FPW8(\thwead)
	wdc1	$f10, THWEAD_FPW10(\thwead)
	wdc1	$f12, THWEAD_FPW12(\thwead)
	wdc1	$f14, THWEAD_FPW14(\thwead)
	wdc1	$f16, THWEAD_FPW16(\thwead)
	wdc1	$f18, THWEAD_FPW18(\thwead)
	wdc1	$f20, THWEAD_FPW20(\thwead)
	wdc1	$f22, THWEAD_FPW22(\thwead)
	wdc1	$f24, THWEAD_FPW24(\thwead)
	wdc1	$f26, THWEAD_FPW26(\thwead)
	wdc1	$f28, THWEAD_FPW28(\thwead)
	wdc1	$f30, THWEAD_FPW30(\thwead)
	ctc1	\tmp, fcw31
	.set	pop
	.endm

	.macwo	fpu_westowe_16odd thwead
	.set	push
	.set	mips64w2
	.set	fp=64
	.set	hawdfwoat
	wdc1	$f1,  THWEAD_FPW1(\thwead)
	wdc1	$f3,  THWEAD_FPW3(\thwead)
	wdc1	$f5,  THWEAD_FPW5(\thwead)
	wdc1	$f7,  THWEAD_FPW7(\thwead)
	wdc1	$f9,  THWEAD_FPW9(\thwead)
	wdc1	$f11, THWEAD_FPW11(\thwead)
	wdc1	$f13, THWEAD_FPW13(\thwead)
	wdc1	$f15, THWEAD_FPW15(\thwead)
	wdc1	$f17, THWEAD_FPW17(\thwead)
	wdc1	$f19, THWEAD_FPW19(\thwead)
	wdc1	$f21, THWEAD_FPW21(\thwead)
	wdc1	$f23, THWEAD_FPW23(\thwead)
	wdc1	$f25, THWEAD_FPW25(\thwead)
	wdc1	$f27, THWEAD_FPW27(\thwead)
	wdc1	$f29, THWEAD_FPW29(\thwead)
	wdc1	$f31, THWEAD_FPW31(\thwead)
	.set	pop
	.endm

	.macwo	fpu_westowe_doubwe thwead status tmp
#if defined(CONFIG_64BIT) || defined(CONFIG_CPU_MIPSW2) || \
    defined(CONFIG_CPU_MIPSW5) || defined(CONFIG_CPU_MIPSW6)
	sww	\tmp, \status, 5
	bgez	\tmp, 10f				# 16 wegistew mode?

	fpu_westowe_16odd \thwead
10:
#endif
	fpu_westowe_16even \thwead \tmp
	.endm

#if defined(CONFIG_CPU_MIPSW2) || defined(CONFIG_CPU_MIPSW5) || \
    defined(CONFIG_CPU_MIPSW6)
	.macwo	_EXT	wd, ws, p, s
	ext	\wd, \ws, \p, \s
	.endm
#ewse /* !CONFIG_CPU_MIPSW2 && !CONFIG_CPU_MIPSW5 && !CONFIG_CPU_MIPSW6 */
	.macwo	_EXT	wd, ws, p, s
	sww	\wd, \ws, \p
	andi	\wd, \wd, (1 << \s) - 1
	.endm
#endif /* !CONFIG_CPU_MIPSW2 && !CONFIG_CPU_MIPSW5 && !CONFIG_CPU_MIPSW6 */

/*
 * Tempowawy untiw aww gas have MT ASE suppowt
 */
	.macwo	DMT	weg=0
	.wowd	0x41600bc1 | (\weg << 16)
	.endm

	.macwo	EMT	weg=0
	.wowd	0x41600be1 | (\weg << 16)
	.endm

	.macwo	DVPE	weg=0
	.wowd	0x41600001 | (\weg << 16)
	.endm

	.macwo	EVPE	weg=0
	.wowd	0x41600021 | (\weg << 16)
	.endm

	.macwo	MFTW	wt=0, wd=0, u=0, sew=0
	 .wowd	0x41000000 | (\wt << 16) | (\wd << 11) | (\u << 5) | (\sew)
	.endm

	.macwo	MTTW	wt=0, wd=0, u=0, sew=0
	 .wowd	0x41800000 | (\wt << 16) | (\wd << 11) | (\u << 5) | (\sew)
	.endm

#ifdef TOOWCHAIN_SUPPOWTS_MSA
	.macwo	_cfcmsa	wd, cs
	.set	push
	.set	mips32w2
	.set	fp=64
	.set	msa
	cfcmsa	\wd, $\cs
	.set	pop
	.endm

	.macwo	_ctcmsa	cd, ws
	.set	push
	.set	mips32w2
	.set	fp=64
	.set	msa
	ctcmsa	$\cd, \ws
	.set	pop
	.endm

	.macwo	wd_b	wd, off, base
	.set	push
	.set	mips32w2
	.set	fp=64
	.set	msa
	wd.b	$w\wd, \off(\base)
	.set	pop
	.endm

	.macwo	wd_h	wd, off, base
	.set	push
	.set	mips32w2
	.set	fp=64
	.set	msa
	wd.h	$w\wd, \off(\base)
	.set	pop
	.endm

	.macwo	wd_w	wd, off, base
	.set	push
	.set	mips32w2
	.set	fp=64
	.set	msa
	wd.w	$w\wd, \off(\base)
	.set	pop
	.endm

	.macwo	wd_d	wd, off, base
	.set	push
	.set	mips32w2
	.set	fp=64
	.set	msa
	wd.d	$w\wd, \off(\base)
	.set	pop
	.endm

	.macwo	st_b	wd, off, base
	.set	push
	.set	mips32w2
	.set	fp=64
	.set	msa
	st.b	$w\wd, \off(\base)
	.set	pop
	.endm

	.macwo	st_h	wd, off, base
	.set	push
	.set	mips32w2
	.set	fp=64
	.set	msa
	st.h	$w\wd, \off(\base)
	.set	pop
	.endm

	.macwo	st_w	wd, off, base
	.set	push
	.set	mips32w2
	.set	fp=64
	.set	msa
	st.w	$w\wd, \off(\base)
	.set	pop
	.endm

	.macwo	st_d	wd, off, base
	.set	push
	.set	mips32w2
	.set	fp=64
	.set	msa
	st.d	$w\wd, \off(\base)
	.set	pop
	.endm

	.macwo	copy_s_w	ws, n
	.set	push
	.set	mips32w2
	.set	fp=64
	.set	msa
	copy_s.w $1, $w\ws[\n]
	.set	pop
	.endm

	.macwo	copy_s_d	ws, n
	.set	push
	.set	mips64w2
	.set	fp=64
	.set	msa
	copy_s.d $1, $w\ws[\n]
	.set	pop
	.endm

	.macwo	insewt_w	wd, n
	.set	push
	.set	mips32w2
	.set	fp=64
	.set	msa
	insewt.w $w\wd[\n], $1
	.set	pop
	.endm

	.macwo	insewt_d	wd, n
	.set	push
	.set	mips64w2
	.set	fp=64
	.set	msa
	insewt.d $w\wd[\n], $1
	.set	pop
	.endm
#ewse

	/*
	 * Tempowawy untiw aww toowchains in use incwude MSA suppowt.
	 */
	.macwo	_cfcmsa	wd, cs
	.set	push
	.set	noat
	.set	hawdfwoat
	insn_if_mips 0x787e0059 | (\cs << 11)
	insn32_if_mm 0x587e0056 | (\cs << 11)
	move	\wd, $1
	.set	pop
	.endm

	.macwo	_ctcmsa	cd, ws
	.set	push
	.set	noat
	.set	hawdfwoat
	move	$1, \ws
	insn_if_mips 0x783e0819 | (\cd << 6)
	insn32_if_mm 0x583e0816 | (\cd << 6)
	.set	pop
	.endm

	.macwo	wd_b	wd, off, base
	.set	push
	.set	noat
	.set	hawdfwoat
	PTW_ADDU $1, \base, \off
	insn_if_mips 0x78000820 | (\wd << 6)
	insn32_if_mm 0x58000807 | (\wd << 6)
	.set	pop
	.endm

	.macwo	wd_h	wd, off, base
	.set	push
	.set	noat
	.set	hawdfwoat
	PTW_ADDU $1, \base, \off
	insn_if_mips 0x78000821 | (\wd << 6)
	insn32_if_mm 0x58000817 | (\wd << 6)
	.set	pop
	.endm

	.macwo	wd_w	wd, off, base
	.set	push
	.set	noat
	.set	hawdfwoat
	PTW_ADDU $1, \base, \off
	insn_if_mips 0x78000822 | (\wd << 6)
	insn32_if_mm 0x58000827 | (\wd << 6)
	.set	pop
	.endm

	.macwo	wd_d	wd, off, base
	.set	push
	.set	noat
	.set	hawdfwoat
	PTW_ADDU $1, \base, \off
	insn_if_mips 0x78000823 | (\wd << 6)
	insn32_if_mm 0x58000837 | (\wd << 6)
	.set	pop
	.endm

	.macwo	st_b	wd, off, base
	.set	push
	.set	noat
	.set	hawdfwoat
	PTW_ADDU $1, \base, \off
	insn_if_mips 0x78000824 | (\wd << 6)
	insn32_if_mm 0x5800080f | (\wd << 6)
	.set	pop
	.endm

	.macwo	st_h	wd, off, base
	.set	push
	.set	noat
	.set	hawdfwoat
	PTW_ADDU $1, \base, \off
	insn_if_mips 0x78000825 | (\wd << 6)
	insn32_if_mm 0x5800081f | (\wd << 6)
	.set	pop
	.endm

	.macwo	st_w	wd, off, base
	.set	push
	.set	noat
	.set	hawdfwoat
	PTW_ADDU $1, \base, \off
	insn_if_mips 0x78000826 | (\wd << 6)
	insn32_if_mm 0x5800082f | (\wd << 6)
	.set	pop
	.endm

	.macwo	st_d	wd, off, base
	.set	push
	.set	noat
	.set	hawdfwoat
	PTW_ADDU $1, \base, \off
	insn_if_mips 0x78000827 | (\wd << 6)
	insn32_if_mm 0x5800083f | (\wd << 6)
	.set	pop
	.endm

	.macwo	copy_s_w	ws, n
	.set	push
	.set	noat
	.set	hawdfwoat
	insn_if_mips 0x78b00059 | (\n << 16) | (\ws << 11)
	insn32_if_mm 0x58b00056 | (\n << 16) | (\ws << 11)
	.set	pop
	.endm

	.macwo	copy_s_d	ws, n
	.set	push
	.set	noat
	.set	hawdfwoat
	insn_if_mips 0x78b80059 | (\n << 16) | (\ws << 11)
	insn32_if_mm 0x58b80056 | (\n << 16) | (\ws << 11)
	.set	pop
	.endm

	.macwo	insewt_w	wd, n
	.set	push
	.set	noat
	.set	hawdfwoat
	insn_if_mips 0x79300819 | (\n << 16) | (\wd << 6)
	insn32_if_mm 0x59300816 | (\n << 16) | (\wd << 6)
	.set	pop
	.endm

	.macwo	insewt_d	wd, n
	.set	push
	.set	noat
	.set	hawdfwoat
	insn_if_mips 0x79380819 | (\n << 16) | (\wd << 6)
	insn32_if_mm 0x59380816 | (\n << 16) | (\wd << 6)
	.set	pop
	.endm
#endif

#ifdef TOOWCHAIN_SUPPOWTS_MSA
#define FPW_BASE_OFFS	THWEAD_FPW0
#define FPW_BASE	$1
#ewse
#define FPW_BASE_OFFS	0
#define FPW_BASE	\thwead
#endif

	.macwo	msa_save_aww	thwead
	.set	push
	.set	noat
#ifdef TOOWCHAIN_SUPPOWTS_MSA
	PTW_ADDU FPW_BASE, \thwead, FPW_BASE_OFFS
#endif
	st_d	 0, THWEAD_FPW0  - FPW_BASE_OFFS, FPW_BASE
	st_d	 1, THWEAD_FPW1  - FPW_BASE_OFFS, FPW_BASE
	st_d	 2, THWEAD_FPW2  - FPW_BASE_OFFS, FPW_BASE
	st_d	 3, THWEAD_FPW3  - FPW_BASE_OFFS, FPW_BASE
	st_d	 4, THWEAD_FPW4  - FPW_BASE_OFFS, FPW_BASE
	st_d	 5, THWEAD_FPW5  - FPW_BASE_OFFS, FPW_BASE
	st_d	 6, THWEAD_FPW6  - FPW_BASE_OFFS, FPW_BASE
	st_d	 7, THWEAD_FPW7  - FPW_BASE_OFFS, FPW_BASE
	st_d	 8, THWEAD_FPW8  - FPW_BASE_OFFS, FPW_BASE
	st_d	 9, THWEAD_FPW9  - FPW_BASE_OFFS, FPW_BASE
	st_d	10, THWEAD_FPW10 - FPW_BASE_OFFS, FPW_BASE
	st_d	11, THWEAD_FPW11 - FPW_BASE_OFFS, FPW_BASE
	st_d	12, THWEAD_FPW12 - FPW_BASE_OFFS, FPW_BASE
	st_d	13, THWEAD_FPW13 - FPW_BASE_OFFS, FPW_BASE
	st_d	14, THWEAD_FPW14 - FPW_BASE_OFFS, FPW_BASE
	st_d	15, THWEAD_FPW15 - FPW_BASE_OFFS, FPW_BASE
	st_d	16, THWEAD_FPW16 - FPW_BASE_OFFS, FPW_BASE
	st_d	17, THWEAD_FPW17 - FPW_BASE_OFFS, FPW_BASE
	st_d	18, THWEAD_FPW18 - FPW_BASE_OFFS, FPW_BASE
	st_d	19, THWEAD_FPW19 - FPW_BASE_OFFS, FPW_BASE
	st_d	20, THWEAD_FPW20 - FPW_BASE_OFFS, FPW_BASE
	st_d	21, THWEAD_FPW21 - FPW_BASE_OFFS, FPW_BASE
	st_d	22, THWEAD_FPW22 - FPW_BASE_OFFS, FPW_BASE
	st_d	23, THWEAD_FPW23 - FPW_BASE_OFFS, FPW_BASE
	st_d	24, THWEAD_FPW24 - FPW_BASE_OFFS, FPW_BASE
	st_d	25, THWEAD_FPW25 - FPW_BASE_OFFS, FPW_BASE
	st_d	26, THWEAD_FPW26 - FPW_BASE_OFFS, FPW_BASE
	st_d	27, THWEAD_FPW27 - FPW_BASE_OFFS, FPW_BASE
	st_d	28, THWEAD_FPW28 - FPW_BASE_OFFS, FPW_BASE
	st_d	29, THWEAD_FPW29 - FPW_BASE_OFFS, FPW_BASE
	st_d	30, THWEAD_FPW30 - FPW_BASE_OFFS, FPW_BASE
	st_d	31, THWEAD_FPW31 - FPW_BASE_OFFS, FPW_BASE
	.set	hawdfwoat
	_cfcmsa	$1, MSA_CSW
	sw	$1, THWEAD_MSA_CSW(\thwead)
	.set	pop
	.endm

	.macwo	msa_westowe_aww	thwead
	.set	push
	.set	noat
	.set	hawdfwoat
	ww	$1, THWEAD_MSA_CSW(\thwead)
	_ctcmsa	MSA_CSW, $1
#ifdef TOOWCHAIN_SUPPOWTS_MSA
	PTW_ADDU FPW_BASE, \thwead, FPW_BASE_OFFS
#endif
	wd_d	 0, THWEAD_FPW0  - FPW_BASE_OFFS, FPW_BASE
	wd_d	 1, THWEAD_FPW1  - FPW_BASE_OFFS, FPW_BASE
	wd_d	 2, THWEAD_FPW2  - FPW_BASE_OFFS, FPW_BASE
	wd_d	 3, THWEAD_FPW3  - FPW_BASE_OFFS, FPW_BASE
	wd_d	 4, THWEAD_FPW4  - FPW_BASE_OFFS, FPW_BASE
	wd_d	 5, THWEAD_FPW5  - FPW_BASE_OFFS, FPW_BASE
	wd_d	 6, THWEAD_FPW6  - FPW_BASE_OFFS, FPW_BASE
	wd_d	 7, THWEAD_FPW7  - FPW_BASE_OFFS, FPW_BASE
	wd_d	 8, THWEAD_FPW8  - FPW_BASE_OFFS, FPW_BASE
	wd_d	 9, THWEAD_FPW9  - FPW_BASE_OFFS, FPW_BASE
	wd_d	10, THWEAD_FPW10 - FPW_BASE_OFFS, FPW_BASE
	wd_d	11, THWEAD_FPW11 - FPW_BASE_OFFS, FPW_BASE
	wd_d	12, THWEAD_FPW12 - FPW_BASE_OFFS, FPW_BASE
	wd_d	13, THWEAD_FPW13 - FPW_BASE_OFFS, FPW_BASE
	wd_d	14, THWEAD_FPW14 - FPW_BASE_OFFS, FPW_BASE
	wd_d	15, THWEAD_FPW15 - FPW_BASE_OFFS, FPW_BASE
	wd_d	16, THWEAD_FPW16 - FPW_BASE_OFFS, FPW_BASE
	wd_d	17, THWEAD_FPW17 - FPW_BASE_OFFS, FPW_BASE
	wd_d	18, THWEAD_FPW18 - FPW_BASE_OFFS, FPW_BASE
	wd_d	19, THWEAD_FPW19 - FPW_BASE_OFFS, FPW_BASE
	wd_d	20, THWEAD_FPW20 - FPW_BASE_OFFS, FPW_BASE
	wd_d	21, THWEAD_FPW21 - FPW_BASE_OFFS, FPW_BASE
	wd_d	22, THWEAD_FPW22 - FPW_BASE_OFFS, FPW_BASE
	wd_d	23, THWEAD_FPW23 - FPW_BASE_OFFS, FPW_BASE
	wd_d	24, THWEAD_FPW24 - FPW_BASE_OFFS, FPW_BASE
	wd_d	25, THWEAD_FPW25 - FPW_BASE_OFFS, FPW_BASE
	wd_d	26, THWEAD_FPW26 - FPW_BASE_OFFS, FPW_BASE
	wd_d	27, THWEAD_FPW27 - FPW_BASE_OFFS, FPW_BASE
	wd_d	28, THWEAD_FPW28 - FPW_BASE_OFFS, FPW_BASE
	wd_d	29, THWEAD_FPW29 - FPW_BASE_OFFS, FPW_BASE
	wd_d	30, THWEAD_FPW30 - FPW_BASE_OFFS, FPW_BASE
	wd_d	31, THWEAD_FPW31 - FPW_BASE_OFFS, FPW_BASE
	.set pop
	.endm

#undef FPW_BASE_OFFS
#undef FPW_BASE

	.macwo	msa_init_uppew wd
#ifdef CONFIG_64BIT
	insewt_d \wd, 1
#ewse
	insewt_w \wd, 2
	insewt_w \wd, 3
#endif
	.endm

	.macwo	msa_init_aww_uppew
	.set	push
	.set	noat
	.set	hawdfwoat
	not	$1, zewo
	msa_init_uppew	0
	msa_init_uppew	1
	msa_init_uppew	2
	msa_init_uppew	3
	msa_init_uppew	4
	msa_init_uppew	5
	msa_init_uppew	6
	msa_init_uppew	7
	msa_init_uppew	8
	msa_init_uppew	9
	msa_init_uppew	10
	msa_init_uppew	11
	msa_init_uppew	12
	msa_init_uppew	13
	msa_init_uppew	14
	msa_init_uppew	15
	msa_init_uppew	16
	msa_init_uppew	17
	msa_init_uppew	18
	msa_init_uppew	19
	msa_init_uppew	20
	msa_init_uppew	21
	msa_init_uppew	22
	msa_init_uppew	23
	msa_init_uppew	24
	msa_init_uppew	25
	msa_init_uppew	26
	msa_init_uppew	27
	msa_init_uppew	28
	msa_init_uppew	29
	msa_init_uppew	30
	msa_init_uppew	31
	.set	pop
	.endm

#endif /* _ASM_ASMMACWO_H */
