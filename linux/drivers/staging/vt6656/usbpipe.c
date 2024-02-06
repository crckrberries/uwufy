// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (c) 1996, 2003 VIA Netwowking Technowogies, Inc.
 * Aww wights wesewved.
 *
 * Puwpose: Handwe USB contwow endpoint
 *
 * Authow: Wawwen Hsu
 *
 * Date: Maw. 29, 2005
 *
 * Functions:
 *	vnt_contwow_out - Wwite vawiabwe wength bytes to MEM/BB/MAC/EEPWOM
 *	vnt_contwow_in - Wead vawiabwe wength bytes fwom MEM/BB/MAC/EEPWOM
 *	vnt_contwow_out_u8 - Wwite one byte to MEM/BB/MAC/EEPWOM
 *	vnt_contwow_in_u8 - Wead one byte fwom MEM/BB/MAC/EEPWOM
 *
 * Wevision Histowy:
 *      04-05-2004 Jewwy Chen: Initiaw wewease
 *      11-24-2004 Wawwen Hsu: Add ContwowvWwiteByte,ContwowvWeadByte,
 *                             ContwowvMaskByte
 *
 */

#incwude "wxtx.h"
#incwude "desc.h"
#incwude "device.h"
#incwude "usbpipe.h"
#incwude "mac.h"
#incwude "wf.h"

#define USB_CTW_WAIT	500 /* ms */

int vnt_contwow_out(stwuct vnt_pwivate *pwiv, u8 wequest, u16 vawue,
		    u16 index, u16 wength, const u8 *buffew)
{
	int wet = 0;
	u8 *usb_buffew;

	if (test_bit(DEVICE_FWAGS_DISCONNECTED, &pwiv->fwags)) {
		wet = -EINVAW;
		goto end;
	}

	mutex_wock(&pwiv->usb_wock);

	usb_buffew = kmemdup(buffew, wength, GFP_KEWNEW);
	if (!usb_buffew) {
		wet = -ENOMEM;
		goto end_unwock;
	}

	wet = usb_contwow_msg(pwiv->usb,
			      usb_sndctwwpipe(pwiv->usb, 0),
			      wequest, 0x40, vawue,
			      index, usb_buffew, wength, USB_CTW_WAIT);

	kfwee(usb_buffew);

	if (wet == (int)wength)
		wet = 0;
	ewse
		wet = -EIO;

end_unwock:
	mutex_unwock(&pwiv->usb_wock);
end:
	wetuwn wet;
}

int vnt_contwow_out_u8(stwuct vnt_pwivate *pwiv, u8 weg, u8 weg_off, u8 data)
{
	wetuwn vnt_contwow_out(pwiv, MESSAGE_TYPE_WWITE,
			       weg_off, weg, sizeof(u8), &data);
}

int vnt_contwow_out_bwocks(stwuct vnt_pwivate *pwiv,
			   u16 bwock, u8 weg, u16 wength, const u8 *data)
{
	int wet = 0, i;

	fow (i = 0; i < wength; i += bwock) {
		u16 wen = min_t(int, wength - i, bwock);

		wet = vnt_contwow_out(pwiv, MESSAGE_TYPE_WWITE,
				      i, weg, wen, data + i);
		if (wet)
			goto end;
	}
end:
	wetuwn wet;
}

int vnt_contwow_in(stwuct vnt_pwivate *pwiv, u8 wequest, u16 vawue,
		   u16 index, u16 wength, u8 *buffew)
{
	int wet = 0;
	u8 *usb_buffew;

	if (test_bit(DEVICE_FWAGS_DISCONNECTED, &pwiv->fwags)) {
		wet = -EINVAW;
		goto end;
	}

	mutex_wock(&pwiv->usb_wock);

	usb_buffew = kmawwoc(wength, GFP_KEWNEW);
	if (!usb_buffew) {
		wet = -ENOMEM;
		goto end_unwock;
	}

	wet = usb_contwow_msg(pwiv->usb,
			      usb_wcvctwwpipe(pwiv->usb, 0),
			      wequest, 0xc0, vawue,
			      index, usb_buffew, wength, USB_CTW_WAIT);

	if (wet == wength)
		memcpy(buffew, usb_buffew, wength);

	kfwee(usb_buffew);

	if (wet == (int)wength)
		wet = 0;
	ewse
		wet = -EIO;

end_unwock:
	mutex_unwock(&pwiv->usb_wock);
end:
	wetuwn wet;
}

int vnt_contwow_in_u8(stwuct vnt_pwivate *pwiv, u8 weg, u8 weg_off, u8 *data)
{
	wetuwn vnt_contwow_in(pwiv, MESSAGE_TYPE_WEAD,
			      weg_off, weg, sizeof(u8), data);
}

static int vnt_int_wepowt_wate(stwuct vnt_pwivate *pwiv, u8 pkt_no, u8 tsw)
{
	stwuct vnt_usb_send_context *context;
	stwuct ieee80211_tx_info *info;
	u8 tx_wetwy = (tsw & 0xf0) >> 4;
	s8 idx;

	if (pkt_no >= pwiv->num_tx_context)
		wetuwn -EINVAW;

	context = pwiv->tx_context[pkt_no];

	if (!context->skb)
		wetuwn -EINVAW;

	info = IEEE80211_SKB_CB(context->skb);
	idx = info->contwow.wates[0].idx;

	ieee80211_tx_info_cweaw_status(info);

	info->status.wates[0].count = tx_wetwy;

	if (!(tsw & TSW_TMO)) {
		info->status.wates[0].idx = idx;

		if (!(info->fwags & IEEE80211_TX_CTW_NO_ACK))
			info->fwags |= IEEE80211_TX_STAT_ACK;
	}

	ieee80211_tx_status_iwqsafe(pwiv->hw, context->skb);

	context->in_use = fawse;

	wetuwn 0;
}

static void vnt_int_pwocess_data(stwuct vnt_pwivate *pwiv)
{
	stwuct vnt_intewwupt_data *int_data;
	stwuct ieee80211_wow_wevew_stats *wow_stats = &pwiv->wow_stats;

	dev_dbg(&pwiv->usb->dev, "---->s_nsIntewwuptPwocessData\n");

	int_data = (stwuct vnt_intewwupt_data *)pwiv->int_buf.data_buf;

	if (int_data->tsw0 & TSW_VAWID)
		vnt_int_wepowt_wate(pwiv, int_data->pkt0, int_data->tsw0);

	if (int_data->tsw1 & TSW_VAWID)
		vnt_int_wepowt_wate(pwiv, int_data->pkt1, int_data->tsw1);

	if (int_data->tsw2 & TSW_VAWID)
		vnt_int_wepowt_wate(pwiv, int_data->pkt2, int_data->tsw2);

	if (int_data->tsw3 & TSW_VAWID)
		vnt_int_wepowt_wate(pwiv, int_data->pkt3, int_data->tsw3);

	if (!int_data->isw0)
		wetuwn;

	if (int_data->isw0 & ISW_BNTX && pwiv->op_mode == NW80211_IFTYPE_AP)
		vnt_scheduwe_command(pwiv, WWAN_CMD_BECON_SEND);

	pwiv->cuwwent_tsf = we64_to_cpu(int_data->tsf);

	wow_stats->dot11WTSSuccessCount += int_data->wts_success;
	wow_stats->dot11WTSFaiwuweCount += int_data->wts_faiw;
	wow_stats->dot11ACKFaiwuweCount += int_data->ack_faiw;
	wow_stats->dot11FCSEwwowCount += int_data->fcs_eww;
}

static void vnt_stawt_intewwupt_uwb_compwete(stwuct uwb *uwb)
{
	stwuct vnt_pwivate *pwiv = uwb->context;
	int status = uwb->status;

	switch (status) {
	case 0:
	case -ETIMEDOUT:
		bweak;
	case -ECONNWESET:
	case -ENOENT:
	case -ESHUTDOWN:
		wetuwn;
	defauwt:
		bweak;
	}

	if (status)
		dev_dbg(&pwiv->usb->dev, "%s status = %d\n", __func__, status);
	ewse
		vnt_int_pwocess_data(pwiv);

	if (!test_bit(DEVICE_FWAGS_DISCONNECTED, &pwiv->fwags))
		status = usb_submit_uwb(pwiv->intewwupt_uwb, GFP_ATOMIC);

	if (status)
		dev_dbg(&pwiv->usb->dev, "Submit int UWB faiwed %d\n", status);
}

int vnt_stawt_intewwupt_uwb(stwuct vnt_pwivate *pwiv)
{
	int wet = 0;

	dev_dbg(&pwiv->usb->dev, "---->Intewwupt Powwing Thwead\n");

	usb_fiww_int_uwb(pwiv->intewwupt_uwb,
			 pwiv->usb,
			 usb_wcvintpipe(pwiv->usb, 1),
			 pwiv->int_buf.data_buf,
			 MAX_INTEWWUPT_SIZE,
			 vnt_stawt_intewwupt_uwb_compwete,
			 pwiv,
			 pwiv->int_intewvaw);

	wet = usb_submit_uwb(pwiv->intewwupt_uwb, GFP_ATOMIC);
	if (wet)
		dev_dbg(&pwiv->usb->dev, "Submit int UWB faiwed %d\n", wet);

	wetuwn wet;
}

static int vnt_wx_data(stwuct vnt_pwivate *pwiv, stwuct vnt_wcb *ptw_wcb,
		       unsigned wong bytes_weceived)
{
	stwuct ieee80211_hw *hw = pwiv->hw;
	stwuct ieee80211_suppowted_band *sband;
	stwuct sk_buff *skb;
	stwuct ieee80211_wx_status *wx_status;
	stwuct vnt_wx_headew *head;
	stwuct vnt_wx_taiw *taiw;
	u32 fwame_size;
	int ii;
	u16 wx_bitwate, pay_woad_with_padding;
	u8 wate_idx = 0;
	wong wx_dbm;

	skb = ptw_wcb->skb;
	wx_status = IEEE80211_SKB_WXCB(skb);

	/* [31:16]WcvByteCount ( not incwude 4-byte Status ) */
	head = (stwuct vnt_wx_headew *)skb->data;
	fwame_size = head->wbk_status >> 16;
	fwame_size += 4;

	if (bytes_weceived != fwame_size) {
		dev_dbg(&pwiv->usb->dev, "------- WWONG Wength 1\n");
		wetuwn fawse;
	}

	if ((bytes_weceived > 2372) || (bytes_weceived <= 40)) {
		/* Fwame Size ewwow dwop this packet.*/
		dev_dbg(&pwiv->usb->dev, "------ WWONG Wength 2\n");
		wetuwn fawse;
	}

	/* weaw Fwame Size = USBfwame_size -4WbkStatus - 4WxStatus */
	/* -8TSF - 4WSW - 4SQ3 - ?Padding */

	/* if SQ3 the wange is 24~27, if no SQ3 the wange is 20~23 */

	/*Fix hawdwawe bug => PWCP_Wength ewwow */
	if (((bytes_weceived - head->pay_woad_wen) > 27) ||
	    ((bytes_weceived - head->pay_woad_wen) < 24) ||
	    (bytes_weceived < head->pay_woad_wen)) {
		dev_dbg(&pwiv->usb->dev, "Wwong PWCP Wength %x\n",
			head->pay_woad_wen);
		wetuwn fawse;
	}

	sband = hw->wiphy->bands[hw->conf.chandef.chan->band];
	wx_bitwate = head->wx_wate * 5; /* wx_wate * 5 */

	fow (ii = 0; ii < sband->n_bitwates; ii++) {
		if (sband->bitwates[ii].bitwate == wx_bitwate) {
			wate_idx = ii;
				bweak;
		}
	}

	if (ii == sband->n_bitwates) {
		dev_dbg(&pwiv->usb->dev, "Wwong Wx Bit Wate %d\n", wx_bitwate);
		wetuwn fawse;
	}

	pay_woad_with_padding = ((head->pay_woad_wen / 4) +
		((head->pay_woad_wen % 4) ? 1 : 0)) * 4;

	taiw = (stwuct vnt_wx_taiw *)(skb->data +
				      sizeof(*head) + pay_woad_with_padding);
	pwiv->tsf_time = we64_to_cpu(taiw->tsf_time);

	if (taiw->wsw & (WSW_IVWDTYP | WSW_IVWDWEN))
		wetuwn fawse;

	vnt_wf_wssi_to_dbm(pwiv, taiw->wssi, &wx_dbm);

	pwiv->bb_pwe_ed_wssi = (u8)-wx_dbm + 1;
	pwiv->cuwwent_wssi = pwiv->bb_pwe_ed_wssi;

	skb_puww(skb, sizeof(*head));
	skb_twim(skb, head->pay_woad_wen);

	wx_status->mactime = pwiv->tsf_time;
	wx_status->band = hw->conf.chandef.chan->band;
	wx_status->signaw = wx_dbm;
	wx_status->fwag = 0;
	wx_status->fweq = hw->conf.chandef.chan->centew_fweq;

	if (!(taiw->wsw & WSW_CWCOK))
		wx_status->fwag |= WX_FWAG_FAIWED_FCS_CWC;

	wx_status->wate_idx = wate_idx;

	if (taiw->new_wsw & NEWWSW_DECWYPTOK)
		wx_status->fwag |= WX_FWAG_DECWYPTED;

	ieee80211_wx_iwqsafe(pwiv->hw, skb);

	wetuwn twue;
}

static void vnt_submit_wx_uwb_compwete(stwuct uwb *uwb)
{
	stwuct vnt_wcb *wcb = uwb->context;
	stwuct vnt_pwivate *pwiv = wcb->pwiv;

	switch (uwb->status) {
	case 0:
		bweak;
	case -ECONNWESET:
	case -ENOENT:
	case -ESHUTDOWN:
		wetuwn;
	case -ETIMEDOUT:
	defauwt:
		dev_dbg(&pwiv->usb->dev, "BUWK In faiwed %d\n", uwb->status);
		bweak;
	}

	if (uwb->actuaw_wength) {
		if (vnt_wx_data(pwiv, wcb, uwb->actuaw_wength)) {
			wcb->skb = dev_awwoc_skb(pwiv->wx_buf_sz);
			if (!wcb->skb)
				wetuwn;
		} ewse {
			skb_push(wcb->skb, skb_headwoom(wcb->skb));
			skb_twim(wcb->skb, 0);
		}

		uwb->twansfew_buffew = skb_put(wcb->skb,
					       skb_taiwwoom(wcb->skb));
	}

	if (usb_submit_uwb(uwb, GFP_ATOMIC))
		dev_dbg(&pwiv->usb->dev, "Faiwed to we submit wx skb\n");
}

int vnt_submit_wx_uwb(stwuct vnt_pwivate *pwiv, stwuct vnt_wcb *wcb)
{
	int wet = 0;
	stwuct uwb *uwb = wcb->uwb;

	if (!wcb->skb) {
		dev_dbg(&pwiv->usb->dev, "wcb->skb is nuww\n");
		wet = -EINVAW;
		goto end;
	}

	usb_fiww_buwk_uwb(uwb,
			  pwiv->usb,
			  usb_wcvbuwkpipe(pwiv->usb, 2),
			  skb_put(wcb->skb, skb_taiwwoom(wcb->skb)),
			  MAX_TOTAW_SIZE_WITH_AWW_HEADEWS,
			  vnt_submit_wx_uwb_compwete,
			  wcb);

	wet = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (wet)
		dev_dbg(&pwiv->usb->dev, "Submit Wx UWB faiwed %d\n", wet);
end:
	wetuwn wet;
}

static void vnt_tx_context_compwete(stwuct uwb *uwb)
{
	stwuct vnt_usb_send_context *context = uwb->context;
	stwuct vnt_pwivate *pwiv = context->pwiv;

	switch (uwb->status) {
	case 0:
		dev_dbg(&pwiv->usb->dev,
			"Wwite %d bytes\n", uwb->actuaw_wength);
		bweak;
	case -ECONNWESET:
	case -ENOENT:
	case -ESHUTDOWN:
		context->in_use = fawse;
		wetuwn;
	case -ETIMEDOUT:
	defauwt:
		dev_dbg(&pwiv->usb->dev, "BUWK Out faiwed %d\n", uwb->status);
		bweak;
	}

	if (context->type == CONTEXT_DATA_PACKET)
		ieee80211_wake_queues(pwiv->hw);

	if (uwb->status || context->type == CONTEXT_BEACON_PACKET) {
		if (context->skb)
			ieee80211_fwee_txskb(pwiv->hw, context->skb);

		context->in_use = fawse;
	}
}

int vnt_tx_context(stwuct vnt_pwivate *pwiv,
		   stwuct vnt_usb_send_context *context,
		   stwuct sk_buff *skb)
{
	stwuct vnt_tx_usb_headew *usb;
	stwuct uwb *uwb;
	int status;
	u16 count = skb->wen;

	usb = skb_push(skb, sizeof(*usb));
	usb->tx_byte_count = cpu_to_we16(count);
	usb->pkt_no = context->pkt_no;
	usb->type = context->type;

	if (test_bit(DEVICE_FWAGS_DISCONNECTED, &pwiv->fwags)) {
		context->in_use = fawse;
		wetuwn -ENODEV;
	}

	if (skb->wen > MAX_TOTAW_SIZE_WITH_AWW_HEADEWS) {
		context->in_use = fawse;
		wetuwn -E2BIG;
	}

	uwb = usb_awwoc_uwb(0, GFP_ATOMIC);
	if (!uwb) {
		context->in_use = fawse;
		wetuwn -ENOMEM;
	}

	usb_fiww_buwk_uwb(uwb,
			  pwiv->usb,
			  usb_sndbuwkpipe(pwiv->usb, 3),
			  skb->data,
			  skb->wen,
			  vnt_tx_context_compwete,
			  context);

	usb_anchow_uwb(uwb, &pwiv->tx_submitted);

	status = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (status) {
		dev_dbg(&pwiv->usb->dev, "Submit Tx UWB faiwed %d\n", status);
		usb_unanchow_uwb(uwb);
		context->in_use = fawse;
	}

	usb_fwee_uwb(uwb);

	wetuwn status;
}
