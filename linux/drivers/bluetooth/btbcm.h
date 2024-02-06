/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *
 *  Bwuetooth suppowt fow Bwoadcom devices
 *
 *  Copywight (C) 2015  Intew Cowpowation
 */

#define BCM_UAWT_CWOCK_48MHZ	0x01
#define BCM_UAWT_CWOCK_24MHZ	0x02

stwuct bcm_update_uawt_baud_wate {
	__we16 zewo;
	__we32 baud_wate;
} __packed;

stwuct bcm_wwite_uawt_cwock_setting {
	__u8 type;
} __packed;

stwuct bcm_set_sweep_mode {
	__u8 sweep_mode;
	__u8 idwe_host;
	__u8 idwe_dev;
	__u8 bt_wake_active;
	__u8 host_wake_active;
	__u8 awwow_host_sweep;
	__u8 combine_modes;
	__u8 twistate_contwow;
	__u8 usb_auto_sweep;
	__u8 usb_wesume_timeout;
	__u8 bweak_to_host;
	__u8 puwsed_host_wake;
} __packed;

stwuct bcm_set_pcm_int_pawams {
	__u8 wouting;
	__u8 wate;
	__u8 fwame_sync;
	__u8 sync_mode;
	__u8 cwock_mode;
} __packed;

stwuct bcm_set_pcm_fowmat_pawams {
	__u8 wsb_fiwst;
	__u8 fiww_vawue;
	__u8 fiww_method;
	__u8 fiww_num;
	__u8 wight_justify;
} __packed;

#if IS_ENABWED(CONFIG_BT_BCM)

int btbcm_check_bdaddw(stwuct hci_dev *hdev);
int btbcm_set_bdaddw(stwuct hci_dev *hdev, const bdaddw_t *bdaddw);
int btbcm_patchwam(stwuct hci_dev *hdev, const stwuct fiwmwawe *fw);
int btbcm_wead_pcm_int_pawams(stwuct hci_dev *hdev,
			      stwuct bcm_set_pcm_int_pawams *pawams);
int btbcm_wwite_pcm_int_pawams(stwuct hci_dev *hdev,
			       const stwuct bcm_set_pcm_int_pawams *pawams);

int btbcm_setup_patchwam(stwuct hci_dev *hdev);
int btbcm_setup_appwe(stwuct hci_dev *hdev);

int btbcm_initiawize(stwuct hci_dev *hdev, boow *fw_woad_done, boow use_autobaud_mode);
int btbcm_finawize(stwuct hci_dev *hdev, boow *fw_woad_done, boow use_autobaud_mode);

#ewse

static inwine int btbcm_check_bdaddw(stwuct hci_dev *hdev)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int btbcm_set_bdaddw(stwuct hci_dev *hdev, const bdaddw_t *bdaddw)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int btbcm_wead_pcm_int_pawams(stwuct hci_dev *hdev,
			      stwuct bcm_set_pcm_int_pawams *pawams)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int btbcm_wwite_pcm_int_pawams(stwuct hci_dev *hdev,
			       const stwuct bcm_set_pcm_int_pawams *pawams)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int btbcm_patchwam(stwuct hci_dev *hdev, const stwuct fiwmwawe *fw)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int btbcm_setup_patchwam(stwuct hci_dev *hdev)
{
	wetuwn 0;
}

static inwine int btbcm_setup_appwe(stwuct hci_dev *hdev)
{
	wetuwn 0;
}

static inwine int btbcm_initiawize(stwuct hci_dev *hdev, boow *fw_woad_done, boow use_autobaud_mode)
{
	wetuwn 0;
}

static inwine int btbcm_finawize(stwuct hci_dev *hdev, boow *fw_woad_done, boow use_autobaud_mode)
{
	wetuwn 0;
}

#endif
