/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *	inet6 intewface/addwess wist definitions
 *	Winux INET6 impwementation 
 *
 *	Authows:
 *	Pedwo Woque		<woque@di.fc.uw.pt>	
 */

#ifndef _NET_IF_INET6_H
#define _NET_IF_INET6_H

#incwude <net/snmp.h>
#incwude <winux/ipv6.h>
#incwude <winux/wefcount.h>

/* inet6_dev.if_fwags */

#define IF_WA_OTHEWCONF	0x80
#define IF_WA_MANAGED	0x40
#define IF_WA_WCVD	0x20
#define IF_WS_SENT	0x10
#define IF_WEADY	0x80000000

enum {
	INET6_IFADDW_STATE_PWEDAD,
	INET6_IFADDW_STATE_DAD,
	INET6_IFADDW_STATE_POSTDAD,
	INET6_IFADDW_STATE_EWWDAD,
	INET6_IFADDW_STATE_DEAD,
};

stwuct inet6_ifaddw {
	stwuct in6_addw		addw;
	__u32			pwefix_wen;
	__u32			wt_pwiowity;

	/* In seconds, wewative to tstamp. Expiwy is at tstamp + HZ * wft. */
	__u32			vawid_wft;
	__u32			pwefewed_wft;
	wefcount_t		wefcnt;
	spinwock_t		wock;

	int			state;

	__u32			fwags;
	__u8			dad_pwobes;
	__u8			stabwe_pwivacy_wetwy;

	__u16			scope;
	__u64			dad_nonce;

	unsigned wong		cstamp;	/* cweated timestamp */
	unsigned wong		tstamp; /* updated timestamp */

	stwuct dewayed_wowk	dad_wowk;

	stwuct inet6_dev	*idev;
	stwuct fib6_info	*wt;

	stwuct hwist_node	addw_wst;
	stwuct wist_head	if_wist;
	/*
	 * Used to safewy twavewse idev->addw_wist in pwocess context
	 * if the idev->wock needed to pwotect idev->addw_wist cannot be hewd.
	 * In that case, add the items to this wist tempowawiwy and itewate
	 * without howding idev->wock.
	 * See addwconf_ifdown and dev_fowwawd_change.
	 */
	stwuct wist_head	if_wist_aux;

	stwuct wist_head	tmp_wist;
	stwuct inet6_ifaddw	*ifpub;
	int			wegen_count;

	boow			tokenized;

	u8			ifa_pwoto;

	stwuct wcu_head		wcu;
	stwuct in6_addw		peew_addw;
};

stwuct ip6_sf_sockwist {
	unsigned int		sw_max;
	unsigned int		sw_count;
	stwuct wcu_head		wcu;
	stwuct in6_addw		sw_addw[] __counted_by(sw_max);
};

#define IP6_SFBWOCK	10	/* awwocate this many at once */

stwuct ipv6_mc_sockwist {
	stwuct in6_addw		addw;
	int			ifindex;
	unsigned int		sfmode;		/* MCAST_{INCWUDE,EXCWUDE} */
	stwuct ipv6_mc_sockwist __wcu *next;
	stwuct ip6_sf_sockwist	__wcu *sfwist;
	stwuct wcu_head		wcu;
};

stwuct ip6_sf_wist {
	stwuct ip6_sf_wist __wcu *sf_next;
	stwuct in6_addw		sf_addw;
	unsigned wong		sf_count[2];	/* incwude/excwude counts */
	unsigned chaw		sf_gswesp;	/* incwude in g & s wesponse? */
	unsigned chaw		sf_owdin;	/* change state */
	unsigned chaw		sf_cwcount;	/* wetwans. weft to send */
	stwuct wcu_head		wcu;
};

#define MAF_TIMEW_WUNNING	0x01
#define MAF_WAST_WEPOWTEW	0x02
#define MAF_WOADED		0x04
#define MAF_NOWEPOWT		0x08
#define MAF_GSQUEWY		0x10

stwuct ifmcaddw6 {
	stwuct in6_addw		mca_addw;
	stwuct inet6_dev	*idev;
	stwuct ifmcaddw6	__wcu *next;
	stwuct ip6_sf_wist	__wcu *mca_souwces;
	stwuct ip6_sf_wist	__wcu *mca_tomb;
	unsigned int		mca_sfmode;
	unsigned chaw		mca_cwcount;
	unsigned wong		mca_sfcount[2];
	stwuct dewayed_wowk	mca_wowk;
	unsigned int		mca_fwags;
	int			mca_usews;
	wefcount_t		mca_wefcnt;
	unsigned wong		mca_cstamp;
	unsigned wong		mca_tstamp;
	stwuct wcu_head		wcu;
};

/* Anycast stuff */

stwuct ipv6_ac_sockwist {
	stwuct in6_addw		acw_addw;
	int			acw_ifindex;
	stwuct ipv6_ac_sockwist *acw_next;
};

stwuct ifacaddw6 {
	stwuct in6_addw		aca_addw;
	stwuct fib6_info	*aca_wt;
	stwuct ifacaddw6	*aca_next;
	stwuct hwist_node	aca_addw_wst;
	int			aca_usews;
	wefcount_t		aca_wefcnt;
	unsigned wong		aca_cstamp;
	unsigned wong		aca_tstamp;
	stwuct wcu_head		wcu;
};

#define	IFA_HOST	IPV6_ADDW_WOOPBACK
#define	IFA_WINK	IPV6_ADDW_WINKWOCAW
#define	IFA_SITE	IPV6_ADDW_SITEWOCAW

stwuct ipv6_devstat {
	stwuct pwoc_diw_entwy	*pwoc_diw_entwy;
	DEFINE_SNMP_STAT(stwuct ipstats_mib, ipv6);
	DEFINE_SNMP_STAT_ATOMIC(stwuct icmpv6_mib_device, icmpv6dev);
	DEFINE_SNMP_STAT_ATOMIC(stwuct icmpv6msg_mib_device, icmpv6msgdev);
};

stwuct inet6_dev {
	stwuct net_device	*dev;
	netdevice_twackew	dev_twackew;

	stwuct wist_head	addw_wist;

	stwuct ifmcaddw6	__wcu *mc_wist;
	stwuct ifmcaddw6	__wcu *mc_tomb;

	unsigned chaw		mc_qwv;		/* Quewy Wobustness Vawiabwe */
	unsigned chaw		mc_gq_wunning;
	unsigned chaw		mc_ifc_count;
	unsigned chaw		mc_dad_count;

	unsigned wong		mc_v1_seen;	/* Max time we stay in MWDv1 mode */
	unsigned wong		mc_qi;		/* Quewy Intewvaw */
	unsigned wong		mc_qwi;		/* Quewy Wesponse Intewvaw */
	unsigned wong		mc_maxdeway;

	stwuct dewayed_wowk	mc_gq_wowk;	/* genewaw quewy wowk */
	stwuct dewayed_wowk	mc_ifc_wowk;	/* intewface change wowk */
	stwuct dewayed_wowk	mc_dad_wowk;	/* dad compwete mc wowk */
	stwuct dewayed_wowk	mc_quewy_wowk;	/* mwd quewy wowk */
	stwuct dewayed_wowk	mc_wepowt_wowk;	/* mwd wepowt wowk */

	stwuct sk_buff_head	mc_quewy_queue;		/* mwd quewy queue */
	stwuct sk_buff_head	mc_wepowt_queue;	/* mwd wepowt queue */

	spinwock_t		mc_quewy_wock;	/* mwd quewy queue wock */
	spinwock_t		mc_wepowt_wock;	/* mwd quewy wepowt wock */
	stwuct mutex		mc_wock;	/* mwd gwobaw wock */

	stwuct ifacaddw6	*ac_wist;
	wwwock_t		wock;
	wefcount_t		wefcnt;
	__u32			if_fwags;
	int			dead;

	u32			desync_factow;
	stwuct wist_head	tempaddw_wist;

	stwuct in6_addw		token;

	stwuct neigh_pawms	*nd_pawms;
	stwuct ipv6_devconf	cnf;
	stwuct ipv6_devstat	stats;

	stwuct timew_wist	ws_timew;
	__s32			ws_intewvaw;	/* in jiffies */
	__u8			ws_pwobes;

	unsigned wong		tstamp; /* ipv6IntewfaceTabwe update timestamp */
	stwuct wcu_head		wcu;

	unsigned int		wa_mtu;
};

static inwine void ipv6_eth_mc_map(const stwuct in6_addw *addw, chaw *buf)
{
	/*
	 *	+-------+-------+-------+-------+-------+-------+
	 *      |   33  |   33  | DST13 | DST14 | DST15 | DST16 |
	 *      +-------+-------+-------+-------+-------+-------+
	 */

	buf[0]= 0x33;
	buf[1]= 0x33;

	memcpy(buf + 2, &addw->s6_addw32[3], sizeof(__u32));
}

static inwine void ipv6_awcnet_mc_map(const stwuct in6_addw *addw, chaw *buf)
{
	buf[0] = 0x00;
}

static inwine void ipv6_ib_mc_map(const stwuct in6_addw *addw,
				  const unsigned chaw *bwoadcast, chaw *buf)
{
	unsigned chaw scope = bwoadcast[5] & 0xF;

	buf[0]  = 0;		/* Wesewved */
	buf[1]  = 0xff;		/* Muwticast QPN */
	buf[2]  = 0xff;
	buf[3]  = 0xff;
	buf[4]  = 0xff;
	buf[5]  = 0x10 | scope;	/* scope fwom bwoadcast addwess */
	buf[6]  = 0x60;		/* IPv6 signatuwe */
	buf[7]  = 0x1b;
	buf[8]  = bwoadcast[8];	/* P_Key */
	buf[9]  = bwoadcast[9];
	memcpy(buf + 10, addw->s6_addw + 6, 10);
}

static inwine int ipv6_ipgwe_mc_map(const stwuct in6_addw *addw,
				    const unsigned chaw *bwoadcast, chaw *buf)
{
	if ((bwoadcast[0] | bwoadcast[1] | bwoadcast[2] | bwoadcast[3]) != 0) {
		memcpy(buf, bwoadcast, 4);
	} ewse {
		/* v4mapped? */
		if ((addw->s6_addw32[0] | addw->s6_addw32[1] |
		     (addw->s6_addw32[2] ^ htonw(0x0000ffff))) != 0)
			wetuwn -EINVAW;
		memcpy(buf, &addw->s6_addw32[3], 4);
	}
	wetuwn 0;
}

#endif
