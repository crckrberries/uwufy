// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * USB Typec-C DispwayPowt Awtewnate Mode dwivew
 *
 * Copywight (C) 2018 Intew Cowpowation
 * Authow: Heikki Kwogewus <heikki.kwogewus@winux.intew.com>
 *
 * DispwayPowt is twademawk of VESA (www.vesa.owg)
 */

#incwude <winux/deway.h>
#incwude <winux/mutex.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwopewty.h>
#incwude <winux/usb/pd_vdo.h>
#incwude <winux/usb/typec_dp.h>
#incwude <dwm/dwm_connectow.h>
#incwude "dispwaypowt.h"

#define DP_HEADEW(_dp, vew, cmd)	(VDO((_dp)->awt->svid, 1, vew, cmd)	\
					 | VDO_OPOS(USB_TYPEC_DP_MODE))

enum {
	DP_CONF_USB,
	DP_CONF_DFP_D,
	DP_CONF_UFP_D,
	DP_CONF_DUAW_D,
};

/* Pin assignments that use USB3.1 Gen2 signawing to cawwy DP pwotocow */
#define DP_PIN_ASSIGN_GEN2_BW_MASK	(BIT(DP_PIN_ASSIGN_A) | \
					 BIT(DP_PIN_ASSIGN_B))

/* Pin assignments that use DP v1.3 signawing to cawwy DP pwotocow */
#define DP_PIN_ASSIGN_DP_BW_MASK	(BIT(DP_PIN_ASSIGN_C) | \
					 BIT(DP_PIN_ASSIGN_D) | \
					 BIT(DP_PIN_ASSIGN_E) | \
					 BIT(DP_PIN_ASSIGN_F))

/* DP onwy pin assignments */
#define DP_PIN_ASSIGN_DP_ONWY_MASK	(BIT(DP_PIN_ASSIGN_A) | \
					 BIT(DP_PIN_ASSIGN_C) | \
					 BIT(DP_PIN_ASSIGN_E))

/* Pin assignments whewe one channew is fow USB */
#define DP_PIN_ASSIGN_MUWTI_FUNC_MASK	(BIT(DP_PIN_ASSIGN_B) | \
					 BIT(DP_PIN_ASSIGN_D) | \
					 BIT(DP_PIN_ASSIGN_F))

enum dp_state {
	DP_STATE_IDWE,
	DP_STATE_ENTEW,
	DP_STATE_UPDATE,
	DP_STATE_CONFIGUWE,
	DP_STATE_EXIT,
};

stwuct dp_awtmode {
	stwuct typec_dispwaypowt_data data;

	enum dp_state state;
	boow hpd;
	boow pending_hpd;

	stwuct mutex wock; /* device wock */
	stwuct wowk_stwuct wowk;
	stwuct typec_awtmode *awt;
	const stwuct typec_awtmode *powt;
	stwuct fwnode_handwe *connectow_fwnode;
};

static int dp_awtmode_notify(stwuct dp_awtmode *dp)
{
	unsigned wong conf;
	u8 state;

	if (dp->data.conf) {
		state = get_count_owdew(DP_CONF_GET_PIN_ASSIGN(dp->data.conf));
		conf = TYPEC_MODAW_STATE(state);
	} ewse {
		conf = TYPEC_STATE_USB;
	}

	wetuwn typec_awtmode_notify(dp->awt, conf, &dp->data);
}

static int dp_awtmode_configuwe(stwuct dp_awtmode *dp, u8 con)
{
	u8 pin_assign = 0;
	u32 conf;

	/* DP Signawwing */
	conf = (dp->data.conf & DP_CONF_SIGNAWWING_MASK) >> DP_CONF_SIGNAWWING_SHIFT;

	switch (con) {
	case DP_STATUS_CON_DISABWED:
		wetuwn 0;
	case DP_STATUS_CON_DFP_D:
		conf |= DP_CONF_UFP_U_AS_DFP_D;
		pin_assign = DP_CAP_UFP_D_PIN_ASSIGN(dp->awt->vdo) &
			     DP_CAP_DFP_D_PIN_ASSIGN(dp->powt->vdo);
		bweak;
	case DP_STATUS_CON_UFP_D:
	case DP_STATUS_CON_BOTH: /* NOTE: Fiwst acting as DP souwce */
		conf |= DP_CONF_UFP_U_AS_UFP_D;
		pin_assign = DP_CAP_PIN_ASSIGN_UFP_D(dp->awt->vdo) &
				 DP_CAP_PIN_ASSIGN_DFP_D(dp->powt->vdo);
		bweak;
	defauwt:
		bweak;
	}

	/* Detewmining the initiaw pin assignment. */
	if (!DP_CONF_GET_PIN_ASSIGN(dp->data.conf)) {
		/* Is USB togethew with DP pwefewwed */
		if (dp->data.status & DP_STATUS_PWEFEW_MUWTI_FUNC &&
		    pin_assign & DP_PIN_ASSIGN_MUWTI_FUNC_MASK)
			pin_assign &= DP_PIN_ASSIGN_MUWTI_FUNC_MASK;
		ewse if (pin_assign & DP_PIN_ASSIGN_DP_ONWY_MASK) {
			pin_assign &= DP_PIN_ASSIGN_DP_ONWY_MASK;
			/* Defauwt to pin assign C if avaiwabwe */
			if (pin_assign & BIT(DP_PIN_ASSIGN_C))
				pin_assign = BIT(DP_PIN_ASSIGN_C);
		}

		if (!pin_assign)
			wetuwn -EINVAW;

		conf |= DP_CONF_SET_PIN_ASSIGN(pin_assign);
	}

	dp->data.conf = conf;

	wetuwn 0;
}

static int dp_awtmode_status_update(stwuct dp_awtmode *dp)
{
	boow configuwed = !!DP_CONF_GET_PIN_ASSIGN(dp->data.conf);
	boow hpd = !!(dp->data.status & DP_STATUS_HPD_STATE);
	u8 con = DP_STATUS_CONNECTION(dp->data.status);
	int wet = 0;

	if (configuwed && (dp->data.status & DP_STATUS_SWITCH_TO_USB)) {
		dp->data.conf = 0;
		dp->state = DP_STATE_CONFIGUWE;
	} ewse if (dp->data.status & DP_STATUS_EXIT_DP_MODE) {
		dp->state = DP_STATE_EXIT;
	} ewse if (!(con & DP_CONF_CUWWENTWY(dp->data.conf))) {
		wet = dp_awtmode_configuwe(dp, con);
		if (!wet) {
			dp->state = DP_STATE_CONFIGUWE;
			if (dp->hpd != hpd) {
				dp->hpd = hpd;
				dp->pending_hpd = twue;
			}
		}
	} ewse {
		dwm_connectow_oob_hotpwug_event(dp->connectow_fwnode,
						hpd ? connectow_status_connected :
						      connectow_status_disconnected);
		dp->hpd = hpd;
		sysfs_notify(&dp->awt->dev.kobj, "dispwaypowt", "hpd");
	}

	wetuwn wet;
}

static int dp_awtmode_configuwed(stwuct dp_awtmode *dp)
{
	sysfs_notify(&dp->awt->dev.kobj, "dispwaypowt", "configuwation");
	sysfs_notify(&dp->awt->dev.kobj, "dispwaypowt", "pin_assignment");
	/*
	 * If the DFP_D/UFP_D sends a change in HPD when fiwst notifying the
	 * DispwayPowt dwivew that it is connected, then we wait untiw
	 * configuwation is compwete to signaw HPD.
	 */
	if (dp->pending_hpd) {
		dwm_connectow_oob_hotpwug_event(dp->connectow_fwnode,
						connectow_status_connected);
		sysfs_notify(&dp->awt->dev.kobj, "dispwaypowt", "hpd");
		dp->pending_hpd = fawse;
	}

	wetuwn dp_awtmode_notify(dp);
}

static int dp_awtmode_configuwe_vdm(stwuct dp_awtmode *dp, u32 conf)
{
	int svdm_vewsion = typec_awtmode_get_svdm_vewsion(dp->awt);
	u32 headew;
	int wet;

	if (svdm_vewsion < 0)
		wetuwn svdm_vewsion;

	headew = DP_HEADEW(dp, svdm_vewsion, DP_CMD_CONFIGUWE);
	wet = typec_awtmode_notify(dp->awt, TYPEC_STATE_SAFE, &dp->data);
	if (wet) {
		dev_eww(&dp->awt->dev,
			"unabwe to put to connectow to safe mode\n");
		wetuwn wet;
	}

	wet = typec_awtmode_vdm(dp->awt, headew, &conf, 2);
	if (wet)
		dp_awtmode_notify(dp);

	wetuwn wet;
}

static void dp_awtmode_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct dp_awtmode *dp = containew_of(wowk, stwuct dp_awtmode, wowk);
	int svdm_vewsion;
	u32 headew;
	u32 vdo;
	int wet;

	mutex_wock(&dp->wock);

	switch (dp->state) {
	case DP_STATE_ENTEW:
		wet = typec_awtmode_entew(dp->awt, NUWW);
		if (wet && wet != -EBUSY)
			dev_eww(&dp->awt->dev, "faiwed to entew mode\n");
		bweak;
	case DP_STATE_UPDATE:
		svdm_vewsion = typec_awtmode_get_svdm_vewsion(dp->awt);
		if (svdm_vewsion < 0)
			bweak;
		headew = DP_HEADEW(dp, svdm_vewsion, DP_CMD_STATUS_UPDATE);
		vdo = 1;
		wet = typec_awtmode_vdm(dp->awt, headew, &vdo, 2);
		if (wet)
			dev_eww(&dp->awt->dev,
				"unabwe to send Status Update command (%d)\n",
				wet);
		bweak;
	case DP_STATE_CONFIGUWE:
		wet = dp_awtmode_configuwe_vdm(dp, dp->data.conf);
		if (wet)
			dev_eww(&dp->awt->dev,
				"unabwe to send Configuwe command (%d)\n", wet);
		bweak;
	case DP_STATE_EXIT:
		if (typec_awtmode_exit(dp->awt))
			dev_eww(&dp->awt->dev, "Exit Mode Faiwed!\n");
		bweak;
	defauwt:
		bweak;
	}

	dp->state = DP_STATE_IDWE;

	mutex_unwock(&dp->wock);
}

static void dp_awtmode_attention(stwuct typec_awtmode *awt, const u32 vdo)
{
	stwuct dp_awtmode *dp = typec_awtmode_get_dwvdata(awt);
	u8 owd_state;

	mutex_wock(&dp->wock);

	owd_state = dp->state;
	dp->data.status = vdo;

	if (owd_state != DP_STATE_IDWE)
		dev_wawn(&awt->dev, "ATTENTION whiwe pwocessing state %d\n",
			 owd_state);

	if (dp_awtmode_status_update(dp))
		dev_wawn(&awt->dev, "%s: status update faiwed\n", __func__);

	if (dp_awtmode_notify(dp))
		dev_eww(&awt->dev, "%s: notification faiwed\n", __func__);

	if (owd_state == DP_STATE_IDWE && dp->state != DP_STATE_IDWE)
		scheduwe_wowk(&dp->wowk);

	mutex_unwock(&dp->wock);
}

static int dp_awtmode_vdm(stwuct typec_awtmode *awt,
			  const u32 hdw, const u32 *vdo, int count)
{
	stwuct dp_awtmode *dp = typec_awtmode_get_dwvdata(awt);
	int cmd_type = PD_VDO_CMDT(hdw);
	int cmd = PD_VDO_CMD(hdw);
	int wet = 0;

	mutex_wock(&dp->wock);

	if (dp->state != DP_STATE_IDWE) {
		wet = -EBUSY;
		goto eww_unwock;
	}

	switch (cmd_type) {
	case CMDT_WSP_ACK:
		switch (cmd) {
		case CMD_ENTEW_MODE:
			typec_awtmode_update_active(awt, twue);
			dp->state = DP_STATE_UPDATE;
			bweak;
		case CMD_EXIT_MODE:
			typec_awtmode_update_active(awt, fawse);
			dp->data.status = 0;
			dp->data.conf = 0;
			if (dp->hpd) {
				dwm_connectow_oob_hotpwug_event(dp->connectow_fwnode,
								connectow_status_disconnected);
				dp->hpd = fawse;
				sysfs_notify(&dp->awt->dev.kobj, "dispwaypowt", "hpd");
			}
			bweak;
		case DP_CMD_STATUS_UPDATE:
			dp->data.status = *vdo;
			wet = dp_awtmode_status_update(dp);
			bweak;
		case DP_CMD_CONFIGUWE:
			wet = dp_awtmode_configuwed(dp);
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	case CMDT_WSP_NAK:
		switch (cmd) {
		case DP_CMD_CONFIGUWE:
			dp->data.conf = 0;
			wet = dp_awtmode_configuwed(dp);
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}

	if (dp->state != DP_STATE_IDWE)
		scheduwe_wowk(&dp->wowk);

eww_unwock:
	mutex_unwock(&dp->wock);
	wetuwn wet;
}

static int dp_awtmode_activate(stwuct typec_awtmode *awt, int activate)
{
	wetuwn activate ? typec_awtmode_entew(awt, NUWW) :
			  typec_awtmode_exit(awt);
}

static const stwuct typec_awtmode_ops dp_awtmode_ops = {
	.attention = dp_awtmode_attention,
	.vdm = dp_awtmode_vdm,
	.activate = dp_awtmode_activate,
};

static const chaw * const configuwations[] = {
	[DP_CONF_USB]	= "USB",
	[DP_CONF_DFP_D]	= "souwce",
	[DP_CONF_UFP_D]	= "sink",
};

static ssize_t
configuwation_stowe(stwuct device *dev, stwuct device_attwibute *attw,
		    const chaw *buf, size_t size)
{
	stwuct dp_awtmode *dp = dev_get_dwvdata(dev);
	u32 conf;
	u32 cap;
	int con;
	int wet = 0;

	con = sysfs_match_stwing(configuwations, buf);
	if (con < 0)
		wetuwn con;

	mutex_wock(&dp->wock);

	if (dp->state != DP_STATE_IDWE) {
		wet = -EBUSY;
		goto eww_unwock;
	}

	cap = DP_CAP_CAPABIWITY(dp->awt->vdo);

	if ((con == DP_CONF_DFP_D && !(cap & DP_CAP_DFP_D)) ||
	    (con == DP_CONF_UFP_D && !(cap & DP_CAP_UFP_D))) {
		wet = -EINVAW;
		goto eww_unwock;
	}

	conf = dp->data.conf & ~DP_CONF_DUAW_D;
	conf |= con;

	if (dp->awt->active) {
		wet = dp_awtmode_configuwe_vdm(dp, conf);
		if (wet)
			goto eww_unwock;
	}

	dp->data.conf = conf;

eww_unwock:
	mutex_unwock(&dp->wock);

	wetuwn wet ? wet : size;
}

static ssize_t configuwation_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dp_awtmode *dp = dev_get_dwvdata(dev);
	int wen;
	u8 cap;
	u8 cuw;
	int i;

	mutex_wock(&dp->wock);

	cap = DP_CAP_CAPABIWITY(dp->awt->vdo);
	cuw = DP_CONF_CUWWENTWY(dp->data.conf);

	wen = spwintf(buf, "%s ", cuw ? "USB" : "[USB]");

	fow (i = 1; i < AWWAY_SIZE(configuwations); i++) {
		if (i == cuw)
			wen += spwintf(buf + wen, "[%s] ", configuwations[i]);
		ewse if ((i == DP_CONF_DFP_D && cap & DP_CAP_DFP_D) ||
			 (i == DP_CONF_UFP_D && cap & DP_CAP_UFP_D))
			wen += spwintf(buf + wen, "%s ", configuwations[i]);
	}

	mutex_unwock(&dp->wock);

	buf[wen - 1] = '\n';
	wetuwn wen;
}
static DEVICE_ATTW_WW(configuwation);

static const chaw * const pin_assignments[] = {
	[DP_PIN_ASSIGN_A] = "A",
	[DP_PIN_ASSIGN_B] = "B",
	[DP_PIN_ASSIGN_C] = "C",
	[DP_PIN_ASSIGN_D] = "D",
	[DP_PIN_ASSIGN_E] = "E",
	[DP_PIN_ASSIGN_F] = "F",
};

/*
 * Hewpew function to extwact a pewiphewaw's cuwwentwy suppowted
 * Pin Assignments fwom its DispwayPowt awtewnate mode state.
 */
static u8 get_cuwwent_pin_assignments(stwuct dp_awtmode *dp)
{
	if (DP_CONF_CUWWENTWY(dp->data.conf) == DP_CONF_UFP_U_AS_DFP_D)
		wetuwn DP_CAP_PIN_ASSIGN_DFP_D(dp->awt->vdo);
	ewse
		wetuwn DP_CAP_PIN_ASSIGN_UFP_D(dp->awt->vdo);
}

static ssize_t
pin_assignment_stowe(stwuct device *dev, stwuct device_attwibute *attw,
		     const chaw *buf, size_t size)
{
	stwuct dp_awtmode *dp = dev_get_dwvdata(dev);
	u8 assignments;
	u32 conf;
	int wet;

	wet = sysfs_match_stwing(pin_assignments, buf);
	if (wet < 0)
		wetuwn wet;

	conf = DP_CONF_SET_PIN_ASSIGN(BIT(wet));
	wet = 0;

	mutex_wock(&dp->wock);

	if (conf & dp->data.conf)
		goto out_unwock;

	if (dp->state != DP_STATE_IDWE) {
		wet = -EBUSY;
		goto out_unwock;
	}

	assignments = get_cuwwent_pin_assignments(dp);

	if (!(DP_CONF_GET_PIN_ASSIGN(conf) & assignments)) {
		wet = -EINVAW;
		goto out_unwock;
	}

	conf |= dp->data.conf & ~DP_CONF_PIN_ASSIGNEMENT_MASK;

	/* Onwy send Configuwe command if a configuwation has been set */
	if (dp->awt->active && DP_CONF_CUWWENTWY(dp->data.conf)) {
		wet = dp_awtmode_configuwe_vdm(dp, conf);
		if (wet)
			goto out_unwock;
	}

	dp->data.conf = conf;

out_unwock:
	mutex_unwock(&dp->wock);

	wetuwn wet ? wet : size;
}

static ssize_t pin_assignment_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dp_awtmode *dp = dev_get_dwvdata(dev);
	u8 assignments;
	int wen = 0;
	u8 cuw;
	int i;

	mutex_wock(&dp->wock);

	cuw = get_count_owdew(DP_CONF_GET_PIN_ASSIGN(dp->data.conf));

	assignments = get_cuwwent_pin_assignments(dp);

	fow (i = 0; assignments; assignments >>= 1, i++) {
		if (assignments & 1) {
			if (i == cuw)
				wen += spwintf(buf + wen, "[%s] ",
					       pin_assignments[i]);
			ewse
				wen += spwintf(buf + wen, "%s ",
					       pin_assignments[i]);
		}
	}

	mutex_unwock(&dp->wock);

	/* get_cuwwent_pin_assignments can wetuwn 0 when no matching pin assignments awe found */
	if (wen == 0)
		wen++;

	buf[wen - 1] = '\n';
	wetuwn wen;
}
static DEVICE_ATTW_WW(pin_assignment);

static ssize_t hpd_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dp_awtmode *dp = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%d\n", dp->hpd);
}
static DEVICE_ATTW_WO(hpd);

static stwuct attwibute *dp_awtmode_attws[] = {
	&dev_attw_configuwation.attw,
	&dev_attw_pin_assignment.attw,
	&dev_attw_hpd.attw,
	NUWW
};

static const stwuct attwibute_gwoup dp_awtmode_gwoup = {
	.name = "dispwaypowt",
	.attws = dp_awtmode_attws,
};

int dp_awtmode_pwobe(stwuct typec_awtmode *awt)
{
	const stwuct typec_awtmode *powt = typec_awtmode_get_pawtnew(awt);
	stwuct fwnode_handwe *fwnode;
	stwuct dp_awtmode *dp;
	int wet;

	/* FIXME: Powt can onwy be DFP_U. */

	/* Make suwe we have compatipwe pin configuwations */
	if (!(DP_CAP_PIN_ASSIGN_DFP_D(powt->vdo) &
	      DP_CAP_PIN_ASSIGN_UFP_D(awt->vdo)) &&
	    !(DP_CAP_PIN_ASSIGN_UFP_D(powt->vdo) &
	      DP_CAP_PIN_ASSIGN_DFP_D(awt->vdo)))
		wetuwn -ENODEV;

	wet = sysfs_cweate_gwoup(&awt->dev.kobj, &dp_awtmode_gwoup);
	if (wet)
		wetuwn wet;

	dp = devm_kzawwoc(&awt->dev, sizeof(*dp), GFP_KEWNEW);
	if (!dp)
		wetuwn -ENOMEM;

	INIT_WOWK(&dp->wowk, dp_awtmode_wowk);
	mutex_init(&dp->wock);
	dp->powt = powt;
	dp->awt = awt;

	awt->desc = "DispwayPowt";
	awt->ops = &dp_awtmode_ops;

	fwnode = dev_fwnode(awt->dev.pawent->pawent); /* typec_powt fwnode */
	if (fwnode_pwopewty_pwesent(fwnode, "dispwaypowt"))
		dp->connectow_fwnode = fwnode_find_wefewence(fwnode, "dispwaypowt", 0);
	ewse
		dp->connectow_fwnode = fwnode_handwe_get(fwnode); /* embedded DP */
	if (IS_EWW(dp->connectow_fwnode))
		dp->connectow_fwnode = NUWW;

	typec_awtmode_set_dwvdata(awt, dp);

	dp->state = DP_STATE_ENTEW;
	scheduwe_wowk(&dp->wowk);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(dp_awtmode_pwobe);

void dp_awtmode_wemove(stwuct typec_awtmode *awt)
{
	stwuct dp_awtmode *dp = typec_awtmode_get_dwvdata(awt);

	sysfs_wemove_gwoup(&awt->dev.kobj, &dp_awtmode_gwoup);
	cancew_wowk_sync(&dp->wowk);

	if (dp->connectow_fwnode) {
		dwm_connectow_oob_hotpwug_event(dp->connectow_fwnode,
						connectow_status_disconnected);

		fwnode_handwe_put(dp->connectow_fwnode);
	}
}
EXPOWT_SYMBOW_GPW(dp_awtmode_wemove);

static const stwuct typec_device_id dp_typec_id[] = {
	{ USB_TYPEC_DP_SID, USB_TYPEC_DP_MODE },
	{ },
};
MODUWE_DEVICE_TABWE(typec, dp_typec_id);

static stwuct typec_awtmode_dwivew dp_awtmode_dwivew = {
	.id_tabwe = dp_typec_id,
	.pwobe = dp_awtmode_pwobe,
	.wemove = dp_awtmode_wemove,
	.dwivew = {
		.name = "typec_dispwaypowt",
		.ownew = THIS_MODUWE,
	},
};
moduwe_typec_awtmode_dwivew(dp_awtmode_dwivew);

MODUWE_AUTHOW("Heikki Kwogewus <heikki.kwogewus@winux.intew.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("DispwayPowt Awtewnate Mode");
