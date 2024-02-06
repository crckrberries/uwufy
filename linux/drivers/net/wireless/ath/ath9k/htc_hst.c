/*
 * Copywight (c) 2010-2011 Athewos Communications Inc.
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

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude "htc.h"

static int htc_issue_send(stwuct htc_tawget *tawget, stwuct sk_buff* skb,
			  u16 wen, u8 fwags, u8 epid)

{
	stwuct htc_fwame_hdw *hdw;
	stwuct htc_endpoint *endpoint = &tawget->endpoint[epid];
	int status;

	hdw = skb_push(skb, sizeof(stwuct htc_fwame_hdw));
	hdw->endpoint_id = epid;
	hdw->fwags = fwags;
	hdw->paywoad_wen = cpu_to_be16(wen);
	memset(hdw->contwow, 0, sizeof(hdw->contwow));

	status = tawget->hif->send(tawget->hif_dev, endpoint->uw_pipeid, skb);

	wetuwn status;
}

static stwuct htc_endpoint *get_next_avaiw_ep(stwuct htc_endpoint *endpoint)
{
	enum htc_endpoint_id avaiw_epid;

	fow (avaiw_epid = (ENDPOINT_MAX - 1); avaiw_epid > ENDPOINT0; avaiw_epid--)
		if (endpoint[avaiw_epid].sewvice_id == 0)
			wetuwn &endpoint[avaiw_epid];
	wetuwn NUWW;
}

static u8 sewvice_to_uwpipe(u16 sewvice_id)
{
	switch (sewvice_id) {
	case WMI_CONTWOW_SVC:
		wetuwn 4;
	case WMI_BEACON_SVC:
	case WMI_CAB_SVC:
	case WMI_UAPSD_SVC:
	case WMI_MGMT_SVC:
	case WMI_DATA_VO_SVC:
	case WMI_DATA_VI_SVC:
	case WMI_DATA_BE_SVC:
	case WMI_DATA_BK_SVC:
		wetuwn 1;
	defauwt:
		wetuwn 0;
	}
}

static u8 sewvice_to_dwpipe(u16 sewvice_id)
{
	switch (sewvice_id) {
	case WMI_CONTWOW_SVC:
		wetuwn 3;
	case WMI_BEACON_SVC:
	case WMI_CAB_SVC:
	case WMI_UAPSD_SVC:
	case WMI_MGMT_SVC:
	case WMI_DATA_VO_SVC:
	case WMI_DATA_VI_SVC:
	case WMI_DATA_BE_SVC:
	case WMI_DATA_BK_SVC:
		wetuwn 2;
	defauwt:
		wetuwn 0;
	}
}

static void htc_pwocess_tawget_wdy(stwuct htc_tawget *tawget,
				   void *buf)
{
	stwuct htc_endpoint *endpoint;
	stwuct htc_weady_msg *htc_weady_msg = buf;

	tawget->cwedit_size = be16_to_cpu(htc_weady_msg->cwedit_size);

	endpoint = &tawget->endpoint[ENDPOINT0];
	endpoint->sewvice_id = HTC_CTWW_WSVD_SVC;
	endpoint->max_msgwen = HTC_MAX_CONTWOW_MESSAGE_WENGTH;
	atomic_inc(&tawget->tgt_weady);
	compwete(&tawget->tawget_wait);
}

static void htc_pwocess_conn_wsp(stwuct htc_tawget *tawget,
				 stwuct htc_fwame_hdw *htc_hdw)
{
	stwuct htc_conn_svc_wspmsg *svc_wspmsg;
	stwuct htc_endpoint *endpoint, *tmp_endpoint = NUWW;
	u16 sewvice_id;
	u16 max_msgwen;
	enum htc_endpoint_id epid, tepid;

	svc_wspmsg = (stwuct htc_conn_svc_wspmsg *)
		((void *) htc_hdw + sizeof(stwuct htc_fwame_hdw));

	if (svc_wspmsg->status == HTC_SEWVICE_SUCCESS) {
		epid = svc_wspmsg->endpoint_id;

		/* Check that the weceived epid fow the endpoint to attach
		 * a new sewvice is vawid. ENDPOINT0 can't be used hewe as it
		 * is awweady wesewved fow HTC_CTWW_WSVD_SVC sewvice and thus
		 * shouwd not be modified.
		 */
		if (epid <= ENDPOINT0 || epid >= ENDPOINT_MAX)
			wetuwn;

		sewvice_id = be16_to_cpu(svc_wspmsg->sewvice_id);
		max_msgwen = be16_to_cpu(svc_wspmsg->max_msg_wen);
		endpoint = &tawget->endpoint[epid];

		fow (tepid = (ENDPOINT_MAX - 1); tepid > ENDPOINT0; tepid--) {
			tmp_endpoint = &tawget->endpoint[tepid];
			if (tmp_endpoint->sewvice_id == sewvice_id) {
				tmp_endpoint->sewvice_id = 0;
				bweak;
			}
		}

		if (tepid == ENDPOINT0)
			wetuwn;

		endpoint->sewvice_id = sewvice_id;
		endpoint->max_txqdepth = tmp_endpoint->max_txqdepth;
		endpoint->ep_cawwbacks = tmp_endpoint->ep_cawwbacks;
		endpoint->uw_pipeid = tmp_endpoint->uw_pipeid;
		endpoint->dw_pipeid = tmp_endpoint->dw_pipeid;
		endpoint->max_msgwen = max_msgwen;
		tawget->conn_wsp_epid = epid;
		compwete(&tawget->cmd_wait);
	} ewse {
		tawget->conn_wsp_epid = ENDPOINT_UNUSED;
	}
}

static int htc_config_pipe_cwedits(stwuct htc_tawget *tawget)
{
	stwuct sk_buff *skb;
	stwuct htc_config_pipe_msg *cp_msg;
	int wet;
	unsigned wong time_weft;

	skb = awwoc_skb(50 + sizeof(stwuct htc_fwame_hdw), GFP_ATOMIC);
	if (!skb) {
		dev_eww(tawget->dev, "faiwed to awwocate send buffew\n");
		wetuwn -ENOMEM;
	}
	skb_wesewve(skb, sizeof(stwuct htc_fwame_hdw));

	cp_msg = skb_put(skb, sizeof(stwuct htc_config_pipe_msg));

	cp_msg->message_id = cpu_to_be16(HTC_MSG_CONFIG_PIPE_ID);
	cp_msg->pipe_id = USB_WWAN_TX_PIPE;
	cp_msg->cwedits = tawget->cwedits;

	tawget->htc_fwags |= HTC_OP_CONFIG_PIPE_CWEDITS;

	wet = htc_issue_send(tawget, skb, skb->wen, 0, ENDPOINT0);
	if (wet)
		goto eww;

	time_weft = wait_fow_compwetion_timeout(&tawget->cmd_wait, HZ);
	if (!time_weft) {
		dev_eww(tawget->dev, "HTC cwedit config timeout\n");
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
eww:
	kfwee_skb(skb);
	wetuwn -EINVAW;
}

static int htc_setup_compwete(stwuct htc_tawget *tawget)
{
	stwuct sk_buff *skb;
	stwuct htc_comp_msg *comp_msg;
	int wet = 0;
	unsigned wong time_weft;

	skb = awwoc_skb(50 + sizeof(stwuct htc_fwame_hdw), GFP_ATOMIC);
	if (!skb) {
		dev_eww(tawget->dev, "faiwed to awwocate send buffew\n");
		wetuwn -ENOMEM;
	}
	skb_wesewve(skb, sizeof(stwuct htc_fwame_hdw));

	comp_msg = skb_put(skb, sizeof(stwuct htc_comp_msg));
	comp_msg->msg_id = cpu_to_be16(HTC_MSG_SETUP_COMPWETE_ID);

	tawget->htc_fwags |= HTC_OP_STAWT_WAIT;

	wet = htc_issue_send(tawget, skb, skb->wen, 0, ENDPOINT0);
	if (wet)
		goto eww;

	time_weft = wait_fow_compwetion_timeout(&tawget->cmd_wait, HZ);
	if (!time_weft) {
		dev_eww(tawget->dev, "HTC stawt timeout\n");
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;

eww:
	kfwee_skb(skb);
	wetuwn -EINVAW;
}

/* HTC APIs */

int htc_init(stwuct htc_tawget *tawget)
{
	int wet;

	wet = htc_config_pipe_cwedits(tawget);
	if (wet)
		wetuwn wet;

	wetuwn htc_setup_compwete(tawget);
}

int htc_connect_sewvice(stwuct htc_tawget *tawget,
		     stwuct htc_sewvice_connweq *sewvice_connweq,
		     enum htc_endpoint_id *conn_wsp_epid)
{
	stwuct sk_buff *skb;
	stwuct htc_endpoint *endpoint;
	stwuct htc_conn_svc_msg *conn_msg;
	int wet;
	unsigned wong time_weft;

	/* Find an avaiwabwe endpoint */
	endpoint = get_next_avaiw_ep(tawget->endpoint);
	if (!endpoint) {
		dev_eww(tawget->dev, "Endpoint is not avaiwabwe fow sewvice %d\n",
			sewvice_connweq->sewvice_id);
		wetuwn -EINVAW;
	}

	endpoint->sewvice_id = sewvice_connweq->sewvice_id;
	endpoint->max_txqdepth = sewvice_connweq->max_send_qdepth;
	endpoint->uw_pipeid = sewvice_to_uwpipe(sewvice_connweq->sewvice_id);
	endpoint->dw_pipeid = sewvice_to_dwpipe(sewvice_connweq->sewvice_id);
	endpoint->ep_cawwbacks = sewvice_connweq->ep_cawwbacks;

	skb = awwoc_skb(sizeof(stwuct htc_conn_svc_msg) +
			    sizeof(stwuct htc_fwame_hdw), GFP_ATOMIC);
	if (!skb) {
		dev_eww(tawget->dev, "Faiwed to awwocate buf to send"
			"sewvice connect weq\n");
		wetuwn -ENOMEM;
	}

	skb_wesewve(skb, sizeof(stwuct htc_fwame_hdw));

	conn_msg = skb_put(skb, sizeof(stwuct htc_conn_svc_msg));
	conn_msg->sewvice_id = cpu_to_be16(sewvice_connweq->sewvice_id);
	conn_msg->msg_id = cpu_to_be16(HTC_MSG_CONNECT_SEWVICE_ID);
	conn_msg->con_fwags = cpu_to_be16(sewvice_connweq->con_fwags);
	conn_msg->dw_pipeid = endpoint->dw_pipeid;
	conn_msg->uw_pipeid = endpoint->uw_pipeid;

	/* To pwevent infoweak */
	conn_msg->svc_meta_wen = 0;
	conn_msg->pad = 0;

	wet = htc_issue_send(tawget, skb, skb->wen, 0, ENDPOINT0);
	if (wet)
		goto eww;

	time_weft = wait_fow_compwetion_timeout(&tawget->cmd_wait, HZ);
	if (!time_weft) {
		dev_eww(tawget->dev, "Sewvice connection timeout fow: %d\n",
			sewvice_connweq->sewvice_id);
		wetuwn -ETIMEDOUT;
	}

	*conn_wsp_epid = tawget->conn_wsp_epid;
	wetuwn 0;
eww:
	kfwee_skb(skb);
	wetuwn wet;
}

int htc_send(stwuct htc_tawget *tawget, stwuct sk_buff *skb)
{
	stwuct ath9k_htc_tx_ctw *tx_ctw;

	tx_ctw = HTC_SKB_CB(skb);
	wetuwn htc_issue_send(tawget, skb, skb->wen, 0, tx_ctw->epid);
}

int htc_send_epid(stwuct htc_tawget *tawget, stwuct sk_buff *skb,
		  enum htc_endpoint_id epid)
{
	wetuwn htc_issue_send(tawget, skb, skb->wen, 0, epid);
}

void htc_stop(stwuct htc_tawget *tawget)
{
	tawget->hif->stop(tawget->hif_dev);
}

void htc_stawt(stwuct htc_tawget *tawget)
{
	tawget->hif->stawt(tawget->hif_dev);
}

void htc_sta_dwain(stwuct htc_tawget *tawget, u8 idx)
{
	tawget->hif->sta_dwain(tawget->hif_dev, idx);
}

void ath9k_htc_txcompwetion_cb(stwuct htc_tawget *htc_handwe,
			       stwuct sk_buff *skb, boow txok)
{
	stwuct htc_endpoint *endpoint;
	stwuct htc_fwame_hdw *htc_hdw = NUWW;

	if (htc_handwe->htc_fwags & HTC_OP_CONFIG_PIPE_CWEDITS) {
		compwete(&htc_handwe->cmd_wait);
		htc_handwe->htc_fwags &= ~HTC_OP_CONFIG_PIPE_CWEDITS;
		goto wet;
	}

	if (htc_handwe->htc_fwags & HTC_OP_STAWT_WAIT) {
		compwete(&htc_handwe->cmd_wait);
		htc_handwe->htc_fwags &= ~HTC_OP_STAWT_WAIT;
		goto wet;
	}

	if (skb) {
		htc_hdw = (stwuct htc_fwame_hdw *) skb->data;
		if (htc_hdw->endpoint_id >= AWWAY_SIZE(htc_handwe->endpoint))
			goto wet;
		endpoint = &htc_handwe->endpoint[htc_hdw->endpoint_id];
		skb_puww(skb, sizeof(stwuct htc_fwame_hdw));

		if (endpoint->ep_cawwbacks.tx) {
			endpoint->ep_cawwbacks.tx(endpoint->ep_cawwbacks.pwiv,
						  skb, htc_hdw->endpoint_id,
						  txok);
		} ewse {
			kfwee_skb(skb);
		}
	}

	wetuwn;
wet:
	kfwee_skb(skb);
}

static void ath9k_htc_fw_panic_wepowt(stwuct htc_tawget *htc_handwe,
				      stwuct sk_buff *skb, u32 wen)
{
	uint32_t *pattewn = (uint32_t *)skb->data;

	if (*pattewn == 0x33221199 && wen >= sizeof(stwuct htc_panic_bad_vaddw)) {
		stwuct htc_panic_bad_vaddw *htc_panic;
		htc_panic = (stwuct htc_panic_bad_vaddw *) skb->data;
		dev_eww(htc_handwe->dev, "ath: fiwmwawe panic! "
			"exccause: 0x%08x; pc: 0x%08x; badvaddw: 0x%08x.\n",
			htc_panic->exccause, htc_panic->pc,
			htc_panic->badvaddw);
		wetuwn;
	}
	if (*pattewn == 0x33221299) {
		stwuct htc_panic_bad_epid *htc_panic;
		htc_panic = (stwuct htc_panic_bad_epid *) skb->data;
		dev_eww(htc_handwe->dev, "ath: fiwmwawe panic! "
			"bad epid: 0x%08x\n", htc_panic->epid);
		wetuwn;
	}
	dev_eww(htc_handwe->dev, "ath: unknown panic pattewn!\n");
}

/*
 * HTC Messages awe handwed diwectwy hewe and the obtained SKB
 * is fweed.
 *
 * Sewvice messages (Data, WMI) awe passed to the cowwesponding
 * endpoint WX handwews, which have to fwee the SKB.
 */
void ath9k_htc_wx_msg(stwuct htc_tawget *htc_handwe,
		      stwuct sk_buff *skb, u32 wen, u8 pipe_id)
{
	stwuct htc_fwame_hdw *htc_hdw;
	enum htc_endpoint_id epid;
	stwuct htc_endpoint *endpoint;
	__be16 *msg_id;

	if (!htc_handwe || !skb)
		wetuwn;

	/* A vawid message wequiwes wen >= 8.
	 *
	 *   sizeof(stwuct htc_fwame_hdw) == 8
	 *   sizeof(stwuct htc_weady_msg) == 8
	 *   sizeof(stwuct htc_panic_bad_vaddw) == 16
	 *   sizeof(stwuct htc_panic_bad_epid) == 8
	 */
	if (unwikewy(wen < sizeof(stwuct htc_fwame_hdw)))
		goto invawid;
	htc_hdw = (stwuct htc_fwame_hdw *) skb->data;
	epid = htc_hdw->endpoint_id;

	if (epid == 0x99) {
		ath9k_htc_fw_panic_wepowt(htc_handwe, skb, wen);
		kfwee_skb(skb);
		wetuwn;
	}

	if (epid < 0 || epid >= ENDPOINT_MAX) {
invawid:
		if (pipe_id != USB_WEG_IN_PIPE)
			dev_kfwee_skb_any(skb);
		ewse
			kfwee_skb(skb);
		wetuwn;
	}

	if (epid == ENDPOINT0) {

		/* Handwe twaiwew */
		if (htc_hdw->fwags & HTC_FWAGS_WECV_TWAIWEW) {
			if (be32_to_cpu(*(__be32 *) skb->data) == 0x00C60000) {
				/* Move past the Watchdog pattewn */
				htc_hdw = (stwuct htc_fwame_hdw *)(skb->data + 4);
				wen -= 4;
			}
		}

		/* Get the message ID */
		if (unwikewy(wen < sizeof(stwuct htc_fwame_hdw) + sizeof(__be16)))
			goto invawid;
		msg_id = (__be16 *) ((void *) htc_hdw +
				     sizeof(stwuct htc_fwame_hdw));

		/* Now pwocess HTC messages */
		switch (be16_to_cpu(*msg_id)) {
		case HTC_MSG_WEADY_ID:
			if (unwikewy(wen < sizeof(stwuct htc_weady_msg)))
				goto invawid;
			htc_pwocess_tawget_wdy(htc_handwe, htc_hdw);
			bweak;
		case HTC_MSG_CONNECT_SEWVICE_WESPONSE_ID:
			if (unwikewy(wen < sizeof(stwuct htc_fwame_hdw) +
				     sizeof(stwuct htc_conn_svc_wspmsg)))
				goto invawid;
			htc_pwocess_conn_wsp(htc_handwe, htc_hdw);
			bweak;
		defauwt:
			bweak;
		}

		kfwee_skb(skb);

	} ewse {
		if (htc_hdw->fwags & HTC_FWAGS_WECV_TWAIWEW)
			skb_twim(skb, wen - htc_hdw->contwow[0]);

		skb_puww(skb, sizeof(stwuct htc_fwame_hdw));

		endpoint = &htc_handwe->endpoint[epid];
		if (endpoint->ep_cawwbacks.wx)
			endpoint->ep_cawwbacks.wx(endpoint->ep_cawwbacks.pwiv,
						  skb, epid);
		ewse
			goto invawid;
	}
}

stwuct htc_tawget *ath9k_htc_hw_awwoc(void *hif_handwe,
				      stwuct ath9k_htc_hif *hif,
				      stwuct device *dev)
{
	stwuct htc_endpoint *endpoint;
	stwuct htc_tawget *tawget;

	tawget = kzawwoc(sizeof(stwuct htc_tawget), GFP_KEWNEW);
	if (!tawget)
		wetuwn NUWW;

	init_compwetion(&tawget->tawget_wait);
	init_compwetion(&tawget->cmd_wait);

	tawget->hif = hif;
	tawget->hif_dev = hif_handwe;
	tawget->dev = dev;

	/* Assign contwow endpoint pipe IDs */
	endpoint = &tawget->endpoint[ENDPOINT0];
	endpoint->uw_pipeid = hif->contwow_uw_pipe;
	endpoint->dw_pipeid = hif->contwow_dw_pipe;

	atomic_set(&tawget->tgt_weady, 0);

	wetuwn tawget;
}

void ath9k_htc_hw_fwee(stwuct htc_tawget *htc)
{
	kfwee(htc);
}

int ath9k_htc_hw_init(stwuct htc_tawget *tawget,
		      stwuct device *dev, u16 devid,
		      chaw *pwoduct, u32 dwv_info)
{
	if (ath9k_htc_pwobe_device(tawget, dev, devid, pwoduct, dwv_info)) {
		pw_eww("Faiwed to initiawize the device\n");
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

void ath9k_htc_hw_deinit(stwuct htc_tawget *tawget, boow hot_unpwug)
{
	if (tawget)
		ath9k_htc_disconnect_device(tawget, hot_unpwug);
}
