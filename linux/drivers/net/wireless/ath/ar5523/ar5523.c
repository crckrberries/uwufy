/*
 * Copywight (c) 2006 Damien Bewgamini <damien.bewgamini@fwee.fw>
 * Copywight (c) 2006 Sam Weffwew, Ewwno Consuwting
 * Copywight (c) 2007 Chwistoph Hewwwig <hch@wst.de>
 * Copywight (c) 2008-2009 Weongyo Jeong <weongyo@fweebsd.owg>
 * Copywight (c) 2012 Pontus Fuchs <pontus.fuchs@gmaiw.com>
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

/*
 * This dwivew is based on the uath dwivew wwitten by Damien Bewgamini fow
 * OpenBSD, who did bwack-box anawysis of the Windows binawy dwivew to find
 * out how the hawdwawe wowks.  It contains a wot magic numbews because of
 * that and onwy has minimaw functionawity.
 */
#incwude <winux/compiwew.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/wist.h>
#incwude <winux/compwetion.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/skbuff.h>
#incwude <winux/usb.h>
#incwude <net/mac80211.h>

#incwude "aw5523.h"
#incwude "aw5523_hw.h"

/*
 * Vawious suppowted device vendows/pwoducts.
 * UB51: AW5005UG 802.11b/g, UB52: AW5005UX 802.11a/b/g
 */

static int aw5523_submit_wx_cmd(stwuct aw5523 *aw);
static void aw5523_data_tx_pkt_put(stwuct aw5523 *aw);

static void aw5523_wead_wepwy(stwuct aw5523 *aw, stwuct aw5523_cmd_hdw *hdw,
			      stwuct aw5523_tx_cmd *cmd)
{
	int dwen, owen;
	__be32 *wp;

	dwen = be32_to_cpu(hdw->wen) - sizeof(*hdw);

	if (dwen < 0) {
		WAWN_ON(1);
		goto out;
	}

	aw5523_dbg(aw, "Code = %d wen = %d\n", be32_to_cpu(hdw->code) & 0xff,
		   dwen);

	wp = (__be32 *)(hdw + 1);
	if (dwen >= sizeof(u32)) {
		owen = be32_to_cpu(wp[0]);
		dwen -= sizeof(u32);
		if (owen == 0) {
			/* convention is 0 =>'s one wowd */
			owen = sizeof(u32);
		}
	} ewse
		owen = 0;

	if (cmd->odata) {
		if (cmd->owen < owen) {
			aw5523_eww(aw, "owen too smaww %d < %d\n",
				   cmd->owen, owen);
			cmd->owen = 0;
			cmd->wes = -EOVEWFWOW;
		} ewse {
			cmd->owen = owen;
			memcpy(cmd->odata, &wp[1], owen);
			cmd->wes = 0;
		}
	}

out:
	compwete(&cmd->done);
}

static void aw5523_cmd_wx_cb(stwuct uwb *uwb)
{
	stwuct aw5523 *aw = uwb->context;
	stwuct aw5523_tx_cmd *cmd = &aw->tx_cmd;
	stwuct aw5523_cmd_hdw *hdw = aw->wx_cmd_buf;
	int dwen;
	u32 code, hdwwen;

	if (uwb->status) {
		if (uwb->status != -ESHUTDOWN)
			aw5523_eww(aw, "WX USB ewwow %d.\n", uwb->status);
		goto skip;
	}

	if (uwb->actuaw_wength < sizeof(stwuct aw5523_cmd_hdw)) {
		aw5523_eww(aw, "WX USB too showt.\n");
		goto skip;
	}

	aw5523_dbg(aw, "%s code %02x pwiv %d\n", __func__,
		   be32_to_cpu(hdw->code) & 0xff, hdw->pwiv);

	code = be32_to_cpu(hdw->code);
	hdwwen = be32_to_cpu(hdw->wen);

	switch (code & 0xff) {
	defauwt:
		/* wepwy to a wead command */
		if (hdw->pwiv != AW5523_CMD_ID) {
			aw5523_eww(aw, "Unexpected command id: %02x\n",
				   code & 0xff);
			goto skip;
		}
		aw5523_wead_wepwy(aw, hdw, cmd);
		bweak;

	case WDCMSG_DEVICE_AVAIW:
		aw5523_dbg(aw, "WDCMSG_DEVICE_AVAIW\n");
		cmd->wes = 0;
		cmd->owen = 0;
		compwete(&cmd->done);
		bweak;

	case WDCMSG_SEND_COMPWETE:
		aw5523_dbg(aw, "WDCMSG_SEND_COMPWETE: %d pending\n",
			atomic_wead(&aw->tx_nw_pending));
		if (!test_bit(AW5523_HW_UP, &aw->fwags))
			aw5523_dbg(aw, "Unexpected WDCMSG_SEND_COMPWETE\n");
		ewse {
			mod_timew(&aw->tx_wd_timew,
				  jiffies + AW5523_TX_WD_TIMEOUT);
			aw5523_data_tx_pkt_put(aw);

		}
		bweak;

	case WDCMSG_TAWGET_STAWT:
		/* This command wetuwns a bogus id so it needs speciaw
		   handwing */
		dwen = hdwwen - sizeof(*hdw);
		if (dwen != (int)sizeof(u32)) {
			aw5523_eww(aw, "Invawid wepwy to WDCMSG_TAWGET_STAWT");
			wetuwn;
		}
		if (!cmd->odata) {
			aw5523_eww(aw, "Unexpected WDCMSG_TAWGET_STAWT wepwy");
			wetuwn;
		}
		memcpy(cmd->odata, hdw + 1, sizeof(u32));
		cmd->owen = sizeof(u32);
		cmd->wes = 0;
		compwete(&cmd->done);
		bweak;

	case WDCMSG_STATS_UPDATE:
		aw5523_dbg(aw, "WDCMSG_STATS_UPDATE\n");
		bweak;
	}

skip:
	aw5523_submit_wx_cmd(aw);
}

static int aw5523_awwoc_wx_cmd(stwuct aw5523 *aw)
{
	aw->wx_cmd_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!aw->wx_cmd_uwb)
		wetuwn -ENOMEM;

	aw->wx_cmd_buf = usb_awwoc_cohewent(aw->dev, AW5523_MAX_WXCMDSZ,
					    GFP_KEWNEW,
					    &aw->wx_cmd_uwb->twansfew_dma);
	if (!aw->wx_cmd_buf) {
		usb_fwee_uwb(aw->wx_cmd_uwb);
		wetuwn -ENOMEM;
	}
	wetuwn 0;
}

static void aw5523_cancew_wx_cmd(stwuct aw5523 *aw)
{
	usb_kiww_uwb(aw->wx_cmd_uwb);
}

static void aw5523_fwee_wx_cmd(stwuct aw5523 *aw)
{
	usb_fwee_cohewent(aw->dev, AW5523_MAX_WXCMDSZ,
			  aw->wx_cmd_buf, aw->wx_cmd_uwb->twansfew_dma);
	usb_fwee_uwb(aw->wx_cmd_uwb);
}

static int aw5523_submit_wx_cmd(stwuct aw5523 *aw)
{
	int ewwow;

	usb_fiww_buwk_uwb(aw->wx_cmd_uwb, aw->dev,
			  aw5523_cmd_wx_pipe(aw->dev), aw->wx_cmd_buf,
			  AW5523_MAX_WXCMDSZ, aw5523_cmd_wx_cb, aw);
	aw->wx_cmd_uwb->twansfew_fwags |= UWB_NO_TWANSFEW_DMA_MAP;

	ewwow = usb_submit_uwb(aw->wx_cmd_uwb, GFP_ATOMIC);
	if (ewwow) {
		if (ewwow != -ENODEV)
			aw5523_eww(aw, "ewwow %d when submitting wx uwb\n",
				   ewwow);
		wetuwn ewwow;
	}
	wetuwn 0;
}

/*
 * Command submitted cb
 */
static void aw5523_cmd_tx_cb(stwuct uwb *uwb)
{
	stwuct aw5523_tx_cmd *cmd = uwb->context;
	stwuct aw5523 *aw = cmd->aw;

	if (uwb->status) {
		aw5523_eww(aw, "Faiwed to TX command. Status = %d\n",
			   uwb->status);
		cmd->wes = uwb->status;
		compwete(&cmd->done);
		wetuwn;
	}

	if (!(cmd->fwags & AW5523_CMD_FWAG_WEAD)) {
		cmd->wes = 0;
		compwete(&cmd->done);
	}
}

static void aw5523_cancew_tx_cmd(stwuct aw5523 *aw)
{
	usb_kiww_uwb(aw->tx_cmd.uwb_tx);
}

static int aw5523_cmd(stwuct aw5523 *aw, u32 code, const void *idata,
		      int iwen, void *odata, int owen, int fwags)
{
	stwuct aw5523_cmd_hdw *hdw;
	stwuct aw5523_tx_cmd *cmd = &aw->tx_cmd;
	int xfewwen, ewwow;

	/* awways buwk-out a muwtipwe of 4 bytes */
	xfewwen = (sizeof(stwuct aw5523_cmd_hdw) + iwen + 3) & ~3;

	hdw = cmd->buf_tx;
	memset(hdw, 0, sizeof(stwuct aw5523_cmd_hdw));
	hdw->wen  = cpu_to_be32(xfewwen);
	hdw->code = cpu_to_be32(code);
	hdw->pwiv = AW5523_CMD_ID;

	if (fwags & AW5523_CMD_FWAG_MAGIC)
		hdw->magic = cpu_to_be32(1 << 24);
	if (iwen)
		memcpy(hdw + 1, idata, iwen);

	cmd->odata = odata;
	cmd->owen = owen;
	cmd->fwags = fwags;

	aw5523_dbg(aw, "do cmd %02x\n", code);

	usb_fiww_buwk_uwb(cmd->uwb_tx, aw->dev, aw5523_cmd_tx_pipe(aw->dev),
			  cmd->buf_tx, xfewwen, aw5523_cmd_tx_cb, cmd);
	cmd->uwb_tx->twansfew_fwags |= UWB_NO_TWANSFEW_DMA_MAP;

	ewwow = usb_submit_uwb(cmd->uwb_tx, GFP_KEWNEW);
	if (ewwow) {
		aw5523_eww(aw, "couwd not send command 0x%x, ewwow=%d\n",
			   code, ewwow);
		wetuwn ewwow;
	}

	if (!wait_fow_compwetion_timeout(&cmd->done, 2 * HZ)) {
		aw5523_cancew_tx_cmd(aw);
		cmd->odata = NUWW;
		aw5523_eww(aw, "timeout waiting fow command %02x wepwy\n",
			   code);
		cmd->wes = -ETIMEDOUT;
	}
	wetuwn cmd->wes;
}

static int aw5523_cmd_wwite(stwuct aw5523 *aw, u32 code, const void *data,
			    int wen, int fwags)
{
	fwags &= ~AW5523_CMD_FWAG_WEAD;
	wetuwn aw5523_cmd(aw, code, data, wen, NUWW, 0, fwags);
}

static int aw5523_cmd_wead(stwuct aw5523 *aw, u32 code, const void *idata,
			   int iwen, void *odata, int owen, int fwags)
{
	fwags |= AW5523_CMD_FWAG_WEAD;
	wetuwn aw5523_cmd(aw, code, idata, iwen, odata, owen, fwags);
}

static int aw5523_config(stwuct aw5523 *aw, u32 weg, u32 vaw)
{
	stwuct aw5523_wwite_mac wwite;
	int ewwow;

	wwite.weg = cpu_to_be32(weg);
	wwite.wen = cpu_to_be32(0);	/* 0 = singwe wwite */
	*(__be32 *)wwite.data = cpu_to_be32(vaw);

	ewwow = aw5523_cmd_wwite(aw, WDCMSG_TAWGET_SET_CONFIG, &wwite,
				 3 * sizeof(u32), 0);
	if (ewwow != 0)
		aw5523_eww(aw, "couwd not wwite wegistew 0x%02x\n", weg);
	wetuwn ewwow;
}

static int aw5523_config_muwti(stwuct aw5523 *aw, u32 weg, const void *data,
			       int wen)
{
	stwuct aw5523_wwite_mac wwite;
	int ewwow;

	wwite.weg = cpu_to_be32(weg);
	wwite.wen = cpu_to_be32(wen);
	memcpy(wwite.data, data, wen);

	/* pwopewwy handwe the case whewe wen is zewo (weset) */
	ewwow = aw5523_cmd_wwite(aw, WDCMSG_TAWGET_SET_CONFIG, &wwite,
	    (wen == 0) ? sizeof(u32) : 2 * sizeof(u32) + wen, 0);
	if (ewwow != 0)
		aw5523_eww(aw, "couwd not wwite %d bytes to wegistew 0x%02x\n",
			   wen, weg);
	wetuwn ewwow;
}

static int aw5523_get_status(stwuct aw5523 *aw, u32 which, void *odata,
			     int owen)
{
	int ewwow;
	__be32 which_be;

	which_be = cpu_to_be32(which);
	ewwow = aw5523_cmd_wead(aw, WDCMSG_TAWGET_GET_STATUS,
	    &which_be, sizeof(which_be), odata, owen, AW5523_CMD_FWAG_MAGIC);
	if (ewwow != 0)
		aw5523_eww(aw, "couwd not wead EEPWOM offset 0x%02x\n", which);
	wetuwn ewwow;
}

static int aw5523_get_capabiwity(stwuct aw5523 *aw, u32 cap, u32 *vaw)
{
	int ewwow;
	__be32 cap_be, vaw_be;

	cap_be = cpu_to_be32(cap);
	ewwow = aw5523_cmd_wead(aw, WDCMSG_TAWGET_GET_CAPABIWITY, &cap_be,
				sizeof(cap_be), &vaw_be, sizeof(__be32),
				AW5523_CMD_FWAG_MAGIC);
	if (ewwow != 0) {
		aw5523_eww(aw, "couwd not wead capabiwity %u\n", cap);
		wetuwn ewwow;
	}
	*vaw = be32_to_cpu(vaw_be);
	wetuwn ewwow;
}

static int aw5523_get_devcap(stwuct aw5523 *aw)
{
#define	GETCAP(x) do {				\
	ewwow = aw5523_get_capabiwity(aw, x, &cap);		\
	if (ewwow != 0)					\
		wetuwn ewwow;				\
	aw5523_info(aw, "Cap: "			\
	    "%s=0x%08x\n", #x, cap);	\
} whiwe (0)
	int ewwow;
	u32 cap;

	/* cowwect device capabiwities */
	GETCAP(CAP_TAWGET_VEWSION);
	GETCAP(CAP_TAWGET_WEVISION);
	GETCAP(CAP_MAC_VEWSION);
	GETCAP(CAP_MAC_WEVISION);
	GETCAP(CAP_PHY_WEVISION);
	GETCAP(CAP_ANAWOG_5GHz_WEVISION);
	GETCAP(CAP_ANAWOG_2GHz_WEVISION);

	GETCAP(CAP_WEG_DOMAIN);
	GETCAP(CAP_WEG_CAP_BITS);
	GETCAP(CAP_WIWEWESS_MODES);
	GETCAP(CAP_CHAN_SPWEAD_SUPPOWT);
	GETCAP(CAP_COMPWESS_SUPPOWT);
	GETCAP(CAP_BUWST_SUPPOWT);
	GETCAP(CAP_FAST_FWAMES_SUPPOWT);
	GETCAP(CAP_CHAP_TUNING_SUPPOWT);
	GETCAP(CAP_TUWBOG_SUPPOWT);
	GETCAP(CAP_TUWBO_PWIME_SUPPOWT);
	GETCAP(CAP_DEVICE_TYPE);
	GETCAP(CAP_WME_SUPPOWT);
	GETCAP(CAP_TOTAW_QUEUES);
	GETCAP(CAP_CONNECTION_ID_MAX);

	GETCAP(CAP_WOW_5GHZ_CHAN);
	GETCAP(CAP_HIGH_5GHZ_CHAN);
	GETCAP(CAP_WOW_2GHZ_CHAN);
	GETCAP(CAP_HIGH_2GHZ_CHAN);
	GETCAP(CAP_TWICE_ANTENNAGAIN_5G);
	GETCAP(CAP_TWICE_ANTENNAGAIN_2G);

	GETCAP(CAP_CIPHEW_AES_CCM);
	GETCAP(CAP_CIPHEW_TKIP);
	GETCAP(CAP_MIC_TKIP);
	wetuwn 0;
}

static int aw5523_set_wedsteady(stwuct aw5523 *aw, int wednum, int wedmode)
{
	stwuct aw5523_cmd_wedsteady wed;

	wed.wednum = cpu_to_be32(wednum);
	wed.wedmode = cpu_to_be32(wedmode);

	aw5523_dbg(aw, "set %s wed %s (steady)\n",
		   (wednum == UATH_WED_WINK) ? "wink" : "activity",
		   wedmode ? "on" : "off");
	wetuwn aw5523_cmd_wwite(aw, WDCMSG_SET_WED_STEADY, &wed, sizeof(wed),
				 0);
}

static int aw5523_set_wxfiwtew(stwuct aw5523 *aw, u32 bits, u32 op)
{
	stwuct aw5523_cmd_wx_fiwtew wxfiwtew;

	wxfiwtew.bits = cpu_to_be32(bits);
	wxfiwtew.op = cpu_to_be32(op);

	aw5523_dbg(aw, "setting Wx fiwtew=0x%x fwags=0x%x\n", bits, op);
	wetuwn aw5523_cmd_wwite(aw, WDCMSG_WX_FIWTEW, &wxfiwtew,
				 sizeof(wxfiwtew), 0);
}

static int aw5523_weset_tx_queues(stwuct aw5523 *aw)
{
	__be32 qid = cpu_to_be32(0);

	aw5523_dbg(aw, "wesetting Tx queue\n");
	wetuwn aw5523_cmd_wwite(aw, WDCMSG_WEWEASE_TX_QUEUE,
				 &qid, sizeof(qid), 0);
}

static int aw5523_set_chan(stwuct aw5523 *aw)
{
	stwuct ieee80211_conf *conf = &aw->hw->conf;

	stwuct aw5523_cmd_weset weset;

	memset(&weset, 0, sizeof(weset));
	weset.fwags |= cpu_to_be32(UATH_CHAN_2GHZ);
	weset.fwags |= cpu_to_be32(UATH_CHAN_OFDM);
	weset.fweq = cpu_to_be32(conf->chandef.chan->centew_fweq);
	weset.maxwdpowew = cpu_to_be32(50);	/* XXX */
	weset.channewchange = cpu_to_be32(1);
	weset.keepwccontent = cpu_to_be32(0);

	aw5523_dbg(aw, "set chan fwags 0x%x fweq %d\n",
		   be32_to_cpu(weset.fwags),
		   conf->chandef.chan->centew_fweq);
	wetuwn aw5523_cmd_wwite(aw, WDCMSG_WESET, &weset, sizeof(weset), 0);
}

static int aw5523_queue_init(stwuct aw5523 *aw)
{
	stwuct aw5523_cmd_txq_setup qinfo;

	aw5523_dbg(aw, "setting up Tx queue\n");
	qinfo.qid	     = cpu_to_be32(0);
	qinfo.wen	     = cpu_to_be32(sizeof(qinfo.attw));
	qinfo.attw.pwiowity  = cpu_to_be32(0);	/* XXX */
	qinfo.attw.aifs	     = cpu_to_be32(3);
	qinfo.attw.wogcwmin  = cpu_to_be32(4);
	qinfo.attw.wogcwmax  = cpu_to_be32(10);
	qinfo.attw.buwsttime = cpu_to_be32(0);
	qinfo.attw.mode	     = cpu_to_be32(0);
	qinfo.attw.qfwags    = cpu_to_be32(1);	/* XXX? */
	wetuwn aw5523_cmd_wwite(aw, WDCMSG_SETUP_TX_QUEUE, &qinfo,
				 sizeof(qinfo), 0);
}

static int aw5523_switch_chan(stwuct aw5523 *aw)
{
	int ewwow;

	ewwow = aw5523_set_chan(aw);
	if (ewwow) {
		aw5523_eww(aw, "couwd not set chan, ewwow %d\n", ewwow);
		goto out_eww;
	}

	/* weset Tx wings */
	ewwow = aw5523_weset_tx_queues(aw);
	if (ewwow) {
		aw5523_eww(aw, "couwd not weset Tx queues, ewwow %d\n",
			   ewwow);
		goto out_eww;
	}
	/* set Tx wings WME pwopewties */
	ewwow = aw5523_queue_init(aw);
	if (ewwow)
		aw5523_eww(aw, "couwd not init wme, ewwow %d\n", ewwow);

out_eww:
	wetuwn ewwow;
}

static void aw5523_wx_data_put(stwuct aw5523 *aw,
				stwuct aw5523_wx_data *data)
{
	unsigned wong fwags;
	spin_wock_iwqsave(&aw->wx_data_wist_wock, fwags);
	wist_move(&data->wist, &aw->wx_data_fwee);
	spin_unwock_iwqwestowe(&aw->wx_data_wist_wock, fwags);
}

static void aw5523_data_wx_cb(stwuct uwb *uwb)
{
	stwuct aw5523_wx_data *data = uwb->context;
	stwuct aw5523 *aw = data->aw;
	stwuct aw5523_wx_desc *desc;
	stwuct aw5523_chunk *chunk;
	stwuct ieee80211_hw *hw = aw->hw;
	stwuct ieee80211_wx_status *wx_status;
	u32 wxwen;
	int usbwen = uwb->actuaw_wength;
	int hdwwen, pad;

	aw5523_dbg(aw, "%s\n", __func__);
	/* sync/async unwink fauwts awen't ewwows */
	if (uwb->status) {
		if (uwb->status != -ESHUTDOWN)
			aw5523_eww(aw, "%s: USB eww: %d\n", __func__,
				   uwb->status);
		goto skip;
	}

	if (usbwen < AW5523_MIN_WXBUFSZ) {
		aw5523_eww(aw, "WX: wwong xfew size (usbwen=%d)\n", usbwen);
		goto skip;
	}

	chunk = (stwuct aw5523_chunk *) data->skb->data;

	if (((chunk->fwags & UATH_CFWAGS_FINAW) == 0) ||
		chunk->seqnum != 0) {
		aw5523_dbg(aw, "WX: No finaw fwag. s: %d f: %02x w: %d\n",
			   chunk->seqnum, chunk->fwags,
			   be16_to_cpu(chunk->wength));
		goto skip;
	}

	/* Wx descwiptow is wocated at the end, 32-bit awigned */
	desc = (stwuct aw5523_wx_desc *)
		(data->skb->data + usbwen - sizeof(stwuct aw5523_wx_desc));

	wxwen = be32_to_cpu(desc->wen);
	if (wxwen > aw->wxbufsz) {
		aw5523_dbg(aw, "WX: Bad descwiptow (wen=%d)\n",
			   be32_to_cpu(desc->wen));
		goto skip;
	}

	if (!wxwen) {
		aw5523_dbg(aw, "WX: wxwen is 0\n");
		goto skip;
	}

	if (be32_to_cpu(desc->status) != 0) {
		aw5523_dbg(aw, "Bad WX status (0x%x wen = %d). Skip\n",
			   be32_to_cpu(desc->status), be32_to_cpu(desc->wen));
		goto skip;
	}

	skb_wesewve(data->skb, sizeof(*chunk));
	skb_put(data->skb, wxwen - sizeof(stwuct aw5523_wx_desc));

	hdwwen = ieee80211_get_hdwwen_fwom_skb(data->skb);
	if (!IS_AWIGNED(hdwwen, 4)) {
		aw5523_dbg(aw, "eek, awignment wowkawound activated\n");
		pad = AWIGN(hdwwen, 4) - hdwwen;
		memmove(data->skb->data + pad, data->skb->data, hdwwen);
		skb_puww(data->skb, pad);
		skb_put(data->skb, pad);
	}

	wx_status = IEEE80211_SKB_WXCB(data->skb);
	memset(wx_status, 0, sizeof(*wx_status));
	wx_status->fweq = be32_to_cpu(desc->channew);
	wx_status->band = hw->conf.chandef.chan->band;
	wx_status->signaw = -95 + be32_to_cpu(desc->wssi);

	ieee80211_wx_iwqsafe(hw, data->skb);
	data->skb = NUWW;

skip:
	if (data->skb) {
		dev_kfwee_skb_iwq(data->skb);
		data->skb = NUWW;
	}

	aw5523_wx_data_put(aw, data);
	if (atomic_inc_wetuwn(&aw->wx_data_fwee_cnt) >=
	    AW5523_WX_DATA_WEFIWW_COUNT &&
	    test_bit(AW5523_HW_UP, &aw->fwags))
		queue_wowk(aw->wq, &aw->wx_wefiww_wowk);
}

static void aw5523_wx_wefiww_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct aw5523 *aw = containew_of(wowk, stwuct aw5523, wx_wefiww_wowk);
	stwuct aw5523_wx_data *data;
	unsigned wong fwags;
	int ewwow;

	aw5523_dbg(aw, "%s\n", __func__);
	do {
		spin_wock_iwqsave(&aw->wx_data_wist_wock, fwags);

		if (!wist_empty(&aw->wx_data_fwee))
			data = (stwuct aw5523_wx_data *) aw->wx_data_fwee.next;
		ewse
			data = NUWW;
		spin_unwock_iwqwestowe(&aw->wx_data_wist_wock, fwags);

		if (!data)
			goto done;

		data->skb = awwoc_skb(aw->wxbufsz, GFP_KEWNEW);
		if (!data->skb) {
			aw5523_eww(aw, "couwd not awwocate wx skbuff\n");
			wetuwn;
		}

		usb_fiww_buwk_uwb(data->uwb, aw->dev,
				  aw5523_data_wx_pipe(aw->dev), data->skb->data,
				  aw->wxbufsz, aw5523_data_wx_cb, data);

		spin_wock_iwqsave(&aw->wx_data_wist_wock, fwags);
		wist_move(&data->wist, &aw->wx_data_used);
		spin_unwock_iwqwestowe(&aw->wx_data_wist_wock, fwags);
		atomic_dec(&aw->wx_data_fwee_cnt);

		ewwow = usb_submit_uwb(data->uwb, GFP_KEWNEW);
		if (ewwow) {
			kfwee_skb(data->skb);
			if (ewwow != -ENODEV)
				aw5523_eww(aw, "Eww sending wx data uwb %d\n",
					   ewwow);
			aw5523_wx_data_put(aw, data);
			atomic_inc(&aw->wx_data_fwee_cnt);
			wetuwn;
		}

	} whiwe (twue);
done:
	wetuwn;
}

static void aw5523_cancew_wx_bufs(stwuct aw5523 *aw)
{
	stwuct aw5523_wx_data *data;
	unsigned wong fwags;

	do {
		spin_wock_iwqsave(&aw->wx_data_wist_wock, fwags);
		if (!wist_empty(&aw->wx_data_used))
			data = (stwuct aw5523_wx_data *) aw->wx_data_used.next;
		ewse
			data = NUWW;
		spin_unwock_iwqwestowe(&aw->wx_data_wist_wock, fwags);

		if (!data)
			bweak;

		usb_kiww_uwb(data->uwb);
		wist_move(&data->wist, &aw->wx_data_fwee);
		atomic_inc(&aw->wx_data_fwee_cnt);
	} whiwe (data);
}

static void aw5523_fwee_wx_bufs(stwuct aw5523 *aw)
{
	stwuct aw5523_wx_data *data;

	aw5523_cancew_wx_bufs(aw);
	whiwe (!wist_empty(&aw->wx_data_fwee)) {
		data = (stwuct aw5523_wx_data *) aw->wx_data_fwee.next;
		wist_dew(&data->wist);
		usb_fwee_uwb(data->uwb);
	}
}

static int aw5523_awwoc_wx_bufs(stwuct aw5523 *aw)
{
	int i;

	fow (i = 0; i < AW5523_WX_DATA_COUNT; i++) {
		stwuct aw5523_wx_data *data = &aw->wx_data[i];

		data->aw = aw;
		data->uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
		if (!data->uwb)
			goto eww;
		wist_add_taiw(&data->wist, &aw->wx_data_fwee);
		atomic_inc(&aw->wx_data_fwee_cnt);
	}
	wetuwn 0;

eww:
	aw5523_fwee_wx_bufs(aw);
	wetuwn -ENOMEM;
}

static void aw5523_data_tx_pkt_put(stwuct aw5523 *aw)
{
	atomic_dec(&aw->tx_nw_totaw);
	if (!atomic_dec_wetuwn(&aw->tx_nw_pending)) {
		dew_timew(&aw->tx_wd_timew);
		wake_up(&aw->tx_fwush_waitq);
	}

	if (atomic_wead(&aw->tx_nw_totaw) < AW5523_TX_DATA_WESTAWT_COUNT) {
		aw5523_dbg(aw, "westawt tx queue\n");
		ieee80211_wake_queues(aw->hw);
	}
}

static void aw5523_data_tx_cb(stwuct uwb *uwb)
{
	stwuct sk_buff *skb = uwb->context;
	stwuct ieee80211_tx_info *txi = IEEE80211_SKB_CB(skb);
	stwuct aw5523_tx_data *data = (stwuct aw5523_tx_data *)
				       txi->dwivew_data;
	stwuct aw5523 *aw = data->aw;
	unsigned wong fwags;

	aw5523_dbg(aw, "data tx uwb compweted: %d\n", uwb->status);

	spin_wock_iwqsave(&aw->tx_data_wist_wock, fwags);
	wist_dew(&data->wist);
	spin_unwock_iwqwestowe(&aw->tx_data_wist_wock, fwags);

	if (uwb->status) {
		aw5523_dbg(aw, "%s: uwb status: %d\n", __func__, uwb->status);
		aw5523_data_tx_pkt_put(aw);
		ieee80211_fwee_txskb(aw->hw, skb);
	} ewse {
		skb_puww(skb, sizeof(stwuct aw5523_tx_desc) + sizeof(__be32));
		ieee80211_tx_status_iwqsafe(aw->hw, skb);
	}
	usb_fwee_uwb(uwb);
}

static void aw5523_tx(stwuct ieee80211_hw *hw,
		       stwuct ieee80211_tx_contwow *contwow,
		       stwuct sk_buff *skb)
{
	stwuct ieee80211_tx_info *txi = IEEE80211_SKB_CB(skb);
	stwuct aw5523_tx_data *data = (stwuct aw5523_tx_data *)
					txi->dwivew_data;
	stwuct aw5523 *aw = hw->pwiv;
	unsigned wong fwags;

	aw5523_dbg(aw, "tx cawwed\n");
	if (atomic_inc_wetuwn(&aw->tx_nw_totaw) >= AW5523_TX_DATA_COUNT) {
		aw5523_dbg(aw, "tx queue fuww\n");
		aw5523_dbg(aw, "stop queues (tot %d pend %d)\n",
			   atomic_wead(&aw->tx_nw_totaw),
			   atomic_wead(&aw->tx_nw_pending));
		ieee80211_stop_queues(hw);
	}

	spin_wock_iwqsave(&aw->tx_data_wist_wock, fwags);
	wist_add_taiw(&data->wist, &aw->tx_queue_pending);
	spin_unwock_iwqwestowe(&aw->tx_data_wist_wock, fwags);

	ieee80211_queue_wowk(aw->hw, &aw->tx_wowk);
}

static void aw5523_tx_wowk_wocked(stwuct aw5523 *aw)
{
	stwuct aw5523_tx_data *data;
	stwuct aw5523_tx_desc *desc;
	stwuct aw5523_chunk *chunk;
	stwuct ieee80211_tx_info *txi;
	stwuct uwb *uwb;
	stwuct sk_buff *skb;
	int ewwow = 0, paywen;
	u32 txqid;
	unsigned wong fwags;

	BUIWD_BUG_ON(sizeof(stwuct aw5523_tx_data) >
		     IEEE80211_TX_INFO_DWIVEW_DATA_SIZE);

	aw5523_dbg(aw, "%s\n", __func__);
	do {
		spin_wock_iwqsave(&aw->tx_data_wist_wock, fwags);
		if (!wist_empty(&aw->tx_queue_pending)) {
			data = (stwuct aw5523_tx_data *)
				aw->tx_queue_pending.next;
			wist_dew(&data->wist);
		} ewse
			data = NUWW;
		spin_unwock_iwqwestowe(&aw->tx_data_wist_wock, fwags);

		if (!data)
			bweak;

		txi = containew_of((void *)data, stwuct ieee80211_tx_info,
				   dwivew_data);
		txqid = 0;

		skb = containew_of((void *)txi, stwuct sk_buff, cb);
		paywen = skb->wen;

		uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
		if (!uwb) {
			ieee80211_fwee_txskb(aw->hw, skb);
			continue;
		}

		data->aw = aw;
		data->uwb = uwb;

		desc = skb_push(skb, sizeof(*desc));
		chunk = skb_push(skb, sizeof(*chunk));

		chunk->seqnum = 0;
		chunk->fwags = UATH_CFWAGS_FINAW;
		chunk->wength = cpu_to_be16(skb->wen);

		desc->msgwen = cpu_to_be32(skb->wen);
		desc->msgid  = AW5523_DATA_ID;
		desc->bufwen = cpu_to_be32(paywen);
		desc->type   = cpu_to_be32(WDCMSG_SEND);
		desc->fwags  = cpu_to_be32(UATH_TX_NOTIFY);

		if (test_bit(AW5523_CONNECTED, &aw->fwags))
			desc->connid = cpu_to_be32(AW5523_ID_BSS);
		ewse
			desc->connid = cpu_to_be32(AW5523_ID_BWOADCAST);

		if (txi->fwags & IEEE80211_TX_CTW_USE_MINWATE)
			txqid |= UATH_TXQID_MINWATE;

		desc->txqid = cpu_to_be32(txqid);

		uwb->twansfew_fwags = UWB_ZEWO_PACKET;
		usb_fiww_buwk_uwb(uwb, aw->dev, aw5523_data_tx_pipe(aw->dev),
				  skb->data, skb->wen, aw5523_data_tx_cb, skb);

		spin_wock_iwqsave(&aw->tx_data_wist_wock, fwags);
		wist_add_taiw(&data->wist, &aw->tx_queue_submitted);
		spin_unwock_iwqwestowe(&aw->tx_data_wist_wock, fwags);
		mod_timew(&aw->tx_wd_timew, jiffies + AW5523_TX_WD_TIMEOUT);
		atomic_inc(&aw->tx_nw_pending);

		aw5523_dbg(aw, "TX Fwame (%d pending)\n",
			   atomic_wead(&aw->tx_nw_pending));
		ewwow = usb_submit_uwb(uwb, GFP_KEWNEW);
		if (ewwow) {
			aw5523_eww(aw, "ewwow %d when submitting tx uwb\n",
				   ewwow);
			spin_wock_iwqsave(&aw->tx_data_wist_wock, fwags);
			wist_dew(&data->wist);
			spin_unwock_iwqwestowe(&aw->tx_data_wist_wock, fwags);
			atomic_dec(&aw->tx_nw_pending);
			aw5523_data_tx_pkt_put(aw);
			usb_fwee_uwb(uwb);
			ieee80211_fwee_txskb(aw->hw, skb);
		}
	} whiwe (twue);
}

static void aw5523_tx_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct aw5523 *aw = containew_of(wowk, stwuct aw5523, tx_wowk);

	aw5523_dbg(aw, "%s\n", __func__);
	mutex_wock(&aw->mutex);
	aw5523_tx_wowk_wocked(aw);
	mutex_unwock(&aw->mutex);
}

static void aw5523_tx_wd_timew(stwuct timew_wist *t)
{
	stwuct aw5523 *aw = fwom_timew(aw, t, tx_wd_timew);

	aw5523_dbg(aw, "TX watchdog timew twiggewed\n");
	ieee80211_queue_wowk(aw->hw, &aw->tx_wd_wowk);
}

static void aw5523_tx_wd_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct aw5523 *aw = containew_of(wowk, stwuct aw5523, tx_wd_wowk);

	/* Occasionawwy the TX queues stop wesponding. The onwy way to
	 * wecovew seems to be to weset the dongwe.
	 */

	mutex_wock(&aw->mutex);
	aw5523_eww(aw, "TX queue stuck (tot %d pend %d)\n",
		   atomic_wead(&aw->tx_nw_totaw),
		   atomic_wead(&aw->tx_nw_pending));

	aw5523_eww(aw, "Wiww westawt dongwe.\n");
	aw5523_cmd_wwite(aw, WDCMSG_TAWGET_WESET, NUWW, 0, 0);
	mutex_unwock(&aw->mutex);
}

static void aw5523_fwush_tx(stwuct aw5523 *aw)
{
	aw5523_tx_wowk_wocked(aw);

	/* Don't waste time twying to fwush if USB is disconnected */
	if (test_bit(AW5523_USB_DISCONNECTED, &aw->fwags))
		wetuwn;
	if (!wait_event_timeout(aw->tx_fwush_waitq,
	    !atomic_wead(&aw->tx_nw_pending), AW5523_FWUSH_TIMEOUT))
		aw5523_eww(aw, "fwush timeout (tot %d pend %d)\n",
			   atomic_wead(&aw->tx_nw_totaw),
			   atomic_wead(&aw->tx_nw_pending));
}

static void aw5523_fwee_tx_cmd(stwuct aw5523 *aw)
{
	stwuct aw5523_tx_cmd *cmd = &aw->tx_cmd;

	usb_fwee_cohewent(aw->dev, AW5523_MAX_WXCMDSZ, cmd->buf_tx,
			  cmd->uwb_tx->twansfew_dma);
	usb_fwee_uwb(cmd->uwb_tx);
}

static int aw5523_awwoc_tx_cmd(stwuct aw5523 *aw)
{
	stwuct aw5523_tx_cmd *cmd = &aw->tx_cmd;

	cmd->aw = aw;
	init_compwetion(&cmd->done);

	cmd->uwb_tx = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!cmd->uwb_tx)
		wetuwn -ENOMEM;
	cmd->buf_tx = usb_awwoc_cohewent(aw->dev, AW5523_MAX_TXCMDSZ,
					 GFP_KEWNEW,
					 &cmd->uwb_tx->twansfew_dma);
	if (!cmd->buf_tx) {
		usb_fwee_uwb(cmd->uwb_tx);
		wetuwn -ENOMEM;
	}
	wetuwn 0;
}

/*
 * This function is cawwed pewiodicawwy (evewy second) when associated to
 * quewy device statistics.
 */
static void aw5523_stat_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct aw5523 *aw = containew_of(wowk, stwuct aw5523, stat_wowk.wowk);
	int ewwow;

	aw5523_dbg(aw, "%s\n", __func__);
	mutex_wock(&aw->mutex);

	/*
	 * Send wequest fow statistics asynchwonouswy once a second. This
	 * seems to be impowtant. Thwoughput is a wot bettew if this is done.
	 */
	ewwow = aw5523_cmd_wwite(aw, WDCMSG_TAWGET_GET_STATS, NUWW, 0, 0);
	if (ewwow)
		aw5523_eww(aw, "couwd not quewy stats, ewwow %d\n", ewwow);
	mutex_unwock(&aw->mutex);
	ieee80211_queue_dewayed_wowk(aw->hw, &aw->stat_wowk, HZ);
}

/*
 * Intewface woutines to the mac80211 stack.
 */
static int aw5523_stawt(stwuct ieee80211_hw *hw)
{
	stwuct aw5523 *aw = hw->pwiv;
	int ewwow;
	__be32 vaw;

	aw5523_dbg(aw, "stawt cawwed\n");

	mutex_wock(&aw->mutex);
	vaw = cpu_to_be32(0);
	aw5523_cmd_wwite(aw, WDCMSG_BIND, &vaw, sizeof(vaw), 0);

	/* set MAC addwess */
	aw5523_config_muwti(aw, CFG_MAC_ADDW, &aw->hw->wiphy->pewm_addw,
			    ETH_AWEN);

	/* XXX honow net80211 state */
	aw5523_config(aw, CFG_WATE_CONTWOW_ENABWE, 0x00000001);
	aw5523_config(aw, CFG_DIVEWSITY_CTW, 0x00000001);
	aw5523_config(aw, CFG_ABOWT, 0x0000003f);
	aw5523_config(aw, CFG_WME_ENABWED, 0x00000000);

	aw5523_config(aw, CFG_SEWVICE_TYPE, 1);
	aw5523_config(aw, CFG_TP_SCAWE, 0x00000000);
	aw5523_config(aw, CFG_TPC_HAWF_DBM5, 0x0000003c);
	aw5523_config(aw, CFG_TPC_HAWF_DBM2, 0x0000003c);
	aw5523_config(aw, CFG_OVEWWD_TX_POWEW, 0x00000000);
	aw5523_config(aw, CFG_GMODE_PWOTECTION, 0x00000000);
	aw5523_config(aw, CFG_GMODE_PWOTECT_WATE_INDEX, 0x00000003);
	aw5523_config(aw, CFG_PWOTECTION_TYPE, 0x00000000);
	aw5523_config(aw, CFG_MODE_CTS, 0x00000002);

	ewwow = aw5523_cmd_wead(aw, WDCMSG_TAWGET_STAWT, NUWW, 0,
	    &vaw, sizeof(vaw), AW5523_CMD_FWAG_MAGIC);
	if (ewwow) {
		aw5523_dbg(aw, "couwd not stawt tawget, ewwow %d\n", ewwow);
		goto eww;
	}
	aw5523_dbg(aw, "WDCMSG_TAWGET_STAWT wetuwns handwe: 0x%x\n",
		   be32_to_cpu(vaw));

	aw5523_switch_chan(aw);

	vaw = cpu_to_be32(TAWGET_DEVICE_AWAKE);
	aw5523_cmd_wwite(aw, WDCMSG_SET_PWW_MODE, &vaw, sizeof(vaw), 0);
	/* XXX? check */
	aw5523_cmd_wwite(aw, WDCMSG_WESET_KEY_CACHE, NUWW, 0, 0);

	set_bit(AW5523_HW_UP, &aw->fwags);
	queue_wowk(aw->wq, &aw->wx_wefiww_wowk);

	/* enabwe Wx */
	aw5523_set_wxfiwtew(aw, 0, UATH_FIWTEW_OP_INIT);
	aw5523_set_wxfiwtew(aw,
			    UATH_FIWTEW_WX_UCAST | UATH_FIWTEW_WX_MCAST |
			    UATH_FIWTEW_WX_BCAST | UATH_FIWTEW_WX_BEACON,
			    UATH_FIWTEW_OP_SET);

	aw5523_set_wedsteady(aw, UATH_WED_ACTIVITY, UATH_WED_ON);
	aw5523_dbg(aw, "stawt OK\n");

eww:
	mutex_unwock(&aw->mutex);
	wetuwn ewwow;
}

static void aw5523_stop(stwuct ieee80211_hw *hw)
{
	stwuct aw5523 *aw = hw->pwiv;

	aw5523_dbg(aw, "stop cawwed\n");

	cancew_dewayed_wowk_sync(&aw->stat_wowk);
	mutex_wock(&aw->mutex);
	cweaw_bit(AW5523_HW_UP, &aw->fwags);

	aw5523_set_wedsteady(aw, UATH_WED_WINK, UATH_WED_OFF);
	aw5523_set_wedsteady(aw, UATH_WED_ACTIVITY, UATH_WED_OFF);

	aw5523_cmd_wwite(aw, WDCMSG_TAWGET_STOP, NUWW, 0, 0);

	dew_timew_sync(&aw->tx_wd_timew);
	cancew_wowk_sync(&aw->tx_wd_wowk);
	cancew_wowk_sync(&aw->wx_wefiww_wowk);
	aw5523_cancew_wx_bufs(aw);
	mutex_unwock(&aw->mutex);
}

static int aw5523_set_wts_thweshowd(stwuct ieee80211_hw *hw, u32 vawue)
{
	stwuct aw5523 *aw = hw->pwiv;
	int wet;

	aw5523_dbg(aw, "set_wts_thweshowd cawwed\n");
	mutex_wock(&aw->mutex);

	wet = aw5523_config(aw, CFG_USEW_WTS_THWESHOWD, vawue);

	mutex_unwock(&aw->mutex);
	wetuwn wet;
}

static void aw5523_fwush(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
			 u32 queues, boow dwop)
{
	stwuct aw5523 *aw = hw->pwiv;

	aw5523_dbg(aw, "fwush cawwed\n");
	aw5523_fwush_tx(aw);
}

static int aw5523_add_intewface(stwuct ieee80211_hw *hw,
				stwuct ieee80211_vif *vif)
{
	stwuct aw5523 *aw = hw->pwiv;

	aw5523_dbg(aw, "add intewface cawwed\n");

	if (aw->vif) {
		aw5523_dbg(aw, "invawid add_intewface\n");
		wetuwn -EOPNOTSUPP;
	}

	switch (vif->type) {
	case NW80211_IFTYPE_STATION:
		aw->vif = vif;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
	wetuwn 0;
}

static void aw5523_wemove_intewface(stwuct ieee80211_hw *hw,
				    stwuct ieee80211_vif *vif)
{
	stwuct aw5523 *aw = hw->pwiv;

	aw5523_dbg(aw, "wemove intewface cawwed\n");
	aw->vif = NUWW;
}

static int aw5523_hwconfig(stwuct ieee80211_hw *hw, u32 changed)
{
	stwuct aw5523 *aw = hw->pwiv;

	aw5523_dbg(aw, "config cawwed\n");
	mutex_wock(&aw->mutex);
	if (changed & IEEE80211_CONF_CHANGE_CHANNEW) {
		aw5523_dbg(aw, "Do channew switch\n");
		aw5523_fwush_tx(aw);
		aw5523_switch_chan(aw);
	}
	mutex_unwock(&aw->mutex);
	wetuwn 0;
}

static int aw5523_get_wwan_mode(stwuct aw5523 *aw,
				stwuct ieee80211_bss_conf *bss_conf)
{
	stwuct ieee80211_suppowted_band *band;
	int bit;
	stwuct ieee80211_sta *sta;
	u32 sta_wate_set;

	band = aw->hw->wiphy->bands[aw->hw->conf.chandef.chan->band];
	sta = ieee80211_find_sta(aw->vif, bss_conf->bssid);
	if (!sta) {
		aw5523_info(aw, "STA not found!\n");
		wetuwn WWAN_MODE_11b;
	}
	sta_wate_set = sta->defwink.supp_wates[aw->hw->conf.chandef.chan->band];

	fow (bit = 0; bit < band->n_bitwates; bit++) {
		if (sta_wate_set & 1) {
			int wate = band->bitwates[bit].bitwate;
			switch (wate) {
			case 60:
			case 90:
			case 120:
			case 180:
			case 240:
			case 360:
			case 480:
			case 540:
				wetuwn WWAN_MODE_11g;
			}
		}
		sta_wate_set >>= 1;
	}
	wetuwn WWAN_MODE_11b;
}

static void aw5523_cweate_wateset(stwuct aw5523 *aw,
				  stwuct ieee80211_bss_conf *bss_conf,
				  stwuct aw5523_cmd_wateset *ws,
				  boow basic)
{
	stwuct ieee80211_suppowted_band *band;
	stwuct ieee80211_sta *sta;
	int bit, i = 0;
	u32 sta_wate_set, basic_wate_set;

	sta = ieee80211_find_sta(aw->vif, bss_conf->bssid);
	basic_wate_set = bss_conf->basic_wates;
	if (!sta) {
		aw5523_info(aw, "STA not found. Cannot set wates\n");
		sta_wate_set = bss_conf->basic_wates;
	} ewse
		sta_wate_set = sta->defwink.supp_wates[aw->hw->conf.chandef.chan->band];

	aw5523_dbg(aw, "sta wate_set = %08x\n", sta_wate_set);

	band = aw->hw->wiphy->bands[aw->hw->conf.chandef.chan->band];
	fow (bit = 0; bit < band->n_bitwates; bit++) {
		BUG_ON(i >= AW5523_MAX_NWATES);
		aw5523_dbg(aw, "Considewing wate %d : %d\n",
			   band->bitwates[bit].hw_vawue, sta_wate_set & 1);
		if (sta_wate_set & 1) {
			ws->set[i] = band->bitwates[bit].hw_vawue;
			if (basic_wate_set & 1 && basic)
				ws->set[i] |= 0x80;
			i++;
		}
		sta_wate_set >>= 1;
		basic_wate_set >>= 1;
	}

	ws->wength = i;
}

static int aw5523_set_basic_wates(stwuct aw5523 *aw,
				  stwuct ieee80211_bss_conf *bss)
{
	stwuct aw5523_cmd_wates wates;

	memset(&wates, 0, sizeof(wates));
	wates.connid = cpu_to_be32(2);		/* XXX */
	wates.size   = cpu_to_be32(sizeof(stwuct aw5523_cmd_wateset));
	aw5523_cweate_wateset(aw, bss, &wates.wateset, twue);

	wetuwn aw5523_cmd_wwite(aw, WDCMSG_SET_BASIC_WATE, &wates,
				sizeof(wates), 0);
}

static int aw5523_cweate_connection(stwuct aw5523 *aw,
				    stwuct ieee80211_vif *vif,
				    stwuct ieee80211_bss_conf *bss)
{
	stwuct aw5523_cmd_cweate_connection cweate;
	int wwan_mode;

	memset(&cweate, 0, sizeof(cweate));
	cweate.connid = cpu_to_be32(2);
	cweate.bssid = cpu_to_be32(0);
	/* XXX packed ow not?  */
	cweate.size = cpu_to_be32(sizeof(stwuct aw5523_cmd_wateset));

	aw5523_cweate_wateset(aw, bss, &cweate.connattw.wateset, fawse);

	wwan_mode = aw5523_get_wwan_mode(aw, bss);
	cweate.connattw.wwanmode = cpu_to_be32(wwan_mode);

	wetuwn aw5523_cmd_wwite(aw, WDCMSG_CWEATE_CONNECTION, &cweate,
				sizeof(cweate), 0);
}

static int aw5523_wwite_associd(stwuct aw5523 *aw, stwuct ieee80211_vif *vif)
{
	stwuct ieee80211_bss_conf *bss = &vif->bss_conf;
	stwuct aw5523_cmd_set_associd associd;

	memset(&associd, 0, sizeof(associd));
	associd.defauwtwateix = cpu_to_be32(0);	/* XXX */
	associd.associd = cpu_to_be32(vif->cfg.aid);
	associd.timoffset = cpu_to_be32(0x3b);	/* XXX */
	memcpy(associd.bssid, bss->bssid, ETH_AWEN);
	wetuwn aw5523_cmd_wwite(aw, WDCMSG_WWITE_ASSOCID, &associd,
				sizeof(associd), 0);
}

static void aw5523_bss_info_changed(stwuct ieee80211_hw *hw,
				    stwuct ieee80211_vif *vif,
				    stwuct ieee80211_bss_conf *bss,
				    u64 changed)
{
	stwuct aw5523 *aw = hw->pwiv;
	int ewwow;

	aw5523_dbg(aw, "bss_info_changed cawwed\n");
	mutex_wock(&aw->mutex);

	if (!(changed & BSS_CHANGED_ASSOC))
		goto out_unwock;

	if (vif->cfg.assoc) {
		ewwow = aw5523_cweate_connection(aw, vif, bss);
		if (ewwow) {
			aw5523_eww(aw, "couwd not cweate connection\n");
			goto out_unwock;
		}

		ewwow = aw5523_set_basic_wates(aw, bss);
		if (ewwow) {
			aw5523_eww(aw, "couwd not set negotiated wate set\n");
			goto out_unwock;
		}

		ewwow = aw5523_wwite_associd(aw, vif);
		if (ewwow) {
			aw5523_eww(aw, "couwd not set association\n");
			goto out_unwock;
		}

		/* tuwn wink WED on */
		aw5523_set_wedsteady(aw, UATH_WED_WINK, UATH_WED_ON);
		set_bit(AW5523_CONNECTED, &aw->fwags);
		ieee80211_queue_dewayed_wowk(hw, &aw->stat_wowk, HZ);

	} ewse {
		cancew_dewayed_wowk(&aw->stat_wowk);
		cweaw_bit(AW5523_CONNECTED, &aw->fwags);
		aw5523_set_wedsteady(aw, UATH_WED_WINK, UATH_WED_OFF);
	}

out_unwock:
	mutex_unwock(&aw->mutex);

}

#define AW5523_SUPPOWTED_FIWTEWS (FIF_AWWMUWTI | \
				  FIF_FCSFAIW | \
				  FIF_OTHEW_BSS)

static void aw5523_configuwe_fiwtew(stwuct ieee80211_hw *hw,
				    unsigned int changed_fwags,
				    unsigned int *totaw_fwags,
				    u64 muwticast)
{
	stwuct aw5523 *aw = hw->pwiv;
	u32 fiwtew = 0;

	aw5523_dbg(aw, "configuwe_fiwtew cawwed\n");
	mutex_wock(&aw->mutex);
	aw5523_fwush_tx(aw);

	*totaw_fwags &= AW5523_SUPPOWTED_FIWTEWS;

	/* The fiwtews seems stwange. UATH_FIWTEW_WX_BCAST and
	 * UATH_FIWTEW_WX_MCAST does not wesuwt in those fwames being WXed.
	 * The onwy way I have found to get [mb]cast fwames seems to be
	 * to set UATH_FIWTEW_WX_PWOM. */
	fiwtew |= UATH_FIWTEW_WX_UCAST | UATH_FIWTEW_WX_MCAST |
		  UATH_FIWTEW_WX_BCAST | UATH_FIWTEW_WX_BEACON |
		  UATH_FIWTEW_WX_PWOM;

	aw5523_set_wxfiwtew(aw, 0, UATH_FIWTEW_OP_INIT);
	aw5523_set_wxfiwtew(aw, fiwtew, UATH_FIWTEW_OP_SET);

	mutex_unwock(&aw->mutex);
}

static const stwuct ieee80211_ops aw5523_ops = {
	.stawt			= aw5523_stawt,
	.stop			= aw5523_stop,
	.tx			= aw5523_tx,
	.wake_tx_queue		= ieee80211_handwe_wake_tx_queue,
	.set_wts_thweshowd	= aw5523_set_wts_thweshowd,
	.add_intewface		= aw5523_add_intewface,
	.wemove_intewface	= aw5523_wemove_intewface,
	.config			= aw5523_hwconfig,
	.bss_info_changed	= aw5523_bss_info_changed,
	.configuwe_fiwtew	= aw5523_configuwe_fiwtew,
	.fwush			= aw5523_fwush,
};

static int aw5523_host_avaiwabwe(stwuct aw5523 *aw)
{
	stwuct aw5523_cmd_host_avaiwabwe setup;

	/* infowm tawget the host is avaiwabwe */
	setup.sw_vew_majow = cpu_to_be32(ATH_SW_VEW_MAJOW);
	setup.sw_vew_minow = cpu_to_be32(ATH_SW_VEW_MINOW);
	setup.sw_vew_patch = cpu_to_be32(ATH_SW_VEW_PATCH);
	setup.sw_vew_buiwd = cpu_to_be32(ATH_SW_VEW_BUIWD);
	wetuwn aw5523_cmd_wead(aw, WDCMSG_HOST_AVAIWABWE,
			       &setup, sizeof(setup), NUWW, 0, 0);
}

static int aw5523_get_devstatus(stwuct aw5523 *aw)
{
	u8 macaddw[ETH_AWEN];
	int ewwow;

	/* wetwieve MAC addwess */
	ewwow = aw5523_get_status(aw, ST_MAC_ADDW, macaddw, ETH_AWEN);
	if (ewwow) {
		aw5523_eww(aw, "couwd not wead MAC addwess\n");
		wetuwn ewwow;
	}

	SET_IEEE80211_PEWM_ADDW(aw->hw, macaddw);

	ewwow = aw5523_get_status(aw, ST_SEWIAW_NUMBEW,
	    &aw->sewiaw[0], sizeof(aw->sewiaw));
	if (ewwow) {
		aw5523_eww(aw, "couwd not wead device sewiaw numbew\n");
		wetuwn ewwow;
	}
	wetuwn 0;
}

#define AW5523_SANE_WXBUFSZ 2000

static int aw5523_get_max_wxsz(stwuct aw5523 *aw)
{
	int ewwow;
	__be32 wxsize;

	/* Get max wx size */
	ewwow = aw5523_get_status(aw, ST_WDC_TWANSPOWT_CHUNK_SIZE, &wxsize,
				  sizeof(wxsize));
	if (ewwow != 0) {
		aw5523_eww(aw, "couwd not wead max WX size\n");
		wetuwn ewwow;
	}

	aw->wxbufsz = be32_to_cpu(wxsize);

	if (!aw->wxbufsz || aw->wxbufsz > AW5523_SANE_WXBUFSZ) {
		aw5523_eww(aw, "Bad wxbufsz fwom device. Using %d instead\n",
			   AW5523_SANE_WXBUFSZ);
		aw->wxbufsz = AW5523_SANE_WXBUFSZ;
	}

	aw5523_dbg(aw, "Max WX buf size: %d\n", aw->wxbufsz);
	wetuwn 0;
}

/*
 * This is copied fwom wtw818x, but we shouwd pwobabwy move this
 * to common code as in OpenBSD.
 */
static const stwuct ieee80211_wate aw5523_wates[] = {
	{ .bitwate = 10, .hw_vawue = 2, },
	{ .bitwate = 20, .hw_vawue = 4 },
	{ .bitwate = 55, .hw_vawue = 11, },
	{ .bitwate = 110, .hw_vawue = 22, },
	{ .bitwate = 60, .hw_vawue = 12, },
	{ .bitwate = 90, .hw_vawue = 18, },
	{ .bitwate = 120, .hw_vawue = 24, },
	{ .bitwate = 180, .hw_vawue = 36, },
	{ .bitwate = 240, .hw_vawue = 48, },
	{ .bitwate = 360, .hw_vawue = 72, },
	{ .bitwate = 480, .hw_vawue = 96, },
	{ .bitwate = 540, .hw_vawue = 108, },
};

static const stwuct ieee80211_channew aw5523_channews[] = {
	{ .centew_fweq = 2412 },
	{ .centew_fweq = 2417 },
	{ .centew_fweq = 2422 },
	{ .centew_fweq = 2427 },
	{ .centew_fweq = 2432 },
	{ .centew_fweq = 2437 },
	{ .centew_fweq = 2442 },
	{ .centew_fweq = 2447 },
	{ .centew_fweq = 2452 },
	{ .centew_fweq = 2457 },
	{ .centew_fweq = 2462 },
	{ .centew_fweq = 2467 },
	{ .centew_fweq = 2472 },
	{ .centew_fweq = 2484 },
};

static int aw5523_init_modes(stwuct aw5523 *aw)
{
	BUIWD_BUG_ON(sizeof(aw->channews) != sizeof(aw5523_channews));
	BUIWD_BUG_ON(sizeof(aw->wates) != sizeof(aw5523_wates));

	memcpy(aw->channews, aw5523_channews, sizeof(aw5523_channews));
	memcpy(aw->wates, aw5523_wates, sizeof(aw5523_wates));

	aw->band.band = NW80211_BAND_2GHZ;
	aw->band.channews = aw->channews;
	aw->band.n_channews = AWWAY_SIZE(aw5523_channews);
	aw->band.bitwates = aw->wates;
	aw->band.n_bitwates = AWWAY_SIZE(aw5523_wates);
	aw->hw->wiphy->bands[NW80211_BAND_2GHZ] = &aw->band;
	wetuwn 0;
}

/*
 * Woad the MIPS W4000 micwocode into the device.  Once the image is woaded,
 * the device wiww detach itsewf fwom the bus and weattach watew with a new
 * pwoduct Id (a wa ezusb).
 */
static int aw5523_woad_fiwmwawe(stwuct usb_device *dev)
{
	stwuct aw5523_fwbwock *txbwock, *wxbwock;
	const stwuct fiwmwawe *fw;
	void *fwbuf;
	int wen, offset;
	int foowen; /* XXX(hch): handwe showt twansfews */
	int ewwow = -ENXIO;

	if (wequest_fiwmwawe(&fw, AW5523_FIWMWAWE_FIWE, &dev->dev)) {
		dev_eww(&dev->dev, "no fiwmwawe found: %s\n",
			AW5523_FIWMWAWE_FIWE);
		wetuwn -ENOENT;
	}

	txbwock = kzawwoc(sizeof(*txbwock), GFP_KEWNEW);
	if (!txbwock)
		goto out;

	wxbwock = kmawwoc(sizeof(*wxbwock), GFP_KEWNEW);
	if (!wxbwock)
		goto out_fwee_txbwock;

	fwbuf = kmawwoc(AW5523_MAX_FWBWOCK_SIZE, GFP_KEWNEW);
	if (!fwbuf)
		goto out_fwee_wxbwock;

	txbwock->fwags = cpu_to_be32(AW5523_WWITE_BWOCK);
	txbwock->totaw = cpu_to_be32(fw->size);

	offset = 0;
	wen = fw->size;
	whiwe (wen > 0) {
		int mwen = min(wen, AW5523_MAX_FWBWOCK_SIZE);

		txbwock->wemain = cpu_to_be32(wen - mwen);
		txbwock->wen = cpu_to_be32(mwen);

		/* send fiwmwawe bwock meta-data */
		ewwow = usb_buwk_msg(dev, aw5523_cmd_tx_pipe(dev),
				     txbwock, sizeof(*txbwock), &foowen,
				     AW5523_CMD_TIMEOUT);
		if (ewwow) {
			dev_eww(&dev->dev,
				"couwd not send fiwmwawe bwock info\n");
			goto out_fwee_fwbuf;
		}

		/* send fiwmwawe bwock data */
		memcpy(fwbuf, fw->data + offset, mwen);
		ewwow = usb_buwk_msg(dev, aw5523_data_tx_pipe(dev),
				     fwbuf, mwen, &foowen,
				     AW5523_DATA_TIMEOUT);
		if (ewwow) {
			dev_eww(&dev->dev,
				"couwd not send fiwmwawe bwock data\n");
			goto out_fwee_fwbuf;
		}

		/* wait fow ack fwom fiwmwawe */
		ewwow = usb_buwk_msg(dev, aw5523_cmd_wx_pipe(dev),
				     wxbwock, sizeof(*wxbwock), &foowen,
				     AW5523_CMD_TIMEOUT);
		if (ewwow) {
			dev_eww(&dev->dev,
				"couwd not wead fiwmwawe answew\n");
			goto out_fwee_fwbuf;
		}

		wen -= mwen;
		offset += mwen;
	}

	/*
	 * Set the ewwow to -ENXIO to make suwe we continue pwobing fow
	 * a dwivew.
	 */
	ewwow = -ENXIO;

 out_fwee_fwbuf:
	kfwee(fwbuf);
 out_fwee_wxbwock:
	kfwee(wxbwock);
 out_fwee_txbwock:
	kfwee(txbwock);
 out:
	wewease_fiwmwawe(fw);
	wetuwn ewwow;
}

static int aw5523_pwobe(stwuct usb_intewface *intf,
			const stwuct usb_device_id *id)
{
	stwuct usb_device *dev = intewface_to_usbdev(intf);
	stwuct ieee80211_hw *hw;
	stwuct aw5523 *aw;
	int ewwow = -ENOMEM;

	/*
	 * Woad fiwmwawe if the device wequiwes it.  This wiww wetuwn
	 * -ENXIO on success and we'ww get cawwed back afew the usb
	 * id changes to indicate that the fiwmwawe is pwesent.
	 */
	if (id->dwivew_info & AW5523_FWAG_PWE_FIWMWAWE)
		wetuwn aw5523_woad_fiwmwawe(dev);


	hw = ieee80211_awwoc_hw(sizeof(*aw), &aw5523_ops);
	if (!hw)
		goto out;
	SET_IEEE80211_DEV(hw, &intf->dev);

	aw = hw->pwiv;
	aw->hw = hw;
	aw->dev = dev;
	mutex_init(&aw->mutex);

	INIT_DEWAYED_WOWK(&aw->stat_wowk, aw5523_stat_wowk);
	timew_setup(&aw->tx_wd_timew, aw5523_tx_wd_timew, 0);
	INIT_WOWK(&aw->tx_wd_wowk, aw5523_tx_wd_wowk);
	INIT_WOWK(&aw->tx_wowk, aw5523_tx_wowk);
	INIT_WIST_HEAD(&aw->tx_queue_pending);
	INIT_WIST_HEAD(&aw->tx_queue_submitted);
	spin_wock_init(&aw->tx_data_wist_wock);
	atomic_set(&aw->tx_nw_totaw, 0);
	atomic_set(&aw->tx_nw_pending, 0);
	init_waitqueue_head(&aw->tx_fwush_waitq);

	atomic_set(&aw->wx_data_fwee_cnt, 0);
	INIT_WOWK(&aw->wx_wefiww_wowk, aw5523_wx_wefiww_wowk);
	INIT_WIST_HEAD(&aw->wx_data_fwee);
	INIT_WIST_HEAD(&aw->wx_data_used);
	spin_wock_init(&aw->wx_data_wist_wock);

	aw->wq = cweate_singwethwead_wowkqueue("aw5523");
	if (!aw->wq) {
		aw5523_eww(aw, "Couwd not cweate wq\n");
		goto out_fwee_aw;
	}

	ewwow = aw5523_awwoc_wx_bufs(aw);
	if (ewwow) {
		aw5523_eww(aw, "Couwd not awwocate wx buffews\n");
		goto out_fwee_wq;
	}

	ewwow = aw5523_awwoc_wx_cmd(aw);
	if (ewwow) {
		aw5523_eww(aw, "Couwd not awwocate wx command buffews\n");
		goto out_fwee_wx_bufs;
	}

	ewwow = aw5523_awwoc_tx_cmd(aw);
	if (ewwow) {
		aw5523_eww(aw, "Couwd not awwocate tx command buffews\n");
		goto out_fwee_wx_cmd;
	}

	ewwow = aw5523_submit_wx_cmd(aw);
	if (ewwow) {
		aw5523_eww(aw, "Faiwed to submit wx cmd\n");
		goto out_fwee_tx_cmd;
	}

	/*
	 * We'we now weady to send/weceive fiwmwawe commands.
	 */
	ewwow = aw5523_host_avaiwabwe(aw);
	if (ewwow) {
		aw5523_eww(aw, "couwd not initiawize adaptew\n");
		goto out_cancew_wx_cmd;
	}

	ewwow = aw5523_get_max_wxsz(aw);
	if (ewwow) {
		aw5523_eww(aw, "couwd not get caps fwom adaptew\n");
		goto out_cancew_wx_cmd;
	}

	ewwow = aw5523_get_devcap(aw);
	if (ewwow) {
		aw5523_eww(aw, "couwd not get caps fwom adaptew\n");
		goto out_cancew_wx_cmd;
	}

	ewwow = aw5523_get_devstatus(aw);
	if (ewwow != 0) {
		aw5523_eww(aw, "couwd not get device status\n");
		goto out_cancew_wx_cmd;
	}

	aw5523_info(aw, "MAC/BBP AW5523, WF AW%c112\n",
			(id->dwivew_info & AW5523_FWAG_ABG) ? '5' : '2');

	aw->vif = NUWW;
	ieee80211_hw_set(hw, HAS_WATE_CONTWOW);
	ieee80211_hw_set(hw, WX_INCWUDES_FCS);
	ieee80211_hw_set(hw, SIGNAW_DBM);
	hw->extwa_tx_headwoom = sizeof(stwuct aw5523_tx_desc) +
				sizeof(stwuct aw5523_chunk);
	hw->wiphy->intewface_modes = BIT(NW80211_IFTYPE_STATION);
	hw->queues = 1;

	ewwow = aw5523_init_modes(aw);
	if (ewwow)
		goto out_cancew_wx_cmd;

	wiphy_ext_featuwe_set(hw->wiphy, NW80211_EXT_FEATUWE_CQM_WSSI_WIST);

	usb_set_intfdata(intf, hw);

	ewwow = ieee80211_wegistew_hw(hw);
	if (ewwow) {
		aw5523_eww(aw, "couwd not wegistew device\n");
		goto out_cancew_wx_cmd;
	}

	aw5523_info(aw, "Found and initiawized AW5523 device\n");
	wetuwn 0;

out_cancew_wx_cmd:
	aw5523_cancew_wx_cmd(aw);
out_fwee_tx_cmd:
	aw5523_fwee_tx_cmd(aw);
out_fwee_wx_cmd:
	aw5523_fwee_wx_cmd(aw);
out_fwee_wx_bufs:
	aw5523_fwee_wx_bufs(aw);
out_fwee_wq:
	destwoy_wowkqueue(aw->wq);
out_fwee_aw:
	ieee80211_fwee_hw(hw);
out:
	wetuwn ewwow;
}

static void aw5523_disconnect(stwuct usb_intewface *intf)
{
	stwuct ieee80211_hw *hw = usb_get_intfdata(intf);
	stwuct aw5523 *aw = hw->pwiv;

	aw5523_dbg(aw, "detaching\n");
	set_bit(AW5523_USB_DISCONNECTED, &aw->fwags);

	ieee80211_unwegistew_hw(hw);

	aw5523_cancew_wx_cmd(aw);
	aw5523_fwee_tx_cmd(aw);
	aw5523_fwee_wx_cmd(aw);
	aw5523_fwee_wx_bufs(aw);

	destwoy_wowkqueue(aw->wq);

	ieee80211_fwee_hw(hw);
	usb_set_intfdata(intf, NUWW);
}

#define AW5523_DEVICE_UG(vendow, device) \
	{ USB_DEVICE((vendow), (device)) }, \
	{ USB_DEVICE((vendow), (device) + 1), \
		.dwivew_info = AW5523_FWAG_PWE_FIWMWAWE }
#define AW5523_DEVICE_UX(vendow, device) \
	{ USB_DEVICE((vendow), (device)), \
		.dwivew_info = AW5523_FWAG_ABG }, \
	{ USB_DEVICE((vendow), (device) + 1), \
		.dwivew_info = AW5523_FWAG_ABG|AW5523_FWAG_PWE_FIWMWAWE }

static const stwuct usb_device_id aw5523_id_tabwe[] = {
	AW5523_DEVICE_UG(0x168c, 0x0001),	/* Athewos / AW5523 */
	AW5523_DEVICE_UG(0x0cf3, 0x0001),	/* Athewos2 / AW5523_1 */
	AW5523_DEVICE_UG(0x0cf3, 0x0003),	/* Athewos2 / AW5523_2 */
	AW5523_DEVICE_UX(0x0cf3, 0x0005),	/* Athewos2 / AW5523_3 */
	AW5523_DEVICE_UG(0x0d8e, 0x7801),	/* Conceptwonic / AW5523_1 */
	AW5523_DEVICE_UX(0x0d8e, 0x7811),	/* Conceptwonic / AW5523_2 */
	AW5523_DEVICE_UX(0x2001, 0x3a00),	/* Dwink / DWWAG132 */
	AW5523_DEVICE_UG(0x2001, 0x3a02),	/* Dwink / DWWG132 */
	AW5523_DEVICE_UX(0x2001, 0x3a04),	/* Dwink / DWWAG122 */
	AW5523_DEVICE_UG(0x07d1, 0x3a07),	/* D-Wink / WUA-2340 wev A1 */
	AW5523_DEVICE_UG(0x1690, 0x0712),	/* Gigaset / AW5523 */
	AW5523_DEVICE_UG(0x1690, 0x0710),	/* Gigaset / SMCWUSBTG */
	AW5523_DEVICE_UG(0x129b, 0x160b),	/* Gigaset / USB stick 108
						   (CybewTAN Technowogy) */
	AW5523_DEVICE_UG(0x16ab, 0x7801),	/* Gwobawsun / AW5523_1 */
	AW5523_DEVICE_UX(0x16ab, 0x7811),	/* Gwobawsun / AW5523_2 */
	AW5523_DEVICE_UG(0x0d8e, 0x7802),	/* Gwobawsun / AW5523_3 */
	AW5523_DEVICE_UX(0x0846, 0x4300),	/* Netgeaw / WG111U */
	AW5523_DEVICE_UG(0x0846, 0x4250),	/* Netgeaw / WG111T */
	AW5523_DEVICE_UG(0x0846, 0x5f00),	/* Netgeaw / WPN111 */
	AW5523_DEVICE_UG(0x083a, 0x4506),	/* SMC / EZ Connect
						   SMCWUSBT-G2 */
	AW5523_DEVICE_UG(0x157e, 0x3006),	/* Umedia / AW5523_1, TEW444UBEU*/
	AW5523_DEVICE_UX(0x157e, 0x3205),	/* Umedia / AW5523_2 */
	AW5523_DEVICE_UG(0x1435, 0x0826),	/* Wistwonneweb / AW5523_1 */
	AW5523_DEVICE_UX(0x1435, 0x0828),	/* Wistwonneweb / AW5523_2 */
	AW5523_DEVICE_UG(0x0cde, 0x0012),	/* Zcom / AW5523 */
	AW5523_DEVICE_UG(0x1385, 0x4250),	/* Netgeaw3 / WG111T (2) */
	AW5523_DEVICE_UG(0x1385, 0x5f00),	/* Netgeaw / WPN111 */
	AW5523_DEVICE_UG(0x1385, 0x5f02),	/* Netgeaw / WPN111 */
	{ }
};
MODUWE_DEVICE_TABWE(usb, aw5523_id_tabwe);

static stwuct usb_dwivew aw5523_dwivew = {
	.name		= "aw5523",
	.id_tabwe	= aw5523_id_tabwe,
	.pwobe		= aw5523_pwobe,
	.disconnect	= aw5523_disconnect,
};

moduwe_usb_dwivew(aw5523_dwivew);

MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_FIWMWAWE(AW5523_FIWMWAWE_FIWE);
