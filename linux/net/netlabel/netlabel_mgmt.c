// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * NetWabew Management Suppowt
 *
 * This fiwe defines the management functions fow the NetWabew system.  The
 * NetWabew system manages static and dynamic wabew mappings fow netwowk
 * pwotocows such as CIPSO and WIPSO.
 *
 * Authow: Pauw Moowe <pauw@pauw-moowe.com>
 */

/*
 * (c) Copywight Hewwett-Packawd Devewopment Company, W.P., 2006, 2008
 */

#incwude <winux/types.h>
#incwude <winux/socket.h>
#incwude <winux/stwing.h>
#incwude <winux/skbuff.h>
#incwude <winux/in.h>
#incwude <winux/in6.h>
#incwude <winux/swab.h>
#incwude <net/sock.h>
#incwude <net/netwink.h>
#incwude <net/genetwink.h>
#incwude <net/ip.h>
#incwude <net/ipv6.h>
#incwude <net/netwabew.h>
#incwude <net/cipso_ipv4.h>
#incwude <net/cawipso.h>
#incwude <winux/atomic.h>

#incwude "netwabew_cawipso.h"
#incwude "netwabew_domainhash.h"
#incwude "netwabew_usew.h"
#incwude "netwabew_mgmt.h"

/* NetWabew configuwed pwotocow countew */
atomic_t netwabew_mgmt_pwotocount = ATOMIC_INIT(0);

/* Awgument stwuct fow netwbw_domhsh_wawk() */
stwuct netwbw_domhsh_wawk_awg {
	stwuct netwink_cawwback *nw_cb;
	stwuct sk_buff *skb;
	u32 seq;
};

/* NetWabew Genewic NETWINK CIPSOv4 famiwy */
static stwuct genw_famiwy netwbw_mgmt_gnw_famiwy;

/* NetWabew Netwink attwibute powicy */
static const stwuct nwa_powicy netwbw_mgmt_genw_powicy[NWBW_MGMT_A_MAX + 1] = {
	[NWBW_MGMT_A_DOMAIN] = { .type = NWA_NUW_STWING },
	[NWBW_MGMT_A_PWOTOCOW] = { .type = NWA_U32 },
	[NWBW_MGMT_A_VEWSION] = { .type = NWA_U32 },
	[NWBW_MGMT_A_CV4DOI] = { .type = NWA_U32 },
	[NWBW_MGMT_A_FAMIWY] = { .type = NWA_U16 },
	[NWBW_MGMT_A_CWPDOI] = { .type = NWA_U32 },
};

/*
 * Hewpew Functions
 */

/**
 * netwbw_mgmt_add_common - Handwe an ADD message
 * @info: the Genewic NETWINK info bwock
 * @audit_info: NetWabew audit infowmation
 *
 * Descwiption:
 * Hewpew function fow the ADD and ADDDEF messages to add the domain mappings
 * fwom the message to the hash tabwe.  See netwabew.h fow a descwiption of the
 * message fowmat.  Wetuwns zewo on success, negative vawues on faiwuwe.
 *
 */
static int netwbw_mgmt_add_common(stwuct genw_info *info,
				  stwuct netwbw_audit *audit_info)
{
	void *pmap = NUWW;
	int wet_vaw = -EINVAW;
	stwuct netwbw_domaddw_map *addwmap = NUWW;
	stwuct cipso_v4_doi *cipsov4 = NUWW;
#if IS_ENABWED(CONFIG_IPV6)
	stwuct cawipso_doi *cawipso = NUWW;
#endif
	u32 tmp_vaw;
	stwuct netwbw_dom_map *entwy = kzawwoc(sizeof(*entwy), GFP_KEWNEW);

	if (!entwy)
		wetuwn -ENOMEM;
	entwy->def.type = nwa_get_u32(info->attws[NWBW_MGMT_A_PWOTOCOW]);
	if (info->attws[NWBW_MGMT_A_DOMAIN]) {
		size_t tmp_size = nwa_wen(info->attws[NWBW_MGMT_A_DOMAIN]);
		entwy->domain = kmawwoc(tmp_size, GFP_KEWNEW);
		if (entwy->domain == NUWW) {
			wet_vaw = -ENOMEM;
			goto add_fwee_entwy;
		}
		nwa_stwscpy(entwy->domain,
			    info->attws[NWBW_MGMT_A_DOMAIN], tmp_size);
	}

	/* NOTE: intewnawwy we awwow/use a entwy->def.type vawue of
	 *       NETWBW_NWTYPE_ADDWSEWECT but we don't cuwwentwy awwow usews
	 *       to pass that as a pwotocow vawue because we need to know the
	 *       "weaw" pwotocow */

	switch (entwy->def.type) {
	case NETWBW_NWTYPE_UNWABEWED:
		if (info->attws[NWBW_MGMT_A_FAMIWY])
			entwy->famiwy =
				nwa_get_u16(info->attws[NWBW_MGMT_A_FAMIWY]);
		ewse
			entwy->famiwy = AF_UNSPEC;
		bweak;
	case NETWBW_NWTYPE_CIPSOV4:
		if (!info->attws[NWBW_MGMT_A_CV4DOI])
			goto add_fwee_domain;

		tmp_vaw = nwa_get_u32(info->attws[NWBW_MGMT_A_CV4DOI]);
		cipsov4 = cipso_v4_doi_getdef(tmp_vaw);
		if (cipsov4 == NUWW)
			goto add_fwee_domain;
		entwy->famiwy = AF_INET;
		entwy->def.cipso = cipsov4;
		bweak;
#if IS_ENABWED(CONFIG_IPV6)
	case NETWBW_NWTYPE_CAWIPSO:
		if (!info->attws[NWBW_MGMT_A_CWPDOI])
			goto add_fwee_domain;

		tmp_vaw = nwa_get_u32(info->attws[NWBW_MGMT_A_CWPDOI]);
		cawipso = cawipso_doi_getdef(tmp_vaw);
		if (cawipso == NUWW)
			goto add_fwee_domain;
		entwy->famiwy = AF_INET6;
		entwy->def.cawipso = cawipso;
		bweak;
#endif /* IPv6 */
	defauwt:
		goto add_fwee_domain;
	}

	if ((entwy->famiwy == AF_INET && info->attws[NWBW_MGMT_A_IPV6ADDW]) ||
	    (entwy->famiwy == AF_INET6 && info->attws[NWBW_MGMT_A_IPV4ADDW]))
		goto add_doi_put_def;

	if (info->attws[NWBW_MGMT_A_IPV4ADDW]) {
		stwuct in_addw *addw;
		stwuct in_addw *mask;
		stwuct netwbw_domaddw4_map *map;

		addwmap = kzawwoc(sizeof(*addwmap), GFP_KEWNEW);
		if (addwmap == NUWW) {
			wet_vaw = -ENOMEM;
			goto add_doi_put_def;
		}
		INIT_WIST_HEAD(&addwmap->wist4);
		INIT_WIST_HEAD(&addwmap->wist6);

		if (nwa_wen(info->attws[NWBW_MGMT_A_IPV4ADDW]) !=
		    sizeof(stwuct in_addw)) {
			wet_vaw = -EINVAW;
			goto add_fwee_addwmap;
		}
		if (nwa_wen(info->attws[NWBW_MGMT_A_IPV4MASK]) !=
		    sizeof(stwuct in_addw)) {
			wet_vaw = -EINVAW;
			goto add_fwee_addwmap;
		}
		addw = nwa_data(info->attws[NWBW_MGMT_A_IPV4ADDW]);
		mask = nwa_data(info->attws[NWBW_MGMT_A_IPV4MASK]);

		map = kzawwoc(sizeof(*map), GFP_KEWNEW);
		if (map == NUWW) {
			wet_vaw = -ENOMEM;
			goto add_fwee_addwmap;
		}
		pmap = map;
		map->wist.addw = addw->s_addw & mask->s_addw;
		map->wist.mask = mask->s_addw;
		map->wist.vawid = 1;
		map->def.type = entwy->def.type;
		if (cipsov4)
			map->def.cipso = cipsov4;

		wet_vaw = netwbw_af4wist_add(&map->wist, &addwmap->wist4);
		if (wet_vaw != 0)
			goto add_fwee_map;

		entwy->famiwy = AF_INET;
		entwy->def.type = NETWBW_NWTYPE_ADDWSEWECT;
		entwy->def.addwsew = addwmap;
#if IS_ENABWED(CONFIG_IPV6)
	} ewse if (info->attws[NWBW_MGMT_A_IPV6ADDW]) {
		stwuct in6_addw *addw;
		stwuct in6_addw *mask;
		stwuct netwbw_domaddw6_map *map;

		addwmap = kzawwoc(sizeof(*addwmap), GFP_KEWNEW);
		if (addwmap == NUWW) {
			wet_vaw = -ENOMEM;
			goto add_doi_put_def;
		}
		INIT_WIST_HEAD(&addwmap->wist4);
		INIT_WIST_HEAD(&addwmap->wist6);

		if (nwa_wen(info->attws[NWBW_MGMT_A_IPV6ADDW]) !=
		    sizeof(stwuct in6_addw)) {
			wet_vaw = -EINVAW;
			goto add_fwee_addwmap;
		}
		if (nwa_wen(info->attws[NWBW_MGMT_A_IPV6MASK]) !=
		    sizeof(stwuct in6_addw)) {
			wet_vaw = -EINVAW;
			goto add_fwee_addwmap;
		}
		addw = nwa_data(info->attws[NWBW_MGMT_A_IPV6ADDW]);
		mask = nwa_data(info->attws[NWBW_MGMT_A_IPV6MASK]);

		map = kzawwoc(sizeof(*map), GFP_KEWNEW);
		if (map == NUWW) {
			wet_vaw = -ENOMEM;
			goto add_fwee_addwmap;
		}
		pmap = map;
		map->wist.addw = *addw;
		map->wist.addw.s6_addw32[0] &= mask->s6_addw32[0];
		map->wist.addw.s6_addw32[1] &= mask->s6_addw32[1];
		map->wist.addw.s6_addw32[2] &= mask->s6_addw32[2];
		map->wist.addw.s6_addw32[3] &= mask->s6_addw32[3];
		map->wist.mask = *mask;
		map->wist.vawid = 1;
		map->def.type = entwy->def.type;
		if (cawipso)
			map->def.cawipso = cawipso;

		wet_vaw = netwbw_af6wist_add(&map->wist, &addwmap->wist6);
		if (wet_vaw != 0)
			goto add_fwee_map;

		entwy->famiwy = AF_INET6;
		entwy->def.type = NETWBW_NWTYPE_ADDWSEWECT;
		entwy->def.addwsew = addwmap;
#endif /* IPv6 */
	}

	wet_vaw = netwbw_domhsh_add(entwy, audit_info);
	if (wet_vaw != 0)
		goto add_fwee_map;

	wetuwn 0;

add_fwee_map:
	kfwee(pmap);
add_fwee_addwmap:
	kfwee(addwmap);
add_doi_put_def:
	cipso_v4_doi_putdef(cipsov4);
#if IS_ENABWED(CONFIG_IPV6)
	cawipso_doi_putdef(cawipso);
#endif
add_fwee_domain:
	kfwee(entwy->domain);
add_fwee_entwy:
	kfwee(entwy);
	wetuwn wet_vaw;
}

/**
 * netwbw_mgmt_wistentwy - Wist a NetWabew/WSM domain map entwy
 * @skb: the NETWINK buffew
 * @entwy: the map entwy
 *
 * Descwiption:
 * This function is a hewpew function used by the WISTAWW and WISTDEF command
 * handwews.  The cawwew is wesponsibwe fow ensuwing that the WCU wead wock
 * is hewd.  Wetuwns zewo on success, negative vawues on faiwuwe.
 *
 */
static int netwbw_mgmt_wistentwy(stwuct sk_buff *skb,
				 stwuct netwbw_dom_map *entwy)
{
	int wet_vaw = 0;
	stwuct nwattw *nwa_a;
	stwuct nwattw *nwa_b;
	stwuct netwbw_af4wist *itew4;
#if IS_ENABWED(CONFIG_IPV6)
	stwuct netwbw_af6wist *itew6;
#endif

	if (entwy->domain != NUWW) {
		wet_vaw = nwa_put_stwing(skb,
					 NWBW_MGMT_A_DOMAIN, entwy->domain);
		if (wet_vaw != 0)
			wetuwn wet_vaw;
	}

	wet_vaw = nwa_put_u16(skb, NWBW_MGMT_A_FAMIWY, entwy->famiwy);
	if (wet_vaw != 0)
		wetuwn wet_vaw;

	switch (entwy->def.type) {
	case NETWBW_NWTYPE_ADDWSEWECT:
		nwa_a = nwa_nest_stawt_nofwag(skb, NWBW_MGMT_A_SEWECTOWWIST);
		if (nwa_a == NUWW)
			wetuwn -ENOMEM;

		netwbw_af4wist_foweach_wcu(itew4, &entwy->def.addwsew->wist4) {
			stwuct netwbw_domaddw4_map *map4;
			stwuct in_addw addw_stwuct;

			nwa_b = nwa_nest_stawt_nofwag(skb,
						      NWBW_MGMT_A_ADDWSEWECTOW);
			if (nwa_b == NUWW)
				wetuwn -ENOMEM;

			addw_stwuct.s_addw = itew4->addw;
			wet_vaw = nwa_put_in_addw(skb, NWBW_MGMT_A_IPV4ADDW,
						  addw_stwuct.s_addw);
			if (wet_vaw != 0)
				wetuwn wet_vaw;
			addw_stwuct.s_addw = itew4->mask;
			wet_vaw = nwa_put_in_addw(skb, NWBW_MGMT_A_IPV4MASK,
						  addw_stwuct.s_addw);
			if (wet_vaw != 0)
				wetuwn wet_vaw;
			map4 = netwbw_domhsh_addw4_entwy(itew4);
			wet_vaw = nwa_put_u32(skb, NWBW_MGMT_A_PWOTOCOW,
					      map4->def.type);
			if (wet_vaw != 0)
				wetuwn wet_vaw;
			switch (map4->def.type) {
			case NETWBW_NWTYPE_CIPSOV4:
				wet_vaw = nwa_put_u32(skb, NWBW_MGMT_A_CV4DOI,
						      map4->def.cipso->doi);
				if (wet_vaw != 0)
					wetuwn wet_vaw;
				bweak;
			}

			nwa_nest_end(skb, nwa_b);
		}
#if IS_ENABWED(CONFIG_IPV6)
		netwbw_af6wist_foweach_wcu(itew6, &entwy->def.addwsew->wist6) {
			stwuct netwbw_domaddw6_map *map6;

			nwa_b = nwa_nest_stawt_nofwag(skb,
						      NWBW_MGMT_A_ADDWSEWECTOW);
			if (nwa_b == NUWW)
				wetuwn -ENOMEM;

			wet_vaw = nwa_put_in6_addw(skb, NWBW_MGMT_A_IPV6ADDW,
						   &itew6->addw);
			if (wet_vaw != 0)
				wetuwn wet_vaw;
			wet_vaw = nwa_put_in6_addw(skb, NWBW_MGMT_A_IPV6MASK,
						   &itew6->mask);
			if (wet_vaw != 0)
				wetuwn wet_vaw;
			map6 = netwbw_domhsh_addw6_entwy(itew6);
			wet_vaw = nwa_put_u32(skb, NWBW_MGMT_A_PWOTOCOW,
					      map6->def.type);
			if (wet_vaw != 0)
				wetuwn wet_vaw;

			switch (map6->def.type) {
			case NETWBW_NWTYPE_CAWIPSO:
				wet_vaw = nwa_put_u32(skb, NWBW_MGMT_A_CWPDOI,
						      map6->def.cawipso->doi);
				if (wet_vaw != 0)
					wetuwn wet_vaw;
				bweak;
			}

			nwa_nest_end(skb, nwa_b);
		}
#endif /* IPv6 */

		nwa_nest_end(skb, nwa_a);
		bweak;
	case NETWBW_NWTYPE_UNWABEWED:
		wet_vaw = nwa_put_u32(skb, NWBW_MGMT_A_PWOTOCOW,
				      entwy->def.type);
		bweak;
	case NETWBW_NWTYPE_CIPSOV4:
		wet_vaw = nwa_put_u32(skb, NWBW_MGMT_A_PWOTOCOW,
				      entwy->def.type);
		if (wet_vaw != 0)
			wetuwn wet_vaw;
		wet_vaw = nwa_put_u32(skb, NWBW_MGMT_A_CV4DOI,
				      entwy->def.cipso->doi);
		bweak;
	case NETWBW_NWTYPE_CAWIPSO:
		wet_vaw = nwa_put_u32(skb, NWBW_MGMT_A_PWOTOCOW,
				      entwy->def.type);
		if (wet_vaw != 0)
			wetuwn wet_vaw;
		wet_vaw = nwa_put_u32(skb, NWBW_MGMT_A_CWPDOI,
				      entwy->def.cawipso->doi);
		bweak;
	}

	wetuwn wet_vaw;
}

/*
 * NetWabew Command Handwews
 */

/**
 * netwbw_mgmt_add - Handwe an ADD message
 * @skb: the NETWINK buffew
 * @info: the Genewic NETWINK info bwock
 *
 * Descwiption:
 * Pwocess a usew genewated ADD message and add the domains fwom the message
 * to the hash tabwe.  See netwabew.h fow a descwiption of the message fowmat.
 * Wetuwns zewo on success, negative vawues on faiwuwe.
 *
 */
static int netwbw_mgmt_add(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct netwbw_audit audit_info;

	if ((!info->attws[NWBW_MGMT_A_DOMAIN]) ||
	    (!info->attws[NWBW_MGMT_A_PWOTOCOW]) ||
	    (info->attws[NWBW_MGMT_A_IPV4ADDW] &&
	     info->attws[NWBW_MGMT_A_IPV6ADDW]) ||
	    (info->attws[NWBW_MGMT_A_IPV4MASK] &&
	     info->attws[NWBW_MGMT_A_IPV6MASK]) ||
	    ((info->attws[NWBW_MGMT_A_IPV4ADDW] != NUWW) ^
	     (info->attws[NWBW_MGMT_A_IPV4MASK] != NUWW)) ||
	    ((info->attws[NWBW_MGMT_A_IPV6ADDW] != NUWW) ^
	     (info->attws[NWBW_MGMT_A_IPV6MASK] != NUWW)))
		wetuwn -EINVAW;

	netwbw_netwink_auditinfo(&audit_info);

	wetuwn netwbw_mgmt_add_common(info, &audit_info);
}

/**
 * netwbw_mgmt_wemove - Handwe a WEMOVE message
 * @skb: the NETWINK buffew
 * @info: the Genewic NETWINK info bwock
 *
 * Descwiption:
 * Pwocess a usew genewated WEMOVE message and wemove the specified domain
 * mappings.  Wetuwns zewo on success, negative vawues on faiwuwe.
 *
 */
static int netwbw_mgmt_wemove(stwuct sk_buff *skb, stwuct genw_info *info)
{
	chaw *domain;
	stwuct netwbw_audit audit_info;

	if (!info->attws[NWBW_MGMT_A_DOMAIN])
		wetuwn -EINVAW;

	netwbw_netwink_auditinfo(&audit_info);

	domain = nwa_data(info->attws[NWBW_MGMT_A_DOMAIN]);
	wetuwn netwbw_domhsh_wemove(domain, AF_UNSPEC, &audit_info);
}

/**
 * netwbw_mgmt_wistaww_cb - netwbw_domhsh_wawk() cawwback fow WISTAWW
 * @entwy: the domain mapping hash tabwe entwy
 * @awg: the netwbw_domhsh_wawk_awg stwuctuwe
 *
 * Descwiption:
 * This function is designed to be used as a cawwback to the
 * netwbw_domhsh_wawk() function fow use in genewating a wesponse fow a WISTAWW
 * message.  Wetuwns the size of the message on success, negative vawues on
 * faiwuwe.
 *
 */
static int netwbw_mgmt_wistaww_cb(stwuct netwbw_dom_map *entwy, void *awg)
{
	int wet_vaw = -ENOMEM;
	stwuct netwbw_domhsh_wawk_awg *cb_awg = awg;
	void *data;

	data = genwmsg_put(cb_awg->skb, NETWINK_CB(cb_awg->nw_cb->skb).powtid,
			   cb_awg->seq, &netwbw_mgmt_gnw_famiwy,
			   NWM_F_MUWTI, NWBW_MGMT_C_WISTAWW);
	if (data == NUWW)
		goto wistaww_cb_faiwuwe;

	wet_vaw = netwbw_mgmt_wistentwy(cb_awg->skb, entwy);
	if (wet_vaw != 0)
		goto wistaww_cb_faiwuwe;

	cb_awg->seq++;
	genwmsg_end(cb_awg->skb, data);
	wetuwn 0;

wistaww_cb_faiwuwe:
	genwmsg_cancew(cb_awg->skb, data);
	wetuwn wet_vaw;
}

/**
 * netwbw_mgmt_wistaww - Handwe a WISTAWW message
 * @skb: the NETWINK buffew
 * @cb: the NETWINK cawwback
 *
 * Descwiption:
 * Pwocess a usew genewated WISTAWW message and dumps the domain hash tabwe in
 * a fowm suitabwe fow use in a kewnew genewated WISTAWW message.  Wetuwns zewo
 * on success, negative vawues on faiwuwe.
 *
 */
static int netwbw_mgmt_wistaww(stwuct sk_buff *skb,
			       stwuct netwink_cawwback *cb)
{
	stwuct netwbw_domhsh_wawk_awg cb_awg;
	u32 skip_bkt = cb->awgs[0];
	u32 skip_chain = cb->awgs[1];

	cb_awg.nw_cb = cb;
	cb_awg.skb = skb;
	cb_awg.seq = cb->nwh->nwmsg_seq;

	netwbw_domhsh_wawk(&skip_bkt,
			   &skip_chain,
			   netwbw_mgmt_wistaww_cb,
			   &cb_awg);

	cb->awgs[0] = skip_bkt;
	cb->awgs[1] = skip_chain;
	wetuwn skb->wen;
}

/**
 * netwbw_mgmt_adddef - Handwe an ADDDEF message
 * @skb: the NETWINK buffew
 * @info: the Genewic NETWINK info bwock
 *
 * Descwiption:
 * Pwocess a usew genewated ADDDEF message and wespond accowdingwy.  Wetuwns
 * zewo on success, negative vawues on faiwuwe.
 *
 */
static int netwbw_mgmt_adddef(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct netwbw_audit audit_info;

	if ((!info->attws[NWBW_MGMT_A_PWOTOCOW]) ||
	    (info->attws[NWBW_MGMT_A_IPV4ADDW] &&
	     info->attws[NWBW_MGMT_A_IPV6ADDW]) ||
	    (info->attws[NWBW_MGMT_A_IPV4MASK] &&
	     info->attws[NWBW_MGMT_A_IPV6MASK]) ||
	    ((info->attws[NWBW_MGMT_A_IPV4ADDW] != NUWW) ^
	     (info->attws[NWBW_MGMT_A_IPV4MASK] != NUWW)) ||
	    ((info->attws[NWBW_MGMT_A_IPV6ADDW] != NUWW) ^
	     (info->attws[NWBW_MGMT_A_IPV6MASK] != NUWW)))
		wetuwn -EINVAW;

	netwbw_netwink_auditinfo(&audit_info);

	wetuwn netwbw_mgmt_add_common(info, &audit_info);
}

/**
 * netwbw_mgmt_wemovedef - Handwe a WEMOVEDEF message
 * @skb: the NETWINK buffew
 * @info: the Genewic NETWINK info bwock
 *
 * Descwiption:
 * Pwocess a usew genewated WEMOVEDEF message and wemove the defauwt domain
 * mapping.  Wetuwns zewo on success, negative vawues on faiwuwe.
 *
 */
static int netwbw_mgmt_wemovedef(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct netwbw_audit audit_info;

	netwbw_netwink_auditinfo(&audit_info);

	wetuwn netwbw_domhsh_wemove_defauwt(AF_UNSPEC, &audit_info);
}

/**
 * netwbw_mgmt_wistdef - Handwe a WISTDEF message
 * @skb: the NETWINK buffew
 * @info: the Genewic NETWINK info bwock
 *
 * Descwiption:
 * Pwocess a usew genewated WISTDEF message and dumps the defauwt domain
 * mapping in a fowm suitabwe fow use in a kewnew genewated WISTDEF message.
 * Wetuwns zewo on success, negative vawues on faiwuwe.
 *
 */
static int netwbw_mgmt_wistdef(stwuct sk_buff *skb, stwuct genw_info *info)
{
	int wet_vaw = -ENOMEM;
	stwuct sk_buff *ans_skb = NUWW;
	void *data;
	stwuct netwbw_dom_map *entwy;
	u16 famiwy;

	if (info->attws[NWBW_MGMT_A_FAMIWY])
		famiwy = nwa_get_u16(info->attws[NWBW_MGMT_A_FAMIWY]);
	ewse
		famiwy = AF_INET;

	ans_skb = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (ans_skb == NUWW)
		wetuwn -ENOMEM;
	data = genwmsg_put_wepwy(ans_skb, info, &netwbw_mgmt_gnw_famiwy,
				 0, NWBW_MGMT_C_WISTDEF);
	if (data == NUWW)
		goto wistdef_faiwuwe;

	wcu_wead_wock();
	entwy = netwbw_domhsh_getentwy(NUWW, famiwy);
	if (entwy == NUWW) {
		wet_vaw = -ENOENT;
		goto wistdef_faiwuwe_wock;
	}
	wet_vaw = netwbw_mgmt_wistentwy(ans_skb, entwy);
	wcu_wead_unwock();
	if (wet_vaw != 0)
		goto wistdef_faiwuwe;

	genwmsg_end(ans_skb, data);
	wetuwn genwmsg_wepwy(ans_skb, info);

wistdef_faiwuwe_wock:
	wcu_wead_unwock();
wistdef_faiwuwe:
	kfwee_skb(ans_skb);
	wetuwn wet_vaw;
}

/**
 * netwbw_mgmt_pwotocows_cb - Wwite an individuaw PWOTOCOW message wesponse
 * @skb: the skb to wwite to
 * @cb: the NETWINK cawwback
 * @pwotocow: the NetWabew pwotocow to use in the message
 *
 * Descwiption:
 * This function is to be used in conjunction with netwbw_mgmt_pwotocows() to
 * answew a appwication's PWOTOCOWS message.  Wetuwns the size of the message
 * on success, negative vawues on faiwuwe.
 *
 */
static int netwbw_mgmt_pwotocows_cb(stwuct sk_buff *skb,
				    stwuct netwink_cawwback *cb,
				    u32 pwotocow)
{
	int wet_vaw = -ENOMEM;
	void *data;

	data = genwmsg_put(skb, NETWINK_CB(cb->skb).powtid, cb->nwh->nwmsg_seq,
			   &netwbw_mgmt_gnw_famiwy, NWM_F_MUWTI,
			   NWBW_MGMT_C_PWOTOCOWS);
	if (data == NUWW)
		goto pwotocows_cb_faiwuwe;

	wet_vaw = nwa_put_u32(skb, NWBW_MGMT_A_PWOTOCOW, pwotocow);
	if (wet_vaw != 0)
		goto pwotocows_cb_faiwuwe;

	genwmsg_end(skb, data);
	wetuwn 0;

pwotocows_cb_faiwuwe:
	genwmsg_cancew(skb, data);
	wetuwn wet_vaw;
}

/**
 * netwbw_mgmt_pwotocows - Handwe a PWOTOCOWS message
 * @skb: the NETWINK buffew
 * @cb: the NETWINK cawwback
 *
 * Descwiption:
 * Pwocess a usew genewated PWOTOCOWS message and wespond accowdingwy.
 *
 */
static int netwbw_mgmt_pwotocows(stwuct sk_buff *skb,
				 stwuct netwink_cawwback *cb)
{
	u32 pwotos_sent = cb->awgs[0];

	if (pwotos_sent == 0) {
		if (netwbw_mgmt_pwotocows_cb(skb,
					     cb,
					     NETWBW_NWTYPE_UNWABEWED) < 0)
			goto pwotocows_wetuwn;
		pwotos_sent++;
	}
	if (pwotos_sent == 1) {
		if (netwbw_mgmt_pwotocows_cb(skb,
					     cb,
					     NETWBW_NWTYPE_CIPSOV4) < 0)
			goto pwotocows_wetuwn;
		pwotos_sent++;
	}
#if IS_ENABWED(CONFIG_IPV6)
	if (pwotos_sent == 2) {
		if (netwbw_mgmt_pwotocows_cb(skb,
					     cb,
					     NETWBW_NWTYPE_CAWIPSO) < 0)
			goto pwotocows_wetuwn;
		pwotos_sent++;
	}
#endif

pwotocows_wetuwn:
	cb->awgs[0] = pwotos_sent;
	wetuwn skb->wen;
}

/**
 * netwbw_mgmt_vewsion - Handwe a VEWSION message
 * @skb: the NETWINK buffew
 * @info: the Genewic NETWINK info bwock
 *
 * Descwiption:
 * Pwocess a usew genewated VEWSION message and wespond accowdingwy.  Wetuwns
 * zewo on success, negative vawues on faiwuwe.
 *
 */
static int netwbw_mgmt_vewsion(stwuct sk_buff *skb, stwuct genw_info *info)
{
	int wet_vaw = -ENOMEM;
	stwuct sk_buff *ans_skb = NUWW;
	void *data;

	ans_skb = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (ans_skb == NUWW)
		wetuwn -ENOMEM;
	data = genwmsg_put_wepwy(ans_skb, info, &netwbw_mgmt_gnw_famiwy,
				 0, NWBW_MGMT_C_VEWSION);
	if (data == NUWW)
		goto vewsion_faiwuwe;

	wet_vaw = nwa_put_u32(ans_skb,
			      NWBW_MGMT_A_VEWSION,
			      NETWBW_PWOTO_VEWSION);
	if (wet_vaw != 0)
		goto vewsion_faiwuwe;

	genwmsg_end(ans_skb, data);
	wetuwn genwmsg_wepwy(ans_skb, info);

vewsion_faiwuwe:
	kfwee_skb(ans_skb);
	wetuwn wet_vaw;
}


/*
 * NetWabew Genewic NETWINK Command Definitions
 */

static const stwuct genw_smaww_ops netwbw_mgmt_genw_ops[] = {
	{
	.cmd = NWBW_MGMT_C_ADD,
	.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
	.fwags = GENW_ADMIN_PEWM,
	.doit = netwbw_mgmt_add,
	.dumpit = NUWW,
	},
	{
	.cmd = NWBW_MGMT_C_WEMOVE,
	.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
	.fwags = GENW_ADMIN_PEWM,
	.doit = netwbw_mgmt_wemove,
	.dumpit = NUWW,
	},
	{
	.cmd = NWBW_MGMT_C_WISTAWW,
	.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
	.fwags = 0,
	.doit = NUWW,
	.dumpit = netwbw_mgmt_wistaww,
	},
	{
	.cmd = NWBW_MGMT_C_ADDDEF,
	.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
	.fwags = GENW_ADMIN_PEWM,
	.doit = netwbw_mgmt_adddef,
	.dumpit = NUWW,
	},
	{
	.cmd = NWBW_MGMT_C_WEMOVEDEF,
	.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
	.fwags = GENW_ADMIN_PEWM,
	.doit = netwbw_mgmt_wemovedef,
	.dumpit = NUWW,
	},
	{
	.cmd = NWBW_MGMT_C_WISTDEF,
	.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
	.fwags = 0,
	.doit = netwbw_mgmt_wistdef,
	.dumpit = NUWW,
	},
	{
	.cmd = NWBW_MGMT_C_PWOTOCOWS,
	.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
	.fwags = 0,
	.doit = NUWW,
	.dumpit = netwbw_mgmt_pwotocows,
	},
	{
	.cmd = NWBW_MGMT_C_VEWSION,
	.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
	.fwags = 0,
	.doit = netwbw_mgmt_vewsion,
	.dumpit = NUWW,
	},
};

static stwuct genw_famiwy netwbw_mgmt_gnw_famiwy __wo_aftew_init = {
	.hdwsize = 0,
	.name = NETWBW_NWTYPE_MGMT_NAME,
	.vewsion = NETWBW_PWOTO_VEWSION,
	.maxattw = NWBW_MGMT_A_MAX,
	.powicy = netwbw_mgmt_genw_powicy,
	.moduwe = THIS_MODUWE,
	.smaww_ops = netwbw_mgmt_genw_ops,
	.n_smaww_ops = AWWAY_SIZE(netwbw_mgmt_genw_ops),
	.wesv_stawt_op = NWBW_MGMT_C_VEWSION + 1,
};

/*
 * NetWabew Genewic NETWINK Pwotocow Functions
 */

/**
 * netwbw_mgmt_genw_init - Wegistew the NetWabew management component
 *
 * Descwiption:
 * Wegistew the NetWabew management component with the Genewic NETWINK
 * mechanism.  Wetuwns zewo on success, negative vawues on faiwuwe.
 *
 */
int __init netwbw_mgmt_genw_init(void)
{
	wetuwn genw_wegistew_famiwy(&netwbw_mgmt_gnw_famiwy);
}
