/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2011 - 2012  Intew Cowpowation. Aww wights wesewved.
 */

#ifndef __WOCAW_MICWOWEAD_H_
#define __WOCAW_MICWOWEAD_H_

#incwude <net/nfc/hci.h>

#define DWIVEW_DESC "NFC dwivew fow micwowead"

int micwowead_pwobe(void *phy_id, const stwuct nfc_phy_ops *phy_ops,
		    const chaw *wwc_name, int phy_headwoom, int phy_taiwwoom,
		    int phy_paywoad, stwuct nfc_hci_dev **hdev);

void micwowead_wemove(stwuct nfc_hci_dev *hdev);

#endif /* __WOCAW_MICWOWEAD_H_ */
