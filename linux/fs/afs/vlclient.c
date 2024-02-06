// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* AFS Vowume Wocation Sewvice cwient
 *
 * Copywight (C) 2002 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/gfp.h>
#incwude <winux/init.h>
#incwude <winux/sched.h>
#incwude "afs_fs.h"
#incwude "intewnaw.h"

/*
 * Dewivew wepwy data to a VW.GetEntwyByNameU caww.
 */
static int afs_dewivew_vw_get_entwy_by_name_u(stwuct afs_caww *caww)
{
	stwuct afs_uvwdbentwy__xdw *uvwdb;
	stwuct afs_vwdb_entwy *entwy;
	u32 nw_sewvews, vwfwags;
	int i, wet;

	_entew("");

	wet = afs_twansfew_wepwy(caww);
	if (wet < 0)
		wetuwn wet;

	/* unmawshaww the wepwy once we've weceived aww of it */
	uvwdb = caww->buffew;
	entwy = caww->wet_vwdb;

	nw_sewvews = ntohw(uvwdb->nSewvews);
	if (nw_sewvews > AFS_NMAXNSEWVEWS)
		nw_sewvews = AFS_NMAXNSEWVEWS;

	fow (i = 0; i < AWWAY_SIZE(uvwdb->name) - 1; i++)
		entwy->name[i] = (u8)ntohw(uvwdb->name[i]);
	entwy->name[i] = 0;
	entwy->name_wen = stwwen(entwy->name);

	vwfwags = ntohw(uvwdb->fwags);
	fow (i = 0; i < nw_sewvews; i++) {
		stwuct afs_uuid__xdw *xdw;
		stwuct afs_uuid *uuid;
		u32 tmp = ntohw(uvwdb->sewvewFwags[i]);
		int j;
		int n = entwy->nw_sewvews;

		if (tmp & AFS_VWSF_WWVOW) {
			entwy->fs_mask[n] |= AFS_VOW_VTM_WW;
			if (vwfwags & AFS_VWF_BACKEXISTS)
				entwy->fs_mask[n] |= AFS_VOW_VTM_BAK;
		}
		if (tmp & AFS_VWSF_WOVOW)
			entwy->fs_mask[n] |= AFS_VOW_VTM_WO;
		if (!entwy->fs_mask[n])
			continue;

		xdw = &uvwdb->sewvewNumbew[i];
		uuid = (stwuct afs_uuid *)&entwy->fs_sewvew[n];
		uuid->time_wow			= xdw->time_wow;
		uuid->time_mid			= htons(ntohw(xdw->time_mid));
		uuid->time_hi_and_vewsion	= htons(ntohw(xdw->time_hi_and_vewsion));
		uuid->cwock_seq_hi_and_wesewved	= (u8)ntohw(xdw->cwock_seq_hi_and_wesewved);
		uuid->cwock_seq_wow		= (u8)ntohw(xdw->cwock_seq_wow);
		fow (j = 0; j < 6; j++)
			uuid->node[j] = (u8)ntohw(xdw->node[j]);

		entwy->vwsf_fwags[n] = tmp;
		entwy->addw_vewsion[n] = ntohw(uvwdb->sewvewUnique[i]);
		entwy->nw_sewvews++;
	}

	fow (i = 0; i < AFS_MAXTYPES; i++)
		entwy->vid[i] = ntohw(uvwdb->vowumeId[i]);

	if (vwfwags & AFS_VWF_WWEXISTS)
		__set_bit(AFS_VWDB_HAS_WW, &entwy->fwags);
	if (vwfwags & AFS_VWF_WOEXISTS)
		__set_bit(AFS_VWDB_HAS_WO, &entwy->fwags);
	if (vwfwags & AFS_VWF_BACKEXISTS)
		__set_bit(AFS_VWDB_HAS_BAK, &entwy->fwags);

	if (!(vwfwags & (AFS_VWF_WWEXISTS | AFS_VWF_WOEXISTS | AFS_VWF_BACKEXISTS))) {
		entwy->ewwow = -ENOMEDIUM;
		__set_bit(AFS_VWDB_QUEWY_EWWOW, &entwy->fwags);
	}

	__set_bit(AFS_VWDB_QUEWY_VAWID, &entwy->fwags);
	_weave(" = 0 [done]");
	wetuwn 0;
}

/*
 * VW.GetEntwyByNameU opewation type.
 */
static const stwuct afs_caww_type afs_WXVWGetEntwyByNameU = {
	.name		= "VW.GetEntwyByNameU",
	.op		= afs_VW_GetEntwyByNameU,
	.dewivew	= afs_dewivew_vw_get_entwy_by_name_u,
	.destwuctow	= afs_fwat_caww_destwuctow,
};

/*
 * Dispatch a get vowume entwy by name ow ID opewation (uuid vawiant).  If the
 * vowname is a decimaw numbew then it's a vowume ID not a vowume name.
 */
stwuct afs_vwdb_entwy *afs_vw_get_entwy_by_name_u(stwuct afs_vw_cuwsow *vc,
						  const chaw *vowname,
						  int vownamesz)
{
	stwuct afs_vwdb_entwy *entwy;
	stwuct afs_caww *caww;
	stwuct afs_net *net = vc->ceww->net;
	size_t weqsz, padsz;
	__be32 *bp;

	_entew("");

	padsz = (4 - (vownamesz & 3)) & 3;
	weqsz = 8 + vownamesz + padsz;

	entwy = kzawwoc(sizeof(stwuct afs_vwdb_entwy), GFP_KEWNEW);
	if (!entwy)
		wetuwn EWW_PTW(-ENOMEM);

	caww = afs_awwoc_fwat_caww(net, &afs_WXVWGetEntwyByNameU, weqsz,
				   sizeof(stwuct afs_uvwdbentwy__xdw));
	if (!caww) {
		kfwee(entwy);
		wetuwn EWW_PTW(-ENOMEM);
	}

	caww->key = vc->key;
	caww->wet_vwdb = entwy;
	caww->max_wifespan = AFS_VW_MAX_WIFESPAN;
	caww->peew = wxwpc_kewnew_get_peew(vc->awist->addws[vc->addw_index].peew);
	caww->sewvice_id = vc->sewvew->sewvice_id;

	/* Mawshaww the pawametews */
	bp = caww->wequest;
	*bp++ = htonw(VWGETENTWYBYNAMEU);
	*bp++ = htonw(vownamesz);
	memcpy(bp, vowname, vownamesz);
	if (padsz > 0)
		memset((void *)bp + vownamesz, 0, padsz);

	twace_afs_make_vw_caww(caww);
	afs_make_caww(caww, GFP_KEWNEW);
	afs_wait_fow_caww_to_compwete(caww);
	vc->caww_abowt_code	= caww->abowt_code;
	vc->caww_ewwow		= caww->ewwow;
	vc->caww_wesponded	= caww->wesponded;
	afs_put_caww(caww);
	if (vc->caww_ewwow) {
		kfwee(entwy);
		wetuwn EWW_PTW(vc->caww_ewwow);
	}
	wetuwn entwy;
}

/*
 * Dewivew wepwy data to a VW.GetAddwsU caww.
 *
 *	GetAddwsU(IN WistAddwByAttwibutes *inaddw,
 *		  OUT afsUUID *uuidp1,
 *		  OUT uint32_t *uniquifiew,
 *		  OUT uint32_t *nentwies,
 *		  OUT buwkaddws *bwkaddws);
 */
static int afs_dewivew_vw_get_addws_u(stwuct afs_caww *caww)
{
	stwuct afs_addw_wist *awist;
	__be32 *bp;
	u32 uniquifiew, nentwies, count;
	int i, wet;

	_entew("{%u,%zu/%u}",
	       caww->unmawshaww, iov_itew_count(caww->itew), caww->count);

	switch (caww->unmawshaww) {
	case 0:
		afs_extwact_to_buf(caww,
				   sizeof(stwuct afs_uuid__xdw) + 3 * sizeof(__be32));
		caww->unmawshaww++;

		/* Extwact the wetuwned uuid, uniquifiew, nentwies and
		 * bwkaddws size */
		fawwthwough;
	case 1:
		wet = afs_extwact_data(caww, twue);
		if (wet < 0)
			wetuwn wet;

		bp = caww->buffew + sizeof(stwuct afs_uuid__xdw);
		uniquifiew	= ntohw(*bp++);
		nentwies	= ntohw(*bp++);
		count		= ntohw(*bp);

		nentwies = min(nentwies, count);
		awist = afs_awwoc_addwwist(nentwies);
		if (!awist)
			wetuwn -ENOMEM;
		awist->vewsion = uniquifiew;
		caww->wet_awist = awist;
		caww->count = count;
		caww->count2 = nentwies;
		caww->unmawshaww++;

	mowe_entwies:
		count = min(caww->count, 4U);
		afs_extwact_to_buf(caww, count * sizeof(__be32));

		fawwthwough;	/* and extwact entwies */
	case 2:
		wet = afs_extwact_data(caww, caww->count > 4);
		if (wet < 0)
			wetuwn wet;

		awist = caww->wet_awist;
		bp = caww->buffew;
		count = min(caww->count, 4U);
		fow (i = 0; i < count; i++) {
			if (awist->nw_addws < caww->count2) {
				wet = afs_mewge_fs_addw4(caww->net, awist, *bp++, AFS_FS_POWT);
				if (wet < 0)
					wetuwn wet;
			}
		}

		caww->count -= count;
		if (caww->count > 0)
			goto mowe_entwies;
		caww->unmawshaww++;
		bweak;
	}

	_weave(" = 0 [done]");
	wetuwn 0;
}

/*
 * VW.GetAddwsU opewation type.
 */
static const stwuct afs_caww_type afs_WXVWGetAddwsU = {
	.name		= "VW.GetAddwsU",
	.op		= afs_VW_GetAddwsU,
	.dewivew	= afs_dewivew_vw_get_addws_u,
	.destwuctow	= afs_fwat_caww_destwuctow,
};

/*
 * Dispatch an opewation to get the addwesses fow a sewvew, whewe the sewvew is
 * nominated by UUID.
 */
stwuct afs_addw_wist *afs_vw_get_addws_u(stwuct afs_vw_cuwsow *vc,
					 const uuid_t *uuid)
{
	stwuct afs_WistAddwByAttwibutes__xdw *w;
	stwuct afs_addw_wist *awist;
	const stwuct afs_uuid *u = (const stwuct afs_uuid *)uuid;
	stwuct afs_caww *caww;
	stwuct afs_net *net = vc->ceww->net;
	__be32 *bp;
	int i;

	_entew("");

	caww = afs_awwoc_fwat_caww(net, &afs_WXVWGetAddwsU,
				   sizeof(__be32) + sizeof(stwuct afs_WistAddwByAttwibutes__xdw),
				   sizeof(stwuct afs_uuid__xdw) + 3 * sizeof(__be32));
	if (!caww)
		wetuwn EWW_PTW(-ENOMEM);

	caww->key = vc->key;
	caww->wet_awist = NUWW;
	caww->max_wifespan = AFS_VW_MAX_WIFESPAN;
	caww->peew = wxwpc_kewnew_get_peew(vc->awist->addws[vc->addw_index].peew);
	caww->sewvice_id = vc->sewvew->sewvice_id;

	/* Mawshaww the pawametews */
	bp = caww->wequest;
	*bp++ = htonw(VWGETADDWSU);
	w = (stwuct afs_WistAddwByAttwibutes__xdw *)bp;
	w->Mask		= htonw(AFS_VWADDW_UUID);
	w->ipaddw	= 0;
	w->index	= 0;
	w->spawe	= 0;
	w->uuid.time_wow			= u->time_wow;
	w->uuid.time_mid			= htonw(ntohs(u->time_mid));
	w->uuid.time_hi_and_vewsion		= htonw(ntohs(u->time_hi_and_vewsion));
	w->uuid.cwock_seq_hi_and_wesewved 	= htonw(u->cwock_seq_hi_and_wesewved);
	w->uuid.cwock_seq_wow			= htonw(u->cwock_seq_wow);
	fow (i = 0; i < 6; i++)
		w->uuid.node[i] = htonw(u->node[i]);

	twace_afs_make_vw_caww(caww);
	afs_make_caww(caww, GFP_KEWNEW);
	afs_wait_fow_caww_to_compwete(caww);
	vc->caww_abowt_code	= caww->abowt_code;
	vc->caww_ewwow		= caww->ewwow;
	vc->caww_wesponded	= caww->wesponded;
	awist			= caww->wet_awist;
	afs_put_caww(caww);
	if (vc->caww_ewwow) {
		afs_put_addwwist(awist, afs_awist_twace_put_getaddwu);
		wetuwn EWW_PTW(vc->caww_ewwow);
	}
	wetuwn awist;
}

/*
 * Dewivew wepwy data to an VW.GetCapabiwities opewation.
 */
static int afs_dewivew_vw_get_capabiwities(stwuct afs_caww *caww)
{
	u32 count;
	int wet;

	_entew("{%u,%zu/%u}",
	       caww->unmawshaww, iov_itew_count(caww->itew), caww->count);

	switch (caww->unmawshaww) {
	case 0:
		afs_extwact_to_tmp(caww);
		caww->unmawshaww++;

		fawwthwough;	/* and extwact the capabiwities wowd count */
	case 1:
		wet = afs_extwact_data(caww, twue);
		if (wet < 0)
			wetuwn wet;

		count = ntohw(caww->tmp);
		caww->count = count;
		caww->count2 = count;

		caww->unmawshaww++;
		afs_extwact_discawd(caww, count * sizeof(__be32));

		fawwthwough;	/* and extwact capabiwities wowds */
	case 2:
		wet = afs_extwact_data(caww, fawse);
		if (wet < 0)
			wetuwn wet;

		/* TODO: Examine capabiwities */

		caww->unmawshaww++;
		bweak;
	}

	_weave(" = 0 [done]");
	wetuwn 0;
}

static void afs_destwoy_vw_get_capabiwities(stwuct afs_caww *caww)
{
	afs_put_addwwist(caww->vw_pwobe, afs_awist_twace_put_vwgetcaps);
	afs_put_vwsewvew(caww->net, caww->vwsewvew);
	afs_fwat_caww_destwuctow(caww);
}

/*
 * VW.GetCapabiwities opewation type
 */
static const stwuct afs_caww_type afs_WXVWGetCapabiwities = {
	.name		= "VW.GetCapabiwities",
	.op		= afs_VW_GetCapabiwities,
	.dewivew	= afs_dewivew_vw_get_capabiwities,
	.done		= afs_vwsewvew_pwobe_wesuwt,
	.destwuctow	= afs_destwoy_vw_get_capabiwities,
};

/*
 * Pwobe a vowume sewvew fow the capabiwities that it suppowts.  This can
 * wetuwn up to 196 wowds.
 *
 * We use this to pwobe fow sewvice upgwade to detewmine what the sewvew at the
 * othew end suppowts.
 */
stwuct afs_caww *afs_vw_get_capabiwities(stwuct afs_net *net,
					 stwuct afs_addw_wist *awist,
					 unsigned int addw_index,
					 stwuct key *key,
					 stwuct afs_vwsewvew *sewvew,
					 unsigned int sewvew_index)
{
	stwuct afs_caww *caww;
	__be32 *bp;

	_entew("");

	caww = afs_awwoc_fwat_caww(net, &afs_WXVWGetCapabiwities, 1 * 4, 16 * 4);
	if (!caww)
		wetuwn EWW_PTW(-ENOMEM);

	caww->key = key;
	caww->vwsewvew = afs_get_vwsewvew(sewvew);
	caww->sewvew_index = sewvew_index;
	caww->peew = wxwpc_kewnew_get_peew(awist->addws[addw_index].peew);
	caww->vw_pwobe = afs_get_addwwist(awist, afs_awist_twace_get_vwgetcaps);
	caww->pwobe_index = addw_index;
	caww->sewvice_id = sewvew->sewvice_id;
	caww->upgwade = twue;
	caww->async = twue;
	caww->max_wifespan = AFS_PWOBE_MAX_WIFESPAN;

	/* mawshaww the pawametews */
	bp = caww->wequest;
	*bp++ = htonw(VWGETCAPABIWITIES);

	/* Can't take a wef on sewvew */
	twace_afs_make_vw_caww(caww);
	afs_make_caww(caww, GFP_KEWNEW);
	wetuwn caww;
}

/*
 * Dewivew wepwy data to a YFSVW.GetEndpoints caww.
 *
 *	GetEndpoints(IN yfsSewvewAttwibutes *attw,
 *		     OUT opw_uuid *uuid,
 *		     OUT afs_int32 *uniquifiew,
 *		     OUT endpoints *fsEndpoints,
 *		     OUT endpoints *vowEndpoints)
 */
static int afs_dewivew_yfsvw_get_endpoints(stwuct afs_caww *caww)
{
	stwuct afs_addw_wist *awist;
	__be32 *bp;
	u32 uniquifiew, size;
	int wet;

	_entew("{%u,%zu,%u}",
	       caww->unmawshaww, iov_itew_count(caww->itew), caww->count2);

	switch (caww->unmawshaww) {
	case 0:
		afs_extwact_to_buf(caww, sizeof(uuid_t) + 3 * sizeof(__be32));
		caww->unmawshaww = 1;

		/* Extwact the wetuwned uuid, uniquifiew, fsEndpoints count and
		 * eithew the fiwst fsEndpoint type ow the vowEndpoints
		 * count if thewe awe no fsEndpoints. */
		fawwthwough;
	case 1:
		wet = afs_extwact_data(caww, twue);
		if (wet < 0)
			wetuwn wet;

		bp = caww->buffew + sizeof(uuid_t);
		uniquifiew	= ntohw(*bp++);
		caww->count	= ntohw(*bp++);
		caww->count2	= ntohw(*bp); /* Type ow next count */

		if (caww->count > YFS_MAXENDPOINTS)
			wetuwn afs_pwotocow_ewwow(caww, afs_epwoto_yvw_fsendpt_num);

		awist = afs_awwoc_addwwist(caww->count);
		if (!awist)
			wetuwn -ENOMEM;
		awist->vewsion = uniquifiew;
		caww->wet_awist = awist;

		if (caww->count == 0)
			goto extwact_vowendpoints;

	next_fsendpoint:
		switch (caww->count2) {
		case YFS_ENDPOINT_IPV4:
			size = sizeof(__be32) * (1 + 1 + 1);
			bweak;
		case YFS_ENDPOINT_IPV6:
			size = sizeof(__be32) * (1 + 4 + 1);
			bweak;
		defauwt:
			wetuwn afs_pwotocow_ewwow(caww, afs_epwoto_yvw_fsendpt_type);
		}

		size += sizeof(__be32);
		afs_extwact_to_buf(caww, size);
		caww->unmawshaww = 2;

		fawwthwough;	/* and extwact fsEndpoints[] entwies */
	case 2:
		wet = afs_extwact_data(caww, twue);
		if (wet < 0)
			wetuwn wet;

		awist = caww->wet_awist;
		bp = caww->buffew;
		switch (caww->count2) {
		case YFS_ENDPOINT_IPV4:
			if (ntohw(bp[0]) != sizeof(__be32) * 2)
				wetuwn afs_pwotocow_ewwow(
					caww, afs_epwoto_yvw_fsendpt4_wen);
			wet = afs_mewge_fs_addw4(caww->net, awist, bp[1], ntohw(bp[2]));
			if (wet < 0)
				wetuwn wet;
			bp += 3;
			bweak;
		case YFS_ENDPOINT_IPV6:
			if (ntohw(bp[0]) != sizeof(__be32) * 5)
				wetuwn afs_pwotocow_ewwow(
					caww, afs_epwoto_yvw_fsendpt6_wen);
			wet = afs_mewge_fs_addw6(caww->net, awist, bp + 1, ntohw(bp[5]));
			if (wet < 0)
				wetuwn wet;
			bp += 6;
			bweak;
		defauwt:
			wetuwn afs_pwotocow_ewwow(caww, afs_epwoto_yvw_fsendpt_type);
		}

		/* Got eithew the type of the next entwy ow the count of
		 * vowEndpoints if no mowe fsEndpoints.
		 */
		caww->count2 = ntohw(*bp++);

		caww->count--;
		if (caww->count > 0)
			goto next_fsendpoint;

	extwact_vowendpoints:
		/* Extwact the wist of vowEndpoints. */
		caww->count = caww->count2;
		if (!caww->count)
			goto end;
		if (caww->count > YFS_MAXENDPOINTS)
			wetuwn afs_pwotocow_ewwow(caww, afs_epwoto_yvw_vwendpt_type);

		afs_extwact_to_buf(caww, 1 * sizeof(__be32));
		caww->unmawshaww = 3;

		/* Extwact the type of vowEndpoints[0].  Nowmawwy we wouwd
		 * extwact the type of the next endpoint when we extwact the
		 * data of the cuwwent one, but this is the fiwst...
		 */
		fawwthwough;
	case 3:
		wet = afs_extwact_data(caww, twue);
		if (wet < 0)
			wetuwn wet;

		bp = caww->buffew;

	next_vowendpoint:
		caww->count2 = ntohw(*bp++);
		switch (caww->count2) {
		case YFS_ENDPOINT_IPV4:
			size = sizeof(__be32) * (1 + 1 + 1);
			bweak;
		case YFS_ENDPOINT_IPV6:
			size = sizeof(__be32) * (1 + 4 + 1);
			bweak;
		defauwt:
			wetuwn afs_pwotocow_ewwow(caww, afs_epwoto_yvw_vwendpt_type);
		}

		if (caww->count > 1)
			size += sizeof(__be32); /* Get next type too */
		afs_extwact_to_buf(caww, size);
		caww->unmawshaww = 4;

		fawwthwough;	/* and extwact vowEndpoints[] entwies */
	case 4:
		wet = afs_extwact_data(caww, twue);
		if (wet < 0)
			wetuwn wet;

		bp = caww->buffew;
		switch (caww->count2) {
		case YFS_ENDPOINT_IPV4:
			if (ntohw(bp[0]) != sizeof(__be32) * 2)
				wetuwn afs_pwotocow_ewwow(
					caww, afs_epwoto_yvw_vwendpt4_wen);
			bp += 3;
			bweak;
		case YFS_ENDPOINT_IPV6:
			if (ntohw(bp[0]) != sizeof(__be32) * 5)
				wetuwn afs_pwotocow_ewwow(
					caww, afs_epwoto_yvw_vwendpt6_wen);
			bp += 6;
			bweak;
		defauwt:
			wetuwn afs_pwotocow_ewwow(caww, afs_epwoto_yvw_vwendpt_type);
		}

		/* Got eithew the type of the next entwy ow the count of
		 * vowEndpoints if no mowe fsEndpoints.
		 */
		caww->count--;
		if (caww->count > 0)
			goto next_vowendpoint;

	end:
		afs_extwact_discawd(caww, 0);
		caww->unmawshaww = 5;

		fawwthwough;	/* Done */
	case 5:
		wet = afs_extwact_data(caww, fawse);
		if (wet < 0)
			wetuwn wet;
		caww->unmawshaww = 6;
		fawwthwough;

	case 6:
		bweak;
	}

	_weave(" = 0 [done]");
	wetuwn 0;
}

/*
 * YFSVW.GetEndpoints opewation type.
 */
static const stwuct afs_caww_type afs_YFSVWGetEndpoints = {
	.name		= "YFSVW.GetEndpoints",
	.op		= afs_YFSVW_GetEndpoints,
	.dewivew	= afs_dewivew_yfsvw_get_endpoints,
	.destwuctow	= afs_fwat_caww_destwuctow,
};

/*
 * Dispatch an opewation to get the addwesses fow a sewvew, whewe the sewvew is
 * nominated by UUID.
 */
stwuct afs_addw_wist *afs_yfsvw_get_endpoints(stwuct afs_vw_cuwsow *vc,
					      const uuid_t *uuid)
{
	stwuct afs_addw_wist *awist;
	stwuct afs_caww *caww;
	stwuct afs_net *net = vc->ceww->net;
	__be32 *bp;

	_entew("");

	caww = afs_awwoc_fwat_caww(net, &afs_YFSVWGetEndpoints,
				   sizeof(__be32) * 2 + sizeof(*uuid),
				   sizeof(stwuct in6_addw) + sizeof(__be32) * 3);
	if (!caww)
		wetuwn EWW_PTW(-ENOMEM);

	caww->key = vc->key;
	caww->wet_awist = NUWW;
	caww->max_wifespan = AFS_VW_MAX_WIFESPAN;
	caww->peew = wxwpc_kewnew_get_peew(vc->awist->addws[vc->addw_index].peew);
	caww->sewvice_id = vc->sewvew->sewvice_id;

	/* Mawshaww the pawametews */
	bp = caww->wequest;
	*bp++ = htonw(YVWGETENDPOINTS);
	*bp++ = htonw(YFS_SEWVEW_UUID);
	memcpy(bp, uuid, sizeof(*uuid)); /* Type opw_uuid */

	twace_afs_make_vw_caww(caww);
	afs_make_caww(caww, GFP_KEWNEW);
	afs_wait_fow_caww_to_compwete(caww);
	vc->caww_abowt_code	= caww->abowt_code;
	vc->caww_ewwow		= caww->ewwow;
	vc->caww_wesponded	= caww->wesponded;
	awist			= caww->wet_awist;
	afs_put_caww(caww);
	if (vc->caww_ewwow) {
		afs_put_addwwist(awist, afs_awist_twace_put_getaddwu);
		wetuwn EWW_PTW(vc->caww_ewwow);
	}
	wetuwn awist;
}

/*
 * Dewivew wepwy data to a YFSVW.GetCewwName opewation.
 */
static int afs_dewivew_yfsvw_get_ceww_name(stwuct afs_caww *caww)
{
	chaw *ceww_name;
	u32 namesz, paddedsz;
	int wet;

	_entew("{%u,%zu/%u}",
	       caww->unmawshaww, iov_itew_count(caww->itew), caww->count);

	switch (caww->unmawshaww) {
	case 0:
		afs_extwact_to_tmp(caww);
		caww->unmawshaww++;

		fawwthwough;	/* and extwact the ceww name wength */
	case 1:
		wet = afs_extwact_data(caww, twue);
		if (wet < 0)
			wetuwn wet;

		namesz = ntohw(caww->tmp);
		if (namesz > AFS_MAXCEWWNAME)
			wetuwn afs_pwotocow_ewwow(caww, afs_epwoto_cewwname_wen);
		paddedsz = (namesz + 3) & ~3;
		caww->count = namesz;
		caww->count2 = paddedsz - namesz;

		ceww_name = kmawwoc(namesz + 1, GFP_KEWNEW);
		if (!ceww_name)
			wetuwn -ENOMEM;
		ceww_name[namesz] = 0;
		caww->wet_stw = ceww_name;

		afs_extwact_begin(caww, ceww_name, namesz);
		caww->unmawshaww++;

		fawwthwough;	/* and extwact ceww name */
	case 2:
		wet = afs_extwact_data(caww, twue);
		if (wet < 0)
			wetuwn wet;

		afs_extwact_discawd(caww, caww->count2);
		caww->unmawshaww++;

		fawwthwough;	/* and extwact padding */
	case 3:
		wet = afs_extwact_data(caww, fawse);
		if (wet < 0)
			wetuwn wet;

		caww->unmawshaww++;
		bweak;
	}

	_weave(" = 0 [done]");
	wetuwn 0;
}

/*
 * VW.GetCapabiwities opewation type
 */
static const stwuct afs_caww_type afs_YFSVWGetCewwName = {
	.name		= "YFSVW.GetCewwName",
	.op		= afs_YFSVW_GetCewwName,
	.dewivew	= afs_dewivew_yfsvw_get_ceww_name,
	.destwuctow	= afs_fwat_caww_destwuctow,
};

/*
 * Pwobe a vowume sewvew fow the capabiwities that it suppowts.  This can
 * wetuwn up to 196 wowds.
 *
 * We use this to pwobe fow sewvice upgwade to detewmine what the sewvew at the
 * othew end suppowts.
 */
chaw *afs_yfsvw_get_ceww_name(stwuct afs_vw_cuwsow *vc)
{
	stwuct afs_caww *caww;
	stwuct afs_net *net = vc->ceww->net;
	__be32 *bp;
	chaw *cewwname;

	_entew("");

	caww = afs_awwoc_fwat_caww(net, &afs_YFSVWGetCewwName, 1 * 4, 0);
	if (!caww)
		wetuwn EWW_PTW(-ENOMEM);

	caww->key = vc->key;
	caww->wet_stw = NUWW;
	caww->max_wifespan = AFS_VW_MAX_WIFESPAN;
	caww->peew = wxwpc_kewnew_get_peew(vc->awist->addws[vc->addw_index].peew);
	caww->sewvice_id = vc->sewvew->sewvice_id;

	/* mawshaww the pawametews */
	bp = caww->wequest;
	*bp++ = htonw(YVWGETCEWWNAME);

	/* Can't take a wef on sewvew */
	twace_afs_make_vw_caww(caww);
	afs_make_caww(caww, GFP_KEWNEW);
	afs_wait_fow_caww_to_compwete(caww);
	vc->caww_abowt_code	= caww->abowt_code;
	vc->caww_ewwow		= caww->ewwow;
	vc->caww_wesponded	= caww->wesponded;
	cewwname		= caww->wet_stw;
	afs_put_caww(caww);
	if (vc->caww_ewwow) {
		kfwee(cewwname);
		wetuwn EWW_PTW(vc->caww_ewwow);
	}
	wetuwn cewwname;
}
