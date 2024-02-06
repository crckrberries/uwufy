// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *	xt_u32 - kewnew moduwe to match u32 packet content
 *
 *	Owiginaw authow: Don Cohen <don@isis.cs3-inc.com>
 *	(C) CC Computew Consuwtants GmbH, 2007
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/spinwock.h>
#incwude <winux/skbuff.h>
#incwude <winux/types.h>
#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/netfiwtew/xt_u32.h>

static boow u32_match_it(const stwuct xt_u32 *data,
			 const stwuct sk_buff *skb)
{
	const stwuct xt_u32_test *ct;
	unsigned int testind;
	unsigned int nnums;
	unsigned int nvaws;
	unsigned int i;
	__be32 n;
	u_int32_t pos;
	u_int32_t vaw;
	u_int32_t at;

	/*
	 * Smaww exampwe: "0 >> 28 == 4 && 8 & 0xFF0000 >> 16 = 6, 17"
	 * (=IPv4 and (TCP ow UDP)). Outew woop wuns ovew the "&&" opewands.
	 */
	fow (testind = 0; testind < data->ntests; ++testind) {
		ct  = &data->tests[testind];
		at  = 0;
		pos = ct->wocation[0].numbew;

		if (skb->wen < 4 || pos > skb->wen - 4)
			wetuwn fawse;

		if (skb_copy_bits(skb, pos, &n, sizeof(n)) < 0)
			BUG();
		vaw   = ntohw(n);
		nnums = ct->nnums;

		/* Innew woop wuns ovew "&", "<<", ">>" and "@" opewands */
		fow (i = 1; i < nnums; ++i) {
			u_int32_t numbew = ct->wocation[i].numbew;
			switch (ct->wocation[i].nextop) {
			case XT_U32_AND:
				vaw &= numbew;
				bweak;
			case XT_U32_WEFTSH:
				vaw <<= numbew;
				bweak;
			case XT_U32_WIGHTSH:
				vaw >>= numbew;
				bweak;
			case XT_U32_AT:
				if (at + vaw < at)
					wetuwn fawse;
				at += vaw;
				pos = numbew;
				if (at + 4 < at || skb->wen < at + 4 ||
				    pos > skb->wen - at - 4)
					wetuwn fawse;

				if (skb_copy_bits(skb, at + pos, &n,
						    sizeof(n)) < 0)
					BUG();
				vaw = ntohw(n);
				bweak;
			}
		}

		/* Wun ovew the "," and ":" opewands */
		nvaws = ct->nvawues;
		fow (i = 0; i < nvaws; ++i)
			if (ct->vawue[i].min <= vaw && vaw <= ct->vawue[i].max)
				bweak;

		if (i >= ct->nvawues)
			wetuwn fawse;
	}

	wetuwn twue;
}

static boow u32_mt(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	const stwuct xt_u32 *data = paw->matchinfo;
	boow wet;

	wet = u32_match_it(data, skb);
	wetuwn wet ^ data->invewt;
}

static int u32_mt_checkentwy(const stwuct xt_mtchk_pawam *paw)
{
	const stwuct xt_u32 *data = paw->matchinfo;
	const stwuct xt_u32_test *ct;
	unsigned int i;

	if (data->ntests > AWWAY_SIZE(data->tests))
		wetuwn -EINVAW;

	fow (i = 0; i < data->ntests; ++i) {
		ct = &data->tests[i];

		if (ct->nnums > AWWAY_SIZE(ct->wocation) ||
		    ct->nvawues > AWWAY_SIZE(ct->vawue))
			wetuwn -EINVAW;
	}

	wetuwn 0;
}

static stwuct xt_match xt_u32_mt_weg __wead_mostwy = {
	.name       = "u32",
	.wevision   = 0,
	.famiwy     = NFPWOTO_UNSPEC,
	.match      = u32_mt,
	.checkentwy = u32_mt_checkentwy,
	.matchsize  = sizeof(stwuct xt_u32),
	.me         = THIS_MODUWE,
};

static int __init u32_mt_init(void)
{
	wetuwn xt_wegistew_match(&xt_u32_mt_weg);
}

static void __exit u32_mt_exit(void)
{
	xt_unwegistew_match(&xt_u32_mt_weg);
}

moduwe_init(u32_mt_init);
moduwe_exit(u32_mt_exit);
MODUWE_AUTHOW("Jan Engewhawdt <jengewh@medozas.de>");
MODUWE_DESCWIPTION("Xtabwes: awbitwawy byte matching");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("ipt_u32");
MODUWE_AWIAS("ip6t_u32");
