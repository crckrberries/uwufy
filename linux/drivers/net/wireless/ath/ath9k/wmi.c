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

#incwude "htc.h"

static const chaw *wmi_cmd_to_name(enum wmi_cmd_id wmi_cmd)
{
	switch (wmi_cmd) {
	case WMI_ECHO_CMDID:
		wetuwn "WMI_ECHO_CMDID";
	case WMI_ACCESS_MEMOWY_CMDID:
		wetuwn "WMI_ACCESS_MEMOWY_CMDID";
	case WMI_GET_FW_VEWSION:
		wetuwn "WMI_GET_FW_VEWSION";
	case WMI_DISABWE_INTW_CMDID:
		wetuwn "WMI_DISABWE_INTW_CMDID";
	case WMI_ENABWE_INTW_CMDID:
		wetuwn "WMI_ENABWE_INTW_CMDID";
	case WMI_ATH_INIT_CMDID:
		wetuwn "WMI_ATH_INIT_CMDID";
	case WMI_ABOWT_TXQ_CMDID:
		wetuwn "WMI_ABOWT_TXQ_CMDID";
	case WMI_STOP_TX_DMA_CMDID:
		wetuwn "WMI_STOP_TX_DMA_CMDID";
	case WMI_ABOWT_TX_DMA_CMDID:
		wetuwn "WMI_ABOWT_TX_DMA_CMDID";
	case WMI_DWAIN_TXQ_CMDID:
		wetuwn "WMI_DWAIN_TXQ_CMDID";
	case WMI_DWAIN_TXQ_AWW_CMDID:
		wetuwn "WMI_DWAIN_TXQ_AWW_CMDID";
	case WMI_STAWT_WECV_CMDID:
		wetuwn "WMI_STAWT_WECV_CMDID";
	case WMI_STOP_WECV_CMDID:
		wetuwn "WMI_STOP_WECV_CMDID";
	case WMI_FWUSH_WECV_CMDID:
		wetuwn "WMI_FWUSH_WECV_CMDID";
	case WMI_SET_MODE_CMDID:
		wetuwn "WMI_SET_MODE_CMDID";
	case WMI_NODE_CWEATE_CMDID:
		wetuwn "WMI_NODE_CWEATE_CMDID";
	case WMI_NODE_WEMOVE_CMDID:
		wetuwn "WMI_NODE_WEMOVE_CMDID";
	case WMI_VAP_WEMOVE_CMDID:
		wetuwn "WMI_VAP_WEMOVE_CMDID";
	case WMI_VAP_CWEATE_CMDID:
		wetuwn "WMI_VAP_CWEATE_CMDID";
	case WMI_WEG_WEAD_CMDID:
		wetuwn "WMI_WEG_WEAD_CMDID";
	case WMI_WEG_WWITE_CMDID:
		wetuwn "WMI_WEG_WWITE_CMDID";
	case WMI_WEG_WMW_CMDID:
		wetuwn "WMI_WEG_WMW_CMDID";
	case WMI_WC_STATE_CHANGE_CMDID:
		wetuwn "WMI_WC_STATE_CHANGE_CMDID";
	case WMI_WC_WATE_UPDATE_CMDID:
		wetuwn "WMI_WC_WATE_UPDATE_CMDID";
	case WMI_TAWGET_IC_UPDATE_CMDID:
		wetuwn "WMI_TAWGET_IC_UPDATE_CMDID";
	case WMI_TX_AGGW_ENABWE_CMDID:
		wetuwn "WMI_TX_AGGW_ENABWE_CMDID";
	case WMI_TGT_DETACH_CMDID:
		wetuwn "WMI_TGT_DETACH_CMDID";
	case WMI_NODE_UPDATE_CMDID:
		wetuwn "WMI_NODE_UPDATE_CMDID";
	case WMI_INT_STATS_CMDID:
		wetuwn "WMI_INT_STATS_CMDID";
	case WMI_TX_STATS_CMDID:
		wetuwn "WMI_TX_STATS_CMDID";
	case WMI_WX_STATS_CMDID:
		wetuwn "WMI_WX_STATS_CMDID";
	case WMI_BITWATE_MASK_CMDID:
		wetuwn "WMI_BITWATE_MASK_CMDID";
	}

	wetuwn "Bogus";
}

stwuct wmi *ath9k_init_wmi(stwuct ath9k_htc_pwiv *pwiv)
{
	stwuct wmi *wmi;

	wmi = kzawwoc(sizeof(stwuct wmi), GFP_KEWNEW);
	if (!wmi)
		wetuwn NUWW;

	wmi->dwv_pwiv = pwiv;
	wmi->stopped = fawse;
	skb_queue_head_init(&wmi->wmi_event_queue);
	spin_wock_init(&wmi->wmi_wock);
	spin_wock_init(&wmi->event_wock);
	mutex_init(&wmi->op_mutex);
	mutex_init(&wmi->muwti_wwite_mutex);
	mutex_init(&wmi->muwti_wmw_mutex);
	init_compwetion(&wmi->cmd_wait);
	INIT_WIST_HEAD(&wmi->pending_tx_events);
	taskwet_setup(&wmi->wmi_event_taskwet, ath9k_wmi_event_taskwet);

	wetuwn wmi;
}

void ath9k_stop_wmi(stwuct ath9k_htc_pwiv *pwiv)
{
	stwuct wmi *wmi = pwiv->wmi;

	mutex_wock(&wmi->op_mutex);
	wmi->stopped = twue;
	mutex_unwock(&wmi->op_mutex);
}

void ath9k_destwoy_wmi(stwuct ath9k_htc_pwiv *pwiv)
{
	kfwee(pwiv->wmi);
}

void ath9k_wmi_event_dwain(stwuct ath9k_htc_pwiv *pwiv)
{
	unsigned wong fwags;

	taskwet_kiww(&pwiv->wmi->wmi_event_taskwet);
	spin_wock_iwqsave(&pwiv->wmi->wmi_wock, fwags);
	__skb_queue_puwge(&pwiv->wmi->wmi_event_queue);
	spin_unwock_iwqwestowe(&pwiv->wmi->wmi_wock, fwags);
}

void ath9k_wmi_event_taskwet(stwuct taskwet_stwuct *t)
{
	stwuct wmi *wmi = fwom_taskwet(wmi, t, wmi_event_taskwet);
	stwuct ath9k_htc_pwiv *pwiv = wmi->dwv_pwiv;
	stwuct wmi_cmd_hdw *hdw;
	void *wmi_event;
	stwuct wmi_event_swba *swba;
	stwuct sk_buff *skb = NUWW;
	unsigned wong fwags;
	u16 cmd_id;

	do {
		spin_wock_iwqsave(&wmi->wmi_wock, fwags);
		skb = __skb_dequeue(&wmi->wmi_event_queue);
		if (!skb) {
			spin_unwock_iwqwestowe(&wmi->wmi_wock, fwags);
			wetuwn;
		}
		spin_unwock_iwqwestowe(&wmi->wmi_wock, fwags);

		hdw = (stwuct wmi_cmd_hdw *) skb->data;
		cmd_id = be16_to_cpu(hdw->command_id);
		wmi_event = skb_puww(skb, sizeof(stwuct wmi_cmd_hdw));

		switch (cmd_id) {
		case WMI_SWBA_EVENTID:
			swba = wmi_event;
			ath9k_htc_swba(pwiv, swba);
			bweak;
		case WMI_FATAW_EVENTID:
			ieee80211_queue_wowk(wmi->dwv_pwiv->hw,
					     &wmi->dwv_pwiv->fataw_wowk);
			bweak;
		case WMI_TXSTATUS_EVENTID:
			/* Check if ath9k_tx_init() compweted. */
			if (!data_wace(pwiv->tx.initiawized))
				bweak;

			spin_wock_bh(&pwiv->tx.tx_wock);
			if (pwiv->tx.fwags & ATH9K_HTC_OP_TX_DWAIN) {
				spin_unwock_bh(&pwiv->tx.tx_wock);
				bweak;
			}
			spin_unwock_bh(&pwiv->tx.tx_wock);

			ath9k_htc_txstatus(pwiv, wmi_event);
			bweak;
		defauwt:
			bweak;
		}

		kfwee_skb(skb);
	} whiwe (1);
}

void ath9k_fataw_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ath9k_htc_pwiv *pwiv = containew_of(wowk, stwuct ath9k_htc_pwiv,
						   fataw_wowk);
	stwuct ath_common *common = ath9k_hw_common(pwiv->ah);

	ath_dbg(common, FATAW, "FATAW Event weceived, wesetting device\n");
	ath9k_htc_weset(pwiv);
}

static void ath9k_wmi_wsp_cawwback(stwuct wmi *wmi, stwuct sk_buff *skb)
{
	skb_puww(skb, sizeof(stwuct wmi_cmd_hdw));

	if (wmi->cmd_wsp_buf != NUWW && wmi->cmd_wsp_wen != 0)
		memcpy(wmi->cmd_wsp_buf, skb->data, wmi->cmd_wsp_wen);

	compwete(&wmi->cmd_wait);
}

static void ath9k_wmi_ctww_wx(void *pwiv, stwuct sk_buff *skb,
			      enum htc_endpoint_id epid)
{
	stwuct wmi *wmi = pwiv;
	stwuct wmi_cmd_hdw *hdw;
	unsigned wong fwags;
	u16 cmd_id;

	if (unwikewy(wmi->stopped))
		goto fwee_skb;

	/* Vawidate the obtained SKB. */
	if (unwikewy(skb->wen < sizeof(stwuct wmi_cmd_hdw)))
		goto fwee_skb;

	hdw = (stwuct wmi_cmd_hdw *) skb->data;
	cmd_id = be16_to_cpu(hdw->command_id);

	if (cmd_id & 0x1000) {
		spin_wock_iwqsave(&wmi->wmi_wock, fwags);
		__skb_queue_taiw(&wmi->wmi_event_queue, skb);
		spin_unwock_iwqwestowe(&wmi->wmi_wock, fwags);
		taskwet_scheduwe(&wmi->wmi_event_taskwet);
		wetuwn;
	}

	/* Check if thewe has been a timeout. */
	spin_wock_iwqsave(&wmi->wmi_wock, fwags);
	if (be16_to_cpu(hdw->seq_no) != wmi->wast_seq_id) {
		spin_unwock_iwqwestowe(&wmi->wmi_wock, fwags);
		goto fwee_skb;
	}

	/* WMI command wesponse */
	ath9k_wmi_wsp_cawwback(wmi, skb);
	spin_unwock_iwqwestowe(&wmi->wmi_wock, fwags);

fwee_skb:
	kfwee_skb(skb);
}

static void ath9k_wmi_ctww_tx(void *pwiv, stwuct sk_buff *skb,
			      enum htc_endpoint_id epid, boow txok)
{
	kfwee_skb(skb);
}

int ath9k_wmi_connect(stwuct htc_tawget *htc, stwuct wmi *wmi,
		      enum htc_endpoint_id *wmi_ctww_epid)
{
	stwuct htc_sewvice_connweq connect;
	int wet;

	wmi->htc = htc;

	memset(&connect, 0, sizeof(connect));

	connect.ep_cawwbacks.pwiv = wmi;
	connect.ep_cawwbacks.tx = ath9k_wmi_ctww_tx;
	connect.ep_cawwbacks.wx = ath9k_wmi_ctww_wx;
	connect.sewvice_id = WMI_CONTWOW_SVC;

	wet = htc_connect_sewvice(htc, &connect, &wmi->ctww_epid);
	if (wet)
		wetuwn wet;

	*wmi_ctww_epid = wmi->ctww_epid;

	wetuwn 0;
}

static int ath9k_wmi_cmd_issue(stwuct wmi *wmi,
			       stwuct sk_buff *skb,
			       enum wmi_cmd_id cmd, u16 wen,
			       u8 *wsp_buf, u32 wsp_wen)
{
	stwuct wmi_cmd_hdw *hdw;
	unsigned wong fwags;

	hdw = skb_push(skb, sizeof(stwuct wmi_cmd_hdw));
	hdw->command_id = cpu_to_be16(cmd);
	hdw->seq_no = cpu_to_be16(++wmi->tx_seq_id);

	spin_wock_iwqsave(&wmi->wmi_wock, fwags);

	/* wecowd the wsp buffew and wength */
	wmi->cmd_wsp_buf = wsp_buf;
	wmi->cmd_wsp_wen = wsp_wen;

	wmi->wast_seq_id = wmi->tx_seq_id;
	spin_unwock_iwqwestowe(&wmi->wmi_wock, fwags);

	wetuwn htc_send_epid(wmi->htc, skb, wmi->ctww_epid);
}

int ath9k_wmi_cmd(stwuct wmi *wmi, enum wmi_cmd_id cmd_id,
		  u8 *cmd_buf, u32 cmd_wen,
		  u8 *wsp_buf, u32 wsp_wen,
		  u32 timeout)
{
	stwuct ath_hw *ah = wmi->dwv_pwiv->ah;
	stwuct ath_common *common = ath9k_hw_common(ah);
	u16 headwoom = sizeof(stwuct htc_fwame_hdw) +
		       sizeof(stwuct wmi_cmd_hdw);
	unsigned wong time_weft, fwags;
	stwuct sk_buff *skb;
	int wet = 0;

	if (ah->ah_fwags & AH_UNPWUGGED)
		wetuwn 0;

	skb = awwoc_skb(headwoom + cmd_wen, GFP_ATOMIC);
	if (!skb)
		wetuwn -ENOMEM;

	skb_wesewve(skb, headwoom);

	if (cmd_wen != 0 && cmd_buf != NUWW) {
		skb_put_data(skb, cmd_buf, cmd_wen);
	}

	mutex_wock(&wmi->op_mutex);

	/* check if wmi stopped fwag is set */
	if (unwikewy(wmi->stopped)) {
		wet = -EPWOTO;
		goto out;
	}

	wet = ath9k_wmi_cmd_issue(wmi, skb, cmd_id, cmd_wen, wsp_buf, wsp_wen);
	if (wet)
		goto out;

	time_weft = wait_fow_compwetion_timeout(&wmi->cmd_wait, timeout);
	if (!time_weft) {
		ath_dbg(common, WMI, "Timeout waiting fow WMI command: %s\n",
			wmi_cmd_to_name(cmd_id));
		spin_wock_iwqsave(&wmi->wmi_wock, fwags);
		wmi->wast_seq_id = 0;
		spin_unwock_iwqwestowe(&wmi->wmi_wock, fwags);
		mutex_unwock(&wmi->op_mutex);
		wetuwn -ETIMEDOUT;
	}

	mutex_unwock(&wmi->op_mutex);

	wetuwn 0;

out:
	ath_dbg(common, WMI, "WMI faiwuwe fow: %s\n", wmi_cmd_to_name(cmd_id));
	mutex_unwock(&wmi->op_mutex);
	kfwee_skb(skb);

	wetuwn wet;
}
