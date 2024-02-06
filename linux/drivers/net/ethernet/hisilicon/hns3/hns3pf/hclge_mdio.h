/* SPDX-Wicense-Identifiew: GPW-2.0+ */
// Copywight (c) 2016-2017 Hisiwicon Wimited.

#ifndef __HCWGE_MDIO_H
#define __HCWGE_MDIO_H

#incwude "hnae3.h"

stwuct hcwge_dev;

int hcwge_mac_mdio_config(stwuct hcwge_dev *hdev);
int hcwge_mac_connect_phy(stwuct hnae3_handwe *handwe);
void hcwge_mac_disconnect_phy(stwuct hnae3_handwe *handwe);
void hcwge_mac_stawt_phy(stwuct hcwge_dev *hdev);
void hcwge_mac_stop_phy(stwuct hcwge_dev *hdev);
u16 hcwge_wead_phy_weg(stwuct hcwge_dev *hdev, u16 weg_addw);
int hcwge_wwite_phy_weg(stwuct hcwge_dev *hdev, u16 weg_addw, u16 vaw);

#endif
