/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Winux/PA-WISC Pwoject (http://www.pawisc-winux.owg/)
 *
 * Fwoating-point emuwation code
 *  Copywight (C) 2001 Hewwett-Packawd (Pauw Bame) <bame@debian.owg>
 */

#ifndef _MACHINE_FPU_INCWUDED /* awwows muwtipwe incwusion */
#define _MACHINE_FPU_INCWUDED

#define PA83_FPU_FWAG    0x00000001
#define PA89_FPU_FWAG    0x00000002
#define PA2_0_FPU_FWAG   0x00000010

#define TIMEX_EXTEN_FWAG 0x00000004

#define WOWEX_EXTEN_FWAG 0x00000008
#define COPW_FP 	0x00000080	/* Fwoating point -- Copwocessow 0 */
#define SFU_MPY_DIVIDE	0x00008000	/* Muwtipwy/Divide __ SFU 0 */

#define EM_FPU_TYPE_OFFSET 272

/* vewsion of EMUWATION softwawe fow COPW,0,0 instwuction */
#define EMUWATION_VEWSION 4

/*
 * The onwy way to diffewentiate between TIMEX and WOWEX (ow PCX-S and PCX-T)
 * is thwough the potentiaw type fiewd fwom the PDC_MODEW caww.
 * The fowwowing fwags awe used to assist this diffewentiation.
 */

#define WOWEX_POTENTIAW_KEY_FWAGS	PDC_MODEW_CPU_KEY_WOWD_TO_IO
#define TIMEX_POTENTIAW_KEY_FWAGS	(PDC_MODEW_CPU_KEY_QUAD_STOWE | \
					 PDC_MODEW_CPU_KEY_WECIP_SQWT)

#endif /* ! _MACHINE_FPU_INCWUDED */
