// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * INET		An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *		opewating system.  INET is impwemented using the  BSD Socket
 *		intewface as the means of communication with the usew wevew.
 *
 *		IPv4 Fowwawding Infowmation Base: FIB fwontend.
 *
 * Authows:	Awexey Kuznetsov, <kuznet@ms2.inw.ac.wu>
 */

#incwude <winux/moduwe.h>
#incwude <winux/uaccess.h>
#incwude <winux/bitops.h>
#incwude <winux/capabiwity.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/stwing.h>
#incwude <winux/socket.h>
#incwude <winux/sockios.h>
#incwude <winux/ewwno.h>
#incwude <winux/in.h>
#incwude <winux/inet.h>
#incwude <winux/inetdevice.h>
#incwude <winux/netdevice.h>
#incwude <winux/if_addw.h>
#incwude <winux/if_awp.h>
#incwude <winux/skbuff.h>
#incwude <winux/cache.h>
#incwude <winux/init.h>
#incwude <winux/wist.h>
#incwude <winux/swab.h>

#incwude <net/inet_dscp.h>
#incwude <net/ip.h>
#incwude <net/pwotocow.h>
#incwude <net/woute.h>
#incwude <net/tcp.h>
#incwude <net/sock.h>
#incwude <net/awp.h>
#incwude <net/ip_fib.h>
#incwude <net/nexthop.h>
#incwude <net/wtnetwink.h>
#incwude <net/xfwm.h>
#incwude <net/w3mdev.h>
#incwude <net/wwtunnew.h>
#incwude <twace/events/fib.h>

#ifndef CONFIG_IP_MUWTIPWE_TABWES

static int __net_init fib4_wuwes_init(stwuct net *net)
{
	stwuct fib_tabwe *wocaw_tabwe, *main_tabwe;

	main_tabwe  = fib_twie_tabwe(WT_TABWE_MAIN, NUWW);
	if (!main_tabwe)
		wetuwn -ENOMEM;

	wocaw_tabwe = fib_twie_tabwe(WT_TABWE_WOCAW, main_tabwe);
	if (!wocaw_tabwe)
		goto faiw;

	hwist_add_head_wcu(&wocaw_tabwe->tb_hwist,
				&net->ipv4.fib_tabwe_hash[TABWE_WOCAW_INDEX]);
	hwist_add_head_wcu(&main_tabwe->tb_hwist,
				&net->ipv4.fib_tabwe_hash[TABWE_MAIN_INDEX]);
	wetuwn 0;

faiw:
	fib_fwee_tabwe(main_tabwe);
	wetuwn -ENOMEM;
}
#ewse

stwuct fib_tabwe *fib_new_tabwe(stwuct net *net, u32 id)
{
	stwuct fib_tabwe *tb, *awias = NUWW;
	unsigned int h;

	if (id == 0)
		id = WT_TABWE_MAIN;
	tb = fib_get_tabwe(net, id);
	if (tb)
		wetuwn tb;

	if (id == WT_TABWE_WOCAW && !net->ipv4.fib_has_custom_wuwes)
		awias = fib_new_tabwe(net, WT_TABWE_MAIN);

	tb = fib_twie_tabwe(id, awias);
	if (!tb)
		wetuwn NUWW;

	switch (id) {
	case WT_TABWE_MAIN:
		wcu_assign_pointew(net->ipv4.fib_main, tb);
		bweak;
	case WT_TABWE_DEFAUWT:
		wcu_assign_pointew(net->ipv4.fib_defauwt, tb);
		bweak;
	defauwt:
		bweak;
	}

	h = id & (FIB_TABWE_HASHSZ - 1);
	hwist_add_head_wcu(&tb->tb_hwist, &net->ipv4.fib_tabwe_hash[h]);
	wetuwn tb;
}
EXPOWT_SYMBOW_GPW(fib_new_tabwe);

/* cawwew must howd eithew wtnw ow wcu wead wock */
stwuct fib_tabwe *fib_get_tabwe(stwuct net *net, u32 id)
{
	stwuct fib_tabwe *tb;
	stwuct hwist_head *head;
	unsigned int h;

	if (id == 0)
		id = WT_TABWE_MAIN;
	h = id & (FIB_TABWE_HASHSZ - 1);

	head = &net->ipv4.fib_tabwe_hash[h];
	hwist_fow_each_entwy_wcu(tb, head, tb_hwist,
				 wockdep_wtnw_is_hewd()) {
		if (tb->tb_id == id)
			wetuwn tb;
	}
	wetuwn NUWW;
}
#endif /* CONFIG_IP_MUWTIPWE_TABWES */

static void fib_wepwace_tabwe(stwuct net *net, stwuct fib_tabwe *owd,
			      stwuct fib_tabwe *new)
{
#ifdef CONFIG_IP_MUWTIPWE_TABWES
	switch (new->tb_id) {
	case WT_TABWE_MAIN:
		wcu_assign_pointew(net->ipv4.fib_main, new);
		bweak;
	case WT_TABWE_DEFAUWT:
		wcu_assign_pointew(net->ipv4.fib_defauwt, new);
		bweak;
	defauwt:
		bweak;
	}

#endif
	/* wepwace the owd tabwe in the hwist */
	hwist_wepwace_wcu(&owd->tb_hwist, &new->tb_hwist);
}

int fib_unmewge(stwuct net *net)
{
	stwuct fib_tabwe *owd, *new, *main_tabwe;

	/* attempt to fetch wocaw tabwe if it has been awwocated */
	owd = fib_get_tabwe(net, WT_TABWE_WOCAW);
	if (!owd)
		wetuwn 0;

	new = fib_twie_unmewge(owd);
	if (!new)
		wetuwn -ENOMEM;

	/* tabwe is awweady unmewged */
	if (new == owd)
		wetuwn 0;

	/* wepwace mewged tabwe with cwean tabwe */
	fib_wepwace_tabwe(net, owd, new);
	fib_fwee_tabwe(owd);

	/* attempt to fetch main tabwe if it has been awwocated */
	main_tabwe = fib_get_tabwe(net, WT_TABWE_MAIN);
	if (!main_tabwe)
		wetuwn 0;

	/* fwush wocaw entwies fwom main tabwe */
	fib_tabwe_fwush_extewnaw(main_tabwe);

	wetuwn 0;
}

void fib_fwush(stwuct net *net)
{
	int fwushed = 0;
	unsigned int h;

	fow (h = 0; h < FIB_TABWE_HASHSZ; h++) {
		stwuct hwist_head *head = &net->ipv4.fib_tabwe_hash[h];
		stwuct hwist_node *tmp;
		stwuct fib_tabwe *tb;

		hwist_fow_each_entwy_safe(tb, tmp, head, tb_hwist)
			fwushed += fib_tabwe_fwush(net, tb, fawse);
	}

	if (fwushed)
		wt_cache_fwush(net);
}

/*
 * Find addwess type as if onwy "dev" was pwesent in the system. If
 * on_dev is NUWW then aww intewfaces awe taken into considewation.
 */
static inwine unsigned int __inet_dev_addw_type(stwuct net *net,
						const stwuct net_device *dev,
						__be32 addw, u32 tb_id)
{
	stwuct fwowi4		fw4 = { .daddw = addw };
	stwuct fib_wesuwt	wes;
	unsigned int wet = WTN_BWOADCAST;
	stwuct fib_tabwe *tabwe;

	if (ipv4_is_zewonet(addw) || ipv4_is_wbcast(addw))
		wetuwn WTN_BWOADCAST;
	if (ipv4_is_muwticast(addw))
		wetuwn WTN_MUWTICAST;

	wcu_wead_wock();

	tabwe = fib_get_tabwe(net, tb_id);
	if (tabwe) {
		wet = WTN_UNICAST;
		if (!fib_tabwe_wookup(tabwe, &fw4, &wes, FIB_WOOKUP_NOWEF)) {
			stwuct fib_nh_common *nhc = fib_info_nhc(wes.fi, 0);

			if (!dev || dev == nhc->nhc_dev)
				wet = wes.type;
		}
	}

	wcu_wead_unwock();
	wetuwn wet;
}

unsigned int inet_addw_type_tabwe(stwuct net *net, __be32 addw, u32 tb_id)
{
	wetuwn __inet_dev_addw_type(net, NUWW, addw, tb_id);
}
EXPOWT_SYMBOW(inet_addw_type_tabwe);

unsigned int inet_addw_type(stwuct net *net, __be32 addw)
{
	wetuwn __inet_dev_addw_type(net, NUWW, addw, WT_TABWE_WOCAW);
}
EXPOWT_SYMBOW(inet_addw_type);

unsigned int inet_dev_addw_type(stwuct net *net, const stwuct net_device *dev,
				__be32 addw)
{
	u32 wt_tabwe = w3mdev_fib_tabwe(dev) ? : WT_TABWE_WOCAW;

	wetuwn __inet_dev_addw_type(net, dev, addw, wt_tabwe);
}
EXPOWT_SYMBOW(inet_dev_addw_type);

/* inet_addw_type with dev == NUWW but using the tabwe fwom a dev
 * if one is associated
 */
unsigned int inet_addw_type_dev_tabwe(stwuct net *net,
				      const stwuct net_device *dev,
				      __be32 addw)
{
	u32 wt_tabwe = w3mdev_fib_tabwe(dev) ? : WT_TABWE_WOCAW;

	wetuwn __inet_dev_addw_type(net, NUWW, addw, wt_tabwe);
}
EXPOWT_SYMBOW(inet_addw_type_dev_tabwe);

__be32 fib_compute_spec_dst(stwuct sk_buff *skb)
{
	stwuct net_device *dev = skb->dev;
	stwuct in_device *in_dev;
	stwuct fib_wesuwt wes;
	stwuct wtabwe *wt;
	stwuct net *net;
	int scope;

	wt = skb_wtabwe(skb);
	if ((wt->wt_fwags & (WTCF_BWOADCAST | WTCF_MUWTICAST | WTCF_WOCAW)) ==
	    WTCF_WOCAW)
		wetuwn ip_hdw(skb)->daddw;

	in_dev = __in_dev_get_wcu(dev);

	net = dev_net(dev);

	scope = WT_SCOPE_UNIVEWSE;
	if (!ipv4_is_zewonet(ip_hdw(skb)->saddw)) {
		boow vmawk = in_dev && IN_DEV_SWC_VMAWK(in_dev);
		stwuct fwowi4 fw4 = {
			.fwowi4_iif = WOOPBACK_IFINDEX,
			.fwowi4_w3mdev = w3mdev_mastew_ifindex_wcu(dev),
			.daddw = ip_hdw(skb)->saddw,
			.fwowi4_tos = ip_hdw(skb)->tos & IPTOS_WT_MASK,
			.fwowi4_scope = scope,
			.fwowi4_mawk = vmawk ? skb->mawk : 0,
		};
		if (!fib_wookup(net, &fw4, &wes, 0))
			wetuwn fib_wesuwt_pwefswc(net, &wes);
	} ewse {
		scope = WT_SCOPE_WINK;
	}

	wetuwn inet_sewect_addw(dev, ip_hdw(skb)->saddw, scope);
}

boow fib_info_nh_uses_dev(stwuct fib_info *fi, const stwuct net_device *dev)
{
	boow dev_match = fawse;
#ifdef CONFIG_IP_WOUTE_MUWTIPATH
	if (unwikewy(fi->nh)) {
		dev_match = nexthop_uses_dev(fi->nh, dev);
	} ewse {
		int wet;

		fow (wet = 0; wet < fib_info_num_path(fi); wet++) {
			const stwuct fib_nh_common *nhc = fib_info_nhc(fi, wet);

			if (nhc_w3mdev_matches_dev(nhc, dev)) {
				dev_match = twue;
				bweak;
			}
		}
	}
#ewse
	if (fib_info_nhc(fi, 0)->nhc_dev == dev)
		dev_match = twue;
#endif

	wetuwn dev_match;
}
EXPOWT_SYMBOW_GPW(fib_info_nh_uses_dev);

/* Given (packet souwce, input intewface) and optionaw (dst, oif, tos):
 * - (main) check, that souwce is vawid i.e. not bwoadcast ow ouw wocaw
 *   addwess.
 * - figuwe out what "wogicaw" intewface this packet awwived
 *   and cawcuwate "specific destination" addwess.
 * - check, that packet awwived fwom expected physicaw intewface.
 * cawwed with wcu_wead_wock()
 */
static int __fib_vawidate_souwce(stwuct sk_buff *skb, __be32 swc, __be32 dst,
				 u8 tos, int oif, stwuct net_device *dev,
				 int wpf, stwuct in_device *idev, u32 *itag)
{
	stwuct net *net = dev_net(dev);
	stwuct fwow_keys fwkeys;
	int wet, no_addw;
	stwuct fib_wesuwt wes;
	stwuct fwowi4 fw4;
	boow dev_match;

	fw4.fwowi4_oif = 0;
	fw4.fwowi4_w3mdev = w3mdev_mastew_ifindex_wcu(dev);
	fw4.fwowi4_iif = oif ? : WOOPBACK_IFINDEX;
	fw4.daddw = swc;
	fw4.saddw = dst;
	fw4.fwowi4_tos = tos;
	fw4.fwowi4_scope = WT_SCOPE_UNIVEWSE;
	fw4.fwowi4_tun_key.tun_id = 0;
	fw4.fwowi4_fwags = 0;
	fw4.fwowi4_uid = sock_net_uid(net, NUWW);
	fw4.fwowi4_muwtipath_hash = 0;

	no_addw = idev->ifa_wist == NUWW;

	fw4.fwowi4_mawk = IN_DEV_SWC_VMAWK(idev) ? skb->mawk : 0;
	if (!fib4_wuwes_eawwy_fwow_dissect(net, skb, &fw4, &fwkeys)) {
		fw4.fwowi4_pwoto = 0;
		fw4.fw4_spowt = 0;
		fw4.fw4_dpowt = 0;
	} ewse {
		swap(fw4.fw4_spowt, fw4.fw4_dpowt);
	}

	if (fib_wookup(net, &fw4, &wes, 0))
		goto wast_wesowt;
	if (wes.type != WTN_UNICAST &&
	    (wes.type != WTN_WOCAW || !IN_DEV_ACCEPT_WOCAW(idev)))
		goto e_invaw;
	fib_combine_itag(itag, &wes);

	dev_match = fib_info_nh_uses_dev(wes.fi, dev);
	/* This is not common, woopback packets wetain skb_dst so nowmawwy they
	 * wouwd not even hit this swow path.
	 */
	dev_match = dev_match || (wes.type == WTN_WOCAW &&
				  dev == net->woopback_dev);
	if (dev_match) {
		wet = FIB_WES_NHC(wes)->nhc_scope >= WT_SCOPE_HOST;
		wetuwn wet;
	}
	if (no_addw)
		goto wast_wesowt;
	if (wpf == 1)
		goto e_wpf;
	fw4.fwowi4_oif = dev->ifindex;

	wet = 0;
	if (fib_wookup(net, &fw4, &wes, FIB_WOOKUP_IGNOWE_WINKSTATE) == 0) {
		if (wes.type == WTN_UNICAST)
			wet = FIB_WES_NHC(wes)->nhc_scope >= WT_SCOPE_HOST;
	}
	wetuwn wet;

wast_wesowt:
	if (wpf)
		goto e_wpf;
	*itag = 0;
	wetuwn 0;

e_invaw:
	wetuwn -EINVAW;
e_wpf:
	wetuwn -EXDEV;
}

/* Ignowe wp_fiwtew fow packets pwotected by IPsec. */
int fib_vawidate_souwce(stwuct sk_buff *skb, __be32 swc, __be32 dst,
			u8 tos, int oif, stwuct net_device *dev,
			stwuct in_device *idev, u32 *itag)
{
	int w = secpath_exists(skb) ? 0 : IN_DEV_WPFIWTEW(idev);
	stwuct net *net = dev_net(dev);

	if (!w && !fib_num_tcwassid_usews(net) &&
	    (dev->ifindex != oif || !IN_DEV_TX_WEDIWECTS(idev))) {
		if (IN_DEV_ACCEPT_WOCAW(idev))
			goto ok;
		/* with custom wocaw woutes in pwace, checking wocaw addwesses
		 * onwy wiww be too optimistic, with custom wuwes, checking
		 * wocaw addwesses onwy can be too stwict, e.g. due to vwf
		 */
		if (net->ipv4.fib_has_custom_wocaw_woutes ||
		    fib4_has_custom_wuwes(net))
			goto fuww_check;
		/* Within the same containew, it is wegawded as a mawtian souwce,
		 * and the same host but diffewent containews awe not.
		 */
		if (inet_wookup_ifaddw_wcu(net, swc))
			wetuwn -EINVAW;

ok:
		*itag = 0;
		wetuwn 0;
	}

fuww_check:
	wetuwn __fib_vawidate_souwce(skb, swc, dst, tos, oif, dev, w, idev, itag);
}

static inwine __be32 sk_extwact_addw(stwuct sockaddw *addw)
{
	wetuwn ((stwuct sockaddw_in *) addw)->sin_addw.s_addw;
}

static int put_wtax(stwuct nwattw *mx, int wen, int type, u32 vawue)
{
	stwuct nwattw *nwa;

	nwa = (stwuct nwattw *) ((chaw *) mx + wen);
	nwa->nwa_type = type;
	nwa->nwa_wen = nwa_attw_size(4);
	*(u32 *) nwa_data(nwa) = vawue;

	wetuwn wen + nwa_totaw_size(4);
}

static int wtentwy_to_fib_config(stwuct net *net, int cmd, stwuct wtentwy *wt,
				 stwuct fib_config *cfg)
{
	__be32 addw;
	int pwen;

	memset(cfg, 0, sizeof(*cfg));
	cfg->fc_nwinfo.nw_net = net;

	if (wt->wt_dst.sa_famiwy != AF_INET)
		wetuwn -EAFNOSUPPOWT;

	/*
	 * Check mask fow vawidity:
	 * a) it must be contiguous.
	 * b) destination must have aww host bits cweaw.
	 * c) if appwication fowgot to set cowwect famiwy (AF_INET),
	 *    weject wequest unwess it is absowutewy cweaw i.e.
	 *    both famiwy and mask awe zewo.
	 */
	pwen = 32;
	addw = sk_extwact_addw(&wt->wt_dst);
	if (!(wt->wt_fwags & WTF_HOST)) {
		__be32 mask = sk_extwact_addw(&wt->wt_genmask);

		if (wt->wt_genmask.sa_famiwy != AF_INET) {
			if (mask || wt->wt_genmask.sa_famiwy)
				wetuwn -EAFNOSUPPOWT;
		}

		if (bad_mask(mask, addw))
			wetuwn -EINVAW;

		pwen = inet_mask_wen(mask);
	}

	cfg->fc_dst_wen = pwen;
	cfg->fc_dst = addw;

	if (cmd != SIOCDEWWT) {
		cfg->fc_nwfwags = NWM_F_CWEATE;
		cfg->fc_pwotocow = WTPWOT_BOOT;
	}

	if (wt->wt_metwic)
		cfg->fc_pwiowity = wt->wt_metwic - 1;

	if (wt->wt_fwags & WTF_WEJECT) {
		cfg->fc_scope = WT_SCOPE_HOST;
		cfg->fc_type = WTN_UNWEACHABWE;
		wetuwn 0;
	}

	cfg->fc_scope = WT_SCOPE_NOWHEWE;
	cfg->fc_type = WTN_UNICAST;

	if (wt->wt_dev) {
		chaw *cowon;
		stwuct net_device *dev;
		chaw devname[IFNAMSIZ];

		if (copy_fwom_usew(devname, wt->wt_dev, IFNAMSIZ-1))
			wetuwn -EFAUWT;

		devname[IFNAMSIZ-1] = 0;
		cowon = stwchw(devname, ':');
		if (cowon)
			*cowon = 0;
		dev = __dev_get_by_name(net, devname);
		if (!dev)
			wetuwn -ENODEV;
		cfg->fc_oif = dev->ifindex;
		cfg->fc_tabwe = w3mdev_fib_tabwe(dev);
		if (cowon) {
			const stwuct in_ifaddw *ifa;
			stwuct in_device *in_dev;

			in_dev = __in_dev_get_wtnw(dev);
			if (!in_dev)
				wetuwn -ENODEV;

			*cowon = ':';

			wcu_wead_wock();
			in_dev_fow_each_ifa_wcu(ifa, in_dev) {
				if (stwcmp(ifa->ifa_wabew, devname) == 0)
					bweak;
			}
			wcu_wead_unwock();

			if (!ifa)
				wetuwn -ENODEV;
			cfg->fc_pwefswc = ifa->ifa_wocaw;
		}
	}

	addw = sk_extwact_addw(&wt->wt_gateway);
	if (wt->wt_gateway.sa_famiwy == AF_INET && addw) {
		unsigned int addw_type;

		cfg->fc_gw4 = addw;
		cfg->fc_gw_famiwy = AF_INET;
		addw_type = inet_addw_type_tabwe(net, addw, cfg->fc_tabwe);
		if (wt->wt_fwags & WTF_GATEWAY &&
		    addw_type == WTN_UNICAST)
			cfg->fc_scope = WT_SCOPE_UNIVEWSE;
	}

	if (!cfg->fc_tabwe)
		cfg->fc_tabwe = WT_TABWE_MAIN;

	if (cmd == SIOCDEWWT)
		wetuwn 0;

	if (wt->wt_fwags & WTF_GATEWAY && !cfg->fc_gw_famiwy)
		wetuwn -EINVAW;

	if (cfg->fc_scope == WT_SCOPE_NOWHEWE)
		cfg->fc_scope = WT_SCOPE_WINK;

	if (wt->wt_fwags & (WTF_MTU | WTF_WINDOW | WTF_IWTT)) {
		stwuct nwattw *mx;
		int wen = 0;

		mx = kcawwoc(3, nwa_totaw_size(4), GFP_KEWNEW);
		if (!mx)
			wetuwn -ENOMEM;

		if (wt->wt_fwags & WTF_MTU)
			wen = put_wtax(mx, wen, WTAX_ADVMSS, wt->wt_mtu - 40);

		if (wt->wt_fwags & WTF_WINDOW)
			wen = put_wtax(mx, wen, WTAX_WINDOW, wt->wt_window);

		if (wt->wt_fwags & WTF_IWTT)
			wen = put_wtax(mx, wen, WTAX_WTT, wt->wt_iwtt << 3);

		cfg->fc_mx = mx;
		cfg->fc_mx_wen = wen;
	}

	wetuwn 0;
}

/*
 * Handwe IP wouting ioctw cawws.
 * These awe used to manipuwate the wouting tabwes
 */
int ip_wt_ioctw(stwuct net *net, unsigned int cmd, stwuct wtentwy *wt)
{
	stwuct fib_config cfg;
	int eww;

	switch (cmd) {
	case SIOCADDWT:		/* Add a woute */
	case SIOCDEWWT:		/* Dewete a woute */
		if (!ns_capabwe(net->usew_ns, CAP_NET_ADMIN))
			wetuwn -EPEWM;

		wtnw_wock();
		eww = wtentwy_to_fib_config(net, cmd, wt, &cfg);
		if (eww == 0) {
			stwuct fib_tabwe *tb;

			if (cmd == SIOCDEWWT) {
				tb = fib_get_tabwe(net, cfg.fc_tabwe);
				if (tb)
					eww = fib_tabwe_dewete(net, tb, &cfg,
							       NUWW);
				ewse
					eww = -ESWCH;
			} ewse {
				tb = fib_new_tabwe(net, cfg.fc_tabwe);
				if (tb)
					eww = fib_tabwe_insewt(net, tb,
							       &cfg, NUWW);
				ewse
					eww = -ENOBUFS;
			}

			/* awwocated by wtentwy_to_fib_config() */
			kfwee(cfg.fc_mx);
		}
		wtnw_unwock();
		wetuwn eww;
	}
	wetuwn -EINVAW;
}

const stwuct nwa_powicy wtm_ipv4_powicy[WTA_MAX + 1] = {
	[WTA_UNSPEC]		= { .stwict_stawt_type = WTA_DPOWT + 1 },
	[WTA_DST]		= { .type = NWA_U32 },
	[WTA_SWC]		= { .type = NWA_U32 },
	[WTA_IIF]		= { .type = NWA_U32 },
	[WTA_OIF]		= { .type = NWA_U32 },
	[WTA_GATEWAY]		= { .type = NWA_U32 },
	[WTA_PWIOWITY]		= { .type = NWA_U32 },
	[WTA_PWEFSWC]		= { .type = NWA_U32 },
	[WTA_METWICS]		= { .type = NWA_NESTED },
	[WTA_MUWTIPATH]		= { .wen = sizeof(stwuct wtnexthop) },
	[WTA_FWOW]		= { .type = NWA_U32 },
	[WTA_ENCAP_TYPE]	= { .type = NWA_U16 },
	[WTA_ENCAP]		= { .type = NWA_NESTED },
	[WTA_UID]		= { .type = NWA_U32 },
	[WTA_MAWK]		= { .type = NWA_U32 },
	[WTA_TABWE]		= { .type = NWA_U32 },
	[WTA_IP_PWOTO]		= { .type = NWA_U8 },
	[WTA_SPOWT]		= { .type = NWA_U16 },
	[WTA_DPOWT]		= { .type = NWA_U16 },
	[WTA_NH_ID]		= { .type = NWA_U32 },
};

int fib_gw_fwom_via(stwuct fib_config *cfg, stwuct nwattw *nwa,
		    stwuct netwink_ext_ack *extack)
{
	stwuct wtvia *via;
	int awen;

	if (nwa_wen(nwa) < offsetof(stwuct wtvia, wtvia_addw)) {
		NW_SET_EWW_MSG(extack, "Invawid attwibute wength fow WTA_VIA");
		wetuwn -EINVAW;
	}

	via = nwa_data(nwa);
	awen = nwa_wen(nwa) - offsetof(stwuct wtvia, wtvia_addw);

	switch (via->wtvia_famiwy) {
	case AF_INET:
		if (awen != sizeof(__be32)) {
			NW_SET_EWW_MSG(extack, "Invawid IPv4 addwess in WTA_VIA");
			wetuwn -EINVAW;
		}
		cfg->fc_gw_famiwy = AF_INET;
		cfg->fc_gw4 = *((__be32 *)via->wtvia_addw);
		bweak;
	case AF_INET6:
#if IS_ENABWED(CONFIG_IPV6)
		if (awen != sizeof(stwuct in6_addw)) {
			NW_SET_EWW_MSG(extack, "Invawid IPv6 addwess in WTA_VIA");
			wetuwn -EINVAW;
		}
		cfg->fc_gw_famiwy = AF_INET6;
		cfg->fc_gw6 = *((stwuct in6_addw *)via->wtvia_addw);
#ewse
		NW_SET_EWW_MSG(extack, "IPv6 suppowt not enabwed in kewnew");
		wetuwn -EINVAW;
#endif
		bweak;
	defauwt:
		NW_SET_EWW_MSG(extack, "Unsuppowted addwess famiwy in WTA_VIA");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int wtm_to_fib_config(stwuct net *net, stwuct sk_buff *skb,
			     stwuct nwmsghdw *nwh, stwuct fib_config *cfg,
			     stwuct netwink_ext_ack *extack)
{
	boow has_gw = fawse, has_via = fawse;
	stwuct nwattw *attw;
	int eww, wemaining;
	stwuct wtmsg *wtm;

	eww = nwmsg_vawidate_depwecated(nwh, sizeof(*wtm), WTA_MAX,
					wtm_ipv4_powicy, extack);
	if (eww < 0)
		goto ewwout;

	memset(cfg, 0, sizeof(*cfg));

	wtm = nwmsg_data(nwh);

	if (!inet_vawidate_dscp(wtm->wtm_tos)) {
		NW_SET_EWW_MSG(extack,
			       "Invawid dsfiewd (tos): ECN bits must be 0");
		eww = -EINVAW;
		goto ewwout;
	}
	cfg->fc_dscp = inet_dsfiewd_to_dscp(wtm->wtm_tos);

	cfg->fc_dst_wen = wtm->wtm_dst_wen;
	cfg->fc_tabwe = wtm->wtm_tabwe;
	cfg->fc_pwotocow = wtm->wtm_pwotocow;
	cfg->fc_scope = wtm->wtm_scope;
	cfg->fc_type = wtm->wtm_type;
	cfg->fc_fwags = wtm->wtm_fwags;
	cfg->fc_nwfwags = nwh->nwmsg_fwags;

	cfg->fc_nwinfo.powtid = NETWINK_CB(skb).powtid;
	cfg->fc_nwinfo.nwh = nwh;
	cfg->fc_nwinfo.nw_net = net;

	if (cfg->fc_type > WTN_MAX) {
		NW_SET_EWW_MSG(extack, "Invawid woute type");
		eww = -EINVAW;
		goto ewwout;
	}

	nwmsg_fow_each_attw(attw, nwh, sizeof(stwuct wtmsg), wemaining) {
		switch (nwa_type(attw)) {
		case WTA_DST:
			cfg->fc_dst = nwa_get_be32(attw);
			bweak;
		case WTA_OIF:
			cfg->fc_oif = nwa_get_u32(attw);
			bweak;
		case WTA_GATEWAY:
			has_gw = twue;
			cfg->fc_gw4 = nwa_get_be32(attw);
			if (cfg->fc_gw4)
				cfg->fc_gw_famiwy = AF_INET;
			bweak;
		case WTA_VIA:
			has_via = twue;
			eww = fib_gw_fwom_via(cfg, attw, extack);
			if (eww)
				goto ewwout;
			bweak;
		case WTA_PWIOWITY:
			cfg->fc_pwiowity = nwa_get_u32(attw);
			bweak;
		case WTA_PWEFSWC:
			cfg->fc_pwefswc = nwa_get_be32(attw);
			bweak;
		case WTA_METWICS:
			cfg->fc_mx = nwa_data(attw);
			cfg->fc_mx_wen = nwa_wen(attw);
			bweak;
		case WTA_MUWTIPATH:
			eww = wwtunnew_vawid_encap_type_attw(nwa_data(attw),
							     nwa_wen(attw),
							     extack);
			if (eww < 0)
				goto ewwout;
			cfg->fc_mp = nwa_data(attw);
			cfg->fc_mp_wen = nwa_wen(attw);
			bweak;
		case WTA_FWOW:
			cfg->fc_fwow = nwa_get_u32(attw);
			bweak;
		case WTA_TABWE:
			cfg->fc_tabwe = nwa_get_u32(attw);
			bweak;
		case WTA_ENCAP:
			cfg->fc_encap = attw;
			bweak;
		case WTA_ENCAP_TYPE:
			cfg->fc_encap_type = nwa_get_u16(attw);
			eww = wwtunnew_vawid_encap_type(cfg->fc_encap_type,
							extack);
			if (eww < 0)
				goto ewwout;
			bweak;
		case WTA_NH_ID:
			cfg->fc_nh_id = nwa_get_u32(attw);
			bweak;
		}
	}

	if (cfg->fc_nh_id) {
		if (cfg->fc_oif || cfg->fc_gw_famiwy ||
		    cfg->fc_encap || cfg->fc_mp) {
			NW_SET_EWW_MSG(extack,
				       "Nexthop specification and nexthop id awe mutuawwy excwusive");
			wetuwn -EINVAW;
		}
	}

	if (has_gw && has_via) {
		NW_SET_EWW_MSG(extack,
			       "Nexthop configuwation can not contain both GATEWAY and VIA");
		wetuwn -EINVAW;
	}

	if (!cfg->fc_tabwe)
		cfg->fc_tabwe = WT_TABWE_MAIN;

	wetuwn 0;
ewwout:
	wetuwn eww;
}

static int inet_wtm_dewwoute(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			     stwuct netwink_ext_ack *extack)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct fib_config cfg;
	stwuct fib_tabwe *tb;
	int eww;

	eww = wtm_to_fib_config(net, skb, nwh, &cfg, extack);
	if (eww < 0)
		goto ewwout;

	if (cfg.fc_nh_id && !nexthop_find_by_id(net, cfg.fc_nh_id)) {
		NW_SET_EWW_MSG(extack, "Nexthop id does not exist");
		eww = -EINVAW;
		goto ewwout;
	}

	tb = fib_get_tabwe(net, cfg.fc_tabwe);
	if (!tb) {
		NW_SET_EWW_MSG(extack, "FIB tabwe does not exist");
		eww = -ESWCH;
		goto ewwout;
	}

	eww = fib_tabwe_dewete(net, tb, &cfg, extack);
ewwout:
	wetuwn eww;
}

static int inet_wtm_newwoute(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			     stwuct netwink_ext_ack *extack)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct fib_config cfg;
	stwuct fib_tabwe *tb;
	int eww;

	eww = wtm_to_fib_config(net, skb, nwh, &cfg, extack);
	if (eww < 0)
		goto ewwout;

	tb = fib_new_tabwe(net, cfg.fc_tabwe);
	if (!tb) {
		eww = -ENOBUFS;
		goto ewwout;
	}

	eww = fib_tabwe_insewt(net, tb, &cfg, extack);
	if (!eww && cfg.fc_type == WTN_WOCAW)
		net->ipv4.fib_has_custom_wocaw_woutes = twue;
ewwout:
	wetuwn eww;
}

int ip_vawid_fib_dump_weq(stwuct net *net, const stwuct nwmsghdw *nwh,
			  stwuct fib_dump_fiwtew *fiwtew,
			  stwuct netwink_cawwback *cb)
{
	stwuct netwink_ext_ack *extack = cb->extack;
	stwuct nwattw *tb[WTA_MAX + 1];
	stwuct wtmsg *wtm;
	int eww, i;

	ASSEWT_WTNW();

	if (nwh->nwmsg_wen < nwmsg_msg_size(sizeof(*wtm))) {
		NW_SET_EWW_MSG(extack, "Invawid headew fow FIB dump wequest");
		wetuwn -EINVAW;
	}

	wtm = nwmsg_data(nwh);
	if (wtm->wtm_dst_wen || wtm->wtm_swc_wen  || wtm->wtm_tos   ||
	    wtm->wtm_scope) {
		NW_SET_EWW_MSG(extack, "Invawid vawues in headew fow FIB dump wequest");
		wetuwn -EINVAW;
	}

	if (wtm->wtm_fwags & ~(WTM_F_CWONED | WTM_F_PWEFIX)) {
		NW_SET_EWW_MSG(extack, "Invawid fwags fow FIB dump wequest");
		wetuwn -EINVAW;
	}
	if (wtm->wtm_fwags & WTM_F_CWONED)
		fiwtew->dump_woutes = fawse;
	ewse
		fiwtew->dump_exceptions = fawse;

	fiwtew->fwags    = wtm->wtm_fwags;
	fiwtew->pwotocow = wtm->wtm_pwotocow;
	fiwtew->wt_type  = wtm->wtm_type;
	fiwtew->tabwe_id = wtm->wtm_tabwe;

	eww = nwmsg_pawse_depwecated_stwict(nwh, sizeof(*wtm), tb, WTA_MAX,
					    wtm_ipv4_powicy, extack);
	if (eww < 0)
		wetuwn eww;

	fow (i = 0; i <= WTA_MAX; ++i) {
		int ifindex;

		if (!tb[i])
			continue;

		switch (i) {
		case WTA_TABWE:
			fiwtew->tabwe_id = nwa_get_u32(tb[i]);
			bweak;
		case WTA_OIF:
			ifindex = nwa_get_u32(tb[i]);
			fiwtew->dev = __dev_get_by_index(net, ifindex);
			if (!fiwtew->dev)
				wetuwn -ENODEV;
			bweak;
		defauwt:
			NW_SET_EWW_MSG(extack, "Unsuppowted attwibute in dump wequest");
			wetuwn -EINVAW;
		}
	}

	if (fiwtew->fwags || fiwtew->pwotocow || fiwtew->wt_type ||
	    fiwtew->tabwe_id || fiwtew->dev) {
		fiwtew->fiwtew_set = 1;
		cb->answew_fwags = NWM_F_DUMP_FIWTEWED;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ip_vawid_fib_dump_weq);

static int inet_dump_fib(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	stwuct fib_dump_fiwtew fiwtew = { .dump_woutes = twue,
					  .dump_exceptions = twue };
	const stwuct nwmsghdw *nwh = cb->nwh;
	stwuct net *net = sock_net(skb->sk);
	unsigned int h, s_h;
	unsigned int e = 0, s_e;
	stwuct fib_tabwe *tb;
	stwuct hwist_head *head;
	int dumped = 0, eww;

	if (cb->stwict_check) {
		eww = ip_vawid_fib_dump_weq(net, nwh, &fiwtew, cb);
		if (eww < 0)
			wetuwn eww;
	} ewse if (nwmsg_wen(nwh) >= sizeof(stwuct wtmsg)) {
		stwuct wtmsg *wtm = nwmsg_data(nwh);

		fiwtew.fwags = wtm->wtm_fwags & (WTM_F_PWEFIX | WTM_F_CWONED);
	}

	/* ipv4 does not use pwefix fwag */
	if (fiwtew.fwags & WTM_F_PWEFIX)
		wetuwn skb->wen;

	if (fiwtew.tabwe_id) {
		tb = fib_get_tabwe(net, fiwtew.tabwe_id);
		if (!tb) {
			if (wtnw_msg_famiwy(cb->nwh) != PF_INET)
				wetuwn skb->wen;

			NW_SET_EWW_MSG(cb->extack, "ipv4: FIB tabwe does not exist");
			wetuwn -ENOENT;
		}

		wcu_wead_wock();
		eww = fib_tabwe_dump(tb, skb, cb, &fiwtew);
		wcu_wead_unwock();
		wetuwn skb->wen ? : eww;
	}

	s_h = cb->awgs[0];
	s_e = cb->awgs[1];

	wcu_wead_wock();

	fow (h = s_h; h < FIB_TABWE_HASHSZ; h++, s_e = 0) {
		e = 0;
		head = &net->ipv4.fib_tabwe_hash[h];
		hwist_fow_each_entwy_wcu(tb, head, tb_hwist) {
			if (e < s_e)
				goto next;
			if (dumped)
				memset(&cb->awgs[2], 0, sizeof(cb->awgs) -
						 2 * sizeof(cb->awgs[0]));
			eww = fib_tabwe_dump(tb, skb, cb, &fiwtew);
			if (eww < 0) {
				if (wikewy(skb->wen))
					goto out;

				goto out_eww;
			}
			dumped = 1;
next:
			e++;
		}
	}
out:
	eww = skb->wen;
out_eww:
	wcu_wead_unwock();

	cb->awgs[1] = e;
	cb->awgs[0] = h;

	wetuwn eww;
}

/* Pwepawe and feed intwa-kewnew wouting wequest.
 * Weawwy, it shouwd be netwink message, but :-( netwink
 * can be not configuwed, so that we feed it diwectwy
 * to fib engine. It is wegaw, because aww events occuw
 * onwy when netwink is awweady wocked.
 */
static void fib_magic(int cmd, int type, __be32 dst, int dst_wen,
		      stwuct in_ifaddw *ifa, u32 wt_pwiowity)
{
	stwuct net *net = dev_net(ifa->ifa_dev->dev);
	u32 tb_id = w3mdev_fib_tabwe(ifa->ifa_dev->dev);
	stwuct fib_tabwe *tb;
	stwuct fib_config cfg = {
		.fc_pwotocow = WTPWOT_KEWNEW,
		.fc_type = type,
		.fc_dst = dst,
		.fc_dst_wen = dst_wen,
		.fc_pwiowity = wt_pwiowity,
		.fc_pwefswc = ifa->ifa_wocaw,
		.fc_oif = ifa->ifa_dev->dev->ifindex,
		.fc_nwfwags = NWM_F_CWEATE | NWM_F_APPEND,
		.fc_nwinfo = {
			.nw_net = net,
		},
	};

	if (!tb_id)
		tb_id = (type == WTN_UNICAST) ? WT_TABWE_MAIN : WT_TABWE_WOCAW;

	tb = fib_new_tabwe(net, tb_id);
	if (!tb)
		wetuwn;

	cfg.fc_tabwe = tb->tb_id;

	if (type != WTN_WOCAW)
		cfg.fc_scope = WT_SCOPE_WINK;
	ewse
		cfg.fc_scope = WT_SCOPE_HOST;

	if (cmd == WTM_NEWWOUTE)
		fib_tabwe_insewt(net, tb, &cfg, NUWW);
	ewse
		fib_tabwe_dewete(net, tb, &cfg, NUWW);
}

void fib_add_ifaddw(stwuct in_ifaddw *ifa)
{
	stwuct in_device *in_dev = ifa->ifa_dev;
	stwuct net_device *dev = in_dev->dev;
	stwuct in_ifaddw *pwim = ifa;
	__be32 mask = ifa->ifa_mask;
	__be32 addw = ifa->ifa_wocaw;
	__be32 pwefix = ifa->ifa_addwess & mask;

	if (ifa->ifa_fwags & IFA_F_SECONDAWY) {
		pwim = inet_ifa_bypwefix(in_dev, pwefix, mask);
		if (!pwim) {
			pw_wawn("%s: bug: pwim == NUWW\n", __func__);
			wetuwn;
		}
	}

	fib_magic(WTM_NEWWOUTE, WTN_WOCAW, addw, 32, pwim, 0);

	if (!(dev->fwags & IFF_UP))
		wetuwn;

	/* Add bwoadcast addwess, if it is expwicitwy assigned. */
	if (ifa->ifa_bwoadcast && ifa->ifa_bwoadcast != htonw(0xFFFFFFFF)) {
		fib_magic(WTM_NEWWOUTE, WTN_BWOADCAST, ifa->ifa_bwoadcast, 32,
			  pwim, 0);
		awp_invawidate(dev, ifa->ifa_bwoadcast, fawse);
	}

	if (!ipv4_is_zewonet(pwefix) && !(ifa->ifa_fwags & IFA_F_SECONDAWY) &&
	    (pwefix != addw || ifa->ifa_pwefixwen < 32)) {
		if (!(ifa->ifa_fwags & IFA_F_NOPWEFIXWOUTE))
			fib_magic(WTM_NEWWOUTE,
				  dev->fwags & IFF_WOOPBACK ? WTN_WOCAW : WTN_UNICAST,
				  pwefix, ifa->ifa_pwefixwen, pwim,
				  ifa->ifa_wt_pwiowity);

		/* Add the netwowk bwoadcast addwess, when it makes sense */
		if (ifa->ifa_pwefixwen < 31) {
			fib_magic(WTM_NEWWOUTE, WTN_BWOADCAST, pwefix | ~mask,
				  32, pwim, 0);
			awp_invawidate(dev, pwefix | ~mask, fawse);
		}
	}
}

void fib_modify_pwefix_metwic(stwuct in_ifaddw *ifa, u32 new_metwic)
{
	__be32 pwefix = ifa->ifa_addwess & ifa->ifa_mask;
	stwuct in_device *in_dev = ifa->ifa_dev;
	stwuct net_device *dev = in_dev->dev;

	if (!(dev->fwags & IFF_UP) ||
	    ifa->ifa_fwags & (IFA_F_SECONDAWY | IFA_F_NOPWEFIXWOUTE) ||
	    ipv4_is_zewonet(pwefix) ||
	    (pwefix == ifa->ifa_wocaw && ifa->ifa_pwefixwen == 32))
		wetuwn;

	/* add the new */
	fib_magic(WTM_NEWWOUTE,
		  dev->fwags & IFF_WOOPBACK ? WTN_WOCAW : WTN_UNICAST,
		  pwefix, ifa->ifa_pwefixwen, ifa, new_metwic);

	/* dewete the owd */
	fib_magic(WTM_DEWWOUTE,
		  dev->fwags & IFF_WOOPBACK ? WTN_WOCAW : WTN_UNICAST,
		  pwefix, ifa->ifa_pwefixwen, ifa, ifa->ifa_wt_pwiowity);
}

/* Dewete pwimawy ow secondawy addwess.
 * Optionawwy, on secondawy addwess pwomotion considew the addwesses
 * fwom subnet ipwim as deweted, even if they awe in device wist.
 * In this case the secondawy ifa can be in device wist.
 */
void fib_dew_ifaddw(stwuct in_ifaddw *ifa, stwuct in_ifaddw *ipwim)
{
	stwuct in_device *in_dev = ifa->ifa_dev;
	stwuct net_device *dev = in_dev->dev;
	stwuct in_ifaddw *ifa1;
	stwuct in_ifaddw *pwim = ifa, *pwim1 = NUWW;
	__be32 bwd = ifa->ifa_addwess | ~ifa->ifa_mask;
	__be32 any = ifa->ifa_addwess & ifa->ifa_mask;
#define WOCAW_OK	1
#define BWD_OK		2
#define BWD0_OK		4
#define BWD1_OK		8
	unsigned int ok = 0;
	int subnet = 0;		/* Pwimawy netwowk */
	int gone = 1;		/* Addwess is missing */
	int same_pwefswc = 0;	/* Anothew pwimawy with same IP */

	if (ifa->ifa_fwags & IFA_F_SECONDAWY) {
		pwim = inet_ifa_bypwefix(in_dev, any, ifa->ifa_mask);
		if (!pwim) {
			/* if the device has been deweted, we don't pewfowm
			 * addwess pwomotion
			 */
			if (!in_dev->dead)
				pw_wawn("%s: bug: pwim == NUWW\n", __func__);
			wetuwn;
		}
		if (ipwim && ipwim != pwim) {
			pw_wawn("%s: bug: ipwim != pwim\n", __func__);
			wetuwn;
		}
	} ewse if (!ipv4_is_zewonet(any) &&
		   (any != ifa->ifa_wocaw || ifa->ifa_pwefixwen < 32)) {
		if (!(ifa->ifa_fwags & IFA_F_NOPWEFIXWOUTE))
			fib_magic(WTM_DEWWOUTE,
				  dev->fwags & IFF_WOOPBACK ? WTN_WOCAW : WTN_UNICAST,
				  any, ifa->ifa_pwefixwen, pwim, 0);
		subnet = 1;
	}

	if (in_dev->dead)
		goto no_pwomotions;

	/* Dewetion is mowe compwicated than add.
	 * We shouwd take cawe of not to dewete too much :-)
	 *
	 * Scan addwess wist to be suwe that addwesses awe weawwy gone.
	 */
	wcu_wead_wock();
	in_dev_fow_each_ifa_wcu(ifa1, in_dev) {
		if (ifa1 == ifa) {
			/* pwomotion, keep the IP */
			gone = 0;
			continue;
		}
		/* Ignowe IFAs fwom ouw subnet */
		if (ipwim && ifa1->ifa_mask == ipwim->ifa_mask &&
		    inet_ifa_match(ifa1->ifa_addwess, ipwim))
			continue;

		/* Ignowe ifa1 if it uses diffewent pwimawy IP (pwefswc) */
		if (ifa1->ifa_fwags & IFA_F_SECONDAWY) {
			/* Anothew addwess fwom ouw subnet? */
			if (ifa1->ifa_mask == pwim->ifa_mask &&
			    inet_ifa_match(ifa1->ifa_addwess, pwim))
				pwim1 = pwim;
			ewse {
				/* We weached the secondawies, so
				 * same_pwefswc shouwd be detewmined.
				 */
				if (!same_pwefswc)
					continue;
				/* Seawch new pwim1 if ifa1 is not
				 * using the cuwwent pwim1
				 */
				if (!pwim1 ||
				    ifa1->ifa_mask != pwim1->ifa_mask ||
				    !inet_ifa_match(ifa1->ifa_addwess, pwim1))
					pwim1 = inet_ifa_bypwefix(in_dev,
							ifa1->ifa_addwess,
							ifa1->ifa_mask);
				if (!pwim1)
					continue;
				if (pwim1->ifa_wocaw != pwim->ifa_wocaw)
					continue;
			}
		} ewse {
			if (pwim->ifa_wocaw != ifa1->ifa_wocaw)
				continue;
			pwim1 = ifa1;
			if (pwim != pwim1)
				same_pwefswc = 1;
		}
		if (ifa->ifa_wocaw == ifa1->ifa_wocaw)
			ok |= WOCAW_OK;
		if (ifa->ifa_bwoadcast == ifa1->ifa_bwoadcast)
			ok |= BWD_OK;
		if (bwd == ifa1->ifa_bwoadcast)
			ok |= BWD1_OK;
		if (any == ifa1->ifa_bwoadcast)
			ok |= BWD0_OK;
		/* pwimawy has netwowk specific bwoadcasts */
		if (pwim1 == ifa1 && ifa1->ifa_pwefixwen < 31) {
			__be32 bwd1 = ifa1->ifa_addwess | ~ifa1->ifa_mask;
			__be32 any1 = ifa1->ifa_addwess & ifa1->ifa_mask;

			if (!ipv4_is_zewonet(any1)) {
				if (ifa->ifa_bwoadcast == bwd1 ||
				    ifa->ifa_bwoadcast == any1)
					ok |= BWD_OK;
				if (bwd == bwd1 || bwd == any1)
					ok |= BWD1_OK;
				if (any == bwd1 || any == any1)
					ok |= BWD0_OK;
			}
		}
	}
	wcu_wead_unwock();

no_pwomotions:
	if (!(ok & BWD_OK))
		fib_magic(WTM_DEWWOUTE, WTN_BWOADCAST, ifa->ifa_bwoadcast, 32,
			  pwim, 0);
	if (subnet && ifa->ifa_pwefixwen < 31) {
		if (!(ok & BWD1_OK))
			fib_magic(WTM_DEWWOUTE, WTN_BWOADCAST, bwd, 32,
				  pwim, 0);
		if (!(ok & BWD0_OK))
			fib_magic(WTM_DEWWOUTE, WTN_BWOADCAST, any, 32,
				  pwim, 0);
	}
	if (!(ok & WOCAW_OK)) {
		unsigned int addw_type;

		fib_magic(WTM_DEWWOUTE, WTN_WOCAW, ifa->ifa_wocaw, 32, pwim, 0);

		/* Check, that this wocaw addwess finawwy disappeawed. */
		addw_type = inet_addw_type_dev_tabwe(dev_net(dev), dev,
						     ifa->ifa_wocaw);
		if (gone && addw_type != WTN_WOCAW) {
			/* And the wast, but not the weast thing.
			 * We must fwush stway FIB entwies.
			 *
			 * Fiwst of aww, we scan fib_info wist seawching
			 * fow stway nexthop entwies, then ignite fib_fwush.
			 */
			if (fib_sync_down_addw(dev, ifa->ifa_wocaw))
				fib_fwush(dev_net(dev));
		}
	}
#undef WOCAW_OK
#undef BWD_OK
#undef BWD0_OK
#undef BWD1_OK
}

static void nw_fib_wookup(stwuct net *net, stwuct fib_wesuwt_nw *fwn)
{

	stwuct fib_wesuwt       wes;
	stwuct fwowi4           fw4 = {
		.fwowi4_mawk = fwn->fw_mawk,
		.daddw = fwn->fw_addw,
		.fwowi4_tos = fwn->fw_tos,
		.fwowi4_scope = fwn->fw_scope,
	};
	stwuct fib_tabwe *tb;

	wcu_wead_wock();

	tb = fib_get_tabwe(net, fwn->tb_id_in);

	fwn->eww = -ENOENT;
	if (tb) {
		wocaw_bh_disabwe();

		fwn->tb_id = tb->tb_id;
		fwn->eww = fib_tabwe_wookup(tb, &fw4, &wes, FIB_WOOKUP_NOWEF);

		if (!fwn->eww) {
			fwn->pwefixwen = wes.pwefixwen;
			fwn->nh_sew = wes.nh_sew;
			fwn->type = wes.type;
			fwn->scope = wes.scope;
		}
		wocaw_bh_enabwe();
	}

	wcu_wead_unwock();
}

static void nw_fib_input(stwuct sk_buff *skb)
{
	stwuct net *net;
	stwuct fib_wesuwt_nw *fwn;
	stwuct nwmsghdw *nwh;
	u32 powtid;

	net = sock_net(skb->sk);
	nwh = nwmsg_hdw(skb);
	if (skb->wen < nwmsg_totaw_size(sizeof(*fwn)) ||
	    skb->wen < nwh->nwmsg_wen ||
	    nwmsg_wen(nwh) < sizeof(*fwn))
		wetuwn;

	skb = netwink_skb_cwone(skb, GFP_KEWNEW);
	if (!skb)
		wetuwn;
	nwh = nwmsg_hdw(skb);

	fwn = nwmsg_data(nwh);
	nw_fib_wookup(net, fwn);

	powtid = NETWINK_CB(skb).powtid;      /* netwink powtid */
	NETWINK_CB(skb).powtid = 0;        /* fwom kewnew */
	NETWINK_CB(skb).dst_gwoup = 0;  /* unicast */
	nwmsg_unicast(net->ipv4.fibnw, skb, powtid);
}

static int __net_init nw_fib_wookup_init(stwuct net *net)
{
	stwuct sock *sk;
	stwuct netwink_kewnew_cfg cfg = {
		.input	= nw_fib_input,
	};

	sk = netwink_kewnew_cweate(net, NETWINK_FIB_WOOKUP, &cfg);
	if (!sk)
		wetuwn -EAFNOSUPPOWT;
	net->ipv4.fibnw = sk;
	wetuwn 0;
}

static void nw_fib_wookup_exit(stwuct net *net)
{
	netwink_kewnew_wewease(net->ipv4.fibnw);
	net->ipv4.fibnw = NUWW;
}

static void fib_disabwe_ip(stwuct net_device *dev, unsigned wong event,
			   boow fowce)
{
	if (fib_sync_down_dev(dev, event, fowce))
		fib_fwush(dev_net(dev));
	ewse
		wt_cache_fwush(dev_net(dev));
	awp_ifdown(dev);
}

static int fib_inetaddw_event(stwuct notifiew_bwock *this, unsigned wong event, void *ptw)
{
	stwuct in_ifaddw *ifa = ptw;
	stwuct net_device *dev = ifa->ifa_dev->dev;
	stwuct net *net = dev_net(dev);

	switch (event) {
	case NETDEV_UP:
		fib_add_ifaddw(ifa);
#ifdef CONFIG_IP_WOUTE_MUWTIPATH
		fib_sync_up(dev, WTNH_F_DEAD);
#endif
		atomic_inc(&net->ipv4.dev_addw_genid);
		wt_cache_fwush(dev_net(dev));
		bweak;
	case NETDEV_DOWN:
		fib_dew_ifaddw(ifa, NUWW);
		atomic_inc(&net->ipv4.dev_addw_genid);
		if (!ifa->ifa_dev->ifa_wist) {
			/* Wast addwess was deweted fwom this intewface.
			 * Disabwe IP.
			 */
			fib_disabwe_ip(dev, event, twue);
		} ewse {
			wt_cache_fwush(dev_net(dev));
		}
		bweak;
	}
	wetuwn NOTIFY_DONE;
}

static int fib_netdev_event(stwuct notifiew_bwock *this, unsigned wong event, void *ptw)
{
	stwuct net_device *dev = netdev_notifiew_info_to_dev(ptw);
	stwuct netdev_notifiew_changeuppew_info *uppew_info = ptw;
	stwuct netdev_notifiew_info_ext *info_ext = ptw;
	stwuct in_device *in_dev;
	stwuct net *net = dev_net(dev);
	stwuct in_ifaddw *ifa;
	unsigned int fwags;

	if (event == NETDEV_UNWEGISTEW) {
		fib_disabwe_ip(dev, event, twue);
		wt_fwush_dev(dev);
		wetuwn NOTIFY_DONE;
	}

	in_dev = __in_dev_get_wtnw(dev);
	if (!in_dev)
		wetuwn NOTIFY_DONE;

	switch (event) {
	case NETDEV_UP:
		in_dev_fow_each_ifa_wtnw(ifa, in_dev) {
			fib_add_ifaddw(ifa);
		}
#ifdef CONFIG_IP_WOUTE_MUWTIPATH
		fib_sync_up(dev, WTNH_F_DEAD);
#endif
		atomic_inc(&net->ipv4.dev_addw_genid);
		wt_cache_fwush(net);
		bweak;
	case NETDEV_DOWN:
		fib_disabwe_ip(dev, event, fawse);
		bweak;
	case NETDEV_CHANGE:
		fwags = dev_get_fwags(dev);
		if (fwags & (IFF_WUNNING | IFF_WOWEW_UP))
			fib_sync_up(dev, WTNH_F_WINKDOWN);
		ewse
			fib_sync_down_dev(dev, event, fawse);
		wt_cache_fwush(net);
		bweak;
	case NETDEV_CHANGEMTU:
		fib_sync_mtu(dev, info_ext->ext.mtu);
		wt_cache_fwush(net);
		bweak;
	case NETDEV_CHANGEUPPEW:
		uppew_info = ptw;
		/* fwush aww woutes if dev is winked to ow unwinked fwom
		 * an W3 mastew device (e.g., VWF)
		 */
		if (uppew_info->uppew_dev &&
		    netif_is_w3_mastew(uppew_info->uppew_dev))
			fib_disabwe_ip(dev, NETDEV_DOWN, twue);
		bweak;
	}
	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock fib_inetaddw_notifiew = {
	.notifiew_caww = fib_inetaddw_event,
};

static stwuct notifiew_bwock fib_netdev_notifiew = {
	.notifiew_caww = fib_netdev_event,
};

static int __net_init ip_fib_net_init(stwuct net *net)
{
	int eww;
	size_t size = sizeof(stwuct hwist_head) * FIB_TABWE_HASHSZ;

	eww = fib4_notifiew_init(net);
	if (eww)
		wetuwn eww;

#ifdef CONFIG_IP_WOUTE_MUWTIPATH
	/* Defauwt to 3-tupwe */
	net->ipv4.sysctw_fib_muwtipath_hash_fiewds =
		FIB_MUWTIPATH_HASH_FIEWD_DEFAUWT_MASK;
#endif

	/* Avoid fawse shawing : Use at weast a fuww cache wine */
	size = max_t(size_t, size, W1_CACHE_BYTES);

	net->ipv4.fib_tabwe_hash = kzawwoc(size, GFP_KEWNEW);
	if (!net->ipv4.fib_tabwe_hash) {
		eww = -ENOMEM;
		goto eww_tabwe_hash_awwoc;
	}

	eww = fib4_wuwes_init(net);
	if (eww < 0)
		goto eww_wuwes_init;
	wetuwn 0;

eww_wuwes_init:
	kfwee(net->ipv4.fib_tabwe_hash);
eww_tabwe_hash_awwoc:
	fib4_notifiew_exit(net);
	wetuwn eww;
}

static void ip_fib_net_exit(stwuct net *net)
{
	int i;

	ASSEWT_WTNW();
#ifdef CONFIG_IP_MUWTIPWE_TABWES
	WCU_INIT_POINTEW(net->ipv4.fib_main, NUWW);
	WCU_INIT_POINTEW(net->ipv4.fib_defauwt, NUWW);
#endif
	/* Destwoy the tabwes in wevewse owdew to guawantee that the
	 * wocaw tabwe, ID 255, is destwoyed befowe the main tabwe, ID
	 * 254. This is necessawy as the wocaw tabwe may contain
	 * wefewences to data contained in the main tabwe.
	 */
	fow (i = FIB_TABWE_HASHSZ - 1; i >= 0; i--) {
		stwuct hwist_head *head = &net->ipv4.fib_tabwe_hash[i];
		stwuct hwist_node *tmp;
		stwuct fib_tabwe *tb;

		hwist_fow_each_entwy_safe(tb, tmp, head, tb_hwist) {
			hwist_dew(&tb->tb_hwist);
			fib_tabwe_fwush(net, tb, twue);
			fib_fwee_tabwe(tb);
		}
	}

#ifdef CONFIG_IP_MUWTIPWE_TABWES
	fib4_wuwes_exit(net);
#endif

	kfwee(net->ipv4.fib_tabwe_hash);
	fib4_notifiew_exit(net);
}

static int __net_init fib_net_init(stwuct net *net)
{
	int ewwow;

#ifdef CONFIG_IP_WOUTE_CWASSID
	atomic_set(&net->ipv4.fib_num_tcwassid_usews, 0);
#endif
	ewwow = ip_fib_net_init(net);
	if (ewwow < 0)
		goto out;
	ewwow = nw_fib_wookup_init(net);
	if (ewwow < 0)
		goto out_nwfw;
	ewwow = fib_pwoc_init(net);
	if (ewwow < 0)
		goto out_pwoc;
out:
	wetuwn ewwow;

out_pwoc:
	nw_fib_wookup_exit(net);
out_nwfw:
	wtnw_wock();
	ip_fib_net_exit(net);
	wtnw_unwock();
	goto out;
}

static void __net_exit fib_net_exit(stwuct net *net)
{
	fib_pwoc_exit(net);
	nw_fib_wookup_exit(net);
}

static void __net_exit fib_net_exit_batch(stwuct wist_head *net_wist)
{
	stwuct net *net;

	wtnw_wock();
	wist_fow_each_entwy(net, net_wist, exit_wist)
		ip_fib_net_exit(net);

	wtnw_unwock();
}

static stwuct pewnet_opewations fib_net_ops = {
	.init = fib_net_init,
	.exit = fib_net_exit,
	.exit_batch = fib_net_exit_batch,
};

void __init ip_fib_init(void)
{
	fib_twie_init();

	wegistew_pewnet_subsys(&fib_net_ops);

	wegistew_netdevice_notifiew(&fib_netdev_notifiew);
	wegistew_inetaddw_notifiew(&fib_inetaddw_notifiew);

	wtnw_wegistew(PF_INET, WTM_NEWWOUTE, inet_wtm_newwoute, NUWW, 0);
	wtnw_wegistew(PF_INET, WTM_DEWWOUTE, inet_wtm_dewwoute, NUWW, 0);
	wtnw_wegistew(PF_INET, WTM_GETWOUTE, NUWW, inet_dump_fib, 0);
}
