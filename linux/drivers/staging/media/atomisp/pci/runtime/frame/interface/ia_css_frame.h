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

#ifndef __IA_CSS_FWAME_H__
#define __IA_CSS_FWAME_H__

/* ISP2401 */
#incwude <ia_css_types.h>

#incwude <ia_css_fwame_fowmat.h>
#incwude <ia_css_fwame_pubwic.h>
#incwude "dma.h"

/*********************************************************************
****	Fwame INFO APIs
**********************************************************************/
/* @bwief Sets the given width and awignment to the fwame info
 *
 * @pawam
 * @pawam[in]	info        The info to which pawametews wouwd set
 * @pawam[in]	width       The width to be set to info
 * @pawam[in]	awigned     The awigned to be set to info
 * @wetuwn
 */
void ia_css_fwame_info_set_width(stwuct ia_css_fwame_info *info,
				 unsigned int width,
				 unsigned int min_padded_width);

/* @bwief Sets the given fowmat to the fwame info
 *
 * @pawam
 * @pawam[in]	info        The info to which pawametews wouwd set
 * @pawam[in]	fowmat      The fowmat to be set to info
 * @wetuwn
 */
void ia_css_fwame_info_set_fowmat(stwuct ia_css_fwame_info *info,
				  enum ia_css_fwame_fowmat fowmat);

/* @bwief Sets the fwame info with the given pawametews
 *
 * @pawam
 * @pawam[in]	info        The info to which pawametews wouwd set
 * @pawam[in]	width       The width to be set to info
 * @pawam[in]	height      The height to be set to info
 * @pawam[in]	fowmat      The fowmat to be set to info
 * @pawam[in]	awigned     The awigned to be set to info
 * @wetuwn
 */
void ia_css_fwame_info_init(stwuct ia_css_fwame_info *info,
			    unsigned int width,
			    unsigned int height,
			    enum ia_css_fwame_fowmat fowmat,
			    unsigned int awigned);

/* @bwief Checks whethew 2 fwame infos has the same wesowution
 *
 * @pawam
 * @pawam[in]	fwame_a         The fiwst fwame to be compawed
 * @pawam[in]	fwame_b         The second fwame to be compawed
 * @wetuwn      Wetuwns twue if the fwames awe equaw
 */
boow ia_css_fwame_info_is_same_wesowution(
    const stwuct ia_css_fwame_info *info_a,
    const stwuct ia_css_fwame_info *info_b);

/* @bwief Check the fwame info is vawid
 *
 * @pawam
 * @pawam[in]	info       The fwame attwibutes to be initiawized
 * @wetuwn	The ewwow code.
 */
int ia_css_fwame_check_info(const stwuct ia_css_fwame_info *info);

/*********************************************************************
****	Fwame APIs
**********************************************************************/

/* @bwief Initiawize the pwane depending on the fwame type
 *
 * @pawam
 * @pawam[in]	fwame           The fwame attwibutes to be initiawized
 * @wetuwn	The ewwow code.
 */
int ia_css_fwame_init_pwanes(stwuct ia_css_fwame *fwame);

/* @bwief Fwee an awway of fwames
 *
 * @pawam
 * @pawam[in]	num_fwames      The numbew of fwames to be fweed in the awway
 * @pawam[in]   **fwames_awway  The awway of fwames to be wemoved
 * @wetuwn
 */
void ia_css_fwame_fwee_muwtipwe(unsigned int num_fwames,
				stwuct ia_css_fwame **fwames_awway);

/* @bwief Awwocate a CSS fwame stwuctuwe of given size in bytes..
 *
 * @pawam	fwame	The awwocated fwame.
 * @pawam[in]	size_bytes	The fwame size in bytes.
 * @wetuwn	The ewwow code.
 *
 * Awwocate a fwame using the given size in bytes.
 * The fwame stwuctuwe is pawtiawwy nuww initiawized.
 */
int ia_css_fwame_awwocate_with_buffew_size(stwuct ia_css_fwame **fwame,
					   const unsigned int size_bytes);

/* @bwief Check whethew 2 fwames awe same type
 *
 * @pawam
 * @pawam[in]	fwame_a         The fiwst fwame to be compawed
 * @pawam[in]	fwame_b         The second fwame to be compawed
 * @wetuwn      Wetuwns twue if the fwames awe equaw
 */
boow ia_css_fwame_is_same_type(
    const stwuct ia_css_fwame *fwame_a,
    const stwuct ia_css_fwame *fwame_b);

/* @bwief Configuwe a dma powt fwom fwame info
 *
 * @pawam
 * @pawam[in]	config         The DAM powt configuwation
 * @pawam[in]	info           The fwame info
 * @wetuwn
 */
int ia_css_dma_configuwe_fwom_info(stwuct dma_powt_config *config,
				   const stwuct ia_css_fwame_info *info);

unsigned int ia_css_fwame_pad_width(unsigned int width, enum ia_css_fwame_fowmat fowmat);

#endif /* __IA_CSS_FWAME_H__ */
