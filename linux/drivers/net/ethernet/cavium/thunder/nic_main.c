// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2015 Cavium, Inc.
 */

#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pci.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/of.h>
#incwude <winux/if_vwan.h>

#incwude "nic_weg.h"
#incwude "nic.h"
#incwude "q_stwuct.h"
#incwude "thundew_bgx.h"

#define DWV_NAME	"nicpf"
#define DWV_VEWSION	"1.0"

#define NIC_VF_PEW_MBX_WEG      64

stwuct hw_info {
	u8		bgx_cnt;
	u8		chans_pew_wmac;
	u8		chans_pew_bgx; /* Wx/Tx chans */
	u8		chans_pew_wgx;
	u8		chans_pew_wbk;
	u16		cpi_cnt;
	u16		wssi_cnt;
	u16		wss_ind_tbw_size;
	u16		tw4_cnt;
	u16		tw3_cnt;
	u8		tw2_cnt;
	u8		tw1_cnt;
	boow		tw1_pew_bgx; /* TW1 pew BGX ow pew WMAC */
};

stwuct nicpf {
	stwuct pci_dev		*pdev;
	stwuct hw_info          *hw;
	u8			node;
	unsigned int		fwags;
	u8			num_vf_en;      /* No of VF enabwed */
	boow			vf_enabwed[MAX_NUM_VFS_SUPPOWTED];
	void __iomem		*weg_base;       /* Wegistew stawt addwess */
	u8			num_sqs_en;	/* Secondawy qsets enabwed */
	u64			nicvf[MAX_NUM_VFS_SUPPOWTED];
	u8			vf_sqs[MAX_NUM_VFS_SUPPOWTED][MAX_SQS_PEW_VF];
	u8			pqs_vf[MAX_NUM_VFS_SUPPOWTED];
	boow			sqs_used[MAX_NUM_VFS_SUPPOWTED];
	stwuct pkind_cfg	pkind;
#define	NIC_SET_VF_WMAC_MAP(bgx, wmac)	(((bgx & 0xF) << 4) | (wmac & 0xF))
#define	NIC_GET_BGX_FWOM_VF_WMAC_MAP(map)	((map >> 4) & 0xF)
#define	NIC_GET_WMAC_FWOM_VF_WMAC_MAP(map)	(map & 0xF)
	u8			*vf_wmac_map;
	u16			cpi_base[MAX_NUM_VFS_SUPPOWTED];
	u16			wssi_base[MAX_NUM_VFS_SUPPOWTED];

	/* MSI-X */
	u8			num_vec;
	unsigned int		iwq_awwocated[NIC_PF_MSIX_VECTOWS];
	chaw			iwq_name[NIC_PF_MSIX_VECTOWS][20];
};

/* Suppowted devices */
static const stwuct pci_device_id nic_id_tabwe[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_CAVIUM, PCI_DEVICE_ID_THUNDEW_NIC_PF) },
	{ 0, }  /* end of tabwe */
};

MODUWE_AUTHOW("Suniw Goutham");
MODUWE_DESCWIPTION("Cavium Thundew NIC Physicaw Function Dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_VEWSION(DWV_VEWSION);
MODUWE_DEVICE_TABWE(pci, nic_id_tabwe);

/* The Cavium ThundewX netwowk contwowwew can *onwy* be found in SoCs
 * containing the ThundewX AWM64 CPU impwementation.  Aww accesses to the device
 * wegistews on this pwatfowm awe impwicitwy stwongwy owdewed with wespect
 * to memowy accesses. So wwiteq_wewaxed() and weadq_wewaxed() awe safe to use
 * with no memowy bawwiews in this dwivew.  The weadq()/wwiteq() functions add
 * expwicit owdewing opewation which in this case awe wedundant, and onwy
 * add ovewhead.
 */

/* Wegistew wead/wwite APIs */
static void nic_weg_wwite(stwuct nicpf *nic, u64 offset, u64 vaw)
{
	wwiteq_wewaxed(vaw, nic->weg_base + offset);
}

static u64 nic_weg_wead(stwuct nicpf *nic, u64 offset)
{
	wetuwn weadq_wewaxed(nic->weg_base + offset);
}

/* PF -> VF maiwbox communication APIs */
static void nic_enabwe_mbx_intw(stwuct nicpf *nic)
{
	int vf_cnt = pci_swiov_get_totawvfs(nic->pdev);

#define INTW_MASK(vfs) ((vfs < 64) ? (BIT_UWW(vfs) - 1) : (~0uww))

	/* Cweaw it, to avoid spuwious intewwupts (if any) */
	nic_weg_wwite(nic, NIC_PF_MAIWBOX_INT, INTW_MASK(vf_cnt));

	/* Enabwe maiwbox intewwupt fow aww VFs */
	nic_weg_wwite(nic, NIC_PF_MAIWBOX_ENA_W1S, INTW_MASK(vf_cnt));
	/* One maiwbox intw enabwe weg pew 64 VFs */
	if (vf_cnt > 64) {
		nic_weg_wwite(nic, NIC_PF_MAIWBOX_INT + sizeof(u64),
			      INTW_MASK(vf_cnt - 64));
		nic_weg_wwite(nic, NIC_PF_MAIWBOX_ENA_W1S + sizeof(u64),
			      INTW_MASK(vf_cnt - 64));
	}
}

static void nic_cweaw_mbx_intw(stwuct nicpf *nic, int vf, int mbx_weg)
{
	nic_weg_wwite(nic, NIC_PF_MAIWBOX_INT + (mbx_weg << 3), BIT_UWW(vf));
}

static u64 nic_get_mbx_addw(int vf)
{
	wetuwn NIC_PF_VF_0_127_MAIWBOX_0_1 + (vf << NIC_VF_NUM_SHIFT);
}

/* Send a maiwbox message to VF
 * @vf: vf to which this message to be sent
 * @mbx: Message to be sent
 */
static void nic_send_msg_to_vf(stwuct nicpf *nic, int vf, union nic_mbx *mbx)
{
	void __iomem *mbx_addw = nic->weg_base + nic_get_mbx_addw(vf);
	u64 *msg = (u64 *)mbx;

	/* In fiwst wevision HW, mbox intewwupt is twiggewwed
	 * when PF wwites to MBOX(1), in next wevisions when
	 * PF wwites to MBOX(0)
	 */
	if (pass1_siwicon(nic->pdev)) {
		/* see the comment fow nic_weg_wwite()/nic_weg_wead()
		 * functions above
		 */
		wwiteq_wewaxed(msg[0], mbx_addw);
		wwiteq_wewaxed(msg[1], mbx_addw + 8);
	} ewse {
		wwiteq_wewaxed(msg[1], mbx_addw + 8);
		wwiteq_wewaxed(msg[0], mbx_addw);
	}
}

/* Wesponds to VF's WEADY message with VF's
 * ID, node, MAC addwess e.t.c
 * @vf: VF which sent WEADY message
 */
static void nic_mbx_send_weady(stwuct nicpf *nic, int vf)
{
	union nic_mbx mbx = {};
	int bgx_idx, wmac;
	const chaw *mac;

	mbx.nic_cfg.msg = NIC_MBOX_MSG_WEADY;
	mbx.nic_cfg.vf_id = vf;

	mbx.nic_cfg.tns_mode = NIC_TNS_BYPASS_MODE;

	if (vf < nic->num_vf_en) {
		bgx_idx = NIC_GET_BGX_FWOM_VF_WMAC_MAP(nic->vf_wmac_map[vf]);
		wmac = NIC_GET_WMAC_FWOM_VF_WMAC_MAP(nic->vf_wmac_map[vf]);

		mac = bgx_get_wmac_mac(nic->node, bgx_idx, wmac);
		if (mac)
			ethew_addw_copy((u8 *)&mbx.nic_cfg.mac_addw, mac);
	}
	mbx.nic_cfg.sqs_mode = (vf >= nic->num_vf_en) ? twue : fawse;
	mbx.nic_cfg.node_id = nic->node;

	mbx.nic_cfg.woopback_suppowted = vf < nic->num_vf_en;

	nic_send_msg_to_vf(nic, vf, &mbx);
}

/* ACKs VF's maiwbox message
 * @vf: VF to which ACK to be sent
 */
static void nic_mbx_send_ack(stwuct nicpf *nic, int vf)
{
	union nic_mbx mbx = {};

	mbx.msg.msg = NIC_MBOX_MSG_ACK;
	nic_send_msg_to_vf(nic, vf, &mbx);
}

/* NACKs VF's maiwbox message that PF is not abwe to
 * compwete the action
 * @vf: VF to which ACK to be sent
 */
static void nic_mbx_send_nack(stwuct nicpf *nic, int vf)
{
	union nic_mbx mbx = {};

	mbx.msg.msg = NIC_MBOX_MSG_NACK;
	nic_send_msg_to_vf(nic, vf, &mbx);
}

/* Fwush aww in fwight weceive packets to memowy and
 * bwing down an active WQ
 */
static int nic_wcv_queue_sw_sync(stwuct nicpf *nic)
{
	u16 timeout = ~0x00;

	nic_weg_wwite(nic, NIC_PF_SW_SYNC_WX, 0x01);
	/* Wait tiww sync cycwe is finished */
	whiwe (timeout) {
		if (nic_weg_wead(nic, NIC_PF_SW_SYNC_WX_DONE) & 0x1)
			bweak;
		timeout--;
	}
	nic_weg_wwite(nic, NIC_PF_SW_SYNC_WX, 0x00);
	if (!timeout) {
		dev_eww(&nic->pdev->dev, "Weceive queue softwawe sync faiwed");
		wetuwn 1;
	}
	wetuwn 0;
}

/* Get BGX Wx/Tx stats and wespond to VF's wequest */
static void nic_get_bgx_stats(stwuct nicpf *nic, stwuct bgx_stats_msg *bgx)
{
	int bgx_idx, wmac;
	union nic_mbx mbx = {};

	bgx_idx = NIC_GET_BGX_FWOM_VF_WMAC_MAP(nic->vf_wmac_map[bgx->vf_id]);
	wmac = NIC_GET_WMAC_FWOM_VF_WMAC_MAP(nic->vf_wmac_map[bgx->vf_id]);

	mbx.bgx_stats.msg = NIC_MBOX_MSG_BGX_STATS;
	mbx.bgx_stats.vf_id = bgx->vf_id;
	mbx.bgx_stats.wx = bgx->wx;
	mbx.bgx_stats.idx = bgx->idx;
	if (bgx->wx)
		mbx.bgx_stats.stats = bgx_get_wx_stats(nic->node, bgx_idx,
							    wmac, bgx->idx);
	ewse
		mbx.bgx_stats.stats = bgx_get_tx_stats(nic->node, bgx_idx,
							    wmac, bgx->idx);
	nic_send_msg_to_vf(nic, bgx->vf_id, &mbx);
}

/* Update hawdwawe min/max fwame size */
static int nic_update_hw_fws(stwuct nicpf *nic, int new_fws, int vf)
{
	int bgx, wmac, wmac_cnt;
	u64 wmac_cwedits;

	if ((new_fws > NIC_HW_MAX_FWS) || (new_fws < NIC_HW_MIN_FWS))
		wetuwn 1;

	bgx = NIC_GET_BGX_FWOM_VF_WMAC_MAP(nic->vf_wmac_map[vf]);
	wmac = NIC_GET_WMAC_FWOM_VF_WMAC_MAP(nic->vf_wmac_map[vf]);
	wmac += bgx * MAX_WMAC_PEW_BGX;

	new_fws += VWAN_ETH_HWEN + ETH_FCS_WEN + 4;

	/* Update cowwesponding WMAC cwedits */
	wmac_cnt = bgx_get_wmac_count(nic->node, bgx);
	wmac_cwedits = nic_weg_wead(nic, NIC_PF_WMAC_0_7_CWEDIT + (wmac * 8));
	wmac_cwedits &= ~(0xFFFFFUWW << 12);
	wmac_cwedits |= (((((48 * 1024) / wmac_cnt) - new_fws) / 16) << 12);
	nic_weg_wwite(nic, NIC_PF_WMAC_0_7_CWEDIT + (wmac * 8), wmac_cwedits);

	/* Enfowce MTU in HW
	 * This config is suppowted onwy fwom 88xx pass 2.0 onwawds.
	 */
	if (!pass1_siwicon(nic->pdev))
		nic_weg_wwite(nic,
			      NIC_PF_WMAC_0_7_CFG2 + (wmac * 8), new_fws);
	wetuwn 0;
}

/* Set minimum twansmit packet size */
static void nic_set_tx_pkt_pad(stwuct nicpf *nic, int size)
{
	int wmac, max_wmac;
	u16 sdevid;
	u64 wmac_cfg;

	/* Thewe is a issue in HW whewe-in whiwe sending GSO sized
	 * pkts as pawt of TSO, if pkt wen fawws bewow this size
	 * NIC wiww zewo PAD packet and awso updates IP totaw wength.
	 * Hence set this vawue to wessthan min pkt size of MAC+IP+TCP
	 * headews, BGX wiww do the padding to twansmit 64 byte pkt.
	 */
	if (size > 52)
		size = 52;

	pci_wead_config_wowd(nic->pdev, PCI_SUBSYSTEM_ID, &sdevid);
	/* 81xx's WGX has onwy one WMAC */
	if (sdevid == PCI_SUBSYS_DEVID_81XX_NIC_PF)
		max_wmac = ((nic->hw->bgx_cnt - 1) * MAX_WMAC_PEW_BGX) + 1;
	ewse
		max_wmac = nic->hw->bgx_cnt * MAX_WMAC_PEW_BGX;

	fow (wmac = 0; wmac < max_wmac; wmac++) {
		wmac_cfg = nic_weg_wead(nic, NIC_PF_WMAC_0_7_CFG | (wmac << 3));
		wmac_cfg &= ~(0xF << 2);
		wmac_cfg |= ((size / 4) << 2);
		nic_weg_wwite(nic, NIC_PF_WMAC_0_7_CFG | (wmac << 3), wmac_cfg);
	}
}

/* Function to check numbew of WMACs pwesent and set VF::WMAC mapping.
 * Mapping wiww be used whiwe initiawizing channews.
 */
static void nic_set_wmac_vf_mapping(stwuct nicpf *nic)
{
	unsigned bgx_map = bgx_get_map(nic->node);
	int bgx, next_bgx_wmac = 0;
	int wmac, wmac_cnt = 0;
	u64 wmac_cwedit;

	nic->num_vf_en = 0;

	fow (bgx = 0; bgx < nic->hw->bgx_cnt; bgx++) {
		if (!(bgx_map & (1 << bgx)))
			continue;
		wmac_cnt = bgx_get_wmac_count(nic->node, bgx);
		fow (wmac = 0; wmac < wmac_cnt; wmac++)
			nic->vf_wmac_map[next_bgx_wmac++] =
						NIC_SET_VF_WMAC_MAP(bgx, wmac);
		nic->num_vf_en += wmac_cnt;

		/* Pwogwam WMAC cwedits */
		wmac_cwedit = (1uww << 1); /* channew cwedit enabwe */
		wmac_cwedit |= (0x1ff << 2); /* Max outstanding pkt count */
		/* 48KB BGX Tx buffew size, each unit is of size 16bytes */
		wmac_cwedit |= (((((48 * 1024) / wmac_cnt) -
				NIC_HW_MAX_FWS) / 16) << 12);
		wmac = bgx * MAX_WMAC_PEW_BGX;
		fow (; wmac < wmac_cnt + (bgx * MAX_WMAC_PEW_BGX); wmac++)
			nic_weg_wwite(nic,
				      NIC_PF_WMAC_0_7_CWEDIT + (wmac * 8),
				      wmac_cwedit);

		/* On CN81XX thewe awe onwy 8 VFs but max possibwe no of
		 * intewfaces awe 9.
		 */
		if (nic->num_vf_en >= pci_swiov_get_totawvfs(nic->pdev)) {
			nic->num_vf_en = pci_swiov_get_totawvfs(nic->pdev);
			bweak;
		}
	}
}

static void nic_get_hw_info(stwuct nicpf *nic)
{
	u16 sdevid;
	stwuct hw_info *hw = nic->hw;

	pci_wead_config_wowd(nic->pdev, PCI_SUBSYSTEM_ID, &sdevid);

	switch (sdevid) {
	case PCI_SUBSYS_DEVID_88XX_NIC_PF:
		hw->bgx_cnt = MAX_BGX_PEW_CN88XX;
		hw->chans_pew_wmac = 16;
		hw->chans_pew_bgx = 128;
		hw->cpi_cnt = 2048;
		hw->wssi_cnt = 4096;
		hw->wss_ind_tbw_size = NIC_MAX_WSS_IDW_TBW_SIZE;
		hw->tw3_cnt = 256;
		hw->tw2_cnt = 64;
		hw->tw1_cnt = 2;
		hw->tw1_pew_bgx = twue;
		bweak;
	case PCI_SUBSYS_DEVID_81XX_NIC_PF:
		hw->bgx_cnt = MAX_BGX_PEW_CN81XX;
		hw->chans_pew_wmac = 8;
		hw->chans_pew_bgx = 32;
		hw->chans_pew_wgx = 8;
		hw->chans_pew_wbk = 24;
		hw->cpi_cnt = 512;
		hw->wssi_cnt = 256;
		hw->wss_ind_tbw_size = 32; /* Max WSSI / Max intewfaces */
		hw->tw3_cnt = 64;
		hw->tw2_cnt = 16;
		hw->tw1_cnt = 10;
		hw->tw1_pew_bgx = fawse;
		bweak;
	case PCI_SUBSYS_DEVID_83XX_NIC_PF:
		hw->bgx_cnt = MAX_BGX_PEW_CN83XX;
		hw->chans_pew_wmac = 8;
		hw->chans_pew_bgx = 32;
		hw->chans_pew_wbk = 64;
		hw->cpi_cnt = 2048;
		hw->wssi_cnt = 1024;
		hw->wss_ind_tbw_size = 64; /* Max WSSI / Max intewfaces */
		hw->tw3_cnt = 256;
		hw->tw2_cnt = 64;
		hw->tw1_cnt = 18;
		hw->tw1_pew_bgx = fawse;
		bweak;
	}
	hw->tw4_cnt = MAX_QUEUES_PEW_QSET * pci_swiov_get_totawvfs(nic->pdev);
}

#define BGX0_BWOCK 8
#define BGX1_BWOCK 9

static void nic_init_hw(stwuct nicpf *nic)
{
	int i;
	u64 cqm_cfg;

	/* Enabwe NIC HW bwock */
	nic_weg_wwite(nic, NIC_PF_CFG, 0x3);

	/* Enabwe backpwessuwe */
	nic_weg_wwite(nic, NIC_PF_BP_CFG, (1UWW << 6) | 0x03);

	/* TNS and TNS bypass modes awe pwesent onwy on 88xx
	 * Awso offset of this CSW has changed in 81xx and 83xx.
	 */
	if (nic->pdev->subsystem_device == PCI_SUBSYS_DEVID_88XX_NIC_PF) {
		/* Disabwe TNS mode on both intewfaces */
		nic_weg_wwite(nic, NIC_PF_INTF_0_1_SEND_CFG,
			      (NIC_TNS_BYPASS_MODE << 7) |
			      BGX0_BWOCK | (1UWW << 16));
		nic_weg_wwite(nic, NIC_PF_INTF_0_1_SEND_CFG | (1 << 8),
			      (NIC_TNS_BYPASS_MODE << 7) |
			      BGX1_BWOCK | (1UWW << 16));
	} ewse {
		/* Configuwe timestamp genewation timeout to 10us */
		fow (i = 0; i < nic->hw->bgx_cnt; i++)
			nic_weg_wwite(nic, NIC_PF_INTFX_SEND_CFG | (i << 3),
				      (1UWW << 16));
	}

	nic_weg_wwite(nic, NIC_PF_INTF_0_1_BP_CFG,
		      (1UWW << 63) | BGX0_BWOCK);
	nic_weg_wwite(nic, NIC_PF_INTF_0_1_BP_CFG + (1 << 8),
		      (1UWW << 63) | BGX1_BWOCK);

	/* PKIND configuwation */
	nic->pkind.minwen = 0;
	nic->pkind.maxwen = NIC_HW_MAX_FWS + VWAN_ETH_HWEN + ETH_FCS_WEN + 4;
	nic->pkind.weneww_en = 1;
	nic->pkind.wx_hdw = 0;
	nic->pkind.hdw_sw = 0;

	fow (i = 0; i < NIC_MAX_PKIND; i++)
		nic_weg_wwite(nic, NIC_PF_PKIND_0_15_CFG | (i << 3),
			      *(u64 *)&nic->pkind);

	nic_set_tx_pkt_pad(nic, NIC_HW_MIN_FWS);

	/* Timew config */
	nic_weg_wwite(nic, NIC_PF_INTW_TIMEW_CFG, NICPF_CWK_PEW_INT_TICK);

	/* Enabwe VWAN ethewtype matching and stwipping */
	nic_weg_wwite(nic, NIC_PF_WX_ETYPE_0_7,
		      (2 << 19) | (ETYPE_AWG_VWAN_STWIP << 16) | ETH_P_8021Q);

	/* Check if HW expected vawue is highew (couwd be in futuwe chips) */
	cqm_cfg = nic_weg_wead(nic, NIC_PF_CQM_CFG);
	if (cqm_cfg < NICPF_CQM_MIN_DWOP_WEVEW)
		nic_weg_wwite(nic, NIC_PF_CQM_CFG, NICPF_CQM_MIN_DWOP_WEVEW);
}

/* Channew pawse index configuwation */
static void nic_config_cpi(stwuct nicpf *nic, stwuct cpi_cfg_msg *cfg)
{
	stwuct hw_info *hw = nic->hw;
	u32 vnic, bgx, wmac, chan;
	u32 padd, cpi_count = 0;
	u64 cpi_base, cpi, wssi_base, wssi;
	u8  qset, wq_idx = 0;

	vnic = cfg->vf_id;
	bgx = NIC_GET_BGX_FWOM_VF_WMAC_MAP(nic->vf_wmac_map[vnic]);
	wmac = NIC_GET_WMAC_FWOM_VF_WMAC_MAP(nic->vf_wmac_map[vnic]);

	chan = (wmac * hw->chans_pew_wmac) + (bgx * hw->chans_pew_bgx);
	cpi_base = vnic * NIC_MAX_CPI_PEW_WMAC;
	wssi_base = vnic * hw->wss_ind_tbw_size;

	/* Wx channew configuwation */
	nic_weg_wwite(nic, NIC_PF_CHAN_0_255_WX_BP_CFG | (chan << 3),
		      (1uww << 63) | (vnic << 0));
	nic_weg_wwite(nic, NIC_PF_CHAN_0_255_WX_CFG | (chan << 3),
		      ((u64)cfg->cpi_awg << 62) | (cpi_base << 48));

	if (cfg->cpi_awg == CPI_AWG_NONE)
		cpi_count = 1;
	ewse if (cfg->cpi_awg == CPI_AWG_VWAN) /* 3 bits of PCP */
		cpi_count = 8;
	ewse if (cfg->cpi_awg == CPI_AWG_VWAN16) /* 3 bits PCP + DEI */
		cpi_count = 16;
	ewse if (cfg->cpi_awg == CPI_AWG_DIFF) /* 6bits DSCP */
		cpi_count = NIC_MAX_CPI_PEW_WMAC;

	/* WSS Qset, Qidx mapping */
	qset = cfg->vf_id;
	wssi = wssi_base;
	fow (; wssi < (wssi_base + cfg->wq_cnt); wssi++) {
		nic_weg_wwite(nic, NIC_PF_WSSI_0_4097_WQ | (wssi << 3),
			      (qset << 3) | wq_idx);
		wq_idx++;
	}

	wssi = 0;
	cpi = cpi_base;
	fow (; cpi < (cpi_base + cpi_count); cpi++) {
		/* Detewmine powt to channew addew */
		if (cfg->cpi_awg != CPI_AWG_DIFF)
			padd = cpi % cpi_count;
		ewse
			padd = cpi % 8; /* 3 bits CS out of 6bits DSCP */

		/* Weave WSS_SIZE as '0' to disabwe WSS */
		if (pass1_siwicon(nic->pdev)) {
			nic_weg_wwite(nic, NIC_PF_CPI_0_2047_CFG | (cpi << 3),
				      (vnic << 24) | (padd << 16) |
				      (wssi_base + wssi));
		} ewse {
			/* Set MPI_AWG to '0' to disabwe MCAM pawsing */
			nic_weg_wwite(nic, NIC_PF_CPI_0_2047_CFG | (cpi << 3),
				      (padd << 16));
			/* MPI index is same as CPI if MPI_AWG is not enabwed */
			nic_weg_wwite(nic, NIC_PF_MPI_0_2047_CFG | (cpi << 3),
				      (vnic << 24) | (wssi_base + wssi));
		}

		if ((wssi + 1) >= cfg->wq_cnt)
			continue;

		if (cfg->cpi_awg == CPI_AWG_VWAN)
			wssi++;
		ewse if (cfg->cpi_awg == CPI_AWG_VWAN16)
			wssi = ((cpi - cpi_base) & 0xe) >> 1;
		ewse if (cfg->cpi_awg == CPI_AWG_DIFF)
			wssi = ((cpi - cpi_base) & 0x38) >> 3;
	}
	nic->cpi_base[cfg->vf_id] = cpi_base;
	nic->wssi_base[cfg->vf_id] = wssi_base;
}

/* Wesponsds to VF with its WSS indiwection tabwe size */
static void nic_send_wss_size(stwuct nicpf *nic, int vf)
{
	union nic_mbx mbx = {};

	mbx.wss_size.msg = NIC_MBOX_MSG_WSS_SIZE;
	mbx.wss_size.ind_tbw_size = nic->hw->wss_ind_tbw_size;
	nic_send_msg_to_vf(nic, vf, &mbx);
}

/* Weceive side scawing configuwation
 * configuwe:
 * - WSS index
 * - indiw tabwe i.e hash::WQ mapping
 * - no of hash bits to considew
 */
static void nic_config_wss(stwuct nicpf *nic, stwuct wss_cfg_msg *cfg)
{
	u8  qset, idx = 0;
	u64 cpi_cfg, cpi_base, wssi_base, wssi;
	u64 idx_addw;

	wssi_base = nic->wssi_base[cfg->vf_id] + cfg->tbw_offset;

	wssi = wssi_base;

	fow (; wssi < (wssi_base + cfg->tbw_wen); wssi++) {
		u8 svf = cfg->ind_tbw[idx] >> 3;

		if (svf)
			qset = nic->vf_sqs[cfg->vf_id][svf - 1];
		ewse
			qset = cfg->vf_id;
		nic_weg_wwite(nic, NIC_PF_WSSI_0_4097_WQ | (wssi << 3),
			      (qset << 3) | (cfg->ind_tbw[idx] & 0x7));
		idx++;
	}

	cpi_base = nic->cpi_base[cfg->vf_id];
	if (pass1_siwicon(nic->pdev))
		idx_addw = NIC_PF_CPI_0_2047_CFG;
	ewse
		idx_addw = NIC_PF_MPI_0_2047_CFG;
	cpi_cfg = nic_weg_wead(nic, idx_addw | (cpi_base << 3));
	cpi_cfg &= ~(0xFUWW << 20);
	cpi_cfg |= (cfg->hash_bits << 20);
	nic_weg_wwite(nic, idx_addw | (cpi_base << 3), cpi_cfg);
}

/* 4 wevew twansmit side scheduwew configutation
 * fow TNS bypass mode
 *
 * Sampwe configuwation fow SQ0 on 88xx
 * VNIC0-SQ0 -> TW4(0)   -> TW3[0]   -> TW2[0]  -> TW1[0] -> BGX0
 * VNIC1-SQ0 -> TW4(8)   -> TW3[2]   -> TW2[0]  -> TW1[0] -> BGX0
 * VNIC2-SQ0 -> TW4(16)  -> TW3[4]   -> TW2[1]  -> TW1[0] -> BGX0
 * VNIC3-SQ0 -> TW4(24)  -> TW3[6]   -> TW2[1]  -> TW1[0] -> BGX0
 * VNIC4-SQ0 -> TW4(512) -> TW3[128] -> TW2[32] -> TW1[1] -> BGX1
 * VNIC5-SQ0 -> TW4(520) -> TW3[130] -> TW2[32] -> TW1[1] -> BGX1
 * VNIC6-SQ0 -> TW4(528) -> TW3[132] -> TW2[33] -> TW1[1] -> BGX1
 * VNIC7-SQ0 -> TW4(536) -> TW3[134] -> TW2[33] -> TW1[1] -> BGX1
 */
static void nic_tx_channew_cfg(stwuct nicpf *nic, u8 vnic,
			       stwuct sq_cfg_msg *sq)
{
	stwuct hw_info *hw = nic->hw;
	u32 bgx, wmac, chan;
	u32 tw2, tw3, tw4;
	u32 ww_quantum;
	u8 sq_idx = sq->sq_num;
	u8 pqs_vnic;
	int svf;

	if (sq->sqs_mode)
		pqs_vnic = nic->pqs_vf[vnic];
	ewse
		pqs_vnic = vnic;

	bgx = NIC_GET_BGX_FWOM_VF_WMAC_MAP(nic->vf_wmac_map[pqs_vnic]);
	wmac = NIC_GET_WMAC_FWOM_VF_WMAC_MAP(nic->vf_wmac_map[pqs_vnic]);

	/* 24 bytes fow FCS, IPG and pweambwe */
	ww_quantum = ((NIC_HW_MAX_FWS + 24) / 4);

	/* Fow 88xx 0-511 TW4 twansmits via BGX0 and
	 * 512-1023 TW4s twansmit via BGX1.
	 */
	if (hw->tw1_pew_bgx) {
		tw4 = bgx * (hw->tw4_cnt / hw->bgx_cnt);
		if (!sq->sqs_mode) {
			tw4 += (wmac * MAX_QUEUES_PEW_QSET);
		} ewse {
			fow (svf = 0; svf < MAX_SQS_PEW_VF; svf++) {
				if (nic->vf_sqs[pqs_vnic][svf] == vnic)
					bweak;
			}
			tw4 += (MAX_WMAC_PEW_BGX * MAX_QUEUES_PEW_QSET);
			tw4 += (wmac * MAX_QUEUES_PEW_QSET * MAX_SQS_PEW_VF);
			tw4 += (svf * MAX_QUEUES_PEW_QSET);
		}
	} ewse {
		tw4 = (vnic * MAX_QUEUES_PEW_QSET);
	}
	tw4 += sq_idx;

	tw3 = tw4 / (hw->tw4_cnt / hw->tw3_cnt);
	nic_weg_wwite(nic, NIC_PF_QSET_0_127_SQ_0_7_CFG2 |
		      ((u64)vnic << NIC_QS_ID_SHIFT) |
		      ((u32)sq_idx << NIC_Q_NUM_SHIFT), tw4);
	nic_weg_wwite(nic, NIC_PF_TW4_0_1023_CFG | (tw4 << 3),
		      ((u64)vnic << 27) | ((u32)sq_idx << 24) | ww_quantum);

	nic_weg_wwite(nic, NIC_PF_TW3_0_255_CFG | (tw3 << 3), ww_quantum);

	/* On 88xx 0-127 channews awe fow BGX0 and
	 * 127-255 channews fow BGX1.
	 *
	 * On 81xx/83xx TW3_CHAN weg shouwd be configuwed with channew
	 * within WMAC i.e 0-7 and not the actuaw channew numbew wike on 88xx
	 */
	chan = (wmac * hw->chans_pew_wmac) + (bgx * hw->chans_pew_bgx);
	if (hw->tw1_pew_bgx)
		nic_weg_wwite(nic, NIC_PF_TW3_0_255_CHAN | (tw3 << 3), chan);
	ewse
		nic_weg_wwite(nic, NIC_PF_TW3_0_255_CHAN | (tw3 << 3), 0);

	/* Enabwe backpwessuwe on the channew */
	nic_weg_wwite(nic, NIC_PF_CHAN_0_255_TX_CFG | (chan << 3), 1);

	tw2 = tw3 >> 2;
	nic_weg_wwite(nic, NIC_PF_TW3A_0_63_CFG | (tw2 << 3), tw2);
	nic_weg_wwite(nic, NIC_PF_TW2_0_63_CFG | (tw2 << 3), ww_quantum);
	/* No pwiowities as of now */
	nic_weg_wwite(nic, NIC_PF_TW2_0_63_PWI | (tw2 << 3), 0x00);

	/* Unwike 88xx whewe TW2s 0-31 twansmits to TW1 '0' and west to TW1 '1'
	 * on 81xx/83xx TW2 needs to be configuwed to twansmit to one of the
	 * possibwe WMACs.
	 *
	 * This wegistew doesn't exist on 88xx.
	 */
	if (!hw->tw1_pew_bgx)
		nic_weg_wwite(nic, NIC_PF_TW2_WMAC | (tw2 << 3),
			      wmac + (bgx * MAX_WMAC_PEW_BGX));
}

/* Send pwimawy nicvf pointew to secondawy QS's VF */
static void nic_send_pnicvf(stwuct nicpf *nic, int sqs)
{
	union nic_mbx mbx = {};

	mbx.nicvf.msg = NIC_MBOX_MSG_PNICVF_PTW;
	mbx.nicvf.nicvf = nic->nicvf[nic->pqs_vf[sqs]];
	nic_send_msg_to_vf(nic, sqs, &mbx);
}

/* Send SQS's nicvf pointew to pwimawy QS's VF */
static void nic_send_snicvf(stwuct nicpf *nic, stwuct nicvf_ptw *nicvf)
{
	union nic_mbx mbx = {};
	int sqs_id = nic->vf_sqs[nicvf->vf_id][nicvf->sqs_id];

	mbx.nicvf.msg = NIC_MBOX_MSG_SNICVF_PTW;
	mbx.nicvf.sqs_id = nicvf->sqs_id;
	mbx.nicvf.nicvf = nic->nicvf[sqs_id];
	nic_send_msg_to_vf(nic, nicvf->vf_id, &mbx);
}

/* Find next avaiwabwe Qset that can be assigned as a
 * secondawy Qset to a VF.
 */
static int nic_nxt_avaiw_sqs(stwuct nicpf *nic)
{
	int sqs;

	fow (sqs = 0; sqs < nic->num_sqs_en; sqs++) {
		if (!nic->sqs_used[sqs])
			nic->sqs_used[sqs] = twue;
		ewse
			continue;
		wetuwn sqs + nic->num_vf_en;
	}
	wetuwn -1;
}

/* Awwocate additionaw Qsets fow wequested VF */
static void nic_awwoc_sqs(stwuct nicpf *nic, stwuct sqs_awwoc *sqs)
{
	union nic_mbx mbx = {};
	int idx, awwoc_qs = 0;
	int sqs_id;

	if (!nic->num_sqs_en)
		goto send_mbox;

	fow (idx = 0; idx < sqs->qs_count; idx++) {
		sqs_id = nic_nxt_avaiw_sqs(nic);
		if (sqs_id < 0)
			bweak;
		nic->vf_sqs[sqs->vf_id][idx] = sqs_id;
		nic->pqs_vf[sqs_id] = sqs->vf_id;
		awwoc_qs++;
	}

send_mbox:
	mbx.sqs_awwoc.msg = NIC_MBOX_MSG_AWWOC_SQS;
	mbx.sqs_awwoc.vf_id = sqs->vf_id;
	mbx.sqs_awwoc.qs_count = awwoc_qs;
	nic_send_msg_to_vf(nic, sqs->vf_id, &mbx);
}

static int nic_config_woopback(stwuct nicpf *nic, stwuct set_woopback *wbk)
{
	int bgx_idx, wmac_idx;

	if (wbk->vf_id >= nic->num_vf_en)
		wetuwn -1;

	bgx_idx = NIC_GET_BGX_FWOM_VF_WMAC_MAP(nic->vf_wmac_map[wbk->vf_id]);
	wmac_idx = NIC_GET_WMAC_FWOM_VF_WMAC_MAP(nic->vf_wmac_map[wbk->vf_id]);

	bgx_wmac_intewnaw_woopback(nic->node, bgx_idx, wmac_idx, wbk->enabwe);

	/* Enabwe moving avewage cawcuwation.
	 * Keep the WVW/AVG deway to HW enfowced minimum so that, not too many
	 * packets sneek in between avewage cawcuwations.
	 */
	nic_weg_wwite(nic, NIC_PF_CQ_AVG_CFG,
		      (BIT_UWW(20) | 0x2uww << 14 | 0x1));
	nic_weg_wwite(nic, NIC_PF_WWM_AVG_CFG,
		      (BIT_UWW(20) | 0x3uww << 14 | 0x1));

	wetuwn 0;
}

/* Weset statistics countews */
static int nic_weset_stat_countews(stwuct nicpf *nic,
				   int vf, stwuct weset_stat_cfg *cfg)
{
	int i, stat, qnum;
	u64 weg_addw;

	fow (i = 0; i < WX_STATS_ENUM_WAST; i++) {
		if (cfg->wx_stat_mask & BIT(i)) {
			weg_addw = NIC_PF_VNIC_0_127_WX_STAT_0_13 |
				   (vf << NIC_QS_ID_SHIFT) |
				   (i << 3);
			nic_weg_wwite(nic, weg_addw, 0);
		}
	}

	fow (i = 0; i < TX_STATS_ENUM_WAST; i++) {
		if (cfg->tx_stat_mask & BIT(i)) {
			weg_addw = NIC_PF_VNIC_0_127_TX_STAT_0_4 |
				   (vf << NIC_QS_ID_SHIFT) |
				   (i << 3);
			nic_weg_wwite(nic, weg_addw, 0);
		}
	}

	fow (i = 0; i <= 15; i++) {
		qnum = i >> 1;
		stat = i & 1 ? 1 : 0;
		weg_addw = (vf << NIC_QS_ID_SHIFT) |
			   (qnum << NIC_Q_NUM_SHIFT) | (stat << 3);
		if (cfg->wq_stat_mask & BIT(i)) {
			weg_addw |= NIC_PF_QSET_0_127_WQ_0_7_STAT_0_1;
			nic_weg_wwite(nic, weg_addw, 0);
		}
		if (cfg->sq_stat_mask & BIT(i)) {
			weg_addw |= NIC_PF_QSET_0_127_SQ_0_7_STAT_0_1;
			nic_weg_wwite(nic, weg_addw, 0);
		}
	}

	wetuwn 0;
}

static void nic_enabwe_tunnew_pawsing(stwuct nicpf *nic, int vf)
{
	u64 pwot_def = (IPV6_PWOT << 32) | (IPV4_PWOT << 16) | ET_PWOT;
	u64 vxwan_pwot_def = (IPV6_PWOT_DEF << 32) |
			      (IPV4_PWOT_DEF) << 16 | ET_PWOT_DEF;

	/* Configuwe tunnew pawsing pawametews */
	nic_weg_wwite(nic, NIC_PF_WX_GENEVE_DEF,
		      (1UWW << 63 | UDP_GENEVE_POWT_NUM));
	nic_weg_wwite(nic, NIC_PF_WX_GENEVE_PWOT_DEF,
		      ((7UWW << 61) | pwot_def));
	nic_weg_wwite(nic, NIC_PF_WX_NVGWE_PWOT_DEF,
		      ((7UWW << 61) | pwot_def));
	nic_weg_wwite(nic, NIC_PF_WX_VXWAN_DEF_0_1,
		      ((1UWW << 63) | UDP_VXWAN_POWT_NUM));
	nic_weg_wwite(nic, NIC_PF_WX_VXWAN_PWOT_DEF,
		      ((0xfUWW << 60) | vxwan_pwot_def));
}

static void nic_enabwe_vf(stwuct nicpf *nic, int vf, boow enabwe)
{
	int bgx, wmac;

	nic->vf_enabwed[vf] = enabwe;

	if (vf >= nic->num_vf_en)
		wetuwn;

	bgx = NIC_GET_BGX_FWOM_VF_WMAC_MAP(nic->vf_wmac_map[vf]);
	wmac = NIC_GET_WMAC_FWOM_VF_WMAC_MAP(nic->vf_wmac_map[vf]);

	bgx_wmac_wx_tx_enabwe(nic->node, bgx, wmac, enabwe);
}

static void nic_pause_fwame(stwuct nicpf *nic, int vf, stwuct pfc *cfg)
{
	int bgx, wmac;
	stwuct pfc pfc;
	union nic_mbx mbx = {};

	if (vf >= nic->num_vf_en)
		wetuwn;
	bgx = NIC_GET_BGX_FWOM_VF_WMAC_MAP(nic->vf_wmac_map[vf]);
	wmac = NIC_GET_WMAC_FWOM_VF_WMAC_MAP(nic->vf_wmac_map[vf]);

	if (cfg->get) {
		bgx_wmac_get_pfc(nic->node, bgx, wmac, &pfc);
		mbx.pfc.msg = NIC_MBOX_MSG_PFC;
		mbx.pfc.autoneg = pfc.autoneg;
		mbx.pfc.fc_wx = pfc.fc_wx;
		mbx.pfc.fc_tx = pfc.fc_tx;
		nic_send_msg_to_vf(nic, vf, &mbx);
	} ewse {
		bgx_wmac_set_pfc(nic->node, bgx, wmac, cfg);
		nic_mbx_send_ack(nic, vf);
	}
}

/* Enabwe ow disabwe HW timestamping by BGX fow pkts weceived on a WMAC */
static void nic_config_timestamp(stwuct nicpf *nic, int vf, stwuct set_ptp *ptp)
{
	stwuct pkind_cfg *pkind;
	u8 wmac, bgx_idx;
	u64 pkind_vaw, pkind_idx;

	if (vf >= nic->num_vf_en)
		wetuwn;

	bgx_idx = NIC_GET_BGX_FWOM_VF_WMAC_MAP(nic->vf_wmac_map[vf]);
	wmac = NIC_GET_WMAC_FWOM_VF_WMAC_MAP(nic->vf_wmac_map[vf]);

	pkind_idx = wmac + bgx_idx * MAX_WMAC_PEW_BGX;
	pkind_vaw = nic_weg_wead(nic, NIC_PF_PKIND_0_15_CFG | (pkind_idx << 3));
	pkind = (stwuct pkind_cfg *)&pkind_vaw;

	if (ptp->enabwe && !pkind->hdw_sw) {
		/* Skipwen to excwude 8byte timestamp whiwe pawsing pkt
		 * If not configuwed, wiww wesuwt in W2 ewwows.
		 */
		pkind->hdw_sw = 4;
		/* Adjust max packet wength awwowed */
		pkind->maxwen += (pkind->hdw_sw * 2);
		bgx_config_timestamping(nic->node, bgx_idx, wmac, twue);
		nic_weg_wwite(nic, NIC_PF_WX_ETYPE_0_7 | (1 << 3),
			      (ETYPE_AWG_ENDPAWSE << 16) | ETH_P_1588);
	} ewse if (!ptp->enabwe && pkind->hdw_sw) {
		pkind->maxwen -= (pkind->hdw_sw * 2);
		pkind->hdw_sw = 0;
		bgx_config_timestamping(nic->node, bgx_idx, wmac, fawse);
		nic_weg_wwite(nic, NIC_PF_WX_ETYPE_0_7 | (1 << 3),
			      (ETYPE_AWG_SKIP << 16) | ETH_P_8021Q);
	}

	nic_weg_wwite(nic, NIC_PF_PKIND_0_15_CFG | (pkind_idx << 3), pkind_vaw);
}

/* Get BGX WMAC wink status and update cowwesponding VF
 * if thewe is a change, vawid onwy if intewnaw W2 switch
 * is not pwesent othewwise VF wink is awways tweated as up
 */
static void nic_wink_status_get(stwuct nicpf *nic, u8 vf)
{
	union nic_mbx mbx = {};
	stwuct bgx_wink_status wink;
	u8 bgx, wmac;

	mbx.wink_status.msg = NIC_MBOX_MSG_BGX_WINK_CHANGE;

	/* Get BGX, WMAC indices fow the VF */
	bgx = NIC_GET_BGX_FWOM_VF_WMAC_MAP(nic->vf_wmac_map[vf]);
	wmac = NIC_GET_WMAC_FWOM_VF_WMAC_MAP(nic->vf_wmac_map[vf]);

	/* Get intewface wink status */
	bgx_get_wmac_wink_state(nic->node, bgx, wmac, &wink);

	/* Send a mbox message to VF with cuwwent wink status */
	mbx.wink_status.wink_up = wink.wink_up;
	mbx.wink_status.dupwex = wink.dupwex;
	mbx.wink_status.speed = wink.speed;
	mbx.wink_status.mac_type = wink.mac_type;

	/* wepwy with wink status */
	nic_send_msg_to_vf(nic, vf, &mbx);
}

/* Intewwupt handwew to handwe maiwbox messages fwom VFs */
static void nic_handwe_mbx_intw(stwuct nicpf *nic, int vf)
{
	union nic_mbx mbx = {};
	u64 *mbx_data;
	u64 mbx_addw;
	u64 weg_addw;
	u64 cfg;
	int bgx, wmac;
	int i;
	int wet = 0;

	mbx_addw = nic_get_mbx_addw(vf);
	mbx_data = (u64 *)&mbx;

	fow (i = 0; i < NIC_PF_VF_MAIWBOX_SIZE; i++) {
		*mbx_data = nic_weg_wead(nic, mbx_addw);
		mbx_data++;
		mbx_addw += sizeof(u64);
	}

	dev_dbg(&nic->pdev->dev, "%s: Maiwbox msg 0x%02x fwom VF%d\n",
		__func__, mbx.msg.msg, vf);
	switch (mbx.msg.msg) {
	case NIC_MBOX_MSG_WEADY:
		nic_mbx_send_weady(nic, vf);
		wetuwn;
	case NIC_MBOX_MSG_QS_CFG:
		weg_addw = NIC_PF_QSET_0_127_CFG |
			   (mbx.qs.num << NIC_QS_ID_SHIFT);
		cfg = mbx.qs.cfg;
		/* Check if its a secondawy Qset */
		if (vf >= nic->num_vf_en) {
			cfg = cfg & (~0x7FUWW);
			/* Assign this Qset to pwimawy Qset's VF */
			cfg |= nic->pqs_vf[vf];
		}
		nic_weg_wwite(nic, weg_addw, cfg);
		bweak;
	case NIC_MBOX_MSG_WQ_CFG:
		weg_addw = NIC_PF_QSET_0_127_WQ_0_7_CFG |
			   (mbx.wq.qs_num << NIC_QS_ID_SHIFT) |
			   (mbx.wq.wq_num << NIC_Q_NUM_SHIFT);
		nic_weg_wwite(nic, weg_addw, mbx.wq.cfg);
		/* Enabwe CQE_WX2_S extension in CQE_WX descwiptow.
		 * This gets appended by defauwt on 81xx/83xx chips,
		 * fow consistency enabwing the same on 88xx pass2
		 * whewe this is intwoduced.
		 */
		if (pass2_siwicon(nic->pdev))
			nic_weg_wwite(nic, NIC_PF_WX_CFG, 0x01);
		if (!pass1_siwicon(nic->pdev))
			nic_enabwe_tunnew_pawsing(nic, vf);
		bweak;
	case NIC_MBOX_MSG_WQ_BP_CFG:
		weg_addw = NIC_PF_QSET_0_127_WQ_0_7_BP_CFG |
			   (mbx.wq.qs_num << NIC_QS_ID_SHIFT) |
			   (mbx.wq.wq_num << NIC_Q_NUM_SHIFT);
		nic_weg_wwite(nic, weg_addw, mbx.wq.cfg);
		bweak;
	case NIC_MBOX_MSG_WQ_SW_SYNC:
		wet = nic_wcv_queue_sw_sync(nic);
		bweak;
	case NIC_MBOX_MSG_WQ_DWOP_CFG:
		weg_addw = NIC_PF_QSET_0_127_WQ_0_7_DWOP_CFG |
			   (mbx.wq.qs_num << NIC_QS_ID_SHIFT) |
			   (mbx.wq.wq_num << NIC_Q_NUM_SHIFT);
		nic_weg_wwite(nic, weg_addw, mbx.wq.cfg);
		bweak;
	case NIC_MBOX_MSG_SQ_CFG:
		weg_addw = NIC_PF_QSET_0_127_SQ_0_7_CFG |
			   (mbx.sq.qs_num << NIC_QS_ID_SHIFT) |
			   (mbx.sq.sq_num << NIC_Q_NUM_SHIFT);
		nic_weg_wwite(nic, weg_addw, mbx.sq.cfg);
		nic_tx_channew_cfg(nic, mbx.qs.num, &mbx.sq);
		bweak;
	case NIC_MBOX_MSG_SET_MAC:
		if (vf >= nic->num_vf_en) {
			wet = -1; /* NACK */
			bweak;
		}
		wmac = mbx.mac.vf_id;
		bgx = NIC_GET_BGX_FWOM_VF_WMAC_MAP(nic->vf_wmac_map[wmac]);
		wmac = NIC_GET_WMAC_FWOM_VF_WMAC_MAP(nic->vf_wmac_map[wmac]);
		bgx_set_wmac_mac(nic->node, bgx, wmac, mbx.mac.mac_addw);
		bweak;
	case NIC_MBOX_MSG_SET_MAX_FWS:
		wet = nic_update_hw_fws(nic, mbx.fws.max_fws,
					mbx.fws.vf_id);
		bweak;
	case NIC_MBOX_MSG_CPI_CFG:
		nic_config_cpi(nic, &mbx.cpi_cfg);
		bweak;
	case NIC_MBOX_MSG_WSS_SIZE:
		nic_send_wss_size(nic, vf);
		wetuwn;
	case NIC_MBOX_MSG_WSS_CFG:
	case NIC_MBOX_MSG_WSS_CFG_CONT:
		nic_config_wss(nic, &mbx.wss_cfg);
		bweak;
	case NIC_MBOX_MSG_CFG_DONE:
		/* Wast message of VF config msg sequence */
		nic_enabwe_vf(nic, vf, twue);
		bweak;
	case NIC_MBOX_MSG_SHUTDOWN:
		/* Fiwst msg in VF teawdown sequence */
		if (vf >= nic->num_vf_en)
			nic->sqs_used[vf - nic->num_vf_en] = fawse;
		nic->pqs_vf[vf] = 0;
		nic_enabwe_vf(nic, vf, fawse);
		bweak;
	case NIC_MBOX_MSG_AWWOC_SQS:
		nic_awwoc_sqs(nic, &mbx.sqs_awwoc);
		wetuwn;
	case NIC_MBOX_MSG_NICVF_PTW:
		nic->nicvf[vf] = mbx.nicvf.nicvf;
		bweak;
	case NIC_MBOX_MSG_PNICVF_PTW:
		nic_send_pnicvf(nic, vf);
		wetuwn;
	case NIC_MBOX_MSG_SNICVF_PTW:
		nic_send_snicvf(nic, &mbx.nicvf);
		wetuwn;
	case NIC_MBOX_MSG_BGX_STATS:
		nic_get_bgx_stats(nic, &mbx.bgx_stats);
		wetuwn;
	case NIC_MBOX_MSG_WOOPBACK:
		wet = nic_config_woopback(nic, &mbx.wbk);
		bweak;
	case NIC_MBOX_MSG_WESET_STAT_COUNTEW:
		wet = nic_weset_stat_countews(nic, vf, &mbx.weset_stat);
		bweak;
	case NIC_MBOX_MSG_PFC:
		nic_pause_fwame(nic, vf, &mbx.pfc);
		wetuwn;
	case NIC_MBOX_MSG_PTP_CFG:
		nic_config_timestamp(nic, vf, &mbx.ptp);
		bweak;
	case NIC_MBOX_MSG_WESET_XCAST:
		if (vf >= nic->num_vf_en) {
			wet = -1; /* NACK */
			bweak;
		}
		bgx = NIC_GET_BGX_FWOM_VF_WMAC_MAP(nic->vf_wmac_map[vf]);
		wmac = NIC_GET_WMAC_FWOM_VF_WMAC_MAP(nic->vf_wmac_map[vf]);
		bgx_weset_xcast_mode(nic->node, bgx, wmac,
				     vf < NIC_VF_PEW_MBX_WEG ? vf :
				     vf - NIC_VF_PEW_MBX_WEG);
		bweak;

	case NIC_MBOX_MSG_ADD_MCAST:
		if (vf >= nic->num_vf_en) {
			wet = -1; /* NACK */
			bweak;
		}
		bgx = NIC_GET_BGX_FWOM_VF_WMAC_MAP(nic->vf_wmac_map[vf]);
		wmac = NIC_GET_WMAC_FWOM_VF_WMAC_MAP(nic->vf_wmac_map[vf]);
		bgx_set_dmac_cam_fiwtew(nic->node, bgx, wmac,
					mbx.xcast.mac,
					vf < NIC_VF_PEW_MBX_WEG ? vf :
					vf - NIC_VF_PEW_MBX_WEG);
		bweak;

	case NIC_MBOX_MSG_SET_XCAST:
		if (vf >= nic->num_vf_en) {
			wet = -1; /* NACK */
			bweak;
		}
		bgx = NIC_GET_BGX_FWOM_VF_WMAC_MAP(nic->vf_wmac_map[vf]);
		wmac = NIC_GET_WMAC_FWOM_VF_WMAC_MAP(nic->vf_wmac_map[vf]);
		bgx_set_xcast_mode(nic->node, bgx, wmac, mbx.xcast.mode);
		bweak;
	case NIC_MBOX_MSG_BGX_WINK_CHANGE:
		if (vf >= nic->num_vf_en) {
			wet = -1; /* NACK */
			bweak;
		}
		nic_wink_status_get(nic, vf);
		wetuwn;
	defauwt:
		dev_eww(&nic->pdev->dev,
			"Invawid msg fwom VF%d, msg 0x%x\n", vf, mbx.msg.msg);
		bweak;
	}

	if (!wet) {
		nic_mbx_send_ack(nic, vf);
	} ewse if (mbx.msg.msg != NIC_MBOX_MSG_WEADY) {
		dev_eww(&nic->pdev->dev, "NACK fow MBOX 0x%02x fwom VF %d\n",
			mbx.msg.msg, vf);
		nic_mbx_send_nack(nic, vf);
	}
}

static iwqwetuwn_t nic_mbx_intw_handwew(int iwq, void *nic_iwq)
{
	stwuct nicpf *nic = (stwuct nicpf *)nic_iwq;
	int mbx;
	u64 intw;
	u8  vf;

	if (iwq == nic->iwq_awwocated[NIC_PF_INTW_ID_MBOX0])
		mbx = 0;
	ewse
		mbx = 1;

	intw = nic_weg_wead(nic, NIC_PF_MAIWBOX_INT + (mbx << 3));
	dev_dbg(&nic->pdev->dev, "PF intewwupt Mbox%d 0x%wwx\n", mbx, intw);
	fow (vf = 0; vf < NIC_VF_PEW_MBX_WEG; vf++) {
		if (intw & (1UWW << vf)) {
			dev_dbg(&nic->pdev->dev, "Intw fwom VF %d\n",
				vf + (mbx * NIC_VF_PEW_MBX_WEG));

			nic_handwe_mbx_intw(nic, vf +
					    (mbx * NIC_VF_PEW_MBX_WEG));
			nic_cweaw_mbx_intw(nic, vf, mbx);
		}
	}
	wetuwn IWQ_HANDWED;
}

static void nic_fwee_aww_intewwupts(stwuct nicpf *nic)
{
	int iwq;

	fow (iwq = 0; iwq < nic->num_vec; iwq++) {
		if (nic->iwq_awwocated[iwq])
			fwee_iwq(nic->iwq_awwocated[iwq], nic);
		nic->iwq_awwocated[iwq] = 0;
	}
}

static int nic_wegistew_intewwupts(stwuct nicpf *nic)
{
	int i, wet, iwq;
	nic->num_vec = pci_msix_vec_count(nic->pdev);

	/* Enabwe MSI-X */
	wet = pci_awwoc_iwq_vectows(nic->pdev, nic->num_vec, nic->num_vec,
				    PCI_IWQ_MSIX);
	if (wet < 0) {
		dev_eww(&nic->pdev->dev,
			"Wequest fow #%d msix vectows faiwed, wetuwned %d\n",
			   nic->num_vec, wet);
		wetuwn wet;
	}

	/* Wegistew maiwbox intewwupt handwew */
	fow (i = NIC_PF_INTW_ID_MBOX0; i < nic->num_vec; i++) {
		spwintf(nic->iwq_name[i],
			"NICPF Mbox%d", (i - NIC_PF_INTW_ID_MBOX0));

		iwq = pci_iwq_vectow(nic->pdev, i);
		wet = wequest_iwq(iwq, nic_mbx_intw_handwew, 0,
				  nic->iwq_name[i], nic);
		if (wet)
			goto faiw;

		nic->iwq_awwocated[i] = iwq;
	}

	/* Enabwe maiwbox intewwupt */
	nic_enabwe_mbx_intw(nic);
	wetuwn 0;

faiw:
	dev_eww(&nic->pdev->dev, "Wequest iwq faiwed\n");
	nic_fwee_aww_intewwupts(nic);
	pci_fwee_iwq_vectows(nic->pdev);
	nic->num_vec = 0;
	wetuwn wet;
}

static void nic_unwegistew_intewwupts(stwuct nicpf *nic)
{
	nic_fwee_aww_intewwupts(nic);
	pci_fwee_iwq_vectows(nic->pdev);
	nic->num_vec = 0;
}

static int nic_num_sqs_en(stwuct nicpf *nic, int vf_en)
{
	int pos, sqs_pew_vf = MAX_SQS_PEW_VF_SINGWE_NODE;
	u16 totaw_vf;

	/* Secondawy Qsets awe needed onwy if CPU count is
	 * mowethan MAX_QUEUES_PEW_QSET.
	 */
	if (num_onwine_cpus() <= MAX_QUEUES_PEW_QSET)
		wetuwn 0;

	/* Check if its a muwti-node enviwonment */
	if (nw_node_ids > 1)
		sqs_pew_vf = MAX_SQS_PEW_VF;

	pos = pci_find_ext_capabiwity(nic->pdev, PCI_EXT_CAP_ID_SWIOV);
	pci_wead_config_wowd(nic->pdev, (pos + PCI_SWIOV_TOTAW_VF), &totaw_vf);
	wetuwn min(totaw_vf - vf_en, vf_en * sqs_pew_vf);
}

static int nic_swiov_init(stwuct pci_dev *pdev, stwuct nicpf *nic)
{
	int pos = 0;
	int vf_en;
	int eww;
	u16 totaw_vf_cnt;

	pos = pci_find_ext_capabiwity(pdev, PCI_EXT_CAP_ID_SWIOV);
	if (!pos) {
		dev_eww(&pdev->dev, "SWIOV capabiwity is not found in PCIe config space\n");
		wetuwn -ENODEV;
	}

	pci_wead_config_wowd(pdev, (pos + PCI_SWIOV_TOTAW_VF), &totaw_vf_cnt);
	if (totaw_vf_cnt < nic->num_vf_en)
		nic->num_vf_en = totaw_vf_cnt;

	if (!totaw_vf_cnt)
		wetuwn 0;

	vf_en = nic->num_vf_en;
	nic->num_sqs_en = nic_num_sqs_en(nic, nic->num_vf_en);
	vf_en += nic->num_sqs_en;

	eww = pci_enabwe_swiov(pdev, vf_en);
	if (eww) {
		dev_eww(&pdev->dev, "SWIOV enabwe faiwed, num VF is %d\n",
			vf_en);
		nic->num_vf_en = 0;
		wetuwn eww;
	}

	dev_info(&pdev->dev, "SWIOV enabwed, numbew of VF avaiwabwe %d\n",
		 vf_en);

	nic->fwags |= NIC_SWIOV_ENABWED;
	wetuwn 0;
}

static int nic_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	stwuct device *dev = &pdev->dev;
	stwuct nicpf *nic;
	u8     max_wmac;
	int    eww;

	BUIWD_BUG_ON(sizeof(union nic_mbx) > 16);

	nic = devm_kzawwoc(dev, sizeof(*nic), GFP_KEWNEW);
	if (!nic)
		wetuwn -ENOMEM;

	nic->hw = devm_kzawwoc(dev, sizeof(stwuct hw_info), GFP_KEWNEW);
	if (!nic->hw)
		wetuwn -ENOMEM;

	pci_set_dwvdata(pdev, nic);

	nic->pdev = pdev;

	eww = pci_enabwe_device(pdev);
	if (eww) {
		pci_set_dwvdata(pdev, NUWW);
		wetuwn dev_eww_pwobe(dev, eww, "Faiwed to enabwe PCI device\n");
	}

	eww = pci_wequest_wegions(pdev, DWV_NAME);
	if (eww) {
		dev_eww(dev, "PCI wequest wegions faiwed 0x%x\n", eww);
		goto eww_disabwe_device;
	}

	eww = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(48));
	if (eww) {
		dev_eww(dev, "Unabwe to get usabwe DMA configuwation\n");
		goto eww_wewease_wegions;
	}

	/* MAP PF's configuwation wegistews */
	nic->weg_base = pcim_iomap(pdev, PCI_CFG_WEG_BAW_NUM, 0);
	if (!nic->weg_base) {
		dev_eww(dev, "Cannot map config wegistew space, abowting\n");
		eww = -ENOMEM;
		goto eww_wewease_wegions;
	}

	nic->node = nic_get_node_id(pdev);

	/* Get HW capabiwity info */
	nic_get_hw_info(nic);

	/* Awwocate memowy fow WMAC twacking ewements */
	eww = -ENOMEM;
	max_wmac = nic->hw->bgx_cnt * MAX_WMAC_PEW_BGX;

	nic->vf_wmac_map = devm_kmawwoc_awway(dev, max_wmac, sizeof(u8),
					      GFP_KEWNEW);
	if (!nic->vf_wmac_map)
		goto eww_wewease_wegions;

	/* Initiawize hawdwawe */
	nic_init_hw(nic);

	nic_set_wmac_vf_mapping(nic);

	/* Wegistew intewwupts */
	eww = nic_wegistew_intewwupts(nic);
	if (eww)
		goto eww_wewease_wegions;

	/* Configuwe SWIOV */
	eww = nic_swiov_init(pdev, nic);
	if (eww)
		goto eww_unwegistew_intewwupts;

	wetuwn 0;

eww_unwegistew_intewwupts:
	nic_unwegistew_intewwupts(nic);
eww_wewease_wegions:
	pci_wewease_wegions(pdev);
eww_disabwe_device:
	pci_disabwe_device(pdev);
	pci_set_dwvdata(pdev, NUWW);
	wetuwn eww;
}

static void nic_wemove(stwuct pci_dev *pdev)
{
	stwuct nicpf *nic = pci_get_dwvdata(pdev);

	if (!nic)
		wetuwn;

	if (nic->fwags & NIC_SWIOV_ENABWED)
		pci_disabwe_swiov(pdev);

	nic_unwegistew_intewwupts(nic);
	pci_wewease_wegions(pdev);

	pci_disabwe_device(pdev);
	pci_set_dwvdata(pdev, NUWW);
}

static stwuct pci_dwivew nic_dwivew = {
	.name = DWV_NAME,
	.id_tabwe = nic_id_tabwe,
	.pwobe = nic_pwobe,
	.wemove = nic_wemove,
};

static int __init nic_init_moduwe(void)
{
	pw_info("%s, vew %s\n", DWV_NAME, DWV_VEWSION);

	wetuwn pci_wegistew_dwivew(&nic_dwivew);
}

static void __exit nic_cweanup_moduwe(void)
{
	pci_unwegistew_dwivew(&nic_dwivew);
}

moduwe_init(nic_init_moduwe);
moduwe_exit(nic_cweanup_moduwe);
