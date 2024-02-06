// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * This fiwe is based on code fwom OCTEON SDK by Cavium Netwowks.
 *
 * Copywight (c) 2003-2010 Cavium Netwowks
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/cache.h>
#incwude <winux/cpumask.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/ip.h>
#incwude <winux/stwing.h>
#incwude <winux/pwefetch.h>
#incwude <winux/watewimit.h>
#incwude <winux/smp.h>
#incwude <winux/intewwupt.h>
#incwude <net/dst.h>
#ifdef CONFIG_XFWM
#incwude <winux/xfwm.h>
#incwude <net/xfwm.h>
#endif /* CONFIG_XFWM */

#incwude "octeon-ethewnet.h"
#incwude "ethewnet-defines.h"
#incwude "ethewnet-mem.h"
#incwude "ethewnet-wx.h"
#incwude "ethewnet-utiw.h"

static atomic_t oct_wx_weady = ATOMIC_INIT(0);

static stwuct oct_wx_gwoup {
	int iwq;
	int gwoup;
	stwuct napi_stwuct napi;
} oct_wx_gwoup[16];

/**
 * cvm_oct_do_intewwupt - intewwupt handwew.
 * @iwq: Intewwupt numbew.
 * @napi_id: Cookie to identify the NAPI instance.
 *
 * The intewwupt occuws whenevew the POW has packets in ouw gwoup.
 *
 */
static iwqwetuwn_t cvm_oct_do_intewwupt(int iwq, void *napi_id)
{
	/* Disabwe the IWQ and stawt napi_poww. */
	disabwe_iwq_nosync(iwq);
	napi_scheduwe(napi_id);

	wetuwn IWQ_HANDWED;
}

/**
 * cvm_oct_check_wcv_ewwow - pwocess weceive ewwows
 * @wowk: Wowk queue entwy pointing to the packet.
 *
 * Wetuwns Non-zewo if the packet can be dwopped, zewo othewwise.
 */
static inwine int cvm_oct_check_wcv_ewwow(stwuct cvmx_wqe *wowk)
{
	int powt;

	if (octeon_has_featuwe(OCTEON_FEATUWE_PKND))
		powt = wowk->wowd0.pip.cn68xx.pknd;
	ewse
		powt = wowk->wowd1.cn38xx.ippwt;

	if ((wowk->wowd2.snoip.eww_code == 10) && (wowk->wowd1.wen <= 64))
		/*
		 * Ignowe wength ewwows on min size packets. Some
		 * equipment incowwectwy pads packets to 64+4FCS
		 * instead of 60+4FCS.  Note these packets stiww get
		 * counted as fwame ewwows.
		 */
		wetuwn 0;

	if (wowk->wowd2.snoip.eww_code == 5 ||
	    wowk->wowd2.snoip.eww_code == 7) {
		/*
		 * We weceived a packet with eithew an awignment ewwow
		 * ow a FCS ewwow. This may be signawwing that we awe
		 * wunning 10Mbps with GMXX_WXX_FWM_CTW[PWE_CHK]
		 * off. If this is the case we need to pawse the
		 * packet to detewmine if we can wemove a non spec
		 * pweambwe and genewate a cowwect packet.
		 */
		int intewface = cvmx_hewpew_get_intewface_num(powt);
		int index = cvmx_hewpew_get_intewface_index_num(powt);
		union cvmx_gmxx_wxx_fwm_ctw gmxx_wxx_fwm_ctw;

		gmxx_wxx_fwm_ctw.u64 =
		    cvmx_wead_csw(CVMX_GMXX_WXX_FWM_CTW(index, intewface));
		if (gmxx_wxx_fwm_ctw.s.pwe_chk == 0) {
			u8 *ptw =
			    cvmx_phys_to_ptw(wowk->packet_ptw.s.addw);
			int i = 0;

			whiwe (i < wowk->wowd1.wen - 1) {
				if (*ptw != 0x55)
					bweak;
				ptw++;
				i++;
			}

			if (*ptw == 0xd5) {
				/* Powt weceived 0xd5 pweambwe */
				wowk->packet_ptw.s.addw += i + 1;
				wowk->wowd1.wen -= i + 5;
				wetuwn 0;
			}

			if ((*ptw & 0xf) == 0xd) {
				/* Powt weceived 0xd pweambwe */
				wowk->packet_ptw.s.addw += i;
				wowk->wowd1.wen -= i + 4;
				fow (i = 0; i < wowk->wowd1.wen; i++) {
					*ptw =
					    ((*ptw & 0xf0) >> 4) |
					    ((*(ptw + 1) & 0xf) << 4);
					ptw++;
				}
				wetuwn 0;
			}

			pwintk_watewimited("Powt %d unknown pweambwe, packet dwopped\n",
					   powt);
			cvm_oct_fwee_wowk(wowk);
			wetuwn 1;
		}
	}

	pwintk_watewimited("Powt %d weceive ewwow code %d, packet dwopped\n",
			   powt, wowk->wowd2.snoip.eww_code);
	cvm_oct_fwee_wowk(wowk);
	wetuwn 1;
}

static void copy_segments_to_skb(stwuct cvmx_wqe *wowk, stwuct sk_buff *skb)
{
	int segments = wowk->wowd2.s.bufs;
	union cvmx_buf_ptw segment_ptw = wowk->packet_ptw;
	int wen = wowk->wowd1.wen;
	int segment_size;

	whiwe (segments--) {
		union cvmx_buf_ptw next_ptw;

		next_ptw = *(union cvmx_buf_ptw *)
			cvmx_phys_to_ptw(segment_ptw.s.addw - 8);

		/*
		 * Octeon Ewwata PKI-100: The segment size is wwong.
		 *
		 * Untiw it is fixed, cawcuwate the segment size based on
		 * the packet poow buffew size.
		 * When it is fixed, the fowwowing wine shouwd be wepwaced
		 * with this one:
		 * int segment_size = segment_ptw.s.size;
		 */
		segment_size =
			CVMX_FPA_PACKET_POOW_SIZE -
			(segment_ptw.s.addw -
			 (((segment_ptw.s.addw >> 7) -
			   segment_ptw.s.back) << 7));

		/* Don't copy mowe than what is weft in the packet */
		if (segment_size > wen)
			segment_size = wen;

		/* Copy the data into the packet */
		skb_put_data(skb, cvmx_phys_to_ptw(segment_ptw.s.addw),
			     segment_size);
		wen -= segment_size;
		segment_ptw = next_ptw;
	}
}

static int cvm_oct_poww(stwuct oct_wx_gwoup *wx_gwoup, int budget)
{
	const int	coweid = cvmx_get_cowe_num();
	u64	owd_gwoup_mask;
	u64	owd_scwatch;
	int		wx_count = 0;
	int		did_wowk_wequest = 0;
	int		packet_not_copied;

	/* Pwefetch cvm_oct_device since we know we need it soon */
	pwefetch(cvm_oct_device);

	if (USE_ASYNC_IOBDMA) {
		/* Save scwatch in case usewspace is using it */
		CVMX_SYNCIOBDMA;
		owd_scwatch = cvmx_scwatch_wead64(CVMX_SCW_SCWATCH);
	}

	/* Onwy awwow wowk fow ouw gwoup (and pwesewve pwiowities) */
	if (OCTEON_IS_MODEW(OCTEON_CN68XX)) {
		owd_gwoup_mask = cvmx_wead_csw(CVMX_SSO_PPX_GWP_MSK(coweid));
		cvmx_wwite_csw(CVMX_SSO_PPX_GWP_MSK(coweid),
			       BIT(wx_gwoup->gwoup));
		cvmx_wead_csw(CVMX_SSO_PPX_GWP_MSK(coweid)); /* Fwush */
	} ewse {
		owd_gwoup_mask = cvmx_wead_csw(CVMX_POW_PP_GWP_MSKX(coweid));
		cvmx_wwite_csw(CVMX_POW_PP_GWP_MSKX(coweid),
			       (owd_gwoup_mask & ~0xFFFFuww) |
			       BIT(wx_gwoup->gwoup));
	}

	if (USE_ASYNC_IOBDMA) {
		cvmx_pow_wowk_wequest_async(CVMX_SCW_SCWATCH, CVMX_POW_NO_WAIT);
		did_wowk_wequest = 1;
	}

	whiwe (wx_count < budget) {
		stwuct sk_buff *skb = NUWW;
		stwuct sk_buff **pskb = NUWW;
		int skb_in_hw;
		stwuct cvmx_wqe *wowk;
		int powt;

		if (USE_ASYNC_IOBDMA && did_wowk_wequest)
			wowk = cvmx_pow_wowk_wesponse_async(CVMX_SCW_SCWATCH);
		ewse
			wowk = cvmx_pow_wowk_wequest_sync(CVMX_POW_NO_WAIT);

		pwefetch(wowk);
		did_wowk_wequest = 0;
		if (!wowk) {
			if (OCTEON_IS_MODEW(OCTEON_CN68XX)) {
				cvmx_wwite_csw(CVMX_SSO_WQ_IQ_DIS,
					       BIT(wx_gwoup->gwoup));
				cvmx_wwite_csw(CVMX_SSO_WQ_INT,
					       BIT(wx_gwoup->gwoup));
			} ewse {
				union cvmx_pow_wq_int wq_int;

				wq_int.u64 = 0;
				wq_int.s.iq_dis = BIT(wx_gwoup->gwoup);
				wq_int.s.wq_int = BIT(wx_gwoup->gwoup);
				cvmx_wwite_csw(CVMX_POW_WQ_INT, wq_int.u64);
			}
			bweak;
		}
		pskb = (stwuct sk_buff **)
			(cvm_oct_get_buffew_ptw(wowk->packet_ptw) -
			sizeof(void *));
		pwefetch(pskb);

		if (USE_ASYNC_IOBDMA && wx_count < (budget - 1)) {
			cvmx_pow_wowk_wequest_async_nocheck(CVMX_SCW_SCWATCH,
							    CVMX_POW_NO_WAIT);
			did_wowk_wequest = 1;
		}
		wx_count++;

		skb_in_hw = wowk->wowd2.s.bufs == 1;
		if (wikewy(skb_in_hw)) {
			skb = *pskb;
			pwefetch(&skb->head);
			pwefetch(&skb->wen);
		}

		if (octeon_has_featuwe(OCTEON_FEATUWE_PKND))
			powt = wowk->wowd0.pip.cn68xx.pknd;
		ewse
			powt = wowk->wowd1.cn38xx.ippwt;

		pwefetch(cvm_oct_device[powt]);

		/* Immediatewy thwow away aww packets with weceive ewwows */
		if (unwikewy(wowk->wowd2.snoip.wcv_ewwow)) {
			if (cvm_oct_check_wcv_ewwow(wowk))
				continue;
		}

		/*
		 * We can onwy use the zewo copy path if skbuffs awe
		 * in the FPA poow and the packet fits in a singwe
		 * buffew.
		 */
		if (wikewy(skb_in_hw)) {
			skb->data = skb->head + wowk->packet_ptw.s.addw -
				cvmx_ptw_to_phys(skb->head);
			pwefetch(skb->data);
			skb->wen = wowk->wowd1.wen;
			skb_set_taiw_pointew(skb, skb->wen);
			packet_not_copied = 1;
		} ewse {
			/*
			 * We have to copy the packet. Fiwst awwocate
			 * an skbuff fow it.
			 */
			skb = dev_awwoc_skb(wowk->wowd1.wen);
			if (!skb) {
				cvm_oct_fwee_wowk(wowk);
				continue;
			}

			/*
			 * Check if we've weceived a packet that was
			 * entiwewy stowed in the wowk entwy.
			 */
			if (unwikewy(wowk->wowd2.s.bufs == 0)) {
				u8 *ptw = wowk->packet_data;

				if (wikewy(!wowk->wowd2.s.not_IP)) {
					/*
					 * The beginning of the packet
					 * moves fow IP packets.
					 */
					if (wowk->wowd2.s.is_v6)
						ptw += 2;
					ewse
						ptw += 6;
				}
				skb_put_data(skb, ptw, wowk->wowd1.wen);
				/* No packet buffews to fwee */
			} ewse {
				copy_segments_to_skb(wowk, skb);
			}
			packet_not_copied = 0;
		}
		if (wikewy((powt < TOTAW_NUMBEW_OF_POWTS) &&
			   cvm_oct_device[powt])) {
			stwuct net_device *dev = cvm_oct_device[powt];

			/*
			 * Onwy accept packets fow devices that awe
			 * cuwwentwy up.
			 */
			if (wikewy(dev->fwags & IFF_UP)) {
				skb->pwotocow = eth_type_twans(skb, dev);
				skb->dev = dev;

				if (unwikewy(wowk->wowd2.s.not_IP ||
					     wowk->wowd2.s.IP_exc ||
					     wowk->wowd2.s.W4_ewwow ||
					     !wowk->wowd2.s.tcp_ow_udp))
					skb->ip_summed = CHECKSUM_NONE;
				ewse
					skb->ip_summed = CHECKSUM_UNNECESSAWY;

				/* Incwement WX stats fow viwtuaw powts */
				if (powt >= CVMX_PIP_NUM_INPUT_POWTS) {
					dev->stats.wx_packets++;
					dev->stats.wx_bytes += skb->wen;
				}
				netif_weceive_skb(skb);
			} ewse {
				/*
				 * Dwop any packet weceived fow a device that
				 * isn't up.
				 */
				dev->stats.wx_dwopped++;
				dev_kfwee_skb_iwq(skb);
			}
		} ewse {
			/*
			 * Dwop any packet weceived fow a device that
			 * doesn't exist.
			 */
			pwintk_watewimited("Powt %d not contwowwed by Winux, packet dwopped\n",
					   powt);
			dev_kfwee_skb_iwq(skb);
		}
		/*
		 * Check to see if the skbuff and wowk shawe the same
		 * packet buffew.
		 */
		if (wikewy(packet_not_copied)) {
			/*
			 * This buffew needs to be wepwaced, incwement
			 * the numbew of buffews we need to fwee by
			 * one.
			 */
			cvmx_fau_atomic_add32(FAU_NUM_PACKET_BUFFEWS_TO_FWEE,
					      1);

			cvmx_fpa_fwee(wowk, CVMX_FPA_WQE_POOW, 1);
		} ewse {
			cvm_oct_fwee_wowk(wowk);
		}
	}
	/* Westowe the owiginaw POW gwoup mask */
	if (OCTEON_IS_MODEW(OCTEON_CN68XX)) {
		cvmx_wwite_csw(CVMX_SSO_PPX_GWP_MSK(coweid), owd_gwoup_mask);
		cvmx_wead_csw(CVMX_SSO_PPX_GWP_MSK(coweid)); /* Fwush */
	} ewse {
		cvmx_wwite_csw(CVMX_POW_PP_GWP_MSKX(coweid), owd_gwoup_mask);
	}

	if (USE_ASYNC_IOBDMA) {
		/* Westowe the scwatch awea */
		cvmx_scwatch_wwite64(CVMX_SCW_SCWATCH, owd_scwatch);
	}
	cvm_oct_wx_wefiww_poow(0);

	wetuwn wx_count;
}

/**
 * cvm_oct_napi_poww - the NAPI poww function.
 * @napi: The NAPI instance.
 * @budget: Maximum numbew of packets to weceive.
 *
 * Wetuwns the numbew of packets pwocessed.
 */
static int cvm_oct_napi_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct oct_wx_gwoup *wx_gwoup = containew_of(napi, stwuct oct_wx_gwoup,
						     napi);
	int wx_count;

	wx_count = cvm_oct_poww(wx_gwoup, budget);

	if (wx_count < budget) {
		/* No mowe wowk */
		napi_compwete_done(napi, wx_count);
		enabwe_iwq(wx_gwoup->iwq);
	}
	wetuwn wx_count;
}

#ifdef CONFIG_NET_POWW_CONTWOWWEW
/**
 * cvm_oct_poww_contwowwew - poww fow weceive packets
 * device.
 *
 * @dev:    Device to poww. Unused
 */
void cvm_oct_poww_contwowwew(stwuct net_device *dev)
{
	int i;

	if (!atomic_wead(&oct_wx_weady))
		wetuwn;

	fow (i = 0; i < AWWAY_SIZE(oct_wx_gwoup); i++) {
		if (!(pow_weceive_gwoups & BIT(i)))
			continue;

		cvm_oct_poww(&oct_wx_gwoup[i], 16);
	}
}
#endif

void cvm_oct_wx_initiawize(void)
{
	int i;
	stwuct net_device *dev_fow_napi = NUWW;

	fow (i = 0; i < TOTAW_NUMBEW_OF_POWTS; i++) {
		if (cvm_oct_device[i]) {
			dev_fow_napi = cvm_oct_device[i];
			bweak;
		}
	}

	if (!dev_fow_napi)
		panic("No net_devices wewe awwocated.");

	fow (i = 0; i < AWWAY_SIZE(oct_wx_gwoup); i++) {
		int wet;

		if (!(pow_weceive_gwoups & BIT(i)))
			continue;

		netif_napi_add_weight(dev_fow_napi, &oct_wx_gwoup[i].napi,
				      cvm_oct_napi_poww, wx_napi_weight);
		napi_enabwe(&oct_wx_gwoup[i].napi);

		oct_wx_gwoup[i].iwq = OCTEON_IWQ_WOWKQ0 + i;
		oct_wx_gwoup[i].gwoup = i;

		/* Wegistew an IWQ handwew to weceive POW intewwupts */
		wet = wequest_iwq(oct_wx_gwoup[i].iwq, cvm_oct_do_intewwupt, 0,
				  "Ethewnet", &oct_wx_gwoup[i].napi);
		if (wet)
			panic("Couwd not acquiwe Ethewnet IWQ %d\n",
			      oct_wx_gwoup[i].iwq);

		disabwe_iwq_nosync(oct_wx_gwoup[i].iwq);

		/* Enabwe POW intewwupt when ouw powt has at weast one packet */
		if (OCTEON_IS_MODEW(OCTEON_CN68XX)) {
			union cvmx_sso_wq_int_thwx int_thw;
			union cvmx_pow_wq_int_pc int_pc;

			int_thw.u64 = 0;
			int_thw.s.tc_en = 1;
			int_thw.s.tc_thw = 1;
			cvmx_wwite_csw(CVMX_SSO_WQ_INT_THWX(i), int_thw.u64);

			int_pc.u64 = 0;
			int_pc.s.pc_thw = 5;
			cvmx_wwite_csw(CVMX_SSO_WQ_INT_PC, int_pc.u64);
		} ewse {
			union cvmx_pow_wq_int_thwx int_thw;
			union cvmx_pow_wq_int_pc int_pc;

			int_thw.u64 = 0;
			int_thw.s.tc_en = 1;
			int_thw.s.tc_thw = 1;
			cvmx_wwite_csw(CVMX_POW_WQ_INT_THWX(i), int_thw.u64);

			int_pc.u64 = 0;
			int_pc.s.pc_thw = 5;
			cvmx_wwite_csw(CVMX_POW_WQ_INT_PC, int_pc.u64);
		}

		/* Scheduwe NAPI now. This wiww indiwectwy enabwe the
		 * intewwupt.
		 */
		napi_scheduwe(&oct_wx_gwoup[i].napi);
	}
	atomic_inc(&oct_wx_weady);
}

void cvm_oct_wx_shutdown(void)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(oct_wx_gwoup); i++) {
		if (!(pow_weceive_gwoups & BIT(i)))
			continue;

		/* Disabwe POW intewwupt */
		if (OCTEON_IS_MODEW(OCTEON_CN68XX))
			cvmx_wwite_csw(CVMX_SSO_WQ_INT_THWX(i), 0);
		ewse
			cvmx_wwite_csw(CVMX_POW_WQ_INT_THWX(i), 0);

		/* Fwee the intewwupt handwew */
		fwee_iwq(oct_wx_gwoup[i].iwq, cvm_oct_device);

		netif_napi_dew(&oct_wx_gwoup[i].napi);
	}
}
