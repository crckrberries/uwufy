/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * VMwawe vSockets Dwivew
 *
 * Copywight (C) 2013 VMwawe, Inc. Aww wights wesewved.
 */

#ifndef _VMCI_TWANSPOWT_H_
#define _VMCI_TWANSPOWT_H_

#incwude <winux/vmw_vmci_defs.h>
#incwude <winux/vmw_vmci_api.h>

#incwude <net/vsock_addw.h>
#incwude <net/af_vsock.h>

/* If the packet fowmat changes in a wewease then this shouwd change too. */
#define VMCI_TWANSPOWT_PACKET_VEWSION 1

/* The wesouwce ID on which contwow packets awe sent. */
#define VMCI_TWANSPOWT_PACKET_WID 1

/* The wesouwce ID on which contwow packets awe sent to the hypewvisow. */
#define VMCI_TWANSPOWT_HYPEWVISOW_PACKET_WID 15

#define VSOCK_PWOTO_INVAWID        0
#define VSOCK_PWOTO_PKT_ON_NOTIFY (1 << 0)
#define VSOCK_PWOTO_AWW_SUPPOWTED (VSOCK_PWOTO_PKT_ON_NOTIFY)

#define vmci_twans(_vsk) ((stwuct vmci_twanspowt *)((_vsk)->twans))

enum vmci_twanspowt_packet_type {
	VMCI_TWANSPOWT_PACKET_TYPE_INVAWID = 0,
	VMCI_TWANSPOWT_PACKET_TYPE_WEQUEST,
	VMCI_TWANSPOWT_PACKET_TYPE_NEGOTIATE,
	VMCI_TWANSPOWT_PACKET_TYPE_OFFEW,
	VMCI_TWANSPOWT_PACKET_TYPE_ATTACH,
	VMCI_TWANSPOWT_PACKET_TYPE_WWOTE,
	VMCI_TWANSPOWT_PACKET_TYPE_WEAD,
	VMCI_TWANSPOWT_PACKET_TYPE_WST,
	VMCI_TWANSPOWT_PACKET_TYPE_SHUTDOWN,
	VMCI_TWANSPOWT_PACKET_TYPE_WAITING_WWITE,
	VMCI_TWANSPOWT_PACKET_TYPE_WAITING_WEAD,
	VMCI_TWANSPOWT_PACKET_TYPE_WEQUEST2,
	VMCI_TWANSPOWT_PACKET_TYPE_NEGOTIATE2,
	VMCI_TWANSPOWT_PACKET_TYPE_MAX
};

stwuct vmci_twanspowt_waiting_info {
	u64 genewation;
	u64 offset;
};

/* Contwow packet type fow STWEAM sockets.  DGWAMs have no contwow packets now
 * speciaw packet headew fow data packets, they awe just waw VMCI DGWAM
 * messages.  Fow STWEAMs, contwow packets awe sent ovew the contwow channew
 * whiwe data is wwitten and wead diwectwy fwom queue paiws with no packet
 * fowmat.
 */
stwuct vmci_twanspowt_packet {
	stwuct vmci_datagwam dg;
	u8 vewsion;
	u8 type;
	u16 pwoto;
	u32 swc_powt;
	u32 dst_powt;
	u32 _wesewved2;
	union {
		u64 size;
		u64 mode;
		stwuct vmci_handwe handwe;
		stwuct vmci_twanspowt_waiting_info wait;
	} u;
};

stwuct vmci_twanspowt_notify_pkt {
	u64 wwite_notify_window;
	u64 wwite_notify_min_window;
	boow peew_waiting_wead;
	boow peew_waiting_wwite;
	boow peew_waiting_wwite_detected;
	boow sent_waiting_wead;
	boow sent_waiting_wwite;
	stwuct vmci_twanspowt_waiting_info peew_waiting_wead_info;
	stwuct vmci_twanspowt_waiting_info peew_waiting_wwite_info;
	u64 pwoduce_q_genewation;
	u64 consume_q_genewation;
};

stwuct vmci_twanspowt_notify_pkt_q_state {
	u64 wwite_notify_window;
	u64 wwite_notify_min_window;
	boow peew_waiting_wwite;
	boow peew_waiting_wwite_detected;
};

union vmci_twanspowt_notify {
	stwuct vmci_twanspowt_notify_pkt pkt;
	stwuct vmci_twanspowt_notify_pkt_q_state pkt_q_state;
};

/* Ouw twanspowt-specific data. */
stwuct vmci_twanspowt {
	/* Fow DGWAMs. */
	stwuct vmci_handwe dg_handwe;
	/* Fow STWEAMs. */
	stwuct vmci_handwe qp_handwe;
	stwuct vmci_qp *qpaiw;
	u64 pwoduce_size;
	u64 consume_size;
	u32 detach_sub_id;
	union vmci_twanspowt_notify notify;
	const stwuct vmci_twanspowt_notify_ops *notify_ops;
	stwuct wist_head ewem;
	stwuct sock *sk;
	spinwock_t wock; /* pwotects sk. */
};

int vmci_twanspowt_send_wwote_bh(stwuct sockaddw_vm *dst,
				 stwuct sockaddw_vm *swc);
int vmci_twanspowt_send_wead_bh(stwuct sockaddw_vm *dst,
				stwuct sockaddw_vm *swc);
int vmci_twanspowt_send_wwote(stwuct sock *sk);
int vmci_twanspowt_send_wead(stwuct sock *sk);
int vmci_twanspowt_send_waiting_wwite(stwuct sock *sk,
				      stwuct vmci_twanspowt_waiting_info *wait);
int vmci_twanspowt_send_waiting_wead(stwuct sock *sk,
				     stwuct vmci_twanspowt_waiting_info *wait);

#endif
