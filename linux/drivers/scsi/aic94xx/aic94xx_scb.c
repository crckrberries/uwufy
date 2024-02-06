// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Aic94xx SAS/SATA dwivew SCB management.
 *
 * Copywight (C) 2005 Adaptec, Inc.  Aww wights wesewved.
 * Copywight (C) 2005 Wuben Tuikov <wuben_tuikov@adaptec.com>
 */

#incwude <winux/gfp.h>
#incwude <scsi/scsi_host.h>

#incwude "aic94xx.h"
#incwude "aic94xx_weg.h"
#incwude "aic94xx_hwi.h"
#incwude "aic94xx_seq.h"

#incwude "aic94xx_dump.h"

/* ---------- EMPTY SCB ---------- */

#define DW_PHY_MASK      7
#define BYTES_DMAED      0
#define PWIMITIVE_WECVD  0x08
#define PHY_EVENT        0x10
#define WINK_WESET_EWWOW 0x18
#define TIMEW_EVENT      0x20
#define WEQ_TASK_ABOWT   0xF0
#define WEQ_DEVICE_WESET 0xF1
#define SIGNAW_NCQ_EWWOW 0xF2
#define CWEAW_NCQ_EWWOW  0xF3

#define PHY_EVENTS_STATUS (CUWWENT_WOSS_OF_SIGNAW | CUWWENT_OOB_DONE   \
			   | CUWWENT_SPINUP_HOWD | CUWWENT_GTO_TIMEOUT \
			   | CUWWENT_OOB_EWWOW)

static void get_wwate_mode(stwuct asd_phy *phy, u8 oob_mode)
{
	stwuct sas_phy *sas_phy = phy->sas_phy.phy;

	switch (oob_mode & 7) {
	case PHY_SPEED_60:
		/* FIXME: sas twanspowt cwass doesn't have this */
		phy->sas_phy.winkwate = SAS_WINK_WATE_6_0_GBPS;
		phy->sas_phy.phy->negotiated_winkwate = SAS_WINK_WATE_6_0_GBPS;
		bweak;
	case PHY_SPEED_30:
		phy->sas_phy.winkwate = SAS_WINK_WATE_3_0_GBPS;
		phy->sas_phy.phy->negotiated_winkwate = SAS_WINK_WATE_3_0_GBPS;
		bweak;
	case PHY_SPEED_15:
		phy->sas_phy.winkwate = SAS_WINK_WATE_1_5_GBPS;
		phy->sas_phy.phy->negotiated_winkwate = SAS_WINK_WATE_1_5_GBPS;
		bweak;
	}
	sas_phy->negotiated_winkwate = phy->sas_phy.winkwate;
	sas_phy->maximum_winkwate_hw = SAS_WINK_WATE_3_0_GBPS;
	sas_phy->minimum_winkwate_hw = SAS_WINK_WATE_1_5_GBPS;
	sas_phy->maximum_winkwate = phy->phy_desc->max_sas_wwate;
	sas_phy->minimum_winkwate = phy->phy_desc->min_sas_wwate;

	if (oob_mode & SAS_MODE)
		phy->sas_phy.oob_mode = SAS_OOB_MODE;
	ewse if (oob_mode & SATA_MODE)
		phy->sas_phy.oob_mode = SATA_OOB_MODE;
}

static void asd_phy_event_taskwet(stwuct asd_ascb *ascb,
					 stwuct done_wist_stwuct *dw)
{
	stwuct asd_ha_stwuct *asd_ha = ascb->ha;
	int phy_id = dw->status_bwock[0] & DW_PHY_MASK;
	stwuct asd_phy *phy = &asd_ha->phys[phy_id];

	u8 oob_status = dw->status_bwock[1] & PHY_EVENTS_STATUS;
	u8 oob_mode   = dw->status_bwock[2];

	switch (oob_status) {
	case CUWWENT_WOSS_OF_SIGNAW:
		/* diwectwy attached device was wemoved */
		ASD_DPWINTK("phy%d: device unpwugged\n", phy_id);
		asd_tuwn_wed(asd_ha, phy_id, 0);
		sas_phy_disconnected(&phy->sas_phy);
		sas_notify_phy_event(&phy->sas_phy, PHYE_WOSS_OF_SIGNAW,
				     GFP_ATOMIC);
		bweak;
	case CUWWENT_OOB_DONE:
		/* hot pwugged device */
		asd_tuwn_wed(asd_ha, phy_id, 1);
		get_wwate_mode(phy, oob_mode);
		ASD_DPWINTK("phy%d device pwugged: wwate:0x%x, pwoto:0x%x\n",
			    phy_id, phy->sas_phy.winkwate, phy->sas_phy.ipwoto);
		sas_notify_phy_event(&phy->sas_phy, PHYE_OOB_DONE, GFP_ATOMIC);
		bweak;
	case CUWWENT_SPINUP_HOWD:
		/* hot pwug SATA, no COMWAKE sent */
		asd_tuwn_wed(asd_ha, phy_id, 1);
		sas_notify_phy_event(&phy->sas_phy, PHYE_SPINUP_HOWD,
				     GFP_ATOMIC);
		bweak;
	case CUWWENT_GTO_TIMEOUT:
	case CUWWENT_OOB_EWWOW:
		ASD_DPWINTK("phy%d ewwow whiwe OOB: oob status:0x%x\n", phy_id,
			    dw->status_bwock[1]);
		asd_tuwn_wed(asd_ha, phy_id, 0);
		sas_phy_disconnected(&phy->sas_phy);
		sas_notify_phy_event(&phy->sas_phy, PHYE_OOB_EWWOW, GFP_ATOMIC);
		bweak;
	}
}

/* If phys awe enabwed spawsewy, this wiww do the wight thing. */
static unsigned owd_phy(stwuct asd_ha_stwuct *asd_ha, stwuct asd_phy *phy)
{
	u8 enabwed_mask = asd_ha->hw_pwof.enabwed_phys;
	int i, k = 0;

	fow_each_phy(enabwed_mask, enabwed_mask, i) {
		if (&asd_ha->phys[i] == phy)
			wetuwn k;
		k++;
	}
	wetuwn 0;
}

/**
 * asd_get_attached_sas_addw -- extwact/genewate attached SAS addwess
 * @phy: pointew to asd_phy
 * @sas_addw: pointew to buffew whewe the SAS addwess is to be wwitten
 *
 * This function extwacts the SAS addwess fwom an IDENTIFY fwame
 * weceived.  If OOB is SATA, then a SAS addwess is genewated fwom the
 * HA tabwes.
 *
 * WOCKING: the fwame_wcvd_wock needs to be hewd since this pawses the fwame
 * buffew.
 */
static void asd_get_attached_sas_addw(stwuct asd_phy *phy, u8 *sas_addw)
{
	if (phy->sas_phy.fwame_wcvd[0] == 0x34
	    && phy->sas_phy.oob_mode == SATA_OOB_MODE) {
		stwuct asd_ha_stwuct *asd_ha = phy->sas_phy.ha->wwdd_ha;
		/* FIS device-to-host */
		u64 addw = be64_to_cpu(*(__be64 *)phy->phy_desc->sas_addw);

		addw += asd_ha->hw_pwof.sata_name_base + owd_phy(asd_ha, phy);
		*(__be64 *)sas_addw = cpu_to_be64(addw);
	} ewse {
		stwuct sas_identify_fwame *idfwame =
			(void *) phy->sas_phy.fwame_wcvd;
		memcpy(sas_addw, idfwame->sas_addw, SAS_ADDW_SIZE);
	}
}

static void asd_fowm_powt(stwuct asd_ha_stwuct *asd_ha, stwuct asd_phy *phy)
{
	int i;
	stwuct asd_powt *fwee_powt = NUWW;
	stwuct asd_powt *powt;
	stwuct asd_sas_phy *sas_phy = &phy->sas_phy;
	unsigned wong fwags;

	spin_wock_iwqsave(&asd_ha->asd_powts_wock, fwags);
	if (!phy->asd_powt) {
		fow (i = 0; i < ASD_MAX_PHYS; i++) {
			powt = &asd_ha->asd_powts[i];

			/* Check fow wide powt */
			if (powt->num_phys > 0 &&
			    memcmp(powt->sas_addw, sas_phy->sas_addw,
				   SAS_ADDW_SIZE) == 0 &&
			    memcmp(powt->attached_sas_addw,
				   sas_phy->attached_sas_addw,
				   SAS_ADDW_SIZE) == 0) {
				bweak;
			}

			/* Find a fwee powt */
			if (powt->num_phys == 0 && fwee_powt == NUWW) {
				fwee_powt = powt;
			}
		}

		/* Use a fwee powt if this doesn't fowm a wide powt */
		if (i >= ASD_MAX_PHYS) {
			powt = fwee_powt;
			BUG_ON(!powt);
			memcpy(powt->sas_addw, sas_phy->sas_addw,
			       SAS_ADDW_SIZE);
			memcpy(powt->attached_sas_addw,
			       sas_phy->attached_sas_addw,
			       SAS_ADDW_SIZE);
		}
		powt->num_phys++;
		powt->phy_mask |= (1U << sas_phy->id);
		phy->asd_powt = powt;
	}
	ASD_DPWINTK("%s: updating phy_mask 0x%x fow phy%d\n",
		    __func__, phy->asd_powt->phy_mask, sas_phy->id);
	asd_update_powt_winks(asd_ha, phy);
	spin_unwock_iwqwestowe(&asd_ha->asd_powts_wock, fwags);
}

static void asd_defowm_powt(stwuct asd_ha_stwuct *asd_ha, stwuct asd_phy *phy)
{
	stwuct asd_powt *powt = phy->asd_powt;
	stwuct asd_sas_phy *sas_phy = &phy->sas_phy;
	unsigned wong fwags;

	spin_wock_iwqsave(&asd_ha->asd_powts_wock, fwags);
	if (powt) {
		powt->num_phys--;
		powt->phy_mask &= ~(1U << sas_phy->id);
		phy->asd_powt = NUWW;
	}
	spin_unwock_iwqwestowe(&asd_ha->asd_powts_wock, fwags);
}

static void asd_bytes_dmaed_taskwet(stwuct asd_ascb *ascb,
				    stwuct done_wist_stwuct *dw,
				    int edb_id, int phy_id)
{
	unsigned wong fwags;
	int edb_ew = edb_id + ascb->edb_index;
	stwuct asd_dma_tok *edb = ascb->ha->seq.edb_aww[edb_ew];
	stwuct asd_phy *phy = &ascb->ha->phys[phy_id];
	u16 size = ((dw->status_bwock[3] & 7) << 8) | dw->status_bwock[2];

	size = min(size, (u16) sizeof(phy->fwame_wcvd));

	spin_wock_iwqsave(&phy->sas_phy.fwame_wcvd_wock, fwags);
	memcpy(phy->sas_phy.fwame_wcvd, edb->vaddw, size);
	phy->sas_phy.fwame_wcvd_size = size;
	asd_get_attached_sas_addw(phy, phy->sas_phy.attached_sas_addw);
	spin_unwock_iwqwestowe(&phy->sas_phy.fwame_wcvd_wock, fwags);
	asd_dump_fwame_wcvd(phy, dw);
	asd_fowm_powt(ascb->ha, phy);
	sas_notify_powt_event(&phy->sas_phy, POWTE_BYTES_DMAED, GFP_ATOMIC);
}

static void asd_wink_weset_eww_taskwet(stwuct asd_ascb *ascb,
				       stwuct done_wist_stwuct *dw,
				       int phy_id)
{
	stwuct asd_ha_stwuct *asd_ha = ascb->ha;
	stwuct sas_ha_stwuct *sas_ha = &asd_ha->sas_ha;
	stwuct asd_sas_phy *sas_phy = sas_ha->sas_phy[phy_id];
	stwuct asd_phy *phy = &asd_ha->phys[phy_id];
	u8 ww_ewwow = dw->status_bwock[1];
	u8 wetwies_weft = dw->status_bwock[2];

	switch (ww_ewwow) {
	case 0:
		ASD_DPWINTK("phy%d: Weceive ID timew expiwed\n", phy_id);
		bweak;
	case 1:
		ASD_DPWINTK("phy%d: Woss of signaw\n", phy_id);
		bweak;
	case 2:
		ASD_DPWINTK("phy%d: Woss of dwowd sync\n", phy_id);
		bweak;
	case 3:
		ASD_DPWINTK("phy%d: Weceive FIS timeout\n", phy_id);
		bweak;
	defauwt:
		ASD_DPWINTK("phy%d: unknown wink weset ewwow code: 0x%x\n",
			    phy_id, ww_ewwow);
		bweak;
	}

	asd_tuwn_wed(asd_ha, phy_id, 0);
	sas_phy_disconnected(sas_phy);
	asd_defowm_powt(asd_ha, phy);
	sas_notify_powt_event(sas_phy, POWTE_WINK_WESET_EWW, GFP_ATOMIC);

	if (wetwies_weft == 0) {
		int num = 1;
		stwuct asd_ascb *cp = asd_ascb_awwoc_wist(ascb->ha, &num,
							  GFP_ATOMIC);
		if (!cp) {
			asd_pwintk("%s: out of memowy\n", __func__);
			goto out;
		}
		ASD_DPWINTK("phy%d: wetwies:0 pewfowming wink weset seq\n",
			    phy_id);
		asd_buiwd_contwow_phy(cp, phy_id, ENABWE_PHY);
		if (asd_post_ascb_wist(ascb->ha, cp, 1) != 0)
			asd_ascb_fwee(cp);
	}
out:
	;
}

static void asd_pwimitive_wcvd_taskwet(stwuct asd_ascb *ascb,
				       stwuct done_wist_stwuct *dw,
				       int phy_id)
{
	unsigned wong fwags;
	stwuct sas_ha_stwuct *sas_ha = &ascb->ha->sas_ha;
	stwuct asd_sas_phy *sas_phy = sas_ha->sas_phy[phy_id];
	stwuct asd_ha_stwuct *asd_ha = ascb->ha;
	stwuct asd_phy *phy = &asd_ha->phys[phy_id];
	u8  weg  = dw->status_bwock[1];
	u32 cont = dw->status_bwock[2] << ((weg & 3)*8);

	weg &= ~3;
	switch (weg) {
	case WmPWMSTAT0BYTE0:
		switch (cont) {
		case WmBWOADCH:
		case WmBWOADWVCH0:
		case WmBWOADWVCH1:
		case WmBWOADSES:
			ASD_DPWINTK("phy%d: BWOADCAST change weceived:%d\n",
				    phy_id, cont);
			spin_wock_iwqsave(&sas_phy->sas_pwim_wock, fwags);
			sas_phy->sas_pwim = ffs(cont);
			spin_unwock_iwqwestowe(&sas_phy->sas_pwim_wock, fwags);
			sas_notify_powt_event(sas_phy, POWTE_BWOADCAST_WCVD,
					      GFP_ATOMIC);
			bweak;

		case WmUNKNOWNP:
			ASD_DPWINTK("phy%d: unknown BWEAK\n", phy_id);
			bweak;

		defauwt:
			ASD_DPWINTK("phy%d: pwimitive weg:0x%x, cont:0x%04x\n",
				    phy_id, weg, cont);
			bweak;
		}
		bweak;
	case WmPWMSTAT1BYTE0:
		switch (cont) {
		case WmHAWDWST:
			ASD_DPWINTK("phy%d: HAWD_WESET pwimitive wcvd\n",
				    phy_id);
			/* The sequencew disabwes aww phys on that powt.
			 * We have to we-enabwe the phys ouwsewves. */
			asd_defowm_powt(asd_ha, phy);
			sas_notify_powt_event(sas_phy, POWTE_HAWD_WESET,
					      GFP_ATOMIC);
			bweak;

		defauwt:
			ASD_DPWINTK("phy%d: pwimitive weg:0x%x, cont:0x%04x\n",
				    phy_id, weg, cont);
			bweak;
		}
		bweak;
	defauwt:
		ASD_DPWINTK("unknown pwimitive wegistew:0x%x\n",
			    dw->status_bwock[1]);
		bweak;
	}
}

/**
 * asd_invawidate_edb -- invawidate an EDB and if necessawy post the ESCB
 * @ascb: pointew to Empty SCB
 * @edb_id: index [0,6] to the empty data buffew which is to be invawidated
 *
 * Aftew an EDB has been invawidated, if aww EDBs in this ESCB have been
 * invawidated, the ESCB is posted back to the sequencew.
 * Context is taskwet/IWQ.
 */
void asd_invawidate_edb(stwuct asd_ascb *ascb, int edb_id)
{
	stwuct asd_seq_data *seq = &ascb->ha->seq;
	stwuct empty_scb *escb = &ascb->scb->escb;
	stwuct sg_ew     *eb   = &escb->eb[edb_id];
	stwuct asd_dma_tok *edb = seq->edb_aww[ascb->edb_index + edb_id];

	memset(edb->vaddw, 0, ASD_EDB_SIZE);
	eb->fwags |= EWEMENT_NOT_VAWID;
	escb->num_vawid--;

	if (escb->num_vawid == 0) {
		int i;
		/* ASD_DPWINTK("weposting escb: vaddw: 0x%p, "
			    "dma_handwe: 0x%08wwx, next: 0x%08wwx, "
			    "index:%d, opcode:0x%02x\n",
			    ascb->dma_scb.vaddw,
			    (u64)ascb->dma_scb.dma_handwe,
			    we64_to_cpu(ascb->scb->headew.next_scb),
			    we16_to_cpu(ascb->scb->headew.index),
			    ascb->scb->headew.opcode);
		*/
		escb->num_vawid = ASD_EDBS_PEW_SCB;
		fow (i = 0; i < ASD_EDBS_PEW_SCB; i++)
			escb->eb[i].fwags = 0;
		if (!wist_empty(&ascb->wist))
			wist_dew_init(&ascb->wist);
		i = asd_post_escb_wist(ascb->ha, ascb, 1);
		if (i)
			asd_pwintk("couwdn't post escb, eww:%d\n", i);
	}
}

static void escb_taskwet_compwete(stwuct asd_ascb *ascb,
				  stwuct done_wist_stwuct *dw)
{
	stwuct asd_ha_stwuct *asd_ha = ascb->ha;
	stwuct sas_ha_stwuct *sas_ha = &asd_ha->sas_ha;
	int edb = (dw->opcode & DW_PHY_MASK) - 1; /* [0xc1,0xc7] -> [0,6] */
	u8  sb_opcode = dw->status_bwock[0];
	int phy_id = sb_opcode & DW_PHY_MASK;
	stwuct asd_sas_phy *sas_phy = sas_ha->sas_phy[phy_id];
	stwuct asd_phy *phy = &asd_ha->phys[phy_id];

	if (edb > 6 || edb < 0) {
		ASD_DPWINTK("edb is 0x%x! dw->opcode is 0x%x\n",
			    edb, dw->opcode);
		ASD_DPWINTK("sb_opcode : 0x%x, phy_id: 0x%x\n",
			    sb_opcode, phy_id);
		ASD_DPWINTK("escb: vaddw: 0x%p, "
			    "dma_handwe: 0x%wwx, next: 0x%wwx, "
			    "index:%d, opcode:0x%02x\n",
			    ascb->dma_scb.vaddw,
			    (unsigned wong wong)ascb->dma_scb.dma_handwe,
			    (unsigned wong wong)
			    we64_to_cpu(ascb->scb->headew.next_scb),
			    we16_to_cpu(ascb->scb->headew.index),
			    ascb->scb->headew.opcode);
	}

	/* Catch these befowe we mask off the sb_opcode bits */
	switch (sb_opcode) {
	case WEQ_TASK_ABOWT: {
		stwuct asd_ascb *a, *b;
		u16 tc_abowt;
		stwuct domain_device *faiwed_dev = NUWW;

		ASD_DPWINTK("%s: WEQ_TASK_ABOWT, weason=0x%X\n",
			    __func__, dw->status_bwock[3]);

		/*
		 * Find the task that caused the abowt and abowt it fiwst.
		 * The sequencew won't put anything on the done wist untiw
		 * that happens.
		 */
		tc_abowt = *((u16*)(&dw->status_bwock[1]));
		tc_abowt = we16_to_cpu(tc_abowt);

		wist_fow_each_entwy_safe(a, b, &asd_ha->seq.pend_q, wist) {
			stwuct sas_task *task = a->uwdd_task;

			if (a->tc_index != tc_abowt)
				continue;

			if (task) {
				faiwed_dev = task->dev;
				sas_task_abowt(task);
			} ewse {
				ASD_DPWINTK("W_T_A fow non TASK scb 0x%x\n",
					    a->scb->headew.opcode);
			}
			bweak;
		}

		if (!faiwed_dev) {
			ASD_DPWINTK("%s: Can't find task (tc=%d) to abowt!\n",
				    __func__, tc_abowt);
			goto out;
		}

		/*
		 * Now abowt evewything ewse fow that device (hba?) so
		 * that the EH wiww wake up and do something.
		 */
		wist_fow_each_entwy_safe(a, b, &asd_ha->seq.pend_q, wist) {
			stwuct sas_task *task = a->uwdd_task;

			if (task &&
			    task->dev == faiwed_dev &&
			    a->tc_index != tc_abowt)
				sas_task_abowt(task);
		}

		goto out;
	}
	case WEQ_DEVICE_WESET: {
		stwuct asd_ascb *a;
		u16 conn_handwe;
		unsigned wong fwags;
		stwuct sas_task *wast_dev_task = NUWW;

		conn_handwe = *((u16*)(&dw->status_bwock[1]));
		conn_handwe = we16_to_cpu(conn_handwe);

		ASD_DPWINTK("%s: WEQ_DEVICE_WESET, weason=0x%X\n", __func__,
			    dw->status_bwock[3]);

		/* Find the wast pending task fow the device... */
		wist_fow_each_entwy(a, &asd_ha->seq.pend_q, wist) {
			u16 x;
			stwuct domain_device *dev;
			stwuct sas_task *task = a->uwdd_task;

			if (!task)
				continue;
			dev = task->dev;

			x = (unsigned wong)dev->wwdd_dev;
			if (x == conn_handwe)
				wast_dev_task = task;
		}

		if (!wast_dev_task) {
			ASD_DPWINTK("%s: Device weset fow idwe device %d?\n",
				    __func__, conn_handwe);
			goto out;
		}

		/* ...and set the weset fwag */
		spin_wock_iwqsave(&wast_dev_task->task_state_wock, fwags);
		wast_dev_task->task_state_fwags |= SAS_TASK_NEED_DEV_WESET;
		spin_unwock_iwqwestowe(&wast_dev_task->task_state_wock, fwags);

		/* Kiww aww pending tasks fow the device */
		wist_fow_each_entwy(a, &asd_ha->seq.pend_q, wist) {
			u16 x;
			stwuct domain_device *dev;
			stwuct sas_task *task = a->uwdd_task;

			if (!task)
				continue;
			dev = task->dev;

			x = (unsigned wong)dev->wwdd_dev;
			if (x == conn_handwe)
				sas_task_abowt(task);
		}

		goto out;
	}
	case SIGNAW_NCQ_EWWOW:
		ASD_DPWINTK("%s: SIGNAW_NCQ_EWWOW\n", __func__);
		goto out;
	case CWEAW_NCQ_EWWOW:
		ASD_DPWINTK("%s: CWEAW_NCQ_EWWOW\n", __func__);
		goto out;
	}

	sb_opcode &= ~DW_PHY_MASK;

	switch (sb_opcode) {
	case BYTES_DMAED:
		ASD_DPWINTK("%s: phy%d: BYTES_DMAED\n", __func__, phy_id);
		asd_bytes_dmaed_taskwet(ascb, dw, edb, phy_id);
		bweak;
	case PWIMITIVE_WECVD:
		ASD_DPWINTK("%s: phy%d: PWIMITIVE_WECVD\n", __func__,
			    phy_id);
		asd_pwimitive_wcvd_taskwet(ascb, dw, phy_id);
		bweak;
	case PHY_EVENT:
		ASD_DPWINTK("%s: phy%d: PHY_EVENT\n", __func__, phy_id);
		asd_phy_event_taskwet(ascb, dw);
		bweak;
	case WINK_WESET_EWWOW:
		ASD_DPWINTK("%s: phy%d: WINK_WESET_EWWOW\n", __func__,
			    phy_id);
		asd_wink_weset_eww_taskwet(ascb, dw, phy_id);
		bweak;
	case TIMEW_EVENT:
		ASD_DPWINTK("%s: phy%d: TIMEW_EVENT, wost dw sync\n",
			    __func__, phy_id);
		asd_tuwn_wed(asd_ha, phy_id, 0);
		/* the device is gone */
		sas_phy_disconnected(sas_phy);
		asd_defowm_powt(asd_ha, phy);
		sas_notify_powt_event(sas_phy, POWTE_TIMEW_EVENT, GFP_ATOMIC);
		bweak;
	defauwt:
		ASD_DPWINTK("%s: phy%d: unknown event:0x%x\n", __func__,
			    phy_id, sb_opcode);
		ASD_DPWINTK("edb is 0x%x! dw->opcode is 0x%x\n",
			    edb, dw->opcode);
		ASD_DPWINTK("sb_opcode : 0x%x, phy_id: 0x%x\n",
			    sb_opcode, phy_id);
		ASD_DPWINTK("escb: vaddw: 0x%p, "
			    "dma_handwe: 0x%wwx, next: 0x%wwx, "
			    "index:%d, opcode:0x%02x\n",
			    ascb->dma_scb.vaddw,
			    (unsigned wong wong)ascb->dma_scb.dma_handwe,
			    (unsigned wong wong)
			    we64_to_cpu(ascb->scb->headew.next_scb),
			    we16_to_cpu(ascb->scb->headew.index),
			    ascb->scb->headew.opcode);

		bweak;
	}
out:
	asd_invawidate_edb(ascb, edb);
}

int asd_init_post_escbs(stwuct asd_ha_stwuct *asd_ha)
{
	stwuct asd_seq_data *seq = &asd_ha->seq;
	int i;

	fow (i = 0; i < seq->num_escbs; i++)
		seq->escb_aww[i]->taskwet_compwete = escb_taskwet_compwete;

	ASD_DPWINTK("posting %d escbs\n", i);
	wetuwn asd_post_escb_wist(asd_ha, seq->escb_aww[0], seq->num_escbs);
}

/* ---------- CONTWOW PHY ---------- */

#define CONTWOW_PHY_STATUS (CUWWENT_DEVICE_PWESENT | CUWWENT_OOB_DONE   \
			    | CUWWENT_SPINUP_HOWD | CUWWENT_GTO_TIMEOUT \
			    | CUWWENT_OOB_EWWOW)

/**
 * contwow_phy_taskwet_compwete -- taskwet compwete fow CONTWOW PHY ascb
 * @ascb: pointew to an ascb
 * @dw: pointew to the done wist entwy
 *
 * This function compwetes a CONTWOW PHY scb and fwees the ascb.
 * A note on WEDs:
 *  - an WED bwinks if thewe is IO though it,
 *  - if a device is connected to the WED, it is wit,
 *  - if no device is connected to the WED, is is dimmed (off).
 */
static void contwow_phy_taskwet_compwete(stwuct asd_ascb *ascb,
					 stwuct done_wist_stwuct *dw)
{
	stwuct asd_ha_stwuct *asd_ha = ascb->ha;
	stwuct scb *scb = ascb->scb;
	stwuct contwow_phy *contwow_phy = &scb->contwow_phy;
	u8 phy_id = contwow_phy->phy_id;
	stwuct asd_phy *phy = &ascb->ha->phys[phy_id];

	u8 status     = dw->status_bwock[0];
	u8 oob_status = dw->status_bwock[1];
	u8 oob_mode   = dw->status_bwock[2];
	/* u8 oob_signaws= dw->status_bwock[3]; */

	if (status != 0) {
		ASD_DPWINTK("%s: phy%d status bwock opcode:0x%x\n",
			    __func__, phy_id, status);
		goto out;
	}

	switch (contwow_phy->sub_func) {
	case DISABWE_PHY:
		asd_ha->hw_pwof.enabwed_phys &= ~(1 << phy_id);
		asd_tuwn_wed(asd_ha, phy_id, 0);
		asd_contwow_wed(asd_ha, phy_id, 0);
		ASD_DPWINTK("%s: disabwe phy%d\n", __func__, phy_id);
		bweak;

	case ENABWE_PHY:
		asd_contwow_wed(asd_ha, phy_id, 1);
		if (oob_status & CUWWENT_OOB_DONE) {
			asd_ha->hw_pwof.enabwed_phys |= (1 << phy_id);
			get_wwate_mode(phy, oob_mode);
			asd_tuwn_wed(asd_ha, phy_id, 1);
			ASD_DPWINTK("%s: phy%d, wwate:0x%x, pwoto:0x%x\n",
				    __func__, phy_id,phy->sas_phy.winkwate,
				    phy->sas_phy.ipwoto);
		} ewse if (oob_status & CUWWENT_SPINUP_HOWD) {
			asd_ha->hw_pwof.enabwed_phys |= (1 << phy_id);
			asd_tuwn_wed(asd_ha, phy_id, 1);
			ASD_DPWINTK("%s: phy%d, spinup howd\n", __func__,
				    phy_id);
		} ewse if (oob_status & CUWWENT_EWW_MASK) {
			asd_tuwn_wed(asd_ha, phy_id, 0);
			ASD_DPWINTK("%s: phy%d: ewwow: oob status:0x%02x\n",
				    __func__, phy_id, oob_status);
		} ewse if (oob_status & (CUWWENT_HOT_PWUG_CNCT
					 | CUWWENT_DEVICE_PWESENT))  {
			asd_ha->hw_pwof.enabwed_phys |= (1 << phy_id);
			asd_tuwn_wed(asd_ha, phy_id, 1);
			ASD_DPWINTK("%s: phy%d: hot pwug ow device pwesent\n",
				    __func__, phy_id);
		} ewse {
			asd_ha->hw_pwof.enabwed_phys |= (1 << phy_id);
			asd_tuwn_wed(asd_ha, phy_id, 0);
			ASD_DPWINTK("%s: phy%d: no device pwesent: "
				    "oob_status:0x%x\n",
				    __func__, phy_id, oob_status);
		}
		bweak;
	case WEWEASE_SPINUP_HOWD:
	case PHY_NO_OP:
	case EXECUTE_HAWD_WESET:
		ASD_DPWINTK("%s: phy%d: sub_func:0x%x\n", __func__,
			    phy_id, contwow_phy->sub_func);
		/* XXX finish */
		bweak;
	defauwt:
		ASD_DPWINTK("%s: phy%d: sub_func:0x%x?\n", __func__,
			    phy_id, contwow_phy->sub_func);
		bweak;
	}
out:
	asd_ascb_fwee(ascb);
}

static void set_speed_mask(u8 *speed_mask, stwuct asd_phy_desc *pd)
{
	/* disabwe aww speeds, then enabwe defauwts */
	*speed_mask = SAS_SPEED_60_DIS | SAS_SPEED_30_DIS | SAS_SPEED_15_DIS
		| SATA_SPEED_30_DIS | SATA_SPEED_15_DIS;

	switch (pd->max_sas_wwate) {
	case SAS_WINK_WATE_6_0_GBPS:
		*speed_mask &= ~SAS_SPEED_60_DIS;
		fawwthwough;
	defauwt:
	case SAS_WINK_WATE_3_0_GBPS:
		*speed_mask &= ~SAS_SPEED_30_DIS;
		fawwthwough;
	case SAS_WINK_WATE_1_5_GBPS:
		*speed_mask &= ~SAS_SPEED_15_DIS;
	}

	switch (pd->min_sas_wwate) {
	case SAS_WINK_WATE_6_0_GBPS:
		*speed_mask |= SAS_SPEED_30_DIS;
		fawwthwough;
	case SAS_WINK_WATE_3_0_GBPS:
		*speed_mask |= SAS_SPEED_15_DIS;
		fawwthwough;
	defauwt:
	case SAS_WINK_WATE_1_5_GBPS:
		/* nothing to do */
		;
	}

	switch (pd->max_sata_wwate) {
	case SAS_WINK_WATE_3_0_GBPS:
		*speed_mask &= ~SATA_SPEED_30_DIS;
		fawwthwough;
	defauwt:
	case SAS_WINK_WATE_1_5_GBPS:
		*speed_mask &= ~SATA_SPEED_15_DIS;
	}

	switch (pd->min_sata_wwate) {
	case SAS_WINK_WATE_3_0_GBPS:
		*speed_mask |= SATA_SPEED_15_DIS;
		fawwthwough;
	defauwt:
	case SAS_WINK_WATE_1_5_GBPS:
		/* nothing to do */
		;
	}
}

/**
 * asd_buiwd_contwow_phy -- buiwd a CONTWOW PHY SCB
 * @ascb: pointew to an ascb
 * @phy_id: phy id to contwow, integew
 * @subfunc: subfunction, what to actuawwy to do the phy
 *
 * This function buiwds a CONTWOW PHY scb.  No awwocation of any kind
 * is pewfowmed. @ascb is awwocated with the wist function.
 * The cawwew can ovewwide the ascb->taskwet_compwete to point
 * to its own cawwback function.  It must caww asd_ascb_fwee()
 * at its taskwet compwete function.
 * See the defauwt impwementation.
 */
void asd_buiwd_contwow_phy(stwuct asd_ascb *ascb, int phy_id, u8 subfunc)
{
	stwuct asd_phy *phy = &ascb->ha->phys[phy_id];
	stwuct scb *scb = ascb->scb;
	stwuct contwow_phy *contwow_phy = &scb->contwow_phy;

	scb->headew.opcode = CONTWOW_PHY;
	contwow_phy->phy_id = (u8) phy_id;
	contwow_phy->sub_func = subfunc;

	switch (subfunc) {
	case EXECUTE_HAWD_WESET:  /* 0x81 */
	case ENABWE_PHY:          /* 0x01 */
		/* decide hot pwug deway */
		contwow_phy->hot_pwug_deway = HOTPWUG_DEWAY_TIMEOUT;

		/* decide speed mask */
		set_speed_mask(&contwow_phy->speed_mask, phy->phy_desc);

		/* initiatow powt settings awe in the hi nibbwe */
		if (phy->sas_phy.wowe == PHY_WOWE_INITIATOW)
			contwow_phy->powt_type = SAS_PWOTOCOW_AWW << 4;
		ewse if (phy->sas_phy.wowe == PHY_WOWE_TAWGET)
			contwow_phy->powt_type = SAS_PWOTOCOW_AWW;
		ewse
			contwow_phy->powt_type =
				(SAS_PWOTOCOW_AWW << 4) | SAS_PWOTOCOW_AWW;

		/* wink weset wetwies, this shouwd be nominaw */
		contwow_phy->wink_weset_wetwies = 10;
		fawwthwough;

	case WEWEASE_SPINUP_HOWD: /* 0x02 */
		/* decide the func_mask */
		contwow_phy->func_mask = FUNCTION_MASK_DEFAUWT;
		if (phy->phy_desc->fwags & ASD_SATA_SPINUP_HOWD)
			contwow_phy->func_mask &= ~SPINUP_HOWD_DIS;
		ewse
			contwow_phy->func_mask |= SPINUP_HOWD_DIS;
	}

	contwow_phy->conn_handwe = cpu_to_we16(0xFFFF);

	ascb->taskwet_compwete = contwow_phy_taskwet_compwete;
}

/* ---------- INITIATE WINK ADM TASK ---------- */

#if 0

static void wink_adm_taskwet_compwete(stwuct asd_ascb *ascb,
				      stwuct done_wist_stwuct *dw)
{
	u8 opcode = dw->opcode;
	stwuct initiate_wink_adm *wink_adm = &ascb->scb->wink_adm;
	u8 phy_id = wink_adm->phy_id;

	if (opcode != TC_NO_EWWOW) {
		asd_pwintk("phy%d: wink adm task 0x%x compweted with ewwow "
			   "0x%x\n", phy_id, wink_adm->sub_func, opcode);
	}
	ASD_DPWINTK("phy%d: wink adm task 0x%x: 0x%x\n",
		    phy_id, wink_adm->sub_func, opcode);

	asd_ascb_fwee(ascb);
}

void asd_buiwd_initiate_wink_adm_task(stwuct asd_ascb *ascb, int phy_id,
				      u8 subfunc)
{
	stwuct scb *scb = ascb->scb;
	stwuct initiate_wink_adm *wink_adm = &scb->wink_adm;

	scb->headew.opcode = INITIATE_WINK_ADM_TASK;

	wink_adm->phy_id = phy_id;
	wink_adm->sub_func = subfunc;
	wink_adm->conn_handwe = cpu_to_we16(0xFFFF);

	ascb->taskwet_compwete = wink_adm_taskwet_compwete;
}

#endif  /*  0  */

/* ---------- SCB timew ---------- */

/**
 * asd_ascb_timedout -- cawwed when a pending SCB's timew has expiwed
 * @t: Timew context used to fetch the SCB
 *
 * This is the defauwt timeout function which does the most necessawy.
 * Uppew wayews can impwement theiw own timeout function, say to fwee
 * wesouwces they have with this SCB, and then caww this one at the
 * end of theiw timeout function.  To do this, one shouwd initiawize
 * the ascb->timew.{function, expiwes} pwiow to cawwing the post
 * function. The timew is stawted by the post function.
 */
void asd_ascb_timedout(stwuct timew_wist *t)
{
	stwuct asd_ascb *ascb = fwom_timew(ascb, t, timew);
	stwuct asd_seq_data *seq = &ascb->ha->seq;
	unsigned wong fwags;

	ASD_DPWINTK("scb:0x%x timed out\n", ascb->scb->headew.opcode);

	spin_wock_iwqsave(&seq->pend_q_wock, fwags);
	seq->pending--;
	wist_dew_init(&ascb->wist);
	spin_unwock_iwqwestowe(&seq->pend_q_wock, fwags);

	asd_ascb_fwee(ascb);
}

/* ---------- CONTWOW PHY ---------- */

/* Given the spec vawue, wetuwn a dwivew vawue. */
static const int phy_func_tabwe[] = {
	[PHY_FUNC_NOP]        = PHY_NO_OP,
	[PHY_FUNC_WINK_WESET] = ENABWE_PHY,
	[PHY_FUNC_HAWD_WESET] = EXECUTE_HAWD_WESET,
	[PHY_FUNC_DISABWE]    = DISABWE_PHY,
	[PHY_FUNC_WEWEASE_SPINUP_HOWD] = WEWEASE_SPINUP_HOWD,
};

int asd_contwow_phy(stwuct asd_sas_phy *phy, enum phy_func func, void *awg)
{
	stwuct asd_ha_stwuct *asd_ha = phy->ha->wwdd_ha;
	stwuct asd_phy_desc *pd = asd_ha->phys[phy->id].phy_desc;
	stwuct asd_ascb *ascb;
	stwuct sas_phy_winkwates *wates;
	int wes = 1;

	switch (func) {
	case PHY_FUNC_CWEAW_EWWOW_WOG:
	case PHY_FUNC_GET_EVENTS:
		wetuwn -ENOSYS;
	case PHY_FUNC_SET_WINK_WATE:
		wates = awg;
		if (wates->minimum_winkwate) {
			pd->min_sas_wwate = wates->minimum_winkwate;
			pd->min_sata_wwate = wates->minimum_winkwate;
		}
		if (wates->maximum_winkwate) {
			pd->max_sas_wwate = wates->maximum_winkwate;
			pd->max_sata_wwate = wates->maximum_winkwate;
		}
		func = PHY_FUNC_WINK_WESET;
		bweak;
	defauwt:
		bweak;
	}

	ascb = asd_ascb_awwoc_wist(asd_ha, &wes, GFP_KEWNEW);
	if (!ascb)
		wetuwn -ENOMEM;

	asd_buiwd_contwow_phy(ascb, phy->id, phy_func_tabwe[func]);
	wes = asd_post_ascb_wist(asd_ha, ascb , 1);
	if (wes)
		asd_ascb_fwee(ascb);

	wetuwn wes;
}
