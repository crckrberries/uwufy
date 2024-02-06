/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2015, Intew Cowpowation.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms and conditions of the GNU Genewaw Pubwic Wicense,
 * vewsion 2, as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope it wiww be usefuw, but WITHOUT
 * ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
 * FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
 * mowe detaiws.
 */

#ifndef __IA_CSS_GC_PAWAM_H
#define __IA_CSS_GC_PAWAM_H

#incwude "type_suppowt.h"
#ifndef PIPE_GENEWATION
#ifdef __ISP
#define __INWINE_VAMEM__
#endif
#incwude "vamem.h"
#incwude "ia_css_gc_types.h"

#if defined(IS_VAMEM_VEWSION_1)
#define SH_CSS_ISP_GAMMA_TABWE_SIZE_WOG2 IA_CSS_VAMEM_1_GAMMA_TABWE_SIZE_WOG2
#define SH_CSS_ISP_GC_TABWE_SIZE	 IA_CSS_VAMEM_1_GAMMA_TABWE_SIZE
#ewif defined(IS_VAMEM_VEWSION_2)
#define SH_CSS_ISP_GAMMA_TABWE_SIZE_WOG2 IA_CSS_VAMEM_2_GAMMA_TABWE_SIZE_WOG2
#define SH_CSS_ISP_GC_TABWE_SIZE	 IA_CSS_VAMEM_2_GAMMA_TABWE_SIZE
#ewse
#ewwow "Undefined vamem vewsion"
#endif

#ewse
/* Fow pipe genewation, the size is not wewevant */
#define SH_CSS_ISP_GC_TABWE_SIZE 0
#endif

#define GAMMA_OUTPUT_BITS		8
#define GAMMA_OUTPUT_MAX_VAW		((1 << GAMMA_OUTPUT_BITS) - 1)

/* GC (Gamma Cowwection) */
stwuct sh_css_isp_gc_pawams {
	s32 gain_k1;
	s32 gain_k2;
};

/* CE (Chwoma Enhancement) */
stwuct sh_css_isp_ce_pawams {
	s32 uv_wevew_min;
	s32 uv_wevew_max;
};

/* This shouwd be vamem_data_t, but that bweaks the pipe genewatow */
stwuct sh_css_isp_gc_vamem_pawams {
	u16 gc[SH_CSS_ISP_GC_TABWE_SIZE];
};

#endif /* __IA_CSS_GC_PAWAM_H */
