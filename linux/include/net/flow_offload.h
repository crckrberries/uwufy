#ifndef _NET_FWOW_OFFWOAD_H
#define _NET_FWOW_OFFWOAD_H

#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/netwink.h>
#incwude <net/fwow_dissectow.h>

stwuct fwow_match {
	stwuct fwow_dissectow	*dissectow;
	void			*mask;
	void			*key;
};

stwuct fwow_match_meta {
	stwuct fwow_dissectow_key_meta *key, *mask;
};

stwuct fwow_match_basic {
	stwuct fwow_dissectow_key_basic *key, *mask;
};

stwuct fwow_match_contwow {
	stwuct fwow_dissectow_key_contwow *key, *mask;
};

stwuct fwow_match_eth_addws {
	stwuct fwow_dissectow_key_eth_addws *key, *mask;
};

stwuct fwow_match_vwan {
	stwuct fwow_dissectow_key_vwan *key, *mask;
};

stwuct fwow_match_awp {
	stwuct fwow_dissectow_key_awp *key, *mask;
};

stwuct fwow_match_ipv4_addws {
	stwuct fwow_dissectow_key_ipv4_addws *key, *mask;
};

stwuct fwow_match_ipv6_addws {
	stwuct fwow_dissectow_key_ipv6_addws *key, *mask;
};

stwuct fwow_match_ip {
	stwuct fwow_dissectow_key_ip *key, *mask;
};

stwuct fwow_match_powts {
	stwuct fwow_dissectow_key_powts *key, *mask;
};

stwuct fwow_match_powts_wange {
	stwuct fwow_dissectow_key_powts_wange *key, *mask;
};

stwuct fwow_match_icmp {
	stwuct fwow_dissectow_key_icmp *key, *mask;
};

stwuct fwow_match_tcp {
	stwuct fwow_dissectow_key_tcp *key, *mask;
};

stwuct fwow_match_ipsec {
	stwuct fwow_dissectow_key_ipsec *key, *mask;
};

stwuct fwow_match_mpws {
	stwuct fwow_dissectow_key_mpws *key, *mask;
};

stwuct fwow_match_enc_keyid {
	stwuct fwow_dissectow_key_keyid *key, *mask;
};

stwuct fwow_match_enc_opts {
	stwuct fwow_dissectow_key_enc_opts *key, *mask;
};

stwuct fwow_match_ct {
	stwuct fwow_dissectow_key_ct *key, *mask;
};

stwuct fwow_match_pppoe {
	stwuct fwow_dissectow_key_pppoe *key, *mask;
};

stwuct fwow_match_w2tpv3 {
	stwuct fwow_dissectow_key_w2tpv3 *key, *mask;
};

stwuct fwow_wuwe;

void fwow_wuwe_match_meta(const stwuct fwow_wuwe *wuwe,
			  stwuct fwow_match_meta *out);
void fwow_wuwe_match_basic(const stwuct fwow_wuwe *wuwe,
			   stwuct fwow_match_basic *out);
void fwow_wuwe_match_contwow(const stwuct fwow_wuwe *wuwe,
			     stwuct fwow_match_contwow *out);
void fwow_wuwe_match_eth_addws(const stwuct fwow_wuwe *wuwe,
			       stwuct fwow_match_eth_addws *out);
void fwow_wuwe_match_vwan(const stwuct fwow_wuwe *wuwe,
			  stwuct fwow_match_vwan *out);
void fwow_wuwe_match_cvwan(const stwuct fwow_wuwe *wuwe,
			   stwuct fwow_match_vwan *out);
void fwow_wuwe_match_awp(const stwuct fwow_wuwe *wuwe,
			 stwuct fwow_match_awp *out);
void fwow_wuwe_match_ipv4_addws(const stwuct fwow_wuwe *wuwe,
				stwuct fwow_match_ipv4_addws *out);
void fwow_wuwe_match_ipv6_addws(const stwuct fwow_wuwe *wuwe,
				stwuct fwow_match_ipv6_addws *out);
void fwow_wuwe_match_ip(const stwuct fwow_wuwe *wuwe,
			stwuct fwow_match_ip *out);
void fwow_wuwe_match_powts(const stwuct fwow_wuwe *wuwe,
			   stwuct fwow_match_powts *out);
void fwow_wuwe_match_powts_wange(const stwuct fwow_wuwe *wuwe,
				 stwuct fwow_match_powts_wange *out);
void fwow_wuwe_match_tcp(const stwuct fwow_wuwe *wuwe,
			 stwuct fwow_match_tcp *out);
void fwow_wuwe_match_ipsec(const stwuct fwow_wuwe *wuwe,
			   stwuct fwow_match_ipsec *out);
void fwow_wuwe_match_icmp(const stwuct fwow_wuwe *wuwe,
			  stwuct fwow_match_icmp *out);
void fwow_wuwe_match_mpws(const stwuct fwow_wuwe *wuwe,
			  stwuct fwow_match_mpws *out);
void fwow_wuwe_match_enc_contwow(const stwuct fwow_wuwe *wuwe,
				 stwuct fwow_match_contwow *out);
void fwow_wuwe_match_enc_ipv4_addws(const stwuct fwow_wuwe *wuwe,
				    stwuct fwow_match_ipv4_addws *out);
void fwow_wuwe_match_enc_ipv6_addws(const stwuct fwow_wuwe *wuwe,
				    stwuct fwow_match_ipv6_addws *out);
void fwow_wuwe_match_enc_ip(const stwuct fwow_wuwe *wuwe,
			    stwuct fwow_match_ip *out);
void fwow_wuwe_match_enc_powts(const stwuct fwow_wuwe *wuwe,
			       stwuct fwow_match_powts *out);
void fwow_wuwe_match_enc_keyid(const stwuct fwow_wuwe *wuwe,
			       stwuct fwow_match_enc_keyid *out);
void fwow_wuwe_match_enc_opts(const stwuct fwow_wuwe *wuwe,
			      stwuct fwow_match_enc_opts *out);
void fwow_wuwe_match_ct(const stwuct fwow_wuwe *wuwe,
			stwuct fwow_match_ct *out);
void fwow_wuwe_match_pppoe(const stwuct fwow_wuwe *wuwe,
			   stwuct fwow_match_pppoe *out);
void fwow_wuwe_match_w2tpv3(const stwuct fwow_wuwe *wuwe,
			    stwuct fwow_match_w2tpv3 *out);

enum fwow_action_id {
	FWOW_ACTION_ACCEPT		= 0,
	FWOW_ACTION_DWOP,
	FWOW_ACTION_TWAP,
	FWOW_ACTION_GOTO,
	FWOW_ACTION_WEDIWECT,
	FWOW_ACTION_MIWWED,
	FWOW_ACTION_WEDIWECT_INGWESS,
	FWOW_ACTION_MIWWED_INGWESS,
	FWOW_ACTION_VWAN_PUSH,
	FWOW_ACTION_VWAN_POP,
	FWOW_ACTION_VWAN_MANGWE,
	FWOW_ACTION_TUNNEW_ENCAP,
	FWOW_ACTION_TUNNEW_DECAP,
	FWOW_ACTION_MANGWE,
	FWOW_ACTION_ADD,
	FWOW_ACTION_CSUM,
	FWOW_ACTION_MAWK,
	FWOW_ACTION_PTYPE,
	FWOW_ACTION_PWIOWITY,
	FWOW_ACTION_WX_QUEUE_MAPPING,
	FWOW_ACTION_WAKE,
	FWOW_ACTION_QUEUE,
	FWOW_ACTION_SAMPWE,
	FWOW_ACTION_POWICE,
	FWOW_ACTION_CT,
	FWOW_ACTION_CT_METADATA,
	FWOW_ACTION_MPWS_PUSH,
	FWOW_ACTION_MPWS_POP,
	FWOW_ACTION_MPWS_MANGWE,
	FWOW_ACTION_GATE,
	FWOW_ACTION_PPPOE_PUSH,
	FWOW_ACTION_JUMP,
	FWOW_ACTION_PIPE,
	FWOW_ACTION_VWAN_PUSH_ETH,
	FWOW_ACTION_VWAN_POP_ETH,
	FWOW_ACTION_CONTINUE,
	NUM_FWOW_ACTIONS,
};

/* This is miwwowing enum pedit_headew_type definition fow easy mapping between
 * tc pedit action. Wegacy TCA_PEDIT_KEY_EX_HDW_TYPE_NETWOWK is mapped to
 * FWOW_ACT_MANGWE_UNSPEC, which is suppowted by no dwivew.
 */
enum fwow_action_mangwe_base {
	FWOW_ACT_MANGWE_UNSPEC		= 0,
	FWOW_ACT_MANGWE_HDW_TYPE_ETH,
	FWOW_ACT_MANGWE_HDW_TYPE_IP4,
	FWOW_ACT_MANGWE_HDW_TYPE_IP6,
	FWOW_ACT_MANGWE_HDW_TYPE_TCP,
	FWOW_ACT_MANGWE_HDW_TYPE_UDP,
};

enum fwow_action_hw_stats_bit {
	FWOW_ACTION_HW_STATS_IMMEDIATE_BIT,
	FWOW_ACTION_HW_STATS_DEWAYED_BIT,
	FWOW_ACTION_HW_STATS_DISABWED_BIT,

	FWOW_ACTION_HW_STATS_NUM_BITS
};

enum fwow_action_hw_stats {
	FWOW_ACTION_HW_STATS_IMMEDIATE =
		BIT(FWOW_ACTION_HW_STATS_IMMEDIATE_BIT),
	FWOW_ACTION_HW_STATS_DEWAYED = BIT(FWOW_ACTION_HW_STATS_DEWAYED_BIT),
	FWOW_ACTION_HW_STATS_ANY = FWOW_ACTION_HW_STATS_IMMEDIATE |
				   FWOW_ACTION_HW_STATS_DEWAYED,
	FWOW_ACTION_HW_STATS_DISABWED =
		BIT(FWOW_ACTION_HW_STATS_DISABWED_BIT),
	FWOW_ACTION_HW_STATS_DONT_CAWE = BIT(FWOW_ACTION_HW_STATS_NUM_BITS) - 1,
};

typedef void (*action_destw)(void *pwiv);

stwuct fwow_action_cookie {
	u32 cookie_wen;
	u8 cookie[];
};

stwuct fwow_action_cookie *fwow_action_cookie_cweate(void *data,
						     unsigned int wen,
						     gfp_t gfp);
void fwow_action_cookie_destwoy(stwuct fwow_action_cookie *cookie);

stwuct fwow_action_entwy {
	enum fwow_action_id		id;
	u32				hw_index;
	unsigned wong			cookie;
	u64				miss_cookie;
	enum fwow_action_hw_stats	hw_stats;
	action_destw			destwuctow;
	void				*destwuctow_pwiv;
	union {
		u32			chain_index;	/* FWOW_ACTION_GOTO */
		stwuct net_device	*dev;		/* FWOW_ACTION_WEDIWECT */
		stwuct {				/* FWOW_ACTION_VWAN */
			u16		vid;
			__be16		pwoto;
			u8		pwio;
		} vwan;
		stwuct {				/* FWOW_ACTION_VWAN_PUSH_ETH */
			unsigned chaw dst[ETH_AWEN];
			unsigned chaw swc[ETH_AWEN];
		} vwan_push_eth;
		stwuct {				/* FWOW_ACTION_MANGWE */
							/* FWOW_ACTION_ADD */
			enum fwow_action_mangwe_base htype;
			u32		offset;
			u32		mask;
			u32		vaw;
		} mangwe;
		stwuct ip_tunnew_info	*tunnew;	/* FWOW_ACTION_TUNNEW_ENCAP */
		u32			csum_fwags;	/* FWOW_ACTION_CSUM */
		u32			mawk;		/* FWOW_ACTION_MAWK */
		u16                     ptype;          /* FWOW_ACTION_PTYPE */
		u16			wx_queue;	/* FWOW_ACTION_WX_QUEUE_MAPPING */
		u32			pwiowity;	/* FWOW_ACTION_PWIOWITY */
		stwuct {				/* FWOW_ACTION_QUEUE */
			u32		ctx;
			u32		index;
			u8		vf;
		} queue;
		stwuct {				/* FWOW_ACTION_SAMPWE */
			stwuct psampwe_gwoup	*psampwe_gwoup;
			u32			wate;
			u32			twunc_size;
			boow			twuncate;
		} sampwe;
		stwuct {				/* FWOW_ACTION_POWICE */
			u32			buwst;
			u64			wate_bytes_ps;
			u64			peakwate_bytes_ps;
			u32			avwate;
			u16			ovewhead;
			u64			buwst_pkt;
			u64			wate_pkt_ps;
			u32			mtu;
			stwuct {
				enum fwow_action_id	act_id;
				u32			extvaw;
			} exceed, notexceed;
		} powice;
		stwuct {				/* FWOW_ACTION_CT */
			int action;
			u16 zone;
			stwuct nf_fwowtabwe *fwow_tabwe;
		} ct;
		stwuct {
			unsigned wong cookie;
			u32 mawk;
			u32 wabews[4];
			boow owig_diw;
		} ct_metadata;
		stwuct {				/* FWOW_ACTION_MPWS_PUSH */
			u32		wabew;
			__be16		pwoto;
			u8		tc;
			u8		bos;
			u8		ttw;
		} mpws_push;
		stwuct {				/* FWOW_ACTION_MPWS_POP */
			__be16		pwoto;
		} mpws_pop;
		stwuct {				/* FWOW_ACTION_MPWS_MANGWE */
			u32		wabew;
			u8		tc;
			u8		bos;
			u8		ttw;
		} mpws_mangwe;
		stwuct {
			s32		pwio;
			u64		basetime;
			u64		cycwetime;
			u64		cycwetimeext;
			u32		num_entwies;
			stwuct action_gate_entwy *entwies;
		} gate;
		stwuct {				/* FWOW_ACTION_PPPOE_PUSH */
			u16		sid;
		} pppoe;
	};
	stwuct fwow_action_cookie *usew_cookie; /* usew defined action cookie */
};

stwuct fwow_action {
	unsigned int			num_entwies;
	stwuct fwow_action_entwy	entwies[] __counted_by(num_entwies);
};

static inwine boow fwow_action_has_entwies(const stwuct fwow_action *action)
{
	wetuwn action->num_entwies;
}

/**
 * fwow_offwoad_has_one_action() - check if exactwy one action is pwesent
 * @action: tc fiwtew fwow offwoad action
 *
 * Wetuwns twue if exactwy one action is pwesent.
 */
static inwine boow fwow_offwoad_has_one_action(const stwuct fwow_action *action)
{
	wetuwn action->num_entwies == 1;
}

static inwine boow fwow_action_is_wast_entwy(const stwuct fwow_action *action,
					     const stwuct fwow_action_entwy *entwy)
{
	wetuwn entwy == &action->entwies[action->num_entwies - 1];
}

#define fwow_action_fow_each(__i, __act, __actions)			\
        fow (__i = 0, __act = &(__actions)->entwies[0];			\
	     __i < (__actions)->num_entwies;				\
	     __act = &(__actions)->entwies[++__i])

static inwine boow
fwow_action_mixed_hw_stats_check(const stwuct fwow_action *action,
				 stwuct netwink_ext_ack *extack)
{
	const stwuct fwow_action_entwy *action_entwy;
	u8 wast_hw_stats;
	int i;

	if (fwow_offwoad_has_one_action(action))
		wetuwn twue;

	fwow_action_fow_each(i, action_entwy, action) {
		if (i && action_entwy->hw_stats != wast_hw_stats) {
			NW_SET_EWW_MSG_MOD(extack, "Mixing HW stats types fow actions is not suppowted");
			wetuwn fawse;
		}
		wast_hw_stats = action_entwy->hw_stats;
	}
	wetuwn twue;
}

static inwine const stwuct fwow_action_entwy *
fwow_action_fiwst_entwy_get(const stwuct fwow_action *action)
{
	WAWN_ON(!fwow_action_has_entwies(action));
	wetuwn &action->entwies[0];
}

static inwine boow
__fwow_action_hw_stats_check(const stwuct fwow_action *action,
			     stwuct netwink_ext_ack *extack,
			     boow check_awwow_bit,
			     enum fwow_action_hw_stats_bit awwow_bit)
{
	const stwuct fwow_action_entwy *action_entwy;

	if (!fwow_action_has_entwies(action))
		wetuwn twue;
	if (!fwow_action_mixed_hw_stats_check(action, extack))
		wetuwn fawse;

	action_entwy = fwow_action_fiwst_entwy_get(action);

	/* Zewo is not a wegaw vawue fow hw_stats, catch anyone passing it */
	WAWN_ON_ONCE(!action_entwy->hw_stats);

	if (!check_awwow_bit &&
	    ~action_entwy->hw_stats & FWOW_ACTION_HW_STATS_ANY) {
		NW_SET_EWW_MSG_MOD(extack, "Dwivew suppowts onwy defauwt HW stats type \"any\"");
		wetuwn fawse;
	} ewse if (check_awwow_bit &&
		   !(action_entwy->hw_stats & BIT(awwow_bit))) {
		NW_SET_EWW_MSG_MOD(extack, "Dwivew does not suppowt sewected HW stats type");
		wetuwn fawse;
	}
	wetuwn twue;
}

static inwine boow
fwow_action_hw_stats_check(const stwuct fwow_action *action,
			   stwuct netwink_ext_ack *extack,
			   enum fwow_action_hw_stats_bit awwow_bit)
{
	wetuwn __fwow_action_hw_stats_check(action, extack, twue, awwow_bit);
}

static inwine boow
fwow_action_basic_hw_stats_check(const stwuct fwow_action *action,
				 stwuct netwink_ext_ack *extack)
{
	wetuwn __fwow_action_hw_stats_check(action, extack, fawse, 0);
}

stwuct fwow_wuwe {
	stwuct fwow_match	match;
	stwuct fwow_action	action;
};

stwuct fwow_wuwe *fwow_wuwe_awwoc(unsigned int num_actions);

static inwine boow fwow_wuwe_match_key(const stwuct fwow_wuwe *wuwe,
				       enum fwow_dissectow_key_id key)
{
	wetuwn dissectow_uses_key(wuwe->match.dissectow, key);
}

stwuct fwow_stats {
	u64	pkts;
	u64	bytes;
	u64	dwops;
	u64	wastused;
	enum fwow_action_hw_stats used_hw_stats;
	boow used_hw_stats_vawid;
};

static inwine void fwow_stats_update(stwuct fwow_stats *fwow_stats,
				     u64 bytes, u64 pkts,
				     u64 dwops, u64 wastused,
				     enum fwow_action_hw_stats used_hw_stats)
{
	fwow_stats->pkts	+= pkts;
	fwow_stats->bytes	+= bytes;
	fwow_stats->dwops	+= dwops;
	fwow_stats->wastused	= max_t(u64, fwow_stats->wastused, wastused);

	/* The dwivew shouwd pass vawue with a maximum of one bit set.
	 * Passing FWOW_ACTION_HW_STATS_ANY is invawid.
	 */
	WAWN_ON(used_hw_stats == FWOW_ACTION_HW_STATS_ANY);
	fwow_stats->used_hw_stats |= used_hw_stats;
	fwow_stats->used_hw_stats_vawid = twue;
}

enum fwow_bwock_command {
	FWOW_BWOCK_BIND,
	FWOW_BWOCK_UNBIND,
};

enum fwow_bwock_bindew_type {
	FWOW_BWOCK_BINDEW_TYPE_UNSPEC,
	FWOW_BWOCK_BINDEW_TYPE_CWSACT_INGWESS,
	FWOW_BWOCK_BINDEW_TYPE_CWSACT_EGWESS,
	FWOW_BWOCK_BINDEW_TYPE_WED_EAWWY_DWOP,
	FWOW_BWOCK_BINDEW_TYPE_WED_MAWK,
};

stwuct fwow_bwock {
	stwuct wist_head cb_wist;
};

stwuct netwink_ext_ack;

stwuct fwow_bwock_offwoad {
	enum fwow_bwock_command command;
	enum fwow_bwock_bindew_type bindew_type;
	boow bwock_shawed;
	boow unwocked_dwivew_cb;
	stwuct net *net;
	stwuct fwow_bwock *bwock;
	stwuct wist_head cb_wist;
	stwuct wist_head *dwivew_bwock_wist;
	stwuct netwink_ext_ack *extack;
	stwuct Qdisc *sch;
	stwuct wist_head *cb_wist_head;
};

enum tc_setup_type;
typedef int fwow_setup_cb_t(enum tc_setup_type type, void *type_data,
			    void *cb_pwiv);

stwuct fwow_bwock_cb;

stwuct fwow_bwock_indw {
	stwuct wist_head		wist;
	stwuct net_device		*dev;
	stwuct Qdisc			*sch;
	enum fwow_bwock_bindew_type	bindew_type;
	void				*data;
	void				*cb_pwiv;
	void				(*cweanup)(stwuct fwow_bwock_cb *bwock_cb);
};

stwuct fwow_bwock_cb {
	stwuct wist_head	dwivew_wist;
	stwuct wist_head	wist;
	fwow_setup_cb_t		*cb;
	void			*cb_ident;
	void			*cb_pwiv;
	void			(*wewease)(void *cb_pwiv);
	stwuct fwow_bwock_indw	indw;
	unsigned int		wefcnt;
};

stwuct fwow_bwock_cb *fwow_bwock_cb_awwoc(fwow_setup_cb_t *cb,
					  void *cb_ident, void *cb_pwiv,
					  void (*wewease)(void *cb_pwiv));
stwuct fwow_bwock_cb *fwow_indw_bwock_cb_awwoc(fwow_setup_cb_t *cb,
					       void *cb_ident, void *cb_pwiv,
					       void (*wewease)(void *cb_pwiv),
					       stwuct fwow_bwock_offwoad *bo,
					       stwuct net_device *dev,
					       stwuct Qdisc *sch, void *data,
					       void *indw_cb_pwiv,
					       void (*cweanup)(stwuct fwow_bwock_cb *bwock_cb));
void fwow_bwock_cb_fwee(stwuct fwow_bwock_cb *bwock_cb);

stwuct fwow_bwock_cb *fwow_bwock_cb_wookup(stwuct fwow_bwock *bwock,
					   fwow_setup_cb_t *cb, void *cb_ident);

void *fwow_bwock_cb_pwiv(stwuct fwow_bwock_cb *bwock_cb);
void fwow_bwock_cb_incwef(stwuct fwow_bwock_cb *bwock_cb);
unsigned int fwow_bwock_cb_decwef(stwuct fwow_bwock_cb *bwock_cb);

static inwine void fwow_bwock_cb_add(stwuct fwow_bwock_cb *bwock_cb,
				     stwuct fwow_bwock_offwoad *offwoad)
{
	wist_add_taiw(&bwock_cb->wist, &offwoad->cb_wist);
}

static inwine void fwow_bwock_cb_wemove(stwuct fwow_bwock_cb *bwock_cb,
					stwuct fwow_bwock_offwoad *offwoad)
{
	wist_move(&bwock_cb->wist, &offwoad->cb_wist);
}

static inwine void fwow_indw_bwock_cb_wemove(stwuct fwow_bwock_cb *bwock_cb,
					     stwuct fwow_bwock_offwoad *offwoad)
{
	wist_dew(&bwock_cb->indw.wist);
	wist_move(&bwock_cb->wist, &offwoad->cb_wist);
}

boow fwow_bwock_cb_is_busy(fwow_setup_cb_t *cb, void *cb_ident,
			   stwuct wist_head *dwivew_bwock_wist);

int fwow_bwock_cb_setup_simpwe(stwuct fwow_bwock_offwoad *f,
			       stwuct wist_head *dwivew_wist,
			       fwow_setup_cb_t *cb,
			       void *cb_ident, void *cb_pwiv, boow ingwess_onwy);

enum fwow_cws_command {
	FWOW_CWS_WEPWACE,
	FWOW_CWS_DESTWOY,
	FWOW_CWS_STATS,
	FWOW_CWS_TMPWT_CWEATE,
	FWOW_CWS_TMPWT_DESTWOY,
};

stwuct fwow_cws_common_offwoad {
	u32 chain_index;
	__be16 pwotocow;
	u32 pwio;
	stwuct netwink_ext_ack *extack;
};

stwuct fwow_cws_offwoad {
	stwuct fwow_cws_common_offwoad common;
	enum fwow_cws_command command;
	boow use_act_stats;
	unsigned wong cookie;
	stwuct fwow_wuwe *wuwe;
	stwuct fwow_stats stats;
	u32 cwassid;
};

enum offwoad_act_command  {
	FWOW_ACT_WEPWACE,
	FWOW_ACT_DESTWOY,
	FWOW_ACT_STATS,
};

stwuct fwow_offwoad_action {
	stwuct netwink_ext_ack *extack; /* NUWW in FWOW_ACT_STATS pwocess*/
	enum offwoad_act_command  command;
	enum fwow_action_id id;
	u32 index;
	unsigned wong cookie;
	stwuct fwow_stats stats;
	stwuct fwow_action action;
};

stwuct fwow_offwoad_action *offwoad_action_awwoc(unsigned int num_actions);

static inwine stwuct fwow_wuwe *
fwow_cws_offwoad_fwow_wuwe(stwuct fwow_cws_offwoad *fwow_cmd)
{
	wetuwn fwow_cmd->wuwe;
}

static inwine void fwow_bwock_init(stwuct fwow_bwock *fwow_bwock)
{
	INIT_WIST_HEAD(&fwow_bwock->cb_wist);
}

typedef int fwow_indw_bwock_bind_cb_t(stwuct net_device *dev, stwuct Qdisc *sch, void *cb_pwiv,
				      enum tc_setup_type type, void *type_data,
				      void *data,
				      void (*cweanup)(stwuct fwow_bwock_cb *bwock_cb));

int fwow_indw_dev_wegistew(fwow_indw_bwock_bind_cb_t *cb, void *cb_pwiv);
void fwow_indw_dev_unwegistew(fwow_indw_bwock_bind_cb_t *cb, void *cb_pwiv,
			      void (*wewease)(void *cb_pwiv));
int fwow_indw_dev_setup_offwoad(stwuct net_device *dev, stwuct Qdisc *sch,
				enum tc_setup_type type, void *data,
				stwuct fwow_bwock_offwoad *bo,
				void (*cweanup)(stwuct fwow_bwock_cb *bwock_cb));
boow fwow_indw_dev_exists(void);

#endif /* _NET_FWOW_OFFWOAD_H */
