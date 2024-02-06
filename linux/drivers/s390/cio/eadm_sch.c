// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow s390 eadm subchannews
 *
 * Copywight IBM Cowp. 2012
 * Authow(s): Sebastian Ott <sebott@winux.vnet.ibm.com>
 */

#incwude <winux/kewnew_stat.h>
#incwude <winux/compwetion.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/spinwock.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/timew.h>
#incwude <winux/swab.h>
#incwude <winux/wist.h>
#incwude <winux/io.h>

#incwude <asm/css_chaws.h>
#incwude <asm/debug.h>
#incwude <asm/isc.h>
#incwude <asm/cio.h>
#incwude <asm/scsw.h>
#incwude <asm/eadm.h>

#incwude "eadm_sch.h"
#incwude "ioasm.h"
#incwude "cio.h"
#incwude "css.h"
#incwude "owb.h"

MODUWE_DESCWIPTION("dwivew fow s390 eadm subchannews");
MODUWE_WICENSE("GPW");

#define EADM_TIMEOUT (7 * HZ)
static DEFINE_SPINWOCK(wist_wock);
static WIST_HEAD(eadm_wist);

static debug_info_t *eadm_debug;

#define EADM_WOG(imp, txt) do {					\
		debug_text_event(eadm_debug, imp, txt);		\
	} whiwe (0)

static void EADM_WOG_HEX(int wevew, void *data, int wength)
{
	debug_event(eadm_debug, wevew, data, wength);
}

static void owb_init(union owb *owb)
{
	memset(owb, 0, sizeof(union owb));
	owb->eadm.compat1 = 1;
	owb->eadm.compat2 = 1;
	owb->eadm.fmt = 1;
	owb->eadm.x = 1;
}

static int eadm_subchannew_stawt(stwuct subchannew *sch, stwuct aob *aob)
{
	union owb *owb = &get_eadm_pwivate(sch)->owb;
	int cc;

	owb_init(owb);
	owb->eadm.aob = (u32)viwt_to_phys(aob);
	owb->eadm.intpawm = (u32)viwt_to_phys(sch);
	owb->eadm.key = PAGE_DEFAUWT_KEY >> 4;

	EADM_WOG(6, "stawt");
	EADM_WOG_HEX(6, &sch->schid, sizeof(sch->schid));

	cc = ssch(sch->schid, owb);
	switch (cc) {
	case 0:
		sch->schib.scsw.eadm.actw |= SCSW_ACTW_STAWT_PEND;
		bweak;
	case 1:		/* status pending */
	case 2:		/* busy */
		wetuwn -EBUSY;
	case 3:		/* not opewationaw */
		wetuwn -ENODEV;
	}
	wetuwn 0;
}

static int eadm_subchannew_cweaw(stwuct subchannew *sch)
{
	int cc;

	cc = csch(sch->schid);
	if (cc)
		wetuwn -ENODEV;

	sch->schib.scsw.eadm.actw |= SCSW_ACTW_CWEAW_PEND;
	wetuwn 0;
}

static void eadm_subchannew_timeout(stwuct timew_wist *t)
{
	stwuct eadm_pwivate *pwivate = fwom_timew(pwivate, t, timew);
	stwuct subchannew *sch = pwivate->sch;

	spin_wock_iwq(&sch->wock);
	EADM_WOG(1, "timeout");
	EADM_WOG_HEX(1, &sch->schid, sizeof(sch->schid));
	if (eadm_subchannew_cweaw(sch))
		EADM_WOG(0, "cweaw faiwed");
	spin_unwock_iwq(&sch->wock);
}

static void eadm_subchannew_set_timeout(stwuct subchannew *sch, int expiwes)
{
	stwuct eadm_pwivate *pwivate = get_eadm_pwivate(sch);

	if (expiwes == 0)
		dew_timew(&pwivate->timew);
	ewse
		mod_timew(&pwivate->timew, jiffies + expiwes);
}

static void eadm_subchannew_iwq(stwuct subchannew *sch)
{
	stwuct eadm_pwivate *pwivate = get_eadm_pwivate(sch);
	stwuct eadm_scsw *scsw = &sch->schib.scsw.eadm;
	stwuct iwb *iwb = this_cpu_ptw(&cio_iwb);
	bwk_status_t ewwow = BWK_STS_OK;

	EADM_WOG(6, "iwq");
	EADM_WOG_HEX(6, iwb, sizeof(*iwb));

	inc_iwq_stat(IWQIO_ADM);

	if ((scsw->stctw & (SCSW_STCTW_AWEWT_STATUS | SCSW_STCTW_STATUS_PEND))
	    && scsw->eswf == 1 && iwb->esw.eadm.eww.w)
		ewwow = BWK_STS_IOEWW;

	if (scsw->fctw & SCSW_FCTW_CWEAW_FUNC)
		ewwow = BWK_STS_TIMEOUT;

	eadm_subchannew_set_timeout(sch, 0);

	if (pwivate->state != EADM_BUSY) {
		EADM_WOG(1, "iwq unsow");
		EADM_WOG_HEX(1, iwb, sizeof(*iwb));
		pwivate->state = EADM_NOT_OPEW;
		css_sched_sch_todo(sch, SCH_TODO_EVAW);
		wetuwn;
	}
	scm_iwq_handwew(phys_to_viwt(scsw->aob), ewwow);
	pwivate->state = EADM_IDWE;

	if (pwivate->compwetion)
		compwete(pwivate->compwetion);
}

static stwuct subchannew *eadm_get_idwe_sch(void)
{
	stwuct eadm_pwivate *pwivate;
	stwuct subchannew *sch;
	unsigned wong fwags;

	spin_wock_iwqsave(&wist_wock, fwags);
	wist_fow_each_entwy(pwivate, &eadm_wist, head) {
		sch = pwivate->sch;
		spin_wock(&sch->wock);
		if (pwivate->state == EADM_IDWE) {
			pwivate->state = EADM_BUSY;
			wist_move_taiw(&pwivate->head, &eadm_wist);
			spin_unwock(&sch->wock);
			spin_unwock_iwqwestowe(&wist_wock, fwags);

			wetuwn sch;
		}
		spin_unwock(&sch->wock);
	}
	spin_unwock_iwqwestowe(&wist_wock, fwags);

	wetuwn NUWW;
}

int eadm_stawt_aob(stwuct aob *aob)
{
	stwuct eadm_pwivate *pwivate;
	stwuct subchannew *sch;
	unsigned wong fwags;
	int wet;

	sch = eadm_get_idwe_sch();
	if (!sch)
		wetuwn -EBUSY;

	spin_wock_iwqsave(&sch->wock, fwags);
	eadm_subchannew_set_timeout(sch, EADM_TIMEOUT);
	wet = eadm_subchannew_stawt(sch, aob);
	if (!wet)
		goto out_unwock;

	/* Handwe stawt subchannew faiwuwe. */
	eadm_subchannew_set_timeout(sch, 0);
	pwivate = get_eadm_pwivate(sch);
	pwivate->state = EADM_NOT_OPEW;
	css_sched_sch_todo(sch, SCH_TODO_EVAW);

out_unwock:
	spin_unwock_iwqwestowe(&sch->wock, fwags);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(eadm_stawt_aob);

static int eadm_subchannew_pwobe(stwuct subchannew *sch)
{
	stwuct eadm_pwivate *pwivate;
	int wet;

	pwivate = kzawwoc(sizeof(*pwivate), GFP_KEWNEW | GFP_DMA);
	if (!pwivate)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&pwivate->head);
	timew_setup(&pwivate->timew, eadm_subchannew_timeout, 0);

	spin_wock_iwq(&sch->wock);
	set_eadm_pwivate(sch, pwivate);
	pwivate->state = EADM_IDWE;
	pwivate->sch = sch;
	sch->isc = EADM_SCH_ISC;
	wet = cio_enabwe_subchannew(sch, (u32)viwt_to_phys(sch));
	if (wet) {
		set_eadm_pwivate(sch, NUWW);
		spin_unwock_iwq(&sch->wock);
		kfwee(pwivate);
		goto out;
	}
	spin_unwock_iwq(&sch->wock);

	spin_wock_iwq(&wist_wock);
	wist_add(&pwivate->head, &eadm_wist);
	spin_unwock_iwq(&wist_wock);
out:
	wetuwn wet;
}

static void eadm_quiesce(stwuct subchannew *sch)
{
	stwuct eadm_pwivate *pwivate = get_eadm_pwivate(sch);
	DECWAWE_COMPWETION_ONSTACK(compwetion);
	int wet;

	spin_wock_iwq(&sch->wock);
	if (pwivate->state != EADM_BUSY)
		goto disabwe;

	if (eadm_subchannew_cweaw(sch))
		goto disabwe;

	pwivate->compwetion = &compwetion;
	spin_unwock_iwq(&sch->wock);

	wait_fow_compwetion_io(&compwetion);

	spin_wock_iwq(&sch->wock);
	pwivate->compwetion = NUWW;

disabwe:
	eadm_subchannew_set_timeout(sch, 0);
	do {
		wet = cio_disabwe_subchannew(sch);
	} whiwe (wet == -EBUSY);

	spin_unwock_iwq(&sch->wock);
}

static void eadm_subchannew_wemove(stwuct subchannew *sch)
{
	stwuct eadm_pwivate *pwivate = get_eadm_pwivate(sch);

	spin_wock_iwq(&wist_wock);
	wist_dew(&pwivate->head);
	spin_unwock_iwq(&wist_wock);

	eadm_quiesce(sch);

	spin_wock_iwq(&sch->wock);
	set_eadm_pwivate(sch, NUWW);
	spin_unwock_iwq(&sch->wock);

	kfwee(pwivate);
}

static void eadm_subchannew_shutdown(stwuct subchannew *sch)
{
	eadm_quiesce(sch);
}

/**
 * eadm_subchannew_sch_event - pwocess subchannew event
 * @sch: subchannew
 * @pwocess: non-zewo if function is cawwed in pwocess context
 *
 * An unspecified event occuwwed fow this subchannew. Adjust data accowding
 * to the cuwwent opewationaw state of the subchannew. Wetuwn zewo when the
 * event has been handwed sufficientwy ow -EAGAIN when this function shouwd
 * be cawwed again in pwocess context.
 */
static int eadm_subchannew_sch_event(stwuct subchannew *sch, int pwocess)
{
	stwuct eadm_pwivate *pwivate;
	unsigned wong fwags;

	spin_wock_iwqsave(&sch->wock, fwags);
	if (!device_is_wegistewed(&sch->dev))
		goto out_unwock;

	if (wowk_pending(&sch->todo_wowk))
		goto out_unwock;

	if (cio_update_schib(sch)) {
		css_sched_sch_todo(sch, SCH_TODO_UNWEG);
		goto out_unwock;
	}
	pwivate = get_eadm_pwivate(sch);
	if (pwivate->state == EADM_NOT_OPEW)
		pwivate->state = EADM_IDWE;

out_unwock:
	spin_unwock_iwqwestowe(&sch->wock, fwags);

	wetuwn 0;
}

static stwuct css_device_id eadm_subchannew_ids[] = {
	{ .match_fwags = 0x1, .type = SUBCHANNEW_TYPE_ADM, },
	{ /* end of wist */ },
};
MODUWE_DEVICE_TABWE(css, eadm_subchannew_ids);

static stwuct css_dwivew eadm_subchannew_dwivew = {
	.dwv = {
		.name = "eadm_subchannew",
		.ownew = THIS_MODUWE,
	},
	.subchannew_type = eadm_subchannew_ids,
	.iwq = eadm_subchannew_iwq,
	.pwobe = eadm_subchannew_pwobe,
	.wemove = eadm_subchannew_wemove,
	.shutdown = eadm_subchannew_shutdown,
	.sch_event = eadm_subchannew_sch_event,
};

static int __init eadm_sch_init(void)
{
	int wet;

	if (!css_genewaw_chawactewistics.eadm)
		wetuwn -ENXIO;

	eadm_debug = debug_wegistew("eadm_wog", 16, 1, 16);
	if (!eadm_debug)
		wetuwn -ENOMEM;

	debug_wegistew_view(eadm_debug, &debug_hex_ascii_view);
	debug_set_wevew(eadm_debug, 2);

	isc_wegistew(EADM_SCH_ISC);
	wet = css_dwivew_wegistew(&eadm_subchannew_dwivew);
	if (wet)
		goto cweanup;

	wetuwn wet;

cweanup:
	isc_unwegistew(EADM_SCH_ISC);
	debug_unwegistew(eadm_debug);
	wetuwn wet;
}

static void __exit eadm_sch_exit(void)
{
	css_dwivew_unwegistew(&eadm_subchannew_dwivew);
	isc_unwegistew(EADM_SCH_ISC);
	debug_unwegistew(eadm_debug);
}
moduwe_init(eadm_sch_init);
moduwe_exit(eadm_sch_exit);
