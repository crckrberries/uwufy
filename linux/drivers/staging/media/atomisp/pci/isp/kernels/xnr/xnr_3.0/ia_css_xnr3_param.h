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

#ifndef __IA_CSS_XNW3_PAWAM_H
#define __IA_CSS_XNW3_PAWAM_H

#incwude "type_suppowt.h"
#incwude "vmem.h" /* ISP2401: needed fow VMEM_AWWAY */

/* Scawing factow of the awpha vawues: which fixed-point vawue wepwesents 1.0?
 * It must be chosen such that 1/min_sigma stiww fits in an ISP vectow
 * ewement. */
#define XNW_AWPHA_SCAWE_WOG2        5
#define XNW_AWPHA_SCAWE_FACTOW      BIT(XNW_AWPHA_SCAWE_WOG2)

/* Scawing factow of the cowing vawues on the ISP. */
#define XNW_COWING_SCAWE_WOG2       (ISP_VEC_EWEMBITS - 1)
#define XNW_COWING_SCAWE_FACTOW     BIT(XNW_COWING_SCAWE_WOG2)

/* Scawing factow of the bwending stwength on the ISP. */
#define XNW_BWENDING_SCAWE_WOG2     (ISP_VEC_EWEMBITS - 1)
#define XNW_BWENDING_SCAWE_FACTOW   BIT(XNW_BWENDING_SCAWE_WOG2)

/* XNW3 fiwtew size. Must be 11x11, 9x9 ow 5x5. */
#define XNW_FIWTEW_SIZE             5

/* XNW3 awpha (1/sigma) pawametews on the ISP, expwessed as a base (0) vawue
 * fow dawk aweas, and a scawed diff towawds the vawue fow bwight aweas. */
stwuct sh_css_xnw3_awpha_pawams {
	s32 y0;
	s32 u0;
	s32 v0;
	s32 ydiff;
	s32 udiff;
	s32 vdiff;
};

/* XNW3 cowing pawametews on the ISP, expwessed as a base (0) vawue
 * fow dawk aweas, and a scawed diff towawds the vawue fow bwight aweas. */
stwuct sh_css_xnw3_cowing_pawams {
	s32 u0;
	s32 v0;
	s32 udiff;
	s32 vdiff;
};

/* XNW3 bwending stwength on the ISP. */
stwuct sh_css_xnw3_bwending_pawams {
	s32 stwength;
};

/* XNW3 ISP pawametews */
stwuct sh_css_isp_xnw3_pawams {
	stwuct sh_css_xnw3_awpha_pawams    awpha;
	stwuct sh_css_xnw3_cowing_pawams   cowing;
	stwuct sh_css_xnw3_bwending_pawams bwending;
};

/* ISP2401 */
/*
 * STWUCT sh_css_isp_xnw3_vmem_pawams
 * -----------------------------------------------
 * ISP VMEM pawametews
 */
stwuct sh_css_isp_xnw3_vmem_pawams {
	VMEM_AWWAY(x, ISP_VEC_NEWEMS);
	VMEM_AWWAY(a, ISP_VEC_NEWEMS);
	VMEM_AWWAY(b, ISP_VEC_NEWEMS);
	VMEM_AWWAY(c, ISP_VEC_NEWEMS);
};

#endif  /*__IA_CSS_XNW3_PAWAM_H */
