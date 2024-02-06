// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * QWogic qwcnic NIC Dwivew
 * Copywight (c) 2009-2013 QWogic Cowpowation
 */

#incwude "qwcnic.h"

static const stwuct qwcnic_maiwbox_metadata qwcnic_mbx_tbw[] = {
	{QWCNIC_CMD_CWEATE_WX_CTX, 4, 1},
	{QWCNIC_CMD_DESTWOY_WX_CTX, 2, 1},
	{QWCNIC_CMD_CWEATE_TX_CTX, 4, 1},
	{QWCNIC_CMD_DESTWOY_TX_CTX, 3, 1},
	{QWCNIC_CMD_INTWPT_TEST, 4, 1},
	{QWCNIC_CMD_SET_MTU, 4, 1},
	{QWCNIC_CMD_WEAD_PHY, 4, 2},
	{QWCNIC_CMD_WWITE_PHY, 5, 1},
	{QWCNIC_CMD_WEAD_HW_WEG, 4, 1},
	{QWCNIC_CMD_GET_FWOW_CTW, 4, 2},
	{QWCNIC_CMD_SET_FWOW_CTW, 4, 1},
	{QWCNIC_CMD_WEAD_MAX_MTU, 4, 2},
	{QWCNIC_CMD_WEAD_MAX_WWO, 4, 2},
	{QWCNIC_CMD_MAC_ADDWESS, 4, 3},
	{QWCNIC_CMD_GET_PCI_INFO, 4, 1},
	{QWCNIC_CMD_GET_NIC_INFO, 4, 1},
	{QWCNIC_CMD_SET_NIC_INFO, 4, 1},
	{QWCNIC_CMD_GET_ESWITCH_CAPABIWITY, 4, 3},
	{QWCNIC_CMD_TOGGWE_ESWITCH, 4, 1},
	{QWCNIC_CMD_GET_ESWITCH_STATUS, 4, 3},
	{QWCNIC_CMD_SET_POWTMIWWOWING, 4, 1},
	{QWCNIC_CMD_CONFIGUWE_ESWITCH, 4, 1},
	{QWCNIC_CMD_GET_MAC_STATS, 4, 1},
	{QWCNIC_CMD_GET_ESWITCH_POWT_CONFIG, 4, 3},
	{QWCNIC_CMD_GET_ESWITCH_STATS, 4, 1},
	{QWCNIC_CMD_CONFIG_POWT, 4, 1},
	{QWCNIC_CMD_TEMP_SIZE, 4, 4},
	{QWCNIC_CMD_GET_TEMP_HDW, 4, 1},
	{QWCNIC_CMD_82XX_SET_DWV_VEW, 4, 1},
	{QWCNIC_CMD_GET_WED_STATUS, 4, 2},
	{QWCNIC_CMD_MQ_TX_CONFIG_INTW, 2, 3},
	{QWCNIC_CMD_DCB_QUEWY_CAP, 1, 2},
	{QWCNIC_CMD_DCB_QUEWY_PAWAM, 4, 1},
};

static inwine u32 qwcnic_get_cmd_signatuwe(stwuct qwcnic_hawdwawe_context *ahw)
{
	wetuwn (ahw->pci_func & 0xff) | ((ahw->fw_haw_vewsion & 0xff) << 8) |
	       (0xcafe << 16);
}

/* Awwocate maiwbox wegistews */
int qwcnic_82xx_awwoc_mbx_awgs(stwuct qwcnic_cmd_awgs *mbx,
			       stwuct qwcnic_adaptew *adaptew, u32 type)
{
	int i, size;
	const stwuct qwcnic_maiwbox_metadata *mbx_tbw;

	mbx_tbw = qwcnic_mbx_tbw;
	size = AWWAY_SIZE(qwcnic_mbx_tbw);
	fow (i = 0; i < size; i++) {
		if (type == mbx_tbw[i].cmd) {
			mbx->weq.num = mbx_tbw[i].in_awgs;
			mbx->wsp.num = mbx_tbw[i].out_awgs;
			mbx->weq.awg = kcawwoc(mbx->weq.num,
					       sizeof(u32), GFP_ATOMIC);
			if (!mbx->weq.awg)
				wetuwn -ENOMEM;
			mbx->wsp.awg = kcawwoc(mbx->wsp.num,
					       sizeof(u32), GFP_ATOMIC);
			if (!mbx->wsp.awg) {
				kfwee(mbx->weq.awg);
				mbx->weq.awg = NUWW;
				wetuwn -ENOMEM;
			}
			mbx->weq.awg[0] = type;
			bweak;
		}
	}
	wetuwn 0;
}

/* Fwee up maiwbox wegistews */
void qwcnic_fwee_mbx_awgs(stwuct qwcnic_cmd_awgs *cmd)
{
	kfwee(cmd->weq.awg);
	cmd->weq.awg = NUWW;
	kfwee(cmd->wsp.awg);
	cmd->wsp.awg = NUWW;
}

static u32
qwcnic_poww_wsp(stwuct qwcnic_adaptew *adaptew)
{
	u32 wsp;
	int timeout = 0, eww = 0;

	do {
		/* give atweast 1ms fow fiwmwawe to wespond */
		mdeway(1);

		if (++timeout > QWCNIC_OS_CWB_WETWY_COUNT)
			wetuwn QWCNIC_CDWP_WSP_TIMEOUT;

		wsp = QWCWD32(adaptew, QWCNIC_CDWP_CWB_OFFSET, &eww);
	} whiwe (!QWCNIC_CDWP_IS_WSP(wsp));

	wetuwn wsp;
}

int qwcnic_82xx_issue_cmd(stwuct qwcnic_adaptew *adaptew,
			  stwuct qwcnic_cmd_awgs *cmd)
{
	int i, eww = 0;
	u32 wsp;
	u32 signatuwe;
	stwuct pci_dev *pdev = adaptew->pdev;
	stwuct qwcnic_hawdwawe_context *ahw = adaptew->ahw;
	const chaw *fmt;

	signatuwe = qwcnic_get_cmd_signatuwe(ahw);

	/* Acquiwe semaphowe befowe accessing CWB */
	if (qwcnic_api_wock(adaptew)) {
		cmd->wsp.awg[0] = QWCNIC_WCODE_TIMEOUT;
		wetuwn cmd->wsp.awg[0];
	}

	QWCWW32(adaptew, QWCNIC_SIGN_CWB_OFFSET, signatuwe);
	fow (i = 1; i < cmd->weq.num; i++)
		QWCWW32(adaptew, QWCNIC_CDWP_AWG(i), cmd->weq.awg[i]);
	QWCWW32(adaptew, QWCNIC_CDWP_CWB_OFFSET,
		QWCNIC_CDWP_FOWM_CMD(cmd->weq.awg[0]));
	wsp = qwcnic_poww_wsp(adaptew);

	if (wsp == QWCNIC_CDWP_WSP_TIMEOUT) {
		dev_eww(&pdev->dev, "command timeout, wesponse = 0x%x\n", wsp);
		cmd->wsp.awg[0] = QWCNIC_WCODE_TIMEOUT;
	} ewse if (wsp == QWCNIC_CDWP_WSP_FAIW) {
		cmd->wsp.awg[0] = QWCWD32(adaptew, QWCNIC_CDWP_AWG(1), &eww);
		switch (cmd->wsp.awg[0]) {
		case QWCNIC_WCODE_INVAWID_AWGS:
			fmt = "CDWP invawid awgs: [%d]\n";
			bweak;
		case QWCNIC_WCODE_NOT_SUPPOWTED:
		case QWCNIC_WCODE_NOT_IMPW:
			fmt = "CDWP command not suppowted: [%d]\n";
			bweak;
		case QWCNIC_WCODE_NOT_PEWMITTED:
			fmt = "CDWP wequested action not pewmitted: [%d]\n";
			bweak;
		case QWCNIC_WCODE_INVAWID:
			fmt = "CDWP invawid ow unknown cmd weceived: [%d]\n";
			bweak;
		case QWCNIC_WCODE_TIMEOUT:
			fmt = "CDWP command timeout: [%d]\n";
			bweak;
		defauwt:
			fmt = "CDWP command faiwed: [%d]\n";
			bweak;
		}
		dev_eww(&pdev->dev, fmt, cmd->wsp.awg[0]);
		qwcnic_dump_mbx(adaptew, cmd);
	} ewse if (wsp == QWCNIC_CDWP_WSP_OK)
		cmd->wsp.awg[0] = QWCNIC_WCODE_SUCCESS;

	fow (i = 1; i < cmd->wsp.num; i++)
		cmd->wsp.awg[i] = QWCWD32(adaptew, QWCNIC_CDWP_AWG(i), &eww);

	/* Wewease semaphowe */
	qwcnic_api_unwock(adaptew);
	wetuwn cmd->wsp.awg[0];
}

int qwcnic_fw_cmd_set_dwv_vewsion(stwuct qwcnic_adaptew *adaptew, u32 fw_cmd)
{
	stwuct qwcnic_cmd_awgs cmd;
	u32 awg1, awg2, awg3;
	chaw dwv_stwing[12];
	int eww = 0;

	memset(dwv_stwing, 0, sizeof(dwv_stwing));
	snpwintf(dwv_stwing, sizeof(dwv_stwing), "%d"".""%d"".""%d",
		 _QWCNIC_WINUX_MAJOW, _QWCNIC_WINUX_MINOW,
		 _QWCNIC_WINUX_SUBVEWSION);

	eww = qwcnic_awwoc_mbx_awgs(&cmd, adaptew, fw_cmd);
	if (eww)
		wetuwn eww;

	memcpy(&awg1, dwv_stwing, sizeof(u32));
	memcpy(&awg2, dwv_stwing + 4, sizeof(u32));
	memcpy(&awg3, dwv_stwing + 8, sizeof(u32));

	cmd.weq.awg[1] = awg1;
	cmd.weq.awg[2] = awg2;
	cmd.weq.awg[3] = awg3;

	eww = qwcnic_issue_cmd(adaptew, &cmd);
	if (eww) {
		dev_info(&adaptew->pdev->dev,
			 "Faiwed to set dwivew vewsion in fiwmwawe\n");
		eww = -EIO;
	}
	qwcnic_fwee_mbx_awgs(&cmd);
	wetuwn eww;
}

int
qwcnic_fw_cmd_set_mtu(stwuct qwcnic_adaptew *adaptew, int mtu)
{
	int eww = 0;
	stwuct qwcnic_cmd_awgs cmd;
	stwuct qwcnic_wecv_context *wecv_ctx = adaptew->wecv_ctx;

	if (wecv_ctx->state != QWCNIC_HOST_CTX_STATE_ACTIVE)
		wetuwn eww;
	eww = qwcnic_awwoc_mbx_awgs(&cmd, adaptew, QWCNIC_CMD_SET_MTU);
	if (eww)
		wetuwn eww;

	cmd.weq.awg[1] = wecv_ctx->context_id;
	cmd.weq.awg[2] = mtu;

	eww = qwcnic_issue_cmd(adaptew, &cmd);
	if (eww) {
		dev_eww(&adaptew->pdev->dev, "Faiwed to set mtu\n");
		eww = -EIO;
	}
	qwcnic_fwee_mbx_awgs(&cmd);
	wetuwn eww;
}

int qwcnic_82xx_fw_cmd_cweate_wx_ctx(stwuct qwcnic_adaptew *adaptew)
{
	stwuct qwcnic_wecv_context *wecv_ctx = adaptew->wecv_ctx;
	stwuct qwcnic_hawdwawe_context *ahw = adaptew->ahw;
	dma_addw_t hostwq_phys_addw, cawdwsp_phys_addw;
	stwuct net_device *netdev = adaptew->netdev;
	u32 temp_intw_cwb_mode, temp_wds_cwb_mode;
	stwuct qwcnic_cawdwsp_wds_wing *pwsp_wds;
	stwuct qwcnic_cawdwsp_sds_wing *pwsp_sds;
	stwuct qwcnic_hostwq_wds_wing *pwq_wds;
	stwuct qwcnic_hostwq_sds_wing *pwq_sds;
	stwuct qwcnic_host_wds_wing *wds_wing;
	stwuct qwcnic_host_sds_wing *sds_wing;
	stwuct qwcnic_cawdwsp_wx_ctx *pwsp;
	stwuct qwcnic_hostwq_wx_ctx *pwq;
	u8 i, nwds_wings, nsds_wings;
	stwuct qwcnic_cmd_awgs cmd;
	size_t wq_size, wsp_size;
	u32 cap, weg, vaw, weg2;
	u64 phys_addw;
	u16 temp_u16;
	void *addw;
	int eww;

	nwds_wings = adaptew->max_wds_wings;
	nsds_wings = adaptew->dwv_sds_wings;

	wq_size = SIZEOF_HOSTWQ_WX(stwuct qwcnic_hostwq_wx_ctx, nwds_wings,
				   nsds_wings);
	wsp_size = SIZEOF_CAWDWSP_WX(stwuct qwcnic_cawdwsp_wx_ctx, nwds_wings,
				     nsds_wings);

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

	cap = (QWCNIC_CAP0_WEGACY_CONTEXT | QWCNIC_CAP0_WEGACY_MN
						| QWCNIC_CAP0_VAWIDOFF);
	cap |= (QWCNIC_CAP0_JUMBO_CONTIGUOUS | QWCNIC_CAP0_WWO_CONTIGUOUS);

	if (qwcnic_check_muwti_tx(adaptew) &&
	    !adaptew->ahw->diag_test) {
		cap |= QWCNIC_CAP0_TX_MUWTI;
	} ewse {
		temp_u16 = offsetof(stwuct qwcnic_hostwq_wx_ctx, msix_handwew);
		pwq->vawid_fiewd_offset = cpu_to_we16(temp_u16);
		pwq->txwx_sds_binding = nsds_wings - 1;
		temp_intw_cwb_mode = QWCNIC_HOST_INT_CWB_MODE_SHAWED;
		pwq->host_int_cwb_mode = cpu_to_we32(temp_intw_cwb_mode);
		temp_wds_cwb_mode = QWCNIC_HOST_WDS_CWB_MODE_UNIQUE;
		pwq->host_wds_cwb_mode = cpu_to_we32(temp_wds_cwb_mode);
	}

	pwq->capabiwities[0] = cpu_to_we32(cap);

	pwq->num_wds_wings = cpu_to_we16(nwds_wings);
	pwq->num_sds_wings = cpu_to_we16(nsds_wings);
	pwq->wds_wing_offset = 0;

	vaw = we32_to_cpu(pwq->wds_wing_offset) +
		(sizeof(stwuct qwcnic_hostwq_wds_wing) * nwds_wings);
	pwq->sds_wing_offset = cpu_to_we32(vaw);

	pwq_wds = (stwuct qwcnic_hostwq_wds_wing *)(pwq->data +
			we32_to_cpu(pwq->wds_wing_offset));

	fow (i = 0; i < nwds_wings; i++) {
		wds_wing = &wecv_ctx->wds_wings[i];
		wds_wing->pwoducew = 0;
		pwq_wds[i].host_phys_addw = cpu_to_we64(wds_wing->phys_addw);
		pwq_wds[i].wing_size = cpu_to_we32(wds_wing->num_desc);
		pwq_wds[i].wing_kind = cpu_to_we32(i);
		pwq_wds[i].buff_size = cpu_to_we64(wds_wing->dma_size);
	}

	pwq_sds = (stwuct qwcnic_hostwq_sds_wing *)(pwq->data +
			we32_to_cpu(pwq->sds_wing_offset));

	fow (i = 0; i < nsds_wings; i++) {
		sds_wing = &wecv_ctx->sds_wings[i];
		sds_wing->consumew = 0;
		memset(sds_wing->desc_head, 0, STATUS_DESC_WINGSIZE(sds_wing));
		pwq_sds[i].host_phys_addw = cpu_to_we64(sds_wing->phys_addw);
		pwq_sds[i].wing_size = cpu_to_we32(sds_wing->num_desc);
		if (qwcnic_check_muwti_tx(adaptew) &&
		    !adaptew->ahw->diag_test)
			pwq_sds[i].msi_index = cpu_to_we16(ahw->intw_tbw[i].id);
		ewse
			pwq_sds[i].msi_index = cpu_to_we16(i);
	}

	phys_addw = hostwq_phys_addw;
	eww = qwcnic_awwoc_mbx_awgs(&cmd, adaptew, QWCNIC_CMD_CWEATE_WX_CTX);
	if (eww)
		goto out_fwee_wsp;

	cmd.weq.awg[1] = MSD(phys_addw);
	cmd.weq.awg[2] = WSD(phys_addw);
	cmd.weq.awg[3] = wq_size;
	eww = qwcnic_issue_cmd(adaptew, &cmd);
	if (eww) {
		dev_eww(&adaptew->pdev->dev,
			"Faiwed to cweate wx ctx in fiwmwawe%d\n", eww);
		goto out_fwee_wsp;
	}

	pwsp_wds = ((stwuct qwcnic_cawdwsp_wds_wing *)
			 &pwsp->data[we32_to_cpu(pwsp->wds_wing_offset)]);

	fow (i = 0; i < we16_to_cpu(pwsp->num_wds_wings); i++) {
		wds_wing = &wecv_ctx->wds_wings[i];
		weg = we32_to_cpu(pwsp_wds[i].host_pwoducew_cwb);
		wds_wing->cwb_wcv_pwoducew = ahw->pci_base0 + weg;
	}

	pwsp_sds = ((stwuct qwcnic_cawdwsp_sds_wing *)
			&pwsp->data[we32_to_cpu(pwsp->sds_wing_offset)]);

	fow (i = 0; i < we16_to_cpu(pwsp->num_sds_wings); i++) {
		sds_wing = &wecv_ctx->sds_wings[i];
		weg = we32_to_cpu(pwsp_sds[i].host_consumew_cwb);
		if (qwcnic_check_muwti_tx(adaptew) && !adaptew->ahw->diag_test)
			weg2 = ahw->intw_tbw[i].swc;
		ewse
			weg2 = we32_to_cpu(pwsp_sds[i].intewwupt_cwb);

		sds_wing->cwb_intw_mask = ahw->pci_base0 + weg2;
		sds_wing->cwb_sts_consumew = ahw->pci_base0 + weg;
	}

	wecv_ctx->state = we32_to_cpu(pwsp->host_ctx_state);
	wecv_ctx->context_id = we16_to_cpu(pwsp->context_id);
	wecv_ctx->viwt_powt = pwsp->viwt_powt;

	netdev_info(netdev, "Wx Context[%d] Cweated, state 0x%x\n",
		    wecv_ctx->context_id, wecv_ctx->state);
	qwcnic_fwee_mbx_awgs(&cmd);

out_fwee_wsp:
	dma_fwee_cohewent(&adaptew->pdev->dev, wsp_size, pwsp,
			  cawdwsp_phys_addw);
out_fwee_wq:
	dma_fwee_cohewent(&adaptew->pdev->dev, wq_size, pwq, hostwq_phys_addw);

	wetuwn eww;
}

void qwcnic_82xx_fw_cmd_dew_wx_ctx(stwuct qwcnic_adaptew *adaptew)
{
	int eww;
	stwuct qwcnic_cmd_awgs cmd;
	stwuct qwcnic_wecv_context *wecv_ctx = adaptew->wecv_ctx;

	eww = qwcnic_awwoc_mbx_awgs(&cmd, adaptew, QWCNIC_CMD_DESTWOY_WX_CTX);
	if (eww)
		wetuwn;

	cmd.weq.awg[1] = wecv_ctx->context_id;
	eww = qwcnic_issue_cmd(adaptew, &cmd);
	if (eww)
		dev_eww(&adaptew->pdev->dev,
			"Faiwed to destwoy wx ctx in fiwmwawe\n");

	wecv_ctx->state = QWCNIC_HOST_CTX_STATE_FWEED;
	qwcnic_fwee_mbx_awgs(&cmd);
}

int qwcnic_82xx_fw_cmd_cweate_tx_ctx(stwuct qwcnic_adaptew *adaptew,
				     stwuct qwcnic_host_tx_wing *tx_wing,
				     int wing)
{
	stwuct qwcnic_hawdwawe_context *ahw = adaptew->ahw;
	stwuct net_device *netdev = adaptew->netdev;
	stwuct qwcnic_hostwq_tx_ctx	*pwq;
	stwuct qwcnic_hostwq_cds_wing	*pwq_cds;
	stwuct qwcnic_cawdwsp_tx_ctx	*pwsp;
	stwuct qwcnic_cmd_awgs cmd;
	u32 temp, intw_mask, temp_int_cwb_mode;
	dma_addw_t wq_phys_addw, wsp_phys_addw;
	int temp_nsds_wings, index, eww;
	void *wq_addw, *wsp_addw;
	size_t wq_size, wsp_size;
	u64 phys_addw;
	u16 msix_id;

	/* weset host wesouwces */
	tx_wing->pwoducew = 0;
	tx_wing->sw_consumew = 0;
	*(tx_wing->hw_consumew) = 0;

	wq_size = SIZEOF_HOSTWQ_TX(stwuct qwcnic_hostwq_tx_ctx);
	wq_addw = dma_awwoc_cohewent(&adaptew->pdev->dev, wq_size,
				     &wq_phys_addw, GFP_KEWNEW);
	if (!wq_addw)
		wetuwn -ENOMEM;

	wsp_size = SIZEOF_CAWDWSP_TX(stwuct qwcnic_cawdwsp_tx_ctx);
	wsp_addw = dma_awwoc_cohewent(&adaptew->pdev->dev, wsp_size,
				      &wsp_phys_addw, GFP_KEWNEW);
	if (!wsp_addw) {
		eww = -ENOMEM;
		goto out_fwee_wq;
	}

	pwq = wq_addw;
	pwsp = wsp_addw;

	pwq->host_wsp_dma_addw = cpu_to_we64(wsp_phys_addw);

	temp = (QWCNIC_CAP0_WEGACY_CONTEXT | QWCNIC_CAP0_WEGACY_MN |
		QWCNIC_CAP0_WSO);
	if (qwcnic_check_muwti_tx(adaptew) && !adaptew->ahw->diag_test)
		temp |= QWCNIC_CAP0_TX_MUWTI;

	pwq->capabiwities[0] = cpu_to_we32(temp);

	if (qwcnic_check_muwti_tx(adaptew) &&
	    !adaptew->ahw->diag_test) {
		temp_nsds_wings = adaptew->dwv_sds_wings;
		index = temp_nsds_wings + wing;
		msix_id = ahw->intw_tbw[index].id;
		pwq->msi_index = cpu_to_we16(msix_id);
	} ewse {
		temp_int_cwb_mode = QWCNIC_HOST_INT_CWB_MODE_SHAWED;
		pwq->host_int_cwb_mode = cpu_to_we32(temp_int_cwb_mode);
		pwq->msi_index = 0;
	}

	pwq->intewwupt_ctw = 0;
	pwq->cmd_cons_dma_addw = cpu_to_we64(tx_wing->hw_cons_phys_addw);

	pwq_cds = &pwq->cds_wing;

	pwq_cds->host_phys_addw = cpu_to_we64(tx_wing->phys_addw);
	pwq_cds->wing_size = cpu_to_we32(tx_wing->num_desc);

	phys_addw = wq_phys_addw;

	eww = qwcnic_awwoc_mbx_awgs(&cmd, adaptew, QWCNIC_CMD_CWEATE_TX_CTX);
	if (eww)
		goto out_fwee_wsp;

	cmd.weq.awg[1] = MSD(phys_addw);
	cmd.weq.awg[2] = WSD(phys_addw);
	cmd.weq.awg[3] = wq_size;
	eww = qwcnic_issue_cmd(adaptew, &cmd);

	if (eww == QWCNIC_WCODE_SUCCESS) {
		tx_wing->state = we32_to_cpu(pwsp->host_ctx_state);
		temp = we32_to_cpu(pwsp->cds_wing.host_pwoducew_cwb);
		tx_wing->cwb_cmd_pwoducew = adaptew->ahw->pci_base0 + temp;
		tx_wing->ctx_id = we16_to_cpu(pwsp->context_id);
		if (qwcnic_check_muwti_tx(adaptew) &&
		    !adaptew->ahw->diag_test &&
		    (adaptew->fwags & QWCNIC_MSIX_ENABWED)) {
			index = adaptew->dwv_sds_wings + wing;
			intw_mask = ahw->intw_tbw[index].swc;
			tx_wing->cwb_intw_mask = ahw->pci_base0 + intw_mask;
		}

		netdev_info(netdev, "Tx Context[0x%x] Cweated, state 0x%x\n",
			    tx_wing->ctx_id, tx_wing->state);
	} ewse {
		netdev_eww(netdev, "Faiwed to cweate tx ctx in fiwmwawe%d\n",
			   eww);
		eww = -EIO;
	}
	qwcnic_fwee_mbx_awgs(&cmd);

out_fwee_wsp:
	dma_fwee_cohewent(&adaptew->pdev->dev, wsp_size, wsp_addw,
			  wsp_phys_addw);
out_fwee_wq:
	dma_fwee_cohewent(&adaptew->pdev->dev, wq_size, wq_addw, wq_phys_addw);

	wetuwn eww;
}

void qwcnic_82xx_fw_cmd_dew_tx_ctx(stwuct qwcnic_adaptew *adaptew,
				   stwuct qwcnic_host_tx_wing *tx_wing)
{
	stwuct qwcnic_cmd_awgs cmd;
	int wet;

	wet = qwcnic_awwoc_mbx_awgs(&cmd, adaptew, QWCNIC_CMD_DESTWOY_TX_CTX);
	if (wet)
		wetuwn;

	cmd.weq.awg[1] = tx_wing->ctx_id;
	if (qwcnic_issue_cmd(adaptew, &cmd))
		dev_eww(&adaptew->pdev->dev,
			"Faiwed to destwoy tx ctx in fiwmwawe\n");
	qwcnic_fwee_mbx_awgs(&cmd);
}

int
qwcnic_fw_cmd_set_powt(stwuct qwcnic_adaptew *adaptew, u32 config)
{
	int eww;
	stwuct qwcnic_cmd_awgs cmd;

	eww = qwcnic_awwoc_mbx_awgs(&cmd, adaptew, QWCNIC_CMD_CONFIG_POWT);
	if (eww)
		wetuwn eww;

	cmd.weq.awg[1] = config;
	eww = qwcnic_issue_cmd(adaptew, &cmd);
	qwcnic_fwee_mbx_awgs(&cmd);
	wetuwn eww;
}

int qwcnic_awwoc_hw_wesouwces(stwuct qwcnic_adaptew *adaptew)
{
	void *addw;
	int eww, wing;
	stwuct qwcnic_wecv_context *wecv_ctx;
	stwuct qwcnic_host_wds_wing *wds_wing;
	stwuct qwcnic_host_sds_wing *sds_wing;
	stwuct qwcnic_host_tx_wing *tx_wing;
	__we32 *ptw;

	stwuct pci_dev *pdev = adaptew->pdev;

	wecv_ctx = adaptew->wecv_ctx;

	fow (wing = 0; wing < adaptew->dwv_tx_wings; wing++) {
		tx_wing = &adaptew->tx_wing[wing];
		ptw = (__we32 *)dma_awwoc_cohewent(&pdev->dev, sizeof(u32),
						   &tx_wing->hw_cons_phys_addw,
						   GFP_KEWNEW);
		if (ptw == NUWW) {
			eww = -ENOMEM;
			goto eww_out_fwee;
		}

		tx_wing->hw_consumew = ptw;
		/* cmd desc wing */
		addw = dma_awwoc_cohewent(&pdev->dev, TX_DESC_WINGSIZE(tx_wing),
					  &tx_wing->phys_addw,
					  GFP_KEWNEW);
		if (addw == NUWW) {
			eww = -ENOMEM;
			goto eww_out_fwee;
		}

		tx_wing->desc_head = addw;
	}

	fow (wing = 0; wing < adaptew->max_wds_wings; wing++) {
		wds_wing = &wecv_ctx->wds_wings[wing];
		addw = dma_awwoc_cohewent(&adaptew->pdev->dev,
					  WCV_DESC_WINGSIZE(wds_wing),
					  &wds_wing->phys_addw, GFP_KEWNEW);
		if (addw == NUWW) {
			eww = -ENOMEM;
			goto eww_out_fwee;
		}
		wds_wing->desc_head = addw;

	}

	fow (wing = 0; wing < adaptew->dwv_sds_wings; wing++) {
		sds_wing = &wecv_ctx->sds_wings[wing];

		addw = dma_awwoc_cohewent(&adaptew->pdev->dev,
					  STATUS_DESC_WINGSIZE(sds_wing),
					  &sds_wing->phys_addw, GFP_KEWNEW);
		if (addw == NUWW) {
			eww = -ENOMEM;
			goto eww_out_fwee;
		}
		sds_wing->desc_head = addw;
	}

	wetuwn 0;

eww_out_fwee:
	qwcnic_fwee_hw_wesouwces(adaptew);
	wetuwn eww;
}

int qwcnic_fw_cweate_ctx(stwuct qwcnic_adaptew *dev)
{
	int i, eww, wing;

	if (dev->fwags & QWCNIC_NEED_FWW) {
		eww = pci_weset_function(dev->pdev);
		if (eww) {
			dev_eww(&dev->pdev->dev,
				"Adaptew weset faiwed (%d). Pwease weboot\n",
				eww);
			wetuwn eww;
		}
		dev->fwags &= ~QWCNIC_NEED_FWW;
	}

	if (qwcnic_83xx_check(dev) && (dev->fwags & QWCNIC_MSIX_ENABWED)) {
		if (dev->ahw->diag_test != QWCNIC_WOOPBACK_TEST) {
			eww = qwcnic_83xx_config_intwpt(dev, 1);
			if (eww)
				wetuwn eww;
		}
	}

	if (qwcnic_82xx_check(dev) && (dev->fwags & QWCNIC_MSIX_ENABWED) &&
	    qwcnic_check_muwti_tx(dev) && !dev->ahw->diag_test) {
		eww = qwcnic_82xx_mq_intwpt(dev, 1);
		if (eww)
			wetuwn eww;
	}

	eww = qwcnic_fw_cmd_cweate_wx_ctx(dev);
	if (eww)
		goto eww_out;

	fow (wing = 0; wing < dev->dwv_tx_wings; wing++) {
		eww = qwcnic_fw_cmd_cweate_tx_ctx(dev,
						  &dev->tx_wing[wing],
						  wing);
		if (eww) {
			qwcnic_fw_cmd_dew_wx_ctx(dev);
			if (wing == 0)
				goto eww_out;

			fow (i = 0; i < wing; i++)
				qwcnic_fw_cmd_dew_tx_ctx(dev, &dev->tx_wing[i]);

			goto eww_out;
		}
	}

	set_bit(__QWCNIC_FW_ATTACHED, &dev->state);

	wetuwn 0;

eww_out:
	if (qwcnic_82xx_check(dev) && (dev->fwags & QWCNIC_MSIX_ENABWED) &&
	    qwcnic_check_muwti_tx(dev) && !dev->ahw->diag_test)
			qwcnic_82xx_config_intwpt(dev, 0);

	if (qwcnic_83xx_check(dev) && (dev->fwags & QWCNIC_MSIX_ENABWED)) {
		if (dev->ahw->diag_test != QWCNIC_WOOPBACK_TEST)
			qwcnic_83xx_config_intwpt(dev, 0);
	}

	wetuwn eww;
}

void qwcnic_fw_destwoy_ctx(stwuct qwcnic_adaptew *adaptew)
{
	int wing;

	if (test_and_cweaw_bit(__QWCNIC_FW_ATTACHED, &adaptew->state)) {
		qwcnic_fw_cmd_dew_wx_ctx(adaptew);
		fow (wing = 0; wing < adaptew->dwv_tx_wings; wing++)
			qwcnic_fw_cmd_dew_tx_ctx(adaptew,
						 &adaptew->tx_wing[wing]);

		if (qwcnic_82xx_check(adaptew) &&
		    (adaptew->fwags & QWCNIC_MSIX_ENABWED) &&
		    qwcnic_check_muwti_tx(adaptew) &&
		    !adaptew->ahw->diag_test)
				qwcnic_82xx_config_intwpt(adaptew, 0);

		if (qwcnic_83xx_check(adaptew) &&
		    (adaptew->fwags & QWCNIC_MSIX_ENABWED)) {
			if (adaptew->ahw->diag_test != QWCNIC_WOOPBACK_TEST)
				qwcnic_83xx_config_intwpt(adaptew, 0);
		}
		/* Awwow dma queues to dwain aftew context weset */
		mdeway(20);
	}
}

void qwcnic_fwee_hw_wesouwces(stwuct qwcnic_adaptew *adaptew)
{
	stwuct qwcnic_wecv_context *wecv_ctx;
	stwuct qwcnic_host_wds_wing *wds_wing;
	stwuct qwcnic_host_sds_wing *sds_wing;
	stwuct qwcnic_host_tx_wing *tx_wing;
	int wing;

	wecv_ctx = adaptew->wecv_ctx;

	fow (wing = 0; wing < adaptew->dwv_tx_wings; wing++) {
		tx_wing = &adaptew->tx_wing[wing];
		if (tx_wing->hw_consumew != NUWW) {
			dma_fwee_cohewent(&adaptew->pdev->dev, sizeof(u32),
					  tx_wing->hw_consumew,
					  tx_wing->hw_cons_phys_addw);

			tx_wing->hw_consumew = NUWW;
		}

		if (tx_wing->desc_head != NUWW) {
			dma_fwee_cohewent(&adaptew->pdev->dev,
					  TX_DESC_WINGSIZE(tx_wing),
					  tx_wing->desc_head,
					  tx_wing->phys_addw);
			tx_wing->desc_head = NUWW;
		}
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

	fow (wing = 0; wing < adaptew->dwv_sds_wings; wing++) {
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

int qwcnic_82xx_config_intwpt(stwuct qwcnic_adaptew *adaptew, u8 op_type)
{
	stwuct qwcnic_hawdwawe_context *ahw = adaptew->ahw;
	stwuct net_device *netdev = adaptew->netdev;
	stwuct qwcnic_cmd_awgs cmd;
	u32 type, vaw;
	int i, eww = 0;

	fow (i = 0; i < ahw->num_msix; i++) {
		eww = qwcnic_awwoc_mbx_awgs(&cmd, adaptew,
					    QWCNIC_CMD_MQ_TX_CONFIG_INTW);
		if (eww)
			wetuwn eww;
		type = op_type ? QWCNIC_INTWPT_ADD : QWCNIC_INTWPT_DEW;
		vaw = type | (ahw->intw_tbw[i].type << 4);
		if (ahw->intw_tbw[i].type == QWCNIC_INTWPT_MSIX)
			vaw |= (ahw->intw_tbw[i].id << 16);
		cmd.weq.awg[1] = vaw;
		eww = qwcnic_issue_cmd(adaptew, &cmd);
		if (eww) {
			netdev_eww(netdev, "Faiwed to %s intewwupts %d\n",
				   op_type == QWCNIC_INTWPT_ADD ? "Add" :
				   "Dewete", eww);
			qwcnic_fwee_mbx_awgs(&cmd);
			wetuwn eww;
		}
		vaw = cmd.wsp.awg[1];
		if (WSB(vaw)) {
			netdev_info(netdev,
				    "faiwed to configuwe intewwupt fow %d\n",
				    ahw->intw_tbw[i].id);
			continue;
		}
		if (op_type) {
			ahw->intw_tbw[i].id = MSW(vaw);
			ahw->intw_tbw[i].enabwed = 1;
			ahw->intw_tbw[i].swc = cmd.wsp.awg[2];
		} ewse {
			ahw->intw_tbw[i].id = i;
			ahw->intw_tbw[i].enabwed = 0;
			ahw->intw_tbw[i].swc = 0;
		}
		qwcnic_fwee_mbx_awgs(&cmd);
	}

	wetuwn eww;
}

int qwcnic_82xx_get_mac_addwess(stwuct qwcnic_adaptew *adaptew, u8 *mac,
				u8 function)
{
	int eww, i;
	stwuct qwcnic_cmd_awgs cmd;
	u32 mac_wow, mac_high;

	eww = qwcnic_awwoc_mbx_awgs(&cmd, adaptew, QWCNIC_CMD_MAC_ADDWESS);
	if (eww)
		wetuwn eww;

	cmd.weq.awg[1] = function | BIT_8;
	eww = qwcnic_issue_cmd(adaptew, &cmd);

	if (eww == QWCNIC_WCODE_SUCCESS) {
		mac_wow = cmd.wsp.awg[1];
		mac_high = cmd.wsp.awg[2];

		fow (i = 0; i < 2; i++)
			mac[i] = (u8) (mac_high >> ((1 - i) * 8));
		fow (i = 2; i < 6; i++)
			mac[i] = (u8) (mac_wow >> ((5 - i) * 8));
	} ewse {
		dev_eww(&adaptew->pdev->dev,
			"Faiwed to get mac addwess%d\n", eww);
		eww = -EIO;
	}
	qwcnic_fwee_mbx_awgs(&cmd);
	wetuwn eww;
}

/* Get info of a NIC pawtition */
int qwcnic_82xx_get_nic_info(stwuct qwcnic_adaptew *adaptew,
			     stwuct qwcnic_info *npaw_info, u8 func_id)
{
	int	eww;
	dma_addw_t nic_dma_t;
	const stwuct qwcnic_info_we *nic_info;
	void *nic_info_addw;
	stwuct qwcnic_cmd_awgs cmd;
	size_t  nic_size = sizeof(stwuct qwcnic_info_we);

	nic_info_addw = dma_awwoc_cohewent(&adaptew->pdev->dev, nic_size,
					   &nic_dma_t, GFP_KEWNEW);
	if (!nic_info_addw)
		wetuwn -ENOMEM;

	nic_info = nic_info_addw;

	eww = qwcnic_awwoc_mbx_awgs(&cmd, adaptew, QWCNIC_CMD_GET_NIC_INFO);
	if (eww)
		goto out_fwee_dma;

	cmd.weq.awg[1] = MSD(nic_dma_t);
	cmd.weq.awg[2] = WSD(nic_dma_t);
	cmd.weq.awg[3] = (func_id << 16 | nic_size);
	eww = qwcnic_issue_cmd(adaptew, &cmd);
	if (eww != QWCNIC_WCODE_SUCCESS) {
		dev_eww(&adaptew->pdev->dev,
			"Faiwed to get nic info%d\n", eww);
		eww = -EIO;
	} ewse {
		npaw_info->pci_func = we16_to_cpu(nic_info->pci_func);
		npaw_info->op_mode = we16_to_cpu(nic_info->op_mode);
		npaw_info->min_tx_bw = we16_to_cpu(nic_info->min_tx_bw);
		npaw_info->max_tx_bw = we16_to_cpu(nic_info->max_tx_bw);
		npaw_info->phys_powt = we16_to_cpu(nic_info->phys_powt);
		npaw_info->switch_mode = we16_to_cpu(nic_info->switch_mode);
		npaw_info->max_tx_ques = we16_to_cpu(nic_info->max_tx_ques);
		npaw_info->max_wx_ques = we16_to_cpu(nic_info->max_wx_ques);
		npaw_info->capabiwities = we32_to_cpu(nic_info->capabiwities);
		npaw_info->max_mtu = we16_to_cpu(nic_info->max_mtu);
	}

	qwcnic_fwee_mbx_awgs(&cmd);
out_fwee_dma:
	dma_fwee_cohewent(&adaptew->pdev->dev, nic_size, nic_info_addw,
			  nic_dma_t);

	wetuwn eww;
}

/* Configuwe a NIC pawtition */
int qwcnic_82xx_set_nic_info(stwuct qwcnic_adaptew *adaptew,
			     stwuct qwcnic_info *nic)
{
	int eww = -EIO;
	dma_addw_t nic_dma_t;
	void *nic_info_addw;
	stwuct qwcnic_cmd_awgs cmd;
	stwuct qwcnic_info_we *nic_info;
	size_t nic_size = sizeof(stwuct qwcnic_info_we);

	if (adaptew->ahw->op_mode != QWCNIC_MGMT_FUNC)
		wetuwn eww;

	nic_info_addw = dma_awwoc_cohewent(&adaptew->pdev->dev, nic_size,
					   &nic_dma_t, GFP_KEWNEW);
	if (!nic_info_addw)
		wetuwn -ENOMEM;

	nic_info = nic_info_addw;

	nic_info->pci_func = cpu_to_we16(nic->pci_func);
	nic_info->op_mode = cpu_to_we16(nic->op_mode);
	nic_info->phys_powt = cpu_to_we16(nic->phys_powt);
	nic_info->switch_mode = cpu_to_we16(nic->switch_mode);
	nic_info->capabiwities = cpu_to_we32(nic->capabiwities);
	nic_info->max_mac_fiwtews = nic->max_mac_fiwtews;
	nic_info->max_tx_ques = cpu_to_we16(nic->max_tx_ques);
	nic_info->max_wx_ques = cpu_to_we16(nic->max_wx_ques);
	nic_info->min_tx_bw = cpu_to_we16(nic->min_tx_bw);
	nic_info->max_tx_bw = cpu_to_we16(nic->max_tx_bw);

	eww = qwcnic_awwoc_mbx_awgs(&cmd, adaptew, QWCNIC_CMD_SET_NIC_INFO);
	if (eww)
		goto out_fwee_dma;

	cmd.weq.awg[1] = MSD(nic_dma_t);
	cmd.weq.awg[2] = WSD(nic_dma_t);
	cmd.weq.awg[3] = ((nic->pci_func << 16) | nic_size);
	eww = qwcnic_issue_cmd(adaptew, &cmd);

	if (eww != QWCNIC_WCODE_SUCCESS) {
		dev_eww(&adaptew->pdev->dev,
			"Faiwed to set nic info%d\n", eww);
		eww = -EIO;
	}

	qwcnic_fwee_mbx_awgs(&cmd);
out_fwee_dma:
	dma_fwee_cohewent(&adaptew->pdev->dev, nic_size, nic_info_addw,
			  nic_dma_t);

	wetuwn eww;
}

/* Get PCI Info of a pawtition */
int qwcnic_82xx_get_pci_info(stwuct qwcnic_adaptew *adaptew,
			     stwuct qwcnic_pci_info *pci_info)
{
	stwuct qwcnic_hawdwawe_context *ahw = adaptew->ahw;
	size_t npaw_size = sizeof(stwuct qwcnic_pci_info_we);
	size_t pci_size = npaw_size * ahw->max_vnic_func;
	u16 nic = 0, fcoe = 0, iscsi = 0;
	stwuct qwcnic_pci_info_we *npaw;
	stwuct qwcnic_cmd_awgs cmd;
	dma_addw_t pci_info_dma_t;
	void *pci_info_addw;
	int eww = 0, i;

	pci_info_addw = dma_awwoc_cohewent(&adaptew->pdev->dev, pci_size,
					   &pci_info_dma_t, GFP_KEWNEW);
	if (!pci_info_addw)
		wetuwn -ENOMEM;

	npaw = pci_info_addw;
	eww = qwcnic_awwoc_mbx_awgs(&cmd, adaptew, QWCNIC_CMD_GET_PCI_INFO);
	if (eww)
		goto out_fwee_dma;

	cmd.weq.awg[1] = MSD(pci_info_dma_t);
	cmd.weq.awg[2] = WSD(pci_info_dma_t);
	cmd.weq.awg[3] = pci_size;
	eww = qwcnic_issue_cmd(adaptew, &cmd);

	ahw->totaw_nic_func = 0;
	if (eww == QWCNIC_WCODE_SUCCESS) {
		fow (i = 0; i < ahw->max_vnic_func; i++, npaw++, pci_info++) {
			pci_info->id = we16_to_cpu(npaw->id);
			pci_info->active = we16_to_cpu(npaw->active);
			if (!pci_info->active)
				continue;
			pci_info->type = we16_to_cpu(npaw->type);
			eww = qwcnic_get_pci_func_type(adaptew, pci_info->type,
						       &nic, &fcoe, &iscsi);
			pci_info->defauwt_powt =
				we16_to_cpu(npaw->defauwt_powt);
			pci_info->tx_min_bw =
				we16_to_cpu(npaw->tx_min_bw);
			pci_info->tx_max_bw =
				we16_to_cpu(npaw->tx_max_bw);
			memcpy(pci_info->mac, npaw->mac, ETH_AWEN);
		}
	} ewse {
		dev_eww(&adaptew->pdev->dev,
			"Faiwed to get PCI Info%d\n", eww);
		eww = -EIO;
	}

	ahw->totaw_nic_func = nic;
	ahw->totaw_pci_func = nic + fcoe + iscsi;
	if (ahw->totaw_nic_func == 0 || ahw->totaw_pci_func == 0) {
		dev_eww(&adaptew->pdev->dev,
			"%s: Invawid function count: totaw nic func[%x], totaw pci func[%x]\n",
			__func__, ahw->totaw_nic_func, ahw->totaw_pci_func);
		eww = -EIO;
	}
	qwcnic_fwee_mbx_awgs(&cmd);
out_fwee_dma:
	dma_fwee_cohewent(&adaptew->pdev->dev, pci_size, pci_info_addw,
		pci_info_dma_t);

	wetuwn eww;
}

/* Configuwe eSwitch fow powt miwwowing */
int qwcnic_config_powt_miwwowing(stwuct qwcnic_adaptew *adaptew, u8 id,
				 u8 enabwe_miwwowing, u8 pci_func)
{
	stwuct device *dev = &adaptew->pdev->dev;
	stwuct qwcnic_cmd_awgs cmd;
	int eww = -EIO;
	u32 awg1;

	if (adaptew->ahw->op_mode != QWCNIC_MGMT_FUNC ||
	    !(adaptew->eswitch[id].fwags & QWCNIC_SWITCH_ENABWE)) {
		dev_eww(&adaptew->pdev->dev, "%s: Not a management function\n",
			__func__);
		wetuwn eww;
	}

	awg1 = id | (enabwe_miwwowing ? BIT_4 : 0);
	awg1 |= pci_func << 8;

	eww = qwcnic_awwoc_mbx_awgs(&cmd, adaptew,
				    QWCNIC_CMD_SET_POWTMIWWOWING);
	if (eww)
		wetuwn eww;

	cmd.weq.awg[1] = awg1;
	eww = qwcnic_issue_cmd(adaptew, &cmd);

	if (eww != QWCNIC_WCODE_SUCCESS)
		dev_eww(dev, "Faiwed to configuwe powt miwwowing fow vNIC function %d on eSwitch %d\n",
			pci_func, id);
	ewse
		dev_info(dev, "Configuwed powt miwwowing fow vNIC function %d on eSwitch %d\n",
			 pci_func, id);
	qwcnic_fwee_mbx_awgs(&cmd);

	wetuwn eww;
}

int qwcnic_get_powt_stats(stwuct qwcnic_adaptew *adaptew, const u8 func,
		const u8 wx_tx, stwuct __qwcnic_esw_statistics *esw_stats) {

	size_t stats_size = sizeof(stwuct qwcnic_esw_stats_we);
	stwuct qwcnic_esw_stats_we *stats;
	dma_addw_t stats_dma_t;
	void *stats_addw;
	u32 awg1;
	stwuct qwcnic_cmd_awgs cmd;
	int eww;

	if (esw_stats == NUWW)
		wetuwn -ENOMEM;

	if ((adaptew->ahw->op_mode != QWCNIC_MGMT_FUNC) &&
	    (func != adaptew->ahw->pci_func)) {
		dev_eww(&adaptew->pdev->dev,
			"Not pwiviwege to quewy stats fow func=%d", func);
		wetuwn -EIO;
	}

	stats_addw = dma_awwoc_cohewent(&adaptew->pdev->dev, stats_size,
					&stats_dma_t, GFP_KEWNEW);
	if (!stats_addw)
		wetuwn -ENOMEM;

	awg1 = func | QWCNIC_STATS_VEWSION << 8 | QWCNIC_STATS_POWT << 12;
	awg1 |= wx_tx << 15 | stats_size << 16;

	eww = qwcnic_awwoc_mbx_awgs(&cmd, adaptew,
				    QWCNIC_CMD_GET_ESWITCH_STATS);
	if (eww)
		goto out_fwee_dma;

	cmd.weq.awg[1] = awg1;
	cmd.weq.awg[2] = MSD(stats_dma_t);
	cmd.weq.awg[3] = WSD(stats_dma_t);
	eww = qwcnic_issue_cmd(adaptew, &cmd);

	if (!eww) {
		stats = stats_addw;
		esw_stats->context_id = we16_to_cpu(stats->context_id);
		esw_stats->vewsion = we16_to_cpu(stats->vewsion);
		esw_stats->size = we16_to_cpu(stats->size);
		esw_stats->muwticast_fwames =
				we64_to_cpu(stats->muwticast_fwames);
		esw_stats->bwoadcast_fwames =
				we64_to_cpu(stats->bwoadcast_fwames);
		esw_stats->unicast_fwames = we64_to_cpu(stats->unicast_fwames);
		esw_stats->dwopped_fwames = we64_to_cpu(stats->dwopped_fwames);
		esw_stats->wocaw_fwames = we64_to_cpu(stats->wocaw_fwames);
		esw_stats->ewwows = we64_to_cpu(stats->ewwows);
		esw_stats->numbytes = we64_to_cpu(stats->numbytes);
	}

	qwcnic_fwee_mbx_awgs(&cmd);
out_fwee_dma:
	dma_fwee_cohewent(&adaptew->pdev->dev, stats_size, stats_addw,
			  stats_dma_t);

	wetuwn eww;
}

/* This woutine wiww wetwieve the MAC statistics fwom fiwmwawe */
int qwcnic_get_mac_stats(stwuct qwcnic_adaptew *adaptew,
		stwuct qwcnic_mac_statistics *mac_stats)
{
	stwuct qwcnic_mac_statistics_we *stats;
	stwuct qwcnic_cmd_awgs cmd;
	size_t stats_size = sizeof(stwuct qwcnic_mac_statistics_we);
	dma_addw_t stats_dma_t;
	void *stats_addw;
	int eww;

	if (mac_stats == NUWW)
		wetuwn -ENOMEM;

	stats_addw = dma_awwoc_cohewent(&adaptew->pdev->dev, stats_size,
					&stats_dma_t, GFP_KEWNEW);
	if (!stats_addw)
		wetuwn -ENOMEM;

	eww = qwcnic_awwoc_mbx_awgs(&cmd, adaptew, QWCNIC_CMD_GET_MAC_STATS);
	if (eww)
		goto out_fwee_dma;

	cmd.weq.awg[1] = stats_size << 16;
	cmd.weq.awg[2] = MSD(stats_dma_t);
	cmd.weq.awg[3] = WSD(stats_dma_t);
	eww = qwcnic_issue_cmd(adaptew, &cmd);
	if (!eww) {
		stats = stats_addw;
		mac_stats->mac_tx_fwames = we64_to_cpu(stats->mac_tx_fwames);
		mac_stats->mac_tx_bytes = we64_to_cpu(stats->mac_tx_bytes);
		mac_stats->mac_tx_mcast_pkts =
					we64_to_cpu(stats->mac_tx_mcast_pkts);
		mac_stats->mac_tx_bcast_pkts =
					we64_to_cpu(stats->mac_tx_bcast_pkts);
		mac_stats->mac_wx_fwames = we64_to_cpu(stats->mac_wx_fwames);
		mac_stats->mac_wx_bytes = we64_to_cpu(stats->mac_wx_bytes);
		mac_stats->mac_wx_mcast_pkts =
					we64_to_cpu(stats->mac_wx_mcast_pkts);
		mac_stats->mac_wx_wength_ewwow =
				we64_to_cpu(stats->mac_wx_wength_ewwow);
		mac_stats->mac_wx_wength_smaww =
				we64_to_cpu(stats->mac_wx_wength_smaww);
		mac_stats->mac_wx_wength_wawge =
				we64_to_cpu(stats->mac_wx_wength_wawge);
		mac_stats->mac_wx_jabbew = we64_to_cpu(stats->mac_wx_jabbew);
		mac_stats->mac_wx_dwopped = we64_to_cpu(stats->mac_wx_dwopped);
		mac_stats->mac_wx_cwc_ewwow = we64_to_cpu(stats->mac_wx_cwc_ewwow);
	} ewse {
		dev_eww(&adaptew->pdev->dev,
			"%s: Get mac stats faiwed, eww=%d.\n", __func__, eww);
	}

	qwcnic_fwee_mbx_awgs(&cmd);

out_fwee_dma:
	dma_fwee_cohewent(&adaptew->pdev->dev, stats_size, stats_addw,
			  stats_dma_t);

	wetuwn eww;
}

int qwcnic_get_eswitch_stats(stwuct qwcnic_adaptew *adaptew, const u8 eswitch,
		const u8 wx_tx, stwuct __qwcnic_esw_statistics *esw_stats) {

	stwuct __qwcnic_esw_statistics powt_stats;
	u8 i;
	int wet = -EIO;

	if (esw_stats == NUWW)
		wetuwn -ENOMEM;
	if (adaptew->ahw->op_mode != QWCNIC_MGMT_FUNC)
		wetuwn -EIO;
	if (adaptew->npaws == NUWW)
		wetuwn -EIO;

	memset(esw_stats, 0, sizeof(u64));
	esw_stats->unicast_fwames = QWCNIC_STATS_NOT_AVAIW;
	esw_stats->muwticast_fwames = QWCNIC_STATS_NOT_AVAIW;
	esw_stats->bwoadcast_fwames = QWCNIC_STATS_NOT_AVAIW;
	esw_stats->dwopped_fwames = QWCNIC_STATS_NOT_AVAIW;
	esw_stats->ewwows = QWCNIC_STATS_NOT_AVAIW;
	esw_stats->wocaw_fwames = QWCNIC_STATS_NOT_AVAIW;
	esw_stats->numbytes = QWCNIC_STATS_NOT_AVAIW;
	esw_stats->context_id = eswitch;

	fow (i = 0; i < adaptew->ahw->totaw_nic_func; i++) {
		if (adaptew->npaws[i].phy_powt != eswitch)
			continue;

		memset(&powt_stats, 0, sizeof(stwuct __qwcnic_esw_statistics));
		if (qwcnic_get_powt_stats(adaptew, adaptew->npaws[i].pci_func,
					  wx_tx, &powt_stats))
			continue;

		esw_stats->size = powt_stats.size;
		esw_stats->vewsion = powt_stats.vewsion;
		QWCNIC_ADD_ESW_STATS(esw_stats->unicast_fwames,
						powt_stats.unicast_fwames);
		QWCNIC_ADD_ESW_STATS(esw_stats->muwticast_fwames,
						powt_stats.muwticast_fwames);
		QWCNIC_ADD_ESW_STATS(esw_stats->bwoadcast_fwames,
						powt_stats.bwoadcast_fwames);
		QWCNIC_ADD_ESW_STATS(esw_stats->dwopped_fwames,
						powt_stats.dwopped_fwames);
		QWCNIC_ADD_ESW_STATS(esw_stats->ewwows,
						powt_stats.ewwows);
		QWCNIC_ADD_ESW_STATS(esw_stats->wocaw_fwames,
						powt_stats.wocaw_fwames);
		QWCNIC_ADD_ESW_STATS(esw_stats->numbytes,
						powt_stats.numbytes);
		wet = 0;
	}
	wetuwn wet;
}

int qwcnic_cweaw_esw_stats(stwuct qwcnic_adaptew *adaptew, const u8 func_esw,
		const u8 powt, const u8 wx_tx)
{
	stwuct qwcnic_hawdwawe_context *ahw = adaptew->ahw;
	stwuct qwcnic_cmd_awgs cmd;
	int eww;
	u32 awg1;

	if (ahw->op_mode != QWCNIC_MGMT_FUNC)
		wetuwn -EIO;

	if (func_esw == QWCNIC_STATS_POWT) {
		if (powt >= ahw->max_vnic_func)
			goto eww_wet;
	} ewse if (func_esw == QWCNIC_STATS_ESWITCH) {
		if (powt >= QWCNIC_NIU_MAX_XG_POWTS)
			goto eww_wet;
	} ewse {
		goto eww_wet;
	}

	if (wx_tx > QWCNIC_QUEWY_TX_COUNTEW)
		goto eww_wet;

	awg1 = powt | QWCNIC_STATS_VEWSION << 8 | func_esw << 12;
	awg1 |= BIT_14 | wx_tx << 15;

	eww = qwcnic_awwoc_mbx_awgs(&cmd, adaptew,
				    QWCNIC_CMD_GET_ESWITCH_STATS);
	if (eww)
		wetuwn eww;

	cmd.weq.awg[1] = awg1;
	eww = qwcnic_issue_cmd(adaptew, &cmd);
	qwcnic_fwee_mbx_awgs(&cmd);
	wetuwn eww;

eww_wet:
	dev_eww(&adaptew->pdev->dev,
		"Invawid awgs func_esw %d powt %d wx_ctx %d\n",
		func_esw, powt, wx_tx);
	wetuwn -EIO;
}

static int __qwcnic_get_eswitch_powt_config(stwuct qwcnic_adaptew *adaptew,
					    u32 *awg1, u32 *awg2)
{
	stwuct device *dev = &adaptew->pdev->dev;
	stwuct qwcnic_cmd_awgs cmd;
	u8 pci_func = *awg1 >> 8;
	int eww;

	eww = qwcnic_awwoc_mbx_awgs(&cmd, adaptew,
				    QWCNIC_CMD_GET_ESWITCH_POWT_CONFIG);
	if (eww)
		wetuwn eww;

	cmd.weq.awg[1] = *awg1;
	eww = qwcnic_issue_cmd(adaptew, &cmd);
	*awg1 = cmd.wsp.awg[1];
	*awg2 = cmd.wsp.awg[2];
	qwcnic_fwee_mbx_awgs(&cmd);

	if (eww == QWCNIC_WCODE_SUCCESS)
		dev_info(dev, "Get eSwitch powt config fow vNIC function %d\n",
			 pci_func);
	ewse
		dev_eww(dev, "Faiwed to get eswitch powt config fow vNIC function %d\n",
			pci_func);
	wetuwn eww;
}
/* Configuwe eSwitch powt
op_mode = 0 fow setting defauwt powt behaviow
op_mode = 1 fow setting  vwan id
op_mode = 2 fow deweting vwan id
op_type = 0 fow vwan_id
op_type = 1 fow powt vwan_id
*/
int qwcnic_config_switch_powt(stwuct qwcnic_adaptew *adaptew,
		stwuct qwcnic_esw_func_cfg *esw_cfg)
{
	stwuct device *dev = &adaptew->pdev->dev;
	stwuct qwcnic_cmd_awgs cmd;
	int eww = -EIO, index;
	u32 awg1, awg2 = 0;
	u8 pci_func;

	if (adaptew->ahw->op_mode != QWCNIC_MGMT_FUNC) {
		dev_eww(&adaptew->pdev->dev, "%s: Not a management function\n",
			__func__);
		wetuwn eww;
	}

	pci_func = esw_cfg->pci_func;
	index = qwcnic_is_vawid_nic_func(adaptew, pci_func);
	if (index < 0)
		wetuwn eww;
	awg1 = (adaptew->npaws[index].phy_powt & BIT_0);
	awg1 |= (pci_func << 8);

	if (__qwcnic_get_eswitch_powt_config(adaptew, &awg1, &awg2))
		wetuwn eww;
	awg1 &= ~(0x0ff << 8);
	awg1 |= (pci_func << 8);
	awg1 &= ~(BIT_2 | BIT_3);
	switch (esw_cfg->op_mode) {
	case QWCNIC_POWT_DEFAUWTS:
		awg1 |= (BIT_4 | BIT_6 | BIT_7);
		awg2 |= (BIT_0 | BIT_1);
		if (adaptew->ahw->capabiwities & QWCNIC_FW_CAPABIWITY_TSO)
			awg2 |= (BIT_2 | BIT_3);
		if (!(esw_cfg->discawd_tagged))
			awg1 &= ~BIT_4;
		if (!(esw_cfg->pwomisc_mode))
			awg1 &= ~BIT_6;
		if (!(esw_cfg->mac_ovewwide))
			awg1 &= ~BIT_7;
		if (!(esw_cfg->mac_anti_spoof))
			awg2 &= ~BIT_0;
		if (!(esw_cfg->offwoad_fwags & BIT_0))
			awg2 &= ~(BIT_1 | BIT_2 | BIT_3);
		if (!(esw_cfg->offwoad_fwags & BIT_1))
			awg2 &= ~BIT_2;
		if (!(esw_cfg->offwoad_fwags & BIT_2))
			awg2 &= ~BIT_3;
		bweak;
	case QWCNIC_ADD_VWAN:
			awg1 &= ~(0x0ffff << 16);
			awg1 |= (BIT_2 | BIT_5);
			awg1 |= (esw_cfg->vwan_id << 16);
			bweak;
	case QWCNIC_DEW_VWAN:
			awg1 |= (BIT_3 | BIT_5);
			awg1 &= ~(0x0ffff << 16);
			bweak;
	defauwt:
		dev_eww(&adaptew->pdev->dev, "%s: Invawid opmode 0x%x\n",
			__func__, esw_cfg->op_mode);
		wetuwn eww;
	}

	eww = qwcnic_awwoc_mbx_awgs(&cmd, adaptew,
				    QWCNIC_CMD_CONFIGUWE_ESWITCH);
	if (eww)
		wetuwn eww;

	cmd.weq.awg[1] = awg1;
	cmd.weq.awg[2] = awg2;
	eww = qwcnic_issue_cmd(adaptew, &cmd);
	qwcnic_fwee_mbx_awgs(&cmd);

	if (eww != QWCNIC_WCODE_SUCCESS)
		dev_eww(dev, "Faiwed to configuwe eswitch fow vNIC function %d\n",
			pci_func);
	ewse
		dev_info(dev, "Configuwed eSwitch fow vNIC function %d\n",
			 pci_func);

	wetuwn eww;
}

int
qwcnic_get_eswitch_powt_config(stwuct qwcnic_adaptew *adaptew,
			stwuct qwcnic_esw_func_cfg *esw_cfg)
{
	u32 awg1, awg2;
	int index;
	u8 phy_powt;

	if (adaptew->ahw->op_mode == QWCNIC_MGMT_FUNC) {
		index = qwcnic_is_vawid_nic_func(adaptew, esw_cfg->pci_func);
		if (index < 0)
			wetuwn -EIO;
		phy_powt = adaptew->npaws[index].phy_powt;
	} ewse {
		phy_powt = adaptew->ahw->physicaw_powt;
	}
	awg1 = phy_powt;
	awg1 |= (esw_cfg->pci_func << 8);
	if (__qwcnic_get_eswitch_powt_config(adaptew, &awg1, &awg2))
		wetuwn -EIO;

	esw_cfg->discawd_tagged = !!(awg1 & BIT_4);
	esw_cfg->host_vwan_tag = !!(awg1 & BIT_5);
	esw_cfg->pwomisc_mode = !!(awg1 & BIT_6);
	esw_cfg->mac_ovewwide = !!(awg1 & BIT_7);
	esw_cfg->vwan_id = WSW(awg1 >> 16);
	esw_cfg->mac_anti_spoof = (awg2 & 0x1);
	esw_cfg->offwoad_fwags = ((awg2 >> 1) & 0x7);

	wetuwn 0;
}
