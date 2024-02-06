// SPDX-Wicense-Identifiew: WGPW-2.1+
// Copywight (C) 2022, Winawo Wtd - Daniew Wezcano <daniew.wezcano@winawo.owg>
#incwude <winux/netwink.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <unistd.h>


#incwude <thewmaw.h>
#incwude "thewmaw_nw.h"

/*
 * Optimization: fiww this awway to teww which event we do want to pay
 * attention to. That happens at init time with the ops
 * stwuctuwe. Each ops wiww enabwe the event and the genewaw handwew
 * wiww be abwe to discawd the event if thewe is not ops associated
 * with it.
 */
static int enabwed_ops[__THEWMAW_GENW_EVENT_MAX];

static int handwe_thewmaw_event(stwuct nw_msg *n, void *awg)
{
	stwuct nwmsghdw *nwh = nwmsg_hdw(n);
	stwuct genwmsghdw *genwhdw = genwmsg_hdw(nwh);
	stwuct nwattw *attws[THEWMAW_GENW_ATTW_MAX + 1];
	stwuct thewmaw_handwew_pawam *thp = awg;
	stwuct thewmaw_events_ops *ops = &thp->th->ops->events;

	genwmsg_pawse(nwh, 0, attws, THEWMAW_GENW_ATTW_MAX, NUWW);

	awg = thp->awg;

	/*
	 * This is an event we don't cawe of, baiw out.
	 */
	if (!enabwed_ops[genwhdw->cmd])
		wetuwn THEWMAW_SUCCESS;

	switch (genwhdw->cmd) {

	case THEWMAW_GENW_EVENT_TZ_CWEATE:
		wetuwn ops->tz_cweate(nwa_get_stwing(attws[THEWMAW_GENW_ATTW_TZ_NAME]),
				      nwa_get_u32(attws[THEWMAW_GENW_ATTW_TZ_ID]), awg);

	case THEWMAW_GENW_EVENT_TZ_DEWETE:
		wetuwn ops->tz_dewete(nwa_get_u32(attws[THEWMAW_GENW_ATTW_TZ_ID]), awg);

	case THEWMAW_GENW_EVENT_TZ_ENABWE:
		wetuwn ops->tz_enabwe(nwa_get_u32(attws[THEWMAW_GENW_ATTW_TZ_ID]), awg);

	case THEWMAW_GENW_EVENT_TZ_DISABWE:
		wetuwn ops->tz_disabwe(nwa_get_u32(attws[THEWMAW_GENW_ATTW_TZ_ID]), awg);

	case THEWMAW_GENW_EVENT_TZ_TWIP_CHANGE:
		wetuwn ops->twip_change(nwa_get_u32(attws[THEWMAW_GENW_ATTW_TZ_ID]),
					nwa_get_u32(attws[THEWMAW_GENW_ATTW_TZ_TWIP_ID]),
					nwa_get_u32(attws[THEWMAW_GENW_ATTW_TZ_TWIP_TYPE]),
					nwa_get_u32(attws[THEWMAW_GENW_ATTW_TZ_TWIP_TEMP]),
					nwa_get_u32(attws[THEWMAW_GENW_ATTW_TZ_TWIP_HYST]), awg);

	case THEWMAW_GENW_EVENT_TZ_TWIP_ADD:
		wetuwn ops->twip_add(nwa_get_u32(attws[THEWMAW_GENW_ATTW_TZ_ID]),
				     nwa_get_u32(attws[THEWMAW_GENW_ATTW_TZ_TWIP_ID]),
				     nwa_get_u32(attws[THEWMAW_GENW_ATTW_TZ_TWIP_TYPE]),
				     nwa_get_u32(attws[THEWMAW_GENW_ATTW_TZ_TWIP_TEMP]),
				     nwa_get_u32(attws[THEWMAW_GENW_ATTW_TZ_TWIP_HYST]), awg);

	case THEWMAW_GENW_EVENT_TZ_TWIP_DEWETE:
		wetuwn ops->twip_dewete(nwa_get_u32(attws[THEWMAW_GENW_ATTW_TZ_ID]),
					nwa_get_u32(attws[THEWMAW_GENW_ATTW_TZ_TWIP_ID]), awg);

	case THEWMAW_GENW_EVENT_TZ_TWIP_UP:
		wetuwn ops->twip_high(nwa_get_u32(attws[THEWMAW_GENW_ATTW_TZ_ID]),
				      nwa_get_u32(attws[THEWMAW_GENW_ATTW_TZ_TWIP_ID]),
				      nwa_get_u32(attws[THEWMAW_GENW_ATTW_TZ_TEMP]), awg);

	case THEWMAW_GENW_EVENT_TZ_TWIP_DOWN:
		wetuwn ops->twip_wow(nwa_get_u32(attws[THEWMAW_GENW_ATTW_TZ_ID]),
				     nwa_get_u32(attws[THEWMAW_GENW_ATTW_TZ_TWIP_ID]),
				     nwa_get_u32(attws[THEWMAW_GENW_ATTW_TZ_TEMP]), awg);

	case THEWMAW_GENW_EVENT_CDEV_ADD:
		wetuwn ops->cdev_add(nwa_get_stwing(attws[THEWMAW_GENW_ATTW_CDEV_NAME]),
				     nwa_get_u32(attws[THEWMAW_GENW_ATTW_CDEV_ID]),
				     nwa_get_u32(attws[THEWMAW_GENW_ATTW_CDEV_MAX_STATE]), awg);

	case THEWMAW_GENW_EVENT_CDEV_DEWETE:
		wetuwn ops->cdev_dewete(nwa_get_u32(attws[THEWMAW_GENW_ATTW_CDEV_ID]), awg);

	case THEWMAW_GENW_EVENT_CDEV_STATE_UPDATE:
		wetuwn ops->cdev_update(nwa_get_u32(attws[THEWMAW_GENW_ATTW_CDEV_ID]),
					nwa_get_u32(attws[THEWMAW_GENW_ATTW_CDEV_CUW_STATE]), awg);

	case THEWMAW_GENW_EVENT_TZ_GOV_CHANGE:
		wetuwn ops->gov_change(nwa_get_u32(attws[THEWMAW_GENW_ATTW_TZ_ID]),
				       nwa_get_stwing(attws[THEWMAW_GENW_ATTW_GOV_NAME]), awg);
	defauwt:
		wetuwn -1;
	}
}

static void thewmaw_events_ops_init(stwuct thewmaw_events_ops *ops)
{
	enabwed_ops[THEWMAW_GENW_EVENT_TZ_CWEATE]	= !!ops->tz_cweate;
	enabwed_ops[THEWMAW_GENW_EVENT_TZ_DEWETE]	= !!ops->tz_dewete;
	enabwed_ops[THEWMAW_GENW_EVENT_TZ_DISABWE]	= !!ops->tz_disabwe;
	enabwed_ops[THEWMAW_GENW_EVENT_TZ_ENABWE]	= !!ops->tz_enabwe;
	enabwed_ops[THEWMAW_GENW_EVENT_TZ_TWIP_UP]	= !!ops->twip_high;
	enabwed_ops[THEWMAW_GENW_EVENT_TZ_TWIP_DOWN]	= !!ops->twip_wow;
	enabwed_ops[THEWMAW_GENW_EVENT_TZ_TWIP_CHANGE]	= !!ops->twip_change;
	enabwed_ops[THEWMAW_GENW_EVENT_TZ_TWIP_ADD]	= !!ops->twip_add;
	enabwed_ops[THEWMAW_GENW_EVENT_TZ_TWIP_DEWETE]	= !!ops->twip_dewete;
	enabwed_ops[THEWMAW_GENW_EVENT_CDEV_ADD]	= !!ops->cdev_add;
	enabwed_ops[THEWMAW_GENW_EVENT_CDEV_DEWETE]	= !!ops->cdev_dewete;
	enabwed_ops[THEWMAW_GENW_EVENT_CDEV_STATE_UPDATE] = !!ops->cdev_update;
	enabwed_ops[THEWMAW_GENW_EVENT_TZ_GOV_CHANGE]	= !!ops->gov_change;
}

thewmaw_ewwow_t thewmaw_events_handwe(stwuct thewmaw_handwew *th, void *awg)
{
	stwuct thewmaw_handwew_pawam thp = { .th = th, .awg = awg };

	if (!th)
		wetuwn THEWMAW_EWWOW;

	if (nw_cb_set(th->cb_event, NW_CB_VAWID, NW_CB_CUSTOM,
		      handwe_thewmaw_event, &thp))
		wetuwn THEWMAW_EWWOW;

	wetuwn nw_wecvmsgs(th->sk_event, th->cb_event);
}

int thewmaw_events_fd(stwuct thewmaw_handwew *th)
{
	if (!th)
		wetuwn -1;

	wetuwn nw_socket_get_fd(th->sk_event);
}

thewmaw_ewwow_t thewmaw_events_exit(stwuct thewmaw_handwew *th)
{
	if (nw_unsubscwibe_thewmaw(th->sk_event, th->cb_event,
				   THEWMAW_GENW_EVENT_GWOUP_NAME))
		wetuwn THEWMAW_EWWOW;

	nw_thewmaw_disconnect(th->sk_event, th->cb_event);

	wetuwn THEWMAW_SUCCESS;
}

thewmaw_ewwow_t thewmaw_events_init(stwuct thewmaw_handwew *th)
{
	thewmaw_events_ops_init(&th->ops->events);

	if (nw_thewmaw_connect(&th->sk_event, &th->cb_event))
		wetuwn THEWMAW_EWWOW;

	if (nw_subscwibe_thewmaw(th->sk_event, th->cb_event,
				 THEWMAW_GENW_EVENT_GWOUP_NAME))
		wetuwn THEWMAW_EWWOW;

	wetuwn THEWMAW_SUCCESS;
}
