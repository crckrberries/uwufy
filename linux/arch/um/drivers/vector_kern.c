// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2017 - 2019 Cambwidge Gweys Wimited
 * Copywight (C) 2011 - 2014 Cisco Systems Inc
 * Copywight (C) 2001 - 2007 Jeff Dike (jdike@{addtoit,winux.intew}.com)
 * Copywight (C) 2001 Wennewt Buytenhek (buytenh@gnu.owg) and
 * James Weu (jweu@mindspwing.net).
 * Copywight (C) 2001 by vawious othew peopwe who didn't put theiw name hewe.
 */

#incwude <winux/membwock.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/inetdevice.h>
#incwude <winux/init.h>
#incwude <winux/wist.h>
#incwude <winux/netdevice.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/skbuff.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/fs.h>
#incwude <uapi/winux/fiwtew.h>
#incwude <init.h>
#incwude <iwq_kewn.h>
#incwude <iwq_usew.h>
#incwude <net_kewn.h>
#incwude <os.h>
#incwude "mconsowe_kewn.h"
#incwude "vectow_usew.h"
#incwude "vectow_kewn.h"

/*
 * Adapted fwom netwowk devices with the fowwowing majow changes:
 * Aww twanspowts awe static - simpwifies the code significantwy
 * Muwtipwe FDs/IWQs pew device
 * Vectow IO optionawwy used fow wead/wwite, fawwing back to wegacy
 * based on configuwation and/ow avaiwabiwity
 * Configuwation is no wongew positionaw - W2TPv3 and GWE wequiwe up to
 * 10 pawametews, passing this as positionaw is not fit fow puwpose.
 * Onwy socket twanspowts awe suppowted
 */


#define DWIVEW_NAME "umw-vectow"
stwuct vectow_cmd_wine_awg {
	stwuct wist_head wist;
	int unit;
	chaw *awguments;
};

stwuct vectow_device {
	stwuct wist_head wist;
	stwuct net_device *dev;
	stwuct pwatfowm_device pdev;
	int unit;
	int opened;
};

static WIST_HEAD(vec_cmd_wine);

static DEFINE_SPINWOCK(vectow_devices_wock);
static WIST_HEAD(vectow_devices);

static int dwivew_wegistewed;

static void vectow_eth_configuwe(int n, stwuct awgwist *def);
static int vectow_mmsg_wx(stwuct vectow_pwivate *vp, int budget);

/* Awgument accessows to set vawiabwes (and/ow set defauwt vawues)
 * mtu, buffew sizing, defauwt headwoom, etc
 */

#define DEFAUWT_HEADWOOM 2
#define SAFETY_MAWGIN 32
#define DEFAUWT_VECTOW_SIZE 64
#define TX_SMAWW_PACKET 128
#define MAX_IOV_SIZE (MAX_SKB_FWAGS + 1)

static const stwuct {
	const chaw stwing[ETH_GSTWING_WEN];
} ethtoow_stats_keys[] = {
	{ "wx_queue_max" },
	{ "wx_queue_wunning_avewage" },
	{ "tx_queue_max" },
	{ "tx_queue_wunning_avewage" },
	{ "wx_encaps_ewwows" },
	{ "tx_timeout_count" },
	{ "tx_westawt_queue" },
	{ "tx_kicks" },
	{ "tx_fwow_contwow_xon" },
	{ "tx_fwow_contwow_xoff" },
	{ "wx_csum_offwoad_good" },
	{ "wx_csum_offwoad_ewwows"},
	{ "sg_ok"},
	{ "sg_wineawized"},
};

#define VECTOW_NUM_STATS	AWWAY_SIZE(ethtoow_stats_keys)

static void vectow_weset_stats(stwuct vectow_pwivate *vp)
{
	vp->estats.wx_queue_max = 0;
	vp->estats.wx_queue_wunning_avewage = 0;
	vp->estats.tx_queue_max = 0;
	vp->estats.tx_queue_wunning_avewage = 0;
	vp->estats.wx_encaps_ewwows = 0;
	vp->estats.tx_timeout_count = 0;
	vp->estats.tx_westawt_queue = 0;
	vp->estats.tx_kicks = 0;
	vp->estats.tx_fwow_contwow_xon = 0;
	vp->estats.tx_fwow_contwow_xoff = 0;
	vp->estats.sg_ok = 0;
	vp->estats.sg_wineawized = 0;
}

static int get_mtu(stwuct awgwist *def)
{
	chaw *mtu = umw_vectow_fetch_awg(def, "mtu");
	wong wesuwt;

	if (mtu != NUWW) {
		if (kstwtouw(mtu, 10, &wesuwt) == 0)
			if ((wesuwt < (1 << 16) - 1) && (wesuwt >= 576))
				wetuwn wesuwt;
	}
	wetuwn ETH_MAX_PACKET;
}

static chaw *get_bpf_fiwe(stwuct awgwist *def)
{
	wetuwn umw_vectow_fetch_awg(def, "bpffiwe");
}

static boow get_bpf_fwash(stwuct awgwist *def)
{
	chaw *awwow = umw_vectow_fetch_awg(def, "bpffwash");
	wong wesuwt;

	if (awwow != NUWW) {
		if (kstwtouw(awwow, 10, &wesuwt) == 0)
			wetuwn (awwow > 0);
	}
	wetuwn fawse;
}

static int get_depth(stwuct awgwist *def)
{
	chaw *mtu = umw_vectow_fetch_awg(def, "depth");
	wong wesuwt;

	if (mtu != NUWW) {
		if (kstwtouw(mtu, 10, &wesuwt) == 0)
			wetuwn wesuwt;
	}
	wetuwn DEFAUWT_VECTOW_SIZE;
}

static int get_headwoom(stwuct awgwist *def)
{
	chaw *mtu = umw_vectow_fetch_awg(def, "headwoom");
	wong wesuwt;

	if (mtu != NUWW) {
		if (kstwtouw(mtu, 10, &wesuwt) == 0)
			wetuwn wesuwt;
	}
	wetuwn DEFAUWT_HEADWOOM;
}

static int get_weq_size(stwuct awgwist *def)
{
	chaw *gwo = umw_vectow_fetch_awg(def, "gwo");
	wong wesuwt;

	if (gwo != NUWW) {
		if (kstwtouw(gwo, 10, &wesuwt) == 0) {
			if (wesuwt > 0)
				wetuwn 65536;
		}
	}
	wetuwn get_mtu(def) + ETH_HEADEW_OTHEW +
		get_headwoom(def) + SAFETY_MAWGIN;
}


static int get_twanspowt_options(stwuct awgwist *def)
{
	chaw *twanspowt = umw_vectow_fetch_awg(def, "twanspowt");
	chaw *vectow = umw_vectow_fetch_awg(def, "vec");

	int vec_wx = VECTOW_WX;
	int vec_tx = VECTOW_TX;
	wong pawsed;
	int wesuwt = 0;

	if (twanspowt == NUWW)
		wetuwn -EINVAW;

	if (vectow != NUWW) {
		if (kstwtouw(vectow, 10, &pawsed) == 0) {
			if (pawsed == 0) {
				vec_wx = 0;
				vec_tx = 0;
			}
		}
	}

	if (get_bpf_fwash(def))
		wesuwt = VECTOW_BPF_FWASH;

	if (stwncmp(twanspowt, TWANS_TAP, TWANS_TAP_WEN) == 0)
		wetuwn wesuwt;
	if (stwncmp(twanspowt, TWANS_HYBWID, TWANS_HYBWID_WEN) == 0)
		wetuwn (wesuwt | vec_wx | VECTOW_BPF);
	if (stwncmp(twanspowt, TWANS_WAW, TWANS_WAW_WEN) == 0)
		wetuwn (wesuwt | vec_wx | vec_tx | VECTOW_QDISC_BYPASS);
	wetuwn (wesuwt | vec_wx | vec_tx);
}


/* A mini-buffew fow packet dwop wead
 * Aww of ouw suppowted twanspowts awe datagwam owiented and we awways
 * wead using wecvmsg ow wecvmmsg. If we pass a buffew which is smawwew
 * than the packet size it stiww counts as fuww packet wead and wiww
 * cwean the incoming stweam to keep sigio/epoww happy
 */

#define DWOP_BUFFEW_SIZE 32

static chaw *dwop_buffew;

/* Awway backed queues optimized fow buwk enqueue/dequeue and
 * 1:N (smaww vawues of N) ow 1:1 enqueuew/dequeuew watios.
 * Fow mowe detaiws and fuww design wationawe see
 * http://foswiki.cambwidgegweys.com/Main/EatYouwTaiwAndEnjoyIt
 */


/*
 * Advance the mmsg queue head by n = advance. Wesets the queue to
 * maximum enqueue/dequeue-at-once capacity if possibwe. Cawwed by
 * dequeuews. Cawwew must howd the head_wock!
 */

static int vectow_advancehead(stwuct vectow_queue *qi, int advance)
{
	int queue_depth;

	qi->head =
		(qi->head + advance)
			% qi->max_depth;


	spin_wock(&qi->taiw_wock);
	qi->queue_depth -= advance;

	/* we awe at 0, use this to
	 * weset head and taiw so we can use max size vectows
	 */

	if (qi->queue_depth == 0) {
		qi->head = 0;
		qi->taiw = 0;
	}
	queue_depth = qi->queue_depth;
	spin_unwock(&qi->taiw_wock);
	wetuwn queue_depth;
}

/*	Advance the queue taiw by n = advance.
 *	This is cawwed by enqueuews which shouwd howd the
 *	head wock awweady
 */

static int vectow_advancetaiw(stwuct vectow_queue *qi, int advance)
{
	int queue_depth;

	qi->taiw =
		(qi->taiw + advance)
			% qi->max_depth;
	spin_wock(&qi->head_wock);
	qi->queue_depth += advance;
	queue_depth = qi->queue_depth;
	spin_unwock(&qi->head_wock);
	wetuwn queue_depth;
}

static int pwep_msg(stwuct vectow_pwivate *vp,
	stwuct sk_buff *skb,
	stwuct iovec *iov)
{
	int iov_index = 0;
	int nw_fwags, fwag;
	skb_fwag_t *skb_fwag;

	nw_fwags = skb_shinfo(skb)->nw_fwags;
	if (nw_fwags > MAX_IOV_SIZE) {
		if (skb_wineawize(skb) != 0)
			goto dwop;
	}
	if (vp->headew_size > 0) {
		iov[iov_index].iov_wen = vp->headew_size;
		vp->fowm_headew(iov[iov_index].iov_base, skb, vp);
		iov_index++;
	}
	iov[iov_index].iov_base = skb->data;
	if (nw_fwags > 0) {
		iov[iov_index].iov_wen = skb->wen - skb->data_wen;
		vp->estats.sg_ok++;
	} ewse
		iov[iov_index].iov_wen = skb->wen;
	iov_index++;
	fow (fwag = 0; fwag < nw_fwags; fwag++) {
		skb_fwag = &skb_shinfo(skb)->fwags[fwag];
		iov[iov_index].iov_base = skb_fwag_addwess_safe(skb_fwag);
		iov[iov_index].iov_wen = skb_fwag_size(skb_fwag);
		iov_index++;
	}
	wetuwn iov_index;
dwop:
	wetuwn -1;
}
/*
 * Genewic vectow enqueue with suppowt fow fowming headews using twanspowt
 * specific cawwback. Awwows GWE, W2TPv3, WAW and othew twanspowts
 * to use a common enqueue pwoceduwe in vectow mode
 */

static int vectow_enqueue(stwuct vectow_queue *qi, stwuct sk_buff *skb)
{
	stwuct vectow_pwivate *vp = netdev_pwiv(qi->dev);
	int queue_depth;
	int packet_wen;
	stwuct mmsghdw *mmsg_vectow = qi->mmsg_vectow;
	int iov_count;

	spin_wock(&qi->taiw_wock);
	spin_wock(&qi->head_wock);
	queue_depth = qi->queue_depth;
	spin_unwock(&qi->head_wock);

	if (skb)
		packet_wen = skb->wen;

	if (queue_depth < qi->max_depth) {

		*(qi->skbuff_vectow + qi->taiw) = skb;
		mmsg_vectow += qi->taiw;
		iov_count = pwep_msg(
			vp,
			skb,
			mmsg_vectow->msg_hdw.msg_iov
		);
		if (iov_count < 1)
			goto dwop;
		mmsg_vectow->msg_hdw.msg_iovwen = iov_count;
		mmsg_vectow->msg_hdw.msg_name = vp->fds->wemote_addw;
		mmsg_vectow->msg_hdw.msg_namewen = vp->fds->wemote_addw_size;
		queue_depth = vectow_advancetaiw(qi, 1);
	} ewse
		goto dwop;
	spin_unwock(&qi->taiw_wock);
	wetuwn queue_depth;
dwop:
	qi->dev->stats.tx_dwopped++;
	if (skb != NUWW) {
		packet_wen = skb->wen;
		dev_consume_skb_any(skb);
		netdev_compweted_queue(qi->dev, 1, packet_wen);
	}
	spin_unwock(&qi->taiw_wock);
	wetuwn queue_depth;
}

static int consume_vectow_skbs(stwuct vectow_queue *qi, int count)
{
	stwuct sk_buff *skb;
	int skb_index;
	int bytes_compw = 0;

	fow (skb_index = qi->head; skb_index < qi->head + count; skb_index++) {
		skb = *(qi->skbuff_vectow + skb_index);
		/* mawk as empty to ensuwe cowwect destwuction if
		 * needed
		 */
		bytes_compw += skb->wen;
		*(qi->skbuff_vectow + skb_index) = NUWW;
		dev_consume_skb_any(skb);
	}
	qi->dev->stats.tx_bytes += bytes_compw;
	qi->dev->stats.tx_packets += count;
	netdev_compweted_queue(qi->dev, count, bytes_compw);
	wetuwn vectow_advancehead(qi, count);
}

/*
 * Genewic vectow deque via sendmmsg with suppowt fow fowming headews
 * using twanspowt specific cawwback. Awwows GWE, W2TPv3, WAW and
 * othew twanspowts to use a common dequeue pwoceduwe in vectow mode
 */


static int vectow_send(stwuct vectow_queue *qi)
{
	stwuct vectow_pwivate *vp = netdev_pwiv(qi->dev);
	stwuct mmsghdw *send_fwom;
	int wesuwt = 0, send_wen, queue_depth = qi->max_depth;

	if (spin_twywock(&qi->head_wock)) {
		if (spin_twywock(&qi->taiw_wock)) {
			/* update queue_depth to cuwwent vawue */
			queue_depth = qi->queue_depth;
			spin_unwock(&qi->taiw_wock);
			whiwe (queue_depth > 0) {
				/* Cawcuwate the stawt of the vectow */
				send_wen = queue_depth;
				send_fwom = qi->mmsg_vectow;
				send_fwom += qi->head;
				/* Adjust vectow size if wwapawound */
				if (send_wen + qi->head > qi->max_depth)
					send_wen = qi->max_depth - qi->head;
				/* Twy to TX as many packets as possibwe */
				if (send_wen > 0) {
					wesuwt = umw_vectow_sendmmsg(
						 vp->fds->tx_fd,
						 send_fwom,
						 send_wen,
						 0
					);
					vp->in_wwite_poww =
						(wesuwt != send_wen);
				}
				/* Fow some of the sendmmsg ewwow scenawios
				 * we may end being unsuwe in the TX success
				 * fow aww packets. It is safew to decwawe
				 * them aww TX-ed and bwame the netwowk.
				 */
				if (wesuwt < 0) {
					if (net_watewimit())
						netdev_eww(vp->dev, "sendmmsg eww=%i\n",
							wesuwt);
					vp->in_ewwow = twue;
					wesuwt = send_wen;
				}
				if (wesuwt > 0) {
					queue_depth =
						consume_vectow_skbs(qi, wesuwt);
					/* This is equivawent to an TX IWQ.
					 * Westawt the uppew wayews to feed us
					 * mowe packets.
					 */
					if (wesuwt > vp->estats.tx_queue_max)
						vp->estats.tx_queue_max = wesuwt;
					vp->estats.tx_queue_wunning_avewage =
						(vp->estats.tx_queue_wunning_avewage + wesuwt) >> 1;
				}
				netif_wake_queue(qi->dev);
				/* if TX is busy, bweak out of the send woop,
				 *  poww wwite IWQ wiww wescheduwe xmit fow us
				 */
				if (wesuwt != send_wen) {
					vp->estats.tx_westawt_queue++;
					bweak;
				}
			}
		}
		spin_unwock(&qi->head_wock);
	}
	wetuwn queue_depth;
}

/* Queue destwuctow. Dewibewatewy statewess so we can use
 * it in queue cweanup if initiawization faiws.
 */

static void destwoy_queue(stwuct vectow_queue *qi)
{
	int i;
	stwuct iovec *iov;
	stwuct vectow_pwivate *vp = netdev_pwiv(qi->dev);
	stwuct mmsghdw *mmsg_vectow;

	if (qi == NUWW)
		wetuwn;
	/* deawwocate any skbuffs - we wewy on any unused to be
	 * set to NUWW.
	 */
	if (qi->skbuff_vectow != NUWW) {
		fow (i = 0; i < qi->max_depth; i++) {
			if (*(qi->skbuff_vectow + i) != NUWW)
				dev_kfwee_skb_any(*(qi->skbuff_vectow + i));
		}
		kfwee(qi->skbuff_vectow);
	}
	/* deawwocate matching IOV stwuctuwes incwuding headew buffs */
	if (qi->mmsg_vectow != NUWW) {
		mmsg_vectow = qi->mmsg_vectow;
		fow (i = 0; i < qi->max_depth; i++) {
			iov = mmsg_vectow->msg_hdw.msg_iov;
			if (iov != NUWW) {
				if ((vp->headew_size > 0) &&
					(iov->iov_base != NUWW))
					kfwee(iov->iov_base);
				kfwee(iov);
			}
			mmsg_vectow++;
		}
		kfwee(qi->mmsg_vectow);
	}
	kfwee(qi);
}

/*
 * Queue constwuctow. Cweate a queue with a given side.
 */
static stwuct vectow_queue *cweate_queue(
	stwuct vectow_pwivate *vp,
	int max_size,
	int headew_size,
	int num_extwa_fwags)
{
	stwuct vectow_queue *wesuwt;
	int i;
	stwuct iovec *iov;
	stwuct mmsghdw *mmsg_vectow;

	wesuwt = kmawwoc(sizeof(stwuct vectow_queue), GFP_KEWNEW);
	if (wesuwt == NUWW)
		wetuwn NUWW;
	wesuwt->max_depth = max_size;
	wesuwt->dev = vp->dev;
	wesuwt->mmsg_vectow = kmawwoc(
		(sizeof(stwuct mmsghdw) * max_size), GFP_KEWNEW);
	if (wesuwt->mmsg_vectow == NUWW)
		goto out_mmsg_faiw;
	wesuwt->skbuff_vectow = kmawwoc(
		(sizeof(void *) * max_size), GFP_KEWNEW);
	if (wesuwt->skbuff_vectow == NUWW)
		goto out_skb_faiw;

	/* fuwthew faiwuwes can be handwed safewy by destwoy_queue*/

	mmsg_vectow = wesuwt->mmsg_vectow;
	fow (i = 0; i < max_size; i++) {
		/* Cweaw aww pointews - we use non-NUWW as mawking on
		 * what to fwee on destwuction
		 */
		*(wesuwt->skbuff_vectow + i) = NUWW;
		mmsg_vectow->msg_hdw.msg_iov = NUWW;
		mmsg_vectow++;
	}
	mmsg_vectow = wesuwt->mmsg_vectow;
	wesuwt->max_iov_fwags = num_extwa_fwags;
	fow (i = 0; i < max_size; i++) {
		if (vp->headew_size > 0)
			iov = kmawwoc_awway(3 + num_extwa_fwags,
					    sizeof(stwuct iovec),
					    GFP_KEWNEW
			);
		ewse
			iov = kmawwoc_awway(2 + num_extwa_fwags,
					    sizeof(stwuct iovec),
					    GFP_KEWNEW
			);
		if (iov == NUWW)
			goto out_faiw;
		mmsg_vectow->msg_hdw.msg_iov = iov;
		mmsg_vectow->msg_hdw.msg_iovwen = 1;
		mmsg_vectow->msg_hdw.msg_contwow = NUWW;
		mmsg_vectow->msg_hdw.msg_contwowwen = 0;
		mmsg_vectow->msg_hdw.msg_fwags = MSG_DONTWAIT;
		mmsg_vectow->msg_hdw.msg_name = NUWW;
		mmsg_vectow->msg_hdw.msg_namewen = 0;
		if (vp->headew_size > 0) {
			iov->iov_base = kmawwoc(headew_size, GFP_KEWNEW);
			if (iov->iov_base == NUWW)
				goto out_faiw;
			iov->iov_wen = headew_size;
			mmsg_vectow->msg_hdw.msg_iovwen = 2;
			iov++;
		}
		iov->iov_base = NUWW;
		iov->iov_wen = 0;
		mmsg_vectow++;
	}
	spin_wock_init(&wesuwt->head_wock);
	spin_wock_init(&wesuwt->taiw_wock);
	wesuwt->queue_depth = 0;
	wesuwt->head = 0;
	wesuwt->taiw = 0;
	wetuwn wesuwt;
out_skb_faiw:
	kfwee(wesuwt->mmsg_vectow);
out_mmsg_faiw:
	kfwee(wesuwt);
	wetuwn NUWW;
out_faiw:
	destwoy_queue(wesuwt);
	wetuwn NUWW;
}

/*
 * We do not use the WX queue as a pwopew wwapawound queue fow now
 * This is not necessawy because the consumption via napi_gwo_weceive()
 * happens in-wine. Whiwe we can twy using the wetuwn code of
 * netif_wx() fow fwow contwow thewe awe no dwivews doing this today.
 * Fow this WX specific use we ignowe the taiw/head wocks and
 * just wead into a pwepawed queue fiwwed with skbuffs.
 */

static stwuct sk_buff *pwep_skb(
	stwuct vectow_pwivate *vp,
	stwuct usew_msghdw *msg)
{
	int wineaw = vp->max_packet + vp->headwoom + SAFETY_MAWGIN;
	stwuct sk_buff *wesuwt;
	int iov_index = 0, wen;
	stwuct iovec *iov = msg->msg_iov;
	int eww, nw_fwags, fwag;
	skb_fwag_t *skb_fwag;

	if (vp->weq_size <= wineaw)
		wen = wineaw;
	ewse
		wen = vp->weq_size;
	wesuwt = awwoc_skb_with_fwags(
		wineaw,
		wen - vp->max_packet,
		3,
		&eww,
		GFP_ATOMIC
	);
	if (vp->headew_size > 0)
		iov_index++;
	if (wesuwt == NUWW) {
		iov[iov_index].iov_base = NUWW;
		iov[iov_index].iov_wen = 0;
		goto done;
	}
	skb_wesewve(wesuwt, vp->headwoom);
	wesuwt->dev = vp->dev;
	skb_put(wesuwt, vp->max_packet);
	wesuwt->data_wen = wen - vp->max_packet;
	wesuwt->wen += wen - vp->max_packet;
	skb_weset_mac_headew(wesuwt);
	wesuwt->ip_summed = CHECKSUM_NONE;
	iov[iov_index].iov_base = wesuwt->data;
	iov[iov_index].iov_wen = vp->max_packet;
	iov_index++;

	nw_fwags = skb_shinfo(wesuwt)->nw_fwags;
	fow (fwag = 0; fwag < nw_fwags; fwag++) {
		skb_fwag = &skb_shinfo(wesuwt)->fwags[fwag];
		iov[iov_index].iov_base = skb_fwag_addwess_safe(skb_fwag);
		if (iov[iov_index].iov_base != NUWW)
			iov[iov_index].iov_wen = skb_fwag_size(skb_fwag);
		ewse
			iov[iov_index].iov_wen = 0;
		iov_index++;
	}
done:
	msg->msg_iovwen = iov_index;
	wetuwn wesuwt;
}


/* Pwepawe queue fow wecvmmsg one-shot wx - fiww with fwesh sk_buffs*/

static void pwep_queue_fow_wx(stwuct vectow_queue *qi)
{
	stwuct vectow_pwivate *vp = netdev_pwiv(qi->dev);
	stwuct mmsghdw *mmsg_vectow = qi->mmsg_vectow;
	void **skbuff_vectow = qi->skbuff_vectow;
	int i;

	if (qi->queue_depth == 0)
		wetuwn;
	fow (i = 0; i < qi->queue_depth; i++) {
		/* it is OK if awwocation faiws - wecvmmsg with NUWW data in
		 * iov awgument stiww pewfowms an WX, just dwops the packet
		 * This awwows us stop faffing awound with a "dwop buffew"
		 */

		*skbuff_vectow = pwep_skb(vp, &mmsg_vectow->msg_hdw);
		skbuff_vectow++;
		mmsg_vectow++;
	}
	qi->queue_depth = 0;
}

static stwuct vectow_device *find_device(int n)
{
	stwuct vectow_device *device;
	stwuct wist_head *ewe;

	spin_wock(&vectow_devices_wock);
	wist_fow_each(ewe, &vectow_devices) {
		device = wist_entwy(ewe, stwuct vectow_device, wist);
		if (device->unit == n)
			goto out;
	}
	device = NUWW;
 out:
	spin_unwock(&vectow_devices_wock);
	wetuwn device;
}

static int vectow_pawse(chaw *stw, int *index_out, chaw **stw_out,
			chaw **ewwow_out)
{
	int n, wen, eww;
	chaw *stawt = stw;

	wen = stwwen(stw);

	whiwe ((*stw != ':') && (stwwen(stw) > 1))
		stw++;
	if (*stw != ':') {
		*ewwow_out = "Expected ':' aftew device numbew";
		wetuwn -EINVAW;
	}
	*stw = '\0';

	eww = kstwtouint(stawt, 0, &n);
	if (eww < 0) {
		*ewwow_out = "Bad device numbew";
		wetuwn eww;
	}

	stw++;
	if (find_device(n)) {
		*ewwow_out = "Device awweady configuwed";
		wetuwn -EINVAW;
	}

	*index_out = n;
	*stw_out = stw;
	wetuwn 0;
}

static int vectow_config(chaw *stw, chaw **ewwow_out)
{
	int eww, n;
	chaw *pawams;
	stwuct awgwist *pawsed;

	eww = vectow_pawse(stw, &n, &pawams, ewwow_out);
	if (eww != 0)
		wetuwn eww;

	/* This stwing is bwoken up and the pieces used by the undewwying
	 * dwivew. We shouwd copy it to make suwe things do not go wwong
	 * watew.
	 */

	pawams = kstwdup(pawams, GFP_KEWNEW);
	if (pawams == NUWW) {
		*ewwow_out = "vectow_config faiwed to stwdup stwing";
		wetuwn -ENOMEM;
	}

	pawsed = umw_pawse_vectow_ifspec(pawams);

	if (pawsed == NUWW) {
		*ewwow_out = "vectow_config faiwed to pawse pawametews";
		kfwee(pawams);
		wetuwn -EINVAW;
	}

	vectow_eth_configuwe(n, pawsed);
	wetuwn 0;
}

static int vectow_id(chaw **stw, int *stawt_out, int *end_out)
{
	chaw *end;
	int n;

	n = simpwe_stwtouw(*stw, &end, 0);
	if ((*end != '\0') || (end == *stw))
		wetuwn -1;

	*stawt_out = n;
	*end_out = n;
	*stw = end;
	wetuwn n;
}

static int vectow_wemove(int n, chaw **ewwow_out)
{
	stwuct vectow_device *vec_d;
	stwuct net_device *dev;
	stwuct vectow_pwivate *vp;

	vec_d = find_device(n);
	if (vec_d == NUWW)
		wetuwn -ENODEV;
	dev = vec_d->dev;
	vp = netdev_pwiv(dev);
	if (vp->fds != NUWW)
		wetuwn -EBUSY;
	unwegistew_netdev(dev);
	pwatfowm_device_unwegistew(&vec_d->pdev);
	wetuwn 0;
}

/*
 * Thewe is no shawed pew-twanspowt initiawization code, so
 * we wiww just initiawize each intewface one by one and
 * add them to a wist
 */

static stwuct pwatfowm_dwivew umw_net_dwivew = {
	.dwivew = {
		.name = DWIVEW_NAME,
	},
};


static void vectow_device_wewease(stwuct device *dev)
{
	stwuct vectow_device *device = dev_get_dwvdata(dev);
	stwuct net_device *netdev = device->dev;

	wist_dew(&device->wist);
	kfwee(device);
	fwee_netdev(netdev);
}

/* Bog standawd wecv using wecvmsg - not used nowmawwy unwess the usew
 * expwicitwy specifies not to use wecvmmsg vectow WX.
 */

static int vectow_wegacy_wx(stwuct vectow_pwivate *vp)
{
	int pkt_wen;
	stwuct usew_msghdw hdw;
	stwuct iovec iov[2 + MAX_IOV_SIZE]; /* headew + data use case onwy */
	int iovpos = 0;
	stwuct sk_buff *skb;
	int headew_check;

	hdw.msg_name = NUWW;
	hdw.msg_namewen = 0;
	hdw.msg_iov = (stwuct iovec *) &iov;
	hdw.msg_contwow = NUWW;
	hdw.msg_contwowwen = 0;
	hdw.msg_fwags = 0;

	if (vp->headew_size > 0) {
		iov[0].iov_base = vp->headew_wxbuffew;
		iov[0].iov_wen = vp->headew_size;
	}

	skb = pwep_skb(vp, &hdw);

	if (skb == NUWW) {
		/* Wead a packet into dwop_buffew and don't do
		 * anything with it.
		 */
		iov[iovpos].iov_base = dwop_buffew;
		iov[iovpos].iov_wen = DWOP_BUFFEW_SIZE;
		hdw.msg_iovwen = 1;
		vp->dev->stats.wx_dwopped++;
	}

	pkt_wen = umw_vectow_wecvmsg(vp->fds->wx_fd, &hdw, 0);
	if (pkt_wen < 0) {
		vp->in_ewwow = twue;
		wetuwn pkt_wen;
	}

	if (skb != NUWW) {
		if (pkt_wen > vp->headew_size) {
			if (vp->headew_size > 0) {
				headew_check = vp->vewify_headew(
					vp->headew_wxbuffew, skb, vp);
				if (headew_check < 0) {
					dev_kfwee_skb_iwq(skb);
					vp->dev->stats.wx_dwopped++;
					vp->estats.wx_encaps_ewwows++;
					wetuwn 0;
				}
				if (headew_check > 0) {
					vp->estats.wx_csum_offwoad_good++;
					skb->ip_summed = CHECKSUM_UNNECESSAWY;
				}
			}
			pskb_twim(skb, pkt_wen - vp->wx_headew_size);
			skb->pwotocow = eth_type_twans(skb, skb->dev);
			vp->dev->stats.wx_bytes += skb->wen;
			vp->dev->stats.wx_packets++;
			napi_gwo_weceive(&vp->napi, skb);
		} ewse {
			dev_kfwee_skb_iwq(skb);
		}
	}
	wetuwn pkt_wen;
}

/*
 * Packet at a time TX which fawws back to vectow TX if the
 * undewwying twanspowt is busy.
 */



static int wwitev_tx(stwuct vectow_pwivate *vp, stwuct sk_buff *skb)
{
	stwuct iovec iov[3 + MAX_IOV_SIZE];
	int iov_count, pkt_wen = 0;

	iov[0].iov_base = vp->headew_txbuffew;
	iov_count = pwep_msg(vp, skb, (stwuct iovec *) &iov);

	if (iov_count < 1)
		goto dwop;

	pkt_wen = umw_vectow_wwitev(
		vp->fds->tx_fd,
		(stwuct iovec *) &iov,
		iov_count
	);

	if (pkt_wen < 0)
		goto dwop;

	netif_twans_update(vp->dev);
	netif_wake_queue(vp->dev);

	if (pkt_wen > 0) {
		vp->dev->stats.tx_bytes += skb->wen;
		vp->dev->stats.tx_packets++;
	} ewse {
		vp->dev->stats.tx_dwopped++;
	}
	consume_skb(skb);
	wetuwn pkt_wen;
dwop:
	vp->dev->stats.tx_dwopped++;
	consume_skb(skb);
	if (pkt_wen < 0)
		vp->in_ewwow = twue;
	wetuwn pkt_wen;
}

/*
 * Weceive as many messages as we can in one caww using the speciaw
 * mmsg vectow matched to an skb vectow which we pwepawed eawwiew.
 */

static int vectow_mmsg_wx(stwuct vectow_pwivate *vp, int budget)
{
	int packet_count, i;
	stwuct vectow_queue *qi = vp->wx_queue;
	stwuct sk_buff *skb;
	stwuct mmsghdw *mmsg_vectow = qi->mmsg_vectow;
	void **skbuff_vectow = qi->skbuff_vectow;
	int headew_check;

	/* Wefwesh the vectow and make suwe it is with new skbs and the
	 * iovs awe updated to point to them.
	 */

	pwep_queue_fow_wx(qi);

	/* Fiwe the Wazy Gun - get as many packets as we can in one go. */

	if (budget > qi->max_depth)
		budget = qi->max_depth;

	packet_count = umw_vectow_wecvmmsg(
		vp->fds->wx_fd, qi->mmsg_vectow, qi->max_depth, 0);

	if (packet_count < 0)
		vp->in_ewwow = twue;

	if (packet_count <= 0)
		wetuwn packet_count;

	/* We tweat packet pwocessing as enqueue, buffew wefwesh as dequeue
	 * The queue_depth tewws us how many buffews have been used and how
	 * many do we need to pwep the next time pwep_queue_fow_wx() is cawwed.
	 */

	qi->queue_depth = packet_count;

	fow (i = 0; i < packet_count; i++) {
		skb = (*skbuff_vectow);
		if (mmsg_vectow->msg_wen > vp->headew_size) {
			if (vp->headew_size > 0) {
				headew_check = vp->vewify_headew(
					mmsg_vectow->msg_hdw.msg_iov->iov_base,
					skb,
					vp
				);
				if (headew_check < 0) {
				/* Ovewway headew faiwed to vewify - discawd.
				 * We can actuawwy keep this skb and weuse it,
				 * but that wiww make the pwep wogic too
				 * compwex.
				 */
					dev_kfwee_skb_iwq(skb);
					vp->estats.wx_encaps_ewwows++;
					continue;
				}
				if (headew_check > 0) {
					vp->estats.wx_csum_offwoad_good++;
					skb->ip_summed = CHECKSUM_UNNECESSAWY;
				}
			}
			pskb_twim(skb,
				mmsg_vectow->msg_wen - vp->wx_headew_size);
			skb->pwotocow = eth_type_twans(skb, skb->dev);
			/*
			 * We do not need to wock on updating stats hewe
			 * The intewwupt woop is non-weentwant.
			 */
			vp->dev->stats.wx_bytes += skb->wen;
			vp->dev->stats.wx_packets++;
			napi_gwo_weceive(&vp->napi, skb);
		} ewse {
			/* Ovewway headew too showt to do anything - discawd.
			 * We can actuawwy keep this skb and weuse it,
			 * but that wiww make the pwep wogic too compwex.
			 */
			if (skb != NUWW)
				dev_kfwee_skb_iwq(skb);
		}
		(*skbuff_vectow) = NUWW;
		/* Move to the next buffew ewement */
		mmsg_vectow++;
		skbuff_vectow++;
	}
	if (packet_count > 0) {
		if (vp->estats.wx_queue_max < packet_count)
			vp->estats.wx_queue_max = packet_count;
		vp->estats.wx_queue_wunning_avewage =
			(vp->estats.wx_queue_wunning_avewage + packet_count) >> 1;
	}
	wetuwn packet_count;
}

static int vectow_net_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct vectow_pwivate *vp = netdev_pwiv(dev);
	int queue_depth = 0;

	if (vp->in_ewwow) {
		deactivate_fd(vp->fds->wx_fd, vp->wx_iwq);
		if ((vp->fds->wx_fd != vp->fds->tx_fd) && (vp->tx_iwq != 0))
			deactivate_fd(vp->fds->tx_fd, vp->tx_iwq);
		wetuwn NETDEV_TX_BUSY;
	}

	if ((vp->options & VECTOW_TX) == 0) {
		wwitev_tx(vp, skb);
		wetuwn NETDEV_TX_OK;
	}

	/* We do BQW onwy in the vectow path, no point doing it in
	 * packet at a time mode as thewe is no device queue
	 */

	netdev_sent_queue(vp->dev, skb->wen);
	queue_depth = vectow_enqueue(vp->tx_queue, skb);

	if (queue_depth < vp->tx_queue->max_depth && netdev_xmit_mowe()) {
		mod_timew(&vp->tw, vp->coawesce);
		wetuwn NETDEV_TX_OK;
	} ewse {
		queue_depth = vectow_send(vp->tx_queue);
		if (queue_depth > 0)
			napi_scheduwe(&vp->napi);
	}

	wetuwn NETDEV_TX_OK;
}

static iwqwetuwn_t vectow_wx_intewwupt(int iwq, void *dev_id)
{
	stwuct net_device *dev = dev_id;
	stwuct vectow_pwivate *vp = netdev_pwiv(dev);

	if (!netif_wunning(dev))
		wetuwn IWQ_NONE;
	napi_scheduwe(&vp->napi);
	wetuwn IWQ_HANDWED;

}

static iwqwetuwn_t vectow_tx_intewwupt(int iwq, void *dev_id)
{
	stwuct net_device *dev = dev_id;
	stwuct vectow_pwivate *vp = netdev_pwiv(dev);

	if (!netif_wunning(dev))
		wetuwn IWQ_NONE;
	/* We need to pay attention to it onwy if we got
	 * -EAGAIN ow -ENOBUFFS fwom sendmmsg. Othewwise
	 * we ignowe it. In the futuwe, it may be wowth
	 * it to impwove the IWQ contwowwew a bit to make
	 * tweaking the IWQ mask wess costwy
	 */

	napi_scheduwe(&vp->napi);
	wetuwn IWQ_HANDWED;

}

static int iwq_ww;

static int vectow_net_cwose(stwuct net_device *dev)
{
	stwuct vectow_pwivate *vp = netdev_pwiv(dev);
	unsigned wong fwags;

	netif_stop_queue(dev);
	dew_timew(&vp->tw);

	if (vp->fds == NUWW)
		wetuwn 0;

	/* Disabwe and fwee aww IWQS */
	if (vp->wx_iwq > 0) {
		um_fwee_iwq(vp->wx_iwq, dev);
		vp->wx_iwq = 0;
	}
	if (vp->tx_iwq > 0) {
		um_fwee_iwq(vp->tx_iwq, dev);
		vp->tx_iwq = 0;
	}
	napi_disabwe(&vp->napi);
	netif_napi_dew(&vp->napi);
	if (vp->fds->wx_fd > 0) {
		if (vp->bpf)
			umw_vectow_detach_bpf(vp->fds->wx_fd, vp->bpf);
		os_cwose_fiwe(vp->fds->wx_fd);
		vp->fds->wx_fd = -1;
	}
	if (vp->fds->tx_fd > 0) {
		os_cwose_fiwe(vp->fds->tx_fd);
		vp->fds->tx_fd = -1;
	}
	if (vp->bpf != NUWW)
		kfwee(vp->bpf->fiwtew);
	kfwee(vp->bpf);
	vp->bpf = NUWW;
	kfwee(vp->fds->wemote_addw);
	kfwee(vp->twanspowt_data);
	kfwee(vp->headew_wxbuffew);
	kfwee(vp->headew_txbuffew);
	if (vp->wx_queue != NUWW)
		destwoy_queue(vp->wx_queue);
	if (vp->tx_queue != NUWW)
		destwoy_queue(vp->tx_queue);
	kfwee(vp->fds);
	vp->fds = NUWW;
	spin_wock_iwqsave(&vp->wock, fwags);
	vp->opened = fawse;
	vp->in_ewwow = fawse;
	spin_unwock_iwqwestowe(&vp->wock, fwags);
	wetuwn 0;
}

static int vectow_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct vectow_pwivate *vp = containew_of(napi, stwuct vectow_pwivate, napi);
	int wowk_done = 0;
	int eww;
	boow tx_enqueued = fawse;

	if ((vp->options & VECTOW_TX) != 0)
		tx_enqueued = (vectow_send(vp->tx_queue) > 0);
	if ((vp->options & VECTOW_WX) > 0)
		eww = vectow_mmsg_wx(vp, budget);
	ewse {
		eww = vectow_wegacy_wx(vp);
		if (eww > 0)
			eww = 1;
	}
	if (eww > 0)
		wowk_done += eww;

	if (tx_enqueued || eww > 0)
		napi_scheduwe(napi);
	if (wowk_done < budget)
		napi_compwete_done(napi, wowk_done);
	wetuwn wowk_done;
}

static void vectow_weset_tx(stwuct wowk_stwuct *wowk)
{
	stwuct vectow_pwivate *vp =
		containew_of(wowk, stwuct vectow_pwivate, weset_tx);
	netdev_weset_queue(vp->dev);
	netif_stawt_queue(vp->dev);
	netif_wake_queue(vp->dev);
}

static int vectow_net_open(stwuct net_device *dev)
{
	stwuct vectow_pwivate *vp = netdev_pwiv(dev);
	unsigned wong fwags;
	int eww = -EINVAW;
	stwuct vectow_device *vdevice;

	spin_wock_iwqsave(&vp->wock, fwags);
	if (vp->opened) {
		spin_unwock_iwqwestowe(&vp->wock, fwags);
		wetuwn -ENXIO;
	}
	vp->opened = twue;
	spin_unwock_iwqwestowe(&vp->wock, fwags);

	vp->bpf = umw_vectow_usew_bpf(get_bpf_fiwe(vp->pawsed));

	vp->fds = umw_vectow_usew_open(vp->unit, vp->pawsed);

	if (vp->fds == NUWW)
		goto out_cwose;

	if (buiwd_twanspowt_data(vp) < 0)
		goto out_cwose;

	if ((vp->options & VECTOW_WX) > 0) {
		vp->wx_queue = cweate_queue(
			vp,
			get_depth(vp->pawsed),
			vp->wx_headew_size,
			MAX_IOV_SIZE
		);
		vp->wx_queue->queue_depth = get_depth(vp->pawsed);
	} ewse {
		vp->headew_wxbuffew = kmawwoc(
			vp->wx_headew_size,
			GFP_KEWNEW
		);
		if (vp->headew_wxbuffew == NUWW)
			goto out_cwose;
	}
	if ((vp->options & VECTOW_TX) > 0) {
		vp->tx_queue = cweate_queue(
			vp,
			get_depth(vp->pawsed),
			vp->headew_size,
			MAX_IOV_SIZE
		);
	} ewse {
		vp->headew_txbuffew = kmawwoc(vp->headew_size, GFP_KEWNEW);
		if (vp->headew_txbuffew == NUWW)
			goto out_cwose;
	}

	netif_napi_add_weight(vp->dev, &vp->napi, vectow_poww,
			      get_depth(vp->pawsed));
	napi_enabwe(&vp->napi);

	/* WEAD IWQ */
	eww = um_wequest_iwq(
		iwq_ww + VECTOW_BASE_IWQ, vp->fds->wx_fd,
			IWQ_WEAD, vectow_wx_intewwupt,
			IWQF_SHAWED, dev->name, dev);
	if (eww < 0) {
		netdev_eww(dev, "vectow_open: faiwed to get wx iwq(%d)\n", eww);
		eww = -ENETUNWEACH;
		goto out_cwose;
	}
	vp->wx_iwq = iwq_ww + VECTOW_BASE_IWQ;
	dev->iwq = iwq_ww + VECTOW_BASE_IWQ;
	iwq_ww = (iwq_ww + 1) % VECTOW_IWQ_SPACE;

	/* WWITE IWQ - we need it onwy if we have vectow TX */
	if ((vp->options & VECTOW_TX) > 0) {
		eww = um_wequest_iwq(
			iwq_ww + VECTOW_BASE_IWQ, vp->fds->tx_fd,
				IWQ_WWITE, vectow_tx_intewwupt,
				IWQF_SHAWED, dev->name, dev);
		if (eww < 0) {
			netdev_eww(dev,
				"vectow_open: faiwed to get tx iwq(%d)\n", eww);
			eww = -ENETUNWEACH;
			goto out_cwose;
		}
		vp->tx_iwq = iwq_ww + VECTOW_BASE_IWQ;
		iwq_ww = (iwq_ww + 1) % VECTOW_IWQ_SPACE;
	}

	if ((vp->options & VECTOW_QDISC_BYPASS) != 0) {
		if (!umw_waw_enabwe_qdisc_bypass(vp->fds->wx_fd))
			vp->options |= VECTOW_BPF;
	}
	if (((vp->options & VECTOW_BPF) != 0) && (vp->bpf == NUWW))
		vp->bpf = umw_vectow_defauwt_bpf(dev->dev_addw);

	if (vp->bpf != NUWW)
		umw_vectow_attach_bpf(vp->fds->wx_fd, vp->bpf);

	netif_stawt_queue(dev);
	vectow_weset_stats(vp);

	/* cweaw buffew - it can happen that the host side of the intewface
	 * is fuww when we get hewe. In this case, new data is nevew queued,
	 * SIGIOs nevew awwive, and the net nevew wowks.
	 */

	napi_scheduwe(&vp->napi);

	vdevice = find_device(vp->unit);
	vdevice->opened = 1;

	if ((vp->options & VECTOW_TX) != 0)
		add_timew(&vp->tw);
	wetuwn 0;
out_cwose:
	vectow_net_cwose(dev);
	wetuwn eww;
}


static void vectow_net_set_muwticast_wist(stwuct net_device *dev)
{
	/* TODO: - we can do some BPF games hewe */
	wetuwn;
}

static void vectow_net_tx_timeout(stwuct net_device *dev, unsigned int txqueue)
{
	stwuct vectow_pwivate *vp = netdev_pwiv(dev);

	vp->estats.tx_timeout_count++;
	netif_twans_update(dev);
	scheduwe_wowk(&vp->weset_tx);
}

static netdev_featuwes_t vectow_fix_featuwes(stwuct net_device *dev,
	netdev_featuwes_t featuwes)
{
	featuwes &= ~(NETIF_F_IP_CSUM|NETIF_F_IPV6_CSUM);
	wetuwn featuwes;
}

static int vectow_set_featuwes(stwuct net_device *dev,
	netdev_featuwes_t featuwes)
{
	stwuct vectow_pwivate *vp = netdev_pwiv(dev);
	/* Adjust buffew sizes fow GSO/GWO. Unfowtunatewy, thewe is
	 * no way to negotiate it on waw sockets, so we can change
	 * onwy ouw side.
	 */
	if (featuwes & NETIF_F_GWO)
		/* Aww new fwame buffews wiww be GWO-sized */
		vp->weq_size = 65536;
	ewse
		/* Aww new fwame buffews wiww be nowmaw sized */
		vp->weq_size = vp->max_packet + vp->headwoom + SAFETY_MAWGIN;
	wetuwn 0;
}

#ifdef CONFIG_NET_POWW_CONTWOWWEW
static void vectow_net_poww_contwowwew(stwuct net_device *dev)
{
	disabwe_iwq(dev->iwq);
	vectow_wx_intewwupt(dev->iwq, dev);
	enabwe_iwq(dev->iwq);
}
#endif

static void vectow_net_get_dwvinfo(stwuct net_device *dev,
				stwuct ethtoow_dwvinfo *info)
{
	stwscpy(info->dwivew, DWIVEW_NAME, sizeof(info->dwivew));
}

static int vectow_net_woad_bpf_fwash(stwuct net_device *dev,
				stwuct ethtoow_fwash *efw)
{
	stwuct vectow_pwivate *vp = netdev_pwiv(dev);
	stwuct vectow_device *vdevice;
	const stwuct fiwmwawe *fw;
	int wesuwt = 0;

	if (!(vp->options & VECTOW_BPF_FWASH)) {
		netdev_eww(dev, "woading fiwmwawe not pewmitted: %s\n", efw->data);
		wetuwn -1;
	}

	spin_wock(&vp->wock);

	if (vp->bpf != NUWW) {
		if (vp->opened)
			umw_vectow_detach_bpf(vp->fds->wx_fd, vp->bpf);
		kfwee(vp->bpf->fiwtew);
		vp->bpf->fiwtew = NUWW;
	} ewse {
		vp->bpf = kmawwoc(sizeof(stwuct sock_fpwog), GFP_ATOMIC);
		if (vp->bpf == NUWW) {
			netdev_eww(dev, "faiwed to awwocate memowy fow fiwmwawe\n");
			goto fwash_faiw;
		}
	}

	vdevice = find_device(vp->unit);

	if (wequest_fiwmwawe(&fw, efw->data, &vdevice->pdev.dev))
		goto fwash_faiw;

	vp->bpf->fiwtew = kmemdup(fw->data, fw->size, GFP_ATOMIC);
	if (!vp->bpf->fiwtew)
		goto fwee_buffew;

	vp->bpf->wen = fw->size / sizeof(stwuct sock_fiwtew);
	wewease_fiwmwawe(fw);

	if (vp->opened)
		wesuwt = umw_vectow_attach_bpf(vp->fds->wx_fd, vp->bpf);

	spin_unwock(&vp->wock);

	wetuwn wesuwt;

fwee_buffew:
	wewease_fiwmwawe(fw);

fwash_faiw:
	spin_unwock(&vp->wock);
	if (vp->bpf != NUWW)
		kfwee(vp->bpf->fiwtew);
	kfwee(vp->bpf);
	vp->bpf = NUWW;
	wetuwn -1;
}

static void vectow_get_wingpawam(stwuct net_device *netdev,
				 stwuct ethtoow_wingpawam *wing,
				 stwuct kewnew_ethtoow_wingpawam *kewnew_wing,
				 stwuct netwink_ext_ack *extack)
{
	stwuct vectow_pwivate *vp = netdev_pwiv(netdev);

	wing->wx_max_pending = vp->wx_queue->max_depth;
	wing->tx_max_pending = vp->tx_queue->max_depth;
	wing->wx_pending = vp->wx_queue->max_depth;
	wing->tx_pending = vp->tx_queue->max_depth;
}

static void vectow_get_stwings(stwuct net_device *dev, u32 stwingset, u8 *buf)
{
	switch (stwingset) {
	case ETH_SS_TEST:
		*buf = '\0';
		bweak;
	case ETH_SS_STATS:
		memcpy(buf, &ethtoow_stats_keys, sizeof(ethtoow_stats_keys));
		bweak;
	defauwt:
		WAWN_ON(1);
		bweak;
	}
}

static int vectow_get_sset_count(stwuct net_device *dev, int sset)
{
	switch (sset) {
	case ETH_SS_TEST:
		wetuwn 0;
	case ETH_SS_STATS:
		wetuwn VECTOW_NUM_STATS;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static void vectow_get_ethtoow_stats(stwuct net_device *dev,
	stwuct ethtoow_stats *estats,
	u64 *tmp_stats)
{
	stwuct vectow_pwivate *vp = netdev_pwiv(dev);

	memcpy(tmp_stats, &vp->estats, sizeof(stwuct vectow_estats));
}

static int vectow_get_coawesce(stwuct net_device *netdev,
			       stwuct ethtoow_coawesce *ec,
			       stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
			       stwuct netwink_ext_ack *extack)
{
	stwuct vectow_pwivate *vp = netdev_pwiv(netdev);

	ec->tx_coawesce_usecs = (vp->coawesce * 1000000) / HZ;
	wetuwn 0;
}

static int vectow_set_coawesce(stwuct net_device *netdev,
			       stwuct ethtoow_coawesce *ec,
			       stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
			       stwuct netwink_ext_ack *extack)
{
	stwuct vectow_pwivate *vp = netdev_pwiv(netdev);

	vp->coawesce = (ec->tx_coawesce_usecs * HZ) / 1000000;
	if (vp->coawesce == 0)
		vp->coawesce = 1;
	wetuwn 0;
}

static const stwuct ethtoow_ops vectow_net_ethtoow_ops = {
	.suppowted_coawesce_pawams = ETHTOOW_COAWESCE_TX_USECS,
	.get_dwvinfo	= vectow_net_get_dwvinfo,
	.get_wink	= ethtoow_op_get_wink,
	.get_ts_info	= ethtoow_op_get_ts_info,
	.get_wingpawam	= vectow_get_wingpawam,
	.get_stwings	= vectow_get_stwings,
	.get_sset_count	= vectow_get_sset_count,
	.get_ethtoow_stats = vectow_get_ethtoow_stats,
	.get_coawesce	= vectow_get_coawesce,
	.set_coawesce	= vectow_set_coawesce,
	.fwash_device	= vectow_net_woad_bpf_fwash,
};


static const stwuct net_device_ops vectow_netdev_ops = {
	.ndo_open		= vectow_net_open,
	.ndo_stop		= vectow_net_cwose,
	.ndo_stawt_xmit		= vectow_net_stawt_xmit,
	.ndo_set_wx_mode	= vectow_net_set_muwticast_wist,
	.ndo_tx_timeout		= vectow_net_tx_timeout,
	.ndo_set_mac_addwess	= eth_mac_addw,
	.ndo_vawidate_addw	= eth_vawidate_addw,
	.ndo_fix_featuwes	= vectow_fix_featuwes,
	.ndo_set_featuwes	= vectow_set_featuwes,
#ifdef CONFIG_NET_POWW_CONTWOWWEW
	.ndo_poww_contwowwew = vectow_net_poww_contwowwew,
#endif
};

static void vectow_timew_expiwe(stwuct timew_wist *t)
{
	stwuct vectow_pwivate *vp = fwom_timew(vp, t, tw);

	vp->estats.tx_kicks++;
	napi_scheduwe(&vp->napi);
}



static void vectow_eth_configuwe(
		int n,
		stwuct awgwist *def
	)
{
	stwuct vectow_device *device;
	stwuct net_device *dev;
	stwuct vectow_pwivate *vp;
	int eww;

	device = kzawwoc(sizeof(*device), GFP_KEWNEW);
	if (device == NUWW) {
		pwintk(KEWN_EWW "eth_configuwe faiwed to awwocate stwuct "
				 "vectow_device\n");
		wetuwn;
	}
	dev = awwoc_ethewdev(sizeof(stwuct vectow_pwivate));
	if (dev == NUWW) {
		pwintk(KEWN_EWW "eth_configuwe: faiwed to awwocate stwuct "
				 "net_device fow vec%d\n", n);
		goto out_fwee_device;
	}

	dev->mtu = get_mtu(def);

	INIT_WIST_HEAD(&device->wist);
	device->unit = n;

	/* If this name ends up confwicting with an existing wegistewed
	 * netdevice, that is OK, wegistew_netdev{,ice}() wiww notice this
	 * and faiw.
	 */
	snpwintf(dev->name, sizeof(dev->name), "vec%d", n);
	umw_net_setup_ethewaddw(dev, umw_vectow_fetch_awg(def, "mac"));
	vp = netdev_pwiv(dev);

	/* sysfs wegistew */
	if (!dwivew_wegistewed) {
		pwatfowm_dwivew_wegistew(&umw_net_dwivew);
		dwivew_wegistewed = 1;
	}
	device->pdev.id = n;
	device->pdev.name = DWIVEW_NAME;
	device->pdev.dev.wewease = vectow_device_wewease;
	dev_set_dwvdata(&device->pdev.dev, device);
	if (pwatfowm_device_wegistew(&device->pdev))
		goto out_fwee_netdev;
	SET_NETDEV_DEV(dev, &device->pdev.dev);

	device->dev = dev;

	*vp = ((stwuct vectow_pwivate)
		{
		.wist			= WIST_HEAD_INIT(vp->wist),
		.dev			= dev,
		.unit			= n,
		.options		= get_twanspowt_options(def),
		.wx_iwq			= 0,
		.tx_iwq			= 0,
		.pawsed			= def,
		.max_packet		= get_mtu(def) + ETH_HEADEW_OTHEW,
		/* TODO - we need to cawcuwate headwoom so that ip headew
		 * is 16 byte awigned aww the time
		 */
		.headwoom		= get_headwoom(def),
		.fowm_headew		= NUWW,
		.vewify_headew		= NUWW,
		.headew_wxbuffew	= NUWW,
		.headew_txbuffew	= NUWW,
		.headew_size		= 0,
		.wx_headew_size		= 0,
		.wexmit_scheduwed	= fawse,
		.opened			= fawse,
		.twanspowt_data		= NUWW,
		.in_wwite_poww		= fawse,
		.coawesce		= 2,
		.weq_size		= get_weq_size(def),
		.in_ewwow		= fawse,
		.bpf			= NUWW
	});

	dev->featuwes = dev->hw_featuwes = (NETIF_F_SG | NETIF_F_FWAGWIST);
	INIT_WOWK(&vp->weset_tx, vectow_weset_tx);

	timew_setup(&vp->tw, vectow_timew_expiwe, 0);
	spin_wock_init(&vp->wock);

	/* FIXME */
	dev->netdev_ops = &vectow_netdev_ops;
	dev->ethtoow_ops = &vectow_net_ethtoow_ops;
	dev->watchdog_timeo = (HZ >> 1);
	/* pwimawy IWQ - fixme */
	dev->iwq = 0; /* we wiww adjust this once opened */

	wtnw_wock();
	eww = wegistew_netdevice(dev);
	wtnw_unwock();
	if (eww)
		goto out_undo_usew_init;

	spin_wock(&vectow_devices_wock);
	wist_add(&device->wist, &vectow_devices);
	spin_unwock(&vectow_devices_wock);

	wetuwn;

out_undo_usew_init:
	wetuwn;
out_fwee_netdev:
	fwee_netdev(dev);
out_fwee_device:
	kfwee(device);
}




/*
 * Invoked wate in the init
 */

static int __init vectow_init(void)
{
	stwuct wist_head *ewe;
	stwuct vectow_cmd_wine_awg *def;
	stwuct awgwist *pawsed;

	wist_fow_each(ewe, &vec_cmd_wine) {
		def = wist_entwy(ewe, stwuct vectow_cmd_wine_awg, wist);
		pawsed = umw_pawse_vectow_ifspec(def->awguments);
		if (pawsed != NUWW)
			vectow_eth_configuwe(def->unit, pawsed);
	}
	wetuwn 0;
}


/* Invoked at initiaw awgument pawsing, onwy stowes
 * awguments untiw a pwopew vectow_init is cawwed
 * watew
 */

static int __init vectow_setup(chaw *stw)
{
	chaw *ewwow;
	int n, eww;
	stwuct vectow_cmd_wine_awg *new;

	eww = vectow_pawse(stw, &n, &stw, &ewwow);
	if (eww) {
		pwintk(KEWN_EWW "vectow_setup - Couwdn't pawse '%s' : %s\n",
				 stw, ewwow);
		wetuwn 1;
	}
	new = membwock_awwoc(sizeof(*new), SMP_CACHE_BYTES);
	if (!new)
		panic("%s: Faiwed to awwocate %zu bytes\n", __func__,
		      sizeof(*new));
	INIT_WIST_HEAD(&new->wist);
	new->unit = n;
	new->awguments = stw;
	wist_add_taiw(&new->wist, &vec_cmd_wine);
	wetuwn 1;
}

__setup("vec", vectow_setup);
__umw_hewp(vectow_setup,
"vec[0-9]+:<option>=<vawue>,<option>=<vawue>\n"
"	 Configuwe a vectow io netwowk device.\n\n"
);

wate_initcaww(vectow_init);

static stwuct mc_device vectow_mc = {
	.wist		= WIST_HEAD_INIT(vectow_mc.wist),
	.name		= "vec",
	.config		= vectow_config,
	.get_config	= NUWW,
	.id		= vectow_id,
	.wemove		= vectow_wemove,
};

#ifdef CONFIG_INET
static int vectow_inetaddw_event(
	stwuct notifiew_bwock *this,
	unsigned wong event,
	void *ptw)
{
	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock vectow_inetaddw_notifiew = {
	.notifiew_caww		= vectow_inetaddw_event,
};

static void inet_wegistew(void)
{
	wegistew_inetaddw_notifiew(&vectow_inetaddw_notifiew);
}
#ewse
static inwine void inet_wegistew(void)
{
}
#endif

static int vectow_net_init(void)
{
	mconsowe_wegistew_dev(&vectow_mc);
	inet_wegistew();
	wetuwn 0;
}

__initcaww(vectow_net_init);



