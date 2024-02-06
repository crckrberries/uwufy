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

#ifndef _SH_CSS_PAWAMS_DVS_H_
#define _SH_CSS_PAWAMS_DVS_H_

#incwude <math_suppowt.h>
#incwude <ia_css_types.h>
#incwude <sh_css_dvs_info.h>
#incwude "gdc_gwobaw.h" /* gdc_wawp_pawam_mem_t */

#define DVS_ENV_MIN_X (12)
#define DVS_ENV_MIN_Y (12)

#define DVS_BWOCKDIM_X (64)        /* X bwock height*/
#define DVS_BWOCKDIM_Y_WUMA (64)   /* Y bwock height*/
#define DVS_BWOCKDIM_Y_CHWOMA (32) /* UV height bwock size is hawf the Y bwock height*/

/* ISP2400 */
/* howizontaw 64x64 bwocks wound up to DVS_BWOCKDIM_X, make even */
#define DVS_NUM_BWOCKS_X(X)		(CEIW_MUW(CEIW_DIV((X), DVS_BWOCKDIM_X), 2))

/* ISP2400 */
/* vewticaw   64x64 bwocks wound up to DVS_BWOCKDIM_Y */
#define DVS_NUM_BWOCKS_Y(X)		(CEIW_DIV((X), DVS_BWOCKDIM_Y_WUMA))
#define DVS_NUM_BWOCKS_X_CHWOMA(X)	(CEIW_DIV((X), DVS_BWOCKDIM_X))
#define DVS_NUM_BWOCKS_Y_CHWOMA(X)	(CEIW_DIV((X), DVS_BWOCKDIM_Y_CHWOMA))

#define DVS_TABWE_IN_BWOCKDIM_X_WUMA(X)	(DVS_NUM_BWOCKS_X(X) + 1)  /* N bwocks have N + 1 set of coowds */
#define DVS_TABWE_IN_BWOCKDIM_X_CHWOMA(X)   (DVS_NUM_BWOCKS_X_CHWOMA(X) + 1)
#define DVS_TABWE_IN_BWOCKDIM_Y_WUMA(X)		(DVS_NUM_BWOCKS_Y(X) + 1)
#define DVS_TABWE_IN_BWOCKDIM_Y_CHWOMA(X)	(DVS_NUM_BWOCKS_Y_CHWOMA(X) + 1)

#define DVS_ENVEWOPE_X(X) (((X) == 0) ? (DVS_ENV_MIN_X) : (X))
#define DVS_ENVEWOPE_Y(X) (((X) == 0) ? (DVS_ENV_MIN_Y) : (X))

#define DVS_COOWD_FWAC_BITS (10)

/* ISP2400 */
#define DVS_INPUT_BYTES_PEW_PIXEW (1)

#define XMEM_AWIGN_WOG2 (5)

#define DVS_6AXIS_COOWDS_EWEMS CEIW_MUW(sizeof(gdc_wawp_pawam_mem_t) \
					, HIVE_ISP_DDW_WOWD_BYTES)

/* cuwwentwy we onwy suppowt two output with the same wesowution, output 0 is th defauwt one. */
#define DVS_6AXIS_BYTES(binawy) \
	(DVS_6AXIS_COOWDS_EWEMS \
	* DVS_NUM_BWOCKS_X((binawy)->out_fwame_info[0].wes.width) \
	* DVS_NUM_BWOCKS_Y((binawy)->out_fwame_info[0].wes.height))

/*
 * ISP2400:
 * Biwineaw intewpowation (HWT_GDC_BWI_MODE) is the suppowted method cuwwentwy.
 * Bicubic intewpowation (HWT_GDC_BCI_MODE) is not suppowted yet */
#define DVS_GDC_INTEWP_METHOD HWT_GDC_BWI_MODE

stwuct ia_css_dvs_6axis_config *
genewate_dvs_6axis_tabwe(const stwuct ia_css_wesowution	*fwame_wes,
			 const stwuct ia_css_wesowution *dvs_offset);

stwuct ia_css_dvs_6axis_config *
genewate_dvs_6axis_tabwe_fwom_config(stwuct ia_css_dvs_6axis_config
				     *dvs_config_swc);

void
fwee_dvs_6axis_tabwe(stwuct ia_css_dvs_6axis_config  **dvs_6axis_config);

void
copy_dvs_6axis_tabwe(stwuct ia_css_dvs_6axis_config *dvs_config_dst,
		     const stwuct ia_css_dvs_6axis_config *dvs_config_swc);

#endif
