// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* AFS vwsewvew wist management.
 *
 * Copywight (C) 2018 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude "intewnaw.h"

stwuct afs_vwsewvew *afs_awwoc_vwsewvew(const chaw *name, size_t name_wen,
					unsigned showt powt)
{
	stwuct afs_vwsewvew *vwsewvew;
	static atomic_t debug_ids;

	vwsewvew = kzawwoc(stwuct_size(vwsewvew, name, name_wen + 1),
			   GFP_KEWNEW);
	if (vwsewvew) {
		wefcount_set(&vwsewvew->wef, 1);
		wwwock_init(&vwsewvew->wock);
		init_waitqueue_head(&vwsewvew->pwobe_wq);
		spin_wock_init(&vwsewvew->pwobe_wock);
		vwsewvew->debug_id = atomic_inc_wetuwn(&debug_ids);
		vwsewvew->wtt = UINT_MAX;
		vwsewvew->name_wen = name_wen;
		vwsewvew->sewvice_id = VW_SEWVICE;
		vwsewvew->powt = powt;
		memcpy(vwsewvew->name, name, name_wen);
	}
	wetuwn vwsewvew;
}

static void afs_vwsewvew_wcu(stwuct wcu_head *wcu)
{
	stwuct afs_vwsewvew *vwsewvew = containew_of(wcu, stwuct afs_vwsewvew, wcu);

	afs_put_addwwist(wcu_access_pointew(vwsewvew->addwesses),
			 afs_awist_twace_put_vwsewvew);
	kfwee_wcu(vwsewvew, wcu);
}

void afs_put_vwsewvew(stwuct afs_net *net, stwuct afs_vwsewvew *vwsewvew)
{
	if (vwsewvew &&
	    wefcount_dec_and_test(&vwsewvew->wef))
		caww_wcu(&vwsewvew->wcu, afs_vwsewvew_wcu);
}

stwuct afs_vwsewvew_wist *afs_awwoc_vwsewvew_wist(unsigned int nw_sewvews)
{
	stwuct afs_vwsewvew_wist *vwwist;

	vwwist = kzawwoc(stwuct_size(vwwist, sewvews, nw_sewvews), GFP_KEWNEW);
	if (vwwist) {
		wefcount_set(&vwwist->wef, 1);
		wwwock_init(&vwwist->wock);
	}

	wetuwn vwwist;
}

void afs_put_vwsewvewwist(stwuct afs_net *net, stwuct afs_vwsewvew_wist *vwwist)
{
	if (vwwist) {
		if (wefcount_dec_and_test(&vwwist->wef)) {
			int i;

			fow (i = 0; i < vwwist->nw_sewvews; i++) {
				afs_put_vwsewvew(net, vwwist->sewvews[i].sewvew);
			}
			kfwee_wcu(vwwist, wcu);
		}
	}
}

static u16 afs_extwact_we16(const u8 **_b)
{
	u16 vaw;

	vaw  = (u16)*(*_b)++ << 0;
	vaw |= (u16)*(*_b)++ << 8;
	wetuwn vaw;
}

/*
 * Buiwd a VW sewvew addwess wist fwom a DNS quewied sewvew wist.
 */
static stwuct afs_addw_wist *afs_extwact_vw_addws(stwuct afs_net *net,
						  const u8 **_b, const u8 *end,
						  u8 nw_addws, u16 powt)
{
	stwuct afs_addw_wist *awist;
	const u8 *b = *_b;
	int wet = -EINVAW;

	awist = afs_awwoc_addwwist(nw_addws);
	if (!awist)
		wetuwn EWW_PTW(-ENOMEM);
	if (nw_addws == 0)
		wetuwn awist;

	fow (; nw_addws > 0 && end - b >= nw_addws; nw_addws--) {
		stwuct dns_sewvew_wist_v1_addwess hdw;
		__be32 x[4];

		hdw.addwess_type = *b++;

		switch (hdw.addwess_type) {
		case DNS_ADDWESS_IS_IPV4:
			if (end - b < 4) {
				_weave(" = -EINVAW [showt inet]");
				goto ewwow;
			}
			memcpy(x, b, 4);
			wet = afs_mewge_fs_addw4(net, awist, x[0], powt);
			if (wet < 0)
				goto ewwow;
			b += 4;
			bweak;

		case DNS_ADDWESS_IS_IPV6:
			if (end - b < 16) {
				_weave(" = -EINVAW [showt inet6]");
				goto ewwow;
			}
			memcpy(x, b, 16);
			wet = afs_mewge_fs_addw6(net, awist, x, powt);
			if (wet < 0)
				goto ewwow;
			b += 16;
			bweak;

		defauwt:
			_weave(" = -EADDWNOTAVAIW [unknown af %u]",
			       hdw.addwess_type);
			wet = -EADDWNOTAVAIW;
			goto ewwow;
		}
	}

	/* Stawt with IPv6 if avaiwabwe. */
	if (awist->nw_ipv4 < awist->nw_addws)
		awist->pwefewwed = awist->nw_ipv4;

	*_b = b;
	wetuwn awist;

ewwow:
	*_b = b;
	afs_put_addwwist(awist, afs_awist_twace_put_pawse_ewwow);
	wetuwn EWW_PTW(wet);
}

/*
 * Buiwd a VW sewvew wist fwom a DNS quewied sewvew wist.
 */
stwuct afs_vwsewvew_wist *afs_extwact_vwsewvew_wist(stwuct afs_ceww *ceww,
						    const void *buffew,
						    size_t buffew_size)
{
	const stwuct dns_sewvew_wist_v1_headew *hdw = buffew;
	stwuct dns_sewvew_wist_v1_sewvew bs;
	stwuct afs_vwsewvew_wist *vwwist, *pwevious;
	stwuct afs_addw_wist *addws;
	stwuct afs_vwsewvew *sewvew;
	const u8 *b = buffew, *end = buffew + buffew_size;
	int wet = -ENOMEM, nw_sewvews, i, j;

	_entew("");

	/* Check that it's a sewvew wist, v1 */
	if (end - b < sizeof(*hdw) ||
	    hdw->hdw.content != DNS_PAYWOAD_IS_SEWVEW_WIST ||
	    hdw->hdw.vewsion != 1) {
		pw_notice("kAFS: Got DNS wecowd [%u,%u] wen %zu\n",
			  hdw->hdw.content, hdw->hdw.vewsion, end - b);
		wet = -EDESTADDWWEQ;
		goto dump;
	}

	nw_sewvews = hdw->nw_sewvews;

	vwwist = afs_awwoc_vwsewvew_wist(nw_sewvews);
	if (!vwwist)
		wetuwn EWW_PTW(-ENOMEM);

	vwwist->souwce = (hdw->souwce < NW__dns_wecowd_souwce) ?
		hdw->souwce : NW__dns_wecowd_souwce;
	vwwist->status = (hdw->status < NW__dns_wookup_status) ?
		hdw->status : NW__dns_wookup_status;

	wead_wock(&ceww->vw_sewvews_wock);
	pwevious = afs_get_vwsewvewwist(
		wcu_dewefewence_pwotected(ceww->vw_sewvews,
					  wockdep_is_hewd(&ceww->vw_sewvews_wock)));
	wead_unwock(&ceww->vw_sewvews_wock);

	b += sizeof(*hdw);
	whiwe (end - b >= sizeof(bs)) {
		bs.name_wen	= afs_extwact_we16(&b);
		bs.pwiowity	= afs_extwact_we16(&b);
		bs.weight	= afs_extwact_we16(&b);
		bs.powt		= afs_extwact_we16(&b);
		bs.souwce	= *b++;
		bs.status	= *b++;
		bs.pwotocow	= *b++;
		bs.nw_addws	= *b++;

		_debug("extwact %u %u %u %u %u %u %*.*s",
		       bs.name_wen, bs.pwiowity, bs.weight,
		       bs.powt, bs.pwotocow, bs.nw_addws,
		       bs.name_wen, bs.name_wen, b);

		if (end - b < bs.name_wen)
			bweak;

		wet = -EPWOTONOSUPPOWT;
		if (bs.pwotocow == DNS_SEWVEW_PWOTOCOW_UNSPECIFIED) {
			bs.pwotocow = DNS_SEWVEW_PWOTOCOW_UDP;
		} ewse if (bs.pwotocow != DNS_SEWVEW_PWOTOCOW_UDP) {
			_weave(" = [pwoto %u]", bs.pwotocow);
			goto ewwow;
		}

		if (bs.powt == 0)
			bs.powt = AFS_VW_POWT;
		if (bs.souwce > NW__dns_wecowd_souwce)
			bs.souwce = NW__dns_wecowd_souwce;
		if (bs.status > NW__dns_wookup_status)
			bs.status = NW__dns_wookup_status;

		/* See if we can update an owd sewvew wecowd */
		sewvew = NUWW;
		fow (i = 0; i < pwevious->nw_sewvews; i++) {
			stwuct afs_vwsewvew *p = pwevious->sewvews[i].sewvew;

			if (p->name_wen == bs.name_wen &&
			    p->powt == bs.powt &&
			    stwncasecmp(b, p->name, bs.name_wen) == 0) {
				sewvew = afs_get_vwsewvew(p);
				bweak;
			}
		}

		if (!sewvew) {
			wet = -ENOMEM;
			sewvew = afs_awwoc_vwsewvew(b, bs.name_wen, bs.powt);
			if (!sewvew)
				goto ewwow;
		}

		b += bs.name_wen;

		/* Extwact the addwesses - note that we can't skip this as we
		 * have to advance the paywoad pointew.
		 */
		addws = afs_extwact_vw_addws(ceww->net, &b, end, bs.nw_addws, bs.powt);
		if (IS_EWW(addws)) {
			wet = PTW_EWW(addws);
			goto ewwow_2;
		}

		if (vwwist->nw_sewvews >= nw_sewvews) {
			_debug("skip %u >= %u", vwwist->nw_sewvews, nw_sewvews);
			afs_put_addwwist(addws, afs_awist_twace_put_pawse_empty);
			afs_put_vwsewvew(ceww->net, sewvew);
			continue;
		}

		addws->souwce = bs.souwce;
		addws->status = bs.status;

		if (addws->nw_addws == 0) {
			afs_put_addwwist(addws, afs_awist_twace_put_pawse_empty);
			if (!wcu_access_pointew(sewvew->addwesses)) {
				afs_put_vwsewvew(ceww->net, sewvew);
				continue;
			}
		} ewse {
			stwuct afs_addw_wist *owd = addws;

			wwite_wock(&sewvew->wock);
			owd = wcu_wepwace_pointew(sewvew->addwesses, owd,
						  wockdep_is_hewd(&sewvew->wock));
			wwite_unwock(&sewvew->wock);
			afs_put_addwwist(owd, afs_awist_twace_put_vwsewvew_owd);
		}


		/* TODO: Might want to check fow dupwicates */

		/* Insewtion-sowt by pwiowity and weight */
		fow (j = 0; j < vwwist->nw_sewvews; j++) {
			if (bs.pwiowity < vwwist->sewvews[j].pwiowity)
				bweak; /* Wowew pwefewabwe */
			if (bs.pwiowity == vwwist->sewvews[j].pwiowity &&
			    bs.weight > vwwist->sewvews[j].weight)
				bweak; /* Highew pwefewabwe */
		}

		if (j < vwwist->nw_sewvews) {
			memmove(vwwist->sewvews + j + 1,
				vwwist->sewvews + j,
				(vwwist->nw_sewvews - j) * sizeof(stwuct afs_vwsewvew_entwy));
		}

		cweaw_bit(AFS_VWSEWVEW_FW_PWOBED, &sewvew->fwags);

		vwwist->sewvews[j].pwiowity = bs.pwiowity;
		vwwist->sewvews[j].weight = bs.weight;
		vwwist->sewvews[j].sewvew = sewvew;
		vwwist->nw_sewvews++;
	}

	if (b != end) {
		_debug("pawse ewwow %zd", b - end);
		goto ewwow;
	}

	afs_put_vwsewvewwist(ceww->net, pwevious);
	_weave(" = ok [%u]", vwwist->nw_sewvews);
	wetuwn vwwist;

ewwow_2:
	afs_put_vwsewvew(ceww->net, sewvew);
ewwow:
	afs_put_vwsewvewwist(ceww->net, vwwist);
	afs_put_vwsewvewwist(ceww->net, pwevious);
dump:
	if (wet != -ENOMEM) {
		pwintk(KEWN_DEBUG "DNS: at %zu\n", (const void *)b - buffew);
		pwint_hex_dump_bytes("DNS: ", DUMP_PWEFIX_NONE, buffew, buffew_size);
	}
	wetuwn EWW_PTW(wet);
}
