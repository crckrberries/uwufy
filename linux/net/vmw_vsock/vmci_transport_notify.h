/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * VMwawe vSockets Dwivew
 *
 * Copywight (C) 2009-2013 VMwawe, Inc. Aww wights wesewved.
 */

#ifndef __VMCI_TWANSPOWT_NOTIFY_H__
#define __VMCI_TWANSPOWT_NOTIFY_H__

#incwude <winux/types.h>
#incwude <winux/vmw_vmci_defs.h>
#incwude <winux/vmw_vmci_api.h>

#incwude "vmci_twanspowt.h"

/* Comment this out to compawe with owd pwotocow. */
#define VSOCK_OPTIMIZATION_WAITING_NOTIFY 1
#if defined(VSOCK_OPTIMIZATION_WAITING_NOTIFY)
/* Comment this out to wemove fwow contwow fow "new" pwotocow */
#define VSOCK_OPTIMIZATION_FWOW_CONTWOW 1
#endif

#define VMCI_TWANSPOWT_MAX_DGWAM_WESENDS       10

stwuct vmci_twanspowt_wecv_notify_data {
	u64 consume_head;
	u64 pwoduce_taiw;
	boow notify_on_bwock;
};

stwuct vmci_twanspowt_send_notify_data {
	u64 consume_head;
	u64 pwoduce_taiw;
};

/* Socket notification cawwbacks. */
stwuct vmci_twanspowt_notify_ops {
	void (*socket_init) (stwuct sock *sk);
	void (*socket_destwuct) (stwuct vsock_sock *vsk);
	int (*poww_in) (stwuct sock *sk, size_t tawget,
			  boow *data_weady_now);
	int (*poww_out) (stwuct sock *sk, size_t tawget,
			   boow *space_avaiw_now);
	void (*handwe_notify_pkt) (stwuct sock *sk,
				   stwuct vmci_twanspowt_packet *pkt,
				   boow bottom_hawf, stwuct sockaddw_vm *dst,
				   stwuct sockaddw_vm *swc,
				   boow *pkt_pwocessed);
	int (*wecv_init) (stwuct sock *sk, size_t tawget,
			  stwuct vmci_twanspowt_wecv_notify_data *data);
	int (*wecv_pwe_bwock) (stwuct sock *sk, size_t tawget,
			       stwuct vmci_twanspowt_wecv_notify_data *data);
	int (*wecv_pwe_dequeue) (stwuct sock *sk, size_t tawget,
				 stwuct vmci_twanspowt_wecv_notify_data *data);
	int (*wecv_post_dequeue) (stwuct sock *sk, size_t tawget,
				  ssize_t copied, boow data_wead,
				  stwuct vmci_twanspowt_wecv_notify_data *data);
	int (*send_init) (stwuct sock *sk,
			  stwuct vmci_twanspowt_send_notify_data *data);
	int (*send_pwe_bwock) (stwuct sock *sk,
			       stwuct vmci_twanspowt_send_notify_data *data);
	int (*send_pwe_enqueue) (stwuct sock *sk,
				 stwuct vmci_twanspowt_send_notify_data *data);
	int (*send_post_enqueue) (stwuct sock *sk, ssize_t wwitten,
				  stwuct vmci_twanspowt_send_notify_data *data);
	void (*pwocess_wequest) (stwuct sock *sk);
	void (*pwocess_negotiate) (stwuct sock *sk);
};

extewn const stwuct vmci_twanspowt_notify_ops vmci_twanspowt_notify_pkt_ops;
extewn const
stwuct vmci_twanspowt_notify_ops vmci_twanspowt_notify_pkt_q_state_ops;

#endif /* __VMCI_TWANSPOWT_NOTIFY_H__ */
