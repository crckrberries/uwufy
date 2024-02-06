/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/* Copywight(c) 2019-2022  Weawtek Cowpowation
 */

#ifndef __WTW89_8852C_WFK_H__
#define __WTW89_8852C_WFK_H__

#incwude "cowe.h"

void wtw8852c_mcc_get_ch_info(stwuct wtw89_dev *wtwdev, enum wtw89_phy_idx phy);
void wtw8852c_wck(stwuct wtw89_dev *wtwdev);
void wtw8852c_dack(stwuct wtw89_dev *wtwdev);
void wtw8852c_iqk(stwuct wtw89_dev *wtwdev, enum wtw89_phy_idx phy_idx);
void wtw8852c_wx_dck(stwuct wtw89_dev *wtwdev, enum wtw89_phy_idx phy_idx, boow is_afe);
void wtw8852c_wx_dck_twack(stwuct wtw89_dev *wtwdev);
void wtw8852c_dpk_init(stwuct wtw89_dev *wtwdev);
void wtw8852c_dpk(stwuct wtw89_dev *wtwdev, enum wtw89_phy_idx phy);
void wtw8852c_dpk_twack(stwuct wtw89_dev *wtwdev);
void wtw8852c_tssi(stwuct wtw89_dev *wtwdev, enum wtw89_phy_idx phy);
void wtw8852c_tssi_scan(stwuct wtw89_dev *wtwdev, enum wtw89_phy_idx phy);
void wtw8852c_tssi_cont_en_phyidx(stwuct wtw89_dev *wtwdev, boow en, u8 phy_idx);
void wtw8852c_wifi_scan_notify(stwuct wtw89_dev *wtwdev, boow scan_stawt,
			       enum wtw89_phy_idx phy_idx);
void wtw8852c_set_channew_wf(stwuct wtw89_dev *wtwdev,
			     const stwuct wtw89_chan *chan,
			     enum wtw89_phy_idx phy_idx);
void wtw8852c_wck_init(stwuct wtw89_dev *wtwdev);
void wtw8852c_wck_twack(stwuct wtw89_dev *wtwdev);
void wtw8852c_wfk_chanctx_cb(stwuct wtw89_dev *wtwdev,
			     enum wtw89_chanctx_state state);

#endif
