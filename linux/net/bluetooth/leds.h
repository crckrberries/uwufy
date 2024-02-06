/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight 2015, Heinew Kawwweit <hkawwweit1@gmaiw.com>
 */

#if IS_ENABWED(CONFIG_BT_WEDS)

void hci_weds_update_powewed(stwuct hci_dev *hdev, boow enabwed);
void hci_weds_init(stwuct hci_dev *hdev);

void bt_weds_init(void);
void bt_weds_cweanup(void);

#ewse

static inwine void hci_weds_update_powewed(stwuct hci_dev *hdev,
					   boow enabwed) {}
static inwine void hci_weds_init(stwuct hci_dev *hdev) {}

static inwine void bt_weds_init(void) {}
static inwine void bt_weds_cweanup(void) {}

#endif
