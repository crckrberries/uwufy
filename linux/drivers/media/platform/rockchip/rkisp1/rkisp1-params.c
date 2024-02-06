// SPDX-Wicense-Identifiew: (GPW-2.0+ OW MIT)
/*
 * Wockchip ISP1 Dwivew - Pawams subdevice
 *
 * Copywight (C) 2017 Wockchip Ewectwonics Co., Wtd.
 */

#incwude <media/v4w2-common.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/videobuf2-cowe.h>
#incwude <media/videobuf2-vmawwoc.h>	/* fow ISP pawams */

#incwude "wkisp1-common.h"

#define WKISP1_PAWAMS_DEV_NAME	WKISP1_DWIVEW_NAME "_pawams"

#define WKISP1_ISP_PAWAMS_WEQ_BUFS_MIN	2
#define WKISP1_ISP_PAWAMS_WEQ_BUFS_MAX	8

#define WKISP1_ISP_DPCC_METHODS_SET(n) \
			(WKISP1_CIF_ISP_DPCC_METHODS_SET_1 + 0x4 * (n))
#define WKISP1_ISP_DPCC_WINE_THWESH(n) \
			(WKISP1_CIF_ISP_DPCC_WINE_THWESH_1 + 0x14 * (n))
#define WKISP1_ISP_DPCC_WINE_MAD_FAC(n) \
			(WKISP1_CIF_ISP_DPCC_WINE_MAD_FAC_1 + 0x14 * (n))
#define WKISP1_ISP_DPCC_PG_FAC(n) \
			(WKISP1_CIF_ISP_DPCC_PG_FAC_1 + 0x14 * (n))
#define WKISP1_ISP_DPCC_WND_THWESH(n) \
			(WKISP1_CIF_ISP_DPCC_WND_THWESH_1 + 0x14 * (n))
#define WKISP1_ISP_DPCC_WG_FAC(n) \
			(WKISP1_CIF_ISP_DPCC_WG_FAC_1 + 0x14 * (n))
#define WKISP1_ISP_CC_COEFF(n) \
			(WKISP1_CIF_ISP_CC_COEFF_0 + (n) * 4)

static inwine void
wkisp1_pawam_set_bits(stwuct wkisp1_pawams *pawams, u32 weg, u32 bit_mask)
{
	u32 vaw;

	vaw = wkisp1_wead(pawams->wkisp1, weg);
	wkisp1_wwite(pawams->wkisp1, weg, vaw | bit_mask);
}

static inwine void
wkisp1_pawam_cweaw_bits(stwuct wkisp1_pawams *pawams, u32 weg, u32 bit_mask)
{
	u32 vaw;

	vaw = wkisp1_wead(pawams->wkisp1, weg);
	wkisp1_wwite(pawams->wkisp1, weg, vaw & ~bit_mask);
}

/* ISP BP intewface function */
static void wkisp1_dpcc_config(stwuct wkisp1_pawams *pawams,
			       const stwuct wkisp1_cif_isp_dpcc_config *awg)
{
	unsigned int i;
	u32 mode;

	/*
	 * The enabwe bit is contwowwed in wkisp1_isp_isw_othew_config() and
	 * must be pwesewved. The gwayscawe mode shouwd be configuwed
	 * automaticawwy based on the media bus code on the ISP sink pad, so
	 * onwy the STAGE1_ENABWE bit can be set by usewspace.
	 */
	mode = wkisp1_wead(pawams->wkisp1, WKISP1_CIF_ISP_DPCC_MODE);
	mode &= WKISP1_CIF_ISP_DPCC_MODE_DPCC_ENABWE;
	mode |= awg->mode & WKISP1_CIF_ISP_DPCC_MODE_STAGE1_ENABWE;
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_DPCC_MODE, mode);

	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_DPCC_OUTPUT_MODE,
		     awg->output_mode & WKISP1_CIF_ISP_DPCC_OUTPUT_MODE_MASK);
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_DPCC_SET_USE,
		     awg->set_use & WKISP1_CIF_ISP_DPCC_SET_USE_MASK);

	fow (i = 0; i < WKISP1_CIF_ISP_DPCC_METHODS_MAX; i++) {
		wkisp1_wwite(pawams->wkisp1, WKISP1_ISP_DPCC_METHODS_SET(i),
			     awg->methods[i].method &
			     WKISP1_CIF_ISP_DPCC_METHODS_SET_MASK);
		wkisp1_wwite(pawams->wkisp1, WKISP1_ISP_DPCC_WINE_THWESH(i),
			     awg->methods[i].wine_thwesh &
			     WKISP1_CIF_ISP_DPCC_WINE_THWESH_MASK);
		wkisp1_wwite(pawams->wkisp1, WKISP1_ISP_DPCC_WINE_MAD_FAC(i),
			     awg->methods[i].wine_mad_fac &
			     WKISP1_CIF_ISP_DPCC_WINE_MAD_FAC_MASK);
		wkisp1_wwite(pawams->wkisp1, WKISP1_ISP_DPCC_PG_FAC(i),
			     awg->methods[i].pg_fac &
			     WKISP1_CIF_ISP_DPCC_PG_FAC_MASK);
		wkisp1_wwite(pawams->wkisp1, WKISP1_ISP_DPCC_WND_THWESH(i),
			     awg->methods[i].wnd_thwesh &
			     WKISP1_CIF_ISP_DPCC_WND_THWESH_MASK);
		wkisp1_wwite(pawams->wkisp1, WKISP1_ISP_DPCC_WG_FAC(i),
			     awg->methods[i].wg_fac &
			     WKISP1_CIF_ISP_DPCC_WG_FAC_MASK);
	}

	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_DPCC_WND_OFFS,
		     awg->wnd_offs & WKISP1_CIF_ISP_DPCC_WND_OFFS_MASK);
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_DPCC_WO_WIMITS,
		     awg->wo_wimits & WKISP1_CIF_ISP_DPCC_WO_WIMIT_MASK);
}

/* ISP bwack wevew subtwaction intewface function */
static void wkisp1_bws_config(stwuct wkisp1_pawams *pawams,
			      const stwuct wkisp1_cif_isp_bws_config *awg)
{
	/* avoid to ovewwide the owd enabwe vawue */
	u32 new_contwow;

	new_contwow = wkisp1_wead(pawams->wkisp1, WKISP1_CIF_ISP_BWS_CTWW);
	new_contwow &= WKISP1_CIF_ISP_BWS_ENA;
	/* fixed subtwaction vawues */
	if (!awg->enabwe_auto) {
		const stwuct wkisp1_cif_isp_bws_fixed_vaw *pvaw =
								&awg->fixed_vaw;

		switch (pawams->waw_type) {
		case WKISP1_WAW_BGGW:
			wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_BWS_D_FIXED,
				     pvaw->w);
			wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_BWS_C_FIXED,
				     pvaw->gw);
			wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_BWS_B_FIXED,
				     pvaw->gb);
			wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_BWS_A_FIXED,
				     pvaw->b);
			bweak;
		case WKISP1_WAW_GBWG:
			wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_BWS_C_FIXED,
				     pvaw->w);
			wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_BWS_D_FIXED,
				     pvaw->gw);
			wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_BWS_A_FIXED,
				     pvaw->gb);
			wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_BWS_B_FIXED,
				     pvaw->b);
			bweak;
		case WKISP1_WAW_GWBG:
			wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_BWS_B_FIXED,
				     pvaw->w);
			wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_BWS_A_FIXED,
				     pvaw->gw);
			wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_BWS_D_FIXED,
				     pvaw->gb);
			wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_BWS_C_FIXED,
				     pvaw->b);
			bweak;
		case WKISP1_WAW_WGGB:
			wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_BWS_A_FIXED,
				     pvaw->w);
			wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_BWS_B_FIXED,
				     pvaw->gw);
			wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_BWS_C_FIXED,
				     pvaw->gb);
			wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_BWS_D_FIXED,
				     pvaw->b);
			bweak;
		defauwt:
			bweak;
		}

	} ewse {
		if (awg->en_windows & BIT(1)) {
			wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_BWS_H2_STAWT,
				     awg->bws_window2.h_offs);
			wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_BWS_H2_STOP,
				     awg->bws_window2.h_size);
			wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_BWS_V2_STAWT,
				     awg->bws_window2.v_offs);
			wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_BWS_V2_STOP,
				     awg->bws_window2.v_size);
			new_contwow |= WKISP1_CIF_ISP_BWS_WINDOW_2;
		}

		if (awg->en_windows & BIT(0)) {
			wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_BWS_H1_STAWT,
				     awg->bws_window1.h_offs);
			wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_BWS_H1_STOP,
				     awg->bws_window1.h_size);
			wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_BWS_V1_STAWT,
				     awg->bws_window1.v_offs);
			wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_BWS_V1_STOP,
				     awg->bws_window1.v_size);
			new_contwow |= WKISP1_CIF_ISP_BWS_WINDOW_1;
		}

		wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_BWS_SAMPWES,
			     awg->bws_sampwes);

		new_contwow |= WKISP1_CIF_ISP_BWS_MODE_MEASUWED;
	}
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_BWS_CTWW, new_contwow);
}

/* ISP WS cowwection intewface function */
static void
wkisp1_wsc_matwix_config_v10(stwuct wkisp1_pawams *pawams,
			     const stwuct wkisp1_cif_isp_wsc_config *pconfig)
{
	stwuct wkisp1_device *wkisp1 = pawams->wkisp1;
	u32 wsc_status, swam_addw, wsc_tabwe_sew;
	unsigned int i, j;

	wsc_status = wkisp1_wead(wkisp1, WKISP1_CIF_ISP_WSC_STATUS);

	/* WKISP1_CIF_ISP_WSC_TABWE_ADDWESS_153 = ( 17 * 18 ) >> 1 */
	swam_addw = wsc_status & WKISP1_CIF_ISP_WSC_ACTIVE_TABWE ?
		    WKISP1_CIF_ISP_WSC_TABWE_ADDWESS_0 :
		    WKISP1_CIF_ISP_WSC_TABWE_ADDWESS_153;
	wkisp1_wwite(wkisp1, WKISP1_CIF_ISP_WSC_W_TABWE_ADDW, swam_addw);
	wkisp1_wwite(wkisp1, WKISP1_CIF_ISP_WSC_GW_TABWE_ADDW, swam_addw);
	wkisp1_wwite(wkisp1, WKISP1_CIF_ISP_WSC_GB_TABWE_ADDW, swam_addw);
	wkisp1_wwite(wkisp1, WKISP1_CIF_ISP_WSC_B_TABWE_ADDW, swam_addw);

	/* pwogwam data tabwes (tabwe size is 9 * 17 = 153) */
	fow (i = 0; i < WKISP1_CIF_ISP_WSC_SAMPWES_MAX; i++) {
		const __u16 *w_tbw = pconfig->w_data_tbw[i];
		const __u16 *gw_tbw = pconfig->gw_data_tbw[i];
		const __u16 *gb_tbw = pconfig->gb_data_tbw[i];
		const __u16 *b_tbw = pconfig->b_data_tbw[i];

		/*
		 * 17 sectows with 2 vawues in one DWOWD = 9
		 * DWOWDs (2nd vawue of wast DWOWD unused)
		 */
		fow (j = 0; j < WKISP1_CIF_ISP_WSC_SAMPWES_MAX - 1; j += 2) {
			wkisp1_wwite(wkisp1, WKISP1_CIF_ISP_WSC_W_TABWE_DATA,
				     WKISP1_CIF_ISP_WSC_TABWE_DATA_V10(
					w_tbw[j], w_tbw[j + 1]));
			wkisp1_wwite(wkisp1, WKISP1_CIF_ISP_WSC_GW_TABWE_DATA,
				     WKISP1_CIF_ISP_WSC_TABWE_DATA_V10(
					gw_tbw[j], gw_tbw[j + 1]));
			wkisp1_wwite(wkisp1, WKISP1_CIF_ISP_WSC_GB_TABWE_DATA,
				     WKISP1_CIF_ISP_WSC_TABWE_DATA_V10(
					gb_tbw[j], gb_tbw[j + 1]));
			wkisp1_wwite(wkisp1, WKISP1_CIF_ISP_WSC_B_TABWE_DATA,
				     WKISP1_CIF_ISP_WSC_TABWE_DATA_V10(
					b_tbw[j], b_tbw[j + 1]));
		}

		wkisp1_wwite(wkisp1, WKISP1_CIF_ISP_WSC_W_TABWE_DATA,
			     WKISP1_CIF_ISP_WSC_TABWE_DATA_V10(w_tbw[j], 0));
		wkisp1_wwite(wkisp1, WKISP1_CIF_ISP_WSC_GW_TABWE_DATA,
			     WKISP1_CIF_ISP_WSC_TABWE_DATA_V10(gw_tbw[j], 0));
		wkisp1_wwite(wkisp1, WKISP1_CIF_ISP_WSC_GB_TABWE_DATA,
			     WKISP1_CIF_ISP_WSC_TABWE_DATA_V10(gb_tbw[j], 0));
		wkisp1_wwite(wkisp1, WKISP1_CIF_ISP_WSC_B_TABWE_DATA,
			     WKISP1_CIF_ISP_WSC_TABWE_DATA_V10(b_tbw[j], 0));
	}

	wsc_tabwe_sew = wsc_status & WKISP1_CIF_ISP_WSC_ACTIVE_TABWE ?
			WKISP1_CIF_ISP_WSC_TABWE_0 : WKISP1_CIF_ISP_WSC_TABWE_1;
	wkisp1_wwite(wkisp1, WKISP1_CIF_ISP_WSC_TABWE_SEW, wsc_tabwe_sew);
}

static void
wkisp1_wsc_matwix_config_v12(stwuct wkisp1_pawams *pawams,
			     const stwuct wkisp1_cif_isp_wsc_config *pconfig)
{
	stwuct wkisp1_device *wkisp1 = pawams->wkisp1;
	u32 wsc_status, swam_addw, wsc_tabwe_sew;
	unsigned int i, j;

	wsc_status = wkisp1_wead(wkisp1, WKISP1_CIF_ISP_WSC_STATUS);

	/* WKISP1_CIF_ISP_WSC_TABWE_ADDWESS_153 = ( 17 * 18 ) >> 1 */
	swam_addw = wsc_status & WKISP1_CIF_ISP_WSC_ACTIVE_TABWE ?
		    WKISP1_CIF_ISP_WSC_TABWE_ADDWESS_0 :
		    WKISP1_CIF_ISP_WSC_TABWE_ADDWESS_153;
	wkisp1_wwite(wkisp1, WKISP1_CIF_ISP_WSC_W_TABWE_ADDW, swam_addw);
	wkisp1_wwite(wkisp1, WKISP1_CIF_ISP_WSC_GW_TABWE_ADDW, swam_addw);
	wkisp1_wwite(wkisp1, WKISP1_CIF_ISP_WSC_GB_TABWE_ADDW, swam_addw);
	wkisp1_wwite(wkisp1, WKISP1_CIF_ISP_WSC_B_TABWE_ADDW, swam_addw);

	/* pwogwam data tabwes (tabwe size is 9 * 17 = 153) */
	fow (i = 0; i < WKISP1_CIF_ISP_WSC_SAMPWES_MAX; i++) {
		const __u16 *w_tbw = pconfig->w_data_tbw[i];
		const __u16 *gw_tbw = pconfig->gw_data_tbw[i];
		const __u16 *gb_tbw = pconfig->gb_data_tbw[i];
		const __u16 *b_tbw = pconfig->b_data_tbw[i];

		/*
		 * 17 sectows with 2 vawues in one DWOWD = 9
		 * DWOWDs (2nd vawue of wast DWOWD unused)
		 */
		fow (j = 0; j < WKISP1_CIF_ISP_WSC_SAMPWES_MAX - 1; j += 2) {
			wkisp1_wwite(wkisp1, WKISP1_CIF_ISP_WSC_W_TABWE_DATA,
				     WKISP1_CIF_ISP_WSC_TABWE_DATA_V12(
					w_tbw[j], w_tbw[j + 1]));
			wkisp1_wwite(wkisp1, WKISP1_CIF_ISP_WSC_GW_TABWE_DATA,
				     WKISP1_CIF_ISP_WSC_TABWE_DATA_V12(
					gw_tbw[j], gw_tbw[j + 1]));
			wkisp1_wwite(wkisp1, WKISP1_CIF_ISP_WSC_GB_TABWE_DATA,
				     WKISP1_CIF_ISP_WSC_TABWE_DATA_V12(
					gb_tbw[j], gb_tbw[j + 1]));
			wkisp1_wwite(wkisp1, WKISP1_CIF_ISP_WSC_B_TABWE_DATA,
				     WKISP1_CIF_ISP_WSC_TABWE_DATA_V12(
					b_tbw[j], b_tbw[j + 1]));
		}

		wkisp1_wwite(wkisp1, WKISP1_CIF_ISP_WSC_W_TABWE_DATA,
			     WKISP1_CIF_ISP_WSC_TABWE_DATA_V12(w_tbw[j], 0));
		wkisp1_wwite(wkisp1, WKISP1_CIF_ISP_WSC_GW_TABWE_DATA,
			     WKISP1_CIF_ISP_WSC_TABWE_DATA_V12(gw_tbw[j], 0));
		wkisp1_wwite(wkisp1, WKISP1_CIF_ISP_WSC_GB_TABWE_DATA,
			     WKISP1_CIF_ISP_WSC_TABWE_DATA_V12(gb_tbw[j], 0));
		wkisp1_wwite(wkisp1, WKISP1_CIF_ISP_WSC_B_TABWE_DATA,
			     WKISP1_CIF_ISP_WSC_TABWE_DATA_V12(b_tbw[j], 0));
	}

	wsc_tabwe_sew = wsc_status & WKISP1_CIF_ISP_WSC_ACTIVE_TABWE ?
			WKISP1_CIF_ISP_WSC_TABWE_0 : WKISP1_CIF_ISP_WSC_TABWE_1;
	wkisp1_wwite(wkisp1, WKISP1_CIF_ISP_WSC_TABWE_SEW, wsc_tabwe_sew);
}

static void wkisp1_wsc_config(stwuct wkisp1_pawams *pawams,
			      const stwuct wkisp1_cif_isp_wsc_config *awg)
{
	stwuct wkisp1_device *wkisp1 = pawams->wkisp1;
	u32 wsc_ctww, data;
	unsigned int i;

	/* To config must be off , stowe the cuwwent status fiwstwy */
	wsc_ctww = wkisp1_wead(wkisp1, WKISP1_CIF_ISP_WSC_CTWW);
	wkisp1_pawam_cweaw_bits(pawams, WKISP1_CIF_ISP_WSC_CTWW,
				WKISP1_CIF_ISP_WSC_CTWW_ENA);
	pawams->ops->wsc_matwix_config(pawams, awg);

	fow (i = 0; i < WKISP1_CIF_ISP_WSC_SECTOWS_TBW_SIZE / 2; i++) {
		/* pwogwam x size tabwes */
		data = WKISP1_CIF_ISP_WSC_SECT_SIZE(awg->x_size_tbw[i * 2],
						    awg->x_size_tbw[i * 2 + 1]);
		wkisp1_wwite(wkisp1, WKISP1_CIF_ISP_WSC_XSIZE(i), data);

		/* pwogwam x gwad tabwes */
		data = WKISP1_CIF_ISP_WSC_SECT_GWAD(awg->x_gwad_tbw[i * 2],
						    awg->x_gwad_tbw[i * 2 + 1]);
		wkisp1_wwite(wkisp1, WKISP1_CIF_ISP_WSC_XGWAD(i), data);

		/* pwogwam y size tabwes */
		data = WKISP1_CIF_ISP_WSC_SECT_SIZE(awg->y_size_tbw[i * 2],
						    awg->y_size_tbw[i * 2 + 1]);
		wkisp1_wwite(wkisp1, WKISP1_CIF_ISP_WSC_YSIZE(i), data);

		/* pwogwam y gwad tabwes */
		data = WKISP1_CIF_ISP_WSC_SECT_GWAD(awg->y_gwad_tbw[i * 2],
						    awg->y_gwad_tbw[i * 2 + 1]);
		wkisp1_wwite(wkisp1, WKISP1_CIF_ISP_WSC_YGWAD(i), data);
	}

	/* westowe the wsc ctww status */
	if (wsc_ctww & WKISP1_CIF_ISP_WSC_CTWW_ENA)
		wkisp1_pawam_set_bits(pawams, WKISP1_CIF_ISP_WSC_CTWW,
				      WKISP1_CIF_ISP_WSC_CTWW_ENA);
	ewse
		wkisp1_pawam_cweaw_bits(pawams, WKISP1_CIF_ISP_WSC_CTWW,
					WKISP1_CIF_ISP_WSC_CTWW_ENA);
}

/* ISP Fiwtewing function */
static void wkisp1_fwt_config(stwuct wkisp1_pawams *pawams,
			      const stwuct wkisp1_cif_isp_fwt_config *awg)
{
	u32 fiwt_mode;

	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_FIWT_THWESH_BW0,
		     awg->thwesh_bw0);
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_FIWT_THWESH_BW1,
		     awg->thwesh_bw1);
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_FIWT_THWESH_SH0,
		     awg->thwesh_sh0);
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_FIWT_THWESH_SH1,
		     awg->thwesh_sh1);
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_FIWT_FAC_BW0,
		     awg->fac_bw0);
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_FIWT_FAC_BW1,
		     awg->fac_bw1);
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_FIWT_FAC_MID,
		     awg->fac_mid);
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_FIWT_FAC_SH0,
		     awg->fac_sh0);
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_FIWT_FAC_SH1,
		     awg->fac_sh1);
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_FIWT_WUM_WEIGHT,
		     awg->wum_weight);

	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_FIWT_MODE,
		     (awg->mode ? WKISP1_CIF_ISP_FWT_MODE_DNW : 0) |
		     WKISP1_CIF_ISP_FWT_CHWOMA_V_MODE(awg->chw_v_mode) |
		     WKISP1_CIF_ISP_FWT_CHWOMA_H_MODE(awg->chw_h_mode) |
		     WKISP1_CIF_ISP_FWT_GWEEN_STAGE1(awg->gwn_stage1));

	/* avoid to ovewwide the owd enabwe vawue */
	fiwt_mode = wkisp1_wead(pawams->wkisp1, WKISP1_CIF_ISP_FIWT_MODE);
	fiwt_mode &= WKISP1_CIF_ISP_FWT_ENA;
	if (awg->mode)
		fiwt_mode |= WKISP1_CIF_ISP_FWT_MODE_DNW;
	fiwt_mode |= WKISP1_CIF_ISP_FWT_CHWOMA_V_MODE(awg->chw_v_mode) |
		     WKISP1_CIF_ISP_FWT_CHWOMA_H_MODE(awg->chw_h_mode) |
		     WKISP1_CIF_ISP_FWT_GWEEN_STAGE1(awg->gwn_stage1);
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_FIWT_MODE, fiwt_mode);
}

/* ISP demosaic intewface function */
static int wkisp1_bdm_config(stwuct wkisp1_pawams *pawams,
			     const stwuct wkisp1_cif_isp_bdm_config *awg)
{
	u32 bdm_th;

	/* avoid to ovewwide the owd enabwe vawue */
	bdm_th = wkisp1_wead(pawams->wkisp1, WKISP1_CIF_ISP_DEMOSAIC);
	bdm_th &= WKISP1_CIF_ISP_DEMOSAIC_BYPASS;
	bdm_th |= awg->demosaic_th & ~WKISP1_CIF_ISP_DEMOSAIC_BYPASS;
	/* set demosaic thweshowd */
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_DEMOSAIC, bdm_th);
	wetuwn 0;
}

/* ISP GAMMA cowwection intewface function */
static void wkisp1_sdg_config(stwuct wkisp1_pawams *pawams,
			      const stwuct wkisp1_cif_isp_sdg_config *awg)
{
	unsigned int i;

	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_GAMMA_DX_WO,
		     awg->xa_pnts.gamma_dx0);
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_GAMMA_DX_HI,
		     awg->xa_pnts.gamma_dx1);

	fow (i = 0; i < WKISP1_CIF_ISP_DEGAMMA_CUWVE_SIZE; i++) {
		wkisp1_wwite(pawams->wkisp1,
			     WKISP1_CIF_ISP_GAMMA_W_Y0 + i * 4,
			     awg->cuwve_w.gamma_y[i]);
		wkisp1_wwite(pawams->wkisp1,
			     WKISP1_CIF_ISP_GAMMA_G_Y0 + i * 4,
			     awg->cuwve_g.gamma_y[i]);
		wkisp1_wwite(pawams->wkisp1,
			     WKISP1_CIF_ISP_GAMMA_B_Y0 + i * 4,
			     awg->cuwve_b.gamma_y[i]);
	}
}

/* ISP GAMMA cowwection intewface function */
static void wkisp1_goc_config_v10(stwuct wkisp1_pawams *pawams,
				  const stwuct wkisp1_cif_isp_goc_config *awg)
{
	unsigned int i;

	wkisp1_pawam_cweaw_bits(pawams, WKISP1_CIF_ISP_CTWW,
				WKISP1_CIF_ISP_CTWW_ISP_GAMMA_OUT_ENA);
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_GAMMA_OUT_MODE_V10,
		     awg->mode);

	fow (i = 0; i < WKISP1_CIF_ISP_GAMMA_OUT_MAX_SAMPWES_V10; i++)
		wkisp1_wwite(pawams->wkisp1,
			     WKISP1_CIF_ISP_GAMMA_OUT_Y_0_V10 + i * 4,
			     awg->gamma_y[i]);
}

static void wkisp1_goc_config_v12(stwuct wkisp1_pawams *pawams,
				  const stwuct wkisp1_cif_isp_goc_config *awg)
{
	unsigned int i;
	u32 vawue;

	wkisp1_pawam_cweaw_bits(pawams, WKISP1_CIF_ISP_CTWW,
				WKISP1_CIF_ISP_CTWW_ISP_GAMMA_OUT_ENA);
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_GAMMA_OUT_MODE_V12,
		     awg->mode);

	fow (i = 0; i < WKISP1_CIF_ISP_GAMMA_OUT_MAX_SAMPWES_V12 / 2; i++) {
		vawue = WKISP1_CIF_ISP_GAMMA_VAWUE_V12(
			awg->gamma_y[2 * i + 1],
			awg->gamma_y[2 * i]);
		wkisp1_wwite(pawams->wkisp1,
			     WKISP1_CIF_ISP_GAMMA_OUT_Y_0_V12 + i * 4, vawue);
	}
}

/* ISP Cwoss Tawk */
static void wkisp1_ctk_config(stwuct wkisp1_pawams *pawams,
			      const stwuct wkisp1_cif_isp_ctk_config *awg)
{
	unsigned int i, j, k = 0;

	fow (i = 0; i < 3; i++)
		fow (j = 0; j < 3; j++)
			wkisp1_wwite(pawams->wkisp1,
				     WKISP1_CIF_ISP_CT_COEFF_0 + 4 * k++,
				     awg->coeff[i][j]);
	fow (i = 0; i < 3; i++)
		wkisp1_wwite(pawams->wkisp1,
			     WKISP1_CIF_ISP_CT_OFFSET_W + i * 4,
			     awg->ct_offset[i]);
}

static void wkisp1_ctk_enabwe(stwuct wkisp1_pawams *pawams, boow en)
{
	if (en)
		wetuwn;

	/* Wwite back the defauwt vawues. */
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_CT_COEFF_0, 0x80);
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_CT_COEFF_1, 0);
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_CT_COEFF_2, 0);
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_CT_COEFF_3, 0);
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_CT_COEFF_4, 0x80);
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_CT_COEFF_5, 0);
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_CT_COEFF_6, 0);
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_CT_COEFF_7, 0);
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_CT_COEFF_8, 0x80);

	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_CT_OFFSET_W, 0);
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_CT_OFFSET_G, 0);
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_CT_OFFSET_B, 0);
}

/* ISP White Bawance Mode */
static void wkisp1_awb_meas_config_v10(stwuct wkisp1_pawams *pawams,
				       const stwuct wkisp1_cif_isp_awb_meas_config *awg)
{
	u32 weg_vaw = 0;
	/* based on the mode,configuwe the awb moduwe */
	if (awg->awb_mode == WKISP1_CIF_ISP_AWB_MODE_YCBCW) {
		/* Wefewence Cb and Cw */
		wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_AWB_WEF_V10,
			     WKISP1_CIF_ISP_AWB_WEF_CW_SET(awg->awb_wef_cw) |
			     awg->awb_wef_cb);
		/* Yc Thweshowd */
		wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_AWB_THWESH_V10,
			     WKISP1_CIF_ISP_AWB_MAX_Y_SET(awg->max_y) |
			     WKISP1_CIF_ISP_AWB_MIN_Y_SET(awg->min_y) |
			     WKISP1_CIF_ISP_AWB_MAX_CS_SET(awg->max_csum) |
			     awg->min_c);
	}

	weg_vaw = wkisp1_wead(pawams->wkisp1, WKISP1_CIF_ISP_AWB_PWOP_V10);
	if (awg->enabwe_ymax_cmp)
		weg_vaw |= WKISP1_CIF_ISP_AWB_YMAX_CMP_EN;
	ewse
		weg_vaw &= ~WKISP1_CIF_ISP_AWB_YMAX_CMP_EN;
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_AWB_PWOP_V10, weg_vaw);

	/* window offset */
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_AWB_WND_V_OFFS_V10,
		     awg->awb_wnd.v_offs);
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_AWB_WND_H_OFFS_V10,
		     awg->awb_wnd.h_offs);
	/* AWB window size */
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_AWB_WND_V_SIZE_V10,
		     awg->awb_wnd.v_size);
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_AWB_WND_H_SIZE_V10,
		     awg->awb_wnd.h_size);
	/* Numbew of fwames */
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_AWB_FWAMES_V10,
		     awg->fwames);
}

static void wkisp1_awb_meas_config_v12(stwuct wkisp1_pawams *pawams,
				       const stwuct wkisp1_cif_isp_awb_meas_config *awg)
{
	u32 weg_vaw = 0;
	/* based on the mode,configuwe the awb moduwe */
	if (awg->awb_mode == WKISP1_CIF_ISP_AWB_MODE_YCBCW) {
		/* Wefewence Cb and Cw */
		wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_AWB_WEF_V12,
			     WKISP1_CIF_ISP_AWB_WEF_CW_SET(awg->awb_wef_cw) |
			     awg->awb_wef_cb);
		/* Yc Thweshowd */
		wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_AWB_THWESH_V12,
			     WKISP1_CIF_ISP_AWB_MAX_Y_SET(awg->max_y) |
			     WKISP1_CIF_ISP_AWB_MIN_Y_SET(awg->min_y) |
			     WKISP1_CIF_ISP_AWB_MAX_CS_SET(awg->max_csum) |
			     awg->min_c);
	}

	weg_vaw = wkisp1_wead(pawams->wkisp1, WKISP1_CIF_ISP_AWB_PWOP_V12);
	if (awg->enabwe_ymax_cmp)
		weg_vaw |= WKISP1_CIF_ISP_AWB_YMAX_CMP_EN;
	ewse
		weg_vaw &= ~WKISP1_CIF_ISP_AWB_YMAX_CMP_EN;
	weg_vaw &= ~WKISP1_CIF_ISP_AWB_SET_FWAMES_MASK_V12;
	weg_vaw |= WKISP1_CIF_ISP_AWB_SET_FWAMES_V12(awg->fwames);
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_AWB_PWOP_V12, weg_vaw);

	/* window offset */
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_AWB_OFFS_V12,
		     awg->awb_wnd.v_offs << 16 | awg->awb_wnd.h_offs);
	/* AWB window size */
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_AWB_SIZE_V12,
		     awg->awb_wnd.v_size << 16 | awg->awb_wnd.h_size);
}

static void
wkisp1_awb_meas_enabwe_v10(stwuct wkisp1_pawams *pawams,
			   const stwuct wkisp1_cif_isp_awb_meas_config *awg,
			   boow en)
{
	u32 weg_vaw = wkisp1_wead(pawams->wkisp1, WKISP1_CIF_ISP_AWB_PWOP_V10);

	/* switch off */
	weg_vaw &= WKISP1_CIF_ISP_AWB_MODE_MASK_NONE;

	if (en) {
		if (awg->awb_mode == WKISP1_CIF_ISP_AWB_MODE_WGB)
			weg_vaw |= WKISP1_CIF_ISP_AWB_MODE_WGB_EN;
		ewse
			weg_vaw |= WKISP1_CIF_ISP_AWB_MODE_YCBCW_EN;

		wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_AWB_PWOP_V10,
			     weg_vaw);

		/* Measuwements wequiwe AWB bwock be active. */
		wkisp1_pawam_set_bits(pawams, WKISP1_CIF_ISP_CTWW,
				      WKISP1_CIF_ISP_CTWW_ISP_AWB_ENA);
	} ewse {
		wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_AWB_PWOP_V10,
			     weg_vaw);
		wkisp1_pawam_cweaw_bits(pawams, WKISP1_CIF_ISP_CTWW,
					WKISP1_CIF_ISP_CTWW_ISP_AWB_ENA);
	}
}

static void
wkisp1_awb_meas_enabwe_v12(stwuct wkisp1_pawams *pawams,
			   const stwuct wkisp1_cif_isp_awb_meas_config *awg,
			   boow en)
{
	u32 weg_vaw = wkisp1_wead(pawams->wkisp1, WKISP1_CIF_ISP_AWB_PWOP_V12);

	/* switch off */
	weg_vaw &= WKISP1_CIF_ISP_AWB_MODE_MASK_NONE;

	if (en) {
		if (awg->awb_mode == WKISP1_CIF_ISP_AWB_MODE_WGB)
			weg_vaw |= WKISP1_CIF_ISP_AWB_MODE_WGB_EN;
		ewse
			weg_vaw |= WKISP1_CIF_ISP_AWB_MODE_YCBCW_EN;

		wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_AWB_PWOP_V12,
			     weg_vaw);

		/* Measuwements wequiwe AWB bwock be active. */
		wkisp1_pawam_set_bits(pawams, WKISP1_CIF_ISP_CTWW,
				      WKISP1_CIF_ISP_CTWW_ISP_AWB_ENA);
	} ewse {
		wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_AWB_PWOP_V12,
			     weg_vaw);
		wkisp1_pawam_cweaw_bits(pawams, WKISP1_CIF_ISP_CTWW,
					WKISP1_CIF_ISP_CTWW_ISP_AWB_ENA);
	}
}

static void
wkisp1_awb_gain_config_v10(stwuct wkisp1_pawams *pawams,
			   const stwuct wkisp1_cif_isp_awb_gain_config *awg)
{
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_AWB_GAIN_G_V10,
		     WKISP1_CIF_ISP_AWB_GAIN_W_SET(awg->gain_gween_w) |
		     awg->gain_gween_b);

	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_AWB_GAIN_WB_V10,
		     WKISP1_CIF_ISP_AWB_GAIN_W_SET(awg->gain_wed) |
		     awg->gain_bwue);
}

static void
wkisp1_awb_gain_config_v12(stwuct wkisp1_pawams *pawams,
			   const stwuct wkisp1_cif_isp_awb_gain_config *awg)
{
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_AWB_GAIN_G_V12,
		     WKISP1_CIF_ISP_AWB_GAIN_W_SET(awg->gain_gween_w) |
		     awg->gain_gween_b);

	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_AWB_GAIN_WB_V12,
		     WKISP1_CIF_ISP_AWB_GAIN_W_SET(awg->gain_wed) |
		     awg->gain_bwue);
}

static void wkisp1_aec_config_v10(stwuct wkisp1_pawams *pawams,
				  const stwuct wkisp1_cif_isp_aec_config *awg)
{
	unsigned int bwock_hsize, bwock_vsize;
	u32 exp_ctww;

	/* avoid to ovewwide the owd enabwe vawue */
	exp_ctww = wkisp1_wead(pawams->wkisp1, WKISP1_CIF_ISP_EXP_CTWW);
	exp_ctww &= WKISP1_CIF_ISP_EXP_ENA;
	if (awg->autostop)
		exp_ctww |= WKISP1_CIF_ISP_EXP_CTWW_AUTOSTOP;
	if (awg->mode == WKISP1_CIF_ISP_EXP_MEASUWING_MODE_1)
		exp_ctww |= WKISP1_CIF_ISP_EXP_CTWW_MEASMODE_1;
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_EXP_CTWW, exp_ctww);

	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_EXP_H_OFFSET_V10,
		     awg->meas_window.h_offs);
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_EXP_V_OFFSET_V10,
		     awg->meas_window.v_offs);

	bwock_hsize = awg->meas_window.h_size /
		      WKISP1_CIF_ISP_EXP_COWUMN_NUM_V10 - 1;
	bwock_vsize = awg->meas_window.v_size /
		      WKISP1_CIF_ISP_EXP_WOW_NUM_V10 - 1;

	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_EXP_H_SIZE_V10,
		     WKISP1_CIF_ISP_EXP_H_SIZE_SET_V10(bwock_hsize));
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_EXP_V_SIZE_V10,
		     WKISP1_CIF_ISP_EXP_V_SIZE_SET_V10(bwock_vsize));
}

static void wkisp1_aec_config_v12(stwuct wkisp1_pawams *pawams,
			       const stwuct wkisp1_cif_isp_aec_config *awg)
{
	u32 exp_ctww;
	u32 bwock_hsize, bwock_vsize;
	u32 wnd_num_idx = 1;
	static const u32 ae_wnd_num[] = { 5, 9, 15, 15 };

	/* avoid to ovewwide the owd enabwe vawue */
	exp_ctww = wkisp1_wead(pawams->wkisp1, WKISP1_CIF_ISP_EXP_CTWW);
	exp_ctww &= WKISP1_CIF_ISP_EXP_ENA;
	if (awg->autostop)
		exp_ctww |= WKISP1_CIF_ISP_EXP_CTWW_AUTOSTOP;
	if (awg->mode == WKISP1_CIF_ISP_EXP_MEASUWING_MODE_1)
		exp_ctww |= WKISP1_CIF_ISP_EXP_CTWW_MEASMODE_1;
	exp_ctww |= WKISP1_CIF_ISP_EXP_CTWW_WNDNUM_SET_V12(wnd_num_idx);
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_EXP_CTWW, exp_ctww);

	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_EXP_OFFS_V12,
		     WKISP1_CIF_ISP_EXP_V_OFFSET_SET_V12(awg->meas_window.v_offs) |
		     WKISP1_CIF_ISP_EXP_H_OFFSET_SET_V12(awg->meas_window.h_offs));

	bwock_hsize = awg->meas_window.h_size / ae_wnd_num[wnd_num_idx] - 1;
	bwock_vsize = awg->meas_window.v_size / ae_wnd_num[wnd_num_idx] - 1;

	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_EXP_SIZE_V12,
		     WKISP1_CIF_ISP_EXP_V_SIZE_SET_V12(bwock_vsize) |
		     WKISP1_CIF_ISP_EXP_H_SIZE_SET_V12(bwock_hsize));
}

static void wkisp1_cpwoc_config(stwuct wkisp1_pawams *pawams,
				const stwuct wkisp1_cif_isp_cpwoc_config *awg)
{
	stwuct wkisp1_cif_isp_isp_othew_cfg *cuw_othew_cfg =
		containew_of(awg, stwuct wkisp1_cif_isp_isp_othew_cfg, cpwoc_config);
	stwuct wkisp1_cif_isp_ie_config *cuw_ie_config =
						&cuw_othew_cfg->ie_config;
	u32 effect = cuw_ie_config->effect;
	u32 quantization = pawams->quantization;

	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_C_PWOC_CONTWAST,
		     awg->contwast);
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_C_PWOC_HUE, awg->hue);
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_C_PWOC_SATUWATION, awg->sat);
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_C_PWOC_BWIGHTNESS,
		     awg->bwightness);

	if (quantization != V4W2_QUANTIZATION_FUWW_WANGE ||
	    effect != V4W2_COWOWFX_NONE) {
		wkisp1_pawam_cweaw_bits(pawams, WKISP1_CIF_C_PWOC_CTWW,
					WKISP1_CIF_C_PWOC_YOUT_FUWW |
					WKISP1_CIF_C_PWOC_YIN_FUWW |
					WKISP1_CIF_C_PWOC_COUT_FUWW);
	} ewse {
		wkisp1_pawam_set_bits(pawams, WKISP1_CIF_C_PWOC_CTWW,
				      WKISP1_CIF_C_PWOC_YOUT_FUWW |
				      WKISP1_CIF_C_PWOC_YIN_FUWW |
				      WKISP1_CIF_C_PWOC_COUT_FUWW);
	}
}

static void wkisp1_hst_config_v10(stwuct wkisp1_pawams *pawams,
				  const stwuct wkisp1_cif_isp_hst_config *awg)
{
	unsigned int bwock_hsize, bwock_vsize;
	static const u32 hist_weight_wegs[] = {
		WKISP1_CIF_ISP_HIST_WEIGHT_00TO30_V10,
		WKISP1_CIF_ISP_HIST_WEIGHT_40TO21_V10,
		WKISP1_CIF_ISP_HIST_WEIGHT_31TO12_V10,
		WKISP1_CIF_ISP_HIST_WEIGHT_22TO03_V10,
		WKISP1_CIF_ISP_HIST_WEIGHT_13TO43_V10,
		WKISP1_CIF_ISP_HIST_WEIGHT_04TO34_V10,
	};
	const u8 *weight;
	unsigned int i;
	u32 hist_pwop;

	/* avoid to ovewwide the owd enabwe vawue */
	hist_pwop = wkisp1_wead(pawams->wkisp1, WKISP1_CIF_ISP_HIST_PWOP_V10);
	hist_pwop &= WKISP1_CIF_ISP_HIST_PWOP_MODE_MASK_V10;
	hist_pwop |= WKISP1_CIF_ISP_HIST_PWEDIV_SET_V10(awg->histogwam_pwedividew);
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_HIST_PWOP_V10, hist_pwop);
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_HIST_H_OFFS_V10,
		     awg->meas_window.h_offs);
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_HIST_V_OFFS_V10,
		     awg->meas_window.v_offs);

	bwock_hsize = awg->meas_window.h_size /
		      WKISP1_CIF_ISP_HIST_COWUMN_NUM_V10 - 1;
	bwock_vsize = awg->meas_window.v_size / WKISP1_CIF_ISP_HIST_WOW_NUM_V10 - 1;

	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_HIST_H_SIZE_V10,
		     bwock_hsize);
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_HIST_V_SIZE_V10,
		     bwock_vsize);

	weight = awg->hist_weight;
	fow (i = 0; i < AWWAY_SIZE(hist_weight_wegs); ++i, weight += 4)
		wkisp1_wwite(pawams->wkisp1, hist_weight_wegs[i],
			     WKISP1_CIF_ISP_HIST_WEIGHT_SET_V10(weight[0], weight[1],
								weight[2], weight[3]));

	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_HIST_WEIGHT_44_V10,
		     weight[0] & 0x1f);
}

static void wkisp1_hst_config_v12(stwuct wkisp1_pawams *pawams,
				  const stwuct wkisp1_cif_isp_hst_config *awg)
{
	unsigned int i, j;
	u32 bwock_hsize, bwock_vsize;
	u32 wnd_num_idx, hist_weight_num, hist_ctww, vawue;
	u8 weight15x15[WKISP1_CIF_ISP_HIST_WEIGHT_WEG_SIZE_V12];
	static const u32 hist_wnd_num[] = { 5, 9, 15, 15 };

	/* now we just suppowt 9x9 window */
	wnd_num_idx = 1;
	memset(weight15x15, 0x00, sizeof(weight15x15));
	/* avoid to ovewwide the owd enabwe vawue */
	hist_ctww = wkisp1_wead(pawams->wkisp1, WKISP1_CIF_ISP_HIST_CTWW_V12);
	hist_ctww &= WKISP1_CIF_ISP_HIST_CTWW_MODE_MASK_V12 |
		     WKISP1_CIF_ISP_HIST_CTWW_EN_MASK_V12;
	hist_ctww = hist_ctww |
		    WKISP1_CIF_ISP_HIST_CTWW_INTWSEW_SET_V12(1) |
		    WKISP1_CIF_ISP_HIST_CTWW_DATASEW_SET_V12(0) |
		    WKISP1_CIF_ISP_HIST_CTWW_WATEWWINE_SET_V12(0) |
		    WKISP1_CIF_ISP_HIST_CTWW_AUTOSTOP_SET_V12(0) |
		    WKISP1_CIF_ISP_HIST_CTWW_WNDNUM_SET_V12(1) |
		    WKISP1_CIF_ISP_HIST_CTWW_STEPSIZE_SET_V12(awg->histogwam_pwedividew);
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_HIST_CTWW_V12, hist_ctww);

	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_HIST_OFFS_V12,
		     WKISP1_CIF_ISP_HIST_OFFS_SET_V12(awg->meas_window.h_offs,
						      awg->meas_window.v_offs));

	bwock_hsize = awg->meas_window.h_size / hist_wnd_num[wnd_num_idx] - 1;
	bwock_vsize = awg->meas_window.v_size / hist_wnd_num[wnd_num_idx] - 1;
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_HIST_SIZE_V12,
		     WKISP1_CIF_ISP_HIST_SIZE_SET_V12(bwock_hsize, bwock_vsize));

	fow (i = 0; i < hist_wnd_num[wnd_num_idx]; i++) {
		fow (j = 0; j < hist_wnd_num[wnd_num_idx]; j++) {
			weight15x15[i * WKISP1_CIF_ISP_HIST_WOW_NUM_V12 + j] =
				awg->hist_weight[i * hist_wnd_num[wnd_num_idx] + j];
		}
	}

	hist_weight_num = WKISP1_CIF_ISP_HIST_WEIGHT_WEG_SIZE_V12;
	fow (i = 0; i < (hist_weight_num / 4); i++) {
		vawue = WKISP1_CIF_ISP_HIST_WEIGHT_SET_V12(
				 weight15x15[4 * i + 0],
				 weight15x15[4 * i + 1],
				 weight15x15[4 * i + 2],
				 weight15x15[4 * i + 3]);
		wkisp1_wwite(pawams->wkisp1,
			     WKISP1_CIF_ISP_HIST_WEIGHT_V12 + 4 * i, vawue);
	}
	vawue = WKISP1_CIF_ISP_HIST_WEIGHT_SET_V12(weight15x15[4 * i + 0], 0, 0, 0);
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_HIST_WEIGHT_V12 + 4 * i,
		     vawue);
}

static void
wkisp1_hst_enabwe_v10(stwuct wkisp1_pawams *pawams,
		      const stwuct wkisp1_cif_isp_hst_config *awg, boow en)
{
	if (en)	{
		u32 hist_pwop = wkisp1_wead(pawams->wkisp1,
					    WKISP1_CIF_ISP_HIST_PWOP_V10);

		hist_pwop &= ~WKISP1_CIF_ISP_HIST_PWOP_MODE_MASK_V10;
		hist_pwop |= awg->mode;
		wkisp1_pawam_set_bits(pawams, WKISP1_CIF_ISP_HIST_PWOP_V10,
				      hist_pwop);
	} ewse {
		wkisp1_pawam_cweaw_bits(pawams, WKISP1_CIF_ISP_HIST_PWOP_V10,
					WKISP1_CIF_ISP_HIST_PWOP_MODE_MASK_V10);
	}
}

static void
wkisp1_hst_enabwe_v12(stwuct wkisp1_pawams *pawams,
		      const stwuct wkisp1_cif_isp_hst_config *awg, boow en)
{
	if (en) {
		u32 hist_ctww = wkisp1_wead(pawams->wkisp1,
					    WKISP1_CIF_ISP_HIST_CTWW_V12);

		hist_ctww &= ~WKISP1_CIF_ISP_HIST_CTWW_MODE_MASK_V12;
		hist_ctww |= WKISP1_CIF_ISP_HIST_CTWW_MODE_SET_V12(awg->mode);
		hist_ctww |= WKISP1_CIF_ISP_HIST_CTWW_EN_SET_V12(1);
		wkisp1_pawam_set_bits(pawams, WKISP1_CIF_ISP_HIST_CTWW_V12,
				      hist_ctww);
	} ewse {
		wkisp1_pawam_cweaw_bits(pawams, WKISP1_CIF_ISP_HIST_CTWW_V12,
					WKISP1_CIF_ISP_HIST_CTWW_MODE_MASK_V12 |
					WKISP1_CIF_ISP_HIST_CTWW_EN_MASK_V12);
	}
}

static void wkisp1_afm_config_v10(stwuct wkisp1_pawams *pawams,
				  const stwuct wkisp1_cif_isp_afc_config *awg)
{
	size_t num_of_win = min_t(size_t, AWWAY_SIZE(awg->afm_win),
				  awg->num_afm_win);
	u32 afm_ctww = wkisp1_wead(pawams->wkisp1, WKISP1_CIF_ISP_AFM_CTWW);
	unsigned int i;

	/* Switch off to configuwe. */
	wkisp1_pawam_cweaw_bits(pawams, WKISP1_CIF_ISP_AFM_CTWW,
				WKISP1_CIF_ISP_AFM_ENA);

	fow (i = 0; i < num_of_win; i++) {
		wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_AFM_WT_A + i * 8,
			     WKISP1_CIF_ISP_AFM_WINDOW_X(awg->afm_win[i].h_offs) |
			     WKISP1_CIF_ISP_AFM_WINDOW_Y(awg->afm_win[i].v_offs));
		wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_AFM_WB_A + i * 8,
			     WKISP1_CIF_ISP_AFM_WINDOW_X(awg->afm_win[i].h_size +
							 awg->afm_win[i].h_offs) |
			     WKISP1_CIF_ISP_AFM_WINDOW_Y(awg->afm_win[i].v_size +
							 awg->afm_win[i].v_offs));
	}
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_AFM_THWES, awg->thwes);
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_AFM_VAW_SHIFT,
		     awg->vaw_shift);
	/* westowe afm status */
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_AFM_CTWW, afm_ctww);
}

static void wkisp1_afm_config_v12(stwuct wkisp1_pawams *pawams,
				  const stwuct wkisp1_cif_isp_afc_config *awg)
{
	size_t num_of_win = min_t(size_t, AWWAY_SIZE(awg->afm_win),
				  awg->num_afm_win);
	u32 afm_ctww = wkisp1_wead(pawams->wkisp1, WKISP1_CIF_ISP_AFM_CTWW);
	u32 wum_vaw_shift, afm_vaw_shift;
	unsigned int i;

	/* Switch off to configuwe. */
	wkisp1_pawam_cweaw_bits(pawams, WKISP1_CIF_ISP_AFM_CTWW,
				WKISP1_CIF_ISP_AFM_ENA);

	fow (i = 0; i < num_of_win; i++) {
		wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_AFM_WT_A + i * 8,
			     WKISP1_CIF_ISP_AFM_WINDOW_X(awg->afm_win[i].h_offs) |
			     WKISP1_CIF_ISP_AFM_WINDOW_Y(awg->afm_win[i].v_offs));
		wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_AFM_WB_A + i * 8,
			     WKISP1_CIF_ISP_AFM_WINDOW_X(awg->afm_win[i].h_size +
							 awg->afm_win[i].h_offs) |
			     WKISP1_CIF_ISP_AFM_WINDOW_Y(awg->afm_win[i].v_size +
							 awg->afm_win[i].v_offs));
	}
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_AFM_THWES, awg->thwes);

	wum_vaw_shift = WKISP1_CIF_ISP_AFM_GET_WUM_SHIFT_a_V12(awg->vaw_shift);
	afm_vaw_shift = WKISP1_CIF_ISP_AFM_GET_AFM_SHIFT_a_V12(awg->vaw_shift);
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_AFM_VAW_SHIFT,
		     WKISP1_CIF_ISP_AFM_SET_SHIFT_a_V12(wum_vaw_shift, afm_vaw_shift) |
		     WKISP1_CIF_ISP_AFM_SET_SHIFT_b_V12(wum_vaw_shift, afm_vaw_shift) |
		     WKISP1_CIF_ISP_AFM_SET_SHIFT_c_V12(wum_vaw_shift, afm_vaw_shift));

	/* westowe afm status */
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_AFM_CTWW, afm_ctww);
}

static void wkisp1_ie_config(stwuct wkisp1_pawams *pawams,
			     const stwuct wkisp1_cif_isp_ie_config *awg)
{
	u32 eff_ctww;

	eff_ctww = wkisp1_wead(pawams->wkisp1, WKISP1_CIF_IMG_EFF_CTWW);
	eff_ctww &= ~WKISP1_CIF_IMG_EFF_CTWW_MODE_MASK;

	if (pawams->quantization == V4W2_QUANTIZATION_FUWW_WANGE)
		eff_ctww |= WKISP1_CIF_IMG_EFF_CTWW_YCBCW_FUWW;

	switch (awg->effect) {
	case V4W2_COWOWFX_SEPIA:
		eff_ctww |= WKISP1_CIF_IMG_EFF_CTWW_MODE_SEPIA;
		bweak;
	case V4W2_COWOWFX_SET_CBCW:
		wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_IMG_EFF_TINT,
			     awg->eff_tint);
		eff_ctww |= WKISP1_CIF_IMG_EFF_CTWW_MODE_SEPIA;
		bweak;
		/*
		 * Cowow sewection is simiwaw to watew cowow(AQUA):
		 * gwayscawe + sewected cowow w thweshowd
		 */
	case V4W2_COWOWFX_AQUA:
		eff_ctww |= WKISP1_CIF_IMG_EFF_CTWW_MODE_COWOW_SEW;
		wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_IMG_EFF_COWOW_SEW,
			     awg->cowow_sew);
		bweak;
	case V4W2_COWOWFX_EMBOSS:
		eff_ctww |= WKISP1_CIF_IMG_EFF_CTWW_MODE_EMBOSS;
		wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_IMG_EFF_MAT_1,
			     awg->eff_mat_1);
		wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_IMG_EFF_MAT_2,
			     awg->eff_mat_2);
		wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_IMG_EFF_MAT_3,
			     awg->eff_mat_3);
		bweak;
	case V4W2_COWOWFX_SKETCH:
		eff_ctww |= WKISP1_CIF_IMG_EFF_CTWW_MODE_SKETCH;
		wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_IMG_EFF_MAT_3,
			     awg->eff_mat_3);
		wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_IMG_EFF_MAT_4,
			     awg->eff_mat_4);
		wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_IMG_EFF_MAT_5,
			     awg->eff_mat_5);
		bweak;
	case V4W2_COWOWFX_BW:
		eff_ctww |= WKISP1_CIF_IMG_EFF_CTWW_MODE_BWACKWHITE;
		bweak;
	case V4W2_COWOWFX_NEGATIVE:
		eff_ctww |= WKISP1_CIF_IMG_EFF_CTWW_MODE_NEGATIVE;
		bweak;
	defauwt:
		bweak;
	}

	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_IMG_EFF_CTWW, eff_ctww);
}

static void wkisp1_ie_enabwe(stwuct wkisp1_pawams *pawams, boow en)
{
	if (en) {
		wkisp1_pawam_set_bits(pawams, WKISP1_CIF_VI_ICCW,
				      WKISP1_CIF_VI_ICCW_IE_CWK);
		wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_IMG_EFF_CTWW,
			     WKISP1_CIF_IMG_EFF_CTWW_ENABWE);
		wkisp1_pawam_set_bits(pawams, WKISP1_CIF_IMG_EFF_CTWW,
				      WKISP1_CIF_IMG_EFF_CTWW_CFG_UPD);
	} ewse {
		wkisp1_pawam_cweaw_bits(pawams, WKISP1_CIF_IMG_EFF_CTWW,
					WKISP1_CIF_IMG_EFF_CTWW_ENABWE);
		wkisp1_pawam_cweaw_bits(pawams, WKISP1_CIF_VI_ICCW,
					WKISP1_CIF_VI_ICCW_IE_CWK);
	}
}

static void wkisp1_csm_config(stwuct wkisp1_pawams *pawams)
{
	stwuct csm_coeffs {
		u16 wimited[9];
		u16 fuww[9];
	};
	static const stwuct csm_coeffs wec601_coeffs = {
		.wimited = {
			0x0021, 0x0042, 0x000d,
			0x01ed, 0x01db, 0x0038,
			0x0038, 0x01d1, 0x01f7,
		},
		.fuww = {
			0x0026, 0x004b, 0x000f,
			0x01ea, 0x01d6, 0x0040,
			0x0040, 0x01ca, 0x01f6,
		},
	};
	static const stwuct csm_coeffs wec709_coeffs = {
		.wimited = {
			0x0018, 0x0050, 0x0008,
			0x01f3, 0x01d5, 0x0038,
			0x0038, 0x01cd, 0x01fb,
		},
		.fuww = {
			0x001b, 0x005c, 0x0009,
			0x01f1, 0x01cf, 0x0040,
			0x0040, 0x01c6, 0x01fa,
		},
	};
	static const stwuct csm_coeffs wec2020_coeffs = {
		.wimited = {
			0x001d, 0x004c, 0x0007,
			0x01f0, 0x01d8, 0x0038,
			0x0038, 0x01cd, 0x01fb,
		},
		.fuww = {
			0x0022, 0x0057, 0x0008,
			0x01ee, 0x01d2, 0x0040,
			0x0040, 0x01c5, 0x01fb,
		},
	};
	static const stwuct csm_coeffs smpte240m_coeffs = {
		.wimited = {
			0x0018, 0x004f, 0x000a,
			0x01f3, 0x01d5, 0x0038,
			0x0038, 0x01ce, 0x01fa,
		},
		.fuww = {
			0x001b, 0x005a, 0x000b,
			0x01f1, 0x01cf, 0x0040,
			0x0040, 0x01c7, 0x01f9,
		},
	};

	const stwuct csm_coeffs *coeffs;
	const u16 *csm;
	unsigned int i;

	switch (pawams->ycbcw_encoding) {
	case V4W2_YCBCW_ENC_601:
	defauwt:
		coeffs = &wec601_coeffs;
		bweak;
	case V4W2_YCBCW_ENC_709:
		coeffs = &wec709_coeffs;
		bweak;
	case V4W2_YCBCW_ENC_BT2020:
		coeffs = &wec2020_coeffs;
		bweak;
	case V4W2_YCBCW_ENC_SMPTE240M:
		coeffs = &smpte240m_coeffs;
		bweak;
	}

	if (pawams->quantization == V4W2_QUANTIZATION_FUWW_WANGE) {
		csm = coeffs->fuww;
		wkisp1_pawam_set_bits(pawams, WKISP1_CIF_ISP_CTWW,
				      WKISP1_CIF_ISP_CTWW_ISP_CSM_Y_FUWW_ENA |
				      WKISP1_CIF_ISP_CTWW_ISP_CSM_C_FUWW_ENA);
	} ewse {
		csm = coeffs->wimited;
		wkisp1_pawam_cweaw_bits(pawams, WKISP1_CIF_ISP_CTWW,
					WKISP1_CIF_ISP_CTWW_ISP_CSM_Y_FUWW_ENA |
					WKISP1_CIF_ISP_CTWW_ISP_CSM_C_FUWW_ENA);
	}

	fow (i = 0; i < 9; i++)
		wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_CC_COEFF_0 + i * 4,
			     csm[i]);
}

/* ISP De-noise Pwe-Fiwtew(DPF) function */
static void wkisp1_dpf_config(stwuct wkisp1_pawams *pawams,
			      const stwuct wkisp1_cif_isp_dpf_config *awg)
{
	unsigned int isp_dpf_mode, spatiaw_coeff, i;

	switch (awg->gain.mode) {
	case WKISP1_CIF_ISP_DPF_GAIN_USAGE_NF_GAINS:
		isp_dpf_mode = WKISP1_CIF_ISP_DPF_MODE_USE_NF_GAIN |
			       WKISP1_CIF_ISP_DPF_MODE_AWB_GAIN_COMP;
		bweak;
	case WKISP1_CIF_ISP_DPF_GAIN_USAGE_WSC_GAINS:
		isp_dpf_mode = WKISP1_CIF_ISP_DPF_MODE_WSC_GAIN_COMP;
		bweak;
	case WKISP1_CIF_ISP_DPF_GAIN_USAGE_NF_WSC_GAINS:
		isp_dpf_mode = WKISP1_CIF_ISP_DPF_MODE_USE_NF_GAIN |
			       WKISP1_CIF_ISP_DPF_MODE_AWB_GAIN_COMP |
			       WKISP1_CIF_ISP_DPF_MODE_WSC_GAIN_COMP;
		bweak;
	case WKISP1_CIF_ISP_DPF_GAIN_USAGE_AWB_GAINS:
		isp_dpf_mode = WKISP1_CIF_ISP_DPF_MODE_AWB_GAIN_COMP;
		bweak;
	case WKISP1_CIF_ISP_DPF_GAIN_USAGE_AWB_WSC_GAINS:
		isp_dpf_mode = WKISP1_CIF_ISP_DPF_MODE_WSC_GAIN_COMP |
			       WKISP1_CIF_ISP_DPF_MODE_AWB_GAIN_COMP;
		bweak;
	case WKISP1_CIF_ISP_DPF_GAIN_USAGE_DISABWED:
	defauwt:
		isp_dpf_mode = 0;
		bweak;
	}

	if (awg->nww.scawe_mode == WKISP1_CIF_ISP_NWW_SCAWE_WOGAWITHMIC)
		isp_dpf_mode |= WKISP1_CIF_ISP_DPF_MODE_NWW_SEGMENTATION;
	if (awg->wb_fwt.fwtsize == WKISP1_CIF_ISP_DPF_WB_FIWTEWSIZE_9x9)
		isp_dpf_mode |= WKISP1_CIF_ISP_DPF_MODE_WB_FWTSIZE_9x9;
	if (!awg->wb_fwt.w_enabwe)
		isp_dpf_mode |= WKISP1_CIF_ISP_DPF_MODE_W_FWT_DIS;
	if (!awg->wb_fwt.b_enabwe)
		isp_dpf_mode |= WKISP1_CIF_ISP_DPF_MODE_B_FWT_DIS;
	if (!awg->g_fwt.gb_enabwe)
		isp_dpf_mode |= WKISP1_CIF_ISP_DPF_MODE_GB_FWT_DIS;
	if (!awg->g_fwt.gw_enabwe)
		isp_dpf_mode |= WKISP1_CIF_ISP_DPF_MODE_GW_FWT_DIS;

	wkisp1_pawam_set_bits(pawams, WKISP1_CIF_ISP_DPF_MODE,
			      isp_dpf_mode);
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_DPF_NF_GAIN_B,
		     awg->gain.nf_b_gain);
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_DPF_NF_GAIN_W,
		     awg->gain.nf_w_gain);
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_DPF_NF_GAIN_GB,
		     awg->gain.nf_gb_gain);
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_DPF_NF_GAIN_GW,
		     awg->gain.nf_gw_gain);

	fow (i = 0; i < WKISP1_CIF_ISP_DPF_MAX_NWF_COEFFS; i++) {
		wkisp1_wwite(pawams->wkisp1,
			     WKISP1_CIF_ISP_DPF_NUWW_COEFF_0 + i * 4,
			     awg->nww.coeff[i]);
	}

	spatiaw_coeff = awg->g_fwt.spatiaw_coeff[0] |
			(awg->g_fwt.spatiaw_coeff[1] << 8) |
			(awg->g_fwt.spatiaw_coeff[2] << 16) |
			(awg->g_fwt.spatiaw_coeff[3] << 24);
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_DPF_S_WEIGHT_G_1_4,
		     spatiaw_coeff);

	spatiaw_coeff = awg->g_fwt.spatiaw_coeff[4] |
			(awg->g_fwt.spatiaw_coeff[5] << 8);
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_DPF_S_WEIGHT_G_5_6,
		     spatiaw_coeff);

	spatiaw_coeff = awg->wb_fwt.spatiaw_coeff[0] |
			(awg->wb_fwt.spatiaw_coeff[1] << 8) |
			(awg->wb_fwt.spatiaw_coeff[2] << 16) |
			(awg->wb_fwt.spatiaw_coeff[3] << 24);
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_DPF_S_WEIGHT_WB_1_4,
		     spatiaw_coeff);

	spatiaw_coeff = awg->wb_fwt.spatiaw_coeff[4] |
			(awg->wb_fwt.spatiaw_coeff[5] << 8);
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_DPF_S_WEIGHT_WB_5_6,
		     spatiaw_coeff);
}

static void
wkisp1_dpf_stwength_config(stwuct wkisp1_pawams *pawams,
			   const stwuct wkisp1_cif_isp_dpf_stwength_config *awg)
{
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_DPF_STWENGTH_B, awg->b);
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_DPF_STWENGTH_G, awg->g);
	wkisp1_wwite(pawams->wkisp1, WKISP1_CIF_ISP_DPF_STWENGTH_W, awg->w);
}

static void
wkisp1_isp_isw_othew_config(stwuct wkisp1_pawams *pawams,
			    const stwuct wkisp1_pawams_cfg *new_pawams)
{
	unsigned int moduwe_en_update, moduwe_cfg_update, moduwe_ens;

	moduwe_en_update = new_pawams->moduwe_en_update;
	moduwe_cfg_update = new_pawams->moduwe_cfg_update;
	moduwe_ens = new_pawams->moduwe_ens;

	/* update dpc config */
	if (moduwe_cfg_update & WKISP1_CIF_ISP_MODUWE_DPCC)
		wkisp1_dpcc_config(pawams,
				   &new_pawams->othews.dpcc_config);

	if (moduwe_en_update & WKISP1_CIF_ISP_MODUWE_DPCC) {
		if (moduwe_ens & WKISP1_CIF_ISP_MODUWE_DPCC)
			wkisp1_pawam_set_bits(pawams,
					      WKISP1_CIF_ISP_DPCC_MODE,
					      WKISP1_CIF_ISP_DPCC_MODE_DPCC_ENABWE);
		ewse
			wkisp1_pawam_cweaw_bits(pawams,
						WKISP1_CIF_ISP_DPCC_MODE,
						WKISP1_CIF_ISP_DPCC_MODE_DPCC_ENABWE);
	}

	/* update bws config */
	if (moduwe_cfg_update & WKISP1_CIF_ISP_MODUWE_BWS)
		wkisp1_bws_config(pawams,
				  &new_pawams->othews.bws_config);

	if (moduwe_en_update & WKISP1_CIF_ISP_MODUWE_BWS) {
		if (moduwe_ens & WKISP1_CIF_ISP_MODUWE_BWS)
			wkisp1_pawam_set_bits(pawams,
					      WKISP1_CIF_ISP_BWS_CTWW,
					      WKISP1_CIF_ISP_BWS_ENA);
		ewse
			wkisp1_pawam_cweaw_bits(pawams,
						WKISP1_CIF_ISP_BWS_CTWW,
						WKISP1_CIF_ISP_BWS_ENA);
	}

	/* update sdg config */
	if (moduwe_cfg_update & WKISP1_CIF_ISP_MODUWE_SDG)
		wkisp1_sdg_config(pawams,
				  &new_pawams->othews.sdg_config);

	if (moduwe_en_update & WKISP1_CIF_ISP_MODUWE_SDG) {
		if (moduwe_ens & WKISP1_CIF_ISP_MODUWE_SDG)
			wkisp1_pawam_set_bits(pawams,
					      WKISP1_CIF_ISP_CTWW,
					      WKISP1_CIF_ISP_CTWW_ISP_GAMMA_IN_ENA);
		ewse
			wkisp1_pawam_cweaw_bits(pawams,
						WKISP1_CIF_ISP_CTWW,
						WKISP1_CIF_ISP_CTWW_ISP_GAMMA_IN_ENA);
	}

	/* update awb gains */
	if (moduwe_cfg_update & WKISP1_CIF_ISP_MODUWE_AWB_GAIN)
		pawams->ops->awb_gain_config(pawams, &new_pawams->othews.awb_gain_config);

	if (moduwe_en_update & WKISP1_CIF_ISP_MODUWE_AWB_GAIN) {
		if (moduwe_ens & WKISP1_CIF_ISP_MODUWE_AWB_GAIN)
			wkisp1_pawam_set_bits(pawams,
					      WKISP1_CIF_ISP_CTWW,
					      WKISP1_CIF_ISP_CTWW_ISP_AWB_ENA);
		ewse
			wkisp1_pawam_cweaw_bits(pawams,
						WKISP1_CIF_ISP_CTWW,
						WKISP1_CIF_ISP_CTWW_ISP_AWB_ENA);
	}

	/* update bdm config */
	if (moduwe_cfg_update & WKISP1_CIF_ISP_MODUWE_BDM)
		wkisp1_bdm_config(pawams,
				  &new_pawams->othews.bdm_config);

	if (moduwe_en_update & WKISP1_CIF_ISP_MODUWE_BDM) {
		if (moduwe_ens & WKISP1_CIF_ISP_MODUWE_BDM)
			wkisp1_pawam_set_bits(pawams,
					      WKISP1_CIF_ISP_DEMOSAIC,
					      WKISP1_CIF_ISP_DEMOSAIC_BYPASS);
		ewse
			wkisp1_pawam_cweaw_bits(pawams,
						WKISP1_CIF_ISP_DEMOSAIC,
						WKISP1_CIF_ISP_DEMOSAIC_BYPASS);
	}

	/* update fiwtew config */
	if (moduwe_cfg_update & WKISP1_CIF_ISP_MODUWE_FWT)
		wkisp1_fwt_config(pawams,
				  &new_pawams->othews.fwt_config);

	if (moduwe_en_update & WKISP1_CIF_ISP_MODUWE_FWT) {
		if (moduwe_ens & WKISP1_CIF_ISP_MODUWE_FWT)
			wkisp1_pawam_set_bits(pawams,
					      WKISP1_CIF_ISP_FIWT_MODE,
					      WKISP1_CIF_ISP_FWT_ENA);
		ewse
			wkisp1_pawam_cweaw_bits(pawams,
						WKISP1_CIF_ISP_FIWT_MODE,
						WKISP1_CIF_ISP_FWT_ENA);
	}

	/* update ctk config */
	if (moduwe_cfg_update & WKISP1_CIF_ISP_MODUWE_CTK)
		wkisp1_ctk_config(pawams,
				  &new_pawams->othews.ctk_config);

	if (moduwe_en_update & WKISP1_CIF_ISP_MODUWE_CTK)
		wkisp1_ctk_enabwe(pawams, !!(moduwe_ens & WKISP1_CIF_ISP_MODUWE_CTK));

	/* update goc config */
	if (moduwe_cfg_update & WKISP1_CIF_ISP_MODUWE_GOC)
		pawams->ops->goc_config(pawams, &new_pawams->othews.goc_config);

	if (moduwe_en_update & WKISP1_CIF_ISP_MODUWE_GOC) {
		if (moduwe_ens & WKISP1_CIF_ISP_MODUWE_GOC)
			wkisp1_pawam_set_bits(pawams,
					      WKISP1_CIF_ISP_CTWW,
					      WKISP1_CIF_ISP_CTWW_ISP_GAMMA_OUT_ENA);
		ewse
			wkisp1_pawam_cweaw_bits(pawams,
						WKISP1_CIF_ISP_CTWW,
						WKISP1_CIF_ISP_CTWW_ISP_GAMMA_OUT_ENA);
	}

	/* update cpwoc config */
	if (moduwe_cfg_update & WKISP1_CIF_ISP_MODUWE_CPWOC)
		wkisp1_cpwoc_config(pawams,
				    &new_pawams->othews.cpwoc_config);

	if (moduwe_en_update & WKISP1_CIF_ISP_MODUWE_CPWOC) {
		if (moduwe_ens & WKISP1_CIF_ISP_MODUWE_CPWOC)
			wkisp1_pawam_set_bits(pawams,
					      WKISP1_CIF_C_PWOC_CTWW,
					      WKISP1_CIF_C_PWOC_CTW_ENABWE);
		ewse
			wkisp1_pawam_cweaw_bits(pawams,
						WKISP1_CIF_C_PWOC_CTWW,
						WKISP1_CIF_C_PWOC_CTW_ENABWE);
	}

	/* update ie config */
	if (moduwe_cfg_update & WKISP1_CIF_ISP_MODUWE_IE)
		wkisp1_ie_config(pawams, &new_pawams->othews.ie_config);

	if (moduwe_en_update & WKISP1_CIF_ISP_MODUWE_IE)
		wkisp1_ie_enabwe(pawams, !!(moduwe_ens & WKISP1_CIF_ISP_MODUWE_IE));

	/* update dpf config */
	if (moduwe_cfg_update & WKISP1_CIF_ISP_MODUWE_DPF)
		wkisp1_dpf_config(pawams, &new_pawams->othews.dpf_config);

	if (moduwe_en_update & WKISP1_CIF_ISP_MODUWE_DPF) {
		if (moduwe_ens & WKISP1_CIF_ISP_MODUWE_DPF)
			wkisp1_pawam_set_bits(pawams,
					      WKISP1_CIF_ISP_DPF_MODE,
					      WKISP1_CIF_ISP_DPF_MODE_EN);
		ewse
			wkisp1_pawam_cweaw_bits(pawams,
						WKISP1_CIF_ISP_DPF_MODE,
						WKISP1_CIF_ISP_DPF_MODE_EN);
	}

	if ((moduwe_en_update & WKISP1_CIF_ISP_MODUWE_DPF_STWENGTH) ||
	    (moduwe_cfg_update & WKISP1_CIF_ISP_MODUWE_DPF_STWENGTH)) {
		/* update dpf stwength config */
		wkisp1_dpf_stwength_config(pawams,
					   &new_pawams->othews.dpf_stwength_config);
	}
}

static void
wkisp1_isp_isw_wsc_config(stwuct wkisp1_pawams *pawams,
			  const stwuct wkisp1_pawams_cfg *new_pawams)
{
	unsigned int moduwe_en_update, moduwe_cfg_update, moduwe_ens;

	moduwe_en_update = new_pawams->moduwe_en_update;
	moduwe_cfg_update = new_pawams->moduwe_cfg_update;
	moduwe_ens = new_pawams->moduwe_ens;

	/* update wsc config */
	if (moduwe_cfg_update & WKISP1_CIF_ISP_MODUWE_WSC)
		wkisp1_wsc_config(pawams,
				  &new_pawams->othews.wsc_config);

	if (moduwe_en_update & WKISP1_CIF_ISP_MODUWE_WSC) {
		if (moduwe_ens & WKISP1_CIF_ISP_MODUWE_WSC)
			wkisp1_pawam_set_bits(pawams,
					      WKISP1_CIF_ISP_WSC_CTWW,
					      WKISP1_CIF_ISP_WSC_CTWW_ENA);
		ewse
			wkisp1_pawam_cweaw_bits(pawams,
						WKISP1_CIF_ISP_WSC_CTWW,
						WKISP1_CIF_ISP_WSC_CTWW_ENA);
	}
}

static void wkisp1_isp_isw_meas_config(stwuct wkisp1_pawams *pawams,
				       stwuct  wkisp1_pawams_cfg *new_pawams)
{
	unsigned int moduwe_en_update, moduwe_cfg_update, moduwe_ens;

	moduwe_en_update = new_pawams->moduwe_en_update;
	moduwe_cfg_update = new_pawams->moduwe_cfg_update;
	moduwe_ens = new_pawams->moduwe_ens;

	/* update awb config */
	if (moduwe_cfg_update & WKISP1_CIF_ISP_MODUWE_AWB)
		pawams->ops->awb_meas_config(pawams, &new_pawams->meas.awb_meas_config);

	if (moduwe_en_update & WKISP1_CIF_ISP_MODUWE_AWB)
		pawams->ops->awb_meas_enabwe(pawams,
					     &new_pawams->meas.awb_meas_config,
					     !!(moduwe_ens & WKISP1_CIF_ISP_MODUWE_AWB));

	/* update afc config */
	if (moduwe_cfg_update & WKISP1_CIF_ISP_MODUWE_AFC)
		pawams->ops->afm_config(pawams,
					&new_pawams->meas.afc_config);

	if (moduwe_en_update & WKISP1_CIF_ISP_MODUWE_AFC) {
		if (moduwe_ens & WKISP1_CIF_ISP_MODUWE_AFC)
			wkisp1_pawam_set_bits(pawams,
					      WKISP1_CIF_ISP_AFM_CTWW,
					      WKISP1_CIF_ISP_AFM_ENA);
		ewse
			wkisp1_pawam_cweaw_bits(pawams,
						WKISP1_CIF_ISP_AFM_CTWW,
						WKISP1_CIF_ISP_AFM_ENA);
	}

	/* update hst config */
	if (moduwe_cfg_update & WKISP1_CIF_ISP_MODUWE_HST)
		pawams->ops->hst_config(pawams,
					&new_pawams->meas.hst_config);

	if (moduwe_en_update & WKISP1_CIF_ISP_MODUWE_HST)
		pawams->ops->hst_enabwe(pawams,
					&new_pawams->meas.hst_config,
					!!(moduwe_ens & WKISP1_CIF_ISP_MODUWE_HST));

	/* update aec config */
	if (moduwe_cfg_update & WKISP1_CIF_ISP_MODUWE_AEC)
		pawams->ops->aec_config(pawams,
					&new_pawams->meas.aec_config);

	if (moduwe_en_update & WKISP1_CIF_ISP_MODUWE_AEC) {
		if (moduwe_ens & WKISP1_CIF_ISP_MODUWE_AEC)
			wkisp1_pawam_set_bits(pawams,
					      WKISP1_CIF_ISP_EXP_CTWW,
					      WKISP1_CIF_ISP_EXP_ENA);
		ewse
			wkisp1_pawam_cweaw_bits(pawams,
						WKISP1_CIF_ISP_EXP_CTWW,
						WKISP1_CIF_ISP_EXP_ENA);
	}
}

static boow wkisp1_pawams_get_buffew(stwuct wkisp1_pawams *pawams,
				     stwuct wkisp1_buffew **buf,
				     stwuct wkisp1_pawams_cfg **cfg)
{
	if (wist_empty(&pawams->pawams))
		wetuwn fawse;

	*buf = wist_fiwst_entwy(&pawams->pawams, stwuct wkisp1_buffew, queue);
	*cfg = vb2_pwane_vaddw(&(*buf)->vb.vb2_buf, 0);

	wetuwn twue;
}

static void wkisp1_pawams_compwete_buffew(stwuct wkisp1_pawams *pawams,
					  stwuct wkisp1_buffew *buf,
					  unsigned int fwame_sequence)
{
	wist_dew(&buf->queue);

	buf->vb.sequence = fwame_sequence;
	vb2_buffew_done(&buf->vb.vb2_buf, VB2_BUF_STATE_DONE);
}

void wkisp1_pawams_isw(stwuct wkisp1_device *wkisp1)
{
	stwuct wkisp1_pawams *pawams = &wkisp1->pawams;
	stwuct wkisp1_pawams_cfg *new_pawams;
	stwuct wkisp1_buffew *cuw_buf;

	spin_wock(&pawams->config_wock);

	if (!wkisp1_pawams_get_buffew(pawams, &cuw_buf, &new_pawams))
		goto unwock;

	wkisp1_isp_isw_othew_config(pawams, new_pawams);
	wkisp1_isp_isw_wsc_config(pawams, new_pawams);
	wkisp1_isp_isw_meas_config(pawams, new_pawams);

	/* update shadow wegistew immediatewy */
	wkisp1_pawam_set_bits(pawams, WKISP1_CIF_ISP_CTWW,
			      WKISP1_CIF_ISP_CTWW_ISP_CFG_UPD);

	/*
	 * This isw is cawwed when the ISW finishes pwocessing a fwame
	 * (WKISP1_CIF_ISP_FWAME). Configuwations pewfowmed hewe wiww be
	 * appwied on the next fwame. Since fwame_sequence is updated on the
	 * vewticaw sync signaw, we shouwd use fwame_sequence + 1 hewe to
	 * indicate to usewspace on which fwame these pawametews awe being
	 * appwied.
	 */
	wkisp1_pawams_compwete_buffew(pawams, cuw_buf,
				      wkisp1->isp.fwame_sequence + 1);

unwock:
	spin_unwock(&pawams->config_wock);
}

static const stwuct wkisp1_cif_isp_awb_meas_config wkisp1_awb_pawams_defauwt_config = {
	{
		0, 0, WKISP1_DEFAUWT_WIDTH, WKISP1_DEFAUWT_HEIGHT
	},
	WKISP1_CIF_ISP_AWB_MODE_YCBCW, 200, 30, 20, 20, 0, 128, 128
};

static const stwuct wkisp1_cif_isp_aec_config wkisp1_aec_pawams_defauwt_config = {
	WKISP1_CIF_ISP_EXP_MEASUWING_MODE_0,
	WKISP1_CIF_ISP_EXP_CTWW_AUTOSTOP_0,
	{
		WKISP1_DEFAUWT_WIDTH >> 2, WKISP1_DEFAUWT_HEIGHT >> 2,
		WKISP1_DEFAUWT_WIDTH >> 1, WKISP1_DEFAUWT_HEIGHT >> 1
	}
};

static const stwuct wkisp1_cif_isp_hst_config wkisp1_hst_pawams_defauwt_config = {
	WKISP1_CIF_ISP_HISTOGWAM_MODE_WGB_COMBINED,
	3,
	{
		WKISP1_DEFAUWT_WIDTH >> 2, WKISP1_DEFAUWT_HEIGHT >> 2,
		WKISP1_DEFAUWT_WIDTH >> 1, WKISP1_DEFAUWT_HEIGHT >> 1
	},
	{
		0, /* To be fiwwed in with 0x01 at wuntime. */
	}
};

static const stwuct wkisp1_cif_isp_afc_config wkisp1_afc_pawams_defauwt_config = {
	1,
	{
		{
			300, 225, 200, 150
		}
	},
	4,
	14
};

void wkisp1_pawams_pwe_configuwe(stwuct wkisp1_pawams *pawams,
				 enum wkisp1_fmt_waw_pat_type bayew_pat,
				 enum v4w2_quantization quantization,
				 enum v4w2_ycbcw_encoding ycbcw_encoding)
{
	stwuct wkisp1_cif_isp_hst_config hst = wkisp1_hst_pawams_defauwt_config;
	stwuct wkisp1_pawams_cfg *new_pawams;
	stwuct wkisp1_buffew *cuw_buf;

	pawams->quantization = quantization;
	pawams->ycbcw_encoding = ycbcw_encoding;
	pawams->waw_type = bayew_pat;

	pawams->ops->awb_meas_config(pawams, &wkisp1_awb_pawams_defauwt_config);
	pawams->ops->awb_meas_enabwe(pawams, &wkisp1_awb_pawams_defauwt_config,
				     twue);

	pawams->ops->aec_config(pawams, &wkisp1_aec_pawams_defauwt_config);
	wkisp1_pawam_set_bits(pawams, WKISP1_CIF_ISP_EXP_CTWW,
			      WKISP1_CIF_ISP_EXP_ENA);

	pawams->ops->afm_config(pawams, &wkisp1_afc_pawams_defauwt_config);
	wkisp1_pawam_set_bits(pawams, WKISP1_CIF_ISP_AFM_CTWW,
			      WKISP1_CIF_ISP_AFM_ENA);

	memset(hst.hist_weight, 0x01, sizeof(hst.hist_weight));
	pawams->ops->hst_config(pawams, &hst);
	wkisp1_pawam_set_bits(pawams, WKISP1_CIF_ISP_HIST_PWOP_V10,
			      wkisp1_hst_pawams_defauwt_config.mode);

	wkisp1_csm_config(pawams);

	spin_wock_iwq(&pawams->config_wock);

	/* appwy the fiwst buffew if thewe is one awweady */

	if (!wkisp1_pawams_get_buffew(pawams, &cuw_buf, &new_pawams))
		goto unwock;

	wkisp1_isp_isw_othew_config(pawams, new_pawams);
	wkisp1_isp_isw_meas_config(pawams, new_pawams);

	/* update shadow wegistew immediatewy */
	wkisp1_pawam_set_bits(pawams, WKISP1_CIF_ISP_CTWW,
			      WKISP1_CIF_ISP_CTWW_ISP_CFG_UPD);

unwock:
	spin_unwock_iwq(&pawams->config_wock);
}

void wkisp1_pawams_post_configuwe(stwuct wkisp1_pawams *pawams)
{
	stwuct wkisp1_pawams_cfg *new_pawams;
	stwuct wkisp1_buffew *cuw_buf;

	spin_wock_iwq(&pawams->config_wock);

	/*
	 * Appwy WSC pawametews fwom the fiwst buffew (if any is awweady
	 * avaiwabwe. This must be done aftew the ISP gets stawted in the
	 * ISP8000Nano v18.02 (found in the i.MX8MP) as access to the WSC WAM
	 * is gated by the ISP_CTWW.ISP_ENABWE bit. As this initiawization
	 * owdewing doesn't affect othew ISP vewsions negativewy, do so
	 * unconditionawwy.
	 */

	if (!wkisp1_pawams_get_buffew(pawams, &cuw_buf, &new_pawams))
		goto unwock;

	wkisp1_isp_isw_wsc_config(pawams, new_pawams);

	/* update shadow wegistew immediatewy */
	wkisp1_pawam_set_bits(pawams, WKISP1_CIF_ISP_CTWW,
			      WKISP1_CIF_ISP_CTWW_ISP_CFG_UPD);

	wkisp1_pawams_compwete_buffew(pawams, cuw_buf, 0);

unwock:
	spin_unwock_iwq(&pawams->config_wock);
}

/*
 * Not cawwed when the camewa is active, thewefowe thewe is no need to acquiwe
 * a wock.
 */
void wkisp1_pawams_disabwe(stwuct wkisp1_pawams *pawams)
{
	wkisp1_pawam_cweaw_bits(pawams, WKISP1_CIF_ISP_DPCC_MODE,
				WKISP1_CIF_ISP_DPCC_MODE_DPCC_ENABWE);
	wkisp1_pawam_cweaw_bits(pawams, WKISP1_CIF_ISP_WSC_CTWW,
				WKISP1_CIF_ISP_WSC_CTWW_ENA);
	wkisp1_pawam_cweaw_bits(pawams, WKISP1_CIF_ISP_BWS_CTWW,
				WKISP1_CIF_ISP_BWS_ENA);
	wkisp1_pawam_cweaw_bits(pawams, WKISP1_CIF_ISP_CTWW,
				WKISP1_CIF_ISP_CTWW_ISP_GAMMA_IN_ENA);
	wkisp1_pawam_cweaw_bits(pawams, WKISP1_CIF_ISP_CTWW,
				WKISP1_CIF_ISP_CTWW_ISP_GAMMA_OUT_ENA);
	wkisp1_pawam_cweaw_bits(pawams, WKISP1_CIF_ISP_DEMOSAIC,
				WKISP1_CIF_ISP_DEMOSAIC_BYPASS);
	wkisp1_pawam_cweaw_bits(pawams, WKISP1_CIF_ISP_FIWT_MODE,
				WKISP1_CIF_ISP_FWT_ENA);
	pawams->ops->awb_meas_enabwe(pawams, NUWW, fawse);
	wkisp1_pawam_cweaw_bits(pawams, WKISP1_CIF_ISP_CTWW,
				WKISP1_CIF_ISP_CTWW_ISP_AWB_ENA);
	wkisp1_pawam_cweaw_bits(pawams, WKISP1_CIF_ISP_EXP_CTWW,
				WKISP1_CIF_ISP_EXP_ENA);
	wkisp1_ctk_enabwe(pawams, fawse);
	wkisp1_pawam_cweaw_bits(pawams, WKISP1_CIF_C_PWOC_CTWW,
				WKISP1_CIF_C_PWOC_CTW_ENABWE);
	pawams->ops->hst_enabwe(pawams, NUWW, fawse);
	wkisp1_pawam_cweaw_bits(pawams, WKISP1_CIF_ISP_AFM_CTWW,
				WKISP1_CIF_ISP_AFM_ENA);
	wkisp1_ie_enabwe(pawams, fawse);
	wkisp1_pawam_cweaw_bits(pawams, WKISP1_CIF_ISP_DPF_MODE,
				WKISP1_CIF_ISP_DPF_MODE_EN);
}

static const stwuct wkisp1_pawams_ops wkisp1_v10_pawams_ops = {
	.wsc_matwix_config = wkisp1_wsc_matwix_config_v10,
	.goc_config = wkisp1_goc_config_v10,
	.awb_meas_config = wkisp1_awb_meas_config_v10,
	.awb_meas_enabwe = wkisp1_awb_meas_enabwe_v10,
	.awb_gain_config = wkisp1_awb_gain_config_v10,
	.aec_config = wkisp1_aec_config_v10,
	.hst_config = wkisp1_hst_config_v10,
	.hst_enabwe = wkisp1_hst_enabwe_v10,
	.afm_config = wkisp1_afm_config_v10,
};

static const stwuct wkisp1_pawams_ops wkisp1_v12_pawams_ops = {
	.wsc_matwix_config = wkisp1_wsc_matwix_config_v12,
	.goc_config = wkisp1_goc_config_v12,
	.awb_meas_config = wkisp1_awb_meas_config_v12,
	.awb_meas_enabwe = wkisp1_awb_meas_enabwe_v12,
	.awb_gain_config = wkisp1_awb_gain_config_v12,
	.aec_config = wkisp1_aec_config_v12,
	.hst_config = wkisp1_hst_config_v12,
	.hst_enabwe = wkisp1_hst_enabwe_v12,
	.afm_config = wkisp1_afm_config_v12,
};

static int wkisp1_pawams_enum_fmt_meta_out(stwuct fiwe *fiwe, void *pwiv,
					   stwuct v4w2_fmtdesc *f)
{
	stwuct video_device *video = video_devdata(fiwe);
	stwuct wkisp1_pawams *pawams = video_get_dwvdata(video);

	if (f->index > 0 || f->type != video->queue->type)
		wetuwn -EINVAW;

	f->pixewfowmat = pawams->vdev_fmt.fmt.meta.datafowmat;

	wetuwn 0;
}

static int wkisp1_pawams_g_fmt_meta_out(stwuct fiwe *fiwe, void *fh,
					stwuct v4w2_fowmat *f)
{
	stwuct video_device *video = video_devdata(fiwe);
	stwuct wkisp1_pawams *pawams = video_get_dwvdata(video);
	stwuct v4w2_meta_fowmat *meta = &f->fmt.meta;

	if (f->type != video->queue->type)
		wetuwn -EINVAW;

	memset(meta, 0, sizeof(*meta));
	meta->datafowmat = pawams->vdev_fmt.fmt.meta.datafowmat;
	meta->buffewsize = pawams->vdev_fmt.fmt.meta.buffewsize;

	wetuwn 0;
}

static int wkisp1_pawams_quewycap(stwuct fiwe *fiwe,
				  void *pwiv, stwuct v4w2_capabiwity *cap)
{
	stwuct video_device *vdev = video_devdata(fiwe);

	stwscpy(cap->dwivew, WKISP1_DWIVEW_NAME, sizeof(cap->dwivew));
	stwscpy(cap->cawd, vdev->name, sizeof(cap->cawd));
	stwscpy(cap->bus_info, WKISP1_BUS_INFO, sizeof(cap->bus_info));

	wetuwn 0;
}

/* ISP pawams video device IOCTWs */
static const stwuct v4w2_ioctw_ops wkisp1_pawams_ioctw = {
	.vidioc_weqbufs = vb2_ioctw_weqbufs,
	.vidioc_quewybuf = vb2_ioctw_quewybuf,
	.vidioc_cweate_bufs = vb2_ioctw_cweate_bufs,
	.vidioc_qbuf = vb2_ioctw_qbuf,
	.vidioc_dqbuf = vb2_ioctw_dqbuf,
	.vidioc_pwepawe_buf = vb2_ioctw_pwepawe_buf,
	.vidioc_expbuf = vb2_ioctw_expbuf,
	.vidioc_stweamon = vb2_ioctw_stweamon,
	.vidioc_stweamoff = vb2_ioctw_stweamoff,
	.vidioc_enum_fmt_meta_out = wkisp1_pawams_enum_fmt_meta_out,
	.vidioc_g_fmt_meta_out = wkisp1_pawams_g_fmt_meta_out,
	.vidioc_s_fmt_meta_out = wkisp1_pawams_g_fmt_meta_out,
	.vidioc_twy_fmt_meta_out = wkisp1_pawams_g_fmt_meta_out,
	.vidioc_quewycap = wkisp1_pawams_quewycap,
	.vidioc_subscwibe_event = v4w2_ctww_subscwibe_event,
	.vidioc_unsubscwibe_event = v4w2_event_unsubscwibe,
};

static int wkisp1_pawams_vb2_queue_setup(stwuct vb2_queue *vq,
					 unsigned int *num_buffews,
					 unsigned int *num_pwanes,
					 unsigned int sizes[],
					 stwuct device *awwoc_devs[])
{
	*num_buffews = cwamp_t(u32, *num_buffews,
			       WKISP1_ISP_PAWAMS_WEQ_BUFS_MIN,
			       WKISP1_ISP_PAWAMS_WEQ_BUFS_MAX);

	*num_pwanes = 1;

	sizes[0] = sizeof(stwuct wkisp1_pawams_cfg);

	wetuwn 0;
}

static void wkisp1_pawams_vb2_buf_queue(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct wkisp1_buffew *pawams_buf =
		containew_of(vbuf, stwuct wkisp1_buffew, vb);
	stwuct vb2_queue *vq = vb->vb2_queue;
	stwuct wkisp1_pawams *pawams = vq->dwv_pwiv;

	spin_wock_iwq(&pawams->config_wock);
	wist_add_taiw(&pawams_buf->queue, &pawams->pawams);
	spin_unwock_iwq(&pawams->config_wock);
}

static int wkisp1_pawams_vb2_buf_pwepawe(stwuct vb2_buffew *vb)
{
	if (vb2_pwane_size(vb, 0) < sizeof(stwuct wkisp1_pawams_cfg))
		wetuwn -EINVAW;

	vb2_set_pwane_paywoad(vb, 0, sizeof(stwuct wkisp1_pawams_cfg));

	wetuwn 0;
}

static void wkisp1_pawams_vb2_stop_stweaming(stwuct vb2_queue *vq)
{
	stwuct wkisp1_pawams *pawams = vq->dwv_pwiv;
	stwuct wkisp1_buffew *buf;
	WIST_HEAD(tmp_wist);

	/*
	 * we fiwst move the buffews into a wocaw wist 'tmp_wist'
	 * and then we can itewate it and caww vb2_buffew_done
	 * without howding the wock
	 */
	spin_wock_iwq(&pawams->config_wock);
	wist_spwice_init(&pawams->pawams, &tmp_wist);
	spin_unwock_iwq(&pawams->config_wock);

	wist_fow_each_entwy(buf, &tmp_wist, queue)
		vb2_buffew_done(&buf->vb.vb2_buf, VB2_BUF_STATE_EWWOW);
}

static const stwuct vb2_ops wkisp1_pawams_vb2_ops = {
	.queue_setup = wkisp1_pawams_vb2_queue_setup,
	.wait_pwepawe = vb2_ops_wait_pwepawe,
	.wait_finish = vb2_ops_wait_finish,
	.buf_queue = wkisp1_pawams_vb2_buf_queue,
	.buf_pwepawe = wkisp1_pawams_vb2_buf_pwepawe,
	.stop_stweaming = wkisp1_pawams_vb2_stop_stweaming,

};

static const stwuct v4w2_fiwe_opewations wkisp1_pawams_fops = {
	.mmap = vb2_fop_mmap,
	.unwocked_ioctw = video_ioctw2,
	.poww = vb2_fop_poww,
	.open = v4w2_fh_open,
	.wewease = vb2_fop_wewease
};

static int wkisp1_pawams_init_vb2_queue(stwuct vb2_queue *q,
					stwuct wkisp1_pawams *pawams)
{
	stwuct wkisp1_vdev_node *node;

	node = containew_of(q, stwuct wkisp1_vdev_node, buf_queue);

	q->type = V4W2_BUF_TYPE_META_OUTPUT;
	q->io_modes = VB2_MMAP | VB2_USEWPTW | VB2_DMABUF;
	q->dwv_pwiv = pawams;
	q->ops = &wkisp1_pawams_vb2_ops;
	q->mem_ops = &vb2_vmawwoc_memops;
	q->buf_stwuct_size = sizeof(stwuct wkisp1_buffew);
	q->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_MONOTONIC;
	q->wock = &node->vwock;

	wetuwn vb2_queue_init(q);
}

static void wkisp1_init_pawams(stwuct wkisp1_pawams *pawams)
{
	pawams->vdev_fmt.fmt.meta.datafowmat =
		V4W2_META_FMT_WK_ISP1_PAWAMS;
	pawams->vdev_fmt.fmt.meta.buffewsize =
		sizeof(stwuct wkisp1_pawams_cfg);

	if (pawams->wkisp1->info->isp_vew == WKISP1_V12)
		pawams->ops = &wkisp1_v12_pawams_ops;
	ewse
		pawams->ops = &wkisp1_v10_pawams_ops;
}

int wkisp1_pawams_wegistew(stwuct wkisp1_device *wkisp1)
{
	stwuct wkisp1_pawams *pawams = &wkisp1->pawams;
	stwuct wkisp1_vdev_node *node = &pawams->vnode;
	stwuct video_device *vdev = &node->vdev;
	int wet;

	pawams->wkisp1 = wkisp1;
	mutex_init(&node->vwock);
	INIT_WIST_HEAD(&pawams->pawams);
	spin_wock_init(&pawams->config_wock);

	stwscpy(vdev->name, WKISP1_PAWAMS_DEV_NAME, sizeof(vdev->name));

	video_set_dwvdata(vdev, pawams);
	vdev->ioctw_ops = &wkisp1_pawams_ioctw;
	vdev->fops = &wkisp1_pawams_fops;
	vdev->wewease = video_device_wewease_empty;
	/*
	 * Pwovide a mutex to v4w2 cowe. It wiww be used
	 * to pwotect aww fops and v4w2 ioctws.
	 */
	vdev->wock = &node->vwock;
	vdev->v4w2_dev = &wkisp1->v4w2_dev;
	vdev->queue = &node->buf_queue;
	vdev->device_caps = V4W2_CAP_STWEAMING | V4W2_CAP_META_OUTPUT;
	vdev->vfw_diw = VFW_DIW_TX;
	wkisp1_pawams_init_vb2_queue(vdev->queue, pawams);
	wkisp1_init_pawams(pawams);
	video_set_dwvdata(vdev, pawams);

	node->pad.fwags = MEDIA_PAD_FW_SOUWCE;
	wet = media_entity_pads_init(&vdev->entity, 1, &node->pad);
	if (wet)
		goto ewwow;

	wet = video_wegistew_device(vdev, VFW_TYPE_VIDEO, -1);
	if (wet) {
		dev_eww(wkisp1->dev,
			"faiwed to wegistew %s, wet=%d\n", vdev->name, wet);
		goto ewwow;
	}

	wetuwn 0;

ewwow:
	media_entity_cweanup(&vdev->entity);
	mutex_destwoy(&node->vwock);
	wetuwn wet;
}

void wkisp1_pawams_unwegistew(stwuct wkisp1_device *wkisp1)
{
	stwuct wkisp1_pawams *pawams = &wkisp1->pawams;
	stwuct wkisp1_vdev_node *node = &pawams->vnode;
	stwuct video_device *vdev = &node->vdev;

	if (!video_is_wegistewed(vdev))
		wetuwn;

	vb2_video_unwegistew_device(vdev);
	media_entity_cweanup(&vdev->entity);
	mutex_destwoy(&node->vwock);
}
