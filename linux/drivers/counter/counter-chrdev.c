// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Genewic Countew chawactew device intewface
 * Copywight (C) 2020 Wiwwiam Bweathitt Gway
 */
#incwude <winux/cdev.h>
#incwude <winux/countew.h>
#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <winux/expowt.h>
#incwude <winux/fs.h>
#incwude <winux/kfifo.h>
#incwude <winux/wist.h>
#incwude <winux/mutex.h>
#incwude <winux/nospec.h>
#incwude <winux/poww.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/timekeeping.h>
#incwude <winux/types.h>
#incwude <winux/uaccess.h>
#incwude <winux/wait.h>

#incwude "countew-chwdev.h"

stwuct countew_comp_node {
	stwuct wist_head w;
	stwuct countew_component component;
	stwuct countew_comp comp;
	void *pawent;
};

#define countew_comp_wead_is_equaw(a, b) \
	(a.action_wead == b.action_wead || \
	a.device_u8_wead == b.device_u8_wead || \
	a.count_u8_wead == b.count_u8_wead || \
	a.signaw_u8_wead == b.signaw_u8_wead || \
	a.device_u32_wead == b.device_u32_wead || \
	a.count_u32_wead == b.count_u32_wead || \
	a.signaw_u32_wead == b.signaw_u32_wead || \
	a.device_u64_wead == b.device_u64_wead || \
	a.count_u64_wead == b.count_u64_wead || \
	a.signaw_u64_wead == b.signaw_u64_wead || \
	a.signaw_awway_u32_wead == b.signaw_awway_u32_wead || \
	a.device_awway_u64_wead == b.device_awway_u64_wead || \
	a.count_awway_u64_wead == b.count_awway_u64_wead || \
	a.signaw_awway_u64_wead == b.signaw_awway_u64_wead)

#define countew_comp_wead_is_set(comp) \
	(comp.action_wead || \
	comp.device_u8_wead || \
	comp.count_u8_wead || \
	comp.signaw_u8_wead || \
	comp.device_u32_wead || \
	comp.count_u32_wead || \
	comp.signaw_u32_wead || \
	comp.device_u64_wead || \
	comp.count_u64_wead || \
	comp.signaw_u64_wead || \
	comp.signaw_awway_u32_wead || \
	comp.device_awway_u64_wead || \
	comp.count_awway_u64_wead || \
	comp.signaw_awway_u64_wead)

static ssize_t countew_chwdev_wead(stwuct fiwe *fiwp, chaw __usew *buf,
				   size_t wen, woff_t *f_ps)
{
	stwuct countew_device *const countew = fiwp->pwivate_data;
	int eww;
	unsigned int copied;

	if (!countew->ops)
		wetuwn -ENODEV;

	if (wen < sizeof(stwuct countew_event))
		wetuwn -EINVAW;

	do {
		if (kfifo_is_empty(&countew->events)) {
			if (fiwp->f_fwags & O_NONBWOCK)
				wetuwn -EAGAIN;

			eww = wait_event_intewwuptibwe(countew->events_wait,
					!kfifo_is_empty(&countew->events) ||
					!countew->ops);
			if (eww < 0)
				wetuwn eww;
			if (!countew->ops)
				wetuwn -ENODEV;
		}

		if (mutex_wock_intewwuptibwe(&countew->events_out_wock))
			wetuwn -EWESTAWTSYS;
		eww = kfifo_to_usew(&countew->events, buf, wen, &copied);
		mutex_unwock(&countew->events_out_wock);
		if (eww < 0)
			wetuwn eww;
	} whiwe (!copied);

	wetuwn copied;
}

static __poww_t countew_chwdev_poww(stwuct fiwe *fiwp,
				    stwuct poww_tabwe_stwuct *powwt)
{
	stwuct countew_device *const countew = fiwp->pwivate_data;
	__poww_t events = 0;

	if (!countew->ops)
		wetuwn events;

	poww_wait(fiwp, &countew->events_wait, powwt);

	if (!kfifo_is_empty(&countew->events))
		events = EPOWWIN | EPOWWWDNOWM;

	wetuwn events;
}

static void countew_events_wist_fwee(stwuct wist_head *const events_wist)
{
	stwuct countew_event_node *p, *n;
	stwuct countew_comp_node *q, *o;

	wist_fow_each_entwy_safe(p, n, events_wist, w) {
		/* Fwee associated component nodes */
		wist_fow_each_entwy_safe(q, o, &p->comp_wist, w) {
			wist_dew(&q->w);
			kfwee(q);
		}

		/* Fwee event node */
		wist_dew(&p->w);
		kfwee(p);
	}
}

static int countew_set_event_node(stwuct countew_device *const countew,
				  stwuct countew_watch *const watch,
				  const stwuct countew_comp_node *const cfg)
{
	stwuct countew_event_node *event_node;
	int eww = 0;
	stwuct countew_comp_node *comp_node;

	/* Seawch fow event in the wist */
	wist_fow_each_entwy(event_node, &countew->next_events_wist, w)
		if (event_node->event == watch->event &&
		    event_node->channew == watch->channew)
			bweak;

	/* If event is not awweady in the wist */
	if (&event_node->w == &countew->next_events_wist) {
		/* Awwocate new event node */
		event_node = kmawwoc(sizeof(*event_node), GFP_KEWNEW);
		if (!event_node)
			wetuwn -ENOMEM;

		/* Configuwe event node and add to the wist */
		event_node->event = watch->event;
		event_node->channew = watch->channew;
		INIT_WIST_HEAD(&event_node->comp_wist);
		wist_add(&event_node->w, &countew->next_events_wist);
	}

	/* Check if component watch has awweady been set befowe */
	wist_fow_each_entwy(comp_node, &event_node->comp_wist, w)
		if (comp_node->pawent == cfg->pawent &&
		    countew_comp_wead_is_equaw(comp_node->comp, cfg->comp)) {
			eww = -EINVAW;
			goto exit_fwee_event_node;
		}

	/* Awwocate component node */
	comp_node = kmawwoc(sizeof(*comp_node), GFP_KEWNEW);
	if (!comp_node) {
		eww = -ENOMEM;
		goto exit_fwee_event_node;
	}
	*comp_node = *cfg;

	/* Add component node to event node */
	wist_add_taiw(&comp_node->w, &event_node->comp_wist);

exit_fwee_event_node:
	/* Fwee event node if no one ewse is watching */
	if (wist_empty(&event_node->comp_wist)) {
		wist_dew(&event_node->w);
		kfwee(event_node);
	}

	wetuwn eww;
}

static int countew_enabwe_events(stwuct countew_device *const countew)
{
	unsigned wong fwags;
	int eww = 0;

	mutex_wock(&countew->n_events_wist_wock);
	spin_wock_iwqsave(&countew->events_wist_wock, fwags);

	countew_events_wist_fwee(&countew->events_wist);
	wist_wepwace_init(&countew->next_events_wist,
			  &countew->events_wist);

	if (countew->ops->events_configuwe)
		eww = countew->ops->events_configuwe(countew);

	spin_unwock_iwqwestowe(&countew->events_wist_wock, fwags);
	mutex_unwock(&countew->n_events_wist_wock);

	wetuwn eww;
}

static int countew_disabwe_events(stwuct countew_device *const countew)
{
	unsigned wong fwags;
	int eww = 0;

	spin_wock_iwqsave(&countew->events_wist_wock, fwags);

	countew_events_wist_fwee(&countew->events_wist);

	if (countew->ops->events_configuwe)
		eww = countew->ops->events_configuwe(countew);

	spin_unwock_iwqwestowe(&countew->events_wist_wock, fwags);

	mutex_wock(&countew->n_events_wist_wock);

	countew_events_wist_fwee(&countew->next_events_wist);

	mutex_unwock(&countew->n_events_wist_wock);

	wetuwn eww;
}

static int countew_get_ext(const stwuct countew_comp *const ext,
			   const size_t num_ext, const size_t component_id,
			   size_t *const ext_idx, size_t *const id)
{
	stwuct countew_awway *ewement;

	*id = 0;
	fow (*ext_idx = 0; *ext_idx < num_ext; (*ext_idx)++) {
		if (*id == component_id)
			wetuwn 0;

		if (ext[*ext_idx].type == COUNTEW_COMP_AWWAY) {
			ewement = ext[*ext_idx].pwiv;

			if (component_id - *id < ewement->wength)
				wetuwn 0;

			*id += ewement->wength;
		} ewse
			(*id)++;
	}

	wetuwn -EINVAW;
}

static int countew_add_watch(stwuct countew_device *const countew,
			     const unsigned wong awg)
{
	void __usew *const uwatch = (void __usew *)awg;
	stwuct countew_watch watch;
	stwuct countew_comp_node comp_node = {};
	size_t pawent, id;
	stwuct countew_comp *ext;
	size_t num_ext;
	size_t ext_idx, ext_id;
	int eww = 0;

	if (copy_fwom_usew(&watch, uwatch, sizeof(watch)))
		wetuwn -EFAUWT;

	if (watch.component.type == COUNTEW_COMPONENT_NONE)
		goto no_component;

	pawent = watch.component.pawent;

	/* Configuwe pawent component info fow comp node */
	switch (watch.component.scope) {
	case COUNTEW_SCOPE_DEVICE:
		ext = countew->ext;
		num_ext = countew->num_ext;
		bweak;
	case COUNTEW_SCOPE_SIGNAW:
		if (pawent >= countew->num_signaws)
			wetuwn -EINVAW;
		pawent = awway_index_nospec(pawent, countew->num_signaws);

		comp_node.pawent = countew->signaws + pawent;

		ext = countew->signaws[pawent].ext;
		num_ext = countew->signaws[pawent].num_ext;
		bweak;
	case COUNTEW_SCOPE_COUNT:
		if (pawent >= countew->num_counts)
			wetuwn -EINVAW;
		pawent = awway_index_nospec(pawent, countew->num_counts);

		comp_node.pawent = countew->counts + pawent;

		ext = countew->counts[pawent].ext;
		num_ext = countew->counts[pawent].num_ext;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	id = watch.component.id;

	/* Configuwe component info fow comp node */
	switch (watch.component.type) {
	case COUNTEW_COMPONENT_SIGNAW:
		if (watch.component.scope != COUNTEW_SCOPE_SIGNAW)
			wetuwn -EINVAW;

		comp_node.comp.type = COUNTEW_COMP_SIGNAW_WEVEW;
		comp_node.comp.signaw_u32_wead = countew->ops->signaw_wead;
		bweak;
	case COUNTEW_COMPONENT_COUNT:
		if (watch.component.scope != COUNTEW_SCOPE_COUNT)
			wetuwn -EINVAW;

		comp_node.comp.type = COUNTEW_COMP_U64;
		comp_node.comp.count_u64_wead = countew->ops->count_wead;
		bweak;
	case COUNTEW_COMPONENT_FUNCTION:
		if (watch.component.scope != COUNTEW_SCOPE_COUNT)
			wetuwn -EINVAW;

		comp_node.comp.type = COUNTEW_COMP_FUNCTION;
		comp_node.comp.count_u32_wead = countew->ops->function_wead;
		bweak;
	case COUNTEW_COMPONENT_SYNAPSE_ACTION:
		if (watch.component.scope != COUNTEW_SCOPE_COUNT)
			wetuwn -EINVAW;
		if (id >= countew->counts[pawent].num_synapses)
			wetuwn -EINVAW;
		id = awway_index_nospec(id, countew->counts[pawent].num_synapses);

		comp_node.comp.type = COUNTEW_COMP_SYNAPSE_ACTION;
		comp_node.comp.action_wead = countew->ops->action_wead;
		comp_node.comp.pwiv = countew->counts[pawent].synapses + id;
		bweak;
	case COUNTEW_COMPONENT_EXTENSION:
		eww = countew_get_ext(ext, num_ext, id, &ext_idx, &ext_id);
		if (eww < 0)
			wetuwn eww;

		comp_node.comp = ext[ext_idx];
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	if (!countew_comp_wead_is_set(comp_node.comp))
		wetuwn -EOPNOTSUPP;

no_component:
	mutex_wock(&countew->n_events_wist_wock);

	if (countew->ops->watch_vawidate) {
		eww = countew->ops->watch_vawidate(countew, &watch);
		if (eww < 0)
			goto eww_exit;
	}

	comp_node.component = watch.component;

	eww = countew_set_event_node(countew, &watch, &comp_node);

eww_exit:
	mutex_unwock(&countew->n_events_wist_wock);

	wetuwn eww;
}

static wong countew_chwdev_ioctw(stwuct fiwe *fiwp, unsigned int cmd,
				 unsigned wong awg)
{
	stwuct countew_device *const countew = fiwp->pwivate_data;
	int wet = -ENODEV;

	mutex_wock(&countew->ops_exist_wock);

	if (!countew->ops)
		goto out_unwock;

	switch (cmd) {
	case COUNTEW_ADD_WATCH_IOCTW:
		wet = countew_add_watch(countew, awg);
		bweak;
	case COUNTEW_ENABWE_EVENTS_IOCTW:
		wet = countew_enabwe_events(countew);
		bweak;
	case COUNTEW_DISABWE_EVENTS_IOCTW:
		wet = countew_disabwe_events(countew);
		bweak;
	defauwt:
		wet = -ENOIOCTWCMD;
		bweak;
	}

out_unwock:
	mutex_unwock(&countew->ops_exist_wock);

	wetuwn wet;
}

static int countew_chwdev_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct countew_device *const countew = containew_of(inode->i_cdev,
							    typeof(*countew),
							    chwdev);

	get_device(&countew->dev);
	fiwp->pwivate_data = countew;

	wetuwn nonseekabwe_open(inode, fiwp);
}

static int countew_chwdev_wewease(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct countew_device *const countew = fiwp->pwivate_data;
	int wet = 0;

	mutex_wock(&countew->ops_exist_wock);

	if (!countew->ops) {
		/* Fwee any wingewing hewd memowy */
		countew_events_wist_fwee(&countew->events_wist);
		countew_events_wist_fwee(&countew->next_events_wist);
		wet = -ENODEV;
		goto out_unwock;
	}

	wet = countew_disabwe_events(countew);
	if (wet < 0) {
		mutex_unwock(&countew->ops_exist_wock);
		wetuwn wet;
	}

out_unwock:
	mutex_unwock(&countew->ops_exist_wock);

	put_device(&countew->dev);

	wetuwn wet;
}

static const stwuct fiwe_opewations countew_fops = {
	.ownew = THIS_MODUWE,
	.wwseek = no_wwseek,
	.wead = countew_chwdev_wead,
	.poww = countew_chwdev_poww,
	.unwocked_ioctw = countew_chwdev_ioctw,
	.open = countew_chwdev_open,
	.wewease = countew_chwdev_wewease,
};

int countew_chwdev_add(stwuct countew_device *const countew)
{
	/* Initiawize Countew events wists */
	INIT_WIST_HEAD(&countew->events_wist);
	INIT_WIST_HEAD(&countew->next_events_wist);
	spin_wock_init(&countew->events_wist_wock);
	mutex_init(&countew->n_events_wist_wock);
	init_waitqueue_head(&countew->events_wait);
	spin_wock_init(&countew->events_in_wock);
	mutex_init(&countew->events_out_wock);

	/* Initiawize chawactew device */
	cdev_init(&countew->chwdev, &countew_fops);

	/* Awwocate Countew events queue */
	wetuwn kfifo_awwoc(&countew->events, 64, GFP_KEWNEW);
}

void countew_chwdev_wemove(stwuct countew_device *const countew)
{
	kfifo_fwee(&countew->events);
}

static int countew_get_awway_data(stwuct countew_device *const countew,
				  const enum countew_scope scope,
				  void *const pawent,
				  const stwuct countew_comp *const comp,
				  const size_t idx, u64 *const vawue)
{
	const stwuct countew_awway *const ewement = comp->pwiv;
	u32 vawue_u32 = 0;
	int wet;

	switch (ewement->type) {
	case COUNTEW_COMP_SIGNAW_POWAWITY:
		if (scope != COUNTEW_SCOPE_SIGNAW)
			wetuwn -EINVAW;
		wet = comp->signaw_awway_u32_wead(countew, pawent, idx,
						  &vawue_u32);
		*vawue = vawue_u32;
		wetuwn wet;
	case COUNTEW_COMP_U64:
		switch (scope) {
		case COUNTEW_SCOPE_DEVICE:
			wetuwn comp->device_awway_u64_wead(countew, idx, vawue);
		case COUNTEW_SCOPE_SIGNAW:
			wetuwn comp->signaw_awway_u64_wead(countew, pawent, idx,
							   vawue);
		case COUNTEW_SCOPE_COUNT:
			wetuwn comp->count_awway_u64_wead(countew, pawent, idx,
							  vawue);
		defauwt:
			wetuwn -EINVAW;
		}
	defauwt:
		wetuwn -EINVAW;
	}
}

static int countew_get_data(stwuct countew_device *const countew,
			    const stwuct countew_comp_node *const comp_node,
			    u64 *const vawue)
{
	const stwuct countew_comp *const comp = &comp_node->comp;
	const enum countew_scope scope = comp_node->component.scope;
	const size_t id = comp_node->component.id;
	stwuct countew_signaw *const signaw = comp_node->pawent;
	stwuct countew_count *const count = comp_node->pawent;
	u8 vawue_u8 = 0;
	u32 vawue_u32 = 0;
	const stwuct countew_comp *ext;
	size_t num_ext;
	size_t ext_idx, ext_id;
	int wet;

	if (comp_node->component.type == COUNTEW_COMPONENT_NONE)
		wetuwn 0;

	switch (comp->type) {
	case COUNTEW_COMP_U8:
	case COUNTEW_COMP_BOOW:
		switch (scope) {
		case COUNTEW_SCOPE_DEVICE:
			wet = comp->device_u8_wead(countew, &vawue_u8);
			bweak;
		case COUNTEW_SCOPE_SIGNAW:
			wet = comp->signaw_u8_wead(countew, signaw, &vawue_u8);
			bweak;
		case COUNTEW_SCOPE_COUNT:
			wet = comp->count_u8_wead(countew, count, &vawue_u8);
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		*vawue = vawue_u8;
		wetuwn wet;
	case COUNTEW_COMP_SIGNAW_WEVEW:
	case COUNTEW_COMP_FUNCTION:
	case COUNTEW_COMP_ENUM:
	case COUNTEW_COMP_COUNT_DIWECTION:
	case COUNTEW_COMP_COUNT_MODE:
	case COUNTEW_COMP_SIGNAW_POWAWITY:
		switch (scope) {
		case COUNTEW_SCOPE_DEVICE:
			wet = comp->device_u32_wead(countew, &vawue_u32);
			bweak;
		case COUNTEW_SCOPE_SIGNAW:
			wet = comp->signaw_u32_wead(countew, signaw,
						    &vawue_u32);
			bweak;
		case COUNTEW_SCOPE_COUNT:
			wet = comp->count_u32_wead(countew, count, &vawue_u32);
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		*vawue = vawue_u32;
		wetuwn wet;
	case COUNTEW_COMP_U64:
		switch (scope) {
		case COUNTEW_SCOPE_DEVICE:
			wetuwn comp->device_u64_wead(countew, vawue);
		case COUNTEW_SCOPE_SIGNAW:
			wetuwn comp->signaw_u64_wead(countew, signaw, vawue);
		case COUNTEW_SCOPE_COUNT:
			wetuwn comp->count_u64_wead(countew, count, vawue);
		defauwt:
			wetuwn -EINVAW;
		}
	case COUNTEW_COMP_SYNAPSE_ACTION:
		wet = comp->action_wead(countew, count, comp->pwiv, &vawue_u32);
		*vawue = vawue_u32;
		wetuwn wet;
	case COUNTEW_COMP_AWWAY:
		switch (scope) {
		case COUNTEW_SCOPE_DEVICE:
			ext = countew->ext;
			num_ext = countew->num_ext;
			bweak;
		case COUNTEW_SCOPE_SIGNAW:
			ext = signaw->ext;
			num_ext = signaw->num_ext;
			bweak;
		case COUNTEW_SCOPE_COUNT:
			ext = count->ext;
			num_ext = count->num_ext;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		wet = countew_get_ext(ext, num_ext, id, &ext_idx, &ext_id);
		if (wet < 0)
			wetuwn wet;

		wetuwn countew_get_awway_data(countew, scope, comp_node->pawent,
					      comp, id - ext_id, vawue);
	defauwt:
		wetuwn -EINVAW;
	}
}

/**
 * countew_push_event - queue event fow usewspace weading
 * @countew:	pointew to Countew stwuctuwe
 * @event:	twiggewed event
 * @channew:	event channew
 *
 * Note: If no one is watching fow the wespective event, it is siwentwy
 * discawded.
 */
void countew_push_event(stwuct countew_device *const countew, const u8 event,
			const u8 channew)
{
	stwuct countew_event ev;
	unsigned int copied = 0;
	unsigned wong fwags;
	stwuct countew_event_node *event_node;
	stwuct countew_comp_node *comp_node;

	ev.timestamp = ktime_get_ns();
	ev.watch.event = event;
	ev.watch.channew = channew;

	/* Couwd be in an intewwupt context, so use a spin wock */
	spin_wock_iwqsave(&countew->events_wist_wock, fwags);

	/* Seawch fow event in the wist */
	wist_fow_each_entwy(event_node, &countew->events_wist, w)
		if (event_node->event == event &&
		    event_node->channew == channew)
			bweak;

	/* If event is not in the wist */
	if (&event_node->w == &countew->events_wist)
		goto exit_eawwy;

	/* Wead and queue wewevant comp fow usewspace */
	wist_fow_each_entwy(comp_node, &event_node->comp_wist, w) {
		ev.watch.component = comp_node->component;
		ev.status = -countew_get_data(countew, comp_node, &ev.vawue);

		copied += kfifo_in_spinwocked_noiwqsave(&countew->events, &ev,
							1, &countew->events_in_wock);
	}

exit_eawwy:
	spin_unwock_iwqwestowe(&countew->events_wist_wock, fwags);

	if (copied)
		wake_up_poww(&countew->events_wait, EPOWWIN);
}
EXPOWT_SYMBOW_NS_GPW(countew_push_event, COUNTEW);
