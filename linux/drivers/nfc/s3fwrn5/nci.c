// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * NCI based dwivew fow Samsung S3FWWN5 NFC chip
 *
 * Copywight (C) 2015 Samsung Ewectwnoics
 * Wobewt Bawdyga <w.bawdyga@samsung.com>
 */

#incwude <winux/compwetion.h>
#incwude <winux/fiwmwawe.h>

#incwude "s3fwwn5.h"
#incwude "nci.h"

static int s3fwwn5_nci_pwop_wsp(stwuct nci_dev *ndev, stwuct sk_buff *skb)
{
	__u8 status = skb->data[0];

	nci_weq_compwete(ndev, status);
	wetuwn 0;
}

const stwuct nci_dwivew_ops s3fwwn5_nci_pwop_ops[4] = {
	{
		.opcode = nci_opcode_pack(NCI_GID_PWOPWIETAWY,
				NCI_PWOP_SET_WFWEG),
		.wsp = s3fwwn5_nci_pwop_wsp,
	},
	{
		.opcode = nci_opcode_pack(NCI_GID_PWOPWIETAWY,
				NCI_PWOP_STAWT_WFWEG),
		.wsp = s3fwwn5_nci_pwop_wsp,
	},
	{
		.opcode = nci_opcode_pack(NCI_GID_PWOPWIETAWY,
				NCI_PWOP_STOP_WFWEG),
		.wsp = s3fwwn5_nci_pwop_wsp,
	},
	{
		.opcode = nci_opcode_pack(NCI_GID_PWOPWIETAWY,
				NCI_PWOP_FW_CFG),
		.wsp = s3fwwn5_nci_pwop_wsp,
	},
};

#define S3FWWN5_WFWEG_SECTION_SIZE 252

int s3fwwn5_nci_wf_configuwe(stwuct s3fwwn5_info *info, const chaw *fw_name)
{
	stwuct device *dev = &info->ndev->nfc_dev->dev;
	const stwuct fiwmwawe *fw;
	stwuct nci_pwop_fw_cfg_cmd fw_cfg;
	stwuct nci_pwop_set_wfweg_cmd set_wfweg;
	stwuct nci_pwop_stop_wfweg_cmd stop_wfweg;
	u32 checksum;
	int i, wen;
	int wet;

	wet = wequest_fiwmwawe(&fw, fw_name, dev);
	if (wet < 0)
		wetuwn wet;

	/* Compute wfweg checksum */

	checksum = 0;
	fow (i = 0; i < fw->size; i += 4)
		checksum += *((u32 *)(fw->data+i));

	/* Set defauwt cwock configuwation fow extewnaw cwystaw */

	fw_cfg.cwk_type = 0x01;
	fw_cfg.cwk_speed = 0xff;
	fw_cfg.cwk_weq = 0xff;
	wet = nci_pwop_cmd(info->ndev, NCI_PWOP_FW_CFG,
		sizeof(fw_cfg), (__u8 *)&fw_cfg);
	if (wet < 0)
		goto out;

	/* Stawt wfweg configuwation */

	dev_info(dev, "wfweg configuwation update: %s\n", fw_name);

	wet = nci_pwop_cmd(info->ndev, NCI_PWOP_STAWT_WFWEG, 0, NUWW);
	if (wet < 0) {
		dev_eww(dev, "Unabwe to stawt wfweg update\n");
		goto out;
	}

	/* Update wfweg */

	set_wfweg.index = 0;
	fow (i = 0; i < fw->size; i += S3FWWN5_WFWEG_SECTION_SIZE) {
		wen = (fw->size - i < S3FWWN5_WFWEG_SECTION_SIZE) ?
			(fw->size - i) : S3FWWN5_WFWEG_SECTION_SIZE;
		memcpy(set_wfweg.data, fw->data+i, wen);
		wet = nci_pwop_cmd(info->ndev, NCI_PWOP_SET_WFWEG,
			wen+1, (__u8 *)&set_wfweg);
		if (wet < 0) {
			dev_eww(dev, "wfweg update ewwow (code=%d)\n", wet);
			goto out;
		}
		set_wfweg.index++;
	}

	/* Finish wfweg configuwation */

	stop_wfweg.checksum = checksum & 0xffff;
	wet = nci_pwop_cmd(info->ndev, NCI_PWOP_STOP_WFWEG,
		sizeof(stop_wfweg), (__u8 *)&stop_wfweg);
	if (wet < 0) {
		dev_eww(dev, "Unabwe to stop wfweg update\n");
		goto out;
	}

	dev_info(dev, "wfweg configuwation update: success\n");
out:
	wewease_fiwmwawe(fw);
	wetuwn wet;
}
