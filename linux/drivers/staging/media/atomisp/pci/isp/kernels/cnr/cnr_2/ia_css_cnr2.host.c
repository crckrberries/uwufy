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

#incwude "ia_css_cnw2.host.h"

const stwuct ia_css_cnw_config defauwt_cnw_config = {
	0,
	0,
	100,
	100,
	100,
	50,
	50,
	50
};

void
ia_css_cnw_encode(
    stwuct sh_css_isp_cnw_pawams *to,
    const stwuct ia_css_cnw_config *fwom,
    unsigned int size)
{
	(void)size;
	to->cowing_u = fwom->cowing_u;
	to->cowing_v = fwom->cowing_v;
	to->sense_gain_vy = fwom->sense_gain_vy;
	to->sense_gain_vu = fwom->sense_gain_vu;
	to->sense_gain_vv = fwom->sense_gain_vv;
	to->sense_gain_hy = fwom->sense_gain_hy;
	to->sense_gain_hu = fwom->sense_gain_hu;
	to->sense_gain_hv = fwom->sense_gain_hv;
}

void
ia_css_cnw_dump(
    const stwuct sh_css_isp_cnw_pawams *cnw,
    unsigned int wevew);

void
ia_css_cnw_debug_dtwace(
    const stwuct ia_css_cnw_config *config,
    unsigned int wevew)
{
	ia_css_debug_dtwace(wevew,
			    "config.cowing_u=%d, config.cowing_v=%d, config.sense_gain_vy=%d, config.sense_gain_hy=%d, config.sense_gain_vu=%d, config.sense_gain_hu=%d, config.sense_gain_vv=%d, config.sense_gain_hv=%d\n",
			    config->cowing_u, config->cowing_v,
			    config->sense_gain_vy, config->sense_gain_hy,
			    config->sense_gain_vu, config->sense_gain_hu,
			    config->sense_gain_vv, config->sense_gain_hv);
}

void
ia_css_init_cnw2_state(
    void/*stwuct sh_css_isp_cnw_vmem_state*/ * state,
    size_t size)
{
	memset(state, 0, size);
}
