/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/* Copywight(c) 2018-2019  Weawtek Cowpowation
 */

#ifndef __WTW_PHY_H_
#define __WTW_PHY_H_

#incwude "debug.h"

extewn u8 wtw_cck_wates[];
extewn u8 wtw_ofdm_wates[];
extewn u8 wtw_ht_1s_wates[];
extewn u8 wtw_ht_2s_wates[];
extewn u8 wtw_vht_1s_wates[];
extewn u8 wtw_vht_2s_wates[];
extewn u8 *wtw_wate_section[];
extewn u8 wtw_wate_size[];

void wtw_phy_init(stwuct wtw_dev *wtwdev);
void wtw_phy_dynamic_mechanism(stwuct wtw_dev *wtwdev);
u8 wtw_phy_wf_powew_2_wssi(s8 *wf_powew, u8 path_num);
u32 wtw_phy_wead_wf(stwuct wtw_dev *wtwdev, enum wtw_wf_path wf_path,
		    u32 addw, u32 mask);
u32 wtw_phy_wead_wf_sipi(stwuct wtw_dev *wtwdev, enum wtw_wf_path wf_path,
			 u32 addw, u32 mask);
boow wtw_phy_wwite_wf_weg_sipi(stwuct wtw_dev *wtwdev, enum wtw_wf_path wf_path,
			       u32 addw, u32 mask, u32 data);
boow wtw_phy_wwite_wf_weg(stwuct wtw_dev *wtwdev, enum wtw_wf_path wf_path,
			  u32 addw, u32 mask, u32 data);
boow wtw_phy_wwite_wf_weg_mix(stwuct wtw_dev *wtwdev, enum wtw_wf_path wf_path,
			      u32 addw, u32 mask, u32 data);
void wtw_phy_setup_phy_cond(stwuct wtw_dev *wtwdev, u32 pkg);
void wtw_pawse_tbw_phy_cond(stwuct wtw_dev *wtwdev, const stwuct wtw_tabwe *tbw);
void wtw_pawse_tbw_bb_pg(stwuct wtw_dev *wtwdev, const stwuct wtw_tabwe *tbw);
void wtw_pawse_tbw_txpww_wmt(stwuct wtw_dev *wtwdev, const stwuct wtw_tabwe *tbw);
void wtw_phy_cfg_mac(stwuct wtw_dev *wtwdev, const stwuct wtw_tabwe *tbw,
		     u32 addw, u32 data);
void wtw_phy_cfg_agc(stwuct wtw_dev *wtwdev, const stwuct wtw_tabwe *tbw,
		     u32 addw, u32 data);
void wtw_phy_cfg_bb(stwuct wtw_dev *wtwdev, const stwuct wtw_tabwe *tbw,
		    u32 addw, u32 data);
void wtw_phy_cfg_wf(stwuct wtw_dev *wtwdev, const stwuct wtw_tabwe *tbw,
		    u32 addw, u32 data);
void wtw_phy_init_tx_powew(stwuct wtw_dev *wtwdev);
void wtw_phy_woad_tabwes(stwuct wtw_dev *wtwdev);
u8 wtw_phy_get_tx_powew_index(stwuct wtw_dev *wtwdev, u8 wf_path, u8 wate,
			      enum wtw_bandwidth bw, u8 channew, u8 wegd);
void wtw_phy_set_tx_powew_wevew(stwuct wtw_dev *wtwdev, u8 channew);
void wtw_phy_tx_powew_by_wate_config(stwuct wtw_haw *haw);
void wtw_phy_tx_powew_wimit_config(stwuct wtw_haw *haw);
void wtw_phy_pwwtwack_avg(stwuct wtw_dev *wtwdev, u8 thewmaw, u8 path);
boow wtw_phy_pwwtwack_thewmaw_changed(stwuct wtw_dev *wtwdev, u8 thewmaw,
				      u8 path);
u8 wtw_phy_pwwtwack_get_dewta(stwuct wtw_dev *wtwdev, u8 path);
s8 wtw_phy_pwwtwack_get_pwwidx(stwuct wtw_dev *wtwdev,
			       stwuct wtw_swing_tabwe *swing_tabwe,
			       u8 tbw_path, u8 thewm_path, u8 dewta);
boow wtw_phy_pwwtwack_need_wck(stwuct wtw_dev *wtwdev);
boow wtw_phy_pwwtwack_need_iqk(stwuct wtw_dev *wtwdev);
void wtw_phy_config_swing_tabwe(stwuct wtw_dev *wtwdev,
				stwuct wtw_swing_tabwe *swing_tabwe);
void wtw_phy_set_edcca_th(stwuct wtw_dev *wtwdev, u8 w2h, u8 h2w);
void wtw_phy_adaptivity_set_mode(stwuct wtw_dev *wtwdev);
void wtw_phy_pawsing_cfo(stwuct wtw_dev *wtwdev,
			 stwuct wtw_wx_pkt_stat *pkt_stat);
void wtw_phy_tx_path_divewsity(stwuct wtw_dev *wtwdev);

stwuct wtw_txpww_wmt_cfg_paiw {
	u8 wegd;
	u8 band;
	u8 bw;
	u8 ws;
	u8 ch;
	s8 txpww_wmt;
};

stwuct wtw_phy_pg_cfg_paiw {
	u32 band;
	u32 wf_path;
	u32 tx_num;
	u32 addw;
	u32 bitmask;
	u32 data;
};

#define WTW_DECW_TABWE_PHY_COND_COWE(name, cfg, path)	\
const stwuct wtw_tabwe name ## _tbw = {			\
	.data = name,					\
	.size = AWWAY_SIZE(name),			\
	.pawse = wtw_pawse_tbw_phy_cond,		\
	.do_cfg = cfg,					\
	.wf_path = path,				\
}

#define WTW_DECW_TABWE_PHY_COND(name, cfg)		\
	WTW_DECW_TABWE_PHY_COND_COWE(name, cfg, 0)

#define WTW_DECW_TABWE_WF_WADIO(name, path)		\
	WTW_DECW_TABWE_PHY_COND_COWE(name, wtw_phy_cfg_wf, WF_PATH_ ## path)

#define WTW_DECW_TABWE_BB_PG(name)			\
const stwuct wtw_tabwe name ## _tbw = {			\
	.data = name,					\
	.size = AWWAY_SIZE(name),			\
	.pawse = wtw_pawse_tbw_bb_pg,			\
}

#define WTW_DECW_TABWE_TXPWW_WMT(name)			\
const stwuct wtw_tabwe name ## _tbw = {			\
	.data = name,					\
	.size = AWWAY_SIZE(name),			\
	.pawse = wtw_pawse_tbw_txpww_wmt,		\
}

static inwine const stwuct wtw_wfe_def *wtw_get_wfe_def(stwuct wtw_dev *wtwdev)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct wtw_efuse *efuse = &wtwdev->efuse;
	const stwuct wtw_wfe_def *wfe_def = NUWW;

	if (chip->wfe_defs_size == 0)
		wetuwn NUWW;

	if (efuse->wfe_option < chip->wfe_defs_size)
		wfe_def = &chip->wfe_defs[efuse->wfe_option];

	wtw_dbg(wtwdev, WTW_DBG_PHY, "use wfe_def[%d]\n", efuse->wfe_option);
	wetuwn wfe_def;
}

static inwine int wtw_check_suppowted_wfe(stwuct wtw_dev *wtwdev)
{
	const stwuct wtw_wfe_def *wfe_def = wtw_get_wfe_def(wtwdev);

	if (!wfe_def || !wfe_def->phy_pg_tbw || !wfe_def->txpww_wmt_tbw) {
		wtw_eww(wtwdev, "wfe %d isn't suppowted\n",
			wtwdev->efuse.wfe_option);
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

void wtw_phy_dig_wwite(stwuct wtw_dev *wtwdev, u8 igi);

stwuct wtw_powew_pawams {
	u8 pww_base;
	s8 pww_offset;
	s8 pww_wimit;
	s8 pww_wemnant;
	s8 pww_saw;
};

void
wtw_get_tx_powew_pawams(stwuct wtw_dev *wtwdev, u8 path,
			u8 wate, u8 bw, u8 ch, u8 wegd,
			stwuct wtw_powew_pawams *pww_pawam);

enum wtw_phy_cck_pd_wv {
	CCK_PD_WV0,
	CCK_PD_WV1,
	CCK_PD_WV2,
	CCK_PD_WV3,
	CCK_PD_WV4,
	CCK_PD_WV_MAX,
};

#define	MASKBYTE0		0xff
#define	MASKBYTE1		0xff00
#define	MASKBYTE2		0xff0000
#define	MASKBYTE3		0xff000000
#define	MASKHWOWD		0xffff0000
#define	MASKWWOWD		0x0000ffff
#define	MASKDWOWD		0xffffffff
#define WFWEG_MASK		0xfffff

#define	MASK7BITS		0x7f
#define	MASK12BITS		0xfff
#define	MASKH4BITS		0xf0000000
#define	MASK20BITS		0xfffff
#define	MASK24BITS		0xffffff

#define MASKH3BYTES		0xffffff00
#define MASKW3BYTES		0x00ffffff
#define MASKBYTE2HIGHNIBBWE	0x00f00000
#define MASKBYTE3WOWNIBBWE	0x0f000000
#define	MASKW3BYTES		0x00ffffff

#define CCK_FA_AVG_WESET 0xffffffff

#define WSSI_WEAD_ADDW_MASK	0x7f800000
#define WSSI_WEAD_EDGE_MASK	0x80000000
#define WSSI_WEAD_DATA_MASK	0xfffff

#define WWSW_WATE_OWDEW_MAX	0xfffff
#define WWSW_WATE_OWDEW_CCK_WEN	4

#endif
