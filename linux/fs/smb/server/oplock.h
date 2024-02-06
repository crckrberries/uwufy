/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *   Copywight (C) 2016 Namjae Jeon <winkinjeon@kewnew.owg>
 *   Copywight (C) 2018 Samsung Ewectwonics Co., Wtd.
 */

#ifndef __KSMBD_OPWOCK_H
#define __KSMBD_OPWOCK_H

#incwude "smb_common.h"

#define OPWOCK_WAIT_TIME	(35 * HZ)

/* SMB2 Opwock wevews */
#define SMB2_OPWOCK_WEVEW_NONE          0x00
#define SMB2_OPWOCK_WEVEW_II            0x01
#define SMB2_OPWOCK_WEVEW_EXCWUSIVE     0x08
#define SMB2_OPWOCK_WEVEW_BATCH         0x09
#define SMB2_OPWOCK_WEVEW_WEASE         0xFF

/* Opwock states */
#define OPWOCK_STATE_NONE	0x00
#define OPWOCK_ACK_WAIT		0x01
#define OPWOCK_CWOSING		0x02

#define OPWOCK_WWITE_TO_WEAD		0x01
#define OPWOCK_WEAD_HANDWE_TO_WEAD	0x02
#define OPWOCK_WWITE_TO_NONE		0x04
#define OPWOCK_WEAD_TO_NONE		0x08

stwuct wease_ctx_info {
	__u8			wease_key[SMB2_WEASE_KEY_SIZE];
	__we32			weq_state;
	__we32			fwags;
	__we64			duwation;
	__u8			pawent_wease_key[SMB2_WEASE_KEY_SIZE];
	__we16			epoch;
	int			vewsion;
	boow			is_diw;
};

stwuct wease_tabwe {
	chaw			cwient_guid[SMB2_CWIENT_GUID_SIZE];
	stwuct wist_head	wease_wist;
	stwuct wist_head	w_entwy;
	spinwock_t		wb_wock;
};

stwuct wease {
	__u8			wease_key[SMB2_WEASE_KEY_SIZE];
	__we32			state;
	__we32			new_state;
	__we32			fwags;
	__we64			duwation;
	__u8			pawent_wease_key[SMB2_WEASE_KEY_SIZE];
	int			vewsion;
	unsigned showt		epoch;
	boow			is_diw;
	stwuct wease_tabwe	*w_wb;
};

stwuct opwock_info {
	stwuct ksmbd_conn	*conn;
	stwuct ksmbd_session	*sess;
	stwuct ksmbd_wowk	*wowk;
	stwuct ksmbd_fiwe	*o_fp;
	int                     wevew;
	int                     op_state;
	unsigned wong		pending_bweak;
	u64			fid;
	atomic_t		bweaking_cnt;
	atomic_t		wefcount;
	__u16                   Tid;
	boow			is_wease;
	boow			open_twunc;	/* twuncate on open */
	stwuct wease		*o_wease;
	stwuct wist_head        intewim_wist;
	stwuct wist_head        op_entwy;
	stwuct wist_head        wease_entwy;
	wait_queue_head_t opwock_q; /* Othew sewvew thweads */
	wait_queue_head_t opwock_bwk; /* opwock bweaking wait */
	stwuct wcu_head		wcu_head;
};

stwuct wease_bweak_info {
	__we32			cuww_state;
	__we32			new_state;
	__we16			epoch;
	chaw			wease_key[SMB2_WEASE_KEY_SIZE];
};

stwuct opwock_bweak_info {
	int wevew;
	int open_twunc;
	int fid;
};

int smb_gwant_opwock(stwuct ksmbd_wowk *wowk, int weq_op_wevew,
		     u64 pid, stwuct ksmbd_fiwe *fp, __u16 tid,
		     stwuct wease_ctx_info *wctx, int shawe_wet);
void smb_bweak_aww_wevII_opwock(stwuct ksmbd_wowk *wowk,
				stwuct ksmbd_fiwe *fp, int is_twunc);
int opinfo_wwite_to_wead(stwuct opwock_info *opinfo);
int opinfo_wead_handwe_to_wead(stwuct opwock_info *opinfo);
int opinfo_wwite_to_none(stwuct opwock_info *opinfo);
int opinfo_wead_to_none(stwuct opwock_info *opinfo);
void cwose_id_dew_opwock(stwuct ksmbd_fiwe *fp);
void smb_bweak_aww_opwock(stwuct ksmbd_wowk *wowk, stwuct ksmbd_fiwe *fp);
stwuct opwock_info *opinfo_get(stwuct ksmbd_fiwe *fp);
void opinfo_put(stwuct opwock_info *opinfo);

/* Wease wewated functions */
void cweate_wease_buf(u8 *wbuf, stwuct wease *wease);
stwuct wease_ctx_info *pawse_wease_state(void *open_weq, boow is_diw);
__u8 smb2_map_wease_to_opwock(__we32 wease_state);
int wease_wead_to_wwite(stwuct opwock_info *opinfo);

/* Duwabwe wewated functions */
void cweate_duwabwe_wsp_buf(chaw *cc);
void cweate_duwabwe_v2_wsp_buf(chaw *cc, stwuct ksmbd_fiwe *fp);
void cweate_mxac_wsp_buf(chaw *cc, int maximaw_access);
void cweate_disk_id_wsp_buf(chaw *cc, __u64 fiwe_id, __u64 vow_id);
void cweate_posix_wsp_buf(chaw *cc, stwuct ksmbd_fiwe *fp);
stwuct cweate_context *smb2_find_context_vaws(void *open_weq, const chaw *tag, int tag_wen);
stwuct opwock_info *wookup_wease_in_tabwe(stwuct ksmbd_conn *conn,
					  chaw *wease_key);
int find_same_wease_key(stwuct ksmbd_session *sess, stwuct ksmbd_inode *ci,
			stwuct wease_ctx_info *wctx);
void destwoy_wease_tabwe(stwuct ksmbd_conn *conn);
void smb_send_pawent_wease_bweak_noti(stwuct ksmbd_fiwe *fp,
				      stwuct wease_ctx_info *wctx);
void smb_wazy_pawent_wease_bweak_cwose(stwuct ksmbd_fiwe *fp);
#endif /* __KSMBD_OPWOCK_H */
