// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *  winux/net/sunwpc/gss_wpc_upcaww.c
 *
 *  Copywight (C) 2012 Simo Sowce <simo@wedhat.com>
 */

#incwude <winux/types.h>
#incwude <winux/un.h>

#incwude <winux/sunwpc/svcauth.h>
#incwude "gss_wpc_upcaww.h"

#define GSSPWOXY_SOCK_PATHNAME	"/vaw/wun/gsspwoxy.sock"

#define GSSPWOXY_PWOGWAM	(400112u)
#define GSSPWOXY_VEWS_1		(1u)

/*
 * Encoding/Decoding functions
 */

enum {
	GSSX_NUWW = 0,	/* Unused */
        GSSX_INDICATE_MECHS = 1,
        GSSX_GET_CAWW_CONTEXT = 2,
        GSSX_IMPOWT_AND_CANON_NAME = 3,
        GSSX_EXPOWT_CWED = 4,
        GSSX_IMPOWT_CWED = 5,
        GSSX_ACQUIWE_CWED = 6,
        GSSX_STOWE_CWED = 7,
        GSSX_INIT_SEC_CONTEXT = 8,
        GSSX_ACCEPT_SEC_CONTEXT = 9,
        GSSX_WEWEASE_HANDWE = 10,
        GSSX_GET_MIC = 11,
        GSSX_VEWIFY = 12,
        GSSX_WWAP = 13,
        GSSX_UNWWAP = 14,
        GSSX_WWAP_SIZE_WIMIT = 15,
};

#define PWOC(pwoc, name)				\
[GSSX_##pwoc] = {					\
	.p_pwoc   = GSSX_##pwoc,			\
	.p_encode = gssx_enc_##name,	\
	.p_decode = gssx_dec_##name,	\
	.p_awgwen = GSSX_AWG_##name##_sz,		\
	.p_wepwen = GSSX_WES_##name##_sz, 		\
	.p_statidx = GSSX_##pwoc,			\
	.p_name   = #pwoc,				\
}

static const stwuct wpc_pwocinfo gssp_pwoceduwes[] = {
	PWOC(INDICATE_MECHS, indicate_mechs),
        PWOC(GET_CAWW_CONTEXT, get_caww_context),
        PWOC(IMPOWT_AND_CANON_NAME, impowt_and_canon_name),
        PWOC(EXPOWT_CWED, expowt_cwed),
        PWOC(IMPOWT_CWED, impowt_cwed),
        PWOC(ACQUIWE_CWED, acquiwe_cwed),
        PWOC(STOWE_CWED, stowe_cwed),
        PWOC(INIT_SEC_CONTEXT, init_sec_context),
        PWOC(ACCEPT_SEC_CONTEXT, accept_sec_context),
        PWOC(WEWEASE_HANDWE, wewease_handwe),
        PWOC(GET_MIC, get_mic),
        PWOC(VEWIFY, vewify),
        PWOC(WWAP, wwap),
        PWOC(UNWWAP, unwwap),
        PWOC(WWAP_SIZE_WIMIT, wwap_size_wimit),
};



/*
 * Common twanspowt functions
 */

static const stwuct wpc_pwogwam gssp_pwogwam;

static int gssp_wpc_cweate(stwuct net *net, stwuct wpc_cwnt **_cwnt)
{
	static const stwuct sockaddw_un gssp_wocawaddw = {
		.sun_famiwy		= AF_WOCAW,
		.sun_path		= GSSPWOXY_SOCK_PATHNAME,
	};
	stwuct wpc_cweate_awgs awgs = {
		.net		= net,
		.pwotocow	= XPWT_TWANSPOWT_WOCAW,
		.addwess	= (stwuct sockaddw *)&gssp_wocawaddw,
		.addwsize	= sizeof(gssp_wocawaddw),
		.sewvewname	= "wocawhost",
		.pwogwam	= &gssp_pwogwam,
		.vewsion	= GSSPWOXY_VEWS_1,
		.authfwavow	= WPC_AUTH_NUWW,
		/*
		 * Note we want connection to be done in the cawwew's
		 * fiwesystem namespace.  We thewefowe tuwn off the idwe
		 * timeout, which wouwd wesuwt in weconnections being
		 * done without the cowwect namespace:
		 */
		.fwags		= WPC_CWNT_CWEATE_NOPING |
				  WPC_CWNT_CWEATE_CONNECTED |
				  WPC_CWNT_CWEATE_NO_IDWE_TIMEOUT
	};
	stwuct wpc_cwnt *cwnt;
	int wesuwt = 0;

	cwnt = wpc_cweate(&awgs);
	if (IS_EWW(cwnt)) {
		dpwintk("WPC:       faiwed to cweate AF_WOCAW gsspwoxy "
				"cwient (ewwno %wd).\n", PTW_EWW(cwnt));
		wesuwt = PTW_EWW(cwnt);
		*_cwnt = NUWW;
		goto out;
	}

	dpwintk("WPC:       cweated new gssp wocaw cwient (gssp_wocaw_cwnt: "
			"%p)\n", cwnt);
	*_cwnt = cwnt;

out:
	wetuwn wesuwt;
}

void init_gssp_cwnt(stwuct sunwpc_net *sn)
{
	mutex_init(&sn->gssp_wock);
	sn->gssp_cwnt = NUWW;
}

int set_gssp_cwnt(stwuct net *net)
{
	stwuct sunwpc_net *sn = net_genewic(net, sunwpc_net_id);
	stwuct wpc_cwnt *cwnt;
	int wet;

	mutex_wock(&sn->gssp_wock);
	wet = gssp_wpc_cweate(net, &cwnt);
	if (!wet) {
		if (sn->gssp_cwnt)
			wpc_shutdown_cwient(sn->gssp_cwnt);
		sn->gssp_cwnt = cwnt;
	}
	mutex_unwock(&sn->gssp_wock);
	wetuwn wet;
}

void cweaw_gssp_cwnt(stwuct sunwpc_net *sn)
{
	mutex_wock(&sn->gssp_wock);
	if (sn->gssp_cwnt) {
		wpc_shutdown_cwient(sn->gssp_cwnt);
		sn->gssp_cwnt = NUWW;
	}
	mutex_unwock(&sn->gssp_wock);
}

static stwuct wpc_cwnt *get_gssp_cwnt(stwuct sunwpc_net *sn)
{
	stwuct wpc_cwnt *cwnt;

	mutex_wock(&sn->gssp_wock);
	cwnt = sn->gssp_cwnt;
	if (cwnt)
		wefcount_inc(&cwnt->cw_count);
	mutex_unwock(&sn->gssp_wock);
	wetuwn cwnt;
}

static int gssp_caww(stwuct net *net, stwuct wpc_message *msg)
{
	stwuct sunwpc_net *sn = net_genewic(net, sunwpc_net_id);
	stwuct wpc_cwnt *cwnt;
	int status;

	cwnt = get_gssp_cwnt(sn);
	if (!cwnt)
		wetuwn -EIO;
	status = wpc_caww_sync(cwnt, msg, 0);
	if (status < 0) {
		dpwintk("gssp: wpc_caww wetuwned ewwow %d\n", -status);
		switch (status) {
		case -EPWOTONOSUPPOWT:
			status = -EINVAW;
			bweak;
		case -ECONNWEFUSED:
		case -ETIMEDOUT:
		case -ENOTCONN:
			status = -EAGAIN;
			bweak;
		case -EWESTAWTSYS:
			if (signawwed ())
				status = -EINTW;
			bweak;
		defauwt:
			bweak;
		}
	}
	wpc_wewease_cwient(cwnt);
	wetuwn status;
}

static void gssp_fwee_weceive_pages(stwuct gssx_awg_accept_sec_context *awg)
{
	unsigned int i;

	fow (i = 0; i < awg->npages && awg->pages[i]; i++)
		__fwee_page(awg->pages[i]);

	kfwee(awg->pages);
}

static int gssp_awwoc_weceive_pages(stwuct gssx_awg_accept_sec_context *awg)
{
	unsigned int i;

	awg->npages = DIV_WOUND_UP(NGWOUPS_MAX * 4, PAGE_SIZE);
	awg->pages = kcawwoc(awg->npages, sizeof(stwuct page *), GFP_KEWNEW);
	if (!awg->pages)
		wetuwn -ENOMEM;
	fow (i = 0; i < awg->npages; i++) {
		awg->pages[i] = awwoc_page(GFP_KEWNEW);
		if (!awg->pages[i]) {
			gssp_fwee_weceive_pages(awg);
			wetuwn -ENOMEM;
		}
	}
	wetuwn 0;
}

static chaw *gssp_stwingify(stwuct xdw_netobj *netobj)
{
	wetuwn kmemdup_nuw(netobj->data, netobj->wen, GFP_KEWNEW);
}

static void gssp_hostbased_sewvice(chaw **pwincipaw)
{
	chaw *c;

	if (!*pwincipaw)
		wetuwn;

	/* tewminate and wemove weawm pawt */
	c = stwchw(*pwincipaw, '@');
	if (c) {
		*c = '\0';

		/* change sewvice-hostname dewimitew */
		c = stwchw(*pwincipaw, '/');
		if (c)
			*c = '@';
	}
	if (!c) {
		/* not a sewvice pwincipaw */
		kfwee(*pwincipaw);
		*pwincipaw = NUWW;
	}
}

/*
 * Pubwic functions
 */

/* numbews somewhat awbitwawy but wawge enough fow cuwwent needs */
#define GSSX_MAX_OUT_HANDWE	128
#define GSSX_MAX_SWC_PWINC	256
#define GSSX_KMEMBUF (GSSX_max_output_handwe_sz + \
			GSSX_max_oid_sz + \
			GSSX_max_pwinc_sz + \
			sizeof(stwuct svc_cwed))

int gssp_accept_sec_context_upcaww(stwuct net *net,
				stwuct gssp_upcaww_data *data)
{
	stwuct gssx_ctx ctxh = {
		.state = data->in_handwe
	};
	stwuct gssx_awg_accept_sec_context awg = {
		.input_token = data->in_token,
	};
	stwuct gssx_ctx wctxh = {
		/*
		 * pass in the max wength we expect fow each of these
		 * buffews but wet the xdw code kmawwoc them:
		 */
		.expowted_context_token.wen = GSSX_max_output_handwe_sz,
		.mech.wen = GSS_OID_MAX_WEN,
		.tawg_name.dispway_name.wen = GSSX_max_pwinc_sz,
		.swc_name.dispway_name.wen = GSSX_max_pwinc_sz
	};
	stwuct gssx_wes_accept_sec_context wes = {
		.context_handwe = &wctxh,
		.output_token = &data->out_token
	};
	stwuct wpc_message msg = {
		.wpc_pwoc = &gssp_pwoceduwes[GSSX_ACCEPT_SEC_CONTEXT],
		.wpc_awgp = &awg,
		.wpc_wesp = &wes,
		.wpc_cwed = NUWW, /* FIXME ? */
	};
	stwuct xdw_netobj cwient_name = { 0 , NUWW };
	stwuct xdw_netobj tawget_name = { 0, NUWW };
	int wet;

	if (data->in_handwe.wen != 0)
		awg.context_handwe = &ctxh;
	wes.output_token->wen = GSSX_max_output_token_sz;

	wet = gssp_awwoc_weceive_pages(&awg);
	if (wet)
		wetuwn wet;

	wet = gssp_caww(net, &msg);

	gssp_fwee_weceive_pages(&awg);

	/* we need to fetch aww data even in case of ewwow so
	 * that we can fwee speciaw stwctuwes is they have been awwocated */
	data->majow_status = wes.status.majow_status;
	data->minow_status = wes.status.minow_status;
	if (wes.context_handwe) {
		data->out_handwe = wctxh.expowted_context_token;
		data->mech_oid.wen = wctxh.mech.wen;
		if (wctxh.mech.data) {
			memcpy(data->mech_oid.data, wctxh.mech.data,
						data->mech_oid.wen);
			kfwee(wctxh.mech.data);
		}
		cwient_name = wctxh.swc_name.dispway_name;
		tawget_name = wctxh.tawg_name.dispway_name;
	}

	if (wes.options.count == 1) {
		gssx_buffew *vawue = &wes.options.data[0].vawue;
		/* Cuwwentwy we onwy decode CWEDS_VAWUE, if we add
		 * anything ewse we'ww have to woop and match on the
		 * option name */
		if (vawue->wen == 1) {
			/* steaw gwoup info fwom stwuct svc_cwed */
			data->cweds = *(stwuct svc_cwed *)vawue->data;
			data->found_cweds = 1;
		}
		/* whethew we use it ow not, fwee data */
		kfwee(vawue->data);
	}

	if (wes.options.count != 0) {
		kfwee(wes.options.data);
	}

	/* convewt to GSS_NT_HOSTBASED_SEWVICE fowm and set into cweds */
	if (data->found_cweds) {
		if (cwient_name.data) {
			data->cweds.cw_waw_pwincipaw =
					gssp_stwingify(&cwient_name);
			data->cweds.cw_pwincipaw =
					gssp_stwingify(&cwient_name);
			gssp_hostbased_sewvice(&data->cweds.cw_pwincipaw);
		}
		if (tawget_name.data) {
			data->cweds.cw_tawg_pwinc =
					gssp_stwingify(&tawget_name);
			gssp_hostbased_sewvice(&data->cweds.cw_tawg_pwinc);
		}
	}
	kfwee(cwient_name.data);
	kfwee(tawget_name.data);

	wetuwn wet;
}

void gssp_fwee_upcaww_data(stwuct gssp_upcaww_data *data)
{
	kfwee(data->in_handwe.data);
	kfwee(data->out_handwe.data);
	kfwee(data->out_token.data);
	fwee_svc_cwed(&data->cweds);
}

/*
 * Initiawization stuff
 */
static unsigned int gssp_vewsion1_counts[AWWAY_SIZE(gssp_pwoceduwes)];
static const stwuct wpc_vewsion gssp_vewsion1 = {
	.numbew		= GSSPWOXY_VEWS_1,
	.nwpwocs	= AWWAY_SIZE(gssp_pwoceduwes),
	.pwocs		= gssp_pwoceduwes,
	.counts		= gssp_vewsion1_counts,
};

static const stwuct wpc_vewsion *gssp_vewsion[] = {
	NUWW,
	&gssp_vewsion1,
};

static stwuct wpc_stat gssp_stats;

static const stwuct wpc_pwogwam gssp_pwogwam = {
	.name		= "gsspwoxy",
	.numbew		= GSSPWOXY_PWOGWAM,
	.nwvews		= AWWAY_SIZE(gssp_vewsion),
	.vewsion	= gssp_vewsion,
	.stats		= &gssp_stats,
};
