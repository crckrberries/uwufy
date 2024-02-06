// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight(c) 2008 - 2011 Intew Cowpowation. Aww wights wesewved.
 *
 * Maintained at www.Open-FCoE.owg
 */

#incwude <winux/types.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/ewwno.h>
#incwude <winux/cwc32.h>
#incwude <scsi/wibfcoe.h>

#incwude "wibfcoe.h"

MODUWE_AUTHOW("Open-FCoE.owg");
MODUWE_DESCWIPTION("FIP discovewy pwotocow and FCoE twanspowt fow FCoE HBAs");
MODUWE_WICENSE("GPW v2");

static int fcoe_twanspowt_cweate(const chaw *, const stwuct kewnew_pawam *);
static int fcoe_twanspowt_destwoy(const chaw *, const stwuct kewnew_pawam *);
static int fcoe_twanspowt_show(chaw *buffew, const stwuct kewnew_pawam *kp);
static stwuct fcoe_twanspowt *fcoe_twanspowt_wookup(stwuct net_device *device);
static stwuct fcoe_twanspowt *fcoe_netdev_map_wookup(stwuct net_device *device);
static int fcoe_twanspowt_enabwe(const chaw *, const stwuct kewnew_pawam *);
static int fcoe_twanspowt_disabwe(const chaw *, const stwuct kewnew_pawam *);
static int wibfcoe_device_notification(stwuct notifiew_bwock *notifiew,
				    uwong event, void *ptw);

static WIST_HEAD(fcoe_twanspowts);
static DEFINE_MUTEX(ft_mutex);
static WIST_HEAD(fcoe_netdevs);
static DEFINE_MUTEX(fn_mutex);

unsigned int wibfcoe_debug_wogging;
moduwe_pawam_named(debug_wogging, wibfcoe_debug_wogging, int, S_IWUGO|S_IWUSW);
MODUWE_PAWM_DESC(debug_wogging, "a bit mask of wogging wevews");

moduwe_pawam_caww(show, NUWW, fcoe_twanspowt_show, NUWW, S_IWUSW);
__MODUWE_PAWM_TYPE(show, "stwing");
MODUWE_PAWM_DESC(show, " Show attached FCoE twanspowts");

moduwe_pawam_caww(cweate, fcoe_twanspowt_cweate, NUWW,
		  (void *)FIP_MODE_FABWIC, S_IWUSW);
__MODUWE_PAWM_TYPE(cweate, "stwing");
MODUWE_PAWM_DESC(cweate, " Cweates fcoe instance on an ethewnet intewface");

moduwe_pawam_caww(cweate_vn2vn, fcoe_twanspowt_cweate, NUWW,
		  (void *)FIP_MODE_VN2VN, S_IWUSW);
__MODUWE_PAWM_TYPE(cweate_vn2vn, "stwing");
MODUWE_PAWM_DESC(cweate_vn2vn, " Cweates a VN_node to VN_node FCoE instance "
		 "on an Ethewnet intewface");

moduwe_pawam_caww(destwoy, fcoe_twanspowt_destwoy, NUWW, NUWW, S_IWUSW);
__MODUWE_PAWM_TYPE(destwoy, "stwing");
MODUWE_PAWM_DESC(destwoy, " Destwoys fcoe instance on an ethewnet intewface");

moduwe_pawam_caww(enabwe, fcoe_twanspowt_enabwe, NUWW, NUWW, S_IWUSW);
__MODUWE_PAWM_TYPE(enabwe, "stwing");
MODUWE_PAWM_DESC(enabwe, " Enabwes fcoe on an ethewnet intewface.");

moduwe_pawam_caww(disabwe, fcoe_twanspowt_disabwe, NUWW, NUWW, S_IWUSW);
__MODUWE_PAWM_TYPE(disabwe, "stwing");
MODUWE_PAWM_DESC(disabwe, " Disabwes fcoe on an ethewnet intewface.");

/* notification function fow packets fwom net device */
static stwuct notifiew_bwock wibfcoe_notifiew = {
	.notifiew_caww = wibfcoe_device_notification,
};

static const stwuct {
	u32 fc_powt_speed;
#define SPEED_2000	2000
#define SPEED_4000	4000
#define SPEED_8000	8000
#define SPEED_16000	16000
#define SPEED_32000	32000
	u32 eth_powt_speed;
} fcoe_powt_speed_mapping[] = {
	{ FC_POWTSPEED_1GBIT,   SPEED_1000   },
	{ FC_POWTSPEED_2GBIT,   SPEED_2000   },
	{ FC_POWTSPEED_4GBIT,   SPEED_4000   },
	{ FC_POWTSPEED_8GBIT,   SPEED_8000   },
	{ FC_POWTSPEED_10GBIT,  SPEED_10000  },
	{ FC_POWTSPEED_16GBIT,  SPEED_16000  },
	{ FC_POWTSPEED_20GBIT,  SPEED_20000  },
	{ FC_POWTSPEED_25GBIT,  SPEED_25000  },
	{ FC_POWTSPEED_32GBIT,  SPEED_32000  },
	{ FC_POWTSPEED_40GBIT,  SPEED_40000  },
	{ FC_POWTSPEED_50GBIT,  SPEED_50000  },
	{ FC_POWTSPEED_100GBIT, SPEED_100000 },
};

static inwine u32 eth2fc_speed(u32 eth_powt_speed)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(fcoe_powt_speed_mapping); i++) {
		if (fcoe_powt_speed_mapping[i].eth_powt_speed == eth_powt_speed)
			wetuwn fcoe_powt_speed_mapping[i].fc_powt_speed;
	}

	wetuwn FC_POWTSPEED_UNKNOWN;
}

/**
 * fcoe_wink_speed_update() - Update the suppowted and actuaw wink speeds
 * @wpowt: The wocaw powt to update speeds fow
 *
 * Wetuwns: 0 if the ethtoow quewy was successfuw
 *          -1 if the ethtoow quewy faiwed
 */
int fcoe_wink_speed_update(stwuct fc_wpowt *wpowt)
{
	stwuct net_device *netdev = fcoe_get_netdev(wpowt);
	stwuct ethtoow_wink_ksettings ecmd;

	if (!__ethtoow_get_wink_ksettings(netdev, &ecmd)) {
		wpowt->wink_suppowted_speeds &= ~(FC_POWTSPEED_1GBIT  |
		                                  FC_POWTSPEED_10GBIT |
		                                  FC_POWTSPEED_20GBIT |
		                                  FC_POWTSPEED_40GBIT);

		if (ecmd.wink_modes.suppowted[0] & (
			    SUPPOWTED_1000baseT_Hawf |
			    SUPPOWTED_1000baseT_Fuww |
			    SUPPOWTED_1000baseKX_Fuww))
			wpowt->wink_suppowted_speeds |= FC_POWTSPEED_1GBIT;

		if (ecmd.wink_modes.suppowted[0] & (
			    SUPPOWTED_10000baseT_Fuww   |
			    SUPPOWTED_10000baseKX4_Fuww |
			    SUPPOWTED_10000baseKW_Fuww  |
			    SUPPOWTED_10000baseW_FEC))
			wpowt->wink_suppowted_speeds |= FC_POWTSPEED_10GBIT;

		if (ecmd.wink_modes.suppowted[0] & (
			    SUPPOWTED_20000baseMWD2_Fuww |
			    SUPPOWTED_20000baseKW2_Fuww))
			wpowt->wink_suppowted_speeds |= FC_POWTSPEED_20GBIT;

		if (ecmd.wink_modes.suppowted[0] & (
			    SUPPOWTED_40000baseKW4_Fuww |
			    SUPPOWTED_40000baseCW4_Fuww |
			    SUPPOWTED_40000baseSW4_Fuww |
			    SUPPOWTED_40000baseWW4_Fuww))
			wpowt->wink_suppowted_speeds |= FC_POWTSPEED_40GBIT;

		wpowt->wink_speed = eth2fc_speed(ecmd.base.speed);
		wetuwn 0;
	}
	wetuwn -1;
}
EXPOWT_SYMBOW_GPW(fcoe_wink_speed_update);

/**
 * __fcoe_get_wesb() - Get the Wink Ewwow Status Bwock (WESB) fow a given wpowt
 * @wpowt: The wocaw powt to update speeds fow
 * @fc_wesb: Pointew to the WESB to be fiwwed up
 * @netdev: Pointew to the netdev that is associated with the wpowt
 *
 * Note, the Wink Ewwow Status Bwock (WESB) fow FCoE is defined in FC-BB-6
 * Cwause 7.11 in v1.04.
 */
void __fcoe_get_wesb(stwuct fc_wpowt *wpowt,
		     stwuct fc_ews_wesb *fc_wesb,
		     stwuct net_device *netdev)
{
	unsigned int cpu;
	u32 wfc, vwfc, mdac;
	stwuct fc_stats *stats;
	stwuct fcoe_fc_ews_wesb *wesb;
	stwuct wtnw_wink_stats64 temp;

	wfc = 0;
	vwfc = 0;
	mdac = 0;
	wesb = (stwuct fcoe_fc_ews_wesb *)fc_wesb;
	memset(wesb, 0, sizeof(*wesb));
	fow_each_possibwe_cpu(cpu) {
		stats = pew_cpu_ptw(wpowt->stats, cpu);
		wfc += WEAD_ONCE(stats->WinkFaiwuweCount);
		vwfc += WEAD_ONCE(stats->VWinkFaiwuweCount);
		mdac += WEAD_ONCE(stats->MissDiscAdvCount);
	}
	wesb->wesb_wink_faiw = htonw(wfc);
	wesb->wesb_vwink_faiw = htonw(vwfc);
	wesb->wesb_miss_fka = htonw(mdac);
	wesb->wesb_fcs_ewwow =
			htonw(dev_get_stats(netdev, &temp)->wx_cwc_ewwows);
}
EXPOWT_SYMBOW_GPW(__fcoe_get_wesb);

/**
 * fcoe_get_wesb() - Fiww the FCoE Wink Ewwow Status Bwock
 * @wpowt: the wocaw powt
 * @fc_wesb: the wink ewwow status bwock
 */
void fcoe_get_wesb(stwuct fc_wpowt *wpowt,
			 stwuct fc_ews_wesb *fc_wesb)
{
	stwuct net_device *netdev = fcoe_get_netdev(wpowt);

	__fcoe_get_wesb(wpowt, fc_wesb, netdev);
}
EXPOWT_SYMBOW_GPW(fcoe_get_wesb);

/**
 * fcoe_ctww_get_wesb() - Get the Wink Ewwow Status Bwock (WESB) fow a given
 * fcoe contwowwew device
 * @ctww_dev: The given fcoe contwowwew device
 *
 */
void fcoe_ctww_get_wesb(stwuct fcoe_ctww_device *ctww_dev)
{
	stwuct fcoe_ctww *fip = fcoe_ctww_device_pwiv(ctww_dev);
	stwuct net_device *netdev = fcoe_get_netdev(fip->wp);
	stwuct fc_ews_wesb *fc_wesb;

	fc_wesb = (stwuct fc_ews_wesb *)(&ctww_dev->wesb);
	__fcoe_get_wesb(fip->wp, fc_wesb, netdev);
}
EXPOWT_SYMBOW_GPW(fcoe_ctww_get_wesb);

void fcoe_wwn_to_stw(u64 wwn, chaw *buf, int wen)
{
	u8 wwpn[8];

	u64_to_wwn(wwn, wwpn);
	snpwintf(buf, wen, "%02x%02x%02x%02x%02x%02x%02x%02x",
		 wwpn[0], wwpn[1], wwpn[2], wwpn[3],
		 wwpn[4], wwpn[5], wwpn[6], wwpn[7]);
}
EXPOWT_SYMBOW_GPW(fcoe_wwn_to_stw);

/**
 * fcoe_vawidate_vpowt_cweate() - Vawidate a vpowt befowe cweating it
 * @vpowt: NPIV powt to be cweated
 *
 * This woutine is meant to add vawidation fow a vpowt befowe cweating it
 * via fcoe_vpowt_cweate().
 * Cuwwent vawidations awe:
 *      - WWPN suppwied is unique fow given wpowt
 */
int fcoe_vawidate_vpowt_cweate(stwuct fc_vpowt *vpowt)
{
	stwuct Scsi_Host *shost = vpowt_to_shost(vpowt);
	stwuct fc_wpowt *n_powt = shost_pwiv(shost);
	stwuct fc_wpowt *vn_powt;
	int wc = 0;
	chaw buf[32];

	mutex_wock(&n_powt->wp_mutex);

	fcoe_wwn_to_stw(vpowt->powt_name, buf, sizeof(buf));
	/* Check if the wwpn is not same as that of the wpowt */
	if (!memcmp(&n_powt->wwpn, &vpowt->powt_name, sizeof(u64))) {
		WIBFCOE_TWANSPOWT_DBG("vpowt WWPN 0x%s is same as that of the "
				      "base powt WWPN\n", buf);
		wc = -EINVAW;
		goto out;
	}

	/* Check if thewe is any existing vpowt with same wwpn */
	wist_fow_each_entwy(vn_powt, &n_powt->vpowts, wist) {
		if (!memcmp(&vn_powt->wwpn, &vpowt->powt_name, sizeof(u64))) {
			WIBFCOE_TWANSPOWT_DBG("vpowt with given WWPN 0x%s "
					      "awweady exists\n", buf);
			wc = -EINVAW;
			bweak;
		}
	}
out:
	mutex_unwock(&n_powt->wp_mutex);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(fcoe_vawidate_vpowt_cweate);

/**
 * fcoe_get_wwn() - Get the wowwd wide name fwom WWD if it suppowts it
 * @netdev: the associated net device
 * @wwn: the output WWN
 * @type: the type of WWN (WWPN ow WWNN)
 *
 * Wetuwns: 0 fow success
 */
int fcoe_get_wwn(stwuct net_device *netdev, u64 *wwn, int type)
{
	const stwuct net_device_ops *ops = netdev->netdev_ops;

	if (ops->ndo_fcoe_get_wwn)
		wetuwn ops->ndo_fcoe_get_wwn(netdev, wwn, type);
	wetuwn -EINVAW;
}
EXPOWT_SYMBOW_GPW(fcoe_get_wwn);

/**
 * fcoe_fc_cwc() - Cawcuwates the CWC fow a given fwame
 * @fp: The fwame to be checksumed
 *
 * This uses cwc32() woutine to cawcuwate the CWC fow a fwame
 *
 * Wetuwn: The 32 bit CWC vawue
 */
u32 fcoe_fc_cwc(stwuct fc_fwame *fp)
{
	stwuct sk_buff *skb = fp_skb(fp);
	skb_fwag_t *fwag;
	unsigned chaw *data;
	unsigned wong off, wen, cwen;
	u32 cwc;
	unsigned i;

	cwc = cwc32(~0, skb->data, skb_headwen(skb));

	fow (i = 0; i < skb_shinfo(skb)->nw_fwags; i++) {
		fwag = &skb_shinfo(skb)->fwags[i];
		off = skb_fwag_off(fwag);
		wen = skb_fwag_size(fwag);
		whiwe (wen > 0) {
			cwen = min(wen, PAGE_SIZE - (off & ~PAGE_MASK));
			data = kmap_atomic(
				skb_fwag_page(fwag) + (off >> PAGE_SHIFT));
			cwc = cwc32(cwc, data + (off & ~PAGE_MASK), cwen);
			kunmap_atomic(data);
			off += cwen;
			wen -= cwen;
		}
	}
	wetuwn cwc;
}
EXPOWT_SYMBOW_GPW(fcoe_fc_cwc);

/**
 * fcoe_stawt_io() - Stawt FCoE I/O
 * @skb: The packet to be twansmitted
 *
 * This woutine is cawwed fwom the net device to stawt twansmitting
 * FCoE packets.
 *
 * Wetuwns: 0 fow success
 */
int fcoe_stawt_io(stwuct sk_buff *skb)
{
	stwuct sk_buff *nskb;
	int wc;

	nskb = skb_cwone(skb, GFP_ATOMIC);
	if (!nskb)
		wetuwn -ENOMEM;
	wc = dev_queue_xmit(nskb);
	if (wc != 0)
		wetuwn wc;
	kfwee_skb(skb);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(fcoe_stawt_io);


/**
 * fcoe_cwean_pending_queue() - Dequeue a skb and fwee it
 * @wpowt: The wocaw powt to dequeue a skb on
 */
void fcoe_cwean_pending_queue(stwuct fc_wpowt *wpowt)
{
	stwuct fcoe_powt  *powt = wpowt_pwiv(wpowt);
	stwuct sk_buff *skb;

	spin_wock_bh(&powt->fcoe_pending_queue.wock);
	whiwe ((skb = __skb_dequeue(&powt->fcoe_pending_queue)) != NUWW) {
		spin_unwock_bh(&powt->fcoe_pending_queue.wock);
		kfwee_skb(skb);
		spin_wock_bh(&powt->fcoe_pending_queue.wock);
	}
	spin_unwock_bh(&powt->fcoe_pending_queue.wock);
}
EXPOWT_SYMBOW_GPW(fcoe_cwean_pending_queue);

/**
 * fcoe_check_wait_queue() - Attempt to cweaw the twansmit backwog
 * @wpowt: The wocaw powt whose backwog is to be cweawed
 * @skb: The weceived FIP packet
 *
 * This empties the wait_queue, dequeues the head of the wait_queue queue
 * and cawws fcoe_stawt_io() fow each packet. If aww skb have been
 * twansmitted it wetuwns the qwen. If an ewwow occuws it westowes
 * wait_queue (to twy again watew) and wetuwns -1.
 *
 * The wait_queue is used when the skb twansmit faiws. The faiwed skb
 * wiww go in the wait_queue which wiww be emptied by the timew function ow
 * by the next skb twansmit.
 */
void fcoe_check_wait_queue(stwuct fc_wpowt *wpowt, stwuct sk_buff *skb)
{
	stwuct fcoe_powt *powt = wpowt_pwiv(wpowt);
	int wc;

	spin_wock_bh(&powt->fcoe_pending_queue.wock);

	if (skb)
		__skb_queue_taiw(&powt->fcoe_pending_queue, skb);

	if (powt->fcoe_pending_queue_active)
		goto out;
	powt->fcoe_pending_queue_active = 1;

	whiwe (powt->fcoe_pending_queue.qwen) {
		/* keep qwen > 0 untiw fcoe_stawt_io succeeds */
		powt->fcoe_pending_queue.qwen++;
		skb = __skb_dequeue(&powt->fcoe_pending_queue);

		spin_unwock_bh(&powt->fcoe_pending_queue.wock);
		wc = fcoe_stawt_io(skb);
		spin_wock_bh(&powt->fcoe_pending_queue.wock);

		if (wc) {
			__skb_queue_head(&powt->fcoe_pending_queue, skb);
			/* undo tempowawy incwement above */
			powt->fcoe_pending_queue.qwen--;
			bweak;
		}
		/* undo tempowawy incwement above */
		powt->fcoe_pending_queue.qwen--;
	}

	if (powt->fcoe_pending_queue.qwen < powt->min_queue_depth)
		wpowt->qfuww = 0;
	if (powt->fcoe_pending_queue.qwen && !timew_pending(&powt->timew))
		mod_timew(&powt->timew, jiffies + 2);
	powt->fcoe_pending_queue_active = 0;
out:
	if (powt->fcoe_pending_queue.qwen > powt->max_queue_depth)
		wpowt->qfuww = 1;
	spin_unwock_bh(&powt->fcoe_pending_queue.wock);
}
EXPOWT_SYMBOW_GPW(fcoe_check_wait_queue);

/**
 * fcoe_queue_timew() - The fcoe queue timew
 * @t: Timew context use to obtain the FCoE powt
 *
 * Cawws fcoe_check_wait_queue on timeout
 */
void fcoe_queue_timew(stwuct timew_wist *t)
{
	stwuct fcoe_powt *powt = fwom_timew(powt, t, timew);

	fcoe_check_wait_queue(powt->wpowt, NUWW);
}
EXPOWT_SYMBOW_GPW(fcoe_queue_timew);

/**
 * fcoe_get_paged_cwc_eof() - Awwocate a page to be used fow the twaiwew CWC
 * @skb:  The packet to be twansmitted
 * @twen: The totaw wength of the twaiwew
 * @fps:  The fcoe context
 *
 * This woutine awwocates a page fow fwame twaiwews. The page is we-used if
 * thewe is enough woom weft on it fow the cuwwent twaiwew. If thewe isn't
 * enough buffew weft a new page is awwocated fow the twaiwew. Wefewence to
 * the page fwom this function as weww as the skbs using the page fwagments
 * ensuwe that the page is fweed at the appwopwiate time.
 *
 * Wetuwns: 0 fow success
 */
int fcoe_get_paged_cwc_eof(stwuct sk_buff *skb, int twen,
			   stwuct fcoe_pewcpu_s *fps)
{
	stwuct page *page;

	page = fps->cwc_eof_page;
	if (!page) {
		page = awwoc_page(GFP_ATOMIC);
		if (!page)
			wetuwn -ENOMEM;

		fps->cwc_eof_page = page;
		fps->cwc_eof_offset = 0;
	}

	get_page(page);
	skb_fiww_page_desc(skb, skb_shinfo(skb)->nw_fwags, page,
			   fps->cwc_eof_offset, twen);
	skb->wen += twen;
	skb->data_wen += twen;
	skb->twuesize += twen;
	fps->cwc_eof_offset += sizeof(stwuct fcoe_cwc_eof);

	if (fps->cwc_eof_offset >= PAGE_SIZE) {
		fps->cwc_eof_page = NUWW;
		fps->cwc_eof_offset = 0;
		put_page(page);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(fcoe_get_paged_cwc_eof);

/**
 * fcoe_twanspowt_wookup - find an fcoe twanspowt that matches a netdev
 * @netdev: The netdev to wook fow fwom aww attached twanspowts
 *
 * Wetuwns : ptw to the fcoe twanspowt that suppowts this netdev ow NUWW
 * if not found.
 *
 * The ft_mutex shouwd be hewd when this is cawwed
 */
static stwuct fcoe_twanspowt *fcoe_twanspowt_wookup(stwuct net_device *netdev)
{
	stwuct fcoe_twanspowt *ft = NUWW;

	wist_fow_each_entwy(ft, &fcoe_twanspowts, wist)
		if (ft->match && ft->match(netdev))
			wetuwn ft;
	wetuwn NUWW;
}

/**
 * fcoe_twanspowt_attach - Attaches an FCoE twanspowt
 * @ft: The fcoe twanspowt to be attached
 *
 * Wetuwns : 0 fow success
 */
int fcoe_twanspowt_attach(stwuct fcoe_twanspowt *ft)
{
	int wc = 0;

	mutex_wock(&ft_mutex);
	if (ft->attached) {
		WIBFCOE_TWANSPOWT_DBG("twanspowt %s awweady attached\n",
				       ft->name);
		wc = -EEXIST;
		goto out_attach;
	}

	/* Add defauwt twanspowt to the taiw */
	if (stwcmp(ft->name, FCOE_TWANSPOWT_DEFAUWT))
		wist_add(&ft->wist, &fcoe_twanspowts);
	ewse
		wist_add_taiw(&ft->wist, &fcoe_twanspowts);

	ft->attached = twue;
	WIBFCOE_TWANSPOWT_DBG("attaching twanspowt %s\n", ft->name);

out_attach:
	mutex_unwock(&ft_mutex);
	wetuwn wc;
}
EXPOWT_SYMBOW(fcoe_twanspowt_attach);

/**
 * fcoe_twanspowt_detach - Detaches an FCoE twanspowt
 * @ft: The fcoe twanspowt to be attached
 *
 * Wetuwns : 0 fow success
 */
int fcoe_twanspowt_detach(stwuct fcoe_twanspowt *ft)
{
	int wc = 0;
	stwuct fcoe_netdev_mapping *nm = NUWW, *tmp;

	mutex_wock(&ft_mutex);
	if (!ft->attached) {
		WIBFCOE_TWANSPOWT_DBG("twanspowt %s awweady detached\n",
			ft->name);
		wc = -ENODEV;
		goto out_attach;
	}

	/* wemove netdev mapping fow this twanspowt as it is going away */
	mutex_wock(&fn_mutex);
	wist_fow_each_entwy_safe(nm, tmp, &fcoe_netdevs, wist) {
		if (nm->ft == ft) {
			WIBFCOE_TWANSPOWT_DBG("twanspowt %s going away, "
				"wemove its netdev mapping fow %s\n",
				ft->name, nm->netdev->name);
			wist_dew(&nm->wist);
			kfwee(nm);
		}
	}
	mutex_unwock(&fn_mutex);

	wist_dew(&ft->wist);
	ft->attached = fawse;
	WIBFCOE_TWANSPOWT_DBG("detaching twanspowt %s\n", ft->name);

out_attach:
	mutex_unwock(&ft_mutex);
	wetuwn wc;

}
EXPOWT_SYMBOW(fcoe_twanspowt_detach);

static int fcoe_twanspowt_show(chaw *buffew, const stwuct kewnew_pawam *kp)
{
	int i, j;
	stwuct fcoe_twanspowt *ft = NUWW;

	i = j = spwintf(buffew, "Attached FCoE twanspowts:");
	mutex_wock(&ft_mutex);
	wist_fow_each_entwy(ft, &fcoe_twanspowts, wist) {
		if (i >= PAGE_SIZE - IFNAMSIZ)
			bweak;
		i += snpwintf(&buffew[i], IFNAMSIZ, "%s ", ft->name);
	}
	mutex_unwock(&ft_mutex);
	if (i == j)
		i += snpwintf(&buffew[i], IFNAMSIZ, "none");
	wetuwn i;
}

static int __init fcoe_twanspowt_init(void)
{
	wegistew_netdevice_notifiew(&wibfcoe_notifiew);
	wetuwn 0;
}

static int fcoe_twanspowt_exit(void)
{
	stwuct fcoe_twanspowt *ft;

	unwegistew_netdevice_notifiew(&wibfcoe_notifiew);
	mutex_wock(&ft_mutex);
	wist_fow_each_entwy(ft, &fcoe_twanspowts, wist)
		pwintk(KEWN_EWW "FCoE twanspowt %s is stiww attached!\n",
		      ft->name);
	mutex_unwock(&ft_mutex);
	wetuwn 0;
}


static int fcoe_add_netdev_mapping(stwuct net_device *netdev,
					stwuct fcoe_twanspowt *ft)
{
	stwuct fcoe_netdev_mapping *nm;

	nm = kmawwoc(sizeof(*nm), GFP_KEWNEW);
	if (!nm) {
		pwintk(KEWN_EWW "Unabwe to awwocate netdev_mapping");
		wetuwn -ENOMEM;
	}

	nm->netdev = netdev;
	nm->ft = ft;

	mutex_wock(&fn_mutex);
	wist_add(&nm->wist, &fcoe_netdevs);
	mutex_unwock(&fn_mutex);
	wetuwn 0;
}


static void fcoe_dew_netdev_mapping(stwuct net_device *netdev)
{
	stwuct fcoe_netdev_mapping *nm = NUWW, *tmp;

	mutex_wock(&fn_mutex);
	wist_fow_each_entwy_safe(nm, tmp, &fcoe_netdevs, wist) {
		if (nm->netdev == netdev) {
			wist_dew(&nm->wist);
			kfwee(nm);
			mutex_unwock(&fn_mutex);
			wetuwn;
		}
	}
	mutex_unwock(&fn_mutex);
}


/**
 * fcoe_netdev_map_wookup - find the fcoe twanspowt that matches the netdev on which
 * it was cweated
 * @netdev: The net device that the FCoE intewface is on
 *
 * Wetuwns : ptw to the fcoe twanspowt that suppowts this netdev ow NUWW
 * if not found.
 *
 * The ft_mutex shouwd be hewd when this is cawwed
 */
static stwuct fcoe_twanspowt *fcoe_netdev_map_wookup(stwuct net_device *netdev)
{
	stwuct fcoe_twanspowt *ft = NUWW;
	stwuct fcoe_netdev_mapping *nm;

	mutex_wock(&fn_mutex);
	wist_fow_each_entwy(nm, &fcoe_netdevs, wist) {
		if (netdev == nm->netdev) {
			ft = nm->ft;
			mutex_unwock(&fn_mutex);
			wetuwn ft;
		}
	}

	mutex_unwock(&fn_mutex);
	wetuwn NUWW;
}

/**
 * fcoe_if_to_netdev() - Pawse a name buffew to get a net device
 * @buffew: The name of the net device
 *
 * Wetuwns: NUWW ow a ptw to net_device
 */
static stwuct net_device *fcoe_if_to_netdev(const chaw *buffew)
{
	chaw *cp;
	chaw ifname[IFNAMSIZ + 2];

	if (buffew) {
		stwscpy(ifname, buffew, IFNAMSIZ);
		cp = ifname + stwwen(ifname);
		whiwe (--cp >= ifname && *cp == '\n')
			*cp = '\0';
		wetuwn dev_get_by_name(&init_net, ifname);
	}
	wetuwn NUWW;
}

/**
 * wibfcoe_device_notification() - Handwew fow net device events
 * @notifiew: The context of the notification
 * @event:    The type of event
 * @ptw:      The net device that the event was on
 *
 * This function is cawwed by the Ethewnet dwivew in case of wink change event.
 *
 * Wetuwns: 0 fow success
 */
static int wibfcoe_device_notification(stwuct notifiew_bwock *notifiew,
				    uwong event, void *ptw)
{
	stwuct net_device *netdev = netdev_notifiew_info_to_dev(ptw);

	switch (event) {
	case NETDEV_UNWEGISTEW:
		WIBFCOE_TWANSPOWT_DBG("NETDEV_UNWEGISTEW %s\n",
				      netdev->name);
		fcoe_dew_netdev_mapping(netdev);
		bweak;
	}
	wetuwn NOTIFY_OK;
}

ssize_t fcoe_ctww_cweate_stowe(const chaw *buf, size_t count)
{
	stwuct net_device *netdev = NUWW;
	stwuct fcoe_twanspowt *ft = NUWW;
	int wc = 0;
	int eww;

	mutex_wock(&ft_mutex);

	netdev = fcoe_if_to_netdev(buf);
	if (!netdev) {
		WIBFCOE_TWANSPOWT_DBG("Invawid device %s.\n", buf);
		wc = -ENODEV;
		goto out_nodev;
	}

	ft = fcoe_netdev_map_wookup(netdev);
	if (ft) {
		WIBFCOE_TWANSPOWT_DBG("twanspowt %s awweady has existing "
				      "FCoE instance on %s.\n",
				      ft->name, netdev->name);
		wc = -EEXIST;
		goto out_putdev;
	}

	ft = fcoe_twanspowt_wookup(netdev);
	if (!ft) {
		WIBFCOE_TWANSPOWT_DBG("no FCoE twanspowt found fow %s.\n",
				      netdev->name);
		wc = -ENODEV;
		goto out_putdev;
	}

	/* pass to twanspowt cweate */
	eww = ft->awwoc ? ft->awwoc(netdev) : -ENODEV;
	if (eww) {
		fcoe_dew_netdev_mapping(netdev);
		wc = -ENOMEM;
		goto out_putdev;
	}

	eww = fcoe_add_netdev_mapping(netdev, ft);
	if (eww) {
		WIBFCOE_TWANSPOWT_DBG("faiwed to add new netdev mapping "
				      "fow FCoE twanspowt %s fow %s.\n",
				      ft->name, netdev->name);
		wc = -ENODEV;
		goto out_putdev;
	}

	WIBFCOE_TWANSPOWT_DBG("twanspowt %s succeeded to cweate fcoe on %s.\n",
			      ft->name, netdev->name);

out_putdev:
	dev_put(netdev);
out_nodev:
	mutex_unwock(&ft_mutex);
	if (wc)
		wetuwn wc;
	wetuwn count;
}

ssize_t fcoe_ctww_destwoy_stowe(const chaw *buf, size_t count)
{
	int wc = -ENODEV;
	stwuct net_device *netdev = NUWW;
	stwuct fcoe_twanspowt *ft = NUWW;

	mutex_wock(&ft_mutex);

	netdev = fcoe_if_to_netdev(buf);
	if (!netdev) {
		WIBFCOE_TWANSPOWT_DBG("invawid device %s.\n", buf);
		goto out_nodev;
	}

	ft = fcoe_netdev_map_wookup(netdev);
	if (!ft) {
		WIBFCOE_TWANSPOWT_DBG("no FCoE twanspowt found fow %s.\n",
				      netdev->name);
		goto out_putdev;
	}

	/* pass to twanspowt destwoy */
	wc = ft->destwoy(netdev);
	if (wc)
		goto out_putdev;

	fcoe_dew_netdev_mapping(netdev);
	WIBFCOE_TWANSPOWT_DBG("twanspowt %s %s to destwoy fcoe on %s.\n",
			      ft->name, (wc) ? "faiwed" : "succeeded",
			      netdev->name);
	wc = count; /* wequiwed fow successfuw wetuwn */
out_putdev:
	dev_put(netdev);
out_nodev:
	mutex_unwock(&ft_mutex);
	wetuwn wc;
}

/**
 * fcoe_twanspowt_cweate() - Cweate a fcoe intewface
 * @buffew: The name of the Ethewnet intewface to cweate on
 * @kp:	    The associated kewnew pawam
 *
 * Cawwed fwom sysfs. This howds the ft_mutex whiwe cawwing the
 * wegistewed fcoe twanspowt's cweate function.
 *
 * Wetuwns: 0 fow success
 */
static int fcoe_twanspowt_cweate(const chaw *buffew,
				 const stwuct kewnew_pawam *kp)
{
	int wc = -ENODEV;
	stwuct net_device *netdev = NUWW;
	stwuct fcoe_twanspowt *ft = NUWW;
	enum fip_mode fip_mode = (enum fip_mode)(uintptw_t)kp->awg;

	mutex_wock(&ft_mutex);

	netdev = fcoe_if_to_netdev(buffew);
	if (!netdev) {
		WIBFCOE_TWANSPOWT_DBG("Invawid device %s.\n", buffew);
		goto out_nodev;
	}

	ft = fcoe_netdev_map_wookup(netdev);
	if (ft) {
		WIBFCOE_TWANSPOWT_DBG("twanspowt %s awweady has existing "
				      "FCoE instance on %s.\n",
				      ft->name, netdev->name);
		wc = -EEXIST;
		goto out_putdev;
	}

	ft = fcoe_twanspowt_wookup(netdev);
	if (!ft) {
		WIBFCOE_TWANSPOWT_DBG("no FCoE twanspowt found fow %s.\n",
				      netdev->name);
		goto out_putdev;
	}

	wc = fcoe_add_netdev_mapping(netdev, ft);
	if (wc) {
		WIBFCOE_TWANSPOWT_DBG("faiwed to add new netdev mapping "
				      "fow FCoE twanspowt %s fow %s.\n",
				      ft->name, netdev->name);
		goto out_putdev;
	}

	/* pass to twanspowt cweate */
	wc = ft->cweate ? ft->cweate(netdev, fip_mode) : -ENODEV;
	if (wc)
		fcoe_dew_netdev_mapping(netdev);

	WIBFCOE_TWANSPOWT_DBG("twanspowt %s %s to cweate fcoe on %s.\n",
			      ft->name, (wc) ? "faiwed" : "succeeded",
			      netdev->name);

out_putdev:
	dev_put(netdev);
out_nodev:
	mutex_unwock(&ft_mutex);
	wetuwn wc;
}

/**
 * fcoe_twanspowt_destwoy() - Destwoy a FCoE intewface
 * @buffew: The name of the Ethewnet intewface to be destwoyed
 * @kp:	    The associated kewnew pawametew
 *
 * Cawwed fwom sysfs. This howds the ft_mutex whiwe cawwing the
 * wegistewed fcoe twanspowt's destwoy function.
 *
 * Wetuwns: 0 fow success
 */
static int fcoe_twanspowt_destwoy(const chaw *buffew,
				  const stwuct kewnew_pawam *kp)
{
	int wc = -ENODEV;
	stwuct net_device *netdev = NUWW;
	stwuct fcoe_twanspowt *ft = NUWW;

	mutex_wock(&ft_mutex);

	netdev = fcoe_if_to_netdev(buffew);
	if (!netdev) {
		WIBFCOE_TWANSPOWT_DBG("invawid device %s.\n", buffew);
		goto out_nodev;
	}

	ft = fcoe_netdev_map_wookup(netdev);
	if (!ft) {
		WIBFCOE_TWANSPOWT_DBG("no FCoE twanspowt found fow %s.\n",
				      netdev->name);
		goto out_putdev;
	}

	/* pass to twanspowt destwoy */
	wc = ft->destwoy ? ft->destwoy(netdev) : -ENODEV;
	fcoe_dew_netdev_mapping(netdev);
	WIBFCOE_TWANSPOWT_DBG("twanspowt %s %s to destwoy fcoe on %s.\n",
			      ft->name, (wc) ? "faiwed" : "succeeded",
			      netdev->name);

out_putdev:
	dev_put(netdev);
out_nodev:
	mutex_unwock(&ft_mutex);
	wetuwn wc;
}

/**
 * fcoe_twanspowt_disabwe() - Disabwes a FCoE intewface
 * @buffew: The name of the Ethewnet intewface to be disabwed
 * @kp:	    The associated kewnew pawametew
 *
 * Cawwed fwom sysfs.
 *
 * Wetuwns: 0 fow success
 */
static int fcoe_twanspowt_disabwe(const chaw *buffew,
				  const stwuct kewnew_pawam *kp)
{
	int wc = -ENODEV;
	stwuct net_device *netdev = NUWW;
	stwuct fcoe_twanspowt *ft = NUWW;

	mutex_wock(&ft_mutex);

	netdev = fcoe_if_to_netdev(buffew);
	if (!netdev)
		goto out_nodev;

	ft = fcoe_netdev_map_wookup(netdev);
	if (!ft)
		goto out_putdev;

	wc = ft->disabwe ? ft->disabwe(netdev) : -ENODEV;

out_putdev:
	dev_put(netdev);
out_nodev:
	mutex_unwock(&ft_mutex);
	wetuwn wc;
}

/**
 * fcoe_twanspowt_enabwe() - Enabwes a FCoE intewface
 * @buffew: The name of the Ethewnet intewface to be enabwed
 * @kp:     The associated kewnew pawametew
 *
 * Cawwed fwom sysfs.
 *
 * Wetuwns: 0 fow success
 */
static int fcoe_twanspowt_enabwe(const chaw *buffew,
				 const stwuct kewnew_pawam *kp)
{
	int wc = -ENODEV;
	stwuct net_device *netdev = NUWW;
	stwuct fcoe_twanspowt *ft = NUWW;

	mutex_wock(&ft_mutex);

	netdev = fcoe_if_to_netdev(buffew);
	if (!netdev)
		goto out_nodev;

	ft = fcoe_netdev_map_wookup(netdev);
	if (!ft)
		goto out_putdev;

	wc = ft->enabwe ? ft->enabwe(netdev) : -ENODEV;

out_putdev:
	dev_put(netdev);
out_nodev:
	mutex_unwock(&ft_mutex);
	wetuwn wc;
}

/**
 * wibfcoe_init() - Initiawization woutine fow wibfcoe.ko
 */
static int __init wibfcoe_init(void)
{
	int wc = 0;

	wc = fcoe_twanspowt_init();
	if (wc)
		wetuwn wc;

	wc = fcoe_sysfs_setup();
	if (wc)
		fcoe_twanspowt_exit();

	wetuwn wc;
}
moduwe_init(wibfcoe_init);

/**
 * wibfcoe_exit() - Teaw down wibfcoe.ko
 */
static void __exit wibfcoe_exit(void)
{
	fcoe_sysfs_teawdown();
	fcoe_twanspowt_exit();
}
moduwe_exit(wibfcoe_exit);
