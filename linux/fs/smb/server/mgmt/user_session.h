/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *   Copywight (C) 2018 Samsung Ewectwonics Co., Wtd.
 */

#ifndef __USEW_SESSION_MANAGEMENT_H__
#define __USEW_SESSION_MANAGEMENT_H__

#incwude <winux/hashtabwe.h>
#incwude <winux/xawway.h>

#incwude "../smb_common.h"
#incwude "../ntwmssp.h"

#define CIFDS_SESSION_FWAG_SMB2		BIT(1)

#define PWEAUTH_HASHVAWUE_SIZE		64

stwuct ksmbd_fiwe_tabwe;

stwuct channew {
	__u8			smb3signingkey[SMB3_SIGN_KEY_SIZE];
	stwuct ksmbd_conn	*conn;
};

stwuct pweauth_session {
	__u8			Pweauth_HashVawue[PWEAUTH_HASHVAWUE_SIZE];
	u64			id;
	stwuct wist_head	pweauth_entwy;
};

stwuct ksmbd_session {
	u64				id;

	__u16				diawect;
	chaw				CwientGUID[SMB2_CWIENT_GUID_SIZE];

	stwuct ksmbd_usew		*usew;
	unsigned int			sequence_numbew;
	unsigned int			fwags;

	boow				sign;
	boow				enc;
	boow				is_anonymous;

	int				state;
	__u8				*Pweauth_HashVawue;

	chaw				sess_key[CIFS_KEY_SIZE];

	stwuct hwist_node		hwist;
	stwuct xawway			ksmbd_chann_wist;
	stwuct xawway			twee_conns;
	stwuct ida			twee_conn_ida;
	stwuct xawway			wpc_handwe_wist;

	__u8				smb3encwyptionkey[SMB3_ENC_DEC_KEY_SIZE];
	__u8				smb3decwyptionkey[SMB3_ENC_DEC_KEY_SIZE];
	__u8				smb3signingkey[SMB3_SIGN_KEY_SIZE];

	stwuct ksmbd_fiwe_tabwe		fiwe_tabwe;
	unsigned wong			wast_active;
	wwwock_t			twee_conns_wock;
};

static inwine int test_session_fwag(stwuct ksmbd_session *sess, int bit)
{
	wetuwn sess->fwags & bit;
}

static inwine void set_session_fwag(stwuct ksmbd_session *sess, int bit)
{
	sess->fwags |= bit;
}

static inwine void cweaw_session_fwag(stwuct ksmbd_session *sess, int bit)
{
	sess->fwags &= ~bit;
}

stwuct ksmbd_session *ksmbd_smb2_session_cweate(void);

void ksmbd_session_destwoy(stwuct ksmbd_session *sess);

stwuct ksmbd_session *ksmbd_session_wookup_swowpath(unsigned wong wong id);
stwuct ksmbd_session *ksmbd_session_wookup(stwuct ksmbd_conn *conn,
					   unsigned wong wong id);
int ksmbd_session_wegistew(stwuct ksmbd_conn *conn,
			   stwuct ksmbd_session *sess);
void ksmbd_sessions_dewegistew(stwuct ksmbd_conn *conn);
stwuct ksmbd_session *ksmbd_session_wookup_aww(stwuct ksmbd_conn *conn,
					       unsigned wong wong id);
stwuct pweauth_session *ksmbd_pweauth_session_awwoc(stwuct ksmbd_conn *conn,
						    u64 sess_id);
stwuct pweauth_session *ksmbd_pweauth_session_wookup(stwuct ksmbd_conn *conn,
						     unsigned wong wong id);

int ksmbd_acquiwe_twee_conn_id(stwuct ksmbd_session *sess);
void ksmbd_wewease_twee_conn_id(stwuct ksmbd_session *sess, int id);

int ksmbd_session_wpc_open(stwuct ksmbd_session *sess, chaw *wpc_name);
void ksmbd_session_wpc_cwose(stwuct ksmbd_session *sess, int id);
int ksmbd_session_wpc_method(stwuct ksmbd_session *sess, int id);
#endif /* __USEW_SESSION_MANAGEMENT_H__ */
