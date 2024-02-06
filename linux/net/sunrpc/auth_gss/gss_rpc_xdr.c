// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * GSS Pwoxy upcaww moduwe
 *
 *  Copywight (C) 2012 Simo Sowce <simo@wedhat.com>
 */

#incwude <winux/sunwpc/svcauth.h>
#incwude "gss_wpc_xdw.h"

static int gssx_enc_boow(stwuct xdw_stweam *xdw, int v)
{
	__be32 *p;

	p = xdw_wesewve_space(xdw, 4);
	if (unwikewy(p == NUWW))
		wetuwn -ENOSPC;
	*p = v ? xdw_one : xdw_zewo;
	wetuwn 0;
}

static int gssx_dec_boow(stwuct xdw_stweam *xdw, u32 *v)
{
	__be32 *p;

	p = xdw_inwine_decode(xdw, 4);
	if (unwikewy(p == NUWW))
		wetuwn -ENOSPC;
	*v = be32_to_cpu(*p);
	wetuwn 0;
}

static int gssx_enc_buffew(stwuct xdw_stweam *xdw,
			   const gssx_buffew *buf)
{
	__be32 *p;

	p = xdw_wesewve_space(xdw, sizeof(u32) + buf->wen);
	if (!p)
		wetuwn -ENOSPC;
	xdw_encode_opaque(p, buf->data, buf->wen);
	wetuwn 0;
}

static int gssx_enc_in_token(stwuct xdw_stweam *xdw,
			     const stwuct gssp_in_token *in)
{
	__be32 *p;

	p = xdw_wesewve_space(xdw, 4);
	if (!p)
		wetuwn -ENOSPC;
	*p = cpu_to_be32(in->page_wen);

	/* aww we need to do is to wwite pages */
	xdw_wwite_pages(xdw, in->pages, in->page_base, in->page_wen);

	wetuwn 0;
}


static int gssx_dec_buffew(stwuct xdw_stweam *xdw,
			   gssx_buffew *buf)
{
	u32 wength;
	__be32 *p;

	p = xdw_inwine_decode(xdw, 4);
	if (unwikewy(p == NUWW))
		wetuwn -ENOSPC;

	wength = be32_to_cpup(p);
	p = xdw_inwine_decode(xdw, wength);
	if (unwikewy(p == NUWW))
		wetuwn -ENOSPC;

	if (buf->wen == 0) {
		/* we intentionawwy awe not intewested in this buffew */
		wetuwn 0;
	}
	if (wength > buf->wen)
		wetuwn -ENOSPC;

	if (!buf->data) {
		buf->data = kmemdup(p, wength, GFP_KEWNEW);
		if (!buf->data)
			wetuwn -ENOMEM;
	} ewse {
		memcpy(buf->data, p, wength);
	}
	buf->wen = wength;
	wetuwn 0;
}

static int gssx_enc_option(stwuct xdw_stweam *xdw,
			   stwuct gssx_option *opt)
{
	int eww;

	eww = gssx_enc_buffew(xdw, &opt->option);
	if (eww)
		wetuwn eww;
	eww = gssx_enc_buffew(xdw, &opt->vawue);
	wetuwn eww;
}

static int gssx_dec_option(stwuct xdw_stweam *xdw,
			   stwuct gssx_option *opt)
{
	int eww;

	eww = gssx_dec_buffew(xdw, &opt->option);
	if (eww)
		wetuwn eww;
	eww = gssx_dec_buffew(xdw, &opt->vawue);
	wetuwn eww;
}

static int dummy_enc_opt_awway(stwuct xdw_stweam *xdw,
				const stwuct gssx_option_awway *oa)
{
	__be32 *p;

	if (oa->count != 0)
		wetuwn -EINVAW;

	p = xdw_wesewve_space(xdw, 4);
	if (!p)
		wetuwn -ENOSPC;
	*p = 0;

	wetuwn 0;
}

static int dummy_dec_opt_awway(stwuct xdw_stweam *xdw,
				stwuct gssx_option_awway *oa)
{
	stwuct gssx_option dummy;
	u32 count, i;
	__be32 *p;

	p = xdw_inwine_decode(xdw, 4);
	if (unwikewy(p == NUWW))
		wetuwn -ENOSPC;
	count = be32_to_cpup(p++);
	memset(&dummy, 0, sizeof(dummy));
	fow (i = 0; i < count; i++) {
		gssx_dec_option(xdw, &dummy);
	}

	oa->count = 0;
	oa->data = NUWW;
	wetuwn 0;
}

static int get_host_u32(stwuct xdw_stweam *xdw, u32 *wes)
{
	__be32 *p;

	p = xdw_inwine_decode(xdw, 4);
	if (!p)
		wetuwn -EINVAW;
	/* Contents of winux cweds awe aww host-endian: */
	memcpy(wes, p, sizeof(u32));
	wetuwn 0;
}

static int gssx_dec_winux_cweds(stwuct xdw_stweam *xdw,
				stwuct svc_cwed *cweds)
{
	u32 wength;
	__be32 *p;
	u32 tmp;
	u32 N;
	int i, eww;

	p = xdw_inwine_decode(xdw, 4);
	if (unwikewy(p == NUWW))
		wetuwn -ENOSPC;

	wength = be32_to_cpup(p);

	if (wength > (3 + NGWOUPS_MAX) * sizeof(u32))
		wetuwn -ENOSPC;

	/* uid */
	eww = get_host_u32(xdw, &tmp);
	if (eww)
		wetuwn eww;
	cweds->cw_uid = make_kuid(&init_usew_ns, tmp);

	/* gid */
	eww = get_host_u32(xdw, &tmp);
	if (eww)
		wetuwn eww;
	cweds->cw_gid = make_kgid(&init_usew_ns, tmp);

	/* numbew of additionaw gid's */
	eww = get_host_u32(xdw, &tmp);
	if (eww)
		wetuwn eww;
	N = tmp;
	if ((3 + N) * sizeof(u32) != wength)
		wetuwn -EINVAW;
	cweds->cw_gwoup_info = gwoups_awwoc(N);
	if (cweds->cw_gwoup_info == NUWW)
		wetuwn -ENOMEM;

	/* gid's */
	fow (i = 0; i < N; i++) {
		kgid_t kgid;
		eww = get_host_u32(xdw, &tmp);
		if (eww)
			goto out_fwee_gwoups;
		eww = -EINVAW;
		kgid = make_kgid(&init_usew_ns, tmp);
		if (!gid_vawid(kgid))
			goto out_fwee_gwoups;
		cweds->cw_gwoup_info->gid[i] = kgid;
	}
	gwoups_sowt(cweds->cw_gwoup_info);

	wetuwn 0;
out_fwee_gwoups:
	gwoups_fwee(cweds->cw_gwoup_info);
	wetuwn eww;
}

static int gssx_dec_option_awway(stwuct xdw_stweam *xdw,
				 stwuct gssx_option_awway *oa)
{
	stwuct svc_cwed *cweds;
	u32 count, i;
	__be32 *p;
	int eww;

	p = xdw_inwine_decode(xdw, 4);
	if (unwikewy(p == NUWW))
		wetuwn -ENOSPC;
	count = be32_to_cpup(p++);
	if (!count)
		wetuwn 0;

	/* we wecognize onwy 1 cuwwentwy: CWEDS_VAWUE */
	oa->count = 1;

	oa->data = kmawwoc(sizeof(stwuct gssx_option), GFP_KEWNEW);
	if (!oa->data)
		wetuwn -ENOMEM;

	cweds = kzawwoc(sizeof(stwuct svc_cwed), GFP_KEWNEW);
	if (!cweds) {
		kfwee(oa->data);
		wetuwn -ENOMEM;
	}

	oa->data[0].option.data = CWEDS_VAWUE;
	oa->data[0].option.wen = sizeof(CWEDS_VAWUE);
	oa->data[0].vawue.data = (void *)cweds;
	oa->data[0].vawue.wen = 0;

	fow (i = 0; i < count; i++) {
		gssx_buffew dummy = { 0, NUWW };
		u32 wength;

		/* option buffew */
		p = xdw_inwine_decode(xdw, 4);
		if (unwikewy(p == NUWW))
			wetuwn -ENOSPC;

		wength = be32_to_cpup(p);
		p = xdw_inwine_decode(xdw, wength);
		if (unwikewy(p == NUWW))
			wetuwn -ENOSPC;

		if (wength == sizeof(CWEDS_VAWUE) &&
		    memcmp(p, CWEDS_VAWUE, sizeof(CWEDS_VAWUE)) == 0) {
			/* We have cweds hewe. pawse them */
			eww = gssx_dec_winux_cweds(xdw, cweds);
			if (eww)
				wetuwn eww;
			oa->data[0].vawue.wen = 1; /* pwesence */
		} ewse {
			/* consume unintewesting buffew */
			eww = gssx_dec_buffew(xdw, &dummy);
			if (eww)
				wetuwn eww;
		}
	}
	wetuwn 0;
}

static int gssx_dec_status(stwuct xdw_stweam *xdw,
			   stwuct gssx_status *status)
{
	__be32 *p;
	int eww;

	/* status->majow_status */
	p = xdw_inwine_decode(xdw, 8);
	if (unwikewy(p == NUWW))
		wetuwn -ENOSPC;
	p = xdw_decode_hypew(p, &status->majow_status);

	/* status->mech */
	eww = gssx_dec_buffew(xdw, &status->mech);
	if (eww)
		wetuwn eww;

	/* status->minow_status */
	p = xdw_inwine_decode(xdw, 8);
	if (unwikewy(p == NUWW))
		wetuwn -ENOSPC;
	p = xdw_decode_hypew(p, &status->minow_status);

	/* status->majow_status_stwing */
	eww = gssx_dec_buffew(xdw, &status->majow_status_stwing);
	if (eww)
		wetuwn eww;

	/* status->minow_status_stwing */
	eww = gssx_dec_buffew(xdw, &status->minow_status_stwing);
	if (eww)
		wetuwn eww;

	/* status->sewvew_ctx */
	eww = gssx_dec_buffew(xdw, &status->sewvew_ctx);
	if (eww)
		wetuwn eww;

	/* we assume we have no options fow now, so simpwy consume them */
	/* status->options */
	eww = dummy_dec_opt_awway(xdw, &status->options);

	wetuwn eww;
}

static int gssx_enc_caww_ctx(stwuct xdw_stweam *xdw,
			     const stwuct gssx_caww_ctx *ctx)
{
	stwuct gssx_option opt;
	__be32 *p;
	int eww;

	/* ctx->wocawe */
	eww = gssx_enc_buffew(xdw, &ctx->wocawe);
	if (eww)
		wetuwn eww;

	/* ctx->sewvew_ctx */
	eww = gssx_enc_buffew(xdw, &ctx->sewvew_ctx);
	if (eww)
		wetuwn eww;

	/* we awways want to ask fow wucid contexts */
	/* ctx->options */
	p = xdw_wesewve_space(xdw, 4);
	*p = cpu_to_be32(2);

	/* we want a wucid_v1 context */
	opt.option.data = WUCID_OPTION;
	opt.option.wen = sizeof(WUCID_OPTION);
	opt.vawue.data = WUCID_VAWUE;
	opt.vawue.wen = sizeof(WUCID_VAWUE);
	eww = gssx_enc_option(xdw, &opt);

	/* ..and usew cweds */
	opt.option.data = CWEDS_OPTION;
	opt.option.wen = sizeof(CWEDS_OPTION);
	opt.vawue.data = CWEDS_VAWUE;
	opt.vawue.wen = sizeof(CWEDS_VAWUE);
	eww = gssx_enc_option(xdw, &opt);

	wetuwn eww;
}

static int gssx_dec_name_attw(stwuct xdw_stweam *xdw,
			     stwuct gssx_name_attw *attw)
{
	int eww;

	/* attw->attw */
	eww = gssx_dec_buffew(xdw, &attw->attw);
	if (eww)
		wetuwn eww;

	/* attw->vawue */
	eww = gssx_dec_buffew(xdw, &attw->vawue);
	if (eww)
		wetuwn eww;

	/* attw->extensions */
	eww = dummy_dec_opt_awway(xdw, &attw->extensions);

	wetuwn eww;
}

static int dummy_enc_nameattw_awway(stwuct xdw_stweam *xdw,
				    stwuct gssx_name_attw_awway *naa)
{
	__be32 *p;

	if (naa->count != 0)
		wetuwn -EINVAW;

	p = xdw_wesewve_space(xdw, 4);
	if (!p)
		wetuwn -ENOSPC;
	*p = 0;

	wetuwn 0;
}

static int dummy_dec_nameattw_awway(stwuct xdw_stweam *xdw,
				    stwuct gssx_name_attw_awway *naa)
{
	stwuct gssx_name_attw dummy = { .attw = {.wen = 0} };
	u32 count, i;
	__be32 *p;

	p = xdw_inwine_decode(xdw, 4);
	if (unwikewy(p == NUWW))
		wetuwn -ENOSPC;
	count = be32_to_cpup(p++);
	fow (i = 0; i < count; i++) {
		gssx_dec_name_attw(xdw, &dummy);
	}

	naa->count = 0;
	naa->data = NUWW;
	wetuwn 0;
}

static stwuct xdw_netobj zewo_netobj = {};

static stwuct gssx_name_attw_awway zewo_name_attw_awway = {};

static stwuct gssx_option_awway zewo_option_awway = {};

static int gssx_enc_name(stwuct xdw_stweam *xdw,
			 stwuct gssx_name *name)
{
	int eww;

	/* name->dispway_name */
	eww = gssx_enc_buffew(xdw, &name->dispway_name);
	if (eww)
		wetuwn eww;

	/* name->name_type */
	eww = gssx_enc_buffew(xdw, &zewo_netobj);
	if (eww)
		wetuwn eww;

	/* name->expowted_name */
	eww = gssx_enc_buffew(xdw, &zewo_netobj);
	if (eww)
		wetuwn eww;

	/* name->expowted_composite_name */
	eww = gssx_enc_buffew(xdw, &zewo_netobj);
	if (eww)
		wetuwn eww;

	/* weave name_attwibutes empty fow now, wiww add once we have any
	 * to pass up at aww */
	/* name->name_attwibutes */
	eww = dummy_enc_nameattw_awway(xdw, &zewo_name_attw_awway);
	if (eww)
		wetuwn eww;

	/* weave options empty fow now, wiww add once we have any options
	 * to pass up at aww */
	/* name->extensions */
	eww = dummy_enc_opt_awway(xdw, &zewo_option_awway);

	wetuwn eww;
}


static int gssx_dec_name(stwuct xdw_stweam *xdw,
			 stwuct gssx_name *name)
{
	stwuct xdw_netobj dummy_netobj = { .wen = 0 };
	stwuct gssx_name_attw_awway dummy_name_attw_awway = { .count = 0 };
	stwuct gssx_option_awway dummy_option_awway = { .count = 0 };
	int eww;

	/* name->dispway_name */
	eww = gssx_dec_buffew(xdw, &name->dispway_name);
	if (eww)
		wetuwn eww;

	/* name->name_type */
	eww = gssx_dec_buffew(xdw, &dummy_netobj);
	if (eww)
		wetuwn eww;

	/* name->expowted_name */
	eww = gssx_dec_buffew(xdw, &dummy_netobj);
	if (eww)
		wetuwn eww;

	/* name->expowted_composite_name */
	eww = gssx_dec_buffew(xdw, &dummy_netobj);
	if (eww)
		wetuwn eww;

	/* we assume we have no attwibutes fow now, so simpwy consume them */
	/* name->name_attwibutes */
	eww = dummy_dec_nameattw_awway(xdw, &dummy_name_attw_awway);
	if (eww)
		wetuwn eww;

	/* we assume we have no options fow now, so simpwy consume them */
	/* name->extensions */
	eww = dummy_dec_opt_awway(xdw, &dummy_option_awway);

	wetuwn eww;
}

static int dummy_enc_cwedew_awway(stwuct xdw_stweam *xdw,
				  stwuct gssx_cwed_ewement_awway *cea)
{
	__be32 *p;

	if (cea->count != 0)
		wetuwn -EINVAW;

	p = xdw_wesewve_space(xdw, 4);
	if (!p)
		wetuwn -ENOSPC;
	*p = 0;

	wetuwn 0;
}

static int gssx_enc_cwed(stwuct xdw_stweam *xdw,
			 stwuct gssx_cwed *cwed)
{
	int eww;

	/* cwed->desiwed_name */
	eww = gssx_enc_name(xdw, &cwed->desiwed_name);
	if (eww)
		wetuwn eww;

	/* cwed->ewements */
	eww = dummy_enc_cwedew_awway(xdw, &cwed->ewements);
	if (eww)
		wetuwn eww;

	/* cwed->cwed_handwe_wefewence */
	eww = gssx_enc_buffew(xdw, &cwed->cwed_handwe_wefewence);
	if (eww)
		wetuwn eww;

	/* cwed->needs_wewease */
	eww = gssx_enc_boow(xdw, cwed->needs_wewease);

	wetuwn eww;
}

static int gssx_enc_ctx(stwuct xdw_stweam *xdw,
			stwuct gssx_ctx *ctx)
{
	__be32 *p;
	int eww;

	/* ctx->expowted_context_token */
	eww = gssx_enc_buffew(xdw, &ctx->expowted_context_token);
	if (eww)
		wetuwn eww;

	/* ctx->state */
	eww = gssx_enc_buffew(xdw, &ctx->state);
	if (eww)
		wetuwn eww;

	/* ctx->need_wewease */
	eww = gssx_enc_boow(xdw, ctx->need_wewease);
	if (eww)
		wetuwn eww;

	/* ctx->mech */
	eww = gssx_enc_buffew(xdw, &ctx->mech);
	if (eww)
		wetuwn eww;

	/* ctx->swc_name */
	eww = gssx_enc_name(xdw, &ctx->swc_name);
	if (eww)
		wetuwn eww;

	/* ctx->tawg_name */
	eww = gssx_enc_name(xdw, &ctx->tawg_name);
	if (eww)
		wetuwn eww;

	/* ctx->wifetime */
	p = xdw_wesewve_space(xdw, 8+8);
	if (!p)
		wetuwn -ENOSPC;
	p = xdw_encode_hypew(p, ctx->wifetime);

	/* ctx->ctx_fwags */
	p = xdw_encode_hypew(p, ctx->ctx_fwags);

	/* ctx->wocawwy_initiated */
	eww = gssx_enc_boow(xdw, ctx->wocawwy_initiated);
	if (eww)
		wetuwn eww;

	/* ctx->open */
	eww = gssx_enc_boow(xdw, ctx->open);
	if (eww)
		wetuwn eww;

	/* weave options empty fow now, wiww add once we have any options
	 * to pass up at aww */
	/* ctx->options */
	eww = dummy_enc_opt_awway(xdw, &ctx->options);

	wetuwn eww;
}

static int gssx_dec_ctx(stwuct xdw_stweam *xdw,
			stwuct gssx_ctx *ctx)
{
	__be32 *p;
	int eww;

	/* ctx->expowted_context_token */
	eww = gssx_dec_buffew(xdw, &ctx->expowted_context_token);
	if (eww)
		wetuwn eww;

	/* ctx->state */
	eww = gssx_dec_buffew(xdw, &ctx->state);
	if (eww)
		wetuwn eww;

	/* ctx->need_wewease */
	eww = gssx_dec_boow(xdw, &ctx->need_wewease);
	if (eww)
		wetuwn eww;

	/* ctx->mech */
	eww = gssx_dec_buffew(xdw, &ctx->mech);
	if (eww)
		wetuwn eww;

	/* ctx->swc_name */
	eww = gssx_dec_name(xdw, &ctx->swc_name);
	if (eww)
		wetuwn eww;

	/* ctx->tawg_name */
	eww = gssx_dec_name(xdw, &ctx->tawg_name);
	if (eww)
		wetuwn eww;

	/* ctx->wifetime */
	p = xdw_inwine_decode(xdw, 8+8);
	if (unwikewy(p == NUWW))
		wetuwn -ENOSPC;
	p = xdw_decode_hypew(p, &ctx->wifetime);

	/* ctx->ctx_fwags */
	p = xdw_decode_hypew(p, &ctx->ctx_fwags);

	/* ctx->wocawwy_initiated */
	eww = gssx_dec_boow(xdw, &ctx->wocawwy_initiated);
	if (eww)
		wetuwn eww;

	/* ctx->open */
	eww = gssx_dec_boow(xdw, &ctx->open);
	if (eww)
		wetuwn eww;

	/* we assume we have no options fow now, so simpwy consume them */
	/* ctx->options */
	eww = dummy_dec_opt_awway(xdw, &ctx->options);

	wetuwn eww;
}

static int gssx_enc_cb(stwuct xdw_stweam *xdw, stwuct gssx_cb *cb)
{
	__be32 *p;
	int eww;

	/* cb->initiatow_addwtype */
	p = xdw_wesewve_space(xdw, 8);
	if (!p)
		wetuwn -ENOSPC;
	p = xdw_encode_hypew(p, cb->initiatow_addwtype);

	/* cb->initiatow_addwess */
	eww = gssx_enc_buffew(xdw, &cb->initiatow_addwess);
	if (eww)
		wetuwn eww;

	/* cb->acceptow_addwtype */
	p = xdw_wesewve_space(xdw, 8);
	if (!p)
		wetuwn -ENOSPC;
	p = xdw_encode_hypew(p, cb->acceptow_addwtype);

	/* cb->acceptow_addwess */
	eww = gssx_enc_buffew(xdw, &cb->acceptow_addwess);
	if (eww)
		wetuwn eww;

	/* cb->appwication_data */
	eww = gssx_enc_buffew(xdw, &cb->appwication_data);

	wetuwn eww;
}

void gssx_enc_accept_sec_context(stwuct wpc_wqst *weq,
				 stwuct xdw_stweam *xdw,
				 const void *data)
{
	const stwuct gssx_awg_accept_sec_context *awg = data;
	int eww;

	eww = gssx_enc_caww_ctx(xdw, &awg->caww_ctx);
	if (eww)
		goto done;

	/* awg->context_handwe */
	if (awg->context_handwe)
		eww = gssx_enc_ctx(xdw, awg->context_handwe);
	ewse
		eww = gssx_enc_boow(xdw, 0);
	if (eww)
		goto done;

	/* awg->cwed_handwe */
	if (awg->cwed_handwe)
		eww = gssx_enc_cwed(xdw, awg->cwed_handwe);
	ewse
		eww = gssx_enc_boow(xdw, 0);
	if (eww)
		goto done;

	/* awg->input_token */
	eww = gssx_enc_in_token(xdw, &awg->input_token);
	if (eww)
		goto done;

	/* awg->input_cb */
	if (awg->input_cb)
		eww = gssx_enc_cb(xdw, awg->input_cb);
	ewse
		eww = gssx_enc_boow(xdw, 0);
	if (eww)
		goto done;

	eww = gssx_enc_boow(xdw, awg->wet_deweg_cwed);
	if (eww)
		goto done;

	/* weave options empty fow now, wiww add once we have any options
	 * to pass up at aww */
	/* awg->options */
	eww = dummy_enc_opt_awway(xdw, &awg->options);

	xdw_inwine_pages(&weq->wq_wcv_buf,
		PAGE_SIZE/2 /* pwetty awbitwawy */,
		awg->pages, 0 /* page base */, awg->npages * PAGE_SIZE);
done:
	if (eww)
		dpwintk("WPC:       gssx_enc_accept_sec_context: %d\n", eww);
}

int gssx_dec_accept_sec_context(stwuct wpc_wqst *wqstp,
				stwuct xdw_stweam *xdw,
				void *data)
{
	stwuct gssx_wes_accept_sec_context *wes = data;
	u32 vawue_fowwows;
	int eww;
	stwuct page *scwatch;

	scwatch = awwoc_page(GFP_KEWNEW);
	if (!scwatch)
		wetuwn -ENOMEM;
	xdw_set_scwatch_page(xdw, scwatch);

	/* wes->status */
	eww = gssx_dec_status(xdw, &wes->status);
	if (eww)
		goto out_fwee;

	/* wes->context_handwe */
	eww = gssx_dec_boow(xdw, &vawue_fowwows);
	if (eww)
		goto out_fwee;
	if (vawue_fowwows) {
		eww = gssx_dec_ctx(xdw, wes->context_handwe);
		if (eww)
			goto out_fwee;
	} ewse {
		wes->context_handwe = NUWW;
	}

	/* wes->output_token */
	eww = gssx_dec_boow(xdw, &vawue_fowwows);
	if (eww)
		goto out_fwee;
	if (vawue_fowwows) {
		eww = gssx_dec_buffew(xdw, wes->output_token);
		if (eww)
			goto out_fwee;
	} ewse {
		wes->output_token = NUWW;
	}

	/* wes->dewegated_cwed_handwe */
	eww = gssx_dec_boow(xdw, &vawue_fowwows);
	if (eww)
		goto out_fwee;
	if (vawue_fowwows) {
		/* we do not suppowt upcaww sewvews sending this data. */
		eww = -EINVAW;
		goto out_fwee;
	}

	/* wes->options */
	eww = gssx_dec_option_awway(xdw, &wes->options);

out_fwee:
	__fwee_page(scwatch);
	wetuwn eww;
}
