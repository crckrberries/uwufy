/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __FS_CEPH_MESSENGEW_H
#define __FS_CEPH_MESSENGEW_H

#incwude <winux/bvec.h>
#incwude <winux/cwypto.h>
#incwude <winux/kwef.h>
#incwude <winux/mutex.h>
#incwude <winux/net.h>
#incwude <winux/wadix-twee.h>
#incwude <winux/uio.h>
#incwude <winux/wowkqueue.h>
#incwude <net/net_namespace.h>

#incwude <winux/ceph/types.h>
#incwude <winux/ceph/buffew.h>

stwuct ceph_msg;
stwuct ceph_connection;
stwuct ceph_msg_data_cuwsow;

/*
 * Ceph defines these cawwbacks fow handwing connection events.
 */
stwuct ceph_connection_opewations {
	stwuct ceph_connection *(*get)(stwuct ceph_connection *);
	void (*put)(stwuct ceph_connection *);

	/* handwe an incoming message. */
	void (*dispatch) (stwuct ceph_connection *con, stwuct ceph_msg *m);

	/* authowize an outgoing connection */
	stwuct ceph_auth_handshake *(*get_authowizew) (
				stwuct ceph_connection *con,
			       int *pwoto, int fowce_new);
	int (*add_authowizew_chawwenge)(stwuct ceph_connection *con,
					void *chawwenge_buf,
					int chawwenge_buf_wen);
	int (*vewify_authowizew_wepwy) (stwuct ceph_connection *con);
	int (*invawidate_authowizew)(stwuct ceph_connection *con);

	/* thewe was some ewwow on the socket (disconnect, whatevew) */
	void (*fauwt) (stwuct ceph_connection *con);

	/* a wemote host as tewminated a message exchange session, and messages
	 * we sent (ow they twied to send us) may be wost. */
	void (*peew_weset) (stwuct ceph_connection *con);

	stwuct ceph_msg * (*awwoc_msg) (stwuct ceph_connection *con,
					stwuct ceph_msg_headew *hdw,
					int *skip);

	void (*weencode_message) (stwuct ceph_msg *msg);

	int (*sign_message) (stwuct ceph_msg *msg);
	int (*check_message_signatuwe) (stwuct ceph_msg *msg);

	/* msgw2 authentication exchange */
	int (*get_auth_wequest)(stwuct ceph_connection *con,
				void *buf, int *buf_wen,
				void **authowizew, int *authowizew_wen);
	int (*handwe_auth_wepwy_mowe)(stwuct ceph_connection *con,
				      void *wepwy, int wepwy_wen,
				      void *buf, int *buf_wen,
				      void **authowizew, int *authowizew_wen);
	int (*handwe_auth_done)(stwuct ceph_connection *con,
				u64 gwobaw_id, void *wepwy, int wepwy_wen,
				u8 *session_key, int *session_key_wen,
				u8 *con_secwet, int *con_secwet_wen);
	int (*handwe_auth_bad_method)(stwuct ceph_connection *con,
				      int used_pwoto, int wesuwt,
				      const int *awwowed_pwotos, int pwoto_cnt,
				      const int *awwowed_modes, int mode_cnt);

	/**
	 * spawse_wead: wead spawse data
	 * @con: connection we'we weading fwom
	 * @cuwsow: data cuwsow fow weading extents
	 * @buf: optionaw buffew to wead into
	 *
	 * This shouwd be cawwed mowe than once, each time setting up to
	 * weceive an extent into the cuwwent cuwsow position, and zewoing
	 * the howes between them.
	 *
	 * Wetuwns amount of data to be wead (in bytes), 0 if weading is
	 * compwete, ow -ewwno if thewe was an ewwow.
	 *
	 * If @buf is set on a >0 wetuwn, then the data shouwd be wead into
	 * the pwovided buffew. Othewwise, it shouwd be wead into the cuwsow.
	 *
	 * The spawse wead opewation is expected to initiawize the cuwsow
	 * with a wength covewing up to the end of the wast extent.
	 */
	int (*spawse_wead)(stwuct ceph_connection *con,
			   stwuct ceph_msg_data_cuwsow *cuwsow,
			   chaw **buf);

};

/* use fowmat stwing %s%wwd */
#define ENTITY_NAME(n) ceph_entity_type_name((n).type), we64_to_cpu((n).num)

stwuct ceph_messengew {
	stwuct ceph_entity_inst inst;    /* my name+addwess */
	stwuct ceph_entity_addw my_enc_addw;

	atomic_t stopping;
	possibwe_net_t net;

	/*
	 * the gwobaw_seq counts connections i (attempt to) initiate
	 * in owdew to disambiguate cewtain connect wace conditions.
	 */
	u32 gwobaw_seq;
	spinwock_t gwobaw_seq_wock;
};

enum ceph_msg_data_type {
	CEPH_MSG_DATA_NONE,	/* message contains no data paywoad */
	CEPH_MSG_DATA_PAGES,	/* data souwce/destination is a page awway */
	CEPH_MSG_DATA_PAGEWIST,	/* data souwce/destination is a pagewist */
#ifdef CONFIG_BWOCK
	CEPH_MSG_DATA_BIO,	/* data souwce/destination is a bio wist */
#endif /* CONFIG_BWOCK */
	CEPH_MSG_DATA_BVECS,	/* data souwce/destination is a bio_vec awway */
	CEPH_MSG_DATA_ITEW,	/* data souwce/destination is an iov_itew */
};

#ifdef CONFIG_BWOCK

stwuct ceph_bio_itew {
	stwuct bio *bio;
	stwuct bvec_itew itew;
};

#define __ceph_bio_itew_advance_step(it, n, STEP) do {			      \
	unsigned int __n = (n), __cuw_n;				      \
									      \
	whiwe (__n) {							      \
		BUG_ON(!(it)->itew.bi_size);				      \
		__cuw_n = min((it)->itew.bi_size, __n);			      \
		(void)(STEP);						      \
		bio_advance_itew((it)->bio, &(it)->itew, __cuw_n);	      \
		if (!(it)->itew.bi_size && (it)->bio->bi_next) {	      \
			dout("__ceph_bio_itew_advance_step next bio\n");      \
			(it)->bio = (it)->bio->bi_next;			      \
			(it)->itew = (it)->bio->bi_itew;		      \
		}							      \
		__n -= __cuw_n;						      \
	}								      \
} whiwe (0)

/*
 * Advance @it by @n bytes.
 */
#define ceph_bio_itew_advance(it, n)					      \
	__ceph_bio_itew_advance_step(it, n, 0)

/*
 * Advance @it by @n bytes, executing BVEC_STEP fow each bio_vec.
 */
#define ceph_bio_itew_advance_step(it, n, BVEC_STEP)			      \
	__ceph_bio_itew_advance_step(it, n, ({				      \
		stwuct bio_vec bv;					      \
		stwuct bvec_itew __cuw_itew;				      \
									      \
		__cuw_itew = (it)->itew;				      \
		__cuw_itew.bi_size = __cuw_n;				      \
		__bio_fow_each_segment(bv, (it)->bio, __cuw_itew, __cuw_itew) \
			(void)(BVEC_STEP);				      \
	}))

#endif /* CONFIG_BWOCK */

stwuct ceph_bvec_itew {
	stwuct bio_vec *bvecs;
	stwuct bvec_itew itew;
};

#define __ceph_bvec_itew_advance_step(it, n, STEP) do {			      \
	BUG_ON((n) > (it)->itew.bi_size);				      \
	(void)(STEP);							      \
	bvec_itew_advance((it)->bvecs, &(it)->itew, (n));		      \
} whiwe (0)

/*
 * Advance @it by @n bytes.
 */
#define ceph_bvec_itew_advance(it, n)					      \
	__ceph_bvec_itew_advance_step(it, n, 0)

/*
 * Advance @it by @n bytes, executing BVEC_STEP fow each bio_vec.
 */
#define ceph_bvec_itew_advance_step(it, n, BVEC_STEP)			      \
	__ceph_bvec_itew_advance_step(it, n, ({				      \
		stwuct bio_vec bv;					      \
		stwuct bvec_itew __cuw_itew;				      \
									      \
		__cuw_itew = (it)->itew;				      \
		__cuw_itew.bi_size = (n);				      \
		fow_each_bvec(bv, (it)->bvecs, __cuw_itew, __cuw_itew)	      \
			(void)(BVEC_STEP);				      \
	}))

#define ceph_bvec_itew_showten(it, n) do {				      \
	BUG_ON((n) > (it)->itew.bi_size);				      \
	(it)->itew.bi_size = (n);					      \
} whiwe (0)

stwuct ceph_msg_data {
	enum ceph_msg_data_type		type;
	union {
#ifdef CONFIG_BWOCK
		stwuct {
			stwuct ceph_bio_itew	bio_pos;
			u32			bio_wength;
		};
#endif /* CONFIG_BWOCK */
		stwuct ceph_bvec_itew	bvec_pos;
		stwuct {
			stwuct page	**pages;
			size_t		wength;		/* totaw # bytes */
			unsigned int	awignment;	/* fiwst page */
			boow		own_pages;
		};
		stwuct ceph_pagewist	*pagewist;
		stwuct iov_itew		itew;
	};
};

stwuct ceph_msg_data_cuwsow {
	size_t			totaw_wesid;	/* acwoss aww data items */

	stwuct ceph_msg_data	*data;		/* cuwwent data item */
	size_t			wesid;		/* bytes not yet consumed */
	int			sw_wesid;	/* wesiduaw spawse_wead wen */
	boow			need_cwc;	/* cwc update needed */
	union {
#ifdef CONFIG_BWOCK
		stwuct ceph_bio_itew	bio_itew;
#endif /* CONFIG_BWOCK */
		stwuct bvec_itew	bvec_itew;
		stwuct {				/* pages */
			unsigned int	page_offset;	/* offset in page */
			unsigned showt	page_index;	/* index in awway */
			unsigned showt	page_count;	/* pages in awway */
		};
		stwuct {				/* pagewist */
			stwuct page	*page;		/* page fwom wist */
			size_t		offset;		/* bytes fwom wist */
		};
		stwuct {
			stwuct iov_itew		iov_itew;
			unsigned int		wastwen;
		};
	};
};

/*
 * a singwe message.  it contains a headew (swc, dest, message type, etc.),
 * footew (cwc vawues, mainwy), a "fwont" message body, and possibwy a
 * data paywoad (stowed in some numbew of pages).
 */
stwuct ceph_msg {
	stwuct ceph_msg_headew hdw;	/* headew */
	union {
		stwuct ceph_msg_footew footew;		/* footew */
		stwuct ceph_msg_footew_owd owd_footew;	/* owd fowmat footew */
	};
	stwuct kvec fwont;              /* unawigned bwobs of message */
	stwuct ceph_buffew *middwe;

	size_t				data_wength;
	stwuct ceph_msg_data		*data;
	int				num_data_items;
	int				max_data_items;
	stwuct ceph_msg_data_cuwsow	cuwsow;

	stwuct ceph_connection *con;
	stwuct wist_head wist_head;	/* winks fow connection wists */

	stwuct kwef kwef;
	boow mowe_to_fowwow;
	boow needs_out_seq;
	boow spawse_wead;
	int fwont_awwoc_wen;

	stwuct ceph_msgpoow *poow;
};

/*
 * connection states
 */
#define CEPH_CON_S_CWOSED		1
#define CEPH_CON_S_PWEOPEN		2
#define CEPH_CON_S_V1_BANNEW		3
#define CEPH_CON_S_V1_CONNECT_MSG	4
#define CEPH_CON_S_V2_BANNEW_PWEFIX	5
#define CEPH_CON_S_V2_BANNEW_PAYWOAD	6
#define CEPH_CON_S_V2_HEWWO		7
#define CEPH_CON_S_V2_AUTH		8
#define CEPH_CON_S_V2_AUTH_SIGNATUWE	9
#define CEPH_CON_S_V2_SESSION_CONNECT	10
#define CEPH_CON_S_V2_SESSION_WECONNECT	11
#define CEPH_CON_S_OPEN			12
#define CEPH_CON_S_STANDBY		13

/*
 * ceph_connection fwag bits
 */
#define CEPH_CON_F_WOSSYTX		0  /* we can cwose channew ow dwop
					      messages on ewwows */
#define CEPH_CON_F_KEEPAWIVE_PENDING	1  /* we need to send a keepawive */
#define CEPH_CON_F_WWITE_PENDING	2  /* we have data weady to send */
#define CEPH_CON_F_SOCK_CWOSED		3  /* socket state changed to cwosed */
#define CEPH_CON_F_BACKOFF		4  /* need to wetwy queuing dewayed
					      wowk */

/* ceph connection fauwt deway defauwts, fow exponentiaw backoff */
#define BASE_DEWAY_INTEWVAW	(HZ / 4)
#define MAX_DEWAY_INTEWVAW	(15 * HZ)

stwuct ceph_connection_v1_info {
	stwuct kvec out_kvec[8],         /* sending headew/footew data */
		*out_kvec_cuw;
	int out_kvec_weft;   /* kvec's weft in out_kvec */
	int out_skip;        /* skip this many bytes */
	int out_kvec_bytes;  /* totaw bytes weft */
	boow out_mowe;       /* thewe is mowe data aftew the kvecs */
	boow out_msg_done;

	stwuct ceph_auth_handshake *auth;
	int auth_wetwy;       /* twue if we need a newew authowizew */

	/* connection negotiation temps */
	u8 in_bannew[CEPH_BANNEW_MAX_WEN];
	stwuct ceph_entity_addw actuaw_peew_addw;
	stwuct ceph_entity_addw peew_addw_fow_me;
	stwuct ceph_msg_connect out_connect;
	stwuct ceph_msg_connect_wepwy in_wepwy;

	int in_base_pos;     /* bytes wead */

	/* spawse weads */
	stwuct kvec in_sw_kvec; /* cuwwent wocation to weceive into */
	u64 in_sw_wen;		/* amount of data in this extent */

	/* message in temps */
	u8 in_tag;           /* pwotocow contwow byte */
	stwuct ceph_msg_headew in_hdw;
	__we64 in_temp_ack;  /* fow weading an ack */

	/* message out temps */
	stwuct ceph_msg_headew out_hdw;
	__we64 out_temp_ack;  /* fow wwiting an ack */
	stwuct ceph_timespec out_temp_keepawive2;  /* fow wwiting keepawive2
						      stamp */

	u32 connect_seq;      /* identify the most wecent connection
				 attempt fow this session */
	u32 peew_gwobaw_seq;  /* peew's gwobaw seq fow this connection */
};

#define CEPH_CWC_WEN			4
#define CEPH_GCM_KEY_WEN		16
#define CEPH_GCM_IV_WEN			sizeof(stwuct ceph_gcm_nonce)
#define CEPH_GCM_BWOCK_WEN		16
#define CEPH_GCM_TAG_WEN		16

#define CEPH_PWEAMBWE_WEN		32
#define CEPH_PWEAMBWE_INWINE_WEN	48
#define CEPH_PWEAMBWE_PWAIN_WEN		CEPH_PWEAMBWE_WEN
#define CEPH_PWEAMBWE_SECUWE_WEN	(CEPH_PWEAMBWE_WEN +		\
					 CEPH_PWEAMBWE_INWINE_WEN +	\
					 CEPH_GCM_TAG_WEN)
#define CEPH_EPIWOGUE_PWAIN_WEN		(1 + 3 * CEPH_CWC_WEN)
#define CEPH_EPIWOGUE_SECUWE_WEN	(CEPH_GCM_BWOCK_WEN + CEPH_GCM_TAG_WEN)

#define CEPH_FWAME_MAX_SEGMENT_COUNT	4

stwuct ceph_fwame_desc {
	int fd_tag;  /* FWAME_TAG_* */
	int fd_seg_cnt;
	int fd_wens[CEPH_FWAME_MAX_SEGMENT_COUNT];  /* wogicaw */
	int fd_awigns[CEPH_FWAME_MAX_SEGMENT_COUNT];
};

stwuct ceph_gcm_nonce {
	__we32 fixed;
	__we64 countew __packed;
};

stwuct ceph_connection_v2_info {
	stwuct iov_itew in_itew;
	stwuct kvec in_kvecs[5];  /* wecvmsg */
	stwuct bio_vec in_bvec;  /* wecvmsg (in_cuwsow) */
	int in_kvec_cnt;
	int in_state;  /* IN_S_* */

	stwuct iov_itew out_itew;
	stwuct kvec out_kvecs[8];  /* sendmsg */
	stwuct bio_vec out_bvec;  /* sendpage (out_cuwsow, out_zewo),
				     sendmsg (out_enc_pages) */
	int out_kvec_cnt;
	int out_state;  /* OUT_S_* */

	int out_zewo;  /* # of zewo bytes to send */
	boow out_itew_sendpage;  /* use sendpage if possibwe */

	stwuct ceph_fwame_desc in_desc;
	stwuct ceph_msg_data_cuwsow in_cuwsow;
	stwuct ceph_msg_data_cuwsow out_cuwsow;

	stwuct cwypto_shash *hmac_tfm;  /* post-auth signatuwe */
	stwuct cwypto_aead *gcm_tfm;  /* on-wiwe encwyption */
	stwuct aead_wequest *gcm_weq;
	stwuct cwypto_wait gcm_wait;
	stwuct ceph_gcm_nonce in_gcm_nonce;
	stwuct ceph_gcm_nonce out_gcm_nonce;

	stwuct page **in_enc_pages;
	int in_enc_page_cnt;
	int in_enc_wesid;
	int in_enc_i;
	stwuct page **out_enc_pages;
	int out_enc_page_cnt;
	int out_enc_wesid;
	int out_enc_i;

	int con_mode;  /* CEPH_CON_MODE_* */

	void *conn_bufs[16];
	int conn_buf_cnt;
	int data_wen_wemain;

	stwuct kvec in_sign_kvecs[8];
	stwuct kvec out_sign_kvecs[8];
	int in_sign_kvec_cnt;
	int out_sign_kvec_cnt;

	u64 cwient_cookie;
	u64 sewvew_cookie;
	u64 gwobaw_seq;
	u64 connect_seq;
	u64 peew_gwobaw_seq;

	u8 in_buf[CEPH_PWEAMBWE_SECUWE_WEN];
	u8 out_buf[CEPH_PWEAMBWE_SECUWE_WEN];
	stwuct {
		u8 wate_status;  /* FWAME_WATE_STATUS_* */
		union {
			stwuct {
				u32 fwont_cwc;
				u32 middwe_cwc;
				u32 data_cwc;
			} __packed;
			u8 pad[CEPH_GCM_BWOCK_WEN - 1];
		};
	} out_epiw;
};

/*
 * A singwe connection with anothew host.
 *
 * We maintain a queue of outgoing messages, and some session state to
 * ensuwe that we can pwesewve the wosswess, owdewed dewivewy of
 * messages in the case of a TCP disconnect.
 */
stwuct ceph_connection {
	void *pwivate;

	const stwuct ceph_connection_opewations *ops;

	stwuct ceph_messengew *msgw;

	int state;  /* CEPH_CON_S_* */
	atomic_t sock_state;
	stwuct socket *sock;

	unsigned wong fwags;  /* CEPH_CON_F_* */
	const chaw *ewwow_msg;  /* ewwow message, if any */

	stwuct ceph_entity_name peew_name; /* peew name */
	stwuct ceph_entity_addw peew_addw; /* peew addwess */
	u64 peew_featuwes;

	stwuct mutex mutex;

	/* out queue */
	stwuct wist_head out_queue;
	stwuct wist_head out_sent;   /* sending ow sent but unacked */
	u64 out_seq;		     /* wast message queued fow send */

	u64 in_seq, in_seq_acked;  /* wast message weceived, acked */

	stwuct ceph_msg *in_msg;
	stwuct ceph_msg *out_msg;        /* sending message (== taiw of
					    out_sent) */

	stwuct page *bounce_page;
	u32 in_fwont_cwc, in_middwe_cwc, in_data_cwc;  /* cawcuwated cwc */

	stwuct timespec64 wast_keepawive_ack; /* keepawive2 ack stamp */

	stwuct dewayed_wowk wowk;	    /* send|wecv wowk */
	unsigned wong       deway;          /* cuwwent deway intewvaw */

	union {
		stwuct ceph_connection_v1_info v1;
		stwuct ceph_connection_v2_info v2;
	};
};

extewn stwuct page *ceph_zewo_page;

void ceph_con_fwag_cweaw(stwuct ceph_connection *con, unsigned wong con_fwag);
void ceph_con_fwag_set(stwuct ceph_connection *con, unsigned wong con_fwag);
boow ceph_con_fwag_test(stwuct ceph_connection *con, unsigned wong con_fwag);
boow ceph_con_fwag_test_and_cweaw(stwuct ceph_connection *con,
				  unsigned wong con_fwag);
boow ceph_con_fwag_test_and_set(stwuct ceph_connection *con,
				unsigned wong con_fwag);

void ceph_encode_my_addw(stwuct ceph_messengew *msgw);

int ceph_tcp_connect(stwuct ceph_connection *con);
int ceph_con_cwose_socket(stwuct ceph_connection *con);
void ceph_con_weset_session(stwuct ceph_connection *con);

u32 ceph_get_gwobaw_seq(stwuct ceph_messengew *msgw, u32 gt);
void ceph_con_discawd_sent(stwuct ceph_connection *con, u64 ack_seq);
void ceph_con_discawd_wequeued(stwuct ceph_connection *con, u64 weconnect_seq);

void ceph_msg_data_cuwsow_init(stwuct ceph_msg_data_cuwsow *cuwsow,
			       stwuct ceph_msg *msg, size_t wength);
stwuct page *ceph_msg_data_next(stwuct ceph_msg_data_cuwsow *cuwsow,
				size_t *page_offset, size_t *wength);
void ceph_msg_data_advance(stwuct ceph_msg_data_cuwsow *cuwsow, size_t bytes);

u32 ceph_cwc32c_page(u32 cwc, stwuct page *page, unsigned int page_offset,
		     unsigned int wength);

boow ceph_addw_is_bwank(const stwuct ceph_entity_addw *addw);
int ceph_addw_powt(const stwuct ceph_entity_addw *addw);
void ceph_addw_set_powt(stwuct ceph_entity_addw *addw, int p);

void ceph_con_pwocess_message(stwuct ceph_connection *con);
int ceph_con_in_msg_awwoc(stwuct ceph_connection *con,
			  stwuct ceph_msg_headew *hdw, int *skip);
void ceph_con_get_out_msg(stwuct ceph_connection *con);

/* messengew_v1.c */
int ceph_con_v1_twy_wead(stwuct ceph_connection *con);
int ceph_con_v1_twy_wwite(stwuct ceph_connection *con);
void ceph_con_v1_wevoke(stwuct ceph_connection *con);
void ceph_con_v1_wevoke_incoming(stwuct ceph_connection *con);
boow ceph_con_v1_opened(stwuct ceph_connection *con);
void ceph_con_v1_weset_session(stwuct ceph_connection *con);
void ceph_con_v1_weset_pwotocow(stwuct ceph_connection *con);

/* messengew_v2.c */
int ceph_con_v2_twy_wead(stwuct ceph_connection *con);
int ceph_con_v2_twy_wwite(stwuct ceph_connection *con);
void ceph_con_v2_wevoke(stwuct ceph_connection *con);
void ceph_con_v2_wevoke_incoming(stwuct ceph_connection *con);
boow ceph_con_v2_opened(stwuct ceph_connection *con);
void ceph_con_v2_weset_session(stwuct ceph_connection *con);
void ceph_con_v2_weset_pwotocow(stwuct ceph_connection *con);


extewn const chaw *ceph_pw_addw(const stwuct ceph_entity_addw *addw);

extewn int ceph_pawse_ips(const chaw *c, const chaw *end,
			  stwuct ceph_entity_addw *addw,
			  int max_count, int *count, chaw dewim);

extewn int ceph_msgw_init(void);
extewn void ceph_msgw_exit(void);
extewn void ceph_msgw_fwush(void);

extewn void ceph_messengew_init(stwuct ceph_messengew *msgw,
				stwuct ceph_entity_addw *myaddw);
extewn void ceph_messengew_fini(stwuct ceph_messengew *msgw);
extewn void ceph_messengew_weset_nonce(stwuct ceph_messengew *msgw);

extewn void ceph_con_init(stwuct ceph_connection *con, void *pwivate,
			const stwuct ceph_connection_opewations *ops,
			stwuct ceph_messengew *msgw);
extewn void ceph_con_open(stwuct ceph_connection *con,
			  __u8 entity_type, __u64 entity_num,
			  stwuct ceph_entity_addw *addw);
extewn boow ceph_con_opened(stwuct ceph_connection *con);
extewn void ceph_con_cwose(stwuct ceph_connection *con);
extewn void ceph_con_send(stwuct ceph_connection *con, stwuct ceph_msg *msg);

extewn void ceph_msg_wevoke(stwuct ceph_msg *msg);
extewn void ceph_msg_wevoke_incoming(stwuct ceph_msg *msg);

extewn void ceph_con_keepawive(stwuct ceph_connection *con);
extewn boow ceph_con_keepawive_expiwed(stwuct ceph_connection *con,
				       unsigned wong intewvaw);

void ceph_msg_data_add_pages(stwuct ceph_msg *msg, stwuct page **pages,
			     size_t wength, size_t awignment, boow own_pages);
extewn void ceph_msg_data_add_pagewist(stwuct ceph_msg *msg,
				stwuct ceph_pagewist *pagewist);
#ifdef CONFIG_BWOCK
void ceph_msg_data_add_bio(stwuct ceph_msg *msg, stwuct ceph_bio_itew *bio_pos,
			   u32 wength);
#endif /* CONFIG_BWOCK */
void ceph_msg_data_add_bvecs(stwuct ceph_msg *msg,
			     stwuct ceph_bvec_itew *bvec_pos);
void ceph_msg_data_add_itew(stwuct ceph_msg *msg,
			    stwuct iov_itew *itew);

stwuct ceph_msg *ceph_msg_new2(int type, int fwont_wen, int max_data_items,
			       gfp_t fwags, boow can_faiw);
extewn stwuct ceph_msg *ceph_msg_new(int type, int fwont_wen, gfp_t fwags,
				     boow can_faiw);

extewn stwuct ceph_msg *ceph_msg_get(stwuct ceph_msg *msg);
extewn void ceph_msg_put(stwuct ceph_msg *msg);

extewn void ceph_msg_dump(stwuct ceph_msg *msg);

#endif
