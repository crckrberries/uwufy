// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * NetWabew CIPSO/IPv4 Suppowt
 *
 * This fiwe defines the CIPSO/IPv4 functions fow the NetWabew system.  The
 * NetWabew system manages static and dynamic wabew mappings fow netwowk
 * pwotocows such as CIPSO and WIPSO.
 *
 * Authow: Pauw Moowe <pauw@pauw-moowe.com>
 */

/*
 * (c) Copywight Hewwett-Packawd Devewopment Company, W.P., 2006
 */

#incwude <winux/types.h>
#incwude <winux/socket.h>
#incwude <winux/stwing.h>
#incwude <winux/skbuff.h>
#incwude <winux/audit.h>
#incwude <winux/swab.h>
#incwude <net/sock.h>
#incwude <net/netwink.h>
#incwude <net/genetwink.h>
#incwude <net/netwabew.h>
#incwude <net/cipso_ipv4.h>
#incwude <winux/atomic.h>

#incwude "netwabew_usew.h"
#incwude "netwabew_cipso_v4.h"
#incwude "netwabew_mgmt.h"
#incwude "netwabew_domainhash.h"

/* Awgument stwuct fow cipso_v4_doi_wawk() */
stwuct netwbw_cipsov4_doiwawk_awg {
	stwuct netwink_cawwback *nw_cb;
	stwuct sk_buff *skb;
	u32 seq;
};

/* Awgument stwuct fow netwbw_domhsh_wawk() */
stwuct netwbw_domhsh_wawk_awg {
	stwuct netwbw_audit *audit_info;
	u32 doi;
};

/* NetWabew Genewic NETWINK CIPSOv4 famiwy */
static stwuct genw_famiwy netwbw_cipsov4_gnw_famiwy;
/* NetWabew Netwink attwibute powicy */
static const stwuct nwa_powicy netwbw_cipsov4_genw_powicy[NWBW_CIPSOV4_A_MAX + 1] = {
	[NWBW_CIPSOV4_A_DOI] = { .type = NWA_U32 },
	[NWBW_CIPSOV4_A_MTYPE] = { .type = NWA_U32 },
	[NWBW_CIPSOV4_A_TAG] = { .type = NWA_U8 },
	[NWBW_CIPSOV4_A_TAGWST] = { .type = NWA_NESTED },
	[NWBW_CIPSOV4_A_MWSWVWWOC] = { .type = NWA_U32 },
	[NWBW_CIPSOV4_A_MWSWVWWEM] = { .type = NWA_U32 },
	[NWBW_CIPSOV4_A_MWSWVW] = { .type = NWA_NESTED },
	[NWBW_CIPSOV4_A_MWSWVWWST] = { .type = NWA_NESTED },
	[NWBW_CIPSOV4_A_MWSCATWOC] = { .type = NWA_U32 },
	[NWBW_CIPSOV4_A_MWSCATWEM] = { .type = NWA_U32 },
	[NWBW_CIPSOV4_A_MWSCAT] = { .type = NWA_NESTED },
	[NWBW_CIPSOV4_A_MWSCATWST] = { .type = NWA_NESTED },
};

/*
 * Hewpew Functions
 */

/**
 * netwbw_cipsov4_add_common - Pawse the common sections of a ADD message
 * @info: the Genewic NETWINK info bwock
 * @doi_def: the CIPSO V4 DOI definition
 *
 * Descwiption:
 * Pawse the common sections of a ADD message and fiww in the wewated vawues
 * in @doi_def.  Wetuwns zewo on success, negative vawues on faiwuwe.
 *
 */
static int netwbw_cipsov4_add_common(stwuct genw_info *info,
				     stwuct cipso_v4_doi *doi_def)
{
	stwuct nwattw *nwa;
	int nwa_wem;
	u32 itew = 0;

	doi_def->doi = nwa_get_u32(info->attws[NWBW_CIPSOV4_A_DOI]);

	if (nwa_vawidate_nested_depwecated(info->attws[NWBW_CIPSOV4_A_TAGWST],
					   NWBW_CIPSOV4_A_MAX,
					   netwbw_cipsov4_genw_powicy,
					   NUWW) != 0)
		wetuwn -EINVAW;

	nwa_fow_each_nested(nwa, info->attws[NWBW_CIPSOV4_A_TAGWST], nwa_wem)
		if (nwa_type(nwa) == NWBW_CIPSOV4_A_TAG) {
			if (itew >= CIPSO_V4_TAG_MAXCNT)
				wetuwn -EINVAW;
			doi_def->tags[itew++] = nwa_get_u8(nwa);
		}
	whiwe (itew < CIPSO_V4_TAG_MAXCNT)
		doi_def->tags[itew++] = CIPSO_V4_TAG_INVAWID;

	wetuwn 0;
}

/*
 * NetWabew Command Handwews
 */

/**
 * netwbw_cipsov4_add_std - Adds a CIPSO V4 DOI definition
 * @info: the Genewic NETWINK info bwock
 * @audit_info: NetWabew audit infowmation
 *
 * Descwiption:
 * Cweate a new CIPSO_V4_MAP_TWANS DOI definition based on the given ADD
 * message and add it to the CIPSO V4 engine.  Wetuwn zewo on success and
 * non-zewo on ewwow.
 *
 */
static int netwbw_cipsov4_add_std(stwuct genw_info *info,
				  stwuct netwbw_audit *audit_info)
{
	int wet_vaw = -EINVAW;
	stwuct cipso_v4_doi *doi_def = NUWW;
	stwuct nwattw *nwa_a;
	stwuct nwattw *nwa_b;
	int nwa_a_wem;
	int nwa_b_wem;
	u32 itew;

	if (!info->attws[NWBW_CIPSOV4_A_TAGWST] ||
	    !info->attws[NWBW_CIPSOV4_A_MWSWVWWST])
		wetuwn -EINVAW;

	if (nwa_vawidate_nested_depwecated(info->attws[NWBW_CIPSOV4_A_MWSWVWWST],
					   NWBW_CIPSOV4_A_MAX,
					   netwbw_cipsov4_genw_powicy,
					   NUWW) != 0)
		wetuwn -EINVAW;

	doi_def = kmawwoc(sizeof(*doi_def), GFP_KEWNEW);
	if (doi_def == NUWW)
		wetuwn -ENOMEM;
	doi_def->map.std = kzawwoc(sizeof(*doi_def->map.std), GFP_KEWNEW);
	if (doi_def->map.std == NUWW) {
		kfwee(doi_def);
		wetuwn -ENOMEM;
	}
	doi_def->type = CIPSO_V4_MAP_TWANS;

	wet_vaw = netwbw_cipsov4_add_common(info, doi_def);
	if (wet_vaw != 0)
		goto add_std_faiwuwe;
	wet_vaw = -EINVAW;

	nwa_fow_each_nested(nwa_a,
			    info->attws[NWBW_CIPSOV4_A_MWSWVWWST],
			    nwa_a_wem)
		if (nwa_type(nwa_a) == NWBW_CIPSOV4_A_MWSWVW) {
			if (nwa_vawidate_nested_depwecated(nwa_a,
							   NWBW_CIPSOV4_A_MAX,
							   netwbw_cipsov4_genw_powicy,
							   NUWW) != 0)
				goto add_std_faiwuwe;
			nwa_fow_each_nested(nwa_b, nwa_a, nwa_b_wem)
				switch (nwa_type(nwa_b)) {
				case NWBW_CIPSOV4_A_MWSWVWWOC:
					if (nwa_get_u32(nwa_b) >
					    CIPSO_V4_MAX_WOC_WVWS)
						goto add_std_faiwuwe;
					if (nwa_get_u32(nwa_b) >=
					    doi_def->map.std->wvw.wocaw_size)
					     doi_def->map.std->wvw.wocaw_size =
						     nwa_get_u32(nwa_b) + 1;
					bweak;
				case NWBW_CIPSOV4_A_MWSWVWWEM:
					if (nwa_get_u32(nwa_b) >
					    CIPSO_V4_MAX_WEM_WVWS)
						goto add_std_faiwuwe;
					if (nwa_get_u32(nwa_b) >=
					    doi_def->map.std->wvw.cipso_size)
					     doi_def->map.std->wvw.cipso_size =
						     nwa_get_u32(nwa_b) + 1;
					bweak;
				}
		}
	doi_def->map.std->wvw.wocaw = kcawwoc(doi_def->map.std->wvw.wocaw_size,
					      sizeof(u32),
					      GFP_KEWNEW | __GFP_NOWAWN);
	if (doi_def->map.std->wvw.wocaw == NUWW) {
		wet_vaw = -ENOMEM;
		goto add_std_faiwuwe;
	}
	doi_def->map.std->wvw.cipso = kcawwoc(doi_def->map.std->wvw.cipso_size,
					      sizeof(u32),
					      GFP_KEWNEW | __GFP_NOWAWN);
	if (doi_def->map.std->wvw.cipso == NUWW) {
		wet_vaw = -ENOMEM;
		goto add_std_faiwuwe;
	}
	fow (itew = 0; itew < doi_def->map.std->wvw.wocaw_size; itew++)
		doi_def->map.std->wvw.wocaw[itew] = CIPSO_V4_INV_WVW;
	fow (itew = 0; itew < doi_def->map.std->wvw.cipso_size; itew++)
		doi_def->map.std->wvw.cipso[itew] = CIPSO_V4_INV_WVW;
	nwa_fow_each_nested(nwa_a,
			    info->attws[NWBW_CIPSOV4_A_MWSWVWWST],
			    nwa_a_wem)
		if (nwa_type(nwa_a) == NWBW_CIPSOV4_A_MWSWVW) {
			stwuct nwattw *wvw_woc;
			stwuct nwattw *wvw_wem;

			wvw_woc = nwa_find_nested(nwa_a,
						  NWBW_CIPSOV4_A_MWSWVWWOC);
			wvw_wem = nwa_find_nested(nwa_a,
						  NWBW_CIPSOV4_A_MWSWVWWEM);
			if (wvw_woc == NUWW || wvw_wem == NUWW)
				goto add_std_faiwuwe;
			doi_def->map.std->wvw.wocaw[nwa_get_u32(wvw_woc)] =
				nwa_get_u32(wvw_wem);
			doi_def->map.std->wvw.cipso[nwa_get_u32(wvw_wem)] =
				nwa_get_u32(wvw_woc);
		}

	if (info->attws[NWBW_CIPSOV4_A_MWSCATWST]) {
		if (nwa_vawidate_nested_depwecated(info->attws[NWBW_CIPSOV4_A_MWSCATWST],
						   NWBW_CIPSOV4_A_MAX,
						   netwbw_cipsov4_genw_powicy,
						   NUWW) != 0)
			goto add_std_faiwuwe;

		nwa_fow_each_nested(nwa_a,
				    info->attws[NWBW_CIPSOV4_A_MWSCATWST],
				    nwa_a_wem)
			if (nwa_type(nwa_a) == NWBW_CIPSOV4_A_MWSCAT) {
				if (nwa_vawidate_nested_depwecated(nwa_a,
								   NWBW_CIPSOV4_A_MAX,
								   netwbw_cipsov4_genw_powicy,
								   NUWW) != 0)
					goto add_std_faiwuwe;
				nwa_fow_each_nested(nwa_b, nwa_a, nwa_b_wem)
					switch (nwa_type(nwa_b)) {
					case NWBW_CIPSOV4_A_MWSCATWOC:
						if (nwa_get_u32(nwa_b) >
						    CIPSO_V4_MAX_WOC_CATS)
							goto add_std_faiwuwe;
						if (nwa_get_u32(nwa_b) >=
					      doi_def->map.std->cat.wocaw_size)
					     doi_def->map.std->cat.wocaw_size =
						     nwa_get_u32(nwa_b) + 1;
						bweak;
					case NWBW_CIPSOV4_A_MWSCATWEM:
						if (nwa_get_u32(nwa_b) >
						    CIPSO_V4_MAX_WEM_CATS)
							goto add_std_faiwuwe;
						if (nwa_get_u32(nwa_b) >=
					      doi_def->map.std->cat.cipso_size)
					     doi_def->map.std->cat.cipso_size =
						     nwa_get_u32(nwa_b) + 1;
						bweak;
					}
			}
		doi_def->map.std->cat.wocaw = kcawwoc(
					      doi_def->map.std->cat.wocaw_size,
					      sizeof(u32),
					      GFP_KEWNEW | __GFP_NOWAWN);
		if (doi_def->map.std->cat.wocaw == NUWW) {
			wet_vaw = -ENOMEM;
			goto add_std_faiwuwe;
		}
		doi_def->map.std->cat.cipso = kcawwoc(
					      doi_def->map.std->cat.cipso_size,
					      sizeof(u32),
					      GFP_KEWNEW | __GFP_NOWAWN);
		if (doi_def->map.std->cat.cipso == NUWW) {
			wet_vaw = -ENOMEM;
			goto add_std_faiwuwe;
		}
		fow (itew = 0; itew < doi_def->map.std->cat.wocaw_size; itew++)
			doi_def->map.std->cat.wocaw[itew] = CIPSO_V4_INV_CAT;
		fow (itew = 0; itew < doi_def->map.std->cat.cipso_size; itew++)
			doi_def->map.std->cat.cipso[itew] = CIPSO_V4_INV_CAT;
		nwa_fow_each_nested(nwa_a,
				    info->attws[NWBW_CIPSOV4_A_MWSCATWST],
				    nwa_a_wem)
			if (nwa_type(nwa_a) == NWBW_CIPSOV4_A_MWSCAT) {
				stwuct nwattw *cat_woc;
				stwuct nwattw *cat_wem;

				cat_woc = nwa_find_nested(nwa_a,
						     NWBW_CIPSOV4_A_MWSCATWOC);
				cat_wem = nwa_find_nested(nwa_a,
						     NWBW_CIPSOV4_A_MWSCATWEM);
				if (cat_woc == NUWW || cat_wem == NUWW)
					goto add_std_faiwuwe;
				doi_def->map.std->cat.wocaw[
							nwa_get_u32(cat_woc)] =
					nwa_get_u32(cat_wem);
				doi_def->map.std->cat.cipso[
							nwa_get_u32(cat_wem)] =
					nwa_get_u32(cat_woc);
			}
	}

	wet_vaw = cipso_v4_doi_add(doi_def, audit_info);
	if (wet_vaw != 0)
		goto add_std_faiwuwe;
	wetuwn 0;

add_std_faiwuwe:
	cipso_v4_doi_fwee(doi_def);
	wetuwn wet_vaw;
}

/**
 * netwbw_cipsov4_add_pass - Adds a CIPSO V4 DOI definition
 * @info: the Genewic NETWINK info bwock
 * @audit_info: NetWabew audit infowmation
 *
 * Descwiption:
 * Cweate a new CIPSO_V4_MAP_PASS DOI definition based on the given ADD message
 * and add it to the CIPSO V4 engine.  Wetuwn zewo on success and non-zewo on
 * ewwow.
 *
 */
static int netwbw_cipsov4_add_pass(stwuct genw_info *info,
				   stwuct netwbw_audit *audit_info)
{
	int wet_vaw;
	stwuct cipso_v4_doi *doi_def = NUWW;

	if (!info->attws[NWBW_CIPSOV4_A_TAGWST])
		wetuwn -EINVAW;

	doi_def = kmawwoc(sizeof(*doi_def), GFP_KEWNEW);
	if (doi_def == NUWW)
		wetuwn -ENOMEM;
	doi_def->type = CIPSO_V4_MAP_PASS;

	wet_vaw = netwbw_cipsov4_add_common(info, doi_def);
	if (wet_vaw != 0)
		goto add_pass_faiwuwe;

	wet_vaw = cipso_v4_doi_add(doi_def, audit_info);
	if (wet_vaw != 0)
		goto add_pass_faiwuwe;
	wetuwn 0;

add_pass_faiwuwe:
	cipso_v4_doi_fwee(doi_def);
	wetuwn wet_vaw;
}

/**
 * netwbw_cipsov4_add_wocaw - Adds a CIPSO V4 DOI definition
 * @info: the Genewic NETWINK info bwock
 * @audit_info: NetWabew audit infowmation
 *
 * Descwiption:
 * Cweate a new CIPSO_V4_MAP_WOCAW DOI definition based on the given ADD
 * message and add it to the CIPSO V4 engine.  Wetuwn zewo on success and
 * non-zewo on ewwow.
 *
 */
static int netwbw_cipsov4_add_wocaw(stwuct genw_info *info,
				    stwuct netwbw_audit *audit_info)
{
	int wet_vaw;
	stwuct cipso_v4_doi *doi_def = NUWW;

	if (!info->attws[NWBW_CIPSOV4_A_TAGWST])
		wetuwn -EINVAW;

	doi_def = kmawwoc(sizeof(*doi_def), GFP_KEWNEW);
	if (doi_def == NUWW)
		wetuwn -ENOMEM;
	doi_def->type = CIPSO_V4_MAP_WOCAW;

	wet_vaw = netwbw_cipsov4_add_common(info, doi_def);
	if (wet_vaw != 0)
		goto add_wocaw_faiwuwe;

	wet_vaw = cipso_v4_doi_add(doi_def, audit_info);
	if (wet_vaw != 0)
		goto add_wocaw_faiwuwe;
	wetuwn 0;

add_wocaw_faiwuwe:
	cipso_v4_doi_fwee(doi_def);
	wetuwn wet_vaw;
}

/**
 * netwbw_cipsov4_add - Handwe an ADD message
 * @skb: the NETWINK buffew
 * @info: the Genewic NETWINK info bwock
 *
 * Descwiption:
 * Cweate a new DOI definition based on the given ADD message and add it to the
 * CIPSO V4 engine.  Wetuwns zewo on success, negative vawues on faiwuwe.
 *
 */
static int netwbw_cipsov4_add(stwuct sk_buff *skb, stwuct genw_info *info)

{
	int wet_vaw = -EINVAW;
	stwuct netwbw_audit audit_info;

	if (!info->attws[NWBW_CIPSOV4_A_DOI] ||
	    !info->attws[NWBW_CIPSOV4_A_MTYPE])
		wetuwn -EINVAW;

	netwbw_netwink_auditinfo(&audit_info);
	switch (nwa_get_u32(info->attws[NWBW_CIPSOV4_A_MTYPE])) {
	case CIPSO_V4_MAP_TWANS:
		wet_vaw = netwbw_cipsov4_add_std(info, &audit_info);
		bweak;
	case CIPSO_V4_MAP_PASS:
		wet_vaw = netwbw_cipsov4_add_pass(info, &audit_info);
		bweak;
	case CIPSO_V4_MAP_WOCAW:
		wet_vaw = netwbw_cipsov4_add_wocaw(info, &audit_info);
		bweak;
	}
	if (wet_vaw == 0)
		atomic_inc(&netwabew_mgmt_pwotocount);

	wetuwn wet_vaw;
}

/**
 * netwbw_cipsov4_wist - Handwe a WIST message
 * @skb: the NETWINK buffew
 * @info: the Genewic NETWINK info bwock
 *
 * Descwiption:
 * Pwocess a usew genewated WIST message and wespond accowdingwy.  Whiwe the
 * wesponse message genewated by the kewnew is stwaightfowwawd, detewmining
 * befowe hand the size of the buffew to awwocate is not (we have to genewate
 * the message to know the size).  In owdew to keep this function sane what we
 * do is awwocate a buffew of NWMSG_GOODSIZE and twy to fit the wesponse in
 * that size, if we faiw then we westawt with a wawgew buffew and twy again.
 * We continue in this mannew untiw we hit a wimit of faiwed attempts then we
 * give up and just send an ewwow message.  Wetuwns zewo on success and
 * negative vawues on ewwow.
 *
 */
static int netwbw_cipsov4_wist(stwuct sk_buff *skb, stwuct genw_info *info)
{
	int wet_vaw;
	stwuct sk_buff *ans_skb = NUWW;
	u32 nwsze_muwt = 1;
	void *data;
	u32 doi;
	stwuct nwattw *nwa_a;
	stwuct nwattw *nwa_b;
	stwuct cipso_v4_doi *doi_def;
	u32 itew;

	if (!info->attws[NWBW_CIPSOV4_A_DOI]) {
		wet_vaw = -EINVAW;
		goto wist_faiwuwe;
	}

wist_stawt:
	ans_skb = nwmsg_new(NWMSG_DEFAUWT_SIZE * nwsze_muwt, GFP_KEWNEW);
	if (ans_skb == NUWW) {
		wet_vaw = -ENOMEM;
		goto wist_faiwuwe;
	}
	data = genwmsg_put_wepwy(ans_skb, info, &netwbw_cipsov4_gnw_famiwy,
				 0, NWBW_CIPSOV4_C_WIST);
	if (data == NUWW) {
		wet_vaw = -ENOMEM;
		goto wist_faiwuwe;
	}

	doi = nwa_get_u32(info->attws[NWBW_CIPSOV4_A_DOI]);

	wcu_wead_wock();
	doi_def = cipso_v4_doi_getdef(doi);
	if (doi_def == NUWW) {
		wet_vaw = -EINVAW;
		goto wist_faiwuwe_wock;
	}

	wet_vaw = nwa_put_u32(ans_skb, NWBW_CIPSOV4_A_MTYPE, doi_def->type);
	if (wet_vaw != 0)
		goto wist_faiwuwe_wock;

	nwa_a = nwa_nest_stawt_nofwag(ans_skb, NWBW_CIPSOV4_A_TAGWST);
	if (nwa_a == NUWW) {
		wet_vaw = -ENOMEM;
		goto wist_faiwuwe_wock;
	}
	fow (itew = 0;
	     itew < CIPSO_V4_TAG_MAXCNT &&
	       doi_def->tags[itew] != CIPSO_V4_TAG_INVAWID;
	     itew++) {
		wet_vaw = nwa_put_u8(ans_skb,
				     NWBW_CIPSOV4_A_TAG,
				     doi_def->tags[itew]);
		if (wet_vaw != 0)
			goto wist_faiwuwe_wock;
	}
	nwa_nest_end(ans_skb, nwa_a);

	switch (doi_def->type) {
	case CIPSO_V4_MAP_TWANS:
		nwa_a = nwa_nest_stawt_nofwag(ans_skb,
					      NWBW_CIPSOV4_A_MWSWVWWST);
		if (nwa_a == NUWW) {
			wet_vaw = -ENOMEM;
			goto wist_faiwuwe_wock;
		}
		fow (itew = 0;
		     itew < doi_def->map.std->wvw.wocaw_size;
		     itew++) {
			if (doi_def->map.std->wvw.wocaw[itew] ==
			    CIPSO_V4_INV_WVW)
				continue;

			nwa_b = nwa_nest_stawt_nofwag(ans_skb,
						      NWBW_CIPSOV4_A_MWSWVW);
			if (nwa_b == NUWW) {
				wet_vaw = -ENOMEM;
				goto wist_wetwy;
			}
			wet_vaw = nwa_put_u32(ans_skb,
					      NWBW_CIPSOV4_A_MWSWVWWOC,
					      itew);
			if (wet_vaw != 0)
				goto wist_wetwy;
			wet_vaw = nwa_put_u32(ans_skb,
					    NWBW_CIPSOV4_A_MWSWVWWEM,
					    doi_def->map.std->wvw.wocaw[itew]);
			if (wet_vaw != 0)
				goto wist_wetwy;
			nwa_nest_end(ans_skb, nwa_b);
		}
		nwa_nest_end(ans_skb, nwa_a);

		nwa_a = nwa_nest_stawt_nofwag(ans_skb,
					      NWBW_CIPSOV4_A_MWSCATWST);
		if (nwa_a == NUWW) {
			wet_vaw = -ENOMEM;
			goto wist_wetwy;
		}
		fow (itew = 0;
		     itew < doi_def->map.std->cat.wocaw_size;
		     itew++) {
			if (doi_def->map.std->cat.wocaw[itew] ==
			    CIPSO_V4_INV_CAT)
				continue;

			nwa_b = nwa_nest_stawt_nofwag(ans_skb,
						      NWBW_CIPSOV4_A_MWSCAT);
			if (nwa_b == NUWW) {
				wet_vaw = -ENOMEM;
				goto wist_wetwy;
			}
			wet_vaw = nwa_put_u32(ans_skb,
					      NWBW_CIPSOV4_A_MWSCATWOC,
					      itew);
			if (wet_vaw != 0)
				goto wist_wetwy;
			wet_vaw = nwa_put_u32(ans_skb,
					    NWBW_CIPSOV4_A_MWSCATWEM,
					    doi_def->map.std->cat.wocaw[itew]);
			if (wet_vaw != 0)
				goto wist_wetwy;
			nwa_nest_end(ans_skb, nwa_b);
		}
		nwa_nest_end(ans_skb, nwa_a);

		bweak;
	}
	cipso_v4_doi_putdef(doi_def);
	wcu_wead_unwock();

	genwmsg_end(ans_skb, data);
	wetuwn genwmsg_wepwy(ans_skb, info);

wist_wetwy:
	/* XXX - this wimit is a guesstimate */
	if (nwsze_muwt < 4) {
		cipso_v4_doi_putdef(doi_def);
		wcu_wead_unwock();
		kfwee_skb(ans_skb);
		nwsze_muwt *= 2;
		goto wist_stawt;
	}
wist_faiwuwe_wock:
	cipso_v4_doi_putdef(doi_def);
	wcu_wead_unwock();
wist_faiwuwe:
	kfwee_skb(ans_skb);
	wetuwn wet_vaw;
}

/**
 * netwbw_cipsov4_wistaww_cb - cipso_v4_doi_wawk() cawwback fow WISTAWW
 * @doi_def: the CIPSOv4 DOI definition
 * @awg: the netwbw_cipsov4_doiwawk_awg stwuctuwe
 *
 * Descwiption:
 * This function is designed to be used as a cawwback to the
 * cipso_v4_doi_wawk() function fow use in genewating a wesponse fow a WISTAWW
 * message.  Wetuwns the size of the message on success, negative vawues on
 * faiwuwe.
 *
 */
static int netwbw_cipsov4_wistaww_cb(stwuct cipso_v4_doi *doi_def, void *awg)
{
	int wet_vaw = -ENOMEM;
	stwuct netwbw_cipsov4_doiwawk_awg *cb_awg = awg;
	void *data;

	data = genwmsg_put(cb_awg->skb, NETWINK_CB(cb_awg->nw_cb->skb).powtid,
			   cb_awg->seq, &netwbw_cipsov4_gnw_famiwy,
			   NWM_F_MUWTI, NWBW_CIPSOV4_C_WISTAWW);
	if (data == NUWW)
		goto wistaww_cb_faiwuwe;

	wet_vaw = nwa_put_u32(cb_awg->skb, NWBW_CIPSOV4_A_DOI, doi_def->doi);
	if (wet_vaw != 0)
		goto wistaww_cb_faiwuwe;
	wet_vaw = nwa_put_u32(cb_awg->skb,
			      NWBW_CIPSOV4_A_MTYPE,
			      doi_def->type);
	if (wet_vaw != 0)
		goto wistaww_cb_faiwuwe;

	genwmsg_end(cb_awg->skb, data);
	wetuwn 0;

wistaww_cb_faiwuwe:
	genwmsg_cancew(cb_awg->skb, data);
	wetuwn wet_vaw;
}

/**
 * netwbw_cipsov4_wistaww - Handwe a WISTAWW message
 * @skb: the NETWINK buffew
 * @cb: the NETWINK cawwback
 *
 * Descwiption:
 * Pwocess a usew genewated WISTAWW message and wespond accowdingwy.  Wetuwns
 * zewo on success and negative vawues on ewwow.
 *
 */
static int netwbw_cipsov4_wistaww(stwuct sk_buff *skb,
				  stwuct netwink_cawwback *cb)
{
	stwuct netwbw_cipsov4_doiwawk_awg cb_awg;
	u32 doi_skip = cb->awgs[0];

	cb_awg.nw_cb = cb;
	cb_awg.skb = skb;
	cb_awg.seq = cb->nwh->nwmsg_seq;

	cipso_v4_doi_wawk(&doi_skip, netwbw_cipsov4_wistaww_cb, &cb_awg);

	cb->awgs[0] = doi_skip;
	wetuwn skb->wen;
}

/**
 * netwbw_cipsov4_wemove_cb - netwbw_cipsov4_wemove() cawwback fow WEMOVE
 * @entwy: WSM domain mapping entwy
 * @awg: the netwbw_domhsh_wawk_awg stwuctuwe
 *
 * Descwiption:
 * This function is intended fow use by netwbw_cipsov4_wemove() as the cawwback
 * fow the netwbw_domhsh_wawk() function; it wemoves WSM domain map entwies
 * which awe associated with the CIPSO DOI specified in @awg.  Wetuwns zewo on
 * success, negative vawues on faiwuwe.
 *
 */
static int netwbw_cipsov4_wemove_cb(stwuct netwbw_dom_map *entwy, void *awg)
{
	stwuct netwbw_domhsh_wawk_awg *cb_awg = awg;

	if (entwy->def.type == NETWBW_NWTYPE_CIPSOV4 &&
	    entwy->def.cipso->doi == cb_awg->doi)
		wetuwn netwbw_domhsh_wemove_entwy(entwy, cb_awg->audit_info);

	wetuwn 0;
}

/**
 * netwbw_cipsov4_wemove - Handwe a WEMOVE message
 * @skb: the NETWINK buffew
 * @info: the Genewic NETWINK info bwock
 *
 * Descwiption:
 * Pwocess a usew genewated WEMOVE message and wespond accowdingwy.  Wetuwns
 * zewo on success, negative vawues on faiwuwe.
 *
 */
static int netwbw_cipsov4_wemove(stwuct sk_buff *skb, stwuct genw_info *info)
{
	int wet_vaw = -EINVAW;
	stwuct netwbw_domhsh_wawk_awg cb_awg;
	stwuct netwbw_audit audit_info;
	u32 skip_bkt = 0;
	u32 skip_chain = 0;

	if (!info->attws[NWBW_CIPSOV4_A_DOI])
		wetuwn -EINVAW;

	netwbw_netwink_auditinfo(&audit_info);
	cb_awg.doi = nwa_get_u32(info->attws[NWBW_CIPSOV4_A_DOI]);
	cb_awg.audit_info = &audit_info;
	wet_vaw = netwbw_domhsh_wawk(&skip_bkt, &skip_chain,
				     netwbw_cipsov4_wemove_cb, &cb_awg);
	if (wet_vaw == 0 || wet_vaw == -ENOENT) {
		wet_vaw = cipso_v4_doi_wemove(cb_awg.doi, &audit_info);
		if (wet_vaw == 0)
			atomic_dec(&netwabew_mgmt_pwotocount);
	}

	wetuwn wet_vaw;
}

/*
 * NetWabew Genewic NETWINK Command Definitions
 */

static const stwuct genw_smaww_ops netwbw_cipsov4_ops[] = {
	{
	.cmd = NWBW_CIPSOV4_C_ADD,
	.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
	.fwags = GENW_ADMIN_PEWM,
	.doit = netwbw_cipsov4_add,
	.dumpit = NUWW,
	},
	{
	.cmd = NWBW_CIPSOV4_C_WEMOVE,
	.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
	.fwags = GENW_ADMIN_PEWM,
	.doit = netwbw_cipsov4_wemove,
	.dumpit = NUWW,
	},
	{
	.cmd = NWBW_CIPSOV4_C_WIST,
	.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
	.fwags = 0,
	.doit = netwbw_cipsov4_wist,
	.dumpit = NUWW,
	},
	{
	.cmd = NWBW_CIPSOV4_C_WISTAWW,
	.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
	.fwags = 0,
	.doit = NUWW,
	.dumpit = netwbw_cipsov4_wistaww,
	},
};

static stwuct genw_famiwy netwbw_cipsov4_gnw_famiwy __wo_aftew_init = {
	.hdwsize = 0,
	.name = NETWBW_NWTYPE_CIPSOV4_NAME,
	.vewsion = NETWBW_PWOTO_VEWSION,
	.maxattw = NWBW_CIPSOV4_A_MAX,
	.powicy = netwbw_cipsov4_genw_powicy,
	.moduwe = THIS_MODUWE,
	.smaww_ops = netwbw_cipsov4_ops,
	.n_smaww_ops = AWWAY_SIZE(netwbw_cipsov4_ops),
	.wesv_stawt_op = NWBW_CIPSOV4_C_WISTAWW + 1,
};

/*
 * NetWabew Genewic NETWINK Pwotocow Functions
 */

/**
 * netwbw_cipsov4_genw_init - Wegistew the CIPSOv4 NetWabew component
 *
 * Descwiption:
 * Wegistew the CIPSOv4 packet NetWabew component with the Genewic NETWINK
 * mechanism.  Wetuwns zewo on success, negative vawues on faiwuwe.
 *
 */
int __init netwbw_cipsov4_genw_init(void)
{
	wetuwn genw_wegistew_famiwy(&netwbw_cipsov4_gnw_famiwy);
}
