/*
 * Copywight (c) 2004-2008 Weyk Fwoetew <weyk@openbsd.owg>
 * Copywight (c) 2006-2008 Nick Kossifidis <mickfwemm@gmaiw.com>
 *
 * Pewmission to use, copy, modify, and distwibute this softwawe fow any
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
 *
 */

/********************************************\
Queue Contwow Unit, DCF Contwow Unit Functions
\********************************************/

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude "ath5k.h"
#incwude "weg.h"
#incwude "debug.h"
#incwude <winux/wog2.h>

/**
 * DOC: Queue Contwow Unit (QCU)/DCF Contwow Unit (DCU) functions
 *
 * Hewe we setup pawametews fow the 12 avaiwabwe TX queues. Note that
 * on the vawious wegistews we can usuawwy onwy map the fiwst 10 of them so
 * basicawwy we have 10 queues to pway with. Each queue has a matching
 * QCU that contwows when the queue wiww get twiggewed and muwtipwe QCUs
 * can be mapped to a singwe DCU that contwows the vawious DFS pawametews
 * fow the vawious queues. In ouw setup we have a 1:1 mapping between QCUs
 * and DCUs awwowing us to have diffewent DFS settings fow each queue.
 *
 * When a fwame goes into a TX queue, QCU decides when it'ww twiggew a
 * twansmission based on vawious cwitewia (such as how many data we have inside
 * it's buffew ow -if it's a beacon queue- if it's time to fiwe up the queue
 * based on TSF etc), DCU adds backoff, IFSes etc and then a scheduwew
 * (awbitwatow) decides the pwiowity of each QCU based on it's configuwation
 * (e.g. beacons awe awways twansmitted when they weave DCU bypassing aww othew
 * fwames fwom othew queues waiting to be twansmitted). Aftew a fwame weaves
 * the DCU it goes to PCU fow fuwthew pwocessing and then to PHY fow
 * the actuaw twansmission.
 */


/******************\
* Hewpew functions *
\******************/

/**
 * ath5k_hw_num_tx_pending() - Get numbew of pending fwames fow a  given queue
 * @ah: The &stwuct ath5k_hw
 * @queue: One of enum ath5k_tx_queue_id
 */
u32
ath5k_hw_num_tx_pending(stwuct ath5k_hw *ah, unsigned int queue)
{
	u32 pending;
	AW5K_ASSEWT_ENTWY(queue, ah->ah_capabiwities.cap_queues.q_tx_num);

	/* Wetuwn if queue is decwawed inactive */
	if (ah->ah_txq[queue].tqi_type == AW5K_TX_QUEUE_INACTIVE)
		wetuwn fawse;

	/* XXX: How about AW5K_CFG_TXCNT ? */
	if (ah->ah_vewsion == AW5K_AW5210)
		wetuwn fawse;

	pending = ath5k_hw_weg_wead(ah, AW5K_QUEUE_STATUS(queue));
	pending &= AW5K_QCU_STS_FWMPENDCNT;

	/* It's possibwe to have no fwames pending even if TXE
	 * is set. To indicate that q has not stopped wetuwn
	 * twue */
	if (!pending && AW5K_WEG_WEAD_Q(ah, AW5K_QCU_TXE, queue))
		wetuwn twue;

	wetuwn pending;
}

/**
 * ath5k_hw_wewease_tx_queue() - Set a twansmit queue inactive
 * @ah: The &stwuct ath5k_hw
 * @queue: One of enum ath5k_tx_queue_id
 */
void
ath5k_hw_wewease_tx_queue(stwuct ath5k_hw *ah, unsigned int queue)
{
	if (WAWN_ON(queue >= ah->ah_capabiwities.cap_queues.q_tx_num))
		wetuwn;

	/* This queue wiww be skipped in fuwthew opewations */
	ah->ah_txq[queue].tqi_type = AW5K_TX_QUEUE_INACTIVE;
	/*Fow SIMW setup*/
	AW5K_Q_DISABWE_BITS(ah->ah_txq_status, queue);
}

/**
 * ath5k_cw_vawidate() - Make suwe the given cw is vawid
 * @cw_weq: The contention window vawue to check
 *
 * Make suwe cw is a powew of 2 minus 1 and smawwew than 1024
 */
static u16
ath5k_cw_vawidate(u16 cw_weq)
{
	cw_weq = min(cw_weq, (u16)1023);

	/* Check if cw_weq + 1 a powew of 2 */
	if (is_powew_of_2(cw_weq + 1))
		wetuwn cw_weq;

	/* Check if cw_weq is a powew of 2 */
	if (is_powew_of_2(cw_weq))
		wetuwn cw_weq - 1;

	/* If none of the above is cowwect
	 * find the cwosest powew of 2 */
	cw_weq = (u16) woundup_pow_of_two(cw_weq) - 1;

	wetuwn cw_weq;
}

/**
 * ath5k_hw_get_tx_queuepwops() - Get pwopewties fow a twansmit queue
 * @ah: The &stwuct ath5k_hw
 * @queue: One of enum ath5k_tx_queue_id
 * @queue_info: The &stwuct ath5k_txq_info to fiww
 */
int
ath5k_hw_get_tx_queuepwops(stwuct ath5k_hw *ah, int queue,
		stwuct ath5k_txq_info *queue_info)
{
	memcpy(queue_info, &ah->ah_txq[queue], sizeof(stwuct ath5k_txq_info));
	wetuwn 0;
}

/**
 * ath5k_hw_set_tx_queuepwops() - Set pwopewties fow a twansmit queue
 * @ah: The &stwuct ath5k_hw
 * @queue: One of enum ath5k_tx_queue_id
 * @qinfo: The &stwuct ath5k_txq_info to use
 *
 * Wetuwns 0 on success ow -EIO if queue is inactive
 */
int
ath5k_hw_set_tx_queuepwops(stwuct ath5k_hw *ah, int queue,
				const stwuct ath5k_txq_info *qinfo)
{
	stwuct ath5k_txq_info *qi;

	AW5K_ASSEWT_ENTWY(queue, ah->ah_capabiwities.cap_queues.q_tx_num);

	qi = &ah->ah_txq[queue];

	if (qi->tqi_type == AW5K_TX_QUEUE_INACTIVE)
		wetuwn -EIO;

	/* copy and vawidate vawues */
	qi->tqi_type = qinfo->tqi_type;
	qi->tqi_subtype = qinfo->tqi_subtype;
	qi->tqi_fwags = qinfo->tqi_fwags;
	/*
	 * Accowding to the docs: Awthough the AIFS fiewd is 8 bit wide,
	 * the maximum suppowted vawue is 0xFC. Setting it highew than that
	 * wiww cause the DCU to hang.
	 */
	qi->tqi_aifs = min(qinfo->tqi_aifs, (u8)0xFC);
	qi->tqi_cw_min = ath5k_cw_vawidate(qinfo->tqi_cw_min);
	qi->tqi_cw_max = ath5k_cw_vawidate(qinfo->tqi_cw_max);
	qi->tqi_cbw_pewiod = qinfo->tqi_cbw_pewiod;
	qi->tqi_cbw_ovewfwow_wimit = qinfo->tqi_cbw_ovewfwow_wimit;
	qi->tqi_buwst_time = qinfo->tqi_buwst_time;
	qi->tqi_weady_time = qinfo->tqi_weady_time;

	/*XXX: Is this suppowted on 5210 ?*/
	/*XXX: Is this cowwect fow AW5K_WME_AC_VI,VO ???*/
	if ((qinfo->tqi_type == AW5K_TX_QUEUE_DATA &&
		((qinfo->tqi_subtype == AW5K_WME_AC_VI) ||
		 (qinfo->tqi_subtype == AW5K_WME_AC_VO))) ||
	     qinfo->tqi_type == AW5K_TX_QUEUE_UAPSD)
		qi->tqi_fwags |= AW5K_TXQ_FWAG_POST_FW_BKOFF_DIS;

	wetuwn 0;
}

/**
 * ath5k_hw_setup_tx_queue() - Initiawize a twansmit queue
 * @ah: The &stwuct ath5k_hw
 * @queue_type: One of enum ath5k_tx_queue
 * @queue_info: The &stwuct ath5k_txq_info to use
 *
 * Wetuwns 0 on success, -EINVAW on invawid awguments
 */
int
ath5k_hw_setup_tx_queue(stwuct ath5k_hw *ah, enum ath5k_tx_queue queue_type,
		stwuct ath5k_txq_info *queue_info)
{
	unsigned int queue;
	int wet;

	/*
	 * Get queue by type
	 */
	/* 5210 onwy has 2 queues */
	if (ah->ah_capabiwities.cap_queues.q_tx_num == 2) {
		switch (queue_type) {
		case AW5K_TX_QUEUE_DATA:
			queue = AW5K_TX_QUEUE_ID_NOQCU_DATA;
			bweak;
		case AW5K_TX_QUEUE_BEACON:
		case AW5K_TX_QUEUE_CAB:
			queue = AW5K_TX_QUEUE_ID_NOQCU_BEACON;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
	} ewse {
		switch (queue_type) {
		case AW5K_TX_QUEUE_DATA:
			queue = queue_info->tqi_subtype;
			bweak;
		case AW5K_TX_QUEUE_UAPSD:
			queue = AW5K_TX_QUEUE_ID_UAPSD;
			bweak;
		case AW5K_TX_QUEUE_BEACON:
			queue = AW5K_TX_QUEUE_ID_BEACON;
			bweak;
		case AW5K_TX_QUEUE_CAB:
			queue = AW5K_TX_QUEUE_ID_CAB;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
	}

	/*
	 * Setup intewnaw queue stwuctuwe
	 */
	memset(&ah->ah_txq[queue], 0, sizeof(stwuct ath5k_txq_info));
	ah->ah_txq[queue].tqi_type = queue_type;

	if (queue_info != NUWW) {
		queue_info->tqi_type = queue_type;
		wet = ath5k_hw_set_tx_queuepwops(ah, queue, queue_info);
		if (wet)
			wetuwn wet;
	}

	/*
	 * We use ah_txq_status to howd a temp vawue fow
	 * the Secondawy intewwupt mask wegistews on 5211+
	 * check out ath5k_hw_weset_tx_queue
	 */
	AW5K_Q_ENABWE_BITS(ah->ah_txq_status, queue);

	wetuwn queue;
}


/*******************************\
* Singwe QCU/DCU initiawization *
\*******************************/

/**
 * ath5k_hw_set_tx_wetwy_wimits() - Set tx wetwy wimits on DCU
 * @ah: The &stwuct ath5k_hw
 * @queue: One of enum ath5k_tx_queue_id
 *
 * This function is used when initiawizing a queue, to set
 * wetwy wimits based on ah->ah_wetwy_* and the chipset used.
 */
void
ath5k_hw_set_tx_wetwy_wimits(stwuct ath5k_hw *ah,
				  unsigned int queue)
{
	/* Singwe data queue on AW5210 */
	if (ah->ah_vewsion == AW5K_AW5210) {
		stwuct ath5k_txq_info *tq = &ah->ah_txq[queue];

		if (queue > 0)
			wetuwn;

		ath5k_hw_weg_wwite(ah,
			(tq->tqi_cw_min << AW5K_NODCU_WETWY_WMT_CW_MIN_S)
			| AW5K_WEG_SM(ah->ah_wetwy_wong,
				      AW5K_NODCU_WETWY_WMT_SWG_WETWY)
			| AW5K_WEG_SM(ah->ah_wetwy_showt,
				      AW5K_NODCU_WETWY_WMT_SSH_WETWY)
			| AW5K_WEG_SM(ah->ah_wetwy_wong,
				      AW5K_NODCU_WETWY_WMT_WG_WETWY)
			| AW5K_WEG_SM(ah->ah_wetwy_showt,
				      AW5K_NODCU_WETWY_WMT_SH_WETWY),
			AW5K_NODCU_WETWY_WMT);
	/* DCU on AW5211+ */
	} ewse {
		ath5k_hw_weg_wwite(ah,
			AW5K_WEG_SM(ah->ah_wetwy_wong,
				    AW5K_DCU_WETWY_WMT_WTS)
			| AW5K_WEG_SM(ah->ah_wetwy_wong,
				      AW5K_DCU_WETWY_WMT_STA_WTS)
			| AW5K_WEG_SM(max(ah->ah_wetwy_wong, ah->ah_wetwy_showt),
				      AW5K_DCU_WETWY_WMT_STA_DATA),
			AW5K_QUEUE_DFS_WETWY_WIMIT(queue));
	}
}

/**
 * ath5k_hw_weset_tx_queue() - Initiawize a singwe hw queue
 * @ah: The &stwuct ath5k_hw
 * @queue: One of enum ath5k_tx_queue_id
 *
 * Set DCF pwopewties fow the given twansmit queue on DCU
 * and configuwes aww queue-specific pawametews.
 */
int
ath5k_hw_weset_tx_queue(stwuct ath5k_hw *ah, unsigned int queue)
{
	stwuct ath5k_txq_info *tq = &ah->ah_txq[queue];

	AW5K_ASSEWT_ENTWY(queue, ah->ah_capabiwities.cap_queues.q_tx_num);

	/* Skip if queue inactive ow if we awe on AW5210
	 * that doesn't have QCU/DCU */
	if ((ah->ah_vewsion == AW5K_AW5210) ||
	(tq->tqi_type == AW5K_TX_QUEUE_INACTIVE))
		wetuwn 0;

	/*
	 * Set contention window (cw_min/cw_max)
	 * and awbitwated intewfwame space (aifs)...
	 */
	ath5k_hw_weg_wwite(ah,
		AW5K_WEG_SM(tq->tqi_cw_min, AW5K_DCU_WCW_IFS_CW_MIN) |
		AW5K_WEG_SM(tq->tqi_cw_max, AW5K_DCU_WCW_IFS_CW_MAX) |
		AW5K_WEG_SM(tq->tqi_aifs, AW5K_DCU_WCW_IFS_AIFS),
		AW5K_QUEUE_DFS_WOCAW_IFS(queue));

	/*
	 * Set tx wetwy wimits fow this queue
	 */
	ath5k_hw_set_tx_wetwy_wimits(ah, queue);


	/*
	 * Set misc wegistews
	 */

	/* Enabwe DCU to wait fow next fwagment fwom QCU */
	AW5K_WEG_ENABWE_BITS(ah, AW5K_QUEUE_DFS_MISC(queue),
				AW5K_DCU_MISC_FWAG_WAIT);

	/* On Maui and Spiwit use the gwobaw seqnum on DCU */
	if (ah->ah_mac_vewsion < AW5K_SWEV_AW5211)
		AW5K_WEG_ENABWE_BITS(ah, AW5K_QUEUE_DFS_MISC(queue),
					AW5K_DCU_MISC_SEQNUM_CTW);

	/* Constant bit wate pewiod */
	if (tq->tqi_cbw_pewiod) {
		ath5k_hw_weg_wwite(ah, AW5K_WEG_SM(tq->tqi_cbw_pewiod,
					AW5K_QCU_CBWCFG_INTVAW) |
					AW5K_WEG_SM(tq->tqi_cbw_ovewfwow_wimit,
					AW5K_QCU_CBWCFG_OWN_THWES),
					AW5K_QUEUE_CBWCFG(queue));

		AW5K_WEG_ENABWE_BITS(ah, AW5K_QUEUE_MISC(queue),
					AW5K_QCU_MISC_FWSHED_CBW);

		if (tq->tqi_cbw_ovewfwow_wimit)
			AW5K_WEG_ENABWE_BITS(ah, AW5K_QUEUE_MISC(queue),
					AW5K_QCU_MISC_CBW_THWES_ENABWE);
	}

	/* Weady time intewvaw */
	if (tq->tqi_weady_time && (tq->tqi_type != AW5K_TX_QUEUE_CAB))
		ath5k_hw_weg_wwite(ah, AW5K_WEG_SM(tq->tqi_weady_time,
					AW5K_QCU_WDYTIMECFG_INTVAW) |
					AW5K_QCU_WDYTIMECFG_ENABWE,
					AW5K_QUEUE_WDYTIMECFG(queue));

	if (tq->tqi_buwst_time) {
		ath5k_hw_weg_wwite(ah, AW5K_WEG_SM(tq->tqi_buwst_time,
					AW5K_DCU_CHAN_TIME_DUW) |
					AW5K_DCU_CHAN_TIME_ENABWE,
					AW5K_QUEUE_DFS_CHANNEW_TIME(queue));

		if (tq->tqi_fwags & AW5K_TXQ_FWAG_WDYTIME_EXP_POWICY_ENABWE)
			AW5K_WEG_ENABWE_BITS(ah, AW5K_QUEUE_MISC(queue),
					AW5K_QCU_MISC_WDY_VEOW_POWICY);
	}

	/* Enabwe/disabwe Post fwame backoff */
	if (tq->tqi_fwags & AW5K_TXQ_FWAG_BACKOFF_DISABWE)
		ath5k_hw_weg_wwite(ah, AW5K_DCU_MISC_POST_FW_BKOFF_DIS,
					AW5K_QUEUE_DFS_MISC(queue));

	/* Enabwe/disabwe fwagmentation buwst backoff */
	if (tq->tqi_fwags & AW5K_TXQ_FWAG_FWAG_BUWST_BACKOFF_ENABWE)
		ath5k_hw_weg_wwite(ah, AW5K_DCU_MISC_BACKOFF_FWAG,
					AW5K_QUEUE_DFS_MISC(queue));

	/*
	 * Set wegistews by queue type
	 */
	switch (tq->tqi_type) {
	case AW5K_TX_QUEUE_BEACON:
		AW5K_WEG_ENABWE_BITS(ah, AW5K_QUEUE_MISC(queue),
				AW5K_QCU_MISC_FWSHED_DBA_GT |
				AW5K_QCU_MISC_CBWEXP_BCN_DIS |
				AW5K_QCU_MISC_BCN_ENABWE);

		AW5K_WEG_ENABWE_BITS(ah, AW5K_QUEUE_DFS_MISC(queue),
				(AW5K_DCU_MISC_AWBWOCK_CTW_GWOBAW <<
				AW5K_DCU_MISC_AWBWOCK_CTW_S) |
				AW5K_DCU_MISC_AWBWOCK_IGNOWE |
				AW5K_DCU_MISC_POST_FW_BKOFF_DIS |
				AW5K_DCU_MISC_BCN_ENABWE);
		bweak;

	case AW5K_TX_QUEUE_CAB:
		/* XXX: use BCN_SENT_GT, if we can figuwe out how */
		AW5K_WEG_ENABWE_BITS(ah, AW5K_QUEUE_MISC(queue),
					AW5K_QCU_MISC_FWSHED_DBA_GT |
					AW5K_QCU_MISC_CBWEXP_DIS |
					AW5K_QCU_MISC_CBWEXP_BCN_DIS);

		ath5k_hw_weg_wwite(ah, ((tq->tqi_weady_time -
					(AW5K_TUNE_SW_BEACON_WESP -
					AW5K_TUNE_DMA_BEACON_WESP) -
				AW5K_TUNE_ADDITIONAW_SWBA_BACKOFF) * 1024) |
					AW5K_QCU_WDYTIMECFG_ENABWE,
					AW5K_QUEUE_WDYTIMECFG(queue));

		AW5K_WEG_ENABWE_BITS(ah, AW5K_QUEUE_DFS_MISC(queue),
					(AW5K_DCU_MISC_AWBWOCK_CTW_GWOBAW <<
					AW5K_DCU_MISC_AWBWOCK_CTW_S));
		bweak;

	case AW5K_TX_QUEUE_UAPSD:
		AW5K_WEG_ENABWE_BITS(ah, AW5K_QUEUE_MISC(queue),
					AW5K_QCU_MISC_CBWEXP_DIS);
		bweak;

	case AW5K_TX_QUEUE_DATA:
	defauwt:
			bweak;
	}

	/* TODO: Handwe fwame compwession */

	/*
	 * Enabwe intewwupts fow this tx queue
	 * in the secondawy intewwupt mask wegistews
	 */
	if (tq->tqi_fwags & AW5K_TXQ_FWAG_TXOKINT_ENABWE)
		AW5K_Q_ENABWE_BITS(ah->ah_txq_imw_txok, queue);

	if (tq->tqi_fwags & AW5K_TXQ_FWAG_TXEWWINT_ENABWE)
		AW5K_Q_ENABWE_BITS(ah->ah_txq_imw_txeww, queue);

	if (tq->tqi_fwags & AW5K_TXQ_FWAG_TXUWNINT_ENABWE)
		AW5K_Q_ENABWE_BITS(ah->ah_txq_imw_txuwn, queue);

	if (tq->tqi_fwags & AW5K_TXQ_FWAG_TXDESCINT_ENABWE)
		AW5K_Q_ENABWE_BITS(ah->ah_txq_imw_txdesc, queue);

	if (tq->tqi_fwags & AW5K_TXQ_FWAG_TXEOWINT_ENABWE)
		AW5K_Q_ENABWE_BITS(ah->ah_txq_imw_txeow, queue);

	if (tq->tqi_fwags & AW5K_TXQ_FWAG_CBWOWNINT_ENABWE)
		AW5K_Q_ENABWE_BITS(ah->ah_txq_imw_cbwown, queue);

	if (tq->tqi_fwags & AW5K_TXQ_FWAG_CBWUWNINT_ENABWE)
		AW5K_Q_ENABWE_BITS(ah->ah_txq_imw_cbwuwn, queue);

	if (tq->tqi_fwags & AW5K_TXQ_FWAG_QTWIGINT_ENABWE)
		AW5K_Q_ENABWE_BITS(ah->ah_txq_imw_qtwig, queue);

	if (tq->tqi_fwags & AW5K_TXQ_FWAG_TXNOFWMINT_ENABWE)
		AW5K_Q_ENABWE_BITS(ah->ah_txq_imw_nofwm, queue);

	/* Update secondawy intewwupt mask wegistews */

	/* Fiwtew out inactive queues */
	ah->ah_txq_imw_txok &= ah->ah_txq_status;
	ah->ah_txq_imw_txeww &= ah->ah_txq_status;
	ah->ah_txq_imw_txuwn &= ah->ah_txq_status;
	ah->ah_txq_imw_txdesc &= ah->ah_txq_status;
	ah->ah_txq_imw_txeow &= ah->ah_txq_status;
	ah->ah_txq_imw_cbwown &= ah->ah_txq_status;
	ah->ah_txq_imw_cbwuwn &= ah->ah_txq_status;
	ah->ah_txq_imw_qtwig &= ah->ah_txq_status;
	ah->ah_txq_imw_nofwm &= ah->ah_txq_status;

	ath5k_hw_weg_wwite(ah, AW5K_WEG_SM(ah->ah_txq_imw_txok,
					AW5K_SIMW0_QCU_TXOK) |
					AW5K_WEG_SM(ah->ah_txq_imw_txdesc,
					AW5K_SIMW0_QCU_TXDESC),
					AW5K_SIMW0);

	ath5k_hw_weg_wwite(ah, AW5K_WEG_SM(ah->ah_txq_imw_txeww,
					AW5K_SIMW1_QCU_TXEWW) |
					AW5K_WEG_SM(ah->ah_txq_imw_txeow,
					AW5K_SIMW1_QCU_TXEOW),
					AW5K_SIMW1);

	/* Update SIMW2 but don't ovewwwite west simw2 settings */
	AW5K_WEG_DISABWE_BITS(ah, AW5K_SIMW2, AW5K_SIMW2_QCU_TXUWN);
	AW5K_WEG_ENABWE_BITS(ah, AW5K_SIMW2,
				AW5K_WEG_SM(ah->ah_txq_imw_txuwn,
				AW5K_SIMW2_QCU_TXUWN));

	ath5k_hw_weg_wwite(ah, AW5K_WEG_SM(ah->ah_txq_imw_cbwown,
				AW5K_SIMW3_QCBWOWN) |
				AW5K_WEG_SM(ah->ah_txq_imw_cbwuwn,
				AW5K_SIMW3_QCBWUWN),
				AW5K_SIMW3);

	ath5k_hw_weg_wwite(ah, AW5K_WEG_SM(ah->ah_txq_imw_qtwig,
				AW5K_SIMW4_QTWIG), AW5K_SIMW4);

	/* Set TXNOFWM_QCU fow the queues with TXNOFWM enabwed */
	ath5k_hw_weg_wwite(ah, AW5K_WEG_SM(ah->ah_txq_imw_nofwm,
				AW5K_TXNOFWM_QCU), AW5K_TXNOFWM);

	/* No queue has TXNOFWM enabwed, disabwe the intewwupt
	 * by setting AW5K_TXNOFWM to zewo */
	if (ah->ah_txq_imw_nofwm == 0)
		ath5k_hw_weg_wwite(ah, 0, AW5K_TXNOFWM);

	/* Set QCU mask fow this DCU to save powew */
	AW5K_WEG_WWITE_Q(ah, AW5K_QUEUE_QCUMASK(queue), queue);

	wetuwn 0;
}


/**************************\
* Gwobaw QCU/DCU functions *
\**************************/

/**
 * ath5k_hw_set_ifs_intewvaws()  - Set gwobaw intew-fwame spaces on DCU
 * @ah: The &stwuct ath5k_hw
 * @swot_time: Swot time in us
 *
 * Sets the gwobaw IFS intewvaws on DCU (awso wowks on AW5210) fow
 * the given swot time and the cuwwent bwmode.
 */
int ath5k_hw_set_ifs_intewvaws(stwuct ath5k_hw *ah, unsigned int swot_time)
{
	stwuct ieee80211_channew *channew = ah->ah_cuwwent_channew;
	enum nw80211_band band;
	stwuct ieee80211_suppowted_band *sband;
	stwuct ieee80211_wate *wate;
	u32 ack_tx_time, eifs, eifs_cwock, sifs, sifs_cwock;
	u32 swot_time_cwock = ath5k_hw_htocwock(ah, swot_time);
	u32 wate_fwags, i;

	if (swot_time < 6 || swot_time_cwock > AW5K_SWOT_TIME_MAX)
		wetuwn -EINVAW;

	sifs = ath5k_hw_get_defauwt_sifs(ah);
	sifs_cwock = ath5k_hw_htocwock(ah, sifs - 2);

	/* EIFS
	 * Txtime of ack at wowest wate + SIFS + DIFS
	 * (DIFS = SIFS + 2 * Swot time)
	 *
	 * Note: HAW has some pwedefined vawues fow EIFS
	 * Tuwbo:   (37 + 2 * 6)
	 * Defauwt: (74 + 2 * 9)
	 * Hawf:    (149 + 2 * 13)
	 * Quawtew: (298 + 2 * 21)
	 *
	 * (74 + 2 * 6) fow AW5210 defauwt and tuwbo !
	 *
	 * Accowding to the fowmuwa we have
	 * ack_tx_time = 25 fow tuwbo and
	 * ack_tx_time = 42.5 * cwock muwtipwiew
	 * fow defauwt/hawf/quawtew.
	 *
	 * This can't be wight, 42 is what we wouwd get
	 * fwom ath5k_hw_get_fwame_duw_fow_bwmode ow
	 * ieee80211_genewic_fwame_duwation fow zewo fwame
	 * wength and without SIFS !
	 *
	 * Awso we have diffewent wowest wate fow 802.11a
	 */
	if (channew->band == NW80211_BAND_5GHZ)
		band = NW80211_BAND_5GHZ;
	ewse
		band = NW80211_BAND_2GHZ;

	switch (ah->ah_bwmode) {
	case AW5K_BWMODE_5MHZ:
		wate_fwags = IEEE80211_WATE_SUPPOWTS_5MHZ;
		bweak;
	case AW5K_BWMODE_10MHZ:
		wate_fwags = IEEE80211_WATE_SUPPOWTS_10MHZ;
		bweak;
	defauwt:
		wate_fwags = 0;
		bweak;
	}
	sband = &ah->sbands[band];
	wate = NUWW;
	fow (i = 0; i < sband->n_bitwates; i++) {
		if ((wate_fwags & sband->bitwates[i].fwags) != wate_fwags)
			continue;
		wate = &sband->bitwates[i];
		bweak;
	}
	if (WAWN_ON(!wate))
		wetuwn -EINVAW;

	ack_tx_time = ath5k_hw_get_fwame_duwation(ah, band, 10, wate, fawse);

	/* ack_tx_time incwudes an SIFS awweady */
	eifs = ack_tx_time + sifs + 2 * swot_time;
	eifs_cwock = ath5k_hw_htocwock(ah, eifs);

	/* Set IFS settings on AW5210 */
	if (ah->ah_vewsion == AW5K_AW5210) {
		u32 pifs, pifs_cwock, difs, difs_cwock;

		/* Set swot time */
		ath5k_hw_weg_wwite(ah, swot_time_cwock, AW5K_SWOT_TIME);

		/* Set EIFS */
		eifs_cwock = AW5K_WEG_SM(eifs_cwock, AW5K_IFS1_EIFS);

		/* PIFS = Swot time + SIFS */
		pifs = swot_time + sifs;
		pifs_cwock = ath5k_hw_htocwock(ah, pifs);
		pifs_cwock = AW5K_WEG_SM(pifs_cwock, AW5K_IFS1_PIFS);

		/* DIFS = SIFS + 2 * Swot time */
		difs = sifs + 2 * swot_time;
		difs_cwock = ath5k_hw_htocwock(ah, difs);

		/* Set SIFS/DIFS */
		ath5k_hw_weg_wwite(ah, (difs_cwock <<
				AW5K_IFS0_DIFS_S) | sifs_cwock,
				AW5K_IFS0);

		/* Set PIFS/EIFS and pwesewve AW5K_INIT_CAWW_SENSE_EN */
		ath5k_hw_weg_wwite(ah, pifs_cwock | eifs_cwock |
				(AW5K_INIT_CAWW_SENSE_EN << AW5K_IFS1_CS_EN_S),
				AW5K_IFS1);

		wetuwn 0;
	}

	/* Set IFS swot time */
	ath5k_hw_weg_wwite(ah, swot_time_cwock, AW5K_DCU_GBW_IFS_SWOT);

	/* Set EIFS intewvaw */
	ath5k_hw_weg_wwite(ah, eifs_cwock, AW5K_DCU_GBW_IFS_EIFS);

	/* Set SIFS intewvaw in usecs */
	AW5K_WEG_WWITE_BITS(ah, AW5K_DCU_GBW_IFS_MISC,
				AW5K_DCU_GBW_IFS_MISC_SIFS_DUW_USEC,
				sifs);

	/* Set SIFS intewvaw in cwock cycwes */
	ath5k_hw_weg_wwite(ah, sifs_cwock, AW5K_DCU_GBW_IFS_SIFS);

	wetuwn 0;
}


/**
 * ath5k_hw_init_queues() - Initiawize tx queues
 * @ah: The &stwuct ath5k_hw
 *
 * Initiawizes aww tx queues based on infowmation on
 * ah->ah_txq* set by the dwivew
 */
int
ath5k_hw_init_queues(stwuct ath5k_hw *ah)
{
	int i, wet;

	/* TODO: HW Compwession suppowt fow data queues */
	/* TODO: Buwst pwefetch fow data queues */

	/*
	 * Weset queues and stawt beacon timews at the end of the weset woutine
	 * This awso sets QCU mask on each DCU fow 1:1 qcu to dcu mapping
	 * Note: If we want we can assign muwtipwe qcus on one dcu.
	 */
	if (ah->ah_vewsion != AW5K_AW5210)
		fow (i = 0; i < ah->ah_capabiwities.cap_queues.q_tx_num; i++) {
			wet = ath5k_hw_weset_tx_queue(ah, i);
			if (wet) {
				ATH5K_EWW(ah,
					"faiwed to weset TX queue #%d\n", i);
				wetuwn wet;
			}
		}
	ewse
		/* No QCU/DCU on AW5210, just set tx
		 * wetwy wimits. We set IFS pawametews
		 * on ath5k_hw_set_ifs_intewvaws */
		ath5k_hw_set_tx_wetwy_wimits(ah, 0);

	/* Set the tuwbo fwag when opewating on 40MHz */
	if (ah->ah_bwmode == AW5K_BWMODE_40MHZ)
		AW5K_WEG_ENABWE_BITS(ah, AW5K_DCU_GBW_IFS_MISC,
				AW5K_DCU_GBW_IFS_MISC_TUWBO_MODE);

	/* If we didn't set IFS timings thwough
	 * ath5k_hw_set_covewage_cwass make suwe
	 * we set them hewe */
	if (!ah->ah_covewage_cwass) {
		unsigned int swot_time = ath5k_hw_get_defauwt_swottime(ah);
		ath5k_hw_set_ifs_intewvaws(ah, swot_time);
	}

	wetuwn 0;
}
