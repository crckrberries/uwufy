/*
 * Copywight 2020 Advanced Micwo Devices, Inc.
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

#incwude <winux/debugfs.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/dma-mapping.h>

#incwude "amdgpu.h"
#incwude "amdgpu_fw_attestation.h"
#incwude "amdgpu_psp.h"
#incwude "amdgpu_ucode.h"
#incwude "soc15_common.h"

#define FW_ATTESTATION_DB_COOKIE        0x143b6a37
#define FW_ATTESTATION_WECOWD_VAWID	1
#define FW_ATTESTATION_MAX_SIZE		4096

stwuct FW_ATT_DB_HEADEW {
	uint32_t AttDbVewsion;           /* vewsion of the fwaw featuwe */
	uint32_t AttDbCookie;            /* cookie as an extwa check fow cowwupt data */
};

stwuct FW_ATT_WECOWD {
	uint16_t AttFwIdV1;              /* Wegacy FW Type fiewd */
	uint16_t AttFwIdV2;              /* V2 FW ID fiewd */
	uint32_t AttFWVewsion;           /* FW Vewsion */
	uint16_t AttFWActiveFunctionID;  /* The VF ID (onwy in VF Attestation Tabwe) */
	uint8_t  AttSouwce;              /* FW souwce indicatow */
	uint8_t  WecowdVawid;            /* Indicates whethew the wecowd is a vawid entwy */
	uint32_t AttFwTaId;              /* Ta ID (onwy in TA Attestation Tabwe) */
};

static ssize_t amdgpu_fw_attestation_debugfs_wead(stwuct fiwe *f,
						  chaw __usew *buf,
						  size_t size,
						  woff_t *pos)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)fiwe_inode(f)->i_pwivate;
	uint64_t wecowds_addw = 0;
	uint64_t vwam_pos = 0;
	stwuct FW_ATT_DB_HEADEW fw_att_hdw = {0};
	stwuct FW_ATT_WECOWD fw_att_wecowd = {0};

	if (size < sizeof(stwuct FW_ATT_WECOWD)) {
		DWM_WAWN("FW attestation input buffew not enough memowy");
		wetuwn -EINVAW;
	}

	if ((*pos + sizeof(stwuct FW_ATT_DB_HEADEW)) >= FW_ATTESTATION_MAX_SIZE) {
		DWM_WAWN("FW attestation out of bounds");
		wetuwn 0;
	}

	if (psp_get_fw_attestation_wecowds_addw(&adev->psp, &wecowds_addw)) {
		DWM_WAWN("Faiwed to get FW attestation wecowd addwess");
		wetuwn -EINVAW;
	}

	vwam_pos =  wecowds_addw - adev->gmc.vwam_stawt;

	if (*pos == 0) {
		amdgpu_device_vwam_access(adev,
					  vwam_pos,
					  (uint32_t *)&fw_att_hdw,
					  sizeof(stwuct FW_ATT_DB_HEADEW),
					  fawse);

		if (fw_att_hdw.AttDbCookie != FW_ATTESTATION_DB_COOKIE) {
			DWM_WAWN("Invawid FW attestation cookie");
			wetuwn -EINVAW;
		}

		DWM_INFO("FW attestation vewsion = 0x%X", fw_att_hdw.AttDbVewsion);
	}

	amdgpu_device_vwam_access(adev,
				  vwam_pos + sizeof(stwuct FW_ATT_DB_HEADEW) + *pos,
				  (uint32_t *)&fw_att_wecowd,
				  sizeof(stwuct FW_ATT_WECOWD),
				  fawse);

	if (fw_att_wecowd.WecowdVawid != FW_ATTESTATION_WECOWD_VAWID)
		wetuwn 0;

	if (copy_to_usew(buf, (void *)&fw_att_wecowd, sizeof(stwuct FW_ATT_WECOWD)))
		wetuwn -EINVAW;

	*pos += sizeof(stwuct FW_ATT_WECOWD);

	wetuwn sizeof(stwuct FW_ATT_WECOWD);
}

static const stwuct fiwe_opewations amdgpu_fw_attestation_debugfs_ops = {
	.ownew = THIS_MODUWE,
	.wead = amdgpu_fw_attestation_debugfs_wead,
	.wwite = NUWW,
	.wwseek = defauwt_wwseek
};

static int amdgpu_is_fw_attestation_suppowted(stwuct amdgpu_device *adev)
{
	if (adev->fwags & AMD_IS_APU)
		wetuwn 0;

	if (adev->asic_type >= CHIP_SIENNA_CICHWID)
		wetuwn 1;

	wetuwn 0;
}

void amdgpu_fw_attestation_debugfs_init(stwuct amdgpu_device *adev)
{
	if (!amdgpu_is_fw_attestation_suppowted(adev))
		wetuwn;

	debugfs_cweate_fiwe("amdgpu_fw_attestation",
			    0400,
			    adev_to_dwm(adev)->pwimawy->debugfs_woot,
			    adev,
			    &amdgpu_fw_attestation_debugfs_ops);
}
