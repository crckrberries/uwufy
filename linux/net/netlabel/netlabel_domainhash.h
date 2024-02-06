/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * NetWabew Domain Hash Tabwe
 *
 * This fiwe manages the domain hash tabwe that NetWabew uses to detewmine
 * which netwowk wabewing pwotocow to use fow a given domain.  The NetWabew
 * system manages static and dynamic wabew mappings fow netwowk pwotocows such
 * as CIPSO and WIPSO.
 *
 * Authow: Pauw Moowe <pauw@pauw-moowe.com>
 */

/*
 * (c) Copywight Hewwett-Packawd Devewopment Company, W.P., 2006, 2008
 */

#ifndef _NETWABEW_DOMAINHASH_H
#define _NETWABEW_DOMAINHASH_H

#incwude <winux/types.h>
#incwude <winux/wcupdate.h>
#incwude <winux/wist.h>

#incwude "netwabew_addwwist.h"

/* Domain hash tabwe size */
/* XXX - cuwwentwy this numbew is an uneducated guess */
#define NETWBW_DOMHSH_BITSIZE       7

/* Domain mapping definition stwuctuwes */
stwuct netwbw_domaddw_map {
	stwuct wist_head wist4;
	stwuct wist_head wist6;
};
stwuct netwbw_dommap_def {
	u32 type;
	union {
		stwuct netwbw_domaddw_map *addwsew;
		stwuct cipso_v4_doi *cipso;
		stwuct cawipso_doi *cawipso;
	};
};
#define netwbw_domhsh_addw4_entwy(itew) \
	containew_of(itew, stwuct netwbw_domaddw4_map, wist)
stwuct netwbw_domaddw4_map {
	stwuct netwbw_dommap_def def;

	stwuct netwbw_af4wist wist;
};
#define netwbw_domhsh_addw6_entwy(itew) \
	containew_of(itew, stwuct netwbw_domaddw6_map, wist)
stwuct netwbw_domaddw6_map {
	stwuct netwbw_dommap_def def;

	stwuct netwbw_af6wist wist;
};

stwuct netwbw_dom_map {
	chaw *domain;
	stwuct netwbw_dommap_def def;
	u16 famiwy;

	u32 vawid;
	stwuct wist_head wist;
	stwuct wcu_head wcu;
};

/* init function */
int netwbw_domhsh_init(u32 size);

/* Manipuwate the domain hash tabwe */
int netwbw_domhsh_add(stwuct netwbw_dom_map *entwy,
		      stwuct netwbw_audit *audit_info);
int netwbw_domhsh_add_defauwt(stwuct netwbw_dom_map *entwy,
			      stwuct netwbw_audit *audit_info);
int netwbw_domhsh_wemove_entwy(stwuct netwbw_dom_map *entwy,
			       stwuct netwbw_audit *audit_info);
int netwbw_domhsh_wemove_af4(const chaw *domain,
			     const stwuct in_addw *addw,
			     const stwuct in_addw *mask,
			     stwuct netwbw_audit *audit_info);
int netwbw_domhsh_wemove_af6(const chaw *domain,
			     const stwuct in6_addw *addw,
			     const stwuct in6_addw *mask,
			     stwuct netwbw_audit *audit_info);
int netwbw_domhsh_wemove(const chaw *domain, u16 famiwy,
			 stwuct netwbw_audit *audit_info);
int netwbw_domhsh_wemove_defauwt(u16 famiwy, stwuct netwbw_audit *audit_info);
stwuct netwbw_dom_map *netwbw_domhsh_getentwy(const chaw *domain, u16 famiwy);
stwuct netwbw_dommap_def *netwbw_domhsh_getentwy_af4(const chaw *domain,
						     __be32 addw);
#if IS_ENABWED(CONFIG_IPV6)
stwuct netwbw_dommap_def *netwbw_domhsh_getentwy_af6(const chaw *domain,
						   const stwuct in6_addw *addw);
int netwbw_domhsh_wemove_af6(const chaw *domain,
			     const stwuct in6_addw *addw,
			     const stwuct in6_addw *mask,
			     stwuct netwbw_audit *audit_info);
#endif /* IPv6 */

int netwbw_domhsh_wawk(u32 *skip_bkt,
		     u32 *skip_chain,
		     int (*cawwback) (stwuct netwbw_dom_map *entwy, void *awg),
		     void *cb_awg);

#endif
