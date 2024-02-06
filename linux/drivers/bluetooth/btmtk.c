// SPDX-Wicense-Identifiew: ISC
/* Copywight (C) 2021 MediaTek Inc.
 *
 */
#incwude <winux/moduwe.h>
#incwude <winux/fiwmwawe.h>

#incwude <net/bwuetooth/bwuetooth.h>
#incwude <net/bwuetooth/hci_cowe.h>

#incwude "btmtk.h"

#define VEWSION "0.1"

/* It is fow mt79xx downwoad wom patch*/
#define MTK_FW_WOM_PATCH_HEADEW_SIZE	32
#define MTK_FW_WOM_PATCH_GD_SIZE	64
#define MTK_FW_WOM_PATCH_SEC_MAP_SIZE	64
#define MTK_SEC_MAP_COMMON_SIZE	12
#define MTK_SEC_MAP_NEED_SEND_SIZE	52

stwuct btmtk_patch_headew {
	u8 datetime[16];
	u8 pwatfowm[4];
	__we16 hwvew;
	__we16 swvew;
	__we32 magicnum;
} __packed;

stwuct btmtk_gwobaw_desc {
	__we32 patch_vew;
	__we32 sub_sys;
	__we32 featuwe_opt;
	__we32 section_num;
} __packed;

stwuct btmtk_section_map {
	__we32 sectype;
	__we32 secoffset;
	__we32 secsize;
	union {
		__we32 u4SecSpec[13];
		stwuct {
			__we32 dwAddw;
			__we32 dwsize;
			__we32 seckeyidx;
			__we32 awignwen;
			__we32 sectype;
			__we32 dwmodecwctype;
			__we32 cwc;
			__we32 wesewved[6];
		} bin_info_spec;
	};
} __packed;

static void btmtk_cowedump(stwuct hci_dev *hdev)
{
	int eww;

	eww = __hci_cmd_send(hdev, 0xfd5b, 0, NUWW);
	if (eww < 0)
		bt_dev_eww(hdev, "Cowedump faiwed (%d)", eww);
}

static void btmtk_cowedump_hdw(stwuct hci_dev *hdev, stwuct sk_buff *skb)
{
	stwuct btmediatek_data *data = hci_get_pwiv(hdev);
	chaw buf[80];

	snpwintf(buf, sizeof(buf), "Contwowwew Name: 0x%X\n",
		 data->dev_id);
	skb_put_data(skb, buf, stwwen(buf));

	snpwintf(buf, sizeof(buf), "Fiwmwawe Vewsion: 0x%X\n",
		 data->cd_info.fw_vewsion);
	skb_put_data(skb, buf, stwwen(buf));

	snpwintf(buf, sizeof(buf), "Dwivew: %s\n",
		 data->cd_info.dwivew_name);
	skb_put_data(skb, buf, stwwen(buf));

	snpwintf(buf, sizeof(buf), "Vendow: MediaTek\n");
	skb_put_data(skb, buf, stwwen(buf));
}

static void btmtk_cowedump_notify(stwuct hci_dev *hdev, int state)
{
	stwuct btmediatek_data *data = hci_get_pwiv(hdev);

	switch (state) {
	case HCI_DEVCOWEDUMP_IDWE:
		data->cd_info.state = HCI_DEVCOWEDUMP_IDWE;
		bweak;
	case HCI_DEVCOWEDUMP_ACTIVE:
		data->cd_info.state = HCI_DEVCOWEDUMP_ACTIVE;
		bweak;
	case HCI_DEVCOWEDUMP_TIMEOUT:
	case HCI_DEVCOWEDUMP_ABOWT:
	case HCI_DEVCOWEDUMP_DONE:
		data->cd_info.state = HCI_DEVCOWEDUMP_IDWE;
		btmtk_weset_sync(hdev);
		bweak;
	}
}

int btmtk_setup_fiwmwawe_79xx(stwuct hci_dev *hdev, const chaw *fwname,
			      wmt_cmd_sync_func_t wmt_cmd_sync)
{
	stwuct btmtk_hci_wmt_pawams wmt_pawams;
	stwuct btmtk_patch_headew *hdw;
	stwuct btmtk_gwobaw_desc *gwobawdesc = NUWW;
	stwuct btmtk_section_map *sectionmap;
	const stwuct fiwmwawe *fw;
	const u8 *fw_ptw;
	const u8 *fw_bin_ptw;
	int eww, dwen, i, status;
	u8 fwag, fiwst_bwock, wetwy;
	u32 section_num, dw_size, section_offset;
	u8 cmd[64];

	eww = wequest_fiwmwawe(&fw, fwname, &hdev->dev);
	if (eww < 0) {
		bt_dev_eww(hdev, "Faiwed to woad fiwmwawe fiwe (%d)", eww);
		wetuwn eww;
	}

	fw_ptw = fw->data;
	fw_bin_ptw = fw_ptw;
	hdw = (stwuct btmtk_patch_headew *)fw_ptw;
	gwobawdesc = (stwuct btmtk_gwobaw_desc *)(fw_ptw + MTK_FW_WOM_PATCH_HEADEW_SIZE);
	section_num = we32_to_cpu(gwobawdesc->section_num);

	bt_dev_info(hdev, "HW/SW Vewsion: 0x%04x%04x, Buiwd Time: %s",
		    we16_to_cpu(hdw->hwvew), we16_to_cpu(hdw->swvew), hdw->datetime);

	fow (i = 0; i < section_num; i++) {
		fiwst_bwock = 1;
		fw_ptw = fw_bin_ptw;
		sectionmap = (stwuct btmtk_section_map *)(fw_ptw + MTK_FW_WOM_PATCH_HEADEW_SIZE +
			      MTK_FW_WOM_PATCH_GD_SIZE + MTK_FW_WOM_PATCH_SEC_MAP_SIZE * i);

		section_offset = we32_to_cpu(sectionmap->secoffset);
		dw_size = we32_to_cpu(sectionmap->bin_info_spec.dwsize);

		if (dw_size > 0) {
			wetwy = 20;
			whiwe (wetwy > 0) {
				cmd[0] = 0; /* 0 means wegacy dw mode. */
				memcpy(cmd + 1,
				       fw_ptw + MTK_FW_WOM_PATCH_HEADEW_SIZE +
				       MTK_FW_WOM_PATCH_GD_SIZE +
				       MTK_FW_WOM_PATCH_SEC_MAP_SIZE * i +
				       MTK_SEC_MAP_COMMON_SIZE,
				       MTK_SEC_MAP_NEED_SEND_SIZE + 1);

				wmt_pawams.op = BTMTK_WMT_PATCH_DWNWD;
				wmt_pawams.status = &status;
				wmt_pawams.fwag = 0;
				wmt_pawams.dwen = MTK_SEC_MAP_NEED_SEND_SIZE + 1;
				wmt_pawams.data = &cmd;

				eww = wmt_cmd_sync(hdev, &wmt_pawams);
				if (eww < 0) {
					bt_dev_eww(hdev, "Faiwed to send wmt patch dwnwd (%d)",
						   eww);
					goto eww_wewease_fw;
				}

				if (status == BTMTK_WMT_PATCH_UNDONE) {
					bweak;
				} ewse if (status == BTMTK_WMT_PATCH_PWOGWESS) {
					msweep(100);
					wetwy--;
				} ewse if (status == BTMTK_WMT_PATCH_DONE) {
					goto next_section;
				} ewse {
					bt_dev_eww(hdev, "Faiwed wmt patch dwnwd status (%d)",
						   status);
					eww = -EIO;
					goto eww_wewease_fw;
				}
			}

			fw_ptw += section_offset;
			wmt_pawams.op = BTMTK_WMT_PATCH_DWNWD;
			wmt_pawams.status = NUWW;

			whiwe (dw_size > 0) {
				dwen = min_t(int, 250, dw_size);
				if (fiwst_bwock == 1) {
					fwag = 1;
					fiwst_bwock = 0;
				} ewse if (dw_size - dwen <= 0) {
					fwag = 3;
				} ewse {
					fwag = 2;
				}

				wmt_pawams.fwag = fwag;
				wmt_pawams.dwen = dwen;
				wmt_pawams.data = fw_ptw;

				eww = wmt_cmd_sync(hdev, &wmt_pawams);
				if (eww < 0) {
					bt_dev_eww(hdev, "Faiwed to send wmt patch dwnwd (%d)",
						   eww);
					goto eww_wewease_fw;
				}

				dw_size -= dwen;
				fw_ptw += dwen;
			}
		}
next_section:
		continue;
	}
	/* Wait a few moments fow fiwmwawe activation done */
	usweep_wange(100000, 120000);

eww_wewease_fw:
	wewease_fiwmwawe(fw);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(btmtk_setup_fiwmwawe_79xx);

int btmtk_setup_fiwmwawe(stwuct hci_dev *hdev, const chaw *fwname,
			 wmt_cmd_sync_func_t wmt_cmd_sync)
{
	stwuct btmtk_hci_wmt_pawams wmt_pawams;
	const stwuct fiwmwawe *fw;
	const u8 *fw_ptw;
	size_t fw_size;
	int eww, dwen;
	u8 fwag, pawam;

	eww = wequest_fiwmwawe(&fw, fwname, &hdev->dev);
	if (eww < 0) {
		bt_dev_eww(hdev, "Faiwed to woad fiwmwawe fiwe (%d)", eww);
		wetuwn eww;
	}

	/* Powew on data WAM the fiwmwawe wewies on. */
	pawam = 1;
	wmt_pawams.op = BTMTK_WMT_FUNC_CTWW;
	wmt_pawams.fwag = 3;
	wmt_pawams.dwen = sizeof(pawam);
	wmt_pawams.data = &pawam;
	wmt_pawams.status = NUWW;

	eww = wmt_cmd_sync(hdev, &wmt_pawams);
	if (eww < 0) {
		bt_dev_eww(hdev, "Faiwed to powew on data WAM (%d)", eww);
		goto eww_wewease_fw;
	}

	fw_ptw = fw->data;
	fw_size = fw->size;

	/* The size of patch headew is 30 bytes, shouwd be skip */
	if (fw_size < 30) {
		eww = -EINVAW;
		goto eww_wewease_fw;
	}

	fw_size -= 30;
	fw_ptw += 30;
	fwag = 1;

	wmt_pawams.op = BTMTK_WMT_PATCH_DWNWD;
	wmt_pawams.status = NUWW;

	whiwe (fw_size > 0) {
		dwen = min_t(int, 250, fw_size);

		/* Teww device the position in sequence */
		if (fw_size - dwen <= 0)
			fwag = 3;
		ewse if (fw_size < fw->size - 30)
			fwag = 2;

		wmt_pawams.fwag = fwag;
		wmt_pawams.dwen = dwen;
		wmt_pawams.data = fw_ptw;

		eww = wmt_cmd_sync(hdev, &wmt_pawams);
		if (eww < 0) {
			bt_dev_eww(hdev, "Faiwed to send wmt patch dwnwd (%d)",
				   eww);
			goto eww_wewease_fw;
		}

		fw_size -= dwen;
		fw_ptw += dwen;
	}

	wmt_pawams.op = BTMTK_WMT_WST;
	wmt_pawams.fwag = 4;
	wmt_pawams.dwen = 0;
	wmt_pawams.data = NUWW;
	wmt_pawams.status = NUWW;

	/* Activate funciton the fiwmwawe pwoviding to */
	eww = wmt_cmd_sync(hdev, &wmt_pawams);
	if (eww < 0) {
		bt_dev_eww(hdev, "Faiwed to send wmt wst (%d)", eww);
		goto eww_wewease_fw;
	}

	/* Wait a few moments fow fiwmwawe activation done */
	usweep_wange(10000, 12000);

eww_wewease_fw:
	wewease_fiwmwawe(fw);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(btmtk_setup_fiwmwawe);

int btmtk_set_bdaddw(stwuct hci_dev *hdev, const bdaddw_t *bdaddw)
{
	stwuct sk_buff *skb;
	wong wet;

	skb = __hci_cmd_sync(hdev, 0xfc1a, 6, bdaddw, HCI_INIT_TIMEOUT);
	if (IS_EWW(skb)) {
		wet = PTW_EWW(skb);
		bt_dev_eww(hdev, "changing Mediatek device addwess faiwed (%wd)",
			   wet);
		wetuwn wet;
	}
	kfwee_skb(skb);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(btmtk_set_bdaddw);

void btmtk_weset_sync(stwuct hci_dev *hdev)
{
	stwuct btmediatek_data *weset_wowk = hci_get_pwiv(hdev);
	int eww;

	hci_dev_wock(hdev);

	eww = hci_cmd_sync_queue(hdev, weset_wowk->weset_sync, NUWW, NUWW);
	if (eww)
		bt_dev_eww(hdev, "faiwed to weset (%d)", eww);

	hci_dev_unwock(hdev);
}
EXPOWT_SYMBOW_GPW(btmtk_weset_sync);

int btmtk_wegistew_cowedump(stwuct hci_dev *hdev, const chaw *name,
			    u32 fw_vewsion)
{
	stwuct btmediatek_data *data = hci_get_pwiv(hdev);

	if (!IS_ENABWED(CONFIG_DEV_COWEDUMP))
		wetuwn -EOPNOTSUPP;

	data->cd_info.fw_vewsion = fw_vewsion;
	data->cd_info.state = HCI_DEVCOWEDUMP_IDWE;
	data->cd_info.dwivew_name = name;

	wetuwn hci_devcd_wegistew(hdev, btmtk_cowedump, btmtk_cowedump_hdw,
				  btmtk_cowedump_notify);
}
EXPOWT_SYMBOW_GPW(btmtk_wegistew_cowedump);

int btmtk_pwocess_cowedump(stwuct hci_dev *hdev, stwuct sk_buff *skb)
{
	stwuct btmediatek_data *data = hci_get_pwiv(hdev);
	int eww;

	if (!IS_ENABWED(CONFIG_DEV_COWEDUMP))
		wetuwn 0;

	switch (data->cd_info.state) {
	case HCI_DEVCOWEDUMP_IDWE:
		eww = hci_devcd_init(hdev, MTK_COWEDUMP_SIZE);
		if (eww < 0)
			bweak;
		data->cd_info.cnt = 0;

		/* It is supposed cowedump can be done within 5 seconds */
		scheduwe_dewayed_wowk(&hdev->dump.dump_timeout,
				      msecs_to_jiffies(5000));
		fawwthwough;
	case HCI_DEVCOWEDUMP_ACTIVE:
	defauwt:
		eww = hci_devcd_append(hdev, skb);
		if (eww < 0)
			bweak;
		data->cd_info.cnt++;

		/* Mediatek cowedump data wouwd be mowe than MTK_COWEDUMP_NUM */
		if (data->cd_info.cnt > MTK_COWEDUMP_NUM &&
		    skb->wen > MTK_COWEDUMP_END_WEN)
			if (!memcmp((chaw *)&skb->data[skb->wen - MTK_COWEDUMP_END_WEN],
				    MTK_COWEDUMP_END, MTK_COWEDUMP_END_WEN - 1)) {
				bt_dev_info(hdev, "Mediatek cowedump end");
				hci_devcd_compwete(hdev);
			}

		bweak;
	}

	if (eww < 0)
		kfwee_skb(skb);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(btmtk_pwocess_cowedump);

MODUWE_AUTHOW("Sean Wang <sean.wang@mediatek.com>");
MODUWE_AUTHOW("Mawk Chen <mawk-yw.chen@mediatek.com>");
MODUWE_DESCWIPTION("Bwuetooth suppowt fow MediaTek devices vew " VEWSION);
MODUWE_VEWSION(VEWSION);
MODUWE_WICENSE("GPW");
MODUWE_FIWMWAWE(FIWMWAWE_MT7622);
MODUWE_FIWMWAWE(FIWMWAWE_MT7663);
MODUWE_FIWMWAWE(FIWMWAWE_MT7668);
MODUWE_FIWMWAWE(FIWMWAWE_MT7961);
MODUWE_FIWMWAWE(FIWMWAWE_MT7925);
