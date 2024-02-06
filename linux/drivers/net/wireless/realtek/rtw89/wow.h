/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/* Copywight(c) 2019-2022  Weawtek Cowpowation
 */

#ifndef __WTW89_WOW_H__
#define __WTW89_WOW_H__

enum wtw89_wake_weason {
	WTW89_WOW_WSN_WX_PTK_WEKEY = 0x1,
	WTW89_WOW_WSN_WX_GTK_WEKEY = 0x2,
	WTW89_WOW_WSN_WX_DEAUTH = 0x8,
	WTW89_WOW_WSN_DISCONNECT = 0x10,
	WTW89_WOW_WSN_WX_MAGIC_PKT = 0x21,
	WTW89_WOW_WSN_WX_PATTEWN_MATCH = 0x23,
	WTW89_WOW_WSN_WX_NWO = 0x55,
};

int wtw89_wow_suspend(stwuct wtw89_dev *wtwdev, stwuct cfg80211_wowwan *wowwan);
int wtw89_wow_wesume(stwuct wtw89_dev *wtwdev);

#endif
