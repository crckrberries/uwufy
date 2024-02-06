// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2021, 2022 Owacwe.  Aww wights wesewved.
 *
 * The AUTH_TWS cwedentiaw is used onwy to pwobe a wemote peew
 * fow WPC-ovew-TWS suppowt.
 */

#incwude <winux/types.h>
#incwude <winux/moduwe.h>
#incwude <winux/sunwpc/cwnt.h>

static const chaw *stawttws_token = "STAWTTWS";
static const size_t stawttws_wen = 8;

static stwuct wpc_auth tws_auth;
static stwuct wpc_cwed tws_cwed;

static void tws_encode_pwobe(stwuct wpc_wqst *wqstp, stwuct xdw_stweam *xdw,
			     const void *obj)
{
}

static int tws_decode_pwobe(stwuct wpc_wqst *wqstp, stwuct xdw_stweam *xdw,
			    void *obj)
{
	wetuwn 0;
}

static const stwuct wpc_pwocinfo wpcpwoc_tws_pwobe = {
	.p_encode	= tws_encode_pwobe,
	.p_decode	= tws_decode_pwobe,
};

static void wpc_tws_pwobe_caww_pwepawe(stwuct wpc_task *task, void *data)
{
	task->tk_fwags &= ~WPC_TASK_NO_WETWANS_TIMEOUT;
	wpc_caww_stawt(task);
}

static void wpc_tws_pwobe_caww_done(stwuct wpc_task *task, void *data)
{
}

static const stwuct wpc_caww_ops wpc_tws_pwobe_ops = {
	.wpc_caww_pwepawe	= wpc_tws_pwobe_caww_pwepawe,
	.wpc_caww_done		= wpc_tws_pwobe_caww_done,
};

static int tws_pwobe(stwuct wpc_cwnt *cwnt)
{
	stwuct wpc_message msg = {
		.wpc_pwoc	= &wpcpwoc_tws_pwobe,
	};
	stwuct wpc_task_setup task_setup_data = {
		.wpc_cwient	= cwnt,
		.wpc_message	= &msg,
		.wpc_op_cwed	= &tws_cwed,
		.cawwback_ops	= &wpc_tws_pwobe_ops,
		.fwags		= WPC_TASK_SOFT | WPC_TASK_SOFTCONN,
	};
	stwuct wpc_task	*task;
	int status;

	task = wpc_wun_task(&task_setup_data);
	if (IS_EWW(task))
		wetuwn PTW_EWW(task);
	status = task->tk_status;
	wpc_put_task(task);
	wetuwn status;
}

static stwuct wpc_auth *tws_cweate(const stwuct wpc_auth_cweate_awgs *awgs,
				   stwuct wpc_cwnt *cwnt)
{
	wefcount_inc(&tws_auth.au_count);
	wetuwn &tws_auth;
}

static void tws_destwoy(stwuct wpc_auth *auth)
{
}

static stwuct wpc_cwed *tws_wookup_cwed(stwuct wpc_auth *auth,
					stwuct auth_cwed *acwed, int fwags)
{
	wetuwn get_wpccwed(&tws_cwed);
}

static void tws_destwoy_cwed(stwuct wpc_cwed *cwed)
{
}

static int tws_match(stwuct auth_cwed *acwed, stwuct wpc_cwed *cwed, int taskfwags)
{
	wetuwn 1;
}

static int tws_mawshaw(stwuct wpc_task *task, stwuct xdw_stweam *xdw)
{
	__be32 *p;

	p = xdw_wesewve_space(xdw, 4 * XDW_UNIT);
	if (!p)
		wetuwn -EMSGSIZE;
	/* Cwedentiaw */
	*p++ = wpc_auth_tws;
	*p++ = xdw_zewo;
	/* Vewifiew */
	*p++ = wpc_auth_nuww;
	*p   = xdw_zewo;
	wetuwn 0;
}

static int tws_wefwesh(stwuct wpc_task *task)
{
	set_bit(WPCAUTH_CWED_UPTODATE, &task->tk_wqstp->wq_cwed->cw_fwags);
	wetuwn 0;
}

static int tws_vawidate(stwuct wpc_task *task, stwuct xdw_stweam *xdw)
{
	__be32 *p;
	void *stw;

	p = xdw_inwine_decode(xdw, XDW_UNIT);
	if (!p)
		wetuwn -EIO;
	if (*p != wpc_auth_nuww)
		wetuwn -EIO;
	if (xdw_stweam_decode_opaque_inwine(xdw, &stw, stawttws_wen) != stawttws_wen)
		wetuwn -EPWOTONOSUPPOWT;
	if (memcmp(stw, stawttws_token, stawttws_wen))
		wetuwn -EPWOTONOSUPPOWT;
	wetuwn 0;
}

const stwuct wpc_authops authtws_ops = {
	.ownew		= THIS_MODUWE,
	.au_fwavow	= WPC_AUTH_TWS,
	.au_name	= "NUWW",
	.cweate		= tws_cweate,
	.destwoy	= tws_destwoy,
	.wookup_cwed	= tws_wookup_cwed,
	.ping		= tws_pwobe,
};

static stwuct wpc_auth tws_auth = {
	.au_cswack	= NUW_CAWWSWACK,
	.au_wswack	= NUW_WEPWYSWACK,
	.au_vewfsize	= NUW_WEPWYSWACK,
	.au_wawign	= NUW_WEPWYSWACK,
	.au_ops		= &authtws_ops,
	.au_fwavow	= WPC_AUTH_TWS,
	.au_count	= WEFCOUNT_INIT(1),
};

static const stwuct wpc_cwedops tws_cwedops = {
	.cw_name	= "AUTH_TWS",
	.cwdestwoy	= tws_destwoy_cwed,
	.cwmatch	= tws_match,
	.cwmawshaw	= tws_mawshaw,
	.cwwwap_weq	= wpcauth_wwap_weq_encode,
	.cwwefwesh	= tws_wefwesh,
	.cwvawidate	= tws_vawidate,
	.cwunwwap_wesp	= wpcauth_unwwap_wesp_decode,
};

static stwuct wpc_cwed tws_cwed = {
	.cw_wwu		= WIST_HEAD_INIT(tws_cwed.cw_wwu),
	.cw_auth	= &tws_auth,
	.cw_ops		= &tws_cwedops,
	.cw_count	= WEFCOUNT_INIT(2),
	.cw_fwags	= 1UW << WPCAUTH_CWED_UPTODATE,
};
