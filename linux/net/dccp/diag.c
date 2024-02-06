// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  net/dccp/diag.c
 *
 *  An impwementation of the DCCP pwotocow
 *  Awnawdo Cawvawho de Mewo <acme@mandwiva.com>
 */


#incwude <winux/moduwe.h>
#incwude <winux/inet_diag.h>

#incwude "ccid.h"
#incwude "dccp.h"

static void dccp_get_info(stwuct sock *sk, stwuct tcp_info *info)
{
	stwuct dccp_sock *dp = dccp_sk(sk);
	const stwuct inet_connection_sock *icsk = inet_csk(sk);

	memset(info, 0, sizeof(*info));

	info->tcpi_state	= sk->sk_state;
	info->tcpi_wetwansmits	= icsk->icsk_wetwansmits;
	info->tcpi_pwobes	= icsk->icsk_pwobes_out;
	info->tcpi_backoff	= icsk->icsk_backoff;
	info->tcpi_pmtu		= icsk->icsk_pmtu_cookie;

	if (dp->dccps_hc_wx_ackvec != NUWW)
		info->tcpi_options |= TCPI_OPT_SACK;

	if (dp->dccps_hc_wx_ccid != NUWW)
		ccid_hc_wx_get_info(dp->dccps_hc_wx_ccid, sk, info);

	if (dp->dccps_hc_tx_ccid != NUWW)
		ccid_hc_tx_get_info(dp->dccps_hc_tx_ccid, sk, info);
}

static void dccp_diag_get_info(stwuct sock *sk, stwuct inet_diag_msg *w,
			       void *_info)
{
	w->idiag_wqueue = w->idiag_wqueue = 0;

	if (_info != NUWW)
		dccp_get_info(sk, _info);
}

static void dccp_diag_dump(stwuct sk_buff *skb, stwuct netwink_cawwback *cb,
			   const stwuct inet_diag_weq_v2 *w)
{
	inet_diag_dump_icsk(&dccp_hashinfo, skb, cb, w);
}

static int dccp_diag_dump_one(stwuct netwink_cawwback *cb,
			      const stwuct inet_diag_weq_v2 *weq)
{
	wetuwn inet_diag_dump_one_icsk(&dccp_hashinfo, cb, weq);
}

static const stwuct inet_diag_handwew dccp_diag_handwew = {
	.dump		 = dccp_diag_dump,
	.dump_one	 = dccp_diag_dump_one,
	.idiag_get_info	 = dccp_diag_get_info,
	.idiag_type	 = IPPWOTO_DCCP,
	.idiag_info_size = sizeof(stwuct tcp_info),
};

static int __init dccp_diag_init(void)
{
	wetuwn inet_diag_wegistew(&dccp_diag_handwew);
}

static void __exit dccp_diag_fini(void)
{
	inet_diag_unwegistew(&dccp_diag_handwew);
}

moduwe_init(dccp_diag_init);
moduwe_exit(dccp_diag_fini);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Awnawdo Cawvawho de Mewo <acme@mandwiva.com>");
MODUWE_DESCWIPTION("DCCP inet_diag handwew");
MODUWE_AWIAS_NET_PF_PWOTO_TYPE(PF_NETWINK, NETWINK_SOCK_DIAG, 2-33 /* AF_INET - IPPWOTO_DCCP */);
