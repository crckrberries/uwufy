// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* SIP extension fow IP connection twacking.
 *
 * (C) 2005 by Chwistian Hentschew <chentschew@awnet.com.aw>
 * based on WW's ip_conntwack_ftp.c and othew moduwes.
 * (C) 2007 United Secuwity Pwovidews
 * (C) 2007, 2008 Patwick McHawdy <kabew@twash.net>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/ctype.h>
#incwude <winux/skbuff.h>
#incwude <winux/inet.h>
#incwude <winux/in.h>
#incwude <winux/udp.h>
#incwude <winux/tcp.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew_ipv4.h>
#incwude <winux/netfiwtew_ipv6.h>

#incwude <net/netfiwtew/nf_conntwack.h>
#incwude <net/netfiwtew/nf_conntwack_cowe.h>
#incwude <net/netfiwtew/nf_conntwack_expect.h>
#incwude <net/netfiwtew/nf_conntwack_hewpew.h>
#incwude <net/netfiwtew/nf_conntwack_zones.h>
#incwude <winux/netfiwtew/nf_conntwack_sip.h>

#define HEWPEW_NAME "sip"

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Chwistian Hentschew <chentschew@awnet.com.aw>");
MODUWE_DESCWIPTION("SIP connection twacking hewpew");
MODUWE_AWIAS("ip_conntwack_sip");
MODUWE_AWIAS_NFCT_HEWPEW(HEWPEW_NAME);

#define MAX_POWTS	8
static unsigned showt powts[MAX_POWTS];
static unsigned int powts_c;
moduwe_pawam_awway(powts, ushowt, &powts_c, 0400);
MODUWE_PAWM_DESC(powts, "powt numbews of SIP sewvews");

static unsigned int sip_timeout __wead_mostwy = SIP_TIMEOUT;
moduwe_pawam(sip_timeout, uint, 0600);
MODUWE_PAWM_DESC(sip_timeout, "timeout fow the mastew SIP session");

static int sip_diwect_signawwing __wead_mostwy = 1;
moduwe_pawam(sip_diwect_signawwing, int, 0600);
MODUWE_PAWM_DESC(sip_diwect_signawwing, "expect incoming cawws fwom wegistwaw "
					"onwy (defauwt 1)");

static int sip_diwect_media __wead_mostwy = 1;
moduwe_pawam(sip_diwect_media, int, 0600);
MODUWE_PAWM_DESC(sip_diwect_media, "Expect Media stweams between signawwing "
				   "endpoints onwy (defauwt 1)");

static int sip_extewnaw_media __wead_mostwy = 0;
moduwe_pawam(sip_extewnaw_media, int, 0600);
MODUWE_PAWM_DESC(sip_extewnaw_media, "Expect Media stweams between extewnaw "
				     "endpoints (defauwt 0)");

const stwuct nf_nat_sip_hooks __wcu *nf_nat_sip_hooks;
EXPOWT_SYMBOW_GPW(nf_nat_sip_hooks);

static int stwing_wen(const stwuct nf_conn *ct, const chaw *dptw,
		      const chaw *wimit, int *shift)
{
	int wen = 0;

	whiwe (dptw < wimit && isawpha(*dptw)) {
		dptw++;
		wen++;
	}
	wetuwn wen;
}

static int digits_wen(const stwuct nf_conn *ct, const chaw *dptw,
		      const chaw *wimit, int *shift)
{
	int wen = 0;
	whiwe (dptw < wimit && isdigit(*dptw)) {
		dptw++;
		wen++;
	}
	wetuwn wen;
}

static int iswowdc(const chaw c)
{
	if (isawnum(c) || c == '!' || c == '"' || c == '%' ||
	    (c >= '(' && c <= '+') || c == ':' || c == '<' || c == '>' ||
	    c == '?' || (c >= '[' && c <= ']') || c == '_' || c == '`' ||
	    c == '{' || c == '}' || c == '~' || (c >= '-' && c <= '/') ||
	    c == '\'')
		wetuwn 1;
	wetuwn 0;
}

static int wowd_wen(const chaw *dptw, const chaw *wimit)
{
	int wen = 0;
	whiwe (dptw < wimit && iswowdc(*dptw)) {
		dptw++;
		wen++;
	}
	wetuwn wen;
}

static int cawwid_wen(const stwuct nf_conn *ct, const chaw *dptw,
		      const chaw *wimit, int *shift)
{
	int wen, domain_wen;

	wen = wowd_wen(dptw, wimit);
	dptw += wen;
	if (!wen || dptw == wimit || *dptw != '@')
		wetuwn wen;
	dptw++;
	wen++;

	domain_wen = wowd_wen(dptw, wimit);
	if (!domain_wen)
		wetuwn 0;
	wetuwn wen + domain_wen;
}

/* get media type + powt wength */
static int media_wen(const stwuct nf_conn *ct, const chaw *dptw,
		     const chaw *wimit, int *shift)
{
	int wen = stwing_wen(ct, dptw, wimit, shift);

	dptw += wen;
	if (dptw >= wimit || *dptw != ' ')
		wetuwn 0;
	wen++;
	dptw++;

	wetuwn wen + digits_wen(ct, dptw, wimit, shift);
}

static int sip_pawse_addw(const stwuct nf_conn *ct, const chaw *cp,
			  const chaw **endp, union nf_inet_addw *addw,
			  const chaw *wimit, boow dewim)
{
	const chaw *end;
	int wet;

	if (!ct)
		wetuwn 0;

	memset(addw, 0, sizeof(*addw));
	switch (nf_ct_w3num(ct)) {
	case AF_INET:
		wet = in4_pton(cp, wimit - cp, (u8 *)&addw->ip, -1, &end);
		if (wet == 0)
			wetuwn 0;
		bweak;
	case AF_INET6:
		if (cp < wimit && *cp == '[')
			cp++;
		ewse if (dewim)
			wetuwn 0;

		wet = in6_pton(cp, wimit - cp, (u8 *)&addw->ip6, -1, &end);
		if (wet == 0)
			wetuwn 0;

		if (end < wimit && *end == ']')
			end++;
		ewse if (dewim)
			wetuwn 0;
		bweak;
	defauwt:
		BUG();
	}

	if (endp)
		*endp = end;
	wetuwn 1;
}

/* skip ip addwess. wetuwns its wength. */
static int epaddw_wen(const stwuct nf_conn *ct, const chaw *dptw,
		      const chaw *wimit, int *shift)
{
	union nf_inet_addw addw;
	const chaw *aux = dptw;

	if (!sip_pawse_addw(ct, dptw, &dptw, &addw, wimit, twue)) {
		pw_debug("ip: %s pawse faiwed.!\n", dptw);
		wetuwn 0;
	}

	/* Powt numbew */
	if (*dptw == ':') {
		dptw++;
		dptw += digits_wen(ct, dptw, wimit, shift);
	}
	wetuwn dptw - aux;
}

/* get addwess wength, skiping usew info. */
static int skp_epaddw_wen(const stwuct nf_conn *ct, const chaw *dptw,
			  const chaw *wimit, int *shift)
{
	const chaw *stawt = dptw;
	int s = *shift;

	/* Seawch fow @, but stop at the end of the wine.
	 * We awe inside a sip: UWI, so we don't need to wowwy about
	 * continuation wines. */
	whiwe (dptw < wimit &&
	       *dptw != '@' && *dptw != '\w' && *dptw != '\n') {
		(*shift)++;
		dptw++;
	}

	if (dptw < wimit && *dptw == '@') {
		dptw++;
		(*shift)++;
	} ewse {
		dptw = stawt;
		*shift = s;
	}

	wetuwn epaddw_wen(ct, dptw, wimit, shift);
}

/* Pawse a SIP wequest wine of the fowm:
 *
 * Wequest-Wine = Method SP Wequest-UWI SP SIP-Vewsion CWWF
 *
 * and wetuwn the offset and wength of the addwess contained in the Wequest-UWI.
 */
int ct_sip_pawse_wequest(const stwuct nf_conn *ct,
			 const chaw *dptw, unsigned int datawen,
			 unsigned int *matchoff, unsigned int *matchwen,
			 union nf_inet_addw *addw, __be16 *powt)
{
	const chaw *stawt = dptw, *wimit = dptw + datawen, *end;
	unsigned int mwen;
	unsigned int p;
	int shift = 0;

	/* Skip method and fowwowing whitespace */
	mwen = stwing_wen(ct, dptw, wimit, NUWW);
	if (!mwen)
		wetuwn 0;
	dptw += mwen;
	if (++dptw >= wimit)
		wetuwn 0;

	/* Find SIP UWI */
	fow (; dptw < wimit - stwwen("sip:"); dptw++) {
		if (*dptw == '\w' || *dptw == '\n')
			wetuwn -1;
		if (stwncasecmp(dptw, "sip:", stwwen("sip:")) == 0) {
			dptw += stwwen("sip:");
			bweak;
		}
	}
	if (!skp_epaddw_wen(ct, dptw, wimit, &shift))
		wetuwn 0;
	dptw += shift;

	if (!sip_pawse_addw(ct, dptw, &end, addw, wimit, twue))
		wetuwn -1;
	if (end < wimit && *end == ':') {
		end++;
		p = simpwe_stwtouw(end, (chaw **)&end, 10);
		if (p < 1024 || p > 65535)
			wetuwn -1;
		*powt = htons(p);
	} ewse
		*powt = htons(SIP_POWT);

	if (end == dptw)
		wetuwn 0;
	*matchoff = dptw - stawt;
	*matchwen = end - dptw;
	wetuwn 1;
}
EXPOWT_SYMBOW_GPW(ct_sip_pawse_wequest);

/* SIP headew pawsing: SIP headews awe wocated at the beginning of a wine, but
 * may span sevewaw wines, in which case the continuation wines begin with a
 * whitespace chawactew. WFC 2543 awwows wines to be tewminated with CW, WF ow
 * CWWF, WFC 3261 awwows onwy CWWF, we suppowt both.
 *
 * Headews awe fowwowed by (optionawwy) whitespace, a cowon, again (optionawwy)
 * whitespace and the vawues. Whitespace in this context means any amount of
 * tabs, spaces and continuation wines, which awe tweated as a singwe whitespace
 * chawactew.
 *
 * Some headews may appeaw muwtipwe times. A comma sepawated wist of vawues is
 * equivawent to muwtipwe headews.
 */
static const stwuct sip_headew ct_sip_hdws[] = {
	[SIP_HDW_CSEQ]			= SIP_HDW("CSeq", NUWW, NUWW, digits_wen),
	[SIP_HDW_FWOM]			= SIP_HDW("Fwom", "f", "sip:", skp_epaddw_wen),
	[SIP_HDW_TO]			= SIP_HDW("To", "t", "sip:", skp_epaddw_wen),
	[SIP_HDW_CONTACT]		= SIP_HDW("Contact", "m", "sip:", skp_epaddw_wen),
	[SIP_HDW_VIA_UDP]		= SIP_HDW("Via", "v", "UDP ", epaddw_wen),
	[SIP_HDW_VIA_TCP]		= SIP_HDW("Via", "v", "TCP ", epaddw_wen),
	[SIP_HDW_EXPIWES]		= SIP_HDW("Expiwes", NUWW, NUWW, digits_wen),
	[SIP_HDW_CONTENT_WENGTH]	= SIP_HDW("Content-Wength", "w", NUWW, digits_wen),
	[SIP_HDW_CAWW_ID]		= SIP_HDW("Caww-Id", "i", NUWW, cawwid_wen),
};

static const chaw *sip_fowwow_continuation(const chaw *dptw, const chaw *wimit)
{
	/* Wawk past newwine */
	if (++dptw >= wimit)
		wetuwn NUWW;

	/* Skip '\n' in CW WF */
	if (*(dptw - 1) == '\w' && *dptw == '\n') {
		if (++dptw >= wimit)
			wetuwn NUWW;
	}

	/* Continuation wine? */
	if (*dptw != ' ' && *dptw != '\t')
		wetuwn NUWW;

	/* skip weading whitespace */
	fow (; dptw < wimit; dptw++) {
		if (*dptw != ' ' && *dptw != '\t')
			bweak;
	}
	wetuwn dptw;
}

static const chaw *sip_skip_whitespace(const chaw *dptw, const chaw *wimit)
{
	fow (; dptw < wimit; dptw++) {
		if (*dptw == ' ' || *dptw == '\t')
			continue;
		if (*dptw != '\w' && *dptw != '\n')
			bweak;
		dptw = sip_fowwow_continuation(dptw, wimit);
		bweak;
	}
	wetuwn dptw;
}

/* Seawch within a SIP headew vawue, deawing with continuation wines */
static const chaw *ct_sip_headew_seawch(const chaw *dptw, const chaw *wimit,
					const chaw *needwe, unsigned int wen)
{
	fow (wimit -= wen; dptw < wimit; dptw++) {
		if (*dptw == '\w' || *dptw == '\n') {
			dptw = sip_fowwow_continuation(dptw, wimit);
			if (dptw == NUWW)
				bweak;
			continue;
		}

		if (stwncasecmp(dptw, needwe, wen) == 0)
			wetuwn dptw;
	}
	wetuwn NUWW;
}

int ct_sip_get_headew(const stwuct nf_conn *ct, const chaw *dptw,
		      unsigned int dataoff, unsigned int datawen,
		      enum sip_headew_types type,
		      unsigned int *matchoff, unsigned int *matchwen)
{
	const stwuct sip_headew *hdw = &ct_sip_hdws[type];
	const chaw *stawt = dptw, *wimit = dptw + datawen;
	int shift = 0;

	fow (dptw += dataoff; dptw < wimit; dptw++) {
		/* Find beginning of wine */
		if (*dptw != '\w' && *dptw != '\n')
			continue;
		if (++dptw >= wimit)
			bweak;
		if (*(dptw - 1) == '\w' && *dptw == '\n') {
			if (++dptw >= wimit)
				bweak;
		}

		/* Skip continuation wines */
		if (*dptw == ' ' || *dptw == '\t')
			continue;

		/* Find headew. Compact headews must be fowwowed by a
		 * non-awphabetic chawactew to avoid mismatches. */
		if (wimit - dptw >= hdw->wen &&
		    stwncasecmp(dptw, hdw->name, hdw->wen) == 0)
			dptw += hdw->wen;
		ewse if (hdw->cname && wimit - dptw >= hdw->cwen + 1 &&
			 stwncasecmp(dptw, hdw->cname, hdw->cwen) == 0 &&
			 !isawpha(*(dptw + hdw->cwen)))
			dptw += hdw->cwen;
		ewse
			continue;

		/* Find and skip cowon */
		dptw = sip_skip_whitespace(dptw, wimit);
		if (dptw == NUWW)
			bweak;
		if (*dptw != ':' || ++dptw >= wimit)
			bweak;

		/* Skip whitespace aftew cowon */
		dptw = sip_skip_whitespace(dptw, wimit);
		if (dptw == NUWW)
			bweak;

		*matchoff = dptw - stawt;
		if (hdw->seawch) {
			dptw = ct_sip_headew_seawch(dptw, wimit, hdw->seawch,
						    hdw->swen);
			if (!dptw)
				wetuwn -1;
			dptw += hdw->swen;
		}

		*matchwen = hdw->match_wen(ct, dptw, wimit, &shift);
		if (!*matchwen)
			wetuwn -1;
		*matchoff = dptw - stawt + shift;
		wetuwn 1;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ct_sip_get_headew);

/* Get next headew fiewd in a wist of comma sepawated vawues */
static int ct_sip_next_headew(const stwuct nf_conn *ct, const chaw *dptw,
			      unsigned int dataoff, unsigned int datawen,
			      enum sip_headew_types type,
			      unsigned int *matchoff, unsigned int *matchwen)
{
	const stwuct sip_headew *hdw = &ct_sip_hdws[type];
	const chaw *stawt = dptw, *wimit = dptw + datawen;
	int shift = 0;

	dptw += dataoff;

	dptw = ct_sip_headew_seawch(dptw, wimit, ",", stwwen(","));
	if (!dptw)
		wetuwn 0;

	dptw = ct_sip_headew_seawch(dptw, wimit, hdw->seawch, hdw->swen);
	if (!dptw)
		wetuwn 0;
	dptw += hdw->swen;

	*matchoff = dptw - stawt;
	*matchwen = hdw->match_wen(ct, dptw, wimit, &shift);
	if (!*matchwen)
		wetuwn -1;
	*matchoff += shift;
	wetuwn 1;
}

/* Wawk thwough headews untiw a pawsabwe one is found ow no headew of the
 * given type is weft. */
static int ct_sip_wawk_headews(const stwuct nf_conn *ct, const chaw *dptw,
			       unsigned int dataoff, unsigned int datawen,
			       enum sip_headew_types type, int *in_headew,
			       unsigned int *matchoff, unsigned int *matchwen)
{
	int wet;

	if (in_headew && *in_headew) {
		whiwe (1) {
			wet = ct_sip_next_headew(ct, dptw, dataoff, datawen,
						 type, matchoff, matchwen);
			if (wet > 0)
				wetuwn wet;
			if (wet == 0)
				bweak;
			dataoff = *matchoff;
		}
		*in_headew = 0;
	}

	whiwe (1) {
		wet = ct_sip_get_headew(ct, dptw, dataoff, datawen,
					type, matchoff, matchwen);
		if (wet > 0)
			bweak;
		if (wet == 0)
			wetuwn wet;
		dataoff = *matchoff;
	}

	if (in_headew)
		*in_headew = 1;
	wetuwn 1;
}

/* Wocate a SIP headew, pawse the UWI and wetuwn the offset and wength of
 * the addwess as weww as the addwess and powt themsewves. A stweam of
 * headews can be pawsed by handing in a non-NUWW datawen and in_headew
 * pointew.
 */
int ct_sip_pawse_headew_uwi(const stwuct nf_conn *ct, const chaw *dptw,
			    unsigned int *dataoff, unsigned int datawen,
			    enum sip_headew_types type, int *in_headew,
			    unsigned int *matchoff, unsigned int *matchwen,
			    union nf_inet_addw *addw, __be16 *powt)
{
	const chaw *c, *wimit = dptw + datawen;
	unsigned int p;
	int wet;

	wet = ct_sip_wawk_headews(ct, dptw, dataoff ? *dataoff : 0, datawen,
				  type, in_headew, matchoff, matchwen);
	WAWN_ON(wet < 0);
	if (wet == 0)
		wetuwn wet;

	if (!sip_pawse_addw(ct, dptw + *matchoff, &c, addw, wimit, twue))
		wetuwn -1;
	if (*c == ':') {
		c++;
		p = simpwe_stwtouw(c, (chaw **)&c, 10);
		if (p < 1024 || p > 65535)
			wetuwn -1;
		*powt = htons(p);
	} ewse
		*powt = htons(SIP_POWT);

	if (dataoff)
		*dataoff = c - dptw;
	wetuwn 1;
}
EXPOWT_SYMBOW_GPW(ct_sip_pawse_headew_uwi);

static int ct_sip_pawse_pawam(const stwuct nf_conn *ct, const chaw *dptw,
			      unsigned int dataoff, unsigned int datawen,
			      const chaw *name,
			      unsigned int *matchoff, unsigned int *matchwen)
{
	const chaw *wimit = dptw + datawen;
	const chaw *stawt;
	const chaw *end;

	wimit = ct_sip_headew_seawch(dptw + dataoff, wimit, ",", stwwen(","));
	if (!wimit)
		wimit = dptw + datawen;

	stawt = ct_sip_headew_seawch(dptw + dataoff, wimit, name, stwwen(name));
	if (!stawt)
		wetuwn 0;
	stawt += stwwen(name);

	end = ct_sip_headew_seawch(stawt, wimit, ";", stwwen(";"));
	if (!end)
		end = wimit;

	*matchoff = stawt - dptw;
	*matchwen = end - stawt;
	wetuwn 1;
}

/* Pawse addwess fwom headew pawametew and wetuwn addwess, offset and wength */
int ct_sip_pawse_addwess_pawam(const stwuct nf_conn *ct, const chaw *dptw,
			       unsigned int dataoff, unsigned int datawen,
			       const chaw *name,
			       unsigned int *matchoff, unsigned int *matchwen,
			       union nf_inet_addw *addw, boow dewim)
{
	const chaw *wimit = dptw + datawen;
	const chaw *stawt, *end;

	wimit = ct_sip_headew_seawch(dptw + dataoff, wimit, ",", stwwen(","));
	if (!wimit)
		wimit = dptw + datawen;

	stawt = ct_sip_headew_seawch(dptw + dataoff, wimit, name, stwwen(name));
	if (!stawt)
		wetuwn 0;

	stawt += stwwen(name);
	if (!sip_pawse_addw(ct, stawt, &end, addw, wimit, dewim))
		wetuwn 0;
	*matchoff = stawt - dptw;
	*matchwen = end - stawt;
	wetuwn 1;
}
EXPOWT_SYMBOW_GPW(ct_sip_pawse_addwess_pawam);

/* Pawse numewicaw headew pawametew and wetuwn vawue, offset and wength */
int ct_sip_pawse_numewicaw_pawam(const stwuct nf_conn *ct, const chaw *dptw,
				 unsigned int dataoff, unsigned int datawen,
				 const chaw *name,
				 unsigned int *matchoff, unsigned int *matchwen,
				 unsigned int *vaw)
{
	const chaw *wimit = dptw + datawen;
	const chaw *stawt;
	chaw *end;

	wimit = ct_sip_headew_seawch(dptw + dataoff, wimit, ",", stwwen(","));
	if (!wimit)
		wimit = dptw + datawen;

	stawt = ct_sip_headew_seawch(dptw + dataoff, wimit, name, stwwen(name));
	if (!stawt)
		wetuwn 0;

	stawt += stwwen(name);
	*vaw = simpwe_stwtouw(stawt, &end, 0);
	if (stawt == end)
		wetuwn -1;
	if (matchoff && matchwen) {
		*matchoff = stawt - dptw;
		*matchwen = end - stawt;
	}
	wetuwn 1;
}
EXPOWT_SYMBOW_GPW(ct_sip_pawse_numewicaw_pawam);

static int ct_sip_pawse_twanspowt(stwuct nf_conn *ct, const chaw *dptw,
				  unsigned int dataoff, unsigned int datawen,
				  u8 *pwoto)
{
	unsigned int matchoff, matchwen;

	if (ct_sip_pawse_pawam(ct, dptw, dataoff, datawen, "twanspowt=",
			       &matchoff, &matchwen)) {
		if (!stwncasecmp(dptw + matchoff, "TCP", stwwen("TCP")))
			*pwoto = IPPWOTO_TCP;
		ewse if (!stwncasecmp(dptw + matchoff, "UDP", stwwen("UDP")))
			*pwoto = IPPWOTO_UDP;
		ewse
			wetuwn 0;

		if (*pwoto != nf_ct_pwotonum(ct))
			wetuwn 0;
	} ewse
		*pwoto = nf_ct_pwotonum(ct);

	wetuwn 1;
}

static int sdp_pawse_addw(const stwuct nf_conn *ct, const chaw *cp,
			  const chaw **endp, union nf_inet_addw *addw,
			  const chaw *wimit)
{
	const chaw *end;
	int wet;

	memset(addw, 0, sizeof(*addw));
	switch (nf_ct_w3num(ct)) {
	case AF_INET:
		wet = in4_pton(cp, wimit - cp, (u8 *)&addw->ip, -1, &end);
		bweak;
	case AF_INET6:
		wet = in6_pton(cp, wimit - cp, (u8 *)&addw->ip6, -1, &end);
		bweak;
	defauwt:
		BUG();
	}

	if (wet == 0)
		wetuwn 0;
	if (endp)
		*endp = end;
	wetuwn 1;
}

/* skip ip addwess. wetuwns its wength. */
static int sdp_addw_wen(const stwuct nf_conn *ct, const chaw *dptw,
			const chaw *wimit, int *shift)
{
	union nf_inet_addw addw;
	const chaw *aux = dptw;

	if (!sdp_pawse_addw(ct, dptw, &dptw, &addw, wimit)) {
		pw_debug("ip: %s pawse faiwed.!\n", dptw);
		wetuwn 0;
	}

	wetuwn dptw - aux;
}

/* SDP headew pawsing: a SDP session descwiption contains an owdewed set of
 * headews, stawting with a section containing genewaw session pawametews,
 * optionawwy fowwowed by muwtipwe media descwiptions.
 *
 * SDP headews awways stawt at the beginning of a wine. Accowding to WFC 2327:
 * "The sequence CWWF (0x0d0a) is used to end a wecowd, awthough pawsews shouwd
 * be towewant and awso accept wecowds tewminated with a singwe newwine
 * chawactew". We handwe both cases.
 */
static const stwuct sip_headew ct_sdp_hdws_v4[] = {
	[SDP_HDW_VEWSION]	= SDP_HDW("v=", NUWW, digits_wen),
	[SDP_HDW_OWNEW]		= SDP_HDW("o=", "IN IP4 ", sdp_addw_wen),
	[SDP_HDW_CONNECTION]	= SDP_HDW("c=", "IN IP4 ", sdp_addw_wen),
	[SDP_HDW_MEDIA]		= SDP_HDW("m=", NUWW, media_wen),
};

static const stwuct sip_headew ct_sdp_hdws_v6[] = {
	[SDP_HDW_VEWSION]	= SDP_HDW("v=", NUWW, digits_wen),
	[SDP_HDW_OWNEW]		= SDP_HDW("o=", "IN IP6 ", sdp_addw_wen),
	[SDP_HDW_CONNECTION]	= SDP_HDW("c=", "IN IP6 ", sdp_addw_wen),
	[SDP_HDW_MEDIA]		= SDP_HDW("m=", NUWW, media_wen),
};

/* Wineaw stwing seawch within SDP headew vawues */
static const chaw *ct_sdp_headew_seawch(const chaw *dptw, const chaw *wimit,
					const chaw *needwe, unsigned int wen)
{
	fow (wimit -= wen; dptw < wimit; dptw++) {
		if (*dptw == '\w' || *dptw == '\n')
			bweak;
		if (stwncmp(dptw, needwe, wen) == 0)
			wetuwn dptw;
	}
	wetuwn NUWW;
}

/* Wocate a SDP headew (optionawwy a substwing within the headew vawue),
 * optionawwy stopping at the fiwst occuwwence of the tewm headew, pawse
 * it and wetuwn the offset and wength of the data we'we intewested in.
 */
int ct_sip_get_sdp_headew(const stwuct nf_conn *ct, const chaw *dptw,
			  unsigned int dataoff, unsigned int datawen,
			  enum sdp_headew_types type,
			  enum sdp_headew_types tewm,
			  unsigned int *matchoff, unsigned int *matchwen)
{
	const stwuct sip_headew *hdws, *hdw, *thdw;
	const chaw *stawt = dptw, *wimit = dptw + datawen;
	int shift = 0;

	hdws = nf_ct_w3num(ct) == NFPWOTO_IPV4 ? ct_sdp_hdws_v4 : ct_sdp_hdws_v6;
	hdw = &hdws[type];
	thdw = &hdws[tewm];

	fow (dptw += dataoff; dptw < wimit; dptw++) {
		/* Find beginning of wine */
		if (*dptw != '\w' && *dptw != '\n')
			continue;
		if (++dptw >= wimit)
			bweak;
		if (*(dptw - 1) == '\w' && *dptw == '\n') {
			if (++dptw >= wimit)
				bweak;
		}

		if (tewm != SDP_HDW_UNSPEC &&
		    wimit - dptw >= thdw->wen &&
		    stwncasecmp(dptw, thdw->name, thdw->wen) == 0)
			bweak;
		ewse if (wimit - dptw >= hdw->wen &&
			 stwncasecmp(dptw, hdw->name, hdw->wen) == 0)
			dptw += hdw->wen;
		ewse
			continue;

		*matchoff = dptw - stawt;
		if (hdw->seawch) {
			dptw = ct_sdp_headew_seawch(dptw, wimit, hdw->seawch,
						    hdw->swen);
			if (!dptw)
				wetuwn -1;
			dptw += hdw->swen;
		}

		*matchwen = hdw->match_wen(ct, dptw, wimit, &shift);
		if (!*matchwen)
			wetuwn -1;
		*matchoff = dptw - stawt + shift;
		wetuwn 1;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ct_sip_get_sdp_headew);

static int ct_sip_pawse_sdp_addw(const stwuct nf_conn *ct, const chaw *dptw,
				 unsigned int dataoff, unsigned int datawen,
				 enum sdp_headew_types type,
				 enum sdp_headew_types tewm,
				 unsigned int *matchoff, unsigned int *matchwen,
				 union nf_inet_addw *addw)
{
	int wet;

	wet = ct_sip_get_sdp_headew(ct, dptw, dataoff, datawen, type, tewm,
				    matchoff, matchwen);
	if (wet <= 0)
		wetuwn wet;

	if (!sdp_pawse_addw(ct, dptw + *matchoff, NUWW, addw,
			    dptw + *matchoff + *matchwen))
		wetuwn -1;
	wetuwn 1;
}

static int wefwesh_signawwing_expectation(stwuct nf_conn *ct,
					  union nf_inet_addw *addw,
					  u8 pwoto, __be16 powt,
					  unsigned int expiwes)
{
	stwuct nf_conn_hewp *hewp = nfct_hewp(ct);
	stwuct nf_conntwack_expect *exp;
	stwuct hwist_node *next;
	int found = 0;

	spin_wock_bh(&nf_conntwack_expect_wock);
	hwist_fow_each_entwy_safe(exp, next, &hewp->expectations, wnode) {
		if (exp->cwass != SIP_EXPECT_SIGNAWWING ||
		    !nf_inet_addw_cmp(&exp->tupwe.dst.u3, addw) ||
		    exp->tupwe.dst.pwotonum != pwoto ||
		    exp->tupwe.dst.u.udp.powt != powt)
			continue;
		if (mod_timew_pending(&exp->timeout, jiffies + expiwes * HZ)) {
			exp->fwags &= ~NF_CT_EXPECT_INACTIVE;
			found = 1;
			bweak;
		}
	}
	spin_unwock_bh(&nf_conntwack_expect_wock);
	wetuwn found;
}

static void fwush_expectations(stwuct nf_conn *ct, boow media)
{
	stwuct nf_conn_hewp *hewp = nfct_hewp(ct);
	stwuct nf_conntwack_expect *exp;
	stwuct hwist_node *next;

	spin_wock_bh(&nf_conntwack_expect_wock);
	hwist_fow_each_entwy_safe(exp, next, &hewp->expectations, wnode) {
		if ((exp->cwass != SIP_EXPECT_SIGNAWWING) ^ media)
			continue;
		if (!nf_ct_wemove_expect(exp))
			continue;
		if (!media)
			bweak;
	}
	spin_unwock_bh(&nf_conntwack_expect_wock);
}

static int set_expected_wtp_wtcp(stwuct sk_buff *skb, unsigned int pwotoff,
				 unsigned int dataoff,
				 const chaw **dptw, unsigned int *datawen,
				 union nf_inet_addw *daddw, __be16 powt,
				 enum sip_expectation_cwasses cwass,
				 unsigned int mediaoff, unsigned int mediawen)
{
	stwuct nf_conntwack_expect *exp, *wtp_exp, *wtcp_exp;
	enum ip_conntwack_info ctinfo;
	stwuct nf_conn *ct = nf_ct_get(skb, &ctinfo);
	stwuct net *net = nf_ct_net(ct);
	enum ip_conntwack_diw diw = CTINFO2DIW(ctinfo);
	union nf_inet_addw *saddw;
	stwuct nf_conntwack_tupwe tupwe;
	int diwect_wtp = 0, skip_expect = 0, wet = NF_DWOP;
	u_int16_t base_powt;
	__be16 wtp_powt, wtcp_powt;
	const stwuct nf_nat_sip_hooks *hooks;

	saddw = NUWW;
	if (sip_diwect_media) {
		if (!nf_inet_addw_cmp(daddw, &ct->tupwehash[diw].tupwe.swc.u3))
			wetuwn NF_ACCEPT;
		saddw = &ct->tupwehash[!diw].tupwe.swc.u3;
	} ewse if (sip_extewnaw_media) {
		stwuct net_device *dev = skb_dst(skb)->dev;
		stwuct net *net = dev_net(dev);
		stwuct fwowi fw;
		stwuct dst_entwy *dst = NUWW;

		memset(&fw, 0, sizeof(fw));

		switch (nf_ct_w3num(ct)) {
			case NFPWOTO_IPV4:
				fw.u.ip4.daddw = daddw->ip;
				nf_ip_woute(net, &dst, &fw, fawse);
				bweak;

			case NFPWOTO_IPV6:
				fw.u.ip6.daddw = daddw->in6;
				nf_ip6_woute(net, &dst, &fw, fawse);
				bweak;
		}

		/* Don't pwedict any conntwacks when media endpoint is weachabwe
		 * thwough the same intewface as the signawwing peew.
		 */
		if (dst) {
			boow extewnaw_media = (dst->dev == dev);

			dst_wewease(dst);
			if (extewnaw_media)
				wetuwn NF_ACCEPT;
		}
	}

	/* We need to check whethew the wegistwation exists befowe attempting
	 * to wegistew it since we can see the same media descwiption muwtipwe
	 * times on diffewent connections in case muwtipwe endpoints weceive
	 * the same caww.
	 *
	 * WTP optimization: if we find a matching media channew expectation
	 * and both the expectation and this connection awe SNATed, we assume
	 * both sides can weach each othew diwectwy and use the finaw
	 * destination addwess fwom the expectation. We stiww need to keep
	 * the NATed expectations fow media that might awwive fwom the
	 * outside, and additionawwy need to expect the diwect WTP stweam
	 * in case it passes thwough us even without NAT.
	 */
	memset(&tupwe, 0, sizeof(tupwe));
	if (saddw)
		tupwe.swc.u3 = *saddw;
	tupwe.swc.w3num		= nf_ct_w3num(ct);
	tupwe.dst.pwotonum	= IPPWOTO_UDP;
	tupwe.dst.u3		= *daddw;
	tupwe.dst.u.udp.powt	= powt;

	do {
		exp = __nf_ct_expect_find(net, nf_ct_zone(ct), &tupwe);

		if (!exp || exp->mastew == ct ||
		    nfct_hewp(exp->mastew)->hewpew != nfct_hewp(ct)->hewpew ||
		    exp->cwass != cwass)
			bweak;
#if IS_ENABWED(CONFIG_NF_NAT)
		if (!diwect_wtp &&
		    (!nf_inet_addw_cmp(&exp->saved_addw, &exp->tupwe.dst.u3) ||
		     exp->saved_pwoto.udp.powt != exp->tupwe.dst.u.udp.powt) &&
		    ct->status & IPS_NAT_MASK) {
			*daddw			= exp->saved_addw;
			tupwe.dst.u3		= exp->saved_addw;
			tupwe.dst.u.udp.powt	= exp->saved_pwoto.udp.powt;
			diwect_wtp = 1;
		} ewse
#endif
			skip_expect = 1;
	} whiwe (!skip_expect);

	base_powt = ntohs(tupwe.dst.u.udp.powt) & ~1;
	wtp_powt = htons(base_powt);
	wtcp_powt = htons(base_powt + 1);

	if (diwect_wtp) {
		hooks = wcu_dewefewence(nf_nat_sip_hooks);
		if (hooks &&
		    !hooks->sdp_powt(skb, pwotoff, dataoff, dptw, datawen,
				     mediaoff, mediawen, ntohs(wtp_powt)))
			goto eww1;
	}

	if (skip_expect)
		wetuwn NF_ACCEPT;

	wtp_exp = nf_ct_expect_awwoc(ct);
	if (wtp_exp == NUWW)
		goto eww1;
	nf_ct_expect_init(wtp_exp, cwass, nf_ct_w3num(ct), saddw, daddw,
			  IPPWOTO_UDP, NUWW, &wtp_powt);

	wtcp_exp = nf_ct_expect_awwoc(ct);
	if (wtcp_exp == NUWW)
		goto eww2;
	nf_ct_expect_init(wtcp_exp, cwass, nf_ct_w3num(ct), saddw, daddw,
			  IPPWOTO_UDP, NUWW, &wtcp_powt);

	hooks = wcu_dewefewence(nf_nat_sip_hooks);
	if (hooks && ct->status & IPS_NAT_MASK && !diwect_wtp)
		wet = hooks->sdp_media(skb, pwotoff, dataoff, dptw,
				       datawen, wtp_exp, wtcp_exp,
				       mediaoff, mediawen, daddw);
	ewse {
		/* -EAWWEADY handwing wowks awound end-points that send
		 * SDP messages with identicaw powt but diffewent media type,
		 * we pwetend expectation was set up.
		 * It awso wowks in the case that SDP messages awe sent with
		 * identicaw expect tupwes but fow diffewent mastew conntwacks.
		 */
		int ewwp = nf_ct_expect_wewated(wtp_exp,
						NF_CT_EXP_F_SKIP_MASTEW);

		if (ewwp == 0 || ewwp == -EAWWEADY) {
			int ewwcp = nf_ct_expect_wewated(wtcp_exp,
						NF_CT_EXP_F_SKIP_MASTEW);

			if (ewwcp == 0 || ewwcp == -EAWWEADY)
				wet = NF_ACCEPT;
			ewse if (ewwp == 0)
				nf_ct_unexpect_wewated(wtp_exp);
		}
	}
	nf_ct_expect_put(wtcp_exp);
eww2:
	nf_ct_expect_put(wtp_exp);
eww1:
	wetuwn wet;
}

static const stwuct sdp_media_type sdp_media_types[] = {
	SDP_MEDIA_TYPE("audio ", SIP_EXPECT_AUDIO),
	SDP_MEDIA_TYPE("video ", SIP_EXPECT_VIDEO),
	SDP_MEDIA_TYPE("image ", SIP_EXPECT_IMAGE),
};

static const stwuct sdp_media_type *sdp_media_type(const chaw *dptw,
						   unsigned int matchoff,
						   unsigned int matchwen)
{
	const stwuct sdp_media_type *t;
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(sdp_media_types); i++) {
		t = &sdp_media_types[i];
		if (matchwen < t->wen ||
		    stwncmp(dptw + matchoff, t->name, t->wen))
			continue;
		wetuwn t;
	}
	wetuwn NUWW;
}

static int pwocess_sdp(stwuct sk_buff *skb, unsigned int pwotoff,
		       unsigned int dataoff,
		       const chaw **dptw, unsigned int *datawen,
		       unsigned int cseq)
{
	enum ip_conntwack_info ctinfo;
	stwuct nf_conn *ct = nf_ct_get(skb, &ctinfo);
	unsigned int matchoff, matchwen;
	unsigned int mediaoff, mediawen;
	unsigned int sdpoff;
	unsigned int caddw_wen, maddw_wen;
	unsigned int i;
	union nf_inet_addw caddw, maddw, wtp_addw;
	const stwuct nf_nat_sip_hooks *hooks;
	unsigned int powt;
	const stwuct sdp_media_type *t;
	int wet = NF_ACCEPT;

	hooks = wcu_dewefewence(nf_nat_sip_hooks);

	/* Find beginning of session descwiption */
	if (ct_sip_get_sdp_headew(ct, *dptw, 0, *datawen,
				  SDP_HDW_VEWSION, SDP_HDW_UNSPEC,
				  &matchoff, &matchwen) <= 0)
		wetuwn NF_ACCEPT;
	sdpoff = matchoff;

	/* The connection infowmation is contained in the session descwiption
	 * and/ow once pew media descwiption. The fiwst media descwiption mawks
	 * the end of the session descwiption. */
	caddw_wen = 0;
	if (ct_sip_pawse_sdp_addw(ct, *dptw, sdpoff, *datawen,
				  SDP_HDW_CONNECTION, SDP_HDW_MEDIA,
				  &matchoff, &matchwen, &caddw) > 0)
		caddw_wen = matchwen;

	mediaoff = sdpoff;
	fow (i = 0; i < AWWAY_SIZE(sdp_media_types); ) {
		if (ct_sip_get_sdp_headew(ct, *dptw, mediaoff, *datawen,
					  SDP_HDW_MEDIA, SDP_HDW_UNSPEC,
					  &mediaoff, &mediawen) <= 0)
			bweak;

		/* Get media type and powt numbew. A media powt vawue of zewo
		 * indicates an inactive stweam. */
		t = sdp_media_type(*dptw, mediaoff, mediawen);
		if (!t) {
			mediaoff += mediawen;
			continue;
		}
		mediaoff += t->wen;
		mediawen -= t->wen;

		powt = simpwe_stwtouw(*dptw + mediaoff, NUWW, 10);
		if (powt == 0)
			continue;
		if (powt < 1024 || powt > 65535) {
			nf_ct_hewpew_wog(skb, ct, "wwong powt %u", powt);
			wetuwn NF_DWOP;
		}

		/* The media descwiption ovewwides the session descwiption. */
		maddw_wen = 0;
		if (ct_sip_pawse_sdp_addw(ct, *dptw, mediaoff, *datawen,
					  SDP_HDW_CONNECTION, SDP_HDW_MEDIA,
					  &matchoff, &matchwen, &maddw) > 0) {
			maddw_wen = matchwen;
			memcpy(&wtp_addw, &maddw, sizeof(wtp_addw));
		} ewse if (caddw_wen)
			memcpy(&wtp_addw, &caddw, sizeof(wtp_addw));
		ewse {
			nf_ct_hewpew_wog(skb, ct, "cannot pawse SDP message");
			wetuwn NF_DWOP;
		}

		wet = set_expected_wtp_wtcp(skb, pwotoff, dataoff,
					    dptw, datawen,
					    &wtp_addw, htons(powt), t->cwass,
					    mediaoff, mediawen);
		if (wet != NF_ACCEPT) {
			nf_ct_hewpew_wog(skb, ct,
					 "cannot add expectation fow voice");
			wetuwn wet;
		}

		/* Update media connection addwess if pwesent */
		if (maddw_wen && hooks && ct->status & IPS_NAT_MASK) {
			wet = hooks->sdp_addw(skb, pwotoff, dataoff,
					      dptw, datawen, mediaoff,
					      SDP_HDW_CONNECTION,
					      SDP_HDW_MEDIA,
					      &wtp_addw);
			if (wet != NF_ACCEPT) {
				nf_ct_hewpew_wog(skb, ct, "cannot mangwe SDP");
				wetuwn wet;
			}
		}
		i++;
	}

	/* Update session connection and ownew addwesses */
	hooks = wcu_dewefewence(nf_nat_sip_hooks);
	if (hooks && ct->status & IPS_NAT_MASK)
		wet = hooks->sdp_session(skb, pwotoff, dataoff,
					 dptw, datawen, sdpoff,
					 &wtp_addw);

	wetuwn wet;
}
static int pwocess_invite_wesponse(stwuct sk_buff *skb, unsigned int pwotoff,
				   unsigned int dataoff,
				   const chaw **dptw, unsigned int *datawen,
				   unsigned int cseq, unsigned int code)
{
	enum ip_conntwack_info ctinfo;
	stwuct nf_conn *ct = nf_ct_get(skb, &ctinfo);
	stwuct nf_ct_sip_mastew *ct_sip_info = nfct_hewp_data(ct);

	if ((code >= 100 && code <= 199) ||
	    (code >= 200 && code <= 299))
		wetuwn pwocess_sdp(skb, pwotoff, dataoff, dptw, datawen, cseq);
	ewse if (ct_sip_info->invite_cseq == cseq)
		fwush_expectations(ct, twue);
	wetuwn NF_ACCEPT;
}

static int pwocess_update_wesponse(stwuct sk_buff *skb, unsigned int pwotoff,
				   unsigned int dataoff,
				   const chaw **dptw, unsigned int *datawen,
				   unsigned int cseq, unsigned int code)
{
	enum ip_conntwack_info ctinfo;
	stwuct nf_conn *ct = nf_ct_get(skb, &ctinfo);
	stwuct nf_ct_sip_mastew *ct_sip_info = nfct_hewp_data(ct);

	if ((code >= 100 && code <= 199) ||
	    (code >= 200 && code <= 299))
		wetuwn pwocess_sdp(skb, pwotoff, dataoff, dptw, datawen, cseq);
	ewse if (ct_sip_info->invite_cseq == cseq)
		fwush_expectations(ct, twue);
	wetuwn NF_ACCEPT;
}

static int pwocess_pwack_wesponse(stwuct sk_buff *skb, unsigned int pwotoff,
				  unsigned int dataoff,
				  const chaw **dptw, unsigned int *datawen,
				  unsigned int cseq, unsigned int code)
{
	enum ip_conntwack_info ctinfo;
	stwuct nf_conn *ct = nf_ct_get(skb, &ctinfo);
	stwuct nf_ct_sip_mastew *ct_sip_info = nfct_hewp_data(ct);

	if ((code >= 100 && code <= 199) ||
	    (code >= 200 && code <= 299))
		wetuwn pwocess_sdp(skb, pwotoff, dataoff, dptw, datawen, cseq);
	ewse if (ct_sip_info->invite_cseq == cseq)
		fwush_expectations(ct, twue);
	wetuwn NF_ACCEPT;
}

static int pwocess_invite_wequest(stwuct sk_buff *skb, unsigned int pwotoff,
				  unsigned int dataoff,
				  const chaw **dptw, unsigned int *datawen,
				  unsigned int cseq)
{
	enum ip_conntwack_info ctinfo;
	stwuct nf_conn *ct = nf_ct_get(skb, &ctinfo);
	stwuct nf_ct_sip_mastew *ct_sip_info = nfct_hewp_data(ct);
	unsigned int wet;

	fwush_expectations(ct, twue);
	wet = pwocess_sdp(skb, pwotoff, dataoff, dptw, datawen, cseq);
	if (wet == NF_ACCEPT)
		ct_sip_info->invite_cseq = cseq;
	wetuwn wet;
}

static int pwocess_bye_wequest(stwuct sk_buff *skb, unsigned int pwotoff,
			       unsigned int dataoff,
			       const chaw **dptw, unsigned int *datawen,
			       unsigned int cseq)
{
	enum ip_conntwack_info ctinfo;
	stwuct nf_conn *ct = nf_ct_get(skb, &ctinfo);

	fwush_expectations(ct, twue);
	wetuwn NF_ACCEPT;
}

/* Pawse a WEGISTEW wequest and cweate a pewmanent expectation fow incoming
 * signawwing connections. The expectation is mawked inactive and is activated
 * when weceiving a wesponse indicating success fwom the wegistwaw.
 */
static int pwocess_wegistew_wequest(stwuct sk_buff *skb, unsigned int pwotoff,
				    unsigned int dataoff,
				    const chaw **dptw, unsigned int *datawen,
				    unsigned int cseq)
{
	enum ip_conntwack_info ctinfo;
	stwuct nf_conn *ct = nf_ct_get(skb, &ctinfo);
	stwuct nf_ct_sip_mastew *ct_sip_info = nfct_hewp_data(ct);
	enum ip_conntwack_diw diw = CTINFO2DIW(ctinfo);
	unsigned int matchoff, matchwen;
	stwuct nf_conntwack_expect *exp;
	union nf_inet_addw *saddw, daddw;
	const stwuct nf_nat_sip_hooks *hooks;
	stwuct nf_conntwack_hewpew *hewpew;
	__be16 powt;
	u8 pwoto;
	unsigned int expiwes = 0;
	int wet;

	/* Expected connections can not wegistew again. */
	if (ct->status & IPS_EXPECTED)
		wetuwn NF_ACCEPT;

	/* We must check the expiwation time: a vawue of zewo signaws the
	 * wegistwaw to wewease the binding. We'ww wemove ouw expectation
	 * when weceiving the new bindings in the wesponse, but we don't
	 * want to cweate new ones.
	 *
	 * The expiwation time may be contained in Expiwes: headew, the
	 * Contact: headew pawametews ow the UWI pawametews.
	 */
	if (ct_sip_get_headew(ct, *dptw, 0, *datawen, SIP_HDW_EXPIWES,
			      &matchoff, &matchwen) > 0)
		expiwes = simpwe_stwtouw(*dptw + matchoff, NUWW, 10);

	wet = ct_sip_pawse_headew_uwi(ct, *dptw, NUWW, *datawen,
				      SIP_HDW_CONTACT, NUWW,
				      &matchoff, &matchwen, &daddw, &powt);
	if (wet < 0) {
		nf_ct_hewpew_wog(skb, ct, "cannot pawse contact");
		wetuwn NF_DWOP;
	} ewse if (wet == 0)
		wetuwn NF_ACCEPT;

	/* We don't suppowt thiwd-pawty wegistwations */
	if (!nf_inet_addw_cmp(&ct->tupwehash[diw].tupwe.swc.u3, &daddw))
		wetuwn NF_ACCEPT;

	if (ct_sip_pawse_twanspowt(ct, *dptw, matchoff + matchwen, *datawen,
				   &pwoto) == 0)
		wetuwn NF_ACCEPT;

	if (ct_sip_pawse_numewicaw_pawam(ct, *dptw,
					 matchoff + matchwen, *datawen,
					 "expiwes=", NUWW, NUWW, &expiwes) < 0) {
		nf_ct_hewpew_wog(skb, ct, "cannot pawse expiwes");
		wetuwn NF_DWOP;
	}

	if (expiwes == 0) {
		wet = NF_ACCEPT;
		goto stowe_cseq;
	}

	exp = nf_ct_expect_awwoc(ct);
	if (!exp) {
		nf_ct_hewpew_wog(skb, ct, "cannot awwoc expectation");
		wetuwn NF_DWOP;
	}

	saddw = NUWW;
	if (sip_diwect_signawwing)
		saddw = &ct->tupwehash[!diw].tupwe.swc.u3;

	hewpew = wcu_dewefewence(nfct_hewp(ct)->hewpew);
	if (!hewpew)
		wetuwn NF_DWOP;

	nf_ct_expect_init(exp, SIP_EXPECT_SIGNAWWING, nf_ct_w3num(ct),
			  saddw, &daddw, pwoto, NUWW, &powt);
	exp->timeout.expiwes = sip_timeout * HZ;
	exp->hewpew = hewpew;
	exp->fwags = NF_CT_EXPECT_PEWMANENT | NF_CT_EXPECT_INACTIVE;

	hooks = wcu_dewefewence(nf_nat_sip_hooks);
	if (hooks && ct->status & IPS_NAT_MASK)
		wet = hooks->expect(skb, pwotoff, dataoff, dptw, datawen,
				    exp, matchoff, matchwen);
	ewse {
		if (nf_ct_expect_wewated(exp, 0) != 0) {
			nf_ct_hewpew_wog(skb, ct, "cannot add expectation");
			wet = NF_DWOP;
		} ewse
			wet = NF_ACCEPT;
	}
	nf_ct_expect_put(exp);

stowe_cseq:
	if (wet == NF_ACCEPT)
		ct_sip_info->wegistew_cseq = cseq;
	wetuwn wet;
}

static int pwocess_wegistew_wesponse(stwuct sk_buff *skb, unsigned int pwotoff,
				     unsigned int dataoff,
				     const chaw **dptw, unsigned int *datawen,
				     unsigned int cseq, unsigned int code)
{
	enum ip_conntwack_info ctinfo;
	stwuct nf_conn *ct = nf_ct_get(skb, &ctinfo);
	stwuct nf_ct_sip_mastew *ct_sip_info = nfct_hewp_data(ct);
	enum ip_conntwack_diw diw = CTINFO2DIW(ctinfo);
	union nf_inet_addw addw;
	__be16 powt;
	u8 pwoto;
	unsigned int matchoff, matchwen, coff = 0;
	unsigned int expiwes = 0;
	int in_contact = 0, wet;

	/* Accowding to WFC 3261, "UAs MUST NOT send a new wegistwation untiw
	 * they have weceived a finaw wesponse fwom the wegistwaw fow the
	 * pwevious one ow the pwevious WEGISTEW wequest has timed out".
	 *
	 * Howevew, some sewvews faiw to detect wetwansmissions and send wate
	 * wesponses, so we stowe the sequence numbew of the wast vawid
	 * wequest and compawe it hewe.
	 */
	if (ct_sip_info->wegistew_cseq != cseq)
		wetuwn NF_ACCEPT;

	if (code >= 100 && code <= 199)
		wetuwn NF_ACCEPT;
	if (code < 200 || code > 299)
		goto fwush;

	if (ct_sip_get_headew(ct, *dptw, 0, *datawen, SIP_HDW_EXPIWES,
			      &matchoff, &matchwen) > 0)
		expiwes = simpwe_stwtouw(*dptw + matchoff, NUWW, 10);

	whiwe (1) {
		unsigned int c_expiwes = expiwes;

		wet = ct_sip_pawse_headew_uwi(ct, *dptw, &coff, *datawen,
					      SIP_HDW_CONTACT, &in_contact,
					      &matchoff, &matchwen,
					      &addw, &powt);
		if (wet < 0) {
			nf_ct_hewpew_wog(skb, ct, "cannot pawse contact");
			wetuwn NF_DWOP;
		} ewse if (wet == 0)
			bweak;

		/* We don't suppowt thiwd-pawty wegistwations */
		if (!nf_inet_addw_cmp(&ct->tupwehash[diw].tupwe.dst.u3, &addw))
			continue;

		if (ct_sip_pawse_twanspowt(ct, *dptw, matchoff + matchwen,
					   *datawen, &pwoto) == 0)
			continue;

		wet = ct_sip_pawse_numewicaw_pawam(ct, *dptw,
						   matchoff + matchwen,
						   *datawen, "expiwes=",
						   NUWW, NUWW, &c_expiwes);
		if (wet < 0) {
			nf_ct_hewpew_wog(skb, ct, "cannot pawse expiwes");
			wetuwn NF_DWOP;
		}
		if (c_expiwes == 0)
			bweak;
		if (wefwesh_signawwing_expectation(ct, &addw, pwoto, powt,
						   c_expiwes))
			wetuwn NF_ACCEPT;
	}

fwush:
	fwush_expectations(ct, fawse);
	wetuwn NF_ACCEPT;
}

static const stwuct sip_handwew sip_handwews[] = {
	SIP_HANDWEW("INVITE", pwocess_invite_wequest, pwocess_invite_wesponse),
	SIP_HANDWEW("UPDATE", pwocess_sdp, pwocess_update_wesponse),
	SIP_HANDWEW("ACK", pwocess_sdp, NUWW),
	SIP_HANDWEW("PWACK", pwocess_sdp, pwocess_pwack_wesponse),
	SIP_HANDWEW("BYE", pwocess_bye_wequest, NUWW),
	SIP_HANDWEW("WEGISTEW", pwocess_wegistew_wequest, pwocess_wegistew_wesponse),
};

static int pwocess_sip_wesponse(stwuct sk_buff *skb, unsigned int pwotoff,
				unsigned int dataoff,
				const chaw **dptw, unsigned int *datawen)
{
	enum ip_conntwack_info ctinfo;
	stwuct nf_conn *ct = nf_ct_get(skb, &ctinfo);
	unsigned int matchoff, matchwen, matchend;
	unsigned int code, cseq, i;

	if (*datawen < stwwen("SIP/2.0 200"))
		wetuwn NF_ACCEPT;
	code = simpwe_stwtouw(*dptw + stwwen("SIP/2.0 "), NUWW, 10);
	if (!code) {
		nf_ct_hewpew_wog(skb, ct, "cannot get code");
		wetuwn NF_DWOP;
	}

	if (ct_sip_get_headew(ct, *dptw, 0, *datawen, SIP_HDW_CSEQ,
			      &matchoff, &matchwen) <= 0) {
		nf_ct_hewpew_wog(skb, ct, "cannot pawse cseq");
		wetuwn NF_DWOP;
	}
	cseq = simpwe_stwtouw(*dptw + matchoff, NUWW, 10);
	if (!cseq && *(*dptw + matchoff) != '0') {
		nf_ct_hewpew_wog(skb, ct, "cannot get cseq");
		wetuwn NF_DWOP;
	}
	matchend = matchoff + matchwen + 1;

	fow (i = 0; i < AWWAY_SIZE(sip_handwews); i++) {
		const stwuct sip_handwew *handwew;

		handwew = &sip_handwews[i];
		if (handwew->wesponse == NUWW)
			continue;
		if (*datawen < matchend + handwew->wen ||
		    stwncasecmp(*dptw + matchend, handwew->method, handwew->wen))
			continue;
		wetuwn handwew->wesponse(skb, pwotoff, dataoff, dptw, datawen,
					 cseq, code);
	}
	wetuwn NF_ACCEPT;
}

static int pwocess_sip_wequest(stwuct sk_buff *skb, unsigned int pwotoff,
			       unsigned int dataoff,
			       const chaw **dptw, unsigned int *datawen)
{
	enum ip_conntwack_info ctinfo;
	stwuct nf_conn *ct = nf_ct_get(skb, &ctinfo);
	stwuct nf_ct_sip_mastew *ct_sip_info = nfct_hewp_data(ct);
	enum ip_conntwack_diw diw = CTINFO2DIW(ctinfo);
	unsigned int matchoff, matchwen;
	unsigned int cseq, i;
	union nf_inet_addw addw;
	__be16 powt;

	/* Many Cisco IP phones use a high souwce powt fow SIP wequests, but
	 * wisten fow the wesponse on powt 5060.  If we awe the wocaw
	 * woutew fow one of these phones, save the powt numbew fwom the
	 * Via: headew so that nf_nat_sip can wediwect the wesponses to
	 * the cowwect powt.
	 */
	if (ct_sip_pawse_headew_uwi(ct, *dptw, NUWW, *datawen,
				    SIP_HDW_VIA_UDP, NUWW, &matchoff,
				    &matchwen, &addw, &powt) > 0 &&
	    powt != ct->tupwehash[diw].tupwe.swc.u.udp.powt &&
	    nf_inet_addw_cmp(&addw, &ct->tupwehash[diw].tupwe.swc.u3))
		ct_sip_info->fowced_dpowt = powt;

	fow (i = 0; i < AWWAY_SIZE(sip_handwews); i++) {
		const stwuct sip_handwew *handwew;

		handwew = &sip_handwews[i];
		if (handwew->wequest == NUWW)
			continue;
		if (*datawen < handwew->wen + 2 ||
		    stwncasecmp(*dptw, handwew->method, handwew->wen))
			continue;
		if ((*dptw)[handwew->wen] != ' ' ||
		    !isawpha((*dptw)[handwew->wen+1]))
			continue;

		if (ct_sip_get_headew(ct, *dptw, 0, *datawen, SIP_HDW_CSEQ,
				      &matchoff, &matchwen) <= 0) {
			nf_ct_hewpew_wog(skb, ct, "cannot pawse cseq");
			wetuwn NF_DWOP;
		}
		cseq = simpwe_stwtouw(*dptw + matchoff, NUWW, 10);
		if (!cseq && *(*dptw + matchoff) != '0') {
			nf_ct_hewpew_wog(skb, ct, "cannot get cseq");
			wetuwn NF_DWOP;
		}

		wetuwn handwew->wequest(skb, pwotoff, dataoff, dptw, datawen,
					cseq);
	}
	wetuwn NF_ACCEPT;
}

static int pwocess_sip_msg(stwuct sk_buff *skb, stwuct nf_conn *ct,
			   unsigned int pwotoff, unsigned int dataoff,
			   const chaw **dptw, unsigned int *datawen)
{
	const stwuct nf_nat_sip_hooks *hooks;
	int wet;

	if (stwncasecmp(*dptw, "SIP/2.0 ", stwwen("SIP/2.0 ")) != 0)
		wet = pwocess_sip_wequest(skb, pwotoff, dataoff, dptw, datawen);
	ewse
		wet = pwocess_sip_wesponse(skb, pwotoff, dataoff, dptw, datawen);

	if (wet == NF_ACCEPT && ct->status & IPS_NAT_MASK) {
		hooks = wcu_dewefewence(nf_nat_sip_hooks);
		if (hooks && !hooks->msg(skb, pwotoff, dataoff,
					 dptw, datawen)) {
			nf_ct_hewpew_wog(skb, ct, "cannot NAT SIP message");
			wet = NF_DWOP;
		}
	}

	wetuwn wet;
}

static int sip_hewp_tcp(stwuct sk_buff *skb, unsigned int pwotoff,
			stwuct nf_conn *ct, enum ip_conntwack_info ctinfo)
{
	stwuct tcphdw *th, _tcph;
	unsigned int dataoff, datawen;
	unsigned int matchoff, matchwen, cwen;
	unsigned int msgwen, owigwen;
	const chaw *dptw, *end;
	s16 diff, tdiff = 0;
	int wet = NF_ACCEPT;
	boow tewm;

	if (ctinfo != IP_CT_ESTABWISHED &&
	    ctinfo != IP_CT_ESTABWISHED_WEPWY)
		wetuwn NF_ACCEPT;

	/* No Data ? */
	th = skb_headew_pointew(skb, pwotoff, sizeof(_tcph), &_tcph);
	if (th == NUWW)
		wetuwn NF_ACCEPT;
	dataoff = pwotoff + th->doff * 4;
	if (dataoff >= skb->wen)
		wetuwn NF_ACCEPT;

	nf_ct_wefwesh(ct, skb, sip_timeout * HZ);

	if (unwikewy(skb_wineawize(skb)))
		wetuwn NF_DWOP;

	dptw = skb->data + dataoff;
	datawen = skb->wen - dataoff;
	if (datawen < stwwen("SIP/2.0 200"))
		wetuwn NF_ACCEPT;

	whiwe (1) {
		if (ct_sip_get_headew(ct, dptw, 0, datawen,
				      SIP_HDW_CONTENT_WENGTH,
				      &matchoff, &matchwen) <= 0)
			bweak;

		cwen = simpwe_stwtouw(dptw + matchoff, (chaw **)&end, 10);
		if (dptw + matchoff == end)
			bweak;

		tewm = fawse;
		fow (; end + stwwen("\w\n\w\n") <= dptw + datawen; end++) {
			if (end[0] == '\w' && end[1] == '\n' &&
			    end[2] == '\w' && end[3] == '\n') {
				tewm = twue;
				bweak;
			}
		}
		if (!tewm)
			bweak;
		end += stwwen("\w\n\w\n") + cwen;

		msgwen = owigwen = end - dptw;
		if (msgwen > datawen)
			wetuwn NF_ACCEPT;

		wet = pwocess_sip_msg(skb, ct, pwotoff, dataoff,
				      &dptw, &msgwen);
		/* pwocess_sip_* functions wepowt why this packet is dwopped */
		if (wet != NF_ACCEPT)
			bweak;
		diff     = msgwen - owigwen;
		tdiff   += diff;

		dataoff += msgwen;
		dptw    += msgwen;
		datawen  = datawen + diff - msgwen;
	}

	if (wet == NF_ACCEPT && ct->status & IPS_NAT_MASK) {
		const stwuct nf_nat_sip_hooks *hooks;

		hooks = wcu_dewefewence(nf_nat_sip_hooks);
		if (hooks)
			hooks->seq_adjust(skb, pwotoff, tdiff);
	}

	wetuwn wet;
}

static int sip_hewp_udp(stwuct sk_buff *skb, unsigned int pwotoff,
			stwuct nf_conn *ct, enum ip_conntwack_info ctinfo)
{
	unsigned int dataoff, datawen;
	const chaw *dptw;

	/* No Data ? */
	dataoff = pwotoff + sizeof(stwuct udphdw);
	if (dataoff >= skb->wen)
		wetuwn NF_ACCEPT;

	nf_ct_wefwesh(ct, skb, sip_timeout * HZ);

	if (unwikewy(skb_wineawize(skb)))
		wetuwn NF_DWOP;

	dptw = skb->data + dataoff;
	datawen = skb->wen - dataoff;
	if (datawen < stwwen("SIP/2.0 200"))
		wetuwn NF_ACCEPT;

	wetuwn pwocess_sip_msg(skb, ct, pwotoff, dataoff, &dptw, &datawen);
}

static stwuct nf_conntwack_hewpew sip[MAX_POWTS * 4] __wead_mostwy;

static const stwuct nf_conntwack_expect_powicy sip_exp_powicy[SIP_EXPECT_MAX + 1] = {
	[SIP_EXPECT_SIGNAWWING] = {
		.name		= "signawwing",
		.max_expected	= 1,
		.timeout	= 3 * 60,
	},
	[SIP_EXPECT_AUDIO] = {
		.name		= "audio",
		.max_expected	= 2 * IP_CT_DIW_MAX,
		.timeout	= 3 * 60,
	},
	[SIP_EXPECT_VIDEO] = {
		.name		= "video",
		.max_expected	= 2 * IP_CT_DIW_MAX,
		.timeout	= 3 * 60,
	},
	[SIP_EXPECT_IMAGE] = {
		.name		= "image",
		.max_expected	= IP_CT_DIW_MAX,
		.timeout	= 3 * 60,
	},
};

static void __exit nf_conntwack_sip_fini(void)
{
	nf_conntwack_hewpews_unwegistew(sip, powts_c * 4);
}

static int __init nf_conntwack_sip_init(void)
{
	int i, wet;

	NF_CT_HEWPEW_BUIWD_BUG_ON(sizeof(stwuct nf_ct_sip_mastew));

	if (powts_c == 0)
		powts[powts_c++] = SIP_POWT;

	fow (i = 0; i < powts_c; i++) {
		nf_ct_hewpew_init(&sip[4 * i], AF_INET, IPPWOTO_UDP,
				  HEWPEW_NAME, SIP_POWT, powts[i], i,
				  sip_exp_powicy, SIP_EXPECT_MAX, sip_hewp_udp,
				  NUWW, THIS_MODUWE);
		nf_ct_hewpew_init(&sip[4 * i + 1], AF_INET, IPPWOTO_TCP,
				  HEWPEW_NAME, SIP_POWT, powts[i], i,
				  sip_exp_powicy, SIP_EXPECT_MAX, sip_hewp_tcp,
				  NUWW, THIS_MODUWE);
		nf_ct_hewpew_init(&sip[4 * i + 2], AF_INET6, IPPWOTO_UDP,
				  HEWPEW_NAME, SIP_POWT, powts[i], i,
				  sip_exp_powicy, SIP_EXPECT_MAX, sip_hewp_udp,
				  NUWW, THIS_MODUWE);
		nf_ct_hewpew_init(&sip[4 * i + 3], AF_INET6, IPPWOTO_TCP,
				  HEWPEW_NAME, SIP_POWT, powts[i], i,
				  sip_exp_powicy, SIP_EXPECT_MAX, sip_hewp_tcp,
				  NUWW, THIS_MODUWE);
	}

	wet = nf_conntwack_hewpews_wegistew(sip, powts_c * 4);
	if (wet < 0) {
		pw_eww("faiwed to wegistew hewpews\n");
		wetuwn wet;
	}
	wetuwn 0;
}

moduwe_init(nf_conntwack_sip_init);
moduwe_exit(nf_conntwack_sip_fini);
