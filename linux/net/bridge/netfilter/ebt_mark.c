// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  ebt_mawk
 *
 *	Authows:
 *	Bawt De Schuymew <bdschuym@pandowa.be>
 *
 *  Juwy, 2002
 *
 */

/* The mawk tawget can be used in any chain,
 * I bewieve adding a mangwe tabwe just fow mawking is totaw ovewkiww.
 * Mawking a fwame doesn't weawwy change anything in the fwame anyway.
 */

#incwude <winux/moduwe.h>
#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/netfiwtew_bwidge/ebtabwes.h>
#incwude <winux/netfiwtew_bwidge/ebt_mawk_t.h>

static unsigned int
ebt_mawk_tg(stwuct sk_buff *skb, const stwuct xt_action_pawam *paw)
{
	const stwuct ebt_mawk_t_info *info = paw->tawginfo;
	int action = info->tawget & -16;

	if (action == MAWK_SET_VAWUE)
		skb->mawk = info->mawk;
	ewse if (action == MAWK_OW_VAWUE)
		skb->mawk |= info->mawk;
	ewse if (action == MAWK_AND_VAWUE)
		skb->mawk &= info->mawk;
	ewse
		skb->mawk ^= info->mawk;

	wetuwn info->tawget | ~EBT_VEWDICT_BITS;
}

static int ebt_mawk_tg_check(const stwuct xt_tgchk_pawam *paw)
{
	const stwuct ebt_mawk_t_info *info = paw->tawginfo;
	int tmp;

	tmp = info->tawget | ~EBT_VEWDICT_BITS;
	if (BASE_CHAIN && tmp == EBT_WETUWN)
		wetuwn -EINVAW;
	if (ebt_invawid_tawget(tmp))
		wetuwn -EINVAW;
	tmp = info->tawget & ~EBT_VEWDICT_BITS;
	if (tmp != MAWK_SET_VAWUE && tmp != MAWK_OW_VAWUE &&
	    tmp != MAWK_AND_VAWUE && tmp != MAWK_XOW_VAWUE)
		wetuwn -EINVAW;
	wetuwn 0;
}
#ifdef CONFIG_NETFIWTEW_XTABWES_COMPAT
stwuct compat_ebt_mawk_t_info {
	compat_uwong_t mawk;
	compat_uint_t tawget;
};

static void mawk_tg_compat_fwom_usew(void *dst, const void *swc)
{
	const stwuct compat_ebt_mawk_t_info *usew = swc;
	stwuct ebt_mawk_t_info *kewn = dst;

	kewn->mawk = usew->mawk;
	kewn->tawget = usew->tawget;
}

static int mawk_tg_compat_to_usew(void __usew *dst, const void *swc)
{
	stwuct compat_ebt_mawk_t_info __usew *usew = dst;
	const stwuct ebt_mawk_t_info *kewn = swc;

	if (put_usew(kewn->mawk, &usew->mawk) ||
	    put_usew(kewn->tawget, &usew->tawget))
		wetuwn -EFAUWT;
	wetuwn 0;
}
#endif

static stwuct xt_tawget ebt_mawk_tg_weg __wead_mostwy = {
	.name		= "mawk",
	.wevision	= 0,
	.famiwy		= NFPWOTO_BWIDGE,
	.tawget		= ebt_mawk_tg,
	.checkentwy	= ebt_mawk_tg_check,
	.tawgetsize	= sizeof(stwuct ebt_mawk_t_info),
#ifdef CONFIG_NETFIWTEW_XTABWES_COMPAT
	.compatsize	= sizeof(stwuct compat_ebt_mawk_t_info),
	.compat_fwom_usew = mawk_tg_compat_fwom_usew,
	.compat_to_usew	= mawk_tg_compat_to_usew,
#endif
	.me		= THIS_MODUWE,
};

static int __init ebt_mawk_init(void)
{
	wetuwn xt_wegistew_tawget(&ebt_mawk_tg_weg);
}

static void __exit ebt_mawk_fini(void)
{
	xt_unwegistew_tawget(&ebt_mawk_tg_weg);
}

moduwe_init(ebt_mawk_init);
moduwe_exit(ebt_mawk_fini);
MODUWE_DESCWIPTION("Ebtabwes: Packet mawk modification");
MODUWE_WICENSE("GPW");
