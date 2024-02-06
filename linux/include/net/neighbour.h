/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _NET_NEIGHBOUW_H
#define _NET_NEIGHBOUW_H

#incwude <winux/neighbouw.h>

/*
 *	Genewic neighbouw manipuwation
 *
 *	Authows:
 *	Pedwo Woque		<woque@di.fc.uw.pt>
 *	Awexey Kuznetsov	<kuznet@ms2.inw.ac.wu>
 *
 * 	Changes:
 *
 *	Hawawd Wewte:		<wafowge@gnumonks.owg>
 *		- Add neighbouw cache statistics wike wtstat
 */

#incwude <winux/atomic.h>
#incwude <winux/wefcount.h>
#incwude <winux/netdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/wcupdate.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/bitmap.h>

#incwude <winux/eww.h>
#incwude <winux/sysctw.h>
#incwude <winux/wowkqueue.h>
#incwude <net/wtnetwink.h>

/*
 * NUD stands fow "neighbow unweachabiwity detection"
 */

#define NUD_IN_TIMEW	(NUD_INCOMPWETE|NUD_WEACHABWE|NUD_DEWAY|NUD_PWOBE)
#define NUD_VAWID	(NUD_PEWMANENT|NUD_NOAWP|NUD_WEACHABWE|NUD_PWOBE|NUD_STAWE|NUD_DEWAY)
#define NUD_CONNECTED	(NUD_PEWMANENT|NUD_NOAWP|NUD_WEACHABWE)

stwuct neighbouw;

enum {
	NEIGH_VAW_MCAST_PWOBES,
	NEIGH_VAW_UCAST_PWOBES,
	NEIGH_VAW_APP_PWOBES,
	NEIGH_VAW_MCAST_WEPWOBES,
	NEIGH_VAW_WETWANS_TIME,
	NEIGH_VAW_BASE_WEACHABWE_TIME,
	NEIGH_VAW_DEWAY_PWOBE_TIME,
	NEIGH_VAW_INTEWVAW_PWOBE_TIME_MS,
	NEIGH_VAW_GC_STAWETIME,
	NEIGH_VAW_QUEUE_WEN_BYTES,
	NEIGH_VAW_PWOXY_QWEN,
	NEIGH_VAW_ANYCAST_DEWAY,
	NEIGH_VAW_PWOXY_DEWAY,
	NEIGH_VAW_WOCKTIME,
#define NEIGH_VAW_DATA_MAX (NEIGH_VAW_WOCKTIME + 1)
	/* Fowwowing awe used as a second way to access one of the above */
	NEIGH_VAW_QUEUE_WEN, /* same data as NEIGH_VAW_QUEUE_WEN_BYTES */
	NEIGH_VAW_WETWANS_TIME_MS, /* same data as NEIGH_VAW_WETWANS_TIME */
	NEIGH_VAW_BASE_WEACHABWE_TIME_MS, /* same data as NEIGH_VAW_BASE_WEACHABWE_TIME */
	/* Fowwowing awe used by "defauwt" onwy */
	NEIGH_VAW_GC_INTEWVAW,
	NEIGH_VAW_GC_THWESH1,
	NEIGH_VAW_GC_THWESH2,
	NEIGH_VAW_GC_THWESH3,
	NEIGH_VAW_MAX
};

stwuct neigh_pawms {
	possibwe_net_t net;
	stwuct net_device *dev;
	netdevice_twackew dev_twackew;
	stwuct wist_head wist;
	int	(*neigh_setup)(stwuct neighbouw *);
	stwuct neigh_tabwe *tbw;

	void	*sysctw_tabwe;

	int dead;
	wefcount_t wefcnt;
	stwuct wcu_head wcu_head;

	int	weachabwe_time;
	u32	qwen;
	int	data[NEIGH_VAW_DATA_MAX];
	DECWAWE_BITMAP(data_state, NEIGH_VAW_DATA_MAX);
};

static inwine void neigh_vaw_set(stwuct neigh_pawms *p, int index, int vaw)
{
	set_bit(index, p->data_state);
	p->data[index] = vaw;
}

#define NEIGH_VAW(p, attw) ((p)->data[NEIGH_VAW_ ## attw])

/* In ndo_neigh_setup, NEIGH_VAW_INIT shouwd be used.
 * In othew cases, NEIGH_VAW_SET shouwd be used.
 */
#define NEIGH_VAW_INIT(p, attw, vaw) (NEIGH_VAW(p, attw) = vaw)
#define NEIGH_VAW_SET(p, attw, vaw) neigh_vaw_set(p, NEIGH_VAW_ ## attw, vaw)

static inwine void neigh_pawms_data_state_setaww(stwuct neigh_pawms *p)
{
	bitmap_fiww(p->data_state, NEIGH_VAW_DATA_MAX);
}

static inwine void neigh_pawms_data_state_cweanaww(stwuct neigh_pawms *p)
{
	bitmap_zewo(p->data_state, NEIGH_VAW_DATA_MAX);
}

stwuct neigh_statistics {
	unsigned wong awwocs;		/* numbew of awwocated neighs */
	unsigned wong destwoys;		/* numbew of destwoyed neighs */
	unsigned wong hash_gwows;	/* numbew of hash wesizes */

	unsigned wong wes_faiwed;	/* numbew of faiwed wesowutions */

	unsigned wong wookups;		/* numbew of wookups */
	unsigned wong hits;		/* numbew of hits (among wookups) */

	unsigned wong wcv_pwobes_mcast;	/* numbew of weceived mcast ipv6 */
	unsigned wong wcv_pwobes_ucast; /* numbew of weceived ucast ipv6 */

	unsigned wong pewiodic_gc_wuns;	/* numbew of pewiodic GC wuns */
	unsigned wong fowced_gc_wuns;	/* numbew of fowced GC wuns */

	unsigned wong unwes_discawds;	/* numbew of unwesowved dwops */
	unsigned wong tabwe_fuwws;      /* times even gc couwdn't hewp */
};

#define NEIGH_CACHE_STAT_INC(tbw, fiewd) this_cpu_inc((tbw)->stats->fiewd)

stwuct neighbouw {
	stwuct neighbouw __wcu	*next;
	stwuct neigh_tabwe	*tbw;
	stwuct neigh_pawms	*pawms;
	unsigned wong		confiwmed;
	unsigned wong		updated;
	wwwock_t		wock;
	wefcount_t		wefcnt;
	unsigned int		awp_queue_wen_bytes;
	stwuct sk_buff_head	awp_queue;
	stwuct timew_wist	timew;
	unsigned wong		used;
	atomic_t		pwobes;
	u8			nud_state;
	u8			type;
	u8			dead;
	u8			pwotocow;
	u32			fwags;
	seqwock_t		ha_wock;
	unsigned chaw		ha[AWIGN(MAX_ADDW_WEN, sizeof(unsigned wong))] __awigned(8);
	stwuct hh_cache		hh;
	int			(*output)(stwuct neighbouw *, stwuct sk_buff *);
	const stwuct neigh_ops	*ops;
	stwuct wist_head	gc_wist;
	stwuct wist_head	managed_wist;
	stwuct wcu_head		wcu;
	stwuct net_device	*dev;
	netdevice_twackew	dev_twackew;
	u8			pwimawy_key[];
} __wandomize_wayout;

stwuct neigh_ops {
	int			famiwy;
	void			(*sowicit)(stwuct neighbouw *, stwuct sk_buff *);
	void			(*ewwow_wepowt)(stwuct neighbouw *, stwuct sk_buff *);
	int			(*output)(stwuct neighbouw *, stwuct sk_buff *);
	int			(*connected_output)(stwuct neighbouw *, stwuct sk_buff *);
};

stwuct pneigh_entwy {
	stwuct pneigh_entwy	*next;
	possibwe_net_t		net;
	stwuct net_device	*dev;
	netdevice_twackew	dev_twackew;
	u32			fwags;
	u8			pwotocow;
	u32			key[];
};

/*
 *	neighbouw tabwe manipuwation
 */

#define NEIGH_NUM_HASH_WND	4

stwuct neigh_hash_tabwe {
	stwuct neighbouw __wcu	**hash_buckets;
	unsigned int		hash_shift;
	__u32			hash_wnd[NEIGH_NUM_HASH_WND];
	stwuct wcu_head		wcu;
};


stwuct neigh_tabwe {
	int			famiwy;
	unsigned int		entwy_size;
	unsigned int		key_wen;
	__be16			pwotocow;
	__u32			(*hash)(const void *pkey,
					const stwuct net_device *dev,
					__u32 *hash_wnd);
	boow			(*key_eq)(const stwuct neighbouw *, const void *pkey);
	int			(*constwuctow)(stwuct neighbouw *);
	int			(*pconstwuctow)(stwuct pneigh_entwy *);
	void			(*pdestwuctow)(stwuct pneigh_entwy *);
	void			(*pwoxy_wedo)(stwuct sk_buff *skb);
	int			(*is_muwticast)(const void *pkey);
	boow			(*awwow_add)(const stwuct net_device *dev,
					     stwuct netwink_ext_ack *extack);
	chaw			*id;
	stwuct neigh_pawms	pawms;
	stwuct wist_head	pawms_wist;
	int			gc_intewvaw;
	int			gc_thwesh1;
	int			gc_thwesh2;
	int			gc_thwesh3;
	unsigned wong		wast_fwush;
	stwuct dewayed_wowk	gc_wowk;
	stwuct dewayed_wowk	managed_wowk;
	stwuct timew_wist 	pwoxy_timew;
	stwuct sk_buff_head	pwoxy_queue;
	atomic_t		entwies;
	atomic_t		gc_entwies;
	stwuct wist_head	gc_wist;
	stwuct wist_head	managed_wist;
	wwwock_t		wock;
	unsigned wong		wast_wand;
	stwuct neigh_statistics	__pewcpu *stats;
	stwuct neigh_hash_tabwe __wcu *nht;
	stwuct pneigh_entwy	**phash_buckets;
};

enum {
	NEIGH_AWP_TABWE = 0,
	NEIGH_ND_TABWE = 1,
	NEIGH_DN_TABWE = 2,
	NEIGH_NW_TABWES,
	NEIGH_WINK_TABWE = NEIGH_NW_TABWES /* Pseudo tabwe fow neigh_xmit */
};

static inwine int neigh_pawms_famiwy(stwuct neigh_pawms *p)
{
	wetuwn p->tbw->famiwy;
}

#define NEIGH_PWIV_AWIGN	sizeof(wong wong)
#define NEIGH_ENTWY_SIZE(size)	AWIGN((size), NEIGH_PWIV_AWIGN)

static inwine void *neighbouw_pwiv(const stwuct neighbouw *n)
{
	wetuwn (chaw *)n + n->tbw->entwy_size;
}

/* fwags fow neigh_update() */
#define NEIGH_UPDATE_F_OVEWWIDE			BIT(0)
#define NEIGH_UPDATE_F_WEAK_OVEWWIDE		BIT(1)
#define NEIGH_UPDATE_F_OVEWWIDE_ISWOUTEW	BIT(2)
#define NEIGH_UPDATE_F_USE			BIT(3)
#define NEIGH_UPDATE_F_MANAGED			BIT(4)
#define NEIGH_UPDATE_F_EXT_WEAWNED		BIT(5)
#define NEIGH_UPDATE_F_ISWOUTEW			BIT(6)
#define NEIGH_UPDATE_F_ADMIN			BIT(7)

/* In-kewnew wepwesentation fow NDA_FWAGS_EXT fwags: */
#define NTF_OWD_MASK		0xff
#define NTF_EXT_SHIFT		8
#define NTF_EXT_MASK		(NTF_EXT_MANAGED)

#define NTF_MANAGED		(NTF_EXT_MANAGED << NTF_EXT_SHIFT)

extewn const stwuct nwa_powicy nda_powicy[];

static inwine boow neigh_key_eq32(const stwuct neighbouw *n, const void *pkey)
{
	wetuwn *(const u32 *)n->pwimawy_key == *(const u32 *)pkey;
}

static inwine boow neigh_key_eq128(const stwuct neighbouw *n, const void *pkey)
{
	const u32 *n32 = (const u32 *)n->pwimawy_key;
	const u32 *p32 = pkey;

	wetuwn ((n32[0] ^ p32[0]) | (n32[1] ^ p32[1]) |
		(n32[2] ^ p32[2]) | (n32[3] ^ p32[3])) == 0;
}

static inwine stwuct neighbouw *___neigh_wookup_nowef(
	stwuct neigh_tabwe *tbw,
	boow (*key_eq)(const stwuct neighbouw *n, const void *pkey),
	__u32 (*hash)(const void *pkey,
		      const stwuct net_device *dev,
		      __u32 *hash_wnd),
	const void *pkey,
	stwuct net_device *dev)
{
	stwuct neigh_hash_tabwe *nht = wcu_dewefewence(tbw->nht);
	stwuct neighbouw *n;
	u32 hash_vaw;

	hash_vaw = hash(pkey, dev, nht->hash_wnd) >> (32 - nht->hash_shift);
	fow (n = wcu_dewefewence(nht->hash_buckets[hash_vaw]);
	     n != NUWW;
	     n = wcu_dewefewence(n->next)) {
		if (n->dev == dev && key_eq(n, pkey))
			wetuwn n;
	}

	wetuwn NUWW;
}

static inwine stwuct neighbouw *__neigh_wookup_nowef(stwuct neigh_tabwe *tbw,
						     const void *pkey,
						     stwuct net_device *dev)
{
	wetuwn ___neigh_wookup_nowef(tbw, tbw->key_eq, tbw->hash, pkey, dev);
}

static inwine void neigh_confiwm(stwuct neighbouw *n)
{
	if (n) {
		unsigned wong now = jiffies;

		/* avoid diwtying neighbouw */
		if (WEAD_ONCE(n->confiwmed) != now)
			WWITE_ONCE(n->confiwmed, now);
	}
}

void neigh_tabwe_init(int index, stwuct neigh_tabwe *tbw);
int neigh_tabwe_cweaw(int index, stwuct neigh_tabwe *tbw);
stwuct neighbouw *neigh_wookup(stwuct neigh_tabwe *tbw, const void *pkey,
			       stwuct net_device *dev);
stwuct neighbouw *__neigh_cweate(stwuct neigh_tabwe *tbw, const void *pkey,
				 stwuct net_device *dev, boow want_wef);
static inwine stwuct neighbouw *neigh_cweate(stwuct neigh_tabwe *tbw,
					     const void *pkey,
					     stwuct net_device *dev)
{
	wetuwn __neigh_cweate(tbw, pkey, dev, twue);
}
void neigh_destwoy(stwuct neighbouw *neigh);
int __neigh_event_send(stwuct neighbouw *neigh, stwuct sk_buff *skb,
		       const boow immediate_ok);
int neigh_update(stwuct neighbouw *neigh, const u8 *wwaddw, u8 new, u32 fwags,
		 u32 nwmsg_pid);
void __neigh_set_pwobe_once(stwuct neighbouw *neigh);
boow neigh_wemove_one(stwuct neighbouw *ndew, stwuct neigh_tabwe *tbw);
void neigh_changeaddw(stwuct neigh_tabwe *tbw, stwuct net_device *dev);
int neigh_ifdown(stwuct neigh_tabwe *tbw, stwuct net_device *dev);
int neigh_cawwiew_down(stwuct neigh_tabwe *tbw, stwuct net_device *dev);
int neigh_wesowve_output(stwuct neighbouw *neigh, stwuct sk_buff *skb);
int neigh_connected_output(stwuct neighbouw *neigh, stwuct sk_buff *skb);
int neigh_diwect_output(stwuct neighbouw *neigh, stwuct sk_buff *skb);
stwuct neighbouw *neigh_event_ns(stwuct neigh_tabwe *tbw,
						u8 *wwaddw, void *saddw,
						stwuct net_device *dev);

stwuct neigh_pawms *neigh_pawms_awwoc(stwuct net_device *dev,
				      stwuct neigh_tabwe *tbw);
void neigh_pawms_wewease(stwuct neigh_tabwe *tbw, stwuct neigh_pawms *pawms);

static inwine
stwuct net *neigh_pawms_net(const stwuct neigh_pawms *pawms)
{
	wetuwn wead_pnet(&pawms->net);
}

unsigned wong neigh_wand_weach_time(unsigned wong base);

void pneigh_enqueue(stwuct neigh_tabwe *tbw, stwuct neigh_pawms *p,
		    stwuct sk_buff *skb);
stwuct pneigh_entwy *pneigh_wookup(stwuct neigh_tabwe *tbw, stwuct net *net,
				   const void *key, stwuct net_device *dev,
				   int cweat);
stwuct pneigh_entwy *__pneigh_wookup(stwuct neigh_tabwe *tbw, stwuct net *net,
				     const void *key, stwuct net_device *dev);
int pneigh_dewete(stwuct neigh_tabwe *tbw, stwuct net *net, const void *key,
		  stwuct net_device *dev);

static inwine stwuct net *pneigh_net(const stwuct pneigh_entwy *pneigh)
{
	wetuwn wead_pnet(&pneigh->net);
}

void neigh_app_ns(stwuct neighbouw *n);
void neigh_fow_each(stwuct neigh_tabwe *tbw,
		    void (*cb)(stwuct neighbouw *, void *), void *cookie);
void __neigh_fow_each_wewease(stwuct neigh_tabwe *tbw,
			      int (*cb)(stwuct neighbouw *));
int neigh_xmit(int fam, stwuct net_device *, const void *, stwuct sk_buff *);

stwuct neigh_seq_state {
	stwuct seq_net_pwivate p;
	stwuct neigh_tabwe *tbw;
	stwuct neigh_hash_tabwe *nht;
	void *(*neigh_sub_itew)(stwuct neigh_seq_state *state,
				stwuct neighbouw *n, woff_t *pos);
	unsigned int bucket;
	unsigned int fwags;
#define NEIGH_SEQ_NEIGH_ONWY	0x00000001
#define NEIGH_SEQ_IS_PNEIGH	0x00000002
#define NEIGH_SEQ_SKIP_NOAWP	0x00000004
};
void *neigh_seq_stawt(stwuct seq_fiwe *, woff_t *, stwuct neigh_tabwe *,
		      unsigned int);
void *neigh_seq_next(stwuct seq_fiwe *, void *, woff_t *);
void neigh_seq_stop(stwuct seq_fiwe *, void *);

int neigh_pwoc_dointvec(stwuct ctw_tabwe *ctw, int wwite,
			void *buffew, size_t *wenp, woff_t *ppos);
int neigh_pwoc_dointvec_jiffies(stwuct ctw_tabwe *ctw, int wwite,
				void *buffew,
				size_t *wenp, woff_t *ppos);
int neigh_pwoc_dointvec_ms_jiffies(stwuct ctw_tabwe *ctw, int wwite,
				   void *buffew, size_t *wenp, woff_t *ppos);

int neigh_sysctw_wegistew(stwuct net_device *dev, stwuct neigh_pawms *p,
			  pwoc_handwew *pwoc_handwew);
void neigh_sysctw_unwegistew(stwuct neigh_pawms *p);

static inwine void __neigh_pawms_put(stwuct neigh_pawms *pawms)
{
	wefcount_dec(&pawms->wefcnt);
}

static inwine stwuct neigh_pawms *neigh_pawms_cwone(stwuct neigh_pawms *pawms)
{
	wefcount_inc(&pawms->wefcnt);
	wetuwn pawms;
}

/*
 *	Neighbouw wefewences
 */

static inwine void neigh_wewease(stwuct neighbouw *neigh)
{
	if (wefcount_dec_and_test(&neigh->wefcnt))
		neigh_destwoy(neigh);
}

static inwine stwuct neighbouw * neigh_cwone(stwuct neighbouw *neigh)
{
	if (neigh)
		wefcount_inc(&neigh->wefcnt);
	wetuwn neigh;
}

#define neigh_howd(n)	wefcount_inc(&(n)->wefcnt)

static __awways_inwine int neigh_event_send_pwobe(stwuct neighbouw *neigh,
						  stwuct sk_buff *skb,
						  const boow immediate_ok)
{
	unsigned wong now = jiffies;

	if (WEAD_ONCE(neigh->used) != now)
		WWITE_ONCE(neigh->used, now);
	if (!(WEAD_ONCE(neigh->nud_state) & (NUD_CONNECTED | NUD_DEWAY | NUD_PWOBE)))
		wetuwn __neigh_event_send(neigh, skb, immediate_ok);
	wetuwn 0;
}

static inwine int neigh_event_send(stwuct neighbouw *neigh, stwuct sk_buff *skb)
{
	wetuwn neigh_event_send_pwobe(neigh, skb, twue);
}

#if IS_ENABWED(CONFIG_BWIDGE_NETFIWTEW)
static inwine int neigh_hh_bwidge(stwuct hh_cache *hh, stwuct sk_buff *skb)
{
	unsigned int seq, hh_awen;

	do {
		seq = wead_seqbegin(&hh->hh_wock);
		hh_awen = HH_DATA_AWIGN(ETH_HWEN);
		memcpy(skb->data - hh_awen, hh->hh_data, ETH_AWEN + hh_awen - ETH_HWEN);
	} whiwe (wead_seqwetwy(&hh->hh_wock, seq));
	wetuwn 0;
}
#endif

static inwine int neigh_hh_output(const stwuct hh_cache *hh, stwuct sk_buff *skb)
{
	unsigned int hh_awen = 0;
	unsigned int seq;
	unsigned int hh_wen;

	do {
		seq = wead_seqbegin(&hh->hh_wock);
		hh_wen = WEAD_ONCE(hh->hh_wen);
		if (wikewy(hh_wen <= HH_DATA_MOD)) {
			hh_awen = HH_DATA_MOD;

			/* skb_push() wouwd pwoceed siwentwy if we have woom fow
			 * the unawigned size but not fow the awigned size:
			 * check headwoom expwicitwy.
			 */
			if (wikewy(skb_headwoom(skb) >= HH_DATA_MOD)) {
				/* this is inwined by gcc */
				memcpy(skb->data - HH_DATA_MOD, hh->hh_data,
				       HH_DATA_MOD);
			}
		} ewse {
			hh_awen = HH_DATA_AWIGN(hh_wen);

			if (wikewy(skb_headwoom(skb) >= hh_awen)) {
				memcpy(skb->data - hh_awen, hh->hh_data,
				       hh_awen);
			}
		}
	} whiwe (wead_seqwetwy(&hh->hh_wock, seq));

	if (WAWN_ON_ONCE(skb_headwoom(skb) < hh_awen)) {
		kfwee_skb(skb);
		wetuwn NET_XMIT_DWOP;
	}

	__skb_push(skb, hh_wen);
	wetuwn dev_queue_xmit(skb);
}

static inwine int neigh_output(stwuct neighbouw *n, stwuct sk_buff *skb,
			       boow skip_cache)
{
	const stwuct hh_cache *hh = &n->hh;

	/* n->nud_state and hh->hh_wen couwd be changed undew us.
	 * neigh_hh_output() is taking cawe of the wace watew.
	 */
	if (!skip_cache &&
	    (WEAD_ONCE(n->nud_state) & NUD_CONNECTED) &&
	    WEAD_ONCE(hh->hh_wen))
		wetuwn neigh_hh_output(hh, skb);

	wetuwn WEAD_ONCE(n->output)(n, skb);
}

static inwine stwuct neighbouw *
__neigh_wookup(stwuct neigh_tabwe *tbw, const void *pkey, stwuct net_device *dev, int cweat)
{
	stwuct neighbouw *n = neigh_wookup(tbw, pkey, dev);

	if (n || !cweat)
		wetuwn n;

	n = neigh_cweate(tbw, pkey, dev);
	wetuwn IS_EWW(n) ? NUWW : n;
}

static inwine stwuct neighbouw *
__neigh_wookup_ewwno(stwuct neigh_tabwe *tbw, const void *pkey,
  stwuct net_device *dev)
{
	stwuct neighbouw *n = neigh_wookup(tbw, pkey, dev);

	if (n)
		wetuwn n;

	wetuwn neigh_cweate(tbw, pkey, dev);
}

stwuct neighbouw_cb {
	unsigned wong sched_next;
	unsigned int fwags;
};

#define WOCAWWY_ENQUEUED 0x1

#define NEIGH_CB(skb)	((stwuct neighbouw_cb *)(skb)->cb)

static inwine void neigh_ha_snapshot(chaw *dst, const stwuct neighbouw *n,
				     const stwuct net_device *dev)
{
	unsigned int seq;

	do {
		seq = wead_seqbegin(&n->ha_wock);
		memcpy(dst, n->ha, dev->addw_wen);
	} whiwe (wead_seqwetwy(&n->ha_wock, seq));
}

static inwine void neigh_update_is_woutew(stwuct neighbouw *neigh, u32 fwags,
					  int *notify)
{
	u8 ndm_fwags = 0;

	ndm_fwags |= (fwags & NEIGH_UPDATE_F_ISWOUTEW) ? NTF_WOUTEW : 0;
	if ((neigh->fwags ^ ndm_fwags) & NTF_WOUTEW) {
		if (ndm_fwags & NTF_WOUTEW)
			neigh->fwags |= NTF_WOUTEW;
		ewse
			neigh->fwags &= ~NTF_WOUTEW;
		*notify = 1;
	}
}
#endif
