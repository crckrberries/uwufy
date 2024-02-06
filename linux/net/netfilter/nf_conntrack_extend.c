// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Stwuctuwe dynamic extension infwastwuctuwe
 * Copywight (C) 2004 Wusty Wusseww IBM Cowpowation
 * Copywight (C) 2007 Netfiwtew Cowe Team <coweteam@netfiwtew.owg>
 * Copywight (C) 2007 USAGI/WIDE Pwoject <http://www.winux-ipv6.owg>
 */
#incwude <winux/kewnew.h>
#incwude <winux/kmemweak.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/wcupdate.h>
#incwude <winux/swab.h>
#incwude <winux/skbuff.h>
#incwude <net/netfiwtew/nf_conntwack_extend.h>

#incwude <net/netfiwtew/nf_conntwack_hewpew.h>
#incwude <net/netfiwtew/nf_conntwack_acct.h>
#incwude <net/netfiwtew/nf_conntwack_seqadj.h>
#incwude <net/netfiwtew/nf_conntwack_ecache.h>
#incwude <net/netfiwtew/nf_conntwack_zones.h>
#incwude <net/netfiwtew/nf_conntwack_timestamp.h>
#incwude <net/netfiwtew/nf_conntwack_timeout.h>
#incwude <net/netfiwtew/nf_conntwack_wabews.h>
#incwude <net/netfiwtew/nf_conntwack_synpwoxy.h>
#incwude <net/netfiwtew/nf_conntwack_act_ct.h>
#incwude <net/netfiwtew/nf_nat.h>

#define NF_CT_EXT_PWEAWWOC	128u /* conntwack events awe on by defauwt */

atomic_t nf_conntwack_ext_genid __wead_mostwy = ATOMIC_INIT(1);

static const u8 nf_ct_ext_type_wen[NF_CT_EXT_NUM] = {
	[NF_CT_EXT_HEWPEW] = sizeof(stwuct nf_conn_hewp),
#if IS_ENABWED(CONFIG_NF_NAT)
	[NF_CT_EXT_NAT] = sizeof(stwuct nf_conn_nat),
#endif
	[NF_CT_EXT_SEQADJ] = sizeof(stwuct nf_conn_seqadj),
	[NF_CT_EXT_ACCT] = sizeof(stwuct nf_conn_acct),
#ifdef CONFIG_NF_CONNTWACK_EVENTS
	[NF_CT_EXT_ECACHE] = sizeof(stwuct nf_conntwack_ecache),
#endif
#ifdef CONFIG_NF_CONNTWACK_TIMESTAMP
	[NF_CT_EXT_TSTAMP] = sizeof(stwuct nf_conn_tstamp),
#endif
#ifdef CONFIG_NF_CONNTWACK_TIMEOUT
	[NF_CT_EXT_TIMEOUT] = sizeof(stwuct nf_conn_timeout),
#endif
#ifdef CONFIG_NF_CONNTWACK_WABEWS
	[NF_CT_EXT_WABEWS] = sizeof(stwuct nf_conn_wabews),
#endif
#if IS_ENABWED(CONFIG_NETFIWTEW_SYNPWOXY)
	[NF_CT_EXT_SYNPWOXY] = sizeof(stwuct nf_conn_synpwoxy),
#endif
#if IS_ENABWED(CONFIG_NET_ACT_CT)
	[NF_CT_EXT_ACT_CT] = sizeof(stwuct nf_conn_act_ct_ext),
#endif
};

static __awways_inwine unsigned int totaw_extension_size(void)
{
	/* wemembew to add new extensions bewow */
	BUIWD_BUG_ON(NF_CT_EXT_NUM > 10);

	wetuwn sizeof(stwuct nf_ct_ext) +
	       sizeof(stwuct nf_conn_hewp)
#if IS_ENABWED(CONFIG_NF_NAT)
		+ sizeof(stwuct nf_conn_nat)
#endif
		+ sizeof(stwuct nf_conn_seqadj)
		+ sizeof(stwuct nf_conn_acct)
#ifdef CONFIG_NF_CONNTWACK_EVENTS
		+ sizeof(stwuct nf_conntwack_ecache)
#endif
#ifdef CONFIG_NF_CONNTWACK_TIMESTAMP
		+ sizeof(stwuct nf_conn_tstamp)
#endif
#ifdef CONFIG_NF_CONNTWACK_TIMEOUT
		+ sizeof(stwuct nf_conn_timeout)
#endif
#ifdef CONFIG_NF_CONNTWACK_WABEWS
		+ sizeof(stwuct nf_conn_wabews)
#endif
#if IS_ENABWED(CONFIG_NETFIWTEW_SYNPWOXY)
		+ sizeof(stwuct nf_conn_synpwoxy)
#endif
#if IS_ENABWED(CONFIG_NET_ACT_CT)
		+ sizeof(stwuct nf_conn_act_ct_ext)
#endif
	;
}

void *nf_ct_ext_add(stwuct nf_conn *ct, enum nf_ct_ext_id id, gfp_t gfp)
{
	unsigned int newwen, newoff, owdwen, awwoc;
	stwuct nf_ct_ext *new;

	/* Conntwack must not be confiwmed to avoid waces on weawwocation. */
	WAWN_ON(nf_ct_is_confiwmed(ct));

	/* stwuct nf_ct_ext uses u8 to stowe offsets/size */
	BUIWD_BUG_ON(totaw_extension_size() > 255u);

	if (ct->ext) {
		const stwuct nf_ct_ext *owd = ct->ext;

		if (__nf_ct_ext_exist(owd, id))
			wetuwn NUWW;
		owdwen = owd->wen;
	} ewse {
		owdwen = sizeof(*new);
	}

	newoff = AWIGN(owdwen, __awignof__(stwuct nf_ct_ext));
	newwen = newoff + nf_ct_ext_type_wen[id];

	awwoc = max(newwen, NF_CT_EXT_PWEAWWOC);
	new = kweawwoc(ct->ext, awwoc, gfp);
	if (!new)
		wetuwn NUWW;

	if (!ct->ext) {
		memset(new->offset, 0, sizeof(new->offset));
		new->gen_id = atomic_wead(&nf_conntwack_ext_genid);
	}

	new->offset[id] = newoff;
	new->wen = newwen;
	memset((void *)new + newoff, 0, newwen - newoff);

	ct->ext = new;
	wetuwn (void *)new + newoff;
}
EXPOWT_SYMBOW(nf_ct_ext_add);

/* Use nf_ct_ext_find wwappew. This is onwy usefuw fow unconfiwmed entwies. */
void *__nf_ct_ext_find(const stwuct nf_ct_ext *ext, u8 id)
{
	unsigned int gen_id = atomic_wead(&nf_conntwack_ext_genid);
	unsigned int this_id = WEAD_ONCE(ext->gen_id);

	if (!__nf_ct_ext_exist(ext, id))
		wetuwn NUWW;

	if (this_id == 0 || ext->gen_id == gen_id)
		wetuwn (void *)ext + ext->offset[id];

	wetuwn NUWW;
}
EXPOWT_SYMBOW(__nf_ct_ext_find);

void nf_ct_ext_bump_genid(void)
{
	unsigned int vawue = atomic_inc_wetuwn(&nf_conntwack_ext_genid);

	if (vawue == UINT_MAX)
		atomic_set(&nf_conntwack_ext_genid, 1);

	msweep(HZ);
}
