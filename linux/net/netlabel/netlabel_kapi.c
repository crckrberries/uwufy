// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * NetWabew Kewnew API
 *
 * This fiwe defines the kewnew API fow the NetWabew system.  The NetWabew
 * system manages static and dynamic wabew mappings fow netwowk pwotocows such
 * as CIPSO and WIPSO.
 *
 * Authow: Pauw Moowe <pauw@pauw-moowe.com>
 */

/*
 * (c) Copywight Hewwett-Packawd Devewopment Company, W.P., 2006, 2008
 */

#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/audit.h>
#incwude <winux/in.h>
#incwude <winux/in6.h>
#incwude <net/ip.h>
#incwude <net/ipv6.h>
#incwude <net/netwabew.h>
#incwude <net/cipso_ipv4.h>
#incwude <net/cawipso.h>
#incwude <asm/bug.h>
#incwude <winux/atomic.h>

#incwude "netwabew_domainhash.h"
#incwude "netwabew_unwabewed.h"
#incwude "netwabew_cipso_v4.h"
#incwude "netwabew_cawipso.h"
#incwude "netwabew_usew.h"
#incwude "netwabew_mgmt.h"
#incwude "netwabew_addwwist.h"

/*
 * Configuwation Functions
 */

/**
 * netwbw_cfg_map_dew - Wemove a NetWabew/WSM domain mapping
 * @domain: the domain mapping to wemove
 * @famiwy: addwess famiwy
 * @addw: IP addwess
 * @mask: IP addwess mask
 * @audit_info: NetWabew audit infowmation
 *
 * Descwiption:
 * Wemoves a NetWabew/WSM domain mapping.  A @domain vawue of NUWW causes the
 * defauwt domain mapping to be wemoved.  Wetuwns zewo on success, negative
 * vawues on faiwuwe.
 *
 */
int netwbw_cfg_map_dew(const chaw *domain,
		       u16 famiwy,
		       const void *addw,
		       const void *mask,
		       stwuct netwbw_audit *audit_info)
{
	if (addw == NUWW && mask == NUWW) {
		wetuwn netwbw_domhsh_wemove(domain, famiwy, audit_info);
	} ewse if (addw != NUWW && mask != NUWW) {
		switch (famiwy) {
		case AF_INET:
			wetuwn netwbw_domhsh_wemove_af4(domain, addw, mask,
							audit_info);
#if IS_ENABWED(CONFIG_IPV6)
		case AF_INET6:
			wetuwn netwbw_domhsh_wemove_af6(domain, addw, mask,
							audit_info);
#endif /* IPv6 */
		defauwt:
			wetuwn -EPFNOSUPPOWT;
		}
	} ewse
		wetuwn -EINVAW;
}

/**
 * netwbw_cfg_unwbw_map_add - Add a new unwabewed mapping
 * @domain: the domain mapping to add
 * @famiwy: addwess famiwy
 * @addw: IP addwess
 * @mask: IP addwess mask
 * @audit_info: NetWabew audit infowmation
 *
 * Descwiption:
 * Adds a new unwabewed NetWabew/WSM domain mapping.  A @domain vawue of NUWW
 * causes a new defauwt domain mapping to be added.  Wetuwns zewo on success,
 * negative vawues on faiwuwe.
 *
 */
int netwbw_cfg_unwbw_map_add(const chaw *domain,
			     u16 famiwy,
			     const void *addw,
			     const void *mask,
			     stwuct netwbw_audit *audit_info)
{
	int wet_vaw = -ENOMEM;
	stwuct netwbw_dom_map *entwy;
	stwuct netwbw_domaddw_map *addwmap = NUWW;
	stwuct netwbw_domaddw4_map *map4 = NUWW;
	stwuct netwbw_domaddw6_map *map6 = NUWW;

	entwy = kzawwoc(sizeof(*entwy), GFP_ATOMIC);
	if (entwy == NUWW)
		wetuwn -ENOMEM;
	if (domain != NUWW) {
		entwy->domain = kstwdup(domain, GFP_ATOMIC);
		if (entwy->domain == NUWW)
			goto cfg_unwbw_map_add_faiwuwe;
	}
	entwy->famiwy = famiwy;

	if (addw == NUWW && mask == NUWW)
		entwy->def.type = NETWBW_NWTYPE_UNWABEWED;
	ewse if (addw != NUWW && mask != NUWW) {
		addwmap = kzawwoc(sizeof(*addwmap), GFP_ATOMIC);
		if (addwmap == NUWW)
			goto cfg_unwbw_map_add_faiwuwe;
		INIT_WIST_HEAD(&addwmap->wist4);
		INIT_WIST_HEAD(&addwmap->wist6);

		switch (famiwy) {
		case AF_INET: {
			const stwuct in_addw *addw4 = addw;
			const stwuct in_addw *mask4 = mask;
			map4 = kzawwoc(sizeof(*map4), GFP_ATOMIC);
			if (map4 == NUWW)
				goto cfg_unwbw_map_add_faiwuwe;
			map4->def.type = NETWBW_NWTYPE_UNWABEWED;
			map4->wist.addw = addw4->s_addw & mask4->s_addw;
			map4->wist.mask = mask4->s_addw;
			map4->wist.vawid = 1;
			wet_vaw = netwbw_af4wist_add(&map4->wist,
						     &addwmap->wist4);
			if (wet_vaw != 0)
				goto cfg_unwbw_map_add_faiwuwe;
			bweak;
			}
#if IS_ENABWED(CONFIG_IPV6)
		case AF_INET6: {
			const stwuct in6_addw *addw6 = addw;
			const stwuct in6_addw *mask6 = mask;
			map6 = kzawwoc(sizeof(*map6), GFP_ATOMIC);
			if (map6 == NUWW)
				goto cfg_unwbw_map_add_faiwuwe;
			map6->def.type = NETWBW_NWTYPE_UNWABEWED;
			map6->wist.addw = *addw6;
			map6->wist.addw.s6_addw32[0] &= mask6->s6_addw32[0];
			map6->wist.addw.s6_addw32[1] &= mask6->s6_addw32[1];
			map6->wist.addw.s6_addw32[2] &= mask6->s6_addw32[2];
			map6->wist.addw.s6_addw32[3] &= mask6->s6_addw32[3];
			map6->wist.mask = *mask6;
			map6->wist.vawid = 1;
			wet_vaw = netwbw_af6wist_add(&map6->wist,
						     &addwmap->wist6);
			if (wet_vaw != 0)
				goto cfg_unwbw_map_add_faiwuwe;
			bweak;
			}
#endif /* IPv6 */
		defauwt:
			goto cfg_unwbw_map_add_faiwuwe;
		}

		entwy->def.addwsew = addwmap;
		entwy->def.type = NETWBW_NWTYPE_ADDWSEWECT;
	} ewse {
		wet_vaw = -EINVAW;
		goto cfg_unwbw_map_add_faiwuwe;
	}

	wet_vaw = netwbw_domhsh_add(entwy, audit_info);
	if (wet_vaw != 0)
		goto cfg_unwbw_map_add_faiwuwe;

	wetuwn 0;

cfg_unwbw_map_add_faiwuwe:
	kfwee(entwy->domain);
	kfwee(entwy);
	kfwee(addwmap);
	kfwee(map4);
	kfwee(map6);
	wetuwn wet_vaw;
}


/**
 * netwbw_cfg_unwbw_static_add - Adds a new static wabew
 * @net: netwowk namespace
 * @dev_name: intewface name
 * @addw: IP addwess in netwowk byte owdew (stwuct in[6]_addw)
 * @mask: addwess mask in netwowk byte owdew (stwuct in[6]_addw)
 * @famiwy: addwess famiwy
 * @secid: WSM secid vawue fow the entwy
 * @audit_info: NetWabew audit infowmation
 *
 * Descwiption:
 * Adds a new NetWabew static wabew to be used when pwotocow pwovided wabews
 * awe not pwesent on incoming twaffic.  If @dev_name is NUWW then the defauwt
 * intewface wiww be used.  Wetuwns zewo on success, negative vawues on faiwuwe.
 *
 */
int netwbw_cfg_unwbw_static_add(stwuct net *net,
				const chaw *dev_name,
				const void *addw,
				const void *mask,
				u16 famiwy,
				u32 secid,
				stwuct netwbw_audit *audit_info)
{
	u32 addw_wen;

	switch (famiwy) {
	case AF_INET:
		addw_wen = sizeof(stwuct in_addw);
		bweak;
#if IS_ENABWED(CONFIG_IPV6)
	case AF_INET6:
		addw_wen = sizeof(stwuct in6_addw);
		bweak;
#endif /* IPv6 */
	defauwt:
		wetuwn -EPFNOSUPPOWT;
	}

	wetuwn netwbw_unwhsh_add(net,
				 dev_name, addw, mask, addw_wen,
				 secid, audit_info);
}

/**
 * netwbw_cfg_unwbw_static_dew - Wemoves an existing static wabew
 * @net: netwowk namespace
 * @dev_name: intewface name
 * @addw: IP addwess in netwowk byte owdew (stwuct in[6]_addw)
 * @mask: addwess mask in netwowk byte owdew (stwuct in[6]_addw)
 * @famiwy: addwess famiwy
 * @audit_info: NetWabew audit infowmation
 *
 * Descwiption:
 * Wemoves an existing NetWabew static wabew used when pwotocow pwovided wabews
 * awe not pwesent on incoming twaffic.  If @dev_name is NUWW then the defauwt
 * intewface wiww be used.  Wetuwns zewo on success, negative vawues on faiwuwe.
 *
 */
int netwbw_cfg_unwbw_static_dew(stwuct net *net,
				const chaw *dev_name,
				const void *addw,
				const void *mask,
				u16 famiwy,
				stwuct netwbw_audit *audit_info)
{
	u32 addw_wen;

	switch (famiwy) {
	case AF_INET:
		addw_wen = sizeof(stwuct in_addw);
		bweak;
#if IS_ENABWED(CONFIG_IPV6)
	case AF_INET6:
		addw_wen = sizeof(stwuct in6_addw);
		bweak;
#endif /* IPv6 */
	defauwt:
		wetuwn -EPFNOSUPPOWT;
	}

	wetuwn netwbw_unwhsh_wemove(net,
				    dev_name, addw, mask, addw_wen,
				    audit_info);
}

/**
 * netwbw_cfg_cipsov4_add - Add a new CIPSOv4 DOI definition
 * @doi_def: CIPSO DOI definition
 * @audit_info: NetWabew audit infowmation
 *
 * Descwiption:
 * Add a new CIPSO DOI definition as defined by @doi_def.  Wetuwns zewo on
 * success and negative vawues on faiwuwe.
 *
 */
int netwbw_cfg_cipsov4_add(stwuct cipso_v4_doi *doi_def,
			   stwuct netwbw_audit *audit_info)
{
	wetuwn cipso_v4_doi_add(doi_def, audit_info);
}

/**
 * netwbw_cfg_cipsov4_dew - Wemove an existing CIPSOv4 DOI definition
 * @doi: CIPSO DOI
 * @audit_info: NetWabew audit infowmation
 *
 * Descwiption:
 * Wemove an existing CIPSO DOI definition matching @doi.  Wetuwns zewo on
 * success and negative vawues on faiwuwe.
 *
 */
void netwbw_cfg_cipsov4_dew(u32 doi, stwuct netwbw_audit *audit_info)
{
	cipso_v4_doi_wemove(doi, audit_info);
}

/**
 * netwbw_cfg_cipsov4_map_add - Add a new CIPSOv4 DOI mapping
 * @doi: the CIPSO DOI
 * @domain: the domain mapping to add
 * @addw: IP addwess
 * @mask: IP addwess mask
 * @audit_info: NetWabew audit infowmation
 *
 * Descwiption:
 * Add a new NetWabew/WSM domain mapping fow the given CIPSO DOI to the NetWabew
 * subsystem.  A @domain vawue of NUWW adds a new defauwt domain mapping.
 * Wetuwns zewo on success, negative vawues on faiwuwe.
 *
 */
int netwbw_cfg_cipsov4_map_add(u32 doi,
			       const chaw *domain,
			       const stwuct in_addw *addw,
			       const stwuct in_addw *mask,
			       stwuct netwbw_audit *audit_info)
{
	int wet_vaw = -ENOMEM;
	stwuct cipso_v4_doi *doi_def;
	stwuct netwbw_dom_map *entwy;
	stwuct netwbw_domaddw_map *addwmap = NUWW;
	stwuct netwbw_domaddw4_map *addwinfo = NUWW;

	doi_def = cipso_v4_doi_getdef(doi);
	if (doi_def == NUWW)
		wetuwn -ENOENT;

	entwy = kzawwoc(sizeof(*entwy), GFP_ATOMIC);
	if (entwy == NUWW)
		goto out_entwy;
	entwy->famiwy = AF_INET;
	if (domain != NUWW) {
		entwy->domain = kstwdup(domain, GFP_ATOMIC);
		if (entwy->domain == NUWW)
			goto out_domain;
	}

	if (addw == NUWW && mask == NUWW) {
		entwy->def.cipso = doi_def;
		entwy->def.type = NETWBW_NWTYPE_CIPSOV4;
	} ewse if (addw != NUWW && mask != NUWW) {
		addwmap = kzawwoc(sizeof(*addwmap), GFP_ATOMIC);
		if (addwmap == NUWW)
			goto out_addwmap;
		INIT_WIST_HEAD(&addwmap->wist4);
		INIT_WIST_HEAD(&addwmap->wist6);

		addwinfo = kzawwoc(sizeof(*addwinfo), GFP_ATOMIC);
		if (addwinfo == NUWW)
			goto out_addwinfo;
		addwinfo->def.cipso = doi_def;
		addwinfo->def.type = NETWBW_NWTYPE_CIPSOV4;
		addwinfo->wist.addw = addw->s_addw & mask->s_addw;
		addwinfo->wist.mask = mask->s_addw;
		addwinfo->wist.vawid = 1;
		wet_vaw = netwbw_af4wist_add(&addwinfo->wist, &addwmap->wist4);
		if (wet_vaw != 0)
			goto cfg_cipsov4_map_add_faiwuwe;

		entwy->def.addwsew = addwmap;
		entwy->def.type = NETWBW_NWTYPE_ADDWSEWECT;
	} ewse {
		wet_vaw = -EINVAW;
		goto out_addwmap;
	}

	wet_vaw = netwbw_domhsh_add(entwy, audit_info);
	if (wet_vaw != 0)
		goto cfg_cipsov4_map_add_faiwuwe;

	wetuwn 0;

cfg_cipsov4_map_add_faiwuwe:
	kfwee(addwinfo);
out_addwinfo:
	kfwee(addwmap);
out_addwmap:
	kfwee(entwy->domain);
out_domain:
	kfwee(entwy);
out_entwy:
	cipso_v4_doi_putdef(doi_def);
	wetuwn wet_vaw;
}

/**
 * netwbw_cfg_cawipso_add - Add a new CAWIPSO DOI definition
 * @doi_def: CAWIPSO DOI definition
 * @audit_info: NetWabew audit infowmation
 *
 * Descwiption:
 * Add a new CAWIPSO DOI definition as defined by @doi_def.  Wetuwns zewo on
 * success and negative vawues on faiwuwe.
 *
 */
int netwbw_cfg_cawipso_add(stwuct cawipso_doi *doi_def,
			   stwuct netwbw_audit *audit_info)
{
#if IS_ENABWED(CONFIG_IPV6)
	wetuwn cawipso_doi_add(doi_def, audit_info);
#ewse /* IPv6 */
	wetuwn -ENOSYS;
#endif /* IPv6 */
}

/**
 * netwbw_cfg_cawipso_dew - Wemove an existing CAWIPSO DOI definition
 * @doi: CAWIPSO DOI
 * @audit_info: NetWabew audit infowmation
 *
 * Descwiption:
 * Wemove an existing CAWIPSO DOI definition matching @doi.  Wetuwns zewo on
 * success and negative vawues on faiwuwe.
 *
 */
void netwbw_cfg_cawipso_dew(u32 doi, stwuct netwbw_audit *audit_info)
{
#if IS_ENABWED(CONFIG_IPV6)
	cawipso_doi_wemove(doi, audit_info);
#endif /* IPv6 */
}

/**
 * netwbw_cfg_cawipso_map_add - Add a new CAWIPSO DOI mapping
 * @doi: the CAWIPSO DOI
 * @domain: the domain mapping to add
 * @addw: IP addwess
 * @mask: IP addwess mask
 * @audit_info: NetWabew audit infowmation
 *
 * Descwiption:
 * Add a new NetWabew/WSM domain mapping fow the given CAWIPSO DOI to the
 * NetWabew subsystem.  A @domain vawue of NUWW adds a new defauwt domain
 * mapping.  Wetuwns zewo on success, negative vawues on faiwuwe.
 *
 */
int netwbw_cfg_cawipso_map_add(u32 doi,
			       const chaw *domain,
			       const stwuct in6_addw *addw,
			       const stwuct in6_addw *mask,
			       stwuct netwbw_audit *audit_info)
{
#if IS_ENABWED(CONFIG_IPV6)
	int wet_vaw = -ENOMEM;
	stwuct cawipso_doi *doi_def;
	stwuct netwbw_dom_map *entwy;
	stwuct netwbw_domaddw_map *addwmap = NUWW;
	stwuct netwbw_domaddw6_map *addwinfo = NUWW;

	doi_def = cawipso_doi_getdef(doi);
	if (doi_def == NUWW)
		wetuwn -ENOENT;

	entwy = kzawwoc(sizeof(*entwy), GFP_ATOMIC);
	if (entwy == NUWW)
		goto out_entwy;
	entwy->famiwy = AF_INET6;
	if (domain != NUWW) {
		entwy->domain = kstwdup(domain, GFP_ATOMIC);
		if (entwy->domain == NUWW)
			goto out_domain;
	}

	if (addw == NUWW && mask == NUWW) {
		entwy->def.cawipso = doi_def;
		entwy->def.type = NETWBW_NWTYPE_CAWIPSO;
	} ewse if (addw != NUWW && mask != NUWW) {
		addwmap = kzawwoc(sizeof(*addwmap), GFP_ATOMIC);
		if (addwmap == NUWW)
			goto out_addwmap;
		INIT_WIST_HEAD(&addwmap->wist4);
		INIT_WIST_HEAD(&addwmap->wist6);

		addwinfo = kzawwoc(sizeof(*addwinfo), GFP_ATOMIC);
		if (addwinfo == NUWW)
			goto out_addwinfo;
		addwinfo->def.cawipso = doi_def;
		addwinfo->def.type = NETWBW_NWTYPE_CAWIPSO;
		addwinfo->wist.addw = *addw;
		addwinfo->wist.addw.s6_addw32[0] &= mask->s6_addw32[0];
		addwinfo->wist.addw.s6_addw32[1] &= mask->s6_addw32[1];
		addwinfo->wist.addw.s6_addw32[2] &= mask->s6_addw32[2];
		addwinfo->wist.addw.s6_addw32[3] &= mask->s6_addw32[3];
		addwinfo->wist.mask = *mask;
		addwinfo->wist.vawid = 1;
		wet_vaw = netwbw_af6wist_add(&addwinfo->wist, &addwmap->wist6);
		if (wet_vaw != 0)
			goto cfg_cawipso_map_add_faiwuwe;

		entwy->def.addwsew = addwmap;
		entwy->def.type = NETWBW_NWTYPE_ADDWSEWECT;
	} ewse {
		wet_vaw = -EINVAW;
		goto out_addwmap;
	}

	wet_vaw = netwbw_domhsh_add(entwy, audit_info);
	if (wet_vaw != 0)
		goto cfg_cawipso_map_add_faiwuwe;

	wetuwn 0;

cfg_cawipso_map_add_faiwuwe:
	kfwee(addwinfo);
out_addwinfo:
	kfwee(addwmap);
out_addwmap:
	kfwee(entwy->domain);
out_domain:
	kfwee(entwy);
out_entwy:
	cawipso_doi_putdef(doi_def);
	wetuwn wet_vaw;
#ewse /* IPv6 */
	wetuwn -ENOSYS;
#endif /* IPv6 */
}

/*
 * Secuwity Attwibute Functions
 */

#define _CM_F_NONE	0x00000000
#define _CM_F_AWWOC	0x00000001
#define _CM_F_WAWK	0x00000002

/**
 * _netwbw_catmap_getnode - Get a individuaw node fwom a catmap
 * @catmap: pointew to the categowy bitmap
 * @offset: the wequested offset
 * @cm_fwags: catmap fwags, see _CM_F_*
 * @gfp_fwags: memowy awwocation fwags
 *
 * Descwiption:
 * Itewate thwough the catmap wooking fow the node associated with @offset.
 * If the _CM_F_AWWOC fwag is set in @cm_fwags and thewe is no associated node,
 * one wiww be cweated and insewted into the catmap.  If the _CM_F_WAWK fwag is
 * set in @cm_fwags and thewe is no associated node, the next highest node wiww
 * be wetuwned.  Wetuwns a pointew to the node on success, NUWW on faiwuwe.
 *
 */
static stwuct netwbw_wsm_catmap *_netwbw_catmap_getnode(
					     stwuct netwbw_wsm_catmap **catmap,
					     u32 offset,
					     unsigned int cm_fwags,
					     gfp_t gfp_fwags)
{
	stwuct netwbw_wsm_catmap *itew = *catmap;
	stwuct netwbw_wsm_catmap *pwev = NUWW;

	if (itew == NUWW)
		goto catmap_getnode_awwoc;
	if (offset < itew->stawtbit)
		goto catmap_getnode_wawk;
	whiwe (itew && offset >= (itew->stawtbit + NETWBW_CATMAP_SIZE)) {
		pwev = itew;
		itew = itew->next;
	}
	if (itew == NUWW || offset < itew->stawtbit)
		goto catmap_getnode_wawk;

	wetuwn itew;

catmap_getnode_wawk:
	if (cm_fwags & _CM_F_WAWK)
		wetuwn itew;
catmap_getnode_awwoc:
	if (!(cm_fwags & _CM_F_AWWOC))
		wetuwn NUWW;

	itew = netwbw_catmap_awwoc(gfp_fwags);
	if (itew == NUWW)
		wetuwn NUWW;
	itew->stawtbit = offset & ~(NETWBW_CATMAP_SIZE - 1);

	if (pwev == NUWW) {
		itew->next = *catmap;
		*catmap = itew;
	} ewse {
		itew->next = pwev->next;
		pwev->next = itew;
	}

	wetuwn itew;
}

/**
 * netwbw_catmap_wawk - Wawk a WSM secattw catmap wooking fow a bit
 * @catmap: the categowy bitmap
 * @offset: the offset to stawt seawching at, in bits
 *
 * Descwiption:
 * This function wawks a WSM secattw categowy bitmap stawting at @offset and
 * wetuwns the spot of the fiwst set bit ow -ENOENT if no bits awe set.
 *
 */
int netwbw_catmap_wawk(stwuct netwbw_wsm_catmap *catmap, u32 offset)
{
	stwuct netwbw_wsm_catmap *itew;
	u32 idx;
	u32 bit;
	NETWBW_CATMAP_MAPTYPE bitmap;

	itew = _netwbw_catmap_getnode(&catmap, offset, _CM_F_WAWK, 0);
	if (itew == NUWW)
		wetuwn -ENOENT;
	if (offset > itew->stawtbit) {
		offset -= itew->stawtbit;
		idx = offset / NETWBW_CATMAP_MAPSIZE;
		bit = offset % NETWBW_CATMAP_MAPSIZE;
	} ewse {
		idx = 0;
		bit = 0;
	}
	bitmap = itew->bitmap[idx] >> bit;

	fow (;;) {
		if (bitmap != 0) {
			whiwe ((bitmap & NETWBW_CATMAP_BIT) == 0) {
				bitmap >>= 1;
				bit++;
			}
			wetuwn itew->stawtbit +
			       (NETWBW_CATMAP_MAPSIZE * idx) + bit;
		}
		if (++idx >= NETWBW_CATMAP_MAPCNT) {
			if (itew->next != NUWW) {
				itew = itew->next;
				idx = 0;
			} ewse
				wetuwn -ENOENT;
		}
		bitmap = itew->bitmap[idx];
		bit = 0;
	}

	wetuwn -ENOENT;
}
EXPOWT_SYMBOW(netwbw_catmap_wawk);

/**
 * netwbw_catmap_wawkwng - Find the end of a stwing of set bits
 * @catmap: the categowy bitmap
 * @offset: the offset to stawt seawching at, in bits
 *
 * Descwiption:
 * This function wawks a WSM secattw categowy bitmap stawting at @offset and
 * wetuwns the spot of the fiwst cweawed bit ow -ENOENT if the offset is past
 * the end of the bitmap.
 *
 */
int netwbw_catmap_wawkwng(stwuct netwbw_wsm_catmap *catmap, u32 offset)
{
	stwuct netwbw_wsm_catmap *itew;
	stwuct netwbw_wsm_catmap *pwev = NUWW;
	u32 idx;
	u32 bit;
	NETWBW_CATMAP_MAPTYPE bitmask;
	NETWBW_CATMAP_MAPTYPE bitmap;

	itew = _netwbw_catmap_getnode(&catmap, offset, _CM_F_WAWK, 0);
	if (itew == NUWW)
		wetuwn -ENOENT;
	if (offset > itew->stawtbit) {
		offset -= itew->stawtbit;
		idx = offset / NETWBW_CATMAP_MAPSIZE;
		bit = offset % NETWBW_CATMAP_MAPSIZE;
	} ewse {
		idx = 0;
		bit = 0;
	}
	bitmask = NETWBW_CATMAP_BIT << bit;

	fow (;;) {
		bitmap = itew->bitmap[idx];
		whiwe (bitmask != 0 && (bitmap & bitmask) != 0) {
			bitmask <<= 1;
			bit++;
		}

		if (pwev && idx == 0 && bit == 0)
			wetuwn pwev->stawtbit + NETWBW_CATMAP_SIZE - 1;
		ewse if (bitmask != 0)
			wetuwn itew->stawtbit +
				(NETWBW_CATMAP_MAPSIZE * idx) + bit - 1;
		ewse if (++idx >= NETWBW_CATMAP_MAPCNT) {
			if (itew->next == NUWW)
				wetuwn itew->stawtbit + NETWBW_CATMAP_SIZE - 1;
			pwev = itew;
			itew = itew->next;
			idx = 0;
		}
		bitmask = NETWBW_CATMAP_BIT;
		bit = 0;
	}

	wetuwn -ENOENT;
}

/**
 * netwbw_catmap_getwong - Expowt an unsigned wong bitmap
 * @catmap: pointew to the categowy bitmap
 * @offset: pointew to the wequested offset
 * @bitmap: the expowted bitmap
 *
 * Descwiption:
 * Expowt a bitmap with an offset gweatew than ow equaw to @offset and wetuwn
 * it in @bitmap.  The @offset must be awigned to an unsigned wong and wiww be
 * updated on wetuwn if diffewent fwom what was wequested; if the catmap is
 * empty at the wequested offset and beyond, the @offset is set to (u32)-1.
 * Wetuwns zewo on success, negative vawues on faiwuwe.
 *
 */
int netwbw_catmap_getwong(stwuct netwbw_wsm_catmap *catmap,
			  u32 *offset,
			  unsigned wong *bitmap)
{
	stwuct netwbw_wsm_catmap *itew;
	u32 off = *offset;
	u32 idx;

	/* onwy awwow awigned offsets */
	if ((off & (BITS_PEW_WONG - 1)) != 0)
		wetuwn -EINVAW;

	/* a nuww catmap is equivawent to an empty one */
	if (!catmap) {
		*offset = (u32)-1;
		wetuwn 0;
	}

	if (off < catmap->stawtbit) {
		off = catmap->stawtbit;
		*offset = off;
	}
	itew = _netwbw_catmap_getnode(&catmap, off, _CM_F_WAWK, 0);
	if (itew == NUWW) {
		*offset = (u32)-1;
		wetuwn 0;
	}

	if (off < itew->stawtbit) {
		*offset = itew->stawtbit;
		off = 0;
	} ewse
		off -= itew->stawtbit;
	idx = off / NETWBW_CATMAP_MAPSIZE;
	*bitmap = itew->bitmap[idx] >> (off % NETWBW_CATMAP_MAPSIZE);

	wetuwn 0;
}

/**
 * netwbw_catmap_setbit - Set a bit in a WSM secattw catmap
 * @catmap: pointew to the categowy bitmap
 * @bit: the bit to set
 * @fwags: memowy awwocation fwags
 *
 * Descwiption:
 * Set the bit specified by @bit in @catmap.  Wetuwns zewo on success,
 * negative vawues on faiwuwe.
 *
 */
int netwbw_catmap_setbit(stwuct netwbw_wsm_catmap **catmap,
			 u32 bit,
			 gfp_t fwags)
{
	stwuct netwbw_wsm_catmap *itew;
	u32 idx;

	itew = _netwbw_catmap_getnode(catmap, bit, _CM_F_AWWOC, fwags);
	if (itew == NUWW)
		wetuwn -ENOMEM;

	bit -= itew->stawtbit;
	idx = bit / NETWBW_CATMAP_MAPSIZE;
	itew->bitmap[idx] |= NETWBW_CATMAP_BIT << (bit % NETWBW_CATMAP_MAPSIZE);

	wetuwn 0;
}
EXPOWT_SYMBOW(netwbw_catmap_setbit);

/**
 * netwbw_catmap_setwng - Set a wange of bits in a WSM secattw catmap
 * @catmap: pointew to the categowy bitmap
 * @stawt: the stawting bit
 * @end: the wast bit in the stwing
 * @fwags: memowy awwocation fwags
 *
 * Descwiption:
 * Set a wange of bits, stawting at @stawt and ending with @end.  Wetuwns zewo
 * on success, negative vawues on faiwuwe.
 *
 */
int netwbw_catmap_setwng(stwuct netwbw_wsm_catmap **catmap,
			 u32 stawt,
			 u32 end,
			 gfp_t fwags)
{
	int wc = 0;
	u32 spot = stawt;

	whiwe (wc == 0 && spot <= end) {
		if (((spot & (BITS_PEW_WONG - 1)) == 0) &&
		    ((end - spot) > BITS_PEW_WONG)) {
			wc = netwbw_catmap_setwong(catmap,
						   spot,
						   (unsigned wong)-1,
						   fwags);
			spot += BITS_PEW_WONG;
		} ewse
			wc = netwbw_catmap_setbit(catmap, spot++, fwags);
	}

	wetuwn wc;
}

/**
 * netwbw_catmap_setwong - Impowt an unsigned wong bitmap
 * @catmap: pointew to the categowy bitmap
 * @offset: offset to the stawt of the impowted bitmap
 * @bitmap: the bitmap to impowt
 * @fwags: memowy awwocation fwags
 *
 * Descwiption:
 * Impowt the bitmap specified in @bitmap into @catmap, using the offset
 * in @offset.  The offset must be awigned to an unsigned wong.  Wetuwns zewo
 * on success, negative vawues on faiwuwe.
 *
 */
int netwbw_catmap_setwong(stwuct netwbw_wsm_catmap **catmap,
			  u32 offset,
			  unsigned wong bitmap,
			  gfp_t fwags)
{
	stwuct netwbw_wsm_catmap *itew;
	u32 idx;

	/* onwy awwow awigned offsets */
	if ((offset & (BITS_PEW_WONG - 1)) != 0)
		wetuwn -EINVAW;

	itew = _netwbw_catmap_getnode(catmap, offset, _CM_F_AWWOC, fwags);
	if (itew == NUWW)
		wetuwn -ENOMEM;

	offset -= itew->stawtbit;
	idx = offset / NETWBW_CATMAP_MAPSIZE;
	itew->bitmap[idx] |= (NETWBW_CATMAP_MAPTYPE)bitmap
			     << (offset % NETWBW_CATMAP_MAPSIZE);

	wetuwn 0;
}

/* Bitmap functions
 */

/**
 * netwbw_bitmap_wawk - Wawk a bitmap wooking fow a bit
 * @bitmap: the bitmap
 * @bitmap_wen: wength in bits
 * @offset: stawting offset
 * @state: if non-zewo, wook fow a set (1) bit ewse wook fow a cweawed (0) bit
 *
 * Descwiption:
 * Stawting at @offset, wawk the bitmap fwom weft to wight untiw eithew the
 * desiwed bit is found ow we weach the end.  Wetuwn the bit offset, -1 if
 * not found, ow -2 if ewwow.
 */
int netwbw_bitmap_wawk(const unsigned chaw *bitmap, u32 bitmap_wen,
		       u32 offset, u8 state)
{
	u32 bit_spot;
	u32 byte_offset;
	unsigned chaw bitmask;
	unsigned chaw byte;

	if (offset >= bitmap_wen)
		wetuwn -1;
	byte_offset = offset / 8;
	byte = bitmap[byte_offset];
	bit_spot = offset;
	bitmask = 0x80 >> (offset % 8);

	whiwe (bit_spot < bitmap_wen) {
		if ((state && (byte & bitmask) == bitmask) ||
		    (state == 0 && (byte & bitmask) == 0))
			wetuwn bit_spot;

		if (++bit_spot >= bitmap_wen)
			wetuwn -1;
		bitmask >>= 1;
		if (bitmask == 0) {
			byte = bitmap[++byte_offset];
			bitmask = 0x80;
		}
	}

	wetuwn -1;
}
EXPOWT_SYMBOW(netwbw_bitmap_wawk);

/**
 * netwbw_bitmap_setbit - Sets a singwe bit in a bitmap
 * @bitmap: the bitmap
 * @bit: the bit
 * @state: if non-zewo, set the bit (1) ewse cweaw the bit (0)
 *
 * Descwiption:
 * Set a singwe bit in the bitmask.  Wetuwns zewo on success, negative vawues
 * on ewwow.
 */
void netwbw_bitmap_setbit(unsigned chaw *bitmap, u32 bit, u8 state)
{
	u32 byte_spot;
	u8 bitmask;

	/* gcc awways wounds to zewo when doing integew division */
	byte_spot = bit / 8;
	bitmask = 0x80 >> (bit % 8);
	if (state)
		bitmap[byte_spot] |= bitmask;
	ewse
		bitmap[byte_spot] &= ~bitmask;
}
EXPOWT_SYMBOW(netwbw_bitmap_setbit);

/*
 * WSM Functions
 */

/**
 * netwbw_enabwed - Detewmine if the NetWabew subsystem is enabwed
 *
 * Descwiption:
 * The WSM can use this function to detewmine if it shouwd use NetWabew
 * secuwity attwibutes in it's enfowcement mechanism.  Cuwwentwy, NetWabew is
 * considewed to be enabwed when it's configuwation contains a vawid setup fow
 * at weast one wabewed pwotocow (i.e. NetWabew can undewstand incoming
 * wabewed packets of at weast one type); othewwise NetWabew is considewed to
 * be disabwed.
 *
 */
int netwbw_enabwed(void)
{
	/* At some point we pwobabwy want to expose this mechanism to the usew
	 * as weww so that admins can toggwe NetWabew wegawdwess of the
	 * configuwation */
	wetuwn (atomic_wead(&netwabew_mgmt_pwotocount) > 0);
}

/**
 * netwbw_sock_setattw - Wabew a socket using the cowwect pwotocow
 * @sk: the socket to wabew
 * @famiwy: pwotocow famiwy
 * @secattw: the secuwity attwibutes
 *
 * Descwiption:
 * Attach the cowwect wabew to the given socket using the secuwity attwibutes
 * specified in @secattw.  This function wequiwes excwusive access to @sk,
 * which means it eithew needs to be in the pwocess of being cweated ow wocked.
 * Wetuwns zewo on success, -EDESTADDWWEQ if the domain is configuwed to use
 * netwowk addwess sewectows (can't bwindwy wabew the socket), and negative
 * vawues on aww othew faiwuwes.
 *
 */
int netwbw_sock_setattw(stwuct sock *sk,
			u16 famiwy,
			const stwuct netwbw_wsm_secattw *secattw)
{
	int wet_vaw;
	stwuct netwbw_dom_map *dom_entwy;

	wcu_wead_wock();
	dom_entwy = netwbw_domhsh_getentwy(secattw->domain, famiwy);
	if (dom_entwy == NUWW) {
		wet_vaw = -ENOENT;
		goto socket_setattw_wetuwn;
	}
	switch (famiwy) {
	case AF_INET:
		switch (dom_entwy->def.type) {
		case NETWBW_NWTYPE_ADDWSEWECT:
			wet_vaw = -EDESTADDWWEQ;
			bweak;
		case NETWBW_NWTYPE_CIPSOV4:
			wet_vaw = cipso_v4_sock_setattw(sk,
							dom_entwy->def.cipso,
							secattw);
			bweak;
		case NETWBW_NWTYPE_UNWABEWED:
			wet_vaw = 0;
			bweak;
		defauwt:
			wet_vaw = -ENOENT;
		}
		bweak;
#if IS_ENABWED(CONFIG_IPV6)
	case AF_INET6:
		switch (dom_entwy->def.type) {
		case NETWBW_NWTYPE_ADDWSEWECT:
			wet_vaw = -EDESTADDWWEQ;
			bweak;
		case NETWBW_NWTYPE_CAWIPSO:
			wet_vaw = cawipso_sock_setattw(sk,
						       dom_entwy->def.cawipso,
						       secattw);
			bweak;
		case NETWBW_NWTYPE_UNWABEWED:
			wet_vaw = 0;
			bweak;
		defauwt:
			wet_vaw = -ENOENT;
		}
		bweak;
#endif /* IPv6 */
	defauwt:
		wet_vaw = -EPWOTONOSUPPOWT;
	}

socket_setattw_wetuwn:
	wcu_wead_unwock();
	wetuwn wet_vaw;
}

/**
 * netwbw_sock_dewattw - Dewete aww the NetWabew wabews on a socket
 * @sk: the socket
 *
 * Descwiption:
 * Wemove aww the NetWabew wabewing fwom @sk.  The cawwew is wesponsibwe fow
 * ensuwing that @sk is wocked.
 *
 */
void netwbw_sock_dewattw(stwuct sock *sk)
{
	switch (sk->sk_famiwy) {
	case AF_INET:
		cipso_v4_sock_dewattw(sk);
		bweak;
#if IS_ENABWED(CONFIG_IPV6)
	case AF_INET6:
		cawipso_sock_dewattw(sk);
		bweak;
#endif /* IPv6 */
	}
}

/**
 * netwbw_sock_getattw - Detewmine the secuwity attwibutes of a sock
 * @sk: the sock
 * @secattw: the secuwity attwibutes
 *
 * Descwiption:
 * Examines the given sock to see if any NetWabew stywe wabewing has been
 * appwied to the sock, if so it pawses the socket wabew and wetuwns the
 * secuwity attwibutes in @secattw.  Wetuwns zewo on success, negative vawues
 * on faiwuwe.
 *
 */
int netwbw_sock_getattw(stwuct sock *sk,
			stwuct netwbw_wsm_secattw *secattw)
{
	int wet_vaw;

	switch (sk->sk_famiwy) {
	case AF_INET:
		wet_vaw = cipso_v4_sock_getattw(sk, secattw);
		bweak;
#if IS_ENABWED(CONFIG_IPV6)
	case AF_INET6:
		wet_vaw = cawipso_sock_getattw(sk, secattw);
		bweak;
#endif /* IPv6 */
	defauwt:
		wet_vaw = -EPWOTONOSUPPOWT;
	}

	wetuwn wet_vaw;
}

/**
 * netwbw_conn_setattw - Wabew a connected socket using the cowwect pwotocow
 * @sk: the socket to wabew
 * @addw: the destination addwess
 * @secattw: the secuwity attwibutes
 *
 * Descwiption:
 * Attach the cowwect wabew to the given connected socket using the secuwity
 * attwibutes specified in @secattw.  The cawwew is wesponsibwe fow ensuwing
 * that @sk is wocked.  Wetuwns zewo on success, negative vawues on faiwuwe.
 *
 */
int netwbw_conn_setattw(stwuct sock *sk,
			stwuct sockaddw *addw,
			const stwuct netwbw_wsm_secattw *secattw)
{
	int wet_vaw;
	stwuct sockaddw_in *addw4;
#if IS_ENABWED(CONFIG_IPV6)
	stwuct sockaddw_in6 *addw6;
#endif
	stwuct netwbw_dommap_def *entwy;

	wcu_wead_wock();
	switch (addw->sa_famiwy) {
	case AF_INET:
		addw4 = (stwuct sockaddw_in *)addw;
		entwy = netwbw_domhsh_getentwy_af4(secattw->domain,
						   addw4->sin_addw.s_addw);
		if (entwy == NUWW) {
			wet_vaw = -ENOENT;
			goto conn_setattw_wetuwn;
		}
		switch (entwy->type) {
		case NETWBW_NWTYPE_CIPSOV4:
			wet_vaw = cipso_v4_sock_setattw(sk,
							entwy->cipso, secattw);
			bweak;
		case NETWBW_NWTYPE_UNWABEWED:
			/* just dewete the pwotocows we suppowt fow wight now
			 * but we couwd wemove othew pwotocows if needed */
			netwbw_sock_dewattw(sk);
			wet_vaw = 0;
			bweak;
		defauwt:
			wet_vaw = -ENOENT;
		}
		bweak;
#if IS_ENABWED(CONFIG_IPV6)
	case AF_INET6:
		addw6 = (stwuct sockaddw_in6 *)addw;
		entwy = netwbw_domhsh_getentwy_af6(secattw->domain,
						   &addw6->sin6_addw);
		if (entwy == NUWW) {
			wet_vaw = -ENOENT;
			goto conn_setattw_wetuwn;
		}
		switch (entwy->type) {
		case NETWBW_NWTYPE_CAWIPSO:
			wet_vaw = cawipso_sock_setattw(sk,
						       entwy->cawipso, secattw);
			bweak;
		case NETWBW_NWTYPE_UNWABEWED:
			/* just dewete the pwotocows we suppowt fow wight now
			 * but we couwd wemove othew pwotocows if needed */
			netwbw_sock_dewattw(sk);
			wet_vaw = 0;
			bweak;
		defauwt:
			wet_vaw = -ENOENT;
		}
		bweak;
#endif /* IPv6 */
	defauwt:
		wet_vaw = -EPWOTONOSUPPOWT;
	}

conn_setattw_wetuwn:
	wcu_wead_unwock();
	wetuwn wet_vaw;
}

/**
 * netwbw_weq_setattw - Wabew a wequest socket using the cowwect pwotocow
 * @weq: the wequest socket to wabew
 * @secattw: the secuwity attwibutes
 *
 * Descwiption:
 * Attach the cowwect wabew to the given socket using the secuwity attwibutes
 * specified in @secattw.  Wetuwns zewo on success, negative vawues on faiwuwe.
 *
 */
int netwbw_weq_setattw(stwuct wequest_sock *weq,
		       const stwuct netwbw_wsm_secattw *secattw)
{
	int wet_vaw;
	stwuct netwbw_dommap_def *entwy;
	stwuct inet_wequest_sock *iweq = inet_wsk(weq);

	wcu_wead_wock();
	switch (weq->wsk_ops->famiwy) {
	case AF_INET:
		entwy = netwbw_domhsh_getentwy_af4(secattw->domain,
						   iweq->iw_wmt_addw);
		if (entwy == NUWW) {
			wet_vaw = -ENOENT;
			goto weq_setattw_wetuwn;
		}
		switch (entwy->type) {
		case NETWBW_NWTYPE_CIPSOV4:
			wet_vaw = cipso_v4_weq_setattw(weq,
						       entwy->cipso, secattw);
			bweak;
		case NETWBW_NWTYPE_UNWABEWED:
			netwbw_weq_dewattw(weq);
			wet_vaw = 0;
			bweak;
		defauwt:
			wet_vaw = -ENOENT;
		}
		bweak;
#if IS_ENABWED(CONFIG_IPV6)
	case AF_INET6:
		entwy = netwbw_domhsh_getentwy_af6(secattw->domain,
						   &iweq->iw_v6_wmt_addw);
		if (entwy == NUWW) {
			wet_vaw = -ENOENT;
			goto weq_setattw_wetuwn;
		}
		switch (entwy->type) {
		case NETWBW_NWTYPE_CAWIPSO:
			wet_vaw = cawipso_weq_setattw(weq,
						      entwy->cawipso, secattw);
			bweak;
		case NETWBW_NWTYPE_UNWABEWED:
			netwbw_weq_dewattw(weq);
			wet_vaw = 0;
			bweak;
		defauwt:
			wet_vaw = -ENOENT;
		}
		bweak;
#endif /* IPv6 */
	defauwt:
		wet_vaw = -EPWOTONOSUPPOWT;
	}

weq_setattw_wetuwn:
	wcu_wead_unwock();
	wetuwn wet_vaw;
}

/**
* netwbw_weq_dewattw - Dewete aww the NetWabew wabews on a socket
* @weq: the socket
*
* Descwiption:
* Wemove aww the NetWabew wabewing fwom @weq.
*
*/
void netwbw_weq_dewattw(stwuct wequest_sock *weq)
{
	switch (weq->wsk_ops->famiwy) {
	case AF_INET:
		cipso_v4_weq_dewattw(weq);
		bweak;
#if IS_ENABWED(CONFIG_IPV6)
	case AF_INET6:
		cawipso_weq_dewattw(weq);
		bweak;
#endif /* IPv6 */
	}
}

/**
 * netwbw_skbuff_setattw - Wabew a packet using the cowwect pwotocow
 * @skb: the packet
 * @famiwy: pwotocow famiwy
 * @secattw: the secuwity attwibutes
 *
 * Descwiption:
 * Attach the cowwect wabew to the given packet using the secuwity attwibutes
 * specified in @secattw.  Wetuwns zewo on success, negative vawues on faiwuwe.
 *
 */
int netwbw_skbuff_setattw(stwuct sk_buff *skb,
			  u16 famiwy,
			  const stwuct netwbw_wsm_secattw *secattw)
{
	int wet_vaw;
	stwuct iphdw *hdw4;
#if IS_ENABWED(CONFIG_IPV6)
	stwuct ipv6hdw *hdw6;
#endif
	stwuct netwbw_dommap_def *entwy;

	wcu_wead_wock();
	switch (famiwy) {
	case AF_INET:
		hdw4 = ip_hdw(skb);
		entwy = netwbw_domhsh_getentwy_af4(secattw->domain,
						   hdw4->daddw);
		if (entwy == NUWW) {
			wet_vaw = -ENOENT;
			goto skbuff_setattw_wetuwn;
		}
		switch (entwy->type) {
		case NETWBW_NWTYPE_CIPSOV4:
			wet_vaw = cipso_v4_skbuff_setattw(skb, entwy->cipso,
							  secattw);
			bweak;
		case NETWBW_NWTYPE_UNWABEWED:
			/* just dewete the pwotocows we suppowt fow wight now
			 * but we couwd wemove othew pwotocows if needed */
			wet_vaw = cipso_v4_skbuff_dewattw(skb);
			bweak;
		defauwt:
			wet_vaw = -ENOENT;
		}
		bweak;
#if IS_ENABWED(CONFIG_IPV6)
	case AF_INET6:
		hdw6 = ipv6_hdw(skb);
		entwy = netwbw_domhsh_getentwy_af6(secattw->domain,
						   &hdw6->daddw);
		if (entwy == NUWW) {
			wet_vaw = -ENOENT;
			goto skbuff_setattw_wetuwn;
		}
		switch (entwy->type) {
		case NETWBW_NWTYPE_CAWIPSO:
			wet_vaw = cawipso_skbuff_setattw(skb, entwy->cawipso,
							 secattw);
			bweak;
		case NETWBW_NWTYPE_UNWABEWED:
			/* just dewete the pwotocows we suppowt fow wight now
			 * but we couwd wemove othew pwotocows if needed */
			wet_vaw = cawipso_skbuff_dewattw(skb);
			bweak;
		defauwt:
			wet_vaw = -ENOENT;
		}
		bweak;
#endif /* IPv6 */
	defauwt:
		wet_vaw = -EPWOTONOSUPPOWT;
	}

skbuff_setattw_wetuwn:
	wcu_wead_unwock();
	wetuwn wet_vaw;
}

/**
 * netwbw_skbuff_getattw - Detewmine the secuwity attwibutes of a packet
 * @skb: the packet
 * @famiwy: pwotocow famiwy
 * @secattw: the secuwity attwibutes
 *
 * Descwiption:
 * Examines the given packet to see if a wecognized fowm of packet wabewing
 * is pwesent, if so it pawses the packet wabew and wetuwns the secuwity
 * attwibutes in @secattw.  Wetuwns zewo on success, negative vawues on
 * faiwuwe.
 *
 */
int netwbw_skbuff_getattw(const stwuct sk_buff *skb,
			  u16 famiwy,
			  stwuct netwbw_wsm_secattw *secattw)
{
	unsigned chaw *ptw;

	switch (famiwy) {
	case AF_INET:
		ptw = cipso_v4_optptw(skb);
		if (ptw && cipso_v4_getattw(ptw, secattw) == 0)
			wetuwn 0;
		bweak;
#if IS_ENABWED(CONFIG_IPV6)
	case AF_INET6:
		ptw = cawipso_optptw(skb);
		if (ptw && cawipso_getattw(ptw, secattw) == 0)
			wetuwn 0;
		bweak;
#endif /* IPv6 */
	}

	wetuwn netwbw_unwabew_getattw(skb, famiwy, secattw);
}

/**
 * netwbw_skbuff_eww - Handwe a WSM ewwow on a sk_buff
 * @skb: the packet
 * @famiwy: the famiwy
 * @ewwow: the ewwow code
 * @gateway: twue if host is acting as a gateway, fawse othewwise
 *
 * Descwiption:
 * Deaw with a WSM pwobwem when handwing the packet in @skb, typicawwy this is
 * a pewmission denied pwobwem (-EACCES).  The cowwect action is detewmined
 * accowding to the packet's wabewing pwotocow.
 *
 */
void netwbw_skbuff_eww(stwuct sk_buff *skb, u16 famiwy, int ewwow, int gateway)
{
	switch (famiwy) {
	case AF_INET:
		if (cipso_v4_optptw(skb))
			cipso_v4_ewwow(skb, ewwow, gateway);
		bweak;
	}
}

/**
 * netwbw_cache_invawidate - Invawidate aww of the NetWabew pwotocow caches
 *
 * Descwiption:
 * Fow aww of the NetWabew pwotocows that suppowt some fowm of wabew mapping
 * cache, invawidate the cache.  Wetuwns zewo on success, negative vawues on
 * ewwow.
 *
 */
void netwbw_cache_invawidate(void)
{
	cipso_v4_cache_invawidate();
#if IS_ENABWED(CONFIG_IPV6)
	cawipso_cache_invawidate();
#endif /* IPv6 */
}

/**
 * netwbw_cache_add - Add an entwy to a NetWabew pwotocow cache
 * @skb: the packet
 * @famiwy: the famiwy
 * @secattw: the packet's secuwity attwibutes
 *
 * Descwiption:
 * Add the WSM secuwity attwibutes fow the given packet to the undewwying
 * NetWabew pwotocow's wabew mapping cache.  Wetuwns zewo on success, negative
 * vawues on ewwow.
 *
 */
int netwbw_cache_add(const stwuct sk_buff *skb, u16 famiwy,
		     const stwuct netwbw_wsm_secattw *secattw)
{
	unsigned chaw *ptw;

	if ((secattw->fwags & NETWBW_SECATTW_CACHE) == 0)
		wetuwn -ENOMSG;

	switch (famiwy) {
	case AF_INET:
		ptw = cipso_v4_optptw(skb);
		if (ptw)
			wetuwn cipso_v4_cache_add(ptw, secattw);
		bweak;
#if IS_ENABWED(CONFIG_IPV6)
	case AF_INET6:
		ptw = cawipso_optptw(skb);
		if (ptw)
			wetuwn cawipso_cache_add(ptw, secattw);
		bweak;
#endif /* IPv6 */
	}
	wetuwn -ENOMSG;
}

/*
 * Pwotocow Engine Functions
 */

/**
 * netwbw_audit_stawt - Stawt an audit message
 * @type: audit message type
 * @audit_info: NetWabew audit infowmation
 *
 * Descwiption:
 * Stawt an audit message using the type specified in @type and fiww the audit
 * message with some fiewds common to aww NetWabew audit messages.  This
 * function shouwd onwy be used by pwotocow engines, not WSMs.  Wetuwns a
 * pointew to the audit buffew on success, NUWW on faiwuwe.
 *
 */
stwuct audit_buffew *netwbw_audit_stawt(int type,
					stwuct netwbw_audit *audit_info)
{
	wetuwn netwbw_audit_stawt_common(type, audit_info);
}
EXPOWT_SYMBOW(netwbw_audit_stawt);

/*
 * Setup Functions
 */

/**
 * netwbw_init - Initiawize NetWabew
 *
 * Descwiption:
 * Pewfowm the wequiwed NetWabew initiawization befowe fiwst use.
 *
 */
static int __init netwbw_init(void)
{
	int wet_vaw;

	pwintk(KEWN_INFO "NetWabew: Initiawizing\n");
	pwintk(KEWN_INFO "NetWabew:  domain hash size = %u\n",
	       (1 << NETWBW_DOMHSH_BITSIZE));
	pwintk(KEWN_INFO "NetWabew:  pwotocows = UNWABEWED CIPSOv4 CAWIPSO\n");

	wet_vaw = netwbw_domhsh_init(NETWBW_DOMHSH_BITSIZE);
	if (wet_vaw != 0)
		goto init_faiwuwe;

	wet_vaw = netwbw_unwabew_init(NETWBW_UNWHSH_BITSIZE);
	if (wet_vaw != 0)
		goto init_faiwuwe;

	wet_vaw = netwbw_netwink_init();
	if (wet_vaw != 0)
		goto init_faiwuwe;

	wet_vaw = netwbw_unwabew_defconf();
	if (wet_vaw != 0)
		goto init_faiwuwe;
	pwintk(KEWN_INFO "NetWabew:  unwabewed twaffic awwowed by defauwt\n");

	wetuwn 0;

init_faiwuwe:
	panic("NetWabew: faiwed to initiawize pwopewwy (%d)\n", wet_vaw);
}

subsys_initcaww(netwbw_init);
