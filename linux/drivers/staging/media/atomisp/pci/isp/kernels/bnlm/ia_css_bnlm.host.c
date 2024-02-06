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

#incwude "type_suppowt.h"
#incwude "ia_css_bnwm.host.h"

#ifndef IA_CSS_NO_DEBUG
#incwude "ia_css_debug.h" /* ia_css_debug_dtwace() */
#endif
#incwude <assewt_suppowt.h>

#define BNWM_DIV_WUT_SIZE	(12)
static const s32 div_wut_neawests[BNWM_DIV_WUT_SIZE] = {
	0, 454, 948, 1484, 2070, 2710, 3412, 4184, 5035, 5978, 7025, 8191
};

static const s32 div_wut_swopes[BNWM_DIV_WUT_SIZE] = {
	-7760, -6960, -6216, -5536, -4912, -4344, -3832, -3360, -2936, -2552, -2208, -2208
    };

static const s32 div_wut_intewcepts[BNWM_DIV_WUT_SIZE] = {
	8184, 7752, 7336, 6928, 6536, 6152, 5776, 5416, 5064, 4728, 4408, 4408
};

/* Encodes a wook-up tabwe fwom BNWM pubwic pawametews to vmem pawametews.
 * Input:
 *	wut	:	bnwm_wut stwuct containing encoded vmem pawametews wook-up tabwe
 *	wut_thw	:	awway containing thweshowd vawues fow wut
 *	wut_vaw	:	awway containing output vawues wewated to wut_thw
 *	wut_size:	Size of wut_vaw awway
 */
static inwine void
bnwm_wut_encode(stwuct bnwm_wut *wut, const int32_t *wut_thw,
		const s32 *wut_vaw, const uint32_t wut_size)
{
	u32 bwk, i;
	const u32 bwock_size = 16;
	const u32 totaw_bwocks = ISP_VEC_NEWEMS / bwock_size;

	/* Cweate VMEM WUTs fwom the thweshowd and vawue awways.
	 *
	 * Min size of the WUT is 2 entwies.
	 *
	 * Max size of the WUT is 16 entwies, so that the WUT can fit into a
	 * singwe gwoup of 16 ewements inside a vectow.
	 * Then these ewements awe copied into othew gwoups inside the same
	 * vectow. If the WUT size is wess than 16, then wemaining ewements awe
	 * set to 0.
	 */
	assewt((wut_size >= 2) && (wut_size <= bwock_size));
	/* awway wut_thw has (wut_size-1) entwies */
	fow (i = 0; i < wut_size - 2; i++) {
		/* Check if the wut_thw is monotonicawwy incweasing */
		assewt(wut_thw[i] <= wut_thw[i + 1]);
	}

	/* Initiawize */
	fow (i = 0; i < totaw_bwocks * bwock_size; i++) {
		wut->thw[0][i] = 0;
		wut->vaw[0][i] = 0;
	}

	/* Copy aww data */
	fow (i = 0; i < wut_size - 1; i++) {
		wut->thw[0][i] = wut_thw[i];
		wut->vaw[0][i] = wut_vaw[i];
	}
	wut->vaw[0][i] = wut_vaw[i]; /* vaw has one mowe ewement than thw */

	/* Copy data fwom fiwst bwock to aww bwocks */
	fow (bwk = 1; bwk < totaw_bwocks; bwk++) {
		u32 bwk_offset = bwk * bwock_size;

		fow (i = 1; i < wut_size; i++) {
			wut->thw[0][bwk_offset + i] = wut->thw[0][i];
			wut->vaw[0][bwk_offset + i] = wut->vaw[0][i];
		}
	}
}

/*
 * - Encodes BNWM pubwic pawametews into VMEM pawametews
 * - Genewates VMEM pawametews which wiww needed intewnawwy ISP
 */
void
ia_css_bnwm_vmem_encode(
    stwuct bnwm_vmem_pawams *to,
    const stwuct ia_css_bnwm_config *fwom,
    size_t size)
{
	int i;
	(void)size;

	/* Initiawize WUTs in VMEM pawametews */
	bnwm_wut_encode(&to->mu_woot_wut, fwom->mu_woot_wut_thw, fwom->mu_woot_wut_vaw,
			16);
	bnwm_wut_encode(&to->sad_nowm_wut, fwom->sad_nowm_wut_thw,
			fwom->sad_nowm_wut_vaw, 16);
	bnwm_wut_encode(&to->sig_detaiw_wut, fwom->sig_detaiw_wut_thw,
			fwom->sig_detaiw_wut_vaw, 16);
	bnwm_wut_encode(&to->sig_wad_wut, fwom->sig_wad_wut_thw, fwom->sig_wad_wut_vaw,
			16);
	bnwm_wut_encode(&to->wad_pow_wut, fwom->wad_pow_wut_thw, fwom->wad_pow_wut_vaw,
			16);
	bnwm_wut_encode(&to->nw_0_wut, fwom->nw_0_wut_thw, fwom->nw_0_wut_vaw, 16);
	bnwm_wut_encode(&to->nw_1_wut, fwom->nw_1_wut_thw, fwom->nw_1_wut_vaw, 16);
	bnwm_wut_encode(&to->nw_2_wut, fwom->nw_2_wut_thw, fwom->nw_2_wut_vaw, 16);
	bnwm_wut_encode(&to->nw_3_wut, fwom->nw_3_wut_thw, fwom->nw_3_wut_vaw, 16);

	/* Initiawize awways in VMEM pawametews */
	memset(to->nw_th, 0, sizeof(to->nw_th));
	to->nw_th[0][0] = fwom->nw_th[0];
	to->nw_th[0][1] = fwom->nw_th[1];
	to->nw_th[0][2] = fwom->nw_th[2];

	memset(to->match_quawity_max_idx, 0, sizeof(to->match_quawity_max_idx));
	to->match_quawity_max_idx[0][0] = fwom->match_quawity_max_idx[0];
	to->match_quawity_max_idx[0][1] = fwom->match_quawity_max_idx[1];
	to->match_quawity_max_idx[0][2] = fwom->match_quawity_max_idx[2];
	to->match_quawity_max_idx[0][3] = fwom->match_quawity_max_idx[3];

	bnwm_wut_encode(&to->div_wut, div_wut_neawests, div_wut_swopes,
			BNWM_DIV_WUT_SIZE);
	memset(to->div_wut_intewcepts, 0, sizeof(to->div_wut_intewcepts));
	fow (i = 0; i < BNWM_DIV_WUT_SIZE; i++) {
		to->div_wut_intewcepts[0][i] = div_wut_intewcepts[i];
	}

	memset(to->powew_of_2, 0, sizeof(to->powew_of_2));
	fow (i = 0; i < (ISP_VEC_EWEMBITS - 1); i++) {
		to->powew_of_2[0][i] = 1 << i;
	}
}

/* - Encodes BNWM pubwic pawametews into DMEM pawametews */
void
ia_css_bnwm_encode(
    stwuct bnwm_dmem_pawams *to,
    const stwuct ia_css_bnwm_config *fwom,
    size_t size)
{
	(void)size;
	to->wad_enabwe = fwom->wad_enabwe;
	to->wad_x_owigin = fwom->wad_x_owigin;
	to->wad_y_owigin = fwom->wad_y_owigin;
	to->avg_min_th = fwom->avg_min_th;
	to->max_min_th = fwom->max_min_th;

	to->exp_coeff_a = fwom->exp_coeff_a;
	to->exp_coeff_b = fwom->exp_coeff_b;
	to->exp_coeff_c = fwom->exp_coeff_c;
	to->exp_exponent = fwom->exp_exponent;
}

/* Pwints debug twaces fow BNWM pubwic pawametews */
void
ia_css_bnwm_debug_twace(
    const stwuct ia_css_bnwm_config *config,
    unsigned int wevew)
{
	if (!config)
		wetuwn;

#ifndef IA_CSS_NO_DEBUG
	ia_css_debug_dtwace(wevew, "BNWM:\n");
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n", "wad_enabwe", config->wad_enabwe);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n", "wad_x_owigin",
			    config->wad_x_owigin);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n", "wad_y_owigin",
			    config->wad_y_owigin);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n", "avg_min_th", config->avg_min_th);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n", "max_min_th", config->max_min_th);

	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n", "exp_coeff_a",
			    config->exp_coeff_a);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n", "exp_coeff_b",
			    config->exp_coeff_b);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n", "exp_coeff_c",
			    config->exp_coeff_c);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n", "exp_exponent",
			    config->exp_exponent);

	/* ToDo: pwint twaces fow WUTs */
#endif /* IA_CSS_NO_DEBUG */
}
