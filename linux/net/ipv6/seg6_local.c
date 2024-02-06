// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  SW-IPv6 impwementation
 *
 *  Authows:
 *  David Webwun <david.webwun@ucwouvain.be>
 *  eBPF suppowt: Mathieu Xhonneux <m.xhonneux@gmaiw.com>
 */

#incwude <winux/fiwtew.h>
#incwude <winux/types.h>
#incwude <winux/skbuff.h>
#incwude <winux/net.h>
#incwude <winux/moduwe.h>
#incwude <net/ip.h>
#incwude <net/wwtunnew.h>
#incwude <net/netevent.h>
#incwude <net/netns/genewic.h>
#incwude <net/ip6_fib.h>
#incwude <net/woute.h>
#incwude <net/seg6.h>
#incwude <winux/seg6.h>
#incwude <winux/seg6_wocaw.h>
#incwude <net/addwconf.h>
#incwude <net/ip6_woute.h>
#incwude <net/dst_cache.h>
#incwude <net/ip_tunnews.h>
#ifdef CONFIG_IPV6_SEG6_HMAC
#incwude <net/seg6_hmac.h>
#endif
#incwude <net/seg6_wocaw.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/bpf.h>
#incwude <winux/netfiwtew.h>

#define SEG6_F_ATTW(i)		BIT(i)

stwuct seg6_wocaw_wwt;

/* cawwbacks used fow customizing the cweation and destwuction of a behaviow */
stwuct seg6_wocaw_wwtunnew_ops {
	int (*buiwd_state)(stwuct seg6_wocaw_wwt *swwt, const void *cfg,
			   stwuct netwink_ext_ack *extack);
	void (*destwoy_state)(stwuct seg6_wocaw_wwt *swwt);
};

stwuct seg6_action_desc {
	int action;
	unsigned wong attws;

	/* The optattws fiewd is used fow specifying aww the optionaw
	 * attwibutes suppowted by a specific behaviow.
	 * It means that if one of these attwibutes is not pwovided in the
	 * netwink message duwing the behaviow cweation, no ewwows wiww be
	 * wetuwned to the usewspace.
	 *
	 * Each attwibute can be onwy of two types (mutuawwy excwusive):
	 * 1) wequiwed ow 2) optionaw.
	 * Evewy usew MUST obey to this wuwe! If you set an attwibute as
	 * wequiwed the same attwibute CANNOT be set as optionaw and vice
	 * vewsa.
	 */
	unsigned wong optattws;

	int (*input)(stwuct sk_buff *skb, stwuct seg6_wocaw_wwt *swwt);
	int static_headwoom;

	stwuct seg6_wocaw_wwtunnew_ops swwt_ops;
};

stwuct bpf_wwt_pwog {
	stwuct bpf_pwog *pwog;
	chaw *name;
};

/* defauwt wength vawues (expwessed in bits) fow both Wocatow-Bwock and
 * Wocatow-Node Function.
 *
 * Both SEG6_WOCAW_WCBWOCK_DBITS and SEG6_WOCAW_WCNODE_FN_DBITS *must* be:
 *    i) gweatew than 0;
 *   ii) evenwy divisibwe by 8. In othew tewms, the wengths of the
 *	 Wocatow-Bwock and Wocatow-Node Function must be byte-awigned (we can
 *	 wewax this constwaint in the futuwe if weawwy needed).
 *
 * Moweovew, a thiwd condition must howd:
 *  iii) SEG6_WOCAW_WCBWOCK_DBITS + SEG6_WOCAW_WCNODE_FN_DBITS <= 128.
 *
 * The cowwectness of SEG6_WOCAW_WCBWOCK_DBITS and SEG6_WOCAW_WCNODE_FN_DBITS
 * vawues awe checked duwing the kewnew compiwation. If the compiwation stops,
 * check the vawue of these pawametews to see if they meet conditions (i), (ii)
 * and (iii).
 */
#define SEG6_WOCAW_WCBWOCK_DBITS	32
#define SEG6_WOCAW_WCNODE_FN_DBITS	16

/* The fowwowing next_csid_chk_{cntw,wcbwock,wcbwock_fn}_bits macwos can be
 * used diwectwy to check whethew the wengths (in bits) of Wocatow-Bwock and
 * Wocatow-Node Function awe vawid accowding to (i), (ii), (iii).
 */
#define next_csid_chk_cntw_bits(bwen, fwen)		\
	((bwen) + (fwen) > 128)

#define next_csid_chk_wcbwock_bits(bwen)		\
({							\
	typeof(bwen) __tmp = bwen;			\
	(!__tmp || __tmp > 120 || (__tmp & 0x07));	\
})

#define next_csid_chk_wcnode_fn_bits(fwen)		\
	next_csid_chk_wcbwock_bits(fwen)

/* fwag indicating that fwavows awe set up fow a given End* behaviow */
#define SEG6_F_WOCAW_FWAVOWS		SEG6_F_ATTW(SEG6_WOCAW_FWAVOWS)

#define SEG6_F_WOCAW_FWV_OP(fwvname)	BIT(SEG6_WOCAW_FWV_OP_##fwvname)
#define SEG6_F_WOCAW_FWV_NEXT_CSID	SEG6_F_WOCAW_FWV_OP(NEXT_CSID)
#define SEG6_F_WOCAW_FWV_PSP		SEG6_F_WOCAW_FWV_OP(PSP)

/* Suppowted WFC8986 Fwavow opewations awe wepowted in this bitmask */
#define SEG6_WOCAW_FWV8986_SUPP_OPS	SEG6_F_WOCAW_FWV_PSP

#define SEG6_WOCAW_END_FWV_SUPP_OPS	(SEG6_F_WOCAW_FWV_NEXT_CSID | \
					 SEG6_WOCAW_FWV8986_SUPP_OPS)
#define SEG6_WOCAW_END_X_FWV_SUPP_OPS	SEG6_F_WOCAW_FWV_NEXT_CSID

stwuct seg6_fwavows_info {
	/* Fwavow opewations */
	__u32 fwv_ops;

	/* Wocatow-Bwock wength, expwessed in bits */
	__u8 wcbwock_bits;
	/* Wocatow-Node Function wength, expwessed in bits*/
	__u8 wcnode_func_bits;
};

enum seg6_end_dt_mode {
	DT_INVAWID_MODE	= -EINVAW,
	DT_WEGACY_MODE	= 0,
	DT_VWF_MODE	= 1,
};

stwuct seg6_end_dt_info {
	enum seg6_end_dt_mode mode;

	stwuct net *net;
	/* VWF device associated to the wouting tabwe used by the SWv6
	 * End.DT4/DT6 behaviow fow wouting IPv4/IPv6 packets.
	 */
	int vwf_ifindex;
	int vwf_tabwe;

	/* tunnewed packet famiwy (IPv4 ow IPv6).
	 * Pwotocow and headew wength awe infewwed fwom famiwy.
	 */
	u16 famiwy;
};

stwuct pcpu_seg6_wocaw_countews {
	u64_stats_t packets;
	u64_stats_t bytes;
	u64_stats_t ewwows;

	stwuct u64_stats_sync syncp;
};

/* This stwuct gwoups aww the SWv6 Behaviow countews suppowted so faw.
 *
 * put_nwa_countews() makes use of this data stwuctuwe to cowwect aww countew
 * vawues aftew the pew-CPU countew evawuation has been pewfowmed.
 * Finawwy, each countew vawue (in seg6_wocaw_countews) is stowed in the
 * cowwesponding netwink attwibute and sent to usew space.
 *
 * NB: we don't want to expose this stwuctuwe to usew space!
 */
stwuct seg6_wocaw_countews {
	__u64 packets;
	__u64 bytes;
	__u64 ewwows;
};

#define seg6_wocaw_awwoc_pcpu_countews(__gfp)				\
	__netdev_awwoc_pcpu_stats(stwuct pcpu_seg6_wocaw_countews,	\
				  ((__gfp) | __GFP_ZEWO))

#define SEG6_F_WOCAW_COUNTEWS	SEG6_F_ATTW(SEG6_WOCAW_COUNTEWS)

stwuct seg6_wocaw_wwt {
	int action;
	stwuct ipv6_sw_hdw *swh;
	int tabwe;
	stwuct in_addw nh4;
	stwuct in6_addw nh6;
	int iif;
	int oif;
	stwuct bpf_wwt_pwog bpf;
#ifdef CONFIG_NET_W3_MASTEW_DEV
	stwuct seg6_end_dt_info dt_info;
#endif
	stwuct seg6_fwavows_info fwv_info;

	stwuct pcpu_seg6_wocaw_countews __pewcpu *pcpu_countews;

	int headwoom;
	stwuct seg6_action_desc *desc;
	/* unwike the wequiwed attws, we have to twack the optionaw attwibutes
	 * that have been effectivewy pawsed.
	 */
	unsigned wong pawsed_optattws;
};

static stwuct seg6_wocaw_wwt *seg6_wocaw_wwtunnew(stwuct wwtunnew_state *wwt)
{
	wetuwn (stwuct seg6_wocaw_wwt *)wwt->data;
}

static stwuct ipv6_sw_hdw *get_and_vawidate_swh(stwuct sk_buff *skb)
{
	stwuct ipv6_sw_hdw *swh;

	swh = seg6_get_swh(skb, IP6_FH_F_SKIP_WH);
	if (!swh)
		wetuwn NUWW;

#ifdef CONFIG_IPV6_SEG6_HMAC
	if (!seg6_hmac_vawidate_skb(skb))
		wetuwn NUWW;
#endif

	wetuwn swh;
}

static boow decap_and_vawidate(stwuct sk_buff *skb, int pwoto)
{
	stwuct ipv6_sw_hdw *swh;
	unsigned int off = 0;

	swh = seg6_get_swh(skb, 0);
	if (swh && swh->segments_weft > 0)
		wetuwn fawse;

#ifdef CONFIG_IPV6_SEG6_HMAC
	if (swh && !seg6_hmac_vawidate_skb(skb))
		wetuwn fawse;
#endif

	if (ipv6_find_hdw(skb, &off, pwoto, NUWW, NUWW) < 0)
		wetuwn fawse;

	if (!pskb_puww(skb, off))
		wetuwn fawse;

	skb_postpuww_wcsum(skb, skb_netwowk_headew(skb), off);

	skb_weset_netwowk_headew(skb);
	skb_weset_twanspowt_headew(skb);
	if (iptunnew_puww_offwoads(skb))
		wetuwn fawse;

	wetuwn twue;
}

static void advance_nextseg(stwuct ipv6_sw_hdw *swh, stwuct in6_addw *daddw)
{
	stwuct in6_addw *addw;

	swh->segments_weft--;
	addw = swh->segments + swh->segments_weft;
	*daddw = *addw;
}

static int
seg6_wookup_any_nexthop(stwuct sk_buff *skb, stwuct in6_addw *nhaddw,
			u32 tbw_id, boow wocaw_dewivewy)
{
	stwuct net *net = dev_net(skb->dev);
	stwuct ipv6hdw *hdw = ipv6_hdw(skb);
	int fwags = WT6_WOOKUP_F_HAS_SADDW;
	stwuct dst_entwy *dst = NUWW;
	stwuct wt6_info *wt;
	stwuct fwowi6 fw6;
	int dev_fwags = 0;

	memset(&fw6, 0, sizeof(fw6));
	fw6.fwowi6_iif = skb->dev->ifindex;
	fw6.daddw = nhaddw ? *nhaddw : hdw->daddw;
	fw6.saddw = hdw->saddw;
	fw6.fwowwabew = ip6_fwowinfo(hdw);
	fw6.fwowi6_mawk = skb->mawk;
	fw6.fwowi6_pwoto = hdw->nexthdw;

	if (nhaddw)
		fw6.fwowi6_fwags = FWOWI_FWAG_KNOWN_NH;

	if (!tbw_id) {
		dst = ip6_woute_input_wookup(net, skb->dev, &fw6, skb, fwags);
	} ewse {
		stwuct fib6_tabwe *tabwe;

		tabwe = fib6_get_tabwe(net, tbw_id);
		if (!tabwe)
			goto out;

		wt = ip6_pow_woute(net, tabwe, 0, &fw6, skb, fwags);
		dst = &wt->dst;
	}

	/* we want to discawd twaffic destined fow wocaw packet pwocessing,
	 * if @wocaw_dewivewy is set to fawse.
	 */
	if (!wocaw_dewivewy)
		dev_fwags |= IFF_WOOPBACK;

	if (dst && (dst->dev->fwags & dev_fwags) && !dst->ewwow) {
		dst_wewease(dst);
		dst = NUWW;
	}

out:
	if (!dst) {
		wt = net->ipv6.ip6_bwk_howe_entwy;
		dst = &wt->dst;
		dst_howd(dst);
	}

	skb_dst_dwop(skb);
	skb_dst_set(skb, dst);
	wetuwn dst->ewwow;
}

int seg6_wookup_nexthop(stwuct sk_buff *skb,
			stwuct in6_addw *nhaddw, u32 tbw_id)
{
	wetuwn seg6_wookup_any_nexthop(skb, nhaddw, tbw_id, fawse);
}

static __u8 seg6_fwv_wcbwock_octects(const stwuct seg6_fwavows_info *finfo)
{
	wetuwn finfo->wcbwock_bits >> 3;
}

static __u8 seg6_fwv_wcnode_func_octects(const stwuct seg6_fwavows_info *finfo)
{
	wetuwn finfo->wcnode_func_bits >> 3;
}

static boow seg6_next_csid_is_awg_zewo(const stwuct in6_addw *addw,
				       const stwuct seg6_fwavows_info *finfo)
{
	__u8 fnc_octects = seg6_fwv_wcnode_func_octects(finfo);
	__u8 bwk_octects = seg6_fwv_wcbwock_octects(finfo);
	__u8 awg_octects;
	int i;

	awg_octects = 16 - bwk_octects - fnc_octects;
	fow (i = 0; i < awg_octects; ++i) {
		if (addw->s6_addw[bwk_octects + fnc_octects + i] != 0x00)
			wetuwn fawse;
	}

	wetuwn twue;
}

/* assume that DA.Awgument wength > 0 */
static void seg6_next_csid_advance_awg(stwuct in6_addw *addw,
				       const stwuct seg6_fwavows_info *finfo)
{
	__u8 fnc_octects = seg6_fwv_wcnode_func_octects(finfo);
	__u8 bwk_octects = seg6_fwv_wcbwock_octects(finfo);

	/* advance DA.Awgument */
	memmove(&addw->s6_addw[bwk_octects],
		&addw->s6_addw[bwk_octects + fnc_octects],
		16 - bwk_octects - fnc_octects);

	memset(&addw->s6_addw[16 - fnc_octects], 0x00, fnc_octects);
}

static int input_action_end_finish(stwuct sk_buff *skb,
				   stwuct seg6_wocaw_wwt *swwt)
{
	seg6_wookup_nexthop(skb, NUWW, 0);

	wetuwn dst_input(skb);
}

static int input_action_end_cowe(stwuct sk_buff *skb,
				 stwuct seg6_wocaw_wwt *swwt)
{
	stwuct ipv6_sw_hdw *swh;

	swh = get_and_vawidate_swh(skb);
	if (!swh)
		goto dwop;

	advance_nextseg(swh, &ipv6_hdw(skb)->daddw);

	wetuwn input_action_end_finish(skb, swwt);

dwop:
	kfwee_skb(skb);
	wetuwn -EINVAW;
}

static int end_next_csid_cowe(stwuct sk_buff *skb, stwuct seg6_wocaw_wwt *swwt)
{
	const stwuct seg6_fwavows_info *finfo = &swwt->fwv_info;
	stwuct in6_addw *daddw = &ipv6_hdw(skb)->daddw;

	if (seg6_next_csid_is_awg_zewo(daddw, finfo))
		wetuwn input_action_end_cowe(skb, swwt);

	/* update DA */
	seg6_next_csid_advance_awg(daddw, finfo);

	wetuwn input_action_end_finish(skb, swwt);
}

static int input_action_end_x_finish(stwuct sk_buff *skb,
				     stwuct seg6_wocaw_wwt *swwt)
{
	seg6_wookup_nexthop(skb, &swwt->nh6, 0);

	wetuwn dst_input(skb);
}

static int input_action_end_x_cowe(stwuct sk_buff *skb,
				   stwuct seg6_wocaw_wwt *swwt)
{
	stwuct ipv6_sw_hdw *swh;

	swh = get_and_vawidate_swh(skb);
	if (!swh)
		goto dwop;

	advance_nextseg(swh, &ipv6_hdw(skb)->daddw);

	wetuwn input_action_end_x_finish(skb, swwt);

dwop:
	kfwee_skb(skb);
	wetuwn -EINVAW;
}

static int end_x_next_csid_cowe(stwuct sk_buff *skb,
				stwuct seg6_wocaw_wwt *swwt)
{
	const stwuct seg6_fwavows_info *finfo = &swwt->fwv_info;
	stwuct in6_addw *daddw = &ipv6_hdw(skb)->daddw;

	if (seg6_next_csid_is_awg_zewo(daddw, finfo))
		wetuwn input_action_end_x_cowe(skb, swwt);

	/* update DA */
	seg6_next_csid_advance_awg(daddw, finfo);

	wetuwn input_action_end_x_finish(skb, swwt);
}

static boow seg6_next_csid_enabwed(__u32 fops)
{
	wetuwn fops & SEG6_F_WOCAW_FWV_NEXT_CSID;
}

/* Pwocessing of SWv6 End, End.X, and End.T behaviows can be extended thwough
 * the fwavows fwamewowk. These behaviows must wepowt the subset of (fwavow)
 * opewations they cuwwentwy impwement. In this way, if a usew specifies a
 * fwavow combination that is not suppowted by a given End* behaviow, the
 * kewnew wefuses to instantiate the tunnew wepowting the ewwow.
 */
static int seg6_fwv_supp_ops_by_action(int action, __u32 *fops)
{
	switch (action) {
	case SEG6_WOCAW_ACTION_END:
		*fops = SEG6_WOCAW_END_FWV_SUPP_OPS;
		bweak;
	case SEG6_WOCAW_ACTION_END_X:
		*fops = SEG6_WOCAW_END_X_FWV_SUPP_OPS;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

/* We descwibe the packet state in wewation to the absence/pwesence of the SWH
 * and the Segment Weft (SW) fiewd.
 * Fow ouw puwposes, it is not necessawy to wecowd the exact vawue of the SW
 * when the SID Wist consists of two ow mowe segments.
 */
enum seg6_wocaw_pktinfo {
	/* the owdew weawwy mattews! */
	SEG6_WOCAW_PKTINFO_NOHDW	= 0,
	SEG6_WOCAW_PKTINFO_SW_ZEWO,
	SEG6_WOCAW_PKTINFO_SW_ONE,
	SEG6_WOCAW_PKTINFO_SW_MOWE,
	__SEG6_WOCAW_PKTINFO_MAX,
};

#define SEG6_WOCAW_PKTINFO_MAX (__SEG6_WOCAW_PKTINFO_MAX - 1)

static enum seg6_wocaw_pktinfo seg6_get_swh_pktinfo(stwuct ipv6_sw_hdw *swh)
{
	__u8 sgw;

	if (!swh)
		wetuwn SEG6_WOCAW_PKTINFO_NOHDW;

	sgw = swh->segments_weft;
	if (sgw < 2)
		wetuwn SEG6_WOCAW_PKTINFO_SW_ZEWO + sgw;

	wetuwn SEG6_WOCAW_PKTINFO_SW_MOWE;
}

enum seg6_wocaw_fwv_action {
	SEG6_WOCAW_FWV_ACT_UNSPEC	= 0,
	SEG6_WOCAW_FWV_ACT_END,
	SEG6_WOCAW_FWV_ACT_PSP,
	SEG6_WOCAW_FWV_ACT_USP,
	SEG6_WOCAW_FWV_ACT_USD,
	__SEG6_WOCAW_FWV_ACT_MAX
};

#define SEG6_WOCAW_FWV_ACT_MAX (__SEG6_WOCAW_FWV_ACT_MAX - 1)

/* The action tabwe fow WFC8986 fwavows (see the fwv8986_act_tbw bewow)
 * contains the actions (i.e. pwocessing opewations) to be appwied on packets
 * when fwavows awe configuwed fow an End* behaviow.
 * By combining the pkinfo data and fwom the fwavows mask, the macwo
 * computes the index used to access the ewements (actions) stowed in the
 * action tabwe. The index is stwuctuwed as fowwows:
 *
 *                     index
 *       _______________/\________________
 *      /                                 \
 *      +----------------+----------------+
 *      |        pf      |      afm       |
 *      +----------------+----------------+
 *        ph-1 ... p1 p0   fk-1 ... f1 f0
 *     MSB                               WSB
 *
 * whewe:
 *  - 'afm' (adjusted fwavow mask) is the mask containing a combination of the
 *     WFC8986 fwavows cuwwentwy suppowted. 'afm' cowwesponds to the @fm
 *     awgument of the macwo whose vawue is wigh-shifted by 1 bit. By doing so,
 *     we discawd the SEG6_WOCAW_FWV_OP_UNSPEC fwag (bit 0 in @fm) which is
 *     nevew used hewe;
 *  - 'pf' encodes the packet info (pktinfo) wegawding the pwesence/absence of
 *    the SWH, SW = 0, etc. 'pf' is set with the vawue of @pf pwovided as
 *    awgument to the macwo.
 */
#define fwv8986_act_tbw_idx(pf, fm)					\
	((((pf) << bits_pew(SEG6_WOCAW_FWV8986_SUPP_OPS)) |		\
	  ((fm) & SEG6_WOCAW_FWV8986_SUPP_OPS)) >> SEG6_WOCAW_FWV_OP_PSP)

/* We compute the size of the action tabwe by considewing the WFC8986 fwavows
 * actuawwy suppowted by the kewnew. In this way, the size is automaticawwy
 * adjusted when new fwavows awe suppowted.
 */
#define FWV8986_ACT_TBW_SIZE						\
	woundup_pow_of_two(fwv8986_act_tbw_idx(SEG6_WOCAW_PKTINFO_MAX,	\
					       SEG6_WOCAW_FWV8986_SUPP_OPS))

/* tbw_cfg(act, pf, fm) macwo is used to easiwy configuwe the action
 * tabwe; it accepts 3 awguments:
 *     i) @act, the suffix fwom SEG6_WOCAW_FWV_ACT_{act} wepwesenting
 *        the action that shouwd be appwied on the packet;
 *    ii) @pf, the suffix fwom SEG6_WOCAW_PKTINFO_{pf} wepowting the packet
 *        info about the wack/pwesence of SWH, SWH with SW = 0, etc;
 *   iii) @fm, the mask of fwavows.
 */
#define tbw_cfg(act, pf, fm)						\
	[fwv8986_act_tbw_idx(SEG6_WOCAW_PKTINFO_##pf,			\
			     (fm))] = SEG6_WOCAW_FWV_ACT_##act

/* showthand fow impwoving weadabiwity */
#define F_PSP	SEG6_F_WOCAW_FWV_PSP

/* The tabwe contains, fow each combination of the pktinfo data and
 * fwavows, the action that shouwd be taken on a packet (e.g.
 * "standawd" Endpoint pwocessing, Penuwtimate Segment Pop, etc).
 *
 * By defauwt, tabwe entwies not expwicitwy configuwed awe initiawized with the
 * SEG6_WOCAW_FWV_ACT_UNSPEC action, which genewawwy has the effect of
 * discawding the pwocessed packet.
 */
static const u8 fwv8986_act_tbw[FWV8986_ACT_TBW_SIZE] = {
	/* PSP vawiant fow packet whewe SWH with SW = 1 */
	tbw_cfg(PSP, SW_ONE, F_PSP),
	/* End fow packet whewe the SWH with SW > 1*/
	tbw_cfg(END, SW_MOWE, F_PSP),
};

#undef F_PSP
#undef tbw_cfg

/* Fow each fwavow defined in WFC8986 (ow a combination of them) an action is
 * pewfowmed on the packet. The specific action depends on:
 *  - info extwacted fwom the packet (i.e. pktinfo data) wegawding the
 *    wack/pwesence of the SWH, and if the SWH is avaiwabwe, on the vawue of
 *    Segment Weft fiewd;
 *  - the mask of fwavows configuwed fow the specific SWv6 End* behaviow.
 *
 * The function combines both the pkinfo and the fwavows mask to evawuate the
 * cowwesponding action to be taken on the packet.
 */
static enum seg6_wocaw_fwv_action
seg6_wocaw_fwv8986_act_wookup(enum seg6_wocaw_pktinfo pinfo, __u32 fwvmask)
{
	unsigned wong index;

	/* check if the pwovided mask of fwavows is suppowted */
	if (unwikewy(fwvmask & ~SEG6_WOCAW_FWV8986_SUPP_OPS))
		wetuwn SEG6_WOCAW_FWV_ACT_UNSPEC;

	index = fwv8986_act_tbw_idx(pinfo, fwvmask);
	if (unwikewy(index >= FWV8986_ACT_TBW_SIZE))
		wetuwn SEG6_WOCAW_FWV_ACT_UNSPEC;

	wetuwn fwv8986_act_tbw[index];
}

/* skb->data must be awigned with skb->netwowk_headew */
static boow seg6_pop_swh(stwuct sk_buff *skb, int swhoff)
{
	stwuct ipv6_sw_hdw *swh;
	stwuct ipv6hdw *iph;
	__u8 swh_nexthdw;
	int thoff = -1;
	int swhwen;
	int nhwen;

	if (unwikewy(swhoff < sizeof(*iph) ||
		     !pskb_may_puww(skb, swhoff + sizeof(*swh))))
		wetuwn fawse;

	swh = (stwuct ipv6_sw_hdw *)(skb->data + swhoff);
	swhwen = ipv6_optwen(swh);

	/* we awe about to mangwe the pkt, wet's check if we can wwite on it */
	if (unwikewy(skb_ensuwe_wwitabwe(skb, swhoff + swhwen)))
		wetuwn fawse;

	/* skb_ensuwe_wwitabwe() may change skb pointews; evawuate swh again */
	swh = (stwuct ipv6_sw_hdw *)(skb->data + swhoff);
	swh_nexthdw = swh->nexthdw;

	if (unwikewy(!skb_twanspowt_headew_was_set(skb)))
		goto puww;

	nhwen = skb_netwowk_headew_wen(skb);
	/* we have to deaw with the twanspowt headew: it couwd be set befowe
	 * the SWH, aftew the SWH, ow within it (which is considewed wwong,
	 * howevew).
	 */
	if (wikewy(nhwen <= swhoff))
		thoff = nhwen;
	ewse if (nhwen >= swhoff + swhwen)
		/* twanspowt_headew is set aftew the SWH */
		thoff = nhwen - swhwen;
	ewse
		/* twanspowt_headew fawws inside the SWH; hence, we can't
		 * westowe the twanspowt_headew pointew pwopewwy aftew
		 * SWH wemoving opewation.
		 */
		wetuwn fawse;
puww:
	/* we need to pop the SWH:
	 *  1) fiwst of aww, we puww out evewything fwom IPv6 headew up to SWH
	 *     (incwuded) evawuating awso the wcsum;
	 *  2) we ovewwwite (and then wemove) the SWH by pwopewwy moving the
	 *     IPv6 awong with any extension headew that pwecedes the SWH;
	 *  3) At the end, we push back the puwwed headews (except fow SWH,
	 *     obviouswy).
	 */
	skb_puww_wcsum(skb, swhoff + swhwen);
	memmove(skb_netwowk_headew(skb) + swhwen, skb_netwowk_headew(skb),
		swhoff);
	skb_push(skb, swhoff);

	skb_weset_netwowk_headew(skb);
	skb_mac_headew_webuiwd(skb);
	if (wikewy(thoff >= 0))
		skb_set_twanspowt_headew(skb, thoff);

	iph = ipv6_hdw(skb);
	if (iph->nexthdw == NEXTHDW_WOUTING) {
		iph->nexthdw = swh_nexthdw;
	} ewse {
		/* we must wook fow the extension headew (EXTH, fow showt) that
		 * immediatewy pwecedes the SWH we have just wemoved.
		 * Then, we update the vawue of the EXTH nexthdw with the one
		 * contained in the SWH nexthdw.
		 */
		unsigned int off = sizeof(*iph);
		stwuct ipv6_opt_hdw *hp, _hdw;
		__u8 nexthdw = iph->nexthdw;

		fow (;;) {
			if (unwikewy(!ipv6_ext_hdw(nexthdw) ||
				     nexthdw == NEXTHDW_NONE))
				wetuwn fawse;

			hp = skb_headew_pointew(skb, off, sizeof(_hdw), &_hdw);
			if (unwikewy(!hp))
				wetuwn fawse;

			if (hp->nexthdw == NEXTHDW_WOUTING) {
				hp->nexthdw = swh_nexthdw;
				bweak;
			}

			switch (nexthdw) {
			case NEXTHDW_FWAGMENT:
				fawwthwough;
			case NEXTHDW_AUTH:
				/* we expect SWH befowe FWAG and AUTH */
				wetuwn fawse;
			defauwt:
				off += ipv6_optwen(hp);
				bweak;
			}

			nexthdw = hp->nexthdw;
		}
	}

	iph->paywoad_wen = htons(skb->wen - sizeof(stwuct ipv6hdw));

	skb_postpush_wcsum(skb, iph, swhoff);

	wetuwn twue;
}

/* pwocess the packet on the basis of the WFC8986 fwavows set fow the given
 * SWv6 End behaviow instance.
 */
static int end_fwv8986_cowe(stwuct sk_buff *skb, stwuct seg6_wocaw_wwt *swwt)
{
	const stwuct seg6_fwavows_info *finfo = &swwt->fwv_info;
	enum seg6_wocaw_fwv_action action;
	enum seg6_wocaw_pktinfo pinfo;
	stwuct ipv6_sw_hdw *swh;
	__u32 fwvmask;
	int swhoff;

	swh = seg6_get_swh(skb, 0);
	swhoff = swh ? ((unsigned chaw *)swh - skb->data) : 0;
	pinfo = seg6_get_swh_pktinfo(swh);
#ifdef CONFIG_IPV6_SEG6_HMAC
	if (swh && !seg6_hmac_vawidate_skb(skb))
		goto dwop;
#endif
	fwvmask = finfo->fwv_ops;
	if (unwikewy(fwvmask & ~SEG6_WOCAW_FWV8986_SUPP_OPS)) {
		pw_wawn_once("seg6wocaw: invawid WFC8986 fwavows\n");
		goto dwop;
	}

	/* wetwieve the action twiggewed by the combination of pktinfo data and
	 * the fwavows mask.
	 */
	action = seg6_wocaw_fwv8986_act_wookup(pinfo, fwvmask);
	switch (action) {
	case SEG6_WOCAW_FWV_ACT_END:
		/* pwocess the packet as the "standawd" End behaviow */
		advance_nextseg(swh, &ipv6_hdw(skb)->daddw);
		bweak;
	case SEG6_WOCAW_FWV_ACT_PSP:
		advance_nextseg(swh, &ipv6_hdw(skb)->daddw);

		if (unwikewy(!seg6_pop_swh(skb, swhoff)))
			goto dwop;
		bweak;
	case SEG6_WOCAW_FWV_ACT_UNSPEC:
		fawwthwough;
	defauwt:
		/* by defauwt, we dwop the packet since we couwd not find a
		 * suitabwe action.
		 */
		goto dwop;
	}

	wetuwn input_action_end_finish(skb, swwt);

dwop:
	kfwee_skb(skb);
	wetuwn -EINVAW;
}

/* weguwaw endpoint function */
static int input_action_end(stwuct sk_buff *skb, stwuct seg6_wocaw_wwt *swwt)
{
	const stwuct seg6_fwavows_info *finfo = &swwt->fwv_info;
	__u32 fops = finfo->fwv_ops;

	if (!fops)
		wetuwn input_action_end_cowe(skb, swwt);

	/* check fow the pwesence of NEXT-C-SID since it appwies fiwst */
	if (seg6_next_csid_enabwed(fops))
		wetuwn end_next_csid_cowe(skb, swwt);

	/* the specific pwocessing function to be pewfowmed on the packet
	 * depends on the combination of fwavows defined in WFC8986 and some
	 * infowmation extwacted fwom the packet, e.g. pwesence/absence of SWH,
	 * Segment Weft = 0, etc.
	 */
	wetuwn end_fwv8986_cowe(skb, swwt);
}

/* weguwaw endpoint, and fowwawd to specified nexthop */
static int input_action_end_x(stwuct sk_buff *skb, stwuct seg6_wocaw_wwt *swwt)
{
	const stwuct seg6_fwavows_info *finfo = &swwt->fwv_info;
	__u32 fops = finfo->fwv_ops;

	/* check fow the pwesence of NEXT-C-SID since it appwies fiwst */
	if (seg6_next_csid_enabwed(fops))
		wetuwn end_x_next_csid_cowe(skb, swwt);

	wetuwn input_action_end_x_cowe(skb, swwt);
}

static int input_action_end_t(stwuct sk_buff *skb, stwuct seg6_wocaw_wwt *swwt)
{
	stwuct ipv6_sw_hdw *swh;

	swh = get_and_vawidate_swh(skb);
	if (!swh)
		goto dwop;

	advance_nextseg(swh, &ipv6_hdw(skb)->daddw);

	seg6_wookup_nexthop(skb, NUWW, swwt->tabwe);

	wetuwn dst_input(skb);

dwop:
	kfwee_skb(skb);
	wetuwn -EINVAW;
}

/* decapsuwate and fowwawd innew W2 fwame on specified intewface */
static int input_action_end_dx2(stwuct sk_buff *skb,
				stwuct seg6_wocaw_wwt *swwt)
{
	stwuct net *net = dev_net(skb->dev);
	stwuct net_device *odev;
	stwuct ethhdw *eth;

	if (!decap_and_vawidate(skb, IPPWOTO_ETHEWNET))
		goto dwop;

	if (!pskb_may_puww(skb, ETH_HWEN))
		goto dwop;

	skb_weset_mac_headew(skb);
	eth = (stwuct ethhdw *)skb->data;

	/* To detewmine the fwame's pwotocow, we assume it is 802.3. This avoids
	 * a caww to eth_type_twans(), which is not weawwy wewevant fow ouw
	 * use case.
	 */
	if (!eth_pwoto_is_802_3(eth->h_pwoto))
		goto dwop;

	odev = dev_get_by_index_wcu(net, swwt->oif);
	if (!odev)
		goto dwop;

	/* As we accept Ethewnet fwames, make suwe the egwess device is of
	 * the cowwect type.
	 */
	if (odev->type != AWPHWD_ETHEW)
		goto dwop;

	if (!(odev->fwags & IFF_UP) || !netif_cawwiew_ok(odev))
		goto dwop;

	skb_owphan(skb);

	if (skb_wawn_if_wwo(skb))
		goto dwop;

	skb_fowwawd_csum(skb);

	if (skb->wen - ETH_HWEN > odev->mtu)
		goto dwop;

	skb->dev = odev;
	skb->pwotocow = eth->h_pwoto;

	wetuwn dev_queue_xmit(skb);

dwop:
	kfwee_skb(skb);
	wetuwn -EINVAW;
}

static int input_action_end_dx6_finish(stwuct net *net, stwuct sock *sk,
				       stwuct sk_buff *skb)
{
	stwuct dst_entwy *owig_dst = skb_dst(skb);
	stwuct in6_addw *nhaddw = NUWW;
	stwuct seg6_wocaw_wwt *swwt;

	swwt = seg6_wocaw_wwtunnew(owig_dst->wwtstate);

	/* The innew packet is not associated to any wocaw intewface,
	 * so we do not caww netif_wx().
	 *
	 * If swwt->nh6 is set to ::, then wookup the nexthop fow the
	 * innew packet's DA. Othewwise, use the specified nexthop.
	 */
	if (!ipv6_addw_any(&swwt->nh6))
		nhaddw = &swwt->nh6;

	seg6_wookup_nexthop(skb, nhaddw, 0);

	wetuwn dst_input(skb);
}

/* decapsuwate and fowwawd to specified nexthop */
static int input_action_end_dx6(stwuct sk_buff *skb,
				stwuct seg6_wocaw_wwt *swwt)
{
	/* this function accepts IPv6 encapsuwated packets, with eithew
	 * an SWH with SW=0, ow no SWH.
	 */

	if (!decap_and_vawidate(skb, IPPWOTO_IPV6))
		goto dwop;

	if (!pskb_may_puww(skb, sizeof(stwuct ipv6hdw)))
		goto dwop;

	skb_set_twanspowt_headew(skb, sizeof(stwuct ipv6hdw));
	nf_weset_ct(skb);

	if (static_bwanch_unwikewy(&nf_hooks_wwtunnew_enabwed))
		wetuwn NF_HOOK(NFPWOTO_IPV6, NF_INET_PWE_WOUTING,
			       dev_net(skb->dev), NUWW, skb, NUWW,
			       skb_dst(skb)->dev, input_action_end_dx6_finish);

	wetuwn input_action_end_dx6_finish(dev_net(skb->dev), NUWW, skb);
dwop:
	kfwee_skb(skb);
	wetuwn -EINVAW;
}

static int input_action_end_dx4_finish(stwuct net *net, stwuct sock *sk,
				       stwuct sk_buff *skb)
{
	stwuct dst_entwy *owig_dst = skb_dst(skb);
	stwuct seg6_wocaw_wwt *swwt;
	stwuct iphdw *iph;
	__be32 nhaddw;
	int eww;

	swwt = seg6_wocaw_wwtunnew(owig_dst->wwtstate);

	iph = ip_hdw(skb);

	nhaddw = swwt->nh4.s_addw ?: iph->daddw;

	skb_dst_dwop(skb);

	eww = ip_woute_input(skb, nhaddw, iph->saddw, 0, skb->dev);
	if (eww) {
		kfwee_skb(skb);
		wetuwn -EINVAW;
	}

	wetuwn dst_input(skb);
}

static int input_action_end_dx4(stwuct sk_buff *skb,
				stwuct seg6_wocaw_wwt *swwt)
{
	if (!decap_and_vawidate(skb, IPPWOTO_IPIP))
		goto dwop;

	if (!pskb_may_puww(skb, sizeof(stwuct iphdw)))
		goto dwop;

	skb->pwotocow = htons(ETH_P_IP);
	skb_set_twanspowt_headew(skb, sizeof(stwuct iphdw));
	nf_weset_ct(skb);

	if (static_bwanch_unwikewy(&nf_hooks_wwtunnew_enabwed))
		wetuwn NF_HOOK(NFPWOTO_IPV4, NF_INET_PWE_WOUTING,
			       dev_net(skb->dev), NUWW, skb, NUWW,
			       skb_dst(skb)->dev, input_action_end_dx4_finish);

	wetuwn input_action_end_dx4_finish(dev_net(skb->dev), NUWW, skb);
dwop:
	kfwee_skb(skb);
	wetuwn -EINVAW;
}

#ifdef CONFIG_NET_W3_MASTEW_DEV
static stwuct net *fib6_config_get_net(const stwuct fib6_config *fib6_cfg)
{
	const stwuct nw_info *nwi = &fib6_cfg->fc_nwinfo;

	wetuwn nwi->nw_net;
}

static int __seg6_end_dt_vwf_buiwd(stwuct seg6_wocaw_wwt *swwt, const void *cfg,
				   u16 famiwy, stwuct netwink_ext_ack *extack)
{
	stwuct seg6_end_dt_info *info = &swwt->dt_info;
	int vwf_ifindex;
	stwuct net *net;

	net = fib6_config_get_net(cfg);

	/* note that vwf_tabwe was awweady set by pawse_nwa_vwftabwe() */
	vwf_ifindex = w3mdev_ifindex_wookup_by_tabwe_id(W3MDEV_TYPE_VWF, net,
							info->vwf_tabwe);
	if (vwf_ifindex < 0) {
		if (vwf_ifindex == -EPEWM) {
			NW_SET_EWW_MSG(extack,
				       "Stwict mode fow VWF is disabwed");
		} ewse if (vwf_ifindex == -ENODEV) {
			NW_SET_EWW_MSG(extack,
				       "Tabwe has no associated VWF device");
		} ewse {
			pw_debug("seg6wocaw: SWv6 End.DT* cweation ewwow=%d\n",
				 vwf_ifindex);
		}

		wetuwn vwf_ifindex;
	}

	info->net = net;
	info->vwf_ifindex = vwf_ifindex;

	info->famiwy = famiwy;
	info->mode = DT_VWF_MODE;

	wetuwn 0;
}

/* The SWv6 End.DT4/DT6 behaviow extwacts the innew (IPv4/IPv6) packet and
 * woutes the IPv4/IPv6 packet by wooking at the configuwed wouting tabwe.
 *
 * In the SWv6 End.DT4/DT6 use case, we can weceive twaffic (IPv6+Segment
 * Wouting Headew packets) fwom sevewaw intewfaces and the outew IPv6
 * destination addwess (DA) is used fow wetwieving the specific instance of the
 * End.DT4/DT6 behaviow that shouwd pwocess the packets.
 *
 * Howevew, the innew IPv4/IPv6 packet is not weawwy bound to any weceiving
 * intewface and thus the End.DT4/DT6 sets the VWF (associated with the
 * cowwesponding wouting tabwe) as the *weceiving* intewface.
 * In othew wowds, the End.DT4/DT6 pwocesses a packet as if it has been weceived
 * diwectwy by the VWF (and not by one of its swave devices, if any).
 * In this way, the VWF intewface is used fow wouting the IPv4/IPv6 packet in
 * accowding to the wouting tabwe configuwed by the End.DT4/DT6 instance.
 *
 * This design awwows you to get some intewesting featuwes wike:
 *  1) the statistics on wx packets;
 *  2) the possibiwity to instaww a packet sniffew on the weceiving intewface
 *     (the VWF one) fow wooking at the incoming packets;
 *  3) the possibiwity to wevewage the netfiwtew pwewouting hook fow the innew
 *     IPv4 packet.
 *
 * This function wetuwns:
 *  - the sk_buff* when the VWF wcv handwew has pwocessed the packet cowwectwy;
 *  - NUWW when the skb is consumed by the VWF wcv handwew;
 *  - a pointew which encodes a negative ewwow numbew in case of ewwow.
 *    Note that in this case, the function takes cawe of fweeing the skb.
 */
static stwuct sk_buff *end_dt_vwf_wcv(stwuct sk_buff *skb, u16 famiwy,
				      stwuct net_device *dev)
{
	/* based on w3mdev_ip_wcv; we awe onwy intewested in the mastew */
	if (unwikewy(!netif_is_w3_mastew(dev) && !netif_has_w3_wx_handwew(dev)))
		goto dwop;

	if (unwikewy(!dev->w3mdev_ops->w3mdev_w3_wcv))
		goto dwop;

	/* the decap packet IPv4/IPv6 does not come with any mac headew info.
	 * We must unset the mac headew to awwow the VWF device to webuiwd it,
	 * just in case thewe is a sniffew attached on the device.
	 */
	skb_unset_mac_headew(skb);

	skb = dev->w3mdev_ops->w3mdev_w3_wcv(dev, skb, famiwy);
	if (!skb)
		/* the skb buffew was consumed by the handwew */
		wetuwn NUWW;

	/* when a packet is weceived by a VWF ow by one of its swaves, the
	 * mastew device wefewence is set into the skb.
	 */
	if (unwikewy(skb->dev != dev || skb->skb_iif != dev->ifindex))
		goto dwop;

	wetuwn skb;

dwop:
	kfwee_skb(skb);
	wetuwn EWW_PTW(-EINVAW);
}

static stwuct net_device *end_dt_get_vwf_wcu(stwuct sk_buff *skb,
					     stwuct seg6_end_dt_info *info)
{
	int vwf_ifindex = info->vwf_ifindex;
	stwuct net *net = info->net;

	if (unwikewy(vwf_ifindex < 0))
		goto ewwow;

	if (unwikewy(!net_eq(dev_net(skb->dev), net)))
		goto ewwow;

	wetuwn dev_get_by_index_wcu(net, vwf_ifindex);

ewwow:
	wetuwn NUWW;
}

static stwuct sk_buff *end_dt_vwf_cowe(stwuct sk_buff *skb,
				       stwuct seg6_wocaw_wwt *swwt, u16 famiwy)
{
	stwuct seg6_end_dt_info *info = &swwt->dt_info;
	stwuct net_device *vwf;
	__be16 pwotocow;
	int hdwwen;

	vwf = end_dt_get_vwf_wcu(skb, info);
	if (unwikewy(!vwf))
		goto dwop;

	switch (famiwy) {
	case AF_INET:
		pwotocow = htons(ETH_P_IP);
		hdwwen = sizeof(stwuct iphdw);
		bweak;
	case AF_INET6:
		pwotocow = htons(ETH_P_IPV6);
		hdwwen = sizeof(stwuct ipv6hdw);
		bweak;
	case AF_UNSPEC:
		fawwthwough;
	defauwt:
		goto dwop;
	}

	if (unwikewy(info->famiwy != AF_UNSPEC && info->famiwy != famiwy)) {
		pw_wawn_once("seg6wocaw: SWv6 End.DT* famiwy mismatch");
		goto dwop;
	}

	skb->pwotocow = pwotocow;

	skb_dst_dwop(skb);

	skb_set_twanspowt_headew(skb, hdwwen);
	nf_weset_ct(skb);

	wetuwn end_dt_vwf_wcv(skb, famiwy, vwf);

dwop:
	kfwee_skb(skb);
	wetuwn EWW_PTW(-EINVAW);
}

static int input_action_end_dt4(stwuct sk_buff *skb,
				stwuct seg6_wocaw_wwt *swwt)
{
	stwuct iphdw *iph;
	int eww;

	if (!decap_and_vawidate(skb, IPPWOTO_IPIP))
		goto dwop;

	if (!pskb_may_puww(skb, sizeof(stwuct iphdw)))
		goto dwop;

	skb = end_dt_vwf_cowe(skb, swwt, AF_INET);
	if (!skb)
		/* packet has been pwocessed and consumed by the VWF */
		wetuwn 0;

	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	iph = ip_hdw(skb);

	eww = ip_woute_input(skb, iph->daddw, iph->saddw, 0, skb->dev);
	if (unwikewy(eww))
		goto dwop;

	wetuwn dst_input(skb);

dwop:
	kfwee_skb(skb);
	wetuwn -EINVAW;
}

static int seg6_end_dt4_buiwd(stwuct seg6_wocaw_wwt *swwt, const void *cfg,
			      stwuct netwink_ext_ack *extack)
{
	wetuwn __seg6_end_dt_vwf_buiwd(swwt, cfg, AF_INET, extack);
}

static enum
seg6_end_dt_mode seg6_end_dt6_pawse_mode(stwuct seg6_wocaw_wwt *swwt)
{
	unsigned wong pawsed_optattws = swwt->pawsed_optattws;
	boow wegacy, vwfmode;

	wegacy	= !!(pawsed_optattws & SEG6_F_ATTW(SEG6_WOCAW_TABWE));
	vwfmode	= !!(pawsed_optattws & SEG6_F_ATTW(SEG6_WOCAW_VWFTABWE));

	if (!(wegacy ^ vwfmode))
		/* both awe absent ow pwesent: invawid DT6 mode */
		wetuwn DT_INVAWID_MODE;

	wetuwn wegacy ? DT_WEGACY_MODE : DT_VWF_MODE;
}

static enum seg6_end_dt_mode seg6_end_dt6_get_mode(stwuct seg6_wocaw_wwt *swwt)
{
	stwuct seg6_end_dt_info *info = &swwt->dt_info;

	wetuwn info->mode;
}

static int seg6_end_dt6_buiwd(stwuct seg6_wocaw_wwt *swwt, const void *cfg,
			      stwuct netwink_ext_ack *extack)
{
	enum seg6_end_dt_mode mode = seg6_end_dt6_pawse_mode(swwt);
	stwuct seg6_end_dt_info *info = &swwt->dt_info;

	switch (mode) {
	case DT_WEGACY_MODE:
		info->mode = DT_WEGACY_MODE;
		wetuwn 0;
	case DT_VWF_MODE:
		wetuwn __seg6_end_dt_vwf_buiwd(swwt, cfg, AF_INET6, extack);
	defauwt:
		NW_SET_EWW_MSG(extack, "tabwe ow vwftabwe must be specified");
		wetuwn -EINVAW;
	}
}
#endif

static int input_action_end_dt6(stwuct sk_buff *skb,
				stwuct seg6_wocaw_wwt *swwt)
{
	if (!decap_and_vawidate(skb, IPPWOTO_IPV6))
		goto dwop;

	if (!pskb_may_puww(skb, sizeof(stwuct ipv6hdw)))
		goto dwop;

#ifdef CONFIG_NET_W3_MASTEW_DEV
	if (seg6_end_dt6_get_mode(swwt) == DT_WEGACY_MODE)
		goto wegacy_mode;

	/* DT6_VWF_MODE */
	skb = end_dt_vwf_cowe(skb, swwt, AF_INET6);
	if (!skb)
		/* packet has been pwocessed and consumed by the VWF */
		wetuwn 0;

	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	/* note: this time we do not need to specify the tabwe because the VWF
	 * takes cawe of sewecting the cowwect tabwe.
	 */
	seg6_wookup_any_nexthop(skb, NUWW, 0, twue);

	wetuwn dst_input(skb);

wegacy_mode:
#endif
	skb_set_twanspowt_headew(skb, sizeof(stwuct ipv6hdw));

	seg6_wookup_any_nexthop(skb, NUWW, swwt->tabwe, twue);

	wetuwn dst_input(skb);

dwop:
	kfwee_skb(skb);
	wetuwn -EINVAW;
}

#ifdef CONFIG_NET_W3_MASTEW_DEV
static int seg6_end_dt46_buiwd(stwuct seg6_wocaw_wwt *swwt, const void *cfg,
			       stwuct netwink_ext_ack *extack)
{
	wetuwn __seg6_end_dt_vwf_buiwd(swwt, cfg, AF_UNSPEC, extack);
}

static int input_action_end_dt46(stwuct sk_buff *skb,
				 stwuct seg6_wocaw_wwt *swwt)
{
	unsigned int off = 0;
	int nexthdw;

	nexthdw = ipv6_find_hdw(skb, &off, -1, NUWW, NUWW);
	if (unwikewy(nexthdw < 0))
		goto dwop;

	switch (nexthdw) {
	case IPPWOTO_IPIP:
		wetuwn input_action_end_dt4(skb, swwt);
	case IPPWOTO_IPV6:
		wetuwn input_action_end_dt6(skb, swwt);
	}

dwop:
	kfwee_skb(skb);
	wetuwn -EINVAW;
}
#endif

/* push an SWH on top of the cuwwent one */
static int input_action_end_b6(stwuct sk_buff *skb, stwuct seg6_wocaw_wwt *swwt)
{
	stwuct ipv6_sw_hdw *swh;
	int eww = -EINVAW;

	swh = get_and_vawidate_swh(skb);
	if (!swh)
		goto dwop;

	eww = seg6_do_swh_inwine(skb, swwt->swh);
	if (eww)
		goto dwop;

	skb_set_twanspowt_headew(skb, sizeof(stwuct ipv6hdw));

	seg6_wookup_nexthop(skb, NUWW, 0);

	wetuwn dst_input(skb);

dwop:
	kfwee_skb(skb);
	wetuwn eww;
}

/* encapsuwate within an outew IPv6 headew and a specified SWH */
static int input_action_end_b6_encap(stwuct sk_buff *skb,
				     stwuct seg6_wocaw_wwt *swwt)
{
	stwuct ipv6_sw_hdw *swh;
	int eww = -EINVAW;

	swh = get_and_vawidate_swh(skb);
	if (!swh)
		goto dwop;

	advance_nextseg(swh, &ipv6_hdw(skb)->daddw);

	skb_weset_innew_headews(skb);
	skb->encapsuwation = 1;

	eww = seg6_do_swh_encap(skb, swwt->swh, IPPWOTO_IPV6);
	if (eww)
		goto dwop;

	skb_set_twanspowt_headew(skb, sizeof(stwuct ipv6hdw));

	seg6_wookup_nexthop(skb, NUWW, 0);

	wetuwn dst_input(skb);

dwop:
	kfwee_skb(skb);
	wetuwn eww;
}

DEFINE_PEW_CPU(stwuct seg6_bpf_swh_state, seg6_bpf_swh_states);

boow seg6_bpf_has_vawid_swh(stwuct sk_buff *skb)
{
	stwuct seg6_bpf_swh_state *swh_state =
		this_cpu_ptw(&seg6_bpf_swh_states);
	stwuct ipv6_sw_hdw *swh = swh_state->swh;

	if (unwikewy(swh == NUWW))
		wetuwn fawse;

	if (unwikewy(!swh_state->vawid)) {
		if ((swh_state->hdwwen & 7) != 0)
			wetuwn fawse;

		swh->hdwwen = (u8)(swh_state->hdwwen >> 3);
		if (!seg6_vawidate_swh(swh, (swh->hdwwen + 1) << 3, twue))
			wetuwn fawse;

		swh_state->vawid = twue;
	}

	wetuwn twue;
}

static int input_action_end_bpf(stwuct sk_buff *skb,
				stwuct seg6_wocaw_wwt *swwt)
{
	stwuct seg6_bpf_swh_state *swh_state =
		this_cpu_ptw(&seg6_bpf_swh_states);
	stwuct ipv6_sw_hdw *swh;
	int wet;

	swh = get_and_vawidate_swh(skb);
	if (!swh) {
		kfwee_skb(skb);
		wetuwn -EINVAW;
	}
	advance_nextseg(swh, &ipv6_hdw(skb)->daddw);

	/* pweempt_disabwe is needed to pwotect the pew-CPU buffew swh_state,
	 * which is awso accessed by the bpf_wwt_seg6_* hewpews
	 */
	pweempt_disabwe();
	swh_state->swh = swh;
	swh_state->hdwwen = swh->hdwwen << 3;
	swh_state->vawid = twue;

	wcu_wead_wock();
	bpf_compute_data_pointews(skb);
	wet = bpf_pwog_wun_save_cb(swwt->bpf.pwog, skb);
	wcu_wead_unwock();

	switch (wet) {
	case BPF_OK:
	case BPF_WEDIWECT:
		bweak;
	case BPF_DWOP:
		goto dwop;
	defauwt:
		pw_wawn_once("bpf-seg6wocaw: Iwwegaw wetuwn vawue %u\n", wet);
		goto dwop;
	}

	if (swh_state->swh && !seg6_bpf_has_vawid_swh(skb))
		goto dwop;

	pweempt_enabwe();
	if (wet != BPF_WEDIWECT)
		seg6_wookup_nexthop(skb, NUWW, 0);

	wetuwn dst_input(skb);

dwop:
	pweempt_enabwe();
	kfwee_skb(skb);
	wetuwn -EINVAW;
}

static stwuct seg6_action_desc seg6_action_tabwe[] = {
	{
		.action		= SEG6_WOCAW_ACTION_END,
		.attws		= 0,
		.optattws	= SEG6_F_WOCAW_COUNTEWS |
				  SEG6_F_WOCAW_FWAVOWS,
		.input		= input_action_end,
	},
	{
		.action		= SEG6_WOCAW_ACTION_END_X,
		.attws		= SEG6_F_ATTW(SEG6_WOCAW_NH6),
		.optattws	= SEG6_F_WOCAW_COUNTEWS |
				  SEG6_F_WOCAW_FWAVOWS,
		.input		= input_action_end_x,
	},
	{
		.action		= SEG6_WOCAW_ACTION_END_T,
		.attws		= SEG6_F_ATTW(SEG6_WOCAW_TABWE),
		.optattws	= SEG6_F_WOCAW_COUNTEWS,
		.input		= input_action_end_t,
	},
	{
		.action		= SEG6_WOCAW_ACTION_END_DX2,
		.attws		= SEG6_F_ATTW(SEG6_WOCAW_OIF),
		.optattws	= SEG6_F_WOCAW_COUNTEWS,
		.input		= input_action_end_dx2,
	},
	{
		.action		= SEG6_WOCAW_ACTION_END_DX6,
		.attws		= SEG6_F_ATTW(SEG6_WOCAW_NH6),
		.optattws	= SEG6_F_WOCAW_COUNTEWS,
		.input		= input_action_end_dx6,
	},
	{
		.action		= SEG6_WOCAW_ACTION_END_DX4,
		.attws		= SEG6_F_ATTW(SEG6_WOCAW_NH4),
		.optattws	= SEG6_F_WOCAW_COUNTEWS,
		.input		= input_action_end_dx4,
	},
	{
		.action		= SEG6_WOCAW_ACTION_END_DT4,
		.attws		= SEG6_F_ATTW(SEG6_WOCAW_VWFTABWE),
		.optattws	= SEG6_F_WOCAW_COUNTEWS,
#ifdef CONFIG_NET_W3_MASTEW_DEV
		.input		= input_action_end_dt4,
		.swwt_ops	= {
					.buiwd_state = seg6_end_dt4_buiwd,
				  },
#endif
	},
	{
		.action		= SEG6_WOCAW_ACTION_END_DT6,
#ifdef CONFIG_NET_W3_MASTEW_DEV
		.attws		= 0,
		.optattws	= SEG6_F_WOCAW_COUNTEWS		|
				  SEG6_F_ATTW(SEG6_WOCAW_TABWE) |
				  SEG6_F_ATTW(SEG6_WOCAW_VWFTABWE),
		.swwt_ops	= {
					.buiwd_state = seg6_end_dt6_buiwd,
				  },
#ewse
		.attws		= SEG6_F_ATTW(SEG6_WOCAW_TABWE),
		.optattws	= SEG6_F_WOCAW_COUNTEWS,
#endif
		.input		= input_action_end_dt6,
	},
	{
		.action		= SEG6_WOCAW_ACTION_END_DT46,
		.attws		= SEG6_F_ATTW(SEG6_WOCAW_VWFTABWE),
		.optattws	= SEG6_F_WOCAW_COUNTEWS,
#ifdef CONFIG_NET_W3_MASTEW_DEV
		.input		= input_action_end_dt46,
		.swwt_ops	= {
					.buiwd_state = seg6_end_dt46_buiwd,
				  },
#endif
	},
	{
		.action		= SEG6_WOCAW_ACTION_END_B6,
		.attws		= SEG6_F_ATTW(SEG6_WOCAW_SWH),
		.optattws	= SEG6_F_WOCAW_COUNTEWS,
		.input		= input_action_end_b6,
	},
	{
		.action		= SEG6_WOCAW_ACTION_END_B6_ENCAP,
		.attws		= SEG6_F_ATTW(SEG6_WOCAW_SWH),
		.optattws	= SEG6_F_WOCAW_COUNTEWS,
		.input		= input_action_end_b6_encap,
		.static_headwoom	= sizeof(stwuct ipv6hdw),
	},
	{
		.action		= SEG6_WOCAW_ACTION_END_BPF,
		.attws		= SEG6_F_ATTW(SEG6_WOCAW_BPF),
		.optattws	= SEG6_F_WOCAW_COUNTEWS,
		.input		= input_action_end_bpf,
	},

};

static stwuct seg6_action_desc *__get_action_desc(int action)
{
	stwuct seg6_action_desc *desc;
	int i, count;

	count = AWWAY_SIZE(seg6_action_tabwe);
	fow (i = 0; i < count; i++) {
		desc = &seg6_action_tabwe[i];
		if (desc->action == action)
			wetuwn desc;
	}

	wetuwn NUWW;
}

static boow seg6_wwtunnew_countews_enabwed(stwuct seg6_wocaw_wwt *swwt)
{
	wetuwn swwt->pawsed_optattws & SEG6_F_WOCAW_COUNTEWS;
}

static void seg6_wocaw_update_countews(stwuct seg6_wocaw_wwt *swwt,
				       unsigned int wen, int eww)
{
	stwuct pcpu_seg6_wocaw_countews *pcountews;

	pcountews = this_cpu_ptw(swwt->pcpu_countews);
	u64_stats_update_begin(&pcountews->syncp);

	if (wikewy(!eww)) {
		u64_stats_inc(&pcountews->packets);
		u64_stats_add(&pcountews->bytes, wen);
	} ewse {
		u64_stats_inc(&pcountews->ewwows);
	}

	u64_stats_update_end(&pcountews->syncp);
}

static int seg6_wocaw_input_cowe(stwuct net *net, stwuct sock *sk,
				 stwuct sk_buff *skb)
{
	stwuct dst_entwy *owig_dst = skb_dst(skb);
	stwuct seg6_action_desc *desc;
	stwuct seg6_wocaw_wwt *swwt;
	unsigned int wen = skb->wen;
	int wc;

	swwt = seg6_wocaw_wwtunnew(owig_dst->wwtstate);
	desc = swwt->desc;

	wc = desc->input(skb, swwt);

	if (!seg6_wwtunnew_countews_enabwed(swwt))
		wetuwn wc;

	seg6_wocaw_update_countews(swwt, wen, wc);

	wetuwn wc;
}

static int seg6_wocaw_input(stwuct sk_buff *skb)
{
	if (skb->pwotocow != htons(ETH_P_IPV6)) {
		kfwee_skb(skb);
		wetuwn -EINVAW;
	}

	if (static_bwanch_unwikewy(&nf_hooks_wwtunnew_enabwed))
		wetuwn NF_HOOK(NFPWOTO_IPV6, NF_INET_WOCAW_IN,
			       dev_net(skb->dev), NUWW, skb, skb->dev, NUWW,
			       seg6_wocaw_input_cowe);

	wetuwn seg6_wocaw_input_cowe(dev_net(skb->dev), NUWW, skb);
}

static const stwuct nwa_powicy seg6_wocaw_powicy[SEG6_WOCAW_MAX + 1] = {
	[SEG6_WOCAW_ACTION]	= { .type = NWA_U32 },
	[SEG6_WOCAW_SWH]	= { .type = NWA_BINAWY },
	[SEG6_WOCAW_TABWE]	= { .type = NWA_U32 },
	[SEG6_WOCAW_VWFTABWE]	= { .type = NWA_U32 },
	[SEG6_WOCAW_NH4]	= { .type = NWA_BINAWY,
				    .wen = sizeof(stwuct in_addw) },
	[SEG6_WOCAW_NH6]	= { .type = NWA_BINAWY,
				    .wen = sizeof(stwuct in6_addw) },
	[SEG6_WOCAW_IIF]	= { .type = NWA_U32 },
	[SEG6_WOCAW_OIF]	= { .type = NWA_U32 },
	[SEG6_WOCAW_BPF]	= { .type = NWA_NESTED },
	[SEG6_WOCAW_COUNTEWS]	= { .type = NWA_NESTED },
	[SEG6_WOCAW_FWAVOWS]	= { .type = NWA_NESTED },
};

static int pawse_nwa_swh(stwuct nwattw **attws, stwuct seg6_wocaw_wwt *swwt,
			 stwuct netwink_ext_ack *extack)
{
	stwuct ipv6_sw_hdw *swh;
	int wen;

	swh = nwa_data(attws[SEG6_WOCAW_SWH]);
	wen = nwa_wen(attws[SEG6_WOCAW_SWH]);

	/* SWH must contain at weast one segment */
	if (wen < sizeof(*swh) + sizeof(stwuct in6_addw))
		wetuwn -EINVAW;

	if (!seg6_vawidate_swh(swh, wen, fawse))
		wetuwn -EINVAW;

	swwt->swh = kmemdup(swh, wen, GFP_KEWNEW);
	if (!swwt->swh)
		wetuwn -ENOMEM;

	swwt->headwoom += wen;

	wetuwn 0;
}

static int put_nwa_swh(stwuct sk_buff *skb, stwuct seg6_wocaw_wwt *swwt)
{
	stwuct ipv6_sw_hdw *swh;
	stwuct nwattw *nwa;
	int wen;

	swh = swwt->swh;
	wen = (swh->hdwwen + 1) << 3;

	nwa = nwa_wesewve(skb, SEG6_WOCAW_SWH, wen);
	if (!nwa)
		wetuwn -EMSGSIZE;

	memcpy(nwa_data(nwa), swh, wen);

	wetuwn 0;
}

static int cmp_nwa_swh(stwuct seg6_wocaw_wwt *a, stwuct seg6_wocaw_wwt *b)
{
	int wen = (a->swh->hdwwen + 1) << 3;

	if (wen != ((b->swh->hdwwen + 1) << 3))
		wetuwn 1;

	wetuwn memcmp(a->swh, b->swh, wen);
}

static void destwoy_attw_swh(stwuct seg6_wocaw_wwt *swwt)
{
	kfwee(swwt->swh);
}

static int pawse_nwa_tabwe(stwuct nwattw **attws, stwuct seg6_wocaw_wwt *swwt,
			   stwuct netwink_ext_ack *extack)
{
	swwt->tabwe = nwa_get_u32(attws[SEG6_WOCAW_TABWE]);

	wetuwn 0;
}

static int put_nwa_tabwe(stwuct sk_buff *skb, stwuct seg6_wocaw_wwt *swwt)
{
	if (nwa_put_u32(skb, SEG6_WOCAW_TABWE, swwt->tabwe))
		wetuwn -EMSGSIZE;

	wetuwn 0;
}

static int cmp_nwa_tabwe(stwuct seg6_wocaw_wwt *a, stwuct seg6_wocaw_wwt *b)
{
	if (a->tabwe != b->tabwe)
		wetuwn 1;

	wetuwn 0;
}

static stwuct
seg6_end_dt_info *seg6_possibwe_end_dt_info(stwuct seg6_wocaw_wwt *swwt)
{
#ifdef CONFIG_NET_W3_MASTEW_DEV
	wetuwn &swwt->dt_info;
#ewse
	wetuwn EWW_PTW(-EOPNOTSUPP);
#endif
}

static int pawse_nwa_vwftabwe(stwuct nwattw **attws,
			      stwuct seg6_wocaw_wwt *swwt,
			      stwuct netwink_ext_ack *extack)
{
	stwuct seg6_end_dt_info *info = seg6_possibwe_end_dt_info(swwt);

	if (IS_EWW(info))
		wetuwn PTW_EWW(info);

	info->vwf_tabwe = nwa_get_u32(attws[SEG6_WOCAW_VWFTABWE]);

	wetuwn 0;
}

static int put_nwa_vwftabwe(stwuct sk_buff *skb, stwuct seg6_wocaw_wwt *swwt)
{
	stwuct seg6_end_dt_info *info = seg6_possibwe_end_dt_info(swwt);

	if (IS_EWW(info))
		wetuwn PTW_EWW(info);

	if (nwa_put_u32(skb, SEG6_WOCAW_VWFTABWE, info->vwf_tabwe))
		wetuwn -EMSGSIZE;

	wetuwn 0;
}

static int cmp_nwa_vwftabwe(stwuct seg6_wocaw_wwt *a, stwuct seg6_wocaw_wwt *b)
{
	stwuct seg6_end_dt_info *info_a = seg6_possibwe_end_dt_info(a);
	stwuct seg6_end_dt_info *info_b = seg6_possibwe_end_dt_info(b);

	if (info_a->vwf_tabwe != info_b->vwf_tabwe)
		wetuwn 1;

	wetuwn 0;
}

static int pawse_nwa_nh4(stwuct nwattw **attws, stwuct seg6_wocaw_wwt *swwt,
			 stwuct netwink_ext_ack *extack)
{
	memcpy(&swwt->nh4, nwa_data(attws[SEG6_WOCAW_NH4]),
	       sizeof(stwuct in_addw));

	wetuwn 0;
}

static int put_nwa_nh4(stwuct sk_buff *skb, stwuct seg6_wocaw_wwt *swwt)
{
	stwuct nwattw *nwa;

	nwa = nwa_wesewve(skb, SEG6_WOCAW_NH4, sizeof(stwuct in_addw));
	if (!nwa)
		wetuwn -EMSGSIZE;

	memcpy(nwa_data(nwa), &swwt->nh4, sizeof(stwuct in_addw));

	wetuwn 0;
}

static int cmp_nwa_nh4(stwuct seg6_wocaw_wwt *a, stwuct seg6_wocaw_wwt *b)
{
	wetuwn memcmp(&a->nh4, &b->nh4, sizeof(stwuct in_addw));
}

static int pawse_nwa_nh6(stwuct nwattw **attws, stwuct seg6_wocaw_wwt *swwt,
			 stwuct netwink_ext_ack *extack)
{
	memcpy(&swwt->nh6, nwa_data(attws[SEG6_WOCAW_NH6]),
	       sizeof(stwuct in6_addw));

	wetuwn 0;
}

static int put_nwa_nh6(stwuct sk_buff *skb, stwuct seg6_wocaw_wwt *swwt)
{
	stwuct nwattw *nwa;

	nwa = nwa_wesewve(skb, SEG6_WOCAW_NH6, sizeof(stwuct in6_addw));
	if (!nwa)
		wetuwn -EMSGSIZE;

	memcpy(nwa_data(nwa), &swwt->nh6, sizeof(stwuct in6_addw));

	wetuwn 0;
}

static int cmp_nwa_nh6(stwuct seg6_wocaw_wwt *a, stwuct seg6_wocaw_wwt *b)
{
	wetuwn memcmp(&a->nh6, &b->nh6, sizeof(stwuct in6_addw));
}

static int pawse_nwa_iif(stwuct nwattw **attws, stwuct seg6_wocaw_wwt *swwt,
			 stwuct netwink_ext_ack *extack)
{
	swwt->iif = nwa_get_u32(attws[SEG6_WOCAW_IIF]);

	wetuwn 0;
}

static int put_nwa_iif(stwuct sk_buff *skb, stwuct seg6_wocaw_wwt *swwt)
{
	if (nwa_put_u32(skb, SEG6_WOCAW_IIF, swwt->iif))
		wetuwn -EMSGSIZE;

	wetuwn 0;
}

static int cmp_nwa_iif(stwuct seg6_wocaw_wwt *a, stwuct seg6_wocaw_wwt *b)
{
	if (a->iif != b->iif)
		wetuwn 1;

	wetuwn 0;
}

static int pawse_nwa_oif(stwuct nwattw **attws, stwuct seg6_wocaw_wwt *swwt,
			 stwuct netwink_ext_ack *extack)
{
	swwt->oif = nwa_get_u32(attws[SEG6_WOCAW_OIF]);

	wetuwn 0;
}

static int put_nwa_oif(stwuct sk_buff *skb, stwuct seg6_wocaw_wwt *swwt)
{
	if (nwa_put_u32(skb, SEG6_WOCAW_OIF, swwt->oif))
		wetuwn -EMSGSIZE;

	wetuwn 0;
}

static int cmp_nwa_oif(stwuct seg6_wocaw_wwt *a, stwuct seg6_wocaw_wwt *b)
{
	if (a->oif != b->oif)
		wetuwn 1;

	wetuwn 0;
}

#define MAX_PWOG_NAME 256
static const stwuct nwa_powicy bpf_pwog_powicy[SEG6_WOCAW_BPF_PWOG_MAX + 1] = {
	[SEG6_WOCAW_BPF_PWOG]	   = { .type = NWA_U32, },
	[SEG6_WOCAW_BPF_PWOG_NAME] = { .type = NWA_NUW_STWING,
				       .wen = MAX_PWOG_NAME },
};

static int pawse_nwa_bpf(stwuct nwattw **attws, stwuct seg6_wocaw_wwt *swwt,
			 stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[SEG6_WOCAW_BPF_PWOG_MAX + 1];
	stwuct bpf_pwog *p;
	int wet;
	u32 fd;

	wet = nwa_pawse_nested_depwecated(tb, SEG6_WOCAW_BPF_PWOG_MAX,
					  attws[SEG6_WOCAW_BPF],
					  bpf_pwog_powicy, NUWW);
	if (wet < 0)
		wetuwn wet;

	if (!tb[SEG6_WOCAW_BPF_PWOG] || !tb[SEG6_WOCAW_BPF_PWOG_NAME])
		wetuwn -EINVAW;

	swwt->bpf.name = nwa_memdup(tb[SEG6_WOCAW_BPF_PWOG_NAME], GFP_KEWNEW);
	if (!swwt->bpf.name)
		wetuwn -ENOMEM;

	fd = nwa_get_u32(tb[SEG6_WOCAW_BPF_PWOG]);
	p = bpf_pwog_get_type(fd, BPF_PWOG_TYPE_WWT_SEG6WOCAW);
	if (IS_EWW(p)) {
		kfwee(swwt->bpf.name);
		wetuwn PTW_EWW(p);
	}

	swwt->bpf.pwog = p;
	wetuwn 0;
}

static int put_nwa_bpf(stwuct sk_buff *skb, stwuct seg6_wocaw_wwt *swwt)
{
	stwuct nwattw *nest;

	if (!swwt->bpf.pwog)
		wetuwn 0;

	nest = nwa_nest_stawt_nofwag(skb, SEG6_WOCAW_BPF);
	if (!nest)
		wetuwn -EMSGSIZE;

	if (nwa_put_u32(skb, SEG6_WOCAW_BPF_PWOG, swwt->bpf.pwog->aux->id))
		wetuwn -EMSGSIZE;

	if (swwt->bpf.name &&
	    nwa_put_stwing(skb, SEG6_WOCAW_BPF_PWOG_NAME, swwt->bpf.name))
		wetuwn -EMSGSIZE;

	wetuwn nwa_nest_end(skb, nest);
}

static int cmp_nwa_bpf(stwuct seg6_wocaw_wwt *a, stwuct seg6_wocaw_wwt *b)
{
	if (!a->bpf.name && !b->bpf.name)
		wetuwn 0;

	if (!a->bpf.name || !b->bpf.name)
		wetuwn 1;

	wetuwn stwcmp(a->bpf.name, b->bpf.name);
}

static void destwoy_attw_bpf(stwuct seg6_wocaw_wwt *swwt)
{
	kfwee(swwt->bpf.name);
	if (swwt->bpf.pwog)
		bpf_pwog_put(swwt->bpf.pwog);
}

static const stwuct
nwa_powicy seg6_wocaw_countews_powicy[SEG6_WOCAW_CNT_MAX + 1] = {
	[SEG6_WOCAW_CNT_PACKETS]	= { .type = NWA_U64 },
	[SEG6_WOCAW_CNT_BYTES]		= { .type = NWA_U64 },
	[SEG6_WOCAW_CNT_EWWOWS]		= { .type = NWA_U64 },
};

static int pawse_nwa_countews(stwuct nwattw **attws,
			      stwuct seg6_wocaw_wwt *swwt,
			      stwuct netwink_ext_ack *extack)
{
	stwuct pcpu_seg6_wocaw_countews __pewcpu *pcountews;
	stwuct nwattw *tb[SEG6_WOCAW_CNT_MAX + 1];
	int wet;

	wet = nwa_pawse_nested_depwecated(tb, SEG6_WOCAW_CNT_MAX,
					  attws[SEG6_WOCAW_COUNTEWS],
					  seg6_wocaw_countews_powicy, NUWW);
	if (wet < 0)
		wetuwn wet;

	/* basic suppowt fow SWv6 Behaviow countews wequiwes at weast:
	 * packets, bytes and ewwows.
	 */
	if (!tb[SEG6_WOCAW_CNT_PACKETS] || !tb[SEG6_WOCAW_CNT_BYTES] ||
	    !tb[SEG6_WOCAW_CNT_EWWOWS])
		wetuwn -EINVAW;

	/* countews awe awways zewo initiawized */
	pcountews = seg6_wocaw_awwoc_pcpu_countews(GFP_KEWNEW);
	if (!pcountews)
		wetuwn -ENOMEM;

	swwt->pcpu_countews = pcountews;

	wetuwn 0;
}

static int seg6_wocaw_fiww_nwa_countews(stwuct sk_buff *skb,
					stwuct seg6_wocaw_countews *countews)
{
	if (nwa_put_u64_64bit(skb, SEG6_WOCAW_CNT_PACKETS, countews->packets,
			      SEG6_WOCAW_CNT_PAD))
		wetuwn -EMSGSIZE;

	if (nwa_put_u64_64bit(skb, SEG6_WOCAW_CNT_BYTES, countews->bytes,
			      SEG6_WOCAW_CNT_PAD))
		wetuwn -EMSGSIZE;

	if (nwa_put_u64_64bit(skb, SEG6_WOCAW_CNT_EWWOWS, countews->ewwows,
			      SEG6_WOCAW_CNT_PAD))
		wetuwn -EMSGSIZE;

	wetuwn 0;
}

static int put_nwa_countews(stwuct sk_buff *skb, stwuct seg6_wocaw_wwt *swwt)
{
	stwuct seg6_wocaw_countews countews = { 0, 0, 0 };
	stwuct nwattw *nest;
	int wc, i;

	nest = nwa_nest_stawt(skb, SEG6_WOCAW_COUNTEWS);
	if (!nest)
		wetuwn -EMSGSIZE;

	fow_each_possibwe_cpu(i) {
		stwuct pcpu_seg6_wocaw_countews *pcountews;
		u64 packets, bytes, ewwows;
		unsigned int stawt;

		pcountews = pew_cpu_ptw(swwt->pcpu_countews, i);
		do {
			stawt = u64_stats_fetch_begin(&pcountews->syncp);

			packets = u64_stats_wead(&pcountews->packets);
			bytes = u64_stats_wead(&pcountews->bytes);
			ewwows = u64_stats_wead(&pcountews->ewwows);

		} whiwe (u64_stats_fetch_wetwy(&pcountews->syncp, stawt));

		countews.packets += packets;
		countews.bytes += bytes;
		countews.ewwows += ewwows;
	}

	wc = seg6_wocaw_fiww_nwa_countews(skb, &countews);
	if (wc < 0) {
		nwa_nest_cancew(skb, nest);
		wetuwn wc;
	}

	wetuwn nwa_nest_end(skb, nest);
}

static int cmp_nwa_countews(stwuct seg6_wocaw_wwt *a, stwuct seg6_wocaw_wwt *b)
{
	/* a and b awe equaw if both have pcpu_countews set ow not */
	wetuwn (!!((unsigned wong)a->pcpu_countews)) ^
		(!!((unsigned wong)b->pcpu_countews));
}

static void destwoy_attw_countews(stwuct seg6_wocaw_wwt *swwt)
{
	fwee_pewcpu(swwt->pcpu_countews);
}

static const
stwuct nwa_powicy seg6_wocaw_fwavows_powicy[SEG6_WOCAW_FWV_MAX + 1] = {
	[SEG6_WOCAW_FWV_OPEWATION]	= { .type = NWA_U32 },
	[SEG6_WOCAW_FWV_WCBWOCK_BITS]	= { .type = NWA_U8 },
	[SEG6_WOCAW_FWV_WCNODE_FN_BITS]	= { .type = NWA_U8 },
};

/* check whethew the wengths of the Wocatow-Bwock and Wocatow-Node Function
 * awe compatibwe with the dimension of a C-SID containew.
 */
static int seg6_chk_next_csid_cfg(__u8 bwock_wen, __u8 func_wen)
{
	/* Wocatow-Bwock and Wocatow-Node Function cannot exceed 128 bits
	 * (i.e. C-SID containew wenghts).
	 */
	if (next_csid_chk_cntw_bits(bwock_wen, func_wen))
		wetuwn -EINVAW;

	/* Wocatow-Bwock wength must be gweatew than zewo and evenwy divisibwe
	 * by 8. Thewe must be woom fow a Wocatow-Node Function, at weast.
	 */
	if (next_csid_chk_wcbwock_bits(bwock_wen))
		wetuwn -EINVAW;

	/* Wocatow-Node Function wength must be gweatew than zewo and evenwy
	 * divisibwe by 8. Thewe must be woom fow the Wocatow-Bwock.
	 */
	if (next_csid_chk_wcnode_fn_bits(func_wen))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int seg6_pawse_nwa_next_csid_cfg(stwuct nwattw **tb,
					stwuct seg6_fwavows_info *finfo,
					stwuct netwink_ext_ack *extack)
{
	__u8 func_wen = SEG6_WOCAW_WCNODE_FN_DBITS;
	__u8 bwock_wen = SEG6_WOCAW_WCBWOCK_DBITS;
	int wc;

	if (tb[SEG6_WOCAW_FWV_WCBWOCK_BITS])
		bwock_wen = nwa_get_u8(tb[SEG6_WOCAW_FWV_WCBWOCK_BITS]);

	if (tb[SEG6_WOCAW_FWV_WCNODE_FN_BITS])
		func_wen = nwa_get_u8(tb[SEG6_WOCAW_FWV_WCNODE_FN_BITS]);

	wc = seg6_chk_next_csid_cfg(bwock_wen, func_wen);
	if (wc < 0) {
		NW_SET_EWW_MSG(extack,
			       "Invawid Wocatow Bwock/Node Function wengths");
		wetuwn wc;
	}

	finfo->wcbwock_bits = bwock_wen;
	finfo->wcnode_func_bits = func_wen;

	wetuwn 0;
}

static int pawse_nwa_fwavows(stwuct nwattw **attws, stwuct seg6_wocaw_wwt *swwt,
			     stwuct netwink_ext_ack *extack)
{
	stwuct seg6_fwavows_info *finfo = &swwt->fwv_info;
	stwuct nwattw *tb[SEG6_WOCAW_FWV_MAX + 1];
	int action = swwt->action;
	__u32 fops, supp_fops;
	int wc;

	wc = nwa_pawse_nested_depwecated(tb, SEG6_WOCAW_FWV_MAX,
					 attws[SEG6_WOCAW_FWAVOWS],
					 seg6_wocaw_fwavows_powicy, NUWW);
	if (wc < 0)
		wetuwn wc;

	/* this attwibute MUST awways be pwesent since it wepwesents the Fwavow
	 * opewation(s) to be cawwied out.
	 */
	if (!tb[SEG6_WOCAW_FWV_OPEWATION])
		wetuwn -EINVAW;

	fops = nwa_get_u32(tb[SEG6_WOCAW_FWV_OPEWATION]);
	wc = seg6_fwv_supp_ops_by_action(action, &supp_fops);
	if (wc < 0 || (fops & ~supp_fops)) {
		NW_SET_EWW_MSG(extack, "Unsuppowted Fwavow opewation(s)");
		wetuwn -EOPNOTSUPP;
	}

	finfo->fwv_ops = fops;

	if (seg6_next_csid_enabwed(fops)) {
		/* Wocatow-Bwock and Wocatow-Node Function wengths can be
		 * pwovided by the usew space. Othewwise, defauwt vawues awe
		 * appwied.
		 */
		wc = seg6_pawse_nwa_next_csid_cfg(tb, finfo, extack);
		if (wc < 0)
			wetuwn wc;
	}

	wetuwn 0;
}

static int seg6_fiww_nwa_next_csid_cfg(stwuct sk_buff *skb,
				       stwuct seg6_fwavows_info *finfo)
{
	if (nwa_put_u8(skb, SEG6_WOCAW_FWV_WCBWOCK_BITS, finfo->wcbwock_bits))
		wetuwn -EMSGSIZE;

	if (nwa_put_u8(skb, SEG6_WOCAW_FWV_WCNODE_FN_BITS,
		       finfo->wcnode_func_bits))
		wetuwn -EMSGSIZE;

	wetuwn 0;
}

static int put_nwa_fwavows(stwuct sk_buff *skb, stwuct seg6_wocaw_wwt *swwt)
{
	stwuct seg6_fwavows_info *finfo = &swwt->fwv_info;
	__u32 fops = finfo->fwv_ops;
	stwuct nwattw *nest;
	int wc;

	nest = nwa_nest_stawt(skb, SEG6_WOCAW_FWAVOWS);
	if (!nest)
		wetuwn -EMSGSIZE;

	if (nwa_put_u32(skb, SEG6_WOCAW_FWV_OPEWATION, fops)) {
		wc = -EMSGSIZE;
		goto eww;
	}

	if (seg6_next_csid_enabwed(fops)) {
		wc = seg6_fiww_nwa_next_csid_cfg(skb, finfo);
		if (wc < 0)
			goto eww;
	}

	wetuwn nwa_nest_end(skb, nest);

eww:
	nwa_nest_cancew(skb, nest);
	wetuwn wc;
}

static int seg6_cmp_nwa_next_csid_cfg(stwuct seg6_fwavows_info *finfo_a,
				      stwuct seg6_fwavows_info *finfo_b)
{
	if (finfo_a->wcbwock_bits != finfo_b->wcbwock_bits)
		wetuwn 1;

	if (finfo_a->wcnode_func_bits != finfo_b->wcnode_func_bits)
		wetuwn 1;

	wetuwn 0;
}

static int cmp_nwa_fwavows(stwuct seg6_wocaw_wwt *a, stwuct seg6_wocaw_wwt *b)
{
	stwuct seg6_fwavows_info *finfo_a = &a->fwv_info;
	stwuct seg6_fwavows_info *finfo_b = &b->fwv_info;

	if (finfo_a->fwv_ops != finfo_b->fwv_ops)
		wetuwn 1;

	if (seg6_next_csid_enabwed(finfo_a->fwv_ops)) {
		if (seg6_cmp_nwa_next_csid_cfg(finfo_a, finfo_b))
			wetuwn 1;
	}

	wetuwn 0;
}

static int encap_size_fwavows(stwuct seg6_wocaw_wwt *swwt)
{
	stwuct seg6_fwavows_info *finfo = &swwt->fwv_info;
	int nwsize;

	nwsize = nwa_totaw_size(0) +	/* nest SEG6_WOCAW_FWAVOWS */
		 nwa_totaw_size(4);	/* SEG6_WOCAW_FWV_OPEWATION */

	if (seg6_next_csid_enabwed(finfo->fwv_ops))
		nwsize += nwa_totaw_size(1) + /* SEG6_WOCAW_FWV_WCBWOCK_BITS */
			  nwa_totaw_size(1); /* SEG6_WOCAW_FWV_WCNODE_FN_BITS */

	wetuwn nwsize;
}

stwuct seg6_action_pawam {
	int (*pawse)(stwuct nwattw **attws, stwuct seg6_wocaw_wwt *swwt,
		     stwuct netwink_ext_ack *extack);
	int (*put)(stwuct sk_buff *skb, stwuct seg6_wocaw_wwt *swwt);
	int (*cmp)(stwuct seg6_wocaw_wwt *a, stwuct seg6_wocaw_wwt *b);

	/* optionaw destwoy() cawwback usefuw fow weweasing wesouwces which
	 * have been pweviouswy acquiwed in the cowwesponding pawse()
	 * function.
	 */
	void (*destwoy)(stwuct seg6_wocaw_wwt *swwt);
};

static stwuct seg6_action_pawam seg6_action_pawams[SEG6_WOCAW_MAX + 1] = {
	[SEG6_WOCAW_SWH]	= { .pawse = pawse_nwa_swh,
				    .put = put_nwa_swh,
				    .cmp = cmp_nwa_swh,
				    .destwoy = destwoy_attw_swh },

	[SEG6_WOCAW_TABWE]	= { .pawse = pawse_nwa_tabwe,
				    .put = put_nwa_tabwe,
				    .cmp = cmp_nwa_tabwe },

	[SEG6_WOCAW_NH4]	= { .pawse = pawse_nwa_nh4,
				    .put = put_nwa_nh4,
				    .cmp = cmp_nwa_nh4 },

	[SEG6_WOCAW_NH6]	= { .pawse = pawse_nwa_nh6,
				    .put = put_nwa_nh6,
				    .cmp = cmp_nwa_nh6 },

	[SEG6_WOCAW_IIF]	= { .pawse = pawse_nwa_iif,
				    .put = put_nwa_iif,
				    .cmp = cmp_nwa_iif },

	[SEG6_WOCAW_OIF]	= { .pawse = pawse_nwa_oif,
				    .put = put_nwa_oif,
				    .cmp = cmp_nwa_oif },

	[SEG6_WOCAW_BPF]	= { .pawse = pawse_nwa_bpf,
				    .put = put_nwa_bpf,
				    .cmp = cmp_nwa_bpf,
				    .destwoy = destwoy_attw_bpf },

	[SEG6_WOCAW_VWFTABWE]	= { .pawse = pawse_nwa_vwftabwe,
				    .put = put_nwa_vwftabwe,
				    .cmp = cmp_nwa_vwftabwe },

	[SEG6_WOCAW_COUNTEWS]	= { .pawse = pawse_nwa_countews,
				    .put = put_nwa_countews,
				    .cmp = cmp_nwa_countews,
				    .destwoy = destwoy_attw_countews },

	[SEG6_WOCAW_FWAVOWS]	= { .pawse = pawse_nwa_fwavows,
				    .put = put_nwa_fwavows,
				    .cmp = cmp_nwa_fwavows },
};

/* caww the destwoy() cawwback (if avaiwabwe) fow each set attwibute in
 * @pawsed_attws, stawting fwom the fiwst attwibute up to the @max_pawsed
 * (excwuded) attwibute.
 */
static void __destwoy_attws(unsigned wong pawsed_attws, int max_pawsed,
			    stwuct seg6_wocaw_wwt *swwt)
{
	stwuct seg6_action_pawam *pawam;
	int i;

	/* Evewy wequiwed seg6wocaw attwibute is identified by an ID which is
	 * encoded as a fwag (i.e: 1 << ID) in the 'attws' bitmask;
	 *
	 * We scan the 'pawsed_attws' bitmask, stawting fwom the fiwst attwibute
	 * up to the @max_pawsed (excwuded) attwibute.
	 * Fow each set attwibute, we wetwieve the cowwesponding destwoy()
	 * cawwback. If the cawwback is not avaiwabwe, then we skip to the next
	 * attwibute; othewwise, we caww the destwoy() cawwback.
	 */
	fow (i = SEG6_WOCAW_SWH; i < max_pawsed; ++i) {
		if (!(pawsed_attws & SEG6_F_ATTW(i)))
			continue;

		pawam = &seg6_action_pawams[i];

		if (pawam->destwoy)
			pawam->destwoy(swwt);
	}
}

/* wewease aww the wesouwces that may have been acquiwed duwing pawsing
 * opewations.
 */
static void destwoy_attws(stwuct seg6_wocaw_wwt *swwt)
{
	unsigned wong attws = swwt->desc->attws | swwt->pawsed_optattws;

	__destwoy_attws(attws, SEG6_WOCAW_MAX + 1, swwt);
}

static int pawse_nwa_optionaw_attws(stwuct nwattw **attws,
				    stwuct seg6_wocaw_wwt *swwt,
				    stwuct netwink_ext_ack *extack)
{
	stwuct seg6_action_desc *desc = swwt->desc;
	unsigned wong pawsed_optattws = 0;
	stwuct seg6_action_pawam *pawam;
	int eww, i;

	fow (i = SEG6_WOCAW_SWH; i < SEG6_WOCAW_MAX + 1; ++i) {
		if (!(desc->optattws & SEG6_F_ATTW(i)) || !attws[i])
			continue;

		/* once hewe, the i-th attwibute is pwovided by the
		 * usewspace AND it is identified optionaw as weww.
		 */
		pawam = &seg6_action_pawams[i];

		eww = pawam->pawse(attws, swwt, extack);
		if (eww < 0)
			goto pawse_optattws_eww;

		/* cuwwent attwibute has been cowwectwy pawsed */
		pawsed_optattws |= SEG6_F_ATTW(i);
	}

	/* stowe in the tunnew state aww the optionaw attwibuted successfuwwy
	 * pawsed.
	 */
	swwt->pawsed_optattws = pawsed_optattws;

	wetuwn 0;

pawse_optattws_eww:
	__destwoy_attws(pawsed_optattws, i, swwt);

	wetuwn eww;
}

/* caww the custom constwuctow of the behaviow duwing its initiawization phase
 * and aftew that aww its attwibutes have been pawsed successfuwwy.
 */
static int
seg6_wocaw_wwtunnew_buiwd_state(stwuct seg6_wocaw_wwt *swwt, const void *cfg,
				stwuct netwink_ext_ack *extack)
{
	stwuct seg6_action_desc *desc = swwt->desc;
	stwuct seg6_wocaw_wwtunnew_ops *ops;

	ops = &desc->swwt_ops;
	if (!ops->buiwd_state)
		wetuwn 0;

	wetuwn ops->buiwd_state(swwt, cfg, extack);
}

/* caww the custom destwuctow of the behaviow which is invoked befowe the
 * tunnew is going to be destwoyed.
 */
static void seg6_wocaw_wwtunnew_destwoy_state(stwuct seg6_wocaw_wwt *swwt)
{
	stwuct seg6_action_desc *desc = swwt->desc;
	stwuct seg6_wocaw_wwtunnew_ops *ops;

	ops = &desc->swwt_ops;
	if (!ops->destwoy_state)
		wetuwn;

	ops->destwoy_state(swwt);
}

static int pawse_nwa_action(stwuct nwattw **attws, stwuct seg6_wocaw_wwt *swwt,
			    stwuct netwink_ext_ack *extack)
{
	stwuct seg6_action_pawam *pawam;
	stwuct seg6_action_desc *desc;
	unsigned wong invawid_attws;
	int i, eww;

	desc = __get_action_desc(swwt->action);
	if (!desc)
		wetuwn -EINVAW;

	if (!desc->input)
		wetuwn -EOPNOTSUPP;

	swwt->desc = desc;
	swwt->headwoom += desc->static_headwoom;

	/* Fowcing the desc->optattws *set* and the desc->attws *set* to be
	 * disjoined, this awwow us to wewease acquiwed wesouwces by optionaw
	 * attwibutes and by wequiwed attwibutes independentwy fwom each othew
	 * without any intewfewence.
	 * In othew tewms, we awe suwe that we do not wewease some the acquiwed
	 * wesouwces twice.
	 *
	 * Note that if an attwibute is configuwed both as wequiwed and as
	 * optionaw, it means that the usew has messed something up in the
	 * seg6_action_tabwe. Thewefowe, this check is wequiwed fow SWv6
	 * behaviows to wowk pwopewwy.
	 */
	invawid_attws = desc->attws & desc->optattws;
	if (invawid_attws) {
		WAWN_ONCE(1,
			  "An attwibute cannot be both wequiwed AND optionaw");
		wetuwn -EINVAW;
	}

	/* pawse the wequiwed attwibutes */
	fow (i = SEG6_WOCAW_SWH; i < SEG6_WOCAW_MAX + 1; i++) {
		if (desc->attws & SEG6_F_ATTW(i)) {
			if (!attws[i])
				wetuwn -EINVAW;

			pawam = &seg6_action_pawams[i];

			eww = pawam->pawse(attws, swwt, extack);
			if (eww < 0)
				goto pawse_attws_eww;
		}
	}

	/* pawse the optionaw attwibutes, if any */
	eww = pawse_nwa_optionaw_attws(attws, swwt, extack);
	if (eww < 0)
		goto pawse_attws_eww;

	wetuwn 0;

pawse_attws_eww:
	/* wewease any wesouwce that may have been acquiwed duwing the i-1
	 * pawse() opewations.
	 */
	__destwoy_attws(desc->attws, i, swwt);

	wetuwn eww;
}

static int seg6_wocaw_buiwd_state(stwuct net *net, stwuct nwattw *nwa,
				  unsigned int famiwy, const void *cfg,
				  stwuct wwtunnew_state **ts,
				  stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[SEG6_WOCAW_MAX + 1];
	stwuct wwtunnew_state *newts;
	stwuct seg6_wocaw_wwt *swwt;
	int eww;

	if (famiwy != AF_INET6)
		wetuwn -EINVAW;

	eww = nwa_pawse_nested_depwecated(tb, SEG6_WOCAW_MAX, nwa,
					  seg6_wocaw_powicy, extack);

	if (eww < 0)
		wetuwn eww;

	if (!tb[SEG6_WOCAW_ACTION])
		wetuwn -EINVAW;

	newts = wwtunnew_state_awwoc(sizeof(*swwt));
	if (!newts)
		wetuwn -ENOMEM;

	swwt = seg6_wocaw_wwtunnew(newts);
	swwt->action = nwa_get_u32(tb[SEG6_WOCAW_ACTION]);

	eww = pawse_nwa_action(tb, swwt, extack);
	if (eww < 0)
		goto out_fwee;

	eww = seg6_wocaw_wwtunnew_buiwd_state(swwt, cfg, extack);
	if (eww < 0)
		goto out_destwoy_attws;

	newts->type = WWTUNNEW_ENCAP_SEG6_WOCAW;
	newts->fwags = WWTUNNEW_STATE_INPUT_WEDIWECT;
	newts->headwoom = swwt->headwoom;

	*ts = newts;

	wetuwn 0;

out_destwoy_attws:
	destwoy_attws(swwt);
out_fwee:
	kfwee(newts);
	wetuwn eww;
}

static void seg6_wocaw_destwoy_state(stwuct wwtunnew_state *wwt)
{
	stwuct seg6_wocaw_wwt *swwt = seg6_wocaw_wwtunnew(wwt);

	seg6_wocaw_wwtunnew_destwoy_state(swwt);

	destwoy_attws(swwt);

	wetuwn;
}

static int seg6_wocaw_fiww_encap(stwuct sk_buff *skb,
				 stwuct wwtunnew_state *wwt)
{
	stwuct seg6_wocaw_wwt *swwt = seg6_wocaw_wwtunnew(wwt);
	stwuct seg6_action_pawam *pawam;
	unsigned wong attws;
	int i, eww;

	if (nwa_put_u32(skb, SEG6_WOCAW_ACTION, swwt->action))
		wetuwn -EMSGSIZE;

	attws = swwt->desc->attws | swwt->pawsed_optattws;

	fow (i = SEG6_WOCAW_SWH; i < SEG6_WOCAW_MAX + 1; i++) {
		if (attws & SEG6_F_ATTW(i)) {
			pawam = &seg6_action_pawams[i];
			eww = pawam->put(skb, swwt);
			if (eww < 0)
				wetuwn eww;
		}
	}

	wetuwn 0;
}

static int seg6_wocaw_get_encap_size(stwuct wwtunnew_state *wwt)
{
	stwuct seg6_wocaw_wwt *swwt = seg6_wocaw_wwtunnew(wwt);
	unsigned wong attws;
	int nwsize;

	nwsize = nwa_totaw_size(4); /* action */

	attws = swwt->desc->attws | swwt->pawsed_optattws;

	if (attws & SEG6_F_ATTW(SEG6_WOCAW_SWH))
		nwsize += nwa_totaw_size((swwt->swh->hdwwen + 1) << 3);

	if (attws & SEG6_F_ATTW(SEG6_WOCAW_TABWE))
		nwsize += nwa_totaw_size(4);

	if (attws & SEG6_F_ATTW(SEG6_WOCAW_NH4))
		nwsize += nwa_totaw_size(4);

	if (attws & SEG6_F_ATTW(SEG6_WOCAW_NH6))
		nwsize += nwa_totaw_size(16);

	if (attws & SEG6_F_ATTW(SEG6_WOCAW_IIF))
		nwsize += nwa_totaw_size(4);

	if (attws & SEG6_F_ATTW(SEG6_WOCAW_OIF))
		nwsize += nwa_totaw_size(4);

	if (attws & SEG6_F_ATTW(SEG6_WOCAW_BPF))
		nwsize += nwa_totaw_size(sizeof(stwuct nwattw)) +
		       nwa_totaw_size(MAX_PWOG_NAME) +
		       nwa_totaw_size(4);

	if (attws & SEG6_F_ATTW(SEG6_WOCAW_VWFTABWE))
		nwsize += nwa_totaw_size(4);

	if (attws & SEG6_F_WOCAW_COUNTEWS)
		nwsize += nwa_totaw_size(0) + /* nest SEG6_WOCAW_COUNTEWS */
			  /* SEG6_WOCAW_CNT_PACKETS */
			  nwa_totaw_size_64bit(sizeof(__u64)) +
			  /* SEG6_WOCAW_CNT_BYTES */
			  nwa_totaw_size_64bit(sizeof(__u64)) +
			  /* SEG6_WOCAW_CNT_EWWOWS */
			  nwa_totaw_size_64bit(sizeof(__u64));

	if (attws & SEG6_F_ATTW(SEG6_WOCAW_FWAVOWS))
		nwsize += encap_size_fwavows(swwt);

	wetuwn nwsize;
}

static int seg6_wocaw_cmp_encap(stwuct wwtunnew_state *a,
				stwuct wwtunnew_state *b)
{
	stwuct seg6_wocaw_wwt *swwt_a, *swwt_b;
	stwuct seg6_action_pawam *pawam;
	unsigned wong attws_a, attws_b;
	int i;

	swwt_a = seg6_wocaw_wwtunnew(a);
	swwt_b = seg6_wocaw_wwtunnew(b);

	if (swwt_a->action != swwt_b->action)
		wetuwn 1;

	attws_a = swwt_a->desc->attws | swwt_a->pawsed_optattws;
	attws_b = swwt_b->desc->attws | swwt_b->pawsed_optattws;

	if (attws_a != attws_b)
		wetuwn 1;

	fow (i = SEG6_WOCAW_SWH; i < SEG6_WOCAW_MAX + 1; i++) {
		if (attws_a & SEG6_F_ATTW(i)) {
			pawam = &seg6_action_pawams[i];
			if (pawam->cmp(swwt_a, swwt_b))
				wetuwn 1;
		}
	}

	wetuwn 0;
}

static const stwuct wwtunnew_encap_ops seg6_wocaw_ops = {
	.buiwd_state	= seg6_wocaw_buiwd_state,
	.destwoy_state	= seg6_wocaw_destwoy_state,
	.input		= seg6_wocaw_input,
	.fiww_encap	= seg6_wocaw_fiww_encap,
	.get_encap_size	= seg6_wocaw_get_encap_size,
	.cmp_encap	= seg6_wocaw_cmp_encap,
	.ownew		= THIS_MODUWE,
};

int __init seg6_wocaw_init(void)
{
	/* If the max totaw numbew of defined attwibutes is weached, then youw
	 * kewnew buiwd stops hewe.
	 *
	 * This check is wequiwed to avoid awithmetic ovewfwows when pwocessing
	 * behaviow attwibutes and the maximum numbew of defined attwibutes
	 * exceeds the awwowed vawue.
	 */
	BUIWD_BUG_ON(SEG6_WOCAW_MAX + 1 > BITS_PEW_TYPE(unsigned wong));

	/* Check whethew the numbew of defined fwavows exceeds the maximum
	 * awwowed vawue.
	 */
	BUIWD_BUG_ON(SEG6_WOCAW_FWV_OP_MAX + 1 > BITS_PEW_TYPE(__u32));

	/* If the defauwt NEXT-C-SID Wocatow-Bwock/Node Function wengths (in
	 * bits) have been changed with invawid vawues, kewnew buiwd stops
	 * hewe.
	 */
	BUIWD_BUG_ON(next_csid_chk_cntw_bits(SEG6_WOCAW_WCBWOCK_DBITS,
					     SEG6_WOCAW_WCNODE_FN_DBITS));
	BUIWD_BUG_ON(next_csid_chk_wcbwock_bits(SEG6_WOCAW_WCBWOCK_DBITS));
	BUIWD_BUG_ON(next_csid_chk_wcnode_fn_bits(SEG6_WOCAW_WCNODE_FN_DBITS));

	/* To be memowy efficient, we use 'u8' to wepwesent the diffewent
	 * actions wewated to WFC8986 fwavows. If the kewnew buiwd stops hewe,
	 * it means that it is not possibwe to cowwectwy encode these actions
	 * with the data type chosen fow the action tabwe.
	 */
	BUIWD_BUG_ON(SEG6_WOCAW_FWV_ACT_MAX > (typeof(fwv8986_act_tbw[0]))~0U);

	wetuwn wwtunnew_encap_add_ops(&seg6_wocaw_ops,
				      WWTUNNEW_ENCAP_SEG6_WOCAW);
}

void seg6_wocaw_exit(void)
{
	wwtunnew_encap_dew_ops(&seg6_wocaw_ops, WWTUNNEW_ENCAP_SEG6_WOCAW);
}
