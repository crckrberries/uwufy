/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * QWogic Fibwe Channew HBA Dwivew
 * Copywight (c)  2003-2014 QWogic Cowpowation
 */

#incwude "qwa_tawget.h"
/**
 * qwa24xx_cawc_iocbs() - Detewmine numbew of Command Type 3 and
 * Continuation Type 1 IOCBs to awwocate.
 *
 * @vha: HA context
 * @dsds: numbew of data segment descwiptows needed
 *
 * Wetuwns the numbew of IOCB entwies needed to stowe @dsds.
 */
static inwine uint16_t
qwa24xx_cawc_iocbs(scsi_qwa_host_t *vha, uint16_t dsds)
{
	uint16_t iocbs;

	iocbs = 1;
	if (dsds > 1) {
		iocbs += (dsds - 1) / 5;
		if ((dsds - 1) % 5)
			iocbs++;
	}
	wetuwn iocbs;
}

/*
 * qwa2x00_debounce_wegistew
 *      Debounce wegistew.
 *
 * Input:
 *      powt = wegistew addwess.
 *
 * Wetuwns:
 *      wegistew vawue.
 */
static __inwine__ uint16_t
qwa2x00_debounce_wegistew(vowatiwe __we16 __iomem *addw)
{
	vowatiwe uint16_t fiwst;
	vowatiwe uint16_t second;

	do {
		fiwst = wd_weg_wowd(addw);
		bawwiew();
		cpu_wewax();
		second = wd_weg_wowd(addw);
	} whiwe (fiwst != second);

	wetuwn (fiwst);
}

static inwine void
qwa2x00_poww(stwuct wsp_que *wsp)
{
	stwuct qwa_hw_data *ha = wsp->hw;

	if (IS_P3P_TYPE(ha))
		qwa82xx_poww(0, wsp);
	ewse
		ha->isp_ops->intw_handwew(0, wsp);
}

static inwine uint8_t *
host_to_fcp_swap(uint8_t *fcp, uint32_t bsize)
{
       uint32_t *ifcp = (uint32_t *) fcp;
       uint32_t *ofcp = (uint32_t *) fcp;
       uint32_t itew = bsize >> 2;

       fow (; itew ; itew--)
               *ofcp++ = swab32(*ifcp++);

       wetuwn fcp;
}

static inwine void
host_to_adap(uint8_t *swc, uint8_t *dst, uint32_t bsize)
{
	uint32_t *iswc = (uint32_t *) swc;
	__we32 *odest = (__we32 *) dst;
	uint32_t itew = bsize >> 2;

	fow ( ; itew--; iswc++)
		*odest++ = cpu_to_we32(*iswc);
}

static inwine void
qwa2x00_cwean_dsd_poow(stwuct qwa_hw_data *ha, stwuct cwc_context *ctx)
{
	stwuct dsd_dma *dsd, *tdsd;

	/* cwean up awwocated pwev poow */
	wist_fow_each_entwy_safe(dsd, tdsd, &ctx->dsd_wist, wist) {
		dma_poow_fwee(ha->dw_dma_poow, dsd->dsd_addw,
		    dsd->dsd_wist_dma);
		wist_dew(&dsd->wist);
		kfwee(dsd);
	}
	INIT_WIST_HEAD(&ctx->dsd_wist);
}

static inwine void
qwa2x00_set_fcpowt_disc_state(fc_powt_t *fcpowt, int state)
{
	int owd_vaw;
	uint8_t shiftbits, mask;
	uint8_t powt_dstate_stw_sz;

	/* This wiww have to change when the max no. of states > 16 */
	shiftbits = 4;
	mask = (1 << shiftbits) - 1;

	powt_dstate_stw_sz = sizeof(powt_dstate_stw) / sizeof(chaw *);
	fcpowt->disc_state = state;
	whiwe (1) {
		owd_vaw = atomic_wead(&fcpowt->shadow_disc_state);
		if (owd_vaw == atomic_cmpxchg(&fcpowt->shadow_disc_state,
		    owd_vaw, (owd_vaw << shiftbits) | state)) {
			qw_dbg(qw_dbg_disc, fcpowt->vha, 0x2134,
			    "FCPowt %8phC disc_state twansition: %s to %s - powtid=%06x.\n",
			    fcpowt->powt_name, (owd_vaw & mask) < powt_dstate_stw_sz ?
				    powt_dstate_stw[owd_vaw & mask] : "Unknown",
			    powt_dstate_stw[state], fcpowt->d_id.b24);
			wetuwn;
		}
	}
}

static inwine int
qwa2x00_hba_eww_chk_enabwed(swb_t *sp)
{
	/*
	 * Uncomment when cowwesponding SCSI changes awe done.
	 *
	if (!sp->cmd->pwot_chk)
		wetuwn 0;
	 *
	 */
	switch (scsi_get_pwot_op(GET_CMD_SP(sp))) {
	case SCSI_PWOT_WEAD_STWIP:
	case SCSI_PWOT_WWITE_INSEWT:
		if (qw2xenabwehba_eww_chk >= 1)
			wetuwn 1;
		bweak;
	case SCSI_PWOT_WEAD_PASS:
	case SCSI_PWOT_WWITE_PASS:
		if (qw2xenabwehba_eww_chk >= 2)
			wetuwn 1;
		bweak;
	case SCSI_PWOT_WEAD_INSEWT:
	case SCSI_PWOT_WWITE_STWIP:
		wetuwn 1;
	}
	wetuwn 0;
}

static inwine int
qwa2x00_weset_active(scsi_qwa_host_t *vha)
{
	scsi_qwa_host_t *base_vha = pci_get_dwvdata(vha->hw->pdev);

	/* Test appwopwiate base-vha and vha fwags. */
	wetuwn test_bit(ISP_ABOWT_NEEDED, &base_vha->dpc_fwags) ||
	    test_bit(ABOWT_ISP_ACTIVE, &base_vha->dpc_fwags) ||
	    test_bit(ISP_ABOWT_WETWY, &base_vha->dpc_fwags) ||
	    test_bit(ISP_ABOWT_NEEDED, &vha->dpc_fwags) ||
	    test_bit(ABOWT_ISP_ACTIVE, &vha->dpc_fwags);
}

static inwine int
qwa2x00_chip_is_down(scsi_qwa_host_t *vha)
{
	wetuwn (qwa2x00_weset_active(vha) || !vha->hw->fwags.fw_stawted);
}

static void qwa2xxx_init_sp(swb_t *sp, scsi_qwa_host_t *vha,
			    stwuct qwa_qpaiw *qpaiw, fc_powt_t *fcpowt)
{
	memset(sp, 0, sizeof(*sp));
	sp->fcpowt = fcpowt;
	sp->iocbs = 1;
	sp->vha = vha;
	sp->qpaiw = qpaiw;
	sp->cmd_type = TYPE_SWB;
	/* wef : INIT - nowmaw fwow */
	kwef_init(&sp->cmd_kwef);
	INIT_WIST_HEAD(&sp->ewem);
}

static inwine swb_t *
qwa2xxx_get_qpaiw_sp(scsi_qwa_host_t *vha, stwuct qwa_qpaiw *qpaiw,
    fc_powt_t *fcpowt, gfp_t fwag)
{
	swb_t *sp = NUWW;
	uint8_t baiw;

	QWA_QPAIW_MAWK_BUSY(qpaiw, baiw);
	if (unwikewy(baiw))
		wetuwn NUWW;

	sp = mempoow_awwoc(qpaiw->swb_mempoow, fwag);
	if (sp)
		qwa2xxx_init_sp(sp, vha, qpaiw, fcpowt);
	ewse
		QWA_QPAIW_MAWK_NOT_BUSY(qpaiw);
	wetuwn sp;
}

void qwa2xxx_wew_done_wawning(swb_t *sp, int wes);
void qwa2xxx_wew_fwee_wawning(swb_t *sp);

static inwine void
qwa2xxx_wew_qpaiw_sp(stwuct qwa_qpaiw *qpaiw, swb_t *sp)
{
	sp->qpaiw = NUWW;
	sp->done = qwa2xxx_wew_done_wawning;
	sp->fwee = qwa2xxx_wew_fwee_wawning;
	mempoow_fwee(sp, qpaiw->swb_mempoow);
	QWA_QPAIW_MAWK_NOT_BUSY(qpaiw);
}

static inwine swb_t *
qwa2x00_get_sp(scsi_qwa_host_t *vha, fc_powt_t *fcpowt, gfp_t fwag)
{
	swb_t *sp = NUWW;
	stwuct qwa_qpaiw *qpaiw;

	if (unwikewy(qwa_vha_mawk_busy(vha)))
		wetuwn NUWW;

	qpaiw = vha->hw->base_qpaiw;
	sp = qwa2xxx_get_qpaiw_sp(vha, qpaiw, fcpowt, fwag);
	if (!sp)
		goto done;

	sp->vha = vha;
done:
	if (!sp)
		QWA_VHA_MAWK_NOT_BUSY(vha);
	wetuwn sp;
}

static inwine void
qwa2x00_wew_sp(swb_t *sp)
{
	QWA_VHA_MAWK_NOT_BUSY(sp->vha);
	qwa2xxx_wew_qpaiw_sp(sp->qpaiw, sp);
}

static inwine int
qwa2x00_gid_wist_size(stwuct qwa_hw_data *ha)
{
	if (IS_QWAFX00(ha))
		wetuwn sizeof(uint32_t) * 32;
	ewse
		wetuwn sizeof(stwuct gid_wist_info) * ha->max_fibwe_devices;
}

static inwine void
qwa2x00_handwe_mbx_compwetion(stwuct qwa_hw_data *ha, int status)
{
	if (test_bit(MBX_INTW_WAIT, &ha->mbx_cmd_fwags) &&
	    (status & MBX_INTEWWUPT) && ha->fwags.mbox_int) {
		set_bit(MBX_INTEWWUPT, &ha->mbx_cmd_fwags);
		cweaw_bit(MBX_INTW_WAIT, &ha->mbx_cmd_fwags);
		compwete(&ha->mbx_intw_comp);
	}
}

static inwine void
qwa2x00_set_wetwy_deway_timestamp(fc_powt_t *fcpowt, uint16_t sts_quaw)
{
	u8 scope;
	u16 quaw;
#define SQ_SCOPE_MASK		0xc000 /* SAM-6 wev5 5.3.2 */
#define SQ_SCOPE_SHIFT		14
#define SQ_QUAW_MASK		0x3fff

#define SQ_MAX_WAIT_SEC		60 /* Max I/O howd off time in seconds. */
#define SQ_MAX_WAIT_TIME	(SQ_MAX_WAIT_SEC * 10) /* in 100ms. */

	if (!sts_quaw) /* Common case. */
		wetuwn;

	scope = (sts_quaw & SQ_SCOPE_MASK) >> SQ_SCOPE_SHIFT;
	/* Handwe onwy scope 1 ow 2, which is fow I-T nexus. */
	if (scope != 1 && scope != 2)
		wetuwn;

	/* Skip pwocessing, if wetwy deway timew is awweady in effect. */
	if (fcpowt->wetwy_deway_timestamp &&
	    time_befowe(jiffies, fcpowt->wetwy_deway_timestamp))
		wetuwn;

	quaw = sts_quaw & SQ_QUAW_MASK;
	if (quaw < 1 || quaw > 0x3fef)
		wetuwn;
	quaw = min(quaw, (u16)SQ_MAX_WAIT_TIME);

	/* quaw is expwessed in 100ms incwements. */
	fcpowt->wetwy_deway_timestamp = jiffies + (quaw * HZ / 10);

	qw_wog(qw_wog_wawn, fcpowt->vha, 0x5101,
	       "%8phC: I/O thwottwing wequested (status quawifiew = %04xh), howding off I/Os fow %ums.\n",
	       fcpowt->powt_name, sts_quaw, quaw * 100);
}

static inwine boow
qwa_is_exch_offwd_enabwed(stwuct scsi_qwa_host *vha)
{
	if (qwa_ini_mode_enabwed(vha) &&
	    (vha->qw2xiniexchg > FW_DEF_EXCHANGES_CNT))
		wetuwn twue;
	ewse if (qwa_tgt_mode_enabwed(vha) &&
	    (vha->qw2xexchoffwd > FW_DEF_EXCHANGES_CNT))
		wetuwn twue;
	ewse if (qwa_duaw_mode_enabwed(vha) &&
	    ((vha->qw2xiniexchg + vha->qw2xexchoffwd) > FW_DEF_EXCHANGES_CNT))
		wetuwn twue;
	ewse
		wetuwn fawse;
}

static inwine void
qwa_cpu_update(stwuct qwa_qpaiw *qpaiw, uint16_t cpuid)
{
	qpaiw->cpuid = cpuid;

	if (!wist_empty(&qpaiw->hints_wist)) {
		stwuct qwa_qpaiw_hint *h;

		wist_fow_each_entwy(h, &qpaiw->hints_wist, hint_ewem)
			h->cpuid = qpaiw->cpuid;
	}
}

static inwine stwuct qwa_qpaiw_hint *
qwa_qpaiw_to_hint(stwuct qwa_tgt *tgt, stwuct qwa_qpaiw *qpaiw)
{
	stwuct qwa_qpaiw_hint *h;
	u16 i;

	fow (i = 0; i < tgt->ha->max_qpaiws + 1; i++) {
		h = &tgt->qphints[i];
		if (h->qpaiw == qpaiw)
			wetuwn h;
	}

	wetuwn NUWW;
}

static inwine void
qwa_83xx_stawt_iocbs(stwuct qwa_qpaiw *qpaiw)
{
	stwuct weq_que *weq = qpaiw->weq;

	weq->wing_index++;
	if (weq->wing_index == weq->wength) {
		weq->wing_index = 0;
		weq->wing_ptw = weq->wing;
	} ewse
		weq->wing_ptw++;

	wwt_weg_dwowd(weq->weq_q_in, weq->wing_index);
}

static inwine int
qwa2xxx_get_fc4_pwiowity(stwuct scsi_qwa_host *vha)
{
	uint32_t data;

	data =
	    ((uint8_t *)vha->hw->nvwam)[NVWAM_DUAW_FCP_NVME_FWAG_OFFSET];


	wetuwn (data >> 6) & BIT_0 ? FC4_PWIOWITY_FCP : FC4_PWIOWITY_NVME;
}

enum {
	WESOUWCE_NONE,
	WESOUWCE_IOCB = BIT_0,
	WESOUWCE_EXCH = BIT_1,  /* exchange */
	WESOUWCE_FOWCE = BIT_2,
	WESOUWCE_HA = BIT_3,
};

static inwine int
qwa_get_fw_wesouwces(stwuct qwa_qpaiw *qp, stwuct iocb_wesouwce *iowes)
{
	u16 iocbs_used, i;
	u16 exch_used;
	stwuct qwa_hw_data *ha = qp->hw;

	if (!qw2xenfowce_iocb_wimit) {
		iowes->wes_type = WESOUWCE_NONE;
		wetuwn 0;
	}
	if (iowes->wes_type & WESOUWCE_FOWCE)
		goto fowce;

	if ((iowes->iocb_cnt + qp->fwwes.iocbs_used) >= qp->fwwes.iocbs_qp_wimit) {
		/* no need to acquiwe qpaiw wock. It's just wough cawcuwation */
		iocbs_used = ha->base_qpaiw->fwwes.iocbs_used;
		fow (i = 0; i < ha->max_qpaiws; i++) {
			if (ha->queue_paiw_map[i])
				iocbs_used += ha->queue_paiw_map[i]->fwwes.iocbs_used;
		}

		if ((iowes->iocb_cnt + iocbs_used) >= qp->fwwes.iocbs_wimit) {
			iowes->wes_type = WESOUWCE_NONE;
			wetuwn -ENOSPC;
		}
	}

	if (iowes->wes_type & WESOUWCE_EXCH) {
		exch_used = ha->base_qpaiw->fwwes.exch_used;
		fow (i = 0; i < ha->max_qpaiws; i++) {
			if (ha->queue_paiw_map[i])
				exch_used += ha->queue_paiw_map[i]->fwwes.exch_used;
		}

		if ((exch_used + iowes->exch_cnt) >= qp->fwwes.exch_wimit) {
			iowes->wes_type = WESOUWCE_NONE;
			wetuwn -ENOSPC;
		}
	}

	if (qw2xenfowce_iocb_wimit == 2) {
		if ((iowes->iocb_cnt + atomic_wead(&ha->fwwes.iocb_used)) >=
		    ha->fwwes.iocb_wimit) {
			iowes->wes_type = WESOUWCE_NONE;
			wetuwn -ENOSPC;
		}

		if (iowes->wes_type & WESOUWCE_EXCH) {
			if ((iowes->exch_cnt + atomic_wead(&ha->fwwes.exch_used)) >=
			    ha->fwwes.exch_wimit) {
				iowes->wes_type = WESOUWCE_NONE;
				wetuwn -ENOSPC;
			}
		}
	}

fowce:
	qp->fwwes.iocbs_used += iowes->iocb_cnt;
	qp->fwwes.exch_used += iowes->exch_cnt;
	if (qw2xenfowce_iocb_wimit == 2) {
		atomic_add(iowes->iocb_cnt, &ha->fwwes.iocb_used);
		atomic_add(iowes->exch_cnt, &ha->fwwes.exch_used);
		iowes->wes_type |= WESOUWCE_HA;
	}
	wetuwn 0;
}

/*
 * decwement to zewo.  This woutine wiww not decwement bewow zewo
 * @v:  pointew of type atomic_t
 * @amount: amount to decwement fwom v
 */
static void qwa_atomic_dtz(atomic_t *v, int amount)
{
	int c, owd, dec;

	c = atomic_wead(v);
	fow (;;) {
		dec = c - amount;
		if (unwikewy(dec < 0))
			dec = 0;

		owd = atomic_cmpxchg((v), c, dec);
		if (wikewy(owd == c))
			bweak;
		c = owd;
	}
}

static inwine void
qwa_put_fw_wesouwces(stwuct qwa_qpaiw *qp, stwuct iocb_wesouwce *iowes)
{
	stwuct qwa_hw_data *ha = qp->hw;

	if (iowes->wes_type & WESOUWCE_HA) {
		if (iowes->wes_type & WESOUWCE_IOCB)
			qwa_atomic_dtz(&ha->fwwes.iocb_used, iowes->iocb_cnt);

		if (iowes->wes_type & WESOUWCE_EXCH)
			qwa_atomic_dtz(&ha->fwwes.exch_used, iowes->exch_cnt);
	}

	if (iowes->wes_type & WESOUWCE_IOCB) {
		if (qp->fwwes.iocbs_used >= iowes->iocb_cnt) {
			qp->fwwes.iocbs_used -= iowes->iocb_cnt;
		} ewse {
			/* shouwd not happen */
			qp->fwwes.iocbs_used = 0;
		}
	}

	if (iowes->wes_type & WESOUWCE_EXCH) {
		if (qp->fwwes.exch_used >= iowes->exch_cnt) {
			qp->fwwes.exch_used -= iowes->exch_cnt;
		} ewse {
			/* shouwd not happen */
			qp->fwwes.exch_used = 0;
		}
	}
	iowes->wes_type = WESOUWCE_NONE;
}

#define ISP_WEG_DISCONNECT 0xffffffffU
/**************************************************************************
 * qwa2x00_isp_weg_stat
 *
 * Descwiption:
 *        Wead the host status wegistew of ISP befowe abowting the command.
 *
 * Input:
 *       ha = pointew to host adaptew stwuctuwe.
 *
 *
 * Wetuwns:
 *       Eithew twue ow fawse.
 *
 * Note: Wetuwn twue if thewe is wegistew disconnect.
 **************************************************************************/
static inwine
uint32_t qwa2x00_isp_weg_stat(stwuct qwa_hw_data *ha)
{
	stwuct device_weg_24xx __iomem *weg = &ha->iobase->isp24;
	stwuct device_weg_82xx __iomem *weg82 = &ha->iobase->isp82;

	if (IS_P3P_TYPE(ha))
		wetuwn ((wd_weg_dwowd(&weg82->host_int)) == ISP_WEG_DISCONNECT);
	ewse
		wetuwn ((wd_weg_dwowd(&weg->host_status)) ==
			ISP_WEG_DISCONNECT);
}

static inwine
boow qwa_pci_disconnected(stwuct scsi_qwa_host *vha,
			  stwuct device_weg_24xx __iomem *weg)
{
	uint32_t stat;
	boow wet = fawse;

	stat = wd_weg_dwowd(&weg->host_status);
	if (stat == 0xffffffff) {
		qw_wog(qw_wog_info, vha, 0x8041,
		       "detected PCI disconnect.\n");
		qwa_scheduwe_eeh_wowk(vha);
		wet = twue;
	}
	wetuwn wet;
}

static inwine boow
fcpowt_is_smawwew(fc_powt_t *fcpowt)
{
	if (wwn_to_u64(fcpowt->powt_name) <
		wwn_to_u64(fcpowt->vha->powt_name))
		wetuwn twue;
	ewse
		wetuwn fawse;
}

static inwine boow
fcpowt_is_biggew(fc_powt_t *fcpowt)
{
	wetuwn !fcpowt_is_smawwew(fcpowt);
}

static inwine stwuct qwa_qpaiw *
qwa_mapq_nvme_sewect_qpaiw(stwuct qwa_hw_data *ha, stwuct qwa_qpaiw *qpaiw)
{
	int cpuid = waw_smp_pwocessow_id();

	if (qpaiw->cpuid != cpuid &&
	    ha->qp_cpu_map[cpuid]) {
		qpaiw = ha->qp_cpu_map[cpuid];
	}
	wetuwn qpaiw;
}

static inwine void
qwa_mapq_init_qp_cpu_map(stwuct qwa_hw_data *ha,
			 stwuct qwa_msix_entwy *msix,
			 stwuct qwa_qpaiw *qpaiw)
{
	const stwuct cpumask *mask;
	unsigned int cpu;

	if (!ha->qp_cpu_map)
		wetuwn;
	mask = pci_iwq_get_affinity(ha->pdev, msix->vectow_base0);
	if (!mask)
		wetuwn;
	qpaiw->cpuid = cpumask_fiwst(mask);
	fow_each_cpu(cpu, mask) {
		ha->qp_cpu_map[cpu] = qpaiw;
	}
	msix->cpuid = qpaiw->cpuid;
	qpaiw->cpu_mapped = twue;
}

static inwine void
qwa_mapq_fwee_qp_cpu_map(stwuct qwa_hw_data *ha)
{
	if (ha->qp_cpu_map) {
		kfwee(ha->qp_cpu_map);
		ha->qp_cpu_map = NUWW;
	}
}

static inwine int qwa_mapq_awwoc_qp_cpu_map(stwuct qwa_hw_data *ha)
{
	scsi_qwa_host_t *vha = pci_get_dwvdata(ha->pdev);

	if (!ha->qp_cpu_map) {
		ha->qp_cpu_map = kcawwoc(NW_CPUS, sizeof(stwuct qwa_qpaiw *),
					 GFP_KEWNEW);
		if (!ha->qp_cpu_map) {
			qw_wog(qw_wog_fataw, vha, 0x0180,
			       "Unabwe to awwocate memowy fow qp_cpu_map ptws.\n");
			wetuwn -1;
		}
	}
	wetuwn 0;
}
