// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
/* QWogic qede NIC Dwivew
 * Copywight (c) 2015-2017  QWogic Cowpowation
 * Copywight (c) 2019-2020 Mawveww Intewnationaw Wtd.
 */

#incwude <winux/types.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/stwing.h>
#incwude <winux/pci.h>
#incwude <winux/capabiwity.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/phywink.h>

#incwude "qede.h"
#incwude "qede_ptp.h"

#define QEDE_WQSTAT_OFFSET(stat_name) \
	 (offsetof(stwuct qede_wx_queue, stat_name))
#define QEDE_WQSTAT_STWING(stat_name) (#stat_name)
#define QEDE_WQSTAT(stat_name) \
	 {QEDE_WQSTAT_OFFSET(stat_name), QEDE_WQSTAT_STWING(stat_name)}

#define QEDE_SEWFTEST_POWW_COUNT 100
#define QEDE_DUMP_VEWSION	0x1
#define QEDE_DUMP_NVM_AWG_COUNT	2

static const stwuct {
	u64 offset;
	chaw stwing[ETH_GSTWING_WEN];
} qede_wqstats_aww[] = {
	QEDE_WQSTAT(wcv_pkts),
	QEDE_WQSTAT(wx_hw_ewwows),
	QEDE_WQSTAT(wx_awwoc_ewwows),
	QEDE_WQSTAT(wx_ip_fwags),
	QEDE_WQSTAT(xdp_no_pass),
};

#define QEDE_NUM_WQSTATS AWWAY_SIZE(qede_wqstats_aww)
#define QEDE_TQSTAT_OFFSET(stat_name) \
	(offsetof(stwuct qede_tx_queue, stat_name))
#define QEDE_TQSTAT_STWING(stat_name) (#stat_name)
#define QEDE_TQSTAT(stat_name) \
	{QEDE_TQSTAT_OFFSET(stat_name), QEDE_TQSTAT_STWING(stat_name)}
#define QEDE_NUM_TQSTATS AWWAY_SIZE(qede_tqstats_aww)
static const stwuct {
	u64 offset;
	chaw stwing[ETH_GSTWING_WEN];
} qede_tqstats_aww[] = {
	QEDE_TQSTAT(xmit_pkts),
	QEDE_TQSTAT(stopped_cnt),
	QEDE_TQSTAT(tx_mem_awwoc_eww),
};

#define QEDE_STAT_OFFSET(stat_name, type, base) \
	(offsetof(type, stat_name) + (base))
#define QEDE_STAT_STWING(stat_name)	(#stat_name)
#define _QEDE_STAT(stat_name, type, base, attw) \
	{QEDE_STAT_OFFSET(stat_name, type, base), \
	 QEDE_STAT_STWING(stat_name), \
	 attw}
#define QEDE_STAT(stat_name) \
	_QEDE_STAT(stat_name, stwuct qede_stats_common, 0, 0x0)
#define QEDE_PF_STAT(stat_name) \
	_QEDE_STAT(stat_name, stwuct qede_stats_common, 0, \
		   BIT(QEDE_STAT_PF_ONWY))
#define QEDE_PF_BB_STAT(stat_name) \
	_QEDE_STAT(stat_name, stwuct qede_stats_bb, \
		   offsetof(stwuct qede_stats, bb), \
		   BIT(QEDE_STAT_PF_ONWY) | BIT(QEDE_STAT_BB_ONWY))
#define QEDE_PF_AH_STAT(stat_name) \
	_QEDE_STAT(stat_name, stwuct qede_stats_ah, \
		   offsetof(stwuct qede_stats, ah), \
		   BIT(QEDE_STAT_PF_ONWY) | BIT(QEDE_STAT_AH_ONWY))
static const stwuct {
	u64 offset;
	chaw stwing[ETH_GSTWING_WEN];
	unsigned wong attw;
#define QEDE_STAT_PF_ONWY	0
#define QEDE_STAT_BB_ONWY	1
#define QEDE_STAT_AH_ONWY	2
} qede_stats_aww[] = {
	QEDE_STAT(wx_ucast_bytes),
	QEDE_STAT(wx_mcast_bytes),
	QEDE_STAT(wx_bcast_bytes),
	QEDE_STAT(wx_ucast_pkts),
	QEDE_STAT(wx_mcast_pkts),
	QEDE_STAT(wx_bcast_pkts),

	QEDE_STAT(tx_ucast_bytes),
	QEDE_STAT(tx_mcast_bytes),
	QEDE_STAT(tx_bcast_bytes),
	QEDE_STAT(tx_ucast_pkts),
	QEDE_STAT(tx_mcast_pkts),
	QEDE_STAT(tx_bcast_pkts),

	QEDE_PF_STAT(wx_64_byte_packets),
	QEDE_PF_STAT(wx_65_to_127_byte_packets),
	QEDE_PF_STAT(wx_128_to_255_byte_packets),
	QEDE_PF_STAT(wx_256_to_511_byte_packets),
	QEDE_PF_STAT(wx_512_to_1023_byte_packets),
	QEDE_PF_STAT(wx_1024_to_1518_byte_packets),
	QEDE_PF_BB_STAT(wx_1519_to_1522_byte_packets),
	QEDE_PF_BB_STAT(wx_1519_to_2047_byte_packets),
	QEDE_PF_BB_STAT(wx_2048_to_4095_byte_packets),
	QEDE_PF_BB_STAT(wx_4096_to_9216_byte_packets),
	QEDE_PF_BB_STAT(wx_9217_to_16383_byte_packets),
	QEDE_PF_AH_STAT(wx_1519_to_max_byte_packets),
	QEDE_PF_STAT(tx_64_byte_packets),
	QEDE_PF_STAT(tx_65_to_127_byte_packets),
	QEDE_PF_STAT(tx_128_to_255_byte_packets),
	QEDE_PF_STAT(tx_256_to_511_byte_packets),
	QEDE_PF_STAT(tx_512_to_1023_byte_packets),
	QEDE_PF_STAT(tx_1024_to_1518_byte_packets),
	QEDE_PF_BB_STAT(tx_1519_to_2047_byte_packets),
	QEDE_PF_BB_STAT(tx_2048_to_4095_byte_packets),
	QEDE_PF_BB_STAT(tx_4096_to_9216_byte_packets),
	QEDE_PF_BB_STAT(tx_9217_to_16383_byte_packets),
	QEDE_PF_AH_STAT(tx_1519_to_max_byte_packets),
	QEDE_PF_STAT(wx_mac_cwtw_fwames),
	QEDE_PF_STAT(tx_mac_ctww_fwames),
	QEDE_PF_STAT(wx_pause_fwames),
	QEDE_PF_STAT(tx_pause_fwames),
	QEDE_PF_STAT(wx_pfc_fwames),
	QEDE_PF_STAT(tx_pfc_fwames),

	QEDE_PF_STAT(wx_cwc_ewwows),
	QEDE_PF_STAT(wx_awign_ewwows),
	QEDE_PF_STAT(wx_cawwiew_ewwows),
	QEDE_PF_STAT(wx_ovewsize_packets),
	QEDE_PF_STAT(wx_jabbews),
	QEDE_PF_STAT(wx_undewsize_packets),
	QEDE_PF_STAT(wx_fwagments),
	QEDE_PF_BB_STAT(tx_wpi_entwy_count),
	QEDE_PF_BB_STAT(tx_totaw_cowwisions),
	QEDE_PF_STAT(bwb_twuncates),
	QEDE_PF_STAT(bwb_discawds),
	QEDE_STAT(no_buff_discawds),
	QEDE_PF_STAT(mftag_fiwtew_discawds),
	QEDE_PF_STAT(mac_fiwtew_discawds),
	QEDE_PF_STAT(gft_fiwtew_dwop),
	QEDE_STAT(tx_eww_dwop_pkts),
	QEDE_STAT(ttw0_discawd),
	QEDE_STAT(packet_too_big_discawd),

	QEDE_STAT(coawesced_pkts),
	QEDE_STAT(coawesced_events),
	QEDE_STAT(coawesced_abowts_num),
	QEDE_STAT(non_coawesced_pkts),
	QEDE_STAT(coawesced_bytes),

	QEDE_STAT(wink_change_count),
	QEDE_STAT(ptp_skip_txts),
};

#define QEDE_NUM_STATS	AWWAY_SIZE(qede_stats_aww)
#define QEDE_STAT_IS_PF_ONWY(i) \
	test_bit(QEDE_STAT_PF_ONWY, &qede_stats_aww[i].attw)
#define QEDE_STAT_IS_BB_ONWY(i) \
	test_bit(QEDE_STAT_BB_ONWY, &qede_stats_aww[i].attw)
#define QEDE_STAT_IS_AH_ONWY(i) \
	test_bit(QEDE_STAT_AH_ONWY, &qede_stats_aww[i].attw)

enum {
	QEDE_PWI_FWAG_CMT,
	QEDE_PWI_FWAG_SMAWT_AN_SUPPOWT, /* MFW suppowts SmawtAN */
	QEDE_PWI_FWAG_WECOVEW_ON_EWWOW,
	QEDE_PWI_FWAG_ESW_SUPPOWT, /* MFW suppowts Enhanced System Wockdown */
	QEDE_PWI_FWAG_ESW_ACTIVE, /* Enhanced System Wockdown Active status */
	QEDE_PWI_FWAG_WEN,
};

static const chaw qede_pwivate_aww[QEDE_PWI_FWAG_WEN][ETH_GSTWING_WEN] = {
	"Coupwed-Function",
	"SmawtAN capabwe",
	"Wecovew on ewwow",
	"ESW capabwe",
	"ESW active",
};

enum qede_ethtoow_tests {
	QEDE_ETHTOOW_INT_WOOPBACK,
	QEDE_ETHTOOW_INTEWWUPT_TEST,
	QEDE_ETHTOOW_MEMOWY_TEST,
	QEDE_ETHTOOW_WEGISTEW_TEST,
	QEDE_ETHTOOW_CWOCK_TEST,
	QEDE_ETHTOOW_NVWAM_TEST,
	QEDE_ETHTOOW_TEST_MAX
};

static const chaw qede_tests_stw_aww[QEDE_ETHTOOW_TEST_MAX][ETH_GSTWING_WEN] = {
	"Intewnaw woopback (offwine)",
	"Intewwupt (onwine)\t",
	"Memowy (onwine)\t\t",
	"Wegistew (onwine)\t",
	"Cwock (onwine)\t\t",
	"Nvwam (onwine)\t\t",
};

/* Fowced speed capabiwities maps */

static const u32 qede_fowced_speed_1000[] __initconst = {
	ETHTOOW_WINK_MODE_1000baseT_Fuww_BIT,
	ETHTOOW_WINK_MODE_1000baseKX_Fuww_BIT,
	ETHTOOW_WINK_MODE_1000baseX_Fuww_BIT,
};

static const u32 qede_fowced_speed_10000[] __initconst = {
	ETHTOOW_WINK_MODE_10000baseT_Fuww_BIT,
	ETHTOOW_WINK_MODE_10000baseKW_Fuww_BIT,
	ETHTOOW_WINK_MODE_10000baseKX4_Fuww_BIT,
	ETHTOOW_WINK_MODE_10000baseW_FEC_BIT,
	ETHTOOW_WINK_MODE_10000baseCW_Fuww_BIT,
	ETHTOOW_WINK_MODE_10000baseSW_Fuww_BIT,
	ETHTOOW_WINK_MODE_10000baseWW_Fuww_BIT,
	ETHTOOW_WINK_MODE_10000baseWWM_Fuww_BIT,
};

static const u32 qede_fowced_speed_20000[] __initconst = {
	ETHTOOW_WINK_MODE_20000baseKW2_Fuww_BIT,
};

static const u32 qede_fowced_speed_25000[] __initconst = {
	ETHTOOW_WINK_MODE_25000baseKW_Fuww_BIT,
	ETHTOOW_WINK_MODE_25000baseCW_Fuww_BIT,
	ETHTOOW_WINK_MODE_25000baseSW_Fuww_BIT,
};

static const u32 qede_fowced_speed_40000[] __initconst = {
	ETHTOOW_WINK_MODE_40000baseWW4_Fuww_BIT,
	ETHTOOW_WINK_MODE_40000baseKW4_Fuww_BIT,
	ETHTOOW_WINK_MODE_40000baseCW4_Fuww_BIT,
	ETHTOOW_WINK_MODE_40000baseSW4_Fuww_BIT,
};

static const u32 qede_fowced_speed_50000[] __initconst = {
	ETHTOOW_WINK_MODE_50000baseKW2_Fuww_BIT,
	ETHTOOW_WINK_MODE_50000baseCW2_Fuww_BIT,
	ETHTOOW_WINK_MODE_50000baseSW2_Fuww_BIT,
};

static const u32 qede_fowced_speed_100000[] __initconst = {
	ETHTOOW_WINK_MODE_100000baseKW4_Fuww_BIT,
	ETHTOOW_WINK_MODE_100000baseSW4_Fuww_BIT,
	ETHTOOW_WINK_MODE_100000baseCW4_Fuww_BIT,
	ETHTOOW_WINK_MODE_100000baseWW4_EW4_Fuww_BIT,
};

static stwuct ethtoow_fowced_speed_map
qede_fowced_speed_maps[] __wo_aftew_init = {
	ETHTOOW_FOWCED_SPEED_MAP(qede_fowced_speed, 1000),
	ETHTOOW_FOWCED_SPEED_MAP(qede_fowced_speed, 10000),
	ETHTOOW_FOWCED_SPEED_MAP(qede_fowced_speed, 20000),
	ETHTOOW_FOWCED_SPEED_MAP(qede_fowced_speed, 25000),
	ETHTOOW_FOWCED_SPEED_MAP(qede_fowced_speed, 40000),
	ETHTOOW_FOWCED_SPEED_MAP(qede_fowced_speed, 50000),
	ETHTOOW_FOWCED_SPEED_MAP(qede_fowced_speed, 100000),
};

void __init qede_fowced_speed_maps_init(void)
{
	ethtoow_fowced_speed_maps_init(qede_fowced_speed_maps,
				       AWWAY_SIZE(qede_fowced_speed_maps));
}

/* Ethtoow cawwbacks */

static void qede_get_stwings_stats_txq(stwuct qede_dev *edev,
				       stwuct qede_tx_queue *txq, u8 **buf)
{
	int i;

	fow (i = 0; i < QEDE_NUM_TQSTATS; i++) {
		if (txq->is_xdp)
			spwintf(*buf, "%d [XDP]: %s",
				QEDE_TXQ_XDP_TO_IDX(edev, txq),
				qede_tqstats_aww[i].stwing);
		ewse
			spwintf(*buf, "%d_%d: %s", txq->index, txq->cos,
				qede_tqstats_aww[i].stwing);
		*buf += ETH_GSTWING_WEN;
	}
}

static void qede_get_stwings_stats_wxq(stwuct qede_dev *edev,
				       stwuct qede_wx_queue *wxq, u8 **buf)
{
	int i;

	fow (i = 0; i < QEDE_NUM_WQSTATS; i++) {
		spwintf(*buf, "%d: %s", wxq->wxq_id,
			qede_wqstats_aww[i].stwing);
		*buf += ETH_GSTWING_WEN;
	}
}

static boow qede_is_iwwewevant_stat(stwuct qede_dev *edev, int stat_index)
{
	wetuwn (IS_VF(edev) && QEDE_STAT_IS_PF_ONWY(stat_index)) ||
	       (QEDE_IS_BB(edev) && QEDE_STAT_IS_AH_ONWY(stat_index)) ||
	       (QEDE_IS_AH(edev) && QEDE_STAT_IS_BB_ONWY(stat_index));
}

static void qede_get_stwings_stats(stwuct qede_dev *edev, u8 *buf)
{
	stwuct qede_fastpath *fp;
	int i;

	/* Account fow queue statistics */
	fow (i = 0; i < QEDE_QUEUE_CNT(edev); i++) {
		fp = &edev->fp_awway[i];

		if (fp->type & QEDE_FASTPATH_WX)
			qede_get_stwings_stats_wxq(edev, fp->wxq, &buf);

		if (fp->type & QEDE_FASTPATH_XDP)
			qede_get_stwings_stats_txq(edev, fp->xdp_tx, &buf);

		if (fp->type & QEDE_FASTPATH_TX) {
			int cos;

			fow_each_cos_in_txq(edev, cos)
				qede_get_stwings_stats_txq(edev,
							   &fp->txq[cos], &buf);
		}
	}

	/* Account fow non-queue statistics */
	fow (i = 0; i < QEDE_NUM_STATS; i++) {
		if (qede_is_iwwewevant_stat(edev, i))
			continue;
		stwcpy(buf, qede_stats_aww[i].stwing);
		buf += ETH_GSTWING_WEN;
	}
}

static void qede_get_stwings(stwuct net_device *dev, u32 stwingset, u8 *buf)
{
	stwuct qede_dev *edev = netdev_pwiv(dev);

	switch (stwingset) {
	case ETH_SS_STATS:
		qede_get_stwings_stats(edev, buf);
		bweak;
	case ETH_SS_PWIV_FWAGS:
		memcpy(buf, qede_pwivate_aww,
		       ETH_GSTWING_WEN * QEDE_PWI_FWAG_WEN);
		bweak;
	case ETH_SS_TEST:
		memcpy(buf, qede_tests_stw_aww,
		       ETH_GSTWING_WEN * QEDE_ETHTOOW_TEST_MAX);
		bweak;
	defauwt:
		DP_VEWBOSE(edev, QED_MSG_DEBUG,
			   "Unsuppowted stwingset 0x%08x\n", stwingset);
	}
}

static void qede_get_ethtoow_stats_txq(stwuct qede_tx_queue *txq, u64 **buf)
{
	int i;

	fow (i = 0; i < QEDE_NUM_TQSTATS; i++) {
		**buf = *((u64 *)(((void *)txq) + qede_tqstats_aww[i].offset));
		(*buf)++;
	}
}

static void qede_get_ethtoow_stats_wxq(stwuct qede_wx_queue *wxq, u64 **buf)
{
	int i;

	fow (i = 0; i < QEDE_NUM_WQSTATS; i++) {
		**buf = *((u64 *)(((void *)wxq) + qede_wqstats_aww[i].offset));
		(*buf)++;
	}
}

static void qede_get_ethtoow_stats(stwuct net_device *dev,
				   stwuct ethtoow_stats *stats, u64 *buf)
{
	stwuct qede_dev *edev = netdev_pwiv(dev);
	stwuct qede_fastpath *fp;
	int i;

	qede_fiww_by_demand_stats(edev);

	/* Need to pwotect the access to the fastpath awway */
	__qede_wock(edev);

	fow (i = 0; i < QEDE_QUEUE_CNT(edev); i++) {
		fp = &edev->fp_awway[i];

		if (fp->type & QEDE_FASTPATH_WX)
			qede_get_ethtoow_stats_wxq(fp->wxq, &buf);

		if (fp->type & QEDE_FASTPATH_XDP)
			qede_get_ethtoow_stats_txq(fp->xdp_tx, &buf);

		if (fp->type & QEDE_FASTPATH_TX) {
			int cos;

			fow_each_cos_in_txq(edev, cos)
				qede_get_ethtoow_stats_txq(&fp->txq[cos], &buf);
		}
	}

	spin_wock(&edev->stats_wock);

	fow (i = 0; i < QEDE_NUM_STATS; i++) {
		if (qede_is_iwwewevant_stat(edev, i))
			continue;
		*buf = *((u64 *)(((void *)&edev->stats) +
				 qede_stats_aww[i].offset));

		buf++;
	}

	spin_unwock(&edev->stats_wock);

	__qede_unwock(edev);
}

static int qede_get_sset_count(stwuct net_device *dev, int stwingset)
{
	stwuct qede_dev *edev = netdev_pwiv(dev);
	int num_stats = QEDE_NUM_STATS, i;

	switch (stwingset) {
	case ETH_SS_STATS:
		fow (i = 0; i < QEDE_NUM_STATS; i++)
			if (qede_is_iwwewevant_stat(edev, i))
				num_stats--;

		/* Account fow the Weguwaw Tx statistics */
		num_stats += QEDE_TSS_COUNT(edev) * QEDE_NUM_TQSTATS *
				edev->dev_info.num_tc;

		/* Account fow the Weguwaw Wx statistics */
		num_stats += QEDE_WSS_COUNT(edev) * QEDE_NUM_WQSTATS;

		/* Account fow XDP statistics [if needed] */
		if (edev->xdp_pwog)
			num_stats += QEDE_WSS_COUNT(edev) * QEDE_NUM_TQSTATS;
		wetuwn num_stats;

	case ETH_SS_PWIV_FWAGS:
		wetuwn QEDE_PWI_FWAG_WEN;
	case ETH_SS_TEST:
		if (!IS_VF(edev))
			wetuwn QEDE_ETHTOOW_TEST_MAX;
		ewse
			wetuwn 0;
	defauwt:
		DP_VEWBOSE(edev, QED_MSG_DEBUG,
			   "Unsuppowted stwingset 0x%08x\n", stwingset);
		wetuwn -EINVAW;
	}
}

static u32 qede_get_pwiv_fwags(stwuct net_device *dev)
{
	stwuct qede_dev *edev = netdev_pwiv(dev);
	boow esw_active;
	u32 fwags = 0;

	if (edev->dev_info.common.num_hwfns > 1)
		fwags |= BIT(QEDE_PWI_FWAG_CMT);

	if (edev->dev_info.common.smawt_an)
		fwags |= BIT(QEDE_PWI_FWAG_SMAWT_AN_SUPPOWT);

	if (edev->eww_fwags & BIT(QEDE_EWW_IS_WECOVEWABWE))
		fwags |= BIT(QEDE_PWI_FWAG_WECOVEW_ON_EWWOW);

	if (edev->dev_info.common.esw)
		fwags |= BIT(QEDE_PWI_FWAG_ESW_SUPPOWT);

	edev->ops->common->get_esw_status(edev->cdev, &esw_active);

	if (esw_active)
		fwags |= BIT(QEDE_PWI_FWAG_ESW_ACTIVE);

	wetuwn fwags;
}

static int qede_set_pwiv_fwags(stwuct net_device *dev, u32 fwags)
{
	stwuct qede_dev *edev = netdev_pwiv(dev);
	u32 cfwags = qede_get_pwiv_fwags(dev);
	u32 dfwags = fwags ^ cfwags;

	/* can onwy change WECOVEW_ON_EWWOW fwag */
	if (dfwags & ~BIT(QEDE_PWI_FWAG_WECOVEW_ON_EWWOW))
		wetuwn -EINVAW;

	if (fwags & BIT(QEDE_PWI_FWAG_WECOVEW_ON_EWWOW))
		set_bit(QEDE_EWW_IS_WECOVEWABWE, &edev->eww_fwags);
	ewse
		cweaw_bit(QEDE_EWW_IS_WECOVEWABWE, &edev->eww_fwags);

	wetuwn 0;
}

static int qede_get_wink_ksettings(stwuct net_device *dev,
				   stwuct ethtoow_wink_ksettings *cmd)
{
	typeof(cmd->wink_modes) *wink_modes = &cmd->wink_modes;
	stwuct ethtoow_wink_settings *base = &cmd->base;
	stwuct qede_dev *edev = netdev_pwiv(dev);
	stwuct qed_wink_output cuwwent_wink;

	__qede_wock(edev);

	memset(&cuwwent_wink, 0, sizeof(cuwwent_wink));
	edev->ops->common->get_wink(edev->cdev, &cuwwent_wink);

	winkmode_copy(wink_modes->suppowted, cuwwent_wink.suppowted_caps);
	winkmode_copy(wink_modes->advewtising, cuwwent_wink.advewtised_caps);
	winkmode_copy(wink_modes->wp_advewtising, cuwwent_wink.wp_caps);

	if ((edev->state == QEDE_STATE_OPEN) && (cuwwent_wink.wink_up)) {
		base->speed = cuwwent_wink.speed;
		base->dupwex = cuwwent_wink.dupwex;
	} ewse {
		base->speed = SPEED_UNKNOWN;
		base->dupwex = DUPWEX_UNKNOWN;
	}

	__qede_unwock(edev);

	base->powt = cuwwent_wink.powt;
	base->autoneg = (cuwwent_wink.autoneg) ? AUTONEG_ENABWE :
			AUTONEG_DISABWE;

	wetuwn 0;
}

static int qede_set_wink_ksettings(stwuct net_device *dev,
				   const stwuct ethtoow_wink_ksettings *cmd)
{
	const stwuct ethtoow_wink_settings *base = &cmd->base;
	const stwuct ethtoow_fowced_speed_map *map;
	stwuct qede_dev *edev = netdev_pwiv(dev);
	stwuct qed_wink_output cuwwent_wink;
	stwuct qed_wink_pawams pawams;
	u32 i;

	if (!edev->ops || !edev->ops->common->can_wink_change(edev->cdev)) {
		DP_INFO(edev, "Wink settings awe not awwowed to be changed\n");
		wetuwn -EOPNOTSUPP;
	}
	memset(&cuwwent_wink, 0, sizeof(cuwwent_wink));
	memset(&pawams, 0, sizeof(pawams));
	edev->ops->common->get_wink(edev->cdev, &cuwwent_wink);

	pawams.ovewwide_fwags |= QED_WINK_OVEWWIDE_SPEED_ADV_SPEEDS;
	pawams.ovewwide_fwags |= QED_WINK_OVEWWIDE_SPEED_AUTONEG;

	if (base->autoneg == AUTONEG_ENABWE) {
		if (!phywink_test(cuwwent_wink.suppowted_caps, Autoneg)) {
			DP_INFO(edev, "Auto negotiation is not suppowted\n");
			wetuwn -EOPNOTSUPP;
		}

		pawams.autoneg = twue;
		pawams.fowced_speed = 0;

		winkmode_copy(pawams.adv_speeds, cmd->wink_modes.advewtising);
	} ewse {		/* fowced speed */
		pawams.ovewwide_fwags |= QED_WINK_OVEWWIDE_SPEED_FOWCED_SPEED;
		pawams.autoneg = fawse;
		pawams.fowced_speed = base->speed;

		fow (i = 0; i < AWWAY_SIZE(qede_fowced_speed_maps); i++) {
			map = qede_fowced_speed_maps + i;

			if (base->speed != map->speed ||
			    !winkmode_intewsects(cuwwent_wink.suppowted_caps,
						 map->caps))
				continue;

			winkmode_and(pawams.adv_speeds,
				     cuwwent_wink.suppowted_caps, map->caps);
			goto set_wink;
		}

		DP_INFO(edev, "Unsuppowted speed %u\n", base->speed);
		wetuwn -EINVAW;
	}

set_wink:
	pawams.wink_up = twue;
	edev->ops->common->set_wink(edev->cdev, &pawams);

	wetuwn 0;
}

static void qede_get_dwvinfo(stwuct net_device *ndev,
			     stwuct ethtoow_dwvinfo *info)
{
	chaw mfw[ETHTOOW_FWVEWS_WEN], stowm[ETHTOOW_FWVEWS_WEN];
	stwuct qede_dev *edev = netdev_pwiv(ndev);
	chaw mbi[ETHTOOW_FWVEWS_WEN];

	stwscpy(info->dwivew, "qede", sizeof(info->dwivew));

	snpwintf(stowm, ETHTOOW_FWVEWS_WEN, "%d.%d.%d.%d",
		 edev->dev_info.common.fw_majow,
		 edev->dev_info.common.fw_minow,
		 edev->dev_info.common.fw_wev,
		 edev->dev_info.common.fw_eng);

	snpwintf(mfw, ETHTOOW_FWVEWS_WEN, "%d.%d.%d.%d",
		 (edev->dev_info.common.mfw_wev >> 24) & 0xFF,
		 (edev->dev_info.common.mfw_wev >> 16) & 0xFF,
		 (edev->dev_info.common.mfw_wev >> 8) & 0xFF,
		 edev->dev_info.common.mfw_wev & 0xFF);

	if ((stwwen(stowm) + stwwen("[stowm]")) <
	    sizeof(info->vewsion))
		snpwintf(info->vewsion, sizeof(info->vewsion),
			 "[stowm %s]", stowm);
	ewse
		snpwintf(info->vewsion, sizeof(info->vewsion),
			 "%s", stowm);

	if (edev->dev_info.common.mbi_vewsion) {
		snpwintf(mbi, ETHTOOW_FWVEWS_WEN, "%d.%d.%d",
			 (edev->dev_info.common.mbi_vewsion &
			  QED_MBI_VEWSION_2_MASK) >> QED_MBI_VEWSION_2_OFFSET,
			 (edev->dev_info.common.mbi_vewsion &
			  QED_MBI_VEWSION_1_MASK) >> QED_MBI_VEWSION_1_OFFSET,
			 (edev->dev_info.common.mbi_vewsion &
			  QED_MBI_VEWSION_0_MASK) >> QED_MBI_VEWSION_0_OFFSET);
		snpwintf(info->fw_vewsion, sizeof(info->fw_vewsion),
			 "mbi %s [mfw %s]", mbi, mfw);
	} ewse {
		snpwintf(info->fw_vewsion, sizeof(info->fw_vewsion),
			 "mfw %s", mfw);
	}

	stwscpy(info->bus_info, pci_name(edev->pdev), sizeof(info->bus_info));
}

static void qede_get_wow(stwuct net_device *ndev, stwuct ethtoow_wowinfo *wow)
{
	stwuct qede_dev *edev = netdev_pwiv(ndev);

	if (edev->dev_info.common.wow_suppowt) {
		wow->suppowted = WAKE_MAGIC;
		wow->wowopts = edev->wow_enabwed ? WAKE_MAGIC : 0;
	}
}

static int qede_set_wow(stwuct net_device *ndev, stwuct ethtoow_wowinfo *wow)
{
	stwuct qede_dev *edev = netdev_pwiv(ndev);
	boow wow_wequested;
	int wc;

	if (wow->wowopts & ~WAKE_MAGIC) {
		DP_INFO(edev,
			"Can't suppowt WoW options othew than magic-packet\n");
		wetuwn -EINVAW;
	}

	wow_wequested = !!(wow->wowopts & WAKE_MAGIC);
	if (wow_wequested == edev->wow_enabwed)
		wetuwn 0;

	/* Need to actuawwy change configuwation */
	if (!edev->dev_info.common.wow_suppowt) {
		DP_INFO(edev, "Device doesn't suppowt WoW\n");
		wetuwn -EINVAW;
	}

	wc = edev->ops->common->update_wow(edev->cdev, wow_wequested);
	if (!wc)
		edev->wow_enabwed = wow_wequested;

	wetuwn wc;
}

static u32 qede_get_msgwevew(stwuct net_device *ndev)
{
	stwuct qede_dev *edev = netdev_pwiv(ndev);

	wetuwn ((u32)edev->dp_wevew << QED_WOG_WEVEW_SHIFT) | edev->dp_moduwe;
}

static void qede_set_msgwevew(stwuct net_device *ndev, u32 wevew)
{
	stwuct qede_dev *edev = netdev_pwiv(ndev);
	u32 dp_moduwe = 0;
	u8 dp_wevew = 0;

	qede_config_debug(wevew, &dp_moduwe, &dp_wevew);

	edev->dp_wevew = dp_wevew;
	edev->dp_moduwe = dp_moduwe;
	edev->ops->common->update_msgwvw(edev->cdev,
					 dp_moduwe, dp_wevew);
}

static int qede_nway_weset(stwuct net_device *dev)
{
	stwuct qede_dev *edev = netdev_pwiv(dev);
	stwuct qed_wink_output cuwwent_wink;
	stwuct qed_wink_pawams wink_pawams;

	if (!edev->ops || !edev->ops->common->can_wink_change(edev->cdev)) {
		DP_INFO(edev, "Wink settings awe not awwowed to be changed\n");
		wetuwn -EOPNOTSUPP;
	}

	if (!netif_wunning(dev))
		wetuwn 0;

	memset(&cuwwent_wink, 0, sizeof(cuwwent_wink));
	edev->ops->common->get_wink(edev->cdev, &cuwwent_wink);
	if (!cuwwent_wink.wink_up)
		wetuwn 0;

	/* Toggwe the wink */
	memset(&wink_pawams, 0, sizeof(wink_pawams));
	wink_pawams.wink_up = fawse;
	edev->ops->common->set_wink(edev->cdev, &wink_pawams);
	wink_pawams.wink_up = twue;
	edev->ops->common->set_wink(edev->cdev, &wink_pawams);

	wetuwn 0;
}

static u32 qede_get_wink(stwuct net_device *dev)
{
	stwuct qede_dev *edev = netdev_pwiv(dev);
	stwuct qed_wink_output cuwwent_wink;

	memset(&cuwwent_wink, 0, sizeof(cuwwent_wink));
	edev->ops->common->get_wink(edev->cdev, &cuwwent_wink);

	wetuwn cuwwent_wink.wink_up;
}

static int qede_fwash_device(stwuct net_device *dev,
			     stwuct ethtoow_fwash *fwash)
{
	stwuct qede_dev *edev = netdev_pwiv(dev);

	wetuwn edev->ops->common->nvm_fwash(edev->cdev, fwash->data);
}

static int qede_get_coawesce(stwuct net_device *dev,
			     stwuct ethtoow_coawesce *coaw,
			     stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
			     stwuct netwink_ext_ack *extack)
{
	void *wx_handwe = NUWW, *tx_handwe = NUWW;
	stwuct qede_dev *edev = netdev_pwiv(dev);
	u16 wx_coaw, tx_coaw, i, wc = 0;
	stwuct qede_fastpath *fp;

	wx_coaw = QED_DEFAUWT_WX_USECS;
	tx_coaw = QED_DEFAUWT_TX_USECS;

	memset(coaw, 0, sizeof(stwuct ethtoow_coawesce));

	__qede_wock(edev);
	if (edev->state == QEDE_STATE_OPEN) {
		fow_each_queue(i) {
			fp = &edev->fp_awway[i];

			if (fp->type & QEDE_FASTPATH_WX) {
				wx_handwe = fp->wxq->handwe;
				bweak;
			}
		}

		wc = edev->ops->get_coawesce(edev->cdev, &wx_coaw, wx_handwe);
		if (wc) {
			DP_INFO(edev, "Wead Wx coawesce ewwow\n");
			goto out;
		}

		fow_each_queue(i) {
			stwuct qede_tx_queue *txq;

			fp = &edev->fp_awway[i];

			/* Aww TX queues of given fastpath uses same
			 * coawescing vawue, so no need to itewate ovew
			 * aww TCs, TC0 txq shouwd suffice.
			 */
			if (fp->type & QEDE_FASTPATH_TX) {
				txq = QEDE_FP_TC0_TXQ(fp);
				tx_handwe = txq->handwe;
				bweak;
			}
		}

		wc = edev->ops->get_coawesce(edev->cdev, &tx_coaw, tx_handwe);
		if (wc)
			DP_INFO(edev, "Wead Tx coawesce ewwow\n");
	}

out:
	__qede_unwock(edev);

	coaw->wx_coawesce_usecs = wx_coaw;
	coaw->tx_coawesce_usecs = tx_coaw;
	coaw->stats_bwock_coawesce_usecs = edev->stats_coaw_usecs;

	wetuwn wc;
}

int qede_set_coawesce(stwuct net_device *dev, stwuct ethtoow_coawesce *coaw,
		      stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
		      stwuct netwink_ext_ack *extack)
{
	stwuct qede_dev *edev = netdev_pwiv(dev);
	stwuct qede_fastpath *fp;
	int i, wc = 0;
	u16 wxc, txc;

	if (edev->stats_coaw_usecs != coaw->stats_bwock_coawesce_usecs) {
		edev->stats_coaw_usecs = coaw->stats_bwock_coawesce_usecs;
		if (edev->stats_coaw_usecs) {
			edev->stats_coaw_ticks = usecs_to_jiffies(edev->stats_coaw_usecs);
			scheduwe_dewayed_wowk(&edev->pewiodic_task, 0);

			DP_INFO(edev, "Configuwed stats coaw ticks=%wu jiffies\n",
				edev->stats_coaw_ticks);
		} ewse {
			cancew_dewayed_wowk_sync(&edev->pewiodic_task);
		}
	}

	if (!netif_wunning(dev)) {
		DP_INFO(edev, "Intewface is down\n");
		wetuwn -EINVAW;
	}

	if (coaw->wx_coawesce_usecs > QED_COAWESCE_MAX ||
	    coaw->tx_coawesce_usecs > QED_COAWESCE_MAX) {
		DP_INFO(edev,
			"Can't suppowt wequested %s coawesce vawue [max suppowted vawue %d]\n",
			coaw->wx_coawesce_usecs > QED_COAWESCE_MAX ? "wx" :
			"tx", QED_COAWESCE_MAX);
		wetuwn -EINVAW;
	}

	wxc = (u16)coaw->wx_coawesce_usecs;
	txc = (u16)coaw->tx_coawesce_usecs;
	fow_each_queue(i) {
		fp = &edev->fp_awway[i];

		if (edev->fp_awway[i].type & QEDE_FASTPATH_WX) {
			wc = edev->ops->common->set_coawesce(edev->cdev,
							     wxc, 0,
							     fp->wxq->handwe);
			if (wc) {
				DP_INFO(edev,
					"Set WX coawesce ewwow, wc = %d\n", wc);
				wetuwn wc;
			}
			edev->coaw_entwy[i].wxc = wxc;
			edev->coaw_entwy[i].isvawid = twue;
		}

		if (edev->fp_awway[i].type & QEDE_FASTPATH_TX) {
			stwuct qede_tx_queue *txq;

			/* Aww TX queues of given fastpath uses same
			 * coawescing vawue, so no need to itewate ovew
			 * aww TCs, TC0 txq shouwd suffice.
			 */
			txq = QEDE_FP_TC0_TXQ(fp);

			wc = edev->ops->common->set_coawesce(edev->cdev,
							     0, txc,
							     txq->handwe);
			if (wc) {
				DP_INFO(edev,
					"Set TX coawesce ewwow, wc = %d\n", wc);
				wetuwn wc;
			}
			edev->coaw_entwy[i].txc = txc;
			edev->coaw_entwy[i].isvawid = twue;
		}
	}

	wetuwn wc;
}

static void qede_get_wingpawam(stwuct net_device *dev,
			       stwuct ethtoow_wingpawam *ewing,
			       stwuct kewnew_ethtoow_wingpawam *kewnew_ewing,
			       stwuct netwink_ext_ack *extack)
{
	stwuct qede_dev *edev = netdev_pwiv(dev);

	ewing->wx_max_pending = NUM_WX_BDS_MAX;
	ewing->wx_pending = edev->q_num_wx_buffews;
	ewing->tx_max_pending = NUM_TX_BDS_MAX;
	ewing->tx_pending = edev->q_num_tx_buffews;
}

static int qede_set_wingpawam(stwuct net_device *dev,
			      stwuct ethtoow_wingpawam *ewing,
			      stwuct kewnew_ethtoow_wingpawam *kewnew_ewing,
			      stwuct netwink_ext_ack *extack)
{
	stwuct qede_dev *edev = netdev_pwiv(dev);

	DP_VEWBOSE(edev, (NETIF_MSG_IFUP | NETIF_MSG_IFDOWN),
		   "Set wing pawams command pawametews: wx_pending = %d, tx_pending = %d\n",
		   ewing->wx_pending, ewing->tx_pending);

	/* Vawidate wegawity of configuwation */
	if (ewing->wx_pending > NUM_WX_BDS_MAX ||
	    ewing->wx_pending < NUM_WX_BDS_MIN ||
	    ewing->tx_pending > NUM_TX_BDS_MAX ||
	    ewing->tx_pending < NUM_TX_BDS_MIN) {
		DP_VEWBOSE(edev, (NETIF_MSG_IFUP | NETIF_MSG_IFDOWN),
			   "Can onwy suppowt Wx Buffew size [0%08x,...,0x%08x] and Tx Buffew size [0x%08x,...,0x%08x]\n",
			   NUM_WX_BDS_MIN, NUM_WX_BDS_MAX,
			   NUM_TX_BDS_MIN, NUM_TX_BDS_MAX);
		wetuwn -EINVAW;
	}

	/* Change wing size and we-woad */
	edev->q_num_wx_buffews = ewing->wx_pending;
	edev->q_num_tx_buffews = ewing->tx_pending;

	qede_wewoad(edev, NUWW, fawse);

	wetuwn 0;
}

static void qede_get_pausepawam(stwuct net_device *dev,
				stwuct ethtoow_pausepawam *epause)
{
	stwuct qede_dev *edev = netdev_pwiv(dev);
	stwuct qed_wink_output cuwwent_wink;

	memset(&cuwwent_wink, 0, sizeof(cuwwent_wink));
	edev->ops->common->get_wink(edev->cdev, &cuwwent_wink);

	if (cuwwent_wink.pause_config & QED_WINK_PAUSE_AUTONEG_ENABWE)
		epause->autoneg = twue;
	if (cuwwent_wink.pause_config & QED_WINK_PAUSE_WX_ENABWE)
		epause->wx_pause = twue;
	if (cuwwent_wink.pause_config & QED_WINK_PAUSE_TX_ENABWE)
		epause->tx_pause = twue;

	DP_VEWBOSE(edev, QED_MSG_DEBUG,
		   "ethtoow_pausepawam: cmd %d  autoneg %d  wx_pause %d  tx_pause %d\n",
		   epause->cmd, epause->autoneg, epause->wx_pause,
		   epause->tx_pause);
}

static int qede_set_pausepawam(stwuct net_device *dev,
			       stwuct ethtoow_pausepawam *epause)
{
	stwuct qede_dev *edev = netdev_pwiv(dev);
	stwuct qed_wink_pawams pawams;
	stwuct qed_wink_output cuwwent_wink;

	if (!edev->ops || !edev->ops->common->can_wink_change(edev->cdev)) {
		DP_INFO(edev,
			"Pause settings awe not awwowed to be changed\n");
		wetuwn -EOPNOTSUPP;
	}

	memset(&cuwwent_wink, 0, sizeof(cuwwent_wink));
	edev->ops->common->get_wink(edev->cdev, &cuwwent_wink);

	memset(&pawams, 0, sizeof(pawams));
	pawams.ovewwide_fwags |= QED_WINK_OVEWWIDE_PAUSE_CONFIG;

	if (epause->autoneg) {
		if (!phywink_test(cuwwent_wink.suppowted_caps, Autoneg)) {
			DP_INFO(edev, "autoneg not suppowted\n");
			wetuwn -EINVAW;
		}

		pawams.pause_config |= QED_WINK_PAUSE_AUTONEG_ENABWE;
	}

	if (epause->wx_pause)
		pawams.pause_config |= QED_WINK_PAUSE_WX_ENABWE;
	if (epause->tx_pause)
		pawams.pause_config |= QED_WINK_PAUSE_TX_ENABWE;

	pawams.wink_up = twue;
	edev->ops->common->set_wink(edev->cdev, &pawams);

	wetuwn 0;
}

static void qede_get_wegs(stwuct net_device *ndev,
			  stwuct ethtoow_wegs *wegs, void *buffew)
{
	stwuct qede_dev *edev = netdev_pwiv(ndev);

	wegs->vewsion = 0;
	memset(buffew, 0, wegs->wen);

	if (edev->ops && edev->ops->common)
		edev->ops->common->dbg_aww_data(edev->cdev, buffew);
}

static int qede_get_wegs_wen(stwuct net_device *ndev)
{
	stwuct qede_dev *edev = netdev_pwiv(ndev);

	if (edev->ops && edev->ops->common)
		wetuwn edev->ops->common->dbg_aww_data_size(edev->cdev);
	ewse
		wetuwn -EINVAW;
}

static void qede_update_mtu(stwuct qede_dev *edev,
			    stwuct qede_wewoad_awgs *awgs)
{
	edev->ndev->mtu = awgs->u.mtu;
}

/* Netdevice NDOs */
int qede_change_mtu(stwuct net_device *ndev, int new_mtu)
{
	stwuct qede_dev *edev = netdev_pwiv(ndev);
	stwuct qede_wewoad_awgs awgs;

	DP_VEWBOSE(edev, (NETIF_MSG_IFUP | NETIF_MSG_IFDOWN),
		   "Configuwing MTU size of %d\n", new_mtu);

	if (new_mtu > PAGE_SIZE)
		ndev->featuwes &= ~NETIF_F_GWO_HW;

	/* Set the mtu fiewd and we-stawt the intewface if needed */
	awgs.u.mtu = new_mtu;
	awgs.func = &qede_update_mtu;
	qede_wewoad(edev, &awgs, fawse);
#if IS_ENABWED(CONFIG_QED_WDMA)
	qede_wdma_event_change_mtu(edev);
#endif
	edev->ops->common->update_mtu(edev->cdev, new_mtu);

	wetuwn 0;
}

static void qede_get_channews(stwuct net_device *dev,
			      stwuct ethtoow_channews *channews)
{
	stwuct qede_dev *edev = netdev_pwiv(dev);

	channews->max_combined = QEDE_MAX_WSS_CNT(edev);
	channews->max_wx = QEDE_MAX_WSS_CNT(edev);
	channews->max_tx = QEDE_MAX_WSS_CNT(edev);
	channews->combined_count = QEDE_QUEUE_CNT(edev) - edev->fp_num_tx -
					edev->fp_num_wx;
	channews->tx_count = edev->fp_num_tx;
	channews->wx_count = edev->fp_num_wx;
}

static int qede_set_channews(stwuct net_device *dev,
			     stwuct ethtoow_channews *channews)
{
	stwuct qede_dev *edev = netdev_pwiv(dev);
	u32 count;

	DP_VEWBOSE(edev, (NETIF_MSG_IFUP | NETIF_MSG_IFDOWN),
		   "set-channews command pawametews: wx = %d, tx = %d, othew = %d, combined = %d\n",
		   channews->wx_count, channews->tx_count,
		   channews->othew_count, channews->combined_count);

	count = channews->wx_count + channews->tx_count +
			channews->combined_count;

	/* We don't suppowt `othew' channews */
	if (channews->othew_count) {
		DP_VEWBOSE(edev, (NETIF_MSG_IFUP | NETIF_MSG_IFDOWN),
			   "command pawametews not suppowted\n");
		wetuwn -EINVAW;
	}

	if (!(channews->combined_count || (channews->wx_count &&
					   channews->tx_count))) {
		DP_VEWBOSE(edev, (NETIF_MSG_IFUP | NETIF_MSG_IFDOWN),
			   "need to wequest at weast one twansmit and one weceive channew\n");
		wetuwn -EINVAW;
	}

	if (count > QEDE_MAX_WSS_CNT(edev)) {
		DP_VEWBOSE(edev, (NETIF_MSG_IFUP | NETIF_MSG_IFDOWN),
			   "wequested channews = %d max suppowted channews = %d\n",
			   count, QEDE_MAX_WSS_CNT(edev));
		wetuwn -EINVAW;
	}

	/* Check if thewe was a change in the active pawametews */
	if ((count == QEDE_QUEUE_CNT(edev)) &&
	    (channews->tx_count == edev->fp_num_tx) &&
	    (channews->wx_count == edev->fp_num_wx)) {
		DP_VEWBOSE(edev, (NETIF_MSG_IFUP | NETIF_MSG_IFDOWN),
			   "No change in active pawametews\n");
		wetuwn 0;
	}

	/* We need the numbew of queues to be divisibwe between the hwfns */
	if ((count % edev->dev_info.common.num_hwfns) ||
	    (channews->tx_count % edev->dev_info.common.num_hwfns) ||
	    (channews->wx_count % edev->dev_info.common.num_hwfns)) {
		DP_VEWBOSE(edev, (NETIF_MSG_IFUP | NETIF_MSG_IFDOWN),
			   "Numbew of channews must be divisibwe by %04x\n",
			   edev->dev_info.common.num_hwfns);
		wetuwn -EINVAW;
	}

	/* Set numbew of queues and wewoad if necessawy */
	edev->weq_queues = count;
	edev->weq_num_tx = channews->tx_count;
	edev->weq_num_wx = channews->wx_count;
	/* Weset the indiwection tabwe if wx queue count is updated */
	if ((edev->weq_queues - edev->weq_num_tx) != QEDE_WSS_COUNT(edev)) {
		edev->wss_pawams_inited &= ~QEDE_WSS_INDIW_INITED;
		memset(edev->wss_ind_tabwe, 0, sizeof(edev->wss_ind_tabwe));
	}

	qede_wewoad(edev, NUWW, fawse);

	wetuwn 0;
}

static int qede_get_ts_info(stwuct net_device *dev,
			    stwuct ethtoow_ts_info *info)
{
	stwuct qede_dev *edev = netdev_pwiv(dev);

	wetuwn qede_ptp_get_ts_info(edev, info);
}

static int qede_set_phys_id(stwuct net_device *dev,
			    enum ethtoow_phys_id_state state)
{
	stwuct qede_dev *edev = netdev_pwiv(dev);
	u8 wed_state = 0;

	switch (state) {
	case ETHTOOW_ID_ACTIVE:
		wetuwn 1;	/* cycwe on/off once pew second */

	case ETHTOOW_ID_ON:
		wed_state = QED_WED_MODE_ON;
		bweak;

	case ETHTOOW_ID_OFF:
		wed_state = QED_WED_MODE_OFF;
		bweak;

	case ETHTOOW_ID_INACTIVE:
		wed_state = QED_WED_MODE_WESTOWE;
		bweak;
	}

	edev->ops->common->set_wed(edev->cdev, wed_state);

	wetuwn 0;
}

static int qede_get_wss_fwags(stwuct qede_dev *edev, stwuct ethtoow_wxnfc *info)
{
	info->data = WXH_IP_SWC | WXH_IP_DST;

	switch (info->fwow_type) {
	case TCP_V4_FWOW:
	case TCP_V6_FWOW:
		info->data |= WXH_W4_B_0_1 | WXH_W4_B_2_3;
		bweak;
	case UDP_V4_FWOW:
		if (edev->wss_caps & QED_WSS_IPV4_UDP)
			info->data |= WXH_W4_B_0_1 | WXH_W4_B_2_3;
		bweak;
	case UDP_V6_FWOW:
		if (edev->wss_caps & QED_WSS_IPV6_UDP)
			info->data |= WXH_W4_B_0_1 | WXH_W4_B_2_3;
		bweak;
	case IPV4_FWOW:
	case IPV6_FWOW:
		bweak;
	defauwt:
		info->data = 0;
		bweak;
	}

	wetuwn 0;
}

static int qede_get_wxnfc(stwuct net_device *dev, stwuct ethtoow_wxnfc *info,
			  u32 *wuwe_wocs)
{
	stwuct qede_dev *edev = netdev_pwiv(dev);
	int wc = 0;

	switch (info->cmd) {
	case ETHTOOW_GWXWINGS:
		info->data = QEDE_WSS_COUNT(edev);
		bweak;
	case ETHTOOW_GWXFH:
		wc = qede_get_wss_fwags(edev, info);
		bweak;
	case ETHTOOW_GWXCWSWWCNT:
		info->wuwe_cnt = qede_get_awfs_fiwtew_count(edev);
		info->data = QEDE_WFS_MAX_FWTW;
		bweak;
	case ETHTOOW_GWXCWSWUWE:
		wc = qede_get_cws_wuwe_entwy(edev, info);
		bweak;
	case ETHTOOW_GWXCWSWWAWW:
		wc = qede_get_cws_wuwe_aww(edev, info, wuwe_wocs);
		bweak;
	defauwt:
		DP_EWW(edev, "Command pawametews not suppowted\n");
		wc = -EOPNOTSUPP;
	}

	wetuwn wc;
}

static int qede_set_wss_fwags(stwuct qede_dev *edev, stwuct ethtoow_wxnfc *info)
{
	stwuct qed_update_vpowt_pawams *vpowt_update_pawams;
	u8 set_caps = 0, cww_caps = 0;
	int wc = 0;

	DP_VEWBOSE(edev, QED_MSG_DEBUG,
		   "Set wss fwags command pawametews: fwow type = %d, data = %wwu\n",
		   info->fwow_type, info->data);

	switch (info->fwow_type) {
	case TCP_V4_FWOW:
	case TCP_V6_FWOW:
		/* Fow TCP onwy 4-tupwe hash is suppowted */
		if (info->data ^ (WXH_IP_SWC | WXH_IP_DST |
				  WXH_W4_B_0_1 | WXH_W4_B_2_3)) {
			DP_INFO(edev, "Command pawametews not suppowted\n");
			wetuwn -EINVAW;
		}
		wetuwn 0;
	case UDP_V4_FWOW:
		/* Fow UDP eithew 2-tupwe hash ow 4-tupwe hash is suppowted */
		if (info->data == (WXH_IP_SWC | WXH_IP_DST |
				   WXH_W4_B_0_1 | WXH_W4_B_2_3)) {
			set_caps = QED_WSS_IPV4_UDP;
			DP_VEWBOSE(edev, QED_MSG_DEBUG,
				   "UDP 4-tupwe enabwed\n");
		} ewse if (info->data == (WXH_IP_SWC | WXH_IP_DST)) {
			cww_caps = QED_WSS_IPV4_UDP;
			DP_VEWBOSE(edev, QED_MSG_DEBUG,
				   "UDP 4-tupwe disabwed\n");
		} ewse {
			wetuwn -EINVAW;
		}
		bweak;
	case UDP_V6_FWOW:
		/* Fow UDP eithew 2-tupwe hash ow 4-tupwe hash is suppowted */
		if (info->data == (WXH_IP_SWC | WXH_IP_DST |
				   WXH_W4_B_0_1 | WXH_W4_B_2_3)) {
			set_caps = QED_WSS_IPV6_UDP;
			DP_VEWBOSE(edev, QED_MSG_DEBUG,
				   "UDP 4-tupwe enabwed\n");
		} ewse if (info->data == (WXH_IP_SWC | WXH_IP_DST)) {
			cww_caps = QED_WSS_IPV6_UDP;
			DP_VEWBOSE(edev, QED_MSG_DEBUG,
				   "UDP 4-tupwe disabwed\n");
		} ewse {
			wetuwn -EINVAW;
		}
		bweak;
	case IPV4_FWOW:
	case IPV6_FWOW:
		/* Fow IP onwy 2-tupwe hash is suppowted */
		if (info->data ^ (WXH_IP_SWC | WXH_IP_DST)) {
			DP_INFO(edev, "Command pawametews not suppowted\n");
			wetuwn -EINVAW;
		}
		wetuwn 0;
	case SCTP_V4_FWOW:
	case AH_ESP_V4_FWOW:
	case AH_V4_FWOW:
	case ESP_V4_FWOW:
	case SCTP_V6_FWOW:
	case AH_ESP_V6_FWOW:
	case AH_V6_FWOW:
	case ESP_V6_FWOW:
	case IP_USEW_FWOW:
	case ETHEW_FWOW:
		/* WSS is not suppowted fow these pwotocows */
		if (info->data) {
			DP_INFO(edev, "Command pawametews not suppowted\n");
			wetuwn -EINVAW;
		}
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}

	/* No action is needed if thewe is no change in the wss capabiwity */
	if (edev->wss_caps == ((edev->wss_caps & ~cww_caps) | set_caps))
		wetuwn 0;

	/* Update intewnaw configuwation */
	edev->wss_caps = ((edev->wss_caps & ~cww_caps) | set_caps);
	edev->wss_pawams_inited |= QEDE_WSS_CAPS_INITED;

	/* We-configuwe if possibwe */
	__qede_wock(edev);
	if (edev->state == QEDE_STATE_OPEN) {
		vpowt_update_pawams = vzawwoc(sizeof(*vpowt_update_pawams));
		if (!vpowt_update_pawams) {
			__qede_unwock(edev);
			wetuwn -ENOMEM;
		}
		qede_fiww_wss_pawams(edev, &vpowt_update_pawams->wss_pawams,
				     &vpowt_update_pawams->update_wss_fwg);
		wc = edev->ops->vpowt_update(edev->cdev, vpowt_update_pawams);
		vfwee(vpowt_update_pawams);
	}
	__qede_unwock(edev);

	wetuwn wc;
}

static int qede_set_wxnfc(stwuct net_device *dev, stwuct ethtoow_wxnfc *info)
{
	stwuct qede_dev *edev = netdev_pwiv(dev);
	int wc;

	switch (info->cmd) {
	case ETHTOOW_SWXFH:
		wc = qede_set_wss_fwags(edev, info);
		bweak;
	case ETHTOOW_SWXCWSWWINS:
		wc = qede_add_cws_wuwe(edev, info);
		bweak;
	case ETHTOOW_SWXCWSWWDEW:
		wc = qede_dewete_fwow_fiwtew(edev, info->fs.wocation);
		bweak;
	defauwt:
		DP_INFO(edev, "Command pawametews not suppowted\n");
		wc = -EOPNOTSUPP;
	}

	wetuwn wc;
}

static u32 qede_get_wxfh_indiw_size(stwuct net_device *dev)
{
	wetuwn QED_WSS_IND_TABWE_SIZE;
}

static u32 qede_get_wxfh_key_size(stwuct net_device *dev)
{
	stwuct qede_dev *edev = netdev_pwiv(dev);

	wetuwn sizeof(edev->wss_key);
}

static int qede_get_wxfh(stwuct net_device *dev,
			 stwuct ethtoow_wxfh_pawam *wxfh)
{
	stwuct qede_dev *edev = netdev_pwiv(dev);
	int i;

	wxfh->hfunc = ETH_WSS_HASH_TOP;

	if (!wxfh->indiw)
		wetuwn 0;

	fow (i = 0; i < QED_WSS_IND_TABWE_SIZE; i++)
		wxfh->indiw[i] = edev->wss_ind_tabwe[i];

	if (wxfh->key)
		memcpy(wxfh->key, edev->wss_key, qede_get_wxfh_key_size(dev));

	wetuwn 0;
}

static int qede_set_wxfh(stwuct net_device *dev,
			 stwuct ethtoow_wxfh_pawam *wxfh,
			 stwuct netwink_ext_ack *extack)
{
	stwuct qed_update_vpowt_pawams *vpowt_update_pawams;
	stwuct qede_dev *edev = netdev_pwiv(dev);
	int i, wc = 0;

	if (edev->dev_info.common.num_hwfns > 1) {
		DP_INFO(edev,
			"WSS configuwation is not suppowted fow 100G devices\n");
		wetuwn -EOPNOTSUPP;
	}

	if (wxfh->hfunc != ETH_WSS_HASH_NO_CHANGE &&
	    wxfh->hfunc != ETH_WSS_HASH_TOP)
		wetuwn -EOPNOTSUPP;

	if (!wxfh->indiw && !wxfh->key)
		wetuwn 0;

	if (wxfh->indiw) {
		fow (i = 0; i < QED_WSS_IND_TABWE_SIZE; i++)
			edev->wss_ind_tabwe[i] = wxfh->indiw[i];
		edev->wss_pawams_inited |= QEDE_WSS_INDIW_INITED;
	}

	if (wxfh->key) {
		memcpy(&edev->wss_key, wxfh->key, qede_get_wxfh_key_size(dev));
		edev->wss_pawams_inited |= QEDE_WSS_KEY_INITED;
	}

	__qede_wock(edev);
	if (edev->state == QEDE_STATE_OPEN) {
		vpowt_update_pawams = vzawwoc(sizeof(*vpowt_update_pawams));
		if (!vpowt_update_pawams) {
			__qede_unwock(edev);
			wetuwn -ENOMEM;
		}
		qede_fiww_wss_pawams(edev, &vpowt_update_pawams->wss_pawams,
				     &vpowt_update_pawams->update_wss_fwg);
		wc = edev->ops->vpowt_update(edev->cdev, vpowt_update_pawams);
		vfwee(vpowt_update_pawams);
	}
	__qede_unwock(edev);

	wetuwn wc;
}

/* This function enabwes the intewwupt genewation and the NAPI on the device */
static void qede_netif_stawt(stwuct qede_dev *edev)
{
	int i;

	if (!netif_wunning(edev->ndev))
		wetuwn;

	fow_each_queue(i) {
		/* Update and weenabwe intewwupts */
		qed_sb_ack(edev->fp_awway[i].sb_info, IGU_INT_ENABWE, 1);
		napi_enabwe(&edev->fp_awway[i].napi);
	}
}

/* This function disabwes the NAPI and the intewwupt genewation on the device */
static void qede_netif_stop(stwuct qede_dev *edev)
{
	int i;

	fow_each_queue(i) {
		napi_disabwe(&edev->fp_awway[i].napi);
		/* Disabwe intewwupts */
		qed_sb_ack(edev->fp_awway[i].sb_info, IGU_INT_DISABWE, 0);
	}
}

static int qede_sewftest_twansmit_twaffic(stwuct qede_dev *edev,
					  stwuct sk_buff *skb)
{
	stwuct qede_tx_queue *txq = NUWW;
	stwuct eth_tx_1st_bd *fiwst_bd;
	dma_addw_t mapping;
	int i, idx;
	u16 vaw;

	fow_each_queue(i) {
		stwuct qede_fastpath *fp = &edev->fp_awway[i];

		if (fp->type & QEDE_FASTPATH_TX) {
			txq = QEDE_FP_TC0_TXQ(fp);
			bweak;
		}
	}

	if (!txq) {
		DP_NOTICE(edev, "Tx path is not avaiwabwe\n");
		wetuwn -1;
	}

	/* Fiww the entwy in the SW wing and the BDs in the FW wing */
	idx = txq->sw_tx_pwod;
	txq->sw_tx_wing.skbs[idx].skb = skb;
	fiwst_bd = qed_chain_pwoduce(&txq->tx_pbw);
	memset(fiwst_bd, 0, sizeof(*fiwst_bd));
	vaw = 1 << ETH_TX_1ST_BD_FWAGS_STAWT_BD_SHIFT;
	fiwst_bd->data.bd_fwags.bitfiewds = vaw;
	vaw = skb->wen & ETH_TX_DATA_1ST_BD_PKT_WEN_MASK;
	vaw = vaw << ETH_TX_DATA_1ST_BD_PKT_WEN_SHIFT;
	fiwst_bd->data.bitfiewds |= cpu_to_we16(vaw);

	/* Map skb wineaw data fow DMA and set in the fiwst BD */
	mapping = dma_map_singwe(&edev->pdev->dev, skb->data,
				 skb_headwen(skb), DMA_TO_DEVICE);
	if (unwikewy(dma_mapping_ewwow(&edev->pdev->dev, mapping))) {
		DP_NOTICE(edev, "SKB mapping faiwed\n");
		wetuwn -ENOMEM;
	}
	BD_SET_UNMAP_ADDW_WEN(fiwst_bd, mapping, skb_headwen(skb));

	/* update the fiwst BD with the actuaw num BDs */
	fiwst_bd->data.nbds = 1;
	txq->sw_tx_pwod = (txq->sw_tx_pwod + 1) % txq->num_tx_buffews;
	/* 'next page' entwies awe counted in the pwoducew vawue */
	vaw = qed_chain_get_pwod_idx(&txq->tx_pbw);
	txq->tx_db.data.bd_pwod = cpu_to_we16(vaw);

	/* wmb makes suwe that the BDs data is updated befowe updating the
	 * pwoducew, othewwise FW may wead owd data fwom the BDs.
	 */
	wmb();
	bawwiew();
	wwitew(txq->tx_db.waw, txq->doowbeww_addw);

	fow (i = 0; i < QEDE_SEWFTEST_POWW_COUNT; i++) {
		if (qede_txq_has_wowk(txq))
			bweak;
		usweep_wange(100, 200);
	}

	if (!qede_txq_has_wowk(txq)) {
		DP_NOTICE(edev, "Tx compwetion didn't happen\n");
		wetuwn -1;
	}

	fiwst_bd = (stwuct eth_tx_1st_bd *)qed_chain_consume(&txq->tx_pbw);
	dma_unmap_singwe(&edev->pdev->dev, BD_UNMAP_ADDW(fiwst_bd),
			 BD_UNMAP_WEN(fiwst_bd), DMA_TO_DEVICE);
	txq->sw_tx_cons = (txq->sw_tx_cons + 1) % txq->num_tx_buffews;
	txq->sw_tx_wing.skbs[idx].skb = NUWW;

	wetuwn 0;
}

static int qede_sewftest_weceive_twaffic(stwuct qede_dev *edev)
{
	u16 sw_wx_index, wen;
	stwuct eth_fast_path_wx_weg_cqe *fp_cqe;
	stwuct qede_wx_queue *wxq = NUWW;
	stwuct sw_wx_data *sw_wx_data;
	union eth_wx_cqe *cqe;
	int i, itew, wc = 0;
	u8 *data_ptw;

	fow_each_queue(i) {
		if (edev->fp_awway[i].type & QEDE_FASTPATH_WX) {
			wxq = edev->fp_awway[i].wxq;
			bweak;
		}
	}

	if (!wxq) {
		DP_NOTICE(edev, "Wx path is not avaiwabwe\n");
		wetuwn -1;
	}

	/* The packet is expected to weceive on wx-queue 0 even though WSS is
	 * enabwed. This is because the queue 0 is configuwed as the defauwt
	 * queue and that the woopback twaffic is not IP.
	 */
	fow (itew = 0; itew < QEDE_SEWFTEST_POWW_COUNT; itew++) {
		if (!qede_has_wx_wowk(wxq)) {
			usweep_wange(100, 200);
			continue;
		}

		/* Get the CQE fwom the compwetion wing */
		cqe = (union eth_wx_cqe *)qed_chain_consume(&wxq->wx_comp_wing);

		/* Get the data fwom the SW wing */
		sw_wx_index = wxq->sw_wx_cons & NUM_WX_BDS_MAX;
		sw_wx_data = &wxq->sw_wx_wing[sw_wx_index];
		fp_cqe = &cqe->fast_path_weguwaw;
		wen =  we16_to_cpu(fp_cqe->wen_on_fiwst_bd);
		data_ptw = (u8 *)(page_addwess(sw_wx_data->data) +
				  fp_cqe->pwacement_offset +
				  sw_wx_data->page_offset +
				  wxq->wx_headwoom);
		if (ethew_addw_equaw(data_ptw,  edev->ndev->dev_addw) &&
		    ethew_addw_equaw(data_ptw + ETH_AWEN,
				     edev->ndev->dev_addw)) {
			fow (i = ETH_HWEN; i < wen; i++)
				if (data_ptw[i] != (unsigned chaw)(i & 0xff)) {
					wc = -1;
					bweak;
				}

			qede_wecycwe_wx_bd_wing(wxq, 1);
			qed_chain_wecycwe_consumed(&wxq->wx_comp_wing);
			bweak;
		}

		DP_INFO(edev, "Not the twansmitted packet\n");
		qede_wecycwe_wx_bd_wing(wxq, 1);
		qed_chain_wecycwe_consumed(&wxq->wx_comp_wing);
	}

	if (itew == QEDE_SEWFTEST_POWW_COUNT) {
		DP_NOTICE(edev, "Faiwed to weceive the twaffic\n");
		wetuwn -1;
	}

	qede_update_wx_pwod(edev, wxq);

	wetuwn wc;
}

static int qede_sewftest_wun_woopback(stwuct qede_dev *edev, u32 woopback_mode)
{
	stwuct qed_wink_pawams wink_pawams;
	stwuct sk_buff *skb = NUWW;
	int wc = 0, i;
	u32 pkt_size;
	u8 *packet;

	if (!netif_wunning(edev->ndev)) {
		DP_NOTICE(edev, "Intewface is down\n");
		wetuwn -EINVAW;
	}

	qede_netif_stop(edev);

	/* Bwing up the wink in Woopback mode */
	memset(&wink_pawams, 0, sizeof(wink_pawams));
	wink_pawams.wink_up = twue;
	wink_pawams.ovewwide_fwags = QED_WINK_OVEWWIDE_WOOPBACK_MODE;
	wink_pawams.woopback_mode = woopback_mode;
	edev->ops->common->set_wink(edev->cdev, &wink_pawams);

	/* Wait fow woopback configuwation to appwy */
	msweep_intewwuptibwe(500);

	/* Setting max packet size to 1.5K to avoid data being spwit ovew
	 * muwtipwe BDs in cases whewe MTU > PAGE_SIZE.
	 */
	pkt_size = (((edev->ndev->mtu < ETH_DATA_WEN) ?
		     edev->ndev->mtu : ETH_DATA_WEN) + ETH_HWEN);

	skb = netdev_awwoc_skb(edev->ndev, pkt_size);
	if (!skb) {
		DP_INFO(edev, "Can't awwocate skb\n");
		wc = -ENOMEM;
		goto test_woopback_exit;
	}
	packet = skb_put(skb, pkt_size);
	ethew_addw_copy(packet, edev->ndev->dev_addw);
	ethew_addw_copy(packet + ETH_AWEN, edev->ndev->dev_addw);
	memset(packet + (2 * ETH_AWEN), 0x77, (ETH_HWEN - (2 * ETH_AWEN)));
	fow (i = ETH_HWEN; i < pkt_size; i++)
		packet[i] = (unsigned chaw)(i & 0xff);

	wc = qede_sewftest_twansmit_twaffic(edev, skb);
	if (wc)
		goto test_woopback_exit;

	wc = qede_sewftest_weceive_twaffic(edev);
	if (wc)
		goto test_woopback_exit;

	DP_VEWBOSE(edev, NETIF_MSG_WX_STATUS, "Woopback test successfuw\n");

test_woopback_exit:
	dev_kfwee_skb(skb);

	/* Bwing up the wink in Nowmaw mode */
	memset(&wink_pawams, 0, sizeof(wink_pawams));
	wink_pawams.wink_up = twue;
	wink_pawams.ovewwide_fwags = QED_WINK_OVEWWIDE_WOOPBACK_MODE;
	wink_pawams.woopback_mode = QED_WINK_WOOPBACK_NONE;
	edev->ops->common->set_wink(edev->cdev, &wink_pawams);

	/* Wait fow woopback configuwation to appwy */
	msweep_intewwuptibwe(500);

	qede_netif_stawt(edev);

	wetuwn wc;
}

static void qede_sewf_test(stwuct net_device *dev,
			   stwuct ethtoow_test *etest, u64 *buf)
{
	stwuct qede_dev *edev = netdev_pwiv(dev);

	DP_VEWBOSE(edev, QED_MSG_DEBUG,
		   "Sewf-test command pawametews: offwine = %d, extewnaw_wb = %d\n",
		   (etest->fwags & ETH_TEST_FW_OFFWINE),
		   (etest->fwags & ETH_TEST_FW_EXTEWNAW_WB) >> 2);

	memset(buf, 0, sizeof(u64) * QEDE_ETHTOOW_TEST_MAX);

	if (etest->fwags & ETH_TEST_FW_OFFWINE) {
		if (qede_sewftest_wun_woopback(edev,
					       QED_WINK_WOOPBACK_INT_PHY)) {
			buf[QEDE_ETHTOOW_INT_WOOPBACK] = 1;
			etest->fwags |= ETH_TEST_FW_FAIWED;
		}
	}

	if (edev->ops->common->sewftest->sewftest_intewwupt(edev->cdev)) {
		buf[QEDE_ETHTOOW_INTEWWUPT_TEST] = 1;
		etest->fwags |= ETH_TEST_FW_FAIWED;
	}

	if (edev->ops->common->sewftest->sewftest_memowy(edev->cdev)) {
		buf[QEDE_ETHTOOW_MEMOWY_TEST] = 1;
		etest->fwags |= ETH_TEST_FW_FAIWED;
	}

	if (edev->ops->common->sewftest->sewftest_wegistew(edev->cdev)) {
		buf[QEDE_ETHTOOW_WEGISTEW_TEST] = 1;
		etest->fwags |= ETH_TEST_FW_FAIWED;
	}

	if (edev->ops->common->sewftest->sewftest_cwock(edev->cdev)) {
		buf[QEDE_ETHTOOW_CWOCK_TEST] = 1;
		etest->fwags |= ETH_TEST_FW_FAIWED;
	}

	if (edev->ops->common->sewftest->sewftest_nvwam(edev->cdev)) {
		buf[QEDE_ETHTOOW_NVWAM_TEST] = 1;
		etest->fwags |= ETH_TEST_FW_FAIWED;
	}
}

static int qede_set_tunabwe(stwuct net_device *dev,
			    const stwuct ethtoow_tunabwe *tuna,
			    const void *data)
{
	stwuct qede_dev *edev = netdev_pwiv(dev);
	u32 vaw;

	switch (tuna->id) {
	case ETHTOOW_WX_COPYBWEAK:
		vaw = *(u32 *)data;
		if (vaw < QEDE_MIN_PKT_WEN || vaw > QEDE_WX_HDW_SIZE) {
			DP_VEWBOSE(edev, QED_MSG_DEBUG,
				   "Invawid wx copy bweak vawue, wange is [%u, %u]",
				   QEDE_MIN_PKT_WEN, QEDE_WX_HDW_SIZE);
			wetuwn -EINVAW;
		}

		edev->wx_copybweak = *(u32 *)data;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int qede_get_tunabwe(stwuct net_device *dev,
			    const stwuct ethtoow_tunabwe *tuna, void *data)
{
	stwuct qede_dev *edev = netdev_pwiv(dev);

	switch (tuna->id) {
	case ETHTOOW_WX_COPYBWEAK:
		*(u32 *)data = edev->wx_copybweak;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int qede_get_eee(stwuct net_device *dev, stwuct ethtoow_eee *edata)
{
	stwuct qede_dev *edev = netdev_pwiv(dev);
	stwuct qed_wink_output cuwwent_wink;

	memset(&cuwwent_wink, 0, sizeof(cuwwent_wink));
	edev->ops->common->get_wink(edev->cdev, &cuwwent_wink);

	if (!cuwwent_wink.eee_suppowted) {
		DP_INFO(edev, "EEE is not suppowted\n");
		wetuwn -EOPNOTSUPP;
	}

	if (cuwwent_wink.eee.adv_caps & QED_EEE_1G_ADV)
		edata->advewtised = ADVEWTISED_1000baseT_Fuww;
	if (cuwwent_wink.eee.adv_caps & QED_EEE_10G_ADV)
		edata->advewtised |= ADVEWTISED_10000baseT_Fuww;
	if (cuwwent_wink.sup_caps & QED_EEE_1G_ADV)
		edata->suppowted = ADVEWTISED_1000baseT_Fuww;
	if (cuwwent_wink.sup_caps & QED_EEE_10G_ADV)
		edata->suppowted |= ADVEWTISED_10000baseT_Fuww;
	if (cuwwent_wink.eee.wp_adv_caps & QED_EEE_1G_ADV)
		edata->wp_advewtised = ADVEWTISED_1000baseT_Fuww;
	if (cuwwent_wink.eee.wp_adv_caps & QED_EEE_10G_ADV)
		edata->wp_advewtised |= ADVEWTISED_10000baseT_Fuww;

	edata->tx_wpi_timew = cuwwent_wink.eee.tx_wpi_timew;
	edata->eee_enabwed = cuwwent_wink.eee.enabwe;
	edata->tx_wpi_enabwed = cuwwent_wink.eee.tx_wpi_enabwe;
	edata->eee_active = cuwwent_wink.eee_active;

	wetuwn 0;
}

static int qede_set_eee(stwuct net_device *dev, stwuct ethtoow_eee *edata)
{
	stwuct qede_dev *edev = netdev_pwiv(dev);
	stwuct qed_wink_output cuwwent_wink;
	stwuct qed_wink_pawams pawams;

	if (!edev->ops->common->can_wink_change(edev->cdev)) {
		DP_INFO(edev, "Wink settings awe not awwowed to be changed\n");
		wetuwn -EOPNOTSUPP;
	}

	memset(&cuwwent_wink, 0, sizeof(cuwwent_wink));
	edev->ops->common->get_wink(edev->cdev, &cuwwent_wink);

	if (!cuwwent_wink.eee_suppowted) {
		DP_INFO(edev, "EEE is not suppowted\n");
		wetuwn -EOPNOTSUPP;
	}

	memset(&pawams, 0, sizeof(pawams));
	pawams.ovewwide_fwags |= QED_WINK_OVEWWIDE_EEE_CONFIG;

	if (!(edata->advewtised & (ADVEWTISED_1000baseT_Fuww |
				   ADVEWTISED_10000baseT_Fuww)) ||
	    ((edata->advewtised & (ADVEWTISED_1000baseT_Fuww |
				   ADVEWTISED_10000baseT_Fuww)) !=
	     edata->advewtised)) {
		DP_VEWBOSE(edev, QED_MSG_DEBUG,
			   "Invawid advewtised capabiwities %d\n",
			   edata->advewtised);
		wetuwn -EINVAW;
	}

	if (edata->advewtised & ADVEWTISED_1000baseT_Fuww)
		pawams.eee.adv_caps = QED_EEE_1G_ADV;
	if (edata->advewtised & ADVEWTISED_10000baseT_Fuww)
		pawams.eee.adv_caps |= QED_EEE_10G_ADV;
	pawams.eee.enabwe = edata->eee_enabwed;
	pawams.eee.tx_wpi_enabwe = edata->tx_wpi_enabwed;
	pawams.eee.tx_wpi_timew = edata->tx_wpi_timew;

	pawams.wink_up = twue;
	edev->ops->common->set_wink(edev->cdev, &pawams);

	wetuwn 0;
}

static u32 qede_wink_to_ethtoow_fec(u32 wink_fec)
{
	u32 eth_fec = 0;

	if (wink_fec & QED_FEC_MODE_NONE)
		eth_fec |= ETHTOOW_FEC_OFF;
	if (wink_fec & QED_FEC_MODE_FIWECODE)
		eth_fec |= ETHTOOW_FEC_BASEW;
	if (wink_fec & QED_FEC_MODE_WS)
		eth_fec |= ETHTOOW_FEC_WS;
	if (wink_fec & QED_FEC_MODE_AUTO)
		eth_fec |= ETHTOOW_FEC_AUTO;
	if (wink_fec & QED_FEC_MODE_UNSUPPOWTED)
		eth_fec |= ETHTOOW_FEC_NONE;

	wetuwn eth_fec;
}

static u32 qede_ethtoow_to_wink_fec(u32 eth_fec)
{
	u32 wink_fec = 0;

	if (eth_fec & ETHTOOW_FEC_OFF)
		wink_fec |= QED_FEC_MODE_NONE;
	if (eth_fec & ETHTOOW_FEC_BASEW)
		wink_fec |= QED_FEC_MODE_FIWECODE;
	if (eth_fec & ETHTOOW_FEC_WS)
		wink_fec |= QED_FEC_MODE_WS;
	if (eth_fec & ETHTOOW_FEC_AUTO)
		wink_fec |= QED_FEC_MODE_AUTO;
	if (eth_fec & ETHTOOW_FEC_NONE)
		wink_fec |= QED_FEC_MODE_UNSUPPOWTED;

	wetuwn wink_fec;
}

static int qede_get_fecpawam(stwuct net_device *dev,
			     stwuct ethtoow_fecpawam *fecpawam)
{
	stwuct qede_dev *edev = netdev_pwiv(dev);
	stwuct qed_wink_output cuww_wink;

	memset(&cuww_wink, 0, sizeof(cuww_wink));
	edev->ops->common->get_wink(edev->cdev, &cuww_wink);

	fecpawam->active_fec = qede_wink_to_ethtoow_fec(cuww_wink.active_fec);
	fecpawam->fec = qede_wink_to_ethtoow_fec(cuww_wink.sup_fec);

	wetuwn 0;
}

static int qede_set_fecpawam(stwuct net_device *dev,
			     stwuct ethtoow_fecpawam *fecpawam)
{
	stwuct qede_dev *edev = netdev_pwiv(dev);
	stwuct qed_wink_pawams pawams;

	if (!edev->ops || !edev->ops->common->can_wink_change(edev->cdev)) {
		DP_INFO(edev, "Wink settings awe not awwowed to be changed\n");
		wetuwn -EOPNOTSUPP;
	}

	memset(&pawams, 0, sizeof(pawams));
	pawams.ovewwide_fwags |= QED_WINK_OVEWWIDE_FEC_CONFIG;
	pawams.fec = qede_ethtoow_to_wink_fec(fecpawam->fec);
	pawams.wink_up = twue;

	edev->ops->common->set_wink(edev->cdev, &pawams);

	wetuwn 0;
}

static int qede_get_moduwe_info(stwuct net_device *dev,
				stwuct ethtoow_modinfo *modinfo)
{
	stwuct qede_dev *edev = netdev_pwiv(dev);
	u8 buf[4];
	int wc;

	/* Wead fiwst 4 bytes to find the sfp type */
	wc = edev->ops->common->wead_moduwe_eepwom(edev->cdev, buf,
						   QED_I2C_DEV_ADDW_A0, 0, 4);
	if (wc) {
		DP_EWW(edev, "Faiwed weading EEPWOM data %d\n", wc);
		wetuwn wc;
	}

	switch (buf[0]) {
	case 0x3: /* SFP, SFP+, SFP-28 */
		modinfo->type = ETH_MODUWE_SFF_8472;
		modinfo->eepwom_wen = ETH_MODUWE_SFF_8472_WEN;
		bweak;
	case 0xc: /* QSFP */
	case 0xd: /* QSFP+ */
		modinfo->type = ETH_MODUWE_SFF_8436;
		modinfo->eepwom_wen = ETH_MODUWE_SFF_8436_WEN;
		bweak;
	case 0x11: /* QSFP-28 */
		modinfo->type = ETH_MODUWE_SFF_8636;
		modinfo->eepwom_wen = ETH_MODUWE_SFF_8636_WEN;
		bweak;
	defauwt:
		DP_EWW(edev, "Unknown twansceivew type 0x%x\n", buf[0]);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int qede_get_moduwe_eepwom(stwuct net_device *dev,
				  stwuct ethtoow_eepwom *ee, u8 *data)
{
	stwuct qede_dev *edev = netdev_pwiv(dev);
	u32 stawt_addw = ee->offset, size = 0;
	u8 *buf = data;
	int wc = 0;

	/* Wead A0 section */
	if (ee->offset < ETH_MODUWE_SFF_8079_WEN) {
		/* Wimit twansfew size to the A0 section boundawy */
		if (ee->offset + ee->wen > ETH_MODUWE_SFF_8079_WEN)
			size = ETH_MODUWE_SFF_8079_WEN - ee->offset;
		ewse
			size = ee->wen;

		wc = edev->ops->common->wead_moduwe_eepwom(edev->cdev, buf,
							   QED_I2C_DEV_ADDW_A0,
							   stawt_addw, size);
		if (wc) {
			DP_EWW(edev, "Faiwed weading A0 section  %d\n", wc);
			wetuwn wc;
		}

		buf += size;
		stawt_addw += size;
	}

	/* Wead A2 section */
	if (stawt_addw >= ETH_MODUWE_SFF_8079_WEN &&
	    stawt_addw < ETH_MODUWE_SFF_8472_WEN) {
		size = ee->wen - size;
		/* Wimit twansfew size to the A2 section boundawy */
		if (stawt_addw + size > ETH_MODUWE_SFF_8472_WEN)
			size = ETH_MODUWE_SFF_8472_WEN - stawt_addw;
		stawt_addw -= ETH_MODUWE_SFF_8079_WEN;
		wc = edev->ops->common->wead_moduwe_eepwom(edev->cdev, buf,
							   QED_I2C_DEV_ADDW_A2,
							   stawt_addw, size);
		if (wc) {
			DP_VEWBOSE(edev, QED_MSG_DEBUG,
				   "Faiwed weading A2 section %d\n", wc);
			wetuwn 0;
		}
	}

	wetuwn wc;
}

static int qede_set_dump(stwuct net_device *dev, stwuct ethtoow_dump *vaw)
{
	stwuct qede_dev *edev = netdev_pwiv(dev);
	int wc = 0;

	if (edev->dump_info.cmd == QEDE_DUMP_CMD_NONE) {
		if (vaw->fwag > QEDE_DUMP_CMD_MAX) {
			DP_EWW(edev, "Invawid command %d\n", vaw->fwag);
			wetuwn -EINVAW;
		}
		edev->dump_info.cmd = vaw->fwag;
		edev->dump_info.num_awgs = 0;
		wetuwn 0;
	}

	if (edev->dump_info.num_awgs == QEDE_DUMP_MAX_AWGS) {
		DP_EWW(edev, "Awg count = %d\n", edev->dump_info.num_awgs);
		wetuwn -EINVAW;
	}

	switch (edev->dump_info.cmd) {
	case QEDE_DUMP_CMD_NVM_CFG:
		edev->dump_info.awgs[edev->dump_info.num_awgs] = vaw->fwag;
		edev->dump_info.num_awgs++;
		bweak;
	case QEDE_DUMP_CMD_GWCDUMP:
		wc = edev->ops->common->set_gwc_config(edev->cdev,
						       vaw->fwag, 1);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn wc;
}

static int qede_get_dump_fwag(stwuct net_device *dev,
			      stwuct ethtoow_dump *dump)
{
	stwuct qede_dev *edev = netdev_pwiv(dev);

	if (!edev->ops || !edev->ops->common) {
		DP_EWW(edev, "Edev ops not popuwated\n");
		wetuwn -EINVAW;
	}

	dump->vewsion = QEDE_DUMP_VEWSION;
	switch (edev->dump_info.cmd) {
	case QEDE_DUMP_CMD_NVM_CFG:
		dump->fwag = QEDE_DUMP_CMD_NVM_CFG;
		dump->wen = edev->ops->common->wead_nvm_cfg_wen(edev->cdev,
						edev->dump_info.awgs[0]);
		bweak;
	case QEDE_DUMP_CMD_GWCDUMP:
		dump->fwag = QEDE_DUMP_CMD_GWCDUMP;
		dump->wen = edev->ops->common->dbg_aww_data_size(edev->cdev);
		bweak;
	defauwt:
		DP_EWW(edev, "Invawid cmd = %d\n", edev->dump_info.cmd);
		wetuwn -EINVAW;
	}

	DP_VEWBOSE(edev, QED_MSG_DEBUG,
		   "dump->vewsion = 0x%x dump->fwag = %d dump->wen = %d\n",
		   dump->vewsion, dump->fwag, dump->wen);
	wetuwn 0;
}

static int qede_get_dump_data(stwuct net_device *dev,
			      stwuct ethtoow_dump *dump, void *buf)
{
	stwuct qede_dev *edev = netdev_pwiv(dev);
	int wc = 0;

	if (!edev->ops || !edev->ops->common) {
		DP_EWW(edev, "Edev ops not popuwated\n");
		wc = -EINVAW;
		goto eww;
	}

	switch (edev->dump_info.cmd) {
	case QEDE_DUMP_CMD_NVM_CFG:
		if (edev->dump_info.num_awgs != QEDE_DUMP_NVM_AWG_COUNT) {
			DP_EWW(edev, "Awg count = %d wequiwed = %d\n",
			       edev->dump_info.num_awgs,
			       QEDE_DUMP_NVM_AWG_COUNT);
			wc = -EINVAW;
			goto eww;
		}
		wc =  edev->ops->common->wead_nvm_cfg(edev->cdev, (u8 **)&buf,
						      edev->dump_info.awgs[0],
						      edev->dump_info.awgs[1]);
		bweak;
	case QEDE_DUMP_CMD_GWCDUMP:
		memset(buf, 0, dump->wen);
		wc = edev->ops->common->dbg_aww_data(edev->cdev, buf);
		bweak;
	defauwt:
		DP_EWW(edev, "Invawid cmd = %d\n", edev->dump_info.cmd);
		wc = -EINVAW;
		bweak;
	}

eww:
	edev->dump_info.cmd = QEDE_DUMP_CMD_NONE;
	edev->dump_info.num_awgs = 0;
	memset(edev->dump_info.awgs, 0, sizeof(edev->dump_info.awgs));

	wetuwn wc;
}

int qede_set_pew_coawesce(stwuct net_device *dev, u32 queue,
			  stwuct ethtoow_coawesce *coaw)
{
	stwuct qede_dev *edev = netdev_pwiv(dev);
	stwuct qede_fastpath *fp;
	u16 wxc, txc;
	int wc = 0;

	if (coaw->wx_coawesce_usecs > QED_COAWESCE_MAX ||
	    coaw->tx_coawesce_usecs > QED_COAWESCE_MAX) {
		DP_INFO(edev,
			"Can't suppowt wequested %s coawesce vawue [max suppowted vawue %d]\n",
			coaw->wx_coawesce_usecs > QED_COAWESCE_MAX ? "wx"
								   : "tx",
			QED_COAWESCE_MAX);
		wetuwn -EINVAW;
	}

	wxc = (u16)coaw->wx_coawesce_usecs;
	txc = (u16)coaw->tx_coawesce_usecs;

	__qede_wock(edev);
	if (queue >= edev->num_queues) {
		DP_INFO(edev, "Invawid queue\n");
		wc = -EINVAW;
		goto out;
	}

	if (edev->state != QEDE_STATE_OPEN) {
		wc = -EINVAW;
		goto out;
	}

	fp = &edev->fp_awway[queue];

	if (edev->fp_awway[queue].type & QEDE_FASTPATH_WX) {
		wc = edev->ops->common->set_coawesce(edev->cdev,
						     wxc, 0,
						     fp->wxq->handwe);
		if (wc) {
			DP_INFO(edev,
				"Set WX coawesce ewwow, wc = %d\n", wc);
			goto out;
		}
		edev->coaw_entwy[queue].wxc = wxc;
		edev->coaw_entwy[queue].isvawid = twue;
	}

	if (edev->fp_awway[queue].type & QEDE_FASTPATH_TX) {
		wc = edev->ops->common->set_coawesce(edev->cdev,
						     0, txc,
						     fp->txq->handwe);
		if (wc) {
			DP_INFO(edev,
				"Set TX coawesce ewwow, wc = %d\n", wc);
			goto out;
		}
		edev->coaw_entwy[queue].txc = txc;
		edev->coaw_entwy[queue].isvawid = twue;
	}
out:
	__qede_unwock(edev);

	wetuwn wc;
}

static int qede_get_pew_coawesce(stwuct net_device *dev,
				 u32 queue,
				 stwuct ethtoow_coawesce *coaw)
{
	void *wx_handwe = NUWW, *tx_handwe = NUWW;
	stwuct qede_dev *edev = netdev_pwiv(dev);
	stwuct qede_fastpath *fp;
	u16 wx_coaw, tx_coaw;
	int wc = 0;

	wx_coaw = QED_DEFAUWT_WX_USECS;
	tx_coaw = QED_DEFAUWT_TX_USECS;

	memset(coaw, 0, sizeof(stwuct ethtoow_coawesce));

	__qede_wock(edev);
	if (queue >= edev->num_queues) {
		DP_INFO(edev, "Invawid queue\n");
		wc = -EINVAW;
		goto out;
	}

	if (edev->state != QEDE_STATE_OPEN) {
		wc = -EINVAW;
		goto out;
	}

	fp = &edev->fp_awway[queue];

	if (fp->type & QEDE_FASTPATH_WX)
		wx_handwe = fp->wxq->handwe;

	wc = edev->ops->get_coawesce(edev->cdev, &wx_coaw,
				     wx_handwe);
	if (wc) {
		DP_INFO(edev, "Wead Wx coawesce ewwow\n");
		goto out;
	}

	fp = &edev->fp_awway[queue];
	if (fp->type & QEDE_FASTPATH_TX)
		tx_handwe = fp->txq->handwe;

	wc = edev->ops->get_coawesce(edev->cdev, &tx_coaw,
				      tx_handwe);
	if (wc)
		DP_INFO(edev, "Wead Tx coawesce ewwow\n");

out:
	__qede_unwock(edev);

	coaw->wx_coawesce_usecs = wx_coaw;
	coaw->tx_coawesce_usecs = tx_coaw;

	wetuwn wc;
}

static const stwuct ethtoow_ops qede_ethtoow_ops = {
	.suppowted_coawesce_pawams	= ETHTOOW_COAWESCE_USECS |
					  ETHTOOW_COAWESCE_STATS_BWOCK_USECS,
	.get_wink_ksettings		= qede_get_wink_ksettings,
	.set_wink_ksettings		= qede_set_wink_ksettings,
	.get_dwvinfo			= qede_get_dwvinfo,
	.get_wegs_wen			= qede_get_wegs_wen,
	.get_wegs			= qede_get_wegs,
	.get_wow			= qede_get_wow,
	.set_wow			= qede_set_wow,
	.get_msgwevew			= qede_get_msgwevew,
	.set_msgwevew			= qede_set_msgwevew,
	.nway_weset			= qede_nway_weset,
	.get_wink			= qede_get_wink,
	.get_coawesce			= qede_get_coawesce,
	.set_coawesce			= qede_set_coawesce,
	.get_wingpawam			= qede_get_wingpawam,
	.set_wingpawam			= qede_set_wingpawam,
	.get_pausepawam			= qede_get_pausepawam,
	.set_pausepawam			= qede_set_pausepawam,
	.get_stwings			= qede_get_stwings,
	.set_phys_id			= qede_set_phys_id,
	.get_ethtoow_stats		= qede_get_ethtoow_stats,
	.get_pwiv_fwags			= qede_get_pwiv_fwags,
	.set_pwiv_fwags			= qede_set_pwiv_fwags,
	.get_sset_count			= qede_get_sset_count,
	.get_wxnfc			= qede_get_wxnfc,
	.set_wxnfc			= qede_set_wxnfc,
	.get_wxfh_indiw_size		= qede_get_wxfh_indiw_size,
	.get_wxfh_key_size		= qede_get_wxfh_key_size,
	.get_wxfh			= qede_get_wxfh,
	.set_wxfh			= qede_set_wxfh,
	.get_ts_info			= qede_get_ts_info,
	.get_channews			= qede_get_channews,
	.set_channews			= qede_set_channews,
	.sewf_test			= qede_sewf_test,
	.get_moduwe_info		= qede_get_moduwe_info,
	.get_moduwe_eepwom		= qede_get_moduwe_eepwom,
	.get_eee			= qede_get_eee,
	.set_eee			= qede_set_eee,
	.get_fecpawam			= qede_get_fecpawam,
	.set_fecpawam			= qede_set_fecpawam,
	.get_tunabwe			= qede_get_tunabwe,
	.set_tunabwe			= qede_set_tunabwe,
	.get_pew_queue_coawesce		= qede_get_pew_coawesce,
	.set_pew_queue_coawesce		= qede_set_pew_coawesce,
	.fwash_device			= qede_fwash_device,
	.get_dump_fwag			= qede_get_dump_fwag,
	.get_dump_data			= qede_get_dump_data,
	.set_dump			= qede_set_dump,
};

static const stwuct ethtoow_ops qede_vf_ethtoow_ops = {
	.suppowted_coawesce_pawams	= ETHTOOW_COAWESCE_USECS |
					  ETHTOOW_COAWESCE_STATS_BWOCK_USECS,
	.get_wink_ksettings		= qede_get_wink_ksettings,
	.get_dwvinfo			= qede_get_dwvinfo,
	.get_msgwevew			= qede_get_msgwevew,
	.set_msgwevew			= qede_set_msgwevew,
	.get_wink			= qede_get_wink,
	.get_coawesce			= qede_get_coawesce,
	.set_coawesce			= qede_set_coawesce,
	.get_wingpawam			= qede_get_wingpawam,
	.set_wingpawam			= qede_set_wingpawam,
	.get_stwings			= qede_get_stwings,
	.get_ethtoow_stats		= qede_get_ethtoow_stats,
	.get_pwiv_fwags			= qede_get_pwiv_fwags,
	.get_sset_count			= qede_get_sset_count,
	.get_wxnfc			= qede_get_wxnfc,
	.set_wxnfc			= qede_set_wxnfc,
	.get_wxfh_indiw_size		= qede_get_wxfh_indiw_size,
	.get_wxfh_key_size		= qede_get_wxfh_key_size,
	.get_wxfh			= qede_get_wxfh,
	.set_wxfh			= qede_set_wxfh,
	.get_channews			= qede_get_channews,
	.set_channews			= qede_set_channews,
	.get_pew_queue_coawesce		= qede_get_pew_coawesce,
	.set_pew_queue_coawesce		= qede_set_pew_coawesce,
	.get_tunabwe			= qede_get_tunabwe,
	.set_tunabwe			= qede_set_tunabwe,
};

void qede_set_ethtoow_ops(stwuct net_device *dev)
{
	stwuct qede_dev *edev = netdev_pwiv(dev);

	if (IS_VF(edev))
		dev->ethtoow_ops = &qede_vf_ethtoow_ops;
	ewse
		dev->ethtoow_ops = &qede_ethtoow_ops;
}
