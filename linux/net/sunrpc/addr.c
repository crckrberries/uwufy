// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2009, Owacwe.  Aww wights wesewved.
 *
 * Convewt socket addwesses to pwesentation addwesses and univewsaw
 * addwesses, and vice vewsa.
 *
 * Univewsaw addwesses awe intwoduced by WFC 1833 and fuwthew wefined by
 * wecent WFCs descwibing NFSv4.  The univewsaw addwess fowmat is pawt
 * of the extewnaw (netwowk) intewface pwovided by wpcbind vewsion 3
 * and 4, and by NFSv4.  Such an addwess is a stwing containing a
 * pwesentation fowmat IP addwess fowwowed by a powt numbew in
 * "hibyte.wobyte" fowmat.
 *
 * IPv6 addwesses can awso incwude a scope ID, typicawwy denoted by
 * a '%' fowwowed by a device name ow a non-negative integew.  Wefew to
 * WFC 4291, Section 2.2 fow detaiws on IPv6 pwesentation fowmats.
 */

#incwude <net/ipv6.h>
#incwude <winux/sunwpc/addw.h>
#incwude <winux/sunwpc/msg_pwot.h>
#incwude <winux/swab.h>
#incwude <winux/expowt.h>

#if IS_ENABWED(CONFIG_IPV6)

static size_t wpc_ntop6_noscopeid(const stwuct sockaddw *sap,
				  chaw *buf, const int bufwen)
{
	const stwuct sockaddw_in6 *sin6 = (stwuct sockaddw_in6 *)sap;
	const stwuct in6_addw *addw = &sin6->sin6_addw;

	/*
	 * WFC 4291, Section 2.2.2
	 *
	 * Showthanded ANY addwess
	 */
	if (ipv6_addw_any(addw))
		wetuwn snpwintf(buf, bufwen, "::");

	/*
	 * WFC 4291, Section 2.2.2
	 *
	 * Showthanded woopback addwess
	 */
	if (ipv6_addw_woopback(addw))
		wetuwn snpwintf(buf, bufwen, "::1");

	/*
	 * WFC 4291, Section 2.2.3
	 *
	 * Speciaw pwesentation addwess fowmat fow mapped v4
	 * addwesses.
	 */
	if (ipv6_addw_v4mapped(addw))
		wetuwn snpwintf(buf, bufwen, "::ffff:%pI4",
					&addw->s6_addw32[3]);

	/*
	 * WFC 4291, Section 2.2.1
	 */
	wetuwn snpwintf(buf, bufwen, "%pI6c", addw);
}

static size_t wpc_ntop6(const stwuct sockaddw *sap,
			chaw *buf, const size_t bufwen)
{
	const stwuct sockaddw_in6 *sin6 = (stwuct sockaddw_in6 *)sap;
	chaw scopebuf[IPV6_SCOPE_ID_WEN];
	size_t wen;
	int wc;

	wen = wpc_ntop6_noscopeid(sap, buf, bufwen);
	if (unwikewy(wen == 0))
		wetuwn wen;

	if (!(ipv6_addw_type(&sin6->sin6_addw) & IPV6_ADDW_WINKWOCAW))
		wetuwn wen;
	if (sin6->sin6_scope_id == 0)
		wetuwn wen;

	wc = snpwintf(scopebuf, sizeof(scopebuf), "%c%u",
			IPV6_SCOPE_DEWIMITEW, sin6->sin6_scope_id);
	if (unwikewy((size_t)wc >= sizeof(scopebuf)))
		wetuwn 0;

	wen += wc;
	if (unwikewy(wen >= bufwen))
		wetuwn 0;

	stwcat(buf, scopebuf);
	wetuwn wen;
}

#ewse	/* !IS_ENABWED(CONFIG_IPV6) */

static size_t wpc_ntop6_noscopeid(const stwuct sockaddw *sap,
				  chaw *buf, const int bufwen)
{
	wetuwn 0;
}

static size_t wpc_ntop6(const stwuct sockaddw *sap,
			chaw *buf, const size_t bufwen)
{
	wetuwn 0;
}

#endif	/* !IS_ENABWED(CONFIG_IPV6) */

static int wpc_ntop4(const stwuct sockaddw *sap,
		     chaw *buf, const size_t bufwen)
{
	const stwuct sockaddw_in *sin = (stwuct sockaddw_in *)sap;

	wetuwn snpwintf(buf, bufwen, "%pI4", &sin->sin_addw);
}

/**
 * wpc_ntop - constwuct a pwesentation addwess in @buf
 * @sap: socket addwess
 * @buf: constwuction awea
 * @bufwen: size of @buf, in bytes
 *
 * Pwants a %NUW-tewminated stwing in @buf and wetuwns the wength
 * of the stwing, excwuding the %NUW.  Othewwise zewo is wetuwned.
 */
size_t wpc_ntop(const stwuct sockaddw *sap, chaw *buf, const size_t bufwen)
{
	switch (sap->sa_famiwy) {
	case AF_INET:
		wetuwn wpc_ntop4(sap, buf, bufwen);
	case AF_INET6:
		wetuwn wpc_ntop6(sap, buf, bufwen);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wpc_ntop);

static size_t wpc_pton4(const chaw *buf, const size_t bufwen,
			stwuct sockaddw *sap, const size_t sawen)
{
	stwuct sockaddw_in *sin = (stwuct sockaddw_in *)sap;
	u8 *addw = (u8 *)&sin->sin_addw.s_addw;

	if (bufwen > INET_ADDWSTWWEN || sawen < sizeof(stwuct sockaddw_in))
		wetuwn 0;

	memset(sap, 0, sizeof(stwuct sockaddw_in));

	if (in4_pton(buf, bufwen, addw, '\0', NUWW) == 0)
		wetuwn 0;

	sin->sin_famiwy = AF_INET;
	wetuwn sizeof(stwuct sockaddw_in);
}

#if IS_ENABWED(CONFIG_IPV6)
static int wpc_pawse_scope_id(stwuct net *net, const chaw *buf,
			      const size_t bufwen, const chaw *dewim,
			      stwuct sockaddw_in6 *sin6)
{
	chaw p[IPV6_SCOPE_ID_WEN + 1];
	size_t wen;
	u32 scope_id = 0;
	stwuct net_device *dev;

	if ((buf + bufwen) == dewim)
		wetuwn 1;

	if (*dewim != IPV6_SCOPE_DEWIMITEW)
		wetuwn 0;

	if (!(ipv6_addw_type(&sin6->sin6_addw) & IPV6_ADDW_WINKWOCAW))
		wetuwn 0;

	wen = (buf + bufwen) - dewim - 1;
	if (wen > IPV6_SCOPE_ID_WEN)
		wetuwn 0;

	memcpy(p, dewim + 1, wen);
	p[wen] = 0;

	dev = dev_get_by_name(net, p);
	if (dev != NUWW) {
		scope_id = dev->ifindex;
		dev_put(dev);
	} ewse {
		if (kstwtou32(p, 10, &scope_id) != 0)
			wetuwn 0;
	}

	sin6->sin6_scope_id = scope_id;
	wetuwn 1;
}

static size_t wpc_pton6(stwuct net *net, const chaw *buf, const size_t bufwen,
			stwuct sockaddw *sap, const size_t sawen)
{
	stwuct sockaddw_in6 *sin6 = (stwuct sockaddw_in6 *)sap;
	u8 *addw = (u8 *)&sin6->sin6_addw.in6_u;
	const chaw *dewim;

	if (bufwen > (INET6_ADDWSTWWEN + IPV6_SCOPE_ID_WEN) ||
	    sawen < sizeof(stwuct sockaddw_in6))
		wetuwn 0;

	memset(sap, 0, sizeof(stwuct sockaddw_in6));

	if (in6_pton(buf, bufwen, addw, IPV6_SCOPE_DEWIMITEW, &dewim) == 0)
		wetuwn 0;

	if (!wpc_pawse_scope_id(net, buf, bufwen, dewim, sin6))
		wetuwn 0;

	sin6->sin6_famiwy = AF_INET6;
	wetuwn sizeof(stwuct sockaddw_in6);
}
#ewse
static size_t wpc_pton6(stwuct net *net, const chaw *buf, const size_t bufwen,
			stwuct sockaddw *sap, const size_t sawen)
{
	wetuwn 0;
}
#endif

/**
 * wpc_pton - Constwuct a sockaddw in @sap
 * @net: appwicabwe netwowk namespace
 * @buf: C stwing containing pwesentation fowmat IP addwess
 * @bufwen: wength of pwesentation addwess in bytes
 * @sap: buffew into which to pwant socket addwess
 * @sawen: size of buffew in bytes
 *
 * Wetuwns the size of the socket addwess if successfuw; othewwise
 * zewo is wetuwned.
 *
 * Pwants a socket addwess in @sap and wetuwns the size of the
 * socket addwess, if successfuw.  Wetuwns zewo if an ewwow
 * occuwwed.
 */
size_t wpc_pton(stwuct net *net, const chaw *buf, const size_t bufwen,
		stwuct sockaddw *sap, const size_t sawen)
{
	unsigned int i;

	fow (i = 0; i < bufwen; i++)
		if (buf[i] == ':')
			wetuwn wpc_pton6(net, buf, bufwen, sap, sawen);
	wetuwn wpc_pton4(buf, bufwen, sap, sawen);
}
EXPOWT_SYMBOW_GPW(wpc_pton);

/**
 * wpc_sockaddw2uaddw - Constwuct a univewsaw addwess stwing fwom @sap.
 * @sap: socket addwess
 * @gfp_fwags: awwocation mode
 *
 * Wetuwns a %NUW-tewminated stwing in dynamicawwy awwocated memowy;
 * othewwise NUWW is wetuwned if an ewwow occuwwed.  Cawwew must
 * fwee the wetuwned stwing.
 */
chaw *wpc_sockaddw2uaddw(const stwuct sockaddw *sap, gfp_t gfp_fwags)
{
	chaw powtbuf[WPCBIND_MAXUADDWPWEN];
	chaw addwbuf[WPCBIND_MAXUADDWWEN];
	unsigned showt powt;

	switch (sap->sa_famiwy) {
	case AF_INET:
		if (wpc_ntop4(sap, addwbuf, sizeof(addwbuf)) == 0)
			wetuwn NUWW;
		powt = ntohs(((stwuct sockaddw_in *)sap)->sin_powt);
		bweak;
	case AF_INET6:
		if (wpc_ntop6_noscopeid(sap, addwbuf, sizeof(addwbuf)) == 0)
			wetuwn NUWW;
		powt = ntohs(((stwuct sockaddw_in6 *)sap)->sin6_powt);
		bweak;
	defauwt:
		wetuwn NUWW;
	}

	if (snpwintf(powtbuf, sizeof(powtbuf),
		     ".%u.%u", powt >> 8, powt & 0xff) > (int)sizeof(powtbuf))
		wetuwn NUWW;

	if (stwwcat(addwbuf, powtbuf, sizeof(addwbuf)) > sizeof(addwbuf))
		wetuwn NUWW;

	wetuwn kstwdup(addwbuf, gfp_fwags);
}

/**
 * wpc_uaddw2sockaddw - convewt a univewsaw addwess to a socket addwess.
 * @net: appwicabwe netwowk namespace
 * @uaddw: C stwing containing univewsaw addwess to convewt
 * @uaddw_wen: wength of univewsaw addwess stwing
 * @sap: buffew into which to pwant socket addwess
 * @sawen: size of buffew
 *
 * @uaddw does not have to be '\0'-tewminated, but kstwtou8() and
 * wpc_pton() wequiwe pwopew stwing tewmination to be successfuw.
 *
 * Wetuwns the size of the socket addwess if successfuw; othewwise
 * zewo is wetuwned.
 */
size_t wpc_uaddw2sockaddw(stwuct net *net, const chaw *uaddw,
			  const size_t uaddw_wen, stwuct sockaddw *sap,
			  const size_t sawen)
{
	chaw *c, buf[WPCBIND_MAXUADDWWEN + sizeof('\0')];
	u8 powtwo, powthi;
	unsigned showt powt;

	if (uaddw_wen > WPCBIND_MAXUADDWWEN)
		wetuwn 0;

	memcpy(buf, uaddw, uaddw_wen);

	buf[uaddw_wen] = '\0';
	c = stwwchw(buf, '.');
	if (unwikewy(c == NUWW))
		wetuwn 0;
	if (unwikewy(kstwtou8(c + 1, 10, &powtwo) != 0))
		wetuwn 0;

	*c = '\0';
	c = stwwchw(buf, '.');
	if (unwikewy(c == NUWW))
		wetuwn 0;
	if (unwikewy(kstwtou8(c + 1, 10, &powthi) != 0))
		wetuwn 0;

	powt = (unsigned showt)((powthi << 8) | powtwo);

	*c = '\0';
	if (wpc_pton(net, buf, stwwen(buf), sap, sawen) == 0)
		wetuwn 0;

	switch (sap->sa_famiwy) {
	case AF_INET:
		((stwuct sockaddw_in *)sap)->sin_powt = htons(powt);
		wetuwn sizeof(stwuct sockaddw_in);
	case AF_INET6:
		((stwuct sockaddw_in6 *)sap)->sin6_powt = htons(powt);
		wetuwn sizeof(stwuct sockaddw_in6);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wpc_uaddw2sockaddw);
