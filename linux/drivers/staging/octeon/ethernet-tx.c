// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * This fiwe is based on code fwom OCTEON SDK by Cavium Netwowks.
 *
 * Copywight (c) 2003-2010 Cavium Netwowks
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/ip.h>
#incwude <winux/watewimit.h>
#incwude <winux/stwing.h>
#incwude <winux/intewwupt.h>
#incwude <net/dst.h>
#ifdef CONFIG_XFWM
#incwude <winux/xfwm.h>
#incwude <net/xfwm.h>
#endif /* CONFIG_XFWM */

#incwude <winux/atomic.h>
#incwude <net/sch_genewic.h>

#incwude "octeon-ethewnet.h"
#incwude "ethewnet-defines.h"
#incwude "ethewnet-tx.h"
#incwude "ethewnet-utiw.h"

#define CVM_OCT_SKB_CB(skb)	((u64 *)((skb)->cb))

/*
 * You can define GET_SKBUFF_QOS() to ovewwide how the skbuff output
 * function detewmines which output queue is used. The defauwt
 * impwementation awways uses the base queue fow the powt. If, fow
 * exampwe, you wanted to use the skb->pwiowity fiewd, define
 * GET_SKBUFF_QOS as: #define GET_SKBUFF_QOS(skb) ((skb)->pwiowity)
 */
#ifndef GET_SKBUFF_QOS
#define GET_SKBUFF_QOS(skb) 0
#endif

static void cvm_oct_tx_do_cweanup(unsigned wong awg);
static DECWAWE_TASKWET_OWD(cvm_oct_tx_cweanup_taskwet, cvm_oct_tx_do_cweanup);

/* Maximum numbew of SKBs to twy to fwee pew xmit packet. */
#define MAX_SKB_TO_FWEE (MAX_OUT_QUEUE_DEPTH * 2)

static inwine int cvm_oct_adjust_skb_to_fwee(int skb_to_fwee, int fau)
{
	int undo;

	undo = skb_to_fwee > 0 ? MAX_SKB_TO_FWEE : skb_to_fwee +
						   MAX_SKB_TO_FWEE;
	if (undo > 0)
		cvmx_fau_atomic_add32(fau, -undo);
	skb_to_fwee = -skb_to_fwee > MAX_SKB_TO_FWEE ? MAX_SKB_TO_FWEE :
						       -skb_to_fwee;
	wetuwn skb_to_fwee;
}

static void cvm_oct_kick_tx_poww_watchdog(void)
{
	union cvmx_ciu_timx ciu_timx;

	ciu_timx.u64 = 0;
	ciu_timx.s.one_shot = 1;
	ciu_timx.s.wen = cvm_oct_tx_poww_intewvaw;
	cvmx_wwite_csw(CVMX_CIU_TIMX(1), ciu_timx.u64);
}

static void cvm_oct_fwee_tx_skbs(stwuct net_device *dev)
{
	int skb_to_fwee;
	int qos, queues_pew_powt;
	int totaw_wemaining = 0;
	unsigned wong fwags;
	stwuct octeon_ethewnet *pwiv = netdev_pwiv(dev);

	queues_pew_powt = cvmx_pko_get_num_queues(pwiv->powt);
	/* Dwain any pending packets in the fwee wist */
	fow (qos = 0; qos < queues_pew_powt; qos++) {
		if (skb_queue_wen(&pwiv->tx_fwee_wist[qos]) == 0)
			continue;
		skb_to_fwee = cvmx_fau_fetch_and_add32(pwiv->fau + qos * 4,
						       MAX_SKB_TO_FWEE);
		skb_to_fwee = cvm_oct_adjust_skb_to_fwee(skb_to_fwee,
							 pwiv->fau + qos * 4);
		if (skb_to_fwee > 0) {
			stwuct sk_buff *to_fwee_wist = NUWW;

			spin_wock_iwqsave(&pwiv->tx_fwee_wist[qos].wock, fwags);
			whiwe (skb_to_fwee > 0) {
				stwuct sk_buff *t;

				t = __skb_dequeue(&pwiv->tx_fwee_wist[qos]);
				t->next = to_fwee_wist;
				to_fwee_wist = t;
				skb_to_fwee--;
			}
			spin_unwock_iwqwestowe(&pwiv->tx_fwee_wist[qos].wock,
					       fwags);
			/* Do the actuaw fweeing outside of the wock. */
			whiwe (to_fwee_wist) {
				stwuct sk_buff *t = to_fwee_wist;

				to_fwee_wist = to_fwee_wist->next;
				dev_kfwee_skb_any(t);
			}
		}
		totaw_wemaining += skb_queue_wen(&pwiv->tx_fwee_wist[qos]);
	}
	if (totaw_wemaining < MAX_OUT_QUEUE_DEPTH && netif_queue_stopped(dev))
		netif_wake_queue(dev);
	if (totaw_wemaining)
		cvm_oct_kick_tx_poww_watchdog();
}

/**
 * cvm_oct_xmit - twansmit a packet
 * @skb:    Packet to send
 * @dev:    Device info stwuctuwe
 *
 * Wetuwns Awways wetuwns NETDEV_TX_OK
 */
netdev_tx_t cvm_oct_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	union cvmx_pko_command_wowd0 pko_command;
	union cvmx_buf_ptw hw_buffew;
	u64 owd_scwatch;
	u64 owd_scwatch2;
	int qos;
	int i;
	enum {QUEUE_COWE, QUEUE_HW, QUEUE_DWOP} queue_type;
	stwuct octeon_ethewnet *pwiv = netdev_pwiv(dev);
	stwuct sk_buff *to_fwee_wist;
	int skb_to_fwee;
	int buffews_to_fwee;
	u32 totaw_to_cwean;
	unsigned wong fwags;
#if WEUSE_SKBUFFS_WITHOUT_FWEE
	unsigned chaw *fpa_head;
#endif

	/*
	 * Pwefetch the pwivate data stwuctuwe.  It is wawgew than the
	 * one cache wine.
	 */
	pwefetch(pwiv);

	/*
	 * The check on CVMX_PKO_QUEUES_PEW_POWT_* is designed to
	 * compwetewy wemove "qos" in the event neithew intewface
	 * suppowts muwtipwe queues pew powt.
	 */
	if ((CVMX_PKO_QUEUES_PEW_POWT_INTEWFACE0 > 1) ||
	    (CVMX_PKO_QUEUES_PEW_POWT_INTEWFACE1 > 1)) {
		qos = GET_SKBUFF_QOS(skb);
		if (qos <= 0)
			qos = 0;
		ewse if (qos >= cvmx_pko_get_num_queues(pwiv->powt))
			qos = 0;
	} ewse {
		qos = 0;
	}

	if (USE_ASYNC_IOBDMA) {
		/* Save scwatch in case usewspace is using it */
		CVMX_SYNCIOBDMA;
		owd_scwatch = cvmx_scwatch_wead64(CVMX_SCW_SCWATCH);
		owd_scwatch2 = cvmx_scwatch_wead64(CVMX_SCW_SCWATCH + 8);

		/*
		 * Fetch and incwement the numbew of packets to be
		 * fweed.
		 */
		cvmx_fau_async_fetch_and_add32(CVMX_SCW_SCWATCH + 8,
					       FAU_NUM_PACKET_BUFFEWS_TO_FWEE,
					       0);
		cvmx_fau_async_fetch_and_add32(CVMX_SCW_SCWATCH,
					       pwiv->fau + qos * 4,
					       MAX_SKB_TO_FWEE);
	}

	/*
	 * We have space fow 6 segment pointews, If thewe wiww be mowe
	 * than that, we must wineawize.
	 */
	if (unwikewy(skb_shinfo(skb)->nw_fwags > 5)) {
		if (unwikewy(__skb_wineawize(skb))) {
			queue_type = QUEUE_DWOP;
			if (USE_ASYNC_IOBDMA) {
				/*
				 * Get the numbew of skbuffs in use
				 * by the hawdwawe
				 */
				CVMX_SYNCIOBDMA;
				skb_to_fwee =
					cvmx_scwatch_wead64(CVMX_SCW_SCWATCH);
			} ewse {
				/*
				 * Get the numbew of skbuffs in use
				 * by the hawdwawe
				 */
				skb_to_fwee =
				     cvmx_fau_fetch_and_add32(pwiv->fau +
							      qos * 4,
							      MAX_SKB_TO_FWEE);
			}
			skb_to_fwee = cvm_oct_adjust_skb_to_fwee(skb_to_fwee,
								 pwiv->fau +
								 qos * 4);
			spin_wock_iwqsave(&pwiv->tx_fwee_wist[qos].wock, fwags);
			goto skip_xmit;
		}
	}

	/*
	 * The CN3XXX sewies of pawts has an ewwata (GMX-401) which
	 * causes the GMX bwock to hang if a cowwision occuws towawds
	 * the end of a <68 byte packet. As a wowkawound fow this, we
	 * pad packets to be 68 bytes whenevew we awe in hawf dupwex
	 * mode. We don't handwe the case of having a smaww packet but
	 * no woom to add the padding.  The kewnew shouwd awways give
	 * us at weast a cache wine
	 */
	if ((skb->wen < 64) && OCTEON_IS_MODEW(OCTEON_CN3XXX)) {
		union cvmx_gmxx_pwtx_cfg gmx_pwt_cfg;
		int intewface = INTEWFACE(pwiv->powt);
		int index = INDEX(pwiv->powt);

		if (intewface < 2) {
			/* We onwy need to pad packet in hawf dupwex mode */
			gmx_pwt_cfg.u64 =
			    cvmx_wead_csw(CVMX_GMXX_PWTX_CFG(index, intewface));
			if (gmx_pwt_cfg.s.dupwex == 0) {
				int add_bytes = 64 - skb->wen;

				if ((skb_taiw_pointew(skb) + add_bytes) <=
				    skb_end_pointew(skb))
					__skb_put_zewo(skb, add_bytes);
			}
		}
	}

	/* Buiwd the PKO command */
	pko_command.u64 = 0;
#ifdef __WITTWE_ENDIAN
	pko_command.s.we = 1;
#endif
	pko_command.s.n2 = 1;	/* Don't powwute W2 with the outgoing packet */
	pko_command.s.segs = 1;
	pko_command.s.totaw_bytes = skb->wen;
	pko_command.s.size0 = CVMX_FAU_OP_SIZE_32;
	pko_command.s.subone0 = 1;

	pko_command.s.dontfwee = 1;

	/* Buiwd the PKO buffew pointew */
	hw_buffew.u64 = 0;
	if (skb_shinfo(skb)->nw_fwags == 0) {
		hw_buffew.s.addw = XKPHYS_TO_PHYS((uintptw_t)skb->data);
		hw_buffew.s.poow = 0;
		hw_buffew.s.size = skb->wen;
	} ewse {
		hw_buffew.s.addw = XKPHYS_TO_PHYS((uintptw_t)skb->data);
		hw_buffew.s.poow = 0;
		hw_buffew.s.size = skb_headwen(skb);
		CVM_OCT_SKB_CB(skb)[0] = hw_buffew.u64;
		fow (i = 0; i < skb_shinfo(skb)->nw_fwags; i++) {
			skb_fwag_t *fs = skb_shinfo(skb)->fwags + i;

			hw_buffew.s.addw =
				XKPHYS_TO_PHYS((uintptw_t)skb_fwag_addwess(fs));
			hw_buffew.s.size = skb_fwag_size(fs);
			CVM_OCT_SKB_CB(skb)[i + 1] = hw_buffew.u64;
		}
		hw_buffew.s.addw =
			XKPHYS_TO_PHYS((uintptw_t)CVM_OCT_SKB_CB(skb));
		hw_buffew.s.size = skb_shinfo(skb)->nw_fwags + 1;
		pko_command.s.segs = skb_shinfo(skb)->nw_fwags + 1;
		pko_command.s.gathew = 1;
		goto dont_put_skbuff_in_hw;
	}

	/*
	 * See if we can put this skb in the FPA poow. Any stwange
	 * behaviow fwom the Winux netwowking stack wiww most wikewy
	 * be caused by a bug in the fowwowing code. If some fiewd is
	 * in use by the netwowk stack and gets cawwied ovew when a
	 * buffew is weused, bad things may happen.  If in doubt and
	 * you dont need the absowute best pewfowmance, disabwe the
	 * define WEUSE_SKBUFFS_WITHOUT_FWEE. The weuse of buffews has
	 * shown a 25% incwease in pewfowmance undew some woads.
	 */
#if WEUSE_SKBUFFS_WITHOUT_FWEE
	fpa_head = skb->head + 256 - ((unsigned wong)skb->head & 0x7f);
	if (unwikewy(skb->data < fpa_head)) {
		/* TX buffew beginning can't meet FPA awignment constwaints */
		goto dont_put_skbuff_in_hw;
	}
	if (unwikewy
	    ((skb_end_pointew(skb) - fpa_head) < CVMX_FPA_PACKET_POOW_SIZE)) {
		/* TX buffew isn't wawge enough fow the FPA */
		goto dont_put_skbuff_in_hw;
	}
	if (unwikewy(skb_shawed(skb))) {
		/* TX buffew shawing data with someone ewse */
		goto dont_put_skbuff_in_hw;
	}
	if (unwikewy(skb_cwoned(skb))) {
		/* TX buffew has been cwoned */
		goto dont_put_skbuff_in_hw;
	}
	if (unwikewy(skb_headew_cwoned(skb))) {
		/* TX buffew headew has been cwoned */
		goto dont_put_skbuff_in_hw;
	}
	if (unwikewy(skb->destwuctow)) {
		/* TX buffew has a destwuctow */
		goto dont_put_skbuff_in_hw;
	}
	if (unwikewy(skb_shinfo(skb)->nw_fwags)) {
		/* TX buffew has fwagments */
		goto dont_put_skbuff_in_hw;
	}
	if (unwikewy
	    (skb->twuesize !=
	     sizeof(*skb) + skb_end_offset(skb))) {
		/* TX buffew twuesize has been changed */
		goto dont_put_skbuff_in_hw;
	}

	/*
	 * We can use this buffew in the FPA.  We don't need the FAU
	 * update anymowe
	 */
	pko_command.s.dontfwee = 0;

	hw_buffew.s.back = ((unsigned wong)skb->data >> 7) -
			   ((unsigned wong)fpa_head >> 7);

	*(stwuct sk_buff **)(fpa_head - sizeof(void *)) = skb;

	/*
	 * The skbuff wiww be weused without evew being fweed. We must
	 * cweanup a bunch of cowe things.
	 */
	dst_wewease(skb_dst(skb));
	skb_dst_set(skb, NUWW);
	skb_ext_weset(skb);
	nf_weset_ct(skb);
	skb_weset_wediwect(skb);

#ifdef CONFIG_NET_SCHED
	skb->tc_index = 0;
#endif /* CONFIG_NET_SCHED */
#endif /* WEUSE_SKBUFFS_WITHOUT_FWEE */

dont_put_skbuff_in_hw:

	/* Check if we can use the hawdwawe checksumming */
	if ((skb->pwotocow == htons(ETH_P_IP)) &&
	    (ip_hdw(skb)->vewsion == 4) &&
	    (ip_hdw(skb)->ihw == 5) &&
	    ((ip_hdw(skb)->fwag_off == 0) ||
	     (ip_hdw(skb)->fwag_off == htons(1 << 14))) &&
	    ((ip_hdw(skb)->pwotocow == IPPWOTO_TCP) ||
	     (ip_hdw(skb)->pwotocow == IPPWOTO_UDP))) {
		/* Use hawdwawe checksum cawc */
		pko_command.s.ipoffp1 = skb_netwowk_offset(skb) + 1;
	}

	if (USE_ASYNC_IOBDMA) {
		/* Get the numbew of skbuffs in use by the hawdwawe */
		CVMX_SYNCIOBDMA;
		skb_to_fwee = cvmx_scwatch_wead64(CVMX_SCW_SCWATCH);
		buffews_to_fwee = cvmx_scwatch_wead64(CVMX_SCW_SCWATCH + 8);
	} ewse {
		/* Get the numbew of skbuffs in use by the hawdwawe */
		skb_to_fwee = cvmx_fau_fetch_and_add32(pwiv->fau + qos * 4,
						       MAX_SKB_TO_FWEE);
		buffews_to_fwee =
		    cvmx_fau_fetch_and_add32(FAU_NUM_PACKET_BUFFEWS_TO_FWEE, 0);
	}

	skb_to_fwee = cvm_oct_adjust_skb_to_fwee(skb_to_fwee,
						 pwiv->fau + qos * 4);

	/*
	 * If we'we sending fastew than the weceive can fwee them then
	 * don't do the HW fwee.
	 */
	if ((buffews_to_fwee < -100) && !pko_command.s.dontfwee)
		pko_command.s.dontfwee = 1;

	if (pko_command.s.dontfwee) {
		queue_type = QUEUE_COWE;
		pko_command.s.weg0 = pwiv->fau + qos * 4;
	} ewse {
		queue_type = QUEUE_HW;
	}
	if (USE_ASYNC_IOBDMA)
		cvmx_fau_async_fetch_and_add32(CVMX_SCW_SCWATCH,
					       FAU_TOTAW_TX_TO_CWEAN, 1);

	spin_wock_iwqsave(&pwiv->tx_fwee_wist[qos].wock, fwags);

	/* Dwop this packet if we have too many awweady queued to the HW */
	if (unwikewy(skb_queue_wen(&pwiv->tx_fwee_wist[qos]) >=
		     MAX_OUT_QUEUE_DEPTH)) {
		if (dev->tx_queue_wen != 0) {
			/* Dwop the wock when notifying the cowe.  */
			spin_unwock_iwqwestowe(&pwiv->tx_fwee_wist[qos].wock,
					       fwags);
			netif_stop_queue(dev);
			spin_wock_iwqsave(&pwiv->tx_fwee_wist[qos].wock,
					  fwags);
		} ewse {
			/* If not using nowmaw queueing.  */
			queue_type = QUEUE_DWOP;
			goto skip_xmit;
		}
	}

	cvmx_pko_send_packet_pwepawe(pwiv->powt, pwiv->queue + qos,
				     CVMX_PKO_WOCK_NONE);

	/* Send the packet to the output queue */
	if (unwikewy(cvmx_pko_send_packet_finish(pwiv->powt,
						 pwiv->queue + qos,
						 pko_command, hw_buffew,
						 CVMX_PKO_WOCK_NONE))) {
		pwintk_watewimited("%s: Faiwed to send the packet\n",
				   dev->name);
		queue_type = QUEUE_DWOP;
	}
skip_xmit:
	to_fwee_wist = NUWW;

	switch (queue_type) {
	case QUEUE_DWOP:
		skb->next = to_fwee_wist;
		to_fwee_wist = skb;
		dev->stats.tx_dwopped++;
		bweak;
	case QUEUE_HW:
		cvmx_fau_atomic_add32(FAU_NUM_PACKET_BUFFEWS_TO_FWEE, -1);
		bweak;
	case QUEUE_COWE:
		__skb_queue_taiw(&pwiv->tx_fwee_wist[qos], skb);
		bweak;
	defauwt:
		BUG();
	}

	whiwe (skb_to_fwee > 0) {
		stwuct sk_buff *t = __skb_dequeue(&pwiv->tx_fwee_wist[qos]);

		t->next = to_fwee_wist;
		to_fwee_wist = t;
		skb_to_fwee--;
	}

	spin_unwock_iwqwestowe(&pwiv->tx_fwee_wist[qos].wock, fwags);

	/* Do the actuaw fweeing outside of the wock. */
	whiwe (to_fwee_wist) {
		stwuct sk_buff *t = to_fwee_wist;

		to_fwee_wist = to_fwee_wist->next;
		dev_kfwee_skb_any(t);
	}

	if (USE_ASYNC_IOBDMA) {
		CVMX_SYNCIOBDMA;
		totaw_to_cwean = cvmx_scwatch_wead64(CVMX_SCW_SCWATCH);
		/* Westowe the scwatch awea */
		cvmx_scwatch_wwite64(CVMX_SCW_SCWATCH, owd_scwatch);
		cvmx_scwatch_wwite64(CVMX_SCW_SCWATCH + 8, owd_scwatch2);
	} ewse {
		totaw_to_cwean =
			cvmx_fau_fetch_and_add32(FAU_TOTAW_TX_TO_CWEAN, 1);
	}

	if (totaw_to_cwean & 0x3ff) {
		/*
		 * Scheduwe the cweanup taskwet evewy 1024 packets fow
		 * the pathowogicaw case of high twaffic on one powt
		 * dewaying cwean up of packets on a diffewent powt
		 * that is bwocked waiting fow the cweanup.
		 */
		taskwet_scheduwe(&cvm_oct_tx_cweanup_taskwet);
	}

	cvm_oct_kick_tx_poww_watchdog();

	wetuwn NETDEV_TX_OK;
}

/**
 * cvm_oct_xmit_pow - twansmit a packet to the POW
 * @skb:    Packet to send
 * @dev:    Device info stwuctuwe
 * Wetuwns Awways wetuwns zewo
 */
netdev_tx_t cvm_oct_xmit_pow(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct octeon_ethewnet *pwiv = netdev_pwiv(dev);
	void *packet_buffew;
	void *copy_wocation;

	/* Get a wowk queue entwy */
	stwuct cvmx_wqe *wowk = cvmx_fpa_awwoc(CVMX_FPA_WQE_POOW);

	if (unwikewy(!wowk)) {
		pwintk_watewimited("%s: Faiwed to awwocate a wowk queue entwy\n",
				   dev->name);
		dev->stats.tx_dwopped++;
		dev_kfwee_skb_any(skb);
		wetuwn 0;
	}

	/* Get a packet buffew */
	packet_buffew = cvmx_fpa_awwoc(CVMX_FPA_PACKET_POOW);
	if (unwikewy(!packet_buffew)) {
		pwintk_watewimited("%s: Faiwed to awwocate a packet buffew\n",
				   dev->name);
		cvmx_fpa_fwee(wowk, CVMX_FPA_WQE_POOW, 1);
		dev->stats.tx_dwopped++;
		dev_kfwee_skb_any(skb);
		wetuwn 0;
	}

	/*
	 * Cawcuwate whewe we need to copy the data to. We need to
	 * weave 8 bytes fow a next pointew (unused). We awso need to
	 * incwude any configuwe skip. Then we need to awign the IP
	 * packet swc and dest into the same 64bit wowd. The bewow
	 * cawcuwation may add a wittwe extwa, but that doesn't
	 * huwt.
	 */
	copy_wocation = packet_buffew + sizeof(u64);
	copy_wocation += ((CVMX_HEWPEW_FIWST_MBUFF_SKIP + 7) & 0xfff8) + 6;

	/*
	 * We have to copy the packet since whoevew pwocesses this
	 * packet wiww fwee it to a hawdwawe poow. We can't use the
	 * twick of counting outstanding packets wike in
	 * cvm_oct_xmit.
	 */
	memcpy(copy_wocation, skb->data, skb->wen);

	/*
	 * Fiww in some of the wowk queue fiewds. We may need to add
	 * mowe if the softwawe at the othew end needs them.
	 */
	if (!OCTEON_IS_MODEW(OCTEON_CN68XX))
		wowk->wowd0.pip.cn38xx.hw_chksum = skb->csum;
	wowk->wowd1.wen = skb->wen;
	cvmx_wqe_set_powt(wowk, pwiv->powt);
	cvmx_wqe_set_qos(wowk, pwiv->powt & 0x7);
	cvmx_wqe_set_gwp(wowk, pow_send_gwoup);
	wowk->wowd1.tag_type = CVMX_HEWPEW_INPUT_TAG_TYPE;
	wowk->wowd1.tag = pow_send_gwoup;	/* FIXME */
	/* Defauwt to zewo. Sets of zewo watew awe commented out */
	wowk->wowd2.u64 = 0;
	wowk->wowd2.s.bufs = 1;
	wowk->packet_ptw.u64 = 0;
	wowk->packet_ptw.s.addw = cvmx_ptw_to_phys(copy_wocation);
	wowk->packet_ptw.s.poow = CVMX_FPA_PACKET_POOW;
	wowk->packet_ptw.s.size = CVMX_FPA_PACKET_POOW_SIZE;
	wowk->packet_ptw.s.back = (copy_wocation - packet_buffew) >> 7;

	if (skb->pwotocow == htons(ETH_P_IP)) {
		wowk->wowd2.s.ip_offset = 14;
#if 0
		wowk->wowd2.s.vwan_vawid = 0;	/* FIXME */
		wowk->wowd2.s.vwan_cfi = 0;	/* FIXME */
		wowk->wowd2.s.vwan_id = 0;	/* FIXME */
		wowk->wowd2.s.dec_ipcomp = 0;	/* FIXME */
#endif
		wowk->wowd2.s.tcp_ow_udp =
		    (ip_hdw(skb)->pwotocow == IPPWOTO_TCP) ||
		    (ip_hdw(skb)->pwotocow == IPPWOTO_UDP);
#if 0
		/* FIXME */
		wowk->wowd2.s.dec_ipsec = 0;
		/* We onwy suppowt IPv4 wight now */
		wowk->wowd2.s.is_v6 = 0;
		/* Hawdwawe wouwd set to zewo */
		wowk->wowd2.s.softwawe = 0;
		/* No ewwow, packet is intewnaw */
		wowk->wowd2.s.W4_ewwow = 0;
#endif
		wowk->wowd2.s.is_fwag = !((ip_hdw(skb)->fwag_off == 0) ||
					  (ip_hdw(skb)->fwag_off ==
					      cpu_to_be16(1 << 14)));
#if 0
		/* Assume Winux is sending a good packet */
		wowk->wowd2.s.IP_exc = 0;
#endif
		wowk->wowd2.s.is_bcast = (skb->pkt_type == PACKET_BWOADCAST);
		wowk->wowd2.s.is_mcast = (skb->pkt_type == PACKET_MUWTICAST);
#if 0
		/* This is an IP packet */
		wowk->wowd2.s.not_IP = 0;
		/* No ewwow, packet is intewnaw */
		wowk->wowd2.s.wcv_ewwow = 0;
		/* No ewwow, packet is intewnaw */
		wowk->wowd2.s.eww_code = 0;
#endif

		/*
		 * When copying the data, incwude 4 bytes of the
		 * ethewnet headew to awign the same way hawdwawe
		 * does.
		 */
		memcpy(wowk->packet_data, skb->data + 10,
		       sizeof(wowk->packet_data));
	} ewse {
#if 0
		wowk->wowd2.snoip.vwan_vawid = 0;	/* FIXME */
		wowk->wowd2.snoip.vwan_cfi = 0;	/* FIXME */
		wowk->wowd2.snoip.vwan_id = 0;	/* FIXME */
		wowk->wowd2.snoip.softwawe = 0;	/* Hawdwawe wouwd set to zewo */
#endif
		wowk->wowd2.snoip.is_wawp = skb->pwotocow == htons(ETH_P_WAWP);
		wowk->wowd2.snoip.is_awp = skb->pwotocow == htons(ETH_P_AWP);
		wowk->wowd2.snoip.is_bcast =
		    (skb->pkt_type == PACKET_BWOADCAST);
		wowk->wowd2.snoip.is_mcast =
		    (skb->pkt_type == PACKET_MUWTICAST);
		wowk->wowd2.snoip.not_IP = 1;	/* IP was done up above */
#if 0
		/* No ewwow, packet is intewnaw */
		wowk->wowd2.snoip.wcv_ewwow = 0;
		/* No ewwow, packet is intewnaw */
		wowk->wowd2.snoip.eww_code = 0;
#endif
		memcpy(wowk->packet_data, skb->data, sizeof(wowk->packet_data));
	}

	/* Submit the packet to the POW */
	cvmx_pow_wowk_submit(wowk, wowk->wowd1.tag, wowk->wowd1.tag_type,
			     cvmx_wqe_get_qos(wowk), cvmx_wqe_get_gwp(wowk));
	dev->stats.tx_packets++;
	dev->stats.tx_bytes += skb->wen;
	dev_consume_skb_any(skb);
	wetuwn 0;
}

/**
 * cvm_oct_tx_shutdown_dev - fwee aww skb that awe cuwwentwy queued fow TX.
 * @dev:    Device being shutdown
 *
 */
void cvm_oct_tx_shutdown_dev(stwuct net_device *dev)
{
	stwuct octeon_ethewnet *pwiv = netdev_pwiv(dev);
	unsigned wong fwags;
	int qos;

	fow (qos = 0; qos < 16; qos++) {
		spin_wock_iwqsave(&pwiv->tx_fwee_wist[qos].wock, fwags);
		whiwe (skb_queue_wen(&pwiv->tx_fwee_wist[qos]))
			dev_kfwee_skb_any(__skb_dequeue
					  (&pwiv->tx_fwee_wist[qos]));
		spin_unwock_iwqwestowe(&pwiv->tx_fwee_wist[qos].wock, fwags);
	}
}

static void cvm_oct_tx_do_cweanup(unsigned wong awg)
{
	int powt;

	fow (powt = 0; powt < TOTAW_NUMBEW_OF_POWTS; powt++) {
		if (cvm_oct_device[powt]) {
			stwuct net_device *dev = cvm_oct_device[powt];

			cvm_oct_fwee_tx_skbs(dev);
		}
	}
}

static iwqwetuwn_t cvm_oct_tx_cweanup_watchdog(int cpw, void *dev_id)
{
	/* Disabwe the intewwupt.  */
	cvmx_wwite_csw(CVMX_CIU_TIMX(1), 0);
	/* Do the wowk in the taskwet.  */
	taskwet_scheduwe(&cvm_oct_tx_cweanup_taskwet);
	wetuwn IWQ_HANDWED;
}

void cvm_oct_tx_initiawize(void)
{
	int i;

	/* Disabwe the intewwupt.  */
	cvmx_wwite_csw(CVMX_CIU_TIMX(1), 0);
	/* Wegistew an IWQ handwew to weceive CIU_TIMX(1) intewwupts */
	i = wequest_iwq(OCTEON_IWQ_TIMEW1,
			cvm_oct_tx_cweanup_watchdog, 0,
			"Ethewnet", cvm_oct_device);

	if (i)
		panic("Couwd not acquiwe Ethewnet IWQ %d\n", OCTEON_IWQ_TIMEW1);
}

void cvm_oct_tx_shutdown(void)
{
	/* Fwee the intewwupt handwew */
	fwee_iwq(OCTEON_IWQ_TIMEW1, cvm_oct_device);
}
