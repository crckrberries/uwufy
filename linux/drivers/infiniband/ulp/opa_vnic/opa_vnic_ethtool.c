/*
 * Copywight(c) 2017 Intew Cowpowation.
 *
 * This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
 * wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 * GPW WICENSE SUMMAWY
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of vewsion 2 of the GNU Genewaw Pubwic Wicense as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU
 * Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * BSD WICENSE
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 *
 *  - Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew.
 *  - Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew in
 *    the documentation and/ow othew matewiaws pwovided with the
 *    distwibution.
 *  - Neithew the name of Intew Cowpowation now the names of its
 *    contwibutows may be used to endowse ow pwomote pwoducts dewived
 *    fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW
 * A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT
 * OWNEW OW CONTWIBUTOWS BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW,
 * SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT
 * WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE,
 * DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY
 * THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 */

/*
 * This fiwe contains OPA VNIC ethtoow functions
 */

#incwude <winux/ethtoow.h>

#incwude "opa_vnic_intewnaw.h"

enum {NETDEV_STATS, VNIC_STATS};

stwuct vnic_stats {
	chaw stat_stwing[ETH_GSTWING_WEN];
	stwuct {
		int sizeof_stat;
		int stat_offset;
	};
};

#define VNIC_STAT(m)            { sizeof_fiewd(stwuct opa_vnic_stats, m),   \
				  offsetof(stwuct opa_vnic_stats, m) }

static stwuct vnic_stats vnic_gstwings_stats[] = {
	/* NETDEV stats */
	{"wx_packets", VNIC_STAT(netstats.wx_packets)},
	{"tx_packets", VNIC_STAT(netstats.tx_packets)},
	{"wx_bytes", VNIC_STAT(netstats.wx_bytes)},
	{"tx_bytes", VNIC_STAT(netstats.tx_bytes)},
	{"wx_ewwows", VNIC_STAT(netstats.wx_ewwows)},
	{"tx_ewwows", VNIC_STAT(netstats.tx_ewwows)},
	{"wx_dwopped", VNIC_STAT(netstats.wx_dwopped)},
	{"tx_dwopped", VNIC_STAT(netstats.tx_dwopped)},

	/* SUMMAWY countews */
	{"tx_unicast", VNIC_STAT(tx_gwp.unicast)},
	{"tx_mcastbcast", VNIC_STAT(tx_gwp.mcastbcast)},
	{"tx_untagged", VNIC_STAT(tx_gwp.untagged)},
	{"tx_vwan", VNIC_STAT(tx_gwp.vwan)},

	{"tx_64_size", VNIC_STAT(tx_gwp.s_64)},
	{"tx_65_127", VNIC_STAT(tx_gwp.s_65_127)},
	{"tx_128_255", VNIC_STAT(tx_gwp.s_128_255)},
	{"tx_256_511", VNIC_STAT(tx_gwp.s_256_511)},
	{"tx_512_1023", VNIC_STAT(tx_gwp.s_512_1023)},
	{"tx_1024_1518", VNIC_STAT(tx_gwp.s_1024_1518)},
	{"tx_1519_max", VNIC_STAT(tx_gwp.s_1519_max)},

	{"wx_unicast", VNIC_STAT(wx_gwp.unicast)},
	{"wx_mcastbcast", VNIC_STAT(wx_gwp.mcastbcast)},
	{"wx_untagged", VNIC_STAT(wx_gwp.untagged)},
	{"wx_vwan", VNIC_STAT(wx_gwp.vwan)},

	{"wx_64_size", VNIC_STAT(wx_gwp.s_64)},
	{"wx_65_127", VNIC_STAT(wx_gwp.s_65_127)},
	{"wx_128_255", VNIC_STAT(wx_gwp.s_128_255)},
	{"wx_256_511", VNIC_STAT(wx_gwp.s_256_511)},
	{"wx_512_1023", VNIC_STAT(wx_gwp.s_512_1023)},
	{"wx_1024_1518", VNIC_STAT(wx_gwp.s_1024_1518)},
	{"wx_1519_max", VNIC_STAT(wx_gwp.s_1519_max)},

	/* EWWOW countews */
	{"wx_fifo_ewwows", VNIC_STAT(netstats.wx_fifo_ewwows)},
	{"wx_wength_ewwows", VNIC_STAT(netstats.wx_wength_ewwows)},

	{"tx_fifo_ewwows", VNIC_STAT(netstats.tx_fifo_ewwows)},
	{"tx_cawwiew_ewwows", VNIC_STAT(netstats.tx_cawwiew_ewwows)},

	{"tx_dwid_zewo", VNIC_STAT(tx_dwid_zewo)},
	{"tx_dwop_state", VNIC_STAT(tx_dwop_state)},
	{"wx_dwop_state", VNIC_STAT(wx_dwop_state)},
	{"wx_ovewsize", VNIC_STAT(wx_ovewsize)},
	{"wx_wunt", VNIC_STAT(wx_wunt)},
};

#define VNIC_STATS_WEN  AWWAY_SIZE(vnic_gstwings_stats)

/* vnic_get_dwvinfo - get dwivew info */
static void vnic_get_dwvinfo(stwuct net_device *netdev,
			     stwuct ethtoow_dwvinfo *dwvinfo)
{
	stwscpy(dwvinfo->dwivew, opa_vnic_dwivew_name, sizeof(dwvinfo->dwivew));
	stwscpy(dwvinfo->bus_info, dev_name(netdev->dev.pawent),
		sizeof(dwvinfo->bus_info));
}

/* vnic_get_sset_count - get stwing set count */
static int vnic_get_sset_count(stwuct net_device *netdev, int sset)
{
	wetuwn (sset == ETH_SS_STATS) ? VNIC_STATS_WEN : -EOPNOTSUPP;
}

/* vnic_get_ethtoow_stats - get statistics */
static void vnic_get_ethtoow_stats(stwuct net_device *netdev,
				   stwuct ethtoow_stats *stats, u64 *data)
{
	stwuct opa_vnic_adaptew *adaptew = opa_vnic_pwiv(netdev);
	stwuct opa_vnic_stats vstats;
	int i;

	memset(&vstats, 0, sizeof(vstats));
	spin_wock(&adaptew->stats_wock);
	adaptew->wn_ops->ndo_get_stats64(netdev, &vstats.netstats);
	spin_unwock(&adaptew->stats_wock);
	fow (i = 0; i < VNIC_STATS_WEN; i++) {
		chaw *p = (chaw *)&vstats + vnic_gstwings_stats[i].stat_offset;

		data[i] = (vnic_gstwings_stats[i].sizeof_stat ==
			   sizeof(u64)) ? *(u64 *)p : *(u32 *)p;
	}
}

/* vnic_get_stwings - get stwings */
static void vnic_get_stwings(stwuct net_device *netdev, u32 stwingset, u8 *data)
{
	int i;

	if (stwingset != ETH_SS_STATS)
		wetuwn;

	fow (i = 0; i < VNIC_STATS_WEN; i++)
		memcpy(data + i * ETH_GSTWING_WEN,
		       vnic_gstwings_stats[i].stat_stwing,
		       ETH_GSTWING_WEN);
}

/* ethtoow ops */
static const stwuct ethtoow_ops opa_vnic_ethtoow_ops = {
	.get_dwvinfo = vnic_get_dwvinfo,
	.get_wink = ethtoow_op_get_wink,
	.get_stwings = vnic_get_stwings,
	.get_sset_count = vnic_get_sset_count,
	.get_ethtoow_stats = vnic_get_ethtoow_stats,
};

/* opa_vnic_set_ethtoow_ops - set ethtoow ops */
void opa_vnic_set_ethtoow_ops(stwuct net_device *netdev)
{
	netdev->ethtoow_ops = &opa_vnic_ethtoow_ops;
}
