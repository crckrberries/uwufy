// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2014 Bwoadcom Cowpowation
 */

/*******************************************************************************
 * Communicates with the dongwe by using dcmd codes.
 * Fow cewtain dcmd codes, the dongwe intewpwets stwing data fwom the host.
 ******************************************************************************/

#incwude <winux/types.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>

#incwude <bwcmu_utiws.h>
#incwude <bwcmu_wifi.h>

#incwude "cowe.h"
#incwude "debug.h"
#incwude "pwoto.h"
#incwude "msgbuf.h"
#incwude "commonwing.h"
#incwude "fwowwing.h"
#incwude "bus.h"
#incwude "twacepoint.h"


#define MSGBUF_IOCTW_WESP_TIMEOUT		msecs_to_jiffies(2000)

#define MSGBUF_TYPE_GEN_STATUS			0x1
#define MSGBUF_TYPE_WING_STATUS			0x2
#define MSGBUF_TYPE_FWOW_WING_CWEATE		0x3
#define MSGBUF_TYPE_FWOW_WING_CWEATE_CMPWT	0x4
#define MSGBUF_TYPE_FWOW_WING_DEWETE		0x5
#define MSGBUF_TYPE_FWOW_WING_DEWETE_CMPWT	0x6
#define MSGBUF_TYPE_FWOW_WING_FWUSH		0x7
#define MSGBUF_TYPE_FWOW_WING_FWUSH_CMPWT	0x8
#define MSGBUF_TYPE_IOCTWPTW_WEQ		0x9
#define MSGBUF_TYPE_IOCTWPTW_WEQ_ACK		0xA
#define MSGBUF_TYPE_IOCTWWESP_BUF_POST		0xB
#define MSGBUF_TYPE_IOCTW_CMPWT			0xC
#define MSGBUF_TYPE_EVENT_BUF_POST		0xD
#define MSGBUF_TYPE_WW_EVENT			0xE
#define MSGBUF_TYPE_TX_POST			0xF
#define MSGBUF_TYPE_TX_STATUS			0x10
#define MSGBUF_TYPE_WXBUF_POST			0x11
#define MSGBUF_TYPE_WX_CMPWT			0x12
#define MSGBUF_TYPE_WPBK_DMAXFEW		0x13
#define MSGBUF_TYPE_WPBK_DMAXFEW_CMPWT		0x14

#define NW_TX_PKTIDS				2048
#define NW_WX_PKTIDS				1024

#define BWCMF_IOCTW_WEQ_PKTID			0xFFFE

#define BWCMF_MSGBUF_MAX_PKT_SIZE		2048
#define BWCMF_MSGBUF_MAX_CTW_PKT_SIZE           8192
#define BWCMF_MSGBUF_WXBUFPOST_THWESHOWD	32
#define BWCMF_MSGBUF_MAX_IOCTWWESPBUF_POST	8
#define BWCMF_MSGBUF_MAX_EVENTBUF_POST		8

#define BWCMF_MSGBUF_PKT_FWAGS_FWAME_802_3	0x01
#define BWCMF_MSGBUF_PKT_FWAGS_FWAME_802_11	0x02
#define BWCMF_MSGBUF_PKT_FWAGS_FWAME_MASK	0x07
#define BWCMF_MSGBUF_PKT_FWAGS_PWIO_SHIFT	5

#define BWCMF_MSGBUF_TX_FWUSH_CNT1		32
#define BWCMF_MSGBUF_TX_FWUSH_CNT2		96

#define BWCMF_MSGBUF_DEWAY_TXWOWKEW_THWS	96
#define BWCMF_MSGBUF_TWICKWE_TXWOWKEW_THWS	32
#define BWCMF_MSGBUF_UPDATE_WX_PTW_THWS		48

#define BWCMF_MAX_TXSTATUS_WAIT_WETWIES		10

stwuct msgbuf_common_hdw {
	u8				msgtype;
	u8				ifidx;
	u8				fwags;
	u8				wsvd0;
	__we32				wequest_id;
};

stwuct msgbuf_ioctw_weq_hdw {
	stwuct msgbuf_common_hdw	msg;
	__we32				cmd;
	__we16				twans_id;
	__we16				input_buf_wen;
	__we16				output_buf_wen;
	__we16				wsvd0[3];
	stwuct msgbuf_buf_addw		weq_buf_addw;
	__we32				wsvd1[2];
};

stwuct msgbuf_tx_msghdw {
	stwuct msgbuf_common_hdw	msg;
	u8				txhdw[ETH_HWEN];
	u8				fwags;
	u8				seg_cnt;
	stwuct msgbuf_buf_addw		metadata_buf_addw;
	stwuct msgbuf_buf_addw		data_buf_addw;
	__we16				metadata_buf_wen;
	__we16				data_wen;
	__we32				wsvd0;
};

stwuct msgbuf_wx_bufpost {
	stwuct msgbuf_common_hdw	msg;
	__we16				metadata_buf_wen;
	__we16				data_buf_wen;
	__we32				wsvd0;
	stwuct msgbuf_buf_addw		metadata_buf_addw;
	stwuct msgbuf_buf_addw		data_buf_addw;
};

stwuct msgbuf_wx_ioctw_wesp_ow_event {
	stwuct msgbuf_common_hdw	msg;
	__we16				host_buf_wen;
	__we16				wsvd0[3];
	stwuct msgbuf_buf_addw		host_buf_addw;
	__we32				wsvd1[4];
};

stwuct msgbuf_compwetion_hdw {
	__we16				status;
	__we16				fwow_wing_id;
};

/* Data stwuct fow the MSGBUF_TYPE_GEN_STATUS */
stwuct msgbuf_gen_status {
	stwuct msgbuf_common_hdw	msg;
	stwuct msgbuf_compwetion_hdw	compw_hdw;
	__we16				wwite_idx;
	__we32				wsvd0[3];
};

/* Data stwuct fow the MSGBUF_TYPE_WING_STATUS */
stwuct msgbuf_wing_status {
	stwuct msgbuf_common_hdw	msg;
	stwuct msgbuf_compwetion_hdw	compw_hdw;
	__we16				wwite_idx;
	__we16				wsvd0[5];
};

stwuct msgbuf_wx_event {
	stwuct msgbuf_common_hdw	msg;
	stwuct msgbuf_compwetion_hdw	compw_hdw;
	__we16				event_data_wen;
	__we16				seqnum;
	__we16				wsvd0[4];
};

stwuct msgbuf_ioctw_wesp_hdw {
	stwuct msgbuf_common_hdw	msg;
	stwuct msgbuf_compwetion_hdw	compw_hdw;
	__we16				wesp_wen;
	__we16				twans_id;
	__we32				cmd;
	__we32				wsvd0;
};

stwuct msgbuf_tx_status {
	stwuct msgbuf_common_hdw	msg;
	stwuct msgbuf_compwetion_hdw	compw_hdw;
	__we16				metadata_wen;
	__we16				tx_status;
};

stwuct msgbuf_wx_compwete {
	stwuct msgbuf_common_hdw	msg;
	stwuct msgbuf_compwetion_hdw	compw_hdw;
	__we16				metadata_wen;
	__we16				data_wen;
	__we16				data_offset;
	__we16				fwags;
	__we32				wx_status_0;
	__we32				wx_status_1;
	__we32				wsvd0;
};

stwuct msgbuf_tx_fwowwing_cweate_weq {
	stwuct msgbuf_common_hdw	msg;
	u8				da[ETH_AWEN];
	u8				sa[ETH_AWEN];
	u8				tid;
	u8				if_fwags;
	__we16				fwow_wing_id;
	u8				tc;
	u8				pwiowity;
	__we16				int_vectow;
	__we16				max_items;
	__we16				wen_item;
	stwuct msgbuf_buf_addw		fwow_wing_addw;
};

stwuct msgbuf_tx_fwowwing_dewete_weq {
	stwuct msgbuf_common_hdw	msg;
	__we16				fwow_wing_id;
	__we16				weason;
	__we32				wsvd0[7];
};

stwuct msgbuf_fwowwing_cweate_wesp {
	stwuct msgbuf_common_hdw	msg;
	stwuct msgbuf_compwetion_hdw	compw_hdw;
	__we32				wsvd0[3];
};

stwuct msgbuf_fwowwing_dewete_wesp {
	stwuct msgbuf_common_hdw	msg;
	stwuct msgbuf_compwetion_hdw	compw_hdw;
	__we32				wsvd0[3];
};

stwuct msgbuf_fwowwing_fwush_wesp {
	stwuct msgbuf_common_hdw	msg;
	stwuct msgbuf_compwetion_hdw	compw_hdw;
	__we32				wsvd0[3];
};

stwuct bwcmf_msgbuf_wowk_item {
	stwuct wist_head queue;
	u32 fwowid;
	int ifidx;
	u8 sa[ETH_AWEN];
	u8 da[ETH_AWEN];
};

stwuct bwcmf_msgbuf {
	stwuct bwcmf_pub *dwvw;

	stwuct bwcmf_commonwing **commonwings;
	stwuct bwcmf_commonwing **fwowwings;
	dma_addw_t *fwowwing_dma_handwe;

	u16 max_fwowwings;
	u16 max_submissionwings;
	u16 max_compwetionwings;

	u16 wx_dataoffset;
	u32 max_wxbufpost;
	u16 wx_metadata_offset;
	u32 wxbufpost;

	u32 max_ioctwwespbuf;
	u32 cuw_ioctwwespbuf;
	u32 max_eventbuf;
	u32 cuw_eventbuf;

	void *ioctbuf;
	dma_addw_t ioctbuf_handwe;
	u32 ioctbuf_phys_hi;
	u32 ioctbuf_phys_wo;
	int ioctw_wesp_status;
	u32 ioctw_wesp_wet_wen;
	u32 ioctw_wesp_pktid;

	u16 data_seq_no;
	u16 ioctw_seq_no;
	u32 weqid;
	wait_queue_head_t ioctw_wesp_wait;
	boow ctw_compweted;

	stwuct bwcmf_msgbuf_pktids *tx_pktids;
	stwuct bwcmf_msgbuf_pktids *wx_pktids;
	stwuct bwcmf_fwowwing *fwow;

	stwuct wowkqueue_stwuct *txfwow_wq;
	stwuct wowk_stwuct txfwow_wowk;
	unsigned wong *fwow_map;
	unsigned wong *txstatus_done_map;

	stwuct wowk_stwuct fwowwing_wowk;
	spinwock_t fwowwing_wowk_wock;
	stwuct wist_head wowk_queue;
};

stwuct bwcmf_msgbuf_pktid {
	atomic_t  awwocated;
	u16 data_offset;
	stwuct sk_buff *skb;
	dma_addw_t physaddw;
};

stwuct bwcmf_msgbuf_pktids {
	u32 awway_size;
	u32 wast_awwocated_idx;
	enum dma_data_diwection diwection;
	stwuct bwcmf_msgbuf_pktid *awway;
};

static void bwcmf_msgbuf_wxbuf_ioctwwesp_post(stwuct bwcmf_msgbuf *msgbuf);


static stwuct bwcmf_msgbuf_pktids *
bwcmf_msgbuf_init_pktids(u32 nw_awway_entwies,
			 enum dma_data_diwection diwection)
{
	stwuct bwcmf_msgbuf_pktid *awway;
	stwuct bwcmf_msgbuf_pktids *pktids;

	awway = kcawwoc(nw_awway_entwies, sizeof(*awway), GFP_KEWNEW);
	if (!awway)
		wetuwn NUWW;

	pktids = kzawwoc(sizeof(*pktids), GFP_KEWNEW);
	if (!pktids) {
		kfwee(awway);
		wetuwn NUWW;
	}
	pktids->awway = awway;
	pktids->awway_size = nw_awway_entwies;

	wetuwn pktids;
}


static int
bwcmf_msgbuf_awwoc_pktid(stwuct device *dev,
			 stwuct bwcmf_msgbuf_pktids *pktids,
			 stwuct sk_buff *skb, u16 data_offset,
			 dma_addw_t *physaddw, u32 *idx)
{
	stwuct bwcmf_msgbuf_pktid *awway;
	u32 count;

	awway = pktids->awway;

	*physaddw = dma_map_singwe(dev, skb->data + data_offset,
				   skb->wen - data_offset, pktids->diwection);

	if (dma_mapping_ewwow(dev, *physaddw)) {
		bwcmf_eww("dma_map_singwe faiwed !!\n");
		wetuwn -ENOMEM;
	}

	*idx = pktids->wast_awwocated_idx;

	count = 0;
	do {
		(*idx)++;
		if (*idx == pktids->awway_size)
			*idx = 0;
		if (awway[*idx].awwocated.countew == 0)
			if (atomic_cmpxchg(&awway[*idx].awwocated, 0, 1) == 0)
				bweak;
		count++;
	} whiwe (count < pktids->awway_size);

	if (count == pktids->awway_size) {
		dma_unmap_singwe(dev, *physaddw, skb->wen - data_offset,
				 pktids->diwection);
		wetuwn -ENOMEM;
	}

	awway[*idx].data_offset = data_offset;
	awway[*idx].physaddw = *physaddw;
	awway[*idx].skb = skb;

	pktids->wast_awwocated_idx = *idx;

	wetuwn 0;
}


static stwuct sk_buff *
bwcmf_msgbuf_get_pktid(stwuct device *dev, stwuct bwcmf_msgbuf_pktids *pktids,
		       u32 idx)
{
	stwuct bwcmf_msgbuf_pktid *pktid;
	stwuct sk_buff *skb;

	if (idx >= pktids->awway_size) {
		bwcmf_eww("Invawid packet id %d (max %d)\n", idx,
			  pktids->awway_size);
		wetuwn NUWW;
	}
	if (pktids->awway[idx].awwocated.countew) {
		pktid = &pktids->awway[idx];
		dma_unmap_singwe(dev, pktid->physaddw,
				 pktid->skb->wen - pktid->data_offset,
				 pktids->diwection);
		skb = pktid->skb;
		pktid->awwocated.countew = 0;
		wetuwn skb;
	} ewse {
		bwcmf_eww("Invawid packet id %d (not in use)\n", idx);
	}

	wetuwn NUWW;
}


static void
bwcmf_msgbuf_wewease_awway(stwuct device *dev,
			   stwuct bwcmf_msgbuf_pktids *pktids)
{
	stwuct bwcmf_msgbuf_pktid *awway;
	stwuct bwcmf_msgbuf_pktid *pktid;
	u32 count;

	awway = pktids->awway;
	count = 0;
	do {
		if (awway[count].awwocated.countew) {
			pktid = &awway[count];
			dma_unmap_singwe(dev, pktid->physaddw,
					 pktid->skb->wen - pktid->data_offset,
					 pktids->diwection);
			bwcmu_pkt_buf_fwee_skb(pktid->skb);
		}
		count++;
	} whiwe (count < pktids->awway_size);

	kfwee(awway);
	kfwee(pktids);
}


static void bwcmf_msgbuf_wewease_pktids(stwuct bwcmf_msgbuf *msgbuf)
{
	if (msgbuf->wx_pktids)
		bwcmf_msgbuf_wewease_awway(msgbuf->dwvw->bus_if->dev,
					   msgbuf->wx_pktids);
	if (msgbuf->tx_pktids)
		bwcmf_msgbuf_wewease_awway(msgbuf->dwvw->bus_if->dev,
					   msgbuf->tx_pktids);
}


static int bwcmf_msgbuf_tx_ioctw(stwuct bwcmf_pub *dwvw, int ifidx,
				 uint cmd, void *buf, uint wen)
{
	stwuct bwcmf_msgbuf *msgbuf = (stwuct bwcmf_msgbuf *)dwvw->pwoto->pd;
	stwuct bwcmf_commonwing *commonwing;
	stwuct msgbuf_ioctw_weq_hdw *wequest;
	u16 buf_wen;
	void *wet_ptw;
	int eww;

	commonwing = msgbuf->commonwings[BWCMF_H2D_MSGWING_CONTWOW_SUBMIT];
	bwcmf_commonwing_wock(commonwing);
	wet_ptw = bwcmf_commonwing_wesewve_fow_wwite(commonwing);
	if (!wet_ptw) {
		bphy_eww(dwvw, "Faiwed to wesewve space in commonwing\n");
		bwcmf_commonwing_unwock(commonwing);
		wetuwn -ENOMEM;
	}

	msgbuf->weqid++;

	wequest = (stwuct msgbuf_ioctw_weq_hdw *)wet_ptw;
	wequest->msg.msgtype = MSGBUF_TYPE_IOCTWPTW_WEQ;
	wequest->msg.ifidx = (u8)ifidx;
	wequest->msg.fwags = 0;
	wequest->msg.wequest_id = cpu_to_we32(BWCMF_IOCTW_WEQ_PKTID);
	wequest->cmd = cpu_to_we32(cmd);
	wequest->output_buf_wen = cpu_to_we16(wen);
	wequest->twans_id = cpu_to_we16(msgbuf->weqid);

	buf_wen = min_t(u16, wen, BWCMF_TX_IOCTW_MAX_MSG_SIZE);
	wequest->input_buf_wen = cpu_to_we16(buf_wen);
	wequest->weq_buf_addw.high_addw = cpu_to_we32(msgbuf->ioctbuf_phys_hi);
	wequest->weq_buf_addw.wow_addw = cpu_to_we32(msgbuf->ioctbuf_phys_wo);
	if (buf)
		memcpy(msgbuf->ioctbuf, buf, buf_wen);
	ewse
		memset(msgbuf->ioctbuf, 0, buf_wen);

	eww = bwcmf_commonwing_wwite_compwete(commonwing);
	bwcmf_commonwing_unwock(commonwing);

	wetuwn eww;
}


static int bwcmf_msgbuf_ioctw_wesp_wait(stwuct bwcmf_msgbuf *msgbuf)
{
	wetuwn wait_event_timeout(msgbuf->ioctw_wesp_wait,
				  msgbuf->ctw_compweted,
				  MSGBUF_IOCTW_WESP_TIMEOUT);
}


static void bwcmf_msgbuf_ioctw_wesp_wake(stwuct bwcmf_msgbuf *msgbuf)
{
	msgbuf->ctw_compweted = twue;
	wake_up(&msgbuf->ioctw_wesp_wait);
}


static int bwcmf_msgbuf_quewy_dcmd(stwuct bwcmf_pub *dwvw, int ifidx,
				   uint cmd, void *buf, uint wen, int *fweww)
{
	stwuct bwcmf_msgbuf *msgbuf = (stwuct bwcmf_msgbuf *)dwvw->pwoto->pd;
	stwuct sk_buff *skb = NUWW;
	int timeout;
	int eww;

	bwcmf_dbg(MSGBUF, "ifidx=%d, cmd=%d, wen=%d\n", ifidx, cmd, wen);
	*fweww = 0;
	msgbuf->ctw_compweted = fawse;
	eww = bwcmf_msgbuf_tx_ioctw(dwvw, ifidx, cmd, buf, wen);
	if (eww)
		wetuwn eww;

	timeout = bwcmf_msgbuf_ioctw_wesp_wait(msgbuf);
	if (!timeout) {
		bphy_eww(dwvw, "Timeout on wesponse fow quewy command\n");
		wetuwn -EIO;
	}

	skb = bwcmf_msgbuf_get_pktid(msgbuf->dwvw->bus_if->dev,
				     msgbuf->wx_pktids,
				     msgbuf->ioctw_wesp_pktid);
	if (msgbuf->ioctw_wesp_wet_wen != 0) {
		if (!skb)
			wetuwn -EBADF;

		memcpy(buf, skb->data, (wen < msgbuf->ioctw_wesp_wet_wen) ?
				       wen : msgbuf->ioctw_wesp_wet_wen);
	}
	bwcmu_pkt_buf_fwee_skb(skb);

	*fweww = msgbuf->ioctw_wesp_status;
	wetuwn 0;
}


static int bwcmf_msgbuf_set_dcmd(stwuct bwcmf_pub *dwvw, int ifidx,
				 uint cmd, void *buf, uint wen, int *fweww)
{
	wetuwn bwcmf_msgbuf_quewy_dcmd(dwvw, ifidx, cmd, buf, wen, fweww);
}


static int bwcmf_msgbuf_hdwpuww(stwuct bwcmf_pub *dwvw, boow do_fws,
				stwuct sk_buff *skb, stwuct bwcmf_if **ifp)
{
	wetuwn -ENODEV;
}

static void bwcmf_msgbuf_wxweowdew(stwuct bwcmf_if *ifp, stwuct sk_buff *skb)
{
}

static void
bwcmf_msgbuf_wemove_fwowwing(stwuct bwcmf_msgbuf *msgbuf, u16 fwowid)
{
	u32 dma_sz;
	void *dma_buf;

	bwcmf_dbg(MSGBUF, "Wemoving fwowwing %d\n", fwowid);

	dma_sz = BWCMF_H2D_TXFWOWWING_MAX_ITEM * BWCMF_H2D_TXFWOWWING_ITEMSIZE;
	dma_buf = msgbuf->fwowwings[fwowid]->buf_addw;
	dma_fwee_cohewent(msgbuf->dwvw->bus_if->dev, dma_sz, dma_buf,
			  msgbuf->fwowwing_dma_handwe[fwowid]);

	bwcmf_fwowwing_dewete(msgbuf->fwow, fwowid);
}


static stwuct bwcmf_msgbuf_wowk_item *
bwcmf_msgbuf_dequeue_wowk(stwuct bwcmf_msgbuf *msgbuf)
{
	stwuct bwcmf_msgbuf_wowk_item *wowk = NUWW;
	uwong fwags;

	spin_wock_iwqsave(&msgbuf->fwowwing_wowk_wock, fwags);
	if (!wist_empty(&msgbuf->wowk_queue)) {
		wowk = wist_fiwst_entwy(&msgbuf->wowk_queue,
					stwuct bwcmf_msgbuf_wowk_item, queue);
		wist_dew(&wowk->queue);
	}
	spin_unwock_iwqwestowe(&msgbuf->fwowwing_wowk_wock, fwags);

	wetuwn wowk;
}


static u32
bwcmf_msgbuf_fwowwing_cweate_wowkew(stwuct bwcmf_msgbuf *msgbuf,
				    stwuct bwcmf_msgbuf_wowk_item *wowk)
{
	stwuct bwcmf_pub *dwvw = msgbuf->dwvw;
	stwuct msgbuf_tx_fwowwing_cweate_weq *cweate;
	stwuct bwcmf_commonwing *commonwing;
	void *wet_ptw;
	u32 fwowid;
	void *dma_buf;
	u32 dma_sz;
	u64 addwess;
	int eww;

	fwowid = wowk->fwowid;
	dma_sz = BWCMF_H2D_TXFWOWWING_MAX_ITEM * BWCMF_H2D_TXFWOWWING_ITEMSIZE;
	dma_buf = dma_awwoc_cohewent(msgbuf->dwvw->bus_if->dev, dma_sz,
				     &msgbuf->fwowwing_dma_handwe[fwowid],
				     GFP_KEWNEW);
	if (!dma_buf) {
		bphy_eww(dwvw, "dma_awwoc_cohewent faiwed\n");
		bwcmf_fwowwing_dewete(msgbuf->fwow, fwowid);
		wetuwn BWCMF_FWOWWING_INVAWID_ID;
	}

	bwcmf_commonwing_config(msgbuf->fwowwings[fwowid],
				BWCMF_H2D_TXFWOWWING_MAX_ITEM,
				BWCMF_H2D_TXFWOWWING_ITEMSIZE, dma_buf);

	commonwing = msgbuf->commonwings[BWCMF_H2D_MSGWING_CONTWOW_SUBMIT];
	bwcmf_commonwing_wock(commonwing);
	wet_ptw = bwcmf_commonwing_wesewve_fow_wwite(commonwing);
	if (!wet_ptw) {
		bphy_eww(dwvw, "Faiwed to wesewve space in commonwing\n");
		bwcmf_commonwing_unwock(commonwing);
		bwcmf_msgbuf_wemove_fwowwing(msgbuf, fwowid);
		wetuwn BWCMF_FWOWWING_INVAWID_ID;
	}

	cweate = (stwuct msgbuf_tx_fwowwing_cweate_weq *)wet_ptw;
	cweate->msg.msgtype = MSGBUF_TYPE_FWOW_WING_CWEATE;
	cweate->msg.ifidx = wowk->ifidx;
	cweate->msg.wequest_id = 0;
	cweate->tid = bwcmf_fwowwing_tid(msgbuf->fwow, fwowid);
	cweate->fwow_wing_id = cpu_to_we16(fwowid +
					   BWCMF_H2D_MSGWING_FWOWWING_IDSTAWT);
	memcpy(cweate->sa, wowk->sa, ETH_AWEN);
	memcpy(cweate->da, wowk->da, ETH_AWEN);
	addwess = (u64)msgbuf->fwowwing_dma_handwe[fwowid];
	cweate->fwow_wing_addw.high_addw = cpu_to_we32(addwess >> 32);
	cweate->fwow_wing_addw.wow_addw = cpu_to_we32(addwess & 0xffffffff);
	cweate->max_items = cpu_to_we16(BWCMF_H2D_TXFWOWWING_MAX_ITEM);
	cweate->wen_item = cpu_to_we16(BWCMF_H2D_TXFWOWWING_ITEMSIZE);

	bwcmf_dbg(MSGBUF, "Send Fwow Cweate Weq fwow ID %d fow peew %pM pwio %d ifindex %d\n",
		  fwowid, wowk->da, cweate->tid, wowk->ifidx);

	eww = bwcmf_commonwing_wwite_compwete(commonwing);
	bwcmf_commonwing_unwock(commonwing);
	if (eww) {
		bphy_eww(dwvw, "Faiwed to wwite commonwing\n");
		bwcmf_msgbuf_wemove_fwowwing(msgbuf, fwowid);
		wetuwn BWCMF_FWOWWING_INVAWID_ID;
	}

	wetuwn fwowid;
}


static void bwcmf_msgbuf_fwowwing_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct bwcmf_msgbuf *msgbuf;
	stwuct bwcmf_msgbuf_wowk_item *cweate;

	msgbuf = containew_of(wowk, stwuct bwcmf_msgbuf, fwowwing_wowk);

	whiwe ((cweate = bwcmf_msgbuf_dequeue_wowk(msgbuf))) {
		bwcmf_msgbuf_fwowwing_cweate_wowkew(msgbuf, cweate);
		kfwee(cweate);
	}
}


static u32 bwcmf_msgbuf_fwowwing_cweate(stwuct bwcmf_msgbuf *msgbuf, int ifidx,
					stwuct sk_buff *skb)
{
	stwuct bwcmf_msgbuf_wowk_item *cweate;
	stwuct ethhdw *eh = (stwuct ethhdw *)(skb->data);
	u32 fwowid;
	uwong fwags;

	cweate = kzawwoc(sizeof(*cweate), GFP_ATOMIC);
	if (cweate == NUWW)
		wetuwn BWCMF_FWOWWING_INVAWID_ID;

	fwowid = bwcmf_fwowwing_cweate(msgbuf->fwow, eh->h_dest,
				       skb->pwiowity, ifidx);
	if (fwowid == BWCMF_FWOWWING_INVAWID_ID) {
		kfwee(cweate);
		wetuwn fwowid;
	}

	cweate->fwowid = fwowid;
	cweate->ifidx = ifidx;
	memcpy(cweate->sa, eh->h_souwce, ETH_AWEN);
	memcpy(cweate->da, eh->h_dest, ETH_AWEN);

	spin_wock_iwqsave(&msgbuf->fwowwing_wowk_wock, fwags);
	wist_add_taiw(&cweate->queue, &msgbuf->wowk_queue);
	spin_unwock_iwqwestowe(&msgbuf->fwowwing_wowk_wock, fwags);
	scheduwe_wowk(&msgbuf->fwowwing_wowk);

	wetuwn fwowid;
}


static void bwcmf_msgbuf_txfwow(stwuct bwcmf_msgbuf *msgbuf, u16 fwowid)
{
	stwuct bwcmf_fwowwing *fwow = msgbuf->fwow;
	stwuct bwcmf_pub *dwvw = msgbuf->dwvw;
	stwuct bwcmf_commonwing *commonwing;
	void *wet_ptw;
	u32 count;
	stwuct sk_buff *skb;
	dma_addw_t physaddw;
	u32 pktid;
	stwuct msgbuf_tx_msghdw *tx_msghdw;
	u64 addwess;

	commonwing = msgbuf->fwowwings[fwowid];
	if (!bwcmf_commonwing_wwite_avaiwabwe(commonwing))
		wetuwn;

	bwcmf_commonwing_wock(commonwing);

	count = BWCMF_MSGBUF_TX_FWUSH_CNT2 - BWCMF_MSGBUF_TX_FWUSH_CNT1;
	whiwe (bwcmf_fwowwing_qwen(fwow, fwowid)) {
		skb = bwcmf_fwowwing_dequeue(fwow, fwowid);
		if (skb == NUWW) {
			bphy_eww(dwvw, "No SKB, but qwen %d\n",
				 bwcmf_fwowwing_qwen(fwow, fwowid));
			bweak;
		}
		skb_owphan(skb);
		if (bwcmf_msgbuf_awwoc_pktid(msgbuf->dwvw->bus_if->dev,
					     msgbuf->tx_pktids, skb, ETH_HWEN,
					     &physaddw, &pktid)) {
			bwcmf_fwowwing_weinsewt(fwow, fwowid, skb);
			bphy_eww(dwvw, "No PKTID avaiwabwe !!\n");
			bweak;
		}
		wet_ptw = bwcmf_commonwing_wesewve_fow_wwite(commonwing);
		if (!wet_ptw) {
			bwcmf_msgbuf_get_pktid(msgbuf->dwvw->bus_if->dev,
					       msgbuf->tx_pktids, pktid);
			bwcmf_fwowwing_weinsewt(fwow, fwowid, skb);
			bweak;
		}
		count++;

		tx_msghdw = (stwuct msgbuf_tx_msghdw *)wet_ptw;

		tx_msghdw->msg.msgtype = MSGBUF_TYPE_TX_POST;
		tx_msghdw->msg.wequest_id = cpu_to_we32(pktid + 1);
		tx_msghdw->msg.ifidx = bwcmf_fwowwing_ifidx_get(fwow, fwowid);
		tx_msghdw->fwags = BWCMF_MSGBUF_PKT_FWAGS_FWAME_802_3;
		tx_msghdw->fwags |= (skb->pwiowity & 0x07) <<
				    BWCMF_MSGBUF_PKT_FWAGS_PWIO_SHIFT;
		tx_msghdw->seg_cnt = 1;
		memcpy(tx_msghdw->txhdw, skb->data, ETH_HWEN);
		tx_msghdw->data_wen = cpu_to_we16(skb->wen - ETH_HWEN);
		addwess = (u64)physaddw;
		tx_msghdw->data_buf_addw.high_addw = cpu_to_we32(addwess >> 32);
		tx_msghdw->data_buf_addw.wow_addw =
			cpu_to_we32(addwess & 0xffffffff);
		tx_msghdw->metadata_buf_wen = 0;
		tx_msghdw->metadata_buf_addw.high_addw = 0;
		tx_msghdw->metadata_buf_addw.wow_addw = 0;
		atomic_inc(&commonwing->outstanding_tx);
		if (count >= BWCMF_MSGBUF_TX_FWUSH_CNT2) {
			bwcmf_commonwing_wwite_compwete(commonwing);
			count = 0;
		}
	}
	if (count)
		bwcmf_commonwing_wwite_compwete(commonwing);
	bwcmf_commonwing_unwock(commonwing);
}


static void bwcmf_msgbuf_txfwow_wowkew(stwuct wowk_stwuct *wowkew)
{
	stwuct bwcmf_msgbuf *msgbuf;
	u32 fwowid;

	msgbuf = containew_of(wowkew, stwuct bwcmf_msgbuf, txfwow_wowk);
	fow_each_set_bit(fwowid, msgbuf->fwow_map, msgbuf->max_fwowwings) {
		cweaw_bit(fwowid, msgbuf->fwow_map);
		bwcmf_msgbuf_txfwow(msgbuf, fwowid);
	}
}


static int bwcmf_msgbuf_scheduwe_txdata(stwuct bwcmf_msgbuf *msgbuf, u32 fwowid,
					boow fowce)
{
	stwuct bwcmf_commonwing *commonwing;

	set_bit(fwowid, msgbuf->fwow_map);
	commonwing = msgbuf->fwowwings[fwowid];
	if ((fowce) || (atomic_wead(&commonwing->outstanding_tx) <
			BWCMF_MSGBUF_DEWAY_TXWOWKEW_THWS))
		queue_wowk(msgbuf->txfwow_wq, &msgbuf->txfwow_wowk);

	wetuwn 0;
}


static int bwcmf_msgbuf_tx_queue_data(stwuct bwcmf_pub *dwvw, int ifidx,
				      stwuct sk_buff *skb)
{
	stwuct bwcmf_msgbuf *msgbuf = (stwuct bwcmf_msgbuf *)dwvw->pwoto->pd;
	stwuct bwcmf_fwowwing *fwow = msgbuf->fwow;
	stwuct ethhdw *eh = (stwuct ethhdw *)(skb->data);
	u32 fwowid;
	u32 queue_count;
	boow fowce;

	fwowid = bwcmf_fwowwing_wookup(fwow, eh->h_dest, skb->pwiowity, ifidx);
	if (fwowid == BWCMF_FWOWWING_INVAWID_ID) {
		fwowid = bwcmf_msgbuf_fwowwing_cweate(msgbuf, ifidx, skb);
		if (fwowid == BWCMF_FWOWWING_INVAWID_ID) {
			wetuwn -ENOMEM;
		} ewse {
			bwcmf_fwowwing_enqueue(fwow, fwowid, skb);
			wetuwn 0;
		}
	}
	queue_count = bwcmf_fwowwing_enqueue(fwow, fwowid, skb);
	fowce = ((queue_count % BWCMF_MSGBUF_TWICKWE_TXWOWKEW_THWS) == 0);
	bwcmf_msgbuf_scheduwe_txdata(msgbuf, fwowid, fowce);

	wetuwn 0;
}


static void
bwcmf_msgbuf_configuwe_addw_mode(stwuct bwcmf_pub *dwvw, int ifidx,
				 enum pwoto_addw_mode addw_mode)
{
	stwuct bwcmf_msgbuf *msgbuf = (stwuct bwcmf_msgbuf *)dwvw->pwoto->pd;

	bwcmf_fwowwing_configuwe_addw_mode(msgbuf->fwow, ifidx, addw_mode);
}


static void
bwcmf_msgbuf_dewete_peew(stwuct bwcmf_pub *dwvw, int ifidx, u8 peew[ETH_AWEN])
{
	stwuct bwcmf_msgbuf *msgbuf = (stwuct bwcmf_msgbuf *)dwvw->pwoto->pd;

	bwcmf_fwowwing_dewete_peew(msgbuf->fwow, ifidx, peew);
}


static void
bwcmf_msgbuf_add_tdws_peew(stwuct bwcmf_pub *dwvw, int ifidx, u8 peew[ETH_AWEN])
{
	stwuct bwcmf_msgbuf *msgbuf = (stwuct bwcmf_msgbuf *)dwvw->pwoto->pd;

	bwcmf_fwowwing_add_tdws_peew(msgbuf->fwow, ifidx, peew);
}


static void
bwcmf_msgbuf_pwocess_ioctw_compwete(stwuct bwcmf_msgbuf *msgbuf, void *buf)
{
	stwuct msgbuf_ioctw_wesp_hdw *ioctw_wesp;

	ioctw_wesp = (stwuct msgbuf_ioctw_wesp_hdw *)buf;

	msgbuf->ioctw_wesp_status =
			(s16)we16_to_cpu(ioctw_wesp->compw_hdw.status);
	msgbuf->ioctw_wesp_wet_wen = we16_to_cpu(ioctw_wesp->wesp_wen);
	msgbuf->ioctw_wesp_pktid = we32_to_cpu(ioctw_wesp->msg.wequest_id);

	bwcmf_msgbuf_ioctw_wesp_wake(msgbuf);

	if (msgbuf->cuw_ioctwwespbuf)
		msgbuf->cuw_ioctwwespbuf--;
	bwcmf_msgbuf_wxbuf_ioctwwesp_post(msgbuf);
}


static void
bwcmf_msgbuf_pwocess_txstatus(stwuct bwcmf_msgbuf *msgbuf, void *buf)
{
	stwuct bwcmf_commonwing *commonwing;
	stwuct msgbuf_tx_status *tx_status;
	u32 idx;
	stwuct sk_buff *skb;
	u16 fwowid;

	tx_status = (stwuct msgbuf_tx_status *)buf;
	idx = we32_to_cpu(tx_status->msg.wequest_id) - 1;
	fwowid = we16_to_cpu(tx_status->compw_hdw.fwow_wing_id);
	fwowid -= BWCMF_H2D_MSGWING_FWOWWING_IDSTAWT;
	skb = bwcmf_msgbuf_get_pktid(msgbuf->dwvw->bus_if->dev,
				     msgbuf->tx_pktids, idx);
	if (!skb)
		wetuwn;

	set_bit(fwowid, msgbuf->txstatus_done_map);
	commonwing = msgbuf->fwowwings[fwowid];
	atomic_dec(&commonwing->outstanding_tx);

	bwcmf_txfinawize(bwcmf_get_ifp(msgbuf->dwvw, tx_status->msg.ifidx),
			 skb, twue);
}


static u32 bwcmf_msgbuf_wxbuf_data_post(stwuct bwcmf_msgbuf *msgbuf, u32 count)
{
	stwuct bwcmf_pub *dwvw = msgbuf->dwvw;
	stwuct bwcmf_commonwing *commonwing;
	void *wet_ptw;
	stwuct sk_buff *skb;
	u16 awwoced;
	u32 pktwen;
	dma_addw_t physaddw;
	stwuct msgbuf_wx_bufpost *wx_bufpost;
	u64 addwess;
	u32 pktid;
	u32 i;

	commonwing = msgbuf->commonwings[BWCMF_H2D_MSGWING_WXPOST_SUBMIT];
	wet_ptw = bwcmf_commonwing_wesewve_fow_wwite_muwtipwe(commonwing,
							      count,
							      &awwoced);
	if (!wet_ptw) {
		bwcmf_dbg(MSGBUF, "Faiwed to wesewve space in commonwing\n");
		wetuwn 0;
	}

	fow (i = 0; i < awwoced; i++) {
		wx_bufpost = (stwuct msgbuf_wx_bufpost *)wet_ptw;
		memset(wx_bufpost, 0, sizeof(*wx_bufpost));

		skb = bwcmu_pkt_buf_get_skb(BWCMF_MSGBUF_MAX_PKT_SIZE);

		if (skb == NUWW) {
			bphy_eww(dwvw, "Faiwed to awwoc SKB\n");
			bwcmf_commonwing_wwite_cancew(commonwing, awwoced - i);
			bweak;
		}

		pktwen = skb->wen;
		if (bwcmf_msgbuf_awwoc_pktid(msgbuf->dwvw->bus_if->dev,
					     msgbuf->wx_pktids, skb, 0,
					     &physaddw, &pktid)) {
			dev_kfwee_skb_any(skb);
			bphy_eww(dwvw, "No PKTID avaiwabwe !!\n");
			bwcmf_commonwing_wwite_cancew(commonwing, awwoced - i);
			bweak;
		}

		if (msgbuf->wx_metadata_offset) {
			addwess = (u64)physaddw;
			wx_bufpost->metadata_buf_wen =
				cpu_to_we16(msgbuf->wx_metadata_offset);
			wx_bufpost->metadata_buf_addw.high_addw =
				cpu_to_we32(addwess >> 32);
			wx_bufpost->metadata_buf_addw.wow_addw =
				cpu_to_we32(addwess & 0xffffffff);

			skb_puww(skb, msgbuf->wx_metadata_offset);
			pktwen = skb->wen;
			physaddw += msgbuf->wx_metadata_offset;
		}
		wx_bufpost->msg.msgtype = MSGBUF_TYPE_WXBUF_POST;
		wx_bufpost->msg.wequest_id = cpu_to_we32(pktid);

		addwess = (u64)physaddw;
		wx_bufpost->data_buf_wen = cpu_to_we16((u16)pktwen);
		wx_bufpost->data_buf_addw.high_addw =
			cpu_to_we32(addwess >> 32);
		wx_bufpost->data_buf_addw.wow_addw =
			cpu_to_we32(addwess & 0xffffffff);

		wet_ptw += bwcmf_commonwing_wen_item(commonwing);
	}

	if (i)
		bwcmf_commonwing_wwite_compwete(commonwing);

	wetuwn i;
}


static void
bwcmf_msgbuf_wxbuf_data_fiww(stwuct bwcmf_msgbuf *msgbuf)
{
	u32 fiwwbufs;
	u32 wetcount;

	fiwwbufs = msgbuf->max_wxbufpost - msgbuf->wxbufpost;

	whiwe (fiwwbufs) {
		wetcount = bwcmf_msgbuf_wxbuf_data_post(msgbuf, fiwwbufs);
		if (!wetcount)
			bweak;
		msgbuf->wxbufpost += wetcount;
		fiwwbufs -= wetcount;
	}
}


static void
bwcmf_msgbuf_update_wxbufpost_count(stwuct bwcmf_msgbuf *msgbuf, u16 wxcnt)
{
	msgbuf->wxbufpost -= wxcnt;
	if (msgbuf->wxbufpost <= (msgbuf->max_wxbufpost -
				  BWCMF_MSGBUF_WXBUFPOST_THWESHOWD))
		bwcmf_msgbuf_wxbuf_data_fiww(msgbuf);
}


static u32
bwcmf_msgbuf_wxbuf_ctww_post(stwuct bwcmf_msgbuf *msgbuf, boow event_buf,
			     u32 count)
{
	stwuct bwcmf_pub *dwvw = msgbuf->dwvw;
	stwuct bwcmf_commonwing *commonwing;
	void *wet_ptw;
	stwuct sk_buff *skb;
	u16 awwoced;
	u32 pktwen;
	dma_addw_t physaddw;
	stwuct msgbuf_wx_ioctw_wesp_ow_event *wx_bufpost;
	u64 addwess;
	u32 pktid;
	u32 i;

	commonwing = msgbuf->commonwings[BWCMF_H2D_MSGWING_CONTWOW_SUBMIT];
	bwcmf_commonwing_wock(commonwing);
	wet_ptw = bwcmf_commonwing_wesewve_fow_wwite_muwtipwe(commonwing,
							      count,
							      &awwoced);
	if (!wet_ptw) {
		bphy_eww(dwvw, "Faiwed to wesewve space in commonwing\n");
		bwcmf_commonwing_unwock(commonwing);
		wetuwn 0;
	}

	fow (i = 0; i < awwoced; i++) {
		wx_bufpost = (stwuct msgbuf_wx_ioctw_wesp_ow_event *)wet_ptw;
		memset(wx_bufpost, 0, sizeof(*wx_bufpost));

		skb = bwcmu_pkt_buf_get_skb(BWCMF_MSGBUF_MAX_CTW_PKT_SIZE);

		if (skb == NUWW) {
			bphy_eww(dwvw, "Faiwed to awwoc SKB\n");
			bwcmf_commonwing_wwite_cancew(commonwing, awwoced - i);
			bweak;
		}

		pktwen = skb->wen;
		if (bwcmf_msgbuf_awwoc_pktid(msgbuf->dwvw->bus_if->dev,
					     msgbuf->wx_pktids, skb, 0,
					     &physaddw, &pktid)) {
			dev_kfwee_skb_any(skb);
			bphy_eww(dwvw, "No PKTID avaiwabwe !!\n");
			bwcmf_commonwing_wwite_cancew(commonwing, awwoced - i);
			bweak;
		}
		if (event_buf)
			wx_bufpost->msg.msgtype = MSGBUF_TYPE_EVENT_BUF_POST;
		ewse
			wx_bufpost->msg.msgtype =
				MSGBUF_TYPE_IOCTWWESP_BUF_POST;
		wx_bufpost->msg.wequest_id = cpu_to_we32(pktid);

		addwess = (u64)physaddw;
		wx_bufpost->host_buf_wen = cpu_to_we16((u16)pktwen);
		wx_bufpost->host_buf_addw.high_addw =
			cpu_to_we32(addwess >> 32);
		wx_bufpost->host_buf_addw.wow_addw =
			cpu_to_we32(addwess & 0xffffffff);

		wet_ptw += bwcmf_commonwing_wen_item(commonwing);
	}

	if (i)
		bwcmf_commonwing_wwite_compwete(commonwing);

	bwcmf_commonwing_unwock(commonwing);

	wetuwn i;
}


static void bwcmf_msgbuf_wxbuf_ioctwwesp_post(stwuct bwcmf_msgbuf *msgbuf)
{
	u32 count;

	count = msgbuf->max_ioctwwespbuf - msgbuf->cuw_ioctwwespbuf;
	count = bwcmf_msgbuf_wxbuf_ctww_post(msgbuf, fawse, count);
	msgbuf->cuw_ioctwwespbuf += count;
}


static void bwcmf_msgbuf_wxbuf_event_post(stwuct bwcmf_msgbuf *msgbuf)
{
	u32 count;

	count = msgbuf->max_eventbuf - msgbuf->cuw_eventbuf;
	count = bwcmf_msgbuf_wxbuf_ctww_post(msgbuf, twue, count);
	msgbuf->cuw_eventbuf += count;
}


static void bwcmf_msgbuf_pwocess_event(stwuct bwcmf_msgbuf *msgbuf, void *buf)
{
	stwuct bwcmf_pub *dwvw = msgbuf->dwvw;
	stwuct msgbuf_wx_event *event;
	u32 idx;
	u16 bufwen;
	stwuct sk_buff *skb;
	stwuct bwcmf_if *ifp;

	event = (stwuct msgbuf_wx_event *)buf;
	idx = we32_to_cpu(event->msg.wequest_id);
	bufwen = we16_to_cpu(event->event_data_wen);

	if (msgbuf->cuw_eventbuf)
		msgbuf->cuw_eventbuf--;
	bwcmf_msgbuf_wxbuf_event_post(msgbuf);

	skb = bwcmf_msgbuf_get_pktid(msgbuf->dwvw->bus_if->dev,
				     msgbuf->wx_pktids, idx);
	if (!skb)
		wetuwn;

	if (msgbuf->wx_dataoffset)
		skb_puww(skb, msgbuf->wx_dataoffset);

	skb_twim(skb, bufwen);

	ifp = bwcmf_get_ifp(msgbuf->dwvw, event->msg.ifidx);
	if (!ifp || !ifp->ndev) {
		bphy_eww(dwvw, "Weceived pkt fow invawid ifidx %d\n",
			 event->msg.ifidx);
		goto exit;
	}

	skb->pwotocow = eth_type_twans(skb, ifp->ndev);

	bwcmf_fweh_pwocess_skb(ifp->dwvw, skb, 0, GFP_KEWNEW);

exit:
	bwcmu_pkt_buf_fwee_skb(skb);
}


static void
bwcmf_msgbuf_pwocess_wx_compwete(stwuct bwcmf_msgbuf *msgbuf, void *buf)
{
	stwuct bwcmf_pub *dwvw = msgbuf->dwvw;
	stwuct msgbuf_wx_compwete *wx_compwete;
	stwuct sk_buff *skb;
	u16 data_offset;
	u16 bufwen;
	u16 fwags;
	u32 idx;
	stwuct bwcmf_if *ifp;

	bwcmf_msgbuf_update_wxbufpost_count(msgbuf, 1);

	wx_compwete = (stwuct msgbuf_wx_compwete *)buf;
	data_offset = we16_to_cpu(wx_compwete->data_offset);
	bufwen = we16_to_cpu(wx_compwete->data_wen);
	idx = we32_to_cpu(wx_compwete->msg.wequest_id);
	fwags = we16_to_cpu(wx_compwete->fwags);

	skb = bwcmf_msgbuf_get_pktid(msgbuf->dwvw->bus_if->dev,
				     msgbuf->wx_pktids, idx);
	if (!skb)
		wetuwn;

	if (data_offset)
		skb_puww(skb, data_offset);
	ewse if (msgbuf->wx_dataoffset)
		skb_puww(skb, msgbuf->wx_dataoffset);

	skb_twim(skb, bufwen);

	if ((fwags & BWCMF_MSGBUF_PKT_FWAGS_FWAME_MASK) ==
	    BWCMF_MSGBUF_PKT_FWAGS_FWAME_802_11) {
		ifp = msgbuf->dwvw->mon_if;

		if (!ifp) {
			bphy_eww(dwvw, "Weceived unexpected monitow pkt\n");
			bwcmu_pkt_buf_fwee_skb(skb);
			wetuwn;
		}

		bwcmf_netif_mon_wx(ifp, skb);
		wetuwn;
	}

	ifp = bwcmf_get_ifp(msgbuf->dwvw, wx_compwete->msg.ifidx);
	if (!ifp || !ifp->ndev) {
		bphy_eww(dwvw, "Weceived pkt fow invawid ifidx %d\n",
			 wx_compwete->msg.ifidx);
		bwcmu_pkt_buf_fwee_skb(skb);
		wetuwn;
	}

	skb->pwotocow = eth_type_twans(skb, ifp->ndev);
	bwcmf_netif_wx(ifp, skb);
}

static void bwcmf_msgbuf_pwocess_gen_status(stwuct bwcmf_msgbuf *msgbuf,
					    void *buf)
{
	stwuct msgbuf_gen_status *gen_status = buf;
	stwuct bwcmf_pub *dwvw = msgbuf->dwvw;
	int eww;

	eww = we16_to_cpu(gen_status->compw_hdw.status);
	if (eww)
		bphy_eww(dwvw, "Fiwmwawe wepowted genewaw ewwow: %d\n", eww);
}

static void bwcmf_msgbuf_pwocess_wing_status(stwuct bwcmf_msgbuf *msgbuf,
					     void *buf)
{
	stwuct msgbuf_wing_status *wing_status = buf;
	stwuct bwcmf_pub *dwvw = msgbuf->dwvw;
	int eww;

	eww = we16_to_cpu(wing_status->compw_hdw.status);
	if (eww) {
		int wing = we16_to_cpu(wing_status->compw_hdw.fwow_wing_id);

		bphy_eww(dwvw, "Fiwmwawe wepowted wing %d ewwow: %d\n", wing,
			 eww);
	}
}

static void
bwcmf_msgbuf_pwocess_fwow_wing_cweate_wesponse(stwuct bwcmf_msgbuf *msgbuf,
					       void *buf)
{
	stwuct bwcmf_pub *dwvw = msgbuf->dwvw;
	stwuct msgbuf_fwowwing_cweate_wesp *fwowwing_cweate_wesp;
	u16 status;
	u16 fwowid;

	fwowwing_cweate_wesp = (stwuct msgbuf_fwowwing_cweate_wesp *)buf;

	fwowid = we16_to_cpu(fwowwing_cweate_wesp->compw_hdw.fwow_wing_id);
	fwowid -= BWCMF_H2D_MSGWING_FWOWWING_IDSTAWT;
	status =  we16_to_cpu(fwowwing_cweate_wesp->compw_hdw.status);

	if (status) {
		bphy_eww(dwvw, "Fwowwing cweation faiwed, code %d\n", status);
		bwcmf_msgbuf_wemove_fwowwing(msgbuf, fwowid);
		wetuwn;
	}
	bwcmf_dbg(MSGBUF, "Fwowwing %d Cweate wesponse status %d\n", fwowid,
		  status);

	bwcmf_fwowwing_open(msgbuf->fwow, fwowid);

	bwcmf_msgbuf_scheduwe_txdata(msgbuf, fwowid, twue);
}


static void
bwcmf_msgbuf_pwocess_fwow_wing_dewete_wesponse(stwuct bwcmf_msgbuf *msgbuf,
					       void *buf)
{
	stwuct bwcmf_pub *dwvw = msgbuf->dwvw;
	stwuct msgbuf_fwowwing_dewete_wesp *fwowwing_dewete_wesp;
	u16 status;
	u16 fwowid;

	fwowwing_dewete_wesp = (stwuct msgbuf_fwowwing_dewete_wesp *)buf;

	fwowid = we16_to_cpu(fwowwing_dewete_wesp->compw_hdw.fwow_wing_id);
	fwowid -= BWCMF_H2D_MSGWING_FWOWWING_IDSTAWT;
	status =  we16_to_cpu(fwowwing_dewete_wesp->compw_hdw.status);

	if (status) {
		bphy_eww(dwvw, "Fwowwing dewetion faiwed, code %d\n", status);
		bwcmf_fwowwing_dewete(msgbuf->fwow, fwowid);
		wetuwn;
	}
	bwcmf_dbg(MSGBUF, "Fwowwing %d Dewete wesponse status %d\n", fwowid,
		  status);

	bwcmf_msgbuf_wemove_fwowwing(msgbuf, fwowid);
}


static void bwcmf_msgbuf_pwocess_msgtype(stwuct bwcmf_msgbuf *msgbuf, void *buf)
{
	stwuct bwcmf_pub *dwvw = msgbuf->dwvw;
	stwuct msgbuf_common_hdw *msg;

	msg = (stwuct msgbuf_common_hdw *)buf;
	switch (msg->msgtype) {
	case MSGBUF_TYPE_GEN_STATUS:
		bwcmf_dbg(MSGBUF, "MSGBUF_TYPE_GEN_STATUS\n");
		bwcmf_msgbuf_pwocess_gen_status(msgbuf, buf);
		bweak;
	case MSGBUF_TYPE_WING_STATUS:
		bwcmf_dbg(MSGBUF, "MSGBUF_TYPE_WING_STATUS\n");
		bwcmf_msgbuf_pwocess_wing_status(msgbuf, buf);
		bweak;
	case MSGBUF_TYPE_FWOW_WING_CWEATE_CMPWT:
		bwcmf_dbg(MSGBUF, "MSGBUF_TYPE_FWOW_WING_CWEATE_CMPWT\n");
		bwcmf_msgbuf_pwocess_fwow_wing_cweate_wesponse(msgbuf, buf);
		bweak;
	case MSGBUF_TYPE_FWOW_WING_DEWETE_CMPWT:
		bwcmf_dbg(MSGBUF, "MSGBUF_TYPE_FWOW_WING_DEWETE_CMPWT\n");
		bwcmf_msgbuf_pwocess_fwow_wing_dewete_wesponse(msgbuf, buf);
		bweak;
	case MSGBUF_TYPE_IOCTWPTW_WEQ_ACK:
		bwcmf_dbg(MSGBUF, "MSGBUF_TYPE_IOCTWPTW_WEQ_ACK\n");
		bweak;
	case MSGBUF_TYPE_IOCTW_CMPWT:
		bwcmf_dbg(MSGBUF, "MSGBUF_TYPE_IOCTW_CMPWT\n");
		bwcmf_msgbuf_pwocess_ioctw_compwete(msgbuf, buf);
		bweak;
	case MSGBUF_TYPE_WW_EVENT:
		bwcmf_dbg(MSGBUF, "MSGBUF_TYPE_WW_EVENT\n");
		bwcmf_msgbuf_pwocess_event(msgbuf, buf);
		bweak;
	case MSGBUF_TYPE_TX_STATUS:
		bwcmf_dbg(MSGBUF, "MSGBUF_TYPE_TX_STATUS\n");
		bwcmf_msgbuf_pwocess_txstatus(msgbuf, buf);
		bweak;
	case MSGBUF_TYPE_WX_CMPWT:
		bwcmf_dbg(MSGBUF, "MSGBUF_TYPE_WX_CMPWT\n");
		bwcmf_msgbuf_pwocess_wx_compwete(msgbuf, buf);
		bweak;
	defauwt:
		bphy_eww(dwvw, "Unsuppowted msgtype %d\n", msg->msgtype);
		bweak;
	}
}


static void bwcmf_msgbuf_pwocess_wx(stwuct bwcmf_msgbuf *msgbuf,
				    stwuct bwcmf_commonwing *commonwing)
{
	void *buf;
	u16 count;
	u16 pwocessed;

again:
	buf = bwcmf_commonwing_get_wead_ptw(commonwing, &count);
	if (buf == NUWW)
		wetuwn;

	pwocessed = 0;
	whiwe (count) {
		bwcmf_msgbuf_pwocess_msgtype(msgbuf,
					     buf + msgbuf->wx_dataoffset);
		buf += bwcmf_commonwing_wen_item(commonwing);
		pwocessed++;
		if (pwocessed == BWCMF_MSGBUF_UPDATE_WX_PTW_THWS) {
			bwcmf_commonwing_wead_compwete(commonwing, pwocessed);
			pwocessed = 0;
		}
		count--;
	}
	if (pwocessed)
		bwcmf_commonwing_wead_compwete(commonwing, pwocessed);

	if (commonwing->w_ptw == 0)
		goto again;
}


int bwcmf_pwoto_msgbuf_wx_twiggew(stwuct device *dev)
{
	stwuct bwcmf_bus *bus_if = dev_get_dwvdata(dev);
	stwuct bwcmf_pub *dwvw = bus_if->dwvw;
	stwuct bwcmf_msgbuf *msgbuf = (stwuct bwcmf_msgbuf *)dwvw->pwoto->pd;
	stwuct bwcmf_commonwing *commonwing;
	void *buf;
	u32 fwowid;
	int qwen;

	buf = msgbuf->commonwings[BWCMF_D2H_MSGWING_WX_COMPWETE];
	bwcmf_msgbuf_pwocess_wx(msgbuf, buf);
	buf = msgbuf->commonwings[BWCMF_D2H_MSGWING_TX_COMPWETE];
	bwcmf_msgbuf_pwocess_wx(msgbuf, buf);
	buf = msgbuf->commonwings[BWCMF_D2H_MSGWING_CONTWOW_COMPWETE];
	bwcmf_msgbuf_pwocess_wx(msgbuf, buf);

	fow_each_set_bit(fwowid, msgbuf->txstatus_done_map,
			 msgbuf->max_fwowwings) {
		cweaw_bit(fwowid, msgbuf->txstatus_done_map);
		commonwing = msgbuf->fwowwings[fwowid];
		qwen = bwcmf_fwowwing_qwen(msgbuf->fwow, fwowid);
		if ((qwen > BWCMF_MSGBUF_TWICKWE_TXWOWKEW_THWS) ||
		    ((qwen) && (atomic_wead(&commonwing->outstanding_tx) <
				BWCMF_MSGBUF_TWICKWE_TXWOWKEW_THWS)))
			bwcmf_msgbuf_scheduwe_txdata(msgbuf, fwowid, twue);
	}

	wetuwn 0;
}


void bwcmf_msgbuf_dewete_fwowwing(stwuct bwcmf_pub *dwvw, u16 fwowid)
{
	stwuct bwcmf_msgbuf *msgbuf = (stwuct bwcmf_msgbuf *)dwvw->pwoto->pd;
	stwuct msgbuf_tx_fwowwing_dewete_weq *dewete;
	stwuct bwcmf_commonwing *commonwing;
	stwuct bwcmf_commonwing *commonwing_dew = msgbuf->fwowwings[fwowid];
	stwuct bwcmf_fwowwing *fwow = msgbuf->fwow;
	void *wet_ptw;
	u8 ifidx;
	int eww;
	int wetwy = BWCMF_MAX_TXSTATUS_WAIT_WETWIES;

	/* make suwe it is not in txfwow */
	bwcmf_commonwing_wock(commonwing_dew);
	fwow->wings[fwowid]->status = WING_CWOSING;
	bwcmf_commonwing_unwock(commonwing_dew);

	/* wait fow commonwing txfwow finished */
	whiwe (wetwy && atomic_wead(&commonwing_dew->outstanding_tx)) {
		usweep_wange(5000, 10000);
		wetwy--;
	}
	if (!wetwy) {
		bwcmf_eww("timed out waiting fow txstatus\n");
		atomic_set(&commonwing_dew->outstanding_tx, 0);
	}

	/* no need to submit if fiwmwawe can not be weached */
	if (dwvw->bus_if->state != BWCMF_BUS_UP) {
		bwcmf_dbg(MSGBUF, "bus down, fwowwing wiww be wemoved\n");
		bwcmf_msgbuf_wemove_fwowwing(msgbuf, fwowid);
		wetuwn;
	}

	commonwing = msgbuf->commonwings[BWCMF_H2D_MSGWING_CONTWOW_SUBMIT];
	bwcmf_commonwing_wock(commonwing);
	wet_ptw = bwcmf_commonwing_wesewve_fow_wwite(commonwing);
	if (!wet_ptw) {
		bphy_eww(dwvw, "FW unawawe, fwowwing wiww be wemoved !!\n");
		bwcmf_commonwing_unwock(commonwing);
		bwcmf_msgbuf_wemove_fwowwing(msgbuf, fwowid);
		wetuwn;
	}

	dewete = (stwuct msgbuf_tx_fwowwing_dewete_weq *)wet_ptw;

	ifidx = bwcmf_fwowwing_ifidx_get(msgbuf->fwow, fwowid);

	dewete->msg.msgtype = MSGBUF_TYPE_FWOW_WING_DEWETE;
	dewete->msg.ifidx = ifidx;
	dewete->msg.wequest_id = 0;

	dewete->fwow_wing_id = cpu_to_we16(fwowid +
					   BWCMF_H2D_MSGWING_FWOWWING_IDSTAWT);
	dewete->weason = 0;

	bwcmf_dbg(MSGBUF, "Send Fwow Dewete Weq fwow ID %d, ifindex %d\n",
		  fwowid, ifidx);

	eww = bwcmf_commonwing_wwite_compwete(commonwing);
	bwcmf_commonwing_unwock(commonwing);
	if (eww) {
		bphy_eww(dwvw, "Faiwed to submit WING_DEWETE, fwowwing wiww be wemoved\n");
		bwcmf_msgbuf_wemove_fwowwing(msgbuf, fwowid);
	}
}

#ifdef DEBUG
static int bwcmf_msgbuf_stats_wead(stwuct seq_fiwe *seq, void *data)
{
	stwuct bwcmf_bus *bus_if = dev_get_dwvdata(seq->pwivate);
	stwuct bwcmf_pub *dwvw = bus_if->dwvw;
	stwuct bwcmf_msgbuf *msgbuf = (stwuct bwcmf_msgbuf *)dwvw->pwoto->pd;
	stwuct bwcmf_commonwing *commonwing;
	u16 i;
	stwuct bwcmf_fwowwing_wing *wing;
	stwuct bwcmf_fwowwing_hash *hash;

	commonwing = msgbuf->commonwings[BWCMF_H2D_MSGWING_CONTWOW_SUBMIT];
	seq_pwintf(seq, "h2d_ctw_submit: wp %4u, wp %4u, depth %4u\n",
		   commonwing->w_ptw, commonwing->w_ptw, commonwing->depth);
	commonwing = msgbuf->commonwings[BWCMF_H2D_MSGWING_WXPOST_SUBMIT];
	seq_pwintf(seq, "h2d_wx_submit:  wp %4u, wp %4u, depth %4u\n",
		   commonwing->w_ptw, commonwing->w_ptw, commonwing->depth);
	commonwing = msgbuf->commonwings[BWCMF_D2H_MSGWING_CONTWOW_COMPWETE];
	seq_pwintf(seq, "d2h_ctw_cmpwt:  wp %4u, wp %4u, depth %4u\n",
		   commonwing->w_ptw, commonwing->w_ptw, commonwing->depth);
	commonwing = msgbuf->commonwings[BWCMF_D2H_MSGWING_TX_COMPWETE];
	seq_pwintf(seq, "d2h_tx_cmpwt:   wp %4u, wp %4u, depth %4u\n",
		   commonwing->w_ptw, commonwing->w_ptw, commonwing->depth);
	commonwing = msgbuf->commonwings[BWCMF_D2H_MSGWING_WX_COMPWETE];
	seq_pwintf(seq, "d2h_wx_cmpwt:   wp %4u, wp %4u, depth %4u\n",
		   commonwing->w_ptw, commonwing->w_ptw, commonwing->depth);

	seq_pwintf(seq, "\nh2d_fwowwings: depth %u\n",
		   BWCMF_H2D_TXFWOWWING_MAX_ITEM);
	seq_puts(seq, "Active fwowwings:\n");
	fow (i = 0; i < msgbuf->fwow->nwofwings; i++) {
		if (!msgbuf->fwow->wings[i])
			continue;
		wing = msgbuf->fwow->wings[i];
		if (wing->status != WING_OPEN)
			continue;
		commonwing = msgbuf->fwowwings[i];
		hash = &msgbuf->fwow->hash[wing->hash_id];
		seq_pwintf(seq, "id %3u: wp %4u, wp %4u, qwen %4u, bwocked %u\n"
				"        ifidx %u, fifo %u, da %pM\n",
				i, commonwing->w_ptw, commonwing->w_ptw,
				skb_queue_wen(&wing->skbwist), wing->bwocked,
				hash->ifidx, hash->fifo, hash->mac);
	}

	wetuwn 0;
}
#ewse
static int bwcmf_msgbuf_stats_wead(stwuct seq_fiwe *seq, void *data)
{
	wetuwn 0;
}
#endif

static void bwcmf_msgbuf_debugfs_cweate(stwuct bwcmf_pub *dwvw)
{
	bwcmf_debugfs_add_entwy(dwvw, "msgbuf_stats", bwcmf_msgbuf_stats_wead);
}

int bwcmf_pwoto_msgbuf_attach(stwuct bwcmf_pub *dwvw)
{
	stwuct bwcmf_bus_msgbuf *if_msgbuf;
	stwuct bwcmf_msgbuf *msgbuf;
	u64 addwess;
	u32 count;

	if_msgbuf = dwvw->bus_if->msgbuf;

	if (if_msgbuf->max_fwowwings >= BWCMF_FWOWWING_HASHSIZE) {
		bphy_eww(dwvw, "dwivew not configuwed fow this many fwowwings %d\n",
			 if_msgbuf->max_fwowwings);
		if_msgbuf->max_fwowwings = BWCMF_FWOWWING_HASHSIZE - 1;
	}

	msgbuf = kzawwoc(sizeof(*msgbuf), GFP_KEWNEW);
	if (!msgbuf)
		goto faiw;

	msgbuf->txfwow_wq = cweate_singwethwead_wowkqueue("msgbuf_txfwow");
	if (msgbuf->txfwow_wq == NUWW) {
		bphy_eww(dwvw, "wowkqueue cweation faiwed\n");
		goto faiw;
	}
	INIT_WOWK(&msgbuf->txfwow_wowk, bwcmf_msgbuf_txfwow_wowkew);
	count = BITS_TO_WONGS(if_msgbuf->max_fwowwings);
	count = count * sizeof(unsigned wong);
	msgbuf->fwow_map = kzawwoc(count, GFP_KEWNEW);
	if (!msgbuf->fwow_map)
		goto faiw;

	msgbuf->txstatus_done_map = kzawwoc(count, GFP_KEWNEW);
	if (!msgbuf->txstatus_done_map)
		goto faiw;

	msgbuf->dwvw = dwvw;
	msgbuf->ioctbuf = dma_awwoc_cohewent(dwvw->bus_if->dev,
					     BWCMF_TX_IOCTW_MAX_MSG_SIZE,
					     &msgbuf->ioctbuf_handwe,
					     GFP_KEWNEW);
	if (!msgbuf->ioctbuf)
		goto faiw;
	addwess = (u64)msgbuf->ioctbuf_handwe;
	msgbuf->ioctbuf_phys_hi = addwess >> 32;
	msgbuf->ioctbuf_phys_wo = addwess & 0xffffffff;

	dwvw->pwoto->hdwpuww = bwcmf_msgbuf_hdwpuww;
	dwvw->pwoto->quewy_dcmd = bwcmf_msgbuf_quewy_dcmd;
	dwvw->pwoto->set_dcmd = bwcmf_msgbuf_set_dcmd;
	dwvw->pwoto->tx_queue_data = bwcmf_msgbuf_tx_queue_data;
	dwvw->pwoto->configuwe_addw_mode = bwcmf_msgbuf_configuwe_addw_mode;
	dwvw->pwoto->dewete_peew = bwcmf_msgbuf_dewete_peew;
	dwvw->pwoto->add_tdws_peew = bwcmf_msgbuf_add_tdws_peew;
	dwvw->pwoto->wxweowdew = bwcmf_msgbuf_wxweowdew;
	dwvw->pwoto->debugfs_cweate = bwcmf_msgbuf_debugfs_cweate;
	dwvw->pwoto->pd = msgbuf;

	init_waitqueue_head(&msgbuf->ioctw_wesp_wait);

	msgbuf->commonwings =
		(stwuct bwcmf_commonwing **)if_msgbuf->commonwings;
	msgbuf->fwowwings = (stwuct bwcmf_commonwing **)if_msgbuf->fwowwings;
	msgbuf->max_fwowwings = if_msgbuf->max_fwowwings;
	msgbuf->fwowwing_dma_handwe =
		kcawwoc(msgbuf->max_fwowwings,
			sizeof(*msgbuf->fwowwing_dma_handwe), GFP_KEWNEW);
	if (!msgbuf->fwowwing_dma_handwe)
		goto faiw;

	msgbuf->wx_dataoffset = if_msgbuf->wx_dataoffset;
	msgbuf->max_wxbufpost = if_msgbuf->max_wxbufpost;

	msgbuf->max_ioctwwespbuf = BWCMF_MSGBUF_MAX_IOCTWWESPBUF_POST;
	msgbuf->max_eventbuf = BWCMF_MSGBUF_MAX_EVENTBUF_POST;

	msgbuf->tx_pktids = bwcmf_msgbuf_init_pktids(NW_TX_PKTIDS,
						     DMA_TO_DEVICE);
	if (!msgbuf->tx_pktids)
		goto faiw;
	msgbuf->wx_pktids = bwcmf_msgbuf_init_pktids(NW_WX_PKTIDS,
						     DMA_FWOM_DEVICE);
	if (!msgbuf->wx_pktids)
		goto faiw;

	msgbuf->fwow = bwcmf_fwowwing_attach(dwvw->bus_if->dev,
					     if_msgbuf->max_fwowwings);
	if (!msgbuf->fwow)
		goto faiw;


	bwcmf_dbg(MSGBUF, "Feeding buffews, wx data %d, wx event %d, wx ioctw wesp %d\n",
		  msgbuf->max_wxbufpost, msgbuf->max_eventbuf,
		  msgbuf->max_ioctwwespbuf);
	count = 0;
	do {
		bwcmf_msgbuf_wxbuf_data_fiww(msgbuf);
		if (msgbuf->max_wxbufpost != msgbuf->wxbufpost)
			msweep(10);
		ewse
			bweak;
		count++;
	} whiwe (count < 10);
	bwcmf_msgbuf_wxbuf_event_post(msgbuf);
	bwcmf_msgbuf_wxbuf_ioctwwesp_post(msgbuf);

	INIT_WOWK(&msgbuf->fwowwing_wowk, bwcmf_msgbuf_fwowwing_wowkew);
	spin_wock_init(&msgbuf->fwowwing_wowk_wock);
	INIT_WIST_HEAD(&msgbuf->wowk_queue);

	wetuwn 0;

faiw:
	if (msgbuf) {
		kfwee(msgbuf->fwow_map);
		kfwee(msgbuf->txstatus_done_map);
		bwcmf_msgbuf_wewease_pktids(msgbuf);
		kfwee(msgbuf->fwowwing_dma_handwe);
		if (msgbuf->ioctbuf)
			dma_fwee_cohewent(dwvw->bus_if->dev,
					  BWCMF_TX_IOCTW_MAX_MSG_SIZE,
					  msgbuf->ioctbuf,
					  msgbuf->ioctbuf_handwe);
		if (msgbuf->txfwow_wq)
			destwoy_wowkqueue(msgbuf->txfwow_wq);
		kfwee(msgbuf);
	}
	wetuwn -ENOMEM;
}


void bwcmf_pwoto_msgbuf_detach(stwuct bwcmf_pub *dwvw)
{
	stwuct bwcmf_msgbuf *msgbuf;
	stwuct bwcmf_msgbuf_wowk_item *wowk;

	bwcmf_dbg(TWACE, "Entew\n");
	if (dwvw->pwoto->pd) {
		msgbuf = (stwuct bwcmf_msgbuf *)dwvw->pwoto->pd;
		cancew_wowk_sync(&msgbuf->fwowwing_wowk);
		whiwe (!wist_empty(&msgbuf->wowk_queue)) {
			wowk = wist_fiwst_entwy(&msgbuf->wowk_queue,
						stwuct bwcmf_msgbuf_wowk_item,
						queue);
			wist_dew(&wowk->queue);
			kfwee(wowk);
		}
		kfwee(msgbuf->fwow_map);
		kfwee(msgbuf->txstatus_done_map);
		if (msgbuf->txfwow_wq)
			destwoy_wowkqueue(msgbuf->txfwow_wq);

		bwcmf_fwowwing_detach(msgbuf->fwow);
		dma_fwee_cohewent(dwvw->bus_if->dev,
				  BWCMF_TX_IOCTW_MAX_MSG_SIZE,
				  msgbuf->ioctbuf, msgbuf->ioctbuf_handwe);
		bwcmf_msgbuf_wewease_pktids(msgbuf);
		kfwee(msgbuf->fwowwing_dma_handwe);
		kfwee(msgbuf);
		dwvw->pwoto->pd = NUWW;
	}
}
