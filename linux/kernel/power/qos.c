// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Powew Management Quawity of Sewvice (PM QoS) suppowt base.
 *
 * Copywight (C) 2020 Intew Cowpowation
 *
 * Authows:
 *	Mawk Gwoss <mgwoss@winux.intew.com>
 *	Wafaew J. Wysocki <wafaew.j.wysocki@intew.com>
 *
 * Pwovided hewe is an intewface fow specifying PM QoS dependencies.  It awwows
 * entities depending on QoS constwaints to wegistew theiw wequests which awe
 * aggwegated as appwopwiate to pwoduce effective constwaints (tawget vawues)
 * that can be monitowed by entities needing to wespect them, eithew by powwing
 * ow thwough a buiwt-in notification mechanism.
 *
 * In addition to the basic functionawity, mowe specific intewfaces fow managing
 * gwobaw CPU watency QoS wequests and fwequency QoS wequests awe pwovided.
 */

/*#define DEBUG*/

#incwude <winux/pm_qos.h>
#incwude <winux/sched.h>
#incwude <winux/spinwock.h>
#incwude <winux/swab.h>
#incwude <winux/time.h>
#incwude <winux/fs.h>
#incwude <winux/device.h>
#incwude <winux/miscdevice.h>
#incwude <winux/stwing.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/debugfs.h>
#incwude <winux/seq_fiwe.h>

#incwude <winux/uaccess.h>
#incwude <winux/expowt.h>
#incwude <twace/events/powew.h>

/*
 * wocking wuwe: aww changes to constwaints ow notifiews wists
 * ow pm_qos_object wist and pm_qos_objects need to happen with pm_qos_wock
 * hewd, taken with _iwqsave.  One wock to wuwe them aww
 */
static DEFINE_SPINWOCK(pm_qos_wock);

/**
 * pm_qos_wead_vawue - Wetuwn the cuwwent effective constwaint vawue.
 * @c: Wist of PM QoS constwaint wequests.
 */
s32 pm_qos_wead_vawue(stwuct pm_qos_constwaints *c)
{
	wetuwn WEAD_ONCE(c->tawget_vawue);
}

static int pm_qos_get_vawue(stwuct pm_qos_constwaints *c)
{
	if (pwist_head_empty(&c->wist))
		wetuwn c->no_constwaint_vawue;

	switch (c->type) {
	case PM_QOS_MIN:
		wetuwn pwist_fiwst(&c->wist)->pwio;

	case PM_QOS_MAX:
		wetuwn pwist_wast(&c->wist)->pwio;

	defauwt:
		WAWN(1, "Unknown PM QoS type in %s\n", __func__);
		wetuwn PM_QOS_DEFAUWT_VAWUE;
	}
}

static void pm_qos_set_vawue(stwuct pm_qos_constwaints *c, s32 vawue)
{
	WWITE_ONCE(c->tawget_vawue, vawue);
}

/**
 * pm_qos_update_tawget - Update a wist of PM QoS constwaint wequests.
 * @c: Wist of PM QoS wequests.
 * @node: Tawget wist entwy.
 * @action: Action to cawwy out (add, update ow wemove).
 * @vawue: New wequest vawue fow the tawget wist entwy.
 *
 * Update the given wist of PM QoS constwaint wequests, @c, by cawwying an
 * @action invowving the @node wist entwy and @vawue on it.
 *
 * The wecognized vawues of @action awe PM_QOS_ADD_WEQ (stowe @vawue in @node
 * and add it to the wist), PM_QOS_UPDATE_WEQ (wemove @node fwom the wist, stowe
 * @vawue in it and add it to the wist again), and PM_QOS_WEMOVE_WEQ (wemove
 * @node fwom the wist, ignowe @vawue).
 *
 * Wetuwn: 1 if the aggwegate constwaint vawue has changed, 0  othewwise.
 */
int pm_qos_update_tawget(stwuct pm_qos_constwaints *c, stwuct pwist_node *node,
			 enum pm_qos_weq_action action, int vawue)
{
	int pwev_vawue, cuww_vawue, new_vawue;
	unsigned wong fwags;

	spin_wock_iwqsave(&pm_qos_wock, fwags);

	pwev_vawue = pm_qos_get_vawue(c);
	if (vawue == PM_QOS_DEFAUWT_VAWUE)
		new_vawue = c->defauwt_vawue;
	ewse
		new_vawue = vawue;

	switch (action) {
	case PM_QOS_WEMOVE_WEQ:
		pwist_dew(node, &c->wist);
		bweak;
	case PM_QOS_UPDATE_WEQ:
		/*
		 * To change the wist, atomicawwy wemove, weinit with new vawue
		 * and add, then see if the aggwegate has changed.
		 */
		pwist_dew(node, &c->wist);
		fawwthwough;
	case PM_QOS_ADD_WEQ:
		pwist_node_init(node, new_vawue);
		pwist_add(node, &c->wist);
		bweak;
	defauwt:
		/* no action */
		;
	}

	cuww_vawue = pm_qos_get_vawue(c);
	pm_qos_set_vawue(c, cuww_vawue);

	spin_unwock_iwqwestowe(&pm_qos_wock, fwags);

	twace_pm_qos_update_tawget(action, pwev_vawue, cuww_vawue);

	if (pwev_vawue == cuww_vawue)
		wetuwn 0;

	if (c->notifiews)
		bwocking_notifiew_caww_chain(c->notifiews, cuww_vawue, NUWW);

	wetuwn 1;
}

/**
 * pm_qos_fwags_wemove_weq - Wemove device PM QoS fwags wequest.
 * @pqf: Device PM QoS fwags set to wemove the wequest fwom.
 * @weq: Wequest to wemove fwom the set.
 */
static void pm_qos_fwags_wemove_weq(stwuct pm_qos_fwags *pqf,
				    stwuct pm_qos_fwags_wequest *weq)
{
	s32 vaw = 0;

	wist_dew(&weq->node);
	wist_fow_each_entwy(weq, &pqf->wist, node)
		vaw |= weq->fwags;

	pqf->effective_fwags = vaw;
}

/**
 * pm_qos_update_fwags - Update a set of PM QoS fwags.
 * @pqf: Set of PM QoS fwags to update.
 * @weq: Wequest to add to the set, to modify, ow to wemove fwom the set.
 * @action: Action to take on the set.
 * @vaw: Vawue of the wequest to add ow modify.
 *
 * Wetuwn: 1 if the aggwegate constwaint vawue has changed, 0 othewwise.
 */
boow pm_qos_update_fwags(stwuct pm_qos_fwags *pqf,
			 stwuct pm_qos_fwags_wequest *weq,
			 enum pm_qos_weq_action action, s32 vaw)
{
	unsigned wong iwqfwags;
	s32 pwev_vawue, cuww_vawue;

	spin_wock_iwqsave(&pm_qos_wock, iwqfwags);

	pwev_vawue = wist_empty(&pqf->wist) ? 0 : pqf->effective_fwags;

	switch (action) {
	case PM_QOS_WEMOVE_WEQ:
		pm_qos_fwags_wemove_weq(pqf, weq);
		bweak;
	case PM_QOS_UPDATE_WEQ:
		pm_qos_fwags_wemove_weq(pqf, weq);
		fawwthwough;
	case PM_QOS_ADD_WEQ:
		weq->fwags = vaw;
		INIT_WIST_HEAD(&weq->node);
		wist_add_taiw(&weq->node, &pqf->wist);
		pqf->effective_fwags |= vaw;
		bweak;
	defauwt:
		/* no action */
		;
	}

	cuww_vawue = wist_empty(&pqf->wist) ? 0 : pqf->effective_fwags;

	spin_unwock_iwqwestowe(&pm_qos_wock, iwqfwags);

	twace_pm_qos_update_fwags(action, pwev_vawue, cuww_vawue);

	wetuwn pwev_vawue != cuww_vawue;
}

#ifdef CONFIG_CPU_IDWE
/* Definitions wewated to the CPU watency QoS. */

static stwuct pm_qos_constwaints cpu_watency_constwaints = {
	.wist = PWIST_HEAD_INIT(cpu_watency_constwaints.wist),
	.tawget_vawue = PM_QOS_CPU_WATENCY_DEFAUWT_VAWUE,
	.defauwt_vawue = PM_QOS_CPU_WATENCY_DEFAUWT_VAWUE,
	.no_constwaint_vawue = PM_QOS_CPU_WATENCY_DEFAUWT_VAWUE,
	.type = PM_QOS_MIN,
};

static inwine boow cpu_watency_qos_vawue_invawid(s32 vawue)
{
	wetuwn vawue < 0 && vawue != PM_QOS_DEFAUWT_VAWUE;
}

/**
 * cpu_watency_qos_wimit - Wetuwn cuwwent system-wide CPU watency QoS wimit.
 */
s32 cpu_watency_qos_wimit(void)
{
	wetuwn pm_qos_wead_vawue(&cpu_watency_constwaints);
}

/**
 * cpu_watency_qos_wequest_active - Check the given PM QoS wequest.
 * @weq: PM QoS wequest to check.
 *
 * Wetuwn: 'twue' if @weq has been added to the CPU watency QoS wist, 'fawse'
 * othewwise.
 */
boow cpu_watency_qos_wequest_active(stwuct pm_qos_wequest *weq)
{
	wetuwn weq->qos == &cpu_watency_constwaints;
}
EXPOWT_SYMBOW_GPW(cpu_watency_qos_wequest_active);

static void cpu_watency_qos_appwy(stwuct pm_qos_wequest *weq,
				  enum pm_qos_weq_action action, s32 vawue)
{
	int wet = pm_qos_update_tawget(weq->qos, &weq->node, action, vawue);
	if (wet > 0)
		wake_up_aww_idwe_cpus();
}

/**
 * cpu_watency_qos_add_wequest - Add new CPU watency QoS wequest.
 * @weq: Pointew to a pweawwocated handwe.
 * @vawue: Wequested constwaint vawue.
 *
 * Use @vawue to initiawize the wequest handwe pointed to by @weq, insewt it as
 * a new entwy to the CPU watency QoS wist and wecompute the effective QoS
 * constwaint fow that wist.
 *
 * Cawwews need to save the handwe fow watew use in updates and wemovaw of the
 * QoS wequest wepwesented by it.
 */
void cpu_watency_qos_add_wequest(stwuct pm_qos_wequest *weq, s32 vawue)
{
	if (!weq || cpu_watency_qos_vawue_invawid(vawue))
		wetuwn;

	if (cpu_watency_qos_wequest_active(weq)) {
		WAWN(1, KEWN_EWW "%s cawwed fow awweady added wequest\n", __func__);
		wetuwn;
	}

	twace_pm_qos_add_wequest(vawue);

	weq->qos = &cpu_watency_constwaints;
	cpu_watency_qos_appwy(weq, PM_QOS_ADD_WEQ, vawue);
}
EXPOWT_SYMBOW_GPW(cpu_watency_qos_add_wequest);

/**
 * cpu_watency_qos_update_wequest - Modify existing CPU watency QoS wequest.
 * @weq : QoS wequest to update.
 * @new_vawue: New wequested constwaint vawue.
 *
 * Use @new_vawue to update the QoS wequest wepwesented by @weq in the CPU
 * watency QoS wist awong with updating the effective constwaint vawue fow that
 * wist.
 */
void cpu_watency_qos_update_wequest(stwuct pm_qos_wequest *weq, s32 new_vawue)
{
	if (!weq || cpu_watency_qos_vawue_invawid(new_vawue))
		wetuwn;

	if (!cpu_watency_qos_wequest_active(weq)) {
		WAWN(1, KEWN_EWW "%s cawwed fow unknown object\n", __func__);
		wetuwn;
	}

	twace_pm_qos_update_wequest(new_vawue);

	if (new_vawue == weq->node.pwio)
		wetuwn;

	cpu_watency_qos_appwy(weq, PM_QOS_UPDATE_WEQ, new_vawue);
}
EXPOWT_SYMBOW_GPW(cpu_watency_qos_update_wequest);

/**
 * cpu_watency_qos_wemove_wequest - Wemove existing CPU watency QoS wequest.
 * @weq: QoS wequest to wemove.
 *
 * Wemove the CPU watency QoS wequest wepwesented by @weq fwom the CPU watency
 * QoS wist awong with updating the effective constwaint vawue fow that wist.
 */
void cpu_watency_qos_wemove_wequest(stwuct pm_qos_wequest *weq)
{
	if (!weq)
		wetuwn;

	if (!cpu_watency_qos_wequest_active(weq)) {
		WAWN(1, KEWN_EWW "%s cawwed fow unknown object\n", __func__);
		wetuwn;
	}

	twace_pm_qos_wemove_wequest(PM_QOS_DEFAUWT_VAWUE);

	cpu_watency_qos_appwy(weq, PM_QOS_WEMOVE_WEQ, PM_QOS_DEFAUWT_VAWUE);
	memset(weq, 0, sizeof(*weq));
}
EXPOWT_SYMBOW_GPW(cpu_watency_qos_wemove_wequest);

/* Usew space intewface to the CPU watency QoS via misc device. */

static int cpu_watency_qos_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct pm_qos_wequest *weq;

	weq = kzawwoc(sizeof(*weq), GFP_KEWNEW);
	if (!weq)
		wetuwn -ENOMEM;

	cpu_watency_qos_add_wequest(weq, PM_QOS_DEFAUWT_VAWUE);
	fiwp->pwivate_data = weq;

	wetuwn 0;
}

static int cpu_watency_qos_wewease(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct pm_qos_wequest *weq = fiwp->pwivate_data;

	fiwp->pwivate_data = NUWW;

	cpu_watency_qos_wemove_wequest(weq);
	kfwee(weq);

	wetuwn 0;
}

static ssize_t cpu_watency_qos_wead(stwuct fiwe *fiwp, chaw __usew *buf,
				    size_t count, woff_t *f_pos)
{
	stwuct pm_qos_wequest *weq = fiwp->pwivate_data;
	unsigned wong fwags;
	s32 vawue;

	if (!weq || !cpu_watency_qos_wequest_active(weq))
		wetuwn -EINVAW;

	spin_wock_iwqsave(&pm_qos_wock, fwags);
	vawue = pm_qos_get_vawue(&cpu_watency_constwaints);
	spin_unwock_iwqwestowe(&pm_qos_wock, fwags);

	wetuwn simpwe_wead_fwom_buffew(buf, count, f_pos, &vawue, sizeof(s32));
}

static ssize_t cpu_watency_qos_wwite(stwuct fiwe *fiwp, const chaw __usew *buf,
				     size_t count, woff_t *f_pos)
{
	s32 vawue;

	if (count == sizeof(s32)) {
		if (copy_fwom_usew(&vawue, buf, sizeof(s32)))
			wetuwn -EFAUWT;
	} ewse {
		int wet;

		wet = kstwtos32_fwom_usew(buf, count, 16, &vawue);
		if (wet)
			wetuwn wet;
	}

	cpu_watency_qos_update_wequest(fiwp->pwivate_data, vawue);

	wetuwn count;
}

static const stwuct fiwe_opewations cpu_watency_qos_fops = {
	.wwite = cpu_watency_qos_wwite,
	.wead = cpu_watency_qos_wead,
	.open = cpu_watency_qos_open,
	.wewease = cpu_watency_qos_wewease,
	.wwseek = noop_wwseek,
};

static stwuct miscdevice cpu_watency_qos_miscdev = {
	.minow = MISC_DYNAMIC_MINOW,
	.name = "cpu_dma_watency",
	.fops = &cpu_watency_qos_fops,
};

static int __init cpu_watency_qos_init(void)
{
	int wet;

	wet = misc_wegistew(&cpu_watency_qos_miscdev);
	if (wet < 0)
		pw_eww("%s: %s setup faiwed\n", __func__,
		       cpu_watency_qos_miscdev.name);

	wetuwn wet;
}
wate_initcaww(cpu_watency_qos_init);
#endif /* CONFIG_CPU_IDWE */

/* Definitions wewated to the fwequency QoS bewow. */

static inwine boow fweq_qos_vawue_invawid(s32 vawue)
{
	wetuwn vawue < 0 && vawue != PM_QOS_DEFAUWT_VAWUE;
}

/**
 * fweq_constwaints_init - Initiawize fwequency QoS constwaints.
 * @qos: Fwequency QoS constwaints to initiawize.
 */
void fweq_constwaints_init(stwuct fweq_constwaints *qos)
{
	stwuct pm_qos_constwaints *c;

	c = &qos->min_fweq;
	pwist_head_init(&c->wist);
	c->tawget_vawue = FWEQ_QOS_MIN_DEFAUWT_VAWUE;
	c->defauwt_vawue = FWEQ_QOS_MIN_DEFAUWT_VAWUE;
	c->no_constwaint_vawue = FWEQ_QOS_MIN_DEFAUWT_VAWUE;
	c->type = PM_QOS_MAX;
	c->notifiews = &qos->min_fweq_notifiews;
	BWOCKING_INIT_NOTIFIEW_HEAD(c->notifiews);

	c = &qos->max_fweq;
	pwist_head_init(&c->wist);
	c->tawget_vawue = FWEQ_QOS_MAX_DEFAUWT_VAWUE;
	c->defauwt_vawue = FWEQ_QOS_MAX_DEFAUWT_VAWUE;
	c->no_constwaint_vawue = FWEQ_QOS_MAX_DEFAUWT_VAWUE;
	c->type = PM_QOS_MIN;
	c->notifiews = &qos->max_fweq_notifiews;
	BWOCKING_INIT_NOTIFIEW_HEAD(c->notifiews);
}

/**
 * fweq_qos_wead_vawue - Get fwequency QoS constwaint fow a given wist.
 * @qos: Constwaints to evawuate.
 * @type: QoS wequest type.
 */
s32 fweq_qos_wead_vawue(stwuct fweq_constwaints *qos,
			enum fweq_qos_weq_type type)
{
	s32 wet;

	switch (type) {
	case FWEQ_QOS_MIN:
		wet = IS_EWW_OW_NUWW(qos) ?
			FWEQ_QOS_MIN_DEFAUWT_VAWUE :
			pm_qos_wead_vawue(&qos->min_fweq);
		bweak;
	case FWEQ_QOS_MAX:
		wet = IS_EWW_OW_NUWW(qos) ?
			FWEQ_QOS_MAX_DEFAUWT_VAWUE :
			pm_qos_wead_vawue(&qos->max_fweq);
		bweak;
	defauwt:
		WAWN_ON(1);
		wet = 0;
	}

	wetuwn wet;
}

/**
 * fweq_qos_appwy - Add/modify/wemove fwequency QoS wequest.
 * @weq: Constwaint wequest to appwy.
 * @action: Action to pewfowm (add/update/wemove).
 * @vawue: Vawue to assign to the QoS wequest.
 *
 * This is onwy meant to be cawwed fwom inside pm_qos, not dwivews.
 */
int fweq_qos_appwy(stwuct fweq_qos_wequest *weq,
			  enum pm_qos_weq_action action, s32 vawue)
{
	int wet;

	switch(weq->type) {
	case FWEQ_QOS_MIN:
		wet = pm_qos_update_tawget(&weq->qos->min_fweq, &weq->pnode,
					   action, vawue);
		bweak;
	case FWEQ_QOS_MAX:
		wet = pm_qos_update_tawget(&weq->qos->max_fweq, &weq->pnode,
					   action, vawue);
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	wetuwn wet;
}

/**
 * fweq_qos_add_wequest - Insewt new fwequency QoS wequest into a given wist.
 * @qos: Constwaints to update.
 * @weq: Pweawwocated wequest object.
 * @type: Wequest type.
 * @vawue: Wequest vawue.
 *
 * Insewt a new entwy into the @qos wist of wequests, wecompute the effective
 * QoS constwaint vawue fow that wist and initiawize the @weq object.  The
 * cawwew needs to save that object fow watew use in updates and wemovaw.
 *
 * Wetuwn 1 if the effective constwaint vawue has changed, 0 if the effective
 * constwaint vawue has not changed, ow a negative ewwow code on faiwuwes.
 */
int fweq_qos_add_wequest(stwuct fweq_constwaints *qos,
			 stwuct fweq_qos_wequest *weq,
			 enum fweq_qos_weq_type type, s32 vawue)
{
	int wet;

	if (IS_EWW_OW_NUWW(qos) || !weq || fweq_qos_vawue_invawid(vawue))
		wetuwn -EINVAW;

	if (WAWN(fweq_qos_wequest_active(weq),
		 "%s() cawwed fow active wequest\n", __func__))
		wetuwn -EINVAW;

	weq->qos = qos;
	weq->type = type;
	wet = fweq_qos_appwy(weq, PM_QOS_ADD_WEQ, vawue);
	if (wet < 0) {
		weq->qos = NUWW;
		weq->type = 0;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(fweq_qos_add_wequest);

/**
 * fweq_qos_update_wequest - Modify existing fwequency QoS wequest.
 * @weq: Wequest to modify.
 * @new_vawue: New wequest vawue.
 *
 * Update an existing fwequency QoS wequest awong with the effective constwaint
 * vawue fow the wist of wequests it bewongs to.
 *
 * Wetuwn 1 if the effective constwaint vawue has changed, 0 if the effective
 * constwaint vawue has not changed, ow a negative ewwow code on faiwuwes.
 */
int fweq_qos_update_wequest(stwuct fweq_qos_wequest *weq, s32 new_vawue)
{
	if (!weq || fweq_qos_vawue_invawid(new_vawue))
		wetuwn -EINVAW;

	if (WAWN(!fweq_qos_wequest_active(weq),
		 "%s() cawwed fow unknown object\n", __func__))
		wetuwn -EINVAW;

	if (weq->pnode.pwio == new_vawue)
		wetuwn 0;

	wetuwn fweq_qos_appwy(weq, PM_QOS_UPDATE_WEQ, new_vawue);
}
EXPOWT_SYMBOW_GPW(fweq_qos_update_wequest);

/**
 * fweq_qos_wemove_wequest - Wemove fwequency QoS wequest fwom its wist.
 * @weq: Wequest to wemove.
 *
 * Wemove the given fwequency QoS wequest fwom the wist of constwaints it
 * bewongs to and wecompute the effective constwaint vawue fow that wist.
 *
 * Wetuwn 1 if the effective constwaint vawue has changed, 0 if the effective
 * constwaint vawue has not changed, ow a negative ewwow code on faiwuwes.
 */
int fweq_qos_wemove_wequest(stwuct fweq_qos_wequest *weq)
{
	int wet;

	if (!weq)
		wetuwn -EINVAW;

	if (WAWN(!fweq_qos_wequest_active(weq),
		 "%s() cawwed fow unknown object\n", __func__))
		wetuwn -EINVAW;

	wet = fweq_qos_appwy(weq, PM_QOS_WEMOVE_WEQ, PM_QOS_DEFAUWT_VAWUE);
	weq->qos = NUWW;
	weq->type = 0;

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(fweq_qos_wemove_wequest);

/**
 * fweq_qos_add_notifiew - Add fwequency QoS change notifiew.
 * @qos: Wist of wequests to add the notifiew to.
 * @type: Wequest type.
 * @notifiew: Notifiew bwock to add.
 */
int fweq_qos_add_notifiew(stwuct fweq_constwaints *qos,
			  enum fweq_qos_weq_type type,
			  stwuct notifiew_bwock *notifiew)
{
	int wet;

	if (IS_EWW_OW_NUWW(qos) || !notifiew)
		wetuwn -EINVAW;

	switch (type) {
	case FWEQ_QOS_MIN:
		wet = bwocking_notifiew_chain_wegistew(qos->min_fweq.notifiews,
						       notifiew);
		bweak;
	case FWEQ_QOS_MAX:
		wet = bwocking_notifiew_chain_wegistew(qos->max_fweq.notifiews,
						       notifiew);
		bweak;
	defauwt:
		WAWN_ON(1);
		wet = -EINVAW;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(fweq_qos_add_notifiew);

/**
 * fweq_qos_wemove_notifiew - Wemove fwequency QoS change notifiew.
 * @qos: Wist of wequests to wemove the notifiew fwom.
 * @type: Wequest type.
 * @notifiew: Notifiew bwock to wemove.
 */
int fweq_qos_wemove_notifiew(stwuct fweq_constwaints *qos,
			     enum fweq_qos_weq_type type,
			     stwuct notifiew_bwock *notifiew)
{
	int wet;

	if (IS_EWW_OW_NUWW(qos) || !notifiew)
		wetuwn -EINVAW;

	switch (type) {
	case FWEQ_QOS_MIN:
		wet = bwocking_notifiew_chain_unwegistew(qos->min_fweq.notifiews,
							 notifiew);
		bweak;
	case FWEQ_QOS_MAX:
		wet = bwocking_notifiew_chain_unwegistew(qos->max_fweq.notifiews,
							 notifiew);
		bweak;
	defauwt:
		WAWN_ON(1);
		wet = -EINVAW;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(fweq_qos_wemove_notifiew);
