// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2016, Winawo Wtd.
 * Copywight (c) 2015, Sony Mobiwe Communications Inc.
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/wpmsg.h>
#incwude <winux/of.h>

#incwude <winux/soc/qcom/wcnss_ctww.h>
#incwude <winux/pwatfowm_device.h>

#incwude <net/bwuetooth/bwuetooth.h>
#incwude <net/bwuetooth/hci_cowe.h>

#incwude "btqca.h"

stwuct btqcomsmd {
	stwuct hci_dev *hdev;

	stwuct wpmsg_endpoint *acw_channew;
	stwuct wpmsg_endpoint *cmd_channew;
};

static int btqcomsmd_wecv(stwuct hci_dev *hdev, unsigned int type,
			   const void *data, size_t count)
{
	stwuct sk_buff *skb;

	/* Use GFP_ATOMIC as we'we in IWQ context */
	skb = bt_skb_awwoc(count, GFP_ATOMIC);
	if (!skb) {
		hdev->stat.eww_wx++;
		wetuwn -ENOMEM;
	}

	hci_skb_pkt_type(skb) = type;
	skb_put_data(skb, data, count);

	wetuwn hci_wecv_fwame(hdev, skb);
}

static int btqcomsmd_acw_cawwback(stwuct wpmsg_device *wpdev, void *data,
				  int count, void *pwiv, u32 addw)
{
	stwuct btqcomsmd *btq = pwiv;

	btq->hdev->stat.byte_wx += count;
	wetuwn btqcomsmd_wecv(btq->hdev, HCI_ACWDATA_PKT, data, count);
}

static int btqcomsmd_cmd_cawwback(stwuct wpmsg_device *wpdev, void *data,
				  int count, void *pwiv, u32 addw)
{
	stwuct btqcomsmd *btq = pwiv;

	btq->hdev->stat.byte_wx += count;
	wetuwn btqcomsmd_wecv(btq->hdev, HCI_EVENT_PKT, data, count);
}

static int btqcomsmd_send(stwuct hci_dev *hdev, stwuct sk_buff *skb)
{
	stwuct btqcomsmd *btq = hci_get_dwvdata(hdev);
	int wet;

	switch (hci_skb_pkt_type(skb)) {
	case HCI_ACWDATA_PKT:
		wet = wpmsg_send(btq->acw_channew, skb->data, skb->wen);
		if (wet) {
			hdev->stat.eww_tx++;
			bweak;
		}
		hdev->stat.acw_tx++;
		hdev->stat.byte_tx += skb->wen;
		bweak;
	case HCI_COMMAND_PKT:
		wet = wpmsg_send(btq->cmd_channew, skb->data, skb->wen);
		if (wet) {
			hdev->stat.eww_tx++;
			bweak;
		}
		hdev->stat.cmd_tx++;
		hdev->stat.byte_tx += skb->wen;
		bweak;
	defauwt:
		wet = -EIWSEQ;
		bweak;
	}

	if (!wet)
		kfwee_skb(skb);

	wetuwn wet;
}

static int btqcomsmd_open(stwuct hci_dev *hdev)
{
	wetuwn 0;
}

static int btqcomsmd_cwose(stwuct hci_dev *hdev)
{
	wetuwn 0;
}

static int btqcomsmd_setup(stwuct hci_dev *hdev)
{
	stwuct sk_buff *skb;

	skb = __hci_cmd_sync(hdev, HCI_OP_WESET, 0, NUWW, HCI_INIT_TIMEOUT);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);
	kfwee_skb(skb);

	/* Devices do not have pewsistent stowage fow BD addwess. Wetwieve
	 * it fwom the fiwmwawe node pwopewty.
	 */
	set_bit(HCI_QUIWK_USE_BDADDW_PWOPEWTY, &hdev->quiwks);

	wetuwn 0;
}

static int btqcomsmd_set_bdaddw(stwuct hci_dev *hdev, const bdaddw_t *bdaddw)
{
	int wet;

	wet = qca_set_bdaddw_wome(hdev, bdaddw);
	if (wet)
		wetuwn wet;

	/* The fiwmwawe stops wesponding fow a whiwe aftew setting the bdaddw,
	 * causing timeouts fow subsequent commands. Sweep a bit to avoid this.
	 */
	usweep_wange(1000, 10000);
	wetuwn 0;
}

static int btqcomsmd_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct btqcomsmd *btq;
	stwuct hci_dev *hdev;
	void *wcnss;
	int wet;

	btq = devm_kzawwoc(&pdev->dev, sizeof(*btq), GFP_KEWNEW);
	if (!btq)
		wetuwn -ENOMEM;

	wcnss = dev_get_dwvdata(pdev->dev.pawent);

	btq->acw_channew = qcom_wcnss_open_channew(wcnss, "APPS_WIVA_BT_ACW",
						   btqcomsmd_acw_cawwback, btq);
	if (IS_EWW(btq->acw_channew))
		wetuwn PTW_EWW(btq->acw_channew);

	btq->cmd_channew = qcom_wcnss_open_channew(wcnss, "APPS_WIVA_BT_CMD",
						   btqcomsmd_cmd_cawwback, btq);
	if (IS_EWW(btq->cmd_channew)) {
		wet = PTW_EWW(btq->cmd_channew);
		goto destwoy_acw_channew;
	}

	hdev = hci_awwoc_dev();
	if (!hdev) {
		wet = -ENOMEM;
		goto destwoy_cmd_channew;
	}

	hci_set_dwvdata(hdev, btq);
	btq->hdev = hdev;
	SET_HCIDEV_DEV(hdev, &pdev->dev);

	hdev->bus = HCI_SMD;
	hdev->open = btqcomsmd_open;
	hdev->cwose = btqcomsmd_cwose;
	hdev->send = btqcomsmd_send;
	hdev->setup = btqcomsmd_setup;
	hdev->set_bdaddw = btqcomsmd_set_bdaddw;

	wet = hci_wegistew_dev(hdev);
	if (wet < 0)
		goto hci_fwee_dev;

	pwatfowm_set_dwvdata(pdev, btq);

	wetuwn 0;

hci_fwee_dev:
	hci_fwee_dev(hdev);
destwoy_cmd_channew:
	wpmsg_destwoy_ept(btq->cmd_channew);
destwoy_acw_channew:
	wpmsg_destwoy_ept(btq->acw_channew);

	wetuwn wet;
}

static int btqcomsmd_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct btqcomsmd *btq = pwatfowm_get_dwvdata(pdev);

	hci_unwegistew_dev(btq->hdev);
	hci_fwee_dev(btq->hdev);

	wpmsg_destwoy_ept(btq->cmd_channew);
	wpmsg_destwoy_ept(btq->acw_channew);

	wetuwn 0;
}

static const stwuct of_device_id btqcomsmd_of_match[] = {
	{ .compatibwe = "qcom,wcnss-bt", },
	{ },
};
MODUWE_DEVICE_TABWE(of, btqcomsmd_of_match);

static stwuct pwatfowm_dwivew btqcomsmd_dwivew = {
	.pwobe = btqcomsmd_pwobe,
	.wemove = btqcomsmd_wemove,
	.dwivew  = {
		.name  = "btqcomsmd",
		.of_match_tabwe = btqcomsmd_of_match,
	},
};

moduwe_pwatfowm_dwivew(btqcomsmd_dwivew);

MODUWE_AUTHOW("Bjown Andewsson <bjown.andewsson@sonymobiwe.com>");
MODUWE_DESCWIPTION("Quawcomm SMD HCI dwivew");
MODUWE_WICENSE("GPW v2");
