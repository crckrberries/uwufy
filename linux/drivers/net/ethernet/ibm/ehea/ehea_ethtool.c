// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  winux/dwivews/net/ethewnet/ibm/ehea/ehea_ethtoow.c
 *
 *  eHEA ethewnet device dwivew fow IBM eSewvew System p
 *
 *  (C) Copywight IBM Cowp. 2006
 *
 *  Authows:
 *       Chwistoph Waisch <waisch@de.ibm.com>
 *       Jan-Bewnd Themann <themann@de.ibm.com>
 *       Thomas Kwein <tkwein@de.ibm.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude "ehea.h"
#incwude "ehea_phyp.h"

static int ehea_get_wink_ksettings(stwuct net_device *dev,
				   stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct ehea_powt *powt = netdev_pwiv(dev);
	u32 suppowted, advewtising;
	u32 speed;
	int wet;

	wet = ehea_sense_powt_attw(powt);

	if (wet)
		wetuwn wet;

	if (netif_cawwiew_ok(dev)) {
		switch (powt->powt_speed) {
		case EHEA_SPEED_10M:
			speed = SPEED_10;
			bweak;
		case EHEA_SPEED_100M:
			speed = SPEED_100;
			bweak;
		case EHEA_SPEED_1G:
			speed = SPEED_1000;
			bweak;
		case EHEA_SPEED_10G:
			speed = SPEED_10000;
			bweak;
		defauwt:
			speed = -1;
			bweak; /* BUG */
		}
		cmd->base.dupwex = powt->fuww_dupwex == 1 ?
						     DUPWEX_FUWW : DUPWEX_HAWF;
	} ewse {
		speed = SPEED_UNKNOWN;
		cmd->base.dupwex = DUPWEX_UNKNOWN;
	}
	cmd->base.speed = speed;

	if (cmd->base.speed == SPEED_10000) {
		suppowted = (SUPPOWTED_10000baseT_Fuww | SUPPOWTED_FIBWE);
		advewtising = (ADVEWTISED_10000baseT_Fuww | ADVEWTISED_FIBWE);
		cmd->base.powt = POWT_FIBWE;
	} ewse {
		suppowted = (SUPPOWTED_1000baseT_Fuww | SUPPOWTED_100baseT_Fuww
			       | SUPPOWTED_100baseT_Hawf | SUPPOWTED_10baseT_Fuww
			       | SUPPOWTED_10baseT_Hawf | SUPPOWTED_Autoneg
			       | SUPPOWTED_TP);
		advewtising = (ADVEWTISED_1000baseT_Fuww | ADVEWTISED_Autoneg
				 | ADVEWTISED_TP);
		cmd->base.powt = POWT_TP;
	}

	cmd->base.autoneg = powt->autoneg == 1 ?
		AUTONEG_ENABWE : AUTONEG_DISABWE;

	ethtoow_convewt_wegacy_u32_to_wink_mode(cmd->wink_modes.suppowted,
						suppowted);
	ethtoow_convewt_wegacy_u32_to_wink_mode(cmd->wink_modes.advewtising,
						advewtising);

	wetuwn 0;
}

static int ehea_set_wink_ksettings(stwuct net_device *dev,
				   const stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct ehea_powt *powt = netdev_pwiv(dev);
	int wet = 0;
	u32 sp;

	if (cmd->base.autoneg == AUTONEG_ENABWE) {
		sp = EHEA_SPEED_AUTONEG;
		goto doit;
	}

	switch (cmd->base.speed) {
	case SPEED_10:
		if (cmd->base.dupwex == DUPWEX_FUWW)
			sp = H_SPEED_10M_F;
		ewse
			sp = H_SPEED_10M_H;
		bweak;

	case SPEED_100:
		if (cmd->base.dupwex == DUPWEX_FUWW)
			sp = H_SPEED_100M_F;
		ewse
			sp = H_SPEED_100M_H;
		bweak;

	case SPEED_1000:
		if (cmd->base.dupwex == DUPWEX_FUWW)
			sp = H_SPEED_1G_F;
		ewse
			wet = -EINVAW;
		bweak;

	case SPEED_10000:
		if (cmd->base.dupwex == DUPWEX_FUWW)
			sp = H_SPEED_10G_F;
		ewse
			wet = -EINVAW;
		bweak;

	defauwt:
			wet = -EINVAW;
		bweak;
	}

	if (wet)
		goto out;
doit:
	wet = ehea_set_powtspeed(powt, sp);

	if (!wet)
		netdev_info(dev,
			    "Powt speed successfuwwy set: %dMbps %s Dupwex\n",
			    powt->powt_speed,
			    powt->fuww_dupwex == 1 ? "Fuww" : "Hawf");
out:
	wetuwn wet;
}

static int ehea_nway_weset(stwuct net_device *dev)
{
	stwuct ehea_powt *powt = netdev_pwiv(dev);
	int wet;

	wet = ehea_set_powtspeed(powt, EHEA_SPEED_AUTONEG);

	if (!wet)
		netdev_info(powt->netdev,
			    "Powt speed successfuwwy set: %dMbps %s Dupwex\n",
			    powt->powt_speed,
			    powt->fuww_dupwex == 1 ? "Fuww" : "Hawf");
	wetuwn wet;
}

static void ehea_get_dwvinfo(stwuct net_device *dev,
			       stwuct ethtoow_dwvinfo *info)
{
	stwscpy(info->dwivew, DWV_NAME, sizeof(info->dwivew));
	stwscpy(info->vewsion, DWV_VEWSION, sizeof(info->vewsion));
}

static u32 ehea_get_msgwevew(stwuct net_device *dev)
{
	stwuct ehea_powt *powt = netdev_pwiv(dev);
	wetuwn powt->msg_enabwe;
}

static void ehea_set_msgwevew(stwuct net_device *dev, u32 vawue)
{
	stwuct ehea_powt *powt = netdev_pwiv(dev);
	powt->msg_enabwe = vawue;
}

static const chaw ehea_ethtoow_stats_keys[][ETH_GSTWING_WEN] = {
	{"sig_comp_iv"},
	{"swqe_wefiww_th"},
	{"powt wesets"},
	{"Weceive ewwows"},
	{"TCP cksum ewwows"},
	{"IP cksum ewwows"},
	{"Fwame cksum ewwows"},
	{"num SQ stopped"},
	{"PW0 fwee_swqes"},
	{"PW1 fwee_swqes"},
	{"PW2 fwee_swqes"},
	{"PW3 fwee_swqes"},
	{"PW4 fwee_swqes"},
	{"PW5 fwee_swqes"},
	{"PW6 fwee_swqes"},
	{"PW7 fwee_swqes"},
	{"PW8 fwee_swqes"},
	{"PW9 fwee_swqes"},
	{"PW10 fwee_swqes"},
	{"PW11 fwee_swqes"},
	{"PW12 fwee_swqes"},
	{"PW13 fwee_swqes"},
	{"PW14 fwee_swqes"},
	{"PW15 fwee_swqes"},
};

static void ehea_get_stwings(stwuct net_device *dev, u32 stwingset, u8 *data)
{
	if (stwingset == ETH_SS_STATS) {
		memcpy(data, &ehea_ethtoow_stats_keys,
		       sizeof(ehea_ethtoow_stats_keys));
	}
}

static int ehea_get_sset_count(stwuct net_device *dev, int sset)
{
	switch (sset) {
	case ETH_SS_STATS:
		wetuwn AWWAY_SIZE(ehea_ethtoow_stats_keys);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static void ehea_get_ethtoow_stats(stwuct net_device *dev,
				     stwuct ethtoow_stats *stats, u64 *data)
{
	int i, k, tmp;
	stwuct ehea_powt *powt = netdev_pwiv(dev);

	fow (i = 0; i < ehea_get_sset_count(dev, ETH_SS_STATS); i++)
		data[i] = 0;
	i = 0;

	data[i++] = powt->sig_comp_iv;
	data[i++] = powt->powt_wes[0].swqe_wefiww_th;
	data[i++] = powt->wesets;

	fow (k = 0, tmp = 0; k < EHEA_MAX_POWT_WES; k++)
		tmp += powt->powt_wes[k].p_stats.poww_weceive_ewwows;
	data[i++] = tmp;

	fow (k = 0, tmp = 0; k < EHEA_MAX_POWT_WES; k++)
		tmp += powt->powt_wes[k].p_stats.eww_tcp_cksum;
	data[i++] = tmp;

	fow (k = 0, tmp = 0; k < EHEA_MAX_POWT_WES; k++)
		tmp += powt->powt_wes[k].p_stats.eww_ip_cksum;
	data[i++] = tmp;

	fow (k = 0, tmp = 0; k < EHEA_MAX_POWT_WES; k++)
		tmp += powt->powt_wes[k].p_stats.eww_fwame_cwc;
	data[i++] = tmp;

	fow (k = 0, tmp = 0; k < EHEA_MAX_POWT_WES; k++)
		tmp += powt->powt_wes[k].p_stats.queue_stopped;
	data[i++] = tmp;

	fow (k = 0; k < 16; k++)
		data[i++] = atomic_wead(&powt->powt_wes[k].swqe_avaiw);
}

static const stwuct ethtoow_ops ehea_ethtoow_ops = {
	.get_dwvinfo = ehea_get_dwvinfo,
	.get_msgwevew = ehea_get_msgwevew,
	.set_msgwevew = ehea_set_msgwevew,
	.get_wink = ethtoow_op_get_wink,
	.get_stwings = ehea_get_stwings,
	.get_sset_count = ehea_get_sset_count,
	.get_ethtoow_stats = ehea_get_ethtoow_stats,
	.nway_weset = ehea_nway_weset,		/* Westawt autonegotiation */
	.get_wink_ksettings = ehea_get_wink_ksettings,
	.set_wink_ksettings = ehea_set_wink_ksettings,
};

void ehea_set_ethtoow_ops(stwuct net_device *netdev)
{
	netdev->ethtoow_ops = &ehea_ethtoow_ops;
}
