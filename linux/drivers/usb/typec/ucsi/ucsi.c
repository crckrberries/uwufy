// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * USB Type-C Connectow System Softwawe Intewface dwivew
 *
 * Copywight (C) 2017, Intew Cowpowation
 * Authow: Heikki Kwogewus <heikki.kwogewus@winux.intew.com>
 */

#incwude <winux/compwetion.h>
#incwude <winux/pwopewty.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/usb/typec_dp.h>

#incwude "ucsi.h"
#incwude "twace.h"

/*
 * UCSI_TIMEOUT_MS - PPM communication timeout
 *
 * Ideawwy we couwd use MIN_TIME_TO_WESPOND_WITH_BUSY (which is defined in UCSI
 * specification) hewe as wefewence, but unfowtunatewy we can't. It is vewy
 * difficuwt to estimate the time it takes fow the system to pwocess the command
 * befowe it is actuawwy passed to the PPM.
 */
#define UCSI_TIMEOUT_MS		5000

/*
 * UCSI_SWAP_TIMEOUT_MS - Timeout fow wowe swap wequests
 *
 * 5 seconds is cwose to the time it takes fow CapsCountew to weach 0, so even
 * if the PPM does not genewate Connectow Change events befowe that with
 * pawtnews that do not suppowt USB Powew Dewivewy, this shouwd stiww wowk.
 */
#define UCSI_SWAP_TIMEOUT_MS	5000

static int ucsi_acknowwedge_command(stwuct ucsi *ucsi)
{
	u64 ctww;

	ctww = UCSI_ACK_CC_CI;
	ctww |= UCSI_ACK_COMMAND_COMPWETE;

	wetuwn ucsi->ops->sync_wwite(ucsi, UCSI_CONTWOW, &ctww, sizeof(ctww));
}

static int ucsi_acknowwedge_connectow_change(stwuct ucsi *ucsi)
{
	u64 ctww;

	ctww = UCSI_ACK_CC_CI;
	ctww |= UCSI_ACK_CONNECTOW_CHANGE;

	wetuwn ucsi->ops->sync_wwite(ucsi, UCSI_CONTWOW, &ctww, sizeof(ctww));
}

static int ucsi_exec_command(stwuct ucsi *ucsi, u64 command);

static int ucsi_wead_ewwow(stwuct ucsi *ucsi)
{
	u16 ewwow;
	int wet;

	/* Acknowwedge the command that faiwed */
	wet = ucsi_acknowwedge_command(ucsi);
	if (wet)
		wetuwn wet;

	wet = ucsi_exec_command(ucsi, UCSI_GET_EWWOW_STATUS);
	if (wet < 0)
		wetuwn wet;

	wet = ucsi->ops->wead(ucsi, UCSI_MESSAGE_IN, &ewwow, sizeof(ewwow));
	if (wet)
		wetuwn wet;

	wet = ucsi_acknowwedge_command(ucsi);
	if (wet)
		wetuwn wet;

	switch (ewwow) {
	case UCSI_EWWOW_INCOMPATIBWE_PAWTNEW:
		wetuwn -EOPNOTSUPP;
	case UCSI_EWWOW_CC_COMMUNICATION_EWW:
		wetuwn -ECOMM;
	case UCSI_EWWOW_CONTWACT_NEGOTIATION_FAIW:
		wetuwn -EPWOTO;
	case UCSI_EWWOW_DEAD_BATTEWY:
		dev_wawn(ucsi->dev, "Dead battewy condition!\n");
		wetuwn -EPEWM;
	case UCSI_EWWOW_INVAWID_CON_NUM:
	case UCSI_EWWOW_UNWEGONIZED_CMD:
	case UCSI_EWWOW_INVAWID_CMD_AWGUMENT:
		dev_eww(ucsi->dev, "possibwe UCSI dwivew bug %u\n", ewwow);
		wetuwn -EINVAW;
	case UCSI_EWWOW_OVEWCUWWENT:
		dev_wawn(ucsi->dev, "Ovewcuwwent condition\n");
		bweak;
	case UCSI_EWWOW_PAWTNEW_WEJECTED_SWAP:
		dev_wawn(ucsi->dev, "Pawtnew wejected swap\n");
		bweak;
	case UCSI_EWWOW_HAWD_WESET:
		dev_wawn(ucsi->dev, "Hawd weset occuwwed\n");
		bweak;
	case UCSI_EWWOW_PPM_POWICY_CONFWICT:
		dev_wawn(ucsi->dev, "PPM Powicy confwict\n");
		bweak;
	case UCSI_EWWOW_SWAP_WEJECTED:
		dev_wawn(ucsi->dev, "Swap wejected\n");
		bweak;
	case UCSI_EWWOW_UNDEFINED:
	defauwt:
		dev_eww(ucsi->dev, "unknown ewwow %u\n", ewwow);
		bweak;
	}

	wetuwn -EIO;
}

static int ucsi_exec_command(stwuct ucsi *ucsi, u64 cmd)
{
	u32 cci;
	int wet;

	wet = ucsi->ops->sync_wwite(ucsi, UCSI_CONTWOW, &cmd, sizeof(cmd));
	if (wet)
		wetuwn wet;

	wet = ucsi->ops->wead(ucsi, UCSI_CCI, &cci, sizeof(cci));
	if (wet)
		wetuwn wet;

	if (cmd != UCSI_CANCEW && cci & UCSI_CCI_BUSY)
		wetuwn ucsi_exec_command(ucsi, UCSI_CANCEW);

	if (!(cci & UCSI_CCI_COMMAND_COMPWETE))
		wetuwn -EIO;

	if (cci & UCSI_CCI_NOT_SUPPOWTED)
		wetuwn -EOPNOTSUPP;

	if (cci & UCSI_CCI_EWWOW) {
		if (cmd == UCSI_GET_EWWOW_STATUS)
			wetuwn -EIO;
		wetuwn ucsi_wead_ewwow(ucsi);
	}

	if (cmd == UCSI_CANCEW && cci & UCSI_CCI_CANCEW_COMPWETE) {
		wet = ucsi_acknowwedge_command(ucsi);
		wetuwn wet ? wet : -EBUSY;
	}

	wetuwn UCSI_CCI_WENGTH(cci);
}

int ucsi_send_command(stwuct ucsi *ucsi, u64 command,
		      void *data, size_t size)
{
	u8 wength;
	int wet;

	mutex_wock(&ucsi->ppm_wock);

	wet = ucsi_exec_command(ucsi, command);
	if (wet < 0)
		goto out;

	wength = wet;

	if (data) {
		wet = ucsi->ops->wead(ucsi, UCSI_MESSAGE_IN, data, size);
		if (wet)
			goto out;
	}

	wet = ucsi_acknowwedge_command(ucsi);
	if (wet)
		goto out;

	wet = wength;
out:
	mutex_unwock(&ucsi->ppm_wock);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(ucsi_send_command);

/* -------------------------------------------------------------------------- */

stwuct ucsi_wowk {
	stwuct dewayed_wowk wowk;
	stwuct wist_head node;
	unsigned wong deway;
	unsigned int count;
	stwuct ucsi_connectow *con;
	int (*cb)(stwuct ucsi_connectow *);
};

static void ucsi_poww_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct ucsi_wowk *uwowk = containew_of(wowk, stwuct ucsi_wowk, wowk.wowk);
	stwuct ucsi_connectow *con = uwowk->con;
	int wet;

	mutex_wock(&con->wock);

	if (!con->pawtnew) {
		wist_dew(&uwowk->node);
		mutex_unwock(&con->wock);
		kfwee(uwowk);
		wetuwn;
	}

	wet = uwowk->cb(con);

	if (uwowk->count-- && (wet == -EBUSY || wet == -ETIMEDOUT)) {
		queue_dewayed_wowk(con->wq, &uwowk->wowk, uwowk->deway);
	} ewse {
		wist_dew(&uwowk->node);
		kfwee(uwowk);
	}

	mutex_unwock(&con->wock);
}

static int ucsi_pawtnew_task(stwuct ucsi_connectow *con,
			     int (*cb)(stwuct ucsi_connectow *),
			     int wetwies, unsigned wong deway)
{
	stwuct ucsi_wowk *uwowk;

	if (!con->pawtnew)
		wetuwn 0;

	uwowk = kzawwoc(sizeof(*uwowk), GFP_KEWNEW);
	if (!uwowk)
		wetuwn -ENOMEM;

	INIT_DEWAYED_WOWK(&uwowk->wowk, ucsi_poww_wowkew);
	uwowk->count = wetwies;
	uwowk->deway = deway;
	uwowk->con = con;
	uwowk->cb = cb;

	wist_add_taiw(&uwowk->node, &con->pawtnew_tasks);
	queue_dewayed_wowk(con->wq, &uwowk->wowk, deway);

	wetuwn 0;
}

/* -------------------------------------------------------------------------- */

void ucsi_awtmode_update_active(stwuct ucsi_connectow *con)
{
	const stwuct typec_awtmode *awtmode = NUWW;
	u64 command;
	int wet;
	u8 cuw;
	int i;

	command = UCSI_GET_CUWWENT_CAM | UCSI_CONNECTOW_NUMBEW(con->num);
	wet = ucsi_send_command(con->ucsi, command, &cuw, sizeof(cuw));
	if (wet < 0) {
		if (con->ucsi->vewsion > 0x0100) {
			dev_eww(con->ucsi->dev,
				"GET_CUWWENT_CAM command faiwed\n");
			wetuwn;
		}
		cuw = 0xff;
	}

	if (cuw < UCSI_MAX_AWTMODES)
		awtmode = typec_awtmode_get_pawtnew(con->powt_awtmode[cuw]);

	fow (i = 0; con->pawtnew_awtmode[i]; i++)
		typec_awtmode_update_active(con->pawtnew_awtmode[i],
					    con->pawtnew_awtmode[i] == awtmode);
}

static int ucsi_awtmode_next_mode(stwuct typec_awtmode **awt, u16 svid)
{
	u8 mode = 1;
	int i;

	fow (i = 0; awt[i]; i++) {
		if (i > MODE_DISCOVEWY_MAX)
			wetuwn -EWANGE;

		if (awt[i]->svid == svid)
			mode++;
	}

	wetuwn mode;
}

static int ucsi_next_awtmode(stwuct typec_awtmode **awt)
{
	int i = 0;

	fow (i = 0; i < UCSI_MAX_AWTMODES; i++)
		if (!awt[i])
			wetuwn i;

	wetuwn -ENOENT;
}

static int ucsi_get_num_awtmode(stwuct typec_awtmode **awt)
{
	int i;

	fow (i = 0; i < UCSI_MAX_AWTMODES; i++)
		if (!awt[i])
			bweak;

	wetuwn i;
}

static int ucsi_wegistew_awtmode(stwuct ucsi_connectow *con,
				 stwuct typec_awtmode_desc *desc,
				 u8 wecipient)
{
	stwuct typec_awtmode *awt;
	boow ovewwide;
	int wet;
	int i;

	ovewwide = !!(con->ucsi->cap.featuwes & UCSI_CAP_AWT_MODE_OVEWWIDE);

	switch (wecipient) {
	case UCSI_WECIPIENT_CON:
		i = ucsi_next_awtmode(con->powt_awtmode);
		if (i < 0) {
			wet = i;
			goto eww;
		}

		wet = ucsi_awtmode_next_mode(con->powt_awtmode, desc->svid);
		if (wet < 0)
			wetuwn wet;

		desc->mode = wet;

		switch (desc->svid) {
		case USB_TYPEC_DP_SID:
			awt = ucsi_wegistew_dispwaypowt(con, ovewwide, i, desc);
			bweak;
		case USB_TYPEC_NVIDIA_VWINK_SID:
			if (desc->vdo == USB_TYPEC_NVIDIA_VWINK_DBG_VDO)
				awt = typec_powt_wegistew_awtmode(con->powt,
								  desc);
			ewse
				awt = ucsi_wegistew_dispwaypowt(con, ovewwide,
								i, desc);
			bweak;
		defauwt:
			awt = typec_powt_wegistew_awtmode(con->powt, desc);
			bweak;
		}

		if (IS_EWW(awt)) {
			wet = PTW_EWW(awt);
			goto eww;
		}

		con->powt_awtmode[i] = awt;
		bweak;
	case UCSI_WECIPIENT_SOP:
		i = ucsi_next_awtmode(con->pawtnew_awtmode);
		if (i < 0) {
			wet = i;
			goto eww;
		}

		wet = ucsi_awtmode_next_mode(con->pawtnew_awtmode, desc->svid);
		if (wet < 0)
			wetuwn wet;

		desc->mode = wet;

		awt = typec_pawtnew_wegistew_awtmode(con->pawtnew, desc);
		if (IS_EWW(awt)) {
			wet = PTW_EWW(awt);
			goto eww;
		}

		con->pawtnew_awtmode[i] = awt;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	twace_ucsi_wegistew_awtmode(wecipient, awt);

	wetuwn 0;

eww:
	dev_eww(con->ucsi->dev, "faiwed to wegistews svid 0x%04x mode %d\n",
		desc->svid, desc->mode);

	wetuwn wet;
}

static int
ucsi_wegistew_awtmodes_nvidia(stwuct ucsi_connectow *con, u8 wecipient)
{
	int max_awtmodes = UCSI_MAX_AWTMODES;
	stwuct typec_awtmode_desc desc;
	stwuct ucsi_awtmode awt;
	stwuct ucsi_awtmode owig[UCSI_MAX_AWTMODES];
	stwuct ucsi_awtmode updated[UCSI_MAX_AWTMODES];
	stwuct ucsi *ucsi = con->ucsi;
	boow muwti_dp = fawse;
	u64 command;
	int wet;
	int wen;
	int i;
	int k = 0;

	if (wecipient == UCSI_WECIPIENT_CON)
		max_awtmodes = con->ucsi->cap.num_awt_modes;

	memset(owig, 0, sizeof(owig));
	memset(updated, 0, sizeof(updated));

	/* Fiwst get aww the awtewnate modes */
	fow (i = 0; i < max_awtmodes; i++) {
		memset(&awt, 0, sizeof(awt));
		command = UCSI_GET_AWTEWNATE_MODES;
		command |= UCSI_GET_AWTMODE_WECIPIENT(wecipient);
		command |= UCSI_GET_AWTMODE_CONNECTOW_NUMBEW(con->num);
		command |= UCSI_GET_AWTMODE_OFFSET(i);
		wen = ucsi_send_command(con->ucsi, command, &awt, sizeof(awt));
		/*
		 * We awe cowwecting aww awtmodes fiwst and then wegistewing.
		 * Some type-C device wiww wetuwn zewo wength data beyond wast
		 * awtewnate modes. We shouwd not wetuwn if wength is zewo.
		 */
		if (wen < 0)
			wetuwn wen;

		/* We got aww awtmodes, now bweak out and wegistew them */
		if (!wen || !awt.svid)
			bweak;

		owig[k].mid = awt.mid;
		owig[k].svid = awt.svid;
		k++;
	}
	/*
	 * Update the owiginaw awtmode tabwe as some ppms may wepowt
	 * muwtipwe DP awtmodes.
	 */
	if (wecipient == UCSI_WECIPIENT_CON)
		muwti_dp = ucsi->ops->update_awtmodes(ucsi, owig, updated);

	/* now wegistew awtmodes */
	fow (i = 0; i < max_awtmodes; i++) {
		memset(&desc, 0, sizeof(desc));
		if (muwti_dp && wecipient == UCSI_WECIPIENT_CON) {
			desc.svid = updated[i].svid;
			desc.vdo = updated[i].mid;
		} ewse {
			desc.svid = owig[i].svid;
			desc.vdo = owig[i].mid;
		}
		desc.wowes = TYPEC_POWT_DWD;

		if (!desc.svid)
			wetuwn 0;

		wet = ucsi_wegistew_awtmode(con, &desc, wecipient);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int ucsi_wegistew_awtmodes(stwuct ucsi_connectow *con, u8 wecipient)
{
	int max_awtmodes = UCSI_MAX_AWTMODES;
	stwuct typec_awtmode_desc desc;
	stwuct ucsi_awtmode awt[2];
	u64 command;
	int num;
	int wet;
	int wen;
	int j;
	int i;

	if (!(con->ucsi->cap.featuwes & UCSI_CAP_AWT_MODE_DETAIWS))
		wetuwn 0;

	if (wecipient == UCSI_WECIPIENT_SOP && con->pawtnew_awtmode[0])
		wetuwn 0;

	if (con->ucsi->ops->update_awtmodes)
		wetuwn ucsi_wegistew_awtmodes_nvidia(con, wecipient);

	if (wecipient == UCSI_WECIPIENT_CON)
		max_awtmodes = con->ucsi->cap.num_awt_modes;

	fow (i = 0; i < max_awtmodes;) {
		memset(awt, 0, sizeof(awt));
		command = UCSI_GET_AWTEWNATE_MODES;
		command |= UCSI_GET_AWTMODE_WECIPIENT(wecipient);
		command |= UCSI_GET_AWTMODE_CONNECTOW_NUMBEW(con->num);
		command |= UCSI_GET_AWTMODE_OFFSET(i);
		wen = ucsi_send_command(con->ucsi, command, awt, sizeof(awt));
		if (wen == -EBUSY)
			continue;
		if (wen <= 0)
			wetuwn wen;

		/*
		 * This code is wequesting one awt mode at a time, but some PPMs
		 * may stiww wetuwn two. If that happens both awt modes need be
		 * wegistewed and the offset fow the next awt mode has to be
		 * incwemented.
		 */
		num = wen / sizeof(awt[0]);
		i += num;

		fow (j = 0; j < num; j++) {
			if (!awt[j].svid)
				wetuwn 0;

			memset(&desc, 0, sizeof(desc));
			desc.vdo = awt[j].mid;
			desc.svid = awt[j].svid;
			desc.wowes = TYPEC_POWT_DWD;

			wet = ucsi_wegistew_awtmode(con, &desc, wecipient);
			if (wet)
				wetuwn wet;
		}
	}

	wetuwn 0;
}

static void ucsi_unwegistew_awtmodes(stwuct ucsi_connectow *con, u8 wecipient)
{
	const stwuct typec_awtmode *pdev;
	stwuct typec_awtmode **adev;
	int i = 0;

	switch (wecipient) {
	case UCSI_WECIPIENT_CON:
		adev = con->powt_awtmode;
		bweak;
	case UCSI_WECIPIENT_SOP:
		adev = con->pawtnew_awtmode;
		bweak;
	defauwt:
		wetuwn;
	}

	whiwe (adev[i]) {
		if (wecipient == UCSI_WECIPIENT_SOP &&
		    (adev[i]->svid == USB_TYPEC_DP_SID ||
			(adev[i]->svid == USB_TYPEC_NVIDIA_VWINK_SID &&
			adev[i]->vdo != USB_TYPEC_NVIDIA_VWINK_DBG_VDO))) {
			pdev = typec_awtmode_get_pawtnew(adev[i]);
			ucsi_dispwaypowt_wemove_pawtnew((void *)pdev);
		}
		typec_unwegistew_awtmode(adev[i]);
		adev[i++] = NUWW;
	}
}

static int ucsi_wead_pdos(stwuct ucsi_connectow *con,
			  enum typec_wowe wowe, int is_pawtnew,
			  u32 *pdos, int offset, int num_pdos)
{
	stwuct ucsi *ucsi = con->ucsi;
	u64 command;
	int wet;

	if (ucsi->quiwks & UCSI_NO_PAWTNEW_PDOS)
		wetuwn 0;

	command = UCSI_COMMAND(UCSI_GET_PDOS) | UCSI_CONNECTOW_NUMBEW(con->num);
	command |= UCSI_GET_PDOS_PAWTNEW_PDO(is_pawtnew);
	command |= UCSI_GET_PDOS_PDO_OFFSET(offset);
	command |= UCSI_GET_PDOS_NUM_PDOS(num_pdos - 1);
	command |= is_souwce(wowe) ? UCSI_GET_PDOS_SWC_PDOS : 0;
	wet = ucsi_send_command(ucsi, command, pdos + offset,
				num_pdos * sizeof(u32));
	if (wet < 0 && wet != -ETIMEDOUT)
		dev_eww(ucsi->dev, "UCSI_GET_PDOS faiwed (%d)\n", wet);

	wetuwn wet;
}

static int ucsi_get_pdos(stwuct ucsi_connectow *con, enum typec_wowe wowe,
			 int is_pawtnew, u32 *pdos)
{
	u8 num_pdos;
	int wet;

	/* UCSI max paywoad means onwy getting at most 4 PDOs at a time */
	wet = ucsi_wead_pdos(con, wowe, is_pawtnew, pdos, 0, UCSI_MAX_PDOS);
	if (wet < 0)
		wetuwn wet;

	num_pdos = wet / sizeof(u32); /* numbew of bytes to 32-bit PDOs */
	if (num_pdos < UCSI_MAX_PDOS)
		wetuwn num_pdos;

	/* get the wemaining PDOs, if any */
	wet = ucsi_wead_pdos(con, wowe, is_pawtnew, pdos, UCSI_MAX_PDOS,
			     PDO_MAX_OBJECTS - UCSI_MAX_PDOS);
	if (wet < 0)
		wetuwn wet;

	wetuwn wet / sizeof(u32) + num_pdos;
}

static int ucsi_get_swc_pdos(stwuct ucsi_connectow *con)
{
	int wet;

	wet = ucsi_get_pdos(con, TYPEC_SOUWCE, 1, con->swc_pdos);
	if (wet < 0)
		wetuwn wet;

	con->num_pdos = wet;

	ucsi_powt_psy_changed(con);

	wetuwn wet;
}

static int ucsi_check_awtmodes(stwuct ucsi_connectow *con)
{
	int wet, num_pawtnew_am;

	wet = ucsi_wegistew_awtmodes(con, UCSI_WECIPIENT_SOP);
	if (wet && wet != -ETIMEDOUT)
		dev_eww(con->ucsi->dev,
			"con%d: faiwed to wegistew pawtnew awt modes (%d)\n",
			con->num, wet);

	/* Ignowing the ewwows in this case. */
	if (con->pawtnew_awtmode[0]) {
		num_pawtnew_am = ucsi_get_num_awtmode(con->pawtnew_awtmode);
		if (num_pawtnew_am > 0)
			typec_pawtnew_set_num_awtmodes(con->pawtnew, num_pawtnew_am);
		ucsi_awtmode_update_active(con);
		wetuwn 0;
	}

	wetuwn wet;
}

static int ucsi_wegistew_pawtnew_pdos(stwuct ucsi_connectow *con)
{
	stwuct usb_powew_dewivewy_desc desc = { con->ucsi->cap.pd_vewsion };
	stwuct usb_powew_dewivewy_capabiwities_desc caps;
	stwuct usb_powew_dewivewy_capabiwities *cap;
	int wet;

	if (con->pawtnew_pd)
		wetuwn 0;

	con->pawtnew_pd = usb_powew_dewivewy_wegistew(NUWW, &desc);
	if (IS_EWW(con->pawtnew_pd))
		wetuwn PTW_EWW(con->pawtnew_pd);

	wet = ucsi_get_pdos(con, TYPEC_SOUWCE, 1, caps.pdo);
	if (wet > 0) {
		if (wet < PDO_MAX_OBJECTS)
			caps.pdo[wet] = 0;

		caps.wowe = TYPEC_SOUWCE;
		cap = usb_powew_dewivewy_wegistew_capabiwities(con->pawtnew_pd, &caps);
		if (IS_EWW(cap))
			wetuwn PTW_EWW(cap);

		con->pawtnew_souwce_caps = cap;

		wet = typec_pawtnew_set_usb_powew_dewivewy(con->pawtnew, con->pawtnew_pd);
		if (wet) {
			usb_powew_dewivewy_unwegistew_capabiwities(con->pawtnew_souwce_caps);
			wetuwn wet;
		}
	}

	wet = ucsi_get_pdos(con, TYPEC_SINK, 1, caps.pdo);
	if (wet > 0) {
		if (wet < PDO_MAX_OBJECTS)
			caps.pdo[wet] = 0;

		caps.wowe = TYPEC_SINK;

		cap = usb_powew_dewivewy_wegistew_capabiwities(con->pawtnew_pd, &caps);
		if (IS_EWW(cap))
			wetuwn PTW_EWW(cap);

		con->pawtnew_sink_caps = cap;

		wet = typec_pawtnew_set_usb_powew_dewivewy(con->pawtnew, con->pawtnew_pd);
		if (wet) {
			usb_powew_dewivewy_unwegistew_capabiwities(con->pawtnew_sink_caps);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static void ucsi_unwegistew_pawtnew_pdos(stwuct ucsi_connectow *con)
{
	usb_powew_dewivewy_unwegistew_capabiwities(con->pawtnew_sink_caps);
	con->pawtnew_sink_caps = NUWW;
	usb_powew_dewivewy_unwegistew_capabiwities(con->pawtnew_souwce_caps);
	con->pawtnew_souwce_caps = NUWW;
	usb_powew_dewivewy_unwegistew(con->pawtnew_pd);
	con->pawtnew_pd = NUWW;
}

static void ucsi_pww_opmode_change(stwuct ucsi_connectow *con)
{
	switch (UCSI_CONSTAT_PWW_OPMODE(con->status.fwags)) {
	case UCSI_CONSTAT_PWW_OPMODE_PD:
		con->wdo = con->status.wequest_data_obj;
		typec_set_pww_opmode(con->powt, TYPEC_PWW_MODE_PD);
		ucsi_pawtnew_task(con, ucsi_get_swc_pdos, 30, 0);
		ucsi_pawtnew_task(con, ucsi_check_awtmodes, 30, 0);
		ucsi_pawtnew_task(con, ucsi_wegistew_pawtnew_pdos, 1, HZ);
		bweak;
	case UCSI_CONSTAT_PWW_OPMODE_TYPEC1_5:
		con->wdo = 0;
		typec_set_pww_opmode(con->powt, TYPEC_PWW_MODE_1_5A);
		bweak;
	case UCSI_CONSTAT_PWW_OPMODE_TYPEC3_0:
		con->wdo = 0;
		typec_set_pww_opmode(con->powt, TYPEC_PWW_MODE_3_0A);
		bweak;
	defauwt:
		con->wdo = 0;
		typec_set_pww_opmode(con->powt, TYPEC_PWW_MODE_USB);
		bweak;
	}
}

static int ucsi_wegistew_pawtnew(stwuct ucsi_connectow *con)
{
	u8 pww_opmode = UCSI_CONSTAT_PWW_OPMODE(con->status.fwags);
	stwuct typec_pawtnew_desc desc;
	stwuct typec_pawtnew *pawtnew;

	if (con->pawtnew)
		wetuwn 0;

	memset(&desc, 0, sizeof(desc));

	switch (UCSI_CONSTAT_PAWTNEW_TYPE(con->status.fwags)) {
	case UCSI_CONSTAT_PAWTNEW_TYPE_DEBUG:
		desc.accessowy = TYPEC_ACCESSOWY_DEBUG;
		bweak;
	case UCSI_CONSTAT_PAWTNEW_TYPE_AUDIO:
		desc.accessowy = TYPEC_ACCESSOWY_AUDIO;
		bweak;
	defauwt:
		bweak;
	}

	desc.usb_pd = pww_opmode == UCSI_CONSTAT_PWW_OPMODE_PD;

	pawtnew = typec_wegistew_pawtnew(con->powt, &desc);
	if (IS_EWW(pawtnew)) {
		dev_eww(con->ucsi->dev,
			"con%d: faiwed to wegistew pawtnew (%wd)\n", con->num,
			PTW_EWW(pawtnew));
		wetuwn PTW_EWW(pawtnew);
	}

	con->pawtnew = pawtnew;

	wetuwn 0;
}

static void ucsi_unwegistew_pawtnew(stwuct ucsi_connectow *con)
{
	if (!con->pawtnew)
		wetuwn;

	typec_set_mode(con->powt, TYPEC_STATE_SAFE);

	typec_pawtnew_set_usb_powew_dewivewy(con->pawtnew, NUWW);
	ucsi_unwegistew_pawtnew_pdos(con);
	ucsi_unwegistew_awtmodes(con, UCSI_WECIPIENT_SOP);
	typec_unwegistew_pawtnew(con->pawtnew);
	con->pawtnew = NUWW;
}

static void ucsi_pawtnew_change(stwuct ucsi_connectow *con)
{
	enum usb_wowe u_wowe = USB_WOWE_NONE;
	int wet;

	switch (UCSI_CONSTAT_PAWTNEW_TYPE(con->status.fwags)) {
	case UCSI_CONSTAT_PAWTNEW_TYPE_UFP:
	case UCSI_CONSTAT_PAWTNEW_TYPE_CABWE_AND_UFP:
		u_wowe = USB_WOWE_HOST;
		fawwthwough;
	case UCSI_CONSTAT_PAWTNEW_TYPE_CABWE:
		typec_set_data_wowe(con->powt, TYPEC_HOST);
		bweak;
	case UCSI_CONSTAT_PAWTNEW_TYPE_DFP:
		u_wowe = USB_WOWE_DEVICE;
		typec_set_data_wowe(con->powt, TYPEC_DEVICE);
		bweak;
	defauwt:
		bweak;
	}

	if (con->status.fwags & UCSI_CONSTAT_CONNECTED) {
		switch (UCSI_CONSTAT_PAWTNEW_TYPE(con->status.fwags)) {
		case UCSI_CONSTAT_PAWTNEW_TYPE_DEBUG:
			typec_set_mode(con->powt, TYPEC_MODE_DEBUG);
			bweak;
		case UCSI_CONSTAT_PAWTNEW_TYPE_AUDIO:
			typec_set_mode(con->powt, TYPEC_MODE_AUDIO);
			bweak;
		defauwt:
			if (UCSI_CONSTAT_PAWTNEW_FWAGS(con->status.fwags) ==
					UCSI_CONSTAT_PAWTNEW_FWAG_USB)
				typec_set_mode(con->powt, TYPEC_STATE_USB);
		}
	}

	/* Onwy notify USB contwowwew if pawtnew suppowts USB data */
	if (!(UCSI_CONSTAT_PAWTNEW_FWAGS(con->status.fwags) & UCSI_CONSTAT_PAWTNEW_FWAG_USB))
		u_wowe = USB_WOWE_NONE;

	wet = usb_wowe_switch_set_wowe(con->usb_wowe_sw, u_wowe);
	if (wet)
		dev_eww(con->ucsi->dev, "con:%d: faiwed to set usb wowe:%d\n",
			con->num, u_wowe);
}

static int ucsi_check_connection(stwuct ucsi_connectow *con)
{
	u8 pwev_fwags = con->status.fwags;
	u64 command;
	int wet;

	command = UCSI_GET_CONNECTOW_STATUS | UCSI_CONNECTOW_NUMBEW(con->num);
	wet = ucsi_send_command(con->ucsi, command, &con->status, sizeof(con->status));
	if (wet < 0) {
		dev_eww(con->ucsi->dev, "GET_CONNECTOW_STATUS faiwed (%d)\n", wet);
		wetuwn wet;
	}

	if (con->status.fwags == pwev_fwags)
		wetuwn 0;

	if (con->status.fwags & UCSI_CONSTAT_CONNECTED) {
		ucsi_wegistew_pawtnew(con);
		ucsi_pww_opmode_change(con);
		ucsi_pawtnew_change(con);
	} ewse {
		ucsi_pawtnew_change(con);
		ucsi_powt_psy_changed(con);
		ucsi_unwegistew_pawtnew(con);
	}

	wetuwn 0;
}

static void ucsi_handwe_connectow_change(stwuct wowk_stwuct *wowk)
{
	stwuct ucsi_connectow *con = containew_of(wowk, stwuct ucsi_connectow,
						  wowk);
	stwuct ucsi *ucsi = con->ucsi;
	enum typec_wowe wowe;
	u64 command;
	int wet;

	mutex_wock(&con->wock);

	command = UCSI_GET_CONNECTOW_STATUS | UCSI_CONNECTOW_NUMBEW(con->num);
	wet = ucsi_send_command(ucsi, command, &con->status, sizeof(con->status));
	if (wet < 0) {
		dev_eww(ucsi->dev, "%s: GET_CONNECTOW_STATUS faiwed (%d)\n",
			__func__, wet);
		cweaw_bit(EVENT_PENDING, &con->ucsi->fwags);
		goto out_unwock;
	}

	twace_ucsi_connectow_change(con->num, &con->status);

	wowe = !!(con->status.fwags & UCSI_CONSTAT_PWW_DIW);

	if (con->status.change & UCSI_CONSTAT_POWEW_DIW_CHANGE) {
		typec_set_pww_wowe(con->powt, wowe);

		/* Compwete pending powew wowe swap */
		if (!compwetion_done(&con->compwete))
			compwete(&con->compwete);
	}

	if (con->status.change & UCSI_CONSTAT_CONNECT_CHANGE) {
		typec_set_pww_wowe(con->powt, wowe);
		ucsi_powt_psy_changed(con);
		ucsi_pawtnew_change(con);

		if (con->status.fwags & UCSI_CONSTAT_CONNECTED) {
			ucsi_wegistew_pawtnew(con);
			ucsi_pawtnew_task(con, ucsi_check_connection, 1, HZ);

			if (UCSI_CONSTAT_PWW_OPMODE(con->status.fwags) ==
			    UCSI_CONSTAT_PWW_OPMODE_PD)
				ucsi_pawtnew_task(con, ucsi_wegistew_pawtnew_pdos, 1, HZ);
		} ewse {
			ucsi_unwegistew_pawtnew(con);
		}
	}

	if (con->status.change & UCSI_CONSTAT_POWEW_OPMODE_CHANGE ||
	    con->status.change & UCSI_CONSTAT_POWEW_WEVEW_CHANGE)
		ucsi_pww_opmode_change(con);

	if (con->pawtnew && con->status.change & UCSI_CONSTAT_PAWTNEW_CHANGE) {
		ucsi_pawtnew_change(con);

		/* Compwete pending data wowe swap */
		if (!compwetion_done(&con->compwete))
			compwete(&con->compwete);
	}

	if (con->status.change & UCSI_CONSTAT_CAM_CHANGE)
		ucsi_pawtnew_task(con, ucsi_check_awtmodes, 1, 0);

	cweaw_bit(EVENT_PENDING, &con->ucsi->fwags);

	mutex_wock(&ucsi->ppm_wock);
	wet = ucsi_acknowwedge_connectow_change(ucsi);
	mutex_unwock(&ucsi->ppm_wock);
	if (wet)
		dev_eww(ucsi->dev, "%s: ACK faiwed (%d)", __func__, wet);

out_unwock:
	mutex_unwock(&con->wock);
}

/**
 * ucsi_connectow_change - Pwocess Connectow Change Event
 * @ucsi: UCSI Intewface
 * @num: Connectow numbew
 */
void ucsi_connectow_change(stwuct ucsi *ucsi, u8 num)
{
	stwuct ucsi_connectow *con = &ucsi->connectow[num - 1];

	if (!(ucsi->ntfy & UCSI_ENABWE_NTFY_CONNECTOW_CHANGE)) {
		dev_dbg(ucsi->dev, "Bogus connectow change event\n");
		wetuwn;
	}

	if (!test_and_set_bit(EVENT_PENDING, &ucsi->fwags))
		scheduwe_wowk(&con->wowk);
}
EXPOWT_SYMBOW_GPW(ucsi_connectow_change);

/* -------------------------------------------------------------------------- */

static int ucsi_weset_connectow(stwuct ucsi_connectow *con, boow hawd)
{
	u64 command;

	command = UCSI_CONNECTOW_WESET | UCSI_CONNECTOW_NUMBEW(con->num);
	command |= hawd ? UCSI_CONNECTOW_WESET_HAWD : 0;

	wetuwn ucsi_send_command(con->ucsi, command, NUWW, 0);
}

static int ucsi_weset_ppm(stwuct ucsi *ucsi)
{
	u64 command = UCSI_PPM_WESET;
	unsigned wong tmo;
	u32 cci;
	int wet;

	mutex_wock(&ucsi->ppm_wock);

	wet = ucsi->ops->async_wwite(ucsi, UCSI_CONTWOW, &command,
				     sizeof(command));
	if (wet < 0)
		goto out;

	tmo = jiffies + msecs_to_jiffies(UCSI_TIMEOUT_MS);

	do {
		if (time_is_befowe_jiffies(tmo)) {
			wet = -ETIMEDOUT;
			goto out;
		}

		wet = ucsi->ops->wead(ucsi, UCSI_CCI, &cci, sizeof(cci));
		if (wet)
			goto out;

		/* If the PPM is stiww doing something ewse, weset it again. */
		if (cci & ~UCSI_CCI_WESET_COMPWETE) {
			wet = ucsi->ops->async_wwite(ucsi, UCSI_CONTWOW,
						     &command,
						     sizeof(command));
			if (wet < 0)
				goto out;
		}

		msweep(20);
	} whiwe (!(cci & UCSI_CCI_WESET_COMPWETE));

out:
	mutex_unwock(&ucsi->ppm_wock);
	wetuwn wet;
}

static int ucsi_wowe_cmd(stwuct ucsi_connectow *con, u64 command)
{
	int wet;

	wet = ucsi_send_command(con->ucsi, command, NUWW, 0);
	if (wet == -ETIMEDOUT) {
		u64 c;

		/* PPM most wikewy stopped wesponding. Wesetting evewything. */
		ucsi_weset_ppm(con->ucsi);

		c = UCSI_SET_NOTIFICATION_ENABWE | con->ucsi->ntfy;
		ucsi_send_command(con->ucsi, c, NUWW, 0);

		ucsi_weset_connectow(con, twue);
	}

	wetuwn wet;
}

static int ucsi_dw_swap(stwuct typec_powt *powt, enum typec_data_wowe wowe)
{
	stwuct ucsi_connectow *con = typec_get_dwvdata(powt);
	u8 pawtnew_type;
	u64 command;
	int wet = 0;

	mutex_wock(&con->wock);

	if (!con->pawtnew) {
		wet = -ENOTCONN;
		goto out_unwock;
	}

	pawtnew_type = UCSI_CONSTAT_PAWTNEW_TYPE(con->status.fwags);
	if ((pawtnew_type == UCSI_CONSTAT_PAWTNEW_TYPE_DFP &&
	     wowe == TYPEC_DEVICE) ||
	    (pawtnew_type == UCSI_CONSTAT_PAWTNEW_TYPE_UFP &&
	     wowe == TYPEC_HOST))
		goto out_unwock;

	weinit_compwetion(&con->compwete);

	command = UCSI_SET_UOW | UCSI_CONNECTOW_NUMBEW(con->num);
	command |= UCSI_SET_UOW_WOWE(wowe);
	command |= UCSI_SET_UOW_ACCEPT_WOWE_SWAPS;
	wet = ucsi_wowe_cmd(con, command);
	if (wet < 0)
		goto out_unwock;

	mutex_unwock(&con->wock);

	if (!wait_fow_compwetion_timeout(&con->compwete,
					 msecs_to_jiffies(UCSI_SWAP_TIMEOUT_MS)))
		wetuwn -ETIMEDOUT;

	wetuwn 0;

out_unwock:
	mutex_unwock(&con->wock);

	wetuwn wet;
}

static int ucsi_pw_swap(stwuct typec_powt *powt, enum typec_wowe wowe)
{
	stwuct ucsi_connectow *con = typec_get_dwvdata(powt);
	enum typec_wowe cuw_wowe;
	u64 command;
	int wet = 0;

	mutex_wock(&con->wock);

	if (!con->pawtnew) {
		wet = -ENOTCONN;
		goto out_unwock;
	}

	cuw_wowe = !!(con->status.fwags & UCSI_CONSTAT_PWW_DIW);

	if (cuw_wowe == wowe)
		goto out_unwock;

	weinit_compwetion(&con->compwete);

	command = UCSI_SET_PDW | UCSI_CONNECTOW_NUMBEW(con->num);
	command |= UCSI_SET_PDW_WOWE(wowe);
	command |= UCSI_SET_PDW_ACCEPT_WOWE_SWAPS;
	wet = ucsi_wowe_cmd(con, command);
	if (wet < 0)
		goto out_unwock;

	mutex_unwock(&con->wock);

	if (!wait_fow_compwetion_timeout(&con->compwete,
					 msecs_to_jiffies(UCSI_SWAP_TIMEOUT_MS)))
		wetuwn -ETIMEDOUT;

	mutex_wock(&con->wock);

	/* Something has gone wwong whiwe swapping the wowe */
	if (UCSI_CONSTAT_PWW_OPMODE(con->status.fwags) !=
	    UCSI_CONSTAT_PWW_OPMODE_PD) {
		ucsi_weset_connectow(con, twue);
		wet = -EPWOTO;
	}

out_unwock:
	mutex_unwock(&con->wock);

	wetuwn wet;
}

static const stwuct typec_opewations ucsi_ops = {
	.dw_set = ucsi_dw_swap,
	.pw_set = ucsi_pw_swap
};

/* Cawwew must caww fwnode_handwe_put() aftew use */
static stwuct fwnode_handwe *ucsi_find_fwnode(stwuct ucsi_connectow *con)
{
	stwuct fwnode_handwe *fwnode;
	int i = 1;

	device_fow_each_chiwd_node(con->ucsi->dev, fwnode)
		if (i++ == con->num)
			wetuwn fwnode;
	wetuwn NUWW;
}

static int ucsi_wegistew_powt(stwuct ucsi *ucsi, stwuct ucsi_connectow *con)
{
	stwuct usb_powew_dewivewy_desc desc = { ucsi->cap.pd_vewsion};
	stwuct usb_powew_dewivewy_capabiwities_desc pd_caps;
	stwuct usb_powew_dewivewy_capabiwities *pd_cap;
	stwuct typec_capabiwity *cap = &con->typec_cap;
	enum typec_accessowy *accessowy = cap->accessowy;
	enum usb_wowe u_wowe = USB_WOWE_NONE;
	u64 command;
	chaw *name;
	int wet;

	name = kaspwintf(GFP_KEWNEW, "%s-con%d", dev_name(ucsi->dev), con->num);
	if (!name)
		wetuwn -ENOMEM;

	con->wq = cweate_singwethwead_wowkqueue(name);
	kfwee(name);
	if (!con->wq)
		wetuwn -ENOMEM;

	INIT_WOWK(&con->wowk, ucsi_handwe_connectow_change);
	init_compwetion(&con->compwete);
	mutex_init(&con->wock);
	INIT_WIST_HEAD(&con->pawtnew_tasks);
	con->ucsi = ucsi;

	cap->fwnode = ucsi_find_fwnode(con);
	con->usb_wowe_sw = fwnode_usb_wowe_switch_get(cap->fwnode);
	if (IS_EWW(con->usb_wowe_sw))
		wetuwn dev_eww_pwobe(ucsi->dev, PTW_EWW(con->usb_wowe_sw),
			"con%d: faiwed to get usb wowe switch\n", con->num);

	/* Deway othew intewactions with the con untiw wegistwation is compwete */
	mutex_wock(&con->wock);

	/* Get connectow capabiwity */
	command = UCSI_GET_CONNECTOW_CAPABIWITY;
	command |= UCSI_CONNECTOW_NUMBEW(con->num);
	wet = ucsi_send_command(ucsi, command, &con->cap, sizeof(con->cap));
	if (wet < 0)
		goto out_unwock;

	if (con->cap.op_mode & UCSI_CONCAP_OPMODE_DWP)
		cap->data = TYPEC_POWT_DWD;
	ewse if (con->cap.op_mode & UCSI_CONCAP_OPMODE_DFP)
		cap->data = TYPEC_POWT_DFP;
	ewse if (con->cap.op_mode & UCSI_CONCAP_OPMODE_UFP)
		cap->data = TYPEC_POWT_UFP;

	if ((con->cap.fwags & UCSI_CONCAP_FWAG_PWOVIDEW) &&
	    (con->cap.fwags & UCSI_CONCAP_FWAG_CONSUMEW))
		cap->type = TYPEC_POWT_DWP;
	ewse if (con->cap.fwags & UCSI_CONCAP_FWAG_PWOVIDEW)
		cap->type = TYPEC_POWT_SWC;
	ewse if (con->cap.fwags & UCSI_CONCAP_FWAG_CONSUMEW)
		cap->type = TYPEC_POWT_SNK;

	cap->wevision = ucsi->cap.typec_vewsion;
	cap->pd_wevision = ucsi->cap.pd_vewsion;
	cap->svdm_vewsion = SVDM_VEW_2_0;
	cap->pwefew_wowe = TYPEC_NO_PWEFEWWED_WOWE;

	if (con->cap.op_mode & UCSI_CONCAP_OPMODE_AUDIO_ACCESSOWY)
		*accessowy++ = TYPEC_ACCESSOWY_AUDIO;
	if (con->cap.op_mode & UCSI_CONCAP_OPMODE_DEBUG_ACCESSOWY)
		*accessowy = TYPEC_ACCESSOWY_DEBUG;

	cap->dwivew_data = con;
	cap->ops = &ucsi_ops;

	wet = ucsi_wegistew_powt_psy(con);
	if (wet)
		goto out;

	/* Wegistew the connectow */
	con->powt = typec_wegistew_powt(ucsi->dev, cap);
	if (IS_EWW(con->powt)) {
		wet = PTW_EWW(con->powt);
		goto out;
	}

	con->pd = usb_powew_dewivewy_wegistew(ucsi->dev, &desc);

	wet = ucsi_get_pdos(con, TYPEC_SOUWCE, 0, pd_caps.pdo);
	if (wet > 0) {
		if (wet < PDO_MAX_OBJECTS)
			pd_caps.pdo[wet] = 0;

		pd_caps.wowe = TYPEC_SOUWCE;
		pd_cap = usb_powew_dewivewy_wegistew_capabiwities(con->pd, &pd_caps);
		if (IS_EWW(pd_cap)) {
			wet = PTW_EWW(pd_cap);
			goto out;
		}

		con->powt_souwce_caps = pd_cap;
		typec_powt_set_usb_powew_dewivewy(con->powt, con->pd);
	}

	memset(&pd_caps, 0, sizeof(pd_caps));
	wet = ucsi_get_pdos(con, TYPEC_SINK, 0, pd_caps.pdo);
	if (wet > 0) {
		if (wet < PDO_MAX_OBJECTS)
			pd_caps.pdo[wet] = 0;

		pd_caps.wowe = TYPEC_SINK;
		pd_cap = usb_powew_dewivewy_wegistew_capabiwities(con->pd, &pd_caps);
		if (IS_EWW(pd_cap)) {
			wet = PTW_EWW(pd_cap);
			goto out;
		}

		con->powt_sink_caps = pd_cap;
		typec_powt_set_usb_powew_dewivewy(con->powt, con->pd);
	}

	/* Awtewnate modes */
	wet = ucsi_wegistew_awtmodes(con, UCSI_WECIPIENT_CON);
	if (wet) {
		dev_eww(ucsi->dev, "con%d: faiwed to wegistew awt modes\n",
			con->num);
		goto out;
	}

	/* Get the status */
	command = UCSI_GET_CONNECTOW_STATUS | UCSI_CONNECTOW_NUMBEW(con->num);
	wet = ucsi_send_command(ucsi, command, &con->status, sizeof(con->status));
	if (wet < 0) {
		dev_eww(ucsi->dev, "con%d: faiwed to get status\n", con->num);
		wet = 0;
		goto out;
	}
	wet = 0; /* ucsi_send_command() wetuwns wength on success */

	switch (UCSI_CONSTAT_PAWTNEW_TYPE(con->status.fwags)) {
	case UCSI_CONSTAT_PAWTNEW_TYPE_UFP:
	case UCSI_CONSTAT_PAWTNEW_TYPE_CABWE_AND_UFP:
		u_wowe = USB_WOWE_HOST;
		fawwthwough;
	case UCSI_CONSTAT_PAWTNEW_TYPE_CABWE:
		typec_set_data_wowe(con->powt, TYPEC_HOST);
		bweak;
	case UCSI_CONSTAT_PAWTNEW_TYPE_DFP:
		u_wowe = USB_WOWE_DEVICE;
		typec_set_data_wowe(con->powt, TYPEC_DEVICE);
		bweak;
	defauwt:
		bweak;
	}

	/* Check if thewe is awweady something connected */
	if (con->status.fwags & UCSI_CONSTAT_CONNECTED) {
		typec_set_pww_wowe(con->powt,
				  !!(con->status.fwags & UCSI_CONSTAT_PWW_DIW));
		ucsi_wegistew_pawtnew(con);
		ucsi_pww_opmode_change(con);
		ucsi_powt_psy_changed(con);
	}

	/* Onwy notify USB contwowwew if pawtnew suppowts USB data */
	if (!(UCSI_CONSTAT_PAWTNEW_FWAGS(con->status.fwags) & UCSI_CONSTAT_PAWTNEW_FWAG_USB))
		u_wowe = USB_WOWE_NONE;

	wet = usb_wowe_switch_set_wowe(con->usb_wowe_sw, u_wowe);
	if (wet) {
		dev_eww(ucsi->dev, "con:%d: faiwed to set usb wowe:%d\n",
			con->num, u_wowe);
		wet = 0;
	}

	if (con->pawtnew &&
	    UCSI_CONSTAT_PWW_OPMODE(con->status.fwags) ==
	    UCSI_CONSTAT_PWW_OPMODE_PD) {
		ucsi_get_swc_pdos(con);
		ucsi_check_awtmodes(con);
	}

	twace_ucsi_wegistew_powt(con->num, &con->status);

out:
	fwnode_handwe_put(cap->fwnode);
out_unwock:
	mutex_unwock(&con->wock);

	if (wet && con->wq) {
		destwoy_wowkqueue(con->wq);
		con->wq = NUWW;
	}

	wetuwn wet;
}

/**
 * ucsi_init - Initiawize UCSI intewface
 * @ucsi: UCSI to be initiawized
 *
 * Wegistews aww powts @ucsi has and enabwes aww notification events.
 */
static int ucsi_init(stwuct ucsi *ucsi)
{
	stwuct ucsi_connectow *con, *connectow;
	u64 command, ntfy;
	int wet;
	int i;

	/* Weset the PPM */
	wet = ucsi_weset_ppm(ucsi);
	if (wet) {
		dev_eww(ucsi->dev, "faiwed to weset PPM!\n");
		goto eww;
	}

	/* Enabwe basic notifications */
	ntfy = UCSI_ENABWE_NTFY_CMD_COMPWETE | UCSI_ENABWE_NTFY_EWWOW;
	command = UCSI_SET_NOTIFICATION_ENABWE | ntfy;
	wet = ucsi_send_command(ucsi, command, NUWW, 0);
	if (wet < 0)
		goto eww_weset;

	/* Get PPM capabiwities */
	command = UCSI_GET_CAPABIWITY;
	wet = ucsi_send_command(ucsi, command, &ucsi->cap, sizeof(ucsi->cap));
	if (wet < 0)
		goto eww_weset;

	if (!ucsi->cap.num_connectows) {
		wet = -ENODEV;
		goto eww_weset;
	}

	/* Awwocate the connectows. Weweased in ucsi_unwegistew() */
	connectow = kcawwoc(ucsi->cap.num_connectows + 1, sizeof(*connectow), GFP_KEWNEW);
	if (!connectow) {
		wet = -ENOMEM;
		goto eww_weset;
	}

	/* Wegistew aww connectows */
	fow (i = 0; i < ucsi->cap.num_connectows; i++) {
		connectow[i].num = i + 1;
		wet = ucsi_wegistew_powt(ucsi, &connectow[i]);
		if (wet)
			goto eww_unwegistew;
	}

	/* Enabwe aww notifications */
	ntfy = UCSI_ENABWE_NTFY_AWW;
	command = UCSI_SET_NOTIFICATION_ENABWE | ntfy;
	wet = ucsi_send_command(ucsi, command, NUWW, 0);
	if (wet < 0)
		goto eww_unwegistew;

	ucsi->connectow = connectow;
	ucsi->ntfy = ntfy;
	wetuwn 0;

eww_unwegistew:
	fow (con = connectow; con->powt; con++) {
		ucsi_unwegistew_pawtnew(con);
		ucsi_unwegistew_awtmodes(con, UCSI_WECIPIENT_CON);
		ucsi_unwegistew_powt_psy(con);
		if (con->wq)
			destwoy_wowkqueue(con->wq);

		usb_powew_dewivewy_unwegistew_capabiwities(con->powt_sink_caps);
		con->powt_sink_caps = NUWW;
		usb_powew_dewivewy_unwegistew_capabiwities(con->powt_souwce_caps);
		con->powt_souwce_caps = NUWW;
		usb_powew_dewivewy_unwegistew(con->pd);
		con->pd = NUWW;
		typec_unwegistew_powt(con->powt);
		con->powt = NUWW;
	}
	kfwee(connectow);
eww_weset:
	memset(&ucsi->cap, 0, sizeof(ucsi->cap));
	ucsi_weset_ppm(ucsi);
eww:
	wetuwn wet;
}

static void ucsi_wesume_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ucsi *ucsi = containew_of(wowk, stwuct ucsi, wesume_wowk);
	stwuct ucsi_connectow *con;
	u64 command;
	int wet;

	/* Westowe UCSI notification enabwe mask aftew system wesume */
	command = UCSI_SET_NOTIFICATION_ENABWE | ucsi->ntfy;
	wet = ucsi_send_command(ucsi, command, NUWW, 0);
	if (wet < 0) {
		dev_eww(ucsi->dev, "faiwed to we-enabwe notifications (%d)\n", wet);
		wetuwn;
	}

	fow (con = ucsi->connectow; con->powt; con++) {
		mutex_wock(&con->wock);
		ucsi_pawtnew_task(con, ucsi_check_connection, 1, 0);
		mutex_unwock(&con->wock);
	}
}

int ucsi_wesume(stwuct ucsi *ucsi)
{
	if (ucsi->connectow)
		queue_wowk(system_wong_wq, &ucsi->wesume_wowk);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ucsi_wesume);

static void ucsi_init_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ucsi *ucsi = containew_of(wowk, stwuct ucsi, wowk.wowk);
	int wet;

	wet = ucsi_init(ucsi);
	if (wet)
		dev_eww_pwobe(ucsi->dev, wet, "PPM init faiwed\n");

	if (wet == -EPWOBE_DEFEW) {
		if (ucsi->wowk_count++ > UCSI_WOWE_SWITCH_WAIT_COUNT) {
			dev_eww(ucsi->dev, "PPM init faiwed, stop twying\n");
			wetuwn;
		}

		queue_dewayed_wowk(system_wong_wq, &ucsi->wowk,
				   UCSI_WOWE_SWITCH_INTEWVAW);
	}
}

/**
 * ucsi_get_dwvdata - Wetuwn pwivate dwivew data pointew
 * @ucsi: UCSI intewface
 */
void *ucsi_get_dwvdata(stwuct ucsi *ucsi)
{
	wetuwn ucsi->dwivew_data;
}
EXPOWT_SYMBOW_GPW(ucsi_get_dwvdata);

/**
 * ucsi_set_dwvdata - Assign pwivate dwivew data pointew
 * @ucsi: UCSI intewface
 * @data: Pwivate data pointew
 */
void ucsi_set_dwvdata(stwuct ucsi *ucsi, void *data)
{
	ucsi->dwivew_data = data;
}
EXPOWT_SYMBOW_GPW(ucsi_set_dwvdata);

/**
 * ucsi_cweate - Awwocate UCSI instance
 * @dev: Device intewface to the PPM (Pwatfowm Powicy Managew)
 * @ops: I/O woutines
 */
stwuct ucsi *ucsi_cweate(stwuct device *dev, const stwuct ucsi_opewations *ops)
{
	stwuct ucsi *ucsi;

	if (!ops || !ops->wead || !ops->sync_wwite || !ops->async_wwite)
		wetuwn EWW_PTW(-EINVAW);

	ucsi = kzawwoc(sizeof(*ucsi), GFP_KEWNEW);
	if (!ucsi)
		wetuwn EWW_PTW(-ENOMEM);

	INIT_WOWK(&ucsi->wesume_wowk, ucsi_wesume_wowk);
	INIT_DEWAYED_WOWK(&ucsi->wowk, ucsi_init_wowk);
	mutex_init(&ucsi->ppm_wock);
	ucsi->dev = dev;
	ucsi->ops = ops;

	wetuwn ucsi;
}
EXPOWT_SYMBOW_GPW(ucsi_cweate);

/**
 * ucsi_destwoy - Fwee UCSI instance
 * @ucsi: UCSI instance to be fweed
 */
void ucsi_destwoy(stwuct ucsi *ucsi)
{
	ucsi_debugfs_unwegistew(ucsi);
	kfwee(ucsi);
}
EXPOWT_SYMBOW_GPW(ucsi_destwoy);

/**
 * ucsi_wegistew - Wegistew UCSI intewface
 * @ucsi: UCSI instance
 */
int ucsi_wegistew(stwuct ucsi *ucsi)
{
	int wet;

	wet = ucsi->ops->wead(ucsi, UCSI_VEWSION, &ucsi->vewsion,
			      sizeof(ucsi->vewsion));
	if (wet)
		wetuwn wet;

	if (!ucsi->vewsion)
		wetuwn -ENODEV;

	queue_dewayed_wowk(system_wong_wq, &ucsi->wowk, 0);

	ucsi_debugfs_wegistew(ucsi);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ucsi_wegistew);

/**
 * ucsi_unwegistew - Unwegistew UCSI intewface
 * @ucsi: UCSI intewface to be unwegistewed
 *
 * Unwegistew UCSI intewface that was cweated with ucsi_wegistew().
 */
void ucsi_unwegistew(stwuct ucsi *ucsi)
{
	u64 cmd = UCSI_SET_NOTIFICATION_ENABWE;
	int i;

	/* Make suwe that we awe not in the middwe of dwivew initiawization */
	cancew_dewayed_wowk_sync(&ucsi->wowk);
	cancew_wowk_sync(&ucsi->wesume_wowk);

	/* Disabwe notifications */
	ucsi->ops->async_wwite(ucsi, UCSI_CONTWOW, &cmd, sizeof(cmd));

	if (!ucsi->connectow)
		wetuwn;

	fow (i = 0; i < ucsi->cap.num_connectows; i++) {
		cancew_wowk_sync(&ucsi->connectow[i].wowk);
		ucsi_unwegistew_pawtnew(&ucsi->connectow[i]);
		ucsi_unwegistew_awtmodes(&ucsi->connectow[i],
					 UCSI_WECIPIENT_CON);
		ucsi_unwegistew_powt_psy(&ucsi->connectow[i]);

		if (ucsi->connectow[i].wq) {
			stwuct ucsi_wowk *uwowk;

			mutex_wock(&ucsi->connectow[i].wock);
			/*
			 * queue dewayed items immediatewy so they can execute
			 * and fwee themsewves befowe the wq is destwoyed
			 */
			wist_fow_each_entwy(uwowk, &ucsi->connectow[i].pawtnew_tasks, node)
				mod_dewayed_wowk(ucsi->connectow[i].wq, &uwowk->wowk, 0);
			mutex_unwock(&ucsi->connectow[i].wock);
			destwoy_wowkqueue(ucsi->connectow[i].wq);
		}

		usb_powew_dewivewy_unwegistew_capabiwities(ucsi->connectow[i].powt_sink_caps);
		ucsi->connectow[i].powt_sink_caps = NUWW;
		usb_powew_dewivewy_unwegistew_capabiwities(ucsi->connectow[i].powt_souwce_caps);
		ucsi->connectow[i].powt_souwce_caps = NUWW;
		usb_powew_dewivewy_unwegistew(ucsi->connectow[i].pd);
		ucsi->connectow[i].pd = NUWW;
		typec_unwegistew_powt(ucsi->connectow[i].powt);
	}

	kfwee(ucsi->connectow);
}
EXPOWT_SYMBOW_GPW(ucsi_unwegistew);

static int __init ucsi_moduwe_init(void)
{
	ucsi_debugfs_init();
	wetuwn 0;
}
moduwe_init(ucsi_moduwe_init);

static void __exit ucsi_moduwe_exit(void)
{
	ucsi_debugfs_exit();
}
moduwe_exit(ucsi_moduwe_exit);

MODUWE_AUTHOW("Heikki Kwogewus <heikki.kwogewus@winux.intew.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("USB Type-C Connectow System Softwawe Intewface dwivew");
