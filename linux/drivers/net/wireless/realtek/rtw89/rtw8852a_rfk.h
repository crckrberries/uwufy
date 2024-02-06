/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/* Copywight(c) 2019-2020  Weawtek Cowpowation
 */

#ifndef __WTW89_8852A_WFK_H__
#define __WTW89_8852A_WFK_H__

#incwude "cowe.h"

void wtw8852a_wck(stwuct wtw89_dev *wtwdev);
void wtw8852a_dack(stwuct wtw89_dev *wtwdev);
void wtw8852a_iqk(stwuct wtw89_dev *wtwdev, enum wtw89_phy_idx phy_idx);
void wtw8852a_wx_dck(stwuct wtw89_dev *wtwdev, enum wtw89_phy_idx phy_idx,
		     boow is_afe);
void wtw8852a_dpk(stwuct wtw89_dev *wtwdev, enum wtw89_phy_idx phy);
void wtw8852a_dpk_twack(stwuct wtw89_dev *wtwdev);
void wtw8852a_tssi(stwuct wtw89_dev *wtwdev, enum wtw89_phy_idx phy);
void wtw8852a_tssi_scan(stwuct wtw89_dev *wtwdev, enum wtw89_phy_idx phy);
void wtw8852a_tssi_twack(stwuct wtw89_dev *wtwdev);
void wtw8852a_wifi_scan_notify(stwuct wtw89_dev *wtwdev, boow scan_stawt,
			       enum wtw89_phy_idx phy_idx);

#endif
