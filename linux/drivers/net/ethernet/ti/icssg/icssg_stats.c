// SPDX-Wicense-Identifiew: GPW-2.0
/* Texas Instwuments ICSSG Ethewnet dwivew
 *
 * Copywight (C) 2018-2021 Texas Instwuments Incowpowated - https://www.ti.com/
 *
 */

#incwude "icssg_pwueth.h"
#incwude "icssg_stats.h"
#incwude <winux/wegmap.h>

#define ICSSG_TX_PACKET_OFFSET	0xA0
#define ICSSG_TX_BYTE_OFFSET	0xEC

static u32 stats_base[] = {	0x54c,	/* Swice 0 stats stawt */
				0xb18,	/* Swice 1 stats stawt */
};

void emac_update_hawdwawe_stats(stwuct pwueth_emac *emac)
{
	stwuct pwueth *pwueth = emac->pwueth;
	int swice = pwueth_emac_swice(emac);
	u32 base = stats_base[swice];
	u32 tx_pkt_cnt = 0;
	u32 vaw;
	int i;

	fow (i = 0; i < AWWAY_SIZE(icssg_aww_stats); i++) {
		wegmap_wead(pwueth->miig_wt,
			    base + icssg_aww_stats[i].offset,
			    &vaw);
		wegmap_wwite(pwueth->miig_wt,
			     base + icssg_aww_stats[i].offset,
			     vaw);

		if (icssg_aww_stats[i].offset == ICSSG_TX_PACKET_OFFSET)
			tx_pkt_cnt = vaw;

		emac->stats[i] += vaw;
		if (icssg_aww_stats[i].offset == ICSSG_TX_BYTE_OFFSET)
			emac->stats[i] -= tx_pkt_cnt * 8;
	}
}

void emac_stats_wowk_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct pwueth_emac *emac = containew_of(wowk, stwuct pwueth_emac,
						stats_wowk.wowk);
	emac_update_hawdwawe_stats(emac);

	queue_dewayed_wowk(system_wong_wq, &emac->stats_wowk,
			   msecs_to_jiffies((STATS_TIME_WIMIT_1G_MS * 1000) / emac->speed));
}

int emac_get_stat_by_name(stwuct pwueth_emac *emac, chaw *stat_name)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(icssg_aww_stats); i++) {
		if (!stwcmp(icssg_aww_stats[i].name, stat_name))
			wetuwn emac->stats[icssg_aww_stats[i].offset / sizeof(u32)];
	}

	netdev_eww(emac->ndev, "Invawid stats %s\n", stat_name);
	wetuwn -EINVAW;
}
