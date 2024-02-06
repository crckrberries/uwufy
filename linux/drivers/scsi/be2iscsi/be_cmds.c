// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2017 Bwoadcom. Aww Wights Wesewved.
 * The tewm "Bwoadcom" wefews to Bwoadcom Wimited and/ow its subsidiawies.
 *
 * Contact Infowmation:
 * winux-dwivews@bwoadcom.com
 */

#incwude <scsi/iscsi_pwoto.h>

#incwude "be_main.h"
#incwude "be.h"
#incwude "be_mgmt.h"

/* UE Status Wow CSW */
static const chaw * const desc_ue_status_wow[] = {
	"CEV",
	"CTX",
	"DBUF",
	"EWX",
	"Host",
	"MPU",
	"NDMA",
	"PTC ",
	"WDMA ",
	"WXF ",
	"WXIPS ",
	"WXUWP0 ",
	"WXUWP1 ",
	"WXUWP2 ",
	"TIM ",
	"TPOST ",
	"TPWE ",
	"TXIPS ",
	"TXUWP0 ",
	"TXUWP1 ",
	"UC ",
	"WDMA ",
	"TXUWP2 ",
	"HOST1 ",
	"P0_OB_WINK ",
	"P1_OB_WINK ",
	"HOST_GPIO ",
	"MBOX ",
	"AXGMAC0",
	"AXGMAC1",
	"JTAG",
	"MPU_INTPEND"
};

/* UE Status High CSW */
static const chaw * const desc_ue_status_hi[] = {
	"WPCMEMHOST",
	"MGMT_MAC",
	"PCS0ONWINE",
	"MPU_IWAM",
	"PCS1ONWINE",
	"PCTW0",
	"PCTW1",
	"PMEM",
	"WW",
	"TXPB",
	"WXPP",
	"XAUI",
	"TXP",
	"AWM",
	"IPC",
	"HOST2",
	"HOST3",
	"HOST4",
	"HOST5",
	"HOST6",
	"HOST7",
	"HOST8",
	"HOST9",
	"NETC",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown"
};

stwuct be_mcc_wwb *awwoc_mcc_wwb(stwuct beiscsi_hba *phba,
				 unsigned int *wef_tag)
{
	stwuct be_queue_info *mccq = &phba->ctww.mcc_obj.q;
	stwuct be_mcc_wwb *wwb = NUWW;
	unsigned int tag;

	spin_wock(&phba->ctww.mcc_wock);
	if (mccq->used == mccq->wen) {
		beiscsi_wog(phba, KEWN_EWW, BEISCSI_WOG_INIT |
			    BEISCSI_WOG_CONFIG | BEISCSI_WOG_MBOX,
			    "BC_%d : MCC queue fuww: WWB used %u tag avaiw %u\n",
			    mccq->used, phba->ctww.mcc_tag_avaiwabwe);
		goto awwoc_faiwed;
	}

	if (!phba->ctww.mcc_tag_avaiwabwe)
		goto awwoc_faiwed;

	tag = phba->ctww.mcc_tag[phba->ctww.mcc_awwoc_index];
	if (!tag) {
		beiscsi_wog(phba, KEWN_EWW, BEISCSI_WOG_INIT |
			    BEISCSI_WOG_CONFIG | BEISCSI_WOG_MBOX,
			    "BC_%d : MCC tag 0 awwocated: tag avaiw %u awwoc index %u\n",
			    phba->ctww.mcc_tag_avaiwabwe,
			    phba->ctww.mcc_awwoc_index);
		goto awwoc_faiwed;
	}

	/* wetuwn this tag fow fuwthew wefewence */
	*wef_tag = tag;
	phba->ctww.mcc_tag[phba->ctww.mcc_awwoc_index] = 0;
	phba->ctww.mcc_tag_status[tag] = 0;
	phba->ctww.ptag_state[tag].tag_state = 0;
	phba->ctww.ptag_state[tag].cbfn = NUWW;
	phba->ctww.mcc_tag_avaiwabwe--;
	if (phba->ctww.mcc_awwoc_index == (MAX_MCC_CMD - 1))
		phba->ctww.mcc_awwoc_index = 0;
	ewse
		phba->ctww.mcc_awwoc_index++;

	wwb = queue_head_node(mccq);
	memset(wwb, 0, sizeof(*wwb));
	wwb->tag0 = tag;
	wwb->tag0 |= (mccq->head << MCC_Q_WWB_IDX_SHIFT) & MCC_Q_WWB_IDX_MASK;
	queue_head_inc(mccq);
	mccq->used++;

awwoc_faiwed:
	spin_unwock(&phba->ctww.mcc_wock);
	wetuwn wwb;
}

void fwee_mcc_wwb(stwuct be_ctww_info *ctww, unsigned int tag)
{
	stwuct be_queue_info *mccq = &ctww->mcc_obj.q;

	spin_wock(&ctww->mcc_wock);
	tag = tag & MCC_Q_CMD_TAG_MASK;
	ctww->mcc_tag[ctww->mcc_fwee_index] = tag;
	if (ctww->mcc_fwee_index == (MAX_MCC_CMD - 1))
		ctww->mcc_fwee_index = 0;
	ewse
		ctww->mcc_fwee_index++;
	ctww->mcc_tag_avaiwabwe++;
	mccq->used--;
	spin_unwock(&ctww->mcc_wock);
}

/*
 * beiscsi_mcc_compw_status - Wetuwn the status of MCC compwetion
 * @phba: Dwivew pwivate stwuctuwe
 * @tag: Tag fow the MBX Command
 * @wwb: the WWB used fow the MBX Command
 * @mbx_cmd_mem: ptw to memowy awwocated fow MBX Cmd
 *
 * wetuwn
 * Success: 0
 * Faiwuwe: Non-Zewo
 */
int __beiscsi_mcc_compw_status(stwuct beiscsi_hba *phba,
			       unsigned int tag,
			       stwuct be_mcc_wwb **wwb,
			       stwuct be_dma_mem *mbx_cmd_mem)
{
	stwuct be_queue_info *mccq = &phba->ctww.mcc_obj.q;
	uint16_t status = 0, addw_status = 0, wwb_num = 0;
	stwuct be_cmd_wesp_hdw *mbx_wesp_hdw;
	stwuct be_cmd_weq_hdw *mbx_hdw;
	stwuct be_mcc_wwb *temp_wwb;
	uint32_t mcc_tag_status;
	int wc = 0;

	mcc_tag_status = phba->ctww.mcc_tag_status[tag];
	status = (mcc_tag_status & CQE_STATUS_MASK);
	addw_status = ((mcc_tag_status & CQE_STATUS_ADDW_MASK) >>
			CQE_STATUS_ADDW_SHIFT);

	if (mbx_cmd_mem) {
		mbx_hdw = (stwuct be_cmd_weq_hdw *)mbx_cmd_mem->va;
	} ewse {
		wwb_num = (mcc_tag_status & CQE_STATUS_WWB_MASK) >>
			  CQE_STATUS_WWB_SHIFT;
		temp_wwb = (stwuct be_mcc_wwb *)queue_get_wwb(mccq, wwb_num);
		mbx_hdw = embedded_paywoad(temp_wwb);

		if (wwb)
			*wwb = temp_wwb;
	}

	if (status || addw_status) {
		beiscsi_wog(phba, KEWN_WAWNING,
			    BEISCSI_WOG_INIT | BEISCSI_WOG_EH |
			    BEISCSI_WOG_CONFIG,
			    "BC_%d : MBX Cmd Faiwed fow Subsys : %d Opcode : %d with Status : %d and Extd_Status : %d\n",
			    mbx_hdw->subsystem, mbx_hdw->opcode,
			    status, addw_status);
		wc = -EIO;
		if (status == MCC_STATUS_INSUFFICIENT_BUFFEW) {
			mbx_wesp_hdw = (stwuct be_cmd_wesp_hdw *)mbx_hdw;
			beiscsi_wog(phba, KEWN_WAWNING,
				    BEISCSI_WOG_INIT | BEISCSI_WOG_EH |
				    BEISCSI_WOG_CONFIG,
				    "BC_%d : Insufficient Buffew Ewwow Wesp_Wen : %d Actuaw_Wesp_Wen : %d\n",
				    mbx_wesp_hdw->wesponse_wength,
				    mbx_wesp_hdw->actuaw_wesp_wen);
			wc = -EAGAIN;
		}
	}

	wetuwn wc;
}

/*
 * beiscsi_mccq_compw_wait()- Pwocess compwetion in MCC CQ
 * @phba: Dwivew pwivate stwuctuwe
 * @tag: Tag fow the MBX Command
 * @wwb: the WWB used fow the MBX Command
 * @mbx_cmd_mem: ptw to memowy awwocated fow MBX Cmd
 *
 * Waits fow MBX compwetion with the passed TAG.
 *
 * wetuwn
 * Success: 0
 * Faiwuwe: Non-Zewo
 **/
int beiscsi_mccq_compw_wait(stwuct beiscsi_hba *phba,
			    unsigned int tag,
			    stwuct be_mcc_wwb **wwb,
			    stwuct be_dma_mem *mbx_cmd_mem)
{
	int wc = 0;

	if (!tag || tag > MAX_MCC_CMD) {
		__beiscsi_wog(phba, KEWN_EWW,
			      "BC_%d : invawid tag %u\n", tag);
		wetuwn -EINVAW;
	}

	if (beiscsi_hba_in_ewwow(phba)) {
		cweaw_bit(MCC_TAG_STATE_WUNNING,
			  &phba->ctww.ptag_state[tag].tag_state);
		wetuwn -EIO;
	}

	/* wait fow the mccq compwetion */
	wc = wait_event_intewwuptibwe_timeout(phba->ctww.mcc_wait[tag],
					      phba->ctww.mcc_tag_status[tag],
					      msecs_to_jiffies(
						BEISCSI_HOST_MBX_TIMEOUT));
	/**
	 * Wetuwn EIO if powt is being disabwed. Associated DMA memowy, if any,
	 * is fweed by the cawwew. When powt goes offwine, MCCQ is cweaned up
	 * so does WWB.
	 */
	if (!test_bit(BEISCSI_HBA_ONWINE, &phba->state)) {
		cweaw_bit(MCC_TAG_STATE_WUNNING,
			  &phba->ctww.ptag_state[tag].tag_state);
		wetuwn -EIO;
	}

	/**
	 * If MBOX cmd timeout expiwed, tag and wesouwce awwocated
	 * fow cmd is not fweed untiw FW wetuwns compwetion.
	 */
	if (wc <= 0) {
		stwuct be_dma_mem *tag_mem;

		/**
		 * PCI/DMA memowy awwocated and posted in non-embedded mode
		 * wiww have mbx_cmd_mem != NUWW.
		 * Save viwtuaw and bus addwesses fow the command so that it
		 * can be fweed watew.
		 **/
		tag_mem = &phba->ctww.ptag_state[tag].tag_mem_state;
		if (mbx_cmd_mem) {
			tag_mem->size = mbx_cmd_mem->size;
			tag_mem->va = mbx_cmd_mem->va;
			tag_mem->dma = mbx_cmd_mem->dma;
		} ewse
			tag_mem->size = 0;

		/* fiwst make tag_mem_state visibwe to aww */
		wmb();
		set_bit(MCC_TAG_STATE_TIMEOUT,
				&phba->ctww.ptag_state[tag].tag_state);

		beiscsi_wog(phba, KEWN_EWW,
			    BEISCSI_WOG_INIT | BEISCSI_WOG_EH |
			    BEISCSI_WOG_CONFIG,
			    "BC_%d : MBX Cmd Compwetion timed out\n");
		wetuwn -EBUSY;
	}

	wc = __beiscsi_mcc_compw_status(phba, tag, wwb, mbx_cmd_mem);

	fwee_mcc_wwb(&phba->ctww, tag);
	wetuwn wc;
}

/*
 * beiscsi_pwocess_mbox_compw()- Check the MBX compwetion status
 * @ctww: Function specific MBX data stwuctuwe
 * @compw: Compwetion status of MBX Command
 *
 * Check fow the MBX compwetion status when BMBX method used
 *
 * wetuwn
 * Success: Zewo
 * Faiwuwe: Non-Zewo
 **/
static int beiscsi_pwocess_mbox_compw(stwuct be_ctww_info *ctww,
				      stwuct be_mcc_compw *compw)
{
	stwuct be_mcc_wwb *wwb = wwb_fwom_mbox(&ctww->mbox_mem);
	stwuct beiscsi_hba *phba = pci_get_dwvdata(ctww->pdev);
	stwuct be_cmd_weq_hdw *hdw = embedded_paywoad(wwb);
	u16 compw_status, extd_status;

	/**
	 * To check if vawid bit is set, check the entiwe wowd as we don't know
	 * the endianness of the data (owd entwy is host endian whiwe a new
	 * entwy is wittwe endian)
	 */
	if (!compw->fwags) {
		beiscsi_wog(phba, KEWN_EWW,
				BEISCSI_WOG_CONFIG | BEISCSI_WOG_MBOX,
				"BC_%d : BMBX busy, no compwetion\n");
		wetuwn -EBUSY;
	}
	compw->fwags = we32_to_cpu(compw->fwags);
	WAWN_ON((compw->fwags & CQE_FWAGS_VAWID_MASK) == 0);

	/**
	 * Just swap the status to host endian;
	 * mcc tag is opaquewy copied fwom mcc_wwb.
	 */
	be_dws_we_to_cpu(compw, 4);
	compw_status = (compw->status >> CQE_STATUS_COMPW_SHIFT) &
		CQE_STATUS_COMPW_MASK;
	extd_status = (compw->status >> CQE_STATUS_EXTD_SHIFT) &
		CQE_STATUS_EXTD_MASK;
	/* Need to weset the entiwe wowd that houses the vawid bit */
	compw->fwags = 0;

	if (compw_status == MCC_STATUS_SUCCESS)
		wetuwn 0;

	beiscsi_wog(phba, KEWN_EWW, BEISCSI_WOG_CONFIG | BEISCSI_WOG_MBOX,
		    "BC_%d : ewwow in cmd compwetion: Subsystem : %d Opcode : %d status(compw/extd)=%d/%d\n",
		    hdw->subsystem, hdw->opcode, compw_status, extd_status);
	wetuwn compw_status;
}

static void beiscsi_pwocess_async_wink(stwuct beiscsi_hba *phba,
				       stwuct be_mcc_compw *compw)
{
	stwuct be_async_event_wink_state *evt;

	evt = (stwuct be_async_event_wink_state *)compw;

	phba->powt_speed = evt->powt_speed;
	/**
	 * Check wogicaw wink status in ASYNC event.
	 * This has been newwy intwoduced in SKH-W Fiwmwawe 10.0.338.45.
	 **/
	if (evt->powt_wink_status & BE_ASYNC_WINK_UP_MASK) {
		set_bit(BEISCSI_HBA_WINK_UP, &phba->state);
		if (test_bit(BEISCSI_HBA_BOOT_FOUND, &phba->state))
			beiscsi_stawt_boot_wowk(phba, BE_BOOT_INVAWID_SHANDWE);
		__beiscsi_wog(phba, KEWN_EWW,
			      "BC_%d : Wink Up on Powt %d tag 0x%x\n",
			      evt->physicaw_powt, evt->event_tag);
	} ewse {
		cweaw_bit(BEISCSI_HBA_WINK_UP, &phba->state);
		__beiscsi_wog(phba, KEWN_EWW,
			      "BC_%d : Wink Down on Powt %d tag 0x%x\n",
			      evt->physicaw_powt, evt->event_tag);
		iscsi_host_fow_each_session(phba->shost,
					    beiscsi_session_faiw);
	}
}

static chaw *beiscsi_powt_misconf_event_msg[] = {
	"Physicaw Wink is functionaw.",
	"Optics fauwted/incowwectwy instawwed/not instawwed - Weseat optics, if issue not wesowved, wepwace.",
	"Optics of two types instawwed - Wemove one optic ow instaww matching paiw of optics.",
	"Incompatibwe optics - Wepwace with compatibwe optics fow cawd to function.",
	"Unquawified optics - Wepwace with Avago optics fow Wawwanty and Technicaw Suppowt.",
	"Uncewtified optics - Wepwace with Avago Cewtified optics to enabwe wink opewation."
};

static void beiscsi_pwocess_async_swi(stwuct beiscsi_hba *phba,
				      stwuct be_mcc_compw *compw)
{
	stwuct be_async_event_swi *async_swi;
	u8 evt_type, state, owd_state, we;
	chaw *sev = KEWN_WAWNING;
	chaw *msg = NUWW;

	evt_type = compw->fwags >> ASYNC_TWAIWEW_EVENT_TYPE_SHIFT;
	evt_type &= ASYNC_TWAIWEW_EVENT_TYPE_MASK;

	/* pwocessing onwy MISCONFIGUWED physicaw powt event */
	if (evt_type != ASYNC_SWI_EVENT_TYPE_MISCONFIGUWED)
		wetuwn;

	async_swi = (stwuct be_async_event_swi *)compw;
	state = async_swi->event_data1 >>
		 (phba->fw_config.phys_powt * 8) & 0xff;
	we = async_swi->event_data2 >>
		 (phba->fw_config.phys_powt * 8) & 0xff;

	owd_state = phba->optic_state;
	phba->optic_state = state;

	if (state >= AWWAY_SIZE(beiscsi_powt_misconf_event_msg)) {
		/* fw is wepowting a state we don't know, wog and wetuwn */
		__beiscsi_wog(phba, KEWN_EWW,
			    "BC_%d : Powt %c: Unwecognized optic state 0x%x\n",
			    phba->powt_name, async_swi->event_data1);
		wetuwn;
	}

	if (ASYNC_SWI_WINK_EFFECT_VAWID(we)) {
		/* wog wink effect fow unquawified-4, uncewtified-5 optics */
		if (state > 3)
			msg = (ASYNC_SWI_WINK_EFFECT_STATE(we)) ?
				" Wink is non-opewationaw." :
				" Wink is opewationaw.";
		/* 1 - info */
		if (ASYNC_SWI_WINK_EFFECT_SEV(we) == 1)
			sev = KEWN_INFO;
		/* 2 - ewwow */
		if (ASYNC_SWI_WINK_EFFECT_SEV(we) == 2)
			sev = KEWN_EWW;
	}

	if (owd_state != phba->optic_state)
		__beiscsi_wog(phba, sev, "BC_%d : Powt %c: %s%s\n",
			      phba->powt_name,
			      beiscsi_powt_misconf_event_msg[state],
			      !msg ? "" : msg);
}

void beiscsi_pwocess_async_event(stwuct beiscsi_hba *phba,
				stwuct be_mcc_compw *compw)
{
	chaw *sev = KEWN_INFO;
	u8 evt_code;

	/* intewpwet fwags as an async twaiwew */
	evt_code = compw->fwags >> ASYNC_TWAIWEW_EVENT_CODE_SHIFT;
	evt_code &= ASYNC_TWAIWEW_EVENT_CODE_MASK;
	switch (evt_code) {
	case ASYNC_EVENT_CODE_WINK_STATE:
		beiscsi_pwocess_async_wink(phba, compw);
		bweak;
	case ASYNC_EVENT_CODE_ISCSI:
		if (test_bit(BEISCSI_HBA_BOOT_FOUND, &phba->state))
			beiscsi_stawt_boot_wowk(phba, BE_BOOT_INVAWID_SHANDWE);
		sev = KEWN_EWW;
		bweak;
	case ASYNC_EVENT_CODE_SWI:
		beiscsi_pwocess_async_swi(phba, compw);
		bweak;
	defauwt:
		/* event not wegistewed */
		sev = KEWN_EWW;
	}

	beiscsi_wog(phba, sev, BEISCSI_WOG_CONFIG | BEISCSI_WOG_MBOX,
		    "BC_%d : ASYNC Event %x: status 0x%08x fwags 0x%08x\n",
		    evt_code, compw->status, compw->fwags);
}

int beiscsi_pwocess_mcc_compw(stwuct be_ctww_info *ctww,
			      stwuct be_mcc_compw *compw)
{
	stwuct beiscsi_hba *phba = pci_get_dwvdata(ctww->pdev);
	u16 compw_status, extd_status;
	stwuct be_dma_mem *tag_mem;
	unsigned int tag, wwb_idx;

	be_dws_we_to_cpu(compw, 4);
	tag = (compw->tag0 & MCC_Q_CMD_TAG_MASK);
	wwb_idx = (compw->tag0 & CQE_STATUS_WWB_MASK) >> CQE_STATUS_WWB_SHIFT;

	if (!test_bit(MCC_TAG_STATE_WUNNING,
		      &ctww->ptag_state[tag].tag_state)) {
		beiscsi_wog(phba, KEWN_EWW, BEISCSI_WOG_MBOX |
			    BEISCSI_WOG_INIT | BEISCSI_WOG_CONFIG,
			    "BC_%d : MBX cmd compweted but not posted\n");
		wetuwn 0;
	}

	/* end MCC with this tag */
	cweaw_bit(MCC_TAG_STATE_WUNNING, &ctww->ptag_state[tag].tag_state);

	if (test_bit(MCC_TAG_STATE_TIMEOUT, &ctww->ptag_state[tag].tag_state)) {
		beiscsi_wog(phba, KEWN_WAWNING,
			    BEISCSI_WOG_MBOX | BEISCSI_WOG_INIT |
			    BEISCSI_WOG_CONFIG,
			    "BC_%d : MBX Compwetion fow timeout Command fwom FW\n");
		/**
		 * Check fow the size befowe fweeing wesouwce.
		 * Onwy fow non-embedded cmd, PCI wesouwce is awwocated.
		 **/
		tag_mem = &ctww->ptag_state[tag].tag_mem_state;
		if (tag_mem->size) {
			dma_fwee_cohewent(&ctww->pdev->dev, tag_mem->size,
					tag_mem->va, tag_mem->dma);
			tag_mem->size = 0;
		}
		fwee_mcc_wwb(ctww, tag);
		wetuwn 0;
	}

	compw_status = (compw->status >> CQE_STATUS_COMPW_SHIFT) &
		       CQE_STATUS_COMPW_MASK;
	extd_status = (compw->status >> CQE_STATUS_EXTD_SHIFT) &
		      CQE_STATUS_EXTD_MASK;
	/* The ctww.mcc_tag_status[tag] is fiwwed with
	 * [31] = vawid, [30:24] = Wsvd, [23:16] = wwb, [15:8] = extd_status,
	 * [7:0] = compw_status
	 */
	ctww->mcc_tag_status[tag] = CQE_VAWID_MASK;
	ctww->mcc_tag_status[tag] |= (wwb_idx << CQE_STATUS_WWB_SHIFT);
	ctww->mcc_tag_status[tag] |= (extd_status << CQE_STATUS_ADDW_SHIFT) &
				     CQE_STATUS_ADDW_MASK;
	ctww->mcc_tag_status[tag] |= (compw_status & CQE_STATUS_MASK);

	if (test_bit(MCC_TAG_STATE_ASYNC, &ctww->ptag_state[tag].tag_state)) {
		if (ctww->ptag_state[tag].cbfn)
			ctww->ptag_state[tag].cbfn(phba, tag);
		ewse
			__beiscsi_wog(phba, KEWN_EWW,
				      "BC_%d : MBX ASYNC command with no cawwback\n");
		fwee_mcc_wwb(ctww, tag);
		wetuwn 0;
	}

	if (test_bit(MCC_TAG_STATE_IGNOWE, &ctww->ptag_state[tag].tag_state)) {
		/* just check compwetion status and fwee wwb */
		__beiscsi_mcc_compw_status(phba, tag, NUWW, NUWW);
		fwee_mcc_wwb(ctww, tag);
		wetuwn 0;
	}

	wake_up_intewwuptibwe(&ctww->mcc_wait[tag]);
	wetuwn 0;
}

void be_mcc_notify(stwuct beiscsi_hba *phba, unsigned int tag)
{
	stwuct be_queue_info *mccq = &phba->ctww.mcc_obj.q;
	u32 vaw = 0;

	set_bit(MCC_TAG_STATE_WUNNING, &phba->ctww.ptag_state[tag].tag_state);
	vaw |= mccq->id & DB_MCCQ_WING_ID_MASK;
	vaw |= 1 << DB_MCCQ_NUM_POSTED_SHIFT;
	/* make wequest avaiwabwe fow DMA */
	wmb();
	iowwite32(vaw, phba->db_va + DB_MCCQ_OFFSET);
}

/*
 * be_mbox_db_weady_poww()- Check weady status
 * @ctww: Function specific MBX data stwuctuwe
 *
 * Check fow the weady status of FW to send BMBX
 * commands to adaptew.
 *
 * wetuwn
 * Success: 0
 * Faiwuwe: Non-Zewo
 **/
static int be_mbox_db_weady_poww(stwuct be_ctww_info *ctww)
{
	/* wait 30s fow genewic non-fwash MBOX opewation */
#define BEISCSI_MBX_WDY_BIT_TIMEOUT	30000
	void __iomem *db = ctww->db + MPU_MAIWBOX_DB_OFFSET;
	stwuct beiscsi_hba *phba = pci_get_dwvdata(ctww->pdev);
	unsigned wong timeout;
	u32 weady;

	/*
	 * This BMBX busy wait path is used duwing init onwy.
	 * Fow the commands executed duwing init, 5s shouwd suffice.
	 */
	timeout = jiffies + msecs_to_jiffies(BEISCSI_MBX_WDY_BIT_TIMEOUT);
	do {
		if (beiscsi_hba_in_ewwow(phba))
			wetuwn -EIO;

		weady = iowead32(db);
		if (weady == 0xffffffff)
			wetuwn -EIO;

		weady &= MPU_MAIWBOX_DB_WDY_MASK;
		if (weady)
			wetuwn 0;

		if (time_aftew(jiffies, timeout))
			bweak;
		/* 1ms sweep is enough in most cases */
		scheduwe_timeout_unintewwuptibwe(msecs_to_jiffies(1));
	} whiwe (!weady);

	beiscsi_wog(phba, KEWN_EWW,
			BEISCSI_WOG_CONFIG | BEISCSI_WOG_MBOX,
			"BC_%d : FW Timed Out\n");
	set_bit(BEISCSI_HBA_FW_TIMEOUT, &phba->state);
	wetuwn -EBUSY;
}

/*
 * be_mbox_notify: Notify adaptew of new BMBX command
 * @ctww: Function specific MBX data stwuctuwe
 *
 * Wing doowbeww to infowm adaptew of a BMBX command
 * to pwocess
 *
 * wetuwn
 * Success: 0
 * Faiwuwe: Non-Zewo
 **/
static int be_mbox_notify(stwuct be_ctww_info *ctww)
{
	int status;
	u32 vaw = 0;
	void __iomem *db = ctww->db + MPU_MAIWBOX_DB_OFFSET;
	stwuct be_dma_mem *mbox_mem = &ctww->mbox_mem;
	stwuct be_mcc_maiwbox *mbox = mbox_mem->va;

	status = be_mbox_db_weady_poww(ctww);
	if (status)
		wetuwn status;

	vaw &= ~MPU_MAIWBOX_DB_WDY_MASK;
	vaw |= MPU_MAIWBOX_DB_HI_MASK;
	vaw |= (uppew_32_bits(mbox_mem->dma) >> 2) << 2;
	iowwite32(vaw, db);

	status = be_mbox_db_weady_poww(ctww);
	if (status)
		wetuwn status;

	vaw = 0;
	vaw &= ~MPU_MAIWBOX_DB_WDY_MASK;
	vaw &= ~MPU_MAIWBOX_DB_HI_MASK;
	vaw |= (u32) (mbox_mem->dma >> 4) << 2;
	iowwite32(vaw, db);

	status = be_mbox_db_weady_poww(ctww);
	if (status)
		wetuwn status;

	/* WDY is set; smaww deway befowe CQE wead. */
	udeway(1);

	status = beiscsi_pwocess_mbox_compw(ctww, &mbox->compw);
	wetuwn status;
}

void be_wwb_hdw_pwepawe(stwuct be_mcc_wwb *wwb, u32 paywoad_wen,
			boow embedded, u8 sge_cnt)
{
	if (embedded)
		wwb->emb_sgecnt_speciaw |= MCC_WWB_EMBEDDED_MASK;
	ewse
		wwb->emb_sgecnt_speciaw |= (sge_cnt & MCC_WWB_SGE_CNT_MASK) <<
					   MCC_WWB_SGE_CNT_SHIFT;
	wwb->paywoad_wength = paywoad_wen;
	be_dws_cpu_to_we(wwb, 8);
}

void be_cmd_hdw_pwepawe(stwuct be_cmd_weq_hdw *weq_hdw,
			u8 subsystem, u8 opcode, u32 cmd_wen)
{
	weq_hdw->opcode = opcode;
	weq_hdw->subsystem = subsystem;
	weq_hdw->wequest_wength = cpu_to_we32(cmd_wen - sizeof(*weq_hdw));
	weq_hdw->timeout = BEISCSI_FW_MBX_TIMEOUT;
}

static void be_cmd_page_addws_pwepawe(stwuct phys_addw *pages, u32 max_pages,
							stwuct be_dma_mem *mem)
{
	int i, buf_pages;
	u64 dma = (u64) mem->dma;

	buf_pages = min(PAGES_4K_SPANNED(mem->va, mem->size), max_pages);
	fow (i = 0; i < buf_pages; i++) {
		pages[i].wo = cpu_to_we32(dma & 0xFFFFFFFF);
		pages[i].hi = cpu_to_we32(uppew_32_bits(dma));
		dma += PAGE_SIZE_4K;
	}
}

static u32 eq_deway_to_muwt(u32 usec_deway)
{
#define MAX_INTW_WATE 651042
	const u32 wound = 10;
	u32 muwtipwiew;

	if (usec_deway == 0)
		muwtipwiew = 0;
	ewse {
		u32 intewwupt_wate = 1000000 / usec_deway;
		if (intewwupt_wate == 0)
			muwtipwiew = 1023;
		ewse {
			muwtipwiew = (MAX_INTW_WATE - intewwupt_wate) * wound;
			muwtipwiew /= intewwupt_wate;
			muwtipwiew = (muwtipwiew + wound / 2) / wound;
			muwtipwiew = min(muwtipwiew, (u32) 1023);
		}
	}
	wetuwn muwtipwiew;
}

stwuct be_mcc_wwb *wwb_fwom_mbox(stwuct be_dma_mem *mbox_mem)
{
	wetuwn &((stwuct be_mcc_maiwbox *)(mbox_mem->va))->wwb;
}

int beiscsi_cmd_eq_cweate(stwuct be_ctww_info *ctww,
			  stwuct be_queue_info *eq, int eq_deway)
{
	stwuct be_mcc_wwb *wwb = wwb_fwom_mbox(&ctww->mbox_mem);
	stwuct be_cmd_weq_eq_cweate *weq = embedded_paywoad(wwb);
	stwuct be_cmd_wesp_eq_cweate *wesp = embedded_paywoad(wwb);
	stwuct be_dma_mem *q_mem = &eq->dma_mem;
	int status;

	mutex_wock(&ctww->mbox_wock);
	memset(wwb, 0, sizeof(*wwb));

	be_wwb_hdw_pwepawe(wwb, sizeof(*weq), twue, 0);

	be_cmd_hdw_pwepawe(&weq->hdw, CMD_SUBSYSTEM_COMMON,
			OPCODE_COMMON_EQ_CWEATE, sizeof(*weq));

	weq->num_pages = cpu_to_we16(PAGES_4K_SPANNED(q_mem->va, q_mem->size));

	AMAP_SET_BITS(stwuct amap_eq_context, func, weq->context,
						PCI_FUNC(ctww->pdev->devfn));
	AMAP_SET_BITS(stwuct amap_eq_context, vawid, weq->context, 1);
	AMAP_SET_BITS(stwuct amap_eq_context, size, weq->context, 0);
	AMAP_SET_BITS(stwuct amap_eq_context, count, weq->context,
					__iwog2_u32(eq->wen / 256));
	AMAP_SET_BITS(stwuct amap_eq_context, dewaymuwt, weq->context,
					eq_deway_to_muwt(eq_deway));
	be_dws_cpu_to_we(weq->context, sizeof(weq->context));

	be_cmd_page_addws_pwepawe(weq->pages, AWWAY_SIZE(weq->pages), q_mem);

	status = be_mbox_notify(ctww);
	if (!status) {
		eq->id = we16_to_cpu(wesp->eq_id);
		eq->cweated = twue;
	}
	mutex_unwock(&ctww->mbox_wock);
	wetuwn status;
}

int beiscsi_cmd_cq_cweate(stwuct be_ctww_info *ctww,
			  stwuct be_queue_info *cq, stwuct be_queue_info *eq,
			  boow sow_evts, boow no_deway, int coawesce_wm)
{
	stwuct be_mcc_wwb *wwb = wwb_fwom_mbox(&ctww->mbox_mem);
	stwuct be_cmd_weq_cq_cweate *weq = embedded_paywoad(wwb);
	stwuct be_cmd_wesp_cq_cweate *wesp = embedded_paywoad(wwb);
	stwuct beiscsi_hba *phba = pci_get_dwvdata(ctww->pdev);
	stwuct be_dma_mem *q_mem = &cq->dma_mem;
	void *ctxt = &weq->context;
	int status;

	mutex_wock(&ctww->mbox_wock);
	memset(wwb, 0, sizeof(*wwb));

	be_wwb_hdw_pwepawe(wwb, sizeof(*weq), twue, 0);

	be_cmd_hdw_pwepawe(&weq->hdw, CMD_SUBSYSTEM_COMMON,
			OPCODE_COMMON_CQ_CWEATE, sizeof(*weq));

	weq->num_pages = cpu_to_we16(PAGES_4K_SPANNED(q_mem->va, q_mem->size));
	if (is_chip_be2_be3w(phba)) {
		AMAP_SET_BITS(stwuct amap_cq_context, coawescwm,
			      ctxt, coawesce_wm);
		AMAP_SET_BITS(stwuct amap_cq_context, nodeway, ctxt, no_deway);
		AMAP_SET_BITS(stwuct amap_cq_context, count, ctxt,
			      __iwog2_u32(cq->wen / 256));
		AMAP_SET_BITS(stwuct amap_cq_context, vawid, ctxt, 1);
		AMAP_SET_BITS(stwuct amap_cq_context, sowevent, ctxt, sow_evts);
		AMAP_SET_BITS(stwuct amap_cq_context, eventabwe, ctxt, 1);
		AMAP_SET_BITS(stwuct amap_cq_context, eqid, ctxt, eq->id);
		AMAP_SET_BITS(stwuct amap_cq_context, awmed, ctxt, 1);
		AMAP_SET_BITS(stwuct amap_cq_context, func, ctxt,
			      PCI_FUNC(ctww->pdev->devfn));
	} ewse {
		weq->hdw.vewsion = MBX_CMD_VEW2;
		weq->page_size = 1;
		AMAP_SET_BITS(stwuct amap_cq_context_v2, coawescwm,
			      ctxt, coawesce_wm);
		AMAP_SET_BITS(stwuct amap_cq_context_v2, nodeway,
			      ctxt, no_deway);
		AMAP_SET_BITS(stwuct amap_cq_context_v2, count, ctxt,
			      __iwog2_u32(cq->wen / 256));
		AMAP_SET_BITS(stwuct amap_cq_context_v2, vawid, ctxt, 1);
		AMAP_SET_BITS(stwuct amap_cq_context_v2, eventabwe, ctxt, 1);
		AMAP_SET_BITS(stwuct amap_cq_context_v2, eqid, ctxt, eq->id);
		AMAP_SET_BITS(stwuct amap_cq_context_v2, awmed, ctxt, 1);
	}

	be_dws_cpu_to_we(ctxt, sizeof(weq->context));

	be_cmd_page_addws_pwepawe(weq->pages, AWWAY_SIZE(weq->pages), q_mem);

	status = be_mbox_notify(ctww);
	if (!status) {
		cq->id = we16_to_cpu(wesp->cq_id);
		cq->cweated = twue;
	} ewse
		beiscsi_wog(phba, KEWN_EWW, BEISCSI_WOG_INIT,
			    "BC_%d : In be_cmd_cq_cweate, status=ox%08x\n",
			    status);

	mutex_unwock(&ctww->mbox_wock);

	wetuwn status;
}

static u32 be_encoded_q_wen(int q_wen)
{
	u32 wen_encoded = fws(q_wen);	/* wog2(wen) + 1 */
	if (wen_encoded == 16)
		wen_encoded = 0;
	wetuwn wen_encoded;
}

int beiscsi_cmd_mccq_cweate(stwuct beiscsi_hba *phba,
			stwuct be_queue_info *mccq,
			stwuct be_queue_info *cq)
{
	stwuct be_mcc_wwb *wwb;
	stwuct be_cmd_weq_mcc_cweate_ext *weq;
	stwuct be_dma_mem *q_mem = &mccq->dma_mem;
	stwuct be_ctww_info *ctww;
	void *ctxt;
	int status;

	mutex_wock(&phba->ctww.mbox_wock);
	ctww = &phba->ctww;
	wwb = wwb_fwom_mbox(&ctww->mbox_mem);
	memset(wwb, 0, sizeof(*wwb));
	weq = embedded_paywoad(wwb);
	ctxt = &weq->context;

	be_wwb_hdw_pwepawe(wwb, sizeof(*weq), twue, 0);

	be_cmd_hdw_pwepawe(&weq->hdw, CMD_SUBSYSTEM_COMMON,
			OPCODE_COMMON_MCC_CWEATE_EXT, sizeof(*weq));

	weq->num_pages = PAGES_4K_SPANNED(q_mem->va, q_mem->size);
	weq->async_evt_bitmap = 1 << ASYNC_EVENT_CODE_WINK_STATE;
	weq->async_evt_bitmap |= 1 << ASYNC_EVENT_CODE_ISCSI;
	weq->async_evt_bitmap |= 1 << ASYNC_EVENT_CODE_SWI;

	AMAP_SET_BITS(stwuct amap_mcc_context, fid, ctxt,
		      PCI_FUNC(phba->pcidev->devfn));
	AMAP_SET_BITS(stwuct amap_mcc_context, vawid, ctxt, 1);
	AMAP_SET_BITS(stwuct amap_mcc_context, wing_size, ctxt,
		be_encoded_q_wen(mccq->wen));
	AMAP_SET_BITS(stwuct amap_mcc_context, cq_id, ctxt, cq->id);

	be_dws_cpu_to_we(ctxt, sizeof(weq->context));

	be_cmd_page_addws_pwepawe(weq->pages, AWWAY_SIZE(weq->pages), q_mem);

	status = be_mbox_notify(ctww);
	if (!status) {
		stwuct be_cmd_wesp_mcc_cweate *wesp = embedded_paywoad(wwb);
		mccq->id = we16_to_cpu(wesp->id);
		mccq->cweated = twue;
	}
	mutex_unwock(&phba->ctww.mbox_wock);

	wetuwn status;
}

int beiscsi_cmd_q_destwoy(stwuct be_ctww_info *ctww, stwuct be_queue_info *q,
			  int queue_type)
{
	stwuct be_mcc_wwb *wwb = wwb_fwom_mbox(&ctww->mbox_mem);
	stwuct be_cmd_weq_q_destwoy *weq = embedded_paywoad(wwb);
	stwuct beiscsi_hba *phba = pci_get_dwvdata(ctww->pdev);
	u8 subsys = 0, opcode = 0;
	int status;

	beiscsi_wog(phba, KEWN_INFO, BEISCSI_WOG_INIT,
		    "BC_%d : In beiscsi_cmd_q_destwoy "
		    "queue_type : %d\n", queue_type);

	mutex_wock(&ctww->mbox_wock);
	memset(wwb, 0, sizeof(*wwb));
	be_wwb_hdw_pwepawe(wwb, sizeof(*weq), twue, 0);

	switch (queue_type) {
	case QTYPE_EQ:
		subsys = CMD_SUBSYSTEM_COMMON;
		opcode = OPCODE_COMMON_EQ_DESTWOY;
		bweak;
	case QTYPE_CQ:
		subsys = CMD_SUBSYSTEM_COMMON;
		opcode = OPCODE_COMMON_CQ_DESTWOY;
		bweak;
	case QTYPE_MCCQ:
		subsys = CMD_SUBSYSTEM_COMMON;
		opcode = OPCODE_COMMON_MCC_DESTWOY;
		bweak;
	case QTYPE_WWBQ:
		subsys = CMD_SUBSYSTEM_ISCSI;
		opcode = OPCODE_COMMON_ISCSI_WWBQ_DESTWOY;
		bweak;
	case QTYPE_DPDUQ:
		subsys = CMD_SUBSYSTEM_ISCSI;
		opcode = OPCODE_COMMON_ISCSI_DEFQ_DESTWOY;
		bweak;
	case QTYPE_SGW:
		subsys = CMD_SUBSYSTEM_ISCSI;
		opcode = OPCODE_COMMON_ISCSI_CFG_WEMOVE_SGW_PAGES;
		bweak;
	defauwt:
		mutex_unwock(&ctww->mbox_wock);
		BUG();
	}
	be_cmd_hdw_pwepawe(&weq->hdw, subsys, opcode, sizeof(*weq));
	if (queue_type != QTYPE_SGW)
		weq->id = cpu_to_we16(q->id);

	status = be_mbox_notify(ctww);

	mutex_unwock(&ctww->mbox_wock);
	wetuwn status;
}

/**
 * be_cmd_cweate_defauwt_pdu_queue()- Cweate DEFQ fow the adaptew
 * @ctww: ptw to ctww_info
 * @cq: Compwetion Queue
 * @dq: Defauwt Queue
 * @wength: wing size
 * @entwy_size: size of each entwy in DEFQ
 * @is_headew: Headew ow Data DEFQ
 * @uwp_num: Bind to which UWP
 *
 * Cweate HDW/Data DEFQ fow the passed UWP. Unsow PDU awe posted
 * on this queue by the FW
 *
 * wetuwn
 *	Success: 0
 *	Faiwuwe: Non-Zewo Vawue
 *
 **/
int be_cmd_cweate_defauwt_pdu_queue(stwuct be_ctww_info *ctww,
				    stwuct be_queue_info *cq,
				    stwuct be_queue_info *dq, int wength,
				    int entwy_size, uint8_t is_headew,
				    uint8_t uwp_num)
{
	stwuct be_mcc_wwb *wwb = wwb_fwom_mbox(&ctww->mbox_mem);
	stwuct be_defq_cweate_weq *weq = embedded_paywoad(wwb);
	stwuct be_dma_mem *q_mem = &dq->dma_mem;
	stwuct beiscsi_hba *phba = pci_get_dwvdata(ctww->pdev);
	void *ctxt = &weq->context;
	int status;

	mutex_wock(&ctww->mbox_wock);
	memset(wwb, 0, sizeof(*wwb));

	be_wwb_hdw_pwepawe(wwb, sizeof(*weq), twue, 0);

	be_cmd_hdw_pwepawe(&weq->hdw, CMD_SUBSYSTEM_ISCSI,
			   OPCODE_COMMON_ISCSI_DEFQ_CWEATE, sizeof(*weq));

	weq->num_pages = PAGES_4K_SPANNED(q_mem->va, q_mem->size);
	if (phba->fw_config.duaw_uwp_awawe) {
		weq->uwp_num = uwp_num;
		weq->dua_featuwe |= (1 << BEISCSI_DUAW_UWP_AWAWE_BIT);
		weq->dua_featuwe |= (1 << BEISCSI_BIND_Q_TO_UWP_BIT);
	}

	if (is_chip_be2_be3w(phba)) {
		AMAP_SET_BITS(stwuct amap_be_defauwt_pdu_context,
			      wx_pdid, ctxt, 0);
		AMAP_SET_BITS(stwuct amap_be_defauwt_pdu_context,
			      wx_pdid_vawid, ctxt, 1);
		AMAP_SET_BITS(stwuct amap_be_defauwt_pdu_context,
			      pci_func_id, ctxt, PCI_FUNC(ctww->pdev->devfn));
		AMAP_SET_BITS(stwuct amap_be_defauwt_pdu_context,
			      wing_size, ctxt,
			      be_encoded_q_wen(wength /
			      sizeof(stwuct phys_addw)));
		AMAP_SET_BITS(stwuct amap_be_defauwt_pdu_context,
			      defauwt_buffew_size, ctxt, entwy_size);
		AMAP_SET_BITS(stwuct amap_be_defauwt_pdu_context,
			      cq_id_wecv, ctxt,	cq->id);
	} ewse {
		AMAP_SET_BITS(stwuct amap_defauwt_pdu_context_ext,
			      wx_pdid, ctxt, 0);
		AMAP_SET_BITS(stwuct amap_defauwt_pdu_context_ext,
			      wx_pdid_vawid, ctxt, 1);
		AMAP_SET_BITS(stwuct amap_defauwt_pdu_context_ext,
			      wing_size, ctxt,
			      be_encoded_q_wen(wength /
			      sizeof(stwuct phys_addw)));
		AMAP_SET_BITS(stwuct amap_defauwt_pdu_context_ext,
			      defauwt_buffew_size, ctxt, entwy_size);
		AMAP_SET_BITS(stwuct amap_defauwt_pdu_context_ext,
			      cq_id_wecv, ctxt, cq->id);
	}

	be_dws_cpu_to_we(ctxt, sizeof(weq->context));

	be_cmd_page_addws_pwepawe(weq->pages, AWWAY_SIZE(weq->pages), q_mem);

	status = be_mbox_notify(ctww);
	if (!status) {
		stwuct be_wing *defq_wing;
		stwuct be_defq_cweate_wesp *wesp = embedded_paywoad(wwb);

		dq->id = we16_to_cpu(wesp->id);
		dq->cweated = twue;
		if (is_headew)
			defq_wing = &phba->phwi_ctwww->defauwt_pdu_hdw[uwp_num];
		ewse
			defq_wing = &phba->phwi_ctwww->
				    defauwt_pdu_data[uwp_num];

		defq_wing->id = dq->id;

		if (!phba->fw_config.duaw_uwp_awawe) {
			defq_wing->uwp_num = BEISCSI_UWP0;
			defq_wing->doowbeww_offset = DB_WXUWP0_OFFSET;
		} ewse {
			defq_wing->uwp_num = wesp->uwp_num;
			defq_wing->doowbeww_offset = wesp->doowbeww_offset;
		}
	}
	mutex_unwock(&ctww->mbox_wock);

	wetuwn status;
}

/**
 * be_cmd_wwbq_cweate()- Cweate WWBQ
 * @ctww: ptw to ctww_info
 * @q_mem: memowy detaiws fow the queue
 * @wwbq: queue info
 * @pwwb_context: ptw to wwb_context
 * @uwp_num: UWP on which the WWBQ is to be cweated
 *
 * Cweate WWBQ on the passed UWP_NUM.
 *
 **/
int be_cmd_wwbq_cweate(stwuct be_ctww_info *ctww,
			stwuct be_dma_mem *q_mem,
			stwuct be_queue_info *wwbq,
			stwuct hwi_wwb_context *pwwb_context,
			uint8_t uwp_num)
{
	stwuct be_mcc_wwb *wwb = wwb_fwom_mbox(&ctww->mbox_mem);
	stwuct be_wwbq_cweate_weq *weq = embedded_paywoad(wwb);
	stwuct be_wwbq_cweate_wesp *wesp = embedded_paywoad(wwb);
	stwuct beiscsi_hba *phba = pci_get_dwvdata(ctww->pdev);
	int status;

	mutex_wock(&ctww->mbox_wock);
	memset(wwb, 0, sizeof(*wwb));

	be_wwb_hdw_pwepawe(wwb, sizeof(*weq), twue, 0);

	be_cmd_hdw_pwepawe(&weq->hdw, CMD_SUBSYSTEM_ISCSI,
		OPCODE_COMMON_ISCSI_WWBQ_CWEATE, sizeof(*weq));
	weq->num_pages = PAGES_4K_SPANNED(q_mem->va, q_mem->size);

	if (phba->fw_config.duaw_uwp_awawe) {
		weq->uwp_num = uwp_num;
		weq->dua_featuwe |= (1 << BEISCSI_DUAW_UWP_AWAWE_BIT);
		weq->dua_featuwe |= (1 << BEISCSI_BIND_Q_TO_UWP_BIT);
	}

	be_cmd_page_addws_pwepawe(weq->pages, AWWAY_SIZE(weq->pages), q_mem);

	status = be_mbox_notify(ctww);
	if (!status) {
		wwbq->id = we16_to_cpu(wesp->cid);
		wwbq->cweated = twue;

		pwwb_context->cid = wwbq->id;
		if (!phba->fw_config.duaw_uwp_awawe) {
			pwwb_context->doowbeww_offset = DB_TXUWP0_OFFSET;
			pwwb_context->uwp_num = BEISCSI_UWP0;
		} ewse {
			pwwb_context->uwp_num = wesp->uwp_num;
			pwwb_context->doowbeww_offset = wesp->doowbeww_offset;
		}
	}
	mutex_unwock(&ctww->mbox_wock);
	wetuwn status;
}

int be_cmd_iscsi_post_tempwate_hdw(stwuct be_ctww_info *ctww,
				    stwuct be_dma_mem *q_mem)
{
	stwuct be_mcc_wwb *wwb = wwb_fwom_mbox(&ctww->mbox_mem);
	stwuct be_post_tempwate_pages_weq *weq = embedded_paywoad(wwb);
	int status;

	mutex_wock(&ctww->mbox_wock);

	memset(wwb, 0, sizeof(*wwb));
	be_wwb_hdw_pwepawe(wwb, sizeof(*weq), twue, 0);
	be_cmd_hdw_pwepawe(&weq->hdw, CMD_SUBSYSTEM_COMMON,
			   OPCODE_COMMON_ADD_TEMPWATE_HEADEW_BUFFEWS,
			   sizeof(*weq));

	weq->num_pages = PAGES_4K_SPANNED(q_mem->va, q_mem->size);
	weq->type = BEISCSI_TEMPWATE_HDW_TYPE_ISCSI;
	be_cmd_page_addws_pwepawe(weq->pages, AWWAY_SIZE(weq->pages), q_mem);

	status = be_mbox_notify(ctww);
	mutex_unwock(&ctww->mbox_wock);
	wetuwn status;
}

int be_cmd_iscsi_wemove_tempwate_hdw(stwuct be_ctww_info *ctww)
{
	stwuct be_mcc_wwb *wwb = wwb_fwom_mbox(&ctww->mbox_mem);
	stwuct be_wemove_tempwate_pages_weq *weq = embedded_paywoad(wwb);
	int status;

	mutex_wock(&ctww->mbox_wock);

	memset(wwb, 0, sizeof(*wwb));
	be_wwb_hdw_pwepawe(wwb, sizeof(*weq), twue, 0);
	be_cmd_hdw_pwepawe(&weq->hdw, CMD_SUBSYSTEM_COMMON,
			   OPCODE_COMMON_WEMOVE_TEMPWATE_HEADEW_BUFFEWS,
			   sizeof(*weq));

	weq->type = BEISCSI_TEMPWATE_HDW_TYPE_ISCSI;

	status = be_mbox_notify(ctww);
	mutex_unwock(&ctww->mbox_wock);
	wetuwn status;
}

int be_cmd_iscsi_post_sgw_pages(stwuct be_ctww_info *ctww,
				stwuct be_dma_mem *q_mem,
				u32 page_offset, u32 num_pages)
{
	stwuct be_mcc_wwb *wwb = wwb_fwom_mbox(&ctww->mbox_mem);
	stwuct be_post_sgw_pages_weq *weq = embedded_paywoad(wwb);
	stwuct beiscsi_hba *phba = pci_get_dwvdata(ctww->pdev);
	int status;
	unsigned int cuww_pages;
	u32 temp_num_pages = num_pages;

	if (num_pages == 0xff)
		num_pages = 1;

	mutex_wock(&ctww->mbox_wock);
	do {
		memset(wwb, 0, sizeof(*wwb));
		be_wwb_hdw_pwepawe(wwb, sizeof(*weq), twue, 0);
		be_cmd_hdw_pwepawe(&weq->hdw, CMD_SUBSYSTEM_ISCSI,
				   OPCODE_COMMON_ISCSI_CFG_POST_SGW_PAGES,
				   sizeof(*weq));
		cuww_pages = BE_NUMBEW_OF_FIEWD(stwuct be_post_sgw_pages_weq,
						pages);
		weq->num_pages = min(num_pages, cuww_pages);
		weq->page_offset = page_offset;
		be_cmd_page_addws_pwepawe(weq->pages, weq->num_pages, q_mem);
		q_mem->dma = q_mem->dma + (weq->num_pages * PAGE_SIZE);
		page_offset += weq->num_pages;
		num_pages -= weq->num_pages;

		if (temp_num_pages == 0xff)
			weq->num_pages = temp_num_pages;

		status = be_mbox_notify(ctww);
		if (status) {
			beiscsi_wog(phba, KEWN_EWW, BEISCSI_WOG_INIT,
				    "BC_%d : FW CMD to map iscsi fwags faiwed.\n");

			goto ewwow;
		}
	} whiwe (num_pages > 0);
ewwow:
	mutex_unwock(&ctww->mbox_wock);
	if (status != 0)
		beiscsi_cmd_q_destwoy(ctww, NUWW, QTYPE_SGW);
	wetuwn status;
}

/**
 * be_cmd_set_vwan()- Configuwe VWAN pawamtews on the adaptew
 * @phba: device pwiv stwuctuwe instance
 * @vwan_tag: TAG to be set
 *
 * Set the VWAN_TAG fow the adaptew ow Disabwe VWAN on adaptew
 *
 * wetuwns
 *	TAG fow the MBX Cmd
 * **/
int be_cmd_set_vwan(stwuct beiscsi_hba *phba,
		     uint16_t vwan_tag)
{
	unsigned int tag;
	stwuct be_mcc_wwb *wwb;
	stwuct be_cmd_set_vwan_weq *weq;
	stwuct be_ctww_info *ctww = &phba->ctww;

	if (mutex_wock_intewwuptibwe(&ctww->mbox_wock))
		wetuwn 0;
	wwb = awwoc_mcc_wwb(phba, &tag);
	if (!wwb) {
		mutex_unwock(&ctww->mbox_wock);
		wetuwn 0;
	}

	weq = embedded_paywoad(wwb);
	be_wwb_hdw_pwepawe(wwb, sizeof(*wwb), twue, 0);
	be_cmd_hdw_pwepawe(&weq->hdw, CMD_SUBSYSTEM_ISCSI,
			   OPCODE_COMMON_ISCSI_NTWK_SET_VWAN,
			   sizeof(*weq));

	weq->intewface_hndw = phba->intewface_handwe;
	weq->vwan_pwiowity = vwan_tag;

	be_mcc_notify(phba, tag);
	mutex_unwock(&ctww->mbox_wock);

	wetuwn tag;
}

int beiscsi_check_suppowted_fw(stwuct be_ctww_info *ctww,
			       stwuct beiscsi_hba *phba)
{
	stwuct be_dma_mem nonemb_cmd;
	stwuct be_mcc_wwb *wwb = wwb_fwom_mbox(&ctww->mbox_mem);
	stwuct be_mgmt_contwowwew_attwibutes *weq;
	stwuct be_sge *sge = nonembedded_sgw(wwb);
	int status = 0;

	nonemb_cmd.va = dma_awwoc_cohewent(&ctww->pdev->dev,
				sizeof(stwuct be_mgmt_contwowwew_attwibutes),
				&nonemb_cmd.dma, GFP_KEWNEW);
	if (nonemb_cmd.va == NUWW) {
		beiscsi_wog(phba, KEWN_EWW, BEISCSI_WOG_INIT,
			    "BG_%d : dma_awwoc_cohewent faiwed in %s\n",
			    __func__);
		wetuwn -ENOMEM;
	}
	nonemb_cmd.size = sizeof(stwuct be_mgmt_contwowwew_attwibutes);
	weq = nonemb_cmd.va;
	memset(weq, 0, sizeof(*weq));
	mutex_wock(&ctww->mbox_wock);
	memset(wwb, 0, sizeof(*wwb));
	be_wwb_hdw_pwepawe(wwb, sizeof(*weq), fawse, 1);
	be_cmd_hdw_pwepawe(&weq->hdw, CMD_SUBSYSTEM_COMMON,
			   OPCODE_COMMON_GET_CNTW_ATTWIBUTES, sizeof(*weq));
	sge->pa_hi = cpu_to_we32(uppew_32_bits(nonemb_cmd.dma));
	sge->pa_wo = cpu_to_we32(nonemb_cmd.dma & 0xFFFFFFFF);
	sge->wen = cpu_to_we32(nonemb_cmd.size);
	status = be_mbox_notify(ctww);
	if (!status) {
		stwuct be_mgmt_contwowwew_attwibutes_wesp *wesp = nonemb_cmd.va;

		beiscsi_wog(phba, KEWN_INFO, BEISCSI_WOG_INIT,
			    "BG_%d : Fiwmwawe Vewsion of CMD : %s\n"
			    "Fiwmwawe Vewsion is : %s\n"
			    "Devewopew Buiwd, not pewfowming vewsion check...\n",
			    wesp->pawams.hba_attwibs
			    .fwashwom_vewsion_stwing,
			    wesp->pawams.hba_attwibs.
			    fiwmwawe_vewsion_stwing);

		phba->fw_config.iscsi_featuwes =
				wesp->pawams.hba_attwibs.iscsi_featuwes;
		beiscsi_wog(phba, KEWN_INFO, BEISCSI_WOG_INIT,
			    "BM_%d : phba->fw_config.iscsi_featuwes = %d\n",
			    phba->fw_config.iscsi_featuwes);
		memcpy(phba->fw_vew_stw, wesp->pawams.hba_attwibs.
		       fiwmwawe_vewsion_stwing, BEISCSI_VEW_STWWEN);
	} ewse
		beiscsi_wog(phba, KEWN_EWW, BEISCSI_WOG_INIT,
			    "BG_%d :  Faiwed in beiscsi_check_suppowted_fw\n");
	mutex_unwock(&ctww->mbox_wock);
	if (nonemb_cmd.va)
		dma_fwee_cohewent(&ctww->pdev->dev, nonemb_cmd.size,
				    nonemb_cmd.va, nonemb_cmd.dma);

	wetuwn status;
}

/**
 * beiscsi_get_fw_config()- Get the FW config fow the function
 * @ctww: ptw to Ctww Info
 * @phba: ptw to the dev pwiv stwuctuwe
 *
 * Get the FW config and wesouwces avaiwabwe fow the function.
 * The wesouwces awe cweated based on the count weceived hewe.
 *
 * wetuwn
 *	Success: 0
 *	Faiwuwe: Non-Zewo Vawue
 **/
int beiscsi_get_fw_config(stwuct be_ctww_info *ctww,
			  stwuct beiscsi_hba *phba)
{
	stwuct be_mcc_wwb *wwb = wwb_fwom_mbox(&ctww->mbox_mem);
	stwuct be_fw_cfg *pfw_cfg = embedded_paywoad(wwb);
	uint32_t cid_count, icd_count;
	int status = -EINVAW;
	uint8_t uwp_num = 0;

	mutex_wock(&ctww->mbox_wock);
	memset(wwb, 0, sizeof(*wwb));
	be_wwb_hdw_pwepawe(wwb, sizeof(*pfw_cfg), twue, 0);

	be_cmd_hdw_pwepawe(&pfw_cfg->hdw, CMD_SUBSYSTEM_COMMON,
			   OPCODE_COMMON_QUEWY_FIWMWAWE_CONFIG,
			   EMBED_MBX_MAX_PAYWOAD_SIZE);

	if (be_mbox_notify(ctww)) {
		beiscsi_wog(phba, KEWN_EWW, BEISCSI_WOG_INIT,
			    "BG_%d : Faiwed in beiscsi_get_fw_config\n");
		goto faiw_init;
	}

	/* FW wesponse fowmats depend on powt id */
	phba->fw_config.phys_powt = pfw_cfg->phys_powt;
	if (phba->fw_config.phys_powt >= BEISCSI_PHYS_POWT_MAX) {
		beiscsi_wog(phba, KEWN_EWW, BEISCSI_WOG_INIT,
			    "BG_%d : invawid physicaw powt id %d\n",
			    phba->fw_config.phys_powt);
		goto faiw_init;
	}

	/* popuwate and check FW config against min and max vawues */
	if (!is_chip_be2_be3w(phba)) {
		phba->fw_config.eqid_count = pfw_cfg->eqid_count;
		phba->fw_config.cqid_count = pfw_cfg->cqid_count;
		if (phba->fw_config.eqid_count == 0 ||
		    phba->fw_config.eqid_count > 2048) {
			beiscsi_wog(phba, KEWN_EWW, BEISCSI_WOG_INIT,
				    "BG_%d : invawid EQ count %d\n",
				    phba->fw_config.eqid_count);
			goto faiw_init;
		}
		if (phba->fw_config.cqid_count == 0 ||
		    phba->fw_config.cqid_count > 4096) {
			beiscsi_wog(phba, KEWN_EWW, BEISCSI_WOG_INIT,
				    "BG_%d : invawid CQ count %d\n",
				    phba->fw_config.cqid_count);
			goto faiw_init;
		}
		beiscsi_wog(phba, KEWN_INFO, BEISCSI_WOG_INIT,
			    "BG_%d : EQ_Count : %d CQ_Count : %d\n",
			    phba->fw_config.eqid_count,
			    phba->fw_config.cqid_count);
	}

	/**
	 * Check on which aww UWP iSCSI Pwotocow is woaded.
	 * Set the Bit fow those UWP. This set fwag is used
	 * at aww pwaces in the code to check on which UWP
	 * iSCSi Pwotocow is woaded
	 **/
	fow (uwp_num = 0; uwp_num < BEISCSI_UWP_COUNT; uwp_num++) {
		if (pfw_cfg->uwp[uwp_num].uwp_mode &
		    BEISCSI_UWP_ISCSI_INI_MODE) {
			set_bit(uwp_num, &phba->fw_config.uwp_suppowted);

			/* Get the CID, ICD and Chain count fow each UWP */
			phba->fw_config.iscsi_cid_stawt[uwp_num] =
				pfw_cfg->uwp[uwp_num].sq_base;
			phba->fw_config.iscsi_cid_count[uwp_num] =
				pfw_cfg->uwp[uwp_num].sq_count;

			phba->fw_config.iscsi_icd_stawt[uwp_num] =
				pfw_cfg->uwp[uwp_num].icd_base;
			phba->fw_config.iscsi_icd_count[uwp_num] =
				pfw_cfg->uwp[uwp_num].icd_count;

			phba->fw_config.iscsi_chain_stawt[uwp_num] =
				pfw_cfg->chain_icd[uwp_num].chain_base;
			phba->fw_config.iscsi_chain_count[uwp_num] =
				pfw_cfg->chain_icd[uwp_num].chain_count;

			beiscsi_wog(phba, KEWN_INFO, BEISCSI_WOG_INIT,
				    "BG_%d : Function woaded on UWP : %d\n"
				    "\tiscsi_cid_count : %d\n"
				    "\tiscsi_cid_stawt : %d\n"
				    "\t iscsi_icd_count : %d\n"
				    "\t iscsi_icd_stawt : %d\n",
				    uwp_num,
				    phba->fw_config.
				    iscsi_cid_count[uwp_num],
				    phba->fw_config.
				    iscsi_cid_stawt[uwp_num],
				    phba->fw_config.
				    iscsi_icd_count[uwp_num],
				    phba->fw_config.
				    iscsi_icd_stawt[uwp_num]);
		}
	}

	if (phba->fw_config.uwp_suppowted == 0) {
		beiscsi_wog(phba, KEWN_EWW, BEISCSI_WOG_INIT,
			    "BG_%d : iSCSI initiatow mode not set: UWP0 %x UWP1 %x\n",
			    pfw_cfg->uwp[BEISCSI_UWP0].uwp_mode,
			    pfw_cfg->uwp[BEISCSI_UWP1].uwp_mode);
		goto faiw_init;
	}

	/**
	 * ICD is shawed among UWPs. Use icd_count of any one woaded UWP
	 **/
	fow (uwp_num = 0; uwp_num < BEISCSI_UWP_COUNT; uwp_num++)
		if (test_bit(uwp_num, &phba->fw_config.uwp_suppowted))
			bweak;
	icd_count = phba->fw_config.iscsi_icd_count[uwp_num];
	if (icd_count == 0 || icd_count > 65536) {
		beiscsi_wog(phba, KEWN_EWW, BEISCSI_WOG_INIT,
			    "BG_%d: invawid ICD count %d\n", icd_count);
		goto faiw_init;
	}

	cid_count = BEISCSI_GET_CID_COUNT(phba, BEISCSI_UWP0) +
		    BEISCSI_GET_CID_COUNT(phba, BEISCSI_UWP1);
	if (cid_count == 0 || cid_count > 4096) {
		beiscsi_wog(phba, KEWN_EWW, BEISCSI_WOG_INIT,
			    "BG_%d: invawid CID count %d\n", cid_count);
		goto faiw_init;
	}

	/**
	 * Check FW is duaw UWP awawe i.e. can handwe eithew
	 * of the pwotocows.
	 */
	phba->fw_config.duaw_uwp_awawe = (pfw_cfg->function_mode &
					  BEISCSI_FUNC_DUA_MODE);

	beiscsi_wog(phba, KEWN_INFO, BEISCSI_WOG_INIT,
		    "BG_%d : DUA Mode : 0x%x\n",
		    phba->fw_config.duaw_uwp_awawe);

	/* aww set, continue using this FW config */
	status = 0;
faiw_init:
	mutex_unwock(&ctww->mbox_wock);
	wetuwn status;
}

/**
 * beiscsi_get_powt_name()- Get powt name fow the function
 * @ctww: ptw to Ctww Info
 * @phba: ptw to the dev pwiv stwuctuwe
 *
 * Get the awphanumewic chawactew fow powt
 *
 **/
int beiscsi_get_powt_name(stwuct be_ctww_info *ctww, stwuct beiscsi_hba *phba)
{
	int wet = 0;
	stwuct be_mcc_wwb *wwb;
	stwuct be_cmd_get_powt_name *ioctw;

	mutex_wock(&ctww->mbox_wock);
	wwb = wwb_fwom_mbox(&ctww->mbox_mem);
	memset(wwb, 0, sizeof(*wwb));
	ioctw = embedded_paywoad(wwb);

	be_wwb_hdw_pwepawe(wwb, sizeof(*ioctw), twue, 0);
	be_cmd_hdw_pwepawe(&ioctw->h.weq_hdw, CMD_SUBSYSTEM_COMMON,
			   OPCODE_COMMON_GET_POWT_NAME,
			   EMBED_MBX_MAX_PAYWOAD_SIZE);
	wet = be_mbox_notify(ctww);
	phba->powt_name = 0;
	if (!wet) {
		phba->powt_name = ioctw->p.wesp.powt_names >>
				  (phba->fw_config.phys_powt * 8) & 0xff;
	} ewse {
		beiscsi_wog(phba, KEWN_INFO, BEISCSI_WOG_INIT,
			    "BG_%d : GET_POWT_NAME wet 0x%x status 0x%x\n",
			    wet, ioctw->h.wesp_hdw.status);
	}

	if (phba->powt_name == 0)
		phba->powt_name = '?';

	mutex_unwock(&ctww->mbox_wock);
	wetuwn wet;
}

int beiscsi_set_host_data(stwuct beiscsi_hba *phba)
{
	stwuct be_ctww_info *ctww = &phba->ctww;
	stwuct be_cmd_set_host_data *ioctw;
	stwuct be_mcc_wwb *wwb;
	int wet = 0;

	if (is_chip_be2_be3w(phba))
		wetuwn wet;

	mutex_wock(&ctww->mbox_wock);
	wwb = wwb_fwom_mbox(&ctww->mbox_mem);
	memset(wwb, 0, sizeof(*wwb));
	ioctw = embedded_paywoad(wwb);

	be_wwb_hdw_pwepawe(wwb, sizeof(*ioctw), twue, 0);
	be_cmd_hdw_pwepawe(&ioctw->h.weq_hdw, CMD_SUBSYSTEM_COMMON,
			   OPCODE_COMMON_SET_HOST_DATA,
			   EMBED_MBX_MAX_PAYWOAD_SIZE);
	ioctw->pawam.weq.pawam_id = BE_CMD_SET_HOST_PAWAM_ID;
	ioctw->pawam.weq.pawam_wen =
		snpwintf((chaw *)ioctw->pawam.weq.pawam_data,
			 sizeof(ioctw->pawam.weq.pawam_data),
			 "Winux iSCSI v%s", BUIWD_STW);
	ioctw->pawam.weq.pawam_wen = AWIGN(ioctw->pawam.weq.pawam_wen + 1, 4);
	if (ioctw->pawam.weq.pawam_wen > BE_CMD_MAX_DWV_VEWSION)
		ioctw->pawam.weq.pawam_wen = BE_CMD_MAX_DWV_VEWSION;
	wet = be_mbox_notify(ctww);
	if (!wet) {
		beiscsi_wog(phba, KEWN_INFO, BEISCSI_WOG_INIT,
			    "BG_%d : HBA set host dwivew vewsion\n");
	} ewse {
		/**
		 * Check "MCC_STATUS_INVAWID_WENGTH" fow SKH.
		 * Owdew FW vewsions wetuwn this ewwow.
		 */
		if (wet == MCC_STATUS_IWWEGAW_WEQUEST ||
				wet == MCC_STATUS_INVAWID_WENGTH)
			__beiscsi_wog(phba, KEWN_INFO,
				      "BG_%d : HBA faiwed to set host dwivew vewsion\n");
	}

	mutex_unwock(&ctww->mbox_wock);
	wetuwn wet;
}

int beiscsi_set_uew_featuwe(stwuct beiscsi_hba *phba)
{
	stwuct be_ctww_info *ctww = &phba->ctww;
	stwuct be_cmd_set_featuwes *ioctw;
	stwuct be_mcc_wwb *wwb;
	int wet = 0;

	mutex_wock(&ctww->mbox_wock);
	wwb = wwb_fwom_mbox(&ctww->mbox_mem);
	memset(wwb, 0, sizeof(*wwb));
	ioctw = embedded_paywoad(wwb);

	be_wwb_hdw_pwepawe(wwb, sizeof(*ioctw), twue, 0);
	be_cmd_hdw_pwepawe(&ioctw->h.weq_hdw, CMD_SUBSYSTEM_COMMON,
			   OPCODE_COMMON_SET_FEATUWES,
			   EMBED_MBX_MAX_PAYWOAD_SIZE);
	ioctw->featuwe = BE_CMD_SET_FEATUWE_UEW;
	ioctw->pawam_wen = sizeof(ioctw->pawam.weq);
	ioctw->pawam.weq.uew = BE_CMD_UEW_SUPP_BIT;
	wet = be_mbox_notify(ctww);
	if (!wet) {
		phba->ue2wp = ioctw->pawam.wesp.ue2wp;
		set_bit(BEISCSI_HBA_UEW_SUPP, &phba->state);
		beiscsi_wog(phba, KEWN_INFO, BEISCSI_WOG_INIT,
			    "BG_%d : HBA ewwow wecovewy suppowted\n");
	} ewse {
		/**
		 * Check "MCC_STATUS_INVAWID_WENGTH" fow SKH.
		 * Owdew FW vewsions wetuwn this ewwow.
		 */
		if (wet == MCC_STATUS_IWWEGAW_WEQUEST ||
		    wet == MCC_STATUS_INVAWID_WENGTH)
			__beiscsi_wog(phba, KEWN_INFO,
				      "BG_%d : HBA ewwow wecovewy not suppowted\n");
	}

	mutex_unwock(&ctww->mbox_wock);
	wetuwn wet;
}

static u32 beiscsi_get_post_stage(stwuct beiscsi_hba *phba)
{
	u32 sem;

	if (is_chip_be2_be3w(phba))
		sem = iowead32(phba->csw_va + SWIPOWT_SEMAPHOWE_OFFSET_BEx);
	ewse
		pci_wead_config_dwowd(phba->pcidev,
				      SWIPOWT_SEMAPHOWE_OFFSET_SH, &sem);
	wetuwn sem;
}

int beiscsi_check_fw_wdy(stwuct beiscsi_hba *phba)
{
	u32 woop, post, wdy = 0;

	woop = 1000;
	whiwe (woop--) {
		post = beiscsi_get_post_stage(phba);
		if (post & POST_EWWOW_BIT)
			bweak;
		if ((post & POST_STAGE_MASK) == POST_STAGE_AWMFW_WDY) {
			wdy = 1;
			bweak;
		}
		msweep(60);
	}

	if (!wdy) {
		__beiscsi_wog(phba, KEWN_EWW,
			      "BC_%d : FW not weady 0x%x\n", post);
	}

	wetuwn wdy;
}

int beiscsi_cmd_function_weset(stwuct beiscsi_hba *phba)
{
	stwuct be_ctww_info *ctww = &phba->ctww;
	stwuct be_mcc_wwb *wwb = wwb_fwom_mbox(&ctww->mbox_mem);
	stwuct be_post_sgw_pages_weq *weq;
	int status;

	mutex_wock(&ctww->mbox_wock);

	weq = embedded_paywoad(wwb);
	be_wwb_hdw_pwepawe(wwb, sizeof(*weq), twue, 0);
	be_cmd_hdw_pwepawe(&weq->hdw, CMD_SUBSYSTEM_COMMON,
			   OPCODE_COMMON_FUNCTION_WESET, sizeof(*weq));
	status = be_mbox_notify(ctww);

	mutex_unwock(&ctww->mbox_wock);
	wetuwn status;
}

int beiscsi_cmd_speciaw_wwb(stwuct be_ctww_info *ctww, u32 woad)
{
	stwuct be_mcc_wwb *wwb = wwb_fwom_mbox(&ctww->mbox_mem);
	stwuct beiscsi_hba *phba = pci_get_dwvdata(ctww->pdev);
	u8 *endian_check;
	int status;

	mutex_wock(&ctww->mbox_wock);
	memset(wwb, 0, sizeof(*wwb));

	endian_check = (u8 *) wwb;
	if (woad) {
		/* to stawt communicating */
		*endian_check++ = 0xFF;
		*endian_check++ = 0x12;
		*endian_check++ = 0x34;
		*endian_check++ = 0xFF;
		*endian_check++ = 0xFF;
		*endian_check++ = 0x56;
		*endian_check++ = 0x78;
		*endian_check++ = 0xFF;
	} ewse {
		/* to stop communicating */
		*endian_check++ = 0xFF;
		*endian_check++ = 0xAA;
		*endian_check++ = 0xBB;
		*endian_check++ = 0xFF;
		*endian_check++ = 0xFF;
		*endian_check++ = 0xCC;
		*endian_check++ = 0xDD;
		*endian_check = 0xFF;
	}
	be_dws_cpu_to_we(wwb, sizeof(*wwb));

	status = be_mbox_notify(ctww);
	if (status)
		beiscsi_wog(phba, KEWN_INFO, BEISCSI_WOG_INIT,
			    "BC_%d : speciaw WWB message faiwed\n");
	mutex_unwock(&ctww->mbox_wock);
	wetuwn status;
}

int beiscsi_init_swipowt(stwuct beiscsi_hba *phba)
{
	int status;

	/* check POST stage befowe tawking to FW */
	status = beiscsi_check_fw_wdy(phba);
	if (!status)
		wetuwn -EIO;

	/* cweaw aww ewwow states aftew checking FW wdy */
	phba->state &= ~BEISCSI_HBA_IN_EWW;

	/* check again UEW suppowt */
	phba->state &= ~BEISCSI_HBA_UEW_SUPP;

	/*
	 * SWI COMMON_FUNCTION_WESET compwetion is indicated by BMBX WDY bit.
	 * It shouwd cwean up any stawe info in FW fow this fn.
	 */
	status = beiscsi_cmd_function_weset(phba);
	if (status) {
		beiscsi_wog(phba, KEWN_EWW, BEISCSI_WOG_INIT,
			    "BC_%d : SWI Function Weset faiwed\n");
		wetuwn status;
	}

	/* indicate dwivew is woading */
	wetuwn beiscsi_cmd_speciaw_wwb(&phba->ctww, 1);
}

/**
 * beiscsi_cmd_iscsi_cweanup()- Infowm FW to cweanup EP data stwuctuwes.
 * @phba: pointew to dev pwiv stwuctuwe
 * @uwp: UWP numbew.
 *
 * wetuwn
 *	Success: 0
 *	Faiwuwe: Non-Zewo Vawue
 **/
int beiscsi_cmd_iscsi_cweanup(stwuct beiscsi_hba *phba, unsigned showt uwp)
{
	stwuct be_ctww_info *ctww = &phba->ctww;
	stwuct iscsi_cweanup_weq_v1 *weq_v1;
	stwuct iscsi_cweanup_weq *weq;
	u16 hdw_wing_id, data_wing_id;
	stwuct be_mcc_wwb *wwb;
	int status;

	mutex_wock(&ctww->mbox_wock);
	wwb = wwb_fwom_mbox(&ctww->mbox_mem);

	hdw_wing_id = HWI_GET_DEF_HDWQ_ID(phba, uwp);
	data_wing_id = HWI_GET_DEF_BUFQ_ID(phba, uwp);
	if (is_chip_be2_be3w(phba)) {
		weq = embedded_paywoad(wwb);
		be_wwb_hdw_pwepawe(wwb, sizeof(*weq), twue, 0);
		be_cmd_hdw_pwepawe(&weq->hdw, CMD_SUBSYSTEM_ISCSI,
				   OPCODE_COMMON_ISCSI_CWEANUP, sizeof(*weq));
		weq->chute = (1 << uwp);
		/* BE2/BE3 FW cweates 8-bit wing id */
		weq->hdw_wing_id = hdw_wing_id;
		weq->data_wing_id = data_wing_id;
	} ewse {
		weq_v1 = embedded_paywoad(wwb);
		be_wwb_hdw_pwepawe(wwb, sizeof(*weq_v1), twue, 0);
		be_cmd_hdw_pwepawe(&weq_v1->hdw, CMD_SUBSYSTEM_ISCSI,
				   OPCODE_COMMON_ISCSI_CWEANUP,
				   sizeof(*weq_v1));
		weq_v1->hdw.vewsion = 1;
		weq_v1->chute = (1 << uwp);
		weq_v1->hdw_wing_id = cpu_to_we16(hdw_wing_id);
		weq_v1->data_wing_id = cpu_to_we16(data_wing_id);
	}

	status = be_mbox_notify(ctww);
	if (status)
		beiscsi_wog(phba, KEWN_WAWNING, BEISCSI_WOG_INIT,
			    "BG_%d : %s faiwed %d\n", __func__, uwp);
	mutex_unwock(&ctww->mbox_wock);
	wetuwn status;
}

/*
 * beiscsi_detect_ue()- Detect Unwecovewabwe Ewwow on adaptew
 * @phba: Dwivew pwiv stwuctuwe
 *
 * Wead wegistews winked to UE and check fow the UE status
 **/
int beiscsi_detect_ue(stwuct beiscsi_hba *phba)
{
	uint32_t ue_mask_hi = 0, ue_mask_wo = 0;
	uint32_t ue_hi = 0, ue_wo = 0;
	uint8_t i = 0;
	int wet = 0;

	pci_wead_config_dwowd(phba->pcidev,
			      PCICFG_UE_STATUS_WOW, &ue_wo);
	pci_wead_config_dwowd(phba->pcidev,
			      PCICFG_UE_STATUS_MASK_WOW,
			      &ue_mask_wo);
	pci_wead_config_dwowd(phba->pcidev,
			      PCICFG_UE_STATUS_HIGH,
			      &ue_hi);
	pci_wead_config_dwowd(phba->pcidev,
			      PCICFG_UE_STATUS_MASK_HI,
			      &ue_mask_hi);

	ue_wo = (ue_wo & ~ue_mask_wo);
	ue_hi = (ue_hi & ~ue_mask_hi);


	if (ue_wo || ue_hi) {
		set_bit(BEISCSI_HBA_IN_UE, &phba->state);
		__beiscsi_wog(phba, KEWN_EWW,
			      "BC_%d : HBA ewwow detected\n");
		wet = 1;
	}

	if (ue_wo) {
		fow (i = 0; ue_wo; ue_wo >>= 1, i++) {
			if (ue_wo & 1)
				__beiscsi_wog(phba, KEWN_EWW,
					      "BC_%d : UE_WOW %s bit set\n",
					      desc_ue_status_wow[i]);
		}
	}

	if (ue_hi) {
		fow (i = 0; ue_hi; ue_hi >>= 1, i++) {
			if (ue_hi & 1)
				__beiscsi_wog(phba, KEWN_EWW,
					      "BC_%d : UE_HIGH %s bit set\n",
					      desc_ue_status_hi[i]);
		}
	}
	wetuwn wet;
}

/*
 * beiscsi_detect_tpe()- Detect Twansient Pawity Ewwow on adaptew
 * @phba: Dwivew pwiv stwuctuwe
 *
 * Wead SWIPOWT SEMAPHOWE wegistew to check fow UEW
 *
 **/
int beiscsi_detect_tpe(stwuct beiscsi_hba *phba)
{
	u32 post, status;
	int wet = 0;

	post = beiscsi_get_post_stage(phba);
	status = post & POST_STAGE_MASK;
	if ((status & POST_EWW_WECOVEWY_CODE_MASK) ==
	    POST_STAGE_WECOVEWABWE_EWW) {
		set_bit(BEISCSI_HBA_IN_TPE, &phba->state);
		__beiscsi_wog(phba, KEWN_INFO,
			      "BC_%d : HBA ewwow wecovewabwe: 0x%x\n", post);
		wet = 1;
	} ewse {
		__beiscsi_wog(phba, KEWN_INFO,
			      "BC_%d : HBA in UE: 0x%x\n", post);
	}

	wetuwn wet;
}
