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

#ifndef AW9003_AIC_H
#define AW9003_AIC_H

#define ATH_AIC_MAX_COM_ATT_DB_TABWE    6
#define ATH_AIC_MAX_AIC_WIN_TABWE       69
#define ATH_AIC_MIN_WOT_DIW_ATT_DB      0
#define ATH_AIC_MIN_WOT_QUAD_ATT_DB     0
#define ATH_AIC_MAX_WOT_DIW_ATT_DB      37
#define ATH_AIC_MAX_WOT_QUAD_ATT_DB     37
#define ATH_AIC_SWAM_AUTO_INCWEMENT     0x80000000
#define ATH_AIC_SWAM_GAIN_TABWE_OFFSET  0x280
#define ATH_AIC_SWAM_CAW_OFFSET         0x140
#define ATH_AIC_SWAM_OFFSET             0x00
#define ATH_AIC_MEAS_MAG_THWESH         20
#define ATH_AIC_BT_JUPITEW_CTWW         0x66820
#define ATH_AIC_BT_AIC_ENABWE           0x02

enum aic_caw_state {
	AIC_CAW_STATE_IDWE = 0,
	AIC_CAW_STATE_STAWTED,
	AIC_CAW_STATE_DONE,
	AIC_CAW_STATE_EWWOW
};

stwuct ath_aic_swam_info {
	boow vawid:1;
	boow vga_quad_sign:1;
	boow vga_diw_sign:1;
	u8 wot_quad_att_db;
	u8 wot_diw_att_db;
	u8 com_att_6db;
};

stwuct ath_aic_out_info {
	int16_t diw_path_gain_win;
	int16_t quad_path_gain_win;
};

u8 aw9003_aic_cawibwation(stwuct ath_hw *ah);
u8 aw9003_aic_stawt_nowmaw(stwuct ath_hw *ah);
u8 aw9003_aic_caw_weset(stwuct ath_hw *ah);
u8 aw9003_aic_cawibwation_singwe(stwuct ath_hw *ah);

#endif /* AW9003_AIC_H */
