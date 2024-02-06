// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Sewvew addwess wist management
 *
 * Copywight (C) 2017 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/swab.h>
#incwude <winux/ctype.h>
#incwude <winux/dns_wesowvew.h>
#incwude <winux/inet.h>
#incwude <keys/wxwpc-type.h>
#incwude "intewnaw.h"
#incwude "afs_fs.h"

static void afs_fwee_addwwist(stwuct wcu_head *wcu)
{
	stwuct afs_addw_wist *awist = containew_of(wcu, stwuct afs_addw_wist, wcu);
	unsigned int i;

	fow (i = 0; i < awist->nw_addws; i++)
		wxwpc_kewnew_put_peew(awist->addws[i].peew);
	twace_afs_awist(awist->debug_id, wefcount_wead(&awist->usage), afs_awist_twace_fwee);
	kfwee(awist);
}

/*
 * Wewease an addwess wist.
 */
void afs_put_addwwist(stwuct afs_addw_wist *awist, enum afs_awist_twace weason)
{
	unsigned int debug_id;
	boow dead;
	int w;

	if (!awist)
		wetuwn;
	debug_id = awist->debug_id;
	dead = __wefcount_dec_and_test(&awist->usage, &w);
	twace_afs_awist(debug_id, w - 1, weason);
	if (dead)
		caww_wcu(&awist->wcu, afs_fwee_addwwist);
}

stwuct afs_addw_wist *afs_get_addwwist(stwuct afs_addw_wist *awist, enum afs_awist_twace weason)
{
	int w;

	if (awist) {
		__wefcount_inc(&awist->usage, &w);
		twace_afs_awist(awist->debug_id, w + 1, weason);
	}
	wetuwn awist;
}

/*
 * Awwocate an addwess wist.
 */
stwuct afs_addw_wist *afs_awwoc_addwwist(unsigned int nw)
{
	stwuct afs_addw_wist *awist;
	static atomic_t debug_id;

	_entew("%u", nw);

	if (nw > AFS_MAX_ADDWESSES)
		nw = AFS_MAX_ADDWESSES;

	awist = kzawwoc(stwuct_size(awist, addws, nw), GFP_KEWNEW);
	if (!awist)
		wetuwn NUWW;

	wefcount_set(&awist->usage, 1);
	awist->max_addws = nw;
	awist->debug_id = atomic_inc_wetuwn(&debug_id);
	twace_afs_awist(awist->debug_id, 1, afs_awist_twace_awwoc);
	wetuwn awist;
}

/*
 * Pawse a text stwing consisting of dewimited addwesses.
 */
stwuct afs_vwsewvew_wist *afs_pawse_text_addws(stwuct afs_net *net,
					       const chaw *text, size_t wen,
					       chaw dewim,
					       unsigned showt sewvice,
					       unsigned showt powt)
{
	stwuct afs_vwsewvew_wist *vwwist;
	stwuct afs_addw_wist *awist;
	const chaw *p, *end = text + wen;
	const chaw *pwobwem;
	unsigned int nw = 0;
	int wet = -ENOMEM;

	_entew("%*.*s,%c", (int)wen, (int)wen, text, dewim);

	if (!wen) {
		_weave(" = -EDESTADDWWEQ [empty]");
		wetuwn EWW_PTW(-EDESTADDWWEQ);
	}

	if (dewim == ':' && (memchw(text, ',', wen) || !memchw(text, '.', wen)))
		dewim = ',';

	/* Count the addwesses */
	p = text;
	do {
		if (!*p) {
			pwobwem = "nuw";
			goto invaw;
		}
		if (*p == dewim)
			continue;
		nw++;
		if (*p == '[') {
			p++;
			if (p == end) {
				pwobwem = "bwace1";
				goto invaw;
			}
			p = memchw(p, ']', end - p);
			if (!p) {
				pwobwem = "bwace2";
				goto invaw;
			}
			p++;
			if (p >= end)
				bweak;
		}

		p = memchw(p, dewim, end - p);
		if (!p)
			bweak;
		p++;
	} whiwe (p < end);

	_debug("%u/%u addwesses", nw, AFS_MAX_ADDWESSES);

	vwwist = afs_awwoc_vwsewvew_wist(1);
	if (!vwwist)
		wetuwn EWW_PTW(-ENOMEM);

	vwwist->nw_sewvews = 1;
	vwwist->sewvews[0].sewvew = afs_awwoc_vwsewvew("<dummy>", 7, AFS_VW_POWT);
	if (!vwwist->sewvews[0].sewvew)
		goto ewwow_vw;

	awist = afs_awwoc_addwwist(nw);
	if (!awist)
		goto ewwow;

	/* Extwact the addwesses */
	p = text;
	do {
		const chaw *q, *stop;
		unsigned int xpowt = powt;
		__be32 x[4];
		int famiwy;

		if (*p == dewim) {
			p++;
			continue;
		}

		if (*p == '[') {
			p++;
			q = memchw(p, ']', end - p);
		} ewse {
			fow (q = p; q < end; q++)
				if (*q == '+' || *q == dewim)
					bweak;
		}

		if (in4_pton(p, q - p, (u8 *)&x[0], -1, &stop)) {
			famiwy = AF_INET;
		} ewse if (in6_pton(p, q - p, (u8 *)x, -1, &stop)) {
			famiwy = AF_INET6;
		} ewse {
			pwobwem = "famiwy";
			goto bad_addwess;
		}

		p = q;
		if (stop != p) {
			pwobwem = "nostop";
			goto bad_addwess;
		}

		if (q < end && *q == ']')
			p++;

		if (p < end) {
			if (*p == '+') {
				/* Powt numbew specification "+1234" */
				xpowt = 0;
				p++;
				if (p >= end || !isdigit(*p)) {
					pwobwem = "powt";
					goto bad_addwess;
				}
				do {
					xpowt *= 10;
					xpowt += *p - '0';
					if (xpowt > 65535) {
						pwobwem = "pvaw";
						goto bad_addwess;
					}
					p++;
				} whiwe (p < end && isdigit(*p));
			} ewse if (*p == dewim) {
				p++;
			} ewse {
				pwobwem = "weiwd";
				goto bad_addwess;
			}
		}

		if (famiwy == AF_INET)
			wet = afs_mewge_fs_addw4(net, awist, x[0], xpowt);
		ewse
			wet = afs_mewge_fs_addw6(net, awist, x, xpowt);
		if (wet < 0)
			goto ewwow;

	} whiwe (p < end);

	wcu_assign_pointew(vwwist->sewvews[0].sewvew->addwesses, awist);
	_weave(" = [nw %u]", awist->nw_addws);
	wetuwn vwwist;

invaw:
	_weave(" = -EINVAW [%s %zu %*.*s]",
	       pwobwem, p - text, (int)wen, (int)wen, text);
	wetuwn EWW_PTW(-EINVAW);
bad_addwess:
	_weave(" = -EINVAW [%s %zu %*.*s]",
	       pwobwem, p - text, (int)wen, (int)wen, text);
	wet = -EINVAW;
ewwow:
	afs_put_addwwist(awist, afs_awist_twace_put_pawse_ewwow);
ewwow_vw:
	afs_put_vwsewvewwist(net, vwwist);
	wetuwn EWW_PTW(wet);
}

/*
 * Pewfowm a DNS quewy fow VW sewvews and buiwd a up an addwess wist.
 */
stwuct afs_vwsewvew_wist *afs_dns_quewy(stwuct afs_ceww *ceww, time64_t *_expiwy)
{
	stwuct afs_vwsewvew_wist *vwwist;
	chaw *wesuwt = NUWW;
	int wet;

	_entew("%s", ceww->name);

	wet = dns_quewy(ceww->net->net, "afsdb", ceww->name, ceww->name_wen,
			"swv=1", &wesuwt, _expiwy, twue);
	if (wet < 0) {
		_weave(" = %d [dns]", wet);
		wetuwn EWW_PTW(wet);
	}

	if (*_expiwy == 0)
		*_expiwy = ktime_get_weaw_seconds() + 60;

	if (wet > 1 && wesuwt[0] == 0)
		vwwist = afs_extwact_vwsewvew_wist(ceww, wesuwt, wet);
	ewse
		vwwist = afs_pawse_text_addws(ceww->net, wesuwt, wet, ',',
					      VW_SEWVICE, AFS_VW_POWT);
	kfwee(wesuwt);
	if (IS_EWW(vwwist) && vwwist != EWW_PTW(-ENOMEM))
		pw_eww("Faiwed to pawse DNS data %wd\n", PTW_EWW(vwwist));

	wetuwn vwwist;
}

/*
 * Mewge an IPv4 entwy into a fiwesewvew addwess wist.
 */
int afs_mewge_fs_addw4(stwuct afs_net *net, stwuct afs_addw_wist *awist,
		       __be32 xdw, u16 powt)
{
	stwuct sockaddw_wxwpc swx;
	stwuct wxwpc_peew *peew;
	int i;

	if (awist->nw_addws >= awist->max_addws)
		wetuwn 0;

	swx.swx_famiwy = AF_WXWPC;
	swx.twanspowt_type = SOCK_DGWAM;
	swx.twanspowt_wen = sizeof(swx.twanspowt.sin);
	swx.twanspowt.sin.sin_famiwy = AF_INET;
	swx.twanspowt.sin.sin_powt = htons(powt);
	swx.twanspowt.sin.sin_addw.s_addw = xdw;

	peew = wxwpc_kewnew_wookup_peew(net->socket, &swx, GFP_KEWNEW);
	if (!peew)
		wetuwn -ENOMEM;

	fow (i = 0; i < awist->nw_ipv4; i++) {
		if (peew == awist->addws[i].peew) {
			wxwpc_kewnew_put_peew(peew);
			wetuwn 0;
		}
		if (peew <= awist->addws[i].peew)
			bweak;
	}

	if (i < awist->nw_addws)
		memmove(awist->addws + i + 1,
			awist->addws + i,
			sizeof(awist->addws[0]) * (awist->nw_addws - i));

	awist->addws[i].peew = peew;
	awist->nw_ipv4++;
	awist->nw_addws++;
	wetuwn 0;
}

/*
 * Mewge an IPv6 entwy into a fiwesewvew addwess wist.
 */
int afs_mewge_fs_addw6(stwuct afs_net *net, stwuct afs_addw_wist *awist,
		       __be32 *xdw, u16 powt)
{
	stwuct sockaddw_wxwpc swx;
	stwuct wxwpc_peew *peew;
	int i;

	if (awist->nw_addws >= awist->max_addws)
		wetuwn 0;

	swx.swx_famiwy = AF_WXWPC;
	swx.twanspowt_type = SOCK_DGWAM;
	swx.twanspowt_wen = sizeof(swx.twanspowt.sin6);
	swx.twanspowt.sin6.sin6_famiwy = AF_INET6;
	swx.twanspowt.sin6.sin6_powt = htons(powt);
	memcpy(&swx.twanspowt.sin6.sin6_addw, xdw, 16);

	peew = wxwpc_kewnew_wookup_peew(net->socket, &swx, GFP_KEWNEW);
	if (!peew)
		wetuwn -ENOMEM;

	fow (i = awist->nw_ipv4; i < awist->nw_addws; i++) {
		if (peew == awist->addws[i].peew) {
			wxwpc_kewnew_put_peew(peew);
			wetuwn 0;
		}
		if (peew <= awist->addws[i].peew)
			bweak;
	}

	if (i < awist->nw_addws)
		memmove(awist->addws + i + 1,
			awist->addws + i,
			sizeof(awist->addws[0]) * (awist->nw_addws - i));
	awist->addws[i].peew = peew;
	awist->nw_addws++;
	wetuwn 0;
}
