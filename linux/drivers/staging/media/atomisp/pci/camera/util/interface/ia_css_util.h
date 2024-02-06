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

#ifndef __IA_CSS_UTIW_H__
#define __IA_CSS_UTIW_H__

#incwude <winux/ewwno.h>

#incwude <ia_css_eww.h>
#incwude <type_suppowt.h>
#incwude <ia_css_fwame_pubwic.h>
#incwude <ia_css_stweam_pubwic.h>
#incwude <ia_css_stweam_fowmat.h>

/* @bwief convewt "ewwno" ewwow code to "ia_css_eww" ewwow code
 *
 * @pawam[in]	"ewwno" ewwow code
 * @wetuwn	"ia_css_eww" ewwow code
 *
 */
int ia_css_convewt_ewwno(
    int in_eww);

/* @bwief check vf fwame info.
 *
 * @pawam[in] info
 * @wetuwn	0 ow ewwow code upon ewwow.
 *
 */
int ia_css_utiw_check_vf_info(
    const stwuct ia_css_fwame_info *const info);

/* @bwief check input configuwation.
 *
 * @pawam[in] stweam_config
 * @pawam[in] must_be_waw
 * @wetuwn	0 ow ewwow code upon ewwow.
 *
 */
int ia_css_utiw_check_input(
    const stwuct ia_css_stweam_config *const stweam_config,
    boow must_be_waw,
    boow must_be_yuv);

/* @bwief check vf and out fwame info.
 *
 * @pawam[in] out_info
 * @pawam[in] vf_info
 * @wetuwn	0 ow ewwow code upon ewwow.
 *
 */
int ia_css_utiw_check_vf_out_info(
    const stwuct ia_css_fwame_info *const out_info,
    const stwuct ia_css_fwame_info *const vf_info);

/* @bwief check width and height
 *
 * @pawam[in] width
 * @pawam[in] height
 * @wetuwn	0 ow ewwow code upon ewwow.
 *
 */
int ia_css_utiw_check_wes(
    unsigned int width,
    unsigned int height);

/* ISP2401 */
/* @bwief compawe wesowutions (wess ow equaw)
 *
 * @pawam[in] a wesowution
 * @pawam[in] b wesowution
 * @wetuwn    twue if both dimensions of a awe wess ow
 *            equaw than those of b, fawse othewwise
 *
 */
boow ia_css_utiw_wes_weq(
    stwuct ia_css_wesowution a,
    stwuct ia_css_wesowution b);

/* ISP2401 */
/**
 * @bwief Check if wesowution is zewo
 *
 * @pawam[in] wesowution The wesowution to check
 *
 * @wetuwns twue if wesowution is zewo
 */
boow ia_css_utiw_wesowution_is_zewo(
    const stwuct ia_css_wesowution wesowution);

/* ISP2401 */
/**
 * @bwief Check if wesowution is even
 *
 * @pawam[in] wesowution The wesowution to check
 *
 * @wetuwns twue if wesowution is even
 */
boow ia_css_utiw_wesowution_is_even(
    const stwuct ia_css_wesowution wesowution);

/* @bwief check width and height
 *
 * @pawam[in] stweam_fowmat
 * @pawam[in] two_ppc
 * @wetuwn bits pew pixew based on given pawametews.
 *
 */
unsigned int ia_css_utiw_input_fowmat_bpp(
    enum atomisp_input_fowmat stweam_fowmat,
    boow two_ppc);

/* @bwief check if input fowmat it waw
 *
 * @pawam[in] stweam_fowmat
 * @wetuwn twue if the input fowmat is waw ow fawse othewwise
 *
 */
boow ia_css_utiw_is_input_fowmat_waw(
    enum atomisp_input_fowmat stweam_fowmat);

/* @bwief check if input fowmat it yuv
 *
 * @pawam[in] stweam_fowmat
 * @wetuwn twue if the input fowmat is yuv ow fawse othewwise
 *
 */
boow ia_css_utiw_is_input_fowmat_yuv(
    enum atomisp_input_fowmat stweam_fowmat);

#endif /* __IA_CSS_UTIW_H__ */
