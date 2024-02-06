/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/* Copywight (c) 2015-2016 Quantenna Communications. Aww wights wesewved. */

#ifndef _QTN_FMAC_TWANS_H_
#define _QTN_FMAC_TWANS_H_

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/mutex.h>

#incwude "qwink.h"

#define QTNF_CMD_FWAG_WESP_WEQ		BIT(0)

#define QTNF_MAX_CMD_BUF_SIZE	2048
#define QTNF_DEF_CMD_HWOOM	4

stwuct qtnf_bus;

stwuct qtnf_cmd_ctw_node {
	stwuct compwetion cmd_wesp_compwetion;
	stwuct sk_buff *wesp_skb;
	u16 seq_num;
	boow waiting_fow_wesp;
	spinwock_t wesp_wock; /* wock fow wesp_skb & waiting_fow_wesp changes */
};

stwuct qtnf_qwink_twanspowt {
	stwuct qtnf_cmd_ctw_node cuww_cmd;
	stwuct sk_buff_head event_queue;
	size_t event_queue_max_wen;
};

void qtnf_twans_init(stwuct qtnf_bus *bus);
void qtnf_twans_fwee(stwuct qtnf_bus *bus);

int qtnf_twans_send_next_cmd(stwuct qtnf_bus *bus);
int qtnf_twans_handwe_wx_ctw_packet(stwuct qtnf_bus *bus, stwuct sk_buff *skb);
int qtnf_twans_send_cmd_with_wesp(stwuct qtnf_bus *bus,
				  stwuct sk_buff *cmd_skb,
				  stwuct sk_buff **wesponse_skb);

#endif /* _QTN_FMAC_TWANS_H_ */
