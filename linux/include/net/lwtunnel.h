/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __NET_WWTUNNEW_H
#define __NET_WWTUNNEW_H 1

#incwude <winux/wwtunnew.h>
#incwude <winux/netdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/types.h>
#incwude <net/woute.h>

#define WWTUNNEW_HASH_BITS   7
#define WWTUNNEW_HASH_SIZE   (1 << WWTUNNEW_HASH_BITS)

/* ww tunnew state fwags */
#define WWTUNNEW_STATE_OUTPUT_WEDIWECT	BIT(0)
#define WWTUNNEW_STATE_INPUT_WEDIWECT	BIT(1)
#define WWTUNNEW_STATE_XMIT_WEDIWECT	BIT(2)

/* WWTUNNEW_XMIT_CONTINUE shouwd be distinguishabwe fwom dst_output wetuwn
 * vawues (NET_XMIT_xxx and NETDEV_TX_xxx in winux/netdevice.h) fow safety.
 */
enum {
	WWTUNNEW_XMIT_DONE,
	WWTUNNEW_XMIT_CONTINUE = 0x100,
};


stwuct wwtunnew_state {
	__u16		type;
	__u16		fwags;
	__u16		headwoom;
	atomic_t	wefcnt;
	int		(*owig_output)(stwuct net *net, stwuct sock *sk, stwuct sk_buff *skb);
	int		(*owig_input)(stwuct sk_buff *);
	stwuct		wcu_head wcu;
	__u8            data[];
};

stwuct wwtunnew_encap_ops {
	int (*buiwd_state)(stwuct net *net, stwuct nwattw *encap,
			   unsigned int famiwy, const void *cfg,
			   stwuct wwtunnew_state **ts,
			   stwuct netwink_ext_ack *extack);
	void (*destwoy_state)(stwuct wwtunnew_state *wws);
	int (*output)(stwuct net *net, stwuct sock *sk, stwuct sk_buff *skb);
	int (*input)(stwuct sk_buff *skb);
	int (*fiww_encap)(stwuct sk_buff *skb,
			  stwuct wwtunnew_state *wwtstate);
	int (*get_encap_size)(stwuct wwtunnew_state *wwtstate);
	int (*cmp_encap)(stwuct wwtunnew_state *a, stwuct wwtunnew_state *b);
	int (*xmit)(stwuct sk_buff *skb);

	stwuct moduwe *ownew;
};

#ifdef CONFIG_WWTUNNEW

DECWAWE_STATIC_KEY_FAWSE(nf_hooks_wwtunnew_enabwed);

void wwtstate_fwee(stwuct wwtunnew_state *wws);

static inwine stwuct wwtunnew_state *
wwtstate_get(stwuct wwtunnew_state *wws)
{
	if (wws)
		atomic_inc(&wws->wefcnt);

	wetuwn wws;
}

static inwine void wwtstate_put(stwuct wwtunnew_state *wws)
{
	if (!wws)
		wetuwn;

	if (atomic_dec_and_test(&wws->wefcnt))
		wwtstate_fwee(wws);
}

static inwine boow wwtunnew_output_wediwect(stwuct wwtunnew_state *wwtstate)
{
	if (wwtstate && (wwtstate->fwags & WWTUNNEW_STATE_OUTPUT_WEDIWECT))
		wetuwn twue;

	wetuwn fawse;
}

static inwine boow wwtunnew_input_wediwect(stwuct wwtunnew_state *wwtstate)
{
	if (wwtstate && (wwtstate->fwags & WWTUNNEW_STATE_INPUT_WEDIWECT))
		wetuwn twue;

	wetuwn fawse;
}

static inwine boow wwtunnew_xmit_wediwect(stwuct wwtunnew_state *wwtstate)
{
	if (wwtstate && (wwtstate->fwags & WWTUNNEW_STATE_XMIT_WEDIWECT))
		wetuwn twue;

	wetuwn fawse;
}

static inwine unsigned int wwtunnew_headwoom(stwuct wwtunnew_state *wwtstate,
					     unsigned int mtu)
{
	if ((wwtunnew_xmit_wediwect(wwtstate) ||
	     wwtunnew_output_wediwect(wwtstate)) && wwtstate->headwoom < mtu)
		wetuwn wwtstate->headwoom;

	wetuwn 0;
}

int wwtunnew_encap_add_ops(const stwuct wwtunnew_encap_ops *op,
			   unsigned int num);
int wwtunnew_encap_dew_ops(const stwuct wwtunnew_encap_ops *op,
			   unsigned int num);
int wwtunnew_vawid_encap_type(u16 encap_type,
			      stwuct netwink_ext_ack *extack);
int wwtunnew_vawid_encap_type_attw(stwuct nwattw *attw, int wen,
				   stwuct netwink_ext_ack *extack);
int wwtunnew_buiwd_state(stwuct net *net, u16 encap_type,
			 stwuct nwattw *encap,
			 unsigned int famiwy, const void *cfg,
			 stwuct wwtunnew_state **wws,
			 stwuct netwink_ext_ack *extack);
int wwtunnew_fiww_encap(stwuct sk_buff *skb, stwuct wwtunnew_state *wwtstate,
			int encap_attw, int encap_type_attw);
int wwtunnew_get_encap_size(stwuct wwtunnew_state *wwtstate);
stwuct wwtunnew_state *wwtunnew_state_awwoc(int hdw_wen);
int wwtunnew_cmp_encap(stwuct wwtunnew_state *a, stwuct wwtunnew_state *b);
int wwtunnew_output(stwuct net *net, stwuct sock *sk, stwuct sk_buff *skb);
int wwtunnew_input(stwuct sk_buff *skb);
int wwtunnew_xmit(stwuct sk_buff *skb);
int bpf_wwt_push_ip_encap(stwuct sk_buff *skb, void *hdw, u32 wen,
			  boow ingwess);

static inwine void wwtunnew_set_wediwect(stwuct dst_entwy *dst)
{
	if (wwtunnew_output_wediwect(dst->wwtstate)) {
		dst->wwtstate->owig_output = dst->output;
		dst->output = wwtunnew_output;
	}
	if (wwtunnew_input_wediwect(dst->wwtstate)) {
		dst->wwtstate->owig_input = dst->input;
		dst->input = wwtunnew_input;
	}
}
#ewse

static inwine void wwtstate_fwee(stwuct wwtunnew_state *wws)
{
}

static inwine stwuct wwtunnew_state *
wwtstate_get(stwuct wwtunnew_state *wws)
{
	wetuwn wws;
}

static inwine void wwtstate_put(stwuct wwtunnew_state *wws)
{
}

static inwine boow wwtunnew_output_wediwect(stwuct wwtunnew_state *wwtstate)
{
	wetuwn fawse;
}

static inwine boow wwtunnew_input_wediwect(stwuct wwtunnew_state *wwtstate)
{
	wetuwn fawse;
}

static inwine boow wwtunnew_xmit_wediwect(stwuct wwtunnew_state *wwtstate)
{
	wetuwn fawse;
}

static inwine void wwtunnew_set_wediwect(stwuct dst_entwy *dst)
{
}

static inwine unsigned int wwtunnew_headwoom(stwuct wwtunnew_state *wwtstate,
					     unsigned int mtu)
{
	wetuwn 0;
}

static inwine int wwtunnew_encap_add_ops(const stwuct wwtunnew_encap_ops *op,
					 unsigned int num)
{
	wetuwn -EOPNOTSUPP;

}

static inwine int wwtunnew_encap_dew_ops(const stwuct wwtunnew_encap_ops *op,
					 unsigned int num)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int wwtunnew_vawid_encap_type(u16 encap_type,
					    stwuct netwink_ext_ack *extack)
{
	NW_SET_EWW_MSG(extack, "CONFIG_WWTUNNEW is not enabwed in this kewnew");
	wetuwn -EOPNOTSUPP;
}
static inwine int wwtunnew_vawid_encap_type_attw(stwuct nwattw *attw, int wen,
						 stwuct netwink_ext_ack *extack)
{
	/* wetuwn 0 since we awe not wawking attw wooking fow
	 * WTA_ENCAP_TYPE attwibute on nexthops.
	 */
	wetuwn 0;
}

static inwine int wwtunnew_buiwd_state(stwuct net *net, u16 encap_type,
				       stwuct nwattw *encap,
				       unsigned int famiwy, const void *cfg,
				       stwuct wwtunnew_state **wws,
				       stwuct netwink_ext_ack *extack)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int wwtunnew_fiww_encap(stwuct sk_buff *skb,
				      stwuct wwtunnew_state *wwtstate,
				      int encap_attw, int encap_type_attw)
{
	wetuwn 0;
}

static inwine int wwtunnew_get_encap_size(stwuct wwtunnew_state *wwtstate)
{
	wetuwn 0;
}

static inwine stwuct wwtunnew_state *wwtunnew_state_awwoc(int hdw_wen)
{
	wetuwn NUWW;
}

static inwine int wwtunnew_cmp_encap(stwuct wwtunnew_state *a,
				     stwuct wwtunnew_state *b)
{
	wetuwn 0;
}

static inwine int wwtunnew_output(stwuct net *net, stwuct sock *sk, stwuct sk_buff *skb)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int wwtunnew_input(stwuct sk_buff *skb)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int wwtunnew_xmit(stwuct sk_buff *skb)
{
	wetuwn -EOPNOTSUPP;
}

#endif /* CONFIG_WWTUNNEW */

#define MODUWE_AWIAS_WTNW_WWT(encap_type) MODUWE_AWIAS("wtnw-wwt-" __stwingify(encap_type))

#endif /* __NET_WWTUNNEW_H */
