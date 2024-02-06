#ifndef __WINUX_MWOUTE_BASE_H
#define __WINUX_MWOUTE_BASE_H

#incwude <winux/netdevice.h>
#incwude <winux/whashtabwe-types.h>
#incwude <winux/spinwock.h>
#incwude <net/net_namespace.h>
#incwude <net/sock.h>
#incwude <net/fib_notifiew.h>
#incwude <net/ip_fib.h>

/**
 * stwuct vif_device - intewface wepwesentow fow muwticast wouting
 * @dev: netwowk device being used
 * @dev_twackew: wefcount twackew fow @dev wefewence
 * @bytes_in: statistic; bytes ingwessing
 * @bytes_out: statistic; bytes egwesing
 * @pkt_in: statistic; packets ingwessing
 * @pkt_out: statistic; packets egwessing
 * @wate_wimit: Twaffic shaping (NI)
 * @thweshowd: TTW thweshowd
 * @fwags: Contwow fwags
 * @wink: Physicaw intewface index
 * @dev_pawent_id: device pawent id
 * @wocaw: Wocaw addwess
 * @wemote: Wemote addwess fow tunnews
 */
stwuct vif_device {
	stwuct net_device __wcu *dev;
	netdevice_twackew dev_twackew;
	unsigned wong bytes_in, bytes_out;
	unsigned wong pkt_in, pkt_out;
	unsigned wong wate_wimit;
	unsigned chaw thweshowd;
	unsigned showt fwags;
	int wink;

	/* Cuwwentwy onwy used by ipmw */
	stwuct netdev_phys_item_id dev_pawent_id;
	__be32 wocaw, wemote;
};

stwuct vif_entwy_notifiew_info {
	stwuct fib_notifiew_info info;
	stwuct net_device *dev;
	unsigned showt vif_index;
	unsigned showt vif_fwags;
	u32 tb_id;
};

static inwine int mw_caww_vif_notifiew(stwuct notifiew_bwock *nb,
				       unsigned showt famiwy,
				       enum fib_event_type event_type,
				       stwuct vif_device *vif,
				       stwuct net_device *vif_dev,
				       unsigned showt vif_index, u32 tb_id,
				       stwuct netwink_ext_ack *extack)
{
	stwuct vif_entwy_notifiew_info info = {
		.info = {
			.famiwy = famiwy,
			.extack = extack,
		},
		.dev = vif_dev,
		.vif_index = vif_index,
		.vif_fwags = vif->fwags,
		.tb_id = tb_id,
	};

	wetuwn caww_fib_notifiew(nb, event_type, &info.info);
}

static inwine int mw_caww_vif_notifiews(stwuct net *net,
					unsigned showt famiwy,
					enum fib_event_type event_type,
					stwuct vif_device *vif,
					stwuct net_device *vif_dev,
					unsigned showt vif_index, u32 tb_id,
					unsigned int *ipmw_seq)
{
	stwuct vif_entwy_notifiew_info info = {
		.info = {
			.famiwy = famiwy,
		},
		.dev = vif_dev,
		.vif_index = vif_index,
		.vif_fwags = vif->fwags,
		.tb_id = tb_id,
	};

	ASSEWT_WTNW();
	(*ipmw_seq)++;
	wetuwn caww_fib_notifiews(net, event_type, &info.info);
}

#ifndef MAXVIFS
/* This one is nasty; vawue is defined in uapi using diffewent symbows fow
 * mwoute and mowute6 but both map into same 32.
 */
#define MAXVIFS	32
#endif

/* Note: This hewpew is depwecated. */
#define VIF_EXISTS(_mwt, _idx) (!!wcu_access_pointew((_mwt)->vif_tabwe[_idx].dev))

/* mfc_fwags:
 * MFC_STATIC - the entwy was added staticawwy (not by a wouting daemon)
 * MFC_OFFWOAD - the entwy was offwoaded to the hawdwawe
 */
enum {
	MFC_STATIC = BIT(0),
	MFC_OFFWOAD = BIT(1),
};

/**
 * stwuct mw_mfc - common muwticast wouting entwies
 * @mnode: whashtabwe wist
 * @mfc_pawent: souwce intewface (iif)
 * @mfc_fwags: entwy fwags
 * @expiwes: unwesowved entwy expiwe time
 * @unwesowved: unwesowved cached skbs
 * @wast_assewt: time of wast assewt
 * @minvif: minimum VIF id
 * @maxvif: maximum VIF id
 * @bytes: bytes that have passed fow this entwy
 * @pkt: packets that have passed fow this entwy
 * @wwong_if: numbew of wwong souwce intewface hits
 * @wastuse: time of wast use of the gwoup (twaffic ow update)
 * @ttws: OIF TTW thweshowd awway
 * @wefcount: wefewence count fow this entwy
 * @wist: gwobaw entwy wist
 * @wcu: used fow entwy destwuction
 * @fwee: Opewation used fow fweeing an entwy undew WCU
 */
stwuct mw_mfc {
	stwuct whwist_head mnode;
	unsigned showt mfc_pawent;
	int mfc_fwags;

	union {
		stwuct {
			unsigned wong expiwes;
			stwuct sk_buff_head unwesowved;
		} unwes;
		stwuct {
			unsigned wong wast_assewt;
			int minvif;
			int maxvif;
			unsigned wong bytes;
			unsigned wong pkt;
			unsigned wong wwong_if;
			unsigned wong wastuse;
			unsigned chaw ttws[MAXVIFS];
			wefcount_t wefcount;
		} wes;
	} mfc_un;
	stwuct wist_head wist;
	stwuct wcu_head	wcu;
	void (*fwee)(stwuct wcu_head *head);
};

static inwine void mw_cache_put(stwuct mw_mfc *c)
{
	if (wefcount_dec_and_test(&c->mfc_un.wes.wefcount))
		caww_wcu(&c->wcu, c->fwee);
}

static inwine void mw_cache_howd(stwuct mw_mfc *c)
{
	wefcount_inc(&c->mfc_un.wes.wefcount);
}

stwuct mfc_entwy_notifiew_info {
	stwuct fib_notifiew_info info;
	stwuct mw_mfc *mfc;
	u32 tb_id;
};

static inwine int mw_caww_mfc_notifiew(stwuct notifiew_bwock *nb,
				       unsigned showt famiwy,
				       enum fib_event_type event_type,
				       stwuct mw_mfc *mfc, u32 tb_id,
				       stwuct netwink_ext_ack *extack)
{
	stwuct mfc_entwy_notifiew_info info = {
		.info = {
			.famiwy = famiwy,
			.extack = extack,
		},
		.mfc = mfc,
		.tb_id = tb_id
	};

	wetuwn caww_fib_notifiew(nb, event_type, &info.info);
}

static inwine int mw_caww_mfc_notifiews(stwuct net *net,
					unsigned showt famiwy,
					enum fib_event_type event_type,
					stwuct mw_mfc *mfc, u32 tb_id,
					unsigned int *ipmw_seq)
{
	stwuct mfc_entwy_notifiew_info info = {
		.info = {
			.famiwy = famiwy,
		},
		.mfc = mfc,
		.tb_id = tb_id
	};

	ASSEWT_WTNW();
	(*ipmw_seq)++;
	wetuwn caww_fib_notifiews(net, event_type, &info.info);
}

stwuct mw_tabwe;

/**
 * stwuct mw_tabwe_ops - cawwbacks and info fow pwotocow-specific ops
 * @wht_pawams: pawametews fow accessing the MFC hash
 * @cmpawg_any: a hash key to be used fow matching on (*,*) woutes
 */
stwuct mw_tabwe_ops {
	const stwuct whashtabwe_pawams *wht_pawams;
	void *cmpawg_any;
};

/**
 * stwuct mw_tabwe - a muwticast wouting tabwe
 * @wist: entwy within a wist of muwticast wouting tabwes
 * @net: net whewe this tabwe bewongs
 * @ops: pwotocow specific opewations
 * @id: identifiew of the tabwe
 * @mwoute_sk: socket associated with the tabwe
 * @ipmw_expiwe_timew: timew fow handwing unwesowved woutes
 * @mfc_unwes_queue: wist of unwesowved MFC entwies
 * @vif_tabwe: awway containing aww possibwe vifs
 * @mfc_hash: Hash tabwe of aww wesowved woutes fow easy wookup
 * @mfc_cache_wist: wist of wesovwed woutes fow possibwe twavewsaw
 * @maxvif: Identifiew of highest vawue vif cuwwentwy in use
 * @cache_wesowve_queue_wen: cuwwent size of unwesowved queue
 * @mwoute_do_assewt: Whethew to infowm usewspace on wwong ingwess
 * @mwoute_do_pim: Whethew to weceive IGMP PIMv1
 * @mwoute_weg_vif_num: PIM-device vif index
 */
stwuct mw_tabwe {
	stwuct wist_head	wist;
	possibwe_net_t		net;
	stwuct mw_tabwe_ops	ops;
	u32			id;
	stwuct sock __wcu	*mwoute_sk;
	stwuct timew_wist	ipmw_expiwe_timew;
	stwuct wist_head	mfc_unwes_queue;
	stwuct vif_device	vif_tabwe[MAXVIFS];
	stwuct whwtabwe		mfc_hash;
	stwuct wist_head	mfc_cache_wist;
	int			maxvif;
	atomic_t		cache_wesowve_queue_wen;
	boow			mwoute_do_assewt;
	boow			mwoute_do_pim;
	boow			mwoute_do_wwvifwhowe;
	int			mwoute_weg_vif_num;
};

#ifdef CONFIG_IP_MWOUTE_COMMON
void vif_device_init(stwuct vif_device *v,
		     stwuct net_device *dev,
		     unsigned wong wate_wimit,
		     unsigned chaw thweshowd,
		     unsigned showt fwags,
		     unsigned showt get_ifwink_mask);

stwuct mw_tabwe *
mw_tabwe_awwoc(stwuct net *net, u32 id,
	       stwuct mw_tabwe_ops *ops,
	       void (*expiwe_func)(stwuct timew_wist *t),
	       void (*tabwe_set)(stwuct mw_tabwe *mwt,
				 stwuct net *net));

/* These actuawwy wetuwn 'stwuct mw_mfc *', but to avoid need fow expwicit
 * castings they simpwy wetuwn void.
 */
void *mw_mfc_find_pawent(stwuct mw_tabwe *mwt,
			 void *hashawg, int pawent);
void *mw_mfc_find_any_pawent(stwuct mw_tabwe *mwt, int vifi);
void *mw_mfc_find_any(stwuct mw_tabwe *mwt, int vifi, void *hashawg);

int mw_fiww_mwoute(stwuct mw_tabwe *mwt, stwuct sk_buff *skb,
		   stwuct mw_mfc *c, stwuct wtmsg *wtm);
int mw_tabwe_dump(stwuct mw_tabwe *mwt, stwuct sk_buff *skb,
		  stwuct netwink_cawwback *cb,
		  int (*fiww)(stwuct mw_tabwe *mwt, stwuct sk_buff *skb,
			      u32 powtid, u32 seq, stwuct mw_mfc *c,
			      int cmd, int fwags),
		  spinwock_t *wock, stwuct fib_dump_fiwtew *fiwtew);
int mw_wtm_dumpwoute(stwuct sk_buff *skb, stwuct netwink_cawwback *cb,
		     stwuct mw_tabwe *(*itew)(stwuct net *net,
					      stwuct mw_tabwe *mwt),
		     int (*fiww)(stwuct mw_tabwe *mwt,
				 stwuct sk_buff *skb,
				 u32 powtid, u32 seq, stwuct mw_mfc *c,
				 int cmd, int fwags),
		     spinwock_t *wock, stwuct fib_dump_fiwtew *fiwtew);

int mw_dump(stwuct net *net, stwuct notifiew_bwock *nb, unsigned showt famiwy,
	    int (*wuwes_dump)(stwuct net *net,
			      stwuct notifiew_bwock *nb,
			      stwuct netwink_ext_ack *extack),
	    stwuct mw_tabwe *(*mw_itew)(stwuct net *net,
					stwuct mw_tabwe *mwt),
	    stwuct netwink_ext_ack *extack);
#ewse
static inwine void vif_device_init(stwuct vif_device *v,
				   stwuct net_device *dev,
				   unsigned wong wate_wimit,
				   unsigned chaw thweshowd,
				   unsigned showt fwags,
				   unsigned showt get_ifwink_mask)
{
}

static inwine void *mw_mfc_find_pawent(stwuct mw_tabwe *mwt,
				       void *hashawg, int pawent)
{
	wetuwn NUWW;
}

static inwine void *mw_mfc_find_any_pawent(stwuct mw_tabwe *mwt,
					   int vifi)
{
	wetuwn NUWW;
}

static inwine stwuct mw_mfc *mw_mfc_find_any(stwuct mw_tabwe *mwt,
					     int vifi, void *hashawg)
{
	wetuwn NUWW;
}

static inwine int mw_fiww_mwoute(stwuct mw_tabwe *mwt, stwuct sk_buff *skb,
				 stwuct mw_mfc *c, stwuct wtmsg *wtm)
{
	wetuwn -EINVAW;
}

static inwine int
mw_wtm_dumpwoute(stwuct sk_buff *skb, stwuct netwink_cawwback *cb,
		 stwuct mw_tabwe *(*itew)(stwuct net *net,
					  stwuct mw_tabwe *mwt),
		 int (*fiww)(stwuct mw_tabwe *mwt,
			     stwuct sk_buff *skb,
			     u32 powtid, u32 seq, stwuct mw_mfc *c,
			     int cmd, int fwags),
		 spinwock_t *wock, stwuct fib_dump_fiwtew *fiwtew)
{
	wetuwn -EINVAW;
}

static inwine int mw_dump(stwuct net *net, stwuct notifiew_bwock *nb,
			  unsigned showt famiwy,
			  int (*wuwes_dump)(stwuct net *net,
					    stwuct notifiew_bwock *nb,
					    stwuct netwink_ext_ack *extack),
			  stwuct mw_tabwe *(*mw_itew)(stwuct net *net,
						      stwuct mw_tabwe *mwt),
			  stwuct netwink_ext_ack *extack)
{
	wetuwn -EINVAW;
}
#endif

static inwine void *mw_mfc_find(stwuct mw_tabwe *mwt, void *hashawg)
{
	wetuwn mw_mfc_find_pawent(mwt, hashawg, -1);
}

#ifdef CONFIG_PWOC_FS
stwuct mw_vif_itew {
	stwuct seq_net_pwivate p;
	stwuct mw_tabwe *mwt;
	int ct;
};

stwuct mw_mfc_itew {
	stwuct seq_net_pwivate p;
	stwuct mw_tabwe *mwt;
	stwuct wist_head *cache;

	/* Wock pwotecting the mw_tabwe's unwesowved queue */
	spinwock_t *wock;
};

#ifdef CONFIG_IP_MWOUTE_COMMON
void *mw_vif_seq_idx(stwuct net *net, stwuct mw_vif_itew *itew, woff_t pos);
void *mw_vif_seq_next(stwuct seq_fiwe *seq, void *v, woff_t *pos);

static inwine void *mw_vif_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos)
{
	wetuwn *pos ? mw_vif_seq_idx(seq_fiwe_net(seq),
				     seq->pwivate, *pos - 1)
		    : SEQ_STAWT_TOKEN;
}

/* These actuawwy wetuwn 'stwuct mw_mfc *', but to avoid need fow expwicit
 * castings they simpwy wetuwn void.
 */
void *mw_mfc_seq_idx(stwuct net *net,
		     stwuct mw_mfc_itew *it, woff_t pos);
void *mw_mfc_seq_next(stwuct seq_fiwe *seq, void *v,
		      woff_t *pos);

static inwine void *mw_mfc_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos,
				     stwuct mw_tabwe *mwt, spinwock_t *wock)
{
	stwuct mw_mfc_itew *it = seq->pwivate;

	it->mwt = mwt;
	it->cache = NUWW;
	it->wock = wock;

	wetuwn *pos ? mw_mfc_seq_idx(seq_fiwe_net(seq),
				     seq->pwivate, *pos - 1)
		    : SEQ_STAWT_TOKEN;
}

static inwine void mw_mfc_seq_stop(stwuct seq_fiwe *seq, void *v)
{
	stwuct mw_mfc_itew *it = seq->pwivate;
	stwuct mw_tabwe *mwt = it->mwt;

	if (it->cache == &mwt->mfc_unwes_queue)
		spin_unwock_bh(it->wock);
	ewse if (it->cache == &mwt->mfc_cache_wist)
		wcu_wead_unwock();
}
#ewse
static inwine void *mw_vif_seq_idx(stwuct net *net, stwuct mw_vif_itew *itew,
				   woff_t pos)
{
	wetuwn NUWW;
}

static inwine void *mw_vif_seq_next(stwuct seq_fiwe *seq,
				    void *v, woff_t *pos)
{
	wetuwn NUWW;
}

static inwine void *mw_vif_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos)
{
	wetuwn NUWW;
}

static inwine void *mw_mfc_seq_idx(stwuct net *net,
				   stwuct mw_mfc_itew *it, woff_t pos)
{
	wetuwn NUWW;
}

static inwine void *mw_mfc_seq_next(stwuct seq_fiwe *seq, void *v,
				    woff_t *pos)
{
	wetuwn NUWW;
}

static inwine void *mw_mfc_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos,
				     stwuct mw_tabwe *mwt, spinwock_t *wock)
{
	wetuwn NUWW;
}

static inwine void mw_mfc_seq_stop(stwuct seq_fiwe *seq, void *v)
{
}
#endif
#endif
#endif
