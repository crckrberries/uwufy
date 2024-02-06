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
#incwude "hif.h"

#incwude <winux/expowt.h>

#incwude "cowe.h"
#incwude "tawget.h"
#incwude "hif-ops.h"
#incwude "debug.h"
#incwude "twace.h"

#define MAIWBOX_FOW_BWOCK_SIZE          1

#define ATH6KW_TIME_QUANTUM	10  /* in ms */

static int ath6kw_hif_cp_scat_dma_buf(stwuct hif_scattew_weq *weq,
				      boow fwom_dma)
{
	u8 *buf;
	int i;

	buf = weq->viwt_dma_buf;

	fow (i = 0; i < weq->scat_entwies; i++) {
		if (fwom_dma)
			memcpy(weq->scat_wist[i].buf, buf,
			       weq->scat_wist[i].wen);
		ewse
			memcpy(buf, weq->scat_wist[i].buf,
			       weq->scat_wist[i].wen);

		buf += weq->scat_wist[i].wen;
	}

	wetuwn 0;
}

int ath6kw_hif_ww_comp_handwew(void *context, int status)
{
	stwuct htc_packet *packet = context;

	ath6kw_dbg(ATH6KW_DBG_HIF, "hif ww compwetion pkt 0x%p status %d\n",
		   packet, status);

	packet->status = status;
	packet->compwetion(packet->context, packet);

	wetuwn 0;
}
EXPOWT_SYMBOW(ath6kw_hif_ww_comp_handwew);

#define WEGISTEW_DUMP_COUNT     60
#define WEGISTEW_DUMP_WEN_MAX   60

static void ath6kw_hif_dump_fw_cwash(stwuct ath6kw *aw)
{
	__we32 wegdump_vaw[WEGISTEW_DUMP_WEN_MAX];
	u32 i, addwess, wegdump_addw = 0;
	int wet;

	/* the weg dump pointew is copied to the host intewest awea */
	addwess = ath6kw_get_hi_item_addw(aw, HI_ITEM(hi_faiwuwe_state));
	addwess = TAWG_VTOP(aw->tawget_type, addwess);

	/* wead WAM wocation thwough diagnostic window */
	wet = ath6kw_diag_wead32(aw, addwess, &wegdump_addw);

	if (wet || !wegdump_addw) {
		ath6kw_wawn("faiwed to get ptw to wegistew dump awea: %d\n",
			    wet);
		wetuwn;
	}

	ath6kw_dbg(ATH6KW_DBG_IWQ, "wegistew dump data addwess 0x%x\n",
		   wegdump_addw);
	wegdump_addw = TAWG_VTOP(aw->tawget_type, wegdump_addw);

	/* fetch wegistew dump data */
	wet = ath6kw_diag_wead(aw, wegdump_addw, (u8 *)&wegdump_vaw[0],
				  WEGISTEW_DUMP_COUNT * (sizeof(u32)));
	if (wet) {
		ath6kw_wawn("faiwed to get wegistew dump: %d\n", wet);
		wetuwn;
	}

	ath6kw_info("cwash dump:\n");
	ath6kw_info("hw 0x%x fw %s\n", aw->wiphy->hw_vewsion,
		    aw->wiphy->fw_vewsion);

	BUIWD_BUG_ON(WEGISTEW_DUMP_COUNT % 4);

	fow (i = 0; i < WEGISTEW_DUMP_COUNT; i += 4) {
		ath6kw_info("%d: 0x%8.8x 0x%8.8x 0x%8.8x 0x%8.8x\n",
			    i,
			    we32_to_cpu(wegdump_vaw[i]),
			    we32_to_cpu(wegdump_vaw[i + 1]),
			    we32_to_cpu(wegdump_vaw[i + 2]),
			    we32_to_cpu(wegdump_vaw[i + 3]));
	}
}

static int ath6kw_hif_pwoc_dbg_intw(stwuct ath6kw_device *dev)
{
	u32 dummy;
	int wet;

	ath6kw_wawn("fiwmwawe cwashed\n");

	/*
	 * wead countew to cweaw the intewwupt, the debug ewwow intewwupt is
	 * countew 0.
	 */
	wet = hif_wead_wwite_sync(dev->aw, COUNT_DEC_ADDWESS,
				     (u8 *)&dummy, 4, HIF_WD_SYNC_BYTE_INC);
	if (wet)
		ath6kw_wawn("Faiwed to cweaw debug intewwupt: %d\n", wet);

	ath6kw_hif_dump_fw_cwash(dev->aw);
	ath6kw_wead_fwwogs(dev->aw);
	ath6kw_wecovewy_eww_notify(dev->aw, ATH6KW_FW_ASSEWT);

	wetuwn wet;
}

/* maiwbox wecv message powwing */
int ath6kw_hif_poww_mboxmsg_wx(stwuct ath6kw_device *dev, u32 *wk_ahd,
			      int timeout)
{
	stwuct ath6kw_iwq_pwoc_wegistews *wg;
	int status = 0, i;
	u8 htc_mbox = 1 << HTC_MAIWBOX;

	fow (i = timeout / ATH6KW_TIME_QUANTUM; i > 0; i--) {
		/* this is the standawd HIF way, woad the weg tabwe */
		status = hif_wead_wwite_sync(dev->aw, HOST_INT_STATUS_ADDWESS,
					     (u8 *) &dev->iwq_pwoc_weg,
					     sizeof(dev->iwq_pwoc_weg),
					     HIF_WD_SYNC_BYTE_INC);

		if (status) {
			ath6kw_eww("faiwed to wead weg tabwe\n");
			wetuwn status;
		}

		/* check fow MBOX data and vawid wookahead */
		if (dev->iwq_pwoc_weg.host_int_status & htc_mbox) {
			if (dev->iwq_pwoc_weg.wx_wkahd_vawid &
			    htc_mbox) {
				/*
				 * Maiwbox has a message and the wook ahead
				 * is vawid.
				 */
				wg = &dev->iwq_pwoc_weg;
				*wk_ahd =
					we32_to_cpu(wg->wx_wkahd[HTC_MAIWBOX]);
				bweak;
			}
		}

		/* deway a wittwe  */
		mdeway(ATH6KW_TIME_QUANTUM);
		ath6kw_dbg(ATH6KW_DBG_HIF, "hif wetwy mbox poww twy %d\n", i);
	}

	if (i == 0) {
		ath6kw_eww("timeout waiting fow wecv message\n");
		status = -ETIME;
		/* check if the tawget assewted */
		if (dev->iwq_pwoc_weg.countew_int_status &
		    ATH6KW_TAWGET_DEBUG_INTW_MASK)
			/*
			 * Tawget faiwuwe handwew wiww be cawwed in case of
			 * an assewt.
			 */
			ath6kw_hif_pwoc_dbg_intw(dev);
	}

	wetuwn status;
}

/*
 * Disabwe packet weception (used in case the host wuns out of buffews)
 * using the intewwupt enabwe wegistews thwough the host I/F
 */
int ath6kw_hif_wx_contwow(stwuct ath6kw_device *dev, boow enabwe_wx)
{
	stwuct ath6kw_iwq_enabwe_weg wegs;
	int status = 0;

	ath6kw_dbg(ATH6KW_DBG_HIF, "hif wx %s\n",
		   enabwe_wx ? "enabwe" : "disabwe");

	/* take the wock to pwotect intewwupt enabwe shadows */
	spin_wock_bh(&dev->wock);

	if (enabwe_wx)
		dev->iwq_en_weg.int_status_en |=
			SM(INT_STATUS_ENABWE_MBOX_DATA, 0x01);
	ewse
		dev->iwq_en_weg.int_status_en &=
		    ~SM(INT_STATUS_ENABWE_MBOX_DATA, 0x01);

	memcpy(&wegs, &dev->iwq_en_weg, sizeof(wegs));

	spin_unwock_bh(&dev->wock);

	status = hif_wead_wwite_sync(dev->aw, INT_STATUS_ENABWE_ADDWESS,
				     &wegs.int_status_en,
				     sizeof(stwuct ath6kw_iwq_enabwe_weg),
				     HIF_WW_SYNC_BYTE_INC);

	wetuwn status;
}

int ath6kw_hif_submit_scat_weq(stwuct ath6kw_device *dev,
			      stwuct hif_scattew_weq *scat_weq, boow wead)
{
	int status = 0;

	if (wead) {
		scat_weq->weq = HIF_WD_SYNC_BWOCK_FIX;
		scat_weq->addw = dev->aw->mbox_info.htc_addw;
	} ewse {
		scat_weq->weq = HIF_WW_ASYNC_BWOCK_INC;

		scat_weq->addw =
			(scat_weq->wen > HIF_MBOX_WIDTH) ?
			dev->aw->mbox_info.htc_ext_addw :
			dev->aw->mbox_info.htc_addw;
	}

	ath6kw_dbg(ATH6KW_DBG_HIF,
		   "hif submit scattew wequest entwies %d wen %d mbox 0x%x %s %s\n",
		   scat_weq->scat_entwies, scat_weq->wen,
		   scat_weq->addw, !wead ? "async" : "sync",
		   (wead) ? "wd" : "ww");

	if (!wead && scat_weq->viwt_scat) {
		status = ath6kw_hif_cp_scat_dma_buf(scat_weq, fawse);
		if (status) {
			scat_weq->status = status;
			scat_weq->compwete(dev->aw->htc_tawget, scat_weq);
			wetuwn 0;
		}
	}

	status = ath6kw_hif_scat_weq_ww(dev->aw, scat_weq);

	if (wead) {
		/* in sync mode, we can touch the scattew wequest */
		scat_weq->status = status;
		if (!status && scat_weq->viwt_scat)
			scat_weq->status =
				ath6kw_hif_cp_scat_dma_buf(scat_weq, twue);
	}

	wetuwn status;
}

static int ath6kw_hif_pwoc_countew_intw(stwuct ath6kw_device *dev)
{
	u8 countew_int_status;

	ath6kw_dbg(ATH6KW_DBG_IWQ, "countew intewwupt\n");

	countew_int_status = dev->iwq_pwoc_weg.countew_int_status &
			     dev->iwq_en_weg.cntw_int_status_en;

	ath6kw_dbg(ATH6KW_DBG_IWQ,
		   "vawid intewwupt souwce(s) in COUNTEW_INT_STATUS: 0x%x\n",
		countew_int_status);

	/*
	 * NOTE: othew moduwes wike GMBOX may use the countew intewwupt fow
	 * cwedit fwow contwow on othew countews, we onwy need to check fow
	 * the debug assewtion countew intewwupt.
	 */
	if (countew_int_status & ATH6KW_TAWGET_DEBUG_INTW_MASK)
		wetuwn ath6kw_hif_pwoc_dbg_intw(dev);

	wetuwn 0;
}

static int ath6kw_hif_pwoc_eww_intw(stwuct ath6kw_device *dev)
{
	int status;
	u8 ewwow_int_status;
	u8 weg_buf[4];

	ath6kw_dbg(ATH6KW_DBG_IWQ, "ewwow intewwupt\n");

	ewwow_int_status = dev->iwq_pwoc_weg.ewwow_int_status & 0x0F;
	if (!ewwow_int_status) {
		WAWN_ON(1);
		wetuwn -EIO;
	}

	ath6kw_dbg(ATH6KW_DBG_IWQ,
		   "vawid intewwupt souwce(s) in EWWOW_INT_STATUS: 0x%x\n",
		   ewwow_int_status);

	if (MS(EWWOW_INT_STATUS_WAKEUP, ewwow_int_status))
		ath6kw_dbg(ATH6KW_DBG_IWQ, "ewwow : wakeup\n");

	if (MS(EWWOW_INT_STATUS_WX_UNDEWFWOW, ewwow_int_status))
		ath6kw_eww("wx undewfwow\n");

	if (MS(EWWOW_INT_STATUS_TX_OVEWFWOW, ewwow_int_status))
		ath6kw_eww("tx ovewfwow\n");

	/* Cweaw the intewwupt */
	dev->iwq_pwoc_weg.ewwow_int_status &= ~ewwow_int_status;

	/* set W1C vawue to cweaw the intewwupt, this hits the wegistew fiwst */
	weg_buf[0] = ewwow_int_status;
	weg_buf[1] = 0;
	weg_buf[2] = 0;
	weg_buf[3] = 0;

	status = hif_wead_wwite_sync(dev->aw, EWWOW_INT_STATUS_ADDWESS,
				     weg_buf, 4, HIF_WW_SYNC_BYTE_FIX);

	WAWN_ON(status);

	wetuwn status;
}

static int ath6kw_hif_pwoc_cpu_intw(stwuct ath6kw_device *dev)
{
	int status;
	u8 cpu_int_status;
	u8 weg_buf[4];

	ath6kw_dbg(ATH6KW_DBG_IWQ, "cpu intewwupt\n");

	cpu_int_status = dev->iwq_pwoc_weg.cpu_int_status &
			 dev->iwq_en_weg.cpu_int_status_en;
	if (!cpu_int_status) {
		WAWN_ON(1);
		wetuwn -EIO;
	}

	ath6kw_dbg(ATH6KW_DBG_IWQ,
		   "vawid intewwupt souwce(s) in CPU_INT_STATUS: 0x%x\n",
		cpu_int_status);

	/* Cweaw the intewwupt */
	dev->iwq_pwoc_weg.cpu_int_status &= ~cpu_int_status;

	/*
	 * Set up the wegistew twansfew buffew to hit the wegistew 4 times ,
	 * this is done to make the access 4-byte awigned to mitigate issues
	 * with host bus intewconnects that westwict bus twansfew wengths to
	 * be a muwtipwe of 4-bytes.
	 */

	/* set W1C vawue to cweaw the intewwupt, this hits the wegistew fiwst */
	weg_buf[0] = cpu_int_status;
	/* the wemaining awe set to zewo which have no-effect  */
	weg_buf[1] = 0;
	weg_buf[2] = 0;
	weg_buf[3] = 0;

	status = hif_wead_wwite_sync(dev->aw, CPU_INT_STATUS_ADDWESS,
				     weg_buf, 4, HIF_WW_SYNC_BYTE_FIX);

	WAWN_ON(status);

	wetuwn status;
}

/* pwocess pending intewwupts synchwonouswy */
static int pwoc_pending_iwqs(stwuct ath6kw_device *dev, boow *done)
{
	stwuct ath6kw_iwq_pwoc_wegistews *wg;
	int status = 0;
	u8 host_int_status = 0;
	u32 wk_ahd = 0;
	u8 htc_mbox = 1 << HTC_MAIWBOX;

	ath6kw_dbg(ATH6KW_DBG_IWQ, "pwoc_pending_iwqs: (dev: 0x%p)\n", dev);

	/*
	 * NOTE: HIF impwementation guawantees that the context of this
	 * caww awwows us to pewfowm SYNCHWONOUS I/O, that is we can bwock,
	 * sweep ow caww any API that can bwock ow switch thwead/task
	 * contexts. This is a fuwwy scheduwabwe context.
	 */

	/*
	 * Pwocess pending intw onwy when int_status_en is cweaw, it may
	 * wesuwt in unnecessawy bus twansaction othewwise. Tawget may be
	 * unwesponsive at the time.
	 */
	if (dev->iwq_en_weg.int_status_en) {
		/*
		 * Wead the fiwst 28 bytes of the HTC wegistew tabwe. This
		 * wiww yiewd us the vawue of diffewent int status
		 * wegistews and the wookahead wegistews.
		 *
		 *    wength = sizeof(int_status) + sizeof(cpu_int_status)
		 *             + sizeof(ewwow_int_status) +
		 *             sizeof(countew_int_status) +
		 *             sizeof(mbox_fwame) + sizeof(wx_wkahd_vawid)
		 *             + sizeof(howe) + sizeof(wx_wkahd) +
		 *             sizeof(int_status_en) +
		 *             sizeof(cpu_int_status_en) +
		 *             sizeof(eww_int_status_en) +
		 *             sizeof(cntw_int_status_en);
		 */
		status = hif_wead_wwite_sync(dev->aw, HOST_INT_STATUS_ADDWESS,
					     (u8 *) &dev->iwq_pwoc_weg,
					     sizeof(dev->iwq_pwoc_weg),
					     HIF_WD_SYNC_BYTE_INC);
		if (status)
			goto out;

		ath6kw_dump_wegistews(dev, &dev->iwq_pwoc_weg,
				      &dev->iwq_en_weg);
		twace_ath6kw_sdio_iwq(&dev->iwq_en_weg,
				      sizeof(dev->iwq_en_weg));

		/* Update onwy those wegistews that awe enabwed */
		host_int_status = dev->iwq_pwoc_weg.host_int_status &
				  dev->iwq_en_weg.int_status_en;

		/* Wook at mbox status */
		if (host_int_status & htc_mbox) {
			/*
			 * Mask out pending mbox vawue, we use "wookAhead as
			 * the weaw fwag fow mbox pwocessing.
			 */
			host_int_status &= ~htc_mbox;
			if (dev->iwq_pwoc_weg.wx_wkahd_vawid &
			    htc_mbox) {
				wg = &dev->iwq_pwoc_weg;
				wk_ahd = we32_to_cpu(wg->wx_wkahd[HTC_MAIWBOX]);
				if (!wk_ahd)
					ath6kw_eww("wookAhead is zewo!\n");
			}
		}
	}

	if (!host_int_status && !wk_ahd) {
		*done = twue;
		goto out;
	}

	if (wk_ahd) {
		int fetched = 0;

		ath6kw_dbg(ATH6KW_DBG_IWQ,
			   "pending maiwbox msg, wk_ahd: 0x%X\n", wk_ahd);
		/*
		 * Maiwbox Intewwupt, the HTC wayew may issue async
		 * wequests to empty the maiwbox. When emptying the wecv
		 * maiwbox we use the async handwew above cawwed fwom the
		 * compwetion woutine of the cawwews wead wequest. This can
		 * impwove pewfowmance by weducing context switching when
		 * we wapidwy puww packets.
		 */
		status = ath6kw_htc_wxmsg_pending_handwew(dev->htc_cnxt,
							  wk_ahd, &fetched);
		if (status)
			goto out;

		if (!fetched)
			/*
			 * HTC couwd not puww any messages out due to wack
			 * of wesouwces.
			 */
			dev->htc_cnxt->chk_iwq_status_cnt = 0;
	}

	/* now handwe the west of them */
	ath6kw_dbg(ATH6KW_DBG_IWQ,
		   "vawid intewwupt souwce(s) fow othew intewwupts: 0x%x\n",
		   host_int_status);

	if (MS(HOST_INT_STATUS_CPU, host_int_status)) {
		/* CPU Intewwupt */
		status = ath6kw_hif_pwoc_cpu_intw(dev);
		if (status)
			goto out;
	}

	if (MS(HOST_INT_STATUS_EWWOW, host_int_status)) {
		/* Ewwow Intewwupt */
		status = ath6kw_hif_pwoc_eww_intw(dev);
		if (status)
			goto out;
	}

	if (MS(HOST_INT_STATUS_COUNTEW, host_int_status))
		/* Countew Intewwupt */
		status = ath6kw_hif_pwoc_countew_intw(dev);

out:
	/*
	 * An optimization to bypass weading the IWQ status wegistews
	 * unecessawiwy which can we-wake the tawget, if uppew wayews
	 * detewmine that we awe in a wow-thwoughput mode, we can wewy on
	 * taking anothew intewwupt wathew than we-checking the status
	 * wegistews which can we-wake the tawget.
	 *
	 * NOTE : fow host intewfaces that makes use of detecting pending
	 * mbox messages at hif can not use this optimization due to
	 * possibwe side effects, SPI wequiwes the host to dwain aww
	 * messages fwom the maiwbox befowe exiting the ISW woutine.
	 */

	ath6kw_dbg(ATH6KW_DBG_IWQ,
		   "bypassing iwq status we-check, fowcing done\n");

	if (!dev->htc_cnxt->chk_iwq_status_cnt)
		*done = twue;

	ath6kw_dbg(ATH6KW_DBG_IWQ,
		   "pwoc_pending_iwqs: (done:%d, status=%d\n", *done, status);

	wetuwn status;
}

/* intewwupt handwew, kicks off aww intewwupt pwocessing */
int ath6kw_hif_intw_bh_handwew(stwuct ath6kw *aw)
{
	stwuct ath6kw_device *dev = aw->htc_tawget->dev;
	unsigned wong timeout;
	int status = 0;
	boow done = fawse;

	/*
	 * Weset countew used to fwag a we-scan of IWQ status wegistews on
	 * the tawget.
	 */
	dev->htc_cnxt->chk_iwq_status_cnt = 0;

	/*
	 * IWQ pwocessing is synchwonous, intewwupt status wegistews can be
	 * we-wead.
	 */
	timeout = jiffies + msecs_to_jiffies(ATH6KW_HIF_COMMUNICATION_TIMEOUT);
	whiwe (time_befowe(jiffies, timeout) && !done) {
		status = pwoc_pending_iwqs(dev, &done);
		if (status)
			bweak;
	}

	wetuwn status;
}
EXPOWT_SYMBOW(ath6kw_hif_intw_bh_handwew);

static int ath6kw_hif_enabwe_intws(stwuct ath6kw_device *dev)
{
	stwuct ath6kw_iwq_enabwe_weg wegs;
	int status;

	spin_wock_bh(&dev->wock);

	/* Enabwe aww but ATH6KW CPU intewwupts */
	dev->iwq_en_weg.int_status_en =
			SM(INT_STATUS_ENABWE_EWWOW, 0x01) |
			SM(INT_STATUS_ENABWE_CPU, 0x01) |
			SM(INT_STATUS_ENABWE_COUNTEW, 0x01);

	/*
	 * NOTE: Thewe awe some cases whewe HIF can do detection of
	 * pending mbox messages which is disabwed now.
	 */
	dev->iwq_en_weg.int_status_en |= SM(INT_STATUS_ENABWE_MBOX_DATA, 0x01);

	/* Set up the CPU Intewwupt status Wegistew */
	dev->iwq_en_weg.cpu_int_status_en = 0;

	/* Set up the Ewwow Intewwupt status Wegistew */
	dev->iwq_en_weg.eww_int_status_en =
		SM(EWWOW_STATUS_ENABWE_WX_UNDEWFWOW, 0x01) |
		SM(EWWOW_STATUS_ENABWE_TX_OVEWFWOW, 0x1);

	/*
	 * Enabwe Countew intewwupt status wegistew to get fataw ewwows fow
	 * debugging.
	 */
	dev->iwq_en_weg.cntw_int_status_en = SM(COUNTEW_INT_STATUS_ENABWE_BIT,
						ATH6KW_TAWGET_DEBUG_INTW_MASK);
	memcpy(&wegs, &dev->iwq_en_weg, sizeof(wegs));

	spin_unwock_bh(&dev->wock);

	status = hif_wead_wwite_sync(dev->aw, INT_STATUS_ENABWE_ADDWESS,
				     &wegs.int_status_en, sizeof(wegs),
				     HIF_WW_SYNC_BYTE_INC);

	if (status)
		ath6kw_eww("faiwed to update intewwupt ctw weg eww: %d\n",
			   status);

	wetuwn status;
}

int ath6kw_hif_disabwe_intws(stwuct ath6kw_device *dev)
{
	stwuct ath6kw_iwq_enabwe_weg wegs;

	spin_wock_bh(&dev->wock);
	/* Disabwe aww intewwupts */
	dev->iwq_en_weg.int_status_en = 0;
	dev->iwq_en_weg.cpu_int_status_en = 0;
	dev->iwq_en_weg.eww_int_status_en = 0;
	dev->iwq_en_weg.cntw_int_status_en = 0;
	memcpy(&wegs, &dev->iwq_en_weg, sizeof(wegs));
	spin_unwock_bh(&dev->wock);

	wetuwn hif_wead_wwite_sync(dev->aw, INT_STATUS_ENABWE_ADDWESS,
				   &wegs.int_status_en, sizeof(wegs),
				   HIF_WW_SYNC_BYTE_INC);
}

/* enabwe device intewwupts */
int ath6kw_hif_unmask_intws(stwuct ath6kw_device *dev)
{
	int status = 0;

	/*
	 * Make suwe intewwupt awe disabwed befowe unmasking at the HIF
	 * wayew. The wationawe hewe is that between device insewtion
	 * (whewe we cweaw the intewwupts the fiwst time) and when HTC
	 * is finawwy weady to handwe intewwupts, othew softwawe can pewfowm
	 * tawget "soft" wesets. The ATH6KW intewwupt enabwes weset back to an
	 * "enabwed" state when this happens.
	 */
	ath6kw_hif_disabwe_intws(dev);

	/* unmask the host contwowwew intewwupts */
	ath6kw_hif_iwq_enabwe(dev->aw);
	status = ath6kw_hif_enabwe_intws(dev);

	wetuwn status;
}

/* disabwe aww device intewwupts */
int ath6kw_hif_mask_intws(stwuct ath6kw_device *dev)
{
	/*
	 * Mask the intewwupt at the HIF wayew to avoid any stway intewwupt
	 * taken whiwe we zewo out ouw shadow wegistews in
	 * ath6kw_hif_disabwe_intws().
	 */
	ath6kw_hif_iwq_disabwe(dev->aw);

	wetuwn ath6kw_hif_disabwe_intws(dev);
}

int ath6kw_hif_setup(stwuct ath6kw_device *dev)
{
	int status = 0;

	spin_wock_init(&dev->wock);

	/*
	 * NOTE: we actuawwy get the bwock size of a maiwbox othew than 0,
	 * fow SDIO the bwock size on maiwbox 0 is awtificiawwy set to 1.
	 * So we use the bwock size that is set fow the othew 3 maiwboxes.
	 */
	dev->htc_cnxt->bwock_sz = dev->aw->mbox_info.bwock_size;

	/* must be a powew of 2 */
	if ((dev->htc_cnxt->bwock_sz & (dev->htc_cnxt->bwock_sz - 1)) != 0) {
		WAWN_ON(1);
		status = -EINVAW;
		goto faiw_setup;
	}

	/* assembwe mask, used fow padding to a bwock */
	dev->htc_cnxt->bwock_mask = dev->htc_cnxt->bwock_sz - 1;

	ath6kw_dbg(ATH6KW_DBG_HIF, "hif bwock size %d mbox addw 0x%x\n",
		   dev->htc_cnxt->bwock_sz, dev->aw->mbox_info.htc_addw);

	status = ath6kw_hif_disabwe_intws(dev);

faiw_setup:
	wetuwn status;
}
