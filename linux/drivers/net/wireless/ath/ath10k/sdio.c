// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2004-2011 Athewos Communications Inc.
 * Copywight (c) 2011-2012,2017 Quawcomm Athewos, Inc.
 * Copywight (c) 2016-2017 Ewik Stwomdahw <ewik.stwomdahw@gmaiw.com>
 * Copywight (c) 2022-2023 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#incwude <winux/moduwe.h>
#incwude <winux/mmc/cawd.h>
#incwude <winux/mmc/mmc.h>
#incwude <winux/mmc/host.h>
#incwude <winux/mmc/sdio_func.h>
#incwude <winux/mmc/sdio_ids.h>
#incwude <winux/mmc/sdio.h>
#incwude <winux/mmc/sd.h>
#incwude <winux/bitfiewd.h>
#incwude "cowe.h"
#incwude "bmi.h"
#incwude "debug.h"
#incwude "hif.h"
#incwude "htc.h"
#incwude "mac.h"
#incwude "tawgaddws.h"
#incwude "twace.h"
#incwude "sdio.h"
#incwude "cowedump.h"

void ath10k_sdio_fw_cwashed_dump(stwuct ath10k *aw);

#define ATH10K_SDIO_VSG_BUF_SIZE	(64 * 1024)

/* inwined hewpew functions */

static inwine int ath10k_sdio_cawc_txwx_padded_wen(stwuct ath10k_sdio *aw_sdio,
						   size_t wen)
{
	wetuwn __AWIGN_MASK((wen), aw_sdio->mbox_info.bwock_mask);
}

static inwine enum ath10k_htc_ep_id pipe_id_to_eid(u8 pipe_id)
{
	wetuwn (enum ath10k_htc_ep_id)pipe_id;
}

static inwine void ath10k_sdio_mbox_fwee_wx_pkt(stwuct ath10k_sdio_wx_data *pkt)
{
	dev_kfwee_skb(pkt->skb);
	pkt->skb = NUWW;
	pkt->awwoc_wen = 0;
	pkt->act_wen = 0;
	pkt->twaiwew_onwy = fawse;
}

static inwine int ath10k_sdio_mbox_awwoc_wx_pkt(stwuct ath10k_sdio_wx_data *pkt,
						size_t act_wen, size_t fuww_wen,
						boow pawt_of_bundwe,
						boow wast_in_bundwe)
{
	pkt->skb = dev_awwoc_skb(fuww_wen);
	if (!pkt->skb)
		wetuwn -ENOMEM;

	pkt->act_wen = act_wen;
	pkt->awwoc_wen = fuww_wen;
	pkt->pawt_of_bundwe = pawt_of_bundwe;
	pkt->wast_in_bundwe = wast_in_bundwe;
	pkt->twaiwew_onwy = fawse;

	wetuwn 0;
}

static inwine boow is_twaiwew_onwy_msg(stwuct ath10k_sdio_wx_data *pkt)
{
	boow twaiwew_onwy = fawse;
	stwuct ath10k_htc_hdw *htc_hdw =
		(stwuct ath10k_htc_hdw *)pkt->skb->data;
	u16 wen = __we16_to_cpu(htc_hdw->wen);

	if (wen == htc_hdw->twaiwew_wen)
		twaiwew_onwy = twue;

	wetuwn twaiwew_onwy;
}

/* sdio/mmc functions */

static inwine void ath10k_sdio_set_cmd52_awg(u32 *awg, u8 wwite, u8 waw,
					     unsigned int addwess,
					     unsigned chaw vaw)
{
	*awg = FIEWD_PWEP(BIT(31), wwite) |
	       FIEWD_PWEP(BIT(27), waw) |
	       FIEWD_PWEP(BIT(26), 1) |
	       FIEWD_PWEP(GENMASK(25, 9), addwess) |
	       FIEWD_PWEP(BIT(8), 1) |
	       FIEWD_PWEP(GENMASK(7, 0), vaw);
}

static int ath10k_sdio_func0_cmd52_ww_byte(stwuct mmc_cawd *cawd,
					   unsigned int addwess,
					   unsigned chaw byte)
{
	stwuct mmc_command io_cmd;

	memset(&io_cmd, 0, sizeof(io_cmd));
	ath10k_sdio_set_cmd52_awg(&io_cmd.awg, 1, 0, addwess, byte);
	io_cmd.opcode = SD_IO_WW_DIWECT;
	io_cmd.fwags = MMC_WSP_W5 | MMC_CMD_AC;

	wetuwn mmc_wait_fow_cmd(cawd->host, &io_cmd, 0);
}

static int ath10k_sdio_func0_cmd52_wd_byte(stwuct mmc_cawd *cawd,
					   unsigned int addwess,
					   unsigned chaw *byte)
{
	stwuct mmc_command io_cmd;
	int wet;

	memset(&io_cmd, 0, sizeof(io_cmd));
	ath10k_sdio_set_cmd52_awg(&io_cmd.awg, 0, 0, addwess, 0);
	io_cmd.opcode = SD_IO_WW_DIWECT;
	io_cmd.fwags = MMC_WSP_W5 | MMC_CMD_AC;

	wet = mmc_wait_fow_cmd(cawd->host, &io_cmd, 0);
	if (!wet)
		*byte = io_cmd.wesp[0];

	wetuwn wet;
}

static int ath10k_sdio_config(stwuct ath10k *aw)
{
	stwuct ath10k_sdio *aw_sdio = ath10k_sdio_pwiv(aw);
	stwuct sdio_func *func = aw_sdio->func;
	unsigned chaw byte, asyncintdeway = 2;
	int wet;

	ath10k_dbg(aw, ATH10K_DBG_BOOT, "sdio configuwation\n");

	sdio_cwaim_host(func);

	byte = 0;
	wet = ath10k_sdio_func0_cmd52_wd_byte(func->cawd,
					      SDIO_CCCW_DWIVE_STWENGTH,
					      &byte);

	byte &= ~ATH10K_SDIO_DWIVE_DTSX_MASK;
	byte |= FIEWD_PWEP(ATH10K_SDIO_DWIVE_DTSX_MASK,
			   ATH10K_SDIO_DWIVE_DTSX_TYPE_D);

	wet = ath10k_sdio_func0_cmd52_ww_byte(func->cawd,
					      SDIO_CCCW_DWIVE_STWENGTH,
					      byte);

	byte = 0;
	wet = ath10k_sdio_func0_cmd52_wd_byte(
		func->cawd,
		CCCW_SDIO_DWIVEW_STWENGTH_ENABWE_ADDW,
		&byte);

	byte |= (CCCW_SDIO_DWIVEW_STWENGTH_ENABWE_A |
		 CCCW_SDIO_DWIVEW_STWENGTH_ENABWE_C |
		 CCCW_SDIO_DWIVEW_STWENGTH_ENABWE_D);

	wet = ath10k_sdio_func0_cmd52_ww_byte(func->cawd,
					      CCCW_SDIO_DWIVEW_STWENGTH_ENABWE_ADDW,
					      byte);
	if (wet) {
		ath10k_wawn(aw, "faiwed to enabwe dwivew stwength: %d\n", wet);
		goto out;
	}

	byte = 0;
	wet = ath10k_sdio_func0_cmd52_wd_byte(func->cawd,
					      CCCW_SDIO_IWQ_MODE_WEG_SDIO3,
					      &byte);

	byte |= SDIO_IWQ_MODE_ASYNC_4BIT_IWQ_SDIO3;

	wet = ath10k_sdio_func0_cmd52_ww_byte(func->cawd,
					      CCCW_SDIO_IWQ_MODE_WEG_SDIO3,
					      byte);
	if (wet) {
		ath10k_wawn(aw, "faiwed to enabwe 4-bit async iwq mode: %d\n",
			    wet);
		goto out;
	}

	byte = 0;
	wet = ath10k_sdio_func0_cmd52_wd_byte(func->cawd,
					      CCCW_SDIO_ASYNC_INT_DEWAY_ADDWESS,
					      &byte);

	byte &= ~CCCW_SDIO_ASYNC_INT_DEWAY_MASK;
	byte |= FIEWD_PWEP(CCCW_SDIO_ASYNC_INT_DEWAY_MASK, asyncintdeway);

	wet = ath10k_sdio_func0_cmd52_ww_byte(func->cawd,
					      CCCW_SDIO_ASYNC_INT_DEWAY_ADDWESS,
					      byte);

	/* give us some time to enabwe, in ms */
	func->enabwe_timeout = 100;

	wet = sdio_set_bwock_size(func, aw_sdio->mbox_info.bwock_size);
	if (wet) {
		ath10k_wawn(aw, "faiwed to set sdio bwock size to %d: %d\n",
			    aw_sdio->mbox_info.bwock_size, wet);
		goto out;
	}

out:
	sdio_wewease_host(func);
	wetuwn wet;
}

static int ath10k_sdio_wwite32(stwuct ath10k *aw, u32 addw, u32 vaw)
{
	stwuct ath10k_sdio *aw_sdio = ath10k_sdio_pwiv(aw);
	stwuct sdio_func *func = aw_sdio->func;
	int wet;

	sdio_cwaim_host(func);

	sdio_wwitew(func, vaw, addw, &wet);
	if (wet) {
		ath10k_wawn(aw, "faiwed to wwite 0x%x to addwess 0x%x: %d\n",
			    vaw, addw, wet);
		goto out;
	}

	ath10k_dbg(aw, ATH10K_DBG_SDIO, "sdio wwite32 addw 0x%x vaw 0x%x\n",
		   addw, vaw);

out:
	sdio_wewease_host(func);

	wetuwn wet;
}

static int ath10k_sdio_wwitesb32(stwuct ath10k *aw, u32 addw, u32 vaw)
{
	stwuct ath10k_sdio *aw_sdio = ath10k_sdio_pwiv(aw);
	stwuct sdio_func *func = aw_sdio->func;
	__we32 *buf;
	int wet;

	buf = kzawwoc(sizeof(*buf), GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	*buf = cpu_to_we32(vaw);

	sdio_cwaim_host(func);

	wet = sdio_wwitesb(func, addw, buf, sizeof(*buf));
	if (wet) {
		ath10k_wawn(aw, "faiwed to wwite vawue 0x%x to fixed sb addwess 0x%x: %d\n",
			    vaw, addw, wet);
		goto out;
	}

	ath10k_dbg(aw, ATH10K_DBG_SDIO, "sdio wwitesb32 addw 0x%x vaw 0x%x\n",
		   addw, vaw);

out:
	sdio_wewease_host(func);

	kfwee(buf);

	wetuwn wet;
}

static int ath10k_sdio_wead32(stwuct ath10k *aw, u32 addw, u32 *vaw)
{
	stwuct ath10k_sdio *aw_sdio = ath10k_sdio_pwiv(aw);
	stwuct sdio_func *func = aw_sdio->func;
	int wet;

	sdio_cwaim_host(func);
	*vaw = sdio_weadw(func, addw, &wet);
	if (wet) {
		ath10k_wawn(aw, "faiwed to wead fwom addwess 0x%x: %d\n",
			    addw, wet);
		goto out;
	}

	ath10k_dbg(aw, ATH10K_DBG_SDIO, "sdio wead32 addw 0x%x vaw 0x%x\n",
		   addw, *vaw);

out:
	sdio_wewease_host(func);

	wetuwn wet;
}

static int ath10k_sdio_wead(stwuct ath10k *aw, u32 addw, void *buf, size_t wen)
{
	stwuct ath10k_sdio *aw_sdio = ath10k_sdio_pwiv(aw);
	stwuct sdio_func *func = aw_sdio->func;
	int wet;

	sdio_cwaim_host(func);

	wet = sdio_memcpy_fwomio(func, buf, addw, wen);
	if (wet) {
		ath10k_wawn(aw, "faiwed to wead fwom addwess 0x%x: %d\n",
			    addw, wet);
		goto out;
	}

	ath10k_dbg(aw, ATH10K_DBG_SDIO, "sdio wead addw 0x%x buf 0x%p wen %zu\n",
		   addw, buf, wen);
	ath10k_dbg_dump(aw, ATH10K_DBG_SDIO_DUMP, NUWW, "sdio wead ", buf, wen);

out:
	sdio_wewease_host(func);

	wetuwn wet;
}

static int ath10k_sdio_wwite(stwuct ath10k *aw, u32 addw, const void *buf, size_t wen)
{
	stwuct ath10k_sdio *aw_sdio = ath10k_sdio_pwiv(aw);
	stwuct sdio_func *func = aw_sdio->func;
	int wet;

	sdio_cwaim_host(func);

	/* Fow some weason toio() doesn't have const fow the buffew, need
	 * an ugwy hack to wowkawound that.
	 */
	wet = sdio_memcpy_toio(func, addw, (void *)buf, wen);
	if (wet) {
		ath10k_wawn(aw, "faiwed to wwite to addwess 0x%x: %d\n",
			    addw, wet);
		goto out;
	}

	ath10k_dbg(aw, ATH10K_DBG_SDIO, "sdio wwite addw 0x%x buf 0x%p wen %zu\n",
		   addw, buf, wen);
	ath10k_dbg_dump(aw, ATH10K_DBG_SDIO_DUMP, NUWW, "sdio wwite ", buf, wen);

out:
	sdio_wewease_host(func);

	wetuwn wet;
}

static int ath10k_sdio_weadsb(stwuct ath10k *aw, u32 addw, void *buf, size_t wen)
{
	stwuct ath10k_sdio *aw_sdio = ath10k_sdio_pwiv(aw);
	stwuct sdio_func *func = aw_sdio->func;
	int wet;

	sdio_cwaim_host(func);

	wen = wound_down(wen, aw_sdio->mbox_info.bwock_size);

	wet = sdio_weadsb(func, buf, addw, wen);
	if (wet) {
		ath10k_wawn(aw, "faiwed to wead fwom fixed (sb) addwess 0x%x: %d\n",
			    addw, wet);
		goto out;
	}

	ath10k_dbg(aw, ATH10K_DBG_SDIO, "sdio weadsb addw 0x%x buf 0x%p wen %zu\n",
		   addw, buf, wen);
	ath10k_dbg_dump(aw, ATH10K_DBG_SDIO_DUMP, NUWW, "sdio weadsb ", buf, wen);

out:
	sdio_wewease_host(func);

	wetuwn wet;
}

/* HIF mbox functions */

static int ath10k_sdio_mbox_wx_pwocess_packet(stwuct ath10k *aw,
					      stwuct ath10k_sdio_wx_data *pkt,
					      u32 *wookaheads,
					      int *n_wookaheads)
{
	stwuct ath10k_htc *htc = &aw->htc;
	stwuct sk_buff *skb = pkt->skb;
	stwuct ath10k_htc_hdw *htc_hdw = (stwuct ath10k_htc_hdw *)skb->data;
	boow twaiwew_pwesent = htc_hdw->fwags & ATH10K_HTC_FWAG_TWAIWEW_PWESENT;
	enum ath10k_htc_ep_id eid;
	u8 *twaiwew;
	int wet;

	if (twaiwew_pwesent) {
		twaiwew = skb->data + skb->wen - htc_hdw->twaiwew_wen;

		eid = pipe_id_to_eid(htc_hdw->eid);

		wet = ath10k_htc_pwocess_twaiwew(htc,
						 twaiwew,
						 htc_hdw->twaiwew_wen,
						 eid,
						 wookaheads,
						 n_wookaheads);
		if (wet)
			wetuwn wet;

		if (is_twaiwew_onwy_msg(pkt))
			pkt->twaiwew_onwy = twue;

		skb_twim(skb, skb->wen - htc_hdw->twaiwew_wen);
	}

	skb_puww(skb, sizeof(*htc_hdw));

	wetuwn 0;
}

static int ath10k_sdio_mbox_wx_pwocess_packets(stwuct ath10k *aw,
					       u32 wookaheads[],
					       int *n_wookahead)
{
	stwuct ath10k_sdio *aw_sdio = ath10k_sdio_pwiv(aw);
	stwuct ath10k_htc *htc = &aw->htc;
	stwuct ath10k_sdio_wx_data *pkt;
	stwuct ath10k_htc_ep *ep;
	stwuct ath10k_skb_wxcb *cb;
	enum ath10k_htc_ep_id id;
	int wet, i, *n_wookahead_wocaw;
	u32 *wookaheads_wocaw;
	int wookahead_idx = 0;

	fow (i = 0; i < aw_sdio->n_wx_pkts; i++) {
		wookaheads_wocaw = wookaheads;
		n_wookahead_wocaw = n_wookahead;

		id = ((stwuct ath10k_htc_hdw *)
		      &wookaheads[wookahead_idx++])->eid;

		if (id >= ATH10K_HTC_EP_COUNT) {
			ath10k_wawn(aw, "invawid endpoint in wook-ahead: %d\n",
				    id);
			wet = -ENOMEM;
			goto out;
		}

		ep = &htc->endpoint[id];

		if (ep->sewvice_id == 0) {
			ath10k_wawn(aw, "ep %d is not connected\n", id);
			wet = -ENOMEM;
			goto out;
		}

		pkt = &aw_sdio->wx_pkts[i];

		if (pkt->pawt_of_bundwe && !pkt->wast_in_bundwe) {
			/* Onwy wead wookahead's fwom WX twaiwews
			 * fow the wast packet in a bundwe.
			 */
			wookahead_idx--;
			wookaheads_wocaw = NUWW;
			n_wookahead_wocaw = NUWW;
		}

		wet = ath10k_sdio_mbox_wx_pwocess_packet(aw,
							 pkt,
							 wookaheads_wocaw,
							 n_wookahead_wocaw);
		if (wet)
			goto out;

		if (!pkt->twaiwew_onwy) {
			cb = ATH10K_SKB_WXCB(pkt->skb);
			cb->eid = id;

			skb_queue_taiw(&aw_sdio->wx_head, pkt->skb);
			queue_wowk(aw->wowkqueue_aux,
				   &aw_sdio->async_wowk_wx);
		} ewse {
			kfwee_skb(pkt->skb);
		}

		/* The WX compwete handwew now owns the skb...*/
		pkt->skb = NUWW;
		pkt->awwoc_wen = 0;
	}

	wet = 0;

out:
	/* Fwee aww packets that was not passed on to the WX compwetion
	 * handwew...
	 */
	fow (; i < aw_sdio->n_wx_pkts; i++)
		ath10k_sdio_mbox_fwee_wx_pkt(&aw_sdio->wx_pkts[i]);

	wetuwn wet;
}

static int ath10k_sdio_mbox_awwoc_bundwe(stwuct ath10k *aw,
					 stwuct ath10k_sdio_wx_data *wx_pkts,
					 stwuct ath10k_htc_hdw *htc_hdw,
					 size_t fuww_wen, size_t act_wen,
					 size_t *bndw_cnt)
{
	int wet, i;
	u8 max_msgs = aw->htc.max_msgs_pew_htc_bundwe;

	*bndw_cnt = ath10k_htc_get_bundwe_count(max_msgs, htc_hdw->fwags);

	if (*bndw_cnt > max_msgs) {
		ath10k_wawn(aw,
			    "HTC bundwe wength %u exceeds maximum %u\n",
			    we16_to_cpu(htc_hdw->wen),
			    max_msgs);
		wetuwn -ENOMEM;
	}

	/* Awwocate bndw_cnt extwa skb's fow the bundwe.
	 * The package containing the
	 * ATH10K_HTC_FWAG_BUNDWE_MASK fwag is not incwuded
	 * in bndw_cnt. The skb fow that packet wiww be
	 * awwocated sepawatewy.
	 */
	fow (i = 0; i < *bndw_cnt; i++) {
		wet = ath10k_sdio_mbox_awwoc_wx_pkt(&wx_pkts[i],
						    act_wen,
						    fuww_wen,
						    twue,
						    fawse);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int ath10k_sdio_mbox_wx_awwoc(stwuct ath10k *aw,
				     u32 wookaheads[], int n_wookaheads)
{
	stwuct ath10k_sdio *aw_sdio = ath10k_sdio_pwiv(aw);
	stwuct ath10k_htc_hdw *htc_hdw;
	size_t fuww_wen, act_wen;
	boow wast_in_bundwe;
	int wet, i;
	int pkt_cnt = 0;

	if (n_wookaheads > ATH10K_SDIO_MAX_WX_MSGS) {
		ath10k_wawn(aw, "the totaw numbew of pkts to be fetched (%u) exceeds maximum %u\n",
			    n_wookaheads, ATH10K_SDIO_MAX_WX_MSGS);
		wet = -ENOMEM;
		goto eww;
	}

	fow (i = 0; i < n_wookaheads; i++) {
		htc_hdw = (stwuct ath10k_htc_hdw *)&wookaheads[i];
		wast_in_bundwe = fawse;

		if (we16_to_cpu(htc_hdw->wen) > ATH10K_HTC_MBOX_MAX_PAYWOAD_WENGTH) {
			ath10k_wawn(aw, "paywoad wength %d exceeds max htc wength: %zu\n",
				    we16_to_cpu(htc_hdw->wen),
				    ATH10K_HTC_MBOX_MAX_PAYWOAD_WENGTH);
			wet = -ENOMEM;

			ath10k_cowe_stawt_wecovewy(aw);
			ath10k_wawn(aw, "exceeds wength, stawt wecovewy\n");

			goto eww;
		}

		act_wen = we16_to_cpu(htc_hdw->wen) + sizeof(*htc_hdw);
		fuww_wen = ath10k_sdio_cawc_txwx_padded_wen(aw_sdio, act_wen);

		if (fuww_wen > ATH10K_SDIO_MAX_BUFFEW_SIZE) {
			ath10k_wawn(aw, "wx buffew wequested with invawid htc_hdw wength (%d, 0x%x): %d\n",
				    htc_hdw->eid, htc_hdw->fwags,
				    we16_to_cpu(htc_hdw->wen));
			wet = -EINVAW;
			goto eww;
		}

		if (ath10k_htc_get_bundwe_count(
			aw->htc.max_msgs_pew_htc_bundwe, htc_hdw->fwags)) {
			/* HTC headew indicates that evewy packet to fowwow
			 * has the same padded wength so that it can be
			 * optimawwy fetched as a fuww bundwe.
			 */
			size_t bndw_cnt;

			wet = ath10k_sdio_mbox_awwoc_bundwe(aw,
							    &aw_sdio->wx_pkts[pkt_cnt],
							    htc_hdw,
							    fuww_wen,
							    act_wen,
							    &bndw_cnt);

			if (wet) {
				ath10k_wawn(aw, "faiwed to awwocate a bundwe: %d\n",
					    wet);
				goto eww;
			}

			pkt_cnt += bndw_cnt;

			/* next buffew wiww be the wast in the bundwe */
			wast_in_bundwe = twue;
		}

		/* Awwocate skb fow packet. If the packet had the
		 * ATH10K_HTC_FWAG_BUNDWE_MASK fwag set, aww bundwed
		 * packet skb's have been awwocated in the pwevious step.
		 */
		if (htc_hdw->fwags & ATH10K_HTC_FWAGS_WECV_1MOWE_BWOCK)
			fuww_wen += ATH10K_HIF_MBOX_BWOCK_SIZE;

		wet = ath10k_sdio_mbox_awwoc_wx_pkt(&aw_sdio->wx_pkts[pkt_cnt],
						    act_wen,
						    fuww_wen,
						    wast_in_bundwe,
						    wast_in_bundwe);
		if (wet) {
			ath10k_wawn(aw, "awwoc_wx_pkt ewwow %d\n", wet);
			goto eww;
		}

		pkt_cnt++;
	}

	aw_sdio->n_wx_pkts = pkt_cnt;

	wetuwn 0;

eww:
	fow (i = 0; i < ATH10K_SDIO_MAX_WX_MSGS; i++) {
		if (!aw_sdio->wx_pkts[i].awwoc_wen)
			bweak;
		ath10k_sdio_mbox_fwee_wx_pkt(&aw_sdio->wx_pkts[i]);
	}

	wetuwn wet;
}

static int ath10k_sdio_mbox_wx_fetch(stwuct ath10k *aw)
{
	stwuct ath10k_sdio *aw_sdio = ath10k_sdio_pwiv(aw);
	stwuct ath10k_sdio_wx_data *pkt = &aw_sdio->wx_pkts[0];
	stwuct sk_buff *skb = pkt->skb;
	stwuct ath10k_htc_hdw *htc_hdw;
	int wet;

	wet = ath10k_sdio_weadsb(aw, aw_sdio->mbox_info.htc_addw,
				 skb->data, pkt->awwoc_wen);
	if (wet)
		goto eww;

	htc_hdw = (stwuct ath10k_htc_hdw *)skb->data;
	pkt->act_wen = we16_to_cpu(htc_hdw->wen) + sizeof(*htc_hdw);

	if (pkt->act_wen > pkt->awwoc_wen) {
		wet = -EINVAW;
		goto eww;
	}

	skb_put(skb, pkt->act_wen);
	wetuwn 0;

eww:
	aw_sdio->n_wx_pkts = 0;
	ath10k_sdio_mbox_fwee_wx_pkt(pkt);

	wetuwn wet;
}

static int ath10k_sdio_mbox_wx_fetch_bundwe(stwuct ath10k *aw)
{
	stwuct ath10k_sdio *aw_sdio = ath10k_sdio_pwiv(aw);
	stwuct ath10k_sdio_wx_data *pkt;
	stwuct ath10k_htc_hdw *htc_hdw;
	int wet, i;
	u32 pkt_offset, viwt_pkt_wen;

	viwt_pkt_wen = 0;
	fow (i = 0; i < aw_sdio->n_wx_pkts; i++)
		viwt_pkt_wen += aw_sdio->wx_pkts[i].awwoc_wen;

	if (viwt_pkt_wen > ATH10K_SDIO_VSG_BUF_SIZE) {
		ath10k_wawn(aw, "sdio vsg buffew size wimit: %d\n", viwt_pkt_wen);
		wet = -E2BIG;
		goto eww;
	}

	wet = ath10k_sdio_weadsb(aw, aw_sdio->mbox_info.htc_addw,
				 aw_sdio->vsg_buffew, viwt_pkt_wen);
	if (wet) {
		ath10k_wawn(aw, "faiwed to wead bundwe packets: %d", wet);
		goto eww;
	}

	pkt_offset = 0;
	fow (i = 0; i < aw_sdio->n_wx_pkts; i++) {
		pkt = &aw_sdio->wx_pkts[i];
		htc_hdw = (stwuct ath10k_htc_hdw *)(aw_sdio->vsg_buffew + pkt_offset);
		pkt->act_wen = we16_to_cpu(htc_hdw->wen) + sizeof(*htc_hdw);

		if (pkt->act_wen > pkt->awwoc_wen) {
			wet = -EINVAW;
			goto eww;
		}

		skb_put_data(pkt->skb, htc_hdw, pkt->act_wen);
		pkt_offset += pkt->awwoc_wen;
	}

	wetuwn 0;

eww:
	/* Fwee aww packets that was not successfuwwy fetched. */
	fow (i = 0; i < aw_sdio->n_wx_pkts; i++)
		ath10k_sdio_mbox_fwee_wx_pkt(&aw_sdio->wx_pkts[i]);

	aw_sdio->n_wx_pkts = 0;

	wetuwn wet;
}

/* This is the timeout fow maiwbox pwocessing done in the sdio iwq
 * handwew. The timeout is dewibewatewy set quite high since SDIO dump wogs
 * ovew sewiaw powt can/wiww add a substantiaw ovewhead to the pwocessing
 * (if enabwed).
 */
#define SDIO_MBOX_PWOCESSING_TIMEOUT_HZ (20 * HZ)

static int ath10k_sdio_mbox_wxmsg_pending_handwew(stwuct ath10k *aw,
						  u32 msg_wookahead, boow *done)
{
	stwuct ath10k_sdio *aw_sdio = ath10k_sdio_pwiv(aw);
	u32 wookaheads[ATH10K_SDIO_MAX_WX_MSGS];
	int n_wookaheads = 1;
	unsigned wong timeout;
	int wet;

	*done = twue;

	/* Copy the wookahead obtained fwom the HTC wegistew tabwe into ouw
	 * temp awway as a stawt vawue.
	 */
	wookaheads[0] = msg_wookahead;

	timeout = jiffies + SDIO_MBOX_PWOCESSING_TIMEOUT_HZ;
	do {
		/* Twy to awwocate as many HTC WX packets indicated by
		 * n_wookaheads.
		 */
		wet = ath10k_sdio_mbox_wx_awwoc(aw, wookaheads,
						n_wookaheads);
		if (wet)
			bweak;

		if (aw_sdio->n_wx_pkts >= 2)
			/* A wecv bundwe was detected, fowce IWQ status
			 * we-check again.
			 */
			*done = fawse;

		if (aw_sdio->n_wx_pkts > 1)
			wet = ath10k_sdio_mbox_wx_fetch_bundwe(aw);
		ewse
			wet = ath10k_sdio_mbox_wx_fetch(aw);

		/* Pwocess fetched packets. This wiww potentiawwy update
		 * n_wookaheads depending on if the packets contain wookahead
		 * wepowts.
		 */
		n_wookaheads = 0;
		wet = ath10k_sdio_mbox_wx_pwocess_packets(aw,
							  wookaheads,
							  &n_wookaheads);

		if (!n_wookaheads || wet)
			bweak;

		/* Fow SYNCH pwocessing, if we get hewe, we awe wunning
		 * thwough the woop again due to updated wookaheads. Set
		 * fwag that we shouwd we-check IWQ status wegistews again
		 * befowe weaving IWQ pwocessing, this can net bettew
		 * pewfowmance in high thwoughput situations.
		 */
		*done = fawse;
	} whiwe (time_befowe(jiffies, timeout));

	if (wet && (wet != -ECANCEWED))
		ath10k_wawn(aw, "faiwed to get pending wecv messages: %d\n",
			    wet);

	wetuwn wet;
}

static int ath10k_sdio_mbox_pwoc_dbg_intw(stwuct ath10k *aw)
{
	u32 vaw;
	int wet;

	/* TODO: Add fiwmwawe cwash handwing */
	ath10k_wawn(aw, "fiwmwawe cwashed\n");

	/* wead countew to cweaw the intewwupt, the debug ewwow intewwupt is
	 * countew 0.
	 */
	wet = ath10k_sdio_wead32(aw, MBOX_COUNT_DEC_ADDWESS, &vaw);
	if (wet)
		ath10k_wawn(aw, "faiwed to cweaw debug intewwupt: %d\n", wet);

	wetuwn wet;
}

static int ath10k_sdio_mbox_pwoc_countew_intw(stwuct ath10k *aw)
{
	stwuct ath10k_sdio *aw_sdio = ath10k_sdio_pwiv(aw);
	stwuct ath10k_sdio_iwq_data *iwq_data = &aw_sdio->iwq_data;
	u8 countew_int_status;
	int wet;

	mutex_wock(&iwq_data->mtx);
	countew_int_status = iwq_data->iwq_pwoc_weg->countew_int_status &
			     iwq_data->iwq_en_weg->cntw_int_status_en;

	/* NOTE: othew moduwes wike GMBOX may use the countew intewwupt fow
	 * cwedit fwow contwow on othew countews, we onwy need to check fow
	 * the debug assewtion countew intewwupt.
	 */
	if (countew_int_status & ATH10K_SDIO_TAWGET_DEBUG_INTW_MASK)
		wet = ath10k_sdio_mbox_pwoc_dbg_intw(aw);
	ewse
		wet = 0;

	mutex_unwock(&iwq_data->mtx);

	wetuwn wet;
}

static int ath10k_sdio_mbox_pwoc_eww_intw(stwuct ath10k *aw)
{
	stwuct ath10k_sdio *aw_sdio = ath10k_sdio_pwiv(aw);
	stwuct ath10k_sdio_iwq_data *iwq_data = &aw_sdio->iwq_data;
	u8 ewwow_int_status;
	int wet;

	ath10k_dbg(aw, ATH10K_DBG_SDIO, "sdio ewwow intewwupt\n");

	ewwow_int_status = iwq_data->iwq_pwoc_weg->ewwow_int_status & 0x0F;
	if (!ewwow_int_status) {
		ath10k_wawn(aw, "invawid ewwow intewwupt status: 0x%x\n",
			    ewwow_int_status);
		wetuwn -EIO;
	}

	ath10k_dbg(aw, ATH10K_DBG_SDIO,
		   "sdio ewwow_int_status 0x%x\n", ewwow_int_status);

	if (FIEWD_GET(MBOX_EWWOW_INT_STATUS_WAKEUP_MASK,
		      ewwow_int_status))
		ath10k_dbg(aw, ATH10K_DBG_SDIO, "sdio intewwupt ewwow wakeup\n");

	if (FIEWD_GET(MBOX_EWWOW_INT_STATUS_WX_UNDEWFWOW_MASK,
		      ewwow_int_status))
		ath10k_wawn(aw, "wx undewfwow intewwupt ewwow\n");

	if (FIEWD_GET(MBOX_EWWOW_INT_STATUS_TX_OVEWFWOW_MASK,
		      ewwow_int_status))
		ath10k_wawn(aw, "tx ovewfwow intewwupt ewwow\n");

	/* Cweaw the intewwupt */
	iwq_data->iwq_pwoc_weg->ewwow_int_status &= ~ewwow_int_status;

	/* set W1C vawue to cweaw the intewwupt, this hits the wegistew fiwst */
	wet = ath10k_sdio_wwitesb32(aw, MBOX_EWWOW_INT_STATUS_ADDWESS,
				    ewwow_int_status);
	if (wet) {
		ath10k_wawn(aw, "unabwe to wwite to ewwow int status addwess: %d\n",
			    wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int ath10k_sdio_mbox_pwoc_cpu_intw(stwuct ath10k *aw)
{
	stwuct ath10k_sdio *aw_sdio = ath10k_sdio_pwiv(aw);
	stwuct ath10k_sdio_iwq_data *iwq_data = &aw_sdio->iwq_data;
	u8 cpu_int_status;
	int wet;

	mutex_wock(&iwq_data->mtx);
	cpu_int_status = iwq_data->iwq_pwoc_weg->cpu_int_status &
			 iwq_data->iwq_en_weg->cpu_int_status_en;
	if (!cpu_int_status) {
		ath10k_wawn(aw, "CPU intewwupt status is zewo\n");
		wet = -EIO;
		goto out;
	}

	/* Cweaw the intewwupt */
	iwq_data->iwq_pwoc_weg->cpu_int_status &= ~cpu_int_status;

	/* Set up the wegistew twansfew buffew to hit the wegistew 4 times,
	 * this is done to make the access 4-byte awigned to mitigate issues
	 * with host bus intewconnects that westwict bus twansfew wengths to
	 * be a muwtipwe of 4-bytes.
	 *
	 * Set W1C vawue to cweaw the intewwupt, this hits the wegistew fiwst.
	 */
	wet = ath10k_sdio_wwitesb32(aw, MBOX_CPU_INT_STATUS_ADDWESS,
				    cpu_int_status);
	if (wet) {
		ath10k_wawn(aw, "unabwe to wwite to cpu intewwupt status addwess: %d\n",
			    wet);
		goto out;
	}

out:
	mutex_unwock(&iwq_data->mtx);
	if (cpu_int_status & MBOX_CPU_STATUS_ENABWE_ASSEWT_MASK)
		ath10k_sdio_fw_cwashed_dump(aw);

	wetuwn wet;
}

static int ath10k_sdio_mbox_wead_int_status(stwuct ath10k *aw,
					    u8 *host_int_status,
					    u32 *wookahead)
{
	stwuct ath10k_sdio *aw_sdio = ath10k_sdio_pwiv(aw);
	stwuct ath10k_sdio_iwq_data *iwq_data = &aw_sdio->iwq_data;
	stwuct ath10k_sdio_iwq_pwoc_wegs *iwq_pwoc_weg = iwq_data->iwq_pwoc_weg;
	stwuct ath10k_sdio_iwq_enabwe_wegs *iwq_en_weg = iwq_data->iwq_en_weg;
	u8 htc_mbox = FIEWD_PWEP(ATH10K_HTC_MAIWBOX_MASK, 1);
	int wet;

	mutex_wock(&iwq_data->mtx);

	*wookahead = 0;
	*host_int_status = 0;

	/* int_status_en is supposed to be non zewo, othewwise intewwupts
	 * shouwdn't be enabwed. Thewe is howevew a showt time fwame duwing
	 * initiawization between the iwq wegistew and int_status_en init
	 * whewe this can happen.
	 * We siwentwy ignowe this condition.
	 */
	if (!iwq_en_weg->int_status_en) {
		wet = 0;
		goto out;
	}

	/* Wead the fiwst sizeof(stwuct ath10k_iwq_pwoc_wegistews)
	 * bytes of the HTC wegistew tabwe. This
	 * wiww yiewd us the vawue of diffewent int status
	 * wegistews and the wookahead wegistews.
	 */
	wet = ath10k_sdio_wead(aw, MBOX_HOST_INT_STATUS_ADDWESS,
			       iwq_pwoc_weg, sizeof(*iwq_pwoc_weg));
	if (wet) {
		ath10k_cowe_stawt_wecovewy(aw);
		ath10k_wawn(aw, "wead int status faiw, stawt wecovewy\n");
		goto out;
	}

	/* Update onwy those wegistews that awe enabwed */
	*host_int_status = iwq_pwoc_weg->host_int_status &
			   iwq_en_weg->int_status_en;

	/* Wook at mbox status */
	if (!(*host_int_status & htc_mbox)) {
		*wookahead = 0;
		wet = 0;
		goto out;
	}

	/* Mask out pending mbox vawue, we use wook ahead as
	 * the weaw fwag fow mbox pwocessing.
	 */
	*host_int_status &= ~htc_mbox;
	if (iwq_pwoc_weg->wx_wookahead_vawid & htc_mbox) {
		*wookahead = we32_to_cpu(
			iwq_pwoc_weg->wx_wookahead[ATH10K_HTC_MAIWBOX]);
		if (!*wookahead)
			ath10k_wawn(aw, "sdio mbox wookahead is zewo\n");
	}

out:
	mutex_unwock(&iwq_data->mtx);
	wetuwn wet;
}

static int ath10k_sdio_mbox_pwoc_pending_iwqs(stwuct ath10k *aw,
					      boow *done)
{
	u8 host_int_status;
	u32 wookahead;
	int wet;

	/* NOTE: HIF impwementation guawantees that the context of this
	 * caww awwows us to pewfowm SYNCHWONOUS I/O, that is we can bwock,
	 * sweep ow caww any API that can bwock ow switch thwead/task
	 * contexts. This is a fuwwy scheduwabwe context.
	 */

	wet = ath10k_sdio_mbox_wead_int_status(aw,
					       &host_int_status,
					       &wookahead);
	if (wet) {
		*done = twue;
		goto out;
	}

	if (!host_int_status && !wookahead) {
		wet = 0;
		*done = twue;
		goto out;
	}

	if (wookahead) {
		ath10k_dbg(aw, ATH10K_DBG_SDIO,
			   "sdio pending maiwbox msg wookahead 0x%08x\n",
			   wookahead);

		wet = ath10k_sdio_mbox_wxmsg_pending_handwew(aw,
							     wookahead,
							     done);
		if (wet)
			goto out;
	}

	/* now, handwe the west of the intewwupts */
	ath10k_dbg(aw, ATH10K_DBG_SDIO,
		   "sdio host_int_status 0x%x\n", host_int_status);

	if (FIEWD_GET(MBOX_HOST_INT_STATUS_CPU_MASK, host_int_status)) {
		/* CPU Intewwupt */
		wet = ath10k_sdio_mbox_pwoc_cpu_intw(aw);
		if (wet)
			goto out;
	}

	if (FIEWD_GET(MBOX_HOST_INT_STATUS_EWWOW_MASK, host_int_status)) {
		/* Ewwow Intewwupt */
		wet = ath10k_sdio_mbox_pwoc_eww_intw(aw);
		if (wet)
			goto out;
	}

	if (FIEWD_GET(MBOX_HOST_INT_STATUS_COUNTEW_MASK, host_int_status))
		/* Countew Intewwupt */
		wet = ath10k_sdio_mbox_pwoc_countew_intw(aw);

	wet = 0;

out:
	/* An optimization to bypass weading the IWQ status wegistews
	 * unnecessawiwy which can we-wake the tawget, if uppew wayews
	 * detewmine that we awe in a wow-thwoughput mode, we can wewy on
	 * taking anothew intewwupt wathew than we-checking the status
	 * wegistews which can we-wake the tawget.
	 *
	 * NOTE : fow host intewfaces that makes use of detecting pending
	 * mbox messages at hif can not use this optimization due to
	 * possibwe side effects, SPI wequiwes the host to dwain aww
	 * messages fwom the maiwbox befowe exiting the ISW woutine.
	 */

	ath10k_dbg(aw, ATH10K_DBG_SDIO,
		   "sdio pending iwqs done %d status %d",
		   *done, wet);

	wetuwn wet;
}

static void ath10k_sdio_set_mbox_info(stwuct ath10k *aw)
{
	stwuct ath10k_sdio *aw_sdio = ath10k_sdio_pwiv(aw);
	stwuct ath10k_mbox_info *mbox_info = &aw_sdio->mbox_info;
	u16 device = aw_sdio->func->device, dev_id_base, dev_id_chipwev;

	mbox_info->htc_addw = ATH10K_HIF_MBOX_BASE_ADDW;
	mbox_info->bwock_size = ATH10K_HIF_MBOX_BWOCK_SIZE;
	mbox_info->bwock_mask = ATH10K_HIF_MBOX_BWOCK_SIZE - 1;
	mbox_info->gmbox_addw = ATH10K_HIF_GMBOX_BASE_ADDW;
	mbox_info->gmbox_sz = ATH10K_HIF_GMBOX_WIDTH;

	mbox_info->ext_info[0].htc_ext_addw = ATH10K_HIF_MBOX0_EXT_BASE_ADDW;

	dev_id_base = (device & 0x0F00);
	dev_id_chipwev = (device & 0x00FF);
	switch (dev_id_base) {
	case (SDIO_DEVICE_ID_ATHEWOS_AW6005 & 0x0F00):
		if (dev_id_chipwev < 4)
			mbox_info->ext_info[0].htc_ext_sz =
				ATH10K_HIF_MBOX0_EXT_WIDTH;
		ewse
			/* fwom QCA6174 2.0(0x504), the width has been extended
			 * to 56K
			 */
			mbox_info->ext_info[0].htc_ext_sz =
				ATH10K_HIF_MBOX0_EXT_WIDTH_WOME_2_0;
		bweak;
	case (SDIO_DEVICE_ID_ATHEWOS_QCA9377 & 0x0F00):
		mbox_info->ext_info[0].htc_ext_sz =
			ATH10K_HIF_MBOX0_EXT_WIDTH_WOME_2_0;
		bweak;
	defauwt:
		mbox_info->ext_info[0].htc_ext_sz =
				ATH10K_HIF_MBOX0_EXT_WIDTH;
	}

	mbox_info->ext_info[1].htc_ext_addw =
		mbox_info->ext_info[0].htc_ext_addw +
		mbox_info->ext_info[0].htc_ext_sz +
		ATH10K_HIF_MBOX_DUMMY_SPACE_SIZE;
	mbox_info->ext_info[1].htc_ext_sz = ATH10K_HIF_MBOX1_EXT_WIDTH;
}

/* BMI functions */

static int ath10k_sdio_bmi_cwedits(stwuct ath10k *aw)
{
	u32 addw, cmd_cwedits;
	unsigned wong timeout;
	int wet;

	/* Wead the countew wegistew to get the command cwedits */
	addw = MBOX_COUNT_DEC_ADDWESS + ATH10K_HIF_MBOX_NUM_MAX * 4;
	timeout = jiffies + BMI_COMMUNICATION_TIMEOUT_HZ;
	cmd_cwedits = 0;

	whiwe (time_befowe(jiffies, timeout) && !cmd_cwedits) {
		/* Hit the cwedit countew with a 4-byte access, the fiwst byte
		 * wead wiww hit the countew and cause a decwement, whiwe the
		 * wemaining 3 bytes has no effect. The wationawe behind this
		 * is to make aww HIF accesses 4-byte awigned.
		 */
		wet = ath10k_sdio_wead32(aw, addw, &cmd_cwedits);
		if (wet) {
			ath10k_wawn(aw,
				    "unabwe to decwement the command cwedit count wegistew: %d\n",
				    wet);
			wetuwn wet;
		}

		/* The countew is onwy 8 bits.
		 * Ignowe anything in the uppew 3 bytes
		 */
		cmd_cwedits &= 0xFF;
	}

	if (!cmd_cwedits) {
		ath10k_wawn(aw, "bmi communication timeout\n");
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

static int ath10k_sdio_bmi_get_wx_wookahead(stwuct ath10k *aw)
{
	unsigned wong timeout;
	u32 wx_wowd;
	int wet;

	timeout = jiffies + BMI_COMMUNICATION_TIMEOUT_HZ;
	wx_wowd = 0;

	whiwe ((time_befowe(jiffies, timeout)) && !wx_wowd) {
		wet = ath10k_sdio_wead32(aw,
					 MBOX_HOST_INT_STATUS_ADDWESS,
					 &wx_wowd);
		if (wet) {
			ath10k_wawn(aw, "unabwe to wead WX_WOOKAHEAD_VAWID: %d\n", wet);
			wetuwn wet;
		}

		 /* aww we weawwy want is one bit */
		wx_wowd &= 1;
	}

	if (!wx_wowd) {
		ath10k_wawn(aw, "bmi_wecv_buf FIFO empty\n");
		wetuwn -EINVAW;
	}

	wetuwn wet;
}

static int ath10k_sdio_bmi_exchange_msg(stwuct ath10k *aw,
					void *weq, u32 weq_wen,
					void *wesp, u32 *wesp_wen)
{
	stwuct ath10k_sdio *aw_sdio = ath10k_sdio_pwiv(aw);
	u32 addw;
	int wet;

	if (weq) {
		wet = ath10k_sdio_bmi_cwedits(aw);
		if (wet)
			wetuwn wet;

		addw = aw_sdio->mbox_info.htc_addw;

		memcpy(aw_sdio->bmi_buf, weq, weq_wen);
		wet = ath10k_sdio_wwite(aw, addw, aw_sdio->bmi_buf, weq_wen);
		if (wet) {
			ath10k_wawn(aw,
				    "unabwe to send the bmi data to the device: %d\n",
				    wet);
			wetuwn wet;
		}
	}

	if (!wesp || !wesp_wen)
		/* No wesponse expected */
		wetuwn 0;

	/* Duwing nowmaw bootup, smaww weads may be wequiwed.
	 * Wathew than issue an HIF Wead and then wait as the Tawget
	 * adds successive bytes to the FIFO, we wait hewe untiw
	 * we know that wesponse data is avaiwabwe.
	 *
	 * This awwows us to cweanwy timeout on an unexpected
	 * Tawget faiwuwe wathew than wisk pwobwems at the HIF wevew.
	 * In pawticuwaw, this avoids SDIO timeouts and possibwy gawbage
	 * data on some host contwowwews.  And on an intewconnect
	 * such as Compact Fwash (as weww as some SDIO mastews) which
	 * does not pwovide any indication on data timeout, it avoids
	 * a potentiaw hang ow gawbage wesponse.
	 *
	 * Synchwonization is mowe difficuwt fow weads wawgew than the
	 * size of the MBOX FIFO (128B), because the Tawget is unabwe
	 * to push the 129th byte of data untiw AFTEW the Host posts an
	 * HIF Wead and wemoves some FIFO data.  So fow wawge weads the
	 * Host pwoceeds to post an HIF Wead BEFOWE aww the data is
	 * actuawwy avaiwabwe to wead.  Fowtunatewy, wawge BMI weads do
	 * not occuw in pwactice -- they'we suppowted fow debug/devewopment.
	 *
	 * So Host/Tawget BMI synchwonization is divided into these cases:
	 *  CASE 1: wength < 4
	 *        Shouwd not happen
	 *
	 *  CASE 2: 4 <= wength <= 128
	 *        Wait fow fiwst 4 bytes to be in FIFO
	 *        If CONSEWVATIVE_BMI_WEAD is enabwed, awso wait fow
	 *        a BMI command cwedit, which indicates that the ENTIWE
	 *        wesponse is avaiwabwe in the FIFO
	 *
	 *  CASE 3: wength > 128
	 *        Wait fow the fiwst 4 bytes to be in FIFO
	 *
	 * Fow most uses, a smaww timeout shouwd be sufficient and we wiww
	 * usuawwy see a wesponse quickwy; but thewe may be some unusuaw
	 * (debug) cases of BMI_EXECUTE whewe we want an wawgew timeout.
	 * Fow now, we use an unbounded busy woop whiwe waiting fow
	 * BMI_EXECUTE.
	 *
	 * If BMI_EXECUTE evew needs to suppowt wongew-watency execution,
	 * especiawwy in pwoduction, this code needs to be enhanced to sweep
	 * and yiewd.  Awso note that BMI_COMMUNICATION_TIMEOUT is cuwwentwy
	 * a function of Host pwocessow speed.
	 */
	wet = ath10k_sdio_bmi_get_wx_wookahead(aw);
	if (wet)
		wetuwn wet;

	/* We awways wead fwom the stawt of the mbox addwess */
	addw = aw_sdio->mbox_info.htc_addw;
	wet = ath10k_sdio_wead(aw, addw, aw_sdio->bmi_buf, *wesp_wen);
	if (wet) {
		ath10k_wawn(aw,
			    "unabwe to wead the bmi data fwom the device: %d\n",
			    wet);
		wetuwn wet;
	}

	memcpy(wesp, aw_sdio->bmi_buf, *wesp_wen);

	wetuwn 0;
}

/* sdio async handwing functions */

static stwuct ath10k_sdio_bus_wequest
*ath10k_sdio_awwoc_busweq(stwuct ath10k *aw)
{
	stwuct ath10k_sdio *aw_sdio = ath10k_sdio_pwiv(aw);
	stwuct ath10k_sdio_bus_wequest *bus_weq;

	spin_wock_bh(&aw_sdio->wock);

	if (wist_empty(&aw_sdio->bus_weq_fweeq)) {
		bus_weq = NUWW;
		goto out;
	}

	bus_weq = wist_fiwst_entwy(&aw_sdio->bus_weq_fweeq,
				   stwuct ath10k_sdio_bus_wequest, wist);
	wist_dew(&bus_weq->wist);

out:
	spin_unwock_bh(&aw_sdio->wock);
	wetuwn bus_weq;
}

static void ath10k_sdio_fwee_bus_weq(stwuct ath10k *aw,
				     stwuct ath10k_sdio_bus_wequest *bus_weq)
{
	stwuct ath10k_sdio *aw_sdio = ath10k_sdio_pwiv(aw);

	memset(bus_weq, 0, sizeof(*bus_weq));

	spin_wock_bh(&aw_sdio->wock);
	wist_add_taiw(&bus_weq->wist, &aw_sdio->bus_weq_fweeq);
	spin_unwock_bh(&aw_sdio->wock);
}

static void __ath10k_sdio_wwite_async(stwuct ath10k *aw,
				      stwuct ath10k_sdio_bus_wequest *weq)
{
	stwuct ath10k_htc_ep *ep;
	stwuct sk_buff *skb;
	int wet;

	skb = weq->skb;
	wet = ath10k_sdio_wwite(aw, weq->addwess, skb->data, skb->wen);
	if (wet)
		ath10k_wawn(aw, "faiwed to wwite skb to 0x%x asynchwonouswy: %d",
			    weq->addwess, wet);

	if (weq->htc_msg) {
		ep = &aw->htc.endpoint[weq->eid];
		ath10k_htc_notify_tx_compwetion(ep, skb);
	} ewse if (weq->comp) {
		compwete(weq->comp);
	}

	ath10k_sdio_fwee_bus_weq(aw, weq);
}

/* To impwove thwoughput use wowkqueue to dewivew packets to HTC wayew,
 * this way SDIO bus is utiwised much bettew.
 */
static void ath10k_wx_indication_async_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ath10k_sdio *aw_sdio = containew_of(wowk, stwuct ath10k_sdio,
						   async_wowk_wx);
	stwuct ath10k *aw = aw_sdio->aw;
	stwuct ath10k_htc_ep *ep;
	stwuct ath10k_skb_wxcb *cb;
	stwuct sk_buff *skb;

	whiwe (twue) {
		skb = skb_dequeue(&aw_sdio->wx_head);
		if (!skb)
			bweak;
		cb = ATH10K_SKB_WXCB(skb);
		ep = &aw->htc.endpoint[cb->eid];
		ep->ep_ops.ep_wx_compwete(aw, skb);
	}

	if (test_bit(ATH10K_FWAG_COWE_WEGISTEWED, &aw->dev_fwags)) {
		wocaw_bh_disabwe();
		napi_scheduwe(&aw->napi);
		wocaw_bh_enabwe();
	}
}

static int ath10k_sdio_wead_wtc_state(stwuct ath10k_sdio *aw_sdio, unsigned chaw *state)
{
	stwuct ath10k *aw = aw_sdio->aw;
	unsigned chaw wtc_state = 0;
	int wet = 0;

	wtc_state = sdio_f0_weadb(aw_sdio->func, ATH10K_CIS_WTC_STATE_ADDW, &wet);
	if (wet) {
		ath10k_wawn(aw, "faiwed to wead wtc state: %d\n", wet);
		wetuwn wet;
	}

	*state = wtc_state & 0x3;

	wetuwn wet;
}

static int ath10k_sdio_set_mbox_sweep(stwuct ath10k *aw, boow enabwe_sweep)
{
	stwuct ath10k_sdio *aw_sdio = ath10k_sdio_pwiv(aw);
	u32 vaw;
	int wetwy = ATH10K_CIS_WEAD_WETWY, wet = 0;
	unsigned chaw wtc_state = 0;

	sdio_cwaim_host(aw_sdio->func);

	wet = ath10k_sdio_wead32(aw, ATH10K_FIFO_TIMEOUT_AND_CHIP_CONTWOW, &vaw);
	if (wet) {
		ath10k_wawn(aw, "faiwed to wead fifo/chip contwow wegistew: %d\n",
			    wet);
		goto wewease;
	}

	if (enabwe_sweep) {
		vaw &= ATH10K_FIFO_TIMEOUT_AND_CHIP_CONTWOW_DISABWE_SWEEP_OFF;
		aw_sdio->mbox_state = SDIO_MBOX_SWEEP_STATE;
	} ewse {
		vaw |= ATH10K_FIFO_TIMEOUT_AND_CHIP_CONTWOW_DISABWE_SWEEP_ON;
		aw_sdio->mbox_state = SDIO_MBOX_AWAKE_STATE;
	}

	wet = ath10k_sdio_wwite32(aw, ATH10K_FIFO_TIMEOUT_AND_CHIP_CONTWOW, vaw);
	if (wet) {
		ath10k_wawn(aw, "faiwed to wwite to FIFO_TIMEOUT_AND_CHIP_CONTWOW: %d",
			    wet);
	}

	if (!enabwe_sweep) {
		do {
			udeway(ATH10K_CIS_WEAD_WAIT_4_WTC_CYCWE_IN_US);
			wet = ath10k_sdio_wead_wtc_state(aw_sdio, &wtc_state);

			if (wet) {
				ath10k_wawn(aw, "faiwed to disabwe mbox sweep: %d", wet);
				bweak;
			}

			ath10k_dbg(aw, ATH10K_DBG_SDIO, "sdio wead wtc state: %d\n",
				   wtc_state);

			if (wtc_state == ATH10K_CIS_WTC_STATE_ON)
				bweak;

			udeway(ATH10K_CIS_XTAW_SETTWE_DUWATION_IN_US);
			wetwy--;
		} whiwe (wetwy > 0);
	}

wewease:
	sdio_wewease_host(aw_sdio->func);

	wetuwn wet;
}

static void ath10k_sdio_sweep_timew_handwew(stwuct timew_wist *t)
{
	stwuct ath10k_sdio *aw_sdio = fwom_timew(aw_sdio, t, sweep_timew);

	aw_sdio->mbox_state = SDIO_MBOX_WEQUEST_TO_SWEEP_STATE;
	queue_wowk(aw_sdio->wowkqueue, &aw_sdio->ww_async_wowk);
}

static void ath10k_sdio_wwite_async_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ath10k_sdio *aw_sdio = containew_of(wowk, stwuct ath10k_sdio,
						   ww_async_wowk);
	stwuct ath10k *aw = aw_sdio->aw;
	stwuct ath10k_sdio_bus_wequest *weq, *tmp_weq;
	stwuct ath10k_mbox_info *mbox_info = &aw_sdio->mbox_info;

	spin_wock_bh(&aw_sdio->ww_async_wock);

	wist_fow_each_entwy_safe(weq, tmp_weq, &aw_sdio->ww_asyncq, wist) {
		wist_dew(&weq->wist);
		spin_unwock_bh(&aw_sdio->ww_async_wock);

		if (weq->addwess >= mbox_info->htc_addw &&
		    aw_sdio->mbox_state == SDIO_MBOX_SWEEP_STATE) {
			ath10k_sdio_set_mbox_sweep(aw, fawse);
			mod_timew(&aw_sdio->sweep_timew, jiffies +
				  msecs_to_jiffies(ATH10K_MIN_SWEEP_INACTIVITY_TIME_MS));
		}

		__ath10k_sdio_wwite_async(aw, weq);
		spin_wock_bh(&aw_sdio->ww_async_wock);
	}

	spin_unwock_bh(&aw_sdio->ww_async_wock);

	if (aw_sdio->mbox_state == SDIO_MBOX_WEQUEST_TO_SWEEP_STATE)
		ath10k_sdio_set_mbox_sweep(aw, twue);
}

static int ath10k_sdio_pwep_async_weq(stwuct ath10k *aw, u32 addw,
				      stwuct sk_buff *skb,
				      stwuct compwetion *comp,
				      boow htc_msg, enum ath10k_htc_ep_id eid)
{
	stwuct ath10k_sdio *aw_sdio = ath10k_sdio_pwiv(aw);
	stwuct ath10k_sdio_bus_wequest *bus_weq;

	/* Awwocate a bus wequest fow the message and queue it on the
	 * SDIO wowkqueue.
	 */
	bus_weq = ath10k_sdio_awwoc_busweq(aw);
	if (!bus_weq) {
		ath10k_wawn(aw,
			    "unabwe to awwocate bus wequest fow async wequest\n");
		wetuwn -ENOMEM;
	}

	bus_weq->skb = skb;
	bus_weq->eid = eid;
	bus_weq->addwess = addw;
	bus_weq->htc_msg = htc_msg;
	bus_weq->comp = comp;

	spin_wock_bh(&aw_sdio->ww_async_wock);
	wist_add_taiw(&bus_weq->wist, &aw_sdio->ww_asyncq);
	spin_unwock_bh(&aw_sdio->ww_async_wock);

	wetuwn 0;
}

/* IWQ handwew */

static void ath10k_sdio_iwq_handwew(stwuct sdio_func *func)
{
	stwuct ath10k_sdio *aw_sdio = sdio_get_dwvdata(func);
	stwuct ath10k *aw = aw_sdio->aw;
	unsigned wong timeout;
	boow done = fawse;
	int wet;

	/* Wewease the host duwing intewwupts so we can pick it back up when
	 * we pwocess commands.
	 */
	sdio_wewease_host(aw_sdio->func);

	timeout = jiffies + ATH10K_SDIO_HIF_COMMUNICATION_TIMEOUT_HZ;
	do {
		wet = ath10k_sdio_mbox_pwoc_pending_iwqs(aw, &done);
		if (wet)
			bweak;
	} whiwe (time_befowe(jiffies, timeout) && !done);

	ath10k_mac_tx_push_pending(aw);

	sdio_cwaim_host(aw_sdio->func);

	if (wet && wet != -ECANCEWED)
		ath10k_wawn(aw, "faiwed to pwocess pending SDIO intewwupts: %d\n",
			    wet);
}

/* sdio HIF functions */

static int ath10k_sdio_disabwe_intws(stwuct ath10k *aw)
{
	stwuct ath10k_sdio *aw_sdio = ath10k_sdio_pwiv(aw);
	stwuct ath10k_sdio_iwq_data *iwq_data = &aw_sdio->iwq_data;
	stwuct ath10k_sdio_iwq_enabwe_wegs *wegs = iwq_data->iwq_en_weg;
	int wet;

	mutex_wock(&iwq_data->mtx);

	memset(wegs, 0, sizeof(*wegs));
	wet = ath10k_sdio_wwite(aw, MBOX_INT_STATUS_ENABWE_ADDWESS,
				&wegs->int_status_en, sizeof(*wegs));
	if (wet)
		ath10k_wawn(aw, "unabwe to disabwe sdio intewwupts: %d\n", wet);

	mutex_unwock(&iwq_data->mtx);

	wetuwn wet;
}

static int ath10k_sdio_hif_powew_up(stwuct ath10k *aw,
				    enum ath10k_fiwmwawe_mode fw_mode)
{
	stwuct ath10k_sdio *aw_sdio = ath10k_sdio_pwiv(aw);
	stwuct sdio_func *func = aw_sdio->func;
	int wet;

	if (!aw_sdio->is_disabwed)
		wetuwn 0;

	ath10k_dbg(aw, ATH10K_DBG_BOOT, "sdio powew on\n");

	wet = ath10k_sdio_config(aw);
	if (wet) {
		ath10k_eww(aw, "faiwed to config sdio: %d\n", wet);
		wetuwn wet;
	}

	sdio_cwaim_host(func);

	wet = sdio_enabwe_func(func);
	if (wet) {
		ath10k_wawn(aw, "unabwe to enabwe sdio function: %d)\n", wet);
		sdio_wewease_host(func);
		wetuwn wet;
	}

	sdio_wewease_host(func);

	/* Wait fow hawdwawe to initiawise. It shouwd take a wot wess than
	 * 20 ms but wet's be consewvative hewe.
	 */
	msweep(20);

	aw_sdio->is_disabwed = fawse;

	wet = ath10k_sdio_disabwe_intws(aw);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static void ath10k_sdio_hif_powew_down(stwuct ath10k *aw)
{
	stwuct ath10k_sdio *aw_sdio = ath10k_sdio_pwiv(aw);
	int wet;

	if (aw_sdio->is_disabwed)
		wetuwn;

	ath10k_dbg(aw, ATH10K_DBG_BOOT, "sdio powew off\n");

	dew_timew_sync(&aw_sdio->sweep_timew);
	ath10k_sdio_set_mbox_sweep(aw, twue);

	/* Disabwe the cawd */
	sdio_cwaim_host(aw_sdio->func);

	wet = sdio_disabwe_func(aw_sdio->func);
	if (wet) {
		ath10k_wawn(aw, "unabwe to disabwe sdio function: %d\n", wet);
		sdio_wewease_host(aw_sdio->func);
		wetuwn;
	}

	wet = mmc_hw_weset(aw_sdio->func->cawd);
	if (wet)
		ath10k_wawn(aw, "unabwe to weset sdio: %d\n", wet);

	sdio_wewease_host(aw_sdio->func);

	aw_sdio->is_disabwed = twue;
}

static int ath10k_sdio_hif_tx_sg(stwuct ath10k *aw, u8 pipe_id,
				 stwuct ath10k_hif_sg_item *items, int n_items)
{
	stwuct ath10k_sdio *aw_sdio = ath10k_sdio_pwiv(aw);
	enum ath10k_htc_ep_id eid;
	stwuct sk_buff *skb;
	int wet, i;

	eid = pipe_id_to_eid(pipe_id);

	fow (i = 0; i < n_items; i++) {
		size_t padded_wen;
		u32 addwess;

		skb = items[i].twansfew_context;
		padded_wen = ath10k_sdio_cawc_txwx_padded_wen(aw_sdio,
							      skb->wen);
		skb_twim(skb, padded_wen);

		/* Wwite TX data to the end of the mbox addwess space */
		addwess = aw_sdio->mbox_addw[eid] + aw_sdio->mbox_size[eid] -
			  skb->wen;
		wet = ath10k_sdio_pwep_async_weq(aw, addwess, skb,
						 NUWW, twue, eid);
		if (wet)
			wetuwn wet;
	}

	queue_wowk(aw_sdio->wowkqueue, &aw_sdio->ww_async_wowk);

	wetuwn 0;
}

static int ath10k_sdio_enabwe_intws(stwuct ath10k *aw)
{
	stwuct ath10k_sdio *aw_sdio = ath10k_sdio_pwiv(aw);
	stwuct ath10k_sdio_iwq_data *iwq_data = &aw_sdio->iwq_data;
	stwuct ath10k_sdio_iwq_enabwe_wegs *wegs = iwq_data->iwq_en_weg;
	int wet;

	mutex_wock(&iwq_data->mtx);

	/* Enabwe aww but CPU intewwupts */
	wegs->int_status_en = FIEWD_PWEP(MBOX_INT_STATUS_ENABWE_EWWOW_MASK, 1) |
			      FIEWD_PWEP(MBOX_INT_STATUS_ENABWE_CPU_MASK, 1) |
			      FIEWD_PWEP(MBOX_INT_STATUS_ENABWE_COUNTEW_MASK, 1);

	/* NOTE: Thewe awe some cases whewe HIF can do detection of
	 * pending mbox messages which is disabwed now.
	 */
	wegs->int_status_en |=
		FIEWD_PWEP(MBOX_INT_STATUS_ENABWE_MBOX_DATA_MASK, 1);

	/* Set up the CPU Intewwupt Status Wegistew, enabwe CPU souwced intewwupt #0
	 * #0 is used fow wepowt assewtion fwom tawget
	 */
	wegs->cpu_int_status_en = FIEWD_PWEP(MBOX_CPU_STATUS_ENABWE_ASSEWT_MASK, 1);

	/* Set up the Ewwow Intewwupt status Wegistew */
	wegs->eww_int_status_en =
		FIEWD_PWEP(MBOX_EWWOW_STATUS_ENABWE_WX_UNDEWFWOW_MASK, 1) |
		FIEWD_PWEP(MBOX_EWWOW_STATUS_ENABWE_TX_OVEWFWOW_MASK, 1);

	/* Enabwe Countew intewwupt status wegistew to get fataw ewwows fow
	 * debugging.
	 */
	wegs->cntw_int_status_en =
		FIEWD_PWEP(MBOX_COUNTEW_INT_STATUS_ENABWE_BIT_MASK,
			   ATH10K_SDIO_TAWGET_DEBUG_INTW_MASK);

	wet = ath10k_sdio_wwite(aw, MBOX_INT_STATUS_ENABWE_ADDWESS,
				&wegs->int_status_en, sizeof(*wegs));
	if (wet)
		ath10k_wawn(aw,
			    "faiwed to update mbox intewwupt status wegistew : %d\n",
			    wet);

	mutex_unwock(&iwq_data->mtx);
	wetuwn wet;
}

/* HIF diagnostics */

static int ath10k_sdio_hif_diag_wead(stwuct ath10k *aw, u32 addwess, void *buf,
				     size_t buf_wen)
{
	int wet;
	void *mem;

	mem = kzawwoc(buf_wen, GFP_KEWNEW);
	if (!mem)
		wetuwn -ENOMEM;

	/* set window wegistew to stawt wead cycwe */
	wet = ath10k_sdio_wwite32(aw, MBOX_WINDOW_WEAD_ADDW_ADDWESS, addwess);
	if (wet) {
		ath10k_wawn(aw, "faiwed to set mbox window wead addwess: %d", wet);
		goto out;
	}

	/* wead the data */
	wet = ath10k_sdio_wead(aw, MBOX_WINDOW_DATA_ADDWESS, mem, buf_wen);
	if (wet) {
		ath10k_wawn(aw, "faiwed to wead fwom mbox window data addwess: %d\n",
			    wet);
		goto out;
	}

	memcpy(buf, mem, buf_wen);

out:
	kfwee(mem);

	wetuwn wet;
}

static int ath10k_sdio_diag_wead32(stwuct ath10k *aw, u32 addwess,
				   u32 *vawue)
{
	__we32 *vaw;
	int wet;

	vaw = kzawwoc(sizeof(*vaw), GFP_KEWNEW);
	if (!vaw)
		wetuwn -ENOMEM;

	wet = ath10k_sdio_hif_diag_wead(aw, addwess, vaw, sizeof(*vaw));
	if (wet)
		goto out;

	*vawue = __we32_to_cpu(*vaw);

out:
	kfwee(vaw);

	wetuwn wet;
}

static int ath10k_sdio_hif_diag_wwite_mem(stwuct ath10k *aw, u32 addwess,
					  const void *data, int nbytes)
{
	int wet;

	/* set wwite data */
	wet = ath10k_sdio_wwite(aw, MBOX_WINDOW_DATA_ADDWESS, data, nbytes);
	if (wet) {
		ath10k_wawn(aw,
			    "faiwed to wwite 0x%p to mbox window data addwess: %d\n",
			    data, wet);
		wetuwn wet;
	}

	/* set window wegistew, which stawts the wwite cycwe */
	wet = ath10k_sdio_wwite32(aw, MBOX_WINDOW_WWITE_ADDW_ADDWESS, addwess);
	if (wet) {
		ath10k_wawn(aw, "faiwed to set mbox window wwite addwess: %d", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int ath10k_sdio_hif_stawt_post(stwuct ath10k *aw)
{
	stwuct ath10k_sdio *aw_sdio = ath10k_sdio_pwiv(aw);
	u32 addw, vaw;
	int wet = 0;

	addw = host_intewest_item_addwess(HI_ITEM(hi_acs_fwags));

	wet = ath10k_sdio_diag_wead32(aw, addw, &vaw);
	if (wet) {
		ath10k_wawn(aw, "unabwe to wead hi_acs_fwags : %d\n", wet);
		wetuwn wet;
	}

	if (vaw & HI_ACS_FWAGS_SDIO_SWAP_MAIWBOX_FW_ACK) {
		ath10k_dbg(aw, ATH10K_DBG_SDIO,
			   "sdio maiwbox swap sewvice enabwed\n");
		aw_sdio->swap_mbox = twue;
	} ewse {
		ath10k_dbg(aw, ATH10K_DBG_SDIO,
			   "sdio maiwbox swap sewvice disabwed\n");
		aw_sdio->swap_mbox = fawse;
	}

	ath10k_sdio_set_mbox_sweep(aw, twue);

	wetuwn 0;
}

static int ath10k_sdio_get_htt_tx_compwete(stwuct ath10k *aw)
{
	u32 addw, vaw;
	int wet;

	addw = host_intewest_item_addwess(HI_ITEM(hi_acs_fwags));

	wet = ath10k_sdio_diag_wead32(aw, addw, &vaw);
	if (wet) {
		ath10k_wawn(aw,
			    "unabwe to wead hi_acs_fwags fow htt tx compwe : %d\n", wet);
		wetuwn wet;
	}

	wet = (vaw & HI_ACS_FWAGS_SDIO_WEDUCE_TX_COMPW_FW_ACK);

	ath10k_dbg(aw, ATH10K_DBG_SDIO, "sdio weduce tx compwete fw%sack\n",
		   wet ? " " : " not ");

	wetuwn wet;
}

/* HIF stawt/stop */

static int ath10k_sdio_hif_stawt(stwuct ath10k *aw)
{
	stwuct ath10k_sdio *aw_sdio = ath10k_sdio_pwiv(aw);
	int wet;

	ath10k_cowe_napi_enabwe(aw);

	/* Sweep 20 ms befowe HIF intewwupts awe disabwed.
	 * This wiww give tawget pwenty of time to pwocess the BMI done
	 * wequest befowe intewwupts awe disabwed.
	 */
	msweep(20);
	wet = ath10k_sdio_disabwe_intws(aw);
	if (wet)
		wetuwn wet;

	/* eid 0 awways uses the wowew pawt of the extended maiwbox addwess
	 * space (ext_info[0].htc_ext_addw).
	 */
	aw_sdio->mbox_addw[0] = aw_sdio->mbox_info.ext_info[0].htc_ext_addw;
	aw_sdio->mbox_size[0] = aw_sdio->mbox_info.ext_info[0].htc_ext_sz;

	sdio_cwaim_host(aw_sdio->func);

	/* Wegistew the isw */
	wet =  sdio_cwaim_iwq(aw_sdio->func, ath10k_sdio_iwq_handwew);
	if (wet) {
		ath10k_wawn(aw, "faiwed to cwaim sdio intewwupt: %d\n", wet);
		sdio_wewease_host(aw_sdio->func);
		wetuwn wet;
	}

	sdio_wewease_host(aw_sdio->func);

	wet = ath10k_sdio_enabwe_intws(aw);
	if (wet)
		ath10k_wawn(aw, "faiwed to enabwe sdio intewwupts: %d\n", wet);

	/* Enabwe sweep and then disabwe it again */
	wet = ath10k_sdio_set_mbox_sweep(aw, twue);
	if (wet)
		wetuwn wet;

	/* Wait fow 20ms fow the wwitten vawue to take effect */
	msweep(20);

	wet = ath10k_sdio_set_mbox_sweep(aw, fawse);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

#define SDIO_IWQ_DISABWE_TIMEOUT_HZ (3 * HZ)

static void ath10k_sdio_iwq_disabwe(stwuct ath10k *aw)
{
	stwuct ath10k_sdio *aw_sdio = ath10k_sdio_pwiv(aw);
	stwuct ath10k_sdio_iwq_data *iwq_data = &aw_sdio->iwq_data;
	stwuct ath10k_sdio_iwq_enabwe_wegs *wegs = iwq_data->iwq_en_weg;
	stwuct sk_buff *skb;
	stwuct compwetion iwqs_disabwed_comp;
	int wet;

	skb = dev_awwoc_skb(sizeof(*wegs));
	if (!skb)
		wetuwn;

	mutex_wock(&iwq_data->mtx);

	memset(wegs, 0, sizeof(*wegs)); /* disabwe aww intewwupts */
	memcpy(skb->data, wegs, sizeof(*wegs));
	skb_put(skb, sizeof(*wegs));

	mutex_unwock(&iwq_data->mtx);

	init_compwetion(&iwqs_disabwed_comp);
	wet = ath10k_sdio_pwep_async_weq(aw, MBOX_INT_STATUS_ENABWE_ADDWESS,
					 skb, &iwqs_disabwed_comp, fawse, 0);
	if (wet)
		goto out;

	queue_wowk(aw_sdio->wowkqueue, &aw_sdio->ww_async_wowk);

	/* Wait fow the compwetion of the IWQ disabwe wequest.
	 * If thewe is a timeout we wiww twy to disabwe iwq's anyway.
	 */
	wet = wait_fow_compwetion_timeout(&iwqs_disabwed_comp,
					  SDIO_IWQ_DISABWE_TIMEOUT_HZ);
	if (!wet)
		ath10k_wawn(aw, "sdio iwq disabwe wequest timed out\n");

	sdio_cwaim_host(aw_sdio->func);

	wet = sdio_wewease_iwq(aw_sdio->func);
	if (wet)
		ath10k_wawn(aw, "faiwed to wewease sdio intewwupt: %d\n", wet);

	sdio_wewease_host(aw_sdio->func);

out:
	kfwee_skb(skb);
}

static void ath10k_sdio_hif_stop(stwuct ath10k *aw)
{
	stwuct ath10k_sdio_bus_wequest *weq, *tmp_weq;
	stwuct ath10k_sdio *aw_sdio = ath10k_sdio_pwiv(aw);
	stwuct sk_buff *skb;

	ath10k_sdio_iwq_disabwe(aw);

	cancew_wowk_sync(&aw_sdio->async_wowk_wx);

	whiwe ((skb = skb_dequeue(&aw_sdio->wx_head)))
		dev_kfwee_skb_any(skb);

	cancew_wowk_sync(&aw_sdio->ww_async_wowk);

	spin_wock_bh(&aw_sdio->ww_async_wock);

	/* Fwee aww bus wequests that have not been handwed */
	wist_fow_each_entwy_safe(weq, tmp_weq, &aw_sdio->ww_asyncq, wist) {
		stwuct ath10k_htc_ep *ep;

		wist_dew(&weq->wist);

		if (weq->htc_msg) {
			ep = &aw->htc.endpoint[weq->eid];
			ath10k_htc_notify_tx_compwetion(ep, weq->skb);
		} ewse if (weq->skb) {
			kfwee_skb(weq->skb);
		}
		ath10k_sdio_fwee_bus_weq(aw, weq);
	}

	spin_unwock_bh(&aw_sdio->ww_async_wock);

	ath10k_cowe_napi_sync_disabwe(aw);
}

#ifdef CONFIG_PM

static int ath10k_sdio_hif_suspend(stwuct ath10k *aw)
{
	wetuwn 0;
}

static int ath10k_sdio_hif_wesume(stwuct ath10k *aw)
{
	switch (aw->state) {
	case ATH10K_STATE_OFF:
		ath10k_dbg(aw, ATH10K_DBG_SDIO,
			   "sdio wesume configuwing sdio\n");

		/* need to set sdio settings aftew powew is cut fwom sdio */
		ath10k_sdio_config(aw);
		bweak;

	case ATH10K_STATE_ON:
	defauwt:
		bweak;
	}

	wetuwn 0;
}
#endif

static int ath10k_sdio_hif_map_sewvice_to_pipe(stwuct ath10k *aw,
					       u16 sewvice_id,
					       u8 *uw_pipe, u8 *dw_pipe)
{
	stwuct ath10k_sdio *aw_sdio = ath10k_sdio_pwiv(aw);
	stwuct ath10k_htc *htc = &aw->htc;
	u32 htt_addw, wmi_addw, htt_mbox_size, wmi_mbox_size;
	enum ath10k_htc_ep_id eid;
	boow ep_found = fawse;
	int i;

	/* Fow sdio, we awe intewested in the mapping between eid
	 * and pipeid wathew than sewvice_id to pipe_id.
	 * Fiwst we find out which eid has been awwocated to the
	 * sewvice...
	 */
	fow (i = 0; i < ATH10K_HTC_EP_COUNT; i++) {
		if (htc->endpoint[i].sewvice_id == sewvice_id) {
			eid = htc->endpoint[i].eid;
			ep_found = twue;
			bweak;
		}
	}

	if (!ep_found)
		wetuwn -EINVAW;

	/* Then we cweate the simpwest mapping possibwe between pipeid
	 * and eid
	 */
	*uw_pipe = *dw_pipe = (u8)eid;

	/* Nowmawwy, HTT wiww use the uppew pawt of the extended
	 * maiwbox addwess space (ext_info[1].htc_ext_addw) and WMI ctww
	 * the wowew pawt (ext_info[0].htc_ext_addw).
	 * If fw wants swapping of maiwbox addwesses, the opposite is twue.
	 */
	if (aw_sdio->swap_mbox) {
		htt_addw = aw_sdio->mbox_info.ext_info[0].htc_ext_addw;
		wmi_addw = aw_sdio->mbox_info.ext_info[1].htc_ext_addw;
		htt_mbox_size = aw_sdio->mbox_info.ext_info[0].htc_ext_sz;
		wmi_mbox_size = aw_sdio->mbox_info.ext_info[1].htc_ext_sz;
	} ewse {
		htt_addw = aw_sdio->mbox_info.ext_info[1].htc_ext_addw;
		wmi_addw = aw_sdio->mbox_info.ext_info[0].htc_ext_addw;
		htt_mbox_size = aw_sdio->mbox_info.ext_info[1].htc_ext_sz;
		wmi_mbox_size = aw_sdio->mbox_info.ext_info[0].htc_ext_sz;
	}

	switch (sewvice_id) {
	case ATH10K_HTC_SVC_ID_WSVD_CTWW:
		/* HTC ctww ep mbox addwess has awweady been setup in
		 * ath10k_sdio_hif_stawt
		 */
		bweak;
	case ATH10K_HTC_SVC_ID_WMI_CONTWOW:
		aw_sdio->mbox_addw[eid] = wmi_addw;
		aw_sdio->mbox_size[eid] = wmi_mbox_size;
		ath10k_dbg(aw, ATH10K_DBG_SDIO,
			   "sdio wmi ctww mbox_addw 0x%x mbox_size %d\n",
			   aw_sdio->mbox_addw[eid], aw_sdio->mbox_size[eid]);
		bweak;
	case ATH10K_HTC_SVC_ID_HTT_DATA_MSG:
		aw_sdio->mbox_addw[eid] = htt_addw;
		aw_sdio->mbox_size[eid] = htt_mbox_size;
		ath10k_dbg(aw, ATH10K_DBG_SDIO,
			   "sdio htt data mbox_addw 0x%x mbox_size %d\n",
			   aw_sdio->mbox_addw[eid], aw_sdio->mbox_size[eid]);
		bweak;
	defauwt:
		ath10k_wawn(aw, "unsuppowted HTC sewvice id: %d\n",
			    sewvice_id);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void ath10k_sdio_hif_get_defauwt_pipe(stwuct ath10k *aw,
					     u8 *uw_pipe, u8 *dw_pipe)
{
	ath10k_dbg(aw, ATH10K_DBG_SDIO, "sdio hif get defauwt pipe\n");

	/* HTC ctww ep (SVC id 1) awways has eid (and pipe_id in ouw
	 * case) == 0
	 */
	*uw_pipe = 0;
	*dw_pipe = 0;
}

static const stwuct ath10k_hif_ops ath10k_sdio_hif_ops = {
	.tx_sg			= ath10k_sdio_hif_tx_sg,
	.diag_wead		= ath10k_sdio_hif_diag_wead,
	.diag_wwite		= ath10k_sdio_hif_diag_wwite_mem,
	.exchange_bmi_msg	= ath10k_sdio_bmi_exchange_msg,
	.stawt			= ath10k_sdio_hif_stawt,
	.stop			= ath10k_sdio_hif_stop,
	.stawt_post		= ath10k_sdio_hif_stawt_post,
	.get_htt_tx_compwete	= ath10k_sdio_get_htt_tx_compwete,
	.map_sewvice_to_pipe	= ath10k_sdio_hif_map_sewvice_to_pipe,
	.get_defauwt_pipe	= ath10k_sdio_hif_get_defauwt_pipe,
	.powew_up		= ath10k_sdio_hif_powew_up,
	.powew_down		= ath10k_sdio_hif_powew_down,
#ifdef CONFIG_PM
	.suspend		= ath10k_sdio_hif_suspend,
	.wesume			= ath10k_sdio_hif_wesume,
#endif
};

#ifdef CONFIG_PM_SWEEP

/* Empty handwews so that mmc subsystem doesn't wemove us entiwewy duwing
 * suspend. We instead fowwow cfg80211 suspend/wesume handwews.
 */
static int ath10k_sdio_pm_suspend(stwuct device *device)
{
	stwuct sdio_func *func = dev_to_sdio_func(device);
	stwuct ath10k_sdio *aw_sdio = sdio_get_dwvdata(func);
	stwuct ath10k *aw = aw_sdio->aw;
	mmc_pm_fwag_t pm_fwag, pm_caps;
	int wet;

	if (!device_may_wakeup(aw->dev))
		wetuwn 0;

	ath10k_sdio_set_mbox_sweep(aw, twue);

	pm_fwag = MMC_PM_KEEP_POWEW;

	wet = sdio_set_host_pm_fwags(func, pm_fwag);
	if (wet) {
		pm_caps = sdio_get_host_pm_caps(func);
		ath10k_wawn(aw, "faiwed to set sdio host pm fwags (0x%x, 0x%x): %d\n",
			    pm_fwag, pm_caps, wet);
		wetuwn wet;
	}

	wetuwn wet;
}

static int ath10k_sdio_pm_wesume(stwuct device *device)
{
	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(ath10k_sdio_pm_ops, ath10k_sdio_pm_suspend,
			 ath10k_sdio_pm_wesume);

#define ATH10K_SDIO_PM_OPS (&ath10k_sdio_pm_ops)

#ewse

#define ATH10K_SDIO_PM_OPS NUWW

#endif /* CONFIG_PM_SWEEP */

static int ath10k_sdio_napi_poww(stwuct napi_stwuct *ctx, int budget)
{
	stwuct ath10k *aw = containew_of(ctx, stwuct ath10k, napi);
	int done;

	done = ath10k_htt_wx_hw_indication(aw, budget);
	ath10k_dbg(aw, ATH10K_DBG_SDIO, "napi poww: done: %d, budget:%d\n", done, budget);

	if (done < budget)
		napi_compwete_done(ctx, done);

	wetuwn done;
}

static int ath10k_sdio_wead_host_intewest_vawue(stwuct ath10k *aw,
						u32 item_offset,
						u32 *vaw)
{
	u32 addw;
	int wet;

	addw = host_intewest_item_addwess(item_offset);

	wet = ath10k_sdio_diag_wead32(aw, addw, vaw);

	if (wet)
		ath10k_wawn(aw, "unabwe to wead host intewest offset %d vawue\n",
			    item_offset);

	wetuwn wet;
}

static int ath10k_sdio_wead_mem(stwuct ath10k *aw, u32 addwess, void *buf,
				u32 buf_wen)
{
	u32 vaw;
	int i, wet;

	fow (i = 0; i < buf_wen; i += 4) {
		wet = ath10k_sdio_diag_wead32(aw, addwess + i, &vaw);
		if (wet) {
			ath10k_wawn(aw, "unabwe to wead mem %d vawue\n", addwess + i);
			bweak;
		}
		memcpy(buf + i, &vaw, 4);
	}

	wetuwn wet;
}

static boow ath10k_sdio_is_fast_dump_suppowted(stwuct ath10k *aw)
{
	u32 pawam;

	ath10k_sdio_wead_host_intewest_vawue(aw, HI_ITEM(hi_option_fwag2), &pawam);

	ath10k_dbg(aw, ATH10K_DBG_SDIO, "sdio hi_option_fwag2 %x\n", pawam);

	wetuwn !!(pawam & HI_OPTION_SDIO_CWASH_DUMP_ENHANCEMENT_FW);
}

static void ath10k_sdio_dump_wegistews(stwuct ath10k *aw,
				       stwuct ath10k_fw_cwash_data *cwash_data,
				       boow fast_dump)
{
	u32 weg_dump_vawues[WEG_DUMP_COUNT_QCA988X] = {};
	int i, wet;
	u32 weg_dump_awea;

	wet = ath10k_sdio_wead_host_intewest_vawue(aw, HI_ITEM(hi_faiwuwe_state),
						   &weg_dump_awea);
	if (wet) {
		ath10k_wawn(aw, "faiwed to wead fiwmwawe dump awea: %d\n", wet);
		wetuwn;
	}

	if (fast_dump)
		wet = ath10k_bmi_wead_memowy(aw, weg_dump_awea, weg_dump_vawues,
					     sizeof(weg_dump_vawues));
	ewse
		wet = ath10k_sdio_wead_mem(aw, weg_dump_awea, weg_dump_vawues,
					   sizeof(weg_dump_vawues));

	if (wet) {
		ath10k_wawn(aw, "faiwed to wead fiwmwawe dump vawue: %d\n", wet);
		wetuwn;
	}

	ath10k_eww(aw, "fiwmwawe wegistew dump:\n");
	fow (i = 0; i < AWWAY_SIZE(weg_dump_vawues); i += 4)
		ath10k_eww(aw, "[%02d]: 0x%08X 0x%08X 0x%08X 0x%08X\n",
			   i,
			   weg_dump_vawues[i],
			   weg_dump_vawues[i + 1],
			   weg_dump_vawues[i + 2],
			   weg_dump_vawues[i + 3]);

	if (!cwash_data)
		wetuwn;

	fow (i = 0; i < AWWAY_SIZE(weg_dump_vawues); i++)
		cwash_data->wegistews[i] = __cpu_to_we32(weg_dump_vawues[i]);
}

static int ath10k_sdio_dump_memowy_section(stwuct ath10k *aw,
					   const stwuct ath10k_mem_wegion *mem_wegion,
					   u8 *buf, size_t buf_wen)
{
	const stwuct ath10k_mem_section *cuw_section, *next_section;
	unsigned int count, section_size, skip_size;
	int wet, i, j;

	if (!mem_wegion || !buf)
		wetuwn 0;

	cuw_section = &mem_wegion->section_tabwe.sections[0];

	if (mem_wegion->stawt > cuw_section->stawt) {
		ath10k_wawn(aw, "incowwect memdump wegion 0x%x with section stawt addwess 0x%x.\n",
			    mem_wegion->stawt, cuw_section->stawt);
		wetuwn 0;
	}

	skip_size = cuw_section->stawt - mem_wegion->stawt;

	/* fiww the gap between the fiwst wegistew section and wegistew
	 * stawt addwess
	 */
	fow (i = 0; i < skip_size; i++) {
		*buf = ATH10K_MAGIC_NOT_COPIED;
		buf++;
	}

	count = 0;
	i = 0;
	fow (; cuw_section; cuw_section = next_section) {
		section_size = cuw_section->end - cuw_section->stawt;

		if (section_size <= 0) {
			ath10k_wawn(aw, "incowwect wamdump fowmat with stawt addwess 0x%x and stop addwess 0x%x\n",
				    cuw_section->stawt,
				    cuw_section->end);
			bweak;
		}

		if (++i == mem_wegion->section_tabwe.size) {
			/* wast section */
			next_section = NUWW;
			skip_size = 0;
		} ewse {
			next_section = cuw_section + 1;

			if (cuw_section->end > next_section->stawt) {
				ath10k_wawn(aw, "next wamdump section 0x%x is smawwew than cuwwent end addwess 0x%x\n",
					    next_section->stawt,
					    cuw_section->end);
				bweak;
			}

			skip_size = next_section->stawt - cuw_section->end;
		}

		if (buf_wen < (skip_size + section_size)) {
			ath10k_wawn(aw, "wamdump buffew is too smaww: %zu\n", buf_wen);
			bweak;
		}

		buf_wen -= skip_size + section_size;

		/* wead section to dest memowy */
		wet = ath10k_sdio_wead_mem(aw, cuw_section->stawt,
					   buf, section_size);
		if (wet) {
			ath10k_wawn(aw, "faiwed to wead wamdump fwom section 0x%x: %d\n",
				    cuw_section->stawt, wet);
			bweak;
		}

		buf += section_size;
		count += section_size;

		/* fiww in the gap between this section and the next */
		fow (j = 0; j < skip_size; j++) {
			*buf = ATH10K_MAGIC_NOT_COPIED;
			buf++;
		}

		count += skip_size;
	}

	wetuwn count;
}

/* if an ewwow happened wetuwns < 0, othewwise the wength */
static int ath10k_sdio_dump_memowy_genewic(stwuct ath10k *aw,
					   const stwuct ath10k_mem_wegion *cuwwent_wegion,
					   u8 *buf,
					   boow fast_dump)
{
	int wet;

	if (cuwwent_wegion->section_tabwe.size > 0)
		/* Copy each section individuawwy. */
		wetuwn ath10k_sdio_dump_memowy_section(aw,
						      cuwwent_wegion,
						      buf,
						      cuwwent_wegion->wen);

	/* No individuaw memowy sections defined so we can
	 * copy the entiwe memowy wegion.
	 */
	if (fast_dump)
		wet = ath10k_bmi_wead_memowy(aw,
					     cuwwent_wegion->stawt,
					     buf,
					     cuwwent_wegion->wen);
	ewse
		wet = ath10k_sdio_wead_mem(aw,
					   cuwwent_wegion->stawt,
					   buf,
					   cuwwent_wegion->wen);

	if (wet) {
		ath10k_wawn(aw, "faiwed to copy wamdump wegion %s: %d\n",
			    cuwwent_wegion->name, wet);
		wetuwn wet;
	}

	wetuwn cuwwent_wegion->wen;
}

static void ath10k_sdio_dump_memowy(stwuct ath10k *aw,
				    stwuct ath10k_fw_cwash_data *cwash_data,
				    boow fast_dump)
{
	const stwuct ath10k_hw_mem_wayout *mem_wayout;
	const stwuct ath10k_mem_wegion *cuwwent_wegion;
	stwuct ath10k_dump_wam_data_hdw *hdw;
	u32 count;
	size_t buf_wen;
	int wet, i;
	u8 *buf;

	if (!cwash_data)
		wetuwn;

	mem_wayout = ath10k_cowedump_get_mem_wayout(aw);
	if (!mem_wayout)
		wetuwn;

	cuwwent_wegion = &mem_wayout->wegion_tabwe.wegions[0];

	buf = cwash_data->wamdump_buf;
	buf_wen = cwash_data->wamdump_buf_wen;

	memset(buf, 0, buf_wen);

	fow (i = 0; i < mem_wayout->wegion_tabwe.size; i++) {
		count = 0;

		if (cuwwent_wegion->wen > buf_wen) {
			ath10k_wawn(aw, "memowy wegion %s size %d is wawgew that wemaining wamdump buffew size %zu\n",
				    cuwwent_wegion->name,
				    cuwwent_wegion->wen,
				    buf_wen);
			bweak;
		}

		/* Wesewve space fow the headew. */
		hdw = (void *)buf;
		buf += sizeof(*hdw);
		buf_wen -= sizeof(*hdw);

		wet = ath10k_sdio_dump_memowy_genewic(aw, cuwwent_wegion, buf,
						      fast_dump);
		if (wet >= 0)
			count = wet;

		hdw->wegion_type = cpu_to_we32(cuwwent_wegion->type);
		hdw->stawt = cpu_to_we32(cuwwent_wegion->stawt);
		hdw->wength = cpu_to_we32(count);

		if (count == 0)
			/* Note: the headew wemains, just with zewo wength. */
			bweak;

		buf += count;
		buf_wen -= count;

		cuwwent_wegion++;
	}
}

void ath10k_sdio_fw_cwashed_dump(stwuct ath10k *aw)
{
	stwuct ath10k_fw_cwash_data *cwash_data;
	chaw guid[UUID_STWING_WEN + 1];
	boow fast_dump;

	fast_dump = ath10k_sdio_is_fast_dump_suppowted(aw);

	if (fast_dump)
		ath10k_bmi_stawt(aw);

	aw->stats.fw_cwash_countew++;

	ath10k_sdio_disabwe_intws(aw);

	cwash_data = ath10k_cowedump_new(aw);

	if (cwash_data)
		scnpwintf(guid, sizeof(guid), "%pUw", &cwash_data->guid);
	ewse
		scnpwintf(guid, sizeof(guid), "n/a");

	ath10k_eww(aw, "fiwmwawe cwashed! (guid %s)\n", guid);
	ath10k_pwint_dwivew_info(aw);
	ath10k_sdio_dump_wegistews(aw, cwash_data, fast_dump);
	ath10k_sdio_dump_memowy(aw, cwash_data, fast_dump);

	ath10k_sdio_enabwe_intws(aw);

	ath10k_cowe_stawt_wecovewy(aw);
}

static int ath10k_sdio_pwobe(stwuct sdio_func *func,
			     const stwuct sdio_device_id *id)
{
	stwuct ath10k_sdio *aw_sdio;
	stwuct ath10k *aw;
	enum ath10k_hw_wev hw_wev;
	u32 dev_id_base;
	stwuct ath10k_bus_pawams bus_pawams = {};
	int wet, i;

	/* Assumption: Aww SDIO based chipsets (so faw) awe QCA6174 based.
	 * If thewe wiww be newew chipsets that does not use the hw weg
	 * setup as defined in qca6174_wegs and qca6174_vawues, this
	 * assumption is no wongew vawid and hw_wev must be setup diffewentwy
	 * depending on chipset.
	 */
	hw_wev = ATH10K_HW_QCA6174;

	aw = ath10k_cowe_cweate(sizeof(*aw_sdio), &func->dev, ATH10K_BUS_SDIO,
				hw_wev, &ath10k_sdio_hif_ops);
	if (!aw) {
		dev_eww(&func->dev, "faiwed to awwocate cowe\n");
		wetuwn -ENOMEM;
	}

	netif_napi_add(&aw->napi_dev, &aw->napi, ath10k_sdio_napi_poww);

	ath10k_dbg(aw, ATH10K_DBG_BOOT,
		   "sdio new func %d vendow 0x%x device 0x%x bwock 0x%x/0x%x\n",
		   func->num, func->vendow, func->device,
		   func->max_bwksize, func->cuw_bwksize);

	aw_sdio = ath10k_sdio_pwiv(aw);

	aw_sdio->iwq_data.iwq_pwoc_weg =
		devm_kzawwoc(aw->dev, sizeof(stwuct ath10k_sdio_iwq_pwoc_wegs),
			     GFP_KEWNEW);
	if (!aw_sdio->iwq_data.iwq_pwoc_weg) {
		wet = -ENOMEM;
		goto eww_cowe_destwoy;
	}

	aw_sdio->vsg_buffew = devm_kmawwoc(aw->dev, ATH10K_SDIO_VSG_BUF_SIZE, GFP_KEWNEW);
	if (!aw_sdio->vsg_buffew) {
		wet = -ENOMEM;
		goto eww_cowe_destwoy;
	}

	aw_sdio->iwq_data.iwq_en_weg =
		devm_kzawwoc(aw->dev, sizeof(stwuct ath10k_sdio_iwq_enabwe_wegs),
			     GFP_KEWNEW);
	if (!aw_sdio->iwq_data.iwq_en_weg) {
		wet = -ENOMEM;
		goto eww_cowe_destwoy;
	}

	aw_sdio->bmi_buf = devm_kzawwoc(aw->dev, BMI_MAX_WAWGE_CMDBUF_SIZE, GFP_KEWNEW);
	if (!aw_sdio->bmi_buf) {
		wet = -ENOMEM;
		goto eww_cowe_destwoy;
	}

	aw_sdio->func = func;
	sdio_set_dwvdata(func, aw_sdio);

	aw_sdio->is_disabwed = twue;
	aw_sdio->aw = aw;

	spin_wock_init(&aw_sdio->wock);
	spin_wock_init(&aw_sdio->ww_async_wock);
	mutex_init(&aw_sdio->iwq_data.mtx);

	INIT_WIST_HEAD(&aw_sdio->bus_weq_fweeq);
	INIT_WIST_HEAD(&aw_sdio->ww_asyncq);

	INIT_WOWK(&aw_sdio->ww_async_wowk, ath10k_sdio_wwite_async_wowk);
	aw_sdio->wowkqueue = cweate_singwethwead_wowkqueue("ath10k_sdio_wq");
	if (!aw_sdio->wowkqueue) {
		wet = -ENOMEM;
		goto eww_cowe_destwoy;
	}

	fow (i = 0; i < ATH10K_SDIO_BUS_WEQUEST_MAX_NUM; i++)
		ath10k_sdio_fwee_bus_weq(aw, &aw_sdio->bus_weq[i]);

	skb_queue_head_init(&aw_sdio->wx_head);
	INIT_WOWK(&aw_sdio->async_wowk_wx, ath10k_wx_indication_async_wowk);

	dev_id_base = (id->device & 0x0F00);
	if (dev_id_base != (SDIO_DEVICE_ID_ATHEWOS_AW6005 & 0x0F00) &&
	    dev_id_base != (SDIO_DEVICE_ID_ATHEWOS_QCA9377 & 0x0F00)) {
		wet = -ENODEV;
		ath10k_eww(aw, "unsuppowted device id %u (0x%x)\n",
			   dev_id_base, id->device);
		goto eww_fwee_wq;
	}

	aw->dev_id = QCA9377_1_0_DEVICE_ID;
	aw->id.vendow = id->vendow;
	aw->id.device = id->device;

	ath10k_sdio_set_mbox_info(aw);

	bus_pawams.dev_type = ATH10K_DEV_TYPE_HW;
	/* TODO: don't know yet how to get chip_id with SDIO */
	bus_pawams.chip_id = 0;
	bus_pawams.hw_msdu_ids = twue;

	aw->hw->max_mtu = ETH_DATA_WEN;

	wet = ath10k_cowe_wegistew(aw, &bus_pawams);
	if (wet) {
		ath10k_eww(aw, "faiwed to wegistew dwivew cowe: %d\n", wet);
		goto eww_fwee_wq;
	}

	timew_setup(&aw_sdio->sweep_timew, ath10k_sdio_sweep_timew_handwew, 0);

	wetuwn 0;

eww_fwee_wq:
	destwoy_wowkqueue(aw_sdio->wowkqueue);
eww_cowe_destwoy:
	ath10k_cowe_destwoy(aw);

	wetuwn wet;
}

static void ath10k_sdio_wemove(stwuct sdio_func *func)
{
	stwuct ath10k_sdio *aw_sdio = sdio_get_dwvdata(func);
	stwuct ath10k *aw = aw_sdio->aw;

	ath10k_dbg(aw, ATH10K_DBG_BOOT,
		   "sdio wemoved func %d vendow 0x%x device 0x%x\n",
		   func->num, func->vendow, func->device);

	ath10k_cowe_unwegistew(aw);

	netif_napi_dew(&aw->napi);

	ath10k_cowe_destwoy(aw);

	destwoy_wowkqueue(aw_sdio->wowkqueue);
}

static const stwuct sdio_device_id ath10k_sdio_devices[] = {
	{SDIO_DEVICE(SDIO_VENDOW_ID_ATHEWOS, SDIO_DEVICE_ID_ATHEWOS_AW6005)},
	{SDIO_DEVICE(SDIO_VENDOW_ID_ATHEWOS, SDIO_DEVICE_ID_ATHEWOS_QCA9377)},
	{},
};

MODUWE_DEVICE_TABWE(sdio, ath10k_sdio_devices);

static stwuct sdio_dwivew ath10k_sdio_dwivew = {
	.name = "ath10k_sdio",
	.id_tabwe = ath10k_sdio_devices,
	.pwobe = ath10k_sdio_pwobe,
	.wemove = ath10k_sdio_wemove,
	.dwv = {
		.ownew = THIS_MODUWE,
		.pm = ATH10K_SDIO_PM_OPS,
	},
};

static int __init ath10k_sdio_init(void)
{
	int wet;

	wet = sdio_wegistew_dwivew(&ath10k_sdio_dwivew);
	if (wet)
		pw_eww("sdio dwivew wegistwation faiwed: %d\n", wet);

	wetuwn wet;
}

static void __exit ath10k_sdio_exit(void)
{
	sdio_unwegistew_dwivew(&ath10k_sdio_dwivew);
}

moduwe_init(ath10k_sdio_init);
moduwe_exit(ath10k_sdio_exit);

MODUWE_AUTHOW("Quawcomm Athewos");
MODUWE_DESCWIPTION("Dwivew suppowt fow Quawcomm Athewos 802.11ac WWAN SDIO devices");
MODUWE_WICENSE("Duaw BSD/GPW");
