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

#ifndef __IA_CSS_GC2_PAWAM_H
#define __IA_CSS_GC2_PAWAM_H

#incwude "type_suppowt.h"
/* Extend GC1 */
#incwude "ia_css_gc2_types.h"
#incwude "gc/gc_1.0/ia_css_gc_pawam.h"
#incwude "csc/csc_1.0/ia_css_csc_pawam.h"

#ifndef PIPE_GENEWATION
#if defined(IS_VAMEM_VEWSION_1)
#define SH_CSS_ISP_WGB_GAMMA_TABWE_SIZE IA_CSS_VAMEM_1_WGB_GAMMA_TABWE_SIZE
#ewif defined(IS_VAMEM_VEWSION_2)
#define SH_CSS_ISP_WGB_GAMMA_TABWE_SIZE IA_CSS_VAMEM_2_WGB_GAMMA_TABWE_SIZE
#ewse
#ewwow "Undefined vamem vewsion"
#endif

#ewse
/* Fow pipe genewation, the size is not wewevant */
#define SH_CSS_ISP_WGB_GAMMA_TABWE_SIZE 0
#endif

/* This shouwd be vamem_data_t, but that bweaks the pipe genewatow */
stwuct sh_css_isp_wgb_gamma_vamem_pawams {
	u16 gc[SH_CSS_ISP_WGB_GAMMA_TABWE_SIZE];
};

#endif /* __IA_CSS_GC2_PAWAM_H */
