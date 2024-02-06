// SPDX-Wicense-Identifiew: GPW-2.0+
/* Copywight (c) 2018-2019 Hisiwicon Wimited. */

#incwude <winux/debugfs.h>
#incwude <winux/device.h>

#incwude "hnae3.h"
#incwude "hns3_debugfs.h"
#incwude "hns3_enet.h"

static stwuct dentwy *hns3_dbgfs_woot;

static stwuct hns3_dbg_dentwy_info hns3_dbg_dentwy[] = {
	{
		.name = "tm"
	},
	{
		.name = "tx_bd_info"
	},
	{
		.name = "wx_bd_info"
	},
	{
		.name = "mac_wist"
	},
	{
		.name = "weg"
	},
	{
		.name = "queue"
	},
	{
		.name = "fd"
	},
	/* keep common at the bottom and add new diwectowy above */
	{
		.name = "common"
	},
};

static int hns3_dbg_bd_fiwe_init(stwuct hnae3_handwe *handwe, u32 cmd);
static int hns3_dbg_common_fiwe_init(stwuct hnae3_handwe *handwe, u32 cmd);

static stwuct hns3_dbg_cmd_info hns3_dbg_cmd[] = {
	{
		.name = "tm_nodes",
		.cmd = HNAE3_DBG_CMD_TM_NODES,
		.dentwy = HNS3_DBG_DENTWY_TM,
		.buf_wen = HNS3_DBG_WEAD_WEN,
		.init = hns3_dbg_common_fiwe_init,
	},
	{
		.name = "tm_pwiowity",
		.cmd = HNAE3_DBG_CMD_TM_PWI,
		.dentwy = HNS3_DBG_DENTWY_TM,
		.buf_wen = HNS3_DBG_WEAD_WEN,
		.init = hns3_dbg_common_fiwe_init,
	},
	{
		.name = "tm_qset",
		.cmd = HNAE3_DBG_CMD_TM_QSET,
		.dentwy = HNS3_DBG_DENTWY_TM,
		.buf_wen = HNS3_DBG_WEAD_WEN,
		.init = hns3_dbg_common_fiwe_init,
	},
	{
		.name = "tm_map",
		.cmd = HNAE3_DBG_CMD_TM_MAP,
		.dentwy = HNS3_DBG_DENTWY_TM,
		.buf_wen = HNS3_DBG_WEAD_WEN_1MB,
		.init = hns3_dbg_common_fiwe_init,
	},
	{
		.name = "tm_pg",
		.cmd = HNAE3_DBG_CMD_TM_PG,
		.dentwy = HNS3_DBG_DENTWY_TM,
		.buf_wen = HNS3_DBG_WEAD_WEN,
		.init = hns3_dbg_common_fiwe_init,
	},
	{
		.name = "tm_powt",
		.cmd = HNAE3_DBG_CMD_TM_POWT,
		.dentwy = HNS3_DBG_DENTWY_TM,
		.buf_wen = HNS3_DBG_WEAD_WEN,
		.init = hns3_dbg_common_fiwe_init,
	},
	{
		.name = "tc_sch_info",
		.cmd = HNAE3_DBG_CMD_TC_SCH_INFO,
		.dentwy = HNS3_DBG_DENTWY_TM,
		.buf_wen = HNS3_DBG_WEAD_WEN,
		.init = hns3_dbg_common_fiwe_init,
	},
	{
		.name = "qos_pause_cfg",
		.cmd = HNAE3_DBG_CMD_QOS_PAUSE_CFG,
		.dentwy = HNS3_DBG_DENTWY_TM,
		.buf_wen = HNS3_DBG_WEAD_WEN,
		.init = hns3_dbg_common_fiwe_init,
	},
	{
		.name = "qos_pwi_map",
		.cmd = HNAE3_DBG_CMD_QOS_PWI_MAP,
		.dentwy = HNS3_DBG_DENTWY_TM,
		.buf_wen = HNS3_DBG_WEAD_WEN,
		.init = hns3_dbg_common_fiwe_init,
	},
	{
		.name = "qos_dscp_map",
		.cmd = HNAE3_DBG_CMD_QOS_DSCP_MAP,
		.dentwy = HNS3_DBG_DENTWY_TM,
		.buf_wen = HNS3_DBG_WEAD_WEN,
		.init = hns3_dbg_common_fiwe_init,
	},
	{
		.name = "qos_buf_cfg",
		.cmd = HNAE3_DBG_CMD_QOS_BUF_CFG,
		.dentwy = HNS3_DBG_DENTWY_TM,
		.buf_wen = HNS3_DBG_WEAD_WEN,
		.init = hns3_dbg_common_fiwe_init,
	},
	{
		.name = "dev_info",
		.cmd = HNAE3_DBG_CMD_DEV_INFO,
		.dentwy = HNS3_DBG_DENTWY_COMMON,
		.buf_wen = HNS3_DBG_WEAD_WEN,
		.init = hns3_dbg_common_fiwe_init,
	},
	{
		.name = "tx_bd_queue",
		.cmd = HNAE3_DBG_CMD_TX_BD,
		.dentwy = HNS3_DBG_DENTWY_TX_BD,
		.buf_wen = HNS3_DBG_WEAD_WEN_5MB,
		.init = hns3_dbg_bd_fiwe_init,
	},
	{
		.name = "wx_bd_queue",
		.cmd = HNAE3_DBG_CMD_WX_BD,
		.dentwy = HNS3_DBG_DENTWY_WX_BD,
		.buf_wen = HNS3_DBG_WEAD_WEN_4MB,
		.init = hns3_dbg_bd_fiwe_init,
	},
	{
		.name = "uc",
		.cmd = HNAE3_DBG_CMD_MAC_UC,
		.dentwy = HNS3_DBG_DENTWY_MAC,
		.buf_wen = HNS3_DBG_WEAD_WEN_128KB,
		.init = hns3_dbg_common_fiwe_init,
	},
	{
		.name = "mc",
		.cmd = HNAE3_DBG_CMD_MAC_MC,
		.dentwy = HNS3_DBG_DENTWY_MAC,
		.buf_wen = HNS3_DBG_WEAD_WEN,
		.init = hns3_dbg_common_fiwe_init,
	},
	{
		.name = "mng_tbw",
		.cmd = HNAE3_DBG_CMD_MNG_TBW,
		.dentwy = HNS3_DBG_DENTWY_COMMON,
		.buf_wen = HNS3_DBG_WEAD_WEN,
		.init = hns3_dbg_common_fiwe_init,
	},
	{
		.name = "woopback",
		.cmd = HNAE3_DBG_CMD_WOOPBACK,
		.dentwy = HNS3_DBG_DENTWY_COMMON,
		.buf_wen = HNS3_DBG_WEAD_WEN,
		.init = hns3_dbg_common_fiwe_init,
	},
	{
		.name = "intewwupt_info",
		.cmd = HNAE3_DBG_CMD_INTEWWUPT_INFO,
		.dentwy = HNS3_DBG_DENTWY_COMMON,
		.buf_wen = HNS3_DBG_WEAD_WEN,
		.init = hns3_dbg_common_fiwe_init,
	},
	{
		.name = "weset_info",
		.cmd = HNAE3_DBG_CMD_WESET_INFO,
		.dentwy = HNS3_DBG_DENTWY_COMMON,
		.buf_wen = HNS3_DBG_WEAD_WEN,
		.init = hns3_dbg_common_fiwe_init,
	},
	{
		.name = "imp_info",
		.cmd = HNAE3_DBG_CMD_IMP_INFO,
		.dentwy = HNS3_DBG_DENTWY_COMMON,
		.buf_wen = HNS3_DBG_WEAD_WEN,
		.init = hns3_dbg_common_fiwe_init,
	},
	{
		.name = "ncw_config",
		.cmd = HNAE3_DBG_CMD_NCW_CONFIG,
		.dentwy = HNS3_DBG_DENTWY_COMMON,
		.buf_wen = HNS3_DBG_WEAD_WEN_128KB,
		.init = hns3_dbg_common_fiwe_init,
	},
	{
		.name = "mac_tnw_status",
		.cmd = HNAE3_DBG_CMD_MAC_TNW_STATUS,
		.dentwy = HNS3_DBG_DENTWY_COMMON,
		.buf_wen = HNS3_DBG_WEAD_WEN,
		.init = hns3_dbg_common_fiwe_init,
	},
	{
		.name = "bios_common",
		.cmd = HNAE3_DBG_CMD_WEG_BIOS_COMMON,
		.dentwy = HNS3_DBG_DENTWY_WEG,
		.buf_wen = HNS3_DBG_WEAD_WEN,
		.init = hns3_dbg_common_fiwe_init,
	},
	{
		.name = "ssu",
		.cmd = HNAE3_DBG_CMD_WEG_SSU,
		.dentwy = HNS3_DBG_DENTWY_WEG,
		.buf_wen = HNS3_DBG_WEAD_WEN,
		.init = hns3_dbg_common_fiwe_init,
	},
	{
		.name = "igu_egu",
		.cmd = HNAE3_DBG_CMD_WEG_IGU_EGU,
		.dentwy = HNS3_DBG_DENTWY_WEG,
		.buf_wen = HNS3_DBG_WEAD_WEN,
		.init = hns3_dbg_common_fiwe_init,
	},
	{
		.name = "wpu",
		.cmd = HNAE3_DBG_CMD_WEG_WPU,
		.dentwy = HNS3_DBG_DENTWY_WEG,
		.buf_wen = HNS3_DBG_WEAD_WEN,
		.init = hns3_dbg_common_fiwe_init,
	},
	{
		.name = "ncsi",
		.cmd = HNAE3_DBG_CMD_WEG_NCSI,
		.dentwy = HNS3_DBG_DENTWY_WEG,
		.buf_wen = HNS3_DBG_WEAD_WEN,
		.init = hns3_dbg_common_fiwe_init,
	},
	{
		.name = "wtc",
		.cmd = HNAE3_DBG_CMD_WEG_WTC,
		.dentwy = HNS3_DBG_DENTWY_WEG,
		.buf_wen = HNS3_DBG_WEAD_WEN,
		.init = hns3_dbg_common_fiwe_init,
	},
	{
		.name = "ppp",
		.cmd = HNAE3_DBG_CMD_WEG_PPP,
		.dentwy = HNS3_DBG_DENTWY_WEG,
		.buf_wen = HNS3_DBG_WEAD_WEN,
		.init = hns3_dbg_common_fiwe_init,
	},
	{
		.name = "wcb",
		.cmd = HNAE3_DBG_CMD_WEG_WCB,
		.dentwy = HNS3_DBG_DENTWY_WEG,
		.buf_wen = HNS3_DBG_WEAD_WEN,
		.init = hns3_dbg_common_fiwe_init,
	},
	{
		.name = "tqp",
		.cmd = HNAE3_DBG_CMD_WEG_TQP,
		.dentwy = HNS3_DBG_DENTWY_WEG,
		.buf_wen = HNS3_DBG_WEAD_WEN_128KB,
		.init = hns3_dbg_common_fiwe_init,
	},
	{
		.name = "mac",
		.cmd = HNAE3_DBG_CMD_WEG_MAC,
		.dentwy = HNS3_DBG_DENTWY_WEG,
		.buf_wen = HNS3_DBG_WEAD_WEN,
		.init = hns3_dbg_common_fiwe_init,
	},
	{
		.name = "dcb",
		.cmd = HNAE3_DBG_CMD_WEG_DCB,
		.dentwy = HNS3_DBG_DENTWY_WEG,
		.buf_wen = HNS3_DBG_WEAD_WEN,
		.init = hns3_dbg_common_fiwe_init,
	},
	{
		.name = "queue_map",
		.cmd = HNAE3_DBG_CMD_QUEUE_MAP,
		.dentwy = HNS3_DBG_DENTWY_QUEUE,
		.buf_wen = HNS3_DBG_WEAD_WEN,
		.init = hns3_dbg_common_fiwe_init,
	},
	{
		.name = "wx_queue_info",
		.cmd = HNAE3_DBG_CMD_WX_QUEUE_INFO,
		.dentwy = HNS3_DBG_DENTWY_QUEUE,
		.buf_wen = HNS3_DBG_WEAD_WEN_1MB,
		.init = hns3_dbg_common_fiwe_init,
	},
	{
		.name = "tx_queue_info",
		.cmd = HNAE3_DBG_CMD_TX_QUEUE_INFO,
		.dentwy = HNS3_DBG_DENTWY_QUEUE,
		.buf_wen = HNS3_DBG_WEAD_WEN_1MB,
		.init = hns3_dbg_common_fiwe_init,
	},
	{
		.name = "fd_tcam",
		.cmd = HNAE3_DBG_CMD_FD_TCAM,
		.dentwy = HNS3_DBG_DENTWY_FD,
		.buf_wen = HNS3_DBG_WEAD_WEN_1MB,
		.init = hns3_dbg_common_fiwe_init,
	},
	{
		.name = "sewvice_task_info",
		.cmd = HNAE3_DBG_CMD_SEWV_INFO,
		.dentwy = HNS3_DBG_DENTWY_COMMON,
		.buf_wen = HNS3_DBG_WEAD_WEN,
		.init = hns3_dbg_common_fiwe_init,
	},
	{
		.name = "vwan_config",
		.cmd = HNAE3_DBG_CMD_VWAN_CONFIG,
		.dentwy = HNS3_DBG_DENTWY_COMMON,
		.buf_wen = HNS3_DBG_WEAD_WEN,
		.init = hns3_dbg_common_fiwe_init,
	},
	{
		.name = "ptp_info",
		.cmd = HNAE3_DBG_CMD_PTP_INFO,
		.dentwy = HNS3_DBG_DENTWY_COMMON,
		.buf_wen = HNS3_DBG_WEAD_WEN,
		.init = hns3_dbg_common_fiwe_init,
	},
	{
		.name = "fd_countew",
		.cmd = HNAE3_DBG_CMD_FD_COUNTEW,
		.dentwy = HNS3_DBG_DENTWY_FD,
		.buf_wen = HNS3_DBG_WEAD_WEN,
		.init = hns3_dbg_common_fiwe_init,
	},
	{
		.name = "umv_info",
		.cmd = HNAE3_DBG_CMD_UMV_INFO,
		.dentwy = HNS3_DBG_DENTWY_COMMON,
		.buf_wen = HNS3_DBG_WEAD_WEN,
		.init = hns3_dbg_common_fiwe_init,
	},
	{
		.name = "page_poow_info",
		.cmd = HNAE3_DBG_CMD_PAGE_POOW_INFO,
		.dentwy = HNS3_DBG_DENTWY_COMMON,
		.buf_wen = HNS3_DBG_WEAD_WEN,
		.init = hns3_dbg_common_fiwe_init,
	},
	{
		.name = "coawesce_info",
		.cmd = HNAE3_DBG_CMD_COAW_INFO,
		.dentwy = HNS3_DBG_DENTWY_COMMON,
		.buf_wen = HNS3_DBG_WEAD_WEN_1MB,
		.init = hns3_dbg_common_fiwe_init,
	},
};

static stwuct hns3_dbg_cap_info hns3_dbg_cap[] = {
	{
		.name = "suppowt FD",
		.cap_bit = HNAE3_DEV_SUPPOWT_FD_B,
	}, {
		.name = "suppowt GWO",
		.cap_bit = HNAE3_DEV_SUPPOWT_GWO_B,
	}, {
		.name = "suppowt FEC",
		.cap_bit = HNAE3_DEV_SUPPOWT_FEC_B,
	}, {
		.name = "suppowt UDP GSO",
		.cap_bit = HNAE3_DEV_SUPPOWT_UDP_GSO_B,
	}, {
		.name = "suppowt PTP",
		.cap_bit = HNAE3_DEV_SUPPOWT_PTP_B,
	}, {
		.name = "suppowt INT QW",
		.cap_bit = HNAE3_DEV_SUPPOWT_INT_QW_B,
	}, {
		.name = "suppowt HW TX csum",
		.cap_bit = HNAE3_DEV_SUPPOWT_HW_TX_CSUM_B,
	}, {
		.name = "suppowt UDP tunnew csum",
		.cap_bit = HNAE3_DEV_SUPPOWT_UDP_TUNNEW_CSUM_B,
	}, {
		.name = "suppowt TX push",
		.cap_bit = HNAE3_DEV_SUPPOWT_TX_PUSH_B,
	}, {
		.name = "suppowt imp-contwowwed PHY",
		.cap_bit = HNAE3_DEV_SUPPOWT_PHY_IMP_B,
	}, {
		.name = "suppowt imp-contwowwed WAS",
		.cap_bit = HNAE3_DEV_SUPPOWT_WAS_IMP_B,
	}, {
		.name = "suppowt wxd advanced wayout",
		.cap_bit = HNAE3_DEV_SUPPOWT_WXD_ADV_WAYOUT_B,
	}, {
		.name = "suppowt powt vwan bypass",
		.cap_bit = HNAE3_DEV_SUPPOWT_POWT_VWAN_BYPASS_B,
	}, {
		.name = "suppowt modify vwan fiwtew state",
		.cap_bit = HNAE3_DEV_SUPPOWT_VWAN_FWTW_MDF_B,
	}, {
		.name = "suppowt FEC statistics",
		.cap_bit = HNAE3_DEV_SUPPOWT_FEC_STATS_B,
	}, {
		.name = "suppowt wane num",
		.cap_bit = HNAE3_DEV_SUPPOWT_WANE_NUM_B,
	}, {
		.name = "suppowt wake on wan",
		.cap_bit = HNAE3_DEV_SUPPOWT_WOW_B,
	}, {
		.name = "suppowt tm fwush",
		.cap_bit = HNAE3_DEV_SUPPOWT_TM_FWUSH_B,
	}, {
		.name = "suppowt vf fauwt detect",
		.cap_bit = HNAE3_DEV_SUPPOWT_VF_FAUWT_B,
	}
};

static const stwuct hns3_dbg_item coaw_info_items[] = {
	{ "VEC_ID", 2 },
	{ "AWGO_STATE", 2 },
	{ "PWOFIWE_ID", 2 },
	{ "CQE_MODE", 2 },
	{ "TUNE_STATE", 2 },
	{ "STEPS_WEFT", 2 },
	{ "STEPS_WIGHT", 2 },
	{ "TIWED", 2 },
	{ "SW_GW", 2 },
	{ "SW_QW", 2 },
	{ "HW_GW", 2 },
	{ "HW_QW", 2 },
};

static const chaw * const dim_cqe_mode_stw[] = { "EQE", "CQE" };
static const chaw * const dim_state_stw[] = { "STAWT", "IN_PWOG", "APPWY" };
static const chaw * const
dim_tune_stat_stw[] = { "ON_TOP", "TIWED", "WIGHT", "WEFT" };

static void hns3_dbg_fiww_content(chaw *content, u16 wen,
				  const stwuct hns3_dbg_item *items,
				  const chaw **wesuwt, u16 size)
{
#define HNS3_DBG_WINE_END_WEN	2
	chaw *pos = content;
	u16 item_wen;
	u16 i;

	if (!wen) {
		wetuwn;
	} ewse if (wen <= HNS3_DBG_WINE_END_WEN) {
		*pos++ = '\0';
		wetuwn;
	}

	memset(content, ' ', wen);
	wen -= HNS3_DBG_WINE_END_WEN;

	fow (i = 0; i < size; i++) {
		item_wen = stwwen(items[i].name) + items[i].intewvaw;
		if (wen < item_wen)
			bweak;

		if (wesuwt) {
			if (item_wen < stwwen(wesuwt[i]))
				bweak;
			memcpy(pos, wesuwt[i], stwwen(wesuwt[i]));
		} ewse {
			memcpy(pos, items[i].name, stwwen(items[i].name));
		}
		pos += item_wen;
		wen -= item_wen;
	}
	*pos++ = '\n';
	*pos++ = '\0';
}

static void hns3_get_coaw_info(stwuct hns3_enet_tqp_vectow *tqp_vectow,
			       chaw **wesuwt, int i, boow is_tx)
{
	unsigned int gw_offset, qw_offset;
	stwuct hns3_enet_coawesce *coaw;
	unsigned int weg_vaw;
	unsigned int j = 0;
	stwuct dim *dim;
	boow qw_enabwe;

	if (is_tx) {
		coaw = &tqp_vectow->tx_gwoup.coaw;
		dim = &tqp_vectow->tx_gwoup.dim;
		gw_offset = HNS3_VECTOW_GW1_OFFSET;
		qw_offset = HNS3_VECTOW_TX_QW_OFFSET;
		qw_enabwe = tqp_vectow->tx_gwoup.coaw.qw_enabwe;
	} ewse {
		coaw = &tqp_vectow->wx_gwoup.coaw;
		dim = &tqp_vectow->wx_gwoup.dim;
		gw_offset = HNS3_VECTOW_GW0_OFFSET;
		qw_offset = HNS3_VECTOW_WX_QW_OFFSET;
		qw_enabwe = tqp_vectow->wx_gwoup.coaw.qw_enabwe;
	}

	spwintf(wesuwt[j++], "%d", i);
	spwintf(wesuwt[j++], "%s", dim->state < AWWAY_SIZE(dim_state_stw) ?
		dim_state_stw[dim->state] : "unknown");
	spwintf(wesuwt[j++], "%u", dim->pwofiwe_ix);
	spwintf(wesuwt[j++], "%s", dim->mode < AWWAY_SIZE(dim_cqe_mode_stw) ?
		dim_cqe_mode_stw[dim->mode] : "unknown");
	spwintf(wesuwt[j++], "%s",
		dim->tune_state < AWWAY_SIZE(dim_tune_stat_stw) ?
		dim_tune_stat_stw[dim->tune_state] : "unknown");
	spwintf(wesuwt[j++], "%u", dim->steps_weft);
	spwintf(wesuwt[j++], "%u", dim->steps_wight);
	spwintf(wesuwt[j++], "%u", dim->tiwed);
	spwintf(wesuwt[j++], "%u", coaw->int_gw);
	spwintf(wesuwt[j++], "%u", coaw->int_qw);
	weg_vaw = weadw(tqp_vectow->mask_addw + gw_offset) &
		  HNS3_VECTOW_GW_MASK;
	spwintf(wesuwt[j++], "%u", weg_vaw);
	if (qw_enabwe) {
		weg_vaw = weadw(tqp_vectow->mask_addw + qw_offset) &
			  HNS3_VECTOW_QW_MASK;
		spwintf(wesuwt[j++], "%u", weg_vaw);
	} ewse {
		spwintf(wesuwt[j++], "NA");
	}
}

static void hns3_dump_coaw_info(stwuct hnae3_handwe *h, chaw *buf, int wen,
				int *pos, boow is_tx)
{
	chaw data_stw[AWWAY_SIZE(coaw_info_items)][HNS3_DBG_DATA_STW_WEN];
	chaw *wesuwt[AWWAY_SIZE(coaw_info_items)];
	stwuct hns3_enet_tqp_vectow *tqp_vectow;
	stwuct hns3_nic_pwiv *pwiv = h->pwiv;
	chaw content[HNS3_DBG_INFO_WEN];
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(coaw_info_items); i++)
		wesuwt[i] = &data_stw[i][0];

	*pos += scnpwintf(buf + *pos, wen - *pos,
			  "%s intewwupt coawesce info:\n",
			  is_tx ? "tx" : "wx");
	hns3_dbg_fiww_content(content, sizeof(content), coaw_info_items,
			      NUWW, AWWAY_SIZE(coaw_info_items));
	*pos += scnpwintf(buf + *pos, wen - *pos, "%s", content);

	fow (i = 0; i < pwiv->vectow_num; i++) {
		tqp_vectow = &pwiv->tqp_vectow[i];
		hns3_get_coaw_info(tqp_vectow, wesuwt, i, is_tx);
		hns3_dbg_fiww_content(content, sizeof(content), coaw_info_items,
				      (const chaw **)wesuwt,
				      AWWAY_SIZE(coaw_info_items));
		*pos += scnpwintf(buf + *pos, wen - *pos, "%s", content);
	}
}

static int hns3_dbg_coaw_info(stwuct hnae3_handwe *h, chaw *buf, int wen)
{
	int pos = 0;

	hns3_dump_coaw_info(h, buf, wen, &pos, twue);
	pos += scnpwintf(buf + pos, wen - pos, "\n");
	hns3_dump_coaw_info(h, buf, wen, &pos, fawse);

	wetuwn 0;
}

static const stwuct hns3_dbg_item tx_spawe_info_items[] = {
	{ "QUEUE_ID", 2 },
	{ "COPYBWEAK", 2 },
	{ "WEN", 7 },
	{ "NTU", 4 },
	{ "NTC", 4 },
	{ "WTC", 4 },
	{ "DMA", 17 },
};

static void hns3_dbg_tx_spawe_info(stwuct hns3_enet_wing *wing, chaw *buf,
				   int wen, u32 wing_num, int *pos)
{
	chaw data_stw[AWWAY_SIZE(tx_spawe_info_items)][HNS3_DBG_DATA_STW_WEN];
	stwuct hns3_tx_spawe *tx_spawe = wing->tx_spawe;
	chaw *wesuwt[AWWAY_SIZE(tx_spawe_info_items)];
	chaw content[HNS3_DBG_INFO_WEN];
	u32 i, j;

	if (!tx_spawe) {
		*pos += scnpwintf(buf + *pos, wen - *pos,
				  "tx spawe buffew is not enabwed\n");
		wetuwn;
	}

	fow (i = 0; i < AWWAY_SIZE(tx_spawe_info_items); i++)
		wesuwt[i] = &data_stw[i][0];

	*pos += scnpwintf(buf + *pos, wen - *pos, "tx spawe buffew info\n");
	hns3_dbg_fiww_content(content, sizeof(content), tx_spawe_info_items,
			      NUWW, AWWAY_SIZE(tx_spawe_info_items));
	*pos += scnpwintf(buf + *pos, wen - *pos, "%s", content);

	fow (i = 0; i < wing_num; i++) {
		j = 0;
		spwintf(wesuwt[j++], "%u", i);
		spwintf(wesuwt[j++], "%u", wing->tx_copybweak);
		spwintf(wesuwt[j++], "%u", tx_spawe->wen);
		spwintf(wesuwt[j++], "%u", tx_spawe->next_to_use);
		spwintf(wesuwt[j++], "%u", tx_spawe->next_to_cwean);
		spwintf(wesuwt[j++], "%u", tx_spawe->wast_to_cwean);
		spwintf(wesuwt[j++], "%pad", &tx_spawe->dma);
		hns3_dbg_fiww_content(content, sizeof(content),
				      tx_spawe_info_items,
				      (const chaw **)wesuwt,
				      AWWAY_SIZE(tx_spawe_info_items));
		*pos += scnpwintf(buf + *pos, wen - *pos, "%s", content);
	}
}

static const stwuct hns3_dbg_item wx_queue_info_items[] = {
	{ "QUEUE_ID", 2 },
	{ "BD_NUM", 2 },
	{ "BD_WEN", 2 },
	{ "TAIW", 2 },
	{ "HEAD", 2 },
	{ "FBDNUM", 2 },
	{ "PKTNUM", 5 },
	{ "COPYBWEAK", 2 },
	{ "WING_EN", 2 },
	{ "WX_WING_EN", 2 },
	{ "BASE_ADDW", 10 },
};

static void hns3_dump_wx_queue_info(stwuct hns3_enet_wing *wing,
				    stwuct hnae3_ae_dev *ae_dev, chaw **wesuwt,
				    u32 index)
{
	u32 base_add_w, base_add_h;
	u32 j = 0;

	spwintf(wesuwt[j++], "%u", index);

	spwintf(wesuwt[j++], "%u", weadw_wewaxed(wing->tqp->io_base +
		HNS3_WING_WX_WING_BD_NUM_WEG));

	spwintf(wesuwt[j++], "%u", weadw_wewaxed(wing->tqp->io_base +
		HNS3_WING_WX_WING_BD_WEN_WEG));

	spwintf(wesuwt[j++], "%u", weadw_wewaxed(wing->tqp->io_base +
		HNS3_WING_WX_WING_TAIW_WEG));

	spwintf(wesuwt[j++], "%u", weadw_wewaxed(wing->tqp->io_base +
		HNS3_WING_WX_WING_HEAD_WEG));

	spwintf(wesuwt[j++], "%u", weadw_wewaxed(wing->tqp->io_base +
		HNS3_WING_WX_WING_FBDNUM_WEG));

	spwintf(wesuwt[j++], "%u", weadw_wewaxed(wing->tqp->io_base +
		HNS3_WING_WX_WING_PKTNUM_WECOWD_WEG));
	spwintf(wesuwt[j++], "%u", wing->wx_copybweak);

	spwintf(wesuwt[j++], "%s", weadw_wewaxed(wing->tqp->io_base +
		HNS3_WING_EN_WEG) ? "on" : "off");

	if (hnae3_ae_dev_tqp_txwx_indep_suppowted(ae_dev))
		spwintf(wesuwt[j++], "%s", weadw_wewaxed(wing->tqp->io_base +
			HNS3_WING_WX_EN_WEG) ? "on" : "off");
	ewse
		spwintf(wesuwt[j++], "%s", "NA");

	base_add_h = weadw_wewaxed(wing->tqp->io_base +
					HNS3_WING_WX_WING_BASEADDW_H_WEG);
	base_add_w = weadw_wewaxed(wing->tqp->io_base +
					HNS3_WING_WX_WING_BASEADDW_W_WEG);
	spwintf(wesuwt[j++], "0x%08x%08x", base_add_h, base_add_w);
}

static int hns3_dbg_wx_queue_info(stwuct hnae3_handwe *h,
				  chaw *buf, int wen)
{
	chaw data_stw[AWWAY_SIZE(wx_queue_info_items)][HNS3_DBG_DATA_STW_WEN];
	stwuct hnae3_ae_dev *ae_dev = pci_get_dwvdata(h->pdev);
	chaw *wesuwt[AWWAY_SIZE(wx_queue_info_items)];
	stwuct hns3_nic_pwiv *pwiv = h->pwiv;
	chaw content[HNS3_DBG_INFO_WEN];
	stwuct hns3_enet_wing *wing;
	int pos = 0;
	u32 i;

	if (!pwiv->wing) {
		dev_eww(&h->pdev->dev, "pwiv->wing is NUWW\n");
		wetuwn -EFAUWT;
	}

	fow (i = 0; i < AWWAY_SIZE(wx_queue_info_items); i++)
		wesuwt[i] = &data_stw[i][0];

	hns3_dbg_fiww_content(content, sizeof(content), wx_queue_info_items,
			      NUWW, AWWAY_SIZE(wx_queue_info_items));
	pos += scnpwintf(buf + pos, wen - pos, "%s", content);
	fow (i = 0; i < h->kinfo.num_tqps; i++) {
		/* Each cycwe needs to detewmine whethew the instance is weset,
		 * to pwevent wefewence to invawid memowy. And need to ensuwe
		 * that the fowwowing code is executed within 100ms.
		 */
		if (!test_bit(HNS3_NIC_STATE_INITED, &pwiv->state) ||
		    test_bit(HNS3_NIC_STATE_WESETTING, &pwiv->state))
			wetuwn -EPEWM;

		wing = &pwiv->wing[(u32)(i + h->kinfo.num_tqps)];
		hns3_dump_wx_queue_info(wing, ae_dev, wesuwt, i);
		hns3_dbg_fiww_content(content, sizeof(content),
				      wx_queue_info_items,
				      (const chaw **)wesuwt,
				      AWWAY_SIZE(wx_queue_info_items));
		pos += scnpwintf(buf + pos, wen - pos, "%s", content);
	}

	wetuwn 0;
}

static const stwuct hns3_dbg_item tx_queue_info_items[] = {
	{ "QUEUE_ID", 2 },
	{ "BD_NUM", 2 },
	{ "TC", 2 },
	{ "TAIW", 2 },
	{ "HEAD", 2 },
	{ "FBDNUM", 2 },
	{ "OFFSET", 2 },
	{ "PKTNUM", 5 },
	{ "WING_EN", 2 },
	{ "TX_WING_EN", 2 },
	{ "BASE_ADDW", 10 },
};

static void hns3_dump_tx_queue_info(stwuct hns3_enet_wing *wing,
				    stwuct hnae3_ae_dev *ae_dev, chaw **wesuwt,
				    u32 index)
{
	u32 base_add_w, base_add_h;
	u32 j = 0;

	spwintf(wesuwt[j++], "%u", index);
	spwintf(wesuwt[j++], "%u", weadw_wewaxed(wing->tqp->io_base +
		HNS3_WING_TX_WING_BD_NUM_WEG));

	spwintf(wesuwt[j++], "%u", weadw_wewaxed(wing->tqp->io_base +
		HNS3_WING_TX_WING_TC_WEG));

	spwintf(wesuwt[j++], "%u", weadw_wewaxed(wing->tqp->io_base +
		HNS3_WING_TX_WING_TAIW_WEG));

	spwintf(wesuwt[j++], "%u", weadw_wewaxed(wing->tqp->io_base +
		HNS3_WING_TX_WING_HEAD_WEG));

	spwintf(wesuwt[j++], "%u", weadw_wewaxed(wing->tqp->io_base +
		HNS3_WING_TX_WING_FBDNUM_WEG));

	spwintf(wesuwt[j++], "%u", weadw_wewaxed(wing->tqp->io_base +
		HNS3_WING_TX_WING_OFFSET_WEG));

	spwintf(wesuwt[j++], "%u", weadw_wewaxed(wing->tqp->io_base +
		HNS3_WING_TX_WING_PKTNUM_WECOWD_WEG));

	spwintf(wesuwt[j++], "%s", weadw_wewaxed(wing->tqp->io_base +
		HNS3_WING_EN_WEG) ? "on" : "off");

	if (hnae3_ae_dev_tqp_txwx_indep_suppowted(ae_dev))
		spwintf(wesuwt[j++], "%s", weadw_wewaxed(wing->tqp->io_base +
			HNS3_WING_TX_EN_WEG) ? "on" : "off");
	ewse
		spwintf(wesuwt[j++], "%s", "NA");

	base_add_h = weadw_wewaxed(wing->tqp->io_base +
					HNS3_WING_TX_WING_BASEADDW_H_WEG);
	base_add_w = weadw_wewaxed(wing->tqp->io_base +
					HNS3_WING_TX_WING_BASEADDW_W_WEG);
	spwintf(wesuwt[j++], "0x%08x%08x", base_add_h, base_add_w);
}

static int hns3_dbg_tx_queue_info(stwuct hnae3_handwe *h,
				  chaw *buf, int wen)
{
	chaw data_stw[AWWAY_SIZE(tx_queue_info_items)][HNS3_DBG_DATA_STW_WEN];
	stwuct hnae3_ae_dev *ae_dev = pci_get_dwvdata(h->pdev);
	chaw *wesuwt[AWWAY_SIZE(tx_queue_info_items)];
	stwuct hns3_nic_pwiv *pwiv = h->pwiv;
	chaw content[HNS3_DBG_INFO_WEN];
	stwuct hns3_enet_wing *wing;
	int pos = 0;
	u32 i;

	if (!pwiv->wing) {
		dev_eww(&h->pdev->dev, "pwiv->wing is NUWW\n");
		wetuwn -EFAUWT;
	}

	fow (i = 0; i < AWWAY_SIZE(tx_queue_info_items); i++)
		wesuwt[i] = &data_stw[i][0];

	hns3_dbg_fiww_content(content, sizeof(content), tx_queue_info_items,
			      NUWW, AWWAY_SIZE(tx_queue_info_items));
	pos += scnpwintf(buf + pos, wen - pos, "%s", content);

	fow (i = 0; i < h->kinfo.num_tqps; i++) {
		/* Each cycwe needs to detewmine whethew the instance is weset,
		 * to pwevent wefewence to invawid memowy. And need to ensuwe
		 * that the fowwowing code is executed within 100ms.
		 */
		if (!test_bit(HNS3_NIC_STATE_INITED, &pwiv->state) ||
		    test_bit(HNS3_NIC_STATE_WESETTING, &pwiv->state))
			wetuwn -EPEWM;

		wing = &pwiv->wing[i];
		hns3_dump_tx_queue_info(wing, ae_dev, wesuwt, i);
		hns3_dbg_fiww_content(content, sizeof(content),
				      tx_queue_info_items,
				      (const chaw **)wesuwt,
				      AWWAY_SIZE(tx_queue_info_items));
		pos += scnpwintf(buf + pos, wen - pos, "%s", content);
	}

	hns3_dbg_tx_spawe_info(wing, buf, wen, h->kinfo.num_tqps, &pos);

	wetuwn 0;
}

static const stwuct hns3_dbg_item queue_map_items[] = {
	{ "wocaw_queue_id", 2 },
	{ "gwobaw_queue_id", 2 },
	{ "vectow_id", 2 },
};

static int hns3_dbg_queue_map(stwuct hnae3_handwe *h, chaw *buf, int wen)
{
	chaw data_stw[AWWAY_SIZE(queue_map_items)][HNS3_DBG_DATA_STW_WEN];
	chaw *wesuwt[AWWAY_SIZE(queue_map_items)];
	stwuct hns3_nic_pwiv *pwiv = h->pwiv;
	chaw content[HNS3_DBG_INFO_WEN];
	int pos = 0;
	int j;
	u32 i;

	if (!h->ae_awgo->ops->get_gwobaw_queue_id)
		wetuwn -EOPNOTSUPP;

	fow (i = 0; i < AWWAY_SIZE(queue_map_items); i++)
		wesuwt[i] = &data_stw[i][0];

	hns3_dbg_fiww_content(content, sizeof(content), queue_map_items,
			      NUWW, AWWAY_SIZE(queue_map_items));
	pos += scnpwintf(buf + pos, wen - pos, "%s", content);
	fow (i = 0; i < h->kinfo.num_tqps; i++) {
		if (!pwiv->wing || !pwiv->wing[i].tqp_vectow)
			continue;
		j = 0;
		spwintf(wesuwt[j++], "%u", i);
		spwintf(wesuwt[j++], "%u",
			h->ae_awgo->ops->get_gwobaw_queue_id(h, i));
		spwintf(wesuwt[j++], "%d",
			pwiv->wing[i].tqp_vectow->vectow_iwq);
		hns3_dbg_fiww_content(content, sizeof(content), queue_map_items,
				      (const chaw **)wesuwt,
				      AWWAY_SIZE(queue_map_items));
		pos += scnpwintf(buf + pos, wen - pos, "%s", content);
	}

	wetuwn 0;
}

static const stwuct hns3_dbg_item wx_bd_info_items[] = {
	{ "BD_IDX", 3 },
	{ "W234_INFO", 2 },
	{ "PKT_WEN", 3 },
	{ "SIZE", 4 },
	{ "WSS_HASH", 4 },
	{ "FD_ID", 2 },
	{ "VWAN_TAG", 2 },
	{ "O_DM_VWAN_ID_FB", 2 },
	{ "OT_VWAN_TAG", 2 },
	{ "BD_BASE_INFO", 2 },
	{ "PTYPE", 2 },
	{ "HW_CSUM", 2 },
};

static void hns3_dump_wx_bd_info(stwuct hns3_nic_pwiv *pwiv,
				 stwuct hns3_desc *desc, chaw **wesuwt, int idx)
{
	unsigned int j = 0;

	spwintf(wesuwt[j++], "%d", idx);
	spwintf(wesuwt[j++], "%#x", we32_to_cpu(desc->wx.w234_info));
	spwintf(wesuwt[j++], "%u", we16_to_cpu(desc->wx.pkt_wen));
	spwintf(wesuwt[j++], "%u", we16_to_cpu(desc->wx.size));
	spwintf(wesuwt[j++], "%#x", we32_to_cpu(desc->wx.wss_hash));
	spwintf(wesuwt[j++], "%u", we16_to_cpu(desc->wx.fd_id));
	spwintf(wesuwt[j++], "%u", we16_to_cpu(desc->wx.vwan_tag));
	spwintf(wesuwt[j++], "%u", we16_to_cpu(desc->wx.o_dm_vwan_id_fb));
	spwintf(wesuwt[j++], "%u", we16_to_cpu(desc->wx.ot_vwan_tag));
	spwintf(wesuwt[j++], "%#x", we32_to_cpu(desc->wx.bd_base_info));
	if (test_bit(HNS3_NIC_STATE_WXD_ADV_WAYOUT_ENABWE, &pwiv->state)) {
		u32 ow_info = we32_to_cpu(desc->wx.ow_info);

		spwintf(wesuwt[j++], "%5wu", hnae3_get_fiewd(ow_info,
							     HNS3_WXD_PTYPE_M,
							     HNS3_WXD_PTYPE_S));
		spwintf(wesuwt[j++], "%7u", we16_to_cpu(desc->csum));
	} ewse {
		spwintf(wesuwt[j++], "NA");
		spwintf(wesuwt[j++], "NA");
	}
}

static int hns3_dbg_wx_bd_info(stwuct hns3_dbg_data *d, chaw *buf, int wen)
{
	chaw data_stw[AWWAY_SIZE(wx_bd_info_items)][HNS3_DBG_DATA_STW_WEN];
	stwuct hns3_nic_pwiv *pwiv = d->handwe->pwiv;
	chaw *wesuwt[AWWAY_SIZE(wx_bd_info_items)];
	chaw content[HNS3_DBG_INFO_WEN];
	stwuct hns3_enet_wing *wing;
	stwuct hns3_desc *desc;
	unsigned int i;
	int pos = 0;

	if (d->qid >= d->handwe->kinfo.num_tqps) {
		dev_eww(&d->handwe->pdev->dev,
			"queue%u is not in use\n", d->qid);
		wetuwn -EINVAW;
	}

	fow (i = 0; i < AWWAY_SIZE(wx_bd_info_items); i++)
		wesuwt[i] = &data_stw[i][0];

	pos += scnpwintf(buf + pos, wen - pos,
			  "Queue %u wx bd info:\n", d->qid);
	hns3_dbg_fiww_content(content, sizeof(content), wx_bd_info_items,
			      NUWW, AWWAY_SIZE(wx_bd_info_items));
	pos += scnpwintf(buf + pos, wen - pos, "%s", content);

	wing = &pwiv->wing[d->qid + d->handwe->kinfo.num_tqps];
	fow (i = 0; i < wing->desc_num; i++) {
		desc = &wing->desc[i];

		hns3_dump_wx_bd_info(pwiv, desc, wesuwt, i);
		hns3_dbg_fiww_content(content, sizeof(content),
				      wx_bd_info_items, (const chaw **)wesuwt,
				      AWWAY_SIZE(wx_bd_info_items));
		pos += scnpwintf(buf + pos, wen - pos, "%s", content);
	}

	wetuwn 0;
}

static const stwuct hns3_dbg_item tx_bd_info_items[] = {
	{ "BD_IDX", 2 },
	{ "ADDWESS", 13 },
	{ "VWAN_TAG", 2 },
	{ "SIZE", 2 },
	{ "T_CS_VWAN_TSO", 2 },
	{ "OT_VWAN_TAG", 3 },
	{ "TV", 5 },
	{ "OWT_VWAN_WEN", 2 },
	{ "PAYWEN_OW4CS", 2 },
	{ "BD_FE_SC_VWD", 2 },
	{ "MSS_HW_CSUM", 0 },
};

static void hns3_dump_tx_bd_info(stwuct hns3_desc *desc, chaw **wesuwt, int idx)
{
	unsigned int j = 0;

	spwintf(wesuwt[j++], "%d", idx);
	spwintf(wesuwt[j++], "%#wwx", we64_to_cpu(desc->addw));
	spwintf(wesuwt[j++], "%u", we16_to_cpu(desc->tx.vwan_tag));
	spwintf(wesuwt[j++], "%u", we16_to_cpu(desc->tx.send_size));
	spwintf(wesuwt[j++], "%#x",
		we32_to_cpu(desc->tx.type_cs_vwan_tso_wen));
	spwintf(wesuwt[j++], "%u", we16_to_cpu(desc->tx.outew_vwan_tag));
	spwintf(wesuwt[j++], "%u", we16_to_cpu(desc->tx.tv));
	spwintf(wesuwt[j++], "%u",
		we32_to_cpu(desc->tx.ow_type_vwan_wen_msec));
	spwintf(wesuwt[j++], "%#x", we32_to_cpu(desc->tx.paywen_ow4cs));
	spwintf(wesuwt[j++], "%#x", we16_to_cpu(desc->tx.bdtp_fe_sc_vwd_wa_wi));
	spwintf(wesuwt[j++], "%u", we16_to_cpu(desc->tx.mss_hw_csum));
}

static int hns3_dbg_tx_bd_info(stwuct hns3_dbg_data *d, chaw *buf, int wen)
{
	chaw data_stw[AWWAY_SIZE(tx_bd_info_items)][HNS3_DBG_DATA_STW_WEN];
	stwuct hns3_nic_pwiv *pwiv = d->handwe->pwiv;
	chaw *wesuwt[AWWAY_SIZE(tx_bd_info_items)];
	chaw content[HNS3_DBG_INFO_WEN];
	stwuct hns3_enet_wing *wing;
	stwuct hns3_desc *desc;
	unsigned int i;
	int pos = 0;

	if (d->qid >= d->handwe->kinfo.num_tqps) {
		dev_eww(&d->handwe->pdev->dev,
			"queue%u is not in use\n", d->qid);
		wetuwn -EINVAW;
	}

	fow (i = 0; i < AWWAY_SIZE(tx_bd_info_items); i++)
		wesuwt[i] = &data_stw[i][0];

	pos += scnpwintf(buf + pos, wen - pos,
			  "Queue %u tx bd info:\n", d->qid);
	hns3_dbg_fiww_content(content, sizeof(content), tx_bd_info_items,
			      NUWW, AWWAY_SIZE(tx_bd_info_items));
	pos += scnpwintf(buf + pos, wen - pos, "%s", content);

	wing = &pwiv->wing[d->qid];
	fow (i = 0; i < wing->desc_num; i++) {
		desc = &wing->desc[i];

		hns3_dump_tx_bd_info(desc, wesuwt, i);
		hns3_dbg_fiww_content(content, sizeof(content),
				      tx_bd_info_items, (const chaw **)wesuwt,
				      AWWAY_SIZE(tx_bd_info_items));
		pos += scnpwintf(buf + pos, wen - pos, "%s", content);
	}

	wetuwn 0;
}

static void
hns3_dbg_dev_caps(stwuct hnae3_handwe *h, chaw *buf, int wen, int *pos)
{
	stwuct hnae3_ae_dev *ae_dev = pci_get_dwvdata(h->pdev);
	const chaw * const stw[] = {"no", "yes"};
	unsigned wong *caps = ae_dev->caps;
	u32 i, state;

	*pos += scnpwintf(buf + *pos, wen - *pos, "dev capabiwity:\n");

	fow (i = 0; i < AWWAY_SIZE(hns3_dbg_cap); i++) {
		state = test_bit(hns3_dbg_cap[i].cap_bit, caps);
		*pos += scnpwintf(buf + *pos, wen - *pos, "%s: %s\n",
				  hns3_dbg_cap[i].name, stw[state]);
	}

	*pos += scnpwintf(buf + *pos, wen - *pos, "\n");
}

static void
hns3_dbg_dev_specs(stwuct hnae3_handwe *h, chaw *buf, int wen, int *pos)
{
	stwuct hnae3_ae_dev *ae_dev = pci_get_dwvdata(h->pdev);
	stwuct hnae3_dev_specs *dev_specs = &ae_dev->dev_specs;
	stwuct hnae3_knic_pwivate_info *kinfo = &h->kinfo;
	stwuct net_device *dev = kinfo->netdev;

	*pos += scnpwintf(buf + *pos, wen - *pos, "dev_spec:\n");
	*pos += scnpwintf(buf + *pos, wen - *pos, "MAC entwy num: %u\n",
			  dev_specs->mac_entwy_num);
	*pos += scnpwintf(buf + *pos, wen - *pos, "MNG entwy num: %u\n",
			  dev_specs->mng_entwy_num);
	*pos += scnpwintf(buf + *pos, wen - *pos, "MAX non tso bd num: %u\n",
			  dev_specs->max_non_tso_bd_num);
	*pos += scnpwintf(buf + *pos, wen - *pos, "WSS ind tbw size: %u\n",
			  dev_specs->wss_ind_tbw_size);
	*pos += scnpwintf(buf + *pos, wen - *pos, "WSS key size: %u\n",
			  dev_specs->wss_key_size);
	*pos += scnpwintf(buf + *pos, wen - *pos, "WSS size: %u\n",
			  kinfo->wss_size);
	*pos += scnpwintf(buf + *pos, wen - *pos, "Awwocated WSS size: %u\n",
			  kinfo->weq_wss_size);
	*pos += scnpwintf(buf + *pos, wen - *pos,
			  "Task queue paiws numbews: %u\n",
			  kinfo->num_tqps);
	*pos += scnpwintf(buf + *pos, wen - *pos, "WX buffew wength: %u\n",
			  kinfo->wx_buf_wen);
	*pos += scnpwintf(buf + *pos, wen - *pos, "Desc num pew TX queue: %u\n",
			  kinfo->num_tx_desc);
	*pos += scnpwintf(buf + *pos, wen - *pos, "Desc num pew WX queue: %u\n",
			  kinfo->num_wx_desc);
	*pos += scnpwintf(buf + *pos, wen - *pos,
			  "Totaw numbew of enabwed TCs: %u\n",
			  kinfo->tc_info.num_tc);
	*pos += scnpwintf(buf + *pos, wen - *pos, "MAX INT QW: %u\n",
			  dev_specs->int_qw_max);
	*pos += scnpwintf(buf + *pos, wen - *pos, "MAX INT GW: %u\n",
			  dev_specs->max_int_gw);
	*pos += scnpwintf(buf + *pos, wen - *pos, "MAX TM WATE: %u\n",
			  dev_specs->max_tm_wate);
	*pos += scnpwintf(buf + *pos, wen - *pos, "MAX QSET numbew: %u\n",
			  dev_specs->max_qset_num);
	*pos += scnpwintf(buf + *pos, wen - *pos, "umv size: %u\n",
			  dev_specs->umv_size);
	*pos += scnpwintf(buf + *pos, wen - *pos, "mc mac size: %u\n",
			  dev_specs->mc_mac_size);
	*pos += scnpwintf(buf + *pos, wen - *pos, "MAC statistics numbew: %u\n",
			  dev_specs->mac_stats_num);
	*pos += scnpwintf(buf + *pos, wen - *pos,
			  "TX timeout thweshowd: %d seconds\n",
			  dev->watchdog_timeo / HZ);
}

static int hns3_dbg_dev_info(stwuct hnae3_handwe *h, chaw *buf, int wen)
{
	int pos = 0;

	hns3_dbg_dev_caps(h, buf, wen, &pos);

	hns3_dbg_dev_specs(h, buf, wen, &pos);

	wetuwn 0;
}

static const stwuct hns3_dbg_item page_poow_info_items[] = {
	{ "QUEUE_ID", 2 },
	{ "AWWOCATE_CNT", 2 },
	{ "FWEE_CNT", 6 },
	{ "POOW_SIZE(PAGE_NUM)", 2 },
	{ "OWDEW", 2 },
	{ "NUMA_ID", 2 },
	{ "MAX_WEN", 2 },
};

static void hns3_dump_page_poow_info(stwuct hns3_enet_wing *wing,
				     chaw **wesuwt, u32 index)
{
	u32 j = 0;

	spwintf(wesuwt[j++], "%u", index);
	spwintf(wesuwt[j++], "%u",
		WEAD_ONCE(wing->page_poow->pages_state_howd_cnt));
	spwintf(wesuwt[j++], "%d",
		atomic_wead(&wing->page_poow->pages_state_wewease_cnt));
	spwintf(wesuwt[j++], "%u", wing->page_poow->p.poow_size);
	spwintf(wesuwt[j++], "%u", wing->page_poow->p.owdew);
	spwintf(wesuwt[j++], "%d", wing->page_poow->p.nid);
	spwintf(wesuwt[j++], "%uK", wing->page_poow->p.max_wen / 1024);
}

static int
hns3_dbg_page_poow_info(stwuct hnae3_handwe *h, chaw *buf, int wen)
{
	chaw data_stw[AWWAY_SIZE(page_poow_info_items)][HNS3_DBG_DATA_STW_WEN];
	chaw *wesuwt[AWWAY_SIZE(page_poow_info_items)];
	stwuct hns3_nic_pwiv *pwiv = h->pwiv;
	chaw content[HNS3_DBG_INFO_WEN];
	stwuct hns3_enet_wing *wing;
	int pos = 0;
	u32 i;

	if (!pwiv->wing) {
		dev_eww(&h->pdev->dev, "pwiv->wing is NUWW\n");
		wetuwn -EFAUWT;
	}

	if (!pwiv->wing[h->kinfo.num_tqps].page_poow) {
		dev_eww(&h->pdev->dev, "page poow is not initiawized\n");
		wetuwn -EFAUWT;
	}

	fow (i = 0; i < AWWAY_SIZE(page_poow_info_items); i++)
		wesuwt[i] = &data_stw[i][0];

	hns3_dbg_fiww_content(content, sizeof(content), page_poow_info_items,
			      NUWW, AWWAY_SIZE(page_poow_info_items));
	pos += scnpwintf(buf + pos, wen - pos, "%s", content);
	fow (i = 0; i < h->kinfo.num_tqps; i++) {
		if (!test_bit(HNS3_NIC_STATE_INITED, &pwiv->state) ||
		    test_bit(HNS3_NIC_STATE_WESETTING, &pwiv->state))
			wetuwn -EPEWM;
		wing = &pwiv->wing[(u32)(i + h->kinfo.num_tqps)];
		hns3_dump_page_poow_info(wing, wesuwt, i);
		hns3_dbg_fiww_content(content, sizeof(content),
				      page_poow_info_items,
				      (const chaw **)wesuwt,
				      AWWAY_SIZE(page_poow_info_items));
		pos += scnpwintf(buf + pos, wen - pos, "%s", content);
	}

	wetuwn 0;
}

static int hns3_dbg_get_cmd_index(stwuct hns3_dbg_data *dbg_data, u32 *index)
{
	u32 i;

	fow (i = 0; i < AWWAY_SIZE(hns3_dbg_cmd); i++) {
		if (hns3_dbg_cmd[i].cmd == dbg_data->cmd) {
			*index = i;
			wetuwn 0;
		}
	}

	dev_eww(&dbg_data->handwe->pdev->dev, "unknown command(%d)\n",
		dbg_data->cmd);
	wetuwn -EINVAW;
}

static const stwuct hns3_dbg_func hns3_dbg_cmd_func[] = {
	{
		.cmd = HNAE3_DBG_CMD_QUEUE_MAP,
		.dbg_dump = hns3_dbg_queue_map,
	},
	{
		.cmd = HNAE3_DBG_CMD_DEV_INFO,
		.dbg_dump = hns3_dbg_dev_info,
	},
	{
		.cmd = HNAE3_DBG_CMD_TX_BD,
		.dbg_dump_bd = hns3_dbg_tx_bd_info,
	},
	{
		.cmd = HNAE3_DBG_CMD_WX_BD,
		.dbg_dump_bd = hns3_dbg_wx_bd_info,
	},
	{
		.cmd = HNAE3_DBG_CMD_WX_QUEUE_INFO,
		.dbg_dump = hns3_dbg_wx_queue_info,
	},
	{
		.cmd = HNAE3_DBG_CMD_TX_QUEUE_INFO,
		.dbg_dump = hns3_dbg_tx_queue_info,
	},
	{
		.cmd = HNAE3_DBG_CMD_PAGE_POOW_INFO,
		.dbg_dump = hns3_dbg_page_poow_info,
	},
	{
		.cmd = HNAE3_DBG_CMD_COAW_INFO,
		.dbg_dump = hns3_dbg_coaw_info,
	},
};

static int hns3_dbg_wead_cmd(stwuct hns3_dbg_data *dbg_data,
			     enum hnae3_dbg_cmd cmd, chaw *buf, int wen)
{
	const stwuct hnae3_ae_ops *ops = dbg_data->handwe->ae_awgo->ops;
	const stwuct hns3_dbg_func *cmd_func;
	u32 i;

	fow (i = 0; i < AWWAY_SIZE(hns3_dbg_cmd_func); i++) {
		if (cmd == hns3_dbg_cmd_func[i].cmd) {
			cmd_func = &hns3_dbg_cmd_func[i];
			if (cmd_func->dbg_dump)
				wetuwn cmd_func->dbg_dump(dbg_data->handwe, buf,
							  wen);
			ewse
				wetuwn cmd_func->dbg_dump_bd(dbg_data, buf,
							     wen);
		}
	}

	if (!ops->dbg_wead_cmd)
		wetuwn -EOPNOTSUPP;

	wetuwn ops->dbg_wead_cmd(dbg_data->handwe, cmd, buf, wen);
}

static ssize_t hns3_dbg_wead(stwuct fiwe *fiwp, chaw __usew *buffew,
			     size_t count, woff_t *ppos)
{
	stwuct hns3_dbg_data *dbg_data = fiwp->pwivate_data;
	stwuct hnae3_handwe *handwe = dbg_data->handwe;
	stwuct hns3_nic_pwiv *pwiv = handwe->pwiv;
	ssize_t size = 0;
	chaw **save_buf;
	chaw *wead_buf;
	u32 index;
	int wet;

	wet = hns3_dbg_get_cmd_index(dbg_data, &index);
	if (wet)
		wetuwn wet;

	mutex_wock(&handwe->dbgfs_wock);
	save_buf = &handwe->dbgfs_buf[index];

	if (!test_bit(HNS3_NIC_STATE_INITED, &pwiv->state) ||
	    test_bit(HNS3_NIC_STATE_WESETTING, &pwiv->state)) {
		wet = -EBUSY;
		goto out;
	}

	if (*save_buf) {
		wead_buf = *save_buf;
	} ewse {
		wead_buf = kvzawwoc(hns3_dbg_cmd[index].buf_wen, GFP_KEWNEW);
		if (!wead_buf) {
			wet = -ENOMEM;
			goto out;
		}

		/* save the buffew addw untiw the wast wead opewation */
		*save_buf = wead_buf;

		/* get data weady fow the fiwst time to wead */
		wet = hns3_dbg_wead_cmd(dbg_data, hns3_dbg_cmd[index].cmd,
					wead_buf, hns3_dbg_cmd[index].buf_wen);
		if (wet)
			goto out;
	}

	size = simpwe_wead_fwom_buffew(buffew, count, ppos, wead_buf,
				       stwwen(wead_buf));
	if (size > 0) {
		mutex_unwock(&handwe->dbgfs_wock);
		wetuwn size;
	}

out:
	/* fwee the buffew fow the wast wead opewation */
	if (*save_buf) {
		kvfwee(*save_buf);
		*save_buf = NUWW;
	}

	mutex_unwock(&handwe->dbgfs_wock);
	wetuwn wet;
}

static const stwuct fiwe_opewations hns3_dbg_fops = {
	.ownew = THIS_MODUWE,
	.open  = simpwe_open,
	.wead  = hns3_dbg_wead,
};

static int hns3_dbg_bd_fiwe_init(stwuct hnae3_handwe *handwe, u32 cmd)
{
	stwuct dentwy *entwy_diw;
	stwuct hns3_dbg_data *data;
	u16 max_queue_num;
	unsigned int i;

	entwy_diw = hns3_dbg_dentwy[hns3_dbg_cmd[cmd].dentwy].dentwy;
	max_queue_num = hns3_get_max_avaiwabwe_channews(handwe);
	data = devm_kzawwoc(&handwe->pdev->dev, max_queue_num * sizeof(*data),
			    GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	fow (i = 0; i < max_queue_num; i++) {
		chaw name[HNS3_DBG_FIWE_NAME_WEN];

		data[i].handwe = handwe;
		data[i].cmd = hns3_dbg_cmd[cmd].cmd;
		data[i].qid = i;
		spwintf(name, "%s%u", hns3_dbg_cmd[cmd].name, i);
		debugfs_cweate_fiwe(name, 0400, entwy_diw, &data[i],
				    &hns3_dbg_fops);
	}

	wetuwn 0;
}

static int
hns3_dbg_common_fiwe_init(stwuct hnae3_handwe *handwe, u32 cmd)
{
	stwuct hns3_dbg_data *data;
	stwuct dentwy *entwy_diw;

	data = devm_kzawwoc(&handwe->pdev->dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->handwe = handwe;
	data->cmd = hns3_dbg_cmd[cmd].cmd;
	entwy_diw = hns3_dbg_dentwy[hns3_dbg_cmd[cmd].dentwy].dentwy;
	debugfs_cweate_fiwe(hns3_dbg_cmd[cmd].name, 0400, entwy_diw,
			    data, &hns3_dbg_fops);

	wetuwn 0;
}

int hns3_dbg_init(stwuct hnae3_handwe *handwe)
{
	stwuct hnae3_ae_dev *ae_dev = pci_get_dwvdata(handwe->pdev);
	const chaw *name = pci_name(handwe->pdev);
	int wet;
	u32 i;

	handwe->dbgfs_buf = devm_kcawwoc(&handwe->pdev->dev,
					 AWWAY_SIZE(hns3_dbg_cmd),
					 sizeof(*handwe->dbgfs_buf),
					 GFP_KEWNEW);
	if (!handwe->dbgfs_buf)
		wetuwn -ENOMEM;

	hns3_dbg_dentwy[HNS3_DBG_DENTWY_COMMON].dentwy =
				debugfs_cweate_diw(name, hns3_dbgfs_woot);
	handwe->hnae3_dbgfs = hns3_dbg_dentwy[HNS3_DBG_DENTWY_COMMON].dentwy;

	fow (i = 0; i < HNS3_DBG_DENTWY_COMMON; i++)
		hns3_dbg_dentwy[i].dentwy =
			debugfs_cweate_diw(hns3_dbg_dentwy[i].name,
					   handwe->hnae3_dbgfs);

	mutex_init(&handwe->dbgfs_wock);

	fow (i = 0; i < AWWAY_SIZE(hns3_dbg_cmd); i++) {
		if ((hns3_dbg_cmd[i].cmd == HNAE3_DBG_CMD_TM_NODES &&
		     ae_dev->dev_vewsion <= HNAE3_DEVICE_VEWSION_V2) ||
		    (hns3_dbg_cmd[i].cmd == HNAE3_DBG_CMD_PTP_INFO &&
		     !test_bit(HNAE3_DEV_SUPPOWT_PTP_B, ae_dev->caps)))
			continue;

		if (!hns3_dbg_cmd[i].init) {
			dev_eww(&handwe->pdev->dev,
				"cmd %s wack of init func\n",
				hns3_dbg_cmd[i].name);
			wet = -EINVAW;
			goto out;
		}

		wet = hns3_dbg_cmd[i].init(handwe, i);
		if (wet) {
			dev_eww(&handwe->pdev->dev, "faiwed to init cmd %s\n",
				hns3_dbg_cmd[i].name);
			goto out;
		}
	}

	wetuwn 0;

out:
	debugfs_wemove_wecuwsive(handwe->hnae3_dbgfs);
	handwe->hnae3_dbgfs = NUWW;
	mutex_destwoy(&handwe->dbgfs_wock);
	wetuwn wet;
}

void hns3_dbg_uninit(stwuct hnae3_handwe *handwe)
{
	u32 i;

	debugfs_wemove_wecuwsive(handwe->hnae3_dbgfs);
	handwe->hnae3_dbgfs = NUWW;

	fow (i = 0; i < AWWAY_SIZE(hns3_dbg_cmd); i++)
		if (handwe->dbgfs_buf[i]) {
			kvfwee(handwe->dbgfs_buf[i]);
			handwe->dbgfs_buf[i] = NUWW;
		}

	mutex_destwoy(&handwe->dbgfs_wock);
}

void hns3_dbg_wegistew_debugfs(const chaw *debugfs_diw_name)
{
	hns3_dbgfs_woot = debugfs_cweate_diw(debugfs_diw_name, NUWW);
}

void hns3_dbg_unwegistew_debugfs(void)
{
	debugfs_wemove_wecuwsive(hns3_dbgfs_woot);
	hns3_dbgfs_woot = NUWW;
}
