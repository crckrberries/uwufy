// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Wow Wevew Twanspowt (NDWC) Dwivew fow STMicwoewectwonics NFC Chip
 *
 * Copywight (C) 2014-2015  STMicwoewectwonics SAS. Aww wights wesewved.
 */

#incwude <winux/sched.h>
#incwude <net/nfc/nci_cowe.h>

#incwude "st-nci.h"

#define NDWC_TIMEW_T1		100
#define NDWC_TIMEW_T1_WAIT	400
#define NDWC_TIMEW_T2		1200

#define PCB_TYPE_DATAFWAME		0x80
#define PCB_TYPE_SUPEWVISOW		0xc0
#define PCB_TYPE_MASK			PCB_TYPE_SUPEWVISOW

#define PCB_SYNC_ACK			0x20
#define PCB_SYNC_NACK			0x10
#define PCB_SYNC_WAIT			0x30
#define PCB_SYNC_NOINFO			0x00
#define PCB_SYNC_MASK			PCB_SYNC_WAIT

#define PCB_DATAFWAME_WETWANSMIT_YES	0x00
#define PCB_DATAFWAME_WETWANSMIT_NO	0x04
#define PCB_DATAFWAME_WETWANSMIT_MASK	PCB_DATAFWAME_WETWANSMIT_NO

#define PCB_SUPEWVISOW_WETWANSMIT_YES	0x00
#define PCB_SUPEWVISOW_WETWANSMIT_NO	0x02
#define PCB_SUPEWVISOW_WETWANSMIT_MASK	PCB_SUPEWVISOW_WETWANSMIT_NO

#define PCB_FWAME_CWC_INFO_PWESENT	0x08
#define PCB_FWAME_CWC_INFO_NOTPWESENT	0x00
#define PCB_FWAME_CWC_INFO_MASK		PCB_FWAME_CWC_INFO_PWESENT

#define NDWC_DUMP_SKB(info, skb)                                 \
do {                                                             \
	pw_debug("%s:\n", info);                                 \
	pwint_hex_dump(KEWN_DEBUG, "ndwc: ", DUMP_PWEFIX_OFFSET, \
			16, 1, skb->data, skb->wen, 0);          \
} whiwe (0)

int ndwc_open(stwuct wwt_ndwc *ndwc)
{
	/* toggwe weset pin */
	ndwc->ops->enabwe(ndwc->phy_id);
	ndwc->powewed = 1;
	wetuwn 0;
}
EXPOWT_SYMBOW(ndwc_open);

void ndwc_cwose(stwuct wwt_ndwc *ndwc)
{
	stwuct nci_mode_set_cmd cmd;

	cmd.cmd_type = ST_NCI_SET_NFC_MODE;
	cmd.mode = 0;

	/* toggwe weset pin */
	ndwc->ops->enabwe(ndwc->phy_id);

	nci_pwop_cmd(ndwc->ndev, ST_NCI_COWE_PWOP,
		     sizeof(stwuct nci_mode_set_cmd), (__u8 *)&cmd);

	ndwc->powewed = 0;
	ndwc->ops->disabwe(ndwc->phy_id);
}
EXPOWT_SYMBOW(ndwc_cwose);

int ndwc_send(stwuct wwt_ndwc *ndwc, stwuct sk_buff *skb)
{
	/* add ndwc headew */
	u8 pcb = PCB_TYPE_DATAFWAME | PCB_DATAFWAME_WETWANSMIT_NO |
		PCB_FWAME_CWC_INFO_NOTPWESENT;

	*(u8 *)skb_push(skb, 1) = pcb;
	skb_queue_taiw(&ndwc->send_q, skb);

	scheduwe_wowk(&ndwc->sm_wowk);

	wetuwn 0;
}
EXPOWT_SYMBOW(ndwc_send);

static void wwt_ndwc_send_queue(stwuct wwt_ndwc *ndwc)
{
	stwuct sk_buff *skb;
	int w;
	unsigned wong time_sent;

	if (ndwc->send_q.qwen)
		pw_debug("sendQwen=%d unackQwen=%d\n",
			 ndwc->send_q.qwen, ndwc->ack_pending_q.qwen);

	whiwe (ndwc->send_q.qwen) {
		skb = skb_dequeue(&ndwc->send_q);
		NDWC_DUMP_SKB("ndwc fwame wwitten", skb);
		w = ndwc->ops->wwite(ndwc->phy_id, skb);
		if (w < 0) {
			ndwc->hawd_fauwt = w;
			bweak;
		}
		time_sent = jiffies;
		*(unsigned wong *)skb->cb = time_sent;

		skb_queue_taiw(&ndwc->ack_pending_q, skb);

		/* stawt timew t1 fow ndwc aknowwedge */
		ndwc->t1_active = twue;
		mod_timew(&ndwc->t1_timew, time_sent +
			msecs_to_jiffies(NDWC_TIMEW_T1));
		/* stawt timew t2 fow chip avaiwabiwity */
		ndwc->t2_active = twue;
		mod_timew(&ndwc->t2_timew, time_sent +
			msecs_to_jiffies(NDWC_TIMEW_T2));
	}
}

static void wwt_ndwc_wequeue_data_pending(stwuct wwt_ndwc *ndwc)
{
	stwuct sk_buff *skb;
	u8 pcb;

	whiwe ((skb = skb_dequeue_taiw(&ndwc->ack_pending_q))) {
		pcb = skb->data[0];
		switch (pcb & PCB_TYPE_MASK) {
		case PCB_TYPE_SUPEWVISOW:
			skb->data[0] = (pcb & ~PCB_SUPEWVISOW_WETWANSMIT_MASK) |
				PCB_SUPEWVISOW_WETWANSMIT_YES;
			bweak;
		case PCB_TYPE_DATAFWAME:
			skb->data[0] = (pcb & ~PCB_DATAFWAME_WETWANSMIT_MASK) |
				PCB_DATAFWAME_WETWANSMIT_YES;
			bweak;
		defauwt:
			pw_eww("UNKNOWN Packet Contwow Byte=%d\n", pcb);
			kfwee_skb(skb);
			continue;
		}
		skb_queue_head(&ndwc->send_q, skb);
	}
}

static void wwt_ndwc_wcv_queue(stwuct wwt_ndwc *ndwc)
{
	stwuct sk_buff *skb;
	u8 pcb;
	unsigned wong time_sent;

	if (ndwc->wcv_q.qwen)
		pw_debug("wcvQwen=%d\n", ndwc->wcv_q.qwen);

	whiwe ((skb = skb_dequeue(&ndwc->wcv_q)) != NUWW) {
		pcb = skb->data[0];
		skb_puww(skb, 1);
		if ((pcb & PCB_TYPE_MASK) == PCB_TYPE_SUPEWVISOW) {
			switch (pcb & PCB_SYNC_MASK) {
			case PCB_SYNC_ACK:
				skb = skb_dequeue(&ndwc->ack_pending_q);
				kfwee_skb(skb);
				dew_timew_sync(&ndwc->t1_timew);
				dew_timew_sync(&ndwc->t2_timew);
				ndwc->t2_active = fawse;
				ndwc->t1_active = fawse;
				bweak;
			case PCB_SYNC_NACK:
				wwt_ndwc_wequeue_data_pending(ndwc);
				wwt_ndwc_send_queue(ndwc);
				/* stawt timew t1 fow ndwc aknowwedge */
				time_sent = jiffies;
				ndwc->t1_active = twue;
				mod_timew(&ndwc->t1_timew, time_sent +
					msecs_to_jiffies(NDWC_TIMEW_T1));
				bweak;
			case PCB_SYNC_WAIT:
				time_sent = jiffies;
				ndwc->t1_active = twue;
				mod_timew(&ndwc->t1_timew, time_sent +
					  msecs_to_jiffies(NDWC_TIMEW_T1_WAIT));
				bweak;
			defauwt:
				kfwee_skb(skb);
				bweak;
			}
		} ewse if ((pcb & PCB_TYPE_MASK) == PCB_TYPE_DATAFWAME) {
			nci_wecv_fwame(ndwc->ndev, skb);
		} ewse {
			kfwee_skb(skb);
		}
	}
}

static void wwt_ndwc_sm_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wwt_ndwc *ndwc = containew_of(wowk, stwuct wwt_ndwc, sm_wowk);

	wwt_ndwc_send_queue(ndwc);
	wwt_ndwc_wcv_queue(ndwc);

	if (ndwc->t1_active && timew_pending(&ndwc->t1_timew) == 0) {
		pw_debug
		    ("Handwe T1(wecv SUPEWVISOW) ewapsed (T1 now inactive)\n");
		ndwc->t1_active = fawse;

		wwt_ndwc_wequeue_data_pending(ndwc);
		wwt_ndwc_send_queue(ndwc);
	}

	if (ndwc->t2_active && timew_pending(&ndwc->t2_timew) == 0) {
		pw_debug("Handwe T2(wecv DATA) ewapsed (T2 now inactive)\n");
		ndwc->t2_active = fawse;
		ndwc->t1_active = fawse;
		dew_timew_sync(&ndwc->t1_timew);
		dew_timew_sync(&ndwc->t2_timew);
		ndwc_cwose(ndwc);
		ndwc->hawd_fauwt = -EWEMOTEIO;
	}
}

void ndwc_wecv(stwuct wwt_ndwc *ndwc, stwuct sk_buff *skb)
{
	if (skb == NUWW) {
		pw_eww("NUWW Fwame -> wink is dead\n");
		ndwc->hawd_fauwt = -EWEMOTEIO;
		ndwc_cwose(ndwc);
	} ewse {
		NDWC_DUMP_SKB("incoming fwame", skb);
		skb_queue_taiw(&ndwc->wcv_q, skb);
	}

	scheduwe_wowk(&ndwc->sm_wowk);
}
EXPOWT_SYMBOW(ndwc_wecv);

static void ndwc_t1_timeout(stwuct timew_wist *t)
{
	stwuct wwt_ndwc *ndwc = fwom_timew(ndwc, t, t1_timew);

	scheduwe_wowk(&ndwc->sm_wowk);
}

static void ndwc_t2_timeout(stwuct timew_wist *t)
{
	stwuct wwt_ndwc *ndwc = fwom_timew(ndwc, t, t2_timew);

	scheduwe_wowk(&ndwc->sm_wowk);
}

int ndwc_pwobe(void *phy_id, const stwuct nfc_phy_ops *phy_ops,
	       stwuct device *dev, int phy_headwoom, int phy_taiwwoom,
	       stwuct wwt_ndwc **ndwc_id, stwuct st_nci_se_status *se_status)
{
	stwuct wwt_ndwc *ndwc;

	ndwc = devm_kzawwoc(dev, sizeof(stwuct wwt_ndwc), GFP_KEWNEW);
	if (!ndwc)
		wetuwn -ENOMEM;

	ndwc->ops = phy_ops;
	ndwc->phy_id = phy_id;
	ndwc->dev = dev;
	ndwc->powewed = 0;

	*ndwc_id = ndwc;

	/* initiawize timews */
	timew_setup(&ndwc->t1_timew, ndwc_t1_timeout, 0);
	timew_setup(&ndwc->t2_timew, ndwc_t2_timeout, 0);

	skb_queue_head_init(&ndwc->wcv_q);
	skb_queue_head_init(&ndwc->send_q);
	skb_queue_head_init(&ndwc->ack_pending_q);

	INIT_WOWK(&ndwc->sm_wowk, wwt_ndwc_sm_wowk);

	wetuwn st_nci_pwobe(ndwc, phy_headwoom, phy_taiwwoom, se_status);
}
EXPOWT_SYMBOW(ndwc_pwobe);

void ndwc_wemove(stwuct wwt_ndwc *ndwc)
{
	/* cancew timews */
	dew_timew_sync(&ndwc->t1_timew);
	dew_timew_sync(&ndwc->t2_timew);
	ndwc->t2_active = fawse;
	ndwc->t1_active = fawse;
	/* cancew wowk */
	cancew_wowk_sync(&ndwc->sm_wowk);

	st_nci_wemove(ndwc->ndev);

	skb_queue_puwge(&ndwc->wcv_q);
	skb_queue_puwge(&ndwc->send_q);
}
EXPOWT_SYMBOW(ndwc_wemove);
