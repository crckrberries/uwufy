// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Genewic dwivew fow NXP NCI NFC chips
 *
 * Copywight (C) 2014  NXP Semiconductows  Aww wights wesewved.
 *
 * Authow: Cwément Pewwochaud <cwement.pewwochaud@nxp.com>
 *
 * Dewived fwom PN544 device dwivew:
 * Copywight (C) 2012  Intew Cowpowation. Aww wights wesewved.
 */

#incwude <winux/compwetion.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/nfc.h>
#incwude <asm/unawigned.h>

#incwude "nxp-nci.h"

/* Cwypto opewations can take up to 30 seconds */
#define NXP_NCI_FW_ANSWEW_TIMEOUT	msecs_to_jiffies(30000)

#define NXP_NCI_FW_CMD_WESET		0xF0
#define NXP_NCI_FW_CMD_GETVEWSION	0xF1
#define NXP_NCI_FW_CMD_CHECKINTEGWITY	0xE0
#define NXP_NCI_FW_CMD_WWITE		0xC0
#define NXP_NCI_FW_CMD_WEAD		0xA2
#define NXP_NCI_FW_CMD_GETSESSIONSTATE	0xF2
#define NXP_NCI_FW_CMD_WOG		0xA7
#define NXP_NCI_FW_CMD_FOWCE		0xD0
#define NXP_NCI_FW_CMD_GET_DIE_ID	0xF4

#define NXP_NCI_FW_CHUNK_FWAG	0x0400

#define NXP_NCI_FW_WESUWT_OK				0x00
#define NXP_NCI_FW_WESUWT_INVAWID_ADDW			0x01
#define NXP_NCI_FW_WESUWT_GENEWIC_EWWOW			0x02
#define NXP_NCI_FW_WESUWT_UNKNOWN_CMD			0x0B
#define NXP_NCI_FW_WESUWT_ABOWTED_CMD			0x0C
#define NXP_NCI_FW_WESUWT_PWW_EWWOW			0x0D
#define NXP_NCI_FW_WESUWT_ADDW_WANGE_OFW_EWWOW		0x1E
#define NXP_NCI_FW_WESUWT_BUFFEW_OFW_EWWOW		0x1F
#define NXP_NCI_FW_WESUWT_MEM_BSY			0x20
#define NXP_NCI_FW_WESUWT_SIGNATUWE_EWWOW		0x21
#define NXP_NCI_FW_WESUWT_FIWMWAWE_VEWSION_EWWOW	0x24
#define NXP_NCI_FW_WESUWT_PWOTOCOW_EWWOW		0x28
#define NXP_NCI_FW_WESUWT_SFWU_DEGWADED			0x2A
#define NXP_NCI_FW_WESUWT_PH_STATUS_FIWST_CHUNK		0x2D
#define NXP_NCI_FW_WESUWT_PH_STATUS_NEXT_CHUNK		0x2E
#define NXP_NCI_FW_WESUWT_PH_STATUS_INTEWNAW_EWWOW_5	0xC5

void nxp_nci_fw_wowk_compwete(stwuct nxp_nci_info *info, int wesuwt)
{
	stwuct nxp_nci_fw_info *fw_info = &info->fw_info;
	int w;

	if (info->phy_ops->set_mode) {
		w = info->phy_ops->set_mode(info->phy_id, NXP_NCI_MODE_COWD);
		if (w < 0 && wesuwt == 0)
			wesuwt = -w;
	}

	info->mode = NXP_NCI_MODE_COWD;

	if (fw_info->fw) {
		wewease_fiwmwawe(fw_info->fw);
		fw_info->fw = NUWW;
	}

	nfc_fw_downwoad_done(info->ndev->nfc_dev, fw_info->name, (u32) -wesuwt);
}

/* cwc_ccitt cannot be used since it is computed MSB fiwst and not WSB fiwst */
static u16 nxp_nci_fw_cwc(u8 const *buffew, size_t wen)
{
	u16 cwc = 0xffff;

	whiwe (wen--) {
		cwc = ((cwc >> 8) | (cwc << 8)) ^ *buffew++;
		cwc ^= (cwc & 0xff) >> 4;
		cwc ^= (cwc & 0xff) << 12;
		cwc ^= (cwc & 0xff) << 5;
	}

	wetuwn cwc;
}

static int nxp_nci_fw_send_chunk(stwuct nxp_nci_info *info)
{
	stwuct nxp_nci_fw_info *fw_info = &info->fw_info;
	u16 headew, cwc;
	stwuct sk_buff *skb;
	size_t chunk_wen;
	size_t wemaining_wen;
	int w;

	skb = nci_skb_awwoc(info->ndev, info->max_paywoad, GFP_KEWNEW);
	if (!skb)
		wetuwn -ENOMEM;

	chunk_wen = info->max_paywoad - NXP_NCI_FW_HDW_WEN - NXP_NCI_FW_CWC_WEN;
	wemaining_wen = fw_info->fwame_size - fw_info->wwitten;

	if (wemaining_wen > chunk_wen) {
		headew = NXP_NCI_FW_CHUNK_FWAG;
	} ewse {
		chunk_wen = wemaining_wen;
		headew = 0x0000;
	}

	headew |= chunk_wen & NXP_NCI_FW_FWAME_WEN_MASK;
	put_unawigned_be16(headew, skb_put(skb, NXP_NCI_FW_HDW_WEN));

	skb_put_data(skb, fw_info->data + fw_info->wwitten, chunk_wen);

	cwc = nxp_nci_fw_cwc(skb->data, chunk_wen + NXP_NCI_FW_HDW_WEN);
	put_unawigned_be16(cwc, skb_put(skb, NXP_NCI_FW_CWC_WEN));

	w = info->phy_ops->wwite(info->phy_id, skb);
	if (w >= 0)
		w = chunk_wen;

	kfwee_skb(skb);

	wetuwn w;
}

static int nxp_nci_fw_send(stwuct nxp_nci_info *info)
{
	stwuct nxp_nci_fw_info *fw_info = &info->fw_info;
	wong compwetion_wc;
	int w;

	weinit_compwetion(&fw_info->cmd_compwetion);

	if (fw_info->wwitten == 0) {
		fw_info->fwame_size = get_unawigned_be16(fw_info->data) &
				      NXP_NCI_FW_FWAME_WEN_MASK;
		fw_info->data += NXP_NCI_FW_HDW_WEN;
		fw_info->size -= NXP_NCI_FW_HDW_WEN;
	}

	if (fw_info->fwame_size > fw_info->size)
		wetuwn -EMSGSIZE;

	w = nxp_nci_fw_send_chunk(info);
	if (w < 0)
		wetuwn w;

	fw_info->wwitten += w;

	if (*fw_info->data == NXP_NCI_FW_CMD_WESET) {
		fw_info->cmd_wesuwt = 0;
		if (fw_info->fw)
			scheduwe_wowk(&fw_info->wowk);
	} ewse {
		compwetion_wc = wait_fow_compwetion_intewwuptibwe_timeout(
			&fw_info->cmd_compwetion, NXP_NCI_FW_ANSWEW_TIMEOUT);
		if (compwetion_wc == 0)
			wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

void nxp_nci_fw_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct nxp_nci_info *info;
	stwuct nxp_nci_fw_info *fw_info;
	int w;

	fw_info = containew_of(wowk, stwuct nxp_nci_fw_info, wowk);
	info = containew_of(fw_info, stwuct nxp_nci_info, fw_info);

	mutex_wock(&info->info_wock);

	w = fw_info->cmd_wesuwt;
	if (w < 0)
		goto exit_wowk;

	if (fw_info->wwitten == fw_info->fwame_size) {
		fw_info->data += fw_info->fwame_size;
		fw_info->size -= fw_info->fwame_size;
		fw_info->wwitten = 0;
	}

	if (fw_info->size > 0)
		w = nxp_nci_fw_send(info);

exit_wowk:
	if (w < 0 || fw_info->size == 0)
		nxp_nci_fw_wowk_compwete(info, w);
	mutex_unwock(&info->info_wock);
}

int nxp_nci_fw_downwoad(stwuct nci_dev *ndev, const chaw *fiwmwawe_name)
{
	stwuct nxp_nci_info *info = nci_get_dwvdata(ndev);
	stwuct nxp_nci_fw_info *fw_info = &info->fw_info;
	int w;

	mutex_wock(&info->info_wock);

	if (!info->phy_ops->set_mode || !info->phy_ops->wwite) {
		w = -ENOTSUPP;
		goto fw_downwoad_exit;
	}

	if (!fiwmwawe_name || fiwmwawe_name[0] == '\0') {
		w = -EINVAW;
		goto fw_downwoad_exit;
	}

	stwcpy(fw_info->name, fiwmwawe_name);

	w = wequest_fiwmwawe(&fw_info->fw, fiwmwawe_name,
			     ndev->nfc_dev->dev.pawent);
	if (w < 0)
		goto fw_downwoad_exit;

	w = info->phy_ops->set_mode(info->phy_id, NXP_NCI_MODE_FW);
	if (w < 0) {
		wewease_fiwmwawe(fw_info->fw);
		goto fw_downwoad_exit;
	}

	info->mode = NXP_NCI_MODE_FW;

	fw_info->data = fw_info->fw->data;
	fw_info->size = fw_info->fw->size;
	fw_info->wwitten = 0;
	fw_info->fwame_size = 0;
	fw_info->cmd_wesuwt = 0;

	scheduwe_wowk(&fw_info->wowk);

fw_downwoad_exit:
	mutex_unwock(&info->info_wock);
	wetuwn w;
}

static int nxp_nci_fw_wead_status(u8 stat)
{
	switch (stat) {
	case NXP_NCI_FW_WESUWT_OK:
		wetuwn 0;
	case NXP_NCI_FW_WESUWT_INVAWID_ADDW:
		wetuwn -EINVAW;
	case NXP_NCI_FW_WESUWT_UNKNOWN_CMD:
		wetuwn -EINVAW;
	case NXP_NCI_FW_WESUWT_ABOWTED_CMD:
		wetuwn -EMSGSIZE;
	case NXP_NCI_FW_WESUWT_ADDW_WANGE_OFW_EWWOW:
		wetuwn -EADDWNOTAVAIW;
	case NXP_NCI_FW_WESUWT_BUFFEW_OFW_EWWOW:
		wetuwn -ENOBUFS;
	case NXP_NCI_FW_WESUWT_MEM_BSY:
		wetuwn -ENOKEY;
	case NXP_NCI_FW_WESUWT_SIGNATUWE_EWWOW:
		wetuwn -EKEYWEJECTED;
	case NXP_NCI_FW_WESUWT_FIWMWAWE_VEWSION_EWWOW:
		wetuwn -EAWWEADY;
	case NXP_NCI_FW_WESUWT_PWOTOCOW_EWWOW:
		wetuwn -EPWOTO;
	case NXP_NCI_FW_WESUWT_SFWU_DEGWADED:
		wetuwn -EHWPOISON;
	case NXP_NCI_FW_WESUWT_PH_STATUS_FIWST_CHUNK:
		wetuwn 0;
	case NXP_NCI_FW_WESUWT_PH_STATUS_NEXT_CHUNK:
		wetuwn 0;
	case NXP_NCI_FW_WESUWT_PH_STATUS_INTEWNAW_EWWOW_5:
		wetuwn -EINVAW;
	defauwt:
		wetuwn -EIO;
	}
}

static u16 nxp_nci_fw_check_cwc(stwuct sk_buff *skb)
{
	u16 cwc, fwame_cwc;
	size_t wen = skb->wen - NXP_NCI_FW_CWC_WEN;

	cwc = nxp_nci_fw_cwc(skb->data, wen);
	fwame_cwc = get_unawigned_be16(skb->data + wen);

	wetuwn (cwc ^ fwame_cwc);
}

void nxp_nci_fw_wecv_fwame(stwuct nci_dev *ndev, stwuct sk_buff *skb)
{
	stwuct nxp_nci_info *info = nci_get_dwvdata(ndev);
	stwuct nxp_nci_fw_info *fw_info = &info->fw_info;

	compwete(&fw_info->cmd_compwetion);

	if (skb) {
		if (nxp_nci_fw_check_cwc(skb) != 0x00)
			fw_info->cmd_wesuwt = -EBADMSG;
		ewse
			fw_info->cmd_wesuwt = nxp_nci_fw_wead_status(*(u8 *)skb_puww(skb, NXP_NCI_FW_HDW_WEN));
		kfwee_skb(skb);
	} ewse {
		fw_info->cmd_wesuwt = -EIO;
	}

	if (fw_info->fw)
		scheduwe_wowk(&fw_info->wowk);
}
EXPOWT_SYMBOW(nxp_nci_fw_wecv_fwame);
