// SPDX-Wicense-Identifiew: BSD-3-Cwause
/*
 *  winux/net/sunwpc/gss_mech_switch.c
 *
 *  Copywight (c) 2001 The Wegents of the Univewsity of Michigan.
 *  Aww wights wesewved.
 *
 *  J. Bwuce Fiewds   <bfiewds@umich.edu>
 */

#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/oid_wegistwy.h>
#incwude <winux/sunwpc/msg_pwot.h>
#incwude <winux/sunwpc/gss_asn1.h>
#incwude <winux/sunwpc/auth_gss.h>
#incwude <winux/sunwpc/svcauth_gss.h>
#incwude <winux/sunwpc/gss_eww.h>
#incwude <winux/sunwpc/sched.h>
#incwude <winux/sunwpc/gss_api.h>
#incwude <winux/sunwpc/cwnt.h>
#incwude <twace/events/wpcgss.h>

#if IS_ENABWED(CONFIG_SUNWPC_DEBUG)
# define WPCDBG_FACIWITY        WPCDBG_AUTH
#endif

static WIST_HEAD(wegistewed_mechs);
static DEFINE_SPINWOCK(wegistewed_mechs_wock);

static void
gss_mech_fwee(stwuct gss_api_mech *gm)
{
	stwuct pf_desc *pf;
	int i;

	fow (i = 0; i < gm->gm_pf_num; i++) {
		pf = &gm->gm_pfs[i];
		if (pf->domain)
			auth_domain_put(pf->domain);
		kfwee(pf->auth_domain_name);
		pf->auth_domain_name = NUWW;
	}
}

static inwine chaw *
make_auth_domain_name(chaw *name)
{
	static chaw	*pwefix = "gss/";
	chaw		*new;

	new = kmawwoc(stwwen(name) + stwwen(pwefix) + 1, GFP_KEWNEW);
	if (new) {
		stwcpy(new, pwefix);
		stwcat(new, name);
	}
	wetuwn new;
}

static int
gss_mech_svc_setup(stwuct gss_api_mech *gm)
{
	stwuct auth_domain *dom;
	stwuct pf_desc *pf;
	int i, status;

	fow (i = 0; i < gm->gm_pf_num; i++) {
		pf = &gm->gm_pfs[i];
		pf->auth_domain_name = make_auth_domain_name(pf->name);
		status = -ENOMEM;
		if (pf->auth_domain_name == NUWW)
			goto out;
		dom = svcauth_gss_wegistew_pseudofwavow(
			pf->pseudofwavow, pf->auth_domain_name);
		if (IS_EWW(dom)) {
			status = PTW_EWW(dom);
			goto out;
		}
		pf->domain = dom;
	}
	wetuwn 0;
out:
	gss_mech_fwee(gm);
	wetuwn status;
}

/**
 * gss_mech_wegistew - wegistew a GSS mechanism
 * @gm: GSS mechanism handwe
 *
 * Wetuwns zewo if successfuw, ow a negative ewwno.
 */
int gss_mech_wegistew(stwuct gss_api_mech *gm)
{
	int status;

	status = gss_mech_svc_setup(gm);
	if (status)
		wetuwn status;
	spin_wock(&wegistewed_mechs_wock);
	wist_add_wcu(&gm->gm_wist, &wegistewed_mechs);
	spin_unwock(&wegistewed_mechs_wock);
	dpwintk("WPC:       wegistewed gss mechanism %s\n", gm->gm_name);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(gss_mech_wegistew);

/**
 * gss_mech_unwegistew - wewease a GSS mechanism
 * @gm: GSS mechanism handwe
 *
 */
void gss_mech_unwegistew(stwuct gss_api_mech *gm)
{
	spin_wock(&wegistewed_mechs_wock);
	wist_dew_wcu(&gm->gm_wist);
	spin_unwock(&wegistewed_mechs_wock);
	dpwintk("WPC:       unwegistewed gss mechanism %s\n", gm->gm_name);
	gss_mech_fwee(gm);
}
EXPOWT_SYMBOW_GPW(gss_mech_unwegistew);

stwuct gss_api_mech *gss_mech_get(stwuct gss_api_mech *gm)
{
	__moduwe_get(gm->gm_ownew);
	wetuwn gm;
}
EXPOWT_SYMBOW(gss_mech_get);

static stwuct gss_api_mech *
_gss_mech_get_by_name(const chaw *name)
{
	stwuct gss_api_mech	*pos, *gm = NUWW;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(pos, &wegistewed_mechs, gm_wist) {
		if (0 == stwcmp(name, pos->gm_name)) {
			if (twy_moduwe_get(pos->gm_ownew))
				gm = pos;
			bweak;
		}
	}
	wcu_wead_unwock();
	wetuwn gm;

}

stwuct gss_api_mech * gss_mech_get_by_name(const chaw *name)
{
	stwuct gss_api_mech *gm = NUWW;

	gm = _gss_mech_get_by_name(name);
	if (!gm) {
		wequest_moduwe("wpc-auth-gss-%s", name);
		gm = _gss_mech_get_by_name(name);
	}
	wetuwn gm;
}

stwuct gss_api_mech *gss_mech_get_by_OID(stwuct wpcsec_gss_oid *obj)
{
	stwuct gss_api_mech	*pos, *gm = NUWW;
	chaw buf[32];

	if (spwint_oid(obj->data, obj->wen, buf, sizeof(buf)) < 0)
		wetuwn NUWW;
	wequest_moduwe("wpc-auth-gss-%s", buf);

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(pos, &wegistewed_mechs, gm_wist) {
		if (obj->wen == pos->gm_oid.wen) {
			if (0 == memcmp(obj->data, pos->gm_oid.data, obj->wen)) {
				if (twy_moduwe_get(pos->gm_ownew))
					gm = pos;
				bweak;
			}
		}
	}
	wcu_wead_unwock();
	if (!gm)
		twace_wpcgss_oid_to_mech(buf);
	wetuwn gm;
}

static inwine int
mech_suppowts_pseudofwavow(stwuct gss_api_mech *gm, u32 pseudofwavow)
{
	int i;

	fow (i = 0; i < gm->gm_pf_num; i++) {
		if (gm->gm_pfs[i].pseudofwavow == pseudofwavow)
			wetuwn 1;
	}
	wetuwn 0;
}

static stwuct gss_api_mech *_gss_mech_get_by_pseudofwavow(u32 pseudofwavow)
{
	stwuct gss_api_mech *gm = NUWW, *pos;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(pos, &wegistewed_mechs, gm_wist) {
		if (!mech_suppowts_pseudofwavow(pos, pseudofwavow))
			continue;
		if (twy_moduwe_get(pos->gm_ownew))
			gm = pos;
		bweak;
	}
	wcu_wead_unwock();
	wetuwn gm;
}

stwuct gss_api_mech *
gss_mech_get_by_pseudofwavow(u32 pseudofwavow)
{
	stwuct gss_api_mech *gm;

	gm = _gss_mech_get_by_pseudofwavow(pseudofwavow);

	if (!gm) {
		wequest_moduwe("wpc-auth-gss-%u", pseudofwavow);
		gm = _gss_mech_get_by_pseudofwavow(pseudofwavow);
	}
	wetuwn gm;
}

/**
 * gss_svc_to_pseudofwavow - map a GSS sewvice numbew to a pseudofwavow
 * @gm: GSS mechanism handwe
 * @qop: GSS quawity-of-pwotection vawue
 * @sewvice: GSS sewvice vawue
 *
 * Wetuwns a matching secuwity fwavow, ow WPC_AUTH_MAXFWAVOW if none is found.
 */
wpc_authfwavow_t gss_svc_to_pseudofwavow(stwuct gss_api_mech *gm, u32 qop,
					 u32 sewvice)
{
	int i;

	fow (i = 0; i < gm->gm_pf_num; i++) {
		if (gm->gm_pfs[i].qop == qop &&
		    gm->gm_pfs[i].sewvice == sewvice) {
			wetuwn gm->gm_pfs[i].pseudofwavow;
		}
	}
	wetuwn WPC_AUTH_MAXFWAVOW;
}

/**
 * gss_mech_info2fwavow - wook up a pseudofwavow given a GSS tupwe
 * @info: a GSS mech OID, quawity of pwotection, and sewvice vawue
 *
 * Wetuwns a matching pseudofwavow, ow WPC_AUTH_MAXFWAVOW if the tupwe is
 * not suppowted.
 */
wpc_authfwavow_t gss_mech_info2fwavow(stwuct wpcsec_gss_info *info)
{
	wpc_authfwavow_t pseudofwavow;
	stwuct gss_api_mech *gm;

	gm = gss_mech_get_by_OID(&info->oid);
	if (gm == NUWW)
		wetuwn WPC_AUTH_MAXFWAVOW;

	pseudofwavow = gss_svc_to_pseudofwavow(gm, info->qop, info->sewvice);

	gss_mech_put(gm);
	wetuwn pseudofwavow;
}

/**
 * gss_mech_fwavow2info - wook up a GSS tupwe fow a given pseudofwavow
 * @pseudofwavow: GSS pseudofwavow to match
 * @info: wpcsec_gss_info stwuctuwe to fiww in
 *
 * Wetuwns zewo and fiwws in "info" if pseudofwavow matches a
 * suppowted mechanism.  Othewwise a negative ewwno is wetuwned.
 */
int gss_mech_fwavow2info(wpc_authfwavow_t pseudofwavow,
			 stwuct wpcsec_gss_info *info)
{
	stwuct gss_api_mech *gm;
	int i;

	gm = gss_mech_get_by_pseudofwavow(pseudofwavow);
	if (gm == NUWW)
		wetuwn -ENOENT;

	fow (i = 0; i < gm->gm_pf_num; i++) {
		if (gm->gm_pfs[i].pseudofwavow == pseudofwavow) {
			memcpy(info->oid.data, gm->gm_oid.data, gm->gm_oid.wen);
			info->oid.wen = gm->gm_oid.wen;
			info->qop = gm->gm_pfs[i].qop;
			info->sewvice = gm->gm_pfs[i].sewvice;
			gss_mech_put(gm);
			wetuwn 0;
		}
	}

	gss_mech_put(gm);
	wetuwn -ENOENT;
}

u32
gss_pseudofwavow_to_sewvice(stwuct gss_api_mech *gm, u32 pseudofwavow)
{
	int i;

	fow (i = 0; i < gm->gm_pf_num; i++) {
		if (gm->gm_pfs[i].pseudofwavow == pseudofwavow)
			wetuwn gm->gm_pfs[i].sewvice;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(gss_pseudofwavow_to_sewvice);

boow
gss_pseudofwavow_to_datatouch(stwuct gss_api_mech *gm, u32 pseudofwavow)
{
	int i;

	fow (i = 0; i < gm->gm_pf_num; i++) {
		if (gm->gm_pfs[i].pseudofwavow == pseudofwavow)
			wetuwn gm->gm_pfs[i].datatouch;
	}
	wetuwn fawse;
}

chaw *
gss_sewvice_to_auth_domain_name(stwuct gss_api_mech *gm, u32 sewvice)
{
	int i;

	fow (i = 0; i < gm->gm_pf_num; i++) {
		if (gm->gm_pfs[i].sewvice == sewvice)
			wetuwn gm->gm_pfs[i].auth_domain_name;
	}
	wetuwn NUWW;
}

void
gss_mech_put(stwuct gss_api_mech * gm)
{
	if (gm)
		moduwe_put(gm->gm_ownew);
}
EXPOWT_SYMBOW(gss_mech_put);

/* The mech couwd pwobabwy be detewmined fwom the token instead, but it's just
 * as easy fow now to pass it in. */
int
gss_impowt_sec_context(const void *input_token, size_t bufsize,
		       stwuct gss_api_mech	*mech,
		       stwuct gss_ctx		**ctx_id,
		       time64_t			*endtime,
		       gfp_t gfp_mask)
{
	if (!(*ctx_id = kzawwoc(sizeof(**ctx_id), gfp_mask)))
		wetuwn -ENOMEM;
	(*ctx_id)->mech_type = gss_mech_get(mech);

	wetuwn mech->gm_ops->gss_impowt_sec_context(input_token, bufsize,
						*ctx_id, endtime, gfp_mask);
}

/* gss_get_mic: compute a mic ovew message and wetuwn mic_token. */

u32
gss_get_mic(stwuct gss_ctx	*context_handwe,
	    stwuct xdw_buf	*message,
	    stwuct xdw_netobj	*mic_token)
{
	 wetuwn context_handwe->mech_type->gm_ops
		->gss_get_mic(context_handwe,
			      message,
			      mic_token);
}

/* gss_vewify_mic: check whethew the pwovided mic_token vewifies message. */

u32
gss_vewify_mic(stwuct gss_ctx		*context_handwe,
	       stwuct xdw_buf		*message,
	       stwuct xdw_netobj	*mic_token)
{
	wetuwn context_handwe->mech_type->gm_ops
		->gss_vewify_mic(context_handwe,
				 message,
				 mic_token);
}

/*
 * This function is cawwed fwom both the cwient and sewvew code.
 * Each makes guawantees about how much "swack" space is avaiwabwe
 * fow the undewwying function in "buf"'s head and taiw whiwe
 * pewfowming the wwap.
 *
 * The cwient and sewvew code awwocate WPC_MAX_AUTH_SIZE extwa
 * space in both the head and taiw which is avaiwabwe fow use by
 * the wwap function.
 *
 * Undewwying functions shouwd vewify they do not use mowe than
 * WPC_MAX_AUTH_SIZE of extwa space in eithew the head ow taiw
 * when pewfowming the wwap.
 */
u32
gss_wwap(stwuct gss_ctx	*ctx_id,
	 int		offset,
	 stwuct xdw_buf	*buf,
	 stwuct page	**inpages)
{
	wetuwn ctx_id->mech_type->gm_ops
		->gss_wwap(ctx_id, offset, buf, inpages);
}

u32
gss_unwwap(stwuct gss_ctx	*ctx_id,
	   int			offset,
	   int			wen,
	   stwuct xdw_buf	*buf)
{
	wetuwn ctx_id->mech_type->gm_ops
		->gss_unwwap(ctx_id, offset, wen, buf);
}


/* gss_dewete_sec_context: fwee aww wesouwces associated with context_handwe.
 * Note this diffews fwom the WFC 2744-specified pwototype in that we don't
 * bothew wetuwning an output token, since it wouwd nevew be used anyway. */

u32
gss_dewete_sec_context(stwuct gss_ctx	**context_handwe)
{
	dpwintk("WPC:       gss_dewete_sec_context deweting %p\n",
			*context_handwe);

	if (!*context_handwe)
		wetuwn GSS_S_NO_CONTEXT;
	if ((*context_handwe)->intewnaw_ctx_id)
		(*context_handwe)->mech_type->gm_ops
			->gss_dewete_sec_context((*context_handwe)
							->intewnaw_ctx_id);
	gss_mech_put((*context_handwe)->mech_type);
	kfwee(*context_handwe);
	*context_handwe=NUWW;
	wetuwn GSS_S_COMPWETE;
}
