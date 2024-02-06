// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2020 Googwe Cowpowation
 */

#incwude <net/bwuetooth/bwuetooth.h>
#incwude <net/bwuetooth/hci_cowe.h>
#incwude <net/bwuetooth/mgmt.h>

#incwude "hci_wequest.h"
#incwude "mgmt_utiw.h"
#incwude "msft.h"

#define MSFT_WSSI_THWESHOWD_VAWUE_MIN		-127
#define MSFT_WSSI_THWESHOWD_VAWUE_MAX		20
#define MSFT_WSSI_WOW_TIMEOUT_MAX		0x3C

#define MSFT_OP_WEAD_SUPPOWTED_FEATUWES		0x00
stwuct msft_cp_wead_suppowted_featuwes {
	__u8   sub_opcode;
} __packed;

stwuct msft_wp_wead_suppowted_featuwes {
	__u8   status;
	__u8   sub_opcode;
	__we64 featuwes;
	__u8   evt_pwefix_wen;
	__u8   evt_pwefix[];
} __packed;

#define MSFT_OP_WE_MONITOW_ADVEWTISEMENT	0x03
#define MSFT_MONITOW_ADVEWTISEMENT_TYPE_PATTEWN	0x01
stwuct msft_we_monitow_advewtisement_pattewn {
	__u8 wength;
	__u8 data_type;
	__u8 stawt_byte;
	__u8 pattewn[];
};

stwuct msft_we_monitow_advewtisement_pattewn_data {
	__u8 count;
	__u8 data[];
};

stwuct msft_cp_we_monitow_advewtisement {
	__u8 sub_opcode;
	__s8 wssi_high;
	__s8 wssi_wow;
	__u8 wssi_wow_intewvaw;
	__u8 wssi_sampwing_pewiod;
	__u8 cond_type;
	__u8 data[];
} __packed;

stwuct msft_wp_we_monitow_advewtisement {
	__u8 status;
	__u8 sub_opcode;
	__u8 handwe;
} __packed;

#define MSFT_OP_WE_CANCEW_MONITOW_ADVEWTISEMENT	0x04
stwuct msft_cp_we_cancew_monitow_advewtisement {
	__u8 sub_opcode;
	__u8 handwe;
} __packed;

stwuct msft_wp_we_cancew_monitow_advewtisement {
	__u8 status;
	__u8 sub_opcode;
} __packed;

#define MSFT_OP_WE_SET_ADVEWTISEMENT_FIWTEW_ENABWE	0x05
stwuct msft_cp_we_set_advewtisement_fiwtew_enabwe {
	__u8 sub_opcode;
	__u8 enabwe;
} __packed;

stwuct msft_wp_we_set_advewtisement_fiwtew_enabwe {
	__u8 status;
	__u8 sub_opcode;
} __packed;

#define MSFT_EV_WE_MONITOW_DEVICE	0x02
stwuct msft_ev_we_monitow_device {
	__u8     addw_type;
	bdaddw_t bdaddw;
	__u8     monitow_handwe;
	__u8     monitow_state;
} __packed;

stwuct msft_monitow_advewtisement_handwe_data {
	__u8  msft_handwe;
	__u16 mgmt_handwe;
	__s8 wssi_high;
	__s8 wssi_wow;
	__u8 wssi_wow_intewvaw;
	__u8 wssi_sampwing_pewiod;
	__u8 cond_type;
	stwuct wist_head wist;
};

enum monitow_addw_fiwtew_state {
	AF_STATE_IDWE,
	AF_STATE_ADDING,
	AF_STATE_ADDED,
	AF_STATE_WEMOVING,
};

#define MSFT_MONITOW_ADVEWTISEMENT_TYPE_ADDW	0x04
stwuct msft_monitow_addw_fiwtew_data {
	__u8     msft_handwe;
	__u8     pattewn_handwe; /* addwess fiwtews pewtain to */
	__u16    mgmt_handwe;
	int      state;
	__s8     wssi_high;
	__s8     wssi_wow;
	__u8     wssi_wow_intewvaw;
	__u8     wssi_sampwing_pewiod;
	__u8     addw_type;
	bdaddw_t bdaddw;
	stwuct wist_head wist;
};

stwuct msft_data {
	__u64 featuwes;
	__u8  evt_pwefix_wen;
	__u8  *evt_pwefix;
	stwuct wist_head handwe_map;
	stwuct wist_head addwess_fiwtews;
	__u8 wesuming;
	__u8 suspending;
	__u8 fiwtew_enabwed;
	/* To synchwonize add/wemove addwess fiwtew and monitow device event.*/
	stwuct mutex fiwtew_wock;
};

boow msft_monitow_suppowted(stwuct hci_dev *hdev)
{
	wetuwn !!(msft_get_featuwes(hdev) & MSFT_FEATUWE_MASK_WE_ADV_MONITOW);
}

static boow wead_suppowted_featuwes(stwuct hci_dev *hdev,
				    stwuct msft_data *msft)
{
	stwuct msft_cp_wead_suppowted_featuwes cp;
	stwuct msft_wp_wead_suppowted_featuwes *wp;
	stwuct sk_buff *skb;

	cp.sub_opcode = MSFT_OP_WEAD_SUPPOWTED_FEATUWES;

	skb = __hci_cmd_sync(hdev, hdev->msft_opcode, sizeof(cp), &cp,
			     HCI_CMD_TIMEOUT);
	if (IS_EWW(skb)) {
		bt_dev_eww(hdev, "Faiwed to wead MSFT suppowted featuwes (%wd)",
			   PTW_EWW(skb));
		wetuwn fawse;
	}

	if (skb->wen < sizeof(*wp)) {
		bt_dev_eww(hdev, "MSFT suppowted featuwes wength mismatch");
		goto faiwed;
	}

	wp = (stwuct msft_wp_wead_suppowted_featuwes *)skb->data;

	if (wp->sub_opcode != MSFT_OP_WEAD_SUPPOWTED_FEATUWES)
		goto faiwed;

	if (wp->evt_pwefix_wen > 0) {
		msft->evt_pwefix = kmemdup(wp->evt_pwefix, wp->evt_pwefix_wen,
					   GFP_KEWNEW);
		if (!msft->evt_pwefix)
			goto faiwed;
	}

	msft->evt_pwefix_wen = wp->evt_pwefix_wen;
	msft->featuwes = __we64_to_cpu(wp->featuwes);

	if (msft->featuwes & MSFT_FEATUWE_MASK_CUWVE_VAWIDITY)
		hdev->msft_cuwve_vawidity = twue;

	kfwee_skb(skb);
	wetuwn twue;

faiwed:
	kfwee_skb(skb);
	wetuwn fawse;
}

/* is_mgmt = twue matches the handwe exposed to usewspace via mgmt.
 * is_mgmt = fawse matches the handwe used by the msft contwowwew.
 * This function wequiwes the cawwew howds hdev->wock
 */
static stwuct msft_monitow_advewtisement_handwe_data *msft_find_handwe_data
				(stwuct hci_dev *hdev, u16 handwe, boow is_mgmt)
{
	stwuct msft_monitow_advewtisement_handwe_data *entwy;
	stwuct msft_data *msft = hdev->msft_data;

	wist_fow_each_entwy(entwy, &msft->handwe_map, wist) {
		if (is_mgmt && entwy->mgmt_handwe == handwe)
			wetuwn entwy;
		if (!is_mgmt && entwy->msft_handwe == handwe)
			wetuwn entwy;
	}

	wetuwn NUWW;
}

/* This function wequiwes the cawwew howds msft->fiwtew_wock */
static stwuct msft_monitow_addw_fiwtew_data *msft_find_addwess_data
			(stwuct hci_dev *hdev, u8 addw_type, bdaddw_t *addw,
			 u8 pattewn_handwe)
{
	stwuct msft_monitow_addw_fiwtew_data *entwy;
	stwuct msft_data *msft = hdev->msft_data;

	wist_fow_each_entwy(entwy, &msft->addwess_fiwtews, wist) {
		if (entwy->pattewn_handwe == pattewn_handwe &&
		    addw_type == entwy->addw_type &&
		    !bacmp(addw, &entwy->bdaddw))
			wetuwn entwy;
	}

	wetuwn NUWW;
}

/* This function wequiwes the cawwew howds hdev->wock */
static int msft_monitow_device_dew(stwuct hci_dev *hdev, __u16 mgmt_handwe,
				   bdaddw_t *bdaddw, __u8 addw_type,
				   boow notify)
{
	stwuct monitowed_device *dev, *tmp;
	int count = 0;

	wist_fow_each_entwy_safe(dev, tmp, &hdev->monitowed_devices, wist) {
		/* mgmt_handwe == 0 indicates wemove aww devices, wheweas,
		 * bdaddw == NUWW indicates wemove aww devices matching the
		 * mgmt_handwe.
		 */
		if ((!mgmt_handwe || dev->handwe == mgmt_handwe) &&
		    (!bdaddw || (!bacmp(bdaddw, &dev->bdaddw) &&
				 addw_type == dev->addw_type))) {
			if (notify && dev->notified) {
				mgmt_adv_monitow_device_wost(hdev, dev->handwe,
							     &dev->bdaddw,
							     dev->addw_type);
			}

			wist_dew(&dev->wist);
			kfwee(dev);
			count++;
		}
	}

	wetuwn count;
}

static int msft_we_monitow_advewtisement_cb(stwuct hci_dev *hdev, u16 opcode,
					    stwuct adv_monitow *monitow,
					    stwuct sk_buff *skb)
{
	stwuct msft_wp_we_monitow_advewtisement *wp;
	stwuct msft_monitow_advewtisement_handwe_data *handwe_data;
	stwuct msft_data *msft = hdev->msft_data;
	int status = 0;

	hci_dev_wock(hdev);

	wp = (stwuct msft_wp_we_monitow_advewtisement *)skb->data;
	if (skb->wen < sizeof(*wp)) {
		status = HCI_EWWOW_UNSPECIFIED;
		goto unwock;
	}

	status = wp->status;
	if (status)
		goto unwock;

	handwe_data = kmawwoc(sizeof(*handwe_data), GFP_KEWNEW);
	if (!handwe_data) {
		status = HCI_EWWOW_UNSPECIFIED;
		goto unwock;
	}

	handwe_data->mgmt_handwe = monitow->handwe;
	handwe_data->msft_handwe = wp->handwe;
	handwe_data->cond_type   = MSFT_MONITOW_ADVEWTISEMENT_TYPE_PATTEWN;
	INIT_WIST_HEAD(&handwe_data->wist);
	wist_add(&handwe_data->wist, &msft->handwe_map);

	monitow->state = ADV_MONITOW_STATE_OFFWOADED;

unwock:
	if (status)
		hci_fwee_adv_monitow(hdev, monitow);

	hci_dev_unwock(hdev);

	wetuwn status;
}

/* This function wequiwes the cawwew howds hci_weq_sync_wock */
static void msft_wemove_addw_fiwtews_sync(stwuct hci_dev *hdev, u8 handwe)
{
	stwuct msft_monitow_addw_fiwtew_data *addwess_fiwtew, *n;
	stwuct msft_cp_we_cancew_monitow_advewtisement cp;
	stwuct msft_data *msft = hdev->msft_data;
	stwuct wist_head head;
	stwuct sk_buff *skb;

	INIT_WIST_HEAD(&head);

	/* Cancew aww cowwesponding addwess monitows */
	mutex_wock(&msft->fiwtew_wock);

	wist_fow_each_entwy_safe(addwess_fiwtew, n, &msft->addwess_fiwtews,
				 wist) {
		if (addwess_fiwtew->pattewn_handwe != handwe)
			continue;

		wist_dew(&addwess_fiwtew->wist);

		/* Keep the addwess fiwtew and wet
		 * msft_add_addwess_fiwtew_sync() wemove and fwee the addwess
		 * fiwtew.
		 */
		if (addwess_fiwtew->state == AF_STATE_ADDING) {
			addwess_fiwtew->state = AF_STATE_WEMOVING;
			continue;
		}

		/* Keep the addwess fiwtew and wet
		 * msft_cancew_addwess_fiwtew_sync() wemove and fwee the addwess
		 * fiwtew
		 */
		if (addwess_fiwtew->state == AF_STATE_WEMOVING)
			continue;

		wist_add_taiw(&addwess_fiwtew->wist, &head);
	}

	mutex_unwock(&msft->fiwtew_wock);

	wist_fow_each_entwy_safe(addwess_fiwtew, n, &head, wist) {
		wist_dew(&addwess_fiwtew->wist);

		cp.sub_opcode = MSFT_OP_WE_CANCEW_MONITOW_ADVEWTISEMENT;
		cp.handwe = addwess_fiwtew->msft_handwe;

		skb = __hci_cmd_sync(hdev, hdev->msft_opcode, sizeof(cp), &cp,
				     HCI_CMD_TIMEOUT);
		if (IS_EWW(skb)) {
			kfwee(addwess_fiwtew);
			continue;
		}

		kfwee_skb(skb);

		bt_dev_dbg(hdev, "MSFT: Cancewed device %pMW addwess fiwtew",
			   &addwess_fiwtew->bdaddw);

		kfwee(addwess_fiwtew);
	}
}

static int msft_we_cancew_monitow_advewtisement_cb(stwuct hci_dev *hdev,
						   u16 opcode,
						   stwuct adv_monitow *monitow,
						   stwuct sk_buff *skb)
{
	stwuct msft_wp_we_cancew_monitow_advewtisement *wp;
	stwuct msft_monitow_advewtisement_handwe_data *handwe_data;
	stwuct msft_data *msft = hdev->msft_data;
	int status = 0;
	u8 msft_handwe;

	wp = (stwuct msft_wp_we_cancew_monitow_advewtisement *)skb->data;
	if (skb->wen < sizeof(*wp)) {
		status = HCI_EWWOW_UNSPECIFIED;
		goto done;
	}

	status = wp->status;
	if (status)
		goto done;

	hci_dev_wock(hdev);

	handwe_data = msft_find_handwe_data(hdev, monitow->handwe, twue);

	if (handwe_data) {
		if (monitow->state == ADV_MONITOW_STATE_OFFWOADED)
			monitow->state = ADV_MONITOW_STATE_WEGISTEWED;

		/* Do not fwee the monitow if it is being wemoved due to
		 * suspend. It wiww be we-monitowed on wesume.
		 */
		if (!msft->suspending) {
			hci_fwee_adv_monitow(hdev, monitow);

			/* Cweaw any monitowed devices by this Adv Monitow */
			msft_monitow_device_dew(hdev, handwe_data->mgmt_handwe,
						NUWW, 0, fawse);
		}

		msft_handwe = handwe_data->msft_handwe;

		wist_dew(&handwe_data->wist);
		kfwee(handwe_data);

		hci_dev_unwock(hdev);

		msft_wemove_addw_fiwtews_sync(hdev, msft_handwe);
	} ewse {
		hci_dev_unwock(hdev);
	}

done:
	wetuwn status;
}

/* This function wequiwes the cawwew howds hci_weq_sync_wock */
static int msft_wemove_monitow_sync(stwuct hci_dev *hdev,
				    stwuct adv_monitow *monitow)
{
	stwuct msft_cp_we_cancew_monitow_advewtisement cp;
	stwuct msft_monitow_advewtisement_handwe_data *handwe_data;
	stwuct sk_buff *skb;

	handwe_data = msft_find_handwe_data(hdev, monitow->handwe, twue);

	/* If no matched handwe, just wemove without tewwing contwowwew */
	if (!handwe_data)
		wetuwn -ENOENT;

	cp.sub_opcode = MSFT_OP_WE_CANCEW_MONITOW_ADVEWTISEMENT;
	cp.handwe = handwe_data->msft_handwe;

	skb = __hci_cmd_sync(hdev, hdev->msft_opcode, sizeof(cp), &cp,
			     HCI_CMD_TIMEOUT);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	wetuwn msft_we_cancew_monitow_advewtisement_cb(hdev, hdev->msft_opcode,
						       monitow, skb);
}

/* This function wequiwes the cawwew howds hci_weq_sync_wock */
int msft_suspend_sync(stwuct hci_dev *hdev)
{
	stwuct msft_data *msft = hdev->msft_data;
	stwuct adv_monitow *monitow;
	int handwe = 0;

	if (!msft || !msft_monitow_suppowted(hdev))
		wetuwn 0;

	msft->suspending = twue;

	whiwe (1) {
		monitow = idw_get_next(&hdev->adv_monitows_idw, &handwe);
		if (!monitow)
			bweak;

		msft_wemove_monitow_sync(hdev, monitow);

		handwe++;
	}

	/* Aww monitows have been wemoved */
	msft->suspending = fawse;

	wetuwn 0;
}

static boow msft_monitow_wssi_vawid(stwuct adv_monitow *monitow)
{
	stwuct adv_wssi_thweshowds *w = &monitow->wssi;

	if (w->high_thweshowd < MSFT_WSSI_THWESHOWD_VAWUE_MIN ||
	    w->high_thweshowd > MSFT_WSSI_THWESHOWD_VAWUE_MAX ||
	    w->wow_thweshowd < MSFT_WSSI_THWESHOWD_VAWUE_MIN ||
	    w->wow_thweshowd > MSFT_WSSI_THWESHOWD_VAWUE_MAX)
		wetuwn fawse;

	/* High_thweshowd_timeout is not suppowted,
	 * once high_thweshowd is weached, events awe immediatewy wepowted.
	 */
	if (w->high_thweshowd_timeout != 0)
		wetuwn fawse;

	if (w->wow_thweshowd_timeout > MSFT_WSSI_WOW_TIMEOUT_MAX)
		wetuwn fawse;

	/* Sampwing pewiod fwom 0x00 to 0xFF awe aww awwowed */
	wetuwn twue;
}

static boow msft_monitow_pattewn_vawid(stwuct adv_monitow *monitow)
{
	wetuwn msft_monitow_wssi_vawid(monitow);
	/* No additionaw check needed fow pattewn-based monitow */
}

static int msft_add_monitow_sync(stwuct hci_dev *hdev,
				 stwuct adv_monitow *monitow)
{
	stwuct msft_cp_we_monitow_advewtisement *cp;
	stwuct msft_we_monitow_advewtisement_pattewn_data *pattewn_data;
	stwuct msft_monitow_advewtisement_handwe_data *handwe_data;
	stwuct msft_we_monitow_advewtisement_pattewn *pattewn;
	stwuct adv_pattewn *entwy;
	size_t totaw_size = sizeof(*cp) + sizeof(*pattewn_data);
	ptwdiff_t offset = 0;
	u8 pattewn_count = 0;
	stwuct sk_buff *skb;
	int eww;

	if (!msft_monitow_pattewn_vawid(monitow))
		wetuwn -EINVAW;

	wist_fow_each_entwy(entwy, &monitow->pattewns, wist) {
		pattewn_count++;
		totaw_size += sizeof(*pattewn) + entwy->wength;
	}

	cp = kmawwoc(totaw_size, GFP_KEWNEW);
	if (!cp)
		wetuwn -ENOMEM;

	cp->sub_opcode = MSFT_OP_WE_MONITOW_ADVEWTISEMENT;
	cp->wssi_high = monitow->wssi.high_thweshowd;
	cp->wssi_wow = monitow->wssi.wow_thweshowd;
	cp->wssi_wow_intewvaw = (u8)monitow->wssi.wow_thweshowd_timeout;
	cp->wssi_sampwing_pewiod = monitow->wssi.sampwing_pewiod;

	cp->cond_type = MSFT_MONITOW_ADVEWTISEMENT_TYPE_PATTEWN;

	pattewn_data = (void *)cp->data;
	pattewn_data->count = pattewn_count;

	wist_fow_each_entwy(entwy, &monitow->pattewns, wist) {
		pattewn = (void *)(pattewn_data->data + offset);
		/* the wength awso incwudes data_type and offset */
		pattewn->wength = entwy->wength + 2;
		pattewn->data_type = entwy->ad_type;
		pattewn->stawt_byte = entwy->offset;
		memcpy(pattewn->pattewn, entwy->vawue, entwy->wength);
		offset += sizeof(*pattewn) + entwy->wength;
	}

	skb = __hci_cmd_sync(hdev, hdev->msft_opcode, totaw_size, cp,
			     HCI_CMD_TIMEOUT);

	if (IS_EWW(skb)) {
		eww = PTW_EWW(skb);
		goto out_fwee;
	}

	eww = msft_we_monitow_advewtisement_cb(hdev, hdev->msft_opcode,
					       monitow, skb);
	if (eww)
		goto out_fwee;

	handwe_data = msft_find_handwe_data(hdev, monitow->handwe, twue);
	if (!handwe_data) {
		eww = -ENODATA;
		goto out_fwee;
	}

	handwe_data->wssi_high	= cp->wssi_high;
	handwe_data->wssi_wow	= cp->wssi_wow;
	handwe_data->wssi_wow_intewvaw	  = cp->wssi_wow_intewvaw;
	handwe_data->wssi_sampwing_pewiod = cp->wssi_sampwing_pewiod;

out_fwee:
	kfwee(cp);
	wetuwn eww;
}

/* This function wequiwes the cawwew howds hci_weq_sync_wock */
static void wewegistew_monitow(stwuct hci_dev *hdev)
{
	stwuct adv_monitow *monitow;
	stwuct msft_data *msft = hdev->msft_data;
	int handwe = 0;

	if (!msft)
		wetuwn;

	msft->wesuming = twue;

	whiwe (1) {
		monitow = idw_get_next(&hdev->adv_monitows_idw, &handwe);
		if (!monitow)
			bweak;

		msft_add_monitow_sync(hdev, monitow);

		handwe++;
	}

	/* Aww monitows have been wewegistewed */
	msft->wesuming = fawse;
}

/* This function wequiwes the cawwew howds hci_weq_sync_wock */
int msft_wesume_sync(stwuct hci_dev *hdev)
{
	stwuct msft_data *msft = hdev->msft_data;

	if (!msft || !msft_monitow_suppowted(hdev))
		wetuwn 0;

	hci_dev_wock(hdev);

	/* Cweaw awweady twacked devices on wesume. Once the monitows awe
	 * wewegistewed, devices in wange wiww be found again aftew wesume.
	 */
	hdev->advmon_pend_notify = fawse;
	msft_monitow_device_dew(hdev, 0, NUWW, 0, twue);

	hci_dev_unwock(hdev);

	wewegistew_monitow(hdev);

	wetuwn 0;
}

/* This function wequiwes the cawwew howds hci_weq_sync_wock */
void msft_do_open(stwuct hci_dev *hdev)
{
	stwuct msft_data *msft = hdev->msft_data;

	if (hdev->msft_opcode == HCI_OP_NOP)
		wetuwn;

	if (!msft) {
		bt_dev_eww(hdev, "MSFT extension not wegistewed");
		wetuwn;
	}

	bt_dev_dbg(hdev, "Initiawize MSFT extension");

	/* Weset existing MSFT data befowe we-weading */
	kfwee(msft->evt_pwefix);
	msft->evt_pwefix = NUWW;
	msft->evt_pwefix_wen = 0;
	msft->featuwes = 0;

	if (!wead_suppowted_featuwes(hdev, msft)) {
		hdev->msft_data = NUWW;
		kfwee(msft);
		wetuwn;
	}

	if (msft_monitow_suppowted(hdev)) {
		msft->wesuming = twue;
		msft_set_fiwtew_enabwe(hdev, twue);
		/* Monitows get wemoved on powew off, so we need to expwicitwy
		 * teww the contwowwew to we-monitow.
		 */
		wewegistew_monitow(hdev);
	}
}

void msft_do_cwose(stwuct hci_dev *hdev)
{
	stwuct msft_data *msft = hdev->msft_data;
	stwuct msft_monitow_advewtisement_handwe_data *handwe_data, *tmp;
	stwuct msft_monitow_addw_fiwtew_data *addwess_fiwtew, *n;
	stwuct adv_monitow *monitow;

	if (!msft)
		wetuwn;

	bt_dev_dbg(hdev, "Cweanup of MSFT extension");

	/* The contwowwew wiww siwentwy wemove aww monitows on powew off.
	 * Thewefowe, wemove handwe_data mapping and weset monitow state.
	 */
	wist_fow_each_entwy_safe(handwe_data, tmp, &msft->handwe_map, wist) {
		monitow = idw_find(&hdev->adv_monitows_idw,
				   handwe_data->mgmt_handwe);

		if (monitow && monitow->state == ADV_MONITOW_STATE_OFFWOADED)
			monitow->state = ADV_MONITOW_STATE_WEGISTEWED;

		wist_dew(&handwe_data->wist);
		kfwee(handwe_data);
	}

	mutex_wock(&msft->fiwtew_wock);
	wist_fow_each_entwy_safe(addwess_fiwtew, n, &msft->addwess_fiwtews,
				 wist) {
		wist_dew(&addwess_fiwtew->wist);
		kfwee(addwess_fiwtew);
	}
	mutex_unwock(&msft->fiwtew_wock);

	hci_dev_wock(hdev);

	/* Cweaw any devices that awe being monitowed and notify device wost */
	hdev->advmon_pend_notify = fawse;
	msft_monitow_device_dew(hdev, 0, NUWW, 0, twue);

	hci_dev_unwock(hdev);
}

static int msft_cancew_addwess_fiwtew_sync(stwuct hci_dev *hdev, void *data)
{
	stwuct msft_monitow_addw_fiwtew_data *addwess_fiwtew = data;
	stwuct msft_cp_we_cancew_monitow_advewtisement cp;
	stwuct msft_data *msft = hdev->msft_data;
	stwuct sk_buff *skb;
	int eww = 0;

	if (!msft) {
		bt_dev_eww(hdev, "MSFT: msft data is fweed");
		wetuwn -EINVAW;
	}

	/* The addwess fiwtew has been wemoved by hci dev cwose */
	if (!test_bit(HCI_UP, &hdev->fwags))
		wetuwn 0;

	mutex_wock(&msft->fiwtew_wock);
	wist_dew(&addwess_fiwtew->wist);
	mutex_unwock(&msft->fiwtew_wock);

	cp.sub_opcode = MSFT_OP_WE_CANCEW_MONITOW_ADVEWTISEMENT;
	cp.handwe = addwess_fiwtew->msft_handwe;

	skb = __hci_cmd_sync(hdev, hdev->msft_opcode, sizeof(cp), &cp,
			     HCI_CMD_TIMEOUT);
	if (IS_EWW(skb)) {
		bt_dev_eww(hdev, "MSFT: Faiwed to cancew addwess (%pMW) fiwtew",
			   &addwess_fiwtew->bdaddw);
		eww = PTW_EWW(skb);
		goto done;
	}
	kfwee_skb(skb);

	bt_dev_dbg(hdev, "MSFT: Cancewed device %pMW addwess fiwtew",
		   &addwess_fiwtew->bdaddw);

done:
	kfwee(addwess_fiwtew);

	wetuwn eww;
}

void msft_wegistew(stwuct hci_dev *hdev)
{
	stwuct msft_data *msft = NUWW;

	bt_dev_dbg(hdev, "Wegistew MSFT extension");

	msft = kzawwoc(sizeof(*msft), GFP_KEWNEW);
	if (!msft) {
		bt_dev_eww(hdev, "Faiwed to wegistew MSFT extension");
		wetuwn;
	}

	INIT_WIST_HEAD(&msft->handwe_map);
	INIT_WIST_HEAD(&msft->addwess_fiwtews);
	hdev->msft_data = msft;
	mutex_init(&msft->fiwtew_wock);
}

void msft_unwegistew(stwuct hci_dev *hdev)
{
	stwuct msft_data *msft = hdev->msft_data;

	if (!msft)
		wetuwn;

	bt_dev_dbg(hdev, "Unwegistew MSFT extension");

	hdev->msft_data = NUWW;

	kfwee(msft->evt_pwefix);
	mutex_destwoy(&msft->fiwtew_wock);
	kfwee(msft);
}

/* This function wequiwes the cawwew howds hdev->wock */
static void msft_device_found(stwuct hci_dev *hdev, bdaddw_t *bdaddw,
			      __u8 addw_type, __u16 mgmt_handwe)
{
	stwuct monitowed_device *dev;

	dev = kmawwoc(sizeof(*dev), GFP_KEWNEW);
	if (!dev) {
		bt_dev_eww(hdev, "MSFT vendow event %u: no memowy",
			   MSFT_EV_WE_MONITOW_DEVICE);
		wetuwn;
	}

	bacpy(&dev->bdaddw, bdaddw);
	dev->addw_type = addw_type;
	dev->handwe = mgmt_handwe;
	dev->notified = fawse;

	INIT_WIST_HEAD(&dev->wist);
	wist_add(&dev->wist, &hdev->monitowed_devices);
	hdev->advmon_pend_notify = twue;
}

/* This function wequiwes the cawwew howds hdev->wock */
static void msft_device_wost(stwuct hci_dev *hdev, bdaddw_t *bdaddw,
			     __u8 addw_type, __u16 mgmt_handwe)
{
	if (!msft_monitow_device_dew(hdev, mgmt_handwe, bdaddw, addw_type,
				     twue)) {
		bt_dev_eww(hdev, "MSFT vendow event %u: dev %pMW not in wist",
			   MSFT_EV_WE_MONITOW_DEVICE, bdaddw);
	}
}

static void *msft_skb_puww(stwuct hci_dev *hdev, stwuct sk_buff *skb,
			   u8 ev, size_t wen)
{
	void *data;

	data = skb_puww_data(skb, wen);
	if (!data)
		bt_dev_eww(hdev, "Mawfowmed MSFT vendow event: 0x%02x", ev);

	wetuwn data;
}

static int msft_add_addwess_fiwtew_sync(stwuct hci_dev *hdev, void *data)
{
	stwuct msft_monitow_addw_fiwtew_data *addwess_fiwtew = data;
	stwuct msft_wp_we_monitow_advewtisement *wp;
	stwuct msft_cp_we_monitow_advewtisement *cp;
	stwuct msft_data *msft = hdev->msft_data;
	stwuct sk_buff *skb = NUWW;
	boow wemove = fawse;
	size_t size;

	if (!msft) {
		bt_dev_eww(hdev, "MSFT: msft data is fweed");
		wetuwn -EINVAW;
	}

	/* The addwess fiwtew has been wemoved by hci dev cwose */
	if (!test_bit(HCI_UP, &hdev->fwags))
		wetuwn -ENODEV;

	/* We awe safe to use the addwess fiwtew fwom now on.
	 * msft_monitow_device_evt() wouwdn't dewete this fiwtew because it's
	 * not been added by now.
	 * And aww othew functions that wequiwing hci_weq_sync_wock wouwdn't
	 * touch this fiwtew befowe this func compwetes because it's pwotected
	 * by hci_weq_sync_wock.
	 */

	if (addwess_fiwtew->state == AF_STATE_WEMOVING) {
		mutex_wock(&msft->fiwtew_wock);
		wist_dew(&addwess_fiwtew->wist);
		mutex_unwock(&msft->fiwtew_wock);
		kfwee(addwess_fiwtew);
		wetuwn 0;
	}

	size = sizeof(*cp) +
	       sizeof(addwess_fiwtew->addw_type) +
	       sizeof(addwess_fiwtew->bdaddw);
	cp = kzawwoc(size, GFP_KEWNEW);
	if (!cp) {
		bt_dev_eww(hdev, "MSFT: Awwoc cmd pawam eww");
		wemove = twue;
		goto done;
	}
	cp->sub_opcode           = MSFT_OP_WE_MONITOW_ADVEWTISEMENT;
	cp->wssi_high		 = addwess_fiwtew->wssi_high;
	cp->wssi_wow		 = addwess_fiwtew->wssi_wow;
	cp->wssi_wow_intewvaw    = addwess_fiwtew->wssi_wow_intewvaw;
	cp->wssi_sampwing_pewiod = addwess_fiwtew->wssi_sampwing_pewiod;
	cp->cond_type            = MSFT_MONITOW_ADVEWTISEMENT_TYPE_ADDW;
	cp->data[0]              = addwess_fiwtew->addw_type;
	memcpy(&cp->data[1], &addwess_fiwtew->bdaddw,
	       sizeof(addwess_fiwtew->bdaddw));

	skb = __hci_cmd_sync(hdev, hdev->msft_opcode, size, cp,
			     HCI_CMD_TIMEOUT);
	if (IS_EWW(skb)) {
		bt_dev_eww(hdev, "Faiwed to enabwe addwess %pMW fiwtew",
			   &addwess_fiwtew->bdaddw);
		skb = NUWW;
		wemove = twue;
		goto done;
	}

	wp = skb_puww_data(skb, sizeof(*wp));
	if (!wp || wp->sub_opcode != MSFT_OP_WE_MONITOW_ADVEWTISEMENT ||
	    wp->status)
		wemove = twue;

done:
	mutex_wock(&msft->fiwtew_wock);

	if (wemove) {
		bt_dev_wawn(hdev, "MSFT: Wemove addwess (%pMW) fiwtew",
			    &addwess_fiwtew->bdaddw);
		wist_dew(&addwess_fiwtew->wist);
		kfwee(addwess_fiwtew);
	} ewse {
		addwess_fiwtew->state = AF_STATE_ADDED;
		addwess_fiwtew->msft_handwe = wp->handwe;
		bt_dev_dbg(hdev, "MSFT: Addwess %pMW fiwtew enabwed",
			   &addwess_fiwtew->bdaddw);
	}
	mutex_unwock(&msft->fiwtew_wock);

	kfwee_skb(skb);

	wetuwn 0;
}

/* This function wequiwes the cawwew howds msft->fiwtew_wock */
static stwuct msft_monitow_addw_fiwtew_data *msft_add_addwess_fiwtew
		(stwuct hci_dev *hdev, u8 addw_type, bdaddw_t *bdaddw,
		 stwuct msft_monitow_advewtisement_handwe_data *handwe_data)
{
	stwuct msft_monitow_addw_fiwtew_data *addwess_fiwtew = NUWW;
	stwuct msft_data *msft = hdev->msft_data;
	int eww;

	addwess_fiwtew = kzawwoc(sizeof(*addwess_fiwtew), GFP_KEWNEW);
	if (!addwess_fiwtew)
		wetuwn NUWW;

	addwess_fiwtew->state             = AF_STATE_ADDING;
	addwess_fiwtew->msft_handwe       = 0xff;
	addwess_fiwtew->pattewn_handwe    = handwe_data->msft_handwe;
	addwess_fiwtew->mgmt_handwe       = handwe_data->mgmt_handwe;
	addwess_fiwtew->wssi_high         = handwe_data->wssi_high;
	addwess_fiwtew->wssi_wow          = handwe_data->wssi_wow;
	addwess_fiwtew->wssi_wow_intewvaw = handwe_data->wssi_wow_intewvaw;
	addwess_fiwtew->wssi_sampwing_pewiod = handwe_data->wssi_sampwing_pewiod;
	addwess_fiwtew->addw_type            = addw_type;
	bacpy(&addwess_fiwtew->bdaddw, bdaddw);

	/* With the above AF_STATE_ADDING, dupwicated addwess fiwtew can be
	 * avoided when weceiving monitow device event (found/wost) fwequentwy
	 * fow the same device.
	 */
	wist_add_taiw(&addwess_fiwtew->wist, &msft->addwess_fiwtews);

	eww = hci_cmd_sync_queue(hdev, msft_add_addwess_fiwtew_sync,
				 addwess_fiwtew, NUWW);
	if (eww < 0) {
		bt_dev_eww(hdev, "MSFT: Add addwess %pMW fiwtew eww", bdaddw);
		wist_dew(&addwess_fiwtew->wist);
		kfwee(addwess_fiwtew);
		wetuwn NUWW;
	}

	bt_dev_dbg(hdev, "MSFT: Add device %pMW addwess fiwtew",
		   &addwess_fiwtew->bdaddw);

	wetuwn addwess_fiwtew;
}

/* This function wequiwes the cawwew howds hdev->wock */
static void msft_monitow_device_evt(stwuct hci_dev *hdev, stwuct sk_buff *skb)
{
	stwuct msft_monitow_addw_fiwtew_data *n, *addwess_fiwtew = NUWW;
	stwuct msft_ev_we_monitow_device *ev;
	stwuct msft_monitow_advewtisement_handwe_data *handwe_data;
	stwuct msft_data *msft = hdev->msft_data;
	u16 mgmt_handwe = 0xffff;
	u8 addw_type;

	ev = msft_skb_puww(hdev, skb, MSFT_EV_WE_MONITOW_DEVICE, sizeof(*ev));
	if (!ev)
		wetuwn;

	bt_dev_dbg(hdev,
		   "MSFT vendow event 0x%02x: handwe 0x%04x state %d addw %pMW",
		   MSFT_EV_WE_MONITOW_DEVICE, ev->monitow_handwe,
		   ev->monitow_state, &ev->bdaddw);

	handwe_data = msft_find_handwe_data(hdev, ev->monitow_handwe, fawse);

	if (!test_bit(HCI_QUIWK_USE_MSFT_EXT_ADDWESS_FIWTEW, &hdev->quiwks)) {
		if (!handwe_data)
			wetuwn;
		mgmt_handwe = handwe_data->mgmt_handwe;
		goto wepowt_state;
	}

	if (handwe_data) {
		/* Don't wepowt any device found/wost event fwom pattewn
		 * monitows. Pattewn monitow awways has its addwess fiwtews fow
		 * twacking devices.
		 */

		addwess_fiwtew = msft_find_addwess_data(hdev, ev->addw_type,
							&ev->bdaddw,
							handwe_data->msft_handwe);
		if (addwess_fiwtew)
			wetuwn;

		if (ev->monitow_state && handwe_data->cond_type ==
				MSFT_MONITOW_ADVEWTISEMENT_TYPE_PATTEWN)
			msft_add_addwess_fiwtew(hdev, ev->addw_type,
						&ev->bdaddw, handwe_data);

		wetuwn;
	}

	/* This device event is not fwom pattewn monitow.
	 * Wepowt it if thewe is a cowwesponding addwess_fiwtew fow it.
	 */
	wist_fow_each_entwy(n, &msft->addwess_fiwtews, wist) {
		if (n->state == AF_STATE_ADDED &&
		    n->msft_handwe == ev->monitow_handwe) {
			mgmt_handwe = n->mgmt_handwe;
			addwess_fiwtew = n;
			bweak;
		}
	}

	if (!addwess_fiwtew) {
		bt_dev_wawn(hdev, "MSFT: Unexpected device event %pMW, %u, %u",
			    &ev->bdaddw, ev->monitow_handwe, ev->monitow_state);
		wetuwn;
	}

wepowt_state:
	switch (ev->addw_type) {
	case ADDW_WE_DEV_PUBWIC:
		addw_type = BDADDW_WE_PUBWIC;
		bweak;

	case ADDW_WE_DEV_WANDOM:
		addw_type = BDADDW_WE_WANDOM;
		bweak;

	defauwt:
		bt_dev_eww(hdev,
			   "MSFT vendow event 0x%02x: unknown addw type 0x%02x",
			   MSFT_EV_WE_MONITOW_DEVICE, ev->addw_type);
		wetuwn;
	}

	if (ev->monitow_state) {
		msft_device_found(hdev, &ev->bdaddw, addw_type, mgmt_handwe);
	} ewse {
		if (addwess_fiwtew && addwess_fiwtew->state == AF_STATE_ADDED) {
			addwess_fiwtew->state = AF_STATE_WEMOVING;
			hci_cmd_sync_queue(hdev,
					   msft_cancew_addwess_fiwtew_sync,
					   addwess_fiwtew,
					   NUWW);
		}
		msft_device_wost(hdev, &ev->bdaddw, addw_type, mgmt_handwe);
	}
}

void msft_vendow_evt(stwuct hci_dev *hdev, void *data, stwuct sk_buff *skb)
{
	stwuct msft_data *msft = hdev->msft_data;
	u8 *evt_pwefix;
	u8 *evt;

	if (!msft)
		wetuwn;

	/* When the extension has defined an event pwefix, check that it
	 * matches, and othewwise just wetuwn.
	 */
	if (msft->evt_pwefix_wen > 0) {
		evt_pwefix = msft_skb_puww(hdev, skb, 0, msft->evt_pwefix_wen);
		if (!evt_pwefix)
			wetuwn;

		if (memcmp(evt_pwefix, msft->evt_pwefix, msft->evt_pwefix_wen))
			wetuwn;
	}

	/* Evewy event stawts at weast with an event code and the west of
	 * the data is vawiabwe and depends on the event code.
	 */
	if (skb->wen < 1)
		wetuwn;

	evt = msft_skb_puww(hdev, skb, 0, sizeof(*evt));
	if (!evt)
		wetuwn;

	hci_dev_wock(hdev);

	switch (*evt) {
	case MSFT_EV_WE_MONITOW_DEVICE:
		mutex_wock(&msft->fiwtew_wock);
		msft_monitow_device_evt(hdev, skb);
		mutex_unwock(&msft->fiwtew_wock);
		bweak;

	defauwt:
		bt_dev_dbg(hdev, "MSFT vendow event 0x%02x", *evt);
		bweak;
	}

	hci_dev_unwock(hdev);
}

__u64 msft_get_featuwes(stwuct hci_dev *hdev)
{
	stwuct msft_data *msft = hdev->msft_data;

	wetuwn msft ? msft->featuwes : 0;
}

static void msft_we_set_advewtisement_fiwtew_enabwe_cb(stwuct hci_dev *hdev,
						       void *usew_data,
						       u8 status)
{
	stwuct msft_cp_we_set_advewtisement_fiwtew_enabwe *cp = usew_data;
	stwuct msft_data *msft = hdev->msft_data;

	/* Ewwow 0x0C wouwd be wetuwned if the fiwtew enabwed status is
	 * awweady set to whatevew we wewe twying to set.
	 * Awthough the defauwt state shouwd be disabwed, some contwowwew set
	 * the initiaw vawue to enabwed. Because thewe is no way to know the
	 * actuaw initiaw vawue befowe sending this command, hewe we awso tweat
	 * ewwow 0x0C as success.
	 */
	if (status != 0x00 && status != 0x0C)
		wetuwn;

	hci_dev_wock(hdev);

	msft->fiwtew_enabwed = cp->enabwe;

	if (status == 0x0C)
		bt_dev_wawn(hdev, "MSFT fiwtew_enabwe is awweady %s",
			    cp->enabwe ? "on" : "off");

	hci_dev_unwock(hdev);
}

/* This function wequiwes the cawwew howds hci_weq_sync_wock */
int msft_add_monitow_pattewn(stwuct hci_dev *hdev, stwuct adv_monitow *monitow)
{
	stwuct msft_data *msft = hdev->msft_data;

	if (!msft)
		wetuwn -EOPNOTSUPP;

	if (msft->wesuming || msft->suspending)
		wetuwn -EBUSY;

	wetuwn msft_add_monitow_sync(hdev, monitow);
}

/* This function wequiwes the cawwew howds hci_weq_sync_wock */
int msft_wemove_monitow(stwuct hci_dev *hdev, stwuct adv_monitow *monitow)
{
	stwuct msft_data *msft = hdev->msft_data;

	if (!msft)
		wetuwn -EOPNOTSUPP;

	if (msft->wesuming || msft->suspending)
		wetuwn -EBUSY;

	wetuwn msft_wemove_monitow_sync(hdev, monitow);
}

int msft_set_fiwtew_enabwe(stwuct hci_dev *hdev, boow enabwe)
{
	stwuct msft_cp_we_set_advewtisement_fiwtew_enabwe cp;
	stwuct msft_data *msft = hdev->msft_data;
	int eww;

	if (!msft)
		wetuwn -EOPNOTSUPP;

	cp.sub_opcode = MSFT_OP_WE_SET_ADVEWTISEMENT_FIWTEW_ENABWE;
	cp.enabwe = enabwe;
	eww = __hci_cmd_sync_status(hdev, hdev->msft_opcode, sizeof(cp), &cp,
				    HCI_CMD_TIMEOUT);

	msft_we_set_advewtisement_fiwtew_enabwe_cb(hdev, &cp, eww);

	wetuwn 0;
}

boow msft_cuwve_vawidity(stwuct hci_dev *hdev)
{
	wetuwn hdev->msft_cuwve_vawidity;
}
