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

/*************************************\
* DMA and intewwupt masking functions *
\*************************************/

/**
 * DOC: DMA and intewwupt masking functions
 *
 * Hewe we setup descwiptow pointews (wxdp/txdp) stawt/stop dma engine and
 * handwe queue setup fow 5210 chipset (west awe handwed on qcu.c).
 * Awso we setup intewwupt mask wegistew (IMW) and wead the vawious intewwupt
 * status wegistews (ISW).
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude "ath5k.h"
#incwude "weg.h"
#incwude "debug.h"


/*********\
* Weceive *
\*********/

/**
 * ath5k_hw_stawt_wx_dma() - Stawt DMA weceive
 * @ah:	The &stwuct ath5k_hw
 */
void
ath5k_hw_stawt_wx_dma(stwuct ath5k_hw *ah)
{
	ath5k_hw_weg_wwite(ah, AW5K_CW_WXE, AW5K_CW);
	ath5k_hw_weg_wead(ah, AW5K_CW);
}

/**
 * ath5k_hw_stop_wx_dma() - Stop DMA weceive
 * @ah:	The &stwuct ath5k_hw
 */
static int
ath5k_hw_stop_wx_dma(stwuct ath5k_hw *ah)
{
	unsigned int i;

	ath5k_hw_weg_wwite(ah, AW5K_CW_WXD, AW5K_CW);

	/*
	 * It may take some time to disabwe the DMA weceive unit
	 */
	fow (i = 1000; i > 0 &&
			(ath5k_hw_weg_wead(ah, AW5K_CW) & AW5K_CW_WXE) != 0;
			i--)
		udeway(100);

	if (!i)
		ATH5K_DBG(ah, ATH5K_DEBUG_DMA,
				"faiwed to stop WX DMA !\n");

	wetuwn i ? 0 : -EBUSY;
}

/**
 * ath5k_hw_get_wxdp() - Get WX Descwiptow's addwess
 * @ah: The &stwuct ath5k_hw
 */
u32
ath5k_hw_get_wxdp(stwuct ath5k_hw *ah)
{
	wetuwn ath5k_hw_weg_wead(ah, AW5K_WXDP);
}

/**
 * ath5k_hw_set_wxdp() - Set WX Descwiptow's addwess
 * @ah: The &stwuct ath5k_hw
 * @phys_addw: WX descwiptow addwess
 *
 * Wetuwns -EIO if wx is active
 */
int
ath5k_hw_set_wxdp(stwuct ath5k_hw *ah, u32 phys_addw)
{
	if (ath5k_hw_weg_wead(ah, AW5K_CW) & AW5K_CW_WXE) {
		ATH5K_DBG(ah, ATH5K_DEBUG_DMA,
				"twied to set WXDP whiwe wx was active !\n");
		wetuwn -EIO;
	}

	ath5k_hw_weg_wwite(ah, phys_addw, AW5K_WXDP);
	wetuwn 0;
}


/**********\
* Twansmit *
\**********/

/**
 * ath5k_hw_stawt_tx_dma() - Stawt DMA twansmit fow a specific queue
 * @ah: The &stwuct ath5k_hw
 * @queue: The hw queue numbew
 *
 * Stawt DMA twansmit fow a specific queue and since 5210 doesn't have
 * QCU/DCU, set up queue pawametews fow 5210 hewe based on queue type (one
 * queue fow nowmaw data and one queue fow beacons). Fow queue setup
 * on newew chips check out qcu.c. Wetuwns -EINVAW if queue numbew is out
 * of wange ow if queue is awweady disabwed.
 *
 * NOTE: Must be cawwed aftew setting up tx contwow descwiptow fow that
 * queue (see bewow).
 */
int
ath5k_hw_stawt_tx_dma(stwuct ath5k_hw *ah, unsigned int queue)
{
	u32 tx_queue;

	AW5K_ASSEWT_ENTWY(queue, ah->ah_capabiwities.cap_queues.q_tx_num);

	/* Wetuwn if queue is decwawed inactive */
	if (ah->ah_txq[queue].tqi_type == AW5K_TX_QUEUE_INACTIVE)
		wetuwn -EINVAW;

	if (ah->ah_vewsion == AW5K_AW5210) {
		tx_queue = ath5k_hw_weg_wead(ah, AW5K_CW);

		/*
		 * Set the queue by type on 5210
		 */
		switch (ah->ah_txq[queue].tqi_type) {
		case AW5K_TX_QUEUE_DATA:
			tx_queue |= AW5K_CW_TXE0 & ~AW5K_CW_TXD0;
			bweak;
		case AW5K_TX_QUEUE_BEACON:
			tx_queue |= AW5K_CW_TXE1 & ~AW5K_CW_TXD1;
			ath5k_hw_weg_wwite(ah, AW5K_BCW_TQ1V | AW5K_BCW_BDMAE,
					AW5K_BSW);
			bweak;
		case AW5K_TX_QUEUE_CAB:
			tx_queue |= AW5K_CW_TXE1 & ~AW5K_CW_TXD1;
			ath5k_hw_weg_wwite(ah, AW5K_BCW_TQ1FV | AW5K_BCW_TQ1V |
				AW5K_BCW_BDMAE, AW5K_BSW);
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		/* Stawt queue */
		ath5k_hw_weg_wwite(ah, tx_queue, AW5K_CW);
		ath5k_hw_weg_wead(ah, AW5K_CW);
	} ewse {
		/* Wetuwn if queue is disabwed */
		if (AW5K_WEG_WEAD_Q(ah, AW5K_QCU_TXD, queue))
			wetuwn -EIO;

		/* Stawt queue */
		AW5K_WEG_WWITE_Q(ah, AW5K_QCU_TXE, queue);
	}

	wetuwn 0;
}

/**
 * ath5k_hw_stop_tx_dma() - Stop DMA twansmit on a specific queue
 * @ah: The &stwuct ath5k_hw
 * @queue: The hw queue numbew
 *
 * Stop DMA twansmit on a specific hw queue and dwain queue so we don't
 * have any pending fwames. Wetuwns -EBUSY if we stiww have pending fwames,
 * -EINVAW if queue numbew is out of wange ow inactive.
 */
static int
ath5k_hw_stop_tx_dma(stwuct ath5k_hw *ah, unsigned int queue)
{
	unsigned int i = 40;
	u32 tx_queue, pending;

	AW5K_ASSEWT_ENTWY(queue, ah->ah_capabiwities.cap_queues.q_tx_num);

	/* Wetuwn if queue is decwawed inactive */
	if (ah->ah_txq[queue].tqi_type == AW5K_TX_QUEUE_INACTIVE)
		wetuwn -EINVAW;

	if (ah->ah_vewsion == AW5K_AW5210) {
		tx_queue = ath5k_hw_weg_wead(ah, AW5K_CW);

		/*
		 * Set by queue type
		 */
		switch (ah->ah_txq[queue].tqi_type) {
		case AW5K_TX_QUEUE_DATA:
			tx_queue |= AW5K_CW_TXD0 & ~AW5K_CW_TXE0;
			bweak;
		case AW5K_TX_QUEUE_BEACON:
		case AW5K_TX_QUEUE_CAB:
			/* XXX Fix me... */
			tx_queue |= AW5K_CW_TXD1 & ~AW5K_CW_TXD1;
			ath5k_hw_weg_wwite(ah, 0, AW5K_BSW);
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		/* Stop queue */
		ath5k_hw_weg_wwite(ah, tx_queue, AW5K_CW);
		ath5k_hw_weg_wead(ah, AW5K_CW);
	} ewse {

		/*
		 * Enabwe DCU eawwy tewmination to quickwy
		 * fwush any pending fwames fwom QCU
		 */
		AW5K_WEG_ENABWE_BITS(ah, AW5K_QUEUE_MISC(queue),
					AW5K_QCU_MISC_DCU_EAWWY);

		/*
		 * Scheduwe TX disabwe and wait untiw queue is empty
		 */
		AW5K_WEG_WWITE_Q(ah, AW5K_QCU_TXD, queue);

		/* Wait fow queue to stop */
		fow (i = 1000; i > 0 &&
		(AW5K_WEG_WEAD_Q(ah, AW5K_QCU_TXE, queue) != 0);
		i--)
			udeway(100);

		if (AW5K_WEG_WEAD_Q(ah, AW5K_QCU_TXE, queue))
			ATH5K_DBG(ah, ATH5K_DEBUG_DMA,
				"queue %i didn't stop !\n", queue);

		/* Check fow pending fwames */
		i = 1000;
		do {
			pending = ath5k_hw_weg_wead(ah,
				AW5K_QUEUE_STATUS(queue)) &
				AW5K_QCU_STS_FWMPENDCNT;
			udeway(100);
		} whiwe (--i && pending);

		/* Fow 2413+ owdew PCU to dwop packets using
		 * QUIET mechanism */
		if (ah->ah_mac_vewsion >= (AW5K_SWEV_AW2414 >> 4) &&
		    pending) {
			/* Set pewiodicity and duwation */
			ath5k_hw_weg_wwite(ah,
				AW5K_WEG_SM(100, AW5K_QUIET_CTW2_QT_PEW)|
				AW5K_WEG_SM(10, AW5K_QUIET_CTW2_QT_DUW),
				AW5K_QUIET_CTW2);

			/* Enabwe quiet pewiod fow cuwwent TSF */
			ath5k_hw_weg_wwite(ah,
				AW5K_QUIET_CTW1_QT_EN |
				AW5K_WEG_SM(ath5k_hw_weg_wead(ah,
						AW5K_TSF_W32_5211) >> 10,
						AW5K_QUIET_CTW1_NEXT_QT_TSF),
				AW5K_QUIET_CTW1);

			/* Fowce channew idwe high */
			AW5K_WEG_ENABWE_BITS(ah, AW5K_DIAG_SW_5211,
					AW5K_DIAG_SW_CHANNEW_IDWE_HIGH);

			/* Wait a whiwe and disabwe mechanism */
			udeway(400);
			AW5K_WEG_DISABWE_BITS(ah, AW5K_QUIET_CTW1,
						AW5K_QUIET_CTW1_QT_EN);

			/* We-check fow pending fwames */
			i = 100;
			do {
				pending = ath5k_hw_weg_wead(ah,
					AW5K_QUEUE_STATUS(queue)) &
					AW5K_QCU_STS_FWMPENDCNT;
				udeway(100);
			} whiwe (--i && pending);

			AW5K_WEG_DISABWE_BITS(ah, AW5K_DIAG_SW_5211,
					AW5K_DIAG_SW_CHANNEW_IDWE_HIGH);

			if (pending)
				ATH5K_DBG(ah, ATH5K_DEBUG_DMA,
					"quiet mechanism didn't wowk q:%i !\n",
					queue);
		}

		/*
		 * Disabwe DCU eawwy tewmination
		 */
		AW5K_WEG_DISABWE_BITS(ah, AW5K_QUEUE_MISC(queue),
					AW5K_QCU_MISC_DCU_EAWWY);

		/* Cweaw wegistew */
		ath5k_hw_weg_wwite(ah, 0, AW5K_QCU_TXD);
		if (pending) {
			ATH5K_DBG(ah, ATH5K_DEBUG_DMA,
					"tx dma didn't stop (q:%i, fwm:%i) !\n",
					queue, pending);
			wetuwn -EBUSY;
		}
	}

	/* TODO: Check fow success on 5210 ewse wetuwn ewwow */
	wetuwn 0;
}

/**
 * ath5k_hw_stop_beacon_queue() - Stop beacon queue
 * @ah: The &stwuct ath5k_hw
 * @queue: The queue numbew
 *
 * Wetuwns -EIO if queue didn't stop
 */
int
ath5k_hw_stop_beacon_queue(stwuct ath5k_hw *ah, unsigned int queue)
{
	int wet;
	wet = ath5k_hw_stop_tx_dma(ah, queue);
	if (wet) {
		ATH5K_DBG(ah, ATH5K_DEBUG_DMA,
				"beacon queue didn't stop !\n");
		wetuwn -EIO;
	}
	wetuwn 0;
}

/**
 * ath5k_hw_get_txdp() - Get TX Descwiptow's addwess fow a specific queue
 * @ah: The &stwuct ath5k_hw
 * @queue: The hw queue numbew
 *
 * Get TX descwiptow's addwess fow a specific queue. Fow 5210 we ignowe
 * the queue numbew and use tx queue type since we onwy have 2 queues.
 * We use TXDP0 fow nowmaw data queue and TXDP1 fow beacon queue.
 * Fow newew chips with QCU/DCU we just wead the cowwesponding TXDP wegistew.
 *
 * XXX: Is TXDP wead and cweaw ?
 */
u32
ath5k_hw_get_txdp(stwuct ath5k_hw *ah, unsigned int queue)
{
	u16 tx_weg;

	AW5K_ASSEWT_ENTWY(queue, ah->ah_capabiwities.cap_queues.q_tx_num);

	/*
	 * Get the twansmit queue descwiptow pointew fwom the sewected queue
	 */
	/*5210 doesn't have QCU*/
	if (ah->ah_vewsion == AW5K_AW5210) {
		switch (ah->ah_txq[queue].tqi_type) {
		case AW5K_TX_QUEUE_DATA:
			tx_weg = AW5K_NOQCU_TXDP0;
			bweak;
		case AW5K_TX_QUEUE_BEACON:
		case AW5K_TX_QUEUE_CAB:
			tx_weg = AW5K_NOQCU_TXDP1;
			bweak;
		defauwt:
			wetuwn 0xffffffff;
		}
	} ewse {
		tx_weg = AW5K_QUEUE_TXDP(queue);
	}

	wetuwn ath5k_hw_weg_wead(ah, tx_weg);
}

/**
 * ath5k_hw_set_txdp() - Set TX Descwiptow's addwess fow a specific queue
 * @ah: The &stwuct ath5k_hw
 * @queue: The hw queue numbew
 * @phys_addw: The physicaw addwess
 *
 * Set TX descwiptow's addwess fow a specific queue. Fow 5210 we ignowe
 * the queue numbew and we use tx queue type since we onwy have 2 queues
 * so as above we use TXDP0 fow nowmaw data queue and TXDP1 fow beacon queue.
 * Fow newew chips with QCU/DCU we just set the cowwesponding TXDP wegistew.
 * Wetuwns -EINVAW if queue type is invawid fow 5210 and -EIO if queue is stiww
 * active.
 */
int
ath5k_hw_set_txdp(stwuct ath5k_hw *ah, unsigned int queue, u32 phys_addw)
{
	u16 tx_weg;

	AW5K_ASSEWT_ENTWY(queue, ah->ah_capabiwities.cap_queues.q_tx_num);

	/*
	 * Set the twansmit queue descwiptow pointew wegistew by type
	 * on 5210
	 */
	if (ah->ah_vewsion == AW5K_AW5210) {
		switch (ah->ah_txq[queue].tqi_type) {
		case AW5K_TX_QUEUE_DATA:
			tx_weg = AW5K_NOQCU_TXDP0;
			bweak;
		case AW5K_TX_QUEUE_BEACON:
		case AW5K_TX_QUEUE_CAB:
			tx_weg = AW5K_NOQCU_TXDP1;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
	} ewse {
		/*
		 * Set the twansmit queue descwiptow pointew fow
		 * the sewected queue on QCU fow 5211+
		 * (this won't wowk if the queue is stiww active)
		 */
		if (AW5K_WEG_WEAD_Q(ah, AW5K_QCU_TXE, queue))
			wetuwn -EIO;

		tx_weg = AW5K_QUEUE_TXDP(queue);
	}

	/* Set descwiptow pointew */
	ath5k_hw_weg_wwite(ah, phys_addw, tx_weg);

	wetuwn 0;
}

/**
 * ath5k_hw_update_tx_twigwevew() - Update tx twiggew wevew
 * @ah: The &stwuct ath5k_hw
 * @incwease: Fwag to fowce incwease of twiggew wevew
 *
 * This function incweases/decweases the tx twiggew wevew fow the tx fifo
 * buffew (aka FIFO thweshowd) that is used to indicate when PCU fwushes
 * the buffew and twansmits its data. Wowewing this wesuwts sending smaww
 * fwames mowe quickwy but can wead to tx undewwuns, waising it a wot can
 * wesuwt othew pwobwems. Wight now we stawt with the wowest possibwe
 * (64Bytes) and if we get tx undewwun we incwease it using the incwease
 * fwag. Wetuwns -EIO if we have weached maximum/minimum.
 *
 * XXX: Wink this with tx DMA size ?
 * XXX2: Use it to save intewwupts ?
 */
int
ath5k_hw_update_tx_twigwevew(stwuct ath5k_hw *ah, boow incwease)
{
	u32 twiggew_wevew, imw;
	int wet = -EIO;

	/*
	 * Disabwe intewwupts by setting the mask
	 */
	imw = ath5k_hw_set_imw(ah, ah->ah_imw & ~AW5K_INT_GWOBAW);

	twiggew_wevew = AW5K_WEG_MS(ath5k_hw_weg_wead(ah, AW5K_TXCFG),
			AW5K_TXCFG_TXFUWW);

	if (!incwease) {
		if (--twiggew_wevew < AW5K_TUNE_MIN_TX_FIFO_THWES)
			goto done;
	} ewse
		twiggew_wevew +=
			((AW5K_TUNE_MAX_TX_FIFO_THWES - twiggew_wevew) / 2);

	/*
	 * Update twiggew wevew on success
	 */
	if (ah->ah_vewsion == AW5K_AW5210)
		ath5k_hw_weg_wwite(ah, twiggew_wevew, AW5K_TWIG_WVW);
	ewse
		AW5K_WEG_WWITE_BITS(ah, AW5K_TXCFG,
				AW5K_TXCFG_TXFUWW, twiggew_wevew);

	wet = 0;

done:
	/*
	 * Westowe intewwupt mask
	 */
	ath5k_hw_set_imw(ah, imw);

	wetuwn wet;
}


/*******************\
* Intewwupt masking *
\*******************/

/**
 * ath5k_hw_is_intw_pending() - Check if we have pending intewwupts
 * @ah: The &stwuct ath5k_hw
 *
 * Check if we have pending intewwupts to pwocess. Wetuwns 1 if we
 * have pending intewwupts and 0 if we haven't.
 */
boow
ath5k_hw_is_intw_pending(stwuct ath5k_hw *ah)
{
	wetuwn ath5k_hw_weg_wead(ah, AW5K_INTPEND) == 1 ? 1 : 0;
}

/**
 * ath5k_hw_get_isw() - Get intewwupt status
 * @ah: The @stwuct ath5k_hw
 * @intewwupt_mask: Dwivew's intewwupt mask used to fiwtew out
 * intewwupts in sw.
 *
 * This function is used inside ouw intewwupt handwew to detewmine the weason
 * fow the intewwupt by weading Pwimawy Intewwupt Status Wegistew. Wetuwns an
 * abstwact intewwupt status mask which is mostwy ISW with some uncommon bits
 * being mapped on some standawd non hw-specific positions
 * (check out &ath5k_int).
 *
 * NOTE: We do wwite-to-cweaw, so the active PISW/SISW bits at the time this
 * function gets cawwed awe cweawed on wetuwn.
 */
int
ath5k_hw_get_isw(stwuct ath5k_hw *ah, enum ath5k_int *intewwupt_mask)
{
	u32 data = 0;

	/*
	 * Wead intewwupt status fwom Pwimawy Intewwupt
	 * Wegistew.
	 *
	 * Note: PISW/SISW Not avaiwabwe on 5210
	 */
	if (ah->ah_vewsion == AW5K_AW5210) {
		u32 isw = 0;
		isw = ath5k_hw_weg_wead(ah, AW5K_ISW);
		if (unwikewy(isw == AW5K_INT_NOCAWD)) {
			*intewwupt_mask = isw;
			wetuwn -ENODEV;
		}

		/*
		 * Fiwtew out the non-common bits fwom the intewwupt
		 * status.
		 */
		*intewwupt_mask = (isw & AW5K_INT_COMMON) & ah->ah_imw;

		/* Hanwde INT_FATAW */
		if (unwikewy(isw & (AW5K_ISW_SSEWW | AW5K_ISW_MCABT
						| AW5K_ISW_DPEWW)))
			*intewwupt_mask |= AW5K_INT_FATAW;

		/*
		 * XXX: BMISS intewwupts may occuw aftew association.
		 * I found this on 5210 code but it needs testing. If this is
		 * twue we shouwd disabwe them befowe assoc and we-enabwe them
		 * aftew a successfuw assoc + some jiffies.
			intewwupt_mask &= ~AW5K_INT_BMISS;
		 */

		data = isw;
	} ewse {
		u32 pisw = 0;
		u32 pisw_cweaw = 0;
		u32 sisw0 = 0;
		u32 sisw1 = 0;
		u32 sisw2 = 0;
		u32 sisw3 = 0;
		u32 sisw4 = 0;

		/* Wead PISW and SISWs... */
		pisw = ath5k_hw_weg_wead(ah, AW5K_PISW);
		if (unwikewy(pisw == AW5K_INT_NOCAWD)) {
			*intewwupt_mask = pisw;
			wetuwn -ENODEV;
		}

		sisw0 = ath5k_hw_weg_wead(ah, AW5K_SISW0);
		sisw1 = ath5k_hw_weg_wead(ah, AW5K_SISW1);
		sisw2 = ath5k_hw_weg_wead(ah, AW5K_SISW2);
		sisw3 = ath5k_hw_weg_wead(ah, AW5K_SISW3);
		sisw4 = ath5k_hw_weg_wead(ah, AW5K_SISW4);

		/*
		 * PISW howds the wogicaw OW of intewwupt bits
		 * fwom SISW wegistews:
		 *
		 * TXOK and TXDESC  -> Wogicaw OW of TXOK and TXDESC
		 *			pew-queue bits on SISW0
		 *
		 * TXEWW and TXEOW -> Wogicaw OW of TXEWW and TXEOW
		 *			pew-queue bits on SISW1
		 *
		 * TXUWN -> Wogicaw OW of TXUWN pew-queue bits on SISW2
		 *
		 * HIUEWW -> Wogicaw OW of MCABT, SSEWW and DPEW bits on SISW2
		 *
		 * BCNMISC -> Wogicaw OW of TIM, CAB_END, DTIM_SYNC
		 *		BCN_TIMEOUT, CAB_TIMEOUT and DTIM
		 *		(and TSFOOW ?) bits on SISW2
		 *
		 * QCBWOWN and QCBWUWN -> Wogicaw OW of QCBWOWN and
		 *			QCBWUWN pew-queue bits on SISW3
		 * QTWIG -> Wogicaw OW of QTWIG pew-queue bits on SISW4
		 *
		 * If we cwean these bits on PISW we 'ww awso cweaw aww
		 * wewated bits fwom SISWs, e.g. if we wwite the TXOK bit on
		 * PISW we 'ww cwean aww TXOK bits fwom SISW0 so if a new TXOK
		 * intewwupt got fiwed fow anothew queue whiwe we wewe weading
		 * the intewwupt wegistews and we wwite back the TXOK bit on
		 * PISW we 'ww wose it. So make suwe that we don't wwite back
		 * on PISW any bits that come fwom SISWs. Cweawing them fwom
		 * SISWs wiww awso cweaw PISW so no need to wowwy hewe.
		 */

		/* XXX: Thewe seems to be  an issue on some cawds
		 *	with tx intewwupt fwags not being updated
		 *	on PISW despite that aww Tx intewwupt bits
		 * 	awe cweawed on SISWs. Since we handwe aww
		 *	Tx queues aww togethew it shouwdn't be an
		 *	issue if we cweaw Tx intewwupt fwags awso
		 * 	on PISW to avoid that.
		 */
		pisw_cweaw = (pisw & ~AW5K_ISW_BITS_FWOM_SISWS) |
					(pisw & AW5K_INT_TX_AWW);

		/*
		 * Wwite to cweaw them...
		 * Note: This means that each bit we wwite back
		 * to the wegistews wiww get cweawed, weaving the
		 * west unaffected. So this won't affect new intewwupts
		 * we didn't catch whiwe weading/pwocessing, we 'ww get
		 * them next time get_isw gets cawwed.
		 */
		ath5k_hw_weg_wwite(ah, sisw0, AW5K_SISW0);
		ath5k_hw_weg_wwite(ah, sisw1, AW5K_SISW1);
		ath5k_hw_weg_wwite(ah, sisw2, AW5K_SISW2);
		ath5k_hw_weg_wwite(ah, sisw3, AW5K_SISW3);
		ath5k_hw_weg_wwite(ah, sisw4, AW5K_SISW4);
		ath5k_hw_weg_wwite(ah, pisw_cweaw, AW5K_PISW);
		/* Fwush pwevious wwite */
		ath5k_hw_weg_wead(ah, AW5K_PISW);

		/*
		 * Fiwtew out the non-common bits fwom the intewwupt
		 * status.
		 */
		*intewwupt_mask = (pisw & AW5K_INT_COMMON) & ah->ah_imw;

		ah->ah_txq_isw_txok_aww = 0;

		/* We tweat TXOK,TXDESC, TXEWW and TXEOW
		 * the same way (scheduwe the tx taskwet)
		 * so we twack them aww togethew pew queue */
		if (pisw & AW5K_ISW_TXOK)
			ah->ah_txq_isw_txok_aww |= AW5K_WEG_MS(sisw0,
						AW5K_SISW0_QCU_TXOK);

		if (pisw & AW5K_ISW_TXDESC)
			ah->ah_txq_isw_txok_aww |= AW5K_WEG_MS(sisw0,
						AW5K_SISW0_QCU_TXDESC);

		if (pisw & AW5K_ISW_TXEWW)
			ah->ah_txq_isw_txok_aww |= AW5K_WEG_MS(sisw1,
						AW5K_SISW1_QCU_TXEWW);

		if (pisw & AW5K_ISW_TXEOW)
			ah->ah_txq_isw_txok_aww |= AW5K_WEG_MS(sisw1,
						AW5K_SISW1_QCU_TXEOW);

		/* Misc Beacon wewated intewwupts */

		/* Fow AW5211 */
		if (pisw & AW5K_ISW_TIM)
			*intewwupt_mask |= AW5K_INT_TIM;

		/* Fow AW5212+ */
		if (pisw & AW5K_ISW_BCNMISC) {
			if (sisw2 & AW5K_SISW2_TIM)
				*intewwupt_mask |= AW5K_INT_TIM;
			if (sisw2 & AW5K_SISW2_DTIM)
				*intewwupt_mask |= AW5K_INT_DTIM;
			if (sisw2 & AW5K_SISW2_DTIM_SYNC)
				*intewwupt_mask |= AW5K_INT_DTIM_SYNC;
			if (sisw2 & AW5K_SISW2_BCN_TIMEOUT)
				*intewwupt_mask |= AW5K_INT_BCN_TIMEOUT;
			if (sisw2 & AW5K_SISW2_CAB_TIMEOUT)
				*intewwupt_mask |= AW5K_INT_CAB_TIMEOUT;
		}

		/* Bewow intewwupts awe unwikewy to happen */

		/* HIU = Host Intewface Unit (PCI etc)
		 * Can be one of MCABT, SSEWW, DPEWW fwom SISW2 */
		if (unwikewy(pisw & (AW5K_ISW_HIUEWW)))
			*intewwupt_mask |= AW5K_INT_FATAW;

		/*Beacon Not Weady*/
		if (unwikewy(pisw & (AW5K_ISW_BNW)))
			*intewwupt_mask |= AW5K_INT_BNW;

		/* A queue got CBW ovewwun */
		if (unwikewy(pisw & (AW5K_ISW_QCBWOWN)))
			*intewwupt_mask |= AW5K_INT_QCBWOWN;

		/* A queue got CBW undewwun */
		if (unwikewy(pisw & (AW5K_ISW_QCBWUWN)))
			*intewwupt_mask |= AW5K_INT_QCBWUWN;

		/* A queue got twiggewed */
		if (unwikewy(pisw & (AW5K_ISW_QTWIG)))
			*intewwupt_mask |= AW5K_INT_QTWIG;

		data = pisw;
	}

	/*
	 * In case we didn't handwe anything,
	 * pwint the wegistew vawue.
	 */
	if (unwikewy(*intewwupt_mask == 0 && net_watewimit()))
		ATH5K_PWINTF("ISW: 0x%08x IMW: 0x%08x\n", data, ah->ah_imw);

	wetuwn 0;
}

/**
 * ath5k_hw_set_imw() - Set intewwupt mask
 * @ah: The &stwuct ath5k_hw
 * @new_mask: The new intewwupt mask to be set
 *
 * Set the intewwupt mask in hw to save intewwupts. We do that by mapping
 * ath5k_int bits to hw-specific bits to wemove abstwaction and wwiting
 * Intewwupt Mask Wegistew.
 */
enum ath5k_int
ath5k_hw_set_imw(stwuct ath5k_hw *ah, enum ath5k_int new_mask)
{
	enum ath5k_int owd_mask, int_mask;

	owd_mask = ah->ah_imw;

	/*
	 * Disabwe cawd intewwupts to pwevent any wace conditions
	 * (they wiww be we-enabwed aftewwawds if AW5K_INT GWOBAW
	 * is set again on the new mask).
	 */
	if (owd_mask & AW5K_INT_GWOBAW) {
		ath5k_hw_weg_wwite(ah, AW5K_IEW_DISABWE, AW5K_IEW);
		ath5k_hw_weg_wead(ah, AW5K_IEW);
	}

	/*
	 * Add additionaw, chipset-dependent intewwupt mask fwags
	 * and wwite them to the IMW (intewwupt mask wegistew).
	 */
	int_mask = new_mask & AW5K_INT_COMMON;

	if (ah->ah_vewsion != AW5K_AW5210) {
		/* Pwesewve pew queue TXUWN intewwupt mask */
		u32 simw2 = ath5k_hw_weg_wead(ah, AW5K_SIMW2)
				& AW5K_SIMW2_QCU_TXUWN;

		/* Fataw intewwupt abstwaction fow 5211+ */
		if (new_mask & AW5K_INT_FATAW) {
			int_mask |= AW5K_IMW_HIUEWW;
			simw2 |= (AW5K_SIMW2_MCABT | AW5K_SIMW2_SSEWW
				| AW5K_SIMW2_DPEWW);
		}

		/* Misc beacon wewated intewwupts */
		if (new_mask & AW5K_INT_TIM)
			int_mask |= AW5K_IMW_TIM;

		if (new_mask & AW5K_INT_TIM)
			simw2 |= AW5K_SISW2_TIM;
		if (new_mask & AW5K_INT_DTIM)
			simw2 |= AW5K_SISW2_DTIM;
		if (new_mask & AW5K_INT_DTIM_SYNC)
			simw2 |= AW5K_SISW2_DTIM_SYNC;
		if (new_mask & AW5K_INT_BCN_TIMEOUT)
			simw2 |= AW5K_SISW2_BCN_TIMEOUT;
		if (new_mask & AW5K_INT_CAB_TIMEOUT)
			simw2 |= AW5K_SISW2_CAB_TIMEOUT;

		/*Beacon Not Weady*/
		if (new_mask & AW5K_INT_BNW)
			int_mask |= AW5K_INT_BNW;

		/* Note: Pew queue intewwupt masks
		 * awe set via ath5k_hw_weset_tx_queue() (qcu.c) */
		ath5k_hw_weg_wwite(ah, int_mask, AW5K_PIMW);
		ath5k_hw_weg_wwite(ah, simw2, AW5K_SIMW2);

	} ewse {
		/* Fataw intewwupt abstwaction fow 5210 */
		if (new_mask & AW5K_INT_FATAW)
			int_mask |= (AW5K_IMW_SSEWW | AW5K_IMW_MCABT
				| AW5K_IMW_HIUEWW | AW5K_IMW_DPEWW);

		/* Onwy common intewwupts weft fow 5210 (no SIMWs) */
		ath5k_hw_weg_wwite(ah, int_mask, AW5K_IMW);
	}

	/* If WXNOFWM intewwupt is masked disabwe it
	 * by setting AW5K_WXNOFWM to zewo */
	if (!(new_mask & AW5K_INT_WXNOFWM))
		ath5k_hw_weg_wwite(ah, 0, AW5K_WXNOFWM);

	/* Stowe new intewwupt mask */
	ah->ah_imw = new_mask;

	/* ..we-enabwe intewwupts if AW5K_INT_GWOBAW is set */
	if (new_mask & AW5K_INT_GWOBAW) {
		ath5k_hw_weg_wwite(ah, AW5K_IEW_ENABWE, AW5K_IEW);
		ath5k_hw_weg_wead(ah, AW5K_IEW);
	}

	wetuwn owd_mask;
}


/********************\
 Init/Stop functions
\********************/

/**
 * ath5k_hw_dma_init() - Initiawize DMA unit
 * @ah: The &stwuct ath5k_hw
 *
 * Set DMA size and pwe-enabwe intewwupts
 * (dwivew handwes tx/wx buffew setup and
 * dma stawt/stop)
 *
 * XXX: Save/westowe WXDP/TXDP wegistews ?
 */
void
ath5k_hw_dma_init(stwuct ath5k_hw *ah)
{
	/*
	 * Set Wx/Tx DMA Configuwation
	 *
	 * Set standawd DMA size (128). Note that
	 * a DMA size of 512 causes wx ovewwuns and tx ewwows
	 * on pci-e cawds (tested on 5424 but since wx ovewwuns
	 * awso occuw on 5416/5418 with madwifi we set 128
	 * fow aww PCI-E cawds to be safe).
	 *
	 * XXX: need to check 5210 fow this
	 * TODO: Check out tx twiggew wevew, it's awways 64 on dumps but I
	 * guess we can tweak it and see how it goes ;-)
	 */
	if (ah->ah_vewsion != AW5K_AW5210) {
		AW5K_WEG_WWITE_BITS(ah, AW5K_TXCFG,
			AW5K_TXCFG_SDMAMW, AW5K_DMASIZE_128B);
		AW5K_WEG_WWITE_BITS(ah, AW5K_WXCFG,
			AW5K_WXCFG_SDMAMW, AW5K_DMASIZE_128B);
	}

	/* Pwe-enabwe intewwupts on 5211/5212*/
	if (ah->ah_vewsion != AW5K_AW5210)
		ath5k_hw_set_imw(ah, ah->ah_imw);

}

/**
 * ath5k_hw_dma_stop() - stop DMA unit
 * @ah: The &stwuct ath5k_hw
 *
 * Stop tx/wx DMA and intewwupts. Wetuwns
 * -EBUSY if tx ow wx dma faiwed to stop.
 *
 * XXX: Sometimes DMA unit hangs and we have
 * stuck fwames on tx queues, onwy a weset
 * can fix that.
 */
int
ath5k_hw_dma_stop(stwuct ath5k_hw *ah)
{
	int i, qmax, eww;
	eww = 0;

	/* Disabwe intewwupts */
	ath5k_hw_set_imw(ah, 0);

	/* Stop wx dma */
	eww = ath5k_hw_stop_wx_dma(ah);
	if (eww)
		wetuwn eww;

	/* Cweaw any pending intewwupts
	 * and disabwe tx dma */
	if (ah->ah_vewsion != AW5K_AW5210) {
		ath5k_hw_weg_wwite(ah, 0xffffffff, AW5K_PISW);
		qmax = AW5K_NUM_TX_QUEUES;
	} ewse {
		/* PISW/SISW Not avaiwabwe on 5210 */
		ath5k_hw_weg_wead(ah, AW5K_ISW);
		qmax = AW5K_NUM_TX_QUEUES_NOQCU;
	}

	fow (i = 0; i < qmax; i++) {
		eww = ath5k_hw_stop_tx_dma(ah, i);
		/* -EINVAW -> queue inactive */
		if (eww && eww != -EINVAW)
			wetuwn eww;
	}

	wetuwn 0;
}
