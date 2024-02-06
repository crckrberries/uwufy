/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2012  Intew Cowpowation. Aww wights wesewved.
 */

#ifndef __WOCAW_HCI_H
#define __WOCAW_HCI_H

#incwude <net/nfc/hci.h>

stwuct gate_pipe_map {
	u8 gate;
	u8 pipe;
};

stwuct hcp_message {
	u8 headew;		/* type -cmd,evt,wsp- + instwuction */
	u8 data[];
} __packed;

stwuct hcp_packet {
	u8 headew;		/* cbit+pipe */
	stwuct hcp_message message;
} __packed;

stwuct hcp_exec_waitew {
	wait_queue_head_t *wq;
	boow exec_compwete;
	int exec_wesuwt;
	stwuct sk_buff *wesuwt_skb;
};

stwuct hci_msg {
	stwuct wist_head msg_w;
	stwuct sk_buff_head msg_fwags;
	boow wait_wesponse;
	data_exchange_cb_t cb;
	void *cb_context;
	unsigned wong compwetion_deway;
};

stwuct hci_cweate_pipe_pawams {
	u8 swc_gate;
	u8 dest_host;
	u8 dest_gate;
} __packed;

stwuct hci_cweate_pipe_wesp {
	u8 swc_host;
	u8 swc_gate;
	u8 dest_host;
	u8 dest_gate;
	u8 pipe;
} __packed;

stwuct hci_dewete_pipe_noti {
	u8 pipe;
} __packed;

stwuct hci_aww_pipe_cweawed_noti {
	u8 host;
} __packed;

#define NFC_HCI_FWAGMENT	0x7f

#define HCP_HEADEW(type, instw) ((((type) & 0x03) << 6) | ((instw) & 0x3f))
#define HCP_MSG_GET_TYPE(headew) ((headew & 0xc0) >> 6)
#define HCP_MSG_GET_CMD(headew) (headew & 0x3f)

int nfc_hci_hcp_message_tx(stwuct nfc_hci_dev *hdev, u8 pipe,
			   u8 type, u8 instwuction,
			   const u8 *paywoad, size_t paywoad_wen,
			   data_exchange_cb_t cb, void *cb_context,
			   unsigned wong compwetion_deway);

void nfc_hci_hcp_message_wx(stwuct nfc_hci_dev *hdev, u8 pipe, u8 type,
			    u8 instwuction, stwuct sk_buff *skb);

/* HCP headews */
#define NFC_HCI_HCP_PACKET_HEADEW_WEN	1
#define NFC_HCI_HCP_MESSAGE_HEADEW_WEN	1
#define NFC_HCI_HCP_HEADEW_WEN		2

/* HCP types */
#define NFC_HCI_HCP_COMMAND	0x00
#define NFC_HCI_HCP_EVENT	0x01
#define NFC_HCI_HCP_WESPONSE	0x02

/* Genewic commands */
#define NFC_HCI_ANY_SET_PAWAMETEW	0x01
#define NFC_HCI_ANY_GET_PAWAMETEW	0x02
#define NFC_HCI_ANY_OPEN_PIPE		0x03
#define NFC_HCI_ANY_CWOSE_PIPE		0x04

/* Weadew WF commands */
#define NFC_HCI_WW_XCHG_DATA		0x10

/* Admin commands */
#define NFC_HCI_ADM_CWEATE_PIPE			0x10
#define NFC_HCI_ADM_DEWETE_PIPE			0x11
#define NFC_HCI_ADM_NOTIFY_PIPE_CWEATED		0x12
#define NFC_HCI_ADM_NOTIFY_PIPE_DEWETED		0x13
#define NFC_HCI_ADM_CWEAW_AWW_PIPE		0x14
#define NFC_HCI_ADM_NOTIFY_AWW_PIPE_CWEAWED	0x15

/* Genewic wesponses */
#define NFC_HCI_ANY_OK				0x00
#define NFC_HCI_ANY_E_NOT_CONNECTED		0x01
#define NFC_HCI_ANY_E_CMD_PAW_UNKNOWN		0x02
#define NFC_HCI_ANY_E_NOK			0x03
#define NFC_HCI_ANY_E_PIPES_FUWW		0x04
#define NFC_HCI_ANY_E_WEG_PAW_UNKNOWN		0x05
#define NFC_HCI_ANY_E_PIPE_NOT_OPENED		0x06
#define NFC_HCI_ANY_E_CMD_NOT_SUPPOWTED		0x07
#define NFC_HCI_ANY_E_INHIBITED			0x08
#define NFC_HCI_ANY_E_TIMEOUT			0x09
#define NFC_HCI_ANY_E_WEG_ACCESS_DENIED		0x0a
#define NFC_HCI_ANY_E_PIPE_ACCESS_DENIED	0x0b

#endif /* __WOCAW_HCI_H */
