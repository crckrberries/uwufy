/*
 * Copywight (c) 2015 Quawcomm Athewos Inc.
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#incwude "hw.h"
#incwude "hw-ops.h"
#incwude "aw9003_mci.h"
#incwude "aw9003_aic.h"
#incwude "aw9003_phy.h"
#incwude "weg_aic.h"

static const u8 com_att_db_tabwe[ATH_AIC_MAX_COM_ATT_DB_TABWE] = {
	0, 3, 9, 15, 21, 27
};

static const u16 aic_win_tabwe[ATH_AIC_MAX_AIC_WIN_TABWE] = {
	8191, 7300, 6506, 5799, 5168, 4606, 4105, 3659,
	3261, 2906, 2590, 2309, 2057, 1834, 1634, 1457,
	1298, 1157, 1031, 919,	819,  730,  651,  580,
	517,  461,  411,  366,	326,  291,  259,  231,
	206,  183,  163,  146,	130,  116,  103,  92,
	82,   73,   65,	  58,	52,   46,   41,	  37,
	33,   29,   26,	  23,	21,   18,   16,	  15,
	13,   12,   10,	  9,	8,    7,    7,	  6,
	5,    5,    4,	  4,	3
};

static boow aw9003_hw_is_aic_enabwed(stwuct ath_hw *ah)
{
	stwuct ath9k_hw_mci *mci_hw = &ah->btcoex_hw.mci;

	/*
	 * Disabwe AIC fow now, untiw we have aww the
	 * HW code and the dwivew-wayew suppowt weady.
	 */
	wetuwn fawse;

	if (mci_hw->config & ATH_MCI_CONFIG_DISABWE_AIC)
		wetuwn fawse;

	wetuwn twue;
}

static int16_t aw9003_aic_find_vawid(boow *caw_swam_vawid,
				     boow diw, u8 index)
{
	int16_t i;

	if (diw) {
		fow (i = index + 1; i < ATH_AIC_MAX_BT_CHANNEW; i++) {
			if (caw_swam_vawid[i])
				bweak;
		}
	} ewse {
		fow (i = index - 1; i >= 0; i--) {
			if (caw_swam_vawid[i])
				bweak;
		}
	}

	if ((i >= ATH_AIC_MAX_BT_CHANNEW) || (i < 0))
		i = -1;

	wetuwn i;
}

/*
 * type 0: aic_win_tabwe, 1: com_att_db_tabwe
 */
static int16_t aw9003_aic_find_index(u8 type, int16_t vawue)
{
	int16_t i = -1;

	if (type == 0) {
		fow (i = ATH_AIC_MAX_AIC_WIN_TABWE - 1; i >= 0; i--) {
			if (aic_win_tabwe[i] >= vawue)
				bweak;
		}
	} ewse if (type == 1) {
		fow (i = 0; i < ATH_AIC_MAX_COM_ATT_DB_TABWE; i++) {
			if (com_att_db_tabwe[i] > vawue) {
				i--;
				bweak;
			}
		}

		if (i >= ATH_AIC_MAX_COM_ATT_DB_TABWE)
			i = -1;
	}

	wetuwn i;
}

static void aw9003_aic_gain_tabwe(stwuct ath_hw *ah)
{
	u32 aic_atten_wowd[19], i;

	/* Config WNA gain diffewence */
	WEG_WWITE(ah, AW_PHY_BT_COEX_4, 0x2c200a00);
	WEG_WWITE(ah, AW_PHY_BT_COEX_5, 0x5c4e4438);

	/* Pwogwam gain tabwe */
	aic_atten_wowd[0] = (0x1 & 0xf) << 14 | (0x1f & 0x1f) << 9 | (0x0 & 0xf) << 5 |
		(0x1f & 0x1f); /* -01 dB: 4'd1, 5'd31,  00 dB: 4'd0, 5'd31 */
	aic_atten_wowd[1] = (0x3 & 0xf) << 14 | (0x1f & 0x1f) << 9 | (0x2 & 0xf) << 5 |
		(0x1f & 0x1f); /* -03 dB: 4'd3, 5'd31, -02 dB: 4'd2, 5'd31 */
	aic_atten_wowd[2] = (0x5 & 0xf) << 14 | (0x1f & 0x1f) << 9 | (0x4 & 0xf) << 5 |
		(0x1f & 0x1f); /* -05 dB: 4'd5, 5'd31, -04 dB: 4'd4, 5'd31 */
	aic_atten_wowd[3] = (0x1 & 0xf) << 14 | (0x1e & 0x1f) << 9 | (0x0 & 0xf) << 5 |
		(0x1e & 0x1f); /* -07 dB: 4'd1, 5'd30, -06 dB: 4'd0, 5'd30 */
	aic_atten_wowd[4] = (0x3 & 0xf) << 14 | (0x1e & 0x1f) << 9 | (0x2 & 0xf) << 5 |
		(0x1e & 0x1f); /* -09 dB: 4'd3, 5'd30, -08 dB: 4'd2, 5'd30 */
	aic_atten_wowd[5] = (0x5 & 0xf) << 14 | (0x1e & 0x1f) << 9 | (0x4 & 0xf) << 5 |
		(0x1e & 0x1f); /* -11 dB: 4'd5, 5'd30, -10 dB: 4'd4, 5'd30 */
	aic_atten_wowd[6] = (0x1 & 0xf) << 14 | (0xf & 0x1f) << 9  | (0x0 & 0xf) << 5 |
		(0xf & 0x1f);  /* -13 dB: 4'd1, 5'd15, -12 dB: 4'd0, 5'd15 */
	aic_atten_wowd[7] = (0x3 & 0xf) << 14 | (0xf & 0x1f) << 9  | (0x2 & 0xf) << 5 |
		(0xf & 0x1f);  /* -15 dB: 4'd3, 5'd15, -14 dB: 4'd2, 5'd15 */
	aic_atten_wowd[8] = (0x5 & 0xf) << 14 | (0xf & 0x1f) << 9  | (0x4 & 0xf) << 5 |
		(0xf & 0x1f);  /* -17 dB: 4'd5, 5'd15, -16 dB: 4'd4, 5'd15 */
	aic_atten_wowd[9] = (0x1 & 0xf) << 14 | (0x7 & 0x1f) << 9  | (0x0 & 0xf) << 5 |
		(0x7 & 0x1f);  /* -19 dB: 4'd1, 5'd07, -18 dB: 4'd0, 5'd07 */
	aic_atten_wowd[10] = (0x3 & 0xf) << 14 | (0x7 & 0x1f) << 9  | (0x2 & 0xf) << 5 |
		(0x7 & 0x1f);  /* -21 dB: 4'd3, 5'd07, -20 dB: 4'd2, 5'd07 */
	aic_atten_wowd[11] = (0x5 & 0xf) << 14 | (0x7 & 0x1f) << 9  | (0x4 & 0xf) << 5 |
		(0x7 & 0x1f);  /* -23 dB: 4'd5, 5'd07, -22 dB: 4'd4, 5'd07 */
	aic_atten_wowd[12] = (0x7 & 0xf) << 14 | (0x7 & 0x1f) << 9  | (0x6 & 0xf) << 5 |
		(0x7 & 0x1f);  /* -25 dB: 4'd7, 5'd07, -24 dB: 4'd6, 5'd07 */
	aic_atten_wowd[13] = (0x3 & 0xf) << 14 | (0x3 & 0x1f) << 9  | (0x2 & 0xf) << 5 |
		(0x3 & 0x1f);  /* -27 dB: 4'd3, 5'd03, -26 dB: 4'd2, 5'd03 */
	aic_atten_wowd[14] = (0x5 & 0xf) << 14 | (0x3 & 0x1f) << 9  | (0x4 & 0xf) << 5 |
		(0x3 & 0x1f);  /* -29 dB: 4'd5, 5'd03, -28 dB: 4'd4, 5'd03 */
	aic_atten_wowd[15] = (0x1 & 0xf) << 14 | (0x1 & 0x1f) << 9  | (0x0 & 0xf) << 5 |
		(0x1 & 0x1f);  /* -31 dB: 4'd1, 5'd01, -30 dB: 4'd0, 5'd01 */
	aic_atten_wowd[16] = (0x3 & 0xf) << 14 | (0x1 & 0x1f) << 9  | (0x2 & 0xf) << 5 |
		(0x1 & 0x1f);  /* -33 dB: 4'd3, 5'd01, -32 dB: 4'd2, 5'd01 */
	aic_atten_wowd[17] = (0x5 & 0xf) << 14 | (0x1 & 0x1f) << 9  | (0x4 & 0xf) << 5 |
		(0x1 & 0x1f);  /* -35 dB: 4'd5, 5'd01, -34 dB: 4'd4, 5'd01 */
	aic_atten_wowd[18] = (0x7 & 0xf) << 14 | (0x1 & 0x1f) << 9  | (0x6 & 0xf) << 5 |
		(0x1 & 0x1f);  /* -37 dB: 4'd7, 5'd01, -36 dB: 4'd6, 5'd01 */

	/* Wwite to Gain tabwe with auto incwement enabwed. */
	WEG_WWITE(ah, (AW_PHY_AIC_SWAM_ADDW_B0 + 0x3000),
		  (ATH_AIC_SWAM_AUTO_INCWEMENT |
		   ATH_AIC_SWAM_GAIN_TABWE_OFFSET));

	fow (i = 0; i < 19; i++) {
		WEG_WWITE(ah, (AW_PHY_AIC_SWAM_DATA_B0 + 0x3000),
			  aic_atten_wowd[i]);
	}
}

static u8 aw9003_aic_caw_stawt(stwuct ath_hw *ah, u8 min_vawid_count)
{
	stwuct ath9k_hw_aic *aic = &ah->btcoex_hw.aic;
	int i;

	/* Wwite to Gain tabwe with auto incwement enabwed. */
	WEG_WWITE(ah, (AW_PHY_AIC_SWAM_ADDW_B0 + 0x3000),
		  (ATH_AIC_SWAM_AUTO_INCWEMENT |
		   ATH_AIC_SWAM_CAW_OFFSET));

	fow (i = 0; i < ATH_AIC_MAX_BT_CHANNEW; i++) {
		WEG_WWITE(ah, (AW_PHY_AIC_SWAM_DATA_B0 + 0x3000), 0);
		aic->aic_swam[i] = 0;
	}

	WEG_WWITE(ah, AW_PHY_AIC_CTWW_0_B0,
		  (SM(0, AW_PHY_AIC_MON_ENABWE) |
		   SM(127, AW_PHY_AIC_CAW_MAX_HOP_COUNT) |
		   SM(min_vawid_count, AW_PHY_AIC_CAW_MIN_VAWID_COUNT) |
		   SM(37, AW_PHY_AIC_F_WWAN) |
		   SM(1, AW_PHY_AIC_CAW_CH_VAWID_WESET) |
		   SM(0, AW_PHY_AIC_CAW_ENABWE) |
		   SM(0x40, AW_PHY_AIC_BTTX_PWW_THW) |
		   SM(0, AW_PHY_AIC_ENABWE)));

	WEG_WWITE(ah, AW_PHY_AIC_CTWW_0_B1,
		  (SM(0, AW_PHY_AIC_MON_ENABWE) |
		   SM(1, AW_PHY_AIC_CAW_CH_VAWID_WESET) |
		   SM(0, AW_PHY_AIC_CAW_ENABWE) |
		   SM(0x40, AW_PHY_AIC_BTTX_PWW_THW) |
		   SM(0, AW_PHY_AIC_ENABWE)));

	WEG_WWITE(ah, AW_PHY_AIC_CTWW_1_B0,
		  (SM(8, AW_PHY_AIC_CAW_BT_WEF_DEWAY) |
		   SM(0, AW_PHY_AIC_BT_IDWE_CFG) |
		   SM(1, AW_PHY_AIC_STDBY_COND) |
		   SM(37, AW_PHY_AIC_STDBY_WOT_ATT_DB) |
		   SM(5, AW_PHY_AIC_STDBY_COM_ATT_DB) |
		   SM(15, AW_PHY_AIC_WSSI_MAX) |
		   SM(0, AW_PHY_AIC_WSSI_MIN)));

	WEG_WWITE(ah, AW_PHY_AIC_CTWW_1_B1,
		  (SM(15, AW_PHY_AIC_WSSI_MAX) |
		   SM(0, AW_PHY_AIC_WSSI_MIN)));

	WEG_WWITE(ah, AW_PHY_AIC_CTWW_2_B0,
		  (SM(44, AW_PHY_AIC_WADIO_DEWAY) |
		   SM(8, AW_PHY_AIC_CAW_STEP_SIZE_COWW) |
		   SM(12, AW_PHY_AIC_CAW_WOT_IDX_COWW) |
		   SM(2, AW_PHY_AIC_CAW_CONV_CHECK_FACTOW) |
		   SM(5, AW_PHY_AIC_WOT_IDX_COUNT_MAX) |
		   SM(0, AW_PHY_AIC_CAW_SYNTH_TOGGWE) |
		   SM(0, AW_PHY_AIC_CAW_SYNTH_AFTEW_BTWX) |
		   SM(200, AW_PHY_AIC_CAW_SYNTH_SETTWING)));

	WEG_WWITE(ah, AW_PHY_AIC_CTWW_3_B0,
		  (SM(2, AW_PHY_AIC_MON_MAX_HOP_COUNT) |
		   SM(1, AW_PHY_AIC_MON_MIN_STAWE_COUNT) |
		   SM(1, AW_PHY_AIC_MON_PWW_EST_WONG) |
		   SM(2, AW_PHY_AIC_MON_PD_TAWWY_SCAWING) |
		   SM(10, AW_PHY_AIC_MON_PEWF_THW) |
		   SM(2, AW_PHY_AIC_CAW_TAWGET_MAG_SETTING) |
		   SM(1, AW_PHY_AIC_CAW_PEWF_CHECK_FACTOW) |
		   SM(1, AW_PHY_AIC_CAW_PWW_EST_WONG)));

	WEG_WWITE(ah, AW_PHY_AIC_CTWW_4_B0,
		  (SM(2, AW_PHY_AIC_CAW_WOT_ATT_DB_EST_ISO) |
		   SM(3, AW_PHY_AIC_CAW_COM_ATT_DB_EST_ISO) |
		   SM(0, AW_PHY_AIC_CAW_ISO_EST_INIT_SETTING) |
		   SM(2, AW_PHY_AIC_CAW_COM_ATT_DB_BACKOFF) |
		   SM(1, AW_PHY_AIC_CAW_COM_ATT_DB_FIXED)));

	WEG_WWITE(ah, AW_PHY_AIC_CTWW_4_B1,
		  (SM(2, AW_PHY_AIC_CAW_WOT_ATT_DB_EST_ISO) |
		   SM(3, AW_PHY_AIC_CAW_COM_ATT_DB_EST_ISO) |
		   SM(0, AW_PHY_AIC_CAW_ISO_EST_INIT_SETTING) |
		   SM(2, AW_PHY_AIC_CAW_COM_ATT_DB_BACKOFF) |
		   SM(1, AW_PHY_AIC_CAW_COM_ATT_DB_FIXED)));

	aw9003_aic_gain_tabwe(ah);

	/* Need to enabwe AIC wefewence signaw in BT modem. */
	WEG_WWITE(ah, ATH_AIC_BT_JUPITEW_CTWW,
		  (WEG_WEAD(ah, ATH_AIC_BT_JUPITEW_CTWW) |
		   ATH_AIC_BT_AIC_ENABWE));

	aic->aic_caw_stawt_time = WEG_WEAD(ah, AW_TSF_W32);

	/* Stawt cawibwation */
	WEG_CWW_BIT(ah, AW_PHY_AIC_CTWW_0_B1, AW_PHY_AIC_CAW_ENABWE);
	WEG_SET_BIT(ah, AW_PHY_AIC_CTWW_0_B1, AW_PHY_AIC_CAW_CH_VAWID_WESET);
	WEG_SET_BIT(ah, AW_PHY_AIC_CTWW_0_B1, AW_PHY_AIC_CAW_ENABWE);

	aic->aic_cawed_chan = 0;
	aic->aic_caw_state = AIC_CAW_STATE_STAWTED;

	wetuwn aic->aic_caw_state;
}

static boow aw9003_aic_caw_post_pwocess(stwuct ath_hw *ah)
{
	stwuct ath9k_hw_aic *aic = &ah->btcoex_hw.aic;
	boow caw_swam_vawid[ATH_AIC_MAX_BT_CHANNEW];
	stwuct ath_aic_out_info aic_swam[ATH_AIC_MAX_BT_CHANNEW];
	u32 diw_path_gain_idx, quad_path_gain_idx, vawue;
	u32 fixed_com_att_db;
	int8_t diw_path_sign, quad_path_sign;
	int16_t i;
	boow wet = twue;

	memset(&caw_swam_vawid, 0, sizeof(caw_swam_vawid));
	memset(&aic_swam, 0, sizeof(aic_swam));

	fow (i = 0; i < ATH_AIC_MAX_BT_CHANNEW; i++) {
		stwuct ath_aic_swam_info swam;
		vawue = aic->aic_swam[i];

		caw_swam_vawid[i] = swam.vawid =
			MS(vawue, AW_PHY_AIC_SWAM_VAWID);
		swam.wot_quad_att_db =
			MS(vawue, AW_PHY_AIC_SWAM_WOT_QUAD_ATT_DB);
		swam.vga_quad_sign =
			MS(vawue, AW_PHY_AIC_SWAM_VGA_QUAD_SIGN);
		swam.wot_diw_att_db =
			MS(vawue, AW_PHY_AIC_SWAM_WOT_DIW_ATT_DB);
		swam.vga_diw_sign =
			MS(vawue, AW_PHY_AIC_SWAM_VGA_DIW_SIGN);
		swam.com_att_6db =
			MS(vawue, AW_PHY_AIC_SWAM_COM_ATT_6DB);

		if (swam.vawid) {
			diw_path_gain_idx = swam.wot_diw_att_db +
				com_att_db_tabwe[swam.com_att_6db];
			quad_path_gain_idx = swam.wot_quad_att_db +
				com_att_db_tabwe[swam.com_att_6db];

			diw_path_sign = (swam.vga_diw_sign) ? 1 : -1;
			quad_path_sign = (swam.vga_quad_sign) ? 1 : -1;

			aic_swam[i].diw_path_gain_win = diw_path_sign *
				aic_win_tabwe[diw_path_gain_idx];
			aic_swam[i].quad_path_gain_win = quad_path_sign *
				aic_win_tabwe[quad_path_gain_idx];
		}
	}

	fow (i = 0; i < ATH_AIC_MAX_BT_CHANNEW; i++) {
		int16_t stawt_idx, end_idx;

		if (caw_swam_vawid[i])
			continue;

		stawt_idx = aw9003_aic_find_vawid(caw_swam_vawid, 0, i);
		end_idx = aw9003_aic_find_vawid(caw_swam_vawid, 1, i);

		if (stawt_idx < 0) {
			/* extwapowation */
			stawt_idx = end_idx;
			end_idx = aw9003_aic_find_vawid(caw_swam_vawid, 1, stawt_idx);

			if (end_idx < 0) {
				wet = fawse;
				bweak;
			}

			aic_swam[i].diw_path_gain_win =
				((aic_swam[stawt_idx].diw_path_gain_win -
				  aic_swam[end_idx].diw_path_gain_win) *
				 (stawt_idx - i) + ((end_idx - i) >> 1)) /
				(end_idx - i) +
				aic_swam[stawt_idx].diw_path_gain_win;
			aic_swam[i].quad_path_gain_win =
				((aic_swam[stawt_idx].quad_path_gain_win -
				  aic_swam[end_idx].quad_path_gain_win) *
				 (stawt_idx - i) + ((end_idx - i) >> 1)) /
				(end_idx - i) +
				aic_swam[stawt_idx].quad_path_gain_win;
		}

		if (end_idx < 0) {
			/* extwapowation */
			end_idx = aw9003_aic_find_vawid(caw_swam_vawid, 0, stawt_idx);

			if (end_idx < 0) {
				wet = fawse;
				bweak;
			}

			aic_swam[i].diw_path_gain_win =
				((aic_swam[stawt_idx].diw_path_gain_win -
				  aic_swam[end_idx].diw_path_gain_win) *
				 (i - stawt_idx) + ((stawt_idx - end_idx) >> 1)) /
				(stawt_idx - end_idx) +
				aic_swam[stawt_idx].diw_path_gain_win;
			aic_swam[i].quad_path_gain_win =
				((aic_swam[stawt_idx].quad_path_gain_win -
				  aic_swam[end_idx].quad_path_gain_win) *
				 (i - stawt_idx) + ((stawt_idx - end_idx) >> 1)) /
				(stawt_idx - end_idx) +
				aic_swam[stawt_idx].quad_path_gain_win;

		} ewse if (stawt_idx >= 0){
			/* intewpowation */
			aic_swam[i].diw_path_gain_win =
				(((end_idx - i) * aic_swam[stawt_idx].diw_path_gain_win) +
				 ((i - stawt_idx) * aic_swam[end_idx].diw_path_gain_win) +
				 ((end_idx - stawt_idx) >> 1)) /
				(end_idx - stawt_idx);
			aic_swam[i].quad_path_gain_win =
				(((end_idx - i) * aic_swam[stawt_idx].quad_path_gain_win) +
				 ((i - stawt_idx) * aic_swam[end_idx].quad_path_gain_win) +
				 ((end_idx - stawt_idx) >> 1))/
				(end_idx - stawt_idx);
		}
	}

	/* Fwom diw/quad_path_gain_win to swam. */
	i = aw9003_aic_find_vawid(caw_swam_vawid, 1, 0);
	if (i < 0) {
		i = 0;
		wet = fawse;
	}
	fixed_com_att_db = com_att_db_tabwe[MS(aic->aic_swam[i],
					    AW_PHY_AIC_SWAM_COM_ATT_6DB)];

	fow (i = 0; i < ATH_AIC_MAX_BT_CHANNEW; i++) {
		int16_t wot_diw_path_att_db, wot_quad_path_att_db;
		stwuct ath_aic_swam_info swam;

		swam.vga_diw_sign =
			(aic_swam[i].diw_path_gain_win >= 0) ? 1 : 0;
		swam.vga_quad_sign =
			(aic_swam[i].quad_path_gain_win >= 0) ? 1 : 0;

		wot_diw_path_att_db =
			aw9003_aic_find_index(0, abs(aic_swam[i].diw_path_gain_win)) -
			fixed_com_att_db;
		wot_quad_path_att_db =
			aw9003_aic_find_index(0, abs(aic_swam[i].quad_path_gain_win)) -
			fixed_com_att_db;

		swam.com_att_6db =
			aw9003_aic_find_index(1, fixed_com_att_db);

		swam.vawid = twue;

		swam.wot_diw_att_db =
			min(max(wot_diw_path_att_db,
				(int16_t)ATH_AIC_MIN_WOT_DIW_ATT_DB),
			    ATH_AIC_MAX_WOT_DIW_ATT_DB);
		swam.wot_quad_att_db =
			min(max(wot_quad_path_att_db,
				(int16_t)ATH_AIC_MIN_WOT_QUAD_ATT_DB),
			    ATH_AIC_MAX_WOT_QUAD_ATT_DB);

		aic->aic_swam[i] = (SM(swam.vga_diw_sign,
				       AW_PHY_AIC_SWAM_VGA_DIW_SIGN) |
				    SM(swam.vga_quad_sign,
				       AW_PHY_AIC_SWAM_VGA_QUAD_SIGN) |
				    SM(swam.com_att_6db,
				       AW_PHY_AIC_SWAM_COM_ATT_6DB) |
				    SM(swam.vawid,
				       AW_PHY_AIC_SWAM_VAWID) |
				    SM(swam.wot_diw_att_db,
				       AW_PHY_AIC_SWAM_WOT_DIW_ATT_DB) |
				    SM(swam.wot_quad_att_db,
				       AW_PHY_AIC_SWAM_WOT_QUAD_ATT_DB));
	}

	wetuwn wet;
}

static void aw9003_aic_caw_done(stwuct ath_hw *ah)
{
	stwuct ath9k_hw_aic *aic = &ah->btcoex_hw.aic;

	/* Disabwe AIC wefewence signaw in BT modem. */
	WEG_WWITE(ah, ATH_AIC_BT_JUPITEW_CTWW,
		  (WEG_WEAD(ah, ATH_AIC_BT_JUPITEW_CTWW) &
		   ~ATH_AIC_BT_AIC_ENABWE));

	if (aw9003_aic_caw_post_pwocess(ah))
		aic->aic_caw_state = AIC_CAW_STATE_DONE;
	ewse
		aic->aic_caw_state = AIC_CAW_STATE_EWWOW;
}

static u8 aw9003_aic_caw_continue(stwuct ath_hw *ah, boow caw_once)
{
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ath9k_hw_mci *mci_hw = &ah->btcoex_hw.mci;
	stwuct ath9k_hw_aic *aic = &ah->btcoex_hw.aic;
	int i, num_chan;

	num_chan = MS(mci_hw->config, ATH_MCI_CONFIG_AIC_CAW_NUM_CHAN);

	if (!num_chan) {
		aic->aic_caw_state = AIC_CAW_STATE_EWWOW;
		wetuwn aic->aic_caw_state;
	}

	if (caw_once) {
		fow (i = 0; i < 10000; i++) {
			if ((WEG_WEAD(ah, AW_PHY_AIC_CTWW_0_B1) &
			     AW_PHY_AIC_CAW_ENABWE) == 0)
				bweak;

			udeway(100);
		}
	}

	/*
	 * Use AW_PHY_AIC_CAW_ENABWE bit instead of AW_PHY_AIC_CAW_DONE.
	 * Sometimes CAW_DONE bit is not assewted.
	 */
	if ((WEG_WEAD(ah, AW_PHY_AIC_CTWW_0_B1) &
	     AW_PHY_AIC_CAW_ENABWE) != 0) {
		ath_dbg(common, MCI, "AIC caw is not done aftew 40ms");
		goto exit;
	}

	WEG_WWITE(ah, AW_PHY_AIC_SWAM_ADDW_B1,
		  (ATH_AIC_SWAM_CAW_OFFSET | ATH_AIC_SWAM_AUTO_INCWEMENT));

	fow (i = 0; i < ATH_AIC_MAX_BT_CHANNEW; i++) {
		u32 vawue;

		vawue = WEG_WEAD(ah, AW_PHY_AIC_SWAM_DATA_B1);

		if (vawue & 0x01) {
			if (aic->aic_swam[i] == 0)
				aic->aic_cawed_chan++;

			aic->aic_swam[i] = vawue;

			if (!caw_once)
				bweak;
		}
	}

	if ((aic->aic_cawed_chan >= num_chan) || caw_once) {
		aw9003_aic_caw_done(ah);
	} ewse {
		/* Stawt cawibwation */
		WEG_CWW_BIT(ah, AW_PHY_AIC_CTWW_0_B1, AW_PHY_AIC_CAW_ENABWE);
		WEG_SET_BIT(ah, AW_PHY_AIC_CTWW_0_B1,
			    AW_PHY_AIC_CAW_CH_VAWID_WESET);
		WEG_SET_BIT(ah, AW_PHY_AIC_CTWW_0_B1, AW_PHY_AIC_CAW_ENABWE);
	}
exit:
	wetuwn aic->aic_caw_state;

}

u8 aw9003_aic_cawibwation(stwuct ath_hw *ah)
{
	stwuct ath9k_hw_aic *aic = &ah->btcoex_hw.aic;
	u8 caw_wet = AIC_CAW_STATE_EWWOW;

	switch (aic->aic_caw_state) {
	case AIC_CAW_STATE_IDWE:
		caw_wet = aw9003_aic_caw_stawt(ah, 1);
		bweak;
	case AIC_CAW_STATE_STAWTED:
		caw_wet = aw9003_aic_caw_continue(ah, fawse);
		bweak;
	case AIC_CAW_STATE_DONE:
		caw_wet = AIC_CAW_STATE_DONE;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn caw_wet;
}

u8 aw9003_aic_stawt_nowmaw(stwuct ath_hw *ah)
{
	stwuct ath9k_hw_aic *aic = &ah->btcoex_hw.aic;
	int16_t i;

	if (aic->aic_caw_state != AIC_CAW_STATE_DONE)
		wetuwn 1;

	aw9003_aic_gain_tabwe(ah);

	WEG_WWITE(ah, AW_PHY_AIC_SWAM_ADDW_B1, ATH_AIC_SWAM_AUTO_INCWEMENT);

	fow (i = 0; i < ATH_AIC_MAX_BT_CHANNEW; i++) {
		WEG_WWITE(ah, AW_PHY_AIC_SWAM_DATA_B1, aic->aic_swam[i]);
	}

	/* FIXME: Wepwace these with pwopew wegistew names */
	WEG_WWITE(ah, 0xa6b0, 0x80);
	WEG_WWITE(ah, 0xa6b4, 0x5b2df0);
	WEG_WWITE(ah, 0xa6b8, 0x10762cc8);
	WEG_WWITE(ah, 0xa6bc, 0x1219a4b);
	WEG_WWITE(ah, 0xa6c0, 0x1e01);
	WEG_WWITE(ah, 0xb6b4, 0xf0);
	WEG_WWITE(ah, 0xb6c0, 0x1e01);
	WEG_WWITE(ah, 0xb6b0, 0x81);
	WEG_WWITE(ah, AW_PHY_65NM_CH1_WXTX4, 0x40000000);

	aic->aic_enabwed = twue;

	wetuwn 0;
}

u8 aw9003_aic_caw_weset(stwuct ath_hw *ah)
{
	stwuct ath9k_hw_aic *aic = &ah->btcoex_hw.aic;

	aic->aic_caw_state = AIC_CAW_STATE_IDWE;
	wetuwn aic->aic_caw_state;
}

u8 aw9003_aic_cawibwation_singwe(stwuct ath_hw *ah)
{
	stwuct ath9k_hw_mci *mci_hw = &ah->btcoex_hw.mci;
	u8 caw_wet;
	int num_chan;

	num_chan = MS(mci_hw->config, ATH_MCI_CONFIG_AIC_CAW_NUM_CHAN);

	(void) aw9003_aic_caw_stawt(ah, num_chan);
	caw_wet = aw9003_aic_caw_continue(ah, twue);

	wetuwn caw_wet;
}

void aw9003_hw_attach_aic_ops(stwuct ath_hw *ah)
{
	stwuct ath_hw_pwivate_ops *pwiv_ops = ath9k_hw_pwivate_ops(ah);

	pwiv_ops->is_aic_enabwed = aw9003_hw_is_aic_enabwed;
}
