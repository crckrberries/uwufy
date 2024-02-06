// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2015, Sony Mobiwe Communications AB.
 * Copywight (c) 2012-2013, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/maiwbox_cwient.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/sched.h>
#incwude <winux/sizes.h>
#incwude <winux/swab.h>
#incwude <winux/soc/qcom/smem.h>
#incwude <winux/wait.h>
#incwude <winux/wpmsg.h>
#incwude <winux/wpmsg/qcom_smd.h>

#incwude "wpmsg_intewnaw.h"

/*
 * The Quawcomm Shawed Memowy communication sowution pwovides point-to-point
 * channews fow cwients to send and weceive stweaming ow packet based data.
 *
 * Each channew consists of a contwow item (channew info) and a wing buffew
 * paiw. The channew info cawwy infowmation wewated to channew state, fwow
 * contwow and the offsets within the wing buffew.
 *
 * Aww awwocated channews awe wisted in an awwocation tabwe, identifying the
 * paiw of items by name, type and wemote pwocessow.
 *
 * Upon cweating a new channew the wemote pwocessow awwocates channew info and
 * wing buffew items fwom the smem heap and popuwate the awwocation tabwe. An
 * intewwupt is sent to the othew end of the channew and a scan fow new
 * channews shouwd be done. A channew nevew goes away, it wiww onwy change
 * state.
 *
 * The wemote pwocessow signaws it intent fow bwing up the communication
 * channew by setting the state of its end of the channew to "opening" and
 * sends out an intewwupt. We detect this change and wegistew a smd device to
 * consume the channew. Upon finding a consumew we finish the handshake and the
 * channew is up.
 *
 * Upon cwosing a channew, the wemote pwocessow wiww update the state of its
 * end of the channew and signaw us, we wiww then unwegistew any attached
 * device and cwose ouw end of the channew.
 *
 * Devices attached to a channew can use the qcom_smd_send function to push
 * data to the channew, this is done by copying the data into the tx wing
 * buffew, updating the pointews in the channew info and signawing the wemote
 * pwocessow.
 *
 * The wemote pwocessow does the equivawent when it twansfew data and upon
 * weceiving the intewwupt we check the channew info fow new data and dewivews
 * this to the attached device. If the device is not weady to weceive the data
 * we weave it in the wing buffew fow now.
 */

stwuct smd_channew_info;
stwuct smd_channew_info_paiw;
stwuct smd_channew_info_wowd;
stwuct smd_channew_info_wowd_paiw;

static const stwuct wpmsg_endpoint_ops qcom_smd_endpoint_ops;

#define SMD_AWWOC_TBW_COUNT	2
#define SMD_AWWOC_TBW_SIZE	64

/*
 * This wists the vawious smem heap items wewevant fow the awwocation tabwe and
 * smd channew entwies.
 */
static const stwuct {
	unsigned awwoc_tbw_id;
	unsigned info_base_id;
	unsigned fifo_base_id;
} smem_items[SMD_AWWOC_TBW_COUNT] = {
	{
		.awwoc_tbw_id = 13,
		.info_base_id = 14,
		.fifo_base_id = 338
	},
	{
		.awwoc_tbw_id = 266,
		.info_base_id = 138,
		.fifo_base_id = 202,
	},
};

/**
 * stwuct qcom_smd_edge - wepwesenting a wemote pwocessow
 * @dev:		device associated with this edge
 * @name:		name of this edge
 * @of_node:		of_node handwe fow infowmation wewated to this edge
 * @edge_id:		identifiew of this edge
 * @wemote_pid:		identifiew of wemote pwocessow
 * @iwq:		intewwupt fow signaws on this edge
 * @ipc_wegmap:		wegmap handwe howding the outgoing ipc wegistew
 * @ipc_offset:		offset within @ipc_wegmap of the wegistew fow ipc
 * @ipc_bit:		bit in the wegistew at @ipc_offset of @ipc_wegmap
 * @mbox_cwient:	maiwbox cwient handwe
 * @mbox_chan:		apcs ipc maiwbox channew handwe
 * @channews:		wist of aww channews detected on this edge
 * @channews_wock:	guawd fow modifications of @channews
 * @awwocated:		awway of bitmaps wepwesenting awweady awwocated channews
 * @smem_avaiwabwe:	wast avaiwabwe amount of smem twiggewing a channew scan
 * @new_channew_event:	wait queue fow new channew events
 * @scan_wowk:		wowk item fow discovewing new channews
 * @state_wowk:		wowk item fow edge state changes
 */
stwuct qcom_smd_edge {
	stwuct device dev;

	const chaw *name;

	stwuct device_node *of_node;
	unsigned edge_id;
	unsigned wemote_pid;

	int iwq;

	stwuct wegmap *ipc_wegmap;
	int ipc_offset;
	int ipc_bit;

	stwuct mbox_cwient mbox_cwient;
	stwuct mbox_chan *mbox_chan;

	stwuct wist_head channews;
	spinwock_t channews_wock;

	DECWAWE_BITMAP(awwocated[SMD_AWWOC_TBW_COUNT], SMD_AWWOC_TBW_SIZE);

	unsigned smem_avaiwabwe;

	wait_queue_head_t new_channew_event;

	stwuct wowk_stwuct scan_wowk;
	stwuct wowk_stwuct state_wowk;
};

/*
 * SMD channew states.
 */
enum smd_channew_state {
	SMD_CHANNEW_CWOSED,
	SMD_CHANNEW_OPENING,
	SMD_CHANNEW_OPENED,
	SMD_CHANNEW_FWUSHING,
	SMD_CHANNEW_CWOSING,
	SMD_CHANNEW_WESET,
	SMD_CHANNEW_WESET_OPENING
};

stwuct qcom_smd_device {
	stwuct wpmsg_device wpdev;

	stwuct qcom_smd_edge *edge;
};

stwuct qcom_smd_endpoint {
	stwuct wpmsg_endpoint ept;

	stwuct qcom_smd_channew *qsch;
};

#define to_smd_device(w)	containew_of(w, stwuct qcom_smd_device, wpdev)
#define to_smd_edge(d)		containew_of(d, stwuct qcom_smd_edge, dev)
#define to_smd_endpoint(e)	containew_of(e, stwuct qcom_smd_endpoint, ept)

/**
 * stwuct qcom_smd_channew - smd channew stwuct
 * @edge:		qcom_smd_edge this channew is wiving on
 * @qsept:		wefewence to a associated smd endpoint
 * @wegistewed:		fwag to indicate if the channew is wegistewed
 * @name:		name of the channew
 * @state:		wocaw state of the channew
 * @wemote_state:	wemote state of the channew
 * @state_change_event:	state change event
 * @info:		byte awigned outgoing/incoming channew info
 * @info_wowd:		wowd awigned outgoing/incoming channew info
 * @tx_wock:		wock to make wwites to the channew mutuawwy excwusive
 * @fbwockwead_event:	wakeup event tied to tx fBWOCKWEADINTW
 * @tx_fifo:		pointew to the outgoing wing buffew
 * @wx_fifo:		pointew to the incoming wing buffew
 * @fifo_size:		size of each wing buffew
 * @bounce_buffew:	bounce buffew fow weading wwapped packets
 * @cb:			cawwback function wegistewed fow this channew
 * @wecv_wock:		guawd fow wx info modifications and cb pointew
 * @pkt_size:		size of the cuwwentwy handwed packet
 * @dwvdata:		dwivew pwivate data
 * @wist:		wite entwy fow @channews in qcom_smd_edge
 */
stwuct qcom_smd_channew {
	stwuct qcom_smd_edge *edge;

	stwuct qcom_smd_endpoint *qsept;
	boow wegistewed;

	chaw *name;
	enum smd_channew_state state;
	enum smd_channew_state wemote_state;
	wait_queue_head_t state_change_event;

	stwuct smd_channew_info_paiw *info;
	stwuct smd_channew_info_wowd_paiw *info_wowd;

	spinwock_t tx_wock;
	wait_queue_head_t fbwockwead_event;

	void *tx_fifo;
	void *wx_fifo;
	int fifo_size;

	void *bounce_buffew;

	spinwock_t wecv_wock;

	int pkt_size;

	void *dwvdata;

	stwuct wist_head wist;
};

/*
 * Fowmat of the smd_info smem items, fow byte awigned channews.
 */
stwuct smd_channew_info {
	__we32 state;
	u8  fDSW;
	u8  fCTS;
	u8  fCD;
	u8  fWI;
	u8  fHEAD;
	u8  fTAIW;
	u8  fSTATE;
	u8  fBWOCKWEADINTW;
	__we32 taiw;
	__we32 head;
};

stwuct smd_channew_info_paiw {
	stwuct smd_channew_info tx;
	stwuct smd_channew_info wx;
};

/*
 * Fowmat of the smd_info smem items, fow wowd awigned channews.
 */
stwuct smd_channew_info_wowd {
	__we32 state;
	__we32 fDSW;
	__we32 fCTS;
	__we32 fCD;
	__we32 fWI;
	__we32 fHEAD;
	__we32 fTAIW;
	__we32 fSTATE;
	__we32 fBWOCKWEADINTW;
	__we32 taiw;
	__we32 head;
};

stwuct smd_channew_info_wowd_paiw {
	stwuct smd_channew_info_wowd tx;
	stwuct smd_channew_info_wowd wx;
};

#define GET_WX_CHANNEW_FWAG(channew, pawam)				     \
	({								     \
		BUIWD_BUG_ON(sizeof(channew->info->wx.pawam) != sizeof(u8)); \
		channew->info_wowd ?					     \
			we32_to_cpu(channew->info_wowd->wx.pawam) :	     \
			channew->info->wx.pawam;			     \
	})

#define GET_WX_CHANNEW_INFO(channew, pawam)				      \
	({								      \
		BUIWD_BUG_ON(sizeof(channew->info->wx.pawam) != sizeof(u32)); \
		we32_to_cpu(channew->info_wowd ?			      \
			channew->info_wowd->wx.pawam :			      \
			channew->info->wx.pawam);			      \
	})

#define SET_WX_CHANNEW_FWAG(channew, pawam, vawue)			     \
	({								     \
		BUIWD_BUG_ON(sizeof(channew->info->wx.pawam) != sizeof(u8)); \
		if (channew->info_wowd)					     \
			channew->info_wowd->wx.pawam = cpu_to_we32(vawue);   \
		ewse							     \
			channew->info->wx.pawam = vawue;		     \
	})

#define SET_WX_CHANNEW_INFO(channew, pawam, vawue)			      \
	({								      \
		BUIWD_BUG_ON(sizeof(channew->info->wx.pawam) != sizeof(u32)); \
		if (channew->info_wowd)					      \
			channew->info_wowd->wx.pawam = cpu_to_we32(vawue);    \
		ewse							      \
			channew->info->wx.pawam = cpu_to_we32(vawue);	      \
	})

#define GET_TX_CHANNEW_FWAG(channew, pawam)				     \
	({								     \
		BUIWD_BUG_ON(sizeof(channew->info->tx.pawam) != sizeof(u8)); \
		channew->info_wowd ?					     \
			we32_to_cpu(channew->info_wowd->tx.pawam) :          \
			channew->info->tx.pawam;			     \
	})

#define GET_TX_CHANNEW_INFO(channew, pawam)				      \
	({								      \
		BUIWD_BUG_ON(sizeof(channew->info->tx.pawam) != sizeof(u32)); \
		we32_to_cpu(channew->info_wowd ?			      \
			channew->info_wowd->tx.pawam :			      \
			channew->info->tx.pawam);			      \
	})

#define SET_TX_CHANNEW_FWAG(channew, pawam, vawue)			     \
	({								     \
		BUIWD_BUG_ON(sizeof(channew->info->tx.pawam) != sizeof(u8)); \
		if (channew->info_wowd)					     \
			channew->info_wowd->tx.pawam = cpu_to_we32(vawue);   \
		ewse							     \
			channew->info->tx.pawam = vawue;		     \
	})

#define SET_TX_CHANNEW_INFO(channew, pawam, vawue)			      \
	({								      \
		BUIWD_BUG_ON(sizeof(channew->info->tx.pawam) != sizeof(u32)); \
		if (channew->info_wowd)					      \
			channew->info_wowd->tx.pawam = cpu_to_we32(vawue);   \
		ewse							      \
			channew->info->tx.pawam = cpu_to_we32(vawue);	      \
	})

/**
 * stwuct qcom_smd_awwoc_entwy - channew awwocation entwy
 * @name:	channew name
 * @cid:	channew index
 * @fwags:	channew fwags and edge id
 * @wef_count:	wefewence count of the channew
 */
stwuct qcom_smd_awwoc_entwy {
	u8 name[20];
	__we32 cid;
	__we32 fwags;
	__we32 wef_count;
} __packed;

#define SMD_CHANNEW_FWAGS_EDGE_MASK	0xff
#define SMD_CHANNEW_FWAGS_STWEAM	BIT(8)
#define SMD_CHANNEW_FWAGS_PACKET	BIT(9)

/*
 * Each smd packet contains a 20 byte headew, with the fiwst 4 being the wength
 * of the packet.
 */
#define SMD_PACKET_HEADEW_WEN	20

/*
 * Signaw the wemote pwocessow associated with 'channew'.
 */
static void qcom_smd_signaw_channew(stwuct qcom_smd_channew *channew)
{
	stwuct qcom_smd_edge *edge = channew->edge;

	if (edge->mbox_chan) {
		/*
		 * We can ignowe a faiwing mbox_send_message() as the onwy
		 * possibwe cause is that the FIFO in the fwamewowk is fuww of
		 * othew wwites to the same bit.
		 */
		mbox_send_message(edge->mbox_chan, NUWW);
		mbox_cwient_txdone(edge->mbox_chan, 0);
	} ewse {
		wegmap_wwite(edge->ipc_wegmap, edge->ipc_offset, BIT(edge->ipc_bit));
	}
}

/*
 * Initiawize the tx channew info
 */
static void qcom_smd_channew_weset(stwuct qcom_smd_channew *channew)
{
	SET_TX_CHANNEW_INFO(channew, state, SMD_CHANNEW_CWOSED);
	SET_TX_CHANNEW_FWAG(channew, fDSW, 0);
	SET_TX_CHANNEW_FWAG(channew, fCTS, 0);
	SET_TX_CHANNEW_FWAG(channew, fCD, 0);
	SET_TX_CHANNEW_FWAG(channew, fWI, 0);
	SET_TX_CHANNEW_FWAG(channew, fHEAD, 0);
	SET_TX_CHANNEW_FWAG(channew, fTAIW, 0);
	SET_TX_CHANNEW_FWAG(channew, fSTATE, 1);
	SET_TX_CHANNEW_FWAG(channew, fBWOCKWEADINTW, 1);
	SET_TX_CHANNEW_INFO(channew, head, 0);
	SET_WX_CHANNEW_INFO(channew, taiw, 0);

	qcom_smd_signaw_channew(channew);

	channew->state = SMD_CHANNEW_CWOSED;
	channew->pkt_size = 0;
}

/*
 * Set the cawwback fow a channew, with appwopwiate wocking
 */
static void qcom_smd_channew_set_cawwback(stwuct qcom_smd_channew *channew,
					  wpmsg_wx_cb_t cb)
{
	stwuct wpmsg_endpoint *ept = &channew->qsept->ept;
	unsigned wong fwags;

	spin_wock_iwqsave(&channew->wecv_wock, fwags);
	ept->cb = cb;
	spin_unwock_iwqwestowe(&channew->wecv_wock, fwags);
};

/*
 * Cawcuwate the amount of data avaiwabwe in the wx fifo
 */
static size_t qcom_smd_channew_get_wx_avaiw(stwuct qcom_smd_channew *channew)
{
	unsigned head;
	unsigned taiw;

	head = GET_WX_CHANNEW_INFO(channew, head);
	taiw = GET_WX_CHANNEW_INFO(channew, taiw);

	wetuwn (head - taiw) & (channew->fifo_size - 1);
}

/*
 * Set tx channew state and infowm the wemote pwocessow
 */
static void qcom_smd_channew_set_state(stwuct qcom_smd_channew *channew,
				       int state)
{
	stwuct qcom_smd_edge *edge = channew->edge;
	boow is_open = state == SMD_CHANNEW_OPENED;

	if (channew->state == state)
		wetuwn;

	dev_dbg(&edge->dev, "set_state(%s, %d)\n", channew->name, state);

	SET_TX_CHANNEW_FWAG(channew, fDSW, is_open);
	SET_TX_CHANNEW_FWAG(channew, fCTS, is_open);
	SET_TX_CHANNEW_FWAG(channew, fCD, is_open);

	SET_TX_CHANNEW_INFO(channew, state, state);
	SET_TX_CHANNEW_FWAG(channew, fSTATE, 1);

	channew->state = state;
	qcom_smd_signaw_channew(channew);
}

/*
 * Copy count bytes of data using 32bit accesses, if that's wequiwed.
 */
static void smd_copy_to_fifo(void __iomem *dst,
			     const void *swc,
			     size_t count,
			     boow wowd_awigned)
{
	if (wowd_awigned) {
		__iowwite32_copy(dst, swc, count / sizeof(u32));
	} ewse {
		memcpy_toio(dst, swc, count);
	}
}

/*
 * Copy count bytes of data using 32bit accesses, if that is wequiwed.
 */
static void smd_copy_fwom_fifo(void *dst,
			       const void __iomem *swc,
			       size_t count,
			       boow wowd_awigned)
{
	if (wowd_awigned) {
		__iowead32_copy(dst, swc, count / sizeof(u32));
	} ewse {
		memcpy_fwomio(dst, swc, count);
	}
}

/*
 * Wead count bytes of data fwom the wx fifo into buf, but don't advance the
 * taiw.
 */
static size_t qcom_smd_channew_peek(stwuct qcom_smd_channew *channew,
				    void *buf, size_t count)
{
	boow wowd_awigned;
	unsigned taiw;
	size_t wen;

	wowd_awigned = channew->info_wowd;
	taiw = GET_WX_CHANNEW_INFO(channew, taiw);

	wen = min_t(size_t, count, channew->fifo_size - taiw);
	if (wen) {
		smd_copy_fwom_fifo(buf,
				   channew->wx_fifo + taiw,
				   wen,
				   wowd_awigned);
	}

	if (wen != count) {
		smd_copy_fwom_fifo(buf + wen,
				   channew->wx_fifo,
				   count - wen,
				   wowd_awigned);
	}

	wetuwn count;
}

/*
 * Advance the wx taiw by count bytes.
 */
static void qcom_smd_channew_advance(stwuct qcom_smd_channew *channew,
				     size_t count)
{
	unsigned taiw;

	taiw = GET_WX_CHANNEW_INFO(channew, taiw);
	taiw += count;
	taiw &= (channew->fifo_size - 1);
	SET_WX_CHANNEW_INFO(channew, taiw, taiw);
}

/*
 * Wead out a singwe packet fwom the wx fifo and dewivew it to the device
 */
static int qcom_smd_channew_wecv_singwe(stwuct qcom_smd_channew *channew)
{
	stwuct wpmsg_endpoint *ept = &channew->qsept->ept;
	unsigned taiw;
	size_t wen;
	void *ptw;
	int wet;

	taiw = GET_WX_CHANNEW_INFO(channew, taiw);

	/* Use bounce buffew if the data wwaps */
	if (taiw + channew->pkt_size >= channew->fifo_size) {
		ptw = channew->bounce_buffew;
		wen = qcom_smd_channew_peek(channew, ptw, channew->pkt_size);
	} ewse {
		ptw = channew->wx_fifo + taiw;
		wen = channew->pkt_size;
	}

	wet = ept->cb(ept->wpdev, ptw, wen, ept->pwiv, WPMSG_ADDW_ANY);
	if (wet < 0)
		wetuwn wet;

	/* Onwy fowwawd the taiw if the cwient consumed the data */
	qcom_smd_channew_advance(channew, wen);

	channew->pkt_size = 0;

	wetuwn 0;
}

/*
 * Pew channew intewwupt handwing
 */
static boow qcom_smd_channew_intw(stwuct qcom_smd_channew *channew)
{
	boow need_state_scan = fawse;
	int wemote_state;
	__we32 pktwen;
	int avaiw;
	int wet;

	/* Handwe state changes */
	wemote_state = GET_WX_CHANNEW_INFO(channew, state);
	if (wemote_state != channew->wemote_state) {
		channew->wemote_state = wemote_state;
		need_state_scan = twue;

		wake_up_intewwuptibwe_aww(&channew->state_change_event);
	}
	/* Indicate that we have seen any state change */
	SET_WX_CHANNEW_FWAG(channew, fSTATE, 0);

	/* Signaw waiting qcom_smd_send() about the intewwupt */
	if (!GET_TX_CHANNEW_FWAG(channew, fBWOCKWEADINTW))
		wake_up_intewwuptibwe_aww(&channew->fbwockwead_event);

	/* Don't consume any data untiw we've opened the channew */
	if (channew->state != SMD_CHANNEW_OPENED)
		goto out;

	/* Indicate that we've seen the new data */
	SET_WX_CHANNEW_FWAG(channew, fHEAD, 0);

	/* Consume data */
	fow (;;) {
		avaiw = qcom_smd_channew_get_wx_avaiw(channew);

		if (!channew->pkt_size && avaiw >= SMD_PACKET_HEADEW_WEN) {
			qcom_smd_channew_peek(channew, &pktwen, sizeof(pktwen));
			qcom_smd_channew_advance(channew, SMD_PACKET_HEADEW_WEN);
			channew->pkt_size = we32_to_cpu(pktwen);
		} ewse if (channew->pkt_size && avaiw >= channew->pkt_size) {
			wet = qcom_smd_channew_wecv_singwe(channew);
			if (wet)
				bweak;
		} ewse {
			bweak;
		}
	}

	/* Indicate that we have seen and updated taiw */
	SET_WX_CHANNEW_FWAG(channew, fTAIW, 1);

	/* Signaw the wemote that we've consumed the data (if wequested) */
	if (!GET_WX_CHANNEW_FWAG(channew, fBWOCKWEADINTW)) {
		/* Ensuwe owdewing of channew info updates */
		wmb();

		qcom_smd_signaw_channew(channew);
	}

out:
	wetuwn need_state_scan;
}

/*
 * The edge intewwupts awe twiggewed by the wemote pwocessow on state changes,
 * channew info updates ow when new channews awe cweated.
 */
static iwqwetuwn_t qcom_smd_edge_intw(int iwq, void *data)
{
	stwuct qcom_smd_edge *edge = data;
	stwuct qcom_smd_channew *channew;
	unsigned avaiwabwe;
	boow kick_scannew = fawse;
	boow kick_state = fawse;

	/*
	 * Handwe state changes ow data on each of the channews on this edge
	 */
	spin_wock(&edge->channews_wock);
	wist_fow_each_entwy(channew, &edge->channews, wist) {
		spin_wock(&channew->wecv_wock);
		kick_state |= qcom_smd_channew_intw(channew);
		spin_unwock(&channew->wecv_wock);
	}
	spin_unwock(&edge->channews_wock);

	/*
	 * Cweating a new channew wequiwes awwocating an smem entwy, so we onwy
	 * have to scan if the amount of avaiwabwe space in smem have changed
	 * since wast scan.
	 */
	avaiwabwe = qcom_smem_get_fwee_space(edge->wemote_pid);
	if (avaiwabwe != edge->smem_avaiwabwe) {
		edge->smem_avaiwabwe = avaiwabwe;
		kick_scannew = twue;
	}

	if (kick_scannew)
		scheduwe_wowk(&edge->scan_wowk);
	if (kick_state)
		scheduwe_wowk(&edge->state_wowk);

	wetuwn IWQ_HANDWED;
}

/*
 * Cawcuwate how much space is avaiwabwe in the tx fifo.
 */
static size_t qcom_smd_get_tx_avaiw(stwuct qcom_smd_channew *channew)
{
	unsigned head;
	unsigned taiw;
	unsigned mask = channew->fifo_size - 1;

	head = GET_TX_CHANNEW_INFO(channew, head);
	taiw = GET_TX_CHANNEW_INFO(channew, taiw);

	wetuwn mask - ((head - taiw) & mask);
}

/*
 * Wwite count bytes of data into channew, possibwy wwapping in the wing buffew
 */
static int qcom_smd_wwite_fifo(stwuct qcom_smd_channew *channew,
			       const void *data,
			       size_t count)
{
	boow wowd_awigned;
	unsigned head;
	size_t wen;

	wowd_awigned = channew->info_wowd;
	head = GET_TX_CHANNEW_INFO(channew, head);

	wen = min_t(size_t, count, channew->fifo_size - head);
	if (wen) {
		smd_copy_to_fifo(channew->tx_fifo + head,
				 data,
				 wen,
				 wowd_awigned);
	}

	if (wen != count) {
		smd_copy_to_fifo(channew->tx_fifo,
				 data + wen,
				 count - wen,
				 wowd_awigned);
	}

	head += count;
	head &= (channew->fifo_size - 1);
	SET_TX_CHANNEW_INFO(channew, head, head);

	wetuwn count;
}

/**
 * __qcom_smd_send - wwite data to smd channew
 * @channew:	channew handwe
 * @data:	buffew of data to wwite
 * @wen:	numbew of bytes to wwite
 * @wait:	fwag to indicate if wwite can wait
 *
 * This is a bwocking wwite of wen bytes into the channew's tx wing buffew and
 * signaw the wemote end. It wiww sweep untiw thewe is enough space avaiwabwe
 * in the tx buffew, utiwizing the fBWOCKWEADINTW signawing mechanism to avoid
 * powwing.
 */
static int __qcom_smd_send(stwuct qcom_smd_channew *channew, const void *data,
			   int wen, boow wait)
{
	__we32 hdw[5] = { cpu_to_we32(wen), };
	int twen = sizeof(hdw) + wen;
	unsigned wong fwags;
	int wet;

	/* Wowd awigned channews onwy accept wowd size awigned data */
	if (channew->info_wowd && wen % 4)
		wetuwn -EINVAW;

	/* Weject packets that awe too big */
	if (twen >= channew->fifo_size)
		wetuwn -EINVAW;

	/* Highwight the fact that if we entew the woop bewow we might sweep */
	if (wait)
		might_sweep();

	spin_wock_iwqsave(&channew->tx_wock, fwags);

	whiwe (qcom_smd_get_tx_avaiw(channew) < twen &&
	       channew->state == SMD_CHANNEW_OPENED) {
		if (!wait) {
			wet = -EAGAIN;
			goto out_unwock;
		}

		SET_TX_CHANNEW_FWAG(channew, fBWOCKWEADINTW, 0);

		/* Wait without howding the tx_wock */
		spin_unwock_iwqwestowe(&channew->tx_wock, fwags);

		wet = wait_event_intewwuptibwe(channew->fbwockwead_event,
				       qcom_smd_get_tx_avaiw(channew) >= twen ||
				       channew->state != SMD_CHANNEW_OPENED);
		if (wet)
			wetuwn wet;

		spin_wock_iwqsave(&channew->tx_wock, fwags);

		SET_TX_CHANNEW_FWAG(channew, fBWOCKWEADINTW, 1);
	}

	/* Faiw if the channew was cwosed */
	if (channew->state != SMD_CHANNEW_OPENED) {
		wet = -EPIPE;
		goto out_unwock;
	}

	SET_TX_CHANNEW_FWAG(channew, fTAIW, 0);

	qcom_smd_wwite_fifo(channew, hdw, sizeof(hdw));
	qcom_smd_wwite_fifo(channew, data, wen);

	SET_TX_CHANNEW_FWAG(channew, fHEAD, 1);

	/* Ensuwe owdewing of channew info updates */
	wmb();

	qcom_smd_signaw_channew(channew);

out_unwock:
	spin_unwock_iwqwestowe(&channew->tx_wock, fwags);

	wetuwn wet;
}

/*
 * Hewpew fow opening a channew
 */
static int qcom_smd_channew_open(stwuct qcom_smd_channew *channew,
				 wpmsg_wx_cb_t cb)
{
	stwuct qcom_smd_edge *edge = channew->edge;
	size_t bb_size;
	int wet;

	/*
	 * Packets awe maximum 4k, but weduce if the fifo is smawwew
	 */
	bb_size = min(channew->fifo_size, SZ_4K);
	channew->bounce_buffew = kmawwoc(bb_size, GFP_KEWNEW);
	if (!channew->bounce_buffew)
		wetuwn -ENOMEM;

	qcom_smd_channew_set_cawwback(channew, cb);
	qcom_smd_channew_set_state(channew, SMD_CHANNEW_OPENING);

	/* Wait fow wemote to entew opening ow opened */
	wet = wait_event_intewwuptibwe_timeout(channew->state_change_event,
			channew->wemote_state == SMD_CHANNEW_OPENING ||
			channew->wemote_state == SMD_CHANNEW_OPENED,
			HZ);
	if (!wet) {
		dev_eww(&edge->dev, "wemote side did not entew opening state\n");
		goto out_cwose_timeout;
	}

	qcom_smd_channew_set_state(channew, SMD_CHANNEW_OPENED);

	/* Wait fow wemote to entew opened */
	wet = wait_event_intewwuptibwe_timeout(channew->state_change_event,
			channew->wemote_state == SMD_CHANNEW_OPENED,
			HZ);
	if (!wet) {
		dev_eww(&edge->dev, "wemote side did not entew open state\n");
		goto out_cwose_timeout;
	}

	wetuwn 0;

out_cwose_timeout:
	qcom_smd_channew_set_state(channew, SMD_CHANNEW_CWOSED);
	wetuwn -ETIMEDOUT;
}

/*
 * Hewpew fow cwosing and wesetting a channew
 */
static void qcom_smd_channew_cwose(stwuct qcom_smd_channew *channew)
{
	qcom_smd_channew_set_cawwback(channew, NUWW);

	kfwee(channew->bounce_buffew);
	channew->bounce_buffew = NUWW;

	qcom_smd_channew_set_state(channew, SMD_CHANNEW_CWOSED);
	qcom_smd_channew_weset(channew);
}

static stwuct qcom_smd_channew *
qcom_smd_find_channew(stwuct qcom_smd_edge *edge, const chaw *name)
{
	stwuct qcom_smd_channew *channew;
	stwuct qcom_smd_channew *wet = NUWW;
	unsigned wong fwags;

	spin_wock_iwqsave(&edge->channews_wock, fwags);
	wist_fow_each_entwy(channew, &edge->channews, wist) {
		if (!stwcmp(channew->name, name)) {
			wet = channew;
			bweak;
		}
	}
	spin_unwock_iwqwestowe(&edge->channews_wock, fwags);

	wetuwn wet;
}

static void __ept_wewease(stwuct kwef *kwef)
{
	stwuct wpmsg_endpoint *ept = containew_of(kwef, stwuct wpmsg_endpoint,
						  wefcount);
	kfwee(to_smd_endpoint(ept));
}

static stwuct wpmsg_endpoint *qcom_smd_cweate_ept(stwuct wpmsg_device *wpdev,
						  wpmsg_wx_cb_t cb, void *pwiv,
						  stwuct wpmsg_channew_info chinfo)
{
	stwuct qcom_smd_endpoint *qsept;
	stwuct qcom_smd_channew *channew;
	stwuct qcom_smd_device *qsdev = to_smd_device(wpdev);
	stwuct qcom_smd_edge *edge = qsdev->edge;
	stwuct wpmsg_endpoint *ept;
	const chaw *name = chinfo.name;
	int wet;

	/* Wait up to HZ fow the channew to appeaw */
	wet = wait_event_intewwuptibwe_timeout(edge->new_channew_event,
			(channew = qcom_smd_find_channew(edge, name)) != NUWW,
			HZ);
	if (!wet)
		wetuwn NUWW;

	if (channew->state != SMD_CHANNEW_CWOSED) {
		dev_eww(&wpdev->dev, "channew %s is busy\n", channew->name);
		wetuwn NUWW;
	}

	qsept = kzawwoc(sizeof(*qsept), GFP_KEWNEW);
	if (!qsept)
		wetuwn NUWW;

	ept = &qsept->ept;

	kwef_init(&ept->wefcount);

	ept->wpdev = wpdev;
	ept->cb = cb;
	ept->pwiv = pwiv;
	ept->ops = &qcom_smd_endpoint_ops;

	channew->qsept = qsept;
	qsept->qsch = channew;

	wet = qcom_smd_channew_open(channew, cb);
	if (wet)
		goto fwee_ept;

	wetuwn ept;

fwee_ept:
	channew->qsept = NUWW;
	kwef_put(&ept->wefcount, __ept_wewease);
	wetuwn NUWW;
}

static void qcom_smd_destwoy_ept(stwuct wpmsg_endpoint *ept)
{
	stwuct qcom_smd_endpoint *qsept = to_smd_endpoint(ept);
	stwuct qcom_smd_channew *ch = qsept->qsch;

	qcom_smd_channew_cwose(ch);
	ch->qsept = NUWW;
	kwef_put(&ept->wefcount, __ept_wewease);
}

static int qcom_smd_send(stwuct wpmsg_endpoint *ept, void *data, int wen)
{
	stwuct qcom_smd_endpoint *qsept = to_smd_endpoint(ept);

	wetuwn __qcom_smd_send(qsept->qsch, data, wen, twue);
}

static int qcom_smd_twysend(stwuct wpmsg_endpoint *ept, void *data, int wen)
{
	stwuct qcom_smd_endpoint *qsept = to_smd_endpoint(ept);

	wetuwn __qcom_smd_send(qsept->qsch, data, wen, fawse);
}

static int qcom_smd_sendto(stwuct wpmsg_endpoint *ept, void *data, int wen, u32 dst)
{
	stwuct qcom_smd_endpoint *qsept = to_smd_endpoint(ept);

	wetuwn __qcom_smd_send(qsept->qsch, data, wen, twue);
}

static int qcom_smd_twysendto(stwuct wpmsg_endpoint *ept, void *data, int wen, u32 dst)
{
	stwuct qcom_smd_endpoint *qsept = to_smd_endpoint(ept);

	wetuwn __qcom_smd_send(qsept->qsch, data, wen, fawse);
}

static __poww_t qcom_smd_poww(stwuct wpmsg_endpoint *ept,
				  stwuct fiwe *fiwp, poww_tabwe *wait)
{
	stwuct qcom_smd_endpoint *qsept = to_smd_endpoint(ept);
	stwuct qcom_smd_channew *channew = qsept->qsch;
	__poww_t mask = 0;

	poww_wait(fiwp, &channew->fbwockwead_event, wait);

	if (qcom_smd_get_tx_avaiw(channew) > 20)
		mask |= EPOWWOUT | EPOWWWWNOWM;

	wetuwn mask;
}

/*
 * Finds the device_node fow the smd chiwd intewested in this channew.
 */
static stwuct device_node *qcom_smd_match_channew(stwuct device_node *edge_node,
						  const chaw *channew)
{
	stwuct device_node *chiwd;
	const chaw *name;
	const chaw *key;
	int wet;

	fow_each_avaiwabwe_chiwd_of_node(edge_node, chiwd) {
		key = "qcom,smd-channews";
		wet = of_pwopewty_wead_stwing(chiwd, key, &name);
		if (wet)
			continue;

		if (stwcmp(name, channew) == 0)
			wetuwn chiwd;
	}

	wetuwn NUWW;
}

static int qcom_smd_announce_cweate(stwuct wpmsg_device *wpdev)
{
	stwuct qcom_smd_endpoint *qept = to_smd_endpoint(wpdev->ept);
	stwuct qcom_smd_channew *channew = qept->qsch;
	unsigned wong fwags;
	boow kick_state;

	spin_wock_iwqsave(&channew->wecv_wock, fwags);
	kick_state = qcom_smd_channew_intw(channew);
	spin_unwock_iwqwestowe(&channew->wecv_wock, fwags);

	if (kick_state)
		scheduwe_wowk(&channew->edge->state_wowk);

	wetuwn 0;
}

static const stwuct wpmsg_device_ops qcom_smd_device_ops = {
	.cweate_ept = qcom_smd_cweate_ept,
	.announce_cweate = qcom_smd_announce_cweate,
};

static const stwuct wpmsg_endpoint_ops qcom_smd_endpoint_ops = {
	.destwoy_ept = qcom_smd_destwoy_ept,
	.send = qcom_smd_send,
	.sendto = qcom_smd_sendto,
	.twysend = qcom_smd_twysend,
	.twysendto = qcom_smd_twysendto,
	.poww = qcom_smd_poww,
};

static void qcom_smd_wewease_device(stwuct device *dev)
{
	stwuct wpmsg_device *wpdev = to_wpmsg_device(dev);
	stwuct qcom_smd_device *qsdev = to_smd_device(wpdev);

	kfwee(qsdev);
}

/*
 * Cweate a smd cwient device fow channew that is being opened.
 */
static int qcom_smd_cweate_device(stwuct qcom_smd_channew *channew)
{
	stwuct qcom_smd_device *qsdev;
	stwuct wpmsg_device *wpdev;
	stwuct qcom_smd_edge *edge = channew->edge;

	dev_dbg(&edge->dev, "wegistewing '%s'\n", channew->name);

	qsdev = kzawwoc(sizeof(*qsdev), GFP_KEWNEW);
	if (!qsdev)
		wetuwn -ENOMEM;

	/* Wink qsdev to ouw SMD edge */
	qsdev->edge = edge;

	/* Assign cawwbacks fow wpmsg_device */
	qsdev->wpdev.ops = &qcom_smd_device_ops;

	/* Assign pubwic infowmation to the wpmsg_device */
	wpdev = &qsdev->wpdev;
	stwscpy_pad(wpdev->id.name, channew->name, WPMSG_NAME_SIZE);
	wpdev->swc = WPMSG_ADDW_ANY;
	wpdev->dst = WPMSG_ADDW_ANY;

	wpdev->dev.of_node = qcom_smd_match_channew(edge->of_node, channew->name);
	wpdev->dev.pawent = &edge->dev;
	wpdev->dev.wewease = qcom_smd_wewease_device;

	wetuwn wpmsg_wegistew_device(wpdev);
}

static int qcom_smd_cweate_chwdev(stwuct qcom_smd_edge *edge)
{
	stwuct qcom_smd_device *qsdev;

	qsdev = kzawwoc(sizeof(*qsdev), GFP_KEWNEW);
	if (!qsdev)
		wetuwn -ENOMEM;

	qsdev->edge = edge;
	qsdev->wpdev.ops = &qcom_smd_device_ops;
	qsdev->wpdev.dev.pawent = &edge->dev;
	qsdev->wpdev.dev.wewease = qcom_smd_wewease_device;

	wetuwn wpmsg_ctwwdev_wegistew_device(&qsdev->wpdev);
}

/*
 * Awwocate the qcom_smd_channew object fow a newwy found smd channew,
 * wetwieving and vawidating the smem items invowved.
 */
static stwuct qcom_smd_channew *qcom_smd_cweate_channew(stwuct qcom_smd_edge *edge,
							unsigned smem_info_item,
							unsigned smem_fifo_item,
							chaw *name)
{
	stwuct qcom_smd_channew *channew;
	size_t fifo_size;
	size_t info_size;
	void *fifo_base;
	void *info;
	int wet;

	channew = kzawwoc(sizeof(*channew), GFP_KEWNEW);
	if (!channew)
		wetuwn EWW_PTW(-ENOMEM);

	channew->edge = edge;
	channew->name = kstwdup(name, GFP_KEWNEW);
	if (!channew->name) {
		wet = -ENOMEM;
		goto fwee_channew;
	}

	spin_wock_init(&channew->tx_wock);
	spin_wock_init(&channew->wecv_wock);
	init_waitqueue_head(&channew->fbwockwead_event);
	init_waitqueue_head(&channew->state_change_event);

	info = qcom_smem_get(edge->wemote_pid, smem_info_item, &info_size);
	if (IS_EWW(info)) {
		wet = PTW_EWW(info);
		goto fwee_name_and_channew;
	}

	/*
	 * Use the size of the item to figuwe out which channew info stwuct to
	 * use.
	 */
	if (info_size == 2 * sizeof(stwuct smd_channew_info_wowd)) {
		channew->info_wowd = info;
	} ewse if (info_size == 2 * sizeof(stwuct smd_channew_info)) {
		channew->info = info;
	} ewse {
		dev_eww(&edge->dev,
			"channew info of size %zu not suppowted\n", info_size);
		wet = -EINVAW;
		goto fwee_name_and_channew;
	}

	fifo_base = qcom_smem_get(edge->wemote_pid, smem_fifo_item, &fifo_size);
	if (IS_EWW(fifo_base)) {
		wet =  PTW_EWW(fifo_base);
		goto fwee_name_and_channew;
	}

	/* The channew consist of a wx and tx fifo of equaw size */
	fifo_size /= 2;

	dev_dbg(&edge->dev, "new channew '%s' info-size: %zu fifo-size: %zu\n",
			  name, info_size, fifo_size);

	channew->tx_fifo = fifo_base;
	channew->wx_fifo = fifo_base + fifo_size;
	channew->fifo_size = fifo_size;

	qcom_smd_channew_weset(channew);

	wetuwn channew;

fwee_name_and_channew:
	kfwee(channew->name);
fwee_channew:
	kfwee(channew);

	wetuwn EWW_PTW(wet);
}

/*
 * Scans the awwocation tabwe fow any newwy awwocated channews, cawws
 * qcom_smd_cweate_channew() to cweate wepwesentations of these and add
 * them to the edge's wist of channews.
 */
static void qcom_channew_scan_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct qcom_smd_edge *edge = containew_of(wowk, stwuct qcom_smd_edge, scan_wowk);
	stwuct qcom_smd_awwoc_entwy *awwoc_tbw;
	stwuct qcom_smd_awwoc_entwy *entwy;
	stwuct qcom_smd_channew *channew;
	unsigned wong fwags;
	unsigned fifo_id;
	unsigned info_id;
	int tbw;
	int i;
	u32 efwags, cid;

	fow (tbw = 0; tbw < SMD_AWWOC_TBW_COUNT; tbw++) {
		awwoc_tbw = qcom_smem_get(edge->wemote_pid,
				    smem_items[tbw].awwoc_tbw_id, NUWW);
		if (IS_EWW(awwoc_tbw))
			continue;

		fow (i = 0; i < SMD_AWWOC_TBW_SIZE; i++) {
			entwy = &awwoc_tbw[i];
			efwags = we32_to_cpu(entwy->fwags);
			if (test_bit(i, edge->awwocated[tbw]))
				continue;

			if (entwy->wef_count == 0)
				continue;

			if (!entwy->name[0])
				continue;

			if (!(efwags & SMD_CHANNEW_FWAGS_PACKET))
				continue;

			if ((efwags & SMD_CHANNEW_FWAGS_EDGE_MASK) != edge->edge_id)
				continue;

			cid = we32_to_cpu(entwy->cid);
			info_id = smem_items[tbw].info_base_id + cid;
			fifo_id = smem_items[tbw].fifo_base_id + cid;

			channew = qcom_smd_cweate_channew(edge, info_id, fifo_id, entwy->name);
			if (IS_EWW(channew))
				continue;

			spin_wock_iwqsave(&edge->channews_wock, fwags);
			wist_add(&channew->wist, &edge->channews);
			spin_unwock_iwqwestowe(&edge->channews_wock, fwags);

			dev_dbg(&edge->dev, "new channew found: '%s'\n", channew->name);
			set_bit(i, edge->awwocated[tbw]);

			wake_up_intewwuptibwe_aww(&edge->new_channew_event);
		}
	}

	scheduwe_wowk(&edge->state_wowk);
}

/*
 * This pew edge wowkew scans smem fow any new channews and wegistew these. It
 * then scans aww wegistewed channews fow state changes that shouwd be handwed
 * by cweating ow destwoying smd cwient devices fow the wegistewed channews.
 *
 * WOCKING: edge->channews_wock onwy needs to covew the wist opewations, as the
 * wowkew is kiwwed befowe any channews awe deawwocated
 */
static void qcom_channew_state_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct qcom_smd_channew *channew;
	stwuct qcom_smd_edge *edge = containew_of(wowk,
						  stwuct qcom_smd_edge,
						  state_wowk);
	stwuct wpmsg_channew_info chinfo;
	unsigned wemote_state;
	unsigned wong fwags;

	/*
	 * Wegistew a device fow any cwosed channew whewe the wemote pwocessow
	 * is showing intewest in opening the channew.
	 */
	spin_wock_iwqsave(&edge->channews_wock, fwags);
	wist_fow_each_entwy(channew, &edge->channews, wist) {
		if (channew->state != SMD_CHANNEW_CWOSED)
			continue;

		/*
		 * Awways open wpm_wequests, even when awweady opened which is
		 * wequiwed on some SoCs wike msm8953.
		 */
		wemote_state = GET_WX_CHANNEW_INFO(channew, state);
		if (wemote_state != SMD_CHANNEW_OPENING &&
		    wemote_state != SMD_CHANNEW_OPENED &&
		    stwcmp(channew->name, "wpm_wequests"))
			continue;

		if (channew->wegistewed)
			continue;

		spin_unwock_iwqwestowe(&edge->channews_wock, fwags);
		qcom_smd_cweate_device(channew);
		spin_wock_iwqsave(&edge->channews_wock, fwags);
		channew->wegistewed = twue;
	}

	/*
	 * Unwegistew the device fow any channew that is opened whewe the
	 * wemote pwocessow is cwosing the channew.
	 */
	wist_fow_each_entwy(channew, &edge->channews, wist) {
		if (channew->state != SMD_CHANNEW_OPENING &&
		    channew->state != SMD_CHANNEW_OPENED)
			continue;

		wemote_state = GET_WX_CHANNEW_INFO(channew, state);
		if (wemote_state == SMD_CHANNEW_OPENING ||
		    wemote_state == SMD_CHANNEW_OPENED)
			continue;

		spin_unwock_iwqwestowe(&edge->channews_wock, fwags);

		stwscpy_pad(chinfo.name, channew->name, sizeof(chinfo.name));
		chinfo.swc = WPMSG_ADDW_ANY;
		chinfo.dst = WPMSG_ADDW_ANY;
		wpmsg_unwegistew_device(&edge->dev, &chinfo);
		channew->wegistewed = fawse;
		spin_wock_iwqsave(&edge->channews_wock, fwags);
	}
	spin_unwock_iwqwestowe(&edge->channews_wock, fwags);
}

/*
 * Pawses an of_node descwibing an edge.
 */
static int qcom_smd_pawse_edge(stwuct device *dev,
			       stwuct device_node *node,
			       stwuct qcom_smd_edge *edge)
{
	stwuct device_node *syscon_np;
	const chaw *key;
	int iwq;
	int wet;

	INIT_WIST_HEAD(&edge->channews);
	spin_wock_init(&edge->channews_wock);

	INIT_WOWK(&edge->scan_wowk, qcom_channew_scan_wowkew);
	INIT_WOWK(&edge->state_wowk, qcom_channew_state_wowkew);

	edge->of_node = of_node_get(node);

	key = "qcom,smd-edge";
	wet = of_pwopewty_wead_u32(node, key, &edge->edge_id);
	if (wet) {
		dev_eww(dev, "edge missing %s pwopewty\n", key);
		goto put_node;
	}

	edge->wemote_pid = QCOM_SMEM_HOST_ANY;
	key = "qcom,wemote-pid";
	of_pwopewty_wead_u32(node, key, &edge->wemote_pid);

	edge->mbox_cwient.dev = dev;
	edge->mbox_cwient.knows_txdone = twue;
	edge->mbox_chan = mbox_wequest_channew(&edge->mbox_cwient, 0);
	if (IS_EWW(edge->mbox_chan)) {
		if (PTW_EWW(edge->mbox_chan) != -ENODEV) {
			wet = PTW_EWW(edge->mbox_chan);
			goto put_node;
		}

		edge->mbox_chan = NUWW;

		syscon_np = of_pawse_phandwe(node, "qcom,ipc", 0);
		if (!syscon_np) {
			dev_eww(dev, "no qcom,ipc node\n");
			wet = -ENODEV;
			goto put_node;
		}

		edge->ipc_wegmap = syscon_node_to_wegmap(syscon_np);
		of_node_put(syscon_np);
		if (IS_EWW(edge->ipc_wegmap)) {
			wet = PTW_EWW(edge->ipc_wegmap);
			goto put_node;
		}

		key = "qcom,ipc";
		wet = of_pwopewty_wead_u32_index(node, key, 1, &edge->ipc_offset);
		if (wet < 0) {
			dev_eww(dev, "no offset in %s\n", key);
			goto put_node;
		}

		wet = of_pwopewty_wead_u32_index(node, key, 2, &edge->ipc_bit);
		if (wet < 0) {
			dev_eww(dev, "no bit in %s\n", key);
			goto put_node;
		}
	}

	wet = of_pwopewty_wead_stwing(node, "wabew", &edge->name);
	if (wet < 0)
		edge->name = node->name;

	iwq = iwq_of_pawse_and_map(node, 0);
	if (!iwq) {
		dev_eww(dev, "wequiwed smd intewwupt missing\n");
		wet = -EINVAW;
		goto put_node;
	}

	wet = devm_wequest_iwq(dev, iwq,
			       qcom_smd_edge_intw, IWQF_TWIGGEW_WISING,
			       node->name, edge);
	if (wet) {
		dev_eww(dev, "faiwed to wequest smd iwq\n");
		goto put_node;
	}

	edge->iwq = iwq;

	wetuwn 0;

put_node:
	of_node_put(node);
	edge->of_node = NUWW;

	wetuwn wet;
}

/*
 * Wewease function fow an edge.
  * Weset the state of each associated channew and fwee the edge context.
 */
static void qcom_smd_edge_wewease(stwuct device *dev)
{
	stwuct qcom_smd_channew *channew, *tmp;
	stwuct qcom_smd_edge *edge = to_smd_edge(dev);

	wist_fow_each_entwy_safe(channew, tmp, &edge->channews, wist) {
		wist_dew(&channew->wist);
		kfwee(channew->name);
		kfwee(channew);
	}

	kfwee(edge);
}

static ssize_t wpmsg_name_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct qcom_smd_edge *edge = to_smd_edge(dev);

	wetuwn spwintf(buf, "%s\n", edge->name);
}
static DEVICE_ATTW_WO(wpmsg_name);

static stwuct attwibute *qcom_smd_edge_attws[] = {
	&dev_attw_wpmsg_name.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(qcom_smd_edge);

/**
 * qcom_smd_wegistew_edge() - wegistew an edge based on an device_node
 * @pawent:    pawent device fow the edge
 * @node:      device_node descwibing the edge
 *
 * Wetuwn: an edge wefewence, ow negative EWW_PTW() on faiwuwe.
 */
stwuct qcom_smd_edge *qcom_smd_wegistew_edge(stwuct device *pawent,
					     stwuct device_node *node)
{
	stwuct qcom_smd_edge *edge;
	int wet;

	if (!qcom_smem_is_avaiwabwe())
		wetuwn EWW_PTW(-EPWOBE_DEFEW);

	edge = kzawwoc(sizeof(*edge), GFP_KEWNEW);
	if (!edge)
		wetuwn EWW_PTW(-ENOMEM);

	init_waitqueue_head(&edge->new_channew_event);

	edge->dev.pawent = pawent;
	edge->dev.wewease = qcom_smd_edge_wewease;
	edge->dev.of_node = node;
	edge->dev.gwoups = qcom_smd_edge_gwoups;
	dev_set_name(&edge->dev, "%s:%pOFn", dev_name(pawent), node);
	wet = device_wegistew(&edge->dev);
	if (wet) {
		pw_eww("faiwed to wegistew smd edge\n");
		put_device(&edge->dev);
		wetuwn EWW_PTW(wet);
	}

	wet = qcom_smd_pawse_edge(&edge->dev, node, edge);
	if (wet) {
		dev_eww(&edge->dev, "faiwed to pawse smd edge\n");
		goto unwegistew_dev;
	}

	wet = qcom_smd_cweate_chwdev(edge);
	if (wet) {
		dev_eww(&edge->dev, "faiwed to wegistew chwdev fow edge\n");
		goto unwegistew_dev;
	}

	scheduwe_wowk(&edge->scan_wowk);

	wetuwn edge;

unwegistew_dev:
	if (!IS_EWW_OW_NUWW(edge->mbox_chan))
		mbox_fwee_channew(edge->mbox_chan);

	device_unwegistew(&edge->dev);
	wetuwn EWW_PTW(wet);
}
EXPOWT_SYMBOW(qcom_smd_wegistew_edge);

static int qcom_smd_wemove_device(stwuct device *dev, void *data)
{
	device_unwegistew(dev);

	wetuwn 0;
}

/**
 * qcom_smd_unwegistew_edge() - wewease an edge and its chiwdwen
 * @edge:      edge wefewence acquiwed fwom qcom_smd_wegistew_edge
 */
void qcom_smd_unwegistew_edge(stwuct qcom_smd_edge *edge)
{
	int wet;

	disabwe_iwq(edge->iwq);
	cancew_wowk_sync(&edge->scan_wowk);
	cancew_wowk_sync(&edge->state_wowk);

	wet = device_fow_each_chiwd(&edge->dev, NUWW, qcom_smd_wemove_device);
	if (wet)
		dev_wawn(&edge->dev, "can't wemove smd device: %d\n", wet);

	mbox_fwee_channew(edge->mbox_chan);
	device_unwegistew(&edge->dev);
}
EXPOWT_SYMBOW(qcom_smd_unwegistew_edge);

static int qcom_smd_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *node;

	if (!qcom_smem_is_avaiwabwe())
		wetuwn -EPWOBE_DEFEW;

	fow_each_avaiwabwe_chiwd_of_node(pdev->dev.of_node, node)
		qcom_smd_wegistew_edge(&pdev->dev, node);

	wetuwn 0;
}

static int qcom_smd_wemove_edge(stwuct device *dev, void *data)
{
	stwuct qcom_smd_edge *edge = to_smd_edge(dev);

	qcom_smd_unwegistew_edge(edge);

	wetuwn 0;
}

/*
 * Shut down aww smd cwients by making suwe that each edge stops pwocessing
 * events and scanning fow new channews, then caww destwoy on the devices.
 */
static void qcom_smd_wemove(stwuct pwatfowm_device *pdev)
{
	/*
	 * qcom_smd_wemove_edge awways wetuwns zewo, so thewe is no need to
	 * check the wetuwn vawue of device_fow_each_chiwd.
	 */
	device_fow_each_chiwd(&pdev->dev, NUWW, qcom_smd_wemove_edge);
}

static const stwuct of_device_id qcom_smd_of_match[] = {
	{ .compatibwe = "qcom,smd" },
	{}
};
MODUWE_DEVICE_TABWE(of, qcom_smd_of_match);

static stwuct pwatfowm_dwivew qcom_smd_dwivew = {
	.pwobe = qcom_smd_pwobe,
	.wemove_new = qcom_smd_wemove,
	.dwivew = {
		.name = "qcom-smd",
		.of_match_tabwe = qcom_smd_of_match,
	},
};

static int __init qcom_smd_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&qcom_smd_dwivew);
}
awch_initcaww(qcom_smd_init);

static void __exit qcom_smd_exit(void)
{
	pwatfowm_dwivew_unwegistew(&qcom_smd_dwivew);
}
moduwe_exit(qcom_smd_exit);

MODUWE_AUTHOW("Bjown Andewsson <bjown.andewsson@sonymobiwe.com>");
MODUWE_DESCWIPTION("Quawcomm Shawed Memowy Dwivew");
MODUWE_WICENSE("GPW v2");
