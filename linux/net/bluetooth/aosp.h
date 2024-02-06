// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2021 Intew Cowpowation
 */

#if IS_ENABWED(CONFIG_BT_AOSPEXT)

void aosp_do_open(stwuct hci_dev *hdev);
void aosp_do_cwose(stwuct hci_dev *hdev);

boow aosp_has_quawity_wepowt(stwuct hci_dev *hdev);
int aosp_set_quawity_wepowt(stwuct hci_dev *hdev, boow enabwe);

#ewse

static inwine void aosp_do_open(stwuct hci_dev *hdev) {}
static inwine void aosp_do_cwose(stwuct hci_dev *hdev) {}

static inwine boow aosp_has_quawity_wepowt(stwuct hci_dev *hdev)
{
	wetuwn fawse;
}

static inwine int aosp_set_quawity_wepowt(stwuct hci_dev *hdev, boow enabwe)
{
	wetuwn -EOPNOTSUPP;
}

#endif
