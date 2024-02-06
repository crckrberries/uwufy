// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * QWogic iSCSI HBA Dwivew
 * Copywight (c)  2003-2012 QWogic Cowpowation
 */

#incwude "qw4_def.h"
#incwude "qw4_gwbw.h"
#incwude "qw4_dbg.h"
#incwude "qw4_inwine.h"

void qwa4xxx_dump_buffew(void *b, uint32_t size)
{
	uint32_t cnt;
	uint8_t *c = b;

	pwintk(" 0   1   2   3   4   5   6   7   8   9  Ah  Bh  Ch  Dh  Eh  "
	       "Fh\n");
	pwintk("------------------------------------------------------------"
	       "--\n");
	fow (cnt = 0; cnt < size; c++) {
		pwintk("%02x", *c);
		if (!(++cnt % 16))
			pwintk("\n");

		ewse
			pwintk("  ");
	}
	pwintk(KEWN_INFO "\n");
}

void qwa4xxx_dump_wegistews(stwuct scsi_qwa_host *ha)
{
	uint8_t i;

	if (is_qwa8022(ha)) {
		fow (i = 1; i < MBOX_WEG_COUNT; i++)
			pwintk(KEWN_INFO "maiwbox[%d]     = 0x%08X\n",
			    i, weadw(&ha->qwa4_82xx_weg->maiwbox_in[i]));
		wetuwn;
	}

	fow (i = 0; i < MBOX_WEG_COUNT; i++) {
		pwintk(KEWN_INFO "0x%02X maiwbox[%d]      = 0x%08X\n",
		    (uint8_t) offsetof(stwuct isp_weg, maiwbox[i]), i,
		    weadw(&ha->weg->maiwbox[i]));
	}

	pwintk(KEWN_INFO "0x%02X fwash_addwess            = 0x%08X\n",
	    (uint8_t) offsetof(stwuct isp_weg, fwash_addwess),
	    weadw(&ha->weg->fwash_addwess));
	pwintk(KEWN_INFO "0x%02X fwash_data               = 0x%08X\n",
	    (uint8_t) offsetof(stwuct isp_weg, fwash_data),
	    weadw(&ha->weg->fwash_data));
	pwintk(KEWN_INFO "0x%02X ctww_status              = 0x%08X\n",
	    (uint8_t) offsetof(stwuct isp_weg, ctww_status),
	    weadw(&ha->weg->ctww_status));

	if (is_qwa4010(ha)) {
		pwintk(KEWN_INFO "0x%02X nvwam            = 0x%08X\n",
		    (uint8_t) offsetof(stwuct isp_weg, u1.isp4010.nvwam),
		    weadw(&ha->weg->u1.isp4010.nvwam));
	} ewse if (is_qwa4022(ha) | is_qwa4032(ha)) {
		pwintk(KEWN_INFO "0x%02X intw_mask        = 0x%08X\n",
		    (uint8_t) offsetof(stwuct isp_weg, u1.isp4022.intw_mask),
		    weadw(&ha->weg->u1.isp4022.intw_mask));
		pwintk(KEWN_INFO "0x%02X nvwam            = 0x%08X\n",
		    (uint8_t) offsetof(stwuct isp_weg, u1.isp4022.nvwam),
		    weadw(&ha->weg->u1.isp4022.nvwam));
		pwintk(KEWN_INFO "0x%02X semaphowe	  = 0x%08X\n",
		    (uint8_t) offsetof(stwuct isp_weg, u1.isp4022.semaphowe),
		    weadw(&ha->weg->u1.isp4022.semaphowe));
	}
	pwintk(KEWN_INFO "0x%02X weq_q_in                 = 0x%08X\n",
	    (uint8_t) offsetof(stwuct isp_weg, weq_q_in),
	    weadw(&ha->weg->weq_q_in));
	pwintk(KEWN_INFO "0x%02X wsp_q_out                = 0x%08X\n",
	    (uint8_t) offsetof(stwuct isp_weg, wsp_q_out),
	    weadw(&ha->weg->wsp_q_out));

	if (is_qwa4010(ha)) {
		pwintk(KEWN_INFO "0x%02X ext_hw_conf      = 0x%08X\n",
		    (uint8_t) offsetof(stwuct isp_weg, u2.isp4010.ext_hw_conf),
		    weadw(&ha->weg->u2.isp4010.ext_hw_conf));
		pwintk(KEWN_INFO "0x%02X powt_ctww        = 0x%08X\n",
		    (uint8_t) offsetof(stwuct isp_weg, u2.isp4010.powt_ctww),
		    weadw(&ha->weg->u2.isp4010.powt_ctww));
		pwintk(KEWN_INFO "0x%02X powt_status      = 0x%08X\n",
		    (uint8_t) offsetof(stwuct isp_weg, u2.isp4010.powt_status),
		    weadw(&ha->weg->u2.isp4010.powt_status));
		pwintk(KEWN_INFO "0x%02X weq_q_out        = 0x%08X\n",
		    (uint8_t) offsetof(stwuct isp_weg, u2.isp4010.weq_q_out),
		    weadw(&ha->weg->u2.isp4010.weq_q_out));
		pwintk(KEWN_INFO "0x%02X gp_out           = 0x%08X\n",
		    (uint8_t) offsetof(stwuct isp_weg, u2.isp4010.gp_out),
		    weadw(&ha->weg->u2.isp4010.gp_out));
		pwintk(KEWN_INFO "0x%02X gp_in	          = 0x%08X\n",
		    (uint8_t) offsetof(stwuct isp_weg, u2.isp4010.gp_in),
		    weadw(&ha->weg->u2.isp4010.gp_in));
		pwintk(KEWN_INFO "0x%02X powt_eww_status  = 0x%08X\n", (uint8_t)
		    offsetof(stwuct isp_weg, u2.isp4010.powt_eww_status),
		    weadw(&ha->weg->u2.isp4010.powt_eww_status));
	} ewse if (is_qwa4022(ha) | is_qwa4032(ha)) {
		pwintk(KEWN_INFO "Page 0 Wegistews:\n");
		pwintk(KEWN_INFO "0x%02X ext_hw_conf      = 0x%08X\n", (uint8_t)
		    offsetof(stwuct isp_weg, u2.isp4022.p0.ext_hw_conf),
		    weadw(&ha->weg->u2.isp4022.p0.ext_hw_conf));
		pwintk(KEWN_INFO "0x%02X powt_ctww        = 0x%08X\n", (uint8_t)
		    offsetof(stwuct isp_weg, u2.isp4022.p0.powt_ctww),
		    weadw(&ha->weg->u2.isp4022.p0.powt_ctww));
		pwintk(KEWN_INFO "0x%02X powt_status      = 0x%08X\n", (uint8_t)
		    offsetof(stwuct isp_weg, u2.isp4022.p0.powt_status),
		    weadw(&ha->weg->u2.isp4022.p0.powt_status));
		pwintk(KEWN_INFO "0x%02X gp_out           = 0x%08X\n",
		    (uint8_t) offsetof(stwuct isp_weg, u2.isp4022.p0.gp_out),
		    weadw(&ha->weg->u2.isp4022.p0.gp_out));
		pwintk(KEWN_INFO "0x%02X gp_in            = 0x%08X\n",
		    (uint8_t) offsetof(stwuct isp_weg, u2.isp4022.p0.gp_in),
		    weadw(&ha->weg->u2.isp4022.p0.gp_in));
		pwintk(KEWN_INFO "0x%02X powt_eww_status  = 0x%08X\n", (uint8_t)
		    offsetof(stwuct isp_weg, u2.isp4022.p0.powt_eww_status),
		    weadw(&ha->weg->u2.isp4022.p0.powt_eww_status));
		pwintk(KEWN_INFO "Page 1 Wegistews:\n");
		wwitew(HOST_MEM_CFG_PAGE & set_wmask(CSW_SCSI_PAGE_SEWECT),
		    &ha->weg->ctww_status);
		pwintk(KEWN_INFO "0x%02X weq_q_out        = 0x%08X\n",
		    (uint8_t) offsetof(stwuct isp_weg, u2.isp4022.p1.weq_q_out),
		    weadw(&ha->weg->u2.isp4022.p1.weq_q_out));
		wwitew(POWT_CTWW_STAT_PAGE & set_wmask(CSW_SCSI_PAGE_SEWECT),
		    &ha->weg->ctww_status);
	}
}

void qwa4_8xxx_dump_peg_weg(stwuct scsi_qwa_host *ha)
{
	uint32_t hawt_status1, hawt_status2;

	hawt_status1 = qwa4_8xxx_wd_diwect(ha, QWA8XXX_PEG_HAWT_STATUS1);
	hawt_status2 = qwa4_8xxx_wd_diwect(ha, QWA8XXX_PEG_HAWT_STATUS2);

	if (is_qwa8022(ha)) {
		qw4_pwintk(KEWN_INFO, ha,
			   "scsi(%wd): %s, ISP%04x Dumping hw/fw wegistews:\n"
			   " PEG_HAWT_STATUS1: 0x%x, PEG_HAWT_STATUS2: 0x%x,\n"
			   " PEG_NET_0_PC: 0x%x, PEG_NET_1_PC: 0x%x,\n"
			   " PEG_NET_2_PC: 0x%x, PEG_NET_3_PC: 0x%x,\n"
			   " PEG_NET_4_PC: 0x%x\n", ha->host_no, __func__,
			   ha->pdev->device, hawt_status1, hawt_status2,
			   qwa4_82xx_wd_32(ha, QWA82XX_CWB_PEG_NET_0 + 0x3c),
			   qwa4_82xx_wd_32(ha, QWA82XX_CWB_PEG_NET_1 + 0x3c),
			   qwa4_82xx_wd_32(ha, QWA82XX_CWB_PEG_NET_2 + 0x3c),
			   qwa4_82xx_wd_32(ha, QWA82XX_CWB_PEG_NET_3 + 0x3c),
			   qwa4_82xx_wd_32(ha, QWA82XX_CWB_PEG_NET_4 + 0x3c));
	} ewse if (is_qwa8032(ha) || is_qwa8042(ha)) {
		qw4_pwintk(KEWN_INFO, ha,
			   "scsi(%wd): %s, ISP%04x Dumping hw/fw wegistews:\n"
			   " PEG_HAWT_STATUS1: 0x%x, PEG_HAWT_STATUS2: 0x%x,\n",
			   ha->host_no, __func__, ha->pdev->device,
			   hawt_status1, hawt_status2);
	}
}
