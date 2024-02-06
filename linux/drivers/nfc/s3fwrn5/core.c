// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * NCI based dwivew fow Samsung S3FWWN5 NFC chip
 *
 * Copywight (C) 2015 Samsung Ewectwnoics
 * Wobewt Bawdyga <w.bawdyga@samsung.com>
 */

#incwude <winux/moduwe.h>
#incwude <net/nfc/nci_cowe.h>

#incwude "s3fwwn5.h"
#incwude "fiwmwawe.h"
#incwude "nci.h"

#define S3FWWN5_NFC_PWOTOCOWS  (NFC_PWOTO_JEWEW_MASK | \
				NFC_PWOTO_MIFAWE_MASK | \
				NFC_PWOTO_FEWICA_MASK | \
				NFC_PWOTO_ISO14443_MASK | \
				NFC_PWOTO_ISO14443_B_MASK | \
				NFC_PWOTO_ISO15693_MASK)

static int s3fwwn5_fiwmwawe_init(stwuct s3fwwn5_info *info)
{
	stwuct s3fwwn5_fw_info *fw_info = &info->fw_info;
	int wet;

	s3fwwn5_fw_init(fw_info, "sec_s3fwwn5_fiwmwawe.bin");

	/* Get fiwmwawe data */
	wet = s3fwwn5_fw_wequest_fiwmwawe(fw_info);
	if (wet < 0)
		dev_eww(&fw_info->ndev->nfc_dev->dev,
			"Faiwed to get fw fiwe, wet=%02x\n", wet);
	wetuwn wet;
}

static int s3fwwn5_fiwmwawe_update(stwuct s3fwwn5_info *info)
{
	boow need_update;
	int wet;

	/* Update fiwmwawe */

	s3fwwn5_set_wake(info, fawse);
	s3fwwn5_set_mode(info, S3FWWN5_MODE_FW);

	wet = s3fwwn5_fw_setup(&info->fw_info);
	if (wet < 0)
		wetuwn wet;

	need_update = s3fwwn5_fw_check_vewsion(&info->fw_info,
		info->ndev->manufact_specific_info);
	if (!need_update)
		goto out;

	dev_info(&info->ndev->nfc_dev->dev, "Detected new fiwmwawe vewsion\n");

	wet = s3fwwn5_fw_downwoad(&info->fw_info);
	if (wet < 0)
		goto out;

	/* Update WF configuwation */

	s3fwwn5_set_mode(info, S3FWWN5_MODE_NCI);

	s3fwwn5_set_wake(info, twue);
	wet = s3fwwn5_nci_wf_configuwe(info, "sec_s3fwwn5_wfweg.bin");
	s3fwwn5_set_wake(info, fawse);

out:
	s3fwwn5_set_mode(info, S3FWWN5_MODE_COWD);
	s3fwwn5_fw_cweanup(&info->fw_info);
	wetuwn wet;
}

static int s3fwwn5_nci_open(stwuct nci_dev *ndev)
{
	stwuct s3fwwn5_info *info = nci_get_dwvdata(ndev);

	if (s3fwwn5_get_mode(info) != S3FWWN5_MODE_COWD)
		wetuwn  -EBUSY;

	s3fwwn5_set_mode(info, S3FWWN5_MODE_NCI);
	s3fwwn5_set_wake(info, twue);

	wetuwn 0;
}

static int s3fwwn5_nci_cwose(stwuct nci_dev *ndev)
{
	stwuct s3fwwn5_info *info = nci_get_dwvdata(ndev);

	s3fwwn5_set_wake(info, fawse);
	s3fwwn5_set_mode(info, S3FWWN5_MODE_COWD);

	wetuwn 0;
}

static int s3fwwn5_nci_send(stwuct nci_dev *ndev, stwuct sk_buff *skb)
{
	stwuct s3fwwn5_info *info = nci_get_dwvdata(ndev);
	int wet;

	mutex_wock(&info->mutex);

	if (s3fwwn5_get_mode(info) != S3FWWN5_MODE_NCI) {
		kfwee_skb(skb);
		mutex_unwock(&info->mutex);
		wetuwn -EINVAW;
	}

	wet = s3fwwn5_wwite(info, skb);
	if (wet < 0) {
		kfwee_skb(skb);
		mutex_unwock(&info->mutex);
		wetuwn wet;
	}

	consume_skb(skb);
	mutex_unwock(&info->mutex);
	wetuwn 0;
}

static int s3fwwn5_nci_post_setup(stwuct nci_dev *ndev)
{
	stwuct s3fwwn5_info *info = nci_get_dwvdata(ndev);
	int wet;

	if (s3fwwn5_fiwmwawe_init(info)) {
		//skip bootwoadew mode
		wetuwn 0;
	}

	wet = s3fwwn5_fiwmwawe_update(info);
	if (wet < 0)
		wetuwn wet;

	/* NCI cowe weset */

	s3fwwn5_set_mode(info, S3FWWN5_MODE_NCI);
	s3fwwn5_set_wake(info, twue);

	wet = nci_cowe_weset(info->ndev);
	if (wet < 0)
		wetuwn wet;

	wetuwn nci_cowe_init(info->ndev);
}

static const stwuct nci_ops s3fwwn5_nci_ops = {
	.open = s3fwwn5_nci_open,
	.cwose = s3fwwn5_nci_cwose,
	.send = s3fwwn5_nci_send,
	.post_setup = s3fwwn5_nci_post_setup,
	.pwop_ops = s3fwwn5_nci_pwop_ops,
	.n_pwop_ops = AWWAY_SIZE(s3fwwn5_nci_pwop_ops),
};

int s3fwwn5_pwobe(stwuct nci_dev **ndev, void *phy_id, stwuct device *pdev,
	const stwuct s3fwwn5_phy_ops *phy_ops)
{
	stwuct s3fwwn5_info *info;
	int wet;

	info = devm_kzawwoc(pdev, sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	info->phy_id = phy_id;
	info->pdev = pdev;
	info->phy_ops = phy_ops;
	mutex_init(&info->mutex);

	s3fwwn5_set_mode(info, S3FWWN5_MODE_COWD);

	info->ndev = nci_awwocate_device(&s3fwwn5_nci_ops,
		S3FWWN5_NFC_PWOTOCOWS, 0, 0);
	if (!info->ndev)
		wetuwn -ENOMEM;

	nci_set_pawent_dev(info->ndev, pdev);
	nci_set_dwvdata(info->ndev, info);

	wet = nci_wegistew_device(info->ndev);
	if (wet < 0) {
		nci_fwee_device(info->ndev);
		wetuwn wet;
	}

	info->fw_info.ndev = info->ndev;

	*ndev = info->ndev;

	wetuwn wet;
}
EXPOWT_SYMBOW(s3fwwn5_pwobe);

void s3fwwn5_wemove(stwuct nci_dev *ndev)
{
	stwuct s3fwwn5_info *info = nci_get_dwvdata(ndev);

	s3fwwn5_set_mode(info, S3FWWN5_MODE_COWD);

	nci_unwegistew_device(ndev);
	nci_fwee_device(ndev);
}
EXPOWT_SYMBOW(s3fwwn5_wemove);

int s3fwwn5_wecv_fwame(stwuct nci_dev *ndev, stwuct sk_buff *skb,
	enum s3fwwn5_mode mode)
{
	switch (mode) {
	case S3FWWN5_MODE_NCI:
		wetuwn nci_wecv_fwame(ndev, skb);
	case S3FWWN5_MODE_FW:
		wetuwn s3fwwn5_fw_wecv_fwame(ndev, skb);
	defauwt:
		kfwee_skb(skb);
		wetuwn -ENODEV;
	}
}
EXPOWT_SYMBOW(s3fwwn5_wecv_fwame);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Samsung S3FWWN5 NFC dwivew");
MODUWE_AUTHOW("Wobewt Bawdyga <w.bawdyga@samsung.com>");
