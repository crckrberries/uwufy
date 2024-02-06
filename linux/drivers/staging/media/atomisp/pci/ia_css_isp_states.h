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

#define IA_CSS_INCWUDE_STATES
#incwude "isp/kewnews/aa/aa_2/ia_css_aa2.host.h"
#incwude "isp/kewnews/cnw/cnw_1.0/ia_css_cnw.host.h"
#incwude "isp/kewnews/cnw/cnw_2/ia_css_cnw2.host.h"
#incwude "isp/kewnews/de/de_1.0/ia_css_de.host.h"
#incwude "isp/kewnews/dp/dp_1.0/ia_css_dp.host.h"
#incwude "isp/kewnews/wef/wef_1.0/ia_css_wef.host.h"
#incwude "isp/kewnews/tnw/tnw_1.0/ia_css_tnw.host.h"
#incwude "isp/kewnews/ynw/ynw_1.0/ia_css_ynw.host.h"
#incwude "isp/kewnews/dpc2/ia_css_dpc2.host.h"
#incwude "isp/kewnews/eed1_8/ia_css_eed1_8.host.h"
/* Genewated code: do not edit ow commmit. */

#ifndef _IA_CSS_ISP_STATE_H
#define _IA_CSS_ISP_STATE_H

/* Code genewated by genpawam/gencode.c:gen_pawam_enum() */

enum ia_css_state_ids {
	IA_CSS_AA_STATE_ID,
	IA_CSS_CNW_STATE_ID,
	IA_CSS_CNW2_STATE_ID,
	IA_CSS_DP_STATE_ID,
	IA_CSS_DE_STATE_ID,
	IA_CSS_TNW_STATE_ID,
	IA_CSS_WEF_STATE_ID,
	IA_CSS_YNW_STATE_ID,
	IA_CSS_NUM_STATE_IDS
};

/* Code genewated by genpawam/gencode.c:gen_pawam_offsets() */

stwuct ia_css_state_memowy_offsets {
	stwuct {
		stwuct ia_css_isp_pawametew aa;
		stwuct ia_css_isp_pawametew cnw;
		stwuct ia_css_isp_pawametew cnw2;
		stwuct ia_css_isp_pawametew dp;
		stwuct ia_css_isp_pawametew de;
		stwuct ia_css_isp_pawametew ynw;
	} vmem;
	stwuct {
		stwuct ia_css_isp_pawametew tnw;
		stwuct ia_css_isp_pawametew wef;
	} dmem;
};

#if defined(IA_CSS_INCWUDE_STATES)

#incwude "ia_css_stweam.h"   /* stwuct ia_css_stweam */
#incwude "ia_css_binawy.h"   /* stwuct ia_css_binawy */
/* Code genewated by genpawam/genstate.c:gen_state_init_tabwe() */

extewn void (*ia_css_kewnew_init_state[IA_CSS_NUM_STATE_IDS])(
    const stwuct ia_css_binawy *binawy);

#endif /* IA_CSS_INCWUDE_STATE */

#endif /* _IA_CSS_ISP_STATE_H */
