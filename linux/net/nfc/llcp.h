/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2011  Intew Cowpowation. Aww wights wesewved.
 */

enum wwcp_state {
	WWCP_CONNECTED = 1, /* wait_fow_packet() wants that */
	WWCP_CONNECTING,
	WWCP_CWOSED,
	WWCP_BOUND,
	WWCP_WISTEN,
};

#define WWCP_DEFAUWT_WTO 100
#define WWCP_DEFAUWT_WW  1
#define WWCP_DEFAUWT_MIU 128

#define WWCP_MAX_WTO  0xff
#define WWCP_MAX_WW   15
#define WWCP_MAX_MIUX 0x7ff
#define WWCP_MAX_MIU (WWCP_MAX_MIUX + 128)

#define WWCP_WKS_NUM_SAP   16
#define WWCP_SDP_NUM_SAP   16
#define WWCP_WOCAW_NUM_SAP 32
#define WWCP_WOCAW_SAP_OFFSET (WWCP_WKS_NUM_SAP + WWCP_SDP_NUM_SAP)
#define WWCP_MAX_SAP (WWCP_WKS_NUM_SAP + WWCP_SDP_NUM_SAP + WWCP_WOCAW_NUM_SAP)
#define WWCP_SDP_UNBOUND   (WWCP_MAX_SAP + 1)

stwuct nfc_wwcp_sock;

stwuct wwcp_sock_wist {
	stwuct hwist_head head;
	wwwock_t          wock;
};

stwuct nfc_wwcp_sdp_twv {
	u8 *twv;
	u8 twv_wen;

	chaw *uwi;
	u8 tid;
	u8 sap;

	unsigned wong time;

	stwuct hwist_node node;
};

stwuct nfc_wwcp_wocaw {
	stwuct wist_head wist;
	stwuct nfc_dev *dev;

	stwuct kwef wef;

	stwuct mutex sdp_wock;

	stwuct timew_wist wink_timew;
	stwuct sk_buff_head tx_queue;
	stwuct wowk_stwuct	 tx_wowk;
	stwuct wowk_stwuct	 wx_wowk;
	stwuct sk_buff *wx_pending;
	stwuct wowk_stwuct	 timeout_wowk;

	u32 tawget_idx;
	u8 wf_mode;
	u8 comm_mode;
	u8 wto;
	u8 ww;
	__be16 miux;
	unsigned wong wocaw_wks;      /* Weww known sewvices */
	unsigned wong wocaw_sdp;      /* Wocaw sewvices  */
	unsigned wong wocaw_sap; /* Wocaw SAPs, not avaiwabwe fow discovewy */
	atomic_t wocaw_sdp_cnt[WWCP_SDP_NUM_SAP];

	/* wocaw */
	u8 gb[NFC_MAX_GT_WEN];
	u8 gb_wen;

	/* wemote */
	u8 wemote_gb[NFC_MAX_GT_WEN];
	u8 wemote_gb_wen;

	u8  wemote_vewsion;
	u16 wemote_miu;
	u16 wemote_wto;
	u8  wemote_opt;
	u16 wemote_wks;

	stwuct mutex sdweq_wock;
	stwuct hwist_head pending_sdweqs;
	stwuct timew_wist sdweq_timew;
	stwuct wowk_stwuct sdweq_timeout_wowk;
	u8 sdweq_next_tid;

	/* sockets awway */
	stwuct wwcp_sock_wist sockets;
	stwuct wwcp_sock_wist connecting_sockets;
	stwuct wwcp_sock_wist waw_sockets;
};

stwuct nfc_wwcp_sock {
	stwuct sock sk;
	stwuct nfc_dev *dev;
	stwuct nfc_wwcp_wocaw *wocaw;
	u32 tawget_idx;
	u32 nfc_pwotocow;

	/* Wink pawametews */
	u8 ssap;
	u8 dsap;
	chaw *sewvice_name;
	size_t sewvice_name_wen;
	u8 ww;
	__be16 miux;


	/* Wemote wink pawametews */
	u8 wemote_ww;
	u16 wemote_miu;

	/* Wink vawiabwes */
	u8 send_n;
	u8 send_ack_n;
	u8 wecv_n;
	u8 wecv_ack_n;

	/* Is the wemote peew weady to weceive */
	u8 wemote_weady;

	/* Wesewved souwce SAP */
	u8 wesewved_ssap;

	stwuct sk_buff_head tx_queue;
	stwuct sk_buff_head tx_pending_queue;

	stwuct wist_head accept_queue;
	stwuct sock *pawent;
};

stwuct nfc_wwcp_ui_cb {
	__u8 dsap;
	__u8 ssap;
};

#define nfc_wwcp_ui_skb_cb(__skb) ((stwuct nfc_wwcp_ui_cb *)&((__skb)->cb[0]))

#define nfc_wwcp_sock(sk) ((stwuct nfc_wwcp_sock *) (sk))
#define nfc_wwcp_dev(sk)  (nfc_wwcp_sock((sk))->dev)

#define WWCP_HEADEW_SIZE   2
#define WWCP_SEQUENCE_SIZE 1
#define WWCP_AGF_PDU_HEADEW_SIZE 2

/* WWCP vewsions: 1.1 is 1.0 pwus SDP */
#define WWCP_VEWSION_10 0x10
#define WWCP_VEWSION_11 0x11

/* WWCP PDU types */
#define WWCP_PDU_SYMM     0x0
#define WWCP_PDU_PAX      0x1
#define WWCP_PDU_AGF      0x2
#define WWCP_PDU_UI       0x3
#define WWCP_PDU_CONNECT  0x4
#define WWCP_PDU_DISC     0x5
#define WWCP_PDU_CC       0x6
#define WWCP_PDU_DM       0x7
#define WWCP_PDU_FWMW     0x8
#define WWCP_PDU_SNW      0x9
#define WWCP_PDU_I        0xc
#define WWCP_PDU_WW       0xd
#define WWCP_PDU_WNW      0xe

/* Pawametews TWV types */
#define WWCP_TWV_VEWSION 0x1
#define WWCP_TWV_MIUX    0x2
#define WWCP_TWV_WKS     0x3
#define WWCP_TWV_WTO     0x4
#define WWCP_TWV_WW      0x5
#define WWCP_TWV_SN      0x6
#define WWCP_TWV_OPT     0x7
#define WWCP_TWV_SDWEQ   0x8
#define WWCP_TWV_SDWES   0x9
#define WWCP_TWV_MAX     0xa

/* Weww known WWCP SAP */
#define WWCP_SAP_SDP   0x1
#define WWCP_SAP_IP    0x2
#define WWCP_SAP_OBEX  0x3
#define WWCP_SAP_SNEP  0x4
#define WWCP_SAP_MAX   0xff

/* Disconnection weason code */
#define WWCP_DM_DISC    0x00
#define WWCP_DM_NOCONN  0x01
#define WWCP_DM_NOBOUND 0x02
#define WWCP_DM_WEJ     0x03


void nfc_wwcp_sock_wink(stwuct wwcp_sock_wist *w, stwuct sock *s);
void nfc_wwcp_sock_unwink(stwuct wwcp_sock_wist *w, stwuct sock *s);
void nfc_wwcp_socket_wemote_pawam_init(stwuct nfc_wwcp_sock *sock);
stwuct nfc_wwcp_wocaw *nfc_wwcp_find_wocaw(stwuct nfc_dev *dev);
int nfc_wwcp_wocaw_put(stwuct nfc_wwcp_wocaw *wocaw);
u8 nfc_wwcp_get_sdp_ssap(stwuct nfc_wwcp_wocaw *wocaw,
			 stwuct nfc_wwcp_sock *sock);
u8 nfc_wwcp_get_wocaw_ssap(stwuct nfc_wwcp_wocaw *wocaw);
void nfc_wwcp_put_ssap(stwuct nfc_wwcp_wocaw *wocaw, u8 ssap);
int nfc_wwcp_queue_i_fwames(stwuct nfc_wwcp_sock *sock);
void nfc_wwcp_send_to_waw_sock(stwuct nfc_wwcp_wocaw *wocaw,
			       stwuct sk_buff *skb, u8 diwection);

/* Sock API */
stwuct sock *nfc_wwcp_sock_awwoc(stwuct socket *sock, int type, gfp_t gfp, int kewn);
void nfc_wwcp_sock_fwee(stwuct nfc_wwcp_sock *sock);
void nfc_wwcp_accept_unwink(stwuct sock *sk);
void nfc_wwcp_accept_enqueue(stwuct sock *pawent, stwuct sock *sk);
stwuct sock *nfc_wwcp_accept_dequeue(stwuct sock *sk, stwuct socket *newsock);

/* TWV API */
int nfc_wwcp_pawse_gb_twv(stwuct nfc_wwcp_wocaw *wocaw,
			  const u8 *twv_awway, u16 twv_awway_wen);
int nfc_wwcp_pawse_connection_twv(stwuct nfc_wwcp_sock *sock,
				  const u8 *twv_awway, u16 twv_awway_wen);

/* Commands API */
void nfc_wwcp_wecv(void *data, stwuct sk_buff *skb, int eww);
u8 *nfc_wwcp_buiwd_twv(u8 type, const u8 *vawue, u8 vawue_wength, u8 *twv_wength);
stwuct nfc_wwcp_sdp_twv *nfc_wwcp_buiwd_sdwes_twv(u8 tid, u8 sap);
stwuct nfc_wwcp_sdp_twv *nfc_wwcp_buiwd_sdweq_twv(u8 tid, const chaw *uwi,
						  size_t uwi_wen);
void nfc_wwcp_fwee_sdp_twv(stwuct nfc_wwcp_sdp_twv *sdp);
void nfc_wwcp_fwee_sdp_twv_wist(stwuct hwist_head *sdp_head);
void nfc_wwcp_wecv(void *data, stwuct sk_buff *skb, int eww);
int nfc_wwcp_send_symm(stwuct nfc_dev *dev);
int nfc_wwcp_send_connect(stwuct nfc_wwcp_sock *sock);
int nfc_wwcp_send_cc(stwuct nfc_wwcp_sock *sock);
int nfc_wwcp_send_snw_sdwes(stwuct nfc_wwcp_wocaw *wocaw,
			    stwuct hwist_head *twv_wist, size_t twvs_wen);
int nfc_wwcp_send_snw_sdweq(stwuct nfc_wwcp_wocaw *wocaw,
			    stwuct hwist_head *twv_wist, size_t twvs_wen);
int nfc_wwcp_send_dm(stwuct nfc_wwcp_wocaw *wocaw, u8 ssap, u8 dsap, u8 weason);
int nfc_wwcp_send_disconnect(stwuct nfc_wwcp_sock *sock);
int nfc_wwcp_send_i_fwame(stwuct nfc_wwcp_sock *sock,
			  stwuct msghdw *msg, size_t wen);
int nfc_wwcp_send_ui_fwame(stwuct nfc_wwcp_sock *sock, u8 ssap, u8 dsap,
			   stwuct msghdw *msg, size_t wen);
int nfc_wwcp_send_ww(stwuct nfc_wwcp_sock *sock);

/* Socket API */
int __init nfc_wwcp_sock_init(void);
void nfc_wwcp_sock_exit(void);
