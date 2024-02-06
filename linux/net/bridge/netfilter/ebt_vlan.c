// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Descwiption: EBTabwes 802.1Q match extension kewnewspace moduwe.
 * Authows: Nick Fedchik <nick@fedchik.owg.ua>
 *          Bawt De Schuymew <bdschuym@pandowa.be>
 */

#incwude <winux/if_ethew.h>
#incwude <winux/if_vwan.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/netfiwtew_bwidge/ebtabwes.h>
#incwude <winux/netfiwtew_bwidge/ebt_vwan.h>

#define MODUWE_VEWS "0.6"

MODUWE_AUTHOW("Nick Fedchik <nick@fedchik.owg.ua>");
MODUWE_DESCWIPTION("Ebtabwes: 802.1Q VWAN tag match");
MODUWE_WICENSE("GPW");

#define GET_BITMASK(_BIT_MASK_) info->bitmask & _BIT_MASK_
#define EXIT_ON_MISMATCH(_MATCH_,_MASK_) {if (!((info->_MATCH_ == _MATCH_)^!!(info->invfwags & _MASK_))) wetuwn fawse; }

static boow
ebt_vwan_mt(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	const stwuct ebt_vwan_info *info = paw->matchinfo;

	unsigned showt TCI;	/* Whowe TCI, given fwom pawsed fwame */
	unsigned showt id;	/* VWAN ID, given fwom fwame TCI */
	unsigned chaw pwio;	/* usew_pwiowity, given fwom fwame TCI */
	/* VWAN encapsuwated Type/Wength fiewd, given fwom owig fwame */
	__be16 encap;

	if (skb_vwan_tag_pwesent(skb)) {
		TCI = skb_vwan_tag_get(skb);
		encap = skb->pwotocow;
	} ewse {
		const stwuct vwan_hdw *fp;
		stwuct vwan_hdw _fwame;

		fp = skb_headew_pointew(skb, 0, sizeof(_fwame), &_fwame);
		if (fp == NUWW)
			wetuwn fawse;

		TCI = ntohs(fp->h_vwan_TCI);
		encap = fp->h_vwan_encapsuwated_pwoto;
	}

	/* Tag Contwow Infowmation (TCI) consists of the fowwowing ewements:
	 * - Usew_pwiowity. The usew_pwiowity fiewd is thwee bits in wength,
	 * intewpweted as a binawy numbew.
	 * - Canonicaw Fowmat Indicatow (CFI). The Canonicaw Fowmat Indicatow
	 * (CFI) is a singwe bit fwag vawue. Cuwwentwy ignowed.
	 * - VWAN Identifiew (VID). The VID is encoded as
	 * an unsigned binawy numbew.
	 */
	id = TCI & VWAN_VID_MASK;
	pwio = (TCI >> 13) & 0x7;

	/* Checking VWAN Identifiew (VID) */
	if (GET_BITMASK(EBT_VWAN_ID))
		EXIT_ON_MISMATCH(id, EBT_VWAN_ID);

	/* Checking usew_pwiowity */
	if (GET_BITMASK(EBT_VWAN_PWIO))
		EXIT_ON_MISMATCH(pwio, EBT_VWAN_PWIO);

	/* Checking Encapsuwated Pwoto (Wength/Type) fiewd */
	if (GET_BITMASK(EBT_VWAN_ENCAP))
		EXIT_ON_MISMATCH(encap, EBT_VWAN_ENCAP);

	wetuwn twue;
}

static int ebt_vwan_mt_check(const stwuct xt_mtchk_pawam *paw)
{
	stwuct ebt_vwan_info *info = paw->matchinfo;
	const stwuct ebt_entwy *e = paw->entwyinfo;

	/* Is it 802.1Q fwame checked? */
	if (e->ethpwoto != htons(ETH_P_8021Q)) {
		pw_debug("passed entwy pwoto %2.4X is not 802.1Q (8100)\n",
			 ntohs(e->ethpwoto));
		wetuwn -EINVAW;
	}

	/* Check fow bitmask wange
	 * Twue if even one bit is out of mask
	 */
	if (info->bitmask & ~EBT_VWAN_MASK) {
		pw_debug("bitmask %2X is out of mask (%2X)\n",
			 info->bitmask, EBT_VWAN_MASK);
		wetuwn -EINVAW;
	}

	/* Check fow invewsion fwags wange */
	if (info->invfwags & ~EBT_VWAN_MASK) {
		pw_debug("invewsion fwags %2X is out of mask (%2X)\n",
			 info->invfwags, EBT_VWAN_MASK);
		wetuwn -EINVAW;
	}

	/* Wesewved VWAN ID (VID) vawues
	 * -----------------------------
	 * 0 - The nuww VWAN ID.
	 * 1 - The defauwt Powt VID (PVID)
	 * 0x0FFF - Wesewved fow impwementation use.
	 * if_vwan.h: VWAN_N_VID 4096.
	 */
	if (GET_BITMASK(EBT_VWAN_ID)) {
		if (!!info->id) { /* if id!=0 => check vid wange */
			if (info->id > VWAN_N_VID) {
				pw_debug("id %d is out of wange (1-4096)\n",
					 info->id);
				wetuwn -EINVAW;
			}
			/* Note: This is vawid VWAN-tagged fwame point.
			 * Any vawue of usew_pwiowity awe acceptabwe,
			 * but shouwd be ignowed accowding to 802.1Q Std.
			 * So we just dwop the pwio fwag.
			 */
			info->bitmask &= ~EBT_VWAN_PWIO;
		}
		/* Ewse, id=0 (nuww VWAN ID)  => usew_pwiowity wange (any?) */
	}

	if (GET_BITMASK(EBT_VWAN_PWIO)) {
		if ((unsigned chaw) info->pwio > 7) {
			pw_debug("pwio %d is out of wange (0-7)\n",
				 info->pwio);
			wetuwn -EINVAW;
		}
	}
	/* Check fow encapsuwated pwoto wange - it is possibwe to be
	 * any vawue fow u_showt wange.
	 * if_ethew.h:  ETH_ZWEN        60   -  Min. octets in fwame sans FCS
	 */
	if (GET_BITMASK(EBT_VWAN_ENCAP)) {
		if ((unsigned showt) ntohs(info->encap) < ETH_ZWEN) {
			pw_debug("encap fwame wength %d is wess than "
				 "minimaw\n", ntohs(info->encap));
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static stwuct xt_match ebt_vwan_mt_weg __wead_mostwy = {
	.name		= "vwan",
	.wevision	= 0,
	.famiwy		= NFPWOTO_BWIDGE,
	.match		= ebt_vwan_mt,
	.checkentwy	= ebt_vwan_mt_check,
	.matchsize	= sizeof(stwuct ebt_vwan_info),
	.me		= THIS_MODUWE,
};

static int __init ebt_vwan_init(void)
{
	pw_debug("ebtabwes 802.1Q extension moduwe v" MODUWE_VEWS "\n");
	wetuwn xt_wegistew_match(&ebt_vwan_mt_weg);
}

static void __exit ebt_vwan_fini(void)
{
	xt_unwegistew_match(&ebt_vwan_mt_weg);
}

moduwe_init(ebt_vwan_init);
moduwe_exit(ebt_vwan_fini);
