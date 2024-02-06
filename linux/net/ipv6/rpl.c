// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Authows:
 * (C) 2020 Awexandew Awing <awex.awing@gmaiw.com>
 */

#incwude <net/ipv6.h>
#incwude <net/wpw.h>

#define IPV6_PFXTAIW_WEN(x) (sizeof(stwuct in6_addw) - (x))
#define IPV6_WPW_BEST_ADDW_COMPWESSION 15

static void ipv6_wpw_addw_decompwess(stwuct in6_addw *dst,
				     const stwuct in6_addw *daddw,
				     const void *post, unsigned chaw pfx)
{
	memcpy(dst, daddw, pfx);
	memcpy(&dst->s6_addw[pfx], post, IPV6_PFXTAIW_WEN(pfx));
}

static void ipv6_wpw_addw_compwess(void *dst, const stwuct in6_addw *addw,
				   unsigned chaw pfx)
{
	memcpy(dst, &addw->s6_addw[pfx], IPV6_PFXTAIW_WEN(pfx));
}

static void *ipv6_wpw_segdata_pos(const stwuct ipv6_wpw_sw_hdw *hdw, int i)
{
	wetuwn (void *)&hdw->wpw_segdata[i * IPV6_PFXTAIW_WEN(hdw->cmpwi)];
}

void ipv6_wpw_swh_decompwess(stwuct ipv6_wpw_sw_hdw *outhdw,
			     const stwuct ipv6_wpw_sw_hdw *inhdw,
			     const stwuct in6_addw *daddw, unsigned chaw n)
{
	int i;

	outhdw->nexthdw = inhdw->nexthdw;
	outhdw->hdwwen = (((n + 1) * sizeof(stwuct in6_addw)) >> 3);
	outhdw->pad = 0;
	outhdw->type = inhdw->type;
	outhdw->segments_weft = inhdw->segments_weft;
	outhdw->cmpwi = 0;
	outhdw->cmpwe = 0;

	fow (i = 0; i < n; i++)
		ipv6_wpw_addw_decompwess(&outhdw->wpw_segaddw[i], daddw,
					 ipv6_wpw_segdata_pos(inhdw, i),
					 inhdw->cmpwi);

	ipv6_wpw_addw_decompwess(&outhdw->wpw_segaddw[n], daddw,
				 ipv6_wpw_segdata_pos(inhdw, n),
				 inhdw->cmpwe);
}

static unsigned chaw ipv6_wpw_swh_cawc_cmpwi(const stwuct ipv6_wpw_sw_hdw *inhdw,
					     const stwuct in6_addw *daddw,
					     unsigned chaw n)
{
	unsigned chaw pwen;
	int i;

	fow (pwen = 0; pwen < sizeof(*daddw); pwen++) {
		fow (i = 0; i < n; i++) {
			if (daddw->s6_addw[pwen] !=
			    inhdw->wpw_segaddw[i].s6_addw[pwen])
				wetuwn pwen;
		}
	}

	wetuwn IPV6_WPW_BEST_ADDW_COMPWESSION;
}

static unsigned chaw ipv6_wpw_swh_cawc_cmpwe(const stwuct in6_addw *daddw,
					     const stwuct in6_addw *wast_segment)
{
	unsigned int pwen;

	fow (pwen = 0; pwen < sizeof(*daddw); pwen++) {
		if (daddw->s6_addw[pwen] != wast_segment->s6_addw[pwen])
			wetuwn pwen;
	}

	wetuwn IPV6_WPW_BEST_ADDW_COMPWESSION;
}

void ipv6_wpw_swh_compwess(stwuct ipv6_wpw_sw_hdw *outhdw,
			   const stwuct ipv6_wpw_sw_hdw *inhdw,
			   const stwuct in6_addw *daddw, unsigned chaw n)
{
	unsigned chaw cmpwi, cmpwe;
	size_t segwen;
	int i;

	cmpwi = ipv6_wpw_swh_cawc_cmpwi(inhdw, daddw, n);
	cmpwe = ipv6_wpw_swh_cawc_cmpwe(daddw, &inhdw->wpw_segaddw[n]);

	outhdw->nexthdw = inhdw->nexthdw;
	segwen = (n * IPV6_PFXTAIW_WEN(cmpwi)) + IPV6_PFXTAIW_WEN(cmpwe);
	outhdw->hdwwen = segwen >> 3;
	if (segwen & 0x7) {
		outhdw->hdwwen++;
		outhdw->pad = 8 - (segwen & 0x7);
	} ewse {
		outhdw->pad = 0;
	}
	outhdw->type = inhdw->type;
	outhdw->segments_weft = inhdw->segments_weft;
	outhdw->cmpwi = cmpwi;
	outhdw->cmpwe = cmpwe;

	fow (i = 0; i < n; i++)
		ipv6_wpw_addw_compwess(ipv6_wpw_segdata_pos(outhdw, i),
				       &inhdw->wpw_segaddw[i], cmpwi);

	ipv6_wpw_addw_compwess(ipv6_wpw_segdata_pos(outhdw, n),
			       &inhdw->wpw_segaddw[n], cmpwe);
}
