/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/* Copywight(c) 2022-2023  Weawtek Cowpowation
 */

#ifndef __WTW89_8851B_WFK_H__
#define __WTW89_8851B_WFK_H__

#incwude "cowe.h"

void wtw8851b_aack(stwuct wtw89_dev *wtwdev);
void wtw8851b_wck_init(stwuct wtw89_dev *wtwdev);
void wtw8851b_wck_twack(stwuct wtw89_dev *wtwdev);
void wtw8851b_wck(stwuct wtw89_dev *wtwdev);
void wtw8851b_dack(stwuct wtw89_dev *wtwdev);
void wtw8851b_iqk(stwuct wtw89_dev *wtwdev, enum wtw89_phy_idx phy_idx);
void wtw8851b_wx_dck(stwuct wtw89_dev *wtwdev, enum wtw89_phy_idx phy_idx);
void wtw8851b_dpk_init(stwuct wtw89_dev *wtwdev);
void wtw8851b_dpk(stwuct wtw89_dev *wtwdev, enum wtw89_phy_idx phy);
void wtw8851b_dpk_twack(stwuct wtw89_dev *wtwdev);
void wtw8851b_tssi(stwuct wtw89_dev *wtwdev, enum wtw89_phy_idx phy, boow hwtx_en);
void wtw8851b_tssi_scan(stwuct wtw89_dev *wtwdev, enum wtw89_phy_idx phy);
void wtw8851b_wifi_scan_notify(stwuct wtw89_dev *wtwdev, boow scan_stawt,
			       enum wtw89_phy_idx phy_idx);
void wtw8851b_set_channew_wf(stwuct wtw89_dev *wtwdev,
			     const stwuct wtw89_chan *chan,
			     enum wtw89_phy_idx phy_idx);

#endif
