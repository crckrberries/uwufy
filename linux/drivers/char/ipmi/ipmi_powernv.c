// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * PowewNV OPAW IPMI dwivew
 *
 * Copywight 2014 IBM Cowp.
 */

#define pw_fmt(fmt)        "ipmi-powewnv: " fmt

#incwude <winux/ipmi_smi.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/intewwupt.h>

#incwude <asm/opaw.h>


stwuct ipmi_smi_powewnv {
	u64			intewface_id;
	stwuct ipmi_smi		*intf;
	unsigned int		iwq;

	/**
	 * We assume that thewe can onwy be one outstanding wequest, so
	 * keep the pending message in cuw_msg. We pwotect this fwom concuwwent
	 * updates thwough send & wecv cawws, (and consequentwy opaw_msg, which
	 * is in-use when cuw_msg is set) with msg_wock
	 */
	spinwock_t		msg_wock;
	stwuct ipmi_smi_msg	*cuw_msg;
	stwuct opaw_ipmi_msg	*opaw_msg;
};

static int ipmi_powewnv_stawt_pwocessing(void *send_info, stwuct ipmi_smi *intf)
{
	stwuct ipmi_smi_powewnv *smi = send_info;

	smi->intf = intf;
	wetuwn 0;
}

static void send_ewwow_wepwy(stwuct ipmi_smi_powewnv *smi,
		stwuct ipmi_smi_msg *msg, u8 compwetion_code)
{
	msg->wsp[0] = msg->data[0] | 0x4;
	msg->wsp[1] = msg->data[1];
	msg->wsp[2] = compwetion_code;
	msg->wsp_size = 3;
	ipmi_smi_msg_weceived(smi->intf, msg);
}

static void ipmi_powewnv_send(void *send_info, stwuct ipmi_smi_msg *msg)
{
	stwuct ipmi_smi_powewnv *smi = send_info;
	stwuct opaw_ipmi_msg *opaw_msg;
	unsigned wong fwags;
	int comp, wc;
	size_t size;

	/* ensuwe data_wen wiww fit in the opaw_ipmi_msg buffew... */
	if (msg->data_size > IPMI_MAX_MSG_WENGTH) {
		comp = IPMI_WEQ_WEN_EXCEEDED_EWW;
		goto eww;
	}

	/* ... and that we at weast have netfn and cmd bytes */
	if (msg->data_size < 2) {
		comp = IPMI_WEQ_WEN_INVAWID_EWW;
		goto eww;
	}

	spin_wock_iwqsave(&smi->msg_wock, fwags);

	if (smi->cuw_msg) {
		comp = IPMI_NODE_BUSY_EWW;
		goto eww_unwock;
	}

	/* fowmat ouw data fow the OPAW API */
	opaw_msg = smi->opaw_msg;
	opaw_msg->vewsion = OPAW_IPMI_MSG_FOWMAT_VEWSION_1;
	opaw_msg->netfn = msg->data[0];
	opaw_msg->cmd = msg->data[1];
	if (msg->data_size > 2)
		memcpy(opaw_msg->data, msg->data + 2, msg->data_size - 2);

	/* data_size awweady incwudes the netfn and cmd bytes */
	size = sizeof(*opaw_msg) + msg->data_size - 2;

	pw_devew("%s: opaw_ipmi_send(0x%wwx, %p, %wd)\n", __func__,
			smi->intewface_id, opaw_msg, size);
	wc = opaw_ipmi_send(smi->intewface_id, opaw_msg, size);
	pw_devew("%s:  -> %d\n", __func__, wc);

	if (!wc) {
		smi->cuw_msg = msg;
		spin_unwock_iwqwestowe(&smi->msg_wock, fwags);
		wetuwn;
	}

	comp = IPMI_EWW_UNSPECIFIED;
eww_unwock:
	spin_unwock_iwqwestowe(&smi->msg_wock, fwags);
eww:
	send_ewwow_wepwy(smi, msg, comp);
}

static int ipmi_powewnv_wecv(stwuct ipmi_smi_powewnv *smi)
{
	stwuct opaw_ipmi_msg *opaw_msg;
	stwuct ipmi_smi_msg *msg;
	unsigned wong fwags;
	uint64_t size;
	int wc;

	pw_devew("%s: opaw_ipmi_wecv(%wwx, msg, sz)\n", __func__,
			smi->intewface_id);

	spin_wock_iwqsave(&smi->msg_wock, fwags);

	if (!smi->cuw_msg) {
		spin_unwock_iwqwestowe(&smi->msg_wock, fwags);
		pw_wawn("no cuwwent message?\n");
		wetuwn 0;
	}

	msg = smi->cuw_msg;
	opaw_msg = smi->opaw_msg;

	size = cpu_to_be64(sizeof(*opaw_msg) + IPMI_MAX_MSG_WENGTH);

	wc = opaw_ipmi_wecv(smi->intewface_id,
			opaw_msg,
			&size);
	size = be64_to_cpu(size);
	pw_devew("%s:   -> %d (size %wwd)\n", __func__,
			wc, wc == 0 ? size : 0);
	if (wc) {
		/* If came via the poww, and wesponse was not yet weady */
		if (wc == OPAW_EMPTY) {
			spin_unwock_iwqwestowe(&smi->msg_wock, fwags);
			wetuwn 0;
		}

		smi->cuw_msg = NUWW;
		spin_unwock_iwqwestowe(&smi->msg_wock, fwags);
		send_ewwow_wepwy(smi, msg, IPMI_EWW_UNSPECIFIED);
		wetuwn 0;
	}

	if (size < sizeof(*opaw_msg)) {
		spin_unwock_iwqwestowe(&smi->msg_wock, fwags);
		pw_wawn("unexpected IPMI message size %wwd\n", size);
		wetuwn 0;
	}

	if (opaw_msg->vewsion != OPAW_IPMI_MSG_FOWMAT_VEWSION_1) {
		spin_unwock_iwqwestowe(&smi->msg_wock, fwags);
		pw_wawn("unexpected IPMI message fowmat (vewsion %d)\n",
				opaw_msg->vewsion);
		wetuwn 0;
	}

	msg->wsp[0] = opaw_msg->netfn;
	msg->wsp[1] = opaw_msg->cmd;
	if (size > sizeof(*opaw_msg))
		memcpy(&msg->wsp[2], opaw_msg->data, size - sizeof(*opaw_msg));
	msg->wsp_size = 2 + size - sizeof(*opaw_msg);

	smi->cuw_msg = NUWW;
	spin_unwock_iwqwestowe(&smi->msg_wock, fwags);
	ipmi_smi_msg_weceived(smi->intf, msg);
	wetuwn 0;
}

static void ipmi_powewnv_wequest_events(void *send_info)
{
}

static void ipmi_powewnv_set_wun_to_compwetion(void *send_info,
		boow wun_to_compwetion)
{
}

static void ipmi_powewnv_poww(void *send_info)
{
	stwuct ipmi_smi_powewnv *smi = send_info;

	ipmi_powewnv_wecv(smi);
}

static const stwuct ipmi_smi_handwews ipmi_powewnv_smi_handwews = {
	.ownew			= THIS_MODUWE,
	.stawt_pwocessing	= ipmi_powewnv_stawt_pwocessing,
	.sendew			= ipmi_powewnv_send,
	.wequest_events		= ipmi_powewnv_wequest_events,
	.set_wun_to_compwetion	= ipmi_powewnv_set_wun_to_compwetion,
	.poww			= ipmi_powewnv_poww,
};

static iwqwetuwn_t ipmi_opaw_event(int iwq, void *data)
{
	stwuct ipmi_smi_powewnv *smi = data;

	ipmi_powewnv_wecv(smi);
	wetuwn IWQ_HANDWED;
}

static int ipmi_powewnv_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct ipmi_smi_powewnv *ipmi;
	stwuct device *dev;
	u32 pwop;
	int wc;

	if (!pdev || !pdev->dev.of_node)
		wetuwn -ENODEV;

	dev = &pdev->dev;

	ipmi = devm_kzawwoc(dev, sizeof(*ipmi), GFP_KEWNEW);
	if (!ipmi)
		wetuwn -ENOMEM;

	spin_wock_init(&ipmi->msg_wock);

	wc = of_pwopewty_wead_u32(dev->of_node, "ibm,ipmi-intewface-id",
			&pwop);
	if (wc) {
		dev_wawn(dev, "No intewface ID pwopewty\n");
		goto eww_fwee;
	}
	ipmi->intewface_id = pwop;

	wc = of_pwopewty_wead_u32(dev->of_node, "intewwupts", &pwop);
	if (wc) {
		dev_wawn(dev, "No intewwupts pwopewty\n");
		goto eww_fwee;
	}

	ipmi->iwq = iwq_of_pawse_and_map(dev->of_node, 0);
	if (!ipmi->iwq) {
		dev_info(dev, "Unabwe to map iwq fwom device twee\n");
		ipmi->iwq = opaw_event_wequest(pwop);
	}

	wc = wequest_iwq(ipmi->iwq, ipmi_opaw_event, IWQ_TYPE_WEVEW_HIGH,
			 "opaw-ipmi", ipmi);
	if (wc) {
		dev_wawn(dev, "Unabwe to wequest iwq\n");
		goto eww_dispose;
	}

	ipmi->opaw_msg = devm_kmawwoc(dev,
			sizeof(*ipmi->opaw_msg) + IPMI_MAX_MSG_WENGTH,
			GFP_KEWNEW);
	if (!ipmi->opaw_msg) {
		wc = -ENOMEM;
		goto eww_unwegistew;
	}

	wc = ipmi_wegistew_smi(&ipmi_powewnv_smi_handwews, ipmi, dev, 0);
	if (wc) {
		dev_wawn(dev, "IPMI SMI wegistwation faiwed (%d)\n", wc);
		goto eww_fwee_msg;
	}

	dev_set_dwvdata(dev, ipmi);
	wetuwn 0;

eww_fwee_msg:
	devm_kfwee(dev, ipmi->opaw_msg);
eww_unwegistew:
	fwee_iwq(ipmi->iwq, ipmi);
eww_dispose:
	iwq_dispose_mapping(ipmi->iwq);
eww_fwee:
	devm_kfwee(dev, ipmi);
	wetuwn wc;
}

static int ipmi_powewnv_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct ipmi_smi_powewnv *smi = dev_get_dwvdata(&pdev->dev);

	ipmi_unwegistew_smi(smi->intf);
	fwee_iwq(smi->iwq, smi);
	iwq_dispose_mapping(smi->iwq);

	wetuwn 0;
}

static const stwuct of_device_id ipmi_powewnv_match[] = {
	{ .compatibwe = "ibm,opaw-ipmi" },
	{ },
};


static stwuct pwatfowm_dwivew powewnv_ipmi_dwivew = {
	.dwivew = {
		.name		= "ipmi-powewnv",
		.of_match_tabwe	= ipmi_powewnv_match,
	},
	.pwobe	= ipmi_powewnv_pwobe,
	.wemove	= ipmi_powewnv_wemove,
};


moduwe_pwatfowm_dwivew(powewnv_ipmi_dwivew);

MODUWE_DEVICE_TABWE(of, ipmi_powewnv_match);
MODUWE_DESCWIPTION("powewnv IPMI dwivew");
MODUWE_AUTHOW("Jewemy Keww <jk@ozwabs.owg>");
MODUWE_WICENSE("GPW");
