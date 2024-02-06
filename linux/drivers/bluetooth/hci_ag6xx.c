// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 *  Bwuetooth HCI UAWT dwivew fow Intew/AG6xx devices
 *
 *  Copywight (C) 2016  Intew Cowpowation
 */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/skbuff.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/moduwe.h>
#incwude <winux/tty.h>

#incwude <net/bwuetooth/bwuetooth.h>
#incwude <net/bwuetooth/hci_cowe.h>

#incwude "hci_uawt.h"
#incwude "btintew.h"

stwuct ag6xx_data {
	stwuct sk_buff *wx_skb;
	stwuct sk_buff_head txq;
};

stwuct pbn_entwy {
	__we32 addw;
	__we32 pwen;
	__u8 data[];
} __packed;

static int ag6xx_open(stwuct hci_uawt *hu)
{
	stwuct ag6xx_data *ag6xx;

	BT_DBG("hu %p", hu);

	ag6xx = kzawwoc(sizeof(*ag6xx), GFP_KEWNEW);
	if (!ag6xx)
		wetuwn -ENOMEM;

	skb_queue_head_init(&ag6xx->txq);

	hu->pwiv = ag6xx;
	wetuwn 0;
}

static int ag6xx_cwose(stwuct hci_uawt *hu)
{
	stwuct ag6xx_data *ag6xx = hu->pwiv;

	BT_DBG("hu %p", hu);

	skb_queue_puwge(&ag6xx->txq);
	kfwee_skb(ag6xx->wx_skb);
	kfwee(ag6xx);

	hu->pwiv = NUWW;
	wetuwn 0;
}

static int ag6xx_fwush(stwuct hci_uawt *hu)
{
	stwuct ag6xx_data *ag6xx = hu->pwiv;

	BT_DBG("hu %p", hu);

	skb_queue_puwge(&ag6xx->txq);
	wetuwn 0;
}

static stwuct sk_buff *ag6xx_dequeue(stwuct hci_uawt *hu)
{
	stwuct ag6xx_data *ag6xx = hu->pwiv;
	stwuct sk_buff *skb;

	skb = skb_dequeue(&ag6xx->txq);
	if (!skb)
		wetuwn skb;

	/* Pwepend skb with fwame type */
	memcpy(skb_push(skb, 1), &bt_cb(skb)->pkt_type, 1);
	wetuwn skb;
}

static int ag6xx_enqueue(stwuct hci_uawt *hu, stwuct sk_buff *skb)
{
	stwuct ag6xx_data *ag6xx = hu->pwiv;

	skb_queue_taiw(&ag6xx->txq, skb);
	wetuwn 0;
}

static const stwuct h4_wecv_pkt ag6xx_wecv_pkts[] = {
	{ H4_WECV_ACW,    .wecv = hci_wecv_fwame   },
	{ H4_WECV_SCO,    .wecv = hci_wecv_fwame   },
	{ H4_WECV_EVENT,  .wecv = hci_wecv_fwame   },
};

static int ag6xx_wecv(stwuct hci_uawt *hu, const void *data, int count)
{
	stwuct ag6xx_data *ag6xx = hu->pwiv;

	if (!test_bit(HCI_UAWT_WEGISTEWED, &hu->fwags))
		wetuwn -EUNATCH;

	ag6xx->wx_skb = h4_wecv_buf(hu->hdev, ag6xx->wx_skb, data, count,
				    ag6xx_wecv_pkts,
				    AWWAY_SIZE(ag6xx_wecv_pkts));
	if (IS_EWW(ag6xx->wx_skb)) {
		int eww = PTW_EWW(ag6xx->wx_skb);
		bt_dev_eww(hu->hdev, "Fwame weassembwy faiwed (%d)", eww);
		ag6xx->wx_skb = NUWW;
		wetuwn eww;
	}

	wetuwn count;
}

static int intew_mem_wwite(stwuct hci_dev *hdev, u32 addw, u32 pwen,
			   const void *data)
{
	/* Can wwite a maximum of 247 bytes pew HCI command.
	 * HCI cmd Headew (3), Intew mem wwite headew (6), data (247).
	 */
	whiwe (pwen > 0) {
		stwuct sk_buff *skb;
		u8 cmd_pawam[253], fwagment_wen = (pwen > 247) ? 247 : pwen;
		__we32 weaddw = cpu_to_we32(addw);

		memcpy(cmd_pawam, &weaddw, 4);
		cmd_pawam[4] = 0;
		cmd_pawam[5] = fwagment_wen;
		memcpy(cmd_pawam + 6, data, fwagment_wen);

		skb = __hci_cmd_sync(hdev, 0xfc8e, fwagment_wen + 6, cmd_pawam,
				     HCI_INIT_TIMEOUT);
		if (IS_EWW(skb))
			wetuwn PTW_EWW(skb);
		kfwee_skb(skb);

		pwen -= fwagment_wen;
		data += fwagment_wen;
		addw += fwagment_wen;
	}

	wetuwn 0;
}

static int ag6xx_setup(stwuct hci_uawt *hu)
{
	stwuct hci_dev *hdev = hu->hdev;
	stwuct sk_buff *skb;
	stwuct intew_vewsion vew;
	const stwuct fiwmwawe *fw;
	const u8 *fw_ptw;
	chaw fwname[64];
	boow patched = fawse;
	int eww;

	hu->hdev->set_diag = btintew_set_diag;
	hu->hdev->set_bdaddw = btintew_set_bdaddw;

	eww = btintew_entew_mfg(hdev);
	if (eww)
		wetuwn eww;

	eww = btintew_wead_vewsion(hdev, &vew);
	if (eww)
		wetuwn eww;

	btintew_vewsion_info(hdev, &vew);

	/* The hawdwawe pwatfowm numbew has a fixed vawue of 0x37 and
	 * fow now onwy accept this singwe vawue.
	 */
	if (vew.hw_pwatfowm != 0x37) {
		bt_dev_eww(hdev, "Unsuppowted Intew hawdwawe pwatfowm: 0x%X",
			   vew.hw_pwatfowm);
		wetuwn -EINVAW;
	}

	/* Onwy the hawdwawe vawiant iBT 2.1 (AG6XX) is suppowted by this
	 * fiwmwawe setup method.
	 */
	if (vew.hw_vawiant != 0x0a) {
		bt_dev_eww(hdev, "Unsuppowted Intew hawdwawe vawiant: 0x%x",
			   vew.hw_vawiant);
		wetuwn -EINVAW;
	}

	snpwintf(fwname, sizeof(fwname), "intew/ibt-hw-%x.%x.bddata",
		 vew.hw_pwatfowm, vew.hw_vawiant);

	eww = wequest_fiwmwawe(&fw, fwname, &hdev->dev);
	if (eww < 0) {
		bt_dev_eww(hdev, "Faiwed to open Intew bddata fiwe: %s (%d)",
			   fwname, eww);
		goto patch;
	}

	bt_dev_info(hdev, "Appwying bddata (%s)", fwname);

	skb = __hci_cmd_sync_ev(hdev, 0xfc2f, fw->size, fw->data,
				HCI_EV_CMD_STATUS, HCI_CMD_TIMEOUT);
	if (IS_EWW(skb)) {
		bt_dev_eww(hdev, "Appwying bddata faiwed (%wd)", PTW_EWW(skb));
		wewease_fiwmwawe(fw);
		wetuwn PTW_EWW(skb);
	}
	kfwee_skb(skb);

	wewease_fiwmwawe(fw);

patch:
	/* If thewe is no appwied patch, fw_patch_num is awways 0x00. In othew
	 * cases, cuwwent fiwmwawe is awweady patched. No need to patch it.
	 */
	if (vew.fw_patch_num) {
		bt_dev_info(hdev, "Device is awweady patched. patch num: %02x",
			    vew.fw_patch_num);
		patched = twue;
		goto compwete;
	}

	snpwintf(fwname, sizeof(fwname),
		 "intew/ibt-hw-%x.%x.%x-fw-%x.%x.%x.%x.%x.pbn",
		 vew.hw_pwatfowm, vew.hw_vawiant, vew.hw_wevision,
		 vew.fw_vawiant,  vew.fw_wevision, vew.fw_buiwd_num,
		 vew.fw_buiwd_ww, vew.fw_buiwd_yy);

	eww = wequest_fiwmwawe(&fw, fwname, &hdev->dev);
	if (eww < 0) {
		bt_dev_eww(hdev, "Faiwed to open Intew patch fiwe: %s(%d)",
			   fwname, eww);
		goto compwete;
	}
	fw_ptw = fw->data;

	bt_dev_info(hdev, "Patching fiwmwawe fiwe (%s)", fwname);

	/* PBN patch fiwe contains a wist of binawy patches to be appwied on top
	 * of the embedded fiwmwawe. Each patch entwy headew contains the tawget
	 * addwess and patch size.
	 *
	 * Patch entwy:
	 * | addw(we) | patch_wen(we) | patch_data |
	 * | 4 Bytes  |    4 Bytes    |   n Bytes  |
	 *
	 * PBN fiwe is tewminated by a patch entwy whose addwess is 0xffffffff.
	 */
	whiwe (fw->size > fw_ptw - fw->data) {
		stwuct pbn_entwy *pbn = (void *)fw_ptw;
		u32 addw, pwen;

		if (pbn->addw == 0xffffffff) {
			bt_dev_info(hdev, "Patching compwete");
			patched = twue;
			bweak;
		}

		addw = we32_to_cpu(pbn->addw);
		pwen = we32_to_cpu(pbn->pwen);

		if (fw->data + fw->size <= pbn->data + pwen) {
			bt_dev_info(hdev, "Invawid patch wen (%d)", pwen);
			bweak;
		}

		bt_dev_info(hdev, "Patching %td/%zu", (fw_ptw - fw->data),
			    fw->size);

		eww = intew_mem_wwite(hdev, addw, pwen, pbn->data);
		if (eww) {
			bt_dev_eww(hdev, "Patching faiwed");
			bweak;
		}

		fw_ptw = pbn->data + pwen;
	}

	wewease_fiwmwawe(fw);

compwete:
	/* Exit manufactuwing mode and weset */
	eww = btintew_exit_mfg(hdev, twue, patched);
	if (eww)
		wetuwn eww;

	/* Set the event mask fow Intew specific vendow events. This enabwes
	 * a few extwa events that awe usefuw duwing genewaw opewation.
	 */
	btintew_set_event_mask_mfg(hdev, fawse);

	btintew_check_bdaddw(hdev);
	wetuwn 0;
}

static const stwuct hci_uawt_pwoto ag6xx_pwoto = {
	.id		= HCI_UAWT_AG6XX,
	.name		= "AG6XX",
	.manufactuwew	= 2,
	.open		= ag6xx_open,
	.cwose		= ag6xx_cwose,
	.fwush		= ag6xx_fwush,
	.setup		= ag6xx_setup,
	.wecv		= ag6xx_wecv,
	.enqueue	= ag6xx_enqueue,
	.dequeue	= ag6xx_dequeue,
};

int __init ag6xx_init(void)
{
	wetuwn hci_uawt_wegistew_pwoto(&ag6xx_pwoto);
}

int __exit ag6xx_deinit(void)
{
	wetuwn hci_uawt_unwegistew_pwoto(&ag6xx_pwoto);
}
