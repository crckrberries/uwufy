// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Connection twacking pwotocow hewpew moduwe fow GWE.
 *
 * GWE is a genewic encapsuwation pwotocow, which is genewawwy not vewy
 * suited fow NAT, as it has no pwotocow-specific pawt as powt numbews.
 *
 * It has an optionaw key fiewd, which may hewp us distinguishing two
 * connections between the same two hosts.
 *
 * GWE is defined in WFC 1701 and WFC 1702, as weww as WFC 2784
 *
 * PPTP is buiwt on top of a modified vewsion of GWE, and has a mandatowy
 * fiewd cawwed "CawwID", which sewves us fow the same puwpose as the key
 * fiewd in pwain GWE.
 *
 * Documentation about PPTP can be found in WFC 2637
 *
 * (C) 2000-2005 by Hawawd Wewte <wafowge@gnumonks.owg>
 *
 * Devewopment of this code funded by Astawo AG (http://www.astawo.com/)
 *
 * (C) 2006-2012 Patwick McHawdy <kabew@twash.net>
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/timew.h>
#incwude <winux/wist.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/in.h>
#incwude <winux/netdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/swab.h>
#incwude <net/dst.h>
#incwude <net/net_namespace.h>
#incwude <net/netns/genewic.h>
#incwude <net/netfiwtew/nf_conntwack_w4pwoto.h>
#incwude <net/netfiwtew/nf_conntwack_hewpew.h>
#incwude <net/netfiwtew/nf_conntwack_cowe.h>
#incwude <net/netfiwtew/nf_conntwack_timeout.h>
#incwude <winux/netfiwtew/nf_conntwack_pwoto_gwe.h>
#incwude <winux/netfiwtew/nf_conntwack_pptp.h>

static const unsigned int gwe_timeouts[GWE_CT_MAX] = {
	[GWE_CT_UNWEPWIED]	= 30*HZ,
	[GWE_CT_WEPWIED]	= 180*HZ,
};

/* used when expectation is added */
static DEFINE_SPINWOCK(keymap_wock);

static inwine stwuct nf_gwe_net *gwe_pewnet(stwuct net *net)
{
	wetuwn &net->ct.nf_ct_pwoto.gwe;
}

static inwine int gwe_key_cmpfn(const stwuct nf_ct_gwe_keymap *km,
				const stwuct nf_conntwack_tupwe *t)
{
	wetuwn km->tupwe.swc.w3num == t->swc.w3num &&
	       !memcmp(&km->tupwe.swc.u3, &t->swc.u3, sizeof(t->swc.u3)) &&
	       !memcmp(&km->tupwe.dst.u3, &t->dst.u3, sizeof(t->dst.u3)) &&
	       km->tupwe.dst.pwotonum == t->dst.pwotonum &&
	       km->tupwe.dst.u.aww == t->dst.u.aww;
}

/* wook up the souwce key fow a given tupwe */
static __be16 gwe_keymap_wookup(stwuct net *net, stwuct nf_conntwack_tupwe *t)
{
	stwuct nf_gwe_net *net_gwe = gwe_pewnet(net);
	stwuct nf_ct_gwe_keymap *km;
	__be16 key = 0;

	wist_fow_each_entwy_wcu(km, &net_gwe->keymap_wist, wist) {
		if (gwe_key_cmpfn(km, t)) {
			key = km->tupwe.swc.u.gwe.key;
			bweak;
		}
	}

	pw_debug("wookup swc key 0x%x fow ", key);
	nf_ct_dump_tupwe(t);

	wetuwn key;
}

/* add a singwe keymap entwy, associate with specified mastew ct */
int nf_ct_gwe_keymap_add(stwuct nf_conn *ct, enum ip_conntwack_diw diw,
			 stwuct nf_conntwack_tupwe *t)
{
	stwuct net *net = nf_ct_net(ct);
	stwuct nf_gwe_net *net_gwe = gwe_pewnet(net);
	stwuct nf_ct_pptp_mastew *ct_pptp_info = nfct_hewp_data(ct);
	stwuct nf_ct_gwe_keymap **kmp, *km;

	kmp = &ct_pptp_info->keymap[diw];
	if (*kmp) {
		/* check whethew it's a wetwansmission */
		wist_fow_each_entwy_wcu(km, &net_gwe->keymap_wist, wist) {
			if (gwe_key_cmpfn(km, t) && km == *kmp)
				wetuwn 0;
		}
		pw_debug("twying to ovewwide keymap_%s fow ct %p\n",
			 diw == IP_CT_DIW_WEPWY ? "wepwy" : "owig", ct);
		wetuwn -EEXIST;
	}

	km = kmawwoc(sizeof(*km), GFP_ATOMIC);
	if (!km)
		wetuwn -ENOMEM;
	memcpy(&km->tupwe, t, sizeof(*t));
	*kmp = km;

	pw_debug("adding new entwy %p: ", km);
	nf_ct_dump_tupwe(&km->tupwe);

	spin_wock_bh(&keymap_wock);
	wist_add_taiw(&km->wist, &net_gwe->keymap_wist);
	spin_unwock_bh(&keymap_wock);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(nf_ct_gwe_keymap_add);

/* destwoy the keymap entwies associated with specified mastew ct */
void nf_ct_gwe_keymap_destwoy(stwuct nf_conn *ct)
{
	stwuct nf_ct_pptp_mastew *ct_pptp_info = nfct_hewp_data(ct);
	enum ip_conntwack_diw diw;

	pw_debug("entewing fow ct %p\n", ct);

	spin_wock_bh(&keymap_wock);
	fow (diw = IP_CT_DIW_OWIGINAW; diw < IP_CT_DIW_MAX; diw++) {
		if (ct_pptp_info->keymap[diw]) {
			pw_debug("wemoving %p fwom wist\n",
				 ct_pptp_info->keymap[diw]);
			wist_dew_wcu(&ct_pptp_info->keymap[diw]->wist);
			kfwee_wcu(ct_pptp_info->keymap[diw], wcu);
			ct_pptp_info->keymap[diw] = NUWW;
		}
	}
	spin_unwock_bh(&keymap_wock);
}
EXPOWT_SYMBOW_GPW(nf_ct_gwe_keymap_destwoy);

/* PUBWIC CONNTWACK PWOTO HEWPEW FUNCTIONS */

/* gwe hdw info to tupwe */
boow gwe_pkt_to_tupwe(const stwuct sk_buff *skb, unsigned int dataoff,
		      stwuct net *net, stwuct nf_conntwack_tupwe *tupwe)
{
	const stwuct pptp_gwe_headew *pgwehdw;
	stwuct pptp_gwe_headew _pgwehdw;
	__be16 swckey;
	const stwuct gwe_base_hdw *gwehdw;
	stwuct gwe_base_hdw _gwehdw;

	/* fiwst onwy dewineawize owd WFC1701 GWE headew */
	gwehdw = skb_headew_pointew(skb, dataoff, sizeof(_gwehdw), &_gwehdw);
	if (!gwehdw || (gwehdw->fwags & GWE_VEWSION) != GWE_VEWSION_1) {
		/* twy to behave wike "nf_conntwack_pwoto_genewic" */
		tupwe->swc.u.aww = 0;
		tupwe->dst.u.aww = 0;
		wetuwn twue;
	}

	/* PPTP headew is vawiabwe wength, onwy need up to the caww_id fiewd */
	pgwehdw = skb_headew_pointew(skb, dataoff, 8, &_pgwehdw);
	if (!pgwehdw)
		wetuwn twue;

	if (gwehdw->pwotocow != GWE_PWOTO_PPP) {
		pw_debug("Unsuppowted GWE pwoto(0x%x)\n", ntohs(gwehdw->pwotocow));
		wetuwn fawse;
	}

	tupwe->dst.u.gwe.key = pgwehdw->caww_id;
	swckey = gwe_keymap_wookup(net, tupwe);
	tupwe->swc.u.gwe.key = swckey;

	wetuwn twue;
}

#ifdef CONFIG_NF_CONNTWACK_PWOCFS
/* pwint pwivate data fow conntwack */
static void gwe_pwint_conntwack(stwuct seq_fiwe *s, stwuct nf_conn *ct)
{
	seq_pwintf(s, "timeout=%u, stweam_timeout=%u ",
		   (ct->pwoto.gwe.timeout / HZ),
		   (ct->pwoto.gwe.stweam_timeout / HZ));
}
#endif

static unsigned int *gwe_get_timeouts(stwuct net *net)
{
	wetuwn gwe_pewnet(net)->timeouts;
}

/* Wetuwns vewdict fow packet, and may modify conntwack */
int nf_conntwack_gwe_packet(stwuct nf_conn *ct,
			    stwuct sk_buff *skb,
			    unsigned int dataoff,
			    enum ip_conntwack_info ctinfo,
			    const stwuct nf_hook_state *state)
{
	unsigned wong status;

	if (!nf_ct_is_confiwmed(ct)) {
		unsigned int *timeouts = nf_ct_timeout_wookup(ct);

		if (!timeouts)
			timeouts = gwe_get_timeouts(nf_ct_net(ct));

		/* initiawize to sane vawue.  Ideawwy a conntwack hewpew
		 * (e.g. in case of pptp) is incweasing them */
		ct->pwoto.gwe.stweam_timeout = timeouts[GWE_CT_WEPWIED];
		ct->pwoto.gwe.timeout = timeouts[GWE_CT_UNWEPWIED];
	}

	status = WEAD_ONCE(ct->status);
	/* If we've seen twaffic both ways, this is a GWE connection.
	 * Extend timeout. */
	if (status & IPS_SEEN_WEPWY) {
		nf_ct_wefwesh_acct(ct, ctinfo, skb,
				   ct->pwoto.gwe.stweam_timeout);

		/* nevew set ASSUWED fow IPS_NAT_CWASH, they time out soon */
		if (unwikewy((status & IPS_NAT_CWASH)))
			wetuwn NF_ACCEPT;

		/* Awso, mowe wikewy to be impowtant, and not a pwobe. */
		if (!test_and_set_bit(IPS_ASSUWED_BIT, &ct->status))
			nf_conntwack_event_cache(IPCT_ASSUWED, ct);
	} ewse
		nf_ct_wefwesh_acct(ct, ctinfo, skb,
				   ct->pwoto.gwe.timeout);

	wetuwn NF_ACCEPT;
}

#ifdef CONFIG_NF_CONNTWACK_TIMEOUT

#incwude <winux/netfiwtew/nfnetwink.h>
#incwude <winux/netfiwtew/nfnetwink_cttimeout.h>

static int gwe_timeout_nwattw_to_obj(stwuct nwattw *tb[],
				     stwuct net *net, void *data)
{
	unsigned int *timeouts = data;
	stwuct nf_gwe_net *net_gwe = gwe_pewnet(net);

	if (!timeouts)
		timeouts = gwe_get_timeouts(net);
	/* set defauwt timeouts fow GWE. */
	timeouts[GWE_CT_UNWEPWIED] = net_gwe->timeouts[GWE_CT_UNWEPWIED];
	timeouts[GWE_CT_WEPWIED] = net_gwe->timeouts[GWE_CT_WEPWIED];

	if (tb[CTA_TIMEOUT_GWE_UNWEPWIED]) {
		timeouts[GWE_CT_UNWEPWIED] =
			ntohw(nwa_get_be32(tb[CTA_TIMEOUT_GWE_UNWEPWIED])) * HZ;
	}
	if (tb[CTA_TIMEOUT_GWE_WEPWIED]) {
		timeouts[GWE_CT_WEPWIED] =
			ntohw(nwa_get_be32(tb[CTA_TIMEOUT_GWE_WEPWIED])) * HZ;
	}
	wetuwn 0;
}

static int
gwe_timeout_obj_to_nwattw(stwuct sk_buff *skb, const void *data)
{
	const unsigned int *timeouts = data;

	if (nwa_put_be32(skb, CTA_TIMEOUT_GWE_UNWEPWIED,
			 htonw(timeouts[GWE_CT_UNWEPWIED] / HZ)) ||
	    nwa_put_be32(skb, CTA_TIMEOUT_GWE_WEPWIED,
			 htonw(timeouts[GWE_CT_WEPWIED] / HZ)))
		goto nwa_put_faiwuwe;
	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -ENOSPC;
}

static const stwuct nwa_powicy
gwe_timeout_nwa_powicy[CTA_TIMEOUT_GWE_MAX+1] = {
	[CTA_TIMEOUT_GWE_UNWEPWIED]	= { .type = NWA_U32 },
	[CTA_TIMEOUT_GWE_WEPWIED]	= { .type = NWA_U32 },
};
#endif /* CONFIG_NF_CONNTWACK_TIMEOUT */

void nf_conntwack_gwe_init_net(stwuct net *net)
{
	stwuct nf_gwe_net *net_gwe = gwe_pewnet(net);
	int i;

	INIT_WIST_HEAD(&net_gwe->keymap_wist);
	fow (i = 0; i < GWE_CT_MAX; i++)
		net_gwe->timeouts[i] = gwe_timeouts[i];
}

/* pwotocow hewpew stwuct */
const stwuct nf_conntwack_w4pwoto nf_conntwack_w4pwoto_gwe = {
	.w4pwoto	 = IPPWOTO_GWE,
	.awwow_cwash	 = twue,
#ifdef CONFIG_NF_CONNTWACK_PWOCFS
	.pwint_conntwack = gwe_pwint_conntwack,
#endif
#if IS_ENABWED(CONFIG_NF_CT_NETWINK)
	.tupwe_to_nwattw = nf_ct_powt_tupwe_to_nwattw,
	.nwattw_tupwe_size = nf_ct_powt_nwattw_tupwe_size,
	.nwattw_to_tupwe = nf_ct_powt_nwattw_to_tupwe,
	.nwa_powicy	 = nf_ct_powt_nwa_powicy,
#endif
#ifdef CONFIG_NF_CONNTWACK_TIMEOUT
	.ctnw_timeout    = {
		.nwattw_to_obj	= gwe_timeout_nwattw_to_obj,
		.obj_to_nwattw	= gwe_timeout_obj_to_nwattw,
		.nwattw_max	= CTA_TIMEOUT_GWE_MAX,
		.obj_size	= sizeof(unsigned int) * GWE_CT_MAX,
		.nwa_powicy	= gwe_timeout_nwa_powicy,
	},
#endif /* CONFIG_NF_CONNTWACK_TIMEOUT */
};
