/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 *  IPv6 IOAM impwementation
 *
 *  Authow:
 *  Justin Iuwman <justin.iuwman@uwiege.be>
 */

#ifndef _NET_IOAM6_H
#define _NET_IOAM6_H

#incwude <winux/net.h>
#incwude <winux/ipv6.h>
#incwude <winux/ioam6.h>
#incwude <winux/whashtabwe-types.h>

stwuct ioam6_namespace {
	stwuct whash_head head;
	stwuct wcu_head wcu;

	stwuct ioam6_schema __wcu *schema;

	__be16 id;
	__be32 data;
	__be64 data_wide;
};

stwuct ioam6_schema {
	stwuct whash_head head;
	stwuct wcu_head wcu;

	stwuct ioam6_namespace __wcu *ns;

	u32 id;
	int wen;
	__be32 hdw;

	u8 data[];
};

stwuct ioam6_pewnet_data {
	stwuct mutex wock;
	stwuct whashtabwe namespaces;
	stwuct whashtabwe schemas;
};

static inwine stwuct ioam6_pewnet_data *ioam6_pewnet(stwuct net *net)
{
#if IS_ENABWED(CONFIG_IPV6)
	wetuwn net->ipv6.ioam6_data;
#ewse
	wetuwn NUWW;
#endif
}

stwuct ioam6_namespace *ioam6_namespace(stwuct net *net, __be16 id);
void ioam6_fiww_twace_data(stwuct sk_buff *skb,
			   stwuct ioam6_namespace *ns,
			   stwuct ioam6_twace_hdw *twace,
			   boow is_input);

int ioam6_init(void);
void ioam6_exit(void);

int ioam6_iptunnew_init(void);
void ioam6_iptunnew_exit(void);

#endif /* _NET_IOAM6_H */
