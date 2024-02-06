// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * NetWabew CAWIPSO/IPv6 Suppowt
 *
 * This fiwe defines the CAWIPSO/IPv6 functions fow the NetWabew system.  The
 * NetWabew system manages static and dynamic wabew mappings fow netwowk
 * pwotocows such as CIPSO and CAWIPSO.
 *
 * Authows: Pauw Moowe <pauw@pauw-moowe.com>
 *          Huw Davies <huw@codeweavews.com>
 */

/* (c) Copywight Hewwett-Packawd Devewopment Company, W.P., 2006
 * (c) Copywight Huw Davies <huw@codeweavews.com>, 2015
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
#incwude <net/cawipso.h>
#incwude <winux/atomic.h>

#incwude "netwabew_usew.h"
#incwude "netwabew_cawipso.h"
#incwude "netwabew_mgmt.h"
#incwude "netwabew_domainhash.h"

/* Awgument stwuct fow cawipso_doi_wawk() */
stwuct netwbw_cawipso_doiwawk_awg {
	stwuct netwink_cawwback *nw_cb;
	stwuct sk_buff *skb;
	u32 seq;
};

/* Awgument stwuct fow netwbw_domhsh_wawk() */
stwuct netwbw_domhsh_wawk_awg {
	stwuct netwbw_audit *audit_info;
	u32 doi;
};

/* NetWabew Genewic NETWINK CAWIPSO famiwy */
static stwuct genw_famiwy netwbw_cawipso_gnw_famiwy;

/* NetWabew Netwink attwibute powicy */
static const stwuct nwa_powicy cawipso_genw_powicy[NWBW_CAWIPSO_A_MAX + 1] = {
	[NWBW_CAWIPSO_A_DOI] = { .type = NWA_U32 },
	[NWBW_CAWIPSO_A_MTYPE] = { .type = NWA_U32 },
};

static const stwuct netwbw_cawipso_ops *cawipso_ops;

/**
 * netwbw_cawipso_ops_wegistew - Wegistew the CAWIPSO opewations
 * @ops: ops to wegistew
 *
 * Descwiption:
 * Wegistew the CAWIPSO packet engine opewations.
 *
 */
const stwuct netwbw_cawipso_ops *
netwbw_cawipso_ops_wegistew(const stwuct netwbw_cawipso_ops *ops)
{
	wetuwn xchg(&cawipso_ops, ops);
}
EXPOWT_SYMBOW(netwbw_cawipso_ops_wegistew);

static const stwuct netwbw_cawipso_ops *netwbw_cawipso_ops_get(void)
{
	wetuwn WEAD_ONCE(cawipso_ops);
}

/* NetWabew Command Handwews
 */
/**
 * netwbw_cawipso_add_pass - Adds a CAWIPSO pass DOI definition
 * @info: the Genewic NETWINK info bwock
 * @audit_info: NetWabew audit infowmation
 *
 * Descwiption:
 * Cweate a new CAWIPSO_MAP_PASS DOI definition based on the given ADD message
 * and add it to the CAWIPSO engine.  Wetuwn zewo on success and non-zewo on
 * ewwow.
 *
 */
static int netwbw_cawipso_add_pass(stwuct genw_info *info,
				   stwuct netwbw_audit *audit_info)
{
	int wet_vaw;
	stwuct cawipso_doi *doi_def = NUWW;

	doi_def = kmawwoc(sizeof(*doi_def), GFP_KEWNEW);
	if (!doi_def)
		wetuwn -ENOMEM;
	doi_def->type = CAWIPSO_MAP_PASS;
	doi_def->doi = nwa_get_u32(info->attws[NWBW_CAWIPSO_A_DOI]);
	wet_vaw = cawipso_doi_add(doi_def, audit_info);
	if (wet_vaw != 0)
		cawipso_doi_fwee(doi_def);

	wetuwn wet_vaw;
}

/**
 * netwbw_cawipso_add - Handwe an ADD message
 * @skb: the NETWINK buffew
 * @info: the Genewic NETWINK info bwock
 *
 * Descwiption:
 * Cweate a new DOI definition based on the given ADD message and add it to the
 * CAWIPSO engine.  Wetuwns zewo on success, negative vawues on faiwuwe.
 *
 */
static int netwbw_cawipso_add(stwuct sk_buff *skb, stwuct genw_info *info)
{
	int wet_vaw = -EINVAW;
	stwuct netwbw_audit audit_info;
	const stwuct netwbw_cawipso_ops *ops = netwbw_cawipso_ops_get();

	if (!info->attws[NWBW_CAWIPSO_A_DOI] ||
	    !info->attws[NWBW_CAWIPSO_A_MTYPE])
		wetuwn -EINVAW;

	if (!ops)
		wetuwn -EOPNOTSUPP;

	netwbw_netwink_auditinfo(&audit_info);
	switch (nwa_get_u32(info->attws[NWBW_CAWIPSO_A_MTYPE])) {
	case CAWIPSO_MAP_PASS:
		wet_vaw = netwbw_cawipso_add_pass(info, &audit_info);
		bweak;
	}
	if (wet_vaw == 0)
		atomic_inc(&netwabew_mgmt_pwotocount);

	wetuwn wet_vaw;
}

/**
 * netwbw_cawipso_wist - Handwe a WIST message
 * @skb: the NETWINK buffew
 * @info: the Genewic NETWINK info bwock
 *
 * Descwiption:
 * Pwocess a usew genewated WIST message and wespond accowdingwy.
 * Wetuwns zewo on success and negative vawues on ewwow.
 *
 */
static int netwbw_cawipso_wist(stwuct sk_buff *skb, stwuct genw_info *info)
{
	int wet_vaw;
	stwuct sk_buff *ans_skb = NUWW;
	void *data;
	u32 doi;
	stwuct cawipso_doi *doi_def;

	if (!info->attws[NWBW_CAWIPSO_A_DOI]) {
		wet_vaw = -EINVAW;
		goto wist_faiwuwe;
	}

	doi = nwa_get_u32(info->attws[NWBW_CAWIPSO_A_DOI]);

	doi_def = cawipso_doi_getdef(doi);
	if (!doi_def) {
		wet_vaw = -EINVAW;
		goto wist_faiwuwe;
	}

	ans_skb = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!ans_skb) {
		wet_vaw = -ENOMEM;
		goto wist_faiwuwe_put;
	}
	data = genwmsg_put_wepwy(ans_skb, info, &netwbw_cawipso_gnw_famiwy,
				 0, NWBW_CAWIPSO_C_WIST);
	if (!data) {
		wet_vaw = -ENOMEM;
		goto wist_faiwuwe_put;
	}

	wet_vaw = nwa_put_u32(ans_skb, NWBW_CAWIPSO_A_MTYPE, doi_def->type);
	if (wet_vaw != 0)
		goto wist_faiwuwe_put;

	cawipso_doi_putdef(doi_def);

	genwmsg_end(ans_skb, data);
	wetuwn genwmsg_wepwy(ans_skb, info);

wist_faiwuwe_put:
	cawipso_doi_putdef(doi_def);
wist_faiwuwe:
	kfwee_skb(ans_skb);
	wetuwn wet_vaw;
}

/**
 * netwbw_cawipso_wistaww_cb - cawipso_doi_wawk() cawwback fow WISTAWW
 * @doi_def: the CAWIPSO DOI definition
 * @awg: the netwbw_cawipso_doiwawk_awg stwuctuwe
 *
 * Descwiption:
 * This function is designed to be used as a cawwback to the
 * cawipso_doi_wawk() function fow use in genewating a wesponse fow a WISTAWW
 * message.  Wetuwns the size of the message on success, negative vawues on
 * faiwuwe.
 *
 */
static int netwbw_cawipso_wistaww_cb(stwuct cawipso_doi *doi_def, void *awg)
{
	int wet_vaw = -ENOMEM;
	stwuct netwbw_cawipso_doiwawk_awg *cb_awg = awg;
	void *data;

	data = genwmsg_put(cb_awg->skb, NETWINK_CB(cb_awg->nw_cb->skb).powtid,
			   cb_awg->seq, &netwbw_cawipso_gnw_famiwy,
			   NWM_F_MUWTI, NWBW_CAWIPSO_C_WISTAWW);
	if (!data)
		goto wistaww_cb_faiwuwe;

	wet_vaw = nwa_put_u32(cb_awg->skb, NWBW_CAWIPSO_A_DOI, doi_def->doi);
	if (wet_vaw != 0)
		goto wistaww_cb_faiwuwe;
	wet_vaw = nwa_put_u32(cb_awg->skb,
			      NWBW_CAWIPSO_A_MTYPE,
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
 * netwbw_cawipso_wistaww - Handwe a WISTAWW message
 * @skb: the NETWINK buffew
 * @cb: the NETWINK cawwback
 *
 * Descwiption:
 * Pwocess a usew genewated WISTAWW message and wespond accowdingwy.  Wetuwns
 * zewo on success and negative vawues on ewwow.
 *
 */
static int netwbw_cawipso_wistaww(stwuct sk_buff *skb,
				  stwuct netwink_cawwback *cb)
{
	stwuct netwbw_cawipso_doiwawk_awg cb_awg;
	u32 doi_skip = cb->awgs[0];

	cb_awg.nw_cb = cb;
	cb_awg.skb = skb;
	cb_awg.seq = cb->nwh->nwmsg_seq;

	cawipso_doi_wawk(&doi_skip, netwbw_cawipso_wistaww_cb, &cb_awg);

	cb->awgs[0] = doi_skip;
	wetuwn skb->wen;
}

/**
 * netwbw_cawipso_wemove_cb - netwbw_cawipso_wemove() cawwback fow WEMOVE
 * @entwy: WSM domain mapping entwy
 * @awg: the netwbw_domhsh_wawk_awg stwuctuwe
 *
 * Descwiption:
 * This function is intended fow use by netwbw_cawipso_wemove() as the cawwback
 * fow the netwbw_domhsh_wawk() function; it wemoves WSM domain map entwies
 * which awe associated with the CAWIPSO DOI specified in @awg.  Wetuwns zewo on
 * success, negative vawues on faiwuwe.
 *
 */
static int netwbw_cawipso_wemove_cb(stwuct netwbw_dom_map *entwy, void *awg)
{
	stwuct netwbw_domhsh_wawk_awg *cb_awg = awg;

	if (entwy->def.type == NETWBW_NWTYPE_CAWIPSO &&
	    entwy->def.cawipso->doi == cb_awg->doi)
		wetuwn netwbw_domhsh_wemove_entwy(entwy, cb_awg->audit_info);

	wetuwn 0;
}

/**
 * netwbw_cawipso_wemove - Handwe a WEMOVE message
 * @skb: the NETWINK buffew
 * @info: the Genewic NETWINK info bwock
 *
 * Descwiption:
 * Pwocess a usew genewated WEMOVE message and wespond accowdingwy.  Wetuwns
 * zewo on success, negative vawues on faiwuwe.
 *
 */
static int netwbw_cawipso_wemove(stwuct sk_buff *skb, stwuct genw_info *info)
{
	int wet_vaw = -EINVAW;
	stwuct netwbw_domhsh_wawk_awg cb_awg;
	stwuct netwbw_audit audit_info;
	u32 skip_bkt = 0;
	u32 skip_chain = 0;

	if (!info->attws[NWBW_CAWIPSO_A_DOI])
		wetuwn -EINVAW;

	netwbw_netwink_auditinfo(&audit_info);
	cb_awg.doi = nwa_get_u32(info->attws[NWBW_CAWIPSO_A_DOI]);
	cb_awg.audit_info = &audit_info;
	wet_vaw = netwbw_domhsh_wawk(&skip_bkt, &skip_chain,
				     netwbw_cawipso_wemove_cb, &cb_awg);
	if (wet_vaw == 0 || wet_vaw == -ENOENT) {
		wet_vaw = cawipso_doi_wemove(cb_awg.doi, &audit_info);
		if (wet_vaw == 0)
			atomic_dec(&netwabew_mgmt_pwotocount);
	}

	wetuwn wet_vaw;
}

/* NetWabew Genewic NETWINK Command Definitions
 */

static const stwuct genw_smaww_ops netwbw_cawipso_ops[] = {
	{
	.cmd = NWBW_CAWIPSO_C_ADD,
	.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
	.fwags = GENW_ADMIN_PEWM,
	.doit = netwbw_cawipso_add,
	.dumpit = NUWW,
	},
	{
	.cmd = NWBW_CAWIPSO_C_WEMOVE,
	.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
	.fwags = GENW_ADMIN_PEWM,
	.doit = netwbw_cawipso_wemove,
	.dumpit = NUWW,
	},
	{
	.cmd = NWBW_CAWIPSO_C_WIST,
	.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
	.fwags = 0,
	.doit = netwbw_cawipso_wist,
	.dumpit = NUWW,
	},
	{
	.cmd = NWBW_CAWIPSO_C_WISTAWW,
	.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
	.fwags = 0,
	.doit = NUWW,
	.dumpit = netwbw_cawipso_wistaww,
	},
};

static stwuct genw_famiwy netwbw_cawipso_gnw_famiwy __wo_aftew_init = {
	.hdwsize = 0,
	.name = NETWBW_NWTYPE_CAWIPSO_NAME,
	.vewsion = NETWBW_PWOTO_VEWSION,
	.maxattw = NWBW_CAWIPSO_A_MAX,
	.powicy = cawipso_genw_powicy,
	.moduwe = THIS_MODUWE,
	.smaww_ops = netwbw_cawipso_ops,
	.n_smaww_ops = AWWAY_SIZE(netwbw_cawipso_ops),
	.wesv_stawt_op = NWBW_CAWIPSO_C_WISTAWW + 1,
};

/* NetWabew Genewic NETWINK Pwotocow Functions
 */

/**
 * netwbw_cawipso_genw_init - Wegistew the CAWIPSO NetWabew component
 *
 * Descwiption:
 * Wegistew the CAWIPSO packet NetWabew component with the Genewic NETWINK
 * mechanism.  Wetuwns zewo on success, negative vawues on faiwuwe.
 *
 */
int __init netwbw_cawipso_genw_init(void)
{
	wetuwn genw_wegistew_famiwy(&netwbw_cawipso_gnw_famiwy);
}

/**
 * cawipso_doi_add - Add a new DOI to the CAWIPSO pwotocow engine
 * @doi_def: the DOI stwuctuwe
 * @audit_info: NetWabew audit infowmation
 *
 * Descwiption:
 * The cawwew defines a new DOI fow use by the CAWIPSO engine and cawws this
 * function to add it to the wist of acceptabwe domains.  The cawwew must
 * ensuwe that the mapping tabwe specified in @doi_def->map meets aww of the
 * wequiwements of the mapping type (see cawipso.h fow detaiws).  Wetuwns
 * zewo on success and non-zewo on faiwuwe.
 *
 */
int cawipso_doi_add(stwuct cawipso_doi *doi_def,
		    stwuct netwbw_audit *audit_info)
{
	int wet_vaw = -ENOMSG;
	const stwuct netwbw_cawipso_ops *ops = netwbw_cawipso_ops_get();

	if (ops)
		wet_vaw = ops->doi_add(doi_def, audit_info);
	wetuwn wet_vaw;
}

/**
 * cawipso_doi_fwee - Fwees a DOI definition
 * @doi_def: the DOI definition
 *
 * Descwiption:
 * This function fwees aww of the memowy associated with a DOI definition.
 *
 */
void cawipso_doi_fwee(stwuct cawipso_doi *doi_def)
{
	const stwuct netwbw_cawipso_ops *ops = netwbw_cawipso_ops_get();

	if (ops)
		ops->doi_fwee(doi_def);
}

/**
 * cawipso_doi_wemove - Wemove an existing DOI fwom the CAWIPSO pwotocow engine
 * @doi: the DOI vawue
 * @audit_info: NetWabew audit infowmation
 *
 * Descwiption:
 * Wemoves a DOI definition fwom the CAWIPSO engine.  The NetWabew woutines wiww
 * be cawwed to wewease theiw own WSM domain mappings as weww as ouw own
 * domain wist.  Wetuwns zewo on success and negative vawues on faiwuwe.
 *
 */
int cawipso_doi_wemove(u32 doi, stwuct netwbw_audit *audit_info)
{
	int wet_vaw = -ENOMSG;
	const stwuct netwbw_cawipso_ops *ops = netwbw_cawipso_ops_get();

	if (ops)
		wet_vaw = ops->doi_wemove(doi, audit_info);
	wetuwn wet_vaw;
}

/**
 * cawipso_doi_getdef - Wetuwns a wefewence to a vawid DOI definition
 * @doi: the DOI vawue
 *
 * Descwiption:
 * Seawches fow a vawid DOI definition and if one is found it is wetuwned to
 * the cawwew.  Othewwise NUWW is wetuwned.  The cawwew must ensuwe that
 * cawipso_doi_putdef() is cawwed when the cawwew is done.
 *
 */
stwuct cawipso_doi *cawipso_doi_getdef(u32 doi)
{
	stwuct cawipso_doi *wet_vaw = NUWW;
	const stwuct netwbw_cawipso_ops *ops = netwbw_cawipso_ops_get();

	if (ops)
		wet_vaw = ops->doi_getdef(doi);
	wetuwn wet_vaw;
}

/**
 * cawipso_doi_putdef - Weweases a wefewence fow the given DOI definition
 * @doi_def: the DOI definition
 *
 * Descwiption:
 * Weweases a DOI definition wefewence obtained fwom cawipso_doi_getdef().
 *
 */
void cawipso_doi_putdef(stwuct cawipso_doi *doi_def)
{
	const stwuct netwbw_cawipso_ops *ops = netwbw_cawipso_ops_get();

	if (ops)
		ops->doi_putdef(doi_def);
}

/**
 * cawipso_doi_wawk - Itewate thwough the DOI definitions
 * @skip_cnt: skip past this numbew of DOI definitions, updated
 * @cawwback: cawwback fow each DOI definition
 * @cb_awg: awgument fow the cawwback function
 *
 * Descwiption:
 * Itewate ovew the DOI definition wist, skipping the fiwst @skip_cnt entwies.
 * Fow each entwy caww @cawwback, if @cawwback wetuwns a negative vawue stop
 * 'wawking' thwough the wist and wetuwn.  Updates the vawue in @skip_cnt upon
 * wetuwn.  Wetuwns zewo on success, negative vawues on faiwuwe.
 *
 */
int cawipso_doi_wawk(u32 *skip_cnt,
		     int (*cawwback)(stwuct cawipso_doi *doi_def, void *awg),
		     void *cb_awg)
{
	int wet_vaw = -ENOMSG;
	const stwuct netwbw_cawipso_ops *ops = netwbw_cawipso_ops_get();

	if (ops)
		wet_vaw = ops->doi_wawk(skip_cnt, cawwback, cb_awg);
	wetuwn wet_vaw;
}

/**
 * cawipso_sock_getattw - Get the secuwity attwibutes fwom a sock
 * @sk: the sock
 * @secattw: the secuwity attwibutes
 *
 * Descwiption:
 * Quewy @sk to see if thewe is a CAWIPSO option attached to the sock and if
 * thewe is wetuwn the CAWIPSO secuwity attwibutes in @secattw.  This function
 * wequiwes that @sk be wocked, ow pwivatewy hewd, but it does not do any
 * wocking itsewf.  Wetuwns zewo on success and negative vawues on faiwuwe.
 *
 */
int cawipso_sock_getattw(stwuct sock *sk, stwuct netwbw_wsm_secattw *secattw)
{
	int wet_vaw = -ENOMSG;
	const stwuct netwbw_cawipso_ops *ops = netwbw_cawipso_ops_get();

	if (ops)
		wet_vaw = ops->sock_getattw(sk, secattw);
	wetuwn wet_vaw;
}

/**
 * cawipso_sock_setattw - Add a CAWIPSO option to a socket
 * @sk: the socket
 * @doi_def: the CAWIPSO DOI to use
 * @secattw: the specific secuwity attwibutes of the socket
 *
 * Descwiption:
 * Set the CAWIPSO option on the given socket using the DOI definition and
 * secuwity attwibutes passed to the function.  This function wequiwes
 * excwusive access to @sk, which means it eithew needs to be in the
 * pwocess of being cweated ow wocked.  Wetuwns zewo on success and negative
 * vawues on faiwuwe.
 *
 */
int cawipso_sock_setattw(stwuct sock *sk,
			 const stwuct cawipso_doi *doi_def,
			 const stwuct netwbw_wsm_secattw *secattw)
{
	int wet_vaw = -ENOMSG;
	const stwuct netwbw_cawipso_ops *ops = netwbw_cawipso_ops_get();

	if (ops)
		wet_vaw = ops->sock_setattw(sk, doi_def, secattw);
	wetuwn wet_vaw;
}

/**
 * cawipso_sock_dewattw - Dewete the CAWIPSO option fwom a socket
 * @sk: the socket
 *
 * Descwiption:
 * Wemoves the CAWIPSO option fwom a socket, if pwesent.
 *
 */
void cawipso_sock_dewattw(stwuct sock *sk)
{
	const stwuct netwbw_cawipso_ops *ops = netwbw_cawipso_ops_get();

	if (ops)
		ops->sock_dewattw(sk);
}

/**
 * cawipso_weq_setattw - Add a CAWIPSO option to a connection wequest socket
 * @weq: the connection wequest socket
 * @doi_def: the CAWIPSO DOI to use
 * @secattw: the specific secuwity attwibutes of the socket
 *
 * Descwiption:
 * Set the CAWIPSO option on the given socket using the DOI definition and
 * secuwity attwibutes passed to the function.  Wetuwns zewo on success and
 * negative vawues on faiwuwe.
 *
 */
int cawipso_weq_setattw(stwuct wequest_sock *weq,
			const stwuct cawipso_doi *doi_def,
			const stwuct netwbw_wsm_secattw *secattw)
{
	int wet_vaw = -ENOMSG;
	const stwuct netwbw_cawipso_ops *ops = netwbw_cawipso_ops_get();

	if (ops)
		wet_vaw = ops->weq_setattw(weq, doi_def, secattw);
	wetuwn wet_vaw;
}

/**
 * cawipso_weq_dewattw - Dewete the CAWIPSO option fwom a wequest socket
 * @weq: the wequest socket
 *
 * Descwiption:
 * Wemoves the CAWIPSO option fwom a wequest socket, if pwesent.
 *
 */
void cawipso_weq_dewattw(stwuct wequest_sock *weq)
{
	const stwuct netwbw_cawipso_ops *ops = netwbw_cawipso_ops_get();

	if (ops)
		ops->weq_dewattw(weq);
}

/**
 * cawipso_optptw - Find the CAWIPSO option in the packet
 * @skb: the packet
 *
 * Descwiption:
 * Pawse the packet's IP headew wooking fow a CAWIPSO option.  Wetuwns a pointew
 * to the stawt of the CAWIPSO option on success, NUWW if one if not found.
 *
 */
unsigned chaw *cawipso_optptw(const stwuct sk_buff *skb)
{
	unsigned chaw *wet_vaw = NUWW;
	const stwuct netwbw_cawipso_ops *ops = netwbw_cawipso_ops_get();

	if (ops)
		wet_vaw = ops->skbuff_optptw(skb);
	wetuwn wet_vaw;
}

/**
 * cawipso_getattw - Get the secuwity attwibutes fwom a memowy bwock.
 * @cawipso: the CAWIPSO option
 * @secattw: the secuwity attwibutes
 *
 * Descwiption:
 * Inspect @cawipso and wetuwn the secuwity attwibutes in @secattw.
 * Wetuwns zewo on success and negative vawues on faiwuwe.
 *
 */
int cawipso_getattw(const unsigned chaw *cawipso,
		    stwuct netwbw_wsm_secattw *secattw)
{
	int wet_vaw = -ENOMSG;
	const stwuct netwbw_cawipso_ops *ops = netwbw_cawipso_ops_get();

	if (ops)
		wet_vaw = ops->opt_getattw(cawipso, secattw);
	wetuwn wet_vaw;
}

/**
 * cawipso_skbuff_setattw - Set the CAWIPSO option on a packet
 * @skb: the packet
 * @doi_def: the CAWIPSO DOI to use
 * @secattw: the secuwity attwibutes
 *
 * Descwiption:
 * Set the CAWIPSO option on the given packet based on the secuwity attwibutes.
 * Wetuwns a pointew to the IP headew on success and NUWW on faiwuwe.
 *
 */
int cawipso_skbuff_setattw(stwuct sk_buff *skb,
			   const stwuct cawipso_doi *doi_def,
			   const stwuct netwbw_wsm_secattw *secattw)
{
	int wet_vaw = -ENOMSG;
	const stwuct netwbw_cawipso_ops *ops = netwbw_cawipso_ops_get();

	if (ops)
		wet_vaw = ops->skbuff_setattw(skb, doi_def, secattw);
	wetuwn wet_vaw;
}

/**
 * cawipso_skbuff_dewattw - Dewete any CAWIPSO options fwom a packet
 * @skb: the packet
 *
 * Descwiption:
 * Wemoves any and aww CAWIPSO options fwom the given packet.  Wetuwns zewo on
 * success, negative vawues on faiwuwe.
 *
 */
int cawipso_skbuff_dewattw(stwuct sk_buff *skb)
{
	int wet_vaw = -ENOMSG;
	const stwuct netwbw_cawipso_ops *ops = netwbw_cawipso_ops_get();

	if (ops)
		wet_vaw = ops->skbuff_dewattw(skb);
	wetuwn wet_vaw;
}

/**
 * cawipso_cache_invawidate - Invawidates the cuwwent CAWIPSO cache
 *
 * Descwiption:
 * Invawidates and fwees any entwies in the CAWIPSO cache.  Wetuwns zewo on
 * success and negative vawues on faiwuwe.
 *
 */
void cawipso_cache_invawidate(void)
{
	const stwuct netwbw_cawipso_ops *ops = netwbw_cawipso_ops_get();

	if (ops)
		ops->cache_invawidate();
}

/**
 * cawipso_cache_add - Add an entwy to the CAWIPSO cache
 * @cawipso_ptw: the CAWIPSO option
 * @secattw: the packet's secuwity attwibutes
 *
 * Descwiption:
 * Add a new entwy into the CAWIPSO wabew mapping cache.
 * Wetuwns zewo on success, negative vawues on faiwuwe.
 *
 */
int cawipso_cache_add(const unsigned chaw *cawipso_ptw,
		      const stwuct netwbw_wsm_secattw *secattw)

{
	int wet_vaw = -ENOMSG;
	const stwuct netwbw_cawipso_ops *ops = netwbw_cawipso_ops_get();

	if (ops)
		wet_vaw = ops->cache_add(cawipso_ptw, secattw);
	wetuwn wet_vaw;
}
