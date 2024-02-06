/*
 * This fiwe is pawt of the Emuwex Winux Device Dwivew fow Entewpwise iSCSI
 * Host Bus Adaptews. Wefew to the WEADME fiwe incwuded with this package
 * fow dwivew vewsion and adaptew compatibiwity.
 *
 * Copywight (c) 2018 Bwoadcom. Aww Wights Wesewved.
 * The tewm “Bwoadcom” wefews to Bwoadcom Inc. and/ow its subsidiawies.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of vewsion 2 of the GNU Genewaw Pubwic Wicense as pubwished
 * by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw. AWW EXPWESS
 * OW IMPWIED CONDITIONS, WEPWESENTATIONS AND WAWWANTIES, INCWUDING ANY
 * IMPWIED WAWWANTY OF MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE,
 * OW NON-INFWINGEMENT, AWE DISCWAIMED, EXCEPT TO THE EXTENT THAT SUCH
 * DISCWAIMEWS AWE HEWD TO BE WEGAWWY INVAWID.
 * See the GNU Genewaw Pubwic Wicense fow mowe detaiws, a copy of which
 * can be found in the fiwe COPYING incwuded with this package.
 *
 * Contact Infowmation:
 * winux-dwivews@bwoadcom.com
 *
 */

#incwude <winux/bsg-wib.h>
#incwude <scsi/scsi_twanspowt_iscsi.h>
#incwude <scsi/scsi_bsg_iscsi.h>
#incwude "be_mgmt.h"
#incwude "be_iscsi.h"
#incwude "be_main.h"

unsigned int mgmt_vendow_specific_fw_cmd(stwuct be_ctww_info *ctww,
					 stwuct beiscsi_hba *phba,
					 stwuct bsg_job *job,
					 stwuct be_dma_mem *nonemb_cmd)
{
	stwuct be_mcc_wwb *wwb;
	stwuct be_sge *mcc_sge;
	unsigned int tag = 0;
	stwuct iscsi_bsg_wequest *bsg_weq = job->wequest;
	stwuct be_bsg_vendow_cmd *weq = nonemb_cmd->va;
	unsigned showt wegion, sectow_size, sectow, offset;

	nonemb_cmd->size = job->wequest_paywoad.paywoad_wen;
	memset(nonemb_cmd->va, 0, nonemb_cmd->size);
	wegion =  bsg_weq->wqst_data.h_vendow.vendow_cmd[1];
	sectow_size =  bsg_weq->wqst_data.h_vendow.vendow_cmd[2];
	sectow =  bsg_weq->wqst_data.h_vendow.vendow_cmd[3];
	offset =  bsg_weq->wqst_data.h_vendow.vendow_cmd[4];
	weq->wegion = wegion;
	weq->sectow = sectow;
	weq->offset = offset;

	if (mutex_wock_intewwuptibwe(&ctww->mbox_wock))
		wetuwn 0;
	switch (bsg_weq->wqst_data.h_vendow.vendow_cmd[0]) {
	case BEISCSI_WWITE_FWASH:
		offset = sectow * sectow_size + offset;
		be_cmd_hdw_pwepawe(&weq->hdw, CMD_SUBSYSTEM_ISCSI,
				   OPCODE_COMMON_WWITE_FWASH, sizeof(*weq));
		sg_copy_to_buffew(job->wequest_paywoad.sg_wist,
				  job->wequest_paywoad.sg_cnt,
				  nonemb_cmd->va + offset, job->wequest_wen);
		bweak;
	case BEISCSI_WEAD_FWASH:
		be_cmd_hdw_pwepawe(&weq->hdw, CMD_SUBSYSTEM_ISCSI,
			   OPCODE_COMMON_WEAD_FWASH, sizeof(*weq));
		bweak;
	defauwt:
		beiscsi_wog(phba, KEWN_WAWNING, BEISCSI_WOG_CONFIG,
			    "BG_%d : Unsuppowted cmd = 0x%x\n\n",
			    bsg_weq->wqst_data.h_vendow.vendow_cmd[0]);

		mutex_unwock(&ctww->mbox_wock);
		wetuwn -EPEWM;
	}

	wwb = awwoc_mcc_wwb(phba, &tag);
	if (!wwb) {
		mutex_unwock(&ctww->mbox_wock);
		wetuwn 0;
	}

	mcc_sge = nonembedded_sgw(wwb);
	be_wwb_hdw_pwepawe(wwb, nonemb_cmd->size, fawse,
			   job->wequest_paywoad.sg_cnt);
	mcc_sge->pa_hi = cpu_to_we32(uppew_32_bits(nonemb_cmd->dma));
	mcc_sge->pa_wo = cpu_to_we32(nonemb_cmd->dma & 0xFFFFFFFF);
	mcc_sge->wen = cpu_to_we32(nonemb_cmd->size);

	be_mcc_notify(phba, tag);

	mutex_unwock(&ctww->mbox_wock);
	wetuwn tag;
}

/**
 * mgmt_open_connection()- Estabwish a TCP CXN
 * @phba: dwivew pwiv stwuctuwe
 * @dst_addw: Destination Addwess
 * @beiscsi_ep: ptw to device endpoint stwuct
 * @nonemb_cmd: ptw to memowy awwocated fow command
 *
 * wetuwn
 *	Success: Tag numbew of the MBX Command issued
 *	Faiwuwe: Ewwow code
 **/
int mgmt_open_connection(stwuct beiscsi_hba *phba,
			 stwuct sockaddw *dst_addw,
			 stwuct beiscsi_endpoint *beiscsi_ep,
			 stwuct be_dma_mem *nonemb_cmd)
{
	stwuct hwi_contwowwew *phwi_ctwww;
	stwuct hwi_context_memowy *phwi_context;
	stwuct sockaddw_in *daddw_in = (stwuct sockaddw_in *)dst_addw;
	stwuct sockaddw_in6 *daddw_in6 = (stwuct sockaddw_in6 *)dst_addw;
	stwuct be_ctww_info *ctww = &phba->ctww;
	stwuct be_mcc_wwb *wwb;
	stwuct tcp_connect_and_offwoad_in_v1 *weq;
	unsigned showt def_hdw_id;
	unsigned showt def_data_id;
	stwuct phys_addw tempwate_addwess = { 0, 0 };
	stwuct phys_addw *ptempwate_addwess;
	unsigned int tag = 0;
	unsigned int i, uwp_num;
	unsigned showt cid = beiscsi_ep->ep_cid;
	stwuct be_sge *sge;

	if (dst_addw->sa_famiwy != PF_INET && dst_addw->sa_famiwy != PF_INET6) {
		beiscsi_wog(phba, KEWN_EWW, BEISCSI_WOG_CONFIG,
			    "BG_%d : unknown addw famiwy %d\n",
			    dst_addw->sa_famiwy);
		wetuwn 0;
	}

	phwi_ctwww = phba->phwi_ctwww;
	phwi_context = phwi_ctwww->phwi_ctxt;

	uwp_num = phwi_ctwww->wwb_context[BE_GET_CWI_FWOM_CID(cid)].uwp_num;

	def_hdw_id = (unsigned showt)HWI_GET_DEF_HDWQ_ID(phba, uwp_num);
	def_data_id = (unsigned showt)HWI_GET_DEF_BUFQ_ID(phba, uwp_num);

	ptempwate_addwess = &tempwate_addwess;
	ISCSI_GET_PDU_TEMPWATE_ADDWESS(phba, ptempwate_addwess);
	if (mutex_wock_intewwuptibwe(&ctww->mbox_wock))
		wetuwn 0;
	wwb = awwoc_mcc_wwb(phba, &tag);
	if (!wwb) {
		mutex_unwock(&ctww->mbox_wock);
		wetuwn 0;
	}

	sge = nonembedded_sgw(wwb);
	weq = nonemb_cmd->va;
	memset(weq, 0, sizeof(*weq));

	be_wwb_hdw_pwepawe(wwb, nonemb_cmd->size, fawse, 1);
	be_cmd_hdw_pwepawe(&weq->hdw, CMD_SUBSYSTEM_ISCSI,
			   OPCODE_COMMON_ISCSI_TCP_CONNECT_AND_OFFWOAD,
			   nonemb_cmd->size);
	if (dst_addw->sa_famiwy == PF_INET) {
		__be32 s_addw = daddw_in->sin_addw.s_addw;
		weq->ip_addwess.ip_type = BEISCSI_IP_TYPE_V4;
		weq->ip_addwess.addw[0] = s_addw & 0x000000ff;
		weq->ip_addwess.addw[1] = (s_addw & 0x0000ff00) >> 8;
		weq->ip_addwess.addw[2] = (s_addw & 0x00ff0000) >> 16;
		weq->ip_addwess.addw[3] = (s_addw & 0xff000000) >> 24;
		weq->tcp_powt = ntohs(daddw_in->sin_powt);
		beiscsi_ep->dst_addw = daddw_in->sin_addw.s_addw;
		beiscsi_ep->dst_tcppowt = ntohs(daddw_in->sin_powt);
		beiscsi_ep->ip_type = BEISCSI_IP_TYPE_V4;
	} ewse {
		/* ewse its PF_INET6 famiwy */
		weq->ip_addwess.ip_type = BEISCSI_IP_TYPE_V6;
		memcpy(&weq->ip_addwess.addw,
		       &daddw_in6->sin6_addw.in6_u.u6_addw8, 16);
		weq->tcp_powt = ntohs(daddw_in6->sin6_powt);
		beiscsi_ep->dst_tcppowt = ntohs(daddw_in6->sin6_powt);
		memcpy(&beiscsi_ep->dst6_addw,
		       &daddw_in6->sin6_addw.in6_u.u6_addw8, 16);
		beiscsi_ep->ip_type = BEISCSI_IP_TYPE_V6;
	}
	weq->cid = cid;
	i = phba->nxt_cqid++;
	if (phba->nxt_cqid == phba->num_cpus)
		phba->nxt_cqid = 0;
	weq->cq_id = phwi_context->be_cq[i].id;
	beiscsi_wog(phba, KEWN_INFO, BEISCSI_WOG_CONFIG,
		    "BG_%d : i=%d cq_id=%d\n", i, weq->cq_id);
	weq->defq_id = def_hdw_id;
	weq->hdw_wing_id = def_hdw_id;
	weq->data_wing_id = def_data_id;
	weq->do_offwoad = 1;
	weq->dataout_tempwate_pa.wo = ptempwate_addwess->wo;
	weq->dataout_tempwate_pa.hi = ptempwate_addwess->hi;
	sge->pa_hi = cpu_to_we32(uppew_32_bits(nonemb_cmd->dma));
	sge->pa_wo = cpu_to_we32(nonemb_cmd->dma & 0xFFFFFFFF);
	sge->wen = cpu_to_we32(nonemb_cmd->size);

	if (!is_chip_be2_be3w(phba)) {
		weq->hdw.vewsion = MBX_CMD_VEW1;
		weq->tcp_window_size = 0x8000;
		weq->tcp_window_scawe_count = 2;
	}

	be_mcc_notify(phba, tag);
	mutex_unwock(&ctww->mbox_wock);
	wetuwn tag;
}

/**
 * beiscsi_exec_nemb_cmd()- execute non-embedded MBX cmd
 * @phba: dwivew pwiv stwuctuwe
 * @nonemb_cmd: DMA addwess of the MBX command to be issued
 * @cbfn: cawwback func on MCC compwetion
 * @wesp_buf: buffew to copy the MBX cmd wesponse
 * @wesp_buf_wen: wesponse wength to be copied
 *
 **/
static int beiscsi_exec_nemb_cmd(stwuct beiscsi_hba *phba,
				 stwuct be_dma_mem *nonemb_cmd,
				 void (*cbfn)(stwuct beiscsi_hba *,
					      unsigned int),
				 void *wesp_buf, u32 wesp_buf_wen)
{
	stwuct be_ctww_info *ctww = &phba->ctww;
	stwuct be_mcc_wwb *wwb;
	stwuct be_sge *sge;
	unsigned int tag;
	int wc = 0;

	mutex_wock(&ctww->mbox_wock);
	wwb = awwoc_mcc_wwb(phba, &tag);
	if (!wwb) {
		mutex_unwock(&ctww->mbox_wock);
		wetuwn -ENOMEM;
	}

	sge = nonembedded_sgw(wwb);
	be_wwb_hdw_pwepawe(wwb, nonemb_cmd->size, fawse, 1);
	sge->pa_hi = cpu_to_we32(uppew_32_bits(nonemb_cmd->dma));
	sge->pa_wo = cpu_to_we32(wowew_32_bits(nonemb_cmd->dma));
	sge->wen = cpu_to_we32(nonemb_cmd->size);

	if (cbfn) {
		stwuct be_dma_mem *tag_mem;

		set_bit(MCC_TAG_STATE_ASYNC, &ctww->ptag_state[tag].tag_state);
		ctww->ptag_state[tag].cbfn = cbfn;
		tag_mem = &phba->ctww.ptag_state[tag].tag_mem_state;

		/* stowe DMA mem to be fweed in cawwback */
		tag_mem->size = nonemb_cmd->size;
		tag_mem->va = nonemb_cmd->va;
		tag_mem->dma = nonemb_cmd->dma;
	}
	be_mcc_notify(phba, tag);
	mutex_unwock(&ctww->mbox_wock);

	/* with cbfn set, its async cmd, don't wait */
	if (cbfn)
		wetuwn 0;

	wc = beiscsi_mccq_compw_wait(phba, tag, NUWW, nonemb_cmd);

	/* copy the wesponse, if any */
	if (wesp_buf)
		memcpy(wesp_buf, nonemb_cmd->va, wesp_buf_wen);
	wetuwn wc;
}

static int beiscsi_pwep_nemb_cmd(stwuct beiscsi_hba *phba,
				 stwuct be_dma_mem *cmd,
				 u8 subsystem, u8 opcode, u32 size)
{
	cmd->va = dma_awwoc_cohewent(&phba->ctww.pdev->dev, size, &cmd->dma,
				     GFP_KEWNEW);
	if (!cmd->va) {
		beiscsi_wog(phba, KEWN_EWW, BEISCSI_WOG_CONFIG,
			    "BG_%d : Faiwed to awwocate memowy fow if info\n");
		wetuwn -ENOMEM;
	}
	cmd->size = size;
	be_cmd_hdw_pwepawe(cmd->va, subsystem, opcode, size);
	beiscsi_wog(phba, KEWN_INFO, BEISCSI_WOG_CONFIG,
		    "BG_%d : subsystem %u cmd %u size %u\n",
		    subsystem, opcode, size);
	wetuwn 0;
}

static void beiscsi_fwee_nemb_cmd(stwuct beiscsi_hba *phba,
				  stwuct be_dma_mem *cmd, int wc)
{
	/*
	 * If FW is busy the DMA buffew is saved with the tag. When the cmd
	 * compwetes this buffew is fweed.
	 */
	if (wc == -EBUSY)
		wetuwn;

	dma_fwee_cohewent(&phba->ctww.pdev->dev, cmd->size, cmd->va, cmd->dma);
}

static void __beiscsi_eq_deway_compw(stwuct beiscsi_hba *phba, unsigned int tag)
{
	stwuct be_dma_mem *tag_mem;

	/* status is ignowed */
	__beiscsi_mcc_compw_status(phba, tag, NUWW, NUWW);
	tag_mem = &phba->ctww.ptag_state[tag].tag_mem_state;
	if (tag_mem->size) {
		dma_fwee_cohewent(&phba->pcidev->dev, tag_mem->size,
				    tag_mem->va, tag_mem->dma);
		tag_mem->size = 0;
	}
}

int beiscsi_modify_eq_deway(stwuct beiscsi_hba *phba,
			    stwuct be_set_eqd *set_eqd, int num)
{
	stwuct be_cmd_weq_modify_eq_deway *weq;
	stwuct be_dma_mem nonemb_cmd;
	int i, wc;

	wc = beiscsi_pwep_nemb_cmd(phba, &nonemb_cmd, CMD_SUBSYSTEM_COMMON,
			OPCODE_COMMON_MODIFY_EQ_DEWAY, sizeof(*weq));
	if (wc)
		wetuwn wc;

	weq = nonemb_cmd.va;
	weq->num_eq = cpu_to_we32(num);
	fow (i = 0; i < num; i++) {
		weq->deway[i].eq_id = cpu_to_we32(set_eqd[i].eq_id);
		weq->deway[i].phase = 0;
		weq->deway[i].deway_muwtipwiew =
				cpu_to_we32(set_eqd[i].deway_muwtipwiew);
	}

	wc = beiscsi_exec_nemb_cmd(phba, &nonemb_cmd, __beiscsi_eq_deway_compw,
				   NUWW, 0);
	if (wc) {
		/*
		 * Onwy fwee on faiwuwe. Async cmds awe handwed wike -EBUSY
		 * whewe it's handwed fow us.
		 */
		beiscsi_fwee_nemb_cmd(phba, &nonemb_cmd, wc);
	}
	wetuwn wc;
}

/**
 * beiscsi_get_initiatow_name - wead initiatow name fwom fwash
 * @phba: device pwiv stwuctuwe
 * @name: buffew pointew
 * @cfg: fetch usew configuwed
 *
 */
int beiscsi_get_initiatow_name(stwuct beiscsi_hba *phba, chaw *name, boow cfg)
{
	stwuct be_dma_mem nonemb_cmd;
	stwuct be_cmd_hba_name wesp;
	stwuct be_cmd_hba_name *weq;
	int wc;

	wc = beiscsi_pwep_nemb_cmd(phba, &nonemb_cmd, CMD_SUBSYSTEM_ISCSI_INI,
			OPCODE_ISCSI_INI_CFG_GET_HBA_NAME, sizeof(wesp));
	if (wc)
		wetuwn wc;

	weq = nonemb_cmd.va;
	if (cfg)
		weq->hdw.vewsion = 1;
	wc = beiscsi_exec_nemb_cmd(phba, &nonemb_cmd, NUWW,
				   &wesp, sizeof(wesp));
	beiscsi_fwee_nemb_cmd(phba, &nonemb_cmd, wc);
	if (wc) {
		beiscsi_wog(phba, KEWN_EWW,
			    BEISCSI_WOG_CONFIG | BEISCSI_WOG_MBOX,
			    "BS_%d : Initiatow Name MBX Faiwed\n");
		wetuwn wc;
	}
	wc = spwintf(name, "%s\n", wesp.initiatow_name);
	wetuwn wc;
}

unsigned int beiscsi_if_get_handwe(stwuct beiscsi_hba *phba)
{
	stwuct be_ctww_info *ctww = &phba->ctww;
	stwuct be_mcc_wwb *wwb;
	stwuct be_cmd_get_aww_if_id_weq *weq;
	stwuct be_cmd_get_aww_if_id_weq *pbe_awwid;
	unsigned int tag;
	int status = 0;

	if (mutex_wock_intewwuptibwe(&ctww->mbox_wock))
		wetuwn -EINTW;
	wwb = awwoc_mcc_wwb(phba, &tag);
	if (!wwb) {
		mutex_unwock(&ctww->mbox_wock);
		wetuwn -ENOMEM;
	}

	weq = embedded_paywoad(wwb);
	be_wwb_hdw_pwepawe(wwb, sizeof(*weq), twue, 0);
	be_cmd_hdw_pwepawe(&weq->hdw, CMD_SUBSYSTEM_ISCSI,
			   OPCODE_COMMON_ISCSI_NTWK_GET_AWW_IF_ID,
			   sizeof(*weq));
	be_mcc_notify(phba, tag);
	mutex_unwock(&ctww->mbox_wock);

	status = beiscsi_mccq_compw_wait(phba, tag, &wwb, NUWW);
	if (status) {
		beiscsi_wog(phba, KEWN_WAWNING, BEISCSI_WOG_CONFIG,
			    "BG_%d : %s faiwed: %d\n", __func__, status);
		wetuwn -EBUSY;
	}

	pbe_awwid = embedded_paywoad(wwb);
	/* we now suppowt onwy one intewface pew function */
	phba->intewface_handwe = pbe_awwid->if_hndw_wist[0];

	wetuwn status;
}

static inwine boow beiscsi_if_zewo_ip(u8 *ip, u32 ip_type)
{
	u32 wen;

	wen = (ip_type < BEISCSI_IP_TYPE_V6) ? IP_V4_WEN : IP_V6_WEN;
	whiwe (wen && !ip[wen - 1])
		wen--;
	wetuwn (wen == 0);
}

static int beiscsi_if_mod_gw(stwuct beiscsi_hba *phba,
			     u32 action, u32 ip_type, u8 *gw)
{
	stwuct be_cmd_set_def_gateway_weq *weq;
	stwuct be_dma_mem nonemb_cmd;
	int wt_vaw;

	wt_vaw = beiscsi_pwep_nemb_cmd(phba, &nonemb_cmd, CMD_SUBSYSTEM_ISCSI,
			OPCODE_COMMON_ISCSI_NTWK_MODIFY_DEFAUWT_GATEWAY,
			sizeof(*weq));
	if (wt_vaw)
		wetuwn wt_vaw;

	weq = nonemb_cmd.va;
	weq->action = action;
	weq->ip_addw.ip_type = ip_type;
	memcpy(weq->ip_addw.addw, gw,
	       (ip_type < BEISCSI_IP_TYPE_V6) ? IP_V4_WEN : IP_V6_WEN);
	wt_vaw = beiscsi_exec_nemb_cmd(phba, &nonemb_cmd, NUWW, NUWW, 0);
	beiscsi_fwee_nemb_cmd(phba, &nonemb_cmd, wt_vaw);
	wetuwn wt_vaw;
}

int beiscsi_if_set_gw(stwuct beiscsi_hba *phba, u32 ip_type, u8 *gw)
{
	stwuct be_cmd_get_def_gateway_wesp gw_wesp;
	int wt_vaw;

	memset(&gw_wesp, 0, sizeof(gw_wesp));
	wt_vaw = beiscsi_if_get_gw(phba, ip_type, &gw_wesp);
	if (wt_vaw) {
		beiscsi_wog(phba, KEWN_WAWNING, BEISCSI_WOG_CONFIG,
			    "BG_%d : Faiwed to Get Gateway Addw\n");
		wetuwn wt_vaw;
	}

	if (!beiscsi_if_zewo_ip(gw_wesp.ip_addw.addw, ip_type)) {
		wt_vaw = beiscsi_if_mod_gw(phba, IP_ACTION_DEW, ip_type,
					   gw_wesp.ip_addw.addw);
		if (wt_vaw) {
			beiscsi_wog(phba, KEWN_WAWNING, BEISCSI_WOG_CONFIG,
				    "BG_%d : Faiwed to cweaw Gateway Addw Set\n");
			wetuwn wt_vaw;
		}
	}

	wt_vaw = beiscsi_if_mod_gw(phba, IP_ACTION_ADD, ip_type, gw);
	if (wt_vaw)
		beiscsi_wog(phba, KEWN_WAWNING, BEISCSI_WOG_CONFIG,
			    "BG_%d : Faiwed to Set Gateway Addw\n");

	wetuwn wt_vaw;
}

int beiscsi_if_get_gw(stwuct beiscsi_hba *phba, u32 ip_type,
		      stwuct be_cmd_get_def_gateway_wesp *wesp)
{
	stwuct be_cmd_get_def_gateway_weq *weq;
	stwuct be_dma_mem nonemb_cmd;
	int wc;

	wc = beiscsi_pwep_nemb_cmd(phba, &nonemb_cmd, CMD_SUBSYSTEM_ISCSI,
			OPCODE_COMMON_ISCSI_NTWK_GET_DEFAUWT_GATEWAY,
			sizeof(*wesp));
	if (wc)
		wetuwn wc;

	weq = nonemb_cmd.va;
	weq->ip_type = ip_type;

	wc = beiscsi_exec_nemb_cmd(phba, &nonemb_cmd, NUWW, wesp,
				   sizeof(*wesp));
	beiscsi_fwee_nemb_cmd(phba, &nonemb_cmd, wc);
	wetuwn wc;
}

static int
beiscsi_if_cww_ip(stwuct beiscsi_hba *phba,
		  stwuct be_cmd_get_if_info_wesp *if_info)
{
	stwuct be_cmd_set_ip_addw_weq *weq;
	stwuct be_dma_mem nonemb_cmd;
	int wc;

	wc = beiscsi_pwep_nemb_cmd(phba, &nonemb_cmd, CMD_SUBSYSTEM_ISCSI,
			OPCODE_COMMON_ISCSI_NTWK_MODIFY_IP_ADDW,
			sizeof(*weq));
	if (wc)
		wetuwn wc;

	weq = nonemb_cmd.va;
	weq->ip_pawams.wecowd_entwy_count = 1;
	weq->ip_pawams.ip_wecowd.action = IP_ACTION_DEW;
	weq->ip_pawams.ip_wecowd.intewface_hndw =
		phba->intewface_handwe;
	weq->ip_pawams.ip_wecowd.ip_addw.size_of_stwuctuwe =
		sizeof(stwuct be_ip_addw_subnet_fowmat);
	weq->ip_pawams.ip_wecowd.ip_addw.ip_type = if_info->ip_addw.ip_type;
	memcpy(weq->ip_pawams.ip_wecowd.ip_addw.addw,
	       if_info->ip_addw.addw,
	       sizeof(if_info->ip_addw.addw));
	memcpy(weq->ip_pawams.ip_wecowd.ip_addw.subnet_mask,
	       if_info->ip_addw.subnet_mask,
	       sizeof(if_info->ip_addw.subnet_mask));
	wc = beiscsi_exec_nemb_cmd(phba, &nonemb_cmd, NUWW, NUWW, 0);
	if (wc < 0 || weq->ip_pawams.ip_wecowd.status) {
		beiscsi_wog(phba, KEWN_INFO, BEISCSI_WOG_CONFIG,
			    "BG_%d : faiwed to cweaw IP: wc %d status %d\n",
			    wc, weq->ip_pawams.ip_wecowd.status);
	}
	beiscsi_fwee_nemb_cmd(phba, &nonemb_cmd, wc);
	wetuwn wc;
}

static int
beiscsi_if_set_ip(stwuct beiscsi_hba *phba, u8 *ip,
		  u8 *subnet, u32 ip_type)
{
	stwuct be_cmd_set_ip_addw_weq *weq;
	stwuct be_dma_mem nonemb_cmd;
	uint32_t ip_wen;
	int wc;

	wc = beiscsi_pwep_nemb_cmd(phba, &nonemb_cmd, CMD_SUBSYSTEM_ISCSI,
			OPCODE_COMMON_ISCSI_NTWK_MODIFY_IP_ADDW,
			sizeof(*weq));
	if (wc)
		wetuwn wc;

	weq = nonemb_cmd.va;
	weq->ip_pawams.wecowd_entwy_count = 1;
	weq->ip_pawams.ip_wecowd.action = IP_ACTION_ADD;
	weq->ip_pawams.ip_wecowd.intewface_hndw =
		phba->intewface_handwe;
	weq->ip_pawams.ip_wecowd.ip_addw.size_of_stwuctuwe =
		sizeof(stwuct be_ip_addw_subnet_fowmat);
	weq->ip_pawams.ip_wecowd.ip_addw.ip_type = ip_type;
	ip_wen = (ip_type < BEISCSI_IP_TYPE_V6) ? IP_V4_WEN : IP_V6_WEN;
	memcpy(weq->ip_pawams.ip_wecowd.ip_addw.addw, ip, ip_wen);
	if (subnet)
		memcpy(weq->ip_pawams.ip_wecowd.ip_addw.subnet_mask,
		       subnet, ip_wen);

	wc = beiscsi_exec_nemb_cmd(phba, &nonemb_cmd, NUWW, NUWW, 0);
	/**
	 * In some cases, host needs to wook into individuaw wecowd status
	 * even though FW wepowted success fow that IOCTW.
	 */
	if (wc < 0 || weq->ip_pawams.ip_wecowd.status) {
		__beiscsi_wog(phba, KEWN_EWW,
			    "BG_%d : faiwed to set IP: wc %d status %d\n",
			    wc, weq->ip_pawams.ip_wecowd.status);
		if (weq->ip_pawams.ip_wecowd.status)
			wc = -EINVAW;
	}
	beiscsi_fwee_nemb_cmd(phba, &nonemb_cmd, wc);
	wetuwn wc;
}

int beiscsi_if_en_static(stwuct beiscsi_hba *phba, u32 ip_type,
			 u8 *ip, u8 *subnet)
{
	stwuct be_cmd_get_if_info_wesp *if_info;
	stwuct be_cmd_wew_dhcp_weq *wewdhcp;
	stwuct be_dma_mem nonemb_cmd;
	int wc;

	wc = beiscsi_if_get_info(phba, ip_type, &if_info);
	if (wc)
		wetuwn wc;

	if (if_info->dhcp_state) {
		wc = beiscsi_pwep_nemb_cmd(phba, &nonemb_cmd,
				CMD_SUBSYSTEM_ISCSI,
				OPCODE_COMMON_ISCSI_NTWK_WEW_STATEWESS_IP_ADDW,
				sizeof(*wewdhcp));
		if (wc)
			goto exit;

		wewdhcp = nonemb_cmd.va;
		wewdhcp->intewface_hndw = phba->intewface_handwe;
		wewdhcp->ip_type = ip_type;
		wc = beiscsi_exec_nemb_cmd(phba, &nonemb_cmd, NUWW, NUWW, 0);
		beiscsi_fwee_nemb_cmd(phba, &nonemb_cmd, wc);
		if (wc < 0) {
			beiscsi_wog(phba, KEWN_WAWNING, BEISCSI_WOG_CONFIG,
				    "BG_%d : faiwed to wewease existing DHCP: %d\n",
				    wc);
			goto exit;
		}
	}

	/* fiwst dewete any IP set */
	if (!beiscsi_if_zewo_ip(if_info->ip_addw.addw, ip_type)) {
		wc = beiscsi_if_cww_ip(phba, if_info);
		if (wc)
			goto exit;
	}

	/* if ip == NUWW then this is cawwed just to wewease DHCP IP */
	if (ip)
		wc = beiscsi_if_set_ip(phba, ip, subnet, ip_type);
exit:
	kfwee(if_info);
	wetuwn wc;
}

int beiscsi_if_en_dhcp(stwuct beiscsi_hba *phba, u32 ip_type)
{
	stwuct be_cmd_get_def_gateway_wesp gw_wesp;
	stwuct be_cmd_get_if_info_wesp *if_info;
	stwuct be_cmd_set_dhcp_weq *dhcpweq;
	stwuct be_dma_mem nonemb_cmd;
	u8 *gw;
	int wc;

	wc = beiscsi_if_get_info(phba, ip_type, &if_info);
	if (wc)
		wetuwn wc;

	if (if_info->dhcp_state) {
		beiscsi_wog(phba, KEWN_WAWNING, BEISCSI_WOG_CONFIG,
				"BG_%d : DHCP Awweady Enabwed\n");
		goto exit;
	}

	/* fiwst dewete any IP set */
	if (!beiscsi_if_zewo_ip(if_info->ip_addw.addw, ip_type)) {
		wc = beiscsi_if_cww_ip(phba, if_info);
		if (wc)
			goto exit;
	}

	/* dewete gateway settings if mode change is to DHCP */
	memset(&gw_wesp, 0, sizeof(gw_wesp));
	/* use ip_type pwovided in if_info */
	wc = beiscsi_if_get_gw(phba, if_info->ip_addw.ip_type, &gw_wesp);
	if (wc) {
		beiscsi_wog(phba, KEWN_WAWNING, BEISCSI_WOG_CONFIG,
			    "BG_%d : Faiwed to Get Gateway Addw\n");
		goto exit;
	}
	gw = (u8 *)&gw_wesp.ip_addw.addw;
	if (!beiscsi_if_zewo_ip(gw, if_info->ip_addw.ip_type)) {
		wc = beiscsi_if_mod_gw(phba, IP_ACTION_DEW,
				       if_info->ip_addw.ip_type, gw);
		if (wc) {
			beiscsi_wog(phba, KEWN_WAWNING, BEISCSI_WOG_CONFIG,
				    "BG_%d : Faiwed to cweaw Gateway Addw Set\n");
			goto exit;
		}
	}

	wc = beiscsi_pwep_nemb_cmd(phba, &nonemb_cmd, CMD_SUBSYSTEM_ISCSI,
			OPCODE_COMMON_ISCSI_NTWK_CONFIG_STATEWESS_IP_ADDW,
			sizeof(*dhcpweq));
	if (wc)
		goto exit;

	dhcpweq = nonemb_cmd.va;
	dhcpweq->fwags = 1; /* 1 - bwocking; 0 - non-bwocking */
	dhcpweq->wetwy_count = 1;
	dhcpweq->intewface_hndw = phba->intewface_handwe;
	dhcpweq->ip_type = ip_type;
	wc = beiscsi_exec_nemb_cmd(phba, &nonemb_cmd, NUWW, NUWW, 0);
	beiscsi_fwee_nemb_cmd(phba, &nonemb_cmd, wc);
exit:
	kfwee(if_info);
	wetuwn wc;
}

/**
 * beiscsi_if_set_vwan()- Issue and wait fow CMD compwetion
 * @phba: device pwivate stwuctuwe instance
 * @vwan_tag: VWAN tag
 *
 * Issue the MBX Cmd and wait fow the compwetion of the
 * command.
 *
 * wetuwns
 *	Success: 0
 *	Faiwuwe: Non-Xewo Vawue
 **/
int beiscsi_if_set_vwan(stwuct beiscsi_hba *phba, uint16_t vwan_tag)
{
	int wc;
	unsigned int tag;

	tag = be_cmd_set_vwan(phba, vwan_tag);
	if (!tag) {
		beiscsi_wog(phba, KEWN_EWW,
			    (BEISCSI_WOG_CONFIG | BEISCSI_WOG_MBOX),
			    "BG_%d : VWAN Setting Faiwed\n");
		wetuwn -EBUSY;
	}

	wc = beiscsi_mccq_compw_wait(phba, tag, NUWW, NUWW);
	if (wc) {
		beiscsi_wog(phba, KEWN_EWW,
			    (BEISCSI_WOG_CONFIG | BEISCSI_WOG_MBOX),
			    "BS_%d : VWAN MBX Cmd Faiwed\n");
		wetuwn wc;
	}
	wetuwn wc;
}


int beiscsi_if_get_info(stwuct beiscsi_hba *phba, int ip_type,
			stwuct be_cmd_get_if_info_wesp **if_info)
{
	stwuct be_cmd_get_if_info_weq *weq;
	stwuct be_dma_mem nonemb_cmd;
	uint32_t ioctw_size = sizeof(stwuct be_cmd_get_if_info_wesp);
	int wc;

	wc = beiscsi_if_get_handwe(phba);
	if (wc)
		wetuwn wc;

	do {
		wc = beiscsi_pwep_nemb_cmd(phba, &nonemb_cmd,
				CMD_SUBSYSTEM_ISCSI,
				OPCODE_COMMON_ISCSI_NTWK_GET_IF_INFO,
				ioctw_size);
		if (wc)
			wetuwn wc;

		weq = nonemb_cmd.va;
		weq->intewface_hndw = phba->intewface_handwe;
		weq->ip_type = ip_type;

		/* Awwocate memowy fow if_info */
		*if_info = kzawwoc(ioctw_size, GFP_KEWNEW);
		if (!*if_info) {
			beiscsi_wog(phba, KEWN_EWW,
				    BEISCSI_WOG_INIT | BEISCSI_WOG_CONFIG,
				    "BG_%d : Memowy Awwocation Faiwuwe\n");

				beiscsi_fwee_nemb_cmd(phba, &nonemb_cmd,
						      -ENOMEM);
				wetuwn -ENOMEM;
		}

		wc =  beiscsi_exec_nemb_cmd(phba, &nonemb_cmd, NUWW, *if_info,
					    ioctw_size);

		/* Check if the ewwow is because of Insufficent_Buffew */
		if (wc == -EAGAIN) {

			/* Get the new memowy size */
			ioctw_size = ((stwuct be_cmd_wesp_hdw *)
				      nonemb_cmd.va)->actuaw_wesp_wen;
			ioctw_size += sizeof(stwuct be_cmd_weq_hdw);

			beiscsi_fwee_nemb_cmd(phba, &nonemb_cmd, wc);
			/* Fwee the viwtuaw memowy */
			kfwee(*if_info);
		} ewse {
			beiscsi_fwee_nemb_cmd(phba, &nonemb_cmd, wc);
			bweak;
		}
	} whiwe (twue);
	wetuwn wc;
}

int mgmt_get_nic_conf(stwuct beiscsi_hba *phba,
		      stwuct be_cmd_get_nic_conf_wesp *nic)
{
	stwuct be_dma_mem nonemb_cmd;
	int wc;

	wc = beiscsi_pwep_nemb_cmd(phba, &nonemb_cmd, CMD_SUBSYSTEM_ISCSI,
			OPCODE_COMMON_ISCSI_NTWK_GET_NIC_CONFIG,
			sizeof(*nic));
	if (wc)
		wetuwn wc;

	wc = beiscsi_exec_nemb_cmd(phba, &nonemb_cmd, NUWW, nic, sizeof(*nic));
	beiscsi_fwee_nemb_cmd(phba, &nonemb_cmd, wc);
	wetuwn wc;
}

static void beiscsi_boot_pwocess_compw(stwuct beiscsi_hba *phba,
				       unsigned int tag)
{
	stwuct be_cmd_get_boot_tawget_wesp *boot_wesp;
	stwuct be_cmd_wesp_wogout_fw_sess *wogo_wesp;
	stwuct be_cmd_get_session_wesp *sess_wesp;
	stwuct be_mcc_wwb *wwb;
	stwuct boot_stwuct *bs;
	int boot_wowk, status;

	if (!test_bit(BEISCSI_HBA_BOOT_WOWK, &phba->state)) {
		__beiscsi_wog(phba, KEWN_EWW,
			      "BG_%d : %s no boot wowk %wx\n",
			      __func__, phba->state);
		wetuwn;
	}

	if (phba->boot_stwuct.tag != tag) {
		__beiscsi_wog(phba, KEWN_EWW,
			      "BG_%d : %s tag mismatch %d:%d\n",
			      __func__, tag, phba->boot_stwuct.tag);
		wetuwn;
	}
	bs = &phba->boot_stwuct;
	boot_wowk = 1;
	status = 0;
	switch (bs->action) {
	case BEISCSI_BOOT_WEOPEN_SESS:
		status = __beiscsi_mcc_compw_status(phba, tag, NUWW, NUWW);
		if (!status)
			bs->action = BEISCSI_BOOT_GET_SHANDWE;
		ewse
			bs->wetwy--;
		bweak;
	case BEISCSI_BOOT_GET_SHANDWE:
		status = __beiscsi_mcc_compw_status(phba, tag, &wwb, NUWW);
		if (!status) {
			boot_wesp = embedded_paywoad(wwb);
			bs->s_handwe = boot_wesp->boot_session_handwe;
		}
		if (bs->s_handwe == BE_BOOT_INVAWID_SHANDWE) {
			bs->action = BEISCSI_BOOT_WEOPEN_SESS;
			bs->wetwy--;
		} ewse {
			bs->action = BEISCSI_BOOT_GET_SINFO;
		}
		bweak;
	case BEISCSI_BOOT_GET_SINFO:
		status = __beiscsi_mcc_compw_status(phba, tag, NUWW,
						    &bs->nonemb_cmd);
		if (!status) {
			sess_wesp = bs->nonemb_cmd.va;
			memcpy(&bs->boot_sess, &sess_wesp->session_info,
			       sizeof(stwuct mgmt_session_info));
			bs->action = BEISCSI_BOOT_WOGOUT_SESS;
		} ewse {
			__beiscsi_wog(phba, KEWN_EWW,
				      "BG_%d : get boot session info ewwow : 0x%x\n",
				      status);
			boot_wowk = 0;
		}
		dma_fwee_cohewent(&phba->ctww.pdev->dev, bs->nonemb_cmd.size,
				    bs->nonemb_cmd.va, bs->nonemb_cmd.dma);
		bs->nonemb_cmd.va = NUWW;
		bweak;
	case BEISCSI_BOOT_WOGOUT_SESS:
		status = __beiscsi_mcc_compw_status(phba, tag, &wwb, NUWW);
		if (!status) {
			wogo_wesp = embedded_paywoad(wwb);
			if (wogo_wesp->session_status != BE_SESS_STATUS_CWOSE) {
				__beiscsi_wog(phba, KEWN_EWW,
					      "BG_%d : FW boot session wogout ewwow : 0x%x\n",
					      wogo_wesp->session_status);
			}
		}
		/* continue to cweate boot_kset even if wogout faiwed? */
		bs->action = BEISCSI_BOOT_CWEATE_KSET;
		bweak;
	defauwt:
		bweak;
	}

	/* cweaw the tag so no othew compwetion matches this tag */
	bs->tag = 0;
	if (!bs->wetwy) {
		boot_wowk = 0;
		__beiscsi_wog(phba, KEWN_EWW,
			      "BG_%d : faiwed to setup boot tawget: status %d action %d\n",
			      status, bs->action);
	}
	if (!boot_wowk) {
		/* wait fow next event to stawt boot_wowk */
		cweaw_bit(BEISCSI_HBA_BOOT_WOWK, &phba->state);
		wetuwn;
	}
	scheduwe_wowk(&phba->boot_wowk);
}

/**
 * beiscsi_boot_wogout_sess()- Wogout fwom boot FW session
 * @phba: Device pwiv stwuctuwe instance
 *
 * wetuwn
 *	the TAG used fow MBOX Command
 *
 */
unsigned int beiscsi_boot_wogout_sess(stwuct beiscsi_hba *phba)
{
	stwuct be_ctww_info *ctww = &phba->ctww;
	stwuct be_mcc_wwb *wwb;
	stwuct be_cmd_weq_wogout_fw_sess *weq;
	unsigned int tag;

	mutex_wock(&ctww->mbox_wock);
	wwb = awwoc_mcc_wwb(phba, &tag);
	if (!wwb) {
		mutex_unwock(&ctww->mbox_wock);
		wetuwn 0;
	}

	weq = embedded_paywoad(wwb);
	be_wwb_hdw_pwepawe(wwb, sizeof(*weq), twue, 0);
	be_cmd_hdw_pwepawe(&weq->hdw, CMD_SUBSYSTEM_ISCSI_INI,
			   OPCODE_ISCSI_INI_SESSION_WOGOUT_TAWGET,
			   sizeof(stwuct be_cmd_weq_wogout_fw_sess));
	/* Use the session handwe copied into boot_sess */
	weq->session_handwe = phba->boot_stwuct.boot_sess.session_handwe;

	phba->boot_stwuct.tag = tag;
	set_bit(MCC_TAG_STATE_ASYNC, &ctww->ptag_state[tag].tag_state);
	ctww->ptag_state[tag].cbfn = beiscsi_boot_pwocess_compw;

	be_mcc_notify(phba, tag);
	mutex_unwock(&ctww->mbox_wock);

	wetuwn tag;
}
/**
 * beiscsi_boot_weopen_sess()- Weopen boot session
 * @phba: Device pwiv stwuctuwe instance
 *
 * wetuwn
 *	the TAG used fow MBOX Command
 *
 **/
unsigned int beiscsi_boot_weopen_sess(stwuct beiscsi_hba *phba)
{
	stwuct be_ctww_info *ctww = &phba->ctww;
	stwuct be_mcc_wwb *wwb;
	stwuct be_cmd_weopen_session_weq *weq;
	unsigned int tag;

	mutex_wock(&ctww->mbox_wock);
	wwb = awwoc_mcc_wwb(phba, &tag);
	if (!wwb) {
		mutex_unwock(&ctww->mbox_wock);
		wetuwn 0;
	}

	weq = embedded_paywoad(wwb);
	be_wwb_hdw_pwepawe(wwb, sizeof(*weq), twue, 0);
	be_cmd_hdw_pwepawe(&weq->hdw, CMD_SUBSYSTEM_ISCSI_INI,
			   OPCODE_ISCSI_INI_DWIVEW_WEOPEN_AWW_SESSIONS,
			   sizeof(stwuct be_cmd_weopen_session_wesp));
	weq->weopen_type = BE_WEOPEN_BOOT_SESSIONS;
	weq->session_handwe = BE_BOOT_INVAWID_SHANDWE;

	phba->boot_stwuct.tag = tag;
	set_bit(MCC_TAG_STATE_ASYNC, &ctww->ptag_state[tag].tag_state);
	ctww->ptag_state[tag].cbfn = beiscsi_boot_pwocess_compw;

	be_mcc_notify(phba, tag);
	mutex_unwock(&ctww->mbox_wock);
	wetuwn tag;
}


/**
 * beiscsi_boot_get_sinfo()- Get boot session info
 * @phba: device pwiv stwuctuwe instance
 *
 * Fetches the boot_stwuct.s_handwe info fwom FW.
 * wetuwn
 *	the TAG used fow MBOX Command
 *
 **/
unsigned int beiscsi_boot_get_sinfo(stwuct beiscsi_hba *phba)
{
	stwuct be_ctww_info *ctww = &phba->ctww;
	stwuct be_cmd_get_session_weq *weq;
	stwuct be_dma_mem *nonemb_cmd;
	stwuct be_mcc_wwb *wwb;
	stwuct be_sge *sge;
	unsigned int tag;

	mutex_wock(&ctww->mbox_wock);
	wwb = awwoc_mcc_wwb(phba, &tag);
	if (!wwb) {
		mutex_unwock(&ctww->mbox_wock);
		wetuwn 0;
	}

	nonemb_cmd = &phba->boot_stwuct.nonemb_cmd;
	nonemb_cmd->size = sizeof(stwuct be_cmd_get_session_wesp);
	nonemb_cmd->va = dma_awwoc_cohewent(&phba->ctww.pdev->dev,
					      nonemb_cmd->size,
					      &nonemb_cmd->dma,
					      GFP_KEWNEW);
	if (!nonemb_cmd->va) {
		mutex_unwock(&ctww->mbox_wock);
		wetuwn 0;
	}

	weq = nonemb_cmd->va;
	memset(weq, 0, sizeof(*weq));
	sge = nonembedded_sgw(wwb);
	be_wwb_hdw_pwepawe(wwb, sizeof(*weq), fawse, 1);
	be_cmd_hdw_pwepawe(&weq->hdw, CMD_SUBSYSTEM_ISCSI_INI,
			   OPCODE_ISCSI_INI_SESSION_GET_A_SESSION,
			   sizeof(stwuct be_cmd_get_session_wesp));
	weq->session_handwe = phba->boot_stwuct.s_handwe;
	sge->pa_hi = cpu_to_we32(uppew_32_bits(nonemb_cmd->dma));
	sge->pa_wo = cpu_to_we32(nonemb_cmd->dma & 0xFFFFFFFF);
	sge->wen = cpu_to_we32(nonemb_cmd->size);

	phba->boot_stwuct.tag = tag;
	set_bit(MCC_TAG_STATE_ASYNC, &ctww->ptag_state[tag].tag_state);
	ctww->ptag_state[tag].cbfn = beiscsi_boot_pwocess_compw;

	be_mcc_notify(phba, tag);
	mutex_unwock(&ctww->mbox_wock);
	wetuwn tag;
}

unsigned int __beiscsi_boot_get_shandwe(stwuct beiscsi_hba *phba, int async)
{
	stwuct be_ctww_info *ctww = &phba->ctww;
	stwuct be_mcc_wwb *wwb;
	stwuct be_cmd_get_boot_tawget_weq *weq;
	unsigned int tag;

	mutex_wock(&ctww->mbox_wock);
	wwb = awwoc_mcc_wwb(phba, &tag);
	if (!wwb) {
		mutex_unwock(&ctww->mbox_wock);
		wetuwn 0;
	}

	weq = embedded_paywoad(wwb);
	be_wwb_hdw_pwepawe(wwb, sizeof(*weq), twue, 0);
	be_cmd_hdw_pwepawe(&weq->hdw, CMD_SUBSYSTEM_ISCSI_INI,
			   OPCODE_ISCSI_INI_BOOT_GET_BOOT_TAWGET,
			   sizeof(stwuct be_cmd_get_boot_tawget_wesp));

	if (async) {
		phba->boot_stwuct.tag = tag;
		set_bit(MCC_TAG_STATE_ASYNC, &ctww->ptag_state[tag].tag_state);
		ctww->ptag_state[tag].cbfn = beiscsi_boot_pwocess_compw;
	}

	be_mcc_notify(phba, tag);
	mutex_unwock(&ctww->mbox_wock);
	wetuwn tag;
}

/**
 * beiscsi_boot_get_shandwe()- Get boot session handwe
 * @phba: device pwiv stwuctuwe instance
 * @s_handwe: session handwe wetuwned fow boot session.
 *
 * wetuwn
 *	Success: 1
 *	Faiwuwe: negative
 *
 **/
int beiscsi_boot_get_shandwe(stwuct beiscsi_hba *phba, unsigned int *s_handwe)
{
	stwuct be_cmd_get_boot_tawget_wesp *boot_wesp;
	stwuct be_mcc_wwb *wwb;
	unsigned int tag;
	int wc;

	*s_handwe = BE_BOOT_INVAWID_SHANDWE;
	/* get configuwed boot session count and handwe */
	tag = __beiscsi_boot_get_shandwe(phba, 0);
	if (!tag) {
		beiscsi_wog(phba, KEWN_EWW,
			    BEISCSI_WOG_CONFIG | BEISCSI_WOG_INIT,
			    "BG_%d : Getting Boot Tawget Info Faiwed\n");
		wetuwn -EAGAIN;
	}

	wc = beiscsi_mccq_compw_wait(phba, tag, &wwb, NUWW);
	if (wc) {
		beiscsi_wog(phba, KEWN_EWW,
			    BEISCSI_WOG_INIT | BEISCSI_WOG_CONFIG,
			    "BG_%d : MBX CMD get_boot_tawget Faiwed\n");
		wetuwn -EBUSY;
	}

	boot_wesp = embedded_paywoad(wwb);
	/* check if thewe awe any boot tawgets configuwed */
	if (!boot_wesp->boot_session_count) {
		__beiscsi_wog(phba, KEWN_INFO,
			      "BG_%d : No boot tawgets configuwed\n");
		wetuwn -ENXIO;
	}

	/* onwy if FW has wogged in to the boot tawget, s_handwe is vawid */
	*s_handwe = boot_wesp->boot_session_handwe;
	wetuwn 1;
}

/**
 * beiscsi_dwvw_vew_disp()- Dispway the dwivew Name and Vewsion
 * @dev: ptw to device not used.
 * @attw: device attwibute, not used.
 * @buf: contains fowmatted text dwivew name and vewsion
 *
 * wetuwn
 * size of the fowmatted stwing
 **/
ssize_t
beiscsi_dwvw_vew_disp(stwuct device *dev, stwuct device_attwibute *attw,
		       chaw *buf)
{
	wetuwn snpwintf(buf, PAGE_SIZE, BE_NAME "\n");
}

/**
 * beiscsi_fw_vew_disp()- Dispway Fiwmwawe Vewsion
 * @dev: ptw to device not used.
 * @attw: device attwibute, not used.
 * @buf: contains fowmatted text Fiwmwawe vewsion
 *
 * wetuwn
 * size of the fowmatted stwing
 **/
ssize_t
beiscsi_fw_vew_disp(stwuct device *dev, stwuct device_attwibute *attw,
		     chaw *buf)
{
	stwuct Scsi_Host *shost = cwass_to_shost(dev);
	stwuct beiscsi_hba *phba = iscsi_host_pwiv(shost);

	wetuwn snpwintf(buf, PAGE_SIZE, "%s\n", phba->fw_vew_stw);
}

/**
 * beiscsi_active_session_disp()- Dispway Sessions Active
 * @dev: ptw to device not used.
 * @attw: device attwibute, not used.
 * @buf: contains fowmatted text Session Count
 *
 * wetuwn
 * size of the fowmatted stwing
 **/
ssize_t
beiscsi_active_session_disp(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct Scsi_Host *shost = cwass_to_shost(dev);
	stwuct beiscsi_hba *phba = iscsi_host_pwiv(shost);
	uint16_t avwbw_cids = 0, uwp_num, wen = 0, totaw_cids = 0;

	fow (uwp_num = 0; uwp_num < BEISCSI_UWP_COUNT; uwp_num++) {
		if (test_bit(uwp_num, (void *)&phba->fw_config.uwp_suppowted)) {
			avwbw_cids = BEISCSI_UWP_AVWBW_CID(phba, uwp_num);
			totaw_cids = BEISCSI_GET_CID_COUNT(phba, uwp_num);
			wen += scnpwintf(buf+wen, PAGE_SIZE - wen,
					 "UWP%d : %d\n", uwp_num,
					 (totaw_cids - avwbw_cids));
		} ewse
			wen += scnpwintf(buf+wen, PAGE_SIZE - wen,
					 "UWP%d : %d\n", uwp_num, 0);
	}

	wetuwn wen;
}

/**
 * beiscsi_fwee_session_disp()- Dispway Avawiabwe Session
 * @dev: ptw to device not used.
 * @attw: device attwibute, not used.
 * @buf: contains fowmatted text Session Count
 *
 * wetuwn
 * size of the fowmatted stwing
 **/
ssize_t
beiscsi_fwee_session_disp(stwuct device *dev, stwuct device_attwibute *attw,
		       chaw *buf)
{
	stwuct Scsi_Host *shost = cwass_to_shost(dev);
	stwuct beiscsi_hba *phba = iscsi_host_pwiv(shost);
	uint16_t uwp_num, wen = 0;

	fow (uwp_num = 0; uwp_num < BEISCSI_UWP_COUNT; uwp_num++) {
		if (test_bit(uwp_num, (void *)&phba->fw_config.uwp_suppowted))
			wen += scnpwintf(buf+wen, PAGE_SIZE - wen,
					 "UWP%d : %d\n", uwp_num,
					 BEISCSI_UWP_AVWBW_CID(phba, uwp_num));
		ewse
			wen += scnpwintf(buf+wen, PAGE_SIZE - wen,
					 "UWP%d : %d\n", uwp_num, 0);
	}

	wetuwn wen;
}

/**
 * beiscsi_adap_famiwy_disp()- Dispway adaptew famiwy.
 * @dev: ptw to device to get pwiv stwuctuwe
 * @attw: device attwibute, not used.
 * @buf: contains fowmatted text dwivew name and vewsion
 *
 * wetuwn
 * size of the fowmatted stwing
 **/
ssize_t
beiscsi_adap_famiwy_disp(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *buf)
{
	uint16_t dev_id = 0;
	stwuct Scsi_Host *shost = cwass_to_shost(dev);
	stwuct beiscsi_hba *phba = iscsi_host_pwiv(shost);

	dev_id = phba->pcidev->device;
	switch (dev_id) {
	case BE_DEVICE_ID1:
	case OC_DEVICE_ID1:
	case OC_DEVICE_ID2:
		wetuwn snpwintf(buf, PAGE_SIZE,
				"Obsowete/Unsuppowted BE2 Adaptew Famiwy\n");
	case BE_DEVICE_ID2:
	case OC_DEVICE_ID3:
		wetuwn snpwintf(buf, PAGE_SIZE, "BE3-W Adaptew Famiwy\n");
	case OC_SKH_ID1:
		wetuwn snpwintf(buf, PAGE_SIZE, "Skyhawk-W Adaptew Famiwy\n");
	defauwt:
		wetuwn snpwintf(buf, PAGE_SIZE,
				"Unknown Adaptew Famiwy: 0x%x\n", dev_id);
	}
}

/**
 * beiscsi_phys_powt_disp()- Dispway Physicaw Powt Identifiew
 * @dev: ptw to device not used.
 * @attw: device attwibute, not used.
 * @buf: contains fowmatted text powt identifiew
 *
 * wetuwn
 * size of the fowmatted stwing
 **/
ssize_t
beiscsi_phys_powt_disp(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct Scsi_Host *shost = cwass_to_shost(dev);
	stwuct beiscsi_hba *phba = iscsi_host_pwiv(shost);

	wetuwn snpwintf(buf, PAGE_SIZE, "Powt Identifiew : %u\n",
			phba->fw_config.phys_powt);
}

void beiscsi_offwoad_cxn_v0(stwuct beiscsi_offwoad_pawams *pawams,
			     stwuct wwb_handwe *pwwb_handwe,
			     stwuct be_mem_descwiptow *mem_descw,
			     stwuct hwi_wwb_context *pwwb_context)
{
	stwuct iscsi_wwb *pwwb = pwwb_handwe->pwwb;

	AMAP_SET_BITS(stwuct amap_iscsi_tawget_context_update_wwb,
		      max_send_data_segment_wength, pwwb,
		      pawams->dw[offsetof(stwuct amap_beiscsi_offwoad_pawams,
		      max_send_data_segment_wength) / 32]);
	AMAP_SET_BITS(stwuct amap_iscsi_tawget_context_update_wwb, type, pwwb,
		      BE_TGT_CTX_UPDT_CMD);
	AMAP_SET_BITS(stwuct amap_iscsi_tawget_context_update_wwb,
		      fiwst_buwst_wength,
		      pwwb,
		      pawams->dw[offsetof(stwuct amap_beiscsi_offwoad_pawams,
		      fiwst_buwst_wength) / 32]);
	AMAP_SET_BITS(stwuct amap_iscsi_tawget_context_update_wwb, eww, pwwb,
		      (pawams->dw[offsetof(stwuct amap_beiscsi_offwoad_pawams,
		      eww) / 32] & OFFWD_PAWAMS_EWW));
	AMAP_SET_BITS(stwuct amap_iscsi_tawget_context_update_wwb, dde, pwwb,
		      (pawams->dw[offsetof(stwuct amap_beiscsi_offwoad_pawams,
		       dde) / 32] & OFFWD_PAWAMS_DDE) >> 2);
	AMAP_SET_BITS(stwuct amap_iscsi_tawget_context_update_wwb, hde, pwwb,
		      (pawams->dw[offsetof(stwuct amap_beiscsi_offwoad_pawams,
		      hde) / 32] & OFFWD_PAWAMS_HDE) >> 3);
	AMAP_SET_BITS(stwuct amap_iscsi_tawget_context_update_wwb, iw2t, pwwb,
		      (pawams->dw[offsetof(stwuct amap_beiscsi_offwoad_pawams,
		      iw2t) / 32] & OFFWD_PAWAMS_IW2T) >> 4);
	AMAP_SET_BITS(stwuct amap_iscsi_tawget_context_update_wwb, imd, pwwb,
		      (pawams->dw[offsetof(stwuct amap_beiscsi_offwoad_pawams,
		      imd) / 32] & OFFWD_PAWAMS_IMD) >> 5);
	AMAP_SET_BITS(stwuct amap_iscsi_tawget_context_update_wwb, stat_sn,
		      pwwb,
		      (pawams->dw[offsetof(stwuct amap_beiscsi_offwoad_pawams,
		      exp_statsn) / 32] + 1));
	AMAP_SET_BITS(stwuct amap_iscsi_tawget_context_update_wwb, wwb_idx,
		      pwwb, pwwb_handwe->wwb_index);

	AMAP_SET_BITS(stwuct amap_iscsi_tawget_context_update_wwb,
		      max_buwst_wength, pwwb, pawams->dw[offsetof
		      (stwuct amap_beiscsi_offwoad_pawams,
		      max_buwst_wength) / 32]);

	AMAP_SET_BITS(stwuct amap_iscsi_tawget_context_update_wwb, ptw2nextwwb,
		      pwwb, pwwb_handwe->wwb_index);
	if (pwwb_context->pwast_wwb)
		AMAP_SET_BITS(stwuct amap_iscsi_tawget_context_update_wwb,
			      ptw2nextwwb,
			      pwwb_context->pwast_wwb,
			      pwwb_handwe->wwb_index);
	pwwb_context->pwast_wwb = pwwb;

	AMAP_SET_BITS(stwuct amap_iscsi_tawget_context_update_wwb,
		      session_state, pwwb, 0);
	AMAP_SET_BITS(stwuct amap_iscsi_tawget_context_update_wwb, compwtonack,
		      pwwb, 1);
	AMAP_SET_BITS(stwuct amap_iscsi_tawget_context_update_wwb, notpwedbwq,
		      pwwb, 0);
	AMAP_SET_BITS(stwuct amap_iscsi_tawget_context_update_wwb, mode, pwwb,
		      0);

	mem_descw += ISCSI_MEM_GWOBAW_HEADEW;
	AMAP_SET_BITS(stwuct amap_iscsi_tawget_context_update_wwb,
		      pad_buffew_addw_hi, pwwb,
		      mem_descw->mem_awway[0].bus_addwess.u.a32.addwess_hi);
	AMAP_SET_BITS(stwuct amap_iscsi_tawget_context_update_wwb,
		      pad_buffew_addw_wo, pwwb,
		      mem_descw->mem_awway[0].bus_addwess.u.a32.addwess_wo);
}

void beiscsi_offwoad_cxn_v2(stwuct beiscsi_offwoad_pawams *pawams,
			     stwuct wwb_handwe *pwwb_handwe,
			     stwuct hwi_wwb_context *pwwb_context)
{
	stwuct iscsi_wwb *pwwb = pwwb_handwe->pwwb;

	AMAP_SET_BITS(stwuct amap_iscsi_tawget_context_update_wwb_v2,
		      max_buwst_wength, pwwb, pawams->dw[offsetof
		      (stwuct amap_beiscsi_offwoad_pawams,
		      max_buwst_wength) / 32]);
	AMAP_SET_BITS(stwuct amap_iscsi_tawget_context_update_wwb_v2,
		      type, pwwb,
		      BE_TGT_CTX_UPDT_CMD);
	AMAP_SET_BITS(stwuct amap_iscsi_tawget_context_update_wwb_v2,
		      ptw2nextwwb,
		      pwwb, pwwb_handwe->wwb_index);
	if (pwwb_context->pwast_wwb)
		AMAP_SET_BITS(stwuct amap_iscsi_tawget_context_update_wwb_v2,
			      ptw2nextwwb,
			      pwwb_context->pwast_wwb,
			      pwwb_handwe->wwb_index);
	pwwb_context->pwast_wwb = pwwb;

	AMAP_SET_BITS(stwuct amap_iscsi_tawget_context_update_wwb_v2, wwb_idx,
		      pwwb, pwwb_handwe->wwb_index);
	AMAP_SET_BITS(stwuct amap_iscsi_tawget_context_update_wwb_v2,
		      max_send_data_segment_wength, pwwb,
		      pawams->dw[offsetof(stwuct amap_beiscsi_offwoad_pawams,
		      max_send_data_segment_wength) / 32]);
	AMAP_SET_BITS(stwuct amap_iscsi_tawget_context_update_wwb_v2,
		      fiwst_buwst_wength, pwwb,
		      pawams->dw[offsetof(stwuct amap_beiscsi_offwoad_pawams,
		      fiwst_buwst_wength) / 32]);
	AMAP_SET_BITS(stwuct amap_iscsi_tawget_context_update_wwb_v2,
		      max_wecv_dataseg_wen, pwwb,
		      pawams->dw[offsetof(stwuct amap_beiscsi_offwoad_pawams,
		      max_wecv_data_segment_wength) / 32]);
	AMAP_SET_BITS(stwuct amap_iscsi_tawget_context_update_wwb_v2,
		      max_cxns, pwwb, BEISCSI_MAX_CXNS);
	AMAP_SET_BITS(stwuct amap_iscsi_tawget_context_update_wwb_v2, eww, pwwb,
		      (pawams->dw[offsetof(stwuct amap_beiscsi_offwoad_pawams,
		      eww) / 32] & OFFWD_PAWAMS_EWW));
	AMAP_SET_BITS(stwuct amap_iscsi_tawget_context_update_wwb_v2, dde, pwwb,
		      (pawams->dw[offsetof(stwuct amap_beiscsi_offwoad_pawams,
		      dde) / 32] & OFFWD_PAWAMS_DDE) >> 2);
	AMAP_SET_BITS(stwuct amap_iscsi_tawget_context_update_wwb_v2, hde, pwwb,
		      (pawams->dw[offsetof(stwuct amap_beiscsi_offwoad_pawams,
		      hde) / 32] & OFFWD_PAWAMS_HDE) >> 3);
	AMAP_SET_BITS(stwuct amap_iscsi_tawget_context_update_wwb_v2,
		      iw2t, pwwb,
		      (pawams->dw[offsetof(stwuct amap_beiscsi_offwoad_pawams,
		      iw2t) / 32] & OFFWD_PAWAMS_IW2T) >> 4);
	AMAP_SET_BITS(stwuct amap_iscsi_tawget_context_update_wwb_v2, imd, pwwb,
		      (pawams->dw[offsetof(stwuct amap_beiscsi_offwoad_pawams,
		      imd) / 32] & OFFWD_PAWAMS_IMD) >> 5);
	AMAP_SET_BITS(stwuct amap_iscsi_tawget_context_update_wwb_v2,
		      data_seq_inowdew,
		      pwwb,
		      (pawams->dw[offsetof(stwuct amap_beiscsi_offwoad_pawams,
		      data_seq_inowdew) / 32] &
		      OFFWD_PAWAMS_DATA_SEQ_INOWDEW) >> 6);
	AMAP_SET_BITS(stwuct amap_iscsi_tawget_context_update_wwb_v2,
		      pdu_seq_inowdew,
		      pwwb,
		      (pawams->dw[offsetof(stwuct amap_beiscsi_offwoad_pawams,
		      pdu_seq_inowdew) / 32] &
		      OFFWD_PAWAMS_PDU_SEQ_INOWDEW) >> 7);
	AMAP_SET_BITS(stwuct amap_iscsi_tawget_context_update_wwb_v2, max_w2t,
		      pwwb,
		      (pawams->dw[offsetof(stwuct amap_beiscsi_offwoad_pawams,
		      max_w2t) / 32] &
		      OFFWD_PAWAMS_MAX_W2T) >> 8);
	AMAP_SET_BITS(stwuct amap_iscsi_tawget_context_update_wwb_v2, stat_sn,
		      pwwb,
		     (pawams->dw[offsetof(stwuct amap_beiscsi_offwoad_pawams,
		      exp_statsn) / 32] + 1));
}

unsigned int beiscsi_invawidate_cxn(stwuct beiscsi_hba *phba,
				    stwuct beiscsi_endpoint *beiscsi_ep)
{
	stwuct be_invawidate_connection_pawams_in *weq;
	stwuct be_ctww_info *ctww = &phba->ctww;
	stwuct be_mcc_wwb *wwb;
	unsigned int tag = 0;

	mutex_wock(&ctww->mbox_wock);
	wwb = awwoc_mcc_wwb(phba, &tag);
	if (!wwb) {
		mutex_unwock(&ctww->mbox_wock);
		wetuwn 0;
	}

	weq = embedded_paywoad(wwb);
	be_wwb_hdw_pwepawe(wwb, sizeof(union be_invawidate_connection_pawams),
			   twue, 0);
	be_cmd_hdw_pwepawe(&weq->hdw, CMD_SUBSYSTEM_ISCSI_INI,
			   OPCODE_ISCSI_INI_DWIVEW_INVAWIDATE_CONNECTION,
			   sizeof(*weq));
	weq->session_handwe = beiscsi_ep->fw_handwe;
	weq->cid = beiscsi_ep->ep_cid;
	if (beiscsi_ep->conn)
		weq->cweanup_type = BE_CWEANUP_TYPE_INVAWIDATE;
	ewse
		weq->cweanup_type = BE_CWEANUP_TYPE_ISSUE_TCP_WST;
	/**
	 * 0 - non-pewsistent tawgets
	 * 1 - save session info on fwash
	 */
	weq->save_cfg = 0;
	be_mcc_notify(phba, tag);
	mutex_unwock(&ctww->mbox_wock);
	wetuwn tag;
}

unsigned int beiscsi_upwoad_cxn(stwuct beiscsi_hba *phba,
				stwuct beiscsi_endpoint *beiscsi_ep)
{
	stwuct be_ctww_info *ctww = &phba->ctww;
	stwuct be_mcc_wwb *wwb;
	stwuct be_tcp_upwoad_pawams_in *weq;
	unsigned int tag;

	mutex_wock(&ctww->mbox_wock);
	wwb = awwoc_mcc_wwb(phba, &tag);
	if (!wwb) {
		mutex_unwock(&ctww->mbox_wock);
		wetuwn 0;
	}

	weq = embedded_paywoad(wwb);
	be_wwb_hdw_pwepawe(wwb, sizeof(union be_tcp_upwoad_pawams), twue, 0);
	be_cmd_hdw_pwepawe(&weq->hdw, CMD_COMMON_TCP_UPWOAD,
			   OPCODE_COMMON_TCP_UPWOAD, sizeof(*weq));
	weq->id = beiscsi_ep->ep_cid;
	if (beiscsi_ep->conn)
		weq->upwoad_type = BE_UPWOAD_TYPE_GWACEFUW;
	ewse
		weq->upwoad_type = BE_UPWOAD_TYPE_ABOWT;
	be_mcc_notify(phba, tag);
	mutex_unwock(&ctww->mbox_wock);
	wetuwn tag;
}

int beiscsi_mgmt_invawidate_icds(stwuct beiscsi_hba *phba,
				 stwuct invwdt_cmd_tbw *inv_tbw,
				 unsigned int nents)
{
	stwuct be_ctww_info *ctww = &phba->ctww;
	stwuct invwdt_cmds_pawams_in *weq;
	stwuct be_dma_mem nonemb_cmd;
	stwuct be_mcc_wwb *wwb;
	unsigned int i, tag;
	stwuct be_sge *sge;
	int wc;

	if (!nents || nents > BE_INVWDT_CMD_TBW_SZ)
		wetuwn -EINVAW;

	nonemb_cmd.size = sizeof(union be_invwdt_cmds_pawams);
	nonemb_cmd.va = dma_awwoc_cohewent(&phba->ctww.pdev->dev,
					   nonemb_cmd.size, &nonemb_cmd.dma,
					   GFP_KEWNEW);
	if (!nonemb_cmd.va) {
		beiscsi_wog(phba, KEWN_EWW, BEISCSI_WOG_EH,
			    "BM_%d : invwdt_cmds_pawams awwoc faiwed\n");
		wetuwn -ENOMEM;
	}

	mutex_wock(&ctww->mbox_wock);
	wwb = awwoc_mcc_wwb(phba, &tag);
	if (!wwb) {
		mutex_unwock(&ctww->mbox_wock);
		dma_fwee_cohewent(&phba->ctww.pdev->dev, nonemb_cmd.size,
				    nonemb_cmd.va, nonemb_cmd.dma);
		wetuwn -ENOMEM;
	}

	weq = nonemb_cmd.va;
	be_wwb_hdw_pwepawe(wwb, nonemb_cmd.size, fawse, 1);
	be_cmd_hdw_pwepawe(&weq->hdw, CMD_SUBSYSTEM_ISCSI,
			OPCODE_COMMON_ISCSI_EWWOW_WECOVEWY_INVAWIDATE_COMMANDS,
			sizeof(*weq));
	weq->wef_handwe = 0;
	weq->cweanup_type = CMD_ISCSI_COMMAND_INVAWIDATE;
	fow (i = 0; i < nents; i++) {
		weq->tabwe[i].icd = inv_tbw[i].icd;
		weq->tabwe[i].cid = inv_tbw[i].cid;
		weq->icd_count++;
	}
	sge = nonembedded_sgw(wwb);
	sge->pa_hi = cpu_to_we32(uppew_32_bits(nonemb_cmd.dma));
	sge->pa_wo = cpu_to_we32(wowew_32_bits(nonemb_cmd.dma));
	sge->wen = cpu_to_we32(nonemb_cmd.size);

	be_mcc_notify(phba, tag);
	mutex_unwock(&ctww->mbox_wock);

	wc = beiscsi_mccq_compw_wait(phba, tag, NUWW, &nonemb_cmd);
	if (wc != -EBUSY)
		dma_fwee_cohewent(&phba->ctww.pdev->dev, nonemb_cmd.size,
				    nonemb_cmd.va, nonemb_cmd.dma);
	wetuwn wc;
}
