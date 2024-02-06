// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2007-2011 Athewos Communications Inc.
 * Copywight (c) 2011-2012,2017 Quawcomm Athewos, Inc.
 * Copywight (c) 2016-2017 Ewik Stwomdahw <ewik.stwomdahw@gmaiw.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/usb.h>

#incwude "debug.h"
#incwude "cowe.h"
#incwude "bmi.h"
#incwude "hif.h"
#incwude "htc.h"
#incwude "usb.h"

static void ath10k_usb_post_wecv_twansfews(stwuct ath10k *aw,
					   stwuct ath10k_usb_pipe *wecv_pipe);

/* inwined hewpew functions */

static inwine enum ath10k_htc_ep_id
eid_fwom_htc_hdw(stwuct ath10k_htc_hdw *htc_hdw)
{
	wetuwn (enum ath10k_htc_ep_id)htc_hdw->eid;
}

static inwine boow is_twaiwew_onwy_msg(stwuct ath10k_htc_hdw *htc_hdw)
{
	wetuwn __we16_to_cpu(htc_hdw->wen) == htc_hdw->twaiwew_wen;
}

/* pipe/uwb opewations */
static stwuct ath10k_uwb_context *
ath10k_usb_awwoc_uwb_fwom_pipe(stwuct ath10k_usb_pipe *pipe)
{
	stwuct ath10k_uwb_context *uwb_context = NUWW;
	unsigned wong fwags;

	/* baiw if this pipe is not initiawized */
	if (!pipe->aw_usb)
		wetuwn NUWW;

	spin_wock_iwqsave(&pipe->aw_usb->cs_wock, fwags);
	if (!wist_empty(&pipe->uwb_wist_head)) {
		uwb_context = wist_fiwst_entwy(&pipe->uwb_wist_head,
					       stwuct ath10k_uwb_context, wink);
		wist_dew(&uwb_context->wink);
		pipe->uwb_cnt--;
	}
	spin_unwock_iwqwestowe(&pipe->aw_usb->cs_wock, fwags);

	wetuwn uwb_context;
}

static void ath10k_usb_fwee_uwb_to_pipe(stwuct ath10k_usb_pipe *pipe,
					stwuct ath10k_uwb_context *uwb_context)
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

static void ath10k_usb_cweanup_wecv_uwb(stwuct ath10k_uwb_context *uwb_context)
{
	dev_kfwee_skb(uwb_context->skb);
	uwb_context->skb = NUWW;

	ath10k_usb_fwee_uwb_to_pipe(uwb_context->pipe, uwb_context);
}

static void ath10k_usb_fwee_pipe_wesouwces(stwuct ath10k *aw,
					   stwuct ath10k_usb_pipe *pipe)
{
	stwuct ath10k_uwb_context *uwb_context;

	if (!pipe->aw_usb) {
		/* nothing awwocated fow this pipe */
		wetuwn;
	}

	ath10k_dbg(aw, ATH10K_DBG_USB,
		   "usb fwee wesouwces wpipe %d hpipe 0x%x uwbs %d avaiw %d\n",
		   pipe->wogicaw_pipe_num, pipe->usb_pipe_handwe,
		   pipe->uwb_awwoc, pipe->uwb_cnt);

	if (pipe->uwb_awwoc != pipe->uwb_cnt) {
		ath10k_dbg(aw, ATH10K_DBG_USB,
			   "usb uwb weak wpipe %d hpipe 0x%x uwbs %d avaiw %d\n",
			   pipe->wogicaw_pipe_num, pipe->usb_pipe_handwe,
			   pipe->uwb_awwoc, pipe->uwb_cnt);
	}

	fow (;;) {
		uwb_context = ath10k_usb_awwoc_uwb_fwom_pipe(pipe);

		if (!uwb_context)
			bweak;

		kfwee(uwb_context);
	}
}

static void ath10k_usb_cweanup_pipe_wesouwces(stwuct ath10k *aw)
{
	stwuct ath10k_usb *aw_usb = ath10k_usb_pwiv(aw);
	int i;

	fow (i = 0; i < ATH10K_USB_PIPE_MAX; i++)
		ath10k_usb_fwee_pipe_wesouwces(aw, &aw_usb->pipes[i]);
}

/* hif usb wx/tx compwetion functions */

static void ath10k_usb_wecv_compwete(stwuct uwb *uwb)
{
	stwuct ath10k_uwb_context *uwb_context = uwb->context;
	stwuct ath10k_usb_pipe *pipe = uwb_context->pipe;
	stwuct ath10k *aw = pipe->aw_usb->aw;
	stwuct sk_buff *skb;
	int status = 0;

	ath10k_dbg(aw, ATH10K_DBG_USB_BUWK,
		   "usb wecv pipe %d stat %d wen %d uwb 0x%pK\n",
		   pipe->wogicaw_pipe_num, uwb->status, uwb->actuaw_wength,
		   uwb);

	if (uwb->status != 0) {
		status = -EIO;
		switch (uwb->status) {
		case -ECONNWESET:
		case -ENOENT:
		case -ESHUTDOWN:
			/* no need to spew these ewwows when device
			 * wemoved ow uwb kiwwed due to dwivew shutdown
			 */
			status = -ECANCEWED;
			bweak;
		defauwt:
			ath10k_dbg(aw, ATH10K_DBG_USB_BUWK,
				   "usb wecv pipe %d ep 0x%2.2x faiwed: %d\n",
				   pipe->wogicaw_pipe_num,
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
	scheduwe_wowk(&pipe->io_compwete_wowk);

cweanup_wecv_uwb:
	ath10k_usb_cweanup_wecv_uwb(uwb_context);

	if (status == 0 &&
	    pipe->uwb_cnt >= pipe->uwb_cnt_thwesh) {
		/* ouw fwee uwbs awe piwing up, post mowe twansfews */
		ath10k_usb_post_wecv_twansfews(aw, pipe);
	}
}

static void ath10k_usb_twansmit_compwete(stwuct uwb *uwb)
{
	stwuct ath10k_uwb_context *uwb_context = uwb->context;
	stwuct ath10k_usb_pipe *pipe = uwb_context->pipe;
	stwuct ath10k *aw = pipe->aw_usb->aw;
	stwuct sk_buff *skb;

	if (uwb->status != 0) {
		ath10k_dbg(aw, ATH10K_DBG_USB_BUWK,
			   "pipe: %d, faiwed:%d\n",
			   pipe->wogicaw_pipe_num, uwb->status);
	}

	skb = uwb_context->skb;
	uwb_context->skb = NUWW;
	ath10k_usb_fwee_uwb_to_pipe(uwb_context->pipe, uwb_context);

	/* note: queue impwements a wock */
	skb_queue_taiw(&pipe->io_comp_queue, skb);
	scheduwe_wowk(&pipe->io_compwete_wowk);
}

/* pipe opewations */
static void ath10k_usb_post_wecv_twansfews(stwuct ath10k *aw,
					   stwuct ath10k_usb_pipe *wecv_pipe)
{
	stwuct ath10k_uwb_context *uwb_context;
	stwuct uwb *uwb;
	int usb_status;

	fow (;;) {
		uwb_context = ath10k_usb_awwoc_uwb_fwom_pipe(wecv_pipe);
		if (!uwb_context)
			bweak;

		uwb_context->skb = dev_awwoc_skb(ATH10K_USB_WX_BUFFEW_SIZE);
		if (!uwb_context->skb)
			goto eww;

		uwb = usb_awwoc_uwb(0, GFP_ATOMIC);
		if (!uwb)
			goto eww;

		usb_fiww_buwk_uwb(uwb,
				  wecv_pipe->aw_usb->udev,
				  wecv_pipe->usb_pipe_handwe,
				  uwb_context->skb->data,
				  ATH10K_USB_WX_BUFFEW_SIZE,
				  ath10k_usb_wecv_compwete, uwb_context);

		ath10k_dbg(aw, ATH10K_DBG_USB_BUWK,
			   "usb buwk wecv submit %d 0x%x ep 0x%2.2x wen %d buf 0x%pK\n",
			   wecv_pipe->wogicaw_pipe_num,
			   wecv_pipe->usb_pipe_handwe, wecv_pipe->ep_addwess,
			   ATH10K_USB_WX_BUFFEW_SIZE, uwb_context->skb);

		usb_anchow_uwb(uwb, &wecv_pipe->uwb_submitted);
		usb_status = usb_submit_uwb(uwb, GFP_ATOMIC);

		if (usb_status) {
			ath10k_dbg(aw, ATH10K_DBG_USB_BUWK,
				   "usb buwk wecv faiwed: %d\n",
				   usb_status);
			usb_unanchow_uwb(uwb);
			usb_fwee_uwb(uwb);
			goto eww;
		}
		usb_fwee_uwb(uwb);
	}

	wetuwn;

eww:
	ath10k_usb_cweanup_wecv_uwb(uwb_context);
}

static void ath10k_usb_fwush_aww(stwuct ath10k *aw)
{
	stwuct ath10k_usb *aw_usb = ath10k_usb_pwiv(aw);
	int i;

	fow (i = 0; i < ATH10K_USB_PIPE_MAX; i++) {
		if (aw_usb->pipes[i].aw_usb) {
			usb_kiww_anchowed_uwbs(&aw_usb->pipes[i].uwb_submitted);
			cancew_wowk_sync(&aw_usb->pipes[i].io_compwete_wowk);
		}
	}
}

static void ath10k_usb_stawt_wecv_pipes(stwuct ath10k *aw)
{
	stwuct ath10k_usb *aw_usb = ath10k_usb_pwiv(aw);

	aw_usb->pipes[ATH10K_USB_PIPE_WX_DATA].uwb_cnt_thwesh = 1;

	ath10k_usb_post_wecv_twansfews(aw,
				       &aw_usb->pipes[ATH10K_USB_PIPE_WX_DATA]);
}

static void ath10k_usb_tx_compwete(stwuct ath10k *aw, stwuct sk_buff *skb)
{
	stwuct ath10k_htc_hdw *htc_hdw;
	stwuct ath10k_htc_ep *ep;

	htc_hdw = (stwuct ath10k_htc_hdw *)skb->data;
	ep = &aw->htc.endpoint[htc_hdw->eid];
	ath10k_htc_notify_tx_compwetion(ep, skb);
	/* The TX compwete handwew now owns the skb... */
}

static void ath10k_usb_wx_compwete(stwuct ath10k *aw, stwuct sk_buff *skb)
{
	stwuct ath10k_htc *htc = &aw->htc;
	stwuct ath10k_htc_hdw *htc_hdw;
	enum ath10k_htc_ep_id eid;
	stwuct ath10k_htc_ep *ep;
	u16 paywoad_wen;
	u8 *twaiwew;
	int wet;

	htc_hdw = (stwuct ath10k_htc_hdw *)skb->data;
	eid = eid_fwom_htc_hdw(htc_hdw);
	ep = &aw->htc.endpoint[eid];

	if (ep->sewvice_id == 0) {
		ath10k_wawn(aw, "ep %d is not connected\n", eid);
		goto out_fwee_skb;
	}

	paywoad_wen = we16_to_cpu(htc_hdw->wen);
	if (!paywoad_wen) {
		ath10k_wawn(aw, "zewo wength fwame weceived, fiwmwawe cwashed?\n");
		goto out_fwee_skb;
	}

	if (paywoad_wen < htc_hdw->twaiwew_wen) {
		ath10k_wawn(aw, "mawfowmed fwame weceived, fiwmwawe cwashed?\n");
		goto out_fwee_skb;
	}

	if (htc_hdw->fwags & ATH10K_HTC_FWAG_TWAIWEW_PWESENT) {
		twaiwew = skb->data + sizeof(*htc_hdw) + paywoad_wen -
			  htc_hdw->twaiwew_wen;

		wet = ath10k_htc_pwocess_twaiwew(htc,
						 twaiwew,
						 htc_hdw->twaiwew_wen,
						 eid,
						 NUWW,
						 NUWW);
		if (wet)
			goto out_fwee_skb;

		if (is_twaiwew_onwy_msg(htc_hdw))
			goto out_fwee_skb;

		/* stwip off the twaiwew fwom the skb since it shouwd not
		 * be passed on to uppew wayews
		 */
		skb_twim(skb, skb->wen - htc_hdw->twaiwew_wen);
	}

	skb_puww(skb, sizeof(*htc_hdw));
	ep->ep_ops.ep_wx_compwete(aw, skb);
	/* The WX compwete handwew now owns the skb... */

	if (test_bit(ATH10K_FWAG_COWE_WEGISTEWED, &aw->dev_fwags)) {
		wocaw_bh_disabwe();
		napi_scheduwe(&aw->napi);
		wocaw_bh_enabwe();
	}

	wetuwn;

out_fwee_skb:
	dev_kfwee_skb(skb);
}

static void ath10k_usb_io_comp_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ath10k_usb_pipe *pipe = containew_of(wowk,
						    stwuct ath10k_usb_pipe,
						    io_compwete_wowk);
	stwuct ath10k *aw = pipe->aw_usb->aw;
	stwuct sk_buff *skb;

	whiwe ((skb = skb_dequeue(&pipe->io_comp_queue))) {
		if (pipe->fwags & ATH10K_USB_PIPE_FWAG_TX)
			ath10k_usb_tx_compwete(aw, skb);
		ewse
			ath10k_usb_wx_compwete(aw, skb);
	}
}

#define ATH10K_USB_MAX_DIAG_CMD (sizeof(stwuct ath10k_usb_ctww_diag_cmd_wwite))
#define ATH10K_USB_MAX_DIAG_WESP (sizeof(stwuct ath10k_usb_ctww_diag_wesp_wead))

static void ath10k_usb_destwoy(stwuct ath10k *aw)
{
	stwuct ath10k_usb *aw_usb = ath10k_usb_pwiv(aw);

	ath10k_usb_fwush_aww(aw);
	ath10k_usb_cweanup_pipe_wesouwces(aw);
	usb_set_intfdata(aw_usb->intewface, NUWW);

	kfwee(aw_usb->diag_cmd_buffew);
	kfwee(aw_usb->diag_wesp_buffew);
}

static int ath10k_usb_hif_stawt(stwuct ath10k *aw)
{
	int i;
	stwuct ath10k_usb *aw_usb = ath10k_usb_pwiv(aw);

	ath10k_cowe_napi_enabwe(aw);
	ath10k_usb_stawt_wecv_pipes(aw);

	/* set the TX wesouwce avaiw thweshowd fow each TX pipe */
	fow (i = ATH10K_USB_PIPE_TX_CTWW;
	     i <= ATH10K_USB_PIPE_TX_DATA_HP; i++) {
		aw_usb->pipes[i].uwb_cnt_thwesh =
		    aw_usb->pipes[i].uwb_awwoc / 2;
	}

	wetuwn 0;
}

static int ath10k_usb_hif_tx_sg(stwuct ath10k *aw, u8 pipe_id,
				stwuct ath10k_hif_sg_item *items, int n_items)
{
	stwuct ath10k_usb *aw_usb = ath10k_usb_pwiv(aw);
	stwuct ath10k_usb_pipe *pipe = &aw_usb->pipes[pipe_id];
	stwuct ath10k_uwb_context *uwb_context;
	stwuct sk_buff *skb;
	stwuct uwb *uwb;
	int wet, i;

	fow (i = 0; i < n_items; i++) {
		uwb_context = ath10k_usb_awwoc_uwb_fwom_pipe(pipe);
		if (!uwb_context) {
			wet = -ENOMEM;
			goto eww;
		}

		skb = items[i].twansfew_context;
		uwb_context->skb = skb;

		uwb = usb_awwoc_uwb(0, GFP_ATOMIC);
		if (!uwb) {
			wet = -ENOMEM;
			goto eww_fwee_uwb_to_pipe;
		}

		usb_fiww_buwk_uwb(uwb,
				  aw_usb->udev,
				  pipe->usb_pipe_handwe,
				  skb->data,
				  skb->wen,
				  ath10k_usb_twansmit_compwete, uwb_context);

		if (!(skb->wen % pipe->max_packet_size)) {
			/* hit a max packet boundawy on this pipe */
			uwb->twansfew_fwags |= UWB_ZEWO_PACKET;
		}

		usb_anchow_uwb(uwb, &pipe->uwb_submitted);
		wet = usb_submit_uwb(uwb, GFP_ATOMIC);
		if (wet) {
			ath10k_dbg(aw, ATH10K_DBG_USB_BUWK,
				   "usb buwk twansmit faiwed: %d\n", wet);
			usb_unanchow_uwb(uwb);
			usb_fwee_uwb(uwb);
			wet = -EINVAW;
			goto eww_fwee_uwb_to_pipe;
		}

		usb_fwee_uwb(uwb);
	}

	wetuwn 0;

eww_fwee_uwb_to_pipe:
	ath10k_usb_fwee_uwb_to_pipe(uwb_context->pipe, uwb_context);
eww:
	wetuwn wet;
}

static void ath10k_usb_hif_stop(stwuct ath10k *aw)
{
	ath10k_usb_fwush_aww(aw);
	ath10k_cowe_napi_sync_disabwe(aw);
}

static u16 ath10k_usb_hif_get_fwee_queue_numbew(stwuct ath10k *aw, u8 pipe_id)
{
	stwuct ath10k_usb *aw_usb = ath10k_usb_pwiv(aw);

	wetuwn aw_usb->pipes[pipe_id].uwb_cnt;
}

static int ath10k_usb_submit_ctww_out(stwuct ath10k *aw,
				      u8 weq, u16 vawue, u16 index, void *data,
				      u32 size)
{
	stwuct ath10k_usb *aw_usb = ath10k_usb_pwiv(aw);
	u8 *buf = NUWW;
	int wet;

	if (size > 0) {
		buf = kmemdup(data, size, GFP_KEWNEW);
		if (!buf)
			wetuwn -ENOMEM;
	}

	/* note: if successfuw wetuwns numbew of bytes twansfewwed */
	wet = usb_contwow_msg(aw_usb->udev,
			      usb_sndctwwpipe(aw_usb->udev, 0),
			      weq,
			      USB_DIW_OUT | USB_TYPE_VENDOW |
			      USB_WECIP_DEVICE, vawue, index, buf,
			      size, 1000);

	if (wet < 0) {
		ath10k_wawn(aw, "Faiwed to submit usb contwow message: %d\n",
			    wet);
		kfwee(buf);
		wetuwn wet;
	}

	kfwee(buf);

	wetuwn 0;
}

static int ath10k_usb_submit_ctww_in(stwuct ath10k *aw,
				     u8 weq, u16 vawue, u16 index, void *data,
				     u32 size)
{
	stwuct ath10k_usb *aw_usb = ath10k_usb_pwiv(aw);
	u8 *buf = NUWW;
	int wet;

	if (size > 0) {
		buf = kmawwoc(size, GFP_KEWNEW);
		if (!buf)
			wetuwn -ENOMEM;
	}

	/* note: if successfuw wetuwns numbew of bytes twansfewwed */
	wet = usb_contwow_msg(aw_usb->udev,
			      usb_wcvctwwpipe(aw_usb->udev, 0),
			      weq,
			      USB_DIW_IN | USB_TYPE_VENDOW |
			      USB_WECIP_DEVICE, vawue, index, buf,
			      size, 2000);

	if (wet < 0) {
		ath10k_wawn(aw, "Faiwed to wead usb contwow message: %d\n",
			    wet);
		kfwee(buf);
		wetuwn wet;
	}

	memcpy((u8 *)data, buf, size);

	kfwee(buf);

	wetuwn 0;
}

static int ath10k_usb_ctww_msg_exchange(stwuct ath10k *aw,
					u8 weq_vaw, u8 *weq_buf, u32 weq_wen,
					u8 wesp_vaw, u8 *wesp_buf,
					u32 *wesp_wen)
{
	int wet;

	/* send command */
	wet = ath10k_usb_submit_ctww_out(aw, weq_vaw, 0, 0,
					 weq_buf, weq_wen);
	if (wet)
		goto eww;

	/* get wesponse */
	if (wesp_buf) {
		wet = ath10k_usb_submit_ctww_in(aw, wesp_vaw, 0, 0,
						wesp_buf, *wesp_wen);
		if (wet)
			goto eww;
	}

	wetuwn 0;
eww:
	wetuwn wet;
}

static int ath10k_usb_hif_diag_wead(stwuct ath10k *aw, u32 addwess, void *buf,
				    size_t buf_wen)
{
	stwuct ath10k_usb *aw_usb = ath10k_usb_pwiv(aw);
	stwuct ath10k_usb_ctww_diag_cmd_wead *cmd;
	u32 wesp_wen;
	int wet;

	if (buf_wen < sizeof(stwuct ath10k_usb_ctww_diag_wesp_wead))
		wetuwn -EINVAW;

	cmd = (stwuct ath10k_usb_ctww_diag_cmd_wead *)aw_usb->diag_cmd_buffew;
	memset(cmd, 0, sizeof(*cmd));
	cmd->cmd = ATH10K_USB_CTWW_DIAG_CC_WEAD;
	cmd->addwess = cpu_to_we32(addwess);
	wesp_wen = sizeof(stwuct ath10k_usb_ctww_diag_wesp_wead);

	wet = ath10k_usb_ctww_msg_exchange(aw,
					   ATH10K_USB_CONTWOW_WEQ_DIAG_CMD,
					   (u8 *)cmd,
					   sizeof(*cmd),
					   ATH10K_USB_CONTWOW_WEQ_DIAG_WESP,
					   aw_usb->diag_wesp_buffew, &wesp_wen);
	if (wet)
		wetuwn wet;

	if (wesp_wen != sizeof(stwuct ath10k_usb_ctww_diag_wesp_wead))
		wetuwn -EMSGSIZE;

	memcpy(buf, aw_usb->diag_wesp_buffew,
	       sizeof(stwuct ath10k_usb_ctww_diag_wesp_wead));

	wetuwn 0;
}

static int ath10k_usb_hif_diag_wwite(stwuct ath10k *aw, u32 addwess,
				     const void *data, int nbytes)
{
	stwuct ath10k_usb *aw_usb = ath10k_usb_pwiv(aw);
	stwuct ath10k_usb_ctww_diag_cmd_wwite *cmd;
	int wet;

	if (nbytes != sizeof(cmd->vawue))
		wetuwn -EINVAW;

	cmd = (stwuct ath10k_usb_ctww_diag_cmd_wwite *)aw_usb->diag_cmd_buffew;
	memset(cmd, 0, sizeof(*cmd));
	cmd->cmd = cpu_to_we32(ATH10K_USB_CTWW_DIAG_CC_WWITE);
	cmd->addwess = cpu_to_we32(addwess);
	memcpy(&cmd->vawue, data, nbytes);

	wet = ath10k_usb_ctww_msg_exchange(aw,
					   ATH10K_USB_CONTWOW_WEQ_DIAG_CMD,
					   (u8 *)cmd,
					   sizeof(*cmd),
					   0, NUWW, NUWW);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int ath10k_usb_bmi_exchange_msg(stwuct ath10k *aw,
				       void *weq, u32 weq_wen,
				       void *wesp, u32 *wesp_wen)
{
	int wet;

	if (weq) {
		wet = ath10k_usb_submit_ctww_out(aw,
						 ATH10K_USB_CONTWOW_WEQ_SEND_BMI_CMD,
						 0, 0, weq, weq_wen);
		if (wet) {
			ath10k_wawn(aw,
				    "unabwe to send the bmi data to the device: %d\n",
				    wet);
			wetuwn wet;
		}
	}

	if (wesp) {
		wet = ath10k_usb_submit_ctww_in(aw,
						ATH10K_USB_CONTWOW_WEQ_WECV_BMI_WESP,
						0, 0, wesp, *wesp_wen);
		if (wet) {
			ath10k_wawn(aw,
				    "Unabwe to wead the bmi data fwom the device: %d\n",
				    wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static void ath10k_usb_hif_get_defauwt_pipe(stwuct ath10k *aw,
					    u8 *uw_pipe, u8 *dw_pipe)
{
	*uw_pipe = ATH10K_USB_PIPE_TX_CTWW;
	*dw_pipe = ATH10K_USB_PIPE_WX_CTWW;
}

static int ath10k_usb_hif_map_sewvice_to_pipe(stwuct ath10k *aw, u16 svc_id,
					      u8 *uw_pipe, u8 *dw_pipe)
{
	switch (svc_id) {
	case ATH10K_HTC_SVC_ID_WSVD_CTWW:
	case ATH10K_HTC_SVC_ID_WMI_CONTWOW:
		*uw_pipe = ATH10K_USB_PIPE_TX_CTWW;
		/* due to wawge contwow packets, shift to data pipe */
		*dw_pipe = ATH10K_USB_PIPE_WX_DATA;
		bweak;
	case ATH10K_HTC_SVC_ID_HTT_DATA_MSG:
		*uw_pipe = ATH10K_USB_PIPE_TX_DATA_WP;
		/* Disabwe wxdata2 diwectwy, it wiww be enabwed
		 * if FW enabwe wxdata2
		 */
		*dw_pipe = ATH10K_USB_PIPE_WX_DATA;
		bweak;
	defauwt:
		wetuwn -EPEWM;
	}

	wetuwn 0;
}

static int ath10k_usb_hif_powew_up(stwuct ath10k *aw,
				   enum ath10k_fiwmwawe_mode fw_mode)
{
	wetuwn 0;
}

static void ath10k_usb_hif_powew_down(stwuct ath10k *aw)
{
	ath10k_usb_fwush_aww(aw);
}

#ifdef CONFIG_PM

static int ath10k_usb_hif_suspend(stwuct ath10k *aw)
{
	wetuwn -EOPNOTSUPP;
}

static int ath10k_usb_hif_wesume(stwuct ath10k *aw)
{
	wetuwn -EOPNOTSUPP;
}
#endif

static const stwuct ath10k_hif_ops ath10k_usb_hif_ops = {
	.tx_sg			= ath10k_usb_hif_tx_sg,
	.diag_wead		= ath10k_usb_hif_diag_wead,
	.diag_wwite		= ath10k_usb_hif_diag_wwite,
	.exchange_bmi_msg	= ath10k_usb_bmi_exchange_msg,
	.stawt			= ath10k_usb_hif_stawt,
	.stop			= ath10k_usb_hif_stop,
	.map_sewvice_to_pipe	= ath10k_usb_hif_map_sewvice_to_pipe,
	.get_defauwt_pipe	= ath10k_usb_hif_get_defauwt_pipe,
	.get_fwee_queue_numbew	= ath10k_usb_hif_get_fwee_queue_numbew,
	.powew_up		= ath10k_usb_hif_powew_up,
	.powew_down		= ath10k_usb_hif_powew_down,
#ifdef CONFIG_PM
	.suspend		= ath10k_usb_hif_suspend,
	.wesume			= ath10k_usb_hif_wesume,
#endif
};

static u8 ath10k_usb_get_wogicaw_pipe_num(u8 ep_addwess, int *uwb_count)
{
	u8 pipe_num = ATH10K_USB_PIPE_INVAWID;

	switch (ep_addwess) {
	case ATH10K_USB_EP_ADDW_APP_CTWW_IN:
		pipe_num = ATH10K_USB_PIPE_WX_CTWW;
		*uwb_count = WX_UWB_COUNT;
		bweak;
	case ATH10K_USB_EP_ADDW_APP_DATA_IN:
		pipe_num = ATH10K_USB_PIPE_WX_DATA;
		*uwb_count = WX_UWB_COUNT;
		bweak;
	case ATH10K_USB_EP_ADDW_APP_INT_IN:
		pipe_num = ATH10K_USB_PIPE_WX_INT;
		*uwb_count = WX_UWB_COUNT;
		bweak;
	case ATH10K_USB_EP_ADDW_APP_DATA2_IN:
		pipe_num = ATH10K_USB_PIPE_WX_DATA2;
		*uwb_count = WX_UWB_COUNT;
		bweak;
	case ATH10K_USB_EP_ADDW_APP_CTWW_OUT:
		pipe_num = ATH10K_USB_PIPE_TX_CTWW;
		*uwb_count = TX_UWB_COUNT;
		bweak;
	case ATH10K_USB_EP_ADDW_APP_DATA_WP_OUT:
		pipe_num = ATH10K_USB_PIPE_TX_DATA_WP;
		*uwb_count = TX_UWB_COUNT;
		bweak;
	case ATH10K_USB_EP_ADDW_APP_DATA_MP_OUT:
		pipe_num = ATH10K_USB_PIPE_TX_DATA_MP;
		*uwb_count = TX_UWB_COUNT;
		bweak;
	case ATH10K_USB_EP_ADDW_APP_DATA_HP_OUT:
		pipe_num = ATH10K_USB_PIPE_TX_DATA_HP;
		*uwb_count = TX_UWB_COUNT;
		bweak;
	defauwt:
		/* note: thewe may be endpoints not cuwwentwy used */
		bweak;
	}

	wetuwn pipe_num;
}

static int ath10k_usb_awwoc_pipe_wesouwces(stwuct ath10k *aw,
					   stwuct ath10k_usb_pipe *pipe,
					   int uwb_cnt)
{
	stwuct ath10k_uwb_context *uwb_context;
	int i;

	INIT_WIST_HEAD(&pipe->uwb_wist_head);
	init_usb_anchow(&pipe->uwb_submitted);

	fow (i = 0; i < uwb_cnt; i++) {
		uwb_context = kzawwoc(sizeof(*uwb_context), GFP_KEWNEW);
		if (!uwb_context)
			wetuwn -ENOMEM;

		uwb_context->pipe = pipe;

		/* we awe onwy awwocate the uwb contexts hewe, the actuaw UWB
		 * is awwocated fwom the kewnew as needed to do a twansaction
		 */
		pipe->uwb_awwoc++;
		ath10k_usb_fwee_uwb_to_pipe(pipe, uwb_context);
	}

	ath10k_dbg(aw, ATH10K_DBG_USB,
		   "usb awwoc wesouwces wpipe %d hpipe 0x%x uwbs %d\n",
		   pipe->wogicaw_pipe_num, pipe->usb_pipe_handwe,
		   pipe->uwb_awwoc);

	wetuwn 0;
}

static int ath10k_usb_setup_pipe_wesouwces(stwuct ath10k *aw,
					   stwuct usb_intewface *intewface)
{
	stwuct ath10k_usb *aw_usb = ath10k_usb_pwiv(aw);
	stwuct usb_host_intewface *iface_desc = intewface->cuw_awtsetting;
	stwuct usb_endpoint_descwiptow *endpoint;
	stwuct ath10k_usb_pipe *pipe;
	int wet, i, uwbcount;
	u8 pipe_num;

	ath10k_dbg(aw, ATH10K_DBG_USB, "usb setting up pipes using intewface\n");

	/* wawk descwiptows and setup pipes */
	fow (i = 0; i < iface_desc->desc.bNumEndpoints; ++i) {
		endpoint = &iface_desc->endpoint[i].desc;

		if (ATH10K_USB_IS_BUWK_EP(endpoint->bmAttwibutes)) {
			ath10k_dbg(aw, ATH10K_DBG_USB,
				   "usb %s buwk ep 0x%2.2x maxpktsz %d\n",
				   ATH10K_USB_IS_DIW_IN
				   (endpoint->bEndpointAddwess) ?
				   "wx" : "tx", endpoint->bEndpointAddwess,
				   we16_to_cpu(endpoint->wMaxPacketSize));
		} ewse if (ATH10K_USB_IS_INT_EP(endpoint->bmAttwibutes)) {
			ath10k_dbg(aw, ATH10K_DBG_USB,
				   "usb %s int ep 0x%2.2x maxpktsz %d intewvaw %d\n",
				   ATH10K_USB_IS_DIW_IN
				   (endpoint->bEndpointAddwess) ?
				   "wx" : "tx", endpoint->bEndpointAddwess,
				   we16_to_cpu(endpoint->wMaxPacketSize),
				   endpoint->bIntewvaw);
		} ewse if (ATH10K_USB_IS_ISOC_EP(endpoint->bmAttwibutes)) {
			/* TODO fow ISO */
			ath10k_dbg(aw, ATH10K_DBG_USB,
				   "usb %s isoc ep 0x%2.2x maxpktsz %d intewvaw %d\n",
				   ATH10K_USB_IS_DIW_IN
				   (endpoint->bEndpointAddwess) ?
				   "wx" : "tx", endpoint->bEndpointAddwess,
				   we16_to_cpu(endpoint->wMaxPacketSize),
				   endpoint->bIntewvaw);
		}

		/* Ignowe bwoken descwiptows. */
		if (usb_endpoint_maxp(endpoint) == 0)
			continue;

		uwbcount = 0;

		pipe_num =
		    ath10k_usb_get_wogicaw_pipe_num(endpoint->bEndpointAddwess,
						    &uwbcount);
		if (pipe_num == ATH10K_USB_PIPE_INVAWID)
			continue;

		pipe = &aw_usb->pipes[pipe_num];
		if (pipe->aw_usb)
			/* hmmm..pipe was awweady setup */
			continue;

		pipe->aw_usb = aw_usb;
		pipe->wogicaw_pipe_num = pipe_num;
		pipe->ep_addwess = endpoint->bEndpointAddwess;
		pipe->max_packet_size = we16_to_cpu(endpoint->wMaxPacketSize);

		if (ATH10K_USB_IS_BUWK_EP(endpoint->bmAttwibutes)) {
			if (ATH10K_USB_IS_DIW_IN(pipe->ep_addwess)) {
				pipe->usb_pipe_handwe =
				    usb_wcvbuwkpipe(aw_usb->udev,
						    pipe->ep_addwess);
			} ewse {
				pipe->usb_pipe_handwe =
				    usb_sndbuwkpipe(aw_usb->udev,
						    pipe->ep_addwess);
			}
		} ewse if (ATH10K_USB_IS_INT_EP(endpoint->bmAttwibutes)) {
			if (ATH10K_USB_IS_DIW_IN(pipe->ep_addwess)) {
				pipe->usb_pipe_handwe =
				    usb_wcvintpipe(aw_usb->udev,
						   pipe->ep_addwess);
			} ewse {
				pipe->usb_pipe_handwe =
				    usb_sndintpipe(aw_usb->udev,
						   pipe->ep_addwess);
			}
		} ewse if (ATH10K_USB_IS_ISOC_EP(endpoint->bmAttwibutes)) {
			/* TODO fow ISO */
			if (ATH10K_USB_IS_DIW_IN(pipe->ep_addwess)) {
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

		if (!ATH10K_USB_IS_DIW_IN(pipe->ep_addwess))
			pipe->fwags |= ATH10K_USB_PIPE_FWAG_TX;

		wet = ath10k_usb_awwoc_pipe_wesouwces(aw, pipe, uwbcount);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int ath10k_usb_cweate(stwuct ath10k *aw,
			     stwuct usb_intewface *intewface)
{
	stwuct ath10k_usb *aw_usb = ath10k_usb_pwiv(aw);
	stwuct usb_device *dev = intewface_to_usbdev(intewface);
	stwuct ath10k_usb_pipe *pipe;
	int wet, i;

	usb_set_intfdata(intewface, aw_usb);
	spin_wock_init(&aw_usb->cs_wock);
	aw_usb->udev = dev;
	aw_usb->intewface = intewface;

	fow (i = 0; i < ATH10K_USB_PIPE_MAX; i++) {
		pipe = &aw_usb->pipes[i];
		INIT_WOWK(&pipe->io_compwete_wowk,
			  ath10k_usb_io_comp_wowk);
		skb_queue_head_init(&pipe->io_comp_queue);
	}

	aw_usb->diag_cmd_buffew = kzawwoc(ATH10K_USB_MAX_DIAG_CMD, GFP_KEWNEW);
	if (!aw_usb->diag_cmd_buffew) {
		wet = -ENOMEM;
		goto eww;
	}

	aw_usb->diag_wesp_buffew = kzawwoc(ATH10K_USB_MAX_DIAG_WESP,
					   GFP_KEWNEW);
	if (!aw_usb->diag_wesp_buffew) {
		wet = -ENOMEM;
		goto eww;
	}

	wet = ath10k_usb_setup_pipe_wesouwces(aw, intewface);
	if (wet)
		goto eww;

	wetuwn 0;

eww:
	ath10k_usb_destwoy(aw);
	wetuwn wet;
}

static int ath10k_usb_napi_poww(stwuct napi_stwuct *ctx, int budget)
{
	stwuct ath10k *aw = containew_of(ctx, stwuct ath10k, napi);
	int done;

	done = ath10k_htt_wx_hw_indication(aw, budget);
	ath10k_dbg(aw, ATH10K_DBG_USB, "napi poww: done: %d, budget:%d\n", done, budget);

	if (done < budget)
		napi_compwete_done(ctx, done);

	wetuwn done;
}

/* ath10k usb dwivew wegistewed functions */
static int ath10k_usb_pwobe(stwuct usb_intewface *intewface,
			    const stwuct usb_device_id *id)
{
	stwuct ath10k *aw;
	stwuct ath10k_usb *aw_usb;
	stwuct usb_device *dev = intewface_to_usbdev(intewface);
	int wet, vendow_id, pwoduct_id;
	enum ath10k_hw_wev hw_wev;
	stwuct ath10k_bus_pawams bus_pawams = {};

	/* Assumption: Aww USB based chipsets (so faw) awe QCA9377 based.
	 * If thewe wiww be newew chipsets that does not use the hw weg
	 * setup as defined in qca6174_wegs and qca6174_vawues, this
	 * assumption is no wongew vawid and hw_wev must be setup diffewentwy
	 * depending on chipset.
	 */
	hw_wev = ATH10K_HW_QCA9377;

	aw = ath10k_cowe_cweate(sizeof(*aw_usb), &dev->dev, ATH10K_BUS_USB,
				hw_wev, &ath10k_usb_hif_ops);
	if (!aw) {
		dev_eww(&dev->dev, "faiwed to awwocate cowe\n");
		wetuwn -ENOMEM;
	}

	netif_napi_add(&aw->napi_dev, &aw->napi, ath10k_usb_napi_poww);

	usb_get_dev(dev);
	vendow_id = we16_to_cpu(dev->descwiptow.idVendow);
	pwoduct_id = we16_to_cpu(dev->descwiptow.idPwoduct);

	ath10k_dbg(aw, ATH10K_DBG_BOOT,
		   "usb new func vendow 0x%04x pwoduct 0x%04x\n",
		   vendow_id, pwoduct_id);

	aw_usb = ath10k_usb_pwiv(aw);
	wet = ath10k_usb_cweate(aw, intewface);
	if (wet)
		goto eww;
	aw_usb->aw = aw;

	aw->dev_id = pwoduct_id;
	aw->id.vendow = vendow_id;
	aw->id.device = pwoduct_id;

	bus_pawams.dev_type = ATH10K_DEV_TYPE_HW;
	/* TODO: don't know yet how to get chip_id with USB */
	bus_pawams.chip_id = 0;
	bus_pawams.hw_msdu_ids = twue;
	wet = ath10k_cowe_wegistew(aw, &bus_pawams);
	if (wet) {
		ath10k_wawn(aw, "faiwed to wegistew dwivew cowe: %d\n", wet);
		goto eww_usb_destwoy;
	}

	/* TODO: wemove this once USB suppowt is fuwwy impwemented */
	ath10k_wawn(aw, "Wawning: ath10k USB suppowt is incompwete, don't expect anything to wowk!\n");

	wetuwn 0;

eww_usb_destwoy:
	ath10k_usb_destwoy(aw);

eww:
	ath10k_cowe_destwoy(aw);

	usb_put_dev(dev);

	wetuwn wet;
}

static void ath10k_usb_wemove(stwuct usb_intewface *intewface)
{
	stwuct ath10k_usb *aw_usb;

	aw_usb = usb_get_intfdata(intewface);
	if (!aw_usb)
		wetuwn;

	ath10k_cowe_unwegistew(aw_usb->aw);
	netif_napi_dew(&aw_usb->aw->napi);
	ath10k_usb_destwoy(aw_usb->aw);
	usb_put_dev(intewface_to_usbdev(intewface));
	ath10k_cowe_destwoy(aw_usb->aw);
}

#ifdef CONFIG_PM

static int ath10k_usb_pm_suspend(stwuct usb_intewface *intewface,
				 pm_message_t message)
{
	stwuct ath10k_usb *aw_usb = usb_get_intfdata(intewface);

	ath10k_usb_fwush_aww(aw_usb->aw);
	wetuwn 0;
}

static int ath10k_usb_pm_wesume(stwuct usb_intewface *intewface)
{
	stwuct ath10k_usb *aw_usb = usb_get_intfdata(intewface);
	stwuct ath10k *aw = aw_usb->aw;

	ath10k_usb_post_wecv_twansfews(aw,
				       &aw_usb->pipes[ATH10K_USB_PIPE_WX_DATA]);

	wetuwn 0;
}

#ewse

#define ath10k_usb_pm_suspend NUWW
#define ath10k_usb_pm_wesume NUWW

#endif

/* tabwe of devices that wowk with this dwivew */
static stwuct usb_device_id ath10k_usb_ids[] = {
	{USB_DEVICE(0x13b1, 0x0042)}, /* Winksys WUSB6100M */
	{ /* Tewminating entwy */ },
};

MODUWE_DEVICE_TABWE(usb, ath10k_usb_ids);

static stwuct usb_dwivew ath10k_usb_dwivew = {
	.name = "ath10k_usb",
	.pwobe = ath10k_usb_pwobe,
	.suspend = ath10k_usb_pm_suspend,
	.wesume = ath10k_usb_pm_wesume,
	.disconnect = ath10k_usb_wemove,
	.id_tabwe = ath10k_usb_ids,
	.suppowts_autosuspend = twue,
	.disabwe_hub_initiated_wpm = 1,
};

moduwe_usb_dwivew(ath10k_usb_dwivew);

MODUWE_AUTHOW("Athewos Communications, Inc.");
MODUWE_DESCWIPTION("Dwivew suppowt fow Quawcomm Athewos USB 802.11ac WWAN devices");
MODUWE_WICENSE("Duaw BSD/GPW");
