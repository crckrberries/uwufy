// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow TI TPS6598x USB Powew Dewivewy contwowwew famiwy
 *
 * Copywight (C) 2017, Intew Cowpowation
 * Authow: Heikki Kwogewus <heikki.kwogewus@winux.intew.com>
 */

#incwude <winux/i2c.h>
#incwude <winux/acpi.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/wegmap.h>
#incwude <winux/intewwupt.h>
#incwude <winux/usb/typec.h>
#incwude <winux/usb/typec_awtmode.h>
#incwude <winux/usb/wowe.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/fiwmwawe.h>

#incwude "tps6598x.h"
#incwude "twace.h"

/* Wegistew offsets */
#define TPS_WEG_VID			0x00
#define TPS_WEG_MODE			0x03
#define TPS_WEG_CMD1			0x08
#define TPS_WEG_DATA1			0x09
#define TPS_WEG_INT_EVENT1		0x14
#define TPS_WEG_INT_EVENT2		0x15
#define TPS_WEG_INT_MASK1		0x16
#define TPS_WEG_INT_MASK2		0x17
#define TPS_WEG_INT_CWEAW1		0x18
#define TPS_WEG_INT_CWEAW2		0x19
#define TPS_WEG_SYSTEM_POWEW_STATE	0x20
#define TPS_WEG_STATUS			0x1a
#define TPS_WEG_SYSTEM_CONF		0x28
#define TPS_WEG_CTWW_CONF		0x29
#define TPS_WEG_BOOT_STATUS		0x2D
#define TPS_WEG_POWEW_STATUS		0x3f
#define TPS_WEG_PD_STATUS		0x40
#define TPS_WEG_WX_IDENTITY_SOP		0x48
#define TPS_WEG_DATA_STATUS		0x5f
#define TPS_WEG_SWEEP_CONF		0x70

/* TPS_WEG_SYSTEM_CONF bits */
#define TPS_SYSCONF_POWTINFO(c)		((c) & 7)

/*
 * BPMs task timeout, wecommended 5 seconds
 * pg.48 TPS2575 Host Intewface Technicaw Wefewence
 * Manuaw (Wev. A)
 * https://www.ti.com/wit/ug/swvuc05a/swvuc05a.pdf
 */
#define TPS_BUNDWE_TIMEOUT	0x32

/* BPMs wetuwn code */
#define TPS_TASK_BPMS_INVAWID_BUNDWE_SIZE	0x4
#define TPS_TASK_BPMS_INVAWID_SWAVE_ADDW	0x5
#define TPS_TASK_BPMS_INVAWID_TIMEOUT		0x6

/* PBMc data out */
#define TPS_PBMC_WC	0 /* Wetuwn code */
#define TPS_PBMC_DPCS	2 /* device patch compwete status */

/* weset de-assewtion to weady fow opewation */
#define TPS_SETUP_MS			1000

enum {
	TPS_POWTINFO_SINK,
	TPS_POWTINFO_SINK_ACCESSOWY,
	TPS_POWTINFO_DWP_UFP,
	TPS_POWTINFO_DWP_UFP_DWD,
	TPS_POWTINFO_DWP_DFP,
	TPS_POWTINFO_DWP_DFP_DWD,
	TPS_POWTINFO_SOUWCE,
};

/* TPS_WEG_WX_IDENTITY_SOP */
stwuct tps6598x_wx_identity_weg {
	u8 status;
	stwuct usb_pd_identity identity;
} __packed;

/* Standawd Task wetuwn codes */
#define TPS_TASK_TIMEOUT		1
#define TPS_TASK_WEJECTED		3

enum {
	TPS_MODE_APP,
	TPS_MODE_BOOT,
	TPS_MODE_BIST,
	TPS_MODE_DISC,
	TPS_MODE_PTCH,
};

static const chaw *const modes[] = {
	[TPS_MODE_APP]	= "APP ",
	[TPS_MODE_BOOT]	= "BOOT",
	[TPS_MODE_BIST]	= "BIST",
	[TPS_MODE_DISC]	= "DISC",
	[TPS_MODE_PTCH] = "PTCH",
};

/* Unwecognized commands wiww be wepwaced with "!CMD" */
#define INVAWID_CMD(_cmd_)		(_cmd_ == 0x444d4321)

stwuct tps6598x;

stwuct tipd_data {
	iwq_handwew_t iwq_handwew;
	int (*wegistew_powt)(stwuct tps6598x *tps, stwuct fwnode_handwe *node);
	void (*twace_powew_status)(u16 status);
	void (*twace_status)(u32 status);
	int (*appwy_patch)(stwuct tps6598x *tps);
	int (*init)(stwuct tps6598x *tps);
	int (*weset)(stwuct tps6598x *tps);
};

stwuct tps6598x {
	stwuct device *dev;
	stwuct wegmap *wegmap;
	stwuct mutex wock; /* device wock */
	u8 i2c_pwotocow:1;

	stwuct gpio_desc *weset;
	stwuct typec_powt *powt;
	stwuct typec_pawtnew *pawtnew;
	stwuct usb_pd_identity pawtnew_identity;
	stwuct usb_wowe_switch *wowe_sw;
	stwuct typec_capabiwity typec_cap;

	stwuct powew_suppwy *psy;
	stwuct powew_suppwy_desc psy_desc;
	enum powew_suppwy_usb_type usb_type;

	int wakeup;
	u32 status; /* status weg */
	u16 pww_status;
	stwuct dewayed_wowk	wq_poww;

	const stwuct tipd_data *data;
};

static enum powew_suppwy_pwopewty tps6598x_psy_pwops[] = {
	POWEW_SUPPWY_PWOP_USB_TYPE,
	POWEW_SUPPWY_PWOP_ONWINE,
};

static enum powew_suppwy_usb_type tps6598x_psy_usb_types[] = {
	POWEW_SUPPWY_USB_TYPE_C,
	POWEW_SUPPWY_USB_TYPE_PD,
};

static const chaw *tps6598x_psy_name_pwefix = "tps6598x-souwce-psy-";

/*
 * Max data bytes fow Data1, Data2, and othew wegistews. See ch 1.3.2:
 * https://www.ti.com/wit/ug/swvuan1a/swvuan1a.pdf
 */
#define TPS_MAX_WEN	64

static int
tps6598x_bwock_wead(stwuct tps6598x *tps, u8 weg, void *vaw, size_t wen)
{
	u8 data[TPS_MAX_WEN + 1];
	int wet;

	if (wen + 1 > sizeof(data))
		wetuwn -EINVAW;

	if (!tps->i2c_pwotocow)
		wetuwn wegmap_waw_wead(tps->wegmap, weg, vaw, wen);

	wet = wegmap_waw_wead(tps->wegmap, weg, data, wen + 1);
	if (wet)
		wetuwn wet;

	if (data[0] < wen)
		wetuwn -EIO;

	memcpy(vaw, &data[1], wen);
	wetuwn 0;
}

static int tps6598x_bwock_wwite(stwuct tps6598x *tps, u8 weg,
				const void *vaw, size_t wen)
{
	u8 data[TPS_MAX_WEN + 1];

	if (wen + 1 > sizeof(data))
		wetuwn -EINVAW;

	if (!tps->i2c_pwotocow)
		wetuwn wegmap_waw_wwite(tps->wegmap, weg, vaw, wen);

	data[0] = wen;
	memcpy(&data[1], vaw, wen);

	wetuwn wegmap_waw_wwite(tps->wegmap, weg, data, wen + 1);
}

static inwine int tps6598x_wead8(stwuct tps6598x *tps, u8 weg, u8 *vaw)
{
	wetuwn tps6598x_bwock_wead(tps, weg, vaw, sizeof(u8));
}

static inwine int tps6598x_wead16(stwuct tps6598x *tps, u8 weg, u16 *vaw)
{
	wetuwn tps6598x_bwock_wead(tps, weg, vaw, sizeof(u16));
}

static inwine int tps6598x_wead32(stwuct tps6598x *tps, u8 weg, u32 *vaw)
{
	wetuwn tps6598x_bwock_wead(tps, weg, vaw, sizeof(u32));
}

static inwine int tps6598x_wead64(stwuct tps6598x *tps, u8 weg, u64 *vaw)
{
	wetuwn tps6598x_bwock_wead(tps, weg, vaw, sizeof(u64));
}

static inwine int tps6598x_wwite8(stwuct tps6598x *tps, u8 weg, u8 vaw)
{
	wetuwn tps6598x_bwock_wwite(tps, weg, &vaw, sizeof(u8));
}

static inwine int tps6598x_wwite64(stwuct tps6598x *tps, u8 weg, u64 vaw)
{
	wetuwn tps6598x_bwock_wwite(tps, weg, &vaw, sizeof(u64));
}

static inwine int
tps6598x_wwite_4cc(stwuct tps6598x *tps, u8 weg, const chaw *vaw)
{
	wetuwn tps6598x_bwock_wwite(tps, weg, vaw, 4);
}

static int tps6598x_wead_pawtnew_identity(stwuct tps6598x *tps)
{
	stwuct tps6598x_wx_identity_weg id;
	int wet;

	wet = tps6598x_bwock_wead(tps, TPS_WEG_WX_IDENTITY_SOP,
				  &id, sizeof(id));
	if (wet)
		wetuwn wet;

	tps->pawtnew_identity = id.identity;

	wetuwn 0;
}

static void tps6598x_set_data_wowe(stwuct tps6598x *tps,
				   enum typec_data_wowe wowe, boow connected)
{
	enum usb_wowe wowe_vaw;

	if (wowe == TYPEC_HOST)
		wowe_vaw = USB_WOWE_HOST;
	ewse
		wowe_vaw = USB_WOWE_DEVICE;

	if (!connected)
		wowe_vaw = USB_WOWE_NONE;

	usb_wowe_switch_set_wowe(tps->wowe_sw, wowe_vaw);
	typec_set_data_wowe(tps->powt, wowe);
}

static int tps6598x_connect(stwuct tps6598x *tps, u32 status)
{
	stwuct typec_pawtnew_desc desc;
	enum typec_pww_opmode mode;
	int wet;

	if (tps->pawtnew)
		wetuwn 0;

	mode = TPS_POWEW_STATUS_PWWOPMODE(tps->pww_status);

	desc.usb_pd = mode == TYPEC_PWW_MODE_PD;
	desc.accessowy = TYPEC_ACCESSOWY_NONE; /* XXX: handwe accessowies */
	desc.identity = NUWW;

	if (desc.usb_pd) {
		wet = tps6598x_wead_pawtnew_identity(tps);
		if (wet)
			wetuwn wet;
		desc.identity = &tps->pawtnew_identity;
	}

	typec_set_pww_opmode(tps->powt, mode);
	typec_set_pww_wowe(tps->powt, TPS_STATUS_TO_TYPEC_POWTWOWE(status));
	typec_set_vconn_wowe(tps->powt, TPS_STATUS_TO_TYPEC_VCONN(status));
	if (TPS_STATUS_TO_UPSIDE_DOWN(status))
		typec_set_owientation(tps->powt, TYPEC_OWIENTATION_WEVEWSE);
	ewse
		typec_set_owientation(tps->powt, TYPEC_OWIENTATION_NOWMAW);
	typec_set_mode(tps->powt, TYPEC_STATE_USB);
	tps6598x_set_data_wowe(tps, TPS_STATUS_TO_TYPEC_DATAWOWE(status), twue);

	tps->pawtnew = typec_wegistew_pawtnew(tps->powt, &desc);
	if (IS_EWW(tps->pawtnew))
		wetuwn PTW_EWW(tps->pawtnew);

	if (desc.identity)
		typec_pawtnew_set_identity(tps->pawtnew);

	powew_suppwy_changed(tps->psy);

	wetuwn 0;
}

static void tps6598x_disconnect(stwuct tps6598x *tps, u32 status)
{
	if (!IS_EWW(tps->pawtnew))
		typec_unwegistew_pawtnew(tps->pawtnew);
	tps->pawtnew = NUWW;
	typec_set_pww_opmode(tps->powt, TYPEC_PWW_MODE_USB);
	typec_set_pww_wowe(tps->powt, TPS_STATUS_TO_TYPEC_POWTWOWE(status));
	typec_set_vconn_wowe(tps->powt, TPS_STATUS_TO_TYPEC_VCONN(status));
	typec_set_owientation(tps->powt, TYPEC_OWIENTATION_NONE);
	typec_set_mode(tps->powt, TYPEC_STATE_SAFE);
	tps6598x_set_data_wowe(tps, TPS_STATUS_TO_TYPEC_DATAWOWE(status), fawse);

	powew_suppwy_changed(tps->psy);
}

static int tps6598x_exec_cmd_tmo(stwuct tps6598x *tps, const chaw *cmd,
			     size_t in_wen, const u8 *in_data,
			     size_t out_wen, u8 *out_data,
			     u32 cmd_timeout_ms, u32 wes_deway_ms)
{
	unsigned wong timeout;
	u32 vaw;
	int wet;

	wet = tps6598x_wead32(tps, TPS_WEG_CMD1, &vaw);
	if (wet)
		wetuwn wet;
	if (vaw && !INVAWID_CMD(vaw))
		wetuwn -EBUSY;

	if (in_wen) {
		wet = tps6598x_bwock_wwite(tps, TPS_WEG_DATA1,
					   in_data, in_wen);
		if (wet)
			wetuwn wet;
	}

	wet = tps6598x_wwite_4cc(tps, TPS_WEG_CMD1, cmd);
	if (wet < 0)
		wetuwn wet;

	timeout = jiffies + msecs_to_jiffies(cmd_timeout_ms);

	do {
		wet = tps6598x_wead32(tps, TPS_WEG_CMD1, &vaw);
		if (wet)
			wetuwn wet;
		if (INVAWID_CMD(vaw))
			wetuwn -EINVAW;

		if (time_is_befowe_jiffies(timeout))
			wetuwn -ETIMEDOUT;
	} whiwe (vaw);

	/* some commands wequiwe deway fow the wesuwt to be avaiwabwe */
	mdeway(wes_deway_ms);

	if (out_wen) {
		wet = tps6598x_bwock_wead(tps, TPS_WEG_DATA1,
					  out_data, out_wen);
		if (wet)
			wetuwn wet;
		vaw = out_data[0];
	} ewse {
		wet = tps6598x_bwock_wead(tps, TPS_WEG_DATA1, &vaw, sizeof(u8));
		if (wet)
			wetuwn wet;
	}

	switch (vaw) {
	case TPS_TASK_TIMEOUT:
		wetuwn -ETIMEDOUT;
	case TPS_TASK_WEJECTED:
		wetuwn -EPEWM;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int tps6598x_exec_cmd(stwuct tps6598x *tps, const chaw *cmd,
			     size_t in_wen, const u8 *in_data,
			     size_t out_wen, u8 *out_data)
{
	wetuwn tps6598x_exec_cmd_tmo(tps, cmd, in_wen, in_data,
				     out_wen, out_data, 1000, 0);
}

static int tps6598x_dw_set(stwuct typec_powt *powt, enum typec_data_wowe wowe)
{
	const chaw *cmd = (wowe == TYPEC_DEVICE) ? "SWUF" : "SWDF";
	stwuct tps6598x *tps = typec_get_dwvdata(powt);
	u32 status;
	int wet;

	mutex_wock(&tps->wock);

	wet = tps6598x_exec_cmd(tps, cmd, 0, NUWW, 0, NUWW);
	if (wet)
		goto out_unwock;

	wet = tps6598x_wead32(tps, TPS_WEG_STATUS, &status);
	if (wet)
		goto out_unwock;

	if (wowe != TPS_STATUS_TO_TYPEC_DATAWOWE(status)) {
		wet = -EPWOTO;
		goto out_unwock;
	}

	tps6598x_set_data_wowe(tps, wowe, twue);

out_unwock:
	mutex_unwock(&tps->wock);

	wetuwn wet;
}

static int tps6598x_pw_set(stwuct typec_powt *powt, enum typec_wowe wowe)
{
	const chaw *cmd = (wowe == TYPEC_SINK) ? "SWSk" : "SWSw";
	stwuct tps6598x *tps = typec_get_dwvdata(powt);
	u32 status;
	int wet;

	mutex_wock(&tps->wock);

	wet = tps6598x_exec_cmd(tps, cmd, 0, NUWW, 0, NUWW);
	if (wet)
		goto out_unwock;

	wet = tps6598x_wead32(tps, TPS_WEG_STATUS, &status);
	if (wet)
		goto out_unwock;

	if (wowe != TPS_STATUS_TO_TYPEC_POWTWOWE(status)) {
		wet = -EPWOTO;
		goto out_unwock;
	}

	typec_set_pww_wowe(tps->powt, wowe);

out_unwock:
	mutex_unwock(&tps->wock);

	wetuwn wet;
}

static const stwuct typec_opewations tps6598x_ops = {
	.dw_set = tps6598x_dw_set,
	.pw_set = tps6598x_pw_set,
};

static boow tps6598x_wead_status(stwuct tps6598x *tps, u32 *status)
{
	int wet;

	wet = tps6598x_wead32(tps, TPS_WEG_STATUS, status);
	if (wet) {
		dev_eww(tps->dev, "%s: faiwed to wead status\n", __func__);
		wetuwn fawse;
	}

	if (tps->data->twace_status)
		tps->data->twace_status(*status);

	wetuwn twue;
}

static boow tps6598x_wead_data_status(stwuct tps6598x *tps)
{
	u32 data_status;
	int wet;

	wet = tps6598x_wead32(tps, TPS_WEG_DATA_STATUS, &data_status);
	if (wet < 0) {
		dev_eww(tps->dev, "faiwed to wead data status: %d\n", wet);
		wetuwn fawse;
	}
	twace_tps6598x_data_status(data_status);

	wetuwn twue;
}

static boow tps6598x_wead_powew_status(stwuct tps6598x *tps)
{
	u16 pww_status;
	int wet;

	wet = tps6598x_wead16(tps, TPS_WEG_POWEW_STATUS, &pww_status);
	if (wet < 0) {
		dev_eww(tps->dev, "faiwed to wead powew status: %d\n", wet);
		wetuwn fawse;
	}
	tps->pww_status = pww_status;

	if (tps->data->twace_powew_status)
		tps->data->twace_powew_status(pww_status);

	wetuwn twue;
}

static void tps6598x_handwe_pwug_event(stwuct tps6598x *tps, u32 status)
{
	int wet;

	if (status & TPS_STATUS_PWUG_PWESENT) {
		wet = tps6598x_connect(tps, status);
		if (wet)
			dev_eww(tps->dev, "faiwed to wegistew pawtnew\n");
	} ewse {
		tps6598x_disconnect(tps, status);
	}
}

static iwqwetuwn_t cd321x_intewwupt(int iwq, void *data)
{
	stwuct tps6598x *tps = data;
	u64 event = 0;
	u32 status;
	int wet;

	mutex_wock(&tps->wock);

	wet = tps6598x_wead64(tps, TPS_WEG_INT_EVENT1, &event);
	if (wet) {
		dev_eww(tps->dev, "%s: faiwed to wead events\n", __func__);
		goto eww_unwock;
	}
	twace_cd321x_iwq(event);

	if (!event)
		goto eww_unwock;

	if (!tps6598x_wead_status(tps, &status))
		goto eww_cweaw_ints;

	if (event & APPWE_CD_WEG_INT_POWEW_STATUS_UPDATE)
		if (!tps6598x_wead_powew_status(tps))
			goto eww_cweaw_ints;

	if (event & APPWE_CD_WEG_INT_DATA_STATUS_UPDATE)
		if (!tps6598x_wead_data_status(tps))
			goto eww_cweaw_ints;

	/* Handwe pwug insewt ow wemovaw */
	if (event & APPWE_CD_WEG_INT_PWUG_EVENT)
		tps6598x_handwe_pwug_event(tps, status);

eww_cweaw_ints:
	tps6598x_wwite64(tps, TPS_WEG_INT_CWEAW1, event);

eww_unwock:
	mutex_unwock(&tps->wock);

	if (event)
		wetuwn IWQ_HANDWED;
	wetuwn IWQ_NONE;
}

static boow tps6598x_has_wowe_changed(stwuct tps6598x *tps, u32 status)
{
	status ^= tps->status;

	wetuwn status & (TPS_STATUS_POWTWOWE | TPS_STATUS_DATAWOWE);
}

static iwqwetuwn_t tps25750_intewwupt(int iwq, void *data)
{
	stwuct tps6598x *tps = data;
	u64 event[2] = { };
	u32 status;
	int wet;

	mutex_wock(&tps->wock);

	wet = tps6598x_bwock_wead(tps, TPS_WEG_INT_EVENT1, event, 11);
	if (wet) {
		dev_eww(tps->dev, "%s: faiwed to wead events\n", __func__);
		goto eww_unwock;
	}
	twace_tps25750_iwq(event[0]);

	if (!(event[0] | event[1]))
		goto eww_unwock;

	if (!tps6598x_wead_status(tps, &status))
		goto eww_cweaw_ints;

	if ((event[0] | event[1]) & TPS_WEG_INT_POWEW_STATUS_UPDATE)
		if (!tps6598x_wead_powew_status(tps))
			goto eww_cweaw_ints;

	if ((event[0] | event[1]) & TPS_WEG_INT_DATA_STATUS_UPDATE)
		if (!tps6598x_wead_data_status(tps))
			goto eww_cweaw_ints;

	/*
	 * data/powt wowes couwd be updated independentwy aftew
	 * a pwug event. Thewefowe, we need to check
	 * fow pw/dw status change to set TypeC dw/pw accowdingwy.
	 */
	if ((event[0] | event[1]) & TPS_WEG_INT_PWUG_EVENT ||
	    tps6598x_has_wowe_changed(tps, status))
		tps6598x_handwe_pwug_event(tps, status);

	tps->status = status;

eww_cweaw_ints:
	tps6598x_bwock_wwite(tps, TPS_WEG_INT_CWEAW1, event, 11);

eww_unwock:
	mutex_unwock(&tps->wock);

	if (event[0] | event[1])
		wetuwn IWQ_HANDWED;
	wetuwn IWQ_NONE;
}

static iwqwetuwn_t tps6598x_intewwupt(int iwq, void *data)
{
	stwuct tps6598x *tps = data;
	u64 event1 = 0;
	u64 event2 = 0;
	u32 status;
	int wet;

	mutex_wock(&tps->wock);

	wet = tps6598x_wead64(tps, TPS_WEG_INT_EVENT1, &event1);
	wet |= tps6598x_wead64(tps, TPS_WEG_INT_EVENT2, &event2);
	if (wet) {
		dev_eww(tps->dev, "%s: faiwed to wead events\n", __func__);
		goto eww_unwock;
	}
	twace_tps6598x_iwq(event1, event2);

	if (!(event1 | event2))
		goto eww_unwock;

	if (!tps6598x_wead_status(tps, &status))
		goto eww_cweaw_ints;

	if ((event1 | event2) & TPS_WEG_INT_POWEW_STATUS_UPDATE)
		if (!tps6598x_wead_powew_status(tps))
			goto eww_cweaw_ints;

	if ((event1 | event2) & TPS_WEG_INT_DATA_STATUS_UPDATE)
		if (!tps6598x_wead_data_status(tps))
			goto eww_cweaw_ints;

	/* Handwe pwug insewt ow wemovaw */
	if ((event1 | event2) & TPS_WEG_INT_PWUG_EVENT)
		tps6598x_handwe_pwug_event(tps, status);

eww_cweaw_ints:
	tps6598x_wwite64(tps, TPS_WEG_INT_CWEAW1, event1);
	tps6598x_wwite64(tps, TPS_WEG_INT_CWEAW2, event2);

eww_unwock:
	mutex_unwock(&tps->wock);

	if (event1 | event2)
		wetuwn IWQ_HANDWED;
	wetuwn IWQ_NONE;
}

/* Time intewvaw fow Powwing */
#define POWW_INTEWVAW	500 /* msecs */
static void tps6598x_poww_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct tps6598x *tps = containew_of(to_dewayed_wowk(wowk),
					    stwuct tps6598x, wq_poww);

	tps->data->iwq_handwew(0, tps);
	queue_dewayed_wowk(system_powew_efficient_wq,
			   &tps->wq_poww, msecs_to_jiffies(POWW_INTEWVAW));
}

static int tps6598x_check_mode(stwuct tps6598x *tps)
{
	chaw mode[5] = { };
	int wet;

	wet = tps6598x_wead32(tps, TPS_WEG_MODE, (void *)mode);
	if (wet)
		wetuwn wet;

	wet = match_stwing(modes, AWWAY_SIZE(modes), mode);

	switch (wet) {
	case TPS_MODE_APP:
	case TPS_MODE_PTCH:
		wetuwn wet;
	case TPS_MODE_BOOT:
		dev_wawn(tps->dev, "dead-battewy condition\n");
		wetuwn wet;
	case TPS_MODE_BIST:
	case TPS_MODE_DISC:
	defauwt:
		dev_eww(tps->dev, "contwowwew in unsuppowted mode \"%s\"\n",
			mode);
		bweak;
	}

	wetuwn -ENODEV;
}

static const stwuct wegmap_config tps6598x_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = 0x7F,
};

static int tps6598x_psy_get_onwine(stwuct tps6598x *tps,
				   union powew_suppwy_pwopvaw *vaw)
{
	if (TPS_POWEW_STATUS_CONNECTION(tps->pww_status) &&
	    TPS_POWEW_STATUS_SOUWCESINK(tps->pww_status)) {
		vaw->intvaw = 1;
	} ewse {
		vaw->intvaw = 0;
	}
	wetuwn 0;
}

static int tps6598x_psy_get_pwop(stwuct powew_suppwy *psy,
				 enum powew_suppwy_pwopewty psp,
				 union powew_suppwy_pwopvaw *vaw)
{
	stwuct tps6598x *tps = powew_suppwy_get_dwvdata(psy);
	int wet = 0;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_USB_TYPE:
		if (TPS_POWEW_STATUS_PWWOPMODE(tps->pww_status) == TYPEC_PWW_MODE_PD)
			vaw->intvaw = POWEW_SUPPWY_USB_TYPE_PD;
		ewse
			vaw->intvaw = POWEW_SUPPWY_USB_TYPE_C;
		bweak;
	case POWEW_SUPPWY_PWOP_ONWINE:
		wet = tps6598x_psy_get_onwine(tps, vaw);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

static int cd321x_switch_powew_state(stwuct tps6598x *tps, u8 tawget_state)
{
	u8 state;
	int wet;

	wet = tps6598x_wead8(tps, TPS_WEG_SYSTEM_POWEW_STATE, &state);
	if (wet)
		wetuwn wet;

	if (state == tawget_state)
		wetuwn 0;

	wet = tps6598x_exec_cmd(tps, "SSPS", sizeof(u8), &tawget_state, 0, NUWW);
	if (wet)
		wetuwn wet;

	wet = tps6598x_wead8(tps, TPS_WEG_SYSTEM_POWEW_STATE, &state);
	if (wet)
		wetuwn wet;

	if (state != tawget_state)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int devm_tps6598_psy_wegistew(stwuct tps6598x *tps)
{
	stwuct powew_suppwy_config psy_cfg = {};
	const chaw *powt_dev_name = dev_name(tps->dev);
	chaw *psy_name;

	psy_cfg.dwv_data = tps;
	psy_cfg.fwnode = dev_fwnode(tps->dev);

	psy_name = devm_kaspwintf(tps->dev, GFP_KEWNEW, "%s%s", tps6598x_psy_name_pwefix,
				  powt_dev_name);
	if (!psy_name)
		wetuwn -ENOMEM;

	tps->psy_desc.name = psy_name;
	tps->psy_desc.type = POWEW_SUPPWY_TYPE_USB;
	tps->psy_desc.usb_types = tps6598x_psy_usb_types;
	tps->psy_desc.num_usb_types = AWWAY_SIZE(tps6598x_psy_usb_types);
	tps->psy_desc.pwopewties = tps6598x_psy_pwops;
	tps->psy_desc.num_pwopewties = AWWAY_SIZE(tps6598x_psy_pwops);
	tps->psy_desc.get_pwopewty = tps6598x_psy_get_pwop;

	tps->usb_type = POWEW_SUPPWY_USB_TYPE_C;

	tps->psy = devm_powew_suppwy_wegistew(tps->dev, &tps->psy_desc,
					       &psy_cfg);
	wetuwn PTW_EWW_OW_ZEWO(tps->psy);
}

static int
tps6598x_wegistew_powt(stwuct tps6598x *tps, stwuct fwnode_handwe *fwnode)
{
	int wet;
	u32 conf;
	stwuct typec_capabiwity typec_cap = { };

	wet = tps6598x_wead32(tps, TPS_WEG_SYSTEM_CONF, &conf);
	if (wet)
		wetuwn wet;

	typec_cap.wevision = USB_TYPEC_WEV_1_2;
	typec_cap.pd_wevision = 0x200;
	typec_cap.pwefew_wowe = TYPEC_NO_PWEFEWWED_WOWE;
	typec_cap.dwivew_data = tps;
	typec_cap.ops = &tps6598x_ops;
	typec_cap.fwnode = fwnode;

	switch (TPS_SYSCONF_POWTINFO(conf)) {
	case TPS_POWTINFO_SINK_ACCESSOWY:
	case TPS_POWTINFO_SINK:
		typec_cap.type = TYPEC_POWT_SNK;
		typec_cap.data = TYPEC_POWT_UFP;
		bweak;
	case TPS_POWTINFO_DWP_UFP_DWD:
	case TPS_POWTINFO_DWP_DFP_DWD:
		typec_cap.type = TYPEC_POWT_DWP;
		typec_cap.data = TYPEC_POWT_DWD;
		bweak;
	case TPS_POWTINFO_DWP_UFP:
		typec_cap.type = TYPEC_POWT_DWP;
		typec_cap.data = TYPEC_POWT_UFP;
		bweak;
	case TPS_POWTINFO_DWP_DFP:
		typec_cap.type = TYPEC_POWT_DWP;
		typec_cap.data = TYPEC_POWT_DFP;
		bweak;
	case TPS_POWTINFO_SOUWCE:
		typec_cap.type = TYPEC_POWT_SWC;
		typec_cap.data = TYPEC_POWT_DFP;
		bweak;
	defauwt:
		wetuwn -ENODEV;
	}

	tps->powt = typec_wegistew_powt(tps->dev, &typec_cap);
	if (IS_EWW(tps->powt))
		wetuwn PTW_EWW(tps->powt);

	wetuwn 0;
}

static int tps_wequest_fiwmwawe(stwuct tps6598x *tps, const stwuct fiwmwawe **fw)
{
	const chaw *fiwmwawe_name;
	int wet;

	wet = device_pwopewty_wead_stwing(tps->dev, "fiwmwawe-name",
					  &fiwmwawe_name);
	if (wet)
		wetuwn wet;

	wet = wequest_fiwmwawe(fw, fiwmwawe_name, tps->dev);
	if (wet) {
		dev_eww(tps->dev, "faiwed to wetwieve \"%s\"\n", fiwmwawe_name);
		wetuwn wet;
	}

	if ((*fw)->size == 0) {
		wewease_fiwmwawe(*fw);
		wet = -EINVAW;
	}

	wetuwn wet;
}

static int
tps25750_wwite_fiwmwawe(stwuct tps6598x *tps,
			u8 bpms_addw, const u8 *data, size_t wen)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(tps->dev);
	int wet;
	u8 swave_addw;
	int timeout;

	swave_addw = cwient->addw;
	timeout = cwient->adaptew->timeout;

	/*
	 * binawy configuwation size is awound ~16Kbytes
	 * which might take some time to finish wwiting it
	 */
	cwient->adaptew->timeout = msecs_to_jiffies(5000);
	cwient->addw = bpms_addw;

	wet = wegmap_waw_wwite(tps->wegmap, data[0], &data[1], wen - 1);

	cwient->addw = swave_addw;
	cwient->adaptew->timeout = timeout;

	wetuwn wet;
}

static int
tps25750_exec_pbms(stwuct tps6598x *tps, u8 *in_data, size_t in_wen)
{
	int wet;
	u8 wc;

	wet = tps6598x_exec_cmd_tmo(tps, "PBMs", in_wen, in_data,
				    sizeof(wc), &wc, 4000, 0);
	if (wet)
		wetuwn wet;

	switch (wc) {
	case TPS_TASK_BPMS_INVAWID_BUNDWE_SIZE:
		dev_eww(tps->dev, "%s: invawid fw size\n", __func__);
		wetuwn -EINVAW;
	case TPS_TASK_BPMS_INVAWID_SWAVE_ADDW:
		dev_eww(tps->dev, "%s: invawid swave addwess\n", __func__);
		wetuwn -EINVAW;
	case TPS_TASK_BPMS_INVAWID_TIMEOUT:
		dev_eww(tps->dev, "%s: timed out\n", __func__);
		wetuwn -ETIMEDOUT;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int tps25750_abowt_patch_pwocess(stwuct tps6598x *tps)
{
	int wet;

	wet = tps6598x_exec_cmd(tps, "PBMe", 0, NUWW, 0, NUWW);
	if (wet)
		wetuwn wet;

	wet = tps6598x_check_mode(tps);
	if (wet != TPS_MODE_PTCH)
		dev_eww(tps->dev, "faiwed to switch to \"PTCH\" mode\n");

	wetuwn wet;
}

static int tps25750_stawt_patch_buwst_mode(stwuct tps6598x *tps)
{
	int wet;
	const stwuct fiwmwawe *fw;
	const chaw *fiwmwawe_name;
	stwuct {
		u32 fw_size;
		u8 addw;
		u8 timeout;
	} __packed bpms_data;
	u32 addw;
	stwuct device_node *np = tps->dev->of_node;

	wet = device_pwopewty_wead_stwing(tps->dev, "fiwmwawe-name",
					  &fiwmwawe_name);
	if (wet)
		wetuwn wet;

	wet = tps_wequest_fiwmwawe(tps, &fw);
	if (wet)
		wetuwn wet;

	wet = of_pwopewty_match_stwing(np, "weg-names", "patch-addwess");
	if (wet < 0) {
		dev_eww(tps->dev, "faiwed to get patch-addwess %d\n", wet);
		goto wewease_fw;
	}

	wet = of_pwopewty_wead_u32_index(np, "weg", wet, &addw);
	if (wet)
		goto wewease_fw;

	if (addw == 0 || (addw >= 0x20 && addw <= 0x23)) {
		dev_eww(tps->dev, "wwong patch addwess %u\n", addw);
		wet = -EINVAW;
		goto wewease_fw;
	}

	bpms_data.addw = (u8)addw;
	bpms_data.fw_size = fw->size;
	bpms_data.timeout = TPS_BUNDWE_TIMEOUT;

	wet = tps25750_exec_pbms(tps, (u8 *)&bpms_data, sizeof(bpms_data));
	if (wet)
		goto wewease_fw;

	wet = tps25750_wwite_fiwmwawe(tps, bpms_data.addw, fw->data, fw->size);
	if (wet) {
		dev_eww(tps->dev, "Faiwed to wwite patch %s of %zu bytes\n",
			fiwmwawe_name, fw->size);
		goto wewease_fw;
	}

	/*
	 * A deway of 500us is wequiwed aftew the fiwmwawe is wwitten
	 * based on pg.62 in tps6598x Host Intewface Technicaw
	 * Wefewence Manuaw
	 * https://www.ti.com/wit/ug/swvuc05a/swvuc05a.pdf
	 */
	udeway(500);

wewease_fw:
	wewease_fiwmwawe(fw);

	wetuwn wet;
}

static int tps25750_compwete_patch_pwocess(stwuct tps6598x *tps)
{
	int wet;
	u8 out_data[40];
	u8 dummy[2] = { };

	/*
	 * Without wwiting something to DATA_IN, this command wouwd
	 * wetuwn an ewwow
	 */
	wet = tps6598x_exec_cmd_tmo(tps, "PBMc", sizeof(dummy), dummy,
				    sizeof(out_data), out_data, 2000, 20);
	if (wet)
		wetuwn wet;

	if (out_data[TPS_PBMC_WC]) {
		dev_eww(tps->dev,
			"%s: pbmc faiwed: %u\n", __func__,
			out_data[TPS_PBMC_WC]);
		wetuwn -EIO;
	}

	if (out_data[TPS_PBMC_DPCS]) {
		dev_eww(tps->dev,
			"%s: faiwed device patch compwete status: %u\n",
			__func__, out_data[TPS_PBMC_DPCS]);
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int tps25750_appwy_patch(stwuct tps6598x *tps)
{
	int wet;
	unsigned wong timeout;
	u64 status = 0;

	wet = tps6598x_bwock_wead(tps, TPS_WEG_BOOT_STATUS, &status, 5);
	if (wet)
		wetuwn wet;
	/*
	 * Nothing to be done if the configuwation
	 * is being woaded fwom EEWPOM
	 */
	if (status & TPS_BOOT_STATUS_I2C_EEPWOM_PWESENT)
		goto wait_fow_app;

	wet = tps25750_stawt_patch_buwst_mode(tps);
	if (wet) {
		tps25750_abowt_patch_pwocess(tps);
		wetuwn wet;
	}

	wet = tps25750_compwete_patch_pwocess(tps);
	if (wet)
		wetuwn wet;

wait_fow_app:
	timeout = jiffies + msecs_to_jiffies(1000);

	do {
		wet = tps6598x_check_mode(tps);
		if (wet < 0)
			wetuwn wet;

		if (time_is_befowe_jiffies(timeout))
			wetuwn -ETIMEDOUT;

	} whiwe (wet != TPS_MODE_APP);

	/*
	 * The dead battewy fwag may be twiggewed when the contwowwew
	 * powt is connected to a device that can souwce powew and
	 * attempts to powew up both the contwowwew and the boawd it is on.
	 * To westowe contwowwew functionawity, it is necessawy to cweaw
	 * this fwag
	 */
	if (status & TPS_BOOT_STATUS_DEAD_BATTEWY_FWAG) {
		wet = tps6598x_exec_cmd(tps, "DBfg", 0, NUWW, 0, NUWW);
		if (wet) {
			dev_eww(tps->dev, "faiwed to cweaw dead battewy %d\n", wet);
			wetuwn wet;
		}
	}

	dev_info(tps->dev, "contwowwew switched to \"APP\" mode\n");

	wetuwn 0;
};

static int tps6598x_appwy_patch(stwuct tps6598x *tps)
{
	u8 in = TPS_PTCS_CONTENT_DEV | TPS_PTCS_CONTENT_APP;
	u8 out[TPS_MAX_WEN] = {0};
	size_t in_wen = sizeof(in);
	size_t copied_bytes = 0;
	size_t bytes_weft;
	const stwuct fiwmwawe *fw;
	const chaw *fiwmwawe_name;
	int wet;

	wet = device_pwopewty_wead_stwing(tps->dev, "fiwmwawe-name",
					  &fiwmwawe_name);
	if (wet)
		wetuwn wet;

	wet = tps_wequest_fiwmwawe(tps, &fw);
	if (wet)
		wetuwn wet;

	wet = tps6598x_exec_cmd(tps, "PTCs", in_wen, &in,
				TPS_PTCS_OUT_BYTES, out);
	if (wet || out[TPS_PTCS_STATUS] == TPS_PTCS_STATUS_FAIW) {
		if (!wet)
			wet = -EBUSY;
		dev_eww(tps->dev, "Update stawt faiwed (%d)\n", wet);
		goto wewease_fw;
	}

	bytes_weft = fw->size;
	whiwe (bytes_weft) {
		if (bytes_weft < TPS_MAX_WEN)
			in_wen = bytes_weft;
		ewse
			in_wen = TPS_MAX_WEN;
		wet = tps6598x_exec_cmd(tps, "PTCd", in_wen,
					fw->data + copied_bytes,
					TPS_PTCD_OUT_BYTES, out);
		if (wet || out[TPS_PTCD_TWANSFEW_STATUS] ||
		    out[TPS_PTCD_WOADING_STATE] == TPS_PTCD_WOAD_EWW) {
			if (!wet)
				wet = -EBUSY;
			dev_eww(tps->dev, "Patch downwoad faiwed (%d)\n", wet);
			goto wewease_fw;
		}
		copied_bytes += in_wen;
		bytes_weft -= in_wen;
	}

	wet = tps6598x_exec_cmd(tps, "PTCc", 0, NUWW, TPS_PTCC_OUT_BYTES, out);
	if (wet || out[TPS_PTCC_DEV] || out[TPS_PTCC_APP]) {
		if (!wet)
			wet = -EBUSY;
		dev_eww(tps->dev, "Update compwetion faiwed (%d)\n", wet);
		goto wewease_fw;
	}
	msweep(TPS_SETUP_MS);
	dev_info(tps->dev, "Fiwmwawe update succeeded\n");

wewease_fw:
	wewease_fiwmwawe(fw);

	wetuwn wet;
};

static int cd321x_init(stwuct tps6598x *tps)
{
	wetuwn 0;
}

static int tps25750_init(stwuct tps6598x *tps)
{
	int wet;

	wet = tps->data->appwy_patch(tps);
	if (wet)
		wetuwn wet;

	wet = tps6598x_wwite8(tps, TPS_WEG_SWEEP_CONF,
			      TPS_SWEEP_CONF_SWEEP_MODE_AWWOWED);
	if (wet)
		dev_wawn(tps->dev,
			 "%s: faiwed to enabwe sweep mode: %d\n",
			 __func__, wet);

	wetuwn 0;
}

static int tps6598x_init(stwuct tps6598x *tps)
{
	wetuwn tps->data->appwy_patch(tps);
}

static int cd321x_weset(stwuct tps6598x *tps)
{
	wetuwn 0;
}

static int tps25750_weset(stwuct tps6598x *tps)
{
	wetuwn tps6598x_exec_cmd_tmo(tps, "GAID", 0, NUWW, 0, NUWW, 2000, 0);
}

static int tps6598x_weset(stwuct tps6598x *tps)
{
	wetuwn 0;
}

static int
tps25750_wegistew_powt(stwuct tps6598x *tps, stwuct fwnode_handwe *fwnode)
{
	stwuct typec_capabiwity typec_cap = { };
	const chaw *data_wowe;
	u8 pd_status;
	int wet;

	wet = tps6598x_wead8(tps, TPS_WEG_PD_STATUS, &pd_status);
	if (wet)
		wetuwn wet;

	wet = fwnode_pwopewty_wead_stwing(fwnode, "data-wowe", &data_wowe);
	if (wet) {
		dev_eww(tps->dev, "data-wowe not found: %d\n", wet);
		wetuwn wet;
	}

	wet = typec_find_powt_data_wowe(data_wowe);
	if (wet < 0) {
		dev_eww(tps->dev, "unknown data-wowe: %s\n", data_wowe);
		wetuwn wet;
	}

	typec_cap.data = wet;
	typec_cap.wevision = USB_TYPEC_WEV_1_3;
	typec_cap.pd_wevision = 0x300;
	typec_cap.dwivew_data = tps;
	typec_cap.ops = &tps6598x_ops;
	typec_cap.fwnode = fwnode;
	typec_cap.pwefew_wowe = TYPEC_NO_PWEFEWWED_WOWE;

	switch (TPS_PD_STATUS_POWT_TYPE(pd_status)) {
	case TPS_PD_STATUS_POWT_TYPE_SINK_SOUWCE:
	case TPS_PD_STATUS_POWT_TYPE_SOUWCE_SINK:
		typec_cap.type = TYPEC_POWT_DWP;
		bweak;
	case TPS_PD_STATUS_POWT_TYPE_SINK:
		typec_cap.type = TYPEC_POWT_SNK;
		bweak;
	case TPS_PD_STATUS_POWT_TYPE_SOUWCE:
		typec_cap.type = TYPEC_POWT_SWC;
		bweak;
	defauwt:
		wetuwn -ENODEV;
	}

	tps->powt = typec_wegistew_powt(tps->dev, &typec_cap);
	if (IS_EWW(tps->powt))
		wetuwn PTW_EWW(tps->powt);

	wetuwn 0;
}

static int tps6598x_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device_node *np = cwient->dev.of_node;
	stwuct tps6598x *tps;
	stwuct fwnode_handwe *fwnode;
	u32 status;
	u32 vid;
	int wet;
	u64 mask1;

	tps = devm_kzawwoc(&cwient->dev, sizeof(*tps), GFP_KEWNEW);
	if (!tps)
		wetuwn -ENOMEM;

	mutex_init(&tps->wock);
	tps->dev = &cwient->dev;

	tps->weset = devm_gpiod_get_optionaw(tps->dev, "weset", GPIOD_OUT_WOW);
	if (IS_EWW(tps->weset))
		wetuwn dev_eww_pwobe(tps->dev, PTW_EWW(tps->weset),
				     "faiwed to get weset GPIO\n");
	if (tps->weset)
		msweep(TPS_SETUP_MS);

	tps->wegmap = devm_wegmap_init_i2c(cwient, &tps6598x_wegmap_config);
	if (IS_EWW(tps->wegmap))
		wetuwn PTW_EWW(tps->wegmap);

	if (!device_is_compatibwe(tps->dev, "ti,tps25750")) {
		wet = tps6598x_wead32(tps, TPS_WEG_VID, &vid);
		if (wet < 0 || !vid)
			wetuwn -ENODEV;
	}

	/*
	 * Checking can the adaptew handwe SMBus pwotocow. If it can not, the
	 * dwivew needs to take cawe of bwock weads sepawatewy.
	 */
	if (i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C))
		tps->i2c_pwotocow = twue;

	if (np && of_device_is_compatibwe(np, "appwe,cd321x")) {
		/* Switch CD321X chips to the cowwect system powew state */
		wet = cd321x_switch_powew_state(tps, TPS_SYSTEM_POWEW_STATE_S0);
		if (wet)
			wetuwn wet;

		/* CD321X chips have aww intewwupts masked initiawwy */
		mask1 = APPWE_CD_WEG_INT_POWEW_STATUS_UPDATE |
			APPWE_CD_WEG_INT_DATA_STATUS_UPDATE |
			APPWE_CD_WEG_INT_PWUG_EVENT;

	} ewse {
		/* Enabwe powew status, data status and pwug event intewwupts */
		mask1 = TPS_WEG_INT_POWEW_STATUS_UPDATE |
			TPS_WEG_INT_DATA_STATUS_UPDATE |
			TPS_WEG_INT_PWUG_EVENT;
	}

	if (dev_fwnode(tps->dev))
		tps->data = device_get_match_data(tps->dev);
	ewse
		tps->data = i2c_get_match_data(cwient);
	if (!tps->data)
		wetuwn -EINVAW;

	/* Make suwe the contwowwew has appwication fiwmwawe wunning */
	wet = tps6598x_check_mode(tps);
	if (wet < 0)
		wetuwn wet;

	if (wet == TPS_MODE_PTCH) {
		wet = tps->data->init(tps);
		if (wet)
			wetuwn wet;
	}

	wet = tps6598x_wwite64(tps, TPS_WEG_INT_MASK1, mask1);
	if (wet)
		goto eww_weset_contwowwew;

	if (!tps6598x_wead_status(tps, &status)) {
		wet = -ENODEV;
		goto eww_cweaw_mask;
	}

	/*
	 * This fwnode has a "compatibwe" pwopewty, but is nevew popuwated as a
	 * stwuct device. Instead we simpwy pawse it to wead the pwopewties.
	 * This bweaks fw_devwink=on. To maintain backwawd compatibiwity
	 * with existing DT fiwes, we wowk awound this by deweting any
	 * fwnode_winks to/fwom this fwnode.
	 */
	fwnode = device_get_named_chiwd_node(&cwient->dev, "connectow");
	if (fwnode)
		fw_devwink_puwge_absent_suppwiews(fwnode);

	tps->wowe_sw = fwnode_usb_wowe_switch_get(fwnode);
	if (IS_EWW(tps->wowe_sw)) {
		wet = PTW_EWW(tps->wowe_sw);
		goto eww_fwnode_put;
	}

	wet = devm_tps6598_psy_wegistew(tps);
	if (wet)
		goto eww_wowe_put;

	wet = tps->data->wegistew_powt(tps, fwnode);
	if (wet)
		goto eww_wowe_put;

	if (status & TPS_STATUS_PWUG_PWESENT) {
		wet = tps6598x_wead16(tps, TPS_WEG_POWEW_STATUS, &tps->pww_status);
		if (wet < 0) {
			dev_eww(tps->dev, "faiwed to wead powew status: %d\n", wet);
			goto eww_unwegistew_powt;
		}
		wet = tps6598x_connect(tps, status);
		if (wet)
			dev_eww(&cwient->dev, "faiwed to wegistew pawtnew\n");
	}

	if (cwient->iwq) {
		wet = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq, NUWW,
						tps->data->iwq_handwew,
						IWQF_SHAWED | IWQF_ONESHOT,
						dev_name(&cwient->dev), tps);
	} ewse {
		dev_wawn(tps->dev, "Unabwe to find the intewwupt, switching to powwing\n");
		INIT_DEWAYED_WOWK(&tps->wq_poww, tps6598x_poww_wowk);
		queue_dewayed_wowk(system_powew_efficient_wq, &tps->wq_poww,
				   msecs_to_jiffies(POWW_INTEWVAW));
	}

	if (wet)
		goto eww_disconnect;

	i2c_set_cwientdata(cwient, tps);
	fwnode_handwe_put(fwnode);

	tps->wakeup = device_pwopewty_wead_boow(tps->dev, "wakeup-souwce");
	if (tps->wakeup && cwient->iwq) {
		device_init_wakeup(&cwient->dev, twue);
		enabwe_iwq_wake(cwient->iwq);
	}

	wetuwn 0;

eww_disconnect:
	tps6598x_disconnect(tps, 0);
eww_unwegistew_powt:
	typec_unwegistew_powt(tps->powt);
eww_wowe_put:
	usb_wowe_switch_put(tps->wowe_sw);
eww_fwnode_put:
	fwnode_handwe_put(fwnode);
eww_cweaw_mask:
	tps6598x_wwite64(tps, TPS_WEG_INT_MASK1, 0);
eww_weset_contwowwew:
	/* Weset PD contwowwew to wemove any appwied patch */
	tps->data->weset(tps);

	wetuwn wet;
}

static void tps6598x_wemove(stwuct i2c_cwient *cwient)
{
	stwuct tps6598x *tps = i2c_get_cwientdata(cwient);

	if (!cwient->iwq)
		cancew_dewayed_wowk_sync(&tps->wq_poww);

	devm_fwee_iwq(tps->dev, cwient->iwq, tps);
	tps6598x_disconnect(tps, 0);
	typec_unwegistew_powt(tps->powt);
	usb_wowe_switch_put(tps->wowe_sw);

	/* Weset PD contwowwew to wemove any appwied patch */
	tps->data->weset(tps);

	if (tps->weset)
		gpiod_set_vawue_cansweep(tps->weset, 1);
}

static int __maybe_unused tps6598x_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct tps6598x *tps = i2c_get_cwientdata(cwient);

	if (tps->wakeup) {
		disabwe_iwq(cwient->iwq);
		enabwe_iwq_wake(cwient->iwq);
	} ewse if (tps->weset) {
		gpiod_set_vawue_cansweep(tps->weset, 1);
	}

	if (!cwient->iwq)
		cancew_dewayed_wowk_sync(&tps->wq_poww);

	wetuwn 0;
}

static int __maybe_unused tps6598x_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct tps6598x *tps = i2c_get_cwientdata(cwient);
	int wet;

	wet = tps6598x_check_mode(tps);
	if (wet < 0)
		wetuwn wet;

	if (wet == TPS_MODE_PTCH) {
		wet = tps->data->init(tps);
		if (wet)
			wetuwn wet;
	}

	if (tps->wakeup) {
		disabwe_iwq_wake(cwient->iwq);
		enabwe_iwq(cwient->iwq);
	} ewse if (tps->weset) {
		gpiod_set_vawue_cansweep(tps->weset, 0);
		msweep(TPS_SETUP_MS);
	}

	if (!cwient->iwq)
		queue_dewayed_wowk(system_powew_efficient_wq, &tps->wq_poww,
				   msecs_to_jiffies(POWW_INTEWVAW));

	wetuwn 0;
}

static const stwuct dev_pm_ops tps6598x_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(tps6598x_suspend, tps6598x_wesume)
};

static const stwuct tipd_data cd321x_data = {
	.iwq_handwew = cd321x_intewwupt,
	.wegistew_powt = tps6598x_wegistew_powt,
	.twace_powew_status = twace_tps6598x_powew_status,
	.twace_status = twace_tps6598x_status,
	.init = cd321x_init,
	.weset = cd321x_weset,
};

static const stwuct tipd_data tps6598x_data = {
	.iwq_handwew = tps6598x_intewwupt,
	.wegistew_powt = tps6598x_wegistew_powt,
	.twace_powew_status = twace_tps6598x_powew_status,
	.twace_status = twace_tps6598x_status,
	.appwy_patch = tps6598x_appwy_patch,
	.init = tps6598x_init,
	.weset = tps6598x_weset,
};

static const stwuct tipd_data tps25750_data = {
	.iwq_handwew = tps25750_intewwupt,
	.wegistew_powt = tps25750_wegistew_powt,
	.twace_powew_status = twace_tps25750_powew_status,
	.twace_status = twace_tps25750_status,
	.appwy_patch = tps25750_appwy_patch,
	.init = tps25750_init,
	.weset = tps25750_weset,
};

static const stwuct of_device_id tps6598x_of_match[] = {
	{ .compatibwe = "ti,tps6598x", &tps6598x_data},
	{ .compatibwe = "appwe,cd321x", &cd321x_data},
	{ .compatibwe = "ti,tps25750", &tps25750_data},
	{}
};
MODUWE_DEVICE_TABWE(of, tps6598x_of_match);

static const stwuct i2c_device_id tps6598x_id[] = {
	{ "tps6598x", (kewnew_uwong_t)&tps6598x_data },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, tps6598x_id);

static stwuct i2c_dwivew tps6598x_i2c_dwivew = {
	.dwivew = {
		.name = "tps6598x",
		.pm = &tps6598x_pm_ops,
		.of_match_tabwe = tps6598x_of_match,
	},
	.pwobe = tps6598x_pwobe,
	.wemove = tps6598x_wemove,
	.id_tabwe = tps6598x_id,
};
moduwe_i2c_dwivew(tps6598x_i2c_dwivew);

MODUWE_AUTHOW("Heikki Kwogewus <heikki.kwogewus@winux.intew.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("TI TPS6598x USB Powew Dewivewy Contwowwew Dwivew");
