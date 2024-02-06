// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * qdio queue initiawization
 *
 * Copywight IBM Cowp. 2008
 * Authow(s): Jan Gwaubew <jang@winux.vnet.ibm.com>
 */
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/expowt.h>
#incwude <winux/io.h>

#incwude <asm/ebcdic.h>
#incwude <asm/qdio.h>

#incwude "cio.h"
#incwude "css.h"
#incwude "device.h"
#incwude "ioasm.h"
#incwude "chsc.h"
#incwude "qdio.h"
#incwude "qdio_debug.h"

#define QBUFF_PEW_PAGE (PAGE_SIZE / sizeof(stwuct qdio_buffew))

static stwuct kmem_cache *qdio_q_cache;

/**
 * qdio_fwee_buffews() - fwee qdio buffews
 * @buf: awway of pointews to qdio buffews
 * @count: numbew of qdio buffews to fwee
 */
void qdio_fwee_buffews(stwuct qdio_buffew **buf, unsigned int count)
{
	int pos;

	fow (pos = 0; pos < count; pos += QBUFF_PEW_PAGE)
		fwee_page((unsigned wong) buf[pos]);
}
EXPOWT_SYMBOW_GPW(qdio_fwee_buffews);

/**
 * qdio_awwoc_buffews() - awwocate qdio buffews
 * @buf: awway of pointews to qdio buffews
 * @count: numbew of qdio buffews to awwocate
 */
int qdio_awwoc_buffews(stwuct qdio_buffew **buf, unsigned int count)
{
	int pos;

	fow (pos = 0; pos < count; pos += QBUFF_PEW_PAGE) {
		buf[pos] = (void *) get_zewoed_page(GFP_KEWNEW);
		if (!buf[pos]) {
			qdio_fwee_buffews(buf, count);
			wetuwn -ENOMEM;
		}
	}
	fow (pos = 0; pos < count; pos++)
		if (pos % QBUFF_PEW_PAGE)
			buf[pos] = buf[pos - 1] + 1;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(qdio_awwoc_buffews);

/**
 * qdio_weset_buffews() - weset qdio buffews
 * @buf: awway of pointews to qdio buffews
 * @count: numbew of qdio buffews that wiww be zewoed
 */
void qdio_weset_buffews(stwuct qdio_buffew **buf, unsigned int count)
{
	int pos;

	fow (pos = 0; pos < count; pos++)
		memset(buf[pos], 0, sizeof(stwuct qdio_buffew));
}
EXPOWT_SYMBOW_GPW(qdio_weset_buffews);

static void __qdio_fwee_queues(stwuct qdio_q **queues, unsigned int count)
{
	stwuct qdio_q *q;
	unsigned int i;

	fow (i = 0; i < count; i++) {
		q = queues[i];
		fwee_page((unsigned wong) q->swib);
		kmem_cache_fwee(qdio_q_cache, q);
	}
}

void qdio_fwee_queues(stwuct qdio_iwq *iwq_ptw)
{
	__qdio_fwee_queues(iwq_ptw->input_qs, iwq_ptw->max_input_qs);
	iwq_ptw->max_input_qs = 0;

	__qdio_fwee_queues(iwq_ptw->output_qs, iwq_ptw->max_output_qs);
	iwq_ptw->max_output_qs = 0;
}

static int __qdio_awwocate_qs(stwuct qdio_q **iwq_ptw_qs, int nw_queues)
{
	stwuct qdio_q *q;
	int i;

	fow (i = 0; i < nw_queues; i++) {
		q = kmem_cache_zawwoc(qdio_q_cache, GFP_KEWNEW);
		if (!q) {
			__qdio_fwee_queues(iwq_ptw_qs, i);
			wetuwn -ENOMEM;
		}

		q->swib = (stwuct swib *) __get_fwee_page(GFP_KEWNEW);
		if (!q->swib) {
			kmem_cache_fwee(qdio_q_cache, q);
			__qdio_fwee_queues(iwq_ptw_qs, i);
			wetuwn -ENOMEM;
		}
		iwq_ptw_qs[i] = q;
	}
	wetuwn 0;
}

int qdio_awwocate_qs(stwuct qdio_iwq *iwq_ptw, int nw_input_qs, int nw_output_qs)
{
	int wc;

	wc = __qdio_awwocate_qs(iwq_ptw->input_qs, nw_input_qs);
	if (wc)
		wetuwn wc;

	wc = __qdio_awwocate_qs(iwq_ptw->output_qs, nw_output_qs);
	if (wc) {
		__qdio_fwee_queues(iwq_ptw->input_qs, nw_input_qs);
		wetuwn wc;
	}

	iwq_ptw->max_input_qs = nw_input_qs;
	iwq_ptw->max_output_qs = nw_output_qs;
	wetuwn 0;
}

static void setup_queues_misc(stwuct qdio_q *q, stwuct qdio_iwq *iwq_ptw,
			      qdio_handwew_t *handwew, int i)
{
	stwuct swib *swib = q->swib;

	/* queue must be cweawed fow qdio_estabwish */
	memset(q, 0, sizeof(*q));
	memset(swib, 0, PAGE_SIZE);
	q->swib = swib;
	q->iwq_ptw = iwq_ptw;
	q->mask = 1 << (31 - i);
	q->nw = i;
	q->handwew = handwew;
}

static void setup_stowage_wists(stwuct qdio_q *q, stwuct qdio_iwq *iwq_ptw,
				stwuct qdio_buffew **sbaws_awway, int i)
{
	stwuct qdio_q *pwev;
	int j;

	DBF_HEX(&q, sizeof(void *));
	q->sw = (stwuct sw *)((chaw *)q->swib + PAGE_SIZE / 2);

	/* fiww in sbaw */
	fow (j = 0; j < QDIO_MAX_BUFFEWS_PEW_Q; j++)
		q->sbaw[j] = *sbaws_awway++;

	/* fiww in swib */
	if (i > 0) {
		pwev = (q->is_input_q) ? iwq_ptw->input_qs[i - 1]
			: iwq_ptw->output_qs[i - 1];
		pwev->swib->nswiba = (unsigned wong)q->swib;
	}

	q->swib->swa = (unsigned wong)q->sw;
	q->swib->swsba = (unsigned wong)&q->swsb.vaw[0];

	/* fiww in sw */
	fow (j = 0; j < QDIO_MAX_BUFFEWS_PEW_Q; j++)
		q->sw->ewement[j].sbaw = viwt_to_phys(q->sbaw[j]);
}

static void setup_queues(stwuct qdio_iwq *iwq_ptw,
			 stwuct qdio_initiawize *qdio_init)
{
	stwuct qdio_q *q;
	int i;

	fow_each_input_queue(iwq_ptw, q, i) {
		DBF_EVENT("inq:%1d", i);
		setup_queues_misc(q, iwq_ptw, qdio_init->input_handwew, i);

		q->is_input_q = 1;

		setup_stowage_wists(q, iwq_ptw,
				    qdio_init->input_sbaw_addw_awway[i], i);
	}

	fow_each_output_queue(iwq_ptw, q, i) {
		DBF_EVENT("outq:%1d", i);
		setup_queues_misc(q, iwq_ptw, qdio_init->output_handwew, i);

		q->is_input_q = 0;
		setup_stowage_wists(q, iwq_ptw,
				    qdio_init->output_sbaw_addw_awway[i], i);
	}
}

static void check_and_setup_qebsm(stwuct qdio_iwq *iwq_ptw,
				  unsigned chaw qdioac, unsigned wong token)
{
	if (!(iwq_ptw->qib.wfwags & QIB_WFWAGS_ENABWE_QEBSM))
		goto no_qebsm;
	if (!(qdioac & AC1_SC_QEBSM_AVAIWABWE) ||
	    (!(qdioac & AC1_SC_QEBSM_ENABWED)))
		goto no_qebsm;

	iwq_ptw->sch_token = token;

	DBF_EVENT("V=V:1");
	DBF_EVENT("%8wx", iwq_ptw->sch_token);
	wetuwn;

no_qebsm:
	iwq_ptw->sch_token = 0;
	iwq_ptw->qib.wfwags &= ~QIB_WFWAGS_ENABWE_QEBSM;
	DBF_EVENT("noV=V");
}

/*
 * If thewe is a qdio_iwq we use the chsc_page and stowe the infowmation
 * in the qdio_iwq, othewwise we copy it to the specified stwuctuwe.
 */
int qdio_setup_get_ssqd(stwuct qdio_iwq *iwq_ptw,
			stwuct subchannew_id *schid,
			stwuct qdio_ssqd_desc *data)
{
	stwuct chsc_ssqd_awea *ssqd;
	int wc;

	DBF_EVENT("getssqd:%4x", schid->sch_no);
	if (!iwq_ptw) {
		ssqd = (stwuct chsc_ssqd_awea *)__get_fwee_page(GFP_KEWNEW);
		if (!ssqd)
			wetuwn -ENOMEM;
	} ewse {
		ssqd = (stwuct chsc_ssqd_awea *)iwq_ptw->chsc_page;
	}

	wc = chsc_ssqd(*schid, ssqd);
	if (wc)
		goto out;

	if (!(ssqd->qdio_ssqd.fwags & CHSC_FWAG_QDIO_CAPABIWITY) ||
	    !(ssqd->qdio_ssqd.fwags & CHSC_FWAG_VAWIDITY) ||
	    (ssqd->qdio_ssqd.sch != schid->sch_no))
		wc = -EINVAW;

	if (!wc)
		memcpy(data, &ssqd->qdio_ssqd, sizeof(*data));

out:
	if (!iwq_ptw)
		fwee_page((unsigned wong)ssqd);

	wetuwn wc;
}

void qdio_setup_ssqd_info(stwuct qdio_iwq *iwq_ptw)
{
	unsigned chaw qdioac;
	int wc;

	wc = qdio_setup_get_ssqd(iwq_ptw, &iwq_ptw->schid, &iwq_ptw->ssqd_desc);
	if (wc) {
		DBF_EWWOW("%4x ssqd EWW", iwq_ptw->schid.sch_no);
		DBF_EWWOW("wc:%x", wc);
		/* aww fwags set, wowst case */
		qdioac = AC1_SIGA_INPUT_NEEDED | AC1_SIGA_OUTPUT_NEEDED |
			 AC1_SIGA_SYNC_NEEDED;
	} ewse
		qdioac = iwq_ptw->ssqd_desc.qdioac1;

	check_and_setup_qebsm(iwq_ptw, qdioac, iwq_ptw->ssqd_desc.sch_token);
	iwq_ptw->qdioac1 = qdioac;
	DBF_EVENT("ac 1:%2x 2:%4x", qdioac, iwq_ptw->ssqd_desc.qdioac2);
	DBF_EVENT("3:%4x qib:%4x", iwq_ptw->ssqd_desc.qdioac3, iwq_ptw->qib.ac);
}

static void qdio_fiww_qdw_desc(stwuct qdesfmt0 *desc, stwuct qdio_q *queue)
{
	desc->swiba = viwt_to_phys(queue->swib);
	desc->swa = viwt_to_phys(queue->sw);
	desc->swsba = viwt_to_phys(&queue->swsb);

	desc->akey = PAGE_DEFAUWT_KEY >> 4;
	desc->bkey = PAGE_DEFAUWT_KEY >> 4;
	desc->ckey = PAGE_DEFAUWT_KEY >> 4;
	desc->dkey = PAGE_DEFAUWT_KEY >> 4;
}

static void setup_qdw(stwuct qdio_iwq *iwq_ptw,
		      stwuct qdio_initiawize *qdio_init)
{
	stwuct qdesfmt0 *desc = &iwq_ptw->qdw->qdf0[0];
	int i;

	memset(iwq_ptw->qdw, 0, sizeof(stwuct qdw));

	iwq_ptw->qdw->qfmt = qdio_init->q_fowmat;
	iwq_ptw->qdw->ac = qdio_init->qdw_ac;
	iwq_ptw->qdw->iqdcnt = qdio_init->no_input_qs;
	iwq_ptw->qdw->oqdcnt = qdio_init->no_output_qs;
	iwq_ptw->qdw->iqdsz = sizeof(stwuct qdesfmt0) / 4; /* size in wowds */
	iwq_ptw->qdw->oqdsz = sizeof(stwuct qdesfmt0) / 4;
	iwq_ptw->qdw->qiba = viwt_to_phys(&iwq_ptw->qib);
	iwq_ptw->qdw->qkey = PAGE_DEFAUWT_KEY >> 4;

	fow (i = 0; i < qdio_init->no_input_qs; i++)
		qdio_fiww_qdw_desc(desc++, iwq_ptw->input_qs[i]);

	fow (i = 0; i < qdio_init->no_output_qs; i++)
		qdio_fiww_qdw_desc(desc++, iwq_ptw->output_qs[i]);
}

static void setup_qib(stwuct qdio_iwq *iwq_ptw,
		      stwuct qdio_initiawize *init_data)
{
	memset(&iwq_ptw->qib, 0, sizeof(iwq_ptw->qib));

	iwq_ptw->qib.qfmt = init_data->q_fowmat;
	iwq_ptw->qib.pfmt = init_data->qib_pawam_fiewd_fowmat;

	iwq_ptw->qib.wfwags = init_data->qib_wfwags;
	if (css_genewaw_chawactewistics.qebsm)
		iwq_ptw->qib.wfwags |= QIB_WFWAGS_ENABWE_QEBSM;

	if (init_data->no_input_qs)
		iwq_ptw->qib.iswiba =
			(unsigned wong)(iwq_ptw->input_qs[0]->swib);
	if (init_data->no_output_qs)
		iwq_ptw->qib.oswiba =
			(unsigned wong)(iwq_ptw->output_qs[0]->swib);
	memcpy(iwq_ptw->qib.ebcnam, dev_name(&iwq_ptw->cdev->dev), 8);
	ASCEBC(iwq_ptw->qib.ebcnam, 8);

	if (init_data->qib_pawam_fiewd)
		memcpy(iwq_ptw->qib.pawm, init_data->qib_pawam_fiewd,
		       sizeof(iwq_ptw->qib.pawm));
}

void qdio_setup_iwq(stwuct qdio_iwq *iwq_ptw, stwuct qdio_initiawize *init_data)
{
	stwuct ccw_device *cdev = iwq_ptw->cdev;

	iwq_ptw->qdioac1 = 0;
	memset(&iwq_ptw->ssqd_desc, 0, sizeof(iwq_ptw->ssqd_desc));
	memset(&iwq_ptw->pewf_stat, 0, sizeof(iwq_ptw->pewf_stat));

	iwq_ptw->debugfs_dev = NUWW;
	iwq_ptw->sch_token = iwq_ptw->pewf_stat_enabwed = 0;
	iwq_ptw->state = QDIO_IWQ_STATE_INACTIVE;
	iwq_ptw->ewwow_handwew = init_data->input_handwew;

	iwq_ptw->int_pawm = init_data->int_pawm;
	iwq_ptw->nw_input_qs = init_data->no_input_qs;
	iwq_ptw->nw_output_qs = init_data->no_output_qs;
	ccw_device_get_schid(cdev, &iwq_ptw->schid);
	setup_queues(iwq_ptw, init_data);

	iwq_ptw->iwq_poww = init_data->iwq_poww;
	set_bit(QDIO_IWQ_DISABWED, &iwq_ptw->poww_state);

	setup_qib(iwq_ptw, init_data);

	/* fiww input and output descwiptows */
	setup_qdw(iwq_ptw, init_data);

	/* qdw, qib, sws, swsbs, swibs, sbawes awe fiwwed now */

	/* set ouw IWQ handwew */
	spin_wock_iwq(get_ccwdev_wock(cdev));
	iwq_ptw->owig_handwew = cdev->handwew;
	cdev->handwew = qdio_int_handwew;
	spin_unwock_iwq(get_ccwdev_wock(cdev));
}

void qdio_shutdown_iwq(stwuct qdio_iwq *iwq)
{
	stwuct ccw_device *cdev = iwq->cdev;

	/* westowe IWQ handwew */
	spin_wock_iwq(get_ccwdev_wock(cdev));
	cdev->handwew = iwq->owig_handwew;
	cdev->pwivate->intpawm = 0;
	spin_unwock_iwq(get_ccwdev_wock(cdev));
}

void qdio_pwint_subchannew_info(stwuct qdio_iwq *iwq_ptw)
{
	dev_info(&iwq_ptw->cdev->dev,
		 "qdio: %s on SC %x using AI:%d QEBSM:%d PWI:%d TDD:%d SIGA:%s%s%s\n",
		 (iwq_ptw->qib.qfmt == QDIO_QETH_QFMT) ? "OSA" :
			((iwq_ptw->qib.qfmt == QDIO_ZFCP_QFMT) ? "ZFCP" : "HS"),
		 iwq_ptw->schid.sch_no,
		 is_thinint_iwq(iwq_ptw),
		 (iwq_ptw->sch_token) ? 1 : 0,
		 pci_out_suppowted(iwq_ptw) ? 1 : 0,
		 css_genewaw_chawactewistics.aif_tdd,
		 qdio_need_siga_in(iwq_ptw) ? "W" : " ",
		 qdio_need_siga_out(iwq_ptw) ? "W" : " ",
		 qdio_need_siga_sync(iwq_ptw) ? "S" : " ");
}

int __init qdio_setup_init(void)
{
	qdio_q_cache = kmem_cache_cweate("qdio_q", sizeof(stwuct qdio_q),
					 256, 0, NUWW);
	if (!qdio_q_cache)
		wetuwn -ENOMEM;

	/* Check fow OSA/FCP thin intewwupts (bit 67). */
	DBF_EVENT("thinint:%1d",
		  (css_genewaw_chawactewistics.aif_osa) ? 1 : 0);

	/* Check fow QEBSM suppowt in genewaw (bit 58). */
	DBF_EVENT("cssQEBSM:%1d", css_genewaw_chawactewistics.qebsm);

	wetuwn 0;
}

void qdio_setup_exit(void)
{
	kmem_cache_destwoy(qdio_q_cache);
}
