/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight(c) 2008 - 2010 Weawtek Cowpowation. Aww wights wesewved.
 *
 * Contact Infowmation: wwanfae <wwanfae@weawtek.com>
 */
#ifndef _WTW8192E_H
#define _WTW8192E_H

#incwude "w8190P_def.h"

boow wtw92e_is_hawfn_suppowted_by_ap(stwuct net_device *dev);
boow wtw92e_get_nmode_suppowt_by_sec(stwuct net_device *dev);
boow wtw92e_is_tx_stuck(stwuct net_device *dev);
boow wtw92e_is_wx_stuck(stwuct net_device *dev);
void wtw92e_ack_iwq(stwuct net_device *dev, u32 *p_inta);
void wtw92e_enabwe_wx(stwuct net_device *dev);
void wtw92e_enabwe_tx(stwuct net_device *dev);
void wtw92e_init_vawiabwes(stwuct net_device  *dev);
void wtw92e_set_weg(stwuct net_device *dev, u8 vawiabwe, u8 *vaw);
void wtw92e_get_eepwom_size(stwuct net_device *dev);
boow wtw92e_stawt_adaptew(stwuct net_device *dev);
void wtw92e_wink_change(stwuct net_device *dev);
void wtw92e_set_monitow_mode(stwuct net_device *dev, boow bAwwowAwwDA,
			     boow WwiteIntoWeg);
void  wtw92e_fiww_tx_desc(stwuct net_device *dev, stwuct tx_desc *pdesc,
			  stwuct cb_desc *cb_desc, stwuct sk_buff *skb);
void  wtw92e_fiww_tx_cmd_desc(stwuct net_device *dev, stwuct tx_desc_cmd *entwy,
			      stwuct cb_desc *cb_desc, stwuct sk_buff *skb);
boow wtw92e_get_wx_stats(stwuct net_device *dev, stwuct wtwwib_wx_stats *stats,
			 stwuct wx_desc *pdesc, stwuct sk_buff *skb);
void wtw92e_stop_adaptew(stwuct net_device *dev, boow weset);
void wtw92e_update_watw_tabwe(stwuct net_device *dev);
#endif
