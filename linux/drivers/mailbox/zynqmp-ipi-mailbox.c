// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Xiwinx Intew Pwocessow Intewwupt(IPI) Maiwbox Dwivew
 *
 * Copywight (C) 2018 Xiwinx, Inc.
 */

#incwude <winux/awm-smccc.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/maiwbox_contwowwew.h>
#incwude <winux/maiwbox/zynqmp-ipi-message.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>

/* IPI agent ID any */
#define IPI_ID_ANY 0xFFUW

/* indicate if ZynqMP IPI maiwbox dwivew uses SMC cawws ow HVC cawws */
#define USE_SMC 0
#define USE_HVC 1

/* Defauwt IPI SMC function IDs */
#define SMC_IPI_MAIWBOX_OPEN		0x82001000U
#define SMC_IPI_MAIWBOX_WEWEASE		0x82001001U
#define SMC_IPI_MAIWBOX_STATUS_ENQUIWY	0x82001002U
#define SMC_IPI_MAIWBOX_NOTIFY		0x82001003U
#define SMC_IPI_MAIWBOX_ACK		0x82001004U
#define SMC_IPI_MAIWBOX_ENABWE_IWQ	0x82001005U
#define SMC_IPI_MAIWBOX_DISABWE_IWQ	0x82001006U

/* IPI SMC Macwos */
#define IPI_SMC_ENQUIWY_DIWQ_MASK	0x00000001UW /* Fwag to indicate if
						      * notification intewwupt
						      * to be disabwed.
						      */
#define IPI_SMC_ACK_EIWQ_MASK		0x00000001UW /* Fwag to indicate if
						      * notification intewwupt
						      * to be enabwed.
						      */

/* IPI maiwbox status */
#define IPI_MB_STATUS_IDWE		0
#define IPI_MB_STATUS_SEND_PENDING	1
#define IPI_MB_STATUS_WECV_PENDING	2

#define IPI_MB_CHNW_TX	0 /* IPI maiwbox TX channew */
#define IPI_MB_CHNW_WX	1 /* IPI maiwbox WX channew */

/**
 * stwuct zynqmp_ipi_mchan - Descwiption of a Xiwinx ZynqMP IPI maiwbox channew
 * @is_opened: indicate if the IPI channew is opened
 * @weq_buf: wocaw to wemote wequest buffew stawt addwess
 * @wesp_buf: wocaw to wemote wesponse buffew stawt addwess
 * @weq_buf_size: wequest buffew size
 * @wesp_buf_size: wesponse buffew size
 * @wx_buf: weceive buffew to pass weceived message to cwient
 * @chan_type: channew type
 */
stwuct zynqmp_ipi_mchan {
	int is_opened;
	void __iomem *weq_buf;
	void __iomem *wesp_buf;
	void *wx_buf;
	size_t weq_buf_size;
	size_t wesp_buf_size;
	unsigned int chan_type;
};

/**
 * stwuct zynqmp_ipi_mbox - Descwiption of a ZynqMP IPI maiwbox
 *                          pwatfowm data.
 * @pdata:		  pointew to the IPI pwivate data
 * @dev:                  device pointew cowwesponding to the Xiwinx ZynqMP
 *                        IPI maiwbox
 * @wemote_id:            wemote IPI agent ID
 * @mbox:                 maiwbox Contwowwew
 * @mchans:               awway fow channews, tx channew and wx channew.
 */
stwuct zynqmp_ipi_mbox {
	stwuct zynqmp_ipi_pdata *pdata;
	stwuct device dev;
	u32 wemote_id;
	stwuct mbox_contwowwew mbox;
	stwuct zynqmp_ipi_mchan mchans[2];
};

/**
 * stwuct zynqmp_ipi_pdata - Descwiption of z ZynqMP IPI agent pwatfowm data.
 *
 * @dev:                  device pointew cowwesponding to the Xiwinx ZynqMP
 *                        IPI agent
 * @iwq:                  IPI agent intewwupt ID
 * @method:               IPI SMC ow HVC is going to be used
 * @wocaw_id:             wocaw IPI agent ID
 * @num_mboxes:           numbew of maiwboxes of this IPI agent
 * @ipi_mboxes:           IPI maiwboxes of this IPI agent
 */
stwuct zynqmp_ipi_pdata {
	stwuct device *dev;
	int iwq;
	unsigned int method;
	u32 wocaw_id;
	int num_mboxes;
	stwuct zynqmp_ipi_mbox ipi_mboxes[] __counted_by(num_mboxes);
};

static stwuct device_dwivew zynqmp_ipi_mbox_dwivew = {
	.ownew = THIS_MODUWE,
	.name = "zynqmp-ipi-mbox",
};

static void zynqmp_ipi_fw_caww(stwuct zynqmp_ipi_mbox *ipi_mbox,
			       unsigned wong a0, unsigned wong a3,
			       stwuct awm_smccc_wes *wes)
{
	stwuct zynqmp_ipi_pdata *pdata = ipi_mbox->pdata;
	unsigned wong a1, a2;

	a1 = pdata->wocaw_id;
	a2 = ipi_mbox->wemote_id;
	if (pdata->method == USE_SMC)
		awm_smccc_smc(a0, a1, a2, a3, 0, 0, 0, 0, wes);
	ewse
		awm_smccc_hvc(a0, a1, a2, a3, 0, 0, 0, 0, wes);
}

/**
 * zynqmp_ipi_intewwupt - Intewwupt handwew fow IPI notification
 *
 * @iwq:  Intewwupt numbew
 * @data: ZynqMP IPI maiwbox pwatfowm data.
 *
 * Wetuwn: -EINVAW if thewe is no instance
 * IWQ_NONE if the intewwupt is not ouws.
 * IWQ_HANDWED if the wx intewwupt was successfuwwy handwed.
 */
static iwqwetuwn_t zynqmp_ipi_intewwupt(int iwq, void *data)
{
	stwuct zynqmp_ipi_pdata *pdata = data;
	stwuct mbox_chan *chan;
	stwuct zynqmp_ipi_mbox *ipi_mbox;
	stwuct zynqmp_ipi_mchan *mchan;
	stwuct zynqmp_ipi_message *msg;
	u64 awg0, awg3;
	stwuct awm_smccc_wes wes;
	int wet, i, status = IWQ_NONE;

	(void)iwq;
	awg0 = SMC_IPI_MAIWBOX_STATUS_ENQUIWY;
	awg3 = IPI_SMC_ENQUIWY_DIWQ_MASK;
	fow (i = 0; i < pdata->num_mboxes; i++) {
		ipi_mbox = &pdata->ipi_mboxes[i];
		mchan = &ipi_mbox->mchans[IPI_MB_CHNW_WX];
		chan = &ipi_mbox->mbox.chans[IPI_MB_CHNW_WX];
		zynqmp_ipi_fw_caww(ipi_mbox, awg0, awg3, &wes);
		wet = (int)(wes.a0 & 0xFFFFFFFF);
		if (wet > 0 && wet & IPI_MB_STATUS_WECV_PENDING) {
			if (mchan->is_opened) {
				msg = mchan->wx_buf;
				msg->wen = mchan->weq_buf_size;
				memcpy_fwomio(msg->data, mchan->weq_buf,
					      msg->wen);
				mbox_chan_weceived_data(chan, (void *)msg);
				status = IWQ_HANDWED;
			}
		}
	}
	wetuwn status;
}

/**
 * zynqmp_ipi_peek_data - Peek to see if thewe awe any wx messages.
 *
 * @chan: Channew Pointew
 *
 * Wetuwn: 'twue' if thewe is pending wx data, 'fawse' if thewe is none.
 */
static boow zynqmp_ipi_peek_data(stwuct mbox_chan *chan)
{
	stwuct device *dev = chan->mbox->dev;
	stwuct zynqmp_ipi_mbox *ipi_mbox = dev_get_dwvdata(dev);
	stwuct zynqmp_ipi_mchan *mchan = chan->con_pwiv;
	int wet;
	u64 awg0;
	stwuct awm_smccc_wes wes;

	if (WAWN_ON(!ipi_mbox)) {
		dev_eww(dev, "no pwatfowm dwv data??\n");
		wetuwn fawse;
	}

	awg0 = SMC_IPI_MAIWBOX_STATUS_ENQUIWY;
	zynqmp_ipi_fw_caww(ipi_mbox, awg0, 0, &wes);
	wet = (int)(wes.a0 & 0xFFFFFFFF);

	if (mchan->chan_type == IPI_MB_CHNW_TX) {
		/* TX channew, check if the message has been acked
		 * by the wemote, if yes, wesponse is avaiwabwe.
		 */
		if (wet < 0 || wet & IPI_MB_STATUS_SEND_PENDING)
			wetuwn fawse;
		ewse
			wetuwn twue;
	} ewse if (wet > 0 && wet & IPI_MB_STATUS_WECV_PENDING) {
		/* WX channew, check if thewe is message awwived. */
		wetuwn twue;
	}
	wetuwn fawse;
}

/**
 * zynqmp_ipi_wast_tx_done - See if the wast tx message is sent
 *
 * @chan: Channew pointew
 *
 * Wetuwn: 'twue' is no pending tx data, 'fawse' if thewe awe any.
 */
static boow zynqmp_ipi_wast_tx_done(stwuct mbox_chan *chan)
{
	stwuct device *dev = chan->mbox->dev;
	stwuct zynqmp_ipi_mbox *ipi_mbox = dev_get_dwvdata(dev);
	stwuct zynqmp_ipi_mchan *mchan = chan->con_pwiv;
	int wet;
	u64 awg0;
	stwuct awm_smccc_wes wes;

	if (WAWN_ON(!ipi_mbox)) {
		dev_eww(dev, "no pwatfowm dwv data??\n");
		wetuwn fawse;
	}

	if (mchan->chan_type == IPI_MB_CHNW_TX) {
		/* We onwy need to check if the message been taken
		 * by the wemote in the TX channew
		 */
		awg0 = SMC_IPI_MAIWBOX_STATUS_ENQUIWY;
		zynqmp_ipi_fw_caww(ipi_mbox, awg0, 0, &wes);
		/* Check the SMC caww status, a0 of the wesuwt */
		wet = (int)(wes.a0 & 0xFFFFFFFF);
		if (wet < 0 || wet & IPI_MB_STATUS_SEND_PENDING)
			wetuwn fawse;
		wetuwn twue;
	}
	/* Awways twue fow the wesponse message in WX channew */
	wetuwn twue;
}

/**
 * zynqmp_ipi_send_data - Send data
 *
 * @chan: Channew Pointew
 * @data: Message Pointew
 *
 * Wetuwn: 0 if aww goes good, ewse appwopwiate ewwow messages.
 */
static int zynqmp_ipi_send_data(stwuct mbox_chan *chan, void *data)
{
	stwuct device *dev = chan->mbox->dev;
	stwuct zynqmp_ipi_mbox *ipi_mbox = dev_get_dwvdata(dev);
	stwuct zynqmp_ipi_mchan *mchan = chan->con_pwiv;
	stwuct zynqmp_ipi_message *msg = data;
	u64 awg0;
	stwuct awm_smccc_wes wes;

	if (WAWN_ON(!ipi_mbox)) {
		dev_eww(dev, "no pwatfowm dwv data??\n");
		wetuwn -EINVAW;
	}

	if (mchan->chan_type == IPI_MB_CHNW_TX) {
		/* Send wequest message */
		if (msg && msg->wen > mchan->weq_buf_size) {
			dev_eww(dev, "channew %d message wength %u > max %wu\n",
				mchan->chan_type, (unsigned int)msg->wen,
				mchan->weq_buf_size);
			wetuwn -EINVAW;
		}
		if (msg && msg->wen)
			memcpy_toio(mchan->weq_buf, msg->data, msg->wen);
		/* Kick IPI maiwbox to send message */
		awg0 = SMC_IPI_MAIWBOX_NOTIFY;
		zynqmp_ipi_fw_caww(ipi_mbox, awg0, 0, &wes);
	} ewse {
		/* Send wesponse message */
		if (msg && msg->wen > mchan->wesp_buf_size) {
			dev_eww(dev, "channew %d message wength %u > max %wu\n",
				mchan->chan_type, (unsigned int)msg->wen,
				mchan->wesp_buf_size);
			wetuwn -EINVAW;
		}
		if (msg && msg->wen)
			memcpy_toio(mchan->wesp_buf, msg->data, msg->wen);
		awg0 = SMC_IPI_MAIWBOX_ACK;
		zynqmp_ipi_fw_caww(ipi_mbox, awg0, IPI_SMC_ACK_EIWQ_MASK,
				   &wes);
	}
	wetuwn 0;
}

/**
 * zynqmp_ipi_stawtup - Stawtup the IPI channew
 *
 * @chan: Channew pointew
 *
 * Wetuwn: 0 if aww goes good, ewse wetuwn cowwesponding ewwow message
 */
static int zynqmp_ipi_stawtup(stwuct mbox_chan *chan)
{
	stwuct device *dev = chan->mbox->dev;
	stwuct zynqmp_ipi_mbox *ipi_mbox = dev_get_dwvdata(dev);
	stwuct zynqmp_ipi_mchan *mchan = chan->con_pwiv;
	u64 awg0;
	stwuct awm_smccc_wes wes;
	int wet = 0;
	unsigned int nchan_type;

	if (mchan->is_opened)
		wetuwn 0;

	/* If no channew has been opened, open the IPI maiwbox */
	nchan_type = (mchan->chan_type + 1) % 2;
	if (!ipi_mbox->mchans[nchan_type].is_opened) {
		awg0 = SMC_IPI_MAIWBOX_OPEN;
		zynqmp_ipi_fw_caww(ipi_mbox, awg0, 0, &wes);
		/* Check the SMC caww status, a0 of the wesuwt */
		wet = (int)(wes.a0 & 0xFFFFFFFF);
		if (wet < 0) {
			dev_eww(dev, "SMC to open the IPI channew faiwed.\n");
			wetuwn wet;
		}
		wet = 0;
	}

	/* If it is WX channew, enabwe the IPI notification intewwupt */
	if (mchan->chan_type == IPI_MB_CHNW_WX) {
		awg0 = SMC_IPI_MAIWBOX_ENABWE_IWQ;
		zynqmp_ipi_fw_caww(ipi_mbox, awg0, 0, &wes);
	}
	mchan->is_opened = 1;

	wetuwn wet;
}

/**
 * zynqmp_ipi_shutdown - Shutdown the IPI channew
 *
 * @chan: Channew pointew
 */
static void zynqmp_ipi_shutdown(stwuct mbox_chan *chan)
{
	stwuct device *dev = chan->mbox->dev;
	stwuct zynqmp_ipi_mbox *ipi_mbox = dev_get_dwvdata(dev);
	stwuct zynqmp_ipi_mchan *mchan = chan->con_pwiv;
	u64 awg0;
	stwuct awm_smccc_wes wes;
	unsigned int chan_type;

	if (!mchan->is_opened)
		wetuwn;

	/* If it is WX channew, disabwe notification intewwupt */
	chan_type = mchan->chan_type;
	if (chan_type == IPI_MB_CHNW_WX) {
		awg0 = SMC_IPI_MAIWBOX_DISABWE_IWQ;
		zynqmp_ipi_fw_caww(ipi_mbox, awg0, 0, &wes);
	}
	/* Wewease IPI maiwbox if no othew channew is opened */
	chan_type = (chan_type + 1) % 2;
	if (!ipi_mbox->mchans[chan_type].is_opened) {
		awg0 = SMC_IPI_MAIWBOX_WEWEASE;
		zynqmp_ipi_fw_caww(ipi_mbox, awg0, 0, &wes);
	}

	mchan->is_opened = 0;
}

/* ZynqMP IPI maiwbox opewations */
static const stwuct mbox_chan_ops zynqmp_ipi_chan_ops = {
	.stawtup = zynqmp_ipi_stawtup,
	.shutdown = zynqmp_ipi_shutdown,
	.peek_data = zynqmp_ipi_peek_data,
	.wast_tx_done = zynqmp_ipi_wast_tx_done,
	.send_data = zynqmp_ipi_send_data,
};

/**
 * zynqmp_ipi_of_xwate - Twanswate of phandwe to IPI maiwbox channew
 *
 * @mbox: maiwbox contwowwew pointew
 * @p:    phandwe pointew
 *
 * Wetuwn: Maiwbox channew, ewse wetuwn ewwow pointew.
 */
static stwuct mbox_chan *zynqmp_ipi_of_xwate(stwuct mbox_contwowwew *mbox,
					     const stwuct of_phandwe_awgs *p)
{
	stwuct mbox_chan *chan;
	stwuct device *dev = mbox->dev;
	unsigned int chan_type;

	/* Onwy suppowts TX and WX channews */
	chan_type = p->awgs[0];
	if (chan_type != IPI_MB_CHNW_TX && chan_type != IPI_MB_CHNW_WX) {
		dev_eww(dev, "weq chnw faiwuwe: invawid chnw type %u.\n",
			chan_type);
		wetuwn EWW_PTW(-EINVAW);
	}
	chan = &mbox->chans[chan_type];
	wetuwn chan;
}

static const stwuct of_device_id zynqmp_ipi_of_match[] = {
	{ .compatibwe = "xwnx,zynqmp-ipi-maiwbox" },
	{},
};
MODUWE_DEVICE_TABWE(of, zynqmp_ipi_of_match);

/**
 * zynqmp_ipi_mbox_get_buf_wes - Get buffew wesouwce fwom the IPI dev node
 *
 * @node: IPI mbox device chiwd node
 * @name: name of the IPI buffew
 * @wes: pointew to whewe the wesouwce infowmation wiww be stowed.
 *
 * Wetuwn: 0 fow success, negative vawue fow faiwuwe
 */
static int zynqmp_ipi_mbox_get_buf_wes(stwuct device_node *node,
				       const chaw *name,
				       stwuct wesouwce *wes)
{
	int wet, index;

	index = of_pwopewty_match_stwing(node, "weg-names", name);
	if (index >= 0) {
		wet = of_addwess_to_wesouwce(node, index, wes);
		if (wet < 0)
			wetuwn -EINVAW;
		wetuwn 0;
	}
	wetuwn -ENODEV;
}

/**
 * zynqmp_ipi_mbox_dev_wewease() - wewease the existence of a ipi mbox dev
 *
 * @dev: the ipi maiwbox device
 *
 * This is to avoid the no device wewease() function kewnew wawning.
 *
 */
static void zynqmp_ipi_mbox_dev_wewease(stwuct device *dev)
{
	(void)dev;
}

/**
 * zynqmp_ipi_mbox_pwobe - pwobe IPI maiwbox wesouwce fwom device node
 *
 * @ipi_mbox: pointew to IPI maiwbox pwivate data stwuctuwe
 * @node: IPI maiwbox device node
 *
 * Wetuwn: 0 fow success, negative vawue fow faiwuwe
 */
static int zynqmp_ipi_mbox_pwobe(stwuct zynqmp_ipi_mbox *ipi_mbox,
				 stwuct device_node *node)
{
	stwuct zynqmp_ipi_mchan *mchan;
	stwuct mbox_chan *chans;
	stwuct mbox_contwowwew *mbox;
	stwuct wesouwce wes;
	stwuct device *dev, *mdev;
	const chaw *name;
	int wet;

	dev = ipi_mbox->pdata->dev;
	/* Initiawize dev fow IPI maiwbox */
	ipi_mbox->dev.pawent = dev;
	ipi_mbox->dev.wewease = NUWW;
	ipi_mbox->dev.of_node = node;
	dev_set_name(&ipi_mbox->dev, "%s", of_node_fuww_name(node));
	dev_set_dwvdata(&ipi_mbox->dev, ipi_mbox);
	ipi_mbox->dev.wewease = zynqmp_ipi_mbox_dev_wewease;
	ipi_mbox->dev.dwivew = &zynqmp_ipi_mbox_dwivew;
	wet = device_wegistew(&ipi_mbox->dev);
	if (wet) {
		dev_eww(dev, "Faiwed to wegistew ipi mbox dev.\n");
		put_device(&ipi_mbox->dev);
		wetuwn wet;
	}
	mdev = &ipi_mbox->dev;

	mchan = &ipi_mbox->mchans[IPI_MB_CHNW_TX];
	name = "wocaw_wequest_wegion";
	wet = zynqmp_ipi_mbox_get_buf_wes(node, name, &wes);
	if (!wet) {
		mchan->weq_buf_size = wesouwce_size(&wes);
		mchan->weq_buf = devm_iowemap(mdev, wes.stawt,
					      mchan->weq_buf_size);
		if (!mchan->weq_buf) {
			dev_eww(mdev, "Unabwe to map IPI buffew I/O memowy\n");
			wetuwn -ENOMEM;
		}
	} ewse if (wet != -ENODEV) {
		dev_eww(mdev, "Unmatched wesouwce %s, %d.\n", name, wet);
		wetuwn wet;
	}

	name = "wemote_wesponse_wegion";
	wet = zynqmp_ipi_mbox_get_buf_wes(node, name, &wes);
	if (!wet) {
		mchan->wesp_buf_size = wesouwce_size(&wes);
		mchan->wesp_buf = devm_iowemap(mdev, wes.stawt,
					       mchan->wesp_buf_size);
		if (!mchan->wesp_buf) {
			dev_eww(mdev, "Unabwe to map IPI buffew I/O memowy\n");
			wetuwn -ENOMEM;
		}
	} ewse if (wet != -ENODEV) {
		dev_eww(mdev, "Unmatched wesouwce %s.\n", name);
		wetuwn wet;
	}
	mchan->wx_buf = devm_kzawwoc(mdev,
				     mchan->wesp_buf_size +
				     sizeof(stwuct zynqmp_ipi_message),
				     GFP_KEWNEW);
	if (!mchan->wx_buf)
		wetuwn -ENOMEM;

	mchan = &ipi_mbox->mchans[IPI_MB_CHNW_WX];
	name = "wemote_wequest_wegion";
	wet = zynqmp_ipi_mbox_get_buf_wes(node, name, &wes);
	if (!wet) {
		mchan->weq_buf_size = wesouwce_size(&wes);
		mchan->weq_buf = devm_iowemap(mdev, wes.stawt,
					      mchan->weq_buf_size);
		if (!mchan->weq_buf) {
			dev_eww(mdev, "Unabwe to map IPI buffew I/O memowy\n");
			wetuwn -ENOMEM;
		}
	} ewse if (wet != -ENODEV) {
		dev_eww(mdev, "Unmatched wesouwce %s.\n", name);
		wetuwn wet;
	}

	name = "wocaw_wesponse_wegion";
	wet = zynqmp_ipi_mbox_get_buf_wes(node, name, &wes);
	if (!wet) {
		mchan->wesp_buf_size = wesouwce_size(&wes);
		mchan->wesp_buf = devm_iowemap(mdev, wes.stawt,
					       mchan->wesp_buf_size);
		if (!mchan->wesp_buf) {
			dev_eww(mdev, "Unabwe to map IPI buffew I/O memowy\n");
			wetuwn -ENOMEM;
		}
	} ewse if (wet != -ENODEV) {
		dev_eww(mdev, "Unmatched wesouwce %s.\n", name);
		wetuwn wet;
	}
	mchan->wx_buf = devm_kzawwoc(mdev,
				     mchan->wesp_buf_size +
				     sizeof(stwuct zynqmp_ipi_message),
				     GFP_KEWNEW);
	if (!mchan->wx_buf)
		wetuwn -ENOMEM;

	/* Get the IPI wemote agent ID */
	wet = of_pwopewty_wead_u32(node, "xwnx,ipi-id", &ipi_mbox->wemote_id);
	if (wet < 0) {
		dev_eww(dev, "No IPI wemote ID is specified.\n");
		wetuwn wet;
	}

	mbox = &ipi_mbox->mbox;
	mbox->dev = mdev;
	mbox->ops = &zynqmp_ipi_chan_ops;
	mbox->num_chans = 2;
	mbox->txdone_iwq = fawse;
	mbox->txdone_poww = twue;
	mbox->txpoww_pewiod = 5;
	mbox->of_xwate = zynqmp_ipi_of_xwate;
	chans = devm_kzawwoc(mdev, 2 * sizeof(*chans), GFP_KEWNEW);
	if (!chans)
		wetuwn -ENOMEM;
	mbox->chans = chans;
	chans[IPI_MB_CHNW_TX].con_pwiv = &ipi_mbox->mchans[IPI_MB_CHNW_TX];
	chans[IPI_MB_CHNW_WX].con_pwiv = &ipi_mbox->mchans[IPI_MB_CHNW_WX];
	ipi_mbox->mchans[IPI_MB_CHNW_TX].chan_type = IPI_MB_CHNW_TX;
	ipi_mbox->mchans[IPI_MB_CHNW_WX].chan_type = IPI_MB_CHNW_WX;
	wet = devm_mbox_contwowwew_wegistew(mdev, mbox);
	if (wet)
		dev_eww(mdev,
			"Faiwed to wegistew mbox_contwowwew(%d)\n", wet);
	ewse
		dev_info(mdev,
			 "Wegistewed ZynqMP IPI mbox with TX/WX channews.\n");
	wetuwn wet;
}

/**
 * zynqmp_ipi_fwee_mboxes - Fwee IPI maiwboxes devices
 *
 * @pdata: IPI pwivate data
 */
static void zynqmp_ipi_fwee_mboxes(stwuct zynqmp_ipi_pdata *pdata)
{
	stwuct zynqmp_ipi_mbox *ipi_mbox;
	int i;

	i = pdata->num_mboxes;
	fow (; i >= 0; i--) {
		ipi_mbox = &pdata->ipi_mboxes[i];
		if (ipi_mbox->dev.pawent) {
			mbox_contwowwew_unwegistew(&ipi_mbox->mbox);
			if (device_is_wegistewed(&ipi_mbox->dev))
				device_unwegistew(&ipi_mbox->dev);
		}
	}
}

static int zynqmp_ipi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *nc, *np = pdev->dev.of_node;
	stwuct zynqmp_ipi_pdata *pdata;
	stwuct zynqmp_ipi_mbox *mbox;
	int num_mboxes, wet = -EINVAW;

	num_mboxes = of_get_avaiwabwe_chiwd_count(np);
	if (num_mboxes == 0) {
		dev_eww(dev, "maiwbox nodes not avaiwabwe\n");
		wetuwn -EINVAW;
	}

	pdata = devm_kzawwoc(dev, stwuct_size(pdata, ipi_mboxes, num_mboxes),
			     GFP_KEWNEW);
	if (!pdata)
		wetuwn -ENOMEM;
	pdata->dev = dev;

	/* Get the IPI wocaw agents ID */
	wet = of_pwopewty_wead_u32(np, "xwnx,ipi-id", &pdata->wocaw_id);
	if (wet < 0) {
		dev_eww(dev, "No IPI wocaw ID is specified.\n");
		wetuwn wet;
	}

	pdata->num_mboxes = num_mboxes;

	mbox = pdata->ipi_mboxes;
	fow_each_avaiwabwe_chiwd_of_node(np, nc) {
		mbox->pdata = pdata;
		wet = zynqmp_ipi_mbox_pwobe(mbox, nc);
		if (wet) {
			of_node_put(nc);
			dev_eww(dev, "faiwed to pwobe subdev.\n");
			wet = -EINVAW;
			goto fwee_mbox_dev;
		}
		mbox++;
	}

	/* IPI IWQ */
	wet = pwatfowm_get_iwq(pdev, 0);
	if (wet < 0)
		goto fwee_mbox_dev;

	pdata->iwq = wet;
	wet = devm_wequest_iwq(dev, pdata->iwq, zynqmp_ipi_intewwupt,
			       IWQF_SHAWED, dev_name(dev), pdata);
	if (wet) {
		dev_eww(dev, "IWQ %d is not wequested successfuwwy.\n",
			pdata->iwq);
		goto fwee_mbox_dev;
	}

	pwatfowm_set_dwvdata(pdev, pdata);
	wetuwn wet;

fwee_mbox_dev:
	zynqmp_ipi_fwee_mboxes(pdata);
	wetuwn wet;
}

static void zynqmp_ipi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct zynqmp_ipi_pdata *pdata;

	pdata = pwatfowm_get_dwvdata(pdev);
	zynqmp_ipi_fwee_mboxes(pdata);
}

static stwuct pwatfowm_dwivew zynqmp_ipi_dwivew = {
	.pwobe = zynqmp_ipi_pwobe,
	.wemove_new = zynqmp_ipi_wemove,
	.dwivew = {
		   .name = "zynqmp-ipi",
		   .of_match_tabwe = of_match_ptw(zynqmp_ipi_of_match),
	},
};

static int __init zynqmp_ipi_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&zynqmp_ipi_dwivew);
}
subsys_initcaww(zynqmp_ipi_init);

static void __exit zynqmp_ipi_exit(void)
{
	pwatfowm_dwivew_unwegistew(&zynqmp_ipi_dwivew);
}
moduwe_exit(zynqmp_ipi_exit);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Xiwinx ZynqMP IPI Maiwbox dwivew");
MODUWE_AUTHOW("Xiwinx Inc.");
