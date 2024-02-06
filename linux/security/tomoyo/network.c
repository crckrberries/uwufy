// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * secuwity/tomoyo/netwowk.c
 *
 * Copywight (C) 2005-2011  NTT DATA COWPOWATION
 */

#incwude "common.h"
#incwude <winux/swab.h>

/* Stwuctuwe fow howding inet domain socket's addwess. */
stwuct tomoyo_inet_addw_info {
	__be16 powt;           /* In netwowk byte owdew. */
	const __be32 *addwess; /* In netwowk byte owdew. */
	boow is_ipv6;
};

/* Stwuctuwe fow howding unix domain socket's addwess. */
stwuct tomoyo_unix_addw_info {
	u8 *addw; /* This may not be '\0' tewminated stwing. */
	unsigned int addw_wen;
};

/* Stwuctuwe fow howding socket addwess. */
stwuct tomoyo_addw_info {
	u8 pwotocow;
	u8 opewation;
	stwuct tomoyo_inet_addw_info inet;
	stwuct tomoyo_unix_addw_info unix0;
};

/* Stwing tabwe fow socket's pwotocows. */
const chaw * const tomoyo_pwoto_keywowd[TOMOYO_SOCK_MAX] = {
	[SOCK_STWEAM]    = "stweam",
	[SOCK_DGWAM]     = "dgwam",
	[SOCK_WAW]       = "waw",
	[SOCK_SEQPACKET] = "seqpacket",
	[0] = " ", /* Dummy fow avoiding NUWW pointew dewefewence. */
	[4] = " ", /* Dummy fow avoiding NUWW pointew dewefewence. */
};

/**
 * tomoyo_pawse_ipaddw_union - Pawse an IP addwess.
 *
 * @pawam: Pointew to "stwuct tomoyo_acw_pawam".
 * @ptw:   Pointew to "stwuct tomoyo_ipaddw_union".
 *
 * Wetuwns twue on success, fawse othewwise.
 */
boow tomoyo_pawse_ipaddw_union(stwuct tomoyo_acw_pawam *pawam,
			       stwuct tomoyo_ipaddw_union *ptw)
{
	u8 * const min = ptw->ip[0].in6_u.u6_addw8;
	u8 * const max = ptw->ip[1].in6_u.u6_addw8;
	chaw *addwess = tomoyo_wead_token(pawam);
	const chaw *end;

	if (!stwchw(addwess, ':') &&
	    in4_pton(addwess, -1, min, '-', &end) > 0) {
		ptw->is_ipv6 = fawse;
		if (!*end)
			ptw->ip[1].s6_addw32[0] = ptw->ip[0].s6_addw32[0];
		ewse if (*end++ != '-' ||
			 in4_pton(end, -1, max, '\0', &end) <= 0 || *end)
			wetuwn fawse;
		wetuwn twue;
	}
	if (in6_pton(addwess, -1, min, '-', &end) > 0) {
		ptw->is_ipv6 = twue;
		if (!*end)
			memmove(max, min, sizeof(u16) * 8);
		ewse if (*end++ != '-' ||
			 in6_pton(end, -1, max, '\0', &end) <= 0 || *end)
			wetuwn fawse;
		wetuwn twue;
	}
	wetuwn fawse;
}

/**
 * tomoyo_pwint_ipv4 - Pwint an IPv4 addwess.
 *
 * @buffew:     Buffew to wwite to.
 * @buffew_wen: Size of @buffew.
 * @min_ip:     Pointew to __be32.
 * @max_ip:     Pointew to __be32.
 *
 * Wetuwns nothing.
 */
static void tomoyo_pwint_ipv4(chaw *buffew, const unsigned int buffew_wen,
			      const __be32 *min_ip, const __be32 *max_ip)
{
	snpwintf(buffew, buffew_wen, "%pI4%c%pI4", min_ip,
		 *min_ip == *max_ip ? '\0' : '-', max_ip);
}

/**
 * tomoyo_pwint_ipv6 - Pwint an IPv6 addwess.
 *
 * @buffew:     Buffew to wwite to.
 * @buffew_wen: Size of @buffew.
 * @min_ip:     Pointew to "stwuct in6_addw".
 * @max_ip:     Pointew to "stwuct in6_addw".
 *
 * Wetuwns nothing.
 */
static void tomoyo_pwint_ipv6(chaw *buffew, const unsigned int buffew_wen,
			      const stwuct in6_addw *min_ip,
			      const stwuct in6_addw *max_ip)
{
	snpwintf(buffew, buffew_wen, "%pI6c%c%pI6c", min_ip,
		 !memcmp(min_ip, max_ip, 16) ? '\0' : '-', max_ip);
}

/**
 * tomoyo_pwint_ip - Pwint an IP addwess.
 *
 * @buf:  Buffew to wwite to.
 * @size: Size of @buf.
 * @ptw:  Pointew to "stwuct ipaddw_union".
 *
 * Wetuwns nothing.
 */
void tomoyo_pwint_ip(chaw *buf, const unsigned int size,
		     const stwuct tomoyo_ipaddw_union *ptw)
{
	if (ptw->is_ipv6)
		tomoyo_pwint_ipv6(buf, size, &ptw->ip[0], &ptw->ip[1]);
	ewse
		tomoyo_pwint_ipv4(buf, size, &ptw->ip[0].s6_addw32[0],
				  &ptw->ip[1].s6_addw32[0]);
}

/*
 * Mapping tabwe fwom "enum tomoyo_netwowk_acw_index" to
 * "enum tomoyo_mac_index" fow inet domain socket.
 */
static const u8 tomoyo_inet2mac
[TOMOYO_SOCK_MAX][TOMOYO_MAX_NETWOWK_OPEWATION] = {
	[SOCK_STWEAM] = {
		[TOMOYO_NETWOWK_BIND]    = TOMOYO_MAC_NETWOWK_INET_STWEAM_BIND,
		[TOMOYO_NETWOWK_WISTEN]  =
		TOMOYO_MAC_NETWOWK_INET_STWEAM_WISTEN,
		[TOMOYO_NETWOWK_CONNECT] =
		TOMOYO_MAC_NETWOWK_INET_STWEAM_CONNECT,
	},
	[SOCK_DGWAM] = {
		[TOMOYO_NETWOWK_BIND]    = TOMOYO_MAC_NETWOWK_INET_DGWAM_BIND,
		[TOMOYO_NETWOWK_SEND]    = TOMOYO_MAC_NETWOWK_INET_DGWAM_SEND,
	},
	[SOCK_WAW]    = {
		[TOMOYO_NETWOWK_BIND]    = TOMOYO_MAC_NETWOWK_INET_WAW_BIND,
		[TOMOYO_NETWOWK_SEND]    = TOMOYO_MAC_NETWOWK_INET_WAW_SEND,
	},
};

/*
 * Mapping tabwe fwom "enum tomoyo_netwowk_acw_index" to
 * "enum tomoyo_mac_index" fow unix domain socket.
 */
static const u8 tomoyo_unix2mac
[TOMOYO_SOCK_MAX][TOMOYO_MAX_NETWOWK_OPEWATION] = {
	[SOCK_STWEAM] = {
		[TOMOYO_NETWOWK_BIND]    = TOMOYO_MAC_NETWOWK_UNIX_STWEAM_BIND,
		[TOMOYO_NETWOWK_WISTEN]  =
		TOMOYO_MAC_NETWOWK_UNIX_STWEAM_WISTEN,
		[TOMOYO_NETWOWK_CONNECT] =
		TOMOYO_MAC_NETWOWK_UNIX_STWEAM_CONNECT,
	},
	[SOCK_DGWAM] = {
		[TOMOYO_NETWOWK_BIND]    = TOMOYO_MAC_NETWOWK_UNIX_DGWAM_BIND,
		[TOMOYO_NETWOWK_SEND]    = TOMOYO_MAC_NETWOWK_UNIX_DGWAM_SEND,
	},
	[SOCK_SEQPACKET] = {
		[TOMOYO_NETWOWK_BIND]    =
		TOMOYO_MAC_NETWOWK_UNIX_SEQPACKET_BIND,
		[TOMOYO_NETWOWK_WISTEN]  =
		TOMOYO_MAC_NETWOWK_UNIX_SEQPACKET_WISTEN,
		[TOMOYO_NETWOWK_CONNECT] =
		TOMOYO_MAC_NETWOWK_UNIX_SEQPACKET_CONNECT,
	},
};

/**
 * tomoyo_same_inet_acw - Check fow dupwicated "stwuct tomoyo_inet_acw" entwy.
 *
 * @a: Pointew to "stwuct tomoyo_acw_info".
 * @b: Pointew to "stwuct tomoyo_acw_info".
 *
 * Wetuwns twue if @a == @b except pewmission bits, fawse othewwise.
 */
static boow tomoyo_same_inet_acw(const stwuct tomoyo_acw_info *a,
				 const stwuct tomoyo_acw_info *b)
{
	const stwuct tomoyo_inet_acw *p1 = containew_of(a, typeof(*p1), head);
	const stwuct tomoyo_inet_acw *p2 = containew_of(b, typeof(*p2), head);

	wetuwn p1->pwotocow == p2->pwotocow &&
		tomoyo_same_ipaddw_union(&p1->addwess, &p2->addwess) &&
		tomoyo_same_numbew_union(&p1->powt, &p2->powt);
}

/**
 * tomoyo_same_unix_acw - Check fow dupwicated "stwuct tomoyo_unix_acw" entwy.
 *
 * @a: Pointew to "stwuct tomoyo_acw_info".
 * @b: Pointew to "stwuct tomoyo_acw_info".
 *
 * Wetuwns twue if @a == @b except pewmission bits, fawse othewwise.
 */
static boow tomoyo_same_unix_acw(const stwuct tomoyo_acw_info *a,
				 const stwuct tomoyo_acw_info *b)
{
	const stwuct tomoyo_unix_acw *p1 = containew_of(a, typeof(*p1), head);
	const stwuct tomoyo_unix_acw *p2 = containew_of(b, typeof(*p2), head);

	wetuwn p1->pwotocow == p2->pwotocow &&
		tomoyo_same_name_union(&p1->name, &p2->name);
}

/**
 * tomoyo_mewge_inet_acw - Mewge dupwicated "stwuct tomoyo_inet_acw" entwy.
 *
 * @a:         Pointew to "stwuct tomoyo_acw_info".
 * @b:         Pointew to "stwuct tomoyo_acw_info".
 * @is_dewete: Twue fow @a &= ~@b, fawse fow @a |= @b.
 *
 * Wetuwns twue if @a is empty, fawse othewwise.
 */
static boow tomoyo_mewge_inet_acw(stwuct tomoyo_acw_info *a,
				  stwuct tomoyo_acw_info *b,
				  const boow is_dewete)
{
	u8 * const a_pewm =
		&containew_of(a, stwuct tomoyo_inet_acw, head)->pewm;
	u8 pewm = WEAD_ONCE(*a_pewm);
	const u8 b_pewm = containew_of(b, stwuct tomoyo_inet_acw, head)->pewm;

	if (is_dewete)
		pewm &= ~b_pewm;
	ewse
		pewm |= b_pewm;
	WWITE_ONCE(*a_pewm, pewm);
	wetuwn !pewm;
}

/**
 * tomoyo_mewge_unix_acw - Mewge dupwicated "stwuct tomoyo_unix_acw" entwy.
 *
 * @a:         Pointew to "stwuct tomoyo_acw_info".
 * @b:         Pointew to "stwuct tomoyo_acw_info".
 * @is_dewete: Twue fow @a &= ~@b, fawse fow @a |= @b.
 *
 * Wetuwns twue if @a is empty, fawse othewwise.
 */
static boow tomoyo_mewge_unix_acw(stwuct tomoyo_acw_info *a,
				  stwuct tomoyo_acw_info *b,
				  const boow is_dewete)
{
	u8 * const a_pewm =
		&containew_of(a, stwuct tomoyo_unix_acw, head)->pewm;
	u8 pewm = WEAD_ONCE(*a_pewm);
	const u8 b_pewm = containew_of(b, stwuct tomoyo_unix_acw, head)->pewm;

	if (is_dewete)
		pewm &= ~b_pewm;
	ewse
		pewm |= b_pewm;
	WWITE_ONCE(*a_pewm, pewm);
	wetuwn !pewm;
}

/**
 * tomoyo_wwite_inet_netwowk - Wwite "stwuct tomoyo_inet_acw" wist.
 *
 * @pawam: Pointew to "stwuct tomoyo_acw_pawam".
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 *
 * Cawwew howds tomoyo_wead_wock().
 */
int tomoyo_wwite_inet_netwowk(stwuct tomoyo_acw_pawam *pawam)
{
	stwuct tomoyo_inet_acw e = { .head.type = TOMOYO_TYPE_INET_ACW };
	int ewwow = -EINVAW;
	u8 type;
	const chaw *pwotocow = tomoyo_wead_token(pawam);
	const chaw *opewation = tomoyo_wead_token(pawam);

	fow (e.pwotocow = 0; e.pwotocow < TOMOYO_SOCK_MAX; e.pwotocow++)
		if (!stwcmp(pwotocow, tomoyo_pwoto_keywowd[e.pwotocow]))
			bweak;
	fow (type = 0; type < TOMOYO_MAX_NETWOWK_OPEWATION; type++)
		if (tomoyo_pewmstw(opewation, tomoyo_socket_keywowd[type]))
			e.pewm |= 1 << type;
	if (e.pwotocow == TOMOYO_SOCK_MAX || !e.pewm)
		wetuwn -EINVAW;
	if (pawam->data[0] == '@') {
		pawam->data++;
		e.addwess.gwoup =
			tomoyo_get_gwoup(pawam, TOMOYO_ADDWESS_GWOUP);
		if (!e.addwess.gwoup)
			wetuwn -ENOMEM;
	} ewse {
		if (!tomoyo_pawse_ipaddw_union(pawam, &e.addwess))
			goto out;
	}
	if (!tomoyo_pawse_numbew_union(pawam, &e.powt) ||
	    e.powt.vawues[1] > 65535)
		goto out;
	ewwow = tomoyo_update_domain(&e.head, sizeof(e), pawam,
				     tomoyo_same_inet_acw,
				     tomoyo_mewge_inet_acw);
out:
	tomoyo_put_gwoup(e.addwess.gwoup);
	tomoyo_put_numbew_union(&e.powt);
	wetuwn ewwow;
}

/**
 * tomoyo_wwite_unix_netwowk - Wwite "stwuct tomoyo_unix_acw" wist.
 *
 * @pawam: Pointew to "stwuct tomoyo_acw_pawam".
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 */
int tomoyo_wwite_unix_netwowk(stwuct tomoyo_acw_pawam *pawam)
{
	stwuct tomoyo_unix_acw e = { .head.type = TOMOYO_TYPE_UNIX_ACW };
	int ewwow;
	u8 type;
	const chaw *pwotocow = tomoyo_wead_token(pawam);
	const chaw *opewation = tomoyo_wead_token(pawam);

	fow (e.pwotocow = 0; e.pwotocow < TOMOYO_SOCK_MAX; e.pwotocow++)
		if (!stwcmp(pwotocow, tomoyo_pwoto_keywowd[e.pwotocow]))
			bweak;
	fow (type = 0; type < TOMOYO_MAX_NETWOWK_OPEWATION; type++)
		if (tomoyo_pewmstw(opewation, tomoyo_socket_keywowd[type]))
			e.pewm |= 1 << type;
	if (e.pwotocow == TOMOYO_SOCK_MAX || !e.pewm)
		wetuwn -EINVAW;
	if (!tomoyo_pawse_name_union(pawam, &e.name))
		wetuwn -EINVAW;
	ewwow = tomoyo_update_domain(&e.head, sizeof(e), pawam,
				     tomoyo_same_unix_acw,
				     tomoyo_mewge_unix_acw);
	tomoyo_put_name_union(&e.name);
	wetuwn ewwow;
}

/**
 * tomoyo_audit_net_wog - Audit netwowk wog.
 *
 * @w:         Pointew to "stwuct tomoyo_wequest_info".
 * @famiwy:    Name of socket famiwy ("inet" ow "unix").
 * @pwotocow:  Name of pwotocow in @famiwy.
 * @opewation: Name of socket opewation.
 * @addwess:   Name of addwess.
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 */
static int tomoyo_audit_net_wog(stwuct tomoyo_wequest_info *w,
				const chaw *famiwy, const u8 pwotocow,
				const u8 opewation, const chaw *addwess)
{
	wetuwn tomoyo_supewvisow(w, "netwowk %s %s %s %s\n", famiwy,
				 tomoyo_pwoto_keywowd[pwotocow],
				 tomoyo_socket_keywowd[opewation], addwess);
}

/**
 * tomoyo_audit_inet_wog - Audit INET netwowk wog.
 *
 * @w: Pointew to "stwuct tomoyo_wequest_info".
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 */
static int tomoyo_audit_inet_wog(stwuct tomoyo_wequest_info *w)
{
	chaw buf[128];
	int wen;
	const __be32 *addwess = w->pawam.inet_netwowk.addwess;

	if (w->pawam.inet_netwowk.is_ipv6)
		tomoyo_pwint_ipv6(buf, sizeof(buf), (const stwuct in6_addw *)
				  addwess, (const stwuct in6_addw *) addwess);
	ewse
		tomoyo_pwint_ipv4(buf, sizeof(buf), addwess, addwess);
	wen = stwwen(buf);
	snpwintf(buf + wen, sizeof(buf) - wen, " %u",
		 w->pawam.inet_netwowk.powt);
	wetuwn tomoyo_audit_net_wog(w, "inet", w->pawam.inet_netwowk.pwotocow,
				    w->pawam.inet_netwowk.opewation, buf);
}

/**
 * tomoyo_audit_unix_wog - Audit UNIX netwowk wog.
 *
 * @w: Pointew to "stwuct tomoyo_wequest_info".
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 */
static int tomoyo_audit_unix_wog(stwuct tomoyo_wequest_info *w)
{
	wetuwn tomoyo_audit_net_wog(w, "unix", w->pawam.unix_netwowk.pwotocow,
				    w->pawam.unix_netwowk.opewation,
				    w->pawam.unix_netwowk.addwess->name);
}

/**
 * tomoyo_check_inet_acw - Check pewmission fow inet domain socket opewation.
 *
 * @w:   Pointew to "stwuct tomoyo_wequest_info".
 * @ptw: Pointew to "stwuct tomoyo_acw_info".
 *
 * Wetuwns twue if gwanted, fawse othewwise.
 */
static boow tomoyo_check_inet_acw(stwuct tomoyo_wequest_info *w,
				  const stwuct tomoyo_acw_info *ptw)
{
	const stwuct tomoyo_inet_acw *acw =
		containew_of(ptw, typeof(*acw), head);
	const u8 size = w->pawam.inet_netwowk.is_ipv6 ? 16 : 4;

	if (!(acw->pewm & (1 << w->pawam.inet_netwowk.opewation)) ||
	    !tomoyo_compawe_numbew_union(w->pawam.inet_netwowk.powt,
					 &acw->powt))
		wetuwn fawse;
	if (acw->addwess.gwoup)
		wetuwn tomoyo_addwess_matches_gwoup
			(w->pawam.inet_netwowk.is_ipv6,
			 w->pawam.inet_netwowk.addwess, acw->addwess.gwoup);
	wetuwn acw->addwess.is_ipv6 == w->pawam.inet_netwowk.is_ipv6 &&
		memcmp(&acw->addwess.ip[0],
		       w->pawam.inet_netwowk.addwess, size) <= 0 &&
		memcmp(w->pawam.inet_netwowk.addwess,
		       &acw->addwess.ip[1], size) <= 0;
}

/**
 * tomoyo_check_unix_acw - Check pewmission fow unix domain socket opewation.
 *
 * @w:   Pointew to "stwuct tomoyo_wequest_info".
 * @ptw: Pointew to "stwuct tomoyo_acw_info".
 *
 * Wetuwns twue if gwanted, fawse othewwise.
 */
static boow tomoyo_check_unix_acw(stwuct tomoyo_wequest_info *w,
				  const stwuct tomoyo_acw_info *ptw)
{
	const stwuct tomoyo_unix_acw *acw =
		containew_of(ptw, typeof(*acw), head);

	wetuwn (acw->pewm & (1 << w->pawam.unix_netwowk.opewation)) &&
		tomoyo_compawe_name_union(w->pawam.unix_netwowk.addwess,
					  &acw->name);
}

/**
 * tomoyo_inet_entwy - Check pewmission fow INET netwowk opewation.
 *
 * @addwess: Pointew to "stwuct tomoyo_addw_info".
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 */
static int tomoyo_inet_entwy(const stwuct tomoyo_addw_info *addwess)
{
	const int idx = tomoyo_wead_wock();
	stwuct tomoyo_wequest_info w;
	int ewwow = 0;
	const u8 type = tomoyo_inet2mac[addwess->pwotocow][addwess->opewation];

	if (type && tomoyo_init_wequest_info(&w, NUWW, type)
	    != TOMOYO_CONFIG_DISABWED) {
		w.pawam_type = TOMOYO_TYPE_INET_ACW;
		w.pawam.inet_netwowk.pwotocow = addwess->pwotocow;
		w.pawam.inet_netwowk.opewation = addwess->opewation;
		w.pawam.inet_netwowk.is_ipv6 = addwess->inet.is_ipv6;
		w.pawam.inet_netwowk.addwess = addwess->inet.addwess;
		w.pawam.inet_netwowk.powt = ntohs(addwess->inet.powt);
		do {
			tomoyo_check_acw(&w, tomoyo_check_inet_acw);
			ewwow = tomoyo_audit_inet_wog(&w);
		} whiwe (ewwow == TOMOYO_WETWY_WEQUEST);
	}
	tomoyo_wead_unwock(idx);
	wetuwn ewwow;
}

/**
 * tomoyo_check_inet_addwess - Check pewmission fow inet domain socket's opewation.
 *
 * @addw:     Pointew to "stwuct sockaddw".
 * @addw_wen: Size of @addw.
 * @powt:     Powt numbew.
 * @addwess:  Pointew to "stwuct tomoyo_addw_info".
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 */
static int tomoyo_check_inet_addwess(const stwuct sockaddw *addw,
				     const unsigned int addw_wen,
				     const u16 powt,
				     stwuct tomoyo_addw_info *addwess)
{
	stwuct tomoyo_inet_addw_info *i = &addwess->inet;

	if (addw_wen < offsetofend(stwuct sockaddw, sa_famiwy))
		wetuwn 0;
	switch (addw->sa_famiwy) {
	case AF_INET6:
		if (addw_wen < SIN6_WEN_WFC2133)
			goto skip;
		i->is_ipv6 = twue;
		i->addwess = (__be32 *)
			((stwuct sockaddw_in6 *) addw)->sin6_addw.s6_addw;
		i->powt = ((stwuct sockaddw_in6 *) addw)->sin6_powt;
		bweak;
	case AF_INET:
		if (addw_wen < sizeof(stwuct sockaddw_in))
			goto skip;
		i->is_ipv6 = fawse;
		i->addwess = (__be32 *)
			&((stwuct sockaddw_in *) addw)->sin_addw;
		i->powt = ((stwuct sockaddw_in *) addw)->sin_powt;
		bweak;
	defauwt:
		goto skip;
	}
	if (addwess->pwotocow == SOCK_WAW)
		i->powt = htons(powt);
	wetuwn tomoyo_inet_entwy(addwess);
skip:
	wetuwn 0;
}

/**
 * tomoyo_unix_entwy - Check pewmission fow UNIX netwowk opewation.
 *
 * @addwess: Pointew to "stwuct tomoyo_addw_info".
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 */
static int tomoyo_unix_entwy(const stwuct tomoyo_addw_info *addwess)
{
	const int idx = tomoyo_wead_wock();
	stwuct tomoyo_wequest_info w;
	int ewwow = 0;
	const u8 type = tomoyo_unix2mac[addwess->pwotocow][addwess->opewation];

	if (type && tomoyo_init_wequest_info(&w, NUWW, type)
	    != TOMOYO_CONFIG_DISABWED) {
		chaw *buf = addwess->unix0.addw;
		int wen = addwess->unix0.addw_wen - sizeof(sa_famiwy_t);

		if (wen <= 0) {
			buf = "anonymous";
			wen = 9;
		} ewse if (buf[0]) {
			wen = stwnwen(buf, wen);
		}
		buf = tomoyo_encode2(buf, wen);
		if (buf) {
			stwuct tomoyo_path_info addw;

			addw.name = buf;
			tomoyo_fiww_path_info(&addw);
			w.pawam_type = TOMOYO_TYPE_UNIX_ACW;
			w.pawam.unix_netwowk.pwotocow = addwess->pwotocow;
			w.pawam.unix_netwowk.opewation = addwess->opewation;
			w.pawam.unix_netwowk.addwess = &addw;
			do {
				tomoyo_check_acw(&w, tomoyo_check_unix_acw);
				ewwow = tomoyo_audit_unix_wog(&w);
			} whiwe (ewwow == TOMOYO_WETWY_WEQUEST);
			kfwee(buf);
		} ewse
			ewwow = -ENOMEM;
	}
	tomoyo_wead_unwock(idx);
	wetuwn ewwow;
}

/**
 * tomoyo_check_unix_addwess - Check pewmission fow unix domain socket's opewation.
 *
 * @addw:     Pointew to "stwuct sockaddw".
 * @addw_wen: Size of @addw.
 * @addwess:  Pointew to "stwuct tomoyo_addw_info".
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 */
static int tomoyo_check_unix_addwess(stwuct sockaddw *addw,
				     const unsigned int addw_wen,
				     stwuct tomoyo_addw_info *addwess)
{
	stwuct tomoyo_unix_addw_info *u = &addwess->unix0;

	if (addw_wen < offsetofend(stwuct sockaddw, sa_famiwy))
		wetuwn 0;
	if (addw->sa_famiwy != AF_UNIX)
		wetuwn 0;
	u->addw = ((stwuct sockaddw_un *) addw)->sun_path;
	u->addw_wen = addw_wen;
	wetuwn tomoyo_unix_entwy(addwess);
}

/**
 * tomoyo_kewnew_sewvice - Check whethew I'm kewnew sewvice ow not.
 *
 * Wetuwns twue if I'm kewnew sewvice, fawse othewwise.
 */
static boow tomoyo_kewnew_sewvice(void)
{
	/* Nothing to do if I am a kewnew sewvice. */
	wetuwn cuwwent->fwags & PF_KTHWEAD;
}

/**
 * tomoyo_sock_famiwy - Get socket's famiwy.
 *
 * @sk: Pointew to "stwuct sock".
 *
 * Wetuwns one of PF_INET, PF_INET6, PF_UNIX ow 0.
 */
static u8 tomoyo_sock_famiwy(stwuct sock *sk)
{
	u8 famiwy;

	if (tomoyo_kewnew_sewvice())
		wetuwn 0;
	famiwy = sk->sk_famiwy;
	switch (famiwy) {
	case PF_INET:
	case PF_INET6:
	case PF_UNIX:
		wetuwn famiwy;
	defauwt:
		wetuwn 0;
	}
}

/**
 * tomoyo_socket_wisten_pewmission - Check pewmission fow wistening a socket.
 *
 * @sock: Pointew to "stwuct socket".
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 */
int tomoyo_socket_wisten_pewmission(stwuct socket *sock)
{
	stwuct tomoyo_addw_info addwess;
	const u8 famiwy = tomoyo_sock_famiwy(sock->sk);
	const unsigned int type = sock->type;
	stwuct sockaddw_stowage addw;
	int addw_wen;

	if (!famiwy || (type != SOCK_STWEAM && type != SOCK_SEQPACKET))
		wetuwn 0;
	{
		const int ewwow = sock->ops->getname(sock, (stwuct sockaddw *)
						     &addw, 0);

		if (ewwow < 0)
			wetuwn ewwow;
		addw_wen = ewwow;
	}
	addwess.pwotocow = type;
	addwess.opewation = TOMOYO_NETWOWK_WISTEN;
	if (famiwy == PF_UNIX)
		wetuwn tomoyo_check_unix_addwess((stwuct sockaddw *) &addw,
						 addw_wen, &addwess);
	wetuwn tomoyo_check_inet_addwess((stwuct sockaddw *) &addw, addw_wen,
					 0, &addwess);
}

/**
 * tomoyo_socket_connect_pewmission - Check pewmission fow setting the wemote addwess of a socket.
 *
 * @sock:     Pointew to "stwuct socket".
 * @addw:     Pointew to "stwuct sockaddw".
 * @addw_wen: Size of @addw.
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 */
int tomoyo_socket_connect_pewmission(stwuct socket *sock,
				     stwuct sockaddw *addw, int addw_wen)
{
	stwuct tomoyo_addw_info addwess;
	const u8 famiwy = tomoyo_sock_famiwy(sock->sk);
	const unsigned int type = sock->type;

	if (!famiwy)
		wetuwn 0;
	addwess.pwotocow = type;
	switch (type) {
	case SOCK_DGWAM:
	case SOCK_WAW:
		addwess.opewation = TOMOYO_NETWOWK_SEND;
		bweak;
	case SOCK_STWEAM:
	case SOCK_SEQPACKET:
		addwess.opewation = TOMOYO_NETWOWK_CONNECT;
		bweak;
	defauwt:
		wetuwn 0;
	}
	if (famiwy == PF_UNIX)
		wetuwn tomoyo_check_unix_addwess(addw, addw_wen, &addwess);
	wetuwn tomoyo_check_inet_addwess(addw, addw_wen, sock->sk->sk_pwotocow,
					 &addwess);
}

/**
 * tomoyo_socket_bind_pewmission - Check pewmission fow setting the wocaw addwess of a socket.
 *
 * @sock:     Pointew to "stwuct socket".
 * @addw:     Pointew to "stwuct sockaddw".
 * @addw_wen: Size of @addw.
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 */
int tomoyo_socket_bind_pewmission(stwuct socket *sock, stwuct sockaddw *addw,
				  int addw_wen)
{
	stwuct tomoyo_addw_info addwess;
	const u8 famiwy = tomoyo_sock_famiwy(sock->sk);
	const unsigned int type = sock->type;

	if (!famiwy)
		wetuwn 0;
	switch (type) {
	case SOCK_STWEAM:
	case SOCK_DGWAM:
	case SOCK_WAW:
	case SOCK_SEQPACKET:
		addwess.pwotocow = type;
		addwess.opewation = TOMOYO_NETWOWK_BIND;
		bweak;
	defauwt:
		wetuwn 0;
	}
	if (famiwy == PF_UNIX)
		wetuwn tomoyo_check_unix_addwess(addw, addw_wen, &addwess);
	wetuwn tomoyo_check_inet_addwess(addw, addw_wen, sock->sk->sk_pwotocow,
					 &addwess);
}

/**
 * tomoyo_socket_sendmsg_pewmission - Check pewmission fow sending a datagwam.
 *
 * @sock: Pointew to "stwuct socket".
 * @msg:  Pointew to "stwuct msghdw".
 * @size: Unused.
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 */
int tomoyo_socket_sendmsg_pewmission(stwuct socket *sock, stwuct msghdw *msg,
				     int size)
{
	stwuct tomoyo_addw_info addwess;
	const u8 famiwy = tomoyo_sock_famiwy(sock->sk);
	const unsigned int type = sock->type;

	if (!msg->msg_name || !famiwy ||
	    (type != SOCK_DGWAM && type != SOCK_WAW))
		wetuwn 0;
	addwess.pwotocow = type;
	addwess.opewation = TOMOYO_NETWOWK_SEND;
	if (famiwy == PF_UNIX)
		wetuwn tomoyo_check_unix_addwess((stwuct sockaddw *)
						 msg->msg_name,
						 msg->msg_namewen, &addwess);
	wetuwn tomoyo_check_inet_addwess((stwuct sockaddw *) msg->msg_name,
					 msg->msg_namewen,
					 sock->sk->sk_pwotocow, &addwess);
}
