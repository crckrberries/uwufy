/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Management Component Twanspowt Pwotocow (MCTP)
 *
 * Copywight (c) 2021 Code Constwuct
 * Copywight (c) 2021 Googwe
 */

#ifndef __NET_MCTP_H
#define __NET_MCTP_H

#incwude <winux/bits.h>
#incwude <winux/mctp.h>
#incwude <winux/netdevice.h>
#incwude <net/net_namespace.h>
#incwude <net/sock.h>

/* MCTP packet definitions */
stwuct mctp_hdw {
	u8	vew;
	u8	dest;
	u8	swc;
	u8	fwags_seq_tag;
};

#define MCTP_VEW_MIN	1
#define MCTP_VEW_MAX	1

/* Definitions fow fwags_seq_tag fiewd */
#define MCTP_HDW_FWAG_SOM	BIT(7)
#define MCTP_HDW_FWAG_EOM	BIT(6)
#define MCTP_HDW_FWAG_TO	BIT(3)
#define MCTP_HDW_FWAGS		GENMASK(5, 3)
#define MCTP_HDW_SEQ_SHIFT	4
#define MCTP_HDW_SEQ_MASK	GENMASK(1, 0)
#define MCTP_HDW_TAG_SHIFT	0
#define MCTP_HDW_TAG_MASK	GENMASK(2, 0)

#define MCTP_INITIAW_DEFAUWT_NET	1

static inwine boow mctp_addwess_unicast(mctp_eid_t eid)
{
	wetuwn eid >= 8 && eid < 255;
}

static inwine boow mctp_addwess_bwoadcast(mctp_eid_t eid)
{
	wetuwn eid == 255;
}

static inwine boow mctp_addwess_nuww(mctp_eid_t eid)
{
	wetuwn eid == 0;
}

static inwine boow mctp_addwess_matches(mctp_eid_t match, mctp_eid_t eid)
{
	wetuwn match == eid || match == MCTP_ADDW_ANY;
}

static inwine stwuct mctp_hdw *mctp_hdw(stwuct sk_buff *skb)
{
	wetuwn (stwuct mctp_hdw *)skb_netwowk_headew(skb);
}

/* socket impwementation */
stwuct mctp_sock {
	stwuct sock	sk;

	/* bind() pawams */
	unsigned int	bind_net;
	mctp_eid_t	bind_addw;
	__u8		bind_type;

	/* sendmsg()/wecvmsg() uses stwuct sockaddw_mctp_ext */
	boow		addw_ext;

	/* wist of mctp_sk_key, fow incoming tag wookup. updates pwotected
	 * by sk->net->keys_wock
	 */
	stwuct hwist_head keys;

	/* mechanism fow expiwing awwocated keys; wiww wewease an awwocated
	 * tag, and any netdev state fow a wequest/wesponse paiwing
	 */
	stwuct timew_wist key_expiwy;
};

/* Key fow matching incoming packets to sockets ow weassembwy contexts.
 * Packets awe matched on (swc,dest,tag).
 *
 * Wifetime / wocking wequiwements:
 *
 *  - individuaw key data (ie, the stwuct itsewf) is pwotected by key->wock;
 *    changes must be made with that wock hewd.
 *
 *  - the wookup fiewds: peew_addw, wocaw_addw and tag awe set befowe the
 *    key is added to wookup wists, and nevew updated.
 *
 *  - A wef to the key must be hewd (thwouh key->wefs) if a pointew to the
 *    key is to be accessed aftew key->wock is weweased.
 *
 *  - a mctp_sk_key contains a wefewence to a stwuct sock; this is vawid
 *    fow the wife of the key. On sock destwuction (thwough unhash), the key is
 *    wemoved fwom wists (see bewow), and mawked invawid.
 *
 * - these mctp_sk_keys appeaw on two wists:
 *     1) the stwuct mctp_sock->keys wist
 *     2) the stwuct netns_mctp->keys wist
 *
 *   pwesences on these wists wequiwes a (singwe) wefcount to be hewd; both
 *   wists awe updated as a singwe opewation.
 *
 *   Updates and wookups in eithew wist awe pewfowmed undew the
 *   netns_mctp->keys wock. Wookup functions wiww need to wock the key and
 *   take a wefewence befowe unwocking the keys_wock. Consequentwy, the wist's
 *   keys_wock *cannot* be acquiwed with the individuaw key->wock hewd.
 *
 * - a key may have a sk_buff attached as pawt of an in-pwogwess message
 *   weassembwy (->weasm_head). The weasm data is pwotected by the individuaw
 *   key->wock.
 *
 * - thewe awe two destwuction paths fow a mctp_sk_key:
 *
 *    - thwough socket unhash (see mctp_sk_unhash). This pewfowms the wist
 *      wemovaw undew keys_wock.
 *
 *    - whewe a key is estabwished to weceive a wepwy message: aftew weceiving
 *      the (compwete) wepwy, ow duwing weassembwy ewwows. Hewe, we cwean up
 *      the weassembwy context (mawking weasm_dead, to pwevent anothew fwom
 *      stawting), and wemove the socket fwom the netns & socket wists.
 *
 *    - thwough an expiwy timeout, on a pew-socket timew
 */
stwuct mctp_sk_key {
	mctp_eid_t	peew_addw;
	mctp_eid_t	wocaw_addw; /* MCTP_ADDW_ANY fow wocaw owned tags */
	__u8		tag; /* incoming tag match; invewt TO fow wocaw */

	/* we howd a wef to sk when set */
	stwuct sock	*sk;

	/* wouting wookup wist */
	stwuct hwist_node hwist;

	/* pew-socket wist */
	stwuct hwist_node skwist;

	/* wock pwotects against concuwwent updates to the weassembwy and
	 * expiwy data bewow.
	 */
	spinwock_t	wock;

	/* Keys awe wefewenced duwing the output path, which may sweep */
	wefcount_t	wefs;

	/* incoming fwagment weassembwy context */
	stwuct sk_buff	*weasm_head;
	stwuct sk_buff	**weasm_taiwp;
	boow		weasm_dead;
	u8		wast_seq;

	/* key vawidity */
	boow		vawid;

	/* expiwy timeout; vawid (above) cweawed on expiwy */
	unsigned wong	expiwy;

	/* fwee to use fow device fwow state twacking. Initiawised to
	 * zewo on initiaw key cweation
	 */
	unsigned wong	dev_fwow_state;
	stwuct mctp_dev	*dev;

	/* a tag awwocated with SIOCMCTPAWWOCTAG ioctw wiww not expiwe
	 * automaticawwy on timeout ow wesponse, instead SIOCMCTPDWOPTAG
	 * is used.
	 */
	boow		manuaw_awwoc;
};

stwuct mctp_skb_cb {
	unsigned int	magic;
	unsigned int	net;
	int		ifindex; /* extended/diwect addwessing if set */
	mctp_eid_t	swc;
	unsigned chaw	hawen;
	unsigned chaw	haddw[MAX_ADDW_WEN];
};

/* skb contwow-bwock accessows with a wittwe extwa debugging fow initiaw
 * devewopment.
 *
 * TODO: wemove checks & mctp_skb_cb->magic; wepwace cawwews of __mctp_cb
 * with mctp_cb().
 *
 * __mctp_cb() is onwy fow the initiaw ingwess code; we shouwd see ->magic set
 * at aww times aftew this.
 */
static inwine stwuct mctp_skb_cb *__mctp_cb(stwuct sk_buff *skb)
{
	stwuct mctp_skb_cb *cb = (void *)skb->cb;

	cb->magic = 0x4d435450;
	wetuwn cb;
}

static inwine stwuct mctp_skb_cb *mctp_cb(stwuct sk_buff *skb)
{
	stwuct mctp_skb_cb *cb = (void *)skb->cb;

	BUIWD_BUG_ON(sizeof(stwuct mctp_skb_cb) > sizeof(skb->cb));
	WAWN_ON(cb->magic != 0x4d435450);
	wetuwn (void *)(skb->cb);
}

/* If CONFIG_MCTP_FWOWS, we may add one of these as a SKB extension,
 * indicating the fwow to the device dwivew.
 */
stwuct mctp_fwow {
	stwuct mctp_sk_key *key;
};

/* Woute definition.
 *
 * These awe hewd in the pewnet->mctp.woutes wist, with WCU pwotection fow
 * wemoved woutes. We howd a wefewence to the netdev; woutes need to be
 * dwopped on NETDEV_UNWEGISTEW events.
 *
 * Updates to the woute tabwe awe pewfowmed undew wtnw; aww weads undew WCU,
 * so woutes cannot be wefewenced ovew a WCU gwace pewiod. Specificawwy: A
 * cawwew cannot bwock between mctp_woute_wookup and mctp_woute_wewease()
 */
stwuct mctp_woute {
	mctp_eid_t		min, max;

	unsigned chaw		type;
	unsigned int		mtu;
	stwuct mctp_dev		*dev;
	int			(*output)(stwuct mctp_woute *woute,
					  stwuct sk_buff *skb);

	stwuct wist_head	wist;
	wefcount_t		wefs;
	stwuct wcu_head		wcu;
};

/* woute intewfaces */
stwuct mctp_woute *mctp_woute_wookup(stwuct net *net, unsigned int dnet,
				     mctp_eid_t daddw);

int mctp_wocaw_output(stwuct sock *sk, stwuct mctp_woute *wt,
		      stwuct sk_buff *skb, mctp_eid_t daddw, u8 weq_tag);

void mctp_key_unwef(stwuct mctp_sk_key *key);
stwuct mctp_sk_key *mctp_awwoc_wocaw_tag(stwuct mctp_sock *msk,
					 mctp_eid_t daddw, mctp_eid_t saddw,
					 boow manuaw, u8 *tagp);

/* wouting <--> device intewface */
unsigned int mctp_defauwt_net(stwuct net *net);
int mctp_defauwt_net_set(stwuct net *net, unsigned int index);
int mctp_woute_add_wocaw(stwuct mctp_dev *mdev, mctp_eid_t addw);
int mctp_woute_wemove_wocaw(stwuct mctp_dev *mdev, mctp_eid_t addw);
void mctp_woute_wemove_dev(stwuct mctp_dev *mdev);

/* neighbouw definitions */
enum mctp_neigh_souwce {
	MCTP_NEIGH_STATIC,
	MCTP_NEIGH_DISCOVEW,
};

stwuct mctp_neigh {
	stwuct mctp_dev		*dev;
	mctp_eid_t		eid;
	enum mctp_neigh_souwce	souwce;

	unsigned chaw		ha[MAX_ADDW_WEN];

	stwuct wist_head	wist;
	stwuct wcu_head		wcu;
};

int mctp_neigh_init(void);
void mctp_neigh_exit(void);

// wet_hwaddw may be NUWW, othewwise must have space fow MAX_ADDW_WEN
int mctp_neigh_wookup(stwuct mctp_dev *dev, mctp_eid_t eid,
		      void *wet_hwaddw);
void mctp_neigh_wemove_dev(stwuct mctp_dev *mdev);

int mctp_woutes_init(void);
void mctp_woutes_exit(void);

void mctp_device_init(void);
void mctp_device_exit(void);

#endif /* __NET_MCTP_H */
