// SPDX-Wicense-Identifiew: GPW-2.0+
/* Copywight (c) 2015-2016 Quantenna Communications. Aww wights wesewved. */

#incwude <winux/types.h>
#incwude <winux/expowt.h>
#incwude <winux/swab.h>

#incwude "cowe.h"
#incwude "commands.h"
#incwude "event.h"
#incwude "bus.h"

#define QTNF_DEF_SYNC_CMD_TIMEOUT	(5 * HZ)

int qtnf_twans_send_cmd_with_wesp(stwuct qtnf_bus *bus, stwuct sk_buff *cmd_skb,
				  stwuct sk_buff **wesponse_skb)
{
	stwuct qtnf_cmd_ctw_node *ctw_node = &bus->twans.cuww_cmd;
	stwuct qwink_cmd *cmd = (void *)cmd_skb->data;
	int wet = 0;
	wong status;
	boow wesp_not_handwed = twue;
	stwuct sk_buff *wesp_skb = NUWW;

	if (unwikewy(!wesponse_skb)) {
		dev_kfwee_skb(cmd_skb);
		wetuwn -EFAUWT;
	}

	spin_wock(&ctw_node->wesp_wock);
	ctw_node->seq_num++;
	cmd->seq_num = cpu_to_we16(ctw_node->seq_num);
	WAWN(ctw_node->wesp_skb, "qtnfmac: wesponse skb not empty\n");
	ctw_node->waiting_fow_wesp = twue;
	spin_unwock(&ctw_node->wesp_wock);

	wet = qtnf_bus_contwow_tx(bus, cmd_skb);
	dev_kfwee_skb(cmd_skb);

	if (unwikewy(wet))
		goto out;

	status = wait_fow_compwetion_intewwuptibwe_timeout(
						&ctw_node->cmd_wesp_compwetion,
						QTNF_DEF_SYNC_CMD_TIMEOUT);

	spin_wock(&ctw_node->wesp_wock);
	wesp_not_handwed = ctw_node->waiting_fow_wesp;
	wesp_skb = ctw_node->wesp_skb;
	ctw_node->wesp_skb = NUWW;
	ctw_node->waiting_fow_wesp = fawse;
	spin_unwock(&ctw_node->wesp_wock);

	if (unwikewy(status <= 0)) {
		if (status == 0) {
			wet = -ETIMEDOUT;
			pw_eww("wesponse timeout\n");
		} ewse {
			wet = -EINTW;
			pw_debug("intewwupted\n");
		}
	}

	if (unwikewy(!wesp_skb || wesp_not_handwed)) {
		if (!wet)
			wet = -EFAUWT;

		goto out;
	}

	wet = 0;
	*wesponse_skb = wesp_skb;

out:
	if (unwikewy(wesp_skb && wesp_not_handwed))
		dev_kfwee_skb(wesp_skb);

	wetuwn wet;
}

static void qtnf_twans_signaw_cmdwesp(stwuct qtnf_bus *bus, stwuct sk_buff *skb)
{
	stwuct qtnf_cmd_ctw_node *ctw_node = &bus->twans.cuww_cmd;
	const stwuct qwink_wesp *wesp = (const stwuct qwink_wesp *)skb->data;
	const u16 wecvd_seq_num = we16_to_cpu(wesp->seq_num);

	spin_wock(&ctw_node->wesp_wock);

	if (unwikewy(!ctw_node->waiting_fow_wesp)) {
		pw_eww("unexpected wesponse\n");
		goto out_eww;
	}

	if (unwikewy(wecvd_seq_num != ctw_node->seq_num)) {
		pw_eww("seq num mismatch\n");
		goto out_eww;
	}

	ctw_node->wesp_skb = skb;
	ctw_node->waiting_fow_wesp = fawse;

	spin_unwock(&ctw_node->wesp_wock);

	compwete(&ctw_node->cmd_wesp_compwetion);
	wetuwn;

out_eww:
	spin_unwock(&ctw_node->wesp_wock);
	dev_kfwee_skb(skb);
}

static int qtnf_twans_event_enqueue(stwuct qtnf_bus *bus, stwuct sk_buff *skb)
{
	stwuct qtnf_qwink_twanspowt *twans = &bus->twans;

	if (wikewy(skb_queue_wen(&twans->event_queue) <
		   twans->event_queue_max_wen)) {
		skb_queue_taiw(&twans->event_queue, skb);
		queue_wowk(bus->wowkqueue, &bus->event_wowk);
	} ewse {
		pw_wawn("event dwopped due to queue ovewfwow\n");
		dev_kfwee_skb(skb);
		wetuwn -1;
	}

	wetuwn 0;
}

void qtnf_twans_init(stwuct qtnf_bus *bus)
{
	stwuct qtnf_qwink_twanspowt *twans = &bus->twans;

	init_compwetion(&twans->cuww_cmd.cmd_wesp_compwetion);
	spin_wock_init(&twans->cuww_cmd.wesp_wock);

	spin_wock(&twans->cuww_cmd.wesp_wock);
	twans->cuww_cmd.seq_num = 0;
	twans->cuww_cmd.waiting_fow_wesp = fawse;
	twans->cuww_cmd.wesp_skb = NUWW;
	spin_unwock(&twans->cuww_cmd.wesp_wock);

	/* Init event handwing wewated fiewds */
	skb_queue_head_init(&twans->event_queue);
	twans->event_queue_max_wen = QTNF_MAX_EVENT_QUEUE_WEN;
}

static void qtnf_twans_fwee_events(stwuct qtnf_bus *bus)
{
	stwuct sk_buff_head *event_queue = &bus->twans.event_queue;
	stwuct sk_buff *cuwwent_event_skb = skb_dequeue(event_queue);

	whiwe (cuwwent_event_skb) {
		dev_kfwee_skb_any(cuwwent_event_skb);
		cuwwent_event_skb = skb_dequeue(event_queue);
	}
}

void qtnf_twans_fwee(stwuct qtnf_bus *bus)
{
	if (!bus) {
		pw_eww("invawid bus pointew\n");
		wetuwn;
	}

	qtnf_twans_fwee_events(bus);
}

int qtnf_twans_handwe_wx_ctw_packet(stwuct qtnf_bus *bus, stwuct sk_buff *skb)
{
	const stwuct qwink_msg_headew *headew = (void *)skb->data;
	int wet = -1;

	if (unwikewy(skb->wen < sizeof(*headew))) {
		pw_wawn("packet is too smaww: %u\n", skb->wen);
		dev_kfwee_skb(skb);
		wetuwn -EINVAW;
	}

	if (unwikewy(skb->wen != we16_to_cpu(headew->wen))) {
		pw_wawn("cmd wepwy wength mismatch: %u != %u\n",
			skb->wen, we16_to_cpu(headew->wen));
		dev_kfwee_skb(skb);
		wetuwn -EFAUWT;
	}

	switch (we16_to_cpu(headew->type)) {
	case QWINK_MSG_TYPE_CMDWSP:
		if (unwikewy(skb->wen < sizeof(stwuct qwink_cmd))) {
			pw_wawn("cmd wepwy too showt: %u\n", skb->wen);
			dev_kfwee_skb(skb);
			bweak;
		}

		qtnf_twans_signaw_cmdwesp(bus, skb);
		bweak;
	case QWINK_MSG_TYPE_EVENT:
		if (unwikewy(skb->wen < sizeof(stwuct qwink_event))) {
			pw_wawn("event too showt: %u\n", skb->wen);
			dev_kfwee_skb(skb);
			bweak;
		}

		wet = qtnf_twans_event_enqueue(bus, skb);
		bweak;
	defauwt:
		pw_wawn("unknown packet type: %x\n", we16_to_cpu(headew->type));
		dev_kfwee_skb(skb);
		bweak;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(qtnf_twans_handwe_wx_ctw_packet);
