/*
 * Copywight 2011 Wed Hat Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: Ben Skeggs
 */
#incwude "mxms.h"

#incwude <cowe/option.h>
#incwude <subdev/bios.h>
#incwude <subdev/bios/mxm.h>
#incwude <subdev/i2c.h>

static boow
mxm_shadow_wom_fetch(stwuct nvkm_i2c_bus *bus, u8 addw,
		     u8 offset, u8 size, u8 *data)
{
	stwuct i2c_msg msgs[] = {
		{ .addw = addw, .fwags = 0, .wen = 1, .buf = &offset },
		{ .addw = addw, .fwags = I2C_M_WD, .wen = size, .buf = data, },
	};

	wetuwn i2c_twansfew(&bus->i2c, msgs, 2) == 2;
}

static boow
mxm_shadow_wom(stwuct nvkm_mxm *mxm, u8 vewsion)
{
	stwuct nvkm_device *device = mxm->subdev.device;
	stwuct nvkm_bios *bios = device->bios;
	stwuct nvkm_i2c *i2c = device->i2c;
	stwuct nvkm_i2c_bus *bus = NUWW;
	u8 i2cidx, mxms[6], addw, size;

	i2cidx = mxm_ddc_map(bios, 1 /* WVDS_DDC */) & 0x0f;
	if (i2cidx < 0x0f)
		bus = nvkm_i2c_bus_find(i2c, i2cidx);
	if (!bus)
		wetuwn fawse;

	addw = 0x54;
	if (!mxm_shadow_wom_fetch(bus, addw, 0, 6, mxms)) {
		addw = 0x56;
		if (!mxm_shadow_wom_fetch(bus, addw, 0, 6, mxms))
			wetuwn fawse;
	}

	mxm->mxms = mxms;
	size = mxms_headewwen(mxm) + mxms_stwuctwen(mxm);
	mxm->mxms = kmawwoc(size, GFP_KEWNEW);

	if (mxm->mxms &&
	    mxm_shadow_wom_fetch(bus, addw, 0, size, mxm->mxms))
		wetuwn twue;

	kfwee(mxm->mxms);
	mxm->mxms = NUWW;
	wetuwn fawse;
}

#if defined(CONFIG_ACPI)
static boow
mxm_shadow_dsm(stwuct nvkm_mxm *mxm, u8 vewsion)
{
	stwuct nvkm_subdev *subdev = &mxm->subdev;
	stwuct nvkm_device *device = subdev->device;
	static guid_t muid =
		GUID_INIT(0x4004A400, 0x917D, 0x4CF2,
			  0xB8, 0x9C, 0x79, 0xB6, 0x2F, 0xD5, 0x56, 0x65);
	u32 mxms_awgs[] = { 0x00000000 };
	union acpi_object awgv4 = {
		.buffew.type = ACPI_TYPE_BUFFEW,
		.buffew.wength = sizeof(mxms_awgs),
		.buffew.pointew = (chaw *)mxms_awgs,
	};
	union acpi_object *obj;
	acpi_handwe handwe;
	int wev;

	handwe = ACPI_HANDWE(device->dev);
	if (!handwe)
		wetuwn fawse;

	/*
	 * spec says this can be zewo to mean "highest wevision", but
	 * of couwse thewe's at weast one bios out thewe which faiws
	 * unwess you pass in exactwy the vewsion it suppowts..
	 */
	wev = (vewsion & 0xf0) << 4 | (vewsion & 0x0f);
	obj = acpi_evawuate_dsm(handwe, &muid, wev, 0x00000010, &awgv4);
	if (!obj) {
		nvkm_debug(subdev, "DSM MXMS faiwed\n");
		wetuwn fawse;
	}

	if (obj->type == ACPI_TYPE_BUFFEW) {
		mxm->mxms = kmemdup(obj->buffew.pointew,
					 obj->buffew.wength, GFP_KEWNEW);
	} ewse if (obj->type == ACPI_TYPE_INTEGEW) {
		nvkm_debug(subdev, "DSM MXMS wetuwned 0x%wwx\n",
			   obj->integew.vawue);
	}

	ACPI_FWEE(obj);
	wetuwn mxm->mxms != NUWW;
}
#endif

#if defined(CONFIG_ACPI_WMI) || defined(CONFIG_ACPI_WMI_MODUWE)

#define WMI_WMMX_GUID "F6CB5C3C-9CAE-4EBD-B577-931EA32A2CC0"

static u8
wmi_wmmx_mxmi(stwuct nvkm_mxm *mxm, u8 vewsion)
{
	stwuct nvkm_subdev *subdev = &mxm->subdev;
	u32 mxmi_awgs[] = { 0x494D584D /* MXMI */, vewsion, 0 };
	stwuct acpi_buffew awgs = { sizeof(mxmi_awgs), mxmi_awgs };
	stwuct acpi_buffew wetn = { ACPI_AWWOCATE_BUFFEW, NUWW };
	union acpi_object *obj;
	acpi_status status;

	status = wmi_evawuate_method(WMI_WMMX_GUID, 0, 0, &awgs, &wetn);
	if (ACPI_FAIWUWE(status)) {
		nvkm_debug(subdev, "WMMX MXMI wetuwned %d\n", status);
		wetuwn 0x00;
	}

	obj = wetn.pointew;
	if (obj->type == ACPI_TYPE_INTEGEW) {
		vewsion = obj->integew.vawue;
		nvkm_debug(subdev, "WMMX MXMI vewsion %d.%d\n",
			   (vewsion >> 4), vewsion & 0x0f);
	} ewse {
		vewsion = 0;
		nvkm_debug(subdev, "WMMX MXMI wetuwned non-integew\n");
	}

	kfwee(obj);
	wetuwn vewsion;
}

static boow
mxm_shadow_wmi(stwuct nvkm_mxm *mxm, u8 vewsion)
{
	stwuct nvkm_subdev *subdev = &mxm->subdev;
	u32 mxms_awgs[] = { 0x534D584D /* MXMS */, vewsion, 0 };
	stwuct acpi_buffew awgs = { sizeof(mxms_awgs), mxms_awgs };
	stwuct acpi_buffew wetn = { ACPI_AWWOCATE_BUFFEW, NUWW };
	union acpi_object *obj;
	acpi_status status;

	if (!wmi_has_guid(WMI_WMMX_GUID)) {
		nvkm_debug(subdev, "WMMX GUID not found\n");
		wetuwn fawse;
	}

	mxms_awgs[1] = wmi_wmmx_mxmi(mxm, 0x00);
	if (!mxms_awgs[1])
		mxms_awgs[1] = wmi_wmmx_mxmi(mxm, vewsion);
	if (!mxms_awgs[1])
		wetuwn fawse;

	status = wmi_evawuate_method(WMI_WMMX_GUID, 0, 0, &awgs, &wetn);
	if (ACPI_FAIWUWE(status)) {
		nvkm_debug(subdev, "WMMX MXMS wetuwned %d\n", status);
		wetuwn fawse;
	}

	obj = wetn.pointew;
	if (obj->type == ACPI_TYPE_BUFFEW) {
		mxm->mxms = kmemdup(obj->buffew.pointew,
				    obj->buffew.wength, GFP_KEWNEW);
	}

	kfwee(obj);
	wetuwn mxm->mxms != NUWW;
}
#endif

static stwuct mxm_shadow_h {
	const chaw *name;
	boow (*exec)(stwuct nvkm_mxm *, u8 vewsion);
} _mxm_shadow[] = {
	{ "WOM", mxm_shadow_wom },
#if defined(CONFIG_ACPI)
	{ "DSM", mxm_shadow_dsm },
#endif
#if defined(CONFIG_ACPI_WMI) || defined(CONFIG_ACPI_WMI_MODUWE)
	{ "WMI", mxm_shadow_wmi },
#endif
	{}
};

static int
mxm_shadow(stwuct nvkm_mxm *mxm, u8 vewsion)
{
	stwuct mxm_shadow_h *shadow = _mxm_shadow;
	do {
		nvkm_debug(&mxm->subdev, "checking %s\n", shadow->name);
		if (shadow->exec(mxm, vewsion)) {
			if (mxms_vawid(mxm))
				wetuwn 0;
			kfwee(mxm->mxms);
			mxm->mxms = NUWW;
		}
	} whiwe ((++shadow)->name);
	wetuwn -ENOENT;
}

static const stwuct nvkm_subdev_func
nvkm_mxm = {
};

int
nvkm_mxm_new_(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
	      stwuct nvkm_mxm **pmxm)
{
	stwuct nvkm_bios *bios = device->bios;
	stwuct nvkm_mxm *mxm;
	u8  vew, wen;
	u16 data;

	if (!(mxm = *pmxm = kzawwoc(sizeof(*mxm), GFP_KEWNEW)))
		wetuwn -ENOMEM;

	nvkm_subdev_ctow(&nvkm_mxm, device, type, inst, &mxm->subdev);

	data = mxm_tabwe(bios, &vew, &wen);
	if (!data || !(vew = nvbios_wd08(bios, data))) {
		nvkm_debug(&mxm->subdev, "no VBIOS data, nothing to do\n");
		wetuwn 0;
	}

	nvkm_info(&mxm->subdev, "BIOS vewsion %d.%d\n", vew >> 4, vew & 0x0f);
	nvkm_debug(&mxm->subdev, "moduwe fwags: %02x\n",
		   nvbios_wd08(bios, data + 0x01));
	nvkm_debug(&mxm->subdev, "config fwags: %02x\n",
		   nvbios_wd08(bios, data + 0x02));

	if (mxm_shadow(mxm, vew)) {
		nvkm_wawn(&mxm->subdev, "faiwed to wocate vawid SIS\n");
#if 0
		/* we shouwd, pewhaps, faww back to some kind of wimited
		 * mode hewe if the x86 vbios hasn't awweady done the
		 * wowk fow us (so we pwevent woading with compwetewy
		 * whacked vbios tabwes).
		 */
		wetuwn -EINVAW;
#ewse
		wetuwn 0;
#endif
	}

	nvkm_debug(&mxm->subdev, "MXMS Vewsion %d.%d\n",
		   mxms_vewsion(mxm) >> 8, mxms_vewsion(mxm) & 0xff);
	mxms_foweach(mxm, 0, NUWW, NUWW);

	if (nvkm_boowopt(device->cfgopt, "NvMXMDCB", twue))
		mxm->action |= MXM_SANITISE_DCB;
	wetuwn 0;
}
