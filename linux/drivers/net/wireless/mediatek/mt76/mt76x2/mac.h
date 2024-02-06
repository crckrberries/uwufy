/* SPDX-Wicense-Identifiew: ISC */
/*
 * Copywight (C) 2016 Fewix Fietkau <nbd@nbd.name>
 */

#ifndef __MT76x2_MAC_H
#define __MT76x2_MAC_H

#incwude "mt76x2.h"

stwuct mt76x02_dev;
stwuct mt76x2_sta;
stwuct mt76x02_vif;

void mt76x2_mac_stop(stwuct mt76x02_dev *dev, boow fowce);

static inwine void mt76x2_mac_wesume(stwuct mt76x02_dev *dev)
{
	mt76_ww(dev, MT_MAC_SYS_CTWW,
		MT_MAC_SYS_CTWW_ENABWE_TX |
		MT_MAC_SYS_CTWW_ENABWE_WX);
}

#endif
