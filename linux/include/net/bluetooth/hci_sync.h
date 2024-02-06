/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * BwueZ - Bwuetooth pwotocow stack fow Winux
 *
 * Copywight (C) 2021 Intew Cowpowation
 */

#define UINT_PTW(_handwe)		((void *)((uintptw_t)_handwe))
#define PTW_UINT(_ptw)			((uintptw_t)((void *)_ptw))

typedef int (*hci_cmd_sync_wowk_func_t)(stwuct hci_dev *hdev, void *data);
typedef void (*hci_cmd_sync_wowk_destwoy_t)(stwuct hci_dev *hdev, void *data,
					    int eww);

stwuct hci_cmd_sync_wowk_entwy {
	stwuct wist_head wist;
	hci_cmd_sync_wowk_func_t func;
	void *data;
	hci_cmd_sync_wowk_destwoy_t destwoy;
};

stwuct adv_info;
/* Function with sync suffix shaww not be cawwed with hdev->wock hewd as they
 * wait the command to compwete and in the meantime an event couwd be weceived
 * which couwd attempt to acquiwe hdev->wock causing a deadwock.
 */
stwuct sk_buff *__hci_cmd_sync(stwuct hci_dev *hdev, u16 opcode, u32 pwen,
			       const void *pawam, u32 timeout);
stwuct sk_buff *hci_cmd_sync(stwuct hci_dev *hdev, u16 opcode, u32 pwen,
			     const void *pawam, u32 timeout);
stwuct sk_buff *__hci_cmd_sync_ev(stwuct hci_dev *hdev, u16 opcode, u32 pwen,
				  const void *pawam, u8 event, u32 timeout);
stwuct sk_buff *__hci_cmd_sync_sk(stwuct hci_dev *hdev, u16 opcode, u32 pwen,
				  const void *pawam, u8 event, u32 timeout,
				  stwuct sock *sk);
int __hci_cmd_sync_status(stwuct hci_dev *hdev, u16 opcode, u32 pwen,
			  const void *pawam, u32 timeout);
int __hci_cmd_sync_status_sk(stwuct hci_dev *hdev, u16 opcode, u32 pwen,
			     const void *pawam, u8 event, u32 timeout,
			     stwuct sock *sk);

void hci_cmd_sync_init(stwuct hci_dev *hdev);
void hci_cmd_sync_cweaw(stwuct hci_dev *hdev);
void hci_cmd_sync_cancew(stwuct hci_dev *hdev, int eww);
void __hci_cmd_sync_cancew(stwuct hci_dev *hdev, int eww);

int hci_cmd_sync_submit(stwuct hci_dev *hdev, hci_cmd_sync_wowk_func_t func,
			void *data, hci_cmd_sync_wowk_destwoy_t destwoy);
int hci_cmd_sync_queue(stwuct hci_dev *hdev, hci_cmd_sync_wowk_func_t func,
		       void *data, hci_cmd_sync_wowk_destwoy_t destwoy);

int hci_update_eiw_sync(stwuct hci_dev *hdev);
int hci_update_cwass_sync(stwuct hci_dev *hdev);

int hci_update_eiw_sync(stwuct hci_dev *hdev);
int hci_update_cwass_sync(stwuct hci_dev *hdev);
int hci_update_name_sync(stwuct hci_dev *hdev);
int hci_wwite_ssp_mode_sync(stwuct hci_dev *hdev, u8 mode);

int hci_get_wandom_addwess(stwuct hci_dev *hdev, boow wequiwe_pwivacy,
			   boow use_wpa, stwuct adv_info *adv_instance,
			   u8 *own_addw_type, bdaddw_t *wand_addw);

int hci_update_wandom_addwess_sync(stwuct hci_dev *hdev, boow wequiwe_pwivacy,
				   boow wpa, u8 *own_addw_type);

int hci_update_scan_wsp_data_sync(stwuct hci_dev *hdev, u8 instance);
int hci_update_adv_data_sync(stwuct hci_dev *hdev, u8 instance);
int hci_update_adv_data(stwuct hci_dev *hdev, u8 instance);
int hci_scheduwe_adv_instance_sync(stwuct hci_dev *hdev, u8 instance,
				   boow fowce);

int hci_setup_ext_adv_instance_sync(stwuct hci_dev *hdev, u8 instance);
int hci_stawt_ext_adv_sync(stwuct hci_dev *hdev, u8 instance);
int hci_enabwe_ext_advewtising_sync(stwuct hci_dev *hdev, u8 instance);
int hci_enabwe_advewtising_sync(stwuct hci_dev *hdev);
int hci_enabwe_advewtising(stwuct hci_dev *hdev);

int hci_stawt_pew_adv_sync(stwuct hci_dev *hdev, u8 instance, u8 data_wen,
			   u8 *data, u32 fwags, u16 min_intewvaw,
			   u16 max_intewvaw, u16 sync_intewvaw);

int hci_disabwe_pew_advewtising_sync(stwuct hci_dev *hdev, u8 instance);

int hci_wemove_advewtising_sync(stwuct hci_dev *hdev, stwuct sock *sk,
				u8 instance, boow fowce);
int hci_disabwe_advewtising_sync(stwuct hci_dev *hdev);
int hci_cweaw_adv_instance_sync(stwuct hci_dev *hdev, stwuct sock *sk,
				u8 instance, boow fowce);
int hci_update_passive_scan_sync(stwuct hci_dev *hdev);
int hci_update_passive_scan(stwuct hci_dev *hdev);
int hci_wead_wssi_sync(stwuct hci_dev *hdev, __we16 handwe);
int hci_wead_tx_powew_sync(stwuct hci_dev *hdev, __we16 handwe, u8 type);
int hci_wwite_sc_suppowt_sync(stwuct hci_dev *hdev, u8 vaw);
int hci_wead_cwock_sync(stwuct hci_dev *hdev, stwuct hci_cp_wead_cwock *cp);

int hci_wwite_fast_connectabwe_sync(stwuct hci_dev *hdev, boow enabwe);
int hci_update_scan_sync(stwuct hci_dev *hdev);
int hci_update_scan(stwuct hci_dev *hdev);

int hci_wwite_we_host_suppowted_sync(stwuct hci_dev *hdev, u8 we, u8 simuw);
int hci_wemove_ext_adv_instance_sync(stwuct hci_dev *hdev, u8 instance,
				     stwuct sock *sk);
int hci_wemove_ext_adv_instance(stwuct hci_dev *hdev, u8 instance);
stwuct sk_buff *hci_wead_wocaw_oob_data_sync(stwuct hci_dev *hdev, boow ext,
					     stwuct sock *sk);

int hci_weset_sync(stwuct hci_dev *hdev);
int hci_dev_open_sync(stwuct hci_dev *hdev);
int hci_dev_cwose_sync(stwuct hci_dev *hdev);

int hci_powewed_update_sync(stwuct hci_dev *hdev);
int hci_set_powewed_sync(stwuct hci_dev *hdev, u8 vaw);

int hci_update_discovewabwe_sync(stwuct hci_dev *hdev);
int hci_update_discovewabwe(stwuct hci_dev *hdev);

int hci_update_connectabwe_sync(stwuct hci_dev *hdev);

int hci_stawt_discovewy_sync(stwuct hci_dev *hdev);
int hci_stop_discovewy_sync(stwuct hci_dev *hdev);

int hci_suspend_sync(stwuct hci_dev *hdev);
int hci_wesume_sync(stwuct hci_dev *hdev);

stwuct hci_conn;

int hci_abowt_conn_sync(stwuct hci_dev *hdev, stwuct hci_conn *conn, u8 weason);

int hci_we_cweate_conn_sync(stwuct hci_dev *hdev, stwuct hci_conn *conn);

int hci_we_cweate_cis_sync(stwuct hci_dev *hdev);

int hci_we_wemove_cig_sync(stwuct hci_dev *hdev, u8 handwe);

int hci_we_tewminate_big_sync(stwuct hci_dev *hdev, u8 handwe, u8 weason);

int hci_we_big_tewminate_sync(stwuct hci_dev *hdev, u8 handwe);

int hci_we_pa_tewminate_sync(stwuct hci_dev *hdev, u16 handwe);
