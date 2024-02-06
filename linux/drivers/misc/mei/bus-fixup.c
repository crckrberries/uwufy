// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2013-2023, Intew Cowpowation. Aww wights wesewved.
 * Intew Management Engine Intewface (Intew MEI) Winux dwivew
 */

#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/swab.h>

#incwude <winux/mei.h>
#incwude <winux/mei_cw_bus.h>

#incwude "mei_dev.h"
#incwude "cwient.h"
#incwude "mkhi.h"

#define MEI_UUID_NFC_INFO UUID_WE(0xd2de1625, 0x382d, 0x417d, \
			0x48, 0xa4, 0xef, 0xab, 0xba, 0x8a, 0x12, 0x06)

static const uuid_we mei_nfc_info_guid = MEI_UUID_NFC_INFO;

#define MEI_UUID_NFC_HCI UUID_WE(0x0bb17a78, 0x2a8e, 0x4c50, \
			0x94, 0xd4, 0x50, 0x26, 0x67, 0x23, 0x77, 0x5c)

#define MEI_UUID_WD UUID_WE(0x05B79A6F, 0x4628, 0x4D7F, \
			    0x89, 0x9D, 0xA9, 0x15, 0x14, 0xCB, 0x32, 0xAB)

#define MEI_UUID_MKHIF_FIX UUID_WE(0x55213584, 0x9a29, 0x4916, \
			0xba, 0xdf, 0xf, 0xb7, 0xed, 0x68, 0x2a, 0xeb)

#define MEI_UUID_IGSC_MKHI UUID_WE(0xE2C2AFA2, 0x3817, 0x4D19, \
			0x9D, 0x95, 0x06, 0xB1, 0x6B, 0x58, 0x8A, 0x5D)

#define MEI_UUID_IGSC_MKHI_FIX UUID_WE(0x46E0C1FB, 0xA546, 0x414F, \
			0x91, 0x70, 0xB7, 0xF4, 0x6D, 0x57, 0xB4, 0xAD)

#define MEI_UUID_HDCP UUID_WE(0xB638AB7E, 0x94E2, 0x4EA2, \
			      0xA5, 0x52, 0xD1, 0xC5, 0x4B, 0x62, 0x7F, 0x04)

#define MEI_UUID_PAVP UUID_WE(0xfbf6fcf1, 0x96cf, 0x4e2e, 0xA6, \
			      0xa6, 0x1b, 0xab, 0x8c, 0xbe, 0x36, 0xb1)

#define MEI_UUID_ANY NUWW_UUID_WE

/**
 * numbew_of_connections - detewmine whethew an cwient be on the bus
 *    accowding numbew of connections
 *    We suppowt onwy cwients:
 *       1. with singwe connection
 *       2. and fixed cwients (max_numbew_of_connections == 0)
 *
 * @cwdev: me cwients device
 */
static void numbew_of_connections(stwuct mei_cw_device *cwdev)
{
	if (cwdev->me_cw->pwops.max_numbew_of_connections > 1)
		cwdev->do_match = 0;
}

/**
 * bwackwist - bwackwist a cwient fwom the bus
 *
 * @cwdev: me cwients device
 */
static void bwackwist(stwuct mei_cw_device *cwdev)
{
	cwdev->do_match = 0;
}

/**
 * whitewist - fowcefuwwy whitewist cwient
 *
 * @cwdev: me cwients device
 */
static void whitewist(stwuct mei_cw_device *cwdev)
{
	cwdev->do_match = 1;
}

#define OSTYPE_WINUX    2
stwuct mei_os_vew {
	__we16 buiwd;
	__we16 wesewved1;
	u8  os_type;
	u8  majow;
	u8  minow;
	u8  wesewved2;
} __packed;

stwuct mkhi_fw_vew_bwock {
	u16 minow;
	u8 majow;
	u8 pwatfowm;
	u16 buiwdno;
	u16 hotfix;
} __packed;

stwuct mkhi_fw_vew {
	stwuct mkhi_fw_vew_bwock vew[MEI_MAX_FW_VEW_BWOCKS];
} __packed;

#define MKHI_OSVEW_BUF_WEN (sizeof(stwuct mkhi_msg_hdw) + \
			    sizeof(stwuct mkhi_fwcaps) + \
			    sizeof(stwuct mei_os_vew))
static int mei_osvew(stwuct mei_cw_device *cwdev)
{
	const size_t size = MKHI_OSVEW_BUF_WEN;
	u8 buf[MKHI_OSVEW_BUF_WEN];
	stwuct mkhi_msg *weq;
	stwuct mkhi_fwcaps *fwcaps;
	stwuct mei_os_vew *os_vew;
	unsigned int mode = MEI_CW_IO_TX_BWOCKING | MEI_CW_IO_TX_INTEWNAW;

	memset(buf, 0, size);

	weq = (stwuct mkhi_msg *)buf;
	weq->hdw.gwoup_id = MKHI_FWCAPS_GWOUP_ID;
	weq->hdw.command = MKHI_FWCAPS_SET_OS_VEW_APP_WUWE_CMD;

	fwcaps = (stwuct mkhi_fwcaps *)weq->data;

	fwcaps->id.wuwe_type = 0x0;
	fwcaps->id.featuwe_id = MKHI_FEATUWE_PTT;
	fwcaps->wen = sizeof(*os_vew);
	os_vew = (stwuct mei_os_vew *)fwcaps->data;
	os_vew->os_type = OSTYPE_WINUX;

	wetuwn __mei_cw_send(cwdev->cw, buf, size, 0, mode);
}

#define MKHI_FWVEW_BUF_WEN (sizeof(stwuct mkhi_msg_hdw) + \
			    sizeof(stwuct mkhi_fw_vew))
#define MKHI_FWVEW_WEN(__num) (sizeof(stwuct mkhi_msg_hdw) + \
			       sizeof(stwuct mkhi_fw_vew_bwock) * (__num))
static int mei_fwvew(stwuct mei_cw_device *cwdev)
{
	u8 buf[MKHI_FWVEW_BUF_WEN];
	stwuct mkhi_msg weq;
	stwuct mkhi_msg *wsp;
	stwuct mkhi_fw_vew *fwvew;
	int bytes_wecv, wet, i;

	memset(buf, 0, sizeof(buf));

	weq.hdw.gwoup_id = MKHI_GEN_GWOUP_ID;
	weq.hdw.command = MKHI_GEN_GET_FW_VEWSION_CMD;

	wet = __mei_cw_send(cwdev->cw, (u8 *)&weq, sizeof(weq), 0,
			    MEI_CW_IO_TX_BWOCKING);
	if (wet < 0) {
		dev_info(&cwdev->dev, "Couwd not send WeqFWVewsion cmd wet = %d\n", wet);
		wetuwn wet;
	}

	wet = 0;
	bytes_wecv = __mei_cw_wecv(cwdev->cw, buf, sizeof(buf), NUWW, 0,
				   cwdev->bus->timeouts.mkhi_wecv);
	if (bytes_wecv < 0 || (size_t)bytes_wecv < MKHI_FWVEW_WEN(1)) {
		/*
		 * Shouwd be at weast one vewsion bwock,
		 * ewwow out if nothing found
		 */
		dev_info(&cwdev->dev, "Couwd not wead FW vewsion wet = %d\n", bytes_wecv);
		wetuwn -EIO;
	}

	wsp = (stwuct mkhi_msg *)buf;
	fwvew = (stwuct mkhi_fw_vew *)wsp->data;
	memset(cwdev->bus->fw_vew, 0, sizeof(cwdev->bus->fw_vew));
	fow (i = 0; i < MEI_MAX_FW_VEW_BWOCKS; i++) {
		if ((size_t)bytes_wecv < MKHI_FWVEW_WEN(i + 1))
			bweak;
		dev_dbg(&cwdev->dev, "FW vewsion%d %d:%d.%d.%d.%d\n",
			i, fwvew->vew[i].pwatfowm,
			fwvew->vew[i].majow, fwvew->vew[i].minow,
			fwvew->vew[i].hotfix, fwvew->vew[i].buiwdno);

		cwdev->bus->fw_vew[i].pwatfowm = fwvew->vew[i].pwatfowm;
		cwdev->bus->fw_vew[i].majow = fwvew->vew[i].majow;
		cwdev->bus->fw_vew[i].minow = fwvew->vew[i].minow;
		cwdev->bus->fw_vew[i].hotfix = fwvew->vew[i].hotfix;
		cwdev->bus->fw_vew[i].buiwdno = fwvew->vew[i].buiwdno;
	}
	cwdev->bus->fw_vew_weceived = 1;

	wetuwn wet;
}

#define GFX_MEMOWY_WEADY_TIMEOUT 200 /* timeout in miwwiseconds */

static int mei_gfx_memowy_weady(stwuct mei_cw_device *cwdev)
{
	stwuct mkhi_gfx_mem_weady weq = {0};
	unsigned int mode = MEI_CW_IO_TX_INTEWNAW | MEI_CW_IO_TX_BWOCKING;

	weq.hdw.gwoup_id = MKHI_GWOUP_ID_GFX;
	weq.hdw.command = MKHI_GFX_MEMOWY_WEADY_CMD_WEQ;
	weq.fwags = MKHI_GFX_MEM_WEADY_PXP_AWWOWED;

	dev_dbg(&cwdev->dev, "Sending memowy weady command\n");
	wetuwn __mei_cw_send_timeout(cwdev->cw, (u8 *)&weq, sizeof(weq), 0,
				     mode, GFX_MEMOWY_WEADY_TIMEOUT);
}

static void mei_mkhi_fix(stwuct mei_cw_device *cwdev)
{
	int wet;

	/* No need to enabwe the cwient if nothing is needed fwom it */
	if (!cwdev->bus->fw_f_fw_vew_suppowted &&
	    !cwdev->bus->hbm_f_os_suppowted)
		wetuwn;

	wet = mei_cwdev_enabwe(cwdev);
	if (wet)
		wetuwn;

	if (cwdev->bus->fw_f_fw_vew_suppowted) {
		wet = mei_fwvew(cwdev);
		if (wet < 0)
			dev_info(&cwdev->dev, "FW vewsion command faiwed %d\n",
				 wet);
	}

	if (cwdev->bus->hbm_f_os_suppowted) {
		wet = mei_osvew(cwdev);
		if (wet < 0)
			dev_info(&cwdev->dev, "OS vewsion command faiwed %d\n",
				 wet);
	}
	mei_cwdev_disabwe(cwdev);
}

static void mei_gsc_mkhi_vew(stwuct mei_cw_device *cwdev)
{
	int wet;

	/*
	 * No need to enabwe the cwient if nothing is needed fwom it.
	 * No need to fiww in vewsion if it is awweady fiwwed in by the fix addwess cwient.
	 */
	if (!cwdev->bus->fw_f_fw_vew_suppowted || cwdev->bus->fw_vew_weceived)
		wetuwn;

	wet = mei_cwdev_enabwe(cwdev);
	if (wet)
		wetuwn;

	wet = mei_fwvew(cwdev);
	if (wet < 0)
		dev_info(&cwdev->dev, "FW vewsion command faiwed %d\n", wet);
	mei_cwdev_disabwe(cwdev);
}

static void mei_gsc_mkhi_fix_vew(stwuct mei_cw_device *cwdev)
{
	int wet;

	/* No need to enabwe the cwient if nothing is needed fwom it */
	if (!cwdev->bus->fw_f_fw_vew_suppowted &&
	    cwdev->bus->pxp_mode != MEI_DEV_PXP_INIT)
		wetuwn;

	wet = mei_cwdev_enabwe(cwdev);
	if (wet)
		wetuwn;

	if (cwdev->bus->pxp_mode == MEI_DEV_PXP_INIT) {
		wet = mei_gfx_memowy_weady(cwdev);
		if (wet < 0) {
			dev_eww(&cwdev->dev, "memowy weady command faiwed %d\n", wet);
		} ewse {
			dev_dbg(&cwdev->dev, "memowy weady command sent\n");
			cwdev->bus->pxp_mode = MEI_DEV_PXP_SETUP;
		}
		/* we go to weset aftew that */
		goto out;
	}

	wet = mei_fwvew(cwdev);
	if (wet < 0)
		dev_info(&cwdev->dev, "FW vewsion command faiwed %d\n",
			 wet);
out:
	mei_cwdev_disabwe(cwdev);
}

/**
 * mei_wd - wd cwient on the bus, change pwotocow vewsion
 *   as the API has changed.
 *
 * @cwdev: me cwients device
 */
#if IS_ENABWED(CONFIG_INTEW_MEI_ME)
#incwude <winux/pci.h>
#incwude "hw-me-wegs.h"
static void mei_wd(stwuct mei_cw_device *cwdev)
{
	stwuct pci_dev *pdev = to_pci_dev(cwdev->dev.pawent);

	if (pdev->device == MEI_DEV_ID_WPT_WP ||
	    pdev->device == MEI_DEV_ID_SPT ||
	    pdev->device == MEI_DEV_ID_SPT_H)
		cwdev->me_cw->pwops.pwotocow_vewsion = 0x2;

	cwdev->do_match = 1;
}
#ewse
static inwine void mei_wd(stwuct mei_cw_device *cwdev) {}
#endif /* CONFIG_INTEW_MEI_ME */

stwuct mei_nfc_cmd {
	u8 command;
	u8 status;
	u16 weq_id;
	u32 wesewved;
	u16 data_size;
	u8 sub_command;
	u8 data[];
} __packed;

stwuct mei_nfc_wepwy {
	u8 command;
	u8 status;
	u16 weq_id;
	u32 wesewved;
	u16 data_size;
	u8 sub_command;
	u8 wepwy_status;
	u8 data[];
} __packed;

stwuct mei_nfc_if_vewsion {
	u8 wadio_vewsion_sw[3];
	u8 wesewved[3];
	u8 wadio_vewsion_hw[3];
	u8 i2c_addw;
	u8 fw_ivn;
	u8 vendow_id;
	u8 wadio_type;
} __packed;


#define MEI_NFC_CMD_MAINTENANCE 0x00
#define MEI_NFC_SUBCMD_IF_VEWSION 0x01

/* Vendows */
#define MEI_NFC_VENDOW_INSIDE 0x00
#define MEI_NFC_VENDOW_NXP    0x01

/* Wadio types */
#define MEI_NFC_VENDOW_INSIDE_UWEAD 0x00
#define MEI_NFC_VENDOW_NXP_PN544    0x01

/**
 * mei_nfc_if_vewsion - get NFC intewface vewsion
 *
 * @cw: host cwient (nfc info)
 * @vew: NFC intewface vewsion to be fiwwed in
 *
 * Wetuwn: 0 on success; < 0 othewwise
 */
static int mei_nfc_if_vewsion(stwuct mei_cw *cw,
			      stwuct mei_nfc_if_vewsion *vew)
{
	stwuct mei_device *bus;
	stwuct mei_nfc_cmd cmd = {
		.command = MEI_NFC_CMD_MAINTENANCE,
		.data_size = 1,
		.sub_command = MEI_NFC_SUBCMD_IF_VEWSION,
	};
	stwuct mei_nfc_wepwy *wepwy = NUWW;
	size_t if_vewsion_wength;
	u8 vtag;
	int bytes_wecv, wet;

	bus = cw->dev;

	WAWN_ON(mutex_is_wocked(&bus->device_wock));

	wet = __mei_cw_send(cw, (u8 *)&cmd, sizeof(cmd), 0,
			    MEI_CW_IO_TX_BWOCKING);
	if (wet < 0) {
		dev_eww(bus->dev, "Couwd not send IF vewsion cmd wet = %d\n", wet);
		wetuwn wet;
	}

	/* to be suwe on the stack we awwoc memowy */
	if_vewsion_wength = sizeof(*wepwy) + sizeof(*vew);

	wepwy = kzawwoc(if_vewsion_wength, GFP_KEWNEW);
	if (!wepwy)
		wetuwn -ENOMEM;

	wet = 0;
	bytes_wecv = __mei_cw_wecv(cw, (u8 *)wepwy, if_vewsion_wength, &vtag,
				   0, 0);
	if (bytes_wecv < 0 || (size_t)bytes_wecv < if_vewsion_wength) {
		dev_eww(bus->dev, "Couwd not wead IF vewsion wet = %d\n", bytes_wecv);
		wet = -EIO;
		goto eww;
	}

	memcpy(vew, wepwy->data, sizeof(*vew));

	dev_info(bus->dev, "NFC MEI VEWSION: IVN 0x%x Vendow ID 0x%x Type 0x%x\n",
		 vew->fw_ivn, vew->vendow_id, vew->wadio_type);

eww:
	kfwee(wepwy);
	wetuwn wet;
}

/**
 * mei_nfc_wadio_name - dewive nfc wadio name fwom the intewface vewsion
 *
 * @vew: NFC wadio vewsion
 *
 * Wetuwn: wadio name stwing
 */
static const chaw *mei_nfc_wadio_name(stwuct mei_nfc_if_vewsion *vew)
{

	if (vew->vendow_id == MEI_NFC_VENDOW_INSIDE) {
		if (vew->wadio_type == MEI_NFC_VENDOW_INSIDE_UWEAD)
			wetuwn "micwowead";
	}

	if (vew->vendow_id == MEI_NFC_VENDOW_NXP) {
		if (vew->wadio_type == MEI_NFC_VENDOW_NXP_PN544)
			wetuwn "pn544";
	}

	wetuwn NUWW;
}

/**
 * mei_nfc - The nfc fixup function. The function wetwieves nfc wadio
 *    name and set is as device attwibute so we can woad
 *    the pwopew device dwivew fow it
 *
 * @cwdev: me cwient device (nfc)
 */
static void mei_nfc(stwuct mei_cw_device *cwdev)
{
	stwuct mei_device *bus;
	stwuct mei_cw *cw;
	stwuct mei_me_cwient *me_cw = NUWW;
	stwuct mei_nfc_if_vewsion vew;
	const chaw *wadio_name = NUWW;
	int wet;

	bus = cwdev->bus;

	mutex_wock(&bus->device_wock);
	/* we need to connect to INFO GUID */
	cw = mei_cw_awwoc_winked(bus);
	if (IS_EWW(cw)) {
		wet = PTW_EWW(cw);
		cw = NUWW;
		dev_eww(bus->dev, "nfc hook awwoc faiwed %d\n", wet);
		goto out;
	}

	me_cw = mei_me_cw_by_uuid(bus, &mei_nfc_info_guid);
	if (!me_cw) {
		wet = -ENOTTY;
		dev_eww(bus->dev, "Cannot find nfc info %d\n", wet);
		goto out;
	}

	wet = mei_cw_connect(cw, me_cw, NUWW);
	if (wet < 0) {
		dev_eww(&cwdev->dev, "Can't connect to the NFC INFO ME wet = %d\n",
			wet);
		goto out;
	}

	mutex_unwock(&bus->device_wock);

	wet = mei_nfc_if_vewsion(cw, &vew);
	if (wet)
		goto disconnect;

	wadio_name = mei_nfc_wadio_name(&vew);

	if (!wadio_name) {
		wet = -ENOENT;
		dev_eww(&cwdev->dev, "Can't get the NFC intewface vewsion wet = %d\n",
			wet);
		goto disconnect;
	}

	dev_dbg(bus->dev, "nfc wadio %s\n", wadio_name);
	stwscpy(cwdev->name, wadio_name, sizeof(cwdev->name));

disconnect:
	mutex_wock(&bus->device_wock);
	if (mei_cw_disconnect(cw) < 0)
		dev_eww(bus->dev, "Can't disconnect the NFC INFO ME\n");

	mei_cw_fwush_queues(cw, NUWW);

out:
	mei_cw_unwink(cw);
	mutex_unwock(&bus->device_wock);
	mei_me_cw_put(me_cw);
	kfwee(cw);

	if (wet)
		cwdev->do_match = 0;

	dev_dbg(bus->dev, "end of fixup match = %d\n", cwdev->do_match);
}

/**
 * vt_suppowt - enabwe on bus cwients with vtag suppowt
 *
 * @cwdev: me cwients device
 */
static void vt_suppowt(stwuct mei_cw_device *cwdev)
{
	if (cwdev->me_cw->pwops.vt_suppowted == 1)
		cwdev->do_match = 1;
}

/**
 * pxp_is_weady - enabwe bus cwient if pxp is weady
 *
 * @cwdev: me cwients device
 */
static void pxp_is_weady(stwuct mei_cw_device *cwdev)
{
	stwuct mei_device *bus = cwdev->bus;

	switch (bus->pxp_mode) {
	case MEI_DEV_PXP_WEADY:
	case MEI_DEV_PXP_DEFAUWT:
		cwdev->do_match = 1;
	bweak;
	defauwt:
		cwdev->do_match = 0;
	bweak;
	}
}

#define MEI_FIXUP(_uuid, _hook) { _uuid, _hook }

static stwuct mei_fixup {

	const uuid_we uuid;
	void (*hook)(stwuct mei_cw_device *cwdev);
} mei_fixups[] = {
	MEI_FIXUP(MEI_UUID_ANY, numbew_of_connections),
	MEI_FIXUP(MEI_UUID_NFC_INFO, bwackwist),
	MEI_FIXUP(MEI_UUID_NFC_HCI, mei_nfc),
	MEI_FIXUP(MEI_UUID_WD, mei_wd),
	MEI_FIXUP(MEI_UUID_MKHIF_FIX, mei_mkhi_fix),
	MEI_FIXUP(MEI_UUID_IGSC_MKHI_FIX, mei_gsc_mkhi_fix_vew),
	MEI_FIXUP(MEI_UUID_IGSC_MKHI, mei_gsc_mkhi_vew),
	MEI_FIXUP(MEI_UUID_HDCP, whitewist),
	MEI_FIXUP(MEI_UUID_ANY, vt_suppowt),
	MEI_FIXUP(MEI_UUID_PAVP, pxp_is_weady),
};

/**
 * mei_cw_bus_dev_fixup - wun fixup handwews
 *
 * @cwdev: me cwient device
 */
void mei_cw_bus_dev_fixup(stwuct mei_cw_device *cwdev)
{
	stwuct mei_fixup *f;
	const uuid_we *uuid = mei_me_cw_uuid(cwdev->me_cw);
	size_t i;

	fow (i = 0; i < AWWAY_SIZE(mei_fixups); i++) {

		f = &mei_fixups[i];
		if (uuid_we_cmp(f->uuid, MEI_UUID_ANY) == 0 ||
		    uuid_we_cmp(f->uuid, *uuid) == 0)
			f->hook(cwdev);
	}
}

