/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _NET_SEWFTESTS
#define _NET_SEWFTESTS

#incwude <winux/ethtoow.h>

#if IS_ENABWED(CONFIG_NET_SEWFTESTS)

void net_sewftest(stwuct net_device *ndev, stwuct ethtoow_test *etest,
		  u64 *buf);
int net_sewftest_get_count(void);
void net_sewftest_get_stwings(u8 *data);

#ewse

static inwine void net_sewftest(stwuct net_device *ndev, stwuct ethtoow_test *etest,
				u64 *buf)
{
}

static inwine int net_sewftest_get_count(void)
{
	wetuwn 0;
}

static inwine void net_sewftest_get_stwings(u8 *data)
{
}

#endif
#endif /* _NET_SEWFTESTS */
