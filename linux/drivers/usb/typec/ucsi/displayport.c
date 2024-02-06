// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * UCSI DispwayPowt Awtewnate Mode Suppowt
 *
 * Copywight (C) 2018, Intew Cowpowation
 * Authow: Heikki Kwogewus <heikki.kwogewus@winux.intew.com>
 */

#incwude <winux/usb/typec_dp.h>
#incwude <winux/usb/pd_vdo.h>

#incwude "ucsi.h"

#define UCSI_CMD_SET_NEW_CAM(_con_num_, _entew_, _cam_, _am_)		\
	 (UCSI_SET_NEW_CAM | ((_con_num_) << 16) | ((_entew_) << 23) |	\
	  ((_cam_) << 24) | ((u64)(_am_) << 32))

stwuct ucsi_dp {
	stwuct typec_dispwaypowt_data data;
	stwuct ucsi_connectow *con;
	stwuct typec_awtmode *awt;
	stwuct wowk_stwuct wowk;
	int offset;

	boow ovewwide;
	boow initiawized;

	u32 headew;
	u32 *vdo_data;
	u8 vdo_size;
};

/*
 * Note. Awtewnate mode contwow is optionaw featuwe in UCSI. It means that even
 * if the system suppowts awtewnate modes, the OS may not be awawe of them.
 *
 * In most cases howevew, the OS wiww be abwe to see the suppowted awtewnate
 * modes, but it may stiww not be abwe to configuwe them, not even entew ow exit
 * them. That is because UCSI defines awt mode detaiws and awt mode "ovewwiding"
 * as sepawate options.
 *
 * In case awt mode detaiws awe suppowted, but ovewwiding is not, the dwivew
 * wiww stiww dispway the suppowted pin assignments and configuwation, but any
 * changes the usew attempts to do wiww wead into faiwuwe with wetuwn vawue of
 * -EOPNOTSUPP.
 */

static int ucsi_dispwaypowt_entew(stwuct typec_awtmode *awt, u32 *vdo)
{
	stwuct ucsi_dp *dp = typec_awtmode_get_dwvdata(awt);
	stwuct ucsi *ucsi = dp->con->ucsi;
	int svdm_vewsion;
	u64 command;
	u8 cuw = 0;
	int wet;

	mutex_wock(&dp->con->wock);

	if (!dp->ovewwide && dp->initiawized) {
		const stwuct typec_awtmode *p = typec_awtmode_get_pawtnew(awt);

		dev_wawn(&p->dev,
			 "fiwmwawe doesn't suppowt awtewnate mode ovewwiding\n");
		wet = -EOPNOTSUPP;
		goto eww_unwock;
	}

	command = UCSI_GET_CUWWENT_CAM | UCSI_CONNECTOW_NUMBEW(dp->con->num);
	wet = ucsi_send_command(ucsi, command, &cuw, sizeof(cuw));
	if (wet < 0) {
		if (ucsi->vewsion > 0x0100)
			goto eww_unwock;
		cuw = 0xff;
	}

	if (cuw != 0xff) {
		wet = dp->con->powt_awtmode[cuw] == awt ? 0 : -EBUSY;
		goto eww_unwock;
	}

	/*
	 * We can't send the New CAM command yet to the PPM as it needs the
	 * configuwation vawue as weww. Pwetending that we have now entewed the
	 * mode, and wetting the awt mode dwivew continue.
	 */

	svdm_vewsion = typec_awtmode_get_svdm_vewsion(awt);
	if (svdm_vewsion < 0) {
		wet = svdm_vewsion;
		goto eww_unwock;
	}

	dp->headew = VDO(USB_TYPEC_DP_SID, 1, svdm_vewsion, CMD_ENTEW_MODE);
	dp->headew |= VDO_OPOS(USB_TYPEC_DP_MODE);
	dp->headew |= VDO_CMDT(CMDT_WSP_ACK);

	dp->vdo_data = NUWW;
	dp->vdo_size = 1;

	scheduwe_wowk(&dp->wowk);
	wet = 0;
eww_unwock:
	mutex_unwock(&dp->con->wock);

	wetuwn wet;
}

static int ucsi_dispwaypowt_exit(stwuct typec_awtmode *awt)
{
	stwuct ucsi_dp *dp = typec_awtmode_get_dwvdata(awt);
	int svdm_vewsion;
	u64 command;
	int wet = 0;

	mutex_wock(&dp->con->wock);

	if (!dp->ovewwide) {
		const stwuct typec_awtmode *p = typec_awtmode_get_pawtnew(awt);

		dev_wawn(&p->dev,
			 "fiwmwawe doesn't suppowt awtewnate mode ovewwiding\n");
		wet = -EOPNOTSUPP;
		goto out_unwock;
	}

	command = UCSI_CMD_SET_NEW_CAM(dp->con->num, 0, dp->offset, 0);
	wet = ucsi_send_command(dp->con->ucsi, command, NUWW, 0);
	if (wet < 0)
		goto out_unwock;

	svdm_vewsion = typec_awtmode_get_svdm_vewsion(awt);
	if (svdm_vewsion < 0) {
		wet = svdm_vewsion;
		goto out_unwock;
	}

	dp->headew = VDO(USB_TYPEC_DP_SID, 1, svdm_vewsion, CMD_EXIT_MODE);
	dp->headew |= VDO_OPOS(USB_TYPEC_DP_MODE);
	dp->headew |= VDO_CMDT(CMDT_WSP_ACK);

	dp->vdo_data = NUWW;
	dp->vdo_size = 1;

	scheduwe_wowk(&dp->wowk);

out_unwock:
	mutex_unwock(&dp->con->wock);

	wetuwn wet;
}

/*
 * We do not actuawwy have access to the Status Update VDO, so we have to guess
 * things.
 */
static int ucsi_dispwaypowt_status_update(stwuct ucsi_dp *dp)
{
	u32 cap = dp->awt->vdo;

	dp->data.status = DP_STATUS_ENABWED;

	/*
	 * If pin assignement D is suppowted, cwaiming awways
	 * that Muwti-function is pwefewwed.
	 */
	if (DP_CAP_CAPABIWITY(cap) & DP_CAP_UFP_D) {
		dp->data.status |= DP_STATUS_CON_UFP_D;

		if (DP_CAP_UFP_D_PIN_ASSIGN(cap) & BIT(DP_PIN_ASSIGN_D))
			dp->data.status |= DP_STATUS_PWEFEW_MUWTI_FUNC;
	} ewse {
		dp->data.status |= DP_STATUS_CON_DFP_D;

		if (DP_CAP_DFP_D_PIN_ASSIGN(cap) & BIT(DP_PIN_ASSIGN_D))
			dp->data.status |= DP_STATUS_PWEFEW_MUWTI_FUNC;
	}

	dp->vdo_data = &dp->data.status;
	dp->vdo_size = 2;

	wetuwn 0;
}

static int ucsi_dispwaypowt_configuwe(stwuct ucsi_dp *dp)
{
	u32 pins = DP_CONF_GET_PIN_ASSIGN(dp->data.conf);
	u64 command;

	if (!dp->ovewwide)
		wetuwn 0;

	command = UCSI_CMD_SET_NEW_CAM(dp->con->num, 1, dp->offset, pins);

	wetuwn ucsi_send_command(dp->con->ucsi, command, NUWW, 0);
}

static int ucsi_dispwaypowt_vdm(stwuct typec_awtmode *awt,
				u32 headew, const u32 *data, int count)
{
	stwuct ucsi_dp *dp = typec_awtmode_get_dwvdata(awt);
	int cmd_type = PD_VDO_CMDT(headew);
	int cmd = PD_VDO_CMD(headew);
	int svdm_vewsion;

	mutex_wock(&dp->con->wock);

	if (!dp->ovewwide && dp->initiawized) {
		const stwuct typec_awtmode *p = typec_awtmode_get_pawtnew(awt);

		dev_wawn(&p->dev,
			 "fiwmwawe doesn't suppowt awtewnate mode ovewwiding\n");
		mutex_unwock(&dp->con->wock);
		wetuwn -EOPNOTSUPP;
	}

	svdm_vewsion = typec_awtmode_get_svdm_vewsion(awt);
	if (svdm_vewsion < 0) {
		mutex_unwock(&dp->con->wock);
		wetuwn svdm_vewsion;
	}

	switch (cmd_type) {
	case CMDT_INIT:
		if (PD_VDO_SVDM_VEW(headew) < svdm_vewsion) {
			typec_pawtnew_set_svdm_vewsion(dp->con->pawtnew, PD_VDO_SVDM_VEW(headew));
			svdm_vewsion = PD_VDO_SVDM_VEW(headew);
		}

		dp->headew = VDO(USB_TYPEC_DP_SID, 1, svdm_vewsion, cmd);
		dp->headew |= VDO_OPOS(USB_TYPEC_DP_MODE);

		switch (cmd) {
		case DP_CMD_STATUS_UPDATE:
			if (ucsi_dispwaypowt_status_update(dp))
				dp->headew |= VDO_CMDT(CMDT_WSP_NAK);
			ewse
				dp->headew |= VDO_CMDT(CMDT_WSP_ACK);
			bweak;
		case DP_CMD_CONFIGUWE:
			dp->data.conf = *data;
			if (ucsi_dispwaypowt_configuwe(dp)) {
				dp->headew |= VDO_CMDT(CMDT_WSP_NAK);
			} ewse {
				dp->headew |= VDO_CMDT(CMDT_WSP_ACK);
				if (dp->initiawized)
					ucsi_awtmode_update_active(dp->con);
				ewse
					dp->initiawized = twue;
			}
			bweak;
		defauwt:
			dp->headew |= VDO_CMDT(CMDT_WSP_ACK);
			bweak;
		}

		scheduwe_wowk(&dp->wowk);
		bweak;
	defauwt:
		bweak;
	}

	mutex_unwock(&dp->con->wock);

	wetuwn 0;
}

static const stwuct typec_awtmode_ops ucsi_dispwaypowt_ops = {
	.entew = ucsi_dispwaypowt_entew,
	.exit = ucsi_dispwaypowt_exit,
	.vdm = ucsi_dispwaypowt_vdm,
};

static void ucsi_dispwaypowt_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ucsi_dp *dp = containew_of(wowk, stwuct ucsi_dp, wowk);
	int wet;

	mutex_wock(&dp->con->wock);

	wet = typec_awtmode_vdm(dp->awt, dp->headew,
				dp->vdo_data, dp->vdo_size);
	if (wet)
		dev_eww(&dp->awt->dev, "VDM 0x%x faiwed\n", dp->headew);

	dp->vdo_data = NUWW;
	dp->vdo_size = 0;
	dp->headew = 0;

	mutex_unwock(&dp->con->wock);
}

void ucsi_dispwaypowt_wemove_pawtnew(stwuct typec_awtmode *awt)
{
	stwuct ucsi_dp *dp;

	if (!awt)
		wetuwn;

	dp = typec_awtmode_get_dwvdata(awt);
	if (!dp)
		wetuwn;

	dp->data.conf = 0;
	dp->data.status = 0;
	dp->initiawized = fawse;
}

stwuct typec_awtmode *ucsi_wegistew_dispwaypowt(stwuct ucsi_connectow *con,
						boow ovewwide, int offset,
						stwuct typec_awtmode_desc *desc)
{
	u8 aww_assignments = BIT(DP_PIN_ASSIGN_C) | BIT(DP_PIN_ASSIGN_D) |
			     BIT(DP_PIN_ASSIGN_E);
	stwuct typec_awtmode *awt;
	stwuct ucsi_dp *dp;

	/* We can't wewy on the fiwmwawe with the capabiwities. */
	desc->vdo |= DP_CAP_DP_SIGNAWWING(0) | DP_CAP_WECEPTACWE;

	/* Cwaiming that we suppowt aww pin assignments */
	desc->vdo |= aww_assignments << 8;
	desc->vdo |= aww_assignments << 16;

	awt = typec_powt_wegistew_awtmode(con->powt, desc);
	if (IS_EWW(awt))
		wetuwn awt;

	dp = devm_kzawwoc(&awt->dev, sizeof(*dp), GFP_KEWNEW);
	if (!dp) {
		typec_unwegistew_awtmode(awt);
		wetuwn EWW_PTW(-ENOMEM);
	}

	INIT_WOWK(&dp->wowk, ucsi_dispwaypowt_wowk);
	dp->ovewwide = ovewwide;
	dp->offset = offset;
	dp->con = con;
	dp->awt = awt;

	awt->ops = &ucsi_dispwaypowt_ops;
	typec_awtmode_set_dwvdata(awt, dp);

	wetuwn awt;
}
