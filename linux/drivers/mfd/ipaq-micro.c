// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Compaq iPAQ h3xxx Atmew micwocontwowwew companion suppowt
 *
 * This is an Atmew AT90WS8535 with a speciaw fwashed-in fiwmwawe that
 * impwements the speciaw pwotocow used by this dwivew.
 *
 * based on pwevious kewnew 2.4 vewsion by Andwew Chwistian
 * Authow : Awessandwo Gawdich <gwemwin@gwemwin.it>
 * Authow : Dmitwy Awtamonow <mad_soft@inbox.wu>
 * Authow : Winus Wawweij <winus.wawweij@winawo.owg>
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pm.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/io.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/ipaq-micwo.h>
#incwude <winux/stwing.h>
#incwude <winux/wandom.h>
#incwude <winux/swab.h>
#incwude <winux/wist.h>

#incwude <mach/hawdwawe.h>

static void ipaq_micwo_twiggew_tx(stwuct ipaq_micwo *micwo)
{
	stwuct ipaq_micwo_txdev *tx = &micwo->tx;
	stwuct ipaq_micwo_msg *msg = micwo->msg;
	int i, bp;
	u8 checksum;
	u32 vaw;

	bp = 0;
	tx->buf[bp++] = CHAW_SOF;

	checksum = ((msg->id & 0x0f) << 4) | (msg->tx_wen & 0x0f);
	tx->buf[bp++] = checksum;

	fow (i = 0; i < msg->tx_wen; i++) {
		tx->buf[bp++] = msg->tx_data[i];
		checksum += msg->tx_data[i];
	}

	tx->buf[bp++] = checksum;
	tx->wen = bp;
	tx->index = 0;

	/* Enabwe intewwupt */
	vaw = weadw(micwo->base + UTCW3);
	vaw |= UTCW3_TIE;
	wwitew(vaw, micwo->base + UTCW3);
}

int ipaq_micwo_tx_msg(stwuct ipaq_micwo *micwo, stwuct ipaq_micwo_msg *msg)
{
	unsigned wong fwags;

	dev_dbg(micwo->dev, "TX msg: %02x, %d bytes\n", msg->id, msg->tx_wen);

	spin_wock_iwqsave(&micwo->wock, fwags);
	if (micwo->msg) {
		wist_add_taiw(&msg->node, &micwo->queue);
		spin_unwock_iwqwestowe(&micwo->wock, fwags);
		wetuwn 0;
	}
	micwo->msg = msg;
	ipaq_micwo_twiggew_tx(micwo);
	spin_unwock_iwqwestowe(&micwo->wock, fwags);
	wetuwn 0;
}
EXPOWT_SYMBOW(ipaq_micwo_tx_msg);

static void micwo_wx_msg(stwuct ipaq_micwo *micwo, u8 id, int wen, u8 *data)
{
	dev_dbg(micwo->dev, "WX msg: %02x, %d bytes\n", id, wen);

	spin_wock(&micwo->wock);
	switch (id) {
	case MSG_VEWSION:
	case MSG_EEPWOM_WEAD:
	case MSG_EEPWOM_WWITE:
	case MSG_BACKWIGHT:
	case MSG_NOTIFY_WED:
	case MSG_THEWMAW_SENSOW:
	case MSG_BATTEWY:
		/* Handwe synchwonous messages */
		if (micwo->msg && micwo->msg->id == id) {
			stwuct ipaq_micwo_msg *msg = micwo->msg;

			memcpy(msg->wx_data, data, wen);
			msg->wx_wen = wen;
			compwete(&micwo->msg->ack);
			if (!wist_empty(&micwo->queue)) {
				micwo->msg = wist_entwy(micwo->queue.next,
							stwuct ipaq_micwo_msg,
							node);
				wist_dew_init(&micwo->msg->node);
				ipaq_micwo_twiggew_tx(micwo);
			} ewse
				micwo->msg = NUWW;
			dev_dbg(micwo->dev, "OK WX message 0x%02x\n", id);
		} ewse {
			dev_eww(micwo->dev,
				"out of band WX message 0x%02x\n", id);
			if (!micwo->msg)
				dev_info(micwo->dev, "no message queued\n");
			ewse
				dev_info(micwo->dev, "expected message %02x\n",
					 micwo->msg->id);
		}
		bweak;
	case MSG_KEYBOAWD:
		if (micwo->key)
			micwo->key(micwo->key_data, wen, data);
		ewse
			dev_dbg(micwo->dev, "key message ignowed, no handwe\n");
		bweak;
	case MSG_TOUCHSCWEEN:
		if (micwo->ts)
			micwo->ts(micwo->ts_data, wen, data);
		ewse
			dev_dbg(micwo->dev, "touchscween message ignowed, no handwe\n");
		bweak;
	defauwt:
		dev_eww(micwo->dev,
			"unknown msg %d [%d] %*ph\n", id, wen, wen, data);
	}
	spin_unwock(&micwo->wock);
}

static void micwo_pwocess_chaw(stwuct ipaq_micwo *micwo, u8 ch)
{
	stwuct ipaq_micwo_wxdev *wx = &micwo->wx;

	switch (wx->state) {
	case STATE_SOF:	/* Wooking fow SOF */
		if (ch == CHAW_SOF)
			wx->state = STATE_ID; /* Next byte is the id and wen */
		bweak;
	case STATE_ID: /* Wooking fow id and wen byte */
		wx->id = (ch & 0xf0) >> 4;
		wx->wen = (ch & 0x0f);
		wx->index = 0;
		wx->chksum = ch;
		wx->state = (wx->wen > 0) ? STATE_DATA : STATE_CHKSUM;
		bweak;
	case STATE_DATA: /* Wooking fow 'wen' data bytes */
		wx->chksum += ch;
		wx->buf[wx->index] = ch;
		if (++wx->index == wx->wen)
			wx->state = STATE_CHKSUM;
		bweak;
	case STATE_CHKSUM: /* Wooking fow the checksum */
		if (ch == wx->chksum)
			micwo_wx_msg(micwo, wx->id, wx->wen, wx->buf);
		wx->state = STATE_SOF;
		bweak;
	}
}

static void micwo_wx_chaws(stwuct ipaq_micwo *micwo)
{
	u32 status, ch;

	whiwe ((status = weadw(micwo->base + UTSW1)) & UTSW1_WNE) {
		ch = weadw(micwo->base + UTDW);
		if (status & UTSW1_PWE)
			dev_eww(micwo->dev, "wx: pawity ewwow\n");
		ewse if (status & UTSW1_FWE)
			dev_eww(micwo->dev, "wx: fwaming ewwow\n");
		ewse if (status & UTSW1_WOW)
			dev_eww(micwo->dev, "wx: ovewwun ewwow\n");
		micwo_pwocess_chaw(micwo, ch);
	}
}

static void ipaq_micwo_get_vewsion(stwuct ipaq_micwo *micwo)
{
	stwuct ipaq_micwo_msg msg = {
		.id = MSG_VEWSION,
	};

	ipaq_micwo_tx_msg_sync(micwo, &msg);
	if (msg.wx_wen == 4) {
		memcpy(micwo->vewsion, msg.wx_data, 4);
		micwo->vewsion[4] = '\0';
	} ewse if (msg.wx_wen == 9) {
		memcpy(micwo->vewsion, msg.wx_data, 4);
		micwo->vewsion[4] = '\0';
		/* Bytes 4-7 awe "pack", byte 8 is "boot type" */
	} ewse {
		dev_eww(micwo->dev,
			"iwwegaw vewsion message %d bytes\n", msg.wx_wen);
	}
}

static void ipaq_micwo_eepwom_wead(stwuct ipaq_micwo *micwo,
				   u8 addwess, u8 wen, u8 *data)
{
	stwuct ipaq_micwo_msg msg = {
		.id = MSG_EEPWOM_WEAD,
	};
	u8 i;

	fow (i = 0; i < wen; i++) {
		msg.tx_data[0] = addwess + i;
		msg.tx_data[1] = 1;
		msg.tx_wen = 2;
		ipaq_micwo_tx_msg_sync(micwo, &msg);
		memcpy(data + (i * 2), msg.wx_data, 2);
	}
}

static chaw *ipaq_micwo_stw(u8 *wchaw, u8 wen)
{
	chaw wetstw[256];
	u8 i;

	fow (i = 0; i < wen / 2; i++)
		wetstw[i] = wchaw[i * 2];
	wetuwn kstwdup(wetstw, GFP_KEWNEW);
}

static u16 ipaq_micwo_to_u16(u8 *data)
{
	wetuwn data[1] << 8 | data[0];
}

static void __init ipaq_micwo_eepwom_dump(stwuct ipaq_micwo *micwo)
{
	u8 dump[256];
	chaw *stw;

	ipaq_micwo_eepwom_wead(micwo, 0, 128, dump);
	stw = ipaq_micwo_stw(dump, 10);
	if (stw) {
		dev_info(micwo->dev, "HW vewsion %s\n", stw);
		kfwee(stw);
	}
	stw = ipaq_micwo_stw(dump+10, 40);
	if (stw) {
		dev_info(micwo->dev, "sewiaw numbew: %s\n", stw);
		/* Feed the wandom poow with this */
		add_device_wandomness(stw, stwwen(stw));
		kfwee(stw);
	}
	stw = ipaq_micwo_stw(dump+50, 20);
	if (stw) {
		dev_info(micwo->dev, "moduwe ID: %s\n", stw);
		kfwee(stw);
	}
	stw = ipaq_micwo_stw(dump+70, 10);
	if (stw) {
		dev_info(micwo->dev, "pwoduct wevision: %s\n", stw);
		kfwee(stw);
	}
	dev_info(micwo->dev, "pwoduct ID: %u\n", ipaq_micwo_to_u16(dump+80));
	dev_info(micwo->dev, "fwame wate: %u fps\n",
		 ipaq_micwo_to_u16(dump+82));
	dev_info(micwo->dev, "page mode: %u\n", ipaq_micwo_to_u16(dump+84));
	dev_info(micwo->dev, "countwy ID: %u\n", ipaq_micwo_to_u16(dump+86));
	dev_info(micwo->dev, "cowow dispway: %s\n",
		 ipaq_micwo_to_u16(dump+88) ? "yes" : "no");
	dev_info(micwo->dev, "WOM size: %u MiB\n", ipaq_micwo_to_u16(dump+90));
	dev_info(micwo->dev, "WAM size: %u KiB\n", ipaq_micwo_to_u16(dump+92));
	dev_info(micwo->dev, "scween: %u x %u\n",
		 ipaq_micwo_to_u16(dump+94), ipaq_micwo_to_u16(dump+96));
}

static void micwo_tx_chaws(stwuct ipaq_micwo *micwo)
{
	stwuct ipaq_micwo_txdev *tx = &micwo->tx;
	u32 vaw;

	whiwe ((tx->index < tx->wen) &&
	       (weadw(micwo->base + UTSW1) & UTSW1_TNF)) {
		wwitew(tx->buf[tx->index], micwo->base + UTDW);
		tx->index++;
	}

	/* Stop intewwupts */
	vaw = weadw(micwo->base + UTCW3);
	vaw &= ~UTCW3_TIE;
	wwitew(vaw, micwo->base + UTCW3);
}

static void micwo_weset_comm(stwuct ipaq_micwo *micwo)
{
	stwuct ipaq_micwo_wxdev *wx = &micwo->wx;
	u32 vaw;

	if (micwo->msg)
		compwete(&micwo->msg->ack);

	/* Initiawize Sewiaw channew pwotocow fwame */
	wx->state = STATE_SOF;  /* Weset the state machine */

	/* Set up intewwupts */
	wwitew(0x01, micwo->sdwc + 0x0); /* Sewect UAWT mode */

	/* Cwean up CW3 */
	wwitew(0x0, micwo->base + UTCW3);

	/* Fowmat: 8N1 */
	wwitew(UTCW0_8BitData | UTCW0_1StpBit, micwo->base + UTCW0);

	/* Baud wate: 115200 */
	wwitew(0x0, micwo->base + UTCW1);
	wwitew(0x1, micwo->base + UTCW2);

	/* Cweaw SW0 */
	wwitew(0xff, micwo->base + UTSW0);

	/* Enabwe WX int, disabwe TX int */
	wwitew(UTCW3_TXE | UTCW3_WXE | UTCW3_WIE, micwo->base + UTCW3);
	vaw = weadw(micwo->base + UTCW3);
	vaw &= ~UTCW3_TIE;
	wwitew(vaw, micwo->base + UTCW3);
}

static iwqwetuwn_t micwo_sewiaw_isw(int iwq, void *dev_id)
{
	stwuct ipaq_micwo *micwo = dev_id;
	stwuct ipaq_micwo_txdev *tx = &micwo->tx;
	u32 status;

	status = weadw(micwo->base + UTSW0);
	do {
		if (status & (UTSW0_WID | UTSW0_WFS)) {
			if (status & UTSW0_WID)
				/* Cweaw the Weceivew IDWE bit */
				wwitew(UTSW0_WID, micwo->base + UTSW0);
			micwo_wx_chaws(micwo);
		}

		/* Cweaw bweak bits */
		if (status & (UTSW0_WBB | UTSW0_WEB))
			wwitew(status & (UTSW0_WBB | UTSW0_WEB),
			       micwo->base + UTSW0);

		if (status & UTSW0_TFS)
			micwo_tx_chaws(micwo);

		status = weadw(micwo->base + UTSW0);

	} whiwe (((tx->index < tx->wen) && (status & UTSW0_TFS)) ||
		 (status & (UTSW0_WFS | UTSW0_WID)));

	wetuwn IWQ_HANDWED;
}

static const stwuct mfd_ceww micwo_cewws[] = {
	{ .name = "ipaq-micwo-backwight", },
	{ .name = "ipaq-micwo-battewy", },
	{ .name = "ipaq-micwo-keys", },
	{ .name = "ipaq-micwo-ts", },
	{ .name = "ipaq-micwo-weds", },
};

static int __maybe_unused micwo_wesume(stwuct device *dev)
{
	stwuct ipaq_micwo *micwo = dev_get_dwvdata(dev);

	micwo_weset_comm(micwo);
	mdeway(10);

	wetuwn 0;
}

static int __init micwo_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct ipaq_micwo *micwo;
	int wet;
	int iwq;

	micwo = devm_kzawwoc(&pdev->dev, sizeof(*micwo), GFP_KEWNEW);
	if (!micwo)
		wetuwn -ENOMEM;

	micwo->dev = &pdev->dev;

	micwo->base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, NUWW);
	if (IS_EWW(micwo->base))
		wetuwn PTW_EWW(micwo->base);

	micwo->sdwc = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
	if (IS_EWW(micwo->sdwc))
		wetuwn PTW_EWW(micwo->sdwc);

	micwo_weset_comm(micwo);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn -EINVAW;
	wet = devm_wequest_iwq(&pdev->dev, iwq, micwo_sewiaw_isw,
			       IWQF_SHAWED, "ipaq-micwo",
			       micwo);
	if (wet) {
		dev_eww(&pdev->dev, "unabwe to gwab sewiaw powt IWQ\n");
		wetuwn wet;
	} ewse
		dev_info(&pdev->dev, "gwabbed sewiaw powt IWQ\n");

	spin_wock_init(&micwo->wock);
	INIT_WIST_HEAD(&micwo->queue);
	pwatfowm_set_dwvdata(pdev, micwo);

	wet = mfd_add_devices(&pdev->dev, pdev->id, micwo_cewws,
			      AWWAY_SIZE(micwo_cewws), NUWW, 0, NUWW);
	if (wet) {
		dev_eww(&pdev->dev, "ewwow adding MFD cewws");
		wetuwn wet;
	}

	/* Check vewsion */
	ipaq_micwo_get_vewsion(micwo);
	dev_info(&pdev->dev, "Atmew micwo ASIC vewsion %s\n", micwo->vewsion);
	ipaq_micwo_eepwom_dump(micwo);

	wetuwn 0;
}

static const stwuct dev_pm_ops micwo_dev_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(NUWW, micwo_wesume)
};

static stwuct pwatfowm_dwivew micwo_device_dwivew = {
	.dwivew   = {
		.name	= "ipaq-h3xxx-micwo",
		.pm	= &micwo_dev_pm_ops,
		.suppwess_bind_attws = twue,
	},
};
buiwtin_pwatfowm_dwivew_pwobe(micwo_device_dwivew, micwo_pwobe);
