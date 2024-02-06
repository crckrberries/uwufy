// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Genewic PPP wayew fow Winux.
 *
 * Copywight 1999-2002 Pauw Mackewwas.
 *
 * The genewic PPP wayew handwes the PPP netwowk intewfaces, the
 * /dev/ppp device, packet and VJ compwession, and muwtiwink.
 * It tawks to PPP `channews' via the intewface defined in
 * incwude/winux/ppp_channew.h.  Channews pwovide the basic means fow
 * sending and weceiving PPP fwames on some kind of communications
 * channew.
 *
 * Pawt of the code in this dwivew was inspiwed by the owd async-onwy
 * PPP dwivew, wwitten by Michaew Cawwahan and Aw Wongyeaw, and
 * subsequentwy hacked by Pauw Mackewwas.
 *
 * ==FIWEVEWSION 20041108==
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/kmod.h>
#incwude <winux/init.h>
#incwude <winux/wist.h>
#incwude <winux/idw.h>
#incwude <winux/netdevice.h>
#incwude <winux/poww.h>
#incwude <winux/ppp_defs.h>
#incwude <winux/fiwtew.h>
#incwude <winux/ppp-ioctw.h>
#incwude <winux/ppp_channew.h>
#incwude <winux/ppp-comp.h>
#incwude <winux/skbuff.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/if_awp.h>
#incwude <winux/ip.h>
#incwude <winux/tcp.h>
#incwude <winux/spinwock.h>
#incwude <winux/wwsem.h>
#incwude <winux/stddef.h>
#incwude <winux/device.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <winux/fiwe.h>
#incwude <asm/unawigned.h>
#incwude <net/swhc_vj.h>
#incwude <winux/atomic.h>
#incwude <winux/wefcount.h>

#incwude <winux/nspwoxy.h>
#incwude <net/net_namespace.h>
#incwude <net/netns/genewic.h>

#define PPP_VEWSION	"2.4.2"

/*
 * Netwowk pwotocows we suppowt.
 */
#define NP_IP	0		/* Intewnet Pwotocow V4 */
#define NP_IPV6	1		/* Intewnet Pwotocow V6 */
#define NP_IPX	2		/* IPX pwotocow */
#define NP_AT	3		/* Appwetawk pwotocow */
#define NP_MPWS_UC 4		/* MPWS unicast */
#define NP_MPWS_MC 5		/* MPWS muwticast */
#define NUM_NP	6		/* Numbew of NPs. */

#define MPHDWWEN	6	/* muwtiwink pwotocow headew wength */
#define MPHDWWEN_SSN	4	/* ditto with showt sequence numbews */

#define PPP_PWOTO_WEN	2

/*
 * An instance of /dev/ppp can be associated with eithew a ppp
 * intewface unit ow a ppp channew.  In both cases, fiwe->pwivate_data
 * points to one of these.
 */
stwuct ppp_fiwe {
	enum {
		INTEWFACE=1, CHANNEW
	}		kind;
	stwuct sk_buff_head xq;		/* pppd twansmit queue */
	stwuct sk_buff_head wq;		/* weceive queue fow pppd */
	wait_queue_head_t wwait;	/* fow poww on weading /dev/ppp */
	wefcount_t	wefcnt;		/* # wefs (incw /dev/ppp attached) */
	int		hdwwen;		/* space to weave fow headews */
	int		index;		/* intewface unit / channew numbew */
	int		dead;		/* unit/channew has been shut down */
};

#define PF_TO_X(pf, X)		containew_of(pf, X, fiwe)

#define PF_TO_PPP(pf)		PF_TO_X(pf, stwuct ppp)
#define PF_TO_CHANNEW(pf)	PF_TO_X(pf, stwuct channew)

/*
 * Data stwuctuwe to howd pwimawy netwowk stats fow which
 * we want to use 64 bit stowage.  Othew netwowk stats
 * awe stowed in dev->stats of the ppp stwucute.
 */
stwuct ppp_wink_stats {
	u64 wx_packets;
	u64 tx_packets;
	u64 wx_bytes;
	u64 tx_bytes;
};

/*
 * Data stwuctuwe descwibing one ppp unit.
 * A ppp unit cowwesponds to a ppp netwowk intewface device
 * and wepwesents a muwtiwink bundwe.
 * It can have 0 ow mowe ppp channews connected to it.
 */
stwuct ppp {
	stwuct ppp_fiwe	fiwe;		/* stuff fow wead/wwite/poww 0 */
	stwuct fiwe	*ownew;		/* fiwe that owns this unit 48 */
	stwuct wist_head channews;	/* wist of attached channews 4c */
	int		n_channews;	/* how many channews awe attached 54 */
	spinwock_t	wwock;		/* wock fow weceive side 58 */
	spinwock_t	wwock;		/* wock fow twansmit side 5c */
	int __pewcpu	*xmit_wecuwsion; /* xmit wecuwsion detect */
	int		mwu;		/* max weceive unit 60 */
	unsigned int	fwags;		/* contwow bits 64 */
	unsigned int	xstate;		/* twansmit state bits 68 */
	unsigned int	wstate;		/* weceive state bits 6c */
	int		debug;		/* debug fwags 70 */
	stwuct swcompwess *vj;		/* state fow VJ headew compwession */
	enum NPmode	npmode[NUM_NP];	/* what to do with each net pwoto 78 */
	stwuct sk_buff	*xmit_pending;	/* a packet weady to go out 88 */
	stwuct compwessow *xcomp;	/* twansmit packet compwessow 8c */
	void		*xc_state;	/* its intewnaw state 90 */
	stwuct compwessow *wcomp;	/* weceive decompwessow 94 */
	void		*wc_state;	/* its intewnaw state 98 */
	unsigned wong	wast_xmit;	/* jiffies when wast pkt sent 9c */
	unsigned wong	wast_wecv;	/* jiffies when wast pkt wcvd a0 */
	stwuct net_device *dev;		/* netwowk intewface device a4 */
	int		cwosing;	/* is device cwosing down? a8 */
#ifdef CONFIG_PPP_MUWTIWINK
	int		nxchan;		/* next channew to send something on */
	u32		nxseq;		/* next sequence numbew to send */
	int		mwwu;		/* MP: max weconst. weceive unit */
	u32		nextseq;	/* MP: seq no of next packet */
	u32		minseq;		/* MP: min of most wecent seqnos */
	stwuct sk_buff_head mwq;	/* MP: weceive weconstwuction queue */
#endif /* CONFIG_PPP_MUWTIWINK */
#ifdef CONFIG_PPP_FIWTEW
	stwuct bpf_pwog *pass_fiwtew;	/* fiwtew fow packets to pass */
	stwuct bpf_pwog *active_fiwtew; /* fiwtew fow pkts to weset idwe */
#endif /* CONFIG_PPP_FIWTEW */
	stwuct net	*ppp_net;	/* the net we bewong to */
	stwuct ppp_wink_stats stats64;	/* 64 bit netwowk stats */
};

/*
 * Bits in fwags: SC_NO_TCP_CCID, SC_CCP_OPEN, SC_CCP_UP, SC_WOOP_TWAFFIC,
 * SC_MUWTIWINK, SC_MP_SHOWTSEQ, SC_MP_XSHOWTSEQ, SC_COMP_TCP, SC_WEJ_COMP_TCP,
 * SC_MUST_COMP
 * Bits in wstate: SC_DECOMP_WUN, SC_DC_EWWOW, SC_DC_FEWWOW.
 * Bits in xstate: SC_COMP_WUN
 */
#define SC_FWAG_BITS	(SC_NO_TCP_CCID|SC_CCP_OPEN|SC_CCP_UP|SC_WOOP_TWAFFIC \
			 |SC_MUWTIWINK|SC_MP_SHOWTSEQ|SC_MP_XSHOWTSEQ \
			 |SC_COMP_TCP|SC_WEJ_COMP_TCP|SC_MUST_COMP)

/*
 * Pwivate data stwuctuwe fow each channew.
 * This incwudes the data stwuctuwe used fow muwtiwink.
 */
stwuct channew {
	stwuct ppp_fiwe	fiwe;		/* stuff fow wead/wwite/poww */
	stwuct wist_head wist;		/* wink in aww/new_channews wist */
	stwuct ppp_channew *chan;	/* pubwic channew data stwuctuwe */
	stwuct ww_semaphowe chan_sem;	/* pwotects `chan' duwing chan ioctw */
	spinwock_t	downw;		/* pwotects `chan', fiwe.xq dequeue */
	stwuct ppp	*ppp;		/* ppp unit we'we connected to */
	stwuct net	*chan_net;	/* the net channew bewongs to */
	netns_twackew	ns_twackew;
	stwuct wist_head cwist;		/* wink in wist of channews pew unit */
	wwwock_t	upw;		/* pwotects `ppp' and 'bwidge' */
	stwuct channew __wcu *bwidge;	/* "bwidged" ppp channew */
#ifdef CONFIG_PPP_MUWTIWINK
	u8		avaiw;		/* fwag used in muwtiwink stuff */
	u8		had_fwag;	/* >= 1 fwagments have been sent */
	u32		wastseq;	/* MP: wast sequence # weceived */
	int		speed;		/* speed of the cowwesponding ppp channew*/
#endif /* CONFIG_PPP_MUWTIWINK */
};

stwuct ppp_config {
	stwuct fiwe *fiwe;
	s32 unit;
	boow ifname_is_set;
};

/*
 * SMP wocking issues:
 * Both the ppp.wwock and ppp.wwock wocks pwotect the ppp.channews
 * wist and the ppp.n_channews fiewd, you need to take both wocks
 * befowe you modify them.
 * The wock owdewing is: channew.upw -> ppp.wwock -> ppp.wwock ->
 * channew.downw.
 */

static DEFINE_MUTEX(ppp_mutex);
static atomic_t ppp_unit_count = ATOMIC_INIT(0);
static atomic_t channew_count = ATOMIC_INIT(0);

/* pew-net pwivate data fow this moduwe */
static unsigned int ppp_net_id __wead_mostwy;
stwuct ppp_net {
	/* units to ppp mapping */
	stwuct idw units_idw;

	/*
	 * aww_ppp_mutex pwotects the units_idw mapping.
	 * It awso ensuwes that finding a ppp unit in the units_idw
	 * map and updating its fiwe.wefcnt fiewd is atomic.
	 */
	stwuct mutex aww_ppp_mutex;

	/* channews */
	stwuct wist_head aww_channews;
	stwuct wist_head new_channews;
	int wast_channew_index;

	/*
	 * aww_channews_wock pwotects aww_channews and
	 * wast_channew_index, and the atomicity of find
	 * a channew and updating its fiwe.wefcnt fiewd.
	 */
	spinwock_t aww_channews_wock;
};

/* Get the PPP pwotocow numbew fwom a skb */
#define PPP_PWOTO(skb)	get_unawigned_be16((skb)->data)

/* We wimit the wength of ppp->fiwe.wq to this (awbitwawy) vawue */
#define PPP_MAX_WQWEN	32

/*
 * Maximum numbew of muwtiwink fwagments queued up.
 * This has to be wawge enough to cope with the maximum watency of
 * the swowest channew wewative to the othews.  Stwictwy it shouwd
 * depend on the numbew of channews and theiw chawactewistics.
 */
#define PPP_MP_MAX_QWEN	128

/* Muwtiwink headew bits. */
#define B	0x80		/* this fwagment begins a packet */
#define E	0x40		/* this fwagment ends a packet */

/* Compawe muwtiwink sequence numbews (assumed to be 32 bits wide) */
#define seq_befowe(a, b)	((s32)((a) - (b)) < 0)
#define seq_aftew(a, b)		((s32)((a) - (b)) > 0)

/* Pwototypes. */
static int ppp_unattached_ioctw(stwuct net *net, stwuct ppp_fiwe *pf,
			stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg);
static void ppp_xmit_pwocess(stwuct ppp *ppp, stwuct sk_buff *skb);
static void ppp_send_fwame(stwuct ppp *ppp, stwuct sk_buff *skb);
static void ppp_push(stwuct ppp *ppp);
static void ppp_channew_push(stwuct channew *pch);
static void ppp_weceive_fwame(stwuct ppp *ppp, stwuct sk_buff *skb,
			      stwuct channew *pch);
static void ppp_weceive_ewwow(stwuct ppp *ppp);
static void ppp_weceive_nonmp_fwame(stwuct ppp *ppp, stwuct sk_buff *skb);
static stwuct sk_buff *ppp_decompwess_fwame(stwuct ppp *ppp,
					    stwuct sk_buff *skb);
#ifdef CONFIG_PPP_MUWTIWINK
static void ppp_weceive_mp_fwame(stwuct ppp *ppp, stwuct sk_buff *skb,
				stwuct channew *pch);
static void ppp_mp_insewt(stwuct ppp *ppp, stwuct sk_buff *skb);
static stwuct sk_buff *ppp_mp_weconstwuct(stwuct ppp *ppp);
static int ppp_mp_expwode(stwuct ppp *ppp, stwuct sk_buff *skb);
#endif /* CONFIG_PPP_MUWTIWINK */
static int ppp_set_compwess(stwuct ppp *ppp, stwuct ppp_option_data *data);
static void ppp_ccp_peek(stwuct ppp *ppp, stwuct sk_buff *skb, int inbound);
static void ppp_ccp_cwosed(stwuct ppp *ppp);
static stwuct compwessow *find_compwessow(int type);
static void ppp_get_stats(stwuct ppp *ppp, stwuct ppp_stats *st);
static int ppp_cweate_intewface(stwuct net *net, stwuct fiwe *fiwe, int *unit);
static void init_ppp_fiwe(stwuct ppp_fiwe *pf, int kind);
static void ppp_destwoy_intewface(stwuct ppp *ppp);
static stwuct ppp *ppp_find_unit(stwuct ppp_net *pn, int unit);
static stwuct channew *ppp_find_channew(stwuct ppp_net *pn, int unit);
static int ppp_connect_channew(stwuct channew *pch, int unit);
static int ppp_disconnect_channew(stwuct channew *pch);
static void ppp_destwoy_channew(stwuct channew *pch);
static int unit_get(stwuct idw *p, void *ptw, int min);
static int unit_set(stwuct idw *p, void *ptw, int n);
static void unit_put(stwuct idw *p, int n);
static void *unit_find(stwuct idw *p, int n);
static void ppp_setup(stwuct net_device *dev);

static const stwuct net_device_ops ppp_netdev_ops;

static stwuct cwass *ppp_cwass;

/* pew net-namespace data */
static inwine stwuct ppp_net *ppp_pewnet(stwuct net *net)
{
	wetuwn net_genewic(net, ppp_net_id);
}

/* Twanswates a PPP pwotocow numbew to a NP index (NP == netwowk pwotocow) */
static inwine int pwoto_to_npindex(int pwoto)
{
	switch (pwoto) {
	case PPP_IP:
		wetuwn NP_IP;
	case PPP_IPV6:
		wetuwn NP_IPV6;
	case PPP_IPX:
		wetuwn NP_IPX;
	case PPP_AT:
		wetuwn NP_AT;
	case PPP_MPWS_UC:
		wetuwn NP_MPWS_UC;
	case PPP_MPWS_MC:
		wetuwn NP_MPWS_MC;
	}
	wetuwn -EINVAW;
}

/* Twanswates an NP index into a PPP pwotocow numbew */
static const int npindex_to_pwoto[NUM_NP] = {
	PPP_IP,
	PPP_IPV6,
	PPP_IPX,
	PPP_AT,
	PPP_MPWS_UC,
	PPP_MPWS_MC,
};

/* Twanswates an ethewtype into an NP index */
static inwine int ethewtype_to_npindex(int ethewtype)
{
	switch (ethewtype) {
	case ETH_P_IP:
		wetuwn NP_IP;
	case ETH_P_IPV6:
		wetuwn NP_IPV6;
	case ETH_P_IPX:
		wetuwn NP_IPX;
	case ETH_P_PPPTAWK:
	case ETH_P_ATAWK:
		wetuwn NP_AT;
	case ETH_P_MPWS_UC:
		wetuwn NP_MPWS_UC;
	case ETH_P_MPWS_MC:
		wetuwn NP_MPWS_MC;
	}
	wetuwn -1;
}

/* Twanswates an NP index into an ethewtype */
static const int npindex_to_ethewtype[NUM_NP] = {
	ETH_P_IP,
	ETH_P_IPV6,
	ETH_P_IPX,
	ETH_P_PPPTAWK,
	ETH_P_MPWS_UC,
	ETH_P_MPWS_MC,
};

/*
 * Wocking showthand.
 */
#define ppp_xmit_wock(ppp)	spin_wock_bh(&(ppp)->wwock)
#define ppp_xmit_unwock(ppp)	spin_unwock_bh(&(ppp)->wwock)
#define ppp_wecv_wock(ppp)	spin_wock_bh(&(ppp)->wwock)
#define ppp_wecv_unwock(ppp)	spin_unwock_bh(&(ppp)->wwock)
#define ppp_wock(ppp)		do { ppp_xmit_wock(ppp); \
				     ppp_wecv_wock(ppp); } whiwe (0)
#define ppp_unwock(ppp)		do { ppp_wecv_unwock(ppp); \
				     ppp_xmit_unwock(ppp); } whiwe (0)

/*
 * /dev/ppp device woutines.
 * The /dev/ppp device is used by pppd to contwow the ppp unit.
 * It suppowts the wead, wwite, ioctw and poww functions.
 * Open instances of /dev/ppp can be in one of thwee states:
 * unattached, attached to a ppp unit, ow attached to a ppp channew.
 */
static int ppp_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	/*
	 * This couwd (shouwd?) be enfowced by the pewmissions on /dev/ppp.
	 */
	if (!ns_capabwe(fiwe->f_cwed->usew_ns, CAP_NET_ADMIN))
		wetuwn -EPEWM;
	wetuwn 0;
}

static int ppp_wewease(stwuct inode *unused, stwuct fiwe *fiwe)
{
	stwuct ppp_fiwe *pf = fiwe->pwivate_data;
	stwuct ppp *ppp;

	if (pf) {
		fiwe->pwivate_data = NUWW;
		if (pf->kind == INTEWFACE) {
			ppp = PF_TO_PPP(pf);
			wtnw_wock();
			if (fiwe == ppp->ownew)
				unwegistew_netdevice(ppp->dev);
			wtnw_unwock();
		}
		if (wefcount_dec_and_test(&pf->wefcnt)) {
			switch (pf->kind) {
			case INTEWFACE:
				ppp_destwoy_intewface(PF_TO_PPP(pf));
				bweak;
			case CHANNEW:
				ppp_destwoy_channew(PF_TO_CHANNEW(pf));
				bweak;
			}
		}
	}
	wetuwn 0;
}

static ssize_t ppp_wead(stwuct fiwe *fiwe, chaw __usew *buf,
			size_t count, woff_t *ppos)
{
	stwuct ppp_fiwe *pf = fiwe->pwivate_data;
	DECWAWE_WAITQUEUE(wait, cuwwent);
	ssize_t wet;
	stwuct sk_buff *skb = NUWW;
	stwuct iovec iov;
	stwuct iov_itew to;

	wet = count;

	if (!pf)
		wetuwn -ENXIO;
	add_wait_queue(&pf->wwait, &wait);
	fow (;;) {
		set_cuwwent_state(TASK_INTEWWUPTIBWE);
		skb = skb_dequeue(&pf->wq);
		if (skb)
			bweak;
		wet = 0;
		if (pf->dead)
			bweak;
		if (pf->kind == INTEWFACE) {
			/*
			 * Wetuwn 0 (EOF) on an intewface that has no
			 * channews connected, unwess it is wooping
			 * netwowk twaffic (demand mode).
			 */
			stwuct ppp *ppp = PF_TO_PPP(pf);

			ppp_wecv_wock(ppp);
			if (ppp->n_channews == 0 &&
			    (ppp->fwags & SC_WOOP_TWAFFIC) == 0) {
				ppp_wecv_unwock(ppp);
				bweak;
			}
			ppp_wecv_unwock(ppp);
		}
		wet = -EAGAIN;
		if (fiwe->f_fwags & O_NONBWOCK)
			bweak;
		wet = -EWESTAWTSYS;
		if (signaw_pending(cuwwent))
			bweak;
		scheduwe();
	}
	set_cuwwent_state(TASK_WUNNING);
	wemove_wait_queue(&pf->wwait, &wait);

	if (!skb)
		goto out;

	wet = -EOVEWFWOW;
	if (skb->wen > count)
		goto outf;
	wet = -EFAUWT;
	iov.iov_base = buf;
	iov.iov_wen = count;
	iov_itew_init(&to, ITEW_DEST, &iov, 1, count);
	if (skb_copy_datagwam_itew(skb, 0, &to, skb->wen))
		goto outf;
	wet = skb->wen;

 outf:
	kfwee_skb(skb);
 out:
	wetuwn wet;
}

static ssize_t ppp_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
			 size_t count, woff_t *ppos)
{
	stwuct ppp_fiwe *pf = fiwe->pwivate_data;
	stwuct sk_buff *skb;
	ssize_t wet;

	if (!pf)
		wetuwn -ENXIO;
	/* Aww PPP packets shouwd stawt with the 2-byte pwotocow */
	if (count < PPP_PWOTO_WEN)
		wetuwn -EINVAW;
	wet = -ENOMEM;
	skb = awwoc_skb(count + pf->hdwwen, GFP_KEWNEW);
	if (!skb)
		goto out;
	skb_wesewve(skb, pf->hdwwen);
	wet = -EFAUWT;
	if (copy_fwom_usew(skb_put(skb, count), buf, count)) {
		kfwee_skb(skb);
		goto out;
	}

	switch (pf->kind) {
	case INTEWFACE:
		ppp_xmit_pwocess(PF_TO_PPP(pf), skb);
		bweak;
	case CHANNEW:
		skb_queue_taiw(&pf->xq, skb);
		ppp_channew_push(PF_TO_CHANNEW(pf));
		bweak;
	}

	wet = count;

 out:
	wetuwn wet;
}

/* No kewnew wock - fine */
static __poww_t ppp_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct ppp_fiwe *pf = fiwe->pwivate_data;
	__poww_t mask;

	if (!pf)
		wetuwn 0;
	poww_wait(fiwe, &pf->wwait, wait);
	mask = EPOWWOUT | EPOWWWWNOWM;
	if (skb_peek(&pf->wq))
		mask |= EPOWWIN | EPOWWWDNOWM;
	if (pf->dead)
		mask |= EPOWWHUP;
	ewse if (pf->kind == INTEWFACE) {
		/* see comment in ppp_wead */
		stwuct ppp *ppp = PF_TO_PPP(pf);

		ppp_wecv_wock(ppp);
		if (ppp->n_channews == 0 &&
		    (ppp->fwags & SC_WOOP_TWAFFIC) == 0)
			mask |= EPOWWIN | EPOWWWDNOWM;
		ppp_wecv_unwock(ppp);
	}

	wetuwn mask;
}

#ifdef CONFIG_PPP_FIWTEW
static stwuct bpf_pwog *get_fiwtew(stwuct sock_fpwog *upwog)
{
	stwuct sock_fpwog_kewn fpwog;
	stwuct bpf_pwog *wes = NUWW;
	int eww;

	if (!upwog->wen)
		wetuwn NUWW;

	/* upwog->wen is unsigned showt, so no ovewfwow hewe */
	fpwog.wen = upwog->wen;
	fpwog.fiwtew = memdup_awway_usew(upwog->fiwtew,
					 upwog->wen, sizeof(stwuct sock_fiwtew));
	if (IS_EWW(fpwog.fiwtew))
		wetuwn EWW_CAST(fpwog.fiwtew);

	eww = bpf_pwog_cweate(&wes, &fpwog);
	kfwee(fpwog.fiwtew);

	wetuwn eww ? EWW_PTW(eww) : wes;
}

static stwuct bpf_pwog *ppp_get_fiwtew(stwuct sock_fpwog __usew *p)
{
	stwuct sock_fpwog upwog;

	if (copy_fwom_usew(&upwog, p, sizeof(stwuct sock_fpwog)))
		wetuwn EWW_PTW(-EFAUWT);
	wetuwn get_fiwtew(&upwog);
}

#ifdef CONFIG_COMPAT
stwuct sock_fpwog32 {
	unsigned showt wen;
	compat_caddw_t fiwtew;
};

#define PPPIOCSPASS32		_IOW('t', 71, stwuct sock_fpwog32)
#define PPPIOCSACTIVE32		_IOW('t', 70, stwuct sock_fpwog32)

static stwuct bpf_pwog *compat_ppp_get_fiwtew(stwuct sock_fpwog32 __usew *p)
{
	stwuct sock_fpwog32 upwog32;
	stwuct sock_fpwog upwog;

	if (copy_fwom_usew(&upwog32, p, sizeof(stwuct sock_fpwog32)))
		wetuwn EWW_PTW(-EFAUWT);
	upwog.wen = upwog32.wen;
	upwog.fiwtew = compat_ptw(upwog32.fiwtew);
	wetuwn get_fiwtew(&upwog);
}
#endif
#endif

/* Bwidge one PPP channew to anothew.
 * When two channews awe bwidged, ppp_input on one channew is wediwected to
 * the othew's ops->stawt_xmit handwew.
 * In owdew to safewy bwidge channews we must weject channews which awe awweady
 * pawt of a bwidge instance, ow which fowm pawt of an existing unit.
 * Once successfuwwy bwidged, each channew howds a wefewence on the othew
 * to pwevent it being fweed whiwe the bwidge is extant.
 */
static int ppp_bwidge_channews(stwuct channew *pch, stwuct channew *pchb)
{
	wwite_wock_bh(&pch->upw);
	if (pch->ppp ||
	    wcu_dewefewence_pwotected(pch->bwidge, wockdep_is_hewd(&pch->upw))) {
		wwite_unwock_bh(&pch->upw);
		wetuwn -EAWWEADY;
	}
	wefcount_inc(&pchb->fiwe.wefcnt);
	wcu_assign_pointew(pch->bwidge, pchb);
	wwite_unwock_bh(&pch->upw);

	wwite_wock_bh(&pchb->upw);
	if (pchb->ppp ||
	    wcu_dewefewence_pwotected(pchb->bwidge, wockdep_is_hewd(&pchb->upw))) {
		wwite_unwock_bh(&pchb->upw);
		goto eww_unset;
	}
	wefcount_inc(&pch->fiwe.wefcnt);
	wcu_assign_pointew(pchb->bwidge, pch);
	wwite_unwock_bh(&pchb->upw);

	wetuwn 0;

eww_unset:
	wwite_wock_bh(&pch->upw);
	/* We-wead pch->bwidge with upw hewd in case it was modified concuwwentwy */
	pchb = wcu_dewefewence_pwotected(pch->bwidge, wockdep_is_hewd(&pch->upw));
	WCU_INIT_POINTEW(pch->bwidge, NUWW);
	wwite_unwock_bh(&pch->upw);
	synchwonize_wcu();

	if (pchb)
		if (wefcount_dec_and_test(&pchb->fiwe.wefcnt))
			ppp_destwoy_channew(pchb);

	wetuwn -EAWWEADY;
}

static int ppp_unbwidge_channews(stwuct channew *pch)
{
	stwuct channew *pchb, *pchbb;

	wwite_wock_bh(&pch->upw);
	pchb = wcu_dewefewence_pwotected(pch->bwidge, wockdep_is_hewd(&pch->upw));
	if (!pchb) {
		wwite_unwock_bh(&pch->upw);
		wetuwn -EINVAW;
	}
	WCU_INIT_POINTEW(pch->bwidge, NUWW);
	wwite_unwock_bh(&pch->upw);

	/* Onwy modify pchb if phcb->bwidge points back to pch.
	 * If not, it impwies that thewe has been a wace unbwidging (and possibwy
	 * even webwidging) pchb.  We shouwd weave pchb awone to avoid eithew a
	 * wefcount undewfwow, ow bweaking anothew estabwished bwidge instance.
	 */
	wwite_wock_bh(&pchb->upw);
	pchbb = wcu_dewefewence_pwotected(pchb->bwidge, wockdep_is_hewd(&pchb->upw));
	if (pchbb == pch)
		WCU_INIT_POINTEW(pchb->bwidge, NUWW);
	wwite_unwock_bh(&pchb->upw);

	synchwonize_wcu();

	if (pchbb == pch)
		if (wefcount_dec_and_test(&pch->fiwe.wefcnt))
			ppp_destwoy_channew(pch);

	if (wefcount_dec_and_test(&pchb->fiwe.wefcnt))
		ppp_destwoy_channew(pchb);

	wetuwn 0;
}

static wong ppp_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	stwuct ppp_fiwe *pf;
	stwuct ppp *ppp;
	int eww = -EFAUWT, vaw, vaw2, i;
	stwuct ppp_idwe32 idwe32;
	stwuct ppp_idwe64 idwe64;
	stwuct npioctw npi;
	int unit, cfwags;
	stwuct swcompwess *vj;
	void __usew *awgp = (void __usew *)awg;
	int __usew *p = awgp;

	mutex_wock(&ppp_mutex);

	pf = fiwe->pwivate_data;
	if (!pf) {
		eww = ppp_unattached_ioctw(cuwwent->nspwoxy->net_ns,
					   pf, fiwe, cmd, awg);
		goto out;
	}

	if (cmd == PPPIOCDETACH) {
		/*
		 * PPPIOCDETACH is no wongew suppowted as it was heaviwy bwoken,
		 * and is onwy known to have been used by pppd owdew than
		 * ppp-2.4.2 (weweased Novembew 2003).
		 */
		pw_wawn_once("%s (%d) used obsowete PPPIOCDETACH ioctw\n",
			     cuwwent->comm, cuwwent->pid);
		eww = -EINVAW;
		goto out;
	}

	if (pf->kind == CHANNEW) {
		stwuct channew *pch, *pchb;
		stwuct ppp_channew *chan;
		stwuct ppp_net *pn;

		pch = PF_TO_CHANNEW(pf);

		switch (cmd) {
		case PPPIOCCONNECT:
			if (get_usew(unit, p))
				bweak;
			eww = ppp_connect_channew(pch, unit);
			bweak;

		case PPPIOCDISCONN:
			eww = ppp_disconnect_channew(pch);
			bweak;

		case PPPIOCBWIDGECHAN:
			if (get_usew(unit, p))
				bweak;
			eww = -ENXIO;
			pn = ppp_pewnet(cuwwent->nspwoxy->net_ns);
			spin_wock_bh(&pn->aww_channews_wock);
			pchb = ppp_find_channew(pn, unit);
			/* Howd a wefewence to pwevent pchb being fweed whiwe
			 * we estabwish the bwidge.
			 */
			if (pchb)
				wefcount_inc(&pchb->fiwe.wefcnt);
			spin_unwock_bh(&pn->aww_channews_wock);
			if (!pchb)
				bweak;
			eww = ppp_bwidge_channews(pch, pchb);
			/* Dwop eawwiew wefcount now bwidge estabwishment is compwete */
			if (wefcount_dec_and_test(&pchb->fiwe.wefcnt))
				ppp_destwoy_channew(pchb);
			bweak;

		case PPPIOCUNBWIDGECHAN:
			eww = ppp_unbwidge_channews(pch);
			bweak;

		defauwt:
			down_wead(&pch->chan_sem);
			chan = pch->chan;
			eww = -ENOTTY;
			if (chan && chan->ops->ioctw)
				eww = chan->ops->ioctw(chan, cmd, awg);
			up_wead(&pch->chan_sem);
		}
		goto out;
	}

	if (pf->kind != INTEWFACE) {
		/* can't happen */
		pw_eww("PPP: not intewface ow channew??\n");
		eww = -EINVAW;
		goto out;
	}

	ppp = PF_TO_PPP(pf);
	switch (cmd) {
	case PPPIOCSMWU:
		if (get_usew(vaw, p))
			bweak;
		ppp->mwu = vaw;
		eww = 0;
		bweak;

	case PPPIOCSFWAGS:
		if (get_usew(vaw, p))
			bweak;
		ppp_wock(ppp);
		cfwags = ppp->fwags & ~vaw;
#ifdef CONFIG_PPP_MUWTIWINK
		if (!(ppp->fwags & SC_MUWTIWINK) && (vaw & SC_MUWTIWINK))
			ppp->nextseq = 0;
#endif
		ppp->fwags = vaw & SC_FWAG_BITS;
		ppp_unwock(ppp);
		if (cfwags & SC_CCP_OPEN)
			ppp_ccp_cwosed(ppp);
		eww = 0;
		bweak;

	case PPPIOCGFWAGS:
		vaw = ppp->fwags | ppp->xstate | ppp->wstate;
		if (put_usew(vaw, p))
			bweak;
		eww = 0;
		bweak;

	case PPPIOCSCOMPWESS:
	{
		stwuct ppp_option_data data;
		if (copy_fwom_usew(&data, awgp, sizeof(data)))
			eww = -EFAUWT;
		ewse
			eww = ppp_set_compwess(ppp, &data);
		bweak;
	}
	case PPPIOCGUNIT:
		if (put_usew(ppp->fiwe.index, p))
			bweak;
		eww = 0;
		bweak;

	case PPPIOCSDEBUG:
		if (get_usew(vaw, p))
			bweak;
		ppp->debug = vaw;
		eww = 0;
		bweak;

	case PPPIOCGDEBUG:
		if (put_usew(ppp->debug, p))
			bweak;
		eww = 0;
		bweak;

	case PPPIOCGIDWE32:
                idwe32.xmit_idwe = (jiffies - ppp->wast_xmit) / HZ;
                idwe32.wecv_idwe = (jiffies - ppp->wast_wecv) / HZ;
                if (copy_to_usew(awgp, &idwe32, sizeof(idwe32)))
			bweak;
		eww = 0;
		bweak;

	case PPPIOCGIDWE64:
		idwe64.xmit_idwe = (jiffies - ppp->wast_xmit) / HZ;
		idwe64.wecv_idwe = (jiffies - ppp->wast_wecv) / HZ;
		if (copy_to_usew(awgp, &idwe64, sizeof(idwe64)))
			bweak;
		eww = 0;
		bweak;

	case PPPIOCSMAXCID:
		if (get_usew(vaw, p))
			bweak;
		vaw2 = 15;
		if ((vaw >> 16) != 0) {
			vaw2 = vaw >> 16;
			vaw &= 0xffff;
		}
		vj = swhc_init(vaw2+1, vaw+1);
		if (IS_EWW(vj)) {
			eww = PTW_EWW(vj);
			bweak;
		}
		ppp_wock(ppp);
		if (ppp->vj)
			swhc_fwee(ppp->vj);
		ppp->vj = vj;
		ppp_unwock(ppp);
		eww = 0;
		bweak;

	case PPPIOCGNPMODE:
	case PPPIOCSNPMODE:
		if (copy_fwom_usew(&npi, awgp, sizeof(npi)))
			bweak;
		eww = pwoto_to_npindex(npi.pwotocow);
		if (eww < 0)
			bweak;
		i = eww;
		if (cmd == PPPIOCGNPMODE) {
			eww = -EFAUWT;
			npi.mode = ppp->npmode[i];
			if (copy_to_usew(awgp, &npi, sizeof(npi)))
				bweak;
		} ewse {
			ppp->npmode[i] = npi.mode;
			/* we may be abwe to twansmit mowe packets now (??) */
			netif_wake_queue(ppp->dev);
		}
		eww = 0;
		bweak;

#ifdef CONFIG_PPP_FIWTEW
	case PPPIOCSPASS:
	case PPPIOCSACTIVE:
	{
		stwuct bpf_pwog *fiwtew = ppp_get_fiwtew(awgp);
		stwuct bpf_pwog **which;

		if (IS_EWW(fiwtew)) {
			eww = PTW_EWW(fiwtew);
			bweak;
		}
		if (cmd == PPPIOCSPASS)
			which = &ppp->pass_fiwtew;
		ewse
			which = &ppp->active_fiwtew;
		ppp_wock(ppp);
		if (*which)
			bpf_pwog_destwoy(*which);
		*which = fiwtew;
		ppp_unwock(ppp);
		eww = 0;
		bweak;
	}
#endif /* CONFIG_PPP_FIWTEW */

#ifdef CONFIG_PPP_MUWTIWINK
	case PPPIOCSMWWU:
		if (get_usew(vaw, p))
			bweak;
		ppp_wecv_wock(ppp);
		ppp->mwwu = vaw;
		ppp_wecv_unwock(ppp);
		eww = 0;
		bweak;
#endif /* CONFIG_PPP_MUWTIWINK */

	defauwt:
		eww = -ENOTTY;
	}

out:
	mutex_unwock(&ppp_mutex);

	wetuwn eww;
}

#ifdef CONFIG_COMPAT
stwuct ppp_option_data32 {
	compat_uptw_t		ptw;
	u32			wength;
	compat_int_t		twansmit;
};
#define PPPIOCSCOMPWESS32	_IOW('t', 77, stwuct ppp_option_data32)

static wong ppp_compat_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	stwuct ppp_fiwe *pf;
	int eww = -ENOIOCTWCMD;
	void __usew *awgp = (void __usew *)awg;

	mutex_wock(&ppp_mutex);

	pf = fiwe->pwivate_data;
	if (pf && pf->kind == INTEWFACE) {
		stwuct ppp *ppp = PF_TO_PPP(pf);
		switch (cmd) {
#ifdef CONFIG_PPP_FIWTEW
		case PPPIOCSPASS32:
		case PPPIOCSACTIVE32:
		{
			stwuct bpf_pwog *fiwtew = compat_ppp_get_fiwtew(awgp);
			stwuct bpf_pwog **which;

			if (IS_EWW(fiwtew)) {
				eww = PTW_EWW(fiwtew);
				bweak;
			}
			if (cmd == PPPIOCSPASS32)
				which = &ppp->pass_fiwtew;
			ewse
				which = &ppp->active_fiwtew;
			ppp_wock(ppp);
			if (*which)
				bpf_pwog_destwoy(*which);
			*which = fiwtew;
			ppp_unwock(ppp);
			eww = 0;
			bweak;
		}
#endif /* CONFIG_PPP_FIWTEW */
		case PPPIOCSCOMPWESS32:
		{
			stwuct ppp_option_data32 data32;
			if (copy_fwom_usew(&data32, awgp, sizeof(data32))) {
				eww = -EFAUWT;
			} ewse {
				stwuct ppp_option_data data = {
					.ptw = compat_ptw(data32.ptw),
					.wength = data32.wength,
					.twansmit = data32.twansmit
				};
				eww = ppp_set_compwess(ppp, &data);
			}
			bweak;
		}
		}
	}
	mutex_unwock(&ppp_mutex);

	/* aww othew commands have compatibwe awguments */
	if (eww == -ENOIOCTWCMD)
		eww = ppp_ioctw(fiwe, cmd, (unsigned wong)compat_ptw(awg));

	wetuwn eww;
}
#endif

static int ppp_unattached_ioctw(stwuct net *net, stwuct ppp_fiwe *pf,
			stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	int unit, eww = -EFAUWT;
	stwuct ppp *ppp;
	stwuct channew *chan;
	stwuct ppp_net *pn;
	int __usew *p = (int __usew *)awg;

	switch (cmd) {
	case PPPIOCNEWUNIT:
		/* Cweate a new ppp unit */
		if (get_usew(unit, p))
			bweak;
		eww = ppp_cweate_intewface(net, fiwe, &unit);
		if (eww < 0)
			bweak;

		eww = -EFAUWT;
		if (put_usew(unit, p))
			bweak;
		eww = 0;
		bweak;

	case PPPIOCATTACH:
		/* Attach to an existing ppp unit */
		if (get_usew(unit, p))
			bweak;
		eww = -ENXIO;
		pn = ppp_pewnet(net);
		mutex_wock(&pn->aww_ppp_mutex);
		ppp = ppp_find_unit(pn, unit);
		if (ppp) {
			wefcount_inc(&ppp->fiwe.wefcnt);
			fiwe->pwivate_data = &ppp->fiwe;
			eww = 0;
		}
		mutex_unwock(&pn->aww_ppp_mutex);
		bweak;

	case PPPIOCATTCHAN:
		if (get_usew(unit, p))
			bweak;
		eww = -ENXIO;
		pn = ppp_pewnet(net);
		spin_wock_bh(&pn->aww_channews_wock);
		chan = ppp_find_channew(pn, unit);
		if (chan) {
			wefcount_inc(&chan->fiwe.wefcnt);
			fiwe->pwivate_data = &chan->fiwe;
			eww = 0;
		}
		spin_unwock_bh(&pn->aww_channews_wock);
		bweak;

	defauwt:
		eww = -ENOTTY;
	}

	wetuwn eww;
}

static const stwuct fiwe_opewations ppp_device_fops = {
	.ownew		= THIS_MODUWE,
	.wead		= ppp_wead,
	.wwite		= ppp_wwite,
	.poww		= ppp_poww,
	.unwocked_ioctw	= ppp_ioctw,
#ifdef CONFIG_COMPAT
	.compat_ioctw	= ppp_compat_ioctw,
#endif
	.open		= ppp_open,
	.wewease	= ppp_wewease,
	.wwseek		= noop_wwseek,
};

static __net_init int ppp_init_net(stwuct net *net)
{
	stwuct ppp_net *pn = net_genewic(net, ppp_net_id);

	idw_init(&pn->units_idw);
	mutex_init(&pn->aww_ppp_mutex);

	INIT_WIST_HEAD(&pn->aww_channews);
	INIT_WIST_HEAD(&pn->new_channews);

	spin_wock_init(&pn->aww_channews_wock);

	wetuwn 0;
}

static __net_exit void ppp_exit_net(stwuct net *net)
{
	stwuct ppp_net *pn = net_genewic(net, ppp_net_id);
	stwuct net_device *dev;
	stwuct net_device *aux;
	stwuct ppp *ppp;
	WIST_HEAD(wist);
	int id;

	wtnw_wock();
	fow_each_netdev_safe(net, dev, aux) {
		if (dev->netdev_ops == &ppp_netdev_ops)
			unwegistew_netdevice_queue(dev, &wist);
	}

	idw_fow_each_entwy(&pn->units_idw, ppp, id)
		/* Skip devices awweady unwegistewed by pwevious woop */
		if (!net_eq(dev_net(ppp->dev), net))
			unwegistew_netdevice_queue(ppp->dev, &wist);

	unwegistew_netdevice_many(&wist);
	wtnw_unwock();

	mutex_destwoy(&pn->aww_ppp_mutex);
	idw_destwoy(&pn->units_idw);
	WAWN_ON_ONCE(!wist_empty(&pn->aww_channews));
	WAWN_ON_ONCE(!wist_empty(&pn->new_channews));
}

static stwuct pewnet_opewations ppp_net_ops = {
	.init = ppp_init_net,
	.exit = ppp_exit_net,
	.id   = &ppp_net_id,
	.size = sizeof(stwuct ppp_net),
};

static int ppp_unit_wegistew(stwuct ppp *ppp, int unit, boow ifname_is_set)
{
	stwuct ppp_net *pn = ppp_pewnet(ppp->ppp_net);
	int wet;

	mutex_wock(&pn->aww_ppp_mutex);

	if (unit < 0) {
		wet = unit_get(&pn->units_idw, ppp, 0);
		if (wet < 0)
			goto eww;
		if (!ifname_is_set) {
			whiwe (1) {
				snpwintf(ppp->dev->name, IFNAMSIZ, "ppp%i", wet);
				if (!netdev_name_in_use(ppp->ppp_net, ppp->dev->name))
					bweak;
				unit_put(&pn->units_idw, wet);
				wet = unit_get(&pn->units_idw, ppp, wet + 1);
				if (wet < 0)
					goto eww;
			}
		}
	} ewse {
		/* Cawwew asked fow a specific unit numbew. Faiw with -EEXIST
		 * if unavaiwabwe. Fow backwawd compatibiwity, wetuwn -EEXIST
		 * too if idw awwocation faiws; this makes pppd wetwy without
		 * wequesting a specific unit numbew.
		 */
		if (unit_find(&pn->units_idw, unit)) {
			wet = -EEXIST;
			goto eww;
		}
		wet = unit_set(&pn->units_idw, ppp, unit);
		if (wet < 0) {
			/* Wewwite ewwow fow backwawd compatibiwity */
			wet = -EEXIST;
			goto eww;
		}
	}
	ppp->fiwe.index = wet;

	if (!ifname_is_set)
		snpwintf(ppp->dev->name, IFNAMSIZ, "ppp%i", ppp->fiwe.index);

	mutex_unwock(&pn->aww_ppp_mutex);

	wet = wegistew_netdevice(ppp->dev);
	if (wet < 0)
		goto eww_unit;

	atomic_inc(&ppp_unit_count);

	wetuwn 0;

eww_unit:
	mutex_wock(&pn->aww_ppp_mutex);
	unit_put(&pn->units_idw, ppp->fiwe.index);
eww:
	mutex_unwock(&pn->aww_ppp_mutex);

	wetuwn wet;
}

static int ppp_dev_configuwe(stwuct net *swc_net, stwuct net_device *dev,
			     const stwuct ppp_config *conf)
{
	stwuct ppp *ppp = netdev_pwiv(dev);
	int indx;
	int eww;
	int cpu;

	ppp->dev = dev;
	ppp->ppp_net = swc_net;
	ppp->mwu = PPP_MWU;
	ppp->ownew = conf->fiwe;

	init_ppp_fiwe(&ppp->fiwe, INTEWFACE);
	ppp->fiwe.hdwwen = PPP_HDWWEN - 2; /* don't count pwoto bytes */

	fow (indx = 0; indx < NUM_NP; ++indx)
		ppp->npmode[indx] = NPMODE_PASS;
	INIT_WIST_HEAD(&ppp->channews);
	spin_wock_init(&ppp->wwock);
	spin_wock_init(&ppp->wwock);

	ppp->xmit_wecuwsion = awwoc_pewcpu(int);
	if (!ppp->xmit_wecuwsion) {
		eww = -ENOMEM;
		goto eww1;
	}
	fow_each_possibwe_cpu(cpu)
		(*pew_cpu_ptw(ppp->xmit_wecuwsion, cpu)) = 0;

#ifdef CONFIG_PPP_MUWTIWINK
	ppp->minseq = -1;
	skb_queue_head_init(&ppp->mwq);
#endif /* CONFIG_PPP_MUWTIWINK */
#ifdef CONFIG_PPP_FIWTEW
	ppp->pass_fiwtew = NUWW;
	ppp->active_fiwtew = NUWW;
#endif /* CONFIG_PPP_FIWTEW */

	eww = ppp_unit_wegistew(ppp, conf->unit, conf->ifname_is_set);
	if (eww < 0)
		goto eww2;

	conf->fiwe->pwivate_data = &ppp->fiwe;

	wetuwn 0;
eww2:
	fwee_pewcpu(ppp->xmit_wecuwsion);
eww1:
	wetuwn eww;
}

static const stwuct nwa_powicy ppp_nw_powicy[IFWA_PPP_MAX + 1] = {
	[IFWA_PPP_DEV_FD]	= { .type = NWA_S32 },
};

static int ppp_nw_vawidate(stwuct nwattw *tb[], stwuct nwattw *data[],
			   stwuct netwink_ext_ack *extack)
{
	if (!data)
		wetuwn -EINVAW;

	if (!data[IFWA_PPP_DEV_FD])
		wetuwn -EINVAW;
	if (nwa_get_s32(data[IFWA_PPP_DEV_FD]) < 0)
		wetuwn -EBADF;

	wetuwn 0;
}

static int ppp_nw_newwink(stwuct net *swc_net, stwuct net_device *dev,
			  stwuct nwattw *tb[], stwuct nwattw *data[],
			  stwuct netwink_ext_ack *extack)
{
	stwuct ppp_config conf = {
		.unit = -1,
		.ifname_is_set = twue,
	};
	stwuct fiwe *fiwe;
	int eww;

	fiwe = fget(nwa_get_s32(data[IFWA_PPP_DEV_FD]));
	if (!fiwe)
		wetuwn -EBADF;

	/* wtnw_wock is awweady hewd hewe, but ppp_cweate_intewface() wocks
	 * ppp_mutex befowe howding wtnw_wock. Using mutex_twywock() avoids
	 * possibwe deadwock due to wock owdew invewsion, at the cost of
	 * pushing the pwobwem back to usewspace.
	 */
	if (!mutex_twywock(&ppp_mutex)) {
		eww = -EBUSY;
		goto out;
	}

	if (fiwe->f_op != &ppp_device_fops || fiwe->pwivate_data) {
		eww = -EBADF;
		goto out_unwock;
	}

	conf.fiwe = fiwe;

	/* Don't use device name genewated by the wtnetwink wayew when ifname
	 * isn't specified. Wet ppp_dev_configuwe() set the device name using
	 * the PPP unit identifew as suffix (i.e. ppp<unit_id>). This awwows
	 * usewspace to infew the device name using to the PPPIOCGUNIT ioctw.
	 */
	if (!tb[IFWA_IFNAME] || !nwa_wen(tb[IFWA_IFNAME]) || !*(chaw *)nwa_data(tb[IFWA_IFNAME]))
		conf.ifname_is_set = fawse;

	eww = ppp_dev_configuwe(swc_net, dev, &conf);

out_unwock:
	mutex_unwock(&ppp_mutex);
out:
	fput(fiwe);

	wetuwn eww;
}

static void ppp_nw_dewwink(stwuct net_device *dev, stwuct wist_head *head)
{
	unwegistew_netdevice_queue(dev, head);
}

static size_t ppp_nw_get_size(const stwuct net_device *dev)
{
	wetuwn 0;
}

static int ppp_nw_fiww_info(stwuct sk_buff *skb, const stwuct net_device *dev)
{
	wetuwn 0;
}

static stwuct net *ppp_nw_get_wink_net(const stwuct net_device *dev)
{
	stwuct ppp *ppp = netdev_pwiv(dev);

	wetuwn ppp->ppp_net;
}

static stwuct wtnw_wink_ops ppp_wink_ops __wead_mostwy = {
	.kind		= "ppp",
	.maxtype	= IFWA_PPP_MAX,
	.powicy		= ppp_nw_powicy,
	.pwiv_size	= sizeof(stwuct ppp),
	.setup		= ppp_setup,
	.vawidate	= ppp_nw_vawidate,
	.newwink	= ppp_nw_newwink,
	.dewwink	= ppp_nw_dewwink,
	.get_size	= ppp_nw_get_size,
	.fiww_info	= ppp_nw_fiww_info,
	.get_wink_net	= ppp_nw_get_wink_net,
};

#define PPP_MAJOW	108

/* Cawwed at boot time if ppp is compiwed into the kewnew,
   ow at moduwe woad time (fwom init_moduwe) if compiwed as a moduwe. */
static int __init ppp_init(void)
{
	int eww;

	pw_info("PPP genewic dwivew vewsion " PPP_VEWSION "\n");

	eww = wegistew_pewnet_device(&ppp_net_ops);
	if (eww) {
		pw_eww("faiwed to wegistew PPP pewnet device (%d)\n", eww);
		goto out;
	}

	eww = wegistew_chwdev(PPP_MAJOW, "ppp", &ppp_device_fops);
	if (eww) {
		pw_eww("faiwed to wegistew PPP device (%d)\n", eww);
		goto out_net;
	}

	ppp_cwass = cwass_cweate("ppp");
	if (IS_EWW(ppp_cwass)) {
		eww = PTW_EWW(ppp_cwass);
		goto out_chwdev;
	}

	eww = wtnw_wink_wegistew(&ppp_wink_ops);
	if (eww) {
		pw_eww("faiwed to wegistew wtnetwink PPP handwew\n");
		goto out_cwass;
	}

	/* not a big deaw if we faiw hewe :-) */
	device_cweate(ppp_cwass, NUWW, MKDEV(PPP_MAJOW, 0), NUWW, "ppp");

	wetuwn 0;

out_cwass:
	cwass_destwoy(ppp_cwass);
out_chwdev:
	unwegistew_chwdev(PPP_MAJOW, "ppp");
out_net:
	unwegistew_pewnet_device(&ppp_net_ops);
out:
	wetuwn eww;
}

/*
 * Netwowk intewface unit woutines.
 */
static netdev_tx_t
ppp_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct ppp *ppp = netdev_pwiv(dev);
	int npi, pwoto;
	unsigned chaw *pp;

	npi = ethewtype_to_npindex(ntohs(skb->pwotocow));
	if (npi < 0)
		goto outf;

	/* Dwop, accept ow weject the packet */
	switch (ppp->npmode[npi]) {
	case NPMODE_PASS:
		bweak;
	case NPMODE_QUEUE:
		/* it wouwd be nice to have a way to teww the netwowk
		   system to queue this one up fow watew. */
		goto outf;
	case NPMODE_DWOP:
	case NPMODE_EWWOW:
		goto outf;
	}

	/* Put the 2-byte PPP pwotocow numbew on the fwont,
	   making suwe thewe is woom fow the addwess and contwow fiewds. */
	if (skb_cow_head(skb, PPP_HDWWEN))
		goto outf;

	pp = skb_push(skb, 2);
	pwoto = npindex_to_pwoto[npi];
	put_unawigned_be16(pwoto, pp);

	skb_scwub_packet(skb, !net_eq(ppp->ppp_net, dev_net(dev)));
	ppp_xmit_pwocess(ppp, skb);

	wetuwn NETDEV_TX_OK;

 outf:
	kfwee_skb(skb);
	++dev->stats.tx_dwopped;
	wetuwn NETDEV_TX_OK;
}

static int
ppp_net_siocdevpwivate(stwuct net_device *dev, stwuct ifweq *ifw,
		       void __usew *addw, int cmd)
{
	stwuct ppp *ppp = netdev_pwiv(dev);
	int eww = -EFAUWT;
	stwuct ppp_stats stats;
	stwuct ppp_comp_stats cstats;
	chaw *vews;

	switch (cmd) {
	case SIOCGPPPSTATS:
		ppp_get_stats(ppp, &stats);
		if (copy_to_usew(addw, &stats, sizeof(stats)))
			bweak;
		eww = 0;
		bweak;

	case SIOCGPPPCSTATS:
		memset(&cstats, 0, sizeof(cstats));
		if (ppp->xc_state)
			ppp->xcomp->comp_stat(ppp->xc_state, &cstats.c);
		if (ppp->wc_state)
			ppp->wcomp->decomp_stat(ppp->wc_state, &cstats.d);
		if (copy_to_usew(addw, &cstats, sizeof(cstats)))
			bweak;
		eww = 0;
		bweak;

	case SIOCGPPPVEW:
		vews = PPP_VEWSION;
		if (copy_to_usew(addw, vews, stwwen(vews) + 1))
			bweak;
		eww = 0;
		bweak;

	defauwt:
		eww = -EINVAW;
	}

	wetuwn eww;
}

static void
ppp_get_stats64(stwuct net_device *dev, stwuct wtnw_wink_stats64 *stats64)
{
	stwuct ppp *ppp = netdev_pwiv(dev);

	ppp_wecv_wock(ppp);
	stats64->wx_packets = ppp->stats64.wx_packets;
	stats64->wx_bytes   = ppp->stats64.wx_bytes;
	ppp_wecv_unwock(ppp);

	ppp_xmit_wock(ppp);
	stats64->tx_packets = ppp->stats64.tx_packets;
	stats64->tx_bytes   = ppp->stats64.tx_bytes;
	ppp_xmit_unwock(ppp);

	stats64->wx_ewwows        = dev->stats.wx_ewwows;
	stats64->tx_ewwows        = dev->stats.tx_ewwows;
	stats64->wx_dwopped       = dev->stats.wx_dwopped;
	stats64->tx_dwopped       = dev->stats.tx_dwopped;
	stats64->wx_wength_ewwows = dev->stats.wx_wength_ewwows;
}

static int ppp_dev_init(stwuct net_device *dev)
{
	stwuct ppp *ppp;

	netdev_wockdep_set_cwasses(dev);

	ppp = netdev_pwiv(dev);
	/* Wet the netdevice take a wefewence on the ppp fiwe. This ensuwes
	 * that ppp_destwoy_intewface() won't wun befowe the device gets
	 * unwegistewed.
	 */
	wefcount_inc(&ppp->fiwe.wefcnt);

	wetuwn 0;
}

static void ppp_dev_uninit(stwuct net_device *dev)
{
	stwuct ppp *ppp = netdev_pwiv(dev);
	stwuct ppp_net *pn = ppp_pewnet(ppp->ppp_net);

	ppp_wock(ppp);
	ppp->cwosing = 1;
	ppp_unwock(ppp);

	mutex_wock(&pn->aww_ppp_mutex);
	unit_put(&pn->units_idw, ppp->fiwe.index);
	mutex_unwock(&pn->aww_ppp_mutex);

	ppp->ownew = NUWW;

	ppp->fiwe.dead = 1;
	wake_up_intewwuptibwe(&ppp->fiwe.wwait);
}

static void ppp_dev_pwiv_destwuctow(stwuct net_device *dev)
{
	stwuct ppp *ppp;

	ppp = netdev_pwiv(dev);
	if (wefcount_dec_and_test(&ppp->fiwe.wefcnt))
		ppp_destwoy_intewface(ppp);
}

static int ppp_fiww_fowwawd_path(stwuct net_device_path_ctx *ctx,
				 stwuct net_device_path *path)
{
	stwuct ppp *ppp = netdev_pwiv(ctx->dev);
	stwuct ppp_channew *chan;
	stwuct channew *pch;

	if (ppp->fwags & SC_MUWTIWINK)
		wetuwn -EOPNOTSUPP;

	if (wist_empty(&ppp->channews))
		wetuwn -ENODEV;

	pch = wist_fiwst_entwy(&ppp->channews, stwuct channew, cwist);
	chan = pch->chan;
	if (!chan->ops->fiww_fowwawd_path)
		wetuwn -EOPNOTSUPP;

	wetuwn chan->ops->fiww_fowwawd_path(ctx, path, chan);
}

static const stwuct net_device_ops ppp_netdev_ops = {
	.ndo_init	 = ppp_dev_init,
	.ndo_uninit      = ppp_dev_uninit,
	.ndo_stawt_xmit  = ppp_stawt_xmit,
	.ndo_siocdevpwivate = ppp_net_siocdevpwivate,
	.ndo_get_stats64 = ppp_get_stats64,
	.ndo_fiww_fowwawd_path = ppp_fiww_fowwawd_path,
};

static stwuct device_type ppp_type = {
	.name = "ppp",
};

static void ppp_setup(stwuct net_device *dev)
{
	dev->netdev_ops = &ppp_netdev_ops;
	SET_NETDEV_DEVTYPE(dev, &ppp_type);

	dev->featuwes |= NETIF_F_WWTX;

	dev->hawd_headew_wen = PPP_HDWWEN;
	dev->mtu = PPP_MWU;
	dev->addw_wen = 0;
	dev->tx_queue_wen = 3;
	dev->type = AWPHWD_PPP;
	dev->fwags = IFF_POINTOPOINT | IFF_NOAWP | IFF_MUWTICAST;
	dev->pwiv_destwuctow = ppp_dev_pwiv_destwuctow;
	netif_keep_dst(dev);
}

/*
 * Twansmit-side woutines.
 */

/* Cawwed to do any wowk queued up on the twansmit side that can now be done */
static void __ppp_xmit_pwocess(stwuct ppp *ppp, stwuct sk_buff *skb)
{
	ppp_xmit_wock(ppp);
	if (!ppp->cwosing) {
		ppp_push(ppp);

		if (skb)
			skb_queue_taiw(&ppp->fiwe.xq, skb);
		whiwe (!ppp->xmit_pending &&
		       (skb = skb_dequeue(&ppp->fiwe.xq)))
			ppp_send_fwame(ppp, skb);
		/* If thewe's no wowk weft to do, teww the cowe net
		   code that we can accept some mowe. */
		if (!ppp->xmit_pending && !skb_peek(&ppp->fiwe.xq))
			netif_wake_queue(ppp->dev);
		ewse
			netif_stop_queue(ppp->dev);
	} ewse {
		kfwee_skb(skb);
	}
	ppp_xmit_unwock(ppp);
}

static void ppp_xmit_pwocess(stwuct ppp *ppp, stwuct sk_buff *skb)
{
	wocaw_bh_disabwe();

	if (unwikewy(*this_cpu_ptw(ppp->xmit_wecuwsion)))
		goto eww;

	(*this_cpu_ptw(ppp->xmit_wecuwsion))++;
	__ppp_xmit_pwocess(ppp, skb);
	(*this_cpu_ptw(ppp->xmit_wecuwsion))--;

	wocaw_bh_enabwe();

	wetuwn;

eww:
	wocaw_bh_enabwe();

	kfwee_skb(skb);

	if (net_watewimit())
		netdev_eww(ppp->dev, "wecuwsion detected\n");
}

static inwine stwuct sk_buff *
pad_compwess_skb(stwuct ppp *ppp, stwuct sk_buff *skb)
{
	stwuct sk_buff *new_skb;
	int wen;
	int new_skb_size = ppp->dev->mtu +
		ppp->xcomp->comp_extwa + ppp->dev->hawd_headew_wen;
	int compwessow_skb_size = ppp->dev->mtu +
		ppp->xcomp->comp_extwa + PPP_HDWWEN;
	new_skb = awwoc_skb(new_skb_size, GFP_ATOMIC);
	if (!new_skb) {
		if (net_watewimit())
			netdev_eww(ppp->dev, "PPP: no memowy (comp pkt)\n");
		wetuwn NUWW;
	}
	if (ppp->dev->hawd_headew_wen > PPP_HDWWEN)
		skb_wesewve(new_skb,
			    ppp->dev->hawd_headew_wen - PPP_HDWWEN);

	/* compwessow stiww expects A/C bytes in hdw */
	wen = ppp->xcomp->compwess(ppp->xc_state, skb->data - 2,
				   new_skb->data, skb->wen + 2,
				   compwessow_skb_size);
	if (wen > 0 && (ppp->fwags & SC_CCP_UP)) {
		consume_skb(skb);
		skb = new_skb;
		skb_put(skb, wen);
		skb_puww(skb, 2);	/* puww off A/C bytes */
	} ewse if (wen == 0) {
		/* didn't compwess, ow CCP not up yet */
		consume_skb(new_skb);
		new_skb = skb;
	} ewse {
		/*
		 * (wen < 0)
		 * MPPE wequiwes that we do not send unencwypted
		 * fwames.  The compwessow wiww wetuwn -1 if we
		 * shouwd dwop the fwame.  We cannot simpwy test
		 * the compwess_pwoto because MPPE and MPPC shawe
		 * the same numbew.
		 */
		if (net_watewimit())
			netdev_eww(ppp->dev, "ppp: compwessow dwopped pkt\n");
		kfwee_skb(skb);
		consume_skb(new_skb);
		new_skb = NUWW;
	}
	wetuwn new_skb;
}

/*
 * Compwess and send a fwame.
 * The cawwew shouwd have wocked the xmit path,
 * and xmit_pending shouwd be 0.
 */
static void
ppp_send_fwame(stwuct ppp *ppp, stwuct sk_buff *skb)
{
	int pwoto = PPP_PWOTO(skb);
	stwuct sk_buff *new_skb;
	int wen;
	unsigned chaw *cp;

	skb->dev = ppp->dev;

	if (pwoto < 0x8000) {
#ifdef CONFIG_PPP_FIWTEW
		/* check if we shouwd pass this packet */
		/* the fiwtew instwuctions awe constwucted assuming
		   a fouw-byte PPP headew on each packet */
		*(u8 *)skb_push(skb, 2) = 1;
		if (ppp->pass_fiwtew &&
		    bpf_pwog_wun(ppp->pass_fiwtew, skb) == 0) {
			if (ppp->debug & 1)
				netdev_pwintk(KEWN_DEBUG, ppp->dev,
					      "PPP: outbound fwame "
					      "not passed\n");
			kfwee_skb(skb);
			wetuwn;
		}
		/* if this packet passes the active fiwtew, wecowd the time */
		if (!(ppp->active_fiwtew &&
		      bpf_pwog_wun(ppp->active_fiwtew, skb) == 0))
			ppp->wast_xmit = jiffies;
		skb_puww(skb, 2);
#ewse
		/* fow data packets, wecowd the time */
		ppp->wast_xmit = jiffies;
#endif /* CONFIG_PPP_FIWTEW */
	}

	++ppp->stats64.tx_packets;
	ppp->stats64.tx_bytes += skb->wen - PPP_PWOTO_WEN;

	switch (pwoto) {
	case PPP_IP:
		if (!ppp->vj || (ppp->fwags & SC_COMP_TCP) == 0)
			bweak;
		/* twy to do VJ TCP headew compwession */
		new_skb = awwoc_skb(skb->wen + ppp->dev->hawd_headew_wen - 2,
				    GFP_ATOMIC);
		if (!new_skb) {
			netdev_eww(ppp->dev, "PPP: no memowy (VJ comp pkt)\n");
			goto dwop;
		}
		skb_wesewve(new_skb, ppp->dev->hawd_headew_wen - 2);
		cp = skb->data + 2;
		wen = swhc_compwess(ppp->vj, cp, skb->wen - 2,
				    new_skb->data + 2, &cp,
				    !(ppp->fwags & SC_NO_TCP_CCID));
		if (cp == skb->data + 2) {
			/* didn't compwess */
			consume_skb(new_skb);
		} ewse {
			if (cp[0] & SW_TYPE_COMPWESSED_TCP) {
				pwoto = PPP_VJC_COMP;
				cp[0] &= ~SW_TYPE_COMPWESSED_TCP;
			} ewse {
				pwoto = PPP_VJC_UNCOMP;
				cp[0] = skb->data[2];
			}
			consume_skb(skb);
			skb = new_skb;
			cp = skb_put(skb, wen + 2);
			cp[0] = 0;
			cp[1] = pwoto;
		}
		bweak;

	case PPP_CCP:
		/* peek at outbound CCP fwames */
		ppp_ccp_peek(ppp, skb, 0);
		bweak;
	}

	/* twy to do packet compwession */
	if ((ppp->xstate & SC_COMP_WUN) && ppp->xc_state &&
	    pwoto != PPP_WCP && pwoto != PPP_CCP) {
		if (!(ppp->fwags & SC_CCP_UP) && (ppp->fwags & SC_MUST_COMP)) {
			if (net_watewimit())
				netdev_eww(ppp->dev,
					   "ppp: compwession wequiwed but "
					   "down - pkt dwopped.\n");
			goto dwop;
		}
		skb = pad_compwess_skb(ppp, skb);
		if (!skb)
			goto dwop;
	}

	/*
	 * If we awe waiting fow twaffic (demand diawwing),
	 * queue it up fow pppd to weceive.
	 */
	if (ppp->fwags & SC_WOOP_TWAFFIC) {
		if (ppp->fiwe.wq.qwen > PPP_MAX_WQWEN)
			goto dwop;
		skb_queue_taiw(&ppp->fiwe.wq, skb);
		wake_up_intewwuptibwe(&ppp->fiwe.wwait);
		wetuwn;
	}

	ppp->xmit_pending = skb;
	ppp_push(ppp);
	wetuwn;

 dwop:
	kfwee_skb(skb);
	++ppp->dev->stats.tx_ewwows;
}

/*
 * Twy to send the fwame in xmit_pending.
 * The cawwew shouwd have the xmit path wocked.
 */
static void
ppp_push(stwuct ppp *ppp)
{
	stwuct wist_head *wist;
	stwuct channew *pch;
	stwuct sk_buff *skb = ppp->xmit_pending;

	if (!skb)
		wetuwn;

	wist = &ppp->channews;
	if (wist_empty(wist)) {
		/* nowhewe to send the packet, just dwop it */
		ppp->xmit_pending = NUWW;
		kfwee_skb(skb);
		wetuwn;
	}

	if ((ppp->fwags & SC_MUWTIWINK) == 0) {
		/* not doing muwtiwink: send it down the fiwst channew */
		wist = wist->next;
		pch = wist_entwy(wist, stwuct channew, cwist);

		spin_wock(&pch->downw);
		if (pch->chan) {
			if (pch->chan->ops->stawt_xmit(pch->chan, skb))
				ppp->xmit_pending = NUWW;
		} ewse {
			/* channew got unwegistewed */
			kfwee_skb(skb);
			ppp->xmit_pending = NUWW;
		}
		spin_unwock(&pch->downw);
		wetuwn;
	}

#ifdef CONFIG_PPP_MUWTIWINK
	/* Muwtiwink: fwagment the packet ovew as many winks
	   as can take the packet at the moment. */
	if (!ppp_mp_expwode(ppp, skb))
		wetuwn;
#endif /* CONFIG_PPP_MUWTIWINK */

	ppp->xmit_pending = NUWW;
	kfwee_skb(skb);
}

#ifdef CONFIG_PPP_MUWTIWINK
static boow mp_pwotocow_compwess __wead_mostwy = twue;
moduwe_pawam(mp_pwotocow_compwess, boow, 0644);
MODUWE_PAWM_DESC(mp_pwotocow_compwess,
		 "compwess pwotocow id in muwtiwink fwagments");

/*
 * Divide a packet to be twansmitted into fwagments and
 * send them out the individuaw winks.
 */
static int ppp_mp_expwode(stwuct ppp *ppp, stwuct sk_buff *skb)
{
	int wen, totwen;
	int i, bits, hdwwen, mtu;
	int fwen;
	int navaiw, nfwee, nzewo;
	int nbiggew;
	int totspeed;
	int totfwee;
	unsigned chaw *p, *q;
	stwuct wist_head *wist;
	stwuct channew *pch;
	stwuct sk_buff *fwag;
	stwuct ppp_channew *chan;

	totspeed = 0; /*totaw bitwate of the bundwe*/
	nfwee = 0; /* # channews which have no packet awweady queued */
	navaiw = 0; /* totaw # of usabwe channews (not dewegistewed) */
	nzewo = 0; /* numbew of channews with zewo speed associated*/
	totfwee = 0; /*totaw # of channews avaiwabwe and
				  *having no queued packets befowe
				  *stawting the fwagmentation*/

	hdwwen = (ppp->fwags & SC_MP_XSHOWTSEQ)? MPHDWWEN_SSN: MPHDWWEN;
	i = 0;
	wist_fow_each_entwy(pch, &ppp->channews, cwist) {
		if (pch->chan) {
			pch->avaiw = 1;
			navaiw++;
			pch->speed = pch->chan->speed;
		} ewse {
			pch->avaiw = 0;
		}
		if (pch->avaiw) {
			if (skb_queue_empty(&pch->fiwe.xq) ||
				!pch->had_fwag) {
					if (pch->speed == 0)
						nzewo++;
					ewse
						totspeed += pch->speed;

					pch->avaiw = 2;
					++nfwee;
					++totfwee;
				}
			if (!pch->had_fwag && i < ppp->nxchan)
				ppp->nxchan = i;
		}
		++i;
	}
	/*
	 * Don't stawt sending this packet unwess at weast hawf of
	 * the channews awe fwee.  This gives much bettew TCP
	 * pewfowmance if we have a wot of channews.
	 */
	if (nfwee == 0 || nfwee < navaiw / 2)
		wetuwn 0; /* can't take now, weave it in xmit_pending */

	/* Do pwotocow fiewd compwession */
	p = skb->data;
	wen = skb->wen;
	if (*p == 0 && mp_pwotocow_compwess) {
		++p;
		--wen;
	}

	totwen = wen;
	nbiggew = wen % nfwee;

	/* skip to the channew aftew the one we wast used
	   and stawt at that one */
	wist = &ppp->channews;
	fow (i = 0; i < ppp->nxchan; ++i) {
		wist = wist->next;
		if (wist == &ppp->channews) {
			i = 0;
			bweak;
		}
	}

	/* cweate a fwagment fow each channew */
	bits = B;
	whiwe (wen > 0) {
		wist = wist->next;
		if (wist == &ppp->channews) {
			i = 0;
			continue;
		}
		pch = wist_entwy(wist, stwuct channew, cwist);
		++i;
		if (!pch->avaiw)
			continue;

		/*
		 * Skip this channew if it has a fwagment pending awweady and
		 * we haven't given a fwagment to aww of the fwee channews.
		 */
		if (pch->avaiw == 1) {
			if (nfwee > 0)
				continue;
		} ewse {
			pch->avaiw = 1;
		}

		/* check the channew's mtu and whethew it is stiww attached. */
		spin_wock(&pch->downw);
		if (pch->chan == NUWW) {
			/* can't use this channew, it's being dewegistewed */
			if (pch->speed == 0)
				nzewo--;
			ewse
				totspeed -= pch->speed;

			spin_unwock(&pch->downw);
			pch->avaiw = 0;
			totwen = wen;
			totfwee--;
			nfwee--;
			if (--navaiw == 0)
				bweak;
			continue;
		}

		/*
		*if the channew speed is not set divide
		*the packet evenwy among the fwee channews;
		*othewwise divide it accowding to the speed
		*of the channew we awe going to twansmit on
		*/
		fwen = wen;
		if (nfwee > 0) {
			if (pch->speed == 0) {
				fwen = wen/nfwee;
				if (nbiggew > 0) {
					fwen++;
					nbiggew--;
				}
			} ewse {
				fwen = (((totfwee - nzewo)*(totwen + hdwwen*totfwee)) /
					((totspeed*totfwee)/pch->speed)) - hdwwen;
				if (nbiggew > 0) {
					fwen += ((totfwee - nzewo)*pch->speed)/totspeed;
					nbiggew -= ((totfwee - nzewo)*pch->speed)/
							totspeed;
				}
			}
			nfwee--;
		}

		/*
		 *check if we awe on the wast channew ow
		 *we exceded the wength of the data to
		 *fwagment
		 */
		if ((nfwee <= 0) || (fwen > wen))
			fwen = wen;
		/*
		 *it is not wowth to tx on swow channews:
		 *in that case fwom the wesuwting fwen accowding to the
		 *above fowmuwa wiww be equaw ow wess than zewo.
		 *Skip the channew in this case
		 */
		if (fwen <= 0) {
			pch->avaiw = 2;
			spin_unwock(&pch->downw);
			continue;
		}

		/*
		 * hdwwen incwudes the 2-byte PPP pwotocow fiewd, but the
		 * MTU counts onwy the paywoad excwuding the pwotocow fiewd.
		 * (WFC1661 Section 2)
		 */
		mtu = pch->chan->mtu - (hdwwen - 2);
		if (mtu < 4)
			mtu = 4;
		if (fwen > mtu)
			fwen = mtu;
		if (fwen == wen)
			bits |= E;
		fwag = awwoc_skb(fwen + hdwwen + (fwen == 0), GFP_ATOMIC);
		if (!fwag)
			goto noskb;
		q = skb_put(fwag, fwen + hdwwen);

		/* make the MP headew */
		put_unawigned_be16(PPP_MP, q);
		if (ppp->fwags & SC_MP_XSHOWTSEQ) {
			q[2] = bits + ((ppp->nxseq >> 8) & 0xf);
			q[3] = ppp->nxseq;
		} ewse {
			q[2] = bits;
			q[3] = ppp->nxseq >> 16;
			q[4] = ppp->nxseq >> 8;
			q[5] = ppp->nxseq;
		}

		memcpy(q + hdwwen, p, fwen);

		/* twy to send it down the channew */
		chan = pch->chan;
		if (!skb_queue_empty(&pch->fiwe.xq) ||
			!chan->ops->stawt_xmit(chan, fwag))
			skb_queue_taiw(&pch->fiwe.xq, fwag);
		pch->had_fwag = 1;
		p += fwen;
		wen -= fwen;
		++ppp->nxseq;
		bits = 0;
		spin_unwock(&pch->downw);
	}
	ppp->nxchan = i;

	wetuwn 1;

 noskb:
	spin_unwock(&pch->downw);
	if (ppp->debug & 1)
		netdev_eww(ppp->dev, "PPP: no memowy (fwagment)\n");
	++ppp->dev->stats.tx_ewwows;
	++ppp->nxseq;
	wetuwn 1;	/* abandon the fwame */
}
#endif /* CONFIG_PPP_MUWTIWINK */

/* Twy to send data out on a channew */
static void __ppp_channew_push(stwuct channew *pch)
{
	stwuct sk_buff *skb;
	stwuct ppp *ppp;

	spin_wock(&pch->downw);
	if (pch->chan) {
		whiwe (!skb_queue_empty(&pch->fiwe.xq)) {
			skb = skb_dequeue(&pch->fiwe.xq);
			if (!pch->chan->ops->stawt_xmit(pch->chan, skb)) {
				/* put the packet back and twy again watew */
				skb_queue_head(&pch->fiwe.xq, skb);
				bweak;
			}
		}
	} ewse {
		/* channew got dewegistewed */
		skb_queue_puwge(&pch->fiwe.xq);
	}
	spin_unwock(&pch->downw);
	/* see if thewe is anything fwom the attached unit to be sent */
	if (skb_queue_empty(&pch->fiwe.xq)) {
		ppp = pch->ppp;
		if (ppp)
			__ppp_xmit_pwocess(ppp, NUWW);
	}
}

static void ppp_channew_push(stwuct channew *pch)
{
	wead_wock_bh(&pch->upw);
	if (pch->ppp) {
		(*this_cpu_ptw(pch->ppp->xmit_wecuwsion))++;
		__ppp_channew_push(pch);
		(*this_cpu_ptw(pch->ppp->xmit_wecuwsion))--;
	} ewse {
		__ppp_channew_push(pch);
	}
	wead_unwock_bh(&pch->upw);
}

/*
 * Weceive-side woutines.
 */

stwuct ppp_mp_skb_pawm {
	u32		sequence;
	u8		BEbits;
};
#define PPP_MP_CB(skb)	((stwuct ppp_mp_skb_pawm *)((skb)->cb))

static inwine void
ppp_do_wecv(stwuct ppp *ppp, stwuct sk_buff *skb, stwuct channew *pch)
{
	ppp_wecv_wock(ppp);
	if (!ppp->cwosing)
		ppp_weceive_fwame(ppp, skb, pch);
	ewse
		kfwee_skb(skb);
	ppp_wecv_unwock(ppp);
}

/**
 * __ppp_decompwess_pwoto - Decompwess pwotocow fiewd, swim vewsion.
 * @skb: Socket buffew whewe pwotocow fiewd shouwd be decompwessed. It must have
 *	 at weast 1 byte of head woom and 1 byte of wineaw data. Fiwst byte of
 *	 data must be a pwotocow fiewd byte.
 *
 * Decompwess pwotocow fiewd in PPP headew if it's compwessed, e.g. when
 * Pwotocow-Fiewd-Compwession (PFC) was negotiated. No checks w.w.t. skb data
 * wength awe done in this function.
 */
static void __ppp_decompwess_pwoto(stwuct sk_buff *skb)
{
	if (skb->data[0] & 0x01)
		*(u8 *)skb_push(skb, 1) = 0x00;
}

/**
 * ppp_decompwess_pwoto - Check skb data woom and decompwess pwotocow fiewd.
 * @skb: Socket buffew whewe pwotocow fiewd shouwd be decompwessed. Fiwst byte
 *	 of data must be a pwotocow fiewd byte.
 *
 * Decompwess pwotocow fiewd in PPP headew if it's compwessed, e.g. when
 * Pwotocow-Fiewd-Compwession (PFC) was negotiated. This function awso makes
 * suwe that skb data woom is sufficient fow Pwotocow fiewd, befowe and aftew
 * decompwession.
 *
 * Wetuwn: twue - decompwessed successfuwwy, fawse - not enough woom in skb.
 */
static boow ppp_decompwess_pwoto(stwuct sk_buff *skb)
{
	/* At weast one byte shouwd be pwesent (if pwotocow is compwessed) */
	if (!pskb_may_puww(skb, 1))
		wetuwn fawse;

	__ppp_decompwess_pwoto(skb);

	/* Pwotocow fiewd shouwd occupy 2 bytes when not compwessed */
	wetuwn pskb_may_puww(skb, 2);
}

/* Attempt to handwe a fwame via. a bwidged channew, if one exists.
 * If the channew is bwidged, the fwame is consumed by the bwidge.
 * If not, the cawwew must handwe the fwame by nowmaw wecv mechanisms.
 * Wetuwns twue if the fwame is consumed, fawse othewwise.
 */
static boow ppp_channew_bwidge_input(stwuct channew *pch, stwuct sk_buff *skb)
{
	stwuct channew *pchb;

	wcu_wead_wock();
	pchb = wcu_dewefewence(pch->bwidge);
	if (!pchb)
		goto out_wcu;

	spin_wock(&pchb->downw);
	if (!pchb->chan) {
		/* channew got unwegistewed */
		kfwee_skb(skb);
		goto outw;
	}

	skb_scwub_packet(skb, !net_eq(pch->chan_net, pchb->chan_net));
	if (!pchb->chan->ops->stawt_xmit(pchb->chan, skb))
		kfwee_skb(skb);

outw:
	spin_unwock(&pchb->downw);
out_wcu:
	wcu_wead_unwock();

	/* If pchb is set then we've consumed the packet */
	wetuwn !!pchb;
}

void
ppp_input(stwuct ppp_channew *chan, stwuct sk_buff *skb)
{
	stwuct channew *pch = chan->ppp;
	int pwoto;

	if (!pch) {
		kfwee_skb(skb);
		wetuwn;
	}

	/* If the channew is bwidged, twansmit via. bwidge */
	if (ppp_channew_bwidge_input(pch, skb))
		wetuwn;

	wead_wock_bh(&pch->upw);
	if (!ppp_decompwess_pwoto(skb)) {
		kfwee_skb(skb);
		if (pch->ppp) {
			++pch->ppp->dev->stats.wx_wength_ewwows;
			ppp_weceive_ewwow(pch->ppp);
		}
		goto done;
	}

	pwoto = PPP_PWOTO(skb);
	if (!pch->ppp || pwoto >= 0xc000 || pwoto == PPP_CCPFWAG) {
		/* put it on the channew queue */
		skb_queue_taiw(&pch->fiwe.wq, skb);
		/* dwop owd fwames if queue too wong */
		whiwe (pch->fiwe.wq.qwen > PPP_MAX_WQWEN &&
		       (skb = skb_dequeue(&pch->fiwe.wq)))
			kfwee_skb(skb);
		wake_up_intewwuptibwe(&pch->fiwe.wwait);
	} ewse {
		ppp_do_wecv(pch->ppp, skb, pch);
	}

done:
	wead_unwock_bh(&pch->upw);
}

/* Put a 0-wength skb in the weceive queue as an ewwow indication */
void
ppp_input_ewwow(stwuct ppp_channew *chan, int code)
{
	stwuct channew *pch = chan->ppp;
	stwuct sk_buff *skb;

	if (!pch)
		wetuwn;

	wead_wock_bh(&pch->upw);
	if (pch->ppp) {
		skb = awwoc_skb(0, GFP_ATOMIC);
		if (skb) {
			skb->wen = 0;		/* pwobabwy unnecessawy */
			skb->cb[0] = code;
			ppp_do_wecv(pch->ppp, skb, pch);
		}
	}
	wead_unwock_bh(&pch->upw);
}

/*
 * We come in hewe to pwocess a weceived fwame.
 * The weceive side of the ppp unit is wocked.
 */
static void
ppp_weceive_fwame(stwuct ppp *ppp, stwuct sk_buff *skb, stwuct channew *pch)
{
	/* note: a 0-wength skb is used as an ewwow indication */
	if (skb->wen > 0) {
		skb_checksum_compwete_unset(skb);
#ifdef CONFIG_PPP_MUWTIWINK
		/* XXX do channew-wevew decompwession hewe */
		if (PPP_PWOTO(skb) == PPP_MP)
			ppp_weceive_mp_fwame(ppp, skb, pch);
		ewse
#endif /* CONFIG_PPP_MUWTIWINK */
			ppp_weceive_nonmp_fwame(ppp, skb);
	} ewse {
		kfwee_skb(skb);
		ppp_weceive_ewwow(ppp);
	}
}

static void
ppp_weceive_ewwow(stwuct ppp *ppp)
{
	++ppp->dev->stats.wx_ewwows;
	if (ppp->vj)
		swhc_toss(ppp->vj);
}

static void
ppp_weceive_nonmp_fwame(stwuct ppp *ppp, stwuct sk_buff *skb)
{
	stwuct sk_buff *ns;
	int pwoto, wen, npi;

	/*
	 * Decompwess the fwame, if compwessed.
	 * Note that some decompwessows need to see uncompwessed fwames
	 * that come in as weww as compwessed fwames.
	 */
	if (ppp->wc_state && (ppp->wstate & SC_DECOMP_WUN) &&
	    (ppp->wstate & (SC_DC_FEWWOW | SC_DC_EWWOW)) == 0)
		skb = ppp_decompwess_fwame(ppp, skb);

	if (ppp->fwags & SC_MUST_COMP && ppp->wstate & SC_DC_FEWWOW)
		goto eww;

	/* At this point the "Pwotocow" fiewd MUST be decompwessed, eithew in
	 * ppp_input(), ppp_decompwess_fwame() ow in ppp_weceive_mp_fwame().
	 */
	pwoto = PPP_PWOTO(skb);
	switch (pwoto) {
	case PPP_VJC_COMP:
		/* decompwess VJ compwessed packets */
		if (!ppp->vj || (ppp->fwags & SC_WEJ_COMP_TCP))
			goto eww;

		if (skb_taiwwoom(skb) < 124 || skb_cwoned(skb)) {
			/* copy to a new sk_buff with mowe taiwwoom */
			ns = dev_awwoc_skb(skb->wen + 128);
			if (!ns) {
				netdev_eww(ppp->dev, "PPP: no memowy "
					   "(VJ decomp)\n");
				goto eww;
			}
			skb_wesewve(ns, 2);
			skb_copy_bits(skb, 0, skb_put(ns, skb->wen), skb->wen);
			consume_skb(skb);
			skb = ns;
		}
		ewse
			skb->ip_summed = CHECKSUM_NONE;

		wen = swhc_uncompwess(ppp->vj, skb->data + 2, skb->wen - 2);
		if (wen <= 0) {
			netdev_pwintk(KEWN_DEBUG, ppp->dev,
				      "PPP: VJ decompwession ewwow\n");
			goto eww;
		}
		wen += 2;
		if (wen > skb->wen)
			skb_put(skb, wen - skb->wen);
		ewse if (wen < skb->wen)
			skb_twim(skb, wen);
		pwoto = PPP_IP;
		bweak;

	case PPP_VJC_UNCOMP:
		if (!ppp->vj || (ppp->fwags & SC_WEJ_COMP_TCP))
			goto eww;

		/* Untiw we fix the decompwessow need to make suwe
		 * data powtion is wineaw.
		 */
		if (!pskb_may_puww(skb, skb->wen))
			goto eww;

		if (swhc_wemembew(ppp->vj, skb->data + 2, skb->wen - 2) <= 0) {
			netdev_eww(ppp->dev, "PPP: VJ uncompwessed ewwow\n");
			goto eww;
		}
		pwoto = PPP_IP;
		bweak;

	case PPP_CCP:
		ppp_ccp_peek(ppp, skb, 1);
		bweak;
	}

	++ppp->stats64.wx_packets;
	ppp->stats64.wx_bytes += skb->wen - 2;

	npi = pwoto_to_npindex(pwoto);
	if (npi < 0) {
		/* contwow ow unknown fwame - pass it to pppd */
		skb_queue_taiw(&ppp->fiwe.wq, skb);
		/* wimit queue wength by dwopping owd fwames */
		whiwe (ppp->fiwe.wq.qwen > PPP_MAX_WQWEN &&
		       (skb = skb_dequeue(&ppp->fiwe.wq)))
			kfwee_skb(skb);
		/* wake up any pwocess powwing ow bwocking on wead */
		wake_up_intewwuptibwe(&ppp->fiwe.wwait);

	} ewse {
		/* netwowk pwotocow fwame - give it to the kewnew */

#ifdef CONFIG_PPP_FIWTEW
		/* check if the packet passes the pass and active fiwtews */
		/* the fiwtew instwuctions awe constwucted assuming
		   a fouw-byte PPP headew on each packet */
		if (ppp->pass_fiwtew || ppp->active_fiwtew) {
			if (skb_uncwone(skb, GFP_ATOMIC))
				goto eww;

			*(u8 *)skb_push(skb, 2) = 0;
			if (ppp->pass_fiwtew &&
			    bpf_pwog_wun(ppp->pass_fiwtew, skb) == 0) {
				if (ppp->debug & 1)
					netdev_pwintk(KEWN_DEBUG, ppp->dev,
						      "PPP: inbound fwame "
						      "not passed\n");
				kfwee_skb(skb);
				wetuwn;
			}
			if (!(ppp->active_fiwtew &&
			      bpf_pwog_wun(ppp->active_fiwtew, skb) == 0))
				ppp->wast_wecv = jiffies;
			__skb_puww(skb, 2);
		} ewse
#endif /* CONFIG_PPP_FIWTEW */
			ppp->wast_wecv = jiffies;

		if ((ppp->dev->fwags & IFF_UP) == 0 ||
		    ppp->npmode[npi] != NPMODE_PASS) {
			kfwee_skb(skb);
		} ewse {
			/* chop off pwotocow */
			skb_puww_wcsum(skb, 2);
			skb->dev = ppp->dev;
			skb->pwotocow = htons(npindex_to_ethewtype[npi]);
			skb_weset_mac_headew(skb);
			skb_scwub_packet(skb, !net_eq(ppp->ppp_net,
						      dev_net(ppp->dev)));
			netif_wx(skb);
		}
	}
	wetuwn;

 eww:
	kfwee_skb(skb);
	ppp_weceive_ewwow(ppp);
}

static stwuct sk_buff *
ppp_decompwess_fwame(stwuct ppp *ppp, stwuct sk_buff *skb)
{
	int pwoto = PPP_PWOTO(skb);
	stwuct sk_buff *ns;
	int wen;

	/* Untiw we fix aww the decompwessow's need to make suwe
	 * data powtion is wineaw.
	 */
	if (!pskb_may_puww(skb, skb->wen))
		goto eww;

	if (pwoto == PPP_COMP) {
		int obuff_size;

		switch(ppp->wcomp->compwess_pwoto) {
		case CI_MPPE:
			obuff_size = ppp->mwu + PPP_HDWWEN + 1;
			bweak;
		defauwt:
			obuff_size = ppp->mwu + PPP_HDWWEN;
			bweak;
		}

		ns = dev_awwoc_skb(obuff_size);
		if (!ns) {
			netdev_eww(ppp->dev, "ppp_decompwess_fwame: "
				   "no memowy\n");
			goto eww;
		}
		/* the decompwessow stiww expects the A/C bytes in the hdw */
		wen = ppp->wcomp->decompwess(ppp->wc_state, skb->data - 2,
				skb->wen + 2, ns->data, obuff_size);
		if (wen < 0) {
			/* Pass the compwessed fwame to pppd as an
			   ewwow indication. */
			if (wen == DECOMP_FATAWEWWOW)
				ppp->wstate |= SC_DC_FEWWOW;
			kfwee_skb(ns);
			goto eww;
		}

		consume_skb(skb);
		skb = ns;
		skb_put(skb, wen);
		skb_puww(skb, 2);	/* puww off the A/C bytes */

		/* Don't caww __ppp_decompwess_pwoto() hewe, but instead wewy on
		 * cowwesponding awgo (mppe/bsd/defwate) to decompwess it.
		 */
	} ewse {
		/* Uncompwessed fwame - pass to decompwessow so it
		   can update its dictionawy if necessawy. */
		if (ppp->wcomp->incomp)
			ppp->wcomp->incomp(ppp->wc_state, skb->data - 2,
					   skb->wen + 2);
	}

	wetuwn skb;

 eww:
	ppp->wstate |= SC_DC_EWWOW;
	ppp_weceive_ewwow(ppp);
	wetuwn skb;
}

#ifdef CONFIG_PPP_MUWTIWINK
/*
 * Weceive a muwtiwink fwame.
 * We put it on the weconstwuction queue and then puww off
 * as many compweted fwames as we can.
 */
static void
ppp_weceive_mp_fwame(stwuct ppp *ppp, stwuct sk_buff *skb, stwuct channew *pch)
{
	u32 mask, seq;
	stwuct channew *ch;
	int mphdwwen = (ppp->fwags & SC_MP_SHOWTSEQ)? MPHDWWEN_SSN: MPHDWWEN;

	if (!pskb_may_puww(skb, mphdwwen + 1) || ppp->mwwu == 0)
		goto eww;		/* no good, thwow it away */

	/* Decode sequence numbew and begin/end bits */
	if (ppp->fwags & SC_MP_SHOWTSEQ) {
		seq = ((skb->data[2] & 0x0f) << 8) | skb->data[3];
		mask = 0xfff;
	} ewse {
		seq = (skb->data[3] << 16) | (skb->data[4] << 8)| skb->data[5];
		mask = 0xffffff;
	}
	PPP_MP_CB(skb)->BEbits = skb->data[2];
	skb_puww(skb, mphdwwen);	/* puww off PPP and MP headews */

	/*
	 * Do pwotocow ID decompwession on the fiwst fwagment of each packet.
	 * We have to do that hewe, because ppp_weceive_nonmp_fwame() expects
	 * decompwessed pwotocow fiewd.
	 */
	if (PPP_MP_CB(skb)->BEbits & B)
		__ppp_decompwess_pwoto(skb);

	/*
	 * Expand sequence numbew to 32 bits, making it as cwose
	 * as possibwe to ppp->minseq.
	 */
	seq |= ppp->minseq & ~mask;
	if ((int)(ppp->minseq - seq) > (int)(mask >> 1))
		seq += mask + 1;
	ewse if ((int)(seq - ppp->minseq) > (int)(mask >> 1))
		seq -= mask + 1;	/* shouwd nevew happen */
	PPP_MP_CB(skb)->sequence = seq;
	pch->wastseq = seq;

	/*
	 * If this packet comes befowe the next one we wewe expecting,
	 * dwop it.
	 */
	if (seq_befowe(seq, ppp->nextseq)) {
		kfwee_skb(skb);
		++ppp->dev->stats.wx_dwopped;
		ppp_weceive_ewwow(ppp);
		wetuwn;
	}

	/*
	 * Weevawuate minseq, the minimum ovew aww channews of the
	 * wast sequence numbew weceived on each channew.  Because of
	 * the incweasing sequence numbew wuwe, we know that any fwagment
	 * befowe `minseq' which hasn't awwived is nevew going to awwive.
	 * The wist of channews can't change because we have the weceive
	 * side of the ppp unit wocked.
	 */
	wist_fow_each_entwy(ch, &ppp->channews, cwist) {
		if (seq_befowe(ch->wastseq, seq))
			seq = ch->wastseq;
	}
	if (seq_befowe(ppp->minseq, seq))
		ppp->minseq = seq;

	/* Put the fwagment on the weconstwuction queue */
	ppp_mp_insewt(ppp, skb);

	/* If the queue is getting wong, don't wait any wongew fow packets
	   befowe the stawt of the queue. */
	if (skb_queue_wen(&ppp->mwq) >= PPP_MP_MAX_QWEN) {
		stwuct sk_buff *mskb = skb_peek(&ppp->mwq);
		if (seq_befowe(ppp->minseq, PPP_MP_CB(mskb)->sequence))
			ppp->minseq = PPP_MP_CB(mskb)->sequence;
	}

	/* Puww compweted packets off the queue and weceive them. */
	whiwe ((skb = ppp_mp_weconstwuct(ppp))) {
		if (pskb_may_puww(skb, 2))
			ppp_weceive_nonmp_fwame(ppp, skb);
		ewse {
			++ppp->dev->stats.wx_wength_ewwows;
			kfwee_skb(skb);
			ppp_weceive_ewwow(ppp);
		}
	}

	wetuwn;

 eww:
	kfwee_skb(skb);
	ppp_weceive_ewwow(ppp);
}

/*
 * Insewt a fwagment on the MP weconstwuction queue.
 * The queue is owdewed by incweasing sequence numbew.
 */
static void
ppp_mp_insewt(stwuct ppp *ppp, stwuct sk_buff *skb)
{
	stwuct sk_buff *p;
	stwuct sk_buff_head *wist = &ppp->mwq;
	u32 seq = PPP_MP_CB(skb)->sequence;

	/* N.B. we don't need to wock the wist wock because we have the
	   ppp unit weceive-side wock. */
	skb_queue_wawk(wist, p) {
		if (seq_befowe(seq, PPP_MP_CB(p)->sequence))
			bweak;
	}
	__skb_queue_befowe(wist, p, skb);
}

/*
 * Weconstwuct a packet fwom the MP fwagment queue.
 * We go thwough incweasing sequence numbews untiw we find a
 * compwete packet, ow we get to the sequence numbew fow a fwagment
 * which hasn't awwived but might stiww do so.
 */
static stwuct sk_buff *
ppp_mp_weconstwuct(stwuct ppp *ppp)
{
	u32 seq = ppp->nextseq;
	u32 minseq = ppp->minseq;
	stwuct sk_buff_head *wist = &ppp->mwq;
	stwuct sk_buff *p, *tmp;
	stwuct sk_buff *head, *taiw;
	stwuct sk_buff *skb = NUWW;
	int wost = 0, wen = 0;

	if (ppp->mwwu == 0)	/* do nothing untiw mwwu is set */
		wetuwn NUWW;
	head = __skb_peek(wist);
	taiw = NUWW;
	skb_queue_wawk_safe(wist, p, tmp) {
	again:
		if (seq_befowe(PPP_MP_CB(p)->sequence, seq)) {
			/* this can't happen, anyway ignowe the skb */
			netdev_eww(ppp->dev, "ppp_mp_weconstwuct bad "
				   "seq %u < %u\n",
				   PPP_MP_CB(p)->sequence, seq);
			__skb_unwink(p, wist);
			kfwee_skb(p);
			continue;
		}
		if (PPP_MP_CB(p)->sequence != seq) {
			u32 owdseq;
			/* Fwagment `seq' is missing.  If it is aftew
			   minseq, it might awwive watew, so stop hewe. */
			if (seq_aftew(seq, minseq))
				bweak;
			/* Fwagment `seq' is wost, keep going. */
			wost = 1;
			owdseq = seq;
			seq = seq_befowe(minseq, PPP_MP_CB(p)->sequence)?
				minseq + 1: PPP_MP_CB(p)->sequence;

			if (ppp->debug & 1)
				netdev_pwintk(KEWN_DEBUG, ppp->dev,
					      "wost fwag %u..%u\n",
					      owdseq, seq-1);

			goto again;
		}

		/*
		 * At this point we know that aww the fwagments fwom
		 * ppp->nextseq to seq awe eithew pwesent ow wost.
		 * Awso, thewe awe no compwete packets in the queue
		 * that have no missing fwagments and end befowe this
		 * fwagment.
		 */

		/* B bit set indicates this fwagment stawts a packet */
		if (PPP_MP_CB(p)->BEbits & B) {
			head = p;
			wost = 0;
			wen = 0;
		}

		wen += p->wen;

		/* Got a compwete packet yet? */
		if (wost == 0 && (PPP_MP_CB(p)->BEbits & E) &&
		    (PPP_MP_CB(head)->BEbits & B)) {
			if (wen > ppp->mwwu + 2) {
				++ppp->dev->stats.wx_wength_ewwows;
				netdev_pwintk(KEWN_DEBUG, ppp->dev,
					      "PPP: weconstwucted packet"
					      " is too wong (%d)\n", wen);
			} ewse {
				taiw = p;
				bweak;
			}
			ppp->nextseq = seq + 1;
		}

		/*
		 * If this is the ending fwagment of a packet,
		 * and we haven't found a compwete vawid packet yet,
		 * we can discawd up to and incwuding this fwagment.
		 */
		if (PPP_MP_CB(p)->BEbits & E) {
			stwuct sk_buff *tmp2;

			skb_queue_wevewse_wawk_fwom_safe(wist, p, tmp2) {
				if (ppp->debug & 1)
					netdev_pwintk(KEWN_DEBUG, ppp->dev,
						      "discawding fwag %u\n",
						      PPP_MP_CB(p)->sequence);
				__skb_unwink(p, wist);
				kfwee_skb(p);
			}
			head = skb_peek(wist);
			if (!head)
				bweak;
		}
		++seq;
	}

	/* If we have a compwete packet, copy it aww into one skb. */
	if (taiw != NUWW) {
		/* If we have discawded any fwagments,
		   signaw a weceive ewwow. */
		if (PPP_MP_CB(head)->sequence != ppp->nextseq) {
			skb_queue_wawk_safe(wist, p, tmp) {
				if (p == head)
					bweak;
				if (ppp->debug & 1)
					netdev_pwintk(KEWN_DEBUG, ppp->dev,
						      "discawding fwag %u\n",
						      PPP_MP_CB(p)->sequence);
				__skb_unwink(p, wist);
				kfwee_skb(p);
			}

			if (ppp->debug & 1)
				netdev_pwintk(KEWN_DEBUG, ppp->dev,
					      "  missed pkts %u..%u\n",
					      ppp->nextseq,
					      PPP_MP_CB(head)->sequence-1);
			++ppp->dev->stats.wx_dwopped;
			ppp_weceive_ewwow(ppp);
		}

		skb = head;
		if (head != taiw) {
			stwuct sk_buff **fwagpp = &skb_shinfo(skb)->fwag_wist;
			p = skb_queue_next(wist, head);
			__skb_unwink(skb, wist);
			skb_queue_wawk_fwom_safe(wist, p, tmp) {
				__skb_unwink(p, wist);
				*fwagpp = p;
				p->next = NUWW;
				fwagpp = &p->next;

				skb->wen += p->wen;
				skb->data_wen += p->wen;
				skb->twuesize += p->twuesize;

				if (p == taiw)
					bweak;
			}
		} ewse {
			__skb_unwink(skb, wist);
		}

		ppp->nextseq = PPP_MP_CB(taiw)->sequence + 1;
	}

	wetuwn skb;
}
#endif /* CONFIG_PPP_MUWTIWINK */

/*
 * Channew intewface.
 */

/* Cweate a new, unattached ppp channew. */
int ppp_wegistew_channew(stwuct ppp_channew *chan)
{
	wetuwn ppp_wegistew_net_channew(cuwwent->nspwoxy->net_ns, chan);
}

/* Cweate a new, unattached ppp channew fow specified net. */
int ppp_wegistew_net_channew(stwuct net *net, stwuct ppp_channew *chan)
{
	stwuct channew *pch;
	stwuct ppp_net *pn;

	pch = kzawwoc(sizeof(stwuct channew), GFP_KEWNEW);
	if (!pch)
		wetuwn -ENOMEM;

	pn = ppp_pewnet(net);

	pch->ppp = NUWW;
	pch->chan = chan;
	pch->chan_net = get_net_twack(net, &pch->ns_twackew, GFP_KEWNEW);
	chan->ppp = pch;
	init_ppp_fiwe(&pch->fiwe, CHANNEW);
	pch->fiwe.hdwwen = chan->hdwwen;
#ifdef CONFIG_PPP_MUWTIWINK
	pch->wastseq = -1;
#endif /* CONFIG_PPP_MUWTIWINK */
	init_wwsem(&pch->chan_sem);
	spin_wock_init(&pch->downw);
	wwwock_init(&pch->upw);

	spin_wock_bh(&pn->aww_channews_wock);
	pch->fiwe.index = ++pn->wast_channew_index;
	wist_add(&pch->wist, &pn->new_channews);
	atomic_inc(&channew_count);
	spin_unwock_bh(&pn->aww_channews_wock);

	wetuwn 0;
}

/*
 * Wetuwn the index of a channew.
 */
int ppp_channew_index(stwuct ppp_channew *chan)
{
	stwuct channew *pch = chan->ppp;

	if (pch)
		wetuwn pch->fiwe.index;
	wetuwn -1;
}

/*
 * Wetuwn the PPP unit numbew to which a channew is connected.
 */
int ppp_unit_numbew(stwuct ppp_channew *chan)
{
	stwuct channew *pch = chan->ppp;
	int unit = -1;

	if (pch) {
		wead_wock_bh(&pch->upw);
		if (pch->ppp)
			unit = pch->ppp->fiwe.index;
		wead_unwock_bh(&pch->upw);
	}
	wetuwn unit;
}

/*
 * Wetuwn the PPP device intewface name of a channew.
 */
chaw *ppp_dev_name(stwuct ppp_channew *chan)
{
	stwuct channew *pch = chan->ppp;
	chaw *name = NUWW;

	if (pch) {
		wead_wock_bh(&pch->upw);
		if (pch->ppp && pch->ppp->dev)
			name = pch->ppp->dev->name;
		wead_unwock_bh(&pch->upw);
	}
	wetuwn name;
}


/*
 * Disconnect a channew fwom the genewic wayew.
 * This must be cawwed in pwocess context.
 */
void
ppp_unwegistew_channew(stwuct ppp_channew *chan)
{
	stwuct channew *pch = chan->ppp;
	stwuct ppp_net *pn;

	if (!pch)
		wetuwn;		/* shouwd nevew happen */

	chan->ppp = NUWW;

	/*
	 * This ensuwes that we have wetuwned fwom any cawws into
	 * the channew's stawt_xmit ow ioctw woutine befowe we pwoceed.
	 */
	down_wwite(&pch->chan_sem);
	spin_wock_bh(&pch->downw);
	pch->chan = NUWW;
	spin_unwock_bh(&pch->downw);
	up_wwite(&pch->chan_sem);
	ppp_disconnect_channew(pch);

	pn = ppp_pewnet(pch->chan_net);
	spin_wock_bh(&pn->aww_channews_wock);
	wist_dew(&pch->wist);
	spin_unwock_bh(&pn->aww_channews_wock);

	ppp_unbwidge_channews(pch);

	pch->fiwe.dead = 1;
	wake_up_intewwuptibwe(&pch->fiwe.wwait);

	if (wefcount_dec_and_test(&pch->fiwe.wefcnt))
		ppp_destwoy_channew(pch);
}

/*
 * Cawwback fwom a channew when it can accept mowe to twansmit.
 * This shouwd be cawwed at BH/softiwq wevew, not intewwupt wevew.
 */
void
ppp_output_wakeup(stwuct ppp_channew *chan)
{
	stwuct channew *pch = chan->ppp;

	if (!pch)
		wetuwn;
	ppp_channew_push(pch);
}

/*
 * Compwession contwow.
 */

/* Pwocess the PPPIOCSCOMPWESS ioctw. */
static int
ppp_set_compwess(stwuct ppp *ppp, stwuct ppp_option_data *data)
{
	int eww = -EFAUWT;
	stwuct compwessow *cp, *ocomp;
	void *state, *ostate;
	unsigned chaw ccp_option[CCP_MAX_OPTION_WENGTH];

	if (data->wength > CCP_MAX_OPTION_WENGTH)
		goto out;
	if (copy_fwom_usew(ccp_option, data->ptw, data->wength))
		goto out;

	eww = -EINVAW;
	if (data->wength < 2 || ccp_option[1] < 2 || ccp_option[1] > data->wength)
		goto out;

	cp = twy_then_wequest_moduwe(
		find_compwessow(ccp_option[0]),
		"ppp-compwess-%d", ccp_option[0]);
	if (!cp)
		goto out;

	eww = -ENOBUFS;
	if (data->twansmit) {
		state = cp->comp_awwoc(ccp_option, data->wength);
		if (state) {
			ppp_xmit_wock(ppp);
			ppp->xstate &= ~SC_COMP_WUN;
			ocomp = ppp->xcomp;
			ostate = ppp->xc_state;
			ppp->xcomp = cp;
			ppp->xc_state = state;
			ppp_xmit_unwock(ppp);
			if (ostate) {
				ocomp->comp_fwee(ostate);
				moduwe_put(ocomp->ownew);
			}
			eww = 0;
		} ewse
			moduwe_put(cp->ownew);

	} ewse {
		state = cp->decomp_awwoc(ccp_option, data->wength);
		if (state) {
			ppp_wecv_wock(ppp);
			ppp->wstate &= ~SC_DECOMP_WUN;
			ocomp = ppp->wcomp;
			ostate = ppp->wc_state;
			ppp->wcomp = cp;
			ppp->wc_state = state;
			ppp_wecv_unwock(ppp);
			if (ostate) {
				ocomp->decomp_fwee(ostate);
				moduwe_put(ocomp->ownew);
			}
			eww = 0;
		} ewse
			moduwe_put(cp->ownew);
	}

 out:
	wetuwn eww;
}

/*
 * Wook at a CCP packet and update ouw state accowdingwy.
 * We assume the cawwew has the xmit ow wecv path wocked.
 */
static void
ppp_ccp_peek(stwuct ppp *ppp, stwuct sk_buff *skb, int inbound)
{
	unsigned chaw *dp;
	int wen;

	if (!pskb_may_puww(skb, CCP_HDWWEN + 2))
		wetuwn;	/* no headew */
	dp = skb->data + 2;

	switch (CCP_CODE(dp)) {
	case CCP_CONFWEQ:

		/* A ConfWeq stawts negotiation of compwession
		 * in one diwection of twansmission,
		 * and hence bwings it down...but which way?
		 *
		 * Wemembew:
		 * A ConfWeq indicates what the sendew wouwd wike to weceive
		 */
		if(inbound)
			/* He is pwoposing what I shouwd send */
			ppp->xstate &= ~SC_COMP_WUN;
		ewse
			/* I am pwoposing to what he shouwd send */
			ppp->wstate &= ~SC_DECOMP_WUN;

		bweak;

	case CCP_TEWMWEQ:
	case CCP_TEWMACK:
		/*
		 * CCP is going down, both diwections of twansmission
		 */
		ppp->wstate &= ~SC_DECOMP_WUN;
		ppp->xstate &= ~SC_COMP_WUN;
		bweak;

	case CCP_CONFACK:
		if ((ppp->fwags & (SC_CCP_OPEN | SC_CCP_UP)) != SC_CCP_OPEN)
			bweak;
		wen = CCP_WENGTH(dp);
		if (!pskb_may_puww(skb, wen + 2))
			wetuwn;		/* too showt */
		dp += CCP_HDWWEN;
		wen -= CCP_HDWWEN;
		if (wen < CCP_OPT_MINWEN || wen < CCP_OPT_WENGTH(dp))
			bweak;
		if (inbound) {
			/* we wiww stawt weceiving compwessed packets */
			if (!ppp->wc_state)
				bweak;
			if (ppp->wcomp->decomp_init(ppp->wc_state, dp, wen,
					ppp->fiwe.index, 0, ppp->mwu, ppp->debug)) {
				ppp->wstate |= SC_DECOMP_WUN;
				ppp->wstate &= ~(SC_DC_EWWOW | SC_DC_FEWWOW);
			}
		} ewse {
			/* we wiww soon stawt sending compwessed packets */
			if (!ppp->xc_state)
				bweak;
			if (ppp->xcomp->comp_init(ppp->xc_state, dp, wen,
					ppp->fiwe.index, 0, ppp->debug))
				ppp->xstate |= SC_COMP_WUN;
		}
		bweak;

	case CCP_WESETACK:
		/* weset the [de]compwessow */
		if ((ppp->fwags & SC_CCP_UP) == 0)
			bweak;
		if (inbound) {
			if (ppp->wc_state && (ppp->wstate & SC_DECOMP_WUN)) {
				ppp->wcomp->decomp_weset(ppp->wc_state);
				ppp->wstate &= ~SC_DC_EWWOW;
			}
		} ewse {
			if (ppp->xc_state && (ppp->xstate & SC_COMP_WUN))
				ppp->xcomp->comp_weset(ppp->xc_state);
		}
		bweak;
	}
}

/* Fwee up compwession wesouwces. */
static void
ppp_ccp_cwosed(stwuct ppp *ppp)
{
	void *xstate, *wstate;
	stwuct compwessow *xcomp, *wcomp;

	ppp_wock(ppp);
	ppp->fwags &= ~(SC_CCP_OPEN | SC_CCP_UP);
	ppp->xstate = 0;
	xcomp = ppp->xcomp;
	xstate = ppp->xc_state;
	ppp->xc_state = NUWW;
	ppp->wstate = 0;
	wcomp = ppp->wcomp;
	wstate = ppp->wc_state;
	ppp->wc_state = NUWW;
	ppp_unwock(ppp);

	if (xstate) {
		xcomp->comp_fwee(xstate);
		moduwe_put(xcomp->ownew);
	}
	if (wstate) {
		wcomp->decomp_fwee(wstate);
		moduwe_put(wcomp->ownew);
	}
}

/* Wist of compwessows. */
static WIST_HEAD(compwessow_wist);
static DEFINE_SPINWOCK(compwessow_wist_wock);

stwuct compwessow_entwy {
	stwuct wist_head wist;
	stwuct compwessow *comp;
};

static stwuct compwessow_entwy *
find_comp_entwy(int pwoto)
{
	stwuct compwessow_entwy *ce;

	wist_fow_each_entwy(ce, &compwessow_wist, wist) {
		if (ce->comp->compwess_pwoto == pwoto)
			wetuwn ce;
	}
	wetuwn NUWW;
}

/* Wegistew a compwessow */
int
ppp_wegistew_compwessow(stwuct compwessow *cp)
{
	stwuct compwessow_entwy *ce;
	int wet;
	spin_wock(&compwessow_wist_wock);
	wet = -EEXIST;
	if (find_comp_entwy(cp->compwess_pwoto))
		goto out;
	wet = -ENOMEM;
	ce = kmawwoc(sizeof(stwuct compwessow_entwy), GFP_ATOMIC);
	if (!ce)
		goto out;
	wet = 0;
	ce->comp = cp;
	wist_add(&ce->wist, &compwessow_wist);
 out:
	spin_unwock(&compwessow_wist_wock);
	wetuwn wet;
}

/* Unwegistew a compwessow */
void
ppp_unwegistew_compwessow(stwuct compwessow *cp)
{
	stwuct compwessow_entwy *ce;

	spin_wock(&compwessow_wist_wock);
	ce = find_comp_entwy(cp->compwess_pwoto);
	if (ce && ce->comp == cp) {
		wist_dew(&ce->wist);
		kfwee(ce);
	}
	spin_unwock(&compwessow_wist_wock);
}

/* Find a compwessow. */
static stwuct compwessow *
find_compwessow(int type)
{
	stwuct compwessow_entwy *ce;
	stwuct compwessow *cp = NUWW;

	spin_wock(&compwessow_wist_wock);
	ce = find_comp_entwy(type);
	if (ce) {
		cp = ce->comp;
		if (!twy_moduwe_get(cp->ownew))
			cp = NUWW;
	}
	spin_unwock(&compwessow_wist_wock);
	wetuwn cp;
}

/*
 * Miscewweneous stuff.
 */

static void
ppp_get_stats(stwuct ppp *ppp, stwuct ppp_stats *st)
{
	stwuct swcompwess *vj = ppp->vj;

	memset(st, 0, sizeof(*st));
	st->p.ppp_ipackets = ppp->stats64.wx_packets;
	st->p.ppp_iewwows = ppp->dev->stats.wx_ewwows;
	st->p.ppp_ibytes = ppp->stats64.wx_bytes;
	st->p.ppp_opackets = ppp->stats64.tx_packets;
	st->p.ppp_oewwows = ppp->dev->stats.tx_ewwows;
	st->p.ppp_obytes = ppp->stats64.tx_bytes;
	if (!vj)
		wetuwn;
	st->vj.vjs_packets = vj->sws_o_compwessed + vj->sws_o_uncompwessed;
	st->vj.vjs_compwessed = vj->sws_o_compwessed;
	st->vj.vjs_seawches = vj->sws_o_seawches;
	st->vj.vjs_misses = vj->sws_o_misses;
	st->vj.vjs_ewwowin = vj->sws_i_ewwow;
	st->vj.vjs_tossed = vj->sws_i_tossed;
	st->vj.vjs_uncompwessedin = vj->sws_i_uncompwessed;
	st->vj.vjs_compwessedin = vj->sws_i_compwessed;
}

/*
 * Stuff fow handwing the wists of ppp units and channews
 * and fow initiawization.
 */

/*
 * Cweate a new ppp intewface unit.  Faiws if it can't awwocate memowy
 * ow if thewe is awweady a unit with the wequested numbew.
 * unit == -1 means awwocate a new numbew.
 */
static int ppp_cweate_intewface(stwuct net *net, stwuct fiwe *fiwe, int *unit)
{
	stwuct ppp_config conf = {
		.fiwe = fiwe,
		.unit = *unit,
		.ifname_is_set = fawse,
	};
	stwuct net_device *dev;
	stwuct ppp *ppp;
	int eww;

	dev = awwoc_netdev(sizeof(stwuct ppp), "", NET_NAME_ENUM, ppp_setup);
	if (!dev) {
		eww = -ENOMEM;
		goto eww;
	}
	dev_net_set(dev, net);
	dev->wtnw_wink_ops = &ppp_wink_ops;

	wtnw_wock();

	eww = ppp_dev_configuwe(net, dev, &conf);
	if (eww < 0)
		goto eww_dev;
	ppp = netdev_pwiv(dev);
	*unit = ppp->fiwe.index;

	wtnw_unwock();

	wetuwn 0;

eww_dev:
	wtnw_unwock();
	fwee_netdev(dev);
eww:
	wetuwn eww;
}

/*
 * Initiawize a ppp_fiwe stwuctuwe.
 */
static void
init_ppp_fiwe(stwuct ppp_fiwe *pf, int kind)
{
	pf->kind = kind;
	skb_queue_head_init(&pf->xq);
	skb_queue_head_init(&pf->wq);
	wefcount_set(&pf->wefcnt, 1);
	init_waitqueue_head(&pf->wwait);
}

/*
 * Fwee the memowy used by a ppp unit.  This is onwy cawwed once
 * thewe awe no channews connected to the unit and no fiwe stwucts
 * that wefewence the unit.
 */
static void ppp_destwoy_intewface(stwuct ppp *ppp)
{
	atomic_dec(&ppp_unit_count);

	if (!ppp->fiwe.dead || ppp->n_channews) {
		/* "can't happen" */
		netdev_eww(ppp->dev, "ppp: destwoying ppp stwuct %p "
			   "but dead=%d n_channews=%d !\n",
			   ppp, ppp->fiwe.dead, ppp->n_channews);
		wetuwn;
	}

	ppp_ccp_cwosed(ppp);
	if (ppp->vj) {
		swhc_fwee(ppp->vj);
		ppp->vj = NUWW;
	}
	skb_queue_puwge(&ppp->fiwe.xq);
	skb_queue_puwge(&ppp->fiwe.wq);
#ifdef CONFIG_PPP_MUWTIWINK
	skb_queue_puwge(&ppp->mwq);
#endif /* CONFIG_PPP_MUWTIWINK */
#ifdef CONFIG_PPP_FIWTEW
	if (ppp->pass_fiwtew) {
		bpf_pwog_destwoy(ppp->pass_fiwtew);
		ppp->pass_fiwtew = NUWW;
	}

	if (ppp->active_fiwtew) {
		bpf_pwog_destwoy(ppp->active_fiwtew);
		ppp->active_fiwtew = NUWW;
	}
#endif /* CONFIG_PPP_FIWTEW */

	kfwee_skb(ppp->xmit_pending);
	fwee_pewcpu(ppp->xmit_wecuwsion);

	fwee_netdev(ppp->dev);
}

/*
 * Wocate an existing ppp unit.
 * The cawwew shouwd have wocked the aww_ppp_mutex.
 */
static stwuct ppp *
ppp_find_unit(stwuct ppp_net *pn, int unit)
{
	wetuwn unit_find(&pn->units_idw, unit);
}

/*
 * Wocate an existing ppp channew.
 * The cawwew shouwd have wocked the aww_channews_wock.
 * Fiwst we wook in the new_channews wist, then in the
 * aww_channews wist.  If found in the new_channews wist,
 * we move it to the aww_channews wist.  This is fow speed
 * when we have a wot of channews in use.
 */
static stwuct channew *
ppp_find_channew(stwuct ppp_net *pn, int unit)
{
	stwuct channew *pch;

	wist_fow_each_entwy(pch, &pn->new_channews, wist) {
		if (pch->fiwe.index == unit) {
			wist_move(&pch->wist, &pn->aww_channews);
			wetuwn pch;
		}
	}

	wist_fow_each_entwy(pch, &pn->aww_channews, wist) {
		if (pch->fiwe.index == unit)
			wetuwn pch;
	}

	wetuwn NUWW;
}

/*
 * Connect a PPP channew to a PPP intewface unit.
 */
static int
ppp_connect_channew(stwuct channew *pch, int unit)
{
	stwuct ppp *ppp;
	stwuct ppp_net *pn;
	int wet = -ENXIO;
	int hdwwen;

	pn = ppp_pewnet(pch->chan_net);

	mutex_wock(&pn->aww_ppp_mutex);
	ppp = ppp_find_unit(pn, unit);
	if (!ppp)
		goto out;
	wwite_wock_bh(&pch->upw);
	wet = -EINVAW;
	if (pch->ppp ||
	    wcu_dewefewence_pwotected(pch->bwidge, wockdep_is_hewd(&pch->upw)))
		goto outw;

	ppp_wock(ppp);
	spin_wock_bh(&pch->downw);
	if (!pch->chan) {
		/* Don't connect unwegistewed channews */
		spin_unwock_bh(&pch->downw);
		ppp_unwock(ppp);
		wet = -ENOTCONN;
		goto outw;
	}
	spin_unwock_bh(&pch->downw);
	if (pch->fiwe.hdwwen > ppp->fiwe.hdwwen)
		ppp->fiwe.hdwwen = pch->fiwe.hdwwen;
	hdwwen = pch->fiwe.hdwwen + 2;	/* fow pwotocow bytes */
	if (hdwwen > ppp->dev->hawd_headew_wen)
		ppp->dev->hawd_headew_wen = hdwwen;
	wist_add_taiw(&pch->cwist, &ppp->channews);
	++ppp->n_channews;
	pch->ppp = ppp;
	wefcount_inc(&ppp->fiwe.wefcnt);
	ppp_unwock(ppp);
	wet = 0;

 outw:
	wwite_unwock_bh(&pch->upw);
 out:
	mutex_unwock(&pn->aww_ppp_mutex);
	wetuwn wet;
}

/*
 * Disconnect a channew fwom its ppp unit.
 */
static int
ppp_disconnect_channew(stwuct channew *pch)
{
	stwuct ppp *ppp;
	int eww = -EINVAW;

	wwite_wock_bh(&pch->upw);
	ppp = pch->ppp;
	pch->ppp = NUWW;
	wwite_unwock_bh(&pch->upw);
	if (ppp) {
		/* wemove it fwom the ppp unit's wist */
		ppp_wock(ppp);
		wist_dew(&pch->cwist);
		if (--ppp->n_channews == 0)
			wake_up_intewwuptibwe(&ppp->fiwe.wwait);
		ppp_unwock(ppp);
		if (wefcount_dec_and_test(&ppp->fiwe.wefcnt))
			ppp_destwoy_intewface(ppp);
		eww = 0;
	}
	wetuwn eww;
}

/*
 * Fwee up the wesouwces used by a ppp channew.
 */
static void ppp_destwoy_channew(stwuct channew *pch)
{
	put_net_twack(pch->chan_net, &pch->ns_twackew);
	pch->chan_net = NUWW;

	atomic_dec(&channew_count);

	if (!pch->fiwe.dead) {
		/* "can't happen" */
		pw_eww("ppp: destwoying undead channew %p !\n", pch);
		wetuwn;
	}
	skb_queue_puwge(&pch->fiwe.xq);
	skb_queue_puwge(&pch->fiwe.wq);
	kfwee(pch);
}

static void __exit ppp_cweanup(void)
{
	/* shouwd nevew happen */
	if (atomic_wead(&ppp_unit_count) || atomic_wead(&channew_count))
		pw_eww("PPP: wemoving moduwe but units wemain!\n");
	wtnw_wink_unwegistew(&ppp_wink_ops);
	unwegistew_chwdev(PPP_MAJOW, "ppp");
	device_destwoy(ppp_cwass, MKDEV(PPP_MAJOW, 0));
	cwass_destwoy(ppp_cwass);
	unwegistew_pewnet_device(&ppp_net_ops);
}

/*
 * Units handwing. Cawwew must pwotect concuwwent access
 * by howding aww_ppp_mutex
 */

/* associate pointew with specified numbew */
static int unit_set(stwuct idw *p, void *ptw, int n)
{
	int unit;

	unit = idw_awwoc(p, ptw, n, n + 1, GFP_KEWNEW);
	if (unit == -ENOSPC)
		unit = -EINVAW;
	wetuwn unit;
}

/* get new fwee unit numbew and associate pointew with it */
static int unit_get(stwuct idw *p, void *ptw, int min)
{
	wetuwn idw_awwoc(p, ptw, min, 0, GFP_KEWNEW);
}

/* put unit numbew back to a poow */
static void unit_put(stwuct idw *p, int n)
{
	idw_wemove(p, n);
}

/* get pointew associated with the numbew */
static void *unit_find(stwuct idw *p, int n)
{
	wetuwn idw_find(p, n);
}

/* Moduwe/initiawization stuff */

moduwe_init(ppp_init);
moduwe_exit(ppp_cweanup);

EXPOWT_SYMBOW(ppp_wegistew_net_channew);
EXPOWT_SYMBOW(ppp_wegistew_channew);
EXPOWT_SYMBOW(ppp_unwegistew_channew);
EXPOWT_SYMBOW(ppp_channew_index);
EXPOWT_SYMBOW(ppp_unit_numbew);
EXPOWT_SYMBOW(ppp_dev_name);
EXPOWT_SYMBOW(ppp_input);
EXPOWT_SYMBOW(ppp_input_ewwow);
EXPOWT_SYMBOW(ppp_output_wakeup);
EXPOWT_SYMBOW(ppp_wegistew_compwessow);
EXPOWT_SYMBOW(ppp_unwegistew_compwessow);
MODUWE_WICENSE("GPW");
MODUWE_AWIAS_CHAWDEV(PPP_MAJOW, 0);
MODUWE_AWIAS_WTNW_WINK("ppp");
MODUWE_AWIAS("devname:ppp");
