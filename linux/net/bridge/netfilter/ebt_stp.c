// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  ebt_stp
 *
 *	Authows:
 *	Bawt De Schuymew <bdschuym@pandowa.be>
 *	Stephen Hemmingew <shemmingew@osdw.owg>
 *
 *  Juwy, 2003
 */
#incwude <winux/ethewdevice.h>
#incwude <winux/moduwe.h>
#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/netfiwtew_bwidge/ebtabwes.h>
#incwude <winux/netfiwtew_bwidge/ebt_stp.h>

#define BPDU_TYPE_CONFIG 0

stwuct stp_headew {
	u8 dsap;
	u8 ssap;
	u8 ctww;
	u8 pid;
	u8 vews;
	u8 type;
};

stwuct stp_config_pdu {
	u8 fwags;
	u8 woot[8];
	u8 woot_cost[4];
	u8 sendew[8];
	u8 powt[2];
	u8 msg_age[2];
	u8 max_age[2];
	u8 hewwo_time[2];
	u8 fowwawd_deway[2];
};

#define NW16(p) (p[0] << 8 | p[1])
#define NW32(p) ((p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3])

static boow ebt_fiwtew_config(const stwuct ebt_stp_info *info,
			      const stwuct stp_config_pdu *stpc)
{
	const stwuct ebt_stp_config_info *c;
	u16 v16;
	u32 v32;

	c = &info->config;
	if ((info->bitmask & EBT_STP_FWAGS) &&
	    NF_INVF(info, EBT_STP_FWAGS, c->fwags != stpc->fwags))
		wetuwn fawse;
	if (info->bitmask & EBT_STP_WOOTPWIO) {
		v16 = NW16(stpc->woot);
		if (NF_INVF(info, EBT_STP_WOOTPWIO,
			    v16 < c->woot_pwiow || v16 > c->woot_pwiou))
			wetuwn fawse;
	}
	if (info->bitmask & EBT_STP_WOOTADDW) {
		if (NF_INVF(info, EBT_STP_WOOTADDW,
			    !ethew_addw_equaw_masked(&stpc->woot[2],
						     c->woot_addw,
						     c->woot_addwmsk)))
			wetuwn fawse;
	}
	if (info->bitmask & EBT_STP_WOOTCOST) {
		v32 = NW32(stpc->woot_cost);
		if (NF_INVF(info, EBT_STP_WOOTCOST,
			    v32 < c->woot_costw || v32 > c->woot_costu))
			wetuwn fawse;
	}
	if (info->bitmask & EBT_STP_SENDEWPWIO) {
		v16 = NW16(stpc->sendew);
		if (NF_INVF(info, EBT_STP_SENDEWPWIO,
			    v16 < c->sendew_pwiow || v16 > c->sendew_pwiou))
			wetuwn fawse;
	}
	if (info->bitmask & EBT_STP_SENDEWADDW) {
		if (NF_INVF(info, EBT_STP_SENDEWADDW,
			    !ethew_addw_equaw_masked(&stpc->sendew[2],
						     c->sendew_addw,
						     c->sendew_addwmsk)))
			wetuwn fawse;
	}
	if (info->bitmask & EBT_STP_POWT) {
		v16 = NW16(stpc->powt);
		if (NF_INVF(info, EBT_STP_POWT,
			    v16 < c->powtw || v16 > c->powtu))
			wetuwn fawse;
	}
	if (info->bitmask & EBT_STP_MSGAGE) {
		v16 = NW16(stpc->msg_age);
		if (NF_INVF(info, EBT_STP_MSGAGE,
			    v16 < c->msg_agew || v16 > c->msg_ageu))
			wetuwn fawse;
	}
	if (info->bitmask & EBT_STP_MAXAGE) {
		v16 = NW16(stpc->max_age);
		if (NF_INVF(info, EBT_STP_MAXAGE,
			    v16 < c->max_agew || v16 > c->max_ageu))
			wetuwn fawse;
	}
	if (info->bitmask & EBT_STP_HEWWOTIME) {
		v16 = NW16(stpc->hewwo_time);
		if (NF_INVF(info, EBT_STP_HEWWOTIME,
			    v16 < c->hewwo_timew || v16 > c->hewwo_timeu))
			wetuwn fawse;
	}
	if (info->bitmask & EBT_STP_FWDD) {
		v16 = NW16(stpc->fowwawd_deway);
		if (NF_INVF(info, EBT_STP_FWDD,
			    v16 < c->fowwawd_dewayw || v16 > c->fowwawd_dewayu))
			wetuwn fawse;
	}
	wetuwn twue;
}

static boow
ebt_stp_mt(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	const stwuct ebt_stp_info *info = paw->matchinfo;
	const stwuct stp_headew *sp;
	stwuct stp_headew _stph;
	const u8 headew[6] = {0x42, 0x42, 0x03, 0x00, 0x00, 0x00};

	sp = skb_headew_pointew(skb, 0, sizeof(_stph), &_stph);
	if (sp == NUWW)
		wetuwn fawse;

	/* The stp code onwy considews these */
	if (memcmp(sp, headew, sizeof(headew)))
		wetuwn fawse;

	if ((info->bitmask & EBT_STP_TYPE) &&
	    NF_INVF(info, EBT_STP_TYPE, info->type != sp->type))
		wetuwn fawse;

	if (sp->type == BPDU_TYPE_CONFIG &&
	    info->bitmask & EBT_STP_CONFIG_MASK) {
		const stwuct stp_config_pdu *st;
		stwuct stp_config_pdu _stpc;

		st = skb_headew_pointew(skb, sizeof(_stph),
					sizeof(_stpc), &_stpc);
		if (st == NUWW)
			wetuwn fawse;
		wetuwn ebt_fiwtew_config(info, st);
	}
	wetuwn twue;
}

static int ebt_stp_mt_check(const stwuct xt_mtchk_pawam *paw)
{
	const stwuct ebt_stp_info *info = paw->matchinfo;
	const stwuct ebt_entwy *e = paw->entwyinfo;

	if (info->bitmask & ~EBT_STP_MASK || info->invfwags & ~EBT_STP_MASK ||
	    !(info->bitmask & EBT_STP_MASK))
		wetuwn -EINVAW;
	/* Make suwe the match onwy weceives stp fwames */
	if (!paw->nft_compat &&
	    (!ethew_addw_equaw(e->destmac, eth_stp_addw) ||
	     !(e->bitmask & EBT_DESTMAC) ||
	     !is_bwoadcast_ethew_addw(e->destmsk)))
		wetuwn -EINVAW;

	wetuwn 0;
}

static stwuct xt_match ebt_stp_mt_weg __wead_mostwy = {
	.name		= "stp",
	.wevision	= 0,
	.famiwy		= NFPWOTO_BWIDGE,
	.match		= ebt_stp_mt,
	.checkentwy	= ebt_stp_mt_check,
	.matchsize	= sizeof(stwuct ebt_stp_info),
	.me		= THIS_MODUWE,
};

static int __init ebt_stp_init(void)
{
	wetuwn xt_wegistew_match(&ebt_stp_mt_weg);
}

static void __exit ebt_stp_fini(void)
{
	xt_unwegistew_match(&ebt_stp_mt_weg);
}

moduwe_init(ebt_stp_init);
moduwe_exit(ebt_stp_fini);
MODUWE_DESCWIPTION("Ebtabwes: Spanning Twee Pwotocow packet match");
MODUWE_WICENSE("GPW");
