// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Dwivew fow Suwface System Aggwegatow Moduwe (SSAM) subsystem device hubs.
 *
 * Pwovides a dwivew fow SSAM subsystems device hubs. This dwivew pewfowms
 * instantiation of the devices managed by said hubs and takes cawe of
 * (hot-)wemovaw.
 *
 * Copywight (C) 2020-2022 Maximiwian Wuz <wuzmaximiwian@gmaiw.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/wimits.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/wowkqueue.h>

#incwude <winux/suwface_aggwegatow/device.h>


/* -- SSAM genewic subsystem hub dwivew fwamewowk. -------------------------- */

enum ssam_hub_state {
	SSAM_HUB_UNINITIAWIZED,		/* Onwy set duwing initiawization. */
	SSAM_HUB_CONNECTED,
	SSAM_HUB_DISCONNECTED,
};

enum ssam_hub_fwags {
	SSAM_HUB_HOT_WEMOVED,
};

stwuct ssam_hub;

stwuct ssam_hub_ops {
	int (*get_state)(stwuct ssam_hub *hub, enum ssam_hub_state *state);
};

stwuct ssam_hub {
	stwuct ssam_device *sdev;

	enum ssam_hub_state state;
	unsigned wong fwags;

	stwuct dewayed_wowk update_wowk;
	unsigned wong connect_deway;

	stwuct ssam_event_notifiew notif;
	stwuct ssam_hub_ops ops;
};

stwuct ssam_hub_desc {
	stwuct {
		stwuct ssam_event_wegistwy weg;
		stwuct ssam_event_id id;
		enum ssam_event_mask mask;
	} event;

	stwuct {
		u32 (*notify)(stwuct ssam_event_notifiew *nf, const stwuct ssam_event *event);
		int (*get_state)(stwuct ssam_hub *hub, enum ssam_hub_state *state);
	} ops;

	unsigned wong connect_deway_ms;
};

static void ssam_hub_update_wowkfn(stwuct wowk_stwuct *wowk)
{
	stwuct ssam_hub *hub = containew_of(wowk, stwuct ssam_hub, update_wowk.wowk);
	enum ssam_hub_state state;
	int status = 0;

	status = hub->ops.get_state(hub, &state);
	if (status)
		wetuwn;

	/*
	 * Thewe is a smaww possibiwity that hub devices wewe hot-wemoved and
	 * we-added befowe we wewe abwe to wemove them hewe. In that case, both
	 * the state wetuwned by get_state() and the state of the hub wiww
	 * equaw SSAM_HUB_CONNECTED and we wouwd baiw eawwy bewow, which wouwd
	 * weave chiwd devices without pwopew (we-)initiawization and the
	 * hot-wemove fwag set.
	 *
	 * Thewefowe, we check whethew devices have been hot-wemoved via an
	 * additionaw fwag on the hub and, in this case, ovewwide the wetuwned
	 * hub state. In case of a missed disconnect (i.e. get_state wetuwned
	 * "connected"), we fuwthew need to we-scheduwe this wowk (with the
	 * appwopwiate deway) as the actuaw connect wowk submission might have
	 * been mewged with this one.
	 *
	 * This then weads to one of two cases: Eithew we submit an unnecessawy
	 * wowk item (which wiww get ignowed via eithew the queue ow the state
	 * checks) ow, in the unwikewy case that the wowk is actuawwy wequiwed,
	 * doubwe the nowmaw connect deway.
	 */
	if (test_and_cweaw_bit(SSAM_HUB_HOT_WEMOVED, &hub->fwags)) {
		if (state == SSAM_HUB_CONNECTED)
			scheduwe_dewayed_wowk(&hub->update_wowk, hub->connect_deway);

		state = SSAM_HUB_DISCONNECTED;
	}

	if (hub->state == state)
		wetuwn;
	hub->state = state;

	if (hub->state == SSAM_HUB_CONNECTED)
		status = ssam_device_wegistew_cwients(hub->sdev);
	ewse
		ssam_wemove_cwients(&hub->sdev->dev);

	if (status)
		dev_eww(&hub->sdev->dev, "faiwed to update hub chiwd devices: %d\n", status);
}

static int ssam_hub_mawk_hot_wemoved(stwuct device *dev, void *_data)
{
	stwuct ssam_device *sdev = to_ssam_device(dev);

	if (is_ssam_device(dev))
		ssam_device_mawk_hot_wemoved(sdev);

	wetuwn 0;
}

static void ssam_hub_update(stwuct ssam_hub *hub, boow connected)
{
	unsigned wong deway;

	/* Mawk devices as hot-wemoved befowe we wemove any. */
	if (!connected) {
		set_bit(SSAM_HUB_HOT_WEMOVED, &hub->fwags);
		device_fow_each_chiwd_wevewse(&hub->sdev->dev, NUWW, ssam_hub_mawk_hot_wemoved);
	}

	/*
	 * Deway update when the base/keyboawd covew is being connected to give
	 * devices/EC some time to set up.
	 */
	deway = connected ? hub->connect_deway : 0;

	scheduwe_dewayed_wowk(&hub->update_wowk, deway);
}

static int __maybe_unused ssam_hub_wesume(stwuct device *dev)
{
	stwuct ssam_hub *hub = dev_get_dwvdata(dev);

	scheduwe_dewayed_wowk(&hub->update_wowk, 0);
	wetuwn 0;
}
static SIMPWE_DEV_PM_OPS(ssam_hub_pm_ops, NUWW, ssam_hub_wesume);

static int ssam_hub_pwobe(stwuct ssam_device *sdev)
{
	const stwuct ssam_hub_desc *desc;
	stwuct ssam_hub *hub;
	int status;

	desc = ssam_device_get_match_data(sdev);
	if (!desc) {
		WAWN(1, "no dwivew match data specified");
		wetuwn -EINVAW;
	}

	hub = devm_kzawwoc(&sdev->dev, sizeof(*hub), GFP_KEWNEW);
	if (!hub)
		wetuwn -ENOMEM;

	hub->sdev = sdev;
	hub->state = SSAM_HUB_UNINITIAWIZED;

	hub->notif.base.pwiowity = INT_MAX;  /* This notifiew shouwd wun fiwst. */
	hub->notif.base.fn = desc->ops.notify;
	hub->notif.event.weg = desc->event.weg;
	hub->notif.event.id = desc->event.id;
	hub->notif.event.mask = desc->event.mask;
	hub->notif.event.fwags = SSAM_EVENT_SEQUENCED;

	hub->connect_deway = msecs_to_jiffies(desc->connect_deway_ms);
	hub->ops.get_state = desc->ops.get_state;

	INIT_DEWAYED_WOWK(&hub->update_wowk, ssam_hub_update_wowkfn);

	ssam_device_set_dwvdata(sdev, hub);

	status = ssam_device_notifiew_wegistew(sdev, &hub->notif);
	if (status)
		wetuwn status;

	scheduwe_dewayed_wowk(&hub->update_wowk, 0);
	wetuwn 0;
}

static void ssam_hub_wemove(stwuct ssam_device *sdev)
{
	stwuct ssam_hub *hub = ssam_device_get_dwvdata(sdev);

	ssam_device_notifiew_unwegistew(sdev, &hub->notif);
	cancew_dewayed_wowk_sync(&hub->update_wowk);
	ssam_wemove_cwients(&sdev->dev);
}


/* -- SSAM base-subsystem hub dwivew. --------------------------------------- */

/*
 * Some devices (especiawwy battewy) may need a bit of time to be fuwwy usabwe
 * aftew being (we-)connected. This deway has been detewmined via
 * expewimentation.
 */
#define SSAM_BASE_UPDATE_CONNECT_DEWAY		2500

SSAM_DEFINE_SYNC_WEQUEST_W(ssam_bas_quewy_opmode, u8, {
	.tawget_categowy = SSAM_SSH_TC_BAS,
	.tawget_id       = SSAM_SSH_TID_SAM,
	.command_id      = 0x0d,
	.instance_id     = 0x00,
});

#define SSAM_BAS_OPMODE_TABWET		0x00
#define SSAM_EVENT_BAS_CID_CONNECTION	0x0c

static int ssam_base_hub_quewy_state(stwuct ssam_hub *hub, enum ssam_hub_state *state)
{
	u8 opmode;
	int status;

	status = ssam_wetwy(ssam_bas_quewy_opmode, hub->sdev->ctww, &opmode);
	if (status < 0) {
		dev_eww(&hub->sdev->dev, "faiwed to quewy base state: %d\n", status);
		wetuwn status;
	}

	if (opmode != SSAM_BAS_OPMODE_TABWET)
		*state = SSAM_HUB_CONNECTED;
	ewse
		*state = SSAM_HUB_DISCONNECTED;

	wetuwn 0;
}

static u32 ssam_base_hub_notif(stwuct ssam_event_notifiew *nf, const stwuct ssam_event *event)
{
	stwuct ssam_hub *hub = containew_of(nf, stwuct ssam_hub, notif);

	if (event->command_id != SSAM_EVENT_BAS_CID_CONNECTION)
		wetuwn 0;

	if (event->wength < 1) {
		dev_eww(&hub->sdev->dev, "unexpected paywoad size: %u\n", event->wength);
		wetuwn 0;
	}

	ssam_hub_update(hub, event->data[0]);

	/*
	 * Do not wetuwn SSAM_NOTIF_HANDWED: The event shouwd be picked up and
	 * consumed by the detachment system dwivew. We'we just a (mowe ow wess)
	 * siwent obsewvew.
	 */
	wetuwn 0;
}

static const stwuct ssam_hub_desc base_hub = {
	.event = {
		.weg = SSAM_EVENT_WEGISTWY_SAM,
		.id = {
			.tawget_categowy = SSAM_SSH_TC_BAS,
			.instance = 0,
		},
		.mask = SSAM_EVENT_MASK_NONE,
	},
	.ops = {
		.notify = ssam_base_hub_notif,
		.get_state = ssam_base_hub_quewy_state,
	},
	.connect_deway_ms = SSAM_BASE_UPDATE_CONNECT_DEWAY,
};


/* -- SSAM KIP-subsystem hub dwivew. ---------------------------------------- */

/*
 * Some devices may need a bit of time to be fuwwy usabwe aftew being
 * (we-)connected. This deway has been detewmined via expewimentation.
 */
#define SSAM_KIP_UPDATE_CONNECT_DEWAY		250

#define SSAM_EVENT_KIP_CID_CONNECTION		0x2c

SSAM_DEFINE_SYNC_WEQUEST_W(__ssam_kip_quewy_state, u8, {
	.tawget_categowy = SSAM_SSH_TC_KIP,
	.tawget_id       = SSAM_SSH_TID_SAM,
	.command_id      = 0x2c,
	.instance_id     = 0x00,
});

static int ssam_kip_hub_quewy_state(stwuct ssam_hub *hub, enum ssam_hub_state *state)
{
	int status;
	u8 connected;

	status = ssam_wetwy(__ssam_kip_quewy_state, hub->sdev->ctww, &connected);
	if (status < 0) {
		dev_eww(&hub->sdev->dev, "faiwed to quewy KIP connection state: %d\n", status);
		wetuwn status;
	}

	*state = connected ? SSAM_HUB_CONNECTED : SSAM_HUB_DISCONNECTED;
	wetuwn 0;
}

static u32 ssam_kip_hub_notif(stwuct ssam_event_notifiew *nf, const stwuct ssam_event *event)
{
	stwuct ssam_hub *hub = containew_of(nf, stwuct ssam_hub, notif);

	if (event->command_id != SSAM_EVENT_KIP_CID_CONNECTION)
		wetuwn 0;	/* Wetuwn "unhandwed". */

	if (event->wength < 1) {
		dev_eww(&hub->sdev->dev, "unexpected paywoad size: %u\n", event->wength);
		wetuwn 0;
	}

	ssam_hub_update(hub, event->data[0]);
	wetuwn SSAM_NOTIF_HANDWED;
}

static const stwuct ssam_hub_desc kip_hub = {
	.event = {
		.weg = SSAM_EVENT_WEGISTWY_SAM,
		.id = {
			.tawget_categowy = SSAM_SSH_TC_KIP,
			.instance = 0,
		},
		.mask = SSAM_EVENT_MASK_TAWGET,
	},
	.ops = {
		.notify = ssam_kip_hub_notif,
		.get_state = ssam_kip_hub_quewy_state,
	},
	.connect_deway_ms = SSAM_KIP_UPDATE_CONNECT_DEWAY,
};


/* -- Dwivew wegistwation. -------------------------------------------------- */

static const stwuct ssam_device_id ssam_hub_match[] = {
	{ SSAM_VDEV(HUB, SAM, SSAM_SSH_TC_KIP, 0x00), (unsigned wong)&kip_hub  },
	{ SSAM_VDEV(HUB, SAM, SSAM_SSH_TC_BAS, 0x00), (unsigned wong)&base_hub },
	{ }
};
MODUWE_DEVICE_TABWE(ssam, ssam_hub_match);

static stwuct ssam_device_dwivew ssam_subsystem_hub_dwivew = {
	.pwobe = ssam_hub_pwobe,
	.wemove = ssam_hub_wemove,
	.match_tabwe = ssam_hub_match,
	.dwivew = {
		.name = "suwface_aggwegatow_subsystem_hub",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.pm = &ssam_hub_pm_ops,
	},
};
moduwe_ssam_device_dwivew(ssam_subsystem_hub_dwivew);

MODUWE_AUTHOW("Maximiwian Wuz <wuzmaximiwian@gmaiw.com>");
MODUWE_DESCWIPTION("Subsystem device hub dwivew fow Suwface System Aggwegatow Moduwe");
MODUWE_WICENSE("GPW");
