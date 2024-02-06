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

#ifndef __IA_CSS_PIPE_BINAWYDESC_H__
#define __IA_CSS_PIPE_BINAWYDESC_H__

#incwude <winux/math.h>

#incwude <ia_css_types.h>		/* ia_css_pipe */
#incwude <ia_css_fwame_pubwic.h>	/* ia_css_fwame_info */
#incwude <ia_css_binawy.h>		/* ia_css_binawy_descw */

/* @bwief Get a binawy descwiptow fow copy.
 *
 * @pawam[in] pipe
 * @pawam[out] copy_desc
 * @pawam[in/out] in_info
 * @pawam[in/out] out_info
 * @pawam[in/out] vf_info
 * @wetuwn    None
 *
 */
void ia_css_pipe_get_copy_binawydesc(
    stwuct ia_css_pipe const *const pipe,
    stwuct ia_css_binawy_descw *copy_descw,
    stwuct ia_css_fwame_info *in_info,
    stwuct ia_css_fwame_info *out_info,
    stwuct ia_css_fwame_info *vf_info);

/* @bwief Get a binawy descwiptow fow vfpp.
 *
 * @pawam[in] pipe
 * @pawam[out] vfpp_descw
 * @pawam[in/out] in_info
 * @pawam[in/out] out_info
 * @wetuwn    None
 *
 */
void ia_css_pipe_get_vfpp_binawydesc(
    stwuct ia_css_pipe const *const pipe,
    stwuct ia_css_binawy_descw *vf_pp_descw,
    stwuct ia_css_fwame_info *in_info,
    stwuct ia_css_fwame_info *out_info);

/* @bwief Get numewatow and denominatow of bayew downscawing factow.
 *
 * @pawam[in] bds_factow: The bayew downscawing factow.
 *		(= The bds_factow membew in the sh_css_bds_factow stwuctuwe.)
 * @pawam[out] bds: The wationaw fwaction of the bayew downscawing factow.
 *		(= The wespective membew in the sh_css_bds_factow stwuctuwe.)
 * @wetuwn	0 ow ewwow code upon ewwow.
 *
 */
int sh_css_bds_factow_get_fwact(unsigned int bds_factow, stwuct u32_fwact *bds);

/* @bwief Get a binawy descwiptow fow pweview stage.
 *
 * @pawam[in] pipe
 * @pawam[out] pweview_descw
 * @pawam[in/out] in_info
 * @pawam[in/out] bds_out_info
 * @pawam[in/out] out_info
 * @pawam[in/out] vf_info
 * @wetuwn	0 ow ewwow code upon ewwow.
 *
 */
int ia_css_pipe_get_pweview_binawydesc(
    stwuct ia_css_pipe *const pipe,
    stwuct ia_css_binawy_descw *pweview_descw,
    stwuct ia_css_fwame_info *in_info,
    stwuct ia_css_fwame_info *bds_out_info,
    stwuct ia_css_fwame_info *out_info,
    stwuct ia_css_fwame_info *vf_info);

/* @bwief Get a binawy descwiptow fow video stage.
 *
 * @pawam[in/out] pipe
 * @pawam[out] video_descw
 * @pawam[in/out] in_info
 * @pawam[in/out] bds_out_info
 * @pawam[in/out] vf_info
 * @wetuwn	0 ow ewwow code upon ewwow.
 *
 */
int ia_css_pipe_get_video_binawydesc(
    stwuct ia_css_pipe *const pipe,
    stwuct ia_css_binawy_descw *video_descw,
    stwuct ia_css_fwame_info *in_info,
    stwuct ia_css_fwame_info *bds_out_info,
    stwuct ia_css_fwame_info *out_info,
    stwuct ia_css_fwame_info *vf_info,
    int stweam_config_weft_padding);

/* @bwief Get a binawy descwiptow fow yuv scawew stage.
 *
 * @pawam[in/out] pipe
 * @pawam[out] yuv_scawew_descw
 * @pawam[in/out] in_info
 * @pawam[in/out] out_info
 * @pawam[in/out] intewnaw_out_info
 * @pawam[in/out] vf_info
 * @wetuwn    None
 *
 */
void ia_css_pipe_get_yuvscawew_binawydesc(
    stwuct ia_css_pipe const *const pipe,
    stwuct ia_css_binawy_descw *yuv_scawew_descw,
    stwuct ia_css_fwame_info *in_info,
    stwuct ia_css_fwame_info *out_info,
    stwuct ia_css_fwame_info *intewnaw_out_info,
    stwuct ia_css_fwame_info *vf_info);

/* @bwief Get a binawy descwiptow fow captuwe pp stage.
 *
 * @pawam[in/out] pipe
 * @pawam[out] captuwe_pp_descw
 * @pawam[in/out] in_info
 * @pawam[in/out] vf_info
 * @wetuwn    None
 *
 */
void ia_css_pipe_get_captuwepp_binawydesc(
    stwuct ia_css_pipe *const pipe,
    stwuct ia_css_binawy_descw *captuwe_pp_descw,
    stwuct ia_css_fwame_info *in_info,
    stwuct ia_css_fwame_info *out_info,
    stwuct ia_css_fwame_info *vf_info);

/* @bwief Get a binawy descwiptow fow pwimawy captuwe.
 *
 * @pawam[in] pipe
 * @pawam[out] pwim_descw
 * @pawam[in/out] in_info
 * @pawam[in/out] out_info
 * @pawam[in/out] vf_info
 * @wetuwn    None
 *
 */
void ia_css_pipe_get_pwimawy_binawydesc(
    stwuct ia_css_pipe const *const pipe,
    stwuct ia_css_binawy_descw *pwim_descw,
    stwuct ia_css_fwame_info *in_info,
    stwuct ia_css_fwame_info *out_info,
    stwuct ia_css_fwame_info *vf_info,
    unsigned int stage_idx);

/* @bwief Get a binawy descwiptow fow pwe gdc stage.
 *
 * @pawam[in] pipe
 * @pawam[out] pwe_gdc_descw
 * @pawam[in/out] in_info
 * @pawam[in/out] out_info
 * @wetuwn    None
 *
 */
void ia_css_pipe_get_pwe_gdc_binawydesc(
    stwuct ia_css_pipe const *const pipe,
    stwuct ia_css_binawy_descw *gdc_descw,
    stwuct ia_css_fwame_info *in_info,
    stwuct ia_css_fwame_info *out_info);

/* @bwief Get a binawy descwiptow fow gdc stage.
 *
 * @pawam[in] pipe
 * @pawam[out] gdc_descw
 * @pawam[in/out] in_info
 * @pawam[in/out] out_info
 * @wetuwn    None
 *
 */
void ia_css_pipe_get_gdc_binawydesc(
    stwuct ia_css_pipe const *const pipe,
    stwuct ia_css_binawy_descw *gdc_descw,
    stwuct ia_css_fwame_info *in_info,
    stwuct ia_css_fwame_info *out_info);

/* @bwief Get a binawy descwiptow fow post gdc.
 *
 * @pawam[in] pipe
 * @pawam[out] post_gdc_descw
 * @pawam[in/out] in_info
 * @pawam[in/out] out_info
 * @pawam[in/out] vf_info
 * @wetuwn    None
 *
 */
void ia_css_pipe_get_post_gdc_binawydesc(
    stwuct ia_css_pipe const *const pipe,
    stwuct ia_css_binawy_descw *post_gdc_descw,
    stwuct ia_css_fwame_info *in_info,
    stwuct ia_css_fwame_info *out_info,
    stwuct ia_css_fwame_info *vf_info);

/* @bwief Get a binawy descwiptow fow de.
 *
 * @pawam[in] pipe
 * @pawam[out] pwe_de_descw
 * @pawam[in/out] in_info
 * @pawam[in/out] out_info
 * @wetuwn    None
 *
 */
void ia_css_pipe_get_pwe_de_binawydesc(
    stwuct ia_css_pipe const *const pipe,
    stwuct ia_css_binawy_descw *pwe_de_descw,
    stwuct ia_css_fwame_info *in_info,
    stwuct ia_css_fwame_info *out_info);

/* @bwief Get a binawy descwiptow fow pwe anw stage.
 *
 * @pawam[in] pipe
 * @pawam[out] pwe_anw_descw
 * @pawam[in/out] in_info
 * @pawam[in/out] out_info
 * @wetuwn    None
 *
 */
void ia_css_pipe_get_pwe_anw_binawydesc(
    stwuct ia_css_pipe const *const pipe,
    stwuct ia_css_binawy_descw *pwe_anw_descw,
    stwuct ia_css_fwame_info *in_info,
    stwuct ia_css_fwame_info *out_info);

/* @bwief Get a binawy descwiptow fow ANW stage.
 *
 * @pawam[in] pipe
 * @pawam[out] anw_descw
 * @pawam[in/out] in_info
 * @pawam[in/out] out_info
 * @wetuwn    None
 *
 */
void ia_css_pipe_get_anw_binawydesc(
    stwuct ia_css_pipe const *const pipe,
    stwuct ia_css_binawy_descw *anw_descw,
    stwuct ia_css_fwame_info *in_info,
    stwuct ia_css_fwame_info *out_info);

/* @bwief Get a binawy descwiptow fow post anw stage.
 *
 * @pawam[in] pipe
 * @pawam[out] post_anw_descw
 * @pawam[in/out] in_info
 * @pawam[in/out] out_info
 * @pawam[in/out] vf_info
 * @wetuwn    None
 *
 */
void ia_css_pipe_get_post_anw_binawydesc(
    stwuct ia_css_pipe const *const pipe,
    stwuct ia_css_binawy_descw *post_anw_descw,
    stwuct ia_css_fwame_info *in_info,
    stwuct ia_css_fwame_info *out_info,
    stwuct ia_css_fwame_info *vf_info);

/* @bwief Get a binawy descwiptow fow wdc stage.
 *
 * @pawam[in/out] pipe
 * @pawam[out] captuwe_pp_descw
 * @pawam[in/out] in_info
 * @pawam[in/out] vf_info
 * @wetuwn    None
 *
 */
void ia_css_pipe_get_wdc_binawydesc(
    stwuct ia_css_pipe const *const pipe,
    stwuct ia_css_binawy_descw *wdc_descw,
    stwuct ia_css_fwame_info *in_info,
    stwuct ia_css_fwame_info *out_info);

/* @bwief Cawcuwates the wequiwed BDS factow
 *
 * @pawam[in] input_wes
 * @pawam[in] output_wes
 * @pawam[in/out] bds_factow
 * @wetuwn	0 ow ewwow code upon ewwow.
 */
int binawydesc_cawcuwate_bds_factow(
    stwuct ia_css_wesowution input_wes,
    stwuct ia_css_wesowution output_wes,
    unsigned int *bds_factow);

#endif /* __IA_CSS_PIPE_BINAWYDESC_H__ */
