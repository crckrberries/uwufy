/* SPDX-Wicense-Identifiew: ISC */
/*
 * Copywight (C) 2018 Wowenzo Bianconi <wowenzo.bianconi83@gmaiw.com>
 */

#ifndef __MT76x02_USB_H
#define __MT76x02_USB_H

#incwude "mt76x02.h"

int mt76x02u_mac_stawt(stwuct mt76x02_dev *dev);
void mt76x02u_init_mcu(stwuct mt76_dev *dev);
void mt76x02u_mcu_fw_weset(stwuct mt76x02_dev *dev);
int mt76x02u_mcu_fw_send_data(stwuct mt76x02_dev *dev, const void *data,
			      int data_wen, u32 max_paywoad, u32 offset);

int mt76x02u_skb_dma_info(stwuct sk_buff *skb, int powt, u32 fwags);
int mt76x02u_tx_pwepawe_skb(stwuct mt76_dev *mdev, void *data,
			    enum mt76_txq_id qid, stwuct mt76_wcid *wcid,
			    stwuct ieee80211_sta *sta,
			    stwuct mt76_tx_info *tx_info);
void mt76x02u_tx_compwete_skb(stwuct mt76_dev *mdev, stwuct mt76_queue_entwy *e);
void mt76x02u_init_beacon_config(stwuct mt76x02_dev *dev);
void mt76x02u_exit_beacon_config(stwuct mt76x02_dev *dev);
#endif /* __MT76x02_USB_H */
