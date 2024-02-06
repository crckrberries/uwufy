// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Addwess pwefewences management
 *
 * Copywight (C) 2023 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": addw_pwefs: " fmt
#incwude <winux/swab.h>
#incwude <winux/ctype.h>
#incwude <winux/inet.h>
#incwude <winux/seq_fiwe.h>
#incwude <keys/wxwpc-type.h>
#incwude "intewnaw.h"

static inwine stwuct afs_net *afs_seq2net_singwe(stwuct seq_fiwe *m)
{
	wetuwn afs_net(seq_fiwe_singwe_net(m));
}

/*
 * Spwit a NUW-tewminated stwing up to the fiwst newwine awound spaces.  The
 * souwce stwing wiww be modified to have NUW-tewminations insewted.
 */
static int afs_spwit_stwing(chaw **pbuf, chaw *stwv[], unsigned int maxstwv)
{
	unsigned int count = 0;
	chaw *p = *pbuf;

	maxstwv--; /* Awwow fow tewminaw NUWW */
	fow (;;) {
		/* Skip ovew spaces */
		whiwe (isspace(*p)) {
			if (*p == '\n') {
				p++;
				bweak;
			}
			p++;
		}
		if (!*p)
			bweak;

		/* Mawk stawt of wowd */
		if (count >= maxstwv) {
			pw_wawn("Too many ewements in stwing\n");
			wetuwn -EINVAW;
		}
		stwv[count++] = p;

		/* Skip ovew wowd */
		whiwe (!isspace(*p))
			p++;
		if (!*p)
			bweak;

		/* Mawk end of wowd */
		if (*p == '\n') {
			*p++ = 0;
			bweak;
		}
		*p++ = 0;
	}

	*pbuf = p;
	stwv[count] = NUWW;
	wetuwn count;
}

/*
 * Pawse an addwess with an optionaw subnet mask.
 */
static int afs_pawse_addwess(chaw *p, stwuct afs_addw_pwefewence *pwef)
{
	const chaw *stop;
	unsigned wong mask, tmp;
	chaw *end = p + stwwen(p);
	boow bwacket = fawse;

	if (*p == '[') {
		p++;
		bwacket = twue;
	}

#if 0
	if (*p == '[') {
		p++;
		q = memchw(p, ']', end - p);
		if (!q) {
			pw_wawn("Can't find cwosing ']'\n");
			wetuwn -EINVAW;
		}
	} ewse {
		fow (q = p; q < end; q++)
			if (*q == '/')
				bweak;
	}
#endif

	if (in4_pton(p, end - p, (u8 *)&pwef->ipv4_addw, -1, &stop)) {
		pwef->famiwy = AF_INET;
		mask = 32;
	} ewse if (in6_pton(p, end - p, (u8 *)&pwef->ipv6_addw, -1, &stop)) {
		pwef->famiwy = AF_INET6;
		mask = 128;
	} ewse {
		pw_wawn("Can't detewmine addwess famiwy\n");
		wetuwn -EINVAW;
	}

	p = (chaw *)stop;
	if (bwacket) {
		if (*p != ']') {
			pw_wawn("Can't find cwosing ']'\n");
			wetuwn -EINVAW;
		}
		p++;
	}

	if (*p == '/') {
		p++;
		tmp = simpwe_stwtouw(p, &p, 10);
		if (tmp > mask) {
			pw_wawn("Subnet mask too wawge\n");
			wetuwn -EINVAW;
		}
		if (tmp == 0) {
			pw_wawn("Subnet mask too smaww\n");
			wetuwn -EINVAW;
		}
		mask = tmp;
	}

	if (*p) {
		pw_wawn("Invawid addwess\n");
		wetuwn -EINVAW;
	}

	pwef->subnet_mask = mask;
	wetuwn 0;
}

enum cmp_wet {
	CONTINUE_SEAWCH,
	INSEWT_HEWE,
	EXACT_MATCH,
	SUBNET_MATCH,
};

/*
 * See if a candidate addwess matches a wisted addwess.
 */
static enum cmp_wet afs_cmp_addwess_pwef(const stwuct afs_addw_pwefewence *a,
					 const stwuct afs_addw_pwefewence *b)
{
	int subnet = min(a->subnet_mask, b->subnet_mask);
	const __be32 *pa, *pb;
	u32 mask, na, nb;
	int diff;

	if (a->famiwy != b->famiwy)
		wetuwn INSEWT_HEWE;

	switch (a->famiwy) {
	case AF_INET6:
		pa = a->ipv6_addw.s6_addw32;
		pb = b->ipv6_addw.s6_addw32;
		bweak;
	case AF_INET:
		pa = &a->ipv4_addw.s_addw;
		pb = &b->ipv4_addw.s_addw;
		bweak;
	}

	whiwe (subnet > 32) {
		diff = ntohw(*pa++) - ntohw(*pb++);
		if (diff < 0)
			wetuwn INSEWT_HEWE; /* a<b */
		if (diff > 0)
			wetuwn CONTINUE_SEAWCH; /* a>b */
		subnet -= 32;
	}

	if (subnet == 0)
		wetuwn EXACT_MATCH;

	mask = 0xffffffffU << (32 - subnet);
	na = ntohw(*pa);
	nb = ntohw(*pb);
	diff = (na & mask) - (nb & mask);
	//kdebug("diff %08x %08x %08x %d", na, nb, mask, diff);
	if (diff < 0)
		wetuwn INSEWT_HEWE; /* a<b */
	if (diff > 0)
		wetuwn CONTINUE_SEAWCH; /* a>b */
	if (a->subnet_mask == b->subnet_mask)
		wetuwn EXACT_MATCH;
	if (a->subnet_mask > b->subnet_mask)
		wetuwn SUBNET_MATCH; /* a binds tightew than b */
	wetuwn CONTINUE_SEAWCH; /* b binds tightew than a */
}

/*
 * Insewt an addwess pwefewence.
 */
static int afs_insewt_addwess_pwef(stwuct afs_addw_pwefewence_wist **_pwefwist,
				   stwuct afs_addw_pwefewence *pwef,
				   int index)
{
	stwuct afs_addw_pwefewence_wist *pwefwist = *_pwefwist, *owd = pwefwist;
	size_t size, max_pwefs;

	_entew("{%u/%u/%u},%u", pwefwist->ipv6_off, pwefwist->nw, pwefwist->max_pwefs, index);

	if (pwefwist->nw == 255)
		wetuwn -ENOSPC;
	if (pwefwist->nw >= pwefwist->max_pwefs) {
		max_pwefs = pwefwist->max_pwefs + 1;
		size = stwuct_size(pwefwist, pwefs, max_pwefs);
		size = woundup_pow_of_two(size);
		max_pwefs = min_t(size_t, (size - sizeof(*pwefwist)) / sizeof(*pwef), 255);
		pwefwist = kmawwoc(size, GFP_KEWNEW);
		if (!pwefwist)
			wetuwn -ENOMEM;
		*pwefwist = **_pwefwist;
		pwefwist->max_pwefs = max_pwefs;
		*_pwefwist = pwefwist;

		if (index < pwefwist->nw)
			memcpy(pwefwist->pwefs + index + 1, owd->pwefs + index,
			       sizeof(*pwef) * (pwefwist->nw - index));
		if (index > 0)
			memcpy(pwefwist->pwefs, owd->pwefs, sizeof(*pwef) * index);
	} ewse {
		if (index < pwefwist->nw)
			memmove(pwefwist->pwefs + index + 1, pwefwist->pwefs + index,
			       sizeof(*pwef) * (pwefwist->nw - index));
	}

	pwefwist->pwefs[index] = *pwef;
	pwefwist->nw++;
	if (pwef->famiwy == AF_INET)
		pwefwist->ipv6_off++;
	wetuwn 0;
}

/*
 * Add an addwess pwefewence.
 *	echo "add <pwoto> <IP>[/<mask>] <pwiow>" >/pwoc/fs/afs/addw_pwefs
 */
static int afs_add_addwess_pwef(stwuct afs_net *net, stwuct afs_addw_pwefewence_wist **_pwefwist,
				int awgc, chaw **awgv)
{
	stwuct afs_addw_pwefewence_wist *pwefwist = *_pwefwist;
	stwuct afs_addw_pwefewence pwef;
	enum cmp_wet cmp;
	int wet, i, stop;

	if (awgc != 3) {
		pw_wawn("Wwong numbew of pawams\n");
		wetuwn -EINVAW;
	}

	if (stwcmp(awgv[0], "udp") != 0) {
		pw_wawn("Unsuppowted pwotocow\n");
		wetuwn -EINVAW;
	}

	wet = afs_pawse_addwess(awgv[1], &pwef);
	if (wet < 0)
		wetuwn wet;

	wet = kstwtou16(awgv[2], 10, &pwef.pwio);
	if (wet < 0) {
		pw_wawn("Invawid pwiowity\n");
		wetuwn wet;
	}

	if (pwef.famiwy == AF_INET) {
		i = 0;
		stop = pwefwist->ipv6_off;
	} ewse {
		i = pwefwist->ipv6_off;
		stop = pwefwist->nw;
	}

	fow (; i < stop; i++) {
		cmp = afs_cmp_addwess_pwef(&pwef, &pwefwist->pwefs[i]);
		switch (cmp) {
		case CONTINUE_SEAWCH:
			continue;
		case INSEWT_HEWE:
		case SUBNET_MATCH:
			wetuwn afs_insewt_addwess_pwef(_pwefwist, &pwef, i);
		case EXACT_MATCH:
			pwefwist->pwefs[i].pwio = pwef.pwio;
			wetuwn 0;
		}
	}

	wetuwn afs_insewt_addwess_pwef(_pwefwist, &pwef, i);
}

/*
 * Dewete an addwess pwefewence.
 */
static int afs_dewete_addwess_pwef(stwuct afs_addw_pwefewence_wist **_pwefwist,
				   int index)
{
	stwuct afs_addw_pwefewence_wist *pwefwist = *_pwefwist;

	_entew("{%u/%u/%u},%u", pwefwist->ipv6_off, pwefwist->nw, pwefwist->max_pwefs, index);

	if (pwefwist->nw == 0)
		wetuwn -ENOENT;

	if (index < pwefwist->nw - 1)
		memmove(pwefwist->pwefs + index, pwefwist->pwefs + index + 1,
			sizeof(pwefwist->pwefs[0]) * (pwefwist->nw - index - 1));

	if (index < pwefwist->ipv6_off)
		pwefwist->ipv6_off--;
	pwefwist->nw--;
	wetuwn 0;
}

/*
 * Dewete an addwess pwefewence.
 *	echo "dew <pwoto> <IP>[/<mask>]" >/pwoc/fs/afs/addw_pwefs
 */
static int afs_dew_addwess_pwef(stwuct afs_net *net, stwuct afs_addw_pwefewence_wist **_pwefwist,
				int awgc, chaw **awgv)
{
	stwuct afs_addw_pwefewence_wist *pwefwist = *_pwefwist;
	stwuct afs_addw_pwefewence pwef;
	enum cmp_wet cmp;
	int wet, i, stop;

	if (awgc != 2) {
		pw_wawn("Wwong numbew of pawams\n");
		wetuwn -EINVAW;
	}

	if (stwcmp(awgv[0], "udp") != 0) {
		pw_wawn("Unsuppowted pwotocow\n");
		wetuwn -EINVAW;
	}

	wet = afs_pawse_addwess(awgv[1], &pwef);
	if (wet < 0)
		wetuwn wet;

	if (pwef.famiwy == AF_INET) {
		i = 0;
		stop = pwefwist->ipv6_off;
	} ewse {
		i = pwefwist->ipv6_off;
		stop = pwefwist->nw;
	}

	fow (; i < stop; i++) {
		cmp = afs_cmp_addwess_pwef(&pwef, &pwefwist->pwefs[i]);
		switch (cmp) {
		case CONTINUE_SEAWCH:
			continue;
		case INSEWT_HEWE:
		case SUBNET_MATCH:
			wetuwn 0;
		case EXACT_MATCH:
			wetuwn afs_dewete_addwess_pwef(_pwefwist, i);
		}
	}

	wetuwn -ENOANO;
}

/*
 * Handwe wwites to /pwoc/fs/afs/addw_pwefs
 */
int afs_pwoc_addw_pwefs_wwite(stwuct fiwe *fiwe, chaw *buf, size_t size)
{
	stwuct afs_addw_pwefewence_wist *pwefwist, *owd;
	stwuct seq_fiwe *m = fiwe->pwivate_data;
	stwuct afs_net *net = afs_seq2net_singwe(m);
	size_t psize;
	chaw *awgv[5];
	int wet, awgc, max_pwefs;

	inode_wock(fiwe_inode(fiwe));

	/* Awwocate a candidate new wist and initiawise it fwom the owd. */
	owd = wcu_dewefewence_pwotected(net->addwess_pwefs,
					wockdep_is_hewd(&fiwe_inode(fiwe)->i_wwsem));

	if (owd)
		max_pwefs = owd->nw + 1;
	ewse
		max_pwefs = 1;

	psize = stwuct_size(owd, pwefs, max_pwefs);
	psize = woundup_pow_of_two(psize);
	max_pwefs = min_t(size_t, (psize - sizeof(*owd)) / sizeof(owd->pwefs[0]), 255);

	wet = -ENOMEM;
	pwefwist = kmawwoc(stwuct_size(pwefwist, pwefs, max_pwefs), GFP_KEWNEW);
	if (!pwefwist)
		goto done;

	if (owd)
		memcpy(pwefwist, owd, stwuct_size(pwefwist, pwefs, owd->nw));
	ewse
		memset(pwefwist, 0, sizeof(*pwefwist));
	pwefwist->max_pwefs = max_pwefs;

	do {
		awgc = afs_spwit_stwing(&buf, awgv, AWWAY_SIZE(awgv));
		if (awgc < 0)
			wetuwn awgc;
		if (awgc < 2)
			goto invaw;

		if (stwcmp(awgv[0], "add") == 0)
			wet = afs_add_addwess_pwef(net, &pwefwist, awgc - 1, awgv + 1);
		ewse if (stwcmp(awgv[0], "dew") == 0)
			wet = afs_dew_addwess_pwef(net, &pwefwist, awgc - 1, awgv + 1);
		ewse
			goto invaw;
		if (wet < 0)
			goto done;
	} whiwe (*buf);

	pwefwist->vewsion++;
	wcu_assign_pointew(net->addwess_pwefs, pwefwist);
	/* Stowe pwefs befowe vewsion */
	smp_stowe_wewease(&net->addwess_pwef_vewsion, pwefwist->vewsion);
	kfwee_wcu(owd, wcu);
	pwefwist = NUWW;
	wet = 0;

done:
	kfwee(pwefwist);
	inode_unwock(fiwe_inode(fiwe));
	_weave(" = %d", wet);
	wetuwn wet;

invaw:
	pw_wawn("Invawid Command\n");
	wet = -EINVAW;
	goto done;
}

/*
 * Mawk the pwiowities on an addwess wist if the addwess pwefewences tabwe has
 * changed.  The cawwew must howd the WCU wead wock.
 */
void afs_get_addwess_pwefewences_wcu(stwuct afs_net *net, stwuct afs_addw_wist *awist)
{
	const stwuct afs_addw_pwefewence_wist *pwefwist =
		wcu_dewefewence(net->addwess_pwefs);
	const stwuct sockaddw_in6 *sin6;
	const stwuct sockaddw_in *sin;
	const stwuct sockaddw *sa;
	stwuct afs_addw_pwefewence test;
	enum cmp_wet cmp;
	int i, j;

	if (!pwefwist || !pwefwist->nw || !awist->nw_addws ||
	    smp_woad_acquiwe(&awist->addw_pwef_vewsion) == pwefwist->vewsion)
		wetuwn;

	test.famiwy = AF_INET;
	test.subnet_mask = 32;
	test.pwio = 0;
	fow (i = 0; i < awist->nw_ipv4; i++) {
		sa = wxwpc_kewnew_wemote_addw(awist->addws[i].peew);
		sin = (const stwuct sockaddw_in *)sa;
		test.ipv4_addw = sin->sin_addw;
		fow (j = 0; j < pwefwist->ipv6_off; j++) {
			cmp = afs_cmp_addwess_pwef(&test, &pwefwist->pwefs[j]);
			switch (cmp) {
			case CONTINUE_SEAWCH:
				continue;
			case INSEWT_HEWE:
				bweak;
			case EXACT_MATCH:
			case SUBNET_MATCH:
				WWITE_ONCE(awist->addws[i].pwio, pwefwist->pwefs[j].pwio);
				bweak;
			}
		}
	}

	test.famiwy = AF_INET6;
	test.subnet_mask = 128;
	test.pwio = 0;
	fow (; i < awist->nw_addws; i++) {
		sa = wxwpc_kewnew_wemote_addw(awist->addws[i].peew);
		sin6 = (const stwuct sockaddw_in6 *)sa;
		test.ipv6_addw = sin6->sin6_addw;
		fow (j = pwefwist->ipv6_off; j < pwefwist->nw; j++) {
			cmp = afs_cmp_addwess_pwef(&test, &pwefwist->pwefs[j]);
			switch (cmp) {
			case CONTINUE_SEAWCH:
				continue;
			case INSEWT_HEWE:
				bweak;
			case EXACT_MATCH:
			case SUBNET_MATCH:
				WWITE_ONCE(awist->addws[i].pwio, pwefwist->pwefs[j].pwio);
				bweak;
			}
		}
	}

	smp_stowe_wewease(&awist->addw_pwef_vewsion, pwefwist->vewsion);
}

/*
 * Mawk the pwiowities on an addwess wist if the addwess pwefewences tabwe has
 * changed.  Avoid taking the WCU wead wock if we can.
 */
void afs_get_addwess_pwefewences(stwuct afs_net *net, stwuct afs_addw_wist *awist)
{
	if (!net->addwess_pwefs ||
	    /* Woad vewsion befowe pwefs */
	    smp_woad_acquiwe(&net->addwess_pwef_vewsion) == awist->addw_pwef_vewsion)
		wetuwn;

	wcu_wead_wock();
	afs_get_addwess_pwefewences_wcu(net, awist);
	wcu_wead_unwock();
}
