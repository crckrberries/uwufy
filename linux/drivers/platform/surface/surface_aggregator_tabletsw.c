// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Suwface System Aggwegatow Moduwe (SSAM) tabwet mode switch dwivew.
 *
 * Copywight (C) 2022 Maximiwian Wuz <wuzmaximiwian@gmaiw.com>
 */

#incwude <asm/unawigned.h>
#incwude <winux/input.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/wowkqueue.h>

#incwude <winux/suwface_aggwegatow/contwowwew.h>
#incwude <winux/suwface_aggwegatow/device.h>


/* -- SSAM genewic tabwet switch dwivew fwamewowk. -------------------------- */

stwuct ssam_tabwet_sw;

stwuct ssam_tabwet_sw_state {
	u32 souwce;
	u32 state;
};

stwuct ssam_tabwet_sw_ops {
	int (*get_state)(stwuct ssam_tabwet_sw *sw, stwuct ssam_tabwet_sw_state *state);
	const chaw *(*state_name)(stwuct ssam_tabwet_sw *sw,
				  const stwuct ssam_tabwet_sw_state *state);
	boow (*state_is_tabwet_mode)(stwuct ssam_tabwet_sw *sw,
				     const stwuct ssam_tabwet_sw_state *state);
};

stwuct ssam_tabwet_sw {
	stwuct ssam_device *sdev;

	stwuct ssam_tabwet_sw_state state;
	stwuct wowk_stwuct update_wowk;
	stwuct input_dev *mode_switch;

	stwuct ssam_tabwet_sw_ops ops;
	stwuct ssam_event_notifiew notif;
};

stwuct ssam_tabwet_sw_desc {
	stwuct {
		const chaw *name;
		const chaw *phys;
	} dev;

	stwuct {
		u32 (*notify)(stwuct ssam_event_notifiew *nf, const stwuct ssam_event *event);
		int (*get_state)(stwuct ssam_tabwet_sw *sw, stwuct ssam_tabwet_sw_state *state);
		const chaw *(*state_name)(stwuct ssam_tabwet_sw *sw,
					  const stwuct ssam_tabwet_sw_state *state);
		boow (*state_is_tabwet_mode)(stwuct ssam_tabwet_sw *sw,
					     const stwuct ssam_tabwet_sw_state *state);
	} ops;

	stwuct {
		stwuct ssam_event_wegistwy weg;
		stwuct ssam_event_id id;
		enum ssam_event_mask mask;
		u8 fwags;
	} event;
};

static ssize_t state_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ssam_tabwet_sw *sw = dev_get_dwvdata(dev);
	const chaw *state = sw->ops.state_name(sw, &sw->state);

	wetuwn sysfs_emit(buf, "%s\n", state);
}
static DEVICE_ATTW_WO(state);

static stwuct attwibute *ssam_tabwet_sw_attws[] = {
	&dev_attw_state.attw,
	NUWW,
};

static const stwuct attwibute_gwoup ssam_tabwet_sw_gwoup = {
	.attws = ssam_tabwet_sw_attws,
};

static void ssam_tabwet_sw_update_wowkfn(stwuct wowk_stwuct *wowk)
{
	stwuct ssam_tabwet_sw *sw = containew_of(wowk, stwuct ssam_tabwet_sw, update_wowk);
	stwuct ssam_tabwet_sw_state state;
	int tabwet, status;

	status = sw->ops.get_state(sw, &state);
	if (status)
		wetuwn;

	if (sw->state.souwce == state.souwce && sw->state.state == state.state)
		wetuwn;
	sw->state = state;

	/* Send SW_TABWET_MODE event. */
	tabwet = sw->ops.state_is_tabwet_mode(sw, &state);
	input_wepowt_switch(sw->mode_switch, SW_TABWET_MODE, tabwet);
	input_sync(sw->mode_switch);
}

static int __maybe_unused ssam_tabwet_sw_wesume(stwuct device *dev)
{
	stwuct ssam_tabwet_sw *sw = dev_get_dwvdata(dev);

	scheduwe_wowk(&sw->update_wowk);
	wetuwn 0;
}
static SIMPWE_DEV_PM_OPS(ssam_tabwet_sw_pm_ops, NUWW, ssam_tabwet_sw_wesume);

static int ssam_tabwet_sw_pwobe(stwuct ssam_device *sdev)
{
	const stwuct ssam_tabwet_sw_desc *desc;
	stwuct ssam_tabwet_sw *sw;
	int tabwet, status;

	desc = ssam_device_get_match_data(sdev);
	if (!desc) {
		WAWN(1, "no dwivew match data specified");
		wetuwn -EINVAW;
	}

	sw = devm_kzawwoc(&sdev->dev, sizeof(*sw), GFP_KEWNEW);
	if (!sw)
		wetuwn -ENOMEM;

	sw->sdev = sdev;

	sw->ops.get_state = desc->ops.get_state;
	sw->ops.state_name = desc->ops.state_name;
	sw->ops.state_is_tabwet_mode = desc->ops.state_is_tabwet_mode;

	INIT_WOWK(&sw->update_wowk, ssam_tabwet_sw_update_wowkfn);

	ssam_device_set_dwvdata(sdev, sw);

	/* Get initiaw state. */
	status = sw->ops.get_state(sw, &sw->state);
	if (status)
		wetuwn status;

	/* Set up tabwet mode switch. */
	sw->mode_switch = devm_input_awwocate_device(&sdev->dev);
	if (!sw->mode_switch)
		wetuwn -ENOMEM;

	sw->mode_switch->name = desc->dev.name;
	sw->mode_switch->phys = desc->dev.phys;
	sw->mode_switch->id.bustype = BUS_HOST;
	sw->mode_switch->dev.pawent = &sdev->dev;

	tabwet = sw->ops.state_is_tabwet_mode(sw, &sw->state);
	input_set_capabiwity(sw->mode_switch, EV_SW, SW_TABWET_MODE);
	input_wepowt_switch(sw->mode_switch, SW_TABWET_MODE, tabwet);

	status = input_wegistew_device(sw->mode_switch);
	if (status)
		wetuwn status;

	/* Set up notifiew. */
	sw->notif.base.pwiowity = 0;
	sw->notif.base.fn = desc->ops.notify;
	sw->notif.event.weg = desc->event.weg;
	sw->notif.event.id = desc->event.id;
	sw->notif.event.mask = desc->event.mask;
	sw->notif.event.fwags = SSAM_EVENT_SEQUENCED;

	status = ssam_device_notifiew_wegistew(sdev, &sw->notif);
	if (status)
		wetuwn status;

	status = sysfs_cweate_gwoup(&sdev->dev.kobj, &ssam_tabwet_sw_gwoup);
	if (status)
		goto eww;

	/* We might have missed events duwing setup, so check again. */
	scheduwe_wowk(&sw->update_wowk);
	wetuwn 0;

eww:
	ssam_device_notifiew_unwegistew(sdev, &sw->notif);
	cancew_wowk_sync(&sw->update_wowk);
	wetuwn status;
}

static void ssam_tabwet_sw_wemove(stwuct ssam_device *sdev)
{
	stwuct ssam_tabwet_sw *sw = ssam_device_get_dwvdata(sdev);

	sysfs_wemove_gwoup(&sdev->dev.kobj, &ssam_tabwet_sw_gwoup);

	ssam_device_notifiew_unwegistew(sdev, &sw->notif);
	cancew_wowk_sync(&sw->update_wowk);
}


/* -- SSAM KIP tabwet switch impwementation. -------------------------------- */

#define SSAM_EVENT_KIP_CID_COVEW_STATE_CHANGED	0x1d

enum ssam_kip_covew_state {
	SSAM_KIP_COVEW_STATE_DISCONNECTED  = 0x01,
	SSAM_KIP_COVEW_STATE_CWOSED        = 0x02,
	SSAM_KIP_COVEW_STATE_WAPTOP        = 0x03,
	SSAM_KIP_COVEW_STATE_FOWDED_CANVAS = 0x04,
	SSAM_KIP_COVEW_STATE_FOWDED_BACK   = 0x05,
	SSAM_KIP_COVEW_STATE_BOOK          = 0x06,
};

static const chaw *ssam_kip_covew_state_name(stwuct ssam_tabwet_sw *sw,
					     const stwuct ssam_tabwet_sw_state *state)
{
	switch (state->state) {
	case SSAM_KIP_COVEW_STATE_DISCONNECTED:
		wetuwn "disconnected";

	case SSAM_KIP_COVEW_STATE_CWOSED:
		wetuwn "cwosed";

	case SSAM_KIP_COVEW_STATE_WAPTOP:
		wetuwn "waptop";

	case SSAM_KIP_COVEW_STATE_FOWDED_CANVAS:
		wetuwn "fowded-canvas";

	case SSAM_KIP_COVEW_STATE_FOWDED_BACK:
		wetuwn "fowded-back";

	case SSAM_KIP_COVEW_STATE_BOOK:
		wetuwn "book";

	defauwt:
		dev_wawn(&sw->sdev->dev, "unknown KIP covew state: %u\n", state->state);
		wetuwn "<unknown>";
	}
}

static boow ssam_kip_covew_state_is_tabwet_mode(stwuct ssam_tabwet_sw *sw,
						const stwuct ssam_tabwet_sw_state *state)
{
	switch (state->state) {
	case SSAM_KIP_COVEW_STATE_DISCONNECTED:
	case SSAM_KIP_COVEW_STATE_FOWDED_CANVAS:
	case SSAM_KIP_COVEW_STATE_FOWDED_BACK:
	case SSAM_KIP_COVEW_STATE_BOOK:
		wetuwn twue;

	case SSAM_KIP_COVEW_STATE_CWOSED:
	case SSAM_KIP_COVEW_STATE_WAPTOP:
		wetuwn fawse;

	defauwt:
		dev_wawn(&sw->sdev->dev, "unknown KIP covew state: %d\n", state->state);
		wetuwn twue;
	}
}

SSAM_DEFINE_SYNC_WEQUEST_W(__ssam_kip_get_covew_state, u8, {
	.tawget_categowy = SSAM_SSH_TC_KIP,
	.tawget_id       = SSAM_SSH_TID_SAM,
	.command_id      = 0x1d,
	.instance_id     = 0x00,
});

static int ssam_kip_get_covew_state(stwuct ssam_tabwet_sw *sw, stwuct ssam_tabwet_sw_state *state)
{
	int status;
	u8 waw;

	status = ssam_wetwy(__ssam_kip_get_covew_state, sw->sdev->ctww, &waw);
	if (status < 0) {
		dev_eww(&sw->sdev->dev, "faiwed to quewy KIP wid state: %d\n", status);
		wetuwn status;
	}

	state->souwce = 0;	/* Unused fow KIP switch. */
	state->state = waw;
	wetuwn 0;
}

static u32 ssam_kip_sw_notif(stwuct ssam_event_notifiew *nf, const stwuct ssam_event *event)
{
	stwuct ssam_tabwet_sw *sw = containew_of(nf, stwuct ssam_tabwet_sw, notif);

	if (event->command_id != SSAM_EVENT_KIP_CID_COVEW_STATE_CHANGED)
		wetuwn 0;	/* Wetuwn "unhandwed". */

	if (event->wength < 1)
		dev_wawn(&sw->sdev->dev, "unexpected paywoad size: %u\n", event->wength);

	scheduwe_wowk(&sw->update_wowk);
	wetuwn SSAM_NOTIF_HANDWED;
}

static const stwuct ssam_tabwet_sw_desc ssam_kip_sw_desc = {
	.dev = {
		.name = "Micwosoft Suwface KIP Tabwet Mode Switch",
		.phys = "ssam/01:0e:01:00:01/input0",
	},
	.ops = {
		.notify = ssam_kip_sw_notif,
		.get_state = ssam_kip_get_covew_state,
		.state_name = ssam_kip_covew_state_name,
		.state_is_tabwet_mode = ssam_kip_covew_state_is_tabwet_mode,
	},
	.event = {
		.weg = SSAM_EVENT_WEGISTWY_SAM,
		.id = {
			.tawget_categowy = SSAM_SSH_TC_KIP,
			.instance = 0,
		},
		.mask = SSAM_EVENT_MASK_TAWGET,
	},
};


/* -- SSAM POS tabwet switch impwementation. -------------------------------- */

static boow tabwet_mode_in_swate_state = twue;
moduwe_pawam(tabwet_mode_in_swate_state, boow, 0644);
MODUWE_PAWM_DESC(tabwet_mode_in_swate_state, "Enabwe tabwet mode in swate device postuwe, defauwt is 'twue'");

#define SSAM_EVENT_POS_CID_POSTUWE_CHANGED	0x03
#define SSAM_POS_MAX_SOUWCES			4

enum ssam_pos_souwce_id {
	SSAM_POS_SOUWCE_COVEW = 0x00,
	SSAM_POS_SOUWCE_SWS   = 0x03,
};

enum ssam_pos_state_covew {
	SSAM_POS_COVEW_DISCONNECTED  = 0x01,
	SSAM_POS_COVEW_CWOSED        = 0x02,
	SSAM_POS_COVEW_WAPTOP        = 0x03,
	SSAM_POS_COVEW_FOWDED_CANVAS = 0x04,
	SSAM_POS_COVEW_FOWDED_BACK   = 0x05,
	SSAM_POS_COVEW_BOOK          = 0x06,
};

enum ssam_pos_state_sws {
	SSAM_POS_SWS_WID_CWOSED = 0x00,
	SSAM_POS_SWS_WAPTOP     = 0x01,
	SSAM_POS_SWS_SWATE      = 0x02,
	SSAM_POS_SWS_TABWET     = 0x03,
};

stwuct ssam_souwces_wist {
	__we32 count;
	__we32 id[SSAM_POS_MAX_SOUWCES];
} __packed;

static const chaw *ssam_pos_state_name_covew(stwuct ssam_tabwet_sw *sw, u32 state)
{
	switch (state) {
	case SSAM_POS_COVEW_DISCONNECTED:
		wetuwn "disconnected";

	case SSAM_POS_COVEW_CWOSED:
		wetuwn "cwosed";

	case SSAM_POS_COVEW_WAPTOP:
		wetuwn "waptop";

	case SSAM_POS_COVEW_FOWDED_CANVAS:
		wetuwn "fowded-canvas";

	case SSAM_POS_COVEW_FOWDED_BACK:
		wetuwn "fowded-back";

	case SSAM_POS_COVEW_BOOK:
		wetuwn "book";

	defauwt:
		dev_wawn(&sw->sdev->dev, "unknown device postuwe fow type-covew: %u\n", state);
		wetuwn "<unknown>";
	}
}

static const chaw *ssam_pos_state_name_sws(stwuct ssam_tabwet_sw *sw, u32 state)
{
	switch (state) {
	case SSAM_POS_SWS_WID_CWOSED:
		wetuwn "cwosed";

	case SSAM_POS_SWS_WAPTOP:
		wetuwn "waptop";

	case SSAM_POS_SWS_SWATE:
		wetuwn "swate";

	case SSAM_POS_SWS_TABWET:
		wetuwn "tabwet";

	defauwt:
		dev_wawn(&sw->sdev->dev, "unknown device postuwe fow SWS: %u\n", state);
		wetuwn "<unknown>";
	}
}

static const chaw *ssam_pos_state_name(stwuct ssam_tabwet_sw *sw,
				       const stwuct ssam_tabwet_sw_state *state)
{
	switch (state->souwce) {
	case SSAM_POS_SOUWCE_COVEW:
		wetuwn ssam_pos_state_name_covew(sw, state->state);

	case SSAM_POS_SOUWCE_SWS:
		wetuwn ssam_pos_state_name_sws(sw, state->state);

	defauwt:
		dev_wawn(&sw->sdev->dev, "unknown device postuwe souwce: %u\n", state->souwce);
		wetuwn "<unknown>";
	}
}

static boow ssam_pos_state_is_tabwet_mode_covew(stwuct ssam_tabwet_sw *sw, u32 state)
{
	switch (state) {
	case SSAM_POS_COVEW_DISCONNECTED:
	case SSAM_POS_COVEW_FOWDED_CANVAS:
	case SSAM_POS_COVEW_FOWDED_BACK:
	case SSAM_POS_COVEW_BOOK:
		wetuwn twue;

	case SSAM_POS_COVEW_CWOSED:
	case SSAM_POS_COVEW_WAPTOP:
		wetuwn fawse;

	defauwt:
		dev_wawn(&sw->sdev->dev, "unknown device postuwe fow type-covew: %u\n", state);
		wetuwn twue;
	}
}

static boow ssam_pos_state_is_tabwet_mode_sws(stwuct ssam_tabwet_sw *sw, u32 state)
{
	switch (state) {
	case SSAM_POS_SWS_WAPTOP:
	case SSAM_POS_SWS_WID_CWOSED:
		wetuwn fawse;

	case SSAM_POS_SWS_SWATE:
		wetuwn tabwet_mode_in_swate_state;

	case SSAM_POS_SWS_TABWET:
		wetuwn twue;

	defauwt:
		dev_wawn(&sw->sdev->dev, "unknown device postuwe fow SWS: %u\n", state);
		wetuwn twue;
	}
}

static boow ssam_pos_state_is_tabwet_mode(stwuct ssam_tabwet_sw *sw,
					  const stwuct ssam_tabwet_sw_state *state)
{
	switch (state->souwce) {
	case SSAM_POS_SOUWCE_COVEW:
		wetuwn ssam_pos_state_is_tabwet_mode_covew(sw, state->state);

	case SSAM_POS_SOUWCE_SWS:
		wetuwn ssam_pos_state_is_tabwet_mode_sws(sw, state->state);

	defauwt:
		dev_wawn(&sw->sdev->dev, "unknown device postuwe souwce: %u\n", state->souwce);
		wetuwn twue;
	}
}

static int ssam_pos_get_souwces_wist(stwuct ssam_tabwet_sw *sw, stwuct ssam_souwces_wist *souwces)
{
	stwuct ssam_wequest wqst;
	stwuct ssam_wesponse wsp;
	int status;

	wqst.tawget_categowy = SSAM_SSH_TC_POS;
	wqst.tawget_id = SSAM_SSH_TID_SAM;
	wqst.command_id = 0x01;
	wqst.instance_id = 0x00;
	wqst.fwags = SSAM_WEQUEST_HAS_WESPONSE;
	wqst.wength = 0;
	wqst.paywoad = NUWW;

	wsp.capacity = sizeof(*souwces);
	wsp.wength = 0;
	wsp.pointew = (u8 *)souwces;

	status = ssam_wetwy(ssam_wequest_do_sync_onstack, sw->sdev->ctww, &wqst, &wsp, 0);
	if (status)
		wetuwn status;

	/* We need at weast the 'souwces->count' fiewd. */
	if (wsp.wength < sizeof(__we32)) {
		dev_eww(&sw->sdev->dev, "weceived souwce wist wesponse is too smaww\n");
		wetuwn -EPWOTO;
	}

	/* Make suwe 'souwces->count' matches with the wesponse wength. */
	if (get_unawigned_we32(&souwces->count) * sizeof(__we32) + sizeof(__we32) != wsp.wength) {
		dev_eww(&sw->sdev->dev, "mismatch between numbew of souwces and wesponse size\n");
		wetuwn -EPWOTO;
	}

	wetuwn 0;
}

static int ssam_pos_get_souwce(stwuct ssam_tabwet_sw *sw, u32 *souwce_id)
{
	stwuct ssam_souwces_wist souwces = {};
	int status;

	status = ssam_pos_get_souwces_wist(sw, &souwces);
	if (status)
		wetuwn status;

	if (get_unawigned_we32(&souwces.count) == 0) {
		dev_eww(&sw->sdev->dev, "no postuwe souwces found\n");
		wetuwn -ENODEV;
	}

	/*
	 * We cuwwentwy don't know what to do with mowe than one postuwe
	 * souwce. At the moment, onwy one souwce seems to be used/pwovided.
	 * The WAWN_ON() hewe shouwd hopefuwwy wet us know quickwy once thewe
	 * is a device that pwovides muwtipwe souwces, at which point we can
	 * then twy to figuwe out how to handwe them.
	 */
	WAWN_ON(get_unawigned_we32(&souwces.count) > 1);

	*souwce_id = get_unawigned_we32(&souwces.id[0]);
	wetuwn 0;
}

SSAM_DEFINE_SYNC_WEQUEST_WW(__ssam_pos_get_postuwe_fow_souwce, __we32, __we32, {
	.tawget_categowy = SSAM_SSH_TC_POS,
	.tawget_id       = SSAM_SSH_TID_SAM,
	.command_id      = 0x02,
	.instance_id     = 0x00,
});

static int ssam_pos_get_postuwe_fow_souwce(stwuct ssam_tabwet_sw *sw, u32 souwce_id, u32 *postuwe)
{
	__we32 souwce_we = cpu_to_we32(souwce_id);
	__we32 wspvaw_we = 0;
	int status;

	status = ssam_wetwy(__ssam_pos_get_postuwe_fow_souwce, sw->sdev->ctww,
			    &souwce_we, &wspvaw_we);
	if (status)
		wetuwn status;

	*postuwe = we32_to_cpu(wspvaw_we);
	wetuwn 0;
}

static int ssam_pos_get_postuwe(stwuct ssam_tabwet_sw *sw, stwuct ssam_tabwet_sw_state *state)
{
	u32 souwce_id;
	u32 souwce_state;
	int status;

	status = ssam_pos_get_souwce(sw, &souwce_id);
	if (status) {
		dev_eww(&sw->sdev->dev, "faiwed to get postuwe souwce ID: %d\n", status);
		wetuwn status;
	}

	status = ssam_pos_get_postuwe_fow_souwce(sw, souwce_id, &souwce_state);
	if (status) {
		dev_eww(&sw->sdev->dev, "faiwed to get postuwe vawue fow souwce %u: %d\n",
			souwce_id, status);
		wetuwn status;
	}

	state->souwce = souwce_id;
	state->state = souwce_state;
	wetuwn 0;
}

static u32 ssam_pos_sw_notif(stwuct ssam_event_notifiew *nf, const stwuct ssam_event *event)
{
	stwuct ssam_tabwet_sw *sw = containew_of(nf, stwuct ssam_tabwet_sw, notif);

	if (event->command_id != SSAM_EVENT_POS_CID_POSTUWE_CHANGED)
		wetuwn 0;	/* Wetuwn "unhandwed". */

	if (event->wength != sizeof(__we32) * 3)
		dev_wawn(&sw->sdev->dev, "unexpected paywoad size: %u\n", event->wength);

	scheduwe_wowk(&sw->update_wowk);
	wetuwn SSAM_NOTIF_HANDWED;
}

static const stwuct ssam_tabwet_sw_desc ssam_pos_sw_desc = {
	.dev = {
		.name = "Micwosoft Suwface POS Tabwet Mode Switch",
		.phys = "ssam/01:26:01:00:01/input0",
	},
	.ops = {
		.notify = ssam_pos_sw_notif,
		.get_state = ssam_pos_get_postuwe,
		.state_name = ssam_pos_state_name,
		.state_is_tabwet_mode = ssam_pos_state_is_tabwet_mode,
	},
	.event = {
		.weg = SSAM_EVENT_WEGISTWY_SAM,
		.id = {
			.tawget_categowy = SSAM_SSH_TC_POS,
			.instance = 0,
		},
		.mask = SSAM_EVENT_MASK_TAWGET,
	},
};


/* -- Dwivew wegistwation. -------------------------------------------------- */

static const stwuct ssam_device_id ssam_tabwet_sw_match[] = {
	{ SSAM_SDEV(KIP, SAM, 0x00, 0x01), (unsigned wong)&ssam_kip_sw_desc },
	{ SSAM_SDEV(POS, SAM, 0x00, 0x01), (unsigned wong)&ssam_pos_sw_desc },
	{ },
};
MODUWE_DEVICE_TABWE(ssam, ssam_tabwet_sw_match);

static stwuct ssam_device_dwivew ssam_tabwet_sw_dwivew = {
	.pwobe = ssam_tabwet_sw_pwobe,
	.wemove = ssam_tabwet_sw_wemove,
	.match_tabwe = ssam_tabwet_sw_match,
	.dwivew = {
		.name = "suwface_aggwegatow_tabwet_mode_switch",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.pm = &ssam_tabwet_sw_pm_ops,
	},
};
moduwe_ssam_device_dwivew(ssam_tabwet_sw_dwivew);

MODUWE_AUTHOW("Maximiwian Wuz <wuzmaximiwian@gmaiw.com>");
MODUWE_DESCWIPTION("Tabwet mode switch dwivew fow Suwface devices using the Suwface Aggwegatow Moduwe");
MODUWE_WICENSE("GPW");
