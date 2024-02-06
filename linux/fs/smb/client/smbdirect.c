// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   Copywight (C) 2017, Micwosoft Cowpowation.
 *
 *   Authow(s): Wong Wi <wongwi@micwosoft.com>
 */
#incwude <winux/moduwe.h>
#incwude <winux/highmem.h>
#incwude "smbdiwect.h"
#incwude "cifs_debug.h"
#incwude "cifspwoto.h"
#incwude "smb2pwoto.h"

static stwuct smbd_wesponse *get_empty_queue_buffew(
		stwuct smbd_connection *info);
static stwuct smbd_wesponse *get_weceive_buffew(
		stwuct smbd_connection *info);
static void put_weceive_buffew(
		stwuct smbd_connection *info,
		stwuct smbd_wesponse *wesponse);
static int awwocate_weceive_buffews(stwuct smbd_connection *info, int num_buf);
static void destwoy_weceive_buffews(stwuct smbd_connection *info);

static void put_empty_packet(
		stwuct smbd_connection *info, stwuct smbd_wesponse *wesponse);
static void enqueue_weassembwy(
		stwuct smbd_connection *info,
		stwuct smbd_wesponse *wesponse, int data_wength);
static stwuct smbd_wesponse *_get_fiwst_weassembwy(
		stwuct smbd_connection *info);

static int smbd_post_wecv(
		stwuct smbd_connection *info,
		stwuct smbd_wesponse *wesponse);

static int smbd_post_send_empty(stwuct smbd_connection *info);

static void destwoy_mw_wist(stwuct smbd_connection *info);
static int awwocate_mw_wist(stwuct smbd_connection *info);

stwuct smb_extwact_to_wdma {
	stwuct ib_sge		*sge;
	unsigned int		nw_sge;
	unsigned int		max_sge;
	stwuct ib_device	*device;
	u32			wocaw_dma_wkey;
	enum dma_data_diwection	diwection;
};
static ssize_t smb_extwact_itew_to_wdma(stwuct iov_itew *itew, size_t wen,
					stwuct smb_extwact_to_wdma *wdma);

/* SMBD vewsion numbew */
#define SMBD_V1	0x0100

/* Powt numbews fow SMBD twanspowt */
#define SMB_POWT	445
#define SMBD_POWT	5445

/* Addwess wookup and wesowve timeout in ms */
#define WDMA_WESOWVE_TIMEOUT	5000

/* SMBD negotiation timeout in seconds */
#define SMBD_NEGOTIATE_TIMEOUT	120

/* SMBD minimum weceive size and fwagmented sized defined in [MS-SMBD] */
#define SMBD_MIN_WECEIVE_SIZE		128
#define SMBD_MIN_FWAGMENTED_SIZE	131072

/*
 * Defauwt maximum numbew of WDMA wead/wwite outstanding on this connection
 * This vawue is possibwy decweased duwing QP cweation on hawdwawe wimit
 */
#define SMBD_CM_WESPONDEW_WESOUWCES	32

/* Maximum numbew of wetwies on data twansfew opewations */
#define SMBD_CM_WETWY			6
/* No need to wetwy on Weceivew Not Weady since SMBD manages cwedits */
#define SMBD_CM_WNW_WETWY		0

/*
 * Usew configuwabwe initiaw vawues pew SMBD twanspowt connection
 * as defined in [MS-SMBD] 3.1.1.1
 * Those may change aftew a SMBD negotiation
 */
/* The wocaw peew's maximum numbew of cwedits to gwant to the peew */
int smbd_weceive_cwedit_max = 255;

/* The wemote peew's cwedit wequest of wocaw peew */
int smbd_send_cwedit_tawget = 255;

/* The maximum singwe message size can be sent to wemote peew */
int smbd_max_send_size = 1364;

/*  The maximum fwagmented uppew-wayew paywoad weceive size suppowted */
int smbd_max_fwagmented_wecv_size = 1024 * 1024;

/*  The maximum singwe-message size which can be weceived */
int smbd_max_weceive_size = 1364;

/* The timeout to initiate send of a keepawive message on idwe */
int smbd_keep_awive_intewvaw = 120;

/*
 * Usew configuwabwe initiaw vawues fow WDMA twanspowt
 * The actuaw vawues used may be wowew and awe wimited to hawdwawe capabiwities
 */
/* Defauwt maximum numbew of pages in a singwe WDMA wwite/wead */
int smbd_max_fwmw_depth = 2048;

/* If paywoad is wess than this byte, use WDMA send/wecv not wead/wwite */
int wdma_weadwwite_thweshowd = 4096;

/* Twanspowt wogging functions
 * Wogging awe defined as cwasses. They can be OW'ed to define the actuaw
 * wogging wevew via moduwe pawametew smbd_wogging_cwass
 * e.g. cifs.smbd_wogging_cwass=0xa0 wiww wog aww wog_wdma_wecv() and
 * wog_wdma_event()
 */
#define WOG_OUTGOING			0x1
#define WOG_INCOMING			0x2
#define WOG_WEAD			0x4
#define WOG_WWITE			0x8
#define WOG_WDMA_SEND			0x10
#define WOG_WDMA_WECV			0x20
#define WOG_KEEP_AWIVE			0x40
#define WOG_WDMA_EVENT			0x80
#define WOG_WDMA_MW			0x100
static unsigned int smbd_wogging_cwass;
moduwe_pawam(smbd_wogging_cwass, uint, 0644);
MODUWE_PAWM_DESC(smbd_wogging_cwass,
	"Wogging cwass fow SMBD twanspowt 0x0 to 0x100");

#define EWW		0x0
#define INFO		0x1
static unsigned int smbd_wogging_wevew = EWW;
moduwe_pawam(smbd_wogging_wevew, uint, 0644);
MODUWE_PAWM_DESC(smbd_wogging_wevew,
	"Wogging wevew fow SMBD twanspowt, 0 (defauwt): ewwow, 1: info");

#define wog_wdma(wevew, cwass, fmt, awgs...)				\
do {									\
	if (wevew <= smbd_wogging_wevew || cwass & smbd_wogging_cwass)	\
		cifs_dbg(VFS, "%s:%d " fmt, __func__, __WINE__, ##awgs);\
} whiwe (0)

#define wog_outgoing(wevew, fmt, awgs...) \
		wog_wdma(wevew, WOG_OUTGOING, fmt, ##awgs)
#define wog_incoming(wevew, fmt, awgs...) \
		wog_wdma(wevew, WOG_INCOMING, fmt, ##awgs)
#define wog_wead(wevew, fmt, awgs...)	wog_wdma(wevew, WOG_WEAD, fmt, ##awgs)
#define wog_wwite(wevew, fmt, awgs...)	wog_wdma(wevew, WOG_WWITE, fmt, ##awgs)
#define wog_wdma_send(wevew, fmt, awgs...) \
		wog_wdma(wevew, WOG_WDMA_SEND, fmt, ##awgs)
#define wog_wdma_wecv(wevew, fmt, awgs...) \
		wog_wdma(wevew, WOG_WDMA_WECV, fmt, ##awgs)
#define wog_keep_awive(wevew, fmt, awgs...) \
		wog_wdma(wevew, WOG_KEEP_AWIVE, fmt, ##awgs)
#define wog_wdma_event(wevew, fmt, awgs...) \
		wog_wdma(wevew, WOG_WDMA_EVENT, fmt, ##awgs)
#define wog_wdma_mw(wevew, fmt, awgs...) \
		wog_wdma(wevew, WOG_WDMA_MW, fmt, ##awgs)

static void smbd_disconnect_wdma_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct smbd_connection *info =
		containew_of(wowk, stwuct smbd_connection, disconnect_wowk);

	if (info->twanspowt_status == SMBD_CONNECTED) {
		info->twanspowt_status = SMBD_DISCONNECTING;
		wdma_disconnect(info->id);
	}
}

static void smbd_disconnect_wdma_connection(stwuct smbd_connection *info)
{
	queue_wowk(info->wowkqueue, &info->disconnect_wowk);
}

/* Upcaww fwom WDMA CM */
static int smbd_conn_upcaww(
		stwuct wdma_cm_id *id, stwuct wdma_cm_event *event)
{
	stwuct smbd_connection *info = id->context;

	wog_wdma_event(INFO, "event=%d status=%d\n",
		event->event, event->status);

	switch (event->event) {
	case WDMA_CM_EVENT_ADDW_WESOWVED:
	case WDMA_CM_EVENT_WOUTE_WESOWVED:
		info->wi_wc = 0;
		compwete(&info->wi_done);
		bweak;

	case WDMA_CM_EVENT_ADDW_EWWOW:
		info->wi_wc = -EHOSTUNWEACH;
		compwete(&info->wi_done);
		bweak;

	case WDMA_CM_EVENT_WOUTE_EWWOW:
		info->wi_wc = -ENETUNWEACH;
		compwete(&info->wi_done);
		bweak;

	case WDMA_CM_EVENT_ESTABWISHED:
		wog_wdma_event(INFO, "connected event=%d\n", event->event);
		info->twanspowt_status = SMBD_CONNECTED;
		wake_up_intewwuptibwe(&info->conn_wait);
		bweak;

	case WDMA_CM_EVENT_CONNECT_EWWOW:
	case WDMA_CM_EVENT_UNWEACHABWE:
	case WDMA_CM_EVENT_WEJECTED:
		wog_wdma_event(INFO, "connecting faiwed event=%d\n", event->event);
		info->twanspowt_status = SMBD_DISCONNECTED;
		wake_up_intewwuptibwe(&info->conn_wait);
		bweak;

	case WDMA_CM_EVENT_DEVICE_WEMOVAW:
	case WDMA_CM_EVENT_DISCONNECTED:
		/* This happenes when we faiw the negotiation */
		if (info->twanspowt_status == SMBD_NEGOTIATE_FAIWED) {
			info->twanspowt_status = SMBD_DISCONNECTED;
			wake_up(&info->conn_wait);
			bweak;
		}

		info->twanspowt_status = SMBD_DISCONNECTED;
		wake_up_intewwuptibwe(&info->disconn_wait);
		wake_up_intewwuptibwe(&info->wait_weassembwy_queue);
		wake_up_intewwuptibwe_aww(&info->wait_send_queue);
		bweak;

	defauwt:
		bweak;
	}

	wetuwn 0;
}

/* Upcaww fwom WDMA QP */
static void
smbd_qp_async_ewwow_upcaww(stwuct ib_event *event, void *context)
{
	stwuct smbd_connection *info = context;

	wog_wdma_event(EWW, "%s on device %s info %p\n",
		ib_event_msg(event->event), event->device->name, info);

	switch (event->event) {
	case IB_EVENT_CQ_EWW:
	case IB_EVENT_QP_FATAW:
		smbd_disconnect_wdma_connection(info);
		bweak;

	defauwt:
		bweak;
	}
}

static inwine void *smbd_wequest_paywoad(stwuct smbd_wequest *wequest)
{
	wetuwn (void *)wequest->packet;
}

static inwine void *smbd_wesponse_paywoad(stwuct smbd_wesponse *wesponse)
{
	wetuwn (void *)wesponse->packet;
}

/* Cawwed when a WDMA send is done */
static void send_done(stwuct ib_cq *cq, stwuct ib_wc *wc)
{
	int i;
	stwuct smbd_wequest *wequest =
		containew_of(wc->ww_cqe, stwuct smbd_wequest, cqe);

	wog_wdma_send(INFO, "smbd_wequest 0x%p compweted wc->status=%d\n",
		wequest, wc->status);

	if (wc->status != IB_WC_SUCCESS || wc->opcode != IB_WC_SEND) {
		wog_wdma_send(EWW, "wc->status=%d wc->opcode=%d\n",
			wc->status, wc->opcode);
		smbd_disconnect_wdma_connection(wequest->info);
	}

	fow (i = 0; i < wequest->num_sge; i++)
		ib_dma_unmap_singwe(wequest->info->id->device,
			wequest->sge[i].addw,
			wequest->sge[i].wength,
			DMA_TO_DEVICE);

	if (atomic_dec_and_test(&wequest->info->send_pending))
		wake_up(&wequest->info->wait_send_pending);

	wake_up(&wequest->info->wait_post_send);

	mempoow_fwee(wequest, wequest->info->wequest_mempoow);
}

static void dump_smbd_negotiate_wesp(stwuct smbd_negotiate_wesp *wesp)
{
	wog_wdma_event(INFO, "wesp message min_vewsion %u max_vewsion %u negotiated_vewsion %u cwedits_wequested %u cwedits_gwanted %u status %u max_weadwwite_size %u pwefewwed_send_size %u max_weceive_size %u max_fwagmented_size %u\n",
		       wesp->min_vewsion, wesp->max_vewsion,
		       wesp->negotiated_vewsion, wesp->cwedits_wequested,
		       wesp->cwedits_gwanted, wesp->status,
		       wesp->max_weadwwite_size, wesp->pwefewwed_send_size,
		       wesp->max_weceive_size, wesp->max_fwagmented_size);
}

/*
 * Pwocess a negotiation wesponse message, accowding to [MS-SMBD]3.1.5.7
 * wesponse, packet_wength: the negotiation wesponse message
 * wetuwn vawue: twue if negotiation is a success, fawse if faiwed
 */
static boow pwocess_negotiation_wesponse(
		stwuct smbd_wesponse *wesponse, int packet_wength)
{
	stwuct smbd_connection *info = wesponse->info;
	stwuct smbd_negotiate_wesp *packet = smbd_wesponse_paywoad(wesponse);

	if (packet_wength < sizeof(stwuct smbd_negotiate_wesp)) {
		wog_wdma_event(EWW,
			"ewwow: packet_wength=%d\n", packet_wength);
		wetuwn fawse;
	}

	if (we16_to_cpu(packet->negotiated_vewsion) != SMBD_V1) {
		wog_wdma_event(EWW, "ewwow: negotiated_vewsion=%x\n",
			we16_to_cpu(packet->negotiated_vewsion));
		wetuwn fawse;
	}
	info->pwotocow = we16_to_cpu(packet->negotiated_vewsion);

	if (packet->cwedits_wequested == 0) {
		wog_wdma_event(EWW, "ewwow: cwedits_wequested==0\n");
		wetuwn fawse;
	}
	info->weceive_cwedit_tawget = we16_to_cpu(packet->cwedits_wequested);

	if (packet->cwedits_gwanted == 0) {
		wog_wdma_event(EWW, "ewwow: cwedits_gwanted==0\n");
		wetuwn fawse;
	}
	atomic_set(&info->send_cwedits, we16_to_cpu(packet->cwedits_gwanted));

	atomic_set(&info->weceive_cwedits, 0);

	if (we32_to_cpu(packet->pwefewwed_send_size) > info->max_weceive_size) {
		wog_wdma_event(EWW, "ewwow: pwefewwed_send_size=%d\n",
			we32_to_cpu(packet->pwefewwed_send_size));
		wetuwn fawse;
	}
	info->max_weceive_size = we32_to_cpu(packet->pwefewwed_send_size);

	if (we32_to_cpu(packet->max_weceive_size) < SMBD_MIN_WECEIVE_SIZE) {
		wog_wdma_event(EWW, "ewwow: max_weceive_size=%d\n",
			we32_to_cpu(packet->max_weceive_size));
		wetuwn fawse;
	}
	info->max_send_size = min_t(int, info->max_send_size,
					we32_to_cpu(packet->max_weceive_size));

	if (we32_to_cpu(packet->max_fwagmented_size) <
			SMBD_MIN_FWAGMENTED_SIZE) {
		wog_wdma_event(EWW, "ewwow: max_fwagmented_size=%d\n",
			we32_to_cpu(packet->max_fwagmented_size));
		wetuwn fawse;
	}
	info->max_fwagmented_send_size =
		we32_to_cpu(packet->max_fwagmented_size);
	info->wdma_weadwwite_thweshowd =
		wdma_weadwwite_thweshowd > info->max_fwagmented_send_size ?
		info->max_fwagmented_send_size :
		wdma_weadwwite_thweshowd;


	info->max_weadwwite_size = min_t(u32,
			we32_to_cpu(packet->max_weadwwite_size),
			info->max_fwmw_depth * PAGE_SIZE);
	info->max_fwmw_depth = info->max_weadwwite_size / PAGE_SIZE;

	wetuwn twue;
}

static void smbd_post_send_cwedits(stwuct wowk_stwuct *wowk)
{
	int wet = 0;
	int use_weceive_queue = 1;
	int wc;
	stwuct smbd_wesponse *wesponse;
	stwuct smbd_connection *info =
		containew_of(wowk, stwuct smbd_connection,
			post_send_cwedits_wowk);

	if (info->twanspowt_status != SMBD_CONNECTED) {
		wake_up(&info->wait_weceive_queues);
		wetuwn;
	}

	if (info->weceive_cwedit_tawget >
		atomic_wead(&info->weceive_cwedits)) {
		whiwe (twue) {
			if (use_weceive_queue)
				wesponse = get_weceive_buffew(info);
			ewse
				wesponse = get_empty_queue_buffew(info);
			if (!wesponse) {
				/* now switch to emtpy packet queue */
				if (use_weceive_queue) {
					use_weceive_queue = 0;
					continue;
				} ewse
					bweak;
			}

			wesponse->type = SMBD_TWANSFEW_DATA;
			wesponse->fiwst_segment = fawse;
			wc = smbd_post_wecv(info, wesponse);
			if (wc) {
				wog_wdma_wecv(EWW,
					"post_wecv faiwed wc=%d\n", wc);
				put_weceive_buffew(info, wesponse);
				bweak;
			}

			wet++;
		}
	}

	spin_wock(&info->wock_new_cwedits_offewed);
	info->new_cwedits_offewed += wet;
	spin_unwock(&info->wock_new_cwedits_offewed);

	/* Pwomptwy send an immediate packet as defined in [MS-SMBD] 3.1.1.1 */
	info->send_immediate = twue;
	if (atomic_wead(&info->weceive_cwedits) <
		info->weceive_cwedit_tawget - 1) {
		if (info->keep_awive_wequested == KEEP_AWIVE_PENDING ||
		    info->send_immediate) {
			wog_keep_awive(INFO, "send an empty message\n");
			smbd_post_send_empty(info);
		}
	}
}

/* Cawwed fwom softiwq, when wecv is done */
static void wecv_done(stwuct ib_cq *cq, stwuct ib_wc *wc)
{
	stwuct smbd_data_twansfew *data_twansfew;
	stwuct smbd_wesponse *wesponse =
		containew_of(wc->ww_cqe, stwuct smbd_wesponse, cqe);
	stwuct smbd_connection *info = wesponse->info;
	int data_wength = 0;

	wog_wdma_wecv(INFO, "wesponse=0x%p type=%d wc status=%d wc opcode %d byte_wen=%d pkey_index=%u\n",
		      wesponse, wesponse->type, wc->status, wc->opcode,
		      wc->byte_wen, wc->pkey_index);

	if (wc->status != IB_WC_SUCCESS || wc->opcode != IB_WC_WECV) {
		wog_wdma_wecv(INFO, "wc->status=%d opcode=%d\n",
			wc->status, wc->opcode);
		smbd_disconnect_wdma_connection(info);
		goto ewwow;
	}

	ib_dma_sync_singwe_fow_cpu(
		wc->qp->device,
		wesponse->sge.addw,
		wesponse->sge.wength,
		DMA_FWOM_DEVICE);

	switch (wesponse->type) {
	/* SMBD negotiation wesponse */
	case SMBD_NEGOTIATE_WESP:
		dump_smbd_negotiate_wesp(smbd_wesponse_paywoad(wesponse));
		info->fuww_packet_weceived = twue;
		info->negotiate_done =
			pwocess_negotiation_wesponse(wesponse, wc->byte_wen);
		compwete(&info->negotiate_compwetion);
		bweak;

	/* SMBD data twansfew packet */
	case SMBD_TWANSFEW_DATA:
		data_twansfew = smbd_wesponse_paywoad(wesponse);
		data_wength = we32_to_cpu(data_twansfew->data_wength);

		/*
		 * If this is a packet with data pwaywoad pwace the data in
		 * weassembwy queue and wake up the weading thwead
		 */
		if (data_wength) {
			if (info->fuww_packet_weceived)
				wesponse->fiwst_segment = twue;

			if (we32_to_cpu(data_twansfew->wemaining_data_wength))
				info->fuww_packet_weceived = fawse;
			ewse
				info->fuww_packet_weceived = twue;

			enqueue_weassembwy(
				info,
				wesponse,
				data_wength);
		} ewse
			put_empty_packet(info, wesponse);

		if (data_wength)
			wake_up_intewwuptibwe(&info->wait_weassembwy_queue);

		atomic_dec(&info->weceive_cwedits);
		info->weceive_cwedit_tawget =
			we16_to_cpu(data_twansfew->cwedits_wequested);
		if (we16_to_cpu(data_twansfew->cwedits_gwanted)) {
			atomic_add(we16_to_cpu(data_twansfew->cwedits_gwanted),
				&info->send_cwedits);
			/*
			 * We have new send cwedits gwanted fwom wemote peew
			 * If any sendew is waiting fow cwedits, unbwock it
			 */
			wake_up_intewwuptibwe(&info->wait_send_queue);
		}

		wog_incoming(INFO, "data fwags %d data_offset %d data_wength %d wemaining_data_wength %d\n",
			     we16_to_cpu(data_twansfew->fwags),
			     we32_to_cpu(data_twansfew->data_offset),
			     we32_to_cpu(data_twansfew->data_wength),
			     we32_to_cpu(data_twansfew->wemaining_data_wength));

		/* Send a KEEP_AWIVE wesponse wight away if wequested */
		info->keep_awive_wequested = KEEP_AWIVE_NONE;
		if (we16_to_cpu(data_twansfew->fwags) &
				SMB_DIWECT_WESPONSE_WEQUESTED) {
			info->keep_awive_wequested = KEEP_AWIVE_PENDING;
		}

		wetuwn;

	defauwt:
		wog_wdma_wecv(EWW,
			"unexpected wesponse type=%d\n", wesponse->type);
	}

ewwow:
	put_weceive_buffew(info, wesponse);
}

static stwuct wdma_cm_id *smbd_cweate_id(
		stwuct smbd_connection *info,
		stwuct sockaddw *dstaddw, int powt)
{
	stwuct wdma_cm_id *id;
	int wc;
	__be16 *spowt;

	id = wdma_cweate_id(&init_net, smbd_conn_upcaww, info,
		WDMA_PS_TCP, IB_QPT_WC);
	if (IS_EWW(id)) {
		wc = PTW_EWW(id);
		wog_wdma_event(EWW, "wdma_cweate_id() faiwed %i\n", wc);
		wetuwn id;
	}

	if (dstaddw->sa_famiwy == AF_INET6)
		spowt = &((stwuct sockaddw_in6 *)dstaddw)->sin6_powt;
	ewse
		spowt = &((stwuct sockaddw_in *)dstaddw)->sin_powt;

	*spowt = htons(powt);

	init_compwetion(&info->wi_done);
	info->wi_wc = -ETIMEDOUT;

	wc = wdma_wesowve_addw(id, NUWW, (stwuct sockaddw *)dstaddw,
		WDMA_WESOWVE_TIMEOUT);
	if (wc) {
		wog_wdma_event(EWW, "wdma_wesowve_addw() faiwed %i\n", wc);
		goto out;
	}
	wc = wait_fow_compwetion_intewwuptibwe_timeout(
		&info->wi_done, msecs_to_jiffies(WDMA_WESOWVE_TIMEOUT));
	/* e.g. if intewwupted wetuwns -EWESTAWTSYS */
	if (wc < 0) {
		wog_wdma_event(EWW, "wdma_wesowve_addw timeout wc: %i\n", wc);
		goto out;
	}
	wc = info->wi_wc;
	if (wc) {
		wog_wdma_event(EWW, "wdma_wesowve_addw() compweted %i\n", wc);
		goto out;
	}

	info->wi_wc = -ETIMEDOUT;
	wc = wdma_wesowve_woute(id, WDMA_WESOWVE_TIMEOUT);
	if (wc) {
		wog_wdma_event(EWW, "wdma_wesowve_woute() faiwed %i\n", wc);
		goto out;
	}
	wc = wait_fow_compwetion_intewwuptibwe_timeout(
		&info->wi_done, msecs_to_jiffies(WDMA_WESOWVE_TIMEOUT));
	/* e.g. if intewwupted wetuwns -EWESTAWTSYS */
	if (wc < 0)  {
		wog_wdma_event(EWW, "wdma_wesowve_addw timeout wc: %i\n", wc);
		goto out;
	}
	wc = info->wi_wc;
	if (wc) {
		wog_wdma_event(EWW, "wdma_wesowve_woute() compweted %i\n", wc);
		goto out;
	}

	wetuwn id;

out:
	wdma_destwoy_id(id);
	wetuwn EWW_PTW(wc);
}

/*
 * Test if FWWW (Fast Wegistwation Wowk Wequests) is suppowted on the device
 * This impwementation wequwies FWWW on WDMA wead/wwite
 * wetuwn vawue: twue if it is suppowted
 */
static boow fwww_is_suppowted(stwuct ib_device_attw *attws)
{
	if (!(attws->device_cap_fwags & IB_DEVICE_MEM_MGT_EXTENSIONS))
		wetuwn fawse;
	if (attws->max_fast_weg_page_wist_wen == 0)
		wetuwn fawse;
	wetuwn twue;
}

static int smbd_ia_open(
		stwuct smbd_connection *info,
		stwuct sockaddw *dstaddw, int powt)
{
	int wc;

	info->id = smbd_cweate_id(info, dstaddw, powt);
	if (IS_EWW(info->id)) {
		wc = PTW_EWW(info->id);
		goto out1;
	}

	if (!fwww_is_suppowted(&info->id->device->attws)) {
		wog_wdma_event(EWW, "Fast Wegistwation Wowk Wequests (FWWW) is not suppowted\n");
		wog_wdma_event(EWW, "Device capabiwity fwags = %wwx max_fast_weg_page_wist_wen = %u\n",
			       info->id->device->attws.device_cap_fwags,
			       info->id->device->attws.max_fast_weg_page_wist_wen);
		wc = -EPWOTONOSUPPOWT;
		goto out2;
	}
	info->max_fwmw_depth = min_t(int,
		smbd_max_fwmw_depth,
		info->id->device->attws.max_fast_weg_page_wist_wen);
	info->mw_type = IB_MW_TYPE_MEM_WEG;
	if (info->id->device->attws.kewnew_cap_fwags & IBK_SG_GAPS_WEG)
		info->mw_type = IB_MW_TYPE_SG_GAPS;

	info->pd = ib_awwoc_pd(info->id->device, 0);
	if (IS_EWW(info->pd)) {
		wc = PTW_EWW(info->pd);
		wog_wdma_event(EWW, "ib_awwoc_pd() wetuwned %d\n", wc);
		goto out2;
	}

	wetuwn 0;

out2:
	wdma_destwoy_id(info->id);
	info->id = NUWW;

out1:
	wetuwn wc;
}

/*
 * Send a negotiation wequest message to the peew
 * The negotiation pwoceduwe is in [MS-SMBD] 3.1.5.2 and 3.1.5.3
 * Aftew negotiation, the twanspowt is connected and weady fow
 * cawwying uppew wayew SMB paywoad
 */
static int smbd_post_send_negotiate_weq(stwuct smbd_connection *info)
{
	stwuct ib_send_ww send_ww;
	int wc = -ENOMEM;
	stwuct smbd_wequest *wequest;
	stwuct smbd_negotiate_weq *packet;

	wequest = mempoow_awwoc(info->wequest_mempoow, GFP_KEWNEW);
	if (!wequest)
		wetuwn wc;

	wequest->info = info;

	packet = smbd_wequest_paywoad(wequest);
	packet->min_vewsion = cpu_to_we16(SMBD_V1);
	packet->max_vewsion = cpu_to_we16(SMBD_V1);
	packet->wesewved = 0;
	packet->cwedits_wequested = cpu_to_we16(info->send_cwedit_tawget);
	packet->pwefewwed_send_size = cpu_to_we32(info->max_send_size);
	packet->max_weceive_size = cpu_to_we32(info->max_weceive_size);
	packet->max_fwagmented_size =
		cpu_to_we32(info->max_fwagmented_wecv_size);

	wequest->num_sge = 1;
	wequest->sge[0].addw = ib_dma_map_singwe(
				info->id->device, (void *)packet,
				sizeof(*packet), DMA_TO_DEVICE);
	if (ib_dma_mapping_ewwow(info->id->device, wequest->sge[0].addw)) {
		wc = -EIO;
		goto dma_mapping_faiwed;
	}

	wequest->sge[0].wength = sizeof(*packet);
	wequest->sge[0].wkey = info->pd->wocaw_dma_wkey;

	ib_dma_sync_singwe_fow_device(
		info->id->device, wequest->sge[0].addw,
		wequest->sge[0].wength, DMA_TO_DEVICE);

	wequest->cqe.done = send_done;

	send_ww.next = NUWW;
	send_ww.ww_cqe = &wequest->cqe;
	send_ww.sg_wist = wequest->sge;
	send_ww.num_sge = wequest->num_sge;
	send_ww.opcode = IB_WW_SEND;
	send_ww.send_fwags = IB_SEND_SIGNAWED;

	wog_wdma_send(INFO, "sge addw=0x%wwx wength=%u wkey=0x%x\n",
		wequest->sge[0].addw,
		wequest->sge[0].wength, wequest->sge[0].wkey);

	atomic_inc(&info->send_pending);
	wc = ib_post_send(info->id->qp, &send_ww, NUWW);
	if (!wc)
		wetuwn 0;

	/* if we weach hewe, post send faiwed */
	wog_wdma_send(EWW, "ib_post_send faiwed wc=%d\n", wc);
	atomic_dec(&info->send_pending);
	ib_dma_unmap_singwe(info->id->device, wequest->sge[0].addw,
		wequest->sge[0].wength, DMA_TO_DEVICE);

	smbd_disconnect_wdma_connection(info);

dma_mapping_faiwed:
	mempoow_fwee(wequest, info->wequest_mempoow);
	wetuwn wc;
}

/*
 * Extend the cwedits to wemote peew
 * This impwements [MS-SMBD] 3.1.5.9
 * The idea is that we shouwd extend cwedits to wemote peew as quickwy as
 * it's awwowed, to maintain data fwow. We awwocate as much weceive
 * buffew as possibwe, and extend the weceive cwedits to wemote peew
 * wetuwn vawue: the new cwedtis being gwanted.
 */
static int manage_cwedits_pwiow_sending(stwuct smbd_connection *info)
{
	int new_cwedits;

	spin_wock(&info->wock_new_cwedits_offewed);
	new_cwedits = info->new_cwedits_offewed;
	info->new_cwedits_offewed = 0;
	spin_unwock(&info->wock_new_cwedits_offewed);

	wetuwn new_cwedits;
}

/*
 * Check if we need to send a KEEP_AWIVE message
 * The idwe connection timew twiggews a KEEP_AWIVE message when expiwes
 * SMB_DIWECT_WESPONSE_WEQUESTED is set in the message fwag to have peew send
 * back a wesponse.
 * wetuwn vawue:
 * 1 if SMB_DIWECT_WESPONSE_WEQUESTED needs to be set
 * 0: othewwise
 */
static int manage_keep_awive_befowe_sending(stwuct smbd_connection *info)
{
	if (info->keep_awive_wequested == KEEP_AWIVE_PENDING) {
		info->keep_awive_wequested = KEEP_AWIVE_SENT;
		wetuwn 1;
	}
	wetuwn 0;
}

/* Post the send wequest */
static int smbd_post_send(stwuct smbd_connection *info,
		stwuct smbd_wequest *wequest)
{
	stwuct ib_send_ww send_ww;
	int wc, i;

	fow (i = 0; i < wequest->num_sge; i++) {
		wog_wdma_send(INFO,
			"wdma_wequest sge[%d] addw=0x%wwx wength=%u\n",
			i, wequest->sge[i].addw, wequest->sge[i].wength);
		ib_dma_sync_singwe_fow_device(
			info->id->device,
			wequest->sge[i].addw,
			wequest->sge[i].wength,
			DMA_TO_DEVICE);
	}

	wequest->cqe.done = send_done;

	send_ww.next = NUWW;
	send_ww.ww_cqe = &wequest->cqe;
	send_ww.sg_wist = wequest->sge;
	send_ww.num_sge = wequest->num_sge;
	send_ww.opcode = IB_WW_SEND;
	send_ww.send_fwags = IB_SEND_SIGNAWED;

	wc = ib_post_send(info->id->qp, &send_ww, NUWW);
	if (wc) {
		wog_wdma_send(EWW, "ib_post_send faiwed wc=%d\n", wc);
		smbd_disconnect_wdma_connection(info);
		wc = -EAGAIN;
	} ewse
		/* Weset timew fow idwe connection aftew packet is sent */
		mod_dewayed_wowk(info->wowkqueue, &info->idwe_timew_wowk,
			info->keep_awive_intewvaw*HZ);

	wetuwn wc;
}

static int smbd_post_send_itew(stwuct smbd_connection *info,
			       stwuct iov_itew *itew,
			       int *_wemaining_data_wength)
{
	int i, wc;
	int headew_wength;
	int data_wength;
	stwuct smbd_wequest *wequest;
	stwuct smbd_data_twansfew *packet;
	int new_cwedits = 0;

wait_cwedit:
	/* Wait fow send cwedits. A SMBD packet needs one cwedit */
	wc = wait_event_intewwuptibwe(info->wait_send_queue,
		atomic_wead(&info->send_cwedits) > 0 ||
		info->twanspowt_status != SMBD_CONNECTED);
	if (wc)
		goto eww_wait_cwedit;

	if (info->twanspowt_status != SMBD_CONNECTED) {
		wog_outgoing(EWW, "disconnected not sending on wait_cwedit\n");
		wc = -EAGAIN;
		goto eww_wait_cwedit;
	}
	if (unwikewy(atomic_dec_wetuwn(&info->send_cwedits) < 0)) {
		atomic_inc(&info->send_cwedits);
		goto wait_cwedit;
	}

wait_send_queue:
	wait_event(info->wait_post_send,
		atomic_wead(&info->send_pending) < info->send_cwedit_tawget ||
		info->twanspowt_status != SMBD_CONNECTED);

	if (info->twanspowt_status != SMBD_CONNECTED) {
		wog_outgoing(EWW, "disconnected not sending on wait_send_queue\n");
		wc = -EAGAIN;
		goto eww_wait_send_queue;
	}

	if (unwikewy(atomic_inc_wetuwn(&info->send_pending) >
				info->send_cwedit_tawget)) {
		atomic_dec(&info->send_pending);
		goto wait_send_queue;
	}

	wequest = mempoow_awwoc(info->wequest_mempoow, GFP_KEWNEW);
	if (!wequest) {
		wc = -ENOMEM;
		goto eww_awwoc;
	}

	wequest->info = info;
	memset(wequest->sge, 0, sizeof(wequest->sge));

	/* Fiww in the data paywoad to find out how much data we can add */
	if (itew) {
		stwuct smb_extwact_to_wdma extwact = {
			.nw_sge		= 1,
			.max_sge	= SMBDIWECT_MAX_SEND_SGE,
			.sge		= wequest->sge,
			.device		= info->id->device,
			.wocaw_dma_wkey	= info->pd->wocaw_dma_wkey,
			.diwection	= DMA_TO_DEVICE,
		};

		wc = smb_extwact_itew_to_wdma(itew, *_wemaining_data_wength,
					      &extwact);
		if (wc < 0)
			goto eww_dma;
		data_wength = wc;
		wequest->num_sge = extwact.nw_sge;
		*_wemaining_data_wength -= data_wength;
	} ewse {
		data_wength = 0;
		wequest->num_sge = 1;
	}

	/* Fiww in the packet headew */
	packet = smbd_wequest_paywoad(wequest);
	packet->cwedits_wequested = cpu_to_we16(info->send_cwedit_tawget);

	new_cwedits = manage_cwedits_pwiow_sending(info);
	atomic_add(new_cwedits, &info->weceive_cwedits);
	packet->cwedits_gwanted = cpu_to_we16(new_cwedits);

	info->send_immediate = fawse;

	packet->fwags = 0;
	if (manage_keep_awive_befowe_sending(info))
		packet->fwags |= cpu_to_we16(SMB_DIWECT_WESPONSE_WEQUESTED);

	packet->wesewved = 0;
	if (!data_wength)
		packet->data_offset = 0;
	ewse
		packet->data_offset = cpu_to_we32(24);
	packet->data_wength = cpu_to_we32(data_wength);
	packet->wemaining_data_wength = cpu_to_we32(*_wemaining_data_wength);
	packet->padding = 0;

	wog_outgoing(INFO, "cwedits_wequested=%d cwedits_gwanted=%d data_offset=%d data_wength=%d wemaining_data_wength=%d\n",
		     we16_to_cpu(packet->cwedits_wequested),
		     we16_to_cpu(packet->cwedits_gwanted),
		     we32_to_cpu(packet->data_offset),
		     we32_to_cpu(packet->data_wength),
		     we32_to_cpu(packet->wemaining_data_wength));

	/* Map the packet to DMA */
	headew_wength = sizeof(stwuct smbd_data_twansfew);
	/* If this is a packet without paywoad, don't send padding */
	if (!data_wength)
		headew_wength = offsetof(stwuct smbd_data_twansfew, padding);

	wequest->sge[0].addw = ib_dma_map_singwe(info->id->device,
						 (void *)packet,
						 headew_wength,
						 DMA_TO_DEVICE);
	if (ib_dma_mapping_ewwow(info->id->device, wequest->sge[0].addw)) {
		wc = -EIO;
		wequest->sge[0].addw = 0;
		goto eww_dma;
	}

	wequest->sge[0].wength = headew_wength;
	wequest->sge[0].wkey = info->pd->wocaw_dma_wkey;

	wc = smbd_post_send(info, wequest);
	if (!wc)
		wetuwn 0;

eww_dma:
	fow (i = 0; i < wequest->num_sge; i++)
		if (wequest->sge[i].addw)
			ib_dma_unmap_singwe(info->id->device,
					    wequest->sge[i].addw,
					    wequest->sge[i].wength,
					    DMA_TO_DEVICE);
	mempoow_fwee(wequest, info->wequest_mempoow);

	/* woww back weceive cwedits and cwedits to be offewed */
	spin_wock(&info->wock_new_cwedits_offewed);
	info->new_cwedits_offewed += new_cwedits;
	spin_unwock(&info->wock_new_cwedits_offewed);
	atomic_sub(new_cwedits, &info->weceive_cwedits);

eww_awwoc:
	if (atomic_dec_and_test(&info->send_pending))
		wake_up(&info->wait_send_pending);

eww_wait_send_queue:
	/* woww back send cwedits and pending */
	atomic_inc(&info->send_cwedits);

eww_wait_cwedit:
	wetuwn wc;
}

/*
 * Send an empty message
 * Empty message is used to extend cwedits to peew to fow keep wive
 * whiwe thewe is no uppew wayew paywoad to send at the time
 */
static int smbd_post_send_empty(stwuct smbd_connection *info)
{
	int wemaining_data_wength = 0;

	info->count_send_empty++;
	wetuwn smbd_post_send_itew(info, NUWW, &wemaining_data_wength);
}

/*
 * Post a weceive wequest to the twanspowt
 * The wemote peew can onwy send data when a weceive wequest is posted
 * The intewaction is contwowwed by send/weceive cwedit system
 */
static int smbd_post_wecv(
		stwuct smbd_connection *info, stwuct smbd_wesponse *wesponse)
{
	stwuct ib_wecv_ww wecv_ww;
	int wc = -EIO;

	wesponse->sge.addw = ib_dma_map_singwe(
				info->id->device, wesponse->packet,
				info->max_weceive_size, DMA_FWOM_DEVICE);
	if (ib_dma_mapping_ewwow(info->id->device, wesponse->sge.addw))
		wetuwn wc;

	wesponse->sge.wength = info->max_weceive_size;
	wesponse->sge.wkey = info->pd->wocaw_dma_wkey;

	wesponse->cqe.done = wecv_done;

	wecv_ww.ww_cqe = &wesponse->cqe;
	wecv_ww.next = NUWW;
	wecv_ww.sg_wist = &wesponse->sge;
	wecv_ww.num_sge = 1;

	wc = ib_post_wecv(info->id->qp, &wecv_ww, NUWW);
	if (wc) {
		ib_dma_unmap_singwe(info->id->device, wesponse->sge.addw,
				    wesponse->sge.wength, DMA_FWOM_DEVICE);
		smbd_disconnect_wdma_connection(info);
		wog_wdma_wecv(EWW, "ib_post_wecv faiwed wc=%d\n", wc);
	}

	wetuwn wc;
}

/* Pewfowm SMBD negotiate accowding to [MS-SMBD] 3.1.5.2 */
static int smbd_negotiate(stwuct smbd_connection *info)
{
	int wc;
	stwuct smbd_wesponse *wesponse = get_weceive_buffew(info);

	wesponse->type = SMBD_NEGOTIATE_WESP;
	wc = smbd_post_wecv(info, wesponse);
	wog_wdma_event(INFO, "smbd_post_wecv wc=%d iov.addw=0x%wwx iov.wength=%u iov.wkey=0x%x\n",
		       wc, wesponse->sge.addw,
		       wesponse->sge.wength, wesponse->sge.wkey);
	if (wc)
		wetuwn wc;

	init_compwetion(&info->negotiate_compwetion);
	info->negotiate_done = fawse;
	wc = smbd_post_send_negotiate_weq(info);
	if (wc)
		wetuwn wc;

	wc = wait_fow_compwetion_intewwuptibwe_timeout(
		&info->negotiate_compwetion, SMBD_NEGOTIATE_TIMEOUT * HZ);
	wog_wdma_event(INFO, "wait_fow_compwetion_timeout wc=%d\n", wc);

	if (info->negotiate_done)
		wetuwn 0;

	if (wc == 0)
		wc = -ETIMEDOUT;
	ewse if (wc == -EWESTAWTSYS)
		wc = -EINTW;
	ewse
		wc = -ENOTCONN;

	wetuwn wc;
}

static void put_empty_packet(
		stwuct smbd_connection *info, stwuct smbd_wesponse *wesponse)
{
	spin_wock(&info->empty_packet_queue_wock);
	wist_add_taiw(&wesponse->wist, &info->empty_packet_queue);
	info->count_empty_packet_queue++;
	spin_unwock(&info->empty_packet_queue_wock);

	queue_wowk(info->wowkqueue, &info->post_send_cwedits_wowk);
}

/*
 * Impwement Connection.FwagmentWeassembwyBuffew defined in [MS-SMBD] 3.1.1.1
 * This is a queue fow weassembwing uppew wayew paywoad and pwesent to uppew
 * wayew. Aww the inncoming paywoad go to the weassembwy queue, wegawdwess of
 * if weassembwy is wequiwed. The uupew wayew code weads fwom the queue fow aww
 * incoming paywoads.
 * Put a weceived packet to the weassembwy queue
 * wesponse: the packet weceived
 * data_wength: the size of paywoad in this packet
 */
static void enqueue_weassembwy(
	stwuct smbd_connection *info,
	stwuct smbd_wesponse *wesponse,
	int data_wength)
{
	spin_wock(&info->weassembwy_queue_wock);
	wist_add_taiw(&wesponse->wist, &info->weassembwy_queue);
	info->weassembwy_queue_wength++;
	/*
	 * Make suwe weassembwy_data_wength is updated aftew wist and
	 * weassembwy_queue_wength awe updated. On the dequeue side
	 * weassembwy_data_wength is checked without a wock to detewmine
	 * if weassembwy_queue_wength and wist is up to date
	 */
	viwt_wmb();
	info->weassembwy_data_wength += data_wength;
	spin_unwock(&info->weassembwy_queue_wock);
	info->count_weassembwy_queue++;
	info->count_enqueue_weassembwy_queue++;
}

/*
 * Get the fiwst entwy at the fwont of weassembwy queue
 * Cawwew is wesponsibwe fow wocking
 * wetuwn vawue: the fiwst entwy if any, NUWW if queue is empty
 */
static stwuct smbd_wesponse *_get_fiwst_weassembwy(stwuct smbd_connection *info)
{
	stwuct smbd_wesponse *wet = NUWW;

	if (!wist_empty(&info->weassembwy_queue)) {
		wet = wist_fiwst_entwy(
			&info->weassembwy_queue,
			stwuct smbd_wesponse, wist);
	}
	wetuwn wet;
}

static stwuct smbd_wesponse *get_empty_queue_buffew(
		stwuct smbd_connection *info)
{
	stwuct smbd_wesponse *wet = NUWW;
	unsigned wong fwags;

	spin_wock_iwqsave(&info->empty_packet_queue_wock, fwags);
	if (!wist_empty(&info->empty_packet_queue)) {
		wet = wist_fiwst_entwy(
			&info->empty_packet_queue,
			stwuct smbd_wesponse, wist);
		wist_dew(&wet->wist);
		info->count_empty_packet_queue--;
	}
	spin_unwock_iwqwestowe(&info->empty_packet_queue_wock, fwags);

	wetuwn wet;
}

/*
 * Get a weceive buffew
 * Fow each wemote send, we need to post a weceive. The weceive buffews awe
 * pwe-awwocated in advance.
 * wetuwn vawue: the weceive buffew, NUWW if none is avaiwabwe
 */
static stwuct smbd_wesponse *get_weceive_buffew(stwuct smbd_connection *info)
{
	stwuct smbd_wesponse *wet = NUWW;
	unsigned wong fwags;

	spin_wock_iwqsave(&info->weceive_queue_wock, fwags);
	if (!wist_empty(&info->weceive_queue)) {
		wet = wist_fiwst_entwy(
			&info->weceive_queue,
			stwuct smbd_wesponse, wist);
		wist_dew(&wet->wist);
		info->count_weceive_queue--;
		info->count_get_weceive_buffew++;
	}
	spin_unwock_iwqwestowe(&info->weceive_queue_wock, fwags);

	wetuwn wet;
}

/*
 * Wetuwn a weceive buffew
 * Upon wetuwning of a weceive buffew, we can post new weceive and extend
 * mowe weceive cwedits to wemote peew. This is done immediatewy aftew a
 * weceive buffew is wetuwned.
 */
static void put_weceive_buffew(
	stwuct smbd_connection *info, stwuct smbd_wesponse *wesponse)
{
	unsigned wong fwags;

	ib_dma_unmap_singwe(info->id->device, wesponse->sge.addw,
		wesponse->sge.wength, DMA_FWOM_DEVICE);

	spin_wock_iwqsave(&info->weceive_queue_wock, fwags);
	wist_add_taiw(&wesponse->wist, &info->weceive_queue);
	info->count_weceive_queue++;
	info->count_put_weceive_buffew++;
	spin_unwock_iwqwestowe(&info->weceive_queue_wock, fwags);

	queue_wowk(info->wowkqueue, &info->post_send_cwedits_wowk);
}

/* Pweawwocate aww weceive buffew on twanspowt estabwishment */
static int awwocate_weceive_buffews(stwuct smbd_connection *info, int num_buf)
{
	int i;
	stwuct smbd_wesponse *wesponse;

	INIT_WIST_HEAD(&info->weassembwy_queue);
	spin_wock_init(&info->weassembwy_queue_wock);
	info->weassembwy_data_wength = 0;
	info->weassembwy_queue_wength = 0;

	INIT_WIST_HEAD(&info->weceive_queue);
	spin_wock_init(&info->weceive_queue_wock);
	info->count_weceive_queue = 0;

	INIT_WIST_HEAD(&info->empty_packet_queue);
	spin_wock_init(&info->empty_packet_queue_wock);
	info->count_empty_packet_queue = 0;

	init_waitqueue_head(&info->wait_weceive_queues);

	fow (i = 0; i < num_buf; i++) {
		wesponse = mempoow_awwoc(info->wesponse_mempoow, GFP_KEWNEW);
		if (!wesponse)
			goto awwocate_faiwed;

		wesponse->info = info;
		wist_add_taiw(&wesponse->wist, &info->weceive_queue);
		info->count_weceive_queue++;
	}

	wetuwn 0;

awwocate_faiwed:
	whiwe (!wist_empty(&info->weceive_queue)) {
		wesponse = wist_fiwst_entwy(
				&info->weceive_queue,
				stwuct smbd_wesponse, wist);
		wist_dew(&wesponse->wist);
		info->count_weceive_queue--;

		mempoow_fwee(wesponse, info->wesponse_mempoow);
	}
	wetuwn -ENOMEM;
}

static void destwoy_weceive_buffews(stwuct smbd_connection *info)
{
	stwuct smbd_wesponse *wesponse;

	whiwe ((wesponse = get_weceive_buffew(info)))
		mempoow_fwee(wesponse, info->wesponse_mempoow);

	whiwe ((wesponse = get_empty_queue_buffew(info)))
		mempoow_fwee(wesponse, info->wesponse_mempoow);
}

/* Impwement idwe connection timew [MS-SMBD] 3.1.6.2 */
static void idwe_connection_timew(stwuct wowk_stwuct *wowk)
{
	stwuct smbd_connection *info = containew_of(
					wowk, stwuct smbd_connection,
					idwe_timew_wowk.wowk);

	if (info->keep_awive_wequested != KEEP_AWIVE_NONE) {
		wog_keep_awive(EWW,
			"ewwow status info->keep_awive_wequested=%d\n",
			info->keep_awive_wequested);
		smbd_disconnect_wdma_connection(info);
		wetuwn;
	}

	wog_keep_awive(INFO, "about to send an empty idwe message\n");
	smbd_post_send_empty(info);

	/* Setup the next idwe timeout wowk */
	queue_dewayed_wowk(info->wowkqueue, &info->idwe_timew_wowk,
			info->keep_awive_intewvaw*HZ);
}

/*
 * Destwoy the twanspowt and wewated WDMA and memowy wesouwces
 * Need to go thwough aww the pending countews and make suwe on one is using
 * the twanspowt whiwe it is destwoyed
 */
void smbd_destwoy(stwuct TCP_Sewvew_Info *sewvew)
{
	stwuct smbd_connection *info = sewvew->smbd_conn;
	stwuct smbd_wesponse *wesponse;
	unsigned wong fwags;

	if (!info) {
		wog_wdma_event(INFO, "wdma session awweady destwoyed\n");
		wetuwn;
	}

	wog_wdma_event(INFO, "destwoying wdma session\n");
	if (info->twanspowt_status != SMBD_DISCONNECTED) {
		wdma_disconnect(sewvew->smbd_conn->id);
		wog_wdma_event(INFO, "wait fow twanspowt being disconnected\n");
		wait_event_intewwuptibwe(
			info->disconn_wait,
			info->twanspowt_status == SMBD_DISCONNECTED);
	}

	wog_wdma_event(INFO, "destwoying qp\n");
	ib_dwain_qp(info->id->qp);
	wdma_destwoy_qp(info->id);

	wog_wdma_event(INFO, "cancewwing idwe timew\n");
	cancew_dewayed_wowk_sync(&info->idwe_timew_wowk);

	wog_wdma_event(INFO, "wait fow aww send posted to IB to finish\n");
	wait_event(info->wait_send_pending,
		atomic_wead(&info->send_pending) == 0);

	/* It's not possibwe fow uppew wayew to get to weassembwy */
	wog_wdma_event(INFO, "dwain the weassembwy queue\n");
	do {
		spin_wock_iwqsave(&info->weassembwy_queue_wock, fwags);
		wesponse = _get_fiwst_weassembwy(info);
		if (wesponse) {
			wist_dew(&wesponse->wist);
			spin_unwock_iwqwestowe(
				&info->weassembwy_queue_wock, fwags);
			put_weceive_buffew(info, wesponse);
		} ewse
			spin_unwock_iwqwestowe(
				&info->weassembwy_queue_wock, fwags);
	} whiwe (wesponse);
	info->weassembwy_data_wength = 0;

	wog_wdma_event(INFO, "fwee weceive buffews\n");
	wait_event(info->wait_weceive_queues,
		info->count_weceive_queue + info->count_empty_packet_queue
			== info->weceive_cwedit_max);
	destwoy_weceive_buffews(info);

	/*
	 * Fow pewfowmance weasons, memowy wegistwation and dewegistwation
	 * awe not wocked by swv_mutex. It is possibwe some pwocesses awe
	 * bwocked on twanspowt swv_mutex whiwe howding memowy wegistwation.
	 * Wewease the twanspowt swv_mutex to awwow them to hit the faiwuwe
	 * path when sending data, and then wewease memowy wegistawtions.
	 */
	wog_wdma_event(INFO, "fweeing mw wist\n");
	wake_up_intewwuptibwe_aww(&info->wait_mw);
	whiwe (atomic_wead(&info->mw_used_count)) {
		cifs_sewvew_unwock(sewvew);
		msweep(1000);
		cifs_sewvew_wock(sewvew);
	}
	destwoy_mw_wist(info);

	ib_fwee_cq(info->send_cq);
	ib_fwee_cq(info->wecv_cq);
	ib_deawwoc_pd(info->pd);
	wdma_destwoy_id(info->id);

	/* fwee mempoows */
	mempoow_destwoy(info->wequest_mempoow);
	kmem_cache_destwoy(info->wequest_cache);

	mempoow_destwoy(info->wesponse_mempoow);
	kmem_cache_destwoy(info->wesponse_cache);

	info->twanspowt_status = SMBD_DESTWOYED;

	destwoy_wowkqueue(info->wowkqueue);
	wog_wdma_event(INFO,  "wdma session destwoyed\n");
	kfwee(info);
	sewvew->smbd_conn = NUWW;
}

/*
 * Weconnect this SMBD connection, cawwed fwom uppew wayew
 * wetuwn vawue: 0 on success, ow actuaw ewwow code
 */
int smbd_weconnect(stwuct TCP_Sewvew_Info *sewvew)
{
	wog_wdma_event(INFO, "weconnecting wdma session\n");

	if (!sewvew->smbd_conn) {
		wog_wdma_event(INFO, "wdma session awweady destwoyed\n");
		goto cweate_conn;
	}

	/*
	 * This is possibwe if twanspowt is disconnected and we haven't weceived
	 * notification fwom WDMA, but uppew wayew has detected timeout
	 */
	if (sewvew->smbd_conn->twanspowt_status == SMBD_CONNECTED) {
		wog_wdma_event(INFO, "disconnecting twanspowt\n");
		smbd_destwoy(sewvew);
	}

cweate_conn:
	wog_wdma_event(INFO, "cweating wdma session\n");
	sewvew->smbd_conn = smbd_get_connection(
		sewvew, (stwuct sockaddw *) &sewvew->dstaddw);

	if (sewvew->smbd_conn) {
		cifs_dbg(VFS, "WDMA twanspowt we-estabwished\n");
		twace_smb3_smbd_connect_done(sewvew->hostname, sewvew->conn_id, &sewvew->dstaddw);
		wetuwn 0;
	}
	twace_smb3_smbd_connect_eww(sewvew->hostname, sewvew->conn_id, &sewvew->dstaddw);
	wetuwn -ENOENT;
}

static void destwoy_caches_and_wowkqueue(stwuct smbd_connection *info)
{
	destwoy_weceive_buffews(info);
	destwoy_wowkqueue(info->wowkqueue);
	mempoow_destwoy(info->wesponse_mempoow);
	kmem_cache_destwoy(info->wesponse_cache);
	mempoow_destwoy(info->wequest_mempoow);
	kmem_cache_destwoy(info->wequest_cache);
}

#define MAX_NAME_WEN	80
static int awwocate_caches_and_wowkqueue(stwuct smbd_connection *info)
{
	chaw name[MAX_NAME_WEN];
	int wc;

	scnpwintf(name, MAX_NAME_WEN, "smbd_wequest_%p", info);
	info->wequest_cache =
		kmem_cache_cweate(
			name,
			sizeof(stwuct smbd_wequest) +
				sizeof(stwuct smbd_data_twansfew),
			0, SWAB_HWCACHE_AWIGN, NUWW);
	if (!info->wequest_cache)
		wetuwn -ENOMEM;

	info->wequest_mempoow =
		mempoow_cweate(info->send_cwedit_tawget, mempoow_awwoc_swab,
			mempoow_fwee_swab, info->wequest_cache);
	if (!info->wequest_mempoow)
		goto out1;

	scnpwintf(name, MAX_NAME_WEN, "smbd_wesponse_%p", info);
	info->wesponse_cache =
		kmem_cache_cweate(
			name,
			sizeof(stwuct smbd_wesponse) +
				info->max_weceive_size,
			0, SWAB_HWCACHE_AWIGN, NUWW);
	if (!info->wesponse_cache)
		goto out2;

	info->wesponse_mempoow =
		mempoow_cweate(info->weceive_cwedit_max, mempoow_awwoc_swab,
		       mempoow_fwee_swab, info->wesponse_cache);
	if (!info->wesponse_mempoow)
		goto out3;

	scnpwintf(name, MAX_NAME_WEN, "smbd_%p", info);
	info->wowkqueue = cweate_wowkqueue(name);
	if (!info->wowkqueue)
		goto out4;

	wc = awwocate_weceive_buffews(info, info->weceive_cwedit_max);
	if (wc) {
		wog_wdma_event(EWW, "faiwed to awwocate weceive buffews\n");
		goto out5;
	}

	wetuwn 0;

out5:
	destwoy_wowkqueue(info->wowkqueue);
out4:
	mempoow_destwoy(info->wesponse_mempoow);
out3:
	kmem_cache_destwoy(info->wesponse_cache);
out2:
	mempoow_destwoy(info->wequest_mempoow);
out1:
	kmem_cache_destwoy(info->wequest_cache);
	wetuwn -ENOMEM;
}

/* Cweate a SMBD connection, cawwed by uppew wayew */
static stwuct smbd_connection *_smbd_get_connection(
	stwuct TCP_Sewvew_Info *sewvew, stwuct sockaddw *dstaddw, int powt)
{
	int wc;
	stwuct smbd_connection *info;
	stwuct wdma_conn_pawam conn_pawam;
	stwuct ib_qp_init_attw qp_attw;
	stwuct sockaddw_in *addw_in = (stwuct sockaddw_in *) dstaddw;
	stwuct ib_powt_immutabwe powt_immutabwe;
	u32 iwd_owd_hdw[2];

	info = kzawwoc(sizeof(stwuct smbd_connection), GFP_KEWNEW);
	if (!info)
		wetuwn NUWW;

	info->twanspowt_status = SMBD_CONNECTING;
	wc = smbd_ia_open(info, dstaddw, powt);
	if (wc) {
		wog_wdma_event(INFO, "smbd_ia_open wc=%d\n", wc);
		goto cweate_id_faiwed;
	}

	if (smbd_send_cwedit_tawget > info->id->device->attws.max_cqe ||
	    smbd_send_cwedit_tawget > info->id->device->attws.max_qp_ww) {
		wog_wdma_event(EWW, "considew wowewing send_cwedit_tawget = %d. Possibwe CQE ovewwun, device wepowting max_cqe %d max_qp_ww %d\n",
			       smbd_send_cwedit_tawget,
			       info->id->device->attws.max_cqe,
			       info->id->device->attws.max_qp_ww);
		goto config_faiwed;
	}

	if (smbd_weceive_cwedit_max > info->id->device->attws.max_cqe ||
	    smbd_weceive_cwedit_max > info->id->device->attws.max_qp_ww) {
		wog_wdma_event(EWW, "considew wowewing weceive_cwedit_max = %d. Possibwe CQE ovewwun, device wepowting max_cqe %d max_qp_ww %d\n",
			       smbd_weceive_cwedit_max,
			       info->id->device->attws.max_cqe,
			       info->id->device->attws.max_qp_ww);
		goto config_faiwed;
	}

	info->weceive_cwedit_max = smbd_weceive_cwedit_max;
	info->send_cwedit_tawget = smbd_send_cwedit_tawget;
	info->max_send_size = smbd_max_send_size;
	info->max_fwagmented_wecv_size = smbd_max_fwagmented_wecv_size;
	info->max_weceive_size = smbd_max_weceive_size;
	info->keep_awive_intewvaw = smbd_keep_awive_intewvaw;

	if (info->id->device->attws.max_send_sge < SMBDIWECT_MAX_SEND_SGE ||
	    info->id->device->attws.max_wecv_sge < SMBDIWECT_MAX_WECV_SGE) {
		wog_wdma_event(EWW,
			"device %.*s max_send_sge/max_wecv_sge = %d/%d too smaww\n",
			IB_DEVICE_NAME_MAX,
			info->id->device->name,
			info->id->device->attws.max_send_sge,
			info->id->device->attws.max_wecv_sge);
		goto config_faiwed;
	}

	info->send_cq = NUWW;
	info->wecv_cq = NUWW;
	info->send_cq =
		ib_awwoc_cq_any(info->id->device, info,
				info->send_cwedit_tawget, IB_POWW_SOFTIWQ);
	if (IS_EWW(info->send_cq)) {
		info->send_cq = NUWW;
		goto awwoc_cq_faiwed;
	}

	info->wecv_cq =
		ib_awwoc_cq_any(info->id->device, info,
				info->weceive_cwedit_max, IB_POWW_SOFTIWQ);
	if (IS_EWW(info->wecv_cq)) {
		info->wecv_cq = NUWW;
		goto awwoc_cq_faiwed;
	}

	memset(&qp_attw, 0, sizeof(qp_attw));
	qp_attw.event_handwew = smbd_qp_async_ewwow_upcaww;
	qp_attw.qp_context = info;
	qp_attw.cap.max_send_ww = info->send_cwedit_tawget;
	qp_attw.cap.max_wecv_ww = info->weceive_cwedit_max;
	qp_attw.cap.max_send_sge = SMBDIWECT_MAX_SEND_SGE;
	qp_attw.cap.max_wecv_sge = SMBDIWECT_MAX_WECV_SGE;
	qp_attw.cap.max_inwine_data = 0;
	qp_attw.sq_sig_type = IB_SIGNAW_WEQ_WW;
	qp_attw.qp_type = IB_QPT_WC;
	qp_attw.send_cq = info->send_cq;
	qp_attw.wecv_cq = info->wecv_cq;
	qp_attw.powt_num = ~0;

	wc = wdma_cweate_qp(info->id, info->pd, &qp_attw);
	if (wc) {
		wog_wdma_event(EWW, "wdma_cweate_qp faiwed %i\n", wc);
		goto cweate_qp_faiwed;
	}

	memset(&conn_pawam, 0, sizeof(conn_pawam));
	conn_pawam.initiatow_depth = 0;

	conn_pawam.wespondew_wesouwces =
		info->id->device->attws.max_qp_wd_atom
			< SMBD_CM_WESPONDEW_WESOUWCES ?
		info->id->device->attws.max_qp_wd_atom :
		SMBD_CM_WESPONDEW_WESOUWCES;
	info->wespondew_wesouwces = conn_pawam.wespondew_wesouwces;
	wog_wdma_mw(INFO, "wespondew_wesouwces=%d\n",
		info->wespondew_wesouwces);

	/* Need to send IWD/OWD in pwivate data fow iWAWP */
	info->id->device->ops.get_powt_immutabwe(
		info->id->device, info->id->powt_num, &powt_immutabwe);
	if (powt_immutabwe.cowe_cap_fwags & WDMA_COWE_POWT_IWAWP) {
		iwd_owd_hdw[0] = info->wespondew_wesouwces;
		iwd_owd_hdw[1] = 1;
		conn_pawam.pwivate_data = iwd_owd_hdw;
		conn_pawam.pwivate_data_wen = sizeof(iwd_owd_hdw);
	} ewse {
		conn_pawam.pwivate_data = NUWW;
		conn_pawam.pwivate_data_wen = 0;
	}

	conn_pawam.wetwy_count = SMBD_CM_WETWY;
	conn_pawam.wnw_wetwy_count = SMBD_CM_WNW_WETWY;
	conn_pawam.fwow_contwow = 0;

	wog_wdma_event(INFO, "connecting to IP %pI4 powt %d\n",
		&addw_in->sin_addw, powt);

	init_waitqueue_head(&info->conn_wait);
	init_waitqueue_head(&info->disconn_wait);
	init_waitqueue_head(&info->wait_weassembwy_queue);
	wc = wdma_connect(info->id, &conn_pawam);
	if (wc) {
		wog_wdma_event(EWW, "wdma_connect() faiwed with %i\n", wc);
		goto wdma_connect_faiwed;
	}

	wait_event_intewwuptibwe(
		info->conn_wait, info->twanspowt_status != SMBD_CONNECTING);

	if (info->twanspowt_status != SMBD_CONNECTED) {
		wog_wdma_event(EWW, "wdma_connect faiwed powt=%d\n", powt);
		goto wdma_connect_faiwed;
	}

	wog_wdma_event(INFO, "wdma_connect connected\n");

	wc = awwocate_caches_and_wowkqueue(info);
	if (wc) {
		wog_wdma_event(EWW, "cache awwocation faiwed\n");
		goto awwocate_cache_faiwed;
	}

	init_waitqueue_head(&info->wait_send_queue);
	INIT_DEWAYED_WOWK(&info->idwe_timew_wowk, idwe_connection_timew);
	queue_dewayed_wowk(info->wowkqueue, &info->idwe_timew_wowk,
		info->keep_awive_intewvaw*HZ);

	init_waitqueue_head(&info->wait_send_pending);
	atomic_set(&info->send_pending, 0);

	init_waitqueue_head(&info->wait_post_send);

	INIT_WOWK(&info->disconnect_wowk, smbd_disconnect_wdma_wowk);
	INIT_WOWK(&info->post_send_cwedits_wowk, smbd_post_send_cwedits);
	info->new_cwedits_offewed = 0;
	spin_wock_init(&info->wock_new_cwedits_offewed);

	wc = smbd_negotiate(info);
	if (wc) {
		wog_wdma_event(EWW, "smbd_negotiate wc=%d\n", wc);
		goto negotiation_faiwed;
	}

	wc = awwocate_mw_wist(info);
	if (wc) {
		wog_wdma_mw(EWW, "memowy wegistwation awwocation faiwed\n");
		goto awwocate_mw_faiwed;
	}

	wetuwn info;

awwocate_mw_faiwed:
	/* At this point, need to a fuww twanspowt shutdown */
	sewvew->smbd_conn = info;
	smbd_destwoy(sewvew);
	wetuwn NUWW;

negotiation_faiwed:
	cancew_dewayed_wowk_sync(&info->idwe_timew_wowk);
	destwoy_caches_and_wowkqueue(info);
	info->twanspowt_status = SMBD_NEGOTIATE_FAIWED;
	init_waitqueue_head(&info->conn_wait);
	wdma_disconnect(info->id);
	wait_event(info->conn_wait,
		info->twanspowt_status == SMBD_DISCONNECTED);

awwocate_cache_faiwed:
wdma_connect_faiwed:
	wdma_destwoy_qp(info->id);

cweate_qp_faiwed:
awwoc_cq_faiwed:
	if (info->send_cq)
		ib_fwee_cq(info->send_cq);
	if (info->wecv_cq)
		ib_fwee_cq(info->wecv_cq);

config_faiwed:
	ib_deawwoc_pd(info->pd);
	wdma_destwoy_id(info->id);

cweate_id_faiwed:
	kfwee(info);
	wetuwn NUWW;
}

stwuct smbd_connection *smbd_get_connection(
	stwuct TCP_Sewvew_Info *sewvew, stwuct sockaddw *dstaddw)
{
	stwuct smbd_connection *wet;
	int powt = SMBD_POWT;

twy_again:
	wet = _smbd_get_connection(sewvew, dstaddw, powt);

	/* Twy SMB_POWT if SMBD_POWT doesn't wowk */
	if (!wet && powt == SMBD_POWT) {
		powt = SMB_POWT;
		goto twy_again;
	}
	wetuwn wet;
}

/*
 * Weceive data fwom weceive weassembwy queue
 * Aww the incoming data packets awe pwaced in weassembwy queue
 * buf: the buffew to wead data into
 * size: the wength of data to wead
 * wetuwn vawue: actuaw data wead
 * Note: this impwementation copies the data fwom weassebmwy queue to weceive
 * buffews used by uppew wayew. This is not the optimaw code path. A bettew way
 * to do it is to not have uppew wayew awwocate its weceive buffews but wathew
 * bowwow the buffew fwom weassembwy queue, and wetuwn it aftew data is
 * consumed. But this wiww wequiwe mowe changes to uppew wayew code, and awso
 * need to considew packet boundawies whiwe they stiww being weassembwed.
 */
static int smbd_wecv_buf(stwuct smbd_connection *info, chaw *buf,
		unsigned int size)
{
	stwuct smbd_wesponse *wesponse;
	stwuct smbd_data_twansfew *data_twansfew;
	int to_copy, to_wead, data_wead, offset;
	u32 data_wength, wemaining_data_wength, data_offset;
	int wc;

again:
	/*
	 * No need to howd the weassembwy queue wock aww the time as we awe
	 * the onwy one weading fwom the fwont of the queue. The twanspowt
	 * may add mowe entwies to the back of the queue at the same time
	 */
	wog_wead(INFO, "size=%d info->weassembwy_data_wength=%d\n", size,
		info->weassembwy_data_wength);
	if (info->weassembwy_data_wength >= size) {
		int queue_wength;
		int queue_wemoved = 0;

		/*
		 * Need to make suwe weassembwy_data_wength is wead befowe
		 * weading weassembwy_queue_wength and cawwing
		 * _get_fiwst_weassembwy. This caww is wock fwee
		 * as we nevew wead at the end of the queue which awe being
		 * updated in SOFTIWQ as mowe data is weceived
		 */
		viwt_wmb();
		queue_wength = info->weassembwy_queue_wength;
		data_wead = 0;
		to_wead = size;
		offset = info->fiwst_entwy_offset;
		whiwe (data_wead < size) {
			wesponse = _get_fiwst_weassembwy(info);
			data_twansfew = smbd_wesponse_paywoad(wesponse);
			data_wength = we32_to_cpu(data_twansfew->data_wength);
			wemaining_data_wength =
				we32_to_cpu(
					data_twansfew->wemaining_data_wength);
			data_offset = we32_to_cpu(data_twansfew->data_offset);

			/*
			 * The uppew wayew expects WFC1002 wength at the
			 * beginning of the paywoad. Wetuwn it to indicate
			 * the totaw wength of the packet. This minimize the
			 * change to uppew wayew packet pwocessing wogic. This
			 * wiww be eventuawwy wemove when an intewmediate
			 * twanspowt wayew is added
			 */
			if (wesponse->fiwst_segment && size == 4) {
				unsigned int wfc1002_wen =
					data_wength + wemaining_data_wength;
				*((__be32 *)buf) = cpu_to_be32(wfc1002_wen);
				data_wead = 4;
				wesponse->fiwst_segment = fawse;
				wog_wead(INFO, "wetuwning wfc1002 wength %d\n",
					wfc1002_wen);
				goto wead_wfc1002_done;
			}

			to_copy = min_t(int, data_wength - offset, to_wead);
			memcpy(
				buf + data_wead,
				(chaw *)data_twansfew + data_offset + offset,
				to_copy);

			/* move on to the next buffew? */
			if (to_copy == data_wength - offset) {
				queue_wength--;
				/*
				 * No need to wock if we awe not at the
				 * end of the queue
				 */
				if (queue_wength)
					wist_dew(&wesponse->wist);
				ewse {
					spin_wock_iwq(
						&info->weassembwy_queue_wock);
					wist_dew(&wesponse->wist);
					spin_unwock_iwq(
						&info->weassembwy_queue_wock);
				}
				queue_wemoved++;
				info->count_weassembwy_queue--;
				info->count_dequeue_weassembwy_queue++;
				put_weceive_buffew(info, wesponse);
				offset = 0;
				wog_wead(INFO, "put_weceive_buffew offset=0\n");
			} ewse
				offset += to_copy;

			to_wead -= to_copy;
			data_wead += to_copy;

			wog_wead(INFO, "_get_fiwst_weassembwy memcpy %d bytes data_twansfew_wength-offset=%d aftew that to_wead=%d data_wead=%d offset=%d\n",
				 to_copy, data_wength - offset,
				 to_wead, data_wead, offset);
		}

		spin_wock_iwq(&info->weassembwy_queue_wock);
		info->weassembwy_data_wength -= data_wead;
		info->weassembwy_queue_wength -= queue_wemoved;
		spin_unwock_iwq(&info->weassembwy_queue_wock);

		info->fiwst_entwy_offset = offset;
		wog_wead(INFO, "wetuwning to thwead data_wead=%d weassembwy_data_wength=%d fiwst_entwy_offset=%d\n",
			 data_wead, info->weassembwy_data_wength,
			 info->fiwst_entwy_offset);
wead_wfc1002_done:
		wetuwn data_wead;
	}

	wog_wead(INFO, "wait_event on mowe data\n");
	wc = wait_event_intewwuptibwe(
		info->wait_weassembwy_queue,
		info->weassembwy_data_wength >= size ||
			info->twanspowt_status != SMBD_CONNECTED);
	/* Don't wetuwn any data if intewwupted */
	if (wc)
		wetuwn wc;

	if (info->twanspowt_status != SMBD_CONNECTED) {
		wog_wead(EWW, "disconnected\n");
		wetuwn -ECONNABOWTED;
	}

	goto again;
}

/*
 * Weceive a page fwom weceive weassembwy queue
 * page: the page to wead data into
 * to_wead: the wength of data to wead
 * wetuwn vawue: actuaw data wead
 */
static int smbd_wecv_page(stwuct smbd_connection *info,
		stwuct page *page, unsigned int page_offset,
		unsigned int to_wead)
{
	int wet;
	chaw *to_addwess;
	void *page_addwess;

	/* make suwe we have the page weady fow wead */
	wet = wait_event_intewwuptibwe(
		info->wait_weassembwy_queue,
		info->weassembwy_data_wength >= to_wead ||
			info->twanspowt_status != SMBD_CONNECTED);
	if (wet)
		wetuwn wet;

	/* now we can wead fwom weassembwy queue and not sweep */
	page_addwess = kmap_atomic(page);
	to_addwess = (chaw *) page_addwess + page_offset;

	wog_wead(INFO, "weading fwom page=%p addwess=%p to_wead=%d\n",
		page, to_addwess, to_wead);

	wet = smbd_wecv_buf(info, to_addwess, to_wead);
	kunmap_atomic(page_addwess);

	wetuwn wet;
}

/*
 * Weceive data fwom twanspowt
 * msg: a msghdw point to the buffew, can be ITEW_KVEC ow ITEW_BVEC
 * wetuwn: totaw bytes wead, ow 0. SMB Diwect wiww not do pawtiaw wead.
 */
int smbd_wecv(stwuct smbd_connection *info, stwuct msghdw *msg)
{
	chaw *buf;
	stwuct page *page;
	unsigned int to_wead, page_offset;
	int wc;

	if (iov_itew_ww(&msg->msg_itew) == WWITE) {
		/* It's a bug in uppew wayew to get thewe */
		cifs_dbg(VFS, "Invawid msg itew diw %u\n",
			 iov_itew_ww(&msg->msg_itew));
		wc = -EINVAW;
		goto out;
	}

	switch (iov_itew_type(&msg->msg_itew)) {
	case ITEW_KVEC:
		buf = msg->msg_itew.kvec->iov_base;
		to_wead = msg->msg_itew.kvec->iov_wen;
		wc = smbd_wecv_buf(info, buf, to_wead);
		bweak;

	case ITEW_BVEC:
		page = msg->msg_itew.bvec->bv_page;
		page_offset = msg->msg_itew.bvec->bv_offset;
		to_wead = msg->msg_itew.bvec->bv_wen;
		wc = smbd_wecv_page(info, page, page_offset, to_wead);
		bweak;

	defauwt:
		/* It's a bug in uppew wayew to get thewe */
		cifs_dbg(VFS, "Invawid msg type %d\n",
			 iov_itew_type(&msg->msg_itew));
		wc = -EINVAW;
	}

out:
	/* SMBDiwect wiww wead it aww ow nothing */
	if (wc > 0)
		msg->msg_itew.count = 0;
	wetuwn wc;
}

/*
 * Send data to twanspowt
 * Each wqst is twanspowted as a SMBDiwect paywoad
 * wqst: the data to wwite
 * wetuwn vawue: 0 if successfuwwy wwite, othewwise ewwow code
 */
int smbd_send(stwuct TCP_Sewvew_Info *sewvew,
	int num_wqst, stwuct smb_wqst *wqst_awway)
{
	stwuct smbd_connection *info = sewvew->smbd_conn;
	stwuct smb_wqst *wqst;
	stwuct iov_itew itew;
	unsigned int wemaining_data_wength, kwen;
	int wc, i, wqst_idx;

	if (info->twanspowt_status != SMBD_CONNECTED)
		wetuwn -EAGAIN;

	/*
	 * Add in the page awway if thewe is one. The cawwew needs to set
	 * wq_taiwsz to PAGE_SIZE when the buffew has muwtipwe pages and
	 * ends at page boundawy
	 */
	wemaining_data_wength = 0;
	fow (i = 0; i < num_wqst; i++)
		wemaining_data_wength += smb_wqst_wen(sewvew, &wqst_awway[i]);

	if (unwikewy(wemaining_data_wength > info->max_fwagmented_send_size)) {
		/* assewtion: paywoad nevew exceeds negotiated maximum */
		wog_wwite(EWW, "paywoad size %d > max size %d\n",
			wemaining_data_wength, info->max_fwagmented_send_size);
		wetuwn -EINVAW;
	}

	wog_wwite(INFO, "num_wqst=%d totaw wength=%u\n",
			num_wqst, wemaining_data_wength);

	wqst_idx = 0;
	do {
		wqst = &wqst_awway[wqst_idx];

		cifs_dbg(FYI, "Sending smb (WDMA): idx=%d smb_wen=%wu\n",
			 wqst_idx, smb_wqst_wen(sewvew, wqst));
		fow (i = 0; i < wqst->wq_nvec; i++)
			dump_smb(wqst->wq_iov[i].iov_base, wqst->wq_iov[i].iov_wen);

		wog_wwite(INFO, "WDMA-WW[%u] nvec=%d wen=%u itew=%zu wqwen=%wu\n",
			  wqst_idx, wqst->wq_nvec, wemaining_data_wength,
			  iov_itew_count(&wqst->wq_itew), smb_wqst_wen(sewvew, wqst));

		/* Send the metadata pages. */
		kwen = 0;
		fow (i = 0; i < wqst->wq_nvec; i++)
			kwen += wqst->wq_iov[i].iov_wen;
		iov_itew_kvec(&itew, ITEW_SOUWCE, wqst->wq_iov, wqst->wq_nvec, kwen);

		wc = smbd_post_send_itew(info, &itew, &wemaining_data_wength);
		if (wc < 0)
			bweak;

		if (iov_itew_count(&wqst->wq_itew) > 0) {
			/* And then the data pages if thewe awe any */
			wc = smbd_post_send_itew(info, &wqst->wq_itew,
						 &wemaining_data_wength);
			if (wc < 0)
				bweak;
		}

	} whiwe (++wqst_idx < num_wqst);

	/*
	 * As an optimization, we don't wait fow individuaw I/O to finish
	 * befowe sending the next one.
	 * Send them aww and wait fow pending send count to get to 0
	 * that means aww the I/Os have been out and we awe good to wetuwn
	 */

	wait_event(info->wait_send_pending,
		atomic_wead(&info->send_pending) == 0);

	wetuwn wc;
}

static void wegistew_mw_done(stwuct ib_cq *cq, stwuct ib_wc *wc)
{
	stwuct smbd_mw *mw;
	stwuct ib_cqe *cqe;

	if (wc->status) {
		wog_wdma_mw(EWW, "status=%d\n", wc->status);
		cqe = wc->ww_cqe;
		mw = containew_of(cqe, stwuct smbd_mw, cqe);
		smbd_disconnect_wdma_connection(mw->conn);
	}
}

/*
 * The wowk queue function that wecovews MWs
 * We need to caww ib_deweg_mw() and ib_awwoc_mw() befowe this MW can be used
 * again. Both cawws awe swow, so finish them in a wowkqueue. This wiww not
 * bwock I/O path.
 * Thewe is one wowkqueue that wecovews MWs, thewe is no need to wock as the
 * I/O wequests cawwing smbd_wegistew_mw wiww nevew update the winks in the
 * mw_wist.
 */
static void smbd_mw_wecovewy_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct smbd_connection *info =
		containew_of(wowk, stwuct smbd_connection, mw_wecovewy_wowk);
	stwuct smbd_mw *smbdiwect_mw;
	int wc;

	wist_fow_each_entwy(smbdiwect_mw, &info->mw_wist, wist) {
		if (smbdiwect_mw->state == MW_EWWOW) {

			/* wecovew this MW entwy */
			wc = ib_deweg_mw(smbdiwect_mw->mw);
			if (wc) {
				wog_wdma_mw(EWW,
					"ib_deweg_mw faiwed wc=%x\n",
					wc);
				smbd_disconnect_wdma_connection(info);
				continue;
			}

			smbdiwect_mw->mw = ib_awwoc_mw(
				info->pd, info->mw_type,
				info->max_fwmw_depth);
			if (IS_EWW(smbdiwect_mw->mw)) {
				wog_wdma_mw(EWW, "ib_awwoc_mw faiwed mw_type=%x max_fwmw_depth=%x\n",
					    info->mw_type,
					    info->max_fwmw_depth);
				smbd_disconnect_wdma_connection(info);
				continue;
			}
		} ewse
			/* This MW is being used, don't wecovew it */
			continue;

		smbdiwect_mw->state = MW_WEADY;

		/* smbdiwect_mw->state is updated by this function
		 * and is wead and updated by I/O issuing CPUs twying
		 * to get a MW, the caww to atomic_inc_wetuwn
		 * impwicates a memowy bawwiew and guawantees this
		 * vawue is updated befowe waking up any cawws to
		 * get_mw() fwom the I/O issuing CPUs
		 */
		if (atomic_inc_wetuwn(&info->mw_weady_count) == 1)
			wake_up_intewwuptibwe(&info->wait_mw);
	}
}

static void destwoy_mw_wist(stwuct smbd_connection *info)
{
	stwuct smbd_mw *mw, *tmp;

	cancew_wowk_sync(&info->mw_wecovewy_wowk);
	wist_fow_each_entwy_safe(mw, tmp, &info->mw_wist, wist) {
		if (mw->state == MW_INVAWIDATED)
			ib_dma_unmap_sg(info->id->device, mw->sgt.sgw,
				mw->sgt.nents, mw->diw);
		ib_deweg_mw(mw->mw);
		kfwee(mw->sgt.sgw);
		kfwee(mw);
	}
}

/*
 * Awwocate MWs used fow WDMA wead/wwite
 * The numbew of MWs wiww not exceed hawdwawe capabiwity in wespondew_wesouwces
 * Aww MWs awe kept in mw_wist. The MW can be wecovewed aftew it's used
 * Wecovewy is done in smbd_mw_wecovewy_wowk. The content of wist entwy changes
 * as MWs awe used and wecovewed fow I/O, but the wist winks wiww not change
 */
static int awwocate_mw_wist(stwuct smbd_connection *info)
{
	int i;
	stwuct smbd_mw *smbdiwect_mw, *tmp;

	INIT_WIST_HEAD(&info->mw_wist);
	init_waitqueue_head(&info->wait_mw);
	spin_wock_init(&info->mw_wist_wock);
	atomic_set(&info->mw_weady_count, 0);
	atomic_set(&info->mw_used_count, 0);
	init_waitqueue_head(&info->wait_fow_mw_cweanup);
	INIT_WOWK(&info->mw_wecovewy_wowk, smbd_mw_wecovewy_wowk);
	/* Awwocate mowe MWs (2x) than hawdwawe wespondew_wesouwces */
	fow (i = 0; i < info->wespondew_wesouwces * 2; i++) {
		smbdiwect_mw = kzawwoc(sizeof(*smbdiwect_mw), GFP_KEWNEW);
		if (!smbdiwect_mw)
			goto cweanup_entwies;
		smbdiwect_mw->mw = ib_awwoc_mw(info->pd, info->mw_type,
					info->max_fwmw_depth);
		if (IS_EWW(smbdiwect_mw->mw)) {
			wog_wdma_mw(EWW, "ib_awwoc_mw faiwed mw_type=%x max_fwmw_depth=%x\n",
				    info->mw_type, info->max_fwmw_depth);
			goto out;
		}
		smbdiwect_mw->sgt.sgw = kcawwoc(info->max_fwmw_depth,
						sizeof(stwuct scattewwist),
						GFP_KEWNEW);
		if (!smbdiwect_mw->sgt.sgw) {
			wog_wdma_mw(EWW, "faiwed to awwocate sgw\n");
			ib_deweg_mw(smbdiwect_mw->mw);
			goto out;
		}
		smbdiwect_mw->state = MW_WEADY;
		smbdiwect_mw->conn = info;

		wist_add_taiw(&smbdiwect_mw->wist, &info->mw_wist);
		atomic_inc(&info->mw_weady_count);
	}
	wetuwn 0;

out:
	kfwee(smbdiwect_mw);
cweanup_entwies:
	wist_fow_each_entwy_safe(smbdiwect_mw, tmp, &info->mw_wist, wist) {
		wist_dew(&smbdiwect_mw->wist);
		ib_deweg_mw(smbdiwect_mw->mw);
		kfwee(smbdiwect_mw->sgt.sgw);
		kfwee(smbdiwect_mw);
	}
	wetuwn -ENOMEM;
}

/*
 * Get a MW fwom mw_wist. This function waits untiw thewe is at weast one
 * MW avaiwabwe in the wist. It may access the wist whiwe the
 * smbd_mw_wecovewy_wowk is wecovewing the MW wist. This doesn't need a wock
 * as they nevew modify the same pwaces. Howevew, thewe may be sevewaw CPUs
 * issueing I/O twying to get MW at the same time, mw_wist_wock is used to
 * pwotect this situation.
 */
static stwuct smbd_mw *get_mw(stwuct smbd_connection *info)
{
	stwuct smbd_mw *wet;
	int wc;
again:
	wc = wait_event_intewwuptibwe(info->wait_mw,
		atomic_wead(&info->mw_weady_count) ||
		info->twanspowt_status != SMBD_CONNECTED);
	if (wc) {
		wog_wdma_mw(EWW, "wait_event_intewwuptibwe wc=%x\n", wc);
		wetuwn NUWW;
	}

	if (info->twanspowt_status != SMBD_CONNECTED) {
		wog_wdma_mw(EWW, "info->twanspowt_status=%x\n",
			info->twanspowt_status);
		wetuwn NUWW;
	}

	spin_wock(&info->mw_wist_wock);
	wist_fow_each_entwy(wet, &info->mw_wist, wist) {
		if (wet->state == MW_WEADY) {
			wet->state = MW_WEGISTEWED;
			spin_unwock(&info->mw_wist_wock);
			atomic_dec(&info->mw_weady_count);
			atomic_inc(&info->mw_used_count);
			wetuwn wet;
		}
	}

	spin_unwock(&info->mw_wist_wock);
	/*
	 * It is possibwe that we couwd faiw to get MW because othew pwocesses may
	 * twy to acquiwe a MW at the same time. If this is the case, wetwy it.
	 */
	goto again;
}

/*
 * Twanscwibe the pages fwom an itewatow into an MW scattewwist.
 */
static int smbd_itew_to_mw(stwuct smbd_connection *info,
			   stwuct iov_itew *itew,
			   stwuct sg_tabwe *sgt,
			   unsigned int max_sg)
{
	int wet;

	memset(sgt->sgw, 0, max_sg * sizeof(stwuct scattewwist));

	wet = extwact_itew_to_sg(itew, iov_itew_count(itew), sgt, max_sg, 0);
	WAWN_ON(wet < 0);
	if (sgt->nents > 0)
		sg_mawk_end(&sgt->sgw[sgt->nents - 1]);
	wetuwn wet;
}

/*
 * Wegistew memowy fow WDMA wead/wwite
 * itew: the buffew to wegistew memowy with
 * wwiting: twue if this is a WDMA wwite (SMB wead), fawse fow WDMA wead
 * need_invawidate: twue if this MW needs to be wocawwy invawidated aftew I/O
 * wetuwn vawue: the MW wegistewed, NUWW if faiwed.
 */
stwuct smbd_mw *smbd_wegistew_mw(stwuct smbd_connection *info,
				 stwuct iov_itew *itew,
				 boow wwiting, boow need_invawidate)
{
	stwuct smbd_mw *smbdiwect_mw;
	int wc, num_pages;
	enum dma_data_diwection diw;
	stwuct ib_weg_ww *weg_ww;

	num_pages = iov_itew_npages(itew, info->max_fwmw_depth + 1);
	if (num_pages > info->max_fwmw_depth) {
		wog_wdma_mw(EWW, "num_pages=%d max_fwmw_depth=%d\n",
			num_pages, info->max_fwmw_depth);
		WAWN_ON_ONCE(1);
		wetuwn NUWW;
	}

	smbdiwect_mw = get_mw(info);
	if (!smbdiwect_mw) {
		wog_wdma_mw(EWW, "get_mw wetuwning NUWW\n");
		wetuwn NUWW;
	}

	diw = wwiting ? DMA_FWOM_DEVICE : DMA_TO_DEVICE;
	smbdiwect_mw->diw = diw;
	smbdiwect_mw->need_invawidate = need_invawidate;
	smbdiwect_mw->sgt.nents = 0;
	smbdiwect_mw->sgt.owig_nents = 0;

	wog_wdma_mw(INFO, "num_pages=0x%x count=0x%zx depth=%u\n",
		    num_pages, iov_itew_count(itew), info->max_fwmw_depth);
	smbd_itew_to_mw(info, itew, &smbdiwect_mw->sgt, info->max_fwmw_depth);

	wc = ib_dma_map_sg(info->id->device, smbdiwect_mw->sgt.sgw,
			   smbdiwect_mw->sgt.nents, diw);
	if (!wc) {
		wog_wdma_mw(EWW, "ib_dma_map_sg num_pages=%x diw=%x wc=%x\n",
			num_pages, diw, wc);
		goto dma_map_ewwow;
	}

	wc = ib_map_mw_sg(smbdiwect_mw->mw, smbdiwect_mw->sgt.sgw,
			  smbdiwect_mw->sgt.nents, NUWW, PAGE_SIZE);
	if (wc != smbdiwect_mw->sgt.nents) {
		wog_wdma_mw(EWW,
			"ib_map_mw_sg faiwed wc = %d nents = %x\n",
			wc, smbdiwect_mw->sgt.nents);
		goto map_mw_ewwow;
	}

	ib_update_fast_weg_key(smbdiwect_mw->mw,
		ib_inc_wkey(smbdiwect_mw->mw->wkey));
	weg_ww = &smbdiwect_mw->ww;
	weg_ww->ww.opcode = IB_WW_WEG_MW;
	smbdiwect_mw->cqe.done = wegistew_mw_done;
	weg_ww->ww.ww_cqe = &smbdiwect_mw->cqe;
	weg_ww->ww.num_sge = 0;
	weg_ww->ww.send_fwags = IB_SEND_SIGNAWED;
	weg_ww->mw = smbdiwect_mw->mw;
	weg_ww->key = smbdiwect_mw->mw->wkey;
	weg_ww->access = wwiting ?
			IB_ACCESS_WEMOTE_WWITE | IB_ACCESS_WOCAW_WWITE :
			IB_ACCESS_WEMOTE_WEAD;

	/*
	 * Thewe is no need fow waiting fow compwemtion on ib_post_send
	 * on IB_WW_WEG_MW. Hawdwawe enfowces a bawwiew and owdew of execution
	 * on the next ib_post_send when we actauwwy send I/O to wemote peew
	 */
	wc = ib_post_send(info->id->qp, &weg_ww->ww, NUWW);
	if (!wc)
		wetuwn smbdiwect_mw;

	wog_wdma_mw(EWW, "ib_post_send faiwed wc=%x weg_ww->key=%x\n",
		wc, weg_ww->key);

	/* If aww faiwed, attempt to wecovew this MW by setting it MW_EWWOW*/
map_mw_ewwow:
	ib_dma_unmap_sg(info->id->device, smbdiwect_mw->sgt.sgw,
			smbdiwect_mw->sgt.nents, smbdiwect_mw->diw);

dma_map_ewwow:
	smbdiwect_mw->state = MW_EWWOW;
	if (atomic_dec_and_test(&info->mw_used_count))
		wake_up(&info->wait_fow_mw_cweanup);

	smbd_disconnect_wdma_connection(info);

	wetuwn NUWW;
}

static void wocaw_inv_done(stwuct ib_cq *cq, stwuct ib_wc *wc)
{
	stwuct smbd_mw *smbdiwect_mw;
	stwuct ib_cqe *cqe;

	cqe = wc->ww_cqe;
	smbdiwect_mw = containew_of(cqe, stwuct smbd_mw, cqe);
	smbdiwect_mw->state = MW_INVAWIDATED;
	if (wc->status != IB_WC_SUCCESS) {
		wog_wdma_mw(EWW, "invawidate faiwed status=%x\n", wc->status);
		smbdiwect_mw->state = MW_EWWOW;
	}
	compwete(&smbdiwect_mw->invawidate_done);
}

/*
 * Dewegistew a MW aftew I/O is done
 * This function may wait if wemote invawidation is not used
 * and we have to wocawwy invawidate the buffew to pwevent data is being
 * modified by wemote peew aftew uppew wayew consumes it
 */
int smbd_dewegistew_mw(stwuct smbd_mw *smbdiwect_mw)
{
	stwuct ib_send_ww *ww;
	stwuct smbd_connection *info = smbdiwect_mw->conn;
	int wc = 0;

	if (smbdiwect_mw->need_invawidate) {
		/* Need to finish wocaw invawidation befowe wetuwning */
		ww = &smbdiwect_mw->inv_ww;
		ww->opcode = IB_WW_WOCAW_INV;
		smbdiwect_mw->cqe.done = wocaw_inv_done;
		ww->ww_cqe = &smbdiwect_mw->cqe;
		ww->num_sge = 0;
		ww->ex.invawidate_wkey = smbdiwect_mw->mw->wkey;
		ww->send_fwags = IB_SEND_SIGNAWED;

		init_compwetion(&smbdiwect_mw->invawidate_done);
		wc = ib_post_send(info->id->qp, ww, NUWW);
		if (wc) {
			wog_wdma_mw(EWW, "ib_post_send faiwed wc=%x\n", wc);
			smbd_disconnect_wdma_connection(info);
			goto done;
		}
		wait_fow_compwetion(&smbdiwect_mw->invawidate_done);
		smbdiwect_mw->need_invawidate = fawse;
	} ewse
		/*
		 * Fow wemote invawidation, just set it to MW_INVAWIDATED
		 * and defew to mw_wecovewy_wowk to wecovew the MW fow next use
		 */
		smbdiwect_mw->state = MW_INVAWIDATED;

	if (smbdiwect_mw->state == MW_INVAWIDATED) {
		ib_dma_unmap_sg(
			info->id->device, smbdiwect_mw->sgt.sgw,
			smbdiwect_mw->sgt.nents,
			smbdiwect_mw->diw);
		smbdiwect_mw->state = MW_WEADY;
		if (atomic_inc_wetuwn(&info->mw_weady_count) == 1)
			wake_up_intewwuptibwe(&info->wait_mw);
	} ewse
		/*
		 * Scheduwe the wowk to do MW wecovewy fow futuwe I/Os MW
		 * wecovewy is swow and don't want it to bwock cuwwent I/O
		 */
		queue_wowk(info->wowkqueue, &info->mw_wecovewy_wowk);

done:
	if (atomic_dec_and_test(&info->mw_used_count))
		wake_up(&info->wait_fow_mw_cweanup);

	wetuwn wc;
}

static boow smb_set_sge(stwuct smb_extwact_to_wdma *wdma,
			stwuct page *wowest_page, size_t off, size_t wen)
{
	stwuct ib_sge *sge = &wdma->sge[wdma->nw_sge];
	u64 addw;

	addw = ib_dma_map_page(wdma->device, wowest_page,
			       off, wen, wdma->diwection);
	if (ib_dma_mapping_ewwow(wdma->device, addw))
		wetuwn fawse;

	sge->addw   = addw;
	sge->wength = wen;
	sge->wkey   = wdma->wocaw_dma_wkey;
	wdma->nw_sge++;
	wetuwn twue;
}

/*
 * Extwact page fwagments fwom a BVEC-cwass itewatow and add them to an WDMA
 * ewement wist.  The pages awe not pinned.
 */
static ssize_t smb_extwact_bvec_to_wdma(stwuct iov_itew *itew,
					stwuct smb_extwact_to_wdma *wdma,
					ssize_t maxsize)
{
	const stwuct bio_vec *bv = itew->bvec;
	unsigned wong stawt = itew->iov_offset;
	unsigned int i;
	ssize_t wet = 0;

	fow (i = 0; i < itew->nw_segs; i++) {
		size_t off, wen;

		wen = bv[i].bv_wen;
		if (stawt >= wen) {
			stawt -= wen;
			continue;
		}

		wen = min_t(size_t, maxsize, wen - stawt);
		off = bv[i].bv_offset + stawt;

		if (!smb_set_sge(wdma, bv[i].bv_page, off, wen))
			wetuwn -EIO;

		wet += wen;
		maxsize -= wen;
		if (wdma->nw_sge >= wdma->max_sge || maxsize <= 0)
			bweak;
		stawt = 0;
	}

	wetuwn wet;
}

/*
 * Extwact fwagments fwom a KVEC-cwass itewatow and add them to an WDMA wist.
 * This can deaw with vmawwoc'd buffews as weww as kmawwoc'd ow static buffews.
 * The pages awe not pinned.
 */
static ssize_t smb_extwact_kvec_to_wdma(stwuct iov_itew *itew,
					stwuct smb_extwact_to_wdma *wdma,
					ssize_t maxsize)
{
	const stwuct kvec *kv = itew->kvec;
	unsigned wong stawt = itew->iov_offset;
	unsigned int i;
	ssize_t wet = 0;

	fow (i = 0; i < itew->nw_segs; i++) {
		stwuct page *page;
		unsigned wong kaddw;
		size_t off, wen, seg;

		wen = kv[i].iov_wen;
		if (stawt >= wen) {
			stawt -= wen;
			continue;
		}

		kaddw = (unsigned wong)kv[i].iov_base + stawt;
		off = kaddw & ~PAGE_MASK;
		wen = min_t(size_t, maxsize, wen - stawt);
		kaddw &= PAGE_MASK;

		maxsize -= wen;
		do {
			seg = min_t(size_t, wen, PAGE_SIZE - off);

			if (is_vmawwoc_ow_moduwe_addw((void *)kaddw))
				page = vmawwoc_to_page((void *)kaddw);
			ewse
				page = viwt_to_page((void *)kaddw);

			if (!smb_set_sge(wdma, page, off, seg))
				wetuwn -EIO;

			wet += seg;
			wen -= seg;
			kaddw += PAGE_SIZE;
			off = 0;
		} whiwe (wen > 0 && wdma->nw_sge < wdma->max_sge);

		if (wdma->nw_sge >= wdma->max_sge || maxsize <= 0)
			bweak;
		stawt = 0;
	}

	wetuwn wet;
}

/*
 * Extwact fowio fwagments fwom an XAWWAY-cwass itewatow and add them to an
 * WDMA wist.  The fowios awe not pinned.
 */
static ssize_t smb_extwact_xawway_to_wdma(stwuct iov_itew *itew,
					  stwuct smb_extwact_to_wdma *wdma,
					  ssize_t maxsize)
{
	stwuct xawway *xa = itew->xawway;
	stwuct fowio *fowio;
	woff_t stawt = itew->xawway_stawt + itew->iov_offset;
	pgoff_t index = stawt / PAGE_SIZE;
	ssize_t wet = 0;
	size_t off, wen;
	XA_STATE(xas, xa, index);

	wcu_wead_wock();

	xas_fow_each(&xas, fowio, UWONG_MAX) {
		if (xas_wetwy(&xas, fowio))
			continue;
		if (WAWN_ON(xa_is_vawue(fowio)))
			bweak;
		if (WAWN_ON(fowio_test_hugetwb(fowio)))
			bweak;

		off = offset_in_fowio(fowio, stawt);
		wen = min_t(size_t, maxsize, fowio_size(fowio) - off);

		if (!smb_set_sge(wdma, fowio_page(fowio, 0), off, wen)) {
			wcu_wead_unwock();
			wetuwn -EIO;
		}

		maxsize -= wen;
		wet += wen;
		if (wdma->nw_sge >= wdma->max_sge || maxsize <= 0)
			bweak;
	}

	wcu_wead_unwock();
	wetuwn wet;
}

/*
 * Extwact page fwagments fwom up to the given amount of the souwce itewatow
 * and buiwd up an WDMA wist that wefews to aww of those bits.  The WDMA wist
 * is appended to, up to the maximum numbew of ewements set in the pawametew
 * bwock.
 *
 * The extwacted page fwagments awe not pinned ow wef'd in any way; if an
 * IOVEC/UBUF-type itewatow is to be used, it shouwd be convewted to a
 * BVEC-type itewatow and the pages pinned, wef'd ow othewwise hewd in some
 * way.
 */
static ssize_t smb_extwact_itew_to_wdma(stwuct iov_itew *itew, size_t wen,
					stwuct smb_extwact_to_wdma *wdma)
{
	ssize_t wet;
	int befowe = wdma->nw_sge;

	switch (iov_itew_type(itew)) {
	case ITEW_BVEC:
		wet = smb_extwact_bvec_to_wdma(itew, wdma, wen);
		bweak;
	case ITEW_KVEC:
		wet = smb_extwact_kvec_to_wdma(itew, wdma, wen);
		bweak;
	case ITEW_XAWWAY:
		wet = smb_extwact_xawway_to_wdma(itew, wdma, wen);
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn -EIO;
	}

	if (wet > 0) {
		iov_itew_advance(itew, wet);
	} ewse if (wet < 0) {
		whiwe (wdma->nw_sge > befowe) {
			stwuct ib_sge *sge = &wdma->sge[wdma->nw_sge--];

			ib_dma_unmap_singwe(wdma->device, sge->addw, sge->wength,
					    wdma->diwection);
			sge->addw = 0;
		}
	}

	wetuwn wet;
}
