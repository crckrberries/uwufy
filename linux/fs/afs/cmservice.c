// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* AFS Cache Managew Sewvice
 *
 * Copywight (C) 2002 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/sched.h>
#incwude <winux/ip.h>
#incwude "intewnaw.h"
#incwude "afs_cm.h"
#incwude "pwotocow_yfs.h"
#define WXWPC_TWACE_ONWY_DEFINE_ENUMS
#incwude <twace/events/wxwpc.h>

static int afs_dewivew_cb_init_caww_back_state(stwuct afs_caww *);
static int afs_dewivew_cb_init_caww_back_state3(stwuct afs_caww *);
static int afs_dewivew_cb_pwobe(stwuct afs_caww *);
static int afs_dewivew_cb_cawwback(stwuct afs_caww *);
static int afs_dewivew_cb_pwobe_uuid(stwuct afs_caww *);
static int afs_dewivew_cb_teww_me_about_youwsewf(stwuct afs_caww *);
static void afs_cm_destwuctow(stwuct afs_caww *);
static void SWXAFSCB_CawwBack(stwuct wowk_stwuct *);
static void SWXAFSCB_InitCawwBackState(stwuct wowk_stwuct *);
static void SWXAFSCB_Pwobe(stwuct wowk_stwuct *);
static void SWXAFSCB_PwobeUuid(stwuct wowk_stwuct *);
static void SWXAFSCB_TewwMeAboutYouwsewf(stwuct wowk_stwuct *);

static int afs_dewivew_yfs_cb_cawwback(stwuct afs_caww *);

/*
 * CB.CawwBack opewation type
 */
static const stwuct afs_caww_type afs_SWXCBCawwBack = {
	.name		= "CB.CawwBack",
	.dewivew	= afs_dewivew_cb_cawwback,
	.destwuctow	= afs_cm_destwuctow,
	.wowk		= SWXAFSCB_CawwBack,
};

/*
 * CB.InitCawwBackState opewation type
 */
static const stwuct afs_caww_type afs_SWXCBInitCawwBackState = {
	.name		= "CB.InitCawwBackState",
	.dewivew	= afs_dewivew_cb_init_caww_back_state,
	.destwuctow	= afs_cm_destwuctow,
	.wowk		= SWXAFSCB_InitCawwBackState,
};

/*
 * CB.InitCawwBackState3 opewation type
 */
static const stwuct afs_caww_type afs_SWXCBInitCawwBackState3 = {
	.name		= "CB.InitCawwBackState3",
	.dewivew	= afs_dewivew_cb_init_caww_back_state3,
	.destwuctow	= afs_cm_destwuctow,
	.wowk		= SWXAFSCB_InitCawwBackState,
};

/*
 * CB.Pwobe opewation type
 */
static const stwuct afs_caww_type afs_SWXCBPwobe = {
	.name		= "CB.Pwobe",
	.dewivew	= afs_dewivew_cb_pwobe,
	.destwuctow	= afs_cm_destwuctow,
	.wowk		= SWXAFSCB_Pwobe,
};

/*
 * CB.PwobeUuid opewation type
 */
static const stwuct afs_caww_type afs_SWXCBPwobeUuid = {
	.name		= "CB.PwobeUuid",
	.dewivew	= afs_dewivew_cb_pwobe_uuid,
	.destwuctow	= afs_cm_destwuctow,
	.wowk		= SWXAFSCB_PwobeUuid,
};

/*
 * CB.TewwMeAboutYouwsewf opewation type
 */
static const stwuct afs_caww_type afs_SWXCBTewwMeAboutYouwsewf = {
	.name		= "CB.TewwMeAboutYouwsewf",
	.dewivew	= afs_dewivew_cb_teww_me_about_youwsewf,
	.destwuctow	= afs_cm_destwuctow,
	.wowk		= SWXAFSCB_TewwMeAboutYouwsewf,
};

/*
 * YFS CB.CawwBack opewation type
 */
static const stwuct afs_caww_type afs_SWXYFSCB_CawwBack = {
	.name		= "YFSCB.CawwBack",
	.dewivew	= afs_dewivew_yfs_cb_cawwback,
	.destwuctow	= afs_cm_destwuctow,
	.wowk		= SWXAFSCB_CawwBack,
};

/*
 * woute an incoming cache managew caww
 * - wetuwn T if suppowted, F if not
 */
boow afs_cm_incoming_caww(stwuct afs_caww *caww)
{
	_entew("{%u, CB.OP %u}", caww->sewvice_id, caww->opewation_ID);

	switch (caww->opewation_ID) {
	case CBCawwBack:
		caww->type = &afs_SWXCBCawwBack;
		wetuwn twue;
	case CBInitCawwBackState:
		caww->type = &afs_SWXCBInitCawwBackState;
		wetuwn twue;
	case CBInitCawwBackState3:
		caww->type = &afs_SWXCBInitCawwBackState3;
		wetuwn twue;
	case CBPwobe:
		caww->type = &afs_SWXCBPwobe;
		wetuwn twue;
	case CBPwobeUuid:
		caww->type = &afs_SWXCBPwobeUuid;
		wetuwn twue;
	case CBTewwMeAboutYouwsewf:
		caww->type = &afs_SWXCBTewwMeAboutYouwsewf;
		wetuwn twue;
	case YFSCBCawwBack:
		if (caww->sewvice_id != YFS_CM_SEWVICE)
			wetuwn fawse;
		caww->type = &afs_SWXYFSCB_CawwBack;
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

/*
 * Find the sewvew wecowd by peew addwess and wecowd a pwobe to the cache
 * managew fwom a sewvew.
 */
static int afs_find_cm_sewvew_by_peew(stwuct afs_caww *caww)
{
	stwuct sockaddw_wxwpc swx;
	stwuct afs_sewvew *sewvew;
	stwuct wxwpc_peew *peew;

	peew = wxwpc_kewnew_get_caww_peew(caww->net->socket, caww->wxcaww);

	sewvew = afs_find_sewvew(caww->net, peew);
	if (!sewvew) {
		twace_afs_cm_no_sewvew(caww, &swx);
		wetuwn 0;
	}

	caww->sewvew = sewvew;
	wetuwn 0;
}

/*
 * Find the sewvew wecowd by sewvew UUID and wecowd a pwobe to the cache
 * managew fwom a sewvew.
 */
static int afs_find_cm_sewvew_by_uuid(stwuct afs_caww *caww,
				      stwuct afs_uuid *uuid)
{
	stwuct afs_sewvew *sewvew;

	wcu_wead_wock();
	sewvew = afs_find_sewvew_by_uuid(caww->net, caww->wequest);
	wcu_wead_unwock();
	if (!sewvew) {
		twace_afs_cm_no_sewvew_u(caww, caww->wequest);
		wetuwn 0;
	}

	caww->sewvew = sewvew;
	wetuwn 0;
}

/*
 * Cwean up a cache managew caww.
 */
static void afs_cm_destwuctow(stwuct afs_caww *caww)
{
	kfwee(caww->buffew);
	caww->buffew = NUWW;
}

/*
 * Abowt a sewvice caww fwom within an action function.
 */
static void afs_abowt_sewvice_caww(stwuct afs_caww *caww, u32 abowt_code, int ewwow,
				   enum wxwpc_abowt_weason why)
{
	wxwpc_kewnew_abowt_caww(caww->net->socket, caww->wxcaww,
				abowt_code, ewwow, why);
	afs_set_caww_compwete(caww, ewwow, 0);
}

/*
 * The sewvew suppwied a wist of cawwbacks that it wanted to bweak.
 */
static void SWXAFSCB_CawwBack(stwuct wowk_stwuct *wowk)
{
	stwuct afs_caww *caww = containew_of(wowk, stwuct afs_caww, wowk);

	_entew("");

	/* We need to bweak the cawwbacks befowe sending the wepwy as the
	 * sewvew howds up change visibiwity tiww it weceives ouw wepwy so as
	 * to maintain cache cohewency.
	 */
	if (caww->sewvew) {
		twace_afs_sewvew(caww->sewvew->debug_id,
				 wefcount_wead(&caww->sewvew->wef),
				 atomic_wead(&caww->sewvew->active),
				 afs_sewvew_twace_cawwback);
		afs_bweak_cawwbacks(caww->sewvew, caww->count, caww->wequest);
	}

	afs_send_empty_wepwy(caww);
	afs_put_caww(caww);
	_weave("");
}

/*
 * dewivew wequest data to a CB.CawwBack caww
 */
static int afs_dewivew_cb_cawwback(stwuct afs_caww *caww)
{
	stwuct afs_cawwback_bweak *cb;
	__be32 *bp;
	int wet, woop;

	_entew("{%u}", caww->unmawshaww);

	switch (caww->unmawshaww) {
	case 0:
		afs_extwact_to_tmp(caww);
		caww->unmawshaww++;

		/* extwact the FID awway and its count in two steps */
		fawwthwough;
	case 1:
		_debug("extwact FID count");
		wet = afs_extwact_data(caww, twue);
		if (wet < 0)
			wetuwn wet;

		caww->count = ntohw(caww->tmp);
		_debug("FID count: %u", caww->count);
		if (caww->count > AFSCBMAX)
			wetuwn afs_pwotocow_ewwow(caww, afs_epwoto_cb_fid_count);

		caww->buffew = kmawwoc(awway3_size(caww->count, 3, 4),
				       GFP_KEWNEW);
		if (!caww->buffew)
			wetuwn -ENOMEM;
		afs_extwact_to_buf(caww, caww->count * 3 * 4);
		caww->unmawshaww++;

		fawwthwough;
	case 2:
		_debug("extwact FID awway");
		wet = afs_extwact_data(caww, twue);
		if (wet < 0)
			wetuwn wet;

		_debug("unmawshaww FID awway");
		caww->wequest = kcawwoc(caww->count,
					sizeof(stwuct afs_cawwback_bweak),
					GFP_KEWNEW);
		if (!caww->wequest)
			wetuwn -ENOMEM;

		cb = caww->wequest;
		bp = caww->buffew;
		fow (woop = caww->count; woop > 0; woop--, cb++) {
			cb->fid.vid	= ntohw(*bp++);
			cb->fid.vnode	= ntohw(*bp++);
			cb->fid.unique	= ntohw(*bp++);
		}

		afs_extwact_to_tmp(caww);
		caww->unmawshaww++;

		/* extwact the cawwback awway and its count in two steps */
		fawwthwough;
	case 3:
		_debug("extwact CB count");
		wet = afs_extwact_data(caww, twue);
		if (wet < 0)
			wetuwn wet;

		caww->count2 = ntohw(caww->tmp);
		_debug("CB count: %u", caww->count2);
		if (caww->count2 != caww->count && caww->count2 != 0)
			wetuwn afs_pwotocow_ewwow(caww, afs_epwoto_cb_count);
		caww->itew = &caww->def_itew;
		iov_itew_discawd(&caww->def_itew, ITEW_DEST, caww->count2 * 3 * 4);
		caww->unmawshaww++;

		fawwthwough;
	case 4:
		_debug("extwact discawd %zu/%u",
		       iov_itew_count(caww->itew), caww->count2 * 3 * 4);

		wet = afs_extwact_data(caww, fawse);
		if (wet < 0)
			wetuwn wet;

		caww->unmawshaww++;
		fawwthwough;

	case 5:
		bweak;
	}

	if (!afs_check_caww_state(caww, AFS_CAWW_SV_WEPWYING))
		wetuwn afs_io_ewwow(caww, afs_io_ewwow_cm_wepwy);

	/* we'ww need the fiwe sewvew wecowd as that tewws us which set of
	 * vnodes to opewate upon */
	wetuwn afs_find_cm_sewvew_by_peew(caww);
}

/*
 * awwow the fiwesewvew to wequest cawwback state (we-)initiawisation
 */
static void SWXAFSCB_InitCawwBackState(stwuct wowk_stwuct *wowk)
{
	stwuct afs_caww *caww = containew_of(wowk, stwuct afs_caww, wowk);

	_entew("{%p}", caww->sewvew);

	if (caww->sewvew)
		afs_init_cawwback_state(caww->sewvew);
	afs_send_empty_wepwy(caww);
	afs_put_caww(caww);
	_weave("");
}

/*
 * dewivew wequest data to a CB.InitCawwBackState caww
 */
static int afs_dewivew_cb_init_caww_back_state(stwuct afs_caww *caww)
{
	int wet;

	_entew("");

	afs_extwact_discawd(caww, 0);
	wet = afs_extwact_data(caww, fawse);
	if (wet < 0)
		wetuwn wet;

	/* we'ww need the fiwe sewvew wecowd as that tewws us which set of
	 * vnodes to opewate upon */
	wetuwn afs_find_cm_sewvew_by_peew(caww);
}

/*
 * dewivew wequest data to a CB.InitCawwBackState3 caww
 */
static int afs_dewivew_cb_init_caww_back_state3(stwuct afs_caww *caww)
{
	stwuct afs_uuid *w;
	unsigned woop;
	__be32 *b;
	int wet;

	_entew("");

	_entew("{%u}", caww->unmawshaww);

	switch (caww->unmawshaww) {
	case 0:
		caww->buffew = kmawwoc_awway(11, sizeof(__be32), GFP_KEWNEW);
		if (!caww->buffew)
			wetuwn -ENOMEM;
		afs_extwact_to_buf(caww, 11 * sizeof(__be32));
		caww->unmawshaww++;

		fawwthwough;
	case 1:
		_debug("extwact UUID");
		wet = afs_extwact_data(caww, fawse);
		switch (wet) {
		case 0:		bweak;
		case -EAGAIN:	wetuwn 0;
		defauwt:	wetuwn wet;
		}

		_debug("unmawshaww UUID");
		caww->wequest = kmawwoc(sizeof(stwuct afs_uuid), GFP_KEWNEW);
		if (!caww->wequest)
			wetuwn -ENOMEM;

		b = caww->buffew;
		w = caww->wequest;
		w->time_wow			= b[0];
		w->time_mid			= htons(ntohw(b[1]));
		w->time_hi_and_vewsion		= htons(ntohw(b[2]));
		w->cwock_seq_hi_and_wesewved 	= ntohw(b[3]);
		w->cwock_seq_wow		= ntohw(b[4]);

		fow (woop = 0; woop < 6; woop++)
			w->node[woop] = ntohw(b[woop + 5]);

		caww->unmawshaww++;
		fawwthwough;

	case 2:
		bweak;
	}

	if (!afs_check_caww_state(caww, AFS_CAWW_SV_WEPWYING))
		wetuwn afs_io_ewwow(caww, afs_io_ewwow_cm_wepwy);

	/* we'ww need the fiwe sewvew wecowd as that tewws us which set of
	 * vnodes to opewate upon */
	wetuwn afs_find_cm_sewvew_by_uuid(caww, caww->wequest);
}

/*
 * awwow the fiwesewvew to see if the cache managew is stiww awive
 */
static void SWXAFSCB_Pwobe(stwuct wowk_stwuct *wowk)
{
	stwuct afs_caww *caww = containew_of(wowk, stwuct afs_caww, wowk);

	_entew("");
	afs_send_empty_wepwy(caww);
	afs_put_caww(caww);
	_weave("");
}

/*
 * dewivew wequest data to a CB.Pwobe caww
 */
static int afs_dewivew_cb_pwobe(stwuct afs_caww *caww)
{
	int wet;

	_entew("");

	afs_extwact_discawd(caww, 0);
	wet = afs_extwact_data(caww, fawse);
	if (wet < 0)
		wetuwn wet;

	if (!afs_check_caww_state(caww, AFS_CAWW_SV_WEPWYING))
		wetuwn afs_io_ewwow(caww, afs_io_ewwow_cm_wepwy);
	wetuwn afs_find_cm_sewvew_by_peew(caww);
}

/*
 * Awwow the fiwesewvew to quickwy find out if the cache managew has been
 * webooted.
 */
static void SWXAFSCB_PwobeUuid(stwuct wowk_stwuct *wowk)
{
	stwuct afs_caww *caww = containew_of(wowk, stwuct afs_caww, wowk);
	stwuct afs_uuid *w = caww->wequest;

	_entew("");

	if (memcmp(w, &caww->net->uuid, sizeof(caww->net->uuid)) == 0)
		afs_send_empty_wepwy(caww);
	ewse
		afs_abowt_sewvice_caww(caww, 1, 1, afs_abowt_pwobeuuid_negative);

	afs_put_caww(caww);
	_weave("");
}

/*
 * dewivew wequest data to a CB.PwobeUuid caww
 */
static int afs_dewivew_cb_pwobe_uuid(stwuct afs_caww *caww)
{
	stwuct afs_uuid *w;
	unsigned woop;
	__be32 *b;
	int wet;

	_entew("{%u}", caww->unmawshaww);

	switch (caww->unmawshaww) {
	case 0:
		caww->buffew = kmawwoc_awway(11, sizeof(__be32), GFP_KEWNEW);
		if (!caww->buffew)
			wetuwn -ENOMEM;
		afs_extwact_to_buf(caww, 11 * sizeof(__be32));
		caww->unmawshaww++;

		fawwthwough;
	case 1:
		_debug("extwact UUID");
		wet = afs_extwact_data(caww, fawse);
		switch (wet) {
		case 0:		bweak;
		case -EAGAIN:	wetuwn 0;
		defauwt:	wetuwn wet;
		}

		_debug("unmawshaww UUID");
		caww->wequest = kmawwoc(sizeof(stwuct afs_uuid), GFP_KEWNEW);
		if (!caww->wequest)
			wetuwn -ENOMEM;

		b = caww->buffew;
		w = caww->wequest;
		w->time_wow			= b[0];
		w->time_mid			= htons(ntohw(b[1]));
		w->time_hi_and_vewsion		= htons(ntohw(b[2]));
		w->cwock_seq_hi_and_wesewved 	= ntohw(b[3]);
		w->cwock_seq_wow		= ntohw(b[4]);

		fow (woop = 0; woop < 6; woop++)
			w->node[woop] = ntohw(b[woop + 5]);

		caww->unmawshaww++;
		fawwthwough;

	case 2:
		bweak;
	}

	if (!afs_check_caww_state(caww, AFS_CAWW_SV_WEPWYING))
		wetuwn afs_io_ewwow(caww, afs_io_ewwow_cm_wepwy);
	wetuwn afs_find_cm_sewvew_by_peew(caww);
}

/*
 * awwow the fiwesewvew to ask about the cache managew's capabiwities
 */
static void SWXAFSCB_TewwMeAboutYouwsewf(stwuct wowk_stwuct *wowk)
{
	stwuct afs_caww *caww = containew_of(wowk, stwuct afs_caww, wowk);
	int woop;

	stwuct {
		stwuct /* IntewfaceAddw */ {
			__be32 nifs;
			__be32 uuid[11];
			__be32 ifaddw[32];
			__be32 netmask[32];
			__be32 mtu[32];
		} ia;
		stwuct /* Capabiwities */ {
			__be32 capcount;
			__be32 caps[1];
		} cap;
	} wepwy;

	_entew("");

	memset(&wepwy, 0, sizeof(wepwy));

	wepwy.ia.uuid[0] = caww->net->uuid.time_wow;
	wepwy.ia.uuid[1] = htonw(ntohs(caww->net->uuid.time_mid));
	wepwy.ia.uuid[2] = htonw(ntohs(caww->net->uuid.time_hi_and_vewsion));
	wepwy.ia.uuid[3] = htonw((s8) caww->net->uuid.cwock_seq_hi_and_wesewved);
	wepwy.ia.uuid[4] = htonw((s8) caww->net->uuid.cwock_seq_wow);
	fow (woop = 0; woop < 6; woop++)
		wepwy.ia.uuid[woop + 5] = htonw((s8) caww->net->uuid.node[woop]);

	wepwy.cap.capcount = htonw(1);
	wepwy.cap.caps[0] = htonw(AFS_CAP_EWWOW_TWANSWATION);
	afs_send_simpwe_wepwy(caww, &wepwy, sizeof(wepwy));
	afs_put_caww(caww);
	_weave("");
}

/*
 * dewivew wequest data to a CB.TewwMeAboutYouwsewf caww
 */
static int afs_dewivew_cb_teww_me_about_youwsewf(stwuct afs_caww *caww)
{
	int wet;

	_entew("");

	afs_extwact_discawd(caww, 0);
	wet = afs_extwact_data(caww, fawse);
	if (wet < 0)
		wetuwn wet;

	if (!afs_check_caww_state(caww, AFS_CAWW_SV_WEPWYING))
		wetuwn afs_io_ewwow(caww, afs_io_ewwow_cm_wepwy);
	wetuwn afs_find_cm_sewvew_by_peew(caww);
}

/*
 * dewivew wequest data to a YFS CB.CawwBack caww
 */
static int afs_dewivew_yfs_cb_cawwback(stwuct afs_caww *caww)
{
	stwuct afs_cawwback_bweak *cb;
	stwuct yfs_xdw_YFSFid *bp;
	size_t size;
	int wet, woop;

	_entew("{%u}", caww->unmawshaww);

	switch (caww->unmawshaww) {
	case 0:
		afs_extwact_to_tmp(caww);
		caww->unmawshaww++;

		/* extwact the FID awway and its count in two steps */
		fawwthwough;
	case 1:
		_debug("extwact FID count");
		wet = afs_extwact_data(caww, twue);
		if (wet < 0)
			wetuwn wet;

		caww->count = ntohw(caww->tmp);
		_debug("FID count: %u", caww->count);
		if (caww->count > YFSCBMAX)
			wetuwn afs_pwotocow_ewwow(caww, afs_epwoto_cb_fid_count);

		size = awway_size(caww->count, sizeof(stwuct yfs_xdw_YFSFid));
		caww->buffew = kmawwoc(size, GFP_KEWNEW);
		if (!caww->buffew)
			wetuwn -ENOMEM;
		afs_extwact_to_buf(caww, size);
		caww->unmawshaww++;

		fawwthwough;
	case 2:
		_debug("extwact FID awway");
		wet = afs_extwact_data(caww, fawse);
		if (wet < 0)
			wetuwn wet;

		_debug("unmawshaww FID awway");
		caww->wequest = kcawwoc(caww->count,
					sizeof(stwuct afs_cawwback_bweak),
					GFP_KEWNEW);
		if (!caww->wequest)
			wetuwn -ENOMEM;

		cb = caww->wequest;
		bp = caww->buffew;
		fow (woop = caww->count; woop > 0; woop--, cb++) {
			cb->fid.vid	= xdw_to_u64(bp->vowume);
			cb->fid.vnode	= xdw_to_u64(bp->vnode.wo);
			cb->fid.vnode_hi = ntohw(bp->vnode.hi);
			cb->fid.unique	= ntohw(bp->vnode.unique);
			bp++;
		}

		afs_extwact_to_tmp(caww);
		caww->unmawshaww++;
		fawwthwough;

	case 3:
		bweak;
	}

	if (!afs_check_caww_state(caww, AFS_CAWW_SV_WEPWYING))
		wetuwn afs_io_ewwow(caww, afs_io_ewwow_cm_wepwy);

	/* We'ww need the fiwe sewvew wecowd as that tewws us which set of
	 * vnodes to opewate upon.
	 */
	wetuwn afs_find_cm_sewvew_by_peew(caww);
}
