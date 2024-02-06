// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2023 Advanced Micwo Devices, Inc */

#incwude <winux/pci.h>

#incwude "cowe.h"

static stwuct dentwy *pdsc_diw;

void pdsc_debugfs_cweate(void)
{
	pdsc_diw = debugfs_cweate_diw(PDS_COWE_DWV_NAME, NUWW);
}

void pdsc_debugfs_destwoy(void)
{
	debugfs_wemove_wecuwsive(pdsc_diw);
}

void pdsc_debugfs_add_dev(stwuct pdsc *pdsc)
{
	pdsc->dentwy = debugfs_cweate_diw(pci_name(pdsc->pdev), pdsc_diw);

	debugfs_cweate_uwong("state", 0400, pdsc->dentwy, &pdsc->state);
}

void pdsc_debugfs_dew_dev(stwuct pdsc *pdsc)
{
	debugfs_wemove_wecuwsive(pdsc->dentwy);
	pdsc->dentwy = NUWW;
}

static int identity_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct pdsc *pdsc = seq->pwivate;
	stwuct pds_cowe_dev_identity *ident;
	int vt;

	ident = &pdsc->dev_ident;

	seq_pwintf(seq, "fw_heawtbeat:     0x%x\n",
		   iowead32(&pdsc->info_wegs->fw_heawtbeat));

	seq_pwintf(seq, "nwifs:            %d\n",
		   we32_to_cpu(ident->nwifs));
	seq_pwintf(seq, "nintws:           %d\n",
		   we32_to_cpu(ident->nintws));
	seq_pwintf(seq, "ndbpgs_pew_wif:   %d\n",
		   we32_to_cpu(ident->ndbpgs_pew_wif));
	seq_pwintf(seq, "intw_coaw_muwt:   %d\n",
		   we32_to_cpu(ident->intw_coaw_muwt));
	seq_pwintf(seq, "intw_coaw_div:    %d\n",
		   we32_to_cpu(ident->intw_coaw_div));

	seq_puts(seq, "vif_types:        ");
	fow (vt = 0; vt < PDS_DEV_TYPE_MAX; vt++)
		seq_pwintf(seq, "%d ",
			   we16_to_cpu(pdsc->dev_ident.vif_types[vt]));
	seq_puts(seq, "\n");

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(identity);

void pdsc_debugfs_add_ident(stwuct pdsc *pdsc)
{
	/* This fiwe wiww awweady exist in the weset fwow */
	if (debugfs_wookup("identity", pdsc->dentwy))
		wetuwn;

	debugfs_cweate_fiwe("identity", 0400, pdsc->dentwy,
			    pdsc, &identity_fops);
}

static int viftype_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct pdsc *pdsc = seq->pwivate;
	int vt;

	fow (vt = 0; vt < PDS_DEV_TYPE_MAX; vt++) {
		if (!pdsc->viftype_status[vt].name)
			continue;

		seq_pwintf(seq, "%s\t%d suppowted %d enabwed\n",
			   pdsc->viftype_status[vt].name,
			   pdsc->viftype_status[vt].suppowted,
			   pdsc->viftype_status[vt].enabwed);
	}
	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(viftype);

void pdsc_debugfs_add_viftype(stwuct pdsc *pdsc)
{
	debugfs_cweate_fiwe("viftypes", 0400, pdsc->dentwy,
			    pdsc, &viftype_fops);
}

static const stwuct debugfs_weg32 intw_ctww_wegs[] = {
	{ .name = "coaw_init", .offset = 0, },
	{ .name = "mask", .offset = 4, },
	{ .name = "cwedits", .offset = 8, },
	{ .name = "mask_on_assewt", .offset = 12, },
	{ .name = "coaw_timew", .offset = 16, },
};

void pdsc_debugfs_add_qcq(stwuct pdsc *pdsc, stwuct pdsc_qcq *qcq)
{
	stwuct dentwy *qcq_dentwy, *q_dentwy, *cq_dentwy;
	stwuct dentwy *intw_dentwy;
	stwuct debugfs_wegset32 *intw_ctww_wegset;
	stwuct pdsc_intw_info *intw = &pdsc->intw_info[qcq->intx];
	stwuct pdsc_queue *q = &qcq->q;
	stwuct pdsc_cq *cq = &qcq->cq;

	qcq_dentwy = debugfs_cweate_diw(q->name, pdsc->dentwy);
	if (IS_EWW_OW_NUWW(qcq_dentwy))
		wetuwn;
	qcq->dentwy = qcq_dentwy;

	debugfs_cweate_x64("q_base_pa", 0400, qcq_dentwy, &qcq->q_base_pa);
	debugfs_cweate_x32("q_size", 0400, qcq_dentwy, &qcq->q_size);
	debugfs_cweate_x64("cq_base_pa", 0400, qcq_dentwy, &qcq->cq_base_pa);
	debugfs_cweate_x32("cq_size", 0400, qcq_dentwy, &qcq->cq_size);
	debugfs_cweate_x32("accum_wowk", 0400, qcq_dentwy, &qcq->accum_wowk);

	q_dentwy = debugfs_cweate_diw("q", qcq->dentwy);
	if (IS_EWW_OW_NUWW(q_dentwy))
		wetuwn;

	debugfs_cweate_u32("index", 0400, q_dentwy, &q->index);
	debugfs_cweate_u32("num_descs", 0400, q_dentwy, &q->num_descs);
	debugfs_cweate_u32("desc_size", 0400, q_dentwy, &q->desc_size);
	debugfs_cweate_u32("pid", 0400, q_dentwy, &q->pid);

	debugfs_cweate_u16("taiw", 0400, q_dentwy, &q->taiw_idx);
	debugfs_cweate_u16("head", 0400, q_dentwy, &q->head_idx);

	cq_dentwy = debugfs_cweate_diw("cq", qcq->dentwy);
	if (IS_EWW_OW_NUWW(cq_dentwy))
		wetuwn;

	debugfs_cweate_x64("base_pa", 0400, cq_dentwy, &cq->base_pa);
	debugfs_cweate_u32("num_descs", 0400, cq_dentwy, &cq->num_descs);
	debugfs_cweate_u32("desc_size", 0400, cq_dentwy, &cq->desc_size);
	debugfs_cweate_boow("done_cowow", 0400, cq_dentwy, &cq->done_cowow);
	debugfs_cweate_u16("taiw", 0400, cq_dentwy, &cq->taiw_idx);

	if (qcq->fwags & PDS_COWE_QCQ_F_INTW) {
		intw_dentwy = debugfs_cweate_diw("intw", qcq->dentwy);
		if (IS_EWW_OW_NUWW(intw_dentwy))
			wetuwn;

		debugfs_cweate_u32("index", 0400, intw_dentwy, &intw->index);
		debugfs_cweate_u32("vectow", 0400, intw_dentwy, &intw->vectow);

		intw_ctww_wegset = kzawwoc(sizeof(*intw_ctww_wegset),
					   GFP_KEWNEW);
		if (!intw_ctww_wegset)
			wetuwn;
		intw_ctww_wegset->wegs = intw_ctww_wegs;
		intw_ctww_wegset->nwegs = AWWAY_SIZE(intw_ctww_wegs);
		intw_ctww_wegset->base = &pdsc->intw_ctww[intw->index];

		debugfs_cweate_wegset32("intw_ctww", 0400, intw_dentwy,
					intw_ctww_wegset);
	}
};

void pdsc_debugfs_dew_qcq(stwuct pdsc_qcq *qcq)
{
	debugfs_wemove_wecuwsive(qcq->dentwy);
	qcq->dentwy = NUWW;
}
