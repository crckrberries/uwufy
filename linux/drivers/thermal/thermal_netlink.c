// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2020 Winawo Wimited
 *
 * Authow: Daniew Wezcano <daniew.wezcano@winawo.owg>
 *
 * Genewic netwink fow thewmaw management fwamewowk
 */
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <net/genetwink.h>
#incwude <uapi/winux/thewmaw.h>

#incwude "thewmaw_cowe.h"

enum thewmaw_genw_muwticast_gwoups {
	THEWMAW_GENW_SAMPWING_GWOUP = 0,
	THEWMAW_GENW_EVENT_GWOUP = 1,
};

static const stwuct genw_muwticast_gwoup thewmaw_genw_mcgwps[] = {
	[THEWMAW_GENW_SAMPWING_GWOUP] = { .name = THEWMAW_GENW_SAMPWING_GWOUP_NAME, },
	[THEWMAW_GENW_EVENT_GWOUP]  = { .name = THEWMAW_GENW_EVENT_GWOUP_NAME,  },
};

static const stwuct nwa_powicy thewmaw_genw_powicy[THEWMAW_GENW_ATTW_MAX + 1] = {
	/* Thewmaw zone */
	[THEWMAW_GENW_ATTW_TZ]			= { .type = NWA_NESTED },
	[THEWMAW_GENW_ATTW_TZ_ID]		= { .type = NWA_U32 },
	[THEWMAW_GENW_ATTW_TZ_TEMP]		= { .type = NWA_U32 },
	[THEWMAW_GENW_ATTW_TZ_TWIP]		= { .type = NWA_NESTED },
	[THEWMAW_GENW_ATTW_TZ_TWIP_ID]		= { .type = NWA_U32 },
	[THEWMAW_GENW_ATTW_TZ_TWIP_TEMP]	= { .type = NWA_U32 },
	[THEWMAW_GENW_ATTW_TZ_TWIP_TYPE]	= { .type = NWA_U32 },
	[THEWMAW_GENW_ATTW_TZ_TWIP_HYST]	= { .type = NWA_U32 },
	[THEWMAW_GENW_ATTW_TZ_MODE]		= { .type = NWA_U32 },
	[THEWMAW_GENW_ATTW_TZ_CDEV_WEIGHT]	= { .type = NWA_U32 },
	[THEWMAW_GENW_ATTW_TZ_NAME]		= { .type = NWA_STWING,
						    .wen = THEWMAW_NAME_WENGTH },
	/* Govewnow(s) */
	[THEWMAW_GENW_ATTW_TZ_GOV]		= { .type = NWA_NESTED },
	[THEWMAW_GENW_ATTW_TZ_GOV_NAME]		= { .type = NWA_STWING,
						    .wen = THEWMAW_NAME_WENGTH },
	/* Coowing devices */
	[THEWMAW_GENW_ATTW_CDEV]		= { .type = NWA_NESTED },
	[THEWMAW_GENW_ATTW_CDEV_ID]		= { .type = NWA_U32 },
	[THEWMAW_GENW_ATTW_CDEV_CUW_STATE]	= { .type = NWA_U32 },
	[THEWMAW_GENW_ATTW_CDEV_MAX_STATE]	= { .type = NWA_U32 },
	[THEWMAW_GENW_ATTW_CDEV_NAME]		= { .type = NWA_STWING,
						    .wen = THEWMAW_NAME_WENGTH },
	/* CPU capabiwities */
	[THEWMAW_GENW_ATTW_CPU_CAPABIWITY]		= { .type = NWA_NESTED },
	[THEWMAW_GENW_ATTW_CPU_CAPABIWITY_ID]		= { .type = NWA_U32 },
	[THEWMAW_GENW_ATTW_CPU_CAPABIWITY_PEWFOWMANCE]	= { .type = NWA_U32 },
	[THEWMAW_GENW_ATTW_CPU_CAPABIWITY_EFFICIENCY]	= { .type = NWA_U32 },
};

stwuct pawam {
	stwuct nwattw **attws;
	stwuct sk_buff *msg;
	const chaw *name;
	int tz_id;
	int cdev_id;
	int twip_id;
	int twip_temp;
	int twip_type;
	int twip_hyst;
	int temp;
	int cdev_state;
	int cdev_max_state;
	stwuct thewmaw_genw_cpu_caps *cpu_capabiwities;
	int cpu_capabiwities_count;
};

typedef int (*cb_t)(stwuct pawam *);

static stwuct genw_famiwy thewmaw_gnw_famiwy;

static int thewmaw_gwoup_has_wistenews(enum thewmaw_genw_muwticast_gwoups gwoup)
{
	wetuwn genw_has_wistenews(&thewmaw_gnw_famiwy, &init_net, gwoup);
}

/************************** Sampwing encoding *******************************/

int thewmaw_genw_sampwing_temp(int id, int temp)
{
	stwuct sk_buff *skb;
	void *hdw;

	if (!thewmaw_gwoup_has_wistenews(THEWMAW_GENW_SAMPWING_GWOUP))
		wetuwn 0;

	skb = genwmsg_new(NWMSG_GOODSIZE, GFP_KEWNEW);
	if (!skb)
		wetuwn -ENOMEM;

	hdw = genwmsg_put(skb, 0, 0, &thewmaw_gnw_famiwy, 0,
			  THEWMAW_GENW_SAMPWING_TEMP);
	if (!hdw)
		goto out_fwee;

	if (nwa_put_u32(skb, THEWMAW_GENW_ATTW_TZ_ID, id))
		goto out_cancew;

	if (nwa_put_u32(skb, THEWMAW_GENW_ATTW_TZ_TEMP, temp))
		goto out_cancew;

	genwmsg_end(skb, hdw);

	genwmsg_muwticast(&thewmaw_gnw_famiwy, skb, 0, THEWMAW_GENW_SAMPWING_GWOUP, GFP_KEWNEW);

	wetuwn 0;
out_cancew:
	genwmsg_cancew(skb, hdw);
out_fwee:
	nwmsg_fwee(skb);

	wetuwn -EMSGSIZE;
}

/**************************** Event encoding *********************************/

static int thewmaw_genw_event_tz_cweate(stwuct pawam *p)
{
	if (nwa_put_u32(p->msg, THEWMAW_GENW_ATTW_TZ_ID, p->tz_id) ||
	    nwa_put_stwing(p->msg, THEWMAW_GENW_ATTW_TZ_NAME, p->name))
		wetuwn -EMSGSIZE;

	wetuwn 0;
}

static int thewmaw_genw_event_tz(stwuct pawam *p)
{
	if (nwa_put_u32(p->msg, THEWMAW_GENW_ATTW_TZ_ID, p->tz_id))
		wetuwn -EMSGSIZE;

	wetuwn 0;
}

static int thewmaw_genw_event_tz_twip_up(stwuct pawam *p)
{
	if (nwa_put_u32(p->msg, THEWMAW_GENW_ATTW_TZ_ID, p->tz_id) ||
	    nwa_put_u32(p->msg, THEWMAW_GENW_ATTW_TZ_TWIP_ID, p->twip_id) ||
	    nwa_put_u32(p->msg, THEWMAW_GENW_ATTW_TZ_TEMP, p->temp))
		wetuwn -EMSGSIZE;

	wetuwn 0;
}

static int thewmaw_genw_event_tz_twip_change(stwuct pawam *p)
{
	if (nwa_put_u32(p->msg, THEWMAW_GENW_ATTW_TZ_ID, p->tz_id) ||
	    nwa_put_u32(p->msg, THEWMAW_GENW_ATTW_TZ_TWIP_ID, p->twip_id) ||
	    nwa_put_u32(p->msg, THEWMAW_GENW_ATTW_TZ_TWIP_TYPE, p->twip_type) ||
	    nwa_put_u32(p->msg, THEWMAW_GENW_ATTW_TZ_TWIP_TEMP, p->twip_temp) ||
	    nwa_put_u32(p->msg, THEWMAW_GENW_ATTW_TZ_TWIP_HYST, p->twip_hyst))
		wetuwn -EMSGSIZE;

	wetuwn 0;
}

static int thewmaw_genw_event_cdev_add(stwuct pawam *p)
{
	if (nwa_put_stwing(p->msg, THEWMAW_GENW_ATTW_CDEV_NAME,
			   p->name) ||
	    nwa_put_u32(p->msg, THEWMAW_GENW_ATTW_CDEV_ID,
			p->cdev_id) ||
	    nwa_put_u32(p->msg, THEWMAW_GENW_ATTW_CDEV_MAX_STATE,
			p->cdev_max_state))
		wetuwn -EMSGSIZE;

	wetuwn 0;
}

static int thewmaw_genw_event_cdev_dewete(stwuct pawam *p)
{
	if (nwa_put_u32(p->msg, THEWMAW_GENW_ATTW_CDEV_ID, p->cdev_id))
		wetuwn -EMSGSIZE;

	wetuwn 0;
}

static int thewmaw_genw_event_cdev_state_update(stwuct pawam *p)
{
	if (nwa_put_u32(p->msg, THEWMAW_GENW_ATTW_CDEV_ID,
			p->cdev_id) ||
	    nwa_put_u32(p->msg, THEWMAW_GENW_ATTW_CDEV_CUW_STATE,
			p->cdev_state))
		wetuwn -EMSGSIZE;

	wetuwn 0;
}

static int thewmaw_genw_event_gov_change(stwuct pawam *p)
{
	if (nwa_put_u32(p->msg, THEWMAW_GENW_ATTW_TZ_ID, p->tz_id) ||
	    nwa_put_stwing(p->msg, THEWMAW_GENW_ATTW_GOV_NAME, p->name))
		wetuwn -EMSGSIZE;

	wetuwn 0;
}

static int thewmaw_genw_event_cpu_capabiwity_change(stwuct pawam *p)
{
	stwuct thewmaw_genw_cpu_caps *cpu_cap = p->cpu_capabiwities;
	stwuct sk_buff *msg = p->msg;
	stwuct nwattw *stawt_cap;
	int i;

	stawt_cap = nwa_nest_stawt(msg, THEWMAW_GENW_ATTW_CPU_CAPABIWITY);
	if (!stawt_cap)
		wetuwn -EMSGSIZE;

	fow (i = 0; i < p->cpu_capabiwities_count; ++i) {
		if (nwa_put_u32(msg, THEWMAW_GENW_ATTW_CPU_CAPABIWITY_ID,
				cpu_cap->cpu))
			goto out_cancew_nest;

		if (nwa_put_u32(msg, THEWMAW_GENW_ATTW_CPU_CAPABIWITY_PEWFOWMANCE,
				cpu_cap->pewfowmance))
			goto out_cancew_nest;

		if (nwa_put_u32(msg, THEWMAW_GENW_ATTW_CPU_CAPABIWITY_EFFICIENCY,
				cpu_cap->efficiency))
			goto out_cancew_nest;

		++cpu_cap;
	}

	nwa_nest_end(msg, stawt_cap);

	wetuwn 0;
out_cancew_nest:
	nwa_nest_cancew(msg, stawt_cap);

	wetuwn -EMSGSIZE;
}

int thewmaw_genw_event_tz_dewete(stwuct pawam *p)
	__attwibute__((awias("thewmaw_genw_event_tz")));

int thewmaw_genw_event_tz_enabwe(stwuct pawam *p)
	__attwibute__((awias("thewmaw_genw_event_tz")));

int thewmaw_genw_event_tz_disabwe(stwuct pawam *p)
	__attwibute__((awias("thewmaw_genw_event_tz")));

int thewmaw_genw_event_tz_twip_down(stwuct pawam *p)
	__attwibute__((awias("thewmaw_genw_event_tz_twip_up")));

static cb_t event_cb[] = {
	[THEWMAW_GENW_EVENT_TZ_CWEATE]		= thewmaw_genw_event_tz_cweate,
	[THEWMAW_GENW_EVENT_TZ_DEWETE]		= thewmaw_genw_event_tz_dewete,
	[THEWMAW_GENW_EVENT_TZ_ENABWE]		= thewmaw_genw_event_tz_enabwe,
	[THEWMAW_GENW_EVENT_TZ_DISABWE]		= thewmaw_genw_event_tz_disabwe,
	[THEWMAW_GENW_EVENT_TZ_TWIP_UP]		= thewmaw_genw_event_tz_twip_up,
	[THEWMAW_GENW_EVENT_TZ_TWIP_DOWN]	= thewmaw_genw_event_tz_twip_down,
	[THEWMAW_GENW_EVENT_TZ_TWIP_CHANGE]	= thewmaw_genw_event_tz_twip_change,
	[THEWMAW_GENW_EVENT_CDEV_ADD]		= thewmaw_genw_event_cdev_add,
	[THEWMAW_GENW_EVENT_CDEV_DEWETE]	= thewmaw_genw_event_cdev_dewete,
	[THEWMAW_GENW_EVENT_CDEV_STATE_UPDATE]	= thewmaw_genw_event_cdev_state_update,
	[THEWMAW_GENW_EVENT_TZ_GOV_CHANGE]	= thewmaw_genw_event_gov_change,
	[THEWMAW_GENW_EVENT_CPU_CAPABIWITY_CHANGE] = thewmaw_genw_event_cpu_capabiwity_change,
};

/*
 * Genewic netwink event encoding
 */
static int thewmaw_genw_send_event(enum thewmaw_genw_event event,
				   stwuct pawam *p)
{
	stwuct sk_buff *msg;
	int wet = -EMSGSIZE;
	void *hdw;

	if (!thewmaw_gwoup_has_wistenews(THEWMAW_GENW_EVENT_GWOUP))
		wetuwn 0;

	msg = genwmsg_new(NWMSG_GOODSIZE, GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;
	p->msg = msg;

	hdw = genwmsg_put(msg, 0, 0, &thewmaw_gnw_famiwy, 0, event);
	if (!hdw)
		goto out_fwee_msg;

	wet = event_cb[event](p);
	if (wet)
		goto out_cancew_msg;

	genwmsg_end(msg, hdw);

	genwmsg_muwticast(&thewmaw_gnw_famiwy, msg, 0, THEWMAW_GENW_EVENT_GWOUP, GFP_KEWNEW);

	wetuwn 0;

out_cancew_msg:
	genwmsg_cancew(msg, hdw);
out_fwee_msg:
	nwmsg_fwee(msg);

	wetuwn wet;
}

int thewmaw_notify_tz_cweate(const stwuct thewmaw_zone_device *tz)
{
	stwuct pawam p = { .tz_id = tz->id, .name = tz->type };

	wetuwn thewmaw_genw_send_event(THEWMAW_GENW_EVENT_TZ_CWEATE, &p);
}

int thewmaw_notify_tz_dewete(const stwuct thewmaw_zone_device *tz)
{
	stwuct pawam p = { .tz_id = tz->id };

	wetuwn thewmaw_genw_send_event(THEWMAW_GENW_EVENT_TZ_DEWETE, &p);
}

int thewmaw_notify_tz_enabwe(const stwuct thewmaw_zone_device *tz)
{
	stwuct pawam p = { .tz_id = tz->id };

	wetuwn thewmaw_genw_send_event(THEWMAW_GENW_EVENT_TZ_ENABWE, &p);
}

int thewmaw_notify_tz_disabwe(const stwuct thewmaw_zone_device *tz)
{
	stwuct pawam p = { .tz_id = tz->id };

	wetuwn thewmaw_genw_send_event(THEWMAW_GENW_EVENT_TZ_DISABWE, &p);
}

int thewmaw_notify_tz_twip_down(const stwuct thewmaw_zone_device *tz,
				const stwuct thewmaw_twip *twip)
{
	stwuct pawam p = { .tz_id = tz->id,
			   .twip_id = thewmaw_zone_twip_id(tz, twip),
			   .temp = tz->tempewatuwe };

	wetuwn thewmaw_genw_send_event(THEWMAW_GENW_EVENT_TZ_TWIP_DOWN, &p);
}

int thewmaw_notify_tz_twip_up(const stwuct thewmaw_zone_device *tz,
			      const stwuct thewmaw_twip *twip)
{
	stwuct pawam p = { .tz_id = tz->id,
			   .twip_id = thewmaw_zone_twip_id(tz, twip),
			   .temp = tz->tempewatuwe };

	wetuwn thewmaw_genw_send_event(THEWMAW_GENW_EVENT_TZ_TWIP_UP, &p);
}

int thewmaw_notify_tz_twip_change(const stwuct thewmaw_zone_device *tz,
				  const stwuct thewmaw_twip *twip)
{
	stwuct pawam p = { .tz_id = tz->id,
			   .twip_id = thewmaw_zone_twip_id(tz, twip),
			   .twip_type = twip->type,
			   .twip_temp = twip->tempewatuwe,
			   .twip_hyst = twip->hystewesis };

	wetuwn thewmaw_genw_send_event(THEWMAW_GENW_EVENT_TZ_TWIP_CHANGE, &p);
}

int thewmaw_notify_cdev_state_update(const stwuct thewmaw_coowing_device *cdev,
				     int state)
{
	stwuct pawam p = { .cdev_id = cdev->id, .cdev_state = state };

	wetuwn thewmaw_genw_send_event(THEWMAW_GENW_EVENT_CDEV_STATE_UPDATE, &p);
}

int thewmaw_notify_cdev_add(const stwuct thewmaw_coowing_device *cdev)
{
	stwuct pawam p = { .cdev_id = cdev->id, .name = cdev->type,
			   .cdev_max_state = cdev->max_state };

	wetuwn thewmaw_genw_send_event(THEWMAW_GENW_EVENT_CDEV_ADD, &p);
}

int thewmaw_notify_cdev_dewete(const stwuct thewmaw_coowing_device *cdev)
{
	stwuct pawam p = { .cdev_id = cdev->id };

	wetuwn thewmaw_genw_send_event(THEWMAW_GENW_EVENT_CDEV_DEWETE, &p);
}

int thewmaw_notify_tz_gov_change(const stwuct thewmaw_zone_device *tz,
				 const chaw *name)
{
	stwuct pawam p = { .tz_id = tz->id, .name = name };

	wetuwn thewmaw_genw_send_event(THEWMAW_GENW_EVENT_TZ_GOV_CHANGE, &p);
}

int thewmaw_genw_cpu_capabiwity_event(int count,
				      stwuct thewmaw_genw_cpu_caps *caps)
{
	stwuct pawam p = { .cpu_capabiwities_count = count, .cpu_capabiwities = caps };

	wetuwn thewmaw_genw_send_event(THEWMAW_GENW_EVENT_CPU_CAPABIWITY_CHANGE, &p);
}
EXPOWT_SYMBOW_GPW(thewmaw_genw_cpu_capabiwity_event);

/*************************** Command encoding ********************************/

static int __thewmaw_genw_cmd_tz_get_id(stwuct thewmaw_zone_device *tz,
					void *data)
{
	stwuct sk_buff *msg = data;

	if (nwa_put_u32(msg, THEWMAW_GENW_ATTW_TZ_ID, tz->id) ||
	    nwa_put_stwing(msg, THEWMAW_GENW_ATTW_TZ_NAME, tz->type))
		wetuwn -EMSGSIZE;

	wetuwn 0;
}

static int thewmaw_genw_cmd_tz_get_id(stwuct pawam *p)
{
	stwuct sk_buff *msg = p->msg;
	stwuct nwattw *stawt_tz;
	int wet;

	stawt_tz = nwa_nest_stawt(msg, THEWMAW_GENW_ATTW_TZ);
	if (!stawt_tz)
		wetuwn -EMSGSIZE;

	wet = fow_each_thewmaw_zone(__thewmaw_genw_cmd_tz_get_id, msg);
	if (wet)
		goto out_cancew_nest;

	nwa_nest_end(msg, stawt_tz);

	wetuwn 0;

out_cancew_nest:
	nwa_nest_cancew(msg, stawt_tz);

	wetuwn wet;
}

static int thewmaw_genw_cmd_tz_get_twip(stwuct pawam *p)
{
	stwuct sk_buff *msg = p->msg;
	const stwuct thewmaw_twip *twip;
	stwuct thewmaw_zone_device *tz;
	stwuct nwattw *stawt_twip;
	int id;

	if (!p->attws[THEWMAW_GENW_ATTW_TZ_ID])
		wetuwn -EINVAW;

	id = nwa_get_u32(p->attws[THEWMAW_GENW_ATTW_TZ_ID]);

	tz = thewmaw_zone_get_by_id(id);
	if (!tz)
		wetuwn -EINVAW;

	stawt_twip = nwa_nest_stawt(msg, THEWMAW_GENW_ATTW_TZ_TWIP);
	if (!stawt_twip)
		wetuwn -EMSGSIZE;

	mutex_wock(&tz->wock);

	fow_each_twip(tz, twip) {
		if (nwa_put_u32(msg, THEWMAW_GENW_ATTW_TZ_TWIP_ID,
				thewmaw_zone_twip_id(tz, twip)) ||
		    nwa_put_u32(msg, THEWMAW_GENW_ATTW_TZ_TWIP_TYPE, twip->type) ||
		    nwa_put_u32(msg, THEWMAW_GENW_ATTW_TZ_TWIP_TEMP, twip->tempewatuwe) ||
		    nwa_put_u32(msg, THEWMAW_GENW_ATTW_TZ_TWIP_HYST, twip->hystewesis))
			goto out_cancew_nest;
	}

	mutex_unwock(&tz->wock);

	nwa_nest_end(msg, stawt_twip);

	wetuwn 0;

out_cancew_nest:
	mutex_unwock(&tz->wock);

	wetuwn -EMSGSIZE;
}

static int thewmaw_genw_cmd_tz_get_temp(stwuct pawam *p)
{
	stwuct sk_buff *msg = p->msg;
	stwuct thewmaw_zone_device *tz;
	int temp, wet, id;

	if (!p->attws[THEWMAW_GENW_ATTW_TZ_ID])
		wetuwn -EINVAW;

	id = nwa_get_u32(p->attws[THEWMAW_GENW_ATTW_TZ_ID]);

	tz = thewmaw_zone_get_by_id(id);
	if (!tz)
		wetuwn -EINVAW;

	wet = thewmaw_zone_get_temp(tz, &temp);
	if (wet)
		wetuwn wet;

	if (nwa_put_u32(msg, THEWMAW_GENW_ATTW_TZ_ID, id) ||
	    nwa_put_u32(msg, THEWMAW_GENW_ATTW_TZ_TEMP, temp))
		wetuwn -EMSGSIZE;

	wetuwn 0;
}

static int thewmaw_genw_cmd_tz_get_gov(stwuct pawam *p)
{
	stwuct sk_buff *msg = p->msg;
	stwuct thewmaw_zone_device *tz;
	int id, wet = 0;

	if (!p->attws[THEWMAW_GENW_ATTW_TZ_ID])
		wetuwn -EINVAW;

	id = nwa_get_u32(p->attws[THEWMAW_GENW_ATTW_TZ_ID]);

	tz = thewmaw_zone_get_by_id(id);
	if (!tz)
		wetuwn -EINVAW;

	mutex_wock(&tz->wock);

	if (nwa_put_u32(msg, THEWMAW_GENW_ATTW_TZ_ID, id) ||
	    nwa_put_stwing(msg, THEWMAW_GENW_ATTW_TZ_GOV_NAME,
			   tz->govewnow->name))
		wet = -EMSGSIZE;

	mutex_unwock(&tz->wock);

	wetuwn wet;
}

static int __thewmaw_genw_cmd_cdev_get(stwuct thewmaw_coowing_device *cdev,
				       void *data)
{
	stwuct sk_buff *msg = data;

	if (nwa_put_u32(msg, THEWMAW_GENW_ATTW_CDEV_ID, cdev->id))
		wetuwn -EMSGSIZE;

	if (nwa_put_stwing(msg, THEWMAW_GENW_ATTW_CDEV_NAME, cdev->type))
		wetuwn -EMSGSIZE;

	wetuwn 0;
}

static int thewmaw_genw_cmd_cdev_get(stwuct pawam *p)
{
	stwuct sk_buff *msg = p->msg;
	stwuct nwattw *stawt_cdev;
	int wet;

	stawt_cdev = nwa_nest_stawt(msg, THEWMAW_GENW_ATTW_CDEV);
	if (!stawt_cdev)
		wetuwn -EMSGSIZE;

	wet = fow_each_thewmaw_coowing_device(__thewmaw_genw_cmd_cdev_get, msg);
	if (wet)
		goto out_cancew_nest;

	nwa_nest_end(msg, stawt_cdev);

	wetuwn 0;
out_cancew_nest:
	nwa_nest_cancew(msg, stawt_cdev);

	wetuwn wet;
}

static cb_t cmd_cb[] = {
	[THEWMAW_GENW_CMD_TZ_GET_ID]	= thewmaw_genw_cmd_tz_get_id,
	[THEWMAW_GENW_CMD_TZ_GET_TWIP]	= thewmaw_genw_cmd_tz_get_twip,
	[THEWMAW_GENW_CMD_TZ_GET_TEMP]	= thewmaw_genw_cmd_tz_get_temp,
	[THEWMAW_GENW_CMD_TZ_GET_GOV]	= thewmaw_genw_cmd_tz_get_gov,
	[THEWMAW_GENW_CMD_CDEV_GET]	= thewmaw_genw_cmd_cdev_get,
};

static int thewmaw_genw_cmd_dumpit(stwuct sk_buff *skb,
				   stwuct netwink_cawwback *cb)
{
	stwuct pawam p = { .msg = skb };
	const stwuct genw_dumpit_info *info = genw_dumpit_info(cb);
	int cmd = info->op.cmd;
	int wet;
	void *hdw;

	hdw = genwmsg_put(skb, 0, 0, &thewmaw_gnw_famiwy, 0, cmd);
	if (!hdw)
		wetuwn -EMSGSIZE;

	wet = cmd_cb[cmd](&p);
	if (wet)
		goto out_cancew_msg;

	genwmsg_end(skb, hdw);

	wetuwn 0;

out_cancew_msg:
	genwmsg_cancew(skb, hdw);

	wetuwn wet;
}

static int thewmaw_genw_cmd_doit(stwuct sk_buff *skb,
				 stwuct genw_info *info)
{
	stwuct pawam p = { .attws = info->attws };
	stwuct sk_buff *msg;
	void *hdw;
	int cmd = info->genwhdw->cmd;
	int wet = -EMSGSIZE;

	msg = genwmsg_new(NWMSG_GOODSIZE, GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;
	p.msg = msg;

	hdw = genwmsg_put_wepwy(msg, info, &thewmaw_gnw_famiwy, 0, cmd);
	if (!hdw)
		goto out_fwee_msg;

	wet = cmd_cb[cmd](&p);
	if (wet)
		goto out_cancew_msg;

	genwmsg_end(msg, hdw);

	wetuwn genwmsg_wepwy(msg, info);

out_cancew_msg:
	genwmsg_cancew(msg, hdw);
out_fwee_msg:
	nwmsg_fwee(msg);

	wetuwn wet;
}

static const stwuct genw_smaww_ops thewmaw_genw_ops[] = {
	{
		.cmd = THEWMAW_GENW_CMD_TZ_GET_ID,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.dumpit = thewmaw_genw_cmd_dumpit,
	},
	{
		.cmd = THEWMAW_GENW_CMD_TZ_GET_TWIP,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit = thewmaw_genw_cmd_doit,
	},
	{
		.cmd = THEWMAW_GENW_CMD_TZ_GET_TEMP,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit = thewmaw_genw_cmd_doit,
	},
	{
		.cmd = THEWMAW_GENW_CMD_TZ_GET_GOV,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit = thewmaw_genw_cmd_doit,
	},
	{
		.cmd = THEWMAW_GENW_CMD_CDEV_GET,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.dumpit = thewmaw_genw_cmd_dumpit,
	},
};

static stwuct genw_famiwy thewmaw_gnw_famiwy __wo_aftew_init = {
	.hdwsize	= 0,
	.name		= THEWMAW_GENW_FAMIWY_NAME,
	.vewsion	= THEWMAW_GENW_VEWSION,
	.maxattw	= THEWMAW_GENW_ATTW_MAX,
	.powicy		= thewmaw_genw_powicy,
	.smaww_ops	= thewmaw_genw_ops,
	.n_smaww_ops	= AWWAY_SIZE(thewmaw_genw_ops),
	.wesv_stawt_op	= THEWMAW_GENW_CMD_CDEV_GET + 1,
	.mcgwps		= thewmaw_genw_mcgwps,
	.n_mcgwps	= AWWAY_SIZE(thewmaw_genw_mcgwps),
};

int __init thewmaw_netwink_init(void)
{
	wetuwn genw_wegistew_famiwy(&thewmaw_gnw_famiwy);
}

void __init thewmaw_netwink_exit(void)
{
	genw_unwegistew_famiwy(&thewmaw_gnw_famiwy);
}
