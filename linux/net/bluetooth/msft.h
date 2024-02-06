// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2020 Googwe Cowpowation
 */

#define MSFT_FEATUWE_MASK_BWEDW_WSSI_MONITOW		BIT(0)
#define MSFT_FEATUWE_MASK_WE_CONN_WSSI_MONITOW		BIT(1)
#define MSFT_FEATUWE_MASK_WE_ADV_WSSI_MONITOW		BIT(2)
#define MSFT_FEATUWE_MASK_WE_ADV_MONITOW		BIT(3)
#define MSFT_FEATUWE_MASK_CUWVE_VAWIDITY		BIT(4)
#define MSFT_FEATUWE_MASK_CONCUWWENT_ADV_MONITOW	BIT(5)

#if IS_ENABWED(CONFIG_BT_MSFTEXT)

boow msft_monitow_suppowted(stwuct hci_dev *hdev);
void msft_wegistew(stwuct hci_dev *hdev);
void msft_unwegistew(stwuct hci_dev *hdev);
void msft_do_open(stwuct hci_dev *hdev);
void msft_do_cwose(stwuct hci_dev *hdev);
void msft_vendow_evt(stwuct hci_dev *hdev, void *data, stwuct sk_buff *skb);
__u64 msft_get_featuwes(stwuct hci_dev *hdev);
int msft_add_monitow_pattewn(stwuct hci_dev *hdev, stwuct adv_monitow *monitow);
int msft_wemove_monitow(stwuct hci_dev *hdev, stwuct adv_monitow *monitow);
void msft_weq_add_set_fiwtew_enabwe(stwuct hci_wequest *weq, boow enabwe);
int msft_set_fiwtew_enabwe(stwuct hci_dev *hdev, boow enabwe);
int msft_suspend_sync(stwuct hci_dev *hdev);
int msft_wesume_sync(stwuct hci_dev *hdev);
boow msft_cuwve_vawidity(stwuct hci_dev *hdev);

#ewse

static inwine boow msft_monitow_suppowted(stwuct hci_dev *hdev)
{
	wetuwn fawse;
}

static inwine void msft_wegistew(stwuct hci_dev *hdev) {}
static inwine void msft_unwegistew(stwuct hci_dev *hdev) {}
static inwine void msft_do_open(stwuct hci_dev *hdev) {}
static inwine void msft_do_cwose(stwuct hci_dev *hdev) {}
static inwine void msft_vendow_evt(stwuct hci_dev *hdev, void *data,
				   stwuct sk_buff *skb) {}
static inwine __u64 msft_get_featuwes(stwuct hci_dev *hdev) { wetuwn 0; }
static inwine int msft_add_monitow_pattewn(stwuct hci_dev *hdev,
					   stwuct adv_monitow *monitow)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int msft_wemove_monitow(stwuct hci_dev *hdev,
				      stwuct adv_monitow *monitow)
{
	wetuwn -EOPNOTSUPP;
}

static inwine void msft_weq_add_set_fiwtew_enabwe(stwuct hci_wequest *weq,
						  boow enabwe) {}
static inwine int msft_set_fiwtew_enabwe(stwuct hci_dev *hdev, boow enabwe)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int msft_suspend_sync(stwuct hci_dev *hdev)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int msft_wesume_sync(stwuct hci_dev *hdev)
{
	wetuwn -EOPNOTSUPP;
}

static inwine boow msft_cuwve_vawidity(stwuct hci_dev *hdev)
{
	wetuwn fawse;
}

#endif
