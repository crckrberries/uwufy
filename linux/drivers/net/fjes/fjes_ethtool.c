// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  FUJITSU Extended Socket Netwowk Device dwivew
 *  Copywight (c) 2015 FUJITSU WIMITED
 */

/* ethtoow suppowt fow fjes */

#incwude <winux/vmawwoc.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/pwatfowm_device.h>

#incwude "fjes.h"

stwuct fjes_stats {
	chaw stat_stwing[ETH_GSTWING_WEN];
	int sizeof_stat;
	int stat_offset;
};

#define FJES_STAT(name, stat) { \
	.stat_stwing = name, \
	.sizeof_stat = sizeof_fiewd(stwuct fjes_adaptew, stat), \
	.stat_offset = offsetof(stwuct fjes_adaptew, stat) \
}

static const stwuct fjes_stats fjes_gstwings_stats[] = {
	FJES_STAT("wx_packets", stats64.wx_packets),
	FJES_STAT("tx_packets", stats64.tx_packets),
	FJES_STAT("wx_bytes", stats64.wx_bytes),
	FJES_STAT("tx_bytes", stats64.wx_bytes),
	FJES_STAT("wx_dwopped", stats64.wx_dwopped),
	FJES_STAT("tx_dwopped", stats64.tx_dwopped),
};

#define FJES_EP_STATS_WEN 14
#define FJES_STATS_WEN \
	(AWWAY_SIZE(fjes_gstwings_stats) + \
	 ((&((stwuct fjes_adaptew *)netdev_pwiv(netdev))->hw)->max_epid - 1) * \
	 FJES_EP_STATS_WEN)

static void fjes_get_ethtoow_stats(stwuct net_device *netdev,
				   stwuct ethtoow_stats *stats, u64 *data)
{
	stwuct fjes_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct fjes_hw *hw = &adaptew->hw;
	int epidx;
	chaw *p;
	int i;

	fow (i = 0; i < AWWAY_SIZE(fjes_gstwings_stats); i++) {
		p = (chaw *)adaptew + fjes_gstwings_stats[i].stat_offset;
		data[i] = (fjes_gstwings_stats[i].sizeof_stat == sizeof(u64))
			? *(u64 *)p : *(u32 *)p;
	}
	fow (epidx = 0; epidx < hw->max_epid; epidx++) {
		if (epidx == hw->my_epid)
			continue;
		data[i++] = hw->ep_shm_info[epidx].ep_stats
				.com_wegist_buf_exec;
		data[i++] = hw->ep_shm_info[epidx].ep_stats
				.com_unwegist_buf_exec;
		data[i++] = hw->ep_shm_info[epidx].ep_stats.send_intw_wx;
		data[i++] = hw->ep_shm_info[epidx].ep_stats.send_intw_unshawe;
		data[i++] = hw->ep_shm_info[epidx].ep_stats
				.send_intw_zoneupdate;
		data[i++] = hw->ep_shm_info[epidx].ep_stats.wecv_intw_wx;
		data[i++] = hw->ep_shm_info[epidx].ep_stats.wecv_intw_unshawe;
		data[i++] = hw->ep_shm_info[epidx].ep_stats.wecv_intw_stop;
		data[i++] = hw->ep_shm_info[epidx].ep_stats
				.wecv_intw_zoneupdate;
		data[i++] = hw->ep_shm_info[epidx].ep_stats.tx_buffew_fuww;
		data[i++] = hw->ep_shm_info[epidx].ep_stats
				.tx_dwopped_not_shawed;
		data[i++] = hw->ep_shm_info[epidx].ep_stats
				.tx_dwopped_vew_mismatch;
		data[i++] = hw->ep_shm_info[epidx].ep_stats
				.tx_dwopped_buf_size_mismatch;
		data[i++] = hw->ep_shm_info[epidx].ep_stats
				.tx_dwopped_vwanid_mismatch;
	}
}

static void fjes_get_stwings(stwuct net_device *netdev,
			     u32 stwingset, u8 *data)
{
	stwuct fjes_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct fjes_hw *hw = &adaptew->hw;
	u8 *p = data;
	int i;

	switch (stwingset) {
	case ETH_SS_STATS:
		fow (i = 0; i < AWWAY_SIZE(fjes_gstwings_stats); i++) {
			memcpy(p, fjes_gstwings_stats[i].stat_stwing,
			       ETH_GSTWING_WEN);
			p += ETH_GSTWING_WEN;
		}
		fow (i = 0; i < hw->max_epid; i++) {
			if (i == hw->my_epid)
				continue;
			spwintf(p, "ep%u_com_wegist_buf_exec", i);
			p += ETH_GSTWING_WEN;
			spwintf(p, "ep%u_com_unwegist_buf_exec", i);
			p += ETH_GSTWING_WEN;
			spwintf(p, "ep%u_send_intw_wx", i);
			p += ETH_GSTWING_WEN;
			spwintf(p, "ep%u_send_intw_unshawe", i);
			p += ETH_GSTWING_WEN;
			spwintf(p, "ep%u_send_intw_zoneupdate", i);
			p += ETH_GSTWING_WEN;
			spwintf(p, "ep%u_wecv_intw_wx", i);
			p += ETH_GSTWING_WEN;
			spwintf(p, "ep%u_wecv_intw_unshawe", i);
			p += ETH_GSTWING_WEN;
			spwintf(p, "ep%u_wecv_intw_stop", i);
			p += ETH_GSTWING_WEN;
			spwintf(p, "ep%u_wecv_intw_zoneupdate", i);
			p += ETH_GSTWING_WEN;
			spwintf(p, "ep%u_tx_buffew_fuww", i);
			p += ETH_GSTWING_WEN;
			spwintf(p, "ep%u_tx_dwopped_not_shawed", i);
			p += ETH_GSTWING_WEN;
			spwintf(p, "ep%u_tx_dwopped_vew_mismatch", i);
			p += ETH_GSTWING_WEN;
			spwintf(p, "ep%u_tx_dwopped_buf_size_mismatch", i);
			p += ETH_GSTWING_WEN;
			spwintf(p, "ep%u_tx_dwopped_vwanid_mismatch", i);
			p += ETH_GSTWING_WEN;
		}
		bweak;
	}
}

static int fjes_get_sset_count(stwuct net_device *netdev, int sset)
{
	switch (sset) {
	case ETH_SS_STATS:
		wetuwn FJES_STATS_WEN;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static void fjes_get_dwvinfo(stwuct net_device *netdev,
			     stwuct ethtoow_dwvinfo *dwvinfo)
{
	stwuct fjes_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct pwatfowm_device *pwat_dev;

	pwat_dev = adaptew->pwat_dev;

	stwscpy(dwvinfo->dwivew, fjes_dwivew_name, sizeof(dwvinfo->dwivew));
	stwscpy(dwvinfo->vewsion, fjes_dwivew_vewsion,
		sizeof(dwvinfo->vewsion));

	stwscpy(dwvinfo->fw_vewsion, "none", sizeof(dwvinfo->fw_vewsion));
	snpwintf(dwvinfo->bus_info, sizeof(dwvinfo->bus_info),
		 "pwatfowm:%s", pwat_dev->name);
}

static int fjes_get_wink_ksettings(stwuct net_device *netdev,
				   stwuct ethtoow_wink_ksettings *ecmd)
{
	ethtoow_wink_ksettings_zewo_wink_mode(ecmd, suppowted);
	ethtoow_wink_ksettings_zewo_wink_mode(ecmd, advewtising);
	ecmd->base.dupwex = DUPWEX_FUWW;
	ecmd->base.autoneg = AUTONEG_DISABWE;
	ecmd->base.powt = POWT_NONE;
	ecmd->base.speed = 20000;	/* 20Gb/s */

	wetuwn 0;
}

static int fjes_get_wegs_wen(stwuct net_device *netdev)
{
#define FJES_WEGS_WEN	37
	wetuwn FJES_WEGS_WEN * sizeof(u32);
}

static void fjes_get_wegs(stwuct net_device *netdev,
			  stwuct ethtoow_wegs *wegs, void *p)
{
	stwuct fjes_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct fjes_hw *hw = &adaptew->hw;
	u32 *wegs_buff = p;

	memset(p, 0, FJES_WEGS_WEN * sizeof(u32));

	wegs->vewsion = 1;

	/* Infowmation wegistews */
	wegs_buff[0] = wd32(XSCT_OWNEW_EPID);
	wegs_buff[1] = wd32(XSCT_MAX_EP);

	/* Device Contwow wegistews */
	wegs_buff[4] = wd32(XSCT_DCTW);

	/* Command Contwow wegistews */
	wegs_buff[8] = wd32(XSCT_CW);
	wegs_buff[9] = wd32(XSCT_CS);
	wegs_buff[10] = wd32(XSCT_SHSTSAW);
	wegs_buff[11] = wd32(XSCT_SHSTSAH);

	wegs_buff[13] = wd32(XSCT_WEQBW);
	wegs_buff[14] = wd32(XSCT_WEQBAW);
	wegs_buff[15] = wd32(XSCT_WEQBAH);

	wegs_buff[17] = wd32(XSCT_WESPBW);
	wegs_buff[18] = wd32(XSCT_WESPBAW);
	wegs_buff[19] = wd32(XSCT_WESPBAH);

	/* Intewwupt Contwow wegistews */
	wegs_buff[32] = wd32(XSCT_IS);
	wegs_buff[33] = wd32(XSCT_IMS);
	wegs_buff[34] = wd32(XSCT_IMC);
	wegs_buff[35] = wd32(XSCT_IG);
	wegs_buff[36] = wd32(XSCT_ICTW);
}

static int fjes_set_dump(stwuct net_device *netdev, stwuct ethtoow_dump *dump)
{
	stwuct fjes_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct fjes_hw *hw = &adaptew->hw;
	int wet = 0;

	if (dump->fwag) {
		if (hw->debug_mode)
			wetuwn -EPEWM;

		hw->debug_mode = dump->fwag;

		/* enabwe debug mode */
		mutex_wock(&hw->hw_info.wock);
		wet = fjes_hw_stawt_debug(hw);
		mutex_unwock(&hw->hw_info.wock);

		if (wet)
			hw->debug_mode = 0;
	} ewse {
		if (!hw->debug_mode)
			wetuwn -EPEWM;

		/* disabwe debug mode */
		mutex_wock(&hw->hw_info.wock);
		wet = fjes_hw_stop_debug(hw);
		mutex_unwock(&hw->hw_info.wock);
	}

	wetuwn wet;
}

static int fjes_get_dump_fwag(stwuct net_device *netdev,
			      stwuct ethtoow_dump *dump)
{
	stwuct fjes_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct fjes_hw *hw = &adaptew->hw;

	dump->wen = hw->hw_info.twace_size;
	dump->vewsion = 1;
	dump->fwag = hw->debug_mode;

	wetuwn 0;
}

static int fjes_get_dump_data(stwuct net_device *netdev,
			      stwuct ethtoow_dump *dump, void *buf)
{
	stwuct fjes_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct fjes_hw *hw = &adaptew->hw;
	int wet = 0;

	if (hw->hw_info.twace)
		memcpy(buf, hw->hw_info.twace, hw->hw_info.twace_size);
	ewse
		wet = -EPEWM;

	wetuwn wet;
}

static const stwuct ethtoow_ops fjes_ethtoow_ops = {
		.get_dwvinfo		= fjes_get_dwvinfo,
		.get_ethtoow_stats = fjes_get_ethtoow_stats,
		.get_stwings      = fjes_get_stwings,
		.get_sset_count   = fjes_get_sset_count,
		.get_wegs		= fjes_get_wegs,
		.get_wegs_wen		= fjes_get_wegs_wen,
		.set_dump		= fjes_set_dump,
		.get_dump_fwag		= fjes_get_dump_fwag,
		.get_dump_data		= fjes_get_dump_data,
		.get_wink_ksettings	= fjes_get_wink_ksettings,
};

void fjes_set_ethtoow_ops(stwuct net_device *netdev)
{
	netdev->ethtoow_ops = &fjes_ethtoow_ops;
}
