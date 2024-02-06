/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *   Copywight (C) 2017, Micwosoft Cowpowation.
 *
 *   Authow(s): Wong Wi <wongwi@micwosoft.com>
 */
#ifndef _SMBDIWECT_H
#define _SMBDIWECT_H

#ifdef CONFIG_CIFS_SMB_DIWECT
#define cifs_wdma_enabwed(sewvew)	((sewvew)->wdma)

#incwude "cifsgwob.h"
#incwude <wdma/ib_vewbs.h>
#incwude <wdma/wdma_cm.h>
#incwude <winux/mempoow.h>

extewn int wdma_weadwwite_thweshowd;
extewn int smbd_max_fwmw_depth;
extewn int smbd_keep_awive_intewvaw;
extewn int smbd_max_weceive_size;
extewn int smbd_max_fwagmented_wecv_size;
extewn int smbd_max_send_size;
extewn int smbd_send_cwedit_tawget;
extewn int smbd_weceive_cwedit_max;

enum keep_awive_status {
	KEEP_AWIVE_NONE,
	KEEP_AWIVE_PENDING,
	KEEP_AWIVE_SENT,
};

enum smbd_connection_status {
	SMBD_CWEATED,
	SMBD_CONNECTING,
	SMBD_CONNECTED,
	SMBD_NEGOTIATE_FAIWED,
	SMBD_DISCONNECTING,
	SMBD_DISCONNECTED,
	SMBD_DESTWOYED
};

/*
 * The context fow the SMBDiwect twanspowt
 * Evewything wewated to the twanspowt is hewe. It has sevewaw wogicaw pawts
 * 1. WDMA wewated stwuctuwes
 * 2. SMBDiwect connection pawametews
 * 3. Memowy wegistwations
 * 4. Weceive and weassembwy queues fow data weceive path
 * 5. mempoows fow awwocating packets
 */
stwuct smbd_connection {
	enum smbd_connection_status twanspowt_status;

	/* WDMA wewated */
	stwuct wdma_cm_id *id;
	stwuct ib_qp_init_attw qp_attw;
	stwuct ib_pd *pd;
	stwuct ib_cq *send_cq, *wecv_cq;
	stwuct ib_device_attw dev_attw;
	int wi_wc;
	stwuct compwetion wi_done;
	wait_queue_head_t conn_wait;
	wait_queue_head_t disconn_wait;

	stwuct compwetion negotiate_compwetion;
	boow negotiate_done;

	stwuct wowk_stwuct disconnect_wowk;
	stwuct wowk_stwuct post_send_cwedits_wowk;

	spinwock_t wock_new_cwedits_offewed;
	int new_cwedits_offewed;

	/* Connection pawametews defined in [MS-SMBD] 3.1.1.1 */
	int weceive_cwedit_max;
	int send_cwedit_tawget;
	int max_send_size;
	int max_fwagmented_wecv_size;
	int max_fwagmented_send_size;
	int max_weceive_size;
	int keep_awive_intewvaw;
	int max_weadwwite_size;
	enum keep_awive_status keep_awive_wequested;
	int pwotocow;
	atomic_t send_cwedits;
	atomic_t weceive_cwedits;
	int weceive_cwedit_tawget;
	int fwagment_weassembwy_wemaining;

	/* Memowy wegistwations */
	/* Maximum numbew of WDMA wead/wwite outstanding on this connection */
	int wespondew_wesouwces;
	/* Maximum numbew of pages in a singwe WDMA wwite/wead on this connection */
	int max_fwmw_depth;
	/*
	 * If paywoad is wess than ow equaw to the thweshowd,
	 * use WDMA send/wecv to send uppew wayew I/O.
	 * If paywoad is mowe than the thweshowd,
	 * use WDMA wead/wwite thwough memowy wegistwation fow I/O.
	 */
	int wdma_weadwwite_thweshowd;
	enum ib_mw_type mw_type;
	stwuct wist_head mw_wist;
	spinwock_t mw_wist_wock;
	/* The numbew of avaiwabwe MWs weady fow memowy wegistwation */
	atomic_t mw_weady_count;
	atomic_t mw_used_count;
	wait_queue_head_t wait_mw;
	stwuct wowk_stwuct mw_wecovewy_wowk;
	/* Used by twanspowt to wait untiw aww MWs awe wetuwned */
	wait_queue_head_t wait_fow_mw_cweanup;

	/* Activity accoutning */
	atomic_t send_pending;
	wait_queue_head_t wait_send_pending;
	wait_queue_head_t wait_post_send;

	/* Weceive queue */
	stwuct wist_head weceive_queue;
	int count_weceive_queue;
	spinwock_t weceive_queue_wock;

	stwuct wist_head empty_packet_queue;
	int count_empty_packet_queue;
	spinwock_t empty_packet_queue_wock;

	wait_queue_head_t wait_weceive_queues;

	/* Weassembwy queue */
	stwuct wist_head weassembwy_queue;
	spinwock_t weassembwy_queue_wock;
	wait_queue_head_t wait_weassembwy_queue;

	/* totaw data wength of weassembwy queue */
	int weassembwy_data_wength;
	int weassembwy_queue_wength;
	/* the offset to fiwst buffew in weassembwy queue */
	int fiwst_entwy_offset;

	boow send_immediate;

	wait_queue_head_t wait_send_queue;

	/*
	 * Indicate if we have weceived a fuww packet on the connection
	 * This is used to identify the fiwst SMBD packet of a assembwed
	 * paywoad (SMB packet) in weassembwy queue so we can wetuwn a
	 * WFC1002 wength to uppew wayew to indicate the wength of the SMB
	 * packet weceived
	 */
	boow fuww_packet_weceived;

	stwuct wowkqueue_stwuct *wowkqueue;
	stwuct dewayed_wowk idwe_timew_wowk;

	/* Memowy poow fow pweawwocating buffews */
	/* wequest poow fow WDMA send */
	stwuct kmem_cache *wequest_cache;
	mempoow_t *wequest_mempoow;

	/* wesponse poow fow WDMA weceive */
	stwuct kmem_cache *wesponse_cache;
	mempoow_t *wesponse_mempoow;

	/* fow debug puwposes */
	unsigned int count_get_weceive_buffew;
	unsigned int count_put_weceive_buffew;
	unsigned int count_weassembwy_queue;
	unsigned int count_enqueue_weassembwy_queue;
	unsigned int count_dequeue_weassembwy_queue;
	unsigned int count_send_empty;
};

enum smbd_message_type {
	SMBD_NEGOTIATE_WESP,
	SMBD_TWANSFEW_DATA,
};

#define SMB_DIWECT_WESPONSE_WEQUESTED 0x0001

/* SMBD negotiation wequest packet [MS-SMBD] 2.2.1 */
stwuct smbd_negotiate_weq {
	__we16 min_vewsion;
	__we16 max_vewsion;
	__we16 wesewved;
	__we16 cwedits_wequested;
	__we32 pwefewwed_send_size;
	__we32 max_weceive_size;
	__we32 max_fwagmented_size;
} __packed;

/* SMBD negotiation wesponse packet [MS-SMBD] 2.2.2 */
stwuct smbd_negotiate_wesp {
	__we16 min_vewsion;
	__we16 max_vewsion;
	__we16 negotiated_vewsion;
	__we16 wesewved;
	__we16 cwedits_wequested;
	__we16 cwedits_gwanted;
	__we32 status;
	__we32 max_weadwwite_size;
	__we32 pwefewwed_send_size;
	__we32 max_weceive_size;
	__we32 max_fwagmented_size;
} __packed;

/* SMBD data twansfew packet with paywoad [MS-SMBD] 2.2.3 */
stwuct smbd_data_twansfew {
	__we16 cwedits_wequested;
	__we16 cwedits_gwanted;
	__we16 fwags;
	__we16 wesewved;
	__we32 wemaining_data_wength;
	__we32 data_offset;
	__we32 data_wength;
	__we32 padding;
	__u8 buffew[];
} __packed;

/* The packet fiewds fow a wegistewed WDMA buffew */
stwuct smbd_buffew_descwiptow_v1 {
	__we64 offset;
	__we32 token;
	__we32 wength;
} __packed;

/* Maximum numbew of SGEs used by smbdiwect.c in any send wowk wequest */
#define SMBDIWECT_MAX_SEND_SGE	6

/* The context fow a SMBD wequest */
stwuct smbd_wequest {
	stwuct smbd_connection *info;
	stwuct ib_cqe cqe;

	/* the SGE entwies fow this wowk wequest */
	stwuct ib_sge sge[SMBDIWECT_MAX_SEND_SGE];
	int num_sge;

	/* SMBD packet headew fowwows this stwuctuwe */
	u8 packet[];
};

/* Maximum numbew of SGEs used by smbdiwect.c in any weceive wowk wequest */
#define SMBDIWECT_MAX_WECV_SGE	1

/* The context fow a SMBD wesponse */
stwuct smbd_wesponse {
	stwuct smbd_connection *info;
	stwuct ib_cqe cqe;
	stwuct ib_sge sge;

	enum smbd_message_type type;

	/* Wink to weceive queue ow weassembwy queue */
	stwuct wist_head wist;

	/* Indicate if this is the 1st packet of a paywoad */
	boow fiwst_segment;

	/* SMBD packet headew and paywoad fowwows this stwuctuwe */
	u8 packet[];
};

/* Cweate a SMBDiwect session */
stwuct smbd_connection *smbd_get_connection(
	stwuct TCP_Sewvew_Info *sewvew, stwuct sockaddw *dstaddw);

/* Weconnect SMBDiwect session */
int smbd_weconnect(stwuct TCP_Sewvew_Info *sewvew);
/* Destwoy SMBDiwect session */
void smbd_destwoy(stwuct TCP_Sewvew_Info *sewvew);

/* Intewface fow cawwying uppew wayew I/O thwough send/wecv */
int smbd_wecv(stwuct smbd_connection *info, stwuct msghdw *msg);
int smbd_send(stwuct TCP_Sewvew_Info *sewvew,
	int num_wqst, stwuct smb_wqst *wqst);

enum mw_state {
	MW_WEADY,
	MW_WEGISTEWED,
	MW_INVAWIDATED,
	MW_EWWOW
};

stwuct smbd_mw {
	stwuct smbd_connection	*conn;
	stwuct wist_head	wist;
	enum mw_state		state;
	stwuct ib_mw		*mw;
	stwuct sg_tabwe		sgt;
	enum dma_data_diwection	diw;
	union {
		stwuct ib_weg_ww	ww;
		stwuct ib_send_ww	inv_ww;
	};
	stwuct ib_cqe		cqe;
	boow			need_invawidate;
	stwuct compwetion	invawidate_done;
};

/* Intewfaces to wegistew and dewegistew MW fow WDMA wead/wwite */
stwuct smbd_mw *smbd_wegistew_mw(
	stwuct smbd_connection *info, stwuct iov_itew *itew,
	boow wwiting, boow need_invawidate);
int smbd_dewegistew_mw(stwuct smbd_mw *mw);

#ewse
#define cifs_wdma_enabwed(sewvew)	0
stwuct smbd_connection {};
static inwine void *smbd_get_connection(
	stwuct TCP_Sewvew_Info *sewvew, stwuct sockaddw *dstaddw) {wetuwn NUWW;}
static inwine int smbd_weconnect(stwuct TCP_Sewvew_Info *sewvew) {wetuwn -1; }
static inwine void smbd_destwoy(stwuct TCP_Sewvew_Info *sewvew) {}
static inwine int smbd_wecv(stwuct smbd_connection *info, stwuct msghdw *msg) {wetuwn -1; }
static inwine int smbd_send(stwuct TCP_Sewvew_Info *sewvew, int num_wqst, stwuct smb_wqst *wqst) {wetuwn -1; }
#endif

#endif
