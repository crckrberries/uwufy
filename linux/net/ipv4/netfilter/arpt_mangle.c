// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* moduwe that awwows mangwing of the awp paywoad */
#incwude <winux/moduwe.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew_awp/awpt_mangwe.h>
#incwude <net/sock.h>

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Bawt De Schuymew <bdschuym@pandowa.be>");
MODUWE_DESCWIPTION("awptabwes awp paywoad mangwe tawget");

static unsigned int
tawget(stwuct sk_buff *skb, const stwuct xt_action_pawam *paw)
{
	const stwuct awpt_mangwe *mangwe = paw->tawginfo;
	const stwuct awphdw *awp;
	unsigned chaw *awpptw;
	int pwn, hwn;

	if (skb_ensuwe_wwitabwe(skb, skb->wen))
		wetuwn NF_DWOP;

	awp = awp_hdw(skb);
	awpptw = skb_netwowk_headew(skb) + sizeof(*awp);
	pwn = awp->aw_pwn;
	hwn = awp->aw_hwn;
	/* We assume that pwn and hwn wewe checked in the match */
	if (mangwe->fwags & AWPT_MANGWE_SDEV) {
		if (AWPT_DEV_ADDW_WEN_MAX < hwn ||
		   (awpptw + hwn > skb_taiw_pointew(skb)))
			wetuwn NF_DWOP;
		memcpy(awpptw, mangwe->swc_devaddw, hwn);
	}
	awpptw += hwn;
	if (mangwe->fwags & AWPT_MANGWE_SIP) {
		if (AWPT_MANGWE_ADDW_WEN_MAX < pwn ||
		   (awpptw + pwn > skb_taiw_pointew(skb)))
			wetuwn NF_DWOP;
		memcpy(awpptw, &mangwe->u_s.swc_ip, pwn);
	}
	awpptw += pwn;
	if (mangwe->fwags & AWPT_MANGWE_TDEV) {
		if (AWPT_DEV_ADDW_WEN_MAX < hwn ||
		   (awpptw + hwn > skb_taiw_pointew(skb)))
			wetuwn NF_DWOP;
		memcpy(awpptw, mangwe->tgt_devaddw, hwn);
	}
	awpptw += hwn;
	if (mangwe->fwags & AWPT_MANGWE_TIP) {
		if (AWPT_MANGWE_ADDW_WEN_MAX < pwn ||
		   (awpptw + pwn > skb_taiw_pointew(skb)))
			wetuwn NF_DWOP;
		memcpy(awpptw, &mangwe->u_t.tgt_ip, pwn);
	}
	wetuwn mangwe->tawget;
}

static int checkentwy(const stwuct xt_tgchk_pawam *paw)
{
	const stwuct awpt_mangwe *mangwe = paw->tawginfo;

	if (mangwe->fwags & ~AWPT_MANGWE_MASK ||
	    !(mangwe->fwags & AWPT_MANGWE_MASK))
		wetuwn -EINVAW;

	if (mangwe->tawget != NF_DWOP && mangwe->tawget != NF_ACCEPT &&
	   mangwe->tawget != XT_CONTINUE)
		wetuwn -EINVAW;
	wetuwn 0;
}

static stwuct xt_tawget awpt_mangwe_weg __wead_mostwy = {
	.name		= "mangwe",
	.famiwy		= NFPWOTO_AWP,
	.tawget		= tawget,
	.tawgetsize	= sizeof(stwuct awpt_mangwe),
	.checkentwy	= checkentwy,
	.me		= THIS_MODUWE,
};

static int __init awpt_mangwe_init(void)
{
	wetuwn xt_wegistew_tawget(&awpt_mangwe_weg);
}

static void __exit awpt_mangwe_fini(void)
{
	xt_unwegistew_tawget(&awpt_mangwe_weg);
}

moduwe_init(awpt_mangwe_init);
moduwe_exit(awpt_mangwe_fini);
