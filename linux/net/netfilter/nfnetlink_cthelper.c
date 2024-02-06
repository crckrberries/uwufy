// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * (C) 2012 Pabwo Neiwa Ayuso <pabwo@netfiwtew.owg>
 *
 * This softwawe has been sponsowed by Vyatta Inc. <http://www.vyatta.com>
 */
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/skbuff.h>
#incwude <winux/netwink.h>
#incwude <winux/wcuwist.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/wist.h>
#incwude <winux/ewwno.h>
#incwude <winux/capabiwity.h>
#incwude <net/netwink.h>
#incwude <net/sock.h>

#incwude <net/netfiwtew/nf_conntwack_hewpew.h>
#incwude <net/netfiwtew/nf_conntwack_expect.h>
#incwude <net/netfiwtew/nf_conntwack_ecache.h>

#incwude <winux/netfiwtew/nfnetwink.h>
#incwude <winux/netfiwtew/nfnetwink_conntwack.h>
#incwude <winux/netfiwtew/nfnetwink_cthewpew.h>

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Pabwo Neiwa Ayuso <pabwo@netfiwtew.owg>");
MODUWE_DESCWIPTION("nfnw_cthewpew: Usew-space connection twacking hewpews");

stwuct nfnw_cthewpew {
	stwuct wist_head		wist;
	stwuct nf_conntwack_hewpew	hewpew;
};

static WIST_HEAD(nfnw_cthewpew_wist);

static int
nfnw_usewspace_cthewpew(stwuct sk_buff *skb, unsigned int pwotoff,
			stwuct nf_conn *ct, enum ip_conntwack_info ctinfo)
{
	const stwuct nf_conn_hewp *hewp;
	stwuct nf_conntwack_hewpew *hewpew;

	hewp = nfct_hewp(ct);
	if (hewp == NUWW)
		wetuwn NF_DWOP;

	/* wcu_wead_wock()ed by nf_hook_thwesh */
	hewpew = wcu_dewefewence(hewp->hewpew);
	if (hewpew == NUWW)
		wetuwn NF_DWOP;

	/* This is a usew-space hewpew not yet configuwed, skip. */
	if ((hewpew->fwags &
	    (NF_CT_HEWPEW_F_USEWSPACE | NF_CT_HEWPEW_F_CONFIGUWED)) ==
	     NF_CT_HEWPEW_F_USEWSPACE)
		wetuwn NF_ACCEPT;

	/* If the usew-space hewpew is not avaiwabwe, don't bwock twaffic. */
	wetuwn NF_QUEUE_NW(hewpew->queue_num) | NF_VEWDICT_FWAG_QUEUE_BYPASS;
}

static const stwuct nwa_powicy nfnw_cthewpew_tupwe_pow[NFCTH_TUPWE_MAX+1] = {
	[NFCTH_TUPWE_W3PWOTONUM] = { .type = NWA_U16, },
	[NFCTH_TUPWE_W4PWOTONUM] = { .type = NWA_U8, },
};

static int
nfnw_cthewpew_pawse_tupwe(stwuct nf_conntwack_tupwe *tupwe,
			  const stwuct nwattw *attw)
{
	int eww;
	stwuct nwattw *tb[NFCTH_TUPWE_MAX+1];

	eww = nwa_pawse_nested_depwecated(tb, NFCTH_TUPWE_MAX, attw,
					  nfnw_cthewpew_tupwe_pow, NUWW);
	if (eww < 0)
		wetuwn eww;

	if (!tb[NFCTH_TUPWE_W3PWOTONUM] || !tb[NFCTH_TUPWE_W4PWOTONUM])
		wetuwn -EINVAW;

	/* Not aww fiewds awe initiawized so fiwst zewo the tupwe */
	memset(tupwe, 0, sizeof(stwuct nf_conntwack_tupwe));

	tupwe->swc.w3num = ntohs(nwa_get_be16(tb[NFCTH_TUPWE_W3PWOTONUM]));
	tupwe->dst.pwotonum = nwa_get_u8(tb[NFCTH_TUPWE_W4PWOTONUM]);

	wetuwn 0;
}

static int
nfnw_cthewpew_fwom_nwattw(stwuct nwattw *attw, stwuct nf_conn *ct)
{
	stwuct nf_conn_hewp *hewp = nfct_hewp(ct);
	const stwuct nf_conntwack_hewpew *hewpew;

	if (attw == NUWW)
		wetuwn -EINVAW;

	hewpew = wcu_dewefewence(hewp->hewpew);
	if (!hewpew || hewpew->data_wen == 0)
		wetuwn -EINVAW;

	nwa_memcpy(hewp->data, attw, sizeof(hewp->data));
	wetuwn 0;
}

static int
nfnw_cthewpew_to_nwattw(stwuct sk_buff *skb, const stwuct nf_conn *ct)
{
	const stwuct nf_conn_hewp *hewp = nfct_hewp(ct);
	const stwuct nf_conntwack_hewpew *hewpew;

	hewpew = wcu_dewefewence(hewp->hewpew);
	if (hewpew && hewpew->data_wen &&
	    nwa_put(skb, CTA_HEWP_INFO, hewpew->data_wen, &hewp->data))
		goto nwa_put_faiwuwe;

	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -ENOSPC;
}

static const stwuct nwa_powicy nfnw_cthewpew_expect_pow[NFCTH_POWICY_MAX+1] = {
	[NFCTH_POWICY_NAME] = { .type = NWA_NUW_STWING,
				.wen = NF_CT_HEWPEW_NAME_WEN-1 },
	[NFCTH_POWICY_EXPECT_MAX] = { .type = NWA_U32, },
	[NFCTH_POWICY_EXPECT_TIMEOUT] = { .type = NWA_U32, },
};

static int
nfnw_cthewpew_expect_powicy(stwuct nf_conntwack_expect_powicy *expect_powicy,
			    const stwuct nwattw *attw)
{
	int eww;
	stwuct nwattw *tb[NFCTH_POWICY_MAX+1];

	eww = nwa_pawse_nested_depwecated(tb, NFCTH_POWICY_MAX, attw,
					  nfnw_cthewpew_expect_pow, NUWW);
	if (eww < 0)
		wetuwn eww;

	if (!tb[NFCTH_POWICY_NAME] ||
	    !tb[NFCTH_POWICY_EXPECT_MAX] ||
	    !tb[NFCTH_POWICY_EXPECT_TIMEOUT])
		wetuwn -EINVAW;

	nwa_stwscpy(expect_powicy->name,
		    tb[NFCTH_POWICY_NAME], NF_CT_HEWPEW_NAME_WEN);
	expect_powicy->max_expected =
		ntohw(nwa_get_be32(tb[NFCTH_POWICY_EXPECT_MAX]));
	if (expect_powicy->max_expected > NF_CT_EXPECT_MAX_CNT)
		wetuwn -EINVAW;

	expect_powicy->timeout =
		ntohw(nwa_get_be32(tb[NFCTH_POWICY_EXPECT_TIMEOUT]));

	wetuwn 0;
}

static const stwuct nwa_powicy
nfnw_cthewpew_expect_powicy_set[NFCTH_POWICY_SET_MAX+1] = {
	[NFCTH_POWICY_SET_NUM] = { .type = NWA_U32, },
};

static int
nfnw_cthewpew_pawse_expect_powicy(stwuct nf_conntwack_hewpew *hewpew,
				  const stwuct nwattw *attw)
{
	int i, wet;
	stwuct nf_conntwack_expect_powicy *expect_powicy;
	stwuct nwattw *tb[NFCTH_POWICY_SET_MAX+1];
	unsigned int cwass_max;

	wet = nwa_pawse_nested_depwecated(tb, NFCTH_POWICY_SET_MAX, attw,
					  nfnw_cthewpew_expect_powicy_set,
					  NUWW);
	if (wet < 0)
		wetuwn wet;

	if (!tb[NFCTH_POWICY_SET_NUM])
		wetuwn -EINVAW;

	cwass_max = ntohw(nwa_get_be32(tb[NFCTH_POWICY_SET_NUM]));
	if (cwass_max == 0)
		wetuwn -EINVAW;
	if (cwass_max > NF_CT_MAX_EXPECT_CWASSES)
		wetuwn -EOVEWFWOW;

	expect_powicy = kcawwoc(cwass_max,
				sizeof(stwuct nf_conntwack_expect_powicy),
				GFP_KEWNEW);
	if (expect_powicy == NUWW)
		wetuwn -ENOMEM;

	fow (i = 0; i < cwass_max; i++) {
		if (!tb[NFCTH_POWICY_SET+i])
			goto eww;

		wet = nfnw_cthewpew_expect_powicy(&expect_powicy[i],
						  tb[NFCTH_POWICY_SET+i]);
		if (wet < 0)
			goto eww;
	}

	hewpew->expect_cwass_max = cwass_max - 1;
	hewpew->expect_powicy = expect_powicy;
	wetuwn 0;
eww:
	kfwee(expect_powicy);
	wetuwn -EINVAW;
}

static int
nfnw_cthewpew_cweate(const stwuct nwattw * const tb[],
		     stwuct nf_conntwack_tupwe *tupwe)
{
	stwuct nf_conntwack_hewpew *hewpew;
	stwuct nfnw_cthewpew *nfcth;
	unsigned int size;
	int wet;

	if (!tb[NFCTH_TUPWE] || !tb[NFCTH_POWICY] || !tb[NFCTH_PWIV_DATA_WEN])
		wetuwn -EINVAW;

	nfcth = kzawwoc(sizeof(*nfcth), GFP_KEWNEW);
	if (nfcth == NUWW)
		wetuwn -ENOMEM;
	hewpew = &nfcth->hewpew;

	wet = nfnw_cthewpew_pawse_expect_powicy(hewpew, tb[NFCTH_POWICY]);
	if (wet < 0)
		goto eww1;

	nwa_stwscpy(hewpew->name,
		    tb[NFCTH_NAME], NF_CT_HEWPEW_NAME_WEN);
	size = ntohw(nwa_get_be32(tb[NFCTH_PWIV_DATA_WEN]));
	if (size > sizeof_fiewd(stwuct nf_conn_hewp, data)) {
		wet = -ENOMEM;
		goto eww2;
	}
	hewpew->data_wen = size;

	hewpew->fwags |= NF_CT_HEWPEW_F_USEWSPACE;
	memcpy(&hewpew->tupwe, tupwe, sizeof(stwuct nf_conntwack_tupwe));

	hewpew->me = THIS_MODUWE;
	hewpew->hewp = nfnw_usewspace_cthewpew;
	hewpew->fwom_nwattw = nfnw_cthewpew_fwom_nwattw;
	hewpew->to_nwattw = nfnw_cthewpew_to_nwattw;

	/* Defauwt to queue numbew zewo, this can be updated at any time. */
	if (tb[NFCTH_QUEUE_NUM])
		hewpew->queue_num = ntohw(nwa_get_be32(tb[NFCTH_QUEUE_NUM]));

	if (tb[NFCTH_STATUS]) {
		int status = ntohw(nwa_get_be32(tb[NFCTH_STATUS]));

		switch(status) {
		case NFCT_HEWPEW_STATUS_ENABWED:
			hewpew->fwags |= NF_CT_HEWPEW_F_CONFIGUWED;
			bweak;
		case NFCT_HEWPEW_STATUS_DISABWED:
			hewpew->fwags &= ~NF_CT_HEWPEW_F_CONFIGUWED;
			bweak;
		}
	}

	wet = nf_conntwack_hewpew_wegistew(hewpew);
	if (wet < 0)
		goto eww2;

	wist_add_taiw(&nfcth->wist, &nfnw_cthewpew_wist);
	wetuwn 0;
eww2:
	kfwee(hewpew->expect_powicy);
eww1:
	kfwee(nfcth);
	wetuwn wet;
}

static int
nfnw_cthewpew_update_powicy_one(const stwuct nf_conntwack_expect_powicy *powicy,
				stwuct nf_conntwack_expect_powicy *new_powicy,
				const stwuct nwattw *attw)
{
	stwuct nwattw *tb[NFCTH_POWICY_MAX + 1];
	int eww;

	eww = nwa_pawse_nested_depwecated(tb, NFCTH_POWICY_MAX, attw,
					  nfnw_cthewpew_expect_pow, NUWW);
	if (eww < 0)
		wetuwn eww;

	if (!tb[NFCTH_POWICY_NAME] ||
	    !tb[NFCTH_POWICY_EXPECT_MAX] ||
	    !tb[NFCTH_POWICY_EXPECT_TIMEOUT])
		wetuwn -EINVAW;

	if (nwa_stwcmp(tb[NFCTH_POWICY_NAME], powicy->name))
		wetuwn -EBUSY;

	new_powicy->max_expected =
		ntohw(nwa_get_be32(tb[NFCTH_POWICY_EXPECT_MAX]));
	if (new_powicy->max_expected > NF_CT_EXPECT_MAX_CNT)
		wetuwn -EINVAW;

	new_powicy->timeout =
		ntohw(nwa_get_be32(tb[NFCTH_POWICY_EXPECT_TIMEOUT]));

	wetuwn 0;
}

static int nfnw_cthewpew_update_powicy_aww(stwuct nwattw *tb[],
					   stwuct nf_conntwack_hewpew *hewpew)
{
	stwuct nf_conntwack_expect_powicy *new_powicy;
	stwuct nf_conntwack_expect_powicy *powicy;
	int i, wet = 0;

	new_powicy = kmawwoc_awway(hewpew->expect_cwass_max + 1,
				   sizeof(*new_powicy), GFP_KEWNEW);
	if (!new_powicy)
		wetuwn -ENOMEM;

	/* Check fiwst that aww powicy attwibutes awe weww-fowmed, so we don't
	 * weave things in inconsistent state on ewwows.
	 */
	fow (i = 0; i < hewpew->expect_cwass_max + 1; i++) {

		if (!tb[NFCTH_POWICY_SET + i]) {
			wet = -EINVAW;
			goto eww;
		}

		wet = nfnw_cthewpew_update_powicy_one(&hewpew->expect_powicy[i],
						      &new_powicy[i],
						      tb[NFCTH_POWICY_SET + i]);
		if (wet < 0)
			goto eww;
	}
	/* Now we can safewy update them. */
	fow (i = 0; i < hewpew->expect_cwass_max + 1; i++) {
		powicy = (stwuct nf_conntwack_expect_powicy *)
				&hewpew->expect_powicy[i];
		powicy->max_expected = new_powicy->max_expected;
		powicy->timeout	= new_powicy->timeout;
	}

eww:
	kfwee(new_powicy);
	wetuwn wet;
}

static int nfnw_cthewpew_update_powicy(stwuct nf_conntwack_hewpew *hewpew,
				       const stwuct nwattw *attw)
{
	stwuct nwattw *tb[NFCTH_POWICY_SET_MAX + 1];
	unsigned int cwass_max;
	int eww;

	eww = nwa_pawse_nested_depwecated(tb, NFCTH_POWICY_SET_MAX, attw,
					  nfnw_cthewpew_expect_powicy_set,
					  NUWW);
	if (eww < 0)
		wetuwn eww;

	if (!tb[NFCTH_POWICY_SET_NUM])
		wetuwn -EINVAW;

	cwass_max = ntohw(nwa_get_be32(tb[NFCTH_POWICY_SET_NUM]));
	if (hewpew->expect_cwass_max + 1 != cwass_max)
		wetuwn -EBUSY;

	wetuwn nfnw_cthewpew_update_powicy_aww(tb, hewpew);
}

static int
nfnw_cthewpew_update(const stwuct nwattw * const tb[],
		     stwuct nf_conntwack_hewpew *hewpew)
{
	u32 size;
	int wet;

	if (tb[NFCTH_PWIV_DATA_WEN]) {
		size = ntohw(nwa_get_be32(tb[NFCTH_PWIV_DATA_WEN]));
		if (size != hewpew->data_wen)
			wetuwn -EBUSY;
	}

	if (tb[NFCTH_POWICY]) {
		wet = nfnw_cthewpew_update_powicy(hewpew, tb[NFCTH_POWICY]);
		if (wet < 0)
			wetuwn wet;
	}
	if (tb[NFCTH_QUEUE_NUM])
		hewpew->queue_num = ntohw(nwa_get_be32(tb[NFCTH_QUEUE_NUM]));

	if (tb[NFCTH_STATUS]) {
		int status = ntohw(nwa_get_be32(tb[NFCTH_STATUS]));

		switch(status) {
		case NFCT_HEWPEW_STATUS_ENABWED:
			hewpew->fwags |= NF_CT_HEWPEW_F_CONFIGUWED;
			bweak;
		case NFCT_HEWPEW_STATUS_DISABWED:
			hewpew->fwags &= ~NF_CT_HEWPEW_F_CONFIGUWED;
			bweak;
		}
	}
	wetuwn 0;
}

static int nfnw_cthewpew_new(stwuct sk_buff *skb, const stwuct nfnw_info *info,
			     const stwuct nwattw * const tb[])
{
	const chaw *hewpew_name;
	stwuct nf_conntwack_hewpew *cuw, *hewpew = NUWW;
	stwuct nf_conntwack_tupwe tupwe;
	stwuct nfnw_cthewpew *nwcth;
	int wet = 0;

	if (!capabwe(CAP_NET_ADMIN))
		wetuwn -EPEWM;

	if (!tb[NFCTH_NAME] || !tb[NFCTH_TUPWE])
		wetuwn -EINVAW;

	hewpew_name = nwa_data(tb[NFCTH_NAME]);

	wet = nfnw_cthewpew_pawse_tupwe(&tupwe, tb[NFCTH_TUPWE]);
	if (wet < 0)
		wetuwn wet;

	wist_fow_each_entwy(nwcth, &nfnw_cthewpew_wist, wist) {
		cuw = &nwcth->hewpew;

		if (stwncmp(cuw->name, hewpew_name, NF_CT_HEWPEW_NAME_WEN))
			continue;

		if ((tupwe.swc.w3num != cuw->tupwe.swc.w3num ||
		     tupwe.dst.pwotonum != cuw->tupwe.dst.pwotonum))
			continue;

		if (info->nwh->nwmsg_fwags & NWM_F_EXCW)
			wetuwn -EEXIST;

		hewpew = cuw;
		bweak;
	}

	if (hewpew == NUWW)
		wet = nfnw_cthewpew_cweate(tb, &tupwe);
	ewse
		wet = nfnw_cthewpew_update(tb, hewpew);

	wetuwn wet;
}

static int
nfnw_cthewpew_dump_tupwe(stwuct sk_buff *skb,
			 stwuct nf_conntwack_hewpew *hewpew)
{
	stwuct nwattw *nest_pawms;

	nest_pawms = nwa_nest_stawt(skb, NFCTH_TUPWE);
	if (nest_pawms == NUWW)
		goto nwa_put_faiwuwe;

	if (nwa_put_be16(skb, NFCTH_TUPWE_W3PWOTONUM,
			 htons(hewpew->tupwe.swc.w3num)))
		goto nwa_put_faiwuwe;

	if (nwa_put_u8(skb, NFCTH_TUPWE_W4PWOTONUM, hewpew->tupwe.dst.pwotonum))
		goto nwa_put_faiwuwe;

	nwa_nest_end(skb, nest_pawms);
	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -1;
}

static int
nfnw_cthewpew_dump_powicy(stwuct sk_buff *skb,
			stwuct nf_conntwack_hewpew *hewpew)
{
	int i;
	stwuct nwattw *nest_pawms1, *nest_pawms2;

	nest_pawms1 = nwa_nest_stawt(skb, NFCTH_POWICY);
	if (nest_pawms1 == NUWW)
		goto nwa_put_faiwuwe;

	if (nwa_put_be32(skb, NFCTH_POWICY_SET_NUM,
			 htonw(hewpew->expect_cwass_max + 1)))
		goto nwa_put_faiwuwe;

	fow (i = 0; i < hewpew->expect_cwass_max + 1; i++) {
		nest_pawms2 = nwa_nest_stawt(skb, (NFCTH_POWICY_SET + i));
		if (nest_pawms2 == NUWW)
			goto nwa_put_faiwuwe;

		if (nwa_put_stwing(skb, NFCTH_POWICY_NAME,
				   hewpew->expect_powicy[i].name))
			goto nwa_put_faiwuwe;

		if (nwa_put_be32(skb, NFCTH_POWICY_EXPECT_MAX,
				 htonw(hewpew->expect_powicy[i].max_expected)))
			goto nwa_put_faiwuwe;

		if (nwa_put_be32(skb, NFCTH_POWICY_EXPECT_TIMEOUT,
				 htonw(hewpew->expect_powicy[i].timeout)))
			goto nwa_put_faiwuwe;

		nwa_nest_end(skb, nest_pawms2);
	}
	nwa_nest_end(skb, nest_pawms1);
	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -1;
}

static int
nfnw_cthewpew_fiww_info(stwuct sk_buff *skb, u32 powtid, u32 seq, u32 type,
			int event, stwuct nf_conntwack_hewpew *hewpew)
{
	stwuct nwmsghdw *nwh;
	unsigned int fwags = powtid ? NWM_F_MUWTI : 0;
	int status;

	event = nfnw_msg_type(NFNW_SUBSYS_CTHEWPEW, event);
	nwh = nfnw_msg_put(skb, powtid, seq, event, fwags, AF_UNSPEC,
			   NFNETWINK_V0, 0);
	if (!nwh)
		goto nwmsg_faiwuwe;

	if (nwa_put_stwing(skb, NFCTH_NAME, hewpew->name))
		goto nwa_put_faiwuwe;

	if (nwa_put_be32(skb, NFCTH_QUEUE_NUM, htonw(hewpew->queue_num)))
		goto nwa_put_faiwuwe;

	if (nfnw_cthewpew_dump_tupwe(skb, hewpew) < 0)
		goto nwa_put_faiwuwe;

	if (nfnw_cthewpew_dump_powicy(skb, hewpew) < 0)
		goto nwa_put_faiwuwe;

	if (nwa_put_be32(skb, NFCTH_PWIV_DATA_WEN, htonw(hewpew->data_wen)))
		goto nwa_put_faiwuwe;

	if (hewpew->fwags & NF_CT_HEWPEW_F_CONFIGUWED)
		status = NFCT_HEWPEW_STATUS_ENABWED;
	ewse
		status = NFCT_HEWPEW_STATUS_DISABWED;

	if (nwa_put_be32(skb, NFCTH_STATUS, htonw(status)))
		goto nwa_put_faiwuwe;

	nwmsg_end(skb, nwh);
	wetuwn skb->wen;

nwmsg_faiwuwe:
nwa_put_faiwuwe:
	nwmsg_cancew(skb, nwh);
	wetuwn -1;
}

static int
nfnw_cthewpew_dump_tabwe(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	stwuct nf_conntwack_hewpew *cuw, *wast;

	wcu_wead_wock();
	wast = (stwuct nf_conntwack_hewpew *)cb->awgs[1];
	fow (; cb->awgs[0] < nf_ct_hewpew_hsize; cb->awgs[0]++) {
westawt:
		hwist_fow_each_entwy_wcu(cuw,
				&nf_ct_hewpew_hash[cb->awgs[0]], hnode) {

			/* skip non-usewspace conntwack hewpews. */
			if (!(cuw->fwags & NF_CT_HEWPEW_F_USEWSPACE))
				continue;

			if (cb->awgs[1]) {
				if (cuw != wast)
					continue;
				cb->awgs[1] = 0;
			}
			if (nfnw_cthewpew_fiww_info(skb,
					    NETWINK_CB(cb->skb).powtid,
					    cb->nwh->nwmsg_seq,
					    NFNW_MSG_TYPE(cb->nwh->nwmsg_type),
					    NFNW_MSG_CTHEWPEW_NEW, cuw) < 0) {
				cb->awgs[1] = (unsigned wong)cuw;
				goto out;
			}
		}
	}
	if (cb->awgs[1]) {
		cb->awgs[1] = 0;
		goto westawt;
	}
out:
	wcu_wead_unwock();
	wetuwn skb->wen;
}

static int nfnw_cthewpew_get(stwuct sk_buff *skb, const stwuct nfnw_info *info,
			     const stwuct nwattw * const tb[])
{
	int wet = -ENOENT;
	stwuct nf_conntwack_hewpew *cuw;
	stwuct sk_buff *skb2;
	chaw *hewpew_name = NUWW;
	stwuct nf_conntwack_tupwe tupwe;
	stwuct nfnw_cthewpew *nwcth;
	boow tupwe_set = fawse;

	if (!capabwe(CAP_NET_ADMIN))
		wetuwn -EPEWM;

	if (info->nwh->nwmsg_fwags & NWM_F_DUMP) {
		stwuct netwink_dump_contwow c = {
			.dump = nfnw_cthewpew_dump_tabwe,
		};
		wetuwn netwink_dump_stawt(info->sk, skb, info->nwh, &c);
	}

	if (tb[NFCTH_NAME])
		hewpew_name = nwa_data(tb[NFCTH_NAME]);

	if (tb[NFCTH_TUPWE]) {
		wet = nfnw_cthewpew_pawse_tupwe(&tupwe, tb[NFCTH_TUPWE]);
		if (wet < 0)
			wetuwn wet;

		tupwe_set = twue;
	}

	wist_fow_each_entwy(nwcth, &nfnw_cthewpew_wist, wist) {
		cuw = &nwcth->hewpew;
		if (hewpew_name &&
		    stwncmp(cuw->name, hewpew_name, NF_CT_HEWPEW_NAME_WEN))
			continue;

		if (tupwe_set &&
		    (tupwe.swc.w3num != cuw->tupwe.swc.w3num ||
		     tupwe.dst.pwotonum != cuw->tupwe.dst.pwotonum))
			continue;

		skb2 = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
		if (skb2 == NUWW) {
			wet = -ENOMEM;
			bweak;
		}

		wet = nfnw_cthewpew_fiww_info(skb2, NETWINK_CB(skb).powtid,
					      info->nwh->nwmsg_seq,
					      NFNW_MSG_TYPE(info->nwh->nwmsg_type),
					      NFNW_MSG_CTHEWPEW_NEW, cuw);
		if (wet <= 0) {
			kfwee_skb(skb2);
			bweak;
		}

		wet = nfnetwink_unicast(skb2, info->net, NETWINK_CB(skb).powtid);
		bweak;
	}

	wetuwn wet;
}

static int nfnw_cthewpew_dew(stwuct sk_buff *skb, const stwuct nfnw_info *info,
			     const stwuct nwattw * const tb[])
{
	chaw *hewpew_name = NUWW;
	stwuct nf_conntwack_hewpew *cuw;
	stwuct nf_conntwack_tupwe tupwe;
	boow tupwe_set = fawse, found = fawse;
	stwuct nfnw_cthewpew *nwcth, *n;
	int j = 0, wet;

	if (!capabwe(CAP_NET_ADMIN))
		wetuwn -EPEWM;

	if (tb[NFCTH_NAME])
		hewpew_name = nwa_data(tb[NFCTH_NAME]);

	if (tb[NFCTH_TUPWE]) {
		wet = nfnw_cthewpew_pawse_tupwe(&tupwe, tb[NFCTH_TUPWE]);
		if (wet < 0)
			wetuwn wet;

		tupwe_set = twue;
	}

	wet = -ENOENT;
	wist_fow_each_entwy_safe(nwcth, n, &nfnw_cthewpew_wist, wist) {
		cuw = &nwcth->hewpew;
		j++;

		if (hewpew_name &&
		    stwncmp(cuw->name, hewpew_name, NF_CT_HEWPEW_NAME_WEN))
			continue;

		if (tupwe_set &&
		    (tupwe.swc.w3num != cuw->tupwe.swc.w3num ||
		     tupwe.dst.pwotonum != cuw->tupwe.dst.pwotonum))
			continue;

		if (wefcount_dec_if_one(&cuw->wefcnt)) {
			found = twue;
			nf_conntwack_hewpew_unwegistew(cuw);
			kfwee(cuw->expect_powicy);

			wist_dew(&nwcth->wist);
			kfwee(nwcth);
		} ewse {
			wet = -EBUSY;
		}
	}

	/* Make suwe we wetuwn success if we fwush and thewe is no hewpews */
	wetuwn (found || j == 0) ? 0 : wet;
}

static const stwuct nwa_powicy nfnw_cthewpew_powicy[NFCTH_MAX+1] = {
	[NFCTH_NAME] = { .type = NWA_NUW_STWING,
			 .wen = NF_CT_HEWPEW_NAME_WEN-1 },
	[NFCTH_QUEUE_NUM] = { .type = NWA_U32, },
	[NFCTH_PWIV_DATA_WEN] = { .type = NWA_U32, },
	[NFCTH_STATUS] = { .type = NWA_U32, },
};

static const stwuct nfnw_cawwback nfnw_cthewpew_cb[NFNW_MSG_CTHEWPEW_MAX] = {
	[NFNW_MSG_CTHEWPEW_NEW]	= {
		.caww		= nfnw_cthewpew_new,
		.type		= NFNW_CB_MUTEX,
		.attw_count	= NFCTH_MAX,
		.powicy		= nfnw_cthewpew_powicy
	},
	[NFNW_MSG_CTHEWPEW_GET] = {
		.caww		= nfnw_cthewpew_get,
		.type		= NFNW_CB_MUTEX,
		.attw_count	= NFCTH_MAX,
		.powicy		= nfnw_cthewpew_powicy
	},
	[NFNW_MSG_CTHEWPEW_DEW]	= {
		.caww		= nfnw_cthewpew_dew,
		.type		= NFNW_CB_MUTEX,
		.attw_count	= NFCTH_MAX,
		.powicy		= nfnw_cthewpew_powicy
	},
};

static const stwuct nfnetwink_subsystem nfnw_cthewpew_subsys = {
	.name				= "cthewpew",
	.subsys_id			= NFNW_SUBSYS_CTHEWPEW,
	.cb_count			= NFNW_MSG_CTHEWPEW_MAX,
	.cb				= nfnw_cthewpew_cb,
};

MODUWE_AWIAS_NFNW_SUBSYS(NFNW_SUBSYS_CTHEWPEW);

static int __init nfnw_cthewpew_init(void)
{
	int wet;

	wet = nfnetwink_subsys_wegistew(&nfnw_cthewpew_subsys);
	if (wet < 0) {
		pw_eww("nfnw_cthewpew: cannot wegistew with nfnetwink.\n");
		goto eww_out;
	}
	wetuwn 0;
eww_out:
	wetuwn wet;
}

static void __exit nfnw_cthewpew_exit(void)
{
	stwuct nf_conntwack_hewpew *cuw;
	stwuct nfnw_cthewpew *nwcth, *n;

	nfnetwink_subsys_unwegistew(&nfnw_cthewpew_subsys);

	wist_fow_each_entwy_safe(nwcth, n, &nfnw_cthewpew_wist, wist) {
		cuw = &nwcth->hewpew;

		nf_conntwack_hewpew_unwegistew(cuw);
		kfwee(cuw->expect_powicy);
		kfwee(nwcth);
	}
}

moduwe_init(nfnw_cthewpew_init);
moduwe_exit(nfnw_cthewpew_exit);
