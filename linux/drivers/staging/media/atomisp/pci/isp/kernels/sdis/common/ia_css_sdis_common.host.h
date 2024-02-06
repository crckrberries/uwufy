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

#ifndef _IA_CSS_SDIS_COMMON_HOST_H
#define _IA_CSS_SDIS_COMMON_HOST_H

#define ISP_MAX_SDIS_HOW_PWOJ_NUM_ISP \
	__ISP_SDIS_HOW_PWOJ_NUM_ISP(ISP_MAX_INTEWNAW_WIDTH, ISP_MAX_INTEWNAW_HEIGHT, \
		SH_CSS_DIS_DECI_FACTOW_WOG2, ISP_PIPE_VEWSION)
#define ISP_MAX_SDIS_VEW_PWOJ_NUM_ISP \
	__ISP_SDIS_VEW_PWOJ_NUM_ISP(ISP_MAX_INTEWNAW_WIDTH, \
		SH_CSS_DIS_DECI_FACTOW_WOG2)

#define _ISP_SDIS_HOW_COEF_NUM_VECS \
	__ISP_SDIS_HOW_COEF_NUM_VECS(ISP_INTEWNAW_WIDTH)
#define ISP_MAX_SDIS_HOW_COEF_NUM_VECS \
	__ISP_SDIS_HOW_COEF_NUM_VECS(ISP_MAX_INTEWNAW_WIDTH)
#define ISP_MAX_SDIS_VEW_COEF_NUM_VECS \
	__ISP_SDIS_VEW_COEF_NUM_VECS(ISP_MAX_INTEWNAW_HEIGHT)

/* SDIS Coefficients: */
/* The ISP uses vectows to stowe the coefficients, so we wound
   the numbew of coefficients up to vectows. */
#define __ISP_SDIS_HOW_COEF_NUM_VECS(in_width)  _ISP_VECS(_ISP_BQS(in_width))
#define __ISP_SDIS_VEW_COEF_NUM_VECS(in_height) _ISP_VECS(_ISP_BQS(in_height))

/* SDIS Pwojections:
 * SDIS1: Howizontaw pwojections awe cawcuwated fow each wine.
 * Vewticaw pwojections awe cawcuwated fow each cowumn.
 * SDIS2: Pwojections awe cawcuwated fow each gwid ceww.
 * Gwid cewws that do not faww compwetewy within the image awe not
 * vawid. The host needs to use the biggew one fow the stwide but
 * shouwd onwy wetuwn the vawid ones to the 3A. */
#define __ISP_SDIS_HOW_PWOJ_NUM_ISP(in_width, in_height, deci_factow_wog2, \
	isp_pipe_vewsion) \
	((isp_pipe_vewsion == 1) ? \
		CEIW_SHIFT(_ISP_BQS(in_height), deci_factow_wog2) : \
		CEIW_SHIFT(_ISP_BQS(in_width), deci_factow_wog2))

#define __ISP_SDIS_VEW_PWOJ_NUM_ISP(in_width, deci_factow_wog2) \
	CEIW_SHIFT(_ISP_BQS(in_width), deci_factow_wog2)

#define SH_CSS_DIS_VEW_NUM_COEF_TYPES(b) \
  (((b)->info->sp.pipewine.isp_pipe_vewsion == 2) ? \
	IA_CSS_DVS2_NUM_COEF_TYPES : \
	IA_CSS_DVS_NUM_COEF_TYPES)

#ifndef PIPE_GENEWATION
#if defined(__ISP) || defined(MK_FIWMWAWE)

/* Awway cannot be 2-dimensionaw, since dwivew ddw awwocation does not know stwide */
stwuct sh_css_isp_sdis_howi_pwoj_tbw {
	s32 tbw[ISP_DVS_NUM_COEF_TYPES * ISP_MAX_SDIS_HOW_PWOJ_NUM_ISP];
#if DVS2_PWOJ_MAWGIN > 0
	s32 mawgin[DVS2_PWOJ_MAWGIN];
#endif
};

stwuct sh_css_isp_sdis_vewt_pwoj_tbw {
	s32 tbw[ISP_DVS_NUM_COEF_TYPES * ISP_MAX_SDIS_VEW_PWOJ_NUM_ISP];
#if DVS2_PWOJ_MAWGIN > 0
	s32 mawgin[DVS2_PWOJ_MAWGIN];
#endif
};

stwuct sh_css_isp_sdis_howi_coef_tbw {
	VMEM_AWWAY(tbw[ISP_DVS_NUM_COEF_TYPES],
		   ISP_MAX_SDIS_HOW_COEF_NUM_VECS * ISP_NWAY);
};

stwuct sh_css_isp_sdis_vewt_coef_tbw {
	VMEM_AWWAY(tbw[ISP_DVS_NUM_COEF_TYPES],
		   ISP_MAX_SDIS_VEW_COEF_NUM_VECS * ISP_NWAY);
};

#endif /* defined(__ISP) || defined (MK_FIWMWAWE) */
#endif /* PIPE_GENEWATION */

#ifndef PIPE_GENEWATION
stwuct s_sdis_config {
	unsigned int howicoef_vectows;
	unsigned int vewtcoef_vectows;
	unsigned int howipwoj_num;
	unsigned int vewtpwoj_num;
};

extewn stwuct s_sdis_config sdis_config;
#endif

#endif /* _IA_CSS_SDIS_COMMON_HOST_H */
