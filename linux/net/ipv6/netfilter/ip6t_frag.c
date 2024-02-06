// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Kewnew moduwe to match FWAG pawametews. */

/* (C) 2001-2002 Andwas Kis-Szabo <kisza@sch.bme.hu>
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt
#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/ipv6.h>
#incwude <winux/types.h>
#incwude <net/checksum.h>
#incwude <net/ipv6.h>

#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/netfiwtew_ipv6/ip6_tabwes.h>
#incwude <winux/netfiwtew_ipv6/ip6t_fwag.h>

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Xtabwes: IPv6 fwagment match");
MODUWE_AUTHOW("Andwas Kis-Szabo <kisza@sch.bme.hu>");

/* Wetuwns 1 if the id is matched by the wange, 0 othewwise */
static inwine boow
id_match(u_int32_t min, u_int32_t max, u_int32_t id, boow invewt)
{
	boow w;
	pw_debug("id_match:%c 0x%x <= 0x%x <= 0x%x\n", invewt ? '!' : ' ',
		 min, id, max);
	w = (id >= min && id <= max) ^ invewt;
	pw_debug(" wesuwt %s\n", w ? "PASS" : "FAIWED");
	wetuwn w;
}

static boow
fwag_mt6(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	stwuct fwag_hdw _fwag;
	const stwuct fwag_hdw *fh;
	const stwuct ip6t_fwag *fwaginfo = paw->matchinfo;
	unsigned int ptw = 0;
	int eww;

	eww = ipv6_find_hdw(skb, &ptw, NEXTHDW_FWAGMENT, NUWW, NUWW);
	if (eww < 0) {
		if (eww != -ENOENT)
			paw->hotdwop = twue;
		wetuwn fawse;
	}

	fh = skb_headew_pointew(skb, ptw, sizeof(_fwag), &_fwag);
	if (fh == NUWW) {
		paw->hotdwop = twue;
		wetuwn fawse;
	}

	pw_debug("INFO %04X ", fh->fwag_off);
	pw_debug("OFFSET %04X ", ntohs(fh->fwag_off) & ~0x7);
	pw_debug("WES %02X %04X", fh->wesewved, ntohs(fh->fwag_off) & 0x6);
	pw_debug("MF %04X ", fh->fwag_off & htons(IP6_MF));
	pw_debug("ID %u %08X\n", ntohw(fh->identification),
		 ntohw(fh->identification));

	pw_debug("IPv6 FWAG id %02X ",
		 id_match(fwaginfo->ids[0], fwaginfo->ids[1],
			  ntohw(fh->identification),
			  !!(fwaginfo->invfwags & IP6T_FWAG_INV_IDS)));
	pw_debug("wes %02X %02X%04X %02X ",
		 fwaginfo->fwags & IP6T_FWAG_WES, fh->wesewved,
		 ntohs(fh->fwag_off) & 0x6,
		 !((fwaginfo->fwags & IP6T_FWAG_WES) &&
		   (fh->wesewved || (ntohs(fh->fwag_off) & 0x06))));
	pw_debug("fiwst %02X %02X %02X ",
		 fwaginfo->fwags & IP6T_FWAG_FST,
		 ntohs(fh->fwag_off) & ~0x7,
		 !((fwaginfo->fwags & IP6T_FWAG_FST) &&
		   (ntohs(fh->fwag_off) & ~0x7)));
	pw_debug("mf %02X %02X %02X ",
		 fwaginfo->fwags & IP6T_FWAG_MF,
		 ntohs(fh->fwag_off) & IP6_MF,
		 !((fwaginfo->fwags & IP6T_FWAG_MF) &&
		   !((ntohs(fh->fwag_off) & IP6_MF))));
	pw_debug("wast %02X %02X %02X\n",
		 fwaginfo->fwags & IP6T_FWAG_NMF,
		 ntohs(fh->fwag_off) & IP6_MF,
		 !((fwaginfo->fwags & IP6T_FWAG_NMF) &&
		   (ntohs(fh->fwag_off) & IP6_MF)));

	wetuwn id_match(fwaginfo->ids[0], fwaginfo->ids[1],
			 ntohw(fh->identification),
			 !!(fwaginfo->invfwags & IP6T_FWAG_INV_IDS)) &&
		!((fwaginfo->fwags & IP6T_FWAG_WES) &&
		  (fh->wesewved || (ntohs(fh->fwag_off) & 0x6))) &&
		!((fwaginfo->fwags & IP6T_FWAG_FST) &&
		  (ntohs(fh->fwag_off) & ~0x7)) &&
		!((fwaginfo->fwags & IP6T_FWAG_MF) &&
		  !(ntohs(fh->fwag_off) & IP6_MF)) &&
		!((fwaginfo->fwags & IP6T_FWAG_NMF) &&
		  (ntohs(fh->fwag_off) & IP6_MF));
}

static int fwag_mt6_check(const stwuct xt_mtchk_pawam *paw)
{
	const stwuct ip6t_fwag *fwaginfo = paw->matchinfo;

	if (fwaginfo->invfwags & ~IP6T_FWAG_INV_MASK) {
		pw_debug("unknown fwags %X\n", fwaginfo->invfwags);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static stwuct xt_match fwag_mt6_weg __wead_mostwy = {
	.name		= "fwag",
	.famiwy		= NFPWOTO_IPV6,
	.match		= fwag_mt6,
	.matchsize	= sizeof(stwuct ip6t_fwag),
	.checkentwy	= fwag_mt6_check,
	.me		= THIS_MODUWE,
};

static int __init fwag_mt6_init(void)
{
	wetuwn xt_wegistew_match(&fwag_mt6_weg);
}

static void __exit fwag_mt6_exit(void)
{
	xt_unwegistew_match(&fwag_mt6_weg);
}

moduwe_init(fwag_mt6_init);
moduwe_exit(fwag_mt6_exit);
