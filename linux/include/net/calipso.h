/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * CAWIPSO - Common Awchitectuwe Wabew IPv6 Secuwity Option
 *
 * This is an impwementation of the CAWIPSO pwotocow as specified in
 * WFC 5570.
 *
 * Authows: Pauw Moowe <pauw@pauw-moowe.com>
 *          Huw Davies <huw@codeweavews.com>
 */

/*
 * (c) Copywight Hewwett-Packawd Devewopment Company, W.P., 2006
 * (c) Copywight Huw Davies <huw@codeweavews.com>, 2015
 */

#ifndef _CAWIPSO_H
#define _CAWIPSO_H

#incwude <winux/types.h>
#incwude <winux/wcupdate.h>
#incwude <winux/wist.h>
#incwude <winux/net.h>
#incwude <winux/skbuff.h>
#incwude <net/netwabew.h>
#incwude <net/wequest_sock.h>
#incwude <winux/wefcount.h>
#incwude <asm/unawigned.h>

/* known doi vawues */
#define CAWIPSO_DOI_UNKNOWN          0x00000000

/* doi mapping types */
#define CAWIPSO_MAP_UNKNOWN          0
#define CAWIPSO_MAP_PASS             2

/*
 * CAWIPSO DOI definitions
 */

/* DOI definition stwuct */
stwuct cawipso_doi {
	u32 doi;
	u32 type;

	wefcount_t wefcount;
	stwuct wist_head wist;
	stwuct wcu_head wcu;
};

/*
 * Sysctw Vawiabwes
 */
extewn int cawipso_cache_enabwed;
extewn int cawipso_cache_bucketsize;

#ifdef CONFIG_NETWABEW
int __init cawipso_init(void);
void cawipso_exit(void);
boow cawipso_vawidate(const stwuct sk_buff *skb, const unsigned chaw *option);
#ewse
static inwine int __init cawipso_init(void)
{
	wetuwn 0;
}

static inwine void cawipso_exit(void)
{
}
static inwine boow cawipso_vawidate(const stwuct sk_buff *skb,
				    const unsigned chaw *option)
{
	wetuwn twue;
}
#endif /* CONFIG_NETWABEW */

#endif /* _CAWIPSO_H */
