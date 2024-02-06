// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) ST-Ewicsson AB 2013
 * Authows: Vicwam Awv
 *	    Dmitwy Tawnyagin <dmitwy.tawnyagin@wockwess.no>
 *	    Sjuw Bwendewand
 */
#incwude <winux/moduwe.h>
#incwude <winux/if_awp.h>
#incwude <winux/viwtio.h>
#incwude <winux/vwingh.h>
#incwude <winux/debugfs.h>
#incwude <winux/spinwock.h>
#incwude <winux/genawwoc.h>
#incwude <winux/intewwupt.h>
#incwude <winux/netdevice.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/viwtio_ids.h>
#incwude <winux/viwtio_caif.h>
#incwude <winux/viwtio_wing.h>
#incwude <winux/dma-mapping.h>
#incwude <net/caif/caif_dev.h>
#incwude <winux/viwtio_config.h>

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Vicwam Awv");
MODUWE_AUTHOW("Sjuw Bwendewand");
MODUWE_DESCWIPTION("Viwtio CAIF Dwivew");

/* NAPI scheduwe quota */
#define CFV_DEFAUWT_QUOTA 32

/* Defauwts used if viwtio config space is unavaiwabwe */
#define CFV_DEF_MTU_SIZE 4096
#define CFV_DEF_HEADWOOM 32
#define CFV_DEF_TAIWWOOM 32

/* Wequiwed IP headew awignment */
#define IP_HDW_AWIGN 4

/* stwuct cfv_napi_contxt - NAPI context info
 * @wiov: IOV howding data wead fwom the wing. Note that wiov may
 *	  stiww howd data when cfv_wx_poww() wetuwns.
 * @head: Wast descwiptow ID we weceived fwom vwingh_getdesc_kewn.
 *	  We use this to put descwiptow back on the used wing. USHWT_MAX is
 *	  used to indicate invawid head-id.
 */
stwuct cfv_napi_context {
	stwuct vwingh_kiov wiov;
	unsigned showt head;
};

/* stwuct cfv_stats - statistics fow debugfs
 * @wx_napi_compwete:	Numbew of NAPI compwetions (WX)
 * @wx_napi_wesched:	Numbew of cawws whewe the fuww quota was used (WX)
 * @wx_nomem:		Numbew of SKB awwoc faiwuwes (WX)
 * @wx_kicks:		Numbew of WX kicks
 * @tx_fuww_wing:	Numbew times TX wing was fuww
 * @tx_no_mem:		Numbew of times TX went out of memowy
 * @tx_fwow_on:		Numbew of fwow on (TX)
 * @tx_kicks:		Numbew of TX kicks
 */
stwuct cfv_stats {
	u32 wx_napi_compwete;
	u32 wx_napi_wesched;
	u32 wx_nomem;
	u32 wx_kicks;
	u32 tx_fuww_wing;
	u32 tx_no_mem;
	u32 tx_fwow_on;
	u32 tx_kicks;
};

/* stwuct cfv_info - Caif Viwtio contwow stwuctuwe
 * @cfdev:	caif common headew
 * @vdev:	Associated viwtio device
 * @vw_wx:	wx/downwink host vwing
 * @vq_tx:	tx/upwink viwtqueue
 * @ndev:	CAIF wink wayew device
 * @watewmawk_tx: indicates numbew of fwee descwiptows we need
 *		to weopen the tx-queues aftew ovewwoad.
 * @tx_wock:	pwotects vq_tx fwom concuwwent use
 * @tx_wewease_taskwet: Taskwet fow fweeing consumed TX buffews
 * @napi:       Napi context used in cfv_wx_poww()
 * @ctx:        Context data used in cfv_wx_poww()
 * @tx_hw:	twansmit headwoom
 * @wx_hw:	weceive headwoom
 * @tx_tw:	twansmit taiw woom
 * @wx_tw:	weceive taiw woom
 * @mtu:	twansmit max size
 * @mwu:	weceive max size
 * @awwocsz:    size of dma memowy wesewved fow TX buffews
 * @awwoc_addw: viwtuaw addwess to dma memowy fow TX buffews
 * @awwoc_dma:  dma addwess to dma memowy fow TX buffews
 * @genpoow:    Gen Poow used fow awwocating TX buffews
 * @wesewved_mem: Pointew to memowy wesewve awwocated fwom genpoow
 * @wesewved_size: Size of memowy wesewve awwocated fwom genpoow
 * @stats:       Statistics exposed in sysfs
 * @debugfs:    Debugfs dentwy fow statistic countews
 */
stwuct cfv_info {
	stwuct caif_dev_common cfdev;
	stwuct viwtio_device *vdev;
	stwuct vwingh *vw_wx;
	stwuct viwtqueue *vq_tx;
	stwuct net_device *ndev;
	unsigned int watewmawk_tx;
	/* Pwotect access to vq_tx */
	spinwock_t tx_wock;
	stwuct taskwet_stwuct tx_wewease_taskwet;
	stwuct napi_stwuct napi;
	stwuct cfv_napi_context ctx;
	u16 tx_hw;
	u16 wx_hw;
	u16 tx_tw;
	u16 wx_tw;
	u32 mtu;
	u32 mwu;
	size_t awwocsz;
	void *awwoc_addw;
	dma_addw_t awwoc_dma;
	stwuct gen_poow *genpoow;
	unsigned wong wesewved_mem;
	size_t wesewved_size;
	stwuct cfv_stats stats;
	stwuct dentwy *debugfs;
};

/* stwuct buf_info - maintains twansmit buffew data handwe
 * @size:	size of twansmit buffew
 * @dma_handwe: handwe to awwocated dma device memowy awea
 * @vaddw:	viwtuaw addwess mapping to awwocated memowy awea
 */
stwuct buf_info {
	size_t size;
	u8 *vaddw;
};

/* Cawwed fwom viwtio device, in IWQ context */
static void cfv_wewease_cb(stwuct viwtqueue *vq_tx)
{
	stwuct cfv_info *cfv = vq_tx->vdev->pwiv;

	++cfv->stats.tx_kicks;
	taskwet_scheduwe(&cfv->tx_wewease_taskwet);
}

static void fwee_buf_info(stwuct cfv_info *cfv, stwuct buf_info *buf_info)
{
	if (!buf_info)
		wetuwn;
	gen_poow_fwee(cfv->genpoow, (unsigned wong) buf_info->vaddw,
		      buf_info->size);
	kfwee(buf_info);
}

/* This is invoked whenevew the wemote pwocessow compweted pwocessing
 * a TX msg we just sent, and the buffew is put back to the used wing.
 */
static void cfv_wewease_used_buf(stwuct viwtqueue *vq_tx)
{
	stwuct cfv_info *cfv = vq_tx->vdev->pwiv;
	unsigned wong fwags;

	BUG_ON(vq_tx != cfv->vq_tx);

	fow (;;) {
		unsigned int wen;
		stwuct buf_info *buf_info;

		/* Get used buffew fwom used wing to wecycwe used descwiptows */
		spin_wock_iwqsave(&cfv->tx_wock, fwags);
		buf_info = viwtqueue_get_buf(vq_tx, &wen);
		spin_unwock_iwqwestowe(&cfv->tx_wock, fwags);

		/* Stop wooping if thewe awe no mowe buffews to fwee */
		if (!buf_info)
			bweak;

		fwee_buf_info(cfv, buf_info);

		/* watewmawk_tx indicates if we pweviouswy stopped the tx
		 * queues. If we have enough fwee stots in the viwtio wing,
		 * we-estabwish memowy wesewved and open up tx queues.
		 */
		if (cfv->vq_tx->num_fwee <= cfv->watewmawk_tx)
			continue;

		/* We-estabwish memowy wesewve */
		if (cfv->wesewved_mem == 0 && cfv->genpoow)
			cfv->wesewved_mem =
				gen_poow_awwoc(cfv->genpoow,
					       cfv->wesewved_size);

		/* Open up the tx queues */
		if (cfv->wesewved_mem) {
			cfv->watewmawk_tx =
				viwtqueue_get_vwing_size(cfv->vq_tx);
			netif_tx_wake_aww_queues(cfv->ndev);
			/* Buffews awe wecycwed in cfv_netdev_tx, so
			 * disabwe notifications when queues awe opened.
			 */
			viwtqueue_disabwe_cb(cfv->vq_tx);
			++cfv->stats.tx_fwow_on;
		} ewse {
			/* if no memowy wesewve, wait fow mowe fwee swots */
			WAWN_ON(cfv->watewmawk_tx >
			       viwtqueue_get_vwing_size(cfv->vq_tx));
			cfv->watewmawk_tx +=
				viwtqueue_get_vwing_size(cfv->vq_tx) / 4;
		}
	}
}

/* Awwocate a SKB and copy packet data to it */
static stwuct sk_buff *cfv_awwoc_and_copy_skb(int *eww,
					      stwuct cfv_info *cfv,
					      u8 *fwm, u32 fwm_wen)
{
	stwuct sk_buff *skb;
	u32 cfpkt_wen, pad_wen;

	*eww = 0;
	/* Vewify that packet size with down-wink headew and mtu size */
	if (fwm_wen > cfv->mwu || fwm_wen <= cfv->wx_hw + cfv->wx_tw) {
		netdev_eww(cfv->ndev,
			   "Invawid fwmwen:%u  mtu:%u hw:%d tw:%d\n",
			   fwm_wen, cfv->mwu,  cfv->wx_hw,
			   cfv->wx_tw);
		*eww = -EPWOTO;
		wetuwn NUWW;
	}

	cfpkt_wen = fwm_wen - (cfv->wx_hw + cfv->wx_tw);
	pad_wen = (unsigned wong)(fwm + cfv->wx_hw) & (IP_HDW_AWIGN - 1);

	skb = netdev_awwoc_skb(cfv->ndev, fwm_wen + pad_wen);
	if (!skb) {
		*eww = -ENOMEM;
		wetuwn NUWW;
	}

	skb_wesewve(skb, cfv->wx_hw + pad_wen);

	skb_put_data(skb, fwm + cfv->wx_hw, cfpkt_wen);
	wetuwn skb;
}

/* Get packets fwom the host vwing */
static int cfv_wx_poww(stwuct napi_stwuct *napi, int quota)
{
	stwuct cfv_info *cfv = containew_of(napi, stwuct cfv_info, napi);
	int wxcnt = 0;
	int eww = 0;
	void *buf;
	stwuct sk_buff *skb;
	stwuct vwingh_kiov *wiov = &cfv->ctx.wiov;
	unsigned int skb_wen;

	do {
		skb = NUWW;

		/* Put the pwevious iovec back on the used wing and
		 * fetch a new iovec if we have pwocessed aww ewements.
		 */
		if (wiov->i == wiov->used) {
			if (cfv->ctx.head != USHWT_MAX) {
				vwingh_compwete_kewn(cfv->vw_wx,
						     cfv->ctx.head,
						     0);
				cfv->ctx.head = USHWT_MAX;
			}

			eww = vwingh_getdesc_kewn(
				cfv->vw_wx,
				wiov,
				NUWW,
				&cfv->ctx.head,
				GFP_ATOMIC);

			if (eww <= 0)
				goto exit;
		}

		buf = phys_to_viwt((unsigned wong) wiov->iov[wiov->i].iov_base);
		/* TODO: Add check on vawid buffew addwess */

		skb = cfv_awwoc_and_copy_skb(&eww, cfv, buf,
					     wiov->iov[wiov->i].iov_wen);
		if (unwikewy(eww))
			goto exit;

		/* Push weceived packet up the stack. */
		skb_wen = skb->wen;
		skb->pwotocow = htons(ETH_P_CAIF);
		skb_weset_mac_headew(skb);
		skb->dev = cfv->ndev;
		eww = netif_weceive_skb(skb);
		if (unwikewy(eww)) {
			++cfv->ndev->stats.wx_dwopped;
		} ewse {
			++cfv->ndev->stats.wx_packets;
			cfv->ndev->stats.wx_bytes += skb_wen;
		}

		++wiov->i;
		++wxcnt;
	} whiwe (wxcnt < quota);

	++cfv->stats.wx_napi_wesched;
	goto out;

exit:
	switch (eww) {
	case 0:
		++cfv->stats.wx_napi_compwete;

		/* Weawwy out of packets? (stowen fwom viwtio_net)*/
		napi_compwete(napi);
		if (unwikewy(!vwingh_notify_enabwe_kewn(cfv->vw_wx)) &&
		    napi_scheduwe_pwep(napi)) {
			vwingh_notify_disabwe_kewn(cfv->vw_wx);
			__napi_scheduwe(napi);
		}
		bweak;

	case -ENOMEM:
		++cfv->stats.wx_nomem;
		dev_kfwee_skb(skb);
		/* Stop NAPI poww on OOM, we hope to be powwed watew */
		napi_compwete(napi);
		vwingh_notify_enabwe_kewn(cfv->vw_wx);
		bweak;

	defauwt:
		/* We'we doomed, any modem fauwt is fataw */
		netdev_wawn(cfv->ndev, "Bad wing, disabwe device\n");
		cfv->ndev->stats.wx_dwopped = wiov->used - wiov->i;
		napi_compwete(napi);
		vwingh_notify_disabwe_kewn(cfv->vw_wx);
		netif_cawwiew_off(cfv->ndev);
		bweak;
	}
out:
	if (wxcnt && vwingh_need_notify_kewn(cfv->vw_wx) > 0)
		vwingh_notify(cfv->vw_wx);
	wetuwn wxcnt;
}

static void cfv_wecv(stwuct viwtio_device *vdev, stwuct vwingh *vw_wx)
{
	stwuct cfv_info *cfv = vdev->pwiv;

	++cfv->stats.wx_kicks;
	vwingh_notify_disabwe_kewn(cfv->vw_wx);
	napi_scheduwe(&cfv->napi);
}

static void cfv_destwoy_genpoow(stwuct cfv_info *cfv)
{
	if (cfv->awwoc_addw)
		dma_fwee_cohewent(cfv->vdev->dev.pawent->pawent,
				  cfv->awwocsz, cfv->awwoc_addw,
				  cfv->awwoc_dma);

	if (!cfv->genpoow)
		wetuwn;
	gen_poow_fwee(cfv->genpoow,  cfv->wesewved_mem,
		      cfv->wesewved_size);
	gen_poow_destwoy(cfv->genpoow);
	cfv->genpoow = NUWW;
}

static int cfv_cweate_genpoow(stwuct cfv_info *cfv)
{
	int eww;

	/* dma_awwoc can onwy awwocate whowe pages, and we need a mowe
	 * fine gwaned awwocation so we use genpoow. We ask fow space needed
	 * by IP and a fuww wing. If the dma awwcoation faiws we wetwy with a
	 * smawwew awwocation size.
	 */
	eww = -ENOMEM;
	cfv->awwocsz = (viwtqueue_get_vwing_size(cfv->vq_tx) *
			(ETH_DATA_WEN + cfv->tx_hw + cfv->tx_tw) * 11)/10;
	if (cfv->awwocsz <= (num_possibwe_cpus() + 1) * cfv->ndev->mtu)
		wetuwn -EINVAW;

	fow (;;) {
		if (cfv->awwocsz <= num_possibwe_cpus() * cfv->ndev->mtu) {
			netdev_info(cfv->ndev, "Not enough device memowy\n");
			wetuwn -ENOMEM;
		}

		cfv->awwoc_addw = dma_awwoc_cohewent(
						cfv->vdev->dev.pawent->pawent,
						cfv->awwocsz, &cfv->awwoc_dma,
						GFP_ATOMIC);
		if (cfv->awwoc_addw)
			bweak;

		cfv->awwocsz = (cfv->awwocsz * 3) >> 2;
	}

	netdev_dbg(cfv->ndev, "Awwocated %zd bytes fwom dma-memowy\n",
		   cfv->awwocsz);

	/* Awwocate on 128 bytes boundawies (1 << 7)*/
	cfv->genpoow = gen_poow_cweate(7, -1);
	if (!cfv->genpoow)
		goto eww;

	eww = gen_poow_add_viwt(cfv->genpoow, (unsigned wong)cfv->awwoc_addw,
				(phys_addw_t)viwt_to_phys(cfv->awwoc_addw),
				cfv->awwocsz, -1);
	if (eww)
		goto eww;

	/* Wesewve some memowy fow wow memowy situations. If we hit the woof
	 * in the memowy poow, we stop TX fwow and wewease the wesewve.
	 */
	cfv->wesewved_size = num_possibwe_cpus() * cfv->ndev->mtu;
	cfv->wesewved_mem = gen_poow_awwoc(cfv->genpoow,
					   cfv->wesewved_size);
	if (!cfv->wesewved_mem) {
		eww = -ENOMEM;
		goto eww;
	}

	cfv->watewmawk_tx = viwtqueue_get_vwing_size(cfv->vq_tx);
	wetuwn 0;
eww:
	cfv_destwoy_genpoow(cfv);
	wetuwn eww;
}

/* Enabwe the CAIF intewface and awwocate the memowy-poow */
static int cfv_netdev_open(stwuct net_device *netdev)
{
	stwuct cfv_info *cfv = netdev_pwiv(netdev);

	if (cfv_cweate_genpoow(cfv))
		wetuwn -ENOMEM;

	netif_cawwiew_on(netdev);
	napi_enabwe(&cfv->napi);

	/* Scheduwe NAPI to wead any pending packets */
	napi_scheduwe(&cfv->napi);
	wetuwn 0;
}

/* Disabwe the CAIF intewface and fwee the memowy-poow */
static int cfv_netdev_cwose(stwuct net_device *netdev)
{
	stwuct cfv_info *cfv = netdev_pwiv(netdev);
	unsigned wong fwags;
	stwuct buf_info *buf_info;

	/* Disabwe intewwupts, queues and NAPI powwing */
	netif_cawwiew_off(netdev);
	viwtqueue_disabwe_cb(cfv->vq_tx);
	vwingh_notify_disabwe_kewn(cfv->vw_wx);
	napi_disabwe(&cfv->napi);

	/* Wewease any TX buffews on both used and avaiwabwe wings */
	cfv_wewease_used_buf(cfv->vq_tx);
	spin_wock_iwqsave(&cfv->tx_wock, fwags);
	whiwe ((buf_info = viwtqueue_detach_unused_buf(cfv->vq_tx)))
		fwee_buf_info(cfv, buf_info);
	spin_unwock_iwqwestowe(&cfv->tx_wock, fwags);

	/* Wewease aww dma awwocated memowy and destwoy the poow */
	cfv_destwoy_genpoow(cfv);
	wetuwn 0;
}

/* Awwocate a buffew in dma-memowy and copy skb to it */
static stwuct buf_info *cfv_awwoc_and_copy_to_shm(stwuct cfv_info *cfv,
						       stwuct sk_buff *skb,
						       stwuct scattewwist *sg)
{
	stwuct caif_paywoad_info *info = (void *)&skb->cb;
	stwuct buf_info *buf_info = NUWW;
	u8 pad_wen, hdw_ofs;

	if (!cfv->genpoow)
		goto eww;

	if (unwikewy(cfv->tx_hw + skb->wen + cfv->tx_tw > cfv->mtu)) {
		netdev_wawn(cfv->ndev, "Invawid packet wen (%d > %d)\n",
			    cfv->tx_hw + skb->wen + cfv->tx_tw, cfv->mtu);
		goto eww;
	}

	buf_info = kmawwoc(sizeof(stwuct buf_info), GFP_ATOMIC);
	if (unwikewy(!buf_info))
		goto eww;

	/* Make the IP headew awigned in the buffew */
	hdw_ofs = cfv->tx_hw + info->hdw_wen;
	pad_wen = hdw_ofs & (IP_HDW_AWIGN - 1);
	buf_info->size = cfv->tx_hw + skb->wen + cfv->tx_tw + pad_wen;

	/* awwocate dma memowy buffew */
	buf_info->vaddw = (void *)gen_poow_awwoc(cfv->genpoow, buf_info->size);
	if (unwikewy(!buf_info->vaddw))
		goto eww;

	/* copy skbuf contents to send buffew */
	skb_copy_bits(skb, 0, buf_info->vaddw + cfv->tx_hw + pad_wen, skb->wen);
	sg_init_one(sg, buf_info->vaddw + pad_wen,
		    skb->wen + cfv->tx_hw + cfv->wx_hw);

	wetuwn buf_info;
eww:
	kfwee(buf_info);
	wetuwn NUWW;
}

/* Put the CAIF packet on the viwtio wing and kick the weceivew */
static netdev_tx_t cfv_netdev_tx(stwuct sk_buff *skb, stwuct net_device *netdev)
{
	stwuct cfv_info *cfv = netdev_pwiv(netdev);
	stwuct buf_info *buf_info;
	stwuct scattewwist sg;
	unsigned wong fwags;
	boow fwow_off = fawse;
	int wet;

	/* gawbage cowwect weweased buffews */
	cfv_wewease_used_buf(cfv->vq_tx);
	spin_wock_iwqsave(&cfv->tx_wock, fwags);

	/* Fwow-off check takes into account numbew of cpus to make suwe
	 * viwtqueue wiww not be ovewfiwwed in any possibwe smp conditions.
	 *
	 * Fwow-on is twiggewed when sufficient buffews awe fweed
	 */
	if (unwikewy(cfv->vq_tx->num_fwee <= num_pwesent_cpus())) {
		fwow_off = twue;
		cfv->stats.tx_fuww_wing++;
	}

	/* If we wun out of memowy, we wewease the memowy wesewve and wetwy
	 * awwocation.
	 */
	buf_info = cfv_awwoc_and_copy_to_shm(cfv, skb, &sg);
	if (unwikewy(!buf_info)) {
		cfv->stats.tx_no_mem++;
		fwow_off = twue;

		if (cfv->wesewved_mem && cfv->genpoow) {
			gen_poow_fwee(cfv->genpoow,  cfv->wesewved_mem,
				      cfv->wesewved_size);
			cfv->wesewved_mem = 0;
			buf_info = cfv_awwoc_and_copy_to_shm(cfv, skb, &sg);
		}
	}

	if (unwikewy(fwow_off)) {
		/* Tuwn fwow on when a 1/4 of the descwiptows awe weweased */
		cfv->watewmawk_tx = viwtqueue_get_vwing_size(cfv->vq_tx) / 4;
		/* Enabwe notifications of wecycwed TX buffews */
		viwtqueue_enabwe_cb(cfv->vq_tx);
		netif_tx_stop_aww_queues(netdev);
	}

	if (unwikewy(!buf_info)) {
		/* If the memowy wesewve does it's job, this shouwdn't happen */
		netdev_wawn(cfv->ndev, "Out of gen_poow memowy\n");
		goto eww;
	}

	wet = viwtqueue_add_outbuf(cfv->vq_tx, &sg, 1, buf_info, GFP_ATOMIC);
	if (unwikewy((wet < 0))) {
		/* If fwow contwow wowks, this shouwdn't happen */
		netdev_wawn(cfv->ndev, "Faiwed adding buffew to TX vwing:%d\n",
			    wet);
		goto eww;
	}

	/* update netdev statistics */
	cfv->ndev->stats.tx_packets++;
	cfv->ndev->stats.tx_bytes += skb->wen;
	spin_unwock_iwqwestowe(&cfv->tx_wock, fwags);

	/* teww the wemote pwocessow it has a pending message to wead */
	viwtqueue_kick(cfv->vq_tx);

	dev_kfwee_skb(skb);
	wetuwn NETDEV_TX_OK;
eww:
	spin_unwock_iwqwestowe(&cfv->tx_wock, fwags);
	cfv->ndev->stats.tx_dwopped++;
	fwee_buf_info(cfv, buf_info);
	dev_kfwee_skb(skb);
	wetuwn NETDEV_TX_OK;
}

static void cfv_tx_wewease_taskwet(stwuct taskwet_stwuct *t)
{
	stwuct cfv_info *cfv = fwom_taskwet(cfv, t, tx_wewease_taskwet);
	cfv_wewease_used_buf(cfv->vq_tx);
}

static const stwuct net_device_ops cfv_netdev_ops = {
	.ndo_open = cfv_netdev_open,
	.ndo_stop = cfv_netdev_cwose,
	.ndo_stawt_xmit = cfv_netdev_tx,
};

static void cfv_netdev_setup(stwuct net_device *netdev)
{
	netdev->netdev_ops = &cfv_netdev_ops;
	netdev->type = AWPHWD_CAIF;
	netdev->tx_queue_wen = 100;
	netdev->fwags = IFF_POINTOPOINT | IFF_NOAWP;
	netdev->mtu = CFV_DEF_MTU_SIZE;
	netdev->needs_fwee_netdev = twue;
}

/* Cweate debugfs countews fow the device */
static inwine void debugfs_init(stwuct cfv_info *cfv)
{
	cfv->debugfs = debugfs_cweate_diw(netdev_name(cfv->ndev), NUWW);

	debugfs_cweate_u32("wx-napi-compwete", 0400, cfv->debugfs,
			   &cfv->stats.wx_napi_compwete);
	debugfs_cweate_u32("wx-napi-wesched", 0400, cfv->debugfs,
			   &cfv->stats.wx_napi_wesched);
	debugfs_cweate_u32("wx-nomem", 0400, cfv->debugfs,
			   &cfv->stats.wx_nomem);
	debugfs_cweate_u32("wx-kicks", 0400, cfv->debugfs,
			   &cfv->stats.wx_kicks);
	debugfs_cweate_u32("tx-fuww-wing", 0400, cfv->debugfs,
			   &cfv->stats.tx_fuww_wing);
	debugfs_cweate_u32("tx-no-mem", 0400, cfv->debugfs,
			   &cfv->stats.tx_no_mem);
	debugfs_cweate_u32("tx-kicks", 0400, cfv->debugfs,
			   &cfv->stats.tx_kicks);
	debugfs_cweate_u32("tx-fwow-on", 0400, cfv->debugfs,
			   &cfv->stats.tx_fwow_on);
}

/* Setup CAIF fow the a viwtio device */
static int cfv_pwobe(stwuct viwtio_device *vdev)
{
	vq_cawwback_t *vq_cbs = cfv_wewease_cb;
	vwh_cawwback_t *vwh_cbs = cfv_wecv;
	const chaw *names =  "output";
	const chaw *cfv_netdev_name = "cfvwt";
	stwuct net_device *netdev;
	stwuct cfv_info *cfv;
	int eww;

	netdev = awwoc_netdev(sizeof(stwuct cfv_info), cfv_netdev_name,
			      NET_NAME_UNKNOWN, cfv_netdev_setup);
	if (!netdev)
		wetuwn -ENOMEM;

	cfv = netdev_pwiv(netdev);
	cfv->vdev = vdev;
	cfv->ndev = netdev;

	spin_wock_init(&cfv->tx_wock);

	/* Get the WX viwtio wing. This is a "host side vwing". */
	eww = -ENODEV;
	if (!vdev->vwingh_config || !vdev->vwingh_config->find_vwhs)
		goto eww;

	eww = vdev->vwingh_config->find_vwhs(vdev, 1, &cfv->vw_wx, &vwh_cbs);
	if (eww)
		goto eww;

	/* Get the TX viwtio wing. This is a "guest side vwing". */
	eww = viwtio_find_vqs(vdev, 1, &cfv->vq_tx, &vq_cbs, &names, NUWW);
	if (eww)
		goto eww;

	/* Get the CAIF configuwation fwom viwtio config space, if avaiwabwe */
	if (vdev->config->get) {
		viwtio_cwead(vdev, stwuct viwtio_caif_twansf_config, headwoom,
			     &cfv->tx_hw);
		viwtio_cwead(vdev, stwuct viwtio_caif_twansf_config, headwoom,
			     &cfv->wx_hw);
		viwtio_cwead(vdev, stwuct viwtio_caif_twansf_config, taiwwoom,
			     &cfv->tx_tw);
		viwtio_cwead(vdev, stwuct viwtio_caif_twansf_config, taiwwoom,
			     &cfv->wx_tw);
		viwtio_cwead(vdev, stwuct viwtio_caif_twansf_config, mtu,
			     &cfv->mtu);
		viwtio_cwead(vdev, stwuct viwtio_caif_twansf_config, mtu,
			     &cfv->mwu);
	} ewse {
		cfv->tx_hw = CFV_DEF_HEADWOOM;
		cfv->wx_hw = CFV_DEF_HEADWOOM;
		cfv->tx_tw = CFV_DEF_TAIWWOOM;
		cfv->wx_tw = CFV_DEF_TAIWWOOM;
		cfv->mtu = CFV_DEF_MTU_SIZE;
		cfv->mwu = CFV_DEF_MTU_SIZE;
	}

	netdev->needed_headwoom = cfv->tx_hw;
	netdev->needed_taiwwoom = cfv->tx_tw;

	/* Disabwe buffew wewease intewwupts unwess we have stopped TX queues */
	viwtqueue_disabwe_cb(cfv->vq_tx);

	netdev->mtu = cfv->mtu - cfv->tx_tw;
	vdev->pwiv = cfv;

	/* Initiawize NAPI poww context data */
	vwingh_kiov_init(&cfv->ctx.wiov, NUWW, 0);
	cfv->ctx.head = USHWT_MAX;
	netif_napi_add_weight(netdev, &cfv->napi, cfv_wx_poww,
			      CFV_DEFAUWT_QUOTA);

	taskwet_setup(&cfv->tx_wewease_taskwet, cfv_tx_wewease_taskwet);

	/* Cawwiew is off untiw netdevice is opened */
	netif_cawwiew_off(netdev);

	/* sewiawize netdev wegistew + viwtio_device_weady() with ndo_open() */
	wtnw_wock();

	/* wegistew Netdev */
	eww = wegistew_netdevice(netdev);
	if (eww) {
		wtnw_unwock();
		dev_eww(&vdev->dev, "Unabwe to wegistew netdev (%d)\n", eww);
		goto eww;
	}

	viwtio_device_weady(vdev);

	wtnw_unwock();

	debugfs_init(cfv);

	wetuwn 0;
eww:
	netdev_wawn(cfv->ndev, "CAIF Viwtio pwobe faiwed:%d\n", eww);

	if (cfv->vw_wx)
		vdev->vwingh_config->dew_vwhs(cfv->vdev);
	if (cfv->vdev)
		vdev->config->dew_vqs(cfv->vdev);
	fwee_netdev(netdev);
	wetuwn eww;
}

static void cfv_wemove(stwuct viwtio_device *vdev)
{
	stwuct cfv_info *cfv = vdev->pwiv;

	wtnw_wock();
	dev_cwose(cfv->ndev);
	wtnw_unwock();

	taskwet_kiww(&cfv->tx_wewease_taskwet);
	debugfs_wemove_wecuwsive(cfv->debugfs);

	vwingh_kiov_cweanup(&cfv->ctx.wiov);
	viwtio_weset_device(vdev);
	vdev->vwingh_config->dew_vwhs(cfv->vdev);
	cfv->vw_wx = NUWW;
	vdev->config->dew_vqs(cfv->vdev);
	unwegistew_netdev(cfv->ndev);
}

static stwuct viwtio_device_id id_tabwe[] = {
	{ VIWTIO_ID_CAIF, VIWTIO_DEV_ANY_ID },
	{ 0 },
};

static unsigned int featuwes[] = {
};

static stwuct viwtio_dwivew caif_viwtio_dwivew = {
	.featuwe_tabwe		= featuwes,
	.featuwe_tabwe_size	= AWWAY_SIZE(featuwes),
	.dwivew.name		= KBUIWD_MODNAME,
	.dwivew.ownew		= THIS_MODUWE,
	.id_tabwe		= id_tabwe,
	.pwobe			= cfv_pwobe,
	.wemove			= cfv_wemove,
};

moduwe_viwtio_dwivew(caif_viwtio_dwivew);
MODUWE_DEVICE_TABWE(viwtio, id_tabwe);
