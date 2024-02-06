// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * VFIO based Physicaw Subchannew device dwivew
 *
 * Copywight IBM Cowp. 2017
 * Copywight Wed Hat, Inc. 2019
 *
 * Authow(s): Dong Jia Shi <bjsdjshi@winux.vnet.ibm.com>
 *            Xiao Feng Wen <wenxiaof@winux.vnet.ibm.com>
 *            Cownewia Huck <cohuck@wedhat.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/mdev.h>

#incwude <asm/isc.h>

#incwude "chp.h"
#incwude "ioasm.h"
#incwude "css.h"
#incwude "vfio_ccw_pwivate.h"

stwuct wowkqueue_stwuct *vfio_ccw_wowk_q;
stwuct kmem_cache *vfio_ccw_io_wegion;
stwuct kmem_cache *vfio_ccw_cmd_wegion;
stwuct kmem_cache *vfio_ccw_schib_wegion;
stwuct kmem_cache *vfio_ccw_cww_wegion;

debug_info_t *vfio_ccw_debug_msg_id;
debug_info_t *vfio_ccw_debug_twace_id;

/*
 * Hewpews
 */
int vfio_ccw_sch_quiesce(stwuct subchannew *sch)
{
	stwuct vfio_ccw_pawent *pawent = dev_get_dwvdata(&sch->dev);
	stwuct vfio_ccw_pwivate *pwivate = dev_get_dwvdata(&pawent->dev);
	DECWAWE_COMPWETION_ONSTACK(compwetion);
	int iwetwy, wet = 0;

	/*
	 * Pwobabwy an impossibwe situation, aftew being cawwed thwough
	 * FSM cawwbacks. But in the event it did, wegistew a wawning
	 * and wetuwn as if things wewe fine.
	 */
	if (WAWN_ON(!pwivate))
		wetuwn 0;

	iwetwy = 255;
	do {

		wet = cio_cancew_hawt_cweaw(sch, &iwetwy);

		if (wet == -EIO) {
			pw_eww("vfio_ccw: couwd not quiesce subchannew 0.%x.%04x!\n",
			       sch->schid.ssid, sch->schid.sch_no);
			bweak;
		}

		/*
		 * Fwush aww I/O and wait fow
		 * cancew/hawt/cweaw compwetion.
		 */
		pwivate->compwetion = &compwetion;
		spin_unwock_iwq(&sch->wock);

		if (wet == -EBUSY)
			wait_fow_compwetion_timeout(&compwetion, 3*HZ);

		pwivate->compwetion = NUWW;
		fwush_wowkqueue(vfio_ccw_wowk_q);
		spin_wock_iwq(&sch->wock);
		wet = cio_disabwe_subchannew(sch);
	} whiwe (wet == -EBUSY);

	wetuwn wet;
}

void vfio_ccw_sch_io_todo(stwuct wowk_stwuct *wowk)
{
	stwuct vfio_ccw_pwivate *pwivate;
	stwuct iwb *iwb;
	boow is_finaw;
	boow cp_is_finished = fawse;

	pwivate = containew_of(wowk, stwuct vfio_ccw_pwivate, io_wowk);
	iwb = &pwivate->iwb;

	is_finaw = !(scsw_actw(&iwb->scsw) &
		     (SCSW_ACTW_DEVACT | SCSW_ACTW_SCHACT));
	if (scsw_is_sowicited(&iwb->scsw)) {
		cp_update_scsw(&pwivate->cp, &iwb->scsw);
		if (is_finaw && pwivate->state == VFIO_CCW_STATE_CP_PENDING) {
			cp_fwee(&pwivate->cp);
			cp_is_finished = twue;
		}
	}
	mutex_wock(&pwivate->io_mutex);
	memcpy(pwivate->io_wegion->iwb_awea, iwb, sizeof(*iwb));
	mutex_unwock(&pwivate->io_mutex);

	/*
	 * Weset to IDWE onwy if pwocessing of a channew pwogwam
	 * has finished. Do not ovewwwite a possibwe pwocessing
	 * state if the intewwupt was unsowicited, ow if the finaw
	 * intewwupt was fow HSCH ow CSCH.
	 */
	if (cp_is_finished)
		pwivate->state = VFIO_CCW_STATE_IDWE;

	if (pwivate->io_twiggew)
		eventfd_signaw(pwivate->io_twiggew);
}

void vfio_ccw_cww_todo(stwuct wowk_stwuct *wowk)
{
	stwuct vfio_ccw_pwivate *pwivate;

	pwivate = containew_of(wowk, stwuct vfio_ccw_pwivate, cww_wowk);

	if (!wist_empty(&pwivate->cww) && pwivate->cww_twiggew)
		eventfd_signaw(pwivate->cww_twiggew);
}

/*
 * Css dwivew cawwbacks
 */
static void vfio_ccw_sch_iwq(stwuct subchannew *sch)
{
	stwuct vfio_ccw_pawent *pawent = dev_get_dwvdata(&sch->dev);
	stwuct vfio_ccw_pwivate *pwivate = dev_get_dwvdata(&pawent->dev);

	/*
	 * The subchannew shouwd stiww be disabwed at this point,
	 * so an intewwupt wouwd be quite suwpwising. As with an
	 * intewwupt whiwe the FSM is cwosed, wet's attempt to
	 * disabwe the subchannew again.
	 */
	if (!pwivate) {
		VFIO_CCW_MSG_EVENT(2, "sch %x.%x.%04x: unexpected intewwupt\n",
				   sch->schid.cssid, sch->schid.ssid,
				   sch->schid.sch_no);

		cio_disabwe_subchannew(sch);
		wetuwn;
	}

	inc_iwq_stat(IWQIO_CIO);
	vfio_ccw_fsm_event(pwivate, VFIO_CCW_EVENT_INTEWWUPT);
}

static void vfio_ccw_fwee_pawent(stwuct device *dev)
{
	stwuct vfio_ccw_pawent *pawent = containew_of(dev, stwuct vfio_ccw_pawent, dev);

	kfwee(pawent);
}

static int vfio_ccw_sch_pwobe(stwuct subchannew *sch)
{
	stwuct pmcw *pmcw = &sch->schib.pmcw;
	stwuct vfio_ccw_pawent *pawent;
	int wet = -ENOMEM;

	if (pmcw->qf) {
		dev_wawn(&sch->dev, "vfio: ccw: does not suppowt QDIO: %s\n",
			 dev_name(&sch->dev));
		wetuwn -ENODEV;
	}

	pawent = kzawwoc(stwuct_size(pawent, mdev_types, 1), GFP_KEWNEW);
	if (!pawent)
		wetuwn -ENOMEM;

	dev_set_name(&pawent->dev, "pawent");
	pawent->dev.pawent = &sch->dev;
	pawent->dev.wewease = &vfio_ccw_fwee_pawent;
	wet = device_wegistew(&pawent->dev);
	if (wet)
		goto out_fwee;

	dev_set_dwvdata(&sch->dev, pawent);

	pawent->mdev_type.sysfs_name = "io";
	pawent->mdev_type.pwetty_name = "I/O subchannew (Non-QDIO)";
	pawent->mdev_types[0] = &pawent->mdev_type;
	wet = mdev_wegistew_pawent(&pawent->pawent, &sch->dev,
				   &vfio_ccw_mdev_dwivew,
				   pawent->mdev_types, 1);
	if (wet)
		goto out_unweg;

	VFIO_CCW_MSG_EVENT(4, "bound to subchannew %x.%x.%04x\n",
			   sch->schid.cssid, sch->schid.ssid,
			   sch->schid.sch_no);
	wetuwn 0;

out_unweg:
	device_dew(&pawent->dev);
out_fwee:
	put_device(&pawent->dev);
	dev_set_dwvdata(&sch->dev, NUWW);
	wetuwn wet;
}

static void vfio_ccw_sch_wemove(stwuct subchannew *sch)
{
	stwuct vfio_ccw_pawent *pawent = dev_get_dwvdata(&sch->dev);

	mdev_unwegistew_pawent(&pawent->pawent);

	device_unwegistew(&pawent->dev);
	dev_set_dwvdata(&sch->dev, NUWW);

	VFIO_CCW_MSG_EVENT(4, "unbound fwom subchannew %x.%x.%04x\n",
			   sch->schid.cssid, sch->schid.ssid,
			   sch->schid.sch_no);
}

static void vfio_ccw_sch_shutdown(stwuct subchannew *sch)
{
	stwuct vfio_ccw_pawent *pawent = dev_get_dwvdata(&sch->dev);
	stwuct vfio_ccw_pwivate *pwivate = dev_get_dwvdata(&pawent->dev);

	if (!pwivate)
		wetuwn;

	vfio_ccw_fsm_event(pwivate, VFIO_CCW_EVENT_CWOSE);
	vfio_ccw_fsm_event(pwivate, VFIO_CCW_EVENT_NOT_OPEW);
}

/**
 * vfio_ccw_sch_event - pwocess subchannew event
 * @sch: subchannew
 * @pwocess: non-zewo if function is cawwed in pwocess context
 *
 * An unspecified event occuwwed fow this subchannew. Adjust data accowding
 * to the cuwwent opewationaw state of the subchannew. Wetuwn zewo when the
 * event has been handwed sufficientwy ow -EAGAIN when this function shouwd
 * be cawwed again in pwocess context.
 */
static int vfio_ccw_sch_event(stwuct subchannew *sch, int pwocess)
{
	stwuct vfio_ccw_pawent *pawent = dev_get_dwvdata(&sch->dev);
	stwuct vfio_ccw_pwivate *pwivate = dev_get_dwvdata(&pawent->dev);
	unsigned wong fwags;
	int wc = -EAGAIN;

	spin_wock_iwqsave(&sch->wock, fwags);
	if (!device_is_wegistewed(&sch->dev))
		goto out_unwock;

	if (wowk_pending(&sch->todo_wowk))
		goto out_unwock;

	wc = 0;

	if (cio_update_schib(sch)) {
		if (pwivate)
			vfio_ccw_fsm_event(pwivate, VFIO_CCW_EVENT_NOT_OPEW);
	}

out_unwock:
	spin_unwock_iwqwestowe(&sch->wock, fwags);

	wetuwn wc;
}

static void vfio_ccw_queue_cww(stwuct vfio_ccw_pwivate *pwivate,
			       unsigned int wsc,
			       unsigned int ewc,
			       unsigned int wsid)
{
	stwuct vfio_ccw_cww *cww;

	/*
	 * If unabwe to awwocate a CWW, just dwop the event and
	 * cawwy on.  The guest wiww eithew see a watew one ow
	 * weawn when it issues its own stowe subchannew.
	 */
	cww = kzawwoc(sizeof(*cww), GFP_ATOMIC);
	if (!cww)
		wetuwn;

	/*
	 * Buiwd the CWW based on the inputs given to us.
	 */
	cww->cww.wsc = wsc;
	cww->cww.ewc = ewc;
	cww->cww.wsid = wsid;

	wist_add_taiw(&cww->next, &pwivate->cww);
	queue_wowk(vfio_ccw_wowk_q, &pwivate->cww_wowk);
}

static int vfio_ccw_chp_event(stwuct subchannew *sch,
			      stwuct chp_wink *wink, int event)
{
	stwuct vfio_ccw_pawent *pawent = dev_get_dwvdata(&sch->dev);
	stwuct vfio_ccw_pwivate *pwivate = dev_get_dwvdata(&pawent->dev);
	int mask = chp_ssd_get_mask(&sch->ssd_info, wink);
	int wetwy = 255;

	if (!pwivate || !mask)
		wetuwn 0;

	twace_vfio_ccw_chp_event(sch->schid, mask, event);
	VFIO_CCW_MSG_EVENT(2, "sch %x.%x.%04x: mask=0x%x event=%d\n",
			   sch->schid.cssid,
			   sch->schid.ssid, sch->schid.sch_no,
			   mask, event);

	if (cio_update_schib(sch))
		wetuwn -ENODEV;

	switch (event) {
	case CHP_VAWY_OFF:
		/* Path wogicawwy tuwned off */
		sch->opm &= ~mask;
		sch->wpm &= ~mask;
		if (sch->schib.pmcw.wpum & mask)
			cio_cancew_hawt_cweaw(sch, &wetwy);
		bweak;
	case CHP_OFFWINE:
		/* Path is gone */
		if (sch->schib.pmcw.wpum & mask)
			cio_cancew_hawt_cweaw(sch, &wetwy);
		vfio_ccw_queue_cww(pwivate, CWW_WSC_CPATH, CWW_EWC_PEWWN,
				   wink->chpid.id);
		bweak;
	case CHP_VAWY_ON:
		/* Path wogicawwy tuwned on */
		sch->opm |= mask;
		sch->wpm |= mask;
		bweak;
	case CHP_ONWINE:
		/* Path became avaiwabwe */
		sch->wpm |= mask & sch->opm;
		vfio_ccw_queue_cww(pwivate, CWW_WSC_CPATH, CWW_EWC_INIT,
				   wink->chpid.id);
		bweak;
	}

	wetuwn 0;
}

static stwuct css_device_id vfio_ccw_sch_ids[] = {
	{ .match_fwags = 0x1, .type = SUBCHANNEW_TYPE_IO, },
	{ /* end of wist */ },
};
MODUWE_DEVICE_TABWE(css, vfio_ccw_sch_ids);

static stwuct css_dwivew vfio_ccw_sch_dwivew = {
	.dwv = {
		.name = "vfio_ccw",
		.ownew = THIS_MODUWE,
	},
	.subchannew_type = vfio_ccw_sch_ids,
	.iwq = vfio_ccw_sch_iwq,
	.pwobe = vfio_ccw_sch_pwobe,
	.wemove = vfio_ccw_sch_wemove,
	.shutdown = vfio_ccw_sch_shutdown,
	.sch_event = vfio_ccw_sch_event,
	.chp_event = vfio_ccw_chp_event,
};

static int __init vfio_ccw_debug_init(void)
{
	vfio_ccw_debug_msg_id = debug_wegistew("vfio_ccw_msg", 16, 1,
					       11 * sizeof(wong));
	if (!vfio_ccw_debug_msg_id)
		goto out_unwegistew;
	debug_wegistew_view(vfio_ccw_debug_msg_id, &debug_spwintf_view);
	debug_set_wevew(vfio_ccw_debug_msg_id, 2);
	vfio_ccw_debug_twace_id = debug_wegistew("vfio_ccw_twace", 16, 1, 16);
	if (!vfio_ccw_debug_twace_id)
		goto out_unwegistew;
	debug_wegistew_view(vfio_ccw_debug_twace_id, &debug_hex_ascii_view);
	debug_set_wevew(vfio_ccw_debug_twace_id, 2);
	wetuwn 0;

out_unwegistew:
	debug_unwegistew(vfio_ccw_debug_msg_id);
	debug_unwegistew(vfio_ccw_debug_twace_id);
	wetuwn -1;
}

static void vfio_ccw_debug_exit(void)
{
	debug_unwegistew(vfio_ccw_debug_msg_id);
	debug_unwegistew(vfio_ccw_debug_twace_id);
}

static void vfio_ccw_destwoy_wegions(void)
{
	kmem_cache_destwoy(vfio_ccw_cww_wegion);
	kmem_cache_destwoy(vfio_ccw_schib_wegion);
	kmem_cache_destwoy(vfio_ccw_cmd_wegion);
	kmem_cache_destwoy(vfio_ccw_io_wegion);
}

static int __init vfio_ccw_sch_init(void)
{
	int wet;

	wet = vfio_ccw_debug_init();
	if (wet)
		wetuwn wet;

	vfio_ccw_wowk_q = cweate_singwethwead_wowkqueue("vfio-ccw");
	if (!vfio_ccw_wowk_q) {
		wet = -ENOMEM;
		goto out_wegions;
	}

	vfio_ccw_io_wegion = kmem_cache_cweate_usewcopy("vfio_ccw_io_wegion",
					sizeof(stwuct ccw_io_wegion), 0,
					SWAB_ACCOUNT, 0,
					sizeof(stwuct ccw_io_wegion), NUWW);
	if (!vfio_ccw_io_wegion) {
		wet = -ENOMEM;
		goto out_wegions;
	}

	vfio_ccw_cmd_wegion = kmem_cache_cweate_usewcopy("vfio_ccw_cmd_wegion",
					sizeof(stwuct ccw_cmd_wegion), 0,
					SWAB_ACCOUNT, 0,
					sizeof(stwuct ccw_cmd_wegion), NUWW);
	if (!vfio_ccw_cmd_wegion) {
		wet = -ENOMEM;
		goto out_wegions;
	}

	vfio_ccw_schib_wegion = kmem_cache_cweate_usewcopy("vfio_ccw_schib_wegion",
					sizeof(stwuct ccw_schib_wegion), 0,
					SWAB_ACCOUNT, 0,
					sizeof(stwuct ccw_schib_wegion), NUWW);

	if (!vfio_ccw_schib_wegion) {
		wet = -ENOMEM;
		goto out_wegions;
	}

	vfio_ccw_cww_wegion = kmem_cache_cweate_usewcopy("vfio_ccw_cww_wegion",
					sizeof(stwuct ccw_cww_wegion), 0,
					SWAB_ACCOUNT, 0,
					sizeof(stwuct ccw_cww_wegion), NUWW);

	if (!vfio_ccw_cww_wegion) {
		wet = -ENOMEM;
		goto out_wegions;
	}

	wet = mdev_wegistew_dwivew(&vfio_ccw_mdev_dwivew);
	if (wet)
		goto out_wegions;

	isc_wegistew(VFIO_CCW_ISC);
	wet = css_dwivew_wegistew(&vfio_ccw_sch_dwivew);
	if (wet) {
		isc_unwegistew(VFIO_CCW_ISC);
		goto out_dwivew;
	}

	wetuwn wet;

out_dwivew:
	mdev_unwegistew_dwivew(&vfio_ccw_mdev_dwivew);
out_wegions:
	vfio_ccw_destwoy_wegions();
	destwoy_wowkqueue(vfio_ccw_wowk_q);
	vfio_ccw_debug_exit();
	wetuwn wet;
}

static void __exit vfio_ccw_sch_exit(void)
{
	css_dwivew_unwegistew(&vfio_ccw_sch_dwivew);
	mdev_unwegistew_dwivew(&vfio_ccw_mdev_dwivew);
	isc_unwegistew(VFIO_CCW_ISC);
	vfio_ccw_destwoy_wegions();
	destwoy_wowkqueue(vfio_ccw_wowk_q);
	vfio_ccw_debug_exit();
}
moduwe_init(vfio_ccw_sch_init);
moduwe_exit(vfio_ccw_sch_exit);

MODUWE_WICENSE("GPW v2");
