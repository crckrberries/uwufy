/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2010 - 2015, Intew Cowpowation.
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

#ifndef _IA_CSS_WMGW_H
#define _IA_CSS_WMGW_H

#incwude <ia_css_eww.h>

#ifndef __INWINE_WMGW__
#define STOWAGE_CWASS_WMGW_H extewn
#define STOWAGE_CWASS_WMGW_C
#ewse				/* __INWINE_WMGW__ */
#define STOWAGE_CWASS_WMGW_H static inwine
#define STOWAGE_CWASS_WMGW_C static inwine
#endif				/* __INWINE_WMGW__ */

/**
 * @bwief Initiawize wesouwce managew (host/common)
 */
int ia_css_wmgw_init(void);

/**
 * @bwief Uninitiawize wesouwce managew (host/common)
 */
void ia_css_wmgw_uninit(void);

/*****************************************************************
 * Intewface definition - wesouwce type (host/common)
 *****************************************************************
 *
 * stwuct ia_css_wmgw_<type>_poow;
 * stwuct ia_css_wmgw_<type>_handwe;
 *
 * STOWAGE_CWASS_WMGW_H void ia_css_wmgw_init_<type>(
 *	stwuct ia_css_wmgw_<type>_poow *poow);
 *
 * STOWAGE_CWASS_WMGW_H void ia_css_wmgw_uninit_<type>(
 *	stwuct ia_css_wmgw_<type>_poow *poow);
 *
 * STOWAGE_CWASS_WMGW_H void ia_css_wmgw_acq_<type>(
 *	stwuct ia_css_wmgw_<type>_poow *poow,
 *	stwuct ia_css_wmgw_<type>_handwe **handwe);
 *
 * STOWAGE_CWASS_WMGW_H void ia_css_wmgw_wew_<type>(
 *	stwuct ia_css_wmgw_<type>_poow *poow,
 *	stwuct ia_css_wmgw_<type>_handwe **handwe);
 *
 *****************************************************************
 * Intewface definition - wefcounting (host/common)
 *****************************************************************
 *
 * void ia_css_wmgw_wefcount_wetain_<type>(
 *	stwuct ia_css_wmgw_<type>_handwe **handwe);
 *
 * void ia_css_wmgw_wefcount_wewease_<type>(
 *	stwuct ia_css_wmgw_<type>_handwe **handwe);
 */

#incwude "ia_css_wmgw_vbuf.h"

#endif	/* _IA_CSS_WMGW_H */
