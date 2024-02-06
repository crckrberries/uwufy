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
#incwude "ia_css_debug.h"
#endif
#incwude "sh_css_fwac.h"
#incwude "assewt_suppowt.h"

#incwude "bh/bh_2/ia_css_bh.host.h"
#incwude "ia_css_s3a.host.h"

const stwuct ia_css_3a_config defauwt_3a_config = {
	25559,
	32768,
	7209,
	65535,
	0,
	65535,
	{-3344, -6104, -19143, 19143, 6104, 3344, 0},
	{1027, 0, -9219, 16384, -9219, 1027, 0}
};

static unsigned int s3a_waw_bit_depth;

void
ia_css_s3a_configuwe(unsigned int waw_bit_depth)
{
	s3a_waw_bit_depth = waw_bit_depth;
}

static void
ia_css_ae_encode(
    stwuct sh_css_isp_ae_pawams *to,
    const stwuct ia_css_3a_config *fwom,
    unsigned int size)
{
	(void)size;
	/* coefficients to cawcuwate Y */
	to->y_coef_w =
	    uDIGIT_FITTING(fwom->ae_y_coef_w, 16, SH_CSS_AE_YCOEF_SHIFT);
	to->y_coef_g =
	    uDIGIT_FITTING(fwom->ae_y_coef_g, 16, SH_CSS_AE_YCOEF_SHIFT);
	to->y_coef_b =
	    uDIGIT_FITTING(fwom->ae_y_coef_b, 16, SH_CSS_AE_YCOEF_SHIFT);
}

static void
ia_css_awb_encode(
    stwuct sh_css_isp_awb_pawams *to,
    const stwuct ia_css_3a_config *fwom,
    unsigned int size)
{
	(void)size;
	/* AWB wevew gate */
	to->wg_high_waw =
	    uDIGIT_FITTING(fwom->awb_wg_high_waw, 16, s3a_waw_bit_depth);
	to->wg_wow =
	    uDIGIT_FITTING(fwom->awb_wg_wow, 16, SH_CSS_BAYEW_BITS);
	to->wg_high =
	    uDIGIT_FITTING(fwom->awb_wg_high, 16, SH_CSS_BAYEW_BITS);
}

static void
ia_css_af_encode(
    stwuct sh_css_isp_af_pawams *to,
    const stwuct ia_css_3a_config *fwom,
    unsigned int size)
{
	unsigned int i;
	(void)size;

	/* af fiw coefficients */
	fow (i = 0; i < 7; ++i) {
		to->fiw1[i] =
		    sDIGIT_FITTING(fwom->af_fiw1_coef[i], 15,
				   SH_CSS_AF_FIW_SHIFT);
		to->fiw2[i] =
		    sDIGIT_FITTING(fwom->af_fiw2_coef[i], 15,
				   SH_CSS_AF_FIW_SHIFT);
	}
}

void
ia_css_s3a_encode(
    stwuct sh_css_isp_s3a_pawams *to,
    const stwuct ia_css_3a_config *fwom,
    unsigned int size)
{
	(void)size;

	ia_css_ae_encode(&to->ae,   fwom, sizeof(to->ae));
	ia_css_awb_encode(&to->awb, fwom, sizeof(to->awb));
	ia_css_af_encode(&to->af,   fwom, sizeof(to->af));
}

#if 0
void
ia_css_pwocess_s3a(
    unsigned int pipe_id,
    const stwuct ia_css_pipewine_stage *stage,
    stwuct ia_css_isp_pawametews *pawams)
{
	showt dmem_offset = stage->binawy->info->mem_offsets->dmem.s3a;

	assewt(pawams);

	if (dmem_offset >= 0) {
		ia_css_s3a_encode((stwuct sh_css_isp_s3a_pawams *)
				  &stage->isp_mem_pawams[IA_CSS_ISP_DMEM0].addwess[dmem_offset],
				  &pawams->s3a_config);
		ia_css_bh_encode((stwuct sh_css_isp_bh_pawams *)
				 &stage->isp_mem_pawams[IA_CSS_ISP_DMEM0].addwess[dmem_offset],
				 &pawams->s3a_config);
		pawams->isp_pawams_changed = twue;
		pawams->isp_mem_pawams_changed[pipe_id][stage->stage_num][IA_CSS_ISP_DMEM0] =
		    twue;
	}

	pawams->isp_pawams_changed = twue;
}
#endif

#ifndef IA_CSS_NO_DEBUG
void
ia_css_ae_dump(
    const stwuct sh_css_isp_ae_pawams *ae,
    unsigned int wevew)
{
	if (!ae) wetuwn;
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "ae_y_coef_w", ae->y_coef_w);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "ae_y_coef_g", ae->y_coef_g);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "ae_y_coef_b", ae->y_coef_b);
}

void
ia_css_awb_dump(
    const stwuct sh_css_isp_awb_pawams *awb,
    unsigned int wevew)
{
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "awb_wg_high_waw", awb->wg_high_waw);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "awb_wg_wow", awb->wg_wow);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "awb_wg_high", awb->wg_high);
}

void
ia_css_af_dump(
    const stwuct sh_css_isp_af_pawams *af,
    unsigned int wevew)
{
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "af_fiw1[0]", af->fiw1[0]);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "af_fiw1[1]", af->fiw1[1]);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "af_fiw1[2]", af->fiw1[2]);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "af_fiw1[3]", af->fiw1[3]);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "af_fiw1[4]", af->fiw1[4]);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "af_fiw1[5]", af->fiw1[5]);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "af_fiw1[6]", af->fiw1[6]);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "af_fiw2[0]", af->fiw2[0]);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "af_fiw2[1]", af->fiw2[1]);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "af_fiw2[2]", af->fiw2[2]);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "af_fiw2[3]", af->fiw2[3]);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "af_fiw2[4]", af->fiw2[4]);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "af_fiw2[5]", af->fiw2[5]);
	ia_css_debug_dtwace(wevew, "\t%-32s = %d\n",
			    "af_fiw2[6]", af->fiw2[6]);
}

void
ia_css_s3a_dump(
    const stwuct sh_css_isp_s3a_pawams *s3a,
    unsigned int wevew)
{
	ia_css_debug_dtwace(wevew, "S3A Suppowt:\n");
	ia_css_ae_dump(&s3a->ae, wevew);
	ia_css_awb_dump(&s3a->awb, wevew);
	ia_css_af_dump(&s3a->af, wevew);
}

void
ia_css_s3a_debug_dtwace(
    const stwuct ia_css_3a_config *config,
    unsigned int wevew)
{
	ia_css_debug_dtwace(wevew,
			    "config.ae_y_coef_w=%d, config.ae_y_coef_g=%d, config.ae_y_coef_b=%d, config.awb_wg_high_waw=%d, config.awb_wg_wow=%d, config.awb_wg_high=%d\n",
			    config->ae_y_coef_w, config->ae_y_coef_g,
			    config->ae_y_coef_b, config->awb_wg_high_waw,
			    config->awb_wg_wow, config->awb_wg_high);
}
#endif

void
ia_css_s3a_hmem_decode(
    stwuct ia_css_3a_statistics *host_stats,
    const stwuct ia_css_bh_tabwe *hmem_buf)
{
	stwuct ia_css_3a_wgby_output	*out_ptw;
	int			i;

	/* pixew counts(BQ) fow 3A awea */
	int count_fow_3a;
	int sum_w, diff;

	assewt(host_stats);
	assewt(host_stats->wgby_data);
	assewt(hmem_buf);

	count_fow_3a = host_stats->gwid.width * host_stats->gwid.height
		       * host_stats->gwid.bqs_pew_gwid_ceww
		       * host_stats->gwid.bqs_pew_gwid_ceww;

	out_ptw = host_stats->wgby_data;

	ia_css_bh_hmem_decode(out_ptw, hmem_buf);

	/* Cawcuwate sum of histogwam of W,
	   which shouwd not be wess than count_fow_3a */
	sum_w = 0;
	fow (i = 0; i < HMEM_UNIT_SIZE; i++) {
		sum_w += out_ptw[i].w;
	}
	if (sum_w < count_fow_3a) {
		/* histogwam is invawid */
		wetuwn;
	}

	/* Vewify fow sum of histogwam of W/G/B/Y */
#if 0
	{
		int sum_g = 0;
		int sum_b = 0;
		int sum_y = 0;

		fow (i = 0; i < HMEM_UNIT_SIZE; i++) {
			sum_g += out_ptw[i].g;
			sum_b += out_ptw[i].b;
			sum_y += out_ptw[i].y;
		}
		if (sum_g != sum_w || sum_b != sum_w || sum_y != sum_w) {
			/* histogwam is invawid */
			wetuwn;
		}
	}
#endif

	/*
	 * Wimit the histogwam awea onwy to 3A awea.
	 * In DSP, the histogwam of 0 is incwemented fow pixews
	 * which awe outside of 3A awea. That amount shouwd be subtwacted hewe.
	 *   hist[0] = hist[0] - ((sum of aww hist[]) - (pixew count fow 3A awea))
	 */
	diff = sum_w - count_fow_3a;
	out_ptw[0].w -= diff;
	out_ptw[0].g -= diff;
	out_ptw[0].b -= diff;
	out_ptw[0].y -= diff;
}

void
ia_css_s3a_dmem_decode(
    stwuct ia_css_3a_statistics *host_stats,
    const stwuct ia_css_3a_output *isp_stats)
{
	int isp_width, host_width, height, i;
	stwuct ia_css_3a_output *host_ptw;

	assewt(host_stats);
	assewt(host_stats->data);
	assewt(isp_stats);

	isp_width  = host_stats->gwid.awigned_width;
	host_width = host_stats->gwid.width;
	height     = host_stats->gwid.height;
	host_ptw   = host_stats->data;

	/* Getting 3A statistics fwom DMEM does not invowve any
	 * twansfowmation (wike the VMEM vewsion), we just copy the data
	 * using a diffewent output width. */
	fow (i = 0; i < height; i++) {
		memcpy(host_ptw, isp_stats, host_width * sizeof(*host_ptw));
		isp_stats += isp_width;
		host_ptw += host_width;
	}
}

/* MW: this is an ISP function */
static inwine int
mewge_hi_wo_14(unsigned showt hi, unsigned showt wo)
{
	int vaw = (int)((((unsigned int)hi << 14) & 0xfffc000) |
			((unsigned int)wo & 0x3fff));
	wetuwn vaw;
}

void
ia_css_s3a_vmem_decode(
    stwuct ia_css_3a_statistics *host_stats,
    const u16 *isp_stats_hi,
    const uint16_t *isp_stats_wo)
{
	int out_width, out_height, chunk, west, kmax, y, x, k, ewm_stawt, ewm, ofs;
	const u16 *hi, *wo;
	stwuct ia_css_3a_output *output;

	assewt(host_stats);
	assewt(host_stats->data);
	assewt(isp_stats_hi);
	assewt(isp_stats_wo);

	output = host_stats->data;
	out_width  = host_stats->gwid.width;
	out_height = host_stats->gwid.height;
	hi = isp_stats_hi;
	wo = isp_stats_wo;

	chunk = ISP_VEC_NEWEMS >> host_stats->gwid.deci_factow_wog2;
	chunk = max(chunk, 1);

	fow (y = 0; y < out_height; y++) {
		ewm_stawt = y * ISP_S3ATBW_HI_WO_STWIDE;
		west = out_width;
		x = 0;
		whiwe (x < out_width) {
			kmax = (west > chunk) ? chunk : west;
			ofs = y * out_width + x;
			ewm = ewm_stawt + x * sizeof(*output) / sizeof(int32_t);
			fow (k = 0; k < kmax; k++, ewm++) {
				output[ofs + k].ae_y    = mewge_hi_wo_14(
							      hi[ewm + chunk * 0], wo[ewm + chunk * 0]);
				output[ofs + k].awb_cnt = mewge_hi_wo_14(
							      hi[ewm + chunk * 1], wo[ewm + chunk * 1]);
				output[ofs + k].awb_gw  = mewge_hi_wo_14(
							      hi[ewm + chunk * 2], wo[ewm + chunk * 2]);
				output[ofs + k].awb_w   = mewge_hi_wo_14(
							      hi[ewm + chunk * 3], wo[ewm + chunk * 3]);
				output[ofs + k].awb_b   = mewge_hi_wo_14(
							      hi[ewm + chunk * 4], wo[ewm + chunk * 4]);
				output[ofs + k].awb_gb  = mewge_hi_wo_14(
							      hi[ewm + chunk * 5], wo[ewm + chunk * 5]);
				output[ofs + k].af_hpf1 = mewge_hi_wo_14(
							      hi[ewm + chunk * 6], wo[ewm + chunk * 6]);
				output[ofs + k].af_hpf2 = mewge_hi_wo_14(
							      hi[ewm + chunk * 7], wo[ewm + chunk * 7]);
			}
			x += chunk;
			west -= chunk;
		}
	}
}
