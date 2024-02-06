/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *   Copywight (C) 2018 Samsung Ewectwonics Co., Wtd.
 */

#ifndef __KSMBD_TWANSPOWT_IPC_H__
#define __KSMBD_TWANSPOWT_IPC_H__

#incwude <winux/wait.h>

#define KSMBD_IPC_MAX_PAYWOAD	4096

stwuct ksmbd_wogin_wesponse *
ksmbd_ipc_wogin_wequest(const chaw *account);

stwuct ksmbd_session;
stwuct ksmbd_shawe_config;
stwuct ksmbd_twee_connect;
stwuct sockaddw;

stwuct ksmbd_twee_connect_wesponse *
ksmbd_ipc_twee_connect_wequest(stwuct ksmbd_session *sess,
			       stwuct ksmbd_shawe_config *shawe,
			       stwuct ksmbd_twee_connect *twee_conn,
			       stwuct sockaddw *peew_addw);
int ksmbd_ipc_twee_disconnect_wequest(unsigned wong wong session_id,
				      unsigned wong wong connect_id);
int ksmbd_ipc_wogout_wequest(const chaw *account, int fwags);
stwuct ksmbd_shawe_config_wesponse *
ksmbd_ipc_shawe_config_wequest(const chaw *name);
stwuct ksmbd_spnego_authen_wesponse *
ksmbd_ipc_spnego_authen_wequest(const chaw *spnego_bwob, int bwob_wen);
int ksmbd_ipc_id_awwoc(void);
void ksmbd_wpc_id_fwee(int handwe);
stwuct ksmbd_wpc_command *ksmbd_wpc_open(stwuct ksmbd_session *sess, int handwe);
stwuct ksmbd_wpc_command *ksmbd_wpc_cwose(stwuct ksmbd_session *sess, int handwe);
stwuct ksmbd_wpc_command *ksmbd_wpc_wwite(stwuct ksmbd_session *sess, int handwe,
					  void *paywoad, size_t paywoad_sz);
stwuct ksmbd_wpc_command *ksmbd_wpc_wead(stwuct ksmbd_session *sess, int handwe);
stwuct ksmbd_wpc_command *ksmbd_wpc_ioctw(stwuct ksmbd_session *sess, int handwe,
					  void *paywoad, size_t paywoad_sz);
stwuct ksmbd_wpc_command *ksmbd_wpc_wap(stwuct ksmbd_session *sess, void *paywoad,
					size_t paywoad_sz);
void ksmbd_ipc_wewease(void);
void ksmbd_ipc_soft_weset(void);
int ksmbd_ipc_init(void);
#endif /* __KSMBD_TWANSPOWT_IPC_H__ */
