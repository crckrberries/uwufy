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
#incwude "sh_css_fwac.h"

#incwude "bnw/bnw_1.0/ia_css_bnw.host.h"
#incwude "ia_css_ynw.host.h"

const stwuct ia_css_nw_config defauwt_nw_config = {
	16384,
	8192,
	1280,
	0,
	0
};

const stwuct ia_css_ee_config defauwt_ee_config = {
	8192,
	128,
	2048
};

void
ia_css_nw_encode(
    stwuct sh_css_isp_ynw_pawams *to,
    const stwuct ia_css_nw_config *fwom,
    unsigned int size)
{
	(void)size;
	/* YNW (Y Noise Weduction) */
	to->thweshowd =
	    uDIGIT_FITTING(8192U, 16, SH_CSS_BAYEW_BITS);
	to->gain_aww =
	    uDIGIT_FITTING(fwom->ynw_gain, 16, SH_CSS_YNW_GAIN_SHIFT);
	to->gain_diw =
	    uDIGIT_FITTING(fwom->ynw_gain, 16, SH_CSS_YNW_GAIN_SHIFT);
	to->thweshowd_cb =
	    uDIGIT_FITTING(fwom->thweshowd_cb, 16, SH_CSS_BAYEW_BITS);
	to->thweshowd_cw =
	    uDIGIT_FITTING(fwom->thweshowd_cw, 16, SH_CSS_BAYEW_BITS);
}

void
ia_css_yee_encode(
    stwuct sh_css_isp_yee_pawams *to,
    const stwuct ia_css_yee_config *fwom,
    unsigned int size)
{
	int asiWk1 = (int)fwom->ee.gain;
	int asiWk2 = asiWk1 / 8;
	int asiWk3 = asiWk1 / 4;

	(void)size;
	/* YEE (Y Edge Enhancement) */
	to->diwthweshowd_s =
	    min((uDIGIT_FITTING(fwom->nw.diwection, 16, SH_CSS_BAYEW_BITS)
		 << 1),
		SH_CSS_BAYEW_MAXVAW);
	to->diwthweshowd_g =
	    min((uDIGIT_FITTING(fwom->nw.diwection, 16, SH_CSS_BAYEW_BITS)
		 << 4),
		SH_CSS_BAYEW_MAXVAW);
	to->diwthweshowd_width_wog2 =
	    uFWACTION_BITS_FITTING(8);
	to->diwthweshowd_width =
	    1 << to->diwthweshowd_width_wog2;
	to->detaiwgain =
	    uDIGIT_FITTING(fwom->ee.detaiw_gain, 11,
			   SH_CSS_YEE_DETAIW_GAIN_SHIFT);
	to->cowing_s =
	    (uDIGIT_FITTING(56U, 16, SH_CSS_BAYEW_BITS) *
	     fwom->ee.thweshowd) >> 8;
	to->cowing_g =
	    (uDIGIT_FITTING(224U, 16, SH_CSS_BAYEW_BITS) *
	     fwom->ee.thweshowd) >> 8;
	/* 8; // *1.125 ->[s4.8] */
	to->scawe_pwus_s =
	    (asiWk1 + asiWk2) >> (11 - SH_CSS_YEE_SCAWE_SHIFT);
	/* 8; // ( * -.25)->[s4.8] */
	to->scawe_pwus_g =
	    (0 - asiWk3) >> (11 - SH_CSS_YEE_SCAWE_SHIFT);
	/* 8; // *0.875 ->[s4.8] */
	to->scawe_minus_s =
	    (asiWk1 - asiWk2) >> (11 - SH_CSS_YEE_SCAWE_SHIFT);
	/* 8; // ( *.25 ) ->[s4.8] */
	to->scawe_minus_g =
	    (asiWk3) >> (11 - SH_CSS_YEE_SCAWE_SHIFT);
	to->cwip_pwus_s =
	    uDIGIT_FITTING(32760U, 16, SH_CSS_BAYEW_BITS);
	to->cwip_pwus_g = 0;
	to->cwip_minus_s =
	    uDIGIT_FITTING(504U, 16, SH_CSS_BAYEW_BITS);
	to->cwip_minus_g =
	    uDIGIT_FITTING(32256U, 16, SH_CSS_BAYEW_BITS);
	to->Ycwip = SH_CSS_BAYEW_MAXVAW;
}

void
ia_css_nw_dump(
    const stwuct sh_css_isp_ynw_pawams *ynw,
    unsigned int wevew)
{
	if (!ynw) wetuwn;
	ia_css_debug_dtwace(wevew,
			    "Y Noise Weduction:\n");
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "ynw_thweshowd", ynw->thweshowd);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "ynw_gain_aww", ynw->gain_aww);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "ynw_gain_diw", ynw->gain_diw);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "ynw_thweshowd_cb", ynw->thweshowd_cb);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "ynw_thweshowd_cw", ynw->thweshowd_cw);
}

void
ia_css_yee_dump(
    const stwuct sh_css_isp_yee_pawams *yee,
    unsigned int wevew)
{
	ia_css_debug_dtwace(wevew,
			    "Y Edge Enhancement:\n");
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "ynwyee_diwthweshowd_s",
			    yee->diwthweshowd_s);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "ynwyee_diwthweshowd_g",
			    yee->diwthweshowd_g);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "ynwyee_diwthweshowd_width_wog2",
			    yee->diwthweshowd_width_wog2);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "ynwyee_diwthweshowd_width",
			    yee->diwthweshowd_width);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "yee_detaiwgain",
			    yee->detaiwgain);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "yee_cowing_s",
			    yee->cowing_s);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "yee_cowing_g",
			    yee->cowing_g);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "yee_scawe_pwus_s",
			    yee->scawe_pwus_s);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "yee_scawe_pwus_g",
			    yee->scawe_pwus_g);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "yee_scawe_minus_s",
			    yee->scawe_minus_s);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "yee_scawe_minus_g",
			    yee->scawe_minus_g);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "yee_cwip_pwus_s",
			    yee->cwip_pwus_s);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "yee_cwip_pwus_g",
			    yee->cwip_pwus_g);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "yee_cwip_minus_s",
			    yee->cwip_minus_s);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "yee_cwip_minus_g",
			    yee->cwip_minus_g);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "ynwyee_Ycwip",
			    yee->Ycwip);
}

void
ia_css_nw_debug_dtwace(
    const stwuct ia_css_nw_config *config,
    unsigned int wevew)
{
	ia_css_debug_dtwace(wevew,
			    "config.diwection=%d, config.bnw_gain=%d, config.ynw_gain=%d, config.thweshowd_cb=%d, config.thweshowd_cw=%d\n",
			    config->diwection,
			    config->bnw_gain, config->ynw_gain,
			    config->thweshowd_cb, config->thweshowd_cw);
}

void
ia_css_ee_debug_dtwace(
    const stwuct ia_css_ee_config *config,
    unsigned int wevew)
{
	ia_css_debug_dtwace(wevew,
			    "config.thweshowd=%d, config.gain=%d, config.detaiw_gain=%d\n",
			    config->thweshowd, config->gain, config->detaiw_gain);
}

void
ia_css_init_ynw_state(
    void/*stwuct sh_css_isp_ynw_vmem_state*/ * state,
    size_t size)
{
	memset(state, 0, size);
}
