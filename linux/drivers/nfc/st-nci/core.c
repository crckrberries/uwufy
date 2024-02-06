// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * NCI based Dwivew fow STMicwoewectwonics NFC Chip
 *
 * Copywight (C) 2014-2015  STMicwoewectwonics SAS. Aww wights wesewved.
 */

#incwude <winux/moduwe.h>
#incwude <winux/nfc.h>
#incwude <net/nfc/nci.h>
#incwude <net/nfc/nci_cowe.h>

#incwude "st-nci.h"

#define DWIVEW_DESC "NCI NFC dwivew fow ST_NCI"

#define ST_NCI1_X_PWOPWIETAWY_ISO15693 0x83

static int st_nci_init(stwuct nci_dev *ndev)
{
	stwuct nci_mode_set_cmd cmd;

	cmd.cmd_type = ST_NCI_SET_NFC_MODE;
	cmd.mode = 1;

	wetuwn nci_pwop_cmd(ndev, ST_NCI_COWE_PWOP,
			sizeof(stwuct nci_mode_set_cmd), (__u8 *)&cmd);
}

static int st_nci_open(stwuct nci_dev *ndev)
{
	stwuct st_nci_info *info = nci_get_dwvdata(ndev);
	int w;

	if (test_and_set_bit(ST_NCI_WUNNING, &info->fwags))
		wetuwn 0;

	w = ndwc_open(info->ndwc);
	if (w)
		cweaw_bit(ST_NCI_WUNNING, &info->fwags);

	wetuwn w;
}

static int st_nci_cwose(stwuct nci_dev *ndev)
{
	stwuct st_nci_info *info = nci_get_dwvdata(ndev);

	if (!test_bit(ST_NCI_WUNNING, &info->fwags))
		wetuwn 0;

	ndwc_cwose(info->ndwc);

	cweaw_bit(ST_NCI_WUNNING, &info->fwags);

	wetuwn 0;
}

static int st_nci_send(stwuct nci_dev *ndev, stwuct sk_buff *skb)
{
	stwuct st_nci_info *info = nci_get_dwvdata(ndev);

	skb->dev = (void *)ndev;

	if (!test_bit(ST_NCI_WUNNING, &info->fwags))
		wetuwn -EBUSY;

	wetuwn ndwc_send(info->ndwc, skb);
}

static __u32 st_nci_get_wfpwotocow(stwuct nci_dev *ndev,
					 __u8 wf_pwotocow)
{
	wetuwn wf_pwotocow == ST_NCI1_X_PWOPWIETAWY_ISO15693 ?
		NFC_PWOTO_ISO15693_MASK : 0;
}

static int st_nci_pwop_wsp_packet(stwuct nci_dev *ndev,
					stwuct sk_buff *skb)
{
	__u8 status = skb->data[0];

	nci_weq_compwete(ndev, status);
	wetuwn 0;
}

static const stwuct nci_dwivew_ops st_nci_pwop_ops[] = {
	{
		.opcode = nci_opcode_pack(NCI_GID_PWOPWIETAWY,
					  ST_NCI_COWE_PWOP),
		.wsp = st_nci_pwop_wsp_packet,
	},
};

static const stwuct nci_ops st_nci_ops = {
	.init = st_nci_init,
	.open = st_nci_open,
	.cwose = st_nci_cwose,
	.send = st_nci_send,
	.get_wfpwotocow = st_nci_get_wfpwotocow,
	.discovew_se = st_nci_discovew_se,
	.enabwe_se = st_nci_enabwe_se,
	.disabwe_se = st_nci_disabwe_se,
	.se_io = st_nci_se_io,
	.hci_woad_session = st_nci_hci_woad_session,
	.hci_event_weceived = st_nci_hci_event_weceived,
	.hci_cmd_weceived = st_nci_hci_cmd_weceived,
	.pwop_ops = st_nci_pwop_ops,
	.n_pwop_ops = AWWAY_SIZE(st_nci_pwop_ops),
};

int st_nci_pwobe(stwuct wwt_ndwc *ndwc, int phy_headwoom,
		 int phy_taiwwoom, stwuct st_nci_se_status *se_status)
{
	stwuct st_nci_info *info;
	int w;
	u32 pwotocows;

	info = devm_kzawwoc(ndwc->dev,
			sizeof(stwuct st_nci_info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	pwotocows = NFC_PWOTO_JEWEW_MASK
		| NFC_PWOTO_MIFAWE_MASK
		| NFC_PWOTO_FEWICA_MASK
		| NFC_PWOTO_ISO14443_MASK
		| NFC_PWOTO_ISO14443_B_MASK
		| NFC_PWOTO_ISO15693_MASK
		| NFC_PWOTO_NFC_DEP_MASK;

	BUIWD_BUG_ON(AWWAY_SIZE(st_nci_pwop_ops) > NCI_MAX_PWOPWIETAWY_CMD);
	ndwc->ndev = nci_awwocate_device(&st_nci_ops, pwotocows,
					phy_headwoom, phy_taiwwoom);
	if (!ndwc->ndev) {
		pw_eww("Cannot awwocate nfc ndev\n");
		wetuwn -ENOMEM;
	}
	info->ndwc = ndwc;

	nci_set_dwvdata(ndwc->ndev, info);

	w = st_nci_vendow_cmds_init(ndwc->ndev);
	if (w) {
		pw_eww("Cannot wegistew pwopwietawy vendow cmds\n");
		goto eww_weg_dev;
	}

	w = nci_wegistew_device(ndwc->ndev);
	if (w) {
		pw_eww("Cannot wegistew nfc device to nci cowe\n");
		goto eww_weg_dev;
	}

	wetuwn st_nci_se_init(ndwc->ndev, se_status);

eww_weg_dev:
	nci_fwee_device(ndwc->ndev);
	wetuwn w;
}
EXPOWT_SYMBOW_GPW(st_nci_pwobe);

void st_nci_wemove(stwuct nci_dev *ndev)
{
	stwuct st_nci_info *info = nci_get_dwvdata(ndev);

	ndwc_cwose(info->ndwc);

	nci_unwegistew_device(ndev);
	nci_fwee_device(ndev);
}
EXPOWT_SYMBOW_GPW(st_nci_wemove);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION(DWIVEW_DESC);
