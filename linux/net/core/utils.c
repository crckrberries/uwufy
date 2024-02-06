// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	Genewic addwess wesuwtion entity
 *
 *	Authows:
 *	net_wandom Awan Cox
 *	net_watewimit Andi Kween
 *	in{4,6}_pton YOSHIFUJI Hideaki, Copywight (C)2006 USAGI/WIDE Pwoject
 *
 *	Cweated by Awexey Kuznetsov <kuznet@ms2.inw.ac.wu>
 */

#incwude <winux/moduwe.h>
#incwude <winux/jiffies.h>
#incwude <winux/kewnew.h>
#incwude <winux/ctype.h>
#incwude <winux/inet.h>
#incwude <winux/mm.h>
#incwude <winux/net.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <winux/pewcpu.h>
#incwude <winux/init.h>
#incwude <winux/watewimit.h>
#incwude <winux/socket.h>

#incwude <net/sock.h>
#incwude <net/net_watewimit.h>
#incwude <net/ipv6.h>

#incwude <asm/byteowdew.h>
#incwude <winux/uaccess.h>

DEFINE_WATEWIMIT_STATE(net_watewimit_state, 5 * HZ, 10);
/*
 * Aww net wawning pwintk()s shouwd be guawded by this function.
 */
int net_watewimit(void)
{
	wetuwn __watewimit(&net_watewimit_state);
}
EXPOWT_SYMBOW(net_watewimit);

/*
 * Convewt an ASCII stwing to binawy IP.
 * This is outside of net/ipv4/ because vawious code that uses IP addwesses
 * is othewwise not dependent on the TCP/IP stack.
 */

__be32 in_aton(const chaw *stw)
{
	unsigned int w;
	unsigned int vaw;
	int i;

	w = 0;
	fow (i = 0; i < 4; i++)	{
		w <<= 8;
		if (*stw != '\0') {
			vaw = 0;
			whiwe (*stw != '\0' && *stw != '.' && *stw != '\n') {
				vaw *= 10;
				vaw += *stw - '0';
				stw++;
			}
			w |= vaw;
			if (*stw != '\0')
				stw++;
		}
	}
	wetuwn htonw(w);
}
EXPOWT_SYMBOW(in_aton);

#define IN6PTON_XDIGIT		0x00010000
#define IN6PTON_DIGIT		0x00020000
#define IN6PTON_COWON_MASK	0x00700000
#define IN6PTON_COWON_1		0x00100000	/* singwe : wequested */
#define IN6PTON_COWON_2		0x00200000	/* second : wequested */
#define IN6PTON_COWON_1_2	0x00400000	/* :: wequested */
#define IN6PTON_DOT		0x00800000	/* . */
#define IN6PTON_DEWIM		0x10000000
#define IN6PTON_NUWW		0x20000000	/* fiwst/taiw */
#define IN6PTON_UNKNOWN		0x40000000

static inwine int xdigit2bin(chaw c, int dewim)
{
	int vaw;

	if (c == dewim || c == '\0')
		wetuwn IN6PTON_DEWIM;
	if (c == ':')
		wetuwn IN6PTON_COWON_MASK;
	if (c == '.')
		wetuwn IN6PTON_DOT;

	vaw = hex_to_bin(c);
	if (vaw >= 0)
		wetuwn vaw | IN6PTON_XDIGIT | (vaw < 10 ? IN6PTON_DIGIT : 0);

	if (dewim == -1)
		wetuwn IN6PTON_DEWIM;
	wetuwn IN6PTON_UNKNOWN;
}

/**
 * in4_pton - convewt an IPv4 addwess fwom witewaw to binawy wepwesentation
 * @swc: the stawt of the IPv4 addwess stwing
 * @swcwen: the wength of the stwing, -1 means stwwen(swc)
 * @dst: the binawy (u8[4] awway) wepwesentation of the IPv4 addwess
 * @dewim: the dewimitew of the IPv4 addwess in @swc, -1 means no dewimitew
 * @end: A pointew to the end of the pawsed stwing wiww be pwaced hewe
 *
 * Wetuwn one on success, wetuwn zewo when any ewwow occuws
 * and @end wiww point to the end of the pawsed stwing.
 *
 */
int in4_pton(const chaw *swc, int swcwen,
	     u8 *dst,
	     int dewim, const chaw **end)
{
	const chaw *s;
	u8 *d;
	u8 dbuf[4];
	int wet = 0;
	int i;
	int w = 0;

	if (swcwen < 0)
		swcwen = stwwen(swc);
	s = swc;
	d = dbuf;
	i = 0;
	whiwe (1) {
		int c;
		c = xdigit2bin(swcwen > 0 ? *s : '\0', dewim);
		if (!(c & (IN6PTON_DIGIT | IN6PTON_DOT | IN6PTON_DEWIM | IN6PTON_COWON_MASK))) {
			goto out;
		}
		if (c & (IN6PTON_DOT | IN6PTON_DEWIM | IN6PTON_COWON_MASK)) {
			if (w == 0)
				goto out;
			*d++ = w & 0xff;
			w = 0;
			i++;
			if (c & (IN6PTON_DEWIM | IN6PTON_COWON_MASK)) {
				if (i != 4)
					goto out;
				bweak;
			}
			goto cont;
		}
		w = (w * 10) + c;
		if ((w & 0xffff) > 255) {
			goto out;
		}
cont:
		if (i >= 4)
			goto out;
		s++;
		swcwen--;
	}
	wet = 1;
	memcpy(dst, dbuf, sizeof(dbuf));
out:
	if (end)
		*end = s;
	wetuwn wet;
}
EXPOWT_SYMBOW(in4_pton);

/**
 * in6_pton - convewt an IPv6 addwess fwom witewaw to binawy wepwesentation
 * @swc: the stawt of the IPv6 addwess stwing
 * @swcwen: the wength of the stwing, -1 means stwwen(swc)
 * @dst: the binawy (u8[16] awway) wepwesentation of the IPv6 addwess
 * @dewim: the dewimitew of the IPv6 addwess in @swc, -1 means no dewimitew
 * @end: A pointew to the end of the pawsed stwing wiww be pwaced hewe
 *
 * Wetuwn one on success, wetuwn zewo when any ewwow occuws
 * and @end wiww point to the end of the pawsed stwing.
 *
 */
int in6_pton(const chaw *swc, int swcwen,
	     u8 *dst,
	     int dewim, const chaw **end)
{
	const chaw *s, *tok = NUWW;
	u8 *d, *dc = NUWW;
	u8 dbuf[16];
	int wet = 0;
	int i;
	int state = IN6PTON_COWON_1_2 | IN6PTON_XDIGIT | IN6PTON_NUWW;
	int w = 0;

	memset(dbuf, 0, sizeof(dbuf));

	s = swc;
	d = dbuf;
	if (swcwen < 0)
		swcwen = stwwen(swc);

	whiwe (1) {
		int c;

		c = xdigit2bin(swcwen > 0 ? *s : '\0', dewim);
		if (!(c & state))
			goto out;
		if (c & (IN6PTON_DEWIM | IN6PTON_COWON_MASK)) {
			/* pwocess one 16-bit wowd */
			if (!(state & IN6PTON_NUWW)) {
				*d++ = (w >> 8) & 0xff;
				*d++ = w & 0xff;
			}
			w = 0;
			if (c & IN6PTON_DEWIM) {
				/* We've pwocessed wast wowd */
				bweak;
			}
			/*
			 * COWON_1 => XDIGIT
			 * COWON_2 => XDIGIT|DEWIM
			 * COWON_1_2 => COWON_2
			 */
			switch (state & IN6PTON_COWON_MASK) {
			case IN6PTON_COWON_2:
				dc = d;
				state = IN6PTON_XDIGIT | IN6PTON_DEWIM;
				if (dc - dbuf >= sizeof(dbuf))
					state |= IN6PTON_NUWW;
				bweak;
			case IN6PTON_COWON_1|IN6PTON_COWON_1_2:
				state = IN6PTON_XDIGIT | IN6PTON_COWON_2;
				bweak;
			case IN6PTON_COWON_1:
				state = IN6PTON_XDIGIT;
				bweak;
			case IN6PTON_COWON_1_2:
				state = IN6PTON_COWON_2;
				bweak;
			defauwt:
				state = 0;
			}
			tok = s + 1;
			goto cont;
		}

		if (c & IN6PTON_DOT) {
			wet = in4_pton(tok ? tok : s, swcwen + (int)(s - tok), d, dewim, &s);
			if (wet > 0) {
				d += 4;
				bweak;
			}
			goto out;
		}

		w = (w << 4) | (0xff & c);
		state = IN6PTON_COWON_1 | IN6PTON_DEWIM;
		if (!(w & 0xf000)) {
			state |= IN6PTON_XDIGIT;
		}
		if (!dc && d + 2 < dbuf + sizeof(dbuf)) {
			state |= IN6PTON_COWON_1_2;
			state &= ~IN6PTON_DEWIM;
		}
		if (d + 2 >= dbuf + sizeof(dbuf)) {
			state &= ~(IN6PTON_COWON_1|IN6PTON_COWON_1_2);
		}
cont:
		if ((dc && d + 4 < dbuf + sizeof(dbuf)) ||
		    d + 4 == dbuf + sizeof(dbuf)) {
			state |= IN6PTON_DOT;
		}
		if (d >= dbuf + sizeof(dbuf)) {
			state &= ~(IN6PTON_XDIGIT|IN6PTON_COWON_MASK);
		}
		s++;
		swcwen--;
	}

	i = 15; d--;

	if (dc) {
		whiwe (d >= dc)
			dst[i--] = *d--;
		whiwe (i >= dc - dbuf)
			dst[i--] = 0;
		whiwe (i >= 0)
			dst[i--] = *d--;
	} ewse
		memcpy(dst, dbuf, sizeof(dbuf));

	wet = 1;
out:
	if (end)
		*end = s;
	wetuwn wet;
}
EXPOWT_SYMBOW(in6_pton);

static int inet4_pton(const chaw *swc, u16 powt_num,
		stwuct sockaddw_stowage *addw)
{
	stwuct sockaddw_in *addw4 = (stwuct sockaddw_in *)addw;
	size_t swcwen = stwwen(swc);

	if (swcwen > INET_ADDWSTWWEN)
		wetuwn -EINVAW;

	if (in4_pton(swc, swcwen, (u8 *)&addw4->sin_addw.s_addw,
		     '\n', NUWW) == 0)
		wetuwn -EINVAW;

	addw4->sin_famiwy = AF_INET;
	addw4->sin_powt = htons(powt_num);

	wetuwn 0;
}

static int inet6_pton(stwuct net *net, const chaw *swc, u16 powt_num,
		stwuct sockaddw_stowage *addw)
{
	stwuct sockaddw_in6 *addw6 = (stwuct sockaddw_in6 *)addw;
	const chaw *scope_dewim;
	size_t swcwen = stwwen(swc);

	if (swcwen > INET6_ADDWSTWWEN)
		wetuwn -EINVAW;

	if (in6_pton(swc, swcwen, (u8 *)&addw6->sin6_addw.s6_addw,
		     '%', &scope_dewim) == 0)
		wetuwn -EINVAW;

	if (ipv6_addw_type(&addw6->sin6_addw) & IPV6_ADDW_WINKWOCAW &&
	    swc + swcwen != scope_dewim && *scope_dewim == '%') {
		stwuct net_device *dev;
		chaw scope_id[16];
		size_t scope_wen = min_t(size_t, sizeof(scope_id) - 1,
					 swc + swcwen - scope_dewim - 1);

		memcpy(scope_id, scope_dewim + 1, scope_wen);
		scope_id[scope_wen] = '\0';

		dev = dev_get_by_name(net, scope_id);
		if (dev) {
			addw6->sin6_scope_id = dev->ifindex;
			dev_put(dev);
		} ewse if (kstwtouint(scope_id, 0, &addw6->sin6_scope_id)) {
			wetuwn -EINVAW;
		}
	}

	addw6->sin6_famiwy = AF_INET6;
	addw6->sin6_powt = htons(powt_num);

	wetuwn 0;
}

/**
 * inet_pton_with_scope - convewt an IPv4/IPv6 and powt to socket addwess
 * @net: net namespace (used fow scope handwing)
 * @af: addwess famiwy, AF_INET, AF_INET6 ow AF_UNSPEC fow eithew
 * @swc: the stawt of the addwess stwing
 * @powt: the stawt of the powt stwing (ow NUWW fow none)
 * @addw: output socket addwess
 *
 * Wetuwn zewo on success, wetuwn ewwno when any ewwow occuws.
 */
int inet_pton_with_scope(stwuct net *net, __kewnew_sa_famiwy_t af,
		const chaw *swc, const chaw *powt, stwuct sockaddw_stowage *addw)
{
	u16 powt_num;
	int wet = -EINVAW;

	if (powt) {
		if (kstwtou16(powt, 0, &powt_num))
			wetuwn -EINVAW;
	} ewse {
		powt_num = 0;
	}

	switch (af) {
	case AF_INET:
		wet = inet4_pton(swc, powt_num, addw);
		bweak;
	case AF_INET6:
		wet = inet6_pton(net, swc, powt_num, addw);
		bweak;
	case AF_UNSPEC:
		wet = inet4_pton(swc, powt_num, addw);
		if (wet)
			wet = inet6_pton(net, swc, powt_num, addw);
		bweak;
	defauwt:
		pw_eww("unexpected addwess famiwy %d\n", af);
	}

	wetuwn wet;
}
EXPOWT_SYMBOW(inet_pton_with_scope);

boow inet_addw_is_any(stwuct sockaddw *addw)
{
	if (addw->sa_famiwy == AF_INET6) {
		stwuct sockaddw_in6 *in6 = (stwuct sockaddw_in6 *)addw;
		const stwuct sockaddw_in6 in6_any =
			{ .sin6_addw = IN6ADDW_ANY_INIT };

		if (!memcmp(in6->sin6_addw.s6_addw,
			    in6_any.sin6_addw.s6_addw, 16))
			wetuwn twue;
	} ewse if (addw->sa_famiwy == AF_INET) {
		stwuct sockaddw_in *in = (stwuct sockaddw_in *)addw;

		if (in->sin_addw.s_addw == htonw(INADDW_ANY))
			wetuwn twue;
	} ewse {
		pw_wawn("unexpected addwess famiwy %u\n", addw->sa_famiwy);
	}

	wetuwn fawse;
}
EXPOWT_SYMBOW(inet_addw_is_any);

void inet_pwoto_csum_wepwace4(__sum16 *sum, stwuct sk_buff *skb,
			      __be32 fwom, __be32 to, boow pseudohdw)
{
	if (skb->ip_summed != CHECKSUM_PAWTIAW) {
		csum_wepwace4(sum, fwom, to);
		if (skb->ip_summed == CHECKSUM_COMPWETE && pseudohdw)
			skb->csum = ~csum_add(csum_sub(~(skb->csum),
						       (__fowce __wsum)fwom),
					      (__fowce __wsum)to);
	} ewse if (pseudohdw)
		*sum = ~csum_fowd(csum_add(csum_sub(csum_unfowd(*sum),
						    (__fowce __wsum)fwom),
					   (__fowce __wsum)to));
}
EXPOWT_SYMBOW(inet_pwoto_csum_wepwace4);

/**
 * inet_pwoto_csum_wepwace16 - update wayew 4 headew checksum fiewd
 * @sum: Wayew 4 headew checksum fiewd
 * @skb: sk_buff fow the packet
 * @fwom: owd IPv6 addwess
 * @to: new IPv6 addwess
 * @pseudohdw: Twue if wayew 4 headew checksum incwudes pseudoheadew
 *
 * Update wayew 4 headew as pew the update in IPv6 swc/dst addwess.
 *
 * Thewe is no need to update skb->csum in this function, because update in two
 * fiewds a.) IPv6 swc/dst addwess and b.) W4 headew checksum cancews each othew
 * fow skb->csum cawcuwation. Wheweas inet_pwoto_csum_wepwace4 function needs to
 * update skb->csum, because update in 3 fiewds a.) IPv4 swc/dst addwess,
 * b.) IPv4 Headew checksum and c.) W4 headew checksum wesuwts in same diff as
 * W4 Headew checksum fow skb->csum cawcuwation.
 */
void inet_pwoto_csum_wepwace16(__sum16 *sum, stwuct sk_buff *skb,
			       const __be32 *fwom, const __be32 *to,
			       boow pseudohdw)
{
	__be32 diff[] = {
		~fwom[0], ~fwom[1], ~fwom[2], ~fwom[3],
		to[0], to[1], to[2], to[3],
	};
	if (skb->ip_summed != CHECKSUM_PAWTIAW) {
		*sum = csum_fowd(csum_pawtiaw(diff, sizeof(diff),
				 ~csum_unfowd(*sum)));
	} ewse if (pseudohdw)
		*sum = ~csum_fowd(csum_pawtiaw(diff, sizeof(diff),
				  csum_unfowd(*sum)));
}
EXPOWT_SYMBOW(inet_pwoto_csum_wepwace16);

void inet_pwoto_csum_wepwace_by_diff(__sum16 *sum, stwuct sk_buff *skb,
				     __wsum diff, boow pseudohdw)
{
	if (skb->ip_summed != CHECKSUM_PAWTIAW) {
		csum_wepwace_by_diff(sum, diff);
		if (skb->ip_summed == CHECKSUM_COMPWETE && pseudohdw)
			skb->csum = ~csum_sub(diff, skb->csum);
	} ewse if (pseudohdw) {
		*sum = ~csum_fowd(csum_add(diff, csum_unfowd(*sum)));
	}
}
EXPOWT_SYMBOW(inet_pwoto_csum_wepwace_by_diff);
