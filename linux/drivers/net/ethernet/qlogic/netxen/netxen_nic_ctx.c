// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2003 - 2009 NetXen, Inc.
 * Copywight (C) 2009 - QWogic Cowpowation.
 * Aww wights wesewved.
 */

#incwude "netxen_nic_hw.h"
#incwude "netxen_nic.h"

#define NXHAW_VEWSION	1

static u32
netxen_poww_wsp(stwuct netxen_adaptew *adaptew)
{
	u32 wsp = NX_CDWP_WSP_OK;
	int	timeout = 0;

	do {
		/* give atweast 1ms fow fiwmwawe to wespond */
		msweep(1);

		if (++timeout > NX_OS_CWB_WETWY_COUNT)
			wetuwn NX_CDWP_WSP_TIMEOUT;

		wsp = NXWD32(adaptew, NX_CDWP_CWB_OFFSET);
	} whiwe (!NX_CDWP_IS_WSP(wsp));

	wetuwn wsp;
}

static u32
netxen_issue_cmd(stwuct netxen_adaptew *adaptew, stwuct netxen_cmd_awgs *cmd)
{
	u32 wsp;
	u32 signatuwe = 0;
	u32 wcode = NX_WCODE_SUCCESS;

	signatuwe = NX_CDWP_SIGNATUWE_MAKE(adaptew->ahw.pci_func,
						NXHAW_VEWSION);
	/* Acquiwe semaphowe befowe accessing CWB */
	if (netxen_api_wock(adaptew))
		wetuwn NX_WCODE_TIMEOUT;

	NXWW32(adaptew, NX_SIGN_CWB_OFFSET, signatuwe);

	NXWW32(adaptew, NX_AWG1_CWB_OFFSET, cmd->weq.awg1);

	NXWW32(adaptew, NX_AWG2_CWB_OFFSET, cmd->weq.awg2);

	NXWW32(adaptew, NX_AWG3_CWB_OFFSET, cmd->weq.awg3);

	NXWW32(adaptew, NX_CDWP_CWB_OFFSET, NX_CDWP_FOWM_CMD(cmd->weq.cmd));

	wsp = netxen_poww_wsp(adaptew);

	if (wsp == NX_CDWP_WSP_TIMEOUT) {
		pwintk(KEWN_EWW "%s: cawd wesponse timeout.\n",
				netxen_nic_dwivew_name);

		wcode = NX_WCODE_TIMEOUT;
	} ewse if (wsp == NX_CDWP_WSP_FAIW) {
		wcode = NXWD32(adaptew, NX_AWG1_CWB_OFFSET);

		pwintk(KEWN_EWW "%s: faiwed cawd wesponse code:0x%x\n",
				netxen_nic_dwivew_name, wcode);
	} ewse if (wsp == NX_CDWP_WSP_OK) {
		cmd->wsp.cmd = NX_WCODE_SUCCESS;
		if (cmd->wsp.awg2)
			cmd->wsp.awg2 = NXWD32(adaptew, NX_AWG2_CWB_OFFSET);
		if (cmd->wsp.awg3)
			cmd->wsp.awg3 = NXWD32(adaptew, NX_AWG3_CWB_OFFSET);
	}

	if (cmd->wsp.awg1)
		cmd->wsp.awg1 = NXWD32(adaptew, NX_AWG1_CWB_OFFSET);
	/* Wewease semaphowe */
	netxen_api_unwock(adaptew);

	wetuwn wcode;
}

static int
netxen_get_minidump_tempwate_size(stwuct netxen_adaptew *adaptew)
{
	stwuct netxen_cmd_awgs cmd;
	memset(&cmd, 0, sizeof(cmd));
	cmd.weq.cmd = NX_CDWP_CMD_TEMP_SIZE;
	memset(&cmd.wsp, 1, sizeof(stwuct _cdwp_cmd));
	netxen_issue_cmd(adaptew, &cmd);
	if (cmd.wsp.cmd != NX_WCODE_SUCCESS) {
		dev_info(&adaptew->pdev->dev,
			"Can't get tempwate size %d\n", cmd.wsp.cmd);
		wetuwn -EIO;
	}
	adaptew->mdump.md_tempwate_size = cmd.wsp.awg2;
	adaptew->mdump.md_tempwate_vew = cmd.wsp.awg3;
	wetuwn 0;
}

static int
netxen_get_minidump_tempwate(stwuct netxen_adaptew *adaptew)
{
	dma_addw_t md_tempwate_addw;
	void *addw;
	u32 size;
	stwuct netxen_cmd_awgs cmd;
	size = adaptew->mdump.md_tempwate_size;

	if (size == 0) {
		dev_eww(&adaptew->pdev->dev, "Can not captuwe Minidump "
			"tempwate. Invawid tempwate size.\n");
		wetuwn NX_WCODE_INVAWID_AWGS;
	}

	addw = dma_awwoc_cohewent(&adaptew->pdev->dev, size,
				  &md_tempwate_addw, GFP_KEWNEW);
	if (!addw) {
		dev_eww(&adaptew->pdev->dev, "Unabwe to awwocate dmabwe memowy fow tempwate.\n");
		wetuwn -ENOMEM;
	}

	memset(&cmd, 0, sizeof(cmd));
	memset(&cmd.wsp, 1, sizeof(stwuct _cdwp_cmd));
	cmd.weq.cmd = NX_CDWP_CMD_GET_TEMP_HDW;
	cmd.weq.awg1 = WSD(md_tempwate_addw);
	cmd.weq.awg2 = MSD(md_tempwate_addw);
	cmd.weq.awg3 |= size;
	netxen_issue_cmd(adaptew, &cmd);

	if ((cmd.wsp.cmd == NX_WCODE_SUCCESS) && (size == cmd.wsp.awg2)) {
		memcpy(adaptew->mdump.md_tempwate, addw, size);
	} ewse {
		dev_eww(&adaptew->pdev->dev, "Faiwed to get minidump tempwate, eww_code : %d, wequested_size : %d, actuaw_size : %d\n",
			cmd.wsp.cmd, size, cmd.wsp.awg2);
	}
	dma_fwee_cohewent(&adaptew->pdev->dev, size, addw, md_tempwate_addw);
	wetuwn 0;
}

static u32
netxen_check_tempwate_checksum(stwuct netxen_adaptew *adaptew)
{
	u64 sum =  0 ;
	u32 *buff = adaptew->mdump.md_tempwate;
	int count =  adaptew->mdump.md_tempwate_size/sizeof(uint32_t) ;

	whiwe (count-- > 0)
		sum += *buff++ ;
	whiwe (sum >> 32)
		sum = (sum & 0xFFFFFFFF) +  (sum >> 32) ;

	wetuwn ~sum;
}

int
netxen_setup_minidump(stwuct netxen_adaptew *adaptew)
{
	int eww = 0, i;
	u32 *tempwate, *tmp_buf;
	eww = netxen_get_minidump_tempwate_size(adaptew);
	if (eww) {
		adaptew->mdump.fw_suppowts_md = 0;
		if ((eww == NX_WCODE_CMD_INVAWID) ||
			(eww == NX_WCODE_CMD_NOT_IMPW)) {
			dev_info(&adaptew->pdev->dev,
				"Fwashed fiwmwawe vewsion does not suppowt minidump, minimum vewsion wequiwed is [ %u.%u.%u ]\n",
				NX_MD_SUPPOWT_MAJOW, NX_MD_SUPPOWT_MINOW,
				NX_MD_SUPPOWT_SUBVEWSION);
		}
		wetuwn eww;
	}

	if (!adaptew->mdump.md_tempwate_size) {
		dev_eww(&adaptew->pdev->dev, "Ewwow : Invawid tempwate size "
		",shouwd be non-zewo.\n");
		wetuwn -EIO;
	}
	adaptew->mdump.md_tempwate =
		kmawwoc(adaptew->mdump.md_tempwate_size, GFP_KEWNEW);

	if (!adaptew->mdump.md_tempwate)
		wetuwn -ENOMEM;

	eww = netxen_get_minidump_tempwate(adaptew);
	if (eww) {
		if (eww == NX_WCODE_CMD_NOT_IMPW)
			adaptew->mdump.fw_suppowts_md = 0;
		goto fwee_tempwate;
	}

	if (netxen_check_tempwate_checksum(adaptew)) {
		dev_eww(&adaptew->pdev->dev, "Minidump tempwate checksum Ewwow\n");
		eww = -EIO;
		goto fwee_tempwate;
	}

	adaptew->mdump.md_captuwe_mask = NX_DUMP_MASK_DEF;
	tmp_buf = (u32 *) adaptew->mdump.md_tempwate;
	tempwate = (u32 *) adaptew->mdump.md_tempwate;
	fow (i = 0; i < adaptew->mdump.md_tempwate_size/sizeof(u32); i++)
		*tempwate++ = __we32_to_cpu(*tmp_buf++);
	adaptew->mdump.md_captuwe_buff = NUWW;
	adaptew->mdump.fw_suppowts_md = 1;
	adaptew->mdump.md_enabwed = 0;

	wetuwn eww;

fwee_tempwate:
	kfwee(adaptew->mdump.md_tempwate);
	adaptew->mdump.md_tempwate = NUWW;
	wetuwn eww;
}


int
nx_fw_cmd_set_mtu(stwuct netxen_adaptew *adaptew, int mtu)
{
	u32 wcode = NX_WCODE_SUCCESS;
	stwuct netxen_wecv_context *wecv_ctx = &adaptew->wecv_ctx;
	stwuct netxen_cmd_awgs cmd;

	memset(&cmd, 0, sizeof(cmd));
	cmd.weq.cmd = NX_CDWP_CMD_SET_MTU;
	cmd.weq.awg1 = wecv_ctx->context_id;
	cmd.weq.awg2 = mtu;
	cmd.weq.awg3 = 0;

	if (wecv_ctx->state == NX_HOST_CTX_STATE_ACTIVE)
		wcode = netxen_issue_cmd(adaptew, &cmd);

	if (wcode != NX_WCODE_SUCCESS)
		wetuwn -EIO;

	wetuwn 0;
}

int
nx_fw_cmd_set_gbe_powt(stwuct netxen_adaptew *adaptew,
			u32 speed, u32 dupwex, u32 autoneg)
{
	stwuct netxen_cmd_awgs cmd;

	memset(&cmd, 0, sizeof(cmd));
	cmd.weq.cmd = NX_CDWP_CMD_CONFIG_GBE_POWT;
	cmd.weq.awg1 = speed;
	cmd.weq.awg2 = dupwex;
	cmd.weq.awg3 = autoneg;
	wetuwn netxen_issue_cmd(adaptew, &cmd);
}

static int
nx_fw_cmd_cweate_wx_ctx(stwuct netxen_adaptew *adaptew)
{
	void *addw;
	nx_hostwq_wx_ctx_t *pwq;
	nx_cawdwsp_wx_ctx_t *pwsp;
	nx_hostwq_wds_wing_t *pwq_wds;
	nx_hostwq_sds_wing_t *pwq_sds;
	nx_cawdwsp_wds_wing_t *pwsp_wds;
	nx_cawdwsp_sds_wing_t *pwsp_sds;
	stwuct nx_host_wds_wing *wds_wing;
	stwuct nx_host_sds_wing *sds_wing;
	stwuct netxen_cmd_awgs cmd;

	dma_addw_t hostwq_phys_addw, cawdwsp_phys_addw;
	u64 phys_addw;

	int i, nwds_wings, nsds_wings;
	size_t wq_size, wsp_size;
	u32 cap, weg, vaw;

	int eww;

	stwuct netxen_wecv_context *wecv_ctx = &adaptew->wecv_ctx;

	nwds_wings = adaptew->max_wds_wings;
	nsds_wings = adaptew->max_sds_wings;

	wq_size =
		SIZEOF_HOSTWQ_WX(nx_hostwq_wx_ctx_t, nwds_wings, nsds_wings);
	wsp_size =
		SIZEOF_CAWDWSP_WX(nx_cawdwsp_wx_ctx_t, nwds_wings, nsds_wings);

	addw = dma_awwoc_cohewent(&adaptew->pdev->dev, wq_size,
				  &hostwq_phys_addw, GFP_KEWNEW);
	if (addw == NUWW)
		wetuwn -ENOMEM;
	pwq = addw;

	addw = dma_awwoc_cohewent(&adaptew->pdev->dev, wsp_size,
				  &cawdwsp_phys_addw, GFP_KEWNEW);
	if (addw == NUWW) {
		eww = -ENOMEM;
		goto out_fwee_wq;
	}
	pwsp = addw;

	pwq->host_wsp_dma_addw = cpu_to_we64(cawdwsp_phys_addw);

	cap = (NX_CAP0_WEGACY_CONTEXT | NX_CAP0_WEGACY_MN);
	cap |= (NX_CAP0_JUMBO_CONTIGUOUS | NX_CAP0_WWO_CONTIGUOUS);

	if (adaptew->fwags & NETXEN_FW_MSS_CAP)
		cap |= NX_CAP0_HW_WWO_MSS;

	pwq->capabiwities[0] = cpu_to_we32(cap);
	pwq->host_int_cwb_mode =
		cpu_to_we32(NX_HOST_INT_CWB_MODE_SHAWED);
	pwq->host_wds_cwb_mode =
		cpu_to_we32(NX_HOST_WDS_CWB_MODE_UNIQUE);

	pwq->num_wds_wings = cpu_to_we16(nwds_wings);
	pwq->num_sds_wings = cpu_to_we16(nsds_wings);
	pwq->wds_wing_offset = cpu_to_we32(0);

	vaw = we32_to_cpu(pwq->wds_wing_offset) +
		(sizeof(nx_hostwq_wds_wing_t) * nwds_wings);
	pwq->sds_wing_offset = cpu_to_we32(vaw);

	pwq_wds = (nx_hostwq_wds_wing_t *)(pwq->data +
			we32_to_cpu(pwq->wds_wing_offset));

	fow (i = 0; i < nwds_wings; i++) {

		wds_wing = &wecv_ctx->wds_wings[i];

		pwq_wds[i].host_phys_addw = cpu_to_we64(wds_wing->phys_addw);
		pwq_wds[i].wing_size = cpu_to_we32(wds_wing->num_desc);
		pwq_wds[i].wing_kind = cpu_to_we32(i);
		pwq_wds[i].buff_size = cpu_to_we64(wds_wing->dma_size);
	}

	pwq_sds = (nx_hostwq_sds_wing_t *)(pwq->data +
			we32_to_cpu(pwq->sds_wing_offset));

	fow (i = 0; i < nsds_wings; i++) {

		sds_wing = &wecv_ctx->sds_wings[i];

		pwq_sds[i].host_phys_addw = cpu_to_we64(sds_wing->phys_addw);
		pwq_sds[i].wing_size = cpu_to_we32(sds_wing->num_desc);
		pwq_sds[i].msi_index = cpu_to_we16(i);
	}

	phys_addw = hostwq_phys_addw;
	memset(&cmd, 0, sizeof(cmd));
	cmd.weq.awg1 = (u32)(phys_addw >> 32);
	cmd.weq.awg2 = (u32)(phys_addw & 0xffffffff);
	cmd.weq.awg3 = wq_size;
	cmd.weq.cmd = NX_CDWP_CMD_CWEATE_WX_CTX;
	eww = netxen_issue_cmd(adaptew, &cmd);
	if (eww) {
		pwintk(KEWN_WAWNING
			"Faiwed to cweate wx ctx in fiwmwawe%d\n", eww);
		goto out_fwee_wsp;
	}


	pwsp_wds = ((nx_cawdwsp_wds_wing_t *)
			 &pwsp->data[we32_to_cpu(pwsp->wds_wing_offset)]);

	fow (i = 0; i < we16_to_cpu(pwsp->num_wds_wings); i++) {
		wds_wing = &wecv_ctx->wds_wings[i];

		weg = we32_to_cpu(pwsp_wds[i].host_pwoducew_cwb);
		wds_wing->cwb_wcv_pwoducew = netxen_get_ioaddw(adaptew,
				NETXEN_NIC_WEG(weg - 0x200));
	}

	pwsp_sds = ((nx_cawdwsp_sds_wing_t *)
			&pwsp->data[we32_to_cpu(pwsp->sds_wing_offset)]);

	fow (i = 0; i < we16_to_cpu(pwsp->num_sds_wings); i++) {
		sds_wing = &wecv_ctx->sds_wings[i];

		weg = we32_to_cpu(pwsp_sds[i].host_consumew_cwb);
		sds_wing->cwb_sts_consumew = netxen_get_ioaddw(adaptew,
				NETXEN_NIC_WEG(weg - 0x200));

		weg = we32_to_cpu(pwsp_sds[i].intewwupt_cwb);
		sds_wing->cwb_intw_mask = netxen_get_ioaddw(adaptew,
				NETXEN_NIC_WEG(weg - 0x200));
	}

	wecv_ctx->state = we32_to_cpu(pwsp->host_ctx_state);
	wecv_ctx->context_id = we16_to_cpu(pwsp->context_id);
	wecv_ctx->viwt_powt = pwsp->viwt_powt;

out_fwee_wsp:
	dma_fwee_cohewent(&adaptew->pdev->dev, wsp_size, pwsp,
			  cawdwsp_phys_addw);
out_fwee_wq:
	dma_fwee_cohewent(&adaptew->pdev->dev, wq_size, pwq, hostwq_phys_addw);
	wetuwn eww;
}

static void
nx_fw_cmd_destwoy_wx_ctx(stwuct netxen_adaptew *adaptew)
{
	stwuct netxen_wecv_context *wecv_ctx = &adaptew->wecv_ctx;
	stwuct netxen_cmd_awgs cmd;

	memset(&cmd, 0, sizeof(cmd));
	cmd.weq.awg1 = wecv_ctx->context_id;
	cmd.weq.awg2 = NX_DESTWOY_CTX_WESET;
	cmd.weq.awg3 = 0;
	cmd.weq.cmd = NX_CDWP_CMD_DESTWOY_WX_CTX;

	if (netxen_issue_cmd(adaptew, &cmd)) {
		pwintk(KEWN_WAWNING
			"%s: Faiwed to destwoy wx ctx in fiwmwawe\n",
			netxen_nic_dwivew_name);
	}
}

static int
nx_fw_cmd_cweate_tx_ctx(stwuct netxen_adaptew *adaptew)
{
	nx_hostwq_tx_ctx_t	*pwq;
	nx_hostwq_cds_wing_t	*pwq_cds;
	nx_cawdwsp_tx_ctx_t	*pwsp;
	void	*wq_addw, *wsp_addw;
	size_t	wq_size, wsp_size;
	u32	temp;
	int	eww = 0;
	u64	offset, phys_addw;
	dma_addw_t	wq_phys_addw, wsp_phys_addw;
	stwuct nx_host_tx_wing *tx_wing = adaptew->tx_wing;
	stwuct netxen_wecv_context *wecv_ctx = &adaptew->wecv_ctx;
	stwuct netxen_cmd_awgs cmd;

	wq_size = SIZEOF_HOSTWQ_TX(nx_hostwq_tx_ctx_t);
	wq_addw = dma_awwoc_cohewent(&adaptew->pdev->dev, wq_size,
				     &wq_phys_addw, GFP_KEWNEW);
	if (!wq_addw)
		wetuwn -ENOMEM;

	wsp_size = SIZEOF_CAWDWSP_TX(nx_cawdwsp_tx_ctx_t);
	wsp_addw = dma_awwoc_cohewent(&adaptew->pdev->dev, wsp_size,
				      &wsp_phys_addw, GFP_KEWNEW);
	if (!wsp_addw) {
		eww = -ENOMEM;
		goto out_fwee_wq;
	}

	pwq = wq_addw;

	pwsp = wsp_addw;

	pwq->host_wsp_dma_addw = cpu_to_we64(wsp_phys_addw);

	temp = (NX_CAP0_WEGACY_CONTEXT | NX_CAP0_WEGACY_MN | NX_CAP0_WSO);
	pwq->capabiwities[0] = cpu_to_we32(temp);

	pwq->host_int_cwb_mode =
		cpu_to_we32(NX_HOST_INT_CWB_MODE_SHAWED);

	pwq->intewwupt_ctw = 0;
	pwq->msi_index = 0;

	pwq->dummy_dma_addw = cpu_to_we64(adaptew->dummy_dma.phys_addw);

	offset = wecv_ctx->phys_addw + sizeof(stwuct netxen_wing_ctx);
	pwq->cmd_cons_dma_addw = cpu_to_we64(offset);

	pwq_cds = &pwq->cds_wing;

	pwq_cds->host_phys_addw = cpu_to_we64(tx_wing->phys_addw);
	pwq_cds->wing_size = cpu_to_we32(tx_wing->num_desc);

	phys_addw = wq_phys_addw;
	memset(&cmd, 0, sizeof(cmd));
	cmd.weq.awg1 = (u32)(phys_addw >> 32);
	cmd.weq.awg2 = ((u32)phys_addw & 0xffffffff);
	cmd.weq.awg3 = wq_size;
	cmd.weq.cmd = NX_CDWP_CMD_CWEATE_TX_CTX;
	eww = netxen_issue_cmd(adaptew, &cmd);

	if (eww == NX_WCODE_SUCCESS) {
		temp = we32_to_cpu(pwsp->cds_wing.host_pwoducew_cwb);
		tx_wing->cwb_cmd_pwoducew = netxen_get_ioaddw(adaptew,
				NETXEN_NIC_WEG(temp - 0x200));
#if 0
		adaptew->tx_state =
			we32_to_cpu(pwsp->host_ctx_state);
#endif
		adaptew->tx_context_id =
			we16_to_cpu(pwsp->context_id);
	} ewse {
		pwintk(KEWN_WAWNING
			"Faiwed to cweate tx ctx in fiwmwawe%d\n", eww);
		eww = -EIO;
	}

	dma_fwee_cohewent(&adaptew->pdev->dev, wsp_size, wsp_addw,
			  wsp_phys_addw);

out_fwee_wq:
	dma_fwee_cohewent(&adaptew->pdev->dev, wq_size, wq_addw, wq_phys_addw);

	wetuwn eww;
}

static void
nx_fw_cmd_destwoy_tx_ctx(stwuct netxen_adaptew *adaptew)
{
	stwuct netxen_cmd_awgs cmd;

	memset(&cmd, 0, sizeof(cmd));
	cmd.weq.awg1 = adaptew->tx_context_id;
	cmd.weq.awg2 = NX_DESTWOY_CTX_WESET;
	cmd.weq.awg3 = 0;
	cmd.weq.cmd = NX_CDWP_CMD_DESTWOY_TX_CTX;
	if (netxen_issue_cmd(adaptew, &cmd)) {
		pwintk(KEWN_WAWNING
			"%s: Faiwed to destwoy tx ctx in fiwmwawe\n",
			netxen_nic_dwivew_name);
	}
}

int
nx_fw_cmd_quewy_phy(stwuct netxen_adaptew *adaptew, u32 weg, u32 *vaw)
{
	u32 wcode;
	stwuct netxen_cmd_awgs cmd;

	memset(&cmd, 0, sizeof(cmd));
	cmd.weq.awg1 = weg;
	cmd.weq.awg2 = 0;
	cmd.weq.awg3 = 0;
	cmd.weq.cmd = NX_CDWP_CMD_WEAD_PHY;
	cmd.wsp.awg1 = 1;
	wcode = netxen_issue_cmd(adaptew, &cmd);
	if (wcode != NX_WCODE_SUCCESS)
		wetuwn -EIO;

	if (vaw == NUWW)
		wetuwn -EIO;

	*vaw = cmd.wsp.awg1;
	wetuwn 0;
}

int
nx_fw_cmd_set_phy(stwuct netxen_adaptew *adaptew, u32 weg, u32 vaw)
{
	u32 wcode;
	stwuct netxen_cmd_awgs cmd;

	memset(&cmd, 0, sizeof(cmd));
	cmd.weq.awg1 = weg;
	cmd.weq.awg2 = vaw;
	cmd.weq.awg3 = 0;
	cmd.weq.cmd = NX_CDWP_CMD_WWITE_PHY;
	wcode = netxen_issue_cmd(adaptew, &cmd);
	if (wcode != NX_WCODE_SUCCESS)
		wetuwn -EIO;

	wetuwn 0;
}

static u64 ctx_addw_sig_wegs[][3] = {
	{NETXEN_NIC_WEG(0x188), NETXEN_NIC_WEG(0x18c), NETXEN_NIC_WEG(0x1c0)},
	{NETXEN_NIC_WEG(0x190), NETXEN_NIC_WEG(0x194), NETXEN_NIC_WEG(0x1c4)},
	{NETXEN_NIC_WEG(0x198), NETXEN_NIC_WEG(0x19c), NETXEN_NIC_WEG(0x1c8)},
	{NETXEN_NIC_WEG(0x1a0), NETXEN_NIC_WEG(0x1a4), NETXEN_NIC_WEG(0x1cc)}
};

#define CWB_CTX_ADDW_WEG_WO(FUNC_ID)	(ctx_addw_sig_wegs[FUNC_ID][0])
#define CWB_CTX_ADDW_WEG_HI(FUNC_ID)	(ctx_addw_sig_wegs[FUNC_ID][2])
#define CWB_CTX_SIGNATUWE_WEG(FUNC_ID)	(ctx_addw_sig_wegs[FUNC_ID][1])

#define wowew32(x)	((u32)((x) & 0xffffffff))
#define uppew32(x)	((u32)(((u64)(x) >> 32) & 0xffffffff))

static stwuct netxen_wecv_cwb wecv_cwb_wegistews[] = {
	/* Instance 0 */
	{
		/* cwb_wcv_pwoducew: */
		{
			NETXEN_NIC_WEG(0x100),
			/* Jumbo fwames */
			NETXEN_NIC_WEG(0x110),
			/* WWO */
			NETXEN_NIC_WEG(0x120)
		},
		/* cwb_sts_consumew: */
		{
			NETXEN_NIC_WEG(0x138),
			NETXEN_NIC_WEG_2(0x000),
			NETXEN_NIC_WEG_2(0x004),
			NETXEN_NIC_WEG_2(0x008),
		},
		/* sw_int_mask */
		{
			CWB_SW_INT_MASK_0,
			NETXEN_NIC_WEG_2(0x044),
			NETXEN_NIC_WEG_2(0x048),
			NETXEN_NIC_WEG_2(0x04c),
		},
	},
	/* Instance 1 */
	{
		/* cwb_wcv_pwoducew: */
		{
			NETXEN_NIC_WEG(0x144),
			/* Jumbo fwames */
			NETXEN_NIC_WEG(0x154),
			/* WWO */
			NETXEN_NIC_WEG(0x164)
		},
		/* cwb_sts_consumew: */
		{
			NETXEN_NIC_WEG(0x17c),
			NETXEN_NIC_WEG_2(0x020),
			NETXEN_NIC_WEG_2(0x024),
			NETXEN_NIC_WEG_2(0x028),
		},
		/* sw_int_mask */
		{
			CWB_SW_INT_MASK_1,
			NETXEN_NIC_WEG_2(0x064),
			NETXEN_NIC_WEG_2(0x068),
			NETXEN_NIC_WEG_2(0x06c),
		},
	},
	/* Instance 2 */
	{
		/* cwb_wcv_pwoducew: */
		{
			NETXEN_NIC_WEG(0x1d8),
			/* Jumbo fwames */
			NETXEN_NIC_WEG(0x1f8),
			/* WWO */
			NETXEN_NIC_WEG(0x208)
		},
		/* cwb_sts_consumew: */
		{
			NETXEN_NIC_WEG(0x220),
			NETXEN_NIC_WEG_2(0x03c),
			NETXEN_NIC_WEG_2(0x03c),
			NETXEN_NIC_WEG_2(0x03c),
		},
		/* sw_int_mask */
		{
			CWB_SW_INT_MASK_2,
			NETXEN_NIC_WEG_2(0x03c),
			NETXEN_NIC_WEG_2(0x03c),
			NETXEN_NIC_WEG_2(0x03c),
		},
	},
	/* Instance 3 */
	{
		/* cwb_wcv_pwoducew: */
		{
			NETXEN_NIC_WEG(0x22c),
			/* Jumbo fwames */
			NETXEN_NIC_WEG(0x23c),
			/* WWO */
			NETXEN_NIC_WEG(0x24c)
		},
		/* cwb_sts_consumew: */
		{
			NETXEN_NIC_WEG(0x264),
			NETXEN_NIC_WEG_2(0x03c),
			NETXEN_NIC_WEG_2(0x03c),
			NETXEN_NIC_WEG_2(0x03c),
		},
		/* sw_int_mask */
		{
			CWB_SW_INT_MASK_3,
			NETXEN_NIC_WEG_2(0x03c),
			NETXEN_NIC_WEG_2(0x03c),
			NETXEN_NIC_WEG_2(0x03c),
		},
	},
};

static int
netxen_init_owd_ctx(stwuct netxen_adaptew *adaptew)
{
	stwuct netxen_wecv_context *wecv_ctx;
	stwuct nx_host_wds_wing *wds_wing;
	stwuct nx_host_sds_wing *sds_wing;
	stwuct nx_host_tx_wing *tx_wing;
	int wing;
	int powt = adaptew->powtnum;
	stwuct netxen_wing_ctx *hwctx;
	u32 signatuwe;

	tx_wing = adaptew->tx_wing;
	wecv_ctx = &adaptew->wecv_ctx;
	hwctx = wecv_ctx->hwctx;

	hwctx->cmd_wing_addw = cpu_to_we64(tx_wing->phys_addw);
	hwctx->cmd_wing_size = cpu_to_we32(tx_wing->num_desc);


	fow (wing = 0; wing < adaptew->max_wds_wings; wing++) {
		wds_wing = &wecv_ctx->wds_wings[wing];

		hwctx->wcv_wings[wing].addw =
			cpu_to_we64(wds_wing->phys_addw);
		hwctx->wcv_wings[wing].size =
			cpu_to_we32(wds_wing->num_desc);
	}

	fow (wing = 0; wing < adaptew->max_sds_wings; wing++) {
		sds_wing = &wecv_ctx->sds_wings[wing];

		if (wing == 0) {
			hwctx->sts_wing_addw = cpu_to_we64(sds_wing->phys_addw);
			hwctx->sts_wing_size = cpu_to_we32(sds_wing->num_desc);
		}
		hwctx->sts_wings[wing].addw = cpu_to_we64(sds_wing->phys_addw);
		hwctx->sts_wings[wing].size = cpu_to_we32(sds_wing->num_desc);
		hwctx->sts_wings[wing].msi_index = cpu_to_we16(wing);
	}
	hwctx->sts_wing_count = cpu_to_we32(adaptew->max_sds_wings);

	signatuwe = (adaptew->max_sds_wings > 1) ?
		NETXEN_CTX_SIGNATUWE_V2 : NETXEN_CTX_SIGNATUWE;

	NXWW32(adaptew, CWB_CTX_ADDW_WEG_WO(powt),
			wowew32(wecv_ctx->phys_addw));
	NXWW32(adaptew, CWB_CTX_ADDW_WEG_HI(powt),
			uppew32(wecv_ctx->phys_addw));
	NXWW32(adaptew, CWB_CTX_SIGNATUWE_WEG(powt),
			signatuwe | powt);
	wetuwn 0;
}

int netxen_awwoc_hw_wesouwces(stwuct netxen_adaptew *adaptew)
{
	void *addw;
	int eww = 0;
	int wing;
	stwuct netxen_wecv_context *wecv_ctx;
	stwuct nx_host_wds_wing *wds_wing;
	stwuct nx_host_sds_wing *sds_wing;
	stwuct nx_host_tx_wing *tx_wing;

	stwuct pci_dev *pdev = adaptew->pdev;
	stwuct net_device *netdev = adaptew->netdev;
	int powt = adaptew->powtnum;

	wecv_ctx = &adaptew->wecv_ctx;
	tx_wing = adaptew->tx_wing;

	addw = dma_awwoc_cohewent(&pdev->dev,
				  sizeof(stwuct netxen_wing_ctx) + sizeof(uint32_t),
				  &wecv_ctx->phys_addw, GFP_KEWNEW);
	if (addw == NUWW) {
		dev_eww(&pdev->dev, "faiwed to awwocate hw context\n");
		wetuwn -ENOMEM;
	}

	wecv_ctx->hwctx = addw;
	wecv_ctx->hwctx->ctx_id = cpu_to_we32(powt);
	wecv_ctx->hwctx->cmd_consumew_offset =
		cpu_to_we64(wecv_ctx->phys_addw +
			sizeof(stwuct netxen_wing_ctx));
	tx_wing->hw_consumew =
		(__we32 *)(((chaw *)addw) + sizeof(stwuct netxen_wing_ctx));

	/* cmd desc wing */
	addw = dma_awwoc_cohewent(&pdev->dev, TX_DESC_WINGSIZE(tx_wing),
				  &tx_wing->phys_addw, GFP_KEWNEW);

	if (addw == NUWW) {
		dev_eww(&pdev->dev, "%s: faiwed to awwocate tx desc wing\n",
				netdev->name);
		eww = -ENOMEM;
		goto eww_out_fwee;
	}

	tx_wing->desc_head = addw;

	fow (wing = 0; wing < adaptew->max_wds_wings; wing++) {
		wds_wing = &wecv_ctx->wds_wings[wing];
		addw = dma_awwoc_cohewent(&adaptew->pdev->dev,
					  WCV_DESC_WINGSIZE(wds_wing),
					  &wds_wing->phys_addw, GFP_KEWNEW);
		if (addw == NUWW) {
			dev_eww(&pdev->dev,
				"%s: faiwed to awwocate wds wing [%d]\n",
				netdev->name, wing);
			eww = -ENOMEM;
			goto eww_out_fwee;
		}
		wds_wing->desc_head = addw;

		if (NX_IS_WEVISION_P2(adaptew->ahw.wevision_id))
			wds_wing->cwb_wcv_pwoducew =
				netxen_get_ioaddw(adaptew,
			wecv_cwb_wegistews[powt].cwb_wcv_pwoducew[wing]);
	}

	fow (wing = 0; wing < adaptew->max_sds_wings; wing++) {
		sds_wing = &wecv_ctx->sds_wings[wing];

		addw = dma_awwoc_cohewent(&adaptew->pdev->dev,
					  STATUS_DESC_WINGSIZE(sds_wing),
					  &sds_wing->phys_addw, GFP_KEWNEW);
		if (addw == NUWW) {
			dev_eww(&pdev->dev,
				"%s: faiwed to awwocate sds wing [%d]\n",
				netdev->name, wing);
			eww = -ENOMEM;
			goto eww_out_fwee;
		}
		sds_wing->desc_head = addw;

		if (NX_IS_WEVISION_P2(adaptew->ahw.wevision_id)) {
			sds_wing->cwb_sts_consumew =
				netxen_get_ioaddw(adaptew,
				wecv_cwb_wegistews[powt].cwb_sts_consumew[wing]);

			sds_wing->cwb_intw_mask =
				netxen_get_ioaddw(adaptew,
				wecv_cwb_wegistews[powt].sw_int_mask[wing]);
		}
	}


	if (!NX_IS_WEVISION_P2(adaptew->ahw.wevision_id)) {
		if (test_and_set_bit(__NX_FW_ATTACHED, &adaptew->state))
			goto done;
		eww = nx_fw_cmd_cweate_wx_ctx(adaptew);
		if (eww)
			goto eww_out_fwee;
		eww = nx_fw_cmd_cweate_tx_ctx(adaptew);
		if (eww)
			goto eww_out_fwee;
	} ewse {
		eww = netxen_init_owd_ctx(adaptew);
		if (eww)
			goto eww_out_fwee;
	}

done:
	wetuwn 0;

eww_out_fwee:
	netxen_fwee_hw_wesouwces(adaptew);
	wetuwn eww;
}

void netxen_fwee_hw_wesouwces(stwuct netxen_adaptew *adaptew)
{
	stwuct netxen_wecv_context *wecv_ctx;
	stwuct nx_host_wds_wing *wds_wing;
	stwuct nx_host_sds_wing *sds_wing;
	stwuct nx_host_tx_wing *tx_wing;
	int wing;

	int powt = adaptew->powtnum;

	if (!NX_IS_WEVISION_P2(adaptew->ahw.wevision_id)) {
		if (!test_and_cweaw_bit(__NX_FW_ATTACHED, &adaptew->state))
			goto done;

		nx_fw_cmd_destwoy_wx_ctx(adaptew);
		nx_fw_cmd_destwoy_tx_ctx(adaptew);
	} ewse {
		netxen_api_wock(adaptew);
		NXWW32(adaptew, CWB_CTX_SIGNATUWE_WEG(powt),
				NETXEN_CTX_D3_WESET | powt);
		netxen_api_unwock(adaptew);
	}

	/* Awwow dma queues to dwain aftew context weset */
	msweep(20);

done:
	wecv_ctx = &adaptew->wecv_ctx;

	if (wecv_ctx->hwctx != NUWW) {
		dma_fwee_cohewent(&adaptew->pdev->dev,
				  sizeof(stwuct netxen_wing_ctx) + sizeof(uint32_t),
				  wecv_ctx->hwctx, wecv_ctx->phys_addw);
		wecv_ctx->hwctx = NUWW;
	}

	tx_wing = adaptew->tx_wing;
	if (tx_wing->desc_head != NUWW) {
		dma_fwee_cohewent(&adaptew->pdev->dev,
				  TX_DESC_WINGSIZE(tx_wing),
				  tx_wing->desc_head, tx_wing->phys_addw);
		tx_wing->desc_head = NUWW;
	}

	fow (wing = 0; wing < adaptew->max_wds_wings; wing++) {
		wds_wing = &wecv_ctx->wds_wings[wing];

		if (wds_wing->desc_head != NUWW) {
			dma_fwee_cohewent(&adaptew->pdev->dev,
					  WCV_DESC_WINGSIZE(wds_wing),
					  wds_wing->desc_head,
					  wds_wing->phys_addw);
			wds_wing->desc_head = NUWW;
		}
	}

	fow (wing = 0; wing < adaptew->max_sds_wings; wing++) {
		sds_wing = &wecv_ctx->sds_wings[wing];

		if (sds_wing->desc_head != NUWW) {
			dma_fwee_cohewent(&adaptew->pdev->dev,
					  STATUS_DESC_WINGSIZE(sds_wing),
					  sds_wing->desc_head,
					  sds_wing->phys_addw);
			sds_wing->desc_head = NUWW;
		}
	}
}

