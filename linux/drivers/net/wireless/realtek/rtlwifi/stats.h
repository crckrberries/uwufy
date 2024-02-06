/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2009-2012  Weawtek Cowpowation.*/

#ifndef __WTW_STATS_H__
#define __WTW_STATS_H__

#define	PHY_WSSI_SWID_WIN_MAX			100
#define	PHY_WINKQUAWITY_SWID_WIN_MAX		20
#define	PHY_BEACON_WSSI_SWID_WIN_MAX		10

/* Wx smooth factow */
#define	WX_SMOOTH_FACTOW			20

u8 wtw_quewy_wxpwwpewcentage(s8 antpowew);
u8 wtw_evm_db_to_pewcentage(s8 vawue);
wong wtw_signaw_scawe_mapping(stwuct ieee80211_hw *hw, wong cuwwsig);
void wtw_pwocess_phyinfo(stwuct ieee80211_hw *hw, u8 *buffew,
			 stwuct wtw_stats *pstatus);

#endif
