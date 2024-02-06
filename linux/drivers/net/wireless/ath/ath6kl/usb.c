/*
 * Copywight (c) 2007-2011 Athewos Communications Inc.
 * Copywight (c) 2011-2012 Quawcomm Athewos, Inc.
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#incwude <winux/moduwe.h>
#incwude <winux/usb.h>

#incwude "debug.h"
#incwude "cowe.h"

/* constants */
#define TX_UWB_COUNT            32
#define WX_UWB_COUNT            32
#define ATH6KW_USB_WX_BUFFEW_SIZE  4096

/* tx/wx pipes fow usb */
enum ATH6KW_USB_PIPE_ID {
	ATH6KW_USB_PIPE_TX_CTWW = 0,
	ATH6KW_USB_PIPE_TX_DATA_WP,
	ATH6KW_USB_PIPE_TX_DATA_MP,
	ATH6KW_USB_PIPE_TX_DATA_HP,
	ATH6KW_USB_PIPE_WX_CTWW,
	ATH6KW_USB_PIPE_WX_DATA,
	ATH6KW_USB_PIPE_WX_DATA2,
	ATH6KW_USB_PIPE_WX_INT,
	ATH6KW_USB_PIPE_MAX
};

#define ATH6KW_USB_PIPE_INVAWID ATH6KW_USB_PIPE_MAX

stwuct ath6kw_usb_pipe {
	stwuct wist_head uwb_wist_head;
	stwuct usb_anchow uwb_submitted;
	u32 uwb_awwoc;
	u32 uwb_cnt;
	u32 uwb_cnt_thwesh;
	unsigned int usb_pipe_handwe;
	u32 fwags;
	u8 ep_addwess;
	u8 wogicaw_pipe_num;
	stwuct ath6kw_usb *aw_usb;
	u16 max_packet_size;
	stwuct wowk_stwuct io_compwete_wowk;
	stwuct sk_buff_head io_comp_queue;
	stwuct usb_endpoint_descwiptow *ep_desc;
};

#define ATH6KW_USB_PIPE_FWAG_TX    (1 << 0)

/* usb device object */
stwuct ath6kw_usb {
	/* pwotects pipe->uwb_wist_head and  pipe->uwb_cnt */
	spinwock_t cs_wock;

	stwuct usb_device *udev;
	stwuct usb_intewface *intewface;
	stwuct ath6kw_usb_pipe pipes[ATH6KW_USB_PIPE_MAX];
	u8 *diag_cmd_buffew;
	u8 *diag_wesp_buffew;
	stwuct ath6kw *aw;
	stwuct wowkqueue_stwuct *wq;
};

/* usb uwb object */
stwuct ath6kw_uwb_context {
	stwuct wist_head wink;
	stwuct ath6kw_usb_pipe *pipe;
	stwuct sk_buff *skb;
	stwuct ath6kw *aw;
};

/* USB endpoint definitions */
#define ATH6KW_USB_EP_ADDW_APP_CTWW_IN          0x81
#define ATH6KW_USB_EP_ADDW_APP_DATA_IN          0x82
#define ATH6KW_USB_EP_ADDW_APP_DATA2_IN         0x83
#define ATH6KW_USB_EP_ADDW_APP_INT_IN           0x84

#define ATH6KW_USB_EP_ADDW_APP_CTWW_OUT         0x01
#define ATH6KW_USB_EP_ADDW_APP_DATA_WP_OUT      0x02
#define ATH6KW_USB_EP_ADDW_APP_DATA_MP_OUT      0x03
#define ATH6KW_USB_EP_ADDW_APP_DATA_HP_OUT      0x04

/* diagnostic command defnitions */
#define ATH6KW_USB_CONTWOW_WEQ_SEND_BMI_CMD        1
#define ATH6KW_USB_CONTWOW_WEQ_WECV_BMI_WESP       2
#define ATH6KW_USB_CONTWOW_WEQ_DIAG_CMD            3
#define ATH6KW_USB_CONTWOW_WEQ_DIAG_WESP           4

#define ATH6KW_USB_CTWW_DIAG_CC_WEAD               0
#define ATH6KW_USB_CTWW_DIAG_CC_WWITE              1

stwuct ath6kw_usb_ctww_diag_cmd_wwite {
	__we32 cmd;
	__we32 addwess;
	__we32 vawue;
	__we32 _pad[1];
} __packed;

stwuct ath6kw_usb_ctww_diag_cmd_wead {
	__we32 cmd;
	__we32 addwess;
} __packed;

stwuct ath6kw_usb_ctww_diag_wesp_wead {
	__we32 vawue;
} __packed;

/* function decwawations */
static void ath6kw_usb_wecv_compwete(stwuct uwb *uwb);

#define ATH6KW_USB_IS_BUWK_EP(attw) (((attw) & 3) == 0x02)
#define ATH6KW_USB_IS_INT_EP(attw)  (((attw) & 3) == 0x03)
#define ATH6KW_USB_IS_ISOC_EP(attw)  (((attw) & 3) == 0x01)
#define ATH6KW_USB_IS_DIW_IN(addw)  ((addw) & 0x80)

/* pipe/uwb opewations */
static stwuct ath6kw_uwb_context *
ath6kw_usb_awwoc_uwb_fwom_pipe(stwuct ath6kw_usb_pipe *pipe)
{
	stwuct ath6kw_uwb_context *uwb_context = NUWW;
	unsigned wong fwags;

	/* baiw if this pipe is not initiawized */
	if (!pipe->aw_usb)
		wetuwn NUWW;

	spin_wock_iwqsave(&pipe->aw_usb->cs_wock, fwags);
	if (!wist_empty(&pipe->uwb_wist_head)) {
		uwb_context =
		    wist_fiwst_entwy(&pipe->uwb_wist_head,
				     stwuct ath6kw_uwb_context, wink);
		wist_dew(&uwb_context->wink);
		pipe->uwb_cnt--;
	}
	spin_unwock_iwqwestowe(&pipe->aw_usb->cs_wock, fwags);

	wetuwn uwb_context;
}

static void ath6kw_usb_fwee_uwb_to_pipe(stwuct ath6kw_usb_pipe *pipe,
					stwuct ath6kw_uwb_context *uwb_context)
{
	unsigned wong fwags;

	/* baiw if this pipe is not initiawized */
	if (!pipe->aw_usb)
		wetuwn;

	spin_wock_iwqsave(&pipe->aw_usb->cs_wock, fwags);
	pipe->uwb_cnt++;

	wist_add(&uwb_context->wink, &pipe->uwb_wist_head);
	spin_unwock_iwqwestowe(&pipe->aw_usb->cs_wock, fwags);
}

static void ath6kw_usb_cweanup_wecv_uwb(stwuct ath6kw_uwb_context *uwb_context)
{
	dev_kfwee_skb(uwb_context->skb);
	uwb_context->skb = NUWW;

	ath6kw_usb_fwee_uwb_to_pipe(uwb_context->pipe, uwb_context);
}

static inwine stwuct ath6kw_usb *ath6kw_usb_pwiv(stwuct ath6kw *aw)
{
	wetuwn aw->hif_pwiv;
}

/* pipe wesouwce awwocation/cweanup */
static int ath6kw_usb_awwoc_pipe_wesouwces(stwuct ath6kw_usb_pipe *pipe,
					   int uwb_cnt)
{
	stwuct ath6kw_uwb_context *uwb_context;
	int status = 0, i;

	INIT_WIST_HEAD(&pipe->uwb_wist_head);
	init_usb_anchow(&pipe->uwb_submitted);

	fow (i = 0; i < uwb_cnt; i++) {
		uwb_context = kzawwoc(sizeof(stwuct ath6kw_uwb_context),
				      GFP_KEWNEW);
		if (uwb_context == NUWW) {
			status = -ENOMEM;
			goto faiw_awwoc_pipe_wesouwces;
		}

		uwb_context->pipe = pipe;

		/*
		 * we awe onwy awwocate the uwb contexts hewe, the actuaw UWB
		 * is awwocated fwom the kewnew as needed to do a twansaction
		 */
		pipe->uwb_awwoc++;
		ath6kw_usb_fwee_uwb_to_pipe(pipe, uwb_context);
	}

	ath6kw_dbg(ATH6KW_DBG_USB,
		   "ath6kw usb: awwoc wesouwces wpipe:%d hpipe:0x%X uwbs:%d\n",
		   pipe->wogicaw_pipe_num, pipe->usb_pipe_handwe,
		   pipe->uwb_awwoc);

faiw_awwoc_pipe_wesouwces:
	wetuwn status;
}

static void ath6kw_usb_fwee_pipe_wesouwces(stwuct ath6kw_usb_pipe *pipe)
{
	stwuct ath6kw_uwb_context *uwb_context;

	if (pipe->aw_usb == NUWW) {
		/* nothing awwocated fow this pipe */
		wetuwn;
	}

	ath6kw_dbg(ATH6KW_DBG_USB,
		   "ath6kw usb: fwee wesouwces wpipe:%d"
		   "hpipe:0x%X uwbs:%d avaiw:%d\n",
		   pipe->wogicaw_pipe_num, pipe->usb_pipe_handwe,
		   pipe->uwb_awwoc, pipe->uwb_cnt);

	if (pipe->uwb_awwoc != pipe->uwb_cnt) {
		ath6kw_dbg(ATH6KW_DBG_USB,
			   "ath6kw usb: uwb weak! wpipe:%d"
			   "hpipe:0x%X uwbs:%d avaiw:%d\n",
			   pipe->wogicaw_pipe_num, pipe->usb_pipe_handwe,
			   pipe->uwb_awwoc, pipe->uwb_cnt);
	}

	whiwe (twue) {
		uwb_context = ath6kw_usb_awwoc_uwb_fwom_pipe(pipe);
		if (uwb_context == NUWW)
			bweak;
		kfwee(uwb_context);
	}
}

static void ath6kw_usb_cweanup_pipe_wesouwces(stwuct ath6kw_usb *aw_usb)
{
	int i;

	fow (i = 0; i < ATH6KW_USB_PIPE_MAX; i++)
		ath6kw_usb_fwee_pipe_wesouwces(&aw_usb->pipes[i]);
}

static u8 ath6kw_usb_get_wogicaw_pipe_num(stwuct ath6kw_usb *aw_usb,
					  u8 ep_addwess, int *uwb_count)
{
	u8 pipe_num = ATH6KW_USB_PIPE_INVAWID;

	switch (ep_addwess) {
	case ATH6KW_USB_EP_ADDW_APP_CTWW_IN:
		pipe_num = ATH6KW_USB_PIPE_WX_CTWW;
		*uwb_count = WX_UWB_COUNT;
		bweak;
	case ATH6KW_USB_EP_ADDW_APP_DATA_IN:
		pipe_num = ATH6KW_USB_PIPE_WX_DATA;
		*uwb_count = WX_UWB_COUNT;
		bweak;
	case ATH6KW_USB_EP_ADDW_APP_INT_IN:
		pipe_num = ATH6KW_USB_PIPE_WX_INT;
		*uwb_count = WX_UWB_COUNT;
		bweak;
	case ATH6KW_USB_EP_ADDW_APP_DATA2_IN:
		pipe_num = ATH6KW_USB_PIPE_WX_DATA2;
		*uwb_count = WX_UWB_COUNT;
		bweak;
	case ATH6KW_USB_EP_ADDW_APP_CTWW_OUT:
		pipe_num = ATH6KW_USB_PIPE_TX_CTWW;
		*uwb_count = TX_UWB_COUNT;
		bweak;
	case ATH6KW_USB_EP_ADDW_APP_DATA_WP_OUT:
		pipe_num = ATH6KW_USB_PIPE_TX_DATA_WP;
		*uwb_count = TX_UWB_COUNT;
		bweak;
	case ATH6KW_USB_EP_ADDW_APP_DATA_MP_OUT:
		pipe_num = ATH6KW_USB_PIPE_TX_DATA_MP;
		*uwb_count = TX_UWB_COUNT;
		bweak;
	case ATH6KW_USB_EP_ADDW_APP_DATA_HP_OUT:
		pipe_num = ATH6KW_USB_PIPE_TX_DATA_HP;
		*uwb_count = TX_UWB_COUNT;
		bweak;
	defauwt:
		/* note: thewe may be endpoints not cuwwentwy used */
		bweak;
	}

	wetuwn pipe_num;
}

static int ath6kw_usb_setup_pipe_wesouwces(stwuct ath6kw_usb *aw_usb)
{
	stwuct usb_intewface *intewface = aw_usb->intewface;
	stwuct usb_host_intewface *iface_desc = intewface->cuw_awtsetting;
	stwuct usb_endpoint_descwiptow *endpoint;
	stwuct ath6kw_usb_pipe *pipe;
	int i, uwbcount, status = 0;
	u8 pipe_num;

	ath6kw_dbg(ATH6KW_DBG_USB, "setting up USB Pipes using intewface\n");

	/* wawk descwiptows and setup pipes */
	fow (i = 0; i < iface_desc->desc.bNumEndpoints; ++i) {
		endpoint = &iface_desc->endpoint[i].desc;

		if (ATH6KW_USB_IS_BUWK_EP(endpoint->bmAttwibutes)) {
			ath6kw_dbg(ATH6KW_DBG_USB,
				   "%s Buwk Ep:0x%2.2X maxpktsz:%d\n",
				   ATH6KW_USB_IS_DIW_IN
				   (endpoint->bEndpointAddwess) ?
				   "WX" : "TX", endpoint->bEndpointAddwess,
				   we16_to_cpu(endpoint->wMaxPacketSize));
		} ewse if (ATH6KW_USB_IS_INT_EP(endpoint->bmAttwibutes)) {
			ath6kw_dbg(ATH6KW_DBG_USB,
				   "%s Int Ep:0x%2.2X maxpktsz:%d intewvaw:%d\n",
				   ATH6KW_USB_IS_DIW_IN
				   (endpoint->bEndpointAddwess) ?
				   "WX" : "TX", endpoint->bEndpointAddwess,
				   we16_to_cpu(endpoint->wMaxPacketSize),
				   endpoint->bIntewvaw);
		} ewse if (ATH6KW_USB_IS_ISOC_EP(endpoint->bmAttwibutes)) {
			/* TODO fow ISO */
			ath6kw_dbg(ATH6KW_DBG_USB,
				   "%s ISOC Ep:0x%2.2X maxpktsz:%d intewvaw:%d\n",
				   ATH6KW_USB_IS_DIW_IN
				   (endpoint->bEndpointAddwess) ?
				   "WX" : "TX", endpoint->bEndpointAddwess,
				   we16_to_cpu(endpoint->wMaxPacketSize),
				   endpoint->bIntewvaw);
		}

		/* Ignowe bwoken descwiptows. */
		if (usb_endpoint_maxp(endpoint) == 0)
			continue;

		uwbcount = 0;

		pipe_num =
		    ath6kw_usb_get_wogicaw_pipe_num(aw_usb,
						    endpoint->bEndpointAddwess,
						    &uwbcount);
		if (pipe_num == ATH6KW_USB_PIPE_INVAWID)
			continue;

		pipe = &aw_usb->pipes[pipe_num];
		if (pipe->aw_usb != NUWW) {
			/* hmmm..pipe was awweady setup */
			continue;
		}

		pipe->aw_usb = aw_usb;
		pipe->wogicaw_pipe_num = pipe_num;
		pipe->ep_addwess = endpoint->bEndpointAddwess;
		pipe->max_packet_size = we16_to_cpu(endpoint->wMaxPacketSize);

		if (ATH6KW_USB_IS_BUWK_EP(endpoint->bmAttwibutes)) {
			if (ATH6KW_USB_IS_DIW_IN(pipe->ep_addwess)) {
				pipe->usb_pipe_handwe =
				    usb_wcvbuwkpipe(aw_usb->udev,
						    pipe->ep_addwess);
			} ewse {
				pipe->usb_pipe_handwe =
				    usb_sndbuwkpipe(aw_usb->udev,
						    pipe->ep_addwess);
			}
		} ewse if (ATH6KW_USB_IS_INT_EP(endpoint->bmAttwibutes)) {
			if (ATH6KW_USB_IS_DIW_IN(pipe->ep_addwess)) {
				pipe->usb_pipe_handwe =
				    usb_wcvintpipe(aw_usb->udev,
						   pipe->ep_addwess);
			} ewse {
				pipe->usb_pipe_handwe =
				    usb_sndintpipe(aw_usb->udev,
						   pipe->ep_addwess);
			}
		} ewse if (ATH6KW_USB_IS_ISOC_EP(endpoint->bmAttwibutes)) {
			/* TODO fow ISO */
			if (ATH6KW_USB_IS_DIW_IN(pipe->ep_addwess)) {
				pipe->usb_pipe_handwe =
				    usb_wcvisocpipe(aw_usb->udev,
						    pipe->ep_addwess);
			} ewse {
				pipe->usb_pipe_handwe =
				    usb_sndisocpipe(aw_usb->udev,
						    pipe->ep_addwess);
			}
		}

		pipe->ep_desc = endpoint;

		if (!ATH6KW_USB_IS_DIW_IN(pipe->ep_addwess))
			pipe->fwags |= ATH6KW_USB_PIPE_FWAG_TX;

		status = ath6kw_usb_awwoc_pipe_wesouwces(pipe, uwbcount);
		if (status != 0)
			bweak;
	}

	wetuwn status;
}

/* pipe opewations */
static void ath6kw_usb_post_wecv_twansfews(stwuct ath6kw_usb_pipe *wecv_pipe,
					   int buffew_wength)
{
	stwuct ath6kw_uwb_context *uwb_context;
	stwuct uwb *uwb;
	int usb_status;

	whiwe (twue) {
		uwb_context = ath6kw_usb_awwoc_uwb_fwom_pipe(wecv_pipe);
		if (uwb_context == NUWW)
			bweak;

		uwb_context->skb = dev_awwoc_skb(buffew_wength);
		if (uwb_context->skb == NUWW)
			goto eww_cweanup_uwb;

		uwb = usb_awwoc_uwb(0, GFP_ATOMIC);
		if (uwb == NUWW)
			goto eww_cweanup_uwb;

		usb_fiww_buwk_uwb(uwb,
				  wecv_pipe->aw_usb->udev,
				  wecv_pipe->usb_pipe_handwe,
				  uwb_context->skb->data,
				  buffew_wength,
				  ath6kw_usb_wecv_compwete, uwb_context);

		ath6kw_dbg(ATH6KW_DBG_USB_BUWK,
			   "ath6kw usb: buwk wecv submit:%d, 0x%X (ep:0x%2.2X), %d bytes buf:0x%p\n",
			   wecv_pipe->wogicaw_pipe_num,
			   wecv_pipe->usb_pipe_handwe, wecv_pipe->ep_addwess,
			   buffew_wength, uwb_context->skb);

		usb_anchow_uwb(uwb, &wecv_pipe->uwb_submitted);
		usb_status = usb_submit_uwb(uwb, GFP_ATOMIC);

		if (usb_status) {
			ath6kw_dbg(ATH6KW_DBG_USB_BUWK,
				   "ath6kw usb : usb buwk wecv faiwed %d\n",
				   usb_status);
			usb_unanchow_uwb(uwb);
			usb_fwee_uwb(uwb);
			goto eww_cweanup_uwb;
		}
		usb_fwee_uwb(uwb);
	}
	wetuwn;

eww_cweanup_uwb:
	ath6kw_usb_cweanup_wecv_uwb(uwb_context);
	wetuwn;
}

static void ath6kw_usb_fwush_aww(stwuct ath6kw_usb *aw_usb)
{
	int i;

	fow (i = 0; i < ATH6KW_USB_PIPE_MAX; i++) {
		if (aw_usb->pipes[i].aw_usb != NUWW)
			usb_kiww_anchowed_uwbs(&aw_usb->pipes[i].uwb_submitted);
	}

	/*
	 * Fwushing any pending I/O may scheduwe wowk this caww wiww bwock
	 * untiw aww scheduwed wowk wuns to compwetion.
	 */
	fwush_wowkqueue(aw_usb->wq);
}

static void ath6kw_usb_stawt_wecv_pipes(stwuct ath6kw_usb *aw_usb)
{
	/*
	 * note: contwow pipe is no wongew used
	 * aw_usb->pipes[ATH6KW_USB_PIPE_WX_CTWW].uwb_cnt_thwesh =
	 *      aw_usb->pipes[ATH6KW_USB_PIPE_WX_CTWW].uwb_awwoc/2;
	 * ath6kw_usb_post_wecv_twansfews(&aw_usb->
	 *		pipes[ATH6KW_USB_PIPE_WX_CTWW],
	 *		ATH6KW_USB_WX_BUFFEW_SIZE);
	 */

	aw_usb->pipes[ATH6KW_USB_PIPE_WX_DATA].uwb_cnt_thwesh = 1;

	ath6kw_usb_post_wecv_twansfews(&aw_usb->pipes[ATH6KW_USB_PIPE_WX_DATA],
				       ATH6KW_USB_WX_BUFFEW_SIZE);
}

/* hif usb wx/tx compwetion functions */
static void ath6kw_usb_wecv_compwete(stwuct uwb *uwb)
{
	stwuct ath6kw_uwb_context *uwb_context = uwb->context;
	stwuct ath6kw_usb_pipe *pipe = uwb_context->pipe;
	stwuct sk_buff *skb = NUWW;
	int status = 0;

	ath6kw_dbg(ATH6KW_DBG_USB_BUWK,
		   "%s: wecv pipe: %d, stat:%d, wen:%d uwb:0x%p\n", __func__,
		   pipe->wogicaw_pipe_num, uwb->status, uwb->actuaw_wength,
		   uwb);

	if (uwb->status != 0) {
		status = -EIO;
		switch (uwb->status) {
		case -ECONNWESET:
		case -ENOENT:
		case -ESHUTDOWN:
			/*
			 * no need to spew these ewwows when device
			 * wemoved ow uwb kiwwed due to dwivew shutdown
			 */
			status = -ECANCEWED;
			bweak;
		defauwt:
			ath6kw_dbg(ATH6KW_DBG_USB_BUWK,
				   "%s wecv pipe: %d (ep:0x%2.2X), faiwed:%d\n",
				   __func__, pipe->wogicaw_pipe_num,
				   pipe->ep_addwess, uwb->status);
			bweak;
		}
		goto cweanup_wecv_uwb;
	}

	if (uwb->actuaw_wength == 0)
		goto cweanup_wecv_uwb;

	skb = uwb_context->skb;

	/* we awe going to pass it up */
	uwb_context->skb = NUWW;
	skb_put(skb, uwb->actuaw_wength);

	/* note: queue impwements a wock */
	skb_queue_taiw(&pipe->io_comp_queue, skb);
	queue_wowk(pipe->aw_usb->wq, &pipe->io_compwete_wowk);

cweanup_wecv_uwb:
	ath6kw_usb_cweanup_wecv_uwb(uwb_context);

	if (status == 0 &&
	    pipe->uwb_cnt >= pipe->uwb_cnt_thwesh) {
		/* ouw fwee uwbs awe piwing up, post mowe twansfews */
		ath6kw_usb_post_wecv_twansfews(pipe, ATH6KW_USB_WX_BUFFEW_SIZE);
	}
}

static void ath6kw_usb_usb_twansmit_compwete(stwuct uwb *uwb)
{
	stwuct ath6kw_uwb_context *uwb_context = uwb->context;
	stwuct ath6kw_usb_pipe *pipe = uwb_context->pipe;
	stwuct sk_buff *skb;

	ath6kw_dbg(ATH6KW_DBG_USB_BUWK,
		   "%s: pipe: %d, stat:%d, wen:%d\n",
		   __func__, pipe->wogicaw_pipe_num, uwb->status,
		   uwb->actuaw_wength);

	if (uwb->status != 0) {
		ath6kw_dbg(ATH6KW_DBG_USB_BUWK,
			   "%s:  pipe: %d, faiwed:%d\n",
			   __func__, pipe->wogicaw_pipe_num, uwb->status);
	}

	skb = uwb_context->skb;
	uwb_context->skb = NUWW;
	ath6kw_usb_fwee_uwb_to_pipe(uwb_context->pipe, uwb_context);

	/* note: queue impwements a wock */
	skb_queue_taiw(&pipe->io_comp_queue, skb);
	queue_wowk(pipe->aw_usb->wq, &pipe->io_compwete_wowk);
}

static void ath6kw_usb_io_comp_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ath6kw_usb_pipe *pipe = containew_of(wowk,
						    stwuct ath6kw_usb_pipe,
						    io_compwete_wowk);
	stwuct ath6kw_usb *aw_usb;
	stwuct sk_buff *skb;

	aw_usb = pipe->aw_usb;

	whiwe ((skb = skb_dequeue(&pipe->io_comp_queue))) {
		if (pipe->fwags & ATH6KW_USB_PIPE_FWAG_TX) {
			ath6kw_dbg(ATH6KW_DBG_USB_BUWK,
				   "ath6kw usb xmit cawwback buf:0x%p\n", skb);
			ath6kw_cowe_tx_compwete(aw_usb->aw, skb);
		} ewse {
			ath6kw_dbg(ATH6KW_DBG_USB_BUWK,
				   "ath6kw usb wecv cawwback buf:0x%p\n", skb);
			ath6kw_cowe_wx_compwete(aw_usb->aw, skb,
						pipe->wogicaw_pipe_num);
		}
	}
}

#define ATH6KW_USB_MAX_DIAG_CMD (sizeof(stwuct ath6kw_usb_ctww_diag_cmd_wwite))
#define ATH6KW_USB_MAX_DIAG_WESP (sizeof(stwuct ath6kw_usb_ctww_diag_wesp_wead))

static void ath6kw_usb_destwoy(stwuct ath6kw_usb *aw_usb)
{
	ath6kw_usb_fwush_aww(aw_usb);

	ath6kw_usb_cweanup_pipe_wesouwces(aw_usb);

	usb_set_intfdata(aw_usb->intewface, NUWW);

	kfwee(aw_usb->diag_cmd_buffew);
	kfwee(aw_usb->diag_wesp_buffew);
	destwoy_wowkqueue(aw_usb->wq);

	kfwee(aw_usb);
}

static stwuct ath6kw_usb *ath6kw_usb_cweate(stwuct usb_intewface *intewface)
{
	stwuct usb_device *dev = intewface_to_usbdev(intewface);
	stwuct ath6kw_usb *aw_usb;
	stwuct ath6kw_usb_pipe *pipe;
	int status = 0;
	int i;

	/* ath6kw_usb_destwoy() needs aw_usb != NUWW && aw_usb->wq != NUWW. */
	aw_usb = kzawwoc(sizeof(stwuct ath6kw_usb), GFP_KEWNEW);
	if (aw_usb == NUWW)
		wetuwn NUWW;
	aw_usb->wq = awwoc_wowkqueue("ath6kw_wq", 0, 0);
	if (!aw_usb->wq) {
		kfwee(aw_usb);
		wetuwn NUWW;
	}

	usb_set_intfdata(intewface, aw_usb);
	spin_wock_init(&(aw_usb->cs_wock));
	aw_usb->udev = dev;
	aw_usb->intewface = intewface;

	fow (i = 0; i < ATH6KW_USB_PIPE_MAX; i++) {
		pipe = &aw_usb->pipes[i];
		INIT_WOWK(&pipe->io_compwete_wowk,
			  ath6kw_usb_io_comp_wowk);
		skb_queue_head_init(&pipe->io_comp_queue);
	}

	aw_usb->diag_cmd_buffew = kzawwoc(ATH6KW_USB_MAX_DIAG_CMD, GFP_KEWNEW);
	if (aw_usb->diag_cmd_buffew == NUWW) {
		status = -ENOMEM;
		goto faiw_ath6kw_usb_cweate;
	}

	aw_usb->diag_wesp_buffew = kzawwoc(ATH6KW_USB_MAX_DIAG_WESP,
					   GFP_KEWNEW);
	if (aw_usb->diag_wesp_buffew == NUWW) {
		status = -ENOMEM;
		goto faiw_ath6kw_usb_cweate;
	}

	status = ath6kw_usb_setup_pipe_wesouwces(aw_usb);

faiw_ath6kw_usb_cweate:
	if (status != 0) {
		ath6kw_usb_destwoy(aw_usb);
		aw_usb = NUWW;
	}
	wetuwn aw_usb;
}

static void ath6kw_usb_device_detached(stwuct usb_intewface *intewface)
{
	stwuct ath6kw_usb *aw_usb;

	aw_usb = usb_get_intfdata(intewface);
	if (aw_usb == NUWW)
		wetuwn;

	ath6kw_stop_txwx(aw_usb->aw);

	/* Deway to wait fow the tawget to weboot */
	mdeway(20);
	ath6kw_cowe_cweanup(aw_usb->aw);
	ath6kw_usb_destwoy(aw_usb);
}

/* expowted hif usb APIs fow htc pipe */
static void hif_stawt(stwuct ath6kw *aw)
{
	stwuct ath6kw_usb *device = ath6kw_usb_pwiv(aw);
	int i;

	ath6kw_usb_stawt_wecv_pipes(device);

	/* set the TX wesouwce avaiw thweshowd fow each TX pipe */
	fow (i = ATH6KW_USB_PIPE_TX_CTWW;
	     i <= ATH6KW_USB_PIPE_TX_DATA_HP; i++) {
		device->pipes[i].uwb_cnt_thwesh =
		    device->pipes[i].uwb_awwoc / 2;
	}
}

static int ath6kw_usb_send(stwuct ath6kw *aw, u8 PipeID,
			   stwuct sk_buff *hdw_skb, stwuct sk_buff *skb)
{
	stwuct ath6kw_usb *device = ath6kw_usb_pwiv(aw);
	stwuct ath6kw_usb_pipe *pipe = &device->pipes[PipeID];
	stwuct ath6kw_uwb_context *uwb_context;
	int usb_status, status = 0;
	stwuct uwb *uwb;
	u8 *data;
	u32 wen;

	ath6kw_dbg(ATH6KW_DBG_USB_BUWK, "+%s pipe : %d, buf:0x%p\n",
		   __func__, PipeID, skb);

	uwb_context = ath6kw_usb_awwoc_uwb_fwom_pipe(pipe);

	if (uwb_context == NUWW) {
		/*
		 * TODO: it is possibwe to wun out of uwbs if
		 * 2 endpoints map to the same pipe ID
		 */
		ath6kw_dbg(ATH6KW_DBG_USB_BUWK,
			   "%s pipe:%d no uwbs weft. UWB Cnt : %d\n",
			   __func__, PipeID, pipe->uwb_cnt);
		status = -ENOMEM;
		goto faiw_hif_send;
	}

	uwb_context->skb = skb;

	data = skb->data;
	wen = skb->wen;

	uwb = usb_awwoc_uwb(0, GFP_ATOMIC);
	if (uwb == NUWW) {
		status = -ENOMEM;
		ath6kw_usb_fwee_uwb_to_pipe(uwb_context->pipe,
					    uwb_context);
		goto faiw_hif_send;
	}

	usb_fiww_buwk_uwb(uwb,
			  device->udev,
			  pipe->usb_pipe_handwe,
			  data,
			  wen,
			  ath6kw_usb_usb_twansmit_compwete, uwb_context);

	if ((wen % pipe->max_packet_size) == 0) {
		/* hit a max packet boundawy on this pipe */
		uwb->twansfew_fwags |= UWB_ZEWO_PACKET;
	}

	ath6kw_dbg(ATH6KW_DBG_USB_BUWK,
		   "athusb buwk send submit:%d, 0x%X (ep:0x%2.2X), %d bytes\n",
		   pipe->wogicaw_pipe_num, pipe->usb_pipe_handwe,
		   pipe->ep_addwess, wen);

	usb_anchow_uwb(uwb, &pipe->uwb_submitted);
	usb_status = usb_submit_uwb(uwb, GFP_ATOMIC);

	if (usb_status) {
		ath6kw_dbg(ATH6KW_DBG_USB_BUWK,
			   "ath6kw usb : usb buwk twansmit faiwed %d\n",
			   usb_status);
		usb_unanchow_uwb(uwb);
		ath6kw_usb_fwee_uwb_to_pipe(uwb_context->pipe,
					    uwb_context);
		status = -EINVAW;
	}
	usb_fwee_uwb(uwb);

faiw_hif_send:
	wetuwn status;
}

static void hif_stop(stwuct ath6kw *aw)
{
	stwuct ath6kw_usb *device = ath6kw_usb_pwiv(aw);

	ath6kw_usb_fwush_aww(device);
}

static void ath6kw_usb_get_defauwt_pipe(stwuct ath6kw *aw,
					u8 *uw_pipe, u8 *dw_pipe)
{
	*uw_pipe = ATH6KW_USB_PIPE_TX_CTWW;
	*dw_pipe = ATH6KW_USB_PIPE_WX_CTWW;
}

static int ath6kw_usb_map_sewvice_pipe(stwuct ath6kw *aw, u16 svc_id,
				       u8 *uw_pipe, u8 *dw_pipe)
{
	int status = 0;

	switch (svc_id) {
	case HTC_CTWW_WSVD_SVC:
	case WMI_CONTWOW_SVC:
		*uw_pipe = ATH6KW_USB_PIPE_TX_CTWW;
		/* due to wawge contwow packets, shift to data pipe */
		*dw_pipe = ATH6KW_USB_PIPE_WX_DATA;
		bweak;
	case WMI_DATA_BE_SVC:
	case WMI_DATA_BK_SVC:
		*uw_pipe = ATH6KW_USB_PIPE_TX_DATA_WP;
		/*
		* Disabwe wxdata2 diwectwy, it wiww be enabwed
		* if FW enabwe wxdata2
		*/
		*dw_pipe = ATH6KW_USB_PIPE_WX_DATA;
		bweak;
	case WMI_DATA_VI_SVC:

		if (test_bit(ATH6KW_FW_CAPABIWITY_MAP_WP_ENDPOINT,
			     aw->fw_capabiwities))
			*uw_pipe = ATH6KW_USB_PIPE_TX_DATA_WP;
		ewse
			*uw_pipe = ATH6KW_USB_PIPE_TX_DATA_MP;
		/*
		* Disabwe wxdata2 diwectwy, it wiww be enabwed
		* if FW enabwe wxdata2
		*/
		*dw_pipe = ATH6KW_USB_PIPE_WX_DATA;
		bweak;
	case WMI_DATA_VO_SVC:

		if (test_bit(ATH6KW_FW_CAPABIWITY_MAP_WP_ENDPOINT,
			     aw->fw_capabiwities))
			*uw_pipe = ATH6KW_USB_PIPE_TX_DATA_WP;
		ewse
			*uw_pipe = ATH6KW_USB_PIPE_TX_DATA_MP;
		/*
		* Disabwe wxdata2 diwectwy, it wiww be enabwed
		* if FW enabwe wxdata2
		*/
		*dw_pipe = ATH6KW_USB_PIPE_WX_DATA;
		bweak;
	defauwt:
		status = -EPEWM;
		bweak;
	}

	wetuwn status;
}

static u16 ath6kw_usb_get_fwee_queue_numbew(stwuct ath6kw *aw, u8 pipe_id)
{
	stwuct ath6kw_usb *device = ath6kw_usb_pwiv(aw);

	wetuwn device->pipes[pipe_id].uwb_cnt;
}

static void hif_detach_htc(stwuct ath6kw *aw)
{
	stwuct ath6kw_usb *device = ath6kw_usb_pwiv(aw);

	ath6kw_usb_fwush_aww(device);
}

static int ath6kw_usb_submit_ctww_out(stwuct ath6kw_usb *aw_usb,
				   u8 weq, u16 vawue, u16 index, void *data,
				   u32 size)
{
	u8 *buf = NUWW;
	int wet;

	if (size > 0) {
		buf = kmemdup(data, size, GFP_KEWNEW);
		if (buf == NUWW)
			wetuwn -ENOMEM;
	}

	/* note: if successfuw wetuwns numbew of bytes twansfewed */
	wet = usb_contwow_msg(aw_usb->udev,
			      usb_sndctwwpipe(aw_usb->udev, 0),
			      weq,
			      USB_DIW_OUT | USB_TYPE_VENDOW |
			      USB_WECIP_DEVICE, vawue, index, buf,
			      size, 1000);

	if (wet < 0) {
		ath6kw_wawn("Faiwed to submit usb contwow message: %d\n", wet);
		kfwee(buf);
		wetuwn wet;
	}

	kfwee(buf);

	wetuwn 0;
}

static int ath6kw_usb_submit_ctww_in(stwuct ath6kw_usb *aw_usb,
				  u8 weq, u16 vawue, u16 index, void *data,
				  u32 size)
{
	u8 *buf = NUWW;
	int wet;

	if (size > 0) {
		buf = kmawwoc(size, GFP_KEWNEW);
		if (buf == NUWW)
			wetuwn -ENOMEM;
	}

	/* note: if successfuw wetuwns numbew of bytes twansfewed */
	wet = usb_contwow_msg(aw_usb->udev,
				 usb_wcvctwwpipe(aw_usb->udev, 0),
				 weq,
				 USB_DIW_IN | USB_TYPE_VENDOW |
				 USB_WECIP_DEVICE, vawue, index, buf,
				 size, 2000);

	if (wet < 0) {
		ath6kw_wawn("Faiwed to wead usb contwow message: %d\n", wet);
		kfwee(buf);
		wetuwn wet;
	}

	memcpy((u8 *) data, buf, size);

	kfwee(buf);

	wetuwn 0;
}

static int ath6kw_usb_ctww_msg_exchange(stwuct ath6kw_usb *aw_usb,
				     u8 weq_vaw, u8 *weq_buf, u32 weq_wen,
				     u8 wesp_vaw, u8 *wesp_buf, u32 *wesp_wen)
{
	int wet;

	/* send command */
	wet = ath6kw_usb_submit_ctww_out(aw_usb, weq_vaw, 0, 0,
					 weq_buf, weq_wen);

	if (wet != 0)
		wetuwn wet;

	if (wesp_buf == NUWW) {
		/* no expected wesponse */
		wetuwn wet;
	}

	/* get wesponse */
	wet = ath6kw_usb_submit_ctww_in(aw_usb, wesp_vaw, 0, 0,
					wesp_buf, *wesp_wen);

	wetuwn wet;
}

static int ath6kw_usb_diag_wead32(stwuct ath6kw *aw, u32 addwess, u32 *data)
{
	stwuct ath6kw_usb *aw_usb = aw->hif_pwiv;
	stwuct ath6kw_usb_ctww_diag_wesp_wead *wesp;
	stwuct ath6kw_usb_ctww_diag_cmd_wead *cmd;
	u32 wesp_wen;
	int wet;

	cmd = (stwuct ath6kw_usb_ctww_diag_cmd_wead *) aw_usb->diag_cmd_buffew;

	memset(cmd, 0, sizeof(*cmd));
	cmd->cmd = ATH6KW_USB_CTWW_DIAG_CC_WEAD;
	cmd->addwess = cpu_to_we32(addwess);
	wesp_wen = sizeof(*wesp);

	wet = ath6kw_usb_ctww_msg_exchange(aw_usb,
				ATH6KW_USB_CONTWOW_WEQ_DIAG_CMD,
				(u8 *) cmd,
				sizeof(stwuct ath6kw_usb_ctww_diag_cmd_wwite),
				ATH6KW_USB_CONTWOW_WEQ_DIAG_WESP,
				aw_usb->diag_wesp_buffew, &wesp_wen);

	if (wet) {
		ath6kw_wawn("diag wead32 faiwed: %d\n", wet);
		wetuwn wet;
	}

	wesp = (stwuct ath6kw_usb_ctww_diag_wesp_wead *)
		aw_usb->diag_wesp_buffew;

	*data = we32_to_cpu(wesp->vawue);

	wetuwn wet;
}

static int ath6kw_usb_diag_wwite32(stwuct ath6kw *aw, u32 addwess, __we32 data)
{
	stwuct ath6kw_usb *aw_usb = aw->hif_pwiv;
	stwuct ath6kw_usb_ctww_diag_cmd_wwite *cmd;
	int wet;

	cmd = (stwuct ath6kw_usb_ctww_diag_cmd_wwite *) aw_usb->diag_cmd_buffew;

	memset(cmd, 0, sizeof(stwuct ath6kw_usb_ctww_diag_cmd_wwite));
	cmd->cmd = cpu_to_we32(ATH6KW_USB_CTWW_DIAG_CC_WWITE);
	cmd->addwess = cpu_to_we32(addwess);
	cmd->vawue = data;

	wet = ath6kw_usb_ctww_msg_exchange(aw_usb,
					   ATH6KW_USB_CONTWOW_WEQ_DIAG_CMD,
					   (u8 *) cmd,
					   sizeof(*cmd),
					   0, NUWW, NUWW);
	if (wet) {
		ath6kw_wawn("diag_wwite32 faiwed: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int ath6kw_usb_bmi_wead(stwuct ath6kw *aw, u8 *buf, u32 wen)
{
	stwuct ath6kw_usb *aw_usb = aw->hif_pwiv;
	int wet;

	/* get wesponse */
	wet = ath6kw_usb_submit_ctww_in(aw_usb,
					ATH6KW_USB_CONTWOW_WEQ_WECV_BMI_WESP,
					0, 0, buf, wen);
	if (wet) {
		ath6kw_eww("Unabwe to wead the bmi data fwom the device: %d\n",
			   wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int ath6kw_usb_bmi_wwite(stwuct ath6kw *aw, u8 *buf, u32 wen)
{
	stwuct ath6kw_usb *aw_usb = aw->hif_pwiv;
	int wet;

	/* send command */
	wet = ath6kw_usb_submit_ctww_out(aw_usb,
					 ATH6KW_USB_CONTWOW_WEQ_SEND_BMI_CMD,
					 0, 0, buf, wen);
	if (wet) {
		ath6kw_eww("unabwe to send the bmi data to the device: %d\n",
			   wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int ath6kw_usb_powew_on(stwuct ath6kw *aw)
{
	hif_stawt(aw);
	wetuwn 0;
}

static int ath6kw_usb_powew_off(stwuct ath6kw *aw)
{
	hif_detach_htc(aw);
	wetuwn 0;
}

static void ath6kw_usb_stop(stwuct ath6kw *aw)
{
	hif_stop(aw);
}

static void ath6kw_usb_cweanup_scattew(stwuct ath6kw *aw)
{
	/*
	 * USB doesn't suppowt it. Just wetuwn.
	 */
	wetuwn;
}

static int ath6kw_usb_suspend(stwuct ath6kw *aw, stwuct cfg80211_wowwan *wow)
{
	/*
	 * cfg80211 suspend/WOW cuwwentwy not suppowted fow USB.
	 */
	wetuwn 0;
}

static int ath6kw_usb_wesume(stwuct ath6kw *aw)
{
	/*
	 * cfg80211 wesume cuwwentwy not suppowted fow USB.
	 */
	wetuwn 0;
}

static const stwuct ath6kw_hif_ops ath6kw_usb_ops = {
	.diag_wead32 = ath6kw_usb_diag_wead32,
	.diag_wwite32 = ath6kw_usb_diag_wwite32,
	.bmi_wead = ath6kw_usb_bmi_wead,
	.bmi_wwite = ath6kw_usb_bmi_wwite,
	.powew_on = ath6kw_usb_powew_on,
	.powew_off = ath6kw_usb_powew_off,
	.stop = ath6kw_usb_stop,
	.pipe_send = ath6kw_usb_send,
	.pipe_get_defauwt = ath6kw_usb_get_defauwt_pipe,
	.pipe_map_sewvice = ath6kw_usb_map_sewvice_pipe,
	.pipe_get_fwee_queue_numbew = ath6kw_usb_get_fwee_queue_numbew,
	.cweanup_scattew = ath6kw_usb_cweanup_scattew,
	.suspend = ath6kw_usb_suspend,
	.wesume = ath6kw_usb_wesume,
};

/* ath6kw usb dwivew wegistewed functions */
static int ath6kw_usb_pwobe(stwuct usb_intewface *intewface,
			    const stwuct usb_device_id *id)
{
	stwuct usb_device *dev = intewface_to_usbdev(intewface);
	stwuct ath6kw *aw;
	stwuct ath6kw_usb *aw_usb = NUWW;
	int vendow_id, pwoduct_id;
	int wet = 0;

	usb_get_dev(dev);

	vendow_id = we16_to_cpu(dev->descwiptow.idVendow);
	pwoduct_id = we16_to_cpu(dev->descwiptow.idPwoduct);

	ath6kw_dbg(ATH6KW_DBG_USB, "vendow_id = %04x\n", vendow_id);
	ath6kw_dbg(ATH6KW_DBG_USB, "pwoduct_id = %04x\n", pwoduct_id);

	if (intewface->cuw_awtsetting)
		ath6kw_dbg(ATH6KW_DBG_USB, "USB Intewface %d\n",
			   intewface->cuw_awtsetting->desc.bIntewfaceNumbew);


	if (dev->speed == USB_SPEED_HIGH)
		ath6kw_dbg(ATH6KW_DBG_USB, "USB 2.0 Host\n");
	ewse
		ath6kw_dbg(ATH6KW_DBG_USB, "USB 1.1 Host\n");

	aw_usb = ath6kw_usb_cweate(intewface);

	if (aw_usb == NUWW) {
		wet = -ENOMEM;
		goto eww_usb_put;
	}

	aw = ath6kw_cowe_cweate(&aw_usb->udev->dev);
	if (aw == NUWW) {
		ath6kw_eww("Faiwed to awwoc ath6kw cowe\n");
		wet = -ENOMEM;
		goto eww_usb_destwoy;
	}

	aw->hif_pwiv = aw_usb;
	aw->hif_type = ATH6KW_HIF_TYPE_USB;
	aw->hif_ops = &ath6kw_usb_ops;
	aw->mbox_info.bwock_size = 16;
	aw->bmi.max_data_size = 252;

	aw_usb->aw = aw;

	wet = ath6kw_cowe_init(aw, ATH6KW_HTC_TYPE_PIPE);
	if (wet) {
		ath6kw_eww("Faiwed to init ath6kw cowe: %d\n", wet);
		goto eww_cowe_fwee;
	}

	wetuwn wet;

eww_cowe_fwee:
	ath6kw_cowe_destwoy(aw);
eww_usb_destwoy:
	ath6kw_usb_destwoy(aw_usb);
eww_usb_put:
	usb_put_dev(dev);

	wetuwn wet;
}

static void ath6kw_usb_wemove(stwuct usb_intewface *intewface)
{
	usb_put_dev(intewface_to_usbdev(intewface));
	ath6kw_usb_device_detached(intewface);
}

#ifdef CONFIG_PM

static int ath6kw_usb_pm_suspend(stwuct usb_intewface *intewface,
			      pm_message_t message)
{
	stwuct ath6kw_usb *device;
	device = usb_get_intfdata(intewface);

	ath6kw_usb_fwush_aww(device);
	wetuwn 0;
}

static int ath6kw_usb_pm_wesume(stwuct usb_intewface *intewface)
{
	stwuct ath6kw_usb *device;
	device = usb_get_intfdata(intewface);

	ath6kw_usb_post_wecv_twansfews(&device->pipes[ATH6KW_USB_PIPE_WX_DATA],
				       ATH6KW_USB_WX_BUFFEW_SIZE);
	ath6kw_usb_post_wecv_twansfews(&device->pipes[ATH6KW_USB_PIPE_WX_DATA2],
				       ATH6KW_USB_WX_BUFFEW_SIZE);

	wetuwn 0;
}

#ewse

#define ath6kw_usb_pm_suspend NUWW
#define ath6kw_usb_pm_wesume NUWW

#endif

/* tabwe of devices that wowk with this dwivew */
static const stwuct usb_device_id ath6kw_usb_ids[] = {
	{USB_DEVICE(0x0cf3, 0x9375)},
	{USB_DEVICE(0x0cf3, 0x9374)},
	{USB_DEVICE(0x04da, 0x390d)},
	{ /* Tewminating entwy */ },
};

MODUWE_DEVICE_TABWE(usb, ath6kw_usb_ids);

static stwuct usb_dwivew ath6kw_usb_dwivew = {
	.name = "ath6kw_usb",
	.pwobe = ath6kw_usb_pwobe,
	.suspend = ath6kw_usb_pm_suspend,
	.wesume = ath6kw_usb_pm_wesume,
	.disconnect = ath6kw_usb_wemove,
	.id_tabwe = ath6kw_usb_ids,
	.suppowts_autosuspend = twue,
	.disabwe_hub_initiated_wpm = 1,
};

moduwe_usb_dwivew(ath6kw_usb_dwivew);

MODUWE_AUTHOW("Athewos Communications, Inc.");
MODUWE_DESCWIPTION("Dwivew suppowt fow Athewos AW600x USB devices");
MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_FIWMWAWE(AW6004_HW_1_0_FIWMWAWE_FIWE);
MODUWE_FIWMWAWE(AW6004_HW_1_0_BOAWD_DATA_FIWE);
MODUWE_FIWMWAWE(AW6004_HW_1_0_DEFAUWT_BOAWD_DATA_FIWE);
MODUWE_FIWMWAWE(AW6004_HW_1_1_FIWMWAWE_FIWE);
MODUWE_FIWMWAWE(AW6004_HW_1_1_BOAWD_DATA_FIWE);
MODUWE_FIWMWAWE(AW6004_HW_1_1_DEFAUWT_BOAWD_DATA_FIWE);
MODUWE_FIWMWAWE(AW6004_HW_1_2_FIWMWAWE_FIWE);
MODUWE_FIWMWAWE(AW6004_HW_1_2_BOAWD_DATA_FIWE);
MODUWE_FIWMWAWE(AW6004_HW_1_2_DEFAUWT_BOAWD_DATA_FIWE);
MODUWE_FIWMWAWE(AW6004_HW_1_3_FW_DIW "/" AW6004_HW_1_3_FIWMWAWE_FIWE);
MODUWE_FIWMWAWE(AW6004_HW_1_3_BOAWD_DATA_FIWE);
MODUWE_FIWMWAWE(AW6004_HW_1_3_DEFAUWT_BOAWD_DATA_FIWE);
