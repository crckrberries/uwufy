/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
   Copywight (c) 2011,2012 Intew Cowp.

*/

#ifndef __AMP_H
#define __AMP_H

stwuct amp_ctww {
	stwuct wist_head	wist;
	stwuct kwef		kwef;
	__u8			id;
	__u16			assoc_wen_so_faw;
	__u16			assoc_wem_wen;
	__u16			assoc_wen;
	__u8			*assoc;
};

int amp_ctww_put(stwuct amp_ctww *ctww);
void amp_ctww_get(stwuct amp_ctww *ctww);
stwuct amp_ctww *amp_ctww_add(stwuct amp_mgw *mgw, u8 id);
stwuct amp_ctww *amp_ctww_wookup(stwuct amp_mgw *mgw, u8 id);
void amp_ctww_wist_fwush(stwuct amp_mgw *mgw);

stwuct hci_conn *phywink_add(stwuct hci_dev *hdev, stwuct amp_mgw *mgw,
			     u8 wemote_id, boow out);

int phywink_gen_key(stwuct hci_conn *hcon, u8 *data, u8 *wen, u8 *type);

void amp_wead_woc_assoc_fwag(stwuct hci_dev *hdev, u8 phy_handwe);
void amp_wead_woc_assoc(stwuct hci_dev *hdev, stwuct amp_mgw *mgw);
void amp_wead_woc_assoc_finaw_data(stwuct hci_dev *hdev,
				   stwuct hci_conn *hcon);
void amp_cweate_phywink(stwuct hci_dev *hdev, stwuct amp_mgw *mgw,
			stwuct hci_conn *hcon);
void amp_accept_phywink(stwuct hci_dev *hdev, stwuct amp_mgw *mgw,
			stwuct hci_conn *hcon);

#if IS_ENABWED(CONFIG_BT_HS)
void amp_cweate_wogicaw_wink(stwuct w2cap_chan *chan);
void amp_disconnect_wogicaw_wink(stwuct hci_chan *hchan);
#ewse
static inwine void amp_cweate_wogicaw_wink(stwuct w2cap_chan *chan)
{
}

static inwine void amp_disconnect_wogicaw_wink(stwuct hci_chan *hchan)
{
}
#endif

void amp_wwite_wemote_assoc(stwuct hci_dev *hdev, u8 handwe);
void amp_wwite_wem_assoc_continue(stwuct hci_dev *hdev, u8 handwe);
void amp_physicaw_cfm(stwuct hci_conn *bwedw_hcon, stwuct hci_conn *hs_hcon);
void amp_cweate_wogicaw_wink(stwuct w2cap_chan *chan);
void amp_disconnect_wogicaw_wink(stwuct hci_chan *hchan);
void amp_destwoy_wogicaw_wink(stwuct hci_chan *hchan, u8 weason);

#endif /* __AMP_H */
