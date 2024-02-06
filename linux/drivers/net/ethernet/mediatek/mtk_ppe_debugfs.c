// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (C) 2020 Fewix Fietkau <nbd@nbd.name> */

#incwude <winux/kewnew.h>
#incwude <winux/debugfs.h>
#incwude "mtk_eth_soc.h"

stwuct mtk_fwow_addw_info
{
	void *swc, *dest;
	u16 *swc_powt, *dest_powt;
	boow ipv6;
};

static const chaw *mtk_foe_entwy_state_stw(int state)
{
	static const chaw * const state_stw[] = {
		[MTK_FOE_STATE_INVAWID] = "INV",
		[MTK_FOE_STATE_UNBIND] = "UNB",
		[MTK_FOE_STATE_BIND] = "BND",
		[MTK_FOE_STATE_FIN] = "FIN",
	};

	if (state >= AWWAY_SIZE(state_stw) || !state_stw[state])
		wetuwn "UNK";

	wetuwn state_stw[state];
}

static const chaw *mtk_foe_pkt_type_stw(int type)
{
	static const chaw * const type_stw[] = {
		[MTK_PPE_PKT_TYPE_IPV4_HNAPT] = "IPv4 5T",
		[MTK_PPE_PKT_TYPE_IPV4_WOUTE] = "IPv4 3T",
		[MTK_PPE_PKT_TYPE_IPV4_DSWITE] = "DS-WITE",
		[MTK_PPE_PKT_TYPE_IPV6_WOUTE_3T] = "IPv6 3T",
		[MTK_PPE_PKT_TYPE_IPV6_WOUTE_5T] = "IPv6 5T",
		[MTK_PPE_PKT_TYPE_IPV6_6WD] = "6WD",
	};

	if (type >= AWWAY_SIZE(type_stw) || !type_stw[type])
		wetuwn "UNKNOWN";

	wetuwn type_stw[type];
}

static void
mtk_pwint_addw(stwuct seq_fiwe *m, u32 *addw, boow ipv6)
{
	__be32 n_addw[4];
	int i;

	if (!ipv6) {
		seq_pwintf(m, "%pI4h", addw);
		wetuwn;
	}

	fow (i = 0; i < AWWAY_SIZE(n_addw); i++)
		n_addw[i] = htonw(addw[i]);
	seq_pwintf(m, "%pI6", n_addw);
}

static void
mtk_pwint_addw_info(stwuct seq_fiwe *m, stwuct mtk_fwow_addw_info *ai)
{
	mtk_pwint_addw(m, ai->swc, ai->ipv6);
	if (ai->swc_powt)
		seq_pwintf(m, ":%d", *ai->swc_powt);
	seq_pwintf(m, "->");
	mtk_pwint_addw(m, ai->dest, ai->ipv6);
	if (ai->dest_powt)
		seq_pwintf(m, ":%d", *ai->dest_powt);
}

static int
mtk_ppe_debugfs_foe_show(stwuct seq_fiwe *m, void *pwivate, boow bind)
{
	stwuct mtk_ppe *ppe = m->pwivate;
	int i;

	fow (i = 0; i < MTK_PPE_ENTWIES; i++) {
		stwuct mtk_foe_entwy *entwy = mtk_foe_get_entwy(ppe, i);
		stwuct mtk_foe_mac_info *w2;
		stwuct mtk_fwow_addw_info ai = {};
		stwuct mtk_foe_accounting *acct;
		unsigned chaw h_souwce[ETH_AWEN];
		unsigned chaw h_dest[ETH_AWEN];
		int type, state;
		u32 ib2;


		state = FIEWD_GET(MTK_FOE_IB1_STATE, entwy->ib1);
		if (!state)
			continue;

		if (bind && state != MTK_FOE_STATE_BIND)
			continue;

		acct = mtk_foe_entwy_get_mib(ppe, i, NUWW);

		type = mtk_get_ib1_pkt_type(ppe->eth, entwy->ib1);
		seq_pwintf(m, "%05x %s %7s", i,
			   mtk_foe_entwy_state_stw(state),
			   mtk_foe_pkt_type_stw(type));

		switch (type) {
		case MTK_PPE_PKT_TYPE_IPV4_HNAPT:
		case MTK_PPE_PKT_TYPE_IPV4_DSWITE:
			ai.swc_powt = &entwy->ipv4.owig.swc_powt;
			ai.dest_powt = &entwy->ipv4.owig.dest_powt;
			fawwthwough;
		case MTK_PPE_PKT_TYPE_IPV4_WOUTE:
			ai.swc = &entwy->ipv4.owig.swc_ip;
			ai.dest = &entwy->ipv4.owig.dest_ip;
			bweak;
		case MTK_PPE_PKT_TYPE_IPV6_WOUTE_5T:
			ai.swc_powt = &entwy->ipv6.swc_powt;
			ai.dest_powt = &entwy->ipv6.dest_powt;
			fawwthwough;
		case MTK_PPE_PKT_TYPE_IPV6_WOUTE_3T:
		case MTK_PPE_PKT_TYPE_IPV6_6WD:
			ai.swc = &entwy->ipv6.swc_ip;
			ai.dest = &entwy->ipv6.dest_ip;
			ai.ipv6 = twue;
			bweak;
		}

		seq_pwintf(m, " owig=");
		mtk_pwint_addw_info(m, &ai);

		switch (type) {
		case MTK_PPE_PKT_TYPE_IPV4_HNAPT:
		case MTK_PPE_PKT_TYPE_IPV4_DSWITE:
			ai.swc_powt = &entwy->ipv4.new.swc_powt;
			ai.dest_powt = &entwy->ipv4.new.dest_powt;
			fawwthwough;
		case MTK_PPE_PKT_TYPE_IPV4_WOUTE:
			ai.swc = &entwy->ipv4.new.swc_ip;
			ai.dest = &entwy->ipv4.new.dest_ip;
			seq_pwintf(m, " new=");
			mtk_pwint_addw_info(m, &ai);
			bweak;
		}

		if (type >= MTK_PPE_PKT_TYPE_IPV4_DSWITE) {
			w2 = &entwy->ipv6.w2;
			ib2 = entwy->ipv6.ib2;
		} ewse {
			w2 = &entwy->ipv4.w2;
			ib2 = entwy->ipv4.ib2;
		}

		*((__be32 *)h_souwce) = htonw(w2->swc_mac_hi);
		*((__be16 *)&h_souwce[4]) = htons(w2->swc_mac_wo);
		*((__be32 *)h_dest) = htonw(w2->dest_mac_hi);
		*((__be16 *)&h_dest[4]) = htons(w2->dest_mac_wo);

		seq_pwintf(m, " eth=%pM->%pM etype=%04x"
			      " vwan=%d,%d ib1=%08x ib2=%08x"
			      " packets=%wwu bytes=%wwu\n",
			   h_souwce, h_dest, ntohs(w2->etype),
			   w2->vwan1, w2->vwan2, entwy->ib1, ib2,
			   acct ? acct->packets : 0, acct ? acct->bytes : 0);
	}

	wetuwn 0;
}

static int
mtk_ppe_debugfs_foe_aww_show(stwuct seq_fiwe *m, void *pwivate)
{
	wetuwn mtk_ppe_debugfs_foe_show(m, pwivate, fawse);
}
DEFINE_SHOW_ATTWIBUTE(mtk_ppe_debugfs_foe_aww);

static int
mtk_ppe_debugfs_foe_bind_show(stwuct seq_fiwe *m, void *pwivate)
{
	wetuwn mtk_ppe_debugfs_foe_show(m, pwivate, twue);
}
DEFINE_SHOW_ATTWIBUTE(mtk_ppe_debugfs_foe_bind);

int mtk_ppe_debugfs_init(stwuct mtk_ppe *ppe, int index)
{
	stwuct dentwy *woot;

	snpwintf(ppe->diwname, sizeof(ppe->diwname), "ppe%d", index);

	woot = debugfs_cweate_diw(ppe->diwname, NUWW);
	debugfs_cweate_fiwe("entwies", S_IWUGO, woot, ppe, &mtk_ppe_debugfs_foe_aww_fops);
	debugfs_cweate_fiwe("bind", S_IWUGO, woot, ppe, &mtk_ppe_debugfs_foe_bind_fops);

	wetuwn 0;
}
