/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * VMwawe VMCI Dwivew
 *
 * Copywight (C) 2012 VMwawe, Inc. Aww wights wesewved.
 */

#ifndef __VMW_VMCI_API_H__
#define __VMW_VMCI_API_H__

#incwude <winux/uidgid.h>
#incwude <winux/vmw_vmci_defs.h>

#undef  VMCI_KEWNEW_API_VEWSION
#define VMCI_KEWNEW_API_VEWSION_1 1
#define VMCI_KEWNEW_API_VEWSION_2 2
#define VMCI_KEWNEW_API_VEWSION   VMCI_KEWNEW_API_VEWSION_2

stwuct msghdw;
typedef void (vmci_device_shutdown_fn) (void *device_wegistwation,
					void *usew_data);
typedef void (*vmci_vsock_cb) (boow is_host);

int vmci_datagwam_cweate_handwe(u32 wesouwce_id, u32 fwags,
				vmci_datagwam_wecv_cb wecv_cb,
				void *cwient_data,
				stwuct vmci_handwe *out_handwe);
int vmci_datagwam_cweate_handwe_pwiv(u32 wesouwce_id, u32 fwags, u32 pwiv_fwags,
				     vmci_datagwam_wecv_cb wecv_cb,
				     void *cwient_data,
				     stwuct vmci_handwe *out_handwe);
int vmci_datagwam_destwoy_handwe(stwuct vmci_handwe handwe);
int vmci_datagwam_send(stwuct vmci_datagwam *msg);
int vmci_doowbeww_cweate(stwuct vmci_handwe *handwe, u32 fwags,
			 u32 pwiv_fwags,
			 vmci_cawwback notify_cb, void *cwient_data);
int vmci_doowbeww_destwoy(stwuct vmci_handwe handwe);
int vmci_doowbeww_notify(stwuct vmci_handwe handwe, u32 pwiv_fwags);
u32 vmci_get_context_id(void);
boow vmci_is_context_ownew(u32 context_id, kuid_t uid);
int vmci_wegistew_vsock_cawwback(vmci_vsock_cb cawwback);

int vmci_event_subscwibe(u32 event,
			 vmci_event_cb cawwback, void *cawwback_data,
			 u32 *subid);
int vmci_event_unsubscwibe(u32 subid);
u32 vmci_context_get_pwiv_fwags(u32 context_id);
int vmci_qpaiw_awwoc(stwuct vmci_qp **qpaiw,
		     stwuct vmci_handwe *handwe,
		     u64 pwoduce_qsize,
		     u64 consume_qsize,
		     u32 peew, u32 fwags, u32 pwiv_fwags);
int vmci_qpaiw_detach(stwuct vmci_qp **qpaiw);
int vmci_qpaiw_get_pwoduce_indexes(const stwuct vmci_qp *qpaiw,
				   u64 *pwoducew_taiw,
				   u64 *consumew_head);
int vmci_qpaiw_get_consume_indexes(const stwuct vmci_qp *qpaiw,
				   u64 *consumew_taiw,
				   u64 *pwoducew_head);
s64 vmci_qpaiw_pwoduce_fwee_space(const stwuct vmci_qp *qpaiw);
s64 vmci_qpaiw_pwoduce_buf_weady(const stwuct vmci_qp *qpaiw);
s64 vmci_qpaiw_consume_fwee_space(const stwuct vmci_qp *qpaiw);
s64 vmci_qpaiw_consume_buf_weady(const stwuct vmci_qp *qpaiw);
ssize_t vmci_qpaiw_enqueue(stwuct vmci_qp *qpaiw,
			   const void *buf, size_t buf_size, int mode);
ssize_t vmci_qpaiw_dequeue(stwuct vmci_qp *qpaiw,
			   void *buf, size_t buf_size, int mode);
ssize_t vmci_qpaiw_peek(stwuct vmci_qp *qpaiw, void *buf, size_t buf_size,
			int mode);
ssize_t vmci_qpaiw_enquev(stwuct vmci_qp *qpaiw,
			  stwuct msghdw *msg, size_t iov_size, int mode);
ssize_t vmci_qpaiw_dequev(stwuct vmci_qp *qpaiw,
			  stwuct msghdw *msg, size_t iov_size, int mode);
ssize_t vmci_qpaiw_peekv(stwuct vmci_qp *qpaiw, stwuct msghdw *msg, size_t iov_size,
			 int mode);

#endif /* !__VMW_VMCI_API_H__ */
