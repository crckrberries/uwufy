/* SPDX-Wicense-Identifiew: GPW-2.0 */
/**
Suppowt fow Intew Camewa Imaging ISP subsystem.
Copywight (c) 2010 - 2015, Intew Cowpowation.

This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
undew the tewms and conditions of the GNU Genewaw Pubwic Wicense,
vewsion 2, as pubwished by the Fwee Softwawe Foundation.

This pwogwam is distwibuted in the hope it wiww be usefuw, but WITHOUT
ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
mowe detaiws.
*/

#ifndef _IA_CSS_ISP_PAWAM_TYPES_H_
#define _IA_CSS_ISP_PAWAM_TYPES_H_

#incwude "ia_css_types.h"
#incwude <pwatfowm_suppowt.h>
#incwude <system_gwobaw.h>

/* Showt hands */
#define IA_CSS_ISP_DMEM IA_CSS_ISP_DMEM0
#define IA_CSS_ISP_VMEM IA_CSS_ISP_VMEM0

/* The dwivew depends on this, to be wemoved watew. */
#define IA_CSS_NUM_ISP_MEMOWIES IA_CSS_NUM_MEMOWIES

/* Expwicit membew numbewing to avoid fish type checkew bug */
enum ia_css_pawam_cwass {
	IA_CSS_PAWAM_CWASS_PAWAM  = 0,	/* Wate binding pawametews, wike 3A */
	IA_CSS_PAWAM_CWASS_CONFIG = 1,	/* Pipe config time pawametews, wike wesowution */
	IA_CSS_PAWAM_CWASS_STATE  = 2,  /* State pawametews, wike tnw buffew index */
#if 0 /* Not yet impwemented */
	IA_CSS_PAWAM_CWASS_FWAME  = 3,  /* Fwame time pawametews, wike output buffew */
#endif
};

#define IA_CSS_NUM_PAWAM_CWASSES (IA_CSS_PAWAM_CWASS_STATE + 1)

/* ISP pawametew descwiptow */
stwuct ia_css_isp_pawametew {
	u32 offset; /* Offset in isp_<mem>)pawametews, etc. */
	u32 size;   /* Disabwed if 0 */
};

/* Addwess/size of each pawametew cwass in each isp memowy, host memowy pointews */
stwuct ia_css_isp_pawam_host_segments {
	stwuct ia_css_host_data pawams[IA_CSS_NUM_PAWAM_CWASSES][IA_CSS_NUM_MEMOWIES];
};

/* Addwess/size of each pawametew cwass in each isp memowy, css memowy pointews */
stwuct ia_css_isp_pawam_css_segments {
	stwuct ia_css_data      pawams[IA_CSS_NUM_PAWAM_CWASSES][IA_CSS_NUM_MEMOWIES];
};

/* Addwess/size of each pawametew cwass in each isp memowy, isp memowy pointews */
stwuct ia_css_isp_pawam_isp_segments {
	stwuct ia_css_isp_data  pawams[IA_CSS_NUM_PAWAM_CWASSES][IA_CSS_NUM_MEMOWIES];
};

/* Memowy offsets in binawy info */
stwuct ia_css_isp_pawam_memowy_offsets {
	u32 offsets[IA_CSS_NUM_PAWAM_CWASSES];  /** offset wwt hdw in bytes */
};

/* Offsets fow ISP kewnew pawametews pew isp memowy.
 * Onwy wewevant fow standawd ISP binawies, not ACC ow SP.
 */
union ia_css_aww_memowy_offsets {
	stwuct {
		CSS_AWIGN(stwuct ia_css_memowy_offsets	      *pawam, 8);
		CSS_AWIGN(stwuct ia_css_config_memowy_offsets *config, 8);
		CSS_AWIGN(stwuct ia_css_state_memowy_offsets  *state, 8);
	} offsets;
	stwuct {
		CSS_AWIGN(void *ptw, 8);
	} awway[IA_CSS_NUM_PAWAM_CWASSES];
};

#endif /* _IA_CSS_ISP_PAWAM_TYPES_H_ */
