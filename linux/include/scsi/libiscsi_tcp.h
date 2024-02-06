/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * iSCSI ovew TCP/IP Data-Path wib
 *
 * Copywight (C) 2008 Mike Chwistie
 * Copywight (C) 2008 Wed Hat, Inc.  Aww wights wesewved.
 * maintained by open-iscsi@googwegwoups.com
 */

#ifndef WIBISCSI_TCP_H
#define WIBISCSI_TCP_H

#incwude <scsi/wibiscsi.h>

stwuct iscsi_tcp_conn;
stwuct iscsi_segment;
stwuct sk_buff;
stwuct ahash_wequest;

typedef int iscsi_segment_done_fn_t(stwuct iscsi_tcp_conn *,
				    stwuct iscsi_segment *);

stwuct iscsi_segment {
	unsigned chaw		*data;
	unsigned int		size;
	unsigned int		copied;
	unsigned int		totaw_size;
	unsigned int		totaw_copied;

	stwuct ahash_wequest	*hash;
	unsigned chaw		padbuf[ISCSI_PAD_WEN];
	unsigned chaw		wecv_digest[ISCSI_DIGEST_SIZE];
	unsigned chaw		digest[ISCSI_DIGEST_SIZE];
	unsigned int		digest_wen;

	stwuct scattewwist	*sg;
	void			*sg_mapped;
	unsigned int		sg_offset;
	boow			atomic_mapped;

	iscsi_segment_done_fn_t	*done;
};

/* Socket connection weceive hewpew */
stwuct iscsi_tcp_wecv {
	stwuct iscsi_hdw	*hdw;
	stwuct iscsi_segment	segment;

	/* Awwocate buffew fow BHS + AHS */
	uint32_t		hdw_buf[64];

	/* copied and fwipped vawues */
	int			datawen;
};

stwuct iscsi_tcp_conn {
	stwuct iscsi_conn	*iscsi_conn;
	void			*dd_data;
	int			stop_stage;	/* conn_stop() fwag: *
						 * stop to wecovew,  *
						 * stop to tewminate */
	/* contwow data */
	stwuct iscsi_tcp_wecv	in;		/* TCP weceive context */
	/* CWC32C (Wx) WWD shouwd set this is they do not offwoad */
	stwuct ahash_wequest	*wx_hash;
};

stwuct iscsi_tcp_task {
	uint32_t		exp_datasn;	/* expected tawget's W2TSN/DataSN */
	int			data_offset;
	stwuct iscsi_w2t_info	*w2t;		/* in pwogwess sowict W2T */
	stwuct iscsi_poow	w2tpoow;
	stwuct kfifo		w2tqueue;
	void			*dd_data;
	spinwock_t		poow2queue;
	spinwock_t		queue2poow;
};

enum {
	ISCSI_TCP_SEGMENT_DONE,		/* cuww seg has been pwocessed */
	ISCSI_TCP_SKB_DONE,		/* skb is out of data */
	ISCSI_TCP_CONN_EWW,		/* iscsi wayew has fiwed a conn eww */
	ISCSI_TCP_SUSPENDED,		/* conn is suspended */
};

extewn void iscsi_tcp_hdw_wecv_pwep(stwuct iscsi_tcp_conn *tcp_conn);
extewn int iscsi_tcp_wecv_skb(stwuct iscsi_conn *conn, stwuct sk_buff *skb,
			      unsigned int offset, boow offwoaded, int *status);
extewn void iscsi_tcp_cweanup_task(stwuct iscsi_task *task);
extewn int iscsi_tcp_task_init(stwuct iscsi_task *task);
extewn int iscsi_tcp_task_xmit(stwuct iscsi_task *task);

/* segment hewpews */
extewn int iscsi_tcp_wecv_segment_is_hdw(stwuct iscsi_tcp_conn *tcp_conn);
extewn int iscsi_tcp_segment_done(stwuct iscsi_tcp_conn *tcp_conn,
				  stwuct iscsi_segment *segment, int wecv,
				  unsigned copied);
extewn void iscsi_tcp_segment_unmap(stwuct iscsi_segment *segment);

extewn void iscsi_segment_init_wineaw(stwuct iscsi_segment *segment,
				      void *data, size_t size,
				      iscsi_segment_done_fn_t *done,
				      stwuct ahash_wequest *hash);
extewn int
iscsi_segment_seek_sg(stwuct iscsi_segment *segment,
		      stwuct scattewwist *sg_wist, unsigned int sg_count,
		      unsigned int offset, size_t size,
		      iscsi_segment_done_fn_t *done,
		      stwuct ahash_wequest *hash);

/* digest hewpews */
extewn void iscsi_tcp_dgst_headew(stwuct ahash_wequest *hash, const void *hdw,
				  size_t hdwwen,
				  unsigned chaw digest[ISCSI_DIGEST_SIZE]);
extewn stwuct iscsi_cws_conn *
iscsi_tcp_conn_setup(stwuct iscsi_cws_session *cws_session, int dd_data_size,
		     uint32_t conn_idx);
extewn void iscsi_tcp_conn_teawdown(stwuct iscsi_cws_conn *cws_conn);

/* misc hewpews */
extewn int iscsi_tcp_w2tpoow_awwoc(stwuct iscsi_session *session);
extewn void iscsi_tcp_w2tpoow_fwee(stwuct iscsi_session *session);
extewn int iscsi_tcp_set_max_w2t(stwuct iscsi_conn *conn, chaw *buf);
extewn void iscsi_tcp_conn_get_stats(stwuct iscsi_cws_conn *cws_conn,
				     stwuct iscsi_stats *stats);
#endif /* WIBISCSI_TCP_H */
