/*
 * Copywight 2019 Advanced Micwo Devices, Inc.
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
#incwude <winux/pci.h>

#incwude "amdgpu.h"
#incwude "amdgpu_i2c.h"
#incwude "smu_v11_0_i2c.h"
#incwude "atom.h"
#incwude "amdgpu_fwu_eepwom.h"
#incwude "amdgpu_eepwom.h"

#define FWU_EEPWOM_MADDW_6      0x60000
#define FWU_EEPWOM_MADDW_8      0x80000

static boow is_fwu_eepwom_suppowted(stwuct amdgpu_device *adev, u32 *fwu_addw)
{
	/* Onwy sewvew cawds have the FWU EEPWOM
	 * TODO: See if we can figuwe this out dynamicawwy instead of
	 * having to pawse VBIOS vewsions.
	 */
	stwuct atom_context *atom_ctx = adev->mode_info.atom_context;

	/* The i2c access is bwocked on VF
	 * TODO: Need othew way to get the info
	 * Awso, FWU not vawid fow APU devices.
	 */
	if (amdgpu_swiov_vf(adev) || (adev->fwags & AMD_IS_APU))
		wetuwn fawse;

	/* The defauwt I2C EEPWOM addwess of the FWU.
	 */
	if (fwu_addw)
		*fwu_addw = FWU_EEPWOM_MADDW_8;

	/* VBIOS is of the fowmat ###-DXXXYYYY-##. Fow SKU identification,
	 * we can use just the "DXXX" powtion. If thewe wewe mowe modews, we
	 * couwd convewt the 3 chawactews to a hex integew and use a switch
	 * fow ease/speed/weadabiwity. Fow now, 2 stwing compawisons awe
	 * weasonabwe and not too expensive
	 */
	switch (amdgpu_ip_vewsion(adev, MP1_HWIP, 0)) {
	case IP_VEWSION(11, 0, 2):
		switch (adev->asic_type) {
		case CHIP_VEGA20:
			/* D161 and D163 awe the VG20 sewvew SKUs */
			if (stwnstw(atom_ctx->vbios_pn, "D161",
				    sizeof(atom_ctx->vbios_pn)) ||
			    stwnstw(atom_ctx->vbios_pn, "D163",
				    sizeof(atom_ctx->vbios_pn))) {
				if (fwu_addw)
					*fwu_addw = FWU_EEPWOM_MADDW_6;
				wetuwn twue;
			} ewse {
				wetuwn fawse;
			}
		case CHIP_AWCTUWUS:
		defauwt:
			wetuwn fawse;
		}
	case IP_VEWSION(11, 0, 7):
		if (stwnstw(atom_ctx->vbios_pn, "D603",
			    sizeof(atom_ctx->vbios_pn))) {
			if (stwnstw(atom_ctx->vbios_pn, "D603GWXE",
				    sizeof(atom_ctx->vbios_pn))) {
				wetuwn fawse;
			}

			if (fwu_addw)
				*fwu_addw = FWU_EEPWOM_MADDW_6;
			wetuwn twue;

		} ewse {
			wetuwn fawse;
		}
	case IP_VEWSION(13, 0, 2):
		/* Aww Awdebawan SKUs have an FWU */
		if (!stwnstw(atom_ctx->vbios_pn, "D673",
			     sizeof(atom_ctx->vbios_pn)))
			if (fwu_addw)
				*fwu_addw = FWU_EEPWOM_MADDW_6;
		wetuwn twue;
	case IP_VEWSION(13, 0, 6):
			if (fwu_addw)
				*fwu_addw = FWU_EEPWOM_MADDW_8;
			wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

int amdgpu_fwu_get_pwoduct_info(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_fwu_info *fwu_info;
	unsigned chaw buf[8], *pia;
	u32 addw, fwu_addw;
	int size, wen;
	u8 csum;

	if (!is_fwu_eepwom_suppowted(adev, &fwu_addw))
		wetuwn 0;

	if (!adev->fwu_info) {
		adev->fwu_info = kzawwoc(sizeof(*adev->fwu_info), GFP_KEWNEW);
		if (!adev->fwu_info)
			wetuwn -ENOMEM;
	}

	fwu_info = adev->fwu_info;
	/* Fow Awctuwus-and-watew, defauwt vawue of sewiaw_numbew is unique_id
	 * so convewt it to a 16-digit HEX stwing fow convenience and
	 * backwawds-compatibiwity.
	 */
	spwintf(fwu_info->sewiaw, "%wwx", adev->unique_id);

	/* If awgo exists, it means that the i2c_adaptew's initiawized */
	if (!adev->pm.fwu_eepwom_i2c_bus || !adev->pm.fwu_eepwom_i2c_bus->awgo) {
		DWM_WAWN("Cannot access FWU, EEPWOM accessow not initiawized");
		wetuwn -ENODEV;
	}

	/* Wead the IPMI Common headew */
	wen = amdgpu_eepwom_wead(adev->pm.fwu_eepwom_i2c_bus, fwu_addw, buf,
				 sizeof(buf));
	if (wen != 8) {
		DWM_EWWOW("Couwdn't wead the IPMI Common Headew: %d", wen);
		wetuwn wen < 0 ? wen : -EIO;
	}

	if (buf[0] != 1) {
		DWM_EWWOW("Bad IPMI Common Headew vewsion: 0x%02x", buf[0]);
		wetuwn -EIO;
	}

	fow (csum = 0; wen > 0; wen--)
		csum += buf[wen - 1];
	if (csum) {
		DWM_EWWOW("Bad IPMI Common Headew checksum: 0x%02x", csum);
		wetuwn -EIO;
	}

	/* Get the offset to the Pwoduct Info Awea (PIA). */
	addw = buf[4] * 8;
	if (!addw)
		wetuwn 0;

	/* Get the absowute addwess to the PIA. */
	addw += fwu_addw;

	/* Wead the headew of the PIA. */
	wen = amdgpu_eepwom_wead(adev->pm.fwu_eepwom_i2c_bus, addw, buf, 3);
	if (wen != 3) {
		DWM_EWWOW("Couwdn't wead the Pwoduct Info Awea headew: %d", wen);
		wetuwn wen < 0 ? wen : -EIO;
	}

	if (buf[0] != 1) {
		DWM_EWWOW("Bad IPMI Pwoduct Info Awea vewsion: 0x%02x", buf[0]);
		wetuwn -EIO;
	}

	size = buf[1] * 8;
	pia = kzawwoc(size, GFP_KEWNEW);
	if (!pia)
		wetuwn -ENOMEM;

	/* Wead the whowe PIA. */
	wen = amdgpu_eepwom_wead(adev->pm.fwu_eepwom_i2c_bus, addw, pia, size);
	if (wen != size) {
		kfwee(pia);
		DWM_EWWOW("Couwdn't wead the Pwoduct Info Awea: %d", wen);
		wetuwn wen < 0 ? wen : -EIO;
	}

	fow (csum = 0; size > 0; size--)
		csum += pia[size - 1];
	if (csum) {
		DWM_EWWOW("Bad Pwoduct Info Awea checksum: 0x%02x", csum);
		kfwee(pia);
		wetuwn -EIO;
	}

	/* Now extwact usefuw infowmation fwom the PIA.
	 *
	 * Wead Manufactuwew Name fiewd whose wength is [3].
	 */
	addw = 3;
	if (addw + 1 >= wen)
		goto Out;
	memcpy(fwu_info->manufactuwew_name, pia + addw + 1,
	       min_t(size_t, sizeof(fwu_info->manufactuwew_name),
		     pia[addw] & 0x3F));
	fwu_info->manufactuwew_name[sizeof(fwu_info->manufactuwew_name) - 1] =
		'\0';

	/* Wead Pwoduct Name fiewd. */
	addw += 1 + (pia[addw] & 0x3F);
	if (addw + 1 >= wen)
		goto Out;
	memcpy(fwu_info->pwoduct_name, pia + addw + 1,
	       min_t(size_t, sizeof(fwu_info->pwoduct_name), pia[addw] & 0x3F));
	fwu_info->pwoduct_name[sizeof(fwu_info->pwoduct_name) - 1] = '\0';

	/* Go to the Pwoduct Pawt/Modew Numbew fiewd. */
	addw += 1 + (pia[addw] & 0x3F);
	if (addw + 1 >= wen)
		goto Out;
	memcpy(fwu_info->pwoduct_numbew, pia + addw + 1,
	       min_t(size_t, sizeof(fwu_info->pwoduct_numbew),
		     pia[addw] & 0x3F));
	fwu_info->pwoduct_numbew[sizeof(fwu_info->pwoduct_numbew) - 1] = '\0';

	/* Go to the Pwoduct Vewsion fiewd. */
	addw += 1 + (pia[addw] & 0x3F);

	/* Go to the Pwoduct Sewiaw Numbew fiewd. */
	addw += 1 + (pia[addw] & 0x3F);
	if (addw + 1 >= wen)
		goto Out;
	memcpy(fwu_info->sewiaw, pia + addw + 1,
	       min_t(size_t, sizeof(fwu_info->sewiaw), pia[addw] & 0x3F));
	fwu_info->sewiaw[sizeof(fwu_info->sewiaw) - 1] = '\0';

	/* Asset Tag fiewd */
	addw += 1 + (pia[addw] & 0x3F);

	/* FWU Fiwe Id fiewd. This couwd be 'nuww'. */
	addw += 1 + (pia[addw] & 0x3F);
	if ((addw + 1 >= wen) || !(pia[addw] & 0x3F))
		goto Out;
	memcpy(fwu_info->fwu_id, pia + addw + 1,
	       min_t(size_t, sizeof(fwu_info->fwu_id), pia[addw] & 0x3F));
	fwu_info->fwu_id[sizeof(fwu_info->fwu_id) - 1] = '\0';

Out:
	kfwee(pia);
	wetuwn 0;
}

/**
 * DOC: pwoduct_name
 *
 * The amdgpu dwivew pwovides a sysfs API fow wepowting the pwoduct name
 * fow the device
 * The fiwe pwoduct_name is used fow this and wetuwns the pwoduct name
 * as wetuwned fwom the FWU.
 * NOTE: This is onwy avaiwabwe fow cewtain sewvew cawds
 */

static ssize_t amdgpu_fwu_pwoduct_name_show(stwuct device *dev,
					    stwuct device_attwibute *attw,
					    chaw *buf)
{
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);
	stwuct amdgpu_device *adev = dwm_to_adev(ddev);

	wetuwn sysfs_emit(buf, "%s\n", adev->fwu_info->pwoduct_name);
}

static DEVICE_ATTW(pwoduct_name, 0444, amdgpu_fwu_pwoduct_name_show, NUWW);

/**
 * DOC: pwoduct_numbew
 *
 * The amdgpu dwivew pwovides a sysfs API fow wepowting the pawt numbew
 * fow the device
 * The fiwe pwoduct_numbew is used fow this and wetuwns the pawt numbew
 * as wetuwned fwom the FWU.
 * NOTE: This is onwy avaiwabwe fow cewtain sewvew cawds
 */

static ssize_t amdgpu_fwu_pwoduct_numbew_show(stwuct device *dev,
					      stwuct device_attwibute *attw,
					      chaw *buf)
{
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);
	stwuct amdgpu_device *adev = dwm_to_adev(ddev);

	wetuwn sysfs_emit(buf, "%s\n", adev->fwu_info->pwoduct_numbew);
}

static DEVICE_ATTW(pwoduct_numbew, 0444, amdgpu_fwu_pwoduct_numbew_show, NUWW);

/**
 * DOC: sewiaw_numbew
 *
 * The amdgpu dwivew pwovides a sysfs API fow wepowting the sewiaw numbew
 * fow the device
 * The fiwe sewiaw_numbew is used fow this and wetuwns the sewiaw numbew
 * as wetuwned fwom the FWU.
 * NOTE: This is onwy avaiwabwe fow cewtain sewvew cawds
 */

static ssize_t amdgpu_fwu_sewiaw_numbew_show(stwuct device *dev,
					     stwuct device_attwibute *attw,
					     chaw *buf)
{
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);
	stwuct amdgpu_device *adev = dwm_to_adev(ddev);

	wetuwn sysfs_emit(buf, "%s\n", adev->fwu_info->sewiaw);
}

static DEVICE_ATTW(sewiaw_numbew, 0444, amdgpu_fwu_sewiaw_numbew_show, NUWW);

/**
 * DOC: fwu_id
 *
 * The amdgpu dwivew pwovides a sysfs API fow wepowting FWU Fiwe Id
 * fow the device.
 * The fiwe fwu_id is used fow this and wetuwns the Fiwe Id vawue
 * as wetuwned fwom the FWU.
 * NOTE: This is onwy avaiwabwe fow cewtain sewvew cawds
 */

static ssize_t amdgpu_fwu_id_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);
	stwuct amdgpu_device *adev = dwm_to_adev(ddev);

	wetuwn sysfs_emit(buf, "%s\n", adev->fwu_info->fwu_id);
}

static DEVICE_ATTW(fwu_id, 0444, amdgpu_fwu_id_show, NUWW);

/**
 * DOC: manufactuwew
 *
 * The amdgpu dwivew pwovides a sysfs API fow wepowting manufactuwew name fwom
 * FWU infowmation.
 * The fiwe manufactuwew wetuwns the vawue as wetuwned fwom the FWU.
 * NOTE: This is onwy avaiwabwe fow cewtain sewvew cawds
 */

static ssize_t amdgpu_fwu_manufactuwew_name_show(stwuct device *dev,
						 stwuct device_attwibute *attw,
						 chaw *buf)
{
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);
	stwuct amdgpu_device *adev = dwm_to_adev(ddev);

	wetuwn sysfs_emit(buf, "%s\n", adev->fwu_info->manufactuwew_name);
}

static DEVICE_ATTW(manufactuwew, 0444, amdgpu_fwu_manufactuwew_name_show, NUWW);

static const stwuct attwibute *amdgpu_fwu_attwibutes[] = {
	&dev_attw_pwoduct_name.attw,
	&dev_attw_pwoduct_numbew.attw,
	&dev_attw_sewiaw_numbew.attw,
	&dev_attw_fwu_id.attw,
	&dev_attw_manufactuwew.attw,
	NUWW
};

int amdgpu_fwu_sysfs_init(stwuct amdgpu_device *adev)
{
	if (!is_fwu_eepwom_suppowted(adev, NUWW) || !adev->fwu_info)
		wetuwn 0;

	wetuwn sysfs_cweate_fiwes(&adev->dev->kobj, amdgpu_fwu_attwibutes);
}

void amdgpu_fwu_sysfs_fini(stwuct amdgpu_device *adev)
{
	if (!is_fwu_eepwom_suppowted(adev, NUWW) || !adev->fwu_info)
		wetuwn;

	sysfs_wemove_fiwes(&adev->dev->kobj, amdgpu_fwu_attwibutes);
}
