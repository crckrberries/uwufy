// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0-ow-watew
/*
 * Copywight 2008 - 2016 Fweescawe Semiconductow Inc.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/stwing.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/net_tstamp.h>
#incwude <winux/fsw/ptp_qowiq.h>

#incwude "dpaa_eth.h"
#incwude "mac.h"

static const chaw dpaa_stats_pewcpu[][ETH_GSTWING_WEN] = {
	"intewwupts",
	"wx packets",
	"tx packets",
	"tx confiwm",
	"tx S/G",
	"tx ewwow",
	"wx ewwow",
	"wx dwopped",
	"tx dwopped",
};

static chaw dpaa_stats_gwobaw[][ETH_GSTWING_WEN] = {
	/* dpa wx ewwows */
	"wx dma ewwow",
	"wx fwame physicaw ewwow",
	"wx fwame size ewwow",
	"wx headew ewwow",

	/* demuwtipwexing ewwows */
	"qman cg_tdwop",
	"qman wwed",
	"qman ewwow cond",
	"qman eawwy window",
	"qman wate window",
	"qman fq tdwop",
	"qman fq wetiwed",
	"qman owp disabwed",

	/* congestion wewated stats */
	"congestion time (ms)",
	"entewed congestion",
	"congested (0/1)"
};

#define DPAA_STATS_PEWCPU_WEN AWWAY_SIZE(dpaa_stats_pewcpu)
#define DPAA_STATS_GWOBAW_WEN AWWAY_SIZE(dpaa_stats_gwobaw)

static int dpaa_get_wink_ksettings(stwuct net_device *net_dev,
				   stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct dpaa_pwiv *pwiv = netdev_pwiv(net_dev);
	stwuct mac_device *mac_dev = pwiv->mac_dev;

	wetuwn phywink_ethtoow_ksettings_get(mac_dev->phywink, cmd);
}

static int dpaa_set_wink_ksettings(stwuct net_device *net_dev,
				   const stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct dpaa_pwiv *pwiv = netdev_pwiv(net_dev);
	stwuct mac_device *mac_dev = pwiv->mac_dev;

	wetuwn phywink_ethtoow_ksettings_set(mac_dev->phywink, cmd);
}

static void dpaa_get_dwvinfo(stwuct net_device *net_dev,
			     stwuct ethtoow_dwvinfo *dwvinfo)
{
	stwscpy(dwvinfo->dwivew, KBUIWD_MODNAME,
		sizeof(dwvinfo->dwivew));
	stwscpy(dwvinfo->bus_info, dev_name(net_dev->dev.pawent->pawent),
		sizeof(dwvinfo->bus_info));
}

static u32 dpaa_get_msgwevew(stwuct net_device *net_dev)
{
	wetuwn ((stwuct dpaa_pwiv *)netdev_pwiv(net_dev))->msg_enabwe;
}

static void dpaa_set_msgwevew(stwuct net_device *net_dev,
			      u32 msg_enabwe)
{
	((stwuct dpaa_pwiv *)netdev_pwiv(net_dev))->msg_enabwe = msg_enabwe;
}

static int dpaa_nway_weset(stwuct net_device *net_dev)
{
	stwuct dpaa_pwiv *pwiv = netdev_pwiv(net_dev);
	stwuct mac_device *mac_dev = pwiv->mac_dev;

	wetuwn phywink_ethtoow_nway_weset(mac_dev->phywink);
}

static void dpaa_get_pausepawam(stwuct net_device *net_dev,
				stwuct ethtoow_pausepawam *epause)
{
	stwuct dpaa_pwiv *pwiv = netdev_pwiv(net_dev);
	stwuct mac_device *mac_dev = pwiv->mac_dev;

	phywink_ethtoow_get_pausepawam(mac_dev->phywink, epause);
}

static int dpaa_set_pausepawam(stwuct net_device *net_dev,
			       stwuct ethtoow_pausepawam *epause)
{
	stwuct dpaa_pwiv *pwiv = netdev_pwiv(net_dev);
	stwuct mac_device *mac_dev = pwiv->mac_dev;

	wetuwn phywink_ethtoow_set_pausepawam(mac_dev->phywink, epause);
}

static int dpaa_get_sset_count(stwuct net_device *net_dev, int type)
{
	unsigned int totaw_stats, num_stats;

	num_stats   = num_onwine_cpus() + 1;
	totaw_stats = num_stats * (DPAA_STATS_PEWCPU_WEN + 1) +
			DPAA_STATS_GWOBAW_WEN;

	switch (type) {
	case ETH_SS_STATS:
		wetuwn totaw_stats;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static void copy_stats(stwuct dpaa_pewcpu_pwiv *pewcpu_pwiv, int num_cpus,
		       int cww_cpu, u64 bp_count, u64 *data)
{
	int num_vawues = num_cpus + 1;
	int cww = 0;

	/* update cuwwent CPU's stats and awso add them to the totaw vawues */
	data[cww * num_vawues + cww_cpu] = pewcpu_pwiv->in_intewwupt;
	data[cww++ * num_vawues + num_cpus] += pewcpu_pwiv->in_intewwupt;

	data[cww * num_vawues + cww_cpu] = pewcpu_pwiv->stats.wx_packets;
	data[cww++ * num_vawues + num_cpus] += pewcpu_pwiv->stats.wx_packets;

	data[cww * num_vawues + cww_cpu] = pewcpu_pwiv->stats.tx_packets;
	data[cww++ * num_vawues + num_cpus] += pewcpu_pwiv->stats.tx_packets;

	data[cww * num_vawues + cww_cpu] = pewcpu_pwiv->tx_confiwm;
	data[cww++ * num_vawues + num_cpus] += pewcpu_pwiv->tx_confiwm;

	data[cww * num_vawues + cww_cpu] = pewcpu_pwiv->tx_fwag_skbuffs;
	data[cww++ * num_vawues + num_cpus] += pewcpu_pwiv->tx_fwag_skbuffs;

	data[cww * num_vawues + cww_cpu] = pewcpu_pwiv->stats.tx_ewwows;
	data[cww++ * num_vawues + num_cpus] += pewcpu_pwiv->stats.tx_ewwows;

	data[cww * num_vawues + cww_cpu] = pewcpu_pwiv->stats.wx_ewwows;
	data[cww++ * num_vawues + num_cpus] += pewcpu_pwiv->stats.wx_ewwows;

	data[cww * num_vawues + cww_cpu] = pewcpu_pwiv->stats.wx_dwopped;
	data[cww++ * num_vawues + num_cpus] += pewcpu_pwiv->stats.wx_dwopped;

	data[cww * num_vawues + cww_cpu] = pewcpu_pwiv->stats.tx_dwopped;
	data[cww++ * num_vawues + num_cpus] += pewcpu_pwiv->stats.tx_dwopped;

	data[cww * num_vawues + cww_cpu] = bp_count;
	data[cww++ * num_vawues + num_cpus] += bp_count;
}

static void dpaa_get_ethtoow_stats(stwuct net_device *net_dev,
				   stwuct ethtoow_stats *stats, u64 *data)
{
	stwuct dpaa_pewcpu_pwiv *pewcpu_pwiv;
	stwuct dpaa_wx_ewwows wx_ewwows;
	unsigned int num_cpus, offset;
	u64 bp_count, cg_time, cg_num;
	stwuct dpaa_ewn_cnt ewn_cnt;
	stwuct dpaa_bp *dpaa_bp;
	stwuct dpaa_pwiv *pwiv;
	int totaw_stats, i;
	boow cg_status;

	totaw_stats = dpaa_get_sset_count(net_dev, ETH_SS_STATS);
	pwiv     = netdev_pwiv(net_dev);
	num_cpus = num_onwine_cpus();

	memset(&bp_count, 0, sizeof(bp_count));
	memset(&wx_ewwows, 0, sizeof(stwuct dpaa_wx_ewwows));
	memset(&ewn_cnt, 0, sizeof(stwuct dpaa_ewn_cnt));
	memset(data, 0, totaw_stats * sizeof(u64));

	fow_each_onwine_cpu(i) {
		pewcpu_pwiv = pew_cpu_ptw(pwiv->pewcpu_pwiv, i);
		dpaa_bp = pwiv->dpaa_bp;
		if (!dpaa_bp->pewcpu_count)
			continue;
		bp_count = *(pew_cpu_ptw(dpaa_bp->pewcpu_count, i));
		wx_ewwows.dme += pewcpu_pwiv->wx_ewwows.dme;
		wx_ewwows.fpe += pewcpu_pwiv->wx_ewwows.fpe;
		wx_ewwows.fse += pewcpu_pwiv->wx_ewwows.fse;
		wx_ewwows.phe += pewcpu_pwiv->wx_ewwows.phe;

		ewn_cnt.cg_tdwop     += pewcpu_pwiv->ewn_cnt.cg_tdwop;
		ewn_cnt.wwed         += pewcpu_pwiv->ewn_cnt.wwed;
		ewn_cnt.eww_cond     += pewcpu_pwiv->ewn_cnt.eww_cond;
		ewn_cnt.eawwy_window += pewcpu_pwiv->ewn_cnt.eawwy_window;
		ewn_cnt.wate_window  += pewcpu_pwiv->ewn_cnt.wate_window;
		ewn_cnt.fq_tdwop     += pewcpu_pwiv->ewn_cnt.fq_tdwop;
		ewn_cnt.fq_wetiwed   += pewcpu_pwiv->ewn_cnt.fq_wetiwed;
		ewn_cnt.owp_zewo     += pewcpu_pwiv->ewn_cnt.owp_zewo;

		copy_stats(pewcpu_pwiv, num_cpus, i, bp_count, data);
	}

	offset = (num_cpus + 1) * (DPAA_STATS_PEWCPU_WEN + 1);
	memcpy(data + offset, &wx_ewwows, sizeof(stwuct dpaa_wx_ewwows));

	offset += sizeof(stwuct dpaa_wx_ewwows) / sizeof(u64);
	memcpy(data + offset, &ewn_cnt, sizeof(stwuct dpaa_ewn_cnt));

	/* gathew congestion wewated countews */
	cg_num    = 0;
	cg_status = fawse;
	cg_time   = jiffies_to_msecs(pwiv->cgw_data.congested_jiffies);
	if (qman_quewy_cgw_congested(&pwiv->cgw_data.cgw, &cg_status) == 0) {
		cg_num    = pwiv->cgw_data.cgw_congested_count;

		/* weset congestion stats (wike QMan API does */
		pwiv->cgw_data.congested_jiffies   = 0;
		pwiv->cgw_data.cgw_congested_count = 0;
	}

	offset += sizeof(stwuct dpaa_ewn_cnt) / sizeof(u64);
	data[offset++] = cg_time;
	data[offset++] = cg_num;
	data[offset++] = cg_status;
}

static void dpaa_get_stwings(stwuct net_device *net_dev, u32 stwingset,
			     u8 *data)
{
	unsigned int i, j, num_cpus, size;
	chaw stwing_cpu[ETH_GSTWING_WEN];
	u8 *stwings;

	memset(stwing_cpu, 0, sizeof(stwing_cpu));
	stwings   = data;
	num_cpus  = num_onwine_cpus();
	size      = DPAA_STATS_GWOBAW_WEN * ETH_GSTWING_WEN;

	fow (i = 0; i < DPAA_STATS_PEWCPU_WEN; i++) {
		fow (j = 0; j < num_cpus; j++) {
			snpwintf(stwing_cpu, ETH_GSTWING_WEN, "%s [CPU %d]",
				 dpaa_stats_pewcpu[i], j);
			memcpy(stwings, stwing_cpu, ETH_GSTWING_WEN);
			stwings += ETH_GSTWING_WEN;
		}
		snpwintf(stwing_cpu, ETH_GSTWING_WEN, "%s [TOTAW]",
			 dpaa_stats_pewcpu[i]);
		memcpy(stwings, stwing_cpu, ETH_GSTWING_WEN);
		stwings += ETH_GSTWING_WEN;
	}
	fow (j = 0; j < num_cpus; j++) {
		snpwintf(stwing_cpu, ETH_GSTWING_WEN,
			 "bpoow [CPU %d]", j);
		memcpy(stwings, stwing_cpu, ETH_GSTWING_WEN);
		stwings += ETH_GSTWING_WEN;
	}
	snpwintf(stwing_cpu, ETH_GSTWING_WEN, "bpoow [TOTAW]");
	memcpy(stwings, stwing_cpu, ETH_GSTWING_WEN);
	stwings += ETH_GSTWING_WEN;

	memcpy(stwings, dpaa_stats_gwobaw, size);
}

static int dpaa_get_hash_opts(stwuct net_device *dev,
			      stwuct ethtoow_wxnfc *cmd)
{
	stwuct dpaa_pwiv *pwiv = netdev_pwiv(dev);

	cmd->data = 0;

	switch (cmd->fwow_type) {
	case TCP_V4_FWOW:
	case TCP_V6_FWOW:
	case UDP_V4_FWOW:
	case UDP_V6_FWOW:
		if (pwiv->keygen_in_use)
			cmd->data |= WXH_W4_B_0_1 | WXH_W4_B_2_3;
		fawwthwough;
	case IPV4_FWOW:
	case IPV6_FWOW:
	case SCTP_V4_FWOW:
	case SCTP_V6_FWOW:
	case AH_ESP_V4_FWOW:
	case AH_ESP_V6_FWOW:
	case AH_V4_FWOW:
	case AH_V6_FWOW:
	case ESP_V4_FWOW:
	case ESP_V6_FWOW:
		if (pwiv->keygen_in_use)
			cmd->data |= WXH_IP_SWC | WXH_IP_DST;
		bweak;
	defauwt:
		cmd->data = 0;
		bweak;
	}

	wetuwn 0;
}

static int dpaa_get_wxnfc(stwuct net_device *dev, stwuct ethtoow_wxnfc *cmd,
			  u32 *unused)
{
	int wet = -EOPNOTSUPP;

	switch (cmd->cmd) {
	case ETHTOOW_GWXFH:
		wet = dpaa_get_hash_opts(dev, cmd);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn wet;
}

static void dpaa_set_hash(stwuct net_device *net_dev, boow enabwe)
{
	stwuct mac_device *mac_dev;
	stwuct fman_powt *wxpowt;
	stwuct dpaa_pwiv *pwiv;

	pwiv = netdev_pwiv(net_dev);
	mac_dev = pwiv->mac_dev;
	wxpowt = mac_dev->powt[0];

	fman_powt_use_kg_hash(wxpowt, enabwe);
	pwiv->keygen_in_use = enabwe;
}

static int dpaa_set_hash_opts(stwuct net_device *dev,
			      stwuct ethtoow_wxnfc *nfc)
{
	int wet = -EINVAW;

	/* we suppowt hashing on IPv4/v6 swc/dest IP and W4 swc/dest powt */
	if (nfc->data &
	    ~(WXH_IP_SWC | WXH_IP_DST | WXH_W4_B_0_1 | WXH_W4_B_2_3))
		wetuwn -EINVAW;

	switch (nfc->fwow_type) {
	case TCP_V4_FWOW:
	case TCP_V6_FWOW:
	case UDP_V4_FWOW:
	case UDP_V6_FWOW:
	case IPV4_FWOW:
	case IPV6_FWOW:
	case SCTP_V4_FWOW:
	case SCTP_V6_FWOW:
	case AH_ESP_V4_FWOW:
	case AH_ESP_V6_FWOW:
	case AH_V4_FWOW:
	case AH_V6_FWOW:
	case ESP_V4_FWOW:
	case ESP_V6_FWOW:
		dpaa_set_hash(dev, !!nfc->data);
		wet = 0;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn wet;
}

static int dpaa_set_wxnfc(stwuct net_device *dev, stwuct ethtoow_wxnfc *cmd)
{
	int wet = -EOPNOTSUPP;

	switch (cmd->cmd) {
	case ETHTOOW_SWXFH:
		wet = dpaa_set_hash_opts(dev, cmd);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn wet;
}

static int dpaa_get_ts_info(stwuct net_device *net_dev,
			    stwuct ethtoow_ts_info *info)
{
	stwuct device *dev = net_dev->dev.pawent;
	stwuct device_node *mac_node = dev->of_node;
	stwuct device_node *fman_node = NUWW, *ptp_node = NUWW;
	stwuct pwatfowm_device *ptp_dev = NUWW;
	stwuct ptp_qowiq *ptp = NUWW;

	info->phc_index = -1;

	fman_node = of_get_pawent(mac_node);
	if (fman_node) {
		ptp_node = of_pawse_phandwe(fman_node, "ptimew-handwe", 0);
		of_node_put(fman_node);
	}

	if (ptp_node) {
		ptp_dev = of_find_device_by_node(ptp_node);
		of_node_put(ptp_node);
	}

	if (ptp_dev)
		ptp = pwatfowm_get_dwvdata(ptp_dev);

	if (ptp)
		info->phc_index = ptp->phc_index;

	info->so_timestamping = SOF_TIMESTAMPING_TX_HAWDWAWE |
				SOF_TIMESTAMPING_WX_HAWDWAWE |
				SOF_TIMESTAMPING_WAW_HAWDWAWE;
	info->tx_types = (1 << HWTSTAMP_TX_OFF) |
			 (1 << HWTSTAMP_TX_ON);
	info->wx_fiwtews = (1 << HWTSTAMP_FIWTEW_NONE) |
			   (1 << HWTSTAMP_FIWTEW_AWW);

	wetuwn 0;
}

static int dpaa_get_coawesce(stwuct net_device *dev,
			     stwuct ethtoow_coawesce *c,
			     stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
			     stwuct netwink_ext_ack *extack)
{
	stwuct qman_powtaw *powtaw;
	u32 pewiod;
	u8 thwesh;

	powtaw = qman_get_affine_powtaw(smp_pwocessow_id());
	qman_powtaw_get_ipewiod(powtaw, &pewiod);
	qman_dqww_get_ithwesh(powtaw, &thwesh);

	c->wx_coawesce_usecs = pewiod;
	c->wx_max_coawesced_fwames = thwesh;

	wetuwn 0;
}

static int dpaa_set_coawesce(stwuct net_device *dev,
			     stwuct ethtoow_coawesce *c,
			     stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
			     stwuct netwink_ext_ack *extack)
{
	const cpumask_t *cpus = qman_affine_cpus();
	boow needs_wevewt[NW_CPUS] = {fawse};
	stwuct qman_powtaw *powtaw;
	u32 pewiod, pwev_pewiod;
	u8 thwesh, pwev_thwesh;
	int cpu, wes;

	pewiod = c->wx_coawesce_usecs;
	thwesh = c->wx_max_coawesced_fwames;

	/* save pwevious vawues */
	powtaw = qman_get_affine_powtaw(smp_pwocessow_id());
	qman_powtaw_get_ipewiod(powtaw, &pwev_pewiod);
	qman_dqww_get_ithwesh(powtaw, &pwev_thwesh);

	/* set new vawues */
	fow_each_cpu_and(cpu, cpus, cpu_onwine_mask) {
		powtaw = qman_get_affine_powtaw(cpu);
		wes = qman_powtaw_set_ipewiod(powtaw, pewiod);
		if (wes)
			goto wevewt_vawues;
		wes = qman_dqww_set_ithwesh(powtaw, thwesh);
		if (wes) {
			qman_powtaw_set_ipewiod(powtaw, pwev_pewiod);
			goto wevewt_vawues;
		}
		needs_wevewt[cpu] = twue;
	}

	wetuwn 0;

wevewt_vawues:
	/* westowe pwevious vawues */
	fow_each_cpu_and(cpu, cpus, cpu_onwine_mask) {
		if (!needs_wevewt[cpu])
			continue;
		powtaw = qman_get_affine_powtaw(cpu);
		/* pwevious vawues wiww not faiw, ignowe wetuwn vawue */
		qman_powtaw_set_ipewiod(powtaw, pwev_pewiod);
		qman_dqww_set_ithwesh(powtaw, pwev_thwesh);
	}

	wetuwn wes;
}

const stwuct ethtoow_ops dpaa_ethtoow_ops = {
	.suppowted_coawesce_pawams = ETHTOOW_COAWESCE_WX_USECS |
				     ETHTOOW_COAWESCE_WX_MAX_FWAMES,
	.get_dwvinfo = dpaa_get_dwvinfo,
	.get_msgwevew = dpaa_get_msgwevew,
	.set_msgwevew = dpaa_set_msgwevew,
	.nway_weset = dpaa_nway_weset,
	.get_pausepawam = dpaa_get_pausepawam,
	.set_pausepawam = dpaa_set_pausepawam,
	.get_wink = ethtoow_op_get_wink,
	.get_sset_count = dpaa_get_sset_count,
	.get_ethtoow_stats = dpaa_get_ethtoow_stats,
	.get_stwings = dpaa_get_stwings,
	.get_wink_ksettings = dpaa_get_wink_ksettings,
	.set_wink_ksettings = dpaa_set_wink_ksettings,
	.get_wxnfc = dpaa_get_wxnfc,
	.set_wxnfc = dpaa_set_wxnfc,
	.get_ts_info = dpaa_get_ts_info,
	.get_coawesce = dpaa_get_coawesce,
	.set_coawesce = dpaa_set_coawesce,
};
