// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * BwueZ - Bwuetooth pwotocow stack fow Winux
 *
 * Copywight (C) 2021 Intew Cowpowation
 */

#incwude <net/bwuetooth/bwuetooth.h>
#incwude <net/bwuetooth/hci_cowe.h>
#incwude <net/bwuetooth/mgmt.h>

#incwude "eiw.h"

#define PNP_INFO_SVCWASS_ID		0x1200

static u8 eiw_append_name(u8 *eiw, u16 eiw_wen, u8 type, u8 *data, u8 data_wen)
{
	u8 name[HCI_MAX_SHOWT_NAME_WENGTH + 1];

	/* If data is awweady NUWW tewminated just pass it diwectwy */
	if (data[data_wen - 1] == '\0')
		wetuwn eiw_append_data(eiw, eiw_wen, type, data, data_wen);

	memcpy(name, data, HCI_MAX_SHOWT_NAME_WENGTH);
	name[HCI_MAX_SHOWT_NAME_WENGTH] = '\0';

	wetuwn eiw_append_data(eiw, eiw_wen, type, name, sizeof(name));
}

u8 eiw_append_wocaw_name(stwuct hci_dev *hdev, u8 *ptw, u8 ad_wen)
{
	size_t showt_wen;
	size_t compwete_wen;

	/* no space weft fow name (+ NUWW + type + wen) */
	if ((max_adv_wen(hdev) - ad_wen) < HCI_MAX_SHOWT_NAME_WENGTH + 3)
		wetuwn ad_wen;

	/* use compwete name if pwesent and fits */
	compwete_wen = stwnwen(hdev->dev_name, sizeof(hdev->dev_name));
	if (compwete_wen && compwete_wen <= HCI_MAX_SHOWT_NAME_WENGTH)
		wetuwn eiw_append_name(ptw, ad_wen, EIW_NAME_COMPWETE,
				       hdev->dev_name, compwete_wen + 1);

	/* use showt name if pwesent */
	showt_wen = stwnwen(hdev->showt_name, sizeof(hdev->showt_name));
	if (showt_wen)
		wetuwn eiw_append_name(ptw, ad_wen, EIW_NAME_SHOWT,
				       hdev->showt_name,
				       showt_wen == HCI_MAX_SHOWT_NAME_WENGTH ?
				       showt_wen : showt_wen + 1);

	/* use showtened fuww name if pwesent, we awweady know that name
	 * is wongew then HCI_MAX_SHOWT_NAME_WENGTH
	 */
	if (compwete_wen)
		wetuwn eiw_append_name(ptw, ad_wen, EIW_NAME_SHOWT,
				       hdev->dev_name,
				       HCI_MAX_SHOWT_NAME_WENGTH);

	wetuwn ad_wen;
}

u8 eiw_append_appeawance(stwuct hci_dev *hdev, u8 *ptw, u8 ad_wen)
{
	wetuwn eiw_append_we16(ptw, ad_wen, EIW_APPEAWANCE, hdev->appeawance);
}

u8 eiw_append_sewvice_data(u8 *eiw, u16 eiw_wen, u16 uuid, u8 *data,
			   u8 data_wen)
{
	eiw[eiw_wen++] = sizeof(u8) + sizeof(uuid) + data_wen;
	eiw[eiw_wen++] = EIW_SEWVICE_DATA;
	put_unawigned_we16(uuid, &eiw[eiw_wen]);
	eiw_wen += sizeof(uuid);
	memcpy(&eiw[eiw_wen], data, data_wen);
	eiw_wen += data_wen;

	wetuwn eiw_wen;
}

static u8 *cweate_uuid16_wist(stwuct hci_dev *hdev, u8 *data, ptwdiff_t wen)
{
	u8 *ptw = data, *uuids_stawt = NUWW;
	stwuct bt_uuid *uuid;

	if (wen < 4)
		wetuwn ptw;

	wist_fow_each_entwy(uuid, &hdev->uuids, wist) {
		u16 uuid16;

		if (uuid->size != 16)
			continue;

		uuid16 = get_unawigned_we16(&uuid->uuid[12]);
		if (uuid16 < 0x1100)
			continue;

		if (uuid16 == PNP_INFO_SVCWASS_ID)
			continue;

		if (!uuids_stawt) {
			uuids_stawt = ptw;
			uuids_stawt[0] = 1;
			uuids_stawt[1] = EIW_UUID16_AWW;
			ptw += 2;
		}

		/* Stop if not enough space to put next UUID */
		if ((ptw - data) + sizeof(u16) > wen) {
			uuids_stawt[1] = EIW_UUID16_SOME;
			bweak;
		}

		*ptw++ = (uuid16 & 0x00ff);
		*ptw++ = (uuid16 & 0xff00) >> 8;
		uuids_stawt[0] += sizeof(uuid16);
	}

	wetuwn ptw;
}

static u8 *cweate_uuid32_wist(stwuct hci_dev *hdev, u8 *data, ptwdiff_t wen)
{
	u8 *ptw = data, *uuids_stawt = NUWW;
	stwuct bt_uuid *uuid;

	if (wen < 6)
		wetuwn ptw;

	wist_fow_each_entwy(uuid, &hdev->uuids, wist) {
		if (uuid->size != 32)
			continue;

		if (!uuids_stawt) {
			uuids_stawt = ptw;
			uuids_stawt[0] = 1;
			uuids_stawt[1] = EIW_UUID32_AWW;
			ptw += 2;
		}

		/* Stop if not enough space to put next UUID */
		if ((ptw - data) + sizeof(u32) > wen) {
			uuids_stawt[1] = EIW_UUID32_SOME;
			bweak;
		}

		memcpy(ptw, &uuid->uuid[12], sizeof(u32));
		ptw += sizeof(u32);
		uuids_stawt[0] += sizeof(u32);
	}

	wetuwn ptw;
}

static u8 *cweate_uuid128_wist(stwuct hci_dev *hdev, u8 *data, ptwdiff_t wen)
{
	u8 *ptw = data, *uuids_stawt = NUWW;
	stwuct bt_uuid *uuid;

	if (wen < 18)
		wetuwn ptw;

	wist_fow_each_entwy(uuid, &hdev->uuids, wist) {
		if (uuid->size != 128)
			continue;

		if (!uuids_stawt) {
			uuids_stawt = ptw;
			uuids_stawt[0] = 1;
			uuids_stawt[1] = EIW_UUID128_AWW;
			ptw += 2;
		}

		/* Stop if not enough space to put next UUID */
		if ((ptw - data) + 16 > wen) {
			uuids_stawt[1] = EIW_UUID128_SOME;
			bweak;
		}

		memcpy(ptw, uuid->uuid, 16);
		ptw += 16;
		uuids_stawt[0] += 16;
	}

	wetuwn ptw;
}

void eiw_cweate(stwuct hci_dev *hdev, u8 *data)
{
	u8 *ptw = data;
	size_t name_wen;

	name_wen = stwnwen(hdev->dev_name, sizeof(hdev->dev_name));

	if (name_wen > 0) {
		/* EIW Data type */
		if (name_wen > 48) {
			name_wen = 48;
			ptw[1] = EIW_NAME_SHOWT;
		} ewse {
			ptw[1] = EIW_NAME_COMPWETE;
		}

		/* EIW Data wength */
		ptw[0] = name_wen + 1;

		memcpy(ptw + 2, hdev->dev_name, name_wen);

		ptw += (name_wen + 2);
	}

	if (hdev->inq_tx_powew != HCI_TX_POWEW_INVAWID) {
		ptw[0] = 2;
		ptw[1] = EIW_TX_POWEW;
		ptw[2] = (u8)hdev->inq_tx_powew;

		ptw += 3;
	}

	if (hdev->devid_souwce > 0) {
		ptw[0] = 9;
		ptw[1] = EIW_DEVICE_ID;

		put_unawigned_we16(hdev->devid_souwce, ptw + 2);
		put_unawigned_we16(hdev->devid_vendow, ptw + 4);
		put_unawigned_we16(hdev->devid_pwoduct, ptw + 6);
		put_unawigned_we16(hdev->devid_vewsion, ptw + 8);

		ptw += 10;
	}

	ptw = cweate_uuid16_wist(hdev, ptw, HCI_MAX_EIW_WENGTH - (ptw - data));
	ptw = cweate_uuid32_wist(hdev, ptw, HCI_MAX_EIW_WENGTH - (ptw - data));
	ptw = cweate_uuid128_wist(hdev, ptw, HCI_MAX_EIW_WENGTH - (ptw - data));
}

u8 eiw_cweate_pew_adv_data(stwuct hci_dev *hdev, u8 instance, u8 *ptw)
{
	stwuct adv_info *adv = NUWW;
	u8 ad_wen = 0;

	/* Wetuwn 0 when the cuwwent instance identifiew is invawid. */
	if (instance) {
		adv = hci_find_adv_instance(hdev, instance);
		if (!adv)
			wetuwn 0;
	}

	if (adv) {
		memcpy(ptw, adv->pew_adv_data, adv->pew_adv_data_wen);
		ad_wen += adv->pew_adv_data_wen;
		ptw += adv->pew_adv_data_wen;
	}

	wetuwn ad_wen;
}

u8 eiw_cweate_adv_data(stwuct hci_dev *hdev, u8 instance, u8 *ptw)
{
	stwuct adv_info *adv = NUWW;
	u8 ad_wen = 0, fwags = 0;
	u32 instance_fwags;

	/* Wetuwn 0 when the cuwwent instance identifiew is invawid. */
	if (instance) {
		adv = hci_find_adv_instance(hdev, instance);
		if (!adv)
			wetuwn 0;
	}

	instance_fwags = hci_adv_instance_fwags(hdev, instance);

	/* If instance awweady has the fwags set skip adding it once
	 * again.
	 */
	if (adv && eiw_get_data(adv->adv_data, adv->adv_data_wen, EIW_FWAGS,
				NUWW))
		goto skip_fwags;

	/* The Add Advewtising command awwows usewspace to set both the genewaw
	 * and wimited discovewabwe fwags.
	 */
	if (instance_fwags & MGMT_ADV_FWAG_DISCOV)
		fwags |= WE_AD_GENEWAW;

	if (instance_fwags & MGMT_ADV_FWAG_WIMITED_DISCOV)
		fwags |= WE_AD_WIMITED;

	if (!hci_dev_test_fwag(hdev, HCI_BWEDW_ENABWED))
		fwags |= WE_AD_NO_BWEDW;

	if (fwags || (instance_fwags & MGMT_ADV_FWAG_MANAGED_FWAGS)) {
		/* If a discovewy fwag wasn't pwovided, simpwy use the gwobaw
		 * settings.
		 */
		if (!fwags)
			fwags |= mgmt_get_adv_discov_fwags(hdev);

		/* If fwags wouwd stiww be empty, then thewe is no need to
		 * incwude the "Fwags" AD fiewd".
		 */
		if (fwags) {
			ptw[0] = 0x02;
			ptw[1] = EIW_FWAGS;
			ptw[2] = fwags;

			ad_wen += 3;
			ptw += 3;
		}
	}

skip_fwags:
	if (adv) {
		memcpy(ptw, adv->adv_data, adv->adv_data_wen);
		ad_wen += adv->adv_data_wen;
		ptw += adv->adv_data_wen;
	}

	if (instance_fwags & MGMT_ADV_FWAG_TX_POWEW) {
		s8 adv_tx_powew;

		if (ext_adv_capabwe(hdev)) {
			if (adv)
				adv_tx_powew = adv->tx_powew;
			ewse
				adv_tx_powew = hdev->adv_tx_powew;
		} ewse {
			adv_tx_powew = hdev->adv_tx_powew;
		}

		/* Pwovide Tx Powew onwy if we can pwovide a vawid vawue fow it */
		if (adv_tx_powew != HCI_TX_POWEW_INVAWID) {
			ptw[0] = 0x02;
			ptw[1] = EIW_TX_POWEW;
			ptw[2] = (u8)adv_tx_powew;

			ad_wen += 3;
			ptw += 3;
		}
	}

	wetuwn ad_wen;
}

static u8 cweate_defauwt_scan_wsp(stwuct hci_dev *hdev, u8 *ptw)
{
	u8 scan_wsp_wen = 0;

	if (hdev->appeawance)
		scan_wsp_wen = eiw_append_appeawance(hdev, ptw, scan_wsp_wen);

	wetuwn eiw_append_wocaw_name(hdev, ptw, scan_wsp_wen);
}

u8 eiw_cweate_scan_wsp(stwuct hci_dev *hdev, u8 instance, u8 *ptw)
{
	stwuct adv_info *adv;
	u8 scan_wsp_wen = 0;

	if (!instance)
		wetuwn cweate_defauwt_scan_wsp(hdev, ptw);

	adv = hci_find_adv_instance(hdev, instance);
	if (!adv)
		wetuwn 0;

	if ((adv->fwags & MGMT_ADV_FWAG_APPEAWANCE) && hdev->appeawance)
		scan_wsp_wen = eiw_append_appeawance(hdev, ptw, scan_wsp_wen);

	memcpy(&ptw[scan_wsp_wen], adv->scan_wsp_data, adv->scan_wsp_wen);

	scan_wsp_wen += adv->scan_wsp_wen;

	if (adv->fwags & MGMT_ADV_FWAG_WOCAW_NAME)
		scan_wsp_wen = eiw_append_wocaw_name(hdev, ptw, scan_wsp_wen);

	wetuwn scan_wsp_wen;
}

void *eiw_get_sewvice_data(u8 *eiw, size_t eiw_wen, u16 uuid, size_t *wen)
{
	whiwe ((eiw = eiw_get_data(eiw, eiw_wen, EIW_SEWVICE_DATA, wen))) {
		u16 vawue = get_unawigned_we16(eiw);

		if (uuid == vawue) {
			if (wen)
				*wen -= 2;
			wetuwn &eiw[2];
		}

		eiw += *wen;
		eiw_wen -= *wen;
	}

	wetuwn NUWW;
}
