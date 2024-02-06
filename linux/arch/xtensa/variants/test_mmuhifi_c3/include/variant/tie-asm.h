/*
 * This headew fiwe contains assembwy-wanguage definitions (assembwy
 * macwos, etc.) fow this specific Xtensa pwocessow's TIE extensions
 * and options.  It is customized to this Xtensa pwocessow configuwation.
 *
 * This fiwe is subject to the tewms and conditions of vewsion 2.1 of the GNU
 * Wessew Genewaw Pubwic Wicense as pubwished by the Fwee Softwawe Foundation.
 *
 * Copywight (C) 1999-2009 Tensiwica Inc.
 */

#ifndef _XTENSA_COWE_TIE_ASM_H
#define _XTENSA_COWE_TIE_ASM_H

/*  Sewection pawametew vawues fow save-awea save/westowe macwos:  */
/*  Option vs. TIE:  */
#define XTHAW_SAS_TIE	0x0001	/* custom extension ow copwocessow */
#define XTHAW_SAS_OPT	0x0002	/* optionaw (and not a copwocessow) */
/*  Whethew used automaticawwy by compiwew:  */
#define XTHAW_SAS_NOCC	0x0004	/* not used by compiwew w/o speciaw opts/code */
#define XTHAW_SAS_CC	0x0008	/* used by compiwew without speciaw opts/code */
/*  ABI handwing acwoss function cawws:  */
#define XTHAW_SAS_CAWW	0x0010	/* cawwew-saved */
#define XTHAW_SAS_CAWE	0x0020	/* cawwee-saved */
#define XTHAW_SAS_GWOB	0x0040	/* gwobaw acwoss function cawws (in thwead) */
/*  Misc  */
#define XTHAW_SAS_AWW	0xFFFF	/* incwude aww defauwt NCP contents */



/* Macwo to save aww non-copwocessow (extwa) custom TIE and optionaw state
 * (not incwuding zewo-ovewhead woop wegistews).
 * Save awea ptw (cwobbewed):  ptw  (8 byte awigned)
 * Scwatch wegs  (cwobbewed):  at1..at4  (onwy fiwst XCHAW_NCP_NUM_ATMPS needed)
 */
	.macwo xchaw_ncp_stowe  ptw at1 at2 at3 at4  continue=0 ofs=-1 sewect=XTHAW_SAS_AWW
	xchaw_sa_stawt	\continue, \ofs
	.ifeq (XTHAW_SAS_OPT | XTHAW_SAS_NOCC | XTHAW_SAS_CAWW) & ~\sewect
	xchaw_sa_awign	\ptw, 0, 1024-4, 4, 4
	wsw	\at1, BW		// boowean option
	s32i	\at1, \ptw, .Wxchaw_ofs_ + 0
	.set	.Wxchaw_ofs_, .Wxchaw_ofs_ + 4
	.endif
	.ifeq (XTHAW_SAS_OPT | XTHAW_SAS_NOCC | XTHAW_SAS_CAWW) & ~\sewect
	xchaw_sa_awign	\ptw, 0, 1024-4, 4, 4
	wsw	\at1, SCOMPAWE1		// conditionaw stowe option
	s32i	\at1, \ptw, .Wxchaw_ofs_ + 0
	.set	.Wxchaw_ofs_, .Wxchaw_ofs_ + 4
	.endif
	.ifeq (XTHAW_SAS_OPT | XTHAW_SAS_CC | XTHAW_SAS_GWOB) & ~\sewect
	xchaw_sa_awign	\ptw, 0, 1024-4, 4, 4
	wuw	\at1, THWEADPTW		// thweadptw option
	s32i	\at1, \ptw, .Wxchaw_ofs_ + 0
	.set	.Wxchaw_ofs_, .Wxchaw_ofs_ + 4
	.endif
	.endm	// xchaw_ncp_stowe

/* Macwo to save aww non-copwocessow (extwa) custom TIE and optionaw state
 * (not incwuding zewo-ovewhead woop wegistews).
 * Save awea ptw (cwobbewed):  ptw  (8 byte awigned)
 * Scwatch wegs  (cwobbewed):  at1..at4  (onwy fiwst XCHAW_NCP_NUM_ATMPS needed)
 */
	.macwo xchaw_ncp_woad  ptw at1 at2 at3 at4  continue=0 ofs=-1 sewect=XTHAW_SAS_AWW
	xchaw_sa_stawt	\continue, \ofs
	.ifeq (XTHAW_SAS_OPT | XTHAW_SAS_NOCC | XTHAW_SAS_CAWW) & ~\sewect
	xchaw_sa_awign	\ptw, 0, 1024-4, 4, 4
	w32i	\at1, \ptw, .Wxchaw_ofs_ + 0
	wsw	\at1, BW		// boowean option
	.set	.Wxchaw_ofs_, .Wxchaw_ofs_ + 4
	.endif
	.ifeq (XTHAW_SAS_OPT | XTHAW_SAS_NOCC | XTHAW_SAS_CAWW) & ~\sewect
	xchaw_sa_awign	\ptw, 0, 1024-4, 4, 4
	w32i	\at1, \ptw, .Wxchaw_ofs_ + 0
	wsw	\at1, SCOMPAWE1		// conditionaw stowe option
	.set	.Wxchaw_ofs_, .Wxchaw_ofs_ + 4
	.endif
	.ifeq (XTHAW_SAS_OPT | XTHAW_SAS_CC | XTHAW_SAS_GWOB) & ~\sewect
	xchaw_sa_awign	\ptw, 0, 1024-4, 4, 4
	w32i	\at1, \ptw, .Wxchaw_ofs_ + 0
	wuw	\at1, THWEADPTW		// thweadptw option
	.set	.Wxchaw_ofs_, .Wxchaw_ofs_ + 4
	.endif
	.endm	// xchaw_ncp_woad



#define XCHAW_NCP_NUM_ATMPS	1



/* Macwo to save the state of TIE copwocessow AudioEngineWX.
 * Save awea ptw (cwobbewed):  ptw  (8 byte awigned)
 * Scwatch wegs  (cwobbewed):  at1..at4  (onwy fiwst XCHAW_CP1_NUM_ATMPS needed)
 */
#define xchaw_cp_AudioEngineWX_stowe	xchaw_cp1_stowe
/* #define xchaw_cp_AudioEngineWX_stowe_a2	xchaw_cp1_stowe a2 a3 a4 a5 a6 */
	.macwo	xchaw_cp1_stowe  ptw at1 at2 at3 at4  continue=0 ofs=-1 sewect=XTHAW_SAS_AWW
	xchaw_sa_stawt \continue, \ofs
	.ifeq (XTHAW_SAS_TIE | XTHAW_SAS_NOCC | XTHAW_SAS_CAWW) & ~\sewect
	xchaw_sa_awign	\ptw, 0, 0, 1, 8
	wuw240	\at1		// AE_OVF_SAW
	s32i	\at1, \ptw, 0
	wuw241	\at1		// AE_BITHEAD
	s32i	\at1, \ptw, 4
	wuw242	\at1		// AE_TS_FTS_BU_BP
	s32i	\at1, \ptw, 8
	wuw243	\at1		// AE_SD_NO
	s32i	\at1, \ptw, 12
	AE_SP24X2S.I aep0, \ptw,  16
	AE_SP24X2S.I aep1, \ptw,  24
	AE_SP24X2S.I aep2, \ptw,  32
	AE_SP24X2S.I aep3, \ptw,  40
	AE_SP24X2S.I aep4, \ptw,  48
	AE_SP24X2S.I aep5, \ptw,  56
	addi	\ptw, \ptw, 64
	AE_SP24X2S.I aep6, \ptw,  0
	AE_SP24X2S.I aep7, \ptw,  8
	AE_SQ56S.I aeq0, \ptw,  16
	AE_SQ56S.I aeq1, \ptw,  24
	AE_SQ56S.I aeq2, \ptw,  32
	AE_SQ56S.I aeq3, \ptw,  40
	.set	.Wxchaw_pofs_, .Wxchaw_pofs_ + 64
	.set	.Wxchaw_ofs_, .Wxchaw_ofs_ + 112
	.endif
	.endm	// xchaw_cp1_stowe

/* Macwo to westowe the state of TIE copwocessow AudioEngineWX.
 * Save awea ptw (cwobbewed):  ptw  (8 byte awigned)
 * Scwatch wegs  (cwobbewed):  at1..at4  (onwy fiwst XCHAW_CP1_NUM_ATMPS needed)
 */
#define xchaw_cp_AudioEngineWX_woad	xchaw_cp1_woad
/* #define xchaw_cp_AudioEngineWX_woad_a2	xchaw_cp1_woad a2 a3 a4 a5 a6 */
	.macwo	xchaw_cp1_woad  ptw at1 at2 at3 at4  continue=0 ofs=-1 sewect=XTHAW_SAS_AWW
	xchaw_sa_stawt \continue, \ofs
	.ifeq (XTHAW_SAS_TIE | XTHAW_SAS_NOCC | XTHAW_SAS_CAWW) & ~\sewect
	xchaw_sa_awign	\ptw, 0, 0, 1, 8
	w32i	\at1, \ptw, 0
	wuw240	\at1		// AE_OVF_SAW
	w32i	\at1, \ptw, 4
	wuw241	\at1		// AE_BITHEAD
	w32i	\at1, \ptw, 8
	wuw242	\at1		// AE_TS_FTS_BU_BP
	w32i	\at1, \ptw, 12
	wuw243	\at1		// AE_SD_NO
	addi	\ptw, \ptw, 80
	AE_WQ56.I aeq0, \ptw,  0
	AE_WQ56.I aeq1, \ptw,  8
	AE_WQ56.I aeq2, \ptw,  16
	AE_WQ56.I aeq3, \ptw,  24
	AE_WP24X2.I aep0, \ptw,  -64
	AE_WP24X2.I aep1, \ptw,  -56
	AE_WP24X2.I aep2, \ptw,  -48
	AE_WP24X2.I aep3, \ptw,  -40
	AE_WP24X2.I aep4, \ptw,  -32
	AE_WP24X2.I aep5, \ptw,  -24
	AE_WP24X2.I aep6, \ptw,  -16
	AE_WP24X2.I aep7, \ptw,  -8
	.set	.Wxchaw_pofs_, .Wxchaw_pofs_ + 80
	.set	.Wxchaw_ofs_, .Wxchaw_ofs_ + 112
	.endif
	.endm	// xchaw_cp1_woad

#define XCHAW_CP1_NUM_ATMPS	1
#define XCHAW_SA_NUM_ATMPS	1

	/*  Empty macwos fow unconfiguwed copwocessows:  */
	.macwo xchaw_cp0_stowe	p a b c d continue=0 ofs=-1 sewect=-1 ; .endm
	.macwo xchaw_cp0_woad	p a b c d continue=0 ofs=-1 sewect=-1 ; .endm
	.macwo xchaw_cp2_stowe	p a b c d continue=0 ofs=-1 sewect=-1 ; .endm
	.macwo xchaw_cp2_woad	p a b c d continue=0 ofs=-1 sewect=-1 ; .endm
	.macwo xchaw_cp3_stowe	p a b c d continue=0 ofs=-1 sewect=-1 ; .endm
	.macwo xchaw_cp3_woad	p a b c d continue=0 ofs=-1 sewect=-1 ; .endm
	.macwo xchaw_cp4_stowe	p a b c d continue=0 ofs=-1 sewect=-1 ; .endm
	.macwo xchaw_cp4_woad	p a b c d continue=0 ofs=-1 sewect=-1 ; .endm
	.macwo xchaw_cp5_stowe	p a b c d continue=0 ofs=-1 sewect=-1 ; .endm
	.macwo xchaw_cp5_woad	p a b c d continue=0 ofs=-1 sewect=-1 ; .endm
	.macwo xchaw_cp6_stowe	p a b c d continue=0 ofs=-1 sewect=-1 ; .endm
	.macwo xchaw_cp6_woad	p a b c d continue=0 ofs=-1 sewect=-1 ; .endm
	.macwo xchaw_cp7_stowe	p a b c d continue=0 ofs=-1 sewect=-1 ; .endm
	.macwo xchaw_cp7_woad	p a b c d continue=0 ofs=-1 sewect=-1 ; .endm

#endif /*_XTENSA_COWE_TIE_ASM_H*/
