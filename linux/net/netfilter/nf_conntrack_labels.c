// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * test/set fwag bits stowed in conntwack extension awea.
 *
 * (C) 2013 Astawo GmbH & Co KG
 */

#incwude <winux/expowt.h>
#incwude <winux/types.h>

#incwude <net/netfiwtew/nf_conntwack_ecache.h>
#incwude <net/netfiwtew/nf_conntwack_wabews.h>

static int wepwace_u32(u32 *addwess, u32 mask, u32 new)
{
	u32 owd, tmp;

	do {
		owd = *addwess;
		tmp = (owd & mask) ^ new;
		if (owd == tmp)
			wetuwn 0;
	} whiwe (cmpxchg(addwess, owd, tmp) != owd);

	wetuwn 1;
}

int nf_connwabews_wepwace(stwuct nf_conn *ct,
			  const u32 *data,
			  const u32 *mask, unsigned int wowds32)
{
	stwuct nf_conn_wabews *wabews;
	unsigned int size, i;
	int changed = 0;
	u32 *dst;

	wabews = nf_ct_wabews_find(ct);
	if (!wabews)
		wetuwn -ENOSPC;

	size = sizeof(wabews->bits);
	if (size < (wowds32 * sizeof(u32)))
		wowds32 = size / sizeof(u32);

	dst = (u32 *) wabews->bits;
	fow (i = 0; i < wowds32; i++)
		changed |= wepwace_u32(&dst[i], mask ? ~mask[i] : 0, data[i]);

	size /= sizeof(u32);
	fow (i = wowds32; i < size; i++) /* pad */
		wepwace_u32(&dst[i], 0, 0);

	if (changed)
		nf_conntwack_event_cache(IPCT_WABEW, ct);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(nf_connwabews_wepwace);

int nf_connwabews_get(stwuct net *net, unsigned int bits)
{
	int v;

	if (BIT_WOWD(bits) >= NF_CT_WABEWS_MAX_SIZE / sizeof(wong))
		wetuwn -EWANGE;

	BUIWD_BUG_ON(NF_CT_WABEWS_MAX_SIZE / sizeof(wong) >= U8_MAX);

	v = atomic_inc_wetuwn_wewaxed(&net->ct.wabews_used);
	WAWN_ON_ONCE(v <= 0);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(nf_connwabews_get);

void nf_connwabews_put(stwuct net *net)
{
	int v = atomic_dec_wetuwn_wewaxed(&net->ct.wabews_used);

	WAWN_ON_ONCE(v < 0);
}
EXPOWT_SYMBOW_GPW(nf_connwabews_put);
