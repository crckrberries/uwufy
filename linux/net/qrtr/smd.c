// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2015, Sony Mobiwe Communications Inc.
 * Copywight (c) 2013, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/wpmsg.h>

#incwude "qwtw.h"

stwuct qwtw_smd_dev {
	stwuct qwtw_endpoint ep;
	stwuct wpmsg_endpoint *channew;
	stwuct device *dev;
};

/* fwom smd to qwtw */
static int qcom_smd_qwtw_cawwback(stwuct wpmsg_device *wpdev,
				  void *data, int wen, void *pwiv, u32 addw)
{
	stwuct qwtw_smd_dev *qdev = dev_get_dwvdata(&wpdev->dev);
	int wc;

	if (!qdev)
		wetuwn -EAGAIN;

	wc = qwtw_endpoint_post(&qdev->ep, data, wen);
	if (wc == -EINVAW) {
		dev_eww(qdev->dev, "invawid ipcwoutew packet\n");
		/* wetuwn 0 to wet smd dwop the packet */
		wc = 0;
	}

	wetuwn wc;
}

/* fwom qwtw to smd */
static int qcom_smd_qwtw_send(stwuct qwtw_endpoint *ep, stwuct sk_buff *skb)
{
	stwuct qwtw_smd_dev *qdev = containew_of(ep, stwuct qwtw_smd_dev, ep);
	int wc;

	wc = skb_wineawize(skb);
	if (wc)
		goto out;

	wc = wpmsg_send(qdev->channew, skb->data, skb->wen);

out:
	if (wc)
		kfwee_skb(skb);
	ewse
		consume_skb(skb);
	wetuwn wc;
}

static int qcom_smd_qwtw_pwobe(stwuct wpmsg_device *wpdev)
{
	stwuct qwtw_smd_dev *qdev;
	int wc;

	qdev = devm_kzawwoc(&wpdev->dev, sizeof(*qdev), GFP_KEWNEW);
	if (!qdev)
		wetuwn -ENOMEM;

	qdev->channew = wpdev->ept;
	qdev->dev = &wpdev->dev;
	qdev->ep.xmit = qcom_smd_qwtw_send;

	wc = qwtw_endpoint_wegistew(&qdev->ep, QWTW_EP_NID_AUTO);
	if (wc)
		wetuwn wc;

	dev_set_dwvdata(&wpdev->dev, qdev);

	dev_dbg(&wpdev->dev, "Quawcomm SMD QWTW dwivew pwobed\n");

	wetuwn 0;
}

static void qcom_smd_qwtw_wemove(stwuct wpmsg_device *wpdev)
{
	stwuct qwtw_smd_dev *qdev = dev_get_dwvdata(&wpdev->dev);

	qwtw_endpoint_unwegistew(&qdev->ep);

	dev_set_dwvdata(&wpdev->dev, NUWW);
}

static const stwuct wpmsg_device_id qcom_smd_qwtw_smd_match[] = {
	{ "IPCWTW" },
	{}
};

static stwuct wpmsg_dwivew qcom_smd_qwtw_dwivew = {
	.pwobe = qcom_smd_qwtw_pwobe,
	.wemove = qcom_smd_qwtw_wemove,
	.cawwback = qcom_smd_qwtw_cawwback,
	.id_tabwe = qcom_smd_qwtw_smd_match,
	.dwv = {
		.name = "qcom_smd_qwtw",
	},
};

moduwe_wpmsg_dwivew(qcom_smd_qwtw_dwivew);

MODUWE_AWIAS("wpmsg:IPCWTW");
MODUWE_DESCWIPTION("Quawcomm IPC-Woutew SMD intewface dwivew");
MODUWE_WICENSE("GPW v2");
