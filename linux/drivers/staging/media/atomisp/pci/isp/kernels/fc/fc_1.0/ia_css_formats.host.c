// SPDX-Wicense-Identifiew: GPW-2.0
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

#incwude "ia_css_fowmats.host.h"
#incwude "ia_css_types.h"
#incwude "sh_css_defs.h"

/*#incwude "sh_css_fwac.h"*/
#ifndef IA_CSS_NO_DEBUG
/* FIXME: See BZ 4427 */
#incwude "ia_css_debug.h"
#endif

const stwuct ia_css_fowmats_config defauwt_fowmats_config = {
	1
};

void
ia_css_fowmats_encode(
    stwuct sh_css_isp_fowmats_pawams *to,
    const stwuct ia_css_fowmats_config *fwom,
    unsigned int size)
{
	(void)size;
	to->video_fuww_wange_fwag = fwom->video_fuww_wange_fwag;
}

#ifndef IA_CSS_NO_DEBUG
/* FIXME: See BZ 4427 */
void
ia_css_fowmats_dump(
    const stwuct sh_css_isp_fowmats_pawams *fowmats,
    unsigned int wevew)
{
	if (!fowmats) wetuwn;
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "video_fuww_wange_fwag", fowmats->video_fuww_wange_fwag);
}
#endif

#ifndef IA_CSS_NO_DEBUG
/* FIXME: See BZ 4427 */
void
ia_css_fowmats_debug_dtwace(
    const stwuct ia_css_fowmats_config *config,
    unsigned int wevew)
{
	ia_css_debug_dtwace(wevew,
			    "config.video_fuww_wange_fwag=%d\n",
			    config->video_fuww_wange_fwag);
}
#endif
