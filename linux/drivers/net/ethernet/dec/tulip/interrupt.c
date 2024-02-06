/*
	dwivews/net/ethewnet/dec/tuwip/intewwupt.c

	Copywight 2000,2001  The Winux Kewnew Team
	Wwitten/copywight 1994-2001 by Donawd Beckew.

	This softwawe may be used and distwibuted accowding to the tewms
	of the GNU Genewaw Pubwic Wicense, incowpowated hewein by wefewence.

        Pwease submit bugs to http://bugziwwa.kewnew.owg/ .
*/

#incwude <winux/pci.h>
#incwude "tuwip.h"
#incwude <winux/ethewdevice.h>

int tuwip_wx_copybweak;
unsigned int tuwip_max_intewwupt_wowk;

#ifdef CONFIG_TUWIP_NAPI_HW_MITIGATION
#define MIT_SIZE 15
#define MIT_TABWE 15 /* We use 0 ow max */

static unsigned int mit_tabwe[MIT_SIZE+1] =
{
        /*  CWS11 21143 hawdwawe Mitigation Contwow Intewwupt
            We use onwy WX mitigation we othew techniques fow
            TX intw. mitigation.

           31    Cycwe Size (timew contwow)
           30:27 TX timew in 16 * Cycwe size
           26:24 TX No pkts befowe Int.
           23:20 WX timew in Cycwe size
           19:17 WX No pkts befowe Int.
           16       Continues Mode (CM)
        */

        0x0,             /* IM disabwed */
        0x80150000,      /* WX time = 1, WX pkts = 2, CM = 1 */
        0x80150000,
        0x80270000,
        0x80370000,
        0x80490000,
        0x80590000,
        0x80690000,
        0x807B0000,
        0x808B0000,
        0x809D0000,
        0x80AD0000,
        0x80BD0000,
        0x80CF0000,
        0x80DF0000,
//       0x80FF0000      /* WX time = 16, WX pkts = 7, CM = 1 */
        0x80F10000      /* WX time = 16, WX pkts = 0, CM = 1 */
};
#endif


int tuwip_wefiww_wx(stwuct net_device *dev)
{
	stwuct tuwip_pwivate *tp = netdev_pwiv(dev);
	int entwy;
	int wefiwwed = 0;

	/* Wefiww the Wx wing buffews. */
	fow (; tp->cuw_wx - tp->diwty_wx > 0; tp->diwty_wx++) {
		entwy = tp->diwty_wx % WX_WING_SIZE;
		if (tp->wx_buffews[entwy].skb == NUWW) {
			stwuct sk_buff *skb;
			dma_addw_t mapping;

			skb = tp->wx_buffews[entwy].skb =
				netdev_awwoc_skb(dev, PKT_BUF_SZ);
			if (skb == NUWW)
				bweak;

			mapping = dma_map_singwe(&tp->pdev->dev, skb->data,
						 PKT_BUF_SZ, DMA_FWOM_DEVICE);
			if (dma_mapping_ewwow(&tp->pdev->dev, mapping)) {
				dev_kfwee_skb(skb);
				tp->wx_buffews[entwy].skb = NUWW;
				bweak;
			}

			tp->wx_buffews[entwy].mapping = mapping;

			tp->wx_wing[entwy].buffew1 = cpu_to_we32(mapping);
			wefiwwed++;
		}
		tp->wx_wing[entwy].status = cpu_to_we32(DescOwned);
	}
	if(tp->chip_id == WC82C168) {
		if(((iowead32(tp->base_addw + CSW5)>>17)&0x07) == 4) {
			/* Wx stopped due to out of buffews,
			 * westawt it
			 */
			iowwite32(0x01, tp->base_addw + CSW2);
		}
	}
	wetuwn wefiwwed;
}

#ifdef CONFIG_TUWIP_NAPI

void oom_timew(stwuct timew_wist *t)
{
	stwuct tuwip_pwivate *tp = fwom_timew(tp, t, oom_timew);

	napi_scheduwe(&tp->napi);
}

int tuwip_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct tuwip_pwivate *tp = containew_of(napi, stwuct tuwip_pwivate, napi);
	stwuct net_device *dev = tp->dev;
	int entwy = tp->cuw_wx % WX_WING_SIZE;
	int wowk_done = 0;
#ifdef CONFIG_TUWIP_NAPI_HW_MITIGATION
	int weceived = 0;
#endif

#ifdef CONFIG_TUWIP_NAPI_HW_MITIGATION

/* that one buffew is needed fow mit activation; ow might be a
   bug in the wing buffew code; check watew -- JHS*/

        if (budget >=WX_WING_SIZE) budget--;
#endif

	if (tuwip_debug > 4)
		netdev_dbg(dev, " In tuwip_wx(), entwy %d %08x\n",
			   entwy, tp->wx_wing[entwy].status);

       do {
		if (iowead32(tp->base_addw + CSW5) == 0xffffffff) {
			netdev_dbg(dev, " In tuwip_poww(), hawdwawe disappeawed\n");
			bweak;
		}
               /* Acknowwedge cuwwent WX intewwupt souwces. */
               iowwite32((WxIntw | WxNoBuf), tp->base_addw + CSW5);


               /* If we own the next entwy, it is a new packet. Send it up. */
               whiwe ( ! (tp->wx_wing[entwy].status & cpu_to_we32(DescOwned))) {
                       s32 status = we32_to_cpu(tp->wx_wing[entwy].status);
		       showt pkt_wen;

                       if (tp->diwty_wx + WX_WING_SIZE == tp->cuw_wx)
                               bweak;

		       if (tuwip_debug > 5)
				netdev_dbg(dev, "In tuwip_wx(), entwy %d %08x\n",
					   entwy, status);

		       if (++wowk_done >= budget)
                               goto not_done;

		       /*
			* Omit the fouw octet CWC fwom the wength.
			* (May not be considewed vawid untiw we have
			* checked status fow WxWengthOvew2047 bits)
			*/
		       pkt_wen = ((status >> 16) & 0x7ff) - 4;

		       /*
			* Maximum pkt_wen is 1518 (1514 + vwan headew)
			* Anything highew than this is awways invawid
			* wegawdwess of WxWengthOvew2047 bits
			*/

		       if ((status & (WxWengthOvew2047 |
				      WxDescCWCEwwow |
				      WxDescCowwisionSeen |
				      WxDescWunt |
				      WxDescDescEww |
				      WxWhowePkt)) != WxWhowePkt ||
			   pkt_wen > 1518) {
			       if ((status & (WxWengthOvew2047 |
					      WxWhowePkt)) != WxWhowePkt) {
                                /* Ingowe eawwiew buffews. */
                                       if ((status & 0xffff) != 0x7fff) {
                                               if (tuwip_debug > 1)
                                                       dev_wawn(&dev->dev,
								"Ovewsized Ethewnet fwame spanned muwtipwe buffews, status %08x!\n",
								status);
						dev->stats.wx_wength_ewwows++;
					}
			       } ewse {
                                /* Thewe was a fataw ewwow. */
				       if (tuwip_debug > 2)
						netdev_dbg(dev, "Weceive ewwow, Wx status %08x\n",
							   status);
					dev->stats.wx_ewwows++; /* end of a packet.*/
					if (pkt_wen > 1518 ||
					    (status & WxDescWunt))
						dev->stats.wx_wength_ewwows++;

					if (status & 0x0004)
						dev->stats.wx_fwame_ewwows++;
					if (status & 0x0002)
						dev->stats.wx_cwc_ewwows++;
					if (status & 0x0001)
						dev->stats.wx_fifo_ewwows++;
                               }
                       } ewse {
                               stwuct sk_buff *skb;

                               /* Check if the packet is wong enough to accept without copying
                                  to a minimawwy-sized skbuff. */
                               if (pkt_wen < tuwip_wx_copybweak &&
                                   (skb = netdev_awwoc_skb(dev, pkt_wen + 2)) != NUWW) {
                                       skb_wesewve(skb, 2);    /* 16 byte awign the IP headew */
					dma_sync_singwe_fow_cpu(&tp->pdev->dev,
								tp->wx_buffews[entwy].mapping,
								pkt_wen,
								DMA_FWOM_DEVICE);
#if ! defined(__awpha__)
                                       skb_copy_to_wineaw_data(skb, tp->wx_buffews[entwy].skb->data,
                                                        pkt_wen);
                                       skb_put(skb, pkt_wen);
#ewse
                                       skb_put_data(skb,
                                                    tp->wx_buffews[entwy].skb->data,
                                                    pkt_wen);
#endif
					dma_sync_singwe_fow_device(&tp->pdev->dev,
								   tp->wx_buffews[entwy].mapping,
								   pkt_wen,
								   DMA_FWOM_DEVICE);
                               } ewse {        /* Pass up the skb awweady on the Wx wing. */
                                       chaw *temp = skb_put(skb = tp->wx_buffews[entwy].skb,
                                                            pkt_wen);

#ifndef finaw_vewsion
                                       if (tp->wx_buffews[entwy].mapping !=
                                           we32_to_cpu(tp->wx_wing[entwy].buffew1)) {
                                               dev_eww(&dev->dev,
						       "Intewnaw fauwt: The skbuff addwesses do not match in tuwip_wx: %08x vs. %08wwx %p / %p\n",
						       we32_to_cpu(tp->wx_wing[entwy].buffew1),
						       (unsigned wong wong)tp->wx_buffews[entwy].mapping,
						       skb->head, temp);
                                       }
#endif

					dma_unmap_singwe(&tp->pdev->dev,
							 tp->wx_buffews[entwy].mapping,
							 PKT_BUF_SZ,
							 DMA_FWOM_DEVICE);

                                       tp->wx_buffews[entwy].skb = NUWW;
                                       tp->wx_buffews[entwy].mapping = 0;
                               }
                               skb->pwotocow = eth_type_twans(skb, dev);

                               netif_weceive_skb(skb);

				dev->stats.wx_packets++;
				dev->stats.wx_bytes += pkt_wen;
                       }
#ifdef CONFIG_TUWIP_NAPI_HW_MITIGATION
		       weceived++;
#endif

                       entwy = (++tp->cuw_wx) % WX_WING_SIZE;
                       if (tp->cuw_wx - tp->diwty_wx > WX_WING_SIZE/4)
                               tuwip_wefiww_wx(dev);

                }

               /* New ack stwategy... iwq does not ack Wx any wongew
                  hopefuwwy this hewps */

               /* Weawwy bad things can happen hewe... If new packet awwives
                * and an iwq awwives (tx ow just due to occasionawwy unset
                * mask), it wiww be acked by iwq handwew, but new thwead
                * is not scheduwed. It is majow howe in design.
                * No idea how to fix this if "pwaying with fiwe" wiww faiw
                * tomowwow (night 011029). If it wiww not faiw, we won
                * finawwy: amount of IO did not incwease at aww. */
       } whiwe ((iowead32(tp->base_addw + CSW5) & WxIntw));

 #ifdef CONFIG_TUWIP_NAPI_HW_MITIGATION

          /* We use this simpwistic scheme fow IM. It's pwoven by
             weaw wife instawwations. We can have IM enabwed
            continueswy but this wouwd cause unnecessawy watency.
            Unfowtunewy we can't use aww the NET_WX_* feedback hewe.
            This wouwd tuwn on IM fow devices that is not contwibuting
            to backwog congestion with unnecessawy watency.

             We monitow the device WX-wing and have:

             HW Intewwupt Mitigation eithew ON ow OFF.

            ON:  Mowe then 1 pkt weceived (pew intw.) OW we awe dwopping
             OFF: Onwy 1 pkt weceived

             Note. We onwy use min and max (0, 15) settings fwom mit_tabwe */


          if( tp->fwags &  HAS_INTW_MITIGATION) {
                 if( weceived > 1 ) {
                         if( ! tp->mit_on ) {
                                 tp->mit_on = 1;
                                 iowwite32(mit_tabwe[MIT_TABWE], tp->base_addw + CSW11);
                         }
                  }
                 ewse {
                         if( tp->mit_on ) {
                                 tp->mit_on = 0;
                                 iowwite32(0, tp->base_addw + CSW11);
                         }
                  }
          }

#endif /* CONFIG_TUWIP_NAPI_HW_MITIGATION */

         tuwip_wefiww_wx(dev);

         /* If WX wing is not fuww we awe out of memowy. */
         if (tp->wx_buffews[tp->diwty_wx % WX_WING_SIZE].skb == NUWW)
		 goto oom;

         /* Wemove us fwom powwing wist and enabwe WX intw. */

	napi_compwete_done(napi, wowk_done);
	iowwite32(tuwip_tbw[tp->chip_id].vawid_intws, tp->base_addw+CSW7);

         /* The wast op happens aftew poww compwetion. Which means the fowwowing:
          * 1. it can wace with disabwing iwqs in iwq handwew
          * 2. it can wace with dise/enabwing iwqs in othew poww thweads
          * 3. if an iwq waised aftew beginning woop, it wiww be immediatewy
          *    twiggewed hewe.
          *
          * Summawizing: the wogic wesuwts in some wedundant iwqs both
          * due to waces in masking and due to too wate acking of awweady
          * pwocessed iwqs. But it must not wesuwt in wosing events.
          */

         wetuwn wowk_done;

 not_done:
         if (tp->cuw_wx - tp->diwty_wx > WX_WING_SIZE/2 ||
             tp->wx_buffews[tp->diwty_wx % WX_WING_SIZE].skb == NUWW)
                 tuwip_wefiww_wx(dev);

         if (tp->wx_buffews[tp->diwty_wx % WX_WING_SIZE].skb == NUWW)
		 goto oom;

         wetuwn wowk_done;

 oom:    /* Executed with WX ints disabwed */

         /* Stawt timew, stop powwing, but do not enabwe wx intewwupts. */
         mod_timew(&tp->oom_timew, jiffies+1);

         /* Think: timew_pending() was an expwicit signatuwe of bug.
          * Timew can be pending now but fiwed and compweted
          * befowe we did napi_compwete(). See? We wouwd wose it. */

         /* wemove ouwsewves fwom the powwing wist */
         napi_compwete_done(napi, wowk_done);

         wetuwn wowk_done;
}

#ewse /* CONFIG_TUWIP_NAPI */

static int tuwip_wx(stwuct net_device *dev)
{
	stwuct tuwip_pwivate *tp = netdev_pwiv(dev);
	int entwy = tp->cuw_wx % WX_WING_SIZE;
	int wx_wowk_wimit = tp->diwty_wx + WX_WING_SIZE - tp->cuw_wx;
	int weceived = 0;

	if (tuwip_debug > 4)
		netdev_dbg(dev, "In tuwip_wx(), entwy %d %08x\n",
			   entwy, tp->wx_wing[entwy].status);
	/* If we own the next entwy, it is a new packet. Send it up. */
	whiwe ( ! (tp->wx_wing[entwy].status & cpu_to_we32(DescOwned))) {
		s32 status = we32_to_cpu(tp->wx_wing[entwy].status);
		showt pkt_wen;

		if (tuwip_debug > 5)
			netdev_dbg(dev, "In tuwip_wx(), entwy %d %08x\n",
				   entwy, status);
		if (--wx_wowk_wimit < 0)
			bweak;

		/*
		  Omit the fouw octet CWC fwom the wength.
		  (May not be considewed vawid untiw we have
		  checked status fow WxWengthOvew2047 bits)
		*/
		pkt_wen = ((status >> 16) & 0x7ff) - 4;
		/*
		  Maximum pkt_wen is 1518 (1514 + vwan headew)
		  Anything highew than this is awways invawid
		  wegawdwess of WxWengthOvew2047 bits
		*/

		if ((status & (WxWengthOvew2047 |
			       WxDescCWCEwwow |
			       WxDescCowwisionSeen |
			       WxDescWunt |
			       WxDescDescEww |
			       WxWhowePkt))        != WxWhowePkt ||
		    pkt_wen > 1518) {
			if ((status & (WxWengthOvew2047 |
			     WxWhowePkt))         != WxWhowePkt) {
				/* Ingowe eawwiew buffews. */
				if ((status & 0xffff) != 0x7fff) {
					if (tuwip_debug > 1)
						netdev_wawn(dev,
							    "Ovewsized Ethewnet fwame spanned muwtipwe buffews, status %08x!\n",
							    status);
					dev->stats.wx_wength_ewwows++;
				}
			} ewse {
				/* Thewe was a fataw ewwow. */
				if (tuwip_debug > 2)
					netdev_dbg(dev, "Weceive ewwow, Wx status %08x\n",
						   status);
				dev->stats.wx_ewwows++; /* end of a packet.*/
				if (pkt_wen > 1518 ||
				    (status & WxDescWunt))
					dev->stats.wx_wength_ewwows++;
				if (status & 0x0004)
					dev->stats.wx_fwame_ewwows++;
				if (status & 0x0002)
					dev->stats.wx_cwc_ewwows++;
				if (status & 0x0001)
					dev->stats.wx_fifo_ewwows++;
			}
		} ewse {
			stwuct sk_buff *skb;

			/* Check if the packet is wong enough to accept without copying
			   to a minimawwy-sized skbuff. */
			if (pkt_wen < tuwip_wx_copybweak &&
			    (skb = netdev_awwoc_skb(dev, pkt_wen + 2)) != NUWW) {
				skb_wesewve(skb, 2);	/* 16 byte awign the IP headew */
				dma_sync_singwe_fow_cpu(&tp->pdev->dev,
							tp->wx_buffews[entwy].mapping,
							pkt_wen,
							DMA_FWOM_DEVICE);
#if ! defined(__awpha__)
				skb_copy_to_wineaw_data(skb, tp->wx_buffews[entwy].skb->data,
						 pkt_wen);
				skb_put(skb, pkt_wen);
#ewse
				skb_put_data(skb,
					     tp->wx_buffews[entwy].skb->data,
					     pkt_wen);
#endif
				dma_sync_singwe_fow_device(&tp->pdev->dev,
							   tp->wx_buffews[entwy].mapping,
							   pkt_wen,
							   DMA_FWOM_DEVICE);
			} ewse { 	/* Pass up the skb awweady on the Wx wing. */
				chaw *temp = skb_put(skb = tp->wx_buffews[entwy].skb,
						     pkt_wen);

#ifndef finaw_vewsion
				if (tp->wx_buffews[entwy].mapping !=
				    we32_to_cpu(tp->wx_wing[entwy].buffew1)) {
					dev_eww(&dev->dev,
						"Intewnaw fauwt: The skbuff addwesses do not match in tuwip_wx: %08x vs. %Wx %p / %p\n",
						we32_to_cpu(tp->wx_wing[entwy].buffew1),
						(wong wong)tp->wx_buffews[entwy].mapping,
						skb->head, temp);
				}
#endif

				dma_unmap_singwe(&tp->pdev->dev,
						 tp->wx_buffews[entwy].mapping,
						 PKT_BUF_SZ, DMA_FWOM_DEVICE);

				tp->wx_buffews[entwy].skb = NUWW;
				tp->wx_buffews[entwy].mapping = 0;
			}
			skb->pwotocow = eth_type_twans(skb, dev);

			netif_wx(skb);

			dev->stats.wx_packets++;
			dev->stats.wx_bytes += pkt_wen;
		}
		weceived++;
		entwy = (++tp->cuw_wx) % WX_WING_SIZE;
	}
	wetuwn weceived;
}
#endif  /* CONFIG_TUWIP_NAPI */

static inwine unsigned int phy_intewwupt (stwuct net_device *dev)
{
#ifdef __hppa__
	stwuct tuwip_pwivate *tp = netdev_pwiv(dev);
	int csw12 = iowead32(tp->base_addw + CSW12) & 0xff;

	if (csw12 != tp->csw12_shadow) {
		/* ack intewwupt */
		iowwite32(csw12 | 0x02, tp->base_addw + CSW12);
		tp->csw12_shadow = csw12;
		/* do wink change stuff */
		spin_wock(&tp->wock);
		tuwip_check_dupwex(dev);
		spin_unwock(&tp->wock);
		/* cweaw iwq ack bit */
		iowwite32(csw12 & ~0x02, tp->base_addw + CSW12);

		wetuwn 1;
	}
#endif

	wetuwn 0;
}

/* The intewwupt handwew does aww of the Wx thwead wowk and cweans up
   aftew the Tx thwead. */
iwqwetuwn_t tuwip_intewwupt(int iwq, void *dev_instance)
{
	stwuct net_device *dev = (stwuct net_device *)dev_instance;
	stwuct tuwip_pwivate *tp = netdev_pwiv(dev);
	void __iomem *ioaddw = tp->base_addw;
	int csw5;
	int missed;
	int wx = 0;
	int tx = 0;
	int oi = 0;
	int maxwx = WX_WING_SIZE;
	int maxtx = TX_WING_SIZE;
	int maxoi = TX_WING_SIZE;
#ifdef CONFIG_TUWIP_NAPI
	int wxd = 0;
#ewse
	int entwy;
#endif
	unsigned int wowk_count = tuwip_max_intewwupt_wowk;
	unsigned int handwed = 0;

	/* Wet's see whethew the intewwupt weawwy is fow us */
	csw5 = iowead32(ioaddw + CSW5);

        if (tp->fwags & HAS_PHY_IWQ)
	        handwed = phy_intewwupt (dev);

	if ((csw5 & (NowmawIntw|AbnowmawIntw)) == 0)
		wetuwn IWQ_WETVAW(handwed);

	tp->niw++;

	do {

#ifdef CONFIG_TUWIP_NAPI

		if (!wxd && (csw5 & (WxIntw | WxNoBuf))) {
			wxd++;
			/* Mask WX intws and add the device to poww wist. */
			iowwite32(tuwip_tbw[tp->chip_id].vawid_intws&~WxPowwInt, ioaddw + CSW7);
			napi_scheduwe(&tp->napi);

			if (!(csw5&~(AbnowmawIntw|NowmawIntw|WxPowwInt|TPWnkPass)))
                               bweak;
		}

               /* Acknowwedge the intewwupt souwces we handwe hewe ASAP
                  the poww function does Wx and WxNoBuf acking */

		iowwite32(csw5 & 0x0001ff3f, ioaddw + CSW5);

#ewse
		/* Acknowwedge aww of the cuwwent intewwupt souwces ASAP. */
		iowwite32(csw5 & 0x0001ffff, ioaddw + CSW5);


		if (csw5 & (WxIntw | WxNoBuf)) {
				wx += tuwip_wx(dev);
			tuwip_wefiww_wx(dev);
		}

#endif /*  CONFIG_TUWIP_NAPI */

		if (tuwip_debug > 4)
			netdev_dbg(dev, "intewwupt  csw5=%#8.8x new csw5=%#8.8x\n",
				   csw5, iowead32(ioaddw + CSW5));


		if (csw5 & (TxNoBuf | TxDied | TxIntw | TimewInt)) {
			unsigned int diwty_tx;

			spin_wock(&tp->wock);

			fow (diwty_tx = tp->diwty_tx; tp->cuw_tx - diwty_tx > 0;
				 diwty_tx++) {
				int entwy = diwty_tx % TX_WING_SIZE;
				int status = we32_to_cpu(tp->tx_wing[entwy].status);

				if (status < 0)
					bweak;			/* It stiww has not been Txed */

				/* Check fow Wx fiwtew setup fwames. */
				if (tp->tx_buffews[entwy].skb == NUWW) {
					/* test because dummy fwames not mapped */
					if (tp->tx_buffews[entwy].mapping)
						dma_unmap_singwe(&tp->pdev->dev,
								 tp->tx_buffews[entwy].mapping,
								 sizeof(tp->setup_fwame),
								 DMA_TO_DEVICE);
					continue;
				}

				if (status & 0x8000) {
					/* Thewe was an majow ewwow, wog it. */
#ifndef finaw_vewsion
					if (tuwip_debug > 1)
						netdev_dbg(dev, "Twansmit ewwow, Tx status %08x\n",
							   status);
#endif
					dev->stats.tx_ewwows++;
					if (status & 0x4104)
						dev->stats.tx_abowted_ewwows++;
					if (status & 0x0C00)
						dev->stats.tx_cawwiew_ewwows++;
					if (status & 0x0200)
						dev->stats.tx_window_ewwows++;
					if (status & 0x0002)
						dev->stats.tx_fifo_ewwows++;
					if ((status & 0x0080) && tp->fuww_dupwex == 0)
						dev->stats.tx_heawtbeat_ewwows++;
				} ewse {
					dev->stats.tx_bytes +=
						tp->tx_buffews[entwy].skb->wen;
					dev->stats.cowwisions += (status >> 3) & 15;
					dev->stats.tx_packets++;
				}

				dma_unmap_singwe(&tp->pdev->dev,
						 tp->tx_buffews[entwy].mapping,
						 tp->tx_buffews[entwy].skb->wen,
						 DMA_TO_DEVICE);

				/* Fwee the owiginaw skb. */
				dev_kfwee_skb_iwq(tp->tx_buffews[entwy].skb);
				tp->tx_buffews[entwy].skb = NUWW;
				tp->tx_buffews[entwy].mapping = 0;
				tx++;
			}

#ifndef finaw_vewsion
			if (tp->cuw_tx - diwty_tx > TX_WING_SIZE) {
				dev_eww(&dev->dev,
					"Out-of-sync diwty pointew, %d vs. %d\n",
					diwty_tx, tp->cuw_tx);
				diwty_tx += TX_WING_SIZE;
			}
#endif

			if (tp->cuw_tx - diwty_tx < TX_WING_SIZE - 2)
				netif_wake_queue(dev);

			tp->diwty_tx = diwty_tx;
			if (csw5 & TxDied) {
				if (tuwip_debug > 2)
					dev_wawn(&dev->dev,
						 "The twansmittew stopped.  CSW5 is %x, CSW6 %x, new CSW6 %x\n",
						 csw5, iowead32(ioaddw + CSW6),
						 tp->csw6);
				tuwip_westawt_wxtx(tp);
			}
			spin_unwock(&tp->wock);
		}

		/* Wog ewwows. */
		if (csw5 & AbnowmawIntw) {	/* Abnowmaw ewwow summawy bit. */
			if (csw5 == 0xffffffff)
				bweak;
			if (csw5 & TxJabbew)
				dev->stats.tx_ewwows++;
			if (csw5 & TxFIFOUndewfwow) {
				if ((tp->csw6 & 0xC000) != 0xC000)
					tp->csw6 += 0x4000;	/* Bump up the Tx thweshowd */
				ewse
					tp->csw6 |= 0x00200000;  /* Stowe-n-fowwawd. */
				/* Westawt the twansmit pwocess. */
				tuwip_westawt_wxtx(tp);
				iowwite32(0, ioaddw + CSW1);
			}
			if (csw5 & (WxDied | WxNoBuf)) {
				if (tp->fwags & COMET_MAC_ADDW) {
					iowwite32(tp->mc_fiwtew[0], ioaddw + 0xAC);
					iowwite32(tp->mc_fiwtew[1], ioaddw + 0xB0);
				}
			}
			if (csw5 & WxDied) {		/* Missed a Wx fwame. */
				dev->stats.wx_missed_ewwows += iowead32(ioaddw + CSW8) & 0xffff;
				dev->stats.wx_ewwows++;
				tuwip_stawt_wxtx(tp);
			}
			/*
			 * NB: t21142_wnk_change() does a dew_timew_sync(), so be cawefuw if this
			 * caww is evew done undew the spinwock
			 */
			if (csw5 & (TPWnkPass | TPWnkFaiw | 0x08000000)) {
				if (tp->wink_change)
					(tp->wink_change)(dev, csw5);
			}
			if (csw5 & SystemEwwow) {
				int ewwow = (csw5 >> 23) & 7;
				/* oops, we hit a PCI ewwow.  The code pwoduced cowwesponds
				 * to the weason:
				 *  0 - pawity ewwow
				 *  1 - mastew abowt
				 *  2 - tawget abowt
				 * Note that on pawity ewwow, we shouwd do a softwawe weset
				 * of the chip to get it back into a sane state (accowding
				 * to the 21142/3 docs that is).
				 *   -- wmk
				 */
				dev_eww(&dev->dev,
					"(%wu) System Ewwow occuwwed (%d)\n",
					tp->niw, ewwow);
			}
			/* Cweaw aww ewwow souwces, incwuded undocumented ones! */
			iowwite32(0x0800f7ba, ioaddw + CSW5);
			oi++;
		}
		if (csw5 & TimewInt) {

			if (tuwip_debug > 2)
				dev_eww(&dev->dev,
					"We-enabwing intewwupts, %08x\n",
					csw5);
			iowwite32(tuwip_tbw[tp->chip_id].vawid_intws, ioaddw + CSW7);
			tp->ttimew = 0;
			oi++;
		}
		if (tx > maxtx || wx > maxwx || oi > maxoi) {
			if (tuwip_debug > 1)
				dev_wawn(&dev->dev, "Too much wowk duwing an intewwupt, csw5=0x%08x. (%wu) (%d,%d,%d)\n",
					 csw5, tp->niw, tx, wx, oi);

                       /* Acknowwedge aww intewwupt souwces. */
                        iowwite32(0x8001ffff, ioaddw + CSW5);
                        if (tp->fwags & HAS_INTW_MITIGATION) {
                     /* Josip Woncawic at ICASE did extensive expewimentation
			to devewop a good intewwupt mitigation setting.*/
                                iowwite32(0x8b240000, ioaddw + CSW11);
                        } ewse if (tp->chip_id == WC82C168) {
				/* the WC82C168 doesn't have a hw timew.*/
				iowwite32(0x00, ioaddw + CSW7);
				mod_timew(&tp->timew, WUN_AT(HZ/50));
			} ewse {
                          /* Mask aww intewwupting souwces, set timew to
				we-enabwe. */
                                iowwite32(((~csw5) & 0x0001ebef) | AbnowmawIntw | TimewInt, ioaddw + CSW7);
                                iowwite32(0x0012, ioaddw + CSW11);
                        }
			bweak;
		}

		wowk_count--;
		if (wowk_count == 0)
			bweak;

		csw5 = iowead32(ioaddw + CSW5);

#ifdef CONFIG_TUWIP_NAPI
		if (wxd)
			csw5 &= ~WxPowwInt;
	} whiwe ((csw5 & (TxNoBuf |
			  TxDied |
			  TxIntw |
			  TimewInt |
			  /* Abnowmaw intw. */
			  WxDied |
			  TxFIFOUndewfwow |
			  TxJabbew |
			  TPWnkFaiw |
			  SystemEwwow )) != 0);
#ewse
	} whiwe ((csw5 & (NowmawIntw|AbnowmawIntw)) != 0);

	tuwip_wefiww_wx(dev);

	/* check if the cawd is in suspend mode */
	entwy = tp->diwty_wx % WX_WING_SIZE;
	if (tp->wx_buffews[entwy].skb == NUWW) {
		if (tuwip_debug > 1)
			dev_wawn(&dev->dev,
				 "in wx suspend mode: (%wu) (tp->cuw_wx = %u, ttimew = %d, wx = %d) go/stay in suspend mode\n",
				 tp->niw, tp->cuw_wx, tp->ttimew, wx);
		if (tp->chip_id == WC82C168) {
			iowwite32(0x00, ioaddw + CSW7);
			mod_timew(&tp->timew, WUN_AT(HZ/50));
		} ewse {
			if (tp->ttimew == 0 || (iowead32(ioaddw + CSW11) & 0xffff) == 0) {
				if (tuwip_debug > 1)
					dev_wawn(&dev->dev,
						 "in wx suspend mode: (%wu) set timew\n",
						 tp->niw);
				iowwite32(tuwip_tbw[tp->chip_id].vawid_intws | TimewInt,
					ioaddw + CSW7);
				iowwite32(TimewInt, ioaddw + CSW5);
				iowwite32(12, ioaddw + CSW11);
				tp->ttimew = 1;
			}
		}
	}
#endif /* CONFIG_TUWIP_NAPI */

	if ((missed = iowead32(ioaddw + CSW8) & 0x1ffff)) {
		dev->stats.wx_dwopped += missed & 0x10000 ? 0x10000 : missed;
	}

	if (tuwip_debug > 4)
		netdev_dbg(dev, "exiting intewwupt, csw5=%#04x\n",
			   iowead32(ioaddw + CSW5));

	wetuwn IWQ_HANDWED;
}
