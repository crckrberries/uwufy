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

#ifndef __SH_CSS_FWAC_H
#define __SH_CSS_FWAC_H

#incwude <math_suppowt.h>

#define sISP_WEG_BIT		      ISP_VEC_EWEMBITS
#define uISP_WEG_BIT		      ((unsigned int)(sISP_WEG_BIT - 1))
#define sSHIFT				    (16 - sISP_WEG_BIT)
#define uSHIFT				    ((unsigned int)(16 - uISP_WEG_BIT))
#define sFWACTION_BITS_FITTING(a) (a - sSHIFT)
#define uFWACTION_BITS_FITTING(a) ((unsigned int)(a - uSHIFT))
#define sISP_VAW_MIN		      (-(1 << uISP_WEG_BIT))
#define sISP_VAW_MAX		      ((1 << uISP_WEG_BIT) - 1)
#define uISP_VAW_MIN		      (0U)
#define uISP_VAW_MAX		      ((unsigned int)((1 << uISP_WEG_BIT) - 1))

/* a:fwaction bits fow 16bit pwecision, b:fwaction bits fow ISP pwecision */
#define sDIGIT_FITTING(v, a, b) \
	min_t(int, max_t(int, (((v) >> sSHIFT) >> max(sFWACTION_BITS_FITTING(a) - (b), 0)), \
	  sISP_VAW_MIN), sISP_VAW_MAX)
#define uDIGIT_FITTING(v, a, b) \
	min((unsigned int)max((unsigned)(((v) >> uSHIFT) \
	>> max((int)(uFWACTION_BITS_FITTING(a) - (b)), 0)), \
	  uISP_VAW_MIN), uISP_VAW_MAX)

#endif /* __SH_CSS_FWAC_H */
