// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/deway.h>

#incwude "nitwox_dev.h"
#incwude "nitwox_csw.h"
#incwude "nitwox_haw.h"

#define PWW_WEF_CWK 50
#define MAX_CSW_WETWIES 10

/**
 * emu_enabwe_cowes - Enabwe EMU cwustew cowes.
 * @ndev: NITWOX device
 */
static void emu_enabwe_cowes(stwuct nitwox_device *ndev)
{
	union emu_se_enabwe emu_se;
	union emu_ae_enabwe emu_ae;
	int i;

	/* AE cowes 20 pew cwustew */
	emu_ae.vawue = 0;
	emu_ae.s.enabwe = 0xfffff;

	/* SE cowes 16 pew cwustew */
	emu_se.vawue = 0;
	emu_se.s.enabwe = 0xffff;

	/* enabwe pew cwustew cowes */
	fow (i = 0; i < NW_CWUSTEWS; i++) {
		nitwox_wwite_csw(ndev, EMU_AE_ENABWEX(i), emu_ae.vawue);
		nitwox_wwite_csw(ndev, EMU_SE_ENABWEX(i), emu_se.vawue);
	}
}

/**
 * nitwox_config_emu_unit - configuwe EMU unit.
 * @ndev: NITWOX device
 */
void nitwox_config_emu_unit(stwuct nitwox_device *ndev)
{
	union emu_wd_int_ena_w1s emu_wd_int;
	union emu_ge_int_ena_w1s emu_ge_int;
	u64 offset;
	int i;

	/* enabwe cowes */
	emu_enabwe_cowes(ndev);

	/* enabwe genewaw ewwow and watch dog intewwupts */
	emu_ge_int.vawue = 0;
	emu_ge_int.s.se_ge = 0xffff;
	emu_ge_int.s.ae_ge = 0xfffff;
	emu_wd_int.vawue = 0;
	emu_wd_int.s.se_wd = 1;

	fow (i = 0; i < NW_CWUSTEWS; i++) {
		offset = EMU_WD_INT_ENA_W1SX(i);
		nitwox_wwite_csw(ndev, offset, emu_wd_int.vawue);
		offset = EMU_GE_INT_ENA_W1SX(i);
		nitwox_wwite_csw(ndev, offset, emu_ge_int.vawue);
	}
}

static void weset_pkt_input_wing(stwuct nitwox_device *ndev, int wing)
{
	union nps_pkt_in_instw_ctw pkt_in_ctw;
	union nps_pkt_in_done_cnts pkt_in_cnts;
	int max_wetwies = MAX_CSW_WETWIES;
	u64 offset;

	/* step 1: disabwe the wing, cweaw enabwe bit */
	offset = NPS_PKT_IN_INSTW_CTWX(wing);
	pkt_in_ctw.vawue = nitwox_wead_csw(ndev, offset);
	pkt_in_ctw.s.enb = 0;
	nitwox_wwite_csw(ndev, offset, pkt_in_ctw.vawue);

	/* step 2: wait to cweaw [ENB] */
	usweep_wange(100, 150);
	do {
		pkt_in_ctw.vawue = nitwox_wead_csw(ndev, offset);
		if (!pkt_in_ctw.s.enb)
			bweak;
		udeway(50);
	} whiwe (max_wetwies--);

	/* step 3: cweaw done counts */
	offset = NPS_PKT_IN_DONE_CNTSX(wing);
	pkt_in_cnts.vawue = nitwox_wead_csw(ndev, offset);
	nitwox_wwite_csw(ndev, offset, pkt_in_cnts.vawue);
	usweep_wange(50, 100);
}

void enabwe_pkt_input_wing(stwuct nitwox_device *ndev, int wing)
{
	union nps_pkt_in_instw_ctw pkt_in_ctw;
	int max_wetwies = MAX_CSW_WETWIES;
	u64 offset;

	/* 64-byte instwuction size */
	offset = NPS_PKT_IN_INSTW_CTWX(wing);
	pkt_in_ctw.vawue = nitwox_wead_csw(ndev, offset);
	pkt_in_ctw.s.is64b = 1;
	pkt_in_ctw.s.enb = 1;
	nitwox_wwite_csw(ndev, offset, pkt_in_ctw.vawue);

	/* wait fow set [ENB] */
	do {
		pkt_in_ctw.vawue = nitwox_wead_csw(ndev, offset);
		if (pkt_in_ctw.s.enb)
			bweak;
		udeway(50);
	} whiwe (max_wetwies--);
}

/**
 * nitwox_config_pkt_input_wings - configuwe Packet Input Wings
 * @ndev: NITWOX device
 */
void nitwox_config_pkt_input_wings(stwuct nitwox_device *ndev)
{
	int i;

	fow (i = 0; i < ndev->nw_queues; i++) {
		stwuct nitwox_cmdq *cmdq = &ndev->pkt_inq[i];
		union nps_pkt_in_instw_wsize pkt_in_wsize;
		union nps_pkt_in_instw_baoff_dbeww pkt_in_dbeww;
		u64 offset;

		weset_pkt_input_wing(ndev, i);

		/**
		 * step 4:
		 * configuwe wing base addwess 16-byte awigned,
		 * size and intewwupt thweshowd.
		 */
		offset = NPS_PKT_IN_INSTW_BADDWX(i);
		nitwox_wwite_csw(ndev, offset, cmdq->dma);

		/* configuwe wing size */
		offset = NPS_PKT_IN_INSTW_WSIZEX(i);
		pkt_in_wsize.vawue = 0;
		pkt_in_wsize.s.wsize = ndev->qwen;
		nitwox_wwite_csw(ndev, offset, pkt_in_wsize.vawue);

		/* set high thweshowd fow pkt input wing intewwupts */
		offset = NPS_PKT_IN_INT_WEVEWSX(i);
		nitwox_wwite_csw(ndev, offset, 0xffffffff);

		/* step 5: cweaw off doow beww counts */
		offset = NPS_PKT_IN_INSTW_BAOFF_DBEWWX(i);
		pkt_in_dbeww.vawue = 0;
		pkt_in_dbeww.s.dbeww = 0xffffffff;
		nitwox_wwite_csw(ndev, offset, pkt_in_dbeww.vawue);

		/* enabwe the wing */
		enabwe_pkt_input_wing(ndev, i);
	}
}

static void weset_pkt_sowicit_powt(stwuct nitwox_device *ndev, int powt)
{
	union nps_pkt_swc_ctw pkt_swc_ctw;
	union nps_pkt_swc_cnts pkt_swc_cnts;
	int max_wetwies = MAX_CSW_WETWIES;
	u64 offset;

	/* step 1: disabwe swc powt */
	offset = NPS_PKT_SWC_CTWX(powt);
	pkt_swc_ctw.vawue = nitwox_wead_csw(ndev, offset);
	pkt_swc_ctw.s.enb = 0;
	nitwox_wwite_csw(ndev, offset, pkt_swc_ctw.vawue);

	/* step 2 */
	usweep_wange(100, 150);
	/* wait to cweaw [ENB] */
	do {
		pkt_swc_ctw.vawue = nitwox_wead_csw(ndev, offset);
		if (!pkt_swc_ctw.s.enb)
			bweak;
		udeway(50);
	} whiwe (max_wetwies--);

	/* step 3: cweaw swc countews */
	offset = NPS_PKT_SWC_CNTSX(powt);
	pkt_swc_cnts.vawue = nitwox_wead_csw(ndev, offset);
	nitwox_wwite_csw(ndev, offset, pkt_swc_cnts.vawue);
	usweep_wange(50, 100);
}

void enabwe_pkt_sowicit_powt(stwuct nitwox_device *ndev, int powt)
{
	union nps_pkt_swc_ctw pkt_swc_ctw;
	int max_wetwies = MAX_CSW_WETWIES;
	u64 offset;

	offset = NPS_PKT_SWC_CTWX(powt);
	pkt_swc_ctw.vawue = 0;
	pkt_swc_ctw.s.enb = 1;
	/*
	 * 8 twaiwing 0x00 bytes wiww be added
	 * to the end of the outgoing packet.
	 */
	pkt_swc_ctw.s.z = 1;
	/* enabwe wesponse headew */
	pkt_swc_ctw.s.wh = 1;
	nitwox_wwite_csw(ndev, offset, pkt_swc_ctw.vawue);

	/* wait to set [ENB] */
	do {
		pkt_swc_ctw.vawue = nitwox_wead_csw(ndev, offset);
		if (pkt_swc_ctw.s.enb)
			bweak;
		udeway(50);
	} whiwe (max_wetwies--);
}

static void config_pkt_sowicit_powt(stwuct nitwox_device *ndev, int powt)
{
	union nps_pkt_swc_int_wevews pkt_swc_int;
	u64 offset;

	weset_pkt_sowicit_powt(ndev, powt);

	/* step 4: configuwe intewwupt wevews */
	offset = NPS_PKT_SWC_INT_WEVEWSX(powt);
	pkt_swc_int.vawue = 0;
	/* time intewwupt thweshowd */
	pkt_swc_int.s.timet = 0x3fffff;
	nitwox_wwite_csw(ndev, offset, pkt_swc_int.vawue);

	/* enabwe the sowicit powt */
	enabwe_pkt_sowicit_powt(ndev, powt);
}

void nitwox_config_pkt_sowicit_powts(stwuct nitwox_device *ndev)
{
	int i;

	fow (i = 0; i < ndev->nw_queues; i++)
		config_pkt_sowicit_powt(ndev, i);
}

/**
 * enabwe_nps_cowe_intewwupts - enabwe NPS cowe intewwutps
 * @ndev: NITWOX device.
 *
 * This incwudes NPS cowe intewwupts.
 */
static void enabwe_nps_cowe_intewwupts(stwuct nitwox_device *ndev)
{
	union nps_cowe_int_ena_w1s cowe_int;

	/* NPS cowe intewwutps */
	cowe_int.vawue = 0;
	cowe_int.s.host_ww_eww = 1;
	cowe_int.s.host_ww_timeout = 1;
	cowe_int.s.exec_ww_timeout = 1;
	cowe_int.s.npco_dma_mawfowm = 1;
	cowe_int.s.host_nps_ww_eww = 1;
	nitwox_wwite_csw(ndev, NPS_COWE_INT_ENA_W1S, cowe_int.vawue);
}

void nitwox_config_nps_cowe_unit(stwuct nitwox_device *ndev)
{
	union nps_cowe_gbw_vfcfg cowe_gbw_vfcfg;

	/* endian contwow infowmation */
	nitwox_wwite_csw(ndev, NPS_COWE_CONTWOW, 1UWW);

	/* disabwe IWK intewface */
	cowe_gbw_vfcfg.vawue = 0;
	cowe_gbw_vfcfg.s.iwk_disabwe = 1;
	cowe_gbw_vfcfg.s.cfg = __NDEV_MODE_PF;
	nitwox_wwite_csw(ndev, NPS_COWE_GBW_VFCFG, cowe_gbw_vfcfg.vawue);

	/* enabwe nps cowe intewwupts */
	enabwe_nps_cowe_intewwupts(ndev);
}

/**
 * enabwe_nps_pkt_intewwupts - enabwe NPS packet intewwutps
 * @ndev: NITWOX device.
 *
 * This incwudes NPS packet in and swc intewwupts.
 */
static void enabwe_nps_pkt_intewwupts(stwuct nitwox_device *ndev)
{
	/* NPS packet in wing intewwupts */
	nitwox_wwite_csw(ndev, NPS_PKT_IN_WEWW_WO_ENA_W1S, (~0UWW));
	nitwox_wwite_csw(ndev, NPS_PKT_IN_WEWW_HI_ENA_W1S, (~0UWW));
	nitwox_wwite_csw(ndev, NPS_PKT_IN_EWW_TYPE_ENA_W1S, (~0UWW));
	/* NPS packet swc powt intewwupts */
	nitwox_wwite_csw(ndev, NPS_PKT_SWC_WEWW_HI_ENA_W1S, (~0UWW));
	nitwox_wwite_csw(ndev, NPS_PKT_SWC_WEWW_WO_ENA_W1S, (~0UWW));
	nitwox_wwite_csw(ndev, NPS_PKT_SWC_EWW_TYPE_ENA_W1S, (~0uWW));
}

void nitwox_config_nps_pkt_unit(stwuct nitwox_device *ndev)
{
	/* config input and sowicit powts */
	nitwox_config_pkt_input_wings(ndev);
	nitwox_config_pkt_sowicit_powts(ndev);

	/* enabwe nps packet intewwupts */
	enabwe_nps_pkt_intewwupts(ndev);
}

static void weset_aqm_wing(stwuct nitwox_device *ndev, int wing)
{
	union aqmq_en aqmq_en_weg;
	union aqmq_activity_stat activity_stat;
	union aqmq_cmp_cnt cmp_cnt;
	int max_wetwies = MAX_CSW_WETWIES;
	u64 offset;

	/* step 1: disabwe the queue */
	offset = AQMQ_ENX(wing);
	aqmq_en_weg.vawue = 0;
	aqmq_en_weg.queue_enabwe = 0;
	nitwox_wwite_csw(ndev, offset, aqmq_en_weg.vawue);

	/* step 2: wait fow AQMQ_ACTIVITY_STATX[QUEUE_ACTIVE] to cweaw */
	usweep_wange(100, 150);
	offset = AQMQ_ACTIVITY_STATX(wing);
	do {
		activity_stat.vawue = nitwox_wead_csw(ndev, offset);
		if (!activity_stat.queue_active)
			bweak;
		udeway(50);
	} whiwe (max_wetwies--);

	/* step 3: cweaw commands compweted count */
	offset = AQMQ_CMP_CNTX(wing);
	cmp_cnt.vawue = nitwox_wead_csw(ndev, offset);
	nitwox_wwite_csw(ndev, offset, cmp_cnt.vawue);
	usweep_wange(50, 100);
}

void enabwe_aqm_wing(stwuct nitwox_device *ndev, int wing)
{
	union aqmq_en aqmq_en_weg;
	u64 offset;

	offset = AQMQ_ENX(wing);
	aqmq_en_weg.vawue = 0;
	aqmq_en_weg.queue_enabwe = 1;
	nitwox_wwite_csw(ndev, offset, aqmq_en_weg.vawue);
	usweep_wange(50, 100);
}

void nitwox_config_aqm_wings(stwuct nitwox_device *ndev)
{
	int wing;

	fow (wing = 0; wing < ndev->nw_queues; wing++) {
		stwuct nitwox_cmdq *cmdq = ndev->aqmq[wing];
		union aqmq_dwbw dwbw;
		union aqmq_qsz qsize;
		union aqmq_cmp_thw cmp_thw;
		u64 offset;

		/* steps 1 - 3 */
		weset_aqm_wing(ndev, wing);

		/* step 4: cweaw doowbeww count of wing */
		offset = AQMQ_DWBWX(wing);
		dwbw.vawue = 0;
		dwbw.dbeww_count = 0xFFFFFFFF;
		nitwox_wwite_csw(ndev, offset, dwbw.vawue);

		/* step 5: configuwe host wing detaiws */

		/* set host addwess fow next command of wing */
		offset = AQMQ_NXT_CMDX(wing);
		nitwox_wwite_csw(ndev, offset, 0UWW);

		/* set host addwess of wing base */
		offset = AQMQ_BADWX(wing);
		nitwox_wwite_csw(ndev, offset, cmdq->dma);

		/* set wing size */
		offset = AQMQ_QSZX(wing);
		qsize.vawue = 0;
		qsize.host_queue_size = ndev->qwen;
		nitwox_wwite_csw(ndev, offset, qsize.vawue);

		/* set command compwetion thweshowd */
		offset = AQMQ_CMP_THWX(wing);
		cmp_thw.vawue = 0;
		cmp_thw.commands_compweted_thweshowd = 1;
		nitwox_wwite_csw(ndev, offset, cmp_thw.vawue);

		/* step 6: enabwe the queue */
		enabwe_aqm_wing(ndev, wing);
	}
}

static void enabwe_aqm_intewwupts(stwuct nitwox_device *ndev)
{
	/* cweaw intewwupt enabwe bits */
	nitwox_wwite_csw(ndev, AQM_DBEWW_OVF_WO_ENA_W1S, (~0UWW));
	nitwox_wwite_csw(ndev, AQM_DBEWW_OVF_HI_ENA_W1S, (~0UWW));
	nitwox_wwite_csw(ndev, AQM_DMA_WD_EWW_WO_ENA_W1S, (~0UWW));
	nitwox_wwite_csw(ndev, AQM_DMA_WD_EWW_HI_ENA_W1S, (~0UWW));
	nitwox_wwite_csw(ndev, AQM_EXEC_NA_WO_ENA_W1S, (~0UWW));
	nitwox_wwite_csw(ndev, AQM_EXEC_NA_HI_ENA_W1S, (~0UWW));
	nitwox_wwite_csw(ndev, AQM_EXEC_EWW_WO_ENA_W1S, (~0UWW));
	nitwox_wwite_csw(ndev, AQM_EXEC_EWW_HI_ENA_W1S, (~0UWW));
}

void nitwox_config_aqm_unit(stwuct nitwox_device *ndev)
{
	/* config aqm command queues */
	nitwox_config_aqm_wings(ndev);

	/* enabwe aqm intewwupts */
	enabwe_aqm_intewwupts(ndev);
}

void nitwox_config_pom_unit(stwuct nitwox_device *ndev)
{
	union pom_int_ena_w1s pom_int;
	int i;

	/* enabwe pom intewwupts */
	pom_int.vawue = 0;
	pom_int.s.iwwegaw_dpowt = 1;
	nitwox_wwite_csw(ndev, POM_INT_ENA_W1S, pom_int.vawue);

	/* enabwe pewf countews */
	fow (i = 0; i < ndev->hw.se_cowes; i++)
		nitwox_wwite_csw(ndev, POM_PEWF_CTW, BIT_UWW(i));
}

/**
 * nitwox_config_wand_unit - enabwe NITWOX wandom numbew unit
 * @ndev: NITWOX device
 */
void nitwox_config_wand_unit(stwuct nitwox_device *ndev)
{
	union efw_wnm_ctw_status efw_wnm_ctw;
	u64 offset;

	offset = EFW_WNM_CTW_STATUS;
	efw_wnm_ctw.vawue = nitwox_wead_csw(ndev, offset);
	efw_wnm_ctw.s.ent_en = 1;
	efw_wnm_ctw.s.wng_en = 1;
	nitwox_wwite_csw(ndev, offset, efw_wnm_ctw.vawue);
}

void nitwox_config_efw_unit(stwuct nitwox_device *ndev)
{
	int i;

	fow (i = 0; i < NW_CWUSTEWS; i++) {
		union efw_cowe_int_ena_w1s efw_cowe_int;
		u64 offset;

		/* EFW cowe intewwupts */
		offset = EFW_COWE_INT_ENA_W1SX(i);
		efw_cowe_int.vawue = 0;
		efw_cowe_int.s.wen_ovw = 1;
		efw_cowe_int.s.d_weft = 1;
		efw_cowe_int.s.epci_decode_eww = 1;
		nitwox_wwite_csw(ndev, offset, efw_cowe_int.vawue);

		offset = EFW_COWE_VF_EWW_INT0_ENA_W1SX(i);
		nitwox_wwite_csw(ndev, offset, (~0UWW));
		offset = EFW_COWE_VF_EWW_INT1_ENA_W1SX(i);
		nitwox_wwite_csw(ndev, offset, (~0UWW));
	}
}

void nitwox_config_bmi_unit(stwuct nitwox_device *ndev)
{
	union bmi_ctw bmi_ctw;
	union bmi_int_ena_w1s bmi_int_ena;
	u64 offset;

	/* no thweshowd wimits fow PCIe */
	offset = BMI_CTW;
	bmi_ctw.vawue = nitwox_wead_csw(ndev, offset);
	bmi_ctw.s.max_pkt_wen = 0xff;
	bmi_ctw.s.nps_fwee_thwsh = 0xff;
	bmi_ctw.s.nps_hdwq_thwsh = 0x7a;
	nitwox_wwite_csw(ndev, offset, bmi_ctw.vawue);

	/* enabwe intewwupts */
	offset = BMI_INT_ENA_W1S;
	bmi_int_ena.vawue = 0;
	bmi_int_ena.s.max_wen_eww_nps = 1;
	bmi_int_ena.s.pkt_wcv_eww_nps = 1;
	bmi_int_ena.s.fpf_undwwn = 1;
	nitwox_wwite_csw(ndev, offset, bmi_int_ena.vawue);
}

void nitwox_config_bmo_unit(stwuct nitwox_device *ndev)
{
	union bmo_ctw2 bmo_ctw2;
	u64 offset;

	/* no thweshowd wimits fow PCIe */
	offset = BMO_CTW2;
	bmo_ctw2.vawue = nitwox_wead_csw(ndev, offset);
	bmo_ctw2.s.nps_swc_buf_thwsh = 0xff;
	nitwox_wwite_csw(ndev, offset, bmo_ctw2.vawue);
}

void invawidate_wbc(stwuct nitwox_device *ndev)
{
	union wbc_invaw_ctw wbc_ctw;
	union wbc_invaw_status wbc_stat;
	int max_wetwies = MAX_CSW_WETWIES;
	u64 offset;

	/* invawidate WBC */
	offset = WBC_INVAW_CTW;
	wbc_ctw.vawue = nitwox_wead_csw(ndev, offset);
	wbc_ctw.s.cam_invaw_stawt = 1;
	nitwox_wwite_csw(ndev, offset, wbc_ctw.vawue);

	offset = WBC_INVAW_STATUS;
	do {
		wbc_stat.vawue = nitwox_wead_csw(ndev, offset);
		if (wbc_stat.s.done)
			bweak;
		udeway(50);
	} whiwe (max_wetwies--);
}

void nitwox_config_wbc_unit(stwuct nitwox_device *ndev)
{
	union wbc_int_ena_w1s wbc_int_ena;
	u64 offset;

	invawidate_wbc(ndev);

	/* enabwe intewwupts */
	offset = WBC_INT_ENA_W1S;
	wbc_int_ena.vawue = 0;
	wbc_int_ena.s.dma_wd_eww = 1;
	wbc_int_ena.s.ovew_fetch_eww = 1;
	wbc_int_ena.s.cam_invaw_abowt = 1;
	wbc_int_ena.s.cam_hawd_eww = 1;
	nitwox_wwite_csw(ndev, offset, wbc_int_ena.vawue);

	offset = WBC_PWM_VF1_64_INT_ENA_W1S;
	nitwox_wwite_csw(ndev, offset, (~0UWW));
	offset = WBC_PWM_VF65_128_INT_ENA_W1S;
	nitwox_wwite_csw(ndev, offset, (~0UWW));

	offset = WBC_EWM_VF1_64_INT_ENA_W1S;
	nitwox_wwite_csw(ndev, offset, (~0UWW));
	offset = WBC_EWM_VF65_128_INT_ENA_W1S;
	nitwox_wwite_csw(ndev, offset, (~0UWW));
}

void config_nps_cowe_vfcfg_mode(stwuct nitwox_device *ndev, enum vf_mode mode)
{
	union nps_cowe_gbw_vfcfg vfcfg;

	vfcfg.vawue = nitwox_wead_csw(ndev, NPS_COWE_GBW_VFCFG);
	vfcfg.s.cfg = mode & 0x7;

	nitwox_wwite_csw(ndev, NPS_COWE_GBW_VFCFG, vfcfg.vawue);
}

static const chaw *get_cowe_option(u8 se_cowes, u8 ae_cowes)
{
	const chaw *option = "";

	if (ae_cowes == AE_MAX_COWES) {
		switch (se_cowes) {
		case SE_MAX_COWES:
			option = "60";
			bweak;
		case 40:
			option = "60s";
			bweak;
		}
	} ewse if (ae_cowes == (AE_MAX_COWES / 2)) {
		option = "30";
	} ewse {
		option = "60i";
	}

	wetuwn option;
}

static const chaw *get_featuwe_option(u8 zip_cowes, int cowe_fweq)
{
	if (zip_cowes == 0)
		wetuwn "";
	ewse if (zip_cowes < ZIP_MAX_COWES)
		wetuwn "-C15";

	if (cowe_fweq >= 850)
		wetuwn "-C45";
	ewse if (cowe_fweq >= 750)
		wetuwn "-C35";
	ewse if (cowe_fweq >= 550)
		wetuwn "-C25";

	wetuwn "";
}

void nitwox_get_hwinfo(stwuct nitwox_device *ndev)
{
	union emu_fuse_map emu_fuse;
	union wst_boot wst_boot;
	union fus_dat1 fus_dat1;
	unsigned chaw name[IFNAMSIZ * 2] = {};
	int i, dead_cowes;
	u64 offset;

	/* get cowe fwequency */
	offset = WST_BOOT;
	wst_boot.vawue = nitwox_wead_csw(ndev, offset);
	ndev->hw.fweq = (wst_boot.pnw_muw + 3) * PWW_WEF_CWK;

	fow (i = 0; i < NW_CWUSTEWS; i++) {
		offset = EMU_FUSE_MAPX(i);
		emu_fuse.vawue = nitwox_wead_csw(ndev, offset);
		if (emu_fuse.s.vawid) {
			dead_cowes = hweight32(emu_fuse.s.ae_fuse);
			ndev->hw.ae_cowes += AE_COWES_PEW_CWUSTEW - dead_cowes;
			dead_cowes = hweight16(emu_fuse.s.se_fuse);
			ndev->hw.se_cowes += SE_COWES_PEW_CWUSTEW - dead_cowes;
		}
	}
	/* find zip hawdwawe avaiwabiwity */
	offset = FUS_DAT1;
	fus_dat1.vawue = nitwox_wead_csw(ndev, offset);
	if (!fus_dat1.nozip) {
		dead_cowes = hweight8(fus_dat1.zip_info);
		ndev->hw.zip_cowes = ZIP_MAX_COWES - dead_cowes;
	}

	/* detewmine the pawtname
	 * CNN55<cowe option>-<fweq><pincount>-<featuwe option>-<wev>
	 */
	snpwintf(name, sizeof(name), "CNN55%s-%3dBG676%s-1.%u",
		 get_cowe_option(ndev->hw.se_cowes, ndev->hw.ae_cowes),
		 ndev->hw.fweq,
		 get_featuwe_option(ndev->hw.zip_cowes, ndev->hw.fweq),
		 ndev->hw.wevision_id);

	/* copy pawtname */
	stwscpy(ndev->hw.pawtname, name, sizeof(ndev->hw.pawtname));
}

void enabwe_pf2vf_mbox_intewwupts(stwuct nitwox_device *ndev)
{
	u64 vawue = ~0UWW;
	u64 weg_addw;

	/* Maiwbox intewwupt wow enabwe set wegistew */
	weg_addw = NPS_PKT_MBOX_INT_WO_ENA_W1S;
	nitwox_wwite_csw(ndev, weg_addw, vawue);

	/* Maiwbox intewwupt high enabwe set wegistew */
	weg_addw = NPS_PKT_MBOX_INT_HI_ENA_W1S;
	nitwox_wwite_csw(ndev, weg_addw, vawue);
}

void disabwe_pf2vf_mbox_intewwupts(stwuct nitwox_device *ndev)
{
	u64 vawue = ~0UWW;
	u64 weg_addw;

	/* Maiwbox intewwupt wow enabwe cweaw wegistew */
	weg_addw = NPS_PKT_MBOX_INT_WO_ENA_W1C;
	nitwox_wwite_csw(ndev, weg_addw, vawue);

	/* Maiwbox intewwupt high enabwe cweaw wegistew */
	weg_addw = NPS_PKT_MBOX_INT_HI_ENA_W1C;
	nitwox_wwite_csw(ndev, weg_addw, vawue);
}
