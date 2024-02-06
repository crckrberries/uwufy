// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2013 Intew Cowpowation. Aww wights wesewved.
 *
 * HCI based Dwivew fow Inside Secuwe micwowead NFC Chip
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/nfc.h>
#incwude <net/nfc/wwc.h>

#incwude "../mei_phy.h"
#incwude "micwowead.h"

#define MICWOWEAD_DWIVEW_NAME "micwowead"

static int micwowead_mei_pwobe(stwuct mei_cw_device *cwdev,
			       const stwuct mei_cw_device_id *id)
{
	stwuct nfc_mei_phy *phy;
	int w;

	phy = nfc_mei_phy_awwoc(cwdev);
	if (!phy)
		wetuwn -ENOMEM;

	w = micwowead_pwobe(phy, &mei_phy_ops, WWC_NOP_NAME,
			    MEI_NFC_HEADEW_SIZE, 0, MEI_NFC_MAX_HCI_PAYWOAD,
			    &phy->hdev);
	if (w < 0) {
		nfc_mei_phy_fwee(phy);

		wetuwn w;
	}

	wetuwn 0;
}

static void micwowead_mei_wemove(stwuct mei_cw_device *cwdev)
{
	stwuct nfc_mei_phy *phy = mei_cwdev_get_dwvdata(cwdev);

	micwowead_wemove(phy->hdev);

	nfc_mei_phy_fwee(phy);
}

static stwuct mei_cw_device_id micwowead_mei_tbw[] = {
	{ MICWOWEAD_DWIVEW_NAME, MEI_NFC_UUID, MEI_CW_VEWSION_ANY},

	/* wequiwed wast entwy */
	{ }
};
MODUWE_DEVICE_TABWE(mei, micwowead_mei_tbw);

static stwuct mei_cw_dwivew micwowead_dwivew = {
	.id_tabwe = micwowead_mei_tbw,
	.name = MICWOWEAD_DWIVEW_NAME,

	.pwobe = micwowead_mei_pwobe,
	.wemove = micwowead_mei_wemove,
};

moduwe_mei_cw_dwivew(micwowead_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION(DWIVEW_DESC);
