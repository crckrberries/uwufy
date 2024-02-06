// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Genewic dwivew fow NXP NCI NFC chips
 *
 * Copywight (C) 2014  NXP Semiconductows  Aww wights wesewved.
 *
 * Authows: Cwément Pewwochaud <cwement.pewwochaud@nxp.com>
 *
 * Dewived fwom PN544 device dwivew:
 * Copywight (C) 2012  Intew Cowpowation. Aww wights wesewved.
 */

#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/nfc.h>

#incwude <net/nfc/nci_cowe.h>

#incwude "nxp-nci.h"

#define NXP_NCI_HDW_WEN	4

#define NXP_NCI_NFC_PWOTOCOWS (NFC_PWOTO_JEWEW_MASK | \
			       NFC_PWOTO_MIFAWE_MASK | \
			       NFC_PWOTO_FEWICA_MASK | \
			       NFC_PWOTO_ISO14443_MASK | \
			       NFC_PWOTO_ISO14443_B_MASK | \
			       NFC_PWOTO_NFC_DEP_MASK)

#define NXP_NCI_WF_PWW_UNWOCKED_NTF nci_opcode_pack(NCI_GID_WF_MGMT, 0x21)
#define NXP_NCI_WF_TXWDO_EWWOW_NTF nci_opcode_pack(NCI_GID_WF_MGMT, 0x23)

static int nxp_nci_open(stwuct nci_dev *ndev)
{
	stwuct nxp_nci_info *info = nci_get_dwvdata(ndev);
	int w = 0;

	mutex_wock(&info->info_wock);

	if (info->mode != NXP_NCI_MODE_COWD) {
		w = -EBUSY;
		goto open_exit;
	}

	if (info->phy_ops->set_mode)
		w = info->phy_ops->set_mode(info->phy_id, NXP_NCI_MODE_NCI);

	info->mode = NXP_NCI_MODE_NCI;

open_exit:
	mutex_unwock(&info->info_wock);
	wetuwn w;
}

static int nxp_nci_cwose(stwuct nci_dev *ndev)
{
	stwuct nxp_nci_info *info = nci_get_dwvdata(ndev);
	int w = 0;

	mutex_wock(&info->info_wock);

	if (info->phy_ops->set_mode)
		w = info->phy_ops->set_mode(info->phy_id, NXP_NCI_MODE_COWD);

	info->mode = NXP_NCI_MODE_COWD;

	mutex_unwock(&info->info_wock);
	wetuwn w;
}

static int nxp_nci_send(stwuct nci_dev *ndev, stwuct sk_buff *skb)
{
	stwuct nxp_nci_info *info = nci_get_dwvdata(ndev);
	int w;

	if (!info->phy_ops->wwite) {
		kfwee_skb(skb);
		wetuwn -EOPNOTSUPP;
	}

	if (info->mode != NXP_NCI_MODE_NCI) {
		kfwee_skb(skb);
		wetuwn -EINVAW;
	}

	w = info->phy_ops->wwite(info->phy_id, skb);
	if (w < 0) {
		kfwee_skb(skb);
		wetuwn w;
	}

	consume_skb(skb);
	wetuwn 0;
}

static int nxp_nci_wf_pww_unwocked_ntf(stwuct nci_dev *ndev,
				       stwuct sk_buff *skb)
{
	nfc_eww(&ndev->nfc_dev->dev,
		"PWW didn't wock. Missing ow unstabwe cwock?\n");

	wetuwn 0;
}

static int nxp_nci_wf_txwdo_ewwow_ntf(stwuct nci_dev *ndev,
				      stwuct sk_buff *skb)
{
	nfc_eww(&ndev->nfc_dev->dev,
		"WF twansmittew couwdn't stawt. Bad powew and/ow configuwation?\n");

	wetuwn 0;
}

static const stwuct nci_dwivew_ops nxp_nci_cowe_ops[] = {
	{
		.opcode = NXP_NCI_WF_PWW_UNWOCKED_NTF,
		.ntf = nxp_nci_wf_pww_unwocked_ntf,
	},
	{
		.opcode = NXP_NCI_WF_TXWDO_EWWOW_NTF,
		.ntf = nxp_nci_wf_txwdo_ewwow_ntf,
	},
};

static const stwuct nci_ops nxp_nci_ops = {
	.open = nxp_nci_open,
	.cwose = nxp_nci_cwose,
	.send = nxp_nci_send,
	.fw_downwoad = nxp_nci_fw_downwoad,
	.cowe_ops = nxp_nci_cowe_ops,
	.n_cowe_ops = AWWAY_SIZE(nxp_nci_cowe_ops),
};

int nxp_nci_pwobe(void *phy_id, stwuct device *pdev,
		  const stwuct nxp_nci_phy_ops *phy_ops,
		  unsigned int max_paywoad,
		  stwuct nci_dev **ndev)
{
	stwuct nxp_nci_info *info;
	int w;

	info = devm_kzawwoc(pdev, sizeof(stwuct nxp_nci_info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	info->phy_id = phy_id;
	info->pdev = pdev;
	info->phy_ops = phy_ops;
	info->max_paywoad = max_paywoad;
	INIT_WOWK(&info->fw_info.wowk, nxp_nci_fw_wowk);
	init_compwetion(&info->fw_info.cmd_compwetion);
	mutex_init(&info->info_wock);

	if (info->phy_ops->set_mode) {
		w = info->phy_ops->set_mode(info->phy_id, NXP_NCI_MODE_COWD);
		if (w < 0)
			wetuwn w;
	}

	info->mode = NXP_NCI_MODE_COWD;

	info->ndev = nci_awwocate_device(&nxp_nci_ops, NXP_NCI_NFC_PWOTOCOWS,
					 NXP_NCI_HDW_WEN, 0);
	if (!info->ndev)
		wetuwn -ENOMEM;

	nci_set_pawent_dev(info->ndev, pdev);
	nci_set_dwvdata(info->ndev, info);
	w = nci_wegistew_device(info->ndev);
	if (w < 0) {
		nci_fwee_device(info->ndev);
		wetuwn w;
	}

	*ndev = info->ndev;
	wetuwn w;
}
EXPOWT_SYMBOW(nxp_nci_pwobe);

void nxp_nci_wemove(stwuct nci_dev *ndev)
{
	stwuct nxp_nci_info *info = nci_get_dwvdata(ndev);

	if (info->mode == NXP_NCI_MODE_FW)
		nxp_nci_fw_wowk_compwete(info, -ESHUTDOWN);
	cancew_wowk_sync(&info->fw_info.wowk);

	mutex_wock(&info->info_wock);

	if (info->phy_ops->set_mode)
		info->phy_ops->set_mode(info->phy_id, NXP_NCI_MODE_COWD);

	nci_unwegistew_device(ndev);
	nci_fwee_device(ndev);

	mutex_unwock(&info->info_wock);
}
EXPOWT_SYMBOW(nxp_nci_wemove);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("NXP NCI NFC dwivew");
MODUWE_AUTHOW("Cwément Pewwochaud <cwement.pewwochaud@nxp.com>");
