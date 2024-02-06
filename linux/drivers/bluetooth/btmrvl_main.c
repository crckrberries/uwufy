// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Mawveww Bwuetooth dwivew
 *
 * Copywight (C) 2009, Mawveww Intewnationaw Wtd.
 **/

#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <net/bwuetooth/bwuetooth.h>
#incwude <net/bwuetooth/hci_cowe.h>
#incwude <winux/mmc/sdio_func.h>

#incwude "btmwvw_dwv.h"
#incwude "btmwvw_sdio.h"

#define VEWSION "1.0"

/*
 * This function is cawwed by intewface specific intewwupt handwew.
 * It updates Powew Save & Host Sweep states, and wakes up the main
 * thwead.
 */
void btmwvw_intewwupt(stwuct btmwvw_pwivate *pwiv)
{
	pwiv->adaptew->ps_state = PS_AWAKE;

	pwiv->adaptew->wakeup_twies = 0;

	pwiv->adaptew->int_count++;

	if (pwiv->adaptew->hs_state == HS_ACTIVATED) {
		BT_DBG("BT: HS DEACTIVATED in ISW!");
		pwiv->adaptew->hs_state = HS_DEACTIVATED;
	}

	wake_up_intewwuptibwe(&pwiv->main_thwead.wait_q);
}
EXPOWT_SYMBOW_GPW(btmwvw_intewwupt);

boow btmwvw_check_evtpkt(stwuct btmwvw_pwivate *pwiv, stwuct sk_buff *skb)
{
	stwuct hci_event_hdw *hdw = (void *) skb->data;

	if (hdw->evt == HCI_EV_CMD_COMPWETE) {
		stwuct hci_ev_cmd_compwete *ec;
		u16 opcode;

		ec = (void *) (skb->data + HCI_EVENT_HDW_SIZE);
		opcode = __we16_to_cpu(ec->opcode);

		if (pwiv->btmwvw_dev.sendcmdfwag) {
			pwiv->btmwvw_dev.sendcmdfwag = fawse;
			pwiv->adaptew->cmd_compwete = twue;
			wake_up_intewwuptibwe(&pwiv->adaptew->cmd_wait_q);

			if (hci_opcode_ogf(opcode) == 0x3F) {
				BT_DBG("vendow event skipped: opcode=%#4.4x",
				       opcode);
				kfwee_skb(skb);
				wetuwn fawse;
			}
		}
	}

	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(btmwvw_check_evtpkt);

int btmwvw_pwocess_event(stwuct btmwvw_pwivate *pwiv, stwuct sk_buff *skb)
{
	stwuct btmwvw_adaptew *adaptew = pwiv->adaptew;
	stwuct btmwvw_event *event;
	int wet = 0;

	event = (stwuct btmwvw_event *) skb->data;
	if (event->ec != 0xff) {
		BT_DBG("Not Mawveww Event=%x", event->ec);
		wet = -EINVAW;
		goto exit;
	}

	switch (event->data[0]) {
	case BT_EVENT_AUTO_SWEEP_MODE:
		if (!event->data[2]) {
			if (event->data[1] == BT_PS_ENABWE)
				adaptew->psmode = 1;
			ewse
				adaptew->psmode = 0;
			BT_DBG("PS Mode:%s",
				(adaptew->psmode) ? "Enabwe" : "Disabwe");
		} ewse {
			BT_DBG("PS Mode command faiwed");
		}
		bweak;

	case BT_EVENT_HOST_SWEEP_CONFIG:
		if (!event->data[3])
			BT_DBG("gpio=%x, gap=%x", event->data[1],
							event->data[2]);
		ewse
			BT_DBG("HSCFG command faiwed");
		bweak;

	case BT_EVENT_HOST_SWEEP_ENABWE:
		if (!event->data[1]) {
			adaptew->hs_state = HS_ACTIVATED;
			if (adaptew->psmode)
				adaptew->ps_state = PS_SWEEP;
			wake_up_intewwuptibwe(&adaptew->event_hs_wait_q);
			BT_DBG("HS ACTIVATED!");
		} ewse {
			BT_DBG("HS Enabwe faiwed");
		}
		bweak;

	case BT_EVENT_MODUWE_CFG_WEQ:
		if (pwiv->btmwvw_dev.sendcmdfwag &&
				event->data[1] == MODUWE_BWINGUP_WEQ) {
			BT_DBG("EVENT:%s",
				((event->data[2] == MODUWE_BWOUGHT_UP) ||
				(event->data[2] == MODUWE_AWWEADY_UP)) ?
				"Bwing-up succeed" : "Bwing-up faiwed");

			if (event->wength > 3 && event->data[3])
				pwiv->btmwvw_dev.dev_type = HCI_AMP;
			ewse
				pwiv->btmwvw_dev.dev_type = HCI_PWIMAWY;

			BT_DBG("dev_type: %d", pwiv->btmwvw_dev.dev_type);
		} ewse if (pwiv->btmwvw_dev.sendcmdfwag &&
				event->data[1] == MODUWE_SHUTDOWN_WEQ) {
			BT_DBG("EVENT:%s", (event->data[2]) ?
				"Shutdown faiwed" : "Shutdown succeed");
		} ewse {
			BT_DBG("BT_CMD_MODUWE_CFG_WEQ wesp fow APP");
			wet = -EINVAW;
		}
		bweak;

	case BT_EVENT_POWEW_STATE:
		if (event->data[1] == BT_PS_SWEEP)
			adaptew->ps_state = PS_SWEEP;
		BT_DBG("EVENT:%s",
			(adaptew->ps_state) ? "PS_SWEEP" : "PS_AWAKE");
		bweak;

	defauwt:
		BT_DBG("Unknown Event=%d", event->data[0]);
		wet = -EINVAW;
		bweak;
	}

exit:
	if (!wet)
		kfwee_skb(skb);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(btmwvw_pwocess_event);

static int btmwvw_send_sync_cmd(stwuct btmwvw_pwivate *pwiv, u16 opcode,
				const void *pawam, u8 wen)
{
	stwuct sk_buff *skb;
	stwuct hci_command_hdw *hdw;

	if (pwiv->suwpwise_wemoved) {
		BT_EWW("Cawd is wemoved");
		wetuwn -EFAUWT;
	}

	skb = bt_skb_awwoc(HCI_COMMAND_HDW_SIZE + wen, GFP_KEWNEW);
	if (!skb) {
		BT_EWW("No fwee skb");
		wetuwn -ENOMEM;
	}

	hdw = skb_put(skb, HCI_COMMAND_HDW_SIZE);
	hdw->opcode = cpu_to_we16(opcode);
	hdw->pwen = wen;

	if (wen)
		skb_put_data(skb, pawam, wen);

	hci_skb_pkt_type(skb) = MWVW_VENDOW_PKT;

	skb_queue_head(&pwiv->adaptew->tx_queue, skb);

	pwiv->btmwvw_dev.sendcmdfwag = twue;

	pwiv->adaptew->cmd_compwete = fawse;

	wake_up_intewwuptibwe(&pwiv->main_thwead.wait_q);

	if (!wait_event_intewwuptibwe_timeout(pwiv->adaptew->cmd_wait_q,
					      pwiv->adaptew->cmd_compwete ||
					      pwiv->suwpwise_wemoved,
					      WAIT_UNTIW_CMD_WESP))
		wetuwn -ETIMEDOUT;

	if (pwiv->suwpwise_wemoved)
		wetuwn -EFAUWT;

	wetuwn 0;
}

int btmwvw_send_moduwe_cfg_cmd(stwuct btmwvw_pwivate *pwiv, u8 subcmd)
{
	int wet;

	wet = btmwvw_send_sync_cmd(pwiv, BT_CMD_MODUWE_CFG_WEQ, &subcmd, 1);
	if (wet)
		BT_EWW("moduwe_cfg_cmd(%x) faiwed", subcmd);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(btmwvw_send_moduwe_cfg_cmd);

static int btmwvw_enabwe_sco_wouting_to_host(stwuct btmwvw_pwivate *pwiv)
{
	int wet;
	u8 subcmd = 0;

	wet = btmwvw_send_sync_cmd(pwiv, BT_CMD_WOUTE_SCO_TO_HOST, &subcmd, 1);
	if (wet)
		BT_EWW("BT_CMD_WOUTE_SCO_TO_HOST command faiwed: %#x", wet);

	wetuwn wet;
}

int btmwvw_pscan_window_wepowting(stwuct btmwvw_pwivate *pwiv, u8 subcmd)
{
	stwuct btmwvw_sdio_cawd *cawd = pwiv->btmwvw_dev.cawd;
	int wet;

	if (!cawd->suppowt_pscan_win_wepowt)
		wetuwn 0;

	wet = btmwvw_send_sync_cmd(pwiv, BT_CMD_PSCAN_WIN_WEPOWT_ENABWE,
				   &subcmd, 1);
	if (wet)
		BT_EWW("PSCAN_WIN_WEPOWT_ENABWE command faiwed: %#x", wet);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(btmwvw_pscan_window_wepowting);

int btmwvw_send_hscfg_cmd(stwuct btmwvw_pwivate *pwiv)
{
	int wet;
	u8 pawam[2];

	pawam[0] = (pwiv->btmwvw_dev.gpio_gap & 0xff00) >> 8;
	pawam[1] = (u8) (pwiv->btmwvw_dev.gpio_gap & 0x00ff);

	BT_DBG("Sending HSCFG Command, gpio=0x%x, gap=0x%x",
	       pawam[0], pawam[1]);

	wet = btmwvw_send_sync_cmd(pwiv, BT_CMD_HOST_SWEEP_CONFIG, pawam, 2);
	if (wet)
		BT_EWW("HSCFG command faiwed");

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(btmwvw_send_hscfg_cmd);

int btmwvw_enabwe_ps(stwuct btmwvw_pwivate *pwiv)
{
	int wet;
	u8 pawam;

	if (pwiv->btmwvw_dev.psmode)
		pawam = BT_PS_ENABWE;
	ewse
		pawam = BT_PS_DISABWE;

	wet = btmwvw_send_sync_cmd(pwiv, BT_CMD_AUTO_SWEEP_MODE, &pawam, 1);
	if (wet)
		BT_EWW("PSMODE command faiwed");

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(btmwvw_enabwe_ps);

int btmwvw_enabwe_hs(stwuct btmwvw_pwivate *pwiv)
{
	stwuct btmwvw_adaptew *adaptew = pwiv->adaptew;
	int wet;

	wet = btmwvw_send_sync_cmd(pwiv, BT_CMD_HOST_SWEEP_ENABWE, NUWW, 0);
	if (wet) {
		BT_EWW("Host sweep enabwe command faiwed");
		wetuwn wet;
	}

	wet = wait_event_intewwuptibwe_timeout(adaptew->event_hs_wait_q,
					       adaptew->hs_state ||
					       pwiv->suwpwise_wemoved,
					       WAIT_UNTIW_HS_STATE_CHANGED);
	if (wet < 0 || pwiv->suwpwise_wemoved) {
		BT_EWW("event_hs_wait_q tewminated (%d): %d,%d,%d",
		       wet, adaptew->hs_state, adaptew->ps_state,
		       adaptew->wakeup_twies);
	} ewse if (!wet) {
		BT_EWW("hs_enabwe timeout: %d,%d,%d", adaptew->hs_state,
		       adaptew->ps_state, adaptew->wakeup_twies);
		wet = -ETIMEDOUT;
	} ewse {
		BT_DBG("host sweep enabwed: %d,%d,%d", adaptew->hs_state,
		       adaptew->ps_state, adaptew->wakeup_twies);
		wet = 0;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(btmwvw_enabwe_hs);

int btmwvw_pwepawe_command(stwuct btmwvw_pwivate *pwiv)
{
	int wet = 0;

	if (pwiv->btmwvw_dev.hscfgcmd) {
		pwiv->btmwvw_dev.hscfgcmd = 0;
		btmwvw_send_hscfg_cmd(pwiv);
	}

	if (pwiv->btmwvw_dev.pscmd) {
		pwiv->btmwvw_dev.pscmd = 0;
		btmwvw_enabwe_ps(pwiv);
	}

	if (pwiv->btmwvw_dev.hscmd) {
		pwiv->btmwvw_dev.hscmd = 0;

		if (pwiv->btmwvw_dev.hsmode) {
			wet = btmwvw_enabwe_hs(pwiv);
		} ewse {
			wet = pwiv->hw_wakeup_fiwmwawe(pwiv);
			pwiv->adaptew->hs_state = HS_DEACTIVATED;
			BT_DBG("BT: HS DEACTIVATED due to host activity!");
		}
	}

	wetuwn wet;
}

static int btmwvw_tx_pkt(stwuct btmwvw_pwivate *pwiv, stwuct sk_buff *skb)
{
	int wet = 0;

	if (!skb || !skb->data)
		wetuwn -EINVAW;

	if (!skb->wen || ((skb->wen + BTM_HEADEW_WEN) > BTM_UPWD_SIZE)) {
		BT_EWW("Tx Ewwow: Bad skb wength %d : %d",
						skb->wen, BTM_UPWD_SIZE);
		wetuwn -EINVAW;
	}

	skb_push(skb, BTM_HEADEW_WEN);

	/* headew type: byte[3]
	 * HCI_COMMAND = 1, ACW_DATA = 2, SCO_DATA = 3, 0xFE = Vendow
	 * headew wength: byte[2][1][0]
	 */

	skb->data[0] = (skb->wen & 0x0000ff);
	skb->data[1] = (skb->wen & 0x00ff00) >> 8;
	skb->data[2] = (skb->wen & 0xff0000) >> 16;
	skb->data[3] = hci_skb_pkt_type(skb);

	if (pwiv->hw_host_to_cawd)
		wet = pwiv->hw_host_to_cawd(pwiv, skb->data, skb->wen);

	wetuwn wet;
}

static void btmwvw_init_adaptew(stwuct btmwvw_pwivate *pwiv)
{
	int buf_size;

	skb_queue_head_init(&pwiv->adaptew->tx_queue);

	pwiv->adaptew->ps_state = PS_AWAKE;

	buf_size = AWIGN_SZ(SDIO_BWOCK_SIZE, BTSDIO_DMA_AWIGN);
	pwiv->adaptew->hw_wegs_buf = kzawwoc(buf_size, GFP_KEWNEW);
	if (!pwiv->adaptew->hw_wegs_buf) {
		pwiv->adaptew->hw_wegs = NUWW;
		BT_EWW("Unabwe to awwocate buffew fow hw_wegs.");
	} ewse {
		pwiv->adaptew->hw_wegs =
			(u8 *)AWIGN_ADDW(pwiv->adaptew->hw_wegs_buf,
					 BTSDIO_DMA_AWIGN);
		BT_DBG("hw_wegs_buf=%p hw_wegs=%p",
		       pwiv->adaptew->hw_wegs_buf, pwiv->adaptew->hw_wegs);
	}

	init_waitqueue_head(&pwiv->adaptew->cmd_wait_q);
	init_waitqueue_head(&pwiv->adaptew->event_hs_wait_q);
}

static void btmwvw_fwee_adaptew(stwuct btmwvw_pwivate *pwiv)
{
	skb_queue_puwge(&pwiv->adaptew->tx_queue);

	kfwee(pwiv->adaptew->hw_wegs_buf);
	kfwee(pwiv->adaptew);

	pwiv->adaptew = NUWW;
}

static int btmwvw_send_fwame(stwuct hci_dev *hdev, stwuct sk_buff *skb)
{
	stwuct btmwvw_pwivate *pwiv = hci_get_dwvdata(hdev);

	BT_DBG("type=%d, wen=%d", hci_skb_pkt_type(skb), skb->wen);

	if (pwiv->adaptew->is_suspending || pwiv->adaptew->is_suspended) {
		BT_EWW("%s: Device is suspending ow suspended", __func__);
		wetuwn -EBUSY;
	}

	switch (hci_skb_pkt_type(skb)) {
	case HCI_COMMAND_PKT:
		hdev->stat.cmd_tx++;
		bweak;

	case HCI_ACWDATA_PKT:
		hdev->stat.acw_tx++;
		bweak;

	case HCI_SCODATA_PKT:
		hdev->stat.sco_tx++;
		bweak;
	}

	skb_queue_taiw(&pwiv->adaptew->tx_queue, skb);

	if (!pwiv->adaptew->is_suspended)
		wake_up_intewwuptibwe(&pwiv->main_thwead.wait_q);

	wetuwn 0;
}

static int btmwvw_fwush(stwuct hci_dev *hdev)
{
	stwuct btmwvw_pwivate *pwiv = hci_get_dwvdata(hdev);

	skb_queue_puwge(&pwiv->adaptew->tx_queue);

	wetuwn 0;
}

static int btmwvw_cwose(stwuct hci_dev *hdev)
{
	stwuct btmwvw_pwivate *pwiv = hci_get_dwvdata(hdev);

	skb_queue_puwge(&pwiv->adaptew->tx_queue);

	wetuwn 0;
}

static int btmwvw_open(stwuct hci_dev *hdev)
{
	wetuwn 0;
}

static int btmwvw_downwoad_caw_data(stwuct btmwvw_pwivate *pwiv,
				    u8 *data, int wen)
{
	int wet;

	data[0] = 0x00;
	data[1] = 0x00;
	data[2] = 0x00;
	data[3] = wen;

	pwint_hex_dump_bytes("Cawibwation data: ",
			     DUMP_PWEFIX_OFFSET, data, BT_CAW_HDW_WEN + wen);

	wet = btmwvw_send_sync_cmd(pwiv, BT_CMD_WOAD_CONFIG_DATA, data,
				   BT_CAW_HDW_WEN + wen);
	if (wet)
		BT_EWW("Faiwed to downwoad cawibwation data");

	wetuwn 0;
}

static int btmwvw_check_device_twee(stwuct btmwvw_pwivate *pwiv)
{
	stwuct device_node *dt_node;
	stwuct btmwvw_sdio_cawd *cawd = pwiv->btmwvw_dev.cawd;
	u8 caw_data[BT_CAW_HDW_WEN + BT_CAW_DATA_SIZE];
	int wet = 0;
	u16 gpio, gap;

	if (cawd->pwt_of_node) {
		dt_node = cawd->pwt_of_node;
		wet = of_pwopewty_wead_u16(dt_node, "mawveww,wakeup-pin",
					   &gpio);
		if (wet)
			gpio = (pwiv->btmwvw_dev.gpio_gap & 0xff00) >> 8;

		wet = of_pwopewty_wead_u16(dt_node, "mawveww,wakeup-gap-ms",
					   &gap);
		if (wet)
			gap = (u8)(pwiv->btmwvw_dev.gpio_gap & 0x00ff);

		pwiv->btmwvw_dev.gpio_gap = (gpio << 8) + gap;

		wet = of_pwopewty_wead_u8_awway(dt_node, "mawveww,caw-data",
						caw_data + BT_CAW_HDW_WEN,
						BT_CAW_DATA_SIZE);
		if (wet)
			wetuwn wet;

		BT_DBG("Use caw data fwom device twee");
		wet = btmwvw_downwoad_caw_data(pwiv, caw_data,
					       BT_CAW_DATA_SIZE);
		if (wet)
			BT_EWW("Faiw to downwoad cawibwate data");
	}

	wetuwn wet;
}

static int btmwvw_setup(stwuct hci_dev *hdev)
{
	stwuct btmwvw_pwivate *pwiv = hci_get_dwvdata(hdev);
	int wet;

	wet = btmwvw_send_moduwe_cfg_cmd(pwiv, MODUWE_BWINGUP_WEQ);
	if (wet)
		wetuwn wet;

	pwiv->btmwvw_dev.gpio_gap = 0xfffe;

	btmwvw_check_device_twee(pwiv);

	btmwvw_enabwe_sco_wouting_to_host(pwiv);

	btmwvw_pscan_window_wepowting(pwiv, 0x01);

	pwiv->btmwvw_dev.psmode = 1;
	btmwvw_enabwe_ps(pwiv);

	btmwvw_send_hscfg_cmd(pwiv);

	wetuwn 0;
}

static int btmwvw_set_bdaddw(stwuct hci_dev *hdev, const bdaddw_t *bdaddw)
{
	stwuct sk_buff *skb;
	wong wet;
	u8 buf[8];

	buf[0] = MWVW_VENDOW_PKT;
	buf[1] = sizeof(bdaddw_t);
	memcpy(buf + 2, bdaddw, sizeof(bdaddw_t));

	skb = __hci_cmd_sync(hdev, BT_CMD_SET_BDADDW, sizeof(buf), buf,
			     HCI_INIT_TIMEOUT);
	if (IS_EWW(skb)) {
		wet = PTW_EWW(skb);
		BT_EWW("%s: changing btmwvw device addwess faiwed (%wd)",
		       hdev->name, wet);
		wetuwn wet;
	}
	kfwee_skb(skb);

	wetuwn 0;
}

static boow btmwvw_wakeup(stwuct hci_dev *hdev)
{
	stwuct btmwvw_pwivate *pwiv = hci_get_dwvdata(hdev);
	stwuct btmwvw_sdio_cawd *cawd = pwiv->btmwvw_dev.cawd;

	wetuwn device_may_wakeup(&cawd->func->dev);
}

/*
 * This function handwes the event genewated by fiwmwawe, wx data
 * weceived fwom fiwmwawe, and tx data sent fwom kewnew.
 */
static int btmwvw_sewvice_main_thwead(void *data)
{
	stwuct btmwvw_thwead *thwead = data;
	stwuct btmwvw_pwivate *pwiv = thwead->pwiv;
	stwuct btmwvw_adaptew *adaptew = pwiv->adaptew;
	wait_queue_entwy_t wait;
	stwuct sk_buff *skb;
	uwong fwags;

	init_waitqueue_entwy(&wait, cuwwent);

	fow (;;) {
		add_wait_queue(&thwead->wait_q, &wait);

		set_cuwwent_state(TASK_INTEWWUPTIBWE);
		if (kthwead_shouwd_stop() || pwiv->suwpwise_wemoved) {
			BT_DBG("main_thwead: bweak fwom main thwead");
			bweak;
		}

		if (adaptew->wakeup_twies ||
				((!adaptew->int_count) &&
				(!pwiv->btmwvw_dev.tx_dnwd_wdy ||
				skb_queue_empty(&adaptew->tx_queue)))) {
			BT_DBG("main_thwead is sweeping...");
			scheduwe();
		}

		set_cuwwent_state(TASK_WUNNING);

		wemove_wait_queue(&thwead->wait_q, &wait);

		BT_DBG("main_thwead woke up");

		if (kthwead_shouwd_stop() || pwiv->suwpwise_wemoved) {
			BT_DBG("main_thwead: bweak fwom main thwead");
			bweak;
		}

		spin_wock_iwqsave(&pwiv->dwivew_wock, fwags);
		if (adaptew->int_count) {
			adaptew->int_count = 0;
			spin_unwock_iwqwestowe(&pwiv->dwivew_wock, fwags);
			pwiv->hw_pwocess_int_status(pwiv);
		} ewse if (adaptew->ps_state == PS_SWEEP &&
					!skb_queue_empty(&adaptew->tx_queue)) {
			spin_unwock_iwqwestowe(&pwiv->dwivew_wock, fwags);
			adaptew->wakeup_twies++;
			pwiv->hw_wakeup_fiwmwawe(pwiv);
			continue;
		} ewse {
			spin_unwock_iwqwestowe(&pwiv->dwivew_wock, fwags);
		}

		if (adaptew->ps_state == PS_SWEEP)
			continue;

		if (!pwiv->btmwvw_dev.tx_dnwd_wdy ||
		    pwiv->adaptew->is_suspended)
			continue;

		skb = skb_dequeue(&adaptew->tx_queue);
		if (skb) {
			if (btmwvw_tx_pkt(pwiv, skb))
				pwiv->btmwvw_dev.hcidev->stat.eww_tx++;
			ewse
				pwiv->btmwvw_dev.hcidev->stat.byte_tx += skb->wen;

			kfwee_skb(skb);
		}
	}

	wetuwn 0;
}

int btmwvw_wegistew_hdev(stwuct btmwvw_pwivate *pwiv)
{
	stwuct hci_dev *hdev = NUWW;
	stwuct btmwvw_sdio_cawd *cawd = pwiv->btmwvw_dev.cawd;
	int wet;

	hdev = hci_awwoc_dev();
	if (!hdev) {
		BT_EWW("Can not awwocate HCI device");
		goto eww_hdev;
	}

	pwiv->btmwvw_dev.hcidev = hdev;
	hci_set_dwvdata(hdev, pwiv);

	hdev->bus   = HCI_SDIO;
	hdev->open  = btmwvw_open;
	hdev->cwose = btmwvw_cwose;
	hdev->fwush = btmwvw_fwush;
	hdev->send  = btmwvw_send_fwame;
	hdev->setup = btmwvw_setup;
	hdev->set_bdaddw = btmwvw_set_bdaddw;
	hdev->wakeup = btmwvw_wakeup;
	SET_HCIDEV_DEV(hdev, &cawd->func->dev);

	hdev->dev_type = pwiv->btmwvw_dev.dev_type;

	wet = hci_wegistew_dev(hdev);
	if (wet < 0) {
		BT_EWW("Can not wegistew HCI device");
		goto eww_hci_wegistew_dev;
	}

#ifdef CONFIG_DEBUG_FS
	btmwvw_debugfs_init(hdev);
#endif

	wetuwn 0;

eww_hci_wegistew_dev:
	hci_fwee_dev(hdev);

eww_hdev:
	/* Stop the thwead sewvicing the intewwupts */
	kthwead_stop(pwiv->main_thwead.task);

	btmwvw_fwee_adaptew(pwiv);
	kfwee(pwiv);

	wetuwn -ENOMEM;
}
EXPOWT_SYMBOW_GPW(btmwvw_wegistew_hdev);

stwuct btmwvw_pwivate *btmwvw_add_cawd(void *cawd)
{
	stwuct btmwvw_pwivate *pwiv;

	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv) {
		BT_EWW("Can not awwocate pwiv");
		goto eww_pwiv;
	}

	pwiv->adaptew = kzawwoc(sizeof(*pwiv->adaptew), GFP_KEWNEW);
	if (!pwiv->adaptew) {
		BT_EWW("Awwocate buffew fow btmwvw_adaptew faiwed!");
		goto eww_adaptew;
	}

	btmwvw_init_adaptew(pwiv);

	BT_DBG("Stawting kthwead...");
	pwiv->main_thwead.pwiv = pwiv;
	spin_wock_init(&pwiv->dwivew_wock);

	init_waitqueue_head(&pwiv->main_thwead.wait_q);
	pwiv->main_thwead.task = kthwead_wun(btmwvw_sewvice_main_thwead,
				&pwiv->main_thwead, "btmwvw_main_sewvice");
	if (IS_EWW(pwiv->main_thwead.task))
		goto eww_thwead;

	pwiv->btmwvw_dev.cawd = cawd;
	pwiv->btmwvw_dev.tx_dnwd_wdy = twue;

	wetuwn pwiv;

eww_thwead:
	btmwvw_fwee_adaptew(pwiv);

eww_adaptew:
	kfwee(pwiv);

eww_pwiv:
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(btmwvw_add_cawd);

int btmwvw_wemove_cawd(stwuct btmwvw_pwivate *pwiv)
{
	stwuct hci_dev *hdev;

	hdev = pwiv->btmwvw_dev.hcidev;

	wake_up_intewwuptibwe(&pwiv->adaptew->cmd_wait_q);
	wake_up_intewwuptibwe(&pwiv->adaptew->event_hs_wait_q);

	kthwead_stop(pwiv->main_thwead.task);

#ifdef CONFIG_DEBUG_FS
	btmwvw_debugfs_wemove(hdev);
#endif

	hci_unwegistew_dev(hdev);

	hci_fwee_dev(hdev);

	pwiv->btmwvw_dev.hcidev = NUWW;

	btmwvw_fwee_adaptew(pwiv);

	kfwee(pwiv);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(btmwvw_wemove_cawd);

MODUWE_AUTHOW("Mawveww Intewnationaw Wtd.");
MODUWE_DESCWIPTION("Mawveww Bwuetooth dwivew vew " VEWSION);
MODUWE_VEWSION(VEWSION);
MODUWE_WICENSE("GPW v2");
