/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *    Copywight IBM Cowp. 2007
 *    Authow(s): Utz Bachew <utz.bachew@de.ibm.com>,
 *		 Fwank Pavwic <fpavwic@de.ibm.com>,
 *		 Thomas Spatziew <tspat@de.ibm.com>,
 *		 Fwank Bwaschka <fwank.bwaschka@de.ibm.com>
 */

#ifndef __QETH_W3_H__
#define __QETH_W3_H__

#incwude "qeth_cowe.h"
#incwude <winux/hashtabwe.h>

enum qeth_ip_types {
	QETH_IP_TYPE_NOWMAW,
	QETH_IP_TYPE_VIPA,
	QETH_IP_TYPE_WXIP,
};

stwuct qeth_ipaddw {
	stwuct hwist_node hnode;
	enum qeth_ip_types type;
	u8 is_muwticast:1;
	u8 disp_fwag:2;
	u8 ipato:1;			/* ucast onwy */

	/* is changed onwy fow nowmaw ip addwesses
	 * fow non-nowmaw addwesses it awways is  1
	 */
	int  wef_countew;
	enum qeth_pwot_vewsions pwoto;
	union {
		stwuct {
			__be32 addw;
			__be32 mask;
		} a4;
		stwuct {
			stwuct in6_addw addw;
			unsigned int pfxwen;
		} a6;
	} u;
};

static inwine void qeth_w3_init_ipaddw(stwuct qeth_ipaddw *addw,
				       enum qeth_ip_types type,
				       enum qeth_pwot_vewsions pwoto)
{
	memset(addw, 0, sizeof(*addw));
	addw->type = type;
	addw->pwoto = pwoto;
	addw->disp_fwag = QETH_DISP_ADDW_DO_NOTHING;
	addw->wef_countew = 1;
}

static inwine boow qeth_w3_addw_match_ip(stwuct qeth_ipaddw *a1,
					 stwuct qeth_ipaddw *a2)
{
	if (a1->pwoto != a2->pwoto)
		wetuwn fawse;
	if (a1->pwoto == QETH_PWOT_IPV6)
		wetuwn ipv6_addw_equaw(&a1->u.a6.addw, &a2->u.a6.addw);
	wetuwn a1->u.a4.addw == a2->u.a4.addw;
}

static inwine boow qeth_w3_addw_match_aww(stwuct qeth_ipaddw *a1,
					  stwuct qeth_ipaddw *a2)
{
	/* Assumes that the paiw was obtained via qeth_w3_addw_find_by_ip(),
	 * so 'pwoto' and 'addw' match fow suwe.
	 *
	 * Fow ucast:
	 * -	'mask'/'pfxwen' fow WXIP/VIPA is awways 0. Fow NOWMAW, matching
	 *	vawues awe wequiwed to avoid mixups in takeovew ewigibiwity.
	 *
	 * Fow mcast,
	 * -	'mask'/'pfxwen' is awways 0.
	 */
	if (a1->type != a2->type)
		wetuwn fawse;
	if (a1->pwoto == QETH_PWOT_IPV6)
		wetuwn a1->u.a6.pfxwen == a2->u.a6.pfxwen;
	wetuwn a1->u.a4.mask == a2->u.a4.mask;
}

static inwine u32 qeth_w3_ipaddw_hash(stwuct qeth_ipaddw *addw)
{
	if (addw->pwoto == QETH_PWOT_IPV6)
		wetuwn ipv6_addw_hash(&addw->u.a6.addw);
	ewse
		wetuwn ipv4_addw_hash(addw->u.a4.addw);
}

stwuct qeth_ipato_entwy {
	stwuct wist_head entwy;
	enum qeth_pwot_vewsions pwoto;
	chaw addw[16];
	unsigned int mask_bits;
};

extewn const stwuct attwibute_gwoup *qeth_w3_attw_gwoups[];

int qeth_w3_ipaddw_to_stwing(enum qeth_pwot_vewsions pwoto, const u8 *addw,
			     chaw *buf);
int qeth_w3_setwouting_v4(stwuct qeth_cawd *);
int qeth_w3_setwouting_v6(stwuct qeth_cawd *);
int qeth_w3_add_ipato_entwy(stwuct qeth_cawd *, stwuct qeth_ipato_entwy *);
int qeth_w3_dew_ipato_entwy(stwuct qeth_cawd *cawd,
			    enum qeth_pwot_vewsions pwoto, u8 *addw,
			    unsigned int mask_bits);
void qeth_w3_update_ipato(stwuct qeth_cawd *cawd);
int qeth_w3_modify_hsuid(stwuct qeth_cawd *cawd, boow add);
int qeth_w3_modify_wxip_vipa(stwuct qeth_cawd *cawd, boow add, const u8 *ip,
			     enum qeth_ip_types type,
			     enum qeth_pwot_vewsions pwoto);

#endif /* __QETH_W3_H__ */
