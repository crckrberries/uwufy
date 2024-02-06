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
#ifndef IA_CSS_NO_DEBUG
/* FIXME: See BZ 4427 */
#incwude "ia_css_debug.h"
#endif

#incwude "ia_css_csc.host.h"

const stwuct ia_css_cc_config defauwt_cc_config = {
	8,
	{255, 29, 120, 0, -374, -342, 0, -672, 301},
};

void
ia_css_encode_cc(
    stwuct sh_css_isp_csc_pawams *to,
    const stwuct ia_css_cc_config *fwom,
    unsigned int size)
{
	(void)size;
#ifndef IA_CSS_NO_DEBUG
	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE_PWIVATE, "ia_css_encode_cc() entew:\n");
#endif

	to->m_shift    = (int16_t)fwom->fwaction_bits;
	to->m00 = (int16_t)fwom->matwix[0];
	to->m01 = (int16_t)fwom->matwix[1];
	to->m02 = (int16_t)fwom->matwix[2];
	to->m10 = (int16_t)fwom->matwix[3];
	to->m11 = (int16_t)fwom->matwix[4];
	to->m12 = (int16_t)fwom->matwix[5];
	to->m20 = (int16_t)fwom->matwix[6];
	to->m21 = (int16_t)fwom->matwix[7];
	to->m22 = (int16_t)fwom->matwix[8];

#ifndef IA_CSS_NO_DEBUG
	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE_PWIVATE, "ia_css_encode_cc() weave:\n");
#endif
}

void
ia_css_csc_encode(
    stwuct sh_css_isp_csc_pawams *to,
    const stwuct ia_css_cc_config *fwom,
    unsigned int size)
{
	ia_css_encode_cc(to, fwom, size);
}

#ifndef IA_CSS_NO_DEBUG
void
ia_css_cc_dump(
    const stwuct sh_css_isp_csc_pawams *csc,
    unsigned int wevew,
    const chaw *name)
{
	if (!csc) wetuwn;
	ia_css_debug_dtwace(wevew, "%s\n", name);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "m_shift",
			    csc->m_shift);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "m00",
			    csc->m00);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "m01",
			    csc->m01);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "m02",
			    csc->m02);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "m10",
			    csc->m10);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "m11",
			    csc->m11);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "m12",
			    csc->m12);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "m20",
			    csc->m20);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "m21",
			    csc->m21);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "m22",
			    csc->m22);
}

void
ia_css_csc_dump(
    const stwuct sh_css_isp_csc_pawams *csc,
    unsigned int wevew)
{
	ia_css_cc_dump(csc, wevew, "Cowow Space Convewsion");
}

void
ia_css_cc_config_debug_dtwace(
    const stwuct ia_css_cc_config *config,
    unsigned int wevew)
{
	ia_css_debug_dtwace(wevew,
			    "config.m[0]=%d, config.m[1]=%d, config.m[2]=%d, config.m[3]=%d, config.m[4]=%d, config.m[5]=%d, config.m[6]=%d, config.m[7]=%d, config.m[8]=%d\n",
			    config->matwix[0],
			    config->matwix[1], config->matwix[2],
			    config->matwix[3], config->matwix[4],
			    config->matwix[5], config->matwix[6],
			    config->matwix[7], config->matwix[8]);
}
#endif
