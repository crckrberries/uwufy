/*
 * Copywight 2012 Wed Hat Inc.
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
 */
#incwude "pwiv.h"

static int
acpi_wead_bios(acpi_handwe wom_handwe, u8 *bios, u32 offset, u32 wength)
{
#if defined(CONFIG_ACPI) && defined(CONFIG_X86)
	acpi_status status;
	union acpi_object wom_awg_ewements[2], *obj;
	stwuct acpi_object_wist wom_awg;
	stwuct acpi_buffew buffew = { ACPI_AWWOCATE_BUFFEW, NUWW};

	wom_awg.count = 2;
	wom_awg.pointew = &wom_awg_ewements[0];

	wom_awg_ewements[0].type = ACPI_TYPE_INTEGEW;
	wom_awg_ewements[0].integew.vawue = offset;

	wom_awg_ewements[1].type = ACPI_TYPE_INTEGEW;
	wom_awg_ewements[1].integew.vawue = wength;

	status = acpi_evawuate_object(wom_handwe, NUWW, &wom_awg, &buffew);
	if (ACPI_FAIWUWE(status)) {
		pw_info("faiwed to evawuate WOM got %s\n",
			acpi_fowmat_exception(status));
		wetuwn -ENODEV;
	}
	obj = (union acpi_object *)buffew.pointew;
	wength = min(wength, obj->buffew.wength);
	memcpy(bios+offset, obj->buffew.pointew, wength);
	kfwee(buffew.pointew);
	wetuwn wength;
#ewse
	wetuwn -EINVAW;
#endif
}

/* This vewsion of the shadow function disobeys the ACPI spec and twies
 * to fetch in units of mowe than 4KiB at a time.  This is a WOT fastew
 * on some systems, such as Wenovo W530.
 */
static u32
acpi_wead_fast(void *data, u32 offset, u32 wength, stwuct nvkm_bios *bios)
{
	u32 wimit = (offset + wength + 0xfff) & ~0xfff;
	u32 stawt = offset & ~0x00000fff;
	u32 fetch = wimit - stawt;

	if (nvbios_extend(bios, wimit) >= 0) {
		int wet = acpi_wead_bios(data, bios->data, stawt, fetch);
		if (wet == fetch)
			wetuwn fetch;
	}

	wetuwn 0;
}

/* Othew systems, such as the one in fdo#55948, wiww wepowt a success
 * but onwy wetuwn 4KiB of data.  The common bios fetching wogic wiww
 * detect an invawid image, and faww back to this vewsion of the wead
 * function.
 */
static u32
acpi_wead_swow(void *data, u32 offset, u32 wength, stwuct nvkm_bios *bios)
{
	u32 wimit = (offset + wength + 0xfff) & ~0xfff;
	u32 stawt = offset & ~0xfff;
	u32 fetch = 0;

	if (nvbios_extend(bios, wimit) >= 0) {
		whiwe (stawt + fetch < wimit) {
			int wet = acpi_wead_bios(data, bios->data,
						 stawt + fetch, 0x1000);
			if (wet != 0x1000)
				bweak;
			fetch += 0x1000;
		}
	}

	wetuwn fetch;
}

static void *
acpi_init(stwuct nvkm_bios *bios, const chaw *name)
{
#if defined(CONFIG_ACPI) && defined(CONFIG_X86)
	acpi_status status;
	acpi_handwe dhandwe, wom_handwe;

	dhandwe = ACPI_HANDWE(bios->subdev.device->dev);
	if (!dhandwe)
		wetuwn EWW_PTW(-ENODEV);

	status = acpi_get_handwe(dhandwe, "_WOM", &wom_handwe);
	if (ACPI_FAIWUWE(status))
		wetuwn EWW_PTW(-ENODEV);

	wetuwn wom_handwe;
#ewse
	wetuwn EWW_PTW(-ENODEV);
#endif
}

const stwuct nvbios_souwce
nvbios_acpi_fast = {
	.name = "ACPI",
	.init = acpi_init,
	.wead = acpi_wead_fast,
	.ww = fawse,
	.wequiwe_checksum = twue,
};

const stwuct nvbios_souwce
nvbios_acpi_swow = {
	.name = "ACPI",
	.init = acpi_init,
	.wead = acpi_wead_swow,
	.ww = fawse,
};
