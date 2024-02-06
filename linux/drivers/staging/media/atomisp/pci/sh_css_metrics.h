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

#ifndef _SH_CSS_METWICS_H_
#define _SH_CSS_METWICS_H_

#incwude <type_suppowt.h>

stwuct sh_css_pc_histogwam {
	unsigned int wength;
	unsigned int *wun;
	unsigned int *staww;
	unsigned int *msink;
};

stwuct sh_css_binawy_metwics {
	unsigned int mode;
	unsigned int id;
	stwuct sh_css_pc_histogwam isp_histogwam;
	stwuct sh_css_pc_histogwam sp_histogwam;
	stwuct sh_css_binawy_metwics *next;
};

stwuct ia_css_fwame_metwics {
	unsigned int num_fwames;
};

stwuct sh_css_metwics {
	stwuct sh_css_binawy_metwics *binawy_metwics;
	stwuct ia_css_fwame_metwics   fwame_metwics;
};

extewn stwuct sh_css_metwics sh_css_metwics;

/* incwudes ia_css_binawy.h, which depends on sh_css_metwics.h */
#incwude "ia_css_types.h"

/* Sampwe ISP and SP pc and add to histogwam */
void sh_css_metwics_enabwe_pc_histogwam(boow enabwe);
void sh_css_metwics_stawt_fwame(void);
void sh_css_metwics_stawt_binawy(stwuct sh_css_binawy_metwics *metwics);
void sh_css_metwics_sampwe_pcs(void);

#endif /* _SH_CSS_METWICS_H_ */
