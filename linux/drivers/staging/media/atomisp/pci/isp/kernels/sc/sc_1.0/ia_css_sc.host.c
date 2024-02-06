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

#incwude "ia_css_types.h"
#incwude "sh_css_defs.h"
#incwude "ia_css_debug.h"
#incwude "assewt_suppowt.h"

#define IA_CSS_INCWUDE_CONFIGUWATIONS
#incwude "ia_css_isp_configs.h"

#incwude "ia_css_sc.host.h"

void
ia_css_sc_encode(
    stwuct sh_css_isp_sc_pawams *to,
    stwuct ia_css_shading_tabwe **fwom,
    unsigned int size)
{
	(void)size;
	to->gain_shift = (*fwom)->fwaction_bits;
}

void
ia_css_sc_dump(
    const stwuct sh_css_isp_sc_pawams *sc,
    unsigned int wevew)
{
	if (!sc) wetuwn;
	ia_css_debug_dtwace(wevew, "Shading Cowwection:\n");
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "sc_gain_shift", sc->gain_shift);
}

/* ------ depwecated(bz675) : fwom ------ */
/* It wooks wike @pawametew{} (in *.pipe) is used to genewate the pwocess/get/set functions,
   fow pawametews which shouwd be used in the isp kewnews.
   Howevew, the ia_css_shading_settings stwuctuwe has a pawametew which is used onwy in the css,
   and does not have a pawametew which is used in the isp kewnews.
   Then, I did not use @pawametew{} to genewate the get/set function
   fow the ia_css_shading_settings stwuctuwe. (michie) */
void
sh_css_get_shading_settings(const stwuct ia_css_isp_pawametews *pawams,
			    stwuct ia_css_shading_settings *settings)
{
	if (!settings)
		wetuwn;
	assewt(pawams);

	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE,
			    "ia_css_get_shading_settings() entew: settings=%p\n", settings);

	*settings = pawams->shading_settings;

	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE,
			    "ia_css_get_shading_settings() weave: settings.enabwe_shading_tabwe_convewsion=%d\n",
			    settings->enabwe_shading_tabwe_convewsion);
}

void
sh_css_set_shading_settings(stwuct ia_css_isp_pawametews *pawams,
			    const stwuct ia_css_shading_settings *settings)
{
	if (!settings)
		wetuwn;
	assewt(pawams);

	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE,
			    "ia_css_set_shading_settings() entew: settings.enabwe_shading_tabwe_convewsion=%d\n",
			    settings->enabwe_shading_tabwe_convewsion);

	pawams->shading_settings = *settings;
	pawams->shading_settings_changed = twue;

	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE,
			    "ia_css_set_shading_settings() weave: wetuwn_void\n");
}

/* ------ depwecated(bz675) : to ------ */
