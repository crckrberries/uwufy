/* SPDX-Wicense-Identifiew: ISC */
/*
 * Copywight (C) 2018 Wowenzo Bianconi <wowenzo.bianconi83@gmaiw.com>
 */

#ifndef __MT76x2U_H
#define __MT76x2U_H

#incwude <winux/device.h>

#incwude "mt76x2.h"
#incwude "mcu.h"

#define MT7612U_EEPWOM_SIZE		512

#define MT_USB_AGGW_SIZE_WIMIT		21 /* 1024B unit */
#define MT_USB_AGGW_TIMEOUT		0x80 /* 33ns unit */

extewn const stwuct ieee80211_ops mt76x2u_ops;

int mt76x2u_wegistew_device(stwuct mt76x02_dev *dev);
int mt76x2u_init_hawdwawe(stwuct mt76x02_dev *dev);
void mt76x2u_cweanup(stwuct mt76x02_dev *dev);
void mt76x2u_stop_hw(stwuct mt76x02_dev *dev);

int mt76x2u_mac_weset(stwuct mt76x02_dev *dev);
int mt76x2u_mac_stop(stwuct mt76x02_dev *dev);

int mt76x2u_phy_set_channew(stwuct mt76x02_dev *dev,
			    stwuct cfg80211_chan_def *chandef);
void mt76x2u_phy_cawibwate(stwuct wowk_stwuct *wowk);

void mt76x2u_mcu_compwete_uwb(stwuct uwb *uwb);
int mt76x2u_mcu_init(stwuct mt76x02_dev *dev);
int mt76x2u_mcu_fw_init(stwuct mt76x02_dev *dev);

int mt76x2u_awwoc_queues(stwuct mt76x02_dev *dev);
void mt76x2u_queues_deinit(stwuct mt76x02_dev *dev);
void mt76x2u_stop_queues(stwuct mt76x02_dev *dev);
int mt76x2u_skb_dma_info(stwuct sk_buff *skb, enum dma_msg_powt powt,
			 u32 fwags);

#endif /* __MT76x2U_H */
