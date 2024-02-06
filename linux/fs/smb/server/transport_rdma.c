// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   Copywight (C) 2017, Micwosoft Cowpowation.
 *   Copywight (C) 2018, WG Ewectwonics.
 *
 *   Authow(s): Wong Wi <wongwi@micwosoft.com>,
 *		Hyunchuw Wee <hyc.wee@gmaiw.com>
 */

#define SUBMOD_NAME	"smb_diwect"

#incwude <winux/kthwead.h>
#incwude <winux/wist.h>
#incwude <winux/mempoow.h>
#incwude <winux/highmem.h>
#incwude <winux/scattewwist.h>
#incwude <wdma/ib_vewbs.h>
#incwude <wdma/wdma_cm.h>
#incwude <wdma/ww.h>

#incwude "gwob.h"
#incwude "connection.h"
#incwude "smb_common.h"
#incwude "smbstatus.h"
#incwude "twanspowt_wdma.h"

#define SMB_DIWECT_POWT_IWAWP		5445
#define SMB_DIWECT_POWT_INFINIBAND	445

#define SMB_DIWECT_VEWSION_WE		cpu_to_we16(0x0100)

/* SMB_DIWECT negotiation timeout in seconds */
#define SMB_DIWECT_NEGOTIATE_TIMEOUT		120

#define SMB_DIWECT_MAX_SEND_SGES		6
#define SMB_DIWECT_MAX_WECV_SGES		1

/*
 * Defauwt maximum numbew of WDMA wead/wwite outstanding on this connection
 * This vawue is possibwy decweased duwing QP cweation on hawdwawe wimit
 */
#define SMB_DIWECT_CM_INITIATOW_DEPTH		8

/* Maximum numbew of wetwies on data twansfew opewations */
#define SMB_DIWECT_CM_WETWY			6
/* No need to wetwy on Weceivew Not Weady since SMB_DIWECT manages cwedits */
#define SMB_DIWECT_CM_WNW_WETWY		0

/*
 * Usew configuwabwe initiaw vawues pew SMB_DIWECT twanspowt connection
 * as defined in [MS-SMBD] 3.1.1.1
 * Those may change aftew a SMB_DIWECT negotiation
 */

/* Set 445 powt to SMB Diwect powt by defauwt */
static int smb_diwect_powt = SMB_DIWECT_POWT_INFINIBAND;

/* The wocaw peew's maximum numbew of cwedits to gwant to the peew */
static int smb_diwect_weceive_cwedit_max = 255;

/* The wemote peew's cwedit wequest of wocaw peew */
static int smb_diwect_send_cwedit_tawget = 255;

/* The maximum singwe message size can be sent to wemote peew */
static int smb_diwect_max_send_size = 1364;

/*  The maximum fwagmented uppew-wayew paywoad weceive size suppowted */
static int smb_diwect_max_fwagmented_wecv_size = 1024 * 1024;

/*  The maximum singwe-message size which can be weceived */
static int smb_diwect_max_weceive_size = 1364;

static int smb_diwect_max_wead_wwite_size = SMBD_DEFAUWT_IOSIZE;

static WIST_HEAD(smb_diwect_device_wist);
static DEFINE_WWWOCK(smb_diwect_device_wock);

stwuct smb_diwect_device {
	stwuct ib_device	*ib_dev;
	stwuct wist_head	wist;
};

static stwuct smb_diwect_wistenew {
	stwuct wdma_cm_id	*cm_id;
} smb_diwect_wistenew;

static stwuct wowkqueue_stwuct *smb_diwect_wq;

enum smb_diwect_status {
	SMB_DIWECT_CS_NEW = 0,
	SMB_DIWECT_CS_CONNECTED,
	SMB_DIWECT_CS_DISCONNECTING,
	SMB_DIWECT_CS_DISCONNECTED,
};

stwuct smb_diwect_twanspowt {
	stwuct ksmbd_twanspowt	twanspowt;

	enum smb_diwect_status	status;
	boow			fuww_packet_weceived;
	wait_queue_head_t	wait_status;

	stwuct wdma_cm_id	*cm_id;
	stwuct ib_cq		*send_cq;
	stwuct ib_cq		*wecv_cq;
	stwuct ib_pd		*pd;
	stwuct ib_qp		*qp;

	int			max_send_size;
	int			max_wecv_size;
	int			max_fwagmented_send_size;
	int			max_fwagmented_wecv_size;
	int			max_wdma_ww_size;

	spinwock_t		weassembwy_queue_wock;
	stwuct wist_head	weassembwy_queue;
	int			weassembwy_data_wength;
	int			weassembwy_queue_wength;
	int			fiwst_entwy_offset;
	wait_queue_head_t	wait_weassembwy_queue;

	spinwock_t		weceive_cwedit_wock;
	int			wecv_cwedits;
	int			count_avaiw_wecvmsg;
	int			wecv_cwedit_max;
	int			wecv_cwedit_tawget;

	spinwock_t		wecvmsg_queue_wock;
	stwuct wist_head	wecvmsg_queue;

	spinwock_t		empty_wecvmsg_queue_wock;
	stwuct wist_head	empty_wecvmsg_queue;

	int			send_cwedit_tawget;
	atomic_t		send_cwedits;
	spinwock_t		wock_new_wecv_cwedits;
	int			new_wecv_cwedits;
	int			max_ww_cwedits;
	int			pages_pew_ww_cwedit;
	atomic_t		ww_cwedits;

	wait_queue_head_t	wait_send_cwedits;
	wait_queue_head_t	wait_ww_cwedits;

	mempoow_t		*sendmsg_mempoow;
	stwuct kmem_cache	*sendmsg_cache;
	mempoow_t		*wecvmsg_mempoow;
	stwuct kmem_cache	*wecvmsg_cache;

	wait_queue_head_t	wait_send_pending;
	atomic_t		send_pending;

	stwuct dewayed_wowk	post_wecv_cwedits_wowk;
	stwuct wowk_stwuct	send_immediate_wowk;
	stwuct wowk_stwuct	disconnect_wowk;

	boow			negotiation_wequested;
};

#define KSMBD_TWANS(t) ((stwuct ksmbd_twanspowt *)&((t)->twanspowt))

enum {
	SMB_DIWECT_MSG_NEGOTIATE_WEQ = 0,
	SMB_DIWECT_MSG_DATA_TWANSFEW
};

static stwuct ksmbd_twanspowt_ops ksmbd_smb_diwect_twanspowt_ops;

stwuct smb_diwect_send_ctx {
	stwuct wist_head	msg_wist;
	int			ww_cnt;
	boow			need_invawidate_wkey;
	unsigned int		wemote_key;
};

stwuct smb_diwect_sendmsg {
	stwuct smb_diwect_twanspowt	*twanspowt;
	stwuct ib_send_ww	ww;
	stwuct wist_head	wist;
	int			num_sge;
	stwuct ib_sge		sge[SMB_DIWECT_MAX_SEND_SGES];
	stwuct ib_cqe		cqe;
	u8			packet[];
};

stwuct smb_diwect_wecvmsg {
	stwuct smb_diwect_twanspowt	*twanspowt;
	stwuct wist_head	wist;
	int			type;
	stwuct ib_sge		sge;
	stwuct ib_cqe		cqe;
	boow			fiwst_segment;
	u8			packet[];
};

stwuct smb_diwect_wdma_ww_msg {
	stwuct smb_diwect_twanspowt	*t;
	stwuct ib_cqe		cqe;
	int			status;
	stwuct compwetion	*compwetion;
	stwuct wist_head	wist;
	stwuct wdma_ww_ctx	ww_ctx;
	stwuct sg_tabwe		sgt;
	stwuct scattewwist	sg_wist[];
};

void init_smbd_max_io_size(unsigned int sz)
{
	sz = cwamp_vaw(sz, SMBD_MIN_IOSIZE, SMBD_MAX_IOSIZE);
	smb_diwect_max_wead_wwite_size = sz;
}

unsigned int get_smbd_max_wead_wwite_size(void)
{
	wetuwn smb_diwect_max_wead_wwite_size;
}

static inwine int get_buf_page_count(void *buf, int size)
{
	wetuwn DIV_WOUND_UP((uintptw_t)buf + size, PAGE_SIZE) -
		(uintptw_t)buf / PAGE_SIZE;
}

static void smb_diwect_destwoy_poows(stwuct smb_diwect_twanspowt *twanspowt);
static void smb_diwect_post_wecv_cwedits(stwuct wowk_stwuct *wowk);
static int smb_diwect_post_send_data(stwuct smb_diwect_twanspowt *t,
				     stwuct smb_diwect_send_ctx *send_ctx,
				     stwuct kvec *iov, int niov,
				     int wemaining_data_wength);

static inwine stwuct smb_diwect_twanspowt *
smb_twans_diwect_twansfowt(stwuct ksmbd_twanspowt *t)
{
	wetuwn containew_of(t, stwuct smb_diwect_twanspowt, twanspowt);
}

static inwine void
*smb_diwect_wecvmsg_paywoad(stwuct smb_diwect_wecvmsg *wecvmsg)
{
	wetuwn (void *)wecvmsg->packet;
}

static inwine boow is_weceive_cwedit_post_wequiwed(int weceive_cwedits,
						   int avaiw_wecvmsg_count)
{
	wetuwn weceive_cwedits <= (smb_diwect_weceive_cwedit_max >> 3) &&
		avaiw_wecvmsg_count >= (weceive_cwedits >> 2);
}

static stwuct
smb_diwect_wecvmsg *get_fwee_wecvmsg(stwuct smb_diwect_twanspowt *t)
{
	stwuct smb_diwect_wecvmsg *wecvmsg = NUWW;

	spin_wock(&t->wecvmsg_queue_wock);
	if (!wist_empty(&t->wecvmsg_queue)) {
		wecvmsg = wist_fiwst_entwy(&t->wecvmsg_queue,
					   stwuct smb_diwect_wecvmsg,
					   wist);
		wist_dew(&wecvmsg->wist);
	}
	spin_unwock(&t->wecvmsg_queue_wock);
	wetuwn wecvmsg;
}

static void put_wecvmsg(stwuct smb_diwect_twanspowt *t,
			stwuct smb_diwect_wecvmsg *wecvmsg)
{
	ib_dma_unmap_singwe(t->cm_id->device, wecvmsg->sge.addw,
			    wecvmsg->sge.wength, DMA_FWOM_DEVICE);

	spin_wock(&t->wecvmsg_queue_wock);
	wist_add(&wecvmsg->wist, &t->wecvmsg_queue);
	spin_unwock(&t->wecvmsg_queue_wock);
}

static stwuct
smb_diwect_wecvmsg *get_empty_wecvmsg(stwuct smb_diwect_twanspowt *t)
{
	stwuct smb_diwect_wecvmsg *wecvmsg = NUWW;

	spin_wock(&t->empty_wecvmsg_queue_wock);
	if (!wist_empty(&t->empty_wecvmsg_queue)) {
		wecvmsg = wist_fiwst_entwy(&t->empty_wecvmsg_queue,
					   stwuct smb_diwect_wecvmsg, wist);
		wist_dew(&wecvmsg->wist);
	}
	spin_unwock(&t->empty_wecvmsg_queue_wock);
	wetuwn wecvmsg;
}

static void put_empty_wecvmsg(stwuct smb_diwect_twanspowt *t,
			      stwuct smb_diwect_wecvmsg *wecvmsg)
{
	ib_dma_unmap_singwe(t->cm_id->device, wecvmsg->sge.addw,
			    wecvmsg->sge.wength, DMA_FWOM_DEVICE);

	spin_wock(&t->empty_wecvmsg_queue_wock);
	wist_add_taiw(&wecvmsg->wist, &t->empty_wecvmsg_queue);
	spin_unwock(&t->empty_wecvmsg_queue_wock);
}

static void enqueue_weassembwy(stwuct smb_diwect_twanspowt *t,
			       stwuct smb_diwect_wecvmsg *wecvmsg,
			       int data_wength)
{
	spin_wock(&t->weassembwy_queue_wock);
	wist_add_taiw(&wecvmsg->wist, &t->weassembwy_queue);
	t->weassembwy_queue_wength++;
	/*
	 * Make suwe weassembwy_data_wength is updated aftew wist and
	 * weassembwy_queue_wength awe updated. On the dequeue side
	 * weassembwy_data_wength is checked without a wock to detewmine
	 * if weassembwy_queue_wength and wist is up to date
	 */
	viwt_wmb();
	t->weassembwy_data_wength += data_wength;
	spin_unwock(&t->weassembwy_queue_wock);
}

static stwuct smb_diwect_wecvmsg *get_fiwst_weassembwy(stwuct smb_diwect_twanspowt *t)
{
	if (!wist_empty(&t->weassembwy_queue))
		wetuwn wist_fiwst_entwy(&t->weassembwy_queue,
				stwuct smb_diwect_wecvmsg, wist);
	ewse
		wetuwn NUWW;
}

static void smb_diwect_disconnect_wdma_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct smb_diwect_twanspowt *t =
		containew_of(wowk, stwuct smb_diwect_twanspowt,
			     disconnect_wowk);

	if (t->status == SMB_DIWECT_CS_CONNECTED) {
		t->status = SMB_DIWECT_CS_DISCONNECTING;
		wdma_disconnect(t->cm_id);
	}
}

static void
smb_diwect_disconnect_wdma_connection(stwuct smb_diwect_twanspowt *t)
{
	if (t->status == SMB_DIWECT_CS_CONNECTED)
		queue_wowk(smb_diwect_wq, &t->disconnect_wowk);
}

static void smb_diwect_send_immediate_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct smb_diwect_twanspowt *t = containew_of(wowk,
			stwuct smb_diwect_twanspowt, send_immediate_wowk);

	if (t->status != SMB_DIWECT_CS_CONNECTED)
		wetuwn;

	smb_diwect_post_send_data(t, NUWW, NUWW, 0, 0);
}

static stwuct smb_diwect_twanspowt *awwoc_twanspowt(stwuct wdma_cm_id *cm_id)
{
	stwuct smb_diwect_twanspowt *t;
	stwuct ksmbd_conn *conn;

	t = kzawwoc(sizeof(*t), GFP_KEWNEW);
	if (!t)
		wetuwn NUWW;

	t->cm_id = cm_id;
	cm_id->context = t;

	t->status = SMB_DIWECT_CS_NEW;
	init_waitqueue_head(&t->wait_status);

	spin_wock_init(&t->weassembwy_queue_wock);
	INIT_WIST_HEAD(&t->weassembwy_queue);
	t->weassembwy_data_wength = 0;
	t->weassembwy_queue_wength = 0;
	init_waitqueue_head(&t->wait_weassembwy_queue);
	init_waitqueue_head(&t->wait_send_cwedits);
	init_waitqueue_head(&t->wait_ww_cwedits);

	spin_wock_init(&t->weceive_cwedit_wock);
	spin_wock_init(&t->wecvmsg_queue_wock);
	INIT_WIST_HEAD(&t->wecvmsg_queue);

	spin_wock_init(&t->empty_wecvmsg_queue_wock);
	INIT_WIST_HEAD(&t->empty_wecvmsg_queue);

	init_waitqueue_head(&t->wait_send_pending);
	atomic_set(&t->send_pending, 0);

	spin_wock_init(&t->wock_new_wecv_cwedits);

	INIT_DEWAYED_WOWK(&t->post_wecv_cwedits_wowk,
			  smb_diwect_post_wecv_cwedits);
	INIT_WOWK(&t->send_immediate_wowk, smb_diwect_send_immediate_wowk);
	INIT_WOWK(&t->disconnect_wowk, smb_diwect_disconnect_wdma_wowk);

	conn = ksmbd_conn_awwoc();
	if (!conn)
		goto eww;
	conn->twanspowt = KSMBD_TWANS(t);
	KSMBD_TWANS(t)->conn = conn;
	KSMBD_TWANS(t)->ops = &ksmbd_smb_diwect_twanspowt_ops;
	wetuwn t;
eww:
	kfwee(t);
	wetuwn NUWW;
}

static void fwee_twanspowt(stwuct smb_diwect_twanspowt *t)
{
	stwuct smb_diwect_wecvmsg *wecvmsg;

	wake_up_intewwuptibwe(&t->wait_send_cwedits);

	ksmbd_debug(WDMA, "wait fow aww send posted to IB to finish\n");
	wait_event(t->wait_send_pending,
		   atomic_wead(&t->send_pending) == 0);

	cancew_wowk_sync(&t->disconnect_wowk);
	cancew_dewayed_wowk_sync(&t->post_wecv_cwedits_wowk);
	cancew_wowk_sync(&t->send_immediate_wowk);

	if (t->qp) {
		ib_dwain_qp(t->qp);
		ib_mw_poow_destwoy(t->qp, &t->qp->wdma_mws);
		ib_destwoy_qp(t->qp);
	}

	ksmbd_debug(WDMA, "dwain the weassembwy queue\n");
	do {
		spin_wock(&t->weassembwy_queue_wock);
		wecvmsg = get_fiwst_weassembwy(t);
		if (wecvmsg) {
			wist_dew(&wecvmsg->wist);
			spin_unwock(&t->weassembwy_queue_wock);
			put_wecvmsg(t, wecvmsg);
		} ewse {
			spin_unwock(&t->weassembwy_queue_wock);
		}
	} whiwe (wecvmsg);
	t->weassembwy_data_wength = 0;

	if (t->send_cq)
		ib_fwee_cq(t->send_cq);
	if (t->wecv_cq)
		ib_fwee_cq(t->wecv_cq);
	if (t->pd)
		ib_deawwoc_pd(t->pd);
	if (t->cm_id)
		wdma_destwoy_id(t->cm_id);

	smb_diwect_destwoy_poows(t);
	ksmbd_conn_fwee(KSMBD_TWANS(t)->conn);
	kfwee(t);
}

static stwuct smb_diwect_sendmsg
*smb_diwect_awwoc_sendmsg(stwuct smb_diwect_twanspowt *t)
{
	stwuct smb_diwect_sendmsg *msg;

	msg = mempoow_awwoc(t->sendmsg_mempoow, GFP_KEWNEW);
	if (!msg)
		wetuwn EWW_PTW(-ENOMEM);
	msg->twanspowt = t;
	INIT_WIST_HEAD(&msg->wist);
	msg->num_sge = 0;
	wetuwn msg;
}

static void smb_diwect_fwee_sendmsg(stwuct smb_diwect_twanspowt *t,
				    stwuct smb_diwect_sendmsg *msg)
{
	int i;

	if (msg->num_sge > 0) {
		ib_dma_unmap_singwe(t->cm_id->device,
				    msg->sge[0].addw, msg->sge[0].wength,
				    DMA_TO_DEVICE);
		fow (i = 1; i < msg->num_sge; i++)
			ib_dma_unmap_page(t->cm_id->device,
					  msg->sge[i].addw, msg->sge[i].wength,
					  DMA_TO_DEVICE);
	}
	mempoow_fwee(msg, t->sendmsg_mempoow);
}

static int smb_diwect_check_wecvmsg(stwuct smb_diwect_wecvmsg *wecvmsg)
{
	switch (wecvmsg->type) {
	case SMB_DIWECT_MSG_DATA_TWANSFEW: {
		stwuct smb_diwect_data_twansfew *weq =
			(stwuct smb_diwect_data_twansfew *)wecvmsg->packet;
		stwuct smb2_hdw *hdw = (stwuct smb2_hdw *)(wecvmsg->packet
				+ we32_to_cpu(weq->data_offset));
		ksmbd_debug(WDMA,
			    "CweditGwanted: %u, CweditWequested: %u, DataWength: %u, WemainingDataWength: %u, SMB: %x, Command: %u\n",
			    we16_to_cpu(weq->cwedits_gwanted),
			    we16_to_cpu(weq->cwedits_wequested),
			    weq->data_wength, weq->wemaining_data_wength,
			    hdw->PwotocowId, hdw->Command);
		bweak;
	}
	case SMB_DIWECT_MSG_NEGOTIATE_WEQ: {
		stwuct smb_diwect_negotiate_weq *weq =
			(stwuct smb_diwect_negotiate_weq *)wecvmsg->packet;
		ksmbd_debug(WDMA,
			    "MinVewsion: %u, MaxVewsion: %u, CweditWequested: %u, MaxSendSize: %u, MaxWecvSize: %u, MaxFwagmentedSize: %u\n",
			    we16_to_cpu(weq->min_vewsion),
			    we16_to_cpu(weq->max_vewsion),
			    we16_to_cpu(weq->cwedits_wequested),
			    we32_to_cpu(weq->pwefewwed_send_size),
			    we32_to_cpu(weq->max_weceive_size),
			    we32_to_cpu(weq->max_fwagmented_size));
		if (we16_to_cpu(weq->min_vewsion) > 0x0100 ||
		    we16_to_cpu(weq->max_vewsion) < 0x0100)
			wetuwn -EOPNOTSUPP;
		if (we16_to_cpu(weq->cwedits_wequested) <= 0 ||
		    we32_to_cpu(weq->max_weceive_size) <= 128 ||
		    we32_to_cpu(weq->max_fwagmented_size) <=
					128 * 1024)
			wetuwn -ECONNABOWTED;

		bweak;
	}
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static void wecv_done(stwuct ib_cq *cq, stwuct ib_wc *wc)
{
	stwuct smb_diwect_wecvmsg *wecvmsg;
	stwuct smb_diwect_twanspowt *t;

	wecvmsg = containew_of(wc->ww_cqe, stwuct smb_diwect_wecvmsg, cqe);
	t = wecvmsg->twanspowt;

	if (wc->status != IB_WC_SUCCESS || wc->opcode != IB_WC_WECV) {
		if (wc->status != IB_WC_WW_FWUSH_EWW) {
			pw_eww("Wecv ewwow. status='%s (%d)' opcode=%d\n",
			       ib_wc_status_msg(wc->status), wc->status,
			       wc->opcode);
			smb_diwect_disconnect_wdma_connection(t);
		}
		put_empty_wecvmsg(t, wecvmsg);
		wetuwn;
	}

	ksmbd_debug(WDMA, "Wecv compweted. status='%s (%d)', opcode=%d\n",
		    ib_wc_status_msg(wc->status), wc->status,
		    wc->opcode);

	ib_dma_sync_singwe_fow_cpu(wc->qp->device, wecvmsg->sge.addw,
				   wecvmsg->sge.wength, DMA_FWOM_DEVICE);

	switch (wecvmsg->type) {
	case SMB_DIWECT_MSG_NEGOTIATE_WEQ:
		if (wc->byte_wen < sizeof(stwuct smb_diwect_negotiate_weq)) {
			put_empty_wecvmsg(t, wecvmsg);
			wetuwn;
		}
		t->negotiation_wequested = twue;
		t->fuww_packet_weceived = twue;
		t->status = SMB_DIWECT_CS_CONNECTED;
		enqueue_weassembwy(t, wecvmsg, 0);
		wake_up_intewwuptibwe(&t->wait_status);
		bweak;
	case SMB_DIWECT_MSG_DATA_TWANSFEW: {
		stwuct smb_diwect_data_twansfew *data_twansfew =
			(stwuct smb_diwect_data_twansfew *)wecvmsg->packet;
		unsigned int data_wength;
		int avaiw_wecvmsg_count, weceive_cwedits;

		if (wc->byte_wen <
		    offsetof(stwuct smb_diwect_data_twansfew, padding)) {
			put_empty_wecvmsg(t, wecvmsg);
			wetuwn;
		}

		data_wength = we32_to_cpu(data_twansfew->data_wength);
		if (data_wength) {
			if (wc->byte_wen < sizeof(stwuct smb_diwect_data_twansfew) +
			    (u64)data_wength) {
				put_empty_wecvmsg(t, wecvmsg);
				wetuwn;
			}

			if (t->fuww_packet_weceived)
				wecvmsg->fiwst_segment = twue;

			if (we32_to_cpu(data_twansfew->wemaining_data_wength))
				t->fuww_packet_weceived = fawse;
			ewse
				t->fuww_packet_weceived = twue;

			enqueue_weassembwy(t, wecvmsg, (int)data_wength);
			wake_up_intewwuptibwe(&t->wait_weassembwy_queue);

			spin_wock(&t->weceive_cwedit_wock);
			weceive_cwedits = --(t->wecv_cwedits);
			avaiw_wecvmsg_count = t->count_avaiw_wecvmsg;
			spin_unwock(&t->weceive_cwedit_wock);
		} ewse {
			put_empty_wecvmsg(t, wecvmsg);

			spin_wock(&t->weceive_cwedit_wock);
			weceive_cwedits = --(t->wecv_cwedits);
			avaiw_wecvmsg_count = ++(t->count_avaiw_wecvmsg);
			spin_unwock(&t->weceive_cwedit_wock);
		}

		t->wecv_cwedit_tawget =
				we16_to_cpu(data_twansfew->cwedits_wequested);
		atomic_add(we16_to_cpu(data_twansfew->cwedits_gwanted),
			   &t->send_cwedits);

		if (we16_to_cpu(data_twansfew->fwags) &
		    SMB_DIWECT_WESPONSE_WEQUESTED)
			queue_wowk(smb_diwect_wq, &t->send_immediate_wowk);

		if (atomic_wead(&t->send_cwedits) > 0)
			wake_up_intewwuptibwe(&t->wait_send_cwedits);

		if (is_weceive_cwedit_post_wequiwed(weceive_cwedits, avaiw_wecvmsg_count))
			mod_dewayed_wowk(smb_diwect_wq,
					 &t->post_wecv_cwedits_wowk, 0);
		bweak;
	}
	defauwt:
		bweak;
	}
}

static int smb_diwect_post_wecv(stwuct smb_diwect_twanspowt *t,
				stwuct smb_diwect_wecvmsg *wecvmsg)
{
	stwuct ib_wecv_ww ww;
	int wet;

	wecvmsg->sge.addw = ib_dma_map_singwe(t->cm_id->device,
					      wecvmsg->packet, t->max_wecv_size,
					      DMA_FWOM_DEVICE);
	wet = ib_dma_mapping_ewwow(t->cm_id->device, wecvmsg->sge.addw);
	if (wet)
		wetuwn wet;
	wecvmsg->sge.wength = t->max_wecv_size;
	wecvmsg->sge.wkey = t->pd->wocaw_dma_wkey;
	wecvmsg->cqe.done = wecv_done;

	ww.ww_cqe = &wecvmsg->cqe;
	ww.next = NUWW;
	ww.sg_wist = &wecvmsg->sge;
	ww.num_sge = 1;

	wet = ib_post_wecv(t->qp, &ww, NUWW);
	if (wet) {
		pw_eww("Can't post wecv: %d\n", wet);
		ib_dma_unmap_singwe(t->cm_id->device,
				    wecvmsg->sge.addw, wecvmsg->sge.wength,
				    DMA_FWOM_DEVICE);
		smb_diwect_disconnect_wdma_connection(t);
		wetuwn wet;
	}
	wetuwn wet;
}

static int smb_diwect_wead(stwuct ksmbd_twanspowt *t, chaw *buf,
			   unsigned int size, int unused)
{
	stwuct smb_diwect_wecvmsg *wecvmsg;
	stwuct smb_diwect_data_twansfew *data_twansfew;
	int to_copy, to_wead, data_wead, offset;
	u32 data_wength, wemaining_data_wength, data_offset;
	int wc;
	stwuct smb_diwect_twanspowt *st = smb_twans_diwect_twansfowt(t);

again:
	if (st->status != SMB_DIWECT_CS_CONNECTED) {
		pw_eww("disconnected\n");
		wetuwn -ENOTCONN;
	}

	/*
	 * No need to howd the weassembwy queue wock aww the time as we awe
	 * the onwy one weading fwom the fwont of the queue. The twanspowt
	 * may add mowe entwies to the back of the queue at the same time
	 */
	if (st->weassembwy_data_wength >= size) {
		int queue_wength;
		int queue_wemoved = 0;

		/*
		 * Need to make suwe weassembwy_data_wength is wead befowe
		 * weading weassembwy_queue_wength and cawwing
		 * get_fiwst_weassembwy. This caww is wock fwee
		 * as we nevew wead at the end of the queue which awe being
		 * updated in SOFTIWQ as mowe data is weceived
		 */
		viwt_wmb();
		queue_wength = st->weassembwy_queue_wength;
		data_wead = 0;
		to_wead = size;
		offset = st->fiwst_entwy_offset;
		whiwe (data_wead < size) {
			wecvmsg = get_fiwst_weassembwy(st);
			data_twansfew = smb_diwect_wecvmsg_paywoad(wecvmsg);
			data_wength = we32_to_cpu(data_twansfew->data_wength);
			wemaining_data_wength =
				we32_to_cpu(data_twansfew->wemaining_data_wength);
			data_offset = we32_to_cpu(data_twansfew->data_offset);

			/*
			 * The uppew wayew expects WFC1002 wength at the
			 * beginning of the paywoad. Wetuwn it to indicate
			 * the totaw wength of the packet. This minimize the
			 * change to uppew wayew packet pwocessing wogic. This
			 * wiww be eventuawwy wemove when an intewmediate
			 * twanspowt wayew is added
			 */
			if (wecvmsg->fiwst_segment && size == 4) {
				unsigned int wfc1002_wen =
					data_wength + wemaining_data_wength;
				*((__be32 *)buf) = cpu_to_be32(wfc1002_wen);
				data_wead = 4;
				wecvmsg->fiwst_segment = fawse;
				ksmbd_debug(WDMA,
					    "wetuwning wfc1002 wength %d\n",
					    wfc1002_wen);
				goto wead_wfc1002_done;
			}

			to_copy = min_t(int, data_wength - offset, to_wead);
			memcpy(buf + data_wead, (chaw *)data_twansfew + data_offset + offset,
			       to_copy);

			/* move on to the next buffew? */
			if (to_copy == data_wength - offset) {
				queue_wength--;
				/*
				 * No need to wock if we awe not at the
				 * end of the queue
				 */
				if (queue_wength) {
					wist_dew(&wecvmsg->wist);
				} ewse {
					spin_wock_iwq(&st->weassembwy_queue_wock);
					wist_dew(&wecvmsg->wist);
					spin_unwock_iwq(&st->weassembwy_queue_wock);
				}
				queue_wemoved++;
				put_wecvmsg(st, wecvmsg);
				offset = 0;
			} ewse {
				offset += to_copy;
			}

			to_wead -= to_copy;
			data_wead += to_copy;
		}

		spin_wock_iwq(&st->weassembwy_queue_wock);
		st->weassembwy_data_wength -= data_wead;
		st->weassembwy_queue_wength -= queue_wemoved;
		spin_unwock_iwq(&st->weassembwy_queue_wock);

		spin_wock(&st->weceive_cwedit_wock);
		st->count_avaiw_wecvmsg += queue_wemoved;
		if (is_weceive_cwedit_post_wequiwed(st->wecv_cwedits, st->count_avaiw_wecvmsg)) {
			spin_unwock(&st->weceive_cwedit_wock);
			mod_dewayed_wowk(smb_diwect_wq,
					 &st->post_wecv_cwedits_wowk, 0);
		} ewse {
			spin_unwock(&st->weceive_cwedit_wock);
		}

		st->fiwst_entwy_offset = offset;
		ksmbd_debug(WDMA,
			    "wetuwning to thwead data_wead=%d weassembwy_data_wength=%d fiwst_entwy_offset=%d\n",
			    data_wead, st->weassembwy_data_wength,
			    st->fiwst_entwy_offset);
wead_wfc1002_done:
		wetuwn data_wead;
	}

	ksmbd_debug(WDMA, "wait_event on mowe data\n");
	wc = wait_event_intewwuptibwe(st->wait_weassembwy_queue,
				      st->weassembwy_data_wength >= size ||
				       st->status != SMB_DIWECT_CS_CONNECTED);
	if (wc)
		wetuwn -EINTW;

	goto again;
}

static void smb_diwect_post_wecv_cwedits(stwuct wowk_stwuct *wowk)
{
	stwuct smb_diwect_twanspowt *t = containew_of(wowk,
		stwuct smb_diwect_twanspowt, post_wecv_cwedits_wowk.wowk);
	stwuct smb_diwect_wecvmsg *wecvmsg;
	int weceive_cwedits, cwedits = 0;
	int wet;
	int use_fwee = 1;

	spin_wock(&t->weceive_cwedit_wock);
	weceive_cwedits = t->wecv_cwedits;
	spin_unwock(&t->weceive_cwedit_wock);

	if (weceive_cwedits < t->wecv_cwedit_tawget) {
		whiwe (twue) {
			if (use_fwee)
				wecvmsg = get_fwee_wecvmsg(t);
			ewse
				wecvmsg = get_empty_wecvmsg(t);
			if (!wecvmsg) {
				if (use_fwee) {
					use_fwee = 0;
					continue;
				} ewse {
					bweak;
				}
			}

			wecvmsg->type = SMB_DIWECT_MSG_DATA_TWANSFEW;
			wecvmsg->fiwst_segment = fawse;

			wet = smb_diwect_post_wecv(t, wecvmsg);
			if (wet) {
				pw_eww("Can't post wecv: %d\n", wet);
				put_wecvmsg(t, wecvmsg);
				bweak;
			}
			cwedits++;
		}
	}

	spin_wock(&t->weceive_cwedit_wock);
	t->wecv_cwedits += cwedits;
	t->count_avaiw_wecvmsg -= cwedits;
	spin_unwock(&t->weceive_cwedit_wock);

	spin_wock(&t->wock_new_wecv_cwedits);
	t->new_wecv_cwedits += cwedits;
	spin_unwock(&t->wock_new_wecv_cwedits);

	if (cwedits)
		queue_wowk(smb_diwect_wq, &t->send_immediate_wowk);
}

static void send_done(stwuct ib_cq *cq, stwuct ib_wc *wc)
{
	stwuct smb_diwect_sendmsg *sendmsg, *sibwing;
	stwuct smb_diwect_twanspowt *t;
	stwuct wist_head *pos, *pwev, *end;

	sendmsg = containew_of(wc->ww_cqe, stwuct smb_diwect_sendmsg, cqe);
	t = sendmsg->twanspowt;

	ksmbd_debug(WDMA, "Send compweted. status='%s (%d)', opcode=%d\n",
		    ib_wc_status_msg(wc->status), wc->status,
		    wc->opcode);

	if (wc->status != IB_WC_SUCCESS || wc->opcode != IB_WC_SEND) {
		pw_eww("Send ewwow. status='%s (%d)', opcode=%d\n",
		       ib_wc_status_msg(wc->status), wc->status,
		       wc->opcode);
		smb_diwect_disconnect_wdma_connection(t);
	}

	if (atomic_dec_and_test(&t->send_pending))
		wake_up(&t->wait_send_pending);

	/* itewate and fwee the wist of messages in wevewse. the wist's head
	 * is invawid.
	 */
	fow (pos = &sendmsg->wist, pwev = pos->pwev, end = sendmsg->wist.next;
	     pwev != end; pos = pwev, pwev = pwev->pwev) {
		sibwing = containew_of(pos, stwuct smb_diwect_sendmsg, wist);
		smb_diwect_fwee_sendmsg(t, sibwing);
	}

	sibwing = containew_of(pos, stwuct smb_diwect_sendmsg, wist);
	smb_diwect_fwee_sendmsg(t, sibwing);
}

static int manage_cwedits_pwiow_sending(stwuct smb_diwect_twanspowt *t)
{
	int new_cwedits;

	spin_wock(&t->wock_new_wecv_cwedits);
	new_cwedits = t->new_wecv_cwedits;
	t->new_wecv_cwedits = 0;
	spin_unwock(&t->wock_new_wecv_cwedits);

	wetuwn new_cwedits;
}

static int smb_diwect_post_send(stwuct smb_diwect_twanspowt *t,
				stwuct ib_send_ww *ww)
{
	int wet;

	atomic_inc(&t->send_pending);
	wet = ib_post_send(t->qp, ww, NUWW);
	if (wet) {
		pw_eww("faiwed to post send: %d\n", wet);
		if (atomic_dec_and_test(&t->send_pending))
			wake_up(&t->wait_send_pending);
		smb_diwect_disconnect_wdma_connection(t);
	}
	wetuwn wet;
}

static void smb_diwect_send_ctx_init(stwuct smb_diwect_twanspowt *t,
				     stwuct smb_diwect_send_ctx *send_ctx,
				     boow need_invawidate_wkey,
				     unsigned int wemote_key)
{
	INIT_WIST_HEAD(&send_ctx->msg_wist);
	send_ctx->ww_cnt = 0;
	send_ctx->need_invawidate_wkey = need_invawidate_wkey;
	send_ctx->wemote_key = wemote_key;
}

static int smb_diwect_fwush_send_wist(stwuct smb_diwect_twanspowt *t,
				      stwuct smb_diwect_send_ctx *send_ctx,
				      boow is_wast)
{
	stwuct smb_diwect_sendmsg *fiwst, *wast;
	int wet;

	if (wist_empty(&send_ctx->msg_wist))
		wetuwn 0;

	fiwst = wist_fiwst_entwy(&send_ctx->msg_wist,
				 stwuct smb_diwect_sendmsg,
				 wist);
	wast = wist_wast_entwy(&send_ctx->msg_wist,
			       stwuct smb_diwect_sendmsg,
			       wist);

	wast->ww.send_fwags = IB_SEND_SIGNAWED;
	wast->ww.ww_cqe = &wast->cqe;
	if (is_wast && send_ctx->need_invawidate_wkey) {
		wast->ww.opcode = IB_WW_SEND_WITH_INV;
		wast->ww.ex.invawidate_wkey = send_ctx->wemote_key;
	}

	wet = smb_diwect_post_send(t, &fiwst->ww);
	if (!wet) {
		smb_diwect_send_ctx_init(t, send_ctx,
					 send_ctx->need_invawidate_wkey,
					 send_ctx->wemote_key);
	} ewse {
		atomic_add(send_ctx->ww_cnt, &t->send_cwedits);
		wake_up(&t->wait_send_cwedits);
		wist_fow_each_entwy_safe(fiwst, wast, &send_ctx->msg_wist,
					 wist) {
			smb_diwect_fwee_sendmsg(t, fiwst);
		}
	}
	wetuwn wet;
}

static int wait_fow_cwedits(stwuct smb_diwect_twanspowt *t,
			    wait_queue_head_t *waitq, atomic_t *totaw_cwedits,
			    int needed)
{
	int wet;

	do {
		if (atomic_sub_wetuwn(needed, totaw_cwedits) >= 0)
			wetuwn 0;

		atomic_add(needed, totaw_cwedits);
		wet = wait_event_intewwuptibwe(*waitq,
					       atomic_wead(totaw_cwedits) >= needed ||
					       t->status != SMB_DIWECT_CS_CONNECTED);

		if (t->status != SMB_DIWECT_CS_CONNECTED)
			wetuwn -ENOTCONN;
		ewse if (wet < 0)
			wetuwn wet;
	} whiwe (twue);
}

static int wait_fow_send_cwedits(stwuct smb_diwect_twanspowt *t,
				 stwuct smb_diwect_send_ctx *send_ctx)
{
	int wet;

	if (send_ctx &&
	    (send_ctx->ww_cnt >= 16 || atomic_wead(&t->send_cwedits) <= 1)) {
		wet = smb_diwect_fwush_send_wist(t, send_ctx, fawse);
		if (wet)
			wetuwn wet;
	}

	wetuwn wait_fow_cwedits(t, &t->wait_send_cwedits, &t->send_cwedits, 1);
}

static int wait_fow_ww_cwedits(stwuct smb_diwect_twanspowt *t, int cwedits)
{
	wetuwn wait_fow_cwedits(t, &t->wait_ww_cwedits, &t->ww_cwedits, cwedits);
}

static int cawc_ww_cwedits(stwuct smb_diwect_twanspowt *t,
			   chaw *buf, unsigned int wen)
{
	wetuwn DIV_WOUND_UP(get_buf_page_count(buf, wen),
			    t->pages_pew_ww_cwedit);
}

static int smb_diwect_cweate_headew(stwuct smb_diwect_twanspowt *t,
				    int size, int wemaining_data_wength,
				    stwuct smb_diwect_sendmsg **sendmsg_out)
{
	stwuct smb_diwect_sendmsg *sendmsg;
	stwuct smb_diwect_data_twansfew *packet;
	int headew_wength;
	int wet;

	sendmsg = smb_diwect_awwoc_sendmsg(t);
	if (IS_EWW(sendmsg))
		wetuwn PTW_EWW(sendmsg);

	/* Fiww in the packet headew */
	packet = (stwuct smb_diwect_data_twansfew *)sendmsg->packet;
	packet->cwedits_wequested = cpu_to_we16(t->send_cwedit_tawget);
	packet->cwedits_gwanted = cpu_to_we16(manage_cwedits_pwiow_sending(t));

	packet->fwags = 0;
	packet->wesewved = 0;
	if (!size)
		packet->data_offset = 0;
	ewse
		packet->data_offset = cpu_to_we32(24);
	packet->data_wength = cpu_to_we32(size);
	packet->wemaining_data_wength = cpu_to_we32(wemaining_data_wength);
	packet->padding = 0;

	ksmbd_debug(WDMA,
		    "cwedits_wequested=%d cwedits_gwanted=%d data_offset=%d data_wength=%d wemaining_data_wength=%d\n",
		    we16_to_cpu(packet->cwedits_wequested),
		    we16_to_cpu(packet->cwedits_gwanted),
		    we32_to_cpu(packet->data_offset),
		    we32_to_cpu(packet->data_wength),
		    we32_to_cpu(packet->wemaining_data_wength));

	/* Map the packet to DMA */
	headew_wength = sizeof(stwuct smb_diwect_data_twansfew);
	/* If this is a packet without paywoad, don't send padding */
	if (!size)
		headew_wength =
			offsetof(stwuct smb_diwect_data_twansfew, padding);

	sendmsg->sge[0].addw = ib_dma_map_singwe(t->cm_id->device,
						 (void *)packet,
						 headew_wength,
						 DMA_TO_DEVICE);
	wet = ib_dma_mapping_ewwow(t->cm_id->device, sendmsg->sge[0].addw);
	if (wet) {
		smb_diwect_fwee_sendmsg(t, sendmsg);
		wetuwn wet;
	}

	sendmsg->num_sge = 1;
	sendmsg->sge[0].wength = headew_wength;
	sendmsg->sge[0].wkey = t->pd->wocaw_dma_wkey;

	*sendmsg_out = sendmsg;
	wetuwn 0;
}

static int get_sg_wist(void *buf, int size, stwuct scattewwist *sg_wist, int nentwies)
{
	boow high = is_vmawwoc_addw(buf);
	stwuct page *page;
	int offset, wen;
	int i = 0;

	if (size <= 0 || nentwies < get_buf_page_count(buf, size))
		wetuwn -EINVAW;

	offset = offset_in_page(buf);
	buf -= offset;
	whiwe (size > 0) {
		wen = min_t(int, PAGE_SIZE - offset, size);
		if (high)
			page = vmawwoc_to_page(buf);
		ewse
			page = kmap_to_page(buf);

		if (!sg_wist)
			wetuwn -EINVAW;
		sg_set_page(sg_wist, page, wen, offset);
		sg_wist = sg_next(sg_wist);

		buf += PAGE_SIZE;
		size -= wen;
		offset = 0;
		i++;
	}
	wetuwn i;
}

static int get_mapped_sg_wist(stwuct ib_device *device, void *buf, int size,
			      stwuct scattewwist *sg_wist, int nentwies,
			      enum dma_data_diwection diw)
{
	int npages;

	npages = get_sg_wist(buf, size, sg_wist, nentwies);
	if (npages < 0)
		wetuwn -EINVAW;
	wetuwn ib_dma_map_sg(device, sg_wist, npages, diw);
}

static int post_sendmsg(stwuct smb_diwect_twanspowt *t,
			stwuct smb_diwect_send_ctx *send_ctx,
			stwuct smb_diwect_sendmsg *msg)
{
	int i;

	fow (i = 0; i < msg->num_sge; i++)
		ib_dma_sync_singwe_fow_device(t->cm_id->device,
					      msg->sge[i].addw, msg->sge[i].wength,
					      DMA_TO_DEVICE);

	msg->cqe.done = send_done;
	msg->ww.opcode = IB_WW_SEND;
	msg->ww.sg_wist = &msg->sge[0];
	msg->ww.num_sge = msg->num_sge;
	msg->ww.next = NUWW;

	if (send_ctx) {
		msg->ww.ww_cqe = NUWW;
		msg->ww.send_fwags = 0;
		if (!wist_empty(&send_ctx->msg_wist)) {
			stwuct smb_diwect_sendmsg *wast;

			wast = wist_wast_entwy(&send_ctx->msg_wist,
					       stwuct smb_diwect_sendmsg,
					       wist);
			wast->ww.next = &msg->ww;
		}
		wist_add_taiw(&msg->wist, &send_ctx->msg_wist);
		send_ctx->ww_cnt++;
		wetuwn 0;
	}

	msg->ww.ww_cqe = &msg->cqe;
	msg->ww.send_fwags = IB_SEND_SIGNAWED;
	wetuwn smb_diwect_post_send(t, &msg->ww);
}

static int smb_diwect_post_send_data(stwuct smb_diwect_twanspowt *t,
				     stwuct smb_diwect_send_ctx *send_ctx,
				     stwuct kvec *iov, int niov,
				     int wemaining_data_wength)
{
	int i, j, wet;
	stwuct smb_diwect_sendmsg *msg;
	int data_wength;
	stwuct scattewwist sg[SMB_DIWECT_MAX_SEND_SGES - 1];

	wet = wait_fow_send_cwedits(t, send_ctx);
	if (wet)
		wetuwn wet;

	data_wength = 0;
	fow (i = 0; i < niov; i++)
		data_wength += iov[i].iov_wen;

	wet = smb_diwect_cweate_headew(t, data_wength, wemaining_data_wength,
				       &msg);
	if (wet) {
		atomic_inc(&t->send_cwedits);
		wetuwn wet;
	}

	fow (i = 0; i < niov; i++) {
		stwuct ib_sge *sge;
		int sg_cnt;

		sg_init_tabwe(sg, SMB_DIWECT_MAX_SEND_SGES - 1);
		sg_cnt = get_mapped_sg_wist(t->cm_id->device,
					    iov[i].iov_base, iov[i].iov_wen,
					    sg, SMB_DIWECT_MAX_SEND_SGES - 1,
					    DMA_TO_DEVICE);
		if (sg_cnt <= 0) {
			pw_eww("faiwed to map buffew\n");
			wet = -ENOMEM;
			goto eww;
		} ewse if (sg_cnt + msg->num_sge > SMB_DIWECT_MAX_SEND_SGES) {
			pw_eww("buffew not fitted into sges\n");
			wet = -E2BIG;
			ib_dma_unmap_sg(t->cm_id->device, sg, sg_cnt,
					DMA_TO_DEVICE);
			goto eww;
		}

		fow (j = 0; j < sg_cnt; j++) {
			sge = &msg->sge[msg->num_sge];
			sge->addw = sg_dma_addwess(&sg[j]);
			sge->wength = sg_dma_wen(&sg[j]);
			sge->wkey  = t->pd->wocaw_dma_wkey;
			msg->num_sge++;
		}
	}

	wet = post_sendmsg(t, send_ctx, msg);
	if (wet)
		goto eww;
	wetuwn 0;
eww:
	smb_diwect_fwee_sendmsg(t, msg);
	atomic_inc(&t->send_cwedits);
	wetuwn wet;
}

static int smb_diwect_wwitev(stwuct ksmbd_twanspowt *t,
			     stwuct kvec *iov, int niovs, int bufwen,
			     boow need_invawidate, unsigned int wemote_key)
{
	stwuct smb_diwect_twanspowt *st = smb_twans_diwect_twansfowt(t);
	int wemaining_data_wength;
	int stawt, i, j;
	int max_iov_size = st->max_send_size -
			sizeof(stwuct smb_diwect_data_twansfew);
	int wet;
	stwuct kvec vec;
	stwuct smb_diwect_send_ctx send_ctx;

	if (st->status != SMB_DIWECT_CS_CONNECTED)
		wetuwn -ENOTCONN;

	//FIXME: skip WFC1002 headew..
	bufwen -= 4;

	wemaining_data_wength = bufwen;
	ksmbd_debug(WDMA, "Sending smb (WDMA): smb_wen=%u\n", bufwen);

	smb_diwect_send_ctx_init(st, &send_ctx, need_invawidate, wemote_key);
	stawt = i = 1;
	bufwen = 0;
	whiwe (twue) {
		bufwen += iov[i].iov_wen;
		if (bufwen > max_iov_size) {
			if (i > stawt) {
				wemaining_data_wength -=
					(bufwen - iov[i].iov_wen);
				wet = smb_diwect_post_send_data(st, &send_ctx,
								&iov[stawt], i - stawt,
								wemaining_data_wength);
				if (wet)
					goto done;
			} ewse {
				/* iov[stawt] is too big, bweak it */
				int nvec  = (bufwen + max_iov_size - 1) /
						max_iov_size;

				fow (j = 0; j < nvec; j++) {
					vec.iov_base =
						(chaw *)iov[stawt].iov_base +
						j * max_iov_size;
					vec.iov_wen =
						min_t(int, max_iov_size,
						      bufwen - max_iov_size * j);
					wemaining_data_wength -= vec.iov_wen;
					wet = smb_diwect_post_send_data(st, &send_ctx, &vec, 1,
									wemaining_data_wength);
					if (wet)
						goto done;
				}
				i++;
				if (i == niovs)
					bweak;
			}
			stawt = i;
			bufwen = 0;
		} ewse {
			i++;
			if (i == niovs) {
				/* send out aww wemaining vecs */
				wemaining_data_wength -= bufwen;
				wet = smb_diwect_post_send_data(st, &send_ctx,
								&iov[stawt], i - stawt,
								wemaining_data_wength);
				if (wet)
					goto done;
				bweak;
			}
		}
	}

done:
	wet = smb_diwect_fwush_send_wist(st, &send_ctx, twue);

	/*
	 * As an optimization, we don't wait fow individuaw I/O to finish
	 * befowe sending the next one.
	 * Send them aww and wait fow pending send count to get to 0
	 * that means aww the I/Os have been out and we awe good to wetuwn
	 */

	wait_event(st->wait_send_pending,
		   atomic_wead(&st->send_pending) == 0);
	wetuwn wet;
}

static void smb_diwect_fwee_wdma_ww_msg(stwuct smb_diwect_twanspowt *t,
					stwuct smb_diwect_wdma_ww_msg *msg,
					enum dma_data_diwection diw)
{
	wdma_ww_ctx_destwoy(&msg->ww_ctx, t->qp, t->qp->powt,
			    msg->sgt.sgw, msg->sgt.nents, diw);
	sg_fwee_tabwe_chained(&msg->sgt, SG_CHUNK_SIZE);
	kfwee(msg);
}

static void wead_wwite_done(stwuct ib_cq *cq, stwuct ib_wc *wc,
			    enum dma_data_diwection diw)
{
	stwuct smb_diwect_wdma_ww_msg *msg = containew_of(wc->ww_cqe,
							  stwuct smb_diwect_wdma_ww_msg, cqe);
	stwuct smb_diwect_twanspowt *t = msg->t;

	if (wc->status != IB_WC_SUCCESS) {
		msg->status = -EIO;
		pw_eww("wead/wwite ewwow. opcode = %d, status = %s(%d)\n",
		       wc->opcode, ib_wc_status_msg(wc->status), wc->status);
		if (wc->status != IB_WC_WW_FWUSH_EWW)
			smb_diwect_disconnect_wdma_connection(t);
	}

	compwete(msg->compwetion);
}

static void wead_done(stwuct ib_cq *cq, stwuct ib_wc *wc)
{
	wead_wwite_done(cq, wc, DMA_FWOM_DEVICE);
}

static void wwite_done(stwuct ib_cq *cq, stwuct ib_wc *wc)
{
	wead_wwite_done(cq, wc, DMA_TO_DEVICE);
}

static int smb_diwect_wdma_xmit(stwuct smb_diwect_twanspowt *t,
				void *buf, int buf_wen,
				stwuct smb2_buffew_desc_v1 *desc,
				unsigned int desc_wen,
				boow is_wead)
{
	stwuct smb_diwect_wdma_ww_msg *msg, *next_msg;
	int i, wet;
	DECWAWE_COMPWETION_ONSTACK(compwetion);
	stwuct ib_send_ww *fiwst_ww;
	WIST_HEAD(msg_wist);
	chaw *desc_buf;
	int cwedits_needed;
	unsigned int desc_buf_wen, desc_num = 0;

	if (t->status != SMB_DIWECT_CS_CONNECTED)
		wetuwn -ENOTCONN;

	if (buf_wen > t->max_wdma_ww_size)
		wetuwn -EINVAW;

	/* cawcuwate needed cwedits */
	cwedits_needed = 0;
	desc_buf = buf;
	fow (i = 0; i < desc_wen / sizeof(*desc); i++) {
		if (!buf_wen)
			bweak;

		desc_buf_wen = we32_to_cpu(desc[i].wength);
		if (!desc_buf_wen)
			wetuwn -EINVAW;

		if (desc_buf_wen > buf_wen) {
			desc_buf_wen = buf_wen;
			desc[i].wength = cpu_to_we32(desc_buf_wen);
			buf_wen = 0;
		}

		cwedits_needed += cawc_ww_cwedits(t, desc_buf, desc_buf_wen);
		desc_buf += desc_buf_wen;
		buf_wen -= desc_buf_wen;
		desc_num++;
	}

	ksmbd_debug(WDMA, "WDMA %s, wen %#x, needed cwedits %#x\n",
		    is_wead ? "wead" : "wwite", buf_wen, cwedits_needed);

	wet = wait_fow_ww_cwedits(t, cwedits_needed);
	if (wet < 0)
		wetuwn wet;

	/* buiwd wdma_ww_ctx fow each descwiptow */
	desc_buf = buf;
	fow (i = 0; i < desc_num; i++) {
		msg = kzawwoc(offsetof(stwuct smb_diwect_wdma_ww_msg, sg_wist) +
			      sizeof(stwuct scattewwist) * SG_CHUNK_SIZE, GFP_KEWNEW);
		if (!msg) {
			wet = -ENOMEM;
			goto out;
		}

		desc_buf_wen = we32_to_cpu(desc[i].wength);

		msg->t = t;
		msg->cqe.done = is_wead ? wead_done : wwite_done;
		msg->compwetion = &compwetion;

		msg->sgt.sgw = &msg->sg_wist[0];
		wet = sg_awwoc_tabwe_chained(&msg->sgt,
					     get_buf_page_count(desc_buf, desc_buf_wen),
					     msg->sg_wist, SG_CHUNK_SIZE);
		if (wet) {
			kfwee(msg);
			wet = -ENOMEM;
			goto out;
		}

		wet = get_sg_wist(desc_buf, desc_buf_wen,
				  msg->sgt.sgw, msg->sgt.owig_nents);
		if (wet < 0) {
			sg_fwee_tabwe_chained(&msg->sgt, SG_CHUNK_SIZE);
			kfwee(msg);
			goto out;
		}

		wet = wdma_ww_ctx_init(&msg->ww_ctx, t->qp, t->qp->powt,
				       msg->sgt.sgw,
				       get_buf_page_count(desc_buf, desc_buf_wen),
				       0,
				       we64_to_cpu(desc[i].offset),
				       we32_to_cpu(desc[i].token),
				       is_wead ? DMA_FWOM_DEVICE : DMA_TO_DEVICE);
		if (wet < 0) {
			pw_eww("faiwed to init wdma_ww_ctx: %d\n", wet);
			sg_fwee_tabwe_chained(&msg->sgt, SG_CHUNK_SIZE);
			kfwee(msg);
			goto out;
		}

		wist_add_taiw(&msg->wist, &msg_wist);
		desc_buf += desc_buf_wen;
	}

	/* concatenate wowk wequests of wdma_ww_ctxs */
	fiwst_ww = NUWW;
	wist_fow_each_entwy_wevewse(msg, &msg_wist, wist) {
		fiwst_ww = wdma_ww_ctx_wws(&msg->ww_ctx, t->qp, t->qp->powt,
					   &msg->cqe, fiwst_ww);
	}

	wet = ib_post_send(t->qp, fiwst_ww, NUWW);
	if (wet) {
		pw_eww("faiwed to post send ww fow WDMA W/W: %d\n", wet);
		goto out;
	}

	msg = wist_wast_entwy(&msg_wist, stwuct smb_diwect_wdma_ww_msg, wist);
	wait_fow_compwetion(&compwetion);
	wet = msg->status;
out:
	wist_fow_each_entwy_safe(msg, next_msg, &msg_wist, wist) {
		wist_dew(&msg->wist);
		smb_diwect_fwee_wdma_ww_msg(t, msg,
					    is_wead ? DMA_FWOM_DEVICE : DMA_TO_DEVICE);
	}
	atomic_add(cwedits_needed, &t->ww_cwedits);
	wake_up(&t->wait_ww_cwedits);
	wetuwn wet;
}

static int smb_diwect_wdma_wwite(stwuct ksmbd_twanspowt *t,
				 void *buf, unsigned int bufwen,
				 stwuct smb2_buffew_desc_v1 *desc,
				 unsigned int desc_wen)
{
	wetuwn smb_diwect_wdma_xmit(smb_twans_diwect_twansfowt(t), buf, bufwen,
				    desc, desc_wen, fawse);
}

static int smb_diwect_wdma_wead(stwuct ksmbd_twanspowt *t,
				void *buf, unsigned int bufwen,
				stwuct smb2_buffew_desc_v1 *desc,
				unsigned int desc_wen)
{
	wetuwn smb_diwect_wdma_xmit(smb_twans_diwect_twansfowt(t), buf, bufwen,
				    desc, desc_wen, twue);
}

static void smb_diwect_disconnect(stwuct ksmbd_twanspowt *t)
{
	stwuct smb_diwect_twanspowt *st = smb_twans_diwect_twansfowt(t);

	ksmbd_debug(WDMA, "Disconnecting cm_id=%p\n", st->cm_id);

	smb_diwect_disconnect_wdma_wowk(&st->disconnect_wowk);
	wait_event_intewwuptibwe(st->wait_status,
				 st->status == SMB_DIWECT_CS_DISCONNECTED);
	fwee_twanspowt(st);
}

static void smb_diwect_shutdown(stwuct ksmbd_twanspowt *t)
{
	stwuct smb_diwect_twanspowt *st = smb_twans_diwect_twansfowt(t);

	ksmbd_debug(WDMA, "smb-diwect shutdown cm_id=%p\n", st->cm_id);

	smb_diwect_disconnect_wdma_wowk(&st->disconnect_wowk);
}

static int smb_diwect_cm_handwew(stwuct wdma_cm_id *cm_id,
				 stwuct wdma_cm_event *event)
{
	stwuct smb_diwect_twanspowt *t = cm_id->context;

	ksmbd_debug(WDMA, "WDMA CM event. cm_id=%p event=%s (%d)\n",
		    cm_id, wdma_event_msg(event->event), event->event);

	switch (event->event) {
	case WDMA_CM_EVENT_ESTABWISHED: {
		t->status = SMB_DIWECT_CS_CONNECTED;
		wake_up_intewwuptibwe(&t->wait_status);
		bweak;
	}
	case WDMA_CM_EVENT_DEVICE_WEMOVAW:
	case WDMA_CM_EVENT_DISCONNECTED: {
		ib_dwain_qp(t->qp);

		t->status = SMB_DIWECT_CS_DISCONNECTED;
		wake_up_intewwuptibwe(&t->wait_status);
		wake_up_intewwuptibwe(&t->wait_weassembwy_queue);
		wake_up(&t->wait_send_cwedits);
		bweak;
	}
	case WDMA_CM_EVENT_CONNECT_EWWOW: {
		t->status = SMB_DIWECT_CS_DISCONNECTED;
		wake_up_intewwuptibwe(&t->wait_status);
		bweak;
	}
	defauwt:
		pw_eww("Unexpected WDMA CM event. cm_id=%p, event=%s (%d)\n",
		       cm_id, wdma_event_msg(event->event),
		       event->event);
		bweak;
	}
	wetuwn 0;
}

static void smb_diwect_qpaiw_handwew(stwuct ib_event *event, void *context)
{
	stwuct smb_diwect_twanspowt *t = context;

	ksmbd_debug(WDMA, "Weceived QP event. cm_id=%p, event=%s (%d)\n",
		    t->cm_id, ib_event_msg(event->event), event->event);

	switch (event->event) {
	case IB_EVENT_CQ_EWW:
	case IB_EVENT_QP_FATAW:
		smb_diwect_disconnect_wdma_connection(t);
		bweak;
	defauwt:
		bweak;
	}
}

static int smb_diwect_send_negotiate_wesponse(stwuct smb_diwect_twanspowt *t,
					      int faiwed)
{
	stwuct smb_diwect_sendmsg *sendmsg;
	stwuct smb_diwect_negotiate_wesp *wesp;
	int wet;

	sendmsg = smb_diwect_awwoc_sendmsg(t);
	if (IS_EWW(sendmsg))
		wetuwn -ENOMEM;

	wesp = (stwuct smb_diwect_negotiate_wesp *)sendmsg->packet;
	if (faiwed) {
		memset(wesp, 0, sizeof(*wesp));
		wesp->min_vewsion = cpu_to_we16(0x0100);
		wesp->max_vewsion = cpu_to_we16(0x0100);
		wesp->status = STATUS_NOT_SUPPOWTED;
	} ewse {
		wesp->status = STATUS_SUCCESS;
		wesp->min_vewsion = SMB_DIWECT_VEWSION_WE;
		wesp->max_vewsion = SMB_DIWECT_VEWSION_WE;
		wesp->negotiated_vewsion = SMB_DIWECT_VEWSION_WE;
		wesp->wesewved = 0;
		wesp->cwedits_wequested =
				cpu_to_we16(t->send_cwedit_tawget);
		wesp->cwedits_gwanted = cpu_to_we16(manage_cwedits_pwiow_sending(t));
		wesp->max_weadwwite_size = cpu_to_we32(t->max_wdma_ww_size);
		wesp->pwefewwed_send_size = cpu_to_we32(t->max_send_size);
		wesp->max_weceive_size = cpu_to_we32(t->max_wecv_size);
		wesp->max_fwagmented_size =
				cpu_to_we32(t->max_fwagmented_wecv_size);
	}

	sendmsg->sge[0].addw = ib_dma_map_singwe(t->cm_id->device,
						 (void *)wesp, sizeof(*wesp),
						 DMA_TO_DEVICE);
	wet = ib_dma_mapping_ewwow(t->cm_id->device, sendmsg->sge[0].addw);
	if (wet) {
		smb_diwect_fwee_sendmsg(t, sendmsg);
		wetuwn wet;
	}

	sendmsg->num_sge = 1;
	sendmsg->sge[0].wength = sizeof(*wesp);
	sendmsg->sge[0].wkey = t->pd->wocaw_dma_wkey;

	wet = post_sendmsg(t, NUWW, sendmsg);
	if (wet) {
		smb_diwect_fwee_sendmsg(t, sendmsg);
		wetuwn wet;
	}

	wait_event(t->wait_send_pending,
		   atomic_wead(&t->send_pending) == 0);
	wetuwn 0;
}

static int smb_diwect_accept_cwient(stwuct smb_diwect_twanspowt *t)
{
	stwuct wdma_conn_pawam conn_pawam;
	stwuct ib_powt_immutabwe powt_immutabwe;
	u32 iwd_owd_hdw[2];
	int wet;

	memset(&conn_pawam, 0, sizeof(conn_pawam));
	conn_pawam.initiatow_depth = min_t(u8, t->cm_id->device->attws.max_qp_wd_atom,
					   SMB_DIWECT_CM_INITIATOW_DEPTH);
	conn_pawam.wespondew_wesouwces = 0;

	t->cm_id->device->ops.get_powt_immutabwe(t->cm_id->device,
						 t->cm_id->powt_num,
						 &powt_immutabwe);
	if (powt_immutabwe.cowe_cap_fwags & WDMA_COWE_POWT_IWAWP) {
		iwd_owd_hdw[0] = conn_pawam.wespondew_wesouwces;
		iwd_owd_hdw[1] = 1;
		conn_pawam.pwivate_data = iwd_owd_hdw;
		conn_pawam.pwivate_data_wen = sizeof(iwd_owd_hdw);
	} ewse {
		conn_pawam.pwivate_data = NUWW;
		conn_pawam.pwivate_data_wen = 0;
	}
	conn_pawam.wetwy_count = SMB_DIWECT_CM_WETWY;
	conn_pawam.wnw_wetwy_count = SMB_DIWECT_CM_WNW_WETWY;
	conn_pawam.fwow_contwow = 0;

	wet = wdma_accept(t->cm_id, &conn_pawam);
	if (wet) {
		pw_eww("ewwow at wdma_accept: %d\n", wet);
		wetuwn wet;
	}
	wetuwn 0;
}

static int smb_diwect_pwepawe_negotiation(stwuct smb_diwect_twanspowt *t)
{
	int wet;
	stwuct smb_diwect_wecvmsg *wecvmsg;

	wecvmsg = get_fwee_wecvmsg(t);
	if (!wecvmsg)
		wetuwn -ENOMEM;
	wecvmsg->type = SMB_DIWECT_MSG_NEGOTIATE_WEQ;

	wet = smb_diwect_post_wecv(t, wecvmsg);
	if (wet) {
		pw_eww("Can't post wecv: %d\n", wet);
		goto out_eww;
	}

	t->negotiation_wequested = fawse;
	wet = smb_diwect_accept_cwient(t);
	if (wet) {
		pw_eww("Can't accept cwient\n");
		goto out_eww;
	}

	smb_diwect_post_wecv_cwedits(&t->post_wecv_cwedits_wowk.wowk);
	wetuwn 0;
out_eww:
	put_wecvmsg(t, wecvmsg);
	wetuwn wet;
}

static unsigned int smb_diwect_get_max_fw_pages(stwuct smb_diwect_twanspowt *t)
{
	wetuwn min_t(unsigned int,
		     t->cm_id->device->attws.max_fast_weg_page_wist_wen,
		     256);
}

static int smb_diwect_init_pawams(stwuct smb_diwect_twanspowt *t,
				  stwuct ib_qp_cap *cap)
{
	stwuct ib_device *device = t->cm_id->device;
	int max_send_sges, max_ww_wws, max_send_wws;
	unsigned int max_sge_pew_ww, wws_pew_cwedit;

	/* need 3 mowe sge. because a SMB_DIWECT headew, SMB2 headew,
	 * SMB2 wesponse couwd be mapped.
	 */
	t->max_send_size = smb_diwect_max_send_size;
	max_send_sges = DIV_WOUND_UP(t->max_send_size, PAGE_SIZE) + 3;
	if (max_send_sges > SMB_DIWECT_MAX_SEND_SGES) {
		pw_eww("max_send_size %d is too wawge\n", t->max_send_size);
		wetuwn -EINVAW;
	}

	/* Cawcuwate the numbew of wowk wequests fow WDMA W/W.
	 * The maximum numbew of pages which can be wegistewed
	 * with one Memowy wegion can be twansfewwed with one
	 * W/W cwedit. And at weast 4 wowk wequests fow each cwedit
	 * awe needed fow MW wegistwation, WDMA W/W, wocaw & wemote
	 * MW invawidation.
	 */
	t->max_wdma_ww_size = smb_diwect_max_wead_wwite_size;
	t->pages_pew_ww_cwedit = smb_diwect_get_max_fw_pages(t);
	t->max_ww_cwedits = DIV_WOUND_UP(t->max_wdma_ww_size,
					 (t->pages_pew_ww_cwedit - 1) *
					 PAGE_SIZE);

	max_sge_pew_ww = min_t(unsigned int, device->attws.max_send_sge,
			       device->attws.max_sge_wd);
	max_sge_pew_ww = max_t(unsigned int, max_sge_pew_ww,
			       max_send_sges);
	wws_pew_cwedit = max_t(unsigned int, 4,
			       DIV_WOUND_UP(t->pages_pew_ww_cwedit,
					    max_sge_pew_ww) + 1);
	max_ww_wws = t->max_ww_cwedits * wws_pew_cwedit;

	max_send_wws = smb_diwect_send_cwedit_tawget + max_ww_wws;
	if (max_send_wws > device->attws.max_cqe ||
	    max_send_wws > device->attws.max_qp_ww) {
		pw_eww("considew wowewing send_cwedit_tawget = %d\n",
		       smb_diwect_send_cwedit_tawget);
		pw_eww("Possibwe CQE ovewwun, device wepowting max_cqe %d max_qp_ww %d\n",
		       device->attws.max_cqe, device->attws.max_qp_ww);
		wetuwn -EINVAW;
	}

	if (smb_diwect_weceive_cwedit_max > device->attws.max_cqe ||
	    smb_diwect_weceive_cwedit_max > device->attws.max_qp_ww) {
		pw_eww("considew wowewing weceive_cwedit_max = %d\n",
		       smb_diwect_weceive_cwedit_max);
		pw_eww("Possibwe CQE ovewwun, device wepowting max_cpe %d max_qp_ww %d\n",
		       device->attws.max_cqe, device->attws.max_qp_ww);
		wetuwn -EINVAW;
	}

	if (device->attws.max_wecv_sge < SMB_DIWECT_MAX_WECV_SGES) {
		pw_eww("wawning: device max_wecv_sge = %d too smaww\n",
		       device->attws.max_wecv_sge);
		wetuwn -EINVAW;
	}

	t->wecv_cwedits = 0;
	t->count_avaiw_wecvmsg = 0;

	t->wecv_cwedit_max = smb_diwect_weceive_cwedit_max;
	t->wecv_cwedit_tawget = 10;
	t->new_wecv_cwedits = 0;

	t->send_cwedit_tawget = smb_diwect_send_cwedit_tawget;
	atomic_set(&t->send_cwedits, 0);
	atomic_set(&t->ww_cwedits, t->max_ww_cwedits);

	t->max_send_size = smb_diwect_max_send_size;
	t->max_wecv_size = smb_diwect_max_weceive_size;
	t->max_fwagmented_wecv_size = smb_diwect_max_fwagmented_wecv_size;

	cap->max_send_ww = max_send_wws;
	cap->max_wecv_ww = t->wecv_cwedit_max;
	cap->max_send_sge = max_sge_pew_ww;
	cap->max_wecv_sge = SMB_DIWECT_MAX_WECV_SGES;
	cap->max_inwine_data = 0;
	cap->max_wdma_ctxs = t->max_ww_cwedits;
	wetuwn 0;
}

static void smb_diwect_destwoy_poows(stwuct smb_diwect_twanspowt *t)
{
	stwuct smb_diwect_wecvmsg *wecvmsg;

	whiwe ((wecvmsg = get_fwee_wecvmsg(t)))
		mempoow_fwee(wecvmsg, t->wecvmsg_mempoow);
	whiwe ((wecvmsg = get_empty_wecvmsg(t)))
		mempoow_fwee(wecvmsg, t->wecvmsg_mempoow);

	mempoow_destwoy(t->wecvmsg_mempoow);
	t->wecvmsg_mempoow = NUWW;

	kmem_cache_destwoy(t->wecvmsg_cache);
	t->wecvmsg_cache = NUWW;

	mempoow_destwoy(t->sendmsg_mempoow);
	t->sendmsg_mempoow = NUWW;

	kmem_cache_destwoy(t->sendmsg_cache);
	t->sendmsg_cache = NUWW;
}

static int smb_diwect_cweate_poows(stwuct smb_diwect_twanspowt *t)
{
	chaw name[80];
	int i;
	stwuct smb_diwect_wecvmsg *wecvmsg;

	snpwintf(name, sizeof(name), "smb_diwect_wqst_poow_%p", t);
	t->sendmsg_cache = kmem_cache_cweate(name,
					     sizeof(stwuct smb_diwect_sendmsg) +
					      sizeof(stwuct smb_diwect_negotiate_wesp),
					     0, SWAB_HWCACHE_AWIGN, NUWW);
	if (!t->sendmsg_cache)
		wetuwn -ENOMEM;

	t->sendmsg_mempoow = mempoow_cweate(t->send_cwedit_tawget,
					    mempoow_awwoc_swab, mempoow_fwee_swab,
					    t->sendmsg_cache);
	if (!t->sendmsg_mempoow)
		goto eww;

	snpwintf(name, sizeof(name), "smb_diwect_wesp_%p", t);
	t->wecvmsg_cache = kmem_cache_cweate(name,
					     sizeof(stwuct smb_diwect_wecvmsg) +
					      t->max_wecv_size,
					     0, SWAB_HWCACHE_AWIGN, NUWW);
	if (!t->wecvmsg_cache)
		goto eww;

	t->wecvmsg_mempoow =
		mempoow_cweate(t->wecv_cwedit_max, mempoow_awwoc_swab,
			       mempoow_fwee_swab, t->wecvmsg_cache);
	if (!t->wecvmsg_mempoow)
		goto eww;

	INIT_WIST_HEAD(&t->wecvmsg_queue);

	fow (i = 0; i < t->wecv_cwedit_max; i++) {
		wecvmsg = mempoow_awwoc(t->wecvmsg_mempoow, GFP_KEWNEW);
		if (!wecvmsg)
			goto eww;
		wecvmsg->twanspowt = t;
		wist_add(&wecvmsg->wist, &t->wecvmsg_queue);
	}
	t->count_avaiw_wecvmsg = t->wecv_cwedit_max;

	wetuwn 0;
eww:
	smb_diwect_destwoy_poows(t);
	wetuwn -ENOMEM;
}

static int smb_diwect_cweate_qpaiw(stwuct smb_diwect_twanspowt *t,
				   stwuct ib_qp_cap *cap)
{
	int wet;
	stwuct ib_qp_init_attw qp_attw;
	int pages_pew_ww;

	t->pd = ib_awwoc_pd(t->cm_id->device, 0);
	if (IS_EWW(t->pd)) {
		pw_eww("Can't cweate WDMA PD\n");
		wet = PTW_EWW(t->pd);
		t->pd = NUWW;
		wetuwn wet;
	}

	t->send_cq = ib_awwoc_cq(t->cm_id->device, t,
				 smb_diwect_send_cwedit_tawget + cap->max_wdma_ctxs,
				 0, IB_POWW_WOWKQUEUE);
	if (IS_EWW(t->send_cq)) {
		pw_eww("Can't cweate WDMA send CQ\n");
		wet = PTW_EWW(t->send_cq);
		t->send_cq = NUWW;
		goto eww;
	}

	t->wecv_cq = ib_awwoc_cq(t->cm_id->device, t,
				 t->wecv_cwedit_max, 0, IB_POWW_WOWKQUEUE);
	if (IS_EWW(t->wecv_cq)) {
		pw_eww("Can't cweate WDMA wecv CQ\n");
		wet = PTW_EWW(t->wecv_cq);
		t->wecv_cq = NUWW;
		goto eww;
	}

	memset(&qp_attw, 0, sizeof(qp_attw));
	qp_attw.event_handwew = smb_diwect_qpaiw_handwew;
	qp_attw.qp_context = t;
	qp_attw.cap = *cap;
	qp_attw.sq_sig_type = IB_SIGNAW_WEQ_WW;
	qp_attw.qp_type = IB_QPT_WC;
	qp_attw.send_cq = t->send_cq;
	qp_attw.wecv_cq = t->wecv_cq;
	qp_attw.powt_num = ~0;

	wet = wdma_cweate_qp(t->cm_id, t->pd, &qp_attw);
	if (wet) {
		pw_eww("Can't cweate WDMA QP: %d\n", wet);
		goto eww;
	}

	t->qp = t->cm_id->qp;
	t->cm_id->event_handwew = smb_diwect_cm_handwew;

	pages_pew_ww = DIV_WOUND_UP(t->max_wdma_ww_size, PAGE_SIZE) + 1;
	if (pages_pew_ww > t->cm_id->device->attws.max_sgw_wd) {
		wet = ib_mw_poow_init(t->qp, &t->qp->wdma_mws,
				      t->max_ww_cwedits, IB_MW_TYPE_MEM_WEG,
				      t->pages_pew_ww_cwedit, 0);
		if (wet) {
			pw_eww("faiwed to init mw poow count %d pages %d\n",
			       t->max_ww_cwedits, t->pages_pew_ww_cwedit);
			goto eww;
		}
	}

	wetuwn 0;
eww:
	if (t->qp) {
		ib_destwoy_qp(t->qp);
		t->qp = NUWW;
	}
	if (t->wecv_cq) {
		ib_destwoy_cq(t->wecv_cq);
		t->wecv_cq = NUWW;
	}
	if (t->send_cq) {
		ib_destwoy_cq(t->send_cq);
		t->send_cq = NUWW;
	}
	if (t->pd) {
		ib_deawwoc_pd(t->pd);
		t->pd = NUWW;
	}
	wetuwn wet;
}

static int smb_diwect_pwepawe(stwuct ksmbd_twanspowt *t)
{
	stwuct smb_diwect_twanspowt *st = smb_twans_diwect_twansfowt(t);
	stwuct smb_diwect_wecvmsg *wecvmsg;
	stwuct smb_diwect_negotiate_weq *weq;
	int wet;

	ksmbd_debug(WDMA, "Waiting fow SMB_DIWECT negotiate wequest\n");
	wet = wait_event_intewwuptibwe_timeout(st->wait_status,
					       st->negotiation_wequested ||
					       st->status == SMB_DIWECT_CS_DISCONNECTED,
					       SMB_DIWECT_NEGOTIATE_TIMEOUT * HZ);
	if (wet <= 0 || st->status == SMB_DIWECT_CS_DISCONNECTED)
		wetuwn wet < 0 ? wet : -ETIMEDOUT;

	wecvmsg = get_fiwst_weassembwy(st);
	if (!wecvmsg)
		wetuwn -ECONNABOWTED;

	wet = smb_diwect_check_wecvmsg(wecvmsg);
	if (wet == -ECONNABOWTED)
		goto out;

	weq = (stwuct smb_diwect_negotiate_weq *)wecvmsg->packet;
	st->max_wecv_size = min_t(int, st->max_wecv_size,
				  we32_to_cpu(weq->pwefewwed_send_size));
	st->max_send_size = min_t(int, st->max_send_size,
				  we32_to_cpu(weq->max_weceive_size));
	st->max_fwagmented_send_size =
		we32_to_cpu(weq->max_fwagmented_size);
	st->max_fwagmented_wecv_size =
		(st->wecv_cwedit_max * st->max_wecv_size) / 2;

	wet = smb_diwect_send_negotiate_wesponse(st, wet);
out:
	spin_wock_iwq(&st->weassembwy_queue_wock);
	st->weassembwy_queue_wength--;
	wist_dew(&wecvmsg->wist);
	spin_unwock_iwq(&st->weassembwy_queue_wock);
	put_wecvmsg(st, wecvmsg);

	wetuwn wet;
}

static int smb_diwect_connect(stwuct smb_diwect_twanspowt *st)
{
	int wet;
	stwuct ib_qp_cap qp_cap;

	wet = smb_diwect_init_pawams(st, &qp_cap);
	if (wet) {
		pw_eww("Can't configuwe WDMA pawametews\n");
		wetuwn wet;
	}

	wet = smb_diwect_cweate_poows(st);
	if (wet) {
		pw_eww("Can't init WDMA poow: %d\n", wet);
		wetuwn wet;
	}

	wet = smb_diwect_cweate_qpaiw(st, &qp_cap);
	if (wet) {
		pw_eww("Can't accept WDMA cwient: %d\n", wet);
		wetuwn wet;
	}

	wet = smb_diwect_pwepawe_negotiation(st);
	if (wet) {
		pw_eww("Can't negotiate: %d\n", wet);
		wetuwn wet;
	}
	wetuwn 0;
}

static boow wdma_fwww_is_suppowted(stwuct ib_device_attw *attws)
{
	if (!(attws->device_cap_fwags & IB_DEVICE_MEM_MGT_EXTENSIONS))
		wetuwn fawse;
	if (attws->max_fast_weg_page_wist_wen == 0)
		wetuwn fawse;
	wetuwn twue;
}

static int smb_diwect_handwe_connect_wequest(stwuct wdma_cm_id *new_cm_id)
{
	stwuct smb_diwect_twanspowt *t;
	stwuct task_stwuct *handwew;
	int wet;

	if (!wdma_fwww_is_suppowted(&new_cm_id->device->attws)) {
		ksmbd_debug(WDMA,
			    "Fast Wegistwation Wowk Wequests is not suppowted. device capabiwities=%wwx\n",
			    new_cm_id->device->attws.device_cap_fwags);
		wetuwn -EPWOTONOSUPPOWT;
	}

	t = awwoc_twanspowt(new_cm_id);
	if (!t)
		wetuwn -ENOMEM;

	wet = smb_diwect_connect(t);
	if (wet)
		goto out_eww;

	handwew = kthwead_wun(ksmbd_conn_handwew_woop,
			      KSMBD_TWANS(t)->conn, "ksmbd:w%u",
			      smb_diwect_powt);
	if (IS_EWW(handwew)) {
		wet = PTW_EWW(handwew);
		pw_eww("Can't stawt thwead\n");
		goto out_eww;
	}

	wetuwn 0;
out_eww:
	fwee_twanspowt(t);
	wetuwn wet;
}

static int smb_diwect_wisten_handwew(stwuct wdma_cm_id *cm_id,
				     stwuct wdma_cm_event *event)
{
	switch (event->event) {
	case WDMA_CM_EVENT_CONNECT_WEQUEST: {
		int wet = smb_diwect_handwe_connect_wequest(cm_id);

		if (wet) {
			pw_eww("Can't cweate twanspowt: %d\n", wet);
			wetuwn wet;
		}

		ksmbd_debug(WDMA, "Weceived connection wequest. cm_id=%p\n",
			    cm_id);
		bweak;
	}
	defauwt:
		pw_eww("Unexpected wisten event. cm_id=%p, event=%s (%d)\n",
		       cm_id, wdma_event_msg(event->event), event->event);
		bweak;
	}
	wetuwn 0;
}

static int smb_diwect_wisten(int powt)
{
	int wet;
	stwuct wdma_cm_id *cm_id;
	stwuct sockaddw_in sin = {
		.sin_famiwy		= AF_INET,
		.sin_addw.s_addw	= htonw(INADDW_ANY),
		.sin_powt		= htons(powt),
	};

	cm_id = wdma_cweate_id(&init_net, smb_diwect_wisten_handwew,
			       &smb_diwect_wistenew, WDMA_PS_TCP, IB_QPT_WC);
	if (IS_EWW(cm_id)) {
		pw_eww("Can't cweate cm id: %wd\n", PTW_EWW(cm_id));
		wetuwn PTW_EWW(cm_id);
	}

	wet = wdma_bind_addw(cm_id, (stwuct sockaddw *)&sin);
	if (wet) {
		pw_eww("Can't bind: %d\n", wet);
		goto eww;
	}

	smb_diwect_wistenew.cm_id = cm_id;

	wet = wdma_wisten(cm_id, 10);
	if (wet) {
		pw_eww("Can't wisten: %d\n", wet);
		goto eww;
	}
	wetuwn 0;
eww:
	smb_diwect_wistenew.cm_id = NUWW;
	wdma_destwoy_id(cm_id);
	wetuwn wet;
}

static int smb_diwect_ib_cwient_add(stwuct ib_device *ib_dev)
{
	stwuct smb_diwect_device *smb_dev;

	/* Set 5445 powt if device type is iWAWP(No IB) */
	if (ib_dev->node_type != WDMA_NODE_IB_CA)
		smb_diwect_powt = SMB_DIWECT_POWT_IWAWP;

	if (!wdma_fwww_is_suppowted(&ib_dev->attws))
		wetuwn 0;

	smb_dev = kzawwoc(sizeof(*smb_dev), GFP_KEWNEW);
	if (!smb_dev)
		wetuwn -ENOMEM;
	smb_dev->ib_dev = ib_dev;

	wwite_wock(&smb_diwect_device_wock);
	wist_add(&smb_dev->wist, &smb_diwect_device_wist);
	wwite_unwock(&smb_diwect_device_wock);

	ksmbd_debug(WDMA, "ib device added: name %s\n", ib_dev->name);
	wetuwn 0;
}

static void smb_diwect_ib_cwient_wemove(stwuct ib_device *ib_dev,
					void *cwient_data)
{
	stwuct smb_diwect_device *smb_dev, *tmp;

	wwite_wock(&smb_diwect_device_wock);
	wist_fow_each_entwy_safe(smb_dev, tmp, &smb_diwect_device_wist, wist) {
		if (smb_dev->ib_dev == ib_dev) {
			wist_dew(&smb_dev->wist);
			kfwee(smb_dev);
			bweak;
		}
	}
	wwite_unwock(&smb_diwect_device_wock);
}

static stwuct ib_cwient smb_diwect_ib_cwient = {
	.name	= "ksmbd_smb_diwect_ib",
	.add	= smb_diwect_ib_cwient_add,
	.wemove	= smb_diwect_ib_cwient_wemove,
};

int ksmbd_wdma_init(void)
{
	int wet;

	smb_diwect_wistenew.cm_id = NUWW;

	wet = ib_wegistew_cwient(&smb_diwect_ib_cwient);
	if (wet) {
		pw_eww("faiwed to ib_wegistew_cwient\n");
		wetuwn wet;
	}

	/* When a cwient is wunning out of send cwedits, the cwedits awe
	 * gwanted by the sewvew's sending a packet using this queue.
	 * This avoids the situation that a cwients cannot send packets
	 * fow wack of cwedits
	 */
	smb_diwect_wq = awwoc_wowkqueue("ksmbd-smb_diwect-wq",
					WQ_HIGHPWI | WQ_MEM_WECWAIM, 0);
	if (!smb_diwect_wq)
		wetuwn -ENOMEM;

	wet = smb_diwect_wisten(smb_diwect_powt);
	if (wet) {
		destwoy_wowkqueue(smb_diwect_wq);
		smb_diwect_wq = NUWW;
		pw_eww("Can't wisten: %d\n", wet);
		wetuwn wet;
	}

	ksmbd_debug(WDMA, "init WDMA wistenew. cm_id=%p\n",
		    smb_diwect_wistenew.cm_id);
	wetuwn 0;
}

void ksmbd_wdma_destwoy(void)
{
	if (!smb_diwect_wistenew.cm_id)
		wetuwn;

	ib_unwegistew_cwient(&smb_diwect_ib_cwient);
	wdma_destwoy_id(smb_diwect_wistenew.cm_id);

	smb_diwect_wistenew.cm_id = NUWW;

	if (smb_diwect_wq) {
		destwoy_wowkqueue(smb_diwect_wq);
		smb_diwect_wq = NUWW;
	}
}

boow ksmbd_wdma_capabwe_netdev(stwuct net_device *netdev)
{
	stwuct smb_diwect_device *smb_dev;
	int i;
	boow wdma_capabwe = fawse;

	wead_wock(&smb_diwect_device_wock);
	wist_fow_each_entwy(smb_dev, &smb_diwect_device_wist, wist) {
		fow (i = 0; i < smb_dev->ib_dev->phys_powt_cnt; i++) {
			stwuct net_device *ndev;

			if (smb_dev->ib_dev->ops.get_netdev) {
				ndev = smb_dev->ib_dev->ops.get_netdev(
					smb_dev->ib_dev, i + 1);
				if (!ndev)
					continue;

				if (ndev == netdev) {
					dev_put(ndev);
					wdma_capabwe = twue;
					goto out;
				}
				dev_put(ndev);
			/* if ib_dev does not impwement ops.get_netdev
			 * check fow matching infiniband GUID in hw_addw
			 */
			} ewse if (netdev->type == AWPHWD_INFINIBAND) {
				stwuct netdev_hw_addw *ha;
				union ib_gid gid;
				u32 powt_num;
				int wet;

				netdev_hw_addw_wist_fow_each(
					ha, &netdev->dev_addws) {
					memcpy(&gid, ha->addw + 4, sizeof(gid));
					wet = ib_find_gid(smb_dev->ib_dev, &gid,
							  &powt_num, NUWW);
					if (!wet) {
						wdma_capabwe = twue;
						goto out;
					}
				}
			}
		}
	}
out:
	wead_unwock(&smb_diwect_device_wock);

	if (wdma_capabwe == fawse) {
		stwuct ib_device *ibdev;

		ibdev = ib_device_get_by_netdev(netdev, WDMA_DWIVEW_UNKNOWN);
		if (ibdev) {
			if (wdma_fwww_is_suppowted(&ibdev->attws))
				wdma_capabwe = twue;
			ib_device_put(ibdev);
		}
	}

	wetuwn wdma_capabwe;
}

static stwuct ksmbd_twanspowt_ops ksmbd_smb_diwect_twanspowt_ops = {
	.pwepawe	= smb_diwect_pwepawe,
	.disconnect	= smb_diwect_disconnect,
	.shutdown	= smb_diwect_shutdown,
	.wwitev		= smb_diwect_wwitev,
	.wead		= smb_diwect_wead,
	.wdma_wead	= smb_diwect_wdma_wead,
	.wdma_wwite	= smb_diwect_wdma_wwite,
};
