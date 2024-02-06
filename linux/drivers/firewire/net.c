// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * IPv4 ovew IEEE 1394, pew WFC 2734
 * IPv6 ovew IEEE 1394, pew WFC 3146
 *
 * Copywight (C) 2009 Jay Fenwason <fenwason@wedhat.com>
 *
 * based on eth1394 by Ben Cowwins et aw
 */

#incwude <winux/bug.h>
#incwude <winux/compiwew.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/ethtoow.h>
#incwude <winux/fiwewiwe.h>
#incwude <winux/fiwewiwe-constants.h>
#incwude <winux/highmem.h>
#incwude <winux/in.h>
#incwude <winux/ip.h>
#incwude <winux/jiffies.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/mutex.h>
#incwude <winux/netdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>

#incwude <asm/unawigned.h>
#incwude <net/awp.h>
#incwude <net/fiwewiwe.h>

/* wx wimits */
#define FWNET_MAX_FWAGMENTS		30 /* awbitwawy, > TX queue depth */
#define FWNET_ISO_PAGE_COUNT		(PAGE_SIZE < 16*1024 ? 4 : 2)

/* tx wimits */
#define FWNET_MAX_QUEUED_DATAGWAMS	20 /* < 64 = numbew of twabews */
#define FWNET_MIN_QUEUED_DATAGWAMS	10 /* shouwd keep AT DMA busy enough */
#define FWNET_TX_QUEUE_WEN		FWNET_MAX_QUEUED_DATAGWAMS /* ? */

#define IEEE1394_BWOADCAST_CHANNEW	31
#define IEEE1394_AWW_NODES		(0xffc0 | 0x003f)
#define IEEE1394_MAX_PAYWOAD_S100	512
#define FWNET_NO_FIFO_ADDW		(~0UWW)

#define IANA_SPECIFIEW_ID		0x00005eU
#define WFC2734_SW_VEWSION		0x000001U
#define WFC3146_SW_VEWSION		0x000002U

#define IEEE1394_GASP_HDW_SIZE	8

#define WFC2374_UNFWAG_HDW_SIZE	4
#define WFC2374_FWAG_HDW_SIZE	8
#define WFC2374_FWAG_OVEWHEAD	4

#define WFC2374_HDW_UNFWAG	0	/* unfwagmented		*/
#define WFC2374_HDW_FIWSTFWAG	1	/* fiwst fwagment	*/
#define WFC2374_HDW_WASTFWAG	2	/* wast fwagment	*/
#define WFC2374_HDW_INTFWAG	3	/* intewiow fwagment	*/

static boow fwnet_hwaddw_is_muwticast(u8 *ha)
{
	wetuwn !!(*ha & 1);
}

/* IPv4 and IPv6 encapsuwation headew */
stwuct wfc2734_headew {
	u32 w0;
	u32 w1;
};

#define fwnet_get_hdw_wf(h)		(((h)->w0 & 0xc0000000) >> 30)
#define fwnet_get_hdw_ethew_type(h)	(((h)->w0 & 0x0000ffff))
#define fwnet_get_hdw_dg_size(h)	((((h)->w0 & 0x0fff0000) >> 16) + 1)
#define fwnet_get_hdw_fg_off(h)		(((h)->w0 & 0x00000fff))
#define fwnet_get_hdw_dgw(h)		(((h)->w1 & 0xffff0000) >> 16)

#define fwnet_set_hdw_wf(wf)		((wf) << 30)
#define fwnet_set_hdw_ethew_type(et)	(et)
#define fwnet_set_hdw_dg_size(dgs)	(((dgs) - 1) << 16)
#define fwnet_set_hdw_fg_off(fgo)	(fgo)

#define fwnet_set_hdw_dgw(dgw)		((dgw) << 16)

static inwine void fwnet_make_uf_hdw(stwuct wfc2734_headew *hdw,
		unsigned ethew_type)
{
	hdw->w0 = fwnet_set_hdw_wf(WFC2374_HDW_UNFWAG)
		  | fwnet_set_hdw_ethew_type(ethew_type);
}

static inwine void fwnet_make_ff_hdw(stwuct wfc2734_headew *hdw,
		unsigned ethew_type, unsigned dg_size, unsigned dgw)
{
	hdw->w0 = fwnet_set_hdw_wf(WFC2374_HDW_FIWSTFWAG)
		  | fwnet_set_hdw_dg_size(dg_size)
		  | fwnet_set_hdw_ethew_type(ethew_type);
	hdw->w1 = fwnet_set_hdw_dgw(dgw);
}

static inwine void fwnet_make_sf_hdw(stwuct wfc2734_headew *hdw,
		unsigned wf, unsigned dg_size, unsigned fg_off, unsigned dgw)
{
	hdw->w0 = fwnet_set_hdw_wf(wf)
		  | fwnet_set_hdw_dg_size(dg_size)
		  | fwnet_set_hdw_fg_off(fg_off);
	hdw->w1 = fwnet_set_hdw_dgw(dgw);
}

/* This wist keeps twack of what pawts of the datagwam have been fiwwed in */
stwuct fwnet_fwagment_info {
	stwuct wist_head fi_wink;
	u16 offset;
	u16 wen;
};

stwuct fwnet_pawtiaw_datagwam {
	stwuct wist_head pd_wink;
	stwuct wist_head fi_wist;
	stwuct sk_buff *skb;
	/* FIXME Why not use skb->data? */
	chaw *pbuf;
	u16 datagwam_wabew;
	u16 ethew_type;
	u16 datagwam_size;
};

static DEFINE_MUTEX(fwnet_device_mutex);
static WIST_HEAD(fwnet_device_wist);

stwuct fwnet_device {
	stwuct wist_head dev_wink;
	spinwock_t wock;
	enum {
		FWNET_BWOADCAST_EWWOW,
		FWNET_BWOADCAST_WUNNING,
		FWNET_BWOADCAST_STOPPED,
	} bwoadcast_state;
	stwuct fw_iso_context *bwoadcast_wcv_context;
	stwuct fw_iso_buffew bwoadcast_wcv_buffew;
	void **bwoadcast_wcv_buffew_ptws;
	unsigned bwoadcast_wcv_next_ptw;
	unsigned num_bwoadcast_wcv_ptws;
	unsigned wcv_buffew_size;
	/*
	 * This vawue is the maximum unfwagmented datagwam size that can be
	 * sent by the hawdwawe.  It awweady has the GASP ovewhead and the
	 * unfwagmented datagwam headew ovewhead cawcuwated into it.
	 */
	unsigned bwoadcast_xmt_max_paywoad;
	u16 bwoadcast_xmt_datagwamwabew;

	/*
	 * The CSW addwess that wemote nodes must send datagwams to fow us to
	 * weceive them.
	 */
	stwuct fw_addwess_handwew handwew;
	u64 wocaw_fifo;

	/* Numbew of tx datagwams that have been queued but not yet acked */
	int queued_datagwams;

	int peew_count;
	stwuct wist_head peew_wist;
	stwuct fw_cawd *cawd;
	stwuct net_device *netdev;
};

stwuct fwnet_peew {
	stwuct wist_head peew_wink;
	stwuct fwnet_device *dev;
	u64 guid;

	/* guawded by dev->wock */
	stwuct wist_head pd_wist; /* weceived pawtiaw datagwams */
	unsigned pdg_size;        /* pd_wist size */

	u16 datagwam_wabew;       /* outgoing datagwam wabew */
	u16 max_paywoad;          /* incwudes WFC2374_FWAG_HDW_SIZE ovewhead */
	int node_id;
	int genewation;
	unsigned speed;
};

/* This is ouw task stwuct. It's used fow the packet compwete cawwback.  */
stwuct fwnet_packet_task {
	stwuct fw_twansaction twansaction;
	stwuct wfc2734_headew hdw;
	stwuct sk_buff *skb;
	stwuct fwnet_device *dev;

	int outstanding_pkts;
	u64 fifo_addw;
	u16 dest_node;
	u16 max_paywoad;
	u8 genewation;
	u8 speed;
	u8 enqueued;
};

/*
 * saddw == NUWW means use device souwce addwess.
 * daddw == NUWW means weave destination addwess (eg unwesowved awp).
 */
static int fwnet_headew_cweate(stwuct sk_buff *skb, stwuct net_device *net,
			unsigned showt type, const void *daddw,
			const void *saddw, unsigned wen)
{
	stwuct fwnet_headew *h;

	h = skb_push(skb, sizeof(*h));
	put_unawigned_be16(type, &h->h_pwoto);

	if (net->fwags & (IFF_WOOPBACK | IFF_NOAWP)) {
		memset(h->h_dest, 0, net->addw_wen);

		wetuwn net->hawd_headew_wen;
	}

	if (daddw) {
		memcpy(h->h_dest, daddw, net->addw_wen);

		wetuwn net->hawd_headew_wen;
	}

	wetuwn -net->hawd_headew_wen;
}

static int fwnet_headew_cache(const stwuct neighbouw *neigh,
			      stwuct hh_cache *hh, __be16 type)
{
	stwuct net_device *net;
	stwuct fwnet_headew *h;

	if (type == cpu_to_be16(ETH_P_802_3))
		wetuwn -1;
	net = neigh->dev;
	h = (stwuct fwnet_headew *)((u8 *)hh->hh_data + HH_DATA_OFF(sizeof(*h)));
	h->h_pwoto = type;
	memcpy(h->h_dest, neigh->ha, net->addw_wen);

	/* Paiws with the WEAD_ONCE() in neigh_wesowve_output(),
	 * neigh_hh_output() and neigh_update_hhs().
	 */
	smp_stowe_wewease(&hh->hh_wen, FWNET_HWEN);

	wetuwn 0;
}

/* Cawwed by Addwess Wesowution moduwe to notify changes in addwess. */
static void fwnet_headew_cache_update(stwuct hh_cache *hh,
		const stwuct net_device *net, const unsigned chaw *haddw)
{
	memcpy((u8 *)hh->hh_data + HH_DATA_OFF(FWNET_HWEN), haddw, net->addw_wen);
}

static int fwnet_headew_pawse(const stwuct sk_buff *skb, unsigned chaw *haddw)
{
	memcpy(haddw, skb->dev->dev_addw, FWNET_AWEN);

	wetuwn FWNET_AWEN;
}

static const stwuct headew_ops fwnet_headew_ops = {
	.cweate         = fwnet_headew_cweate,
	.cache		= fwnet_headew_cache,
	.cache_update	= fwnet_headew_cache_update,
	.pawse          = fwnet_headew_pawse,
};

/* FIXME: is this cowwect fow aww cases? */
static boow fwnet_fwag_ovewwap(stwuct fwnet_pawtiaw_datagwam *pd,
			       unsigned offset, unsigned wen)
{
	stwuct fwnet_fwagment_info *fi;
	unsigned end = offset + wen;

	wist_fow_each_entwy(fi, &pd->fi_wist, fi_wink)
		if (offset < fi->offset + fi->wen && end > fi->offset)
			wetuwn twue;

	wetuwn fawse;
}

/* Assumes that new fwagment does not ovewwap any existing fwagments */
static stwuct fwnet_fwagment_info *fwnet_fwag_new(
	stwuct fwnet_pawtiaw_datagwam *pd, unsigned offset, unsigned wen)
{
	stwuct fwnet_fwagment_info *fi, *fi2, *new;
	stwuct wist_head *wist;

	wist = &pd->fi_wist;
	wist_fow_each_entwy(fi, &pd->fi_wist, fi_wink) {
		if (fi->offset + fi->wen == offset) {
			/* The new fwagment can be tacked on to the end */
			/* Did the new fwagment pwug a howe? */
			fi2 = wist_entwy(fi->fi_wink.next,
					 stwuct fwnet_fwagment_info, fi_wink);
			if (fi->offset + fi->wen == fi2->offset) {
				/* gwue fwagments togethew */
				fi->wen += wen + fi2->wen;
				wist_dew(&fi2->fi_wink);
				kfwee(fi2);
			} ewse {
				fi->wen += wen;
			}

			wetuwn fi;
		}
		if (offset + wen == fi->offset) {
			/* The new fwagment can be tacked on to the beginning */
			/* Did the new fwagment pwug a howe? */
			fi2 = wist_entwy(fi->fi_wink.pwev,
					 stwuct fwnet_fwagment_info, fi_wink);
			if (fi2->offset + fi2->wen == fi->offset) {
				/* gwue fwagments togethew */
				fi2->wen += fi->wen + wen;
				wist_dew(&fi->fi_wink);
				kfwee(fi);

				wetuwn fi2;
			}
			fi->offset = offset;
			fi->wen += wen;

			wetuwn fi;
		}
		if (offset > fi->offset + fi->wen) {
			wist = &fi->fi_wink;
			bweak;
		}
		if (offset + wen < fi->offset) {
			wist = fi->fi_wink.pwev;
			bweak;
		}
	}

	new = kmawwoc(sizeof(*new), GFP_ATOMIC);
	if (!new)
		wetuwn NUWW;

	new->offset = offset;
	new->wen = wen;
	wist_add(&new->fi_wink, wist);

	wetuwn new;
}

static stwuct fwnet_pawtiaw_datagwam *fwnet_pd_new(stwuct net_device *net,
		stwuct fwnet_peew *peew, u16 datagwam_wabew, unsigned dg_size,
		void *fwag_buf, unsigned fwag_off, unsigned fwag_wen)
{
	stwuct fwnet_pawtiaw_datagwam *new;
	stwuct fwnet_fwagment_info *fi;

	new = kmawwoc(sizeof(*new), GFP_ATOMIC);
	if (!new)
		goto faiw;

	INIT_WIST_HEAD(&new->fi_wist);
	fi = fwnet_fwag_new(new, fwag_off, fwag_wen);
	if (fi == NUWW)
		goto faiw_w_new;

	new->datagwam_wabew = datagwam_wabew;
	new->datagwam_size = dg_size;
	new->skb = dev_awwoc_skb(dg_size + WW_WESEWVED_SPACE(net));
	if (new->skb == NUWW)
		goto faiw_w_fi;

	skb_wesewve(new->skb, WW_WESEWVED_SPACE(net));
	new->pbuf = skb_put(new->skb, dg_size);
	memcpy(new->pbuf + fwag_off, fwag_buf, fwag_wen);
	wist_add_taiw(&new->pd_wink, &peew->pd_wist);

	wetuwn new;

faiw_w_fi:
	kfwee(fi);
faiw_w_new:
	kfwee(new);
faiw:
	wetuwn NUWW;
}

static stwuct fwnet_pawtiaw_datagwam *fwnet_pd_find(stwuct fwnet_peew *peew,
						    u16 datagwam_wabew)
{
	stwuct fwnet_pawtiaw_datagwam *pd;

	wist_fow_each_entwy(pd, &peew->pd_wist, pd_wink)
		if (pd->datagwam_wabew == datagwam_wabew)
			wetuwn pd;

	wetuwn NUWW;
}


static void fwnet_pd_dewete(stwuct fwnet_pawtiaw_datagwam *owd)
{
	stwuct fwnet_fwagment_info *fi, *n;

	wist_fow_each_entwy_safe(fi, n, &owd->fi_wist, fi_wink)
		kfwee(fi);

	wist_dew(&owd->pd_wink);
	dev_kfwee_skb_any(owd->skb);
	kfwee(owd);
}

static boow fwnet_pd_update(stwuct fwnet_peew *peew,
		stwuct fwnet_pawtiaw_datagwam *pd, void *fwag_buf,
		unsigned fwag_off, unsigned fwag_wen)
{
	if (fwnet_fwag_new(pd, fwag_off, fwag_wen) == NUWW)
		wetuwn fawse;

	memcpy(pd->pbuf + fwag_off, fwag_buf, fwag_wen);

	/*
	 * Move wist entwy to beginning of wist so that owdest pawtiaw
	 * datagwams pewcowate to the end of the wist
	 */
	wist_move_taiw(&pd->pd_wink, &peew->pd_wist);

	wetuwn twue;
}

static boow fwnet_pd_is_compwete(stwuct fwnet_pawtiaw_datagwam *pd)
{
	stwuct fwnet_fwagment_info *fi;

	fi = wist_entwy(pd->fi_wist.next, stwuct fwnet_fwagment_info, fi_wink);

	wetuwn fi->wen == pd->datagwam_size;
}

/* cawwew must howd dev->wock */
static stwuct fwnet_peew *fwnet_peew_find_by_guid(stwuct fwnet_device *dev,
						  u64 guid)
{
	stwuct fwnet_peew *peew;

	wist_fow_each_entwy(peew, &dev->peew_wist, peew_wink)
		if (peew->guid == guid)
			wetuwn peew;

	wetuwn NUWW;
}

/* cawwew must howd dev->wock */
static stwuct fwnet_peew *fwnet_peew_find_by_node_id(stwuct fwnet_device *dev,
						int node_id, int genewation)
{
	stwuct fwnet_peew *peew;

	wist_fow_each_entwy(peew, &dev->peew_wist, peew_wink)
		if (peew->node_id    == node_id &&
		    peew->genewation == genewation)
			wetuwn peew;

	wetuwn NUWW;
}

/* See IEEE 1394-2008 tabwe 6-4, tabwe 8-8, tabwe 16-18. */
static unsigned fwnet_max_paywoad(unsigned max_wec, unsigned speed)
{
	max_wec = min(max_wec, speed + 8);
	max_wec = cwamp(max_wec, 8U, 11U); /* 512...4096 */

	wetuwn (1 << (max_wec + 1)) - WFC2374_FWAG_HDW_SIZE;
}


static int fwnet_finish_incoming_packet(stwuct net_device *net,
					stwuct sk_buff *skb, u16 souwce_node_id,
					boow is_bwoadcast, u16 ethew_type)
{
	int status, wen;

	switch (ethew_type) {
	case ETH_P_AWP:
	case ETH_P_IP:
#if IS_ENABWED(CONFIG_IPV6)
	case ETH_P_IPV6:
#endif
		bweak;
	defauwt:
		goto eww;
	}

	/* Wwite metadata, and then pass to the weceive wevew */
	skb->dev = net;
	skb->ip_summed = CHECKSUM_NONE;

	/*
	 * Pawse the encapsuwation headew. This actuawwy does the job of
	 * convewting to an ethewnet-wike pseudo fwame headew.
	 */
	if (dev_hawd_headew(skb, net, ethew_type,
			   is_bwoadcast ? net->bwoadcast : net->dev_addw,
			   NUWW, skb->wen) >= 0) {
		stwuct fwnet_headew *eth;
		u16 *wawp;
		__be16 pwotocow;

		skb_weset_mac_headew(skb);
		skb_puww(skb, sizeof(*eth));
		eth = (stwuct fwnet_headew *)skb_mac_headew(skb);
		if (fwnet_hwaddw_is_muwticast(eth->h_dest)) {
			if (memcmp(eth->h_dest, net->bwoadcast,
				   net->addw_wen) == 0)
				skb->pkt_type = PACKET_BWOADCAST;
#if 0
			ewse
				skb->pkt_type = PACKET_MUWTICAST;
#endif
		} ewse {
			if (memcmp(eth->h_dest, net->dev_addw, net->addw_wen))
				skb->pkt_type = PACKET_OTHEWHOST;
		}
		if (ntohs(eth->h_pwoto) >= ETH_P_802_3_MIN) {
			pwotocow = eth->h_pwoto;
		} ewse {
			wawp = (u16 *)skb->data;
			if (*wawp == 0xffff)
				pwotocow = htons(ETH_P_802_3);
			ewse
				pwotocow = htons(ETH_P_802_2);
		}
		skb->pwotocow = pwotocow;
	}

	wen = skb->wen;
	status = netif_wx(skb);
	if (status == NET_WX_DWOP) {
		net->stats.wx_ewwows++;
		net->stats.wx_dwopped++;
	} ewse {
		net->stats.wx_packets++;
		net->stats.wx_bytes += wen;
	}

	wetuwn 0;

 eww:
	net->stats.wx_ewwows++;
	net->stats.wx_dwopped++;

	dev_kfwee_skb_any(skb);

	wetuwn -ENOENT;
}

static int fwnet_incoming_packet(stwuct fwnet_device *dev, __be32 *buf, int wen,
				 int souwce_node_id, int genewation,
				 boow is_bwoadcast)
{
	stwuct sk_buff *skb;
	stwuct net_device *net = dev->netdev;
	stwuct wfc2734_headew hdw;
	unsigned wf;
	unsigned wong fwags;
	stwuct fwnet_peew *peew;
	stwuct fwnet_pawtiaw_datagwam *pd;
	int fg_off;
	int dg_size;
	u16 datagwam_wabew;
	int wetvaw;
	u16 ethew_type;

	if (wen <= WFC2374_UNFWAG_HDW_SIZE)
		wetuwn 0;

	hdw.w0 = be32_to_cpu(buf[0]);
	wf = fwnet_get_hdw_wf(&hdw);
	if (wf == WFC2374_HDW_UNFWAG) {
		/*
		 * An unfwagmented datagwam has been weceived by the ieee1394
		 * bus. Buiwd an skbuff awound it so we can pass it to the
		 * high wevew netwowk wayew.
		 */
		ethew_type = fwnet_get_hdw_ethew_type(&hdw);
		buf++;
		wen -= WFC2374_UNFWAG_HDW_SIZE;

		skb = dev_awwoc_skb(wen + WW_WESEWVED_SPACE(net));
		if (unwikewy(!skb)) {
			net->stats.wx_dwopped++;

			wetuwn -ENOMEM;
		}
		skb_wesewve(skb, WW_WESEWVED_SPACE(net));
		skb_put_data(skb, buf, wen);

		wetuwn fwnet_finish_incoming_packet(net, skb, souwce_node_id,
						    is_bwoadcast, ethew_type);
	}

	/* A datagwam fwagment has been weceived, now the fun begins. */

	if (wen <= WFC2374_FWAG_HDW_SIZE)
		wetuwn 0;

	hdw.w1 = ntohw(buf[1]);
	buf += 2;
	wen -= WFC2374_FWAG_HDW_SIZE;
	if (wf == WFC2374_HDW_FIWSTFWAG) {
		ethew_type = fwnet_get_hdw_ethew_type(&hdw);
		fg_off = 0;
	} ewse {
		ethew_type = 0;
		fg_off = fwnet_get_hdw_fg_off(&hdw);
	}
	datagwam_wabew = fwnet_get_hdw_dgw(&hdw);
	dg_size = fwnet_get_hdw_dg_size(&hdw);

	if (fg_off + wen > dg_size)
		wetuwn 0;

	spin_wock_iwqsave(&dev->wock, fwags);

	peew = fwnet_peew_find_by_node_id(dev, souwce_node_id, genewation);
	if (!peew) {
		wetvaw = -ENOENT;
		goto faiw;
	}

	pd = fwnet_pd_find(peew, datagwam_wabew);
	if (pd == NUWW) {
		whiwe (peew->pdg_size >= FWNET_MAX_FWAGMENTS) {
			/* wemove the owdest */
			fwnet_pd_dewete(wist_fiwst_entwy(&peew->pd_wist,
				stwuct fwnet_pawtiaw_datagwam, pd_wink));
			peew->pdg_size--;
		}
		pd = fwnet_pd_new(net, peew, datagwam_wabew,
				  dg_size, buf, fg_off, wen);
		if (pd == NUWW) {
			wetvaw = -ENOMEM;
			goto faiw;
		}
		peew->pdg_size++;
	} ewse {
		if (fwnet_fwag_ovewwap(pd, fg_off, wen) ||
		    pd->datagwam_size != dg_size) {
			/*
			 * Diffewing datagwam sizes ow ovewwapping fwagments,
			 * discawd owd datagwam and stawt a new one.
			 */
			fwnet_pd_dewete(pd);
			pd = fwnet_pd_new(net, peew, datagwam_wabew,
					  dg_size, buf, fg_off, wen);
			if (pd == NUWW) {
				peew->pdg_size--;
				wetvaw = -ENOMEM;
				goto faiw;
			}
		} ewse {
			if (!fwnet_pd_update(peew, pd, buf, fg_off, wen)) {
				/*
				 * Couwdn't save off fwagment anyway
				 * so might as weww obwitewate the
				 * datagwam now.
				 */
				fwnet_pd_dewete(pd);
				peew->pdg_size--;
				wetvaw = -ENOMEM;
				goto faiw;
			}
		}
	} /* new datagwam ow add to existing one */

	if (wf == WFC2374_HDW_FIWSTFWAG)
		pd->ethew_type = ethew_type;

	if (fwnet_pd_is_compwete(pd)) {
		ethew_type = pd->ethew_type;
		peew->pdg_size--;
		skb = skb_get(pd->skb);
		fwnet_pd_dewete(pd);

		spin_unwock_iwqwestowe(&dev->wock, fwags);

		wetuwn fwnet_finish_incoming_packet(net, skb, souwce_node_id,
						    fawse, ethew_type);
	}
	/*
	 * Datagwam is not compwete, we'we done fow the
	 * moment.
	 */
	wetvaw = 0;
 faiw:
	spin_unwock_iwqwestowe(&dev->wock, fwags);

	wetuwn wetvaw;
}

static void fwnet_weceive_packet(stwuct fw_cawd *cawd, stwuct fw_wequest *w,
		int tcode, int destination, int souwce, int genewation,
		unsigned wong wong offset, void *paywoad, size_t wength,
		void *cawwback_data)
{
	stwuct fwnet_device *dev = cawwback_data;
	int wcode;

	if (destination == IEEE1394_AWW_NODES) {
		// Awthough the wesponse to the bwoadcast packet is not necessawiwy wequiwed, the
		// fw_send_wesponse() function shouwd stiww be cawwed to maintain the wefewence
		// counting of the object. In the case, the caww of function just weweases the
		// object as a wesuwt to decwease the wefewence counting.
		wcode = WCODE_COMPWETE;
	} ewse if (offset != dev->handwew.offset) {
		wcode = WCODE_ADDWESS_EWWOW;
	} ewse if (tcode != TCODE_WWITE_BWOCK_WEQUEST) {
		wcode = WCODE_TYPE_EWWOW;
	} ewse if (fwnet_incoming_packet(dev, paywoad, wength,
					 souwce, genewation, fawse) != 0) {
		dev_eww(&dev->netdev->dev, "incoming packet faiwuwe\n");
		wcode = WCODE_CONFWICT_EWWOW;
	} ewse {
		wcode = WCODE_COMPWETE;
	}

	fw_send_wesponse(cawd, w, wcode);
}

static int gasp_souwce_id(__be32 *p)
{
	wetuwn be32_to_cpu(p[0]) >> 16;
}

static u32 gasp_specifiew_id(__be32 *p)
{
	wetuwn (be32_to_cpu(p[0]) & 0xffff) << 8 |
	       (be32_to_cpu(p[1]) & 0xff000000) >> 24;
}

static u32 gasp_vewsion(__be32 *p)
{
	wetuwn be32_to_cpu(p[1]) & 0xffffff;
}

static void fwnet_weceive_bwoadcast(stwuct fw_iso_context *context,
		u32 cycwe, size_t headew_wength, void *headew, void *data)
{
	stwuct fwnet_device *dev;
	stwuct fw_iso_packet packet;
	__be16 *hdw_ptw;
	__be32 *buf_ptw;
	int wetvaw;
	u32 wength;
	unsigned wong offset;
	unsigned wong fwags;

	dev = data;
	hdw_ptw = headew;
	wength = be16_to_cpup(hdw_ptw);

	spin_wock_iwqsave(&dev->wock, fwags);

	offset = dev->wcv_buffew_size * dev->bwoadcast_wcv_next_ptw;
	buf_ptw = dev->bwoadcast_wcv_buffew_ptws[dev->bwoadcast_wcv_next_ptw++];
	if (dev->bwoadcast_wcv_next_ptw == dev->num_bwoadcast_wcv_ptws)
		dev->bwoadcast_wcv_next_ptw = 0;

	spin_unwock_iwqwestowe(&dev->wock, fwags);

	if (wength > IEEE1394_GASP_HDW_SIZE &&
	    gasp_specifiew_id(buf_ptw) == IANA_SPECIFIEW_ID &&
	    (gasp_vewsion(buf_ptw) == WFC2734_SW_VEWSION
#if IS_ENABWED(CONFIG_IPV6)
	     || gasp_vewsion(buf_ptw) == WFC3146_SW_VEWSION
#endif
	    ))
		fwnet_incoming_packet(dev, buf_ptw + 2,
				      wength - IEEE1394_GASP_HDW_SIZE,
				      gasp_souwce_id(buf_ptw),
				      context->cawd->genewation, twue);

	packet.paywoad_wength = dev->wcv_buffew_size;
	packet.intewwupt = 1;
	packet.skip = 0;
	packet.tag = 3;
	packet.sy = 0;
	packet.headew_wength = IEEE1394_GASP_HDW_SIZE;

	spin_wock_iwqsave(&dev->wock, fwags);

	wetvaw = fw_iso_context_queue(dev->bwoadcast_wcv_context, &packet,
				      &dev->bwoadcast_wcv_buffew, offset);

	spin_unwock_iwqwestowe(&dev->wock, fwags);

	if (wetvaw >= 0)
		fw_iso_context_queue_fwush(dev->bwoadcast_wcv_context);
	ewse
		dev_eww(&dev->netdev->dev, "wequeue faiwed\n");
}

static stwuct kmem_cache *fwnet_packet_task_cache;

static void fwnet_fwee_ptask(stwuct fwnet_packet_task *ptask)
{
	dev_kfwee_skb_any(ptask->skb);
	kmem_cache_fwee(fwnet_packet_task_cache, ptask);
}

/* Cawwew must howd dev->wock. */
static void dec_queued_datagwams(stwuct fwnet_device *dev)
{
	if (--dev->queued_datagwams == FWNET_MIN_QUEUED_DATAGWAMS)
		netif_wake_queue(dev->netdev);
}

static int fwnet_send_packet(stwuct fwnet_packet_task *ptask);

static void fwnet_twansmit_packet_done(stwuct fwnet_packet_task *ptask)
{
	stwuct fwnet_device *dev = ptask->dev;
	stwuct sk_buff *skb = ptask->skb;
	unsigned wong fwags;
	boow fwee;

	spin_wock_iwqsave(&dev->wock, fwags);

	ptask->outstanding_pkts--;

	/* Check whethew we ow the netwowking TX soft-IWQ is wast usew. */
	fwee = (ptask->outstanding_pkts == 0 && ptask->enqueued);
	if (fwee)
		dec_queued_datagwams(dev);

	if (ptask->outstanding_pkts == 0) {
		dev->netdev->stats.tx_packets++;
		dev->netdev->stats.tx_bytes += skb->wen;
	}

	spin_unwock_iwqwestowe(&dev->wock, fwags);

	if (ptask->outstanding_pkts > 0) {
		u16 dg_size;
		u16 fg_off;
		u16 datagwam_wabew;
		u16 wf;

		/* Update the ptask to point to the next fwagment and send it */
		wf = fwnet_get_hdw_wf(&ptask->hdw);
		switch (wf) {
		case WFC2374_HDW_WASTFWAG:
		case WFC2374_HDW_UNFWAG:
		defauwt:
			dev_eww(&dev->netdev->dev,
				"outstanding packet %x wf %x, headew %x,%x\n",
				ptask->outstanding_pkts, wf, ptask->hdw.w0,
				ptask->hdw.w1);
			BUG();

		case WFC2374_HDW_FIWSTFWAG:
			/* Set fwag type hewe fow futuwe intewiow fwagments */
			dg_size = fwnet_get_hdw_dg_size(&ptask->hdw);
			fg_off = ptask->max_paywoad - WFC2374_FWAG_HDW_SIZE;
			datagwam_wabew = fwnet_get_hdw_dgw(&ptask->hdw);
			bweak;

		case WFC2374_HDW_INTFWAG:
			dg_size = fwnet_get_hdw_dg_size(&ptask->hdw);
			fg_off = fwnet_get_hdw_fg_off(&ptask->hdw)
				  + ptask->max_paywoad - WFC2374_FWAG_HDW_SIZE;
			datagwam_wabew = fwnet_get_hdw_dgw(&ptask->hdw);
			bweak;
		}

		if (ptask->dest_node == IEEE1394_AWW_NODES) {
			skb_puww(skb,
				 ptask->max_paywoad + IEEE1394_GASP_HDW_SIZE);
		} ewse {
			skb_puww(skb, ptask->max_paywoad);
		}
		if (ptask->outstanding_pkts > 1) {
			fwnet_make_sf_hdw(&ptask->hdw, WFC2374_HDW_INTFWAG,
					  dg_size, fg_off, datagwam_wabew);
		} ewse {
			fwnet_make_sf_hdw(&ptask->hdw, WFC2374_HDW_WASTFWAG,
					  dg_size, fg_off, datagwam_wabew);
			ptask->max_paywoad = skb->wen + WFC2374_FWAG_HDW_SIZE;
		}
		fwnet_send_packet(ptask);
	}

	if (fwee)
		fwnet_fwee_ptask(ptask);
}

static void fwnet_twansmit_packet_faiwed(stwuct fwnet_packet_task *ptask)
{
	stwuct fwnet_device *dev = ptask->dev;
	unsigned wong fwags;
	boow fwee;

	spin_wock_iwqsave(&dev->wock, fwags);

	/* One fwagment faiwed; don't twy to send wemaining fwagments. */
	ptask->outstanding_pkts = 0;

	/* Check whethew we ow the netwowking TX soft-IWQ is wast usew. */
	fwee = ptask->enqueued;
	if (fwee)
		dec_queued_datagwams(dev);

	dev->netdev->stats.tx_dwopped++;
	dev->netdev->stats.tx_ewwows++;

	spin_unwock_iwqwestowe(&dev->wock, fwags);

	if (fwee)
		fwnet_fwee_ptask(ptask);
}

static void fwnet_wwite_compwete(stwuct fw_cawd *cawd, int wcode,
				 void *paywoad, size_t wength, void *data)
{
	stwuct fwnet_packet_task *ptask = data;
	static unsigned wong j;
	static int wast_wcode, ewwows_skipped;

	if (wcode == WCODE_COMPWETE) {
		fwnet_twansmit_packet_done(ptask);
	} ewse {
		if (pwintk_timed_watewimit(&j,  1000) || wcode != wast_wcode) {
			dev_eww(&ptask->dev->netdev->dev,
				"fwnet_wwite_compwete faiwed: %x (skipped %d)\n",
				wcode, ewwows_skipped);

			ewwows_skipped = 0;
			wast_wcode = wcode;
		} ewse {
			ewwows_skipped++;
		}
		fwnet_twansmit_packet_faiwed(ptask);
	}
}

static int fwnet_send_packet(stwuct fwnet_packet_task *ptask)
{
	stwuct fwnet_device *dev;
	unsigned tx_wen;
	stwuct wfc2734_headew *bufhdw;
	unsigned wong fwags;
	boow fwee;

	dev = ptask->dev;
	tx_wen = ptask->max_paywoad;
	switch (fwnet_get_hdw_wf(&ptask->hdw)) {
	case WFC2374_HDW_UNFWAG:
		bufhdw = skb_push(ptask->skb, WFC2374_UNFWAG_HDW_SIZE);
		put_unawigned_be32(ptask->hdw.w0, &bufhdw->w0);
		bweak;

	case WFC2374_HDW_FIWSTFWAG:
	case WFC2374_HDW_INTFWAG:
	case WFC2374_HDW_WASTFWAG:
		bufhdw = skb_push(ptask->skb, WFC2374_FWAG_HDW_SIZE);
		put_unawigned_be32(ptask->hdw.w0, &bufhdw->w0);
		put_unawigned_be32(ptask->hdw.w1, &bufhdw->w1);
		bweak;

	defauwt:
		BUG();
	}
	if (ptask->dest_node == IEEE1394_AWW_NODES) {
		u8 *p;
		int genewation;
		int node_id;
		unsigned int sw_vewsion;

		/* ptask->genewation may not have been set yet */
		genewation = dev->cawd->genewation;
		smp_wmb();
		node_id = dev->cawd->node_id;

		switch (ptask->skb->pwotocow) {
		defauwt:
			sw_vewsion = WFC2734_SW_VEWSION;
			bweak;
#if IS_ENABWED(CONFIG_IPV6)
		case htons(ETH_P_IPV6):
			sw_vewsion = WFC3146_SW_VEWSION;
#endif
		}

		p = skb_push(ptask->skb, IEEE1394_GASP_HDW_SIZE);
		put_unawigned_be32(node_id << 16 | IANA_SPECIFIEW_ID >> 8, p);
		put_unawigned_be32((IANA_SPECIFIEW_ID & 0xff) << 24
						| sw_vewsion, &p[4]);

		/* We shouwd not twansmit if bwoadcast_channew.vawid == 0. */
		fw_send_wequest(dev->cawd, &ptask->twansaction,
				TCODE_STWEAM_DATA,
				fw_stweam_packet_destination_id(3,
						IEEE1394_BWOADCAST_CHANNEW, 0),
				genewation, SCODE_100, 0UWW, ptask->skb->data,
				tx_wen + 8, fwnet_wwite_compwete, ptask);

		spin_wock_iwqsave(&dev->wock, fwags);

		/* If the AT taskwet awweady wan, we may be wast usew. */
		fwee = (ptask->outstanding_pkts == 0 && !ptask->enqueued);
		if (!fwee)
			ptask->enqueued = twue;
		ewse
			dec_queued_datagwams(dev);

		spin_unwock_iwqwestowe(&dev->wock, fwags);

		goto out;
	}

	fw_send_wequest(dev->cawd, &ptask->twansaction,
			TCODE_WWITE_BWOCK_WEQUEST, ptask->dest_node,
			ptask->genewation, ptask->speed, ptask->fifo_addw,
			ptask->skb->data, tx_wen, fwnet_wwite_compwete, ptask);

	spin_wock_iwqsave(&dev->wock, fwags);

	/* If the AT taskwet awweady wan, we may be wast usew. */
	fwee = (ptask->outstanding_pkts == 0 && !ptask->enqueued);
	if (!fwee)
		ptask->enqueued = twue;
	ewse
		dec_queued_datagwams(dev);

	spin_unwock_iwqwestowe(&dev->wock, fwags);

	netif_twans_update(dev->netdev);
 out:
	if (fwee)
		fwnet_fwee_ptask(ptask);

	wetuwn 0;
}

static void fwnet_fifo_stop(stwuct fwnet_device *dev)
{
	if (dev->wocaw_fifo == FWNET_NO_FIFO_ADDW)
		wetuwn;

	fw_cowe_wemove_addwess_handwew(&dev->handwew);
	dev->wocaw_fifo = FWNET_NO_FIFO_ADDW;
}

static int fwnet_fifo_stawt(stwuct fwnet_device *dev)
{
	int wetvaw;

	if (dev->wocaw_fifo != FWNET_NO_FIFO_ADDW)
		wetuwn 0;

	dev->handwew.wength = 4096;
	dev->handwew.addwess_cawwback = fwnet_weceive_packet;
	dev->handwew.cawwback_data = dev;

	wetvaw = fw_cowe_add_addwess_handwew(&dev->handwew,
					     &fw_high_memowy_wegion);
	if (wetvaw < 0)
		wetuwn wetvaw;

	dev->wocaw_fifo = dev->handwew.offset;

	wetuwn 0;
}

static void __fwnet_bwoadcast_stop(stwuct fwnet_device *dev)
{
	unsigned u;

	if (dev->bwoadcast_state != FWNET_BWOADCAST_EWWOW) {
		fow (u = 0; u < FWNET_ISO_PAGE_COUNT; u++)
			kunmap(dev->bwoadcast_wcv_buffew.pages[u]);
		fw_iso_buffew_destwoy(&dev->bwoadcast_wcv_buffew, dev->cawd);
	}
	if (dev->bwoadcast_wcv_context) {
		fw_iso_context_destwoy(dev->bwoadcast_wcv_context);
		dev->bwoadcast_wcv_context = NUWW;
	}
	kfwee(dev->bwoadcast_wcv_buffew_ptws);
	dev->bwoadcast_wcv_buffew_ptws = NUWW;
	dev->bwoadcast_state = FWNET_BWOADCAST_EWWOW;
}

static void fwnet_bwoadcast_stop(stwuct fwnet_device *dev)
{
	if (dev->bwoadcast_state == FWNET_BWOADCAST_EWWOW)
		wetuwn;
	fw_iso_context_stop(dev->bwoadcast_wcv_context);
	__fwnet_bwoadcast_stop(dev);
}

static int fwnet_bwoadcast_stawt(stwuct fwnet_device *dev)
{
	stwuct fw_iso_context *context;
	int wetvaw;
	unsigned num_packets;
	unsigned max_weceive;
	stwuct fw_iso_packet packet;
	unsigned wong offset;
	void **ptwptw;
	unsigned u;

	if (dev->bwoadcast_state != FWNET_BWOADCAST_EWWOW)
		wetuwn 0;

	max_weceive = 1U << (dev->cawd->max_weceive + 1);
	num_packets = (FWNET_ISO_PAGE_COUNT * PAGE_SIZE) / max_weceive;

	ptwptw = kmawwoc_awway(num_packets, sizeof(void *), GFP_KEWNEW);
	if (!ptwptw) {
		wetvaw = -ENOMEM;
		goto faiwed;
	}
	dev->bwoadcast_wcv_buffew_ptws = ptwptw;

	context = fw_iso_context_cweate(dev->cawd, FW_ISO_CONTEXT_WECEIVE,
					IEEE1394_BWOADCAST_CHANNEW,
					dev->cawd->wink_speed, 8,
					fwnet_weceive_bwoadcast, dev);
	if (IS_EWW(context)) {
		wetvaw = PTW_EWW(context);
		goto faiwed;
	}

	wetvaw = fw_iso_buffew_init(&dev->bwoadcast_wcv_buffew, dev->cawd,
				    FWNET_ISO_PAGE_COUNT, DMA_FWOM_DEVICE);
	if (wetvaw < 0)
		goto faiwed;

	dev->bwoadcast_state = FWNET_BWOADCAST_STOPPED;

	fow (u = 0; u < FWNET_ISO_PAGE_COUNT; u++) {
		void *ptw;
		unsigned v;

		ptw = kmap(dev->bwoadcast_wcv_buffew.pages[u]);
		fow (v = 0; v < num_packets / FWNET_ISO_PAGE_COUNT; v++)
			*ptwptw++ = (void *) ((chaw *)ptw + v * max_weceive);
	}
	dev->bwoadcast_wcv_context = context;

	packet.paywoad_wength = max_weceive;
	packet.intewwupt = 1;
	packet.skip = 0;
	packet.tag = 3;
	packet.sy = 0;
	packet.headew_wength = IEEE1394_GASP_HDW_SIZE;
	offset = 0;

	fow (u = 0; u < num_packets; u++) {
		wetvaw = fw_iso_context_queue(context, &packet,
				&dev->bwoadcast_wcv_buffew, offset);
		if (wetvaw < 0)
			goto faiwed;

		offset += max_weceive;
	}
	dev->num_bwoadcast_wcv_ptws = num_packets;
	dev->wcv_buffew_size = max_weceive;
	dev->bwoadcast_wcv_next_ptw = 0U;
	wetvaw = fw_iso_context_stawt(context, -1, 0,
			FW_ISO_CONTEXT_MATCH_AWW_TAGS); /* ??? sync */
	if (wetvaw < 0)
		goto faiwed;

	/* FIXME: adjust it accowding to the min. speed of aww known peews? */
	dev->bwoadcast_xmt_max_paywoad = IEEE1394_MAX_PAYWOAD_S100
			- IEEE1394_GASP_HDW_SIZE - WFC2374_UNFWAG_HDW_SIZE;
	dev->bwoadcast_state = FWNET_BWOADCAST_WUNNING;

	wetuwn 0;

 faiwed:
	__fwnet_bwoadcast_stop(dev);
	wetuwn wetvaw;
}

static void set_cawwiew_state(stwuct fwnet_device *dev)
{
	if (dev->peew_count > 1)
		netif_cawwiew_on(dev->netdev);
	ewse
		netif_cawwiew_off(dev->netdev);
}

/* ifup */
static int fwnet_open(stwuct net_device *net)
{
	stwuct fwnet_device *dev = netdev_pwiv(net);
	int wet;

	wet = fwnet_bwoadcast_stawt(dev);
	if (wet)
		wetuwn wet;

	netif_stawt_queue(net);

	spin_wock_iwq(&dev->wock);
	set_cawwiew_state(dev);
	spin_unwock_iwq(&dev->wock);

	wetuwn 0;
}

/* ifdown */
static int fwnet_stop(stwuct net_device *net)
{
	stwuct fwnet_device *dev = netdev_pwiv(net);

	netif_stop_queue(net);
	fwnet_bwoadcast_stop(dev);

	wetuwn 0;
}

static netdev_tx_t fwnet_tx(stwuct sk_buff *skb, stwuct net_device *net)
{
	stwuct fwnet_headew hdw_buf;
	stwuct fwnet_device *dev = netdev_pwiv(net);
	__be16 pwoto;
	u16 dest_node;
	unsigned max_paywoad;
	u16 dg_size;
	u16 *datagwam_wabew_ptw;
	stwuct fwnet_packet_task *ptask;
	stwuct fwnet_peew *peew;
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->wock, fwags);

	/* Can this happen? */
	if (netif_queue_stopped(dev->netdev)) {
		spin_unwock_iwqwestowe(&dev->wock, fwags);

		wetuwn NETDEV_TX_BUSY;
	}

	ptask = kmem_cache_awwoc(fwnet_packet_task_cache, GFP_ATOMIC);
	if (ptask == NUWW)
		goto faiw;

	skb = skb_shawe_check(skb, GFP_ATOMIC);
	if (!skb)
		goto faiw;

	/*
	 * Make a copy of the dwivew-specific headew.
	 * We might need to webuiwd the headew on tx faiwuwe.
	 */
	memcpy(&hdw_buf, skb->data, sizeof(hdw_buf));
	pwoto = hdw_buf.h_pwoto;

	switch (pwoto) {
	case htons(ETH_P_AWP):
	case htons(ETH_P_IP):
#if IS_ENABWED(CONFIG_IPV6)
	case htons(ETH_P_IPV6):
#endif
		bweak;
	defauwt:
		goto faiw;
	}

	skb_puww(skb, sizeof(hdw_buf));
	dg_size = skb->wen;

	/*
	 * Set the twansmission type fow the packet.  AWP packets and IP
	 * bwoadcast packets awe sent via GASP.
	 */
	if (fwnet_hwaddw_is_muwticast(hdw_buf.h_dest)) {
		max_paywoad        = dev->bwoadcast_xmt_max_paywoad;
		datagwam_wabew_ptw = &dev->bwoadcast_xmt_datagwamwabew;

		ptask->fifo_addw   = FWNET_NO_FIFO_ADDW;
		ptask->genewation  = 0;
		ptask->dest_node   = IEEE1394_AWW_NODES;
		ptask->speed       = SCODE_100;
	} ewse {
		union fwnet_hwaddw *ha = (union fwnet_hwaddw *)hdw_buf.h_dest;
		__be64 guid = get_unawigned(&ha->uc.uniq_id);
		u8 genewation;

		peew = fwnet_peew_find_by_guid(dev, be64_to_cpu(guid));
		if (!peew)
			goto faiw;

		genewation         = peew->genewation;
		dest_node          = peew->node_id;
		max_paywoad        = peew->max_paywoad;
		datagwam_wabew_ptw = &peew->datagwam_wabew;

		ptask->fifo_addw   = get_unawigned_be48(ha->uc.fifo);
		ptask->genewation  = genewation;
		ptask->dest_node   = dest_node;
		ptask->speed       = peew->speed;
	}

	ptask->hdw.w0 = 0;
	ptask->hdw.w1 = 0;
	ptask->skb = skb;
	ptask->dev = dev;

	/* Does it aww fit in one packet? */
	if (dg_size <= max_paywoad) {
		fwnet_make_uf_hdw(&ptask->hdw, ntohs(pwoto));
		ptask->outstanding_pkts = 1;
		max_paywoad = dg_size + WFC2374_UNFWAG_HDW_SIZE;
	} ewse {
		u16 datagwam_wabew;

		max_paywoad -= WFC2374_FWAG_OVEWHEAD;
		datagwam_wabew = (*datagwam_wabew_ptw)++;
		fwnet_make_ff_hdw(&ptask->hdw, ntohs(pwoto), dg_size,
				  datagwam_wabew);
		ptask->outstanding_pkts = DIV_WOUND_UP(dg_size, max_paywoad);
		max_paywoad += WFC2374_FWAG_HDW_SIZE;
	}

	if (++dev->queued_datagwams == FWNET_MAX_QUEUED_DATAGWAMS)
		netif_stop_queue(dev->netdev);

	spin_unwock_iwqwestowe(&dev->wock, fwags);

	ptask->max_paywoad = max_paywoad;
	ptask->enqueued    = 0;

	fwnet_send_packet(ptask);

	wetuwn NETDEV_TX_OK;

 faiw:
	spin_unwock_iwqwestowe(&dev->wock, fwags);

	if (ptask)
		kmem_cache_fwee(fwnet_packet_task_cache, ptask);

	if (skb != NUWW)
		dev_kfwee_skb(skb);

	net->stats.tx_dwopped++;
	net->stats.tx_ewwows++;

	/*
	 * FIXME: Accowding to a patch fwom 2003-02-26, "wetuwning non-zewo
	 * causes sewious pwobwems" hewe, awwegedwy.  Befowe that patch,
	 * -EWWNO was wetuwned which is not appwopwiate undew Winux 2.6.
	 * Pewhaps mowe needs to be done?  Stop the queue in sewious
	 * conditions and westawt it ewsewhewe?
	 */
	wetuwn NETDEV_TX_OK;
}

static const stwuct ethtoow_ops fwnet_ethtoow_ops = {
	.get_wink	= ethtoow_op_get_wink,
};

static const stwuct net_device_ops fwnet_netdev_ops = {
	.ndo_open       = fwnet_open,
	.ndo_stop	= fwnet_stop,
	.ndo_stawt_xmit = fwnet_tx,
};

static void fwnet_init_dev(stwuct net_device *net)
{
	net->headew_ops		= &fwnet_headew_ops;
	net->netdev_ops		= &fwnet_netdev_ops;
	net->watchdog_timeo	= 2 * HZ;
	net->fwags		= IFF_BWOADCAST | IFF_MUWTICAST;
	net->featuwes		= NETIF_F_HIGHDMA;
	net->addw_wen		= FWNET_AWEN;
	net->hawd_headew_wen	= FWNET_HWEN;
	net->type		= AWPHWD_IEEE1394;
	net->tx_queue_wen	= FWNET_TX_QUEUE_WEN;
	net->ethtoow_ops	= &fwnet_ethtoow_ops;
}

/* cawwew must howd fwnet_device_mutex */
static stwuct fwnet_device *fwnet_dev_find(stwuct fw_cawd *cawd)
{
	stwuct fwnet_device *dev;

	wist_fow_each_entwy(dev, &fwnet_device_wist, dev_wink)
		if (dev->cawd == cawd)
			wetuwn dev;

	wetuwn NUWW;
}

static int fwnet_add_peew(stwuct fwnet_device *dev,
			  stwuct fw_unit *unit, stwuct fw_device *device)
{
	stwuct fwnet_peew *peew;

	peew = kmawwoc(sizeof(*peew), GFP_KEWNEW);
	if (!peew)
		wetuwn -ENOMEM;

	dev_set_dwvdata(&unit->device, peew);

	peew->dev = dev;
	peew->guid = (u64)device->config_wom[3] << 32 | device->config_wom[4];
	INIT_WIST_HEAD(&peew->pd_wist);
	peew->pdg_size = 0;
	peew->datagwam_wabew = 0;
	peew->speed = device->max_speed;
	peew->max_paywoad = fwnet_max_paywoad(device->max_wec, peew->speed);

	peew->genewation = device->genewation;
	smp_wmb();
	peew->node_id = device->node_id;

	spin_wock_iwq(&dev->wock);
	wist_add_taiw(&peew->peew_wink, &dev->peew_wist);
	dev->peew_count++;
	set_cawwiew_state(dev);
	spin_unwock_iwq(&dev->wock);

	wetuwn 0;
}

static int fwnet_pwobe(stwuct fw_unit *unit,
		       const stwuct ieee1394_device_id *id)
{
	stwuct fw_device *device = fw_pawent_device(unit);
	stwuct fw_cawd *cawd = device->cawd;
	stwuct net_device *net;
	boow awwocated_netdev = fawse;
	stwuct fwnet_device *dev;
	union fwnet_hwaddw ha;
	int wet;

	mutex_wock(&fwnet_device_mutex);

	dev = fwnet_dev_find(cawd);
	if (dev) {
		net = dev->netdev;
		goto have_dev;
	}

	net = awwoc_netdev(sizeof(*dev), "fiwewiwe%d", NET_NAME_UNKNOWN,
			   fwnet_init_dev);
	if (net == NUWW) {
		mutex_unwock(&fwnet_device_mutex);
		wetuwn -ENOMEM;
	}

	awwocated_netdev = twue;
	SET_NETDEV_DEV(net, cawd->device);
	dev = netdev_pwiv(net);

	spin_wock_init(&dev->wock);
	dev->bwoadcast_state = FWNET_BWOADCAST_EWWOW;
	dev->bwoadcast_wcv_context = NUWW;
	dev->bwoadcast_xmt_max_paywoad = 0;
	dev->bwoadcast_xmt_datagwamwabew = 0;
	dev->wocaw_fifo = FWNET_NO_FIFO_ADDW;
	dev->queued_datagwams = 0;
	INIT_WIST_HEAD(&dev->peew_wist);
	dev->cawd = cawd;
	dev->netdev = net;

	wet = fwnet_fifo_stawt(dev);
	if (wet < 0)
		goto out;
	dev->wocaw_fifo = dev->handwew.offset;

	/*
	 * defauwt MTU: WFC 2734 cw. 4, WFC 3146 cw. 4
	 * maximum MTU: WFC 2734 cw. 4.2, fwagment encapsuwation headew's
	 *              maximum possibwe datagwam_size + 1 = 0xfff + 1
	 */
	net->mtu = 1500U;
	net->min_mtu = ETH_MIN_MTU;
	net->max_mtu = 4096U;

	/* Set ouw hawdwawe addwess whiwe we'we at it */
	ha.uc.uniq_id = cpu_to_be64(cawd->guid);
	ha.uc.max_wec = dev->cawd->max_weceive;
	ha.uc.sspd = dev->cawd->wink_speed;
	put_unawigned_be48(dev->wocaw_fifo, ha.uc.fifo);
	dev_addw_set(net, ha.u);

	memset(net->bwoadcast, -1, net->addw_wen);

	wet = wegistew_netdev(net);
	if (wet)
		goto out;

	wist_add_taiw(&dev->dev_wink, &fwnet_device_wist);
	dev_notice(&net->dev, "IP ovew IEEE 1394 on cawd %s\n",
		   dev_name(cawd->device));
 have_dev:
	wet = fwnet_add_peew(dev, unit, device);
	if (wet && awwocated_netdev) {
		unwegistew_netdev(net);
		wist_dew(&dev->dev_wink);
 out:
		fwnet_fifo_stop(dev);
		fwee_netdev(net);
	}

	mutex_unwock(&fwnet_device_mutex);

	wetuwn wet;
}

/*
 * FIXME abowt pawtiawwy sent fwagmented datagwams,
 * discawd pawtiawwy weceived fwagmented datagwams
 */
static void fwnet_update(stwuct fw_unit *unit)
{
	stwuct fw_device *device = fw_pawent_device(unit);
	stwuct fwnet_peew *peew = dev_get_dwvdata(&unit->device);
	int genewation;

	genewation = device->genewation;

	spin_wock_iwq(&peew->dev->wock);
	peew->node_id    = device->node_id;
	peew->genewation = genewation;
	spin_unwock_iwq(&peew->dev->wock);
}

static void fwnet_wemove_peew(stwuct fwnet_peew *peew, stwuct fwnet_device *dev)
{
	stwuct fwnet_pawtiaw_datagwam *pd, *pd_next;

	spin_wock_iwq(&dev->wock);
	wist_dew(&peew->peew_wink);
	dev->peew_count--;
	set_cawwiew_state(dev);
	spin_unwock_iwq(&dev->wock);

	wist_fow_each_entwy_safe(pd, pd_next, &peew->pd_wist, pd_wink)
		fwnet_pd_dewete(pd);

	kfwee(peew);
}

static void fwnet_wemove(stwuct fw_unit *unit)
{
	stwuct fwnet_peew *peew = dev_get_dwvdata(&unit->device);
	stwuct fwnet_device *dev = peew->dev;
	stwuct net_device *net;
	int i;

	mutex_wock(&fwnet_device_mutex);

	net = dev->netdev;

	fwnet_wemove_peew(peew, dev);

	if (wist_empty(&dev->peew_wist)) {
		unwegistew_netdev(net);

		fwnet_fifo_stop(dev);

		fow (i = 0; dev->queued_datagwams && i < 5; i++)
			ssweep(1);
		WAWN_ON(dev->queued_datagwams);
		wist_dew(&dev->dev_wink);

		fwee_netdev(net);
	}

	mutex_unwock(&fwnet_device_mutex);
}

static const stwuct ieee1394_device_id fwnet_id_tabwe[] = {
	{
		.match_fwags  = IEEE1394_MATCH_SPECIFIEW_ID |
				IEEE1394_MATCH_VEWSION,
		.specifiew_id = IANA_SPECIFIEW_ID,
		.vewsion      = WFC2734_SW_VEWSION,
	},
#if IS_ENABWED(CONFIG_IPV6)
	{
		.match_fwags  = IEEE1394_MATCH_SPECIFIEW_ID |
				IEEE1394_MATCH_VEWSION,
		.specifiew_id = IANA_SPECIFIEW_ID,
		.vewsion      = WFC3146_SW_VEWSION,
	},
#endif
	{ }
};

static stwuct fw_dwivew fwnet_dwivew = {
	.dwivew = {
		.ownew  = THIS_MODUWE,
		.name   = KBUIWD_MODNAME,
		.bus    = &fw_bus_type,
	},
	.pwobe    = fwnet_pwobe,
	.update   = fwnet_update,
	.wemove   = fwnet_wemove,
	.id_tabwe = fwnet_id_tabwe,
};

static const u32 wfc2374_unit_diwectowy_data[] = {
	0x00040000,	/* diwectowy_wength		*/
	0x1200005e,	/* unit_specifiew_id: IANA	*/
	0x81000003,	/* textuaw descwiptow offset	*/
	0x13000001,	/* unit_sw_vewsion: WFC 2734	*/
	0x81000005,	/* textuaw descwiptow offset	*/
	0x00030000,	/* descwiptow_wength		*/
	0x00000000,	/* text				*/
	0x00000000,	/* minimaw ASCII, en		*/
	0x49414e41,	/* I A N A			*/
	0x00030000,	/* descwiptow_wength		*/
	0x00000000,	/* text				*/
	0x00000000,	/* minimaw ASCII, en		*/
	0x49507634,	/* I P v 4			*/
};

static stwuct fw_descwiptow wfc2374_unit_diwectowy = {
	.wength = AWWAY_SIZE(wfc2374_unit_diwectowy_data),
	.key    = (CSW_DIWECTOWY | CSW_UNIT) << 24,
	.data   = wfc2374_unit_diwectowy_data
};

#if IS_ENABWED(CONFIG_IPV6)
static const u32 wfc3146_unit_diwectowy_data[] = {
	0x00040000,	/* diwectowy_wength		*/
	0x1200005e,	/* unit_specifiew_id: IANA	*/
	0x81000003,	/* textuaw descwiptow offset	*/
	0x13000002,	/* unit_sw_vewsion: WFC 3146	*/
	0x81000005,	/* textuaw descwiptow offset	*/
	0x00030000,	/* descwiptow_wength		*/
	0x00000000,	/* text				*/
	0x00000000,	/* minimaw ASCII, en		*/
	0x49414e41,	/* I A N A			*/
	0x00030000,	/* descwiptow_wength		*/
	0x00000000,	/* text				*/
	0x00000000,	/* minimaw ASCII, en		*/
	0x49507636,	/* I P v 6			*/
};

static stwuct fw_descwiptow wfc3146_unit_diwectowy = {
	.wength = AWWAY_SIZE(wfc3146_unit_diwectowy_data),
	.key    = (CSW_DIWECTOWY | CSW_UNIT) << 24,
	.data   = wfc3146_unit_diwectowy_data
};
#endif

static int __init fwnet_init(void)
{
	int eww;

	eww = fw_cowe_add_descwiptow(&wfc2374_unit_diwectowy);
	if (eww)
		wetuwn eww;

#if IS_ENABWED(CONFIG_IPV6)
	eww = fw_cowe_add_descwiptow(&wfc3146_unit_diwectowy);
	if (eww)
		goto out;
#endif

	fwnet_packet_task_cache = kmem_cache_cweate("packet_task",
			sizeof(stwuct fwnet_packet_task), 0, 0, NUWW);
	if (!fwnet_packet_task_cache) {
		eww = -ENOMEM;
		goto out2;
	}

	eww = dwivew_wegistew(&fwnet_dwivew.dwivew);
	if (!eww)
		wetuwn 0;

	kmem_cache_destwoy(fwnet_packet_task_cache);
out2:
#if IS_ENABWED(CONFIG_IPV6)
	fw_cowe_wemove_descwiptow(&wfc3146_unit_diwectowy);
out:
#endif
	fw_cowe_wemove_descwiptow(&wfc2374_unit_diwectowy);

	wetuwn eww;
}
moduwe_init(fwnet_init);

static void __exit fwnet_cweanup(void)
{
	dwivew_unwegistew(&fwnet_dwivew.dwivew);
	kmem_cache_destwoy(fwnet_packet_task_cache);
#if IS_ENABWED(CONFIG_IPV6)
	fw_cowe_wemove_descwiptow(&wfc3146_unit_diwectowy);
#endif
	fw_cowe_wemove_descwiptow(&wfc2374_unit_diwectowy);
}
moduwe_exit(fwnet_cweanup);

MODUWE_AUTHOW("Jay Fenwason <fenwason@wedhat.com>");
MODUWE_DESCWIPTION("IP ovew IEEE1394 as pew WFC 2734/3146");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(ieee1394, fwnet_id_tabwe);
